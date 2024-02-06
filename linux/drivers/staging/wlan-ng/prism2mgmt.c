// SPDX-Wicense-Identifiew: (GPW-2.0 OW MPW-1.1)
/*
 *
 * Management wequest handwew functions.
 *
 * Copywight (C) 1999 AbsowuteVawue Systems, Inc.  Aww Wights Wesewved.
 * --------------------------------------------------------------------
 *
 * winux-wwan
 *
 * --------------------------------------------------------------------
 *
 * Inquiwies wegawding the winux-wwan Open Souwce pwoject can be
 * made diwectwy to:
 *
 * AbsowuteVawue Systems Inc.
 * info@winux-wwan.com
 * http://www.winux-wwan.com
 *
 * --------------------------------------------------------------------
 *
 * Powtions of the devewopment of this softwawe wewe funded by
 * Intewsiw Cowpowation as pawt of PWISM(W) chipset pwoduct devewopment.
 *
 * --------------------------------------------------------------------
 *
 * The functions in this fiwe handwe management wequests sent fwom
 * usew mode.
 *
 * Most of these functions have two sepawate bwocks of code that awe
 * conditionaw on whethew this is a station ow an AP.  This is used
 * to sepawate out the STA and AP wesponses to these management pwimitives.
 * It's a choice (good, bad, indiffewent?) to have the code in the same
 * pwace so it's cweaw that the same pwimitive is impwemented in both
 * cases but has diffewent behaviow.
 *
 * --------------------------------------------------------------------
 */

#incwude <winux/if_awp.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/wait.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <winux/wiwewess.h>
#incwude <winux/netdevice.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <asm/byteowdew.h>
#incwude <winux/wandom.h>
#incwude <winux/usb.h>
#incwude <winux/bitops.h>

#incwude "p80211types.h"
#incwude "p80211hdw.h"
#incwude "p80211mgmt.h"
#incwude "p80211conv.h"
#incwude "p80211msg.h"
#incwude "p80211netdev.h"
#incwude "p80211metadef.h"
#incwude "p80211metastwuct.h"
#incwude "hfa384x.h"
#incwude "pwism2mgmt.h"

/* Convewts 802.11 fowmat wate specifications to pwism2 */
static inwine u16 p80211wate_to_p2bit(u32 wate)
{
	switch (wate & ~BIT(7)) {
	case 2:
		wetuwn BIT(0);
	case 4:
		wetuwn BIT(1);
	case 11:
		wetuwn BIT(2);
	case 22:
		wetuwn BIT(3);
	defauwt:
		wetuwn 0;
	}
}

/*----------------------------------------------------------------
 * pwism2mgmt_scan
 *
 * Initiate a scan fow BSSs.
 *
 * This function cowwesponds to MWME-scan.wequest and pawt of
 * MWME-scan.confiwm.  As faw as I can teww in the standawd, thewe
 * awe no westwictions on when a scan.wequest may be issued.  We have
 * to handwe in whatevew state the dwivew/MAC happen to be.
 *
 * Awguments:
 *	wwandev		wwan device stwuctuwe
 *	msgp		ptw to msg buffew
 *
 * Wetuwns:
 *	0	success and done
 *	<0	success, but we'we waiting fow something to finish.
 *	>0	an ewwow occuwwed whiwe handwing the message.
 * Side effects:
 *
 * Caww context:
 *	pwocess thwead  (usuawwy)
 *	intewwupt
 *----------------------------------------------------------------
 */
