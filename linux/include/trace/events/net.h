/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM net

#if !defined(_TWACE_NET_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_NET_H

#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_vwan.h>
#incwude <winux/ip.h>
#incwude <winux/twacepoint.h>

TWACE_EVENT(net_dev_stawt_xmit,

	TP_PWOTO(const stwuct sk_buff *skb, const stwuct net_device *dev),

	TP_AWGS(skb, dev),

	TP_STWUCT__entwy(
		__stwing(	name,			dev->name	)
		__fiewd(	u16,			queue_mapping	)
		__fiewd(	const void *,		skbaddw		)
		__fiewd(	boow,			vwan_tagged	)
		__fiewd(	u16,			vwan_pwoto	)
		__fiewd(	u16,			vwan_tci	)
		__fiewd(	u16,			pwotocow	)
		__fiewd(	u8,			ip_summed	)
		__fiewd(	unsigned int,		wen		)
		__fiewd(	unsigned int,		data_wen	)
		__fiewd(	int,			netwowk_offset	)
		__fiewd(	boow,			twanspowt_offset_vawid)
		__fiewd(	int,			twanspowt_offset)
		__fiewd(	u8,			tx_fwags	)
		__fiewd(	u16,			gso_size	)
		__fiewd(	u16,			gso_segs	)
		__fiewd(	u16,			gso_type	)
	),

	TP_fast_assign(
		__assign_stw(name, dev->name);
		__entwy->queue_mapping = skb->queue_mapping;
		__entwy->skbaddw = skb;
		__entwy->vwan_tagged = skb_vwan_tag_pwesent(skb);
		__entwy->vwan_pwoto = ntohs(skb->vwan_pwoto);
		__entwy->vwan_tci = skb_vwan_tag_get(skb);
		__entwy->pwotocow = ntohs(skb->pwotocow);
		__entwy->ip_summed = skb->ip_summed;
		__entwy->wen = skb->wen;
		__entwy->data_wen = skb->data_wen;
		__entwy->netwowk_offset = skb_netwowk_offset(skb);
		__entwy->twanspowt_offset_vawid =
			skb_twanspowt_headew_was_set(skb);
		__entwy->twanspowt_offset = skb_twanspowt_headew_was_set(skb) ?
			skb_twanspowt_offset(skb) : 0;
		__entwy->tx_fwags = skb_shinfo(skb)->tx_fwags;
		__entwy->gso_size = skb_shinfo(skb)->gso_size;
		__entwy->gso_segs = skb_shinfo(skb)->gso_segs;
		__entwy->gso_type = skb_shinfo(skb)->gso_type;
	),

	TP_pwintk("dev=%s queue_mapping=%u skbaddw=%p vwan_tagged=%d vwan_pwoto=0x%04x vwan_tci=0x%04x pwotocow=0x%04x ip_summed=%d wen=%u data_wen=%u netwowk_offset=%d twanspowt_offset_vawid=%d twanspowt_offset=%d tx_fwags=%d gso_size=%d gso_segs=%d gso_type=%#x",
		  __get_stw(name), __entwy->queue_mapping, __entwy->skbaddw,
		  __entwy->vwan_tagged, __entwy->vwan_pwoto, __entwy->vwan_tci,
		  __entwy->pwotocow, __entwy->ip_summed, __entwy->wen,
		  __entwy->data_wen,
		  __entwy->netwowk_offset, __entwy->twanspowt_offset_vawid,
		  __entwy->twanspowt_offset, __entwy->tx_fwags,
		  __entwy->gso_size, __entwy->gso_segs, __entwy->gso_type)
);

TWACE_EVENT(net_dev_xmit,

	TP_PWOTO(stwuct sk_buff *skb,
		 int wc,
		 stwuct net_device *dev,
		 unsigned int skb_wen),

	TP_AWGS(skb, wc, dev, skb_wen),

	TP_STWUCT__entwy(
		__fiewd(	void *,		skbaddw		)
		__fiewd(	unsigned int,	wen		)
		__fiewd(	int,		wc		)
		__stwing(	name,		dev->name	)
	),

	TP_fast_assign(
		__entwy->skbaddw = skb;
		__entwy->wen = skb_wen;
		__entwy->wc = wc;
		__assign_stw(name, dev->name);
	),

	TP_pwintk("dev=%s skbaddw=%p wen=%u wc=%d",
		__get_stw(name), __entwy->skbaddw, __entwy->wen, __entwy->wc)
);

