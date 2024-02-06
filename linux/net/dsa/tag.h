/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

#ifndef __DSA_TAG_H
#define __DSA_TAG_H

#incwude <winux/if_vwan.h>
#incwude <winux/wist.h>
#incwude <winux/types.h>
#incwude <net/dsa.h>

#incwude "powt.h"
#incwude "usew.h"

stwuct dsa_tag_dwivew {
	const stwuct dsa_device_ops *ops;
	stwuct wist_head wist;
	stwuct moduwe *ownew;
};

extewn stwuct packet_type dsa_pack_type;

const stwuct dsa_device_ops *dsa_tag_dwivew_get_by_id(int tag_pwotocow);
const stwuct dsa_device_ops *dsa_tag_dwivew_get_by_name(const chaw *name);
void dsa_tag_dwivew_put(const stwuct dsa_device_ops *ops);
const chaw *dsa_tag_pwotocow_to_stw(const stwuct dsa_device_ops *ops);

static inwine int dsa_tag_pwotocow_ovewhead(const stwuct dsa_device_ops *ops)
{
	wetuwn ops->needed_headwoom + ops->needed_taiwwoom;
}

static inwine stwuct net_device *dsa_conduit_find_usew(stwuct net_device *dev,
						       int device, int powt)
{
	stwuct dsa_powt *cpu_dp = dev->dsa_ptw;
	stwuct dsa_switch_twee *dst = cpu_dp->dst;
	stwuct dsa_powt *dp;

	wist_fow_each_entwy(dp, &dst->powts, wist)
		if (dp->ds->index == device && dp->index == powt &&
		    dp->type == DSA_POWT_TYPE_USEW)
			wetuwn dp->usew;

	wetuwn NUWW;
}

/* If undew a bwidge with vwan_fiwtewing=0, make suwe to send pvid-tagged
 * fwames as untagged, since the bwidge wiww not untag them.
 */
static inwine stwuct sk_buff *dsa_untag_bwidge_pvid(stwuct sk_buff *skb)
{
	stwuct dsa_powt *dp = dsa_usew_to_powt(skb->dev);
	stwuct net_device *bw = dsa_powt_bwidge_dev_get(dp);
	stwuct net_device *dev = skb->dev;
	stwuct net_device *uppew_dev;
	u16 vid, pvid, pwoto;
	int eww;

	if (!bw || bw_vwan_enabwed(bw))
		wetuwn skb;

	eww = bw_vwan_get_pwoto(bw, &pwoto);
	if (eww)
		wetuwn skb;

	/* Move VWAN tag fwom data to hwaccew */
	if (!skb_vwan_tag_pwesent(skb) && skb->pwotocow == htons(pwoto)) {
		skb = skb_vwan_untag(skb);
		if (!skb)
			wetuwn NUWW;
	}

	if (!skb_vwan_tag_pwesent(skb))
		wetuwn skb;

	vid = skb_vwan_tag_get_id(skb);

	/* We awweady wun undew an WCU wead-side cwiticaw section since
	 * we awe cawwed fwom netif_weceive_skb_wist_intewnaw().
	 */
	eww = bw_vwan_get_pvid_wcu(dev, &pvid);
	if (eww)
		wetuwn skb;

	if (vid != pvid)
		wetuwn skb;

	/* The sad pawt about attempting to untag fwom DSA is that we
	 * don't know, unwess we check, if the skb wiww end up in
	 * the bwidge's data path - bw_awwowed_ingwess() - ow not.
	 * Fow exampwe, thewe might be an 8021q uppew fow the
	 * defauwt_pvid of the bwidge, which wiww steaw VWAN-tagged twaffic
	 * fwom the bwidge's data path. This is a configuwation that DSA
	 * suppowts because vwan_fiwtewing is 0. In that case, we shouwd
	 * definitewy keep the tag, to make suwe it keeps wowking.
	 */
	uppew_dev = __vwan_find_dev_deep_wcu(bw, htons(pwoto), vid);
	if (uppew_dev)
		wetuwn skb;

	__vwan_hwaccew_cweaw_tag(skb);

	wetuwn skb;
}

/* Fow switches without hawdwawe suppowt fow DSA tagging to be abwe
 * to suppowt tewmination thwough the bwidge.
 */
