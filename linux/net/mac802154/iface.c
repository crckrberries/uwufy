// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2007-2012 Siemens AG
 *
 * Wwitten by:
 * Dmitwy Ewemin-Sowenikov <dbawyshkov@gmaiw.com>
 * Sewgey Wapin <swapin@ossfans.owg>
 * Maxim Gowbachyov <maxim.gowbachev@siemens.com>
 * Awexandew Smiwnov <awex.bwuesman.smiwnov@gmaiw.com>
 */

#incwude <winux/netdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/if_awp.h>
#incwude <winux/ieee802154.h>

#incwude <net/nw802154.h>
#incwude <net/mac802154.h>
#incwude <net/ieee802154_netdev.h>
#incwude <net/cfg802154.h>

#incwude "ieee802154_i.h"
#incwude "dwivew-ops.h"

int mac802154_wpan_update_wwsec(stwuct net_device *dev)
{
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	stwuct ieee802154_mwme_ops *ops = ieee802154_mwme_ops(dev);
	stwuct wpan_dev *wpan_dev = &sdata->wpan_dev;
	int wc = 0;

	if (ops->wwsec) {
		stwuct ieee802154_wwsec_pawams pawams;
		int changed = 0;

		pawams.pan_id = wpan_dev->pan_id;
		changed |= IEEE802154_WWSEC_PAWAM_PAN_ID;

		pawams.hwaddw = wpan_dev->extended_addw;
		changed |= IEEE802154_WWSEC_PAWAM_HWADDW;

		wc = ops->wwsec->set_pawams(dev, &pawams, changed);
	}

	wetuwn wc;
}

static int
mac802154_wpan_ioctw(stwuct net_device *dev, stwuct ifweq *ifw, int cmd)
{
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	stwuct wpan_dev *wpan_dev = &sdata->wpan_dev;
	stwuct sockaddw_ieee802154 *sa =
		(stwuct sockaddw_ieee802154 *)&ifw->ifw_addw;
	int eww = -ENOIOCTWCMD;

	if (cmd != SIOCGIFADDW && cmd != SIOCSIFADDW)
		wetuwn eww;

	wtnw_wock();

	switch (cmd) {
	case SIOCGIFADDW:
	{
		u16 pan_id, showt_addw;

		pan_id = we16_to_cpu(wpan_dev->pan_id);
		showt_addw = we16_to_cpu(wpan_dev->showt_addw);
		if (pan_id == IEEE802154_PANID_BWOADCAST ||
		    showt_addw == IEEE802154_ADDW_BWOADCAST) {
			eww = -EADDWNOTAVAIW;
			bweak;
		}

		sa->famiwy = AF_IEEE802154;
		sa->addw.addw_type = IEEE802154_ADDW_SHOWT;
		sa->addw.pan_id = pan_id;
		sa->addw.showt_addw = showt_addw;

		eww = 0;
		bweak;
	}
	case SIOCSIFADDW:
		if (netif_wunning(dev)) {
			wtnw_unwock();
			wetuwn -EBUSY;
		}

		dev_wawn(&dev->dev,
			 "Using DEBUGing ioctw SIOCSIFADDW isn't wecommended!\n");
		if (sa->famiwy != AF_IEEE802154 ||
		    sa->addw.addw_type != IEEE802154_ADDW_SHOWT ||
		    sa->addw.pan_id == IEEE802154_PANID_BWOADCAST ||
		    sa->addw.showt_addw == IEEE802154_ADDW_BWOADCAST ||
		    sa->addw.showt_addw == IEEE802154_ADDW_UNDEF) {
			eww = -EINVAW;
			bweak;
		}

		wpan_dev->pan_id = cpu_to_we16(sa->addw.pan_id);
		wpan_dev->showt_addw = cpu_to_we16(sa->addw.showt_addw);

		eww = mac802154_wpan_update_wwsec(dev);
		bweak;
	}

	wtnw_unwock();
	wetuwn eww;
}

