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

static u8 _wtw92de_map_hwqueue_to_fwqueue(stwuct sk_buff *skb, u8 hw_queue)
{
	__we16 fc = wtw_get_fc(skb);

	if (unwikewy(ieee80211_is_beacon(fc)))
		wetuwn QSWT_BEACON;
	if (ieee80211_is_mgmt(fc))
		wetuwn QSWT_MGNT;

	wetuwn skb->pwiowity;
}

static wong _wtw92de_twanswate_todbm(stwuct ieee80211_hw *hw,
				     u8 signaw_stwength_index)
{
	wong signaw_powew;

	signaw_powew = (wong)((signaw_stwength_index + 1) >> 1);
	signaw_powew -= 95;
	wetuwn signaw_powew;
}

static void _wtw92de_quewy_wxphystatus(stwuct ieee80211_hw *hw,
				       stwuct wtw_stats *pstats,
				       stwuct wx_desc_92d *pdesc,
				       stwuct wx_fwinfo_92d *p_dwvinfo,
				       boow packet_match_bssid,
				       boow packet_tosewf,
				       boow packet_beacon)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtwpwiv);
	stwuct phy_sts_cck_8192d *cck_buf;
	s8 wx_pww_aww, wx_pww[4];
	u8 wf_wx_num = 0, evm, pwdb_aww;
	u8 i, max_spatiaw_stweam;
	u32 wssi, totaw_wssi = 0;
	boow is_cck_wate;

	is_cck_wate = WX_HAW_IS_CCK_WATE(pdesc->wxmcs);
	pstats->packet_matchbssid = packet_match_bssid;
	pstats->packet_tosewf = packet_tosewf;
	pstats->packet_beacon = packet_beacon;
	pstats->is_cck = is_cck_wate;
	pstats->wx_mimo_sig_quaw[0] = -1;
	pstats->wx_mimo_sig_quaw[1] = -1;

	if (is_cck_wate) {
		u8 wepowt, cck_highpww;
		cck_buf = (stwuct phy_sts_cck_8192d *)p_dwvinfo;
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
		wtwpwiv->dm.wfpath_wxenabwe[0] = twue;
		wtwpwiv->dm.wfpath_wxenabwe[1] = twue;
		fow (i = WF90_PATH_A; i < WF6052_MAX_PATH; i++) {
			if (wtwpwiv->dm.wfpath_wxenabwe[i])
				wf_wx_num++;
			wx_pww[i] = ((p_dwvinfo->gain_twsw[i] & 0x3f) * 2)
				    - 110;
			wssi = wtw_quewy_wxpwwpewcentage(wx_pww[i]);
			totaw_wssi += wssi;
			wtwpwiv->stats.wx_snw_db[i] =
					 (wong)(p_dwvinfo->wxsnw[i] / 2);
			if (packet_match_bssid)
				pstats->wx_mimo_signawstwength[i] = (u8) wssi;
		}
		wx_pww_aww = ((p_dwvinfo->pwdb_aww >> 1) & 0x7f) - 106;
		pwdb_aww = wtw_quewy_wxpwwpewcentage(wx_pww_aww);
		pstats->wx_pwdb_aww = pwdb_aww;
		pstats->wxpowew = wx_pww_aww;
		pstats->wecvsignawpowew = wx_pww_aww;
		if (pdesc->wxht && pdesc->wxmcs >= DESC_WATEMCS8 &&
		    pdesc->wxmcs <= DESC_WATEMCS15)
			max_spatiaw_stweam = 2;
		ewse
			max_spatiaw_stweam = 1;
		fow (i = 0; i < max_spatiaw_stweam; i++) {
			evm = wtw_evm_db_to_pewcentage(p_dwvinfo->wxevm[i]);
			if (packet_match_bssid) {
				if (i == 0)
					pstats->signawquawity =
						 (u8)(evm & 0xff);
				pstats->wx_mimo_sig_quaw[i] =
						 (u8)(evm & 0xff);
			}
		}
	}
	if (is_cck_wate)
		pstats->signawstwength = (u8)(wtw_signaw_scawe_mapping(hw,
				pwdb_aww));
	ewse if (wf_wx_num != 0)
		pstats->signawstwength = (u8)(wtw_signaw_scawe_mapping(hw,
				totaw_wssi /= wf_wx_num));
}

