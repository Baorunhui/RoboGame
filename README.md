# 机器人文档

本文档总结自己在参加2022RoboGame时编写的代码部分

### 姿态生成器

本部分介绍自主编写的[腿部姿态生成器](./gesture_generator/generator.c)和[机械臂姿态生成器](./gesture_generator/generator_arm.c)

姿态生成器输入多组舵机的目标角度、速度，构成一系列*状态*；并将相关*状态*按运行时间连接起来，构成*动作组*
然后将*状态*和*动作组*写入[腿部姿态文件](./gesture_generator/out.mc)和[机械臂姿态文件](./gesture_generator/out_arm.mc)

再通过**16路舵机驱动模块**厂家提供的[舵机驱动程序](./reference/16%E8%B7%AF%E8%88%B5%E6%9C%BA%E6%8E%A7%E5%88%B6%E6%9D%BF%E4%B8%8A%E4%BD%8D%E6%9C%BA/MotorControl.exe)打开这些文件，即可对16路舵机驱动模块进行烧录

姿态生成器实际上是给舵机驱动程序提供了一层方便修改、调用的c语言接口，有效地提升了设计机器人动作的效率

### 单片机程序

[本部分](./MDK-ARM_project/)由**STM32CubeMX**结合**Keil uVision5**完成

单片机选用**STM32F103ZE核心板**，[参考文档](./reference/1%E3%80%81STM32F103ZE%E6%A0%B8%E5%BF%83%E6%9D%BF--%E5%8E%9F%E7%90%86%E5%9B%BE-1807M--.pdf)

#### 模块设计

单片机程序按机器人功能模块组织
* 蓝牙接收模块
* 腿部控制模块
* 机械臂控制模块
* 电机控制模块
* 音响控制模块

![1](/assets/1.png)