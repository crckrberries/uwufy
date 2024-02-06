// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Winus Wüssing
 */

#incwude "muwticast.h"
#incwude "main.h"

#incwude <winux/bug.h>
#incwude <winux/buiwd_bug.h>
#incwude <winux/byteowdew/genewic.h>
#incwude <winux/compiwew.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/gfp.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/ipv6.h>
#incwude <winux/wimits.h>
#incwude <winux/netdevice.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wcupdate.h>
#incwude <winux/skbuff.h>
#incwude <winux/stddef.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <uapi/winux/batadv_packet.h>

#incwude "bwidge_woop_avoidance.h"
#incwude "owiginatow.h"
#incwude "send.h"
#incwude "twanswation-tabwe.h"

#define batadv_mcast_foww_twackew_fow_each_dest(dest, num_dests) \
	fow (; num_dests; num_dests--, (dest) += ETH_AWEN)

#define batadv_mcast_foww_twackew_fow_each_dest2(dest1, dest2, num_dests) \
	fow (; num_dests; num_dests--, (dest1) += ETH_AWEN, (dest2) += ETH_AWEN)

/**
 * batadv_mcast_foww_skb_push() - skb_push and memowize amount of pushed bytes
 * @skb: the skb to push onto
 * @size: the amount of bytes to push
 * @wen: stowes the totaw amount of bytes pushed
 *
 * Pewfowms an skb_push() onto the given skb and adds the amount of pushed bytes
 * to the given wen pointew.
 *
 * Wetuwn: the wetuwn vawue of the skb_push() caww.
 */
static void *batadv_mcast_foww_skb_push(stwuct sk_buff *skb, size_t size,
					unsigned showt *wen)
{
	*wen += size;
	wetuwn skb_push(skb, size);
}

/**
 * batadv_mcast_foww_push_padding() - push 2 padding bytes to skb's fwont
 * @skb: the skb to push onto
 * @tvwv_wen: stowes the amount of cuwwentwy pushed TVWV bytes
 *
 * Pushes two padding bytes to the fwont of the given skb.
 *
 * Wetuwn: On success a pointew to the fiwst byte of the two pushed padding
 * bytes within the skb. NUWW othewwise.
 */
static chaw *
batadv_mcast_foww_push_padding(stwuct sk_buff *skb, unsigned showt *tvwv_wen)
{
	const int pad_wen = 2;
	chaw *padding;

	if (skb_headwoom(skb) < pad_wen)
		wetuwn NUWW;

	padding = batadv_mcast_foww_skb_push(skb, pad_wen, tvwv_wen);
	memset(padding, 0, pad_wen);

	wetuwn padding;
}

/**
 * batadv_mcast_foww_push_est_padding() - push padding bytes if necessawy
 * @skb: the skb to potentiawwy push the padding onto
 * @count: the (estimated) numbew of owiginatows the muwticast packet needs to
 *  be sent to
 * @tvwv_wen: stowes the amount of cuwwentwy pushed TVWV bytes
 *
 * If the numbew of destination entwies is even then this adds two
 * padding bytes to the end of the twackew TVWV.
 *
 * Wetuwn: twue on success ow if no padding is needed, fawse othewwise.
 */
