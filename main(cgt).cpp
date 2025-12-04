/*
    CGT Test.
*/


#include "cgt.h"


/**
 * 在指定位置打印一行字，并等待用户按下任意按键。 
 */
void wait_for_enter(const char* prompt = "按下任意键继续...", int x = -1, int y = -1) {
    // 跳转光标到指定位置。
    if (x != -1 && y != -1)
        cgt_gotoxy(x, y);

    // 打印提示信息。
    cgt_print_str(prompt ? prompt : "");

    // 清空键盘输入事件缓冲。
    while (cgt_has_key()) {
        char ch;
        cgt_get_key(ch);
    }


    // 等待任意按键。
    while (true) {
        if (cgt_has_key()) {
            char ch;
            cgt_get_key(ch);
            // 读到任意按键，都可结束。
            break;
        }

        // 适当休息，防止占满电脑 CPU。
        cgt_msleep(50);
    }
}


void test_clearscreen_colors() {
    const int COLORS[] = {
        COLOR_RED,
        COLOR_GREEN,
        COLOR_BLUE,
        COLOR_YELLOW,
        COLOR_LIGHT_BLUE,
        COLOR_LIGHT_CYAN,
        COLOR_LIGHT_GREEN,
        COLOR_LIGHT_MAGENTA,
        COLOR_LIGHT_RED
    };

    const int NCOLORS = sizeof(COLORS) / sizeof(COLORS[0]);


    for (int i = 0; i < NCOLORS; i++) {
        int color = COLORS[i];
        cgt_clear_screen(color);

        int x, y;
        cgt_getxy(x, y);
        wait_for_enter("测试：将屏幕刷成指定颜色。按下任意键继续...");
    }
}


void test_print_str() {
    cgt_print_str("1. 我 (x, y) = (10, 0) 处。按任意键继续", 10, 0);
    wait_for_enter("");

    
    cgt_print_str("2. 我 (x, y) = (0, 20) 处。按任意键继续", 0, 20);
    wait_for_enter("");

    cgt_print_str("3. 我 (x, y) = (10, 10) 处，红字绿底。按任意键继续", 10, 10, COLOR_RED, COLOR_GREEN);
    wait_for_enter("");

    cgt_print_str("4. 我 (x, y) = 当前光标处，黄字蓝底。按任意键继续", -1, -1, COLOR_YELLOW, COLOR_BLUE);
    wait_for_enter("");
}


void test_print_value() {
    cgt_clear_screen();

    cgt_print_str("测试打印整数：", 0, 0);
    for (int i = -5; i <= 5; i++) {
        cgt_print_int(i, 0, i + 6, (i % 2 == 0 ? COLOR_LIGHT_YELLOW : COLOR_LIGHT_GREEN));
    }
    wait_for_enter();

    cgt_print_str("测试打印浮点数：", 0, 0);
    for (int i = -5; i <= 5; i++) {
        double val = i * 0.5;
        cgt_print_double(val, 0, i + 18, (i % 2 == 0 ? COLOR_LIGHT_CYAN : COLOR_LIGHT_RED));
    }
    wait_for_enter();
}


void test_color_block() {
    
    cgt_clear_screen();
    cgt_print_str("在 (10, 0) 处打印了一个宽度为 1 的 红 色色块。按任意键继续", 0, 0);
    cgt_print_str(" ", 10, 0, COLOR_BLACK, COLOR_RED);
    wait_for_enter("");

    cgt_clear_screen();
    cgt_print_str("在 (10, 2) 处打印了一个宽度为 2 的 绿 色色块。按任意键继续", 0, 0);
    cgt_print_str("  ", 10, 2, COLOR_BLACK, COLOR_GREEN);
    wait_for_enter("");

    cgt_clear_screen();
    cgt_print_str("在 (2, 4) 处打印了一个宽度为 3 的 蓝 色色块。按任意键继续", 0, 0);
    cgt_print_str("   ", 2, 4, COLOR_BLACK, COLOR_BLUE);
    wait_for_enter("");

    cgt_clear_screen();
    cgt_print_str("在 (2, 6) 处打印了一个宽度为 4 的 黄 色色块。按任意键继续", 0, 0);
    cgt_print_str("    ", 2, 6, COLOR_BLACK, COLOR_YELLOW);
    wait_for_enter("");

    cgt_clear_screen();
    cgt_print_str("在 (2, 8) 处打印了一个宽度为 5 的 紫 色色块。按任意键继续", 0, 0);
    cgt_print_str("     ", 2, 8, COLOR_BLACK, COLOR_MAGENTA);
    wait_for_enter("");
}


