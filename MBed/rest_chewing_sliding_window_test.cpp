#include "mbed.h"
#include "stdio.h"
#include <map>
#include "math.h"
using namespace std;
DigitalOut myled(LED1);
Serial pc(USBTX, USBRX);



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

// int entropyArr(int arr[], int length){
//     map val_freq = map<int,double>;
//     double data_entropy = 0.0;
//     //calculate the frequency of each of the values
//     for(int i = 0; i < length; i++){
//         map<int,double>::iterator it = m.find(arr[i]);
//         if(it != map.end()){
//             val_freq.insert(std::pair<int,double>(arr[i], 1));
//         }else{
//             it->second += 1.0;
//         }
//     }
//     //calculate entropy
//     for(it = val_freq).begin(); it != val_freq.end(); it++){
//         double freq = it->second;
//         data_entropy += (-freq/length) * (log(freq/length)/log(2))
//     }
//     return data_entropy;
// }
double log2( double number ) {
   return log( number ) / log( 2.0 ) ;
}

double entropyArr (int arr[] , int length) {
   std::map<int, int> frequencies ;
   for (int i = 0 ; i < length; i++ )
     frequencies[ arr[i] ]++;
   int numlen = length;
   double infocontent = 0;
   //for (it = inVector->begin(); it != inVector->end(); it++)
   
   for (std::map<int,int>::iterator it = frequencies.begin(); it != frequencies.end(); it++) {
      std::pair<int , int> p = *it;
      //pc.printf("%d,%d", p.first, p.second);
      double freq = static_cast<double>( p.second ) / numlen ;
      infocontent += freq * log2( freq ) ;
   }
   infocontent *= -1 ;
   return infocontent;
}

int classify(int arr[], length) {
    
}
    




int main() {
    int arr[] = {0,1,2,3,4,5,6};
    double x;
    while(1) {
    //     myled = 1;
    //     wait(0.2);
    //     myled = 0;
    //     wait(0.2);
    
        x = entropyArr(arr, 7);
        pc.printf("%f\r\n", x);
    }
}
