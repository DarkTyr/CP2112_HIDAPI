/*
Notes on MAX31785 6 Channel Fan Controller:
pages
0-5 = PWM 0-5
6-11 = Remote thermal Diode 0-5
12 = Internal Temp sensor
13-16 = remote I2C Temperature sensor 0-3
255 =  Applies to all apllicaple pages
*/

#include "maxim_ic_lib.h"

namespace Maxim_IC
{

    int MAX31785::program_MAX31785(CP2112_HIDAPI *handle)
    {
        //initial programming for the MAX31785
        int status;
        uint8_t i2cAddress = 0xA4;      // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};   // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;   // Initialize a counter for the buffer and set to Zero
        uint32_t i2cNumBytesTxd = 0;    // Initialize another counter for the number of bytes actually sent and set to Zero
        //uint32_t i2cNumBytesToRx = 0; // Initialize a counter for the recieve buffer and set to Zero
        //uint32_t i2cNumBytesRxd = 0;  // Initialize another counter for the number of bytes actually recieved and set to Zero

        //Disbale Write Protection
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_WRITE_PROTECT;  //page command
        buffer[i2cNumBytesToTx++] = 0x00;               //Enable Writes for all commands
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_WRITE_PROTECT: status = " << status << endl;
        }

        status = MAX31785::program_Fan_Channel0(handle);
        if (status != 0)
        {
            return status;
        }

        status = MAX31785::program_Fan_Channel1(handle);
        if (status != 0)
        {
            return status;
        }

        status = MAX31785::program_Fan_Channel2(handle);
        if (status != 0)
        {
            return status;
        }

        status = MAX31785::program_Fan_Channel3(handle);
        if (status != 0)
        {
            return status;
        }

        status = MAX31785::program_Fan_Channel4(handle);
        if (status != 0)
        {
            return status;
        }

        status = MAX31785::program_Fan_Channel5(handle);
        if (status != 0)
        {
            return status;
        }

        status = MAX31785::program_Temp_Internal(handle);
        if (status != 0)
        {
            return status;
        }

        status = MAX31785::program_Temp_Sensor0(handle);
        if (status != 0)
        {
            return status;
        }

        status = MAX31785::program_Temp_Sensor1(handle);
        if (status != 0)
        {
            return status;
        }

        status = MAX31785::program_Temp_Sensor2(handle);
        if (status != 0)
        {
            return status;
        }

        status = MAX31785::program_Temp_Sensor3(handle);
        if (status != 0)
        {
            return status;
        }

        status = MAX31785::program_Temp_Sensor4(handle);
        if (status != 0)
        {
            return status;
        }

        status = MAX31785::program_Temp_Sensor5(handle);
        if (status != 0)
        {
            return status;
        }

        status = MAX31785::program_Temp_I2C1(handle);
        if (status != 0)
        {
            return status;
        }

        status = MAX31785::program_Temp_I2C2(handle);
        if (status != 0)
        {
            return status;
        }

        status = MAX31785::program_Temp_I2C3(handle);
        if (status != 0)
        {
            return status;
        }

        status = MAX31785::program_Temp_I2C4(handle);
        if (status != 0)
        {
            return status;
        }

        status = MAX31785::program_Voltage2(handle);
        if (status != 0)
        {
            return status;
        }
        status = MAX31785::program_Voltage3(handle);
        if (status != 0)
        {
            return status;
        }

        status = MAX31785::program_Voltage4(handle);
        if (status != 0)
        {
            return status;
        }

        status = MAX31785::program_Voltage5(handle);
        if (status != 0)
        {
            return status;
        }

