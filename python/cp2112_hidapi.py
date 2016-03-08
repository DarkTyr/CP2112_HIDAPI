import hid

class CP2112_HIDAPI:
    def __init__(self):
        self.vid = 0x10C4 #stock CP2112 VID
        self.pid = 0xEA90 #Stock CP2112 PID
        self.serial = None
        self._device = hid.device()
        
        self.hidstatus = 0x00
        self.i2cstatus = ''
        
        self._reportID = {
            'RESET_DEVICE'      : 0x01,
            'GETSETGPIOCONFIG'  : 0x02,
            'GET_GPIO'          : 0x03,
            'SET_GPIO'          : 0x04,
            'GET_VER_INFO'      : 0x05,
            'GETSETSMBUSCONFIG' : 0x06,
            
            'DATA_READ'         : 0x10,
            'DATA_WRITE_READ'   : 0x11,
            'DATA_READ_FORCE'   : 0x12,
            'DATA_READ_RESPONSE': 0x13,
            'DATA_WRITE'        : 0x14,
            'XFER_STATUS_REQ'   : 0x15,
            'XFER_STATUS_RESPONSE': 0x16,
            'CANCEL_TRANSFER'   : 0x17,
            
            'USB_LOCK'          : 0x20,
            'USB_USB_CONFIG'    : 0x21,
            'USB_MANU_STRING'   : 0x22,
            'USB_PRODUCT_STRING': 0x23,
            'USB_SERIAL_STRING' : 0x24
            }
        
        self._smbusStatusGeneral = {
            0x00: 'BUS_IDLE',
            0x01: 'BUS_BUSY',
            0x02: 'BUS_GOOD',
            0x03: 'BUS_ERROR'
            }
        
        self._smbusStatusBusy = {
            0x00: 'I2C_ADDR_ACK',
            0x01: 'I2C_ADDR_NACK',
            0x02: 'I2C_RD_INPROGRESS',
            0x03: 'I2C_WR_INPROGRESS',
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
        return 'could not match VID'
        
    def openDevice(self):
        self._device.open(self.vid, self.pid)
        if(self._device.error()):
            return self._device.error()
        else:
            return 'Device Opened'
        
    def configureGPIO(self):
        if(not self.device_check()):
            return 'No Device Open'
        
        buffer = []
        buffer.append(self._reportID['GETSETGPIOCONFIG'])
        buffer.append(0xFF)
        buffer.append(0x00)
        buffer.append(0x06)
        buffer.append(0x00)
        buffer.append(0x00)
        self.hidstatus = self._device.send_feature_report(buffer)
        return self.hidstatus
    
    def configureSMBus(self):
        if(not self.device_check()):
            return 'No Device Open'
        
        buffer = []
        buffer.append(self._reportID['GETSETSMBUSCONFIG'])
        buffer.append(0x00)
        buffer.append(0x01)
        buffer.append(0x86)
        buffer.append(0xA0)
        buffer.append(0x02)
        buffer.append(0x00)
        buffer.append(0x03)
        buffer.append(0xE8)
        buffer.append(0x03)
        buffer.append(0xE8)
        buffer.append(0x00)
        buffer.append(0x00)
        buffer.append(0x00)
        self.hidstatus = self._device.send_feature_report(buffer)
        return self.hidstatus
    
    def getGPIO(self):
        if(not self.device_check()):
            return 'No Device Open'
        
        buffer = []
        buffer = self._device.get_feature_report(self._reportID['GET_GPIO'],0x02)
        if(buffer[0] == self._reportID['GET_GPIO']):
            gpio = buffer[1]
            return gpio
        else:
            return ''
    
    def setGPIO(self, gpio, mask):
        if(not self.device_check()):
            return 'No Device Open'
        
        buffer = []
        buffer.append(self._reportID['SET_GPIO'])
        buffer.append(gpio)
        buffer.append(mask)
        self.hidstatus = self._device.send_feature_report(buffer, len(buffer))
        if(self.hidstatus > 0):
            return 'Success'
        else:
            return 'Failed to write to Device'
    
    def smbus_write(self, i2cAddress, bytesToSend, data):
        if(not self.device_check()):
            return 'No Device Open', [0x00]
        
        buffer = []
        buffer.append(self._reportID['DATA_WRITE'])
        buffer.append(i2cAddress)
        buffer.append(bytesToSend)

        for i in range(0, bytesToSend):
            buffer.append(data[i])

        self.hidstatus = self._device.write(buffer)
        self.i2cstatus = 'Status 1: BUSS_BUSY Status 2: I2C_WR_INPROGRESS'
        status = 'Status 1: BUSS_BUSY Status 2: I2C_WR_INPROGRESS'
        
        while(self.i2cstatus == status):
            buffer = []
            buffer.append(self._reportID['XFER_STATUS_REQ'])
            buffer.append(0x01)
            self.hidstatus = self._device.write(buffer)
            if(self.hidstatus < 0):
                return 'Unable to write to device', [0x00]
            buffer = self._device.read(0x07)
            self._xfer_status_response(buffer)
            
        if(self.i2cstatus == 'Status 1: BUS_GOOD Status 2: I2C_SUCCESS'):
            return 'Success', [self.i2cstatus]
        else:
            return 'Failed', [0x00]
            
    def smbus_read(self, i2cAddress, bytesToRead, data):
        if(not self.device_check()):
            return 'No Device Open', [0x00]
        
        buffer = []
        buffer.append(self._reportID['DATA_READ'])
        buffer.append(i2cAddress)
        buffer.append((bytesToRead >> 8) & 0xFF)
        buffer.append((bytesToRead >> 0) & 0xFF)
        self.hidstatus = self._device.write(buffer)
        
        self.i2cstatus = 'Status 1: BUS_BUSY Status 2: I2C_WR_INPROGRESS'
        status = 'Status 1: BUS_BUSY Status 2: I2C_WR_INPROGRESS'
        
        while(self.i2cstatus == status):
            buffer = []
            buffer.append(self._reportID['XFER_STATUS_REQ'])
            buffer.append(0x01)
            self.hidstatus = self._device.write(buffer)
            if(self.hidstatus < 0):
                return 'Unable to write to device', [0x00]
            buffer = self._device.read(0x07)
            hidBytesRead = self._xfer_status_response(buffer)
            
        status = 'Status 1: BUS_GOOD Status 2: I2C_SUCCESS'

        data = []
        bytesRead = 0
        while(bytesRead < bytesToRead):
            buffer = []
            buffer.append(self._reportID['DATA_READ_FORCE'])
            buffer.append(0x00)
            buffer.append(0xFF)
            self.hidstatus = self._device.write(buffer)
            
            buffer = self._device.read(0xFF)
            hidBytesRead = self._xfer_status_response(buffer)
            if(buffer[0] == self._reportID['DATA_READ_RESPONSE']):
                if(buffer[2] > 0x00):
                    for x in range(3, buffer[2] + 3):
                        data.append(buffer[x]) 
                        bytesRead += 1
        if(bytesRead == bytesToRead):
            return 'Success', data
        else:
            return 'Fail', [0x00]
        
    def smbus_write_read(self, i2cAddress, bytesToSend, bytesToRead, data):
        if(not self.device_check()):
            return 'No Device Open', [0x00]
        
        buffer = []
        buffer.append(self._reportID['DATA_WRITE_READ'])
        buffer.append(i2cAddress)
        buffer.append((bytesToRead >> 8) & 0xFF)
        buffer.append((bytesToRead >> 0) & 0xFF)
        buffer.append(bytesToSend)

        for i in range(0, bytesToSend):
            buffer.append(data[i])

        self.hidstatus = self._device.write(buffer)

        self.i2cstatus = 'Status 1: BUS_BUSY Status 2: I2C_WR_INPROGRESS'
        status = 'Status 1: BUS_BUSY Status 2: I2C_WR_INPROGRESS'

        while(self.i2cstatus == status):
            buffer = []
            buffer.append(self._reportID['XFER_STATUS_REQ'])
            buffer.append(0x01)
            self.hidstatus = self._device.write(buffer)
            if(self.hidstatus < 0):
                return 'Unable to write to device', [0x00]
            buffer = self._device.read(0x07)
            hidBytesRead = self._xfer_status_response(buffer)

        status = 'Status 1: BUS_GOOD Status 2: I2C_SUCCESS'
        #if(bytesToRead != hidBytesRead):
        #    return 'Was not able to read all of the Bytes', [self.i2cstatus]
        bytesRead = 0
        
        data = []
        while(bytesRead < bytesToRead):
            buffer = []
            buffer.append(self._reportID['DATA_READ_FORCE'])
            buffer.append(0x00)
            buffer.append(0xFF)
            self.hidstatus = self._device.write(buffer)

            buffer = self._device.read(0xFF)
            hidBytesRead = self._xfer_status_response(buffer)
            if(buffer[0] == self._reportID['DATA_READ_RESPONSE']):
                if(buffer[2] > 0x00):
                    for x in range(3, buffer[2] + 3):
                        data.append(buffer[x])
                        bytesRead += 1
                        
        if(bytesRead == bytesToRead):
            return 'Success', data
        else:
            return 'Fail', [0x00]
        
    def exitDevice(self):
        self._device.close()
        
    def _xfer_status_response(self, data):
        if(data[0] != self._reportID['XFER_STATUS_RESPONSE']):
            return -1
        
        status1 = self._smbusStatusGeneral[data[1]]
        
        if(status1 == 'BUS_IDLE'):
            status2 = self._smbusStatusBusy[data[2]]
        elif (status1 == 'BUS_BUSY'):
            status2 = self._smbusStatusBusy[data[2]]
        elif (status1 == 'BUS_GOOD'):
            status2 = self._smbusStatusError[data[2]]
        elif (status1 == 'BUS_ERROR'):
            status2 = self._smbusStatusError[data[2]]
        else:
            return -1
        
        self.i2cstatus = 'Status 1: ' + status1 + ' Status 2: ' + status2
        
        if((status1 == 'BUS_GOOD') and (status2 == 'I2C_SUCCESS')):
            return (data[5] << 8 | data[6])
        else:
            return 1
