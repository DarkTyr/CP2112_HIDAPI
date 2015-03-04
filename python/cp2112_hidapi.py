import hid



class cp2112_hidapi:
    def __init__(self):
        self.vid = 0x10C4
        self.pid = 0xEA90
        self.device = hid.device()
        
        self.hidstatus
        self.i2cstatus
        
        self._reportID = {
                          'RESET_DEVICE': 0x01,
                          'GETSETGPIOCONFIG': 0x02,
                          'GET_GPIO': 0x03,
                          'SET_GPIO': 0x04,
                          'GET_VER_INFO': 0x05,
                          'GETSETSMBUDCONFIG': 0x06,
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
        self._smbusStatus = {0x1: 'I2C_ACK',
                             0x2: 'I2C_NACK'
                             }
    
    def device_check(self):
        
    def open_device(self):
        device.open(self.vid, self.pid)
        