        //Change Page to all
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = 0xFF;          //Enable Writes for all commands
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            return status;
        }

        //set MFR mode
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_MODE;   //page command
        buffer[i2cNumBytesToTx++] = 0x3F;   //Low
        buffer[i2cNumBytesToTx++] = 0x00;  //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            return status;
        }

        return 0;
    }

    int MAX31785::program_Commit(CP2112_HIDAPI *handle)
    {

        int status;                     // Variable to hold the int to do comparisons on
        uint8_t i2cAddress = 0xA4;      // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};   // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;   // Initialize a counter for the buffer and set to Zero
        uint32_t i2cNumBytesTxd = 0;    // Initialize another counter for the number of bytes actually sent and set to Zero

        //Disbale Write Protection
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_WRITE_PROTECT;  //page command
        buffer[i2cNumBytesToTx++] = 0x00;               //Enable Writes for all commands
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_WRITE_PROTECT: status = " << status << endl;
            return status;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_STORE_DEFUALT_ALL;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "failed CMD_STORE_DEFUALT_ALL: status = " << status << endl;
            return status;
        }
        
        return status;
    }

    int MAX31785::Get_Temps(TEMPS_DOUBLE &Temps_Double, TEMPS_RAW &Temps_Raw)
    {
        int status;

        uint8_t ArrayByte[1] = {0};
        uint16 TwoByte = 0;

        ArrayByte[1] = 0x0D;
        ArrayByte[0] = 0x89;
        TwoByte = ((ArrayByte[1] << 8) + ArrayByte[0]);
        Temps_Raw.Ch0 = TwoByte;
        Temps_Double.Ch0 = ((double)TwoByte * 0.01);

        ArrayByte[1] = 0x0D;
        ArrayByte[0] = 0x89;
        TwoByte = ((ArrayByte[1] << 8) + ArrayByte[0]);
        Temps_Raw.Ch1 = TwoByte;
        Temps_Double.Ch1 = ((double)TwoByte * 0.01);

        ArrayByte[1] = 0x0D;
        ArrayByte[0] = 0x89;
        TwoByte = ((ArrayByte[1] << 8) + ArrayByte[0]);
        Temps_Raw.Ch2 = TwoByte;
        Temps_Double.Ch2 = ((double)TwoByte * 0.01);

        ArrayByte[1] = 0x0D;
        ArrayByte[0] = 0x89;
        TwoByte = ((ArrayByte[1] << 8) + ArrayByte[0]);
        Temps_Raw.Ch3 = TwoByte;
        Temps_Double.Ch3 = ((double)TwoByte * 0.01);

        ArrayByte[1] = 0x0D;
        ArrayByte[0] = 0x89;
        TwoByte = ((ArrayByte[1] << 8) + ArrayByte[0]);
        Temps_Raw.Ch4 = TwoByte;
        Temps_Double.Ch4 = ((double)TwoByte * 0.01);

        ArrayByte[1] = 0x0D;
        ArrayByte[0] = 0x89;
        TwoByte = ((ArrayByte[1] << 8) + ArrayByte[0]);
        Temps_Raw.Ch5 = TwoByte;
        Temps_Double.Ch5 = ((double)TwoByte * 0.01);

        ArrayByte[1] = 0x0D;
        ArrayByte[0] = 0x89;
        TwoByte = ((ArrayByte[1] << 8) + ArrayByte[0]);
        Temps_Raw.D00 = TwoByte;
        Temps_Double.D00 = ((double)TwoByte * 0.01);

        ArrayByte[1] = 0x0D;
        ArrayByte[0] = 0x89;
        TwoByte = ((ArrayByte[1] << 8) + ArrayByte[0]);
        Temps_Raw.D01 = TwoByte;
        Temps_Double.D01 = ((double)TwoByte * 0.01);

        ArrayByte[1] = 0x0D;
        ArrayByte[0] = 0x89;
        TwoByte = ((ArrayByte[1] << 8) + ArrayByte[0]);
        Temps_Raw.D02 = TwoByte;
        Temps_Double.D02 = ((double)TwoByte * 0.01);

        ArrayByte[1] = 0x0D;
        ArrayByte[0] = 0x89;
        TwoByte = ((ArrayByte[1] << 8) + ArrayByte[0]);
        Temps_Raw.D03 = TwoByte;
        Temps_Double.D03 = ((double)TwoByte * 0.01);

        status = 0;

        return status;
    }

    int MAX31785::fan_On(CP2112_HIDAPI *handle)
    {
        //Set GPIO5 open/high
        int status;
        int stringReturn;
        status = handle->set_gpio(0x10 , 0x10);
        status = 0;
        return status;
    }

    int MAX31785::fan_Off(CP2112_HIDAPI *handle)
    {
        //Set GPIO5 low
        int status;
        int stringReturn;
        status = handle->set_gpio(0x10, 0x00);
        status = 0;
        return status;
    }

    int MAX31785::get_Temps(CP2112_HIDAPI *handle, TEMPS_DOUBLE *Temps_Double, TEMPS_RAW *Temps_Raw)
    {
        int status;
        uint8_t i2cAddress = 0xA4;      // Address of MAX31785 chip
        uint8_t buffer[16] = {0x0};     // Initialize a data buffer and set to all Zeros
        uint8_t i2cNumBytesToTx = 0;    // Initialize a counter for the buffer and set to Zero
        uint8_t i2cNumBytesToRx = 0;    // Initialize a counter for the recieve buffer and set to Zero
        uint8_t i2cNumBytesRxd = 0;     // Initialize another counter for the number of bytes actually recieved and set to Zero
        uint16_t TwoByte = 0x0;         // Temperory holding for the 16bit value.

        //produce some array of temps that includes the Fault and Warning limits
        //for debugging.
        //Temp = Y *10 ^ -2
        //were Y is the twos compliment number.

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_TEMP_INT; //Set page to page 12
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_TEMP_INT: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_READ_TEMPERATURE_1;      //READ_TEMPERATURE_1 of page 12
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_INT:CMD_READ_TEMPERATURE_1: status = " << status << endl;
        }

        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Temps_Raw->Int = TwoByte;
        Temps_Double->Int = ((double)TwoByte * 0.01);

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_TEMP_0;      //Set page to page 12
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_TEMP_0: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_READ_TEMPERATURE_1;      //READ_TEMPERATURE_1 of page 12
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_0:CMD_READ_TEMPERATURE_1: status = " << status << endl;
        }

        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Temps_Raw->Ch0 = TwoByte;
        Temps_Double->Ch0 = ((double)TwoByte * 0.01);


        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_TEMP_1;      //Set page to page 12
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_TEMP_1: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_READ_TEMPERATURE_1;      //READ_TEMPERATURE_1 of page 12                    
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_1:CMD_READ_TEMPERATURE_1: status = " << status << endl;
        }

        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Temps_Raw->Ch1 = TwoByte;
        Temps_Double->Ch1 = ((double)TwoByte * 0.01);


        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_TEMP_2;      //Set page to page 12
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_TEMP_2: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_READ_TEMPERATURE_1;      //READ_TEMPERATURE_1 of page 12
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_2:CMD_READ_TEMPERATURE_1: status = " << status << endl;
        }

        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Temps_Raw->Ch2 = TwoByte;
        Temps_Double->Ch2 = ((double)TwoByte * 0.01);

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_TEMP_3;      //Set page to page 12
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_TEMP_3: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_READ_TEMPERATURE_1;      //READ_TEMPERATURE_1 of page 12
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_3:CMD_READ_TEMPERATURE_1: status = " << status << endl;
        }

        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Temps_Raw->Ch3 = TwoByte;
        Temps_Double->Ch3 = ((double)TwoByte * 0.01);

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_TEMP_4;      //Set page to page 12
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_TEMP_4: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_READ_TEMPERATURE_1;      //READ_TEMPERATURE_1 of page 12             
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_4:CMD_READ_TEMPERATURE_1: status = " << status << endl;
        }

        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Temps_Raw->Ch4 = TwoByte;
        Temps_Double->Ch4 = ((double)TwoByte * 0.01);

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_TEMP_5;      //Set page to page 12
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_TEMP_5: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_READ_TEMPERATURE_1;      //READ_TEMPERATURE_1 of page 12        
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_5:CMD_READ_TEMPERATURE_1: status = " << status << endl;
        }

        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Temps_Raw->Ch5 = TwoByte;
        Temps_Double->Ch5 = ((double)TwoByte * 0.01);

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_I2C_0;      //Set page to page 12
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_I2C_0: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_READ_TEMPERATURE_1;      //READ_TEMPERATURE_1 of page 12           
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_I2C_0:CMD_READ_TEMPERATURE_1: status = " << status << endl;
        }

        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Temps_Raw->D00 = TwoByte;
        Temps_Double->D00 = ((double)TwoByte * 0.01);

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_I2C_1;      //Set page to page 12
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_I2C_1: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_READ_TEMPERATURE_1;      //READ_TEMPERATURE_1 of page 12                    
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_I2C_1:CMD_READ_TEMPERATURE_1: status = " << status << endl;
        }

        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Temps_Raw->D01 = TwoByte;
        Temps_Double->D01 = ((double)TwoByte * 0.01);

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_I2C_2;      //Set page to page 12
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_I2C_2: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_READ_TEMPERATURE_1;      //READ_TEMPERATURE_1 of page 12           
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_I2C_2:CMD_READ_TEMPERATURE_1: status = " << status << endl;
        }

        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Temps_Raw->D02 = TwoByte;
        Temps_Double->D02 = ((double)TwoByte * 0.01);

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_I2C_3;      //Set page to page 12
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_I2C_3: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_READ_TEMPERATURE_1;      //READ_TEMPERATURE_1 of page 12
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        //cout << "PAGE_I2C_3:CMD_READ_TEMPERATURE_1: i2cNumBytesRxd = " << dec << int(i2cNumBytesRxd) << endl;
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_I2C_3:CMD_READ_TEMPERATURE_1: status = " << status << endl;
        }

        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Temps_Raw->D03 = TwoByte;
        Temps_Double->D03 = ((double)TwoByte * 0.01);

        return status;
    }

    int MAX31785::get_RPM(CP2112_HIDAPI *handle, RPM_DOUBLE *RPM_Double, RPM_RAW *RPM_Raw)
    {
        uint16 TwoByte = 0;

        int status;                     // i2cStatus return value
        uint8_t i2cAddress = 0xA4;
        uint8_t buffer[16] = {0x0};     // Initialize a data buffer and set to all Zeros
        uint8_t i2cNumBytesToTx = 0;   // Initialize a counter for the buffer and set to Zero
        uint8_t i2cNumBytesToRx = 0;   // Initialize a counter for the recieve buffer and set to Zero
        uint8_t i2cNumBytesRxd = 0;    // Initialize another counter for the number of bytes actually recieved and set to Zero

        /*
          Read RPM of Channel 0 Fan
        */

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_FAN_0;      //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_FAN_0: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_READ_FAN_SPEED_1;      //READ_FAN_SPEED_1
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_0:CMD_READ_FAN_SPEED_1: status = " << status << endl;
        }
        TwoByte = ((buffer[1] << 8) + buffer[0]);
        RPM_Raw->Ch0 = TwoByte;
        RPM_Double->Ch0 = ((double)TwoByte);

        /*
          Read RPM of Channel 1 Fan
        */

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_FAN_1;      //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_FAN_1: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_READ_FAN_SPEED_1;      //READ_FAN_SPEED_1
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_1:CMD_READ_FAN_SPEED_1: status = " << status << endl;
        }
        TwoByte = ((buffer[1] << 8) + buffer[0]);
        RPM_Raw->Ch1 = TwoByte;
        RPM_Double->Ch1 = ((double)TwoByte);

        /*
          Read RPM of Channel 2 Fan
        */

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_FAN_2;      //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_FAN_2: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_READ_FAN_SPEED_1;      //READ_FAN_SPEED_1
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_2:CMD_READ_FAN_SPEED_1: status = " << status << endl;
        }
        TwoByte = ((buffer[1] << 8) + buffer[0]);
        RPM_Raw->Ch2 = TwoByte;
        RPM_Double->Ch2 = ((double)TwoByte);

        /*
          Read RPM of Channel 3 Fan
        */

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_FAN_3;      //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_FAN_3: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_READ_FAN_SPEED_1;      //READ_FAN_SPEED_1
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_3:CMD_READ_FAN_SPEED_1: status = " << status << endl;
        }
        TwoByte = ((buffer[1] << 8) + buffer[0]);
        RPM_Raw->Ch3 = TwoByte;
        RPM_Double->Ch3 = ((double)TwoByte);

        /*
          Read RPM of Channel 4 Fan
        */

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_FAN_4;      //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_FAN_4: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_READ_FAN_SPEED_1;      //READ_FAN_SPEED_1
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_4:CMD_READ_FAN_SPEED_1: status = " << status << endl;
        }
        TwoByte = ((buffer[1] << 8) + buffer[0]);
        RPM_Raw->Ch4 = TwoByte;
        RPM_Double->Ch4 = ((double)TwoByte);

        /*
          Read RPM of Channel 5 Fan
        */

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_FAN_5;      //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_FAN_5: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_READ_FAN_SPEED_1;      //READ_FAN_SPEED_1
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_5:CMD_READ_FAN_SPEED_1: status = " << status << endl;
        }
        TwoByte = ((buffer[1] << 8) + buffer[0]);
        RPM_Raw->Ch5 = TwoByte;
        RPM_Double->Ch5 = ((double)TwoByte);

        return status;

    }

    int MAX31785::get_Volt(CP2112_HIDAPI *handle, VOLTAGE_STRUC *Voltage_structure)
    {
        uint16 TwoByte = 0;
        int status;                     // i2cStatus return value
        uint8_t i2cAddress = 0xA4;
        uint8_t buffer[16] = {0x0};     // Initialize a data buffer and set to all Zeros
        uint8_t i2cNumBytesToTx = 0;    // Initialize a counter for the buffer and set to Zero
        uint8_t i2cNumBytesToRx = 0;    // Initialize a counter for the recieve buffer and set to Zero
        uint8_t i2cNumBytesRxd = 0;     // Initialize another counter for the number of bytes actually recieved and set to Zero

        /*
          Read voltages of Channel 0
        */

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_VOLT_0;      //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_VOLT_0: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_READ_VOUT;      //READ_VOUT
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_0:CMD_READ_VOUT: status = " << status << endl;
        }
        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Voltage_structure->Ch0.vout_raw = TwoByte;
        Voltage_structure->Ch0.vout_double = double(TwoByte);

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_VOUT_PEAK;      //READ_VOUT
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_0:CMD_READ_VOUT: status = " << status << endl;
        }
        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Voltage_structure->Ch0.vout_peak_raw = TwoByte;
        Voltage_structure->Ch0.vout_peak_double = double(TwoByte);

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_VOUT_MIN;      //READ_VOUT
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_0:CMD_READ_VOUT: status = " << status << endl;
        }
        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Voltage_structure->Ch0.vout_min_raw = TwoByte;
        Voltage_structure->Ch0.vout_min_double = double(TwoByte);

        /*
          Read voltages of Channel 1
        */

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_VOLT_1;      //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_VOLT_1: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_READ_VOUT;      //READ_VOUT
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_1:CMD_READ_VOUT: status = " << status << endl;
        }
        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Voltage_structure->Ch1.vout_raw = TwoByte;
        Voltage_structure->Ch1.vout_double = double(TwoByte);

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_VOUT_PEAK;      //READ_VOUT
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_1:CMD_READ_VOUT: status = " << status << endl;
        }
        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Voltage_structure->Ch1.vout_peak_raw = TwoByte;
        Voltage_structure->Ch1.vout_peak_double = double(TwoByte);

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_VOUT_MIN;      //READ_VOUT
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_1:CMD_READ_VOUT: status = " << status << endl;
        }
        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Voltage_structure->Ch1.vout_min_raw = TwoByte;
        Voltage_structure->Ch1.vout_min_double = double(TwoByte);

        /*
          Read voltages of Channel 2
        */

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_VOLT_2;      //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_VOLT_2: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_READ_VOUT;      //READ_VOUT
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_2:CMD_READ_VOUT: status = " << status << endl;
        }
        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Voltage_structure->Ch2.vout_raw = TwoByte;
        Voltage_structure->Ch2.vout_double = double(TwoByte);

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_VOUT_PEAK;      //READ_VOUT
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_2:CMD_READ_VOUT: status = " << status << endl;
        }
        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Voltage_structure->Ch2.vout_peak_raw = TwoByte;
        Voltage_structure->Ch2.vout_peak_double = double(TwoByte);

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_VOUT_MIN;      //READ_VOUT
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_2:CMD_READ_VOUT: status = " << status << endl;
        }
        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Voltage_structure->Ch2.vout_min_raw = TwoByte;
        Voltage_structure->Ch2.vout_min_double = double(TwoByte);

        /*
          Read voltages of Channel 3
        */

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_VOLT_3;      //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_VOLT_3: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_READ_VOUT;      //READ_VOUT
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_3:CMD_READ_VOUT: status = " << status << endl;
        }
        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Voltage_structure->Ch3.vout_raw = TwoByte;
        Voltage_structure->Ch3.vout_double = double(TwoByte);

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_VOUT_PEAK;      //READ_VOUT
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_3:CMD_READ_VOUT: status = " << status << endl;
        }
        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Voltage_structure->Ch3.vout_peak_raw = TwoByte;
        Voltage_structure->Ch3.vout_peak_double = double(TwoByte);

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_VOUT_MIN;      //READ_VOUT
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_3:CMD_READ_VOUT: status = " << status << endl;
        }
        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Voltage_structure->Ch3.vout_min_raw = TwoByte;
        Voltage_structure->Ch3.vout_min_double = double(TwoByte);

        /*
          Read voltages of Channel 4
        */

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_VOLT_4;      //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_VOLT_4: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_READ_VOUT;      //READ_VOUT
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_4:CMD_READ_VOUT: status = " << status << endl;
        }
        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Voltage_structure->Ch4.vout_raw = TwoByte;
        Voltage_structure->Ch4.vout_double = double(TwoByte);

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_VOUT_PEAK;      //READ_VOUT
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_4:CMD_READ_VOUT: status = " << status << endl;
        }
        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Voltage_structure->Ch4.vout_peak_raw = TwoByte;
        Voltage_structure->Ch4.vout_peak_double = double(TwoByte);

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_VOUT_MIN;      //READ_VOUT
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_4:CMD_READ_VOUT: status = " << status << endl;
        }
        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Voltage_structure->Ch4.vout_min_raw = TwoByte;
        Voltage_structure->Ch4.vout_min_double = double(TwoByte);

        /*
          Read voltages of Channel 5
        */

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_VOLT_5;      //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_VOLT_5: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_READ_VOUT;      //READ_VOUT
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_5:CMD_READ_VOUT: status = " << status << endl;
        }
        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Voltage_structure->Ch5.vout_raw = TwoByte;
        Voltage_structure->Ch5.vout_double = double(TwoByte);

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_VOUT_PEAK;      //READ_VOUT
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_5:CMD_READ_VOUT: status = " << status << endl;
        }
        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Voltage_structure->Ch5.vout_peak_raw = TwoByte;
        Voltage_structure->Ch5.vout_peak_double = double(TwoByte);

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_VOUT_MIN;      //READ_VOUT
        i2cNumBytesToRx = 2;
        i2cNumBytesRxd = 0;
        status = handle->i2c_write_read(i2cAddress, i2cNumBytesToTx, i2cNumBytesToRx, &i2cNumBytesRxd, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_5:CMD_READ_VOUT: status = " << status << endl;
        }
        TwoByte = ((buffer[1] << 8) + buffer[0]);
        Voltage_structure->Ch5.vout_min_raw = TwoByte;
        Voltage_structure->Ch5.vout_min_double = double(TwoByte);

        return 0;
    }

    int MAX31785::reset_volt(CP2112_HIDAPI *handle)
    {
        int status;                     // i2cStatus return value
        uint8_t i2cAddress = 0xA4;
        uint8_t buffer[16] = {0x0};     // Initialize a data buffer and set to all Zeros
        uint8_t i2cNumBytesToTx = 0;    // Initialize a counter for the buffer and set to Zero

        /*
          Read voltages of Channel 0
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_VOLT_0;      //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_VOLT_0: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_VOUT_MIN;
        buffer[i2cNumBytesToTx++] = 0x00;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_0:CMD_MFR_VOUT_MIN: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_VOUT_PEAK;
        buffer[i2cNumBytesToTx++] = 0x00;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_0:CMD_MFR_VOUT_MIN: status = " << status << endl;
        }

        /*
          Read voltages of Channel 1
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_VOLT_1;      //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_VOLT_0: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_VOUT_MIN;
        buffer[i2cNumBytesToTx++] = 0x00;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_1:CMD_MFR_VOUT_MIN: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_VOUT_PEAK;
        buffer[i2cNumBytesToTx++] = 0x00;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_1:CMD_MFR_VOUT_MIN: status = " << status << endl;
        }

        /*
          Read voltages of Channel 2
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_VOLT_2;      //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_VOLT_2: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_VOUT_MIN;
        buffer[i2cNumBytesToTx++] = 0x00;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_2:CMD_MFR_VOUT_MIN: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_VOUT_PEAK;
        buffer[i2cNumBytesToTx++] = 0x00;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_2:CMD_MFR_VOUT_MIN: status = " << status << endl;
        }
        
        /*
          Read voltages of Channel 3
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_VOLT_3;      //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_VOLT_3: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_VOUT_MIN;
        buffer[i2cNumBytesToTx++] = 0x00;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_3:CMD_MFR_VOUT_MIN: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_VOUT_PEAK;
        buffer[i2cNumBytesToTx++] = 0x00;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_3:CMD_MFR_VOUT_MIN: status = " << status << endl;
        }

        /*
          Read voltages of Channel 4
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_VOLT_4;      //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_VOLT_4: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_VOUT_MIN;
        buffer[i2cNumBytesToTx++] = 0x00;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_4:CMD_MFR_VOUT_MIN: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_VOUT_PEAK;
        buffer[i2cNumBytesToTx++] = 0x00;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_4:CMD_MFR_VOUT_MIN: status = " << status << endl;
        }

        /*
          Read voltages of Channel 5
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;      //page command
        buffer[i2cNumBytesToTx++] = PAGE_VOLT_5;      //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_VOLT_5: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_VOUT_MIN;
        buffer[i2cNumBytesToTx++] = 0x00;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_5:CMD_MFR_VOUT_MIN: status = " << status << endl;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_VOUT_PEAK;
        buffer[i2cNumBytesToTx++] = 0x00;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_5:CMD_MFR_VOUT_MIN: status = " << status << endl;
        }
        return 0;
    }

    int MAX31785::program_Fan_Channel0(CP2112_HIDAPI *handle)
    {

        //program fan channel 0 of the MAX31785 6 channel fan controller

        int status;                     // Variable to hold the int to do comparisons on
        uint8_t i2cAddress = 0xA4;      // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};   // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;   // Initialize a counter for the buffer and set to Zero

        /*
        Program Fan channel 0
        */

        //
        //Write to Enable channel 0 and fully program
        //


        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;          //page command
        buffer[i2cNumBytesToTx++] = PAGE_FAN_0;        //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_FAN_0: status = " << status << endl;
            return -1;
        }

        // Set the fan to automatic fan control
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_FAN_COMMAND_1;
        buffer[i2cNumBytesToTx++] = 0xFF;      //low
        buffer[i2cNumBytesToTx++] = 0xFF;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_0:CMD_FAN_COMMAND_1: status = " << status << endl;
            return -1;
        }

        /*
          SPIN = 00  disabled
          ROTOR = 0
          ROTOR_HI_LO = 0
          HEALTH = 0 disabled
          RAMP = 011 60% change takes 12 seconds
          TACH0 = 1 ramp fan to 100% if fan fault
          TSFO = 1 ramp fan to 100% if temp sensor fault
          HYST = 01 4 degree C thermal hysteresis
          DUAL_TACH = 0 disabled
          FREQ = 111 25kHz pwm frequency

        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_CONFIG;
        buffer[i2cNumBytesToTx++] = 0xE0;  //low
        buffer[i2cNumBytesToTx++] = 0xE7;  //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_0:CMD_MFR_FAN_CONFIG: status = " << status << endl;
            return -1;
        }

        /*
          PULSE = 11 4 pulses per revolution
          RPM/PWM = 0 PWM is the controlling feature
          FAN_ENABLED = 1 yes
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_FAN_CONFIG_1_2
        buffer[i2cNumBytesToTx++] = 0xB0;      //Data Low
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_0:CMD_FAN_CONFIG_1_2: status = " << status << endl;
            return -1;
        }


        /*
          1000 rpm for 0 - 40 degree C
          2000 rpm for 40 - 50 degree C
          3000 rpm for 50 - 80 degree C
          8000 rpm for 80 - up degree C
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_LUT;

        buffer[i2cNumBytesToTx++] = 0x00;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x00;      //Data High  T0

        buffer[i2cNumBytesToTx++] = 0x58;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1B;      //Data High  RPM0

        buffer[i2cNumBytesToTx++] = 0x4C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x09;      //Data High  T1

        buffer[i2cNumBytesToTx++] = 0xB8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1B;      //Data High  RPM1

        buffer[i2cNumBytesToTx++] = 0xB8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x0B;      //Data High  T2

        buffer[i2cNumBytesToTx++] = 0x58;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1B;      //Data High  RPM2

        buffer[i2cNumBytesToTx++] = 0xA0;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x0F;      //Data High  T3

        buffer[i2cNumBytesToTx++] = 0x58;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1B;      //Data High  RPM3

        buffer[i2cNumBytesToTx++] = 0xA0;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x0F;      //Data High  T4

        buffer[i2cNumBytesToTx++] = 0x58;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1B;      //Data High  RPM4

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  T5

        buffer[i2cNumBytesToTx++] = 0x4C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1D;      //Data High  RPM5

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  T6

        buffer[i2cNumBytesToTx++] = 0x20;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x27;      //Data High  RPM6

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  T7

        buffer[i2cNumBytesToTx++] = 0x10;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x27;      //Data High  RPM7


        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_0:CMD_MFR_FAN_LUT: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_PWM2RPM;
        buffer[i2cNumBytesToTx++] = 0xE8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x12;      //Data High

        buffer[i2cNumBytesToTx++] = 0x68;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1E;      //Data High

        buffer[i2cNumBytesToTx++] = 0x0C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x21;      //Data High

        buffer[i2cNumBytesToTx++] = 0x1C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x25;      //Data High

        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_0:CMD_MFR_FAN_PWM2RPM: status = " << status << endl;
            return -1;
        }

        /*
          warning limit and is disabled with all zeroes
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x00;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x00;      //Data High
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_0:CMD_MFR_FAN_PWM2RPM: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x00;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x00;      //Data High
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_0:CMD_MFR_FAN_PWM2RPM: status = " << status << endl;
            return -1;
        }

        /*
          FAUL_PIN_MONITOR = 1 respondes to the fault pin
          FAULT_PIN_ENABLED = 0 does not asserts the fault pin during active fault
          everything else is 0 and disabled

          This channel drives the Plenum fans which are only two wire fans
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAULT_RESPONSE;
        buffer[i2cNumBytesToTx++] = 0x01;      //Data Low
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_0:CMD_MFR_FAN_PWM2RPM: status = " << status << endl;
            return -1;
        }

        return 0;
    }

    int MAX31785::program_Fan_Channel1(CP2112_HIDAPI *handle)
    {

        //program fan channel 1 of the MAX31785 6 channel fan controller

        int status;                   // Variable to hold the int to do comparisons on
        uint8_t i2cAddress = 0xA4;            // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};    // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;			// Initialize a counter for the buffer and set to Zero
        uint32_t i2cNumBytesTxd = 0;			// Initialize another counter for the number of bytes actually sent and set to Zero


        /*
        Program Fan channel 0
        */

        //
        //Write to Enable channel 0 and fully program according to PMBusFile.txt located in the software folder of CPCU main project.
        //


        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;          //page command
        buffer[i2cNumBytesToTx++] = PAGE_FAN_1;        //Set page to page 1
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_1:CMD_PAGE: status = " << status << endl;
            return -1;
        }

        // Set the fan to automatic fan control
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_FAN_COMMAND_1;
        buffer[i2cNumBytesToTx++] = 0xFF;      //low
        buffer[i2cNumBytesToTx++] = 0xFF;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_1:CMD_FAN_COMMAND_1: status = " << status << endl;
            return -1;
        }

        /*
          SPIN = Eight revs to start motor
          ROTOR = 0
          ROTOR_HI_LO = 0
          HEALTH = enables (1)
          RAMP = 011 60% change takes 12 seconds
          TACH0 = 1 ramp fan to 100% if fan fault
          TSFO = 1 ramp fan to 100% if temp sensor fault
          HYST = 01 4 degree C thermal hysteresis
          DUAL_TACH = 0 disabled
          FREQ = 111 25kHz pwm frequency

        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_CONFIG;
        buffer[i2cNumBytesToTx++] = 0x73;
        buffer[i2cNumBytesToTx++] = 0xE4;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_1:CMD_MFR_FAN_CONFIG: status = " << status << endl;
            return -1;
        }

        /*
          PULSE = 11 4 pulses per revolution
          RPM/PWM = 1 RPM is the controlling feature
          FAN_ENABLED = 1 yes
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_FAN_CONFIG_1_2
        buffer[i2cNumBytesToTx++] = 0xF0;      //Data Low
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_1:CMD_FAN_CONFIG_1_2: status = " << status << endl;
            return -1;
        }


        /*
            Direct format fan speed or percentage, all zeroes is disabled
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0xF4;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x01;      //Data High
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_1:CMD_MFR_FAN_FAULT_LIMIT: status = " << status << endl;
            return -1;
        }

        /*
          1000 rpm for 0 - 40 degree C
          2000 rpm for 40 - 50 degree C
          3000 rpm for 50 - 80 degree C
          8000 rpm for 80 - up degree C
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_LUT;

        buffer[i2cNumBytesToTx++] = 0x00;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x00;      //Data High  T0

        buffer[i2cNumBytesToTx++] = 0xE8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x03;      //Data High  RPM0

        buffer[i2cNumBytesToTx++] = 0x4C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x09;      //Data High  T1

        buffer[i2cNumBytesToTx++] = 0xE8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x03;      //Data High  RPM1

        buffer[i2cNumBytesToTx++] = 0xB8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x0B;      //Data High  T2

        buffer[i2cNumBytesToTx++] = 0xE8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x03;      //Data High  RPM2

        buffer[i2cNumBytesToTx++] = 0xA0;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x0F;      //Data High  T3

        buffer[i2cNumBytesToTx++] = 0xD0;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x07;      //Data High  RPM3

        buffer[i2cNumBytesToTx++] = 0x88;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x13;      //Data High  T4

        buffer[i2cNumBytesToTx++] = 0xB8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x0B;      //Data High  RPM4

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  T5

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  RPM5

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  T6

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  RPM6

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  T7

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  RPM7

        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_1:CMD_MFR_FAN_LUT: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_PWM2RPM;
        buffer[i2cNumBytesToTx++] = 0xE8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x12;      //Data High

        buffer[i2cNumBytesToTx++] = 0x68;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1E;      //Data High

        buffer[i2cNumBytesToTx++] = 0x0C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x21;      //Data High

        buffer[i2cNumBytesToTx++] = 0x1C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x25;      //Data High

        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_1:CMD_MFR_FAN_PWM2RPM: status = " << status << endl;
            return -1;
        }

        /*
          warning limit and is disabled with all zeroes
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x00;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x00;      //Data High
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_1:CMD_MFR_FAN_WARN_LIMIT: status = " << status << endl;
            return -1;
        }

        /*
          FAUL_PIN_MONITOR = 1 ignores the fault pin
          FAULT_PIN_ENABLED = 1 asserts the fault pin during active fault
          everything else is 0 and disabled
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAULT_RESPONSE;
        buffer[i2cNumBytesToTx++] = 0x03;      //Data Low
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_1:CMD_MFR_FAULT_RESPONSE: status = " << status << endl;
            return -1;
        }

        return 0;
    }

    int MAX31785::program_Fan_Channel2(CP2112_HIDAPI *handle)
    {

        //program fan channel 2 of the MAX31785 6 channel fan controller

        int status;                     // Variable to hold the int to do comparisons on
        uint8_t i2cAddress = 0xA4;      // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};   // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;   // Initialize a counter for the buffer and set to Zero
        uint32_t i2cNumBytesTxd = 0;    // Initialize another counter for the number of bytes actually sent and set to Zero


        /*
        Program Fan channel 2
        */

        //
        //Write to Enable channel 2 and fully program according to PMBusFile.txt located in the software folder of CPCU main project.
        //


        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;          //page command
        buffer[i2cNumBytesToTx++] = PAGE_FAN_2;        //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_FAN_2: status = " << status << endl;
            return -1;
        }

        // Set the fan to automatic fan control
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_FAN_COMMAND_1;
        buffer[i2cNumBytesToTx++] = 0xFF;      //low
        buffer[i2cNumBytesToTx++] = 0xFF;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_2:CMD_FAN_COMMAND_1: status = " << status << endl;
            return -1;
        }

        /*
          SPIN = Eight revs to start motor
          ROTOR = 0
          ROTOR_HI_LO = 0
          HEALTH = enables (1)
          RAMP = 011 60% change takes 12 seconds
          TACH0 = 1 ramp fan to 100% if fan fault
          TSFO = 1 ramp fan to 100% if temp sensor fault
          HYST = 01 4 degree C thermal hysteresis
          DUAL_TACH = 0 disabled
          FREQ = 111 25kHz pwm frequency

        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_CONFIG;
        buffer[i2cNumBytesToTx++] = 0x73;
        buffer[i2cNumBytesToTx++] = 0xE4;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_2:CMD_MFR_FAN_CONFIG: status = " << status << endl;
            return -1;
        }

        /*
          PULSE = 11 4 pulses per revolution
          RPM/PWM = 1 RPM is the controlling feature
          FAN_ENABLED = 1 yes
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_FAN_CONFIG_1_2
        buffer[i2cNumBytesToTx++] = 0xF0;      //Data Low
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_2:CMD_FAN_CONFIG_1_2: status = " << status << endl;
            return -1;
        }


        /*
            Direct format fan speed or percentage, all zeroes is disabled
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0xF4;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x01;      //Data High
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_2:CMD_MFR_FAN_FAULT_LIMIT: status = " << status << endl;
            return -1;
        }

        /*
          1000 rpm for 0 - 40 degree C
          2000 rpm for 40 - 50 degree C
          3000 rpm for 50 - 80 degree C
          8000 rpm for 80 - up degree C
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_LUT;

        buffer[i2cNumBytesToTx++] = 0x00;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x00;      //Data High  T0

        buffer[i2cNumBytesToTx++] = 0xE8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x03;      //Data High  RPM0

        buffer[i2cNumBytesToTx++] = 0x4C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x09;      //Data High  T1

        buffer[i2cNumBytesToTx++] = 0xE8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x03;      //Data High  RPM1

        buffer[i2cNumBytesToTx++] = 0xB8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x0B;      //Data High  T2

        buffer[i2cNumBytesToTx++] = 0xE8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x03;      //Data High  RPM2

        buffer[i2cNumBytesToTx++] = 0xA0;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x0F;      //Data High  T3

        buffer[i2cNumBytesToTx++] = 0xD0;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x07;      //Data High  RPM3

        buffer[i2cNumBytesToTx++] = 0x88;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x13;      //Data High  T4

        buffer[i2cNumBytesToTx++] = 0xB8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x0B;      //Data High  RPM4

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  T5

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  RPM5

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  T6

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  RPM6

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  T7

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  RPM7

        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_2:CMD_MFR_FAN_LUT: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_PWM2RPM;
        buffer[i2cNumBytesToTx++] = 0xE8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x12;      //Data High

        buffer[i2cNumBytesToTx++] = 0x68;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1E;      //Data High

        buffer[i2cNumBytesToTx++] = 0x0C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x21;      //Data High

        buffer[i2cNumBytesToTx++] = 0x1C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x25;      //Data High

        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_2:CMD_MFR_FAN_PWM2RPM: status = " << status << endl;
            return -1;
        }

        /*
          warning limit and is disabled with all zeroes
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x00;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x00;      //Data High
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_2:CMD_MFR_FAN_WARN_LIMIT: status = " << status << endl;
            return -1;
        }

        /*
          FAUL_PIN_MONITOR = 0 ignores the fault pin
          FAULT_PIN_ENABLED = 1 adderts the fault pin during active fault
          everything else is 0 and disabled
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAULT_RESPONSE;
        buffer[i2cNumBytesToTx++] = 0x03;      //Data Low
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_2:CMD_MFR_FAULT_RESPONSE: status = " << status << endl;
            return -1;
        }

        return 0;
    }

    int MAX31785::program_Fan_Channel3(CP2112_HIDAPI *handle)
    {

        //program fan channel 3 of the MAX31785 6 channel fan controller

        int status;                     // Variable to hold the int to do comparisons on
        uint8_t i2cAddress = 0xA4;      // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};   // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;   // Initialize a counter for the buffer and set to Zero
        uint32_t i2cNumBytesTxd = 0;    // Initialize another counter for the number of bytes actually sent and set to Zero


        /*
        Program Fan channel 3
        */

        //
        //Write to Enable channel 3 and fully program according to PMBusFile.txt located in the software folder of CPCU main project.
        //


        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;          //page command
        buffer[i2cNumBytesToTx++] = PAGE_FAN_3;        //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_FAN_3: status = " << status << endl;
            return -1;
        }

        // Set the fan to automatic fan control
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_FAN_COMMAND_1;
        buffer[i2cNumBytesToTx++] = 0xFF;      //low
        buffer[i2cNumBytesToTx++] = 0xFF;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_3:CMD_FAN_COMMAND_1: status = " << status << endl;
            return -1;
        }

        /*
          SPIN = Eight revs to start motor
          ROTOR = 0
          ROTOR_HI_LO = 0
          HEALTH = enables (1)
          RAMP = 011 60% change takes 12 seconds
          TACH0 = 1 ramp fan to 100% if fan fault
          TSFO = 1 ramp fan to 100% if temp sensor fault
          HYST = 01 4 degree C thermal hysteresis
          DUAL_TACH = 0 disabled
          FREQ = 111 25kHz pwm frequency

        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_CONFIG;
        buffer[i2cNumBytesToTx++] = 0x73;
        buffer[i2cNumBytesToTx++] = 0xE4;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_3:CMD_MFR_FAN_CONFIG: status = " << status << endl;
            return -1;
        }

        /*
          PULSE = 11 4 pulses per revolution
          RPM/PWM = 1 RPM is the controlling feature
          FAN_ENABLED = 0 yes
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_FAN_CONFIG_1_2
        buffer[i2cNumBytesToTx++] = 0x70;      //Data Low
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_3:CMD_FAN_CONFIG_1_2: status = " << status << endl;
            return -1;
        }


        /*
            Direct format fan speed or percentage, all zeroes is disabled
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x2C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x01;      //Data High
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_3:CMD_MFR_FAN_FAULT_LIMIT: status = " << status << endl;
            return -1;
        }

        /*
          1000 rpm for 0 - 40 degree C
          2000 rpm for 40 - 50 degree C
          3000 rpm for 50 - 80 degree C
          8000 rpm for 80 - up degree C
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_LUT;

        buffer[i2cNumBytesToTx++] = 0x00;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x00;      //Data High  T0

        buffer[i2cNumBytesToTx++] = 0xE8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x03;      //Data High  RPM0

        buffer[i2cNumBytesToTx++] = 0x4C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x09;      //Data High  T1

        buffer[i2cNumBytesToTx++] = 0xE8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x03;      //Data High  RPM1

        buffer[i2cNumBytesToTx++] = 0xB8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x0B;      //Data High  T2

        buffer[i2cNumBytesToTx++] = 0xE8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x03;      //Data High  RPM2

        buffer[i2cNumBytesToTx++] = 0xA0;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x0F;      //Data High  T3

        buffer[i2cNumBytesToTx++] = 0xD0;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x07;      //Data High  RPM3

        buffer[i2cNumBytesToTx++] = 0x88;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x13;      //Data High  T4

        buffer[i2cNumBytesToTx++] = 0xB8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x0B;      //Data High  RPM4

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  T5

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  RPM5

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  T6

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  RPM6

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  T7

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  RPM7

        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_3:CMD_MFR_FAN_LUT: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_PWM2RPM;
        buffer[i2cNumBytesToTx++] = 0xE8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x12;      //Data High

        buffer[i2cNumBytesToTx++] = 0x68;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1E;      //Data High

        buffer[i2cNumBytesToTx++] = 0x0C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x21;      //Data High

        buffer[i2cNumBytesToTx++] = 0x1C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x25;      //Data High

        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_3:CMD_MFR_FAN_PWM2RPM: status = " << status << endl;
            return -1;
        }

        /*
          warning limit and is disabled with all zeroes
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x00;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x00;      //Data High
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_3:CMD_MFR_FAN_WARN_LIMIT: status = " << status << endl;
            return -1;
        }

        /*
          FAUL_PIN_MONITOR = 0 ignores the fault pin
          FAULT_PIN_ENABLED = 0 asserts the fault pin during active fault
          everything else is 0 and disabled
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAULT_RESPONSE;
        buffer[i2cNumBytesToTx++] = 0x00;      //Data Low
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_3:CMD_MFR_FAULT_RESPONSE: status = " << status << endl;
            return -1;
        }

        return status;
    }

    int MAX31785::program_Fan_Channel4(CP2112_HIDAPI *handle)
    {

        //program fan channel 4 of the MAX31785 6 channel fan controller

        int status;                     // Variable to hold the int to do comparisons on
        uint8_t i2cAddress = 0xA4;      // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};   // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;   // Initialize a counter for the buffer and set to Zero
        uint32_t i2cNumBytesTxd = 0;    // Initialize another counter for the number of bytes actually sent and set to Zero


        /*
        Program Fan channel 4
        */

        //
        //Write to Enable channel 0 and fully program according to PMBusFile.txt located in the software folder of CPCU main project.
        //


        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;          //page command
        buffer[i2cNumBytesToTx++] = PAGE_FAN_4;        //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_FAN_4: status = " << status << endl;
            return -1;
        }

        // Set the fan to automatic fan control
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_FAN_COMMAND_1;
        buffer[i2cNumBytesToTx++] = 0xFF;      //low
        buffer[i2cNumBytesToTx++] = 0xFF;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_4:CMD_FAN_COMMAND_1: status = " << status << endl;
            return -1;
        }

        /*
          SPIN = Eight revs to start motor
          ROTOR = 0
          ROTOR_HI_LO = 0
          HEALTH = enables (1)
          RAMP = 011 60% change takes 12 seconds
          TACH0 = 1 ramp fan to 100% if fan fault
          TSFO = 1 ramp fan to 100% if temp sensor fault
          HYST = 01 4 degree C thermal hysteresis
          DUAL_TACH = 0 disabled
          FREQ = 111 25kHz pwm frequency

        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_CONFIG;
        buffer[i2cNumBytesToTx++] = 0x73;
        buffer[i2cNumBytesToTx++] = 0xE4;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_4:CMD_MFR_FAN_CONFIG: status = " << status << endl;
            return -1;
        }

        /*
          PULSE = 11 4 pulses per revolution
          RPM/PWM = 1 RPM is the controlling feature
          FAN_ENABLED = 1 yes
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_FAN_CONFIG_1_2
        buffer[i2cNumBytesToTx++] = 0x70;      //Data Low
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_4:CMD_FAN_CONFIG_1_2: status = " << status << endl;
            return -1;
        }


        /*
            Direct format fan speed or percentage, all zeroes is disabled
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x2C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x01;      //Data High
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_4:CMD_MFR_FAN_FAULT_LIMIT: status = " << status << endl;
            return -1;
        }

        /*
          1000 rpm for 0 - 40 degree C
          2000 rpm for 40 - 50 degree C
          3000 rpm for 50 - 80 degree C
          8000 rpm for 80 - up degree C
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_LUT;

        buffer[i2cNumBytesToTx++] = 0x00;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x00;      //Data High  T0

        buffer[i2cNumBytesToTx++] = 0xE8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x03;      //Data High  RPM0

        buffer[i2cNumBytesToTx++] = 0x4C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x09;      //Data High  T1

        buffer[i2cNumBytesToTx++] = 0xE8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x03;      //Data High  RPM1

        buffer[i2cNumBytesToTx++] = 0xB8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x0B;      //Data High  T2

        buffer[i2cNumBytesToTx++] = 0xE8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x03;      //Data High  RPM2

        buffer[i2cNumBytesToTx++] = 0xA0;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x0F;      //Data High  T3

        buffer[i2cNumBytesToTx++] = 0xD0;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x07;      //Data High  RPM3

        buffer[i2cNumBytesToTx++] = 0x88;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x13;      //Data High  T4

        buffer[i2cNumBytesToTx++] = 0xB8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x0B;      //Data High  RPM4

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  T5

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  RPM5

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  T6

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  RPM6

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  T7

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  RPM7

        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_4:CMD_MFR_FAN_LUT: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_PWM2RPM;
        buffer[i2cNumBytesToTx++] = 0xE8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x12;      //Data High

        buffer[i2cNumBytesToTx++] = 0x68;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1E;      //Data High

        buffer[i2cNumBytesToTx++] = 0x0C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x21;      //Data High

        buffer[i2cNumBytesToTx++] = 0x1C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x25;      //Data High

        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_4:CMD_MFR_FAN_PWM2RPM: status = " << status << endl;
            return -1;
        }

        /*
          warning limit and is disabled with all zeroes
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x00;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x00;      //Data High
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_4:CMD_MFR_FAN_WARN_LIMIT: status = " << status << endl;
            return -1;
        }

        /*
          FAUL_PIN_MONITOR = 0 ignores the fault pin
          FAULT_PIN_ENABLED = 0 asserts the fault pin during active fault
          everything else is 0 and disabled
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAULT_RESPONSE;
        buffer[i2cNumBytesToTx++] = 0x00;      //Data Low
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_4:CMD_MFR_FAULT_RESPONSE: status = " << status << endl;
            return -1;
        }

        return status;
    }

    int MAX31785::program_Fan_Channel5(CP2112_HIDAPI *handle)
    {

        //program fan channel 5 of the MAX31785 6 channel fan controller

        int status;                     // Variable to hold the int to do comparisons on
        uint8_t i2cAddress = 0xA4;      // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};   // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;   // Initialize a counter for the buffer and set to Zero
        uint32_t i2cNumBytesTxd = 0;    // Initialize another counter for the number of bytes actually sent and set to Zero


        /*
        Program Fan channel 5
        */

        //
        //Write to Enable channel 5 and fully program according to PMBusFile.txt located in the software folder of CPCU main project.
        //


        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;          //page command
        buffer[i2cNumBytesToTx++] = PAGE_FAN_5;        //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_FAN_5: status = " << status << endl;
            return -1;
        }

        // Set the fan to automatic fan control
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_FAN_COMMAND_1;
        buffer[i2cNumBytesToTx++] = 0xFF;      //low
        buffer[i2cNumBytesToTx++] = 0xFF;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_5:CMD_FAN_COMMAND_1: status = " << status << endl;
            return -1;
        }

        /*
          SPIN = Eight revs to start motor
          ROTOR = 0
          ROTOR_HI_LO = 0
          HEALTH = enables (1)
          RAMP = 011 60% change takes 12 seconds
          TACH0 = 1 ramp fan to 100% if fan fault
          TSFO = 1 ramp fan to 100% if temp sensor fault
          HYST = 01 4 degree C thermal hysteresis
          DUAL_TACH = 0 disabled
          FREQ = 111 25kHz pwm frequency

        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_CONFIG;
        buffer[i2cNumBytesToTx++] = 0x73;
        buffer[i2cNumBytesToTx++] = 0xE4;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_5:CMD_MFR_FAN_CONFIG: status = " << status << endl;
            return -1;
        }

        /*
          PULSE = 11 4 pulses per revolution
          RPM/PWM = 1 RPM is the controlling feature
          FAN_ENABLED = 0 no
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_FAN_CONFIG_1_2
        buffer[i2cNumBytesToTx++] = 0x70;      //Data Low
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_5:CMD_FAN_CONFIG_1_2: status = " << status << endl;
            return -1;
        }


        /*
            Direct format fan speed or percentage, all zeroes is disabled
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x00;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x00;      //Data High
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_5:CMD_MFR_FAN_FAULT_LIMIT: status = " << status << endl;
            return -1;
        }

        /*
          1000 rpm for 0 - 40 degree C
          2000 rpm for 40 - 50 degree C
          3000 rpm for 50 - 80 degree C
          8000 rpm for 80 - up degree C
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_LUT;

        buffer[i2cNumBytesToTx++] = 0x00;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x00;      //Data High  T0

        buffer[i2cNumBytesToTx++] = 0xE8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x03;      //Data High  RPM0

        buffer[i2cNumBytesToTx++] = 0x4C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x09;      //Data High  T1

        buffer[i2cNumBytesToTx++] = 0xE8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x03;      //Data High  RPM1

        buffer[i2cNumBytesToTx++] = 0xB8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x0B;      //Data High  T2

        buffer[i2cNumBytesToTx++] = 0xE8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x03;      //Data High  RPM2

        buffer[i2cNumBytesToTx++] = 0xA0;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x0F;      //Data High  T3

        buffer[i2cNumBytesToTx++] = 0xD0;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x07;      //Data High  RPM3

        buffer[i2cNumBytesToTx++] = 0x88;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x13;      //Data High  T4

        buffer[i2cNumBytesToTx++] = 0xB8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x0B;      //Data High  RPM4

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  T5

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  RPM5

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  T6

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  RPM6

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  T7

        buffer[i2cNumBytesToTx++] = 0x40;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1F;      //Data High  RPM7

        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_5:CMD_MFR_FAN_LUT: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_PWM2RPM;
        buffer[i2cNumBytesToTx++] = 0xE8;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x12;      //Data High

        buffer[i2cNumBytesToTx++] = 0x68;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1E;      //Data High

        buffer[i2cNumBytesToTx++] = 0x0C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x21;      //Data High

        buffer[i2cNumBytesToTx++] = 0x1C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x25;      //Data High

        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_5:CMD_MFR_FAN_PWM2RPM: status = " << status << endl;
            return -1;
        }

        /*
          warning limit and is disabled with all zeroes
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAN_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x00;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x00;      //Data High
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_5:CMD_MFR_FAN_WARN_LIMIT: status = " << status << endl;
            return -1;
        }

        /*
          FAUL_PIN_MONITOR = 0 ignores the fault pin
          FAULT_PIN_ENABLED = 0 adderts the fault pin during active fault
          everything else is 0 and disabled
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAULT_RESPONSE;
        buffer[i2cNumBytesToTx++] = 0x00;      //Data Low
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_FAN_5:CMD_MFR_FAULT_RESPONSE: status = " << status << endl;
            return -1;
        }

        return 0;
    }

    int MAX31785::program_Temp_Internal(CP2112_HIDAPI *handle)
    {
        int status;                     // Variable to hold the int to do comparisons on
        uint8_t i2cAddress = 0xA4;      // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};   // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;   // Initialize a counter for the buffer and set to Zero
        uint32_t i2cNumBytesTxd = 0;    // Initialize another counter for the number of bytes actually sent and set to Zero

        /*
        Enable internal temp sensor
        */

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;
        buffer[i2cNumBytesToTx++] = PAGE_TEMP_INT;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_TEMP_INT: status = " << status << endl;
            return -1;
        }

        /*
            Assert fault pin when temp sensor faults
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAULT_RESPONSE;
        buffer[i2cNumBytesToTx++] = 0x02;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_INT:CMD_MFR_FAULT_RESPONSE: status = " << status << endl;
            return -1;
        }

        /*
            controlls all fans
            zero offset
            enabled temp sensor
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_TEMP_SENSOR_CONFIG;
        buffer[i2cNumBytesToTx++] = 0x3F;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x80;		//Data high    0x8020
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_INT:CMD_MFR_TEMP_SENSOR_CONFIG: status = " << status << endl;
            return -1;
        }

        /*
            Set fault limit to 85 degree C
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_OT_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x34;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x21;		//Data high    0x2134
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_INT:CMD_OT_FAULT_LIMIT: status = " << status << endl;
            return -1;
        }

        /*
            set warning limit to 75 degree C
        */
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_OT_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x4C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1D;		//Data high    0x1D4C
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_INT:CMD_OT_WARN_LIMIT: status = " << status << endl;
            return -1;
        }

        return 0;
    }

    int MAX31785::program_Temp_Sensor0(CP2112_HIDAPI *handle)
    {

        int status;                     // Variable to hold the int to do comparisons on
        uint8_t i2cAddress = 0xA4;      // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};   // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;   // Initialize a counter for the buffer and set to Zero
        uint32_t i2cNumBytesTxd = 0;    // Initialize another counter for the number of bytes actually sent and set to Zero

        /*
        Enable and Configure Thermal diode 0
        */

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;
        buffer[i2cNumBytesToTx++] = PAGE_TEMP_0;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_TEMP_0: status = " << status << endl;
            return -1;
        }


        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAULT_RESPONSE;
        buffer[i2cNumBytesToTx++] = 0x02;		//Data high    0x8020
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_0:CMD_MFR_FAULT_RESPONSE: status = " << status << endl;
            return -1;
        }


        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_TEMP_SENSOR_CONFIG;
        buffer[i2cNumBytesToTx++] = 0x3F;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x80;		//Data high    0x8020
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_0:CMD_MFR_TEMP_SENSOR_CONFIG: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_OT_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x34;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x21;		//Data high    0x2134
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_0:CMD_OT_FAULT_LIMIT: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_OT_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x4C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1D;		//Data high    0x1D4C
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_0:CMD_OT_WCMD_OT_WARN_LIMITARN_LIMIT: status = " << status << endl;
            return -1;
        }

        return 0;
    }

    int MAX31785::program_Temp_Sensor1(CP2112_HIDAPI *handle)
    {

        int status;                   // Variable to hold the int to do comparisons on
        uint8_t i2cAddress = 0xA4;            // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};    // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;			// Initialize a counter for the buffer and set to Zero
        uint32_t i2cNumBytesTxd = 0;			// Initialize another counter for the number of bytes actually sent and set to Zero

        /*
        Enable and Configure Thermal diode 1
        */

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;
        buffer[i2cNumBytesToTx++] = PAGE_TEMP_1;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_TEMP_1: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAULT_RESPONSE;
        buffer[i2cNumBytesToTx++] = 0x02;		//Data high    0x8020
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_1:CMD_MFR_FAULT_RESPONSE: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_TEMP_SENSOR_CONFIG;
        buffer[i2cNumBytesToTx++] = 0x3F;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x80;		//Data high    0x8020
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_1:CMD_MFR_TEMP_SENSOR_CONFIG: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_OT_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x34;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x21;		//Data high    0x2134
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_1:CMD_OT_FAULT_LIMIT: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_OT_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x4C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1D;		//Data high    0x1D4C
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_1:CMD_OT_WARN_LIMIT: status = " << status << endl;
            return -1;
        }

        return 0;
    }

    int MAX31785::program_Temp_Sensor2(CP2112_HIDAPI *handle)
    {

        int status;                     // Variable to hold the int to do comparisons on
        uint8_t i2cAddress = 0xA4;      // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};   // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;   // Initialize a counter for the buffer and set to Zero
        uint32_t i2cNumBytesTxd = 0;    // Initialize another counter for the number of bytes actually sent and set to Zero

        /*
        Disable and Configure Thermal diode 2
        */

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;
        buffer[i2cNumBytesToTx++] = PAGE_TEMP_2;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_TEMP_2: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAULT_RESPONSE;
        buffer[i2cNumBytesToTx++] = 0x00;		//Data high    0x8020
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_2:CMD_MFR_FAULT_RESPONSE: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_TEMP_SENSOR_CONFIG;
        buffer[i2cNumBytesToTx++] = 0x00;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x00;		//Data high    0x8020
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_2:CMD_MFR_TEMP_SENSOR_CONFIG: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_OT_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x34;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x21;		//Data high    0x2134
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_2:CMD_OT_FAULT_LIMIT: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_OT_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x4C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1D;		//Data high    0x1D4C
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_2:CMD_OT_WARN_LIMIT: status = " << status << endl;
            return -1;
        }

        return status;
    }

    int MAX31785::program_Temp_Sensor3(CP2112_HIDAPI *handle)
    {

        int status;                     // Variable to hold the int to do comparisons on
        uint8_t i2cAddress = 0xA4;      // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};   // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;   // Initialize a counter for the buffer and set to Zero
        uint32_t i2cNumBytesTxd = 0;    // Initialize another counter for the number of bytes actually sent and set to Zero

        /*
        Disable and Configure Thermal diode 3
        */

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;
        buffer[i2cNumBytesToTx++] = PAGE_TEMP_3;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_TEMP_3: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAULT_RESPONSE;
        buffer[i2cNumBytesToTx++] = 0x00;		//Data high    0x8020
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_3:CMD_MFR_FAULT_RESPONSE: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_TEMP_SENSOR_CONFIG;
        buffer[i2cNumBytesToTx++] = 0x00;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x00;		//Data high    0x8020
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_3:CMD_MFR_TEMP_SENSOR_CONFIG: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_OT_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x34;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x21;		//Data high    0x2134
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_3:CMD_OT_FAULT_LIMIT: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_OT_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x4C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1D;		//Data high    0x1D4C
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_3:CMD_OT_WARN_LIMIT: status = " << status << endl;
            return -1;
        }

        return status;
    }

    int MAX31785::program_Temp_Sensor4(CP2112_HIDAPI *handle)
    {

        int status;                     // Variable to hold the int to do comparisons on
        uint8_t i2cAddress = 0xA4;      // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};   // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;   // Initialize a counter for the buffer and set to Zero
        uint32_t i2cNumBytesTxd = 0;    // Initialize another counter for the number of bytes actually sent and set to Zero

        /*
        Disable and Configure Thermal diode 4
        */

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;
        buffer[i2cNumBytesToTx++] = PAGE_TEMP_4;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_TEMP_4: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAULT_RESPONSE;
        buffer[i2cNumBytesToTx++] = 0x00;		//Data high    0x8020
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_4:CMD_MFR_FAULT_RESPONSE: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_TEMP_SENSOR_CONFIG;
        buffer[i2cNumBytesToTx++] = 0x00;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x00;		//Data high    0x8020
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_4:CMD_MFR_TEMP_SENSOR_CONFIG: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_OT_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x34;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x21;		//Data high    0x2134
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_4:CMD_OT_FAULT_LIMIT: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_OT_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x4C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1D;		//Data high    0x1D4C
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_4:CMD_OT_WARN_LIMIT: status = " << status << endl;
            return -1;
        }

        return status;
    }

    int MAX31785::program_Temp_Sensor5(CP2112_HIDAPI *handle)
    {

        int status;                     // Variable to hold the int to do comparisons on
        uint8_t i2cAddress = 0xA4;      // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};   // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;   // Initialize a counter for the buffer and set to Zero
        uint32_t i2cNumBytesTxd = 0;    // Initialize another counter for the number of bytes actually sent and set to Zero

        /*
        Disable and Configure Thermal diode 5
        */

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;
        buffer[i2cNumBytesToTx++] = PAGE_TEMP_5;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_TEMP_5: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAULT_RESPONSE;
        buffer[i2cNumBytesToTx++] = 0x00;		//Data high    0x8020
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_5:CMD_MFR_FAULT_RESPONSE: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_TEMP_SENSOR_CONFIG;
        buffer[i2cNumBytesToTx++] = 0x00;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x00;		//Data high    0x8020
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_5:CMD_MFR_TEMP_SENSOR_CONFIG: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_OT_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x34;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x21;		//Data high    0x2134
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_5:CMD_OT_FAULT_LIMIT: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_OT_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x4C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1D;		//Data high    0x1D4C
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_TEMP_5:CMD_OT_WARN_LIMIT: status = " << status << endl;
            return -1;
        }

        return status;
    }

    int MAX31785::program_Temp_I2C1(CP2112_HIDAPI *handle)
    {

        int status;                     // Variable to hold the int to do comparisons on
        uint8_t i2cAddress = 0xA4;      // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};   // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;   // Initialize a counter for the buffer and set to Zero
        uint32_t i2cNumBytesTxd = 0;    // Initialize another counter for the number of bytes actually sent and set to Zero

        /*
        Enable and Configure I2C temp sensor 0
        */

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;
        buffer[i2cNumBytesToTx++] = PAGE_I2C_0;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_I2C_0: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAULT_RESPONSE;
        buffer[i2cNumBytesToTx++] = 0x02;		//Data high    0x8020
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_I2C_0:CMD_MFR_FAULT_RESPONSE: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_TEMP_SENSOR_CONFIG;
        buffer[i2cNumBytesToTx++] = 0x24;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x80;		//Data high    0x8020
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_I2C_0:CMD_MFR_TEMP_SENSOR_CONFIG: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_OT_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x34;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x21;		//Data high    0x2134
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_I2C_0:CMD_OT_FAULT_LIMIT: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_OT_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x4C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1D;		//Data high    0x1D4C
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_I2C_0:CMD_OT_WARN_LIMIT: status = " << status << endl;
            return -1;
        }

        return status;
    }

    int MAX31785::program_Temp_I2C2(CP2112_HIDAPI *handle)
    {

        int status;                     // Variable to hold the int to do comparisons on
        uint8_t i2cAddress = 0xA4;      // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};   // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;   // Initialize a counter for the buffer and set to Zero
        uint32_t i2cNumBytesTxd = 0;    // Initialize another counter for the number of bytes actually sent and set to Zero

        /*
        Enable and Configure I2C temp sensor 1
        */

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;
        buffer[i2cNumBytesToTx++] = PAGE_I2C_1;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_I2C_1: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAULT_RESPONSE;
        buffer[i2cNumBytesToTx++] = 0x02;		//Data high    0x8020
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_I2C_1:CMD_MFR_FAULT_RESPONSE: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_TEMP_SENSOR_CONFIG;
        buffer[i2cNumBytesToTx++] = 0x24;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x80;		//Data high    0x8020
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_I2C_1:CMD_MFR_TEMP_SENSOR_CONFIG: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_OT_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x34;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x21;		//Data high    0x2134
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_I2C_1:CMD_OT_FAULT_LIMIT: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_OT_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x4C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1D;		//Data high    0x1D4C
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_I2C_1:CMD_OT_WARN_LIMIT: status = " << status << endl;
            return -1;
        }

        return status;
    }

    int MAX31785::program_Temp_I2C3(CP2112_HIDAPI *handle)
    {

        int status;                     // Variable to hold the int to do comparisons on
        uint8_t i2cAddress = 0xA4;      // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};   // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;   // Initialize a counter for the buffer and set to Zero
        uint32_t i2cNumBytesTxd = 0;    // Initialize another counter for the number of bytes actually sent and set to Zero

        /*
        Enable and Configure I2C temp sensor 2
        */

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;
        buffer[i2cNumBytesToTx++] = PAGE_I2C_2;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_I2C_2: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAULT_RESPONSE;
        buffer[i2cNumBytesToTx++] = 0x02;		//Data high    0x8020
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_I2C_2:CMD_MFR_FAULT_RESPONSE: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_TEMP_SENSOR_CONFIG;
        buffer[i2cNumBytesToTx++] = 0x24;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x80;		//Data high    0x8020
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_I2C_2:CMD_MFR_TEMP_SENSOR_CONFIG: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_OT_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x34;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x21;		//Data high    0x2134
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_I2C_2:CMD_OT_FAULT_LIMIT: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_OT_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x4C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1D;		//Data high    0x1D4C
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_I2C_2:CMD_OT_WARN_LIMIT: status = " << status << endl;
            return -1;
        }

        return status;
    }

    int MAX31785::program_Temp_I2C4(CP2112_HIDAPI *handle)
    {

        int status;                     // Variable to hold the int to do comparisons on
        uint8_t i2cAddress = 0xA4;      // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};   // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;   // Initialize a counter for the buffer and set to Zero
        uint32_t i2cNumBytesTxd = 0;    // Initialize another counter for the number of bytes actually sent and set to Zero

        /*
        Enable and Configure I2C temp sensor 3
        */

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;
        buffer[i2cNumBytesToTx++] = PAGE_I2C_3;
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_I2C_3: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAULT_RESPONSE;
        buffer[i2cNumBytesToTx++] = 0x02;		//Data high    0x8020
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_I2C_3:CMD_MFR_FAULT_RESPONSE: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_TEMP_SENSOR_CONFIG;
        buffer[i2cNumBytesToTx++] = 0x24;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x80;		//Data high    0x8020
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_I2C_3:CMD_MFR_TEMP_SENSOR_CONFIG: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_OT_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x34;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x21;		//Data high    0x2134
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_I2C_3:CMD_OT_FAULT_LIMIT: status = " << status << endl;
            return -1;
        }

        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_OT_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x4C;      //Data Low
        buffer[i2cNumBytesToTx++] = 0x1D;		//Data high    0x1D4C
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_I2C_3:CMD_OT_WARN_LIMIT: status = " << status << endl;
            return -1;
        }

        return status;
    }

    int MAX31785::program_Voltage0(CP2112_HIDAPI *handle)
    {
        int status;                     // Variable to hold the int to do comparisons on
        uint8_t i2cAddress = 0xA4;      // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};   // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;   // Initialize a counter for the buffer and set to Zero
        uint32_t i2cNumBytesTxd = 0;    // Initialize another counter for the number of bytes actually sent and set to Zero

        return status;
    }

    int MAX31785::program_Voltage1(CP2112_HIDAPI *handle)
    {
        int status;                     // Variable to hold the int to do comparisons on
        uint8_t i2cAddress = 0xA4;      // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};   // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;   // Initialize a counter for the buffer and set to Zero
        uint32_t i2cNumBytesTxd = 0;    // Initialize another counter for the number of bytes actually sent and set to Zero

        return status;
    }

    int MAX31785::program_Voltage2(CP2112_HIDAPI *handle)
    {
        int status;                     // Variable to hold the int to do comparisons on
        uint8_t i2cAddress = 0xA4;      // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};   // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;   // Initialize a counter for the buffer and set to Zero
        uint32_t i2cNumBytesTxd = 0;    // Initialize another counter for the number of bytes actually sent and set to Zero

        /*
        Program Voltage Channel 2
        */

        //
        //Write to Enable channel 2 and fully program
        //


        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;          //page command
        buffer[i2cNumBytesToTx++] = PAGE_VOLT_2;        //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_VOLT_2: status = " << status << endl;
            return -1;
        }

        // Set Scale to 0.25, 0.25*32767=8192 => 0x2000
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_VOUT_SCALE_MONITOR;
        buffer[i2cNumBytesToTx++] = 0x00;      //low
        buffer[i2cNumBytesToTx++] = 0x20;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_2:CMD_VOUT_SCALE_MONITOR: status = " << status << endl;
            return -1;
        }

        // Set OV Fault to max
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_VOUT_OV_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0xFF;      //low
        buffer[i2cNumBytesToTx++] = 0x7F;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_2:CMD_VOUT_OV_FAULT_LIMIT: status = " << status << endl;
            return -1;
        }

        // Set OV Alert to max
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_VOUT_OV_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0xFF;      //low
        buffer[i2cNumBytesToTx++] = 0x7F;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_2:CMD_VOUT_OV_WARN_LIMIT: status = " << status << endl;
            return -1;
        }

        // Set UV Fault to min
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_VOUT_UV_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x00;      //low
        buffer[i2cNumBytesToTx++] = 0x00;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_2:CMD_VOUT_UV_FAULT_LIMIT: status = " << status << endl;
            return -1;
        }

        // Set UV Alert to min
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_VOUT_UV_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x00;      //low
        buffer[i2cNumBytesToTx++] = 0x00;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_2:CMD_VOUT_UV_WARN_LIMIT: status = " << status << endl;
            return -1;
        }

        // Set Fault Response, Do nothing
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAULT_RESPONSE;
        buffer[i2cNumBytesToTx++] = 0x00;      //low
        buffer[i2cNumBytesToTx++] = 0x00;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_2:CMD_MFR_FAULT_RESPONSE: status = " << status << endl;
            return -1;
        }

        return 0;
    }

    int MAX31785::program_Voltage3(CP2112_HIDAPI *handle)
    {
        int status;                     // Variable to hold the int to do comparisons on
        uint8_t i2cAddress = 0xA4;      // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};   // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;   // Initialize a counter for the buffer and set to Zero
        uint32_t i2cNumBytesTxd = 0;    // Initialize another counter for the number of bytes actually sent and set to Zero

        /*
        Program Voltage Channel 3
        */

        //
        //Write to Enable channel32 and fully program
        //


        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;          //page command
        buffer[i2cNumBytesToTx++] = PAGE_VOLT_3;        //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_VOLT_3: status = " << status << endl;
            return -1;
        }

        // Set Scale to 0.25, 0.25*32767=8192 => 0x2000
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_VOUT_SCALE_MONITOR;
        buffer[i2cNumBytesToTx++] = 0x00;      //low
        buffer[i2cNumBytesToTx++] = 0x20;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_3:CMD_VOUT_SCALE_MONITOR: status = " << status << endl;
            return -1;
        }

        // Set OV Fault to max
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_VOUT_OV_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0xFF;      //low
        buffer[i2cNumBytesToTx++] = 0x7F;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_3:CMD_VOUT_OV_FAULT_LIMIT: status = " << status << endl;
            return -1;
        }

        // Set OV Alert to max
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_VOUT_OV_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0xFF;      //low
        buffer[i2cNumBytesToTx++] = 0x7F;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_3:CMD_VOUT_OV_WARN_LIMIT: status = " << status << endl;
            return -1;
        }

        // Set UV Fault to min
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_VOUT_UV_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x00;      //low
        buffer[i2cNumBytesToTx++] = 0x00;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_3:CMD_VOUT_UV_FAULT_LIMIT: status = " << status << endl;
            return -1;
        }

        // Set UV Alert to min
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_VOUT_UV_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x00;      //low
        buffer[i2cNumBytesToTx++] = 0x00;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_3:CMD_VOUT_UV_WARN_LIMIT: status = " << status << endl;
            return -1;
        }

        // Set Fault Response, Do nothing
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAULT_RESPONSE;
        buffer[i2cNumBytesToTx++] = 0x00;      //low
        buffer[i2cNumBytesToTx++] = 0x00;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_3:CMD_MFR_FAULT_RESPONSE: status = " << status << endl;
            return -1;
        }

        return status;
    }

    int MAX31785::program_Voltage4(CP2112_HIDAPI *handle)
    {
        int status;                     // Variable to hold the int to do comparisons on
        uint8_t i2cAddress = 0xA4;      // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};   // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;   // Initialize a counter for the buffer and set to Zero
        uint32_t i2cNumBytesTxd = 0;    // Initialize another counter for the number of bytes actually sent and set to Zero

        /*
        Program Voltage Channel 2
        */

        //
        //Write to Enable channel 4 and fully program
        //


        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;          //page command
        buffer[i2cNumBytesToTx++] = PAGE_VOLT_4;        //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_VOLT_4: status = " << status << endl;
            return -1;
        }

        // Set Scale to 0.25, 0.25*32767=8192 => 0x2000
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_VOUT_SCALE_MONITOR;
        buffer[i2cNumBytesToTx++] = 0x00;      //low
        buffer[i2cNumBytesToTx++] = 0x20;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_4:CMD_VOUT_SCALE_MONITOR: status = " << status << endl;
            return -1;
        }

        // Set OV Fault to max
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_VOUT_OV_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0xFF;      //low
        buffer[i2cNumBytesToTx++] = 0x7F;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_4:CMD_VOUT_OV_FAULT_LIMIT: status = " << status << endl;
            return -1;
        }

        // Set OV Alert to max
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_VOUT_OV_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0xFF;      //low
        buffer[i2cNumBytesToTx++] = 0x7F;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_4:CMD_VOUT_OV_WARN_LIMIT: status = " << status << endl;
            return -1;
        }

        // Set UV Fault to min
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_VOUT_UV_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x00;      //low
        buffer[i2cNumBytesToTx++] = 0x00;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_4:CMD_VOUT_UV_FAULT_LIMIT: status = " << status << endl;
            return -1;
        }

        // Set UV Alert to min
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_VOUT_UV_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x00;      //low
        buffer[i2cNumBytesToTx++] = 0x00;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_4:CMD_VOUT_UV_WARN_LIMIT: status = " << status << endl;
            return -1;
        }

        // Set Fault Response, Do nothing
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAULT_RESPONSE;
        buffer[i2cNumBytesToTx++] = 0x00;      //low
        buffer[i2cNumBytesToTx++] = 0x00;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_4:CMD_MFR_FAULT_RESPONSE: status = " << status << endl;
            return -1;
        }

        return status;

    }

    int MAX31785::program_Voltage5(CP2112_HIDAPI *handle)
    {
        int status;                     // Variable to hold the int to do comparisons on
        uint8_t i2cAddress = 0xA4;      // Address of MAX31785 chip
        uint8_t buffer[256] = {0x00};   // Initialize a data buffer and set to all Zeros
        uint32_t i2cNumBytesToTx = 0;   // Initialize a counter for the buffer and set to Zero
        uint32_t i2cNumBytesTxd = 0;    // Initialize another counter for the number of bytes actually sent and set to Zero

        /*
        Program Voltage Channel 5
        */

        //
        //Write to Enable channel 5 and fully program
        //


        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_PAGE;          //page command
        buffer[i2cNumBytesToTx++] = PAGE_VOLT_5;        //Set page to page 2
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "CMD_PAGE:PAGE_VOLT_5: status = " << status << endl;
            return -1;
        }

        // Set Scale to 0.25, 0.25*32767=8192 => 0x2000
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_VOUT_SCALE_MONITOR;
        buffer[i2cNumBytesToTx++] = 0x00;      //low
        buffer[i2cNumBytesToTx++] = 0x20;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_5:CMD_VOUT_SCALE_MONITOR: status = " << status << endl;
            return -1;
        }

        // Set OV Fault to max
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_VOUT_OV_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0xFF;      //low
        buffer[i2cNumBytesToTx++] = 0x7F;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_5:CMD_VOUT_OV_FAULT_LIMIT: status = " << status << endl;
            return -1;
        }

        // Set OV Alert to max
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_VOUT_OV_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0xFF;      //low
        buffer[i2cNumBytesToTx++] = 0x7F;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_5:CMD_VOUT_OV_WARN_LIMIT: status = " << status << endl;
            return -1;
        }

        // Set UV Fault to min
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_VOUT_UV_FAULT_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x00;      //low
        buffer[i2cNumBytesToTx++] = 0x00;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_5:CMD_VOUT_UV_FAULT_LIMIT: status = " << status << endl;
            return -1;
        }

        // Set UV Alert to min
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_VOUT_UV_WARN_LIMIT;
        buffer[i2cNumBytesToTx++] = 0x00;      //low
        buffer[i2cNumBytesToTx++] = 0x00;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_5:CMD_VOUT_UV_WARN_LIMIT: status = " << status << endl;
            return -1;
        }

        // Set Fault Response, Do nothing
        i2cNumBytesToTx = 0;
        buffer[i2cNumBytesToTx++] = CMD_MFR_FAULT_RESPONSE;
        buffer[i2cNumBytesToTx++] = 0x00;      //low
        buffer[i2cNumBytesToTx++] = 0x00;      //high
        status = handle->i2c_write(i2cAddress, i2cNumBytesToTx, buffer);
        if (status != CP2112_HIDAPI::I2C_RESULT::I2C_SUCCESS)
        {
            cout << "PAGE_VOLT_5:CMD_MFR_FAULT_RESPONSE: status = " << status << endl;
            return -1;
        }

        return status;
    }


