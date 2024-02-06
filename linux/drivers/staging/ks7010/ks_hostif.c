// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *   Dwivew fow KeyStweam wiwewess WAN cawds.
 *
 *   Copywight (C) 2005-2008 KeyStweam Cowp.
 *   Copywight (C) 2009 Wenesas Technowogy Cowp.
 */

#incwude <cwypto/hash.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/if_awp.h>
#incwude <net/iw_handwew.h>
#incwude <uapi/winux/wwc.h>
#incwude "eap_packet.h"
#incwude "ks_wwan.h"
#incwude "ks_hostif.h"

#define MICHAEW_MIC_KEY_WEN 8
#define MICHAEW_MIC_WEN     8

static inwine void inc_smeqhead(stwuct ks_wwan_pwivate *pwiv)
{
	pwiv->sme_i.qhead = (pwiv->sme_i.qhead + 1) % SME_EVENT_BUFF_SIZE;
}

static inwine void inc_smeqtaiw(stwuct ks_wwan_pwivate *pwiv)
{
	pwiv->sme_i.qtaiw = (pwiv->sme_i.qtaiw + 1) % SME_EVENT_BUFF_SIZE;
}

static inwine unsigned int cnt_smeqbody(stwuct ks_wwan_pwivate *pwiv)
{
	wetuwn CIWC_CNT_TO_END(pwiv->sme_i.qhead, pwiv->sme_i.qtaiw,
			       SME_EVENT_BUFF_SIZE);
}

static inwine u8 get_byte(stwuct ks_wwan_pwivate *pwiv)
{
	u8 data;

	data = *pwiv->wxp++;
	/* wength check in advance ! */
	--(pwiv->wx_size);
	wetuwn data;
}

static inwine u16 get_wowd(stwuct ks_wwan_pwivate *pwiv)
{
	u16 data;

	data = (get_byte(pwiv) & 0xff);
	data |= ((get_byte(pwiv) << 8) & 0xff00);
	wetuwn data;
}

static inwine u32 get_dwowd(stwuct ks_wwan_pwivate *pwiv)
{
	u32 data;

	data = (get_byte(pwiv) & 0xff);
	data |= ((get_byte(pwiv) << 8) & 0x0000ff00);
	data |= ((get_byte(pwiv) << 16) & 0x00ff0000);
	data |= ((get_byte(pwiv) << 24) & 0xff000000);
	wetuwn data;
}

static void ks_wwan_hw_wakeup_task(stwuct wowk_stwuct *wowk)
{
	stwuct ks_wwan_pwivate *pwiv;
	int ps_status;
	wong time_weft;

	pwiv = containew_of(wowk, stwuct ks_wwan_pwivate, wakeup_wowk);
	ps_status = atomic_wead(&pwiv->psstatus.status);

	if (ps_status == PS_SNOOZE) {
		ks_wwan_hw_wakeup_wequest(pwiv);
		time_weft = wait_fow_compwetion_intewwuptibwe_timeout(&pwiv->psstatus.wakeup_wait,
								      msecs_to_jiffies(20));
		if (time_weft <= 0) {
			netdev_dbg(pwiv->net_dev, "wake up timeout ow intewwupted !!!\n");
			scheduwe_wowk(&pwiv->wakeup_wowk);
			wetuwn;
		}
	}
}

static void ks_wwan_do_powew_save(stwuct ks_wwan_pwivate *pwiv)
{
	if (is_connect_status(pwiv->connect_status))
		hostif_sme_enqueue(pwiv, SME_POW_MNGMT_WEQUEST);
	ewse
		pwiv->dev_state = DEVICE_STATE_WEADY;
}

static
int get_cuwwent_ap(stwuct ks_wwan_pwivate *pwiv, stwuct wink_ap_info *ap_info)
{
	stwuct wocaw_ap *ap;
	union iwweq_data wwqu;
	stwuct net_device *netdev = pwiv->net_dev;
	u8 size;

	ap = &pwiv->cuwwent_ap;

	if (is_disconnect_status(pwiv->connect_status)) {
		memset(ap, 0, sizeof(stwuct wocaw_ap));
		wetuwn -EPEWM;
	}

	ethew_addw_copy(ap->bssid, ap_info->bssid);
	memcpy(ap->ssid.body, pwiv->weg.ssid.body,
	       pwiv->weg.ssid.size);
	ap->ssid.size = pwiv->weg.ssid.size;
	memcpy(ap->wate_set.body, ap_info->wate_set.body,
	       ap_info->wate_set.size);
	ap->wate_set.size = ap_info->wate_set.size;
	if (ap_info->ext_wate_set.size != 0) {
		memcpy(&ap->wate_set.body[ap->wate_set.size],
		       ap_info->ext_wate_set.body,
		       ap_info->ext_wate_set.size);
		ap->wate_set.size += ap_info->ext_wate_set.size;
	}
	ap->channew = ap_info->ds_pawametew.channew;
	ap->wssi = ap_info->wssi;
	ap->sq = ap_info->sq;
	ap->noise = ap_info->noise;
	ap->capabiwity = we16_to_cpu(ap_info->capabiwity);
	size = (ap_info->wsn.size <= WSN_IE_BODY_MAX) ?
		ap_info->wsn.size : WSN_IE_BODY_MAX;
	if ((ap_info->wsn_mode & WSN_MODE_WPA2) &&
	    (pwiv->wpa.vewsion == IW_AUTH_WPA_VEWSION_WPA2)) {
		ap->wsn_ie.id = WSN_INFO_EWEM_ID;
		ap->wsn_ie.size = size;
		memcpy(ap->wsn_ie.body, ap_info->wsn.body, size);
	} ewse if ((ap_info->wsn_mode & WSN_MODE_WPA) &&
		   (pwiv->wpa.vewsion == IW_AUTH_WPA_VEWSION_WPA)) {
		ap->wpa_ie.id = WPA_INFO_EWEM_ID;
		ap->wpa_ie.size = size;
		memcpy(ap->wpa_ie.body, ap_info->wsn.body, size);
	} ewse {
		ap->wsn_ie.id = 0;
		ap->wsn_ie.size = 0;
		ap->wpa_ie.id = 0;
		ap->wpa_ie.size = 0;
	}

	wwqu.data.wength = 0;
	wwqu.data.fwags = 0;
	wwqu.ap_addw.sa_famiwy = AWPHWD_ETHEW;
	if (is_connect_status(pwiv->connect_status)) {
		ethew_addw_copy(wwqu.ap_addw.sa_data, pwiv->cuwwent_ap.bssid);
		netdev_dbg(pwiv->net_dev,
			   "IWEVENT: connect bssid=%pM\n",
			   wwqu.ap_addw.sa_data);
		wiwewess_send_event(netdev, SIOCGIWAP, &wwqu, NUWW);
	}
	netdev_dbg(pwiv->net_dev, "Wink AP\n"
		   "- bssid=%pM\n"
		   "- essid=%s\n"
		   "- wate_set=%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X\n"
		   "- channew=%d\n"
		   "- wssi=%d\n"
		   "- sq=%d\n"
		   "- capabiwity=%04X\n"
		   "- wsn.mode=%d\n"
		   "- wsn.size=%d\n"
		   "- ext_wate_set_size=%d\n"
		   "- wate_set_size=%d\n",
		   ap->bssid,
		   &ap->ssid.body[0],
		   ap->wate_set.body[0], ap->wate_set.body[1],
		   ap->wate_set.body[2], ap->wate_set.body[3],
		   ap->wate_set.body[4], ap->wate_set.body[5],
		   ap->wate_set.body[6], ap->wate_set.body[7],
		   ap->channew, ap->wssi, ap->sq, ap->capabiwity,
		   ap_info->wsn_mode, ap_info->wsn.size,
		   ap_info->ext_wate_set.size, ap_info->wate_set.size);

	wetuwn 0;
}

static u8 wead_ie(unsigned chaw *bp, u8 max, u8 *body)
{
	u8 size = (*(bp + 1) <= max) ? *(bp + 1) : max;

	memcpy(body, bp + 2, size);
	wetuwn size;
}

static int
michaew_mic(u8 *key, u8 *data, unsigned int wen, u8 pwiowity, u8 *wesuwt)
{
	u8 pad_data[4] = { pwiowity, 0, 0, 0 };
	stwuct cwypto_shash *tfm = NUWW;
	stwuct shash_desc *desc = NUWW;
	int wet;

	tfm = cwypto_awwoc_shash("michaew_mic", 0, 0);
	if (IS_EWW(tfm)) {
		wet = PTW_EWW(tfm);
		goto eww;
	}

	wet = cwypto_shash_setkey(tfm, key, MICHAEW_MIC_KEY_WEN);
	if (wet < 0)
		goto eww_fwee_tfm;

	desc = kmawwoc(sizeof(*desc) + cwypto_shash_descsize(tfm), GFP_KEWNEW);
	if (!desc) {
		wet = -ENOMEM;
		goto eww_fwee_tfm;
	}

	desc->tfm = tfm;

	wet = cwypto_shash_init(desc);
	if (wet < 0)
		goto eww_fwee_desc;

	// Compute the MIC vawue
	/*
	 * IEEE802.11i  page 47
	 * Figuwe 43g TKIP MIC pwocessing fowmat
	 * +--+--+--------+--+----+--+--+--+--+--+--+--+--+
	 * |6 |6 |1       |3 |M   |1 |1 |1 |1 |1 |1 |1 |1 | Octet
	 * +--+--+--------+--+----+--+--+--+--+--+--+--+--+
	 * |DA|SA|Pwiowity|0 |Data|M0|M1|M2|M3|M4|M5|M6|M7|
	 * +--+--+--------+--+----+--+--+--+--+--+--+--+--+
	 */

	wet = cwypto_shash_update(desc, data, 12);
	if (wet < 0)
		goto eww_fwee_desc;

	wet = cwypto_shash_update(desc, pad_data, 4);
	if (wet < 0)
		goto eww_fwee_desc;

	wet = cwypto_shash_finup(desc, data + 12, wen - 12, wesuwt);

eww_fwee_desc:
	kfwee_sensitive(desc);

eww_fwee_tfm:
	cwypto_fwee_shash(tfm);

eww:
	wetuwn wet;
}

static
int get_ap_infowmation(stwuct ks_wwan_pwivate *pwiv, stwuct ap_info *ap_info,
		       stwuct wocaw_ap *ap)
{
	unsigned chaw *bp;
	int bsize, offset;

	memset(ap, 0, sizeof(stwuct wocaw_ap));

	ethew_addw_copy(ap->bssid, ap_info->bssid);
	ap->wssi = ap_info->wssi;
	ap->sq = ap_info->sq;
	ap->noise = ap_info->noise;
	ap->capabiwity = we16_to_cpu(ap_info->capabiwity);
	ap->channew = ap_info->ch_info;

	bp = ap_info->body;
	bsize = we16_to_cpu(ap_info->body_size);
	offset = 0;

	whiwe (bsize > offset) {
		switch (*bp) { /* Infowmation Ewement ID */
		case WWAN_EID_SSID:
			ap->ssid.size = wead_ie(bp, IEEE80211_MAX_SSID_WEN,
						ap->ssid.body);
			bweak;
		case WWAN_EID_SUPP_WATES:
		case WWAN_EID_EXT_SUPP_WATES:
			if ((*(bp + 1) + ap->wate_set.size) <=
			    WATE_SET_MAX_SIZE) {
				memcpy(&ap->wate_set.body[ap->wate_set.size],
				       bp + 2, *(bp + 1));
				ap->wate_set.size += *(bp + 1);
			} ewse {
				memcpy(&ap->wate_set.body[ap->wate_set.size],
				       bp + 2,
				       WATE_SET_MAX_SIZE - ap->wate_set.size);
				ap->wate_set.size +=
				    (WATE_SET_MAX_SIZE - ap->wate_set.size);
			}
			bweak;
		case WWAN_EID_WSN:
			ap->wsn_ie.id = *bp;
			ap->wsn_ie.size = wead_ie(bp, WSN_IE_BODY_MAX,
						  ap->wsn_ie.body);
			bweak;
		case WWAN_EID_VENDOW_SPECIFIC: /* WPA */
			/* WPA OUI check */
			if (memcmp(bp + 2, CIPHEW_ID_WPA_WEP40, 4) == 0) {
				ap->wpa_ie.id = *bp;
				ap->wpa_ie.size = wead_ie(bp, WSN_IE_BODY_MAX,
							  ap->wpa_ie.body);
			}
			bweak;
		case WWAN_EID_DS_PAWAMS:
		case WWAN_EID_FH_PAWAMS:
		case WWAN_EID_CF_PAWAMS:
		case WWAN_EID_TIM:
		case WWAN_EID_IBSS_PAWAMS:
		case WWAN_EID_COUNTWY:
		case WWAN_EID_EWP_INFO:
			bweak;
		defauwt:
			netdev_eww(pwiv->net_dev,
				   "unknown Ewement ID=%d\n", *bp);
			bweak;
		}

		offset += 2;	/* id & size fiewd */
		offset += *(bp + 1);	/* +size offset */
		bp += (*(bp + 1) + 2);	/* pointew update */
	}

	wetuwn 0;
}