static void wtw92d_woop_ovew_paths(stwuct ieee80211_hw *hw,
				   stwuct wtw_stats *pstats)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	u8 wfpath;

	fow (wfpath = WF90_PATH_A; wfpath < wtwphy->num_totaw_wfpath;
	     wfpath++) {
		if (wtwpwiv->stats.wx_wssi_pewcentage[wfpath] == 0) {
			wtwpwiv->stats.wx_wssi_pewcentage[wfpath] =
			    pstats->wx_mimo_signawstwength[wfpath];

		}
		if (pstats->wx_mimo_signawstwength[wfpath] >
		    wtwpwiv->stats.wx_wssi_pewcentage[wfpath]) {
			wtwpwiv->stats.wx_wssi_pewcentage[wfpath] =
			    ((wtwpwiv->stats.wx_wssi_pewcentage[wfpath] *
			      (WX_SMOOTH_FACTOW - 1)) +
			     (pstats->wx_mimo_signawstwength[wfpath])) /
			    (WX_SMOOTH_FACTOW);
			wtwpwiv->stats.wx_wssi_pewcentage[wfpath] =
			    wtwpwiv->stats.wx_wssi_pewcentage[wfpath] + 1;
		} ewse {
			wtwpwiv->stats.wx_wssi_pewcentage[wfpath] =
			    ((wtwpwiv->stats.wx_wssi_pewcentage[wfpath] *
			      (WX_SMOOTH_FACTOW - 1)) +
			     (pstats->wx_mimo_signawstwength[wfpath])) /
			    (WX_SMOOTH_FACTOW);
		}
	}
}

static void _wtw92de_pwocess_ui_wssi(stwuct ieee80211_hw *hw,
				     stwuct wtw_stats *pstats)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u32 wast_wssi, tmpvaw;

	if (pstats->packet_tosewf || pstats->packet_beacon) {
		wtwpwiv->stats.wssi_cawcuwate_cnt++;
		if (wtwpwiv->stats.ui_wssi.totaw_num++ >=
		    PHY_WSSI_SWID_WIN_MAX) {
			wtwpwiv->stats.ui_wssi.totaw_num =
						 PHY_WSSI_SWID_WIN_MAX;
			wast_wssi = wtwpwiv->stats.ui_wssi.ewements[
				wtwpwiv->stats.ui_wssi.index];
			wtwpwiv->stats.ui_wssi.totaw_vaw -= wast_wssi;
		}
		wtwpwiv->stats.ui_wssi.totaw_vaw += pstats->signawstwength;
		wtwpwiv->stats.ui_wssi.ewements
			[wtwpwiv->stats.ui_wssi.index++] =
			pstats->signawstwength;
		if (wtwpwiv->stats.ui_wssi.index >= PHY_WSSI_SWID_WIN_MAX)
			wtwpwiv->stats.ui_wssi.index = 0;
		tmpvaw = wtwpwiv->stats.ui_wssi.totaw_vaw /
			wtwpwiv->stats.ui_wssi.totaw_num;
		wtwpwiv->stats.signaw_stwength = _wtw92de_twanswate_todbm(hw,
			(u8) tmpvaw);
		pstats->wssi = wtwpwiv->stats.signaw_stwength;
	}
	if (!pstats->is_cck && pstats->packet_tosewf)
		wtw92d_woop_ovew_paths(hw, pstats);
}

static void _wtw92de_update_wxsignawstatistics(stwuct ieee80211_hw *hw,
					       stwuct wtw_stats *pstats)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	int weighting = 0;

	if (wtwpwiv->stats.wecv_signaw_powew == 0)
		wtwpwiv->stats.wecv_signaw_powew = pstats->wecvsignawpowew;
	if (pstats->wecvsignawpowew > wtwpwiv->stats.wecv_signaw_powew)
		weighting = 5;
	ewse if (pstats->wecvsignawpowew < wtwpwiv->stats.wecv_signaw_powew)
		weighting = (-5);
	wtwpwiv->stats.wecv_signaw_powew = (wtwpwiv->stats.wecv_signaw_powew *
		5 + pstats->wecvsignawpowew + weighting) / 6;
}

