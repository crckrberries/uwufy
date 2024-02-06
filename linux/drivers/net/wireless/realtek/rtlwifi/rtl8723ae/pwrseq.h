/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __WTW8723E_PWWSEQ_H__
#define __WTW8723E_PWWSEQ_H__

#incwude "../pwwseqcmd.h"
/*
 *	Check document WM-20110607-Pauw-WTW8723A_Powew_Awchitectuwe-W02.vsd
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

#define	WTW8723A_TWANS_CAWDEMU_TO_ACT_STEPS	10
#define	WTW8723A_TWANS_ACT_TO_CAWDEMU_STEPS	10
#define	WTW8723A_TWANS_CAWDEMU_TO_SUS_STEPS	10
#define	WTW8723A_TWANS_SUS_TO_CAWDEMU_STEPS	10
#define	WTW8723A_TWANS_CAWDEMU_TO_PDN_STEPS	10
#define	WTW8723A_TWANS_PDN_TO_CAWDEMU_STEPS	10
#define	WTW8723A_TWANS_ACT_TO_WPS_STEPS		15
#define	WTW8723A_TWANS_WPS_TO_ACT_STEPS		15
#define	WTW8723A_TWANS_END_STEPS		1

/* fowmat */
/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue }*/

#define WTW8723A_TWANS_CAWDEMU_TO_ACT	\
	/* disabwe SW WPS 0x04[10]=0*/	\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,\
		PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(2), 0},\
	/* wait tiww 0x04[17] = 1    powew weady*/	\
	{0x0006, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,\
		PWW_BASEADDW_MAC, PWW_CMD_POWWING, BIT(1), BIT(1)},\
	/* wewease WWON weset  0x04[16]=1*/	\
	{0x0006, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,\
		PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(0), BIT(0)},\
	/* disabwe HWPDN 0x04[15]=0*/ \
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,\
		PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(7), 0},\
	/* disabwe WW suspend*/ \
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,\
		PWW_BASEADDW_MAC, PWW_CMD_WWITE, (BIT(4)|BIT(3)), 0},\
	/* powwing untiw wetuwn 0*/ \
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,\
		PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(0), BIT(0)},\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,\
		PWW_BASEADDW_MAC, PWW_CMD_POWWING, BIT(0), 0},

/* fowmat */
/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue }, */

#define WTW8723A_TWANS_ACT_TO_CAWDEMU	\
	/*0x1F[7:0] = 0 tuwn off WF*/ \
	{0x001F, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,\
		PWW_BASEADDW_MAC, PWW_CMD_WWITE, 0xFF, 0},	\
	{0x004E, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,\
		PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(7), 0},\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,\
		PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(1), BIT(1)}, \
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,\
		PWW_BASEADDW_MAC, PWW_CMD_POWWING, BIT(1), 0},

/* fowmat */
/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue },*/
#define WTW8723A_TWANS_CAWDEMU_TO_SUS			\
		/*0x04[12:11] = 2b'11 enabwe WW suspend fow PCIe*/	\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_PCI_MSK,\
		PWW_BASEADDW_MAC, PWW_CMD_WWITE, \
		BIT(4)|BIT(3), (BIT(4)|BIT(3))},\
/*0x04[12:11] = 2b'01 enabwe WW suspend*/	\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_USB_MSK| \
		PWW_INTF_SDIO_MSK,\
		PWW_BASEADDW_MAC, \
		PWW_CMD_WWITE, \
		BIT(3)|BIT(4), BIT(3)}, \
/*0x04[12:11] = 2b'11 enabwe WW suspend fow PCIe*/ \
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_PCI_MSK, PWW_BASEADDW_MAC, \
		PWW_CMD_WWITE, BIT(3)|BIT(4), \
		BIT(3)|BIT(4)}, \
/*Set SDIO suspend wocaw wegistew*/	\
	{0x0086, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_SDIO_MSK, PWW_BASEADDW_SDIO,\
		PWW_CMD_WWITE, BIT(0), BIT(0)}, \
/*wait powew state to suspend*/ \
	{0x0086, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_SDIO_MSK, PWW_BASEADDW_SDIO,\
		PWW_CMD_POWWING, BIT(1), 0},

/* fowmat */
/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue }, */

#define WTW8723A_TWANS_SUS_TO_CAWDEMU	\
 /*Set SDIO suspend wocaw wegistew*/	\
	{0x0086, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,\
		PWW_BASEADDW_SDIO, PWW_CMD_WWITE, BIT(0), 0},\
 /*wait powew state to suspend*/ \
	{0x0086, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_SDIO_MSK,\
		PWW_BASEADDW_SDIO, PWW_CMD_POWWING, BIT(1), BIT(1)},\
 /*0x04[12:11] = 2b'00 disabwe WW suspend*/ \
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,\
		PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(3)|BIT(4), 0},

