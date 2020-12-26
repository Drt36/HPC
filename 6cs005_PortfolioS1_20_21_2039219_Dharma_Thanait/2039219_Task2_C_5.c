#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <math.h>


char *encrypted= "$6$AS$igkMDyBH4Q83NBPLiR/a3rI.zSp2H8URxk3Rg/GcZnyKW74U8kwvEP8orqwj4YQhcbPtOiqqVxlbWil85c44l1";
  
pthread_mutex_t lock;
pthread_t thread_1,thread_2; 

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

void threads()
{	
 
  void *kernel_function_1();
  void *kernel_function_2();
  
  pthread_create(&thread_1, NULL,(void*)kernel_function_1, encrypted); 
  pthread_create(&thread_2, NULL,(void*)kernel_function_2, encrypted);
  
  pthread_join(thread_1, NULL);
  pthread_join(thread_2, NULL);
  
  pthread_mutex_destroy(&lock);
  
  

}

//TO find password start With A to M
void *kernel_function_1(char *salt_and_encrypted){


  int x,y,z;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0 // incase you have modified the salt value, then should modifiy the number accordingly
  char plainn[7];   // The combination of letters currently being checked // Please modifiy the number when you enlarge the encrypted password.
  char *encc;  
  int count = 0;     // Pointer to the encrypted password


  substr(salt, salt_and_encrypted, 0, 6);

  for(x='A'; x<='M'; x++){
    for(y='A'; y<='Z'; y++){
        for(z=0; z<=99; z++){
        
        sprintf(plainn, "%c%c%02d", x, y, z);
        //to lock shared resource 
        pthread_mutex_lock(&lock);
        encc = (char *) crypt(plainn, salt);
        //to unlock shared resource 
        pthread_mutex_unlock(&lock);
        
        count++;
        if(strcmp(salt_and_encrypted, encc) == 0){
		    printf("Given password is found!!!\n");
			printf("#%-8d%s %s\n", count, plainn, encc);
		
		}
		else{
				//printf("%-8d%s %s\n", count, plainn, encc);
			} 
		 
        } 
      }
    }
 }
 
 //TO find password start With N to Z
 void *kernel_function_2(char *salt_and_encrypted){
 
  int a,b,c;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0 // incase you have modified the salt value, then should modifiy the number accordingly
  char plain[7];   // The combination of letters currently being checked // Please modifiy the number when you enlarge the encrypted password.
  char *enc;  
  int count = 0;       // Pointer to the encrypted password

  substr(salt, salt_and_encrypted, 0, 6);


  for(a='N'; a<='Z'; a++){
    for(b='A'; b<='Z'; b++){
        for(c=0; c<=99; c++){
        
        sprintf(plain, "%c%c%02d", a, b, c);
        //to lock shared resource 
        pthread_mutex_lock(&lock);  
        enc = (char *) crypt(plain, salt);
        //to unlock shared resource 
        pthread_mutex_unlock(&lock);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){ 
		    printf("Given password is found!!!\n");
			printf("#%-8d%s %s\n", count, plain, enc);
	  
        } else{
        		//printf("%-8d%s %s\n", count, plain, enc);
        	} 
         
        } 
      }
    }
  }

//to calculate time difference
int time_difference(struct timespec *start, struct timespec *finish, 
                              long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec; 
  long long int dn =  finish->tv_nsec - start->tv_nsec; 

  if(dn < 0 ) {
    ds--;
    dn += 1000000000; 
  } 
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}

int main(int argc, char *argv[]){
  struct timespec start, finish;
  long long int time_elapsed;  
  
  if (pthread_mutex_init(&lock, NULL) != 0) { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    }  
  //start timer  
  clock_gettime(CLOCK_MONOTONIC, &start);
  //calling threds
  threads();
  
  //stop timer
  clock_gettime(CLOCK_MONOTONIC, &finish); 
  
  //calculate time difference
  time_difference(&start, &finish, &time_elapsed);
  //ptint time elapsed
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, (time_elapsed/1.0e9)); 
          

  return 0;
}




