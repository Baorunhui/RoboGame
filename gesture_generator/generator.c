#include <stdio.h>


//输出无需修改的头部信息
void head()
{
    FILE *fi, *fo;
    int c;
    fi = fopen("head.txt", "r");
    fo = fopen("out2.mc", "w");
    while(! feof(fi))
    {
        c=fgetc(fi);
        fputc(c,fo);
    }
    fclose(fi);
    fclose(fo);
}

//输出当前状态所有参数
void print_status(FILE *fo, int status[][2])
{
    for(int i=0; i<16; i++)
    {
        fprintf(fo, "Angle%d = %d\nSpeed%d = %d\nbUse%d = True\n", i, status[i][0], i, status[i][1], i);
    }
}

//输出所有状态
int status_all(int status_count)
{

    FILE *fo;
    fo = fopen("out.mc", "a");

    //状态初始化
    int origin_status[16][2] ={
    90,19,
    120,19,
    90,19,
    125,19,
    85,19,
    140,19,
    120,19,
    125,19,
    70,19,
    145,19,
    80,19,
    160,19,
    90,19,
    90,19,
    90,19,
    90,19};

    int status[16][2];
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<2; j++)
        {
            status[i][j] = origin_status[i][j];
        }
    }

    fprintf(fo, "StatusNumber = %d\n", status_count);

    //输出初始状态
    fprintf(fo, "StatusName = initial\n");
    print_status(fo ,status);

//修改开始：

//变车
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<2; j++)
        {
            status[i][j] = origin_status[i][j];
        }
    }
    fprintf(fo, "StatusName = to_car\n");
    //头部
    status[1][0] -=50;
    status[7][0] -=50;
    status[2][0] -=60;
    status[8][0] +=60;
    //中部
    status[3][0] -=125;
    status[9][0] -=125;
    status[4][0] -=30;
    status[10][0] +=30;
    //后部
    status[5][0] -=110;
    status[11][0] -=110;
    status[6][0] +=60;
    status[12][0] -=60;
    print_status(fo ,status);

//变箱子
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<2; j++)
        {
            status[i][j] = origin_status[i][j];
        }
    }
    fprintf(fo, "StatusName = to_box_0\n");
    print_status(fo ,status);

    fprintf(fo, "StatusName = to_box_1\n");
    status[2][0] -=60;
    status[8][0] +=60;

    status[6][0] +=60;
    status[12][0] -=60;
    print_status(fo ,status);

    fprintf(fo, "StatusName = to_box_2\n");

    status[1][0] +=10;
    status[7][0] +=10;

    status[3][0] +=30;
    status[9][0] +=30;

    status[5][0] +=15;
    status[11][0] +=15;

    print_status(fo ,status);

//前进

    for(int i=0; i<16; i++)
    {
        for(int j=0; j<2; j++)
        {
            status[i][j] = origin_status[i][j];
        }
    }

   //前进开始
    fprintf(fo, "StatusName = triwalk_ahead_begin\n");
    status[2][0] -=15;
    status[4][0] +=15;
    status[6][0] -=15;
    status[8][0] -=15;
    status[10][0] +=15;
    status[12][0] -=15;
    print_status(fo ,status);

    //右侧抬腿
    fprintf(fo, "StatusName = triwalk_ahead_1_0\n");
    status[3][0] -=30;
    status[7][0] -=30;
    status[11][0] -=30;
    print_status(fo ,status);

    //移动
    fprintf(fo, "StatusName = triwalk_ahead_1_1\n");
    status[2][0] +=30;
    status[4][0] -=30;
    status[6][0] +=30;
    status[8][0] +=30;
    status[10][0] -=30;
    status[12][0] +=30;
    print_status(fo ,status);

    //右侧落腿
    fprintf(fo, "StatusName = triwalk_ahead_1_2\n");
    status[3][0] +=30;
    status[7][0] +=30;
    status[11][0] +=30;
    print_status(fo ,status);

    //左侧抬腿
    fprintf(fo, "StatusName = triwalk_ahead_2_0\n");
    status[1][0] -=30;
    status[5][0] -=30;
    status[9][0] -=30;
    print_status(fo ,status);

    //移动
    fprintf(fo, "StatusName = triwalk_ahead_2_1\n");
    status[2][0] -=30;
    status[4][0] +=30;
    status[6][0] -=30;
    status[8][0] -=30;
    status[10][0] +=30;
    status[12][0] -=30;
    print_status(fo ,status);

    //左侧落腿
    fprintf(fo, "StatusName = triwalk_ahead_2_2\n");
    status[1][0] +=30;
    status[5][0] +=30;
    status[9][0] +=30;
    print_status(fo ,status);

