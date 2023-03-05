# 机器人文档

本文档总结自己在参加2022RoboGame时编写的代码部分

## 介绍

### 比赛要求
参赛队伍需要自主设计、制作并展示能够自动变形的机器人：机器人变形过程必须自行完成，不得人为辅助，但允许使用遥控的方式控制机器人

### 机器人形态设计
本次比赛中我队设计的变形机器人可以切换多种形态和移动方式，并可完成简单任务：
机器人可以在下面四种形态和移动方式之间任意切换：
* 收纳形态（静止）
* 蝎子形态（三足步态前进、原地旋转）
* 蝎子形态（波浪步态前进、横向移动）
* 战车形态（前进、原地旋转、左转右转）
机器人还可以完成以下简单任务：
* 舞蹈
* 机械臂抓取、搬运

### 模块设计
![1](/assets/pic1.png)

## 代码流程

[本部分](./MDK-ARM_project/)由**STM32CubeMX**结合**Keil uVision5**完成

单片机选用**STM32F103ZE核心板**，[参考文档](./reference/1%E3%80%81STM32F103ZE%E6%A0%B8%E5%BF%83%E6%9D%BF--%E5%8E%9F%E7%90%86%E5%9B%BE-1807M--.pdf)

单片机程序按机器人功能模块组织
* 蓝牙接收模块
* 腿部控制模块
* 机械臂控制模块
* 电机控制模块
* 音响控制模块
* 钳子丝杆部分（由于时间问题并未模块化）

### 主程序部分
代码见[main.c](./MDK-ARM_project/Src/main.c)
文件中定义了```main```函数，包括了机器人的全部动作流程

```c
HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
HAL_Delay(500);
HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
HAL_Delay(500);
HAL_UART_Receive_IT(&huart2,(uint8_t *)&USART2_NewData,1);
```
首先打开需要的PWM波端口，然后打开```huart2```端口准备接收蓝牙信号

```c
uint8_t last_mode = 0xff;
ARM_AHEAD_1();
```
初始化上一个形态标记```last_mode```
调用机械臂模块的函数```ARM_AHEAD_1()```初始化机械臂位置

然后进入一个死循环，每次循环检查蓝牙信号并做出对应动作

```c
if(&0x8000)
{
    	 if((USART2_RX_STA&0x7FFF) ==10 	               
    			&& USART2_RX_BUF[0]==0xA5 	
    			&& USART2_RX_BUF[9]==(USART2_RX_BUF[1] + USART2_RX_BUF[2] + USART2_RX_BUF[3] + 
			USART2_RX_BUF[4] + USART2_RX_BUF[5] + USART2_RX_BUF[6] + 
			USART2_RX_BUF[7] + USART2_RX_BUF[8])%0x100)	
    	{
          ......
```
在每个循环开始时先检验蓝牙信号正确与否：
通过检查```USART2_RX_STA```（蓝牙数据标志）和```USART2_RX_BUF```数组（蓝牙信号内容）的首位和校验和，来确保接受到的信号是可靠的
如果都是可靠的，则进入下面的步骤：

```c
uint8_t move_dir = USART2_RX_BUF[1];
uint8_t left_speed = USART2_RX_BUF[2];
uint8_t right_speed = USART2_RX_BUF[3];
uint8_t arm = USART2_RX_BUF[4];
uint8_t grasp = USART2_RX_BUF[5];
uint8_t mode = USART2_RX_BUF[6];
uint8_t dance = USART2_RX_BUF[7];
uint8_t save = USART2_RX_BUF[8];
```
将蓝牙信号内容按字段解码，获取当前指令信息

```c
switch(left_speed)      //left speed switch
{   
case(0x00):__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,0);break;    //0%
	 case(0x14):__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,4000) ;break;//20%
	 case(0x28):__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,8000) ;break;//40%
	 case(0x3C):__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,12000);break;//60%
	 case(0x50):__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,16000);break;//80%
	 case(0x64):__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,20000);break;//100%
	 default:break;
}
```
根据```left_speed```字段调整```htim2```的PWM波，它是发送给电机驱动模块的PWM波，以此调整车速。```right_speed```字段同理
这里将左侧两轮和右侧两轮的速度分别设置，通过改变两轮差速以实现车形态下的左转右转

```c
switch(mode)
{
    case(0x00):   //car mode
    case(0x01):   //foot mode (tri)
    case(0x02):   //foot mode (wave)
    case(0x03):   //box mode
    default:break;
}
```
根据```mode```字段判断当前机器人形态，并在每个形态下分别实现对应操作
下面以车形态为例：
```c
if(last_mode != 0xff && last_mode != mode)	//switch to car
{
TO_CAR();
}
```
如果```last_mode```标记的上一个形态和当前形态不同，则切换为车形态

```c
switch(move_dir)      //motion switch
{
 case(0x01):CAR_GO();break;
 case(0x02):CAR_RGO();break;
 case(0x03):CAR_LGO();break;
 case(0x04):CAR_BACK();break;
 case(0x00):CAR_STOP();break;
 default:break;
}
```
然后根据```move_dir```字段，确定移动方向
调用电机控制模块的轮行函数或是腿部控制模块的行走步态函数实现移动

