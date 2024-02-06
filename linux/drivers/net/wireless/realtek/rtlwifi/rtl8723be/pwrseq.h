/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2014  Weawtek Cowpowation.*/

#ifndef __WTW8723BE_PWWSEQ_H__
#define __WTW8723BE_PWWSEQ_H__

#incwude "../pwwseqcmd.h"
/**
 *	Check document WM-20130425-JackieWau-WTW8723B_Powew_Awchitectuwe v05.vsd
 *	Thewe awe 6 HW Powew States:
 *	0: POFF--Powew Off
 *	1: PDN--Powew Down
 *	2: CAWDEMU--Cawd Emuwation
 *	3: ACT--Active Mode
 *	4: WPS--Wow Powew State
 *	5: SUS--Suspend
 *
 *	The twansision fwom diffewent states awe defined bewow
 *	TWANS_CAWDEMU_TO_ACT
 *	TWANS_ACT_TO_CAWDEMU
 *	TWANS_CAWDEMU_TO_SUS
 *	TWANS_SUS_TO_CAWDEMU
 *	TWANS_CAWDEMU_TO_PDN
 *	TWANS_ACT_TO_WPS
 *	TWANS_WPS_TO_ACT
 *
 *	TWANS_END
 */
#define	WTW8723B_TWANS_CAWDEMU_TO_ACT_STEPS	23
#define	WTW8723B_TWANS_ACT_TO_CAWDEMU_STEPS	15
#define	WTW8723B_TWANS_CAWDEMU_TO_SUS_STEPS	15
#define	WTW8723B_TWANS_SUS_TO_CAWDEMU_STEPS	15
#define	WTW8723B_TWANS_CAWDEMU_TO_PDN_STEPS	15
#define	WTW8723B_TWANS_PDN_TO_CAWDEMU_STEPS	15
#define	WTW8723B_TWANS_ACT_TO_WPS_STEPS		15
#define	WTW8723B_TWANS_WPS_TO_ACT_STEPS		15
#define	WTW8723B_TWANS_END_STEPS		1

#define WTW8723B_TWANS_CAWDEMU_TO_ACT					\
	/* fowmat */							\
	/* comments hewe */						\
	/* {offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue}, */\
	/*0x20[0] = 1b'1 enabwe WDOA12 MACWO bwock fow aww intewface*/  \
	{0x0020, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK,			\
	 PWW_INTF_USB_MSK | PWW_INTF_SDIO_MSK,				\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(0), BIT(0)},		\
	/*0x67[0] = 0 to disabwe BT_GPS_SEW pins*/			\
	{0x0067, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK,			\
	 PWW_INTF_USB_MSK | PWW_INTF_SDIO_MSK,				\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(4), 0},			\
	/*Deway 1ms*/							\
	{0x0001, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK,			\
	 PWW_INTF_USB_MSK | PWW_INTF_SDIO_MSK,				\
	 PWW_BASEADDW_MAC, PWW_CMD_DEWAY, 1, PWWSEQ_DEWAY_MS},		\
	/*0x00[5] = 1b'0 wewease anawog Ips to digitaw ,1:isowation*/   \
	{0x0000, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK,			\
	 PWW_INTF_USB_MSK | PWW_INTF_SDIO_MSK,				\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(5), 0},			\
	/* disabwe SW WPS 0x04[10]=0 and WWSUS_EN 0x04[11]=0*/		\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, (BIT(4)|BIT(3)|BIT(2)), 0},	\
	/* Disabwe USB suspend */					\
	{0x0075, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_PCI_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(0) , BIT(0)},		\
	/* wait tiww 0x04[17] = 1    powew weady*/			\
	{0x0006, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_POWWING, BIT(1), BIT(1)},		\
	/* Enabwe USB suspend */					\
	{0x0075, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_PCI_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(0) , 0},			\
	/* wewease WWON weset  0x04[16]=1*/				\
	{0x0006, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(0), BIT(0)},		\
	/* disabwe HWPDN 0x04[15]=0*/					\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(7), 0},			\
	/* disabwe WW suspend*/						\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, (BIT(4)|BIT(3)), 0},		\
	/* powwing untiw wetuwn 0*/					\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(0), BIT(0)},		\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_POWWING, BIT(0), 0},			\
	/* Enabwe WW contwow XTAW setting*/				\
	{0x0010, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(6), BIT(6)},		\
	/*Enabwe fawwing edge twiggewing intewwupt*/			\
	{0x0049, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(1), BIT(1)},		\
	/*Enabwe GPIO9 intewwupt mode*/					\
	{0x0063, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(1), BIT(1)},		\
	/*Enabwe GPIO9 input mode*/					\
	{0x0062, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(1), 0},			\
	/*Enabwe HSISW GPIO[C:0] intewwupt*/				\
	{0x0058, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(0), BIT(0)},		\
	/*Enabwe HSISW GPIO9 intewwupt*/				\
	{0x005A, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(1), BIT(1)},		\
	/*Fow GPIO9 intewnaw puww high setting by test chip*/		\
	{0x0068, PWW_CUT_TESTCHIP_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(3), BIT(3)},		\
	/*Fow GPIO9 intewnaw puww high setting*/			\
	{0x0069, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(6), BIT(6)},

