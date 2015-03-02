#include "../include/cp2112_hidapi.h"
//#include <Windows.h>
struct ReportID
{
    enum
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
};

struct SMBusStatus
{
    enum
    {
        BUS_IDLE            = 0x00,
        BUS_BUSY            = 0x01,
        BUS_GOOD            = 0x02,
        BUS_ERROR           = 0x03,
        // If BUS_BUSY
        I2C_ADDR_ACK        = 0x00,
        I2C_ADDR_NACK       = 0x01,
        I2C_RD_PROGRESS     = 0x02,
        I2C_WR_PROGRESS     = 0x03,
        // IF BUS_GOOD or BUS_ERROR
        I2C_TIMEOUT_NACK    = 0x00,
        I2C_TIMEOUT_NF      = 0x01,  //Bus not free
        I2C_ARB_LOST        = 0x02,  //Arbitration lost
        I2C_RD_INCOMPLETE   = 0x03,
        I2C_WR_INCOMPLETE   = 0x04,
        I2C_SUCCESS         = 0x05
    };
};


CP2112_HIDAPI::CP2112_HIDAPI()
{
    hid_init();
    device = NULL;
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    hidStatus = 0;
    i2cStatus = 0;
    verbosity = 0;
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
    if(device == NULL)
    {
        printf("No device matching VID: 0x%04hX PID: 0x%04hX\n", vendorID, productID);
        return -1;
    }
    device_info = *hid_enumerate(vendorID, productID);
    hid_free_enumeration(&device_info);
    return 1;
}

