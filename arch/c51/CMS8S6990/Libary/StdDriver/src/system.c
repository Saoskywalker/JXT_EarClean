/*******************************************************************************
* Copyright (C) 2019 China Micro Semiconductor Limited Company. All Rights Reserved.
*
* This software is owned and published by:
* CMS LLC, No 2609-10, Taurus Plaza, TaoyuanRoad, NanshanDistrict, Shenzhen, China.
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with CMS
* components. This software is licensed by CMS to be adapted only
* for use in systems utilizing CMS components. CMS shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. CMS is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/

/****************************************************************************/
/** \file system.c
**
**  
**
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "system.h"

/****************************************************************************/
/*	Local pre-processor symbols/macros('#define')
****************************************************************************/

/****************************************************************************/
/*	Global variable definitions(declared in header file with 'extern')
****************************************************************************/

/****************************************************************************/
/*	Local type definitions('typedef')
****************************************************************************/

/****************************************************************************/
/*	Local variable  definitions('static')
****************************************************************************/

/****************************************************************************/
/*	Local function prototypes('static')
****************************************************************************/

/****************************************************************************/
/*	Function implementation - global ('extern') and local('static')
****************************************************************************/

/*****************************************************************************
 ** \brief	 SYS_EnableLVD
 **			 ????????????????????????
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void SYS_EnableLVD(void)
{
	LVDCON |= LVD_LVDCON_LVDEN_Msk;
}
/*****************************************************************************
 ** \brief	 SYS_DisableLVD
 **			  ????????????????????????
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void SYS_DisableLVD(void)
{
	LVDCON &= ~(LVD_LVDCON_LVDEN_Msk);	
}
/*****************************************************************************
 ** \brief	 SYS_ConfigLVD
 **			 ??????????????????????????????
 ** \param [in] LVDValue :(1)SYS_LVD_2_0V
 **						  (2)SYS_LVD_2_2V
 **						  (3)SYS_LVD_2_4V
 **						  (4)SYS_LVD_2_7V
 **						  (5)SYS_LVD_3_0V
 **						  (6)SYS_LVD_3_7V
 **						  (7)SYS_LVD_4_0V
 **						  (7)SYS_LVD_4_3V
 ** \return  none
 ** \note	 
*****************************************************************************/
void SYS_ConfigLVD(uint8_t LVDValue)
{
	uint8_t Temp=0;
	
	Temp = LVDCON;
	Temp &= ~(LVD_LVDCON_LVDSEL_Msk);
	Temp |= LVDValue;	
	LVDCON = Temp;	
}

/*****************************************************************************
 ** \brief	 SYS_EnableLVDInt
 **			 ??????????????????????????????
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void SYS_EnableLVDInt(void)
{
	LVDCON |= LVD_LVDCON_LVDINTE_Msk;	
}
/*****************************************************************************
 ** \brief	 SYS_DisableLVDInt
 **			  ??????????????????????????????
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void SYS_DisableLVDInt(void)
{
	LVDCON &= ~(LVD_LVDCON_LVDINTE_Msk);	
}

/*****************************************************************************
 ** \brief	 SYS_GetLVDIntFlag
 **			 ??????LVD???????????????
 ** \param [in] none
 ** \return  0:????????? 1????????????
 ** \note	 
*****************************************************************************/
uint8_t SYS_GetLVDIntFlag(void)
{
	return((LVDCON & LVD_LVDCON_LVDINTF_Msk)? 1:0);
}

/*****************************************************************************
 ** \brief	 SYS_ClearLVDIntFlag
 **			 ??????LVD???????????????
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void SYS_ClearLVDIntFlag(void)
{
	LVDCON	&= ~(LVD_LVDCON_LVDINTF_Msk);
}


/*****************************************************************************
 ** \brief	 SYS_EnableWDTReset
 **			 ??????WDT??????System
 ** \param [in] none
 **
 ** \return none
 ** \note
 *****************************************************************************/
void SYS_EnableWDTReset(void)
{
	if(EA==1) //??????TA??????????????????????????????????????????????????????
	{
		EA=0;
		TA = 0xAA;
		TA = 0x55;
		WDCON |= WDT_WDCON_WDTRE_Msk;
		EA=1;
	}
	else
	{
		TA = 0xAA;
		TA = 0x55;
		WDCON |= WDT_WDCON_WDTRE_Msk;
	}
}
/*****************************************************************************
 ** \brief	 SYS_DisableWDTReset
 **			 ??????WDT??????System
 ** \param [in] none
 **
 ** \return none
 ** \note
 *****************************************************************************/
void SYS_DisableWDTReset(void)
{
	if(EA==1) //??????TA??????????????????????????????????????????????????????
	{
		EA=0;
		TA = 0xAA;
		TA = 0x55;
		WDCON &= ~(WDT_WDCON_WDTRE_Msk);
		EA=1;
	}
	else
	{
		TA = 0xAA;
		TA = 0x55;
		WDCON &= ~(WDT_WDCON_WDTRE_Msk);
	}
}
/*****************************************************************************
 ** \brief	 SYS_GetWDTResetFlag
 **			 ??????WDT??????System?????????
 ** \param [in] none
 **
 ** \return 0???????????????WDT????????????    1????????????WDT????????????
 ** \note
 *****************************************************************************/
uint8_t SYS_GetWDTResetFlag(void)
{
	return((WDCON & WDT_WDCON_WDTRF_Msk)? 1:0);
}
/*****************************************************************************
 ** \brief	 SYS_ClearWDTResetFlag
 **			 ??????WDT??????System?????????
 ** \param [in] none
 **
 ** \return   none
 ** \note
 *****************************************************************************/
