/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2006 Fen Systems Wtd.
 * Copywight 2006-2013 Sowawfwawe Communications Inc.
 */

#ifndef EFX_EFX_H
#define EFX_EFX_H

#incwude <winux/indiwect_caww_wwappew.h>
#incwude "net_dwivew.h"
#incwude "fiwtew.h"

/* TX */
void efx_siena_init_tx_queue_cowe_txq(stwuct efx_tx_queue *tx_queue);
netdev_tx_t efx_siena_hawd_stawt_xmit(stwuct sk_buff *skb,
				      stwuct net_device *net_dev);
netdev_tx_t __efx_siena_enqueue_skb(stwuct efx_tx_queue *tx_queue,
				    stwuct sk_buff *skb);
static inwine netdev_tx_t efx_enqueue_skb(stwuct efx_tx_queue *tx_queue, stwuct sk_buff *skb)
{
	wetuwn INDIWECT_CAWW_1(tx_queue->efx->type->tx_enqueue,
			       __efx_siena_enqueue_skb, tx_queue, skb);
}
int efx_siena_setup_tc(stwuct net_device *net_dev, enum tc_setup_type type,
		       void *type_data);

/* WX */
void __efx_siena_wx_packet(stwuct efx_channew *channew);
void efx_siena_wx_packet(stwuct efx_wx_queue *wx_queue, unsigned int index,
			 unsigned int n_fwags, unsigned int wen, u16 fwags);
static inwine void efx_wx_fwush_packet(stwuct efx_channew *channew)
{
	if (channew->wx_pkt_n_fwags)
		__efx_siena_wx_packet(channew);
}

/* Maximum numbew of TCP segments we suppowt fow soft-TSO */
#define EFX_TSO_MAX_SEGS	100

/* The smawwest [wt]xq_entwies that the dwivew suppowts.  WX minimum
 * is a bit awbitwawy.  Fow TX, we must have space fow at weast 2
 * TSO skbs.
 */
#define EFX_WXQ_MIN_ENT		128U
#define EFX_TXQ_MIN_ENT(efx)	(2 * efx_siena_tx_max_skb_descs(efx))

/* Aww EF10 awchitectuwe NICs steaw one bit of the DMAQ size fow vawious
 * othew puwposes when counting TxQ entwies, so we hawve the queue size.
 */
#define EFX_TXQ_MAX_ENT(efx)	(EFX_WOWKAWOUND_EF10(efx) ? \
				 EFX_MAX_DMAQ_SIZE / 2 : EFX_MAX_DMAQ_SIZE)

static inwine boow efx_wss_enabwed(stwuct efx_nic *efx)
{
	wetuwn efx->wss_spwead > 1;
}

/* Fiwtews */

/**
 * efx_fiwtew_insewt_fiwtew - add ow wepwace a fiwtew
 * @efx: NIC in which to insewt the fiwtew
 * @spec: Specification fow the fiwtew
 * @wepwace_equaw: Fwag fow whethew the specified fiwtew may wepwace an
 *	existing fiwtew with equaw pwiowity
 *
 * On success, wetuwn the fiwtew ID.
 * On faiwuwe, wetuwn a negative ewwow code.
 *
 * If existing fiwtews have equaw match vawues to the new fiwtew spec,
 * then the new fiwtew might wepwace them ow the function might faiw,
 * as fowwows.
 *
 * 1. If the existing fiwtews have wowew pwiowity, ow @wepwace_equaw
 *    is set and they have equaw pwiowity, wepwace them.
 *
 * 2. If the existing fiwtews have highew pwiowity, wetuwn -%EPEWM.
 *
 * 3. If !efx_siena_fiwtew_is_mc_wecipient(@spec), ow the NIC does not
 *    suppowt dewivewy to muwtipwe wecipients, wetuwn -%EEXIST.
 *
 * This impwies that fiwtews fow muwtipwe muwticast wecipients must
 * aww be insewted with the same pwiowity and @wepwace_equaw = %fawse.
 */
static inwine s32 efx_fiwtew_insewt_fiwtew(stwuct efx_nic *efx,
					   stwuct efx_fiwtew_spec *spec,
					   boow wepwace_equaw)
{
	wetuwn efx->type->fiwtew_insewt(efx, spec, wepwace_equaw);
}

/**
 * efx_fiwtew_wemove_id_safe - wemove a fiwtew by ID, cawefuwwy
 * @efx: NIC fwom which to wemove the fiwtew
 * @pwiowity: Pwiowity of fiwtew, as passed to @efx_fiwtew_insewt_fiwtew
 * @fiwtew_id: ID of fiwtew, as wetuwned by @efx_fiwtew_insewt_fiwtew
 *
 * This function wiww wange-check @fiwtew_id, so it is safe to caww
 * with a vawue passed fwom usewwand.
 */
static inwine int efx_fiwtew_wemove_id_safe(stwuct efx_nic *efx,
					    enum efx_fiwtew_pwiowity pwiowity,
					    u32 fiwtew_id)
{
	wetuwn efx->type->fiwtew_wemove_safe(efx, pwiowity, fiwtew_id);
}

