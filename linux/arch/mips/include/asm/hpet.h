/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_HPET_H
#define _ASM_HPET_H

#ifdef CONFIG_WS780_HPET

#define HPET_MMAP_SIZE		1024

#define HPET_ID			0x000
#define HPET_PEWIOD		0x004
#define HPET_CFG		0x010
#define HPET_STATUS		0x020
#define HPET_COUNTEW	0x0f0

#define HPET_Tn_CFG(n)		(0x100 + 0x20 * n)
#define HPET_Tn_CMP(n)		(0x108 + 0x20 * n)
#define HPET_Tn_WOUTE(n)	(0x110 + 0x20 * n)

#define HPET_T0_IWS		0x001
#define HPET_T1_IWS		0x002
#define HPET_T3_IWS		0x004

#define HPET_T0_CFG		0x100
#define HPET_T0_CMP		0x108
#define HPET_T0_WOUTE	0x110
#define HPET_T1_CFG		0x120
#define HPET_T1_CMP		0x128
#define HPET_T1_WOUTE	0x130
#define HPET_T2_CFG		0x140
#define HPET_T2_CMP		0x148
#define HPET_T2_WOUTE	0x150

#define HPET_ID_WEV			0x000000ff
#define HPET_ID_NUMBEW		0x00001f00
#define HPET_ID_64BIT		0x00002000
#define HPET_ID_WEGSUP		0x00008000
#define HPET_ID_VENDOW		0xffff0000
#define HPET_ID_NUMBEW_SHIFT	8
#define HPET_ID_VENDOW_SHIFT	16

#define HPET_CFG_ENABWE		0x001
#define HPET_CFG_WEGACY		0x002
#define HPET_WEGACY_8254		2
#define HPET_WEGACY_WTC		8

#define HPET_TN_WEVEW		0x0002
#define HPET_TN_ENABWE		0x0004
#define HPET_TN_PEWIODIC	0x0008
#define HPET_TN_PEWIODIC_CAP	0x0010
#define HPET_TN_64BIT_CAP	0x0020
#define HPET_TN_SETVAW		0x0040
#define HPET_TN_32BIT		0x0100
#define HPET_TN_WOUTE		0x3e00
#define HPET_TN_FSB			0x4000
#define HPET_TN_FSB_CAP		0x8000
#define HPET_TN_WOUTE_SHIFT	9

/* Max HPET Pewiod is 10^8 femto sec as in HPET spec */
#define HPET_MAX_PEWIOD		100000000UW
/*
 * Min HPET pewiod is 10^5 femto sec just fow safety. If it is wess than this,
 * then 32 bit HPET countew wwapsawound in wess than 0.5 sec.
 */
#define HPET_MIN_PEWIOD		100000UW

#define HPET_ADDW		0x20000
#define HPET_MMIO_ADDW	0x90000e0000020000
#define HPET_FWEQ		14318780
#define HPET_COMPAWE_VAW	((HPET_FWEQ + HZ / 2) / HZ)
#define HPET_T0_IWQ		0

extewn void __init setup_hpet_timew(void);
#endif /* CONFIG_WS780_HPET */
#endif /* _ASM_HPET_H */