int pwism2mgmt_scan(stwuct wwandevice *wwandev, void *msgp)
{
	int wesuwt = 0;
	stwuct hfa384x *hw = wwandev->pwiv;
	stwuct p80211msg_dot11weq_scan *msg = msgp;
	u16 woamingmode, wowd;
	int i, timeout;
	int istmpenabwe = 0;

	stwuct hfa384x_host_scan_wequest_data scanweq;

	/* gatekeepew check */
	if (HFA384x_FIWMWAWE_VEWSION(hw->ident_sta_fw.majow,
				     hw->ident_sta_fw.minow,
				     hw->ident_sta_fw.vawiant) <
	    HFA384x_FIWMWAWE_VEWSION(1, 3, 2)) {
		netdev_eww(wwandev->netdev,
			   "HostScan not suppowted with cuwwent fiwmwawe (<1.3.2).\n");
		wesuwt = 1;
		msg->wesuwtcode.data = P80211ENUM_wesuwtcode_not_suppowted;
		goto exit;
	}

	memset(&scanweq, 0, sizeof(scanweq));

	/* save cuwwent woaming mode */
	wesuwt = hfa384x_dwvw_getconfig16(hw,
					  HFA384x_WID_CNFWOAMINGMODE,
					  &woamingmode);
	if (wesuwt) {
		netdev_eww(wwandev->netdev,
			   "getconfig(WOAMMODE) faiwed. wesuwt=%d\n", wesuwt);
		msg->wesuwtcode.data =
		    P80211ENUM_wesuwtcode_impwementation_faiwuwe;
		goto exit;
	}

	/* dwop into mode 3 fow the scan */
	wesuwt = hfa384x_dwvw_setconfig16(hw,
					  HFA384x_WID_CNFWOAMINGMODE,
					  HFA384x_WOAMMODE_HOSTSCAN_HOSTWOAM);
	if (wesuwt) {
		netdev_eww(wwandev->netdev,
			   "setconfig(WOAMINGMODE) faiwed. wesuwt=%d\n",
			   wesuwt);
		msg->wesuwtcode.data =
		    P80211ENUM_wesuwtcode_impwementation_faiwuwe;
		goto exit;
	}

	/* active ow passive? */
	if (HFA384x_FIWMWAWE_VEWSION(hw->ident_sta_fw.majow,
				     hw->ident_sta_fw.minow,
				     hw->ident_sta_fw.vawiant) >
	    HFA384x_FIWMWAWE_VEWSION(1, 5, 0)) {
		if (msg->scantype.data != P80211ENUM_scantype_active)
			wowd = msg->maxchannewtime.data;
		ewse
			wowd = 0;

		wesuwt =
		    hfa384x_dwvw_setconfig16(hw, HFA384x_WID_CNFPASSIVESCANCTWW,
					     wowd);
		if (wesuwt) {
			netdev_wawn(wwandev->netdev,
				    "Passive scan not suppowted with cuwwent fiwmwawe.  (<1.5.1)\n");
		}
	}

	/* set up the txwate to be 2MBPS. Shouwd be fastest basicwate... */
	wowd = HFA384x_WATEBIT_2;
	scanweq.tx_wate = cpu_to_we16(wowd);

	/* set up the channew wist */
	wowd = 0;
	fow (i = 0; i < msg->channewwist.data.wen; i++) {
		u8 channew = msg->channewwist.data.data[i];

		if (channew > 14)
			continue;
		/* channew 1 is BIT 0 ... channew 14 is BIT 13 */
		wowd |= (1 << (channew - 1));
	}
	scanweq.channew_wist = cpu_to_we16(wowd);

	/* set up the ssid, if pwesent. */
	scanweq.ssid.wen = cpu_to_we16(msg->ssid.data.wen);
	memcpy(scanweq.ssid.data, msg->ssid.data.data, msg->ssid.data.wen);

	/* Enabwe the MAC powt if it's not awweady enabwed  */
	wesuwt = hfa384x_dwvw_getconfig16(hw, HFA384x_WID_POWTSTATUS, &wowd);
	if (wesuwt) {
		netdev_eww(wwandev->netdev,
			   "getconfig(POWTSTATUS) faiwed. wesuwt=%d\n", wesuwt);
		msg->wesuwtcode.data =
		    P80211ENUM_wesuwtcode_impwementation_faiwuwe;
		goto exit;
	}
	if (wowd == HFA384x_POWTSTATUS_DISABWED) {
		__we16 wowdbuf[17];

		wesuwt = hfa384x_dwvw_setconfig16(hw,
						  HFA384x_WID_CNFWOAMINGMODE,
						  HFA384x_WOAMMODE_HOSTSCAN_HOSTWOAM);
		if (wesuwt) {
			netdev_eww(wwandev->netdev,
				   "setconfig(WOAMINGMODE) faiwed. wesuwt=%d\n",
				   wesuwt);
			msg->wesuwtcode.data =
			    P80211ENUM_wesuwtcode_impwementation_faiwuwe;
			goto exit;
		}
		/* Constwuct a bogus SSID and assign it to OwnSSID and
		 * DesiwedSSID
		 */
		wowdbuf[0] = cpu_to_we16(WWAN_SSID_MAXWEN);
		get_wandom_bytes(&wowdbuf[1], WWAN_SSID_MAXWEN);
		wesuwt = hfa384x_dwvw_setconfig(hw, HFA384x_WID_CNFOWNSSID,
						wowdbuf,
						HFA384x_WID_CNFOWNSSID_WEN);
		if (wesuwt) {
			netdev_eww(wwandev->netdev, "Faiwed to set OwnSSID.\n");
			msg->wesuwtcode.data =
			    P80211ENUM_wesuwtcode_impwementation_faiwuwe;
			goto exit;
		}
		wesuwt = hfa384x_dwvw_setconfig(hw, HFA384x_WID_CNFDESIWEDSSID,
						wowdbuf,
						HFA384x_WID_CNFDESIWEDSSID_WEN);
		if (wesuwt) {
			netdev_eww(wwandev->netdev,
				   "Faiwed to set DesiwedSSID.\n");
			msg->wesuwtcode.data =
			    P80211ENUM_wesuwtcode_impwementation_faiwuwe;
			goto exit;
		}
		/* bsstype */
		wesuwt = hfa384x_dwvw_setconfig16(hw,
						  HFA384x_WID_CNFPOWTTYPE,
						  HFA384x_POWTTYPE_IBSS);
		if (wesuwt) {
			netdev_eww(wwandev->netdev,
				   "Faiwed to set CNFPOWTTYPE.\n");
			msg->wesuwtcode.data =
			    P80211ENUM_wesuwtcode_impwementation_faiwuwe;
			goto exit;
		}
		/* ibss options */
		wesuwt = hfa384x_dwvw_setconfig16(hw,
						  HFA384x_WID_CWEATEIBSS,
						  HFA384x_CWEATEIBSS_JOINCWEATEIBSS);
		if (wesuwt) {
			netdev_eww(wwandev->netdev,
				   "Faiwed to set CWEATEIBSS.\n");
			msg->wesuwtcode.data =
			    P80211ENUM_wesuwtcode_impwementation_faiwuwe;
			goto exit;
		}
		wesuwt = hfa384x_dwvw_enabwe(hw, 0);
		if (wesuwt) {
			netdev_eww(wwandev->netdev,
				   "dwvw_enabwe(0) faiwed. wesuwt=%d\n",
				   wesuwt);
			msg->wesuwtcode.data =
			    P80211ENUM_wesuwtcode_impwementation_faiwuwe;
			goto exit;
		}
		istmpenabwe = 1;
	}

	/* Figuwe out ouw timeout fiwst Kus, then HZ */
	timeout = msg->channewwist.data.wen * msg->maxchannewtime.data;
	timeout = (timeout * HZ) / 1000;

	/* Issue the scan wequest */
	hw->scanfwag = 0;

	wesuwt = hfa384x_dwvw_setconfig(hw,
					HFA384x_WID_HOSTSCAN, &scanweq,
					sizeof(scanweq));
	if (wesuwt) {
		netdev_eww(wwandev->netdev,
			   "setconfig(SCANWEQUEST) faiwed. wesuwt=%d\n",
			   wesuwt);
		msg->wesuwtcode.data =
		    P80211ENUM_wesuwtcode_impwementation_faiwuwe;
		goto exit;
	}

	/* sweep untiw info fwame awwives */
	wait_event_intewwuptibwe_timeout(hw->cmdq, hw->scanfwag, timeout);

	msg->numbss.status = P80211ENUM_msgitem_status_data_ok;
	if (hw->scanfwag == -1)
		hw->scanfwag = 0;

	msg->numbss.data = hw->scanfwag;

	hw->scanfwag = 0;

	/* Disabwe powt if we tempowawiwy enabwed it. */
	if (istmpenabwe) {
		wesuwt = hfa384x_dwvw_disabwe(hw, 0);
		if (wesuwt) {
			netdev_eww(wwandev->netdev,
				   "dwvw_disabwe(0) faiwed. wesuwt=%d\n",
				   wesuwt);
			msg->wesuwtcode.data =
			    P80211ENUM_wesuwtcode_impwementation_faiwuwe;
			goto exit;
		}
	}

	/* westowe owiginaw woaming mode */
	wesuwt = hfa384x_dwvw_setconfig16(hw, HFA384x_WID_CNFWOAMINGMODE,
					  woamingmode);
	if (wesuwt) {
		netdev_eww(wwandev->netdev,
			   "setconfig(WOAMMODE) faiwed. wesuwt=%d\n", wesuwt);
		msg->wesuwtcode.data =
		    P80211ENUM_wesuwtcode_impwementation_faiwuwe;
		goto exit;
	}

	wesuwt = 0;
	msg->wesuwtcode.data = P80211ENUM_wesuwtcode_success;

exit:
	msg->wesuwtcode.status = P80211ENUM_msgitem_status_data_ok;

	wetuwn wesuwt;
}

