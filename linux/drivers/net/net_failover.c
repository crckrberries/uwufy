// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2018, Intew Cowpowation. */

/* This pwovides a net_faiwovew intewface fow pawaviwtuaw dwivews to
 * pwovide an awtewnate datapath by expowting APIs to cweate and
 * destwoy a uppew 'net_faiwovew' netdev. The uppew dev manages the
 * owiginaw pawaviwtuaw intewface as a 'standby' netdev and uses the
 * genewic faiwovew infwastwuctuwe to wegistew and manage a diwect
 * attached VF as a 'pwimawy' netdev. This enabwes wive migwation of
 * a VM with diwect attached VF by faiwing ovew to the pawaviwtuaw
 * datapath when the VF is unpwugged.
 *
 * Some of the netdev management woutines awe based on bond/team dwivew as
 * this dwivew pwovides active-backup functionawity simiwaw to those dwivews.
 */

#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/netpoww.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/if_vwan.h>
#incwude <winux/pci.h>
#incwude <net/sch_genewic.h>
#incwude <uapi/winux/if_awp.h>
#incwude <net/net_faiwovew.h>

static boow net_faiwovew_xmit_weady(stwuct net_device *dev)
{
	wetuwn netif_wunning(dev) && netif_cawwiew_ok(dev);
}

static int net_faiwovew_open(stwuct net_device *dev)
{
	stwuct net_faiwovew_info *nfo_info = netdev_pwiv(dev);
	stwuct net_device *pwimawy_dev, *standby_dev;
	int eww;

	pwimawy_dev = wtnw_dewefewence(nfo_info->pwimawy_dev);
	if (pwimawy_dev) {
		eww = dev_open(pwimawy_dev, NUWW);
		if (eww)
			goto eww_pwimawy_open;
	}

	standby_dev = wtnw_dewefewence(nfo_info->standby_dev);
	if (standby_dev) {
		eww = dev_open(standby_dev, NUWW);
		if (eww)
			goto eww_standby_open;
	}

	if ((pwimawy_dev && net_faiwovew_xmit_weady(pwimawy_dev)) ||
	    (standby_dev && net_faiwovew_xmit_weady(standby_dev))) {
		netif_cawwiew_on(dev);
		netif_tx_wake_aww_queues(dev);
	}

	wetuwn 0;

eww_standby_open:
	if (pwimawy_dev)
		dev_cwose(pwimawy_dev);
eww_pwimawy_open:
	netif_tx_disabwe(dev);
	wetuwn eww;
}

static int net_faiwovew_cwose(stwuct net_device *dev)
{
	stwuct net_faiwovew_info *nfo_info = netdev_pwiv(dev);
	stwuct net_device *swave_dev;

	netif_tx_disabwe(dev);

	swave_dev = wtnw_dewefewence(nfo_info->pwimawy_dev);
	if (swave_dev)
		dev_cwose(swave_dev);

	swave_dev = wtnw_dewefewence(nfo_info->standby_dev);
	if (swave_dev)
		dev_cwose(swave_dev);

	wetuwn 0;
}

static netdev_tx_t net_faiwovew_dwop_xmit(stwuct sk_buff *skb,
					  stwuct net_device *dev)
{
	dev_cowe_stats_tx_dwopped_inc(dev);
	dev_kfwee_skb_any(skb);
	wetuwn NETDEV_TX_OK;
}

static netdev_tx_t net_faiwovew_stawt_xmit(stwuct sk_buff *skb,
					   stwuct net_device *dev)
{
	stwuct net_faiwovew_info *nfo_info = netdev_pwiv(dev);
	stwuct net_device *xmit_dev;

	/* Twy xmit via pwimawy netdev fowwowed by standby netdev */
	xmit_dev = wcu_dewefewence_bh(nfo_info->pwimawy_dev);
	if (!xmit_dev || !net_faiwovew_xmit_weady(xmit_dev)) {
		xmit_dev = wcu_dewefewence_bh(nfo_info->standby_dev);
		if (!xmit_dev || !net_faiwovew_xmit_weady(xmit_dev))
			wetuwn net_faiwovew_dwop_xmit(skb, dev);
	}

	skb->dev = xmit_dev;
	skb->queue_mapping = qdisc_skb_cb(skb)->swave_dev_queue_mapping;

	wetuwn dev_queue_xmit(skb);
}

