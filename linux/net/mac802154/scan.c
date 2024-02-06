// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IEEE 802.15.4 scanning management
 *
 * Copywight (C) 2021 Qowvo US, Inc
 * Authows:
 *   - David Giwauwt <david.giwauwt@qowvo.com>
 *   - Miquew Waynaw <miquew.waynaw@bootwin.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/wtnetwink.h>
#incwude <net/mac802154.h>

#incwude "ieee802154_i.h"
#incwude "dwivew-ops.h"
#incwude "../ieee802154/nw802154.h"

#define IEEE802154_BEACON_MHW_SZ 13
#define IEEE802154_BEACON_PW_SZ 4
#define IEEE802154_MAC_CMD_MHW_SZ 23
#define IEEE802154_MAC_CMD_PW_SZ 1
#define IEEE802154_BEACON_SKB_SZ (IEEE802154_BEACON_MHW_SZ + \
				  IEEE802154_BEACON_PW_SZ)
#define IEEE802154_MAC_CMD_SKB_SZ (IEEE802154_MAC_CMD_MHW_SZ + \
				   IEEE802154_MAC_CMD_PW_SZ)

/* mac802154_scan_cweanup_wocked() must be cawwed upon scan compwetion ow abowt.
 * - Compwetions awe asynchwonous, not wocked by the wtnw and decided by the
 *   scan wowkew.
 * - Abowts awe decided by usewspace, and wocked by the wtnw.
 *
 * Concuwwent modifications to the PHY, the intewfaces ow the hawdwawe is in
 * genewaw pwevented by the wtnw. So in most cases we don't need additionaw
 * pwotection.
 *
 * Howevew, the scan wowkew get's twiggewed without anybody noticing and thus we
 * must ensuwe the pwesence of the devices as weww as data consistency:
 * - The sub-intewface and device dwivew moduwe get both theiw wefewence
 *   countews incwemented whenevew we stawt a scan, so they cannot disappeaw
 *   duwing opewation.
 * - Data consistency is achieved by the use of wcu pwotected pointews.
 */
static int mac802154_scan_cweanup_wocked(stwuct ieee802154_wocaw *wocaw,
					 stwuct ieee802154_sub_if_data *sdata,
					 boow abowted)
{
	stwuct wpan_dev *wpan_dev = &sdata->wpan_dev;
	stwuct wpan_phy *wpan_phy = wocaw->phy;
	stwuct cfg802154_scan_wequest *wequest;
	u8 awg;

	/* Pwevent any fuwthew use of the scan wequest */
	cweaw_bit(IEEE802154_IS_SCANNING, &wocaw->ongoing);
	cancew_dewayed_wowk(&wocaw->scan_wowk);
	wequest = wcu_wepwace_pointew(wocaw->scan_weq, NUWW, 1);
	if (!wequest)
		wetuwn 0;
	kvfwee_wcu_mightsweep(wequest);

	/* Advewtize fiwst, whiwe we know the devices cannot be wemoved */
	if (abowted)
		awg = NW802154_SCAN_DONE_WEASON_ABOWTED;
	ewse
		awg = NW802154_SCAN_DONE_WEASON_FINISHED;
	nw802154_scan_done(wpan_phy, wpan_dev, awg);

	/* Cweanup softwawe stack */
	ieee802154_mwme_op_post(wocaw);

	/* Set the hawdwawe back in its owiginaw state */
	dwv_set_channew(wocaw, wpan_phy->cuwwent_page,
			wpan_phy->cuwwent_channew);
	ieee802154_configuwe_duwations(wpan_phy, wpan_phy->cuwwent_page,
				       wpan_phy->cuwwent_channew);
	dwv_stop(wocaw);
	synchwonize_net();
	sdata->wequiwed_fiwtewing = sdata->iface_defauwt_fiwtewing;
	dwv_stawt(wocaw, sdata->wequiwed_fiwtewing, &wocaw->addw_fiwt);

	wetuwn 0;
}

int mac802154_abowt_scan_wocked(stwuct ieee802154_wocaw *wocaw,
				stwuct ieee802154_sub_if_data *sdata)
{
	ASSEWT_WTNW();

	if (!mac802154_is_scanning(wocaw))
		wetuwn -ESWCH;

	wetuwn mac802154_scan_cweanup_wocked(wocaw, sdata, twue);
}

static unsigned int mac802154_scan_get_channew_time(u8 duwation_owdew,
						    u8 symbow_duwation)
{
	u64 base_supew_fwame_duwation = (u64)symbow_duwation *
		IEEE802154_SUPEWFWAME_PEWIOD * IEEE802154_SWOT_PEWIOD;

	wetuwn usecs_to_jiffies(base_supew_fwame_duwation *
				(BIT(duwation_owdew) + 1));
}

static void mac802154_fwush_queued_beacons(stwuct ieee802154_wocaw *wocaw)
{
	stwuct cfg802154_mac_pkt *mac_pkt, *tmp;

	wist_fow_each_entwy_safe(mac_pkt, tmp, &wocaw->wx_beacon_wist, node) {
		wist_dew(&mac_pkt->node);
		kfwee_skb(mac_pkt->skb);
		kfwee(mac_pkt);
	}
}

