#ifndef MAXIM_IC_LIB
#define MAXIM_IC_LIB

//#include <Windows.h>
#include <bits/stdc++.h>
#include <stdint.h>
#include <iostream>
#include "../../../include/cp2112_hidapi.h"


#if defined(MAXIM_IC_LIB_LIBRARY)
#  define MAXIM_IC_LIBSHARED_EXPORT //Q_DECL_EXPORT
#else
#  define MAXIM_IC_LIBSHARED_EXPORT //Q_DECL_IMPORT
#endif

using namespace std;

//Definitions for Pages
#define PAGE_FAN_0      0x00;
#define PAGE_FAN_1      0x01;
#define PAGE_FAN_2      0x02;
#define PAGE_FAN_3      0x03;
#define PAGE_FAN_4      0x04;
#define PAGE_FAN_5      0x05;
#define PAGE_TEMP_0     0x06;
#define PAGE_TEMP_1     0x07;
#define PAGE_TEMP_2     0x08;
#define PAGE_TEMP_3     0x09;
#define PAGE_TEMP_4     0x0A;
#define PAGE_TEMP_5     0x0B;
#define PAGE_TEMP_INT   0x0C;
#define PAGE_I2C_0      0x0D;
#define PAGE_I2C_1      0x0E;
#define PAGE_I2C_2      0x0F;
#define PAGE_I2C_3      0x10;
#define PAGE_VOLT_0     0x11;
#define PAGE_VOLT_1     0x12;
#define PAGE_VOLT_2     0x13;
#define PAGE_VOLT_3     0x14;
#define PAGE_VOLT_4     0x15;
#define PAGE_VOLT_5     0x16;
#define PAGE_ALL        0xFF;

//Definitions for commands
#define CMD_PAGE                    0x00;   //#bytes = 1
#define CMD_CLEAR_FAULTS            0x03;   //#bytes = 0
#define CMD_WRITE_PROTECT           0x10;   //#bytes = 1
#define CMD_STORE_DEFUALT_ALL       0x11;   //#bytes = 0
#define CMD_RESTORE_DEFAULT_ALL     0x12;   //#bytes = 0
#define CMD_CAPABILITY              0x19;   //#bytes = 1
#define CMD_VOUT_MODE               0x20;   //#bytes = 1
#define CMD_VOUT_SCALE_MONITOR      0x2A;   //#bytes = 2
#define CMD_FAN_CONFIG_1_2          0x3A;   //#bytes = 1
#define CMD_FAN_COMMAND_1           0x3B;   //#bytes = 2
#define CMD_VOUT_OV_FAULT_LIMIT     0x40;   //#bytes = 2
#define CMD_VOUT_OV_WARN_LIMIT      0x42;   //#bytes = 2
#define CMD_VOUT_UV_WARN_LIMIT      0x43;   //#bytes = 2
#define CMD_VOUT_UV_FAULT_LIMIT     0x44;   //#bytes = 2
#define CMD_OT_FAULT_LIMIT          0x4F;   //#bytes = 2
#define CMD_OT_WARN_LIMIT           0x51;   //#bytes = 2
#define CMD_STATUS_BYTE             0x78;   //#bytes = 1
#define CMD_STATUS_WORD             0x79;   //#bytes = 2
#define CMD_STATUS_VOUT             0x7A;   //#bytes = 1
#define CMD_STATUS_CML              0x7E;   //#bytes = 1
#define CMD_STATUS_MFR_SPECIFIC     0x80;   //#bytes = 1
#define CMD_STATUS_FANS_1_2         0x81;   //#bytes = 1
#define CMD_READ_VOUT               0x8B;   //#bytes = 2
#define CMD_READ_TEMPERATURE_1      0x8D;   //#bytes = 2
#define CMD_READ_FAN_SPEED_1        0x90;   //#bytes = 2
#define CMD_PMBUS_REVISION          0x98;   //#bytes = 1 result = 0x11
#define CMD_MFR_ID                  0x99;   //#bytes = 1 result = 0x4d
#define CMD_MFR_MODEL               0x9A;   //#bytes = 1 result = 0x53
#define CMD_MFR_REVISION            0x9B;   //#bytes = 2 result = 0x3030
#define CMD_MFR_LOCATION            0x9C;   //#bytes = 8 result = 0x3130313031303130
#define CMD_MFR_DATE                0x9D;   //#bytes = 8 result = 0x3130313031303130
#define CMD_MRF_SERIAL              0x9E;   //#bytes = 8 result = 0x3130313031303130
#define CMD_MFR_MODE                0xD1;   //#bytes = 2
#define CMD_MFR_VOUT_PEAK           0xD4;   //#bytes = 2
#define CMD_MFR_TEMPERATURE_PEAK    0xD6;   //#bytes = 2
#define CMD_MFR_VOUT_MIN            0xD7;   //#bytes = 2
#define CMD_MFR_FAULT_RESPONSE      0xD9;   //#bytes = 1
#define CMD_MFR_NV_FAULT_LOG        0xDC;   //#bytes = 255
#define CMD_MFR_TIME_COUNT          0xDD;   //#bytes = 4
#define CMD_MFR_TEMP_SENSOR_CONFIG  0xF0;   //#bytes = 2
#define CMD_MFR_FAN_CONFIG          0xF1;   //#bytes = 2
#define CMD_MFR_FAN_LUT             0xF2;   //#bytes = 32
#define CMD_MFR_READ_FAN_PWM        0xF3;   //#bytes = 2
#define CMD_MFR_FAN_FAULT_LIMIT     0xF5;   //#bytes = 2
#define CMD_MFR_FAN_WARN_LIMIT      0xF6;   //#bytes = 2
#define CMD_MFR_FAN_RUN_TIME        0xF7;   //#bytes = 2
#define CMD_MFR_FAN_PWM_AVG         0xF8;   //#bytes = 2
#define CMD_MFR_FAN_PWM2RPM         0xF9;   //#bytes = 8


