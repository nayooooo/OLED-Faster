/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����            */
/*---------------------------------------------------------------------*/

#include	"spi.h"

u8 	SPI_RxCnt;
u8 	SPI_RxTimerOut;
u8 	SPI_BUF_type SPI_RxBuffer[SPI_BUF_LENTH];
bit B_SPI_Busy; //����æ��־


//========================================================================
// ����: void	SPI_Init(SPI_InitTypeDef *SPIx)
// ����: SPI��ʼ������.
// ����: SPIx: �ṹ����,��ο�spi.h��Ķ���.
// ����: none.
// �汾: V1.0, 2012-11-22
//========================================================================
void	SPI_Init(SPI_InitTypeDef *SPIx)
{
	if(SPIx->SPI_SSIG == ENABLE)			SPCTL &= ~(1<<7);	//enable SS, conform Master or Slave by SS pin.
	else									SPCTL |=  (1<<7);	//disable SS, conform Master or Slave by SPI_Mode
	if(SPIx->SPI_Module == ENABLE)			SPCTL |=  (1<<6);	//SPI enable
	else									SPCTL &= ~(1<<6);	//SPI disable
	if(SPIx->SPI_FirstBit == SPI_LSB)		SPCTL |= (1<<5);	//LSB first
	else									SPCTL &= ~(1<<5);	//MSB first
	if(SPIx->SPI_Mode == SPI_Mode_Slave)	SPCTL &= ~(1<<4);	//slave
	else									SPCTL |=  (1<<4);	//master
	if(SPIx->SPI_CPOL == SPI_CPOL_High)		SPCTL |=  (1<<3);	//SCLK Idle High, Low Active.
	else									SPCTL &= ~(1<<3);	//SCLK Idle Low, High Active.
	if(SPIx->SPI_CPHA == SPI_CPHA_2Edge)	SPCTL |=  (1<<2);	//sample at the second edge
	else									SPCTL &= ~(1<<2);	//sample at the first  edge
	if(SPIx->SPI_Interrupt == ENABLE)		IE2 |=  (1<<1);
	else									IE2 &= ~(1<<1);
	SPCTL = (SPCTL & ~3) | (SPIx->SPI_Speed & 3);					//set speed
	P_SW1 = (P_SW1 & ~(3<<2)) | SPIx->SPI_IoUse;
	
	SPI_RxTimerOut = 0;
	B_SPI_Busy = 0;
}

//========================================================================
// ����: void	SPI_SetMode(u8 mode)
// ����: SPI��������ģʽ����.
// ����: mode: ָ��ģʽ, ȡֵ SPI_Mode_Master �� SPI_Mode_Slave.
// ����: none.
// �汾: V1.0, 2012-11-22
//========================================================================
void	SPI_SetMode(u8 mode)
{
	if(mode == SPI_Mode_Slave)
	{
		SPCTL &= ~(1<<4);	//��������Ϊ�ӻ�����
		SPCTL &= ~(1<<7);	//SS����ȷ������
	}
	else
	{
		SPCTL |= (1<<4);	//ʹ�� SPI ����ģʽ
		SPCTL |= (1<<7);	//����SS���Ź���
	}
}


//========================================================================
// ����: void SPI_WriteByte(u8 dat)
// ����: SPI����һ���ֽ�����.
// ����: dat: Ҫ���͵�ֵ.
// ����: none.
// �汾: V1.0, 2020-09-14
//========================================================================
void	SPI_WriteByte(u8 dat)		//SPI����һ���ֽ�����
{
	SPDAT = dat;
	B_SPI_Busy = 1;
	while(B_SPI_Busy) ;
}


//========================================================================
// ����: void SPI_Transivion (void) interrupt SPI_VECTOR
// ����: SPI�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2012-11-22
//========================================================================
void SPI_Transivion (void) interrupt SPI_VECTOR
{
	if(SPCTL & 0x10)	//����ģʽ
	{
		B_SPI_Busy = 0;
	}
	else							//�ӻ�ģʽ
	{
		if(SPI_RxCnt >= SPI_BUF_LENTH)		SPI_RxCnt = 0;
		SPI_RxBuffer[SPI_RxCnt++] = SPDAT;
		SPI_RxTimerOut = 5;
	}
	SPSTAT = SPIF + WCOL;	//��0 SPIF��WCOL��־
}

