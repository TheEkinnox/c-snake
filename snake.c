#include <time.h>
#include "snake.h"

int play()
{
    // Initialise the random number generator with the current time as a seed
    // to avoid always generating the same numbers
    srand( time( 0 ) );

    int length = 1;
    Vector2* snake = malloc(MAX_LENGTH * sizeof(Vector2)); // Allocating MAX_LENGTH times the size of the Vector2 struct in the memory will create an array of MAX_LENGTH elements

    // If the program can't find a memory block of the required size it will not allocate anything so consider the memory is full and the app can't run.
    /* /!\ In a real life scenario, this dosn't necessarly mean the memory is full. 
        We could, for exemple, use linked lists to be able to allocate elements at non contiguous adresses /!\ */
    if ( snake == NULL )
        return 1;

    snake[0].x = WIDTH / 2 - 1;
    snake[0].y = HEIGHT / 2 - 1;

    Vector2* velocity = malloc(sizeof(Vector2)); // Allocate one time the size of the Vector2 struct in the memory for a single variable

    if ( velocity == NULL )
        return 1; // In a real application we would return different error codes to be able to handle them correctly, for exemple by displaying the corresponding error message

    velocity->x = 1; // Dereference and set the x velocity of the snake to 1 (using velocity->x is the same as (*velocity).x)
    velocity->y = 0; // Dereference and set the y velocity of the snake to 0

    Vector2* apple = malloc(sizeof(Vector2));

    if ( apple == NULL )
        return 1;

    char board[WIDTH][HEIGHT];

    initBoard( board );

    placeApple( board, apple, snake, length );

    char ch;
    // Keep looping as long as the user hasn't pressed ESC and the game is not over
    while( ( ch = getch() ) != 27 && isGameOver( snake, length ) == 0 ) // getch() is used to get the last pressed key without pausing the program
    {
        CLEAR_SCREEN();

        handleInput( ch, velocity );

        handleMovement( board, snake, length, velocity );

        handleApple( board, snake, apple, &length );

        printf( "Score : %d\n\r", length - 1 ); // Display the current score (the snake's size - 1)

        drawBoard( board );
    }

    // Deallocate our variables to avoid filling up memory with unused data
    free( snake );
    snake = NULL;
    
    free( velocity );
    velocity = NULL;

    free( apple );
    apple = NULL;

    // No need to deallocate board since the memory was automatically allocated (not manually using malloc, calloc, etc...)

    do
    {
        printf( "Score : %d | Play again ? <y/n>", length - 1 ); // Display the final score (snake's length - 1) and ask the user if they want to play again

        if ( ( ch = getchar() ) == 'y' ) // Check if the pressed key is y (getchar() is used to make the program wait until a key is pressed before continuing)
            return play();

        CLEAR_SCREEN();
    } while ( ch != 'y' && ch != 'n' ); // Keep looping until the pressed key is either y or n
    /* /!\ do while will always execute at least once before checking if the condition is met /!\ */

    return 0;
}

char getBoardChar( int x, int y ) {
    if ( ( x == 0 && y == 0 ) || ( x == WIDTH - 1 && y == HEIGHT - 1 ) )
        return '/';

    if ( ( x == 0 && y == HEIGHT - 1 ) || ( x == WIDTH - 1 && y == 0 ) )
        return '\\';

    if ( x == 0 || x == WIDTH - 1 )
        return '|';

    if ( y == 0 || y == HEIGHT - 1 )
        return '-';

    return ' ';
}

void initBoard( char board[WIDTH][HEIGHT] )
{
    for ( int i = 0; i < WIDTH; i++ )
        for ( int j = 0; j < HEIGHT; j++ )
            board[i][j] = getBoardChar( i, j );
}

int isSnake( const Vector2* snake, int length, const Vector2* point, int firstIndex ) {
    // We should check if pointers are null but we know this function will only be used in a safe context
    for ( int i = firstIndex; i < length; i++ )
    {
        if ( point->x == snake[i].x && point->y == snake[i].y )
            return 1;
    }

    return 0;
}

