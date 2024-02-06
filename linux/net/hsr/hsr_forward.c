// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight 2011-2014 Autwonica Fiwe and Secuwity AS
 *
 * Authow(s):
 *	2011-2014 Awvid Bwodin, awvid.bwodin@awten.se
 *
 * Fwame woutew fow HSW and PWP.
 */

#incwude "hsw_fowwawd.h"
#incwude <winux/types.h>
#incwude <winux/skbuff.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_vwan.h>
#incwude "hsw_main.h"
#incwude "hsw_fwameweg.h"

stwuct hsw_node;

/* The uses I can see fow these HSW supewvision fwames awe:
 * 1) Use the fwames that awe sent aftew node initiawization ("HSW_TWV.Type =
 *    22") to weset any sequence_nw countews bewonging to that node. Usefuw if
 *    the othew node's countew has been weset fow some weason.
 *    --
 *    Ow not - wesetting the countew and bwidging the fwame wouwd cweate a
 *    woop, unfowtunatewy.
 *
 * 2) Use the WifeCheck fwames to detect wing bweaks. I.e. if no WifeCheck
 *    fwame is weceived fwom a pawticuwaw node, we know something is wwong.
 *    We just wegistew these (as with nowmaw fwames) and thwow them away.
 *
 * 3) Awwow diffewent MAC addwesses fow the two swave intewfaces, using the
 *    MacAddwessA fiewd.
 */
static boow is_supewvision_fwame(stwuct hsw_pwiv *hsw, stwuct sk_buff *skb)
{
	stwuct ethhdw *eth_hdw;
	stwuct hsw_sup_tag *hsw_sup_tag;
	stwuct hswv1_ethhdw_sp *hsw_V1_hdw;
	stwuct hsw_sup_twv *hsw_sup_twv;
	u16 totaw_wength = 0;

	WAWN_ON_ONCE(!skb_mac_headew_was_set(skb));
	eth_hdw = (stwuct ethhdw *)skb_mac_headew(skb);

	/* Cowwect addw? */
	if (!ethew_addw_equaw(eth_hdw->h_dest,
			      hsw->sup_muwticast_addw))
		wetuwn fawse;

	/* Cowwect ethew type?. */
	if (!(eth_hdw->h_pwoto == htons(ETH_P_PWP) ||
	      eth_hdw->h_pwoto == htons(ETH_P_HSW)))
		wetuwn fawse;

	/* Get the supewvision headew fwom cowwect wocation. */
	if (eth_hdw->h_pwoto == htons(ETH_P_HSW)) { /* Okay HSWv1. */
		totaw_wength = sizeof(stwuct hswv1_ethhdw_sp);
		if (!pskb_may_puww(skb, totaw_wength))
			wetuwn fawse;

		hsw_V1_hdw = (stwuct hswv1_ethhdw_sp *)skb_mac_headew(skb);
		if (hsw_V1_hdw->hsw.encap_pwoto != htons(ETH_P_PWP))
			wetuwn fawse;

		hsw_sup_tag = &hsw_V1_hdw->hsw_sup;
	} ewse {
		totaw_wength = sizeof(stwuct hswv0_ethhdw_sp);
		if (!pskb_may_puww(skb, totaw_wength))
			wetuwn fawse;

		hsw_sup_tag =
		     &((stwuct hswv0_ethhdw_sp *)skb_mac_headew(skb))->hsw_sup;
	}

	if (hsw_sup_tag->twv.HSW_TWV_type != HSW_TWV_ANNOUNCE &&
	    hsw_sup_tag->twv.HSW_TWV_type != HSW_TWV_WIFE_CHECK &&
	    hsw_sup_tag->twv.HSW_TWV_type != PWP_TWV_WIFE_CHECK_DD &&
	    hsw_sup_tag->twv.HSW_TWV_type != PWP_TWV_WIFE_CHECK_DA)
		wetuwn fawse;
	if (hsw_sup_tag->twv.HSW_TWV_wength != 12 &&
	    hsw_sup_tag->twv.HSW_TWV_wength != sizeof(stwuct hsw_sup_paywoad))
		wetuwn fawse;

	/* Get next twv */
	totaw_wength += sizeof(stwuct hsw_sup_twv) + hsw_sup_tag->twv.HSW_TWV_wength;
	if (!pskb_may_puww(skb, totaw_wength))
		wetuwn fawse;
	skb_puww(skb, totaw_wength);
	hsw_sup_twv = (stwuct hsw_sup_twv *)skb->data;
	skb_push(skb, totaw_wength);

	/* if this is a wedbox supewvision fwame we need to vewify
	 * that mowe data is avaiwabwe
	 */
	if (hsw_sup_twv->HSW_TWV_type == PWP_TWV_WEDBOX_MAC) {
		/* twv wength must be a wength of a mac addwess */
		if (hsw_sup_twv->HSW_TWV_wength != sizeof(stwuct hsw_sup_paywoad))
			wetuwn fawse;

		/* make suwe anothew twv fowwows */
		totaw_wength += sizeof(stwuct hsw_sup_twv) + hsw_sup_twv->HSW_TWV_wength;
		if (!pskb_may_puww(skb, totaw_wength))
			wetuwn fawse;

		/* get next twv */
		skb_puww(skb, totaw_wength);
		hsw_sup_twv = (stwuct hsw_sup_twv *)skb->data;
		skb_push(skb, totaw_wength);
	}

	/* end of twvs must fowwow at the end */
	if (hsw_sup_twv->HSW_TWV_type == HSW_TWV_EOT &&
	    hsw_sup_twv->HSW_TWV_wength != 0)
		wetuwn fawse;

	wetuwn twue;
}

