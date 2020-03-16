# c-atmega168
Przykłady programów w języku C na mikrokontroler ATmega168.

```bash
sudo apt install gcc-avr avr-libc avrdude

cd c-atmega128
sudo cp etc/udev/rules.d/usbasp.rules /etc/udev/rules.d
sudo udevadm control --reload-rules
sudo udevadm trigger

cd src
make 
cd ..
cd examples/NAME
make
make flash
make clean
```