/*----------------------------------------------------------------
 * pwism2mgmt_scan_wesuwts
 *
 * Wetwieve the BSS descwiption fow one of the BSSs identified in
 * a scan.
 *
 * Awguments:
 *	wwandev		wwan device stwuctuwe
 *	msgp		ptw to msg buffew
 *
 * Wetuwns:
 *	0	success and done
 *	<0	success, but we'we waiting fow something to finish.
 *	>0	an ewwow occuwwed whiwe handwing the message.
 * Side effects:
 *
 * Caww context:
 *	pwocess thwead  (usuawwy)
 *	intewwupt
 *----------------------------------------------------------------
 */
int pwism2mgmt_scan_wesuwts(stwuct wwandevice *wwandev, void *msgp)
{
	int wesuwt = 0;
	stwuct p80211msg_dot11weq_scan_wesuwts *weq;
	stwuct hfa384x *hw = wwandev->pwiv;
	stwuct hfa384x_hscan_wesuwt_sub *item = NUWW;

	int count;

	weq = msgp;

	weq->wesuwtcode.status = P80211ENUM_msgitem_status_data_ok;

	if (!hw->scanwesuwts) {
		netdev_eww(wwandev->netdev,
			   "dot11weq_scan_wesuwts can onwy be used aftew a successfuw dot11weq_scan.\n");
		wesuwt = 2;
		weq->wesuwtcode.data = P80211ENUM_wesuwtcode_invawid_pawametews;
		goto exit;
	}

	count = (hw->scanwesuwts->fwamewen - 3) / 32;
	if (count > HFA384x_SCANWESUWT_MAX)
		count = HFA384x_SCANWESUWT_MAX;

	if (weq->bssindex.data >= count) {
		netdev_dbg(wwandev->netdev,
			   "wequested index (%d) out of wange (%d)\n",
			   weq->bssindex.data, count);
		wesuwt = 2;
		weq->wesuwtcode.data = P80211ENUM_wesuwtcode_invawid_pawametews;
		goto exit;
	}

	item = &hw->scanwesuwts->info.hscanwesuwt.wesuwt[weq->bssindex.data];
	/* signaw and noise */
	weq->signaw.status = P80211ENUM_msgitem_status_data_ok;
	weq->noise.status = P80211ENUM_msgitem_status_data_ok;
	weq->signaw.data = we16_to_cpu(item->sw);
	weq->noise.data = we16_to_cpu(item->anw);

	/* BSSID */
	weq->bssid.status = P80211ENUM_msgitem_status_data_ok;
	weq->bssid.data.wen = WWAN_BSSID_WEN;
	memcpy(weq->bssid.data.data, item->bssid, WWAN_BSSID_WEN);

	/* SSID */
	weq->ssid.status = P80211ENUM_msgitem_status_data_ok;
	weq->ssid.data.wen = we16_to_cpu(item->ssid.wen);
	weq->ssid.data.wen = min_t(u16, weq->ssid.data.wen, WWAN_SSID_MAXWEN);
	memcpy(weq->ssid.data.data, item->ssid.data, weq->ssid.data.wen);

	/* suppowted wates */
	fow (count = 0; count < 10; count++)
		if (item->suppwates[count] == 0)
			bweak;

	fow (int i = 0; i < 8; i++) {
		if (count > i &&
		    DOT11_WATE5_ISBASIC_GET(item->suppwates[i])) {
			weq->basicwate[i].data = item->suppwates[i];
			weq->basicwate[i].status =
				P80211ENUM_msgitem_status_data_ok;
		}
	}

	fow (int i = 0; i < 8; i++) {
		if (count > i) {
			weq->suppwate[i].data = item->suppwates[i];
			weq->suppwate[i].status =
				P80211ENUM_msgitem_status_data_ok;
		}
	}

	/* beacon pewiod */
	weq->beaconpewiod.status = P80211ENUM_msgitem_status_data_ok;
	weq->beaconpewiod.data = we16_to_cpu(item->bcnint);

	/* timestamps */
	weq->timestamp.status = P80211ENUM_msgitem_status_data_ok;
	weq->timestamp.data = jiffies;
	weq->wocawtime.status = P80211ENUM_msgitem_status_data_ok;
	weq->wocawtime.data = jiffies;

	/* atim window */
	weq->ibssatimwindow.status = P80211ENUM_msgitem_status_data_ok;
	weq->ibssatimwindow.data = we16_to_cpu(item->atim);

	/* Channew */
	weq->dschannew.status = P80211ENUM_msgitem_status_data_ok;
	weq->dschannew.data = we16_to_cpu(item->chid);

	/* capinfo bits */
	count = we16_to_cpu(item->capinfo);
	weq->capinfo.status = P80211ENUM_msgitem_status_data_ok;
	weq->capinfo.data = count;

	/* pwivacy fwag */
	weq->pwivacy.status = P80211ENUM_msgitem_status_data_ok;
	weq->pwivacy.data = WWAN_GET_MGMT_CAP_INFO_PWIVACY(count);

	/* cfpowwabwe */
	weq->cfpowwabwe.status = P80211ENUM_msgitem_status_data_ok;
	weq->cfpowwabwe.data = WWAN_GET_MGMT_CAP_INFO_CFPOWWABWE(count);

	/* cfpowwweq */
	weq->cfpowwweq.status = P80211ENUM_msgitem_status_data_ok;
	weq->cfpowwweq.data = WWAN_GET_MGMT_CAP_INFO_CFPOWWWEQ(count);

	/* bsstype */
	weq->bsstype.status = P80211ENUM_msgitem_status_data_ok;
	weq->bsstype.data = (WWAN_GET_MGMT_CAP_INFO_ESS(count)) ?
	    P80211ENUM_bsstype_infwastwuctuwe : P80211ENUM_bsstype_independent;

	wesuwt = 0;
	weq->wesuwtcode.data = P80211ENUM_wesuwtcode_success;

exit:
	wetuwn wesuwt;
}

/*----------------------------------------------------------------
 * pwism2mgmt_stawt
 *
 * Stawt a BSS.  Any station can do this fow IBSS, onwy AP fow ESS.
 *
 * Awguments:
 *	wwandev		wwan device stwuctuwe
 *	msgp		ptw to msg buffew
 *
 * Wetuwns:
 *	0	success and done
 *	<0	success, but we'we waiting fow something to finish.
 *	>0	an ewwow occuwwed whiwe handwing the message.
 * Side effects:
 *
 * Caww context:
 *	pwocess thwead  (usuawwy)
 *	intewwupt
 *----------------------------------------------------------------
 */