void test_sjtu() {
    const int BACKGROUND = COLOR_LIGHT_RED;
    const int FOREGROUND = COLOR_WHITE;

    cgt_clear_screen(BACKGROUND);
    cgt_print_str("绘制一个 SJTU. 按下任意键继续。", 1, 1, COLOR_LIGHT_YELLOW, BACKGROUND);
    

    const char* sjtu_lines[] = {

        "*******  **********  **********  **      **",
        "*******  **********  **********  **      **",
        "**           **          **      **      **",
        "**           **          **      **      **",
        "*******      **          **      **      **",
        "*******      **          **      **      **",
        "     **      **          **      **      **",
        "     **      **          **      **      **",
        "*******  ******          **      **********",
        "*******  ******          **      **********"
    };


    const long nlines = sizeof(sjtu_lines) / sizeof(sjtu_lines[0]);
    const long offset_x = 3;
    const long offset_y = 3;

    for (long row = 0; row < nlines; row++) {
        const char* line = sjtu_lines[row];

        for (long col = 0; line[col] != '\0'; col++) {
            if (line[col] == '*')
                cgt_print_char(' ', col + offset_x, row + offset_y, FOREGROUND, FOREGROUND);
        }
    }
    

    wait_for_enter("");
}


void test_mouse() {
    cgt_clear_screen();


    // 清空之前可能残留的鼠标事件。
    while (cgt_has_mouse()) {
        int x, y, button, event;
        cgt_get_mouse(x, y, button, event);
    }


    const int EXIT_BLOCK_X = 0;
    const int EXIT_BLOCK_Y = 1;
    const int EXIT_BLOCK_WIDTH = 5;
    for (int i = 0; i < EXIT_BLOCK_WIDTH; i++) {
        cgt_print_str(" ", EXIT_BLOCK_X + i, EXIT_BLOCK_Y, COLOR_BLACK, COLOR_LIGHT_GREEN);
    }
    cgt_print_str("点击上面的绿色块块以结束测试。", 0, 2);


    while (true) {
        if (!cgt_has_mouse()) {
            cgt_msleep(20);
            continue;
        }

        int x, y, button, event;
        cgt_get_mouse(x, y, button, event);


        // 检查是否点击了退出区域
        bool isClick = event == MOUSE_CLICK;
        bool inExit = x >= EXIT_BLOCK_X && x < EXIT_BLOCK_X + EXIT_BLOCK_WIDTH && y == EXIT_BLOCK_Y;
        if (isClick && inExit) {
            break;
        }


        if (y < 3)  // 忽略左上提示信息区域的点击事件。
            continue;


        const char* eventDesc;
        if (event == MOUSE_MOVE) {
            eventDesc = "移动    ";
        } else if (event == MOUSE_CLICK) {
            eventDesc = "点击    ";
        } else if (event == MOUSE_DOUBLECLICK) {
            eventDesc = "双击    ";
        } else if (event == MOUSE_RELEASE) {
            eventDesc = "释放    ";
        } else {
            eventDesc = "未知事件";
        }

        const char* buttonDesc;
        if (button == MOUSE_BUTTON_LEFT) {
            buttonDesc = "左键  ";
        } else if (button == MOUSE_BUTTON_RIGHT) {
            buttonDesc = "右键  ";
        } else if (button == MOUSE_BUTTON_MIDDLE) {
            buttonDesc = "中键  ";
        } else {
            buttonDesc = "无按钮";
        }


        cgt_gotoxy(0, 0);
        cgt_print_str("鼠标测试：发生事件 : ");
        cgt_print_str(eventDesc);
        cgt_print_str("。 按键 : ");
        cgt_print_str(buttonDesc);
        cgt_print_str("。 坐标 : (");
        cgt_print_int(x);
        cgt_print_str(", ");
        cgt_print_int(y);
        cgt_print_str(") 。            ");  // 多余的空格用于覆盖之前的内容。

 
        // 在当前位置打印标记
        char mark = '\0';
        if (event == MOUSE_CLICK) {
            if (button == MOUSE_BUTTON_LEFT) {
                mark = 'L';
            } else if (button == MOUSE_BUTTON_RIGHT) {
                mark = 'R';
            } else if (button == MOUSE_BUTTON_MIDDLE) {
                mark = 'M';
            } else {
                mark = '*';
            }
        }

        if (mark != '\0') {
            cgt_print_char(mark, x, y, COLOR_LIGHT_RED);
        }
    }
}


