import energy_management_unit

print'Creating EMU class with the fan controller as base'
emu = energy_management_unit.MAX31785()
print 'Opening the CP2112 device'
emu.device.open_device()
print 'Configuring the CP2112 device'
emu.device.configure_gpio()
emu.device.configure_smbus()
print 'CP2112 ready for I2C operations'

print 'Set fan controller page to FAN2'
emu.maxPageChange('PAGE_FAN2')
print 'Now to attempt to do a write read'
emu.maxRead('PAGE')
print 'That is all for now folks, closing the HID device'
emu.device.exitDevice()
