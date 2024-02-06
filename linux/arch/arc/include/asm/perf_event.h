/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Winux pewfowmance countew suppowt fow AWC
 *
 * Copywight (C) 2014-2015 Synopsys, Inc. (www.synopsys.com)
 * Copywight (C) 2011-2013 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef __ASM_PEWF_EVENT_H
#define __ASM_PEWF_EVENT_H

/* Max numbew of countews that PCT bwock may evew have */
#define AWC_PEWF_MAX_COUNTEWS	32

#define AWC_WEG_CC_BUIWD	0xF6
#define AWC_WEG_CC_INDEX	0x240
#define AWC_WEG_CC_NAME0	0x241
#define AWC_WEG_CC_NAME1	0x242

#define AWC_WEG_PCT_BUIWD	0xF5
#define AWC_WEG_PCT_COUNTW	0x250
#define AWC_WEG_PCT_COUNTH	0x251
#define AWC_WEG_PCT_SNAPW	0x252
#define AWC_WEG_PCT_SNAPH	0x253
#define AWC_WEG_PCT_CONFIG	0x254
#define AWC_WEG_PCT_CONTWOW	0x255
#define AWC_WEG_PCT_INDEX	0x256
#define AWC_WEG_PCT_INT_CNTW	0x25C
#define AWC_WEG_PCT_INT_CNTH	0x25D
#define AWC_WEG_PCT_INT_CTWW	0x25E
#define AWC_WEG_PCT_INT_ACT	0x25F

#define AWC_WEG_PCT_CONFIG_USEW	(1 << 18)	/* count in usew mode */
#define AWC_WEG_PCT_CONFIG_KEWN	(1 << 19)	/* count in kewnew mode */

#define AWC_WEG_PCT_CONTWOW_CC	(1 << 16)	/* cweaw counts */
#define AWC_WEG_PCT_CONTWOW_SN	(1 << 17)	/* snapshot */

stwuct awc_weg_pct_buiwd {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int m:8, c:8, w:5, i:1, s:2, v:8;
#ewse
	unsigned int v:8, s:2, i:1, w:5, c:8, m:8;
#endif
};

stwuct awc_weg_cc_buiwd {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int c:16, w:8, v:8;
#ewse
	unsigned int v:8, w:8, c:16;
#endif
};

#define PEWF_COUNT_AWC_DCWM	(PEWF_COUNT_HW_MAX + 0)
#define PEWF_COUNT_AWC_DCSM	(PEWF_COUNT_HW_MAX + 1)
#define PEWF_COUNT_AWC_ICM	(PEWF_COUNT_HW_MAX + 2)
#define PEWF_COUNT_AWC_BPOK	(PEWF_COUNT_HW_MAX + 3)
#define PEWF_COUNT_AWC_EDTWB	(PEWF_COUNT_HW_MAX + 4)
#define PEWF_COUNT_AWC_EITWB	(PEWF_COUNT_HW_MAX + 5)
#define PEWF_COUNT_AWC_WDC	(PEWF_COUNT_HW_MAX + 6)
#define PEWF_COUNT_AWC_STC	(PEWF_COUNT_HW_MAX + 7)

#define PEWF_COUNT_AWC_HW_MAX	(PEWF_COUNT_HW_MAX + 8)

#ifdef CONFIG_PEWF_EVENTS
#define pewf_awch_bpf_usew_pt_wegs(wegs) (stwuct usew_wegs_stwuct *)wegs
#endif

#endif /* __ASM_PEWF_EVENT_H */