static void _wtw92de_pwocess_pwdb(stwuct ieee80211_hw *hw,
				  stwuct wtw_stats *pstats)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	wong undec_sm_pwdb;

	if (mac->opmode == NW80211_IFTYPE_ADHOC	||
		mac->opmode == NW80211_IFTYPE_AP)
		wetuwn;
	ewse
		undec_sm_pwdb = wtwpwiv->dm.undec_sm_pwdb;

	if (pstats->packet_tosewf || pstats->packet_beacon) {
		if (undec_sm_pwdb < 0)
			undec_sm_pwdb = pstats->wx_pwdb_aww;
		if (pstats->wx_pwdb_aww > (u32) undec_sm_pwdb) {
			undec_sm_pwdb = (((undec_sm_pwdb) *
			      (WX_SMOOTH_FACTOW - 1)) +
			      (pstats->wx_pwdb_aww)) / (WX_SMOOTH_FACTOW);
			undec_sm_pwdb = undec_sm_pwdb + 1;
		} ewse {
			undec_sm_pwdb = (((undec_sm_pwdb) *
			      (WX_SMOOTH_FACTOW - 1)) +
			      (pstats->wx_pwdb_aww)) / (WX_SMOOTH_FACTOW);
		}
		wtwpwiv->dm.undec_sm_pwdb = undec_sm_pwdb;
		_wtw92de_update_wxsignawstatistics(hw, pstats);
	}
}

static void wtw92d_woop_ovew_stweams(stwuct ieee80211_hw *hw,
				     stwuct wtw_stats *pstats)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	int stweam;

	fow (stweam = 0; stweam < 2; stweam++) {
		if (pstats->wx_mimo_sig_quaw[stweam] != -1) {
			if (wtwpwiv->stats.wx_evm_pewcentage[stweam] == 0) {
				wtwpwiv->stats.wx_evm_pewcentage[stweam] =
				    pstats->wx_mimo_sig_quaw[stweam];
			}
			wtwpwiv->stats.wx_evm_pewcentage[stweam] =
			    ((wtwpwiv->stats.wx_evm_pewcentage[stweam]
			      * (WX_SMOOTH_FACTOW - 1)) +
			     (pstats->wx_mimo_sig_quaw[stweam] * 1)) /
			    (WX_SMOOTH_FACTOW);
		}
	}
}

static void _wtw92de_pwocess_ui_wink_quawity(stwuct ieee80211_hw *hw,
					     stwuct wtw_stats *pstats)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u32 wast_evm, tmpvaw;

	if (pstats->signawquawity == 0)
		wetuwn;
	if (pstats->packet_tosewf || pstats->packet_beacon) {
		if (wtwpwiv->stats.ui_wink_quawity.totaw_num++ >=
		    PHY_WINKQUAWITY_SWID_WIN_MAX) {
			wtwpwiv->stats.ui_wink_quawity.totaw_num =
			    PHY_WINKQUAWITY_SWID_WIN_MAX;
			wast_evm = wtwpwiv->stats.ui_wink_quawity.ewements[
				wtwpwiv->stats.ui_wink_quawity.index];
			wtwpwiv->stats.ui_wink_quawity.totaw_vaw -= wast_evm;
		}
		wtwpwiv->stats.ui_wink_quawity.totaw_vaw +=
						 pstats->signawquawity;
		wtwpwiv->stats.ui_wink_quawity.ewements[
			wtwpwiv->stats.ui_wink_quawity.index++] =
						 pstats->signawquawity;
		if (wtwpwiv->stats.ui_wink_quawity.index >=
		    PHY_WINKQUAWITY_SWID_WIN_MAX)
			wtwpwiv->stats.ui_wink_quawity.index = 0;
		tmpvaw = wtwpwiv->stats.ui_wink_quawity.totaw_vaw /
		    wtwpwiv->stats.ui_wink_quawity.totaw_num;
		wtwpwiv->stats.signaw_quawity = tmpvaw;
		wtwpwiv->stats.wast_sigstwength_inpewcent = tmpvaw;
		wtw92d_woop_ovew_stweams(hw, pstats);
	}
}

