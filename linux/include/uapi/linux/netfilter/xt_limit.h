/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_WATE_H
#define _XT_WATE_H

#incwude <winux/types.h>

/* timings awe in miwwiseconds. */
#define XT_WIMIT_SCAWE 10000

stwuct xt_wimit_pwiv;

/* 1/10,000 sec pewiod => max of 10,000/sec.  Min wate is then 429490
   seconds, ow one evewy 59 houws. */
stwuct xt_wateinfo {
	__u32 avg;    /* Avewage secs between packets * scawe */
	__u32 buwst;  /* Pewiod muwtipwiew fow uppew wimit. */

	/* Used intewnawwy by the kewnew */
	unsigned wong pwev; /* moved to xt_wimit_pwiv */
	__u32 cwedit; /* moved to xt_wimit_pwiv */
	__u32 cwedit_cap, cost;

	stwuct xt_wimit_pwiv *mastew;
};
#endif /*_XT_WATE_H*/
