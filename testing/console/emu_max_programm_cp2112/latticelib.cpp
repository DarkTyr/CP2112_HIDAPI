/*! \mainpage
  *
  *
  * \section intro_sec Introduction
  *     This is a library that is to be used to interact with the Lattice LPTM10-12107
  * \section dependencies_sect Dependencies
  *     This library depends on the FTDI driver and the libMPSSE abstraction layer. Both can be aquired from
  *     the FTDI main website
  *
  *
  *
  *
  *
  *
  *
  *
  *
  */

#include "latticelib.h"


//! Contructor for the Lattice library.
Latticelib::Latticelib(const uint8 &i2cAddress, QObject *parent) : QObject(parent)
{
    i2caddress = i2cAddress;
    memset((void*) &i2cDataSend[0], 0x00, sizeof(i2cDataSend));
    memset((void*) &i2cDataReceive[0], 0x00, sizeof(i2cDataReceive));
    i2cNumBytesToTx = 0;
    i2cNumBytesTxd = 0;
    i2cNumBytesToRx = 0;
    i2cNumBytesRxd = 0;
    doneBit = false;
}

//! setHandle allows the ability to set the FT_HANDLE after the latticelib object has been created.
void Latticelib::setHandle (FT_HANDLE Handle)
{
    handle = Handle;
}

//! trigger to poll all the data from the LPTM-10-12107 chip
void Latticelib::slotGetData()
{
    voltageIn();
    voltageOut();
    current();
    signalSendData(monitorData);
}

//! Once all data has been gather by the slotGetData() this emits the data structure containing all of the data.
void Latticelib::signalSendData(LPTM_Monitor_Data data)
{
    emit data;
}

//! this soft reset of the LPTM10-12107.
QString Latticelib::deviceReset()
{
    i2cNumBytesToTx = 0;
    i2cDataSend[i2cNumBytesToTx++] = CPLD_RESET;
    status = I2C_DeviceWrite(handle, i2caddress, i2cNumBytesToTx, i2cDataSend,&i2cNumBytesTxd,
                             I2C_TRANSFER_OPTIONS_START_BIT |
                             I2C_TRANSFER_OPTIONS_STOP_BIT |
                             I2C_TRANSFER_OPTIONS_BREAK_ON_NACK);
    if (status = FT_OK)
    {
        stringReturn = "Good";
    }
    else
    {
        stringReturn = "I2C write to soft reset the CPLD was not good.";
    }
    return stringReturn;
}