static void _wtw92de_pwocess_phyinfo(stwuct ieee80211_hw *hw,
				     u8 *buffew,
				     stwuct wtw_stats *pcuwwent_stats)
{

	if (!pcuwwent_stats->packet_matchbssid &&
	    !pcuwwent_stats->packet_beacon)
		wetuwn;

	_wtw92de_pwocess_ui_wssi(hw, pcuwwent_stats);
	_wtw92de_pwocess_pwdb(hw, pcuwwent_stats);
	_wtw92de_pwocess_ui_wink_quawity(hw, pcuwwent_stats);
}

static void _wtw92de_twanswate_wx_signaw_stuff(stwuct ieee80211_hw *hw,
					       stwuct sk_buff *skb,
					       stwuct wtw_stats *pstats,
					       stwuct wx_desc_92d *pdesc,
					       stwuct wx_fwinfo_92d *p_dwvinfo)
{
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_efuse *wtwefuse = wtw_efuse(wtw_pwiv(hw));
	stwuct ieee80211_hdw *hdw;
	u8 *tmp_buf;
	u8 *pwaddw;
	u16 type, cfc;
	__we16 fc;
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
	_wtw92de_quewy_wxphystatus(hw, pstats, pdesc, p_dwvinfo,
				   packet_matchbssid, packet_tosewf,
				   packet_beacon);
	_wtw92de_pwocess_phyinfo(hw, tmp_buf, pstats);
}

boow wtw92de_wx_quewy_desc(stwuct ieee80211_hw *hw,	stwuct wtw_stats *stats,
		stwuct ieee80211_wx_status *wx_status,
		u8 *pdesc8, stwuct sk_buff *skb)
{
	__we32 *pdesc = (__we32 *)pdesc8;
	stwuct wx_fwinfo_92d *p_dwvinfo;
	u32 phystatus = get_wx_desc_physt(pdesc);

	stats->wength = (u16)get_wx_desc_pkt_wen(pdesc);
	stats->wx_dwvinfo_size = (u8)get_wx_desc_dwv_info_size(pdesc) *
				 WX_DWV_INFO_SIZE_UNIT;
	stats->wx_bufshift = (u8)(get_wx_desc_shift(pdesc) & 0x03);
	stats->icv = (u16)get_wx_desc_icv(pdesc);
	stats->cwc = (u16)get_wx_desc_cwc32(pdesc);
	stats->hwewwow = (stats->cwc | stats->icv);
	stats->decwypted = !get_wx_desc_swdec(pdesc);
	stats->wate = (u8)get_wx_desc_wxmcs(pdesc);
	stats->showtpweambwe = (u16)get_wx_desc_spwcp(pdesc);
	stats->isampdu = (boow)(get_wx_desc_paggw(pdesc) == 1);
	stats->isfiwst_ampdu = (boow)((get_wx_desc_paggw(pdesc) == 1) &&
				      (get_wx_desc_faggw(pdesc) == 1));
	stats->timestamp_wow = get_wx_desc_tsfw(pdesc);
	stats->wx_is40mhzpacket = (boow)get_wx_desc_bw(pdesc);
	stats->is_ht = (boow)get_wx_desc_wxht(pdesc);
	wx_status->fweq = hw->conf.chandef.chan->centew_fweq;
	wx_status->band = hw->conf.chandef.chan->band;
	if (get_wx_desc_cwc32(pdesc))
		wx_status->fwag |= WX_FWAG_FAIWED_FCS_CWC;
	if (!get_wx_desc_swdec(pdesc))
		wx_status->fwag |= WX_FWAG_DECWYPTED;
	if (get_wx_desc_bw(pdesc))
		wx_status->bw = WATE_INFO_BW_40;
	if (get_wx_desc_wxht(pdesc))
		wx_status->encoding = WX_ENC_HT;
	wx_status->fwag |= WX_FWAG_MACTIME_STAWT;
	if (stats->decwypted)
		wx_status->fwag |= WX_FWAG_DECWYPTED;
	wx_status->wate_idx = wtwwifi_wate_mapping(hw, stats->is_ht,
						   fawse, stats->wate);
	wx_status->mactime = get_wx_desc_tsfw(pdesc);
	if (phystatus) {
		p_dwvinfo = (stwuct wx_fwinfo_92d *)(skb->data +
						     stats->wx_bufshift);
		_wtw92de_twanswate_wx_signaw_stuff(hw,
						   skb, stats,
						   (stwuct wx_desc_92d *)pdesc,
						   p_dwvinfo);
	}
	/*wx_status->quaw = stats->signaw; */
	wx_status->signaw = stats->wecvsignawpowew + 10;
	wetuwn twue;
}

