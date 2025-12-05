# include <stdio.h>
# include <random>
# include <ctime>
# include "game.h"
# include <vector>
# include <algorithm>
# include <iostream>
# define mkp make_pair
using std::vector;
using std::swap;
using std::pair;
using std::make_pair;
static int n, m;
static int tot_mine, last_mine;
static vector< vector< int > > f, t;
static int p[9] = {0, 1, 0, -1, 0, 1, 1, -1, -1};
static int q[9] = {0, 0, 1, 0, -1, 1, -1, 1, -1};
//n lines, m cals
//tot_mine mines, last_mine untagged mines
//f means the "map", tag means the state of a box(being showed, being tagged, etc.)
//p, q means the 8 nearest box's relative position
//f: -1 if mine, 0 if blank
//t: 0 if unrevealed, 1 if tagged, -1 if revealed
/*
pivvi returns: the operation is available or not(.first neq 0 or not), after the 
operation, whether the game is lose or win or continue(.first = -1 or -2 or lastmine),
and return two-dimensional array f if the order is init, t otherwise.
*/
void init(int _n, int _m)
{
    n = _n, m = _m;
    f.assign(n + 1, vector<int>(m + 1, 0));
    t.assign(n + 1, vector<int>(m + 1, 0));
    return;
}
pivvi check()
{
    int i, j;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= m; j++)
        {
            if (f[i][j] != -1 && t[i][j] != -1)
                return mkp(0, t);
            if (f[i][j] == -1 && t[i][j] == -1)
                return mkp(-1, t);
        }
    }
    return mkp(1, t);
}
int near_mine(int x, int y)
{
    int i, j = 0;
    for (i = 1; i <= 8; i++)
    {
        if (x + p[i] < 1 || y + q[i] < 1 || x + p[i] > n || y + q[i] > m)
            continue;
        j += (f[x + p[i]][y + q[i]] == -1);
    }
    return j;
}
int near_tag(int x, int y)
{
    int i, j = 0;
    for (i = 1; i <= 8; i++)
    {
        if (x + p[i] < 1 || y + q[i] < 1 || x + p[i] > n || y + q[i] > m)
            continue;
        j += (t[x + p[i]][y + q[i]] == 1);
    }
    return j;
}
pivvi init_map(int x, int y, int num)
{
    tot_mine = last_mine = num;
    int i, j, u, v;
    std::mt19937 ran(time(0));
    int *a;
    a = new int[n * m];
    //psu random_shuffle begin
    for (i = 0; i < 9; i++)
    {
        if (x + p[i] < 1 || y + q[i] < 1 || x + p[i] > n || y + q[i] > m)
            continue;
        f[x + p[i]][y + q[i]] = 1;
    }
    for (i = 0, j = 0; i < n * m; i++)
    {
        if (f[i / m + 1][i % m + 1])
            continue;
        a[j++] = i;
    }
    for (i = 0; i < 9; i++)
    {
        if (x + p[i] < 1 || y + q[i] < 1 || x + p[i] > n || y + q[i] > m)
            continue;
        f[x + p[i]][y + q[i]] = 0;
    }
    // std::cout << "checkpoint4" << std::endl;
    for (i = 1; i < j; i++)
        swap(a[i], a[ran() % i]);
    for (i = 0; i < num; i++)
    {
        u = a[i] / m + 1;
        v = a[i] % m + 1;
        f[u][v] = -1;
    }
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= m; j++)
            f[i][j] = (!f[i][j]) ? near_mine(i, j) : f[i][j];
    }
    // std::cout << "checkpoint7" << std::endl;
    return mkp(last_mine + 1, f);
}
void ext(int x, int y)
{
    int i, j;
    if (t[x][y] < 0)
        return;
    t[x][y] = -1;
    //std :: cerr << "exting" << x << ' ' << y << f[x][y] << std :: endl;
    if (f[x][y])
        return;
    for (i = 1; i <= 8; i++)
    {
        if (x + p[i] < 1 || y + q[i] < 1 || x + p[i] > n || y + q[i] > m)
            continue;
        ext(x + p[i], y + q[i]);
    }
    return;
}
pivvi tag(int x, int y)
{
    if (t[x][y] < 0)
        return mkp(0, t);
    if (!last_mine && !t[x][y])
        return mkp(0, t);
    last_mine += t[x][y];
    t[x][y] ^= 1;
    last_mine -= t[x][y];
    return mkp(last_mine + 1, t);
}
pivvi click(int x, int y)
{
    if (t[x][y])
        return mkp(0, t);
    if (f[x][y] < 0)
        return mkp(-1, t);
    // std::cout << "checkpoint1" << std::endl;
    ext(x, y);
    // std::cout << "checkpoint1" << std::endl;
    if (check().first == 1)
        return mkp(-2, t);
    // std::cout << "checkpoint1" << std::endl;
    return mkp(last_mine + 1, t);
}
pivvi double_click(int x, int y)
{
    // std::cerr << "d_c tag" << std::endl;
    // upside ok
    int i, j;
    if (t[x][y] != -1 || !f[x][y])
        return mkp(0, t);
    if (near_mine(x, y) != near_tag(x, y))
        return mkp(0, t);
    for (i = 1; i <= 8; i++)
    {
        if (x + p[i] < 1 || y + q[i] < 1 || x + p[i] > n || y + q[i] > m)
            continue;
        if (f[x + p[i]][y + q[i]] != -1)
            click(x + p[i], y + q[i]);
    }
    j = check().first;
    if (j == -1)
        return mkp(-1, t);
    if (!j)
        return mkp(last_mine + 1, t);
    if (j == 1)
        return mkp(-2, t);
}