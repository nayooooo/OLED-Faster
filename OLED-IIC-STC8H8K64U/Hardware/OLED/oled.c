/**********************************************
//		GND -> GND
//		VCC -> VCC
//		SDA -> P2.4
//		SCL -> P2.5
**********************************************/
#include "math.h"

#include "oled.h"
#include "oledfont.h"
//OLED���Դ�
//��Ÿ�ʽ���£��������������ַ�ǵڶ��±�Ϊ��һ�±꣩
// 0 -> [7]0 1 2 3 ... 127
// 1 -> [6]0 1 2 3 ... 127
// 2 -> [5]0 1 2 3 ... 127
// 3 -> [4]0 1 2 3 ... 127
// 4 -> [3]0 1 2 3 ... 127
// 5 -> [2]0 1 2 3 ... 127
// 6 -> [1]0 1 2 3 ... 127
// 7 -> [0]0 1 2 3 ... 127
u8 OLED_GRAM[OLED_COL_MAX][OLED_PAGE_MAX];

//m^n
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;
	return result;
}

/* IIC��д���� -------------------------------------*/
/* ���ٶ�д ----------------------------------------*/
//��SSD1306д��һ���ֽڡ�
//dat:Ҫд�������/����
//cmd:����/�����־ 0,��ʾ����;1,��ʾ����;
static void OLED_WR_Byte(u8 dat,u8 cmd)
{
	IIC_WR_Byte(dat, cmd);
}

//��SSD1306д��һ���ֽ����ݡ�
//dat:Ҫд�������
static void OLED_WR_Byte_Dat(u8 dat)
{
	IIC_WR_Byte_Dat(dat);
}

//��SSD1306д��һ���ֽ����
//cmd:Ҫд�������
static void OLED_WR_Byte_Cmd(u8 cmd)
{
	IIC_WR_Byte_Cmd(cmd);
}
/* ���ٶ�д ----------------------------------------*/
//��SSD1306д��һ���ֽڡ�
//dat:Ҫд�������/����
//cmd:����/�����־ 0,��ʾ����;1,��ʾ����;
static void OLED_WR_Byte_Fast(u8 *buf, u16 size, u8 cmd)
{
	IIC_WR_Byte_Fast(buf, size, cmd);
}

//��SSD1306д��һ���ֽ����ݡ�
//dat:Ҫд�������
static void OLED_WR_Byte_Dat_Fast(u8 *Dat_Buf, u16 size)
{
	IIC_WR_Byte_Dat_Fast(Dat_Buf, size);
}

//��SSD1306д��һ���ֽ����
//cmd:Ҫд�������
static void OLED_WR_Byte_Cmd_Fast(u8 *Cmd_Buf, u16 size)
{
	IIC_WR_Byte_Cmd_Fast(Cmd_Buf, size);
}

/* ���»��浽OLED ----------------------------------*/
void OLED_Refresh_Gram(void)
{
	OLED_WR_Byte_Cmd (0xb0+0);
	OLED_WR_Byte_Cmd (0x00);
	OLED_WR_Byte_Cmd (0x10);
	OLED_WR_Byte_Dat_Fast((u8*)OLED_GRAM, OLED_GRAM_SIZE);
}

//OLED����ʾ
void OLED_Display_On(void)
{
	OLED_WR_Byte_Cmd(0X8D);
	OLED_WR_Byte_Cmd(0X14);
	OLED_WR_Byte_Cmd(0XAF);
}

//OLED����ʾ
void OLED_Display_Off(void)
{
	OLED_WR_Byte_Cmd(0X8D);
	OLED_WR_Byte_Cmd(0X10);
	OLED_WR_Byte_Cmd(0XAE);
}

//OLED����
void OLED_Clear(void)  
{  
	u8 i,n;  
	for(i=0;i<OLED_PAGE_MAX;i++)for(n=0;n<OLED_COL_MAX;n++)OLED_GRAM[n][i]=0X00;  
	OLED_Refresh_Gram();
}

//OLED����		   
void OLED_DrawPoint(u8 x,u8 y,u8 mode)
{
	u8 pos,bx,temp=0;
	if(x>OLED_COL_MAX-1||y>OLED_ROW_MAX-1)return;
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(mode)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;
#if SHOW_EVERY_STEEP
	OLED_Refresh_Gram();
#endif
}

/* ---------------- base graphics ---------------- */

