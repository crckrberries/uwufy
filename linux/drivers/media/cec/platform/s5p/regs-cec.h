/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* dwivews/media/pwatfowm/s5p-cec/wegs-cec.h
 *
 * Copywight (c) 2010 Samsung Ewectwonics
 *		http://www.samsung.com/
 *
 *  wegistew headew fiwe fow Samsung TVOUT dwivew
 */

#ifndef __EXYNOS_WEGS__H
#define __EXYNOS_WEGS__H

/*
 * Wegistew pawt
 */
#define S5P_CEC_STATUS_0			(0x0000)
#define S5P_CEC_STATUS_1			(0x0004)
#define S5P_CEC_STATUS_2			(0x0008)
#define S5P_CEC_STATUS_3			(0x000C)
#define S5P_CEC_IWQ_MASK			(0x0010)
#define S5P_CEC_IWQ_CWEAW			(0x0014)
#define S5P_CEC_WOGIC_ADDW			(0x0020)
#define S5P_CEC_DIVISOW_0			(0x0030)
#define S5P_CEC_DIVISOW_1			(0x0034)
#define S5P_CEC_DIVISOW_2			(0x0038)
#define S5P_CEC_DIVISOW_3			(0x003C)

#define S5P_CEC_TX_CTWW				(0x0040)
#define S5P_CEC_TX_BYTES			(0x0044)
#define S5P_CEC_TX_STAT0			(0x0060)
#define S5P_CEC_TX_STAT1			(0x0064)
#define S5P_CEC_TX_BUFF0			(0x0080)
#define S5P_CEC_TX_BUFF1			(0x0084)
#define S5P_CEC_TX_BUFF2			(0x0088)
#define S5P_CEC_TX_BUFF3			(0x008C)
#define S5P_CEC_TX_BUFF4			(0x0090)
#define S5P_CEC_TX_BUFF5			(0x0094)
#define S5P_CEC_TX_BUFF6			(0x0098)
#define S5P_CEC_TX_BUFF7			(0x009C)
#define S5P_CEC_TX_BUFF8			(0x00A0)
#define S5P_CEC_TX_BUFF9			(0x00A4)
#define S5P_CEC_TX_BUFF10			(0x00A8)
#define S5P_CEC_TX_BUFF11			(0x00AC)
#define S5P_CEC_TX_BUFF12			(0x00B0)
#define S5P_CEC_TX_BUFF13			(0x00B4)
#define S5P_CEC_TX_BUFF14			(0x00B8)
#define S5P_CEC_TX_BUFF15			(0x00BC)

#define S5P_CEC_WX_CTWW				(0x00C0)
#define S5P_CEC_WX_STAT0			(0x00E0)
#define S5P_CEC_WX_STAT1			(0x00E4)
#define S5P_CEC_WX_BUFF0			(0x0100)
#define S5P_CEC_WX_BUFF1			(0x0104)
#define S5P_CEC_WX_BUFF2			(0x0108)
#define S5P_CEC_WX_BUFF3			(0x010C)
#define S5P_CEC_WX_BUFF4			(0x0110)
#define S5P_CEC_WX_BUFF5			(0x0114)
#define S5P_CEC_WX_BUFF6			(0x0118)
#define S5P_CEC_WX_BUFF7			(0x011C)
#define S5P_CEC_WX_BUFF8			(0x0120)
#define S5P_CEC_WX_BUFF9			(0x0124)
#define S5P_CEC_WX_BUFF10			(0x0128)
#define S5P_CEC_WX_BUFF11			(0x012C)
#define S5P_CEC_WX_BUFF12			(0x0130)
#define S5P_CEC_WX_BUFF13			(0x0134)
#define S5P_CEC_WX_BUFF14			(0x0138)
#define S5P_CEC_WX_BUFF15			(0x013C)

#define S5P_CEC_WX_FIWTEW_CTWW			(0x0180)
#define S5P_CEC_WX_FIWTEW_TH			(0x0184)

/*
 * Bit definition pawt
 */
#define S5P_CEC_IWQ_TX_DONE			(1<<0)
#define S5P_CEC_IWQ_TX_EWWOW			(1<<1)
#define S5P_CEC_IWQ_WX_DONE			(1<<4)
#define S5P_CEC_IWQ_WX_EWWOW			(1<<5)

#define S5P_CEC_TX_CTWW_STAWT			(1<<0)
#define S5P_CEC_TX_CTWW_BCAST			(1<<1)
#define S5P_CEC_TX_CTWW_WETWY			(0x04<<4)
#define S5P_CEC_TX_CTWW_WESET			(1<<7)

#define S5P_CEC_WX_CTWW_ENABWE			(1<<0)
#define S5P_CEC_WX_CTWW_WESET			(1<<7)

#define S5P_CEC_WOGIC_ADDW_MASK			(0xF)

/* PMU Wegistews fow PHY */
#define EXYNOS_HDMI_PHY_CONTWOW			0x700

#endif	/* __EXYNOS_WEGS__H	*/
