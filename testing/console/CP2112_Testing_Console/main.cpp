#include <QCoreApplication>
#include <stdio.h>
#include <stdlib.h>

#include "../../../include/hidapi.h"
//#include "hidapi.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Enumerate and print the HID devices on the system
    struct hid_device_info *devs, *cur_dev;

    //devs = hid_enumerate(0x0, 0x0);
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


    hid_device  *device;
    device = hid_open(0x10C4, 0xEA90, NULL);
    printf("device Opened\n");
    hid_close(device);
    printf("device closed\n");



    return a.exec();
}
