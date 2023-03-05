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
    			&& USART2_RX_BUF[9]==(USART2_RX_BUF[1] + USART2_RX_BUF[2] + USART2_RX_BUF[3] + USART2_RX_BUF[4] + USART2_RX_BUF[5] + USART2_RX_BUF[6] + USART2_RX_BUF[7] + USART2_RX_BUF[8])%0x100)	
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

### 腿部控制模块
代码见[foot](./MDK-ARM_project/Src/foot)

### 机械臂控制模块
代码见[arm](./MDK-ARM_project/Src/arm)

### 电机控制模块
代码见[motor](./MDK-ARM_project/Src/motor)

### 音响控制模块
代码见[music](./MDK-ARM_project/Src/music)

### 钳子丝杆部分
代码见[main.c](./MDK-ARM_project/Src/main.c)

## 辅助脚本：姿态生成器

本部分介绍自主编写的[腿部姿态生成器](./gesture_generator/generator.c)和[机械臂姿态生成器](./gesture_generator/generator_arm.c)

姿态生成器输入多组舵机的目标角度、速度，构成一系列*状态*；并将相关*状态*按运行时间连接起来，构成*动作组*
然后将*状态*和*动作组*写入[腿部姿态文件](./gesture_generator/out.mc)和[机械臂姿态文件](./gesture_generator/out_arm.mc)

再通过**16路舵机驱动模块**厂家提供的[舵机驱动程序](./reference/16%E8%B7%AF%E8%88%B5%E6%9C%BA%E6%8E%A7%E5%88%B6%E6%9D%BF%E4%B8%8A%E4%BD%8D%E6%9C%BA/MotorControl.exe)打开这些文件，即可对16路舵机驱动模块进行烧录

姿态生成器实际上是给舵机驱动程序提供了一层方便修改、调用的c语言接口，有效地提升了设计机器人动作的效率

## 手机蓝牙程序

