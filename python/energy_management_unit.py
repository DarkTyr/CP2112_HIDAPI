import cp2112_hidapi

class Energy_Management_Unit:
    def __init__(self):
        self.device = cp2112_hidapi.CP2112_HIDAPI()
        self.fan = MAX31785()
        self.manager = LPTM10()
        self.fan.device = self.device
        # self.manager.device = self._device

    def init_device(self):

        if(self.device.open_device()):
            self.device.configure_gpio()
            self.device.configure_smbus()
            print 'Device has been opened and configured'
        else:
            print 'Device was not found'
            return -1

    def exit_device(self):
        self.device.exit_device()
        print 'Device has been closed'

    def read_temps(self):
        temps = []

        '''Diode Temps first'''
        status, data = self.fan.maxRead('READ_TEMPERATURE', 'PAGE_TEMP_DIODE0')
        if status != 'Success':
            return [-1]
        temps.append(((data[1] << 8) | (data[0] << 0))/100.0)
        if status != 'Success':
            return [-1]
        status, data = self.fan.maxRead('READ_TEMPERATURE', 'PAGE_TEMP_DIODE1')
        if status != 'Success':
            return [-1]
        temps.append(((data[1] << 8) | (data[0] << 0))/100.0)
        '''Internal Temp of the Fan controller'''
        status, data = self.fan.maxRead('READ_TEMPERATURE', 'PAGE_TEMP_INT')
        if status != 'Success':
            return [-1]
        temps.append(((data[1] << 8) | (data[0] << 0))/100.0)
        '''Remote I2C temp sensors'''
        status, data = self.fan.maxRead('READ_TEMPERATURE', 'PAGE_TEMP_I2C0')
        if status != 'Success':
            return [-1]
        temps.append(((data[1] << 8) | (data[0] << 0))/100.0)
        status, data = self.fan.maxRead('READ_TEMPERATURE', 'PAGE_TEMP_I2C1')
        if status != 'Success':
            return [-1]
        temps.append(((data[1] << 8) | (data[0] << 0))/100.0)
        status, data = self.fan.maxRead('READ_TEMPERATURE', 'PAGE_TEMP_I2C2')
        if status != 'Success':
            return [-1]
        temps.append(((data[1] << 8) | (data[0] << 0))/100.0)
        status, data = self.fan.maxRead('READ_TEMPERATURE', 'PAGE_TEMP_I2C3')
        if status != 'Success':
            return [-1]
        temps.append(((data[1] << 8) | (data[0] << 0))/100.0)

        return temps

    def read_fans(self):
        rpm = []

        status, data = self.fan.maxRead('READ_FAN_SPEED_1_2', 'PAGE_FAN0')
        if status != 'Success':
            return [-1]
        rpm.append((data[1] << 8) | (data[0] << 0))
        status, data = self.fan.maxRead('READ_FAN_SPEED_1_2', 'PAGE_FAN1')
        if status != 'Success':
            return [-1]
        rpm.append((data[1] << 8) | (data[0] << 0))
        status, data = self.fan.maxRead('READ_FAN_SPEED_1_2', 'PAGE_FAN2')
        if status != 'Success':
            return [-1]
        rpm.append((data[1] << 8) | (data[0] << 0))
        status, data = self.fan.maxRead('READ_FAN_SPEED_1_2', 'PAGE_FAN3')
        if status != 'Success':
            return [-1]
        rpm.append((data[1] << 8) | (data[0] << 0))
        status, data = self.fan.maxRead('READ_FAN_SPEED_1_2', 'PAGE_FAN4')
        if status != 'Success':
            return [-1]
        rpm.append((data[1] << 8) | (data[0] << 0))
        status, data = self.fan.maxRead('READ_FAN_SPEED_1_2', 'PAGE_FAN5')
        if status != 'Success':
            return [-1]
        rpm.append((data[1] << 8) | (data[0] << 0))

        return rpm