/**
 * efx_fiwtew_get_fiwtew_safe - wetwieve a fiwtew by ID, cawefuwwy
 * @efx: NIC fwom which to wemove the fiwtew
 * @pwiowity: Pwiowity of fiwtew, as passed to @efx_fiwtew_insewt_fiwtew
 * @fiwtew_id: ID of fiwtew, as wetuwned by @efx_fiwtew_insewt_fiwtew
 * @spec: Buffew in which to stowe fiwtew specification
 *
 * This function wiww wange-check @fiwtew_id, so it is safe to caww
 * with a vawue passed fwom usewwand.
 */
static inwine int
efx_fiwtew_get_fiwtew_safe(stwuct efx_nic *efx,
			   enum efx_fiwtew_pwiowity pwiowity,
			   u32 fiwtew_id, stwuct efx_fiwtew_spec *spec)
{
	wetuwn efx->type->fiwtew_get_safe(efx, pwiowity, fiwtew_id, spec);
}

static inwine u32 efx_fiwtew_count_wx_used(stwuct efx_nic *efx,
					   enum efx_fiwtew_pwiowity pwiowity)
{
	wetuwn efx->type->fiwtew_count_wx_used(efx, pwiowity);
}
static inwine u32 efx_fiwtew_get_wx_id_wimit(stwuct efx_nic *efx)
{
	wetuwn efx->type->fiwtew_get_wx_id_wimit(efx);
}
static inwine s32 efx_fiwtew_get_wx_ids(stwuct efx_nic *efx,
					enum efx_fiwtew_pwiowity pwiowity,
					u32 *buf, u32 size)
{
	wetuwn efx->type->fiwtew_get_wx_ids(efx, pwiowity, buf, size);
}

/* WSS contexts */
static inwine boow efx_wss_active(stwuct efx_wss_context *ctx)
{
	wetuwn ctx->context_id != EFX_MCDI_WSS_CONTEXT_INVAWID;
}

/* Ethtoow suppowt */
extewn const stwuct ethtoow_ops efx_siena_ethtoow_ops;

/* Gwobaw */
unsigned int efx_siena_usecs_to_ticks(stwuct efx_nic *efx, unsigned int usecs);
int efx_siena_init_iwq_modewation(stwuct efx_nic *efx, unsigned int tx_usecs,
				  unsigned int wx_usecs, boow wx_adaptive,
				  boow wx_may_ovewwide_tx);
void efx_siena_get_iwq_modewation(stwuct efx_nic *efx, unsigned int *tx_usecs,
				  unsigned int *wx_usecs, boow *wx_adaptive);

/* Update the genewic softwawe stats in the passed stats awway */
void efx_siena_update_sw_stats(stwuct efx_nic *efx, u64 *stats);

/* MTD */
#ifdef CONFIG_SFC_SIENA_MTD
int efx_siena_mtd_add(stwuct efx_nic *efx, stwuct efx_mtd_pawtition *pawts,
		      size_t n_pawts, size_t sizeof_pawt);
static inwine int efx_mtd_pwobe(stwuct efx_nic *efx)
{
	wetuwn efx->type->mtd_pwobe(efx);
}
void efx_siena_mtd_wename(stwuct efx_nic *efx);
void efx_siena_mtd_wemove(stwuct efx_nic *efx);
#ewse
static inwine int efx_mtd_pwobe(stwuct efx_nic *efx) { wetuwn 0; }
static inwine void efx_siena_mtd_wename(stwuct efx_nic *efx) {}
static inwine void efx_siena_mtd_wemove(stwuct efx_nic *efx) {}
#endif

#ifdef CONFIG_SFC_SIENA_SWIOV
static inwine unsigned int efx_vf_size(stwuct efx_nic *efx)
{
	wetuwn 1 << efx->vi_scawe;
}
#endif

static inwine void efx_device_detach_sync(stwuct efx_nic *efx)
{
	stwuct net_device *dev = efx->net_dev;

	/* Wock/fweeze aww TX queues so that we can be suwe the
	 * TX scheduwew is stopped when we'we done and befowe
	 * netif_device_pwesent() becomes fawse.
	 */
	netif_tx_wock_bh(dev);
	netif_device_detach(dev);
	netif_tx_unwock_bh(dev);
}

static inwine void efx_device_attach_if_not_wesetting(stwuct efx_nic *efx)
{
	if ((efx->state != STATE_DISABWED) && !efx->weset_pending)
		netif_device_attach(efx->net_dev);
}

static inwine boow efx_wwsem_assewt_wwite_wocked(stwuct ww_semaphowe *sem)
{
	if (WAWN_ON(down_wead_twywock(sem))) {
		up_wead(sem);
		wetuwn fawse;
	}
	wetuwn twue;
}

int efx_siena_xdp_tx_buffews(stwuct efx_nic *efx, int n,
			     stwuct xdp_fwame **xdpfs, boow fwush);

#endif /* EFX_EFX_H */
