/**
 * resize.c
 *
 * Computer Science 50
 * Hacker Set 5
 *
 * Resizes a 24-bit DIB file by a factor f.
 * Usage: ./resize f infile outfile
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize f infile outfile\n");
        return 1;
    }
    
    //Error check passed in length for n
    float n = atof(argv[1]);    
    if(n<0.0 || n>100.0)
    {
    	printf("Enter an f in the range 0.0 to 100.0\n");
    	return 1;
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //Padding for input file (we need to know how much of each scanline to skip with inptr)
    int inPadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //Store input width & height for iterating later
    LONG inputHeight = abs(bi.biHeight);   
    LONG inputWidth = bi.biWidth;
     
    //Make size adjustments to bitmap file and bitmap info headers
    bi.biHeight = n * bi.biHeight;
    bi.biWidth = n * bi.biWidth;
    // determine padding for scanlines
    int outPadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
	//Given width, padding & height we can calculate bfSize
    bf.bfSize = sizeof(BITMAPFILEHEADER) +
    			sizeof(BITMAPINFOHEADER) +
    			(-bi.biHeight * (bi.biWidth * sizeof(RGBTRIPLE) + outPadding));
    //Don't need to calculate biSizeImage for rgb DIB files
    bi.biSizeImage = (-bi.biHeight * (bi.biWidth * sizeof(RGBTRIPLE) + outPadding));

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    //Set up array for input file
    RGBTRIPLE inBits[inputWidth][inputHeight];    

	// Read  input file into inBits[][]
    // iterate over infile's scanlines
    for (int i = 0; i < inputHeight; i++)
    {
	    // iterate over pixels in scanline
	    for (int j = 0; j < inputWidth; j++)
	    {
	        // read RGB triple from infile
	        fread(&inBits[j][i], sizeof(RGBTRIPLE), 1, inptr);
	    }

	    // skip over padding, if any
	    fseek(inptr, inPadding, SEEK_CUR);
	}
	
	//Set up array for output file    
	RGBTRIPLE outBits[bi.biWidth][abs(bi.biHeight)];	
	
	//Set up absolute bi.biHeight value for looping
	int absBiHeight = abs(bi.biHeight);	
    
    //Resize inBits into outBits
    for(int i=0; i<absBiHeight; i++)
    {
    	//Carry out for 
    	for(int j=0; j<bi.biWidth; j++)
    	{
    		if(n>=1.0)
    		{
    			//Enlarge or keep same size with bicubic interpolation
    			//No resampling (will lead to jagged edges, but simpler
    			int ibI = i/n;
    			int ibJ = j/n;
    			outBits[j][i].rgbtGreen = inBits[ibJ][ibI].rgbtGreen;
    			outBits[j][i].rgbtBlue = inBits[ibJ][ibI].rgbtBlue;
    			outBits[j][i].rgbtRed = inBits[ibJ][ibI].rgbtRed;    			    			
    		}
    		else
    		{
    			//For reductions, we will perform some resampling based on pixels around current
    			//Will lead to loss of information and some blurring potentially
    			
    			//Initialise RGBTriple to write to outBits
    			RGBTRIPLE aveCol;
    			bool firstSample = true;
    			
    			//Find how many pixels to sample
    			int sample = 1/n;
    			
    			for(int a=(sample*i)-(sample/2); a<(sample*i)+(sample/2); a++)
    			{
	    			for(int b=(sample*j)-(sample/2); b<(sample*j)+(sample/2); b++)
	    			{
						//Edge cases, can't sample inBits[-1][-1]
						if(a>=0 && b>=0 && a<inputHeight && b<inputWidth)
						{
							if(firstSample)
							{
								firstSample = false;
								aveCol.rgbtRed = inBits[b][a].rgbtRed;
								aveCol.rgbtGreen = inBits[b][a].rgbtGreen;
								aveCol.rgbtBlue = inBits[b][a].rgbtBlue;
							}
							else
							{
								aveCol.rgbtRed = (aveCol.rgbtRed + inBits[b][a].rgbtRed) / 2;
								aveCol.rgbtGreen = (aveCol.rgbtGreen + inBits[b][a].rgbtGreen) / 2;
								aveCol.rgbtBlue = (aveCol.rgbtBlue + inBits[b][a].rgbtBlue) / 2;
							}
						}
	    			}
	    		}
				//Fill outBits with average colour value
    			outBits[j][i].rgbtGreen = aveCol.rgbtGreen;
    			outBits[j][i].rgbtBlue = aveCol.rgbtBlue;
    			outBits[j][i].rgbtRed = aveCol.rgbtRed;
    		}
    	}
	}

	// Read outBits into output file
    // iterate over infile's scanlines
    for(int i=0; i<absBiHeight; i++)
    {
	    // iterate over pixels in scanline
	    for (int j=0; j<bi.biWidth; j++)
	    {
	        // read RGB triple from infile
	        fwrite(&outBits[j][i], sizeof(RGBTRIPLE), 1, outptr);
	    }

		for(int x=0; x<outPadding; x++)
			fputc('\0', outptr);
    }    
	    

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
