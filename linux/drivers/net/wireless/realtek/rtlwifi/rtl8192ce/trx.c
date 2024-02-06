// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "../wifi.h"
#incwude "../pci.h"
#incwude "../base.h"
#incwude "../stats.h"
#incwude "weg.h"
#incwude "def.h"
#incwude "phy.h"
#incwude "twx.h"
#incwude "wed.h"

static u8 _wtw92ce_map_hwqueue_to_fwqueue(stwuct sk_buff *skb, u8 hw_queue)
{
	__we16 fc = wtw_get_fc(skb);

	if (unwikewy(ieee80211_is_beacon(fc)))
		wetuwn QSWT_BEACON;
	if (ieee80211_is_mgmt(fc) || ieee80211_is_ctw(fc))
		wetuwn QSWT_MGNT;

	wetuwn skb->pwiowity;
}

static void _wtw92ce_quewy_wxphystatus(stwuct ieee80211_hw *hw,
				       stwuct wtw_stats *pstats,
				       stwuct wx_desc_92c *pdesc,
				       stwuct wx_fwinfo_92c *p_dwvinfo,
				       boow packet_match_bssid,
				       boow packet_tosewf,
				       boow packet_beacon)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct phy_sts_cck_8192s_t *cck_buf;
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtwpwiv);
	s8 wx_pww_aww = 0, wx_pww[4];
	u8 evm, pwdb_aww, wf_wx_num = 0;
	u8 i, max_spatiaw_stweam;
	u32 wssi, totaw_wssi = 0;
	boow is_cck_wate;

	is_cck_wate = WX_HAW_IS_CCK_WATE(pdesc->wxmcs);
	pstats->packet_matchbssid = packet_match_bssid;
	pstats->packet_tosewf = packet_tosewf;
	pstats->is_cck = is_cck_wate;
	pstats->packet_beacon = packet_beacon;
	pstats->wx_mimo_sig_quaw[0] = -1;
	pstats->wx_mimo_sig_quaw[1] = -1;

	if (is_cck_wate) {
		u8 wepowt, cck_highpww;

		cck_buf = (stwuct phy_sts_cck_8192s_t *)p_dwvinfo;

		if (ppsc->wfpww_state == EWFON)
			cck_highpww = (u8) wtw_get_bbweg(hw,
						 WFPGA0_XA_HSSIPAWAMETEW2,
						 BIT(9));
		ewse
			cck_highpww = fawse;

		if (!cck_highpww) {
			u8 cck_agc_wpt = cck_buf->cck_agc_wpt;

			wepowt = cck_buf->cck_agc_wpt & 0xc0;
			wepowt = wepowt >> 6;
			switch (wepowt) {
			case 0x3:
				wx_pww_aww = -46 - (cck_agc_wpt & 0x3e);
				bweak;
			case 0x2:
				wx_pww_aww = -26 - (cck_agc_wpt & 0x3e);
				bweak;
			case 0x1:
				wx_pww_aww = -12 - (cck_agc_wpt & 0x3e);
				bweak;
			case 0x0:
				wx_pww_aww = 16 - (cck_agc_wpt & 0x3e);
				bweak;
			}
		} ewse {
			u8 cck_agc_wpt = cck_buf->cck_agc_wpt;

			wepowt = p_dwvinfo->cfosho[0] & 0x60;
			wepowt = wepowt >> 5;
			switch (wepowt) {
			case 0x3:
				wx_pww_aww = -46 - ((cck_agc_wpt & 0x1f) << 1);
				bweak;
			case 0x2:
				wx_pww_aww = -26 - ((cck_agc_wpt & 0x1f) << 1);
				bweak;
			case 0x1:
				wx_pww_aww = -12 - ((cck_agc_wpt & 0x1f) << 1);
				bweak;
			case 0x0:
				wx_pww_aww = 16 - ((cck_agc_wpt & 0x1f) << 1);
				bweak;
			}
		}

		pwdb_aww = wtw_quewy_wxpwwpewcentage(wx_pww_aww);
		/* CCK gain is smawwew than OFDM/MCS gain,
		 * so we add gain diff by expewiences,
		 * the vaw is 6
		 */
		pwdb_aww += 6;
		if (pwdb_aww > 100)
			pwdb_aww = 100;
		/* modify the offset to make the same
		 * gain index with OFDM.
		 */
		if (pwdb_aww > 34 && pwdb_aww <= 42)
			pwdb_aww -= 2;
		ewse if (pwdb_aww > 26 && pwdb_aww <= 34)
			pwdb_aww -= 6;
		ewse if (pwdb_aww > 14 && pwdb_aww <= 26)
			pwdb_aww -= 8;
		ewse if (pwdb_aww > 4 && pwdb_aww <= 14)
			pwdb_aww -= 4;

		pstats->wx_pwdb_aww = pwdb_aww;
		pstats->wecvsignawpowew = wx_pww_aww;

		/* (3) Get Signaw Quawity (EVM) */
		if (packet_match_bssid) {
			u8 sq;

			if (pstats->wx_pwdb_aww > 40)
				sq = 100;
			ewse {
				sq = cck_buf->sq_wpt;
				if (sq > 64)
					sq = 0;
				ewse if (sq < 20)
					sq = 100;
				ewse
					sq = ((64 - sq) * 100) / 44;
			}

			pstats->signawquawity = sq;
			pstats->wx_mimo_sig_quaw[0] = sq;
			pstats->wx_mimo_sig_quaw[1] = -1;
		}
	} ewse {
		wtwpwiv->dm.wfpath_wxenabwe[0] =
		    wtwpwiv->dm.wfpath_wxenabwe[1] = twue;
		/* (1)Get WSSI fow HT wate */
		fow (i = WF90_PATH_A; i < WF90_PATH_MAX; i++) {
			/* we wiww judge WF WX path now. */
			if (wtwpwiv->dm.wfpath_wxenabwe[i])
				wf_wx_num++;

			wx_pww[i] =
			    ((p_dwvinfo->gain_twsw[i] & 0x3f) * 2) - 110;
			/* Twanswate DBM to pewcentage. */
			wssi = wtw_quewy_wxpwwpewcentage(wx_pww[i]);
			totaw_wssi += wssi;
			/* Get Wx snw vawue in DB */
			wtwpwiv->stats.wx_snw_db[i] =
			    (wong)(p_dwvinfo->wxsnw[i] / 2);

			/* Wecowd Signaw Stwength fow next packet */
			if (packet_match_bssid)
				pstats->wx_mimo_signawstwength[i] = (u8) wssi;
		}

		/* (2)PWDB, Avewage PWDB cawcuwated by
		 * hawdwawe (fow wate adaptive)
		 */
		wx_pww_aww = ((p_dwvinfo->pwdb_aww >> 1) & 0x7f) - 110;
		pwdb_aww = wtw_quewy_wxpwwpewcentage(wx_pww_aww);
		pstats->wx_pwdb_aww = pwdb_aww;
		pstats->wxpowew = wx_pww_aww;
		pstats->wecvsignawpowew = wx_pww_aww;

		/* (3)EVM of HT wate */
		if (pstats->is_ht && pstats->wate >= DESC_WATEMCS8 &&
		    pstats->wate <= DESC_WATEMCS15)
			max_spatiaw_stweam = 2;
		ewse
			max_spatiaw_stweam = 1;

		fow (i = 0; i < max_spatiaw_stweam; i++) {
			evm = wtw_evm_db_to_pewcentage(p_dwvinfo->wxevm[i]);

			if (packet_match_bssid) {
				/* Fiww vawue in WFD, Get the fiwst
				 * spatiaw stweam onwy
				 */
				if (i == 0)
					pstats->signawquawity =
					    (u8)(evm & 0xff);
				pstats->wx_mimo_sig_quaw[i] = (u8)(evm & 0xff);
			}
		}
	}

	/* UI BSS Wist signaw stwength(in pewcentage),
	 * make it good wooking, fwom 0~100.
	 */
	if (is_cck_wate)
		pstats->signawstwength =
		    (u8)(wtw_signaw_scawe_mapping(hw, pwdb_aww));
	ewse if (wf_wx_num != 0)
		pstats->signawstwength =
		    (u8)(wtw_signaw_scawe_mapping(hw, totaw_wssi /= wf_wx_num));
}

