#include <QCoreApplication>
#include <stdlib.h>

#include <iostream>
#include <iomanip>

/// need for sleep functionality
#include <Windows.h>


#include "../../../include/cp2112_hidapi.h"
#include "../../../include/hidapi.h"
//#include "hidapi.h"

using namespace std;
int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    // Buffer to hold information being sent on the SMBus
    uint8 buffer[255];

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

    status = EMU->open_device(0x10C4, 0xEA90);
    status = EMU->cp2112_configure();
    cout << "EMU CP2112_configure result : " << status << endl;
    status = EMU->SMBus_configure();
    cout << "EMU i2c_configure result    : " << status << endl;


    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x00;
    buffer[1] = 0x02;
    status = EMU->i2c_write(0xA4, 2, buffer);
    cout << "EMU i2c_write result        : " << status << endl;

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x9D;
    status = EMU->i2c_write_read(0xA4, 0x01, 0x08, buffer);
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


    EMU->exit_device();
    delete EMU;
    return a.exec();
}