//OLED����
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode)
{
#if OLED_DRAW_LINE_BRESENHAM
	int16_t dx = x2 - x1, dy = y2 - y1;
	Point_int16_t p = { 0, 0 };  //��ֹ�� p.x=127��p.y=63 ʱ����
	uint8_t Point_Position_Inverse_Flag = 0X00;  // 0,1,2,3,4bit�ֱ��ʾ��һ���������������޼����� y=x �ԳƱ�ʶ
	int16_t incrE, incrNE, d;
	Point temp;
	
	if(dy==0)			// k==0
	{
		if(dx<0)
		{
			dx = -dx;
			x1 ^= x2; x2 ^= x1; x1 ^= x2;
		}
		for(; p.x<=dx; p.x++)
			OLED_DrawPoint(p.x+x1, p.y+y1, mode);
	}
	else if(dx==0)			// k������
	{
		if(dy<0)
		{
			dy = -dy;
			y1 ^= y2; y2 ^= y1; y1 ^= y2;
		}
		for(; p.y<=dy; p.y++)
			OLED_DrawPoint(p.x+x1, p.y+y1, mode);
	}
	else
	{
		//�� (x1, y1) �� (x2, y2) ����ɵ�һ�����е����
		//��������ת��֮����Կ��ɱ��������ڵ�һ������
		if(dx>0 && dy>0) Point_Position_Inverse_Flag |= 0X01;
		else if(dx>0 && dy <0)				//����ڶ�����
		{
			Point_Position_Inverse_Flag |= 0X02;
			dy = -dy;
			y2 = 2 * y1 - y2;
		}
		else if(dx<0 && dy < 0)			//�����������
		{
			Point_Position_Inverse_Flag |= 0X04;
			dx = -dx; dy = -dy;
			x1 ^= x2; x2 ^= x1; x1 ^= x2;
			y1 ^= y2; y2 ^= y1; y1 ^= y2;
		}
		else if(dx<0 && dy >0)		//�����������
		{
			Point_Position_Inverse_Flag |= 0X08;
			dx = -dx;
			x2 = 2 * x1 - x2;
		}
		//�� (x1, y1) �� (x2, y2) ����� 0<k<=1 �����Σ����任 { x0'=x1, y0'=y1 }��
		if(dx<dy)
		{
			Point_Position_Inverse_Flag |= 0X10;
			temp.x = x2; temp.y = y2;
			x2 = x1 - y1 + temp.y;
			y2 = -x1 + y1 + temp.x;
			dx = x2 - x1; dy = y2 - y1;  // ���¼��� dx, dy Ȼ���ٴ���ɵ�һ�����е����
		}
		
		incrE = 2 * dy, incrNE = 2 * (dy - dx);
		d = 2 * dy - dx;
		
		OLED_DrawPoint(p.x+x1, p.y+y1, mode);
		//��ʼ���������ƫ����
		for(p.x++; p.x<=dx; p.x++)
		{
			if(d<0){			//�Ӷ����������µ�����
				d += incrE;
			}else{				//�Ӷ������������µ�����
				p.y++;
				d += incrNE;
			}
			
			//���Ƶ�
			/* -- ����ڵ� (x0, y0) Ϊԭ��ķ�����֮���� --
			   -- x'= x0-y0+y --
			   -- y'=-x0+y0+x -- */
			switch(Point_Position_Inverse_Flag&0X0F)
			{
				case 0X01:		//��һ��������
				case 0X04:
					if(Point_Position_Inverse_Flag&0X10)
						OLED_DrawPoint(x1+p.y, y1+p.x, mode);
					else
						OLED_DrawPoint(x1+p.x, y1+p.y, mode);
					break;
				case 0X02:		//�ڶ�����
					if(Point_Position_Inverse_Flag&0X10)
						OLED_DrawPoint(x1+p.y, y1-p.x, mode);
					else
						OLED_DrawPoint(x1+p.x, y1-p.y, mode);
					break;
				case 0X08:		//��������
					if(Point_Position_Inverse_Flag&0X10)
						OLED_DrawPoint(x1-p.y, y1+p.x, mode);
					else
						OLED_DrawPoint(x1-p.x, y1+p.y, mode);
					break;
				default: break;
			}
		}
	}
#else
	u32 t; 
	int xerr=0, yerr=0, delta_x, delta_y, distance; 
	int incx, incy, uRow, uCol; 
	delta_x = x2-x1;
	delta_y = y2-y1; 
	uRow = x1; 
	uCol = y1;
	if(delta_x>0) incx=1;
	else if(delta_x==0) incx=0;
	else {incx = -1; delta_x = -delta_x;} 
	if(delta_y>0) incy = 1; 
	else if(delta_y==0) incy = 0;
	else{incy = -1; delta_y = -delta_y;} 
	if(delta_x>delta_y) distance = delta_x;
	else distance = delta_y; 
	for(t=0; t<=distance+1; t++ )
	{  
		OLED_DrawPoint(uRow, uCol, mode);
		
		xerr += delta_x; 
		yerr += delta_y;
		if(xerr>distance)
		{ 
			xerr -= distance; 
			uRow += incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr -= distance; 
			uCol += incy; 
		}
	}
#endif
}

//OLED����
void OLED_DrawCube(u8 x1,u8 y1,u8 x2,u8 y2, u8 mode)
{
	OLED_DrawLine(x1,y1,x2,y1,mode);
	OLED_DrawLine(x1,y2,x2,y2,mode);
	OLED_DrawLine(x1,y1,x1,y2,mode);
	OLED_DrawLine(x2,y1,x2,y2,mode);
}

/* ---------------- message ---------------- */