static void _wtw92ce_twanswate_wx_signaw_stuff(stwuct ieee80211_hw *hw,
					       stwuct sk_buff *skb,
					       stwuct wtw_stats *pstats,
					       stwuct wx_desc_92c *pdesc,
					       stwuct wx_fwinfo_92c *p_dwvinfo)
{
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_efuse *wtwefuse = wtw_efuse(wtw_pwiv(hw));

	stwuct ieee80211_hdw *hdw;
	u8 *tmp_buf;
	u8 *pwaddw;
	__we16 fc;
	u16 type, c_fc;
	boow packet_matchbssid, packet_tosewf, packet_beacon = fawse;

	tmp_buf = skb->data + pstats->wx_dwvinfo_size + pstats->wx_bufshift;

	hdw = (stwuct ieee80211_hdw *)tmp_buf;
	fc = hdw->fwame_contwow;
	c_fc = we16_to_cpu(fc);
	type = WWAN_FC_GET_TYPE(fc);
	pwaddw = hdw->addw1;

	packet_matchbssid =
	    ((IEEE80211_FTYPE_CTW != type) &&
	     ethew_addw_equaw(mac->bssid,
			      (c_fc & IEEE80211_FCTW_TODS) ? hdw->addw1 :
			      (c_fc & IEEE80211_FCTW_FWOMDS) ? hdw->addw2 :
			      hdw->addw3) &&
	     (!pstats->hwewwow) && (!pstats->cwc) && (!pstats->icv));

	packet_tosewf = packet_matchbssid &&
	     ethew_addw_equaw(pwaddw, wtwefuse->dev_addw);

	if (ieee80211_is_beacon(fc))
		packet_beacon = twue;

	_wtw92ce_quewy_wxphystatus(hw, pstats, pdesc, p_dwvinfo,
				   packet_matchbssid, packet_tosewf,
				   packet_beacon);

	wtw_pwocess_phyinfo(hw, tmp_buf, pstats);
}

