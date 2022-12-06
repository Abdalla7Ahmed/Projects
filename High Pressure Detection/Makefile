###########################
# High Pressure Detection #
#   Abdallah Abotaleb     #
###########################

# tool chain
CC = arm-none-eabi-

# microprocessor
CFLAGS =-mcpu=cortex-m3 -gdwarf-2

# includes
INCS = -I .

# liberaries
LIBS =

# any .c files get its .o	
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

# any .s files get its .o
AS_SRC = $(wildcard *.s)
AS_OBJ = $(AS_SRC:.s=.o)

# project name#
project_name =High_Pressure_Detection


# $< : dependense 
# $@ : target     


all: $(project_name).bin

%.o: %.s
	$(CC)as.exe $(CFLAGS) $< -o $@
	
	
%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@

$(project_name).elf: $(OBJ) $(AS_OBJ)
	$(CC)ld.exe -T linker_script.ld $(OBJ) $(AS_OBJ) -o $@ -Map=map_file.map

$(project_name).bin: $(project_name).elf
	$(CC)objcopy.exe -O binary $< $@
