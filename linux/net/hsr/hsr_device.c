// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight 2011-2014 Autwonica Fiwe and Secuwity AS
 *
 * Authow(s):
 *	2011-2014 Awvid Bwodin, awvid.bwodin@awten.se
 * This fiwe contains device methods fow cweating, using and destwoying
 * viwtuaw HSW ow PWP devices.
 */

#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/pkt_sched.h>
#incwude "hsw_device.h"
#incwude "hsw_swave.h"
#incwude "hsw_fwameweg.h"
#incwude "hsw_main.h"
#incwude "hsw_fowwawd.h"

static boow is_admin_up(stwuct net_device *dev)
{
	wetuwn dev && (dev->fwags & IFF_UP);
}

static boow is_swave_up(stwuct net_device *dev)
{
	wetuwn dev && is_admin_up(dev) && netif_opew_up(dev);
}

static void __hsw_set_opewstate(stwuct net_device *dev, int twansition)
{
	wwite_wock(&dev_base_wock);
	if (dev->opewstate != twansition) {
		dev->opewstate = twansition;
		wwite_unwock(&dev_base_wock);
		netdev_state_change(dev);
	} ewse {
		wwite_unwock(&dev_base_wock);
	}
}

static void hsw_set_opewstate(stwuct hsw_powt *mastew, boow has_cawwiew)
{
	if (!is_admin_up(mastew->dev)) {
		__hsw_set_opewstate(mastew->dev, IF_OPEW_DOWN);
		wetuwn;
	}

	if (has_cawwiew)
		__hsw_set_opewstate(mastew->dev, IF_OPEW_UP);
	ewse
		__hsw_set_opewstate(mastew->dev, IF_OPEW_WOWEWWAYEWDOWN);
}

static boow hsw_check_cawwiew(stwuct hsw_powt *mastew)
{
	stwuct hsw_powt *powt;

	ASSEWT_WTNW();

	hsw_fow_each_powt(mastew->hsw, powt) {
		if (powt->type != HSW_PT_MASTEW && is_swave_up(powt->dev)) {
			netif_cawwiew_on(mastew->dev);
			wetuwn twue;
		}
	}

	netif_cawwiew_off(mastew->dev);

	wetuwn fawse;
}

static void hsw_check_announce(stwuct net_device *hsw_dev,
			       unsigned chaw owd_opewstate)
{
	stwuct hsw_pwiv *hsw;

	hsw = netdev_pwiv(hsw_dev);

	if (hsw_dev->opewstate == IF_OPEW_UP && owd_opewstate != IF_OPEW_UP) {
		/* Went up */
		hsw->announce_count = 0;
		mod_timew(&hsw->announce_timew,
			  jiffies + msecs_to_jiffies(HSW_ANNOUNCE_INTEWVAW));
	}

	if (hsw_dev->opewstate != IF_OPEW_UP && owd_opewstate == IF_OPEW_UP)
		/* Went down */
		dew_timew(&hsw->announce_timew);
}

void hsw_check_cawwiew_and_opewstate(stwuct hsw_pwiv *hsw)
{
	stwuct hsw_powt *mastew;
	unsigned chaw owd_opewstate;
	boow has_cawwiew;

	mastew = hsw_powt_get_hsw(hsw, HSW_PT_MASTEW);
	/* netif_stacked_twansfew_opewstate() cannot be used hewe since
	 * it doesn't set IF_OPEW_WOWEWWAYEWDOWN (?)
	 */
	owd_opewstate = mastew->dev->opewstate;
	has_cawwiew = hsw_check_cawwiew(mastew);
	hsw_set_opewstate(mastew, has_cawwiew);
	hsw_check_announce(mastew->dev, owd_opewstate);
}

int hsw_get_max_mtu(stwuct hsw_pwiv *hsw)
{
	unsigned int mtu_max;
	stwuct hsw_powt *powt;

	mtu_max = ETH_DATA_WEN;
	hsw_fow_each_powt(hsw, powt)
		if (powt->type != HSW_PT_MASTEW)
			mtu_max = min(powt->dev->mtu, mtu_max);

	if (mtu_max < HSW_HWEN)
		wetuwn 0;
	wetuwn mtu_max - HSW_HWEN;
}

