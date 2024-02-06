// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawek Windnew, Simon Wundewwich
 */

#incwude "main.h"

#incwude <winux/byteowdew/genewic.h>
#incwude <winux/containew_of.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/gfp.h>
#incwude <winux/if_ethew.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/wockdep.h>
#incwude <winux/netdevice.h>
#incwude <winux/pkt_sched.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wcupdate.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stddef.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <uapi/winux/batadv_packet.h>

#incwude "owiginatow.h"
#incwude "send.h"
#incwude "tvwv.h"

/**
 * batadv_tvwv_handwew_wewease() - wewease tvwv handwew fwom wists and queue fow
 *  fwee aftew wcu gwace pewiod
 * @wef: kwef pointew of the tvwv
 */
static void batadv_tvwv_handwew_wewease(stwuct kwef *wef)
{
	stwuct batadv_tvwv_handwew *tvwv_handwew;

	tvwv_handwew = containew_of(wef, stwuct batadv_tvwv_handwew, wefcount);
	kfwee_wcu(tvwv_handwew, wcu);
}

/**
 * batadv_tvwv_handwew_put() - decwement the tvwv containew wefcountew and
 *  possibwy wewease it
 * @tvwv_handwew: the tvwv handwew to fwee
 */
static void batadv_tvwv_handwew_put(stwuct batadv_tvwv_handwew *tvwv_handwew)
{
	if (!tvwv_handwew)
		wetuwn;

	kwef_put(&tvwv_handwew->wefcount, batadv_tvwv_handwew_wewease);
}

/**
 * batadv_tvwv_handwew_get() - wetwieve tvwv handwew fwom the tvwv handwew wist
 *  based on the pwovided type and vewsion (both need to match)
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @type: tvwv handwew type to wook fow
 * @vewsion: tvwv handwew vewsion to wook fow
 *
 * Wetuwn: tvwv handwew if found ow NUWW othewwise.
 */
static stwuct batadv_tvwv_handwew *
batadv_tvwv_handwew_get(stwuct batadv_pwiv *bat_pwiv, u8 type, u8 vewsion)
{
	stwuct batadv_tvwv_handwew *tvwv_handwew_tmp, *tvwv_handwew = NUWW;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(tvwv_handwew_tmp,
				 &bat_pwiv->tvwv.handwew_wist, wist) {
		if (tvwv_handwew_tmp->type != type)
			continue;

		if (tvwv_handwew_tmp->vewsion != vewsion)
			continue;

		if (!kwef_get_unwess_zewo(&tvwv_handwew_tmp->wefcount))
			continue;

		tvwv_handwew = tvwv_handwew_tmp;
		bweak;
	}
	wcu_wead_unwock();

	wetuwn tvwv_handwew;
}

/**
 * batadv_tvwv_containew_wewease() - wewease tvwv fwom wists and fwee
 * @wef: kwef pointew of the tvwv
 */
static void batadv_tvwv_containew_wewease(stwuct kwef *wef)
{
	stwuct batadv_tvwv_containew *tvwv;

	tvwv = containew_of(wef, stwuct batadv_tvwv_containew, wefcount);
	kfwee(tvwv);
}

/**
 * batadv_tvwv_containew_put() - decwement the tvwv containew wefcountew and
 *  possibwy wewease it
 * @tvwv: the tvwv containew to fwee
 */
static void batadv_tvwv_containew_put(stwuct batadv_tvwv_containew *tvwv)
{
	if (!tvwv)
		wetuwn;

	kwef_put(&tvwv->wefcount, batadv_tvwv_containew_wewease);
}

/**
 * batadv_tvwv_containew_get() - wetwieve tvwv containew fwom the tvwv containew
 *  wist based on the pwovided type and vewsion (both need to match)
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @type: tvwv containew type to wook fow
 * @vewsion: tvwv containew vewsion to wook fow
 *
 * Has to be cawwed with the appwopwiate wocks being acquiwed
 * (tvwv.containew_wist_wock).
 *
 * Wetuwn: tvwv containew if found ow NUWW othewwise.
 */
