#include <iostream>
#include "../tsimd.h"

using namespace std;
using namespace TSimd;

int main(int argc, char* argv[]){
    return 0;
}

//Stuff I was using for microbenchmarking
/*#include <iostream>
#include "../tsimd.h"

using namespace std;

static inline uint64_t rdtscp( uint32_t & aux )
{
    uint64_t rax,rdx;
    asm volatile ( "rdtscp\n" : "=a" (rax), "=d" (rdx), "=c" (aux) : : );
    return (rdx << 32) + rax;
}

int main(int argc, char* argv[]){
    uint32_t crap;
    unsigned long min  = 1l<<63;
    unsigned long max = 0;
    unsigned long avg = 0;
    unsigned long min2  = 1l<<63;
    unsigned long max2 = 0;
    unsigned long avg2 = 0;
    unsigned long min3 = 1l<<63;
    unsigned long max3 = 0;
    unsigned long avg3 = 0;
    for(int i = 0;i<10000;i++){
        unsigned long a = rdtscp(crap);
        asm volatile("" ::: "memory");

        //Code 1 goes here

        asm volatile("" ::: "memory");
        a = rdtscp(crap) - a;
        min = (min>a)?a:min;
        max = (max<a)?a:max;
        avg+=a;
        a = rdtscp(crap);
        asm volatile("" ::: "memory");

        //Code 2 goes here

        asm volatile("" ::: "memory");
        a = rdtscp(crap) - a;
        min2 = (min2>a)?a:min2;
        max2 = (max2<a)?a:max2;
        avg2+=a;
        a = rdtscp(crap);
        asm volatile("" ::: "memory");
        asm volatile("" ::: "memory");
        a = rdtscp(crap) - a;
        min3 = (min3>a)?a:min3;
        max3 = (max3<a)?a:max3;
        avg3+=a;
    }
    cout<<"Code 1:  "<<min-min3<<"-"<<max-max3<<", avg: "<<(avg-avg3)/10000.0<<endl;
    cout<<"Code 2:  "<<min2-min3<<"-"<<max2-max3<<", avg: "<<(avg2-avg3)/10000.0<<endl;
    cout<<"Ratio: "<<(avg-avg3+0.0)/(avg2-avg3)<<endl;
    return 0;
}
*/