```c
if(dance == 0x01)
{
  DANCE_WAVE();
  //MUSIC_WAVE();
}
```
有的形态下，如果设置了```dance```，则会调用腿部控制模块的舞蹈函数和音响模块的播放音乐

接着在```switch(mode)```代码块之外判断机械臂动作，这体现了机器人下部和上部功能的分离，即无论什么形态都可以运动机械臂
```c
switch(grasp)      //grasp control
{
case(0x01):ARM_GRASP();break;
case(0x00):ARM_RELEASE();break;
default:break;
}
```
通过```grasp```字段控制机械爪是抓取还是放下，调用机械臂控制模块的函数

```c
switch(arm)      //arm control
{
 case(0x9C):ARM_BACK_2();break;
 case(0xce):ARM_BACK_1();break;
 case(0x00):ARM_MID();break;
 case(0x32):ARM_AHEAD_1();break;
 case(0x64):ARM_AHEAD_2(); break;
default:break;
}
```
通过```arm```字段调整机械臂的位置，调用机械臂控制模块的函数

```c
last_mode = mode;
USART2_RX_STA=0;
```
最后在循环结束记录当前形态，重置蓝牙标志，结束本次循环

### 蓝牙接收模块
代码见[usart.c](./MDK-ARM_project/Src/usart.c)和[usart.h](./MDK-ARM_project/Src/usart.h)


```c
extern uint8_t  USART2_RX_BUF[USART2_REC_LEN];//usart receive buffer
extern uint16_t USART2_RX_STA; //receive state 
extern uint8_t USART2_NewData;// 1 byte 
```
在```usart.h```中定义了几个全局变量，以便它们在```main.c```被调用

```c
void  HAL_UART_RxCpltCallback(UART_HandleTypeDef  *huart)
{
	if(huart ==&huart2)
    {
        if((USART2_RX_STA&0x8000)==0)
        {
            if(USART2_NewData==0x5A)
            {
                 USART2_RX_STA|=0x8000; 
            }
            else
            {
                   USART2_RX_BUF[USART2_RX_STA&0X7FFF]=USART2_NewData; 
                   USART2_RX_STA++;  
                   if(USART2_RX_STA>(USART2_REC_LEN-1))
			USART2_RX_STA=0;
            }
        }
        HAL_UART_Receive_IT(&huart2,(uint8_t *)&USART2_NewData,1); 
    }
}
```
在```usart.c```中定义了```HAL_UART_RxCpltCallback```函数，它定义了收到蓝牙信号，引发串口中断后的行为：
检验并设置```USART2_RX_STA```，用```USART2_NewData```装填```USART2_RX_BUF```

值得注意的是，在每次串口处理的最后，都要调用
```c
HAL_UART_Receive_IT(&huart2,(uint8_t *)&USART2_NewData,1); 
```
重新打开串口

### 腿部控制模块
代码见[foot](./MDK-ARM_project/Src/foot)
```c
void FOOT_INIT(); 
void TO_CAR();
void TO_FOOT();
void TO_BOX();

void TRIWALK_AHEAD();
void TRIWALK_BACK();
void TRIWALK_LEFT();
void TRIWALK_RIGHT();

void WAVEWALK_AHEAD();
void WAVEWALK_BACK();
void WAVEWALK_LEFT();
void WAVEWALK_RIGHT();

void DANCE_UP_DOWN();
void DANCE_WAVE();
```
本部分设计了控制腿部行动的几种函数（变形、三组行走、波浪行走、舞蹈动作）
它们的实现都很类似，下面以初始化```FOOT_INIT()```为例

```c
void FOOT_INIT()
{
	uint8_t buf[USART3_LEN] = {0xff, 0x09, 0x00, 0x00, 0x00};
	for(int i=0; i< USART3_LEN; i++)
		USART3_TX_BUF[i] = buf[i];
	HAL_UART_Transmit(&huart3, USART3_TX_BUF, USART3_LEN, HAL_MAX_DELAY);
}
```
函数将```{0xff, 0x09, 0x00, 0x00, 0x00}```发送给串口```huart3```，这个数据将被串口连接的16路舵机驱动板接受，舵机驱动板将选择对应的动作组，将控制信号发送给腿部舵机

### 机械臂控制模块
代码见[arm](./MDK-ARM_project/Src/arm)
```c
void ARM_GRASP();
void ARM_RELEASE();

void ARM_BACK_1(); 
void ARM_BACK_2();
void ARM_MID();
void ARM_AHEAD_1();
void ARM_AHEAD_2();
```
本部分设计了控制机械臂行动的几种函数（抓取、释放、机械臂位置）
它们的实现和腿部类似，不再赘述

### 电机控制模块
代码见[motor](./MDK-ARM_project/Src/motor)

本部分分为两个层次
```c
void L_MOTOR_GO();
void R_MOTOR_GO();
void L_MOTOR_BACK();
void R_MOTOR_BACK();
void L_MOTOR_STOP();
void R_MOTOR_STOP();
```
```motor.h```和```motor.c```和实现了左右侧轮子的前进、后退、停止
```c
void CAR_GO();                 
void CAR_BACK();               
void CAR_LGO();                
void CAR_RGO();                
void CAR_STOP();  
```
```motor_control.h```和```motor_control.c```则组合上面的函数，实现车形态的前进、后退、左右转

