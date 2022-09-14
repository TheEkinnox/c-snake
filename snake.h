#include <ncurses.h> // We want to use advanced terminal features so we need to tell our program where to find them
#include <stdlib.h> // We want to use random numbers and malloc so we need to include stdlib.h

#pragma once // Tell our program to only include the functions, constants and structs in this file once (if it already exist, use our)

#define WIDTH 16
#define HEIGHT 9

#define HEAD_CHAR '0'
#define BODY_CHAR 'o'
#define APPLE_CHAR 'x'
#define MAX_LENGTH ( WIDTH - 2 ) * ( HEIGHT - 2 )

#define RANDOM( min, max ) ( rand() % ( max - min + 1 ) ) + min
#define CLEAR_SCREEN() printf( "\033c" );

/// @brief A structure representing a 2 dimensional vector (basically a point)
typedef struct s_Vector2
{
    int x;
    int y;
} Vector2;

int play(void);
char getBoardChar( int x, int y );
void initBoard( char board[WIDTH][HEIGHT] );
int isSnake( const Vector2* snake, int length, const Vector2* point, int firstIndex );
void placeApple( char board[WIDTH][HEIGHT], Vector2* apple, const Vector2* snake, int length );
void handleInput( char input, Vector2* velocity );
void handleMovement( char board[WIDTH][HEIGHT], Vector2* snake, int length, const Vector2* velocity );
void handleApple( char board[WIDTH][HEIGHT], const Vector2* snake, Vector2* apple, int* length );
void drawBoard( const char board[WIDTH][HEIGHT] );
int isGameOver( const Vector2* snake, int length );