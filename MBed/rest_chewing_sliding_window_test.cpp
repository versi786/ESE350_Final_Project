#include "mbed.h"
#include "stdio.h"
#include <map>
#include "math.h"
using namespace std;
#define EMG_BUFFER_LENGTH 1000

DigitalOut myled(LED1);
Serial pc(USBTX, USBRX);
Timer timer;
Ticker emg;
Ticker accelerometer;
AnalogIn emg_pin(p20);
AnalogIn accel(p17);


int emg_buffer[EMG_BUFFER_LENGTH];
int emg_position;

void emg_isr() {
    emg_buffer[emg_position] = emg_pin.read_u16();
    emg_position = (emg_position + 1) % EMG_BUFFER_LENGTH;
    // pc.printf("%d\r\n", emg_pin.read_u16());
}

int maxArr(int arr[], int length){
    int max = -4000000;
    for(int i = 0; i < length; i++){
        if(max < arr[i]){
            max = arr[i];
        }
    }
    return max;
}

int minArr(int arr[], int length){
    int min = 4000000;
    for(int i = 0; i < length; i++){
        if(min > arr[i]){
            min = arr[i];
        }
    }
    return min;
}

double log2( double number ) {
   return log( number ) / log( 2.0 ) ;
}

double entropyArr (int arr[] , int length) {
   std::map<int, int> frequencies ;
   for (int i = 0 ; i < length; i++ )
     frequencies[ arr[i] ]++;
   int numlen = length;
   double infocontent = 0;
   
   for (std::map<int,int>::iterator it = frequencies.begin(); it != frequencies.end(); it++) {
      std::pair<int , int> p = *it;
      double freq = static_cast<double>( p.second ) / numlen ;
      infocontent += freq * log2( freq ) ;
   }
   infocontent *= -1 ;
   return infocontent;
}

int distanceArr(int arr[], int length){
    int total = 0;
    int temp = 0;
    for(int i = 0; i < length - 1; i++){
        temp = arr[i] -arr[i+1];
        if(temp < 0){
            temp = -temp;
        }
        total += temp;
    }
    return total/(length-1);
}

int classify(int arr[], int length) {
    double entropy = entropyArr(arr, length);
    int max = maxArr(arr, length);
    int min = minArr(arr, length);
    int distance = distanceArr(arr, length);
    // pc.printf("entropy: %f\r\nmax:%d\r\nmin:%d\r\ndistance:%d\r\n", entropy, max, min, distance);
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
    int cur_position = 250;
    int displacement = 250;
    int window[250];
    int classification;
    while(1) {
        // pc.printf("hi\r\n");
        if(emg_position >= cur_position){
            memcpy(window, window + (cur_position-250), 250);
            classification = classify(window, 250);
            // pc.printf("\r\nclassification:%d\r\n\r\n", classification);
            myled = classification;
            cur_position = (cur_position + displacement) % EMG_BUFFER_LENGTH;
            // pc.printf("%d/r/n", cur_position);
        }
    }
}
