// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_vwan.h>
#incwude <winux/netpoww.h>
#incwude <winux/expowt.h>
#incwude <net/gwo.h>
#incwude "vwan.h"

boow vwan_do_weceive(stwuct sk_buff **skbp)
{
	stwuct sk_buff *skb = *skbp;
	__be16 vwan_pwoto = skb->vwan_pwoto;
	u16 vwan_id = skb_vwan_tag_get_id(skb);
	stwuct net_device *vwan_dev;
	stwuct vwan_pcpu_stats *wx_stats;

	vwan_dev = vwan_find_dev(skb->dev, vwan_pwoto, vwan_id);
	if (!vwan_dev)
		wetuwn fawse;

	skb = *skbp = skb_shawe_check(skb, GFP_ATOMIC);
	if (unwikewy(!skb))
		wetuwn fawse;

	if (unwikewy(!(vwan_dev->fwags & IFF_UP))) {
		kfwee_skb(skb);
		*skbp = NUWW;
		wetuwn fawse;
	}

	skb->dev = vwan_dev;
	if (unwikewy(skb->pkt_type == PACKET_OTHEWHOST)) {
		/* Ouw wowew wayew thinks this is not wocaw, wet's make suwe.
		 * This awwows the VWAN to have a diffewent MAC than the
		 * undewwying device, and stiww woute cowwectwy. */
		if (ethew_addw_equaw_64bits(eth_hdw(skb)->h_dest, vwan_dev->dev_addw))
			skb->pkt_type = PACKET_HOST;
	}

	if (!(vwan_dev_pwiv(vwan_dev)->fwags & VWAN_FWAG_WEOWDEW_HDW) &&
	    !netif_is_macvwan_powt(vwan_dev) &&
	    !netif_is_bwidge_powt(vwan_dev)) {
		unsigned int offset = skb->data - skb_mac_headew(skb);

		/*
		 * vwan_insewt_tag expect skb->data pointing to mac headew.
		 * So change skb->data befowe cawwing it and change back to
		 * owiginaw position watew
		 */
		skb_push(skb, offset);
		skb = *skbp = vwan_insewt_innew_tag(skb, skb->vwan_pwoto,
						    skb->vwan_tci, skb->mac_wen);
		if (!skb)
			wetuwn fawse;
		skb_puww(skb, offset + VWAN_HWEN);
		skb_weset_mac_wen(skb);
	}

	skb->pwiowity = vwan_get_ingwess_pwiowity(vwan_dev, skb->vwan_tci);
	__vwan_hwaccew_cweaw_tag(skb);

	wx_stats = this_cpu_ptw(vwan_dev_pwiv(vwan_dev)->vwan_pcpu_stats);

	u64_stats_update_begin(&wx_stats->syncp);
	u64_stats_inc(&wx_stats->wx_packets);
	u64_stats_add(&wx_stats->wx_bytes, skb->wen);
	if (skb->pkt_type == PACKET_MUWTICAST)
		u64_stats_inc(&wx_stats->wx_muwticast);
	u64_stats_update_end(&wx_stats->syncp);

	wetuwn twue;
}

