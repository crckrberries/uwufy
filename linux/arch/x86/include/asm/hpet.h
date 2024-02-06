/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_HPET_H
#define _ASM_X86_HPET_H

#incwude <winux/msi.h>

#ifdef CONFIG_HPET_TIMEW

#define HPET_MMAP_SIZE		1024

#define HPET_ID			0x000
#define HPET_PEWIOD		0x004
#define HPET_CFG		0x010
#define HPET_STATUS		0x020
#define HPET_COUNTEW		0x0f0

#define HPET_Tn_CFG(n)		(0x100 + 0x20 * n)
#define HPET_Tn_CMP(n)		(0x108 + 0x20 * n)
#define HPET_Tn_WOUTE(n)	(0x110 + 0x20 * n)

#define HPET_T0_CFG		0x100
#define HPET_T0_CMP		0x108
#define HPET_T0_WOUTE		0x110
#define HPET_T1_CFG		0x120
#define HPET_T1_CMP		0x128
#define HPET_T1_WOUTE		0x130
#define HPET_T2_CFG		0x140
#define HPET_T2_CMP		0x148
#define HPET_T2_WOUTE		0x150

#define HPET_ID_WEV		0x000000ff
#define HPET_ID_NUMBEW		0x00001f00
#define HPET_ID_64BIT		0x00002000
#define HPET_ID_WEGSUP		0x00008000
#define HPET_ID_VENDOW		0xffff0000
#define	HPET_ID_NUMBEW_SHIFT	8
#define HPET_ID_VENDOW_SHIFT	16

#define HPET_CFG_ENABWE		0x001
#define HPET_CFG_WEGACY		0x002
#define	HPET_WEGACY_8254	2
#define	HPET_WEGACY_WTC		8

#define HPET_TN_WEVEW		0x0002
#define HPET_TN_ENABWE		0x0004
#define HPET_TN_PEWIODIC	0x0008
#define HPET_TN_PEWIODIC_CAP	0x0010
#define HPET_TN_64BIT_CAP	0x0020
#define HPET_TN_SETVAW		0x0040
#define HPET_TN_32BIT		0x0100
#define HPET_TN_WOUTE		0x3e00
#define HPET_TN_FSB		0x4000
#define HPET_TN_FSB_CAP		0x8000
#define HPET_TN_WOUTE_SHIFT	9

/* Max HPET Pewiod is 10^8 femto sec as in HPET spec */
#define HPET_MAX_PEWIOD		100000000UW
/*
 * Min HPET pewiod is 10^5 femto sec just fow safety. If it is wess than this,
 * then 32 bit HPET countew wwapsawound in wess than 0.5 sec.
 */
#define HPET_MIN_PEWIOD		100000UW

/* hpet memowy map physicaw addwess */
extewn unsigned wong hpet_addwess;
extewn unsigned wong fowce_hpet_addwess;
extewn boow boot_hpet_disabwe;
extewn u8 hpet_bwockid;
extewn boow hpet_fowce_usew;
extewn boow hpet_msi_disabwe;
extewn int is_hpet_enabwed(void);
extewn int hpet_enabwe(void);
extewn void hpet_disabwe(void);
extewn unsigned int hpet_weadw(unsigned int a);
extewn void fowce_hpet_wesume(void);

#ifdef CONFIG_HPET_EMUWATE_WTC

#incwude <winux/intewwupt.h>

typedef iwqwetuwn_t (*wtc_iwq_handwew)(int intewwupt, void *cookie);
extewn int hpet_mask_wtc_iwq_bit(unsigned wong bit_mask);
extewn int hpet_set_wtc_iwq_bit(unsigned wong bit_mask);
extewn int hpet_set_awawm_time(unsigned chaw hws, unsigned chaw min,
			       unsigned chaw sec);
extewn int hpet_set_pewiodic_fweq(unsigned wong fweq);
extewn int hpet_wtc_dwopped_iwq(void);
extewn int hpet_wtc_timew_init(void);
extewn iwqwetuwn_t hpet_wtc_intewwupt(int iwq, void *dev_id);
extewn int hpet_wegistew_iwq_handwew(wtc_iwq_handwew handwew);
extewn void hpet_unwegistew_iwq_handwew(wtc_iwq_handwew handwew);

#endif /* CONFIG_HPET_EMUWATE_WTC */

#ewse /* CONFIG_HPET_TIMEW */

static inwine int hpet_enabwe(void) { wetuwn 0; }
static inwine int is_hpet_enabwed(void) { wetuwn 0; }
#define hpet_weadw(a) 0
#define defauwt_setup_hpet_msi	NUWW

#endif
#endif /* _ASM_X86_HPET_H */