//     /////////////////////////////////////////////////////////////////////////////////////////
//     //
//     //
//     //
//     //                                  Functions for DS7505 Class
//     //
//     //
//     //
//     ////////////////////////////////////////////////////////////////////////////////////////

//     int DS7505::get_Data(CP2112_HIDAPI *handle, DS7505_Data &data, QVector<uint8> &i2c_address)
//     {
//         int status;
//         int stringReturn;
//         uint8_t i2cAddress = 0x00;                // Var to stor I2C Address
//         uint8_t buffer[16] = {0x00};         // Initialize a data buffer and set to all Zeros
//         uint8_t i2cDataReceive[16] = {0x00};		// Initialize a data buffer and set to all Zeros
//         uint32_t i2cNumBytesToTx = 0;             // Initialize a counter for the buffer and set to Zero
//         uint32_t i2cNumBytesTxd = 0;              // Initialize another counter for the number of bytes actually sent and set to Zero
//         uint32_t i2cNumBytesToRx = 0;             // Initialize a counter for the recieve buffer and set to Zero
//         uint32_t i2cNumBytesRxd = 0;              // Initialize another counter for the number of bytes actually recieved and set to Zero
//         QVector<uint16> hold_temps(12);
//         hold_temps.fill(0x00);
//         QVector<uint8> hold_config(4);
//         hold_config.fill(0x00);
//         int i = 0;                              // I2C Address Index pointer
//         int j = 0;                              // Hold Temps Pointer
//         int k = 0;                              // Hold Config Pointer