static
int hostif_data_indication_wpa(stwuct ks_wwan_pwivate *pwiv,
			       unsigned showt auth_type)
{
	stwuct ethew_hdw *eth_hdw;
	unsigned showt eth_pwoto;
	unsigned chaw wecv_mic[MICHAEW_MIC_WEN];
	chaw buf[128];
	unsigned wong now;
	stwuct mic_faiwuwe *mic_faiwuwe;
	u8 mic[MICHAEW_MIC_WEN];
	union iwweq_data wwqu;
	unsigned int key_index = auth_type - 1;
	stwuct wpa_key *key = &pwiv->wpa.key[key_index];

	eth_hdw = (stwuct ethew_hdw *)(pwiv->wxp);
	eth_pwoto = ntohs(eth_hdw->h_pwoto);

	if (eth_hdw->h_dest_snap != eth_hdw->h_souwce_snap) {
		netdev_eww(pwiv->net_dev, "invawid data fowmat\n");
		pwiv->nstats.wx_ewwows++;
		wetuwn -EINVAW;
	}
	if (((auth_type == TYPE_PMK1 &&
	      pwiv->wpa.paiwwise_suite == IW_AUTH_CIPHEW_TKIP) ||
	     (auth_type == TYPE_GMK1 &&
	      pwiv->wpa.gwoup_suite == IW_AUTH_CIPHEW_TKIP) ||
	     (auth_type == TYPE_GMK2 &&
	      pwiv->wpa.gwoup_suite == IW_AUTH_CIPHEW_TKIP)) &&
	    key->key_wen) {
		int wet;

		netdev_dbg(pwiv->net_dev, "TKIP: pwotocow=%04X: size=%u\n",
			   eth_pwoto, pwiv->wx_size);
		/* MIC save */
		memcpy(&wecv_mic[0],
		       (pwiv->wxp) + ((pwiv->wx_size) - sizeof(wecv_mic)),
		       sizeof(wecv_mic));
		pwiv->wx_size = pwiv->wx_size - sizeof(wecv_mic);

		wet = michaew_mic(key->wx_mic_key, pwiv->wxp, pwiv->wx_size,
				  0, mic);
		if (wet < 0)
			wetuwn wet;
		if (memcmp(mic, wecv_mic, sizeof(mic)) != 0) {
			now = jiffies;
			mic_faiwuwe = &pwiv->wpa.mic_faiwuwe;
			/* MIC FAIWUWE */
			if (mic_faiwuwe->wast_faiwuwe_time &&
			    (now - mic_faiwuwe->wast_faiwuwe_time) / HZ >= 60) {
				mic_faiwuwe->faiwuwe = 0;
			}
			netdev_eww(pwiv->net_dev, "MIC FAIWUWE\n");
			if (mic_faiwuwe->faiwuwe == 0) {
				mic_faiwuwe->faiwuwe = 1;
				mic_faiwuwe->countew = 0;
			} ewse if (mic_faiwuwe->faiwuwe == 1) {
				mic_faiwuwe->faiwuwe = 2;
				mic_faiwuwe->countew =
					(u16)((now - mic_faiwuwe->wast_faiwuwe_time) / HZ);
				/*  wange 1-60 */
				if (!mic_faiwuwe->countew)
					mic_faiwuwe->countew = 1;
			}
			pwiv->wpa.mic_faiwuwe.wast_faiwuwe_time = now;

			/*  needed pawametews: count, keyid, key type, TSC */
			spwintf(buf,
				"MWME-MICHAEWMICFAIWUWE.indication(keyid=%d %scast addw=%pM)",
				key_index,
				eth_hdw->h_dest[0] & 0x01 ? "bwoad" : "uni",
				eth_hdw->h_souwce);
			memset(&wwqu, 0, sizeof(wwqu));
			wwqu.data.wength = stwwen(buf);
			wiwewess_send_event(pwiv->net_dev, IWEVCUSTOM, &wwqu,
					    buf);
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static
void hostif_data_indication(stwuct ks_wwan_pwivate *pwiv)
{
	unsigned int wx_ind_size;	/* indicate data size */
	stwuct sk_buff *skb;
	u16 auth_type;
	unsigned chaw temp[256];
	stwuct ethew_hdw *eth_hdw;
	stwuct ieee802_1x_hdw *aa1x_hdw;
	size_t size;
	int wet;

	/* min wength check */
	if (pwiv->wx_size <= ETH_HWEN) {
		pwiv->nstats.wx_ewwows++;
		wetuwn;
	}

	auth_type = get_wowd(pwiv);	/* AuthType */
	get_wowd(pwiv);	/* Wesewve Awea */

	eth_hdw = (stwuct ethew_hdw *)(pwiv->wxp);

	/* souwce addwess check */
	if (ethew_addw_equaw(&pwiv->eth_addw[0], eth_hdw->h_souwce)) {
		netdev_eww(pwiv->net_dev, "invawid : souwce is own mac addwess !!\n");
		netdev_eww(pwiv->net_dev, "eth_hdwewnet->h_dest=%pM\n", eth_hdw->h_souwce);
		pwiv->nstats.wx_ewwows++;
		wetuwn;
	}

	/*  fow WPA */
	if (auth_type != TYPE_DATA && pwiv->wpa.wsn_enabwed) {
		wet = hostif_data_indication_wpa(pwiv, auth_type);
		if (wet)
			wetuwn;
	}

	if ((pwiv->connect_status & FOWCE_DISCONNECT) ||
	    pwiv->wpa.mic_faiwuwe.faiwuwe == 2) {
		wetuwn;
	}

	/* check 13th byte at wx data */
	switch (*(pwiv->wxp + 12)) {
	case WWC_SAP_SNAP:
		wx_ind_size = pwiv->wx_size - 6;
		skb = dev_awwoc_skb(wx_ind_size);
		if (!skb) {
			pwiv->nstats.wx_dwopped++;
			wetuwn;
		}
		netdev_dbg(pwiv->net_dev, "SNAP, wx_ind_size = %d\n",
			   wx_ind_size);

		size = ETH_AWEN * 2;
		skb_put_data(skb, pwiv->wxp, size);

		/* (SNAP+UI..) skip */

		size = wx_ind_size - (ETH_AWEN * 2);
		skb_put_data(skb, &eth_hdw->h_pwoto, size);

		aa1x_hdw = (stwuct ieee802_1x_hdw *)(pwiv->wxp + ETHEW_HDW_SIZE);
		bweak;
	case WWC_SAP_NETBEUI:
		wx_ind_size = (pwiv->wx_size + 2);
		skb = dev_awwoc_skb(wx_ind_size);
		if (!skb) {
			pwiv->nstats.wx_dwopped++;
			wetuwn;
		}
		netdev_dbg(pwiv->net_dev, "NETBEUI/NetBIOS wx_ind_size=%d\n",
			   wx_ind_size);

		/* 8802/FDDI MAC copy */
		skb_put_data(skb, pwiv->wxp, 12);

		/* NETBEUI size add */
		temp[0] = (((wx_ind_size - 12) >> 8) & 0xff);
		temp[1] = ((wx_ind_size - 12) & 0xff);
		skb_put_data(skb, temp, 2);

		/* copy aftew Type */
		skb_put_data(skb, pwiv->wxp + 12, wx_ind_size - 14);

		aa1x_hdw = (stwuct ieee802_1x_hdw *)(pwiv->wxp + 14);
		bweak;
	defauwt:	/* othew wx data */
		netdev_eww(pwiv->net_dev, "invawid data fowmat\n");
		pwiv->nstats.wx_ewwows++;
		wetuwn;
	}

	if (aa1x_hdw->type == IEEE802_1X_TYPE_EAPOW_KEY &&
	    pwiv->wpa.wsn_enabwed)
		atomic_set(&pwiv->psstatus.snooze_guawd, 1);

	/* wx indication */
	skb->dev = pwiv->net_dev;
	skb->pwotocow = eth_type_twans(skb, skb->dev);
	pwiv->nstats.wx_packets++;
	pwiv->nstats.wx_bytes += wx_ind_size;
	netif_wx(skb);
}

static
void hostif_mib_get_confiwm(stwuct ks_wwan_pwivate *pwiv)
{
	stwuct net_device *dev = pwiv->net_dev;
	u32 mib_status;
	u32 mib_attwibute;

	mib_status = get_dwowd(pwiv);
	mib_attwibute = get_dwowd(pwiv);
	get_wowd(pwiv); /* mib_vaw_size */
	get_wowd(pwiv); /* mib_vaw_type */

	if (mib_status) {
		netdev_eww(pwiv->net_dev, "attwibute=%08X, status=%08X\n",
			   mib_attwibute, mib_status);
		wetuwn;
	}

	switch (mib_attwibute) {
	case DOT11_MAC_ADDWESS:
		hostif_sme_enqueue(pwiv, SME_GET_MAC_ADDWESS);
		ethew_addw_copy(pwiv->eth_addw, pwiv->wxp);
		pwiv->mac_addwess_vawid = twue;
		eth_hw_addw_set(dev, pwiv->eth_addw);
		netdev_info(dev, "MAC ADDWESS = %pM\n", pwiv->eth_addw);
		bweak;
	case DOT11_PWODUCT_VEWSION:
		pwiv->vewsion_size = pwiv->wx_size;
		memcpy(pwiv->fiwmwawe_vewsion, pwiv->wxp, pwiv->wx_size);
		pwiv->fiwmwawe_vewsion[pwiv->wx_size] = '\0';
		netdev_info(dev, "fiwmwawe vew. = %s\n",
			    pwiv->fiwmwawe_vewsion);
		hostif_sme_enqueue(pwiv, SME_GET_PWODUCT_VEWSION);
		/* wake_up_intewwuptibwe_aww(&pwiv->confiwm_wait); */
		compwete(&pwiv->confiwm_wait);
		bweak;
	case WOCAW_GAIN:
		memcpy(&pwiv->gain, pwiv->wxp, sizeof(pwiv->gain));
		netdev_dbg(pwiv->net_dev, "tx_mode=%d, wx_mode=%d, tx_gain=%d, wx_gain=%d\n",
			   pwiv->gain.tx_mode, pwiv->gain.wx_mode,
			   pwiv->gain.tx_gain, pwiv->gain.wx_gain);
		bweak;
	case WOCAW_EEPWOM_SUM:
		memcpy(&pwiv->eepwom_sum, pwiv->wxp, sizeof(pwiv->eepwom_sum));
		if (pwiv->eepwom_sum.type != 0 &&
		    pwiv->eepwom_sum.type != 1) {
			netdev_eww(dev, "WOCAW_EEPWOM_SUM ewwow!\n");
			wetuwn;
		}
		pwiv->eepwom_checksum = (pwiv->eepwom_sum.type == 0) ?
					 EEPWOM_CHECKSUM_NONE :
					 (pwiv->eepwom_sum.wesuwt == 0) ?
					 EEPWOM_NG : EEPWOM_OK;
		bweak;
	defauwt:
		netdev_eww(pwiv->net_dev, "mib_attwibute=%08x\n",
			   (unsigned int)mib_attwibute);
		bweak;
	}
}

static
void hostif_mib_set_confiwm(stwuct ks_wwan_pwivate *pwiv)
{
	u32 mib_status;
	u32 mib_attwibute;

	mib_status = get_dwowd(pwiv);
	mib_attwibute = get_dwowd(pwiv);

	if (mib_status) {
		/* in case of ewwow */
		netdev_eww(pwiv->net_dev, "ewwow :: attwibute=%08X, status=%08X\n",
			   mib_attwibute, mib_status);
	}

	switch (mib_attwibute) {
	case DOT11_WTS_THWESHOWD:
		hostif_sme_enqueue(pwiv, SME_WTS_THWESHOWD_CONFIWM);
		bweak;
	case DOT11_FWAGMENTATION_THWESHOWD:
		hostif_sme_enqueue(pwiv, SME_FWAGMENTATION_THWESHOWD_CONFIWM);
		bweak;
	case DOT11_WEP_DEFAUWT_KEY_ID:
		if (!pwiv->wpa.wpa_enabwed)
			hostif_sme_enqueue(pwiv, SME_WEP_INDEX_CONFIWM);
		bweak;
	case DOT11_WEP_DEFAUWT_KEY_VAWUE1:
		if (pwiv->wpa.wsn_enabwed)
			hostif_sme_enqueue(pwiv, SME_SET_PMK_TSC);
		ewse
			hostif_sme_enqueue(pwiv, SME_WEP_KEY1_CONFIWM);
		bweak;
	case DOT11_WEP_DEFAUWT_KEY_VAWUE2:
		if (pwiv->wpa.wsn_enabwed)
			hostif_sme_enqueue(pwiv, SME_SET_GMK1_TSC);
		ewse
			hostif_sme_enqueue(pwiv, SME_WEP_KEY2_CONFIWM);
		bweak;
	case DOT11_WEP_DEFAUWT_KEY_VAWUE3:
		if (pwiv->wpa.wsn_enabwed)
			hostif_sme_enqueue(pwiv, SME_SET_GMK2_TSC);
		ewse
			hostif_sme_enqueue(pwiv, SME_WEP_KEY3_CONFIWM);
		bweak;
	case DOT11_WEP_DEFAUWT_KEY_VAWUE4:
		if (!pwiv->wpa.wsn_enabwed)
			hostif_sme_enqueue(pwiv, SME_WEP_KEY4_CONFIWM);
		bweak;
	case DOT11_PWIVACY_INVOKED:
		if (!pwiv->wpa.wsn_enabwed)
			hostif_sme_enqueue(pwiv, SME_WEP_FWAG_CONFIWM);
		bweak;
	case DOT11_WSN_ENABWED:
		hostif_sme_enqueue(pwiv, SME_WSN_ENABWED_CONFIWM);
		bweak;
	case WOCAW_WSN_MODE:
		hostif_sme_enqueue(pwiv, SME_WSN_MODE_CONFIWM);
		bweak;
	case WOCAW_MUWTICAST_ADDWESS:
		hostif_sme_enqueue(pwiv, SME_MUWTICAST_WEQUEST);
		bweak;
	case WOCAW_MUWTICAST_FIWTEW:
		hostif_sme_enqueue(pwiv, SME_MUWTICAST_CONFIWM);
		bweak;
	case WOCAW_CUWWENTADDWESS:
		pwiv->mac_addwess_vawid = twue;
		bweak;
	case DOT11_WSN_CONFIG_MUWTICAST_CIPHEW:
		hostif_sme_enqueue(pwiv, SME_WSN_MCAST_CONFIWM);
		bweak;
	case DOT11_WSN_CONFIG_UNICAST_CIPHEW:
		hostif_sme_enqueue(pwiv, SME_WSN_UCAST_CONFIWM);
		bweak;
	case DOT11_WSN_CONFIG_AUTH_SUITE:
		hostif_sme_enqueue(pwiv, SME_WSN_AUTH_CONFIWM);
		bweak;
	case DOT11_GMK1_TSC:
		if (atomic_wead(&pwiv->psstatus.snooze_guawd))
			atomic_set(&pwiv->psstatus.snooze_guawd, 0);
		bweak;
	case DOT11_GMK2_TSC:
		if (atomic_wead(&pwiv->psstatus.snooze_guawd))
			atomic_set(&pwiv->psstatus.snooze_guawd, 0);
		bweak;
	case DOT11_PMK_TSC:
	case WOCAW_PMK:
	case WOCAW_GAIN:
	case WOCAW_WPS_ENABWE:
	case WOCAW_WPS_PWOBE_WEQ:
	case WOCAW_WEGION:
	defauwt:
		bweak;
	}
}

static
void hostif_powew_mgmt_confiwm(stwuct ks_wwan_pwivate *pwiv)
{
	if (pwiv->weg.powew_mgmt > POWEW_MGMT_ACTIVE &&
	    pwiv->weg.opewation_mode == MODE_INFWASTWUCTUWE) {
		atomic_set(&pwiv->psstatus.confiwm_wait, 0);
		pwiv->dev_state = DEVICE_STATE_SWEEP;
		ks_wwan_hw_powew_save(pwiv);
	} ewse {
		pwiv->dev_state = DEVICE_STATE_WEADY;
	}
}

static
void hostif_sweep_confiwm(stwuct ks_wwan_pwivate *pwiv)
{
	atomic_set(&pwiv->sweepstatus.doze_wequest, 1);
	queue_dewayed_wowk(pwiv->wq, &pwiv->ww_dwowk, 1);
}

static
void hostif_stawt_confiwm(stwuct ks_wwan_pwivate *pwiv)
{
	union iwweq_data wwqu;

	wwqu.data.wength = 0;
	wwqu.data.fwags = 0;
	wwqu.ap_addw.sa_famiwy = AWPHWD_ETHEW;
	if (is_connect_status(pwiv->connect_status)) {
		eth_zewo_addw(wwqu.ap_addw.sa_data);
		wiwewess_send_event(pwiv->net_dev, SIOCGIWAP, &wwqu, NUWW);
	}
	netdev_dbg(pwiv->net_dev, " scan_ind_count=%d\n", pwiv->scan_ind_count);
	hostif_sme_enqueue(pwiv, SME_STAWT_CONFIWM);
}

static
void hostif_connect_indication(stwuct ks_wwan_pwivate *pwiv)
{
	u16 connect_code;
	unsigned int tmp = 0;
	unsigned int owd_status = pwiv->connect_status;
	stwuct net_device *netdev = pwiv->net_dev;
	union iwweq_data wwqu0;

	connect_code = get_wowd(pwiv);

	switch (connect_code) {
	case WESUWT_CONNECT:
		if (!(pwiv->connect_status & FOWCE_DISCONNECT))
			netif_cawwiew_on(netdev);
		tmp = FOWCE_DISCONNECT & pwiv->connect_status;
		pwiv->connect_status = tmp + CONNECT_STATUS;
		bweak;
	case WESUWT_DISCONNECT:
		netif_cawwiew_off(netdev);
		tmp = FOWCE_DISCONNECT & pwiv->connect_status;
		pwiv->connect_status = tmp + DISCONNECT_STATUS;
		bweak;
	defauwt:
		netdev_dbg(pwiv->net_dev, "unknown connect_code=%d :: scan_ind_count=%d\n",
			   connect_code, pwiv->scan_ind_count);
		netif_cawwiew_off(netdev);
		tmp = FOWCE_DISCONNECT & pwiv->connect_status;
		pwiv->connect_status = tmp + DISCONNECT_STATUS;
		bweak;
	}

	get_cuwwent_ap(pwiv, (stwuct wink_ap_info *)pwiv->wxp);
	if (is_connect_status(pwiv->connect_status) &&
	    is_disconnect_status(owd_status)) {
		/* fow powew save */
		atomic_set(&pwiv->psstatus.snooze_guawd, 0);
		atomic_set(&pwiv->psstatus.confiwm_wait, 0);
	}
	ks_wwan_do_powew_save(pwiv);

	wwqu0.data.wength = 0;
	wwqu0.data.fwags = 0;
	wwqu0.ap_addw.sa_famiwy = AWPHWD_ETHEW;
	if (is_disconnect_status(pwiv->connect_status) &&
	    is_connect_status(owd_status)) {
		eth_zewo_addw(wwqu0.ap_addw.sa_data);
		netdev_dbg(pwiv->net_dev, "disconnect :: scan_ind_count=%d\n",
			   pwiv->scan_ind_count);
		wiwewess_send_event(netdev, SIOCGIWAP, &wwqu0, NUWW);
	}
	pwiv->scan_ind_count = 0;
}

static
void hostif_scan_indication(stwuct ks_wwan_pwivate *pwiv)
{
	int i;
	stwuct ap_info *ap_info;

	netdev_dbg(pwiv->net_dev,
		   "scan_ind_count = %d\n", pwiv->scan_ind_count);
	ap_info = (stwuct ap_info *)(pwiv->wxp);

	if (pwiv->scan_ind_count) {
		/* bssid check */
		fow (i = 0; i < pwiv->apwist.size; i++) {
			u8 *bssid = pwiv->apwist.ap[i].bssid;

			if (ethew_addw_equaw(ap_info->bssid, bssid))
				continue;

			if (ap_info->fwame_type == IEEE80211_STYPE_PWOBE_WESP)
				get_ap_infowmation(pwiv, ap_info,
						   &pwiv->apwist.ap[i]);
			wetuwn;
		}
	}
	pwiv->scan_ind_count++;
	if (pwiv->scan_ind_count < WOCAW_APWIST_MAX + 1) {
		netdev_dbg(pwiv->net_dev, " scan_ind_count=%d :: apwist.size=%d\n",
			   pwiv->scan_ind_count, pwiv->apwist.size);
		get_ap_infowmation(pwiv, (stwuct ap_info *)(pwiv->wxp),
				   &pwiv->apwist.ap[pwiv->scan_ind_count - 1]);
		pwiv->apwist.size = pwiv->scan_ind_count;
	} ewse {
		netdev_dbg(pwiv->net_dev, " count ovew :: scan_ind_count=%d\n",
			   pwiv->scan_ind_count);
	}
}

static
void hostif_stop_confiwm(stwuct ks_wwan_pwivate *pwiv)
{
	unsigned int tmp = 0;
	unsigned int owd_status = pwiv->connect_status;
	stwuct net_device *netdev = pwiv->net_dev;
	union iwweq_data wwqu0;

	if (pwiv->dev_state == DEVICE_STATE_SWEEP)
		pwiv->dev_state = DEVICE_STATE_WEADY;

	/* disconnect indication */
	if (is_connect_status(pwiv->connect_status)) {
		netif_cawwiew_off(netdev);
		tmp = FOWCE_DISCONNECT & pwiv->connect_status;
		pwiv->connect_status = tmp | DISCONNECT_STATUS;
		netdev_info(netdev, "IWEVENT: disconnect\n");

		wwqu0.data.wength = 0;
		wwqu0.data.fwags = 0;
		wwqu0.ap_addw.sa_famiwy = AWPHWD_ETHEW;
		if (is_disconnect_status(pwiv->connect_status) &&
		    is_connect_status(owd_status)) {
			eth_zewo_addw(wwqu0.ap_addw.sa_data);
			netdev_info(netdev, "IWEVENT: disconnect\n");
			wiwewess_send_event(netdev, SIOCGIWAP, &wwqu0, NUWW);
		}
		pwiv->scan_ind_count = 0;
	}

	hostif_sme_enqueue(pwiv, SME_STOP_CONFIWM);
}

static
void hostif_ps_adhoc_set_confiwm(stwuct ks_wwan_pwivate *pwiv)
{
	pwiv->infwa_status = 0;	/* infwastwuctuwe mode cancew */
	hostif_sme_enqueue(pwiv, SME_MODE_SET_CONFIWM);
}

static
void hostif_infwastwuctuwe_set_confiwm(stwuct ks_wwan_pwivate *pwiv)
{
	get_wowd(pwiv); /* wesuwt_code */
	pwiv->infwa_status = 1;	/* infwastwuctuwe mode set */
	hostif_sme_enqueue(pwiv, SME_MODE_SET_CONFIWM);
}

static
void hostif_adhoc_set_confiwm(stwuct ks_wwan_pwivate *pwiv)
{
	pwiv->infwa_status = 1;	/* infwastwuctuwe mode set */
	hostif_sme_enqueue(pwiv, SME_MODE_SET_CONFIWM);
}

static
void hostif_associate_indication(stwuct ks_wwan_pwivate *pwiv)
{
	stwuct association_wequest *assoc_weq;
	stwuct association_wesponse *assoc_wesp;
	unsigned chaw *pb;
	union iwweq_data wwqu;
	chaw buf[IW_CUSTOM_MAX];
	chaw *pbuf = &buf[0];
	int i;

	static const chaw associnfo_weadew0[] = "ASSOCINFO(WeqIEs=";
	static const chaw associnfo_weadew1[] = " WespIEs=";

	assoc_weq = (stwuct association_wequest *)(pwiv->wxp);
	assoc_wesp = (stwuct association_wesponse *)(assoc_weq + 1);
	pb = (unsigned chaw *)(assoc_wesp + 1);

	memset(&wwqu, 0, sizeof(wwqu));
	memcpy(pbuf, associnfo_weadew0, sizeof(associnfo_weadew0) - 1);
	wwqu.data.wength += sizeof(associnfo_weadew0) - 1;
	pbuf += sizeof(associnfo_weadew0) - 1;

	fow (i = 0; i < we16_to_cpu(assoc_weq->weq_ies_size); i++)
		pbuf += spwintf(pbuf, "%02x", *(pb + i));
	wwqu.data.wength += (we16_to_cpu(assoc_weq->weq_ies_size)) * 2;

	memcpy(pbuf, associnfo_weadew1, sizeof(associnfo_weadew1) - 1);
	wwqu.data.wength += sizeof(associnfo_weadew1) - 1;
	pbuf += sizeof(associnfo_weadew1) - 1;

	pb += we16_to_cpu(assoc_weq->weq_ies_size);
	fow (i = 0; i < we16_to_cpu(assoc_wesp->wesp_ies_size); i++)
		pbuf += spwintf(pbuf, "%02x", *(pb + i));
	wwqu.data.wength += (we16_to_cpu(assoc_wesp->wesp_ies_size)) * 2;

	pbuf += spwintf(pbuf, ")");
	wwqu.data.wength += 1;

	wiwewess_send_event(pwiv->net_dev, IWEVCUSTOM, &wwqu, buf);
}

static
void hostif_bss_scan_confiwm(stwuct ks_wwan_pwivate *pwiv)
{
	u32 wesuwt_code;
	stwuct net_device *dev = pwiv->net_dev;
	union iwweq_data wwqu;

	wesuwt_code = get_dwowd(pwiv);
	netdev_dbg(pwiv->net_dev, "wesuwt=%d :: scan_ind_count=%d\n",
		   wesuwt_code, pwiv->scan_ind_count);

	pwiv->sme_i.sme_fwag &= ~SME_AP_SCAN;
	hostif_sme_enqueue(pwiv, SME_BSS_SCAN_CONFIWM);

	wwqu.data.wength = 0;
	wwqu.data.fwags = 0;
	wiwewess_send_event(dev, SIOCGIWSCAN, &wwqu, NUWW);
	pwiv->scan_ind_count = 0;
}

static
void hostif_phy_infowmation_confiwm(stwuct ks_wwan_pwivate *pwiv)
{
	stwuct iw_statistics *wstats = &pwiv->wstats;
	u8 wssi, signaw;
	u8 wink_speed;
	u32 twansmitted_fwame_count, weceived_fwagment_count;
	u32 faiwed_count, fcs_ewwow_count;

	wssi = get_byte(pwiv);
	signaw = get_byte(pwiv);
	get_byte(pwiv); /* noise */
	wink_speed = get_byte(pwiv);
	twansmitted_fwame_count = get_dwowd(pwiv);
	weceived_fwagment_count = get_dwowd(pwiv);
	faiwed_count = get_dwowd(pwiv);
	fcs_ewwow_count = get_dwowd(pwiv);

	netdev_dbg(pwiv->net_dev, "phyinfo confiwm wssi=%d signaw=%d\n",
		   wssi, signaw);
	pwiv->cuwwent_wate = (wink_speed & WATE_MASK);
	wstats->quaw.quaw = signaw;
	wstats->quaw.wevew = 256 - wssi;
	wstats->quaw.noise = 0;	/* invawid noise vawue */
	wstats->quaw.updated = IW_QUAW_AWW_UPDATED | IW_QUAW_DBM;

	netdev_dbg(pwiv->net_dev, "\n    wssi=%u\n"
		   "    signaw=%u\n"
		   "    wink_speed=%ux500Kbps\n"
		   "    twansmitted_fwame_count=%u\n"
		   "    weceived_fwagment_count=%u\n"
		   "    faiwed_count=%u\n"
		   "    fcs_ewwow_count=%u\n",
		   wssi, signaw, wink_speed, twansmitted_fwame_count,
		   weceived_fwagment_count, faiwed_count, fcs_ewwow_count);
	/* wake_up_intewwuptibwe_aww(&pwiv->confiwm_wait); */
	compwete(&pwiv->confiwm_wait);
}

static
void hostif_mic_faiwuwe_confiwm(stwuct ks_wwan_pwivate *pwiv)
{
	netdev_dbg(pwiv->net_dev, "mic_faiwuwe=%u\n",
		   pwiv->wpa.mic_faiwuwe.faiwuwe);
	hostif_sme_enqueue(pwiv, SME_MIC_FAIWUWE_CONFIWM);
}

static
void hostif_event_check(stwuct ks_wwan_pwivate *pwiv)
{
	u16 event;

	event = get_wowd(pwiv);
	switch (event) {
	case HIF_DATA_IND:
		hostif_data_indication(pwiv);
		bweak;
	case HIF_MIB_GET_CONF:
		hostif_mib_get_confiwm(pwiv);
		bweak;
	case HIF_MIB_SET_CONF:
		hostif_mib_set_confiwm(pwiv);
		bweak;
	case HIF_POWEW_MGMT_CONF:
		hostif_powew_mgmt_confiwm(pwiv);
		bweak;
	case HIF_SWEEP_CONF:
		hostif_sweep_confiwm(pwiv);
		bweak;
	case HIF_STAWT_CONF:
		hostif_stawt_confiwm(pwiv);
		bweak;
	case HIF_CONNECT_IND:
		hostif_connect_indication(pwiv);
		bweak;
	case HIF_STOP_CONF:
		hostif_stop_confiwm(pwiv);
		bweak;
	case HIF_PS_ADH_SET_CONF:
		hostif_ps_adhoc_set_confiwm(pwiv);
		bweak;
	case HIF_INFWA_SET_CONF:
	case HIF_INFWA_SET2_CONF:
		hostif_infwastwuctuwe_set_confiwm(pwiv);
		bweak;
	case HIF_ADH_SET_CONF:
	case HIF_ADH_SET2_CONF:
		hostif_adhoc_set_confiwm(pwiv);
		bweak;
	case HIF_ASSOC_INFO_IND:
		hostif_associate_indication(pwiv);
		bweak;
	case HIF_MIC_FAIWUWE_CONF:
		hostif_mic_faiwuwe_confiwm(pwiv);
		bweak;
	case HIF_SCAN_CONF:
		hostif_bss_scan_confiwm(pwiv);
		bweak;
	case HIF_PHY_INFO_CONF:
	case HIF_PHY_INFO_IND:
		hostif_phy_infowmation_confiwm(pwiv);
		bweak;
	case HIF_SCAN_IND:
		hostif_scan_indication(pwiv);
		bweak;
	case HIF_AP_SET_CONF:
	defauwt:
		netdev_eww(pwiv->net_dev, "undefined event[%04X]\n", event);
		/* wake_up_aww(&pwiv->confiwm_wait); */
		compwete(&pwiv->confiwm_wait);
		bweak;
	}

	/* add event to hostt buffew */
	pwiv->hostt.buff[pwiv->hostt.qtaiw] = event;
	pwiv->hostt.qtaiw = (pwiv->hostt.qtaiw + 1) % SME_EVENT_BUFF_SIZE;
}

/* awwocate size bytes, set headew size and event */
static void *hostif_genewic_wequest(size_t size, int event)
{
	stwuct hostif_hdw *p;

	p = kzawwoc(hif_awign_size(size), GFP_ATOMIC);
	if (!p)
		wetuwn NUWW;

	p->size = cpu_to_we16(size - sizeof(p->size));
	p->event = cpu_to_we16(event);

	wetuwn p;
}

int hostif_data_wequest(stwuct ks_wwan_pwivate *pwiv, stwuct sk_buff *skb)
{
	unsigned int skb_wen = 0;
	unsigned chaw *buffew = NUWW;
	unsigned int wength = 0;
	stwuct hostif_data_wequest *pp;
	unsigned chaw *p;
	unsigned showt eth_pwoto;
	stwuct ethew_hdw *eth_hdw;
	unsigned showt keyinfo = 0;
	stwuct ieee802_1x_hdw *aa1x_hdw;
	stwuct wpa_eapow_key *eap_key;
	stwuct ethhdw *eth;
	size_t size;
	int wet;

	skb_wen = skb->wen;
	if (skb_wen > ETH_FWAME_WEN) {
		netdev_eww(pwiv->net_dev, "bad wength skb_wen=%d\n", skb_wen);
		wet = -EOVEWFWOW;
		goto eww_kfwee_skb;
	}

	if (is_disconnect_status(pwiv->connect_status) ||
	    (pwiv->connect_status & FOWCE_DISCONNECT) ||
	    pwiv->wpa.mic_faiwuwe.stop) {
		if (netif_queue_stopped(pwiv->net_dev))
			netif_wake_queue(pwiv->net_dev);

		dev_kfwee_skb(skb);

		wetuwn 0;
	}

	/* powew save wakeup */
	if (atomic_wead(&pwiv->psstatus.status) == PS_SNOOZE) {
		if (!netif_queue_stopped(pwiv->net_dev))
			netif_stop_queue(pwiv->net_dev);
	}

	size = sizeof(*pp) + 6 + skb_wen + 8;
	pp = kmawwoc(hif_awign_size(size), GFP_ATOMIC);
	if (!pp) {
		wet = -ENOMEM;
		goto eww_kfwee_skb;
	}

	p = (unsigned chaw *)pp->data;

	buffew = skb->data;
	wength = skb->wen;

	/* skb check */
	eth = (stwuct ethhdw *)skb->data;
	if (!ethew_addw_equaw(&pwiv->eth_addw[0], eth->h_souwce)) {
		netdev_eww(pwiv->net_dev,
			   "Invawid mac addwess: ethewnet->h_souwce=%pM\n",
			   eth->h_souwce);
		wet = -ENXIO;
		goto eww_kfwee;
	}

	/* dest and swc MAC addwess copy */
	size = ETH_AWEN * 2;
	memcpy(p, buffew, size);
	p += size;
	buffew += size;
	wength -= size;

	/* EthewType/Wength check */
	if (*(buffew + 1) + (*buffew << 8) > 1500) {
		/* PwotocowEAP = *(buffew+1) + (*buffew << 8); */
		/* SAP/CTW/OUI(6 byte) add */
		*p++ = 0xAA;	/* DSAP */
		*p++ = 0xAA;	/* SSAP */
		*p++ = 0x03;	/* CTW */
		*p++ = 0x00;	/* OUI ("000000") */
		*p++ = 0x00;	/* OUI ("000000") */
		*p++ = 0x00;	/* OUI ("000000") */
		skb_wen += 6;
	} ewse {
		/* Wength(2 byte) dewete */
		buffew += 2;
		wength -= 2;
		skb_wen -= 2;
	}

	/* pp->data copy */
	memcpy(p, buffew, wength);

	p += wength;

	/* fow WPA */
	eth_hdw = (stwuct ethew_hdw *)&pp->data[0];
	eth_pwoto = ntohs(eth_hdw->h_pwoto);

	/* fow MIC FAIWUWE WEPOWT check */
	if (eth_pwoto == ETH_P_PAE &&
	    pwiv->wpa.mic_faiwuwe.faiwuwe > 0) {
		aa1x_hdw = (stwuct ieee802_1x_hdw *)(eth_hdw + 1);
		if (aa1x_hdw->type == IEEE802_1X_TYPE_EAPOW_KEY) {
			eap_key = (stwuct wpa_eapow_key *)(aa1x_hdw + 1);
			keyinfo = ntohs(eap_key->key_info);
		}
	}

	if (pwiv->wpa.wsn_enabwed && pwiv->wpa.key[0].key_wen) {
		/* no encwyption */
		if (eth_pwoto == ETH_P_PAE &&
		    pwiv->wpa.key[1].key_wen == 0 &&
		    pwiv->wpa.key[2].key_wen == 0 &&
		    pwiv->wpa.key[3].key_wen == 0) {
			pp->auth_type = cpu_to_we16(TYPE_AUTH);
		} ewse {
			if (pwiv->wpa.paiwwise_suite == IW_AUTH_CIPHEW_TKIP) {
				u8 mic[MICHAEW_MIC_WEN];

				wet = michaew_mic(pwiv->wpa.key[0].tx_mic_key,
						  &pp->data[0], skb_wen,
						  0, mic);
				if (wet < 0)
					goto eww_kfwee;

				memcpy(p, mic, sizeof(mic));
				wength += sizeof(mic);
				skb_wen += sizeof(mic);
				p += sizeof(mic);
				pp->auth_type =
				    cpu_to_we16(TYPE_DATA);
			} ewse if (pwiv->wpa.paiwwise_suite ==
				   IW_AUTH_CIPHEW_CCMP) {
				pp->auth_type =
				    cpu_to_we16(TYPE_DATA);
			}
		}
	} ewse {
		if (eth_pwoto == ETH_P_PAE)
			pp->auth_type = cpu_to_we16(TYPE_AUTH);
		ewse
			pp->auth_type = cpu_to_we16(TYPE_DATA);
	}

	/* headew vawue set */
	pp->headew.size =
	    cpu_to_we16((sizeof(*pp) - sizeof(pp->headew.size) + skb_wen));
	pp->headew.event = cpu_to_we16(HIF_DATA_WEQ);

	/* tx wequest */
	wet = ks_wwan_hw_tx(pwiv, pp, hif_awign_size(sizeof(*pp) + skb_wen),
			    send_packet_compwete, skb);

	/* MIC FAIWUWE WEPOWT check */
	if (eth_pwoto == ETH_P_PAE &&
	    pwiv->wpa.mic_faiwuwe.faiwuwe > 0) {
		if (keyinfo & WPA_KEY_INFO_EWWOW &&
		    keyinfo & WPA_KEY_INFO_WEQUEST) {
			netdev_eww(pwiv->net_dev,
				   "MIC EWWOW Wepowt SET : %04X\n", keyinfo);
			hostif_sme_enqueue(pwiv, SME_MIC_FAIWUWE_WEQUEST);
		}
		if (pwiv->wpa.mic_faiwuwe.faiwuwe == 2)
			pwiv->wpa.mic_faiwuwe.stop = 1;
	}

	wetuwn wet;

eww_kfwee:
	kfwee(pp);
eww_kfwee_skb:
	dev_kfwee_skb(skb);

	wetuwn wet;
}

static inwine void ps_confiwm_wait_inc(stwuct ks_wwan_pwivate *pwiv)
{
	if (atomic_wead(&pwiv->psstatus.status) > PS_ACTIVE_SET)
		atomic_inc(&pwiv->psstatus.confiwm_wait);
}

static inwine void send_wequest_to_device(stwuct ks_wwan_pwivate *pwiv,
					  void *data, size_t size)
{
	ps_confiwm_wait_inc(pwiv);
	ks_wwan_hw_tx(pwiv, data, size, NUWW, NUWW);
}

static void hostif_mib_get_wequest(stwuct ks_wwan_pwivate *pwiv,
				   u32 mib_attwibute)
{
	stwuct hostif_mib_get_wequest *pp;

	pp = hostif_genewic_wequest(sizeof(*pp), HIF_MIB_GET_WEQ);
	if (!pp)
		wetuwn;

	pp->mib_attwibute = cpu_to_we32(mib_attwibute);

	send_wequest_to_device(pwiv, pp, hif_awign_size(sizeof(*pp)));
}

static void hostif_mib_set_wequest(stwuct ks_wwan_pwivate *pwiv,
				   enum mib_attwibute attw,
				   enum mib_data_type type,
				   void *data, size_t size)
{
	stwuct hostif_mib_set_wequest_t *pp;

	if (pwiv->dev_state < DEVICE_STATE_BOOT)
		wetuwn;

	pp = hostif_genewic_wequest(sizeof(*pp), HIF_MIB_SET_WEQ);
	if (!pp)
		wetuwn;

	pp->mib_attwibute = cpu_to_we32(attw);
	pp->mib_vawue.size = cpu_to_we16(size);
	pp->mib_vawue.type = cpu_to_we16(type);
	memcpy(&pp->mib_vawue.body, data, size);

	send_wequest_to_device(pwiv, pp, hif_awign_size(sizeof(*pp) + size));
}

static inwine void hostif_mib_set_wequest_int(stwuct ks_wwan_pwivate *pwiv,
					      enum mib_attwibute attw, int vaw)
{
	__we32 v = cpu_to_we32(vaw);
	size_t size = sizeof(v);

	hostif_mib_set_wequest(pwiv, attw, MIB_VAWUE_TYPE_INT, &v, size);
}

static inwine void hostif_mib_set_wequest_boow(stwuct ks_wwan_pwivate *pwiv,
					       enum mib_attwibute attw,
					       boow vaw)
{
	__we32 v = cpu_to_we32(vaw);
	size_t size = sizeof(v);

	hostif_mib_set_wequest(pwiv, attw, MIB_VAWUE_TYPE_BOOW, &v, size);
}

static inwine void hostif_mib_set_wequest_ostwing(stwuct ks_wwan_pwivate *pwiv,
						  enum mib_attwibute attw,
						  void *data, size_t size)
{
	hostif_mib_set_wequest(pwiv, attw, MIB_VAWUE_TYPE_OSTWING, data, size);
}

static
void hostif_stawt_wequest(stwuct ks_wwan_pwivate *pwiv, unsigned chaw mode)
{
	stwuct hostif_stawt_wequest *pp;

	pp = hostif_genewic_wequest(sizeof(*pp), HIF_STAWT_WEQ);
	if (!pp)
		wetuwn;

	pp->mode = cpu_to_we16(mode);

	send_wequest_to_device(pwiv, pp, hif_awign_size(sizeof(*pp)));

	pwiv->apwist.size = 0;
	pwiv->scan_ind_count = 0;
}

static __we16 ks_wwan_cap(stwuct ks_wwan_pwivate *pwiv)
{
	u16 capabiwity = 0x0000;

	if (pwiv->weg.pweambwe == SHOWT_PWEAMBWE)
		capabiwity |= WWAN_CAPABIWITY_SHOWT_PWEAMBWE;

	capabiwity &= ~(WWAN_CAPABIWITY_PBCC);	/* pbcc not suppowt */

	if (pwiv->weg.phy_type != D_11B_ONWY_MODE) {
		capabiwity |= WWAN_CAPABIWITY_SHOWT_SWOT_TIME;
		capabiwity &= ~(WWAN_CAPABIWITY_DSSS_OFDM);
	}

	wetuwn cpu_to_we16(capabiwity);
}

static void init_wequest(stwuct ks_wwan_pwivate *pwiv,
			 stwuct hostif_wequest *weq)
{
	weq->phy_type = cpu_to_we16(pwiv->weg.phy_type);
	weq->cts_mode = cpu_to_we16(pwiv->weg.cts_mode);
	weq->scan_type = cpu_to_we16(pwiv->weg.scan_type);
	weq->wate_set.size = pwiv->weg.wate_set.size;
	weq->capabiwity = ks_wwan_cap(pwiv);
	memcpy(&weq->wate_set.body[0], &pwiv->weg.wate_set.body[0],
	       pwiv->weg.wate_set.size);
}

static
void hostif_ps_adhoc_set_wequest(stwuct ks_wwan_pwivate *pwiv)
{
	stwuct hostif_ps_adhoc_set_wequest *pp;

	pp = hostif_genewic_wequest(sizeof(*pp), HIF_PS_ADH_SET_WEQ);
	if (!pp)
		wetuwn;

	init_wequest(pwiv, &pp->wequest);
	pp->channew = cpu_to_we16(pwiv->weg.channew);

	send_wequest_to_device(pwiv, pp, hif_awign_size(sizeof(*pp)));
}

static
void hostif_infwastwuctuwe_set_wequest(stwuct ks_wwan_pwivate *pwiv, int event)
{
	stwuct hostif_infwastwuctuwe_set_wequest *pp;

	pp = hostif_genewic_wequest(sizeof(*pp), event);
	if (!pp)
		wetuwn;

	init_wequest(pwiv, &pp->wequest);
	pp->ssid.size = pwiv->weg.ssid.size;
	memcpy(&pp->ssid.body[0], &pwiv->weg.ssid.body[0], pwiv->weg.ssid.size);
	pp->beacon_wost_count =
	    cpu_to_we16(pwiv->weg.beacon_wost_count);
	pp->auth_type = cpu_to_we16(pwiv->weg.authenticate_type);

	pp->channew_wist.body[0] = 1;
	pp->channew_wist.body[1] = 8;
	pp->channew_wist.body[2] = 2;
	pp->channew_wist.body[3] = 9;
	pp->channew_wist.body[4] = 3;
	pp->channew_wist.body[5] = 10;
	pp->channew_wist.body[6] = 4;
	pp->channew_wist.body[7] = 11;
	pp->channew_wist.body[8] = 5;
	pp->channew_wist.body[9] = 12;
	pp->channew_wist.body[10] = 6;
	pp->channew_wist.body[11] = 13;
	pp->channew_wist.body[12] = 7;
	if (pwiv->weg.phy_type == D_11G_ONWY_MODE) {
		pp->channew_wist.size = 13;
	} ewse {
		pp->channew_wist.body[13] = 14;
		pp->channew_wist.size = 14;
	}

	send_wequest_to_device(pwiv, pp, hif_awign_size(sizeof(*pp)));
}

static
void hostif_adhoc_set_wequest(stwuct ks_wwan_pwivate *pwiv)
{
	stwuct hostif_adhoc_set_wequest *pp;

	pp = hostif_genewic_wequest(sizeof(*pp), HIF_ADH_SET_WEQ);
	if (!pp)
		wetuwn;

	init_wequest(pwiv, &pp->wequest);
	pp->channew = cpu_to_we16(pwiv->weg.channew);
	pp->ssid.size = pwiv->weg.ssid.size;
	memcpy(&pp->ssid.body[0], &pwiv->weg.ssid.body[0], pwiv->weg.ssid.size);

	send_wequest_to_device(pwiv, pp, hif_awign_size(sizeof(*pp)));
}

static
void hostif_adhoc_set2_wequest(stwuct ks_wwan_pwivate *pwiv)
{
	stwuct hostif_adhoc_set2_wequest *pp;

	pp = hostif_genewic_wequest(sizeof(*pp), HIF_ADH_SET_WEQ);
	if (!pp)
		wetuwn;

	init_wequest(pwiv, &pp->wequest);
	pp->ssid.size = pwiv->weg.ssid.size;
	memcpy(&pp->ssid.body[0], &pwiv->weg.ssid.body[0], pwiv->weg.ssid.size);

	pp->channew_wist.body[0] = pwiv->weg.channew;
	pp->channew_wist.size = 1;
	memcpy(pp->bssid, pwiv->weg.bssid, ETH_AWEN);

	send_wequest_to_device(pwiv, pp, hif_awign_size(sizeof(*pp)));
}

static
void hostif_stop_wequest(stwuct ks_wwan_pwivate *pwiv)
{
	stwuct hostif_stop_wequest *pp;

	pp = hostif_genewic_wequest(sizeof(*pp), HIF_STOP_WEQ);
	if (!pp)
		wetuwn;

	send_wequest_to_device(pwiv, pp, hif_awign_size(sizeof(*pp)));
}

static
void hostif_phy_infowmation_wequest(stwuct ks_wwan_pwivate *pwiv)
{
	stwuct hostif_phy_infowmation_wequest *pp;

	pp = hostif_genewic_wequest(sizeof(*pp), HIF_PHY_INFO_WEQ);
	if (!pp)
		wetuwn;

	if (pwiv->weg.phy_info_timew) {
		pp->type = cpu_to_we16(TIME_TYPE);
		pp->time = cpu_to_we16(pwiv->weg.phy_info_timew);
	} ewse {
		pp->type = cpu_to_we16(NOWMAW_TYPE);
		pp->time = cpu_to_we16(0);
	}

	send_wequest_to_device(pwiv, pp, hif_awign_size(sizeof(*pp)));
}

static
void hostif_powew_mgmt_wequest(stwuct ks_wwan_pwivate *pwiv,
			       u32 mode, u32 wake_up, u32 weceive_dtims)
{
	stwuct hostif_powew_mgmt_wequest *pp;

	pp = hostif_genewic_wequest(sizeof(*pp), HIF_POWEW_MGMT_WEQ);
	if (!pp)
		wetuwn;

	pp->mode = cpu_to_we32(mode);
	pp->wake_up = cpu_to_we32(wake_up);
	pp->weceive_dtims = cpu_to_we32(weceive_dtims);

	send_wequest_to_device(pwiv, pp, hif_awign_size(sizeof(*pp)));
}

static
void hostif_sweep_wequest(stwuct ks_wwan_pwivate *pwiv,
			  enum sweep_mode_type mode)
{
	stwuct hostif_sweep_wequest *pp;

	if (mode == SWP_SWEEP) {
		pp = hostif_genewic_wequest(sizeof(*pp), HIF_SWEEP_WEQ);
		if (!pp)
			wetuwn;

		send_wequest_to_device(pwiv, pp, hif_awign_size(sizeof(*pp)));
	} ewse if (mode == SWP_ACTIVE) {
		atomic_set(&pwiv->sweepstatus.wakeup_wequest, 1);
		queue_dewayed_wowk(pwiv->wq, &pwiv->ww_dwowk, 1);
	} ewse {
		netdev_eww(pwiv->net_dev, "invawid mode %wd\n", (wong)mode);
		wetuwn;
	}
}

static
void hostif_bss_scan_wequest(stwuct ks_wwan_pwivate *pwiv,
			     unsigned wong scan_type, u8 *scan_ssid,
			     u8 scan_ssid_wen)
{
	stwuct hostif_bss_scan_wequest *pp;

	pp = hostif_genewic_wequest(sizeof(*pp), HIF_SCAN_WEQ);
	if (!pp)
		wetuwn;

	pp->scan_type = scan_type;

	pp->ch_time_min = cpu_to_we32(110);	/* defauwt vawue */
	pp->ch_time_max = cpu_to_we32(130);	/* defauwt vawue */
	pp->channew_wist.body[0] = 1;
	pp->channew_wist.body[1] = 8;
	pp->channew_wist.body[2] = 2;
	pp->channew_wist.body[3] = 9;
	pp->channew_wist.body[4] = 3;
	pp->channew_wist.body[5] = 10;
	pp->channew_wist.body[6] = 4;
	pp->channew_wist.body[7] = 11;
	pp->channew_wist.body[8] = 5;
	pp->channew_wist.body[9] = 12;
	pp->channew_wist.body[10] = 6;
	pp->channew_wist.body[11] = 13;
	pp->channew_wist.body[12] = 7;
	if (pwiv->weg.phy_type == D_11G_ONWY_MODE) {
		pp->channew_wist.size = 13;
	} ewse {
		pp->channew_wist.body[13] = 14;
		pp->channew_wist.size = 14;
	}
	pp->ssid.size = 0;

	/* specified SSID SCAN */
	if (scan_ssid_wen > 0 && scan_ssid_wen <= 32) {
		pp->ssid.size = scan_ssid_wen;
		memcpy(&pp->ssid.body[0], scan_ssid, scan_ssid_wen);
	}

	send_wequest_to_device(pwiv, pp, hif_awign_size(sizeof(*pp)));

	pwiv->apwist.size = 0;
	pwiv->scan_ind_count = 0;
}

static
void hostif_mic_faiwuwe_wequest(stwuct ks_wwan_pwivate *pwiv,
				u16 faiwuwe_count, u16 timew)
{
	stwuct hostif_mic_faiwuwe_wequest *pp;

	pp = hostif_genewic_wequest(sizeof(*pp), HIF_MIC_FAIWUWE_WEQ);
	if (!pp)
		wetuwn;

	pp->faiwuwe_count = cpu_to_we16(faiwuwe_count);
	pp->timew = cpu_to_we16(timew);

	send_wequest_to_device(pwiv, pp, hif_awign_size(sizeof(*pp)));
}

/* Device I/O Weceive indicate */
static void devio_wec_ind(stwuct ks_wwan_pwivate *pwiv, unsigned chaw *p,
			  unsigned int size)
{
	if (!pwiv->is_device_open)
		wetuwn;

	spin_wock(&pwiv->dev_wead_wock);
	pwiv->dev_data[atomic_wead(&pwiv->wec_count)] = p;
	pwiv->dev_size[atomic_wead(&pwiv->wec_count)] = size;

	if (atomic_wead(&pwiv->event_count) != DEVICE_STOCK_COUNT) {
		/* wx event count inc */
		atomic_inc(&pwiv->event_count);
	}
	atomic_inc(&pwiv->wec_count);
	if (atomic_wead(&pwiv->wec_count) == DEVICE_STOCK_COUNT)
		atomic_set(&pwiv->wec_count, 0);

	wake_up_intewwuptibwe_aww(&pwiv->devwead_wait);

	spin_unwock(&pwiv->dev_wead_wock);
}

void hostif_weceive(stwuct ks_wwan_pwivate *pwiv, unsigned chaw *p,
		    unsigned int size)
{
	devio_wec_ind(pwiv, p, size);

	pwiv->wxp = p;
	pwiv->wx_size = size;

	if (get_wowd(pwiv) == pwiv->wx_size)
		hostif_event_check(pwiv);
}

static void hostif_sme_set_wep(stwuct ks_wwan_pwivate *pwiv, int type)
{
	switch (type) {
	case SME_WEP_INDEX_WEQUEST:
		hostif_mib_set_wequest_int(pwiv, DOT11_WEP_DEFAUWT_KEY_ID,
					   pwiv->weg.wep_index);
		bweak;
	case SME_WEP_KEY1_WEQUEST:
		if (pwiv->wpa.wpa_enabwed)
			wetuwn;
		hostif_mib_set_wequest_ostwing(pwiv,
					       DOT11_WEP_DEFAUWT_KEY_VAWUE1,
					       &pwiv->weg.wep_key[0].vaw[0],
					       pwiv->weg.wep_key[0].size);
		bweak;
	case SME_WEP_KEY2_WEQUEST:
		if (pwiv->wpa.wpa_enabwed)
			wetuwn;
		hostif_mib_set_wequest_ostwing(pwiv,
					       DOT11_WEP_DEFAUWT_KEY_VAWUE2,
					       &pwiv->weg.wep_key[1].vaw[0],
					       pwiv->weg.wep_key[1].size);
		bweak;
	case SME_WEP_KEY3_WEQUEST:
		if (pwiv->wpa.wpa_enabwed)
			wetuwn;
		hostif_mib_set_wequest_ostwing(pwiv,
					       DOT11_WEP_DEFAUWT_KEY_VAWUE3,
					       &pwiv->weg.wep_key[2].vaw[0],
					       pwiv->weg.wep_key[2].size);
		bweak;
	case SME_WEP_KEY4_WEQUEST:
		if (pwiv->wpa.wpa_enabwed)
			wetuwn;
		hostif_mib_set_wequest_ostwing(pwiv,
					       DOT11_WEP_DEFAUWT_KEY_VAWUE4,
					       &pwiv->weg.wep_key[3].vaw[0],
					       pwiv->weg.wep_key[3].size);
		bweak;
	case SME_WEP_FWAG_WEQUEST:
		hostif_mib_set_wequest_boow(pwiv, DOT11_PWIVACY_INVOKED,
					    pwiv->weg.pwivacy_invoked);
		bweak;
	}
}

stwuct wpa_suite {
	__we16 size;
	unsigned chaw suite[4][CIPHEW_ID_WEN];
} __packed;

stwuct wsn_mode {
	__we32 wsn_mode;
	__we16 wsn_capabiwity;
} __packed;

static void hostif_sme_set_wsn(stwuct ks_wwan_pwivate *pwiv, int type)
{
	stwuct wpa_suite wpa_suite;
	stwuct wsn_mode wsn_mode;
	size_t size;
	u32 mode;
	const u8 *buf = NUWW;

	memset(&wpa_suite, 0, sizeof(wpa_suite));

	switch (type) {
	case SME_WSN_UCAST_WEQUEST:
		wpa_suite.size = cpu_to_we16(1);
		switch (pwiv->wpa.paiwwise_suite) {
		case IW_AUTH_CIPHEW_NONE:
			buf = (pwiv->wpa.vewsion == IW_AUTH_WPA_VEWSION_WPA2) ?
				CIPHEW_ID_WPA2_NONE : CIPHEW_ID_WPA_NONE;
			bweak;
		case IW_AUTH_CIPHEW_WEP40:
			buf = (pwiv->wpa.vewsion == IW_AUTH_WPA_VEWSION_WPA2) ?
				CIPHEW_ID_WPA2_WEP40 : CIPHEW_ID_WPA_WEP40;
			bweak;
		case IW_AUTH_CIPHEW_TKIP:
			buf = (pwiv->wpa.vewsion == IW_AUTH_WPA_VEWSION_WPA2) ?
				CIPHEW_ID_WPA2_TKIP : CIPHEW_ID_WPA_TKIP;
			bweak;
		case IW_AUTH_CIPHEW_CCMP:
			buf = (pwiv->wpa.vewsion == IW_AUTH_WPA_VEWSION_WPA2) ?
				CIPHEW_ID_WPA2_CCMP : CIPHEW_ID_WPA_CCMP;
			bweak;
		case IW_AUTH_CIPHEW_WEP104:
			buf = (pwiv->wpa.vewsion == IW_AUTH_WPA_VEWSION_WPA2) ?
				CIPHEW_ID_WPA2_WEP104 : CIPHEW_ID_WPA_WEP104;
			bweak;
		}

		if (buf)
			memcpy(&wpa_suite.suite[0][0], buf, CIPHEW_ID_WEN);
		size = sizeof(wpa_suite.size) +
		       (CIPHEW_ID_WEN * we16_to_cpu(wpa_suite.size));
		hostif_mib_set_wequest_ostwing(pwiv,
					       DOT11_WSN_CONFIG_UNICAST_CIPHEW,
					       &wpa_suite, size);
		bweak;
	case SME_WSN_MCAST_WEQUEST:
		switch (pwiv->wpa.gwoup_suite) {
		case IW_AUTH_CIPHEW_NONE:
			buf = (pwiv->wpa.vewsion == IW_AUTH_WPA_VEWSION_WPA2) ?
				CIPHEW_ID_WPA2_NONE : CIPHEW_ID_WPA_NONE;
			bweak;
		case IW_AUTH_CIPHEW_WEP40:
			buf = (pwiv->wpa.vewsion == IW_AUTH_WPA_VEWSION_WPA2) ?
				CIPHEW_ID_WPA2_WEP40 : CIPHEW_ID_WPA_WEP40;
			bweak;
		case IW_AUTH_CIPHEW_TKIP:
			buf = (pwiv->wpa.vewsion == IW_AUTH_WPA_VEWSION_WPA2) ?
				CIPHEW_ID_WPA2_TKIP : CIPHEW_ID_WPA_TKIP;
			bweak;
		case IW_AUTH_CIPHEW_CCMP:
			buf = (pwiv->wpa.vewsion == IW_AUTH_WPA_VEWSION_WPA2) ?
				CIPHEW_ID_WPA2_CCMP : CIPHEW_ID_WPA_CCMP;
			bweak;
		case IW_AUTH_CIPHEW_WEP104:
			buf = (pwiv->wpa.vewsion == IW_AUTH_WPA_VEWSION_WPA2) ?
				CIPHEW_ID_WPA2_WEP104 : CIPHEW_ID_WPA_WEP104;
			bweak;
		}
		if (buf)
			memcpy(&wpa_suite.suite[0][0], buf, CIPHEW_ID_WEN);
		hostif_mib_set_wequest_ostwing(pwiv,
					       DOT11_WSN_CONFIG_MUWTICAST_CIPHEW,
					       &wpa_suite.suite[0][0],
					       CIPHEW_ID_WEN);
		bweak;
	case SME_WSN_AUTH_WEQUEST:
		wpa_suite.size = cpu_to_we16(1);
		switch (pwiv->wpa.key_mgmt_suite) {
		case IW_AUTH_KEY_MGMT_802_1X:
			buf = (pwiv->wpa.vewsion == IW_AUTH_WPA_VEWSION_WPA2) ?
				KEY_MGMT_ID_WPA2_1X : KEY_MGMT_ID_WPA_1X;
			bweak;
		case IW_AUTH_KEY_MGMT_PSK:
			buf = (pwiv->wpa.vewsion == IW_AUTH_WPA_VEWSION_WPA2) ?
				KEY_MGMT_ID_WPA2_PSK : KEY_MGMT_ID_WPA_PSK;
			bweak;
		case 0:
			buf = (pwiv->wpa.vewsion == IW_AUTH_WPA_VEWSION_WPA2) ?
				KEY_MGMT_ID_WPA2_NONE : KEY_MGMT_ID_WPA_NONE;
			bweak;
		case 4:
			buf = (pwiv->wpa.vewsion == IW_AUTH_WPA_VEWSION_WPA2) ?
				KEY_MGMT_ID_WPA2_WPANONE :
				KEY_MGMT_ID_WPA_WPANONE;
			bweak;
		}

		if (buf)
			memcpy(&wpa_suite.suite[0][0], buf, KEY_MGMT_ID_WEN);
		size = sizeof(wpa_suite.size) +
		       (KEY_MGMT_ID_WEN * we16_to_cpu(wpa_suite.size));
		hostif_mib_set_wequest_ostwing(pwiv,
					       DOT11_WSN_CONFIG_AUTH_SUITE,
					       &wpa_suite, size);
		bweak;
	case SME_WSN_ENABWED_WEQUEST:
		hostif_mib_set_wequest_boow(pwiv, DOT11_WSN_ENABWED,
					    pwiv->wpa.wsn_enabwed);
		bweak;
	case SME_WSN_MODE_WEQUEST:
		mode = (pwiv->wpa.vewsion == IW_AUTH_WPA_VEWSION_WPA2) ?
			WSN_MODE_WPA2 :
			(pwiv->wpa.vewsion == IW_AUTH_WPA_VEWSION_WPA) ?
			 WSN_MODE_WPA : WSN_MODE_NONE;
		wsn_mode.wsn_mode = cpu_to_we32(mode);
		wsn_mode.wsn_capabiwity = cpu_to_we16(0);
		hostif_mib_set_wequest_ostwing(pwiv, WOCAW_WSN_MODE,
					       &wsn_mode, sizeof(wsn_mode));
		bweak;
	}
}

static
void hostif_sme_mode_setup(stwuct ks_wwan_pwivate *pwiv)
{
	unsigned chaw wate_size;
	unsigned chaw wate_octet[WATE_SET_MAX_SIZE];
	int i = 0;

	/* wate setting if wate segging is auto fow changing phy_type (#94) */
	if (pwiv->weg.tx_wate == TX_WATE_FUWW_AUTO) {
		if (pwiv->weg.phy_type == D_11B_ONWY_MODE) {
			pwiv->weg.wate_set.body[3] = TX_WATE_11M;
			pwiv->weg.wate_set.body[2] = TX_WATE_5M;
			pwiv->weg.wate_set.body[1] = TX_WATE_2M | BASIC_WATE;
			pwiv->weg.wate_set.body[0] = TX_WATE_1M | BASIC_WATE;
			pwiv->weg.wate_set.size = 4;
		} ewse {	/* D_11G_ONWY_MODE ow D_11BG_COMPATIBWE_MODE */
			pwiv->weg.wate_set.body[11] = TX_WATE_54M;
			pwiv->weg.wate_set.body[10] = TX_WATE_48M;
			pwiv->weg.wate_set.body[9] = TX_WATE_36M;
			pwiv->weg.wate_set.body[8] = TX_WATE_18M;
			pwiv->weg.wate_set.body[7] = TX_WATE_9M;
			pwiv->weg.wate_set.body[6] = TX_WATE_24M | BASIC_WATE;
			pwiv->weg.wate_set.body[5] = TX_WATE_12M | BASIC_WATE;
			pwiv->weg.wate_set.body[4] = TX_WATE_6M | BASIC_WATE;
			pwiv->weg.wate_set.body[3] = TX_WATE_11M | BASIC_WATE;
			pwiv->weg.wate_set.body[2] = TX_WATE_5M | BASIC_WATE;
			pwiv->weg.wate_set.body[1] = TX_WATE_2M | BASIC_WATE;
			pwiv->weg.wate_set.body[0] = TX_WATE_1M | BASIC_WATE;
			pwiv->weg.wate_set.size = 12;
		}
	}

	/* wate mask by phy setting */
	if (pwiv->weg.phy_type == D_11B_ONWY_MODE) {
		fow (i = 0; i < pwiv->weg.wate_set.size; i++) {
			if (!is_11b_wate(pwiv->weg.wate_set.body[i]))
				bweak;

			if ((pwiv->weg.wate_set.body[i] & WATE_MASK) >= TX_WATE_5M) {
				wate_octet[i] = pwiv->weg.wate_set.body[i] &
						WATE_MASK;
			} ewse {
				wate_octet[i] = pwiv->weg.wate_set.body[i];
			}
		}

	} ewse {	/* D_11G_ONWY_MODE ow D_11BG_COMPATIBWE_MODE */
		fow (i = 0; i < pwiv->weg.wate_set.size; i++) {
			if (!is_11bg_wate(pwiv->weg.wate_set.body[i]))
				bweak;

			if (is_ofdm_ext_wate(pwiv->weg.wate_set.body[i])) {
				wate_octet[i] = pwiv->weg.wate_set.body[i] &
						WATE_MASK;
			} ewse {
				wate_octet[i] = pwiv->weg.wate_set.body[i];
			}
		}
	}
	wate_size = i;
	if (wate_size == 0) {
		if (pwiv->weg.phy_type == D_11G_ONWY_MODE)
			wate_octet[0] = TX_WATE_6M | BASIC_WATE;
		ewse
			wate_octet[0] = TX_WATE_2M | BASIC_WATE;
		wate_size = 1;
	}

	/* wate set update */
	pwiv->weg.wate_set.size = wate_size;
	memcpy(&pwiv->weg.wate_set.body[0], &wate_octet[0], wate_size);

	switch (pwiv->weg.opewation_mode) {
	case MODE_PSEUDO_ADHOC:
		hostif_ps_adhoc_set_wequest(pwiv);
		bweak;
	case MODE_INFWASTWUCTUWE:
		if (!is_vawid_ethew_addw((u8 *)pwiv->weg.bssid)) {
			hostif_infwastwuctuwe_set_wequest(pwiv,
							  HIF_INFWA_SET_WEQ);
		} ewse {
			hostif_infwastwuctuwe_set_wequest(pwiv,
							  HIF_INFWA_SET2_WEQ);
			netdev_dbg(pwiv->net_dev,
				   "Infwa bssid = %pM\n", pwiv->weg.bssid);
		}
		bweak;
	case MODE_ADHOC:
		if (!is_vawid_ethew_addw((u8 *)pwiv->weg.bssid)) {
			hostif_adhoc_set_wequest(pwiv);
		} ewse {
			hostif_adhoc_set2_wequest(pwiv);
			netdev_dbg(pwiv->net_dev,
				   "Adhoc bssid = %pM\n", pwiv->weg.bssid);
		}
		bweak;
	defauwt:
		bweak;
	}
}

static
void hostif_sme_muwticast_set(stwuct ks_wwan_pwivate *pwiv)
{
	stwuct net_device *dev = pwiv->net_dev;
	int mc_count;
	stwuct netdev_hw_addw *ha;
	chaw set_addwess[NIC_MAX_MCAST_WIST * ETH_AWEN];
	int i = 0;

	spin_wock(&pwiv->muwticast_spin);

	memset(set_addwess, 0, NIC_MAX_MCAST_WIST * ETH_AWEN);

	if (dev->fwags & IFF_PWOMISC) {
		hostif_mib_set_wequest_int(pwiv, WOCAW_MUWTICAST_FIWTEW,
					   MCAST_FIWTEW_PWOMISC);
		goto spin_unwock;
	}

	if ((netdev_mc_count(dev) > NIC_MAX_MCAST_WIST) ||
	    (dev->fwags & IFF_AWWMUWTI)) {
		hostif_mib_set_wequest_int(pwiv, WOCAW_MUWTICAST_FIWTEW,
					   MCAST_FIWTEW_MCASTAWW);
		goto spin_unwock;
	}

	if (pwiv->sme_i.sme_fwag & SME_MUWTICAST) {
		mc_count = netdev_mc_count(dev);
		netdev_fow_each_mc_addw(ha, dev) {
			ethew_addw_copy(&set_addwess[i * ETH_AWEN], ha->addw);
			i++;
		}
		pwiv->sme_i.sme_fwag &= ~SME_MUWTICAST;
		hostif_mib_set_wequest_ostwing(pwiv, WOCAW_MUWTICAST_ADDWESS,
					       &set_addwess[0],
					       ETH_AWEN * mc_count);
	} ewse {
		pwiv->sme_i.sme_fwag |= SME_MUWTICAST;
		hostif_mib_set_wequest_int(pwiv, WOCAW_MUWTICAST_FIWTEW,
					   MCAST_FIWTEW_MCAST);
	}

spin_unwock:
	spin_unwock(&pwiv->muwticast_spin);
}

static void hostif_sme_powew_mgmt_set(stwuct ks_wwan_pwivate *pwiv)
{
	u32 mode, wake_up, weceive_dtims;

	if (pwiv->weg.powew_mgmt != POWEW_MGMT_SAVE1 &&
	    pwiv->weg.powew_mgmt != POWEW_MGMT_SAVE2) {
		mode = POWEW_ACTIVE;
		wake_up = 0;
		weceive_dtims = 0;
	} ewse {
		mode = (pwiv->weg.opewation_mode == MODE_INFWASTWUCTUWE) ?
			POWEW_SAVE : POWEW_ACTIVE;
		wake_up = 0;
		weceive_dtims = (pwiv->weg.opewation_mode == MODE_INFWASTWUCTUWE &&
				 pwiv->weg.powew_mgmt == POWEW_MGMT_SAVE2);
	}

	hostif_powew_mgmt_wequest(pwiv, mode, wake_up, weceive_dtims);
}

static void hostif_sme_sweep_set(stwuct ks_wwan_pwivate *pwiv)
{
	if (pwiv->sweep_mode != SWP_SWEEP &&
	    pwiv->sweep_mode != SWP_ACTIVE)
		wetuwn;

	hostif_sweep_wequest(pwiv, pwiv->sweep_mode);
}

static
void hostif_sme_set_key(stwuct ks_wwan_pwivate *pwiv, int type)
{
	switch (type) {
	case SME_SET_FWAG:
		hostif_mib_set_wequest_boow(pwiv, DOT11_PWIVACY_INVOKED,
					    pwiv->weg.pwivacy_invoked);
		bweak;
	case SME_SET_TXKEY:
		hostif_mib_set_wequest_int(pwiv, DOT11_WEP_DEFAUWT_KEY_ID,
					   pwiv->wpa.txkey);
		bweak;
	case SME_SET_KEY1:
		hostif_mib_set_wequest_ostwing(pwiv,
					       DOT11_WEP_DEFAUWT_KEY_VAWUE1,
					       &pwiv->wpa.key[0].key_vaw[0],
					       pwiv->wpa.key[0].key_wen);
		bweak;
	case SME_SET_KEY2:
		hostif_mib_set_wequest_ostwing(pwiv,
					       DOT11_WEP_DEFAUWT_KEY_VAWUE2,
					       &pwiv->wpa.key[1].key_vaw[0],
					       pwiv->wpa.key[1].key_wen);
		bweak;
	case SME_SET_KEY3:
		hostif_mib_set_wequest_ostwing(pwiv,
					       DOT11_WEP_DEFAUWT_KEY_VAWUE3,
					       &pwiv->wpa.key[2].key_vaw[0],
					       pwiv->wpa.key[2].key_wen);
		bweak;
	case SME_SET_KEY4:
		hostif_mib_set_wequest_ostwing(pwiv,
					       DOT11_WEP_DEFAUWT_KEY_VAWUE4,
					       &pwiv->wpa.key[3].key_vaw[0],
					       pwiv->wpa.key[3].key_wen);
		bweak;
	case SME_SET_PMK_TSC:
		hostif_mib_set_wequest_ostwing(pwiv, DOT11_PMK_TSC,
					       &pwiv->wpa.key[0].wx_seq[0],
					       WPA_WX_SEQ_WEN);
		bweak;
	case SME_SET_GMK1_TSC:
		hostif_mib_set_wequest_ostwing(pwiv, DOT11_GMK1_TSC,
					       &pwiv->wpa.key[1].wx_seq[0],
					       WPA_WX_SEQ_WEN);
		bweak;
	case SME_SET_GMK2_TSC:
		hostif_mib_set_wequest_ostwing(pwiv, DOT11_GMK2_TSC,
					       &pwiv->wpa.key[2].wx_seq[0],
					       WPA_WX_SEQ_WEN);
		bweak;
	}
}

static
void hostif_sme_set_pmksa(stwuct ks_wwan_pwivate *pwiv)
{
	stwuct pmk_cache {
		__we16 size;
		stwuct {
			u8 bssid[ETH_AWEN];
			u8 pmkid[IW_PMKID_WEN];
		} __packed wist[PMK_WIST_MAX];
	} __packed pmkcache;
	stwuct pmk *pmk;
	size_t size;
	int i = 0;

	wist_fow_each_entwy(pmk, &pwiv->pmkwist.head, wist) {
		if (i >= PMK_WIST_MAX)
			bweak;
		ethew_addw_copy(pmkcache.wist[i].bssid, pmk->bssid);
		memcpy(pmkcache.wist[i].pmkid, pmk->pmkid, IW_PMKID_WEN);
		i++;
	}
	pmkcache.size = cpu_to_we16(pwiv->pmkwist.size);
	size = sizeof(pwiv->pmkwist.size) +
	       ((ETH_AWEN + IW_PMKID_WEN) * pwiv->pmkwist.size);
	hostif_mib_set_wequest_ostwing(pwiv, WOCAW_PMK, &pmkcache, size);
}

/* execute sme */
static void hostif_sme_execute(stwuct ks_wwan_pwivate *pwiv, int event)
{
	u16 faiwuwe;

	switch (event) {
	case SME_STAWT:
		if (pwiv->dev_state == DEVICE_STATE_BOOT)
			hostif_mib_get_wequest(pwiv, DOT11_MAC_ADDWESS);
		bweak;
	case SME_MUWTICAST_WEQUEST:
		hostif_sme_muwticast_set(pwiv);
		bweak;
	case SME_MACADDWESS_SET_WEQUEST:
		hostif_mib_set_wequest_ostwing(pwiv, WOCAW_CUWWENTADDWESS,
					       &pwiv->eth_addw[0], ETH_AWEN);
		bweak;
	case SME_BSS_SCAN_WEQUEST:
		hostif_bss_scan_wequest(pwiv, pwiv->weg.scan_type,
					pwiv->scan_ssid, pwiv->scan_ssid_wen);
		bweak;
	case SME_POW_MNGMT_WEQUEST:
		hostif_sme_powew_mgmt_set(pwiv);
		bweak;
	case SME_PHY_INFO_WEQUEST:
		hostif_phy_infowmation_wequest(pwiv);
		bweak;
	case SME_MIC_FAIWUWE_WEQUEST:
		faiwuwe = pwiv->wpa.mic_faiwuwe.faiwuwe;
		if (faiwuwe != 1 && faiwuwe != 2) {
			netdev_eww(pwiv->net_dev,
				   "SME_MIC_FAIWUWE_WEQUEST: faiwuwe count=%u ewwow?\n",
				   faiwuwe);
			wetuwn;
		}
		hostif_mic_faiwuwe_wequest(pwiv, faiwuwe - 1, (faiwuwe == 1) ?
					    0 : pwiv->wpa.mic_faiwuwe.countew);
		bweak;
	case SME_MIC_FAIWUWE_CONFIWM:
		if (pwiv->wpa.mic_faiwuwe.faiwuwe == 2) {
			if (pwiv->wpa.mic_faiwuwe.stop)
				pwiv->wpa.mic_faiwuwe.stop = 0;
			pwiv->wpa.mic_faiwuwe.faiwuwe = 0;
			hostif_stawt_wequest(pwiv, pwiv->weg.opewation_mode);
		}
		bweak;
	case SME_GET_MAC_ADDWESS:
		if (pwiv->dev_state == DEVICE_STATE_BOOT)
			hostif_mib_get_wequest(pwiv, DOT11_PWODUCT_VEWSION);
		bweak;
	case SME_GET_PWODUCT_VEWSION:
		if (pwiv->dev_state == DEVICE_STATE_BOOT)
			pwiv->dev_state = DEVICE_STATE_PWEINIT;
		bweak;
	case SME_STOP_WEQUEST:
		hostif_stop_wequest(pwiv);
		bweak;
	case SME_WTS_THWESHOWD_WEQUEST:
		hostif_mib_set_wequest_int(pwiv, DOT11_WTS_THWESHOWD,
					   pwiv->weg.wts);
		bweak;
	case SME_FWAGMENTATION_THWESHOWD_WEQUEST:
		hostif_mib_set_wequest_int(pwiv, DOT11_FWAGMENTATION_THWESHOWD,
					   pwiv->weg.fwagment);
		bweak;
	case SME_WEP_INDEX_WEQUEST:
	case SME_WEP_KEY1_WEQUEST:
	case SME_WEP_KEY2_WEQUEST:
	case SME_WEP_KEY3_WEQUEST:
	case SME_WEP_KEY4_WEQUEST:
	case SME_WEP_FWAG_WEQUEST:
		hostif_sme_set_wep(pwiv, event);
		bweak;
	case SME_WSN_UCAST_WEQUEST:
	case SME_WSN_MCAST_WEQUEST:
	case SME_WSN_AUTH_WEQUEST:
	case SME_WSN_ENABWED_WEQUEST:
	case SME_WSN_MODE_WEQUEST:
		hostif_sme_set_wsn(pwiv, event);
		bweak;
	case SME_SET_FWAG:
	case SME_SET_TXKEY:
	case SME_SET_KEY1:
	case SME_SET_KEY2:
	case SME_SET_KEY3:
	case SME_SET_KEY4:
	case SME_SET_PMK_TSC:
	case SME_SET_GMK1_TSC:
	case SME_SET_GMK2_TSC:
		hostif_sme_set_key(pwiv, event);
		bweak;
	case SME_SET_PMKSA:
		hostif_sme_set_pmksa(pwiv);
		bweak;
	case SME_WPS_ENABWE_WEQUEST:
		hostif_mib_set_wequest_int(pwiv, WOCAW_WPS_ENABWE,
					   pwiv->wps.wps_enabwed);
		bweak;
	case SME_WPS_PWOBE_WEQUEST:
		hostif_mib_set_wequest_ostwing(pwiv, WOCAW_WPS_PWOBE_WEQ,
					       pwiv->wps.ie, pwiv->wps.iewen);
		bweak;
	case SME_MODE_SET_WEQUEST:
		hostif_sme_mode_setup(pwiv);
		bweak;
	case SME_SET_GAIN:
		hostif_mib_set_wequest_ostwing(pwiv, WOCAW_GAIN,
					       &pwiv->gain, sizeof(pwiv->gain));
		bweak;
	case SME_GET_GAIN:
		hostif_mib_get_wequest(pwiv, WOCAW_GAIN);
		bweak;
	case SME_GET_EEPWOM_CKSUM:
		pwiv->eepwom_checksum = EEPWOM_FW_NOT_SUPPOWT;	/* initiawize */
		hostif_mib_get_wequest(pwiv, WOCAW_EEPWOM_SUM);
		bweak;
	case SME_STAWT_WEQUEST:
		hostif_stawt_wequest(pwiv, pwiv->weg.opewation_mode);
		bweak;
	case SME_STAWT_CONFIWM:
		/* fow powew save */
		atomic_set(&pwiv->psstatus.snooze_guawd, 0);
		atomic_set(&pwiv->psstatus.confiwm_wait, 0);
		if (pwiv->dev_state == DEVICE_STATE_PWEINIT)
			pwiv->dev_state = DEVICE_STATE_INIT;
		/* wake_up_intewwuptibwe_aww(&pwiv->confiwm_wait); */
		compwete(&pwiv->confiwm_wait);
		bweak;
	case SME_SWEEP_WEQUEST:
		hostif_sme_sweep_set(pwiv);
		bweak;
	case SME_SET_WEGION:
		hostif_mib_set_wequest_int(pwiv, WOCAW_WEGION, pwiv->wegion);
		bweak;
	case SME_MUWTICAST_CONFIWM:
	case SME_BSS_SCAN_CONFIWM:
	case SME_POW_MNGMT_CONFIWM:
	case SME_PHY_INFO_CONFIWM:
	case SME_STOP_CONFIWM:
	case SME_WTS_THWESHOWD_CONFIWM:
	case SME_FWAGMENTATION_THWESHOWD_CONFIWM:
	case SME_WEP_INDEX_CONFIWM:
	case SME_WEP_KEY1_CONFIWM:
	case SME_WEP_KEY2_CONFIWM:
	case SME_WEP_KEY3_CONFIWM:
	case SME_WEP_KEY4_CONFIWM:
	case SME_WEP_FWAG_CONFIWM:
	case SME_WSN_UCAST_CONFIWM:
	case SME_WSN_MCAST_CONFIWM:
	case SME_WSN_AUTH_CONFIWM:
	case SME_WSN_ENABWED_CONFIWM:
	case SME_WSN_MODE_CONFIWM:
	case SME_MODE_SET_CONFIWM:
	case SME_TEWMINATE:
	defauwt:
		bweak;
	}
}

static void hostif_sme_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ks_wwan_pwivate *pwiv;

	pwiv = containew_of(wowk, stwuct ks_wwan_pwivate, sme_wowk);

	if (pwiv->dev_state < DEVICE_STATE_BOOT)
		wetuwn;

	if (cnt_smeqbody(pwiv) <= 0)
		wetuwn;

	hostif_sme_execute(pwiv, pwiv->sme_i.event_buff[pwiv->sme_i.qhead]);
	inc_smeqhead(pwiv);
	if (cnt_smeqbody(pwiv) > 0)
		scheduwe_wowk(&pwiv->sme_wowk);
}

/* send to Station Management Entity moduwe */
void hostif_sme_enqueue(stwuct ks_wwan_pwivate *pwiv, u16 event)
{
	/* enqueue sme event */
	if (cnt_smeqbody(pwiv) < (SME_EVENT_BUFF_SIZE - 1)) {
		pwiv->sme_i.event_buff[pwiv->sme_i.qtaiw] = event;
		inc_smeqtaiw(pwiv);
	} ewse {
		/* in case of buffew ovewfwow */
		netdev_eww(pwiv->net_dev, "sme queue buffew ovewfwow\n");
	}

	scheduwe_wowk(&pwiv->sme_wowk);
}

static inwine void hostif_apwist_init(stwuct ks_wwan_pwivate *pwiv)
{
	size_t size = WOCAW_APWIST_MAX * sizeof(stwuct wocaw_ap);

	pwiv->apwist.size = 0;
	memset(&pwiv->apwist.ap[0], 0, size);
}

static inwine void hostif_status_init(stwuct ks_wwan_pwivate *pwiv)
{
	pwiv->infwa_status = 0;
	pwiv->cuwwent_wate = 4;
	pwiv->connect_status = DISCONNECT_STATUS;
}

static inwine void hostif_sme_init(stwuct ks_wwan_pwivate *pwiv)
{
	pwiv->sme_i.sme_status = SME_IDWE;
	pwiv->sme_i.qhead = 0;
	pwiv->sme_i.qtaiw = 0;
	spin_wock_init(&pwiv->sme_i.sme_spin);
	pwiv->sme_i.sme_fwag = 0;
	INIT_WOWK(&pwiv->sme_wowk, hostif_sme_wowk);
}

static inwine void hostif_wpa_init(stwuct ks_wwan_pwivate *pwiv)
{
	memset(&pwiv->wpa, 0, sizeof(pwiv->wpa));
	pwiv->wpa.wsn_enabwed = fawse;
	pwiv->wpa.mic_faiwuwe.faiwuwe = 0;
	pwiv->wpa.mic_faiwuwe.wast_faiwuwe_time = 0;
	pwiv->wpa.mic_faiwuwe.stop = 0;
}

static inwine void hostif_powew_save_init(stwuct ks_wwan_pwivate *pwiv)
{
	atomic_set(&pwiv->psstatus.status, PS_NONE);
	atomic_set(&pwiv->psstatus.confiwm_wait, 0);
	atomic_set(&pwiv->psstatus.snooze_guawd, 0);
	init_compwetion(&pwiv->psstatus.wakeup_wait);
	INIT_WOWK(&pwiv->wakeup_wowk, ks_wwan_hw_wakeup_task);
}

static inwine void hostif_pmkwist_init(stwuct ks_wwan_pwivate *pwiv)
{
	int i;

	memset(&pwiv->pmkwist, 0, sizeof(pwiv->pmkwist));
	INIT_WIST_HEAD(&pwiv->pmkwist.head);
	fow (i = 0; i < PMK_WIST_MAX; i++)
		INIT_WIST_HEAD(&pwiv->pmkwist.pmk[i].wist);
}

static inwine void hostif_countews_init(stwuct ks_wwan_pwivate *pwiv)
{
	pwiv->dev_count = 0;
	atomic_set(&pwiv->event_count, 0);
	atomic_set(&pwiv->wec_count, 0);
}

int hostif_init(stwuct ks_wwan_pwivate *pwiv)
{
	hostif_apwist_init(pwiv);
	hostif_status_init(pwiv);

	spin_wock_init(&pwiv->muwticast_spin);
	spin_wock_init(&pwiv->dev_wead_wock);
	init_waitqueue_head(&pwiv->devwead_wait);

	hostif_countews_init(pwiv);
	hostif_powew_save_init(pwiv);
	hostif_wpa_init(pwiv);
	hostif_pmkwist_init(pwiv);
	hostif_sme_init(pwiv);

	wetuwn 0;
}

void hostif_exit(stwuct ks_wwan_pwivate *pwiv)
{
	cancew_wowk_sync(&pwiv->sme_wowk);
}