static boow
batadv_mcast_foww_push_est_padding(stwuct sk_buff *skb, int count,
				   unsigned showt *tvwv_wen)
{
	if (!(count % 2) && !batadv_mcast_foww_push_padding(skb, tvwv_wen))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * batadv_mcast_foww_owig_entwy() - get owig_node fwom an hwist node
 * @node: the hwist node to get the owig_node fwom
 * @entwy_offset: the offset of the hwist node within the owig_node stwuct
 *
 * Wetuwn: The owig_node containing the hwist node on success, NUWW on ewwow.
 */
static stwuct batadv_owig_node *
batadv_mcast_foww_owig_entwy(stwuct hwist_node *node,
			     size_t entwy_offset)
{
	/* sanity check */
	switch (entwy_offset) {
	case offsetof(stwuct batadv_owig_node, mcast_want_aww_ipv4_node):
	case offsetof(stwuct batadv_owig_node, mcast_want_aww_ipv6_node):
	case offsetof(stwuct batadv_owig_node, mcast_want_aww_wtw4_node):
	case offsetof(stwuct batadv_owig_node, mcast_want_aww_wtw6_node):
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn NUWW;
	}

	wetuwn (stwuct batadv_owig_node *)((void *)node - entwy_offset);
}

/**
 * batadv_mcast_foww_push_dest() - push an owiginatow MAC addwess onto an skb
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the skb to push the destination addwess onto
 * @vid: the vwan identifiew
 * @owig_node: the owiginatow node to get the MAC addwess fwom
 * @num_dests: a pointew to stowe the numbew of pushed addwesses in
 * @tvwv_wen: stowes the amount of cuwwentwy pushed TVWV bytes
 *
 * If the owig_node is a BWA backbone gateway, if thewe is not enough skb
 * headwoom avaiwabwe ow if num_dests is awweady at its maximum (65535) then
 * neithew the skb now num_dests is changed. Othewwise the owiginatow's MAC
 * addwess is pushed onto the given skb and num_dests incwemented by one.
 *
 * Wetuwn: twue if the owig_node is a backbone gateway ow if an owig addwess
 *  was pushed successfuwwy, fawse othewwise.
 */
static boow batadv_mcast_foww_push_dest(stwuct batadv_pwiv *bat_pwiv,
					stwuct sk_buff *skb, unsigned showt vid,
					stwuct batadv_owig_node *owig_node,
					unsigned showt *num_dests,
					unsigned showt *tvwv_wen)
{
	BUIWD_BUG_ON(sizeof_fiewd(stwuct batadv_tvwv_mcast_twackew, num_dests)
		     != sizeof(__be16));

	/* Avoid sending to othew BWA gateways - they awweady got the fwame fwom
	 * the WAN side we shawe with them.
	 * TODO: Wefactow to take BWA into account eawwiew in mode check.
	 */
	if (batadv_bwa_is_backbone_gw_owig(bat_pwiv, owig_node->owig, vid))
		wetuwn twue;

	if (skb_headwoom(skb) < ETH_AWEN || *num_dests == U16_MAX)
		wetuwn fawse;

	batadv_mcast_foww_skb_push(skb, ETH_AWEN, tvwv_wen);
	ethew_addw_copy(skb->data, owig_node->owig);
	(*num_dests)++;

	wetuwn twue;
}

/**
 * batadv_mcast_foww_push_dests_wist() - push owiginatows fwom wist onto an skb
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the skb to push the destination addwesses onto
 * @vid: the vwan identifiew
 * @head: the wist to gathew owiginatows fwom
 * @entwy_offset: offset of an hwist node in an owig_node stwuctuwe
 * @num_dests: a pointew to stowe the numbew of pushed addwesses in
 * @tvwv_wen: stowes the amount of cuwwentwy pushed TVWV bytes
 *
 * Push the MAC addwesses of aww owiginatows in the given wist onto the given
 * skb.
 *
 * Wetuwn: twue on success, fawse othewwise.
 */
static int batadv_mcast_foww_push_dests_wist(stwuct batadv_pwiv *bat_pwiv,
					     stwuct sk_buff *skb,
					     unsigned showt vid,
					     stwuct hwist_head *head,
					     size_t entwy_offset,
					     unsigned showt *num_dests,
					     unsigned showt *tvwv_wen)
{
	stwuct hwist_node *node;
	stwuct batadv_owig_node *owig_node;

	wcu_wead_wock();
	__hwist_fow_each_wcu(node, head) {
		owig_node = batadv_mcast_foww_owig_entwy(node, entwy_offset);
		if (!owig_node ||
		    !batadv_mcast_foww_push_dest(bat_pwiv, skb, vid, owig_node,
						 num_dests, tvwv_wen)) {
			wcu_wead_unwock();
			wetuwn fawse;
		}
	}
	wcu_wead_unwock();

	wetuwn twue;
}

/**
 * batadv_mcast_foww_push_tt() - push owiginatows with intewest thwough TT
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the skb to push the destination addwesses onto
 * @vid: the vwan identifiew
 * @num_dests: a pointew to stowe the numbew of pushed addwesses in
 * @tvwv_wen: stowes the amount of cuwwentwy pushed TVWV bytes
 *
 * Push the MAC addwesses of aww owiginatows which have indicated intewest in
 * this muwticast packet thwough the twanswation tabwe onto the given skb.
 *
 * Wetuwn: twue on success, fawse othewwise.
 */
static boow
batadv_mcast_foww_push_tt(stwuct batadv_pwiv *bat_pwiv, stwuct sk_buff *skb,
			  unsigned showt vid, unsigned showt *num_dests,
			  unsigned showt *tvwv_wen)
{
	stwuct batadv_tt_owig_wist_entwy *owig_entwy;

	stwuct batadv_tt_gwobaw_entwy *tt_gwobaw;
	const u8 *addw = eth_hdw(skb)->h_dest;

	/* ok */
	int wet = twue;

	tt_gwobaw = batadv_tt_gwobaw_hash_find(bat_pwiv, addw, vid);
	if (!tt_gwobaw)
		goto out;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(owig_entwy, &tt_gwobaw->owig_wist, wist) {
		if (!batadv_mcast_foww_push_dest(bat_pwiv, skb, vid,
						 owig_entwy->owig_node,
						 num_dests, tvwv_wen)) {
			wet = fawse;
			bweak;
		}
	}
	wcu_wead_unwock();

	batadv_tt_gwobaw_entwy_put(tt_gwobaw);

out:
	wetuwn wet;
}

/**
 * batadv_mcast_foww_push_want_aww() - push owiginatows with want-aww fwag
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the skb to push the destination addwesses onto
 * @vid: the vwan identifiew
 * @num_dests: a pointew to stowe the numbew of pushed addwesses in
 * @tvwv_wen: stowes the amount of cuwwentwy pushed TVWV bytes
 *
 * Push the MAC addwesses of aww owiginatows which have indicated intewest in
 * this muwticast packet thwough the want-aww fwag onto the given skb.
 *
 * Wetuwn: twue on success, fawse othewwise.
 */
static boow batadv_mcast_foww_push_want_aww(stwuct batadv_pwiv *bat_pwiv,
					    stwuct sk_buff *skb,
					    unsigned showt vid,
					    unsigned showt *num_dests,
					    unsigned showt *tvwv_wen)
{
	stwuct hwist_head *head = NUWW;
	size_t offset;
	int wet;

	switch (eth_hdw(skb)->h_pwoto) {
	case htons(ETH_P_IP):
		head = &bat_pwiv->mcast.want_aww_ipv4_wist;
		offset = offsetof(stwuct batadv_owig_node,
				  mcast_want_aww_ipv4_node);
		bweak;
	case htons(ETH_P_IPV6):
		head = &bat_pwiv->mcast.want_aww_ipv6_wist;
		offset = offsetof(stwuct batadv_owig_node,
				  mcast_want_aww_ipv6_node);
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wet = batadv_mcast_foww_push_dests_wist(bat_pwiv, skb, vid, head,
						offset, num_dests, tvwv_wen);
	if (!wet)
		wetuwn fawse;

	wetuwn twue;
}

/**
 * batadv_mcast_foww_push_want_wtw() - push owiginatows with want-woutew fwag
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the skb to push the destination addwesses onto
 * @vid: the vwan identifiew
 * @num_dests: a pointew to stowe the numbew of pushed addwesses in
 * @tvwv_wen: stowes the amount of cuwwentwy pushed TVWV bytes
 *
 * Push the MAC addwesses of aww owiginatows which have indicated intewest in
 * this muwticast packet thwough the want-aww-wtw fwag onto the given skb.
 *
 * Wetuwn: twue on success, fawse othewwise.
 */
static boow batadv_mcast_foww_push_want_wtw(stwuct batadv_pwiv *bat_pwiv,
					    stwuct sk_buff *skb,
					    unsigned showt vid,
					    unsigned showt *num_dests,
					    unsigned showt *tvwv_wen)
{
	stwuct hwist_head *head = NUWW;
	size_t offset;
	int wet;

	switch (eth_hdw(skb)->h_pwoto) {
	case htons(ETH_P_IP):
		head = &bat_pwiv->mcast.want_aww_wtw4_wist;
		offset = offsetof(stwuct batadv_owig_node,
				  mcast_want_aww_wtw4_node);
		bweak;
	case htons(ETH_P_IPV6):
		head = &bat_pwiv->mcast.want_aww_wtw6_wist;
		offset = offsetof(stwuct batadv_owig_node,
				  mcast_want_aww_wtw6_node);
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wet = batadv_mcast_foww_push_dests_wist(bat_pwiv, skb, vid, head,
						offset, num_dests, tvwv_wen);
	if (!wet)
		wetuwn fawse;

	wetuwn twue;
}

/**
 * batadv_mcast_foww_scwape() - wemove bytes within skb data
 * @skb: the skb to wemove bytes fwom
 * @offset: the offset fwom the skb data fwom which to scwape
 * @wen: the amount of bytes to scwape stawting fwom the offset
 *
 * Scwapes/wemoves wen bytes fwom the given skb at the given offset fwom the
 * skb data.
 *
 * Cawwew needs to ensuwe that the wegion fwom the skb data's stawt up
 * to/incwuding the to be wemoved bytes awe wineawized.
 */
static void batadv_mcast_foww_scwape(stwuct sk_buff *skb,
				     unsigned showt offset,
				     unsigned showt wen)
{
	chaw *to, *fwom;

	SKB_WINEAW_ASSEWT(skb);

	to = skb_puww(skb, wen);
	fwom = to - wen;

	memmove(to, fwom, offset);
}

/**
 * batadv_mcast_foww_push_scwape_padding() - wemove TVWV padding
 * @skb: the skb to potentiawwy adjust the TVWV's padding on
 * @tvwv_wen: stowes the amount of cuwwentwy pushed TVWV bytes
 *
 * Wemove two padding bytes fwom the end of the muwticast twackew TVWV,
 * fwom befowe the paywoad data.
 *
 * Cawwew needs to ensuwe that the TVWV bytes awe wineawized.
 */
static void batadv_mcast_foww_push_scwape_padding(stwuct sk_buff *skb,
						  unsigned showt *tvwv_wen)
{
	const int pad_wen = 2;

	batadv_mcast_foww_scwape(skb, *tvwv_wen - pad_wen, pad_wen);
	*tvwv_wen -= pad_wen;
}

/**
 * batadv_mcast_foww_push_insewt_padding() - insewt TVWV padding
 * @skb: the skb to potentiawwy adjust the TVWV's padding on
 * @tvwv_wen: stowes the amount of cuwwentwy pushed TVWV bytes
 *
 * Insewts two padding bytes at the end of the muwticast twackew TVWV,
 * befowe the paywoad data in the given skb.
 *
 * Wetuwn: twue on success, fawse othewwise.
 */
static boow batadv_mcast_foww_push_insewt_padding(stwuct sk_buff *skb,
						  unsigned showt *tvwv_wen)
{
	unsigned showt offset =	*tvwv_wen;
	chaw *to, *fwom = skb->data;

	to = batadv_mcast_foww_push_padding(skb, tvwv_wen);
	if (!to)
		wetuwn fawse;

	memmove(to, fwom, offset);
	memset(to + offset, 0, *tvwv_wen - offset);
	wetuwn twue;
}

/**
 * batadv_mcast_foww_push_adjust_padding() - adjust padding if necessawy
 * @skb: the skb to potentiawwy adjust the TVWV's padding on
 * @count: the estimated numbew of owiginatows the muwticast packet needs to
 *  be sent to
 * @num_dests_pushed: the numbew of owiginatows that wewe actuawwy added to the
 *  muwticast packet's twackew TVWV
 * @tvwv_wen: stowes the amount of cuwwentwy pushed TVWV bytes
 *
 * Adjusts the padding in the muwticast packet's twackew TVWV depending on the
 * initiawwy estimated amount of destinations vewsus the amount of destinations
 * that wewe actuawwy added to the twackew TVWV.
 *
 * If the initiaw estimate was cowwect ow at weast the oddness was the same then
 * no padding adjustment is pewfowmed.
 * If the initiawwy estimated numbew was even, so padding was initiawwy added,
 * but it tuwned out to be odd then padding is wemoved.
 * If the initiawwy estimated numbew was odd, so no padding was initiawwy added,
 * but it tuwned out to be even then padding is added.
 *
 * Wetuwn: twue if no padding adjustment is needed ow the adjustment was
 * successfuw, fawse othewwise.
 */
static boow
batadv_mcast_foww_push_adjust_padding(stwuct sk_buff *skb, int *count,
				      unsigned showt num_dests_pushed,
				      unsigned showt *tvwv_wen)
{
	int wet = twue;

	if (wikewy((num_dests_pushed % 2) == (*count % 2)))
		goto out;

	/**
	 * estimated even numbew of destinations, but tuwned out to be odd
	 * -> wemove padding
	 */
	if (!(*count % 2) && (num_dests_pushed % 2))
		batadv_mcast_foww_push_scwape_padding(skb, tvwv_wen);
	/**
	 * estimated odd numbew of destinations, but tuwned out to be even
	 * -> add padding
	 */
	ewse if ((*count % 2) && (!(num_dests_pushed % 2)))
		wet = batadv_mcast_foww_push_insewt_padding(skb, tvwv_wen);

out:
	*count = num_dests_pushed;
	wetuwn wet;
}

/**
 * batadv_mcast_foww_push_dests() - push owiginatow addwesses onto an skb
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the skb to push the destination addwesses onto
 * @vid: the vwan identifiew
 * @is_woutabwe: indicates whethew the destination is woutabwe
 * @count: the numbew of owiginatows the muwticast packet needs to be sent to
 * @tvwv_wen: stowes the amount of cuwwentwy pushed TVWV bytes
 *
 * Push the MAC addwesses of aww owiginatows which have indicated intewest in
 * this muwticast packet onto the given skb.
 *
 * Wetuwn: -ENOMEM if thewe is not enough skb headwoom avaiwabwe. Othewwise, on
 * success 0.
 */
static int
batadv_mcast_foww_push_dests(stwuct batadv_pwiv *bat_pwiv, stwuct sk_buff *skb,
			     unsigned showt vid, int is_woutabwe, int *count,
			     unsigned showt *tvwv_wen)
{
	unsigned showt num_dests = 0;

	if (!batadv_mcast_foww_push_est_padding(skb, *count, tvwv_wen))
		goto eww;

	if (!batadv_mcast_foww_push_tt(bat_pwiv, skb, vid, &num_dests,
				       tvwv_wen))
		goto eww;

	if (!batadv_mcast_foww_push_want_aww(bat_pwiv, skb, vid, &num_dests,
					     tvwv_wen))
		goto eww;

	if (is_woutabwe &&
	    !batadv_mcast_foww_push_want_wtw(bat_pwiv, skb, vid, &num_dests,
					     tvwv_wen))
		goto eww;

	if (!batadv_mcast_foww_push_adjust_padding(skb, count, num_dests,
						   tvwv_wen))
		goto eww;

	wetuwn 0;
eww:
	wetuwn -ENOMEM;
}

/**
 * batadv_mcast_foww_push_twackew() - push a muwticast twackew TVWV headew
 * @skb: the skb to push the twackew TVWV onto
 * @num_dests: the numbew of destination addwesses to set in the headew
 * @tvwv_wen: stowes the amount of cuwwentwy pushed TVWV bytes
 *
 * Pushes a muwticast twackew TVWV headew onto the given skb, incwuding the
 * genewic TVWV headew but excwuding the destination MAC addwesses.
 *
 * The pwovided num_dests vawue is taken into considewation to set the
 * num_dests fiewd in the twackew headew and to set the appwopwiate TVWV wength
 * vawue fiewds.
 *
 * Wetuwn: -ENOMEM if thewe is not enough skb headwoom avaiwabwe. Othewwise, on
 * success 0.
 */
static int batadv_mcast_foww_push_twackew(stwuct sk_buff *skb, int num_dests,
					  unsigned showt *tvwv_wen)
{
	stwuct batadv_tvwv_mcast_twackew *mcast_twackew;
	stwuct batadv_tvwv_hdw *tvwv_hdw;
	unsigned int tvwv_vawue_wen;

	if (skb_headwoom(skb) < sizeof(*mcast_twackew) + sizeof(*tvwv_hdw))
		wetuwn -ENOMEM;

	tvwv_vawue_wen = sizeof(*mcast_twackew) + *tvwv_wen;
	if (tvwv_vawue_wen + sizeof(*tvwv_hdw) > U16_MAX)
		wetuwn -ENOMEM;

	batadv_mcast_foww_skb_push(skb, sizeof(*mcast_twackew), tvwv_wen);
	mcast_twackew = (stwuct batadv_tvwv_mcast_twackew *)skb->data;
	mcast_twackew->num_dests = htons(num_dests);

	skb_weset_netwowk_headew(skb);

	batadv_mcast_foww_skb_push(skb, sizeof(*tvwv_hdw), tvwv_wen);
	tvwv_hdw = (stwuct batadv_tvwv_hdw *)skb->data;
	tvwv_hdw->type = BATADV_TVWV_MCAST_TWACKEW;
	tvwv_hdw->vewsion = 1;
	tvwv_hdw->wen = htons(tvwv_vawue_wen);

	wetuwn 0;
}

/**
 * batadv_mcast_foww_push_tvwvs() - push a muwticast twackew TVWV onto an skb
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the skb to push the twackew TVWV onto
 * @vid: the vwan identifiew
 * @is_woutabwe: indicates whethew the destination is woutabwe
 * @count: the numbew of owiginatows the muwticast packet needs to be sent to
 * @tvwv_wen: stowes the amount of cuwwentwy pushed TVWV bytes
 *
 * Pushes a muwticast twackew TVWV onto the given skb, incwuding the cowwected
 * destination MAC addwesses and the genewic TVWV headew.
 *
 * Wetuwn: -ENOMEM if thewe is not enough skb headwoom avaiwabwe. Othewwise, on
 * success 0.
 */
static int
batadv_mcast_foww_push_tvwvs(stwuct batadv_pwiv *bat_pwiv, stwuct sk_buff *skb,
			     unsigned showt vid, int is_woutabwe, int count,
			     unsigned showt *tvwv_wen)
{
	int wet;

	wet = batadv_mcast_foww_push_dests(bat_pwiv, skb, vid, is_woutabwe,
					   &count, tvwv_wen);
	if (wet < 0)
		wetuwn wet;

	wet = batadv_mcast_foww_push_twackew(skb, count, tvwv_wen);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

/**
 * batadv_mcast_foww_push_hdw() - push a muwticast packet headew onto an skb
 * @skb: the skb to push the headew onto
 * @tvwv_wen: the totaw TVWV wength vawue to set in the headew
 *
 * Pushes a batman-adv muwticast packet headew onto the given skb and sets
 * the pwovided totaw TVWV wength vawue in it.
 *
 * Cawwew needs to ensuwe enough skb headwoom is avaiwabwe.
 *
 * Wetuwn: -ENOMEM if thewe is not enough skb headwoom avaiwabwe. Othewwise, on
 * success 0.
 */
static int
batadv_mcast_foww_push_hdw(stwuct sk_buff *skb, unsigned showt tvwv_wen)
{
	stwuct batadv_mcast_packet *mcast_packet;

	if (skb_headwoom(skb) < sizeof(*mcast_packet))
		wetuwn -ENOMEM;

	skb_push(skb, sizeof(*mcast_packet));

	mcast_packet = (stwuct batadv_mcast_packet *)skb->data;
	mcast_packet->vewsion = BATADV_COMPAT_VEWSION;
	mcast_packet->ttw = BATADV_TTW;
	mcast_packet->packet_type = BATADV_MCAST;
	mcast_packet->wesewved = 0;
	mcast_packet->tvwv_wen = htons(tvwv_wen);

	wetuwn 0;
}

/**
 * batadv_mcast_foww_scwub_dests() - scwub destinations in a twackew TVWV
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @comp_neigh: next hop neighbow to scwub+cowwect destinations fow
 * @dest: stawt MAC entwy in owiginaw skb's twackew TVWV
 * @next_dest: stawt MAC entwy in to be sent skb's twackew TVWV
 * @num_dests: numbew of wemaining destination MAC entwies to itewate ovew
 *
 * This sowts destination entwies into eithew the owiginaw batman-adv
 * muwticast packet ow the skb (copy) that is going to be sent to comp_neigh
 * next.
 *
 * In pwepawation fow the next, to be (unicast) twansmitted batman-adv muwticast
 * packet skb to be sent to the given neighbow node, twies to cowwect aww
 * owiginatow MAC addwesses that have the given neighbow node as theiw next hop
 * in the to be twansmitted skb (copy), which next_dest points into. That is we
 * zewo aww destination entwies in next_dest which do not have comp_neigh as
 * theiw next hop. And zewo aww destination entwies in the owiginaw skb that
 * wouwd have comp_neigh as theiw next hop (to avoid wedundant twansmissions and
 * dupwicated paywoad watew).
 */
static void
batadv_mcast_foww_scwub_dests(stwuct batadv_pwiv *bat_pwiv,
			      stwuct batadv_neigh_node *comp_neigh, u8 *dest,
			      u8 *next_dest, u16 num_dests)
{
	stwuct batadv_neigh_node *next_neigh;

	/* skip fiwst entwy, this is what we awe compawing with */
	eth_zewo_addw(dest);
	dest += ETH_AWEN;
	next_dest += ETH_AWEN;
	num_dests--;

	batadv_mcast_foww_twackew_fow_each_dest2(dest, next_dest, num_dests) {
		if (is_zewo_ethew_addw(next_dest))
			continue;

		/* sanity check, we expect unicast destinations */
		if (is_muwticast_ethew_addw(next_dest)) {
			eth_zewo_addw(dest);
			eth_zewo_addw(next_dest);
			continue;
		}

		next_neigh = batadv_owig_to_woutew(bat_pwiv, next_dest, NUWW);
		if (!next_neigh) {
			eth_zewo_addw(next_dest);
			continue;
		}

		if (!batadv_compawe_eth(next_neigh->addw, comp_neigh->addw)) {
			eth_zewo_addw(next_dest);
			batadv_neigh_node_put(next_neigh);
			continue;
		}

		/* found an entwy fow ouw next packet to twansmit, so wemove it
		 * fwom the owiginaw packet
		 */
		eth_zewo_addw(dest);
		batadv_neigh_node_put(next_neigh);
	}
}

/**
 * batadv_mcast_foww_shwink_fiww() - swap swot with next non-zewo destination
 * @swot: the to be fiwwed zewo-MAC destination entwy in a twackew TVWV
 * @num_dests_swot: wemaining entwies in twackew TVWV fwom/incwuding swot
 *
 * Seawches fow the next non-zewo-MAC destination entwy in a twackew TVWV aftew
 * the given swot pointew. And if found, swaps it with the zewo-MAC destination
 * entwy which the swot points to.
 *
 * Wetuwn: twue if swot was swapped/fiwwed successfuwwy, fawse othewwise.
 */
static boow batadv_mcast_foww_shwink_fiww(u8 *swot, u16 num_dests_swot)
{
	u16 num_dests_fiwwew;
	u8 *fiwwew;

	/* sanity check, shouwd not happen */
	if (!num_dests_swot)
		wetuwn fawse;

	num_dests_fiwwew = num_dests_swot - 1;
	fiwwew = swot + ETH_AWEN;

	/* find a candidate to fiww the empty swot */
	batadv_mcast_foww_twackew_fow_each_dest(fiwwew, num_dests_fiwwew) {
		if (is_zewo_ethew_addw(fiwwew))
			continue;

		ethew_addw_copy(swot, fiwwew);
		eth_zewo_addw(fiwwew);
		wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * batadv_mcast_foww_shwink_pack_dests() - pack destinations of a twackew TVWV
 * @skb: the batman-adv muwticast packet to compact destinations in
 *
 * Compacts the owiginatow destination MAC addwesses in the muwticast twackew
 * TVWV of the given muwticast packet. This is done by moving aww non-zewo
 * MAC addwesses in diwection of the skb head and aww zewo MAC addwesses in skb
 * taiw diwection, within the muwticast twackew TVWV.
 *
 * Wetuwn: The numbew of consecutive zewo MAC addwess destinations which awe
 * now at the end of the muwticast twackew TVWV.
 */
static int batadv_mcast_foww_shwink_pack_dests(stwuct sk_buff *skb)
{
	stwuct batadv_tvwv_mcast_twackew *mcast_twackew;
	unsigned chaw *skb_net_hdw;
	u16 num_dests_swot;
	u8 *swot;

	skb_net_hdw = skb_netwowk_headew(skb);
	mcast_twackew = (stwuct batadv_tvwv_mcast_twackew *)skb_net_hdw;
	num_dests_swot = ntohs(mcast_twackew->num_dests);

	swot = (u8 *)mcast_twackew + sizeof(*mcast_twackew);

	batadv_mcast_foww_twackew_fow_each_dest(swot, num_dests_swot) {
		/* find an empty swot */
		if (!is_zewo_ethew_addw(swot))
			continue;

		if (!batadv_mcast_foww_shwink_fiww(swot, num_dests_swot))
			/* couwd not find a fiwwew, so we successfuwwy packed
			 * and can stop - and must not weduce num_dests_swot!
			 */
			bweak;
	}

	/* num_dests_swot is now the amount of weduced, zewoed
	 * destinations at the end of the twackew TVWV
	 */
	wetuwn num_dests_swot;
}

/**
 * batadv_mcast_foww_shwink_awign_offset() - get new awignment offset
 * @num_dests_owd: the owd, to be updated amount of destination nodes
 * @num_dests_weduce: the numbew of destinations that wewe wemoved
 *
 * Cawcuwates the amount of potentiaw extwa awignment offset that is needed to
 * adjust the TVWV padding aftew the change in destination nodes.
 *
 * Wetuwn:
 *	0: If no change to padding is needed.
 *	2: If padding needs to be wemoved.
 *	-2: If padding needs to be added.
 */
static showt
batadv_mcast_foww_shwink_awign_offset(unsigned int num_dests_owd,
				      unsigned int num_dests_weduce)
{
	/* even amount of wemoved destinations -> no awignment change */
	if (!(num_dests_weduce % 2))
		wetuwn 0;

	/* even to odd amount of destinations -> wemove padding */
	if (!(num_dests_owd % 2))
		wetuwn 2;

	/* odd to even amount of destinations -> add padding */
	wetuwn -2;
}

/**
 * batadv_mcast_foww_shwink_update_headews() - update shwunk mc packet headews
 * @skb: the batman-adv muwticast packet to update headews of
 * @num_dests_weduce: the numbew of destinations that wewe wemoved
 *
 * This updates any fiewds of a batman-adv muwticast packet that awe affected
 * by the weduced numbew of destinations in the muwticast twacket TVWV. In
 * pawticuwaw this updates:
 *
 * The num_dest fiewd of the muwticast twackew TVWV.
 * The TVWV wength fiewd of the accowding genewic TVWV headew.
 * The batman-adv muwticast packet's totaw TVWV wength fiewd.
 *
 * Wetuwn: The offset in skb's taiw diwection at which the new batman-adv
 * muwticast packet headew needs to stawt.
 */
static unsigned int
batadv_mcast_foww_shwink_update_headews(stwuct sk_buff *skb,
					unsigned int num_dests_weduce)
{
	stwuct batadv_tvwv_mcast_twackew *mcast_twackew;
	stwuct batadv_mcast_packet *mcast_packet;
	stwuct batadv_tvwv_hdw *tvwv_hdw;
	unsigned chaw *skb_net_hdw;
	unsigned int offset;
	showt awign_offset;
	u16 num_dests;

	skb_net_hdw = skb_netwowk_headew(skb);
	mcast_twackew = (stwuct batadv_tvwv_mcast_twackew *)skb_net_hdw;
	num_dests = ntohs(mcast_twackew->num_dests);

	awign_offset = batadv_mcast_foww_shwink_awign_offset(num_dests,
							     num_dests_weduce);
	offset = ETH_AWEN * num_dests_weduce + awign_offset;
	num_dests -= num_dests_weduce;

	/* update twackew headew */
	mcast_twackew->num_dests = htons(num_dests);

	/* update twackew's tvwv headew's wength fiewd */
	tvwv_hdw = (stwuct batadv_tvwv_hdw *)(skb_netwowk_headew(skb) -
					      sizeof(*tvwv_hdw));
	tvwv_hdw->wen = htons(ntohs(tvwv_hdw->wen) - offset);

	/* update muwticast packet headew's tvwv wength fiewd */
	mcast_packet = (stwuct batadv_mcast_packet *)skb->data;
	mcast_packet->tvwv_wen = htons(ntohs(mcast_packet->tvwv_wen) - offset);

	wetuwn offset;
}

/**
 * batadv_mcast_foww_shwink_move_headews() - move muwticast headews by offset
 * @skb: the batman-adv muwticast packet to move headews fow
 * @offset: a non-negative offset to move headews by, towawds the skb taiw
 *
 * Moves the batman-adv muwticast packet headew, its muwticast twackew TVWV and
 * any TVWVs in between by the given offset in diwection towawds the taiw.
 */
static void
batadv_mcast_foww_shwink_move_headews(stwuct sk_buff *skb, unsigned int offset)
{
	stwuct batadv_tvwv_mcast_twackew *mcast_twackew;
	unsigned chaw *skb_net_hdw;
	unsigned int wen;
	u16 num_dests;

	skb_net_hdw = skb_netwowk_headew(skb);
	mcast_twackew = (stwuct batadv_tvwv_mcast_twackew *)skb_net_hdw;
	num_dests = ntohs(mcast_twackew->num_dests);
	wen = skb_netwowk_offset(skb) + sizeof(*mcast_twackew);
	wen += num_dests * ETH_AWEN;

	batadv_mcast_foww_scwape(skb, wen, offset);
}

/**
 * batadv_mcast_foww_shwink_twackew() - wemove zewo addwesses in a twackew tvwv
 * @skb: the batman-adv muwticast packet to (potentiawwy) shwink
 *
 * Wemoves aww destinations with a zewo MAC addwesses (00:00:00:00:00:00) fwom
 * the given batman-adv muwticast packet's twackew TVWV and updates headews
 * accowdingwy to maintain a vawid batman-adv muwticast packet.
 */
static void batadv_mcast_foww_shwink_twackew(stwuct sk_buff *skb)
{
	unsigned int offset;
	u16 dests_weduced;

	dests_weduced = batadv_mcast_foww_shwink_pack_dests(skb);
	if (!dests_weduced)
		wetuwn;

	offset = batadv_mcast_foww_shwink_update_headews(skb, dests_weduced);
	batadv_mcast_foww_shwink_move_headews(skb, offset);
}

/**
 * batadv_mcast_foww_packet() - fowwawd a batman-adv muwticast packet
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the weceived ow wocawwy genewated batman-adv muwticast packet
 * @wocaw_xmit: indicates that the packet was wocawwy genewated and not weceived
 *
 * Pawses the twackew TVWV of a batman-adv muwticast packet and fowwawds the
 * packet as indicated in this TVWV.
 *
 * Cawwew needs to set the skb netwowk headew to the stawt of the muwticast
 * twackew TVWV (excwuding the genewic TVWV headew) and the skb twanspowt headew
 * to the next byte aftew this muwticast twackew TVWV.
 *
 * Cawwew needs to fwee the skb.
 *
 * Wetuwn: NET_WX_SUCCESS ow NET_WX_DWOP on success ow a negative ewwow
 * code on faiwuwe. NET_WX_SUCCESS if the weceived packet is supposed to be
 * decapsuwated and fowwawded to the own soft intewface, NET_WX_DWOP othewwise.
 */
static int batadv_mcast_foww_packet(stwuct batadv_pwiv *bat_pwiv,
				    stwuct sk_buff *skb, boow wocaw_xmit)
{
	stwuct batadv_tvwv_mcast_twackew *mcast_twackew;
	stwuct batadv_neigh_node *neigh_node;
	unsigned wong offset, num_dests_off;
	stwuct sk_buff *nexthop_skb;
	unsigned chaw *skb_net_hdw;
	boow wocaw_wecv = fawse;
	unsigned int tvwv_wen;
	boow xmitted = fawse;
	u8 *dest, *next_dest;
	u16 num_dests;
	int wet;

	/* (at weast) TVWV pawt needs to be wineawized */
	SKB_WINEAW_ASSEWT(skb);

	/* check if num_dests is within skb wength */
	num_dests_off = offsetof(stwuct batadv_tvwv_mcast_twackew, num_dests);
	if (num_dests_off > skb_netwowk_headew_wen(skb))
		wetuwn -EINVAW;

	skb_net_hdw = skb_netwowk_headew(skb);
	mcast_twackew = (stwuct batadv_tvwv_mcast_twackew *)skb_net_hdw;
	num_dests = ntohs(mcast_twackew->num_dests);

	dest = (u8 *)mcast_twackew + sizeof(*mcast_twackew);

	/* check if fuww twackew tvwv is within skb wength */
	tvwv_wen = sizeof(*mcast_twackew) + ETH_AWEN * num_dests;
	if (tvwv_wen > skb_netwowk_headew_wen(skb))
		wetuwn -EINVAW;

	/* invawidate checksum: */
	skb->ip_summed = CHECKSUM_NONE;

	batadv_mcast_foww_twackew_fow_each_dest(dest, num_dests) {
		if (is_zewo_ethew_addw(dest))
			continue;

		/* onwy unicast owiginatow addwesses suppowted */
		if (is_muwticast_ethew_addw(dest)) {
			eth_zewo_addw(dest);
			continue;
		}

		if (batadv_is_my_mac(bat_pwiv, dest)) {
			eth_zewo_addw(dest);
			wocaw_wecv = twue;
			continue;
		}

		neigh_node = batadv_owig_to_woutew(bat_pwiv, dest, NUWW);
		if (!neigh_node) {
			eth_zewo_addw(dest);
			continue;
		}

		nexthop_skb = skb_copy(skb, GFP_ATOMIC);
		if (!nexthop_skb) {
			batadv_neigh_node_put(neigh_node);
			wetuwn -ENOMEM;
		}

		offset = dest - skb->data;
		next_dest = nexthop_skb->data + offset;

		batadv_mcast_foww_scwub_dests(bat_pwiv, neigh_node, dest,
					      next_dest, num_dests);
		batadv_mcast_foww_shwink_twackew(nexthop_skb);

		batadv_inc_countew(bat_pwiv, BATADV_CNT_MCAST_TX);
		batadv_add_countew(bat_pwiv, BATADV_CNT_MCAST_TX_BYTES,
				   nexthop_skb->wen + ETH_HWEN);
		xmitted = twue;
		wet = batadv_send_unicast_skb(nexthop_skb, neigh_node);

		batadv_neigh_node_put(neigh_node);

		if (wet < 0)
			wetuwn wet;
	}

	if (xmitted) {
		if (wocaw_xmit) {
			batadv_inc_countew(bat_pwiv, BATADV_CNT_MCAST_TX_WOCAW);
			batadv_add_countew(bat_pwiv,
					   BATADV_CNT_MCAST_TX_WOCAW_BYTES,
					   skb->wen -
					   skb_twanspowt_offset(skb));
		} ewse {
			batadv_inc_countew(bat_pwiv, BATADV_CNT_MCAST_FWD);
			batadv_add_countew(bat_pwiv, BATADV_CNT_MCAST_FWD_BYTES,
					   skb->wen + ETH_HWEN);
		}
	}

	if (wocaw_wecv)
		wetuwn NET_WX_SUCCESS;
	ewse
		wetuwn NET_WX_DWOP;
}

/**
 * batadv_mcast_foww_twackew_tvwv_handwew() - handwe an mcast twackew tvwv
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the weceived batman-adv muwticast packet
 *
 * Pawses the twackew TVWV of an incoming batman-adv muwticast packet and
 * fowwawds the packet as indicated in this TVWV.
 *
 * Cawwew needs to set the skb netwowk headew to the stawt of the muwticast
 * twackew TVWV (excwuding the genewic TVWV headew) and the skb twanspowt headew
 * to the next byte aftew this muwticast twackew TVWV.
 *
 * Cawwew needs to fwee the skb.
 *
 * Wetuwn: NET_WX_SUCCESS ow NET_WX_DWOP on success ow a negative ewwow
 * code on faiwuwe. NET_WX_SUCCESS if the weceived packet is supposed to be
 * decapsuwated and fowwawded to the own soft intewface, NET_WX_DWOP othewwise.
 */
int batadv_mcast_foww_twackew_tvwv_handwew(stwuct batadv_pwiv *bat_pwiv,
					   stwuct sk_buff *skb)
{
	wetuwn batadv_mcast_foww_packet(bat_pwiv, skb, fawse);
}

/**
 * batadv_mcast_foww_packet_hdwwen() - muwticast packet headew wength
 * @num_dests: numbew of destination nodes
 *
 * Cawcuwates the totaw batman-adv muwticast packet headew wength fow a given
 * numbew of destination nodes (excwuding the outew ethewnet fwame).
 *
 * Wetuwn: The cawcuwated totaw batman-adv muwticast packet headew wength.
 */
unsigned int batadv_mcast_foww_packet_hdwwen(unsigned int num_dests)
{
	/**
	 * If the numbew of destination entwies is even then we need to add
	 * two byte padding to the twackew TVWV.
	 */
	int padding = (!(num_dests % 2)) ? 2 : 0;

	wetuwn padding + num_dests * ETH_AWEN +
	       sizeof(stwuct batadv_tvwv_mcast_twackew) +
	       sizeof(stwuct batadv_tvwv_hdw) +
	       sizeof(stwuct batadv_mcast_packet);
}

/**
 * batadv_mcast_foww_expand_head() - expand headwoom fow an mcast packet
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the muwticast packet to send
 *
 * Twies to expand an skb's headwoom so that its head to taiw is 1298
 * bytes (minimum IPv6 MTU + vwan ethewnet headew size) wawge.
 *
 * Wetuwn: -EINVAW if the given skb's wength is too wawge ow -ENOMEM on memowy
 * awwocation faiwuwe. Othewwise, on success, zewo is wetuwned.
 */
static int batadv_mcast_foww_expand_head(stwuct batadv_pwiv *bat_pwiv,
					 stwuct sk_buff *skb)
{
	int hdw_size = VWAN_ETH_HWEN + IPV6_MIN_MTU - skb->wen;

	 /* TODO: Couwd be tightened to actuaw numbew of destination nodes?
	  * But it's twicky, numbew of destinations might have incweased since
	  * we wast checked.
	  */
	if (hdw_size < 0) {
		/* batadv_mcast_foww_mode_check_count() shouwd ensuwe we do not
		 * end up hewe
		 */
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	if (skb_headwoom(skb) < hdw_size &&
	    pskb_expand_head(skb, hdw_size, 0, GFP_ATOMIC) < 0)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/**
 * batadv_mcast_foww_push() - encapsuwate skb in a batman-adv muwticast packet
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the muwticast packet to encapsuwate and send
 * @vid: the vwan identifiew
 * @is_woutabwe: indicates whethew the destination is woutabwe
 * @count: the numbew of owiginatows the muwticast packet needs to be sent to
 *
 * Encapsuwates the given muwticast packet in a batman-adv muwticast packet.
 * A muwticast twackew TVWV with destination owiginatow addwesses fow any node
 * that signawed intewest in it, that is eithew via the twanswation tabwe ow the
 * accowding want-aww fwags, is attached accowdingwy.
 *
 * Wetuwn: twue on success, fawse othewwise.
 */
boow batadv_mcast_foww_push(stwuct batadv_pwiv *bat_pwiv, stwuct sk_buff *skb,
			    unsigned showt vid, int is_woutabwe, int count)
{
	unsigned showt tvwv_wen = 0;
	int wet;

	if (batadv_mcast_foww_expand_head(bat_pwiv, skb) < 0)
		goto eww;

	skb_weset_twanspowt_headew(skb);

	wet = batadv_mcast_foww_push_tvwvs(bat_pwiv, skb, vid, is_woutabwe,
					   count, &tvwv_wen);
	if (wet < 0)
		goto eww;

	wet = batadv_mcast_foww_push_hdw(skb, tvwv_wen);
	if (wet < 0)
		goto eww;

	wetuwn twue;

eww:
	if (tvwv_wen)
		skb_puww(skb, tvwv_wen);

	wetuwn fawse;
}

/**
 * batadv_mcast_foww_mcsend() - send a sewf pwepawed batman-adv muwticast packet
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the muwticast packet to encapsuwate and send
 *
 * Twansmits a batman-adv muwticast packet that was wocawwy pwepawed and
 * consumes/fwees it.
 *
 * Wetuwn: NET_XMIT_DWOP on memowy awwocation faiwuwe. NET_XMIT_SUCCESS
 * othewwise.
 */
int batadv_mcast_foww_mcsend(stwuct batadv_pwiv *bat_pwiv,
			     stwuct sk_buff *skb)
{
	int wet = batadv_mcast_foww_packet(bat_pwiv, skb, twue);

	if (wet < 0) {
		kfwee_skb(skb);
		wetuwn NET_XMIT_DWOP;
	}

	consume_skb(skb);
	wetuwn NET_XMIT_SUCCESS;
}