class MAX31785:
    def __init__(self):
        self.device = cp2112_hidapi.CP2112_HIDAPI()
        self.mfr = 'Maxim Integrated'
        self.address = 0xA4
        self.reportid = {
            'PAGE'                  : 0x00,
            'CLEAR_FAULTS'          : 0x03,
            'WRITE_PROTECT'         : 0x10,
            'STORE_DEFAULT_ALL'     : 0x11,
            'RESTORE_DEFAULT_ALL'   : 0x12,
            'CAPABILITY'            : 0x19,

            'VOUT_MODE'             : 0x20,
            'VOUT_SCALE_MONITOR'    : 0x2A,

            'FAN_CONFIG_1_2'        : 0x3A,
            'FAN_COMMAND_1'         : 0x3B,

            'VOUT_OV_FAULT_LIMIT'   : 0x40,
            'VOUT_OV_WARN_LIMIT'    : 0x42,
            'VOUT_UV_WARN_LIMIT'    : 0x43,
            'VOUT_UV_FAULT_LIMIT'   : 0x44,
            'OT_FAULT_LIMIT'        : 0x4F,
            'OT_WARN_LIMIT'         : 0x51,

            'STATUS_BYTE'           : 0x78,
            'STATUS_WORD'           : 0x79,
            'STATUS_VOUT'           : 0x7A,
            'STATUS_CML'            : 0x7E,
            'STATUS_MFR_SPECIFIC'   : 0x80,

            'READ_VOUT'             : 0x8B,
            'READ_TEMPERATURE'      : 0x8D,
            'READ_FAN_SPEED_1_2'    : 0x90,

            'PMBUS_REVISION'        : 0x98,
            'MFR_ID'                : 0x99,
            'MFR_MODEL'             : 0x9A,
            'MFR_REVISION'          : 0x9B,
            'MFR_LOCATION'          : 0x9C,
            'MFR_DATE'              : 0x9D,
            'MFR_SERIAL'            : 0x9E,
            'MFR_MODE'              : 0xD1,

            'MFR_VOUT_PEAK'         : 0xD4,
            'MFR_TEMPERATURE_PEAK'  : 0xD6,   
            'MFR_VOUT_MIN'          : 0xD7,
            'MFR_FAULT_RESPONSE'    : 0xD9,
            'MFR_NV_FAULT_LOG'      : 0xDC,
            'MFR_TIME_COUNT'        : 0xDD,
            'MFR_TEMP_SENSOR_CONFIG': 0xF0,
            'MFR_FAN_CONFIG'        : 0xF1,
            'MFR_FAN_LUT'           : 0xF2,
            'MFR_READ_FAN_PWM'      : 0xF3,
            'MFR_FAN_FAULT_LIMIT'   : 0xF5,
            'MFR_FAN_WARN_LIMIT'    : 0xF6,
            'MFR_FAN_RUN_TIME'      : 0xF7,
            'MFR_FAN_PWM_AVG'       : 0xF8,
            'MFR_FAN_PWM2RPM'       : 0xF9
            }

        self.reportlen = {
            'PAGE'                  : 0x01,
            'CLEAR_FAULTS'          : 0x00,
            'WRITE_PROTECT'         : 0x01,
            'STORE_DEFAULT_ALL'     : 0x00,
            'RESTORE_DEFAULT_ALL'   : 0x00,
            'CAPABILITY'            : 0x01,

            'VOUT_MODE'             : 0x01,
            'VOUT_SCALE_MONITOR'    : 0x02,

            'FAN_CONFIG_1_2'        : 0x01,
            'FAN_COMMAND_1'         : 0x02,

            'VOUT_OV_FAULT_LIMIT'   : 0x02,
            'VOUT_OV_WARN_LIMIT'    : 0x02,
            'VOUT_UV_WARN_LIMIT'    : 0x02,
            'VOUT_UV_FAULT_LIMIT'   : 0x02,
            'OT_FAULT_LIMIT'        : 0x02,
            'OT_WARN_LIMIT'         : 0x02,

            'STATUS_BYTE'           : 0x01,
            'STATUS_WORD'           : 0x02,
            'STATUS_VOUT'           : 0x01,
            'STATUS_CML'            : 0x01,
            'STATUS_MFR_SPECIFIC'   : 0x01,

            'READ_VOUT'             : 0x02,
            'READ_TEMPERATURE'      : 0x02,
            'READ_FAN_SPEED_1_2'    : 0x02,

            'PMBUS_REVISION'        : 0x01,
            'MFR_ID'                : 0x01,
            'MFR_MODEL'             : 0x01,
            'MFR_REVISION'          : 0x02,
            'MFR_LOCATION'          : 0x08,
            'MFR_DATE'              : 0x08,
            'MFR_SERIAL'            : 0x08,
            'MFR_MODE'              : 0x02,

            'MFR_VOUT_PEAK'         : 0x02,
            'MFR_TEMPERATURE_PEAK'  : 0x02,   
            'MFR_VOUT_MIN'          : 0x02,
            'MFR_FAULT_RESPONSE'    : 0x01,
            'MFR_NV_FAULT_LOG'      : 0xFF,
            'MFR_TIME_COUNT'        : 0x04,
            'MFR_TEMP_SENSOR_CONFIG': 0x02,
            'MFR_FAN_CONFIG'        : 0x02,
            'MFR_FAN_LUT'           : 0x20,
            'MFR_READ_FAN_PWM'      : 0x02,
            'MFR_FAN_FAULT_LIMIT'   : 0x02,
            'MFR_FAN_WARN_LIMIT'    : 0x02,
            'MFR_FAN_RUN_TIME'      : 0x02,
            'MFR_FAN_PWM_AVG'       : 0x02,
            'MFR_FAN_PWM2RPM'       : 0x08
            }

        self.pageid = {
            'PAGE_FAN0'             : 0x00,
            'PAGE_FAN1'             : 0x01,
            'PAGE_FAN2'             : 0x02,
            'PAGE_FAN3'             : 0x03,
            'PAGE_FAN4'             : 0x04,
            'PAGE_FAN5'             : 0x05,

            'PAGE_TEMP_DIODE0'      : 0x06,
            'PAGE_TEMP_DIODE1'      : 0x07,
            'PAGE_TEMP_DIODE2'      : 0x08,
            'PAGE_TEMP_DIODE3'      : 0x09,
            'PAGE_TEMP_DIODE4'      : 0x0A,
            'PAGE_TEMP_DIODE5'      : 0x0B,
            'PAGE_TEMP_INT'         : 0x0C,

            'PAGE_TEMP_I2C0'        : 0x0D,
            'PAGE_TEMP_I2C1'        : 0x0E, 
            'PAGE_TEMP_I2C2'        : 0x0F,
            'PAGE_TEMP_I2C3'        : 0x10,
            
            'PAGE_VOLT0'            : 0x11,
            'PAGE_VOLT1'            : 0x12,
            'PAGE_VOLT2'            : 0x13,
            'PAGE_VOLT3'            : 0x14,
            'PAGE_VOLT4'            : 0x15,
            'PAGE_VOLT5'            : 0x16,
            
            'PAGE_ALL'              : 0xFF
            }

        self.invpageid = {v: k for k, v in self.pageid.items()}

    def maxPageChange(self, pagestr):
        status, data = self.device.smbus_write(self.address, self.reportlen['PAGE'] + 1, [self.reportid['PAGE']]
                                                  + [self.pageid[pagestr]])
        return status, data

    def maxWrite(self, reportstr, data):
        if(len(data) != self.reportlen[reportstr]):
            return 'Wrong amount of data for the report', [0x00]
        else:
            status, data = self.device.smbus_write(self.address, self.reportlen[reportstr] + 1, [self.reportid[reportstr]] + data)

        return status, data

    def maxRead(self, reportstr, pagestr = ''):
        if(pagestr == ''):
            status, data = self.device.smbus_write_read(self.address, 0x01, self.reportlen[reportstr], [self.reportid[reportstr]])
        else:
            status, data = self.device.smbus_write(self.address, self.reportlen['PAGE'] + 1, [self.reportid['PAGE']]
                                                  + [self.pageid[pagestr]])
            if(status != 'Success'):
                print 'A problem occurred during write: ' + status
                return status, [0x00]

            status, data = self.device.smbus_write_read(self.address, 0x01, self.reportlen[reportstr], [self.reportid[reportstr]])

        if(reportstr == 'PAGE'):
            data = self.invpageid[data[0]]

        return status, data
    

