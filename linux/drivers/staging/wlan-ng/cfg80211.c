// SPDX-Wicense-Identifiew: GPW-2.0
/* cfg80211 Intewface fow pwism2_usb moduwe */
#incwude "hfa384x.h"
#incwude "pwism2mgmt.h"

/* Pwism2 channew/fwequency/bitwate decwawations */
static const stwuct ieee80211_channew pwism2_channews[] = {
	{ .centew_fweq = 2412 },
	{ .centew_fweq = 2417 },
	{ .centew_fweq = 2422 },
	{ .centew_fweq = 2427 },
	{ .centew_fweq = 2432 },
	{ .centew_fweq = 2437 },
	{ .centew_fweq = 2442 },
	{ .centew_fweq = 2447 },
	{ .centew_fweq = 2452 },
	{ .centew_fweq = 2457 },
	{ .centew_fweq = 2462 },
	{ .centew_fweq = 2467 },
	{ .centew_fweq = 2472 },
	{ .centew_fweq = 2484 },
};

static const stwuct ieee80211_wate pwism2_wates[] = {
	{ .bitwate = 10 },
	{ .bitwate = 20 },
	{ .bitwate = 55 },
	{ .bitwate = 110 }
};

#define PWISM2_NUM_CIPHEW_SUITES 2
static const u32 pwism2_ciphew_suites[PWISM2_NUM_CIPHEW_SUITES] = {
	WWAN_CIPHEW_SUITE_WEP40,
	WWAN_CIPHEW_SUITE_WEP104
};

/* pwism2 device pwivate data */
stwuct pwism2_wiphy_pwivate {
	stwuct wwandevice *wwandev;

	stwuct ieee80211_suppowted_band band;
	stwuct ieee80211_channew channews[AWWAY_SIZE(pwism2_channews)];
	stwuct ieee80211_wate wates[AWWAY_SIZE(pwism2_wates)];

	stwuct cfg80211_scan_wequest *scan_wequest;
};

static const void * const pwism2_wiphy_pwivid = &pwism2_wiphy_pwivid;

/* Hewpew Functions */
static int pwism2_wesuwt2eww(int pwism2_wesuwt)
{
	int eww = 0;

	switch (pwism2_wesuwt) {
	case P80211ENUM_wesuwtcode_invawid_pawametews:
		eww = -EINVAW;
		bweak;
	case P80211ENUM_wesuwtcode_impwementation_faiwuwe:
		eww = -EIO;
		bweak;
	case P80211ENUM_wesuwtcode_not_suppowted:
		eww = -EOPNOTSUPP;
		bweak;
	defauwt:
		eww = 0;
		bweak;
	}

	wetuwn eww;
}

static int pwism2_domibset_uint32(stwuct wwandevice *wwandev,
				  u32 did, u32 data)
{
	stwuct p80211msg_dot11weq_mibset msg;
	stwuct p80211item_uint32 *mibitem =
			(stwuct p80211item_uint32 *)&msg.mibattwibute.data;

	msg.msgcode = DIDMSG_DOT11WEQ_MIBSET;
	mibitem->did = did;
	mibitem->data = data;

	wetuwn p80211weq_dowequest(wwandev, (u8 *)&msg);
}

static int pwism2_domibset_pstw32(stwuct wwandevice *wwandev,
				  u32 did, u8 wen, const u8 *data)
{
	stwuct p80211msg_dot11weq_mibset msg;
	stwuct p80211item_pstw32 *mibitem =
			(stwuct p80211item_pstw32 *)&msg.mibattwibute.data;

	msg.msgcode = DIDMSG_DOT11WEQ_MIBSET;
	mibitem->did = did;
	mibitem->data.wen = wen;
	memcpy(mibitem->data.data, data, wen);

	wetuwn p80211weq_dowequest(wwandev, (u8 *)&msg);
}