namespace Maxim_IC
{
        typedef struct TEMPS_RAW
        {
            uint16_t Int;
            uint16_t Ch0;
            uint16_t Ch1;
            uint16_t Ch2;
            uint16_t Ch3;
            uint16_t Ch4;
            uint16_t Ch5;
            uint16_t D00;
            uint16_t D01;
            uint16_t D02;
            uint16_t D03;
            uint16_t Warn;
            uint16_t Fault;
        } *PTemps_Raw;

        typedef struct TEMPS_DOUBLE
        {
            double_t Int;
            double_t Ch0;
            double_t Ch1;
            double_t Ch2;
            double_t Ch3;
            double_t Ch4;
            double_t Ch5;
            double_t D00;
            double_t D01;
            double_t D02;
            double_t D03;
            double_t Warn;
            double_t Fault;
        } *PTemps_Double;

        typedef struct RPM_RAW
        {
            uint16_t Ch0;
            uint16_t Ch1;
            uint16_t Ch2;
            uint16_t Ch3;
            uint16_t Ch4;
            uint16_t Ch5;

        } *PRPM_Raw;

        typedef struct RPM_DOUBLE
        {
            double_t Ch0;
            double_t Ch1;
            double_t Ch2;
            double_t Ch3;
            double_t Ch4;
            double_t Ch5;
        } *PRPM_Double;

        typedef struct VOLTAGE_t
        {
            double_t vout_double;
            uint16_t vout_raw;
            double_t vout_peak_double;
            uint16_t vout_peak_raw;
            double_t vout_min_double;
            uint16_t vout_min_raw;
        } *PVOLTAGE_t;

        typedef struct VOLTAGE_STRUC
        {
            struct VOLTAGE_t Ch0;
            struct VOLTAGE_t Ch1;
            struct VOLTAGE_t Ch2;
            struct VOLTAGE_t Ch3;
            struct VOLTAGE_t Ch4;
            struct VOLTAGE_t Ch5;
        } *PVOLTAGE_STRUC;

        // typedef struct DS7505_Data
        // {
        //     uint8_t  D00_address;         //device address
        //     uint8_t  D00_config;          //Configuration of DS7505
        //     uint16_t D00_raw_temp;        //Raw bit value recieved from DS7505
        //     double_t D00_double_temp;     //Converted value from DS7505
        //     uint16_t D00_raw_HYST;        //Hystoretic temp raw value
        //     double_t D00_double_HYST;     //Hystoretic temp in decimal value
        //     uint16_t D00_raw_tos;         //Thermostat trip point hex value
        //     double_t D00_double_tos;      //Thermostat Trip poing decimal

