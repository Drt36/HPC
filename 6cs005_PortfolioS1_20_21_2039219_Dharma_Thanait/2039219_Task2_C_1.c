#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <unistd.h>
#include <time.h>

 
// A counter used to track the number of combinations explored so far
int count=0;     


void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}


void crack(char *salt_and_encrypted){
  // Loop counters
  int x, y, z;     
  char salt[7];    // String used in hashing the password. Need space for \0 // incase you have modified the salt value, then should modifiy the number accordingly
  char plain[7];   // The combination of letters currently being checked // Please modifiy the number when you enlarge the encrypted password.
  char *enc;       // Pointer to the encrypted password

  substr(salt, salt_and_encrypted, 0, 6);

  for(x='A'; x<='Z'; x++){
    for(y='A'; y<='Z'; y++){
      for(z=0; z<=99; z++){
        sprintf(plain, "%c%c%02d", x, y, z); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
        	printf("Given password is found!!!\n");
	    	printf("#%-8d%s %s\n", count, plain, enc);
	    	
        } 
        else{
        	//printf("%-8d%s %s\n", count, plain, enc);
        }
      }
    }
  }
 
}


//To calculate time difference
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

int main(int argc, char *argv[]){
int i;
    struct timespec start, finish;
	long long int time_elapsed;
	//start timer
	clock_gettime(CLOCK_MONOTONIC, &start);
	
	// ecrypted password here using EncryptShA512 program
  	crack("$6$AS$/VVBKjAgOvuuu1nQOfbtNphsSzeMkQy5wkAQGTGEPWcF88tImSXGgI/DjYzLtcAaY7TXIgDubwlUlac4H1j7e.");		
  	printf("%d solutions explored\n", count);
  	
  	//stop timer
  	clock_gettime(CLOCK_MONOTONIC, &finish);
	time_difference(&start, &finish, &time_elapsed);

	printf("Time elapsed was %lldns or %0.lfs\n", time_elapsed, (time_elapsed/1.0e9));

  return 0;
}


