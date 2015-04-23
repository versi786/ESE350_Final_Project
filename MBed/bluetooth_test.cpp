#include "mbed.h"

// the mbed will be the master and the ble module will be the slave
SPI spi(p5, p6, p7); // mosi, miso, sck
DigitalOut chip_select(p8); // slave chip select -- active low
DigitalIn ready(p9); // slave ready to read -- active high
DigitalIn active(p10); // slave busy -- active high

int main() {
    int send = 0;
    int received = 0;
    chip_select = 1;
    spi.format(4, 1);
    spi.frequency(1000000);
    while (1) {
        send = 0;
        if (active.read() == 0 && ready.read() == 0) {
            chip_select = 0;
            received = spi.write(send);
            chip_select = 1;
            printf("%01x\n", received);
        }
    }
}
