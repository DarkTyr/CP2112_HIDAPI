#include <QCoreApplication>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

/// need for sleep functionality
#include <Windows.h>


#include "../../../include/cp2112_hidapi.h"
#include "../../../include/hidapi.h"
//#include "hidapi.h"

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    // Buffer to hold information  being sent on the USB bus
    unsigned char buffer[255];

    // status of HID call, anything but zero is bad
    int status;

    // Enumerate and print the HID devices on the system
    struct hid_device_info *devs, *cur_dev;

    //devs = hid_enumerate(0x0, 0x0);
    printf("***Enumerate all devices with VID 0x10C4***\n");
    devs = hid_enumerate(0x10C4, 0x0);
    cur_dev = devs;
    while (cur_dev) {
        printf("Device Found \n  VID: %04hX PID: %04hX \n  path: %s \n  serial_number: %ls",
            cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
        printf("\n");
        printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
        printf("  Product:      %ls\n", cur_dev->product_string);
        printf("\n");
        cur_dev = cur_dev->next;
    }
    hid_free_enumeration(devs);

    printf("***open device mathcin VID 0x10C4 PID 0xEA90***\n");
    hid_device  *device;
    device = hid_open(0x10C4, 0xEA90, NULL);
    printf("device Opened\n");


    ///Config the CP2112 I/O for operation
    printf("***Configure the CP2112 IO for operation***\n");
    buffer[0] = 0x02;   // Get/Set GPIO config (feature Request)
    buffer[1] = 0xFF;   // Set all I/O as outputs
    buffer[2] = 0x00;   // Keep as open drain
    buffer[3] = 0x06;   // Enable TX/RX LEDs
    buffer[4] = 0x00;   // Clock divider byte doesn't matter, not enabled
    status = hid_send_feature_report(device, buffer, 6);
    if(status == -1)
    {
        printf("failed to send GPIO config feature report\n");
    }
    else
    {
        printf("GPIO config sent to CP2112\n");
        printf("Bytes sent: %d \n",status - 1);
    }

    ///Config the CP2112 SMBus for operation
    printf("***Configure SMBus for operation***\n");
    buffer[0] = 0x06;   // Get/Set SMBus Config
    buffer[1] = 0x00;   // Clock Speed (100Khz)
    buffer[2] = 0x01;
    buffer[3] = 0x86;
    buffer[4] = 0xA0;
    buffer[5] = 0x02;   // Device Address
    buffer[6] = 0x00;   // Auto send read disabled
    buffer[7] = 0x03;   // Write Time Out of 1000ms
    buffer[8] = 0xE8;
    buffer[9] = 0x03;   // Read Time out of 1000ms
    buffer[10] = 0xE8;
    buffer[11] = 0x00;   // SCL low timeout disabled
    buffer[12] = 0x00;   // 2 Retires
    buffer[13] = 0x00;
    status = hid_send_feature_report(device, buffer, 14);
    if(status == -1)
    {
        printf("failed to send SMBus config feature report\n");
        //string = hid_error(device);
    }
    else
    {
        printf("SMBus config sent to CP2112\n");
        printf("Bytes sent: %d \n",status - 1);
    }

    /// Set GPIO values on CP2112
    printf("***Set GPIO values\n");
    buffer[0] = 0x04;   // Set GPIO values
    buffer[1] = 0x00;   // Latch Value for GPIO
    buffer[2] = 0x00;   // Latch Mask
    status = hid_send_feature_report(device, buffer, 3);
    if(status == -1)
    {
        printf("failed to Set GPIO\n");
        //string = hid_error(device);
    }
    else
    {
        printf("Set GPIO\n");
        printf("Bytes sent: %d \n",status - 1);
    }
    /// Get current GPIO Values
    printf("***Get curent GPIO values");
    buffer[0] = 0x03;   //Get GPIO status
    status = hid_get_feature_report(device, buffer, 3);
    if(status == -1)
    {
        printf("failed to get GPIO\n");
        //string = hid_error(device);
    }
    else
    {
        printf("got GPIO states\n");
        printf("Bytes recieved: %d \n",status - 1);
        printf("Buffer[0]: %02hX\n", buffer[0]);
        printf("Buffer[1]: %02hX\n", buffer[1]);
        printf("Buffer[2]: %02hX\n", buffer[2]);
    }

    /// Send Transfer Status request
    printf("***Send Transfer status request***\n");
    buffer[0] = 0x15;   // Transfer Status request
    buffer[1] = 0x01;   //Request SMBus Transfer Status
    status = hid_write(device, buffer, 2);
    if(status == -1)
    {
        printf("failed to send transfer status request \n");
        //string = hid_error(device);
    }
    else
    {
        printf("Sent Transfer status request\n");
        printf("Bytes sent: %d \n",status - 1);
    }
    /// Read Transfer Status Report
    printf("***Read Transfer status request***\n");
    buffer[0] = 0x03;   //Get GPIO status
    status = hid_read_timeout(device, buffer, 7, 1000);
    if(status == -1)
    {
        printf("failed to read status request\n");
        //string = hid_error(device);
    }
    else
    {
        printf("got status\n");
        printf("Bytes recieved: %d \n",status - 1);
        printf("Buffer[0]: %02hX\n", buffer[0]);
        printf("Buffer[1]: %02hX\n", buffer[1]);
        printf("Buffer[2]: %02hX\n", buffer[2]);
        printf("Buffer[3]: %02hX\n", buffer[3]);
        printf("Buffer[4]: %02hX\n", buffer[4]);
        printf("Buffer[5]: %02hX\n", buffer[5]);
        printf("Buffer[6]: %02hX\n", buffer[6]);
    }


    /// Write something to SMBus
    printf("***Write to SMBus***\n");
    buffer[0] = 0x14; // Data write
    buffer[1] = 0xA4; // Address for MAXIM fan controller
    buffer[2] = 0x02; // Number of bytes to be writen
    buffer[3] = 0x00; // Page register Data
    buffer[4] = 0x01; // Fan channel 1
    status = hid_write(device, buffer, 5);
    if(status == -1)
    {
        printf("didn't write data\n");
    }
    else
    {
        printf("Data was able to send to CP2112 for the SMBus");
        printf("Bytes recieved: %d \n",status - 1);
    }

    /// Send Transfer Status request
    printf("***Send Transfer status request***\n");
    buffer[0] = 0x15;   // Transfer Status request
    buffer[1] = 0x01;   //Request SMBus Transfer Status
    status = hid_write(device, buffer, 2);
    if(status == -1)
    {
        printf("failed to send transfer status request \n");
        //string = hid_error(device);
    }
    else
    {
        printf("Sent Transfer status request\n");
        printf("Bytes sent: %d \n",status - 1);
    }
    /// Read Transfer Status Report about the SMBus data writen
    printf("***Read Transfer status request***\n");
    buffer[0] = 0x03;   //Get GPIO status
    status = hid_read_timeout(device, buffer, 7, 1000);
    if(status == -1)
    {
        printf("failed to read status request\n");
        //string = hid_error(device);
    }
    else
    {
        printf("got status\n");
        printf("Bytes recieved: %d \n",status - 1);
        printf("Buffer[0]: %02hX\n", buffer[0]);
        printf("Buffer[1]: %02hX\n", buffer[1]);
        printf("Buffer[2]: %02hX\n", buffer[2]);
        printf("Buffer[3]: %02hX\n", buffer[3]);
        printf("Buffer[4]: %02hX\n", buffer[4]);
        printf("Buffer[5]: %02hX\n", buffer[5]);
        printf("Buffer[6]: %02hX\n", buffer[6]);
        printf("Buffer[7]: %02hX\n", buffer[7]);
    }
    printf("waiting for 1 second\n");
    Sleep(1000);

    /// Send Data Write Read Request
    printf("***Send Data Read request***\n");
    buffer[0] = 0x11;   // Data Write Read Request
    buffer[1] = 0xA4;   // MAXIM IC Fan Controller Address
    buffer[2] = 0x00;   // Number of bytes to read back
    buffer[3] = 0x02;
    buffer[4] = 0x01;   // Number of bytes to send to target
    buffer[5] = 0x90;   //Data to send
    buffer[6] = 0x00;
    buffer[7] = 0x00;
    status = hid_write(device, buffer, 6);
    if(status == -1)
    {
        printf("failed to Data Write Read Request\n");
        //string = hid_error(device);
    }
    else
    {
        printf("succeded in Data Write Read Request\n");
        printf("Bytes sent: %d \n",status - 1);
    }
    Sleep(100);
    /// Read What was Read
    printf("***Read what was read before request***\n");
    status = hid_read_timeout(device, buffer, 63, 1000);
    if(status == -1)
    {
        printf("failed to read Data Read Request\n");
        //string = hid_error(device);
    }
    else
    {
        if (status == 0)
        {
            printf("CP2112 did not send any data back\n");
        }
        else
        {
            printf("got status\n");
            printf("Bytes recieved: %d \n",status - 1);
            printf("Buffer[0]: %02hX\n", buffer[0]);
            printf("Buffer[1]: %02hX\n", buffer[1]);
            printf("Buffer[2]: %02hX\n", buffer[2]);
            printf("Buffer[3]: %02hX\n", buffer[3]);
            printf("Buffer[4]: %02hX\n", buffer[4]);
            printf("Buffer[5]: %02hX\n", buffer[5]);
            printf("Buffer[6]: %02hX\n", buffer[6]);
            printf("Buffer[7]: %02hX\n", buffer[7]);
            printf("Buffer[8]: %02hX\n", buffer[8]);
        }
    }


    /// Send Transfer Status request
    printf("***Send Transfer status request***\n");
    buffer[0] = 0x12;   // Transfer Status request
    buffer[1] = 0x10;   //Request SMBus Transfer Status
    buffer[2] = 0x00;
    status = hid_write(device, buffer, 3);
    if(status == -1)
    {
        printf("failed to send transfer status request \n");
        //string = hid_error(device);
    }
    else
    {
        printf("Sent Transfer status request\n");
        printf("Bytes sent: %d \n",status - 1);
    }
    /// Read Transfer Status Report about the SMBus data writen
    printf("***Read Transfer status request***\n");
    //buffer[0] = 0x13;   //Get GPIO status
    status = hid_read_timeout(device, buffer, 5, 1000);
    if(status == -1)
    {
        printf("failed to read status request\n");
        //string = hid_error(device);
    }
    else
    {
        printf("got status\n");
        printf("Bytes recieved: %d \n",status - 1);
        printf("Buffer[0]: %02hX\n", buffer[0]);
        printf("Buffer[1]: %02hX\n", buffer[1]);
        printf("Buffer[2]: %02hX\n", buffer[2]);
        printf("Buffer[3]: %02hX\n", buffer[3]);
        printf("Buffer[4]: %02hX\n", buffer[4]);
        printf("Buffer[5]: %02hX\n", buffer[5]);
        printf("Buffer[6]: %02hX\n", buffer[6]);
        printf("Buffer[7]: %02hX\n", buffer[7]);
    }
    hid_close(device);


    printf("device closed\n");



    return a.exec();
}