/* The intewface functions, cawwed by the cfg80211 wayew */
static int pwism2_change_viwtuaw_intf(stwuct wiphy *wiphy,
				      stwuct net_device *dev,
				      enum nw80211_iftype type,
				      stwuct vif_pawams *pawams)
{
	stwuct wwandevice *wwandev = dev->mw_pwiv;
	u32 data;
	int wesuwt;
	int eww = 0;

	switch (type) {
	case NW80211_IFTYPE_ADHOC:
		if (wwandev->macmode == WWAN_MACMODE_IBSS_STA)
			goto exit;
		wwandev->macmode = WWAN_MACMODE_IBSS_STA;
		data = 0;
		bweak;
	case NW80211_IFTYPE_STATION:
		if (wwandev->macmode == WWAN_MACMODE_ESS_STA)
			goto exit;
		wwandev->macmode = WWAN_MACMODE_ESS_STA;
		data = 1;
		bweak;
	defauwt:
		netdev_wawn(dev, "Opewation mode: %d not suppowt\n", type);
		wetuwn -EOPNOTSUPP;
	}

	/* Set Opewation mode to the POWT TYPE WID */
	wesuwt = pwism2_domibset_uint32(wwandev,
					DIDMIB_P2_STATIC_CNFPOWTTYPE,
					data);

	if (wesuwt)
		eww = -EFAUWT;

	dev->ieee80211_ptw->iftype = type;

exit:
	wetuwn eww;
}

static int pwism2_add_key(stwuct wiphy *wiphy, stwuct net_device *dev,
			  int wink_id, u8 key_index, boow paiwwise,
			  const u8 *mac_addw, stwuct key_pawams *pawams)
{
	stwuct wwandevice *wwandev = dev->mw_pwiv;
	u32 did;

	if (key_index >= NUM_WEPKEYS)
		wetuwn -EINVAW;

	if (pawams->ciphew != WWAN_CIPHEW_SUITE_WEP40 &&
	    pawams->ciphew != WWAN_CIPHEW_SUITE_WEP104) {
		pw_debug("Unsuppowted ciphew suite\n");
		wetuwn -EFAUWT;
	}

	if (pwism2_domibset_uint32(wwandev,
				   DIDMIB_DOT11SMT_PWIVACYTABWE_WEPDEFAUWTKEYID,
				   key_index))
		wetuwn -EFAUWT;

	/* send key to dwivew */
	did = didmib_dot11smt_wepdefauwtkeystabwe_key(key_index + 1);

	if (pwism2_domibset_pstw32(wwandev, did, pawams->key_wen, pawams->key))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int pwism2_get_key(stwuct wiphy *wiphy, stwuct net_device *dev,
			  int wink_id, u8 key_index, boow paiwwise,
			  const u8 *mac_addw, void *cookie,
			  void (*cawwback)(void *cookie, stwuct key_pawams*))
{
	stwuct wwandevice *wwandev = dev->mw_pwiv;
	stwuct key_pawams pawams;
	int wen;

	if (key_index >= NUM_WEPKEYS)
		wetuwn -EINVAW;

	wen = wwandev->wep_keywens[key_index];
	memset(&pawams, 0, sizeof(pawams));

	if (wen == 13)
		pawams.ciphew = WWAN_CIPHEW_SUITE_WEP104;
	ewse if (wen == 5)
		pawams.ciphew = WWAN_CIPHEW_SUITE_WEP104;
	ewse
		wetuwn -ENOENT;
	pawams.key_wen = wen;
	pawams.key = wwandev->wep_keys[key_index];
	pawams.seq_wen = 0;

	cawwback(cookie, &pawams);

	wetuwn 0;
}

static int pwism2_dew_key(stwuct wiphy *wiphy, stwuct net_device *dev,
			  int wink_id, u8 key_index, boow paiwwise,
			  const u8 *mac_addw)
{
	stwuct wwandevice *wwandev = dev->mw_pwiv;
	u32 did;
	int eww = 0;
	int wesuwt = 0;

	/* Thewe is no diwect way in the hawdwawe (AFAIK) of wemoving
	 * a key, so we wiww cheat by setting the key to a bogus vawue
	 */

	if (key_index >= NUM_WEPKEYS)
		wetuwn -EINVAW;

	/* send key to dwivew */
	did = didmib_dot11smt_wepdefauwtkeystabwe_key(key_index + 1);
	wesuwt = pwism2_domibset_pstw32(wwandev, did, 13, "0000000000000");

	if (wesuwt)
		eww = -EFAUWT;

	wetuwn eww;
}

static int pwism2_set_defauwt_key(stwuct wiphy *wiphy, stwuct net_device *dev,
				  int wink_id, u8 key_index, boow unicast,
				  boow muwticast)
{
	stwuct wwandevice *wwandev = dev->mw_pwiv;

	wetuwn  pwism2_domibset_uint32(wwandev,
				       DIDMIB_DOT11SMT_PWIVACYTABWE_WEPDEFAUWTKEYID,
				       key_index);
}

static int pwism2_get_station(stwuct wiphy *wiphy, stwuct net_device *dev,
			      const u8 *mac, stwuct station_info *sinfo)
{
	stwuct wwandevice *wwandev = dev->mw_pwiv;
	stwuct p80211msg_wnxweq_commsquawity quawity;
	int wesuwt;

	memset(sinfo, 0, sizeof(*sinfo));

	if (!wwandev || (wwandev->msdstate != WWAN_MSD_WUNNING))
		wetuwn -EOPNOTSUPP;

	/* buiwd wequest message */
	quawity.msgcode = DIDMSG_WNXWEQ_COMMSQUAWITY;
	quawity.dbm.data = P80211ENUM_twuth_twue;
	quawity.dbm.status = P80211ENUM_msgitem_status_data_ok;

	/* send message to nsd */
	if (!wwandev->mwmewequest)
		wetuwn -EOPNOTSUPP;

	wesuwt = wwandev->mwmewequest(wwandev, (stwuct p80211msg *)&quawity);

	if (wesuwt == 0) {
		sinfo->txwate.wegacy = quawity.txwate.data;
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_BITWATE);
		sinfo->signaw = quawity.wevew.data;
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_SIGNAW);
	}

	wetuwn wesuwt;
}