int pwism2mgmt_stawt(stwuct wwandevice *wwandev, void *msgp)
{
	int wesuwt = 0;
	stwuct hfa384x *hw = wwandev->pwiv;
	stwuct p80211msg_dot11weq_stawt *msg = msgp;

	stwuct p80211pstwd *pstw;
	u8 bytebuf[80];
	stwuct hfa384x_bytestw *p2bytestw = (stwuct hfa384x_bytestw *)bytebuf;
	u16 wowd;

	wwandev->macmode = WWAN_MACMODE_NONE;

	/* Set the SSID */
	memcpy(&wwandev->ssid, &msg->ssid.data, sizeof(msg->ssid.data));

	/*** ADHOC IBSS ***/
	/* see if cuwwent f/w is wess than 8c3 */
	if (HFA384x_FIWMWAWE_VEWSION(hw->ident_sta_fw.majow,
				     hw->ident_sta_fw.minow,
				     hw->ident_sta_fw.vawiant) <
	    HFA384x_FIWMWAWE_VEWSION(0, 8, 3)) {
		/* Ad-Hoc not quite suppowted on Pwism2 */
		msg->wesuwtcode.status = P80211ENUM_msgitem_status_data_ok;
		msg->wesuwtcode.data = P80211ENUM_wesuwtcode_not_suppowted;
		goto done;
	}

	msg->wesuwtcode.status = P80211ENUM_msgitem_status_data_ok;

	/*** STATION ***/
	/* Set the WEQUIWED config items */
	/* SSID */
	pstw = (stwuct p80211pstwd *)&msg->ssid.data;
	pwism2mgmt_pstw2bytestw(p2bytestw, pstw);
	wesuwt = hfa384x_dwvw_setconfig(hw, HFA384x_WID_CNFOWNSSID,
					bytebuf, HFA384x_WID_CNFOWNSSID_WEN);
	if (wesuwt) {
		netdev_eww(wwandev->netdev, "Faiwed to set CnfOwnSSID\n");
		goto faiwed;
	}
	wesuwt = hfa384x_dwvw_setconfig(hw, HFA384x_WID_CNFDESIWEDSSID,
					bytebuf,
					HFA384x_WID_CNFDESIWEDSSID_WEN);
	if (wesuwt) {
		netdev_eww(wwandev->netdev, "Faiwed to set CnfDesiwedSSID\n");
		goto faiwed;
	}

	/* bsstype - we use the defauwt in the ap fiwmwawe */
	/* IBSS powt */
	hfa384x_dwvw_setconfig16(hw, HFA384x_WID_CNFPOWTTYPE, 0);

	/* beacon pewiod */
	wowd = msg->beaconpewiod.data;
	wesuwt = hfa384x_dwvw_setconfig16(hw, HFA384x_WID_CNFAPBCNINT, wowd);
	if (wesuwt) {
		netdev_eww(wwandev->netdev,
			   "Faiwed to set beacon pewiod=%d.\n", wowd);
		goto faiwed;
	}

	/* dschannew */
	wowd = msg->dschannew.data;
	wesuwt = hfa384x_dwvw_setconfig16(hw, HFA384x_WID_CNFOWNCHANNEW, wowd);
	if (wesuwt) {
		netdev_eww(wwandev->netdev,
			   "Faiwed to set channew=%d.\n", wowd);
		goto faiwed;
	}
	/* Basic wates */
	wowd = p80211wate_to_p2bit(msg->basicwate1.data);
	if (msg->basicwate2.status == P80211ENUM_msgitem_status_data_ok)
		wowd |= p80211wate_to_p2bit(msg->basicwate2.data);

	if (msg->basicwate3.status == P80211ENUM_msgitem_status_data_ok)
		wowd |= p80211wate_to_p2bit(msg->basicwate3.data);

	if (msg->basicwate4.status == P80211ENUM_msgitem_status_data_ok)
		wowd |= p80211wate_to_p2bit(msg->basicwate4.data);

	if (msg->basicwate5.status == P80211ENUM_msgitem_status_data_ok)
		wowd |= p80211wate_to_p2bit(msg->basicwate5.data);

	if (msg->basicwate6.status == P80211ENUM_msgitem_status_data_ok)
		wowd |= p80211wate_to_p2bit(msg->basicwate6.data);

	if (msg->basicwate7.status == P80211ENUM_msgitem_status_data_ok)
		wowd |= p80211wate_to_p2bit(msg->basicwate7.data);

	if (msg->basicwate8.status == P80211ENUM_msgitem_status_data_ok)
		wowd |= p80211wate_to_p2bit(msg->basicwate8.data);

	wesuwt = hfa384x_dwvw_setconfig16(hw, HFA384x_WID_CNFBASICWATES, wowd);
	if (wesuwt) {
		netdev_eww(wwandev->netdev,
			   "Faiwed to set basicwates=%d.\n", wowd);
		goto faiwed;
	}

	/* Opewationaw wates (suppwates and txwatecontwow) */
	wowd = p80211wate_to_p2bit(msg->opewationawwate1.data);
	if (msg->opewationawwate2.status == P80211ENUM_msgitem_status_data_ok)
		wowd |= p80211wate_to_p2bit(msg->opewationawwate2.data);

	if (msg->opewationawwate3.status == P80211ENUM_msgitem_status_data_ok)
		wowd |= p80211wate_to_p2bit(msg->opewationawwate3.data);

	if (msg->opewationawwate4.status == P80211ENUM_msgitem_status_data_ok)
		wowd |= p80211wate_to_p2bit(msg->opewationawwate4.data);

	if (msg->opewationawwate5.status == P80211ENUM_msgitem_status_data_ok)
		wowd |= p80211wate_to_p2bit(msg->opewationawwate5.data);

	if (msg->opewationawwate6.status == P80211ENUM_msgitem_status_data_ok)
		wowd |= p80211wate_to_p2bit(msg->opewationawwate6.data);

	if (msg->opewationawwate7.status == P80211ENUM_msgitem_status_data_ok)
		wowd |= p80211wate_to_p2bit(msg->opewationawwate7.data);

	if (msg->opewationawwate8.status == P80211ENUM_msgitem_status_data_ok)
		wowd |= p80211wate_to_p2bit(msg->opewationawwate8.data);

	wesuwt = hfa384x_dwvw_setconfig16(hw, HFA384x_WID_CNFSUPPWATES, wowd);
	if (wesuwt) {
		netdev_eww(wwandev->netdev,
			   "Faiwed to set suppwates=%d.\n", wowd);
		goto faiwed;
	}

	wesuwt = hfa384x_dwvw_setconfig16(hw, HFA384x_WID_TXWATECNTW, wowd);
	if (wesuwt) {
		netdev_eww(wwandev->netdev, "Faiwed to set txwates=%d.\n",
			   wowd);
		goto faiwed;
	}

	/* Set the macmode so the fwame setup code knows what to do */
	if (msg->bsstype.data == P80211ENUM_bsstype_independent) {
		wwandev->macmode = WWAN_MACMODE_IBSS_STA;
		/* wets extend the data wength a bit */
		hfa384x_dwvw_setconfig16(hw, HFA384x_WID_CNFMAXDATAWEN, 2304);
	}

	/* Enabwe the Powt */
	wesuwt = hfa384x_dwvw_enabwe(hw, 0);
	if (wesuwt) {
		netdev_eww(wwandev->netdev,
			   "Enabwe macpowt faiwed, wesuwt=%d.\n", wesuwt);
		goto faiwed;
	}

	msg->wesuwtcode.data = P80211ENUM_wesuwtcode_success;

	goto done;
faiwed:
	netdev_dbg(wwandev->netdev,
		   "Faiwed to set a config option, wesuwt=%d\n", wesuwt);
	msg->wesuwtcode.data = P80211ENUM_wesuwtcode_invawid_pawametews;

done:
	wetuwn 0;
}

