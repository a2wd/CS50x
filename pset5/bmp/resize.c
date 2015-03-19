/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Resizes a 24-bit DIB file by a factor n.
 * Usage: ./resize n infile outfile
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    //Error check passed in length for n
    long long n_long = atoll(argv[1]);    
    if(n_long<1 || n_long>100)
    {
    	printf("Enter an n in the range 1 to 100\n");
    	return 1;
    }
    //If in safe integer range, store n value
    unsigned int n = (int) n_long;
    
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

    // iterate over infile's scanlines
    for (int i = 0; i < inputHeight; i++)
    {
    	//Get start of line position
    	fpos_t startOfLine;
    	fgetpos(inptr, &startOfLine);
    	
    	//iterate again for each extra line
    	for(int y = 0; y<n; y++)
    	{
		    //Return pointer to beginning of line
		    //Does nothing on first iteration but on successive iterations this
		    //ensures we're starting at the beginnning of the line for each copy
		    fsetpos(inptr, &startOfLine);
		        	
		    // iterate over pixels in scanline
		    for (int j = 0; j < inputWidth; j++)
		    {
		        // temporary storage
		        RGBTRIPLE triple;

		        // read RGB triple from infile
		        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

		        // write RGB triple to outfile, multiply writes by factor (n) of enlargement
		        for(int x=0; x<n; x++)
			        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
		    }

		    // skip over padding, if any
		    fseek(inptr, inPadding, SEEK_CUR);

		    // add sufficient padding back
		    for (int k = 0; k < outPadding; k++)
		    {
		        fputc(0x00, outptr);
		    }
		}
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