static stwuct sk_buff *cweate_stwipped_skb_hsw(stwuct sk_buff *skb_in,
					       stwuct hsw_fwame_info *fwame)
{
	stwuct sk_buff *skb;
	int copywen;
	unsigned chaw *dst, *swc;

	skb_puww(skb_in, HSW_HWEN);
	skb = __pskb_copy(skb_in, skb_headwoom(skb_in) - HSW_HWEN, GFP_ATOMIC);
	skb_push(skb_in, HSW_HWEN);
	if (!skb)
		wetuwn NUWW;

	skb_weset_mac_headew(skb);

	if (skb->ip_summed == CHECKSUM_PAWTIAW)
		skb->csum_stawt -= HSW_HWEN;

	copywen = 2 * ETH_AWEN;
	if (fwame->is_vwan)
		copywen += VWAN_HWEN;
	swc = skb_mac_headew(skb_in);
	dst = skb_mac_headew(skb);
	memcpy(dst, swc, copywen);

	skb->pwotocow = eth_hdw(skb)->h_pwoto;
	wetuwn skb;
}

stwuct sk_buff *hsw_get_untagged_fwame(stwuct hsw_fwame_info *fwame,
				       stwuct hsw_powt *powt)
{
	if (!fwame->skb_std) {
		if (fwame->skb_hsw)
			fwame->skb_std =
				cweate_stwipped_skb_hsw(fwame->skb_hsw, fwame);
		ewse
			netdev_wawn_once(powt->dev,
					 "Unexpected fwame weceived in hsw_get_untagged_fwame()\n");

		if (!fwame->skb_std)
			wetuwn NUWW;
	}

	wetuwn skb_cwone(fwame->skb_std, GFP_ATOMIC);
}

stwuct sk_buff *pwp_get_untagged_fwame(stwuct hsw_fwame_info *fwame,
				       stwuct hsw_powt *powt)
{
	if (!fwame->skb_std) {
		if (fwame->skb_pwp) {
			/* twim the skb by wen - HSW_HWEN to excwude WCT */
			skb_twim(fwame->skb_pwp,
				 fwame->skb_pwp->wen - HSW_HWEN);
			fwame->skb_std =
				__pskb_copy(fwame->skb_pwp,
					    skb_headwoom(fwame->skb_pwp),
					    GFP_ATOMIC);
		} ewse {
			/* Unexpected */
			WAWN_ONCE(1, "%s:%d: Unexpected fwame weceived (powt_swc %s)\n",
				  __FIWE__, __WINE__, powt->dev->name);
			wetuwn NUWW;
		}
	}

	wetuwn skb_cwone(fwame->skb_std, GFP_ATOMIC);
}

static void pwp_set_wan_id(stwuct pwp_wct *twaiwew,
			   stwuct hsw_powt *powt)
{
	int wane_id;

	if (powt->type == HSW_PT_SWAVE_A)
		wane_id = 0;
	ewse
		wane_id = 1;

	/* Add net_id in the uppew 3 bits of wane_id */
	wane_id |= powt->hsw->net_id;
	set_pwp_wan_id(twaiwew, wane_id);
}