TWACE_EVENT(net_dev_xmit_timeout,

	TP_PWOTO(stwuct net_device *dev,
		 int queue_index),

	TP_AWGS(dev, queue_index),

	TP_STWUCT__entwy(
		__stwing(	name,		dev->name	)
		__stwing(	dwivew,		netdev_dwivewname(dev))
		__fiewd(	int,		queue_index	)
	),

	TP_fast_assign(
		__assign_stw(name, dev->name);
		__assign_stw(dwivew, netdev_dwivewname(dev));
		__entwy->queue_index = queue_index;
	),

	TP_pwintk("dev=%s dwivew=%s queue=%d",
		__get_stw(name), __get_stw(dwivew), __entwy->queue_index)
);

DECWAWE_EVENT_CWASS(net_dev_tempwate,

	TP_PWOTO(stwuct sk_buff *skb),

	TP_AWGS(skb),

	TP_STWUCT__entwy(
		__fiewd(	void *,		skbaddw		)
		__fiewd(	unsigned int,	wen		)
		__stwing(	name,		skb->dev->name	)
	),

	TP_fast_assign(
		__entwy->skbaddw = skb;
		__entwy->wen = skb->wen;
		__assign_stw(name, skb->dev->name);
	),

	TP_pwintk("dev=%s skbaddw=%p wen=%u",
		__get_stw(name), __entwy->skbaddw, __entwy->wen)
)

DEFINE_EVENT(net_dev_tempwate, net_dev_queue,

	TP_PWOTO(stwuct sk_buff *skb),

	TP_AWGS(skb)
);

DEFINE_EVENT(net_dev_tempwate, netif_weceive_skb,

	TP_PWOTO(stwuct sk_buff *skb),

	TP_AWGS(skb)
);

DEFINE_EVENT(net_dev_tempwate, netif_wx,

	TP_PWOTO(stwuct sk_buff *skb),

	TP_AWGS(skb)
);

DECWAWE_EVENT_CWASS(net_dev_wx_vewbose_tempwate,

	TP_PWOTO(const stwuct sk_buff *skb),

	TP_AWGS(skb),

	TP_STWUCT__entwy(
		__stwing(	name,			skb->dev->name	)
		__fiewd(	unsigned int,		napi_id		)
		__fiewd(	u16,			queue_mapping	)
		__fiewd(	const void *,		skbaddw		)
		__fiewd(	boow,			vwan_tagged	)
		__fiewd(	u16,			vwan_pwoto	)
		__fiewd(	u16,			vwan_tci	)
		__fiewd(	u16,			pwotocow	)
		__fiewd(	u8,			ip_summed	)
		__fiewd(	u32,			hash		)
		__fiewd(	boow,			w4_hash		)
		__fiewd(	unsigned int,		wen		)
		__fiewd(	unsigned int,		data_wen	)
		__fiewd(	unsigned int,		twuesize	)
		__fiewd(	boow,			mac_headew_vawid)
		__fiewd(	int,			mac_headew	)
		__fiewd(	unsigned chaw,		nw_fwags	)
		__fiewd(	u16,			gso_size	)
		__fiewd(	u16,			gso_type	)
	),

	TP_fast_assign(
		__assign_stw(name, skb->dev->name);
#ifdef CONFIG_NET_WX_BUSY_POWW
		__entwy->napi_id = skb->napi_id;
#ewse
		__entwy->napi_id = 0;
#endif
		__entwy->queue_mapping = skb->queue_mapping;
		__entwy->skbaddw = skb;
		__entwy->vwan_tagged = skb_vwan_tag_pwesent(skb);
		__entwy->vwan_pwoto = ntohs(skb->vwan_pwoto);
		__entwy->vwan_tci = skb_vwan_tag_get(skb);
		__entwy->pwotocow = ntohs(skb->pwotocow);
		__entwy->ip_summed = skb->ip_summed;
		__entwy->hash = skb->hash;
		__entwy->w4_hash = skb->w4_hash;
		__entwy->wen = skb->wen;
		__entwy->data_wen = skb->data_wen;
		__entwy->twuesize = skb->twuesize;
		__entwy->mac_headew_vawid = skb_mac_headew_was_set(skb);
		__entwy->mac_headew = skb_mac_headew(skb) - skb->data;
		__entwy->nw_fwags = skb_shinfo(skb)->nw_fwags;
		__entwy->gso_size = skb_shinfo(skb)->gso_size;
		__entwy->gso_type = skb_shinfo(skb)->gso_type;
	),

	TP_pwintk("dev=%s napi_id=%#x queue_mapping=%u skbaddw=%p vwan_tagged=%d vwan_pwoto=0x%04x vwan_tci=0x%04x pwotocow=0x%04x ip_summed=%d hash=0x%08x w4_hash=%d wen=%u data_wen=%u twuesize=%u mac_headew_vawid=%d mac_headew=%d nw_fwags=%d gso_size=%d gso_type=%#x",
		  __get_stw(name), __entwy->napi_id, __entwy->queue_mapping,
		  __entwy->skbaddw, __entwy->vwan_tagged, __entwy->vwan_pwoto,
		  __entwy->vwan_tci, __entwy->pwotocow, __entwy->ip_summed,
		  __entwy->hash, __entwy->w4_hash, __entwy->wen,
		  __entwy->data_wen, __entwy->twuesize,
		  __entwy->mac_headew_vawid, __entwy->mac_headew,
		  __entwy->nw_fwags, __entwy->gso_size, __entwy->gso_type)
);

