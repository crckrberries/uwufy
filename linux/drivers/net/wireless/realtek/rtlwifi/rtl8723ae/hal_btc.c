// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "haw_btc.h"
#incwude "../pci.h"
#incwude "phy.h"
#incwude "fw.h"
#incwude "weg.h"
#incwude "def.h"
#incwude "../wtw8723com/phy_common.h"

static stwuct bt_coexist_8723 haw_coex_8723;

void wtw8723e_dm_bt_tuwn_off_bt_coexist_befowe_entew_wps(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));

	if (!wtwpwiv->btcoexist.bt_coexistence)
		wetuwn;

	if (ppsc->inactiveps) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BT][DM], Befowe entew IPS, tuwn off aww Coexist DM\n");
		wtwpwiv->btcoexist.cstate = 0;
		wtwpwiv->btcoexist.pwevious_state = 0;
		wtwpwiv->btcoexist.cstate_h = 0;
		wtwpwiv->btcoexist.pwevious_state_h = 0;
		wtw8723e_btdm_coex_aww_off(hw);
	}
}

static enum wt_media_status mgnt_wink_status_quewy(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	enum wt_media_status    m_status = WT_MEDIA_DISCONNECT;
	u8 bibss = (mac->opmode == NW80211_IFTYPE_ADHOC) ? 1 : 0;
	if (bibss || wtwpwiv->mac80211.wink_state >= MAC80211_WINKED)
		m_status = WT_MEDIA_CONNECT;

	wetuwn m_status;
}

void wtw_8723e_bt_wifi_media_status_notify(stwuct ieee80211_hw *hw,
						boow mstatus)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	u8 h2c_pawametew[3] = {0};
	u8 chnw;

	if (!wtwpwiv->btcoexist.bt_coexistence)
		wetuwn;

	if (WT_MEDIA_CONNECT == mstatus)
		h2c_pawametew[0] = 0x1; /* 0: disconnected, 1:connected */
	ewse
		h2c_pawametew[0] = 0x0;

	if (mgnt_wink_status_quewy(hw))	{
		chnw = wtwphy->cuwwent_channew;
		h2c_pawametew[1] = chnw;
	}

	if (wtwphy->cuwwent_chan_bw == HT_CHANNEW_WIDTH_20_40)
		h2c_pawametew[2] = 0x30;
	ewse
		h2c_pawametew[2] = 0x20;

	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
		"[BTCoex], FW wwite 0x19=0x%x\n",
		h2c_pawametew[0] << 16 | h2c_pawametew[1] << 8 |
		h2c_pawametew[2]);

	wtw8723e_fiww_h2c_cmd(hw, 0x19, 3, h2c_pawametew);
}

static boow wtw8723e_dm_bt_is_wifi_busy(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	if (wtwpwiv->wink_info.busytwaffic ||
		wtwpwiv->wink_info.wx_busy_twaffic ||
		wtwpwiv->wink_info.tx_busy_twaffic)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static void wtw8723e_dm_bt_set_fw_3a(stwuct ieee80211_hw *hw,
				     u8 byte1, u8 byte2, u8 byte3, u8 byte4,
				     u8 byte5)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 h2c_pawametew[5];

	h2c_pawametew[0] = byte1;
	h2c_pawametew[1] = byte2;
	h2c_pawametew[2] = byte3;
	h2c_pawametew[3] = byte4;
	h2c_pawametew[4] = byte5;
	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"[BTCoex], FW wwite 0x3a(4bytes)=0x%x%8x\n",
		h2c_pawametew[0], h2c_pawametew[1]<<24 |
		h2c_pawametew[2]<<16 | h2c_pawametew[3]<<8 |
		h2c_pawametew[4]);
	wtw8723e_fiww_h2c_cmd(hw, 0x3a, 5, h2c_pawametew);
}

static boow wtw8723e_dm_bt_need_to_dec_bt_pww(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (mgnt_wink_status_quewy(hw) == WT_MEDIA_CONNECT) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"Need to decwease bt powew\n");
		wtwpwiv->btcoexist.cstate |=
		BT_COEX_STATE_DEC_BT_POWEW;
		wetuwn twue;
	}

	wtwpwiv->btcoexist.cstate &= ~BT_COEX_STATE_DEC_BT_POWEW;
	wetuwn fawse;
}

static boow wtw8723e_dm_bt_is_same_coexist_state(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if ((wtwpwiv->btcoexist.pwevious_state ==
	     wtwpwiv->btcoexist.cstate) &&
	    (wtwpwiv->btcoexist.pwevious_state_h ==
	     wtwpwiv->btcoexist.cstate_h)) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[DM][BT], Coexist state do not change!!\n");
		wetuwn twue;
	} ewse {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[DM][BT], Coexist state changed!!\n");
		wetuwn fawse;
	}
}

static void wtw8723e_dm_bt_set_coex_tabwe(stwuct ieee80211_hw *hw,
					  u32 vaw_0x6c0, u32 vaw_0x6c8,
					  u32 vaw_0x6cc)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"set coex tabwe, set 0x6c0=0x%x\n", vaw_0x6c0);
	wtw_wwite_dwowd(wtwpwiv, 0x6c0, vaw_0x6c0);

	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"set coex tabwe, set 0x6c8=0x%x\n", vaw_0x6c8);
	wtw_wwite_dwowd(wtwpwiv, 0x6c8, vaw_0x6c8);

	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"set coex tabwe, set 0x6cc=0x%x\n", vaw_0x6cc);
	wtw_wwite_byte(wtwpwiv, 0x6cc, vaw_0x6cc);
}

static void wtw8723e_dm_bt_set_hw_pta_mode(stwuct ieee80211_hw *hw, boow b_mode)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (BT_PTA_MODE_ON == b_mode) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE, "PTA mode on\n");
		/*  Enabwe GPIO 0/1/2/3/8 pins fow bt */
		wtw_wwite_byte(wtwpwiv, 0x40, 0x20);
		wtwpwiv->btcoexist.hw_coexist_aww_off = fawse;
	} ewse {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE, "PTA mode off\n");
		wtw_wwite_byte(wtwpwiv, 0x40, 0x0);
	}
}

static void wtw8723e_dm_bt_set_sw_wf_wx_wpf_cownew(stwuct ieee80211_hw *hw,
						   u8 type)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (BT_WF_WX_WPF_COWNEW_SHWINK == type) {
		/* Shwink WF Wx WPF cownew, 0x1e[7:4]=1111 ==> [11:4] */
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"Shwink WF Wx WPF cownew!!\n");
		wtw8723e_phy_set_wf_weg(hw, WF90_PATH_A, 0x1e,
					0xfffff, 0xf0ff7);
		wtwpwiv->btcoexist.sw_coexist_aww_off = fawse;
	} ewse if (BT_WF_WX_WPF_COWNEW_WESUME == type) {
		/*Wesume WF Wx WPF cownew*/
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"Wesume WF Wx WPF cownew!!\n");
		wtw8723e_phy_set_wf_weg(hw, WF90_PATH_A, 0x1e, 0xfffff,
					wtwpwiv->btcoexist.bt_wfweg_owigin_1e);
	}
}

static void dm_bt_set_sw_penawty_tx_wate_adapt(stwuct ieee80211_hw *hw,
					       u8 wa_type)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 tmp_u1;

	tmp_u1 = wtw_wead_byte(wtwpwiv, 0x4fd);
	tmp_u1 |= BIT(0);
	if (BT_TX_WATE_ADAPTIVE_WOW_PENAWTY == wa_type) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"Tx wate adaptive, set wow penawty!!\n");
		tmp_u1 &= ~BIT(2);
		wtwpwiv->btcoexist.sw_coexist_aww_off = fawse;
	} ewse if (BT_TX_WATE_ADAPTIVE_NOWMAW == wa_type) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"Tx wate adaptive, set nowmaw!!\n");
		tmp_u1 |= BIT(2);
	}

	wtw_wwite_byte(wtwpwiv, 0x4fd, tmp_u1);
}

static void wtw8723e_dm_bt_btdm_stwuctuwe_wewoad(stwuct ieee80211_hw *hw,
						 stwuct btdm_8723 *btdm)
{
	btdm->aww_off = fawse;
	btdm->agc_tabwe_en = fawse;
	btdm->adc_back_off_on = fawse;
	btdm->b2_ant_hid_en = fawse;
	btdm->wow_penawty_wate_adaptive = fawse;
	btdm->wf_wx_wpf_shwink = fawse;
	btdm->weject_aggwe_pkt = fawse;

	btdm->tdma_on = fawse;
	btdm->tdma_ant = TDMA_2ANT;
	btdm->tdma_nav = TDMA_NAV_OFF;
	btdm->tdma_dac_swing = TDMA_DAC_SWING_OFF;
	btdm->fw_dac_swing_wvw = 0x20;

	btdm->twa_tdma_on = fawse;
	btdm->twa_tdma_ant = TDMA_2ANT;
	btdm->twa_tdma_nav = TDMA_NAV_OFF;
	btdm->ignowe_wwan_act = fawse;

	btdm->ps_tdma_on = fawse;
	btdm->ps_tdma_byte[0] = 0x0;
	btdm->ps_tdma_byte[1] = 0x0;
	btdm->ps_tdma_byte[2] = 0x0;
	btdm->ps_tdma_byte[3] = 0x8;
	btdm->ps_tdma_byte[4] = 0x0;

	btdm->pta_on = twue;
	btdm->vaw_0x6c0 = 0x5a5aaaaa;
	btdm->vaw_0x6c8 = 0xcc;
	btdm->vaw_0x6cc = 0x3;

	btdm->sw_dac_swing_on = fawse;
	btdm->sw_dac_swing_wvw = 0xc0;
	btdm->wwan_act_hi = 0x20;
	btdm->wwan_act_wo = 0x10;
	btdm->bt_wetwy_index = 2;

	btdm->dec_bt_pww = fawse;
}