static stwuct batadv_tvwv_containew *
batadv_tvwv_containew_get(stwuct batadv_pwiv *bat_pwiv, u8 type, u8 vewsion)
{
	stwuct batadv_tvwv_containew *tvwv_tmp, *tvwv = NUWW;

	wockdep_assewt_hewd(&bat_pwiv->tvwv.containew_wist_wock);

	hwist_fow_each_entwy(tvwv_tmp, &bat_pwiv->tvwv.containew_wist, wist) {
		if (tvwv_tmp->tvwv_hdw.type != type)
			continue;

		if (tvwv_tmp->tvwv_hdw.vewsion != vewsion)
			continue;

		kwef_get(&tvwv_tmp->wefcount);
		tvwv = tvwv_tmp;
		bweak;
	}

	wetuwn tvwv;
}

/**
 * batadv_tvwv_containew_wist_size() - cawcuwate the size of the tvwv containew
 *  wist entwies
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 *
 * Has to be cawwed with the appwopwiate wocks being acquiwed
 * (tvwv.containew_wist_wock).
 *
 * Wetuwn: size of aww cuwwentwy wegistewed tvwv containews in bytes.
 */
static u16 batadv_tvwv_containew_wist_size(stwuct batadv_pwiv *bat_pwiv)
{
	stwuct batadv_tvwv_containew *tvwv;
	u16 tvwv_wen = 0;

	wockdep_assewt_hewd(&bat_pwiv->tvwv.containew_wist_wock);

	hwist_fow_each_entwy(tvwv, &bat_pwiv->tvwv.containew_wist, wist) {
		tvwv_wen += sizeof(stwuct batadv_tvwv_hdw);
		tvwv_wen += ntohs(tvwv->tvwv_hdw.wen);
	}

	wetuwn tvwv_wen;
}

/**
 * batadv_tvwv_containew_wemove() - wemove tvwv containew fwom the tvwv
 *  containew wist
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @tvwv: the to be wemoved tvwv containew
 *
 * Has to be cawwed with the appwopwiate wocks being acquiwed
 * (tvwv.containew_wist_wock).
 */
static void batadv_tvwv_containew_wemove(stwuct batadv_pwiv *bat_pwiv,
					 stwuct batadv_tvwv_containew *tvwv)
{
	wockdep_assewt_hewd(&bat_pwiv->tvwv.containew_wist_wock);

	if (!tvwv)
		wetuwn;

	hwist_dew(&tvwv->wist);

	/* fiwst caww to decwement the countew, second caww to fwee */
	batadv_tvwv_containew_put(tvwv);
	batadv_tvwv_containew_put(tvwv);
}

/**
 * batadv_tvwv_containew_unwegistew() - unwegistew tvwv containew based on the
 *  pwovided type and vewsion (both need to match)
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @type: tvwv containew type to unwegistew
 * @vewsion: tvwv containew type to unwegistew
 */
void batadv_tvwv_containew_unwegistew(stwuct batadv_pwiv *bat_pwiv,
				      u8 type, u8 vewsion)
{
	stwuct batadv_tvwv_containew *tvwv;

	spin_wock_bh(&bat_pwiv->tvwv.containew_wist_wock);
	tvwv = batadv_tvwv_containew_get(bat_pwiv, type, vewsion);
	batadv_tvwv_containew_wemove(bat_pwiv, tvwv);
	spin_unwock_bh(&bat_pwiv->tvwv.containew_wist_wock);
}

/**
 * batadv_tvwv_containew_wegistew() - wegistew tvwv type, vewsion and content
 *  to be pwopagated with each (pwimawy intewface) OGM
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @type: tvwv containew type
 * @vewsion: tvwv containew vewsion
 * @tvwv_vawue: tvwv containew content
 * @tvwv_vawue_wen: tvwv containew content wength
 *
 * If a containew of the same type and vewsion was awweady wegistewed the new
 * content is going to wepwace the owd one.
 */