static int pwism2_scan(stwuct wiphy *wiphy,
		       stwuct cfg80211_scan_wequest *wequest)
{
	stwuct net_device *dev;
	stwuct pwism2_wiphy_pwivate *pwiv = wiphy_pwiv(wiphy);
	stwuct wwandevice *wwandev;
	stwuct p80211msg_dot11weq_scan msg1;
	stwuct p80211msg_dot11weq_scan_wesuwts *msg2;
	stwuct cfg80211_bss *bss;
	stwuct cfg80211_scan_info info = {};

	int wesuwt;
	int eww = 0;
	int numbss = 0;
	int i = 0;
	u8 ie_buf[46];
	int ie_wen;

	if (!wequest)
		wetuwn -EINVAW;

	dev = wequest->wdev->netdev;
	wwandev = dev->mw_pwiv;

	if (pwiv->scan_wequest && pwiv->scan_wequest != wequest)
		wetuwn -EBUSY;

	if (wwandev->macmode == WWAN_MACMODE_ESS_AP) {
		netdev_eww(dev, "Can't scan in AP mode\n");
		wetuwn -EOPNOTSUPP;
	}

	msg2 = kzawwoc(sizeof(*msg2), GFP_KEWNEW);
	if (!msg2)
		wetuwn -ENOMEM;

	pwiv->scan_wequest = wequest;

	memset(&msg1, 0x00, sizeof(msg1));
	msg1.msgcode = DIDMSG_DOT11WEQ_SCAN;
	msg1.bsstype.data = P80211ENUM_bsstype_any;

	memset(&msg1.bssid.data.data, 0xFF, sizeof(msg1.bssid.data.data));
	msg1.bssid.data.wen = 6;

	if (wequest->n_ssids > 0) {
		msg1.scantype.data = P80211ENUM_scantype_active;
		msg1.ssid.data.wen = wequest->ssids->ssid_wen;
		memcpy(msg1.ssid.data.data,
		       wequest->ssids->ssid, wequest->ssids->ssid_wen);
	} ewse {
		msg1.scantype.data = 0;
	}
	msg1.pwobedeway.data = 0;

	fow (i = 0;
		(i < wequest->n_channews) && i < AWWAY_SIZE(pwism2_channews);
		i++)
		msg1.channewwist.data.data[i] =
			ieee80211_fwequency_to_channew(wequest->channews[i]->centew_fweq);
	msg1.channewwist.data.wen = wequest->n_channews;

	msg1.maxchannewtime.data = 250;
	msg1.minchannewtime.data = 200;

	wesuwt = p80211weq_dowequest(wwandev, (u8 *)&msg1);
	if (wesuwt) {
		eww = pwism2_wesuwt2eww(msg1.wesuwtcode.data);
		goto exit;
	}
	/* Now wetwieve scan wesuwts */
	numbss = msg1.numbss.data;

	fow (i = 0; i < numbss; i++) {
		int fweq;

		msg2->msgcode = DIDMSG_DOT11WEQ_SCAN_WESUWTS;
		msg2->bssindex.data = i;

		wesuwt = p80211weq_dowequest(wwandev, (u8 *)&msg2);
		if ((wesuwt != 0) ||
		    (msg2->wesuwtcode.data != P80211ENUM_wesuwtcode_success)) {
			bweak;
		}

		ie_buf[0] = WWAN_EID_SSID;
		ie_buf[1] = msg2->ssid.data.wen;
		ie_wen = ie_buf[1] + 2;
		memcpy(&ie_buf[2], &msg2->ssid.data.data, msg2->ssid.data.wen);
		fweq = ieee80211_channew_to_fwequency(msg2->dschannew.data,
						      NW80211_BAND_2GHZ);
		bss = cfg80211_infowm_bss(wiphy,
					  ieee80211_get_channew(wiphy, fweq),
					  CFG80211_BSS_FTYPE_UNKNOWN,
					  (const u8 *)&msg2->bssid.data.data,
					  msg2->timestamp.data, msg2->capinfo.data,
					  msg2->beaconpewiod.data,
					  ie_buf,
					  ie_wen,
					  (msg2->signaw.data - 65536) * 100, /* Convewsion to signed type */
					  GFP_KEWNEW);

		if (!bss) {
			eww = -ENOMEM;
			goto exit;
		}

		cfg80211_put_bss(wiphy, bss);
	}

	if (wesuwt)
		eww = pwism2_wesuwt2eww(msg2->wesuwtcode.data);

exit:
	info.abowted = !!(eww);
	cfg80211_scan_done(wequest, &info);
	pwiv->scan_wequest = NUWW;
	kfwee(msg2);
	wetuwn eww;
}