//前进结束

//倒退

    for(int i=0; i<16; i++)
    {
        for(int j=0; j<2; j++)
        {
            status[i][j] = origin_status[i][j];
        }
    }
    //倒退开始
    fprintf(fo, "StatusName = triwalk_back_begin\n");
    status[2][0] +=15;
    status[4][0] -=15;
    status[6][0] +=15;
    status[8][0] +=15;
    status[10][0] -=15;
    status[12][0] +=15;
    print_status(fo ,status);

    //右侧抬腿
    fprintf(fo, "StatusName = triwalk_back_1_0\n");
    status[3][0] -=30;
    status[7][0] -=30;
    status[11][0] -=30;
    print_status(fo ,status);

    //移动
    fprintf(fo, "StatusName = triwalk_back_1_1\n");
    status[2][0] -=30;
    status[4][0] +=30;
    status[6][0] -=30;
    status[8][0] -=30;
    status[10][0] +=30;
    status[12][0] -=30;
    print_status(fo ,status);

    //右侧落腿
    fprintf(fo, "StatusName = triwalk_back_1_2\n");
    status[3][0] +=30;
    status[7][0] +=30;
    status[11][0] +=30;
    print_status(fo ,status);

    //左侧抬腿
    fprintf(fo, "StatusName = triwalk_back_2_0\n");
    status[1][0] -=30;
    status[5][0] -=30;
    status[9][0] -=30;
    print_status(fo ,status);

    //移动
    fprintf(fo, "StatusName = triwalk_back_2_1\n");
    status[2][0] +=30;
    status[4][0] -=30;
    status[6][0] +=30;
    status[8][0] +=30;
    status[10][0] -=30;
    status[12][0] +=30;
    print_status(fo ,status);

    //左侧落腿
    fprintf(fo, "StatusName = triwalk_back_2_2\n");
    status[1][0] +=30;
    status[5][0] +=30;
    status[9][0] +=30;
    print_status(fo ,status);

//倒退结束

//左转

    for(int i=0; i<16; i++)
    {
        for(int j=0; j<2; j++)
        {
            status[i][j] = origin_status[i][j];
        }
    }

   //左转开始
    fprintf(fo, "StatusName = triwalk_left_begin\n");
    status[2][0] +=15;
    status[4][0] -=15;
    status[6][0] +=15;
    status[8][0] -=15;
    status[10][0] +=15;
    status[12][0] -=15;
    print_status(fo ,status);

    //右侧抬腿
    fprintf(fo, "StatusName = triwalk_left_1_0\n");
    status[3][0] -=30;
    status[7][0] -=30;
    status[11][0] -=30;
    print_status(fo ,status);

    //移动
    fprintf(fo, "StatusName = triwalk_left_1_1\n");
    status[2][0] -=30;
    status[4][0] +=30;
    status[6][0] -=30;
    status[8][0] +=30;
    status[10][0] -=30;
    status[12][0] +=30;
    print_status(fo ,status);

    //右侧落腿
    fprintf(fo, "StatusName = triwalk_left_1_2\n");
    status[3][0] +=30;
    status[7][0] +=30;
    status[11][0] +=30;
    print_status(fo ,status);

    //左侧抬腿
    fprintf(fo, "StatusName = triwalk_left_2_0\n");
    status[1][0] -=30;
    status[5][0] -=30;
    status[9][0] -=30;
    print_status(fo ,status);

    //移动
    fprintf(fo, "StatusName = triwalk_left_2_1\n");
    status[2][0] +=30;
    status[4][0] -=30;
    status[6][0] +=30;
    status[8][0] -=30;
    status[10][0] +=30;
    status[12][0] -=30;
    print_status(fo ,status);

    //左侧落腿
    fprintf(fo, "StatusName = triwalk_left_2_2\n");
    status[1][0] +=30;
    status[5][0] +=30;
    status[9][0] +=30;
    print_status(fo ,status);

//左转结束