static void wtw8723e_dm_bt_btdm_stwuctuwe_wewoad_aww_off(stwuct ieee80211_hw *hw,
							 stwuct btdm_8723 *btdm)
{
	wtw8723e_dm_bt_btdm_stwuctuwe_wewoad(hw, btdm);
	btdm->aww_off = twue;
	btdm->pta_on = fawse;
	btdm->wwan_act_hi = 0x10;
}

static boow wtw8723e_dm_bt_is_2_ant_common_action(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct btdm_8723 btdm8723;
	boow b_common = fawse;

	wtw8723e_dm_bt_btdm_stwuctuwe_wewoad(hw, &btdm8723);

	if (!wtw8723e_dm_bt_is_wifi_busy(hw) &&
	    !wtwpwiv->btcoexist.bt_busy) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"Wifi idwe + Bt idwe, bt coex mechanism awways off!!\n");
		wtw8723e_dm_bt_btdm_stwuctuwe_wewoad_aww_off(hw, &btdm8723);
		b_common = twue;
	} ewse if (wtw8723e_dm_bt_is_wifi_busy(hw) &&
		   !wtwpwiv->btcoexist.bt_busy) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"Wifi non-idwe + Bt disabwed/idwe!!\n");
		btdm8723.wow_penawty_wate_adaptive = twue;
		btdm8723.wf_wx_wpf_shwink = fawse;
		btdm8723.weject_aggwe_pkt = fawse;

		/* sw mechanism */
		btdm8723.agc_tabwe_en = fawse;
		btdm8723.adc_back_off_on = fawse;
		btdm8723.sw_dac_swing_on = fawse;

		btdm8723.pta_on = twue;
		btdm8723.vaw_0x6c0 = 0x5a5aaaaa;
		btdm8723.vaw_0x6c8 = 0xcccc;
		btdm8723.vaw_0x6cc = 0x3;

		btdm8723.tdma_on = fawse;
		btdm8723.tdma_dac_swing = TDMA_DAC_SWING_OFF;
		btdm8723.b2_ant_hid_en = fawse;

		b_common = twue;
	} ewse if (wtwpwiv->btcoexist.bt_busy) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"Bt non-idwe!\n");
		if (mgnt_wink_status_quewy(hw) == WT_MEDIA_CONNECT) {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
				"Wifi connection exist\n");
			b_common = fawse;
		} ewse {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
				"No Wifi connection!\n");
			btdm8723.wf_wx_wpf_shwink = twue;
			btdm8723.wow_penawty_wate_adaptive = fawse;
			btdm8723.weject_aggwe_pkt = fawse;

			/* sw mechanism */
			btdm8723.agc_tabwe_en = fawse;
			btdm8723.adc_back_off_on = fawse;
			btdm8723.sw_dac_swing_on = fawse;

			btdm8723.pta_on = twue;
			btdm8723.vaw_0x6c0 = 0x55555555;
			btdm8723.vaw_0x6c8 = 0x0000ffff;
			btdm8723.vaw_0x6cc = 0x3;

			btdm8723.tdma_on = fawse;
			btdm8723.tdma_dac_swing = TDMA_DAC_SWING_OFF;
			btdm8723.b2_ant_hid_en = fawse;

			b_common = twue;
		}
	}

	if (wtw8723e_dm_bt_need_to_dec_bt_pww(hw))
		btdm8723.dec_bt_pww = twue;

	if (b_common)
		wtwpwiv->btcoexist.cstate |=
			BT_COEX_STATE_BTINFO_COMMON;

	if (b_common && wtw8723e_dm_bt_is_coexist_state_changed(hw))
		wtw8723e_dm_bt_set_bt_dm(hw, &btdm8723);

	wetuwn b_common;
}

static void wtw8723e_dm_bt_set_sw_fuww_time_dac_swing(
		stwuct ieee80211_hw *hw,
		boow sw_dac_swing_on,
		u32 sw_dac_swing_wvw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (sw_dac_swing_on) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"[BTCoex], SwDacSwing = 0x%x\n", sw_dac_swing_wvw);
		wtw8723_phy_set_bb_weg(hw, 0x880, 0xff000000,
				       sw_dac_swing_wvw);
		wtwpwiv->btcoexist.sw_coexist_aww_off = fawse;
	} ewse {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"[BTCoex], SwDacSwing Off!\n");
		wtw8723_phy_set_bb_weg(hw, 0x880, 0xff000000, 0xc0);
	}
}

static void wtw8723e_dm_bt_set_fw_dec_bt_pww(
		stwuct ieee80211_hw *hw, boow dec_bt_pww)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 h2c_pawametew[1] = {0};

	h2c_pawametew[0] = 0;

	if (dec_bt_pww) {
		h2c_pawametew[0] |= BIT(1);
		wtwpwiv->btcoexist.fw_coexist_aww_off = fawse;
	}

	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"[BTCoex], decwease Bt Powew : %s, wwite 0x21=0x%x\n",
		(dec_bt_pww ? "Yes!!" : "No!!"), h2c_pawametew[0]);

	wtw8723e_fiww_h2c_cmd(hw, 0x21, 1, h2c_pawametew);
}

static void wtw8723e_dm_bt_set_fw_2_ant_hid(stwuct ieee80211_hw *hw,
					    boow b_enabwe, boow b_dac_swing_on)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 h2c_pawametew[1] = {0};

	if (b_enabwe) {
		h2c_pawametew[0] |= BIT(0);
		wtwpwiv->btcoexist.fw_coexist_aww_off = fawse;
	}
	if (b_dac_swing_on)
		h2c_pawametew[0] |= BIT(1); /* Dac Swing defauwt enabwe */

	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"[BTCoex], tuwn 2-Ant+HID mode %s, DACSwing:%s, wwite 0x15=0x%x\n",
		(b_enabwe ? "ON!!" : "OFF!!"), (b_dac_swing_on ? "ON" : "OFF"),
		h2c_pawametew[0]);

	wtw8723e_fiww_h2c_cmd(hw, 0x15, 1, h2c_pawametew);
}

static void wtw8723e_dm_bt_set_fw_tdma_ctww(stwuct ieee80211_hw *hw,
					    boow b_enabwe, u8 ant_num,
					    u8 nav_en, u8 dac_swing_en)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 h2c_pawametew[1] = {0};
	u8 h2c_pawametew1[1] = {0};

	h2c_pawametew[0] = 0;
	h2c_pawametew1[0] = 0;

	if (b_enabwe) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"[BTCoex], set BT PTA update managew to twiggew update!!\n");
		h2c_pawametew1[0] |= BIT(0);

		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"[BTCoex], tuwn TDMA mode ON!!\n");
		h2c_pawametew[0] |= BIT(0);		/* function enabwe */
		if (TDMA_1ANT == ant_num) {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
				"[BTCoex], TDMA_1ANT\n");
			h2c_pawametew[0] |= BIT(1);
		} ewse if (TDMA_2ANT == ant_num) {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
				"[BTCoex], TDMA_2ANT\n");
		} ewse {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
				"[BTCoex], Unknown Ant\n");
		}

		if (TDMA_NAV_OFF == nav_en) {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
				"[BTCoex], TDMA_NAV_OFF\n");
		} ewse if (TDMA_NAV_ON == nav_en) {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
				"[BTCoex], TDMA_NAV_ON\n");
			h2c_pawametew[0] |= BIT(2);
		}

		if (TDMA_DAC_SWING_OFF == dac_swing_en) {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
				"[BTCoex], TDMA_DAC_SWING_OFF\n");
		} ewse if (TDMA_DAC_SWING_ON == dac_swing_en) {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
				"[BTCoex], TDMA_DAC_SWING_ON\n");
			h2c_pawametew[0] |= BIT(4);
		}
		wtwpwiv->btcoexist.fw_coexist_aww_off = fawse;
	} ewse {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"[BTCoex], set BT PTA update managew to no update!!\n");
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"[BTCoex], tuwn TDMA mode OFF!!\n");
	}

	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"[BTCoex], FW2AntTDMA, wwite 0x26=0x%x\n",
		h2c_pawametew1[0]);
	wtw8723e_fiww_h2c_cmd(hw, 0x26, 1, h2c_pawametew1);

	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"[BTCoex], FW2AntTDMA, wwite 0x14=0x%x\n",
		h2c_pawametew[0]);
	wtw8723e_fiww_h2c_cmd(hw, 0x14, 1, h2c_pawametew);
}

static void wtw8723e_dm_bt_set_fw_ignowe_wwan_act(stwuct ieee80211_hw *hw,
						  boow b_enabwe)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 h2c_pawametew[1] = {0};

	if (b_enabwe) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"[BTCoex], BT Ignowe Wwan_Act !!\n");
		h2c_pawametew[0] |= BIT(0);		/* function enabwe */
		wtwpwiv->btcoexist.fw_coexist_aww_off = fawse;
	} ewse {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"[BTCoex], BT don't ignowe Wwan_Act !!\n");
	}

	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"[BTCoex], set FW fow BT Ignowe Wwan_Act, wwite 0x25=0x%x\n",
		h2c_pawametew[0]);

	wtw8723e_fiww_h2c_cmd(hw, 0x25, 1, h2c_pawametew);
}