```c
void L_MOTOR_GO()
{
	HAL_GPIO_WritePin(GPIOA, IN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, IN2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, IN11_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, IN22_Pin, GPIO_PIN_RESET);

}
```
以```L_MOTOR_GO()```为例，它通过设置单片机端口的电平，向电机驱动板发送信号以设置轮子转向
而轮子转速则在```main.c```中通过调整PWM波以设置

```c
d CAR_GO()
{	
	L_MOTOR_GO();
	R_MOTOR_GO();
}
```
以```CAR_GO()```为例，它通过左侧两轮正转和右侧两轮正转来实现前行


### 音响控制模块
代码见[music](./MDK-ARM_project/Src/music)
```c
void MUSIC_UP_DOWN();
void MUSIC_WAVE();
void MUSIC_WALK();
void MUSIC_REOL();
void MUSIC_OFF();
```
本部分定义了几种音乐播放函数（开始播放指定音乐、音乐结束）
它们的实现和舵机控制也类似，通过串口向音响控制板发送指令，故不赘述

### 钳子丝杆部分
代码见[main.c](./MDK-ARM_project/Src/main.c)
本部分是最后加上的，所以没有抽取作为一个模块，而是结合在```main.c```中的变形部分
以变形为车形态为例：
```c
if(last_mode != 0xff && last_mode != mode)	//switch to car
{
	TO_CAR();
	//hand
	//RESET: back
	//SET: forward
	HAL_GPIO_WritePin(GPIOF ,GPIO_PIN_13,GPIO_PIN_RESET );
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
	HAL_Delay (1000);
	HAL_TIM_PWM_Stop(&htim8,TIM_CHANNEL_2);
}
```
通过向丝杆驱动发送特定时长的PWM波，可以控制丝杆运动距离
而端口```GPIOF ,GPIO_PIN_13```的电位高低则控制丝杆运动的方向

## 辅助脚本：姿态生成器

本部分介绍自主编写的[腿部姿态生成器](./gesture_generator/generator.c)和[机械臂姿态生成器](./gesture_generator/generator_arm.c)

姿态生成器输入多组舵机的目标角度、速度，构成一系列*状态*；并将相关*状态*按运行时间连接起来，构成*动作组*
然后将*状态*和*动作组*写入[腿部姿态文件](./gesture_generator/out.mc)和[机械臂姿态文件](./gesture_generator/out_arm.mc)

再通过**16路舵机驱动模块**厂家提供的[舵机驱动程序](./reference/16%E8%B7%AF%E8%88%B5%E6%9C%BA%E6%8E%A7%E5%88%B6%E6%9D%BF%E4%B8%8A%E4%BD%8D%E6%9C%BA/MotorControl.exe)打开这些文件，即可对16路舵机驱动模块进行烧录

姿态生成器实际上是给舵机驱动程序提供了一层方便修改、调用的c语言接口，有效地提升了设计机器人动作的效率

## 手机蓝牙程序
![2](/assets/pic2.jpg)
本部分采用别人开发的蓝牙调试器
https://www.jianshu.com/p/1a8262492619
在它的框架上可以自定义按键发送的蓝牙指令内容，十分便捷

## 出现的一些问题和解决方案
这里记录制作过程中的各种问题，读者可以有所参考

### 蓝牙短按失控
原本的预期是：
按住蓝牙程序的前进键，会发送前进信号，小车前进；
松手时，会发送停止信号，小车会立刻停下。
但是如果快速地按前进键并松手的话，小车只能收到前进信号，而不能收到停止信号，就会一直前进
经过检查发现，是蓝牙程序默认的**空间操作模式发送间隔**设置得过大，短按时长小于该间隔，故只能发送前一个信号
调整该间隔即可

### 单片机掉线
在经历很长时间工作之后，单片机似乎仍表现良好，机器人所有功能正常
但是在加入一个新的音响模块时，音响模块无法正常工作、机械臂模块经常掉线，表现为不受控制并重启
但是检查舵机控制模块和音响模块都没有问题，最终换了一个新的单片机问题被解决了
所以认为是上一个单片机负荷过大，导致出现故障，于是后来并没有加入音响模块

### 分电板共地
之前的各个模块3.3v和5v的电都是通过单片机的端口取电的，但是随着模块越来越多，单片机能提供的电压也不再稳定
最后解决方案是统一从分电板上取电

### 蝎钳角度
蝎子的钳子是后加的，在不改变原有的机械结构的基础上采用了 丝杆——万向轴——鱼眼轴承 的方案，但是它们连接的角度并没有仔细计算，很大程度是硬凑出来的，所幸能用

### 重装舵机
在准备比赛前几天我们拆下了机器人的各个组件进行喷漆，但是在组装时没有标记各个舵机原有的角度、位置，导致一上电之后机器人各个脚四仰八叉，又要费精力重新调整角度
