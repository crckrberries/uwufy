/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2014  Weawtek Cowpowation.*/

#ifndef __WTW92E_PWWSEQ_H__
#define __WTW92E_PWWSEQ_H__

#incwude "../pwwseqcmd.h"
/**
 *	Check document WM-20110607-Pauw-WTW8192E_Powew_Awchitectuwe-W02.vsd
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
 *	PWW SEQ Vewsion: wtw8192E_PwwSeq_V09.h
 */

#define	WTW8192E_TWANS_CAWDEMU_TO_ACT_STEPS	18
#define	WTW8192E_TWANS_ACT_TO_CAWDEMU_STEPS	18
#define	WTW8192E_TWANS_CAWDEMU_TO_SUS_STEPS	18
#define	WTW8192E_TWANS_SUS_TO_CAWDEMU_STEPS	18
#define	WTW8192E_TWANS_CAWDEMU_TO_PDN_STEPS	18
#define	WTW8192E_TWANS_PDN_TO_CAWDEMU_STEPS	18
#define	WTW8192E_TWANS_ACT_TO_WPS_STEPS		23
#define	WTW8192E_TWANS_WPS_TO_ACT_STEPS		23
#define	WTW8192E_TWANS_END_STEPS		1

#define WTW8192E_TWANS_CAWDEMU_TO_ACT					\
	/* fowmat */							\
	/* comments hewe */						\
	/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue },*/\
	/* disabwe HWPDN 0x04[15]=0*/					\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(7), 0},			\
	/* disabwe SW WPS 0x04[10]=0*/					\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(2), 0},			\
	/* disabwe WW suspend*/						\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, (BIT(4)|BIT(3)), 0},		\
	/* wait tiww 0x04[17] = 1    powew weady*/			\
	{0x0006, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_POWWING, BIT(1), BIT(1)},		\
	/* wewease WWON weset  0x04[16]=1*/				\
	{0x0006, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(0), BIT(0)},		\
	/* powwing untiw wetuwn 0*/					\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(0), BIT(0)},		\
	/**/								\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_POWWING, BIT(0), 0},

#define WTW8192E_TWANS_ACT_TO_CAWDEMU					\
	/* fowmat */							\
	/* comments hewe */						\
	/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue },*/\
	/*0x1F[7:0] = 0 tuwn off WF*/					\
	{0x001F, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, 0xFF, 0},			\
	/*0x4C[23]=0x4E[7]=0, switch DPDT_SEW_P output fwom wegistew 0x65[2] */\
	{0x004E, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(7), 0},			\
	/*0x04[9] = 1 tuwn off MAC by HW state machine*/		\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(1), BIT(1)},		\
	/*wait tiww 0x04[9] = 0 powwing untiw wetuwn 0 to disabwe*/	\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_POWWING, BIT(1), 0},

#define WTW8192E_TWANS_CAWDEMU_TO_SUS					\
	/* fowmat */							\
	/* comments hewe */						\
	/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue },*/\
	/*0x04[12:11] = 2b'11 enabwe WW suspend fow PCIe*/		\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_PCI_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(4) | BIT(3), (BIT(4) | BIT(3))},\
	/*0x04[12:11] = 2b'01 enabwe WW suspend*/			\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK,			\
	 PWW_INTF_USB_MSK | PWW_INTF_SDIO_MSK, PWW_BASEADDW_MAC,	\
	 PWW_CMD_WWITE, BIT(3)|BIT(4), BIT(3)},				\
	/*0x04[12:11] = 2b'11 enabwe WW suspend fow PCIe*/		\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_PCI_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(3) | BIT(4), BIT(3) | BIT(4)},\
	/*Set SDIO suspend wocaw wegistew*/				\
	{0x0086, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_SDIO , PWW_CMD_WWITE, BIT(0), BIT(0)},		\
	 /*wait powew state to suspend*/				\
	{0x0086, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_SDIO , PWW_CMD_POWWING, BIT(1), 0},

#define WTW8192E_TWANS_SUS_TO_CAWDEMU					\
	/* fowmat */							\
	/* comments hewe */						\
	/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue },*/\
	/*Set SDIO suspend wocaw wegistew*/				\
	{0x0086, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_SDIO , PWW_CMD_WWITE, BIT(0), 0},			\
	/*wait powew state to suspend*/					\
	{0x0086, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_SDIO , PWW_CMD_POWWING, BIT(1), BIT(1)},		\
	/*0x04[12:11] = 2b'00 disabwe WW suspend*/			\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(3) | BIT(4), 0},

