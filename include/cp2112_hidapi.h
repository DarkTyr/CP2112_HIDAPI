#ifndef CP2112_HIDAPI_H
#define CP2112_HIDAPI_H

#include <stdio.h>
#include <stdlib.h>
//#include <wchar.h>
#include <string.h>

#include "hidapi.h"

#ifdef __gnu_linux__
#include <unistd.h>
#endif

/******************************************************************************/
/*								Type defines								  */
/******************************************************************************/

typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned long long  uint64;

typedef signed char         int8;
typedef signed short        int16;
typedef signed long long    int64;

//#ifndef _MSC_VER
//typedef unsigned char	bool;
//#endif

#ifdef __x86_64__
    typedef unsigned int    uint32;
    typedef signed int      int32;
#else
    typedef unsigned long   uint32;
    typedef signed long     int32;
#endif

#define MAX_STR 64

class CP2112_HIDAPI
{
public:
    struct cp2112_configure_struct

    {
        uint8 gpio_output_ninput;

        uint8 gpio_nopendrain;

        bool gpio7_clk_en;

        bool gpio0_txtoggle_en;

        bool gpio1_rxtoggle_en;

        uint16 clock_divider;

    };

    struct I2C_RESULT
    {
        enum
        {
            I2C_SUCCESS,
            I2C_INPROGRESS,

            I2C_ADDR_NACK,
            I2C_ARB_LOST,
            I2C_RD_INCOMPLETE,
            I2C_WR_INCOMPLETE,
            I2C_TIMEOUT
        };
    };

    explicit CP2112_HIDAPI();
    ~CP2112_HIDAPI();

    /** @brief Open a HID device using a Vendor ID (VID), Product ID
        (PID)

        The first device with the specified VID and PID is opened. On
        success, this ties the class object to the USB device and opens
        the device.

        @ingroup CP2112
        @param vendorID The Vendor ID (VID) of the device to open.
        @param productID The Product ID (PID) of the device to open.

        @returns
            This function returns 1 on success or -1 on failure.
    */
    int open_device(uint16 vendorID, uint16 productID);
    int cp2112_configure();
    int cp2112_configure(struct cp2112_configure_struct chip_configuration);
    int SMBus_configure();
    int set_gpio(uint8 mask, uint8 GPIO);
    int get_gpio(uint8 *data);
    int i2c_write(uint8 i2cAddress, uint8 bytesToSend, uint8 *data);
    int i2c_read(uint8 i2cAddress, uint8 bytesToRecieve, uint8 *data);
    int i2c_write_read(uint8 i2cAddress, uint8 bytesToSend, uint8 bytesToRecieve, uint8 *data);
    int exit_device();


    hid_device_info device_info;
    uint verbosity;

private:
    hid_device *device;
    uint8 buffer[MAX_STR];
    int hidStatus;
    int i2cStatus;

    int deviceCheck();
    int xfer_status_response_proc();
};

#endif // CP2112_HIDAPI_H
