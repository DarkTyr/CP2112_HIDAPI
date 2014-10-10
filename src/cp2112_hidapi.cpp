#include "../include/cp2112_hidapi.h"
#include <Windows.h>

enum reportID
{
    //Feature Request
    RESET_DEVICE        = 0x01,
    GETSETGPIOCONFIG    = 0x02,
    GET_GPIO            = 0x03,
    SET_GPIO            = 0x04,
    GET_VER_INFO        = 0x05,
    GETSETSMBUSCONFIG   = 0x06,

    //Interrupt transfer
    DATA_READ           = 0x10,
    DATA_WRITE_READ     = 0x11,
    DATA_READ_FORCE     = 0x12,
    DATA_READ_RESPONSE  = 0x13,
    DATA_WRITE          = 0x14,
    XFER_STATUS_REQ     = 0x15,
    XFER_STATUS_RESPONSE= 0x16,
    CANCEL_TRANSFER     = 0x17,

    //USB custumization
    //Feature Request
    USB_LOCK            = 0x20,
    USB_USBCONFIG       = 0x21,
    USB_MANU_STRING     = 0x22,
    USB_PRODUCT_STRING  = 0x23,
    USB_SERIAL_STRING   = 0x24
};

enum smbusStatus
{
    BUS_IDLE            = 0x00,
    BUS_BUSY            = 0x01,
    BUS_GOOD            = 0x02,
};


CP2112_HIDAPI::CP2112_HIDAPI()
{
    hid_init();
    device = NULL;
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
}
CP2112_HIDAPI::~CP2112_HIDAPI()
{
    if(device == NULL)
    {
        ;
    }
    else
    {
        exit_device();
    }
    hid_exit();
}

int CP2112_HIDAPI::open_device(uint16 vendorID, uint16 productID)
{
    device = hid_open(vendorID, productID, NULL);
    //device_info = *hid_enumerate(vendorID, productID);
    //hid_free_enumeration(&device_info);
    return 0;
}

int CP2112_HIDAPI::SMBus_configure()
{
    ///Config the CP2112 SMBus for operation
    //printf("***Configure SMBus for operation***\n");
    buffer[0] = GETSETSMBUSCONFIG;   // Get/Set SMBus Config
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
    hidStatus = hid_send_feature_report(device, buffer, 14);
    /*
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
    */
    return hidStatus;
}

int CP2112_HIDAPI::cp2112_configure()
{
    ///Config the CP2112 I/O for operation
    //printf("***Configure the CP2112 IO for operation***\n");
    buffer[0] = GETSETGPIOCONFIG;   // Get/Set GPIO config (feature Request)
    buffer[1] = 0xFF;   // Set all I/O as outputs
    buffer[2] = 0x00;   // Keep as open drain
    buffer[3] = 0x06;   // Enable TX/RX LEDs
    buffer[4] = 0x00;   // Clock divider byte doesn't matter, not enabled
    buffer[5] = 0x00;   //
    hidStatus = hid_send_feature_report(device, buffer, 6);
    /*
    if(status == -1)
    {
        printf("failed to send GPIO config feature report\n");
    }
    else
    {
        printf("GPIO config sent to CP2112\n");
        printf("Bytes sent: %d \n",status - 1);
    }
    */
    return hidStatus;
}

int CP2112_HIDAPI::set_gpio(uint8 mask, uint8 GPIO)
{
    buffer[0] = SET_GPIO;
    buffer[1] = GPIO;
    buffer[2] = mask;
    hidStatus = hid_send_feature_report(device, buffer, 3);
    return hidStatus;
}

int CP2112_HIDAPI::get_gpio(uint8 *data)
{
    buffer[0] = GET_GPIO;
    hidStatus = hid_get_feature_report(device, buffer, 2);
    *data = buffer[1];
    return hidStatus;
}

int CP2112_HIDAPI::i2c_write(uint8 i2cAddress, uint8 bytesToSend, uint8 *data)
{
    buffer[0] = DATA_WRITE;
    buffer[1] = i2cAddress;
    buffer[2] = bytesToSend;
    memmove((void*) &buffer[3], (void*) &data[0], bytesToSend);
    // Send data
    hidStatus = hid_write(device, buffer, bytesToSend + 3);
    i2cStatus = 0x01;
    while(i2cStatus == 0x01)
    {
        //Sleep(10);
        /// Send Transfer Status request
        buffer[0] = XFER_STATUS_REQ;   // 0x15
        buffer[1] = 0x01;   //Request SMBus Transfer Status
        hidStatus = hid_write(device, buffer, 2);

        //Sleep(10);
        /// Read Transfer Status Report about the SMBus data writen
        memset((void*) &buffer[0], 0x00, sizeof(buffer));
        hidStatus = hid_read(device, buffer, 7);
        if(buffer[0] == 0x16)
        {
            i2cStatus = buffer[1];
        }
    }
    return i2cStatus;
}

