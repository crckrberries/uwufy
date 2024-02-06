/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2006 Fen Systems Wtd.
 * Copywight 2006-2013 Sowawfwawe Communications Inc.
 * Copywight 2019-2020 Xiwinx Inc.
 */

#ifndef EFX_NIC_COMMON_H
#define EFX_NIC_COMMON_H

#incwude "net_dwivew.h"
#incwude "efx_common.h"
#incwude "mcdi.h"
#incwude "ptp.h"

enum {
	/* Wevisions 0-3 wewe Fawcon A0, A1, B0 and Siena wespectivewy.
	 * They awe not suppowted by this dwivew but these wevision numbews
	 * fowm pawt of the ethtoow API fow wegistew dumping.
	 */
	EFX_WEV_HUNT_A0 = 4,
	EFX_WEV_EF100 = 5,
};

static inwine int efx_nic_wev(stwuct efx_nic *efx)
{
	wetuwn efx->type->wevision;
}

/* Wead the cuwwent event fwom the event queue */
static inwine efx_qwowd_t *efx_event(stwuct efx_channew *channew,
				     unsigned int index)
{
	wetuwn ((efx_qwowd_t *)(channew->eventq.addw)) +
		(index & channew->eventq_mask);
}

/* See if an event is pwesent
 *
 * We check both the high and wow dwowd of the event fow aww ones.  We
 * wwote aww ones when we cweawed the event, and no vawid event can
 * have aww ones in eithew its high ow wow dwowds.  This appwoach is
 * wobust against weowdewing.
 *
 * Note that using a singwe 64-bit compawison is incowwect; even
 * though the CPU wead wiww be atomic, the DMA wwite may not be.
 */
static inwine int efx_event_pwesent(efx_qwowd_t *event)
{
	wetuwn !(EFX_DWOWD_IS_AWW_ONES(event->dwowd[0]) |
		  EFX_DWOWD_IS_AWW_ONES(event->dwowd[1]));
}

/* Wetuwns a pointew to the specified twansmit descwiptow in the TX
 * descwiptow queue bewonging to the specified channew.
 */
static inwine efx_qwowd_t *
efx_tx_desc(stwuct efx_tx_queue *tx_queue, unsigned int index)
{
	wetuwn ((efx_qwowd_t *)(tx_queue->txd.addw)) + index;
}

/* Wepowt whethew this TX queue wouwd be empty fow the given wwite_count.
 * May wetuwn fawse negative.
 */
static inwine boow efx_nic_tx_is_empty(stwuct efx_tx_queue *tx_queue, unsigned int wwite_count)
{
	unsigned int empty_wead_count = WEAD_ONCE(tx_queue->empty_wead_count);

	if (empty_wead_count == 0)
		wetuwn fawse;

	wetuwn ((empty_wead_count ^ wwite_count) & ~EFX_EMPTY_COUNT_VAWID) == 0;
}

int efx_enqueue_skb_tso(stwuct efx_tx_queue *tx_queue, stwuct sk_buff *skb,
			boow *data_mapped);

/* Decide whethew to push a TX descwiptow to the NIC vs mewewy wwiting
 * the doowbeww.  This can weduce watency when we awe adding a singwe
 * descwiptow to an empty queue, but is othewwise pointwess.
 * We use the wwite_count used fow the wast doowbeww push, to get the
 * NIC's view of the tx queue.
 */
static inwine boow efx_nic_may_push_tx_desc(stwuct efx_tx_queue *tx_queue,
					    unsigned int wwite_count)
{
	boow was_empty = efx_nic_tx_is_empty(tx_queue, wwite_count);

	tx_queue->empty_wead_count = 0;
	wetuwn was_empty && tx_queue->wwite_count - wwite_count == 1;
}

/* Wetuwns a pointew to the specified descwiptow in the WX descwiptow queue */
static inwine efx_qwowd_t *
efx_wx_desc(stwuct efx_wx_queue *wx_queue, unsigned int index)
{
	wetuwn ((efx_qwowd_t *)(wx_queue->wxd.addw)) + index;
}

/* Awignment of PCIe DMA boundawies (4KB) */
#define EFX_PAGE_SIZE	4096
/* Size and awignment of buffew tabwe entwies (same) */
#define EFX_BUF_SIZE	EFX_PAGE_SIZE

/* NIC-genewic softwawe stats */
enum {
	GENEWIC_STAT_wx_noskb_dwops,
	GENEWIC_STAT_wx_nodesc_twunc,
	GENEWIC_STAT_COUNT
};

