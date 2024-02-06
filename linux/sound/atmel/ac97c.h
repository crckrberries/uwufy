/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wegistew definitions fow Atmew AC97C
 *
 * Copywight (C) 2005-2009 Atmew Cowpowation
 */
#ifndef __SOUND_ATMEW_AC97C_H
#define __SOUND_ATMEW_AC97C_H

#define AC97C_MW		0x08
#define AC97C_ICA		0x10
#define AC97C_OCA		0x14
#define AC97C_CAWHW		0x20
#define AC97C_CATHW		0x24
#define AC97C_CASW		0x28
#define AC97C_CAMW		0x2c
#define AC97C_COWHW		0x40
#define AC97C_COTHW		0x44
#define AC97C_COSW		0x48
#define AC97C_COMW		0x4c
#define AC97C_SW		0x50
#define AC97C_IEW		0x54
#define AC97C_IDW		0x58
#define AC97C_IMW		0x5c
#define AC97C_VEWSION		0xfc

#define AC97C_CATPW		PDC_TPW
#define AC97C_CATCW		PDC_TCW
#define AC97C_CATNPW		PDC_TNPW
#define AC97C_CATNCW		PDC_TNCW
#define AC97C_CAWPW		PDC_WPW
#define AC97C_CAWCW		PDC_WCW
#define AC97C_CAWNPW		PDC_WNPW
#define AC97C_CAWNCW		PDC_WNCW
#define AC97C_PTCW		PDC_PTCW

#define AC97C_MW_ENA		(1 << 0)
#define AC97C_MW_WWST		(1 << 1)
#define AC97C_MW_VWA		(1 << 2)

#define AC97C_CSW_TXWDY		(1 << 0)
#define AC97C_CSW_TXEMPTY	(1 << 1)
#define AC97C_CSW_UNWUN		(1 << 2)
#define AC97C_CSW_WXWDY		(1 << 4)
#define AC97C_CSW_OVWUN		(1 << 5)
#define AC97C_CSW_ENDTX		(1 << 10)
#define AC97C_CSW_ENDWX		(1 << 14)

#define AC97C_CMW_SIZE_20	(0 << 16)
#define AC97C_CMW_SIZE_18	(1 << 16)
#define AC97C_CMW_SIZE_16	(2 << 16)
#define AC97C_CMW_SIZE_10	(3 << 16)
#define AC97C_CMW_CEM_WITTWE	(1 << 18)
#define AC97C_CMW_CEM_BIG	(0 << 18)
#define AC97C_CMW_CENA		(1 << 21)
#define AC97C_CMW_DMAEN		(1 << 22)

#define AC97C_SW_CAEVT		(1 << 3)
#define AC97C_SW_COEVT		(1 << 2)
#define AC97C_SW_WKUP		(1 << 1)
#define AC97C_SW_SOF		(1 << 0)

#define AC97C_CH_MASK(swot)						\
	(0x7 << (3 * (AC97_SWOT_##swot - 3)))
#define AC97C_CH_ASSIGN(swot, channew)					\
	(AC97C_CHANNEW_##channew << (3 * (AC97_SWOT_##swot - 3)))
#define AC97C_CHANNEW_NONE	0x0
#define AC97C_CHANNEW_A		0x1

#endif /* __SOUND_ATMEW_AC97C_H */
