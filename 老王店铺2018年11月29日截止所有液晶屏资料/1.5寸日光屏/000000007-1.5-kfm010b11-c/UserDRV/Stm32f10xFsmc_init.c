#include "stm32f10x.h"
/** 
  * @brief Flexible Static Memory Controller
  */

//								typedef struct
//								{
//									__IO uint32_t BTCR[8];   
//								} FSMC_Bank1_TypeDef; 

//								/** 
//									* @brief Flexible Static Memory Controller Bank1E
//									*/
//									
//								typedef struct
//								{
//									__IO uint32_t BWTR[7];
//								} FSMC_Bank1E_TypeDef;
//		#define FSMC_Bank1          ((FSMC_Bank1_TypeDef *) FSMC_Bank1_R_BASE)
//		#define FSMC_Bank1E         ((FSMC_Bank1E_TypeDef *) FSMC_Bank1E_R_BASE)
//		#define FSMC_Bank2          ((FSMC_Bank2_TypeDef *) FSMC_Bank2_R_BASE)
//		#define FSMC_Bank3          ((FSMC_Bank3_TypeDef *) FSMC_Bank3_R_BASE)
//		#define FSMC_Bank4          ((FSMC_Bank4_TypeDef *) FSMC_Bank4_R_BASE)




//                     FSMC_BCR  FSMC_BTR    
//�洢��1 NOR/PSRAM 1  BTCR[0],  [1];
//�洢��1 NOR/PSRAM 2  BTCR[2],  [3];
//�洢��1 NOR/PSRAM 3  BTCR[4],  [5];
//�洢��1 NOR/PSRAM 4  BTCR[6],  [7];->LCDģʽA-SRAM/PSRAM(CRAM) OE��ת

//�洢��1 NOR/PSRAM 1  BWTR[0] 
//�洢��1 NOR/PSRAM 2  BWTR[2] 
//�洢��1 NOR/PSRAM 3  BWTR[4]  
//�洢��1 NOR/PSRAM 4  BWTR[6]  




void Stm32F10x_FsmcInit(void)
{
	RCC->AHBENR  |= RCC_AHBENR_FSMCEN; /*!< FSMC clock enable */ 
  //��1.initial FSMC_BWTR[6]����дʱ��Ĵ�����	
	FSMC_Bank1E->BWTR[6] = 0X00000000;
//FSMC_Bank1E->BWTR[6] &=~FSMC_BWTR4_ACCMOD;//00������ģʽA	
	FSMC_Bank1E->BWTR[6] |= FSMC_BWTR4_DATAST_0;//1111 1111��DATAST����ʱ��=256��HCLKʱ������(���Ǹ�λ���Ĭ����ֵ)��
//	FSMC_Bank1E->BWTR[6] |= FSMC_BWTR4_ADDSET;//1111��ADDHLD����ʱ��=16��HCLKʱ������(���Ǹ�λ���Ĭ����ֵ)��	
	
  //��2.INIT ����Ƭѡʱ��Ĵ���4 FSMC_BTR4  ��
	FSMC_Bank1->BTCR[7]  = 0X00000000;
//FSMC_Bank1->BTCR[7] &=~FSMC_BTR4_ACCMOD;//00������ģʽA
	FSMC_Bank1->BTCR[7] |= FSMC_BTR4_DATAST;//1111 1111��DATAST����ʱ��=256��HCLKʱ������(���Ǹ�λ���Ĭ����ֵ)��
	FSMC_Bank1->BTCR[7] |= FSMC_BTR4_ADDSET;//111��ADDHLD����ʱ��=16��HCLKʱ������(���Ǹ�λ���Ĭ����ֵ)��  	
  //��3.INIT SRAM/NOR����Ƭѡ���ƼĴ���4    ��
	FSMC_Bank1->BTCR[6] = 0X00000000;
	FSMC_Bank1->BTCR[6] |= FSMC_BCR4_EXTMOD;//EXTMOD����չģʽʹ�� (Extended mode enable)
  FSMC_Bank1->BTCR[6] |= FSMC_BCR4_WREN;  //WREN��дʹ��λ (Write enable bit)	
	FSMC_Bank1->BTCR[6] |= FSMC_BCR4_MWID_0;//01��16λ(��λ���Ĭ��״̬)
//FSMC_Bank1->BTCR[6] &=~FSMC_BCR4_MTYP;  //00��SRAM��ROM(�洢����2...4�ڸ�λ���Ĭ��ֵ)
//FSMC_Bank1->BTCR[6] &=~FSMC_BCR4_MUXEN; //0����ַ/���ݲ����á� 
	FSMC_Bank1->BTCR[6] |= FSMC_BCR4_MBKEN; //1�����ö�Ӧ�Ĵ洢���顣
}
