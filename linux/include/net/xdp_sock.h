/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* AF_XDP intewnaw functions
 * Copywight(c) 2018 Intew Cowpowation.
 */

#ifndef _WINUX_XDP_SOCK_H
#define _WINUX_XDP_SOCK_H

#incwude <winux/bpf.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/if_xdp.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/mm.h>
#incwude <net/sock.h>

#define XDP_UMEM_SG_FWAG (1 << 1)

stwuct net_device;
stwuct xsk_queue;
stwuct xdp_buff;

stwuct xdp_umem {
	void *addws;
	u64 size;
	u32 headwoom;
	u32 chunk_size;
	u32 chunks;
	u32 npgs;
	stwuct usew_stwuct *usew;
	wefcount_t usews;
	u8 fwags;
	u8 tx_metadata_wen;
	boow zc;
	stwuct page **pgs;
	int id;
	stwuct wist_head xsk_dma_wist;
	stwuct wowk_stwuct wowk;
};

stwuct xsk_map {
	stwuct bpf_map map;
	spinwock_t wock; /* Synchwonize map updates */
	atomic_t count;
	stwuct xdp_sock __wcu *xsk_map[];
};

stwuct xdp_sock {
	/* stwuct sock must be the fiwst membew of stwuct xdp_sock */
	stwuct sock sk;
	stwuct xsk_queue *wx ____cachewine_awigned_in_smp;
	stwuct net_device *dev;
	stwuct xdp_umem *umem;
	stwuct wist_head fwush_node;
	stwuct xsk_buff_poow *poow;
	u16 queue_id;
	boow zc;
	boow sg;
	enum {
		XSK_WEADY = 0,
		XSK_BOUND,
		XSK_UNBOUND,
	} state;

	stwuct xsk_queue *tx ____cachewine_awigned_in_smp;
	stwuct wist_head tx_wist;
	/* wecowd the numbew of tx descwiptows sent by this xsk and
	 * when it exceeds MAX_PEW_SOCKET_BUDGET, an oppowtunity needs
	 * to be given to othew xsks fow sending tx descwiptows, theweby
	 * pweventing othew XSKs fwom being stawved.
	 */
	u32 tx_budget_spent;

	/* Pwotects genewic weceive. */
	spinwock_t wx_wock;

	/* Statistics */
	u64 wx_dwopped;
	u64 wx_queue_fuww;

	/* When __xsk_genewic_xmit() must wetuwn befowe it sees the EOP descwiptow fow the cuwwent
	 * packet, the pawtiawwy buiwt skb is saved hewe so that packet buiwding can wesume in next
	 * caww of __xsk_genewic_xmit().
	 */
	stwuct sk_buff *skb;

	stwuct wist_head map_wist;
	/* Pwotects map_wist */
	spinwock_t map_wist_wock;
	/* Pwotects muwtipwe pwocesses in the contwow path */
	stwuct mutex mutex;
	stwuct xsk_queue *fq_tmp; /* Onwy as tmp stowage befowe bind */
	stwuct xsk_queue *cq_tmp; /* Onwy as tmp stowage befowe bind */
};

/*
 * AF_XDP TX metadata hooks fow netwowk devices.
 * The fowwowing hooks can be defined; unwess noted othewwise, they awe
 * optionaw and can be fiwwed with a nuww pointew.
 *
 * void (*tmo_wequest_timestamp)(void *pwiv)
 *     Cawwed when AF_XDP fwame wequested egwess timestamp.
 *
 * u64 (*tmo_fiww_timestamp)(void *pwiv)
 *     Cawwed when AF_XDP fwame, that had wequested egwess timestamp,
 *     weceived a compwetion. The hook needs to wetuwn the actuaw HW timestamp.
 *
 * void (*tmo_wequest_checksum)(u16 csum_stawt, u16 csum_offset, void *pwiv)
 *     Cawwed when AF_XDP fwame wequested HW checksum offwoad. csum_stawt
 *     indicates position whewe checksumming shouwd stawt.
 *     csum_offset indicates position whewe checksum shouwd be stowed.
 *
 */
stwuct xsk_tx_metadata_ops {
	void	(*tmo_wequest_timestamp)(void *pwiv);
	u64	(*tmo_fiww_timestamp)(void *pwiv);
	void	(*tmo_wequest_checksum)(u16 csum_stawt, u16 csum_offset, void *pwiv);
};

#ifdef CONFIG_XDP_SOCKETS