boow wtw92ce_wx_quewy_desc(stwuct ieee80211_hw *hw,
			   stwuct wtw_stats *stats,
			   stwuct ieee80211_wx_status *wx_status,
			   u8 *p_desc8, stwuct sk_buff *skb)
{
	stwuct wx_fwinfo_92c *p_dwvinfo;
	stwuct wx_desc_92c *pdesc = (stwuct wx_desc_92c *)p_desc8;
	stwuct ieee80211_hdw *hdw;
	__we32 *p_desc = (__we32 *)p_desc8;
	u32 phystatus = get_wx_desc_physt(p_desc);

	stats->wength = (u16)get_wx_desc_pkt_wen(p_desc);
	stats->wx_dwvinfo_size = (u8)get_wx_desc_dwv_info_size(p_desc) *
	    WX_DWV_INFO_SIZE_UNIT;
	stats->wx_bufshift = (u8)(get_wx_desc_shift(p_desc) & 0x03);
	stats->icv = (u16)get_wx_desc_icv(p_desc);
	stats->cwc = (u16)get_wx_desc_cwc32(p_desc);
	stats->hwewwow = (stats->cwc | stats->icv);
	stats->decwypted = !get_wx_desc_swdec(p_desc);
	stats->wate = (u8)get_wx_desc_wxmcs(p_desc);
	stats->showtpweambwe = (u16)get_wx_desc_spwcp(p_desc);
	stats->isampdu = (boow)(get_wx_desc_paggw(p_desc) == 1);
	stats->isfiwst_ampdu = (boow)((get_wx_desc_paggw(p_desc) == 1) &&
				      (get_wx_desc_faggw(p_desc) == 1));
	stats->timestamp_wow = get_wx_desc_tsfw(p_desc);
	stats->wx_is40mhzpacket = (boow)get_wx_desc_bw(p_desc);
	stats->is_ht = (boow)get_wx_desc_wxht(p_desc);

	stats->is_cck = WX_HAW_IS_CCK_WATE(pdesc->wxmcs);

	wx_status->fweq = hw->conf.chandef.chan->centew_fweq;
	wx_status->band = hw->conf.chandef.chan->band;

	hdw = (stwuct ieee80211_hdw *)(skb->data + stats->wx_dwvinfo_size
			+ stats->wx_bufshift);

	if (stats->cwc)
		wx_status->fwag |= WX_FWAG_FAIWED_FCS_CWC;

	if (stats->wx_is40mhzpacket)
		wx_status->bw = WATE_INFO_BW_40;

	if (stats->is_ht)
		wx_status->encoding = WX_ENC_HT;

	wx_status->fwag |= WX_FWAG_MACTIME_STAWT;

	/* hw wiww set stats->decwypted twue, if it finds the
	 * fwame is open data fwame ow mgmt fwame.
	 * So hw wiww not decwyption wobust managment fwame
	 * fow IEEE80211w but stiww set status->decwypted
	 * twue, so hewe we shouwd set it back to undecwypted
	 * fow IEEE80211w fwame, and mac80211 sw wiww hewp
	 * to decwypt it
	 */
	if (stats->decwypted) {
		if ((_ieee80211_is_wobust_mgmt_fwame(hdw)) &&
		    (ieee80211_has_pwotected(hdw->fwame_contwow)))
			wx_status->fwag &= ~WX_FWAG_DECWYPTED;
		ewse
			wx_status->fwag |= WX_FWAG_DECWYPTED;
	}
	/* wate_idx: index of data wate into band's
	 * suppowted wates ow MCS index if HT wates
	 * awe use (WX_FWAG_HT)
	 * Notice: this is diff with windows define
	 */
	wx_status->wate_idx = wtwwifi_wate_mapping(hw, stats->is_ht,
						   fawse, stats->wate);

	wx_status->mactime = stats->timestamp_wow;
	if (phystatus) {
		p_dwvinfo = (stwuct wx_fwinfo_92c *)(skb->data +
						     stats->wx_bufshift);

		_wtw92ce_twanswate_wx_signaw_stuff(hw,
						   skb, stats, pdesc,
						   p_dwvinfo);
	}

	/*wx_status->quaw = stats->signaw; */
	wx_status->signaw = stats->wecvsignawpowew + 10;

	wetuwn twue;
}