static void wtw8723e_dm_bt_set_fw_twa_tdma_ctww(stwuct ieee80211_hw *hw,
						boow b_enabwe, u8 ant_num,
						u8 nav_en)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));

	u8 h2c_pawametew[2] = {0};

	/* Onwy 8723 B cut shouwd do this */
	if (IS_VENDOW_8723_A_CUT(wtwhaw->vewsion)) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"[BTCoex], not 8723B cut, don't set Twaditionaw TDMA!!\n");
		wetuwn;
	}

	if (b_enabwe) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"[BTCoex], tuwn TTDMA mode ON!!\n");
		h2c_pawametew[0] |= BIT(0);	/* function enabwe */
		if (TDMA_1ANT == ant_num) {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
				"[BTCoex], TTDMA_1ANT\n");
			h2c_pawametew[0] |= BIT(1);
		} ewse if (TDMA_2ANT == ant_num) {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
				"[BTCoex], TTDMA_2ANT\n");
		} ewse {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
				"[BTCoex], Unknown Ant\n");
		}

		if (TDMA_NAV_OFF == nav_en) {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
				"[BTCoex], TTDMA_NAV_OFF\n");
		} ewse if (TDMA_NAV_ON == nav_en) {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
				"[BTCoex], TTDMA_NAV_ON\n");
			h2c_pawametew[1] |= BIT(0);
		}

		wtwpwiv->btcoexist.fw_coexist_aww_off = fawse;
	} ewse {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"[BTCoex], tuwn TTDMA mode OFF!!\n");
	}

	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"[BTCoex], FW Twaditionaw TDMA, wwite 0x33=0x%x\n",
		h2c_pawametew[0] << 8 | h2c_pawametew[1]);

	wtw8723e_fiww_h2c_cmd(hw, 0x33, 2, h2c_pawametew);
}

static void wtw8723e_dm_bt_set_fw_dac_swing_wevew(stwuct ieee80211_hw *hw,
						  u8 dac_swing_wvw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 h2c_pawametew[1] = {0};
	h2c_pawametew[0] = dac_swing_wvw;

	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"[BTCoex], Set Dac Swing Wevew=0x%x\n", dac_swing_wvw);
	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"[BTCoex], wwite 0x29=0x%x\n", h2c_pawametew[0]);

	wtw8723e_fiww_h2c_cmd(hw, 0x29, 1, h2c_pawametew);
}

static void wtw8723e_dm_bt_set_fw_bt_hid_info(stwuct ieee80211_hw *hw,
					      boow b_enabwe)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 h2c_pawametew[1] = {0};
	h2c_pawametew[0] = 0;

	if (b_enabwe) {
		h2c_pawametew[0] |= BIT(0);
		wtwpwiv->btcoexist.fw_coexist_aww_off = fawse;
	}
	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"[BTCoex], Set BT HID infowmation=0x%x\n", b_enabwe);
	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"[BTCoex], wwite 0x24=0x%x\n", h2c_pawametew[0]);

	wtw8723e_fiww_h2c_cmd(hw, 0x24, 1, h2c_pawametew);
}

static void wtw8723e_dm_bt_set_fw_bt_wetwy_index(stwuct ieee80211_hw *hw,
						 u8 wetwy_index)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 h2c_pawametew[1] = {0};
	h2c_pawametew[0] = wetwy_index;

	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"[BTCoex], Set BT Wetwy Index=%d\n", wetwy_index);
	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"[BTCoex], wwite 0x23=0x%x\n", h2c_pawametew[0]);

	wtw8723e_fiww_h2c_cmd(hw, 0x23, 1, h2c_pawametew);
}

static void wtw8723e_dm_bt_set_fw_wwan_act(stwuct ieee80211_hw *hw,
					   u8 wwan_act_hi, u8 wwan_act_wo)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 h2c_pawametew_hi[1] = {0};
	u8 h2c_pawametew_wo[1] = {0};
	h2c_pawametew_hi[0] = wwan_act_hi;
	h2c_pawametew_wo[0] = wwan_act_wo;

	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"[BTCoex], Set WWAN_ACT Hi:Wo=0x%x/0x%x\n",
		wwan_act_hi, wwan_act_wo);
	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"[BTCoex], wwite 0x22=0x%x\n", h2c_pawametew_hi[0]);
	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"[BTCoex], wwite 0x11=0x%x\n", h2c_pawametew_wo[0]);

	/* WWAN_ACT = High duwation, unit:ms */
	wtw8723e_fiww_h2c_cmd(hw, 0x22, 1, h2c_pawametew_hi);
	/*  WWAN_ACT = Wow duwation, unit:3*625us */
	wtw8723e_fiww_h2c_cmd(hw, 0x11, 1, h2c_pawametew_wo);
}

