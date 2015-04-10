#include "mbed.h"
#include "math.h"
#include "stdio.h"

Serial pc(USBTX, USBRX);

Timer timer;
Ticker emg;
Ticker accelerometer;

AnalogIn emg_pin(p20);
AnalogIn accel(p17);

int emg_buffer[5000];
int emg_position;

char start_buffer[128];
char empty_buffer[128];
static int iteration = -1;

int chewing_threshold = 40000;

void emg_isr() {
    emg_buffer[emg_position++] = emg_pin.read_u16();
//    pc.printf("%d\r\n", emg_1.read_u16());
}

void accel_isr() {
    pc.printf("%d\r\n", accel.read_u16());
}

void emg_flush() {
    for (int i = 0; i < 5000; i++) {
        pc.printf("%d, %d\r\n", iteration, emg_buffer[i]);
    }
    emg_position = 0;
}



int main() {
    int flag1 = 1;
    int flag2 = 1;
    emg_position = 0;
    iteration++;

    timer.start();
    //emg.attach(&emg_isr, .001);
    //accelerometer.attach(&accel_isr, .005);
    flag1 = 1;

    while (flag1) {
        if (pc.readable()) {
            pc.scanf("%s", start_buffer);
        }
        //printf("%d", strcmp(start_buffer , "start"));
        if (strcmp(start_buffer , "start") == 0) {
             //pc.printf("%s\r\n", start_buffer);
             strcpy(start_buffer, empty_buffer);
             emg.attach(&emg_isr, .001);
             flag1 = 0;
        }
    }
    flag2 = 1;
    while (flag2) {
        // measure accelerometer data
//        if (accel.read_u16() > chewing_threshold) {
//            pc.printf("Chewing: %d\r\n", accel.read_u16());
//        } else {
//            pc.printf("Resting: %d\r\n", accel.read_u16());
//        }
        if (emg_position > 4999) {
            emg.detach();
            emg_flush();
            //emg.attach(&emg_isr, .001);
            //break;
            //flag2 = 0;
            main();
        }
    }
    pc.printf("done");
    return 1;
}

//int main() {
//    main_function();
//    return 1;
//}