//         if (i2c_address.size()>5)
//         {
//             status = "To Many devices found, can only have 4 devices";
//             return status;
//         }

//         if (i2c_address.size()==0)
//         {
//             status = "No I2C Addresses Given";
//             return status;
//         }

//         for(i = 0; i < i2c_address.size(); i++)
//         {
//             i2cAddress = i2c_address[i];

//             if(i2cAddress == 0)
//             {
//                 break;
//             }


//             //Read Temp
//             i2cNumBytesToTx = 0;
//             buffer[i2cNumBytesToTx++] = 0x00;      //Set pointer to Temp location 0x00
//             status = I2C_DeviceWrite(handle, i2cAddress, i2cNumBytesToTx, i2cDataSend, &i2cNumBytesTxd,
//                                      I2C_TRANSFER_OPTIONS_START_BIT |
//                                      I2C_TRANSFER_OPTIONS_BREAK_ON_NACK);   //write page command
//             i2cNumBytesToRx = 2;
//             status = I2C_DeviceRead(handle, i2cAddress, i2cNumBytesToRx, i2cDataReceive, &i2cNumBytesRxd,
//                                     I2C_TRANSFER_OPTIONS_START_BIT |
//                                     I2C_TRANSFER_OPTIONS_STOP_BIT |
//                                     I2C_TRANSFER_OPTIONS_FAST_TRANSFER_BYTES |
//                                     I2C_TRANSFER_OPTIONS_NACK_LAST_BYTE); //read two bytes