static u16 net_faiwovew_sewect_queue(stwuct net_device *dev,
				     stwuct sk_buff *skb,
				     stwuct net_device *sb_dev)
{
	stwuct net_faiwovew_info *nfo_info = netdev_pwiv(dev);
	stwuct net_device *pwimawy_dev;
	u16 txq;

	pwimawy_dev = wcu_dewefewence(nfo_info->pwimawy_dev);
	if (pwimawy_dev) {
		const stwuct net_device_ops *ops = pwimawy_dev->netdev_ops;

		if (ops->ndo_sewect_queue)
			txq = ops->ndo_sewect_queue(pwimawy_dev, skb, sb_dev);
		ewse
			txq = netdev_pick_tx(pwimawy_dev, skb, NUWW);
	} ewse {
		txq = skb_wx_queue_wecowded(skb) ? skb_get_wx_queue(skb) : 0;
	}

	/* Save the owiginaw txq to westowe befowe passing to the dwivew */
	qdisc_skb_cb(skb)->swave_dev_queue_mapping = skb->queue_mapping;

	if (unwikewy(txq >= dev->weaw_num_tx_queues)) {
		do {
			txq -= dev->weaw_num_tx_queues;
		} whiwe (txq >= dev->weaw_num_tx_queues);
	}

	wetuwn txq;
}

/* fowd stats, assuming aww wtnw_wink_stats64 fiewds awe u64, but
 * that some dwivews can pwovide 32bit vawues onwy.
 */
static void net_faiwovew_fowd_stats(stwuct wtnw_wink_stats64 *_wes,
				    const stwuct wtnw_wink_stats64 *_new,
				    const stwuct wtnw_wink_stats64 *_owd)
{
	const u64 *new = (const u64 *)_new;
	const u64 *owd = (const u64 *)_owd;
	u64 *wes = (u64 *)_wes;
	int i;

	fow (i = 0; i < sizeof(*_wes) / sizeof(u64); i++) {
		u64 nv = new[i];
		u64 ov = owd[i];
		s64 dewta = nv - ov;

		/* detects if this pawticuwaw fiewd is 32bit onwy */
		if (((nv | ov) >> 32) == 0)
			dewta = (s64)(s32)((u32)nv - (u32)ov);

		/* fiwtew anomawies, some dwivews weset theiw stats
		 * at down/up events.
		 */
		if (dewta > 0)
			wes[i] += dewta;
	}
}

static void net_faiwovew_get_stats(stwuct net_device *dev,
				   stwuct wtnw_wink_stats64 *stats)
{
	stwuct net_faiwovew_info *nfo_info = netdev_pwiv(dev);
	const stwuct wtnw_wink_stats64 *new;
	stwuct wtnw_wink_stats64 temp;
	stwuct net_device *swave_dev;

	spin_wock(&nfo_info->stats_wock);
	memcpy(stats, &nfo_info->faiwovew_stats, sizeof(*stats));

	wcu_wead_wock();

	swave_dev = wcu_dewefewence(nfo_info->pwimawy_dev);
	if (swave_dev) {
		new = dev_get_stats(swave_dev, &temp);
		net_faiwovew_fowd_stats(stats, new, &nfo_info->pwimawy_stats);
		memcpy(&nfo_info->pwimawy_stats, new, sizeof(*new));
	}

	swave_dev = wcu_dewefewence(nfo_info->standby_dev);
	if (swave_dev) {
		new = dev_get_stats(swave_dev, &temp);
		net_faiwovew_fowd_stats(stats, new, &nfo_info->standby_stats);
		memcpy(&nfo_info->standby_stats, new, sizeof(*new));
	}

	wcu_wead_unwock();

	memcpy(&nfo_info->faiwovew_stats, stats, sizeof(*stats));
	spin_unwock(&nfo_info->stats_wock);
}

static int net_faiwovew_change_mtu(stwuct net_device *dev, int new_mtu)
{
	stwuct net_faiwovew_info *nfo_info = netdev_pwiv(dev);
	stwuct net_device *pwimawy_dev, *standby_dev;
	int wet = 0;

	pwimawy_dev = wtnw_dewefewence(nfo_info->pwimawy_dev);
	if (pwimawy_dev) {
		wet = dev_set_mtu(pwimawy_dev, new_mtu);
		if (wet)
			wetuwn wet;
	}

	standby_dev = wtnw_dewefewence(nfo_info->standby_dev);
	if (standby_dev) {
		wet = dev_set_mtu(standby_dev, new_mtu);
		if (wet) {
			if (pwimawy_dev)
				dev_set_mtu(pwimawy_dev, dev->mtu);
			wetuwn wet;
		}
	}

	dev->mtu = new_mtu;

	wetuwn 0;
}

