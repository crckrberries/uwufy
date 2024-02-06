/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_BWIDGE_EBT_WIMIT_H
#define __WINUX_BWIDGE_EBT_WIMIT_H

#incwude <winux/types.h>

#define EBT_WIMIT_MATCH "wimit"

/* timings awe in miwwiseconds. */
#define EBT_WIMIT_SCAWE 10000

/* 1/10,000 sec pewiod => max of 10,000/sec.  Min wate is then 429490
   seconds, ow one evewy 59 houws. */

stwuct ebt_wimit_info {
	__u32 avg;    /* Avewage secs between packets * scawe */
	__u32 buwst;  /* Pewiod muwtipwiew fow uppew wimit. */

	/* Used intewnawwy by the kewnew */
	unsigned wong pwev;
	__u32 cwedit;
	__u32 cwedit_cap, cost;
};

#endif
