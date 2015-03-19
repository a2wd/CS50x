/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
	//Initialise variables
	//x and y for board size,
	// i for the counter number
	int x, y, i=((d*d)-1);
	
	//Loop through board[]
	for(x = 0; x < d; x++)
	{
		for(y = 0; y < d; y++)
		{
			//Fill board[] with values
			board[x][y] = i;
			i--;
		}
	}
	
	// If there are an odd number of pieces, then
	// we must swap counters 1 and 2 around
	if(d%2 == 0)
	{
		board[d-1][d-2] = 2;
		board[d-1][d-3] = 1;
	}
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
	int x, y;
	//Loop through columns
	for(x = 0; x < d; x++)
	{
		printf(" ");
		//Board top
		for(y=0;y<d;y++)
			printf("=====");
		printf("=");
			
		printf("\n | ");
		//Loop through rows
		for(y = 0; y < d; y++)
		{
			//Print numbers for the board
			if(board[x][y] > 0)
				printf("%2i | ", board[x][y]);
			else
				printf("[] | ");
		}
		printf("\n");		
	}
	//Spacing
	printf(" ");
	for(y=0;y<d;y++)
		printf("=====");
		
	printf("=\n\n");	
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
	int i, j, found;
	int x0, y0, xt, yt, xdiff, ydiff;
	
	//Find tile in board[]
	
	for(i = 0, found = false; i < d; i++)
	{
		for(j = 0; j < d; j++)
		{
			if(board[i][j] == tile)
			{
				found = true;
				xt = i;
				yt = j;
			}			
			else if(board[i][j] == 0)
			{
				x0 = i;
				y0 = j;
			}
		}
	}
	
	//No tile to move
	if(!found)
		return false;
		
	//Check distance between tile and free space
	xdiff = abs(x0 - xt);
	ydiff = abs(y0 - yt);
	
	if((xdiff == 0 && ydiff == 1) || (xdiff == 1 && ydiff == 0))
	{
		board[xt][yt] = 0;
		board[x0][y0] = tile;
		return true;
	}
	
	//The tile can't be moved
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
	int x, y, i = 1;
	
	//Loop through board to check all counters are in the correct sequence
	for(x = 0; x < d; x++)
	{
		for(y = 0; y < d; y++)
		{
			//If anything is not in order
			//Return false
			if((board[x][y] != i) && (i < (d*d)))
				return false;
				
			i++;
		}
	}
	
    return true;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