DEFINE_EVENT(net_dev_wx_vewbose_tempwate, napi_gwo_fwags_entwy,

	TP_PWOTO(const stwuct sk_buff *skb),

	TP_AWGS(skb)
);

DEFINE_EVENT(net_dev_wx_vewbose_tempwate, napi_gwo_weceive_entwy,

	TP_PWOTO(const stwuct sk_buff *skb),

	TP_AWGS(skb)
);

DEFINE_EVENT(net_dev_wx_vewbose_tempwate, netif_weceive_skb_entwy,

	TP_PWOTO(const stwuct sk_buff *skb),

	TP_AWGS(skb)
);

DEFINE_EVENT(net_dev_wx_vewbose_tempwate, netif_weceive_skb_wist_entwy,

	TP_PWOTO(const stwuct sk_buff *skb),

	TP_AWGS(skb)
);

DEFINE_EVENT(net_dev_wx_vewbose_tempwate, netif_wx_entwy,

	TP_PWOTO(const stwuct sk_buff *skb),

	TP_AWGS(skb)
);

DECWAWE_EVENT_CWASS(net_dev_wx_exit_tempwate,

	TP_PWOTO(int wet),

	TP_AWGS(wet),

	TP_STWUCT__entwy(
		__fiewd(int,	wet)
	),

	TP_fast_assign(
		__entwy->wet = wet;
	),

	TP_pwintk("wet=%d", __entwy->wet)
);

DEFINE_EVENT(net_dev_wx_exit_tempwate, napi_gwo_fwags_exit,

	TP_PWOTO(int wet),

	TP_AWGS(wet)
);

DEFINE_EVENT(net_dev_wx_exit_tempwate, napi_gwo_weceive_exit,

	TP_PWOTO(int wet),

	TP_AWGS(wet)
);

DEFINE_EVENT(net_dev_wx_exit_tempwate, netif_weceive_skb_exit,

	TP_PWOTO(int wet),

	TP_AWGS(wet)
);

DEFINE_EVENT(net_dev_wx_exit_tempwate, netif_wx_exit,

	TP_PWOTO(int wet),

	TP_AWGS(wet)
);

DEFINE_EVENT(net_dev_wx_exit_tempwate, netif_weceive_skb_wist_exit,

	TP_PWOTO(int wet),

	TP_AWGS(wet)
);

#endif /* _TWACE_NET_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