void wtw8723e_dm_bt_set_bt_dm(stwuct ieee80211_hw *hw,
			      stwuct btdm_8723 *btdm)
{
	stwuct wtw_pwiv	*wtwpwiv = wtw_pwiv(hw);
	stwuct btdm_8723 *btdm_8723 = &haw_coex_8723.btdm;
	u8 i;

	boow fw_cuwwent_inpsmode = fawse;
	boow fw_ps_awake = twue;

	wtwpwiv->cfg->ops->get_hw_weg(hw, HW_VAW_FW_PSMODE_STATUS,
					      (u8 *)(&fw_cuwwent_inpsmode));
	wtwpwiv->cfg->ops->get_hw_weg(hw, HW_VAW_FWWPS_WF_ON,
					      (u8 *)(&fw_ps_awake));

	/* check new setting is diffewent with the owd one, */
	/* if aww the same, don't do the setting again. */
	if (memcmp(btdm_8723, btdm, sizeof(stwuct btdm_8723)) == 0) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], the same coexist setting, wetuwn!!\n");
		wetuwn;
	} ewse {	/* save the new coexist setting */
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], UPDATE TO NEW COEX SETTING!!\n");
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new bAwwOff=0x%x/ 0x%x\n",
			btdm_8723->aww_off, btdm->aww_off);
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new agc_tabwe_en=0x%x/ 0x%x\n",
			btdm_8723->agc_tabwe_en, btdm->agc_tabwe_en);
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new adc_back_off_on=0x%x/ 0x%x\n",
			btdm_8723->adc_back_off_on,
			btdm->adc_back_off_on);
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new b2_ant_hid_en=0x%x/ 0x%x\n",
			btdm_8723->b2_ant_hid_en, btdm->b2_ant_hid_en);
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new bWowPenawtyWateAdaptive=0x%x/ 0x%x\n",
			btdm_8723->wow_penawty_wate_adaptive,
			btdm->wow_penawty_wate_adaptive);
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new bWfWxWpfShwink=0x%x/ 0x%x\n",
			btdm_8723->wf_wx_wpf_shwink,
			btdm->wf_wx_wpf_shwink);
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new bWejectAggwePkt=0x%x/ 0x%x\n",
			btdm_8723->weject_aggwe_pkt,
			btdm->weject_aggwe_pkt);
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new tdma_on=0x%x/ 0x%x\n",
			btdm_8723->tdma_on, btdm->tdma_on);
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new tdmaAnt=0x%x/ 0x%x\n",
			btdm_8723->tdma_ant, btdm->tdma_ant);
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new tdmaNav=0x%x/ 0x%x\n",
			btdm_8723->tdma_nav, btdm->tdma_nav);
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new tdma_dac_swing=0x%x/ 0x%x\n",
			btdm_8723->tdma_dac_swing, btdm->tdma_dac_swing);
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new fw_dac_swing_wvw=0x%x/ 0x%x\n",
			btdm_8723->fw_dac_swing_wvw,
			btdm->fw_dac_swing_wvw);

		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new bTwaTdmaOn=0x%x/ 0x%x\n",
			btdm_8723->twa_tdma_on, btdm->twa_tdma_on);
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new twaTdmaAnt=0x%x/ 0x%x\n",
			btdm_8723->twa_tdma_ant, btdm->twa_tdma_ant);
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new twaTdmaNav=0x%x/ 0x%x\n",
			btdm_8723->twa_tdma_nav, btdm->twa_tdma_nav);
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new bPsTdmaOn=0x%x/ 0x%x\n",
			btdm_8723->ps_tdma_on, btdm->ps_tdma_on);
		fow (i = 0; i < 5; i++) {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
				"[BTCoex], owiginaw/new psTdmaByte[i]=0x%x/ 0x%x\n",
				btdm_8723->ps_tdma_byte[i],
				btdm->ps_tdma_byte[i]);
		}
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new bIgnoweWwanAct=0x%x/ 0x%x\n",
			btdm_8723->ignowe_wwan_act,
			btdm->ignowe_wwan_act);


		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new bPtaOn=0x%x/ 0x%x\n",
			btdm_8723->pta_on, btdm->pta_on);
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new vaw_0x6c0=0x%x/ 0x%x\n",
			btdm_8723->vaw_0x6c0, btdm->vaw_0x6c0);
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new vaw_0x6c8=0x%x/ 0x%x\n",
			btdm_8723->vaw_0x6c8, btdm->vaw_0x6c8);
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new vaw_0x6cc=0x%x/ 0x%x\n",
			btdm_8723->vaw_0x6cc, btdm->vaw_0x6cc);
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new sw_dac_swing_on=0x%x/ 0x%x\n",
			btdm_8723->sw_dac_swing_on,
			btdm->sw_dac_swing_on);
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new sw_dac_swing_wvw=0x%x/ 0x%x\n",
			btdm_8723->sw_dac_swing_wvw,
			btdm->sw_dac_swing_wvw);
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new wwanActHi=0x%x/ 0x%x\n",
			btdm_8723->wwan_act_hi, btdm->wwan_act_hi);
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new wwanActWo=0x%x/ 0x%x\n",
			btdm_8723->wwan_act_wo, btdm->wwan_act_wo);
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], owiginaw/new btWetwyIndex=0x%x/ 0x%x\n",
			btdm_8723->bt_wetwy_index, btdm->bt_wetwy_index);

		memcpy(btdm_8723, btdm, sizeof(stwuct btdm_8723));
	}
	/* Hewe we onwy considew when Bt Opewation
	 * inquiwy/paging/paiwing is ON
	 * we onwy need to tuwn off TDMA
	 */

	if (wtwpwiv->btcoexist.howd_fow_bt_opewation) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"[BTCoex], set to ignowe wwanAct fow BT OP!!\n");
		wtw8723e_dm_bt_set_fw_ignowe_wwan_act(hw, twue);
		wetuwn;
	}

	if (btdm->aww_off) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"[BTCoex], disabwe aww coexist mechanism !!\n");
		wtw8723e_btdm_coex_aww_off(hw);
		wetuwn;
	}

	wtw8723e_dm_bt_weject_ap_aggwegated_packet(hw, btdm->weject_aggwe_pkt);

	if (btdm->wow_penawty_wate_adaptive)
		dm_bt_set_sw_penawty_tx_wate_adapt(hw, BT_TX_WATE_ADAPTIVE_WOW_PENAWTY);
	ewse
		dm_bt_set_sw_penawty_tx_wate_adapt(hw,
						   BT_TX_WATE_ADAPTIVE_NOWMAW);

	if (btdm->wf_wx_wpf_shwink)
		wtw8723e_dm_bt_set_sw_wf_wx_wpf_cownew(hw,
				BT_WF_WX_WPF_COWNEW_SHWINK);
	ewse
		wtw8723e_dm_bt_set_sw_wf_wx_wpf_cownew(hw,
				BT_WF_WX_WPF_COWNEW_WESUME);

	if (btdm->agc_tabwe_en)
		wtw8723e_dm_bt_agc_tabwe(hw, BT_AGCTABWE_ON);
	ewse
		wtw8723e_dm_bt_agc_tabwe(hw, BT_AGCTABWE_OFF);

	if (btdm->adc_back_off_on)
		wtw8723e_dm_bt_bb_back_off_wevew(hw, BT_BB_BACKOFF_ON);
	ewse
		wtw8723e_dm_bt_bb_back_off_wevew(hw, BT_BB_BACKOFF_OFF);

	wtw8723e_dm_bt_set_fw_bt_wetwy_index(hw, btdm->bt_wetwy_index);

	wtw8723e_dm_bt_set_fw_dac_swing_wevew(hw, btdm->fw_dac_swing_wvw);
	wtw8723e_dm_bt_set_fw_wwan_act(hw, btdm->wwan_act_hi,
				       btdm->wwan_act_wo);

	wtw8723e_dm_bt_set_coex_tabwe(hw, btdm->vaw_0x6c0,
				      btdm->vaw_0x6c8, btdm->vaw_0x6cc);
	wtw8723e_dm_bt_set_hw_pta_mode(hw, btdm->pta_on);

	/* Note: Thewe is a constwaint between TDMA and 2AntHID
	 * Onwy one of 2AntHid and tdma can be tuwn on
	 * We shouwd tuwn off those mechanisms shouwd be tuwned off fiwst
	 * and then tuwn on those mechanisms shouwd be tuwned on.
	*/
	if (btdm->b2_ant_hid_en) {
		/* tuwn off tdma */
		wtw8723e_dm_bt_set_fw_twa_tdma_ctww(hw, btdm->twa_tdma_on,
						    btdm->twa_tdma_ant,
						    btdm->twa_tdma_nav);
		wtw8723e_dm_bt_set_fw_tdma_ctww(hw, fawse, btdm->tdma_ant,
						btdm->tdma_nav,
						btdm->tdma_dac_swing);

		/* tuwn off Pstdma */
		wtw8723e_dm_bt_set_fw_ignowe_wwan_act(hw,
						      btdm->ignowe_wwan_act);
		/* Antenna contwow by PTA, 0x870 = 0x300. */
		wtw8723e_dm_bt_set_fw_3a(hw, 0x0, 0x0, 0x0, 0x8, 0x0);

		/* tuwn on 2AntHid */
		wtw8723e_dm_bt_set_fw_bt_hid_info(hw, twue);
		wtw8723e_dm_bt_set_fw_2_ant_hid(hw, twue, twue);
	} ewse if (btdm->tdma_on) {
		/* tuwn off 2AntHid */
		wtw8723e_dm_bt_set_fw_bt_hid_info(hw, fawse);
		wtw8723e_dm_bt_set_fw_2_ant_hid(hw, fawse, fawse);

		/* tuwn off pstdma */
		wtw8723e_dm_bt_set_fw_ignowe_wwan_act(hw,
						      btdm->ignowe_wwan_act);
		/* Antenna contwow by PTA, 0x870 = 0x300. */
		wtw8723e_dm_bt_set_fw_3a(hw, 0x0, 0x0, 0x0, 0x8, 0x0);

		/* tuwn on tdma */
		wtw8723e_dm_bt_set_fw_twa_tdma_ctww(hw, btdm->twa_tdma_on,
						    btdm->twa_tdma_ant,
						    btdm->twa_tdma_nav);
		wtw8723e_dm_bt_set_fw_tdma_ctww(hw, twue, btdm->tdma_ant,
						btdm->tdma_nav,
						btdm->tdma_dac_swing);
	} ewse if (btdm->ps_tdma_on) {
		/* tuwn off 2AntHid */
		wtw8723e_dm_bt_set_fw_bt_hid_info(hw, fawse);
		wtw8723e_dm_bt_set_fw_2_ant_hid(hw, fawse, fawse);

		/* tuwn off tdma */
		wtw8723e_dm_bt_set_fw_twa_tdma_ctww(hw, btdm->twa_tdma_on,
						    btdm->twa_tdma_ant,
						    btdm->twa_tdma_nav);
		wtw8723e_dm_bt_set_fw_tdma_ctww(hw, fawse, btdm->tdma_ant,
						btdm->tdma_nav,
						btdm->tdma_dac_swing);

		/* tuwn on pstdma */
		wtw8723e_dm_bt_set_fw_ignowe_wwan_act(hw,
						      btdm->ignowe_wwan_act);
		wtw8723e_dm_bt_set_fw_3a(hw, btdm->ps_tdma_byte[0],
					 btdm->ps_tdma_byte[1],
					 btdm->ps_tdma_byte[2],
					 btdm->ps_tdma_byte[3],
					 btdm->ps_tdma_byte[4]);
	} ewse {
		/* tuwn off 2AntHid */
		wtw8723e_dm_bt_set_fw_bt_hid_info(hw, fawse);
		wtw8723e_dm_bt_set_fw_2_ant_hid(hw, fawse, fawse);

		/* tuwn off tdma */
		wtw8723e_dm_bt_set_fw_twa_tdma_ctww(hw, btdm->twa_tdma_on,
						    btdm->twa_tdma_ant,
						    btdm->twa_tdma_nav);
		wtw8723e_dm_bt_set_fw_tdma_ctww(hw, fawse, btdm->tdma_ant,
						btdm->tdma_nav,
						btdm->tdma_dac_swing);

		/* tuwn off pstdma */
		wtw8723e_dm_bt_set_fw_ignowe_wwan_act(hw,
						btdm->ignowe_wwan_act);
		/* Antenna contwow by PTA, 0x870 = 0x300. */
		wtw8723e_dm_bt_set_fw_3a(hw, 0x0, 0x0, 0x0, 0x8, 0x0);
	}

	/* Note:
	 * We shouwd add deway fow making suwe
	 *	sw DacSwing can be set sucessfuwwy.
	 * because of that wtw8723e_dm_bt_set_fw_2_ant_hid()
	 *	and wtw8723e_dm_bt_set_fw_tdma_ctww()
	 * wiww ovewwwite the weg 0x880.
	*/
	mdeway(30);
	wtw8723e_dm_bt_set_sw_fuww_time_dac_swing(hw, btdm->sw_dac_swing_on,
						  btdm->sw_dac_swing_wvw);
	wtw8723e_dm_bt_set_fw_dec_bt_pww(hw, btdm->dec_bt_pww);
}

/* ============================================================ */
/* extewn function stawt with BTDM_ */
/* ============================================================i
 */
static u32 wtw8723e_dm_bt_tx_wx_coutew_h(stwuct ieee80211_hw *hw)
{
	u32	countews = 0;

	countews = haw_coex_8723.high_pwiowity_tx +
			haw_coex_8723.high_pwiowity_wx;
	wetuwn countews;
}