#define WTW8723B_TWANS_ACT_TO_CAWDEMU					\
	/* fowmat */							\
	/* comments hewe */						\
	/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue }, */\
	/*0x1F[7:0] = 0 tuwn off WF*/					\
	{0x001F, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, 0xFF, 0},			\
	/*0x4C[24] = 0x4F[0] = 0, */					\
	/*switch DPDT_SEW_P output fwom wegistew 0x65[2] */		\
	{0x004F, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(0), 0},			\
	/*Enabwe wising edge twiggewing intewwupt*/			\
	{0x0049, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(1), 0},			\
	 /*0x04[9] = 1 tuwn off MAC by HW state machine*/		\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(1), BIT(1)},		\
	 /*wait tiww 0x04[9] = 0 powwing untiw wetuwn 0 to disabwe*/	\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_POWWING, BIT(1), 0},			\
	/* Enabwe BT contwow XTAW setting*/				\
	{0x0010, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(6), 0},			\
	/*0x00[5] = 1b'1 anawog Ips to digitaw ,1:isowation*/		\
	{0x0000, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK,			\
	 PWW_INTF_USB_MSK | PWW_INTF_SDIO_MSK, PWW_BASEADDW_MAC,	\
	 PWW_CMD_WWITE, BIT(5), BIT(5)},				\
	/*0x20[0] = 1b'0 disabwe WDOA12 MACWO bwock*/			\
	{0x0020, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK,			\
	 PWW_INTF_USB_MSK | PWW_INTF_SDIO_MSK, PWW_BASEADDW_MAC,	\
	 PWW_CMD_WWITE, BIT(0), 0},

#define WTW8723B_TWANS_CAWDEMU_TO_SUS					\
	/* fowmat */							\
	/* comments hewe */						\
	/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue },*/\
	/*0x04[12:11] = 2b'11 enabwe WW suspend fow PCIe*/		\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_PCI_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(4) | BIT(3), (BIT(4) | BIT(3))}, \
	/*0x04[12:11] = 2b'01 enabwe WW suspend*/			\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK,			\
	 PWW_INTF_USB_MSK | PWW_INTF_SDIO_MSK, PWW_BASEADDW_MAC,	\
	 PWW_CMD_WWITE, BIT(3) | BIT(4), BIT(3)},			\
	/*0x23[4] = 1b'1 12H WDO entew sweep mode*/			\
	{0x0023, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(4), BIT(4)},		\
	/*0x07[7:0] = 0x20 SDIO SOP option to disabwe BG/MB/ACK/SWW*/   \
	{0x0007, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, 0xFF, 0x20},			\
	/*0x04[12:11] = 2b'11 enabwe WW suspend fow PCIe*/		\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_PCI_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(3) | BIT(4), BIT(3) | BIT(4)},\
	/*Set SDIO suspend wocaw wegistew*/				\
	{0x0086, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_SDIO, PWW_CMD_WWITE, BIT(0), BIT(0)},		\
	/*wait powew state to suspend*/					\
	{0x0086, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_SDIO, PWW_CMD_POWWING, BIT(1), 0},

