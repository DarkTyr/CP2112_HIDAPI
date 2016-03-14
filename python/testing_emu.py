import energy_management_unit

print'Creating EMU class with the fan controller as base'
emu = energy_management_unit.Energy_Management_Unit()
print 'Opening the CP2112 device and configuring the device'
emu.init_device()
print 'Get the Fan controller temperatures in Celsius'
temps = emu.read_temps()
print temps
rpm = emu.read_fans()
print rpm

# print 'Trying to find i2C devices on the bus'

status, status1 = emu.device.smbus_write(0xA4, emu.fan.reportlen['PAGE']+1, [emu.fan.reportid['PAGE']]+[emu.fan.pageid['PAGE_VOLT0']])
print status, status1
status, status1 = emu.device.smbus_write(0xA4, emu.fan.reportlen['PAGE']+1, [emu.fan.reportid['PAGE']]+[emu.fan.pageid['PAGE_VOLT0']])
print status, status1
status, status1 = emu.device.smbus_write(0xF2, emu.fan.reportlen['PAGE']+1, [emu.fan.reportid['PAGE']]+[emu.fan.pageid['PAGE_VOLT0']])
print status, status1
status, status1 = emu.device.smbus_write(0xF2, emu.fan.reportlen['PAGE']+1, [emu.fan.reportid['PAGE']]+[emu.fan.pageid['PAGE_VOLT0']])
print status, status1
#
#
# for x in range(1,256):
#     status, status1 = emu.device.smbus_write(x, 2, [0x00, 0x00])
#     print status, status1, hex(x)
#     if status == 'Success':
#         print 'Found i2C device at address: ' + hex(x)
#     if status1 == 'Status 1: BUS_GOOD Status 2: I2C_SUCCESS':
#         print 'Found i2C device at address: ' + hex(x)


print 'That is all for now folks, closing the HID device'
emu.device.exit_device()