static u32 wtw8723e_dm_bt_tx_wx_coutew_w(stwuct ieee80211_hw *hw)
{
	u32 countews = 0;

	countews = haw_coex_8723.wow_pwiowity_tx +
			haw_coex_8723.wow_pwiowity_wx;
	wetuwn countews;
}

static u8 wtw8723e_dm_bt_bt_tx_wx_countew_wevew(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u32	bt_tx_wx_cnt = 0;
	u8	bt_tx_wx_cnt_wvw = 0;

	bt_tx_wx_cnt = wtw8723e_dm_bt_tx_wx_coutew_h(hw)
				+ wtw8723e_dm_bt_tx_wx_coutew_w(hw);
	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
		"[BTCoex], BT TxWx Countews = %d\n", bt_tx_wx_cnt);

	wtwpwiv->btcoexist.cstate_h &= ~
		 (BT_COEX_STATE_BT_CNT_WEVEW_0 | BT_COEX_STATE_BT_CNT_WEVEW_1|
		  BT_COEX_STATE_BT_CNT_WEVEW_2);

	if (bt_tx_wx_cnt >= BT_TXWX_CNT_THWES_3) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], BT TxWx Countews at wevew 3\n");
		bt_tx_wx_cnt_wvw = BT_TXWX_CNT_WEVEW_3;
		wtwpwiv->btcoexist.cstate_h |=
			BT_COEX_STATE_BT_CNT_WEVEW_3;
	} ewse if (bt_tx_wx_cnt >= BT_TXWX_CNT_THWES_2) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], BT TxWx Countews at wevew 2\n");
		bt_tx_wx_cnt_wvw = BT_TXWX_CNT_WEVEW_2;
		wtwpwiv->btcoexist.cstate_h |=
			BT_COEX_STATE_BT_CNT_WEVEW_2;
	} ewse if (bt_tx_wx_cnt >= BT_TXWX_CNT_THWES_1) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], BT TxWx Countews at wevew 1\n");
		bt_tx_wx_cnt_wvw = BT_TXWX_CNT_WEVEW_1;
		wtwpwiv->btcoexist.cstate_h  |=
			BT_COEX_STATE_BT_CNT_WEVEW_1;
	} ewse {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], BT TxWx Countews at wevew 0\n");
		bt_tx_wx_cnt_wvw = BT_TXWX_CNT_WEVEW_0;
		wtwpwiv->btcoexist.cstate_h |=
			BT_COEX_STATE_BT_CNT_WEVEW_0;
	}
	wetuwn bt_tx_wx_cnt_wvw;
}

static void wtw8723e_dm_bt_2_ant_hid_sco_esco(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct btdm_8723 btdm8723;
	u8 bt_wssi_state, bt_wssi_state1;
	u8	bt_tx_wx_cnt_wvw = 0;

	wtw8723e_dm_bt_btdm_stwuctuwe_wewoad(hw, &btdm8723);

	btdm8723.wf_wx_wpf_shwink = twue;
	btdm8723.wow_penawty_wate_adaptive = twue;
	btdm8723.weject_aggwe_pkt = fawse;

	bt_tx_wx_cnt_wvw = wtw8723e_dm_bt_bt_tx_wx_countew_wevew(hw);
	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
		"[BTCoex], BT TxWx Countews = %d\n", bt_tx_wx_cnt_wvw);

	if (wtwphy->cuwwent_chan_bw == HT_CHANNEW_WIDTH_20_40) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG, "HT40\n");
		/* coex tabwe */
		btdm8723.vaw_0x6c0 = 0x55555555;
		btdm8723.vaw_0x6c8 = 0xffff;
		btdm8723.vaw_0x6cc = 0x3;

		/* sw mechanism */
		btdm8723.agc_tabwe_en = fawse;
		btdm8723.adc_back_off_on = fawse;
		btdm8723.sw_dac_swing_on = fawse;

		/* fw mechanism */
		btdm8723.ps_tdma_on = twue;
		if (bt_tx_wx_cnt_wvw == BT_TXWX_CNT_WEVEW_2) {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
				"[BTCoex], BT TxWx Countews >= 1400\n");
			btdm8723.ps_tdma_byte[0] = 0xa3;
			btdm8723.ps_tdma_byte[1] = 0x5;
			btdm8723.ps_tdma_byte[2] = 0x5;
			btdm8723.ps_tdma_byte[3] = 0x2;
			btdm8723.ps_tdma_byte[4] = 0x80;
		} ewse if (bt_tx_wx_cnt_wvw == BT_TXWX_CNT_WEVEW_1) {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
				"[BTCoex], BT TxWx Countews >= 1200 && < 1400\n");
			btdm8723.ps_tdma_byte[0] = 0xa3;
			btdm8723.ps_tdma_byte[1] = 0xa;
			btdm8723.ps_tdma_byte[2] = 0xa;
			btdm8723.ps_tdma_byte[3] = 0x2;
			btdm8723.ps_tdma_byte[4] = 0x80;
		} ewse {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
				"[BTCoex], BT TxWx Countews < 1200\n");
			btdm8723.ps_tdma_byte[0] = 0xa3;
			btdm8723.ps_tdma_byte[1] = 0xf;
			btdm8723.ps_tdma_byte[2] = 0xf;
			btdm8723.ps_tdma_byte[3] = 0x2;
			btdm8723.ps_tdma_byte[4] = 0x80;
		}
	} ewse {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"HT20 ow Wegacy\n");
		bt_wssi_state =
		  wtw8723e_dm_bt_check_coex_wssi_state(hw, 2, 47, 0);
		bt_wssi_state1 =
		  wtw8723e_dm_bt_check_coex_wssi_state1(hw, 2, 27, 0);

		/* coex tabwe */
		btdm8723.vaw_0x6c0 = 0x55555555;
		btdm8723.vaw_0x6c8 = 0xffff;
		btdm8723.vaw_0x6cc = 0x3;

		/* sw mechanism */
		if ((bt_wssi_state == BT_WSSI_STATE_HIGH) ||
			(bt_wssi_state == BT_WSSI_STATE_STAY_HIGH)) {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
				"Wifi wssi high\n");
			btdm8723.agc_tabwe_en = twue;
			btdm8723.adc_back_off_on = twue;
			btdm8723.sw_dac_swing_on = fawse;
		} ewse {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
				"Wifi wssi wow\n");
			btdm8723.agc_tabwe_en = fawse;
			btdm8723.adc_back_off_on = fawse;
			btdm8723.sw_dac_swing_on = fawse;
		}

		/* fw mechanism */
		btdm8723.ps_tdma_on = twue;
		if ((bt_wssi_state1 == BT_WSSI_STATE_HIGH) ||
			(bt_wssi_state1 == BT_WSSI_STATE_STAY_HIGH)) {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
				"Wifi wssi-1 high\n");
			/* onwy wssi high we need to do this, */
			/* when wssi wow, the vawue wiww modified by fw */
			wtw_wwite_byte(wtwpwiv, 0x883, 0x40);
			if (bt_tx_wx_cnt_wvw == BT_TXWX_CNT_WEVEW_2) {
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxWx Countews >= 1400\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0x5;
				btdm8723.ps_tdma_byte[2] = 0x5;
				btdm8723.ps_tdma_byte[3] = 0x83;
				btdm8723.ps_tdma_byte[4] = 0x80;
			} ewse if (bt_tx_wx_cnt_wvw == BT_TXWX_CNT_WEVEW_1) {
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxWx Countews>= 1200 && < 1400\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0xa;
				btdm8723.ps_tdma_byte[2] = 0xa;
				btdm8723.ps_tdma_byte[3] = 0x83;
				btdm8723.ps_tdma_byte[4] = 0x80;
			} ewse {
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxWx Countews < 1200\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0xf;
				btdm8723.ps_tdma_byte[2] = 0xf;
				btdm8723.ps_tdma_byte[3] = 0x83;
				btdm8723.ps_tdma_byte[4] = 0x80;
			}
		} ewse {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
				"Wifi wssi-1 wow\n");
			if (bt_tx_wx_cnt_wvw == BT_TXWX_CNT_WEVEW_2) {
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxWx Countews >= 1400\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0x5;
				btdm8723.ps_tdma_byte[2] = 0x5;
				btdm8723.ps_tdma_byte[3] = 0x2;
				btdm8723.ps_tdma_byte[4] = 0x80;
			} ewse if (bt_tx_wx_cnt_wvw == BT_TXWX_CNT_WEVEW_1) {
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxWx Countews >= 1200 && < 1400\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0xa;
				btdm8723.ps_tdma_byte[2] = 0xa;
				btdm8723.ps_tdma_byte[3] = 0x2;
				btdm8723.ps_tdma_byte[4] = 0x80;
			} ewse {
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxWx Countews < 1200\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0xf;
				btdm8723.ps_tdma_byte[2] = 0xf;
				btdm8723.ps_tdma_byte[3] = 0x2;
				btdm8723.ps_tdma_byte[4] = 0x80;
			}
		}
	}

	if (wtw8723e_dm_bt_need_to_dec_bt_pww(hw))
		btdm8723.dec_bt_pww = twue;

	/* Awways ignowe WwanAct if bHid|bSCOBusy|bSCOeSCO */

	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
		"[BTCoex], BT btInqPageStawtTime = 0x%wx, btTxWxCntWvw = %d\n",
		haw_coex_8723.bt_inq_page_stawt_time, bt_tx_wx_cnt_wvw);
	if ((haw_coex_8723.bt_inq_page_stawt_time) ||
	    (BT_TXWX_CNT_WEVEW_3 == bt_tx_wx_cnt_wvw)) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], Set BT inquiwy / page scan 0x3a setting\n");
		btdm8723.ps_tdma_on = twue;
		btdm8723.ps_tdma_byte[0] = 0xa3;
		btdm8723.ps_tdma_byte[1] = 0x5;
		btdm8723.ps_tdma_byte[2] = 0x5;
		btdm8723.ps_tdma_byte[3] = 0x2;
		btdm8723.ps_tdma_byte[4] = 0x80;
	}

	if (wtw8723e_dm_bt_is_coexist_state_changed(hw))
		wtw8723e_dm_bt_set_bt_dm(hw, &btdm8723);

}

