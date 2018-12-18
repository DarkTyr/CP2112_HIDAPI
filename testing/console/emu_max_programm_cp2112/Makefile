#
# This is an example Makefile for a countwords program.  This
# program uses both the scanner module and a counter module.
# Typing 'make' or 'make count' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = g++
CFLAGS  = -g -Wall -std=c++11
INC_DIR = -I../../../include
LIB_LINK = -ludev

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: all

all:  hid.o cp2112_hidapi.o maxim_ic_lib.o emu_program emu_housekeeping

hid.o:
	$(CC) $(CFLAGS) $(INC_DIR) -fpermissive -c  ../../../src/linux/hid.c

cp2112_hidapi.o:
	$(CC) $(CFLAGS) $(INC_DIR) -c ../../../src/cp2112_hidapi.cpp

maxim_ic_lib.o:
	$(CC) $(CFLAGS) $(INC_DIR) -c maxim_ic_lib.cpp

emu_program.o:
	$(CC) $(CFLAGS) $(INC_DIR) -c emu_program.cpp

emu_housekeeping.o:
	$(CC) $(CFLAGS) $(INC_DIR) -c emu_housekeeping.cpp

emu_program: emu_program.o
	$(CC) $(CFLAGS) $(INC_DIR) -o emu_program emu_program.o maxim_ic_lib.o cp2112_hidapi.o hid.o $(LIB_LINK)

emu_housekeeping: emu_housekeeping.o
	$(CC) $(CFLAGS) $(INC_DIR) -o emu_housekeeping emu_housekeeping.o maxim_ic_lib.o cp2112_hidapi.o hid.o $(LIB_LINK)

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) emu_max_programm_cp2112  *.o *~