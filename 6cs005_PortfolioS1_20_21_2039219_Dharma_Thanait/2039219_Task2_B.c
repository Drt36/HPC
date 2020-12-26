#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAT_SIZE 1024
int MAX_THREADS;

//Parameters For Rows And Columns
int x,y,z;  
//First Matrix
int first_matrix[MAT_SIZE][MAT_SIZE]; 
//Second Matrix
int second_matrix[MAT_SIZE][MAT_SIZE]; 
//Multiplied tresultMatrix
int result_matrix [MAT_SIZE][MAT_SIZE]; 


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

//matrix multiplication
void* mult(void* arg){

	int i = 0;
    int core = i++;
    
    for (int i = core * MAT_SIZE / MAX_THREADS; i < (core + 1) * MAT_SIZE / MAX_THREADS; i++)
        for (int k = 0; k< MAT_SIZE; k++)
            for (int j = 0; j< MAT_SIZE; j++)
                result_matrix[i][j] += first_matrix[i][k] * second_matrix[k][j];

    pthread_exit(0);
}


int main(){

	struct timespec start, finish;
	long long int time_elapsed;

	//Defining first matrix
    printf("Enter the rows for First Matrix: ");
    scanf("%d",&x);
    printf("Enter the columns for First Matrix:");
    scanf("%d",&y);
    
    //Defining Second matrix 
    printf("The rows for Second Matrix:  %d\n",y);
    printf("Enter the columns for Second Matrix: ");
    scanf("%d",&z);
    
    //Defining number of thread
    printf("Enter the number of Threads:  \n");
    scanf("%d",&MAX_THREADS);

	//generating random first matrix
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            first_matrix[i][j]=rand()%50;
        }
    }
    
	//generating random second matrix
    for(int i=0;i<y;i++){
        for(int j=0;j<z;j++){
            second_matrix[i][j]=rand()%50;
        }
    }
    
    //printing first matrix
    printf("\n --- Matrix 1 ---\n\n");
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
         printf("%5d",first_matrix[i][j]);
       
        }
        printf("\n\n");
    }
 
    //printing Second matrix
    printf(" --- Matrix 2 ---\n\n");
    for(int i=0;i<y;i++){
        for(int j=0;j<z;j++){
        	printf("%5d",second_matrix[i][j]);
        }
        printf("\n\n");
    }
  
	//allocating memory
    pthread_t *t = malloc(sizeof(pthread_t) * MAX_THREADS);

    //Defining Threads
    pthread_t thread[MAX_THREADS];

    //Counter For Thread Index
    int thread_number = 0;

    //start time calculation
	clock_gettime(CLOCK_MONOTONIC, &start);


    for (int x = 0; x < MAX_THREADS; x++)
    {
        int *p;
            //Status For Checking Errors
            int status;

            //Create Specific Thread For Each Element In Result Matrix
            status = pthread_create(&thread[thread_number], NULL, mult, (void *) &p[thread_number]);

            //Check For Error
            if(status!=0){
                printf("Error In Threads");
                exit(0);
            }

            thread_number++;
        }





    //Wait For All Threads Done 

   for (int z = 0; z < MAX_THREADS; z++)
        pthread_join(thread[z], NULL);


    //Print Multiplied Result matrix

    printf(" --- Multiplied Matrix ---\n\n");
    for(int i=0;i<x;i++){
        for(int j=0;j<z;j++){
            printf("%5d",result_matrix[i][j]);
        }
        printf("\n\n");
    }


   //stop time calculation
	clock_gettime(CLOCK_MONOTONIC, &finish);
	
	//calculating time difference
	time_difference(&start, &finish, &time_elapsed);
	printf("Time elapsed was %lldns or %0.lfs\n", time_elapsed, (time_elapsed/1.0e9));

    //Total Threads count print
    printf(" ---> Used Threads : %d \n\n",thread_number);
    //free allocated memory
    free(t);
    
    return 0;
}