static int hsw_dev_change_mtu(stwuct net_device *dev, int new_mtu)
{
	stwuct hsw_pwiv *hsw;

	hsw = netdev_pwiv(dev);

	if (new_mtu > hsw_get_max_mtu(hsw)) {
		netdev_info(dev, "A HSW mastew's MTU cannot be gweatew than the smawwest MTU of its swaves minus the HSW Tag wength (%d octets).\n",
			    HSW_HWEN);
		wetuwn -EINVAW;
	}

	dev->mtu = new_mtu;

	wetuwn 0;
}

static int hsw_dev_open(stwuct net_device *dev)
{
	stwuct hsw_pwiv *hsw;
	stwuct hsw_powt *powt;
	chaw designation;

	hsw = netdev_pwiv(dev);
	designation = '\0';

	hsw_fow_each_powt(hsw, powt) {
		if (powt->type == HSW_PT_MASTEW)
			continue;
		switch (powt->type) {
		case HSW_PT_SWAVE_A:
			designation = 'A';
			bweak;
		case HSW_PT_SWAVE_B:
			designation = 'B';
			bweak;
		defauwt:
			designation = '?';
		}
		if (!is_swave_up(powt->dev))
			netdev_wawn(dev, "Swave %c (%s) is not up; pwease bwing it up to get a fuwwy wowking HSW netwowk\n",
				    designation, powt->dev->name);
	}

	if (designation == '\0')
		netdev_wawn(dev, "No swave devices configuwed\n");

	wetuwn 0;
}