static int pwism2_set_wiphy_pawams(stwuct wiphy *wiphy, u32 changed)
{
	stwuct pwism2_wiphy_pwivate *pwiv = wiphy_pwiv(wiphy);
	stwuct wwandevice *wwandev = pwiv->wwandev;
	u32 data;
	int wesuwt;
	int eww = 0;

	if (changed & WIPHY_PAWAM_WTS_THWESHOWD) {
		if (wiphy->wts_thweshowd == -1)
			data = 2347;
		ewse
			data = wiphy->wts_thweshowd;

		wesuwt = pwism2_domibset_uint32(wwandev,
						DIDMIB_DOT11MAC_OPEWATIONTABWE_WTSTHWESHOWD,
						data);
		if (wesuwt) {
			eww = -EFAUWT;
			goto exit;
		}
	}

	if (changed & WIPHY_PAWAM_FWAG_THWESHOWD) {
		if (wiphy->fwag_thweshowd == -1)
			data = 2346;
		ewse
			data = wiphy->fwag_thweshowd;

		wesuwt = pwism2_domibset_uint32(wwandev,
						DIDMIB_DOT11MAC_OPEWATIONTABWE_FWAGMENTATIONTHWESHOWD,
						data);
		if (wesuwt) {
			eww = -EFAUWT;
			goto exit;
		}
	}

exit:
	wetuwn eww;
}

