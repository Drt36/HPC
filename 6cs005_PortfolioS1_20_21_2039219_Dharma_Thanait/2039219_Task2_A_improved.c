#include<stdio.h>
#include<time.h>
#include <stdlib.h>


//To calculate Time diffrence
int time_difference(struct timespec *start, struct timespec *finish, long long int *difference){
  
	long long int ds = finish->tv_sec - start->tv_sec;
	long long int dn = finish->tv_nsec - start->tv_nsec;

	if(dn < 0 ){
		ds--;
		dn += 1000000000;
	}
	*difference = ds * 1000000000 + dn;
	return !(*difference > 0);
}
int main(){

  struct timespec start, finish;
  
  long long int time_elapsed;

  int a[2][2], b[2][2], c[2][2], i, j;

  int m1, m2, m3, m4 , m5, m6, m7;

 

  printf("---Generating First Matrix---:\n");

  for(i = 0;i < 2; i++){

      for(j = 0;j < 2; j++){

           a[i][j]=rand()%70;
		   printf("%d  ", a[i][j]);
	 }
	  printf("\n");
  }
 

  printf("---Generating Second Matrix---: \n");

  for(i = 0; i < 2; i++){

      for(j = 0;j < 2; j++){

           b[i][j]=rand()%70;
			printf("%d  ", b[i][j]);
      }
       printf("\n");
 }
 

  //start time calculation
  clock_gettime(CLOCK_MONOTONIC, &start);
  
  m1= (a[0][0] + a[1][1]) * (b[0][0] + b[1][1]);

  m2= (a[1][0] + a[1][1]) * b[0][0];

  m3= a[0][0] * (b[0][1] - b[1][1]);

  m4= a[1][1] * (b[1][0] - b[0][0]);

  m5= (a[0][0] + a[0][1]) * b[1][1];

  m6= (a[1][0] - a[0][0]) * (b[0][0]+b[0][1]);

  m7= (a[0][1] - a[1][1]) * (b[1][0]+b[1][1]);

 

  c[0][0] = m1 + m4- m5 + m7;

  c[0][1] = m3 + m5;

  c[1][0] = m2 + m4;

  c[1][1] = m1 - m2 + m3 + m6;

 

   printf("\n-------The result of multiplication using Strassen's algorithm:--------- \n");

   for(i = 0; i < 2 ; i++){

      printf("\n");

      for(j = 0;j < 2; j++){

           printf("%d\t", c[i][j]);
	}
   }
  //stop time calculation
  clock_gettime(CLOCK_MONOTONIC, &finish);
	
  //calculating time difference
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.lfs\n", time_elapsed, (time_elapsed/1.0e9));

 

   return 0;

}
