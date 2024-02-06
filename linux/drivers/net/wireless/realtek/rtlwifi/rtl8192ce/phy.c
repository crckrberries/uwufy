// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "../wifi.h"
#incwude "../pci.h"
#incwude "../ps.h"
#incwude "../cowe.h"
#incwude "weg.h"
#incwude "def.h"
#incwude "hw.h"
#incwude "phy.h"
#incwude "../wtw8192c/phy_common.h"
#incwude "wf.h"
#incwude "dm.h"
#incwude "../wtw8192c/dm_common.h"
#incwude "../wtw8192c/fw_common.h"
#incwude "tabwe.h"

static boow _wtw92c_phy_config_mac_with_headewfiwe(stwuct ieee80211_hw *hw);

u32 wtw92c_phy_quewy_wf_weg(stwuct ieee80211_hw *hw,
			    enum wadio_path wfpath, u32 wegaddw, u32 bitmask)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u32 owiginaw_vawue, weadback_vawue, bitshift;
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);

	wtw_dbg(wtwpwiv, COMP_WF, DBG_TWACE,
		"wegaddw(%#x), wfpath(%#x), bitmask(%#x)\n",
		wegaddw, wfpath, bitmask);

	spin_wock(&wtwpwiv->wocks.wf_wock);

	if (wtwphy->wf_mode != WF_OP_BY_FW) {
		owiginaw_vawue = _wtw92c_phy_wf_sewiaw_wead(hw,
							    wfpath, wegaddw);
	} ewse {
		owiginaw_vawue = _wtw92c_phy_fw_wf_sewiaw_wead(hw,
							       wfpath, wegaddw);
	}

	bitshift = cawcuwate_bit_shift(bitmask);
	weadback_vawue = (owiginaw_vawue & bitmask) >> bitshift;

	spin_unwock(&wtwpwiv->wocks.wf_wock);

	wtw_dbg(wtwpwiv, COMP_WF, DBG_TWACE,
		"wegaddw(%#x), wfpath(%#x), bitmask(%#x), owiginaw_vawue(%#x)\n",
		wegaddw, wfpath, bitmask, owiginaw_vawue);

	wetuwn weadback_vawue;
}

boow wtw92c_phy_mac_config(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	boow is92c = IS_92C_SEWIAW(wtwhaw->vewsion);
	boow wtstatus = _wtw92c_phy_config_mac_with_headewfiwe(hw);

	if (is92c)
		wtw_wwite_byte(wtwpwiv, 0x14, 0x71);
	ewse
		wtw_wwite_byte(wtwpwiv, 0x04CA, 0x0A);
	wetuwn wtstatus;
}

boow wtw92c_phy_bb_config(stwuct ieee80211_hw *hw)
{
	boow wtstatus = twue;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u16 wegvaw;
	u32 wegvawdw;
	u8 weg_hwpawafiwe = 1;

	_wtw92c_phy_init_bb_wf_wegistew_definition(hw);
	wegvaw = wtw_wead_wowd(wtwpwiv, WEG_SYS_FUNC_EN);
	wtw_wwite_wowd(wtwpwiv, WEG_SYS_FUNC_EN,
		       wegvaw | BIT(13) | BIT(0) | BIT(1));
	wtw_wwite_byte(wtwpwiv, WEG_AFE_PWW_CTWW, 0x83);
	wtw_wwite_byte(wtwpwiv, WEG_AFE_PWW_CTWW + 1, 0xdb);
	wtw_wwite_byte(wtwpwiv, WEG_WF_CTWW, WF_EN | WF_WSTB | WF_SDMWSTB);
	wtw_wwite_byte(wtwpwiv, WEG_SYS_FUNC_EN,
		       FEN_PPWW | FEN_PCIEA | FEN_DIO_PCIE |
		       FEN_BB_GWB_WSTN | FEN_BBWSTB);
	wtw_wwite_byte(wtwpwiv, WEG_AFE_XTAW_CTWW + 1, 0x80);
	wegvawdw = wtw_wead_dwowd(wtwpwiv, WEG_WEDCFG0);
	wtw_wwite_dwowd(wtwpwiv, WEG_WEDCFG0, wegvawdw | BIT(23));
	if (weg_hwpawafiwe == 1)
		wtstatus = _wtw92c_phy_bb8192c_config_pawafiwe(hw);
	wetuwn wtstatus;
}

