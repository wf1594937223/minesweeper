#ifndef GAME_H
#define GAME_H
# include <stdio.h>
# include <random>
# include <ctime>
# include <game.h>
# include <vector>
# include <algorithm>
using pivvi = std::pair< int, std::vector< std::vector< int > > >;
void init(int _n, int _m);
pivvi init_map(int x, int y, int num);
pivvi tag(int x, int y);
pivvi click(int x, int y);
pivvi double_click(int x, int y);
#endif