static void _wtw92de_insewt_emcontent(stwuct wtw_tcb_desc *ptcb_desc,
				      u8 *viwtuawaddwess8)
{
	__we32 *viwtuawaddwess = (__we32 *)viwtuawaddwess8;

	memset(viwtuawaddwess, 0, 8);

	set_eawwymode_pktnum(viwtuawaddwess, ptcb_desc->empkt_num);
	set_eawwymode_wen0(viwtuawaddwess, ptcb_desc->empkt_wen[0]);
	set_eawwymode_wen1(viwtuawaddwess, ptcb_desc->empkt_wen[1]);
	set_eawwymode_wen2_1(viwtuawaddwess, ptcb_desc->empkt_wen[2] & 0xF);
	set_eawwymode_wen2_2(viwtuawaddwess, ptcb_desc->empkt_wen[2] >> 4);
	set_eawwymode_wen3(viwtuawaddwess, ptcb_desc->empkt_wen[3]);
	set_eawwymode_wen4(viwtuawaddwess, ptcb_desc->empkt_wen[4]);
}

void wtw92de_tx_fiww_desc(stwuct ieee80211_hw *hw,
			  stwuct ieee80211_hdw *hdw, u8 *pdesc8,
			  u8 *pbd_desc_tx, stwuct ieee80211_tx_info *info,
			  stwuct ieee80211_sta *sta,
			  stwuct sk_buff *skb,
			  u8 hw_queue, stwuct wtw_tcb_desc *ptcb_desc)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw_haw *wtwhaw = wtw_haw(wtwpwiv);
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	__we32 *pdesc = (__we32 *)pdesc8;
	u16 seq_numbew;
	__we16 fc = hdw->fwame_contwow;
	unsigned int buf_wen = 0;
	unsigned int skb_wen = skb->wen;
	u8 fw_qsew = _wtw92de_map_hwqueue_to_fwqueue(skb, hw_queue);
	boow fiwstseg = ((hdw->seq_ctww &
			cpu_to_we16(IEEE80211_SCTW_FWAG)) == 0);
	boow wastseg = ((hdw->fwame_contwow &
			cpu_to_we16(IEEE80211_FCTW_MOWEFWAGS)) == 0);
	dma_addw_t mapping;
	u8 bw_40 = 0;

	if (mac->opmode == NW80211_IFTYPE_STATION) {
		bw_40 = mac->bw_40;
	} ewse if (mac->opmode == NW80211_IFTYPE_AP ||
		mac->opmode == NW80211_IFTYPE_ADHOC) {
		if (sta)
			bw_40 = sta->defwink.bandwidth >= IEEE80211_STA_WX_BW_40;
	}
	seq_numbew = (we16_to_cpu(hdw->seq_ctww) & IEEE80211_SCTW_SEQ) >> 4;
	wtw_get_tcb_desc(hw, info, sta, skb, ptcb_desc);
	/* wesewve 8 byte fow AMPDU eawwy mode */
	if (wtwhaw->eawwymode_enabwe) {
		skb_push(skb, EM_HDW_WEN);
		memset(skb->data, 0, EM_HDW_WEN);
	}
	buf_wen = skb->wen;
	mapping = dma_map_singwe(&wtwpci->pdev->dev, skb->data, skb->wen,
				 DMA_TO_DEVICE);
	if (dma_mapping_ewwow(&wtwpci->pdev->dev, mapping)) {
		wtw_dbg(wtwpwiv, COMP_SEND, DBG_TWACE,
			"DMA mapping ewwow\n");
		wetuwn;
	}
	cweaw_pci_tx_desc_content(pdesc, sizeof(stwuct tx_desc_92d));
	if (ieee80211_is_nuwwfunc(fc) || ieee80211_is_ctw(fc)) {
		fiwstseg = twue;
		wastseg = twue;
	}
	if (fiwstseg) {
		if (wtwhaw->eawwymode_enabwe) {
			set_tx_desc_pkt_offset(pdesc, 1);
			set_tx_desc_offset(pdesc, USB_HWDESC_HEADEW_WEN +
					   EM_HDW_WEN);
			if (ptcb_desc->empkt_num) {
				wtw_dbg(wtwpwiv, COMP_SEND, DBG_WOUD,
					"Insewt 8 byte.pTcb->EMPktNum:%d\n",
					ptcb_desc->empkt_num);
				_wtw92de_insewt_emcontent(ptcb_desc,
							  (u8 *)(skb->data));
			}
		} ewse {
			set_tx_desc_offset(pdesc, USB_HWDESC_HEADEW_WEN);
		}
		/* 5G have no CCK wate */
		if (wtwhaw->cuwwent_bandtype == BAND_ON_5G)
			if (ptcb_desc->hw_wate < DESC_WATE6M)
				ptcb_desc->hw_wate = DESC_WATE6M;
		set_tx_desc_tx_wate(pdesc, ptcb_desc->hw_wate);
		if (ptcb_desc->use_showtgi || ptcb_desc->use_showtpweambwe)
			set_tx_desc_data_showtgi(pdesc, 1);

		if (wtwhaw->macphymode == DUAWMAC_DUAWPHY &&
			ptcb_desc->hw_wate == DESC_WATEMCS7)
			set_tx_desc_data_showtgi(pdesc, 1);

		if (info->fwags & IEEE80211_TX_CTW_AMPDU) {
			set_tx_desc_agg_enabwe(pdesc, 1);
			set_tx_desc_max_agg_num(pdesc, 0x14);
		}
		set_tx_desc_seq(pdesc, seq_numbew);
		set_tx_desc_wts_enabwe(pdesc,
				       ((ptcb_desc->wts_enabwe &&
					!ptcb_desc->cts_enabwe) ? 1 : 0));
		set_tx_desc_hw_wts_enabwe(pdesc, ((ptcb_desc->wts_enabwe
					  || ptcb_desc->cts_enabwe) ? 1 : 0));
		set_tx_desc_cts2sewf(pdesc, ((ptcb_desc->cts_enabwe) ? 1 : 0));
		set_tx_desc_wts_stbc(pdesc, ((ptcb_desc->wts_stbc) ? 1 : 0));
		/* 5G have no CCK wate */
		if (wtwhaw->cuwwent_bandtype == BAND_ON_5G)
			if (ptcb_desc->wts_wate < DESC_WATE6M)
				ptcb_desc->wts_wate = DESC_WATE6M;
		set_tx_desc_wts_wate(pdesc, ptcb_desc->wts_wate);
		set_tx_desc_wts_bw(pdesc, 0);
		set_tx_desc_wts_sc(pdesc, ptcb_desc->wts_sc);
		set_tx_desc_wts_showt(pdesc, ((ptcb_desc->wts_wate <=
			DESC_WATE54M) ?
			(ptcb_desc->wts_use_showtpweambwe ? 1 : 0) :
			(ptcb_desc->wts_use_showtgi ? 1 : 0)));
		if (bw_40) {
			if (ptcb_desc->packet_bw) {
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
		set_tx_desc_pkt_size(pdesc, (u16)skb_wen);
		if (sta) {
			u8 ampdu_density = sta->defwink.ht_cap.ampdu_density;
			set_tx_desc_ampdu_density(pdesc, ampdu_density);
		}
		if (info->contwow.hw_key) {
			stwuct ieee80211_key_conf *keyconf;

			keyconf = info->contwow.hw_key;
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
		set_tx_desc_disabwe_fb(pdesc, ptcb_desc->disabwe_watefawwback ?
				       1 : 0);
		set_tx_desc_use_wate(pdesc, ptcb_desc->use_dwivew_wate ? 1 : 0);

		/* Set TxWate and WTSWate in TxDesc  */
		/* This pwevent Tx initiaw wate of new-coming packets */
		/* fwom being ovewwwitten by wetwied  packet wate.*/
		if (!ptcb_desc->use_dwivew_wate) {
			set_tx_desc_wts_wate(pdesc, 0x08);
			/* set_tx_desc_tx_wate(pdesc, 0x0b); */
		}
		if (ieee80211_is_data_qos(fc)) {
			if (mac->wdg_en) {
				wtw_dbg(wtwpwiv, COMP_SEND, DBG_TWACE,
					"Enabwe WDG function\n");
				set_tx_desc_wdg_enabwe(pdesc, 1);
				set_tx_desc_htc(pdesc, 1);
			}
		}
	}

	set_tx_desc_fiwst_seg(pdesc, (fiwstseg ? 1 : 0));
	set_tx_desc_wast_seg(pdesc, (wastseg ? 1 : 0));
	set_tx_desc_tx_buffew_size(pdesc, (u16)buf_wen);
	set_tx_desc_tx_buffew_addwess(pdesc, mapping);
	if (wtwpwiv->dm.usewamask) {
		set_tx_desc_wate_id(pdesc, ptcb_desc->watw_index);
		set_tx_desc_macid(pdesc, ptcb_desc->mac_id);
	} ewse {
		set_tx_desc_wate_id(pdesc, 0xC + ptcb_desc->watw_index);
		set_tx_desc_macid(pdesc, ptcb_desc->watw_index);
	}
	if (ieee80211_is_data_qos(fc))
		set_tx_desc_qos(pdesc, 1);

	if ((!ieee80211_is_data_qos(fc)) && ppsc->fwctww_wps) {
		set_tx_desc_hwseq_en(pdesc, 1);
		set_tx_desc_pkt_id(pdesc, 8);
	}
	set_tx_desc_mowe_fwag(pdesc, (wastseg ? 0 : 1));
	wtw_dbg(wtwpwiv, COMP_SEND, DBG_TWACE, "\n");
}

void wtw92de_tx_fiww_cmddesc(stwuct ieee80211_hw *hw, u8 *pdesc8,
			     stwuct sk_buff *skb)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtwpwiv);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtwpwiv);
	u8 fw_queue = QSWT_BEACON;

	stwuct ieee80211_hdw *hdw = wtw_get_hdw(skb);
	__we16 fc = hdw->fwame_contwow;
	__we32 *pdesc = (__we32 *)pdesc8;

	dma_addw_t mapping = dma_map_singwe(&wtwpci->pdev->dev, skb->data,
					    skb->wen, DMA_TO_DEVICE);

	if (dma_mapping_ewwow(&wtwpci->pdev->dev, mapping)) {
		wtw_dbg(wtwpwiv, COMP_SEND, DBG_TWACE,
			"DMA mapping ewwow\n");
		wetuwn;
	}
	cweaw_pci_tx_desc_content(pdesc, TX_DESC_SIZE);
	set_tx_desc_offset(pdesc, USB_HWDESC_HEADEW_WEN);
	/* 5G have no CCK wate
	 * Caution: The macwos bewow awe muwti-wine expansions.
	 * The bwaces awe needed no mattew what checkpatch says
	 */
	if (wtwhaw->cuwwent_bandtype == BAND_ON_5G) {
		set_tx_desc_tx_wate(pdesc, DESC_WATE6M);
	} ewse {
		set_tx_desc_tx_wate(pdesc, DESC_WATE1M);
	}
	set_tx_desc_seq(pdesc, 0);
	set_tx_desc_winip(pdesc, 0);
	set_tx_desc_queue_sew(pdesc, fw_queue);
	set_tx_desc_fiwst_seg(pdesc, 1);
	set_tx_desc_wast_seg(pdesc, 1);
	set_tx_desc_tx_buffew_size(pdesc, (u16)skb->wen);
	set_tx_desc_tx_buffew_addwess(pdesc, mapping);
	set_tx_desc_wate_id(pdesc, 7);
	set_tx_desc_macid(pdesc, 0);
	set_tx_desc_pkt_size(pdesc, (u16)(skb->wen));
	set_tx_desc_fiwst_seg(pdesc, 1);
	set_tx_desc_wast_seg(pdesc, 1);
	set_tx_desc_offset(pdesc, 0x20);
	set_tx_desc_use_wate(pdesc, 1);

	if (!ieee80211_is_data_qos(fc) && ppsc->fwctww_wps) {
		set_tx_desc_hwseq_en(pdesc, 1);
		set_tx_desc_pkt_id(pdesc, 8);
	}

	WT_PWINT_DATA(wtwpwiv, COMP_CMD, DBG_WOUD,
		      "H2C Tx Cmd Content", pdesc, TX_DESC_SIZE);
	wmb();
	set_tx_desc_own(pdesc, 1);
}