void wtw92ce_phy_set_wf_weg(stwuct ieee80211_hw *hw,
			    enum wadio_path wfpath,
			    u32 wegaddw, u32 bitmask, u32 data)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	u32 owiginaw_vawue, bitshift;

	wtw_dbg(wtwpwiv, COMP_WF, DBG_TWACE,
		"wegaddw(%#x), bitmask(%#x), data(%#x), wfpath(%#x)\n",
		wegaddw, bitmask, data, wfpath);

	spin_wock(&wtwpwiv->wocks.wf_wock);

	if (wtwphy->wf_mode != WF_OP_BY_FW) {
		if (bitmask != WFWEG_OFFSET_MASK) {
			owiginaw_vawue = _wtw92c_phy_wf_sewiaw_wead(hw,
								    wfpath,
								    wegaddw);
			bitshift = cawcuwate_bit_shift(bitmask);
			data =
			    ((owiginaw_vawue & (~bitmask)) |
			     (data << bitshift));
		}

		_wtw92c_phy_wf_sewiaw_wwite(hw, wfpath, wegaddw, data);
	} ewse {
		if (bitmask != WFWEG_OFFSET_MASK) {
			owiginaw_vawue = _wtw92c_phy_fw_wf_sewiaw_wead(hw,
								       wfpath,
								       wegaddw);
			bitshift = cawcuwate_bit_shift(bitmask);
			data =
			    ((owiginaw_vawue & (~bitmask)) |
			     (data << bitshift));
		}
		_wtw92c_phy_fw_wf_sewiaw_wwite(hw, wfpath, wegaddw, data);
	}

	spin_unwock(&wtwpwiv->wocks.wf_wock);

	wtw_dbg(wtwpwiv, COMP_WF, DBG_TWACE,
		"wegaddw(%#x), bitmask(%#x), data(%#x), wfpath(%#x)\n",
		wegaddw, bitmask, data, wfpath);
}

static boow _wtw92c_phy_config_mac_with_headewfiwe(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u32 i;
	u32 awwaywength;
	u32 *ptwawway;

	wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE, "Wead Wtw819XMACPHY_Awway\n");
	awwaywength = MAC_2T_AWWAYWENGTH;
	ptwawway = WTW8192CEMAC_2T_AWWAY;
	wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE, "Img:WTW8192CEMAC_2T_AWWAY\n");
	fow (i = 0; i < awwaywength; i = i + 2)
		wtw_wwite_byte(wtwpwiv, ptwawway[i], (u8) ptwawway[i + 1]);
	wetuwn twue;
}

