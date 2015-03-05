import hid
from aifc import data



class cp2112_hidapi:
    def __init__(self):
        self.vid = 0x10C4
        self.pid = 0xEA90
        self.serial = None
        self.device = hid.device()
        
        self.hidstatus = 0x00
        self.i2cstatus = ''
        
        self._reportID = {
            'RESET_DEVICE': 0x01,
            'GETSETGPIOCONFIG': 0x02,
            'GET_GPIO': 0x03,
            'SET_GPIO': 0x04,
            'GET_VER_INFO': 0x05,
            'GETSETSMBUSCONFIG': 0x06,
            
            'DATA_READ': 0x10,
            'DATA_WRITE_READ': 0x11,
            'DATA_READ_FORCE': 0x12,
            'DATA_READ_RESPONSE': 0x13,
            'DATA_WRITE': 0x14,
            'XFER_STATUS_REQ': 0x15,
            'XFER_STATUS_RESPONSE': 0x16,
            'CANCEL_TRANSFER': 0x17,
            
            'USB_LOCK': 0x20,
            'USB_USB_CONFIG': 0x21,
            'USB_MANU_STRING': 0x22,
            'USB_PRODUCT_STRING': 0x23,
            'USB_SERIAL_STRING': 0x24}
        
        self._smbusStatusGeneral = {
            0x00: 'BUS_IDLE',
            0x01: 'BUS_BUSY',
            0x02: 'BUS_GOOD',
            0x03: 'BUS_ERROR'
            }
        
        self._smbusStatusBusy = {
            0x00: 'I2C_ADDR_ACK',
            0x01: 'I2C_ADDR_NACK',
            0x02: 'I2C_RD_PROGRESS',
            0x03: 'I2C_WR_PROGRESS',
            0x05: 'I2C_SUCCESS'
            }
        
        self._smbusStatusError = {
            0x00: 'I2C_TIMEOUT_NACK',
            0x01: 'I2C_TIMEOUT_NF',
            0x02: 'I2C_ARB_LOST',
            0x03: 'I2C_RD_INCOMPLETE',
            0x04: 'I2C_WR_INCOMPLETE',
            0x05: 'I2C_SUCCESS'
            }
        
    
    def device_check(self):
        for y in hid.enumerate():       
            if(self.vid == y['vendor_id']):
                if(self.pid == y['product_id']):
                    return 'true'
                else:
                    None
            else:
                None
        return ''
        
    def open_device(self):
        self.device.open(self.vid, self.pid)
        if(device.error())
            return device.error()
        else:
            return 'Device Opened'
        
    def cp2112_configureGPIO(self):
        buffer[0] = self._reportID['GETSETGPIOCONFIG']
        buffer[1] = 0xFF
        buffer[2] = 0x00
        buffer[3] = 0x06
        buffer[4] = 0x00
        buffer[5] = 0x00
        self.hidstatus = self.device.send_feature_report(buffer)
        return self.hidstatus
    
    def cp2112_configureSMBus(self):
        buffer[00] = self._reportID['GETSETSMBUSCONFIG']
        buffer[01] = 0x00
        buffer[02] = 0x01
        buffer[03] = 0x86
        buffer[04] = 0xA0
        buffer[05] = 0x02
        buffer[06] = 0x00
        buffer[07] = 0x03
        buffer[08] = 0xE8
        buffer[09] = 0x03
        buffer[10] = 0xE8
        buffer[11] = 0x00
        buffer[12] = 0x00
        buffer[13] = 0x00
        self.hidstatus = self.device.send_feature_report(buffer)
        return self.hidstatus
    
    def get_gpio(self, gpio):
        if(not self.device_check()):
            return 'No Device'
        
        buffer[0] = self._reportID['GET_GPIO']
        self.hidstatus = self.device.get_feature_report(buffer, 0x02)
        if(buffer[0] == self._reportID['GET_GPIO']):
            gpio = buffer[1]
            return 'Success'
        else:
            return 'Did not get feature report back'
    
    def set_gpio(self, gpio, mask):
        if(not self.device_check()):
            return 'No Device'
        
        buffer[0] = self._reportID['SET_GPIO']
        buffer[1] = gpio
        buffer[2] = mask
        self.hidstatus = self.device.send_feature_report(buffer, len(buffer))
        return 'Success'
    
    def smbus_write(self, i2cAddress, bytesToSend, data):
        if(not self.device_check()):
            return 'No Device'
        
        buffer[0] = self._reportID['DATA_WRITE']
        buffer[1] = i2cAddress
        buffer[2] = bytesToSend
        buffer[3:] = data[:]
        self.hidstatus = self.device.send_feature_report(buffer, len(buffer))
        return 'Success'
        
    def smbus_read(self, i2cAddress, bytesToRead, data):
        
    def smbus_write_read(self, i2cAddress,bytesToSend, bytesToRead, data):
        
    def exit_device(self):
        
    def xfer_status_response(self, data):
        if(data[0] != self._reportID['XFER_STATUS_RESPONSE']):
            return -1
        
        status1 = self._smbusStatusBusy[data[1]]
        
        if(status1 == 'BUS_IDLE'):
            status2 = self._smbusStatusBusy[data[2]]
        if else(status1 == 'BUS_BUSY'):
            status2 = self._smbusStatusBusy[data[2]]
        if else(status1 == 'BUS_GOOD'):
            status2 = self._smbusStatusError[data[2]]
        if else(status1 == 'BUS_ERROR'):
            status2 = self._smbusStatusError[data[2]]
        else
        
        self.i2cstatus = 'Status 1: ' + status1 + ' Status 2: ' + status2
        
        if(status1 = 'BUS_GOOD' and status2 = 'I2C_SUCCESS'):
            return (data[5] << 8 | data[6])
        
        
        
        
        