//右转

    for(int i=0; i<16; i++)
    {
        for(int j=0; j<2; j++)
        {
            status[i][j] = origin_status[i][j];
        }
    }

   //右转开始
    fprintf(fo, "StatusName = triwalk_right_begin\n");
    status[2][0] -=15;
    status[4][0] +=15;
    status[6][0] -=15;
    status[8][0] +=15;
    status[10][0] -=15;
    status[12][0] +=15;
    print_status(fo ,status);

    //右侧抬腿
    fprintf(fo, "StatusName = triwalk_right_1_0\n");
    status[3][0] -=30;
    status[7][0] -=30;
    status[11][0] -=30;
    print_status(fo ,status);

    //移动
    fprintf(fo, "StatusName = triwalk_right_1_1\n");
    status[2][0] +=30;
    status[4][0] -=30;
    status[6][0] +=30;
    status[8][0] -=30;
    status[10][0] +=30;
    status[12][0] -=30;
    print_status(fo ,status);

    //右侧落腿
    fprintf(fo, "StatusName = triwalk_right_1_2\n");
    status[3][0] +=30;
    status[7][0] +=30;
    status[11][0] +=30;
    print_status(fo ,status);

    //左侧抬腿
    fprintf(fo, "StatusName = triwalk_right_2_0\n");
    status[1][0] -=30;
    status[5][0] -=30;
    status[9][0] -=30;
    print_status(fo ,status);

    //移动
    fprintf(fo, "StatusName = triwalk_right_2_1\n");
    status[2][0] -=30;
    status[4][0] +=30;
    status[6][0] -=30;
    status[8][0] +=30;
    status[10][0] -=30;
    status[12][0] +=30;
    print_status(fo ,status);

    //左侧落腿
    fprintf(fo, "StatusName = triwalk_right_2_2\n");
    status[1][0] +=30;
    status[5][0] +=30;
    status[9][0] +=30;
    print_status(fo ,status);

//右转结束

//前进（wave）

    for(int i=0; i<16; i++)
    {
        for(int j=0; j<2; j++)
        {
            status[i][j] = origin_status[i][j];
        }
    }

    fprintf(fo, "StatusName = wavewalk_ahead_begin\n");
    print_status(fo ,status);

    //1
    fprintf(fo, "StatusName = wavewalk_ahead_1_0\n");
    status[2][0] -=25;
    status[1][0] -=30;
    print_status(fo ,status);

    fprintf(fo, "StatusName = wavewalk_ahead_1_1\n");
    status[1][0] +=30;
    //status[2][0] +=5;
    status[4][0] +=5;
    status[6][0] +=5;
    status[8][0] -=5;
    status[10][0] -=5;
    status[12][0] -=5;
    print_status(fo ,status);

    //2
    fprintf(fo, "StatusName = wavewalk_ahead_2_0\n");
    status[4][0] -=25;
    status[3][0] -=30;
    print_status(fo ,status);

    fprintf(fo, "StatusName = wavewalk_ahead_2_1\n");
    status[3][0] +=30;
    status[2][0] +=5;
    //status[4][0] +=5;
    status[6][0] +=5;
    status[8][0] -=5;
    status[10][0] -=5;
    status[12][0] -=5;
    print_status(fo ,status);

    //3
    fprintf(fo, "StatusName = wavewalk_ahead_3_0\n");
    status[6][0] -=25;
    status[5][0] -=30;
    print_status(fo ,status);

    fprintf(fo, "StatusName = wavewalk_ahead_3_1\n");
    status[5][0] +=30;
    status[2][0] +=5;
    status[4][0] +=5;
    //status[6][0] +=5;
    status[8][0] -=5;
    status[10][0] -=5;
    status[12][0] -=5;
    print_status(fo ,status);

    //4
    fprintf(fo, "StatusName = wavewalk_ahead_4_0\n");
    status[8][0] +=25;
    status[7][0] -=30;
    print_status(fo ,status);

    fprintf(fo, "StatusName = wavewalk_ahead_4_1\n");
    status[7][0] +=30;
    status[2][0] +=5;
    status[4][0] +=5;
    status[6][0] +=5;
    //status[8][0] -=5;
    status[10][0] -=5;
    status[12][0] -=5;
    print_status(fo ,status);

    //5
    fprintf(fo, "StatusName = wavewalk_ahead_5_0\n");
    status[10][0] +=25;
    status[9][0] -=30;
    print_status(fo ,status);

    fprintf(fo, "StatusName = wavewalk_ahead_5_1\n");
    status[9][0] +=30;
    status[2][0] +=5;
    status[4][0] +=5;
    status[6][0] +=5;
    status[8][0] -=5;
    //status[10][0] -=5;
    status[12][0] -=5;
    print_status(fo ,status);

    //6
    fprintf(fo, "StatusName = wavewalk_ahead_6_0\n");
    status[12][0] +=25;
    status[11][0] -=30;
    print_status(fo ,status);

    fprintf(fo, "StatusName = wavewalk_ahead_6_1\n");
    status[11][0] +=30;
    status[2][0] +=5;
    status[4][0] +=5;
    status[6][0] +=5;
    status[8][0] -=5;
    status[10][0] -=5;
    //status[12][0] -=5;
    print_status(fo ,status);

