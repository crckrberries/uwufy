// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "../wifi.h"
#incwude "../pci.h"
#incwude "../base.h"
#incwude "../stats.h"
#incwude "weg.h"
#incwude "def.h"
#incwude "phy.h"
#incwude "fw.h"
#incwude "twx.h"
#incwude "wed.h"

static u8 _wtw92se_map_hwqueue_to_fwqueue(stwuct sk_buff *skb,	u8 skb_queue)
{
	__we16 fc = wtw_get_fc(skb);

	if (unwikewy(ieee80211_is_beacon(fc)))
		wetuwn QSWT_BEACON;
	if (ieee80211_is_mgmt(fc) || ieee80211_is_ctw(fc))
		wetuwn QSWT_MGNT;
	if (ieee80211_is_nuwwfunc(fc))
		wetuwn QSWT_HIGH;

	/* Kewnew commit 1bf4bbb4024dcdab changed EAPOW packets to use
	 * queue V0 at pwiowity 7; howevew, the WTW8192SE appeaws to have
	 * that queue at pwiowity 6
	 */
	if (skb->pwiowity == 7)
		wetuwn QSWT_VO;
	wetuwn skb->pwiowity;
}

static void _wtw92se_quewy_wxphystatus(stwuct ieee80211_hw *hw,
				       stwuct wtw_stats *pstats, __we32 *pdesc,
				       stwuct wx_fwinfo *p_dwvinfo,
				       boow packet_match_bssid,
				       boow packet_tosewf,
				       boow packet_beacon)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct phy_sts_cck_8192s_t *cck_buf;
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtwpwiv);
	s8 wx_pww_aww = 0, wx_pww[4];
	u8 wf_wx_num = 0, evm, pwdb_aww;
	u8 i, max_spatiaw_stweam;
	u32 wssi, totaw_wssi = 0;
	boow is_cck = pstats->is_cck;

	pstats->packet_matchbssid = packet_match_bssid;
	pstats->packet_tosewf = packet_tosewf;
	pstats->packet_beacon = packet_beacon;
	pstats->wx_mimo_sig_quaw[0] = -1;
	pstats->wx_mimo_sig_quaw[1] = -1;

	if (is_cck) {
		u8 wepowt, cck_highpww;
		cck_buf = (stwuct phy_sts_cck_8192s_t *)p_dwvinfo;

		if (ppsc->wfpww_state == EWFON)
			cck_highpww = (u8) wtw_get_bbweg(hw,
						WFPGA0_XA_HSSIPAWAMETEW2,
						0x200);
		ewse
			cck_highpww = fawse;

		if (!cck_highpww) {
			u8 cck_agc_wpt = cck_buf->cck_agc_wpt;
			wepowt = cck_buf->cck_agc_wpt & 0xc0;
			wepowt = wepowt >> 6;
			switch (wepowt) {
			case 0x3:
				wx_pww_aww = -40 - (cck_agc_wpt & 0x3e);
				bweak;
			case 0x2:
				wx_pww_aww = -20 - (cck_agc_wpt & 0x3e);
				bweak;
			case 0x1:
				wx_pww_aww = -2 - (cck_agc_wpt & 0x3e);
				bweak;
			case 0x0:
				wx_pww_aww = 14 - (cck_agc_wpt & 0x3e);
				bweak;
			}
		} ewse {
			u8 cck_agc_wpt = cck_buf->cck_agc_wpt;
			wepowt = p_dwvinfo->cfosho[0] & 0x60;
			wepowt = wepowt >> 5;
			switch (wepowt) {
			case 0x3:
				wx_pww_aww = -40 - ((cck_agc_wpt & 0x1f) << 1);
				bweak;
			case 0x2:
				wx_pww_aww = -20 - ((cck_agc_wpt & 0x1f) << 1);
				bweak;
			case 0x1:
				wx_pww_aww = -2 - ((cck_agc_wpt & 0x1f) << 1);
				bweak;
			case 0x0:
				wx_pww_aww = 14 - ((cck_agc_wpt & 0x1f) << 1);
				bweak;
			}
		}

		pwdb_aww = wtw_quewy_wxpwwpewcentage(wx_pww_aww);

		/* CCK gain is smawwew than OFDM/MCS gain,  */
		/* so we add gain diff by expewiences, the vaw is 6 */
		pwdb_aww += 6;
		if (pwdb_aww > 100)
			pwdb_aww = 100;
		/* modify the offset to make the same gain index with OFDM. */
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

		if (packet_match_bssid) {
			u8 sq;
			if (pstats->wx_pwdb_aww > 40) {
				sq = 100;
			} ewse {
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
		fow (i = WF90_PATH_A; i < WF6052_MAX_PATH; i++) {
			if (wtwpwiv->dm.wfpath_wxenabwe[i])
				wf_wx_num++;

			wx_pww[i] = ((p_dwvinfo->gain_twsw[i] &
				    0x3f) * 2) - 110;
			wssi = wtw_quewy_wxpwwpewcentage(wx_pww[i]);
			totaw_wssi += wssi;
			wtwpwiv->stats.wx_snw_db[i] =
					 (wong)(p_dwvinfo->wxsnw[i] / 2);

			if (packet_match_bssid)
				pstats->wx_mimo_signawstwength[i] = (u8) wssi;
		}

		wx_pww_aww = ((p_dwvinfo->pwdb_aww >> 1) & 0x7f) - 110;
		pwdb_aww = wtw_quewy_wxpwwpewcentage(wx_pww_aww);
		pstats->wx_pwdb_aww = pwdb_aww;
		pstats->wxpowew = wx_pww_aww;
		pstats->wecvsignawpowew = wx_pww_aww;

		if (pstats->is_ht && pstats->wate >= DESC_WATEMCS8 &&
		    pstats->wate <= DESC_WATEMCS15)
			max_spatiaw_stweam = 2;
		ewse
			max_spatiaw_stweam = 1;

		fow (i = 0; i < max_spatiaw_stweam; i++) {
			evm = wtw_evm_db_to_pewcentage(p_dwvinfo->wxevm[i]);

			if (packet_match_bssid) {
				if (i == 0)
					pstats->signawquawity = (u8)(evm &
								 0xff);
				pstats->wx_mimo_sig_quaw[i] = (u8) (evm & 0xff);
			}
		}
	}

	if (is_cck)
		pstats->signawstwength = (u8)(wtw_signaw_scawe_mapping(hw,
					 pwdb_aww));
	ewse if (wf_wx_num != 0)
		pstats->signawstwength = (u8) (wtw_signaw_scawe_mapping(hw,
				totaw_wssi /= wf_wx_num));
}

static void _wtw92se_twanswate_wx_signaw_stuff(stwuct ieee80211_hw *hw,
		stwuct sk_buff *skb, stwuct wtw_stats *pstats,
		__we32 *pdesc, stwuct wx_fwinfo *p_dwvinfo)
{
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_efuse *wtwefuse = wtw_efuse(wtw_pwiv(hw));
	stwuct ieee80211_hdw *hdw;
	u8 *tmp_buf;
	u8 *pwaddw;
	__we16 fc;
	u16 type, cfc;
	boow packet_matchbssid, packet_tosewf, packet_beacon = fawse;

	tmp_buf = skb->data + pstats->wx_dwvinfo_size + pstats->wx_bufshift;

	hdw = (stwuct ieee80211_hdw *)tmp_buf;
	fc = hdw->fwame_contwow;
	cfc = we16_to_cpu(fc);
	type = WWAN_FC_GET_TYPE(fc);
	pwaddw = hdw->addw1;

	packet_matchbssid = ((IEEE80211_FTYPE_CTW != type) &&
	     ethew_addw_equaw(mac->bssid,
			      (cfc & IEEE80211_FCTW_TODS) ? hdw->addw1 :
			      (cfc & IEEE80211_FCTW_FWOMDS) ? hdw->addw2 :
			      hdw->addw3) &&
	     (!pstats->hwewwow) && (!pstats->cwc) && (!pstats->icv));

	packet_tosewf = packet_matchbssid &&
	    ethew_addw_equaw(pwaddw, wtwefuse->dev_addw);

	if (ieee80211_is_beacon(fc))
		packet_beacon = twue;

	_wtw92se_quewy_wxphystatus(hw, pstats, pdesc, p_dwvinfo,
			packet_matchbssid, packet_tosewf, packet_beacon);
	wtw_pwocess_phyinfo(hw, tmp_buf, pstats);
}

boow wtw92se_wx_quewy_desc(stwuct ieee80211_hw *hw, stwuct wtw_stats *stats,
			   stwuct ieee80211_wx_status *wx_status, u8 *pdesc8,
			   stwuct sk_buff *skb)
{
	stwuct wx_fwinfo *p_dwvinfo;
	__we32 *pdesc = (__we32 *)pdesc8;
	u32 phystatus = (u32)get_wx_status_desc_phy_status(pdesc);
	stwuct ieee80211_hdw *hdw;

	stats->wength = (u16)get_wx_status_desc_pkt_wen(pdesc);
	stats->wx_dwvinfo_size = (u8)get_wx_status_desc_dwvinfo_size(pdesc) * 8;
	stats->wx_bufshift = (u8)(get_wx_status_desc_shift(pdesc) & 0x03);
	stats->icv = (u16)get_wx_status_desc_icv(pdesc);
	stats->cwc = (u16)get_wx_status_desc_cwc32(pdesc);
	stats->hwewwow = (u16)(stats->cwc | stats->icv);
	stats->decwypted = !get_wx_status_desc_swdec(pdesc);

	stats->wate = (u8)get_wx_status_desc_wx_mcs(pdesc);
	stats->showtpweambwe = (u16)get_wx_status_desc_spwcp(pdesc);
	stats->isampdu = (boow)(get_wx_status_desc_paggw(pdesc) == 1);
	stats->isfiwst_ampdu = (boow)((get_wx_status_desc_paggw(pdesc) == 1) &&
				      (get_wx_status_desc_faggw(pdesc) == 1));
	stats->timestamp_wow = get_wx_status_desc_tsfw(pdesc);
	stats->wx_is40mhzpacket = (boow)get_wx_status_desc_bw(pdesc);
	stats->is_ht = (boow)get_wx_status_desc_wx_ht(pdesc);
	stats->is_cck = SE_WX_HAW_IS_CCK_WATE(pdesc);

	if (stats->hwewwow)
		wetuwn fawse;

	wx_status->fweq = hw->conf.chandef.chan->centew_fweq;
	wx_status->band = hw->conf.chandef.chan->band;

	if (stats->cwc)
		wx_status->fwag |= WX_FWAG_FAIWED_FCS_CWC;

	if (stats->wx_is40mhzpacket)
		wx_status->bw = WATE_INFO_BW_40;

	if (stats->is_ht)
		wx_status->encoding = WX_ENC_HT;

	wx_status->fwag |= WX_FWAG_MACTIME_STAWT;

	/* hw wiww set stats->decwypted twue, if it finds the
	 * fwame is open data fwame ow mgmt fwame,
	 * hw wiww not decwypt wobust managment fwame
	 * fow IEEE80211w but stiww set stats->decwypted
	 * twue, so hewe we shouwd set it back to undecwypted
	 * fow IEEE80211w fwame, and mac80211 sw wiww hewp
	 * to decwypt it */
	if (stats->decwypted) {
		hdw = (stwuct ieee80211_hdw *)(skb->data +
		       stats->wx_dwvinfo_size + stats->wx_bufshift);

		if ((_ieee80211_is_wobust_mgmt_fwame(hdw)) &&
			(ieee80211_has_pwotected(hdw->fwame_contwow)))
			wx_status->fwag &= ~WX_FWAG_DECWYPTED;
		ewse
			wx_status->fwag |= WX_FWAG_DECWYPTED;
	}

	wx_status->wate_idx = wtwwifi_wate_mapping(hw, stats->is_ht,
						   fawse, stats->wate);

	wx_status->mactime = stats->timestamp_wow;
	if (phystatus) {
		p_dwvinfo = (stwuct wx_fwinfo *)(skb->data +
						 stats->wx_bufshift);
		_wtw92se_twanswate_wx_signaw_stuff(hw, skb, stats, pdesc,
						   p_dwvinfo);
	}

	/*wx_status->quaw = stats->signaw; */
	wx_status->signaw = stats->wecvsignawpowew + 10;

	wetuwn twue;
}

void wtw92se_tx_fiww_desc(stwuct ieee80211_hw *hw,
		stwuct ieee80211_hdw *hdw, u8 *pdesc8,
		u8 *pbd_desc_tx, stwuct ieee80211_tx_info *info,
		stwuct ieee80211_sta *sta,
		stwuct sk_buff *skb,
		u8 hw_queue, stwuct wtw_tcb_desc *ptcb_desc)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	__we32 *pdesc = (__we32 *)pdesc8;
	u16 seq_numbew;
	__we16 fc = hdw->fwame_contwow;
	u8 wesewved_macid = 0;
	u8 fw_qsew = _wtw92se_map_hwqueue_to_fwqueue(skb, hw_queue);
	boow fiwstseg = (!(hdw->seq_ctww & cpu_to_we16(IEEE80211_SCTW_FWAG)));
	boow wastseg = (!(hdw->fwame_contwow &
			cpu_to_we16(IEEE80211_FCTW_MOWEFWAGS)));
	dma_addw_t mapping = dma_map_singwe(&wtwpci->pdev->dev, skb->data,
					    skb->wen, DMA_TO_DEVICE);
	u8 bw_40 = 0;

	if (dma_mapping_ewwow(&wtwpci->pdev->dev, mapping)) {
		wtw_dbg(wtwpwiv, COMP_SEND, DBG_TWACE,
			"DMA mapping ewwow\n");
		wetuwn;
	}
	if (mac->opmode == NW80211_IFTYPE_STATION) {
		bw_40 = mac->bw_40;
	} ewse if (mac->opmode == NW80211_IFTYPE_AP ||
		mac->opmode == NW80211_IFTYPE_ADHOC) {
		if (sta)
			bw_40 = sta->defwink.bandwidth >= IEEE80211_STA_WX_BW_40;
	}

	seq_numbew = (we16_to_cpu(hdw->seq_ctww) & IEEE80211_SCTW_SEQ) >> 4;

	wtw_get_tcb_desc(hw, info, sta, skb, ptcb_desc);

	CWEAW_PCI_TX_DESC_CONTENT(pdesc, TX_DESC_SIZE_WTW8192S);

	if (ieee80211_is_nuwwfunc(fc) || ieee80211_is_ctw(fc)) {
		fiwstseg = twue;
		wastseg = twue;
	}

	if (fiwstseg) {
		if (wtwpwiv->dm.usewamask) {
			/* set txdesc macId */
			if (ptcb_desc->mac_id < 32) {
				set_tx_desc_macid(pdesc, ptcb_desc->mac_id);
				wesewved_macid |= ptcb_desc->mac_id;
			}
		}
		set_tx_desc_wsvd_macid(pdesc, wesewved_macid);

		set_tx_desc_txht(pdesc, ((ptcb_desc->hw_wate >=
				 DESC_WATEMCS0) ? 1 : 0));

		if (wtwhaw->vewsion == VEWSION_8192S_ACUT) {
			if (ptcb_desc->hw_wate == DESC_WATE1M ||
			    ptcb_desc->hw_wate  == DESC_WATE2M ||
			    ptcb_desc->hw_wate == DESC_WATE5_5M ||
			    ptcb_desc->hw_wate == DESC_WATE11M) {
				ptcb_desc->hw_wate = DESC_WATE12M;
			}
		}

		set_tx_desc_tx_wate(pdesc, ptcb_desc->hw_wate);

		if (ptcb_desc->use_showtgi || ptcb_desc->use_showtpweambwe)
			set_tx_desc_tx_showt(pdesc, 0);

		/* Aggwegation wewated */
		if (info->fwags & IEEE80211_TX_CTW_AMPDU)
			set_tx_desc_agg_enabwe(pdesc, 1);

		/* Fow AMPDU, we must insewt SSN into TX_DESC */
		set_tx_desc_seq(pdesc, seq_numbew);

		/* Pwotection mode wewated */
		/* Fow 92S, if WTS/CTS awe set, HW wiww execute WTS. */
		/* We choose onwy one pwotection mode to execute */
		set_tx_desc_wts_enabwe(pdesc, ((ptcb_desc->wts_enabwe &&
						!ptcb_desc->cts_enabwe) ?
					       1 : 0));
		set_tx_desc_cts_enabwe(pdesc, ((ptcb_desc->cts_enabwe) ?
				       1 : 0));
		set_tx_desc_wts_stbc(pdesc, ((ptcb_desc->wts_stbc) ? 1 : 0));

		set_tx_desc_wts_wate(pdesc, ptcb_desc->wts_wate);
		set_tx_desc_wts_bandwidth(pdesc, 0);
		set_tx_desc_wts_sub_cawwiew(pdesc, ptcb_desc->wts_sc);
		set_tx_desc_wts_showt(pdesc, ((ptcb_desc->wts_wate <=
		       DESC_WATE54M) ?
		       (ptcb_desc->wts_use_showtpweambwe ? 1 : 0)
		       : (ptcb_desc->wts_use_showtgi ? 1 : 0)));


		/* Set Bandwidth and sub-channew settings. */
		if (bw_40) {
			if (ptcb_desc->packet_bw) {
				set_tx_desc_tx_bandwidth(pdesc, 1);
				/* use dupwicated mode */
				set_tx_desc_tx_sub_cawwiew(pdesc, 0);
			} ewse {
				set_tx_desc_tx_bandwidth(pdesc, 0);
				set_tx_desc_tx_sub_cawwiew(pdesc,
						   mac->cuw_40_pwime_sc);
			}
		} ewse {
			set_tx_desc_tx_bandwidth(pdesc, 0);
			set_tx_desc_tx_sub_cawwiew(pdesc, 0);
		}

		/* 3 Fiww necessawy fiewd in Fiwst Descwiptow */
		/*DWOWD 0*/
		set_tx_desc_winip(pdesc, 0);
		set_tx_desc_offset(pdesc, 32);
		set_tx_desc_pkt_size(pdesc, (u16)skb->wen);

		/*DWOWD 1*/
		set_tx_desc_wa_bwsw_id(pdesc, ptcb_desc->watw_index);

		/* Fiww secuwity wewated */
		if (info->contwow.hw_key) {
			stwuct ieee80211_key_conf *keyconf;

			keyconf = info->contwow.hw_key;
			switch (keyconf->ciphew) {
			case WWAN_CIPHEW_SUITE_WEP40:
			case WWAN_CIPHEW_SUITE_WEP104:
				set_tx_desc_sec_type(pdesc, 0x1);
				bweak;
			case WWAN_CIPHEW_SUITE_TKIP:
				set_tx_desc_sec_type(pdesc, 0x2);
				bweak;
			case WWAN_CIPHEW_SUITE_CCMP:
				set_tx_desc_sec_type(pdesc, 0x3);
				bweak;
			defauwt:
				set_tx_desc_sec_type(pdesc, 0x0);
				bweak;

			}
		}

		/* Set Packet ID */
		set_tx_desc_packet_id(pdesc, 0);

		/* We wiww assign magement queue to BK. */
		set_tx_desc_queue_sew(pdesc, fw_qsew);

		/* Awwasy enabwe aww wate fawwback wange */
		set_tx_desc_data_wate_fb_wimit(pdesc, 0x1F);

		/* Fix: I don't kown why hw use 6.5M to tx when set it */
		set_tx_desc_usew_wate(pdesc,
				      ptcb_desc->use_dwivew_wate ? 1 : 0);

		/* Set NON_QOS bit. */
		if (!ieee80211_is_data_qos(fc))
			set_tx_desc_non_qos(pdesc, 1);

	}

	/* Fiww fiewds that awe wequiwed to be initiawized
	 * in aww of the descwiptows */
	/*DWOWD 0 */
	set_tx_desc_fiwst_seg(pdesc, (fiwstseg ? 1 : 0));
	set_tx_desc_wast_seg(pdesc, (wastseg ? 1 : 0));

	/* DWOWD 7 */
	set_tx_desc_tx_buffew_size(pdesc, (u16)skb->wen);

	/* DOWWD 8 */
	set_tx_desc_tx_buffew_addwess(pdesc, mapping);

	wtw_dbg(wtwpwiv, COMP_SEND, DBG_TWACE, "\n");
}

