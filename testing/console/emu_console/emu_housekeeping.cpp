#include <stdlib.h>

#include <iostream>
#include <iomanip>

#include <stdint.h>
#include <unistd.h>

/// need for sleep functionality
//#include <Windows.h>

//#include "../../../include/cp2112_hidapi.h"
//#include "../../../include/hidapi.h"
#include "cp2112_hidapi.h"
#include "hidapi.h"
#include "maxim_ic_lib.h"

// If this is defined the script will print the raw values to console without 
// interpertation or unit conversion
#define PRINT_RAW


typedef struct emu_housekeeping_t
{
    double_t A5_Vin;
    double_t D5_Vin;
    double_t D3_Vin;
    double_t D2_Vin;
    double_t A5_Vout;
    double_t D5_Vout;
    double_t D3_Vout;
    double_t D2_Vout;
    double_t A5_Iout;
    double_t D5_Iout;
    double_t D3_Iout;
    double_t D2_Iout;
    double_t local_3p3_I;
    double_t local_5p0_I;
    double_t local_9p0_I;
    double_t local_fan_I;
} *Pemu_housekeeping_t;

using namespace std;
//int main(int argc, char *argv[])
int main()
{

    // Buffer to hold information being sent on the SMBus
    uint8 buffer[255] = {0x00};
    uint8 bytesRxed = 0;
    uint8 temp = 0;
    double dTemp = 0.0;
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

    struct emu_housekeeping_t emu_hskp;

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

    status = fan_ctrl->get_Temps(EMU, &temps_double, &temps_raw);
    #ifdef PRINT_RAW
        cout << "temps_double::int = " << temps_double.Int << "C" << endl;
        cout << "temps_double::ch0 = " << temps_double.Ch0 << "C" << endl;
        cout << "temps_double::ch1 = " << temps_double.Ch1 << "C" << endl;
        cout << "temps_double::D00 = " << temps_double.D00 << "C" << endl;
        cout << "temps_double::D01 = " << temps_double.D01 << "C" << endl;
        cout << "temps_double::D02 = " << temps_double.D02 << "C" << endl;
        cout << "temps_double::D03 = " << temps_double.D03 << "C" << endl;
    #endif
    cout << "___EMU Temperatures reported in Celsius___" << endl;
    cout << "    Fan Controller Internal : " << temps_double.Int << " C" << endl;
    cout << "           Local Regulators : " << temps_double.Ch0 << " C" << endl;
    cout << "   Backplane MOSFET Control : " << temps_double.Ch1 << " C" << endl;
    cout << "Upper Right Power Regulator : " << temps_double.D00 << " C" << endl;
    cout << " Upper Left Power Regulator : " << temps_double.D01 << " C" << endl;
    cout << "Lower Right Power Regulator : " << temps_double.D02 << " C" << endl;
    cout << " Lower Left Power Regulator : " << temps_double.D03 << " C" << endl;
    cout << endl;

    status = fan_ctrl->get_RPM(EMU, &fanrpm_double, &fanrpm_raw);
    cout << "___EMU connected Fan RPM___" << endl;
    cout << "Plenum fan connection, most likely has no RPM to report" << endl;
    cout << "                 Plenum Fan : " << fanrpm_double.Ch0 << "RPM" << endl;
    cout << "     EMU Local Cooling fan0 : " << fanrpm_double.Ch1 << "RPM" << endl;
    cout << "     EMU Local Cooling fan1 : " << fanrpm_double.Ch2 << "RPM" << endl;
    cout << endl;

    status = fan_ctrl->get_Volt(EMU, &voltage_structure);
    cout << dec;
    #ifdef PRINT_RAW
        cout << "volts_double::ch2::vout_double = " << voltage_structure.Ch2.vout_double << "mV" << endl;
        cout << "volts_double::ch3::vout_double = " << voltage_structure.Ch3.vout_double << "mV" << endl;
        cout << "volts_double::ch4::vout_double = " << voltage_structure.Ch4.vout_double << "mV" << endl;
        cout << "volts_double::ch5::vout_double = " << voltage_structure.Ch5.vout_double << "mV" << endl;
        cout << "volts_double::ch2::vout_min_double = " << voltage_structure.Ch2.vout_min_double << "mV" << endl;
        cout << "volts_double::ch3::vout_min_double = " << voltage_structure.Ch3.vout_min_double << "mV" << endl;
        cout << "volts_double::ch4::vout_min_double = " << voltage_structure.Ch4.vout_min_double << "mV" << endl;
        cout << "volts_double::ch5::vout_min_double = " << voltage_structure.Ch5.vout_min_double << "mV" << endl;
        cout << "volts_double::ch2::vout_peak_double = " << voltage_structure.Ch2.vout_peak_double << "mV" << endl;
        cout << "volts_double::ch3::vout_peak_double = " << voltage_structure.Ch3.vout_peak_double << "mV" << endl;
        cout << "volts_double::ch4::vout_peak_double = " << voltage_structure.Ch4.vout_peak_double << "mV" << endl;
        cout << "volts_double::ch5::vout_peak_double = " << voltage_structure.Ch5.vout_peak_double << "mV" << endl;
    #endif
    // Convert local current sense to Amps, returned voltage is in millivolts (mV)
    // 1V = 1A of current on the current sense, just need to convert to Volts
    emu_hskp.local_3p3_I = voltage_structure.Ch4 / 1000;
    emu_hskp.local_5p0_I = voltage_structure.Ch3 / 1000 - emu_hskp.local_3p3_I;
    emu_hskp.local_9p0_I = voltage_structure.Ch2 / 1000 - emu_hskp.local_3p3_I - emu_hskp.local_5p0_I;
    emu_hskp.local_fan_I = voltage_structure.Ch5 / 1000;



    #ifdef PRINT_RAW
        cout << endl;
        cout << "///////////////////////////" << endl;
        cout << "Lattice Platform Manager Communication" << endl;
        cout << endl;
    #endif

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x09;
    buffer[1] = 0x10;
    status = EMU->i2c_write(0x54, 0x02, buffer);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x07;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    temp = (buffer[0] >> 4);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x08;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    dTemp = double((buffer[0] << 4) + temp)*2/1000;
    #ifdef PRINT_RAW
        cout << dec;
        cout << "Lattice VMON1 Voltage  : " << dTemp << "V" <<endl;
        cout << hex;
    #endif
    emu_hskp.A5_Vout = dTemp * 2


    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x09;
    buffer[1] = 0x11;
    status = EMU->i2c_write(0x54, 0x02, buffer);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x07;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    temp = (buffer[0] >> 4);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x08;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    dTemp = double((buffer[0] << 4) + temp)*2/1000;
    #ifdef PRINT_RAW
    cout << dec;
    cout << "Lattice VMON2 Voltage  : " << dTemp << "V" <<endl;
    cout << hex;
    #endif
    emu_hskp.D5_Vout = dTemp * 2

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x09;
    buffer[1] = 0x12;
    status = EMU->i2c_write(0x54, 0x02, buffer);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x07;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    temp = (buffer[0] >> 4);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x08;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    dTemp = double((buffer[0] << 4) + temp)*2/1000;
    #ifdef PRINT_RAW
    cout << dec;
    cout << "Lattice VMON3 Voltage  : " << dTemp << "V" <<endl;
    cout << hex;
    #endif
    emu_hskp.D3_Vout = dTemp * 2

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x09;
    buffer[1] = 0x13;
    status = EMU->i2c_write(0x54, 0x02, buffer);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x07;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    temp = (buffer[0] >> 4);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x08;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    dTemp = double((buffer[0] << 4) + temp)*2/1000;
    #ifdef PRINT_RAW
    cout << dec;
    cout << "Lattice VMON4 Voltage  : " << dTemp << "V" <<endl;
    cout << hex;
    #endif
    emu_hskp.D2_Vout = dTemp * 2

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x09;
    buffer[1] = 0x14;
    status = EMU->i2c_write(0x54, 0x02, buffer);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x07;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    temp = (buffer[0] >> 4);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x08;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    dTemp = double((buffer[0] << 4) + temp)*2/1000;
    #ifdef PRINT_RAW
        cout << dec;
        cout << "Lattice VMON5 Voltage  : " << dTemp << "V" <<endl;
        cout << hex;
    #endif
    emu_hskp.A5_Vin = dTemp * 3

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x09;
    buffer[1] = 0x15;
    status = EMU->i2c_write(0x54, 0x02, buffer);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x07;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    temp = (buffer[0] >> 4);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x08;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    dTemp = double((buffer[0] << 4) + temp)*2/1000;
    #ifdef PRINT_RAW
        cout << dec;
        cout << "Lattice VMON6 Voltage  : " << dTemp << "V" <<endl;
        cout << hex;
    #endif
    emu_hskp.D5_Vin = dTemp * 3

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x09;
    buffer[1] = 0x16;
    status = EMU->i2c_write(0x54, 0x02, buffer);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x07;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    temp = (buffer[0] >> 4);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x08;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    dTemp = double((buffer[0] << 4) + temp)*2/1000;
    #ifdef PRINT_RAW
        cout << dec;
        cout << "Lattice VMON7 Voltage  : " << dTemp << "V" <<endl;
        cout << hex;
    #endif
    emu_hskp.D3_Vin = dTemp * 3

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x09;
    buffer[1] = 0x17;
    status = EMU->i2c_write(0x54, 0x02, buffer);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x07;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    temp = (buffer[0] >> 4);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x08;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    dTemp = double((buffer[0] << 4) + temp)*2/1000;
    #ifdef PRINT_RAW
        cout << dec;
        cout << "Lattice VMON8 Voltage  : " << dTemp << "V" <<endl;
        cout << hex;
    #endif
    emu_hskp.D2_Vin = dTemp * 3

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x09;
    buffer[1] = 0x18;
    status = EMU->i2c_write(0x54, 0x02, buffer);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x07;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    temp = (buffer[0] >> 4);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x08;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    dTemp = double((buffer[0] << 4) + temp)*2/1000;
    #ifdef PRINT_RAW
        cout << dec;
        cout << "Lattice VMON9 Voltage  : " << dTemp << "V" <<endl;
        cout << hex;
    #endif
    emu_hskp.A5_Iout = dTemp * 10/3

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x09;
    buffer[1] = 0x19;
    status = EMU->i2c_write(0x54, 0x02, buffer);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x07;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    temp = (buffer[0] >> 4);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x08;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    dTemp = double((buffer[0] << 4) + temp)*2/1000;
    #ifdef PRINT_RAW
        cout << dec;
        cout << "Lattice VMON10 Voltage  : " << dTemp << "V" <<endl;
        cout << hex;
    #endif
    emu_hskp.D5_Iout = dTemp * 10/3

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x09;
    buffer[1] = 0x1A;
    status = EMU->i2c_write(0x54, 0x02, buffer);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x07;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    temp = (buffer[0] >> 4);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x08;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    dTemp = double((buffer[0] << 4) + temp)*2/1000;
    #ifdef PRINT_RAW
        cout << dec;
        cout << "Lattice VMON11 Voltage  : " << dTemp << "V" <<endl;
        cout << hex;
    #endif
    emu_hskp.D3_Iout = dTemp * 10/3

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x09;
    buffer[1] = 0x1B;
    status = EMU->i2c_write(0x54, 0x02, buffer);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x07;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    temp = (buffer[0] >> 4);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x08;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    dTemp = double((buffer[0] << 4) + temp)*2/1000;
    #ifdef PRINT_RAW
        cout << dec;
        cout << "Lattice VMON12 Voltage  : " << dTemp << "V" <<endl;
        cout << hex;
    #endif
    emu_hskp.D2_Iout = dTemp * 10/3

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x09;
    buffer[1] = 0x1C;
    status = EMU->i2c_write(0x54, 0x02, buffer);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x07;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    temp = (buffer[0] >> 4);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x08;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);

    dTemp = double((buffer[0] << 4) + temp)*2/1000;
    #ifdef PRINT_RAW
        cout << dec;
        cout << "Lattice PVCCA Voltage  : " << dTemp << "V" <<endl;
        cout << hex;
    #endif

    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x09;
    buffer[1] = 0x1D;
    status = EMU->i2c_write(0x54, 0x02, buffer);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x07;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    temp = (buffer[0] >> 4);
    memset((void*) &buffer[0], 0x00, sizeof(buffer));
    buffer[0] = 0x08;
    status = EMU->i2c_write_read(0x54, 0x01, 0x01, &bytesRxed, buffer);
    dTemp = double((buffer[0] << 4) + temp)*2/1000;
    #ifdef PRINT_RAW
        cout << dec;
        cout << "Lattice PVCCINP Voltage  : " << dTemp << "V" <<endl;
        cout << hex;
    #endif

    cout << "___EMU Power Rail Status___" << endl;
    cout << " Power Rail A5 :  Vin = " <<  emu_hskp.A5_Vin << "V" << "\t";
                    cout << " Vout = " << emu_hskp.A5_Vout << "V" << "\t";
                    cout << " Iout = " << emu_hskp.A5_Iout << "A" << "\t";
                    cout << " Pout = " << emu_hskp.A5_Vout * emu_hskp.A5_Iout << "W" << endl;
    cout << " Power Rail D5 :  Vin = " <<  emu_hskp.D5_Vin << "V" << "\t";
                    cout << " Vout = " << emu_hskp.D5_Vout << "V" << "\t";
                    cout << " Iout = " << emu_hskp.D5_Iout << "A" << "\t";
                    cout << " Pout = " << emu_hskp.D5_Vout * emu_hskp.D5_Iout << "W" << endl;
    cout << " Power Rail D3 :  Vin = " <<  emu_hskp.D3_Vin << "V" << "\t";
                    cout << " Vout = " << emu_hskp.D3_Vout << "V" << "\t";
                    cout << " Iout = " << emu_hskp.D3_Iout << "A" << "\t";
                    cout << " Pout = " << emu_hskp.D3_Vout * emu_hskp.D3_Iout << "W" << endl;
    cout << " Power Rail D2 :  Vin = " <<  emu_hskp.D2_Vin << "V" << "\t";
                    cout << " Vout = " << emu_hskp.D2_Vout << "V" << "\t";
                    cout << " Iout = " << emu_hskp.D2_Iout << "A" << "\t";
                    cout << " Pout = " << emu_hskp.D2_Vout * emu_hskp.D2_Iout << "W" << endl;
    cout << endl;
    cout << "___EMU Local Power Status___" << endl;
    cout << " Sadly no voltage readout on local power supplies" << endl;
    cout << "Local 9V Vctrl :  Vin = " <<  emu_hskp.D5_Vin << "V" << "\t";
                    cout << " Vout = " << 9.00 << "V" << "\t";
                    cout << " Iout = " << emu_hskp.local_9p0_I << "A" << "\t";
                    cout << " Pout = " << 9.00 * emu_hskp.local_9p0_Iout << "W" << endl;
    cout << "      Local 5V :  Vin = " <<  9.00 << "V" << "\t";
                    cout << " Vout = " << 5.00 << "V" << "\t";
                    cout << " Iout = " << emu_hskp.local_5p0_I << "A" << "\t";
                    cout << " Pout = " << 5.00 * emu_hskp.local_5p0_Iout << "W" << endl;
    cout << "    Local 3.3V :  Vin = " <<  5.00 << "V" << "\t";
                    cout << " Vout = " << 3.30 << "V" << "\t";
                    cout << " Iout = " << emu_hskp.local_3p3_I << "A" << "\t";
                    cout << " Pout = " << 3.30 * emu_hskp.local_3p3_Iout << "W" << endl;
    cout << "     Local Fan :  Vin = " << emu_hskp.D5_Vin << "V" << "\t";
                    cout << " Iout = " << emu_hskp.local_fan_I << "A" << "\t";
                    cout << " Pout = " << 3.30 * emu_hskp.local_fan_I << "W" << endl;

    // I believe by calling EMU->exit_device() it currently calls
    // hid_exit() in the hidapi which internally seems to delete itself.
    // Calling delete EMU causes a double free or corruption
    EMU->exit_device();
    delete fan_ctrl;
    return 0;
}