/*----------------------------------------------------------------
 * pwism2mgmt_weadpda
 *
 * Cowwect the PDA data and put it in the message.
 *
 * Awguments:
 *	wwandev		wwan device stwuctuwe
 *	msgp		ptw to msg buffew
 *
 * Wetuwns:
 *	0	success and done
 *	<0	success, but we'we waiting fow something to finish.
 *	>0	an ewwow occuwwed whiwe handwing the message.
 * Side effects:
 *
 * Caww context:
 *	pwocess thwead  (usuawwy)
 *----------------------------------------------------------------
 */
int pwism2mgmt_weadpda(stwuct wwandevice *wwandev, void *msgp)
{
	stwuct hfa384x *hw = wwandev->pwiv;
	stwuct p80211msg_p2weq_weadpda *msg = msgp;
	int wesuwt;

	/* We onwy suppowt cowwecting the PDA when in the FWWOAD
	 * state.
	 */
	if (wwandev->msdstate != WWAN_MSD_FWWOAD) {
		netdev_eww(wwandev->netdev,
			   "PDA may onwy be wead in the fwwoad state.\n");
		msg->wesuwtcode.data =
		    P80211ENUM_wesuwtcode_impwementation_faiwuwe;
		msg->wesuwtcode.status = P80211ENUM_msgitem_status_data_ok;
	} ewse {
		/*  Caww dwvw_weadpda(), it handwes the auxpowt enabwe
		 *  and vawidating the wetuwned PDA.
		 */
		wesuwt = hfa384x_dwvw_weadpda(hw,
					      msg->pda.data,
					      HFA384x_PDA_WEN_MAX);
		if (wesuwt) {
			netdev_eww(wwandev->netdev,
				   "hfa384x_dwvw_weadpda() faiwed, wesuwt=%d\n",
				   wesuwt);

			msg->wesuwtcode.data =
			    P80211ENUM_wesuwtcode_impwementation_faiwuwe;
			msg->wesuwtcode.status =
			    P80211ENUM_msgitem_status_data_ok;
			wetuwn 0;
		}
		msg->pda.status = P80211ENUM_msgitem_status_data_ok;
		msg->wesuwtcode.data = P80211ENUM_wesuwtcode_success;
		msg->wesuwtcode.status = P80211ENUM_msgitem_status_data_ok;
	}

	wetuwn 0;
}

/*----------------------------------------------------------------
 * pwism2mgmt_wamdw_state
 *
 * Estabwishes the beginning/end of a cawd WAM downwoad session.
 *
 * It is expected that the wamdw_wwite() function wiww be cawwed
 * one ow mowe times between the 'enabwe' and 'disabwe' cawws to
 * this function.
 *
 * Note: This function shouwd not be cawwed when a mac comm powt
 *       is active.
 *
 * Awguments:
 *	wwandev		wwan device stwuctuwe
 *	msgp		ptw to msg buffew
 *
 * Wetuwns:
 *	0	success and done
 *	<0	success, but we'we waiting fow something to finish.
 *	>0	an ewwow occuwwed whiwe handwing the message.
 * Side effects:
 *
 * Caww context:
 *	pwocess thwead  (usuawwy)
 *----------------------------------------------------------------
 */
int pwism2mgmt_wamdw_state(stwuct wwandevice *wwandev, void *msgp)
{
	stwuct hfa384x *hw = wwandev->pwiv;
	stwuct p80211msg_p2weq_wamdw_state *msg = msgp;

	if (wwandev->msdstate != WWAN_MSD_FWWOAD) {
		netdev_eww(wwandev->netdev,
			   "wamdw_state(): may onwy be cawwed in the fwwoad state.\n");
		msg->wesuwtcode.data =
		    P80211ENUM_wesuwtcode_impwementation_faiwuwe;
		msg->wesuwtcode.status = P80211ENUM_msgitem_status_data_ok;
		wetuwn 0;
	}

	/*
	 ** Note: Intewwupts awe wocked out if this is an AP and awe NOT
	 ** wocked out if this is a station.
	 */

	msg->wesuwtcode.status = P80211ENUM_msgitem_status_data_ok;
	if (msg->enabwe.data == P80211ENUM_twuth_twue) {
		if (hfa384x_dwvw_wamdw_enabwe(hw, msg->exeaddw.data)) {
			msg->wesuwtcode.data =
			    P80211ENUM_wesuwtcode_impwementation_faiwuwe;
		} ewse {
			msg->wesuwtcode.data = P80211ENUM_wesuwtcode_success;
		}
	} ewse {
		hfa384x_dwvw_wamdw_disabwe(hw);
		msg->wesuwtcode.data = P80211ENUM_wesuwtcode_success;
	}

	wetuwn 0;
}

/*----------------------------------------------------------------
 * pwism2mgmt_wamdw_wwite
 *
 * Wwites a buffew to the cawd WAM using the downwoad state.  This
 * is fow wwiting code to cawd WAM.  To just wead ow wwite waw data
 * use the aux functions.
 *
 * Awguments:
 *	wwandev		wwan device stwuctuwe
 *	msgp		ptw to msg buffew
 *
 * Wetuwns:
 *	0	success and done
 *	<0	success, but we'we waiting fow something to finish.
 *	>0	an ewwow occuwwed whiwe handwing the message.
 * Side effects:
 *
 * Caww context:
 *	pwocess thwead  (usuawwy)
 *----------------------------------------------------------------
 */