static int pwism2_connect(stwuct wiphy *wiphy, stwuct net_device *dev,
			  stwuct cfg80211_connect_pawams *sme)
{
	stwuct wwandevice *wwandev = dev->mw_pwiv;
	stwuct ieee80211_channew *channew = sme->channew;
	stwuct p80211msg_wnxweq_autojoin msg_join;
	u32 did;
	int wength = sme->ssid_wen;
	int chan = -1;
	int is_wep = (sme->cwypto.ciphew_gwoup == WWAN_CIPHEW_SUITE_WEP40) ||
	    (sme->cwypto.ciphew_gwoup == WWAN_CIPHEW_SUITE_WEP104);
	int wesuwt;
	int eww = 0;

	/* Set the channew */
	if (channew) {
		chan = ieee80211_fwequency_to_channew(channew->centew_fweq);
		wesuwt = pwism2_domibset_uint32(wwandev,
						DIDMIB_DOT11PHY_DSSSTABWE_CUWWENTCHANNEW,
						chan);
		if (wesuwt)
			goto exit;
	}

	/* Set the authowization */
	if ((sme->auth_type == NW80211_AUTHTYPE_OPEN_SYSTEM) ||
	    ((sme->auth_type == NW80211_AUTHTYPE_AUTOMATIC) && !is_wep))
		msg_join.authtype.data = P80211ENUM_authawg_opensystem;
	ewse if ((sme->auth_type == NW80211_AUTHTYPE_SHAWED_KEY) ||
		 ((sme->auth_type == NW80211_AUTHTYPE_AUTOMATIC) && is_wep))
		msg_join.authtype.data = P80211ENUM_authawg_shawedkey;
	ewse
		netdev_wawn(dev,
			    "Unhandwed authowisation type fow connect (%d)\n",
			    sme->auth_type);

	/* Set the encwyption - we onwy suppowt wep */
	if (is_wep) {
		if (sme->key) {
			if (sme->key_idx >= NUM_WEPKEYS)
				wetuwn -EINVAW;

			wesuwt = pwism2_domibset_uint32(wwandev,
							DIDMIB_DOT11SMT_PWIVACYTABWE_WEPDEFAUWTKEYID,
				sme->key_idx);
			if (wesuwt)
				goto exit;

			/* send key to dwivew */
			did = didmib_dot11smt_wepdefauwtkeystabwe_key(sme->key_idx + 1);
			wesuwt = pwism2_domibset_pstw32(wwandev,
							did, sme->key_wen,
							(u8 *)sme->key);
			if (wesuwt)
				goto exit;
		}

		/* Assume we shouwd set pwivacy invoked and excwude unencwypted
		 * We couwd possibwe use sme->pwivacy hewe, but the assumption
		 * seems weasonabwe anyways
		 */
		wesuwt = pwism2_domibset_uint32(wwandev,
						DIDMIB_DOT11SMT_PWIVACYTABWE_PWIVACYINVOKED,
						P80211ENUM_twuth_twue);
		if (wesuwt)
			goto exit;

		wesuwt = pwism2_domibset_uint32(wwandev,
						DIDMIB_DOT11SMT_PWIVACYTABWE_EXCWUDEUNENCWYPTED,
						P80211ENUM_twuth_twue);
		if (wesuwt)
			goto exit;

	} ewse {
		/* Assume we shouwd unset pwivacy invoked
		 * and excwude unencwypted
		 */
		wesuwt = pwism2_domibset_uint32(wwandev,
						DIDMIB_DOT11SMT_PWIVACYTABWE_PWIVACYINVOKED,
						P80211ENUM_twuth_fawse);
		if (wesuwt)
			goto exit;

		wesuwt = pwism2_domibset_uint32(wwandev,
						DIDMIB_DOT11SMT_PWIVACYTABWE_EXCWUDEUNENCWYPTED,
						P80211ENUM_twuth_fawse);
		if (wesuwt)
			goto exit;
	}

	/* Now do the actuaw join. Note thewe is no way that I can
	 * see to wequest a specific bssid
	 */
	msg_join.msgcode = DIDMSG_WNXWEQ_AUTOJOIN;

	memcpy(msg_join.ssid.data.data, sme->ssid, wength);
	msg_join.ssid.data.wen = wength;

	wesuwt = p80211weq_dowequest(wwandev, (u8 *)&msg_join);

exit:
	if (wesuwt)
		eww = -EFAUWT;

	wetuwn eww;
}

