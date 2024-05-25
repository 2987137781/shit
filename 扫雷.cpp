// 扫雷.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include<graphics.h>//调用easyx的函数和图像
#include <vector>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
using namespace std;

//define xx xx
/* 行 列 地雷 每个格子的像素 */
constexpr int ROW = 10;
constexpr int COL = 10;
int MINE = 10;
constexpr int PIC_SIZE = 40;
int flag = 0;//控制游戏开始
int flag_flag = 0;
int uncoveredCount = 0;
#define PhotoSize 12
IMAGE img[PhotoSize];//放图图的数组
IMAGE cg_buffer;//动画图片缓冲器，播放动画的时候要用
IMAGE CG_CHOOSE;//胜利或者失败的时候对应的选项卡缓冲器，用来存储胜利或者失败的选项卡图片。
//二维向量
vector<vector<int>>map(ROW + 2, vector<int>(COL + 2, 0));//索引从1开始到ROW 简化边界判断条件
void cartion(int a);
int list(void);
void Judge(int a);
/*画（更新）实际的地图状态*/
void DrawGameMap(void) {
    uncoveredCount = 0;
    for (int i = 1; i <= ROW; i++) {
        for (int j = 1; j <= COL; j++) {
            //putimage坐标从0开始 横j-1 纵i-1 
            if (map[i][j] == -1)
            {
                putimage((j - 1) * PIC_SIZE, (i - 1) * PIC_SIZE, &img[9]);//雷
            }
            else if (map[i][j] >= 0 && map[i][j] <= 8)
            {
                putimage((j - 1) * PIC_SIZE, (i - 1) * PIC_SIZE, &img[map[i][j]]);//0-8的数字
                uncoveredCount++;
            }
            //未点击时空白
            else if (map[i][j] >= 19 && map[i][j] <= 28)
            {
                putimage((j - 1) * PIC_SIZE, (i - 1) * PIC_SIZE, &img[10]);
            }
            //右键标记红旗图片
            else if (map[i][j] > 30)
            {
                putimage((j - 1) * PIC_SIZE, (i - 1) * PIC_SIZE, &img[11]);
            }
        }
    }
}

/*游戏初始化的*/
void GameInit() {
    flag = 0;//游戏开始的标志 
    flag_flag = 0;
    int a, b;
    initgraph(ROW * PIC_SIZE, COL * PIC_SIZE, NOCLOSE | SHOWCONSOLE);//画400*400界面，左上角原点（抽象）
    //初始化地图
    for (int i = 1; i <= ROW; i++) {
        for (int j = 1; j <= COL; j++) {
            map[i][j] = 0;//没有地雷
        }
    }
    //埋地雷
    for (int i = 0; i < MINE;) {
        //随机位置 1-10
        a = rand() % ROW + 1;
        b = rand() % COL + 1;
        if (map[a][b] == 0) {
            map[a][b] = -1;
            i++;
        }
    }
    ////计算每个格子旁边的地雷数
    for (int i = 1; i <= ROW; i++) {
        for (int j = 1; j <= COL; j++) {
            //找到地雷 旁边8个非地雷格子加一
            if (map[i][j] == -1) {
                for (int m = i - 1; m <= i + 1; m++) {
                    for (int n = j - 1; n <= j + 1; n++) {
                        if (map[m][n] != -1) {
                            map[m][n]++;
                        }
                    }
                }
            }
        }
    }
    //用"盖子"把数字和地雷盖上
    for (int i = 1; i <= ROW; i++) {
        for (int j = 1; j <= COL; j++) {
            map[i][j] += 20;
        }
    }
    //把图像放到地图界面中
    char temp[20] = { 0 };
    for (int i = 0; i < 12; i++) {
        sprintf_s(temp, sizeof(temp), "./image/%d.jpg", i);//把索引写到缓冲字符串temp
        loadimage(&img[i], temp, PIC_SIZE, PIC_SIZE);
    }
    DrawGameMap();
}

void open(int i, int o) {//打开之前盖上的“盖子”
    if (map[i][o] == 0) {
        for (int n = i - 1; n <= i + 1; n++) {
            for (int m = o - 1; m <= o + 1; m++) {
                if (map[n][m] != 19 && map[n][m] > 8) {
                    map[n][m] -= 20;
                    flag++;
                    open(n, m);//递归打开周围的格子
                    uncoveredCount++;
                }
            }
        }
    }
}

int Mouse(MOUSEMSG msg) {//根据鼠标操作来更新地图

    int i = msg.y / PIC_SIZE + 1;
    int o = msg.x / PIC_SIZE + 1;
    switch (msg.uMsg) {
    case WM_LBUTTONDOWN:
        if (map[i][o] > 8 && map[i][o] < 29) {
            map[i][o] -= 20;
            flag++;
            open(i, o);
        }
        break;
    case WM_RBUTTONDOWN:
        if (map[i][o] > 8 && map[i][o] < 29) {
            map[i][o] += 20;
            flag_flag++;
        }
        else if (map[i][o] > 30) {
            map[i][o] -= 20;
            flag_flag--;
        }
        break;
    }
    return map[i][o];

}


