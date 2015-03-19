/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
	//Check for empty array
	if(n<1)
		return false;
		
	//Initialise variables
	int i, left = 0, right = n-1, done = false;
		
	//Binary search
	do
	{
		//This will be the last loop
		if(left == right)
		{
			done = true;
		}
		
		i = left + ((right - left) / 2);
		if(value == values[i])
		{
			//A match
			return true;
		}
		else if(value > values[i])
		{
			//Use right half of array
			left = i + 1;			
		}
		else
		{
			//Use left half of array
			right = i - 1;			
		}
	}
	while(!done);
	
	return false;
	
	/* Linear sort
	int i;
		
	//Loop through values[]
	for(i = 0; i < n; i++)
	{
		//Return true if needle is found
		if(values[i] == value)
			return true;
	}
	
	//Needle wasn't found in haystack
    return false;
    */
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Bubble-sort
 	int i, j, swap;
 
 	//Loop through values[]	
 	for(i=0; i<n; i++)
 	{
 		//Selection sort for each value
 		for(j=(i+1); j<n; j++)
 		{
 			//Compare, swapping largest elements up
 			if(values[i] > values[j])
 			{
 				//Make use of swap variable
 				swap = values[j];
 				values[j] = values[i];
 				values[i] = swap;
 			}
 		}
 	}	
 	   
    return;
}
