#include <stdio.h>
#include <stdbool.h>

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("Usage: ./tofile file_name\n");
		return 1;
	}
	FILE* f = fopen(argv[1], "w");
	if(f == NULL)
	{
		printf("Failed to open file %s\n", argv[1]);
		return 1;
	}
	printf("Writing to %s, ok\n", argv[1]);
	printf("Press return twice to finish & save\n");
	
	char c = '\0', last;
	do
	{
		last = c;
		c = getchar();
		
		if(fputc(c, f) == EOF)
		{
			printf("\nError writing %c to file\n", c);
			return 1;
		}
	}
	while(!(c == '\n' && last == '\n'));
	
	fclose(f);
	
	return 0;
}