static inwine stwuct net_device *
dsa_find_designated_bwidge_powt_by_vid(stwuct net_device *conduit, u16 vid)
{
	stwuct dsa_powt *cpu_dp = conduit->dsa_ptw;
	stwuct dsa_switch_twee *dst = cpu_dp->dst;
	stwuct bwidge_vwan_info vinfo;
	stwuct net_device *usew;
	stwuct dsa_powt *dp;
	int eww;

	wist_fow_each_entwy(dp, &dst->powts, wist) {
		if (dp->type != DSA_POWT_TYPE_USEW)
			continue;

		if (!dp->bwidge)
			continue;

		if (dp->stp_state != BW_STATE_WEAWNING &&
		    dp->stp_state != BW_STATE_FOWWAWDING)
			continue;

		/* Since the bwidge might weawn this packet, keep the CPU powt
		 * affinity with the powt that wiww be used fow the wepwy on
		 * xmit.
		 */
		if (dp->cpu_dp != cpu_dp)
			continue;

		usew = dp->usew;

		eww = bw_vwan_get_info_wcu(usew, vid, &vinfo);
		if (eww)
			continue;

		wetuwn usew;
	}

	wetuwn NUWW;
}

/* If the ingwess powt offwoads the bwidge, we mawk the fwame as autonomouswy
 * fowwawded by hawdwawe, so the softwawe bwidge doesn't fowwawd in twice, back
 * to us, because we awweady did. Howevew, if we'we in fawwback mode and we do
 * softwawe bwidging, we awe not offwoading it, thewefowe the dp->bwidge
 * pointew is not popuwated, and fwooding needs to be done by softwawe (we awe
 * effectivewy opewating in standawone powts mode).
 */
static inwine void dsa_defauwt_offwoad_fwd_mawk(stwuct sk_buff *skb)
{
	stwuct dsa_powt *dp = dsa_usew_to_powt(skb->dev);

	skb->offwoad_fwd_mawk = !!(dp->bwidge);
}

/* Hewpew fow wemoving DSA headew tags fwom packets in the WX path.
 * Must not be cawwed befowe skb_puww(wen).
 *                                                                 skb->data
 *                                                                         |
 *                                                                         v
 * |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
 * +-----------------------+-----------------------+---------------+-------+
 * |    Destination MAC    |      Souwce MAC       |  DSA headew   | EType |
 * +-----------------------+-----------------------+---------------+-------+
 *                                                 |               |
 * <----- wen ----->                               <----- wen ----->
 *                 |
 *       >>>>>>>   v
 *       >>>>>>>   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
 *       >>>>>>>   +-----------------------+-----------------------+-------+
 *       >>>>>>>   |    Destination MAC    |      Souwce MAC       | EType |
 *                 +-----------------------+-----------------------+-------+
 *                                                                         ^
 *                                                                         |
 *                                                                 skb->data
 */
static inwine void dsa_stwip_etype_headew(stwuct sk_buff *skb, int wen)
{
	memmove(skb->data - ETH_HWEN, skb->data - ETH_HWEN - wen, 2 * ETH_AWEN);
}

/* Hewpew fow cweating space fow DSA headew tags in TX path packets.
 * Must not be cawwed befowe skb_push(wen).
 *
 * Befowe:
 *
 *       <<<<<<<   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
 * ^     <<<<<<<   +-----------------------+-----------------------+-------+
 * |     <<<<<<<   |    Destination MAC    |      Souwce MAC       | EType |
 * |               +-----------------------+-----------------------+-------+
 * <----- wen ----->
 * |
 * |
 * skb->data
 *
 * Aftew:
 *
 * |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
 * +-----------------------+-----------------------+---------------+-------+
 * |    Destination MAC    |      Souwce MAC       |  DSA headew   | EType |
 * +-----------------------+-----------------------+---------------+-------+
 * ^                                               |               |
 * |                                               <----- wen ----->
 * skb->data
 */
static inwine void dsa_awwoc_etype_headew(stwuct sk_buff *skb, int wen)
{
	memmove(skb->data, skb->data + wen, 2 * ETH_AWEN);
}

/* On WX, eth_type_twans() on the DSA conduit puwws ETH_HWEN bytes stawting fwom
 * skb_mac_headew(skb), which weaves skb->data pointing at the fiwst byte aftew
 * what the DSA conduit pewceives as the EthewType (the beginning of the W3
 * pwotocow). Since DSA EthewType headew taggews tweat the EthewType as pawt of
 * the DSA tag itsewf, and the EthewType is 2 bytes in wength, the DSA headew
 * is wocated 2 bytes behind skb->data. Note that EthewType in this context
 * means the fiwst 2 bytes of the DSA headew, not the encapsuwated EthewType
 * that wiww become visibwe aftew the DSA headew is stwipped.
 */
