/**********************************************
//		GND -> GND
//		VCC -> VCC
//		SDA -> P2.4
//		SCL -> P2.5
**********************************************/
#ifndef __OLED_H
#define __OLED_H			  	 
#include "config.h"
#include "stdlib.h"

#define USE_HARD_IIC
//#define USE_SOFT_IIC

#ifdef USE_SOFT_IIC
	#include "iic.h"
#endif /* USE_SOFT_IIC */
#ifdef USE_HARD_IIC
	#include "MyI2C.h"
#endif /* USE_HARD_IIC */

#define SLAVE_ADDRESS (0x78)

#define OLED_COL_MAX (128)
#define OLED_ROW_MAX (64)
#define OLED_PAGE_MAX (OLED_ROW_MAX/8)
#define OLED_ROW_COL_MAX ((OLED_COL_MAX>OLED_ROW_MAX)?(OLED_COL_MAX):(OLED_ROW_MAX))
#define OLED_ROW_COL_MIN ((OLED_COL_MAX<OLED_ROW_MAX)?(OLED_COL_MAX):(OLED_ROW_MAX))

#define OLED_GRAM_SIZE (OLED_PAGE_MAX*OLED_COL_MAX)
		     
#define OLED_CMD  0
#define OLED_DATA 1
#define OLED_CMD_CHR 0x00
#define OLED_DATA_CHR 0x40

#define FILL 1
#define CLEAR 0

/* ---------------- OLED端口定义 ---------------- */

#define OLED_SCLK_Clr()		SPI_SCLK_Clr()
#define OLED_SCLK_Set()		SPI_SCLK_Set()
#define OLED_SCLK_Pin		SPI_SCLK_Pin

#define OLED_SDIN_Clr()		SPI_SDIN_Clr()
#define OLED_SDIN_Set()		SPI_SDIN_Set()
#define OLED_SDIN_Pin		SPI_SDIN_Pin

#define OLED_RST_Clr()		SPI_RST_Clr()
#define OLED_RST_Set()		SPI_RST_Set()
#define OLED_RST_Pin		SPI_RST_Pin

#define OLED_DC_Clr()		SPI_DC_Clr()
#define OLED_DC_Set()		SPI_DC_Set()
#define OLED_DC_Pin			SPI_DC_Pin
 		                
#define OLED_CS_Clr()		SPI_CS_Clr()
#define OLED_CS_Set()		SPI_CS_Set()
#define OLED_CS_Pin			SPI_CS_Pin

/* ---------------- OLED端口定义 ---------------- */

/* ---------------- 结构体定义 ---------------- */

typedef struct
{
	uint8_t x;
	uint8_t y;
}Point;

typedef struct
{
	int8_t x;
	int8_t y;
}Point_Signed;

typedef struct
{
	uint16_t x;
	uint16_t y;
}Point_uint16_t;

typedef struct
{
	int16_t x;
	int16_t y;
}Point_int16_t;

typedef struct
{
	float x;
	float y;
}Point_Float;

typedef struct
{
	uint8_t x0;
	uint8_t y0;
	uint8_t r;
}Circle;

/* ---------------- 结构体定义 ---------------- */

/* ---------------- 函数实现方法定义 ---------------- */
#define SHOW_EVERY_STEEP 0
#define Stationary_Circle
//#define Dynamic_Circle
#define OLED_DRAW_LINE_BRESENHAM 1
/*
0 -> brasenham
*/
#define OLED_DRAW_ELLIPSE_METHOD 0
/* ---------------- 函数实现方法定义 ---------------- */

//OLED控制用函数
u32 mypow(u8 m,u8 n);
static void OLED_WR_Byte(u8 dat,u8 cmd);
static void OLED_WR_Byte_Dat(u8 dat);
static void OLED_WR_Byte_Cmd(u8 cmd);
static void OLED_WR_Byte_Fast(u8 *buf, u16 size, u8 cmd);
static void OLED_WR_Byte_Dat_Fast(u8 *Dat_Buf, u16 size);
static void OLED_WR_Byte_Cmd_Fast(u8 *Cmd_Buf, u16 size);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);
static void OLED_GPIO_Init(void);
void OLED_Init(void);
void OLED_Clear(void);

void OLED_DrawPoint(u8 x,u8 y,u8 mode);

void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2, u8 mode);
void OLED_DrawCube(u8 x1,u8 y1,u8 x2,u8 y2, u8 mode);

void OLED_ShowBMP(u8 x,u8 y,const u8 *p,u8 width,u8 height,u8 mode);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode);

void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size,u8 mode);
void OLED_ShowNums(u8 x,u8 y,u32 nums,u8 size,u8 mode);
void OLED_ShowDecimal(u8 x, u8 y, u32 Int_Part, u8 Dec_Part, u8 size, u8 mode);
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size,u8 mode);

#endif
	 