//OLED��BMP
void OLED_ShowBMP(u8 x,u8 y,const u8 *p,u8 width,u8 height,u8 mode)
{
	u8 u_x, u_y;
	u8 temp;
	u8 csize;
	u8 i, j;
	
	if(x>OLED_COL_MAX-1 || y>OLED_ROW_MAX-1) return;
	u_x = x; u_y = y;
	csize = (height/8 + ((height%8)?1:0))*width;
	for(i=0; i<csize; i++)
	{
		temp = *p;
		for(j=0; j<8; j++)
		{
			temp&0X80 ? OLED_DrawPoint(u_x,u_y,mode) : OLED_DrawPoint(u_x,u_y,!mode);
			temp <<= 1;
			u_y++;
			if((u_y-y)==height)
			{
				u_y = y;
				u_x++;
				break;
			}
		}
		p++;
	}
}

//OLED���
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode)
{  
	u8 x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)OLED_DrawPoint(x,y,mode);
	}
	OLED_Refresh_Gram();
}

//OLED��ʾ�ַ�
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode)
{      			    
	u8 temp,t,t1;
	u8 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);
	chr=chr-' ';
    for(t=0;t<csize;t++)
    {   
		if(size==12)temp=asc2_1206[chr][t];
		else if(size==16)temp=asc2_1608[chr][t];
		else if(size==24)temp=asc2_2412[chr][t];
		else return;
        for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)OLED_DrawPoint(x,y,mode);
			else OLED_DrawPoint(x,y,!mode);
			temp<<=1;
			y++;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }          
}

//OLED��ʾ����
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size,u8 mode)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ',size,mode);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0',size,1); 
	}
}

//OLED��ʾ���֣��Զ���������λ��
void OLED_ShowNums(u8 x,u8 y,u32 nums,u8 size,u8 mode)
{
	u8 digit = 0;
	u32 temp = nums;
	
	do{
		temp /= 10;
		digit++;
	}while(temp);
	OLED_ShowNum(x, y, nums, digit, size, mode);
}

//OLED��ʾС��
void OLED_ShowDecimal(u8 x, u8 y, u32 Int_Part, u8 Dec_Part, u8 size, u8 mode)
{
	u8 digital = 0;
	u8 temp = Int_Part;
	
	do{
		temp /= 10;
		digital++;
	}while(temp);
	
	OLED_ShowNums(x, y, Int_Part, size, mode);
	OLED_ShowChar(x+digital*(size/2), y, '.', size, mode);
	OLED_ShowNums(x+(digital+1)*(size/2), y, Dec_Part, size, mode);
}

//OLED��ʾ�ַ���
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size,u8 mode)
{	
    while((*p<='~')&&(*p>=' '))
    {       
        if(x>(OLED_COL_MAX-(size/2))){x=0;y+=size;}
        if(y>(OLED_ROW_MAX-size)){y=x=0;OLED_Clear();}
        OLED_ShowChar(x,y,*p,size,mode);	 
        x+=size/2;
        p++;
    }
}

/* ---------------- message ---------------- */

/* ---------------- inition ---------------- */

static void OLED_GPIO_Init(void)
{
	#ifdef USE_SOFT_IIC
		IIC_GPIO_Config();
	#endif /* USE_SOFT_IIC */
	#ifdef USE_HARD_IIC
		I2C_GPIO_Config();
	#endif /* USE_HARD_IIC */
}

//��ʼ��OLED
void OLED_Init(void)
{
	OLED_GPIO_Init();
	#ifdef USE_HARD_IIC
		I2C_Config();
	#endif /* USE_HARD_IIC */
					  
	OLED_WR_Byte_Cmd(0xAE);
	OLED_WR_Byte_Cmd(0xD5);
	OLED_WR_Byte_Cmd(80);  
	OLED_WR_Byte_Cmd(0xA8);
	OLED_WR_Byte_Cmd(0X3F);
	OLED_WR_Byte_Cmd(0xD3);
	OLED_WR_Byte_Cmd(0X00);

	OLED_WR_Byte_Cmd(0x40);
								
	OLED_WR_Byte_Cmd(0x8D);
	OLED_WR_Byte_Cmd(0x14);
	OLED_WR_Byte_Cmd(0x20);
	OLED_WR_Byte_Cmd(0x01);		// ��ֱ��ַģʽ
	OLED_WR_Byte_Cmd(0xA1);
	OLED_WR_Byte_Cmd(0xC0);
	OLED_WR_Byte_Cmd(0xDA);
	OLED_WR_Byte_Cmd(0x12);
		 
	OLED_WR_Byte_Cmd(0x81);
	OLED_WR_Byte_Cmd(0xEF);
	OLED_WR_Byte_Cmd(0xD9);
	OLED_WR_Byte_Cmd(0xF1);
	OLED_WR_Byte_Cmd(0xDB);
	OLED_WR_Byte_Cmd(0x30);

	OLED_WR_Byte_Cmd(0xA4);
	OLED_WR_Byte_Cmd(0xA6);
	OLED_WR_Byte_Cmd(0xAF);
	
	OLED_Clear();
}

/* ---------------- inition ---------------- */