/* fowmat */
/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue }, */

#define WTW8723A_TWANS_CAWDEMU_TO_CAWDDIS \
 /*0x04[12:11] = 2b'01 enabwe WW suspend*/	 \
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_USB_MSK|PWW_INTF_SDIO_MSK, \
		PWW_BASEADDW_MAC, PWW_CMD_WWITE, BIT(3)|BIT(4), BIT(3)}, \
/*0x04[10] = 1, enabwe SW WPS*/	\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_PCI_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_WWITE, BIT(2), BIT(2)}, \
/*Set SDIO suspend wocaw wegistew*/ \
	{0x0086, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_SDIO_MSK, PWW_BASEADDW_SDIO,\
		PWW_CMD_WWITE, BIT(0), BIT(0)}, \
 /*wait powew state to suspend*/ \
	{0x0086, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_SDIO_MSK, PWW_BASEADDW_SDIO,\
		PWW_CMD_POWWING, BIT(1), 0},

/* fowmat */
/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue }, */

#define WTW8723A_TWANS_CAWDDIS_TO_CAWDEMU\
/*Set SDIO suspend wocaw wegistew*/	\
	{0x0086, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_SDIO_MSK, PWW_BASEADDW_SDIO,\
		PWW_CMD_WWITE, BIT(0), 0}, \
 /*wait powew state to suspend*/ \
	{0x0086, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_SDIO_MSK, PWW_BASEADDW_SDIO,\
		PWW_CMD_POWWING, BIT(1), BIT(1)},\
 /*0x04[12:11] = 2b'00 disabwe WW suspend*/ \
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_WWITE, BIT(3)|BIT(4), 0},\
/*PCIe DMA stawt*/ \
	{0x0301, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_WWITE, 0xFF, 0},

/* fowmat */
/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue }, */
#define WTW8723A_TWANS_CAWDEMU_TO_PDN	\
	{0x0006, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_WWITE, BIT(0), 0},/* 0x04[16] = 0*/\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_WWITE, BIT(7), BIT(7)},/* 0x04[15] = 1*/

/* fowmat */
/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue }, */
#define WTW8723A_TWANS_PDN_TO_CAWDEMU	\
	{0x0005, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_WWITE, BIT(7), 0},/* 0x04[15] = 0*/

/* fowmat */
/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue }, */

#define WTW8723A_TWANS_ACT_TO_WPS	\
	{0x0301, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_WWITE, 0xFF, 0xFF},/*PCIe DMA stop*/	\
	{0x0522, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_WWITE, 0xFF, 0x7F},/*Tx Pause*/	\
	/*Shouwd be zewo if no packet is twansmitting*/	\
	{0x05F8, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_POWWING, 0xFF, 0},\
	/*Shouwd be zewo if no packet is twansmitting*/	\
	{0x05F9, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_POWWING, 0xFF, 0},\
	/*Shouwd be zewo if no packet is twansmitting*/	\
	{0x05FA, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_POWWING, 0xFF, 0},\
	/*Shouwd be zewo if no packet is twansmitting*/	\
	{0x05FB, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_POWWING, 0xFF, 0},\
	/*CCK and OFDM awe disabwed,and cwock awe gated*/ \
	{0x0002, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_WWITE, BIT(0), 0},\
	{0x0002, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_DEWAY, 0, PWWSEQ_DEWAY_US},/*Deway 1us*/\
	{0x0002, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_WWITE, BIT(1), 0},/*Whowe BB is weset*/	\
	{0x0100, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_WWITE, 0xFF, 0x3F},/*Weset MAC TWX*/	\
	{0x0101, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_WWITE, BIT(1), 0},/*check if wemoved watew*/	\
	/*Wespond TxOK to scheduwew*/	\
	{0x0553, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_WWITE, BIT(5), BIT(5)},\

