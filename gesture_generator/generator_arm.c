#include <stdio.h>


//输出无需修改的头部信息
void head()
{
    FILE *fi, *fo;
    int c;
    fi = fopen("head.txt", "r");
    fo = fopen("out_arm.mc", "w");
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

void print_status_no_grasp(FILE *fo, int status[][2])
{
    for(int i=0; i<16; i++)
    {
        if(i>=0 && i<4)
        {
            fprintf(fo, "Angle%d = %d\nSpeed%d = %d\nbUse%d = True\n", i, status[i][0], i, status[i][1], i);
        }
        else
        {
            fprintf(fo, "Angle%d = %d\nSpeed%d = %d\nbUse%d = False\n", i, status[i][0], i, status[i][1], i);
        }
    }
}

void print_status_grasp(FILE *fo, int status[][2])
{
    for(int i=0; i<16; i++)
    {
        if(i == 4)
        {
            fprintf(fo, "Angle%d = %d\nSpeed%d = %d\nbUse%d = True\n", i, status[i][0], i, status[i][1], i);
        }
        else
        {
            fprintf(fo, "Angle%d = %d\nSpeed%d = %d\nbUse%d = False\n", i, status[i][0], i, status[i][1], i);
        }
    }
}

//输出所有状态
int status_all(int status_count)
{

    FILE *fo;
    fo = fopen("out_arm.mc", "a");

    //状态初始化
    int origin_status[16][2] ={90,19,90,19,90,19,90,19,90,19,90,19,90,19,90,19,90,19,90,19,90,19,90,19,90,19,90,19,90,19,90,19};
    int status[16][2];
    fprintf(fo, "StatusNumber = %d\n", status_count);

//减速

    for(int i=0; i<16; i++)
    {
            origin_status[i][1] = 3;
    }
    origin_status[4][1] = 1;


    for(int i=0; i<16; i++)
    {
            for(int j=0; j<2; j++)
            {
                status[i][j] = origin_status[i][j];
            }
    }

//输出初始状态
    fprintf(fo, "StatusName = dangerous_initial\n");
    print_status(fo ,status);

//修改开始：

//前伸2
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<2; j++)
        {
            status[i][j] = origin_status[i][j];
        }
    }
    fprintf(fo, "StatusName = ahead_2\n");
    status[0][0] = 15;
    status[1][0] = 180;
    status[2][0] = 90;
    status[3][0] = 90;
    status[4][0] = 0;
    print_status_no_grasp(fo ,status);



//前伸1
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<2; j++)
        {
            status[i][j] = origin_status[i][j];
        }
    }
    fprintf(fo, "StatusName = ahead_1\n");
    status[0][0] = 40;
    status[1][0] = 130;
    status[2][0] = 180;
    status[3][0] = 90;
    status[4][0] = 0;
    print_status_no_grasp(fo ,status);


//竖直
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<2; j++)
        {
            status[i][j] = origin_status[i][j];
        }
    }
    fprintf(fo, "StatusName = vertical\n");
    status[0][0] = 15;
    status[1][0] = 90;
    status[2][0] = 90;
    status[3][0] = 90;
    status[4][0] = 0;
    print_status_no_grasp(fo ,status);

//后仰1
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<2; j++)
        {
            status[i][j] = origin_status[i][j];
        }
    }
    fprintf(fo, "StatusName = back_1\n");
    status[0][0] = 90;
    status[1][0] = 130;
    status[2][0] = 50;
    status[3][0] = 90;
    status[4][0] = 0;
    print_status_no_grasp(fo ,status);

//后仰2
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<2; j++)
        {
            status[i][j] = origin_status[i][j];
        }
    }
    fprintf(fo, "StatusName = back_2\n");
    status[0][0] = 60;
    status[1][0] = 60;
    status[2][0] = 30;
    status[3][0] = 90;
    status[4][0] = 0;
    print_status_no_grasp(fo ,status);

//抓取
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<2; j++)
        {
            status[i][j] = origin_status[i][j];
        }
    }
    fprintf(fo, "StatusName = grasp\n");
    status[4][0] = 90;
    print_status_grasp(fo ,status);

//松手
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<2; j++)
        {
            status[i][j] = origin_status[i][j];
        }
    }
    fprintf(fo, "StatusName = release\n");
    status[4][0] = 0;
    print_status_grasp(fo ,status);

//修改结束

    fclose(fo);
    return 0;

}

int action_all()
{
    FILE *fo;
    fo = fopen("out_arm.mc", "a");
    fprintf(fo, "ActionGroupNumber = 16\n");
    for(int i=0; i<16; i++)
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
    status_all(11 - 3);
//修改结束
    action_all();
}