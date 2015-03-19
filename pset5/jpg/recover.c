/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdbool.h>

int main(int argc, char* argv[])
{
	char* rawFileName;
	bool  rawFileNameMalloc = false;
	
	//If there are extra arguments
	if(argc > 2)
	{
		printf("Recover will recover jpg files from a binary image\n");
		printf("Usage: ./recover filename\n");	
		
		return 0;
	}
    else if(argc == 2)
    {
    	//Allow a lowercase -h switch to display help & exit
    	if(strcmp(argv[1], "-h")==0)
    	{
    		printf("Recover will recover jpg files from a binary image\n");
	    	printf("Usage: ./recover filename\n");
	    	
	    	return 0;
    	}
    	else
    	{
    		//Otherwise assume the second argument is a file name
    		rawFileName = argv[1];
    	}
    }
    else
    {
    	//If there are no arguments, use card.raw for filename
    	rawFileName = malloc(sizeof(char) * 9);
    	strcpy(rawFileName, "card.raw");
    	rawFileNameMalloc = true;
    }
    
    //Open up a pointer to raw file
    FILE* rawFile = fopen(rawFileName, "r");
    
    //Handle error opening raw file
    if(rawFile == NULL)
    {
    	printf("Unable to open raw file\n");

		//Free filename pointer and return
		if(rawFileNameMalloc)
			free(rawFileName);    	
    	
    	return 1;
	}
	
	//Iterate through raw file looking for jpeg images
	unsigned char block[512];
	int recoveredFiles = 0;
	char recoveredFileName[8];
	FILE *nextFile = NULL;
	
	while(!feof(rawFile))
	{
		//Read 512 bytes from rawFile into block array
		if(fread(block, 512, 1, rawFile) != 1)		
			break;

		//Check for new file
		if(	block[0] == 0xFF &&
			block[1] == 0xD8 &&
			block[2] == 0xFF &&
			(block[3] == 0xE0 || block[3] == 0xE1) )
		{
			//Check if we're currently writing a file
			if(nextFile != NULL)
				fclose(nextFile);
			
			//Open a new file
			sprintf(recoveredFileName, "%03i.jpg", recoveredFiles++);
			nextFile = fopen(recoveredFileName, "w");
			
			//Handle error opening file
			if(nextFile == NULL)
			{
				printf("Error opening new file for writing\n");
				return 1;
			}
			
			//Write first block
			if(fwrite(block, 512, 1, nextFile) != 1)
			{
				printf("Error writing to file\n");
				return 1;
			}			
		}
		else
		{
			//Continue writing to file
			if(nextFile != NULL)
			{
				if(fwrite(block, 512, 1, nextFile) != 1)
				{
					printf("Error writing to file\n");
					return 1;
				}
			}
		}
	}
	
	//Close output file
	if(nextFile != NULL)
		fclose(nextFile);
    
    //Close raw file
    fclose(rawFile);
    
    //Free filename pointer and return
    if(rawFileNameMalloc)
	    free(rawFileName);
    return 0;
}
