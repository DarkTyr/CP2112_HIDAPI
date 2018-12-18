#ifndef LATTICELIB_H
#define LATTICELIB_H

#include <QObject>
#include <QString>
#include <QVector>
#include <Windows.h>
#include <stdint.h>

//! Headers for the FTDI driver and the libMPSSE_API
#include "../FTDI_Driver/Windows/ftd2xx.h"
#include "../libMPSSE_API/include/libMPSSE_i2c.h"


//This Libarary is to be used with the LPTM10-12107 208-ball ftBGA

//Register Addresses
//Note that each register is only 1 Byte
//
#define VMON_STATUS0    0x00;   //R
#define VMON_STATUS1    0x01;   //R
#define VMON_STATUS2    0x02;   //R
#define OUTPUT_STATUS0  0x03;   //R
#define OUTPUT_STATUS1  0x04;   //R
#define OUTPUT_STATUS2  0x05;   //R
#define INPUT_STATUS    0x06;   //R
#define ADC_VALUE_LOW   0x07;   //R
#define ADC_VALUE_HIGH  0x08;   //R
#define ADC_MUX         0x09;   //RW
#define UES_BYTE0       0x0A;   //R
#define UES_BYTE1       0x0B;   //R
#define UES_BYTE2       0x0C;   //R
#define UES_BYTE3       0x0D;   //R
#define GP_OUTPUT1      0x0E;   //RW
#define GP_OUTPUT2      0x0F;   //RW
#define GP_OUTPUT3      0x10;   //RW
#define INPUT_VALUE     0x11;   //RW
#define CPLD_RESET      0x12;   //W
#define TRIM1_TRIM      0x13;   //RW
#define TRIM2_TRIM      0x14;   //RW
#define TRIM3_TRIM      0x15;   //RW
#define TRIM4_TRIM      0x16;   //RW
#define TRIM5_TRIM      0x17;   //RW
#define TRIM6_TRIM      0x18;   //RW
#define TRIM7_TRIM      0x19;   //RW
#define TRIM8_TRIM      0x1A;   //RW


//Project Specific Definitions
//
//
//ADC Mux definitions coresponding to each power rail
//The atenuation bit is already taken into account
//
#define ADC_MUX_RAIL_IN_A5  0x14;
#define ADC_MUX_RAIL_IN_D5  0x15;
#define ADC_MUX_RAIL_IN_D3  0x16;
#define ADC_MUX_RAIL_IN_D2  0x17;
#define ADC_MUX_RAIL_OUT_A5 0x10;
#define ADC_MUX_RAIL_OUT_D5 0x11;
#define ADC_MUX_RAIL_OUT_D3 0x02;
#define ADC_MUX_RAIL_OUT_D2 0x03;
#define ADC_MUX_RAIL_CUR_A5 0x18;
#define ADC_MUX_RAIL_CUR_D5 0x19;
#define ADC_MUX_RAIL_CUR_D3 0x1A;
#define ADC_MUX_RAIL_CUR_D2 0x1B;
#define ADC_MUX_PVCCA       0x1C;
#define ADC_MUX_PVCCINP     0x1D;

typedef struct LPTM_Monitor_Data
{
    double A5_in;
    double D5_in;
    double D3_in;
    double D2_in;
    double A5_out;
    double D5_out;
    double D3_out;
    double D2_out;
    double A5_current;
    double D5_current;
    double D3_current;
    double D2_current;

    double PVCCA;
    double PVCCINP;

} *PLPTM_Monitor_Data;


class Latticelib : public QObject
{
    Q_OBJECT

public:

    explicit Latticelib(const uint8 &i2cAddress, QObject *parent = 0);

    ~Latticelib();

    QString deviceReset();

    void setHandle(FT_HANDLE Handle);


signals:

    void signalSendData(LPTM_Monitor_Data data);

public slots:

    void slotGetData();

private:

    void voltageIn();

    void voltageOut();

    void current();

    FT_STATUS status;               // status variable from the FTDI driver
    FT_HANDLE handle;
    QString stringReturn;           // Stores the return result for the functions
    uint8 i2caddress;               // Stores the I2C address from the constructor
    uint8 i2cDataSend[16];          // Do not need a full size buffer because only one byte of data is ever moving (each register is only one byte of data)
    uint8 i2cDataReceive[16];       // Initialize a data buffer and set to all Zeros
    uint32 i2cNumBytesToTx;			// Initialize a counter for the buffer and set to Zero
    uint32 i2cNumBytesTxd;			// Initialize another counter for the number of bytes actually sent and set to Zero
    uint32 i2cNumBytesToRx;			// Initialize a counter for the recieve buffer and set to Zero
    uint32 i2cNumBytesRxd;			// Initialize another counter for the number of bytes actually recieved and set to Zero
    LPTM_Monitor_Data monitorData;  // Variable that stores
    bool doneBit;
};

#endif // LATTICELIB_H