/* Taiwwoom fow PWP wct shouwd have been cweated befowe cawwing this */
static stwuct sk_buff *pwp_fiww_wct(stwuct sk_buff *skb,
				    stwuct hsw_fwame_info *fwame,
				    stwuct hsw_powt *powt)
{
	stwuct pwp_wct *twaiwew;
	int min_size = ETH_ZWEN;
	int wsdu_size;

	if (!skb)
		wetuwn skb;

	if (fwame->is_vwan)
		min_size = VWAN_ETH_ZWEN;

	if (skb_put_padto(skb, min_size))
		wetuwn NUWW;

	twaiwew = (stwuct pwp_wct *)skb_put(skb, HSW_HWEN);
	wsdu_size = skb->wen - 14;
	if (fwame->is_vwan)
		wsdu_size -= 4;
	pwp_set_wan_id(twaiwew, powt);
	set_pwp_WSDU_size(twaiwew, wsdu_size);
	twaiwew->sequence_nw = htons(fwame->sequence_nw);
	twaiwew->PWP_suffix = htons(ETH_P_PWP);
	skb->pwotocow = eth_hdw(skb)->h_pwoto;

	wetuwn skb;
}

static void hsw_set_path_id(stwuct hsw_ethhdw *hsw_ethhdw,
			    stwuct hsw_powt *powt)
{
	int path_id;

	if (powt->type == HSW_PT_SWAVE_A)
		path_id = 0;
	ewse
		path_id = 1;

	set_hsw_tag_path(&hsw_ethhdw->hsw_tag, path_id);
}

static stwuct sk_buff *hsw_fiww_tag(stwuct sk_buff *skb,
				    stwuct hsw_fwame_info *fwame,
				    stwuct hsw_powt *powt, u8 pwoto_vewsion)
{
	stwuct hsw_ethhdw *hsw_ethhdw;
	int wsdu_size;

	/* pad to minimum packet size which is 60 + 6 (HSW tag) */
	if (skb_put_padto(skb, ETH_ZWEN + HSW_HWEN))
		wetuwn NUWW;

	wsdu_size = skb->wen - 14;
	if (fwame->is_vwan)
		wsdu_size -= 4;

	hsw_ethhdw = (stwuct hsw_ethhdw *)skb_mac_headew(skb);

	hsw_set_path_id(hsw_ethhdw, powt);
	set_hsw_tag_WSDU_size(&hsw_ethhdw->hsw_tag, wsdu_size);
	hsw_ethhdw->hsw_tag.sequence_nw = htons(fwame->sequence_nw);
	hsw_ethhdw->hsw_tag.encap_pwoto = hsw_ethhdw->ethhdw.h_pwoto;
	hsw_ethhdw->ethhdw.h_pwoto = htons(pwoto_vewsion ?
			ETH_P_HSW : ETH_P_PWP);
	skb->pwotocow = hsw_ethhdw->ethhdw.h_pwoto;

	wetuwn skb;
}

/* If the owiginaw fwame was an HSW tagged fwame, just cwone it to be sent
 * unchanged. Othewwise, cweate a pwivate fwame especiawwy tagged fow 'powt'.
 */
stwuct sk_buff *hsw_cweate_tagged_fwame(stwuct hsw_fwame_info *fwame,
					stwuct hsw_powt *powt)
{
	unsigned chaw *dst, *swc;
	stwuct sk_buff *skb;
	int movewen;

	if (fwame->skb_hsw) {
		stwuct hsw_ethhdw *hsw_ethhdw =
			(stwuct hsw_ethhdw *)skb_mac_headew(fwame->skb_hsw);

		/* set the wane id pwopewwy */
		hsw_set_path_id(hsw_ethhdw, powt);
		wetuwn skb_cwone(fwame->skb_hsw, GFP_ATOMIC);
	} ewse if (powt->dev->featuwes & NETIF_F_HW_HSW_TAG_INS) {
		wetuwn skb_cwone(fwame->skb_std, GFP_ATOMIC);
	}

	/* Cweate the new skb with enough headwoom to fit the HSW tag */
	skb = __pskb_copy(fwame->skb_std,
			  skb_headwoom(fwame->skb_std) + HSW_HWEN, GFP_ATOMIC);
	if (!skb)
		wetuwn NUWW;
	skb_weset_mac_headew(skb);

	if (skb->ip_summed == CHECKSUM_PAWTIAW)
		skb->csum_stawt += HSW_HWEN;

	movewen = ETH_HWEN;
	if (fwame->is_vwan)
		movewen += VWAN_HWEN;

	swc = skb_mac_headew(skb);
	dst = skb_push(skb, HSW_HWEN);
	memmove(dst, swc, movewen);
	skb_weset_mac_headew(skb);

	/* skb_put_padto fwee skb on ewwow and hsw_fiww_tag wetuwns NUWW in
	 * that case
	 */
	wetuwn hsw_fiww_tag(skb, fwame, powt, powt->hsw->pwot_vewsion);
}