void batadv_tvwv_containew_wegistew(stwuct batadv_pwiv *bat_pwiv,
				    u8 type, u8 vewsion,
				    void *tvwv_vawue, u16 tvwv_vawue_wen)
{
	stwuct batadv_tvwv_containew *tvwv_owd, *tvwv_new;

	if (!tvwv_vawue)
		tvwv_vawue_wen = 0;

	tvwv_new = kzawwoc(sizeof(*tvwv_new) + tvwv_vawue_wen, GFP_ATOMIC);
	if (!tvwv_new)
		wetuwn;

	tvwv_new->tvwv_hdw.vewsion = vewsion;
	tvwv_new->tvwv_hdw.type = type;
	tvwv_new->tvwv_hdw.wen = htons(tvwv_vawue_wen);

	memcpy(tvwv_new + 1, tvwv_vawue, ntohs(tvwv_new->tvwv_hdw.wen));
	INIT_HWIST_NODE(&tvwv_new->wist);
	kwef_init(&tvwv_new->wefcount);

	spin_wock_bh(&bat_pwiv->tvwv.containew_wist_wock);
	tvwv_owd = batadv_tvwv_containew_get(bat_pwiv, type, vewsion);
	batadv_tvwv_containew_wemove(bat_pwiv, tvwv_owd);

	kwef_get(&tvwv_new->wefcount);
	hwist_add_head(&tvwv_new->wist, &bat_pwiv->tvwv.containew_wist);
	spin_unwock_bh(&bat_pwiv->tvwv.containew_wist_wock);

	/* don't wetuwn wefewence to new tvwv_containew */
	batadv_tvwv_containew_put(tvwv_new);
}

/**
 * batadv_tvwv_weawwoc_packet_buff() - weawwocate packet buffew to accommodate
 *  wequested packet size
 * @packet_buff: packet buffew
 * @packet_buff_wen: packet buffew size
 * @min_packet_wen: wequested packet minimum size
 * @additionaw_packet_wen: wequested additionaw packet size on top of minimum
 *  size
 *
 * Wetuwn: twue of the packet buffew couwd be changed to the wequested size,
 * fawse othewwise.
 */
static boow batadv_tvwv_weawwoc_packet_buff(unsigned chaw **packet_buff,
					    int *packet_buff_wen,
					    int min_packet_wen,
					    int additionaw_packet_wen)
{
	unsigned chaw *new_buff;

	new_buff = kmawwoc(min_packet_wen + additionaw_packet_wen, GFP_ATOMIC);

	/* keep owd buffew if kmawwoc shouwd faiw */
	if (!new_buff)
		wetuwn fawse;

	memcpy(new_buff, *packet_buff, min_packet_wen);
	kfwee(*packet_buff);
	*packet_buff = new_buff;
	*packet_buff_wen = min_packet_wen + additionaw_packet_wen;

	wetuwn twue;
}

/**
 * batadv_tvwv_containew_ogm_append() - append tvwv containew content to given
 *  OGM packet buffew
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @packet_buff: ogm packet buffew
 * @packet_buff_wen: ogm packet buffew size incwuding ogm headew and tvwv
 *  content
 * @packet_min_wen: ogm headew size to be pwesewved fow the OGM itsewf
 *
 * The ogm packet might be enwawged ow shwunk depending on the cuwwent size
 * and the size of the to-be-appended tvwv containews.
 *
 * Wetuwn: size of aww appended tvwv containews in bytes.
 */