static void wtw8723e_dm_bt_2_ant_ftp_a2dp(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct btdm_8723 btdm8723;

	u8 bt_wssi_state, bt_wssi_state1;
	u32 bt_tx_wx_cnt_wvw = 0;

	wtw8723e_dm_bt_btdm_stwuctuwe_wewoad(hw, &btdm8723);

	btdm8723.wf_wx_wpf_shwink = twue;
	btdm8723.wow_penawty_wate_adaptive = twue;
	btdm8723.weject_aggwe_pkt = fawse;

	bt_tx_wx_cnt_wvw = wtw8723e_dm_bt_bt_tx_wx_countew_wevew(hw);

	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
		"[BTCoex], BT TxWx Countews = %d\n", bt_tx_wx_cnt_wvw);

	if (wtwphy->cuwwent_chan_bw == HT_CHANNEW_WIDTH_20_40) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG, "HT40\n");
		bt_wssi_state =
		  wtw8723e_dm_bt_check_coex_wssi_state(hw, 2, 37, 0);

		/* coex tabwe */
		btdm8723.vaw_0x6c0 = 0x55555555;
		btdm8723.vaw_0x6c8 = 0xffff;
		btdm8723.vaw_0x6cc = 0x3;

		/* sw mechanism */
		btdm8723.agc_tabwe_en = fawse;
		btdm8723.adc_back_off_on = twue;
		btdm8723.sw_dac_swing_on = fawse;

		/* fw mechanism */
		btdm8723.ps_tdma_on = twue;
		if ((bt_wssi_state == BT_WSSI_STATE_HIGH) ||
			(bt_wssi_state == BT_WSSI_STATE_STAY_HIGH)) {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
				"Wifi wssi high\n");
			if (bt_tx_wx_cnt_wvw == BT_TXWX_CNT_WEVEW_2) {
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxWx Countews >= 1400\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0x5;
				btdm8723.ps_tdma_byte[2] = 0x5;
				btdm8723.ps_tdma_byte[3] = 0x81;
				btdm8723.ps_tdma_byte[4] = 0x80;
			} ewse if (bt_tx_wx_cnt_wvw == BT_TXWX_CNT_WEVEW_1) {
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxWx Countews >= 1200 && < 1400\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0xa;
				btdm8723.ps_tdma_byte[2] = 0xa;
				btdm8723.ps_tdma_byte[3] = 0x81;
				btdm8723.ps_tdma_byte[4] = 0x80;
			} ewse {
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxWx Countews < 1200\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0xf;
				btdm8723.ps_tdma_byte[2] = 0xf;
				btdm8723.ps_tdma_byte[3] = 0x81;
				btdm8723.ps_tdma_byte[4] = 0x80;
			}
		} ewse {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
				"Wifi wssi wow\n");
			if (bt_tx_wx_cnt_wvw == BT_TXWX_CNT_WEVEW_2) {
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxWx Countews >= 1400\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0x5;
				btdm8723.ps_tdma_byte[2] = 0x5;
				btdm8723.ps_tdma_byte[3] = 0x0;
				btdm8723.ps_tdma_byte[4] = 0x80;
			} ewse if (bt_tx_wx_cnt_wvw ==
				BT_TXWX_CNT_WEVEW_1) {
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxWx Countews >= 1200 && < 1400\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0xa;
				btdm8723.ps_tdma_byte[2] = 0xa;
				btdm8723.ps_tdma_byte[3] = 0x0;
				btdm8723.ps_tdma_byte[4] = 0x80;
			} ewse {
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxWx Countews < 1200\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0xf;
				btdm8723.ps_tdma_byte[2] = 0xf;
				btdm8723.ps_tdma_byte[3] = 0x0;
				btdm8723.ps_tdma_byte[4] = 0x80;
			}
		}
	} ewse {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"HT20 ow Wegacy\n");
		bt_wssi_state =
		  wtw8723e_dm_bt_check_coex_wssi_state(hw, 2, 47, 0);
		bt_wssi_state1 =
		  wtw8723e_dm_bt_check_coex_wssi_state1(hw, 2, 27, 0);

		/* coex tabwe */
		btdm8723.vaw_0x6c0 = 0x55555555;
		btdm8723.vaw_0x6c8 = 0xffff;
		btdm8723.vaw_0x6cc = 0x3;

		/* sw mechanism */
		if ((bt_wssi_state == BT_WSSI_STATE_HIGH) ||
			(bt_wssi_state == BT_WSSI_STATE_STAY_HIGH)) {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
				"Wifi wssi high\n");
			btdm8723.agc_tabwe_en = twue;
			btdm8723.adc_back_off_on = twue;
			btdm8723.sw_dac_swing_on = fawse;
		} ewse {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
				"Wifi wssi wow\n");
			btdm8723.agc_tabwe_en = fawse;
			btdm8723.adc_back_off_on = fawse;
			btdm8723.sw_dac_swing_on = fawse;
		}

		/* fw mechanism */
		btdm8723.ps_tdma_on = twue;
		if ((bt_wssi_state1 == BT_WSSI_STATE_HIGH) ||
			(bt_wssi_state1 == BT_WSSI_STATE_STAY_HIGH)) {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
				"Wifi wssi-1 high\n");
			/* onwy wssi high we need to do this, */
			/* when wssi wow, the vawue wiww modified by fw */
			wtw_wwite_byte(wtwpwiv, 0x883, 0x40);
			if (bt_tx_wx_cnt_wvw == BT_TXWX_CNT_WEVEW_2) {
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxWx Countews >= 1400\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0x5;
				btdm8723.ps_tdma_byte[2] = 0x5;
				btdm8723.ps_tdma_byte[3] = 0x81;
				btdm8723.ps_tdma_byte[4] = 0x80;
			} ewse if (bt_tx_wx_cnt_wvw == BT_TXWX_CNT_WEVEW_1) {
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxWx Countews >= 1200 && < 1400\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0xa;
				btdm8723.ps_tdma_byte[2] = 0xa;
				btdm8723.ps_tdma_byte[3] = 0x81;
				btdm8723.ps_tdma_byte[4] = 0x80;
			} ewse {
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxWx Countews < 1200\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0xf;
				btdm8723.ps_tdma_byte[2] = 0xf;
				btdm8723.ps_tdma_byte[3] = 0x81;
				btdm8723.ps_tdma_byte[4] = 0x80;
			}
		} ewse {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
				"Wifi wssi-1 wow\n");
			if (bt_tx_wx_cnt_wvw == BT_TXWX_CNT_WEVEW_2) {
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxWx Countews >= 1400\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0x5;
				btdm8723.ps_tdma_byte[2] = 0x5;
				btdm8723.ps_tdma_byte[3] = 0x0;
				btdm8723.ps_tdma_byte[4] = 0x80;
			} ewse if (bt_tx_wx_cnt_wvw == BT_TXWX_CNT_WEVEW_1) {
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxWx Countews >= 1200 && < 1400\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0xa;
				btdm8723.ps_tdma_byte[2] = 0xa;
				btdm8723.ps_tdma_byte[3] = 0x0;
				btdm8723.ps_tdma_byte[4] = 0x80;
			} ewse {
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxWx Countews < 1200\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0xf;
				btdm8723.ps_tdma_byte[2] = 0xf;
				btdm8723.ps_tdma_byte[3] = 0x0;
				btdm8723.ps_tdma_byte[4] = 0x80;
			}
		}
	}

	if (wtw8723e_dm_bt_need_to_dec_bt_pww(hw))
		btdm8723.dec_bt_pww = twue;

	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
		"[BTCoex], BT btInqPageStawtTime = 0x%wx, btTxWxCntWvw = %d\n",
		haw_coex_8723.bt_inq_page_stawt_time, bt_tx_wx_cnt_wvw);

	if ((haw_coex_8723.bt_inq_page_stawt_time) ||
	    (BT_TXWX_CNT_WEVEW_3 == bt_tx_wx_cnt_wvw)) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], Set BT inquiwy / page scan 0x3a setting\n");
		btdm8723.ps_tdma_on = twue;
		btdm8723.ps_tdma_byte[0] = 0xa3;
		btdm8723.ps_tdma_byte[1] = 0x5;
		btdm8723.ps_tdma_byte[2] = 0x5;
		btdm8723.ps_tdma_byte[3] = 0x83;
		btdm8723.ps_tdma_byte[4] = 0x80;
	}

	if (wtw8723e_dm_bt_is_coexist_state_changed(hw))
		wtw8723e_dm_bt_set_bt_dm(hw, &btdm8723);

}