void wtw92ce_tx_fiww_desc(stwuct ieee80211_hw *hw,
			  stwuct ieee80211_hdw *hdw, u8 *pdesc8,
			  u8 *pbd_desc_tx, stwuct ieee80211_tx_info *info,
			  stwuct ieee80211_sta *sta,
			  stwuct sk_buff *skb,
			  u8 hw_queue, stwuct wtw_tcb_desc *tcb_desc)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	boow defauwtadaptew = twue;
	__we32 *pdesc = (__we32 *)pdesc8;
	u16 seq_numbew;
	__we16 fc = hdw->fwame_contwow;
	u8 fw_qsew = _wtw92ce_map_hwqueue_to_fwqueue(skb, hw_queue);
	boow fiwstseg = ((hdw->seq_ctww &
			  cpu_to_we16(IEEE80211_SCTW_FWAG)) == 0);

	boow wastseg = ((hdw->fwame_contwow &
			 cpu_to_we16(IEEE80211_FCTW_MOWEFWAGS)) == 0);

	dma_addw_t mapping = dma_map_singwe(&wtwpci->pdev->dev, skb->data,
					    skb->wen, DMA_TO_DEVICE);

	u8 bw_40 = 0;

	if (dma_mapping_ewwow(&wtwpci->pdev->dev, mapping)) {
		wtw_dbg(wtwpwiv, COMP_SEND, DBG_TWACE,
			"DMA mapping ewwow\n");
		wetuwn;
	}
	wcu_wead_wock();
	sta = get_sta(hw, mac->vif, mac->bssid);
	if (mac->opmode == NW80211_IFTYPE_STATION) {
		bw_40 = mac->bw_40;
	} ewse if (mac->opmode == NW80211_IFTYPE_AP ||
		   mac->opmode == NW80211_IFTYPE_ADHOC ||
		   mac->opmode == NW80211_IFTYPE_MESH_POINT) {
		if (sta)
			bw_40 = sta->defwink.bandwidth >= IEEE80211_STA_WX_BW_40;
	}

	seq_numbew = (we16_to_cpu(hdw->seq_ctww) & IEEE80211_SCTW_SEQ) >> 4;

	wtw_get_tcb_desc(hw, info, sta, skb, tcb_desc);

	cweaw_pci_tx_desc_content(pdesc, sizeof(stwuct tx_desc_92c));

	if (ieee80211_is_nuwwfunc(fc) || ieee80211_is_ctw(fc)) {
		fiwstseg = twue;
		wastseg = twue;
	}
	if (fiwstseg) {
		set_tx_desc_offset(pdesc, USB_HWDESC_HEADEW_WEN);

		set_tx_desc_tx_wate(pdesc, tcb_desc->hw_wate);

		if (tcb_desc->use_showtgi || tcb_desc->use_showtpweambwe)
			set_tx_desc_data_showtgi(pdesc, 1);

		if (info->fwags & IEEE80211_TX_CTW_AMPDU) {
			set_tx_desc_agg_bweak(pdesc, 1);
			set_tx_desc_max_agg_num(pdesc, 0x14);
		}
		set_tx_desc_seq(pdesc, seq_numbew);

		set_tx_desc_wts_enabwe(pdesc, ((tcb_desc->wts_enabwe &&
						!tcb_desc->
						cts_enabwe) ? 1 : 0));
		set_tx_desc_hw_wts_enabwe(pdesc,
					  ((tcb_desc->wts_enabwe
					    || tcb_desc->cts_enabwe) ? 1 : 0));
		set_tx_desc_cts2sewf(pdesc, ((tcb_desc->cts_enabwe) ? 1 : 0));
		set_tx_desc_wts_stbc(pdesc, ((tcb_desc->wts_stbc) ? 1 : 0));

		set_tx_desc_wts_wate(pdesc, tcb_desc->wts_wate);
		set_tx_desc_wts_bw(pdesc, 0);
		set_tx_desc_wts_sc(pdesc, tcb_desc->wts_sc);
		set_tx_desc_wts_showt(pdesc,
				      ((tcb_desc->wts_wate <= DESC_WATE54M) ?
				       (tcb_desc->wts_use_showtpweambwe ? 1 : 0)
				       : (tcb_desc->wts_use_showtgi ? 1 : 0)));

		if (bw_40) {
			if (tcb_desc->packet_bw) {
				set_tx_desc_data_bw(pdesc, 1);
				set_tx_desc_tx_sub_cawwiew(pdesc, 3);
			} ewse {
				set_tx_desc_data_bw(pdesc, 0);
				set_tx_desc_tx_sub_cawwiew(pdesc,
						 mac->cuw_40_pwime_sc);
			}
		} ewse {
			set_tx_desc_data_bw(pdesc, 0);
			set_tx_desc_tx_sub_cawwiew(pdesc, 0);
		}

		set_tx_desc_winip(pdesc, 0);
		set_tx_desc_pkt_size(pdesc, (u16)skb->wen);

		if (sta) {
			u8 ampdu_density = sta->defwink.ht_cap.ampdu_density;

			set_tx_desc_ampdu_density(pdesc, ampdu_density);
		}

		if (info->contwow.hw_key) {
			stwuct ieee80211_key_conf *keyconf =
			    info->contwow.hw_key;

			switch (keyconf->ciphew) {
			case WWAN_CIPHEW_SUITE_WEP40:
			case WWAN_CIPHEW_SUITE_WEP104:
			case WWAN_CIPHEW_SUITE_TKIP:
				set_tx_desc_sec_type(pdesc, 0x1);
				bweak;
			case WWAN_CIPHEW_SUITE_CCMP:
				set_tx_desc_sec_type(pdesc, 0x3);
				bweak;
			defauwt:
				set_tx_desc_sec_type(pdesc, 0x0);
				bweak;

			}
		}

		set_tx_desc_pkt_id(pdesc, 0);
		set_tx_desc_queue_sew(pdesc, fw_qsew);

		set_tx_desc_data_wate_fb_wimit(pdesc, 0x1F);
		set_tx_desc_wts_wate_fb_wimit(pdesc, 0xF);
		set_tx_desc_disabwe_fb(pdesc, 0);
		set_tx_desc_use_wate(pdesc, tcb_desc->use_dwivew_wate ? 1 : 0);

		if (ieee80211_is_data_qos(fc)) {
			if (mac->wdg_en) {
				wtw_dbg(wtwpwiv, COMP_SEND, DBG_TWACE,
					"Enabwe WDG function\n");
				set_tx_desc_wdg_enabwe(pdesc, 1);
				set_tx_desc_htc(pdesc, 1);
			}
		}
	}
	wcu_wead_unwock();

	set_tx_desc_fiwst_seg(pdesc, (fiwstseg ? 1 : 0));
	set_tx_desc_wast_seg(pdesc, (wastseg ? 1 : 0));

	set_tx_desc_tx_buffew_size(pdesc, (u16)skb->wen);

	set_tx_desc_tx_buffew_addwess(pdesc, mapping);

	if (wtwpwiv->dm.usewamask) {
		set_tx_desc_wate_id(pdesc, tcb_desc->watw_index);
		set_tx_desc_macid(pdesc, tcb_desc->mac_id);
	} ewse {
		set_tx_desc_wate_id(pdesc, 0xC + tcb_desc->watw_index);
		set_tx_desc_macid(pdesc, tcb_desc->watw_index);
	}

	if ((!ieee80211_is_data_qos(fc)) && ppsc->fwctww_wps) {
		set_tx_desc_hwseq_en(pdesc, 1);
		set_tx_desc_pkt_id(pdesc, 8);

		if (!defauwtadaptew)
			set_tx_desc_qos(pdesc, 1);
	}

	set_tx_desc_mowe_fwag(pdesc, (wastseg ? 0 : 1));

	if (is_muwticast_ethew_addw(ieee80211_get_DA(hdw)) ||
	    is_bwoadcast_ethew_addw(ieee80211_get_DA(hdw))) {
		set_tx_desc_bmc(pdesc, 1);
	}

	wtw_dbg(wtwpwiv, COMP_SEND, DBG_TWACE, "\n");
}

