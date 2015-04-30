#include "mbed.h"
#include <stdio.h>
#include <map>
#include "math.h"
#include <Serial.h>

using namespace std;
#define EMG_BUFFER_LENGTH 2000
#define CHEW_BUFFER_LENGTH 22

DigitalOut myled(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);
DigitalOut motor(p5);

Serial pc(USBTX, USBRX);
Serial bluetooth(p28, p27); // Bluetooth tx, rx

Timer timer;
Ticker emg;
Ticker accelerometer;
AnalogIn emg_pin(p20);

int emg_buffer[EMG_BUFFER_LENGTH];
int emg_position;

int chew_buffer[CHEW_BUFFER_LENGTH]; //3 seconds of data;
int chew_position;

void emg_isr() {
    emg_buffer[emg_position] = emg_pin.read_u16();
    emg_position = (emg_position + 1) % EMG_BUFFER_LENGTH;
    // pc.printf("%d\r\n", emg_pin.read_u16());
}


void chew_place(int classification) {
    chew_buffer[chew_position] = classification;
    chew_position = (chew_position + 1) % CHEW_BUFFER_LENGTH;
}

void chew_test(){
    char c = 0;
    int count = 0;
    int flag = 1;
    for(int i = 0; i < CHEW_BUFFER_LENGTH; i++){
        count += chew_buffer[i];
    }
    if(count > 8){ // 3 chews, because chews span over multiple windows
        emg.detach();
        motor = 1;
        myled3 = 1;
        while (flag){
            if (bluetooth.readable()) {
               while(bluetooth.readable()){
                    c = bluetooth.getc();
                    pc.printf("recieved: %c\r\n", c);
                    if (c == 'k') {
                        motor = 0;
                        myled3 = 0;
                        myled = 0;
                        flag = 0;
                        myled4 = 1;
                        wait(5);
                        myled4 = 0;
                    }
                }
            }
        }
        for(int i = 0; i < CHEW_BUFFER_LENGTH; i++){
            chew_buffer[i] = 0;
        }
        emg.attach(&emg_isr, .001);
    }
}

int maxArr(int start, int end, int length){
    int max = -4000000;
    for(int i = start; i < end; i++){
        if(max < emg_buffer[i]){
            max = emg_buffer[i];
        }
    }
    return max;
}

int minArr(int start, int end, int length){
    int min = 4000000;
    for(int i = start; i < end; i++){
        if(min > emg_buffer[i]){
            min = emg_buffer[i];
        }
    }
    return min;
}

double log2( double number ) {
   return log(number) / log(2.0) ;
}

double entropyArr (int start, int end, int length) {
   std::map<int, int> frequencies ;
   for (int i = start ; i < end; i++){
        frequencies[emg_buffer[i]]++;
   }
   double infocontent = 0;
   
   for (std::map<int,int>::iterator it = frequencies.begin(); it != frequencies.end(); it++) {
      std::pair<int , int> p = *it;
      double freq = static_cast<double>(p.second) / length;
      infocontent += freq * log2(freq);
   }
   infocontent *= -1 ;
   return infocontent;
}

int distanceArr(int start, int end, int length){
    int total = 0;
    int temp = 0;
    for(int i = start; i < end - 1; i++){
        temp = emg_buffer[i] -emg_buffer[i+1];
        if(temp < 0){
            temp = -temp;
        }
        total += temp;
    }
    return total/(length-1);
}

int classify(int start, int end, int length) {
    double entropy = entropyArr(start, end, length);
    int max = maxArr(start, end, length);
    int min = minArr(start, end, length);
    int distance = distanceArr(start, end, length);
    if(max < 2320){
        return 0;
    }
    if(entropy <= 6.505481){
        return 0;
    }else{
        if(entropy <= 6.810452){
            if(distance <= 4418){
                if(min <= -9506){
                    if(min <= -11714){
                        return 1;
                    }else{
                        if(max <= 18372){
                            return 0;
                        }else{
                            return 1;
                        }
                    }
                }else{
                    return 1;
                }
            }else{
                if(distance <= 4485){
                    return 0;
                }else{
                    if(max <= 19332){
                        return 0;
                    }else{
                        return 1;
                    }
                }
            }
        }else{
            return 1;
        }
    }

}




int main() {
    int window = 250;
    int displacement = 125;
    int classification;
    int cur_position = window;
    bluetooth.baud(115200);
    timer.start();
    emg.attach(&emg_isr, .001);
    
    while(1) {
        if((cur_position == EMG_BUFFER_LENGTH && emg_position < displacement) || emg_position >= cur_position){
            myled2 = 1;
            classification = classify(cur_position - window , cur_position, window);
            myled2 = 0;
            myled = classification;
            chew_place(classification);
            cur_position = (cur_position + displacement);
            if(cur_position == (EMG_BUFFER_LENGTH + displacement)){
                //ignore overlap of end of buffer and begining of buffer
                cur_position = window;
            }
        }else{
            //inbetween adding classifications, check chew_buffer
            chew_test();
        }
    }
}