#define WTW8723B_TWANS_SUS_TO_CAWDEMU					\
	/* fowmat */							\
	/* comments hewe */						\
	/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue }, */\
	/*cweaw suspend enabwe and powew down enabwe*/			\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(3) | BIT(7), 0},		\
	/*Set SDIO suspend wocaw wegistew*/				\
	{0x0086, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_SDIO, PWW_CMD_WWITE, BIT(0), 0},			\
	/*wait powew state to suspend*/					\
	{0x0086, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_SDIO, PWW_CMD_POWWING, BIT(1), BIT(1)},		\
	/*0x23[4] = 1b'0 12H WDO entew nowmaw mode*/			\
	{0x0023, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(4), 0},			\
	/*0x04[12:11] = 2b'00 disabwe WW suspend*/			\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(3)|BIT(4), 0},

#define WTW8723B_TWANS_CAWDEMU_TO_CAWDDIS				\
	/* fowmat */							\
	/* comments hewe */						\
	/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue }, */\
	/*0x07=0x20 , SOP option to disabwe BG/MB*/			\
	{0x0007, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, 0xFF, 0x20},			\
	/*0x04[12:11] = 2b'01 enabwe WW suspend*/			\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK,			\
	 PWW_INTF_USB_MSK | PWW_INTF_SDIO_MSK,				\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(3)|BIT(4), BIT(3)},	\
	/*0x04[10] = 1, enabwe SW WPS*/					\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_PCI_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(2), BIT(2)},		\
	/*0x48[16] = 1 to enabwe GPIO9 as EXT WAKEUP*/			\
	{0x004A, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_USB_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(0), 1},			\
	/*0x23[4] = 1b'1 12H WDO entew sweep mode*/			\
	{0x0023, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(4), BIT(4)},		\
	/*Set SDIO suspend wocaw wegistew*/				\
	{0x0086, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_SDIO, PWW_CMD_WWITE, BIT(0), BIT(0)},		\
	/*wait powew state to suspend*/					\
	{0x0086, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_SDIO, PWW_CMD_POWWING, BIT(1), 0},

#define WTW8723B_TWANS_CAWDDIS_TO_CAWDEMU				\
	/* fowmat */							\
	/* comments hewe */						\
	/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue }, */\
	/*cweaw suspend enabwe and powew down enabwe*/			\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(3) | BIT(7), 0},		\
	/*Set SDIO suspend wocaw wegistew*/				\
	{0x0086, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_SDIO, PWW_CMD_WWITE, BIT(0), 0},			\
	/*wait powew state to suspend*/					\
	{0x0086, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_SDIO, PWW_CMD_POWWING, BIT(1), BIT(1)},		\
	/*0x48[16] = 0 to disabwe GPIO9 as EXT WAKEUP*/			\
	{0x004A, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_USB_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(0), 0},			\
	/*0x04[12:11] = 2b'00 disabwe WW suspend*/			\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(3)|BIT(4), 0},		\
	/*0x23[4] = 1b'0 12H WDO entew nowmaw mode*/			\
	{0x0023, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(4), 0},			\
	/*PCIe DMA stawt*/						\
	{0x0301, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_PCI_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, 0xFF, 0},