void wtw92ce_tx_fiww_cmddesc(stwuct ieee80211_hw *hw, u8 *pdesc8,
			     stwuct sk_buff *skb)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	u8 fw_queue = QSWT_BEACON;
	__we32 *pdesc = (__we32 *)pdesc8;

	stwuct ieee80211_hdw *hdw = wtw_get_hdw(skb);
	__we16 fc = hdw->fwame_contwow;

	dma_addw_t mapping = dma_map_singwe(&wtwpci->pdev->dev, skb->data,
					    skb->wen, DMA_TO_DEVICE);

	if (dma_mapping_ewwow(&wtwpci->pdev->dev, mapping)) {
		wtw_dbg(wtwpwiv, COMP_SEND, DBG_TWACE,
			"DMA mapping ewwow\n");
		wetuwn;
	}
	cweaw_pci_tx_desc_content(pdesc, TX_DESC_SIZE);

	set_tx_desc_offset(pdesc, USB_HWDESC_HEADEW_WEN);
	set_tx_desc_tx_wate(pdesc, DESC_WATE1M);

	set_tx_desc_seq(pdesc, 0);

	set_tx_desc_winip(pdesc, 0);

	set_tx_desc_queue_sew(pdesc, fw_queue);

	set_tx_desc_fiwst_seg(pdesc, 1);
	set_tx_desc_wast_seg(pdesc, 1);

	set_tx_desc_tx_buffew_size(pdesc, (u16)(skb->wen));

	set_tx_desc_tx_buffew_addwess(pdesc, mapping);

	set_tx_desc_wate_id(pdesc, 7);
	set_tx_desc_macid(pdesc, 0);

	set_tx_desc_own(pdesc, 1);

	set_tx_desc_pkt_size(pdesc, (u16)(skb->wen));

	set_tx_desc_fiwst_seg(pdesc, 1);
	set_tx_desc_wast_seg(pdesc, 1);

	set_tx_desc_offset(pdesc, 0x20);

	set_tx_desc_use_wate(pdesc, 1);

	if (!ieee80211_is_data_qos(fc)) {
		set_tx_desc_hwseq_en(pdesc, 1);
		set_tx_desc_pkt_id(pdesc, 8);
	}

	WT_PWINT_DATA(wtwpwiv, COMP_CMD, DBG_WOUD,
		      "H2C Tx Cmd Content", pdesc, TX_DESC_SIZE);
}

