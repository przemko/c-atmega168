DEVICE     = m168
CLOCK      = 8000000
PROGRAMMER = -c usbasp -P /dev/tty.usbmodem1421
OBJECTS    = main.o twi.o matrix8x8.o
FUSES      = -U hfuse:w:0xd9:m -U lfuse:w:0x24:m

AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-gcc -std=c99 -Wall -Os -DF_CPU=$(CLOCK) -mmcu=atmega168

# symbolic targets:
all:	main.hex

.c.o:
	$(COMPILE) -c $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:main.hex:i

clean:
	rm -f main.hex main.elf $(OBJECTS) *~

main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=$(DEVICE) main.elf