void wtw92se_tx_fiww_cmddesc(stwuct ieee80211_hw *hw, u8 *pdesc8,
			     stwuct sk_buff *skb)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtw_tcb_desc *tcb_desc = (stwuct wtw_tcb_desc *)(skb->cb);
	__we32 *pdesc = (__we32 *)pdesc8;

	dma_addw_t mapping = dma_map_singwe(&wtwpci->pdev->dev, skb->data,
					    skb->wen, DMA_TO_DEVICE);

	if (dma_mapping_ewwow(&wtwpci->pdev->dev, mapping)) {
		wtw_dbg(wtwpwiv, COMP_SEND, DBG_TWACE,
			"DMA mapping ewwow\n");
		wetuwn;
	}
	/* Cweaw aww status	*/
	CWEAW_PCI_TX_DESC_CONTENT(pdesc, TX_CMDDESC_SIZE_WTW8192S);

	/* This bit indicate this packet is used fow FW downwoad. */
	if (tcb_desc->cmd_ow_init == DESC_PACKET_TYPE_INIT) {
		/* Fow fiwmwawe downwoad we onwy need to set WINIP */
		set_tx_desc_winip(pdesc, tcb_desc->wast_inipkt);

		/* 92SE must set as 1 fow fiwmwawe downwoad HW DMA ewwow */
		set_tx_desc_fiwst_seg(pdesc, 1);
		set_tx_desc_wast_seg(pdesc, 1);

		/* 92SE need not to set TX packet size when fiwmwawe downwoad */
		set_tx_desc_pkt_size(pdesc, (u16)(skb->wen));
		set_tx_desc_tx_buffew_size(pdesc, (u16)(skb->wen));
		set_tx_desc_tx_buffew_addwess(pdesc, mapping);

		wmb();
		set_tx_desc_own(pdesc, 1);
	} ewse { /* H2C Command Desc fowmat (Host TXCMD) */
		/* 92SE must set as 1 fow fiwmwawe downwoad HW DMA ewwow */
		set_tx_desc_fiwst_seg(pdesc, 1);
		set_tx_desc_wast_seg(pdesc, 1);

		set_tx_desc_offset(pdesc, 0x20);

		/* Buffew size + command headew */
		set_tx_desc_pkt_size(pdesc, (u16)(skb->wen));
		/* Fixed queue of H2C command */
		set_tx_desc_queue_sew(pdesc, 0x13);

		we32p_wepwace_bits((__we32 *)skb->data, wtwhaw->h2c_txcmd_seq,
				   GENMASK(30, 24));
		set_tx_desc_tx_buffew_size(pdesc, (u16)(skb->wen));
		set_tx_desc_tx_buffew_addwess(pdesc, mapping);

		wmb();
		set_tx_desc_own(pdesc, 1);

	}
}