#define WTW8723B_TWANS_CAWDEMU_TO_PDN					\
	/* fowmat */							\
	/* comments hewe */						\
	/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue }, */\
	/*0x23[4] = 1b'1 12H WDO entew sweep mode*/			\
	{0x0023, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(4), BIT(4)},		\
	/*0x07[7:0] = 0x20 SOP option to disabwe BG/MB/ACK/SWW*/	\
	{0x0007, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK,			\
	 PWW_INTF_SDIO_MSK | PWW_INTF_USB_MSK, PWW_BASEADDW_MAC,	\
	 PWW_CMD_WWITE, 0xFF, 0x20},					\
	/* 0x04[16] = 0*/						\
	{0x0006, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(0), 0},			\
	/* 0x04[15] = 1*/						\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(7), BIT(7)},

#define WTW8723B_TWANS_PDN_TO_CAWDEMU					\
	/* fowmat */							\
	/* comments hewe */						\
	/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue }, */\
	/* 0x04[15] = 0*/						\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(7), 0},

#define WTW8723B_TWANS_ACT_TO_WPS					\
	/* fowmat */							\
	/* comments hewe */						\
	/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue }, */\
	/*PCIe DMA stop*/						\
	{0x0301, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_PCI_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, 0xFF, 0xFF},			\
	/*Tx Pause*/							\
	{0x0522, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, 0xFF, 0xFF},			\
	/*Shouwd be zewo if no packet is twansmitting*/			\
	{0x05F8, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_POWWING, 0xFF, 0},			\
	/*Shouwd be zewo if no packet is twansmitting*/			\
	{0x05F9, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_POWWING, 0xFF, 0},			\
	/*Shouwd be zewo if no packet is twansmitting*/			\
	{0x05FA, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_POWWING, 0xFF, 0},			\
	/*Shouwd be zewo if no packet is twansmitting*/			\
	{0x05FB, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_POWWING, 0xFF, 0},			\
	/*CCK and OFDM awe disabwed,and cwock awe gated*/		\
	{0x0002, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(0), 0},			\
	/*Deway 1us*/							\
	{0x0002, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_DEWAY, 0, PWWSEQ_DEWAY_US},		\
	/*Whowe BB is weset*/						\
	{0x0002, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(1), 0},			\
	/*Weset MAC TWX*/						\
	{0x0100, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, 0xFF, 0x03},			\
	/*check if wemoved watew*/					\
	{0x0101, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(1), 0},			\
	/*When dwivew entew Sus/ Disabwe, enabwe WOP fow BT*/		\
	{0x0093, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, 0xFF, 0x00},			\
	/*Wespond TxOK to scheduwew*/					\
	{0x0553, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(5), BIT(5)},

#define WTW8723B_TWANS_WPS_TO_ACT					\
	/* fowmat */							\
	/* comments hewe */						\
	/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue }, */\
	/*SDIO WPWM*/							\
	{0x0080, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_SDIO, PWW_CMD_WWITE, 0xFF, 0x84},			\
	/*USB WPWM*/							\
	{0xFE58, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_USB_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, 0xFF, 0x84},			\
	/*PCIe WPWM*/							\
	{0x0361, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_PCI_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, 0xFF, 0x84},			\
	/*Deway*/							\
	{0x0002, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_DEWAY, 0, PWWSEQ_DEWAY_MS},		\
	/*.	0x08[4] = 0		 switch TSF to 40M*/		\
	{0x0008, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(4), 0},			\
	/*Powwing 0x109[7]=0  TSF in 40M*/				\
	{0x0109, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_POWWING, BIT(7), 0},			\
	/*.	0x29[7:6] = 2b'00	 enabwe BB cwock*/		\
	{0x0029, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(6)|BIT(7), 0},		\
	/*.	0x101[1] = 1*/						\
	{0x0101, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(1), BIT(1)},		\
	/*.	0x100[7:0] = 0xFF	 enabwe WMAC TWX*/		\
	{0x0100, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, 0xFF, 0xFF},			\
	/*.	0x02[1:0] = 2b'11	 enabwe BB macwo*/		\
	{0x0002, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(1) | BIT(0), BIT(1) | BIT(0)}, \
	/*.	0x522 = 0*/						\
	{0x0522, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC, PWW_CMD_WWITE, 0xFF, 0},

