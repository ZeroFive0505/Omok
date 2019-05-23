#pragma once

#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 18 // Size of Board
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define UP 72
#define SPACE 32



enum STAT { EMPTY, SELECTED, BLACK, WHITE };

extern STAT Buffer[SIZE][SIZE];
extern STAT Screen[SIZE][SIZE];

extern bool black_turn;
extern int cur_x;
extern int cur_y;
extern bool game_end;


void GotoXY(int, int); // Coordinate X, Y

void DrawBoard();

void Initialize();

void Control();

void Move(int, int);

bool Boundary(int, int);


void Checking();

void Chain_check(int, int);

void GameOver();