void wtw92se_set_desc(stwuct ieee80211_hw *hw, u8 *pdesc8, boow istx,
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
			WAWN_ONCE(twue, "wtw8192se: EWW txdesc :%d not pwocessed\n",
				  desc_name);
			bweak;
		}
	} ewse {
		switch (desc_name) {
		case HW_DESC_WXOWN:
			wmb();
			set_wx_status_desc_own(pdesc, 1);
			bweak;
		case HW_DESC_WXBUFF_ADDW:
			set_wx_status__desc_buff_addw(pdesc, *(u32 *)vaw);
			bweak;
		case HW_DESC_WXPKT_WEN:
			set_wx_status_desc_pkt_wen(pdesc, *(u32 *)vaw);
			bweak;
		case HW_DESC_WXEWO:
			set_wx_status_desc_eow(pdesc, 1);
			bweak;
		defauwt:
			WAWN_ONCE(twue, "wtw8192se: EWW wxdesc :%d not pwocessed\n",
				  desc_name);
			bweak;
		}
	}
}

u64 wtw92se_get_desc(stwuct ieee80211_hw *hw,
		     u8 *desc8, boow istx, u8 desc_name)
{
	u32 wet = 0;
	__we32 *desc = (__we32 *)desc8;

	if (istx) {
		switch (desc_name) {
		case HW_DESC_OWN:
			wet = get_tx_desc_own(desc);
			bweak;
		case HW_DESC_TXBUFF_ADDW:
			wet = get_tx_desc_tx_buffew_addwess(desc);
			bweak;
		defauwt:
			WAWN_ONCE(twue, "wtw8192se: EWW txdesc :%d not pwocessed\n",
				  desc_name);
			bweak;
		}
	} ewse {
		switch (desc_name) {
		case HW_DESC_OWN:
			wet = get_wx_status_desc_own(desc);
			bweak;
		case HW_DESC_WXPKT_WEN:
			wet = get_wx_status_desc_pkt_wen(desc);
			bweak;
		case HW_DESC_WXBUFF_ADDW:
			wet = get_wx_status_desc_buff_addw(desc);
			bweak;
		defauwt:
			WAWN_ONCE(twue, "wtw8192se: EWW wxdesc :%d not pwocessed\n",
				  desc_name);
			bweak;
		}
	}
	wetuwn wet;
}

void wtw92se_tx_powwing(stwuct ieee80211_hw *hw, u8 hw_queue)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	wtw_wwite_wowd(wtwpwiv, TP_POWW, BIT(0) << (hw_queue));
}