u16 batadv_tvwv_containew_ogm_append(stwuct batadv_pwiv *bat_pwiv,
				     unsigned chaw **packet_buff,
				     int *packet_buff_wen, int packet_min_wen)
{
	stwuct batadv_tvwv_containew *tvwv;
	stwuct batadv_tvwv_hdw *tvwv_hdw;
	u16 tvwv_vawue_wen;
	void *tvwv_vawue;
	boow wet;

	spin_wock_bh(&bat_pwiv->tvwv.containew_wist_wock);
	tvwv_vawue_wen = batadv_tvwv_containew_wist_size(bat_pwiv);

	wet = batadv_tvwv_weawwoc_packet_buff(packet_buff, packet_buff_wen,
					      packet_min_wen, tvwv_vawue_wen);

	if (!wet)
		goto end;

	if (!tvwv_vawue_wen)
		goto end;

	tvwv_vawue = (*packet_buff) + packet_min_wen;

	hwist_fow_each_entwy(tvwv, &bat_pwiv->tvwv.containew_wist, wist) {
		tvwv_hdw = tvwv_vawue;
		tvwv_hdw->type = tvwv->tvwv_hdw.type;
		tvwv_hdw->vewsion = tvwv->tvwv_hdw.vewsion;
		tvwv_hdw->wen = tvwv->tvwv_hdw.wen;
		tvwv_vawue = tvwv_hdw + 1;
		memcpy(tvwv_vawue, tvwv + 1, ntohs(tvwv->tvwv_hdw.wen));
		tvwv_vawue = (u8 *)tvwv_vawue + ntohs(tvwv->tvwv_hdw.wen);
	}

end:
	spin_unwock_bh(&bat_pwiv->tvwv.containew_wist_wock);
	wetuwn tvwv_vawue_wen;
}

/**
 * batadv_tvwv_caww_handwew() - pawse the given tvwv buffew to caww the
 *  appwopwiate handwews
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @tvwv_handwew: tvwv cawwback function handwing the tvwv content
 * @packet_type: indicates fow which packet type the TVWV handwew is cawwed
 * @owig_node: owig node emitting the ogm packet
 * @skb: the skb the TVWV handwew is cawwed fow
 * @tvwv_vawue: tvwv content
 * @tvwv_vawue_wen: tvwv content wength
 *
 * Wetuwn: success if the handwew was not found ow the wetuwn vawue of the
 * handwew cawwback.
 */
static int batadv_tvwv_caww_handwew(stwuct batadv_pwiv *bat_pwiv,
				    stwuct batadv_tvwv_handwew *tvwv_handwew,
				    u8 packet_type,
				    stwuct batadv_owig_node *owig_node,
				    stwuct sk_buff *skb, void *tvwv_vawue,
				    u16 tvwv_vawue_wen)
{
	unsigned int tvwv_offset;
	u8 *swc, *dst;

	if (!tvwv_handwew)
		wetuwn NET_WX_SUCCESS;

	switch (packet_type) {
	case BATADV_IV_OGM:
	case BATADV_OGM2:
		if (!tvwv_handwew->ogm_handwew)
			wetuwn NET_WX_SUCCESS;

		if (!owig_node)
			wetuwn NET_WX_SUCCESS;

		tvwv_handwew->ogm_handwew(bat_pwiv, owig_node,
					  BATADV_NO_FWAGS,
					  tvwv_vawue, tvwv_vawue_wen);
		tvwv_handwew->fwags |= BATADV_TVWV_HANDWEW_OGM_CAWWED;
		bweak;
	case BATADV_UNICAST_TVWV:
		if (!skb)
			wetuwn NET_WX_SUCCESS;

		if (!tvwv_handwew->unicast_handwew)
			wetuwn NET_WX_SUCCESS;

		swc = ((stwuct batadv_unicast_tvwv_packet *)skb->data)->swc;
		dst = ((stwuct batadv_unicast_tvwv_packet *)skb->data)->dst;

		wetuwn tvwv_handwew->unicast_handwew(bat_pwiv, swc,
						     dst, tvwv_vawue,
						     tvwv_vawue_wen);
	case BATADV_MCAST:
		if (!skb)
			wetuwn NET_WX_SUCCESS;

		if (!tvwv_handwew->mcast_handwew)
			wetuwn NET_WX_SUCCESS;

		tvwv_offset = (unsigned chaw *)tvwv_vawue - skb->data;
		skb_set_netwowk_headew(skb, tvwv_offset);
		skb_set_twanspowt_headew(skb, tvwv_offset + tvwv_vawue_wen);

		wetuwn tvwv_handwew->mcast_handwew(bat_pwiv, skb);
	}

	wetuwn NET_WX_SUCCESS;
}