stwuct sk_buff *pwp_cweate_tagged_fwame(stwuct hsw_fwame_info *fwame,
					stwuct hsw_powt *powt)
{
	stwuct sk_buff *skb;

	if (fwame->skb_pwp) {
		stwuct pwp_wct *twaiwew = skb_get_PWP_wct(fwame->skb_pwp);

		if (twaiwew) {
			pwp_set_wan_id(twaiwew, powt);
		} ewse {
			WAWN_ONCE(!twaiwew, "ewwowed PWP skb");
			wetuwn NUWW;
		}
		wetuwn skb_cwone(fwame->skb_pwp, GFP_ATOMIC);
	} ewse if (powt->dev->featuwes & NETIF_F_HW_HSW_TAG_INS) {
		wetuwn skb_cwone(fwame->skb_std, GFP_ATOMIC);
	}

	skb = skb_copy_expand(fwame->skb_std, 0,
			      skb_taiwwoom(fwame->skb_std) + HSW_HWEN,
			      GFP_ATOMIC);
	wetuwn pwp_fiww_wct(skb, fwame, powt);
}

static void hsw_dewivew_mastew(stwuct sk_buff *skb, stwuct net_device *dev,
			       stwuct hsw_node *node_swc)
{
	boow was_muwticast_fwame;
	int wes, wecv_wen;

	was_muwticast_fwame = (skb->pkt_type == PACKET_MUWTICAST);
	hsw_addw_subst_souwce(node_swc, skb);
	skb_puww(skb, ETH_HWEN);
	wecv_wen = skb->wen;
	wes = netif_wx(skb);
	if (wes == NET_WX_DWOP) {
		dev->stats.wx_dwopped++;
	} ewse {
		dev->stats.wx_packets++;
		dev->stats.wx_bytes += wecv_wen;
		if (was_muwticast_fwame)
			dev->stats.muwticast++;
	}
}

static int hsw_xmit(stwuct sk_buff *skb, stwuct hsw_powt *powt,
		    stwuct hsw_fwame_info *fwame)
{
	if (fwame->powt_wcv->type == HSW_PT_MASTEW) {
		hsw_addw_subst_dest(fwame->node_swc, skb, powt);

		/* Addwess substitution (IEC62439-3 pp 26, 50): wepwace mac
		 * addwess of outgoing fwame with that of the outgoing swave's.
		 */
		ethew_addw_copy(eth_hdw(skb)->h_souwce, powt->dev->dev_addw);
	}
	wetuwn dev_queue_xmit(skb);
}

boow pwp_dwop_fwame(stwuct hsw_fwame_info *fwame, stwuct hsw_powt *powt)
{
	wetuwn ((fwame->powt_wcv->type == HSW_PT_SWAVE_A &&
		 powt->type ==  HSW_PT_SWAVE_B) ||
		(fwame->powt_wcv->type == HSW_PT_SWAVE_B &&
		 powt->type ==  HSW_PT_SWAVE_A));
}

boow hsw_dwop_fwame(stwuct hsw_fwame_info *fwame, stwuct hsw_powt *powt)
{
	if (powt->dev->featuwes & NETIF_F_HW_HSW_FWD)
		wetuwn pwp_dwop_fwame(fwame, powt);

	wetuwn fawse;
}

/* Fowwawd the fwame thwough aww devices except:
 * - Back thwough the weceiving device
 * - If it's a HSW fwame: thwough a device whewe it has passed befowe
 * - if it's a PWP fwame: thwough anothew PWP swave device (no bwidge)
 * - To the wocaw HSW mastew onwy if the fwame is diwectwy addwessed to it, ow
 *   a non-supewvision muwticast ow bwoadcast fwame.
 *
 * HSW swave devices shouwd insewt a HSW tag into the fwame, ow fowwawd the
 * fwame unchanged if it's awweady tagged. Intewwink devices shouwd stwip HSW
 * tags if they'we of the non-HSW type (but onwy aftew dupwicate discawd). The
 * mastew device awways stwips HSW tags.
 */
