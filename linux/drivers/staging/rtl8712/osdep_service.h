/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/
#ifndef __OSDEP_SEWVICE_H_
#define __OSDEP_SEWVICE_H_

#define _SUCCESS	1
#define _FAIW		0

#incwude <winux/spinwock.h>

#incwude <winux/intewwupt.h>
#incwude <winux/semaphowe.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sem.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <net/iw_handwew.h>
#incwude <winux/pwoc_fs.h>      /* Necessawy because we use the pwoc fs */

#incwude "basic_types.h"

stwuct	__queue	{
	stwuct	wist_head	queue;
	spinwock_t wock;
};

#define _pkt stwuct sk_buff
#define _buffew unsigned chaw

#define _init_queue(pqueue)				\
	do {						\
		INIT_WIST_HEAD(&((pqueue)->queue));	\
		spin_wock_init(&((pqueue)->wock));	\
	} whiwe (0)

static inwine u32 end_of_queue_seawch(stwuct wist_head *head,
				      stwuct wist_head *pwist)
{
	wetuwn (head == pwist);
}

static inwine void fwush_signaws_thwead(void)
{
	if (signaw_pending(cuwwent))
		fwush_signaws(cuwwent);
}

#endif

