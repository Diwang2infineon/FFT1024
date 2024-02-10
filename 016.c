/******************************************************************************
 * \file LoopPerformance.c
 *
 * \brief Performance measurement of nested loops
 *
 * This file measures the performance of nested loops by iterating over a large
 * number of iterations and calculating the time taken. It provides a function
 * to print the current time with milliseconds precision and calculates the
 * performance of the loop in terms of Giga operations per second (G/s).
 *
 * \version 1.0
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <math.h>
#include <stdio.h>


#define LOOP_NUM 2000//  1k^3=1G


void print_current_time_with_ms (long *pNum)
{
    long            ms; // Milliseconds
    long          s;  // Seconds
    long long r;

    struct timeval tv;
	struct timezone tz;
  
	mingw_gettimeofday(&tv , 0);
   

    //r= (double)s+(double)ms/1000.0;
    
    s = tv.tv_sec;
	ms = tv.tv_usec/1000;

	*pNum=s;
	*(pNum+1)=ms;
	
//printf("\nCurrent time: %ld %ld seconds since the Epoch\n",s,r);
	

}


int main(int argc, char *argv[]) {
	int i,j,k,c=0;   double flt;
	long parameter[2];
	long  startSec1,startSec2,endSec1,endSec2;
	float sec;
     print_current_time_with_ms(parameter);
     startSec1=parameter[0];
     startSec2=parameter[1];



	printf("hello \n" );
	for(i=0;i<LOOP_NUM;i++)
	{
		for(j=0;j<LOOP_NUM;j++)
		{
			for(k=0;k<LOOP_NUM;k++)
			{
				c=c;
				
				
			}
		}
	}
    //now = time(NULL) ;
     print_current_time_with_ms(parameter);
     endSec1=parameter[0];
     endSec2=parameter[1];
   //endSec=(int)now;
   sec=endSec1-startSec1;
   sec=endSec2-startSec2+(sec*1000);
   sec/=1000;
   c=(LOOP_NUM/1000)*(LOOP_NUM/1000)*(LOOP_NUM/1000);
   flt=(float)c/sec;
      //printf("%d %d %d %d\n",endSec1,startSec1,endSec2,startSec2) ;
   printf("%d G/ %.3f s = %.3f G/s\n",c,sec,flt) ;


while(1);
	printf("\nend ");
	return 0;
}