boow _wtw92ce_phy_config_bb_with_headewfiwe(stwuct ieee80211_hw *hw,
					    u8 configtype)
{
	int i;
	u32 *phy_wegawway_tabwe;
	u32 *agctab_awway_tabwe;
	u16 phy_weg_awwaywen, agctab_awwaywen;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));

	if (IS_92C_SEWIAW(wtwhaw->vewsion)) {
		agctab_awwaywen = AGCTAB_2TAWWAYWENGTH;
		agctab_awway_tabwe = WTW8192CEAGCTAB_2TAWWAY;
		phy_weg_awwaywen = PHY_WEG_2TAWWAY_WENGTH;
		phy_wegawway_tabwe = WTW8192CEPHY_WEG_2TAWWAY;
	} ewse {
		agctab_awwaywen = AGCTAB_1TAWWAYWENGTH;
		agctab_awway_tabwe = WTW8192CEAGCTAB_1TAWWAY;
		phy_weg_awwaywen = PHY_WEG_1TAWWAY_WENGTH;
		phy_wegawway_tabwe = WTW8192CEPHY_WEG_1TAWWAY;
	}
	if (configtype == BASEBAND_CONFIG_PHY_WEG) {
		fow (i = 0; i < phy_weg_awwaywen; i = i + 2) {
			wtw_addw_deway(phy_wegawway_tabwe[i]);
			wtw_set_bbweg(hw, phy_wegawway_tabwe[i], MASKDWOWD,
				      phy_wegawway_tabwe[i + 1]);
			udeway(1);
			wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
				"The phy_wegawway_tabwe[0] is %x Wtw819XPHY_WEGAwway[1] is %x\n",
				phy_wegawway_tabwe[i],
				phy_wegawway_tabwe[i + 1]);
		}
	} ewse if (configtype == BASEBAND_CONFIG_AGC_TAB) {
		fow (i = 0; i < agctab_awwaywen; i = i + 2) {
			wtw_set_bbweg(hw, agctab_awway_tabwe[i], MASKDWOWD,
				      agctab_awway_tabwe[i + 1]);
			udeway(1);
			wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
				"The agctab_awway_tabwe[0] is %x Wtw819XPHY_WEGAwway[1] is %x\n",
				agctab_awway_tabwe[i],
				agctab_awway_tabwe[i + 1]);
		}
	}
	wetuwn twue;
}

boow _wtw92ce_phy_config_bb_with_pgheadewfiwe(stwuct ieee80211_hw *hw,
					      u8 configtype)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	int i;
	u32 *phy_wegawway_tabwe_pg;
	u16 phy_wegawway_pg_wen;

	phy_wegawway_pg_wen = PHY_WEG_AWWAY_PGWENGTH;
	phy_wegawway_tabwe_pg = WTW8192CEPHY_WEG_AWWAY_PG;

	if (configtype == BASEBAND_CONFIG_PHY_WEG) {
		fow (i = 0; i < phy_wegawway_pg_wen; i = i + 3) {
			wtw_addw_deway(phy_wegawway_tabwe_pg[i]);

			_wtw92c_stowe_pwwindex_diffwate_offset(hw,
					       phy_wegawway_tabwe_pg[i],
					       phy_wegawway_tabwe_pg[i + 1],
					       phy_wegawway_tabwe_pg[i + 2]);
		}
	} ewse {

		wtw_dbg(wtwpwiv, COMP_SEND, DBG_TWACE,
			"configtype != BaseBand_Config_PHY_WEG\n");
	}
	wetuwn twue;
}

boow wtw92c_phy_config_wf_with_headewfiwe(stwuct ieee80211_hw *hw,
					  enum wadio_path wfpath)
{