void Game() {
    GameInit();
    while (true) {
        MOUSEMSG msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN|| msg.uMsg == WM_RBUTTONDOWN)//检测到鼠标操作了再检查。
        {
            Judge(Mouse(msg));
        }
        /*     Judge();*/
    }
}

void Judge(int a) {//判断游戏是否结束
    DrawGameMap();
    if (a == -1) {//如果打开了雷，游戏结束
        Sleep(500);//让玩家看到自己雀氏踩到雷了
        closegraph();
        initgraph(700, 488, EX_SHOWCONSOLE);//为动画创建新窗口
        cartion(a);
    }
    else if (uncoveredCount == ROW * COL - MINE && flag_flag == MINE) {//除了雷以外的格子全部打开并且所有雷都得被标出来后，结束游戏
        Sleep(500);
        closegraph();
        initgraph(700, 474, EX_SHOWCONSOLE);
        cartion(a);
    }
}

void cartion(int a)//播放失败或者成功的动画并且处理再玩一次的需求参数a=-1的时候表示踩到雷了，等于别的表示胜利了
{
    if (a == -1)//失败
    {
        loadimage(&CG_CHOOSE, "./image_1/05.png", 700, 94);//失败了的选项卡
        char path[25] = "./image_1/IMG00";
        for (int i = 37; i < 64; i++)
        {
            sprintf_s(path, sizeof(path), "./image_1/IMG00%03d.bmp", i);
            loadimage(&cg_buffer, path, 700, 394);//cg_buffer用来装载cg图片，easyx只能放图片，所以放动画只能像这样一张一张放
            putimage(0, 0, &cg_buffer);
            Sleep(1000 / 24);//沉睡函数，保证一秒24帧的动画
            if (i == 63)
            {
                putimage(0, 394, &CG_CHOOSE);//最后一张图片了，要在下面显示选项卡
                while (1)
                {
                    MOUSEMSG msg = GetMouseMsg();
                    if (msg.uMsg == WM_LBUTTONDOWN )//检测到鼠标操作了再检查。
                    {
                        if ((msg.x >= 18) && (msg.x <= 218) && (msg.y > 394))//检测到鼠标右键且是点到对应的位置了才能again
                        {
                          
                                closegraph();
                                list();//again是从菜单界面开始
                         

                        }
                        if ((msg.x >= 464) && (msg.x <= 687) && (msg.y > 394))//芝士不玩了的选项
                                exit(1);
                    }
                }
            }
        }
    }
    else//成了，总体逻辑和失败一样，变的不过是放出来的图片和选项卡
    {
        char path[25] = "./image/IMG00";
        loadimage(&CG_CHOOSE, "./image_1/04.png", 700, 80);//成功的选项卡

        for (int i = 0; i < 200; i++)
        {

            sprintf_s(path, sizeof(path), "./image/IMG00%03d.bmp", i);
            loadimage(&cg_buffer, path, 700, 394);
            putimage(0, 0, &cg_buffer);
            Sleep(1000 / 24);
            if (i == 199)
            {
                putimage(0, 394, &CG_CHOOSE);

                while (1)
                {
                    MOUSEMSG msg = GetMouseMsg();
                    if (msg.uMsg == WM_LBUTTONDOWN )//检测到鼠标操作了再检查。
                    {
                        if ((msg.x >= 14) && (msg.x <= 344) && (msg.y > 394))
                        {
                                closegraph();
                                list();
                        }
                        if ((msg.x >= 465) && (msg.x <= 683) && (msg.y > 394))
                                exit(1);
                    }
                }
            }
        }
    }
}

int list(void)
{
    initgraph(811, 592, EX_SHOWCONSOLE);
    loadimage(&CG_CHOOSE, "./image_1/caidan.png", 811, 592);
    putimage(0, 0, &CG_CHOOSE);//放置菜单
    while (1)//检测鼠标
    {
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();

            if (msg.uMsg == WM_RBUTTONDOWN)
                continue;
            if (msg.uMsg == WM_LBUTTONDOWN)
            {


                if ((msg.x >= 15) && (msg.x <= 167) && (msg.y > 215) && (msg.y < 287))
                {
                    exit(1);
                }
                if ((msg.x >= 641) && (msg.x <= 794))
                {
                    if ((msg.y > 123) && (msg.y < 194))//检测到右键了简单选项
                    {
                        MINE = 10;
                    }
                    else if ((msg.y > 215) && (msg.y < 287))//检测到右键了有一点难选项
                    {
                        MINE = 20;
                    }
                    else if ((msg.y > 308) && (msg.y < 378))//检测到右键了难死了的选项
                    {
                        MINE = 25;
                    }
                    Game();//设置好难度开始游戏
                }
            }
        }
    }
}

int main()
{
    srand((unsigned)time(NULL));//设置随机种子
    list();
    closegraph();//关闭图像界面
}