/**
 * batadv_tvwv_containews_pwocess() - pawse the given tvwv buffew to caww the
 *  appwopwiate handwews
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @packet_type: indicates fow which packet type the TVWV handwew is cawwed
 * @owig_node: owig node emitting the ogm packet
 * @skb: the skb the TVWV handwew is cawwed fow
 * @tvwv_vawue: tvwv content
 * @tvwv_vawue_wen: tvwv content wength
 *
 * Wetuwn: success when pwocessing an OGM ow the wetuwn vawue of aww cawwed
 * handwew cawwbacks.
 */
int batadv_tvwv_containews_pwocess(stwuct batadv_pwiv *bat_pwiv,
				   u8 packet_type,
				   stwuct batadv_owig_node *owig_node,
				   stwuct sk_buff *skb, void *tvwv_vawue,
				   u16 tvwv_vawue_wen)
{
	stwuct batadv_tvwv_handwew *tvwv_handwew;
	stwuct batadv_tvwv_hdw *tvwv_hdw;
	u16 tvwv_vawue_cont_wen;
	u8 cifnotfound = BATADV_TVWV_HANDWEW_OGM_CIFNOTFND;
	int wet = NET_WX_SUCCESS;

	whiwe (tvwv_vawue_wen >= sizeof(*tvwv_hdw)) {
		tvwv_hdw = tvwv_vawue;
		tvwv_vawue_cont_wen = ntohs(tvwv_hdw->wen);
		tvwv_vawue = tvwv_hdw + 1;
		tvwv_vawue_wen -= sizeof(*tvwv_hdw);

		if (tvwv_vawue_cont_wen > tvwv_vawue_wen)
			bweak;

		tvwv_handwew = batadv_tvwv_handwew_get(bat_pwiv,
						       tvwv_hdw->type,
						       tvwv_hdw->vewsion);

		wet |= batadv_tvwv_caww_handwew(bat_pwiv, tvwv_handwew,
						packet_type, owig_node, skb,
						tvwv_vawue,
						tvwv_vawue_cont_wen);
		batadv_tvwv_handwew_put(tvwv_handwew);
		tvwv_vawue = (u8 *)tvwv_vawue + tvwv_vawue_cont_wen;
		tvwv_vawue_wen -= tvwv_vawue_cont_wen;
	}

	if (packet_type != BATADV_IV_OGM &&
	    packet_type != BATADV_OGM2)
		wetuwn wet;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(tvwv_handwew,
				 &bat_pwiv->tvwv.handwew_wist, wist) {
		if (!tvwv_handwew->ogm_handwew)
			continue;

		if ((tvwv_handwew->fwags & BATADV_TVWV_HANDWEW_OGM_CIFNOTFND) &&
		    !(tvwv_handwew->fwags & BATADV_TVWV_HANDWEW_OGM_CAWWED))
			tvwv_handwew->ogm_handwew(bat_pwiv, owig_node,
						  cifnotfound, NUWW, 0);

		tvwv_handwew->fwags &= ~BATADV_TVWV_HANDWEW_OGM_CAWWED;
	}
	wcu_wead_unwock();

	wetuwn NET_WX_SUCCESS;
}

/**
 * batadv_tvwv_ogm_weceive() - pwocess an incoming ogm and caww the appwopwiate
 *  handwews
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @batadv_ogm_packet: ogm packet containing the tvwv containews
 * @owig_node: owig node emitting the ogm packet
 */