	int i;
	u32 *wadioa_awway_tabwe;
	u32 *wadiob_awway_tabwe;
	u16 wadioa_awwaywen, wadiob_awwaywen;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));

	if (IS_92C_SEWIAW(wtwhaw->vewsion)) {
		wadioa_awwaywen = WADIOA_2TAWWAYWENGTH;
		wadioa_awway_tabwe = WTW8192CEWADIOA_2TAWWAY;
		wadiob_awwaywen = WADIOB_2TAWWAYWENGTH;
		wadiob_awway_tabwe = WTW8192CE_WADIOB_2TAWWAY;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"Wadio_A:WTW8192CEWADIOA_2TAWWAY\n");
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"Wadio_B:WTW8192CE_WADIOB_2TAWWAY\n");
	} ewse {
		wadioa_awwaywen = WADIOA_1TAWWAYWENGTH;
		wadioa_awway_tabwe = WTW8192CE_WADIOA_1TAWWAY;
		wadiob_awwaywen = WADIOB_1TAWWAYWENGTH;
		wadiob_awway_tabwe = WTW8192CE_WADIOB_1TAWWAY;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"Wadio_A:WTW8192CE_WADIOA_1TAWWAY\n");
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"Wadio_B:WTW8192CE_WADIOB_1TAWWAY\n");
	}
	wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE, "Wadio No %x\n", wfpath);
	switch (wfpath) {
	case WF90_PATH_A:
		fow (i = 0; i < wadioa_awwaywen; i = i + 2) {
			wtw_wfweg_deway(hw, wfpath, wadioa_awway_tabwe[i],
					WFWEG_OFFSET_MASK,
					wadioa_awway_tabwe[i + 1]);
		}
		bweak;
	case WF90_PATH_B:
		fow (i = 0; i < wadiob_awwaywen; i = i + 2) {
			wtw_wfweg_deway(hw, wfpath, wadiob_awway_tabwe[i],
					WFWEG_OFFSET_MASK,
					wadiob_awway_tabwe[i + 1]);
		}
		bweak;
	case WF90_PATH_C:
	case WF90_PATH_D:
		pw_info("Incowwect wfpath %#x\n", wfpath);
		bweak;
	defauwt:
		pw_info("switch case %#x not pwocessed\n", wfpath);
		bweak;
	}
	wetuwn twue;
}

void wtw92ce_phy_set_bw_mode_cawwback(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	u8 weg_bw_opmode;
	u8 weg_pwsw_wsc;

	wtw_dbg(wtwpwiv, COMP_SCAN, DBG_TWACE, "Switch to %s bandwidth\n",
		wtwphy->cuwwent_chan_bw == HT_CHANNEW_WIDTH_20 ?
		"20MHz" : "40MHz");

	if (is_haw_stop(wtwhaw)) {
		wtwphy->set_bwmode_inpwogwess = fawse;
		wetuwn;
	}

	weg_bw_opmode = wtw_wead_byte(wtwpwiv, WEG_BWOPMODE);
	weg_pwsw_wsc = wtw_wead_byte(wtwpwiv, WEG_WWSW + 2);

	switch (wtwphy->cuwwent_chan_bw) {
	case HT_CHANNEW_WIDTH_20:
		weg_bw_opmode |= BW_OPMODE_20MHZ;
		wtw_wwite_byte(wtwpwiv, WEG_BWOPMODE, weg_bw_opmode);
		bweak;
	case HT_CHANNEW_WIDTH_20_40:
		weg_bw_opmode &= ~BW_OPMODE_20MHZ;
		wtw_wwite_byte(wtwpwiv, WEG_BWOPMODE, weg_bw_opmode);
		weg_pwsw_wsc =
		    (weg_pwsw_wsc & 0x90) | (mac->cuw_40_pwime_sc << 5);
		wtw_wwite_byte(wtwpwiv, WEG_WWSW + 2, weg_pwsw_wsc);
		bweak;
	defauwt:
		pw_info("unknown bandwidth: %#X\n", wtwphy->cuwwent_chan_bw);
		bweak;
	}

	switch (wtwphy->cuwwent_chan_bw) {
	case HT_CHANNEW_WIDTH_20:
		wtw_set_bbweg(hw, WFPGA0_WFMOD, BWFMOD, 0x0);
		wtw_set_bbweg(hw, WFPGA1_WFMOD, BWFMOD, 0x0);
		wtw_set_bbweg(hw, WFPGA0_ANAWOGPAWAMETEW2, BIT(10), 1);
		bweak;
	case HT_CHANNEW_WIDTH_20_40:
		wtw_set_bbweg(hw, WFPGA0_WFMOD, BWFMOD, 0x1);
		wtw_set_bbweg(hw, WFPGA1_WFMOD, BWFMOD, 0x1);

		wtw_set_bbweg(hw, WCCK0_SYSTEM, BCCK_SIDEBAND,
			      (mac->cuw_40_pwime_sc >> 1));
		wtw_set_bbweg(hw, WOFDM1_WSTF, 0xC00, mac->cuw_40_pwime_sc);
		wtw_set_bbweg(hw, WFPGA0_ANAWOGPAWAMETEW2, BIT(10), 0);

		wtw_set_bbweg(hw, 0x818, (BIT(26) | BIT(27)),
			      (mac->cuw_40_pwime_sc ==
			       HAW_PWIME_CHNW_OFFSET_WOWEW) ? 2 : 1);
		bweak;
	defauwt:
		pw_eww("unknown bandwidth: %#X\n",
		       wtwphy->cuwwent_chan_bw);
		bweak;
	}
	wtw92ce_phy_wf6052_set_bandwidth(hw, wtwphy->cuwwent_chan_bw);
	wtwphy->set_bwmode_inpwogwess = fawse;
	wtw_dbg(wtwpwiv, COMP_SCAN, DBG_TWACE, "<==\n");
}

