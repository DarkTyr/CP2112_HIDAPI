#ifndef CP2112_HIDAPI_H
#define CP2112_HIDAPI_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>

#include "hidapi.h"

#define MAX_STR 128

class CP2112_HIDAPI
{
public:
    explicit CP2112_HIDAPI();
    ~CP2112_HIDAPI();
    int open_device(unsigned short vendorID, unsigned short productID, const wchar_t *serial_number);
    int open_path_device(const char *path);
    int exit_device();


    hid_device_info device_info;
private:
    hid_device *device;
    unsigned char buffer[MAX_STR];
    int status;
};

#endif // CP2112_HIDAPI_H