//前进结束

//后退（wave）

    for(int i=0; i<16; i++)
    {
        for(int j=0; j<2; j++)
        {
            status[i][j] = origin_status[i][j];
        }
    }

    fprintf(fo, "StatusName = wavewalk_back_begin\n");
    print_status(fo ,status);

    //1
    fprintf(fo, "StatusName = wavewalk_back_1_0\n");
    status[2][0] +=25;
    status[1][0] -=30;
    print_status(fo ,status);

    fprintf(fo, "StatusName = wavewalk_back_1_1\n");
    status[1][0] +=30;
    //status[2][0] -=5;
    status[4][0] -=5;
    status[6][0] -=5;
    status[8][0] +=5;
    status[10][0] +=5;
    status[12][0] +=5;
    print_status(fo ,status);

    //2
    fprintf(fo, "StatusName = wavewalk_back_2_0\n");
    status[4][0] +=25;
    status[3][0] -=30;
    print_status(fo ,status);

    fprintf(fo, "StatusName = wavewalk_back_2_1\n");
    status[3][0] +=30;
    status[2][0] -=5;
    //status[4][0] -=5;
    status[6][0] -=5;
    status[8][0] +=5;
    status[10][0] +=5;
    status[12][0] +=5;
    print_status(fo ,status);

    //3
    fprintf(fo, "StatusName = wavewalk_back_3_0\n");
    status[6][0] +=25;
    status[5][0] -=30;
    print_status(fo ,status);

    fprintf(fo, "StatusName = wavewalk_back_3_1\n");
    status[5][0] +=30;
    status[2][0] -=5;
    status[4][0] -=5;
    //status[6][0] -=5;
    status[8][0] +=5;
    status[10][0] +=5;
    status[12][0] +=5;
    print_status(fo ,status);

    //4
    fprintf(fo, "StatusName = wavewalk_back_4_0\n");
    status[8][0] -=25;
    status[7][0] -=30;
    print_status(fo ,status);

    fprintf(fo, "StatusName = wavewalk_back_4_1\n");
    status[7][0] +=30;
    status[2][0] -=5;
    status[4][0] -=5;
    status[6][0] -=5;
    //status[8][0] +=5;
    status[10][0] +=5;
    status[12][0] +=5;
    print_status(fo ,status);

    //5
    fprintf(fo, "StatusName = wavewalk_back_5_0\n");
    status[10][0] -=25;
    status[9][0] -=30;
    print_status(fo ,status);

    fprintf(fo, "StatusName = wavewalk_back_5_1\n");
    status[9][0] +=30;
    status[2][0] -=5;
    status[4][0] -=5;
    status[6][0] -=5;
    status[8][0] +=5;
    //status[10][0] +=5;
    status[12][0] +=5;
    print_status(fo ,status);

    //6
    fprintf(fo, "StatusName = wavewalk_back_6_0\n");
    status[12][0] -=25;
    status[11][0] -=30;
    print_status(fo ,status);

    fprintf(fo, "StatusName = wavewalk_back_6_1\n");
    status[11][0] +=30;
    status[2][0] -=5;
    status[4][0] -=5;
    status[6][0] -=5;
    status[8][0] +=5;
    status[10][0] +=5;
    //status[12][0] +=5;
    print_status(fo ,status);

//后退结束

//右行（wave）

    for(int i=0; i<16; i++)
    {
        for(int j=0; j<2; j++)
        {
            status[i][j] = origin_status[i][j];
        }
    }

    //准备
    fprintf(fo, "StatusName = wavewalk_right_begin\n");
    status[2][0] -=40;
    status[6][0] +=40;
    status[8][0] +=40;
    status[12][0] -=40;
    //status[3][0] -=40;
    //status[9][0] -=40;
    print_status(fo ,status);

    //抬腿
    fprintf(fo, "StatusName = wavewalk_right_1_0\n");
    status[1][0] -=30;
    status[11][0] -=30;
    status[2][0] -=30;
    status[12][0] +=30;
    print_status(fo ,status);

    //落腿
    fprintf(fo, "StatusName = wavewalk_right_1_1\n");
    status[1][0] +=30;
    status[11][0] +=30;
    print_status(fo ,status);

    //拨腿
    fprintf(fo, "StatusName = wavewalk_right_1_2\n");
    status[2][0] +=15;
    status[6][0] -=15;
    status[8][0] +=15;
    status[12][0] -=15;
    print_status(fo ,status);

    //抬腿
    fprintf(fo, "StatusName = wavewalk_right_2_0\n");
    status[5][0] -=30;
    status[7][0] -=30;
    status[6][0] +=30;
    status[8][0] -=30;
    print_status(fo ,status);

    //落腿
    fprintf(fo, "StatusName = wavewalk_right_2_1\n");
    status[5][0] +=30;
    status[7][0] +=30;
    print_status(fo ,status);

    //拨腿
    fprintf(fo, "StatusName = wavewalk_right_2_2\n");
    status[2][0] +=15;
    status[6][0] -=15;
    status[8][0] +=15;
    status[12][0] -=15;
    print_status(fo ,status);

