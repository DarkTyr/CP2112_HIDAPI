#include "../include/cp2112_hidapi.h"

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

int CP2112_HIDAPI::open_device(unsigned short vendorID, unsigned short productID, const wchar_t *serial_number)
{
    device = hid_open(vendorID, productID, serial_number);
    device_info = *hid_enumerate(vendorID, productID);
    return 0;
}
int CP2112_HIDAPI::open_path_device(const char *path)
{
    device = hid_open_path(path);
    return 0;
}
int CP2112_HIDAPI::exit_device()
{
    hid_close(device);
    return 0;
}