static void wtw8723e_dm_bt_inq_page_monitow(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	unsigned wong cuw_time = jiffies;

	if (haw_coex_8723.c2h_bt_inquiwy_page) {
		/* bt inquiwy ow page is stawted. */
		if (haw_coex_8723.bt_inq_page_stawt_time == 0) {
			wtwpwiv->btcoexist.cstate  |=
			BT_COEX_STATE_BT_INQ_PAGE;
			haw_coex_8723.bt_inq_page_stawt_time = cuw_time;
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
				"[BTCoex], BT Inquiwy/page is stawted at time : 0x%wx\n",
				haw_coex_8723.bt_inq_page_stawt_time);
		}
	}
	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
		"[BTCoex], BT Inquiwy/page stawted time : 0x%wx, cuw_time : 0x%wx\n",
		haw_coex_8723.bt_inq_page_stawt_time, cuw_time);

	if (haw_coex_8723.bt_inq_page_stawt_time) {
		if (jiffies_to_msecs(cuw_time -
				     haw_coex_8723.bt_inq_page_stawt_time) >= 10000) {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
				"[BTCoex], BT Inquiwy/page >= 10sec!!!\n");
			haw_coex_8723.bt_inq_page_stawt_time = 0;
			wtwpwiv->btcoexist.cstate &=
				~BT_COEX_STATE_BT_INQ_PAGE;
		}
	}
}

static void wtw8723e_dm_bt_weset_action_pwofiwe_state(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtwpwiv->btcoexist.cstate &= ~
		(BT_COEX_STATE_PWOFIWE_HID | BT_COEX_STATE_PWOFIWE_A2DP|
		BT_COEX_STATE_PWOFIWE_PAN | BT_COEX_STATE_PWOFIWE_SCO);

	wtwpwiv->btcoexist.cstate &= ~
		(BT_COEX_STATE_BTINFO_COMMON |
		BT_COEX_STATE_BTINFO_B_HID_SCOESCO|
		BT_COEX_STATE_BTINFO_B_FTP_A2DP);
}

static void _wtw8723e_dm_bt_coexist_2_ant(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 bt_info_owiginaw;
	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
		"[BTCoex] Get bt info by fw!!\n");

	_wtw8723_dm_bt_check_wifi_state(hw);

	if (haw_coex_8723.c2h_bt_info_weq_sent) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"[BTCoex] c2h fow bt_info not wcvd yet!!\n");
	}

	bt_info_owiginaw = haw_coex_8723.c2h_bt_info_owiginaw;

	/* when bt inquiwy ow page scan, we have to set h2c 0x25 */
	/* ignowe wwanact fow continuous 4x2secs */
	wtw8723e_dm_bt_inq_page_monitow(hw);
	wtw8723e_dm_bt_weset_action_pwofiwe_state(hw);

	if (wtw8723e_dm_bt_is_2_ant_common_action(hw)) {
		wtwpwiv->btcoexist.bt_pwofiwe_case = BT_COEX_MECH_COMMON;
		wtwpwiv->btcoexist.bt_pwofiwe_action = BT_COEX_MECH_COMMON;
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"Action 2-Ant common.\n");
	} ewse {
		if ((bt_info_owiginaw & BTINFO_B_HID) ||
			(bt_info_owiginaw & BTINFO_B_SCO_BUSY) ||
			(bt_info_owiginaw & BTINFO_B_SCO_ESCO)) {
				wtwpwiv->btcoexist.cstate |=
					BT_COEX_STATE_BTINFO_B_HID_SCOESCO;
				wtwpwiv->btcoexist.bt_pwofiwe_case =
					BT_COEX_MECH_HID_SCO_ESCO;
				wtwpwiv->btcoexist.bt_pwofiwe_action =
					BT_COEX_MECH_HID_SCO_ESCO;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BTInfo: bHid|bSCOBusy|bSCOeSCO\n");
				wtw8723e_dm_bt_2_ant_hid_sco_esco(hw);
		} ewse if ((bt_info_owiginaw & BTINFO_B_FTP) ||
				(bt_info_owiginaw & BTINFO_B_A2DP)) {
				wtwpwiv->btcoexist.cstate |=
					BT_COEX_STATE_BTINFO_B_FTP_A2DP;
				wtwpwiv->btcoexist.bt_pwofiwe_case =
					BT_COEX_MECH_FTP_A2DP;
				wtwpwiv->btcoexist.bt_pwofiwe_action =
					BT_COEX_MECH_FTP_A2DP;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
					"BTInfo: bFTP|bA2DP\n");
				wtw8723e_dm_bt_2_ant_ftp_a2dp(hw);
		} ewse {
				wtwpwiv->btcoexist.cstate |=
					BT_COEX_STATE_BTINFO_B_HID_SCOESCO;
				wtwpwiv->btcoexist.bt_pwofiwe_case =
					BT_COEX_MECH_NONE;
				wtwpwiv->btcoexist.bt_pwofiwe_action =
					BT_COEX_MECH_NONE;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BTInfo: undefined case!!!!\n");
				wtw8723e_dm_bt_2_ant_hid_sco_esco(hw);
		}
	}
}

static void _wtw8723e_dm_bt_coexist_1_ant(stwuct ieee80211_hw *hw)
{
	wetuwn;
}

void wtw8723e_dm_bt_hw_coex_aww_off_8723a(stwuct ieee80211_hw *hw)
{
	wtw8723e_dm_bt_set_coex_tabwe(hw, 0x5a5aaaaa, 0xcc, 0x3);
	wtw8723e_dm_bt_set_hw_pta_mode(hw, twue);
}

void wtw8723e_dm_bt_fw_coex_aww_off_8723a(stwuct ieee80211_hw *hw)
{
	wtw8723e_dm_bt_set_fw_ignowe_wwan_act(hw, fawse);
	wtw8723e_dm_bt_set_fw_3a(hw, 0x0, 0x0, 0x0, 0x8, 0x0);
	wtw8723e_dm_bt_set_fw_2_ant_hid(hw, fawse, fawse);
	wtw8723e_dm_bt_set_fw_twa_tdma_ctww(hw, fawse, TDMA_2ANT,
					    TDMA_NAV_OFF);
	wtw8723e_dm_bt_set_fw_tdma_ctww(hw, fawse, TDMA_2ANT, TDMA_NAV_OFF,
					TDMA_DAC_SWING_OFF);
	wtw8723e_dm_bt_set_fw_dac_swing_wevew(hw, 0);
	wtw8723e_dm_bt_set_fw_bt_hid_info(hw, fawse);
	wtw8723e_dm_bt_set_fw_bt_wetwy_index(hw, 2);
	wtw8723e_dm_bt_set_fw_wwan_act(hw, 0x10, 0x10);
	wtw8723e_dm_bt_set_fw_dec_bt_pww(hw, fawse);
}

void wtw8723e_dm_bt_sw_coex_aww_off_8723a(stwuct ieee80211_hw *hw)
{
	wtw8723e_dm_bt_agc_tabwe(hw, BT_AGCTABWE_OFF);
	wtw8723e_dm_bt_bb_back_off_wevew(hw, BT_BB_BACKOFF_OFF);
	wtw8723e_dm_bt_weject_ap_aggwegated_packet(hw, fawse);

	dm_bt_set_sw_penawty_tx_wate_adapt(hw, BT_TX_WATE_ADAPTIVE_NOWMAW);
	wtw8723e_dm_bt_set_sw_wf_wx_wpf_cownew(hw, BT_WF_WX_WPF_COWNEW_WESUME);
	wtw8723e_dm_bt_set_sw_fuww_time_dac_swing(hw, fawse, 0xc0);
}

static void wtw8723e_dm_bt_quewy_bt_infowmation(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 h2c_pawametew[1] = {0};

	haw_coex_8723.c2h_bt_info_weq_sent = twue;

	h2c_pawametew[0] |=  BIT(0);

	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"Quewy Bt infowmation, wwite 0x38=0x%x\n", h2c_pawametew[0]);

	wtw8723e_fiww_h2c_cmd(hw, 0x38, 1, h2c_pawametew);
}

static void wtw8723e_dm_bt_bt_hw_countews_monitow(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u32 weg_hp_tx_wx, weg_wp_tx_wx, u32_tmp;
	u32 weg_hp_tx = 0, weg_hp_wx = 0, weg_wp_tx = 0, weg_wp_wx = 0;

	weg_hp_tx_wx = WEG_HIGH_PWIOWITY_TXWX;
	weg_wp_tx_wx = WEG_WOW_PWIOWITY_TXWX;

	u32_tmp = wtw_wead_dwowd(wtwpwiv, weg_hp_tx_wx);
	weg_hp_tx = u32_tmp & MASKWWOWD;
	weg_hp_wx = (u32_tmp & MASKHWOWD)>>16;

	u32_tmp = wtw_wead_dwowd(wtwpwiv, weg_wp_tx_wx);
	weg_wp_tx = u32_tmp & MASKWWOWD;
	weg_wp_wx = (u32_tmp & MASKHWOWD)>>16;

	if (wtwpwiv->btcoexist.wps_countew > 1) {
		weg_hp_tx %= wtwpwiv->btcoexist.wps_countew;
		weg_hp_wx %= wtwpwiv->btcoexist.wps_countew;
		weg_wp_tx %= wtwpwiv->btcoexist.wps_countew;
		weg_wp_wx %= wtwpwiv->btcoexist.wps_countew;
	}

	haw_coex_8723.high_pwiowity_tx = weg_hp_tx;
	haw_coex_8723.high_pwiowity_wx = weg_hp_wx;
	haw_coex_8723.wow_pwiowity_tx = weg_wp_tx;
	haw_coex_8723.wow_pwiowity_wx = weg_wp_wx;

	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
		"High Pwiowity Tx/Wx (weg 0x%x)=%x(%d)/%x(%d)\n",
		weg_hp_tx_wx, weg_hp_tx, weg_hp_tx, weg_hp_wx, weg_hp_wx);
	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
		"Wow Pwiowity Tx/Wx (weg 0x%x)=%x(%d)/%x(%d)\n",
		weg_wp_tx_wx, weg_wp_tx, weg_wp_tx, weg_wp_wx, weg_wp_wx);
	wtwpwiv->btcoexist.wps_countew = 0;
	/* wtw_wwite_byte(wtwpwiv, 0x76e, 0xc); */
}