//             hold_temps[j++] = ((i2cDataReceive[0] << 8) + i2cDataReceive[1]);

//             //Read Config
//             i2cNumBytesToTx = 0;
//             buffer[i2cNumBytesToTx++] = 0x01;      //Set pointer to Config location 0x00
//             status = I2C_DeviceWrite(handle, i2cAddress, i2cNumBytesToTx, i2cDataSend, &i2cNumBytesTxd,
//                                      I2C_TRANSFER_OPTIONS_START_BIT |
//                                      I2C_TRANSFER_OPTIONS_STOP_BIT |
//                                      I2C_TRANSFER_OPTIONS_BREAK_ON_NACK);   //write page command
//             i2cNumBytesToRx = 1;
//             status = I2C_DeviceRead(handle, i2cAddress, i2cNumBytesToRx, i2cDataReceive, &i2cNumBytesRxd,
//                                     I2C_TRANSFER_OPTIONS_START_BIT |
//                                     I2C_TRANSFER_OPTIONS_STOP_BIT |
//                                     I2C_TRANSFER_OPTIONS_NACK_LAST_BYTE); //read two bytes
//             hold_config[k++] = i2cDataReceive[0];

//             //Read Thyst
//             i2cNumBytesToTx = 0;
//             buffer[i2cNumBytesToTx++] = 0x02;      //Set pointer to Thyst location 0x02
//             status = I2C_DeviceWrite(handle, i2cAddress, i2cNumBytesToTx, i2cDataSend, &i2cNumBytesTxd,
//                                      I2C_TRANSFER_OPTIONS_START_BIT |
//                                      I2C_TRANSFER_OPTIONS_BREAK_ON_NACK);   //write page command
//             i2cNumBytesToRx = 2;
//             status = I2C_DeviceRead(handle, i2cAddress, i2cNumBytesToRx, i2cDataReceive, &i2cNumBytesRxd,
//                                     I2C_TRANSFER_OPTIONS_START_BIT |
//                                     I2C_TRANSFER_OPTIONS_STOP_BIT |
//                                     I2C_TRANSFER_OPTIONS_FAST_TRANSFER_BYTES |
//                                     I2C_TRANSFER_OPTIONS_NACK_LAST_BYTE); //read two bytes

