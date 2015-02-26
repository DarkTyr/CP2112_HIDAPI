#include <QCoreApplication>
#include <stdlib.h>

#include <iostream>
#include <iomanip>

/// need for sleep functionality
//#include <Windows.h>


#include "../../../include/cp2112_hidapi.h"
#include "../../../include/hidapi.h"
//#include "hidapi.h"

using namespace std;
int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    // Buffer to hold information being sent on the SMBus
    uint8 buffer[255];

    // Temp variable to hold 16 bit values in for display
    uint16 temp;
    double dTemp;

    // status of HID call, anything less than zero is bad
    int status;

    // Enumerate and print the HID devices on the system
    struct hid_device_info *devs, *cur_dev;


    cout <<"***Enumerate all devices with VID 0x10C4***\n";
    devs = hid_enumerate(0x10C4, 0x0);
    //devs = hid_enumerate(0x10C4, 0x0);
    cur_dev = devs;
    while (cur_dev)
    {
        cout << "Device Found" << endl;
        cout << uppercase << showbase << hex << setfill('0') << setw(4);
        cout.precision(4);
        cout << "  VID    : " << cur_dev->vendor_id << endl;
        cout << "  PID    : " << cur_dev->product_id << endl;
        cout << "  Serial : " << cur_dev->serial_number <<endl;
        cout << endl;
        wcout << "  Manufacturer : " << cur_dev->manufacturer_string << endl;
        wcout << "  Product      : " << cur_dev->product_string << endl;
        cout << endl;

        cur_dev = cur_dev->next;
    }
    hid_free_enumeration(devs);

    CP2112_HIDAPI *EMU = new CP2112_HIDAPI;

    status = EMU->open_device(0x10c4, 0xea90);
    if (status < 0)
    {
        delete EMU;
        return -1;
    }

    status = EMU->cp2112_configure();
    cout << "EMU CP2112_configure result : " << status << endl;
    status = EMU->SMBus_configure();
    cout << "EMU i2c_configure result    : " << status << endl;

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x10;
    buffer[1] = 0x55;
    status = EMU->i2c_write(0xA4, 0x02, buffer);
    cout << "EMU i2c_write result Disable write protect        : " << status << endl;

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x10;
    status = EMU->i2c_write_read(0xA4, 0x01, 0x01, buffer);
    cout << "EMU i2c_write_read result Write protect status       : " << status << endl;
    printf(" Buffer[0]: %02hX\n", buffer[0]);


    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x10;
    buffer[1] = 0x00;
    status = EMU->i2c_write(0xA4, 0x02, buffer);
    cout << "EMU i2c_write result Disable write protect        : " << status << endl;

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x10;
    status = EMU->i2c_write_read(0xA4, 0x01, 0x01, buffer);
    cout << "EMU i2c_write_read result Write protect status       : " << status << endl;
    printf(" Buffer[0]: %02hX\n", buffer[0]);


    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x00;
    buffer[1] = 0x01;
    status = EMU->i2c_write(0xA4, 0x02, buffer);
    cout << "EMU i2c_write result        : " << status << endl;
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x00;
    status = EMU->i2c_write_read(0xA4, 0x01, 0x01, buffer);
    cout << "EMU i2c_write_read result PAGE Value     : " << status << endl;
    printf(" Buffer[0]: %02hX\n", buffer[0]);

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x9B;
    status = EMU->i2c_write_read(0xA4, 0x01, 0x02, buffer);
    cout << "EMU i2c_write_read result        : " << status << endl;
    printf(" Buffer[0]: %02hX\n", buffer[0]);
    printf(" Buffer[1]: %02hX\n", buffer[1]);
    printf(" Buffer[2]: %02hX\n", buffer[2]);
    printf(" Buffer[3]: %02hX\n", buffer[3]);
    printf(" Buffer[4]: %02hX\n", buffer[4]);
    printf(" Buffer[5]: %02hX\n", buffer[5]);
    printf(" Buffer[6]: %02hX\n", buffer[6]);
    printf(" Buffer[7]: %02hX\n", buffer[7]);
    printf(" Buffer[8]: %02hX\n", buffer[8]);
    printf(" Buffer[9]: %02hX\n", buffer[9]);
    printf("Buffer[10]: %02hX\n", buffer[10]);
    printf("Buffer[11]: %02hX\n", buffer[11]);
    printf("Buffer[12]: %02hX\n", buffer[12]);

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0xF2;
    status = EMU->i2c_write_read(0xA4, 0x01, 0x20, buffer);
    cout << "EMU i2c_write_read result        : " << status << endl;
    printf(" Buffer[0]: %02hX\n", buffer[0]);
    printf(" Buffer[1]: %02hX\n", buffer[1]);
    printf(" Buffer[2]: %02hX\n", buffer[2]);
    printf(" Buffer[3]: %02hX\n", buffer[3]);
    printf(" Buffer[4]: %02hX\n", buffer[4]);
    printf(" Buffer[5]: %02hX\n", buffer[5]);
    printf(" Buffer[6]: %02hX\n", buffer[6]);
    printf(" Buffer[7]: %02hX\n", buffer[7]);
    printf(" Buffer[8]: %02hX\n", buffer[8]);
    printf(" Buffer[9]: %02hX\n", buffer[9]);
    printf("Buffer[10]: %02hX\n", buffer[10]);
    printf("Buffer[11]: %02hX\n", buffer[11]);
    printf("Buffer[12]: %02hX\n", buffer[12]);

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x00;
    buffer[1] = 0x00;
    status = EMU->i2c_write(0xA4, 2, buffer);
    cout << "EMU i2c_write result        : " << status << endl;
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x00;
    status = EMU->i2c_write_read(0xA4, 0x01, 0x01, buffer);
    cout << "EMU i2c_write_read result PAGE Value     : " << status << endl;
    printf(" Buffer[0]: %02hX\n", buffer[0]);

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x90;
    status = EMU->i2c_write_read(0xA4, 0x01, 0x02, buffer);
    cout << "EMU i2c_write_read result FAN0        : " << status << endl;
    printf(" Buffer[0]: %02hX\n", buffer[0]);
    printf(" Buffer[1]: %02hX\n", buffer[1]);
    temp = ((buffer[1] << 8) + buffer[0]);
    cout << dec;
    cout << "Fan0 RPM: " << temp << endl;

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x00;
    buffer[1] = 0x01;
    status = EMU->i2c_write(0xA4, 0x02, buffer);
    cout << "EMU i2c_write result        : " << status << endl;
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x00;
    status = EMU->i2c_write_read(0xA4, 0x01, 0x01, buffer);
    cout << "EMU i2c_write_read result PAGE Value     : " << status << endl;
    printf(" Buffer[0]: %02hX\n", buffer[0]);

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x90;
    status = EMU->i2c_write_read(0xA4, 0x01, 0x02, buffer);
    cout << "EMU i2c_write_read result FAN1        : " << status << endl;
    printf(" Buffer[0]: %02hX\n", buffer[0]);
    printf(" Buffer[1]: %02hX\n", buffer[1]);
    temp = ((buffer[1] << 8) + buffer[0]);
    cout << "Fan1 RPM: " << temp << endl;

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x00;
    buffer[1] = 0x02;
    status = EMU->i2c_write(0xA4, 0x02, buffer);
    cout << "EMU i2c_write result        : " << status << endl;
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x00;
    status = EMU->i2c_write_read(0xA4, 0x01, 0x01, buffer);
    cout << "EMU i2c_write_read result PAGE Value     : " << status << endl;
    printf(" Buffer[0]: %02hX\n", buffer[0]);

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x90;
    status = EMU->i2c_write_read(0xA4, 0x01, 0x02, buffer);
    cout << "EMU i2c_write_read result FAN2       : " << status << endl;
    printf(" Buffer[0]: %02hX\n", buffer[0]);
    printf(" Buffer[1]: %02hX\n", buffer[1]);
    temp = ((buffer[1] << 8) + buffer[0]);
    cout << "Fan2 RPM: " << temp << endl;


    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x00;
    buffer[1] = 0x06;
    status = EMU->i2c_write(0xA4, 0x02, buffer);
    cout << "EMU i2c_write result        : " << status << endl;

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x8D;
    status = EMU->i2c_write_read(0xA4, 0x01, 0x02, buffer);
    cout << "EMU i2c_write_read result TempINT       : " << status << endl;
    printf(" Buffer[0]: %02hX\n", buffer[0]);
    printf(" Buffer[1]: %02hX\n", buffer[1]);
    temp = ((buffer[1] << 8) + buffer[0])/100;
    cout << "TempINT: " << temp << endl;


    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x00;
    buffer[1] = 0x07;
    status = EMU->i2c_write(0xA4, 0x02, buffer);
    cout << "EMU i2c_write result        : " << status << endl;

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x8D;
    status = EMU->i2c_write_read(0xA4, 0x01, 0x02, buffer);
    cout << "EMU i2c_write_read result Temp1       : " << status << endl;
    printf(" Buffer[0]: %02hX\n", buffer[0]);
    printf(" Buffer[1]: %02hX\n", buffer[1]);
    temp = ((buffer[1] << 8) + buffer[0])/100;
    cout << "Temp1: " << temp << endl;
    dTemp = double((buffer[1] << 8) + buffer[0])/100;
    cout << "Temp1: " << dTemp <<endl;

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x00;
    buffer[1] = 0x07;
    status = EMU->i2c_write(0xA4, 0x02, buffer);
    cout << "EMU i2c_write result        : " << status << endl;

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x8D;
    status = EMU->i2c_write_read(0xA4, 0x01, 0x02, buffer);
    cout << "EMU i2c_write_read result Temp2       : " << status << endl;
    printf(" Buffer[0]: %02hX\n", buffer[0]);
    printf(" Buffer[1]: %02hX\n", buffer[1]);
    temp = ((buffer[1] << 8) + buffer[0])/100;
    cout << "Temp2: " << temp << endl;
    dTemp = double((buffer[1] << 8) + buffer[0])/100;
    cout << "Temp2: " << dTemp <<endl;


    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x00;
    buffer[1] = 0x0C;
    status = EMU->i2c_write(0xA4, 0x02, buffer);
    cout << "EMU i2c_write result        : " << status << endl;

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x8D;
    status = EMU->i2c_write_read(0xA4, 0x01, 0x02, buffer);
    cout << "EMU i2c_write_read result TempI2C1       : " << status << endl;
    printf(" Buffer[0]: %02hX\n", buffer[0]);
    printf(" Buffer[1]: %02hX\n", buffer[1]);
    temp = ((buffer[1] << 8) + buffer[0])/100;
    cout << "TempI2C1: " << temp << endl;
    dTemp = double((buffer[1] << 8) + buffer[0])/100;
    cout << "TempI2C1: " << dTemp <<endl;


    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x00;
    buffer[1] = 0x0D;
    status = EMU->i2c_write(0xA4, 0x02, buffer);
    cout << "EMU i2c_write result        : " << status << endl;

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x8D;
    status = EMU->i2c_write_read(0xA4, 0x01, 0x02, buffer);
    cout << "EMU i2c_write_read result I2C2       : " << status << endl;
    printf(" Buffer[0]: %02hX\n", buffer[0]);
    printf(" Buffer[1]: %02hX\n", buffer[1]);
    temp = ((buffer[1] << 8) + buffer[0])/100;
    cout << "TempI2C2: " << temp << endl;
    dTemp = double((buffer[1] << 8) + buffer[0])/100;
    cout << "TempI2C2: " << dTemp <<endl;


    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x00;
    buffer[1] = 0x0E;
    status = EMU->i2c_write(0xA4, 2, buffer);
    cout << "EMU i2c_write result        : " << status << endl;

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x8D;
    status = EMU->i2c_write_read(0xA4, 0x01, 0x02, buffer);
    cout << "EMU i2c_write_read result I2C3       : " << status << endl;
    printf("  Buffer[0]: %02hX\n", buffer[0]);
    printf("  Buffer[1]: %02hX\n", buffer[1]);
    temp = ((buffer[1] << 8) + buffer[0])/100;
    cout << "TempI2C3: " << temp << endl;
    dTemp = double((buffer[1] << 8) + buffer[0])/100;
    cout << "TempI2C3: " << dTemp <<endl;

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x00;
    buffer[1] = 0x0F;
    status = EMU->i2c_write(0xA4, 0x02, buffer);
    cout << "EMU i2c_write result        : " << status << endl;

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x8D;
    status = EMU->i2c_write_read(0xA4, 0x01, 0x02, buffer);
    cout << "EMU i2c_write_read result I2C4       : " << status << endl;
    printf("  Buffer[0]: %02hX\n", buffer[0]);
    printf("  Buffer[1]: %02hX\n", buffer[1]);

    temp = ((buffer[1] << 8) + buffer[0])/100;
    cout << "TempI2C4: " << temp <<endl;
    dTemp = double((buffer[1] << 8) + buffer[0])/100;
    cout << "TempI2C4: " << dTemp <<endl;
    cout << uppercase  << noshowbase << hex << setfill('0') << setw(8);
    cout << "  Buffer[0]: 0x" << +buffer[0] << endl;
    cout << "  Buffer[1]: 0x" << +buffer[1] << endl;
    temp = ((buffer[1] << 8) + buffer[0])/100;
    cout << "TempI2C3: " << temp << endl;
    dTemp = double((buffer[1] << 8) + buffer[0])/100;
    cout << "TempI2C3: " << dTemp <<endl;
    EMU->exit_device();
    //delete EMU;
    return 0;
}