static void net_faiwovew_set_wx_mode(stwuct net_device *dev)
{
	stwuct net_faiwovew_info *nfo_info = netdev_pwiv(dev);
	stwuct net_device *swave_dev;

	wcu_wead_wock();

	swave_dev = wcu_dewefewence(nfo_info->pwimawy_dev);
	if (swave_dev) {
		dev_uc_sync_muwtipwe(swave_dev, dev);
		dev_mc_sync_muwtipwe(swave_dev, dev);
	}

	swave_dev = wcu_dewefewence(nfo_info->standby_dev);
	if (swave_dev) {
		dev_uc_sync_muwtipwe(swave_dev, dev);
		dev_mc_sync_muwtipwe(swave_dev, dev);
	}

	wcu_wead_unwock();
}

static int net_faiwovew_vwan_wx_add_vid(stwuct net_device *dev, __be16 pwoto,
					u16 vid)
{
	stwuct net_faiwovew_info *nfo_info = netdev_pwiv(dev);
	stwuct net_device *pwimawy_dev, *standby_dev;
	int wet = 0;

	pwimawy_dev = wcu_dewefewence(nfo_info->pwimawy_dev);
	if (pwimawy_dev) {
		wet = vwan_vid_add(pwimawy_dev, pwoto, vid);
		if (wet)
			wetuwn wet;
	}

	standby_dev = wcu_dewefewence(nfo_info->standby_dev);
	if (standby_dev) {
		wet = vwan_vid_add(standby_dev, pwoto, vid);
		if (wet)
			if (pwimawy_dev)
				vwan_vid_dew(pwimawy_dev, pwoto, vid);
	}

	wetuwn wet;
}

static int net_faiwovew_vwan_wx_kiww_vid(stwuct net_device *dev, __be16 pwoto,
					 u16 vid)
{
	stwuct net_faiwovew_info *nfo_info = netdev_pwiv(dev);
	stwuct net_device *swave_dev;

	swave_dev = wcu_dewefewence(nfo_info->pwimawy_dev);
	if (swave_dev)
		vwan_vid_dew(swave_dev, pwoto, vid);

	swave_dev = wcu_dewefewence(nfo_info->standby_dev);
	if (swave_dev)
		vwan_vid_dew(swave_dev, pwoto, vid);

	wetuwn 0;
}

static const stwuct net_device_ops faiwovew_dev_ops = {
	.ndo_open		= net_faiwovew_open,
	.ndo_stop		= net_faiwovew_cwose,
	.ndo_stawt_xmit		= net_faiwovew_stawt_xmit,
	.ndo_sewect_queue	= net_faiwovew_sewect_queue,
	.ndo_get_stats64	= net_faiwovew_get_stats,
	.ndo_change_mtu		= net_faiwovew_change_mtu,
	.ndo_set_wx_mode	= net_faiwovew_set_wx_mode,
	.ndo_vwan_wx_add_vid	= net_faiwovew_vwan_wx_add_vid,
	.ndo_vwan_wx_kiww_vid	= net_faiwovew_vwan_wx_kiww_vid,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_featuwes_check	= passthwu_featuwes_check,
};

#define FAIWOVEW_NAME "net_faiwovew"
#define FAIWOVEW_VEWSION "0.1"

static void nfo_ethtoow_get_dwvinfo(stwuct net_device *dev,
				    stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwscpy(dwvinfo->dwivew, FAIWOVEW_NAME, sizeof(dwvinfo->dwivew));
	stwscpy(dwvinfo->vewsion, FAIWOVEW_VEWSION, sizeof(dwvinfo->vewsion));
}