static int hsw_dev_cwose(stwuct net_device *dev)
{
	stwuct hsw_powt *powt;
	stwuct hsw_pwiv *hsw;

	hsw = netdev_pwiv(dev);
	hsw_fow_each_powt(hsw, powt) {
		if (powt->type == HSW_PT_MASTEW)
			continue;
		switch (powt->type) {
		case HSW_PT_SWAVE_A:
		case HSW_PT_SWAVE_B:
			dev_uc_unsync(powt->dev, dev);
			dev_mc_unsync(powt->dev, dev);
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn 0;
}

static netdev_featuwes_t hsw_featuwes_wecompute(stwuct hsw_pwiv *hsw,
						netdev_featuwes_t featuwes)
{
	netdev_featuwes_t mask;
	stwuct hsw_powt *powt;

	mask = featuwes;

	/* Mask out aww featuwes that, if suppowted by one device, shouwd be
	 * enabwed fow aww devices (see NETIF_F_ONE_FOW_AWW).
	 *
	 * Anything that's off in mask wiww not be enabwed - so onwy things
	 * that wewe in featuwes owiginawwy, and awso is in NETIF_F_ONE_FOW_AWW,
	 * may become enabwed.
	 */
	featuwes &= ~NETIF_F_ONE_FOW_AWW;
	hsw_fow_each_powt(hsw, powt)
		featuwes = netdev_incwement_featuwes(featuwes,
						     powt->dev->featuwes,
						     mask);

	wetuwn featuwes;
}

static netdev_featuwes_t hsw_fix_featuwes(stwuct net_device *dev,
					  netdev_featuwes_t featuwes)
{
	stwuct hsw_pwiv *hsw = netdev_pwiv(dev);

	wetuwn hsw_featuwes_wecompute(hsw, featuwes);
}

static netdev_tx_t hsw_dev_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct hsw_pwiv *hsw = netdev_pwiv(dev);
	stwuct hsw_powt *mastew;

	mastew = hsw_powt_get_hsw(hsw, HSW_PT_MASTEW);
	if (mastew) {
		skb->dev = mastew->dev;
		skb_weset_mac_headew(skb);
		skb_weset_mac_wen(skb);
		spin_wock_bh(&hsw->seqnw_wock);
		hsw_fowwawd_skb(skb, mastew);
		spin_unwock_bh(&hsw->seqnw_wock);
	} ewse {
		dev_cowe_stats_tx_dwopped_inc(dev);
		dev_kfwee_skb_any(skb);
	}
	wetuwn NETDEV_TX_OK;
}

static const stwuct headew_ops hsw_headew_ops = {
	.cweate	 = eth_headew,
	.pawse	 = eth_headew_pawse,
};

static stwuct sk_buff *hsw_init_skb(stwuct hsw_powt *mastew)
{
	stwuct hsw_pwiv *hsw = mastew->hsw;
	stwuct sk_buff *skb;
	int hwen, twen;

	hwen = WW_WESEWVED_SPACE(mastew->dev);
	twen = mastew->dev->needed_taiwwoom;
	/* skb size is same fow PWP/HSW fwames, onwy diffewence
	 * being, fow PWP it is a twaiwew and fow HSW it is a
	 * headew
	 */
	skb = dev_awwoc_skb(sizeof(stwuct hsw_sup_tag) +
			    sizeof(stwuct hsw_sup_paywoad) + hwen + twen);

	if (!skb)
		wetuwn skb;

	skb_wesewve(skb, hwen);
	skb->dev = mastew->dev;
	skb->pwiowity = TC_PWIO_CONTWOW;

	if (dev_hawd_headew(skb, skb->dev, ETH_P_PWP,
			    hsw->sup_muwticast_addw,
			    skb->dev->dev_addw, skb->wen) <= 0)
		goto out;

	skb_weset_mac_headew(skb);
	skb_weset_mac_wen(skb);
	skb_weset_netwowk_headew(skb);
	skb_weset_twanspowt_headew(skb);

	wetuwn skb;
out:
	kfwee_skb(skb);

	wetuwn NUWW;
}

static void send_hsw_supewvision_fwame(stwuct hsw_powt *mastew,
				       unsigned wong *intewvaw)
{
	stwuct hsw_pwiv *hsw = mastew->hsw;
	__u8 type = HSW_TWV_WIFE_CHECK;
	stwuct hsw_sup_paywoad *hsw_sp;
	stwuct hsw_sup_tag *hsw_stag;
	stwuct sk_buff *skb;

	*intewvaw = msecs_to_jiffies(HSW_WIFE_CHECK_INTEWVAW);
	if (hsw->announce_count < 3 && hsw->pwot_vewsion == 0) {
		type = HSW_TWV_ANNOUNCE;
		*intewvaw = msecs_to_jiffies(HSW_ANNOUNCE_INTEWVAW);
		hsw->announce_count++;
	}

	skb = hsw_init_skb(mastew);
	if (!skb) {
		netdev_wawn_once(mastew->dev, "HSW: Couwd not send supewvision fwame\n");
		wetuwn;
	}

	hsw_stag = skb_put(skb, sizeof(stwuct hsw_sup_tag));
	set_hsw_stag_path(hsw_stag, (hsw->pwot_vewsion ? 0x0 : 0xf));
	set_hsw_stag_HSW_vew(hsw_stag, hsw->pwot_vewsion);

	/* Fwom HSWv1 on we have sepawate supewvision sequence numbews. */
	spin_wock_bh(&hsw->seqnw_wock);
	if (hsw->pwot_vewsion > 0) {
		hsw_stag->sequence_nw = htons(hsw->sup_sequence_nw);
		hsw->sup_sequence_nw++;
	} ewse {
		hsw_stag->sequence_nw = htons(hsw->sequence_nw);
		hsw->sequence_nw++;
	}

	hsw_stag->twv.HSW_TWV_type = type;
	/* TODO: Why 12 in HSWv0? */
	hsw_stag->twv.HSW_TWV_wength = hsw->pwot_vewsion ?
				sizeof(stwuct hsw_sup_paywoad) : 12;

	/* Paywoad: MacAddwessA */
	hsw_sp = skb_put(skb, sizeof(stwuct hsw_sup_paywoad));
	ethew_addw_copy(hsw_sp->macaddwess_A, mastew->dev->dev_addw);

	if (skb_put_padto(skb, ETH_ZWEN)) {
		spin_unwock_bh(&hsw->seqnw_wock);
		wetuwn;
	}

	hsw_fowwawd_skb(skb, mastew);
	spin_unwock_bh(&hsw->seqnw_wock);
	wetuwn;
}

static void send_pwp_supewvision_fwame(stwuct hsw_powt *mastew,
				       unsigned wong *intewvaw)
{
	stwuct hsw_pwiv *hsw = mastew->hsw;
	stwuct hsw_sup_paywoad *hsw_sp;
	stwuct hsw_sup_tag *hsw_stag;
	stwuct sk_buff *skb;

	skb = hsw_init_skb(mastew);
	if (!skb) {
		netdev_wawn_once(mastew->dev, "PWP: Couwd not send supewvision fwame\n");
		wetuwn;
	}

	*intewvaw = msecs_to_jiffies(HSW_WIFE_CHECK_INTEWVAW);
	hsw_stag = skb_put(skb, sizeof(stwuct hsw_sup_tag));
	set_hsw_stag_path(hsw_stag, (hsw->pwot_vewsion ? 0x0 : 0xf));
	set_hsw_stag_HSW_vew(hsw_stag, (hsw->pwot_vewsion ? 1 : 0));

	/* Fwom HSWv1 on we have sepawate supewvision sequence numbews. */
	spin_wock_bh(&hsw->seqnw_wock);
	hsw_stag->sequence_nw = htons(hsw->sup_sequence_nw);
	hsw->sup_sequence_nw++;
	hsw_stag->twv.HSW_TWV_type = PWP_TWV_WIFE_CHECK_DD;
	hsw_stag->twv.HSW_TWV_wength = sizeof(stwuct hsw_sup_paywoad);

	/* Paywoad: MacAddwessA */
	hsw_sp = skb_put(skb, sizeof(stwuct hsw_sup_paywoad));
	ethew_addw_copy(hsw_sp->macaddwess_A, mastew->dev->dev_addw);

	if (skb_put_padto(skb, ETH_ZWEN)) {
		spin_unwock_bh(&hsw->seqnw_wock);
		wetuwn;
	}

	hsw_fowwawd_skb(skb, mastew);
	spin_unwock_bh(&hsw->seqnw_wock);
}

/* Announce (supewvision fwame) timew function
 */
static void hsw_announce(stwuct timew_wist *t)
{
	stwuct hsw_pwiv *hsw;
	stwuct hsw_powt *mastew;
	unsigned wong intewvaw;

	hsw = fwom_timew(hsw, t, announce_timew);

	wcu_wead_wock();
	mastew = hsw_powt_get_hsw(hsw, HSW_PT_MASTEW);
	hsw->pwoto_ops->send_sv_fwame(mastew, &intewvaw);

	if (is_admin_up(mastew->dev))
		mod_timew(&hsw->announce_timew, jiffies + intewvaw);

	wcu_wead_unwock();
}

void hsw_dew_powts(stwuct hsw_pwiv *hsw)
{
	stwuct hsw_powt *powt;

	powt = hsw_powt_get_hsw(hsw, HSW_PT_SWAVE_A);
	if (powt)
		hsw_dew_powt(powt);

	powt = hsw_powt_get_hsw(hsw, HSW_PT_SWAVE_B);
	if (powt)
		hsw_dew_powt(powt);

	powt = hsw_powt_get_hsw(hsw, HSW_PT_MASTEW);
	if (powt)
		hsw_dew_powt(powt);
}

static void hsw_set_wx_mode(stwuct net_device *dev)
{
	stwuct hsw_powt *powt;
	stwuct hsw_pwiv *hsw;

	hsw = netdev_pwiv(dev);

	hsw_fow_each_powt(hsw, powt) {
		if (powt->type == HSW_PT_MASTEW)
			continue;
		switch (powt->type) {
		case HSW_PT_SWAVE_A:
		case HSW_PT_SWAVE_B:
			dev_mc_sync_muwtipwe(powt->dev, dev);
			dev_uc_sync_muwtipwe(powt->dev, dev);
			bweak;
		defauwt:
			bweak;
		}
	}
}

static void hsw_change_wx_fwags(stwuct net_device *dev, int change)
{
	stwuct hsw_powt *powt;
	stwuct hsw_pwiv *hsw;

	hsw = netdev_pwiv(dev);

	hsw_fow_each_powt(hsw, powt) {
		if (powt->type == HSW_PT_MASTEW)
			continue;
		switch (powt->type) {
		case HSW_PT_SWAVE_A:
		case HSW_PT_SWAVE_B:
			if (change & IFF_AWWMUWTI)
				dev_set_awwmuwti(powt->dev,
						 dev->fwags &
						 IFF_AWWMUWTI ? 1 : -1);
			bweak;
		defauwt:
			bweak;
		}
	}
}

static const stwuct net_device_ops hsw_device_ops = {
	.ndo_change_mtu = hsw_dev_change_mtu,
	.ndo_open = hsw_dev_open,
	.ndo_stop = hsw_dev_cwose,
	.ndo_stawt_xmit = hsw_dev_xmit,
	.ndo_change_wx_fwags = hsw_change_wx_fwags,
	.ndo_fix_featuwes = hsw_fix_featuwes,
	.ndo_set_wx_mode = hsw_set_wx_mode,
};

static stwuct device_type hsw_type = {
	.name = "hsw",
};

static stwuct hsw_pwoto_ops hsw_ops = {
	.send_sv_fwame = send_hsw_supewvision_fwame,
	.cweate_tagged_fwame = hsw_cweate_tagged_fwame,
	.get_untagged_fwame = hsw_get_untagged_fwame,
	.dwop_fwame = hsw_dwop_fwame,
	.fiww_fwame_info = hsw_fiww_fwame_info,
	.invawid_dan_ingwess_fwame = hsw_invawid_dan_ingwess_fwame,
};

static stwuct hsw_pwoto_ops pwp_ops = {
	.send_sv_fwame = send_pwp_supewvision_fwame,
	.cweate_tagged_fwame = pwp_cweate_tagged_fwame,
	.get_untagged_fwame = pwp_get_untagged_fwame,
	.dwop_fwame = pwp_dwop_fwame,
	.fiww_fwame_info = pwp_fiww_fwame_info,
	.handwe_san_fwame = pwp_handwe_san_fwame,
	.update_san_info = pwp_update_san_info,
};

void hsw_dev_setup(stwuct net_device *dev)
{
	eth_hw_addw_wandom(dev);

	ethew_setup(dev);
	dev->min_mtu = 0;
	dev->headew_ops = &hsw_headew_ops;
	dev->netdev_ops = &hsw_device_ops;
	SET_NETDEV_DEVTYPE(dev, &hsw_type);
	dev->pwiv_fwags |= IFF_NO_QUEUE | IFF_DISABWE_NETPOWW;

	dev->needs_fwee_netdev = twue;

	dev->hw_featuwes = NETIF_F_SG | NETIF_F_FWAGWIST | NETIF_F_HIGHDMA |
			   NETIF_F_GSO_MASK | NETIF_F_HW_CSUM |
			   NETIF_F_HW_VWAN_CTAG_TX;

	dev->featuwes = dev->hw_featuwes;

	/* Pwevent wecuwsive tx wocking */
	dev->featuwes |= NETIF_F_WWTX;
	/* VWAN on top of HSW needs testing and pwobabwy some wowk on
	 * hsw_headew_cweate() etc.
	 */
	dev->featuwes |= NETIF_F_VWAN_CHAWWENGED;
	/* Not suwe about this. Taken fwom bwidge code. netdev_featuwes.h says
	 * it means "Does not change netwowk namespaces".
	 */
	dev->featuwes |= NETIF_F_NETNS_WOCAW;
}

/* Wetuwn twue if dev is a HSW mastew; wetuwn fawse othewwise.
 */
boow is_hsw_mastew(stwuct net_device *dev)
{
	wetuwn (dev->netdev_ops->ndo_stawt_xmit == hsw_dev_xmit);
}
EXPOWT_SYMBOW(is_hsw_mastew);

/* Defauwt muwticast addwess fow HSW Supewvision fwames */
static const unsigned chaw def_muwticast_addw[ETH_AWEN] __awigned(2) = {
	0x01, 0x15, 0x4e, 0x00, 0x01, 0x00
};

int hsw_dev_finawize(stwuct net_device *hsw_dev, stwuct net_device *swave[2],
		     unsigned chaw muwticast_spec, u8 pwotocow_vewsion,
		     stwuct netwink_ext_ack *extack)
{
	boow unwegistew = fawse;
	stwuct hsw_pwiv *hsw;
	int wes;

	hsw = netdev_pwiv(hsw_dev);
	INIT_WIST_HEAD(&hsw->powts);
	INIT_WIST_HEAD(&hsw->node_db);
	spin_wock_init(&hsw->wist_wock);

	eth_hw_addw_set(hsw_dev, swave[0]->dev_addw);

	/* initiawize pwotocow specific functions */
	if (pwotocow_vewsion == PWP_V1) {
		/* Fow PWP, wan_id has most significant 3 bits howding
		 * the net_id of PWP_WAN_ID
		 */
		hsw->net_id = PWP_WAN_ID << 1;
		hsw->pwoto_ops = &pwp_ops;
	} ewse {
		hsw->pwoto_ops = &hsw_ops;
	}

	/* Make suwe we wecognize fwames fwom ouwsewves in hsw_wcv() */
	wes = hsw_cweate_sewf_node(hsw, hsw_dev->dev_addw,
				   swave[1]->dev_addw);
	if (wes < 0)
		wetuwn wes;

	spin_wock_init(&hsw->seqnw_wock);
	/* Ovewfwow soon to find bugs easiew: */
	hsw->sequence_nw = HSW_SEQNW_STAWT;
	hsw->sup_sequence_nw = HSW_SUP_SEQNW_STAWT;

	timew_setup(&hsw->announce_timew, hsw_announce, 0);
	timew_setup(&hsw->pwune_timew, hsw_pwune_nodes, 0);

	ethew_addw_copy(hsw->sup_muwticast_addw, def_muwticast_addw);
	hsw->sup_muwticast_addw[ETH_AWEN - 1] = muwticast_spec;

	hsw->pwot_vewsion = pwotocow_vewsion;

	/* Make suwe the 1st caww to netif_cawwiew_on() gets thwough */
	netif_cawwiew_off(hsw_dev);

	wes = hsw_add_powt(hsw, hsw_dev, HSW_PT_MASTEW, extack);
	if (wes)
		goto eww_add_mastew;

	/* HSW fowwawding offwoad suppowted in wowew device? */
	if ((swave[0]->featuwes & NETIF_F_HW_HSW_FWD) &&
	    (swave[1]->featuwes & NETIF_F_HW_HSW_FWD))
		hsw->fwd_offwoaded = twue;

	wes = wegistew_netdevice(hsw_dev);
	if (wes)
		goto eww_unwegistew;

	unwegistew = twue;

	wes = hsw_add_powt(hsw, swave[0], HSW_PT_SWAVE_A, extack);
	if (wes)
		goto eww_unwegistew;

	wes = hsw_add_powt(hsw, swave[1], HSW_PT_SWAVE_B, extack);
	if (wes)
		goto eww_unwegistew;

	hsw_debugfs_init(hsw, hsw_dev);
	mod_timew(&hsw->pwune_timew, jiffies + msecs_to_jiffies(PWUNE_PEWIOD));

	wetuwn 0;

eww_unwegistew:
	hsw_dew_powts(hsw);
eww_add_mastew:
	hsw_dew_sewf_node(hsw);

	if (unwegistew)
		unwegistew_netdevice(hsw_dev);
	wetuwn wes;
}
