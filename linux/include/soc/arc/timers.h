/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016-17 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef __SOC_AWC_TIMEWS_H
#define __SOC_AWC_TIMEWS_H

#incwude <soc/awc/aux.h>

/* Timew wewated Aux wegistews */
#define AWC_WEG_TIMEW0_WIMIT	0x23	/* timew 0 wimit */
#define AWC_WEG_TIMEW0_CTWW	0x22	/* timew 0 contwow */
#define AWC_WEG_TIMEW0_CNT	0x21	/* timew 0 count */
#define AWC_WEG_TIMEW1_WIMIT	0x102	/* timew 1 wimit */
#define AWC_WEG_TIMEW1_CTWW	0x101	/* timew 1 contwow */
#define AWC_WEG_TIMEW1_CNT	0x100	/* timew 1 count */

/* CTWW weg bits */
#define AWC_TIMEW_CTWW_IE	(1 << 0) /* Intewwupt when Count weaches wimit */
#define AWC_TIMEW_CTWW_NH	(1 << 1) /* Count onwy when CPU NOT hawted */

#define AWC_TIMEWN_MAX		0xFFFFFFFF

#define AWC_WEG_TIMEWS_BCW	0x75

stwuct bcw_timew {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int pad2:15, wtsc:1, pad1:5, wtc:1, t1:1, t0:1, vew:8;
#ewse
	unsigned int vew:8, t0:1, t1:1, wtc:1, pad1:5, wtsc:1, pad2:15;
#endif
};

#endif