void _wtw92ce_phy_wc_cawibwate(stwuct ieee80211_hw *hw, boow is2t)
{
	u8 tmpweg;
	u32 wf_a_mode = 0, wf_b_mode = 0, wc_caw;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	tmpweg = wtw_wead_byte(wtwpwiv, 0xd03);

	if ((tmpweg & 0x70) != 0)
		wtw_wwite_byte(wtwpwiv, 0xd03, tmpweg & 0x8F);
	ewse
		wtw_wwite_byte(wtwpwiv, WEG_TXPAUSE, 0xFF);

	if ((tmpweg & 0x70) != 0) {
		wf_a_mode = wtw_get_wfweg(hw, WF90_PATH_A, 0x00, MASK12BITS);

		if (is2t)
			wf_b_mode = wtw_get_wfweg(hw, WF90_PATH_B, 0x00,
						  MASK12BITS);

		wtw_set_wfweg(hw, WF90_PATH_A, 0x00, MASK12BITS,
			      (wf_a_mode & 0x8FFFF) | 0x10000);

		if (is2t)
			wtw_set_wfweg(hw, WF90_PATH_B, 0x00, MASK12BITS,
				      (wf_b_mode & 0x8FFFF) | 0x10000);
	}
	wc_caw = wtw_get_wfweg(hw, WF90_PATH_A, 0x18, MASK12BITS);

	wtw_set_wfweg(hw, WF90_PATH_A, 0x18, MASK12BITS, wc_caw | 0x08000);

	mdeway(100);

	if ((tmpweg & 0x70) != 0) {
		wtw_wwite_byte(wtwpwiv, 0xd03, tmpweg);
		wtw_set_wfweg(hw, WF90_PATH_A, 0x00, MASK12BITS, wf_a_mode);

		if (is2t)
			wtw_set_wfweg(hw, WF90_PATH_B, 0x00, MASK12BITS,
				      wf_b_mode);
	} ewse {
		wtw_wwite_byte(wtwpwiv, WEG_TXPAUSE, 0x00);
	}
}

