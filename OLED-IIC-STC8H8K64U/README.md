# OLED-IIC-STC8H8K64U #

本例程通过优化软件IIC实现高速刷新OLED。

# 工程结构 #

## Fwlib ##

官方库文件。

## User ##

**main.c**文件。

## System ##

片上外设配置文件。

## Hardware ##

### LED ###

LED配置文件，主要用于Debug。

### OLED ###

OLED驱动文件、OLED ASCII字库、OLED屏幕输出文件。

## Software ##

### IIC ###

软件IIC配置文件。

## Obj ##

工程编译输出文件。

## Project ##

工程配置文件

## README.md ##

说明文档。

# 注意 #

本例程只针对STC8H8K64U进行了测试，测试IRC频率分别为11.0592MHz、24MHz、48MHz，它们的显示效果分别是43Hz、94Hz、无法显示（理想状态）。

# 更新日志 #

删除了iic文件中没有用到的内容。		--2022.07.29--