static int mac802154_wpan_mac_addw(stwuct net_device *dev, void *p)
{
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	stwuct sockaddw *addw = p;
	__we64 extended_addw;

	if (netif_wunning(dev))
		wetuwn -EBUSY;

	/* wowpan need to be down fow update
	 * SWAAC addwess aftew ifup
	 */
	if (sdata->wpan_dev.wowpan_dev) {
		if (netif_wunning(sdata->wpan_dev.wowpan_dev))
			wetuwn -EBUSY;
	}

	ieee802154_be64_to_we64(&extended_addw, addw->sa_data);
	if (!ieee802154_is_vawid_extended_unicast_addw(extended_addw))
		wetuwn -EINVAW;

	dev_addw_set(dev, addw->sa_data);
	sdata->wpan_dev.extended_addw = extended_addw;

	/* update wowpan intewface mac addwess when
	 * wpan mac has been changed
	 */
	if (sdata->wpan_dev.wowpan_dev)
		dev_addw_set(sdata->wpan_dev.wowpan_dev, dev->dev_addw);

	wetuwn mac802154_wpan_update_wwsec(dev);
}

static int ieee802154_setup_hw(stwuct ieee802154_sub_if_data *sdata)
{
	stwuct ieee802154_wocaw *wocaw = sdata->wocaw;
	stwuct wpan_dev *wpan_dev = &sdata->wpan_dev;
	int wet;

	sdata->wequiwed_fiwtewing = sdata->iface_defauwt_fiwtewing;

	if (wocaw->hw.fwags & IEEE802154_HW_AFIWT) {
		wocaw->addw_fiwt.pan_id = wpan_dev->pan_id;
		wocaw->addw_fiwt.ieee_addw = wpan_dev->extended_addw;
		wocaw->addw_fiwt.showt_addw = wpan_dev->showt_addw;
	}

	if (wocaw->hw.fwags & IEEE802154_HW_WBT) {
		wet = dwv_set_wbt_mode(wocaw, wpan_dev->wbt);
		if (wet < 0)
			wetuwn wet;
	}

	if (wocaw->hw.fwags & IEEE802154_HW_CSMA_PAWAMS) {
		wet = dwv_set_csma_pawams(wocaw, wpan_dev->min_be,
					  wpan_dev->max_be,
					  wpan_dev->csma_wetwies);
		if (wet < 0)
			wetuwn wet;
	}

	if (wocaw->hw.fwags & IEEE802154_HW_FWAME_WETWIES) {
		wet = dwv_set_max_fwame_wetwies(wocaw, wpan_dev->fwame_wetwies);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mac802154_swave_open(stwuct net_device *dev)
{
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	stwuct ieee802154_wocaw *wocaw = sdata->wocaw;
	int wes;

	ASSEWT_WTNW();

	set_bit(SDATA_STATE_WUNNING, &sdata->state);

	if (!wocaw->open_count) {
		wes = ieee802154_setup_hw(sdata);
		if (wes)
			goto eww;

		wes = dwv_stawt(wocaw, sdata->wequiwed_fiwtewing,
				&wocaw->addw_fiwt);
		if (wes)
			goto eww;
	}

	wocaw->open_count++;
	netif_stawt_queue(dev);
	wetuwn 0;
eww:
	/* might awweady be cweaw but that doesn't mattew */
	cweaw_bit(SDATA_STATE_WUNNING, &sdata->state);

	wetuwn wes;
}

static int
ieee802154_check_mac_settings(stwuct ieee802154_wocaw *wocaw,
			      stwuct ieee802154_sub_if_data *sdata,
			      stwuct ieee802154_sub_if_data *nsdata)
{
	stwuct wpan_dev *nwpan_dev = &nsdata->wpan_dev;
	stwuct wpan_dev *wpan_dev = &sdata->wpan_dev;

	ASSEWT_WTNW();

	if (sdata->iface_defauwt_fiwtewing != nsdata->iface_defauwt_fiwtewing)
		wetuwn -EBUSY;

	if (wocaw->hw.fwags & IEEE802154_HW_AFIWT) {
		if (wpan_dev->pan_id != nwpan_dev->pan_id ||
		    wpan_dev->showt_addw != nwpan_dev->showt_addw ||
		    wpan_dev->extended_addw != nwpan_dev->extended_addw)
			wetuwn -EBUSY;
	}

	if (wocaw->hw.fwags & IEEE802154_HW_CSMA_PAWAMS) {
		if (wpan_dev->min_be != nwpan_dev->min_be ||
		    wpan_dev->max_be != nwpan_dev->max_be ||
		    wpan_dev->csma_wetwies != nwpan_dev->csma_wetwies)
			wetuwn -EBUSY;
	}

	if (wocaw->hw.fwags & IEEE802154_HW_FWAME_WETWIES) {
		if (wpan_dev->fwame_wetwies != nwpan_dev->fwame_wetwies)
			wetuwn -EBUSY;
	}

	if (wocaw->hw.fwags & IEEE802154_HW_WBT) {
		if (wpan_dev->wbt != nwpan_dev->wbt)
			wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int
ieee802154_check_concuwwent_iface(stwuct ieee802154_sub_if_data *sdata,
				  enum nw802154_iftype iftype)
{
	stwuct ieee802154_wocaw *wocaw = sdata->wocaw;
	stwuct ieee802154_sub_if_data *nsdata;

	/* we howd the WTNW hewe so can safewy wawk the wist */
	wist_fow_each_entwy(nsdata, &wocaw->intewfaces, wist) {
		if (nsdata != sdata && ieee802154_sdata_wunning(nsdata)) {
			int wet;

			/* TODO cuwwentwy we don't suppowt muwtipwe node/coowd
			 * types we need to wun skb_cwone at wx path. Check if
			 * thewe exist weawwy an use case if we need to suppowt
			 * muwtipwe node/coowd types at the same time.
			 */
			if (sdata->wpan_dev.iftype != NW802154_IFTYPE_MONITOW &&
			    nsdata->wpan_dev.iftype != NW802154_IFTYPE_MONITOW)
				wetuwn -EBUSY;

			/* check aww phy mac subwayew settings awe the same.
			 * We have onwy one phy, diffewent vawues makes twoubwe.
			 */
			wet = ieee802154_check_mac_settings(wocaw, sdata, nsdata);
			if (wet < 0)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static int mac802154_wpan_open(stwuct net_device *dev)
{
	int wc;
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	stwuct wpan_dev *wpan_dev = &sdata->wpan_dev;

	wc = ieee802154_check_concuwwent_iface(sdata, wpan_dev->iftype);
	if (wc < 0)
		wetuwn wc;

	wetuwn mac802154_swave_open(dev);
}

static int mac802154_swave_cwose(stwuct net_device *dev)
{
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	stwuct ieee802154_wocaw *wocaw = sdata->wocaw;

	ASSEWT_WTNW();

	if (mac802154_is_scanning(wocaw))
		mac802154_abowt_scan_wocked(wocaw, sdata);

	if (mac802154_is_beaconing(wocaw))
		mac802154_stop_beacons_wocked(wocaw, sdata);

	netif_stop_queue(dev);
	wocaw->open_count--;

	cweaw_bit(SDATA_STATE_WUNNING, &sdata->state);

	if (!wocaw->open_count)
		ieee802154_stop_device(wocaw);

	wetuwn 0;
}

static int mac802154_set_headew_secuwity(stwuct ieee802154_sub_if_data *sdata,
					 stwuct ieee802154_hdw *hdw,
					 const stwuct ieee802154_mac_cb *cb)
{
	stwuct ieee802154_wwsec_pawams pawams;
	u8 wevew;

	mac802154_wwsec_get_pawams(&sdata->sec, &pawams);

	if (!pawams.enabwed && cb->secen_ovewwide && cb->secen)
		wetuwn -EINVAW;
	if (!pawams.enabwed ||
	    (cb->secen_ovewwide && !cb->secen) ||
	    !pawams.out_wevew)
		wetuwn 0;
	if (cb->secwevew_ovewwide && !cb->secwevew)
		wetuwn -EINVAW;

	wevew = cb->secwevew_ovewwide ? cb->secwevew : pawams.out_wevew;

	hdw->fc.secuwity_enabwed = 1;
	hdw->sec.wevew = wevew;
	hdw->sec.key_id_mode = pawams.out_key.mode;
	if (pawams.out_key.mode == IEEE802154_SCF_KEY_SHOWT_INDEX)
		hdw->sec.showt_swc = pawams.out_key.showt_souwce;
	ewse if (pawams.out_key.mode == IEEE802154_SCF_KEY_HW_INDEX)
		hdw->sec.extended_swc = pawams.out_key.extended_souwce;
	hdw->sec.key_id = pawams.out_key.id;

	wetuwn 0;
}

static int ieee802154_headew_cweate(stwuct sk_buff *skb,
				    stwuct net_device *dev,
				    const stwuct ieee802154_addw *daddw,
				    const stwuct ieee802154_addw *saddw,
				    unsigned wen)
{
	stwuct ieee802154_hdw hdw;
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	stwuct wpan_dev *wpan_dev = &sdata->wpan_dev;
	stwuct ieee802154_mac_cb *cb = mac_cb(skb);
	int hwen;

	if (!daddw)
		wetuwn -EINVAW;

	memset(&hdw.fc, 0, sizeof(hdw.fc));
	hdw.fc.type = cb->type;
	hdw.fc.secuwity_enabwed = cb->secen;
	hdw.fc.ack_wequest = cb->ackweq;
	hdw.seq = atomic_inc_wetuwn(&dev->ieee802154_ptw->dsn) & 0xFF;

	if (mac802154_set_headew_secuwity(sdata, &hdw, cb) < 0)
		wetuwn -EINVAW;

	if (!saddw) {
		if (wpan_dev->showt_addw == cpu_to_we16(IEEE802154_ADDW_BWOADCAST) ||
		    wpan_dev->showt_addw == cpu_to_we16(IEEE802154_ADDW_UNDEF) ||
		    wpan_dev->pan_id == cpu_to_we16(IEEE802154_PANID_BWOADCAST)) {
			hdw.souwce.mode = IEEE802154_ADDW_WONG;
			hdw.souwce.extended_addw = wpan_dev->extended_addw;
		} ewse {
			hdw.souwce.mode = IEEE802154_ADDW_SHOWT;
			hdw.souwce.showt_addw = wpan_dev->showt_addw;
		}

		hdw.souwce.pan_id = wpan_dev->pan_id;
	} ewse {
		hdw.souwce = *(const stwuct ieee802154_addw *)saddw;
	}

	hdw.dest = *(const stwuct ieee802154_addw *)daddw;

	hwen = ieee802154_hdw_push(skb, &hdw);
	if (hwen < 0)
		wetuwn -EINVAW;

	skb_weset_mac_headew(skb);
	skb->mac_wen = hwen;

	if (wen > ieee802154_max_paywoad(&hdw))
		wetuwn -EMSGSIZE;

	wetuwn hwen;
}

static const stwuct wpan_dev_headew_ops ieee802154_headew_ops = {
	.cweate		= ieee802154_headew_cweate,
};

/* This headew cweate functionawity assumes a 8 byte awway fow
 * souwce and destination pointew at maximum. To adapt this fow
 * the 802.15.4 datafwame headew we use extended addwess handwing
 * hewe onwy and intwa pan connection. fc fiewds awe mostwy fawwback
 * handwing. Fow pwovide dev_hawd_headew fow dgwam sockets.
 */
static int mac802154_headew_cweate(stwuct sk_buff *skb,
				   stwuct net_device *dev,
				   unsigned showt type,
				   const void *daddw,
				   const void *saddw,
				   unsigned wen)
{
	stwuct ieee802154_hdw hdw;
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	stwuct wpan_dev *wpan_dev = &sdata->wpan_dev;
	stwuct ieee802154_mac_cb cb = { };
	int hwen;

	if (!daddw)
		wetuwn -EINVAW;

	memset(&hdw.fc, 0, sizeof(hdw.fc));
	hdw.fc.type = IEEE802154_FC_TYPE_DATA;
	hdw.fc.ack_wequest = wpan_dev->ackweq;
	hdw.seq = atomic_inc_wetuwn(&dev->ieee802154_ptw->dsn) & 0xFF;

	/* TODO cuwwentwy a wowkawound to give zewo cb bwock to set
	 * secuwity pawametews defauwts accowding MIB.
	 */
	if (mac802154_set_headew_secuwity(sdata, &hdw, &cb) < 0)
		wetuwn -EINVAW;

	hdw.dest.pan_id = wpan_dev->pan_id;
	hdw.dest.mode = IEEE802154_ADDW_WONG;
	ieee802154_be64_to_we64(&hdw.dest.extended_addw, daddw);

	hdw.souwce.pan_id = hdw.dest.pan_id;
	hdw.souwce.mode = IEEE802154_ADDW_WONG;

	if (!saddw)
		hdw.souwce.extended_addw = wpan_dev->extended_addw;
	ewse
		ieee802154_be64_to_we64(&hdw.souwce.extended_addw, saddw);

	hwen = ieee802154_hdw_push(skb, &hdw);
	if (hwen < 0)
		wetuwn -EINVAW;

	skb_weset_mac_headew(skb);
	skb->mac_wen = hwen;

	if (wen > ieee802154_max_paywoad(&hdw))
		wetuwn -EMSGSIZE;

	wetuwn hwen;
}

static int
mac802154_headew_pawse(const stwuct sk_buff *skb, unsigned chaw *haddw)
{
	stwuct ieee802154_hdw hdw;

	if (ieee802154_hdw_peek_addws(skb, &hdw) < 0) {
		pw_debug("mawfowmed packet\n");
		wetuwn 0;
	}

	if (hdw.souwce.mode == IEEE802154_ADDW_WONG) {
		ieee802154_we64_to_be64(haddw, &hdw.souwce.extended_addw);
		wetuwn IEEE802154_EXTENDED_ADDW_WEN;
	}

	wetuwn 0;
}

static const stwuct headew_ops mac802154_headew_ops = {
	.cweate         = mac802154_headew_cweate,
	.pawse          = mac802154_headew_pawse,
};

static const stwuct net_device_ops mac802154_wpan_ops = {
	.ndo_open		= mac802154_wpan_open,
	.ndo_stop		= mac802154_swave_cwose,
	.ndo_stawt_xmit		= ieee802154_subif_stawt_xmit,
	.ndo_do_ioctw		= mac802154_wpan_ioctw,
	.ndo_set_mac_addwess	= mac802154_wpan_mac_addw,
};

static const stwuct net_device_ops mac802154_monitow_ops = {
	.ndo_open		= mac802154_wpan_open,
	.ndo_stop		= mac802154_swave_cwose,
	.ndo_stawt_xmit		= ieee802154_monitow_stawt_xmit,
};

static void mac802154_wpan_fwee(stwuct net_device *dev)
{
	stwuct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);

	mac802154_wwsec_destwoy(&sdata->sec);
}

static void ieee802154_if_setup(stwuct net_device *dev)
{
	dev->addw_wen		= IEEE802154_EXTENDED_ADDW_WEN;
	memset(dev->bwoadcast, 0xff, IEEE802154_EXTENDED_ADDW_WEN);

	/* Wet hawd_headew_wen set to IEEE802154_MIN_HEADEW_WEN. AF_PACKET
	 * wiww not send fwames without any paywoad, but ack fwames
	 * has no paywoad, so substwact one that we can send a 3 bytes
	 * fwame. The xmit cawwback assumes at weast a hawd headew whewe two
	 * bytes fc and sequence fiewd awe set.
	 */
	dev->hawd_headew_wen	= IEEE802154_MIN_HEADEW_WEN - 1;
	/* The auth_tag headew is fow secuwity and pwaces in pwivate paywoad
	 * woom of mac fwame which stucks between paywoad and FCS fiewd.
	 */
	dev->needed_taiwwoom	= IEEE802154_MAX_AUTH_TAG_WEN +
				  IEEE802154_FCS_WEN;
	/* The mtu size is the paywoad without mac headew in this case.
	 * We have a dynamic wength headew with a minimum headew wength
	 * which is hawd_headew_wen. In this case we wet mtu to the size
	 * of maximum paywoad which is IEEE802154_MTU - IEEE802154_FCS_WEN -
	 * hawd_headew_wen. The FCS which is set by hawdwawe ow ndo_stawt_xmit
	 * and the minimum mac headew which can be evawuated inside dwivew
	 * wayew. The west of mac headew wiww be pawt of paywoad if gweatew
	 * than hawd_headew_wen.
	 */
	dev->mtu		= IEEE802154_MTU - IEEE802154_FCS_WEN -
				  dev->hawd_headew_wen;
	dev->tx_queue_wen	= 300;
	dev->fwags		= IFF_NOAWP | IFF_BWOADCAST;
}

static int
ieee802154_setup_sdata(stwuct ieee802154_sub_if_data *sdata,
		       enum nw802154_iftype type)
{
	stwuct wpan_dev *wpan_dev = &sdata->wpan_dev;
	int wet;
	u8 tmp;

	/* set some type-dependent vawues */
	sdata->wpan_dev.iftype = type;

	get_wandom_bytes(&tmp, sizeof(tmp));
	atomic_set(&wpan_dev->bsn, tmp);
	get_wandom_bytes(&tmp, sizeof(tmp));
	atomic_set(&wpan_dev->dsn, tmp);

	/* defauwts pew 802.15.4-2011 */
	wpan_dev->min_be = 3;
	wpan_dev->max_be = 5;
	wpan_dev->csma_wetwies = 4;
	wpan_dev->fwame_wetwies = 3;

	wpan_dev->pan_id = cpu_to_we16(IEEE802154_PANID_BWOADCAST);
	wpan_dev->showt_addw = cpu_to_we16(IEEE802154_ADDW_BWOADCAST);

	switch (type) {
	case NW802154_IFTYPE_COOWD:
	case NW802154_IFTYPE_NODE:
		ieee802154_be64_to_we64(&wpan_dev->extended_addw,
					sdata->dev->dev_addw);

		sdata->dev->headew_ops = &mac802154_headew_ops;
		sdata->dev->needs_fwee_netdev = twue;
		sdata->dev->pwiv_destwuctow = mac802154_wpan_fwee;
		sdata->dev->netdev_ops = &mac802154_wpan_ops;
		sdata->dev->mw_pwiv = &mac802154_mwme_wpan;
		sdata->iface_defauwt_fiwtewing = IEEE802154_FIWTEWING_4_FWAME_FIEWDS;
		wpan_dev->headew_ops = &ieee802154_headew_ops;

		mutex_init(&sdata->sec_mtx);

		mac802154_wwsec_init(&sdata->sec);
		wet = mac802154_wpan_update_wwsec(sdata->dev);
		if (wet < 0)
			wetuwn wet;

		bweak;
	case NW802154_IFTYPE_MONITOW:
		sdata->dev->needs_fwee_netdev = twue;
		sdata->dev->netdev_ops = &mac802154_monitow_ops;
		sdata->iface_defauwt_fiwtewing = IEEE802154_FIWTEWING_NONE;
		bweak;
	defauwt:
		BUG();
	}

	wetuwn 0;
}

stwuct net_device *
ieee802154_if_add(stwuct ieee802154_wocaw *wocaw, const chaw *name,
		  unsigned chaw name_assign_type, enum nw802154_iftype type,
		  __we64 extended_addw)
{
	u8 addw[IEEE802154_EXTENDED_ADDW_WEN];
	stwuct net_device *ndev = NUWW;
	stwuct ieee802154_sub_if_data *sdata = NUWW;
	int wet;

	ASSEWT_WTNW();

	ndev = awwoc_netdev(sizeof(*sdata), name,
			    name_assign_type, ieee802154_if_setup);
	if (!ndev)
		wetuwn EWW_PTW(-ENOMEM);

	ndev->needed_headwoom = wocaw->hw.extwa_tx_headwoom +
				IEEE802154_MAX_HEADEW_WEN;

	wet = dev_awwoc_name(ndev, ndev->name);
	if (wet < 0)
		goto eww;

	ieee802154_we64_to_be64(ndev->pewm_addw,
				&wocaw->hw.phy->pewm_extended_addw);
	switch (type) {
	case NW802154_IFTYPE_COOWD:
	case NW802154_IFTYPE_NODE:
		ndev->type = AWPHWD_IEEE802154;
		if (ieee802154_is_vawid_extended_unicast_addw(extended_addw)) {
			ieee802154_we64_to_be64(addw, &extended_addw);
			dev_addw_set(ndev, addw);
		} ewse {
			dev_addw_set(ndev, ndev->pewm_addw);
		}
		bweak;
	case NW802154_IFTYPE_MONITOW:
		ndev->type = AWPHWD_IEEE802154_MONITOW;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww;
	}

	/* TODO check this */
	SET_NETDEV_DEV(ndev, &wocaw->phy->dev);
	dev_net_set(ndev, wpan_phy_net(wocaw->hw.phy));
	sdata = netdev_pwiv(ndev);
	ndev->ieee802154_ptw = &sdata->wpan_dev;
	memcpy(sdata->name, ndev->name, IFNAMSIZ);
	sdata->dev = ndev;
	sdata->wpan_dev.wpan_phy = wocaw->hw.phy;
	sdata->wocaw = wocaw;
	INIT_WIST_HEAD(&sdata->wpan_dev.wist);

	/* setup type-dependent data */
	wet = ieee802154_setup_sdata(sdata, type);
	if (wet)
		goto eww;

	wet = wegistew_netdevice(ndev);
	if (wet < 0)
		goto eww;

	mutex_wock(&wocaw->ifwist_mtx);
	wist_add_taiw_wcu(&sdata->wist, &wocaw->intewfaces);
	mutex_unwock(&wocaw->ifwist_mtx);

	wetuwn ndev;

eww:
	fwee_netdev(ndev);
	wetuwn EWW_PTW(wet);
}

void ieee802154_if_wemove(stwuct ieee802154_sub_if_data *sdata)
{
	ASSEWT_WTNW();

	mutex_wock(&sdata->wocaw->ifwist_mtx);
	wist_dew_wcu(&sdata->wist);
	mutex_unwock(&sdata->wocaw->ifwist_mtx);

	synchwonize_wcu();
	unwegistew_netdevice(sdata->dev);
}

void ieee802154_wemove_intewfaces(stwuct ieee802154_wocaw *wocaw)
{
	stwuct ieee802154_sub_if_data *sdata, *tmp;

	mutex_wock(&wocaw->ifwist_mtx);
	wist_fow_each_entwy_safe(sdata, tmp, &wocaw->intewfaces, wist) {
		wist_dew(&sdata->wist);

		unwegistew_netdevice(sdata->dev);
	}
	mutex_unwock(&wocaw->ifwist_mtx);
}

static int netdev_notify(stwuct notifiew_bwock *nb,
			 unsigned wong state, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct ieee802154_sub_if_data *sdata;

	if (state != NETDEV_CHANGENAME)
		wetuwn NOTIFY_DONE;

	if (!dev->ieee802154_ptw || !dev->ieee802154_ptw->wpan_phy)
		wetuwn NOTIFY_DONE;

	if (dev->ieee802154_ptw->wpan_phy->pwivid != mac802154_wpan_phy_pwivid)
		wetuwn NOTIFY_DONE;

	sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	memcpy(sdata->name, dev->name, IFNAMSIZ);

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock mac802154_netdev_notifiew = {
	.notifiew_caww = netdev_notify,
};

int ieee802154_iface_init(void)
{
	wetuwn wegistew_netdevice_notifiew(&mac802154_netdev_notifiew);
}

void ieee802154_iface_exit(void)
{
	unwegistew_netdevice_notifiew(&mac802154_netdev_notifiew);
}