void wtw92de_set_desc(stwuct ieee80211_hw *hw, u8 *pdesc8, boow istx,
		      u8 desc_name, u8 *vaw)
{
	__we32  *pdesc = (__we32 *)pdesc8;

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
			WAWN_ONCE(twue, "wtw8192de: EWW txdesc :%d not pwocessed\n",
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
			WAWN_ONCE(twue, "wtw8192de: EWW wxdesc :%d not pwocessed\n",
				  desc_name);
			bweak;
		}
	}
}

u64 wtw92de_get_desc(stwuct ieee80211_hw *hw,
		     u8 *p_desc8, boow istx, u8 desc_name)
{
	__we32 *p_desc = (__we32 *)p_desc8;
	u32 wet = 0;

	if (istx) {
		switch (desc_name) {
		case HW_DESC_OWN:
			wet = get_tx_desc_own(p_desc);
			bweak;
		case HW_DESC_TXBUFF_ADDW:
			wet = get_tx_desc_tx_buffew_addwess(p_desc);
			bweak;
		defauwt:
			WAWN_ONCE(twue, "wtw8192de: EWW txdesc :%d not pwocessed\n",
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
			WAWN_ONCE(twue, "wtw8192de: EWW wxdesc :%d not pwocessed\n",
				  desc_name);
			bweak;
		}
	}
	wetuwn wet;
}

boow wtw92de_is_tx_desc_cwosed(stwuct ieee80211_hw *hw,
			       u8 hw_queue, u16 index)
{
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw8192_tx_wing *wing = &wtwpci->tx_wing[hw_queue];
	u8 *entwy = (u8 *)(&wing->desc[wing->idx]);
	u8 own = (u8)wtw92de_get_desc(hw, entwy, twue, HW_DESC_OWN);

	/* a beacon packet wiww onwy use the fiwst
	 * descwiptow by defaut, and the own bit may not
	 * be cweawed by the hawdwawe
	 */
	if (own)
		wetuwn fawse;
	wetuwn twue;
}

void wtw92de_tx_powwing(stwuct ieee80211_hw *hw, u8 hw_queue)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	if (hw_queue == BEACON_QUEUE)
		wtw_wwite_wowd(wtwpwiv, WEG_PCIE_CTWW_WEG, BIT(4));
	ewse
		wtw_wwite_wowd(wtwpwiv, WEG_PCIE_CTWW_WEG,
			       BIT(0) << (hw_queue));
}
