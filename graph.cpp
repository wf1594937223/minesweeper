//mine: 3x2; interval: 1;
# include "cgt.h"
# include "game.h"
# include <sstream>
# include <iostream>
# include <string.h>
# define mkp make_pair
using std::vector;
using std::swap;
using std::pair;
using std::make_pair;
using pii = pair< int,int >;
static int n, m, mpn, mpm, flag;
static int tot_mine, last_mine;
static vector< vector< int > > f, t, mp;
static int p[7] = {0, 0, 0, 1, 1, 1};
static int q[7] = {0, 1, 2, 0, 1, 2};
pii chosen;
//p, q: a block
//(x, y)'s block starts from (3x + 1, 4y + 1)
pii trans(pii tmp)
{
    int x = tmp.first, y = tmp.second;
    if (x < 1 || y < 1 || x > mpn || y > mpm)
        return mkp(-1, -1);
    return mkp(3 * x + 1, 4 * y + 1);
}
pii invtrans(pii tmp)
{
    int x = tmp.first, y = tmp.second;
    if (!(x % 3) || !(y % 4) || x <= 3 || y <= 4 || x > mpn || y > mpm)
        return mkp(-1, -1);
    return mkp((x - 1) / 3, (y - 1) / 4);
}
/*
-1: frame
-1-: already opened boxes
0-: hided boxes
1-: tagged boxes
*/
int prt_mode(pii tmp, int mode)
{
    //text color, background color
    /*
    -1: frame
    -1-: already opened boxes
    0-: hided boxes
    1-: tagged boxes
    */
    int x = tmp.first, y = tmp.second;
    std::swap(x, y); //I think x, y inversed when I coded
    if (mode == -1)
    {
        cgt_print_str(" ", x, y, COLOR_WHITE, COLOR_WHITE);
        return 1;
    }
    if (mode == -10)
    {
        cgt_print_str(" ", x, y, COLOR_LIGHT_WHITE, COLOR_LIGHT_WHITE);
        return 1;
    }
    if (mode == -11)
    {
        cgt_print_str("1", x, y, COLOR_BLUE, COLOR_LIGHT_WHITE);
        return 1;
    }
    if (mode == -12)
    {
        cgt_print_str("2", x, y, COLOR_GREEN, COLOR_LIGHT_WHITE);
        return 1;
    }
    if (mode == -13)
    {
        cgt_print_str("3", x, y, COLOR_RED, COLOR_LIGHT_WHITE);
        return 1;
    }
    if (mode == -14)
    {
        cgt_print_str("4", x, y, COLOR_MAGENTA, COLOR_LIGHT_WHITE);
        return 1;
    }
    if (mode == -15)
    {
        cgt_print_str("5", x, y, COLOR_YELLOW, COLOR_LIGHT_WHITE);
        return 1;
    }
    if (mode == -16)
    {
        cgt_print_str("6", x, y, COLOR_CYAN, COLOR_LIGHT_WHITE);
        return 1;
    }
    if (mode == -17)
    {
        cgt_print_str("7", x, y, COLOR_LIGHT_RED, COLOR_LIGHT_WHITE);
        return 1;
    }
    if (mode == -18)
    {
        cgt_print_str("8", x, y, COLOR_LIGHT_GREEN, COLOR_LIGHT_WHITE);
        return 1;
    }
    if (mode == 0)
    {
        cgt_print_str(" ", x, y, COLOR_WHITE, COLOR_YELLOW);
        return 1;
    }
    if (mode == 1)
    {
        cgt_print_str(" ", x, y, COLOR_WHITE, COLOR_LIGHT_YELLOW);
        return 1;
    }
    if (mode == 10)
    {
        cgt_print_str(" ", x, y, COLOR_WHITE, COLOR_RED);
        return 1;
    }
    if (mode == 11)
    {
        cgt_print_str("F", x, y, COLOR_BLACK, COLOR_RED);
        return 1;
    }
    return 0;
}
void prt_single(pii tmp)
{
    int x = tmp.first, y = tmp.second;
    int tx = invtrans(tmp).first, ty = invtrans(tmp).second;
    if (invtrans(tmp) != mkp(-1, -1))
    {
        if (tmp == trans(invtrans(tmp)))
        {
            if (t[tx][ty] == 0)
            {
                if (mkp(tx, ty) == chosen)
                    prt_mode(tmp, 1);
                else
                    prt_mode(tmp, 0);
                return;
            }
            if (t[tx][ty] == 1)
            {
                prt_mode(tmp, 11);
                return;
            }
            if (t[tx][ty] == -1)
            {
                prt_mode(tmp, -10-f[tx][ty]);
                return;
            }
        }
        else
        {
            if (t[tx][ty] == 0)
            {
                if (mkp(tx, ty) == chosen)
                    prt_mode(tmp, 1);
                else
                    prt_mode(tmp, 0);
                return;
            }
            if (t[tx][ty] == 1)
            {
                prt_mode(tmp, 10);
                return;
            }
            if (t[tx][ty] == -1)
            {
                prt_mode(tmp, -10);
                return;
            }
        }
    }
    else
    {
        if (x < 3 || y < 3)
            return;
        else
        {
            prt_mode(tmp, -1);
            return;
        }
    }
    //error
    return;
}
void init_gra(int _n, int _m, int _mine)
{
    cgt_init();
    cgt_clear_screen();
    n = _n;
    m = _m;
    tot_mine = last_mine = _mine;
    flag = 0;
    init(n, m);
    mpn = 3 * n + 3;
    mpm = 4 * m + 4;
    f.assign(n + 1, vector<int>(m + 1, 0));
    t.assign(n + 1, vector<int>(m + 1, 0));
    mp.assign(mpn + 1, vector<int>(mpm + 1, 0));
    return;
}
void prt_first_line()
{
     int i, j;
    //cgt_clear_screen();
    std::stringstream ss;
    char tmps[110] = {0};
    memset(tmps, ' ', sizeof(tmps) - 1);
    cgt_print_str(tmps, 1, 1, COLOR_LIGHT_WHITE, COLOR_BLACK);
    return;
}
void prt_screen()
{
    int i, j;
    //cgt_clear_screen();
    std::stringstream ss;
    char tmps[110] = {0};
    //memset(tmps, ' ', sizeof(tmps) - 1);
    //cgt_print_str(tmps, 1, 1, COLOR_LIGHT_WHITE, COLOR_BLACK);
    ss << "扫雷 : " << n << "×" << m << " , " << "雷数 : " << tot_mine << " , "
        << "剩余 : " << last_mine;
    ss.getline(tmps, 110);
    cgt_print_str(tmps, 1, 1, COLOR_LIGHT_WHITE, COLOR_BLACK);
    for (i = 3; i <= mpn; i++)
    {
        for (j = 3; j <= mpm; j++)
            prt_single(mkp(i, j));
    }
    return;
}
void game_lose()
{
    int i, j;
    cgt_clear_screen();
    std::stringstream ss;
    char tmps[110] = {0};
    ss << "很遗憾，你Cia到了llo～(∠・ω< )⌒☆";
    ss.getline(tmps, 110);
    cgt_print_str(tmps, 1, 1, COLOR_LIGHT_WHITE, COLOR_BLACK);
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= m; j++)
        {
            if (f[i][j] == -1)
                t[i][j] = 1;
            else
                t[i][j] = -1;
        }
    }
    for (i = 3; i <= mpn; i++)
    {
        for (j = 3; j <= mpm; j++)
            prt_single(mkp(i, j));
    }
    //I think x, y inversed when I coded
    cgt_print_str("请按回车键继续", 1, mpn + 1, COLOR_LIGHT_WHITE, COLOR_BLACK);
    while (true)
    {
        if (cgt_has_key())
        {
            char ch;
            cgt_get_key(ch);
            break;
        }
        cgt_msleep(50);
    }
    cgt_clear_screen();
    return;
}
void game_win()
{
    int i, j;
    cgt_clear_screen();
    std::stringstream ss;
    char tmps[110] = {0};
    ss << "恭喜你，你成功通关了Ciallo～(∠・ω< )⌒☆";
    ss.getline(tmps, 110);
    cgt_print_str(tmps, 1, 1, COLOR_LIGHT_WHITE, COLOR_BLACK);
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= m; j++)
        {
            if (f[i][j] == -1)
                t[i][j] = 1;
            else
                t[i][j] = -1;
        }
    }
    for (i = 3; i <= mpn; i++)
    {
        for (j = 3; j <= mpm; j++)
            prt_single(mkp(i, j));
    }
    //I think x, y inversed when I coded
    cgt_print_str("请按回车键继续", 1, mpn + 1, COLOR_LIGHT_WHITE, COLOR_BLACK);
    while (true)
    {
        if (cgt_has_key())
        {
            char ch;
            cgt_get_key(ch);
            break;
        }
        cgt_msleep(50);
    }
    cgt_clear_screen();
    return;
}
int one_event()
{
    // clean buffer (or should not?)
    // while (cgt_has_mouse())
    // {
    //     int x, y, button, event;
    //     cgt_get_mouse(x, y, button, event);
    // }
    // I prefer cleaning before calling
    while (!cgt_has_mouse())
        cgt_msleep(20);
    int x, y, button, event, fl = 0;
    cgt_get_mouse(x, y, button, event);
    std::swap(x, y); //I think x, y inversed when I coded
    pii now = mkp(x, y);
    pivvi tmp;
    int cli = (button == MOUSE_BUTTON_LEFT && event == MOUSE_CLICK),
        dou_cli = (button == MOUSE_BUTTON_LEFT && event == MOUSE_DOUBLECLICK),
        mv = (event == MOUSE_MOVE),
        ta = (button == MOUSE_BUTTON_RIGHT && event == MOUSE_CLICK);
    if (cli)
    {
        if (invtrans(mkp(x, y)) == mkp(-1, -1))
            return 0;
        pii transxy = invtrans(mkp(x, y));
        x = transxy.first;
        y = transxy.second;
        //std::cout << "checkpoint0" << x << " " << y << std::endl;
        if (!flag)
        {
            flag = 1;
            //std::cout << tx << " " << ty << std::endl;
            //test upside right
            f = init_map(x, y, tot_mine).second;
        }
        tmp = click(x, y);
        //std::cout << "checkpoint2" << std::endl;
        if (!tmp.first)
            return 0;
        if (tmp.first == -1)
        {
            game_lose();
            return -1;
        }
        if (tmp.first == -2)
        {
            game_win();
            return -2;
        }
        fl = 1;
        last_mine = tmp.first - 1;
        t = tmp.second;
    }
    if (dou_cli)
    {
        if (invtrans(mkp(x, y)) == mkp(-1, -1))
            return 0;
        pii transxy = invtrans(mkp(x, y));
        x = transxy.first;
        y = transxy.second;
        if (!flag)
            return 0;
        tmp = double_click(x, y);
        if (!tmp.first)
            return 0;
        if (tmp.first == -1)
        {
            game_lose();
            return -1;
        }
        if (tmp.first == -2)
        {
            game_win();
            return -2;
        }
        fl = 1;
        last_mine = tmp.first - 1;
        t = tmp.second;
    }
    if (ta)
    {
        if (invtrans(mkp(x, y)) == mkp(-1, -1))
            return 0;
        pii transxy = invtrans(mkp(x, y));
        x = transxy.first;
        y = transxy.second;
        tmp = tag(x, y);
        prt_first_line();
        if (!tmp.first)
            return 0;
        if (tmp.first == -1)
        {
            game_lose();
            return -1;
        }
        if (tmp.first == -2)
        {
            game_win();
            return -2;
        }
        fl = 1;
        last_mine = tmp.first - 1;
        t = tmp.second;
    }
    if (mv)
    {
        chosen = invtrans(mkp(x, y));
        fl = 1;
    }
    prt_screen();
    return 1;
}