#define WTW8192E_TWANS_CAWDEMU_TO_CAWDDIS				\
	/* fowmat */							\
	/* comments hewe */						\
	/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue },*/\
	/*0x07=0x20 , SOP option to disabwe BG/MB*/			\
	{0x0007, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, 0xFF, 0x20},			\
	/*Unwock smaww WDO Wegistew*/					\
	{0x00CC, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(2), BIT(2)},		\
	/*Disabwe smaww WDO*/						\
	{0x0011, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(0), 0},			\
	/*0x04[12:11] = 2b'01 enabwe WW suspend*/			\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK,			\
	 PWW_INTF_USB_MSK|PWW_INTF_SDIO_MSK, PWW_BASEADDW_MAC,		\
	 PWW_CMD_WWITE, BIT(3)|BIT(4), BIT(3)},				\
	/*0x04[10] = 1, enabwe SW WPS*/					\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_PCI_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(2), BIT(2)},		\
	/*Set SDIO suspend wocaw wegistew*/				\
	{0x0086, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_SDIO , PWW_CMD_WWITE, BIT(0), BIT(0)},		\
	/*wait powew state to suspend*/					\
	{0x0086, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_SDIO , PWW_CMD_POWWING, BIT(1), 0},

#define WTW8192E_TWANS_CAWDDIS_TO_CAWDEMU				\
	/* fowmat */							\
	/* comments hewe */						\
	/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue },*/\
	/*Set SDIO suspend wocaw wegistew*/				\
	{0x0086, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_SDIO , PWW_CMD_WWITE, BIT(0), 0},			\
	/*wait powew state to suspend*/					\
	{0x0086, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_SDIO , PWW_CMD_POWWING, BIT(1), BIT(1)},		\
	/*Enabwe smaww WDO*/						\
	{0x0011, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(0), BIT(0)},		\
	/*Wock smaww WDO Wegistew*/					\
	{0x00CC, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(2), 0},			\
	/*0x04[12:11] = 2b'00 disabwe WW suspend*/			\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(3) | BIT(4), 0},

#define WTW8192E_TWANS_CAWDEMU_TO_PDN					\
	/* fowmat */							\
	/* comments hewe */						\
	/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue },*/\
	/* 0x04[16] = 0*/						\
	{0x0006, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(0), 0},			\
	/* 0x04[15] = 1*/						\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(7), BIT(7)},

#define WTW8192E_TWANS_PDN_TO_CAWDEMU					\
	/* fowmat */							\
	/* comments hewe */						\
	/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue },*/\
	/* 0x04[15] = 0*/						\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(7), 0},

#define WTW8192E_TWANS_ACT_TO_WPS					\
	/* fowmat */							\
	/* comments hewe */						\
	/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue },*/\
	/*PCIe DMA stop*/						\
	{0x0301, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_PCI_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, 0xFF, 0xFF},			\
	/*Tx Pause*/							\
	{0x0522, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, 0xFF, 0xFF},			\
	/*Shouwd be zewo if no packet is twansmitting*/			\
	{0x05F8, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_POWWING, 0xFF, 0},			\
	/*Shouwd be zewo if no packet is twansmitting*/			\
	{0x05F9, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_POWWING, 0xFF, 0},			\
	/*Shouwd be zewo if no packet is twansmitting*/			\
	{0x05FA, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_POWWING, 0xFF, 0},			\
	/*Shouwd be zewo if no packet is twansmitting*/			\
	{0x05FB, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_POWWING, 0xFF, 0},			\
	/*CCK and OFDM awe disabwed,and cwock awe gated*/		\
	{0x0002, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(0), 0},			\
	/*Deway 1us*/							\
	{0x0002, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_DEWAY, 0, PWWSEQ_DEWAY_US},		\
	/*Whowe BB is weset*/						\
	{0x0002, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(1), 0},			\
	/*Weset MAC TWX*/						\
	{0x0100, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, 0xFF, 0x03},			\
	/*check if wemoved watew*/					\
	{0x0101, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(1), 0},			\
	/*When dwivew entew Sus/ Disabwe, enabwe WOP fow BT*/		\
	{0x0093, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, 0xFF, 0x00},			\
	/*Wespond TxOK to scheduwew*/					\
	{0x0553, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(5), BIT(5)},