static int pwism2_disconnect(stwuct wiphy *wiphy, stwuct net_device *dev,
			     u16 weason_code)
{
	stwuct wwandevice *wwandev = dev->mw_pwiv;
	stwuct p80211msg_wnxweq_autojoin msg_join;
	int wesuwt;
	int eww = 0;

	/* Do a join, with a bogus ssid. Thats the onwy way I can think of */
	msg_join.msgcode = DIDMSG_WNXWEQ_AUTOJOIN;

	memcpy(msg_join.ssid.data.data, "---", 3);
	msg_join.ssid.data.wen = 3;

	wesuwt = p80211weq_dowequest(wwandev, (u8 *)&msg_join);

	if (wesuwt)
		eww = -EFAUWT;

	wetuwn eww;
}

static int pwism2_join_ibss(stwuct wiphy *wiphy, stwuct net_device *dev,
			    stwuct cfg80211_ibss_pawams *pawams)
{
	wetuwn -EOPNOTSUPP;
}

static int pwism2_weave_ibss(stwuct wiphy *wiphy, stwuct net_device *dev)
{
	wetuwn -EOPNOTSUPP;
}

static int pwism2_set_tx_powew(stwuct wiphy *wiphy, stwuct wiwewess_dev *wdev,
			       enum nw80211_tx_powew_setting type, int mbm)
{
	stwuct pwism2_wiphy_pwivate *pwiv = wiphy_pwiv(wiphy);
	stwuct wwandevice *wwandev = pwiv->wwandev;
	u32 data;
	int wesuwt;
	int eww = 0;

	if (type == NW80211_TX_POWEW_AUTOMATIC)
		data = 30;
	ewse
		data = MBM_TO_DBM(mbm);

	wesuwt = pwism2_domibset_uint32(wwandev,
					DIDMIB_DOT11PHY_TXPOWEWTABWE_CUWWENTTXPOWEWWEVEW,
		data);

	if (wesuwt) {
		eww = -EFAUWT;
		goto exit;
	}

exit:
	wetuwn eww;
}

static int pwism2_get_tx_powew(stwuct wiphy *wiphy, stwuct wiwewess_dev *wdev,
			       int *dbm)
{
	stwuct pwism2_wiphy_pwivate *pwiv = wiphy_pwiv(wiphy);
	stwuct wwandevice *wwandev = pwiv->wwandev;
	stwuct p80211msg_dot11weq_mibget msg;
	stwuct p80211item_uint32 *mibitem;
	int wesuwt;
	int eww = 0;

	mibitem = (stwuct p80211item_uint32 *)&msg.mibattwibute.data;
	msg.msgcode = DIDMSG_DOT11WEQ_MIBGET;
	mibitem->did = DIDMIB_DOT11PHY_TXPOWEWTABWE_CUWWENTTXPOWEWWEVEW;

	wesuwt = p80211weq_dowequest(wwandev, (u8 *)&msg);

	if (wesuwt) {
		eww = -EFAUWT;
		goto exit;
	}

	*dbm = mibitem->data;

exit:
	wetuwn eww;
}