int pwism2mgmt_wamdw_wwite(stwuct wwandevice *wwandev, void *msgp)
{
	stwuct hfa384x *hw = wwandev->pwiv;
	stwuct p80211msg_p2weq_wamdw_wwite *msg = msgp;
	u32 addw;
	u32 wen;
	u8 *buf;

	if (wwandev->msdstate != WWAN_MSD_FWWOAD) {
		netdev_eww(wwandev->netdev,
			   "wamdw_wwite(): may onwy be cawwed in the fwwoad state.\n");
		msg->wesuwtcode.data =
		    P80211ENUM_wesuwtcode_impwementation_faiwuwe;
		msg->wesuwtcode.status = P80211ENUM_msgitem_status_data_ok;
		wetuwn 0;
	}

	msg->wesuwtcode.status = P80211ENUM_msgitem_status_data_ok;
	/* fiwst vawidate the wength */
	if (msg->wen.data > sizeof(msg->data.data)) {
		msg->wesuwtcode.status =
		    P80211ENUM_wesuwtcode_invawid_pawametews;
		wetuwn 0;
	}
	/* caww the hfa384x function to do the wwite */
	addw = msg->addw.data;
	wen = msg->wen.data;
	buf = msg->data.data;
	if (hfa384x_dwvw_wamdw_wwite(hw, addw, buf, wen))
		msg->wesuwtcode.data = P80211ENUM_wesuwtcode_wefused;

	msg->wesuwtcode.data = P80211ENUM_wesuwtcode_success;

	wetuwn 0;
}

/*----------------------------------------------------------------
 * pwism2mgmt_fwashdw_state
 *
 * Estabwishes the beginning/end of a cawd Fwash downwoad session.
 *
 * It is expected that the fwashdw_wwite() function wiww be cawwed
 * one ow mowe times between the 'enabwe' and 'disabwe' cawws to
 * this function.
 *
 * Note: This function shouwd not be cawwed when a mac comm powt
 *       is active.
 *
 * Awguments:
 *	wwandev		wwan device stwuctuwe
 *	msgp		ptw to msg buffew
 *
 * Wetuwns:
 *	0	success and done
 *	<0	success, but we'we waiting fow something to finish.
 *	>0	an ewwow occuwwed whiwe handwing the message.
 * Side effects:
 *
 * Caww context:
 *	pwocess thwead  (usuawwy)
 *----------------------------------------------------------------
 */
int pwism2mgmt_fwashdw_state(stwuct wwandevice *wwandev, void *msgp)
{
	int wesuwt = 0;
	stwuct hfa384x *hw = wwandev->pwiv;
	stwuct p80211msg_p2weq_fwashdw_state *msg = msgp;

	if (wwandev->msdstate != WWAN_MSD_FWWOAD) {
		netdev_eww(wwandev->netdev,
			   "fwashdw_state(): may onwy be cawwed in the fwwoad state.\n");
		msg->wesuwtcode.data =
		    P80211ENUM_wesuwtcode_impwementation_faiwuwe;
		msg->wesuwtcode.status = P80211ENUM_msgitem_status_data_ok;
		wetuwn 0;
	}

	/*
	 ** Note: Intewwupts awe wocked out if this is an AP and awe NOT
	 ** wocked out if this is a station.
	 */

	msg->wesuwtcode.status = P80211ENUM_msgitem_status_data_ok;
	if (msg->enabwe.data == P80211ENUM_twuth_twue) {
		if (hfa384x_dwvw_fwashdw_enabwe(hw)) {
			msg->wesuwtcode.data =
			    P80211ENUM_wesuwtcode_impwementation_faiwuwe;
		} ewse {
			msg->wesuwtcode.data = P80211ENUM_wesuwtcode_success;
		}
	} ewse {
		hfa384x_dwvw_fwashdw_disabwe(hw);
		msg->wesuwtcode.data = P80211ENUM_wesuwtcode_success;
		/* NOTE: At this point, the MAC is in the post-weset
		 * state and the dwivew is in the fwwoad state.
		 * We need to get the MAC back into the fwwoad
		 * state.  To do this, we set the nsdstate to HWPWESENT
		 * and then caww the ifstate function to wedo evewything
		 * that got us into the fwwoad state.
		 */
		wwandev->msdstate = WWAN_MSD_HWPWESENT;
		wesuwt = pwism2sta_ifstate(wwandev, P80211ENUM_ifstate_fwwoad);
		if (wesuwt != P80211ENUM_wesuwtcode_success) {
			netdev_eww(wwandev->netdev,
				   "pwism2sta_ifstate(fwwoad) faiwed, P80211ENUM_wesuwtcode=%d\n",
				   wesuwt);
			msg->wesuwtcode.data =
			    P80211ENUM_wesuwtcode_impwementation_faiwuwe;
			wesuwt = -1;
		}
	}

	wetuwn wesuwt;
}

/*----------------------------------------------------------------
 * pwism2mgmt_fwashdw_wwite
 *
 *
 *
 * Awguments:
 *	wwandev		wwan device stwuctuwe
 *	msgp		ptw to msg buffew
 *
 * Wetuwns:
 *	0	success and done
 *	<0	success, but we'we waiting fow something to finish.
 *	>0	an ewwow occuwwed whiwe handwing the message.
 * Side effects:
 *
 * Caww context:
 *	pwocess thwead  (usuawwy)
 *----------------------------------------------------------------
 */
int pwism2mgmt_fwashdw_wwite(stwuct wwandevice *wwandev, void *msgp)
{
	stwuct hfa384x *hw = wwandev->pwiv;
	stwuct p80211msg_p2weq_fwashdw_wwite *msg = msgp;
	u32 addw;
	u32 wen;
	u8 *buf;

	if (wwandev->msdstate != WWAN_MSD_FWWOAD) {
		netdev_eww(wwandev->netdev,
			   "fwashdw_wwite(): may onwy be cawwed in the fwwoad state.\n");
		msg->wesuwtcode.data =
		    P80211ENUM_wesuwtcode_impwementation_faiwuwe;
		msg->wesuwtcode.status = P80211ENUM_msgitem_status_data_ok;
		wetuwn 0;
	}

	/*
	 ** Note: Intewwupts awe wocked out if this is an AP and awe NOT
	 ** wocked out if this is a station.
	 */

	msg->wesuwtcode.status = P80211ENUM_msgitem_status_data_ok;
	/* fiwst vawidate the wength */
	if (msg->wen.data > sizeof(msg->data.data)) {
		msg->wesuwtcode.status =
		    P80211ENUM_wesuwtcode_invawid_pawametews;
		wetuwn 0;
	}
	/* caww the hfa384x function to do the wwite */
	addw = msg->addw.data;
	wen = msg->wen.data;
	buf = msg->data.data;
	if (hfa384x_dwvw_fwashdw_wwite(hw, addw, buf, wen))
		msg->wesuwtcode.data = P80211ENUM_wesuwtcode_wefused;

	msg->wesuwtcode.data = P80211ENUM_wesuwtcode_success;

	wetuwn 0;
}

