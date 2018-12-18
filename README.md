CP2112_HIDAPI
=============

Cross-platform CP2112 Driver based on signal11's HIDAPI work and 
gbishop's/trezor cython-hidapi work.

The C++ version of the interface seems to work great still. After some more work with CP2112_hidapi I believe it is in a functioning state. I have mainly used it on i2c devices that are located on the Energy Management Unit (EMU) that I have (MAX31785 fan controller and Lattice LPTM10 platform power controller). Under the testing/console/ folder I have been able to interface to these two devices very reliably. I have no used anything cross platform as of yet. The emu_console folder has only been used on Linux thus far (Ubuntu 16.04). This was also my first foray into writing my own Makefile. 

I have not worked with the python interface yet and may not get time.

Work in Progress