//             hold_temps[j++] = ((i2cDataReceive[0] << 8) + i2cDataReceive[1]);

//             //Read Tos
//             i2cNumBytesToTx = 0;
//             buffer[i2cNumBytesToTx++] = 0x03;      //Set pointer to Tos location 0x03
//             status = I2C_DeviceWrite(handle, i2cAddress, i2cNumBytesToTx, i2cDataSend, &i2cNumBytesTxd,
//                                      I2C_TRANSFER_OPTIONS_START_BIT |
//                                      I2C_TRANSFER_OPTIONS_BREAK_ON_NACK);   //write page command
//             i2cNumBytesToRx = 2;
//             status = I2C_DeviceRead(handle, i2cAddress, i2cNumBytesToRx, i2cDataReceive, &i2cNumBytesRxd,
//                                     I2C_TRANSFER_OPTIONS_START_BIT |
//                                     I2C_TRANSFER_OPTIONS_STOP_BIT |
//                                     I2C_TRANSFER_OPTIONS_FAST_TRANSFER_BYTES |
//                                     I2C_TRANSFER_OPTIONS_NACK_LAST_BYTE); //read two bytes
//             hold_temps[j++] = ((i2cDataReceive[0] << 8) + i2cDataReceive[1]);
//         }
//         data.D00_address = i2c_address[0];
//         data.D00_raw_temp = hold_temps[0];
//         data.D00_double_temp = ((double)hold_temps[0]/256.0);
//         data.D00_raw_HYST = hold_temps[1];
//         data.D00_double_HYST = ((double)hold_temps[1]/256.0);
//         data.D00_raw_tos = hold_temps[2];
//         data.D00_double_tos = ((double)hold_temps[2]/256.0);
//         data.D00_config = hold_config[0];

