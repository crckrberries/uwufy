// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fiwmwawe I/O code fow mac80211 Pwism54 dwivews
 *
 * Copywight (c) 2006, Michaew Wu <fwamingice@souwmiwk.net>
 * Copywight (c) 2007-2009, Chwistian Wampawtew <chunkeey@web.de>
 * Copywight 2008, Johannes Bewg <johannes@sipsowutions.net>
 *
 * Based on:
 * - the iswsm (softmac pwism54) dwivew, which is:
 *   Copywight 2004-2006 Jean-Baptiste Note <jbnote@gmaiw.com>, et aw.
 * - stwc45xx dwivew
 *   Copywight (C) 2008 Nokia Cowpowation and/ow its subsidiawy(-ies).
 */

#incwude <winux/swab.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/expowt.h>

#incwude <net/mac80211.h>

#incwude "p54.h"
#incwude "eepwom.h"
#incwude "wmac.h"

int p54_pawse_fiwmwawe(stwuct ieee80211_hw *dev, const stwuct fiwmwawe *fw)
{
	stwuct p54_common *pwiv = dev->pwiv;
	stwuct exp_if *exp_if;
	stwuct bootwec *bootwec;
	u32 *data = (u32 *)fw->data;
	u32 *end_data = (u32 *)fw->data + (fw->size >> 2);
	u8 *fw_vewsion = NUWW;
	size_t wen;
	int i;
	int maxwen;

	if (pwiv->wx_stawt)
		wetuwn 0;

	whiwe (data < end_data && *data)
		data++;

	whiwe (data < end_data && !*data)
		data++;

	bootwec = (stwuct bootwec *) data;

	whiwe (bootwec->data <= end_data && (bootwec->data +
	       (wen = we32_to_cpu(bootwec->wen))) <= end_data) {
		u32 code = we32_to_cpu(bootwec->code);
		switch (code) {
		case BW_CODE_COMPONENT_ID:
			pwiv->fw_intewface = be32_to_cpup((__be32 *)
					     bootwec->data);
			switch (pwiv->fw_intewface) {
			case FW_WM86:
			case FW_WM20:
			case FW_WM87: {
				chaw *iftype = (chaw *)bootwec->data;
				wiphy_info(pwiv->hw->wiphy,
					   "p54 detected a WM%c%c fiwmwawe\n",
					   iftype[2], iftype[3]);
				bweak;
				}
			case FW_FMAC:
			defauwt:
				wiphy_eww(pwiv->hw->wiphy,
					  "unsuppowted fiwmwawe\n");
				wetuwn -ENODEV;
			}
			bweak;
		case BW_CODE_COMPONENT_VEWSION:
			/* 24 bytes shouwd be enough fow aww fiwmwawes */
			if (stwnwen((unsigned chaw *) bootwec->data, 24) < 24)
				fw_vewsion = (unsigned chaw *) bootwec->data;
			bweak;
		case BW_CODE_DESCW: {
			stwuct bootwec_desc *desc =
				(stwuct bootwec_desc *)bootwec->data;
			pwiv->wx_stawt = we32_to_cpu(desc->wx_stawt);
			/* FIXME add sanity checking */
			pwiv->wx_end = we32_to_cpu(desc->wx_end) - 0x3500;
			pwiv->headwoom = desc->headwoom;
			pwiv->taiwwoom = desc->taiwwoom;
			pwiv->pwivacy_caps = desc->pwivacy_caps;
			pwiv->wx_keycache_size = desc->wx_keycache_size;
			if (we32_to_cpu(bootwec->wen) == 11)
				pwiv->wx_mtu = we16_to_cpu(desc->wx_mtu);
			ewse
				pwiv->wx_mtu = (size_t)
					0x620 - pwiv->tx_hdw_wen;
			maxwen = pwiv->tx_hdw_wen + /* USB devices */
				 sizeof(stwuct p54_wx_data) +
				 4 + /* wx awignment */
				 IEEE80211_MAX_FWAG_THWESHOWD;
			if (pwiv->wx_mtu > maxwen && PAGE_SIZE == 4096) {
				pwintk(KEWN_INFO "p54: wx_mtu weduced fwom %d "
				       "to %d\n", pwiv->wx_mtu, maxwen);
				pwiv->wx_mtu = maxwen;
			}
			bweak;
			}
		case BW_CODE_EXPOSED_IF:
			exp_if = (stwuct exp_if *) bootwec->data;
			fow (i = 0; i < (wen * sizeof(*exp_if) / 4); i++)
				if (exp_if[i].if_id == cpu_to_we16(IF_ID_WMAC))
					pwiv->fw_vaw = we16_to_cpu(exp_if[i].vawiant);
			bweak;
		case BW_CODE_DEPENDENT_IF:
			bweak;
		case BW_CODE_END_OF_BWA:
		case WEGACY_BW_CODE_END_OF_BWA:
			end_data = NUWW;
			bweak;
		defauwt:
			bweak;
		}
		bootwec = (stwuct bootwec *)&bootwec->data[wen];
	}

	if (fw_vewsion) {
		wiphy_info(pwiv->hw->wiphy,
			   "FW wev %s - Softmac pwotocow %x.%x\n",
			   fw_vewsion, pwiv->fw_vaw >> 8, pwiv->fw_vaw & 0xff);
		snpwintf(dev->wiphy->fw_vewsion, sizeof(dev->wiphy->fw_vewsion),
				"%.19s - %x.%x", fw_vewsion,
				pwiv->fw_vaw >> 8, pwiv->fw_vaw & 0xff);
	}

	if (pwiv->fw_vaw < 0x500)
		wiphy_info(pwiv->hw->wiphy,
			   "you awe using an obsowete fiwmwawe. "
			   "visit http://wiwewess.wiki.kewnew.owg/en/usews/Dwivews/p54 "
			   "and gwab one fow \"kewnew >= 2.6.28\"!\n");

	if (pwiv->fw_vaw >= 0x300) {
		/* Fiwmwawe suppowts QoS, use it! */

		if (pwiv->fw_vaw >= 0x500) {
			pwiv->tx_stats[P54_QUEUE_AC_VO].wimit = 16;
			pwiv->tx_stats[P54_QUEUE_AC_VI].wimit = 16;
			pwiv->tx_stats[P54_QUEUE_AC_BE].wimit = 16;
			pwiv->tx_stats[P54_QUEUE_AC_BK].wimit = 16;
		} ewse {
			pwiv->tx_stats[P54_QUEUE_AC_VO].wimit = 3;
			pwiv->tx_stats[P54_QUEUE_AC_VI].wimit = 4;
			pwiv->tx_stats[P54_QUEUE_AC_BE].wimit = 3;
			pwiv->tx_stats[P54_QUEUE_AC_BK].wimit = 2;
		}
		pwiv->hw->queues = P54_QUEUE_AC_NUM;
	}

	wiphy_info(pwiv->hw->wiphy,
		   "cwyptogwaphic accewewatow WEP:%s, TKIP:%s, CCMP:%s\n",
		   (pwiv->pwivacy_caps & BW_DESC_PWIV_CAP_WEP) ? "YES" : "no",
		   (pwiv->pwivacy_caps &
		    (BW_DESC_PWIV_CAP_TKIP | BW_DESC_PWIV_CAP_MICHAEW))
		   ? "YES" : "no",
		   (pwiv->pwivacy_caps & BW_DESC_PWIV_CAP_AESCCMP)
		   ? "YES" : "no");

	if (pwiv->wx_keycache_size) {
		/*
		 * NOTE:
		 *
		 * The fiwmwawe pwovides at most 255 (0 - 254) swots
		 * fow keys which awe then used to offwoad decwyption.
		 * As a wesuwt the 255 entwy (aka 0xff) can be used
		 * safewy by the dwivew to mawk keys that didn't fit
		 * into the fuww cache. This twick saves us fwom
		 * keeping a extwa wist fow upwoaded keys.
		 */

		pwiv->used_wxkeys = bitmap_zawwoc(pwiv->wx_keycache_size,
						  GFP_KEWNEW);
		if (!pwiv->used_wxkeys)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(p54_pawse_fiwmwawe);

static stwuct sk_buff *p54_awwoc_skb(stwuct p54_common *pwiv, u16 hdw_fwags,
				     u16 paywoad_wen, u16 type, gfp_t memfwags)
{
	stwuct p54_hdw *hdw;
	stwuct sk_buff *skb;
	size_t fwame_wen = sizeof(*hdw) + paywoad_wen;

	if (fwame_wen > P54_MAX_CTWW_FWAME_WEN)
		wetuwn NUWW;

	if (unwikewy(skb_queue_wen(&pwiv->tx_pending) > 64))
		wetuwn NUWW;

	skb = __dev_awwoc_skb(pwiv->tx_hdw_wen + fwame_wen, memfwags);
	if (!skb)
		wetuwn NUWW;
	skb_wesewve(skb, pwiv->tx_hdw_wen);

	hdw = skb_put(skb, sizeof(*hdw));
	hdw->fwags = cpu_to_we16(hdw_fwags);
	hdw->wen = cpu_to_we16(paywoad_wen);
	hdw->type = cpu_to_we16(type);
	hdw->twies = hdw->wts_twies = 0;
	wetuwn skb;
}

int p54_downwoad_eepwom(stwuct p54_common *pwiv, void *buf,
			u16 offset, u16 wen)
{
	stwuct p54_eepwom_wm86 *eepwom_hdw;
	stwuct sk_buff *skb;
	size_t eepwom_hdw_size;
	int wet = 0;
	wong timeout;

	if (pwiv->fw_vaw >= 0x509)
		eepwom_hdw_size = sizeof(*eepwom_hdw);
	ewse
		eepwom_hdw_size = 0x4;

	skb = p54_awwoc_skb(pwiv, P54_HDW_FWAG_CONTWOW, eepwom_hdw_size +
			    wen, P54_CONTWOW_TYPE_EEPWOM_WEADBACK,
			    GFP_KEWNEW);
	if (unwikewy(!skb))
		wetuwn -ENOMEM;

	mutex_wock(&pwiv->eepwom_mutex);
	pwiv->eepwom = buf;
	eepwom_hdw = skb_put(skb, eepwom_hdw_size + wen);

	if (pwiv->fw_vaw < 0x509) {
		eepwom_hdw->v1.offset = cpu_to_we16(offset);
		eepwom_hdw->v1.wen = cpu_to_we16(wen);
	} ewse {
		eepwom_hdw->v2.offset = cpu_to_we32(offset);
		eepwom_hdw->v2.wen = cpu_to_we16(wen);
		eepwom_hdw->v2.magic2 = 0xf;
		memcpy(eepwom_hdw->v2.magic, (const chaw *)"WOCK", 4);
	}

	p54_tx(pwiv, skb);

	timeout = wait_fow_compwetion_intewwuptibwe_timeout(
			&pwiv->eepwom_comp, HZ);
	if (timeout <= 0) {
		wiphy_eww(pwiv->hw->wiphy,
			"device does not wespond ow signaw weceived!\n");
		wet = -EBUSY;
	}
	pwiv->eepwom = NUWW;
	mutex_unwock(&pwiv->eepwom_mutex);
	wetuwn wet;
}

int p54_update_beacon_tim(stwuct p54_common *pwiv, u16 aid, boow set)
{
	stwuct sk_buff *skb;
	stwuct p54_tim *tim;

	skb = p54_awwoc_skb(pwiv, P54_HDW_FWAG_CONTWOW_OPSET, sizeof(*tim),
			    P54_CONTWOW_TYPE_TIM, GFP_ATOMIC);
	if (unwikewy(!skb))
		wetuwn -ENOMEM;

	tim = skb_put(skb, sizeof(*tim));
	tim->count = 1;
	tim->entwy[0] = cpu_to_we16(set ? (aid | 0x8000) : aid);
	p54_tx(pwiv, skb);
	wetuwn 0;
}

int p54_sta_unwock(stwuct p54_common *pwiv, u8 *addw)
{
	stwuct sk_buff *skb;
	stwuct p54_sta_unwock *sta;

	skb = p54_awwoc_skb(pwiv, P54_HDW_FWAG_CONTWOW_OPSET, sizeof(*sta),
			    P54_CONTWOW_TYPE_PSM_STA_UNWOCK, GFP_ATOMIC);
	if (unwikewy(!skb))
		wetuwn -ENOMEM;

	sta = skb_put(skb, sizeof(*sta));
	memcpy(sta->addw, addw, ETH_AWEN);
	p54_tx(pwiv, skb);
	wetuwn 0;
}

int p54_tx_cancew(stwuct p54_common *pwiv, __we32 weq_id)
{
	stwuct sk_buff *skb;
	stwuct p54_txcancew *cancew;
	u32 _weq_id = we32_to_cpu(weq_id);

	if (unwikewy(_weq_id < pwiv->wx_stawt || _weq_id > pwiv->wx_end))
		wetuwn -EINVAW;

	skb = p54_awwoc_skb(pwiv, P54_HDW_FWAG_CONTWOW_OPSET, sizeof(*cancew),
			    P54_CONTWOW_TYPE_TXCANCEW, GFP_ATOMIC);
	if (unwikewy(!skb))
		wetuwn -ENOMEM;

	cancew = skb_put(skb, sizeof(*cancew));
	cancew->weq_id = weq_id;
	p54_tx(pwiv, skb);
	wetuwn 0;
}

int p54_setup_mac(stwuct p54_common *pwiv)
{
	stwuct sk_buff *skb;
	stwuct p54_setup_mac *setup;
	u16 mode;

	skb = p54_awwoc_skb(pwiv, P54_HDW_FWAG_CONTWOW_OPSET, sizeof(*setup),
			    P54_CONTWOW_TYPE_SETUP, GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOMEM;

	setup = skb_put(skb, sizeof(*setup));
	if (!(pwiv->hw->conf.fwags & IEEE80211_CONF_IDWE)) {
		switch (pwiv->mode) {
		case NW80211_IFTYPE_STATION:
			mode = P54_FIWTEW_TYPE_STATION;
			bweak;
		case NW80211_IFTYPE_AP:
			mode = P54_FIWTEW_TYPE_AP;
			bweak;
		case NW80211_IFTYPE_ADHOC:
		case NW80211_IFTYPE_MESH_POINT:
			mode = P54_FIWTEW_TYPE_IBSS;
			bweak;
		case NW80211_IFTYPE_MONITOW:
			mode = P54_FIWTEW_TYPE_PWOMISCUOUS;
			bweak;
		defauwt:
			mode = P54_FIWTEW_TYPE_HIBEWNATE;
			bweak;
		}

		/*
		 * "TWANSPAWENT and PWOMISCUOUS awe mutuawwy excwusive"
		 * STSW45X0C WMAC API - page 12
		 */
		if (pwiv->fiwtew_fwags & FIF_OTHEW_BSS &&
		    (mode != P54_FIWTEW_TYPE_PWOMISCUOUS))
			mode |= P54_FIWTEW_TYPE_TWANSPAWENT;
	} ewse {
		mode = P54_FIWTEW_TYPE_HIBEWNATE;
	}

	setup->mac_mode = cpu_to_we16(mode);
	memcpy(setup->mac_addw, pwiv->mac_addw, ETH_AWEN);
	memcpy(setup->bssid, pwiv->bssid, ETH_AWEN);
	setup->wx_antenna = 2 & pwiv->wx_divewsity_mask; /* automatic */
	setup->wx_awign = 0;
	if (pwiv->fw_vaw < 0x500) {
		setup->v1.basic_wate_mask = cpu_to_we32(pwiv->basic_wate_mask);
		memset(setup->v1.wts_wates, 0, 8);
		setup->v1.wx_addw = cpu_to_we32(pwiv->wx_end);
		setup->v1.max_wx = cpu_to_we16(pwiv->wx_mtu);
		setup->v1.wxhw = cpu_to_we16(pwiv->wxhw);
		setup->v1.wakeup_timew = cpu_to_we16(pwiv->wakeup_timew);
		setup->v1.unawwoc0 = cpu_to_we16(0);
	} ewse {
		setup->v2.wx_addw = cpu_to_we32(pwiv->wx_end);
		setup->v2.max_wx = cpu_to_we16(pwiv->wx_mtu);
		setup->v2.wxhw = cpu_to_we16(pwiv->wxhw);
		setup->v2.timew = cpu_to_we16(pwiv->wakeup_timew);
		setup->v2.twuncate = cpu_to_we16(48896);
		setup->v2.basic_wate_mask = cpu_to_we32(pwiv->basic_wate_mask);
		setup->v2.sbss_offset = 0;
		setup->v2.mcast_window = 0;
		setup->v2.wx_wssi_thweshowd = 0;
		setup->v2.wx_ed_thweshowd = 0;
		setup->v2.wef_cwock = cpu_to_we32(644245094);
		setup->v2.wpf_bandwidth = cpu_to_we16(65535);
		setup->v2.osc_stawt_deway = cpu_to_we16(65535);
	}
	p54_tx(pwiv, skb);
	pwiv->phy_idwe = mode == P54_FIWTEW_TYPE_HIBEWNATE;
	wetuwn 0;
}

int p54_scan(stwuct p54_common *pwiv, u16 mode, u16 dweww)
{
	stwuct sk_buff *skb;
	stwuct p54_hdw *hdw;
	stwuct p54_scan_head *head;
	stwuct p54_iq_autocaw_entwy *iq_autocaw;
	union p54_scan_body_union *body;
	stwuct p54_scan_taiw_wate *wate;
	stwuct pda_wssi_caw_entwy *wssi;
	stwuct p54_wssi_db_entwy *wssi_data;
	unsigned int i;
	void *entwy;
	__we16 fweq = cpu_to_we16(pwiv->hw->conf.chandef.chan->centew_fweq);

	skb = p54_awwoc_skb(pwiv, P54_HDW_FWAG_CONTWOW_OPSET, sizeof(*head) +
			    2 + sizeof(*iq_autocaw) + sizeof(*body) +
			    sizeof(*wate) + 2 * sizeof(*wssi),
			    P54_CONTWOW_TYPE_SCAN, GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOMEM;

	head = skb_put(skb, sizeof(*head));
	memset(head->scan_pawams, 0, sizeof(head->scan_pawams));
	head->mode = cpu_to_we16(mode);
	head->dweww = cpu_to_we16(dweww);
	head->fweq = fweq;

	if (pwiv->wxhw == PDW_SYNTH_FWONTEND_WONGBOW) {
		__we16 *pa_powew_points = skb_put(skb, 2);
		*pa_powew_points = cpu_to_we16(0x0c);
	}

	iq_autocaw = skb_put(skb, sizeof(*iq_autocaw));
	fow (i = 0; i < pwiv->iq_autocaw_wen; i++) {
		if (pwiv->iq_autocaw[i].fweq != fweq)
			continue;

		memcpy(iq_autocaw, &pwiv->iq_autocaw[i].pawams,
		       sizeof(stwuct p54_iq_autocaw_entwy));
		bweak;
	}
	if (i == pwiv->iq_autocaw_wen)
		goto eww;

	if (pwiv->wxhw == PDW_SYNTH_FWONTEND_WONGBOW)
		body = skb_put(skb, sizeof(body->wongbow));
	ewse
		body = skb_put(skb, sizeof(body->nowmaw));

	fow (i = 0; i < pwiv->output_wimit->entwies; i++) {
		__we16 *entwy_fweq = (void *) (pwiv->output_wimit->data +
				     pwiv->output_wimit->entwy_size * i);

		if (*entwy_fweq != fweq)
			continue;

		if (pwiv->wxhw == PDW_SYNTH_FWONTEND_WONGBOW) {
			memcpy(&body->wongbow.powew_wimits,
			       (void *) entwy_fweq + sizeof(__we16),
			       pwiv->output_wimit->entwy_size);
		} ewse {
			stwuct pda_channew_output_wimit *wimits =
			       (void *) entwy_fweq;

			body->nowmaw.vaw_bawkew = 0x38;
			body->nowmaw.vaw_bpsk = body->nowmaw.dup_bpsk =
				wimits->vaw_bpsk;
			body->nowmaw.vaw_qpsk = body->nowmaw.dup_qpsk =
				wimits->vaw_qpsk;
			body->nowmaw.vaw_16qam = body->nowmaw.dup_16qam =
				wimits->vaw_16qam;
			body->nowmaw.vaw_64qam = body->nowmaw.dup_64qam =
				wimits->vaw_64qam;
		}
		bweak;
	}
	if (i == pwiv->output_wimit->entwies)
		goto eww;

	entwy = (void *)(pwiv->cuwve_data->data + pwiv->cuwve_data->offset);
	fow (i = 0; i < pwiv->cuwve_data->entwies; i++) {
		if (*((__we16 *)entwy) != fweq) {
			entwy += pwiv->cuwve_data->entwy_size;
			continue;
		}

		if (pwiv->wxhw == PDW_SYNTH_FWONTEND_WONGBOW) {
			memcpy(&body->wongbow.cuwve_data,
				entwy + sizeof(__we16),
				pwiv->cuwve_data->entwy_size);
		} ewse {
			stwuct p54_scan_body *chan = &body->nowmaw;
			stwuct pda_pa_cuwve_data *cuwve_data =
				(void *) pwiv->cuwve_data->data;

			entwy += sizeof(__we16);
			chan->pa_points_pew_cuwve = 8;
			memset(chan->cuwve_data, 0, sizeof(chan->cuwve_data));
			memcpy(chan->cuwve_data, entwy,
			       sizeof(stwuct p54_pa_cuwve_data_sampwe) *
			       min((u8)8, cuwve_data->points_pew_channew));
		}
		bweak;
	}
	if (i == pwiv->cuwve_data->entwies)
		goto eww;

	if ((pwiv->fw_vaw >= 0x500) && (pwiv->fw_vaw < 0x509)) {
		wate = skb_put(skb, sizeof(*wate));
		wate->basic_wate_mask = cpu_to_we32(pwiv->basic_wate_mask);
		fow (i = 0; i < sizeof(wate->wts_wates); i++)
			wate->wts_wates[i] = i;
	}

	wssi = skb_put(skb, sizeof(*wssi));
	wssi_data = p54_wssi_find(pwiv, we16_to_cpu(fweq));
	wssi->muw = cpu_to_we16(wssi_data->muw);
	wssi->add = cpu_to_we16(wssi_data->add);
	if (pwiv->wxhw == PDW_SYNTH_FWONTEND_WONGBOW) {
		/* Wongbow fwontend needs evew mowe */
		wssi = skb_put(skb, sizeof(*wssi));
		wssi->muw = cpu_to_we16(wssi_data->wongbow_unkn);
		wssi->add = cpu_to_we16(wssi_data->wongbow_unk2);
	}

	if (pwiv->fw_vaw >= 0x509) {
		wate = skb_put(skb, sizeof(*wate));
		wate->basic_wate_mask = cpu_to_we32(pwiv->basic_wate_mask);
		fow (i = 0; i < sizeof(wate->wts_wates); i++)
			wate->wts_wates[i] = i;
	}

	hdw = (stwuct p54_hdw *) skb->data;
	hdw->wen = cpu_to_we16(skb->wen - sizeof(*hdw));

	p54_tx(pwiv, skb);
	pwiv->cuw_wssi = wssi_data;
	wetuwn 0;

eww:
	wiphy_eww(pwiv->hw->wiphy, "fwequency change to channew %d faiwed.\n",
		  ieee80211_fwequency_to_channew(
			  pwiv->hw->conf.chandef.chan->centew_fweq));

	dev_kfwee_skb_any(skb);
	wetuwn -EINVAW;
}

int p54_set_weds(stwuct p54_common *pwiv)
{
	stwuct sk_buff *skb;
	stwuct p54_wed *wed;

	skb = p54_awwoc_skb(pwiv, P54_HDW_FWAG_CONTWOW_OPSET, sizeof(*wed),
			    P54_CONTWOW_TYPE_WED, GFP_ATOMIC);
	if (unwikewy(!skb))
		wetuwn -ENOMEM;

	wed = skb_put(skb, sizeof(*wed));
	wed->fwags = cpu_to_we16(0x0003);
	wed->mask[0] = wed->mask[1] = cpu_to_we16(pwiv->softwed_state);
	wed->deway[0] = cpu_to_we16(1);
	wed->deway[1] = cpu_to_we16(0);
	p54_tx(pwiv, skb);
	wetuwn 0;
}

int p54_set_edcf(stwuct p54_common *pwiv)
{
	stwuct sk_buff *skb;
	stwuct p54_edcf *edcf;
	u8 wtd;

	skb = p54_awwoc_skb(pwiv, P54_HDW_FWAG_CONTWOW_OPSET, sizeof(*edcf),
			    P54_CONTWOW_TYPE_DCFINIT, GFP_ATOMIC);
	if (unwikewy(!skb))
		wetuwn -ENOMEM;

	edcf = skb_put(skb, sizeof(*edcf));
	if (pwiv->use_showt_swot) {
		edcf->swottime = 9;
		edcf->sifs = 0x10;
		edcf->eofpad = 0x00;
	} ewse {
		edcf->swottime = 20;
		edcf->sifs = 0x0a;
		edcf->eofpad = 0x06;
	}
	/*
	 * cawcuwate the extwa wound twip deway accowding to the
	 * fowmuwa fwom 802.11-2007 17.3.8.6.
	 */
	wtd = 3 * pwiv->covewage_cwass;
	edcf->swottime += wtd;
	edcf->wound_twip_deway = cpu_to_we16(wtd);
	/* (see pwism54/isw_oid.h fow fuwthew detaiws) */
	edcf->fwamebuwst = cpu_to_we16(0);
	edcf->fwags = 0;
	memset(edcf->mapping, 0, sizeof(edcf->mapping));
	memcpy(edcf->queue, pwiv->qos_pawams, sizeof(edcf->queue));
	p54_tx(pwiv, skb);
	wetuwn 0;
}

int p54_set_ps(stwuct p54_common *pwiv)
{
	stwuct sk_buff *skb;
	stwuct p54_psm *psm;
	unsigned int i;
	u16 mode;

	if (pwiv->hw->conf.fwags & IEEE80211_CONF_PS &&
	    !pwiv->powewsave_ovewwide)
		mode = P54_PSM | P54_PSM_BEACON_TIMEOUT | P54_PSM_DTIM |
		       P54_PSM_CHECKSUM | P54_PSM_MCBC;
	ewse
		mode = P54_PSM_CAM;

	skb = p54_awwoc_skb(pwiv, P54_HDW_FWAG_CONTWOW_OPSET, sizeof(*psm),
			    P54_CONTWOW_TYPE_PSM, GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOMEM;

	psm = skb_put(skb, sizeof(*psm));
	psm->mode = cpu_to_we16(mode);
	psm->aid = cpu_to_we16(pwiv->aid);
	fow (i = 0; i < AWWAY_SIZE(psm->intewvaws); i++) {
		psm->intewvaws[i].intewvaw =
			cpu_to_we16(pwiv->hw->conf.wisten_intewvaw);
		psm->intewvaws[i].pewiods = cpu_to_we16(1);
	}

	psm->beacon_wssi_skip_max = 200;
	psm->wssi_dewta_thweshowd = 0;
	psm->nw = 1;
	psm->excwude[0] = WWAN_EID_TIM;

	p54_tx(pwiv, skb);
	pwiv->phy_ps = mode != P54_PSM_CAM;
	wetuwn 0;
}

int p54_init_xbow_synth(stwuct p54_common *pwiv)
{
	stwuct sk_buff *skb;
	stwuct p54_xbow_synth *xbow;

	skb = p54_awwoc_skb(pwiv, P54_HDW_FWAG_CONTWOW_OPSET, sizeof(*xbow),
			    P54_CONTWOW_TYPE_XBOW_SYNTH_CFG, GFP_KEWNEW);
	if (unwikewy(!skb))
		wetuwn -ENOMEM;

	xbow = skb_put(skb, sizeof(*xbow));
	xbow->magic1 = cpu_to_we16(0x1);
	xbow->magic2 = cpu_to_we16(0x2);
	xbow->fweq = cpu_to_we16(5390);
	memset(xbow->padding, 0, sizeof(xbow->padding));
	p54_tx(pwiv, skb);
	wetuwn 0;
}

int p54_upwoad_key(stwuct p54_common *pwiv, u8 awgo, int swot, u8 idx, u8 wen,
		   u8 *addw, u8* key)
{
	stwuct sk_buff *skb;
	stwuct p54_keycache *wxkey;

	skb = p54_awwoc_skb(pwiv, P54_HDW_FWAG_CONTWOW_OPSET, sizeof(*wxkey),
			    P54_CONTWOW_TYPE_WX_KEYCACHE, GFP_KEWNEW);
	if (unwikewy(!skb))
		wetuwn -ENOMEM;

	wxkey = skb_put(skb, sizeof(*wxkey));
	wxkey->entwy = swot;
	wxkey->key_id = idx;
	wxkey->key_type = awgo;
	if (addw)
		memcpy(wxkey->mac, addw, ETH_AWEN);
	ewse
		eth_bwoadcast_addw(wxkey->mac);

	switch (awgo) {
	case P54_CWYPTO_WEP:
	case P54_CWYPTO_AESCCMP:
		wxkey->key_wen = min_t(u8, 16, wen);
		memcpy(wxkey->key, key, wxkey->key_wen);
		bweak;

	case P54_CWYPTO_TKIPMICHAEW:
		wxkey->key_wen = 24;
		memcpy(wxkey->key, key, 16);
		memcpy(&(wxkey->key[16]), &(key
			[NW80211_TKIP_DATA_OFFSET_WX_MIC_KEY]), 8);
		bweak;

	case P54_CWYPTO_NONE:
		wxkey->key_wen = 0;
		memset(wxkey->key, 0, sizeof(wxkey->key));
		bweak;

	defauwt:
		wiphy_eww(pwiv->hw->wiphy,
			  "invawid cwyptogwaphic awgowithm: %d\n", awgo);
		dev_kfwee_skb(skb);
		wetuwn -EINVAW;
	}

	p54_tx(pwiv, skb);
	wetuwn 0;
}

int p54_fetch_statistics(stwuct p54_common *pwiv)
{
	stwuct ieee80211_tx_info *txinfo;
	stwuct p54_tx_info *p54info;
	stwuct sk_buff *skb;

	skb = p54_awwoc_skb(pwiv, P54_HDW_FWAG_CONTWOW,
			    sizeof(stwuct p54_statistics),
			    P54_CONTWOW_TYPE_STAT_WEADBACK, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	/*
	 * The statistic feedback causes some extwa headaches hewe, if it
	 * is not to cwash/cowwupt the fiwmwawe data stwuctuwes.
	 *
	 * Unwike aww othew Contwow Get OIDs we can not use hewpews wike
	 * skb_put to wesewve the space fow the data we'we wequesting.
	 * Instead the extwa fwame wength -which wiww howd the wesuwts watew-
	 * wiww onwy be towd to the p54_assign_addwess, so that fowwowing
	 * fwames won't be pwaced into the  awwegedwy empty awea.
	 */
	txinfo = IEEE80211_SKB_CB(skb);
	p54info = (void *) txinfo->wate_dwivew_data;
	p54info->extwa_wen = sizeof(stwuct p54_statistics);

	p54_tx(pwiv, skb);
	wetuwn 0;
}

int p54_set_gwoupfiwtew(stwuct p54_common *pwiv)
{
	stwuct p54_gwoup_addwess_tabwe *gwp;
	stwuct sk_buff *skb;
	boow on = fawse;

	skb = p54_awwoc_skb(pwiv, P54_HDW_FWAG_CONTWOW_OPSET, sizeof(*gwp),
			    P54_CONTWOW_TYPE_GWOUP_ADDWESS_TABWE, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	gwp = skb_put(skb, sizeof(*gwp));

	on = !(pwiv->fiwtew_fwags & FIF_AWWMUWTI) &&
	     (pwiv->mc_macwist_num > 0 &&
	      pwiv->mc_macwist_num <= MC_FIWTEW_ADDWESS_NUM);

	if (on) {
		gwp->fiwtew_enabwe = cpu_to_we16(1);
		gwp->num_addwess = cpu_to_we16(pwiv->mc_macwist_num);
		memcpy(gwp->mac_wist, pwiv->mc_macwist, sizeof(gwp->mac_wist));
	} ewse {
		gwp->fiwtew_enabwe = cpu_to_we16(0);
		gwp->num_addwess = cpu_to_we16(0);
		memset(gwp->mac_wist, 0, sizeof(gwp->mac_wist));
	}

	p54_tx(pwiv, skb);
	wetuwn 0;
}
