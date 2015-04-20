#include "mbed.h"
#include "stdio.h"
#include <map>
#include "math.h"
using namespace std;
#define EMG_BUFFER_LENGTH 3000

DigitalOut myled(LED1);
DigitalOut myled2(LED2);
DigitalOut motor(p5);
Serial pc(USBTX, USBRX);
Timer timer;
Ticker emg;
Ticker accelerometer;
AnalogIn emg_pin(p20);

int emg_buffer[EMG_BUFFER_LENGTH];
int emg_position;

void emg_isr() {
    emg_buffer[emg_position] = emg_pin.read_u16();
    emg_position = (emg_position + 1) % EMG_BUFFER_LENGTH;
    // pc.printf("%d\r\n", emg_pin.read_u16());
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
    //pc.printf("start:%d       End:%d   \r\n",start, end); 
    //pc.printf("entropy: %f\r\nmax:%d\r\nmin:%d\r\ndistance:%d\r\n", entropy, max, min, distance);
    //return 1;
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
    timer.start();
    emg.attach(&emg_isr, .001);
    int window = 250;
    int displacement = 125;
    int classification;
    int cur_position = window;
    while(1) {
        if((cur_position == EMG_BUFFER_LENGTH && emg_position < displacement) || emg_position >= cur_position){
            //pc.printf("%d\r\n", cur_position);
            myled2 = 1;
            classification = classify(cur_position - window , cur_position, window);
            myled2 = 0;
            myled = classification;
            motor = classification;
            //pc.printf("p:%d\r\n", cur_position);
            //pc.printf("c:%d\r\n", classification);
            cur_position = (cur_position + displacement) /*% EMG_BUFFER_LENGTH*/;
            if(cur_position == (EMG_BUFFER_LENGTH + displacement)){
                //ignore overlap of end of buffer and begining of buffer
                cur_position = window;
            }
        }
    }
}