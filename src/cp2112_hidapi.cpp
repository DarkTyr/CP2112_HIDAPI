#include "../include/cp2112_hidapi.h"
#include <Windows.h>

CP2112_HIDAPI::CP2112_HIDAPI()
{
    hid_init();
    device = NULL;
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
}
CP2112_HIDAPI::~CP2112_HIDAPI()
{
    hid_close(device);
    delete this;
}

int CP2112_HIDAPI::open_device(uint8 vendorID, uint8 productID)
{
    device = hid_open(vendorID, productID, NULL);
    device_info = *hid_enumerate(vendorID, productID);
    hid_free_enumeration(&device_info);
    return 0;
}

int CP2112_HIDAPI::i2c_configure()
{
    return 0;
}

int CP2112_HIDAPI::cp2112_configure()
{
    return 0;
}

int CP2112_HIDAPI::set_gpio(uint8 *data)
{
    return 0;
}

int CP2112_HIDAPI::get_gpio(uint8 mask, uint8 *data)
{
    return 0;
}

int CP2112_HIDAPI::i2c_write(uint8 i2cAddress, uint8 bytesToTransfer, uint8 *data)
{
    buffer[0] = 0x14;
    buffer[1] = i2cAddress;
    buffer[2] = bytesToTransfer;
    buffer[3] = *data;
    // Send data
    hidStatus = hid_write(device, buffer, bytesToTransfer + 3);
    while(i2cStatus = 0x01)
    {
        Sleep(25);
        // Send Transfer Status request
        buffer[0] = 0x15;   // Transfer Status request
        buffer[1] = 0x01;   //Request SMBus Transfer Status
        hidStatus = hid_write(device, buffer, 2);
        if(hidStatus == -1)
        {
            printf("failed to send transfer status request \n");
            //string = hid_error(device);
        }
        else
        {
            printf("Sent Transfer status request\n");
            printf("Bytes sent: %d \n",hidStatus - 1);
        }
        // Read Transfer Status Report about the SMBus data writen
        hidStatus = hid_read(device, buffer, 7);
        if(hidStatus == -1)
        {
            printf("failed to read status request from CP2112\n");
            //string = hid_error(device);
        }
        else
        {
            i2cStatus = buffer[1];
            printf("got status\n");
            printf("Bytes recieved: %d \n",hidStatus - 1);
            printf("Buffer[0]: %02hX\n", buffer[0]);
            printf("Buffer[1]: %02hX\n", buffer[1]);
            printf("Buffer[2]: %02hX\n", buffer[2]);
            printf("Buffer[3]: %02hX\n", buffer[3]);
            printf("Buffer[4]: %02hX\n", buffer[4]);
            printf("Buffer[5]: %02hX\n", buffer[5]);
            printf("Buffer[6]: %02hX\n", buffer[6]);
        }
    }
    return i2cStatus;
}

int CP2112_HIDAPI::i2c_read(uint8 i2cAddress, uint8 bytesToRecieve, uint8 *data)
{
    return 0;
}

int CP2112_HIDAPI::i2c_write_read(uint8 i2cAddress, uint8 bytesToTransfer, uint8 bytesToRecieve, uint8 *data)
{
    buffer[0] = 0x00;
    buffer[1] = 0x00;
    buffer[2] = 0x00;
    buffer[3] = 0x00;
    buffer[4] = 0x00;

    return 0;
}

int CP2112_HIDAPI::exit_device()
{
    hid_close(device);
    return 0;
}