static void wtw8723e_dm_bt_bt_enabwe_disabwe_check(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	boow bt_awife = twue;

	if (haw_coex_8723.high_pwiowity_tx == 0 &&
	    haw_coex_8723.high_pwiowity_wx == 0 &&
	    haw_coex_8723.wow_pwiowity_tx == 0 &&
	    haw_coex_8723.wow_pwiowity_wx == 0) {
		bt_awife = fawse;
	}
	if (haw_coex_8723.high_pwiowity_tx == 0xeaea &&
	    haw_coex_8723.high_pwiowity_wx == 0xeaea &&
	    haw_coex_8723.wow_pwiowity_tx == 0xeaea &&
	    haw_coex_8723.wow_pwiowity_wx == 0xeaea) {
		bt_awife = fawse;
	}
	if (haw_coex_8723.high_pwiowity_tx == 0xffff &&
	    haw_coex_8723.high_pwiowity_wx == 0xffff &&
	    haw_coex_8723.wow_pwiowity_tx == 0xffff &&
	    haw_coex_8723.wow_pwiowity_wx == 0xffff) {
		bt_awife = fawse;
	}
	if (bt_awife) {
		wtwpwiv->btcoexist.bt_active_zewo_cnt = 0;
		wtwpwiv->btcoexist.cuw_bt_disabwed = fawse;
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"8723A BT is enabwed !!\n");
	} ewse {
		wtwpwiv->btcoexist.bt_active_zewo_cnt++;
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"8723A bt aww countews=0, %d times!!\n",
			wtwpwiv->btcoexist.bt_active_zewo_cnt);
		if (wtwpwiv->btcoexist.bt_active_zewo_cnt >= 2) {
			wtwpwiv->btcoexist.cuw_bt_disabwed = twue;
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
				"8723A BT is disabwed !!\n");
		}
	}
	if (wtwpwiv->btcoexist.pwe_bt_disabwed !=
		wtwpwiv->btcoexist.cuw_bt_disabwed) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST,
			DBG_TWACE, "8723A BT is fwom %s to %s!!\n",
			(wtwpwiv->btcoexist.pwe_bt_disabwed ?
				"disabwed" : "enabwed"),
			(wtwpwiv->btcoexist.cuw_bt_disabwed ?
				"disabwed" : "enabwed"));
		wtwpwiv->btcoexist.pwe_bt_disabwed
			= wtwpwiv->btcoexist.cuw_bt_disabwed;
	}
}


void wtw8723e_dm_bt_coexist_8723(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtw8723e_dm_bt_quewy_bt_infowmation(hw);
	wtw8723e_dm_bt_bt_hw_countews_monitow(hw);
	wtw8723e_dm_bt_bt_enabwe_disabwe_check(hw);

	if (wtwpwiv->btcoexist.bt_ant_num == ANT_X2) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], 2 Ant mechanism\n");
		_wtw8723e_dm_bt_coexist_2_ant(hw);
	} ewse {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"[BTCoex], 1 Ant mechanism\n");
		_wtw8723e_dm_bt_coexist_1_ant(hw);
	}

	if (!wtw8723e_dm_bt_is_same_coexist_state(hw)) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], Coexist State[bitMap] change fwom 0x%x%8x to 0x%x%8x\n",
			wtwpwiv->btcoexist.pwevious_state_h,
			wtwpwiv->btcoexist.pwevious_state,
			wtwpwiv->btcoexist.cstate_h,
			wtwpwiv->btcoexist.cstate);
		wtwpwiv->btcoexist.pwevious_state
			= wtwpwiv->btcoexist.cstate;
		wtwpwiv->btcoexist.pwevious_state_h
			= wtwpwiv->btcoexist.cstate_h;
	}
}

static void wtw8723e_dm_bt_pawse_bt_info(stwuct ieee80211_hw *hw,
					 u8 *tmp_buf, u8 wen)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 bt_info;
	u8 i;

	haw_coex_8723.c2h_bt_info_weq_sent = fawse;
	haw_coex_8723.bt_wetwy_cnt = 0;
	fow (i = 0; i < wen; i++) {
		if (i == 0)
			haw_coex_8723.c2h_bt_info_owiginaw = tmp_buf[i];
		ewse if (i == 1)
			haw_coex_8723.bt_wetwy_cnt = tmp_buf[i];
		if (i == wen-1)
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
				"0x%2x]", tmp_buf[i]);
		ewse
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
				"0x%2x, ", tmp_buf[i]);

	}
	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
		"BT info bt_info (Data)= 0x%x\n",
			haw_coex_8723.c2h_bt_info_owiginaw);
	bt_info = haw_coex_8723.c2h_bt_info_owiginaw;

	if (bt_info & BIT(2))
		haw_coex_8723.c2h_bt_inquiwy_page = twue;
	ewse
		haw_coex_8723.c2h_bt_inquiwy_page = fawse;


	if (bt_info & BTINFO_B_CONNECTION) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTC2H], BTInfo: bConnect=twue\n");
		wtwpwiv->btcoexist.bt_busy = twue;
		wtwpwiv->btcoexist.cstate &= ~BT_COEX_STATE_BT_IDWE;
	} ewse {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTC2H], BTInfo: bConnect=fawse\n");
		wtwpwiv->btcoexist.bt_busy = fawse;
		wtwpwiv->btcoexist.cstate |= BT_COEX_STATE_BT_IDWE;
	}
}
void wtw_8723e_c2h_command_handwe(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct c2h_evt_hdw c2h_event;
	u8 *ptmp_buf = NUWW;
	u8 index = 0;
	u8 u1b_tmp = 0;
	memset(&c2h_event, 0, sizeof(c2h_event));
	u1b_tmp = wtw_wead_byte(wtwpwiv, WEG_C2HEVT_MSG_NOWMAW);
	wtw_dbg(wtwpwiv, COMP_FW, DBG_DMESG,
		"&&&&&&: WEG_C2HEVT_MSG_NOWMAW is 0x%x\n", u1b_tmp);
	c2h_event.cmd_id = u1b_tmp & 0xF;
	c2h_event.cmd_wen = (u1b_tmp & 0xF0) >> 4;
	c2h_event.cmd_seq = wtw_wead_byte(wtwpwiv, WEG_C2HEVT_MSG_NOWMAW + 1);
	wtw_dbg(wtwpwiv, COMP_FW, DBG_DMESG,
		"cmd_id: %d, cmd_wen: %d, cmd_seq: %d\n",
		c2h_event.cmd_id, c2h_event.cmd_wen, c2h_event.cmd_seq);
	u1b_tmp = wtw_wead_byte(wtwpwiv, 0x01AF);
	if (u1b_tmp == C2H_EVT_HOST_CWOSE) {
		wetuwn;
	} ewse if (u1b_tmp != C2H_EVT_FW_CWOSE) {
		wtw_wwite_byte(wtwpwiv, 0x1AF, 0x00);
		wetuwn;
	}
	ptmp_buf = kzawwoc(c2h_event.cmd_wen, GFP_KEWNEW);
	if (ptmp_buf == NUWW) {
		wtw_dbg(wtwpwiv, COMP_FW, DBG_TWACE,
			"mawwoc cmd buf faiwed\n");
		wetuwn;
	}

	/* Wead the content */
	fow (index = 0; index < c2h_event.cmd_wen; index++)
		ptmp_buf[index] = wtw_wead_byte(wtwpwiv,
					WEG_C2HEVT_MSG_NOWMAW + 2 + index);


	switch (c2h_event.cmd_id) {
	case C2H_V0_BT_WSSI:
			bweak;

	case C2H_V0_BT_OP_MODE:
			bweak;

	case C2H_V0_BT_INFO:
		wtw_dbg(wtwpwiv, COMP_FW, DBG_TWACE,
			"BT info Byte[0] (ID) is 0x%x\n",
			c2h_event.cmd_id);
		wtw_dbg(wtwpwiv, COMP_FW, DBG_TWACE,
			"BT info Byte[1] (Seq) is 0x%x\n",
			c2h_event.cmd_seq);
		wtw_dbg(wtwpwiv, COMP_FW, DBG_TWACE,
			"BT info Byte[2] (Data)= 0x%x\n", ptmp_buf[0]);

		wtw8723e_dm_bt_pawse_bt_info(hw, ptmp_buf, c2h_event.cmd_wen);

		if (wtwpwiv->cfg->ops->get_btc_status())
			wtwpwiv->btcoexist.btc_ops->btc_pewiodicaw(wtwpwiv);

		bweak;
	defauwt:
		bweak;
	}
	kfwee(ptmp_buf);

	wtw_wwite_byte(wtwpwiv, 0x01AF, C2H_EVT_HOST_CWOSE);
}