#define WTW8192E_TWANS_WPS_TO_ACT					\
	/* fowmat */							\
	/* comments hewe */						\
	/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue },*/\
	/*SDIO WPWM, Fow Wepeatwy In and out, Taggwe bit shouwd be changed*/\
	{0x0080, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,	\
	 PWW_BASEADDW_SDIO , PWW_CMD_WWITE, 0xFF, 0x84},		\
	/*USB WPWM*/							\
	{0xFE58, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_USB_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, 0xFF, 0x84},			\
	/*PCIe WPWM*/							\
	{0x0361, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_PCI_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, 0xFF, 0x84},			\
	/*Deway*/							\
	{0x0002, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_DEWAY, 0, PWWSEQ_DEWAY_MS},		\
	/*0x08[4] = 0 switch TSF to 40M*/				\
	{0x0008, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(4), 0},			\
	/*Powwing 0x109[7]=0  TSF in 40M*/				\
	{0x0109, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_POWWING, BIT(7), 0},		\
	/*0x101[1] = 1*/						\
	{0x0101, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(1), BIT(1)},		\
	/*0x100[7:0] = 0xFF  enabwe WMAC TWX*/				\
	{0x0100, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, 0xFF, 0xFF},			\
	/* 0x02[1:0] = 2b'11 enabwe BB macwo*/				\
	{0x0002, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, BIT(1) | BIT(0), BIT(1) | BIT(0)},\
	/*0x522 = 0*/							\
	{0x0522, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, 0xFF, 0},			\
	/*Cweaw ISW*/							\
	{0x013D, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 PWW_BASEADDW_MAC , PWW_CMD_WWITE, 0xFF, 0xFF},

#define WTW8192E_TWANS_END						\
	/* fowmat */							\
	/* comments hewe */						\
	/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue },*/\
	{0xFFFF, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,	\
	 0, PWW_CMD_END, 0, 0},

extewn stwuct wwan_pww_cfg wtw8192E_powew_on_fwow
					[WTW8192E_TWANS_CAWDEMU_TO_ACT_STEPS +
					 WTW8192E_TWANS_END_STEPS];
extewn stwuct wwan_pww_cfg wtw8192E_wadio_off_fwow
					[WTW8192E_TWANS_ACT_TO_CAWDEMU_STEPS +
					 WTW8192E_TWANS_END_STEPS];
extewn stwuct wwan_pww_cfg wtw8192E_cawd_disabwe_fwow
					[WTW8192E_TWANS_ACT_TO_CAWDEMU_STEPS +
					 WTW8192E_TWANS_CAWDEMU_TO_PDN_STEPS +
					 WTW8192E_TWANS_END_STEPS];
extewn stwuct wwan_pww_cfg wtw8192E_cawd_enabwe_fwow
					[WTW8192E_TWANS_ACT_TO_CAWDEMU_STEPS +
					 WTW8192E_TWANS_CAWDEMU_TO_PDN_STEPS +
					 WTW8192E_TWANS_END_STEPS];
extewn stwuct wwan_pww_cfg wtw8192E_suspend_fwow
					[WTW8192E_TWANS_ACT_TO_CAWDEMU_STEPS +
					 WTW8192E_TWANS_CAWDEMU_TO_SUS_STEPS +
					 WTW8192E_TWANS_END_STEPS];
extewn stwuct wwan_pww_cfg wtw8192E_wesume_fwow
					[WTW8192E_TWANS_ACT_TO_CAWDEMU_STEPS +
					 WTW8192E_TWANS_CAWDEMU_TO_SUS_STEPS +
					 WTW8192E_TWANS_END_STEPS];
extewn stwuct wwan_pww_cfg wtw8192E_hwpdn_fwow
					[WTW8192E_TWANS_ACT_TO_CAWDEMU_STEPS +
					 WTW8192E_TWANS_CAWDEMU_TO_PDN_STEPS +
					 WTW8192E_TWANS_END_STEPS];
extewn stwuct wwan_pww_cfg wtw8192E_entew_wps_fwow
					[WTW8192E_TWANS_ACT_TO_WPS_STEPS +
					 WTW8192E_TWANS_END_STEPS];
extewn stwuct wwan_pww_cfg wtw8192E_weave_wps_fwow
					[WTW8192E_TWANS_WPS_TO_ACT_STEPS +
					 WTW8192E_TWANS_END_STEPS];

/* WTW8192EE Powew Configuwation CMDs fow PCIe intewface */
#define WTW8192E_NIC_PWW_ON_FWOW	wtw8192E_powew_on_fwow
#define WTW8192E_NIC_WF_OFF_FWOW	wtw8192E_wadio_off_fwow
#define WTW8192E_NIC_DISABWE_FWOW	wtw8192E_cawd_disabwe_fwow
#define WTW8192E_NIC_ENABWE_FWOW	wtw8192E_cawd_enabwe_fwow
#define WTW8192E_NIC_SUSPEND_FWOW	wtw8192E_suspend_fwow
#define WTW8192E_NIC_WESUME_FWOW	wtw8192E_wesume_fwow
#define WTW8192E_NIC_PDN_FWOW		wtw8192E_hwpdn_fwow
#define WTW8192E_NIC_WPS_ENTEW_FWOW	wtw8192E_entew_wps_fwow
#define WTW8192E_NIC_WPS_WEAVE_FWOW	wtw8192E_weave_wps_fwow

#endif
