#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
int main()
{
	struct timespec start, finish;
	long long int time_elapsed;
	int row_first_matrix;
	int column_first_matrix;
	int column_second_matrix;
	
	printf("Enter the Row of First matrix:\n");
	scanf("%d",&row_first_matrix);
	
	printf("Enter the column of First matrix:\n");
	scanf("%d",&column_first_matrix);
	
	
	printf("The Row of Second matrix is:\n%d\n",column_first_matrix);
	
	printf("Enter the column of Second matrix:\n");
	scanf("%d",&column_second_matrix);
	
	int a[row_first_matrix][column_first_matrix], b[column_first_matrix][column_second_matrix], c[row_first_matrix][column_second_matrix];
	int i, j, k;
		
	//Printing first matrix
	printf("\nThe Firt Matrix:\n");
	for(i=0; i<row_first_matrix; i++) {
		for(j=0; j<column_first_matrix; j++) {
			a[i][j]=rand()%70;
			printf("%d  ", a[i][j]);
				
		}
		printf("\n");
	}
	
	//Printing Second Matrix
	printf("\nThe Second Matrix:\n");
	for(i=0; i<column_first_matrix; i++) {
		for(j=0; j<column_second_matrix; j++) {
			b[i][j]=rand()%70;
			printf("%d  ", b[i][j]);
		}
		printf("\n");
	}
	
	//start time calculation
	clock_gettime(CLOCK_MONOTONIC, &start);
	
	//Start Multiplication of matrix
	for(i=0; i<row_first_matrix; i++) {
		for(j=0; j<column_second_matrix; j++) {
			c[i][j]=0;
			for(k=0; k<column_first_matrix; k++) {

				c[i][j]=c[i][j] + a[i][k] * b[k][j];

			}
		}
	}
	//To print result of multiplied matrix
	printf("\nThe Multiplied Matrix Is: \n");
	for(i=0; i<row_first_matrix; i++) {
		for(j=0; j<column_second_matrix; j++) {
			printf("%d  ", c[i][j]);
		}
		printf("\n");
	}
	//stop time calculation
	clock_gettime(CLOCK_MONOTONIC, &finish);
	
	//calculating time difference
	time_difference(&start, &finish, &time_elapsed);
	printf("Time elapsed was %lldns or %0.lfs\n", time_elapsed, (time_elapsed/1.0e9));

		return 0;
	
	}
	
	