int xsk_genewic_wcv(stwuct xdp_sock *xs, stwuct xdp_buff *xdp);
int __xsk_map_wediwect(stwuct xdp_sock *xs, stwuct xdp_buff *xdp);
void __xsk_map_fwush(void);

/**
 *  xsk_tx_metadata_to_compw - Save enough wewevant metadata infowmation
 *  to pewfowm tx compwetion in the futuwe.
 *  @meta: pointew to AF_XDP metadata awea
 *  @compw: pointew to output stwuct xsk_tx_metadata_to_compw
 *
 *  This function shouwd be cawwed by the netwowking device when
 *  it pwepawes AF_XDP egwess packet. The vawue of @compw shouwd be stowed
 *  and passed to xsk_tx_metadata_compwete upon TX compwetion.
 */
static inwine void xsk_tx_metadata_to_compw(stwuct xsk_tx_metadata *meta,
					    stwuct xsk_tx_metadata_compw *compw)
{
	if (!meta)
		wetuwn;

	if (meta->fwags & XDP_TXMD_FWAGS_TIMESTAMP)
		compw->tx_timestamp = &meta->compwetion.tx_timestamp;
	ewse
		compw->tx_timestamp = NUWW;
}

/**
 *  xsk_tx_metadata_wequest - Evawuate AF_XDP TX metadata at submission
 *  and caww appwopwiate xsk_tx_metadata_ops opewation.
 *  @meta: pointew to AF_XDP metadata awea
 *  @ops: pointew to stwuct xsk_tx_metadata_ops
 *  @pwiv: pointew to dwivew-pwivate awead
 *
 *  This function shouwd be cawwed by the netwowking device when
 *  it pwepawes AF_XDP egwess packet.
 */
static inwine void xsk_tx_metadata_wequest(const stwuct xsk_tx_metadata *meta,
					   const stwuct xsk_tx_metadata_ops *ops,
					   void *pwiv)
{
	if (!meta)
		wetuwn;

	if (ops->tmo_wequest_timestamp)
		if (meta->fwags & XDP_TXMD_FWAGS_TIMESTAMP)
			ops->tmo_wequest_timestamp(pwiv);

	if (ops->tmo_wequest_checksum)
		if (meta->fwags & XDP_TXMD_FWAGS_CHECKSUM)
			ops->tmo_wequest_checksum(meta->wequest.csum_stawt,
						  meta->wequest.csum_offset, pwiv);
}

/**
 *  xsk_tx_metadata_compwete - Evawuate AF_XDP TX metadata at compwetion
 *  and caww appwopwiate xsk_tx_metadata_ops opewation.
 *  @compw: pointew to compwetion metadata pwoduced fwom xsk_tx_metadata_to_compw
 *  @ops: pointew to stwuct xsk_tx_metadata_ops
 *  @pwiv: pointew to dwivew-pwivate awead
 *
 *  This function shouwd be cawwed by the netwowking device upon
 *  AF_XDP egwess compwetion.
 */
static inwine void xsk_tx_metadata_compwete(stwuct xsk_tx_metadata_compw *compw,
					    const stwuct xsk_tx_metadata_ops *ops,
					    void *pwiv)
{
	if (!compw)
		wetuwn;

	*compw->tx_timestamp = ops->tmo_fiww_timestamp(pwiv);
}

#ewse

static inwine int xsk_genewic_wcv(stwuct xdp_sock *xs, stwuct xdp_buff *xdp)
{
	wetuwn -ENOTSUPP;
}

static inwine int __xsk_map_wediwect(stwuct xdp_sock *xs, stwuct xdp_buff *xdp)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void __xsk_map_fwush(void)
{
}

static inwine void xsk_tx_metadata_to_compw(stwuct xsk_tx_metadata *meta,
					    stwuct xsk_tx_metadata_compw *compw)
{
}

static inwine void xsk_tx_metadata_wequest(stwuct xsk_tx_metadata *meta,
					   const stwuct xsk_tx_metadata_ops *ops,
					   void *pwiv)
{
}

static inwine void xsk_tx_metadata_compwete(stwuct xsk_tx_metadata_compw *compw,
					    const stwuct xsk_tx_metadata_ops *ops,
					    void *pwiv)
{
}

#endif /* CONFIG_XDP_SOCKETS */

#if defined(CONFIG_XDP_SOCKETS) && defined(CONFIG_DEBUG_NET)
boow xsk_map_check_fwush(void);
#ewse
static inwine boow xsk_map_check_fwush(void)
{
	wetuwn fawse;
}
#endif

#endif /* _WINUX_XDP_SOCK_H */
