/******************************
*Name: Mihir Gupte
*Date: Dec 13, 2017
*Description: This program receives numbers as input then performs 3 statistical calculations, each calculation using its own POSIX threads. One thread will calculate the average, another will find the minimum number and another thread to find the maximum number.
*******************************/
//Required include files for this program
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*Global variables used in this program
Variable totalNumbers holds the count of input numbers
*/
int averageNum, minimumNum, maximumNum, totalNumbers;

//Function to calculate the average, receives an array of list of numbers
void *calc_avg(void *num)
{
	int *numbers = (int *)num;					//Reference to the number array pointer
	int sum = 0;							    //Variable for sum of all the numbers
	for(int j=1;j <= (totalNumbers); j++)		//Iterates through the total numbers provided 
	{
		sum += numbers[j];						//Adds the numbers of the array through every iteration
	}
	averageNum =(int) (sum/totalNumbers);		//Calculates and stores the average
	pthread_exit(NULL);							//Exits from the thread
}

//Function to find the minimum number from the array of list of numbers
void *calc_min(void *num)
{
	int *numbers = (int *)num;					//Reference to the number array pointer
	minimumNum = numbers[1];					//Stores the first number of the array as the minimum
	for(int k=1; k<=(totalNumbers); k++)		//Iterates through the total numbers provided
	{
		if (minimumNum > numbers[k])			//Checks if the current minimum number is more than the number in the array
		{
			minimumNum = numbers[k];			//Swaps the number with the new minimum
		}
	}
	pthread_exit(NULL);							//Exits from the thread
}

//Function to find the maximum number from the array of list of numbers
void *calc_max(void *num)
{
	int *numbers = (int *)num;					//Reference to the number array pointer
	maximumNum = numbers[1];					//Stores the first number of the array as the maximum
	for(int m=1; m<=(totalNumbers); m++)		//Iterates through the total numbers provided
	{
		if (maximumNum < numbers[m])			//Checks if the current maximum number is less than the number in the array
		{
			maximumNum = numbers[m];			//Swaps the number with the new maximum
		}
	}
	pthread_exit(NULL);							//Exits from the thread
}

int main (int argc, char *argv[])
{
	/* Check if there are any arguments being passed
	* And provide the correct command to use.
	*/
	if (argc < 1){
		fprintf(stderr,"Provide 1 or more numbers. Use command: ./calculate 90 81 78 95 79 72 85 \n");
		exit(1);
	}
	
	int inputNum[argc-1];						//Declare and initializes an array of size of the input numbers
	totalNumbers=0;								//Total number counter
	for (int i=1; i < (argc); i++)				//Iterates through all the arguments provided when the program is ran, but only after the initial program name
	{
		inputNum[i]= atoi(argv[i]);				//Converts the string arguments to integers and stores it in the array
		totalNumbers++;	
	}
	//Variables for each individual thread
	pthread_t threadAvg, threadMax, threadMin;
	
	/*
		Following pthread_create() commands create the individual threads to perform the statistical calculations.
		The conditional statements perform error handling by checking if the thread was created successfully, which returns a 0.
		If it was unsuccessful, then the program prints out an error and exits.
	*/
	
	if(pthread_create(&threadAvg, NULL, (void*) calc_avg, (void*) inputNum)!=0)
	{
		fprintf(stderr,"Cannot create a thread");
		exit(1);
	}
	if(pthread_create(&threadMin, NULL, (void*) calc_min, (void*) inputNum)!=0)
	{
		fprintf(stderr,"Cannot create a thread");
		exit(1);
	}
	if(pthread_create(&threadMax, NULL, (void*) calc_max, (void*) inputNum)!=0)
	{
		fprintf(stderr,"Cannot create a thread");
		exit(1);
	}

	/*
		Following pthread_join() commands wait to join all the threads. The conditional statements performs error
		handling by checking if thread joining was successful. If it was not, it will print out the error and exit.
	*/
	if(pthread_join(threadAvg,NULL)!=0)
	{
		fprintf(stderr,"Cannot join the thread");
		exit(1);
	}
	if(pthread_join(threadMin,NULL)!=0)
	{
		fprintf(stderr,"Cannot join the thread");
		exit(1);
	}
	if(pthread_join(threadMax,NULL)!=0)
	{
		fprintf(stderr,"Cannot join the thread");
		exit(1);
	}

	//Print all the statistical values 
	printf("The average value is %d\n", averageNum);
	printf("The minimum value is %d\n", minimumNum);
	printf("The maximum value is %d\n", maximumNum);
	
	//Ensures main waits for all outstanding threads to be terminated before exiting
	pthread_exit(NULL); 
	return 0;
}