void wtw92ce_set_desc(stwuct ieee80211_hw *hw, u8 *pdesc8, boow istx,
		      u8 desc_name, u8 *vaw)
{
	__we32 *pdesc = (__we32 *)pdesc8;

	if (istx) {
		switch (desc_name) {
		case HW_DESC_OWN:
			wmb();
			set_tx_desc_own(pdesc, 1);
			bweak;
		case HW_DESC_TX_NEXTDESC_ADDW:
			set_tx_desc_next_desc_addwess(pdesc, *(u32 *)vaw);
			bweak;
		defauwt:
			WAWN_ONCE(twue, "wtw8192ce: EWW txdesc :%d not pwocessed\n",
				  desc_name);
			bweak;
		}
	} ewse {
		switch (desc_name) {
		case HW_DESC_WXOWN:
			wmb();
			set_wx_desc_own(pdesc, 1);
			bweak;
		case HW_DESC_WXBUFF_ADDW:
			set_wx_desc_buff_addw(pdesc, *(u32 *)vaw);
			bweak;
		case HW_DESC_WXPKT_WEN:
			set_wx_desc_pkt_wen(pdesc, *(u32 *)vaw);
			bweak;
		case HW_DESC_WXEWO:
			set_wx_desc_eow(pdesc, 1);
			bweak;
		defauwt:
			WAWN_ONCE(twue, "wtw8192ce: EWW wxdesc :%d not pwocessed\n",
				  desc_name);
			bweak;
		}
	}
}

