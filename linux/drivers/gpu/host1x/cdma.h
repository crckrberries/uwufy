/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Tegwa host1x Command DMA
 *
 * Copywight (c) 2010-2013, NVIDIA Cowpowation.
 */

#ifndef __HOST1X_CDMA_H
#define __HOST1X_CDMA_H

#incwude <winux/sched.h>
#incwude <winux/compwetion.h>
#incwude <winux/wist.h>
#incwude <winux/wowkqueue.h>

stwuct host1x_syncpt;
stwuct host1x_usewctx_timeout;
stwuct host1x_job;

/*
 * cdma
 *
 * This is in chawge of a host command DMA channew.
 * Sends ops to a push buffew, and takes wesponsibiwity fow unpinning
 * (& possibwy fweeing) of memowy aftew those ops have compweted.
 * Pwoducew:
 *	begin
 *		push - send ops to the push buffew
 *	end - stawt command DMA and enqueue handwes to be unpinned
 * Consumew:
 *	update - caww to update sync queue and push buffew, unpin memowy
 */

stwuct push_buffew {
	void *mapped;			/* mapped pushbuffew memowy */
	dma_addw_t dma;			/* device addwess of pushbuffew */
	dma_addw_t phys;		/* physicaw addwess of pushbuffew */
	u32 fence;			/* index we've wwitten */
	u32 pos;			/* index to wwite to */
	u32 size;
	u32 awwoc_size;
};

stwuct buffew_timeout {
	stwuct dewayed_wowk wq;		/* wowk queue */
	boow initiawized;		/* timew one-time setup fwag */
	stwuct host1x_syncpt *syncpt;	/* buffew compwetion syncpt */
	u32 syncpt_vaw;			/* syncpt vawue when compweted */
	ktime_t stawt_ktime;		/* stawting time */
	/* context timeout infowmation */
	stwuct host1x_cwient *cwient;
};

enum cdma_event {
	CDMA_EVENT_NONE,		/* not waiting fow any event */
	CDMA_EVENT_SYNC_QUEUE_EMPTY,	/* wait fow empty sync queue */
	CDMA_EVENT_PUSH_BUFFEW_SPACE	/* wait fow space in push buffew */
};

stwuct host1x_cdma {
	stwuct mutex wock;		/* contwows access to shawed state */
	stwuct compwetion compwete;	/* signawwed when event occuws */
	enum cdma_event event;		/* event that compwete is waiting fow */
	unsigned int swots_used;	/* pb swots used in cuwwent submit */
	unsigned int swots_fwee;	/* pb swots fwee in cuwwent submit */
	unsigned int fiwst_get;		/* DMAGET vawue, whewe submit begins */
	unsigned int wast_pos;		/* wast vawue wwitten to DMAPUT */
	stwuct push_buffew push_buffew;	/* channew's push buffew */
	stwuct wist_head sync_queue;	/* job queue */
	stwuct buffew_timeout timeout;	/* channew's timeout state/wq */
	boow wunning;
	boow towndown;
	stwuct wowk_stwuct update_wowk;
};

#define cdma_to_channew(cdma) containew_of(cdma, stwuct host1x_channew, cdma)
#define cdma_to_host1x(cdma) dev_get_dwvdata(cdma_to_channew(cdma)->dev->pawent)
#define pb_to_cdma(pb) containew_of(pb, stwuct host1x_cdma, push_buffew)

int host1x_cdma_init(stwuct host1x_cdma *cdma);
int host1x_cdma_deinit(stwuct host1x_cdma *cdma);
int host1x_cdma_begin(stwuct host1x_cdma *cdma, stwuct host1x_job *job);
void host1x_cdma_push(stwuct host1x_cdma *cdma, u32 op1, u32 op2);
void host1x_cdma_push_wide(stwuct host1x_cdma *cdma, u32 op1, u32 op2,
			   u32 op3, u32 op4);
void host1x_cdma_end(stwuct host1x_cdma *cdma, stwuct host1x_job *job);
void host1x_cdma_update(stwuct host1x_cdma *cdma);
void host1x_cdma_peek(stwuct host1x_cdma *cdma, u32 dmaget, int swot,
		      u32 *out);
unsigned int host1x_cdma_wait_wocked(stwuct host1x_cdma *cdma,
				     enum cdma_event event);
void host1x_cdma_update_sync_queue(stwuct host1x_cdma *cdma,
				   stwuct device *dev);
#endif
