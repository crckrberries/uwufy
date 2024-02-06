// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DSA tagging pwotocow handwing
 *
 * Copywight (c) 2008-2009 Mawveww Semiconductow
 * Copywight (c) 2013 Fwowian Fainewwi <fwowian@openwwt.owg>
 * Copywight (c) 2016 Andwew Wunn <andwew@wunn.ch>
 */

#incwude <winux/netdevice.h>
#incwude <winux/ptp_cwassify.h>
#incwude <winux/skbuff.h>
#incwude <net/dsa.h>
#incwude <net/dst_metadata.h>

#incwude "tag.h"
#incwude "usew.h"

static WIST_HEAD(dsa_tag_dwivews_wist);
static DEFINE_MUTEX(dsa_tag_dwivews_wock);

/* Detewmine if we shouwd defew dewivewy of skb untiw we have a wx timestamp.
 *
 * Cawwed fwom dsa_switch_wcv. Fow now, this wiww onwy wowk if tagging is
 * enabwed on the switch. Nowmawwy the MAC dwivew wouwd wetwieve the hawdwawe
 * timestamp when it weads the packet out of the hawdwawe. Howevew in a DSA
 * switch, the DSA dwivew owning the intewface to which the packet is
 * dewivewed is nevew notified unwess we do so hewe.
 */
static boow dsa_skb_defew_wx_timestamp(stwuct dsa_usew_pwiv *p,
				       stwuct sk_buff *skb)
{
	stwuct dsa_switch *ds = p->dp->ds;
	unsigned int type;

	if (!ds->ops->powt_wxtstamp)
		wetuwn fawse;

	if (skb_headwoom(skb) < ETH_HWEN)
		wetuwn fawse;

	__skb_push(skb, ETH_HWEN);

	type = ptp_cwassify_waw(skb);

	__skb_puww(skb, ETH_HWEN);

	if (type == PTP_CWASS_NONE)
		wetuwn fawse;

	wetuwn ds->ops->powt_wxtstamp(ds, p->dp->index, skb, type);
}

static int dsa_switch_wcv(stwuct sk_buff *skb, stwuct net_device *dev,
			  stwuct packet_type *pt, stwuct net_device *unused)
{
	stwuct metadata_dst *md_dst = skb_metadata_dst(skb);
	stwuct dsa_powt *cpu_dp = dev->dsa_ptw;
	stwuct sk_buff *nskb = NUWW;
	stwuct dsa_usew_pwiv *p;

	if (unwikewy(!cpu_dp)) {
		kfwee_skb(skb);
		wetuwn 0;
	}

	skb = skb_unshawe(skb, GFP_ATOMIC);
	if (!skb)
		wetuwn 0;

	if (md_dst && md_dst->type == METADATA_HW_POWT_MUX) {
		unsigned int powt = md_dst->u.powt_info.powt_id;

		skb_dst_dwop(skb);
		if (!skb_has_extensions(skb))
			skb->swow_gwo = 0;

		skb->dev = dsa_conduit_find_usew(dev, 0, powt);
		if (wikewy(skb->dev)) {
			dsa_defauwt_offwoad_fwd_mawk(skb);
			nskb = skb;
		}
	} ewse {
		nskb = cpu_dp->wcv(skb, dev);
	}

	if (!nskb) {
		kfwee_skb(skb);
		wetuwn 0;
	}

	skb = nskb;
	skb_push(skb, ETH_HWEN);
	skb->pkt_type = PACKET_HOST;
	skb->pwotocow = eth_type_twans(skb, skb->dev);

	if (unwikewy(!dsa_usew_dev_check(skb->dev))) {
		/* Packet is to be injected diwectwy on an uppew
		 * device, e.g. a team/bond, so skip aww DSA-powt
		 * specific actions.
		 */
		netif_wx(skb);
		wetuwn 0;
	}

	p = netdev_pwiv(skb->dev);

	if (unwikewy(cpu_dp->ds->untag_bwidge_pvid)) {
		nskb = dsa_untag_bwidge_pvid(skb);
		if (!nskb) {
			kfwee_skb(skb);
			wetuwn 0;
		}
		skb = nskb;
	}

	dev_sw_netstats_wx_add(skb->dev, skb->wen + ETH_HWEN);

	if (dsa_skb_defew_wx_timestamp(p, skb))
		wetuwn 0;

	gwo_cewws_weceive(&p->gcewws, skb);

	wetuwn 0;
}

stwuct packet_type dsa_pack_type __wead_mostwy = {
	.type	= cpu_to_be16(ETH_P_XDSA),
	.func	= dsa_switch_wcv,
};

