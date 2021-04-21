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
//存储块1 NOR/PSRAM 1  BTCR[0],  [1];
//存储块1 NOR/PSRAM 2  BTCR[2],  [3];
//存储块1 NOR/PSRAM 3  BTCR[4],  [5];
//存储块1 NOR/PSRAM 4  BTCR[6],  [7];->LCD模式A-SRAM/PSRAM(CRAM) OE翻转

//存储块1 NOR/PSRAM 1  BWTR[0] 
//存储块1 NOR/PSRAM 2  BWTR[2] 
//存储块1 NOR/PSRAM 3  BWTR[4]  
//存储块1 NOR/PSRAM 4  BWTR[6]  




void Stm32F10x_FsmcInit(void)
{
	RCC->AHBENR  |= RCC_AHBENR_FSMCEN; /*!< FSMC clock enable */ 
  //●1.initial FSMC_BWTR[6]闪存写时序寄存器●	
	FSMC_Bank1E->BWTR[6] = 0X00000000;
//FSMC_Bank1E->BWTR[6] &=~FSMC_BWTR4_ACCMOD;//00：访问模式A	
	FSMC_Bank1E->BWTR[6] |= FSMC_BWTR4_DATAST_0;//1111 1111：DATAST保持时间=256个HCLK时钟周期(这是复位后的默认数值)。
//	FSMC_Bank1E->BWTR[6] |= FSMC_BWTR4_ADDSET;//1111：ADDHLD保持时间=16个HCLK时钟周期(这是复位后的默认数值)。	
	
  //●2.INIT 闪存片选时序寄存器4 FSMC_BTR4  ●
	FSMC_Bank1->BTCR[7]  = 0X00000000;
//FSMC_Bank1->BTCR[7] &=~FSMC_BTR4_ACCMOD;//00：访问模式A
	FSMC_Bank1->BTCR[7] |= FSMC_BTR4_DATAST;//1111 1111：DATAST保持时间=256个HCLK时钟周期(这是复位后的默认数值)。
	FSMC_Bank1->BTCR[7] |= FSMC_BTR4_ADDSET;//111：ADDHLD保持时间=16个HCLK时钟周期(这是复位后的默认数值)。  	
  //●3.INIT SRAM/NOR闪存片选控制寄存器4    ●
	FSMC_Bank1->BTCR[6] = 0X00000000;
	FSMC_Bank1->BTCR[6] |= FSMC_BCR4_EXTMOD;//EXTMOD：扩展模式使能 (Extended mode enable)
  FSMC_Bank1->BTCR[6] |= FSMC_BCR4_WREN;  //WREN：写使能位 (Write enable bit)	
	FSMC_Bank1->BTCR[6] |= FSMC_BCR4_MWID_0;//01：16位(复位后的默认状态)
//FSMC_Bank1->BTCR[6] &=~FSMC_BCR4_MTYP;  //00：SRAM、ROM(存储器块2...4在复位后的默认值)
//FSMC_Bank1->BTCR[6] &=~FSMC_BCR4_MUXEN; //0：地址/数据不复用。 
	FSMC_Bank1->BTCR[6] |= FSMC_BCR4_MBKEN; //1：启用对应的存储器块。
}