int CP2112_HIDAPI::i2c_read(uint8 i2cAddress, uint8 bytesToRecieve, uint8 *data)
{
    uint8 bytesRead = 0;
    uint8 recieveIndex = 0;
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    /// Send Data Write Read Request
    buffer[0] = DATA_READ; //0x11
    buffer[1] = i2cAddress;
    buffer[2] = 0x00;
    buffer[3] = bytesToRecieve;
    memset((void*) &data[0], 0x00, sizeof(data));


    hidStatus = hid_write(device, buffer, 4);
    i2cStatus = 0x01;


    while(i2cStatus == 0x01)
    {
        //Sleep(10);
        /// Send Transfer Status request
        buffer[0] = XFER_STATUS_REQ;   // 0x15
        buffer[1] = 0x01;   //Request SMBus Transfer Status
        hidStatus = hid_write(device, buffer, 2);

        //Sleep(10);
        /// Read Transfer Status Report about the SMBus data writen
        memset((void*) &buffer[0], 0x00, sizeof(buffer));
        hidStatus = hid_read(device, buffer, 7);
        if(buffer[0] == 0x16)
        {
            i2cStatus = buffer[1];
        }
    }


    while(bytesRead < bytesToRecieve)
    {
        //Sleep(10);
        /// Send Transfer Status request
        buffer[0] = DATA_READ_FORCE;   // 0x12
        buffer[1] = 0x00;
        buffer[2] = 0xFF;   // Send upto 256 bytes please
        hidStatus = hid_write(device, buffer, 3);

        //Sleep(10);
        /// Read Transfer Status Report about the SMBus data writen
        memset((void*) &buffer[0], 0x00, sizeof(buffer));
        hidStatus = hid_read(device, buffer, 64);

        if(buffer[0] == 0x13)
        {
            if(buffer[2] > 0x00)
            {
                for(recieveIndex = 0; recieveIndex < buffer[2]; recieveIndex++)
                {
                    data[bytesRead] = buffer[recieveIndex + 3];
                    bytesRead++;
                }
            }
        }
    }

    return bytesRead;
}

int CP2112_HIDAPI::i2c_write_read(uint8 i2cAddress, uint8 bytesToSend, uint8 bytesToRecieve, uint8 *data)
{
    uint8 bytesRead = 0;
    uint8 recieveIndex = 0;
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    /// Send Data Write Read Request
    buffer[0] = DATA_WRITE_READ; //0x11
    buffer[1] = i2cAddress;
    buffer[2] = 0x00;
    buffer[3] = bytesToRecieve;
    buffer[4] = bytesToSend;

    memmove((void*) &buffer[5], (void*) &data[0], bytesToSend);
    memset((void*) &data[0], 0x00, sizeof(data));


    hidStatus = hid_write(device, buffer, 5 + bytesToSend);
    i2cStatus = 0x01;


    while(i2cStatus == 0x01)
    {
        //Sleep(10);
        /// Send Transfer Status request
        buffer[0] = XFER_STATUS_REQ;   // 0x15
        buffer[1] = 0x01;   //Request SMBus Transfer Status
        hidStatus = hid_write(device, buffer, 2);

        //Sleep(10);
        /// Read Transfer Status Report about the SMBus data writen
        memset((void*) &buffer[0], 0x00, sizeof(buffer));
        hidStatus = hid_read(device, buffer, 7);
        if(buffer[0] == 0x16)
        {
            i2cStatus = buffer[1];
        }
    }


    while(bytesRead < bytesToRecieve)
    {
        //Sleep(10);
        /// Send Transfer Status request
        buffer[0] = DATA_READ_FORCE;   // 0x12
        buffer[1] = 0x00;
        buffer[2] = 0xFF;   // Send upto 256 bytes please
        hidStatus = hid_write(device, buffer, 3);

        //Sleep(10);
        /// Read Transfer Status Report about the SMBus data writen
        memset((void*) &buffer[0], 0x00, sizeof(buffer));
        hidStatus = hid_read(device, buffer, 64);

        if(buffer[0] == 0x13)
        {
            if(buffer[2] > 0x00)
            {
                for(recieveIndex = 0; recieveIndex < buffer[2]; recieveIndex++)
                {
                    data[bytesRead] = buffer[recieveIndex + 3];
                    bytesRead++;
                }
            }
        }
    }

    return bytesRead;
}

int CP2112_HIDAPI::deviceCheck()
{
    if(device == NULL)
    {
        printf("device is still set to NULL");
        return -1;

    }
    else
    {
        return 0;
    }
}

int CP2112_HIDAPI::exit_device()
{
    hid_close(device);
    device = NULL;
    return 0;
}