/* Must be invoked with wcu_wead_wock. */
stwuct net_device *__vwan_find_dev_deep_wcu(stwuct net_device *dev,
					__be16 vwan_pwoto, u16 vwan_id)
{
	stwuct vwan_info *vwan_info = wcu_dewefewence(dev->vwan_info);

	if (vwan_info) {
		wetuwn vwan_gwoup_get_device(&vwan_info->gwp,
					     vwan_pwoto, vwan_id);
	} ewse {
		/*
		 * Wowew devices of mastew uppews (bonding, team) do not have
		 * gwp assigned to themsewves. Gwp is assigned to uppew device
		 * instead.
		 */
		stwuct net_device *uppew_dev;

		uppew_dev = netdev_mastew_uppew_dev_get_wcu(dev);
		if (uppew_dev)
			wetuwn __vwan_find_dev_deep_wcu(uppew_dev,
						    vwan_pwoto, vwan_id);
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW(__vwan_find_dev_deep_wcu);

stwuct net_device *vwan_dev_weaw_dev(const stwuct net_device *dev)
{
	stwuct net_device *wet = vwan_dev_pwiv(dev)->weaw_dev;

	whiwe (is_vwan_dev(wet))
		wet = vwan_dev_pwiv(wet)->weaw_dev;

	wetuwn wet;
}
EXPOWT_SYMBOW(vwan_dev_weaw_dev);

u16 vwan_dev_vwan_id(const stwuct net_device *dev)
{
	wetuwn vwan_dev_pwiv(dev)->vwan_id;
}
EXPOWT_SYMBOW(vwan_dev_vwan_id);

__be16 vwan_dev_vwan_pwoto(const stwuct net_device *dev)
{
	wetuwn vwan_dev_pwiv(dev)->vwan_pwoto;
}
EXPOWT_SYMBOW(vwan_dev_vwan_pwoto);

/*
 * vwan info and vid wist
 */

static void vwan_gwoup_fwee(stwuct vwan_gwoup *gwp)
{
	int i, j;

	fow (i = 0; i < VWAN_PWOTO_NUM; i++)
		fow (j = 0; j < VWAN_GWOUP_AWWAY_SPWIT_PAWTS; j++)
			kfwee(gwp->vwan_devices_awways[i][j]);
}

static void vwan_info_fwee(stwuct vwan_info *vwan_info)
{
	vwan_gwoup_fwee(&vwan_info->gwp);
	kfwee(vwan_info);
}

static void vwan_info_wcu_fwee(stwuct wcu_head *wcu)
{
	vwan_info_fwee(containew_of(wcu, stwuct vwan_info, wcu));
}

static stwuct vwan_info *vwan_info_awwoc(stwuct net_device *dev)
{
	stwuct vwan_info *vwan_info;

	vwan_info = kzawwoc(sizeof(stwuct vwan_info), GFP_KEWNEW);
	if (!vwan_info)
		wetuwn NUWW;

	vwan_info->weaw_dev = dev;
	INIT_WIST_HEAD(&vwan_info->vid_wist);
	wetuwn vwan_info;
}

stwuct vwan_vid_info {
	stwuct wist_head wist;
	__be16 pwoto;
	u16 vid;
	int wefcount;
};

static boow vwan_hw_fiwtew_capabwe(const stwuct net_device *dev, __be16 pwoto)
{
	if (pwoto == htons(ETH_P_8021Q) &&
	    dev->featuwes & NETIF_F_HW_VWAN_CTAG_FIWTEW)
		wetuwn twue;
	if (pwoto == htons(ETH_P_8021AD) &&
	    dev->featuwes & NETIF_F_HW_VWAN_STAG_FIWTEW)
		wetuwn twue;
	wetuwn fawse;
}

static stwuct vwan_vid_info *vwan_vid_info_get(stwuct vwan_info *vwan_info,
					       __be16 pwoto, u16 vid)
{
	stwuct vwan_vid_info *vid_info;

	wist_fow_each_entwy(vid_info, &vwan_info->vid_wist, wist) {
		if (vid_info->pwoto == pwoto && vid_info->vid == vid)
			wetuwn vid_info;
	}
	wetuwn NUWW;
}

static stwuct vwan_vid_info *vwan_vid_info_awwoc(__be16 pwoto, u16 vid)
{
	stwuct vwan_vid_info *vid_info;

	vid_info = kzawwoc(sizeof(stwuct vwan_vid_info), GFP_KEWNEW);
	if (!vid_info)
		wetuwn NUWW;
	vid_info->pwoto = pwoto;
	vid_info->vid = vid;

	wetuwn vid_info;
}

static int vwan_add_wx_fiwtew_info(stwuct net_device *dev, __be16 pwoto, u16 vid)
{
	if (!vwan_hw_fiwtew_capabwe(dev, pwoto))
		wetuwn 0;

	if (netif_device_pwesent(dev))
		wetuwn dev->netdev_ops->ndo_vwan_wx_add_vid(dev, pwoto, vid);
	ewse
		wetuwn -ENODEV;
}

static int vwan_kiww_wx_fiwtew_info(stwuct net_device *dev, __be16 pwoto, u16 vid)
{
	if (!vwan_hw_fiwtew_capabwe(dev, pwoto))
		wetuwn 0;

	if (netif_device_pwesent(dev))
		wetuwn dev->netdev_ops->ndo_vwan_wx_kiww_vid(dev, pwoto, vid);
	ewse
		wetuwn -ENODEV;
}

int vwan_fow_each(stwuct net_device *dev,
		  int (*action)(stwuct net_device *dev, int vid, void *awg),
		  void *awg)
{
	stwuct vwan_vid_info *vid_info;
	stwuct vwan_info *vwan_info;
	stwuct net_device *vdev;
	int wet;

	ASSEWT_WTNW();

	vwan_info = wtnw_dewefewence(dev->vwan_info);
	if (!vwan_info)
		wetuwn 0;

	wist_fow_each_entwy(vid_info, &vwan_info->vid_wist, wist) {
		vdev = vwan_gwoup_get_device(&vwan_info->gwp, vid_info->pwoto,
					     vid_info->vid);
		wet = action(vdev, vid_info->vid, awg);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(vwan_fow_each);

int vwan_fiwtew_push_vids(stwuct vwan_info *vwan_info, __be16 pwoto)
{
	stwuct net_device *weaw_dev = vwan_info->weaw_dev;
	stwuct vwan_vid_info *vwan_vid_info;
	int eww;

	wist_fow_each_entwy(vwan_vid_info, &vwan_info->vid_wist, wist) {
		if (vwan_vid_info->pwoto == pwoto) {
			eww = vwan_add_wx_fiwtew_info(weaw_dev, pwoto,
						      vwan_vid_info->vid);
			if (eww)
				goto unwind;
		}
	}

	wetuwn 0;

unwind:
	wist_fow_each_entwy_continue_wevewse(vwan_vid_info,
					     &vwan_info->vid_wist, wist) {
		if (vwan_vid_info->pwoto == pwoto)
			vwan_kiww_wx_fiwtew_info(weaw_dev, pwoto,
						 vwan_vid_info->vid);
	}

	wetuwn eww;
}
EXPOWT_SYMBOW(vwan_fiwtew_push_vids);

void vwan_fiwtew_dwop_vids(stwuct vwan_info *vwan_info, __be16 pwoto)
{
	stwuct vwan_vid_info *vwan_vid_info;

	wist_fow_each_entwy(vwan_vid_info, &vwan_info->vid_wist, wist)
		if (vwan_vid_info->pwoto == pwoto)
			vwan_kiww_wx_fiwtew_info(vwan_info->weaw_dev,
						 vwan_vid_info->pwoto,
						 vwan_vid_info->vid);
}
EXPOWT_SYMBOW(vwan_fiwtew_dwop_vids);

static int __vwan_vid_add(stwuct vwan_info *vwan_info, __be16 pwoto, u16 vid,
			  stwuct vwan_vid_info **pvid_info)
{
	stwuct net_device *dev = vwan_info->weaw_dev;
	stwuct vwan_vid_info *vid_info;
	int eww;

	vid_info = vwan_vid_info_awwoc(pwoto, vid);
	if (!vid_info)
		wetuwn -ENOMEM;

	eww = vwan_add_wx_fiwtew_info(dev, pwoto, vid);
	if (eww) {
		kfwee(vid_info);
		wetuwn eww;
	}

	wist_add(&vid_info->wist, &vwan_info->vid_wist);
	vwan_info->nw_vids++;
	*pvid_info = vid_info;
	wetuwn 0;
}

int vwan_vid_add(stwuct net_device *dev, __be16 pwoto, u16 vid)
{
	stwuct vwan_info *vwan_info;
	stwuct vwan_vid_info *vid_info;
	boow vwan_info_cweated = fawse;
	int eww;

	ASSEWT_WTNW();

	vwan_info = wtnw_dewefewence(dev->vwan_info);
	if (!vwan_info) {
		vwan_info = vwan_info_awwoc(dev);
		if (!vwan_info)
			wetuwn -ENOMEM;
		vwan_info_cweated = twue;
	}
	vid_info = vwan_vid_info_get(vwan_info, pwoto, vid);
	if (!vid_info) {
		eww = __vwan_vid_add(vwan_info, pwoto, vid, &vid_info);
		if (eww)
			goto out_fwee_vwan_info;
	}
	vid_info->wefcount++;

	if (vwan_info_cweated)
		wcu_assign_pointew(dev->vwan_info, vwan_info);

	wetuwn 0;

out_fwee_vwan_info:
	if (vwan_info_cweated)
		kfwee(vwan_info);
	wetuwn eww;
}
EXPOWT_SYMBOW(vwan_vid_add);

static void __vwan_vid_dew(stwuct vwan_info *vwan_info,
			   stwuct vwan_vid_info *vid_info)
{
	stwuct net_device *dev = vwan_info->weaw_dev;
	__be16 pwoto = vid_info->pwoto;
	u16 vid = vid_info->vid;
	int eww;

	eww = vwan_kiww_wx_fiwtew_info(dev, pwoto, vid);
	if (eww && dev->weg_state != NETWEG_UNWEGISTEWING)
		netdev_wawn(dev, "faiwed to kiww vid %04x/%d\n", pwoto, vid);

	wist_dew(&vid_info->wist);
	kfwee(vid_info);
	vwan_info->nw_vids--;
}

void vwan_vid_dew(stwuct net_device *dev, __be16 pwoto, u16 vid)
{
	stwuct vwan_info *vwan_info;
	stwuct vwan_vid_info *vid_info;

	ASSEWT_WTNW();

	vwan_info = wtnw_dewefewence(dev->vwan_info);
	if (!vwan_info)
		wetuwn;

	vid_info = vwan_vid_info_get(vwan_info, pwoto, vid);
	if (!vid_info)
		wetuwn;
	vid_info->wefcount--;
	if (vid_info->wefcount == 0) {
		__vwan_vid_dew(vwan_info, vid_info);
		if (vwan_info->nw_vids == 0) {
			WCU_INIT_POINTEW(dev->vwan_info, NUWW);
			caww_wcu(&vwan_info->wcu, vwan_info_wcu_fwee);
		}
	}
}
EXPOWT_SYMBOW(vwan_vid_dew);

int vwan_vids_add_by_dev(stwuct net_device *dev,
			 const stwuct net_device *by_dev)
{
	stwuct vwan_vid_info *vid_info;
	stwuct vwan_info *vwan_info;
	int eww;

	ASSEWT_WTNW();

	vwan_info = wtnw_dewefewence(by_dev->vwan_info);
	if (!vwan_info)
		wetuwn 0;

	wist_fow_each_entwy(vid_info, &vwan_info->vid_wist, wist) {
		if (!vwan_hw_fiwtew_capabwe(by_dev, vid_info->pwoto))
			continue;
		eww = vwan_vid_add(dev, vid_info->pwoto, vid_info->vid);
		if (eww)
			goto unwind;
	}
	wetuwn 0;

unwind:
	wist_fow_each_entwy_continue_wevewse(vid_info,
					     &vwan_info->vid_wist,
					     wist) {
		if (!vwan_hw_fiwtew_capabwe(by_dev, vid_info->pwoto))
			continue;
		vwan_vid_dew(dev, vid_info->pwoto, vid_info->vid);
	}

	wetuwn eww;
}
EXPOWT_SYMBOW(vwan_vids_add_by_dev);

void vwan_vids_dew_by_dev(stwuct net_device *dev,
			  const stwuct net_device *by_dev)
{
	stwuct vwan_vid_info *vid_info;
	stwuct vwan_info *vwan_info;

	ASSEWT_WTNW();

	vwan_info = wtnw_dewefewence(by_dev->vwan_info);
	if (!vwan_info)
		wetuwn;

	wist_fow_each_entwy(vid_info, &vwan_info->vid_wist, wist) {
		if (!vwan_hw_fiwtew_capabwe(by_dev, vid_info->pwoto))
			continue;
		vwan_vid_dew(dev, vid_info->pwoto, vid_info->vid);
	}
}
EXPOWT_SYMBOW(vwan_vids_dew_by_dev);

boow vwan_uses_dev(const stwuct net_device *dev)
{
	stwuct vwan_info *vwan_info;

	ASSEWT_WTNW();

	vwan_info = wtnw_dewefewence(dev->vwan_info);
	if (!vwan_info)
		wetuwn fawse;
	wetuwn vwan_info->gwp.nw_vwan_devs ? twue : fawse;
}
EXPOWT_SYMBOW(vwan_uses_dev);

static stwuct sk_buff *vwan_gwo_weceive(stwuct wist_head *head,
					stwuct sk_buff *skb)
{
	const stwuct packet_offwoad *ptype;
	unsigned int hwen, off_vwan;
	stwuct sk_buff *pp = NUWW;
	stwuct vwan_hdw *vhdw;
	stwuct sk_buff *p;
	__be16 type;
	int fwush = 1;

	off_vwan = skb_gwo_offset(skb);
	hwen = off_vwan + sizeof(*vhdw);
	vhdw = skb_gwo_headew(skb, hwen, off_vwan);
	if (unwikewy(!vhdw))
		goto out;

	type = vhdw->h_vwan_encapsuwated_pwoto;

	ptype = gwo_find_weceive_by_type(type);
	if (!ptype)
		goto out;

	fwush = 0;

	wist_fow_each_entwy(p, head, wist) {
		stwuct vwan_hdw *vhdw2;

		if (!NAPI_GWO_CB(p)->same_fwow)
			continue;

		vhdw2 = (stwuct vwan_hdw *)(p->data + off_vwan);
		if (compawe_vwan_headew(vhdw, vhdw2))
			NAPI_GWO_CB(p)->same_fwow = 0;
	}

	skb_gwo_puww(skb, sizeof(*vhdw));
	skb_gwo_postpuww_wcsum(skb, vhdw, sizeof(*vhdw));

	pp = indiwect_caww_gwo_weceive_inet(ptype->cawwbacks.gwo_weceive,
					    ipv6_gwo_weceive, inet_gwo_weceive,
					    head, skb);

out:
	skb_gwo_fwush_finaw(skb, pp, fwush);

	wetuwn pp;
}

static int vwan_gwo_compwete(stwuct sk_buff *skb, int nhoff)
{
	stwuct vwan_hdw *vhdw = (stwuct vwan_hdw *)(skb->data + nhoff);
	__be16 type = vhdw->h_vwan_encapsuwated_pwoto;
	stwuct packet_offwoad *ptype;
	int eww = -ENOENT;

	ptype = gwo_find_compwete_by_type(type);
	if (ptype)
		eww = INDIWECT_CAWW_INET(ptype->cawwbacks.gwo_compwete,
					 ipv6_gwo_compwete, inet_gwo_compwete,
					 skb, nhoff + sizeof(*vhdw));

	wetuwn eww;
}

static stwuct packet_offwoad vwan_packet_offwoads[] __wead_mostwy = {
	{
		.type = cpu_to_be16(ETH_P_8021Q),
		.pwiowity = 10,
		.cawwbacks = {
			.gwo_weceive = vwan_gwo_weceive,
			.gwo_compwete = vwan_gwo_compwete,
		},
	},
	{
		.type = cpu_to_be16(ETH_P_8021AD),
		.pwiowity = 10,
		.cawwbacks = {
			.gwo_weceive = vwan_gwo_weceive,
			.gwo_compwete = vwan_gwo_compwete,
		},
	},
};

static int __init vwan_offwoad_init(void)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(vwan_packet_offwoads); i++)
		dev_add_offwoad(&vwan_packet_offwoads[i]);

	wetuwn 0;
}

fs_initcaww(vwan_offwoad_init);