void test_keyboard() {
    cgt_clear_screen();
    cgt_print_str("键盘测试。点击“EXIT”以退出测试；点击色卡颜色改变前后景色。", 6, 0);
    cgt_print_str("EXIT", 0, 0, COLOR_BLACK, COLOR_LIGHT_GREEN);
    cgt_print_str("确认输入法为英文模式。输入点东西试试看。", 0, 1);

    int foreground = COLOR_WHITE;
    int background = COLOR_BLACK;

    const int COLORS[] = {
        COLOR_RED,
        COLOR_BLACK,
        COLOR_GREEN,
        COLOR_YELLOW,
        COLOR_BLUE,
        COLOR_MAGENTA,
        COLOR_CYAN,
        COLOR_LIGHT_RED,
        COLOR_LIGHT_GREEN,
        COLOR_LIGHT_YELLOW,
        COLOR_LIGHT_BLUE,
        COLOR_LIGHT_MAGENTA,
        COLOR_LIGHT_CYAN,
        COLOR_WHITE
    };

    const int NCOLORS = sizeof(COLORS) / sizeof(COLORS[0]);

    cgt_gotoxy(0, 1);
    cgt_print_str("前景：", 0, 2);
    for (int i = 0; i < NCOLORS; i++) {
        int color = COLORS[i];
        cgt_print_str("  ", 8 + i * 2, 2, COLOR_BLACK, color);
    }

    cgt_print_str("背景：", 0, 3);
    for (int i = 0; i < NCOLORS; i++) {
        int color = COLORS[i];
        cgt_print_str("  ", 8 + i * 2, 3, COLOR_WHITE, color);
    }

    cgt_gotoxy(0, 4);

    while (true) {
        // 先看看用户是不是点击了退出，或者尝试更改颜色。
        if (cgt_has_mouse()) {
            int x, y, button, event;
            cgt_get_mouse(x, y, button, event);

            // 检查是否点击了退出区域
            bool isClick = event == MOUSE_CLICK;
            bool inExit = x >= 0 && x < 4 && y == 0;
            if (isClick && inExit) {
                break;
            }

            // 检查是否点击了前景色区域
            bool inForeground = y == 2 && x >= 8 && x < 8 + NCOLORS * 2;
            if (isClick && inForeground) {
                int colorIndex = (x - 8) / 2;
                foreground = COLORS[colorIndex];
            }

            // 检查是否点击了背景色区域
            bool inBackground = y == 3 && x >= 8 && x < 8 + NCOLORS * 2;
            if (isClick && inBackground) {
                int colorIndex = (x - 8) / 2;
                background = COLORS[colorIndex];
            }

            cgt_set_color(foreground, background);
        }

        // 处理一下键盘输入。
        if (cgt_has_key()) {
            char ch;
            cgt_get_key(ch);
            cgt_print_char(ch, -1, -1, foreground, background);
        }

        // 防止 while 循环吃满 CPU。
        cgt_msleep(10);
    }
}


int main() {
    // 程序开始前，初始化 cgt。
    cgt_init();

    // 清空屏幕
    cgt_clear_screen();

    // 做各项测试

    if (1)  // 设为 1 以启用测试；设为 0 以跳过测试。
        test_print_str();

    if (1)
        test_print_value();

    if (1)
        test_clearscreen_colors();

    if (1)
        test_color_block();

    if (1)
        test_sjtu();

    if (1)
        test_mouse();

    if (1)
        test_keyboard();

    cgt_clear_screen();
    wait_for_enter("CGT 测试结束。按下任意键退出。", 0, 0);

    // 程序结束前记得清理 cgt。
    cgt_close();
    return 0;
}