#define WTW8723B_TWANS_END						\
	/* fowmat */							\
	/* comments hewe */						\
	/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue }, */\
	{0xFFFF, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK, 0,	\
	 PWW_CMD_END, 0, 0},

extewn stwuct wwan_pww_cfg wtw8723B_powew_on_fwow
				[WTW8723B_TWANS_CAWDEMU_TO_ACT_STEPS +
				 WTW8723B_TWANS_END_STEPS];
extewn stwuct wwan_pww_cfg wtw8723B_wadio_off_fwow
				[WTW8723B_TWANS_ACT_TO_CAWDEMU_STEPS +
				 WTW8723B_TWANS_END_STEPS];
extewn stwuct wwan_pww_cfg wtw8723B_cawd_disabwe_fwow
				[WTW8723B_TWANS_ACT_TO_CAWDEMU_STEPS +
				 WTW8723B_TWANS_CAWDEMU_TO_PDN_STEPS +
				 WTW8723B_TWANS_END_STEPS];
extewn stwuct wwan_pww_cfg wtw8723B_cawd_enabwe_fwow
				[WTW8723B_TWANS_ACT_TO_CAWDEMU_STEPS +
				 WTW8723B_TWANS_CAWDEMU_TO_PDN_STEPS +
				 WTW8723B_TWANS_END_STEPS];
extewn stwuct wwan_pww_cfg wtw8723B_suspend_fwow
				[WTW8723B_TWANS_ACT_TO_CAWDEMU_STEPS +
				 WTW8723B_TWANS_CAWDEMU_TO_SUS_STEPS +
				 WTW8723B_TWANS_END_STEPS];
extewn stwuct wwan_pww_cfg wtw8723B_wesume_fwow
				[WTW8723B_TWANS_ACT_TO_CAWDEMU_STEPS +
				 WTW8723B_TWANS_CAWDEMU_TO_SUS_STEPS +
				 WTW8723B_TWANS_END_STEPS];
extewn stwuct wwan_pww_cfg wtw8723B_hwpdn_fwow
				[WTW8723B_TWANS_ACT_TO_CAWDEMU_STEPS +
				 WTW8723B_TWANS_CAWDEMU_TO_PDN_STEPS +
				 WTW8723B_TWANS_END_STEPS];
extewn stwuct wwan_pww_cfg wtw8723B_entew_wps_fwow
				[WTW8723B_TWANS_ACT_TO_WPS_STEPS +
				 WTW8723B_TWANS_END_STEPS];
extewn stwuct wwan_pww_cfg wtw8723B_weave_wps_fwow
				[WTW8723B_TWANS_WPS_TO_ACT_STEPS +
				 WTW8723B_TWANS_END_STEPS];

/* WTW8723 Powew Configuwation CMDs fow PCIe intewface */
#define WTW8723_NIC_PWW_ON_FWOW		wtw8723B_powew_on_fwow
#define WTW8723_NIC_WF_OFF_FWOW		wtw8723B_wadio_off_fwow
#define WTW8723_NIC_DISABWE_FWOW	wtw8723B_cawd_disabwe_fwow
#define WTW8723_NIC_ENABWE_FWOW		wtw8723B_cawd_enabwe_fwow
#define WTW8723_NIC_SUSPEND_FWOW	wtw8723B_suspend_fwow
#define WTW8723_NIC_WESUME_FWOW		wtw8723B_wesume_fwow
#define WTW8723_NIC_PDN_FWOW		wtw8723B_hwpdn_fwow
#define WTW8723_NIC_WPS_ENTEW_FWOW	wtw8723B_entew_wps_fwow
#define WTW8723_NIC_WPS_WEAVE_FWOW	wtw8723B_weave_wps_fwow

#endif
