DEVICE     = m168
CLOCK      = 8000000
OBJECTS    = twi.o matrix8x8.o

COMPILE = avr-gcc -std=c99 -Wall -Os -DF_CPU=$(CLOCK) -mmcu=atmega168 -I../include

# symbolic targets:
all:	install

install: $(OBJECTS)
	mkdir -p ../obj
	mv $(OBJECTS) ../obj

.c.o:
	$(COMPILE) -c $< -o $@

clean:
	rm -f $(OBJECTS) *~