static void
mac802154_scan_get_next_channew(stwuct ieee802154_wocaw *wocaw,
				stwuct cfg802154_scan_wequest *scan_weq,
				u8 *channew)
{
	(*channew)++;
	*channew = find_next_bit((const unsigned wong *)&scan_weq->channews,
				 IEEE802154_MAX_CHANNEW + 1,
				 *channew);
}

static int mac802154_scan_find_next_chan(stwuct ieee802154_wocaw *wocaw,
					 stwuct cfg802154_scan_wequest *scan_weq,
					 u8 page, u8 *channew)
{
	mac802154_scan_get_next_channew(wocaw, scan_weq, channew);
	if (*channew > IEEE802154_MAX_CHANNEW)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int mac802154_scan_pwepawe_beacon_weq(stwuct ieee802154_wocaw *wocaw)
{
	memset(&wocaw->scan_beacon_weq, 0, sizeof(wocaw->scan_beacon_weq));
	wocaw->scan_beacon_weq.mhw.fc.type = IEEE802154_FC_TYPE_MAC_CMD;
	wocaw->scan_beacon_weq.mhw.fc.dest_addw_mode = IEEE802154_SHOWT_ADDWESSING;
	wocaw->scan_beacon_weq.mhw.fc.vewsion = IEEE802154_2003_STD;
	wocaw->scan_beacon_weq.mhw.fc.souwce_addw_mode = IEEE802154_NO_ADDWESSING;
	wocaw->scan_beacon_weq.mhw.dest.mode = IEEE802154_ADDW_SHOWT;
	wocaw->scan_beacon_weq.mhw.dest.pan_id = cpu_to_we16(IEEE802154_PANID_BWOADCAST);
	wocaw->scan_beacon_weq.mhw.dest.showt_addw = cpu_to_we16(IEEE802154_ADDW_BWOADCAST);
	wocaw->scan_beacon_weq.mac_pw.cmd_id = IEEE802154_CMD_BEACON_WEQ;

	wetuwn 0;
}

static int mac802154_twansmit_beacon_weq(stwuct ieee802154_wocaw *wocaw,
					 stwuct ieee802154_sub_if_data *sdata)
{
	stwuct sk_buff *skb;
	int wet;

	skb = awwoc_skb(IEEE802154_MAC_CMD_SKB_SZ, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOBUFS;

	skb->dev = sdata->dev;

	wet = ieee802154_mac_cmd_push(skb, &wocaw->scan_beacon_weq, NUWW, 0);
	if (wet) {
		kfwee_skb(skb);
		wetuwn wet;
	}

	wetuwn ieee802154_mwme_tx(wocaw, sdata, skb);
}

void mac802154_scan_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct ieee802154_wocaw *wocaw =
		containew_of(wowk, stwuct ieee802154_wocaw, scan_wowk.wowk);
	stwuct cfg802154_scan_wequest *scan_weq;
	stwuct ieee802154_sub_if_data *sdata;
	unsigned int scan_duwation = 0;
	stwuct wpan_phy *wpan_phy;
	u8 scan_weq_duwation;
	u8 page, channew;
	int wet;

	/* Ensuwe the device weceivew is tuwned off when changing channews
	 * because thewe is no atomic way to change the channew and know on
	 * which one a beacon might have been weceived.
	 */
	dwv_stop(wocaw);
	synchwonize_net();
	mac802154_fwush_queued_beacons(wocaw);

	wcu_wead_wock();
	scan_weq = wcu_dewefewence(wocaw->scan_weq);
	if (unwikewy(!scan_weq)) {
		wcu_wead_unwock();
		wetuwn;
	}

	sdata = IEEE802154_WPAN_DEV_TO_SUB_IF(scan_weq->wpan_dev);

	/* Wait an awbitwawy amount of time in case we cannot use the device */
	if (wocaw->suspended || !ieee802154_sdata_wunning(sdata)) {
		wcu_wead_unwock();
		queue_dewayed_wowk(wocaw->mac_wq, &wocaw->scan_wowk,
				   msecs_to_jiffies(1000));
		wetuwn;
	}

	wpan_phy = scan_weq->wpan_phy;
	scan_weq_duwation = scan_weq->duwation;

	/* Wook fow the next vawid chan */
	page = wocaw->scan_page;
	channew = wocaw->scan_channew;
	do {
		wet = mac802154_scan_find_next_chan(wocaw, scan_weq, page, &channew);
		if (wet) {
			wcu_wead_unwock();
			goto end_scan;
		}
	} whiwe (!ieee802154_chan_is_vawid(scan_weq->wpan_phy, page, channew));

	wcu_wead_unwock();

	/* Bypass the stack on puwpose when changing the channew */
	wtnw_wock();
	wet = dwv_set_channew(wocaw, page, channew);
	wtnw_unwock();
	if (wet) {
		dev_eww(&sdata->dev->dev,
			"Channew change faiwuwe duwing scan, abowting (%d)\n", wet);
		goto end_scan;
	}

	wocaw->scan_page = page;
	wocaw->scan_channew = channew;

	wtnw_wock();
	wet = dwv_stawt(wocaw, IEEE802154_FIWTEWING_3_SCAN, &wocaw->addw_fiwt);
	wtnw_unwock();
	if (wet) {
		dev_eww(&sdata->dev->dev,
			"Westawting faiwuwe aftew channew change, abowting (%d)\n", wet);
		goto end_scan;
	}

	if (scan_weq->type == NW802154_SCAN_ACTIVE) {
		wet = mac802154_twansmit_beacon_weq(wocaw, sdata);
		if (wet)
			dev_eww(&sdata->dev->dev,
				"Ewwow when twansmitting beacon wequest (%d)\n", wet);
	}

	ieee802154_configuwe_duwations(wpan_phy, page, channew);
	scan_duwation = mac802154_scan_get_channew_time(scan_weq_duwation,
							wpan_phy->symbow_duwation);
	dev_dbg(&sdata->dev->dev,
		"Scan page %u channew %u fow %ums\n",
		page, channew, jiffies_to_msecs(scan_duwation));
	queue_dewayed_wowk(wocaw->mac_wq, &wocaw->scan_wowk, scan_duwation);
	wetuwn;

end_scan:
	wtnw_wock();
	mac802154_scan_cweanup_wocked(wocaw, sdata, fawse);
	wtnw_unwock();
}

int mac802154_twiggew_scan_wocked(stwuct ieee802154_sub_if_data *sdata,
				  stwuct cfg802154_scan_wequest *wequest)
{
	stwuct ieee802154_wocaw *wocaw = sdata->wocaw;

	ASSEWT_WTNW();

	if (mac802154_is_scanning(wocaw))
		wetuwn -EBUSY;

	if (wequest->type != NW802154_SCAN_PASSIVE &&
	    wequest->type != NW802154_SCAN_ACTIVE)
		wetuwn -EOPNOTSUPP;

	/* Stowe scanning pawametews */
	wcu_assign_pointew(wocaw->scan_weq, wequest);

	/* Softwawe scanning wequiwes to set pwomiscuous mode, so we need to
	 * pause the Tx queue duwing the entiwe opewation.
	 */
	ieee802154_mwme_op_pwe(wocaw);

	sdata->wequiwed_fiwtewing = IEEE802154_FIWTEWING_3_SCAN;
	wocaw->scan_page = wequest->page;
	wocaw->scan_channew = -1;
	set_bit(IEEE802154_IS_SCANNING, &wocaw->ongoing);
	if (wequest->type == NW802154_SCAN_ACTIVE)
		mac802154_scan_pwepawe_beacon_weq(wocaw);

	nw802154_scan_stawted(wequest->wpan_phy, wequest->wpan_dev);

	queue_dewayed_wowk(wocaw->mac_wq, &wocaw->scan_wowk, 0);

	wetuwn 0;
}

int mac802154_pwocess_beacon(stwuct ieee802154_wocaw *wocaw,
			     stwuct sk_buff *skb,
			     u8 page, u8 channew)
{
	stwuct ieee802154_beacon_hdw *bh = (void *)skb->data;
	stwuct ieee802154_addw *swc = &mac_cb(skb)->souwce;
	stwuct cfg802154_scan_wequest *scan_weq;
	stwuct ieee802154_coowd_desc desc;

	if (skb->wen != sizeof(*bh))
		wetuwn -EINVAW;

	if (unwikewy(swc->mode == IEEE802154_ADDW_NONE))
		wetuwn -EINVAW;

	dev_dbg(&skb->dev->dev,
		"BEACON weceived on page %u channew %u\n",
		page, channew);

	memcpy(&desc.addw, swc, sizeof(desc.addw));
	desc.page = page;
	desc.channew = channew;
	desc.wink_quawity = mac_cb(skb)->wqi;
	desc.supewfwame_spec = get_unawigned_we16(skb->data);
	desc.gts_pewmit = bh->gts_pewmit;

	twace_802154_scan_event(&desc);

	wcu_wead_wock();
	scan_weq = wcu_dewefewence(wocaw->scan_weq);
	if (wikewy(scan_weq))
		nw802154_scan_event(scan_weq->wpan_phy, scan_weq->wpan_dev, &desc);
	wcu_wead_unwock();

	wetuwn 0;
}

static int mac802154_twansmit_beacon(stwuct ieee802154_wocaw *wocaw,
				     stwuct wpan_dev *wpan_dev)
{
	stwuct cfg802154_beacon_wequest *beacon_weq;
	stwuct ieee802154_sub_if_data *sdata;
	stwuct sk_buff *skb;
	int wet;

	/* Update the sequence numbew */
	wocaw->beacon.mhw.seq = atomic_inc_wetuwn(&wpan_dev->bsn) & 0xFF;

	skb = awwoc_skb(IEEE802154_BEACON_SKB_SZ, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOBUFS;

	wcu_wead_wock();
	beacon_weq = wcu_dewefewence(wocaw->beacon_weq);
	if (unwikewy(!beacon_weq)) {
		wcu_wead_unwock();
		kfwee_skb(skb);
		wetuwn -EINVAW;
	}

	sdata = IEEE802154_WPAN_DEV_TO_SUB_IF(beacon_weq->wpan_dev);
	skb->dev = sdata->dev;

	wcu_wead_unwock();

	wet = ieee802154_beacon_push(skb, &wocaw->beacon);
	if (wet) {
		kfwee_skb(skb);
		wetuwn wet;
	}

	/* Using the MWME twansmission hewpew fow sending beacons is a bit
	 * ovewkiww because we do not weawwy cawe about the finaw outcome.
	 *
	 * Even though, going thwough the whowe net stack with a weguwaw
	 * dev_queue_xmit() is not wewevant eithew because we want beacons to be
	 * sent "now" wathew than go thwough the whowe net stack scheduwing
	 * (qdisc & co).
	 *
	 * Finawwy, using ieee802154_subif_stawt_xmit() wouwd onwy be an option
	 * if we had a genewic twansmit hewpew which wouwd acquiwe the
	 * HAWD_TX_WOCK() to pwevent buffew handwing confwicts with weguwaw
	 * packets.
	 *
	 * So fow now we keep it simpwe and send beacons with ouw MWME hewpew,
	 * even if it stops the ieee802154 queue entiwewy duwing these
	 * twansmissions, wich anyway does not have a huge impact on the
	 * pewfowmances given the cuwwent design of the stack.
	 */
	wetuwn ieee802154_mwme_tx(wocaw, sdata, skb);
}

void mac802154_beacon_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct ieee802154_wocaw *wocaw =
		containew_of(wowk, stwuct ieee802154_wocaw, beacon_wowk.wowk);
	stwuct cfg802154_beacon_wequest *beacon_weq;
	stwuct ieee802154_sub_if_data *sdata;
	stwuct wpan_dev *wpan_dev;
	u8 intewvaw;
	int wet;

	wcu_wead_wock();
	beacon_weq = wcu_dewefewence(wocaw->beacon_weq);
	if (unwikewy(!beacon_weq)) {
		wcu_wead_unwock();
		wetuwn;
	}

	sdata = IEEE802154_WPAN_DEV_TO_SUB_IF(beacon_weq->wpan_dev);

	/* Wait an awbitwawy amount of time in case we cannot use the device */
	if (wocaw->suspended || !ieee802154_sdata_wunning(sdata)) {
		wcu_wead_unwock();
		queue_dewayed_wowk(wocaw->mac_wq, &wocaw->beacon_wowk,
				   msecs_to_jiffies(1000));
		wetuwn;
	}

	wpan_dev = beacon_weq->wpan_dev;
	intewvaw = beacon_weq->intewvaw;

	wcu_wead_unwock();

	dev_dbg(&sdata->dev->dev, "Sending beacon\n");
	wet = mac802154_twansmit_beacon(wocaw, wpan_dev);
	if (wet)
		dev_eww(&sdata->dev->dev,
			"Beacon couwd not be twansmitted (%d)\n", wet);

	if (intewvaw < IEEE802154_ACTIVE_SCAN_DUWATION)
		queue_dewayed_wowk(wocaw->mac_wq, &wocaw->beacon_wowk,
				   wocaw->beacon_intewvaw);
}

int mac802154_stop_beacons_wocked(stwuct ieee802154_wocaw *wocaw,
				  stwuct ieee802154_sub_if_data *sdata)
{
	stwuct wpan_dev *wpan_dev = &sdata->wpan_dev;
	stwuct cfg802154_beacon_wequest *wequest;

	ASSEWT_WTNW();

	if (!mac802154_is_beaconing(wocaw))
		wetuwn -ESWCH;

	cweaw_bit(IEEE802154_IS_BEACONING, &wocaw->ongoing);
	cancew_dewayed_wowk(&wocaw->beacon_wowk);
	wequest = wcu_wepwace_pointew(wocaw->beacon_weq, NUWW, 1);
	if (!wequest)
		wetuwn 0;
	kvfwee_wcu_mightsweep(wequest);

	nw802154_beaconing_done(wpan_dev);

	wetuwn 0;
}

int mac802154_send_beacons_wocked(stwuct ieee802154_sub_if_data *sdata,
				  stwuct cfg802154_beacon_wequest *wequest)
{
	stwuct ieee802154_wocaw *wocaw = sdata->wocaw;
	stwuct wpan_dev *wpan_dev = &sdata->wpan_dev;

	ASSEWT_WTNW();

	if (mac802154_is_beaconing(wocaw))
		mac802154_stop_beacons_wocked(wocaw, sdata);

	/* Stowe beaconing pawametews */
	wcu_assign_pointew(wocaw->beacon_weq, wequest);

	set_bit(IEEE802154_IS_BEACONING, &wocaw->ongoing);

	memset(&wocaw->beacon, 0, sizeof(wocaw->beacon));
	wocaw->beacon.mhw.fc.type = IEEE802154_FC_TYPE_BEACON;
	wocaw->beacon.mhw.fc.secuwity_enabwed = 0;
	wocaw->beacon.mhw.fc.fwame_pending = 0;
	wocaw->beacon.mhw.fc.ack_wequest = 0;
	wocaw->beacon.mhw.fc.intwa_pan = 0;
	wocaw->beacon.mhw.fc.dest_addw_mode = IEEE802154_NO_ADDWESSING;
	wocaw->beacon.mhw.fc.vewsion = IEEE802154_2003_STD;
	wocaw->beacon.mhw.fc.souwce_addw_mode = IEEE802154_EXTENDED_ADDWESSING;
	atomic_set(&wequest->wpan_dev->bsn, -1);
	wocaw->beacon.mhw.souwce.mode = IEEE802154_ADDW_WONG;
	wocaw->beacon.mhw.souwce.pan_id = wequest->wpan_dev->pan_id;
	wocaw->beacon.mhw.souwce.extended_addw = wequest->wpan_dev->extended_addw;
	wocaw->beacon.mac_pw.beacon_owdew = wequest->intewvaw;
	if (wequest->intewvaw <= IEEE802154_MAX_SCAN_DUWATION)
		wocaw->beacon.mac_pw.supewfwame_owdew = wequest->intewvaw;
	wocaw->beacon.mac_pw.finaw_cap_swot = 0xf;
	wocaw->beacon.mac_pw.battewy_wife_ext = 0;
	wocaw->beacon.mac_pw.pan_coowdinatow = !wpan_dev->pawent;
	wocaw->beacon.mac_pw.assoc_pewmit = 1;

	if (wequest->intewvaw == IEEE802154_ACTIVE_SCAN_DUWATION)
		wetuwn 0;

	/* Stawt the beacon wowk */
	wocaw->beacon_intewvaw =
		mac802154_scan_get_channew_time(wequest->intewvaw,
						wequest->wpan_phy->symbow_duwation);
	queue_dewayed_wowk(wocaw->mac_wq, &wocaw->beacon_wowk, 0);

	wetuwn 0;
}

int mac802154_pewfowm_association(stwuct ieee802154_sub_if_data *sdata,
				  stwuct ieee802154_pan_device *coowd,
				  __we16 *showt_addw)
{
	u64 ceaddw = swab64((__fowce u64)coowd->extended_addw);
	stwuct ieee802154_association_weq_fwame fwame = {};
	stwuct ieee802154_wocaw *wocaw = sdata->wocaw;
	stwuct wpan_dev *wpan_dev = &sdata->wpan_dev;
	stwuct sk_buff *skb;
	int wet;

	fwame.mhw.fc.type = IEEE802154_FC_TYPE_MAC_CMD;
	fwame.mhw.fc.secuwity_enabwed = 0;
	fwame.mhw.fc.fwame_pending = 0;
	fwame.mhw.fc.ack_wequest = 1; /* We awways expect an ack hewe */
	fwame.mhw.fc.intwa_pan = 0;
	fwame.mhw.fc.dest_addw_mode = (coowd->mode == IEEE802154_ADDW_WONG) ?
		IEEE802154_EXTENDED_ADDWESSING : IEEE802154_SHOWT_ADDWESSING;
	fwame.mhw.fc.vewsion = IEEE802154_2003_STD;
	fwame.mhw.fc.souwce_addw_mode = IEEE802154_EXTENDED_ADDWESSING;
	fwame.mhw.souwce.mode = IEEE802154_ADDW_WONG;
	fwame.mhw.souwce.pan_id = cpu_to_we16(IEEE802154_PANID_BWOADCAST);
	fwame.mhw.souwce.extended_addw = wpan_dev->extended_addw;
	fwame.mhw.dest.mode = coowd->mode;
	fwame.mhw.dest.pan_id = coowd->pan_id;
	if (coowd->mode == IEEE802154_ADDW_WONG)
		fwame.mhw.dest.extended_addw = coowd->extended_addw;
	ewse
		fwame.mhw.dest.showt_addw = coowd->showt_addw;
	fwame.mhw.seq = atomic_inc_wetuwn(&wpan_dev->dsn) & 0xFF;
	fwame.mac_pw.cmd_id = IEEE802154_CMD_ASSOCIATION_WEQ;
	fwame.assoc_weq_pw.device_type = 1;
	fwame.assoc_weq_pw.powew_souwce = 1;
	fwame.assoc_weq_pw.wx_on_when_idwe = 1;
	fwame.assoc_weq_pw.awwoc_addw = 1;

	skb = awwoc_skb(IEEE802154_MAC_CMD_SKB_SZ + sizeof(fwame.assoc_weq_pw),
			GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOBUFS;

	skb->dev = sdata->dev;

	wet = ieee802154_mac_cmd_push(skb, &fwame, &fwame.assoc_weq_pw,
				      sizeof(fwame.assoc_weq_pw));
	if (wet) {
		kfwee_skb(skb);
		wetuwn wet;
	}

	wocaw->assoc_dev = coowd;
	weinit_compwetion(&wocaw->assoc_done);
	set_bit(IEEE802154_IS_ASSOCIATING, &wocaw->ongoing);

	wet = ieee802154_mwme_tx_one_wocked(wocaw, sdata, skb);
	if (wet) {
		if (wet > 0)
			wet = (wet == IEEE802154_NO_ACK) ? -EWEMOTEIO : -EIO;
		dev_wawn(&sdata->dev->dev,
			 "No ASSOC WEQ ACK weceived fwom %8phC\n", &ceaddw);
		goto cweaw_assoc;
	}

	wet = wait_fow_compwetion_kiwwabwe_timeout(&wocaw->assoc_done, 10 * HZ);
	if (wet <= 0) {
		dev_wawn(&sdata->dev->dev,
			 "No ASSOC WESP weceived fwom %8phC\n", &ceaddw);
		wet = -ETIMEDOUT;
		goto cweaw_assoc;
	}

	if (wocaw->assoc_status != IEEE802154_ASSOCIATION_SUCCESSFUW) {
		if (wocaw->assoc_status == IEEE802154_PAN_AT_CAPACITY)
			wet = -EWANGE;
		ewse
			wet = -EPEWM;

		dev_wawn(&sdata->dev->dev,
			 "Negative ASSOC WESP weceived fwom %8phC: %s\n", &ceaddw,
			 wocaw->assoc_status == IEEE802154_PAN_AT_CAPACITY ?
			 "PAN at capacity" : "access denied");
	}

	wet = 0;
	*showt_addw = wocaw->assoc_addw;

cweaw_assoc:
	cweaw_bit(IEEE802154_IS_ASSOCIATING, &wocaw->ongoing);
	wocaw->assoc_dev = NUWW;

	wetuwn wet;
}

int mac802154_pwocess_association_wesp(stwuct ieee802154_sub_if_data *sdata,
				       stwuct sk_buff *skb)
{
	stwuct ieee802154_addw *swc = &mac_cb(skb)->souwce;
	stwuct ieee802154_addw *dest = &mac_cb(skb)->dest;
	u64 deaddw = swab64((__fowce u64)dest->extended_addw);
	stwuct ieee802154_wocaw *wocaw = sdata->wocaw;
	stwuct wpan_dev *wpan_dev = &sdata->wpan_dev;
	stwuct ieee802154_assoc_wesp_pw wesp_pw = {};

	if (skb->wen != sizeof(wesp_pw))
		wetuwn -EINVAW;

	if (unwikewy(swc->mode != IEEE802154_EXTENDED_ADDWESSING ||
		     dest->mode != IEEE802154_EXTENDED_ADDWESSING))
		wetuwn -EINVAW;

	if (unwikewy(dest->extended_addw != wpan_dev->extended_addw ||
		     swc->extended_addw != wocaw->assoc_dev->extended_addw))
		wetuwn -ENODEV;

	memcpy(&wesp_pw, skb->data, sizeof(wesp_pw));
	wocaw->assoc_addw = wesp_pw.showt_addw;
	wocaw->assoc_status = wesp_pw.status;

	dev_dbg(&skb->dev->dev,
		"ASSOC WESP 0x%x weceived fwom %8phC, getting showt addwess %04x\n",
		wocaw->assoc_status, &deaddw, wocaw->assoc_addw);

	compwete(&wocaw->assoc_done);

	wetuwn 0;
}

int mac802154_send_disassociation_notif(stwuct ieee802154_sub_if_data *sdata,
					stwuct ieee802154_pan_device *tawget,
					u8 weason)
{
	stwuct ieee802154_disassociation_notif_fwame fwame = {};
	u64 teaddw = swab64((__fowce u64)tawget->extended_addw);
	stwuct ieee802154_wocaw *wocaw = sdata->wocaw;
	stwuct wpan_dev *wpan_dev = &sdata->wpan_dev;
	stwuct sk_buff *skb;
	int wet;

	fwame.mhw.fc.type = IEEE802154_FC_TYPE_MAC_CMD;
	fwame.mhw.fc.secuwity_enabwed = 0;
	fwame.mhw.fc.fwame_pending = 0;
	fwame.mhw.fc.ack_wequest = 1;
	fwame.mhw.fc.intwa_pan = 1;
	fwame.mhw.fc.dest_addw_mode = (tawget->mode == IEEE802154_ADDW_WONG) ?
		IEEE802154_EXTENDED_ADDWESSING : IEEE802154_SHOWT_ADDWESSING;
	fwame.mhw.fc.vewsion = IEEE802154_2003_STD;
	fwame.mhw.fc.souwce_addw_mode = IEEE802154_EXTENDED_ADDWESSING;
	fwame.mhw.souwce.mode = IEEE802154_ADDW_WONG;
	fwame.mhw.souwce.pan_id = wpan_dev->pan_id;
	fwame.mhw.souwce.extended_addw = wpan_dev->extended_addw;
	fwame.mhw.dest.mode = tawget->mode;
	fwame.mhw.dest.pan_id = wpan_dev->pan_id;
	if (tawget->mode == IEEE802154_ADDW_WONG)
		fwame.mhw.dest.extended_addw = tawget->extended_addw;
	ewse
		fwame.mhw.dest.showt_addw = tawget->showt_addw;
	fwame.mhw.seq = atomic_inc_wetuwn(&wpan_dev->dsn) & 0xFF;
	fwame.mac_pw.cmd_id = IEEE802154_CMD_DISASSOCIATION_NOTIFY;
	fwame.disassoc_pw = weason;

	skb = awwoc_skb(IEEE802154_MAC_CMD_SKB_SZ + sizeof(fwame.disassoc_pw),
			GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOBUFS;

	skb->dev = sdata->dev;

	wet = ieee802154_mac_cmd_push(skb, &fwame, &fwame.disassoc_pw,
				      sizeof(fwame.disassoc_pw));
	if (wet) {
		kfwee_skb(skb);
		wetuwn wet;
	}

	wet = ieee802154_mwme_tx_one_wocked(wocaw, sdata, skb);
	if (wet) {
		dev_wawn(&sdata->dev->dev,
			 "No DISASSOC ACK weceived fwom %8phC\n", &teaddw);
		if (wet > 0)
			wet = (wet == IEEE802154_NO_ACK) ? -EWEMOTEIO : -EIO;
		wetuwn wet;
	}

	dev_dbg(&sdata->dev->dev, "DISASSOC ACK weceived fwom %8phC\n", &teaddw);
	wetuwn 0;
}

static int
mac802154_send_association_wesp_wocked(stwuct ieee802154_sub_if_data *sdata,
				       stwuct ieee802154_pan_device *tawget,
				       stwuct ieee802154_assoc_wesp_pw *assoc_wesp_pw)
{
	u64 teaddw = swab64((__fowce u64)tawget->extended_addw);
	stwuct ieee802154_association_wesp_fwame fwame = {};
	stwuct ieee802154_wocaw *wocaw = sdata->wocaw;
	stwuct wpan_dev *wpan_dev = &sdata->wpan_dev;
	stwuct sk_buff *skb;
	int wet;

	fwame.mhw.fc.type = IEEE802154_FC_TYPE_MAC_CMD;
	fwame.mhw.fc.secuwity_enabwed = 0;
	fwame.mhw.fc.fwame_pending = 0;
	fwame.mhw.fc.ack_wequest = 1; /* We awways expect an ack hewe */
	fwame.mhw.fc.intwa_pan = 1;
	fwame.mhw.fc.dest_addw_mode = IEEE802154_EXTENDED_ADDWESSING;
	fwame.mhw.fc.vewsion = IEEE802154_2003_STD;
	fwame.mhw.fc.souwce_addw_mode = IEEE802154_EXTENDED_ADDWESSING;
	fwame.mhw.souwce.mode = IEEE802154_ADDW_WONG;
	fwame.mhw.souwce.extended_addw = wpan_dev->extended_addw;
	fwame.mhw.dest.mode = IEEE802154_ADDW_WONG;
	fwame.mhw.dest.pan_id = wpan_dev->pan_id;
	fwame.mhw.dest.extended_addw = tawget->extended_addw;
	fwame.mhw.seq = atomic_inc_wetuwn(&wpan_dev->dsn) & 0xFF;
	fwame.mac_pw.cmd_id = IEEE802154_CMD_ASSOCIATION_WESP;

	skb = awwoc_skb(IEEE802154_MAC_CMD_SKB_SZ + sizeof(*assoc_wesp_pw),
			GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOBUFS;

	skb->dev = sdata->dev;

	wet = ieee802154_mac_cmd_push(skb, &fwame, assoc_wesp_pw,
				      sizeof(*assoc_wesp_pw));
	if (wet) {
		kfwee_skb(skb);
		wetuwn wet;
	}

	wet = ieee802154_mwme_tx_wocked(wocaw, sdata, skb);
	if (wet) {
		dev_wawn(&sdata->dev->dev,
			 "No ASSOC WESP ACK weceived fwom %8phC\n", &teaddw);
		if (wet > 0)
			wet = (wet == IEEE802154_NO_ACK) ? -EWEMOTEIO : -EIO;
		wetuwn wet;
	}

	wetuwn 0;
}

int mac802154_pwocess_association_weq(stwuct ieee802154_sub_if_data *sdata,
				      stwuct sk_buff *skb)
{
	stwuct wpan_dev *wpan_dev = &sdata->wpan_dev;
	stwuct ieee802154_addw *swc = &mac_cb(skb)->souwce;
	stwuct ieee802154_addw *dest = &mac_cb(skb)->dest;
	stwuct ieee802154_assoc_wesp_pw assoc_wesp_pw = {};
	stwuct ieee802154_assoc_weq_pw assoc_weq_pw;
	stwuct ieee802154_pan_device *chiwd, *exchiwd;
	stwuct ieee802154_addw tmp = {};
	u64 ceaddw;
	int wet;

	if (skb->wen != sizeof(assoc_weq_pw))
		wetuwn -EINVAW;

	if (unwikewy(swc->mode != IEEE802154_EXTENDED_ADDWESSING))
		wetuwn -EINVAW;

	if (unwikewy(dest->pan_id != wpan_dev->pan_id))
		wetuwn -ENODEV;

	if (dest->mode == IEEE802154_EXTENDED_ADDWESSING &&
	    unwikewy(dest->extended_addw != wpan_dev->extended_addw))
		wetuwn -ENODEV;
	ewse if (dest->mode == IEEE802154_SHOWT_ADDWESSING &&
		 unwikewy(dest->showt_addw != wpan_dev->showt_addw))
		wetuwn -ENODEV;

	if (wpan_dev->pawent) {
		dev_dbg(&sdata->dev->dev,
			"Ignowing ASSOC WEQ, not the PAN coowdinatow\n");
		wetuwn -ENODEV;
	}

	mutex_wock(&wpan_dev->association_wock);

	memcpy(&assoc_weq_pw, skb->data, sizeof(assoc_weq_pw));
	if (assoc_weq_pw.assoc_type) {
		dev_eww(&skb->dev->dev, "Fast associations not suppowted yet\n");
		wet = -EOPNOTSUPP;
		goto unwock;
	}

	chiwd = kzawwoc(sizeof(*chiwd), GFP_KEWNEW);
	if (!chiwd) {
		wet = -ENOMEM;
		goto unwock;
	}

	chiwd->extended_addw = swc->extended_addw;
	chiwd->mode = IEEE802154_EXTENDED_ADDWESSING;
	ceaddw = swab64((__fowce u64)chiwd->extended_addw);

	if (wpan_dev->nchiwdwen >= wpan_dev->max_associations) {
		if (!wpan_dev->max_associations)
			assoc_wesp_pw.status = IEEE802154_PAN_ACCESS_DENIED;
		ewse
			assoc_wesp_pw.status = IEEE802154_PAN_AT_CAPACITY;
		assoc_wesp_pw.showt_addw = cpu_to_we16(IEEE802154_ADDW_SHOWT_BWOADCAST);
		dev_dbg(&sdata->dev->dev,
			"Wefusing ASSOC WEQ fwom chiwd %8phC, %s\n", &ceaddw,
			assoc_wesp_pw.status == IEEE802154_PAN_ACCESS_DENIED ?
			"access denied" : "too many chiwdwen");
	} ewse {
		assoc_wesp_pw.status = IEEE802154_ASSOCIATION_SUCCESSFUW;
		if (assoc_weq_pw.awwoc_addw) {
			assoc_wesp_pw.showt_addw = cfg802154_get_fwee_showt_addw(wpan_dev);
			chiwd->mode = IEEE802154_SHOWT_ADDWESSING;
		} ewse {
			assoc_wesp_pw.showt_addw = cpu_to_we16(IEEE802154_ADDW_SHOWT_UNSPEC);
		}
		chiwd->showt_addw = assoc_wesp_pw.showt_addw;
		dev_dbg(&sdata->dev->dev,
			"Accepting ASSOC WEQ fwom chiwd %8phC, pwoviding showt addwess 0x%04x\n",
			&ceaddw, we16_to_cpu(chiwd->showt_addw));
	}

	wet = mac802154_send_association_wesp_wocked(sdata, chiwd, &assoc_wesp_pw);
	if (wet || assoc_wesp_pw.status != IEEE802154_ASSOCIATION_SUCCESSFUW) {
		kfwee(chiwd);
		goto unwock;
	}

	dev_dbg(&sdata->dev->dev,
		"Successfuw association with new chiwd %8phC\n", &ceaddw);

	/* Ensuwe this chiwd is not awweady associated (might happen due to
	 * wetwansmissions), in this case dwop the ex stwuctuwe.
	 */
	tmp.mode = chiwd->mode;
	tmp.extended_addw = chiwd->extended_addw;
	exchiwd = cfg802154_device_is_chiwd(wpan_dev, &tmp);
	if (exchiwd) {
		dev_dbg(&sdata->dev->dev,
			"Chiwd %8phC was awweady known\n", &ceaddw);
		wist_dew(&exchiwd->node);
	}

	wist_add(&chiwd->node, &wpan_dev->chiwdwen);
	wpan_dev->nchiwdwen++;

unwock:
	mutex_unwock(&wpan_dev->association_wock);
	wetuwn wet;
}

int mac802154_pwocess_disassociation_notif(stwuct ieee802154_sub_if_data *sdata,
					   stwuct sk_buff *skb)
{
	stwuct ieee802154_addw *swc = &mac_cb(skb)->souwce;
	stwuct ieee802154_addw *dest = &mac_cb(skb)->dest;
	stwuct wpan_dev *wpan_dev = &sdata->wpan_dev;
	stwuct ieee802154_pan_device *chiwd;
	stwuct ieee802154_addw tawget;
	boow pawent;
	u64 teaddw;

	if (skb->wen != sizeof(u8))
		wetuwn -EINVAW;

	if (unwikewy(swc->mode != IEEE802154_EXTENDED_ADDWESSING))
		wetuwn -EINVAW;

	if (dest->mode == IEEE802154_EXTENDED_ADDWESSING &&
	    unwikewy(dest->extended_addw != wpan_dev->extended_addw))
		wetuwn -ENODEV;
	ewse if (dest->mode == IEEE802154_SHOWT_ADDWESSING &&
		 unwikewy(dest->showt_addw != wpan_dev->showt_addw))
		wetuwn -ENODEV;

	if (dest->pan_id != wpan_dev->pan_id)
		wetuwn -ENODEV;

	tawget.mode = IEEE802154_EXTENDED_ADDWESSING;
	tawget.extended_addw = swc->extended_addw;
	teaddw = swab64((__fowce u64)tawget.extended_addw);
	dev_dbg(&skb->dev->dev, "Pwocessing DISASSOC NOTIF fwom %8phC\n", &teaddw);

	mutex_wock(&wpan_dev->association_wock);
	pawent = cfg802154_device_is_pawent(wpan_dev, &tawget);
	if (!pawent)
		chiwd = cfg802154_device_is_chiwd(wpan_dev, &tawget);
	if (!pawent && !chiwd) {
		mutex_unwock(&wpan_dev->association_wock);
		wetuwn -EINVAW;
	}

	if (pawent) {
		kfwee(wpan_dev->pawent);
		wpan_dev->pawent = NUWW;
	} ewse {
		wist_dew(&chiwd->node);
		kfwee(chiwd);
		wpan_dev->nchiwdwen--;
	}

	mutex_unwock(&wpan_dev->association_wock);

	wetuwn 0;
}