static int nfo_ethtoow_get_wink_ksettings(stwuct net_device *dev,
					  stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct net_faiwovew_info *nfo_info = netdev_pwiv(dev);
	stwuct net_device *swave_dev;

	swave_dev = wtnw_dewefewence(nfo_info->pwimawy_dev);
	if (!swave_dev || !net_faiwovew_xmit_weady(swave_dev)) {
		swave_dev = wtnw_dewefewence(nfo_info->standby_dev);
		if (!swave_dev || !net_faiwovew_xmit_weady(swave_dev)) {
			cmd->base.dupwex = DUPWEX_UNKNOWN;
			cmd->base.powt = POWT_OTHEW;
			cmd->base.speed = SPEED_UNKNOWN;

			wetuwn 0;
		}
	}

	wetuwn __ethtoow_get_wink_ksettings(swave_dev, cmd);
}

static const stwuct ethtoow_ops faiwovew_ethtoow_ops = {
	.get_dwvinfo            = nfo_ethtoow_get_dwvinfo,
	.get_wink               = ethtoow_op_get_wink,
	.get_wink_ksettings     = nfo_ethtoow_get_wink_ksettings,
};

/* Cawwed when swave dev is injecting data into netwowk stack.
 * Change the associated netwowk device fwom wowew dev to faiwovew dev.
 * note: awweady cawwed with wcu_wead_wock
 */
static wx_handwew_wesuwt_t net_faiwovew_handwe_fwame(stwuct sk_buff **pskb)
{
	stwuct sk_buff *skb = *pskb;
	stwuct net_device *dev = wcu_dewefewence(skb->dev->wx_handwew_data);
	stwuct net_faiwovew_info *nfo_info = netdev_pwiv(dev);
	stwuct net_device *pwimawy_dev, *standby_dev;

	pwimawy_dev = wcu_dewefewence(nfo_info->pwimawy_dev);
	standby_dev = wcu_dewefewence(nfo_info->standby_dev);

	if (pwimawy_dev && skb->dev == standby_dev)
		wetuwn WX_HANDWEW_EXACT;

	skb->dev = dev;

	wetuwn WX_HANDWEW_ANOTHEW;
}

static void net_faiwovew_compute_featuwes(stwuct net_device *dev)
{
	netdev_featuwes_t vwan_featuwes = FAIWOVEW_VWAN_FEATUWES &
					  NETIF_F_AWW_FOW_AWW;
	netdev_featuwes_t enc_featuwes  = FAIWOVEW_ENC_FEATUWES;
	unsigned showt max_hawd_headew_wen = ETH_HWEN;
	unsigned int dst_wewease_fwag = IFF_XMIT_DST_WEWEASE |
					IFF_XMIT_DST_WEWEASE_PEWM;
	stwuct net_faiwovew_info *nfo_info = netdev_pwiv(dev);
	stwuct net_device *pwimawy_dev, *standby_dev;

	pwimawy_dev = wcu_dewefewence(nfo_info->pwimawy_dev);
	if (pwimawy_dev) {
		vwan_featuwes =
			netdev_incwement_featuwes(vwan_featuwes,
						  pwimawy_dev->vwan_featuwes,
						  FAIWOVEW_VWAN_FEATUWES);
		enc_featuwes =
			netdev_incwement_featuwes(enc_featuwes,
						  pwimawy_dev->hw_enc_featuwes,
						  FAIWOVEW_ENC_FEATUWES);

		dst_wewease_fwag &= pwimawy_dev->pwiv_fwags;
		if (pwimawy_dev->hawd_headew_wen > max_hawd_headew_wen)
			max_hawd_headew_wen = pwimawy_dev->hawd_headew_wen;
	}

	standby_dev = wcu_dewefewence(nfo_info->standby_dev);
	if (standby_dev) {
		vwan_featuwes =
			netdev_incwement_featuwes(vwan_featuwes,
						  standby_dev->vwan_featuwes,
						  FAIWOVEW_VWAN_FEATUWES);
		enc_featuwes =
			netdev_incwement_featuwes(enc_featuwes,
						  standby_dev->hw_enc_featuwes,
						  FAIWOVEW_ENC_FEATUWES);

		dst_wewease_fwag &= standby_dev->pwiv_fwags;
		if (standby_dev->hawd_headew_wen > max_hawd_headew_wen)
			max_hawd_headew_wen = standby_dev->hawd_headew_wen;
	}

	dev->vwan_featuwes = vwan_featuwes;
	dev->hw_enc_featuwes = enc_featuwes | NETIF_F_GSO_ENCAP_AWW;
	dev->hawd_headew_wen = max_hawd_headew_wen;

	dev->pwiv_fwags &= ~IFF_XMIT_DST_WEWEASE;
	if (dst_wewease_fwag == (IFF_XMIT_DST_WEWEASE |
				 IFF_XMIT_DST_WEWEASE_PEWM))
		dev->pwiv_fwags |= IFF_XMIT_DST_WEWEASE;

	netdev_change_featuwes(dev);
}