//右行结束

//左行（wave）

    for(int i=0; i<16; i++)
    {
        for(int j=0; j<2; j++)
        {
            status[i][j] = origin_status[i][j];
        }
    }

    //准备
    fprintf(fo, "StatusName = wavewalk_left_begin\n");
    status[2][0] -=40;
    status[6][0] +=40;
    status[8][0] +=40;
    status[12][0] -=40;
    //status[3][0] -=40;
    //status[9][0] -=40;
    print_status(fo ,status);

    //抬腿
    fprintf(fo, "StatusName = wavewalk_left_1_0\n");
    status[1][0] -=30;
    status[11][0] -=30;
    status[2][0] +=30;
    status[12][0] -=30;
    print_status(fo ,status);

    //落腿
    fprintf(fo, "StatusName = wavewalk_left_1_1\n");
    status[1][0] +=30;
    status[11][0] +=30;
    print_status(fo ,status);

    //拨腿
    fprintf(fo, "StatusName = wavewalk_left_1_2\n");
    status[2][0] -=15;
    status[6][0] +=15;
    status[8][0] -=15;
    status[12][0] +=15;
    print_status(fo ,status);

    //抬腿
    fprintf(fo, "StatusName = wavewalk_left_2_0\n");
    status[5][0] -=30;
    status[7][0] -=30;
    status[6][0] -=30;
    status[8][0] +=30;
    print_status(fo ,status);

    //落腿
    fprintf(fo, "StatusName = wavewalk_left_2_1\n");
    status[5][0] +=30;
    status[7][0] +=30;
    print_status(fo ,status);

    //拨腿
    fprintf(fo, "StatusName = wavewalk_left_2_2\n");
    status[2][0] -=15;
    status[6][0] +=15;
    status[8][0] -=15;
    status[12][0] +=15;
    print_status(fo ,status);

//右行结束

//展示动作(up down)

    for(int i=0; i<16; i++)
    {
        for(int j=0; j<2; j++)
        {
            status[i][j] = origin_status[i][j];
        }
    }
    //准备
    fprintf(fo, "StatusName = up_down_begin\n");
    print_status(fo ,status);

    //down
    fprintf(fo, "StatusName = down\n");
    status[1][0] -=20;
    status[3][0] -=20;
    status[5][0] -=20;
    status[7][0] -=20;
    status[9][0] -=20;
    status[11][0] -=20;
    print_status(fo ,status);

    //up
    fprintf(fo, "StatusName = up\n");
    status[1][0] +=20;
    status[3][0] +=20;
    status[5][0] +=20;
    status[7][0] +=20;
    status[9][0] +=20;
    status[11][0] +=20;
    print_status(fo ,status);

    //split down
    fprintf(fo, "StatusName = split_down\n");
    status[1][0] -=20;
    status[3][0] -=20;
    status[5][0] -=20;
    status[7][0] -=20;
    status[9][0] -=20;
    status[11][0] -=20;

    status[2][0] -=20;
    status[4][0] +=0;
    status[6][0] +=20;
    status[8][0] +=20;
    status[10][0] +=0;
    status[12][0] -=20;
    print_status(fo ,status);

    //split up
    fprintf(fo, "StatusName = split_up\n");
    status[1][0] +=20;
    status[3][0] +=20;
    status[5][0] +=20;
    status[7][0] +=20;
    status[9][0] +=20;
    status[11][0] +=20;

    print_status(fo ,status);
//展示（up down）结束


