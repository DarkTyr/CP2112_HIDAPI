import energy_management_unit
import time


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

status, status1 = emu.device.smbus_write(0xA4, emu.fan.reportlen['PAGE'] + 1, [emu.fan.reportid['PAGE']] + [emu.fan.pageid['PAGE_VOLT0']])
print status, status1
status, status1 = emu.device.smbus_write(0xA4, emu.fan.reportlen['PAGE'] + 1, [emu.fan.reportid['PAGE']] + [emu.fan.pageid['PAGE_VOLT0']])
print status, status1
status, status1 = emu.device.smbus_write(0xF2, emu.fan.reportlen['PAGE'] + 1, [emu.fan.reportid['PAGE']] + [emu.fan.pageid['PAGE_VOLT0']])
print status, status1
status, status1 = emu.device.smbus_write(0xF2, emu.fan.reportlen['PAGE'] + 1, [emu.fan.reportid['PAGE']] + [emu.fan.pageid['PAGE_VOLT0']])
print status, status1

status, status1 = emu.device.smbus_write_read(0x54, 1, 1, [0x00])
print status, status1
status, status1 = emu.device.smbus_write_read(0x54, 1, 1, [0x01])
print status, hex(status1[0])
status, status1 = emu.device.smbus_write_read(0x54, 1, 1, [0x02])
print status, status1

print 'Starting interactions with the Lattice Platform Manager'
for x in xrange(0, 0x0E):
    mux = (1 << 4) + x
    status, status1 = emu.manager.platform_write('ADC_MUX', [mux])
    #print status, status1
    time.sleep(0.25)
    status, data0 = emu.manager.platform_read('ADC_VALUE_LOW')
    status, data1 = emu.manager.platform_read('ADC_VALUE_HIGH')
    voltage = 2/1000.0 * ((data1[0] << 4) + ((data0[0] & 0xF0) >> 4))
    print 'Voltage ADC_MUX = ' + repr(x) + ' : ' + repr(voltage)

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
