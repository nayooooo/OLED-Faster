#include "MyI2C.h"

#include "OLED.h"

void I2C_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.Pin	= SDA_Pin|SCL_Pin;		// I2C.SDA I2C.SCL
	GPIO_InitStructure.Mode	= GPIO_PullUp;			// ׼˫���
	GPIO_Inilize(IIC_GPIO_Port, &GPIO_InitStructure);
}

void I2C_Config(void)
{
	I2C_InitTypeDef I2C_InitStructure;
	I2C_InitStructure.I2C_Mode      = I2C_Mode_Master;	//����ѡ�� I2C_Mode_Master, I2C_Mode_Slave
	I2C_InitStructure.I2C_Enable    = ENABLE;			//I2C����ʹ��, ENABLE, DISABLE
	I2C_InitStructure.I2C_MS_WDTA   = DISABLE;			//����ʹ���Զ�����, ENABLE, DISABLE
	I2C_InitStructure.I2C_MS_Interrupt = DISABLE;		//ʹ������ģʽ�ж�, ENABLE, DISABLE
	I2C_InitStructure.I2C_Speed     = 0;				//�����ٶ�=Fosc/2/(Speed*2+4), 0~63
	I2C_InitStructure.I2C_IoUse     = I2C_P24_P25;		//IO���л� I2C_P14_P15, I2C_P24_P25, I2C_P33_P32

	I2C_Init(&I2C_InitStructure);
}

void My_I2C_Init(void)
{
	I2C_GPIO_Config();
	I2C_Config();
}

//========================================================================
// ����: void IIC_WR_Byte(u8 buf, u8 cmd)
// ����: I2Cд�����ݺ���.
// ����: bufд������, cmdд�����ݻ�����.
// ����: none.
// �汾: V1.0, 2020-09-15
//========================================================================
void IIC_WR_Byte(u8 buf, u8 cmd)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
	Start();                                //������ʼ����
	SendData(SLAVE_ADDRESS);                //�����豸��ַ+д����
	RecvACK();
	if(cmd)			// ����
	{
		SendData(OLED_DATA_CHR);
	}
	else			// ����
	{
		SendData(OLED_CMD_CHR);
	}
	RecvACK();
	SendData(buf);
	RecvACK();
	Stop();                                 //����ֹͣ����
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
}

//========================================================================
// ����: void IIC_WR_Byte_Dat(u8 buf)
// ����: I2Cд�����ݺ���.
// ����: bufд������
// ����: none.
// �汾: V1.0, 2020-09-15
//========================================================================
void IIC_WR_Byte_Dat(u8 buf)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
	Start();                                //������ʼ����
	SendData(SLAVE_ADDRESS);                //�����豸��ַ+д����
	RecvACK();
	SendData(OLED_DATA_CHR);
	RecvACK();
	SendData(buf);
	RecvACK();
	Stop();                                 //����ֹͣ����
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
}

//========================================================================
// ����: void IIC_WR_Byte_Cmd(u8 buf)
// ����: I2Cд�������.
// ����: bufд������
// ����: none.
// �汾: V1.0, 2020-09-15
//========================================================================
void IIC_WR_Byte_Cmd(u8 buf)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
	Start();                                //������ʼ����
	SendData(SLAVE_ADDRESS);                //�����豸��ַ+д����
	RecvACK();
	SendData(OLED_CMD_CHR);
	RecvACK();
	SendData(buf);
	RecvACK();
	Stop();                                 //����ֹͣ����
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
}

//========================================================================
// ����: void IIC_WR_Byte_Fast(u8 *buf, u16 size, u8 cmd)
// ����: I2Cд�����ݺ���.
// ����: *bufд������, sizeд�����ݸ�����cmdд�����ݻ�����.
// ����: none.
// �汾: V1.0, 2020-09-15
//========================================================================
void IIC_WR_Byte_Fast(u8 *buf, u16 size, u8 cmd)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
	Start();                                //������ʼ����
	SendData(SLAVE_ADDRESS);                //�����豸��ַ+д����
	RecvACK();
	if(cmd)			// ����
	{
		SendData(OLED_DATA_CHR);
	}
	else			// ����
	{
		SendData(OLED_CMD_CHR);
	}
	RecvACK();
	while(size--)
	{
		SendData(*buf++);
		RecvACK();
	}
	Stop();                                 //����ֹͣ����
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
}

//========================================================================
// ����: void IIC_WR_Byte_Dat_Fast(u8 *buf, u16 size)
// ����: I2Cд�����ݺ���.
// ����: *bufд������, sizeд�����ݸ�����cmdд�����ݻ�����.
// ����: none.
// �汾: V1.0, 2020-09-15
//========================================================================
void IIC_WR_Byte_Dat_Fast(u8 *buf, u16 size)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
	Start();                                //������ʼ����
	SendData(SLAVE_ADDRESS);                //�����豸��ַ+д����
	RecvACK();
	SendData(OLED_DATA_CHR);
	RecvACK();
	while(size--)
	{
		SendData(*buf++);
		RecvACK();
	}
	Stop();                                 //����ֹͣ����
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
}

//========================================================================
// ����: void IIC_WR_Byte_Cmd_Fast(u8 *buf, u16 size)
// ����: I2Cд�������.
// ����: *bufд������, sizeд�����ݸ���
// ����: none.
// �汾: V1.0, 2020-09-15
//========================================================================
void IIC_WR_Byte_Cmd_Fast(u8 *buf, u16 size)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
	Start();                                //������ʼ����
	SendData(SLAVE_ADDRESS);                //�����豸��ַ+д����
	RecvACK();
	SendData(OLED_CMD_CHR);
	RecvACK();
	while(size--)
	{
		SendData(*buf++);
		RecvACK();
	}
	Stop();                                 //����ֹͣ����
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
}