//! Reads all of the VMON rails that relate to the Voltage inputs into the power supply and converts all data to double.
void Latticelib::voltageIn()
{
    /* The data being stored into the structure includes all hardware factors
      result from LPTM is givin in units which equal 2 millivolts per unit (multiply by 2)
      which makes it millivolts (divide by 1000 to get volts) and then multiply by 3 for
      resistor divider to drop input voltage down to input range.
      */

    //Get the Rail A5 Input voltage and convert to double and save in data structure
    doneBit = false;
    i2cNumBytesToTx = 0;
    i2cDataSend[i2cNumBytesToTx++] = ADC_MUX;
    i2cDataSend[i2cNumBytesToTx++] = ADC_MUX_RAIL_IN_A5;
    status = I2C_DeviceWrite(handle, i2caddress, i2cNumBytesToTx, i2cDataSend,&i2cNumBytesTxd,
                             I2C_TRANSFER_OPTIONS_START_BIT |
                             I2C_TRANSFER_OPTIONS_BREAK_ON_NACK |
                             I2C_TRANSFER_OPTIONS_STOP_BIT);
    while (doneBit = 0)
    {
        i2cNumBytesToTx = 0;
        i2cDataSend[i2cNumBytesToTx++] = ADC_VALUE_LOW;
        status = I2C_DeviceWrite(handle, i2caddress, i2cNumBytesToTx, i2cDataSend,&i2cNumBytesTxd,
                                 I2C_TRANSFER_OPTIONS_START_BIT |
                                 I2C_TRANSFER_OPTIONS_BREAK_ON_NACK |
                                 I2C_TRANSFER_OPTIONS_STOP_BIT);
        i2cNumBytesToRx = 1;
        status = I2C_DeviceRead(handle, i2caddress, i2cNumBytesToRx, i2cDataReceive,&i2cNumBytesRxd,
                                I2C_TRANSFER_OPTIONS_START_BIT |
                                I2C_TRANSFER_OPTIONS_BREAK_ON_NACK |
                                I2C_TRANSFER_OPTIONS_STOP_BIT);
        doneBit = (bool)(i2cDataReceive[1] & 0x01);
    }

    i2cDataReceive[2] = i2cDataReceive[1];

    i2cNumBytesToTx = 0;
    i2cDataSend[i2cNumBytesToTx++] = ADC_VALUE_HIGH;
    status = I2C_DeviceWrite(handle, i2caddress, i2cNumBytesToTx, i2cDataSend,&i2cNumBytesTxd,
                             I2C_TRANSFER_OPTIONS_START_BIT |
                             I2C_TRANSFER_OPTIONS_BREAK_ON_NACK |
                             I2C_TRANSFER_OPTIONS_STOP_BIT);
    i2cNumBytesToRx = 1;
    status = I2C_DeviceRead(handle, i2caddress, i2cNumBytesToRx, i2cDataReceive,&i2cNumBytesRxd,
                            I2C_TRANSFER_OPTIONS_START_BIT |
                            I2C_TRANSFER_OPTIONS_BREAK_ON_NACK |
                            I2C_TRANSFER_OPTIONS_STOP_BIT);


    monitorData.A5_in = ((double) (((i2cDataReceive[1] <<4) + (i2cDataReceive[2] >> 4)) & 0x0FFF))* 2 * 3 / 1000;

    //Get the Rail D5 Input voltage and convert to double and save in data structure
    doneBit = false;
    i2cNumBytesToTx = 0;
    i2cDataSend[i2cNumBytesToTx++] = ADC_MUX;
    i2cDataSend[i2cNumBytesToTx++] = ADC_MUX_RAIL_IN_D5;
    status = I2C_DeviceWrite(handle, i2caddress, i2cNumBytesToTx, i2cDataSend,&i2cNumBytesTxd,
                             I2C_TRANSFER_OPTIONS_START_BIT |
                             I2C_TRANSFER_OPTIONS_BREAK_ON_NACK |
                             I2C_TRANSFER_OPTIONS_STOP_BIT);
    while (doneBit = 0)
    {
        i2cNumBytesToTx = 0;
        i2cDataSend[i2cNumBytesToTx++] = ADC_VALUE_LOW;
        status = I2C_DeviceWrite(handle, i2caddress, i2cNumBytesToTx, i2cDataSend,&i2cNumBytesTxd,
                                 I2C_TRANSFER_OPTIONS_START_BIT |
                                 I2C_TRANSFER_OPTIONS_BREAK_ON_NACK |
                                 I2C_TRANSFER_OPTIONS_STOP_BIT);
        i2cNumBytesToRx = 1;
        status = I2C_DeviceRead(handle, i2caddress, i2cNumBytesToRx, i2cDataReceive,&i2cNumBytesRxd,
                                I2C_TRANSFER_OPTIONS_START_BIT |
                                I2C_TRANSFER_OPTIONS_BREAK_ON_NACK |
                                I2C_TRANSFER_OPTIONS_STOP_BIT);
        doneBit = (bool)(i2cDataReceive[1] & 0x01);
    }

    i2cDataReceive[2] = i2cDataReceive[1];

    i2cNumBytesToTx = 0;
    i2cDataSend[i2cNumBytesToTx++] = ADC_VALUE_HIGH;
    status = I2C_DeviceWrite(handle, i2caddress, i2cNumBytesToTx, i2cDataSend,&i2cNumBytesTxd,
                             I2C_TRANSFER_OPTIONS_START_BIT |
                             I2C_TRANSFER_OPTIONS_BREAK_ON_NACK |
                             I2C_TRANSFER_OPTIONS_STOP_BIT);
    i2cNumBytesToRx = 1;
    status = I2C_DeviceRead(handle, i2caddress, i2cNumBytesToRx, i2cDataReceive,&i2cNumBytesRxd,
                            I2C_TRANSFER_OPTIONS_START_BIT |
                            I2C_TRANSFER_OPTIONS_BREAK_ON_NACK |
                            I2C_TRANSFER_OPTIONS_STOP_BIT);


    monitorData.D5_in = ((double) (((i2cDataReceive[1] <<4) + (i2cDataReceive[2] >> 4)) & 0x0FFF))* 2 * 3 / 1000;

    //Get the Rail D3 Input voltage and convert to double and save in data structure
    doneBit = false;
    i2cNumBytesToTx = 0;
    i2cDataSend[i2cNumBytesToTx++] = ADC_MUX;
    i2cDataSend[i2cNumBytesToTx++] = ADC_MUX_RAIL_IN_D3;
    status = I2C_DeviceWrite(handle, i2caddress, i2cNumBytesToTx, i2cDataSend,&i2cNumBytesTxd,
                             I2C_TRANSFER_OPTIONS_START_BIT |
                             I2C_TRANSFER_OPTIONS_BREAK_ON_NACK |
                             I2C_TRANSFER_OPTIONS_STOP_BIT);
    while (doneBit = 0)
    {
        i2cNumBytesToTx = 0;
        i2cDataSend[i2cNumBytesToTx++] = ADC_VALUE_LOW;
        status = I2C_DeviceWrite(handle, i2caddress, i2cNumBytesToTx, i2cDataSend,&i2cNumBytesTxd,
                                 I2C_TRANSFER_OPTIONS_START_BIT |
                                 I2C_TRANSFER_OPTIONS_BREAK_ON_NACK |
                                 I2C_TRANSFER_OPTIONS_STOP_BIT);
        i2cNumBytesToRx = 1;
        status = I2C_DeviceRead(handle, i2caddress, i2cNumBytesToRx, i2cDataReceive,&i2cNumBytesRxd,
                                I2C_TRANSFER_OPTIONS_START_BIT |
                                I2C_TRANSFER_OPTIONS_BREAK_ON_NACK |
                                I2C_TRANSFER_OPTIONS_STOP_BIT);
        doneBit = (bool)(i2cDataReceive[1] & 0x01);
    }

    i2cDataReceive[2] = i2cDataReceive[1];

    i2cNumBytesToTx = 0;
    i2cDataSend[i2cNumBytesToTx++] = ADC_VALUE_HIGH;
    status = I2C_DeviceWrite(handle, i2caddress, i2cNumBytesToTx, i2cDataSend,&i2cNumBytesTxd,
                             I2C_TRANSFER_OPTIONS_START_BIT |
                             I2C_TRANSFER_OPTIONS_BREAK_ON_NACK |
                             I2C_TRANSFER_OPTIONS_STOP_BIT);
    i2cNumBytesToRx = 1;
    status = I2C_DeviceRead(handle, i2caddress, i2cNumBytesToRx, i2cDataReceive,&i2cNumBytesRxd,
                            I2C_TRANSFER_OPTIONS_START_BIT |
                            I2C_TRANSFER_OPTIONS_BREAK_ON_NACK |
                            I2C_TRANSFER_OPTIONS_STOP_BIT);


    monitorData.D3_in = ((double) (((i2cDataReceive[1] <<4) + (i2cDataReceive[2] >> 4)) & 0x0FFF))* 2 * 3 / 1000;

    //Get the Rail D2 Input voltage and convert to double and save in data structure
    doneBit = false;
    i2cNumBytesToTx = 0;
    i2cDataSend[i2cNumBytesToTx++] = ADC_MUX;
    i2cDataSend[i2cNumBytesToTx++] = ADC_MUX_RAIL_IN_D2;
    status = I2C_DeviceWrite(handle, i2caddress, i2cNumBytesToTx, i2cDataSend,&i2cNumBytesTxd,
                             I2C_TRANSFER_OPTIONS_START_BIT |
                             I2C_TRANSFER_OPTIONS_BREAK_ON_NACK |
                             I2C_TRANSFER_OPTIONS_STOP_BIT);
    while (doneBit = 0)
    {
        i2cNumBytesToTx = 0;
        i2cDataSend[i2cNumBytesToTx++] = ADC_VALUE_LOW;
        status = I2C_DeviceWrite(handle, i2caddress, i2cNumBytesToTx, i2cDataSend,&i2cNumBytesTxd,
                                 I2C_TRANSFER_OPTIONS_START_BIT |
                                 I2C_TRANSFER_OPTIONS_BREAK_ON_NACK |
                                 I2C_TRANSFER_OPTIONS_STOP_BIT);
        i2cNumBytesToRx = 1;
        status = I2C_DeviceRead(handle, i2caddress, i2cNumBytesToRx, i2cDataReceive,&i2cNumBytesRxd,
                                I2C_TRANSFER_OPTIONS_START_BIT |
                                I2C_TRANSFER_OPTIONS_BREAK_ON_NACK |
                                I2C_TRANSFER_OPTIONS_STOP_BIT);
        doneBit = (bool)(i2cDataReceive[1] & 0x01);
    }

    i2cDataReceive[2] = i2cDataReceive[1];

    i2cNumBytesToTx = 0;
    i2cDataSend[i2cNumBytesToTx++] = ADC_VALUE_HIGH;
    status = I2C_DeviceWrite(handle, i2caddress, i2cNumBytesToTx, i2cDataSend,&i2cNumBytesTxd,
                             I2C_TRANSFER_OPTIONS_START_BIT |
                             I2C_TRANSFER_OPTIONS_BREAK_ON_NACK |
                             I2C_TRANSFER_OPTIONS_STOP_BIT);
    i2cNumBytesToRx = 1;
    status = I2C_DeviceRead(handle, i2caddress, i2cNumBytesToRx, i2cDataReceive,&i2cNumBytesRxd,
                            I2C_TRANSFER_OPTIONS_START_BIT |
                            I2C_TRANSFER_OPTIONS_BREAK_ON_NACK |
                            I2C_TRANSFER_OPTIONS_STOP_BIT);
    monitorData.D2_in = ((double) (((i2cDataReceive[1] <<4) + (i2cDataReceive[2] >> 4)) & 0x0FFF))* 2 * 3 / 1000;

}

//! Reads all of the VMON's related to the voltage outputs and converts the data to Double.
void Latticelib::voltageOut()
{
    /* The data being stored into the structure includes all hardware factors
      result from LPTM is givin in units which equal 2 millivolts per unit (multiply by 2)
      which makes it millivolts (divide by 1000 to get volts) and then multiply by
      */
}

//! Reads all of the VMON's related to current monitoring of the power supplly and converts them to double.
void Latticelib::current()
{
    /* The data being stored into the structure includes all hardware factors
      result from LPTM is givin in units which equal 2 millivolts per unit (multiply by 2)
      which makes it millivolts (divide by 1000 to get volts). This brings you to the input
      of the ADC. After that you must devide by 0.03 to take into account the 100 gain amplifier
      and 0.003 hom resistor.
      */
}