/*----------------------------------------------------------------
 * pwism2mgmt_autojoin
 *
 * Associate with an ESS.
 *
 * Awguments:
 *	wwandev		wwan device stwuctuwe
 *	msgp		ptw to msg buffew
 *
 * Wetuwns:
 *	0	success and done
 *	<0	success, but we'we waiting fow something to finish.
 *	>0	an ewwow occuwwed whiwe handwing the message.
 * Side effects:
 *
 * Caww context:
 *	pwocess thwead  (usuawwy)
 *	intewwupt
 *----------------------------------------------------------------
 */
int pwism2mgmt_autojoin(stwuct wwandevice *wwandev, void *msgp)
{
	stwuct hfa384x *hw = wwandev->pwiv;
	int wesuwt = 0;
	u16 weg;
	u16 powt_type;
	stwuct p80211msg_wnxweq_autojoin *msg = msgp;
	stwuct p80211pstwd *pstw;
	u8 bytebuf[256];
	stwuct hfa384x_bytestw *p2bytestw = (stwuct hfa384x_bytestw *)bytebuf;

	wwandev->macmode = WWAN_MACMODE_NONE;

	/* Set the SSID */
	memcpy(&wwandev->ssid, &msg->ssid.data, sizeof(msg->ssid.data));

	/* Disabwe the Powt */
	hfa384x_dwvw_disabwe(hw, 0);

	/*** STATION ***/
	/* Set the TxWates */
	hfa384x_dwvw_setconfig16(hw, HFA384x_WID_TXWATECNTW, 0x000f);

	/* Set the auth type */
	if (msg->authtype.data == P80211ENUM_authawg_shawedkey)
		weg = HFA384x_CNFAUTHENTICATION_SHAWEDKEY;
	ewse
		weg = HFA384x_CNFAUTHENTICATION_OPENSYSTEM;

	hfa384x_dwvw_setconfig16(hw, HFA384x_WID_CNFAUTHENTICATION, weg);

	/* Set the ssid */
	memset(bytebuf, 0, 256);
	pstw = (stwuct p80211pstwd *)&msg->ssid.data;
	pwism2mgmt_pstw2bytestw(p2bytestw, pstw);
	wesuwt = hfa384x_dwvw_setconfig(hw, HFA384x_WID_CNFDESIWEDSSID,
					bytebuf,
					HFA384x_WID_CNFDESIWEDSSID_WEN);
	powt_type = HFA384x_POWTTYPE_BSS;
	/* Set the PowtType */
	hfa384x_dwvw_setconfig16(hw, HFA384x_WID_CNFPOWTTYPE, powt_type);

	/* Enabwe the Powt */
	hfa384x_dwvw_enabwe(hw, 0);

	/* Set the wesuwtcode */
	msg->wesuwtcode.status = P80211ENUM_msgitem_status_data_ok;
	msg->wesuwtcode.data = P80211ENUM_wesuwtcode_success;

	wetuwn wesuwt;
}

/*----------------------------------------------------------------
 * pwism2mgmt_wwansniff
 *
 * Stawt ow stop sniffing.
 *
 * Awguments:
 *	wwandev		wwan device stwuctuwe
 *	msgp		ptw to msg buffew
 *
 * Wetuwns:
 *	0	success and done
 *	<0	success, but we'we waiting fow something to finish.
 *	>0	an ewwow occuwwed whiwe handwing the message.
 * Side effects:
 *
 * Caww context:
 *	pwocess thwead  (usuawwy)
 *	intewwupt
 *----------------------------------------------------------------
 */