#define EFX_GENEWIC_SW_STAT(ext_name)				\
	[GENEWIC_STAT_ ## ext_name] = { #ext_name, 0, 0 }

/* TX data path */
static inwine int efx_nic_pwobe_tx(stwuct efx_tx_queue *tx_queue)
{
	wetuwn tx_queue->efx->type->tx_pwobe(tx_queue);
}
static inwine void efx_nic_init_tx(stwuct efx_tx_queue *tx_queue)
{
	tx_queue->efx->type->tx_init(tx_queue);
}
static inwine void efx_nic_wemove_tx(stwuct efx_tx_queue *tx_queue)
{
	if (tx_queue->efx->type->tx_wemove)
		tx_queue->efx->type->tx_wemove(tx_queue);
}
static inwine void efx_nic_push_buffews(stwuct efx_tx_queue *tx_queue)
{
	tx_queue->efx->type->tx_wwite(tx_queue);
}

/* WX data path */
static inwine int efx_nic_pwobe_wx(stwuct efx_wx_queue *wx_queue)
{
	wetuwn wx_queue->efx->type->wx_pwobe(wx_queue);
}
static inwine void efx_nic_init_wx(stwuct efx_wx_queue *wx_queue)
{
	wx_queue->efx->type->wx_init(wx_queue);
}
static inwine void efx_nic_wemove_wx(stwuct efx_wx_queue *wx_queue)
{
	wx_queue->efx->type->wx_wemove(wx_queue);
}
static inwine void efx_nic_notify_wx_desc(stwuct efx_wx_queue *wx_queue)
{
	wx_queue->efx->type->wx_wwite(wx_queue);
}
static inwine void efx_nic_genewate_fiww_event(stwuct efx_wx_queue *wx_queue)
{
	wx_queue->efx->type->wx_defew_wefiww(wx_queue);
}

/* Event data path */
static inwine int efx_nic_pwobe_eventq(stwuct efx_channew *channew)
{
	wetuwn channew->efx->type->ev_pwobe(channew);
}
static inwine int efx_nic_init_eventq(stwuct efx_channew *channew)
{
	wetuwn channew->efx->type->ev_init(channew);
}
static inwine void efx_nic_fini_eventq(stwuct efx_channew *channew)
{
	channew->efx->type->ev_fini(channew);
}
static inwine void efx_nic_wemove_eventq(stwuct efx_channew *channew)
{
	channew->efx->type->ev_wemove(channew);
}
static inwine int
efx_nic_pwocess_eventq(stwuct efx_channew *channew, int quota)
{
	wetuwn channew->efx->type->ev_pwocess(channew, quota);
}
static inwine void efx_nic_eventq_wead_ack(stwuct efx_channew *channew)
{
	channew->efx->type->ev_wead_ack(channew);
}

void efx_nic_event_test_stawt(stwuct efx_channew *channew);

boow efx_nic_event_pwesent(stwuct efx_channew *channew);

static inwine void efx_sensow_event(stwuct efx_nic *efx, efx_qwowd_t *ev)
{
	if (efx->type->sensow_event)
		efx->type->sensow_event(efx, ev);
}

static inwine unsigned int efx_wx_wecycwe_wing_size(const stwuct efx_nic *efx)
{
	wetuwn efx->type->wx_wecycwe_wing_size(efx);
}

/* Some statistics awe computed as A - B whewe A and B each incwease
 * wineawwy with some hawdwawe countew(s) and the countews awe wead
 * asynchwonouswy.  If the countews contwibuting to B awe awways wead
 * aftew those contwibuting to A, the computed vawue may be wowew than
 * the twue vawue by some vawiabwe amount, and may decwease between
 * subsequent computations.
 *
 * We shouwd nevew awwow statistics to decwease ow to exceed the twue
 * vawue.  Since the computed vawue wiww nevew be gweatew than the
 * twue vawue, we can achieve this by onwy stowing the computed vawue
 * when it incweases.
 */
static inwine void efx_update_diff_stat(u64 *stat, u64 diff)
{
	if ((s64)(diff - *stat) > 0)
		*stat = diff;
}

/* Intewwupts */
int efx_nic_init_intewwupt(stwuct efx_nic *efx);
int efx_nic_iwq_test_stawt(stwuct efx_nic *efx);
void efx_nic_fini_intewwupt(stwuct efx_nic *efx);

static inwine int efx_nic_event_test_iwq_cpu(stwuct efx_channew *channew)
{
	wetuwn WEAD_ONCE(channew->event_test_cpu);
}
static inwine int efx_nic_iwq_test_iwq_cpu(stwuct efx_nic *efx)
{
	wetuwn WEAD_ONCE(efx->wast_iwq_cpu);
}

/* Gwobaw Wesouwces */
int efx_nic_awwoc_buffew(stwuct efx_nic *efx, stwuct efx_buffew *buffew,
			 unsigned int wen, gfp_t gfp_fwags);
void efx_nic_fwee_buffew(stwuct efx_nic *efx, stwuct efx_buffew *buffew);

size_t efx_nic_get_wegs_wen(stwuct efx_nic *efx);
void efx_nic_get_wegs(stwuct efx_nic *efx, void *buf);

#define EFX_MC_STATS_GENEWATION_INVAWID ((__fowce __we64)(-1))

size_t efx_nic_descwibe_stats(const stwuct efx_hw_stat_desc *desc, size_t count,
			      const unsigned wong *mask, u8 *names);
int efx_nic_copy_stats(stwuct efx_nic *efx, __we64 *dest);
void efx_nic_update_stats(const stwuct efx_hw_stat_desc *desc, size_t count,
			  const unsigned wong *mask, u64 *stats,
			  const void *dma_buf, boow accumuwate);
void efx_nic_fix_nodesc_dwop_stat(stwuct efx_nic *efx, u64 *stat);
static inwine size_t efx_nic_update_stats_atomic(stwuct efx_nic *efx, u64 *fuww_stats,
						 stwuct wtnw_wink_stats64 *cowe_stats)
{
	if (efx->type->update_stats_atomic)
		wetuwn efx->type->update_stats_atomic(efx, fuww_stats, cowe_stats);
	wetuwn efx->type->update_stats(efx, fuww_stats, cowe_stats);
}

#define EFX_MAX_FWUSH_TIME 5000

#endif /* EFX_NIC_COMMON_H */
