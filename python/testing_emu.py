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
    time.sleep(0.001)
    status, data0 = emu.manager.platform_read('ADC_VALUE_LOW')
    status, data1 = emu.manager.platform_read('ADC_VALUE_HIGH')
    voltage = 2/1000.0 * ((data1[0] << 4) + ((data0[0] & 0xF0) >> 4))
    print 'Voltage ADC_MUX = ' + repr(x) + ' : ' + repr(voltage)


voltages = emu.manager.read_mux()
for x in xrange(0, 0x0E):
    print emu.manager.mux_str_decode[x], voltages[x]

data_high, string_high = emu.manager.input_to_high()
data_low, string_low = emu.manager.input_to_low()

print data_high
print data_low
for x in xrange(0, 4):
    if(data_high[x] == 1):
        print 'Turn down the voltage on ' + string_high[x]
    if(data_low[x] == 1):
        print 'Turn up the voltage on ' + string_low[x]


status, data = emu.manager.platform_read('VMON_STATUS1')
print bin(data[0]), hex(data[0])
print 'That is all for now folks, closing the HID device'
emu.device.exit_device()
