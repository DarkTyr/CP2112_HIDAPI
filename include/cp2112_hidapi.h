#ifndef CP2112_HIDAPI_H
#define CP2112_HIDAPI_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>

#include "hidapi.h"

/******************************************************************************/
/*								Type defines								  */
/******************************************************************************/

typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned long long uint64;

typedef signed char   int8;
typedef signed short  int16;
typedef signed long long int64;

#ifndef _MSC_VER
//typedef unsigned char	bool;
#endif

#ifdef __x86_64__
    typedef unsigned int   uint32;
    typedef signed int   int32;
#else
    typedef unsigned long   uint32;
    typedef signed long   int32;
#endif

#define MAX_STR 64

class CP2112_HIDAPI
{
public:
    explicit CP2112_HIDAPI();
    ~CP2112_HIDAPI();
    int open_device(uint16 vendorID, uint16 productID);
    int SMBus_configure();
    int cp2112_configure();
    int set_gpio(uint8 mask, uint8 GPIO);
    int get_gpio(uint8 *data);
    int i2c_write(uint8 i2cAddress, uint8 bytesToTransfer, uint8 *data);
    int i2c_read(uint8 i2cAddress, uint8 bytesToRecieve, uint8 *data);
    int i2c_write_read(uint8 i2cAddress, uint8 bytesToTransfer, uint8 bytesToRecieve, uint8 *data);
    int exit_device();


    hid_device_info device_info;
private:
    hid_device *device;
    uint8 buffer[MAX_STR];
    int hidStatus;
    int i2cStatus;
};

#endif // CP2112_HIDAPI_H
