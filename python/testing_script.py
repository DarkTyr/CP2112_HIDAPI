import cp2112_hidapi
print 'creating device object for interaction'
device = cp2112_hidapi.CP2112_HIDAPI()
device.device_check()
device.open_device()
device.configure_gpio()
print 'configured the GPIO'
device.configure_smbus()
print 'configured the SMBus parameters'
status, data = device.smbus_write(0xA4, 2, [0x00, 0x00])
status, data = device.smbus_write_read(0xA4, 1, 20, [0xF2])
print 'Read MFR_FAN_LUT for fan channel 0'
print 'Status: ' + status
print 'Data'
print data
for x in range(len(data)/2):
    print hex((data[x * 2 + 1] << 8)|(data[x * 2] << 0)), (data[x * 2 + 1] << 8)|(data[x * 2] << 0)

status, data = device.smbus_write(0xA4, 2, [0x00, 0x00])
status, data = device.smbus_write_read(0xA4, 1, 2, [0x90])
print 'Fan0 RPM: ' + repr((data[1] << 8)|(data[0] << 0))

status, data = device.smbus_write(0xA4, 2, [0x00, 0x01])
status, data = device.smbus_write_read(0xA4, 1, 2, [0x90])
print 'Fan1 RPM: ' + repr((data[1] << 8)|(data[0] << 0))

status, data = device.smbus_write(0xA4, 2, [0x00, 0x02])
status, data = device.smbus_write_read(0xA4, 1, 2, [0x90])
print 'Fan2 RPM: ' + repr((data[1] << 8)|(data[0] << 0))

status, data = device.smbus_write(0xA4, 2, [0x00, 0x03])
status, data = device.smbus_write_read(0xA4, 1, 2, [0x90])
print 'Fan3 RPM: ' + repr((data[1] << 8)|(data[0] << 0))

status, data = device.smbus_write(0xA4, 2, [0x00, 0x04])
status, data = device.smbus_write_read(0xA4, 1, 2, [0x90])
print 'Fan4 RPM: ' + repr((data[1] << 8)|(data[0] << 0))

status, data = device.smbus_write(0xA4, 2, [0x00, 0x05])
status, data = device.smbus_write_read(0xA4, 1, 2, [0x90])
print 'Fan5 RPM: ' + repr((data[1] << 8)|(data[0] << 0))

status, data = device.smbus_write(0xA4, 2, [0x00, 0x06])
status, data = device.smbus_write_read(0xA4, 1, 2, [0x8D])
temp = (data[1] << 8)|(data[0] << 0)
print 'Internal Temp: ' + repr(temp/100.0)

status, data = device.smbus_write(0xA4, 2, [0x00, 0x07])
status, data = device.smbus_write_read(0xA4, 1, 2, [0x8D])
temp = (data[1] << 8)|(data[0] << 0)
print 'Temp0 Temp: ' + repr(temp/100.0)

status, data = device.smbus_write(0xA4, 2, [0x00, 0x08])
status, data = device.smbus_write_read(0xA4, 1, 2, [0x8D])
temp = (data[1] << 8)|(data[0] << 0)
print 'Temp1 Temp: ' + repr(temp/100.0)

status, data = device.smbus_write(0xA4, 2, [0x00, 0x0C])
status, data = device.smbus_write_read(0xA4, 1, 2, [0x8D])
temp = (data[1] << 8)|(data[0] << 0)
print 'I2C0 Temp: ' + repr(temp/100.0)

status, data = device.smbus_write(0xA4, 2, [0x00, 0x0D])
status, data = device.smbus_write_read(0xA4, 1, 2, [0x8D])
temp = (data[1] << 8)|(data[0] << 0)
print 'I2C1 Temp: ' + repr(temp/100.0)

status, data = device.smbus_write(0xA4, 2, [0x00, 0x0E])
status, data = device.smbus_write_read(0xA4, 1, 2, [0x8D])
temp = (data[1] << 8)|(data[0] << 0)
print 'I2C2 Temp: ' + repr(temp/100.0)

status, data = device.smbus_write(0xA4, 2, [0x00, 0x0F])
status, data = device.smbus_write_read(0xA4, 1, 2, [0x8D])
temp = (data[1] << 8)|(data[0] << 0)
print 'I2C3 Temp: ' + repr(temp/100.0)