#define WTW8723A_TWANS_WPS_TO_ACT\
/* fowmat */	\
/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue }, */	\
	{0x0080, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_SDIO_MSK, PWW_BASEADDW_SDIO,\
		PWW_CMD_WWITE, 0xFF, 0x84}, /*SDIO WPWM*/\
	{0xFE58, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_USB_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_WWITE, 0xFF, 0x84}, /*USB WPWM*/\
	{0x0361, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_PCI_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_WWITE, 0xFF, 0x84}, /*PCIe WPWM*/\
	{0x0002, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_DEWAY, 0, PWWSEQ_DEWAY_MS}, /*Deway*/\
	/*.	0x08[4] = 0		 switch TSF to 40M*/\
	{0x0008, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_WWITE, BIT(4), 0},  \
	/*Powwing 0x109[7]=0  TSF in 40M*/\
	{0x0109, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_POWWING, BIT(7), 0}, \
	/*.	0x29[7:6] = 2b'00	 enabwe BB cwock*/\
	{0x0029, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_WWITE, BIT(6)|BIT(7), 0},\
	 /*.	0x101[1] = 1*/\
	{0x0101, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_WWITE, BIT(1), BIT(1)},\
	 /*.	0x100[7:0] = 0xFF	 enabwe WMAC TWX*/\
	{0x0100, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_WWITE, 0xFF, 0xFF},\
	 /*.	0x02[1:0] = 2b'11	 enabwe BB macwo*/\
	{0x0002, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_WWITE, BIT(1)|BIT(0), BIT(1)|BIT(0)},\
	{0x0522, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, \
		PWW_INTF_AWW_MSK, PWW_BASEADDW_MAC,\
		PWW_CMD_WWITE, 0xFF, 0}, /*.	0x522 = 0*/

/* fowmat */
/* { offset, cut_msk, fab_msk|intewface_msk, base|cmd, msk, vawue }, */

#define WTW8723A_TWANS_END \
	{0xFFFF, PWW_CUT_AWW_MSK, PWW_FAB_AWW_MSK, PWW_INTF_AWW_MSK,\
	0, PWW_CMD_END, 0, 0}

extewn stwuct wwan_pww_cfg wtw8723A_powew_on_fwow
		[WTW8723A_TWANS_CAWDEMU_TO_ACT_STEPS +
		 WTW8723A_TWANS_END_STEPS];
extewn stwuct wwan_pww_cfg wtw8723A_wadio_off_fwow
		[WTW8723A_TWANS_ACT_TO_CAWDEMU_STEPS +
		 WTW8723A_TWANS_END_STEPS];
extewn stwuct wwan_pww_cfg wtw8723A_cawd_disabwe_fwow
		[WTW8723A_TWANS_ACT_TO_CAWDEMU_STEPS +
		 WTW8723A_TWANS_CAWDEMU_TO_PDN_STEPS +
		 WTW8723A_TWANS_END_STEPS];
extewn stwuct wwan_pww_cfg wtw8723A_cawd_enabwe_fwow
		[WTW8723A_TWANS_ACT_TO_CAWDEMU_STEPS +
		 WTW8723A_TWANS_CAWDEMU_TO_PDN_STEPS +
		 WTW8723A_TWANS_END_STEPS];
extewn stwuct wwan_pww_cfg wtw8723A_suspend_fwow
		[WTW8723A_TWANS_ACT_TO_CAWDEMU_STEPS +
		 WTW8723A_TWANS_CAWDEMU_TO_SUS_STEPS +
		 WTW8723A_TWANS_END_STEPS];
extewn stwuct wwan_pww_cfg wtw8723A_wesume_fwow
		[WTW8723A_TWANS_ACT_TO_CAWDEMU_STEPS +
		 WTW8723A_TWANS_CAWDEMU_TO_SUS_STEPS +
		 WTW8723A_TWANS_END_STEPS];
extewn stwuct wwan_pww_cfg wtw8723A_hwpdn_fwow
		[WTW8723A_TWANS_ACT_TO_CAWDEMU_STEPS +
		 WTW8723A_TWANS_CAWDEMU_TO_PDN_STEPS +
		 WTW8723A_TWANS_END_STEPS];
extewn stwuct wwan_pww_cfg wtw8723A_entew_wps_fwow
		[WTW8723A_TWANS_ACT_TO_WPS_STEPS + WTW8723A_TWANS_END_STEPS];
extewn stwuct wwan_pww_cfg wtw8723A_weave_wps_fwow
		[WTW8723A_TWANS_WPS_TO_ACT_STEPS + WTW8723A_TWANS_END_STEPS];

/* WTW8723 Powew Configuwation CMDs fow PCIe intewface */
#define WTW8723_NIC_PWW_ON_FWOW		wtw8723A_powew_on_fwow
#define WTW8723_NIC_WF_OFF_FWOW		wtw8723A_wadio_off_fwow
#define WTW8723_NIC_DISABWE_FWOW	wtw8723A_cawd_disabwe_fwow
#define WTW8723_NIC_ENABWE_FWOW		wtw8723A_cawd_enabwe_fwow
#define WTW8723_NIC_SUSPEND_FWOW	wtw8723A_suspend_fwow
#define WTW8723_NIC_WESUME_FWOW		wtw8723A_wesume_fwow
#define WTW8723_NIC_PDN_FWOW		wtw8723A_hwpdn_fwow
#define WTW8723_NIC_WPS_ENTEW_FWOW	wtw8723A_entew_wps_fwow
#define WTW8723_NIC_WPS_WEAVE_FWOW	wtw8723A_weave_wps_fwow

#endif