void SYS_ClearWDTResetFlag(void)
{
	if(EA==1) //??????TA??????????????????????????????????????????????????????
	{
		EA=0;
		TA = 0xAA;
		TA = 0x55;
		WDCON &= ~(WDT_WDCON_WDTRF_Msk);	
		EA=1;
	}
	else
	{
		TA = 0xAA;
		TA = 0x55;
		WDCON &= ~(WDT_WDCON_WDTRF_Msk);

	}
}

/*****************************************************************************
 ** \brief	 SYS_EnableSoftwareReset
 **			 ??????????????????System
 ** \param [in] none
 **
 ** \return none
 ** \note
 *****************************************************************************/
void SYS_EnableSoftwareReset(void)
{
	if(EA==1) //??????TA??????????????????????????????????????????????????????
	{
		EA=0;
		TA = 0xAA;
		TA = 0x55;
		WDCON |= WDT_WDCON_SWRST_Msk;	
		EA=1;
	}
	else
	{
		TA = 0xAA;
		TA = 0x55;
		WDCON |= WDT_WDCON_SWRST_Msk;	
	}
}
/*****************************************************************************
 ** \brief	 SYS_DisableSoftwareReset
 **			 ??????????????????System
 ** \param [in] none
 **
 ** \return none
 ** \note
 *****************************************************************************/
void SYS_DisableSoftwareReset(void)
{
	if(EA==1) //??????TA??????????????????????????????????????????????????????
	{
		EA=0;
		TA = 0xAA;
		TA = 0x55;
		WDCON &= ~(WDT_WDCON_SWRST_Msk);	
		EA=1;
	}
	else
	{
		TA = 0xAA;
		TA = 0x55;
		WDCON &= ~(WDT_WDCON_SWRST_Msk);	
	}
}
/*****************************************************************************
 ** \brief	 SYS_GetPowerOnResetFlag
 **			 ??????????????????System?????????
 ** \param [in] none
 **
 ** \return   0?????????????????????????????????    1??????????????????????????????
 ** \note
 *****************************************************************************/
uint8_t SYS_GetPowerOnResetFlag(void)
{
	return((WDCON & WDT_WDCON_PORF_Msk)? 1:0);
}
/*****************************************************************************
 ** \brief	 SYS_ClearPowerOnResetFlag
 **			 ??????PowerOn??????System?????????
 ** \param [in] none
 **
 ** \return   none
 ** \note
 *****************************************************************************/
void SYS_ClearPowerOnResetFlag(void)
{
	WDCON &= ~(WDT_WDCON_PORF_Msk);	
}


/*****************************************************************************
 ** \brief	 SYS_EnableWakeUp
 **			 ??????????????????
 ** \param [in] none
 **
 ** \return none
 ** \note	 ?????????????????????GPIO????????????
 *****************************************************************************/
void SYS_EnableWakeUp(void)
{
	PCON |= SYS_PCON_SWE_Msk;
}
/*****************************************************************************
 ** \brief	 SYS_EnableWakeUp
 **			 ??????????????????
 ** \param [in] none
 **
 ** \return none
 ** \note	???????????????????????????LVR????????????
 *****************************************************************************/
void SYS_DisableWakeUp(void)
{
	PCON &= ~(SYS_PCON_SWE_Msk);
}

/*****************************************************************************
 ** \brief	 SYS_EnterStop
 **			 ???????????????STOP??????
 ** \param [in] none
 **
 ** \return none
 ** \note	
 *****************************************************************************/
void SYS_EnterStop(void)
{ 
	_nop_();
	_nop_();
	PCON |= SYS_PCON_STOP_Msk;
	_nop_();	
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();	
}
/*****************************************************************************
 ** \brief	 SYS_EnterIdle
 **			 ?????????????????????Idle??????
 ** \param [in] none
 **
 ** \return none
 ** \note   
 *****************************************************************************/
void SYS_EnterIdle(void)
{
	_nop_();
	_nop_();
	PCON |= SYS_PCON_IDLE_Msk;
	_nop_();	
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}

/*****************************************************************************
 ** \brief	 SYS_EnableWakeUpTrig
 **			 ????????????????????????
 ** \param [in] none
 **
 ** \return none
 ** \note   
 *****************************************************************************/
void SYS_EnableWakeUpTrig(void)
{
	WUTCRH |= (1<<7);

}
/*****************************************************************************
 ** \brief	 SYS_DisableWakeUpTrig
 **			 ????????????????????????
 ** \param [in] none
 **
 ** \return none
 ** \note   
 *****************************************************************************/
void SYS_DisableWakeUpTrig(void)
{
	WUTCRH &= ~(1<<7);
}

/*****************************************************************************
 ** \brief	 SYS_ConfigWUTCLK
 **			????????????????????????
 ** \param [in] clkdiv: (1)WUT_CLK_DIV_1 
 **						(2)WUT_CLK_DIV_8
 **						(2)WUT_CLK_DIV_32
**						(2)WUT_CLK_DIV_256
 ** \return none
 ** \note   
 *****************************************************************************/
void SYS_ConfigWUTCLK(uint8_t clkdiv )
{
	uint8_t Temp=0;
	
	Temp = WUTCRH;
	Temp &= ~(0x3<<4);
	Temp |= (clkdiv<<4);
	WUTCRH = Temp;	
}

/*****************************************************************************
 ** \brief	 SYS_ConfigWUTTime
 **			????????????????????????
 ** \param [in] time: 12it???0x0 ~ 0xFFF???
 ** \return none
 ** \note   
 *****************************************************************************/
void SYS_ConfigWUTTime(uint16_t time )
{
	uint8_t Temp=0;
	
	Temp = WUTCRH;
	Temp &=0xf0;
	Temp |= time>>8;
	WUTCRH = Temp;
	
	WUTCRL = time;
}