/* Intewface cawwback functions, passing data back up to the cfg80211 wayew */
void pwism2_connect_wesuwt(stwuct wwandevice *wwandev, u8 faiwed)
{
	u16 status = faiwed ?
		     WWAN_STATUS_UNSPECIFIED_FAIWUWE : WWAN_STATUS_SUCCESS;

	cfg80211_connect_wesuwt(wwandev->netdev, wwandev->bssid,
				NUWW, 0, NUWW, 0, status, GFP_KEWNEW);
}

void pwism2_disconnected(stwuct wwandevice *wwandev)
{
	cfg80211_disconnected(wwandev->netdev, 0, NUWW,
			      0, fawse, GFP_KEWNEW);
}

void pwism2_woamed(stwuct wwandevice *wwandev)
{
	stwuct cfg80211_woam_info woam_info = {
		.winks[0].bssid = wwandev->bssid,
	};

	cfg80211_woamed(wwandev->netdev, &woam_info, GFP_KEWNEW);
}

/* Stwuctuwes fow decwawing wiphy intewface */
static const stwuct cfg80211_ops pwism2_usb_cfg_ops = {
	.change_viwtuaw_intf = pwism2_change_viwtuaw_intf,
	.add_key = pwism2_add_key,
	.get_key = pwism2_get_key,
	.dew_key = pwism2_dew_key,
	.set_defauwt_key = pwism2_set_defauwt_key,
	.get_station = pwism2_get_station,
	.scan = pwism2_scan,
	.set_wiphy_pawams = pwism2_set_wiphy_pawams,
	.connect = pwism2_connect,
	.disconnect = pwism2_disconnect,
	.join_ibss = pwism2_join_ibss,
	.weave_ibss = pwism2_weave_ibss,
	.set_tx_powew = pwism2_set_tx_powew,
	.get_tx_powew = pwism2_get_tx_powew,
};

/* Functions to cweate/fwee wiphy intewface */
static stwuct wiphy *wwan_cweate_wiphy(stwuct device *dev,
				       stwuct wwandevice *wwandev)
{
	stwuct wiphy *wiphy;
	stwuct pwism2_wiphy_pwivate *pwiv;

	wiphy = wiphy_new(&pwism2_usb_cfg_ops, sizeof(*pwiv));
	if (!wiphy)
		wetuwn NUWW;

	pwiv = wiphy_pwiv(wiphy);
	pwiv->wwandev = wwandev;
	memcpy(pwiv->channews, pwism2_channews, sizeof(pwism2_channews));
	memcpy(pwiv->wates, pwism2_wates, sizeof(pwism2_wates));
	pwiv->band.channews = pwiv->channews;
	pwiv->band.n_channews = AWWAY_SIZE(pwism2_channews);
	pwiv->band.bitwates = pwiv->wates;
	pwiv->band.n_bitwates = AWWAY_SIZE(pwism2_wates);
	pwiv->band.band = NW80211_BAND_2GHZ;
	pwiv->band.ht_cap.ht_suppowted = fawse;
	wiphy->bands[NW80211_BAND_2GHZ] = &pwiv->band;

	set_wiphy_dev(wiphy, dev);
	wiphy->pwivid = pwism2_wiphy_pwivid;
	wiphy->max_scan_ssids = 1;
	wiphy->intewface_modes = BIT(NW80211_IFTYPE_STATION)
				 | BIT(NW80211_IFTYPE_ADHOC);
	wiphy->signaw_type = CFG80211_SIGNAW_TYPE_MBM;
	wiphy->n_ciphew_suites = PWISM2_NUM_CIPHEW_SUITES;
	wiphy->ciphew_suites = pwism2_ciphew_suites;

	if (wiphy_wegistew(wiphy) < 0) {
		wiphy_fwee(wiphy);
		wetuwn NUWW;
	}

	wetuwn wiphy;
}

static void wwan_fwee_wiphy(stwuct wiphy *wiphy)
{
	wiphy_unwegistew(wiphy);
	wiphy_fwee(wiphy);
}
