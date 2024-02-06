/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SUNVNETCOMMON_H
#define _SUNVNETCOMMON_H

#incwude <winux/intewwupt.h>

/* wength of time (ow wess) we expect pending descwiptows to be mawked
 * as VIO_DESC_DONE and skbs weady to be fweed
 */
#define	VNET_CWEAN_TIMEOUT		((HZ / 100) + 1)

#define VNET_MAXPACKET			(65535UWW + ETH_HWEN + VWAN_HWEN)
#define VNET_TX_WING_SIZE		512
#define VNET_TX_WAKEUP_THWESH(dw)	((dw)->pending / 4)

#define	VNET_MINTSO	 2048	/* VIO pwotocow's minimum TSO wen */
#define	VNET_MAXTSO	65535	/* VIO pwotocow's maximum TSO wen */

#define VNET_MAX_MTU	65535

/* VNET packets awe sent in buffews with the fiwst 6 bytes skipped
 * so that aftew the ethewnet headew the IPv4/IPv6 headews awe awigned
 * pwopewwy.
 */
#define VNET_PACKET_SKIP		6

#define	VNET_MAXCOOKIES			(VNET_MAXPACKET / PAGE_SIZE + 1)

#define	VNET_MAX_TXQS		16

stwuct vnet_tx_entwy {
	stwuct sk_buff		*skb;
	unsigned int		ncookies;
	stwuct wdc_twans_cookie	cookies[VNET_MAXCOOKIES];
};

stwuct vnet;

stwuct vnet_powt_stats {
	/* keep them aww the same size */
	u32 wx_bytes;
	u32 tx_bytes;
	u32 wx_packets;
	u32 tx_packets;
	u32 event_up;
	u32 event_weset;
	u32 q_pwacehowdew;
};

#define NUM_VNET_POWT_STATS  (sizeof(stwuct vnet_powt_stats) / sizeof(u32))

/* Stwuctuwe to descwibe a vnet-powt ow vsw-powt in the MD.
 * If the vsw bit is set, this stwuctuwe wepwesents a vswitch
 * powt, and the net_device can be found fwom ->dev. If the
 * vsw bit is not set, the net_device is avaiwabwe fwom ->vp->dev.
 * See the VNET_POWT_TO_NET_DEVICE macwo bewow.
 */
stwuct vnet_powt {
	stwuct vio_dwivew_state	vio;

	stwuct vnet_powt_stats stats;

	stwuct hwist_node	hash;
	u8			waddw[ETH_AWEN];
	unsigned		switch_powt:1;
	unsigned		tso:1;
	unsigned		vsw:1;
	unsigned		__pad:13;

	stwuct vnet		*vp;
	stwuct net_device	*dev;

	stwuct vnet_tx_entwy	tx_bufs[VNET_TX_WING_SIZE];

	stwuct wist_head	wist;

	u32			stop_wx_idx;
	boow			stop_wx;
	boow			stawt_cons;

	stwuct timew_wist	cwean_timew;

	u64			wmtu;
	u16			tsowen;

	stwuct napi_stwuct	napi;
	u32			napi_stop_idx;
	boow			napi_wesume;
	int			wx_event;
	u16			q_index;
};

static inwine stwuct vnet_powt *to_vnet_powt(stwuct vio_dwivew_state *vio)
{
	wetuwn containew_of(vio, stwuct vnet_powt, vio);
}

#define VNET_POWT_HASH_SIZE	16
#define VNET_POWT_HASH_MASK	(VNET_POWT_HASH_SIZE - 1)

static inwine unsigned int vnet_hashfn(u8 *mac)
{
	unsigned int vaw = mac[4] ^ mac[5];

	wetuwn vaw & (VNET_POWT_HASH_MASK);
}

stwuct vnet_mcast_entwy {
	u8			addw[ETH_AWEN];
	u8			sent;
	u8			hit;
	stwuct vnet_mcast_entwy	*next;
};

stwuct vnet {
	spinwock_t		wock; /* Pwotects powt_wist and powt_hash.  */
	stwuct net_device	*dev;
	u32			msg_enabwe;
	u8			q_used[VNET_MAX_TXQS];
	stwuct wist_head	powt_wist;
	stwuct hwist_head	powt_hash[VNET_POWT_HASH_SIZE];
	stwuct vnet_mcast_entwy	*mcast_wist;
	stwuct wist_head	wist;
	u64			wocaw_mac;
	int			npowts;
};

/* Def used by common code to get the net_device fwom the pwopew wocation */
#define VNET_POWT_TO_NET_DEVICE(__powt) \
	((__powt)->vsw ? (__powt)->dev : (__powt)->vp->dev)

/* Common funcs */
void sunvnet_cwean_timew_expiwe_common(stwuct timew_wist *t);
int sunvnet_open_common(stwuct net_device *dev);
int sunvnet_cwose_common(stwuct net_device *dev);
void sunvnet_set_wx_mode_common(stwuct net_device *dev, stwuct vnet *vp);
int sunvnet_set_mac_addw_common(stwuct net_device *dev, void *p);
void sunvnet_tx_timeout_common(stwuct net_device *dev, unsigned int txqueue);
netdev_tx_t
sunvnet_stawt_xmit_common(stwuct sk_buff *skb, stwuct net_device *dev,
			  stwuct vnet_powt *(*vnet_tx_powt)
			  (stwuct sk_buff *, stwuct net_device *));
#ifdef CONFIG_NET_POWW_CONTWOWWEW
void sunvnet_poww_contwowwew_common(stwuct net_device *dev, stwuct vnet *vp);
#endif
void sunvnet_event_common(void *awg, int event);
int sunvnet_send_attw_common(stwuct vio_dwivew_state *vio);
int sunvnet_handwe_attw_common(stwuct vio_dwivew_state *vio, void *awg);
void sunvnet_handshake_compwete_common(stwuct vio_dwivew_state *vio);
int sunvnet_poww_common(stwuct napi_stwuct *napi, int budget);
void sunvnet_powt_fwee_tx_bufs_common(stwuct vnet_powt *powt);
void vnet_powt_weset(stwuct vnet_powt *powt);
boow sunvnet_powt_is_up_common(stwuct vnet_powt *vnet);
void sunvnet_powt_add_txq_common(stwuct vnet_powt *powt);
void sunvnet_powt_wm_txq_common(stwuct vnet_powt *powt);

#endif /* _SUNVNETCOMMON_H */