//         data.D01_address = i2c_address[1];
//         data.D01_raw_temp = hold_temps[3];
//         data.D01_double_temp = ((double)hold_temps[3]/256.0);
//         data.D01_raw_HYST = hold_temps[4];
//         data.D01_double_HYST = ((double)hold_temps[4]/256.0);
//         data.D01_raw_tos = hold_temps[5];
//         data.D01_double_tos = ((double)hold_temps[5]/256.0);
//         data.D01_config = hold_config[1];

//         data.D02_address = i2c_address[2];
//         data.D02_raw_temp = hold_temps[6];
//         data.D02_double_temp = ((double)hold_temps[6]/256.0);
//         data.D02_raw_HYST = hold_temps[7];
//         data.D02_double_HYST = ((double)hold_temps[7]/256.0);
//         data.D02_raw_tos = hold_temps[8];
//         data.D02_double_tos = ((double)hold_temps[8]/256.0);
//         data.D02_config = hold_config[2];

//         data.D03_address = i2c_address[3];
//         data.D03_raw_temp = hold_temps[9];
//         data.D03_double_temp = ((double)hold_temps[9]/256.0);
//         data.D03_raw_HYST = hold_temps[10];
//         data.D03_double_HYST = ((double)hold_temps[10]/256.0);
//         data.D03_raw_tos = hold_temps[11];
//         data.D03_double_tos = ((double)hold_temps[11]/256.0);
//         data.D03_config = hold_config[3];