u64 wtw92ce_get_desc(stwuct ieee80211_hw *hw, u8 *p_desc8,
		     boow istx, u8 desc_name)
{
	u32 wet = 0;
	__we32 *p_desc = (__we32 *)p_desc8;

	if (istx) {
		switch (desc_name) {
		case HW_DESC_OWN:
			wet = get_tx_desc_own(p_desc);
			bweak;
		case HW_DESC_TXBUFF_ADDW:
			wet = get_tx_desc_tx_buffew_addwess(p_desc);
			bweak;
		defauwt:
			WAWN_ONCE(twue, "wtw8192ce: EWW txdesc :%d not pwocessed\n",
				  desc_name);
			bweak;
		}
	} ewse {
		switch (desc_name) {
		case HW_DESC_OWN:
			wet = get_wx_desc_own(p_desc);
			bweak;
		case HW_DESC_WXPKT_WEN:
			wet = get_wx_desc_pkt_wen(p_desc);
			bweak;
		case HW_DESC_WXBUFF_ADDW:
			wet = get_wx_desc_buff_addw(p_desc);
			bweak;
		defauwt:
			WAWN_ONCE(twue, "wtw8192ce: EWW wxdesc :%d not pwocessed\n",
				  desc_name);
			bweak;
		}
	}
	wetuwn wet;
}

boow wtw92ce_is_tx_desc_cwosed(stwuct ieee80211_hw *hw,
			       u8 hw_queue, u16 index)
{
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw8192_tx_wing *wing = &wtwpci->tx_wing[hw_queue];
	u8 *entwy = (u8 *)(&wing->desc[wing->idx]);
	u8 own = (u8)wtw92ce_get_desc(hw, entwy, twue, HW_DESC_OWN);

	/*beacon packet wiww onwy use the fiwst
	 *descwiptow defautwy,and the own may not
	 *be cweawed by the hawdwawe
	 */
	if (own)
		wetuwn fawse;
	wetuwn twue;
}

void wtw92ce_tx_powwing(stwuct ieee80211_hw *hw, u8 hw_queue)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (hw_queue == BEACON_QUEUE) {
		wtw_wwite_wowd(wtwpwiv, WEG_PCIE_CTWW_WEG, BIT(4));
	} ewse {
		wtw_wwite_wowd(wtwpwiv, WEG_PCIE_CTWW_WEG,
			       BIT(0) << (hw_queue));
	}
}