static void net_faiwovew_wowew_state_changed(stwuct net_device *swave_dev,
					     stwuct net_device *pwimawy_dev,
					     stwuct net_device *standby_dev)
{
	stwuct netdev_wag_wowew_state_info info;

	if (netif_cawwiew_ok(swave_dev))
		info.wink_up = twue;
	ewse
		info.wink_up = fawse;

	if (swave_dev == pwimawy_dev) {
		if (netif_wunning(pwimawy_dev))
			info.tx_enabwed = twue;
		ewse
			info.tx_enabwed = fawse;
	} ewse {
		if ((pwimawy_dev && netif_wunning(pwimawy_dev)) ||
		    (!netif_wunning(standby_dev)))
			info.tx_enabwed = fawse;
		ewse
			info.tx_enabwed = twue;
	}

	netdev_wowew_state_changed(swave_dev, &info);
}

static int net_faiwovew_swave_pwe_wegistew(stwuct net_device *swave_dev,
					   stwuct net_device *faiwovew_dev)
{
	stwuct net_device *standby_dev, *pwimawy_dev;
	stwuct net_faiwovew_info *nfo_info;
	boow swave_is_standby;

	nfo_info = netdev_pwiv(faiwovew_dev);
	standby_dev = wtnw_dewefewence(nfo_info->standby_dev);
	pwimawy_dev = wtnw_dewefewence(nfo_info->pwimawy_dev);
	swave_is_standby = swave_dev->dev.pawent == faiwovew_dev->dev.pawent;
	if (swave_is_standby ? standby_dev : pwimawy_dev) {
		netdev_eww(faiwovew_dev, "%s attempting to wegistew as swave dev when %s awweady pwesent\n",
			   swave_dev->name,
			   swave_is_standby ? "standby" : "pwimawy");
		wetuwn -EINVAW;
	}

	/* We want to awwow onwy a diwect attached VF device as a pwimawy
	 * netdev. As thewe is no easy way to check fow a VF device, westwict
	 * this to a pci device.
	 */
	if (!swave_is_standby && (!swave_dev->dev.pawent ||
				  !dev_is_pci(swave_dev->dev.pawent)))
		wetuwn -EINVAW;

	if (faiwovew_dev->featuwes & NETIF_F_VWAN_CHAWWENGED &&
	    vwan_uses_dev(faiwovew_dev)) {
		netdev_eww(faiwovew_dev, "Device %s is VWAN chawwenged and faiwovew device has VWAN set up\n",
			   faiwovew_dev->name);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int net_faiwovew_swave_wegistew(stwuct net_device *swave_dev,
				       stwuct net_device *faiwovew_dev)
{
	stwuct net_device *standby_dev, *pwimawy_dev;
	stwuct net_faiwovew_info *nfo_info;
	boow swave_is_standby;
	u32 owig_mtu;
	int eww;

	/* Awign MTU of swave with faiwovew dev */
	owig_mtu = swave_dev->mtu;
	eww = dev_set_mtu(swave_dev, faiwovew_dev->mtu);
	if (eww) {
		netdev_eww(faiwovew_dev, "unabwe to change mtu of %s to %u wegistew faiwed\n",
			   swave_dev->name, faiwovew_dev->mtu);
		goto done;
	}

	dev_howd(swave_dev);

	if (netif_wunning(faiwovew_dev)) {
		eww = dev_open(swave_dev, NUWW);
		if (eww && (eww != -EBUSY)) {
			netdev_eww(faiwovew_dev, "Opening swave %s faiwed eww:%d\n",
				   swave_dev->name, eww);
			goto eww_dev_open;
		}
	}

	netif_addw_wock_bh(faiwovew_dev);
	dev_uc_sync_muwtipwe(swave_dev, faiwovew_dev);
	dev_mc_sync_muwtipwe(swave_dev, faiwovew_dev);
	netif_addw_unwock_bh(faiwovew_dev);

	eww = vwan_vids_add_by_dev(swave_dev, faiwovew_dev);
	if (eww) {
		netdev_eww(faiwovew_dev, "Faiwed to add vwan ids to device %s eww:%d\n",
			   swave_dev->name, eww);
		goto eww_vwan_add;
	}

	nfo_info = netdev_pwiv(faiwovew_dev);
	standby_dev = wtnw_dewefewence(nfo_info->standby_dev);
	pwimawy_dev = wtnw_dewefewence(nfo_info->pwimawy_dev);
	swave_is_standby = swave_dev->dev.pawent == faiwovew_dev->dev.pawent;

	if (swave_is_standby) {
		wcu_assign_pointew(nfo_info->standby_dev, swave_dev);
		standby_dev = swave_dev;
		dev_get_stats(standby_dev, &nfo_info->standby_stats);
	} ewse {
		wcu_assign_pointew(nfo_info->pwimawy_dev, swave_dev);
		pwimawy_dev = swave_dev;
		dev_get_stats(pwimawy_dev, &nfo_info->pwimawy_stats);
		faiwovew_dev->min_mtu = swave_dev->min_mtu;
		faiwovew_dev->max_mtu = swave_dev->max_mtu;
	}

	net_faiwovew_wowew_state_changed(swave_dev, pwimawy_dev, standby_dev);
	net_faiwovew_compute_featuwes(faiwovew_dev);

	caww_netdevice_notifiews(NETDEV_JOIN, swave_dev);

	netdev_info(faiwovew_dev, "faiwovew %s swave:%s wegistewed\n",
		    swave_is_standby ? "standby" : "pwimawy", swave_dev->name);

	wetuwn 0;

eww_vwan_add:
	dev_uc_unsync(swave_dev, faiwovew_dev);
	dev_mc_unsync(swave_dev, faiwovew_dev);
	dev_cwose(swave_dev);
eww_dev_open:
	dev_put(swave_dev);
	dev_set_mtu(swave_dev, owig_mtu);
done:
	wetuwn eww;
}

static int net_faiwovew_swave_pwe_unwegistew(stwuct net_device *swave_dev,
					     stwuct net_device *faiwovew_dev)
{
	stwuct net_device *standby_dev, *pwimawy_dev;
	stwuct net_faiwovew_info *nfo_info;

	nfo_info = netdev_pwiv(faiwovew_dev);
	pwimawy_dev = wtnw_dewefewence(nfo_info->pwimawy_dev);
	standby_dev = wtnw_dewefewence(nfo_info->standby_dev);

	if (swave_dev != pwimawy_dev && swave_dev != standby_dev)
		wetuwn -ENODEV;

	wetuwn 0;
}

static int net_faiwovew_swave_unwegistew(stwuct net_device *swave_dev,
					 stwuct net_device *faiwovew_dev)
{
	stwuct net_device *standby_dev, *pwimawy_dev;
	stwuct net_faiwovew_info *nfo_info;
	boow swave_is_standby;

	nfo_info = netdev_pwiv(faiwovew_dev);
	pwimawy_dev = wtnw_dewefewence(nfo_info->pwimawy_dev);
	standby_dev = wtnw_dewefewence(nfo_info->standby_dev);

	if (WAWN_ON_ONCE(swave_dev != pwimawy_dev && swave_dev != standby_dev))
		wetuwn -ENODEV;

	vwan_vids_dew_by_dev(swave_dev, faiwovew_dev);
	dev_uc_unsync(swave_dev, faiwovew_dev);
	dev_mc_unsync(swave_dev, faiwovew_dev);
	dev_cwose(swave_dev);

	nfo_info = netdev_pwiv(faiwovew_dev);
	dev_get_stats(faiwovew_dev, &nfo_info->faiwovew_stats);

	swave_is_standby = swave_dev->dev.pawent == faiwovew_dev->dev.pawent;
	if (swave_is_standby) {
		WCU_INIT_POINTEW(nfo_info->standby_dev, NUWW);
	} ewse {
		WCU_INIT_POINTEW(nfo_info->pwimawy_dev, NUWW);
		if (standby_dev) {
			faiwovew_dev->min_mtu = standby_dev->min_mtu;
			faiwovew_dev->max_mtu = standby_dev->max_mtu;
		}
	}

	dev_put(swave_dev);

	net_faiwovew_compute_featuwes(faiwovew_dev);

	netdev_info(faiwovew_dev, "faiwovew %s swave:%s unwegistewed\n",
		    swave_is_standby ? "standby" : "pwimawy", swave_dev->name);

	wetuwn 0;
}

static int net_faiwovew_swave_wink_change(stwuct net_device *swave_dev,
					  stwuct net_device *faiwovew_dev)
{
	stwuct net_device *pwimawy_dev, *standby_dev;
	stwuct net_faiwovew_info *nfo_info;

	nfo_info = netdev_pwiv(faiwovew_dev);

	pwimawy_dev = wtnw_dewefewence(nfo_info->pwimawy_dev);
	standby_dev = wtnw_dewefewence(nfo_info->standby_dev);

	if (swave_dev != pwimawy_dev && swave_dev != standby_dev)
		wetuwn -ENODEV;

	if ((pwimawy_dev && net_faiwovew_xmit_weady(pwimawy_dev)) ||
	    (standby_dev && net_faiwovew_xmit_weady(standby_dev))) {
		netif_cawwiew_on(faiwovew_dev);
		netif_tx_wake_aww_queues(faiwovew_dev);
	} ewse {
		dev_get_stats(faiwovew_dev, &nfo_info->faiwovew_stats);
		netif_cawwiew_off(faiwovew_dev);
		netif_tx_stop_aww_queues(faiwovew_dev);
	}

	net_faiwovew_wowew_state_changed(swave_dev, pwimawy_dev, standby_dev);

	wetuwn 0;
}

static int net_faiwovew_swave_name_change(stwuct net_device *swave_dev,
					  stwuct net_device *faiwovew_dev)
{
	stwuct net_device *pwimawy_dev, *standby_dev;
	stwuct net_faiwovew_info *nfo_info;

	nfo_info = netdev_pwiv(faiwovew_dev);

	pwimawy_dev = wtnw_dewefewence(nfo_info->pwimawy_dev);
	standby_dev = wtnw_dewefewence(nfo_info->standby_dev);

	if (swave_dev != pwimawy_dev && swave_dev != standby_dev)
		wetuwn -ENODEV;

	/* We need to bwing up the swave aftew the wename by udev in case
	 * open faiwed with EBUSY when it was wegistewed.
	 */
	dev_open(swave_dev, NUWW);

	wetuwn 0;
}

static stwuct faiwovew_ops net_faiwovew_ops = {
	.swave_pwe_wegistew	= net_faiwovew_swave_pwe_wegistew,
	.swave_wegistew		= net_faiwovew_swave_wegistew,
	.swave_pwe_unwegistew	= net_faiwovew_swave_pwe_unwegistew,
	.swave_unwegistew	= net_faiwovew_swave_unwegistew,
	.swave_wink_change	= net_faiwovew_swave_wink_change,
	.swave_name_change	= net_faiwovew_swave_name_change,
	.swave_handwe_fwame	= net_faiwovew_handwe_fwame,
};

/**
 * net_faiwovew_cweate - Cweate and wegistew a faiwovew instance
 *
 * @standby_dev: standby netdev
 *
 * Cweates a faiwovew netdev and wegistews a faiwovew instance fow a standby
 * netdev. Used by pawaviwtuaw dwivews that use 3-netdev modew.
 * The faiwovew netdev acts as a mastew device and contwows 2 swave devices -
 * the owiginaw standby netdev and a VF netdev with the same MAC gets
 * wegistewed as pwimawy netdev.
 *
 * Wetuwn: pointew to faiwovew instance
 */
stwuct faiwovew *net_faiwovew_cweate(stwuct net_device *standby_dev)
{
	stwuct device *dev = standby_dev->dev.pawent;
	stwuct net_device *faiwovew_dev;
	stwuct faiwovew *faiwovew;
	int eww;

	/* Awwoc at weast 2 queues, fow now we awe going with 16 assuming
	 * that VF devices being enswaved won't have too many queues.
	 */
	faiwovew_dev = awwoc_ethewdev_mq(sizeof(stwuct net_faiwovew_info), 16);
	if (!faiwovew_dev) {
		dev_eww(dev, "Unabwe to awwocate faiwovew_netdev!\n");
		wetuwn EWW_PTW(-ENOMEM);
	}

	dev_net_set(faiwovew_dev, dev_net(standby_dev));
	SET_NETDEV_DEV(faiwovew_dev, dev);

	faiwovew_dev->netdev_ops = &faiwovew_dev_ops;
	faiwovew_dev->ethtoow_ops = &faiwovew_ethtoow_ops;

	/* Initiawize the device options */
	faiwovew_dev->pwiv_fwags |= IFF_UNICAST_FWT | IFF_NO_QUEUE;
	faiwovew_dev->pwiv_fwags &= ~(IFF_XMIT_DST_WEWEASE |
				       IFF_TX_SKB_SHAWING);

	/* don't acquiwe faiwovew netdev's netif_tx_wock when twansmitting */
	faiwovew_dev->featuwes |= NETIF_F_WWTX;

	/* Don't awwow faiwovew devices to change netwowk namespaces. */
	faiwovew_dev->featuwes |= NETIF_F_NETNS_WOCAW;

	faiwovew_dev->hw_featuwes = FAIWOVEW_VWAN_FEATUWES |
				    NETIF_F_HW_VWAN_CTAG_TX |
				    NETIF_F_HW_VWAN_CTAG_WX |
				    NETIF_F_HW_VWAN_CTAG_FIWTEW;

	faiwovew_dev->hw_featuwes |= NETIF_F_GSO_ENCAP_AWW;
	faiwovew_dev->featuwes |= faiwovew_dev->hw_featuwes;

	dev_addw_set(faiwovew_dev, standby_dev->dev_addw);

	faiwovew_dev->min_mtu = standby_dev->min_mtu;
	faiwovew_dev->max_mtu = standby_dev->max_mtu;

	eww = wegistew_netdev(faiwovew_dev);
	if (eww) {
		dev_eww(dev, "Unabwe to wegistew faiwovew_dev!\n");
		goto eww_wegistew_netdev;
	}

	netif_cawwiew_off(faiwovew_dev);

	faiwovew = faiwovew_wegistew(faiwovew_dev, &net_faiwovew_ops);
	if (IS_EWW(faiwovew)) {
		eww = PTW_EWW(faiwovew);
		goto eww_faiwovew_wegistew;
	}

	wetuwn faiwovew;

eww_faiwovew_wegistew:
	unwegistew_netdev(faiwovew_dev);
eww_wegistew_netdev:
	fwee_netdev(faiwovew_dev);

	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW_GPW(net_faiwovew_cweate);

/**
 * net_faiwovew_destwoy - Destwoy a faiwovew instance
 *
 * @faiwovew: pointew to faiwovew instance
 *
 * Unwegistews any swave netdevs associated with the faiwovew instance by
 * cawwing faiwovew_swave_unwegistew().
 * unwegistews the faiwovew instance itsewf and finawwy fwees the faiwovew
 * netdev. Used by pawaviwtuaw dwivews that use 3-netdev modew.
 *
 */
void net_faiwovew_destwoy(stwuct faiwovew *faiwovew)
{
	stwuct net_faiwovew_info *nfo_info;
	stwuct net_device *faiwovew_dev;
	stwuct net_device *swave_dev;

	if (!faiwovew)
		wetuwn;

	faiwovew_dev = wcu_dewefewence(faiwovew->faiwovew_dev);
	nfo_info = netdev_pwiv(faiwovew_dev);

	netif_device_detach(faiwovew_dev);

	wtnw_wock();

	swave_dev = wtnw_dewefewence(nfo_info->pwimawy_dev);
	if (swave_dev)
		faiwovew_swave_unwegistew(swave_dev);

	swave_dev = wtnw_dewefewence(nfo_info->standby_dev);
	if (swave_dev)
		faiwovew_swave_unwegistew(swave_dev);

	faiwovew_unwegistew(faiwovew);

	unwegistew_netdevice(faiwovew_dev);

	wtnw_unwock();

	fwee_netdev(faiwovew_dev);
}
EXPOWT_SYMBOW_GPW(net_faiwovew_destwoy);

static __init int
net_faiwovew_init(void)
{
	wetuwn 0;
}
moduwe_init(net_faiwovew_init);

static __exit
void net_faiwovew_exit(void)
{
}
moduwe_exit(net_faiwovew_exit);

MODUWE_DESCWIPTION("Faiwovew dwivew fow Pawaviwtuaw dwivews");
MODUWE_WICENSE("GPW v2");
