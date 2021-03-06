#pragma once

#include "tetris.h"


char **map_init(void);
void map_destroy(char **map);

void print_map(char **map, struct bloc *bloc, int score);

int check_lines(char **map);
int is_coliding(char **map, struct bloc *bloc);
int put_bloc(char **map, struct bloc *bloc);

#define CLEAR "\033[1;1H\033[2J"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