class LPTM10:
    def __init__(self):
        self.device = cp2112_hidapi.CP2112_HIDAPI()
        self.mfr = 'Lattice Semiconductor'
        self.address = 0x54  # Configured at firmware compilation
        self.reportid = {
            'VMON_STATUS0'  : 0x00,
            'VMON_STATUS1'  : 0x01,
            'VMON_STATUS2'  : 0x02,
            'OUTPUT_STATUS0': 0x03,
            'OUTPUT_STATUS1': 0x04,
            'OUTPUT_STATUS2': 0x05,
            
            'INPUT_STATUS'  : 0x06,
            'ADC_VALUE_LOW' : 0x07,
            'ADC_VALUE_HIGH': 0x08,
            'ADC_MUX'       : 0x09,
            'UES_BYTE0'     : 0x0A,
            'UES_BYTE1'     : 0x0B,
            'UES_BYTE2'     : 0x0C,
            'UES_BYTE3'     : 0x0D,
            
            'GP_OUTPUT1'    : 0x0E,
            'GP_OUTPUT2'    : 0x0F,
            'GP_OUTPUT3'    : 0x10,
            'INPUT_VALUE'   : 0x11,
            'RESET'         : 0x12,
            
            'TRIM1_TRIM'    : 0x13,
            'TRIM2_TRIM'    : 0x14,
            'TRIM3_TRIM'    : 0x15,
            'TRIM4_TRIM'    : 0x16,
            'TRIM5_TRIM'    : 0x17,
            'TRIM6_TRIM'    : 0x18,
            'TRIM7_TRIM'    : 0x19,
            'TRIM8_TRIM'    : 0x1A
            }
        self.reportlen = 1

    def platformWrite(self):
        status, data = self.device.smbus_write_read(self.address, self.reportlen + 1, [self.reportid['PAGE']])

    def platformRead(self):
        return None