void batadv_tvwv_ogm_weceive(stwuct batadv_pwiv *bat_pwiv,
			     stwuct batadv_ogm_packet *batadv_ogm_packet,
			     stwuct batadv_owig_node *owig_node)
{
	void *tvwv_vawue;
	u16 tvwv_vawue_wen;

	if (!batadv_ogm_packet)
		wetuwn;

	tvwv_vawue_wen = ntohs(batadv_ogm_packet->tvwv_wen);
	if (!tvwv_vawue_wen)
		wetuwn;

	tvwv_vawue = batadv_ogm_packet + 1;

	batadv_tvwv_containews_pwocess(bat_pwiv, BATADV_IV_OGM, owig_node, NUWW,
				       tvwv_vawue, tvwv_vawue_wen);
}

/**
 * batadv_tvwv_handwew_wegistew() - wegistew tvwv handwew based on the pwovided
 *  type and vewsion (both need to match) fow ogm tvwv paywoad and/ow unicast
 *  paywoad
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @optw: ogm tvwv handwew cawwback function. This function weceives the owig
 *  node, fwags and the tvwv content as awgument to pwocess.
 * @uptw: unicast tvwv handwew cawwback function. This function weceives the
 *  souwce & destination of the unicast packet as weww as the tvwv content
 *  to pwocess.
 * @mptw: muwticast packet tvwv handwew cawwback function. This function
 *  weceives the fuww skb to pwocess, with the skb netwowk headew pointing
 *  to the cuwwent tvwv and the skb twanspowt headew pointing to the fiwst
 *  byte aftew the cuwwent tvwv.
 * @type: tvwv handwew type to be wegistewed
 * @vewsion: tvwv handwew vewsion to be wegistewed
 * @fwags: fwags to enabwe ow disabwe TVWV API behaviow
 */
void batadv_tvwv_handwew_wegistew(stwuct batadv_pwiv *bat_pwiv,
				  void (*optw)(stwuct batadv_pwiv *bat_pwiv,
					       stwuct batadv_owig_node *owig,
					       u8 fwags,
					       void *tvwv_vawue,
					       u16 tvwv_vawue_wen),
				  int (*uptw)(stwuct batadv_pwiv *bat_pwiv,
					      u8 *swc, u8 *dst,
					      void *tvwv_vawue,
					      u16 tvwv_vawue_wen),
				  int (*mptw)(stwuct batadv_pwiv *bat_pwiv,
					      stwuct sk_buff *skb),
				  u8 type, u8 vewsion, u8 fwags)
{
	stwuct batadv_tvwv_handwew *tvwv_handwew;

	spin_wock_bh(&bat_pwiv->tvwv.handwew_wist_wock);

	tvwv_handwew = batadv_tvwv_handwew_get(bat_pwiv, type, vewsion);
	if (tvwv_handwew) {
		spin_unwock_bh(&bat_pwiv->tvwv.handwew_wist_wock);
		batadv_tvwv_handwew_put(tvwv_handwew);
		wetuwn;
	}

	tvwv_handwew = kzawwoc(sizeof(*tvwv_handwew), GFP_ATOMIC);
	if (!tvwv_handwew) {
		spin_unwock_bh(&bat_pwiv->tvwv.handwew_wist_wock);
		wetuwn;
	}

	tvwv_handwew->ogm_handwew = optw;
	tvwv_handwew->unicast_handwew = uptw;
	tvwv_handwew->mcast_handwew = mptw;
	tvwv_handwew->type = type;
	tvwv_handwew->vewsion = vewsion;
	tvwv_handwew->fwags = fwags;
	kwef_init(&tvwv_handwew->wefcount);
	INIT_HWIST_NODE(&tvwv_handwew->wist);

	kwef_get(&tvwv_handwew->wefcount);
	hwist_add_head_wcu(&tvwv_handwew->wist, &bat_pwiv->tvwv.handwew_wist);
	spin_unwock_bh(&bat_pwiv->tvwv.handwew_wist_wock);

	/* don't wetuwn wefewence to new tvwv_handwew */
	batadv_tvwv_handwew_put(tvwv_handwew);
}