//展示（wave）

    for(int i=0; i<16; i++)
    {
            status[i][0] = origin_status[i][0];
            status[i][1] = 10;
    }

    //准备 摆平
    fprintf(fo, "StatusName = wave_begin\n");
    status[1][0] -=60;
    status[3][0] -=60;
    status[5][0] -=60;
    status[7][0] -=60;
    status[9][0] -=60;
    status[11][0] -=60;
    print_status(fo ,status);

    //singlewave
    fprintf(fo, "StatusName = single_wave_1\n");
    status[1][0] -=30;
    print_status(fo ,status);

    fprintf(fo, "StatusName = single_wave_2\n");
    status[1][0] +=30;
    status[3][0] -=30;
    print_status(fo ,status);

    fprintf(fo, "StatusName = single_wave_3\n");
    status[1][0] +=20;
    status[3][0] +=30;
    status[5][0] -=30;
    print_status(fo ,status);

    fprintf(fo, "StatusName = single_wave_4\n");
    status[3][0] +=20;
    status[5][0] +=30;
    status[7][0] -=30;
    print_status(fo ,status);

    fprintf(fo, "StatusName = single_wave_5\n");
    status[5][0] +=20;
    status[7][0] +=30;
    status[9][0] -=30;
    print_status(fo ,status);

    fprintf(fo, "StatusName = single_wave_6\n");
    status[7][0] +=20;
    status[9][0] +=30;
    status[11][0] -=30;
    print_status(fo ,status);

    fprintf(fo, "StatusName = single_wave_7\n");
    status[9][0] +=20;
    status[11][0] +=30;
    print_status(fo ,status);

    fprintf(fo, "StatusName = single_wave_8\n");
    status[11][0] +=20;
    print_status(fo ,status);


    //double_wave
    fprintf(fo, "StatusName = double_wave_1\n");
    status[1][0] -=30;
    status[7][0] -=30;
    print_status(fo ,status);

    fprintf(fo, "StatusName = double_wave_2\n");
    status[1][0] +=30;
    status[7][0] +=30;
    status[3][0] -=30;
    status[9][0] -=30;
    print_status(fo ,status);

    fprintf(fo, "StatusName = double_wave_3\n");
    status[1][0] +=20;
    status[7][0] +=20;
    status[3][0] +=30;
    status[9][0] +=30;
    status[5][0] -=30;
    status[11][0] -=30;
    print_status(fo ,status);

    fprintf(fo, "StatusName = double_wave_4\n");
    status[3][0] +=20;
    status[9][0] +=20;
    status[5][0] +=30;
    status[11][0] +=30;
    print_status(fo ,status);

    fprintf(fo, "StatusName = double_wave_5\n");
    status[5][0] +=20;
    status[11][0] +=20;
    print_status(fo ,status);

//wave结束


//修改结束

    fclose(fo);
    return 0;

}

