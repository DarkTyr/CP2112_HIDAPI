#include <stdlib.h>

#include <iostream>
#include <iomanip>

#include <stdint.h>

/// need for sleep functionality
//#include <Windows.h>

//#include "../../../include/cp2112_hidapi.h"
//#include "../../../include/hidapi.h"
#include "cp2112_hidapi.h"
#include "hidapi.h"
#include "maxim_ic_lib.h"

using namespace std;
//int main(int argc, char *argv[])
int main()
{

    // Buffer to hold information being sent on the SMBus
    uint8 buffer[255] = {0x00};
    uint8 bytesRxed = 0;

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
    Maxim_IC::MAX31785 *fan_ctrl = new Maxim_IC::MAX31785;
    struct Maxim_IC::TEMPS_DOUBLE temps_double;
    struct Maxim_IC::TEMPS_RAW temps_raw;
    struct Maxim_IC::RPM_DOUBLE fanrpm_double;
    struct Maxim_IC::RPM_RAW fanrpm_raw;
    struct Maxim_IC::VOLTAGE_STRUC voltage_structure;

    status = EMU->open_device(0x10c4, 0xea90);
    if (status < 0)
    {
        delete EMU;
        delete fan_ctrl;
        return -1;
    }

    //status = EMU->cp2112_configure();

    struct CP2112_HIDAPI::cp2112_configure_struct configuration;
    configuration.clock_divider = 0x0000;
    configuration.gpio0_txtoggle_en = 1;
    configuration.gpio1_rxtoggle_en = 1;
    configuration.gpio7_clk_en = 0;
    configuration.gpio_nopendrain = 0x00;
    configuration.gpio_output_ninput = 0xFF;
    status = EMU->cp2112_configure(configuration);

    cout << "EMU CP2112_configure result : " << status << endl;

    status = EMU->SMBus_configure();
    cout << "EMU i2c_configure result    : " << status << endl;

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x10;
    buffer[1] = 0x00;
    status = EMU->i2c_write(0xA4, 0x02, buffer);
    cout << "EMU i2c_write result Disable write protect        : " << status << endl;

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x10;
    EMU->verbosity = 0;
    status = EMU->i2c_write_read(0xA4, 0x01, 0x01, &bytesRxed, buffer);
    cout << "EMU i2c_write_read result Write protect status       : " << status << endl;
    printf(" Buffer[0]: %02hX\n", buffer[0]);


    fan_ctrl->get_Temps(EMU, &temps_double, &temps_raw);
    cout << "temps_double::int = " << temps_double.Int << endl;
    cout << "temps_double::ch0 = " << temps_double.Ch0 << endl;
    cout << "temps_double::ch1 = " << temps_double.Ch1 << endl;
    cout << "temps_double::ch2 = " << temps_double.Ch2 << endl;
    cout << "temps_double::ch3 = " << temps_double.Ch3 << endl;
    cout << "temps_double::ch4 = " << temps_double.Ch4 << endl;
    cout << "temps_double::ch5 = " << temps_double.Ch5 << endl;
    cout << "temps_double::D00 = " << temps_double.D00 << endl;
    cout << "temps_double::D01 = " << temps_double.D01 << endl;
    cout << "temps_double::D02 = " << temps_double.D02 << endl;
    cout << "temps_double::D03 = " << temps_double.D03 << endl;

    fan_ctrl->get_RPM(EMU, &fanrpm_double, &fanrpm_raw);
    cout << "fanrpm_double::ch0 = " << fanrpm_double.Ch0 << endl;
    cout << "fanrpm_double::ch1 = " << fanrpm_double.Ch1 << endl;
    cout << "fanrpm_double::ch2 = " << fanrpm_double.Ch2 << endl;
    cout << "fanrpm_double::ch3 = " << fanrpm_double.Ch3 << endl;
    cout << "fanrpm_double::ch4 = " << fanrpm_double.Ch4 << endl;
    cout << "fanrpm_double::ch5 = " << fanrpm_double.Ch5 << endl;
    EMU->verbosity = 0;

    fan_ctrl->get_Volt(EMU, &voltage_structure);
    cout << "volts_double::ch0::vout_double = " << voltage_structure.Ch0.vout_double << endl;
    cout << "volts_double::ch1::vout_double = " << voltage_structure.Ch1.vout_double << endl;
    cout << "volts_double::ch2::vout_double = " << voltage_structure.Ch2.vout_double << endl;
    cout << "volts_double::ch3::vout_double = " << voltage_structure.Ch3.vout_double << endl;
    cout << "volts_double::ch4::vout_double = " << voltage_structure.Ch4.vout_double << endl;
    cout << "volts_double::ch5::vout_double = " << voltage_structure.Ch5.vout_double << endl;
    cout << "volts_double::ch0::vout_min_double = " << voltage_structure.Ch0.vout_min_double << endl;
    cout << "volts_double::ch1::vout_min_double = " << voltage_structure.Ch1.vout_min_double << endl;
    cout << "volts_double::ch2::vout_min_double = " << voltage_structure.Ch2.vout_min_double << endl;
    cout << "volts_double::ch3::vout_min_double = " << voltage_structure.Ch3.vout_min_double << endl;
    cout << "volts_double::ch4::vout_min_double = " << voltage_structure.Ch4.vout_min_double << endl;
    cout << "volts_double::ch5::vout_min_double = " << voltage_structure.Ch5.vout_min_double << endl;
    cout << "volts_double::ch0::vout_peak_double = " << voltage_structure.Ch0.vout_peak_double << endl;
    cout << "volts_double::ch1::vout_peak_double = " << voltage_structure.Ch1.vout_peak_double << endl;
    cout << "volts_double::ch2::vout_peak_double = " << voltage_structure.Ch2.vout_peak_double << endl;
    cout << "volts_double::ch3::vout_peak_double = " << voltage_structure.Ch3.vout_peak_double << endl;
    cout << "volts_double::ch4::vout_peak_double = " << voltage_structure.Ch4.vout_peak_double << endl;
    cout << "volts_double::ch5::vout_peak_double = " << voltage_structure.Ch5.vout_peak_double << endl;

    status = fan_ctrl->program_MAX31785(EMU);
    if(status != 0)
    {
        cout << "Something went wrong when programming the program_MAX31785" << endl;
    }
    else
    {
        cout << "program_MAX31785 worked" << endl;
    }

    // I believe by calling EMU->exit_device() it currently calls
    // hid_exit() in the hidapi which internally seems to delete itself.
    // Calling delete EMU causes a double free or corruption
    EMU->exit_device();
    delete fan_ctrl;
    return 0;
}