        //     uint8_t  D01_address;
        //     uint8_t  D01_config;
        //     uint16_t D01_raw_temp;
        //     double_t D01_double_temp;
        //     uint16_t D01_raw_HYST;
        //     double_t D01_double_HYST;
        //     uint16_t D01_raw_tos;
        //     double_t D01_double_tos;

        //     uint8_t  D02_address;
        //     uint8_t  D02_config;
        //     uint16_t D02_raw_temp;
        //     double_t D02_double_temp;
        //     uint16_t D02_raw_HYST;
        //     double_t D02_double_HYST;
        //     uint16_t D02_raw_tos;
        //     double_t D02_double_tos;

        //     uint8_t  D03_address;
        //     uint8_t  D03_config;
        //     uint16_t D03_raw_temp;
        //     double_t D03_double_temp;
        //     uint16_t D03_raw_HYST;
        //     double_t D03_double_HYST;
        //     uint16_t D03_raw_tos;
        //     double_t D03_double_tos;

        //     double_t DS7505_Tos;          //Tos setpoint that is read to set the setpoint
        //     double_t DS7505_Hyst;         //Hyst setpoint that is read to set the setpoint

        // } *PDS7505_Data;

    class MAXIM_IC_LIBSHARED_EXPORT MAX31785
    {
    public:

        static int program_MAX31785(CP2112_HIDAPI *handle);

        static int program_Commit(CP2112_HIDAPI *handle);

        static int fan_On(CP2112_HIDAPI *handle);

        static int fan_Off(CP2112_HIDAPI *handle);

        static int Get_Temps(TEMPS_DOUBLE &Temps_Double, TEMPS_RAW &Temps_Raw);

        static int get_Temps(CP2112_HIDAPI *handle, TEMPS_DOUBLE *Temps_Double, TEMPS_RAW *Temps_Raw);

        static int get_RPM(CP2112_HIDAPI *handle, RPM_DOUBLE *RPM_Double, RPM_RAW *RPM_Raw);

        static int get_Volt(CP2112_HIDAPI *handle, VOLTAGE_STRUC *Voltage_structure);

    private:

        static int program_Fan_Channel0(CP2112_HIDAPI *handle);

        static int program_Fan_Channel1(CP2112_HIDAPI *handle);

        static int program_Fan_Channel2(CP2112_HIDAPI *handle);

        static int program_Fan_Channel3(CP2112_HIDAPI *handle);

        static int program_Fan_Channel4(CP2112_HIDAPI *handle);

        static int program_Fan_Channel5(CP2112_HIDAPI *handle);

        static int program_Temp_Internal(CP2112_HIDAPI *handle);

        static int program_Temp_Sensor0(CP2112_HIDAPI *handle);

        static int program_Temp_Sensor1(CP2112_HIDAPI *handle);

        static int program_Temp_Sensor2(CP2112_HIDAPI *handle);

        static int program_Temp_Sensor3(CP2112_HIDAPI *handle);

        static int program_Temp_Sensor4(CP2112_HIDAPI *handle);

        static int program_Temp_Sensor5(CP2112_HIDAPI *handle);

        static int program_Temp_I2C1(CP2112_HIDAPI *handle);

        static int program_Temp_I2C2(CP2112_HIDAPI *handle);

        static int program_Temp_I2C3(CP2112_HIDAPI *handle);

        static int program_Temp_I2C4(CP2112_HIDAPI *handle);

        static int program_Voltage0(CP2112_HIDAPI *handle);

        static int program_Voltage1(CP2112_HIDAPI *handle);

        static int program_Voltage2(CP2112_HIDAPI *handle);

        static int program_Voltage3(CP2112_HIDAPI *handle);

        static int program_Voltage4(CP2112_HIDAPI *handle);

        static int program_Voltage5(CP2112_HIDAPI *handle);

    };

    // class MAXIM_IC_LIBSHARED_EXPORT DS7505
    // {
    // public:

    //     static int get_Data(CP2112_HIDAPI *handle, DS7505_Data &data, vector<uint8_t> &i2c_address);

    //     static int find_DS7505_Devices(CP2112_HIDAPI *handle, vector<uint8_t> &i2c_address);

    //     static int Configure_DS7505(CP2112_HIDAPI *handle, DS7505_Data &data, vector<uint8_t> &i2c_address);

    //     static int setTripPoints(CP2112_HIDAPI *handle, DS7505_Data &data, vector<uint8_t> &i2c_address);

    // };
}

#endif // MAXIM_IC_LIB
