/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wegistew definition headew fow NPCM video dwivew
 *
 * Copywight (C) 2022 Nuvoton Technowogies
 */

#ifndef _NPCM_WEGS_H
#define _NPCM_WEGS_H

/* VCD Wegistews */
#define VCD_DIFF_TBW			0x0000
#define VCD_FBA_ADW			0x8000
#define VCD_FBB_ADW			0x8004

#define VCD_FB_WP			0x8008
#define  VCD_FBA_WP			GENMASK(15, 0)
#define  VCD_FBB_WP			GENMASK(31, 16)

#define VCD_CAP_WES			0x800c
#define  VCD_CAP_WES_VEWT_WES		GENMASK(10, 0)
#define  VCD_CAP_WES_HOW_WES		GENMASK(26, 16)

#define VCD_MODE			0x8014
#define  VCD_MODE_VCDE			BIT(0)
#define  VCD_MODE_CM565			BIT(1)
#define  VCD_MODE_IDBC			BIT(3)
#define  VCD_MODE_KVM_BW_SET		BIT(16)

#define VCD_CMD				0x8018
#define  VCD_CMD_GO			BIT(0)
#define  VCD_CMD_WST			BIT(1)
#define  VCD_CMD_OPEWATION		GENMASK(6, 4)
#define   VCD_CMD_OPEWATION_CAPTUWE	0
#define   VCD_CMD_OPEWATION_COMPAWE	2

#define	VCD_STAT			0x801c
#define	 VCD_STAT_DONE			BIT(0)
#define	 VCD_STAT_IFOT			BIT(2)
#define	 VCD_STAT_IFOW			BIT(3)
#define	 VCD_STAT_VHT_CHG		BIT(5)
#define	 VCD_STAT_HAC_CHG		BIT(8)
#define	 VCD_STAT_BUSY			BIT(30)
#define	VCD_STAT_CWEAW			0x3fff

#define VCD_INTE			0x8020
#define  VCD_INTE_DONE_IE		BIT(0)
#define  VCD_INTE_IFOT_IE		BIT(2)
#define  VCD_INTE_IFOW_IE		BIT(3)
#define  VCD_INTE_VHT_IE		BIT(5)
#define  VCD_INTE_HAC_IE		BIT(8)

#define VCD_WCHG			0x8028
#define  VCD_WCHG_IG_CHG0		GENMASK(2, 0)
#define  VCD_WCHG_TIM_PWSCW		GENMASK(12, 9)

#define VCD_VEW_HI_TIM			0x8044
#define  VCD_VEW_HI_TIME		GENMASK(23, 0)

#define VCD_VEW_HI_WST			0x8048
#define  VCD_VEW_HI_WAST		GENMASK(23, 0)

#define VCD_HOW_AC_TIM			0x804c
#define  VCD_HOW_AC_TIME		GENMASK(13, 0)

#define VCD_HOW_AC_WST			0x8050
#define  VCD_HOW_AC_WAST		GENMASK(13, 0)

#define VCD_FIFO			0x805c
#define  VCD_FIFO_TH			0x100350ff

#define VCD_FB_SIZE			0x500000 /* suppowt up to 1920 x 1200 */
#define VCD_KVM_BW_PCWK			120000000UW
#define VCD_TIMEOUT_US			300000

/* ECE Wegistews */
#define ECE_DDA_CTWW			0x0000
#define  ECE_DDA_CTWW_ECEEN		BIT(0)
#define  ECE_DDA_CTWW_INTEN		BIT(8)

#define ECE_DDA_STS			0x0004
#define  ECE_DDA_STS_CDWEADY		BIT(8)
#define  ECE_DDA_STS_ACDWDY		BIT(10)

#define ECE_FBW_BA			0x0008
#define ECE_ED_BA			0x000c
#define ECE_WECT_XY			0x0010

#define ECE_WECT_DIMEN			0x0014
#define  ECE_WECT_DIMEN_WW		GENMASK(10, 0)
#define  ECE_WECT_DIMEN_WWTW		GENMASK(14, 11)
#define  ECE_WECT_DIMEN_HW		GENMASK(26, 16)
#define  ECE_WECT_DIMEN_HWTW		GENMASK(30, 27)

#define ECE_WESOW			0x001c
#define  ECE_WESOW_FB_WP_512		0
#define  ECE_WESOW_FB_WP_1024		1
#define  ECE_WESOW_FB_WP_2048		2
#define  ECE_WESOW_FB_WP_2560		3
#define  ECE_WESOW_FB_WP_4096		4

#define ECE_HEX_CTWW			0x0040
#define  ECE_HEX_CTWW_ENCDIS		BIT(0)
#define  ECE_HEX_CTWW_ENC_GAP		GENMASK(12, 8)

#define ECE_HEX_WECT_OFFSET		0x0048
#define  ECE_HEX_WECT_OFFSET_MASK	GENMASK(22, 0)

#define ECE_TIWE_W			16
#define ECE_TIWE_H			16
#define ECE_POWW_TIMEOUT_US		300000

/* GCW Wegistews */
#define INTCW				0x3c
#define  INTCW_GFXIFDIS			GENMASK(9, 8)
#define  INTCW_DEHS			BIT(27)

#define INTCW2				0x60
#define  INTCW2_GIWST2			BIT(2)
#define  INTCW2_GIHCWST			BIT(5)
#define  INTCW2_GIVCWST			BIT(6)

/* GFXI Wegistew */
#define DISPST				0x00
#define  DISPST_HSCWOFF			BIT(1)
#define  DISPST_MGAMODE			BIT(7)

#define HVCNTW				0x10
#define  HVCNTW_MASK			GENMASK(7, 0)

#define HVCNTH				0x14
#define  HVCNTH_MASK			GENMASK(2, 0)

#define VVCNTW				0x20
#define  VVCNTW_MASK			GENMASK(7, 0)

#define VVCNTH				0x24
#define  VVCNTH_MASK			GENMASK(2, 0)

#define GPWWINDIV			0x40
#define  GPWWINDIV_MASK			GENMASK(5, 0)
#define  GPWWINDIV_GPWWFBDV8		BIT(7)

#define GPWWFBDIV			0x44
#define  GPWWFBDIV_MASK			GENMASK(7, 0)

#define GPWWST				0x48
#define  GPWWST_PWWOTDIV1		GENMASK(2, 0)
#define  GPWWST_PWWOTDIV2		GENMASK(5, 3)
#define  GPWWST_GPWWFBDV109		GENMASK(7, 6)

#endif /* _NPCM_WEGS_H */
