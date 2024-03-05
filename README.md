# STMf103c8t6_FPM383c
用stm32f103c8t6驱动FPM383c指纹模块，该项目基于HAL库开发，其中的指纹模块中的注册和验证流程基于通用指纹注册流程和通用指纹验证流程，并且实现自动化注册和验证。
1. tx与rx   tx->PA9,rx->PA10 波特率57600 数据长度 8bit  停止位 2
2. 舵机设置角度 Set_Angle->PB11 下降沿触发 上拉模式
3. 注册led Register_led->PA6 默认输出高电平 推挽输出 输出上拉
4. 删除led Delete_led->PA7   默认输出高电平 推挽输出 输出上拉
5. 注册按钮 Register_button->PA11 输入模式  输入上拉
6. 删除按钮 Delete_button->PA8    输入模式  输入上拉
7. 模块触摸引脚 Touch_out->PB12   输入模式  输入下拉
8. PWM 舵机 ->PA3 预分频 720 计数模式 up  重装载器 2000  自动重装载开启 TIM2_CH4
9.     STM32f103c8t6 频率为72Mhz
<<<<<<< HEAD
   通过文档说明书 实现自动注册和删除(会自动获取指纹id实现指纹注册和删除)同时通过写入内部flash实现对舵机角度的记录实现掉电不丢失旋转角度。
![image](https://github.com/Mieir/STMf103c8t6_FPM383c/blob/Motifiy/imags/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-03-05%20175412.png)
![image](https://github.com/Mieir/STMf103c8t6_FPM383c/blob/Motifiy/imags/2c6ac95ff3e78762511a8fcb162c249.jpg)
![image](https://github.com/Mieir/STMf103c8t6_FPM383c/blob/Motifiy/imags/a64c2afbc1f4a178320130d30867fd0.jpg)
![image](https://github.com/Mieir/STMf103c8t6_FPM383c/blob/Motifiy/imags/ce9edcd6ab99f4f1ce0c4cce9309e59.jpg)
=======
>>>>>>> cfc97509c6be547cbacc20f419e3c2a86b3a0040
