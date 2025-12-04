//mine: 3x2; interval: 1;
# include <iostream>
# include "game.h"
# include "graph.h"
using std::cin, std::cout, std::endl;
int main()
{
    int i, j, n, m, mine, op;
    while(1)
    {
        cout << "\033[2J\033[H"; //clear
        cout << "欢迎来到扫雷游戏" << endl << endl;
        cout << "难度1：简单模式，9×9，10雷" << endl;
        cout << "难度2：中等模式，16×16，40雷" << endl;
        cout << "难度3：困难模式，16×30，99雷" << endl;
        cout << "难度4：自定义模式" << endl;
        cout << "请选择难度（输入后按回车）（输入0退出游戏）: " << endl;
        while(1)
        {
            cin >> op;
            if (!op)
                break;
            else if (op == 1)
                n = 9, m = 9, mine = 10;
            else if (op == 2)
                n = 16, m = 16, mine = 40;
            else if (op == 3)
                n = 16, m = 30, mine = 99;
            else if (op == 4)
            {
                cout << "请输入行数，列数（范围分别为9~24， 9~30，中间空格隔开，输入后按回车）：";
                while(1)
                {
                    cin >> n >> m;
                    if (n < 9 || n > 24 || m < 9 || m > 30)
                    {
                        cout << "输入不合法，请重新输入：";
                        continue;
                    }
                    break;
                }
                int lim = std::min((int)floor(0.924 * n * m) + 2, n * m - 10);
                cout << "请输入雷数（范围为10~" << lim << "，输入后按回车）：";
                while(1)
                {
                    cin >> mine;
                    if (mine < 10 || mine > lim)
                    {
                        cout << "输入不合法，请重新输入：";
                        continue;
                    }
                    break;
                }
            }
            else
            {
                cout << "输入不合法，请重新输入：";
                continue;
            }
            break;
        }
        if (!op)
        {
            cout << "欢迎下次再来！" << endl;
            break;
        }
        cout << "请按任意键开始游戏！";
        getchar();
        init_gra(n, m, mine);
        while(1)
        {
            j = one_event();
            if (j >= 0)
                continue;
            if (j < 0)
                break;
        }
    }
    return 0;
}