int action_all()
{
    FILE *fo;
    fo = fopen("out.mc", "a");
    fprintf(fo, "ActionGroupNumber = 16\n");
    /*for(int i=0; i<16; i++)
    {
        fprintf(fo, "ActionGroupName = %d\nCycleCnt = 0\nActionNumber = 0\n", i);
    }*/

//停止      0
    fprintf(fo, "ActionGroupName = 0\nCycleCnt = 0\n");
    fprintf(fo, "ActionNumber = 1\n");
    fprintf(fo, "StatusName = initial\nTime = 1000\n");

//前进（tri）   1
    fprintf(fo, "ActionGroupName = 1\nCycleCnt = 50\n");
    fprintf(fo, "ActionNumber = 6\n");
    fprintf(fo, "StatusName = triwalk_ahead_1_0\nTime = 300\n");
    fprintf(fo, "StatusName = triwalk_ahead_1_1\nTime = 300\n");
    fprintf(fo, "StatusName = triwalk_ahead_1_2\nTime = 300\n");
    fprintf(fo, "StatusName = triwalk_ahead_2_0\nTime = 300\n");
    fprintf(fo, "StatusName = triwalk_ahead_2_1\nTime = 300\n");
    fprintf(fo, "StatusName = triwalk_ahead_2_2\nTime = 300\n");

//左转      2
    fprintf(fo, "ActionGroupName = 2\nCycleCnt = 50\n");
    fprintf(fo, "ActionNumber = 6\n");
    fprintf(fo, "StatusName = triwalk_left_1_0\nTime = 300\n");
    fprintf(fo, "StatusName = triwalk_left_1_1\nTime = 300\n");
    fprintf(fo, "StatusName = triwalk_left_1_2\nTime = 300\n");
    fprintf(fo, "StatusName = triwalk_left_2_0\nTime = 300\n");
    fprintf(fo, "StatusName = triwalk_left_2_1\nTime = 300\n");
    fprintf(fo, "StatusName = triwalk_left_2_2\nTime = 300\n");

//右转      3
    fprintf(fo, "ActionGroupName = 3\nCycleCnt = 50\n");
    fprintf(fo, "ActionNumber = 6\n");
    fprintf(fo, "StatusName = triwalk_right_1_0\nTime = 300\n");
    fprintf(fo, "StatusName = triwalk_right_1_1\nTime = 300\n");
    fprintf(fo, "StatusName = triwalk_right_1_2\nTime = 300\n");
    fprintf(fo, "StatusName = triwalk_right_2_0\nTime = 300\n");
    fprintf(fo, "StatusName = triwalk_right_2_1\nTime = 300\n");
    fprintf(fo, "StatusName = triwalk_right_2_2\nTime = 300\n");

//后退（tri)    4
    fprintf(fo, "ActionGroupName = 4\nCycleCnt = 50\n");
    fprintf(fo, "ActionNumber = 6\n");
    fprintf(fo, "StatusName = triwalk_back_1_0\nTime = 300\n");
    fprintf(fo, "StatusName = triwalk_back_1_1\nTime = 300\n");
    fprintf(fo, "StatusName = triwalk_back_1_2\nTime = 300\n");
    fprintf(fo, "StatusName = triwalk_back_2_0\nTime = 300\n");
    fprintf(fo, "StatusName = triwalk_back_2_1\nTime = 300\n");
    fprintf(fo, "StatusName = triwalk_back_2_2\nTime = 300\n");

//前进（wave）      5
    fprintf(fo, "ActionGroupName = 5\nCycleCnt = 50\n");
    fprintf(fo, "ActionNumber = 12\n");
    fprintf(fo, "StatusName = wavewalk_ahead_1_0\nTime = 200\n");
    fprintf(fo, "StatusName = wavewalk_ahead_1_1\nTime = 200\n");
    fprintf(fo, "StatusName = wavewalk_ahead_2_0\nTime = 200\n");
    fprintf(fo, "StatusName = wavewalk_ahead_2_1\nTime = 200\n");
    fprintf(fo, "StatusName = wavewalk_ahead_3_0\nTime = 200\n");
    fprintf(fo, "StatusName = wavewalk_ahead_3_1\nTime = 200\n");
    fprintf(fo, "StatusName = wavewalk_ahead_4_0\nTime = 200\n");
    fprintf(fo, "StatusName = wavewalk_ahead_4_1\nTime = 200\n");
    fprintf(fo, "StatusName = wavewalk_ahead_5_0\nTime = 200\n");
    fprintf(fo, "StatusName = wavewalk_ahead_5_1\nTime = 200\n");
    fprintf(fo, "StatusName = wavewalk_ahead_6_0\nTime = 200\n");
    fprintf(fo, "StatusName = wavewalk_ahead_6_1\nTime = 200\n");


//后退（wave）      6
    fprintf(fo, "ActionGroupName = 6\nCycleCnt = 50\n");
    fprintf(fo, "ActionNumber = 12\n");
    fprintf(fo, "StatusName = wavewalk_back_1_0\nTime = 200\n");
    fprintf(fo, "StatusName = wavewalk_back_1_1\nTime = 200\n");
    fprintf(fo, "StatusName = wavewalk_back_2_0\nTime = 200\n");
    fprintf(fo, "StatusName = wavewalk_back_2_1\nTime = 200\n");
    fprintf(fo, "StatusName = wavewalk_back_3_0\nTime = 200\n");
    fprintf(fo, "StatusName = wavewalk_back_3_1\nTime = 200\n");
    fprintf(fo, "StatusName = wavewalk_back_4_0\nTime = 200\n");
    fprintf(fo, "StatusName = wavewalk_back_4_1\nTime = 200\n");
    fprintf(fo, "StatusName = wavewalk_back_5_0\nTime = 200\n");
    fprintf(fo, "StatusName = wavewalk_back_5_1\nTime = 200\n");
    fprintf(fo, "StatusName = wavewalk_back_6_0\nTime = 200\n");
    fprintf(fo, "StatusName = wavewalk_back_6_1\nTime = 200\n");

//变车  7
    fprintf(fo, "ActionGroupName = 7\nCycleCnt = 0\n");
    fprintf(fo, "ActionNumber = 1\n");
    fprintf(fo, "StatusName = to_car\nTime = 1000\n");

//左移（wave）  8
    fprintf(fo, "ActionGroupName = 8\nCycleCnt = 50\n");
    fprintf(fo, "ActionNumber = 6\n");
    fprintf(fo, "StatusName = wavewalk_left_1_0\nTime = 300\n");
    fprintf(fo, "StatusName = wavewalk_left_1_1\nTime = 300\n");
    fprintf(fo, "StatusName = wavewalk_left_1_2\nTime = 300\n");
    fprintf(fo, "StatusName = wavewalk_left_2_0\nTime = 300\n");
    fprintf(fo, "StatusName = wavewalk_left_2_1\nTime = 300\n");
    fprintf(fo, "StatusName = wavewalk_left_2_2\nTime = 300\n");

//右移（wave）  9
    fprintf(fo, "ActionGroupName = 9\nCycleCnt = 50\n");
    fprintf(fo, "ActionNumber = 6\n");
    fprintf(fo, "StatusName = wavewalk_right_1_0\nTime = 300\n");
    fprintf(fo, "StatusName = wavewalk_right_1_1\nTime = 300\n");
    fprintf(fo, "StatusName = wavewalk_right_1_2\nTime = 300\n");
    fprintf(fo, "StatusName = wavewalk_right_2_0\nTime = 300\n");
    fprintf(fo, "StatusName = wavewalk_right_2_1\nTime = 300\n");
    fprintf(fo, "StatusName = wavewalk_right_2_2\nTime = 300\n");

//展示（up down）10
    fprintf(fo, "ActionGroupName = 10\nCycleCnt = 2\n");
    fprintf(fo, "ActionNumber = 12\n");
    fprintf(fo, "StatusName = down\nTime = 1000\n");
    fprintf(fo, "StatusName = up\nTime = 1000\n");
    fprintf(fo, "StatusName = split_down\nTime = 1000\n");
    fprintf(fo, "StatusName = up\nTime = 1000\n");
    fprintf(fo, "StatusName = down\nTime = 1000\n");
    fprintf(fo, "StatusName = split_up\nTime = 1000\n");
    fprintf(fo, "StatusName = down\nTime = 300\n");
    fprintf(fo, "StatusName = up\nTime = 300\n");
    fprintf(fo, "StatusName = split_down\nTime = 300\n");
    fprintf(fo, "StatusName = up\nTime = 300\n");
    fprintf(fo, "StatusName = down\nTime = 300\n");
    fprintf(fo, "StatusName = split_up\nTime = 300\n");

//展示（wave）  11
    fprintf(fo, "ActionGroupName = 11\nCycleCnt = 2\n");
    fprintf(fo, "ActionNumber = 15\n");
    fprintf(fo, "StatusName = wave_begin\nTime = 1000\n");
    fprintf(fo, "StatusName = single_wave_1\nTime = 300\n");
    fprintf(fo, "StatusName = single_wave_2\nTime = 300\n");
    fprintf(fo, "StatusName = single_wave_3\nTime = 300\n");
    fprintf(fo, "StatusName = single_wave_4\nTime = 300\n");
    fprintf(fo, "StatusName = single_wave_5\nTime = 300\n");
    fprintf(fo, "StatusName = single_wave_6\nTime = 300\n");
    fprintf(fo, "StatusName = single_wave_7\nTime = 300\n");
    fprintf(fo, "StatusName = single_wave_8\nTime = 300\n");
    fprintf(fo, "StatusName = wave_begin\nTime = 1000\n");
    fprintf(fo, "StatusName = double_wave_1\nTime = 300\n");
    fprintf(fo, "StatusName = double_wave_2\nTime = 300\n");
    fprintf(fo, "StatusName = double_wave_3\nTime = 300\n");
    fprintf(fo, "StatusName = double_wave_4\nTime = 300\n");
    fprintf(fo, "StatusName = double_wave_5\nTime = 300\n");

//变箱  12
    fprintf(fo, "ActionGroupName = 12\nCycleCnt = 1\n");
    fprintf(fo, "ActionNumber = 3\n");
    fprintf(fo, "StatusName = to_box_0\nTime = 300\n");
    fprintf(fo, "StatusName = to_box_1\nTime = 300\n");
    fprintf(fo, "StatusName = to_box_2\nTime = 300\n");


    for(int i=12; i<16; i++)
    {
        fprintf(fo, "ActionGroupName = %d\nCycleCnt = 0\nActionNumber = 0\n", i);
    }

    fclose(fo);
    return 0;
}

int main()
{
    head();
//修改开始
    status_all(93-1);
//修改结束
    action_all();
}