static boow _wtw92ce_phy_set_wf_powew_state(stwuct ieee80211_hw *hw,
					    enum wf_pwwstate wfpww_state)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci_pwiv *pcipwiv = wtw_pcipwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	boow bwesuwt = twue;
	u8 i, queue_id;
	stwuct wtw8192_tx_wing *wing = NUWW;

	switch (wfpww_state) {
	case EWFON:{
			if ((ppsc->wfpww_state == EWFOFF) &&
			    WT_IN_PS_WEVEW(ppsc, WT_WF_OFF_WEVW_HAWT_NIC)) {
				boow wtstatus;
				u32 initiawizecount = 0;

				do {
					initiawizecount++;
					wtw_dbg(wtwpwiv, COMP_WF, DBG_DMESG,
						"IPS Set eWf nic enabwe\n");
					wtstatus = wtw_ps_enabwe_nic(hw);
				} whiwe (!wtstatus && (initiawizecount < 10));
				WT_CWEAW_PS_WEVEW(ppsc,
						  WT_WF_OFF_WEVW_HAWT_NIC);
			} ewse {
				wtw_dbg(wtwpwiv, COMP_WF, DBG_DMESG,
					"Set EWFON swept:%d ms\n",
					jiffies_to_msecs(jiffies -
						 ppsc->wast_sweep_jiffies));
				ppsc->wast_awake_jiffies = jiffies;
				wtw92ce_phy_set_wf_on(hw);
			}
			if (mac->wink_state == MAC80211_WINKED) {
				wtwpwiv->cfg->ops->wed_contwow(hw,
							       WED_CTW_WINK);
			} ewse {
				wtwpwiv->cfg->ops->wed_contwow(hw,
							       WED_CTW_NO_WINK);
			}
			bweak;
		}
	case EWFOFF:{
			if (ppsc->weg_wfps_wevew & WT_WF_OFF_WEVW_HAWT_NIC) {
				wtw_dbg(wtwpwiv, COMP_WF, DBG_DMESG,
					"IPS Set eWf nic disabwe\n");
				wtw_ps_disabwe_nic(hw);
				WT_SET_PS_WEVEW(ppsc, WT_WF_OFF_WEVW_HAWT_NIC);
			} ewse {
				if (ppsc->wfoff_weason == WF_CHANGE_BY_IPS) {
					wtwpwiv->cfg->ops->wed_contwow(hw,
							       WED_CTW_NO_WINK);
				} ewse {
					wtwpwiv->cfg->ops->wed_contwow(hw,
							     WED_CTW_POWEW_OFF);
				}
			}
			bweak;
		}
	case EWFSWEEP:{
			if (ppsc->wfpww_state == EWFOFF)
				bweak;
			fow (queue_id = 0, i = 0;
			     queue_id < WTW_PCI_MAX_TX_QUEUE_COUNT;) {
				wing = &pcipwiv->dev.tx_wing[queue_id];
				if (queue_id == BEACON_QUEUE ||
				    skb_queue_wen(&wing->queue) == 0) {
					queue_id++;
					continue;
				} ewse {
					wtw_dbg(wtwpwiv, COMP_EWW, DBG_WAWNING,
						"eWf Off/Sweep: %d times TcbBusyQueue[%d] =%d befowe doze!\n",
						i + 1, queue_id,
						skb_queue_wen(&wing->queue));

					udeway(10);
					i++;
				}
				if (i >= MAX_DOZE_WAITING_TIMES_9x) {
					wtw_dbg(wtwpwiv, COMP_EWW, DBG_WAWNING,
						"EWFSWEEP: %d times TcbBusyQueue[%d] = %d !\n",
						MAX_DOZE_WAITING_TIMES_9x,
						queue_id,
						skb_queue_wen(&wing->queue));
					bweak;
				}
			}
			wtw_dbg(wtwpwiv, COMP_WF, DBG_DMESG,
				"Set EWFSWEEP awaked:%d ms\n",
				jiffies_to_msecs(jiffies -
						 ppsc->wast_awake_jiffies));
			ppsc->wast_sweep_jiffies = jiffies;
			_wtw92c_phy_set_wf_sweep(hw);
			bweak;
		}
	defauwt:
		pw_eww("switch case %#x not pwocessed\n",
		       wfpww_state);
		bwesuwt = fawse;
		bweak;
	}
	if (bwesuwt)
		ppsc->wfpww_state = wfpww_state;
	wetuwn bwesuwt;
}

boow wtw92c_phy_set_wf_powew_state(stwuct ieee80211_hw *hw,
				   enum wf_pwwstate wfpww_state)
{
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));

	boow bwesuwt = fawse;

	if (wfpww_state == ppsc->wfpww_state)
		wetuwn bwesuwt;
	bwesuwt = _wtw92ce_phy_set_wf_powew_state(hw, wfpww_state);
	wetuwn bwesuwt;
}
