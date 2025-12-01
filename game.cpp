# include <stdio.h>
# include <random>
# include <ctime>
# include <game.h>
# include <vector>
# include <algorithm>
# define mkp make_pair
using std::vector;
using std::swap;
using std::pair;
using std::make_pair;
static int n, m;
static vector< vector< int > > f, t;
static int p[9] = {0, 1, 0, -1, 0, 1, 1, -1, -1};
static int q[9] = {0, 0, 1, 0, -1, 1, -1, 1, -1};
//n lines, m cals
//f means the "map", tag means the state of a box(being showed, being tagged, etc.)
//p, q means the 8 nearest box's relative position
//f: -1 if mine, 0 if blank
//t: 0 if unrevealed, 1 if tagged, -1 if revealed
/*
pivvi returns: the operation is available or not(.first neq 0 or not), after
the operation, whether the game is lose or win or continue(.first = -1 or 2 or 1), */
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
        j += (f[x + p[i]][y + q[i]] == -1);
    return j;
}
int near_tag(int x, int y)
{
    int i, j = 0;
    for (i = 1; i <= 8; i++)
        j += (t[x + p[i]][y + q[i]] == 1);
    return j;
}
pivvi init_map(int x, int y, int num)
{
    int i, j, u, v;
    std::mt19937 ran(time(0));
    static int *a;
    a = new int[n * m];
    //psu random_shuffle begin
    for (i = 0; i < 9; i++)
        f[x + p[i]][y + q[i]] = 1;
    for (i = 0; i < n * m; i++)
    {
        if (f[a[i] / m + 1][a[i] % m + 1])
            continue;
        a[++j] = i;
    }
    for (i = 0; i < 9; i++)
        f[x + p[i]][y + q[i]] = 0;
    for (i = 0; i < n * m - 9; i++)
    {
        a[i] = i;
        swap(a[i], a[ran() % i]);
    }
    for (i = 0; i < num; i++)
    {
        u = a[i] / m + 1;
        v = a[i] % m + 1;
        f[u][v] = -1;
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            f[i][j] = (!f[i][j]) ? near_mine(i, j) : f[i][j];
    }
    return mkp(1, f);
}
void ext(int x, int y)
{
    int i, j;
    if (t[x][y] < 0)
        return;
    if (f[x][y])
        return;
    t[x][y] = -1;
    for (i = 1; i <= 8; i++)
        ext(x + p[i], x + q[i]);
    return;
}
pivvi tag(int x, int y)
{
    if (t[x][y] < 0)
        return mkp(0, t);
    t[x][y] ^= 1;
    return mkp(1, t);
}
pivvi click(int x, int y)
{
    if (t[x][y])
        return mkp(0, t);
    t[x][y] = -1;
    if (f[x][y] < 0)
        return mkp(-1, t);
    ext(x, y);
    if (check().first == 1)
        return mkp(2, t);
    return mkp(1, t);
}
pivvi double_click(int x, int y)
{
    int i, j;
    if (t[x][y] != -1 || f[x][y])
        return mkp(0, t);
    if (near_mine(x, y) != near_tag(x, y))
        return mkp(0, t);
    for (i = 1; i <= 8; i++)
    {
        if (f[x + p[i]][y + q[i]] != -1)
            click(x + p[i], y + q[i]);
    }
    j = check().first;
    if (j == -1)
        return mkp(-1, t);
    if (!j)
        return mkp(1, t);
    if (j == 1)
        return mkp(2, t);
}