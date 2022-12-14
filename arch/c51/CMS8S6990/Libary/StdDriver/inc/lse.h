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

/*****************************************************************************/
/** \file lse.h
**
** 
**
** History:
** 
*****************************************************************************/
#ifndef __LSE_H__
#define __LSE_H__
/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "cms8s6990.h"
/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define') */
/*****************************************************************************/

/*****************************************************************************/
/* Global type definitions ('typedef') */
/*****************************************************************************/


/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source) */
/*****************************************************************************/


/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source) */
/*****************************************************************************/

/*****************************************************************************
 ** \brief	 LSE_EnableLSE
 **			 ????LSE????
 ** \param [in] none
 ** \return 
 ** \note   
 *****************************************************************************/
void  LSE_EnableLSE(void);
/*****************************************************************************
 ** \brief	 SYS_DisableLSE
 **			 ????LSE????
 ** \param [in] none
 ** \return 
 ** \note   
 *****************************************************************************/
void  LSE_DisableLSE(void);

/*****************************************************************************
 ** \brief	 LSE_Start
 **			 ????LSE????
 ** \param [in] none
 ** \return 
 ** \note   
 *****************************************************************************/
void LSE_Start(void);
/*****************************************************************************
 ** \brief	 LSE_Stop
 **			 ????LSE????
 ** \param [in] none
 ** \return 
 ** \note   
 *****************************************************************************/
void LSE_Stop(void);

/*****************************************************************************
 ** \brief	 LSE_ConfigLSE
 **			 ????LSE????????
 ** \param [in] Time: 16??????????
 ** \return none
 ** \note   
 *****************************************************************************/
void LSE_ConfigLSE(uint16_t  Time);

/*****************************************************************************
 ** \brief	 LSE_EnableLSEWakeup
 **			 ????LSE????????????
 ** \param [in] none
 ** \return 
 ** \note   
 *****************************************************************************/
void LSE_EnableLSEWakeup(void);

/*****************************************************************************
 ** \brief	 LSE_DisableLSEWakeup
 **			 ????LSE????????????
 ** \param [in] none
 ** \return none
 ** \note    
 *****************************************************************************/
void LSE_DisableLSEWakeup(void);

/*****************************************************************************
 ** \brief	 LSE_EnableLSEInt
 **			 ????LSE????
 ** \param [in] none
 ** \return none
 ** \note   
 *****************************************************************************/
void LSE_EnableLSEInt(void);
/*****************************************************************************
 ** \brief	LSE_DisableLSEInt
 **			 ????LSE????
 ** \param [in] none
 ** \return none
 ** \note   
 *****************************************************************************/
void LSE_DisableLSEInt(void);
/*****************************************************************************
 ** \brief	 LSE_GetLSEIntFlag
 **			 ????LSE??????????
 ** \param [in] none
 ** \return 1??????????  0????????
 ** \note  
 *****************************************************************************/
uint8_t  LSE_GetLSEIntFlag(void);
/*****************************************************************************
 ** \brief	 LSE_ClearLSEIntFlag
 **			 ????LSE??????????
 ** \param [in] none
 ** \return none
 ** \note   
 *****************************************************************************/
void  LSE_ClearLSEIntFlag(void);

/*****************************************************************************
 ** \brief	 LSE_GetLSEState
 **			 ????LSE??????????
 ** \param [in] none
 ** \return 1??????  0????????
 ** \note  
 *****************************************************************************/
uint8_t  LSE_GetLSEState(void);


#endif /*  __LSE_H__ */