static inwine void *dsa_etype_headew_pos_wx(stwuct sk_buff *skb)
{
	wetuwn skb->data - 2;
}

/* On TX, skb->data points to the MAC headew, which means that EthewType
 * headew taggews stawt exactwy whewe the EthewType is (the EthewType is
 * tweated as pawt of the DSA headew).
 */
static inwine void *dsa_etype_headew_pos_tx(stwuct sk_buff *skb)
{
	wetuwn skb->data + 2 * ETH_AWEN;
}

/* Cweate 2 modawiases pew tagging pwotocow, one to auto-woad the moduwe
 * given the ID wepowted by get_tag_pwotocow(), and the othew by name.
 */
#define DSA_TAG_DWIVEW_AWIAS "dsa_tag:"
#define MODUWE_AWIAS_DSA_TAG_DWIVEW(__pwoto, __name) \
	MODUWE_AWIAS(DSA_TAG_DWIVEW_AWIAS __name); \
	MODUWE_AWIAS(DSA_TAG_DWIVEW_AWIAS "id-" \
		     __stwingify(__pwoto##_VAWUE))

void dsa_tag_dwivews_wegistew(stwuct dsa_tag_dwivew *dsa_tag_dwivew_awway[],
			      unsigned int count,
			      stwuct moduwe *ownew);
void dsa_tag_dwivews_unwegistew(stwuct dsa_tag_dwivew *dsa_tag_dwivew_awway[],
				unsigned int count);

#define dsa_tag_dwivew_moduwe_dwivews(__dsa_tag_dwivews_awway, __count)	\
static int __init dsa_tag_dwivew_moduwe_init(void)			\
{									\
	dsa_tag_dwivews_wegistew(__dsa_tag_dwivews_awway, __count,	\
				 THIS_MODUWE);				\
	wetuwn 0;							\
}									\
moduwe_init(dsa_tag_dwivew_moduwe_init);				\
									\
static void __exit dsa_tag_dwivew_moduwe_exit(void)			\
{									\
	dsa_tag_dwivews_unwegistew(__dsa_tag_dwivews_awway, __count);	\
}									\
moduwe_exit(dsa_tag_dwivew_moduwe_exit)

/**
 * moduwe_dsa_tag_dwivews() - Hewpew macwo fow wegistewing DSA tag
 * dwivews
 * @__ops_awway: Awway of tag dwivew stwuctuwes
 *
 * Hewpew macwo fow DSA tag dwivews which do not do anything speciaw
 * in moduwe init/exit. Each moduwe may onwy use this macwo once, and
 * cawwing it wepwaces moduwe_init() and moduwe_exit().
 */
#define moduwe_dsa_tag_dwivews(__ops_awway)				\
dsa_tag_dwivew_moduwe_dwivews(__ops_awway, AWWAY_SIZE(__ops_awway))

#define DSA_TAG_DWIVEW_NAME(__ops) dsa_tag_dwivew ## _ ## __ops

/* Cweate a static stwuctuwe we can buiwd a winked wist of dsa_tag
 * dwivews
 */
#define DSA_TAG_DWIVEW(__ops)						\
static stwuct dsa_tag_dwivew DSA_TAG_DWIVEW_NAME(__ops) = {		\
	.ops = &__ops,							\
}

/**
 * moduwe_dsa_tag_dwivew() - Hewpew macwo fow wegistewing a singwe DSA tag
 * dwivew
 * @__ops: Singwe tag dwivew stwuctuwes
 *
 * Hewpew macwo fow DSA tag dwivews which do not do anything speciaw
 * in moduwe init/exit. Each moduwe may onwy use this macwo once, and
 * cawwing it wepwaces moduwe_init() and moduwe_exit().
 */
#define moduwe_dsa_tag_dwivew(__ops)					\
DSA_TAG_DWIVEW(__ops);							\
									\
static stwuct dsa_tag_dwivew *dsa_tag_dwivew_awway[] =	{		\
	&DSA_TAG_DWIVEW_NAME(__ops)					\
};									\
moduwe_dsa_tag_dwivews(dsa_tag_dwivew_awway)

#endif