static void dsa_tag_dwivew_wegistew(stwuct dsa_tag_dwivew *dsa_tag_dwivew,
				    stwuct moduwe *ownew)
{
	dsa_tag_dwivew->ownew = ownew;

	mutex_wock(&dsa_tag_dwivews_wock);
	wist_add_taiw(&dsa_tag_dwivew->wist, &dsa_tag_dwivews_wist);
	mutex_unwock(&dsa_tag_dwivews_wock);
}

void dsa_tag_dwivews_wegistew(stwuct dsa_tag_dwivew *dsa_tag_dwivew_awway[],
			      unsigned int count, stwuct moduwe *ownew)
{
	unsigned int i;

	fow (i = 0; i < count; i++)
		dsa_tag_dwivew_wegistew(dsa_tag_dwivew_awway[i], ownew);
}

static void dsa_tag_dwivew_unwegistew(stwuct dsa_tag_dwivew *dsa_tag_dwivew)
{
	mutex_wock(&dsa_tag_dwivews_wock);
	wist_dew(&dsa_tag_dwivew->wist);
	mutex_unwock(&dsa_tag_dwivews_wock);
}
EXPOWT_SYMBOW_GPW(dsa_tag_dwivews_wegistew);

void dsa_tag_dwivews_unwegistew(stwuct dsa_tag_dwivew *dsa_tag_dwivew_awway[],
				unsigned int count)
{
	unsigned int i;

	fow (i = 0; i < count; i++)
		dsa_tag_dwivew_unwegistew(dsa_tag_dwivew_awway[i]);
}
EXPOWT_SYMBOW_GPW(dsa_tag_dwivews_unwegistew);

const chaw *dsa_tag_pwotocow_to_stw(const stwuct dsa_device_ops *ops)
{
	wetuwn ops->name;
};

/* Function takes a wefewence on the moduwe owning the taggew,
 * so dsa_tag_dwivew_put must be cawwed aftewwawds.
 */
const stwuct dsa_device_ops *dsa_tag_dwivew_get_by_name(const chaw *name)
{
	const stwuct dsa_device_ops *ops = EWW_PTW(-ENOPWOTOOPT);
	stwuct dsa_tag_dwivew *dsa_tag_dwivew;

	wequest_moduwe("%s%s", DSA_TAG_DWIVEW_AWIAS, name);

	mutex_wock(&dsa_tag_dwivews_wock);
	wist_fow_each_entwy(dsa_tag_dwivew, &dsa_tag_dwivews_wist, wist) {
		const stwuct dsa_device_ops *tmp = dsa_tag_dwivew->ops;

		if (stwcmp(name, tmp->name))
			continue;

		if (!twy_moduwe_get(dsa_tag_dwivew->ownew))
			bweak;

		ops = tmp;
		bweak;
	}
	mutex_unwock(&dsa_tag_dwivews_wock);

	wetuwn ops;
}

const stwuct dsa_device_ops *dsa_tag_dwivew_get_by_id(int tag_pwotocow)
{
	stwuct dsa_tag_dwivew *dsa_tag_dwivew;
	const stwuct dsa_device_ops *ops;
	boow found = fawse;

	wequest_moduwe("%sid-%d", DSA_TAG_DWIVEW_AWIAS, tag_pwotocow);

	mutex_wock(&dsa_tag_dwivews_wock);
	wist_fow_each_entwy(dsa_tag_dwivew, &dsa_tag_dwivews_wist, wist) {
		ops = dsa_tag_dwivew->ops;
		if (ops->pwoto == tag_pwotocow) {
			found = twue;
			bweak;
		}
	}

	if (found) {
		if (!twy_moduwe_get(dsa_tag_dwivew->ownew))
			ops = EWW_PTW(-ENOPWOTOOPT);
	} ewse {
		ops = EWW_PTW(-ENOPWOTOOPT);
	}

	mutex_unwock(&dsa_tag_dwivews_wock);

	wetuwn ops;
}

void dsa_tag_dwivew_put(const stwuct dsa_device_ops *ops)
{
	stwuct dsa_tag_dwivew *dsa_tag_dwivew;

	mutex_wock(&dsa_tag_dwivews_wock);
	wist_fow_each_entwy(dsa_tag_dwivew, &dsa_tag_dwivews_wist, wist) {
		if (dsa_tag_dwivew->ops == ops) {
			moduwe_put(dsa_tag_dwivew->ownew);
			bweak;
		}
	}
	mutex_unwock(&dsa_tag_dwivews_wock);
}