int CP2112_HIDAPI::cp2112_configure()
{
    hidStatus = deviceCheck();
    if (hidStatus < 0)
    {
        return -1;
    }
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    ///Config the CP2112 I/O for operation
    //printf("***Configure the CP2112 IO for operation***\n");
    buffer[0] = ReportID::GETSETGPIOCONFIG;   // Get/Set GPIO config (feature Request)
    buffer[1] = 0xFF;   // Set all I/O as outputs
    buffer[2] = 0x00;   // Keep as open drain
    buffer[3] = 0x06;   // Enable TX/RX LEDs
    buffer[4] = 0x00;   // Clock divider byte doesn't matter, not enabled
    buffer[5] = 0x00;   //
    hidStatus = hid_send_feature_report(device, buffer, 6);
    /*
    if(hidStatus == -1)
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

int CP2112_HIDAPI::cp2112_configure(cp2112_configure_struct chip_configuration)
{
    uint8 special_io_functions;
    special_io_functions = chip_configuration.gpio1_rxtoggle_en << 2 |
                           chip_configuration.gpio0_txtoggle_en << 1 |
                           chip_configuration.gpio7_clk_en << 0;

    hidStatus = deviceCheck();
    if (hidStatus < 0)
    {
        return -1;
    }

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    ///Config the CP2112 I/O for operation
    //printf("***Configure the CP2112 IO for operation***\n");
    buffer[0] = ReportID::GETSETGPIOCONFIG;   // Get/Set GPIO config (feature Request)
    buffer[1] = chip_configuration.gpio_output_ninput;   // Set all I/O as outputs
    buffer[2] = chip_configuration.gpio_nopendrain;   // Keep as open drain
    buffer[3] = special_io_functions;   // Enable TX/RX LEDs
    buffer[4] = (chip_configuration.clock_divider << 8) & 0xFF;   // Clock divider byte doesn't matter, not enabled
    buffer[5] = (chip_configuration.clock_divider << 0) & 0xFF;   //
    hidStatus = hid_send_feature_report(device, buffer, 6);
    /*
    if(hidStatus == -1)
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

int CP2112_HIDAPI::SMBus_configure()
{
    hidStatus = deviceCheck();
    if (hidStatus < 0)
    {
        return hidStatus;
    }
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    ///Config the CP2112 SMBus for operation
    //printf("***Configure SMBus for operation***\n");
    buffer[0] = ReportID::GETSETSMBUSCONFIG;   // Get/Set SMBus Config
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
    buffer[12] = 0x00;   // 0 Retires
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


int CP2112_HIDAPI::set_gpio(uint8 mask, uint8 GPIO)
{
    hidStatus = deviceCheck();
    if (hidStatus < 0)
    {
        return -1;
    }
    buffer[0] = ReportID::SET_GPIO;
    buffer[1] = GPIO;
    buffer[2] = mask;
    hidStatus = hid_send_feature_report(device, buffer, 0x03);
    return hidStatus;
}

int CP2112_HIDAPI::get_gpio(uint8 *data)
{
    hidStatus = deviceCheck();
    if (hidStatus < 0)
    {
        return -1;
    }
    buffer[0] = ReportID::GET_GPIO;
    hidStatus = hid_get_feature_report(device, buffer, 0x02);
    *data = buffer[1];
    return hidStatus;
}

int CP2112_HIDAPI::i2c_write(uint8 i2cAddress, uint8 bytesToSend, uint8 *data)
{
    hidStatus = deviceCheck();
    if (hidStatus < 0)
    {
        return -1;
    }
    buffer[0] = ReportID::DATA_WRITE;
    buffer[1] = i2cAddress;
    buffer[2] = bytesToSend;
    memmove((void*) &buffer[3], (void*) &data[0], bytesToSend);
    // Send dataverbosity
    hidStatus = hid_write(device, buffer, bytesToSend + 3);
    i2cStatus = 0x00;

    /// Send Transfer Status request
    buffer[0] = ReportID::XFER_STATUS_REQ;   // 0x15
    buffer[1] = 0x01;   //Request SMBus Transfer Status
    hidStatus = hid_write(device, buffer, 2);

    while(i2cStatus == I2C_RESULT::I2C_INPROGRESS)
    {    
        /// Read Transfer Status Report about the SMBus data writen
        memset((void*) &buffer[0], 0x00, sizeof(buffer));
        hidStatus = hid_read(device, buffer, 7);
        if(buffer[0] == ReportID::XFER_STATUS_RESPONSE)
        {
            i2cStatus = xfer_status_response_proc();
        }
    }
    return i2cStatus;
}

int CP2112_HIDAPI::i2c_read(uint8 i2cAddress, uint8 bytesToRecieve, uint8 *data)
{
    hidStatus = deviceCheck();
    if (hidStatus < 0)
    {
        return -1;
    }
    uint8 bytesRead = 0;
    uint8 recieveIndex = 0;
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    /// Send Data Write Read Request
    buffer[0] = ReportID::DATA_READ; //0x11
    buffer[1] = i2cAddress;
    buffer[2] = 0x00;
    buffer[3] = bytesToRecieve;
    memset((void*) &data[0], 0x00, sizeof(data));


    hidStatus = hid_write(device, buffer, 4);
    i2cStatus = 0x00;


    while(i2cStatus == I2C_RESULT::I2C_INPROGRESS)
    {
        /// Send Transfer Status request
        buffer[0] = ReportID::XFER_STATUS_REQ;   // 0x15
        buffer[1] = 0x01;   //Request SMBus Transfer Status
        hidStatus = hid_write(device, buffer, 2);

        /// Read Transfer Status Report about the SMBus data writen
        memset((void*) &buffer[0], 0x00, sizeof(buffer));
        hidStatus = hid_read(device, buffer, 7);
        if(buffer[0] == ReportID::XFER_STATUS_RESPONSE)
        {
            i2cStatus = xfer_status_response_proc();
        }
    }


    while(bytesRead < bytesToRecieve)
    {
        /// Send Transfer Status request
        buffer[0] = ReportID::DATA_READ_FORCE;   // 0x12
        buffer[1] = 0x00;
        buffer[2] = 0xFF;   // Send upto 256 bytes please
        hidStatus = hid_write(device, buffer, 3);

        /// Read Transfer Status Report about the SMBus data writen
        memset((void*) &buffer[0], 0x00, sizeof(buffer));
        hidStatus = hid_read(device, buffer, 64);

        if(buffer[0] == ReportID::DATA_READ_RESPONSE)
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
    hidStatus = deviceCheck();
    if (hidStatus < 0)
    {
        return -1;
    }
    uint16 bytesRead = 0;
    uint16 recieveIndex = 0;
    uint16 cp2112_bytesRead = 0;

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    /// Send Data Write Read Request
    buffer[0] = ReportID::DATA_WRITE_READ; //0x11
    buffer[1] = i2cAddress;
    buffer[2] = 0x00;
    buffer[3] = bytesToRecieve;
    buffer[4] = bytesToSend;

    memmove((void*) &buffer[5], (void*) &data[0], bytesToSend);
    memset((void*) &data[0], 0x00, sizeof(data));


    hidStatus = hid_write(device, buffer, 5 + bytesToSend);
    i2cStatus = 0x00;

    /// Send Transfer Status request
    buffer[0] = ReportID::XFER_STATUS_REQ;   // 0x15
    buffer[1] = 0x01;   //Request SMBus Transfer Status
    hidStatus = hid_write(device, buffer, 2);

    while(i2cStatus == I2C_RESULT::I2C_INPROGRESS)
    {

        /// Read Transfer Status Report about the SMBus data writen
        memset((void*) &buffer[0], 0x00, sizeof(buffer));
        hidStatus = hid_read_timeout(device, buffer, 7, 1000);
        if(buffer[0] == ReportID::XFER_STATUS_RESPONSE)
        {
            i2cStatus = xfer_status_response_proc();
            cp2112_bytesRead = (buffer[5] << 8) | (buffer[6] << 0);
        }
        if(i2cStatus == I2C_RESULT::I2C_INPROGRESS)
        {
            /// Send Transfer Status request
            buffer[0] = ReportID::XFER_STATUS_REQ;   // 0x15
            buffer[1] = 0x01;   //Request SMBus Transfer Status
            hidStatus = hid_write(device, buffer, 2);
        }
    }

    if(i2cStatus != I2C_RESULT::I2C_SUCCESS)
    {
        return -1;
    }

    while(bytesRead < bytesToRecieve)
    {
        /// Send force data read request
        buffer[0] = ReportID::DATA_READ_FORCE;   // 0x12
        buffer[1] = 0x00;
        buffer[2] = 0xFF;   // Send upto 256 bytes please
        hidStatus = hid_write(device, buffer, 3);

        while (buffer[0] != ReportID::DATA_READ_RESPONSE)
        {
            /// Read Transfer Status Report about the SMBus data writen
            memset((void*) &buffer[0], 0x00, sizeof(buffer));
            hidStatus = hid_read_timeout(device, buffer, 64, 1000);
            if(buffer[0] == ReportID::DATA_READ_RESPONSE)
            {
                cp2112_bytesRead = uint16(buffer[1] << 8 | buffer[2] << 0);
                if(cp2112_bytesRead > 0x00)
                {
                    if(bytesToRecieve < cp2112_bytesRead)
                    {
                        return I2C_RESULT::I2C_RD_INCOMPLETE;
                    }
                    for(recieveIndex = 0; recieveIndex < cp2112_bytesRead; recieveIndex++)
                    {
                        data[bytesRead] = buffer[recieveIndex + 3];
                        bytesRead++;
                    }
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
        printf("no USB device has been opened with this object");
        return -1;

    }
    else
    {
        return 0;
    }
}

int CP2112_HIDAPI::xfer_status_response_proc()
{
    if(buffer[0] == ReportID::XFER_STATUS_RESPONSE)
    {
        switch (buffer[1])
        {
        case SMBusStatus::BUS_IDLE :
            switch(buffer[2])
            {
            case SMBusStatus::I2C_ADDR_ACK      : return I2C_RESULT::I2C_SUCCESS;
            case SMBusStatus::I2C_ADDR_NACK     : return I2C_RESULT::I2C_ADDR_NACK;
            case SMBusStatus::I2C_RD_PROGRESS   : return I2C_RESULT::I2C_INPROGRESS;
            case SMBusStatus::I2C_WR_PROGRESS   : return I2C_RESULT::I2C_INPROGRESS;
            case SMBusStatus::I2C_SUCCESS       : return I2C_RESULT::I2C_SUCCESS;
            };
        case SMBusStatus::BUS_BUSY :
            switch(buffer[2])
            {
            case SMBusStatus::I2C_ADDR_ACK      : return I2C_RESULT::I2C_SUCCESS;
            case SMBusStatus::I2C_ADDR_NACK     : return I2C_RESULT::I2C_ADDR_NACK;
            case SMBusStatus::I2C_RD_PROGRESS   : return I2C_RESULT::I2C_INPROGRESS;
            case SMBusStatus::I2C_WR_PROGRESS   : return I2C_RESULT::I2C_INPROGRESS;
            };
        case SMBusStatus::BUS_GOOD :
            switch(buffer[2])
            {
            case SMBusStatus::I2C_SUCCESS       : return I2C_RESULT::I2C_SUCCESS;
            case SMBusStatus::I2C_TIMEOUT_NACK  : return I2C_RESULT::I2C_ADDR_NACK;
            case SMBusStatus::I2C_TIMEOUT_NF    : return I2C_RESULT::I2C_TIMEOUT;
            case SMBusStatus::I2C_ARB_LOST      : return I2C_RESULT::I2C_ARB_LOST;
            case SMBusStatus::I2C_RD_INCOMPLETE : return I2C_RESULT::I2C_RD_INCOMPLETE;
            case SMBusStatus::I2C_WR_INCOMPLETE : return I2C_RESULT::I2C_WR_INCOMPLETE;
            };
        case SMBusStatus::BUS_ERROR :
            switch(buffer[2])
            {
            case SMBusStatus::I2C_TIMEOUT_NACK  : return I2C_RESULT::I2C_ADDR_NACK;
            case SMBusStatus::I2C_TIMEOUT_NF    : return I2C_RESULT::I2C_TIMEOUT;
            case SMBusStatus::I2C_ARB_LOST      : return I2C_RESULT::I2C_ARB_LOST;
            case SMBusStatus::I2C_RD_INCOMPLETE : return I2C_RESULT::I2C_RD_INCOMPLETE;
            case SMBusStatus::I2C_WR_INCOMPLETE : return I2C_RESULT::I2C_WR_INCOMPLETE;
            }
        }
    }

    return 0;
}

int CP2112_HIDAPI::exit_device()
{
    if (device == NULL)
    {
        return 0;
    }

    hid_close(device);
    device = NULL;
    return 0;
}