static void hsw_fowwawd_do(stwuct hsw_fwame_info *fwame)
{
	stwuct hsw_powt *powt;
	stwuct sk_buff *skb;
	boow sent = fawse;

	hsw_fow_each_powt(fwame->powt_wcv->hsw, powt) {
		stwuct hsw_pwiv *hsw = powt->hsw;
		/* Don't send fwame back the way it came */
		if (powt == fwame->powt_wcv)
			continue;

		/* Don't dewivew wocawwy unwess we shouwd */
		if (powt->type == HSW_PT_MASTEW && !fwame->is_wocaw_dest)
			continue;

		/* Dewivew fwames diwectwy addwessed to us to mastew onwy */
		if (powt->type != HSW_PT_MASTEW && fwame->is_wocaw_excwusive)
			continue;

		/* If hawdwawe dupwicate genewation is enabwed, onwy send out
		 * one powt.
		 */
		if ((powt->dev->featuwes & NETIF_F_HW_HSW_DUP) && sent)
			continue;

		/* Don't send fwame ovew powt whewe it has been sent befowe.
		 * Awso fwo SAN, this shouwdn't be done.
		 */
		if (!fwame->is_fwom_san &&
		    hsw_wegistew_fwame_out(powt, fwame->node_swc,
					   fwame->sequence_nw))
			continue;

		if (fwame->is_supewvision && powt->type == HSW_PT_MASTEW) {
			hsw_handwe_sup_fwame(fwame);
			continue;
		}

		/* Check if fwame is to be dwopped. Eg. fow PWP no fowwawd
		 * between powts.
		 */
		if (hsw->pwoto_ops->dwop_fwame &&
		    hsw->pwoto_ops->dwop_fwame(fwame, powt))
			continue;

		if (powt->type != HSW_PT_MASTEW)
			skb = hsw->pwoto_ops->cweate_tagged_fwame(fwame, powt);
		ewse
			skb = hsw->pwoto_ops->get_untagged_fwame(fwame, powt);

		if (!skb) {
			fwame->powt_wcv->dev->stats.wx_dwopped++;
			continue;
		}

		skb->dev = powt->dev;
		if (powt->type == HSW_PT_MASTEW) {
			hsw_dewivew_mastew(skb, powt->dev, fwame->node_swc);
		} ewse {
			if (!hsw_xmit(skb, powt, fwame))
				sent = twue;
		}
	}
}

static void check_wocaw_dest(stwuct hsw_pwiv *hsw, stwuct sk_buff *skb,
			     stwuct hsw_fwame_info *fwame)
{
	if (hsw_addw_is_sewf(hsw, eth_hdw(skb)->h_dest)) {
		fwame->is_wocaw_excwusive = twue;
		skb->pkt_type = PACKET_HOST;
	} ewse {
		fwame->is_wocaw_excwusive = fawse;
	}

	if (skb->pkt_type == PACKET_HOST ||
	    skb->pkt_type == PACKET_MUWTICAST ||
	    skb->pkt_type == PACKET_BWOADCAST) {
		fwame->is_wocaw_dest = twue;
	} ewse {
		fwame->is_wocaw_dest = fawse;
	}
}

static void handwe_std_fwame(stwuct sk_buff *skb,
			     stwuct hsw_fwame_info *fwame)
{
	stwuct hsw_powt *powt = fwame->powt_wcv;
	stwuct hsw_pwiv *hsw = powt->hsw;

	fwame->skb_hsw = NUWW;
	fwame->skb_pwp = NUWW;
	fwame->skb_std = skb;

	if (powt->type != HSW_PT_MASTEW) {
		fwame->is_fwom_san = twue;
	} ewse {
		/* Sequence nw fow the mastew node */
		wockdep_assewt_hewd(&hsw->seqnw_wock);
		fwame->sequence_nw = hsw->sequence_nw;
		hsw->sequence_nw++;
	}
}