//         status = 0;
//         return status;
//     }

//     int DS7505::find_DS7505_Devices(CP2112_HIDAPI *handle, QVector<uint8> &i2c_address)
//     {
//         QVector<uint8> addresses(4);
//         addresses.fill(0x00);
//         int stringReturn;
//         int status;
//         uint8_t i2cAddress = 0x00;                // Var to store I2C Address
//         uint8_t buffer[16] = {0x00};         // Initialize a data buffer and set to all Zeros
//         uint32_t i2cNumBytesToTx = 0;             // Initialize a counter for the buffer and set to Zero
//         uint32_t i2cNumBytesTxd = 0;              // Initialize another counter for the number of bytes actually sent and set to Zero

//         uint8_t i = 0;
//         uint8_t j = 0;

//         buffer[i2cNumBytesToTx++] = 0x01;

//         for (i = 0x01; i < 0x7F; i++)
//         {
//             i2cAddress = i;
//             status = I2C_DeviceWrite(handle, i2cAddress, i2cNumBytesToTx, i2cDataSend, &i2cNumBytesTxd,
//                                      I2C_TRANSFER_OPTIONS_START_BIT |
//                                      I2C_TRANSFER_OPTIONS_STOP_BIT |
//                                      I2C_TRANSFER_OPTIONS_BREAK_ON_NACK);   //write page command
//             if (status == FT_OK)
//             {
//                 if( j < 4)
//                 {
//                     qDebug()<<"I2C Address"<< i2cAddress << " j:" << j;
//                     addresses[j++] = (i2cAddress);
//                 }

//             }
//         }

//         status = 0;
//         i2c_address = addresses;

//         if(j == 1)
//         {
//             status = "unable to find any DS7505 devices";
//         }

//         return status;
//     }

//     int DS7505::Configure_DS7505(CP2112_HIDAPI *handle,  DS7505_Data &data, QVector<uint8> &i2c_address)
//     {
//         int status;
//         int stringReturn;
//         int16  temp_int;                        // Temporary variable to store the 16bit value for the Double to uint8_t array conversion
//         uint8_t  i2cAddress = 0x00;               // Var to stor I2C Address
//         uint8_t  buffer[16] = {0x00};        // Initialize a data buffer and set to all Zero
//         uint32_t i2cNumBytesToTx = 0;             // Initialize a counter for the buffer and set to Zero
//         uint32_t i2cNumBytesTxd = 0;              // Initialize another counter for the number of bytes actually sent and set to Zero
//         uint8_t i = 0;                              // Integer for for loop functioninality

//         if (i2c_address.size()>5)
//         {
//             status = "To Many devices found, can only have 4 devices";
//             return status;
//         }

//         if (i2c_address.size()==0)
//         {
//             status = "No I2C Addresses Given";
//             return status;
//         }

//         for(i = 0; i < i2c_address.size() - 1; i++)
//         {
//             i2cAddress = i2c_address[i];

//             if(i2cAddress == 0)
//             {
//                 break;
//             }

//             i2cNumBytesToTx = 0;
//             buffer[i2cNumBytesToTx++] = 0x01;  //change pointer to config register
//             buffer[i2cNumBytesToTx++] = 0x78;  //12bit resolution, 6 consecutive OOL to trigger O.S.
//             status = I2C_DeviceWrite(handle, i2cAddress, i2cNumBytesToTx, i2cDataSend, &i2cNumBytesTxd,
//                                      I2C_TRANSFER_OPTIONS_START_BIT |
//                                      I2C_TRANSFER_OPTIONS_STOP_BIT |
//                                      I2C_TRANSFER_OPTIONS_BREAK_ON_NACK);

//             if (status != FT_OK)
//             {
//                 status = int("Unable to program the config register for I2C address 0x%1").arg(i2cAddress,2, 16, QChar('0').toUpper()).toUpper();
//                 return status;
//             }

// //            i2cNumBytesToTx = 0;
// //            buffer[i2cNumBytesToTx++] = 0x03; //Change pointer to Tos register
// //            temp_int = (data.DS7505_Tos)*256;
// //            buffer[i2cNumBytesToTx++] = (temp_int*256) & 0xFF;
// //            buffer[i2cNumBytesToTx++] = ((temp_int*256) >> 8) & 0xFF;
// //            status = I2C_DeviceWrite(handle, i2cAddress, i2cNumBytesToTx, i2cDataSend, &i2cNumBytesTxd,
// //                                     I2C_TRANSFER_OPTIONS_START_BIT |
// //                                     I2C_TRANSFER_OPTIONS_STOP_BIT |
// //                                     I2C_TRANSFER_OPTIONS_BREAK_ON_NACK);
// //            if (status != FT_OK)
// //            {
// //                status = int("Unable to program Tos for I2C address 0x%1").arg(i2cAddress,2, 16, QChar('0').toUpper()).toUpper();
// //                return status;
// //            }


// //            i2cNumBytesToTx = 0;
// //            buffer[i2cNumBytesToTx++] = 0x02; //Change pointer to Thyst register
// //            temp_int = (data.DS7505_Hyst)*256;
// //            buffer[i2cNumBytesToTx++] = (temp_int*256) & 0xFF;
// //            buffer[i2cNumBytesToTx++] = ((temp_int*256) >> 8) & 0xFF;
// //            status = I2C_DeviceWrite(handle, i2cAddress, i2cNumBytesToTx, i2cDataSend, &i2cNumBytesTxd,
// //                                     I2C_TRANSFER_OPTIONS_START_BIT |
// //                                     I2C_TRANSFER_OPTIONS_STOP_BIT |
// //                                     I2C_TRANSFER_OPTIONS_BREAK_ON_NACK);
//             if (status != FT_OK)
//             {
//                 status = int("Unable to program Thyst for I2C address 0x%1").arg(i2cAddress,2, 16, QChar('0').toUpper()).toUpper();
//                 return status;
//             }
//         }

//         if (status == FT_OK)
//         {
//             status = 0;
//         }
//         else
//         {
//             status = "Something fucking didn't work";
//         }

//         return status;
//     }

//     int DS7505::setTripPoints(CP2112_HIDAPI *handle,  DS7505_Data &data, QVector<uint8> &i2c_address)
//     {
//         int status;
//         int stringReturn;
//         uint16  temp_int;                        // Temporary variable to store the 16bit value for the Double to uint8_t array conversion
//         uint8_t  i2cAddress = 0x00;               // Var to stor I2C Address
//         uint8_t  buffer[16] = {0x00};        // Initialize a data buffer and set to all Zero
//         uint32_t i2cNumBytesToTx = 0;             // Initialize a counter for the buffer and set to Zero
//         uint32_t i2cNumBytesTxd = 0;              // Initialize another counter for the number of bytes actually sent and set to Zero
//         uint8_t i = 0;                              // Integer for for loop functioninality

//         if (i2c_address.size()>5)
//         {
//             status = "To Many devices found, can only have 4 devices";
//             return status;
//         }

//         if (i2c_address.size()==0)
//         {
//             status = "No I2C Addresses Given";
//             return status;
//         }

//         for(i = 0; i < i2c_address.size(); i++)
//         {
//             i2cAddress = i2c_address[i];

//             if(i2cAddress == 0)
//             {
//                 break;
//             }

//             i2cNumBytesToTx = 0;
//             buffer[i2cNumBytesToTx++] = 0x03;  //Change pointer to Tos register
//             temp_int = (data.DS7505_Tos)*256;       //Bit shift and conversion for the DS7505
//             buffer[i2cNumBytesToTx++] = (temp_int >> 8) & 0xFF;
//             buffer[i2cNumBytesToTx++] = (temp_int >> 0) & 0xFF;
//             status = I2C_DeviceWrite(handle, i2cAddress, i2cNumBytesToTx, i2cDataSend, &i2cNumBytesTxd,
//                                      I2C_TRANSFER_OPTIONS_START_BIT |
//                                      I2C_TRANSFER_OPTIONS_STOP_BIT |
//                                      I2C_TRANSFER_OPTIONS_BREAK_ON_NACK);
//             if (status != FT_OK)
//             {
//                 status = int("Unable to program Tos for I2C address 0x%1").arg(i2cAddress,2, 16, QChar('0').toUpper()).toUpper();
//                 return status;
//             }


//             i2cNumBytesToTx = 0;
//             buffer[i2cNumBytesToTx++] = 0x02;  //Change pointer to Thyst register
//             temp_int = (data.DS7505_Hyst)*256;      //Bit shift and conversion for the DS7505
//             buffer[i2cNumBytesToTx++] = (temp_int >> 8) & 0xFF;
//             buffer[i2cNumBytesToTx++] = (temp_int >> 0) & 0xFF;
//             status = I2C_DeviceWrite(handle, i2cAddress, i2cNumBytesToTx, i2cDataSend, &i2cNumBytesTxd,
//                                      I2C_TRANSFER_OPTIONS_START_BIT |
//                                      I2C_TRANSFER_OPTIONS_STOP_BIT |
//                                      I2C_TRANSFER_OPTIONS_BREAK_ON_NACK);
//             if (status != FT_OK)
//             {
//                 status = int("Unable to program Thyst for I2C address 0x%1").arg(i2cAddress,2, 16, QChar('0').toUpper()).toUpper();
//                 return status;
//             }
//         }

//         if (status == FT_OK)
//         {
//             status = 0;
//         }
//         else
//         {
//             status = "Something fucking didn't work";
//         }

//         return status;
//     }

}