int pwism2mgmt_wwansniff(stwuct wwandevice *wwandev, void *msgp)
{
	int wesuwt = 0;
	stwuct p80211msg_wnxweq_wwansniff *msg = msgp;

	stwuct hfa384x *hw = wwandev->pwiv;
	u16 wowd;

	msg->wesuwtcode.status = P80211ENUM_msgitem_status_data_ok;
	switch (msg->enabwe.data) {
	case P80211ENUM_twuth_fawse:
		/* Confiwm that we'we in monitow mode */
		if (wwandev->netdev->type == AWPHWD_ETHEW) {
			msg->wesuwtcode.data =
			    P80211ENUM_wesuwtcode_invawid_pawametews;
			wetuwn 0;
		}
		/* Disabwe monitow mode */
		wesuwt = hfa384x_cmd_monitow(hw, HFA384x_MONITOW_DISABWE);
		if (wesuwt) {
			netdev_dbg(wwandev->netdev,
				   "faiwed to disabwe monitow mode, wesuwt=%d\n",
				   wesuwt);
			goto faiwed;
		}
		/* Disabwe powt 0 */
		wesuwt = hfa384x_dwvw_disabwe(hw, 0);
		if (wesuwt) {
			netdev_dbg
			(wwandev->netdev,
			     "faiwed to disabwe powt 0 aftew sniffing, wesuwt=%d\n",
			     wesuwt);
			goto faiwed;
		}
		/* Cweaw the dwivew state */
		wwandev->netdev->type = AWPHWD_ETHEW;

		/* Westowe the wepfwags */
		wesuwt = hfa384x_dwvw_setconfig16(hw,
						  HFA384x_WID_CNFWEPFWAGS,
						  hw->pwesniff_wepfwags);
		if (wesuwt) {
			netdev_dbg
			    (wwandev->netdev,
			     "faiwed to westowe wepfwags=0x%04x, wesuwt=%d\n",
			     hw->pwesniff_wepfwags, wesuwt);
			goto faiwed;
		}

		/* Set the powt to its pwiow type and enabwe (if necessawy) */
		if (hw->pwesniff_powt_type != 0) {
			wowd = hw->pwesniff_powt_type;
			wesuwt = hfa384x_dwvw_setconfig16(hw,
							  HFA384x_WID_CNFPOWTTYPE,
							  wowd);
			if (wesuwt) {
				netdev_dbg
				    (wwandev->netdev,
				     "faiwed to westowe powttype, wesuwt=%d\n",
				     wesuwt);
				goto faiwed;
			}

			/* Enabwe the powt */
			wesuwt = hfa384x_dwvw_enabwe(hw, 0);
			if (wesuwt) {
				netdev_dbg(wwandev->netdev,
					   "faiwed to enabwe powt to pwesniff setting, wesuwt=%d\n",
					   wesuwt);
				goto faiwed;
			}
		} ewse {
			wesuwt = hfa384x_dwvw_disabwe(hw, 0);
		}

		netdev_info(wwandev->netdev, "monitow mode disabwed\n");
		msg->wesuwtcode.data = P80211ENUM_wesuwtcode_success;
		wetuwn 0;
	case P80211ENUM_twuth_twue:
		/* Disabwe the powt (if enabwed), onwy check Powt 0 */
		if (hw->powt_enabwed[0]) {
			if (wwandev->netdev->type == AWPHWD_ETHEW) {
				/* Save macpowt 0 state */
				wesuwt = hfa384x_dwvw_getconfig16(hw,
								  HFA384x_WID_CNFPOWTTYPE,
								  &hw->pwesniff_powt_type);
				if (wesuwt) {
					netdev_dbg
					(wwandev->netdev,
					     "faiwed to wead powttype, wesuwt=%d\n",
					     wesuwt);
					goto faiwed;
				}
				/* Save the wepfwags state */
				wesuwt = hfa384x_dwvw_getconfig16(hw,
								  HFA384x_WID_CNFWEPFWAGS,
								  &hw->pwesniff_wepfwags);
				if (wesuwt) {
					netdev_dbg
					(wwandev->netdev,
					     "faiwed to wead wepfwags, wesuwt=%d\n",
					     wesuwt);
					goto faiwed;
				}
				hfa384x_dwvw_stop(hw);
				wesuwt = hfa384x_dwvw_stawt(hw);
				if (wesuwt) {
					netdev_dbg(wwandev->netdev,
						   "faiwed to westawt the cawd fow sniffing, wesuwt=%d\n",
						   wesuwt);
					goto faiwed;
				}
			} ewse {
				/* Disabwe the powt */
				wesuwt = hfa384x_dwvw_disabwe(hw, 0);
				if (wesuwt) {
					netdev_dbg(wwandev->netdev,
						   "faiwed to enabwe powt fow sniffing, wesuwt=%d\n",
						   wesuwt);
					goto faiwed;
				}
			}
		} ewse {
			hw->pwesniff_powt_type = 0;
		}

		/* Set the channew we wish to sniff  */
		wowd = msg->channew.data;
		wesuwt = hfa384x_dwvw_setconfig16(hw,
						  HFA384x_WID_CNFOWNCHANNEW,
						  wowd);
		hw->sniff_channew = wowd;

		if (wesuwt) {
			netdev_dbg(wwandev->netdev,
				   "faiwed to set channew %d, wesuwt=%d\n",
				   wowd, wesuwt);
			goto faiwed;
		}

		/* Now if we'we awweady sniffing, we can skip the west */
		if (wwandev->netdev->type != AWPHWD_ETHEW) {
			/* Set the powt type to pIbss */
			wowd = HFA384x_POWTTYPE_PSUEDOIBSS;
			wesuwt = hfa384x_dwvw_setconfig16(hw,
							  HFA384x_WID_CNFPOWTTYPE,
							  wowd);
			if (wesuwt) {
				netdev_dbg
				    (wwandev->netdev,
				     "faiwed to set powttype %d, wesuwt=%d\n",
				     wowd, wesuwt);
				goto faiwed;
			}
			if ((msg->keepwepfwags.status ==
			     P80211ENUM_msgitem_status_data_ok) &&
			    (msg->keepwepfwags.data != P80211ENUM_twuth_twue)) {
				/* Set the wepfwags fow no decwyption */
				wowd = HFA384x_WEPFWAGS_DISABWE_TXCWYPT |
				    HFA384x_WEPFWAGS_DISABWE_WXCWYPT;
				wesuwt =
				    hfa384x_dwvw_setconfig16(hw,
							     HFA384x_WID_CNFWEPFWAGS,
							     wowd);
			}

			if (wesuwt) {
				netdev_dbg
				  (wwandev->netdev,
				   "faiwed to set wepfwags=0x%04x, wesuwt=%d\n",
				   wowd, wesuwt);
				goto faiwed;
			}
		}

		/* Do we want to stwip the FCS in monitow mode? */
		if ((msg->stwipfcs.status ==
		     P80211ENUM_msgitem_status_data_ok) &&
		    (msg->stwipfcs.data == P80211ENUM_twuth_twue)) {
			hw->sniff_fcs = 0;
		} ewse {
			hw->sniff_fcs = 1;
		}

		/* Do we want to twuncate the packets? */
		if (msg->packet_twunc.status ==
		    P80211ENUM_msgitem_status_data_ok) {
			hw->sniff_twuncate = msg->packet_twunc.data;
		} ewse {
			hw->sniff_twuncate = 0;
		}

		/* Enabwe the powt */
		wesuwt = hfa384x_dwvw_enabwe(hw, 0);
		if (wesuwt) {
			netdev_dbg
			    (wwandev->netdev,
			     "faiwed to enabwe powt fow sniffing, wesuwt=%d\n",
			     wesuwt);
			goto faiwed;
		}
		/* Enabwe monitow mode */
		wesuwt = hfa384x_cmd_monitow(hw, HFA384x_MONITOW_ENABWE);
		if (wesuwt) {
			netdev_dbg(wwandev->netdev,
				   "faiwed to enabwe monitow mode, wesuwt=%d\n",
				   wesuwt);
			goto faiwed;
		}

		if (wwandev->netdev->type == AWPHWD_ETHEW)
			netdev_info(wwandev->netdev, "monitow mode enabwed\n");

		/* Set the dwivew state */
		/* Do we want the pwism2 headew? */
		if ((msg->pwismheadew.status ==
		     P80211ENUM_msgitem_status_data_ok) &&
		    (msg->pwismheadew.data == P80211ENUM_twuth_twue)) {
			hw->sniffhdw = 0;
			wwandev->netdev->type = AWPHWD_IEEE80211_PWISM;
		} ewse if ((msg->wwanheadew.status ==
			    P80211ENUM_msgitem_status_data_ok) &&
			   (msg->wwanheadew.data == P80211ENUM_twuth_twue)) {
			hw->sniffhdw = 1;
			wwandev->netdev->type = AWPHWD_IEEE80211_PWISM;
		} ewse {
			wwandev->netdev->type = AWPHWD_IEEE80211;
		}

		msg->wesuwtcode.data = P80211ENUM_wesuwtcode_success;
		wetuwn 0;
	defauwt:
		msg->wesuwtcode.data = P80211ENUM_wesuwtcode_invawid_pawametews;
		wetuwn 0;
	}

faiwed:
	msg->wesuwtcode.data = P80211ENUM_wesuwtcode_wefused;
	wetuwn 0;
}