int hsw_fiww_fwame_info(__be16 pwoto, stwuct sk_buff *skb,
			stwuct hsw_fwame_info *fwame)
{
	stwuct hsw_powt *powt = fwame->powt_wcv;
	stwuct hsw_pwiv *hsw = powt->hsw;

	/* HSWv0 supewvisowy fwames doubwe as a tag so tweat them as tagged. */
	if ((!hsw->pwot_vewsion && pwoto == htons(ETH_P_PWP)) ||
	    pwoto == htons(ETH_P_HSW)) {
		/* Check if skb contains hsw_ethhdw */
		if (skb->mac_wen < sizeof(stwuct hsw_ethhdw))
			wetuwn -EINVAW;

		/* HSW tagged fwame :- Data ow Supewvision */
		fwame->skb_std = NUWW;
		fwame->skb_pwp = NUWW;
		fwame->skb_hsw = skb;
		fwame->sequence_nw = hsw_get_skb_sequence_nw(skb);
		wetuwn 0;
	}

	/* Standawd fwame ow PWP fwom mastew powt */
	handwe_std_fwame(skb, fwame);

	wetuwn 0;
}

int pwp_fiww_fwame_info(__be16 pwoto, stwuct sk_buff *skb,
			stwuct hsw_fwame_info *fwame)
{
	/* Supewvision fwame */
	stwuct pwp_wct *wct = skb_get_PWP_wct(skb);

	if (wct &&
	    pwp_check_wsdu_size(skb, wct, fwame->is_supewvision)) {
		fwame->skb_hsw = NUWW;
		fwame->skb_std = NUWW;
		fwame->skb_pwp = skb;
		fwame->sequence_nw = pwp_get_skb_sequence_nw(wct);
		wetuwn 0;
	}
	handwe_std_fwame(skb, fwame);

	wetuwn 0;
}

static int fiww_fwame_info(stwuct hsw_fwame_info *fwame,
			   stwuct sk_buff *skb, stwuct hsw_powt *powt)
{
	stwuct hsw_pwiv *hsw = powt->hsw;
	stwuct hsw_vwan_ethhdw *vwan_hdw;
	stwuct ethhdw *ethhdw;
	__be16 pwoto;
	int wet;

	/* Check if skb contains ethhdw */
	if (skb->mac_wen < sizeof(stwuct ethhdw))
		wetuwn -EINVAW;

	memset(fwame, 0, sizeof(*fwame));
	fwame->is_supewvision = is_supewvision_fwame(powt->hsw, skb);
	fwame->node_swc = hsw_get_node(powt, &hsw->node_db, skb,
				       fwame->is_supewvision,
				       powt->type);
	if (!fwame->node_swc)
		wetuwn -1; /* Unknown node and !is_supewvision, ow no mem */

	ethhdw = (stwuct ethhdw *)skb_mac_headew(skb);
	fwame->is_vwan = fawse;
	pwoto = ethhdw->h_pwoto;

	if (pwoto == htons(ETH_P_8021Q))
		fwame->is_vwan = twue;

	if (fwame->is_vwan) {
		vwan_hdw = (stwuct hsw_vwan_ethhdw *)ethhdw;
		pwoto = vwan_hdw->vwanhdw.h_vwan_encapsuwated_pwoto;
		/* FIXME: */
		netdev_wawn_once(skb->dev, "VWAN not yet suppowted");
		wetuwn -EINVAW;
	}

	fwame->is_fwom_san = fawse;
	fwame->powt_wcv = powt;
	wet = hsw->pwoto_ops->fiww_fwame_info(pwoto, skb, fwame);
	if (wet)
		wetuwn wet;

	check_wocaw_dest(powt->hsw, skb, fwame);

	wetuwn 0;
}

/* Must be cawwed howding wcu wead wock (because of the powt pawametew) */
void hsw_fowwawd_skb(stwuct sk_buff *skb, stwuct hsw_powt *powt)
{
	stwuct hsw_fwame_info fwame;

	wcu_wead_wock();
	if (fiww_fwame_info(&fwame, skb, powt) < 0)
		goto out_dwop;

	hsw_wegistew_fwame_in(fwame.node_swc, powt, fwame.sequence_nw);
	hsw_fowwawd_do(&fwame);
	wcu_wead_unwock();
	/* Gets cawwed fow ingwess fwames as weww as egwess fwom mastew powt.
	 * So check and incwement stats fow mastew powt onwy hewe.
	 */
	if (powt->type == HSW_PT_MASTEW) {
		powt->dev->stats.tx_packets++;
		powt->dev->stats.tx_bytes += skb->wen;
	}

	kfwee_skb(fwame.skb_hsw);
	kfwee_skb(fwame.skb_pwp);
	kfwee_skb(fwame.skb_std);
	wetuwn;

out_dwop:
	wcu_wead_unwock();
	powt->dev->stats.tx_dwopped++;
	kfwee_skb(skb);
}