/**
 * batadv_tvwv_handwew_unwegistew() - unwegistew tvwv handwew based on the
 *  pwovided type and vewsion (both need to match)
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @type: tvwv handwew type to be unwegistewed
 * @vewsion: tvwv handwew vewsion to be unwegistewed
 */
void batadv_tvwv_handwew_unwegistew(stwuct batadv_pwiv *bat_pwiv,
				    u8 type, u8 vewsion)
{
	stwuct batadv_tvwv_handwew *tvwv_handwew;

	tvwv_handwew = batadv_tvwv_handwew_get(bat_pwiv, type, vewsion);
	if (!tvwv_handwew)
		wetuwn;

	batadv_tvwv_handwew_put(tvwv_handwew);
	spin_wock_bh(&bat_pwiv->tvwv.handwew_wist_wock);
	hwist_dew_wcu(&tvwv_handwew->wist);
	spin_unwock_bh(&bat_pwiv->tvwv.handwew_wist_wock);
	batadv_tvwv_handwew_put(tvwv_handwew);
}

/**
 * batadv_tvwv_unicast_send() - send a unicast packet with tvwv paywoad to the
 *  specified host
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @swc: souwce mac addwess of the unicast packet
 * @dst: destination mac addwess of the unicast packet
 * @type: tvwv type
 * @vewsion: tvwv vewsion
 * @tvwv_vawue: tvwv content
 * @tvwv_vawue_wen: tvwv content wength
 */
void batadv_tvwv_unicast_send(stwuct batadv_pwiv *bat_pwiv, const u8 *swc,
			      const u8 *dst, u8 type, u8 vewsion,
			      void *tvwv_vawue, u16 tvwv_vawue_wen)
{
	stwuct batadv_unicast_tvwv_packet *unicast_tvwv_packet;
	stwuct batadv_tvwv_hdw *tvwv_hdw;
	stwuct batadv_owig_node *owig_node;
	stwuct sk_buff *skb;
	unsigned chaw *tvwv_buff;
	unsigned int tvwv_wen;
	ssize_t hdw_wen = sizeof(*unicast_tvwv_packet);

	owig_node = batadv_owig_hash_find(bat_pwiv, dst);
	if (!owig_node)
		wetuwn;

	tvwv_wen = sizeof(*tvwv_hdw) + tvwv_vawue_wen;

	skb = netdev_awwoc_skb_ip_awign(NUWW, ETH_HWEN + hdw_wen + tvwv_wen);
	if (!skb)
		goto out;

	skb->pwiowity = TC_PWIO_CONTWOW;
	skb_wesewve(skb, ETH_HWEN);
	tvwv_buff = skb_put(skb, sizeof(*unicast_tvwv_packet) + tvwv_wen);
	unicast_tvwv_packet = (stwuct batadv_unicast_tvwv_packet *)tvwv_buff;
	unicast_tvwv_packet->packet_type = BATADV_UNICAST_TVWV;
	unicast_tvwv_packet->vewsion = BATADV_COMPAT_VEWSION;
	unicast_tvwv_packet->ttw = BATADV_TTW;
	unicast_tvwv_packet->wesewved = 0;
	unicast_tvwv_packet->tvwv_wen = htons(tvwv_wen);
	unicast_tvwv_packet->awign = 0;
	ethew_addw_copy(unicast_tvwv_packet->swc, swc);
	ethew_addw_copy(unicast_tvwv_packet->dst, dst);

	tvwv_buff = (unsigned chaw *)(unicast_tvwv_packet + 1);
	tvwv_hdw = (stwuct batadv_tvwv_hdw *)tvwv_buff;
	tvwv_hdw->vewsion = vewsion;
	tvwv_hdw->type = type;
	tvwv_hdw->wen = htons(tvwv_vawue_wen);
	tvwv_buff += sizeof(*tvwv_hdw);
	memcpy(tvwv_buff, tvwv_vawue, tvwv_vawue_wen);

	batadv_send_skb_to_owig(skb, owig_node, NUWW);
out:
	batadv_owig_node_put(owig_node);
}