void placeApple( char board[WIDTH][HEIGHT], Vector2* apple, const Vector2* snake, int length ) {
    // We should check if pointers are null but we know this function will only be used in a safe context
    do
    {
        apple->x = RANDOM( 1, WIDTH - 2 );
        apple->y = RANDOM( 1, HEIGHT - 2 );
    } while ( isSnake( snake, length, apple, 0 ) );

    board[apple->x][apple->y] = APPLE_CHAR;
}

void handleInput( char input, Vector2* velocity )
{
    // We should check if pointers are null but we know this function will only be used in a safe context
    switch ( input )
    {
        case 'w':
            if ( (*velocity).y != -1 )
            {
                velocity->x = 0;
                velocity->y = -1;
            }
            break;
        case 'a':
            if ( velocity->x != 1 )
            {
                velocity->x = -1;
                velocity->y = 0;
            }
            break;
        case 's':
            if ( velocity->y != 1 )
            {
                velocity->x = 0;
                velocity->y = 1;
            }
            break;
        case 'd':
            if ( velocity->x != -1 )
            {
                velocity->x = 1;
                velocity->y = 0;
            }
            break;
        default:
            break;
    }
}

void handleMovement( char board[WIDTH][HEIGHT], Vector2* snake, int length, const Vector2* velocity )
{
    // We should check if pointers are null but we know this function will only be used in a safe context
    if ( snake[length - 1].x > 0 && snake[length - 1].x < WIDTH &&
         snake[length - 1].y > 0 && snake[length - 1].y < HEIGHT )
    {
        board[snake[length - 1].x][snake[length - 1].y] = ' ';
    }

    // Loop through all points of the snake starting from it's tail
    for ( int i = length - 1; i >= 0; i-- )
    {
        if ( i == 0 )
        {
            snake[i].x += velocity->x;
            snake[i].y += velocity->y;
        }
        else
        {
            snake[i].x = snake[i-1].x;
            snake[i].y = snake[i-1].y;
        }

        // Set the character at the current snake chunk's position to the head character (HEAD_CHAR) for the first chunk (i == 0)
        // or the body character (BODY_CHAR) for the other chunks (i != 0)
        board[snake[i].x][snake[i].y] = i == 0 ? HEAD_CHAR : BODY_CHAR;
    }
}

void handleApple( char board[WIDTH][HEIGHT], const Vector2* snake, Vector2* apple, int* length )
{
    // We should check if pointers are null but we know this function will only be used in a safe context
    if ( snake[0].x == apple->x && snake[0].y == apple->y )
    {
        (*length)++;
        placeApple( board, apple, snake, *length );
    }
}

void drawBoard( const char board[WIDTH][HEIGHT] )
{
    // Should check if pointers are null but we know this function will only be used in a safe context
    for ( int i = 0; i < HEIGHT; i++ )
    {
        for ( int j = 0; j < WIDTH; j++ )
            printf( "%c", board[j][i] );

        printf( "\n\r" );
    }
}

int isGameOver( const Vector2* snake, int length )
{
    // Should check if pointers are null but we know this function will only be used in a safe context
    if ( snake[0].x == 0 || snake[0].x == WIDTH -1 || snake[0].y == 0 || snake[0].y == HEIGHT - 1 )
    {
        printf( "You lost ! Next time avoid the edges ;p\n\r" );
        return 1;
    }
    else if ( length > 1 && isSnake( snake, length, &snake[0], 1 ) > 0 )
    {
        printf( "You lost ! Biting your own tail must be so painful O-O\n\r" );
        return 1;
    }
    else if ( length == MAX_LENGTH )
    {
        printf( "Congratulations ! You ate all the apples :D\n\r" );
        return 1;
    }

    return 0;
}