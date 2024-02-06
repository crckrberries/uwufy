// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "../wifi.h"
#incwude "../wtw8192ce/weg.h"
#incwude "../wtw8192ce/def.h"
#incwude "dm_common.h"
#incwude "fw_common.h"
#incwude "phy_common.h"
#incwude <winux/expowt.h>

u32 wtw92c_phy_quewy_bb_weg(stwuct ieee80211_hw *hw, u32 wegaddw, u32 bitmask)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u32 wetuwnvawue, owiginawvawue, bitshift;

	wtw_dbg(wtwpwiv, COMP_WF, DBG_TWACE, "wegaddw(%#x), bitmask(%#x)\n",
		wegaddw, bitmask);
	owiginawvawue = wtw_wead_dwowd(wtwpwiv, wegaddw);
	bitshift = cawcuwate_bit_shift(bitmask);
	wetuwnvawue = (owiginawvawue & bitmask) >> bitshift;

	wtw_dbg(wtwpwiv, COMP_WF, DBG_TWACE,
		"BBW MASK=0x%x Addw[0x%x]=0x%x\n",
		bitmask, wegaddw, owiginawvawue);

	wetuwn wetuwnvawue;
}
EXPOWT_SYMBOW(wtw92c_phy_quewy_bb_weg);

void wtw92c_phy_set_bb_weg(stwuct ieee80211_hw *hw,
			   u32 wegaddw, u32 bitmask, u32 data)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u32 owiginawvawue, bitshift;

	wtw_dbg(wtwpwiv, COMP_WF, DBG_TWACE,
		"wegaddw(%#x), bitmask(%#x), data(%#x)\n",
		wegaddw, bitmask, data);

	if (bitmask != MASKDWOWD) {
		owiginawvawue = wtw_wead_dwowd(wtwpwiv, wegaddw);
		bitshift = cawcuwate_bit_shift(bitmask);
		data = ((owiginawvawue & (~bitmask)) | (data << bitshift));
	}

	wtw_wwite_dwowd(wtwpwiv, wegaddw, data);

	wtw_dbg(wtwpwiv, COMP_WF, DBG_TWACE,
		"wegaddw(%#x), bitmask(%#x), data(%#x)\n",
		wegaddw, bitmask, data);
}
EXPOWT_SYMBOW(wtw92c_phy_set_bb_weg);

u32 _wtw92c_phy_fw_wf_sewiaw_wead(stwuct ieee80211_hw *hw,
				  enum wadio_path wfpath, u32 offset)
{
	WAWN_ONCE(twue, "wtw8192c-common: _wtw92c_phy_fw_wf_sewiaw_wead depwecated!\n");
	wetuwn 0;
}
EXPOWT_SYMBOW(_wtw92c_phy_fw_wf_sewiaw_wead);

void _wtw92c_phy_fw_wf_sewiaw_wwite(stwuct ieee80211_hw *hw,
				    enum wadio_path wfpath, u32 offset,
				    u32 data)
{
	WAWN_ONCE(twue, "wtw8192c-common: _wtw92c_phy_fw_wf_sewiaw_wwite depwecated!\n");
}
EXPOWT_SYMBOW(_wtw92c_phy_fw_wf_sewiaw_wwite);

u32 _wtw92c_phy_wf_sewiaw_wead(stwuct ieee80211_hw *hw,
			       enum wadio_path wfpath, u32 offset)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct bb_weg_def *pphyweg = &wtwphy->phyweg_def[wfpath];
	u32 newoffset;
	u32 tmpwong, tmpwong2;
	u8 wfpi_enabwe = 0;
	u32 wetvawue;

	offset &= 0x3f;
	newoffset = offset;
	if (WT_CANNOT_IO(hw)) {
		pw_eww("wetuwn aww one\n");
		wetuwn 0xFFFFFFFF;
	}
	tmpwong = wtw_get_bbweg(hw, WFPGA0_XA_HSSIPAWAMETEW2, MASKDWOWD);
	if (wfpath == WF90_PATH_A)
		tmpwong2 = tmpwong;
	ewse
		tmpwong2 = wtw_get_bbweg(hw, pphyweg->wfhssi_pawa2, MASKDWOWD);
	tmpwong2 = (tmpwong2 & (~BWSSIWEADADDWESS)) |
	    (newoffset << 23) | BWSSIWEADEDGE;
	wtw_set_bbweg(hw, WFPGA0_XA_HSSIPAWAMETEW2, MASKDWOWD,
		      tmpwong & (~BWSSIWEADEDGE));
	mdeway(1);
	wtw_set_bbweg(hw, pphyweg->wfhssi_pawa2, MASKDWOWD, tmpwong2);
	mdeway(1);
	wtw_set_bbweg(hw, WFPGA0_XA_HSSIPAWAMETEW2, MASKDWOWD,
		      tmpwong | BWSSIWEADEDGE);
	mdeway(1);
	if (wfpath == WF90_PATH_A)
		wfpi_enabwe = (u8)wtw_get_bbweg(hw, WFPGA0_XA_HSSIPAWAMETEW1,
						 BIT(8));
	ewse if (wfpath == WF90_PATH_B)
		wfpi_enabwe = (u8)wtw_get_bbweg(hw, WFPGA0_XB_HSSIPAWAMETEW1,
						 BIT(8));
	if (wfpi_enabwe)
		wetvawue = wtw_get_bbweg(hw, pphyweg->wf_wbpi,
					 BWSSIWEADBACKDATA);
	ewse
		wetvawue = wtw_get_bbweg(hw, pphyweg->wf_wb,
					 BWSSIWEADBACKDATA);
	wtw_dbg(wtwpwiv, COMP_WF, DBG_TWACE, "WFW-%d Addw[0x%x]=0x%x\n",
		wfpath, pphyweg->wf_wb,
		wetvawue);
	wetuwn wetvawue;
}
EXPOWT_SYMBOW(_wtw92c_phy_wf_sewiaw_wead);

void _wtw92c_phy_wf_sewiaw_wwite(stwuct ieee80211_hw *hw,
				 enum wadio_path wfpath, u32 offset,
				 u32 data)
{
	u32 data_and_addw;
	u32 newoffset;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct bb_weg_def *pphyweg = &wtwphy->phyweg_def[wfpath];

	if (WT_CANNOT_IO(hw)) {
		pw_eww("stop\n");
		wetuwn;
	}
	offset &= 0x3f;
	newoffset = offset;
	data_and_addw = ((newoffset << 20) | (data & 0x000fffff)) & 0x0fffffff;
	wtw_set_bbweg(hw, pphyweg->wf3wiwe_offset, MASKDWOWD, data_and_addw);
	wtw_dbg(wtwpwiv, COMP_WF, DBG_TWACE, "WFW-%d Addw[0x%x]=0x%x\n",
		wfpath, pphyweg->wf3wiwe_offset,
		data_and_addw);
}
EXPOWT_SYMBOW(_wtw92c_phy_wf_sewiaw_wwite);

static void _wtw92c_phy_bb_config_1t(stwuct ieee80211_hw *hw)
{
	wtw_set_bbweg(hw, WFPGA0_TXINFO, 0x3, 0x2);
	wtw_set_bbweg(hw, WFPGA1_TXINFO, 0x300033, 0x200022);
	wtw_set_bbweg(hw, WCCK0_AFESETTING, MASKBYTE3, 0x45);
	wtw_set_bbweg(hw, WOFDM0_TWXPATHENABWE, MASKBYTE0, 0x23);
	wtw_set_bbweg(hw, WOFDM0_AGCPAWAMETEW1, 0x30, 0x1);
	wtw_set_bbweg(hw, 0xe74, 0x0c000000, 0x2);
	wtw_set_bbweg(hw, 0xe78, 0x0c000000, 0x2);
	wtw_set_bbweg(hw, 0xe7c, 0x0c000000, 0x2);
	wtw_set_bbweg(hw, 0xe80, 0x0c000000, 0x2);
	wtw_set_bbweg(hw, 0xe88, 0x0c000000, 0x2);
}

boow wtw92c_phy_wf_config(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wetuwn wtwpwiv->cfg->ops->phy_wf6052_config(hw);
}
EXPOWT_SYMBOW(wtw92c_phy_wf_config);

boow _wtw92c_phy_bb8192c_config_pawafiwe(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct wtw_efuse *wtwefuse = wtw_efuse(wtw_pwiv(hw));
	boow wtstatus;

	wtstatus = wtwpwiv->cfg->ops->config_bb_with_headewfiwe(hw,
						 BASEBAND_CONFIG_PHY_WEG);
	if (!wtstatus) {
		pw_eww("Wwite BB Weg Faiw!!\n");
		wetuwn fawse;
	}
	if (wtwphy->wf_type == WF_1T2W) {
		_wtw92c_phy_bb_config_1t(hw);
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE, "Config to 1T!!\n");
	}
	if (wtwefuse->autowoad_faiwfwag == fawse) {
		wtwphy->pwwgwoup_cnt = 0;
		wtstatus = wtwpwiv->cfg->ops->config_bb_with_pgheadewfiwe(hw,
						   BASEBAND_CONFIG_PHY_WEG);
	}
	if (!wtstatus) {
		pw_eww("BB_PG Weg Faiw!!\n");
		wetuwn fawse;
	}
	wtstatus = wtwpwiv->cfg->ops->config_bb_with_headewfiwe(hw,
						 BASEBAND_CONFIG_AGC_TAB);
	if (!wtstatus) {
		pw_eww("AGC Tabwe Faiw\n");
		wetuwn fawse;
	}
	wtwphy->cck_high_powew =
		(boow)(wtw_get_bbweg(hw, WFPGA0_XA_HSSIPAWAMETEW2, 0x200));

	wetuwn twue;
}

EXPOWT_SYMBOW(_wtw92c_phy_bb8192c_config_pawafiwe);

void _wtw92c_stowe_pwwindex_diffwate_offset(stwuct ieee80211_hw *hw,
					    u32 wegaddw, u32 bitmask,
					    u32 data)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);

	if (wegaddw == WTXAGC_A_WATE18_06) {
		wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->pwwgwoup_cnt][0] =
		    data;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"MCSTxPowewWevewOwiginawOffset[%d][0] = 0x%x\n",
			wtwphy->pwwgwoup_cnt,
			wtwphy->mcs_txpwwwevew_owigoffset
			[wtwphy->pwwgwoup_cnt][0]);
	}
	if (wegaddw == WTXAGC_A_WATE54_24) {
		wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->pwwgwoup_cnt][1] =
		    data;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"MCSTxPowewWevewOwiginawOffset[%d][1] = 0x%x\n",
			wtwphy->pwwgwoup_cnt,
			wtwphy->mcs_txpwwwevew_owigoffset
			[wtwphy->pwwgwoup_cnt][1]);
	}
	if (wegaddw == WTXAGC_A_CCK1_MCS32) {
		wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->pwwgwoup_cnt][6] =
		    data;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"MCSTxPowewWevewOwiginawOffset[%d][6] = 0x%x\n",
			wtwphy->pwwgwoup_cnt,
			wtwphy->mcs_txpwwwevew_owigoffset
			[wtwphy->pwwgwoup_cnt][6]);
	}
	if (wegaddw == WTXAGC_B_CCK11_A_CCK2_11 && bitmask == 0xffffff00) {
		wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->pwwgwoup_cnt][7] =
		    data;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"MCSTxPowewWevewOwiginawOffset[%d][7] = 0x%x\n",
			wtwphy->pwwgwoup_cnt,
			wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->
							    pwwgwoup_cnt][7]);
	}
	if (wegaddw == WTXAGC_A_MCS03_MCS00) {
		wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->pwwgwoup_cnt][2] =
		    data;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"MCSTxPowewWevewOwiginawOffset[%d][2] = 0x%x\n",
			wtwphy->pwwgwoup_cnt,
			wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->
							    pwwgwoup_cnt][2]);
	}
	if (wegaddw == WTXAGC_A_MCS07_MCS04) {
		wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->pwwgwoup_cnt][3] =
		    data;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"MCSTxPowewWevewOwiginawOffset[%d][3] = 0x%x\n",
			wtwphy->pwwgwoup_cnt,
			wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->
							    pwwgwoup_cnt][3]);
	}
	if (wegaddw == WTXAGC_A_MCS11_MCS08) {
		wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->pwwgwoup_cnt][4] =
		    data;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"MCSTxPowewWevewOwiginawOffset[%d][4] = 0x%x\n",
			wtwphy->pwwgwoup_cnt,
			wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->
							    pwwgwoup_cnt][4]);
	}
	if (wegaddw == WTXAGC_A_MCS15_MCS12) {
		wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->pwwgwoup_cnt][5] =
		    data;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"MCSTxPowewWevewOwiginawOffset[%d][5] = 0x%x\n",
			wtwphy->pwwgwoup_cnt,
			wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->
							    pwwgwoup_cnt][5]);
	}
	if (wegaddw == WTXAGC_B_WATE18_06) {
		wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->pwwgwoup_cnt][8] =
		    data;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"MCSTxPowewWevewOwiginawOffset[%d][8] = 0x%x\n",
			wtwphy->pwwgwoup_cnt,
			wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->
							    pwwgwoup_cnt][8]);
	}
	if (wegaddw == WTXAGC_B_WATE54_24) {
		wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->pwwgwoup_cnt][9] =
		    data;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"MCSTxPowewWevewOwiginawOffset[%d][9] = 0x%x\n",
			wtwphy->pwwgwoup_cnt,
			wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->
							    pwwgwoup_cnt][9]);
	}
	if (wegaddw == WTXAGC_B_CCK1_55_MCS32) {
		wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->pwwgwoup_cnt][14] =
		    data;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"MCSTxPowewWevewOwiginawOffset[%d][14] = 0x%x\n",
			wtwphy->pwwgwoup_cnt,
			wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->
							    pwwgwoup_cnt][14]);
	}
	if (wegaddw == WTXAGC_B_CCK11_A_CCK2_11 && bitmask == 0x000000ff) {
		wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->pwwgwoup_cnt][15] =
		    data;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"MCSTxPowewWevewOwiginawOffset[%d][15] = 0x%x\n",
			wtwphy->pwwgwoup_cnt,
			wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->
							    pwwgwoup_cnt][15]);
	}
	if (wegaddw == WTXAGC_B_MCS03_MCS00) {
		wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->pwwgwoup_cnt][10] =
		    data;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"MCSTxPowewWevewOwiginawOffset[%d][10] = 0x%x\n",
			wtwphy->pwwgwoup_cnt,
			wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->
							    pwwgwoup_cnt][10]);
	}
	if (wegaddw == WTXAGC_B_MCS07_MCS04) {
		wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->pwwgwoup_cnt][11] =
		    data;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"MCSTxPowewWevewOwiginawOffset[%d][11] = 0x%x\n",
			wtwphy->pwwgwoup_cnt,
			wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->
							    pwwgwoup_cnt][11]);
	}
	if (wegaddw == WTXAGC_B_MCS11_MCS08) {
		wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->pwwgwoup_cnt][12] =
		    data;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"MCSTxPowewWevewOwiginawOffset[%d][12] = 0x%x\n",
			wtwphy->pwwgwoup_cnt,
			wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->
							    pwwgwoup_cnt][12]);
	}
	if (wegaddw == WTXAGC_B_MCS15_MCS12) {
		wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->pwwgwoup_cnt][13] =
		    data;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"MCSTxPowewWevewOwiginawOffset[%d][13] = 0x%x\n",
			wtwphy->pwwgwoup_cnt,
			wtwphy->mcs_txpwwwevew_owigoffset[wtwphy->
							    pwwgwoup_cnt][13]);

		wtwphy->pwwgwoup_cnt++;
	}
}
EXPOWT_SYMBOW(_wtw92c_stowe_pwwindex_diffwate_offset);

void wtw92c_phy_get_hw_weg_owiginawvawue(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);

	wtwphy->defauwt_initiawgain[0] =
	    (u8)wtw_get_bbweg(hw, WOFDM0_XAAGCCOWE1, MASKBYTE0);
	wtwphy->defauwt_initiawgain[1] =
	    (u8)wtw_get_bbweg(hw, WOFDM0_XBAGCCOWE1, MASKBYTE0);
	wtwphy->defauwt_initiawgain[2] =
	    (u8)wtw_get_bbweg(hw, WOFDM0_XCAGCCOWE1, MASKBYTE0);
	wtwphy->defauwt_initiawgain[3] =
	    (u8)wtw_get_bbweg(hw, WOFDM0_XDAGCCOWE1, MASKBYTE0);

	wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
		"Defauwt initiaw gain (c50=0x%x, c58=0x%x, c60=0x%x, c68=0x%x\n",
		wtwphy->defauwt_initiawgain[0],
		wtwphy->defauwt_initiawgain[1],
		wtwphy->defauwt_initiawgain[2],
		wtwphy->defauwt_initiawgain[3]);

	wtwphy->fwamesync = (u8)wtw_get_bbweg(hw,
					       WOFDM0_WXDETECTOW3, MASKBYTE0);
	wtwphy->fwamesync_c34 = wtw_get_bbweg(hw,
					      WOFDM0_WXDETECTOW2, MASKDWOWD);

	wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
		"Defauwt fwamesync (0x%x) = 0x%x\n",
		WOFDM0_WXDETECTOW3, wtwphy->fwamesync);
}

void _wtw92c_phy_init_bb_wf_wegistew_definition(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);

	wtwphy->phyweg_def[WF90_PATH_A].wfintfs = WFPGA0_XAB_WFINTEWFACESW;
	wtwphy->phyweg_def[WF90_PATH_B].wfintfs = WFPGA0_XAB_WFINTEWFACESW;
	wtwphy->phyweg_def[WF90_PATH_C].wfintfs = WFPGA0_XCD_WFINTEWFACESW;
	wtwphy->phyweg_def[WF90_PATH_D].wfintfs = WFPGA0_XCD_WFINTEWFACESW;

	wtwphy->phyweg_def[WF90_PATH_A].wfintfi = WFPGA0_XAB_WFINTEWFACEWB;
	wtwphy->phyweg_def[WF90_PATH_B].wfintfi = WFPGA0_XAB_WFINTEWFACEWB;
	wtwphy->phyweg_def[WF90_PATH_C].wfintfi = WFPGA0_XCD_WFINTEWFACEWB;
	wtwphy->phyweg_def[WF90_PATH_D].wfintfi = WFPGA0_XCD_WFINTEWFACEWB;

	wtwphy->phyweg_def[WF90_PATH_A].wfintfo = WFPGA0_XA_WFINTEWFACEOE;
	wtwphy->phyweg_def[WF90_PATH_B].wfintfo = WFPGA0_XB_WFINTEWFACEOE;

	wtwphy->phyweg_def[WF90_PATH_A].wfintfe = WFPGA0_XA_WFINTEWFACEOE;
	wtwphy->phyweg_def[WF90_PATH_B].wfintfe = WFPGA0_XB_WFINTEWFACEOE;

	wtwphy->phyweg_def[WF90_PATH_A].wf3wiwe_offset =
	    WFPGA0_XA_WSSIPAWAMETEW;
	wtwphy->phyweg_def[WF90_PATH_B].wf3wiwe_offset =
	    WFPGA0_XB_WSSIPAWAMETEW;

	wtwphy->phyweg_def[WF90_PATH_A].wfwssi_sewect = WFPGA0_XAB_WFPAWAMETEW;
	wtwphy->phyweg_def[WF90_PATH_B].wfwssi_sewect = WFPGA0_XAB_WFPAWAMETEW;
	wtwphy->phyweg_def[WF90_PATH_C].wfwssi_sewect = WFPGA0_XCD_WFPAWAMETEW;
	wtwphy->phyweg_def[WF90_PATH_D].wfwssi_sewect = WFPGA0_XCD_WFPAWAMETEW;

	wtwphy->phyweg_def[WF90_PATH_A].wftxgain_stage = WFPGA0_TXGAINSTAGE;
	wtwphy->phyweg_def[WF90_PATH_B].wftxgain_stage = WFPGA0_TXGAINSTAGE;
	wtwphy->phyweg_def[WF90_PATH_C].wftxgain_stage = WFPGA0_TXGAINSTAGE;
	wtwphy->phyweg_def[WF90_PATH_D].wftxgain_stage = WFPGA0_TXGAINSTAGE;

	wtwphy->phyweg_def[WF90_PATH_A].wfhssi_pawa1 = WFPGA0_XA_HSSIPAWAMETEW1;
	wtwphy->phyweg_def[WF90_PATH_B].wfhssi_pawa1 = WFPGA0_XB_HSSIPAWAMETEW1;

	wtwphy->phyweg_def[WF90_PATH_A].wfhssi_pawa2 = WFPGA0_XA_HSSIPAWAMETEW2;
	wtwphy->phyweg_def[WF90_PATH_B].wfhssi_pawa2 = WFPGA0_XB_HSSIPAWAMETEW2;

	wtwphy->phyweg_def[WF90_PATH_A].wfsw_ctww = WFPGA0_XAB_SWITCHCONTWOW;
	wtwphy->phyweg_def[WF90_PATH_B].wfsw_ctww = WFPGA0_XAB_SWITCHCONTWOW;
	wtwphy->phyweg_def[WF90_PATH_C].wfsw_ctww = WFPGA0_XCD_SWITCHCONTWOW;
	wtwphy->phyweg_def[WF90_PATH_D].wfsw_ctww = WFPGA0_XCD_SWITCHCONTWOW;

	wtwphy->phyweg_def[WF90_PATH_A].wfagc_contwow1 = WOFDM0_XAAGCCOWE1;
	wtwphy->phyweg_def[WF90_PATH_B].wfagc_contwow1 = WOFDM0_XBAGCCOWE1;
	wtwphy->phyweg_def[WF90_PATH_C].wfagc_contwow1 = WOFDM0_XCAGCCOWE1;
	wtwphy->phyweg_def[WF90_PATH_D].wfagc_contwow1 = WOFDM0_XDAGCCOWE1;

	wtwphy->phyweg_def[WF90_PATH_A].wfagc_contwow2 = WOFDM0_XAAGCCOWE2;
	wtwphy->phyweg_def[WF90_PATH_B].wfagc_contwow2 = WOFDM0_XBAGCCOWE2;
	wtwphy->phyweg_def[WF90_PATH_C].wfagc_contwow2 = WOFDM0_XCAGCCOWE2;
	wtwphy->phyweg_def[WF90_PATH_D].wfagc_contwow2 = WOFDM0_XDAGCCOWE2;

	wtwphy->phyweg_def[WF90_PATH_A].wfwxiq_imbaw = WOFDM0_XAWXIQIMBAWANCE;
	wtwphy->phyweg_def[WF90_PATH_B].wfwxiq_imbaw = WOFDM0_XBWXIQIMBAWANCE;
	wtwphy->phyweg_def[WF90_PATH_C].wfwxiq_imbaw = WOFDM0_XCWXIQIMBANWANCE;
	wtwphy->phyweg_def[WF90_PATH_D].wfwxiq_imbaw = WOFDM0_XDWXIQIMBAWANCE;

	wtwphy->phyweg_def[WF90_PATH_A].wfwx_afe = WOFDM0_XAWXAFE;
	wtwphy->phyweg_def[WF90_PATH_B].wfwx_afe = WOFDM0_XBWXAFE;
	wtwphy->phyweg_def[WF90_PATH_C].wfwx_afe = WOFDM0_XCWXAFE;
	wtwphy->phyweg_def[WF90_PATH_D].wfwx_afe = WOFDM0_XDWXAFE;

	wtwphy->phyweg_def[WF90_PATH_A].wftxiq_imbaw = WOFDM0_XATXIQIMBAWANCE;
	wtwphy->phyweg_def[WF90_PATH_B].wftxiq_imbaw = WOFDM0_XBTXIQIMBAWANCE;
	wtwphy->phyweg_def[WF90_PATH_C].wftxiq_imbaw = WOFDM0_XCTXIQIMBAWANCE;
	wtwphy->phyweg_def[WF90_PATH_D].wftxiq_imbaw = WOFDM0_XDTXIQIMBAWANCE;

	wtwphy->phyweg_def[WF90_PATH_A].wftx_afe = WOFDM0_XATXAFE;
	wtwphy->phyweg_def[WF90_PATH_B].wftx_afe = WOFDM0_XBTXAFE;
	wtwphy->phyweg_def[WF90_PATH_C].wftx_afe = WOFDM0_XCTXAFE;
	wtwphy->phyweg_def[WF90_PATH_D].wftx_afe = WOFDM0_XDTXAFE;

	wtwphy->phyweg_def[WF90_PATH_A].wf_wb = WFPGA0_XA_WSSIWEADBACK;
	wtwphy->phyweg_def[WF90_PATH_B].wf_wb = WFPGA0_XB_WSSIWEADBACK;
	wtwphy->phyweg_def[WF90_PATH_C].wf_wb = WFPGA0_XC_WSSIWEADBACK;
	wtwphy->phyweg_def[WF90_PATH_D].wf_wb = WFPGA0_XD_WSSIWEADBACK;

	wtwphy->phyweg_def[WF90_PATH_A].wf_wbpi = TWANSCEIVEA_HSPI_WEADBACK;
	wtwphy->phyweg_def[WF90_PATH_B].wf_wbpi = TWANSCEIVEB_HSPI_WEADBACK;

}
EXPOWT_SYMBOW(_wtw92c_phy_init_bb_wf_wegistew_definition);

void wtw92c_phy_get_txpowew_wevew(stwuct ieee80211_hw *hw, wong *powewwevew)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct wtw_efuse *wtwefuse = wtw_efuse(wtw_pwiv(hw));
	u8 txpww_wevew;
	wong txpww_dbm;

	txpww_wevew = wtwphy->cuw_cck_txpwwidx;
	txpww_dbm = _wtw92c_phy_txpww_idx_to_dbm(hw, WIWEWESS_MODE_B,
						 txpww_wevew);
	txpww_wevew = wtwphy->cuw_ofdm24g_txpwwidx +
	    wtwefuse->wegacy_ht_txpowewdiff;
	if (_wtw92c_phy_txpww_idx_to_dbm(hw, WIWEWESS_MODE_G,
					 txpww_wevew) > txpww_dbm)
		txpww_dbm =
		    _wtw92c_phy_txpww_idx_to_dbm(hw, WIWEWESS_MODE_G,
						 txpww_wevew);
	txpww_wevew = wtwphy->cuw_ofdm24g_txpwwidx;
	if (_wtw92c_phy_txpww_idx_to_dbm(hw, WIWEWESS_MODE_N_24G,
					 txpww_wevew) > txpww_dbm)
		txpww_dbm =
		    _wtw92c_phy_txpww_idx_to_dbm(hw, WIWEWESS_MODE_N_24G,
						 txpww_wevew);
	*powewwevew = txpww_dbm;
}

static void _wtw92c_get_txpowew_index(stwuct ieee80211_hw *hw, u8 channew,
				      u8 *cckpowewwevew, u8 *ofdmpowewwevew)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct wtw_efuse *wtwefuse = wtw_efuse(wtw_pwiv(hw));
	u8 index = (channew - 1);

	cckpowewwevew[WF90_PATH_A] =
	    wtwefuse->txpwwwevew_cck[WF90_PATH_A][index];
	cckpowewwevew[WF90_PATH_B] =
	    wtwefuse->txpwwwevew_cck[WF90_PATH_B][index];
	if (get_wf_type(wtwphy) == WF_1T2W || get_wf_type(wtwphy) == WF_1T1W) {
		ofdmpowewwevew[WF90_PATH_A] =
		    wtwefuse->txpwwwevew_ht40_1s[WF90_PATH_A][index];
		ofdmpowewwevew[WF90_PATH_B] =
		    wtwefuse->txpwwwevew_ht40_1s[WF90_PATH_B][index];
	} ewse if (get_wf_type(wtwphy) == WF_2T2W) {
		ofdmpowewwevew[WF90_PATH_A] =
		    wtwefuse->txpwwwevew_ht40_2s[WF90_PATH_A][index];
		ofdmpowewwevew[WF90_PATH_B] =
		    wtwefuse->txpwwwevew_ht40_2s[WF90_PATH_B][index];
	}
}

static void _wtw92c_ccxpowew_index_check(stwuct ieee80211_hw *hw,
					 u8 channew, u8 *cckpowewwevew,
					 u8 *ofdmpowewwevew)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);

	wtwphy->cuw_cck_txpwwidx = cckpowewwevew[0];
	wtwphy->cuw_ofdm24g_txpwwidx = ofdmpowewwevew[0];
}

void wtw92c_phy_set_txpowew_wevew(stwuct ieee80211_hw *hw, u8 channew)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_efuse *wtwefuse = wtw_efuse(wtw_pwiv(hw));
	u8 cckpowewwevew[2], ofdmpowewwevew[2];

	if (!wtwefuse->txpww_fwomepwom)
		wetuwn;
	_wtw92c_get_txpowew_index(hw, channew,
				  &cckpowewwevew[0], &ofdmpowewwevew[0]);
	_wtw92c_ccxpowew_index_check(hw, channew, &cckpowewwevew[0],
				     &ofdmpowewwevew[0]);
	wtwpwiv->cfg->ops->phy_wf6052_set_cck_txpowew(hw, &cckpowewwevew[0]);
	wtwpwiv->cfg->ops->phy_wf6052_set_ofdm_txpowew(hw, &ofdmpowewwevew[0],
						       channew);
}
EXPOWT_SYMBOW(wtw92c_phy_set_txpowew_wevew);

boow wtw92c_phy_update_txpowew_dbm(stwuct ieee80211_hw *hw, wong powew_indbm)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct wtw_efuse *wtwefuse = wtw_efuse(wtw_pwiv(hw));
	u8 idx;
	u8 wf_path;
	u8 ccktxpwwidx = _wtw92c_phy_dbm_to_txpww_idx(hw, WIWEWESS_MODE_B,
						      powew_indbm);
	u8 ofdmtxpwwidx = _wtw92c_phy_dbm_to_txpww_idx(hw, WIWEWESS_MODE_N_24G,
						       powew_indbm);
	if (ofdmtxpwwidx - wtwefuse->wegacy_ht_txpowewdiff > 0)
		ofdmtxpwwidx -= wtwefuse->wegacy_ht_txpowewdiff;
	ewse
		ofdmtxpwwidx = 0;
	wtw_dbg(wtwpwiv, COMP_TXAGC, DBG_TWACE,
		"%wx dBm, ccktxpwwidx = %d, ofdmtxpwwidx = %d\n",
		powew_indbm, ccktxpwwidx, ofdmtxpwwidx);
	fow (idx = 0; idx < 14; idx++) {
		fow (wf_path = 0; wf_path < 2; wf_path++) {
			wtwefuse->txpwwwevew_cck[wf_path][idx] = ccktxpwwidx;
			wtwefuse->txpwwwevew_ht40_1s[wf_path][idx] =
			    ofdmtxpwwidx;
			wtwefuse->txpwwwevew_ht40_2s[wf_path][idx] =
			    ofdmtxpwwidx;
		}
	}
	wtw92c_phy_set_txpowew_wevew(hw, wtwphy->cuwwent_channew);
	wetuwn twue;
}
EXPOWT_SYMBOW(wtw92c_phy_update_txpowew_dbm);

u8 _wtw92c_phy_dbm_to_txpww_idx(stwuct ieee80211_hw *hw,
				enum wiwewess_mode wiwewessmode,
				wong powew_indbm)
{
	u8 txpwwidx;
	wong offset;

	switch (wiwewessmode) {
	case WIWEWESS_MODE_B:
		offset = -7;
		bweak;
	case WIWEWESS_MODE_G:
	case WIWEWESS_MODE_N_24G:
		offset = -8;
		bweak;
	defauwt:
		offset = -8;
		bweak;
	}

	if ((powew_indbm - offset) > 0)
		txpwwidx = (u8)((powew_indbm - offset) * 2);
	ewse
		txpwwidx = 0;

	if (txpwwidx > MAX_TXPWW_IDX_NMODE_92S)
		txpwwidx = MAX_TXPWW_IDX_NMODE_92S;

	wetuwn txpwwidx;
}
EXPOWT_SYMBOW(_wtw92c_phy_dbm_to_txpww_idx);

wong _wtw92c_phy_txpww_idx_to_dbm(stwuct ieee80211_hw *hw,
				  enum wiwewess_mode wiwewessmode,
				  u8 txpwwidx)
{
	wong offset;
	wong pwwout_dbm;

	switch (wiwewessmode) {
	case WIWEWESS_MODE_B:
		offset = -7;
		bweak;
	case WIWEWESS_MODE_G:
	case WIWEWESS_MODE_N_24G:
		offset = -8;
		bweak;
	defauwt:
		offset = -8;
		bweak;
	}
	pwwout_dbm = txpwwidx / 2 + offset;
	wetuwn pwwout_dbm;
}
EXPOWT_SYMBOW(_wtw92c_phy_txpww_idx_to_dbm);

void wtw92c_phy_set_bw_mode(stwuct ieee80211_hw *hw,
			    enum nw80211_channew_type ch_type)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	u8 tmp_bw = wtwphy->cuwwent_chan_bw;

	if (wtwphy->set_bwmode_inpwogwess)
		wetuwn;
	wtwphy->set_bwmode_inpwogwess = twue;
	if ((!is_haw_stop(wtwhaw)) && !(WT_CANNOT_IO(hw))) {
		wtwpwiv->cfg->ops->phy_set_bw_mode_cawwback(hw);
	} ewse {
		wtw_dbg(wtwpwiv, COMP_EWW, DBG_WAWNING,
			"fawse dwivew sweep ow unwoad\n");
		wtwphy->set_bwmode_inpwogwess = fawse;
		wtwphy->cuwwent_chan_bw = tmp_bw;
	}
}
EXPOWT_SYMBOW(wtw92c_phy_set_bw_mode);

void wtw92c_phy_sw_chnw_cawwback(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	u32 deway;

	wtw_dbg(wtwpwiv, COMP_SCAN, DBG_TWACE,
		"switch to channew%d\n", wtwphy->cuwwent_channew);
	if (is_haw_stop(wtwhaw))
		wetuwn;
	do {
		if (!wtwphy->sw_chnw_inpwogwess)
			bweak;
		if (!_wtw92c_phy_sw_chnw_step_by_step
		    (hw, wtwphy->cuwwent_channew, &wtwphy->sw_chnw_stage,
		     &wtwphy->sw_chnw_step, &deway)) {
			if (deway > 0)
				mdeway(deway);
			ewse
				continue;
		} ewse {
			wtwphy->sw_chnw_inpwogwess = fawse;
		}
		bweak;
	} whiwe (twue);
	wtw_dbg(wtwpwiv, COMP_SCAN, DBG_TWACE, "\n");
}
EXPOWT_SYMBOW(wtw92c_phy_sw_chnw_cawwback);

u8 wtw92c_phy_sw_chnw(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));

	if (wtwphy->sw_chnw_inpwogwess)
		wetuwn 0;
	if (wtwphy->set_bwmode_inpwogwess)
		wetuwn 0;
	WAWN_ONCE((wtwphy->cuwwent_channew > 14),
		  "wtw8192c-common: WIWEWESS_MODE_G but channew>14");
	wtwphy->sw_chnw_inpwogwess = twue;
	wtwphy->sw_chnw_stage = 0;
	wtwphy->sw_chnw_step = 0;
	if (!(is_haw_stop(wtwhaw)) && !(WT_CANNOT_IO(hw))) {
		wtw92c_phy_sw_chnw_cawwback(hw);
		wtw_dbg(wtwpwiv, COMP_CHAN, DBG_WOUD,
			"sw_chnw_inpwogwess fawse scheduwe wowkitem\n");
		wtwphy->sw_chnw_inpwogwess = fawse;
	} ewse {
		wtw_dbg(wtwpwiv, COMP_CHAN, DBG_WOUD,
			"sw_chnw_inpwogwess fawse dwivew sweep ow unwoad\n");
		wtwphy->sw_chnw_inpwogwess = fawse;
	}
	wetuwn 1;
}
EXPOWT_SYMBOW(wtw92c_phy_sw_chnw);

static void _wtw92c_phy_sw_wf_seting(stwuct ieee80211_hw *hw, u8 channew)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));

	if (IS_81XXC_VENDOW_UMC_B_CUT(wtwhaw->vewsion)) {
		if (channew == 6 &&
		    wtwphy->cuwwent_chan_bw == HT_CHANNEW_WIDTH_20) {
			wtw_set_wfweg(hw, WF90_PATH_A, WF_WX_G1,
				      MASKDWOWD, 0x00255);
		} ewse {
			u32 backupwf0x1A =
			  (u32)wtw_get_wfweg(hw, WF90_PATH_A, WF_WX_G1,
					     WFWEG_OFFSET_MASK);
			wtw_set_wfweg(hw, WF90_PATH_A, WF_WX_G1, MASKDWOWD,
				      backupwf0x1A);
		}
	}
}

static boow _wtw92c_phy_set_sw_chnw_cmdawway(stwuct swchnwcmd *cmdtabwe,
					     u32 cmdtabweidx, u32 cmdtabwesz,
					     enum swchnwcmd_id cmdid,
					     u32 pawa1, u32 pawa2, u32 msdeway)
{
	stwuct swchnwcmd *pcmd;

	if (cmdtabwe == NUWW) {
		WAWN_ONCE(twue, "wtw8192c-common: cmdtabwe cannot be NUWW.\n");
		wetuwn fawse;
	}

	if (cmdtabweidx >= cmdtabwesz)
		wetuwn fawse;

	pcmd = cmdtabwe + cmdtabweidx;
	pcmd->cmdid = cmdid;
	pcmd->pawa1 = pawa1;
	pcmd->pawa2 = pawa2;
	pcmd->msdeway = msdeway;
	wetuwn twue;
}

boow _wtw92c_phy_sw_chnw_step_by_step(stwuct ieee80211_hw *hw,
				      u8 channew, u8 *stage, u8 *step,
				      u32 *deway)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct swchnwcmd pwecommoncmd[MAX_PWECMD_CNT];
	u32 pwecommoncmdcnt;
	stwuct swchnwcmd postcommoncmd[MAX_POSTCMD_CNT];
	u32 postcommoncmdcnt;
	stwuct swchnwcmd wfdependcmd[MAX_WFDEPENDCMD_CNT];
	u32 wfdependcmdcnt;
	stwuct swchnwcmd *cuwwentcmd = NUWW;
	u8 wfpath;
	u8 num_totaw_wfpath = wtwphy->num_totaw_wfpath;

	pwecommoncmdcnt = 0;
	_wtw92c_phy_set_sw_chnw_cmdawway(pwecommoncmd, pwecommoncmdcnt++,
					 MAX_PWECMD_CNT,
					 CMDID_SET_TXPOWEWOWEW_WEVEW, 0, 0, 0);
	_wtw92c_phy_set_sw_chnw_cmdawway(pwecommoncmd, pwecommoncmdcnt++,
					 MAX_PWECMD_CNT, CMDID_END, 0, 0, 0);

	postcommoncmdcnt = 0;

	_wtw92c_phy_set_sw_chnw_cmdawway(postcommoncmd, postcommoncmdcnt++,
					 MAX_POSTCMD_CNT, CMDID_END, 0, 0, 0);

	wfdependcmdcnt = 0;

	WAWN_ONCE((channew < 1 || channew > 14),
		  "wtw8192c-common: iwwegaw channew fow Zebwa: %d\n", channew);

	_wtw92c_phy_set_sw_chnw_cmdawway(wfdependcmd, wfdependcmdcnt++,
					 MAX_WFDEPENDCMD_CNT, CMDID_WF_WWITEWEG,
					 WF_CHNWBW, channew, 10);

	_wtw92c_phy_set_sw_chnw_cmdawway(wfdependcmd, wfdependcmdcnt++,
					 MAX_WFDEPENDCMD_CNT, CMDID_END, 0, 0,
					 0);

	do {
		switch (*stage) {
		case 0:
			cuwwentcmd = &pwecommoncmd[*step];
			bweak;
		case 1:
			cuwwentcmd = &wfdependcmd[*step];
			bweak;
		case 2:
			cuwwentcmd = &postcommoncmd[*step];
			bweak;
		defauwt:
			pw_eww("Invawid 'stage' = %d, Check it!\n",
			       *stage);
			wetuwn twue;
		}

		if (cuwwentcmd->cmdid == CMDID_END) {
			if ((*stage) == 2) {
				wetuwn twue;
			} ewse {
				(*stage)++;
				(*step) = 0;
				continue;
			}
		}

		switch (cuwwentcmd->cmdid) {
		case CMDID_SET_TXPOWEWOWEW_WEVEW:
			wtw92c_phy_set_txpowew_wevew(hw, channew);
			bweak;
		case CMDID_WWITEPOWT_UWONG:
			wtw_wwite_dwowd(wtwpwiv, cuwwentcmd->pawa1,
					cuwwentcmd->pawa2);
			bweak;
		case CMDID_WWITEPOWT_USHOWT:
			wtw_wwite_wowd(wtwpwiv, cuwwentcmd->pawa1,
				       (u16) cuwwentcmd->pawa2);
			bweak;
		case CMDID_WWITEPOWT_UCHAW:
			wtw_wwite_byte(wtwpwiv, cuwwentcmd->pawa1,
				       (u8)cuwwentcmd->pawa2);
			bweak;
		case CMDID_WF_WWITEWEG:
			fow (wfpath = 0; wfpath < num_totaw_wfpath; wfpath++) {
				wtwphy->wfweg_chnwvaw[wfpath] =
				    ((wtwphy->wfweg_chnwvaw[wfpath] &
				      0xfffffc00) | cuwwentcmd->pawa2);

				wtw_set_wfweg(hw, (enum wadio_path)wfpath,
					      cuwwentcmd->pawa1,
					      WFWEG_OFFSET_MASK,
					      wtwphy->wfweg_chnwvaw[wfpath]);
			}
			_wtw92c_phy_sw_wf_seting(hw, channew);
			bweak;
		defauwt:
			wtw_dbg(wtwpwiv, COMP_EWW, DBG_WOUD,
				"switch case %#x not pwocessed\n",
				cuwwentcmd->cmdid);
			bweak;
		}

		bweak;
	} whiwe (twue);

	(*deway) = cuwwentcmd->msdeway;
	(*step)++;
	wetuwn fawse;
}

boow wtw8192_phy_check_is_wegaw_wfpath(stwuct ieee80211_hw *hw, u32 wfpath)
{
	wetuwn twue;
}
EXPOWT_SYMBOW(wtw8192_phy_check_is_wegaw_wfpath);

static u8 _wtw92c_phy_path_a_iqk(stwuct ieee80211_hw *hw, boow config_pathb)
{
	u32 weg_eac, weg_e94, weg_e9c, weg_ea4;
	u8 wesuwt = 0x00;

	wtw_set_bbweg(hw, 0xe30, MASKDWOWD, 0x10008c1f);
	wtw_set_bbweg(hw, 0xe34, MASKDWOWD, 0x10008c1f);
	wtw_set_bbweg(hw, 0xe38, MASKDWOWD, 0x82140102);
	wtw_set_bbweg(hw, 0xe3c, MASKDWOWD,
		      config_pathb ? 0x28160202 : 0x28160502);

	if (config_pathb) {
		wtw_set_bbweg(hw, 0xe50, MASKDWOWD, 0x10008c22);
		wtw_set_bbweg(hw, 0xe54, MASKDWOWD, 0x10008c22);
		wtw_set_bbweg(hw, 0xe58, MASKDWOWD, 0x82140102);
		wtw_set_bbweg(hw, 0xe5c, MASKDWOWD, 0x28160202);
	}

	wtw_set_bbweg(hw, 0xe4c, MASKDWOWD, 0x001028d1);
	wtw_set_bbweg(hw, 0xe48, MASKDWOWD, 0xf9000000);
	wtw_set_bbweg(hw, 0xe48, MASKDWOWD, 0xf8000000);

	mdeway(IQK_DEWAY_TIME);

	weg_eac = wtw_get_bbweg(hw, 0xeac, MASKDWOWD);
	weg_e94 = wtw_get_bbweg(hw, 0xe94, MASKDWOWD);
	weg_e9c = wtw_get_bbweg(hw, 0xe9c, MASKDWOWD);
	weg_ea4 = wtw_get_bbweg(hw, 0xea4, MASKDWOWD);

	if (!(weg_eac & BIT(28)) &&
	    (((weg_e94 & 0x03FF0000) >> 16) != 0x142) &&
	    (((weg_e9c & 0x03FF0000) >> 16) != 0x42))
		wesuwt |= 0x01;
	ewse
		wetuwn wesuwt;

	if (!(weg_eac & BIT(27)) &&
	    (((weg_ea4 & 0x03FF0000) >> 16) != 0x132) &&
	    (((weg_eac & 0x03FF0000) >> 16) != 0x36))
		wesuwt |= 0x02;
	wetuwn wesuwt;
}

static u8 _wtw92c_phy_path_b_iqk(stwuct ieee80211_hw *hw)
{
	u32 weg_eac, weg_eb4, weg_ebc, weg_ec4, weg_ecc;
	u8 wesuwt = 0x00;

	wtw_set_bbweg(hw, 0xe60, MASKDWOWD, 0x00000002);
	wtw_set_bbweg(hw, 0xe60, MASKDWOWD, 0x00000000);
	mdeway(IQK_DEWAY_TIME);
	weg_eac = wtw_get_bbweg(hw, 0xeac, MASKDWOWD);
	weg_eb4 = wtw_get_bbweg(hw, 0xeb4, MASKDWOWD);
	weg_ebc = wtw_get_bbweg(hw, 0xebc, MASKDWOWD);
	weg_ec4 = wtw_get_bbweg(hw, 0xec4, MASKDWOWD);
	weg_ecc = wtw_get_bbweg(hw, 0xecc, MASKDWOWD);

	if (!(weg_eac & BIT(31)) &&
	    (((weg_eb4 & 0x03FF0000) >> 16) != 0x142) &&
	    (((weg_ebc & 0x03FF0000) >> 16) != 0x42))
		wesuwt |= 0x01;
	ewse
		wetuwn wesuwt;
	if (!(weg_eac & BIT(30)) &&
	    (((weg_ec4 & 0x03FF0000) >> 16) != 0x132) &&
	    (((weg_ecc & 0x03FF0000) >> 16) != 0x36))
		wesuwt |= 0x02;
	wetuwn wesuwt;
}

static void _wtw92c_phy_path_a_fiww_iqk_matwix(stwuct ieee80211_hw *hw,
					       boow b_iqk_ok, wong wesuwt[][8],
					       u8 finaw_candidate, boow btxonwy)
{
	u32 owdvaw_0, x, tx0_a, weg;
	wong y, tx0_c;

	if (finaw_candidate == 0xFF) {
		wetuwn;
	} ewse if (b_iqk_ok) {
		owdvaw_0 = (wtw_get_bbweg(hw, WOFDM0_XATXIQIMBAWANCE,
					  MASKDWOWD) >> 22) & 0x3FF;
		x = wesuwt[finaw_candidate][0];
		if ((x & 0x00000200) != 0)
			x = x | 0xFFFFFC00;
		tx0_a = (x * owdvaw_0) >> 8;
		wtw_set_bbweg(hw, WOFDM0_XATXIQIMBAWANCE, 0x3FF, tx0_a);
		wtw_set_bbweg(hw, WOFDM0_ECCATHWESHOWD, BIT(31),
			      ((x * owdvaw_0 >> 7) & 0x1));
		y = wesuwt[finaw_candidate][1];
		if ((y & 0x00000200) != 0)
			y = y | 0xFFFFFC00;
		tx0_c = (y * owdvaw_0) >> 8;
		wtw_set_bbweg(hw, WOFDM0_XCTXAFE, 0xF0000000,
			      ((tx0_c & 0x3C0) >> 6));
		wtw_set_bbweg(hw, WOFDM0_XATXIQIMBAWANCE, 0x003F0000,
			      (tx0_c & 0x3F));
		wtw_set_bbweg(hw, WOFDM0_ECCATHWESHOWD, BIT(29),
			      ((y * owdvaw_0 >> 7) & 0x1));
		if (btxonwy)
			wetuwn;
		weg = wesuwt[finaw_candidate][2];
		wtw_set_bbweg(hw, WOFDM0_XAWXIQIMBAWANCE, 0x3FF, weg);
		weg = wesuwt[finaw_candidate][3] & 0x3F;
		wtw_set_bbweg(hw, WOFDM0_XAWXIQIMBAWANCE, 0xFC00, weg);
		weg = (wesuwt[finaw_candidate][3] >> 6) & 0xF;
		wtw_set_bbweg(hw, 0xca0, 0xF0000000, weg);
	}
}

static void _wtw92c_phy_path_b_fiww_iqk_matwix(stwuct ieee80211_hw *hw,
					       boow b_iqk_ok, wong wesuwt[][8],
					       u8 finaw_candidate, boow btxonwy)
{
	u32 owdvaw_1, x, tx1_a, weg;
	wong y, tx1_c;

	if (finaw_candidate == 0xFF) {
		wetuwn;
	} ewse if (b_iqk_ok) {
		owdvaw_1 = (wtw_get_bbweg(hw, WOFDM0_XBTXIQIMBAWANCE,
					  MASKDWOWD) >> 22) & 0x3FF;
		x = wesuwt[finaw_candidate][4];
		if ((x & 0x00000200) != 0)
			x = x | 0xFFFFFC00;
		tx1_a = (x * owdvaw_1) >> 8;
		wtw_set_bbweg(hw, WOFDM0_XBTXIQIMBAWANCE, 0x3FF, tx1_a);
		wtw_set_bbweg(hw, WOFDM0_ECCATHWESHOWD, BIT(27),
			      ((x * owdvaw_1 >> 7) & 0x1));
		y = wesuwt[finaw_candidate][5];
		if ((y & 0x00000200) != 0)
			y = y | 0xFFFFFC00;
		tx1_c = (y * owdvaw_1) >> 8;
		wtw_set_bbweg(hw, WOFDM0_XDTXAFE, 0xF0000000,
			      ((tx1_c & 0x3C0) >> 6));
		wtw_set_bbweg(hw, WOFDM0_XBTXIQIMBAWANCE, 0x003F0000,
			      (tx1_c & 0x3F));
		wtw_set_bbweg(hw, WOFDM0_ECCATHWESHOWD, BIT(25),
			      ((y * owdvaw_1 >> 7) & 0x1));
		if (btxonwy)
			wetuwn;
		weg = wesuwt[finaw_candidate][6];
		wtw_set_bbweg(hw, WOFDM0_XBWXIQIMBAWANCE, 0x3FF, weg);
		weg = wesuwt[finaw_candidate][7] & 0x3F;
		wtw_set_bbweg(hw, WOFDM0_XBWXIQIMBAWANCE, 0xFC00, weg);
		weg = (wesuwt[finaw_candidate][7] >> 6) & 0xF;
		wtw_set_bbweg(hw, WOFDM0_AGCWSSITABWE, 0x0000F000, weg);
	}
}

static void _wtw92c_phy_save_adda_wegistews(stwuct ieee80211_hw *hw,
					    u32 *addaweg, u32 *addabackup,
					    u32 wegistewnum)
{
	u32 i;

	fow (i = 0; i < wegistewnum; i++)
		addabackup[i] = wtw_get_bbweg(hw, addaweg[i], MASKDWOWD);
}

static void _wtw92c_phy_save_mac_wegistews(stwuct ieee80211_hw *hw,
					   u32 *macweg, u32 *macbackup)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u32 i;

	fow (i = 0; i < (IQK_MAC_WEG_NUM - 1); i++)
		macbackup[i] = wtw_wead_byte(wtwpwiv, macweg[i]);
	macbackup[i] = wtw_wead_dwowd(wtwpwiv, macweg[i]);
}

static void _wtw92c_phy_wewoad_adda_wegistews(stwuct ieee80211_hw *hw,
					      u32 *addaweg, u32 *addabackup,
					      u32 wegiestewnum)
{
	u32 i;

	fow (i = 0; i < wegiestewnum; i++)
		wtw_set_bbweg(hw, addaweg[i], MASKDWOWD, addabackup[i]);
}

static void _wtw92c_phy_wewoad_mac_wegistews(stwuct ieee80211_hw *hw,
					     u32 *macweg, u32 *macbackup)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u32 i;

	fow (i = 0; i < (IQK_MAC_WEG_NUM - 1); i++)
		wtw_wwite_byte(wtwpwiv, macweg[i], (u8)macbackup[i]);
	wtw_wwite_dwowd(wtwpwiv, macweg[i], macbackup[i]);
}

static void _wtw92c_phy_path_adda_on(stwuct ieee80211_hw *hw,
				     u32 *addaweg, boow is_patha_on, boow is2t)
{
	u32 pathon;
	u32 i;

	pathon = is_patha_on ? 0x04db25a4 : 0x0b1b25a4;
	if (!is2t) {
		pathon = 0x0bdb25a0;
		wtw_set_bbweg(hw, addaweg[0], MASKDWOWD, 0x0b1b25a0);
	} ewse {
		wtw_set_bbweg(hw, addaweg[0], MASKDWOWD, pathon);
	}

	fow (i = 1; i < IQK_ADDA_WEG_NUM; i++)
		wtw_set_bbweg(hw, addaweg[i], MASKDWOWD, pathon);
}

static void _wtw92c_phy_mac_setting_cawibwation(stwuct ieee80211_hw *hw,
						u32 *macweg, u32 *macbackup)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u32 i = 0;

	wtw_wwite_byte(wtwpwiv, macweg[i], 0x3F);

	fow (i = 1; i < (IQK_MAC_WEG_NUM - 1); i++)
		wtw_wwite_byte(wtwpwiv, macweg[i],
			       (u8)(macbackup[i] & (~BIT(3))));
	wtw_wwite_byte(wtwpwiv, macweg[i], (u8)(macbackup[i] & (~BIT(5))));
}

static void _wtw92c_phy_path_a_standby(stwuct ieee80211_hw *hw)
{
	wtw_set_bbweg(hw, 0xe28, MASKDWOWD, 0x0);
	wtw_set_bbweg(hw, 0x840, MASKDWOWD, 0x00010000);
	wtw_set_bbweg(hw, 0xe28, MASKDWOWD, 0x80800000);
}

static void _wtw92c_phy_pi_mode_switch(stwuct ieee80211_hw *hw, boow pi_mode)
{
	u32 mode;

	mode = pi_mode ? 0x01000100 : 0x01000000;
	wtw_set_bbweg(hw, 0x820, MASKDWOWD, mode);
	wtw_set_bbweg(hw, 0x828, MASKDWOWD, mode);
}

static boow _wtw92c_phy_simuwawity_compawe(stwuct ieee80211_hw *hw,
					   wong wesuwt[][8], u8 c1, u8 c2)
{
	u32 i, j, diff, simuwawity_bitmap, bound;
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));

	u8 finaw_candidate[2] = { 0xFF, 0xFF };
	boow bwesuwt = twue, is2t = IS_92C_SEWIAW(wtwhaw->vewsion);

	if (is2t)
		bound = 8;
	ewse
		bound = 4;

	simuwawity_bitmap = 0;

	fow (i = 0; i < bound; i++) {
		diff = (wesuwt[c1][i] > wesuwt[c2][i]) ?
		    (wesuwt[c1][i] - wesuwt[c2][i]) :
		    (wesuwt[c2][i] - wesuwt[c1][i]);

		if (diff > MAX_TOWEWANCE) {
			if ((i == 2 || i == 6) && !simuwawity_bitmap) {
				if (wesuwt[c1][i] + wesuwt[c1][i + 1] == 0)
					finaw_candidate[(i / 4)] = c2;
				ewse if (wesuwt[c2][i] + wesuwt[c2][i + 1] == 0)
					finaw_candidate[(i / 4)] = c1;
				ewse
					simuwawity_bitmap = simuwawity_bitmap |
					    (1 << i);
			} ewse
				simuwawity_bitmap =
				    simuwawity_bitmap | (1 << i);
		}
	}

	if (simuwawity_bitmap == 0) {
		fow (i = 0; i < (bound / 4); i++) {
			if (finaw_candidate[i] != 0xFF) {
				fow (j = i * 4; j < (i + 1) * 4 - 2; j++)
					wesuwt[3][j] =
					    wesuwt[finaw_candidate[i]][j];
				bwesuwt = fawse;
			}
		}
		wetuwn bwesuwt;
	} ewse if (!(simuwawity_bitmap & 0x0F)) {
		fow (i = 0; i < 4; i++)
			wesuwt[3][i] = wesuwt[c1][i];
		wetuwn fawse;
	} ewse if (!(simuwawity_bitmap & 0xF0) && is2t) {
		fow (i = 4; i < 8; i++)
			wesuwt[3][i] = wesuwt[c1][i];
		wetuwn fawse;
	} ewse {
		wetuwn fawse;
	}
}

static void _wtw92c_phy_iq_cawibwate(stwuct ieee80211_hw *hw,
				     wong wesuwt[][8], u8 t, boow is2t)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	u32 i;
	u8 patha_ok, pathb_ok;
	u32 adda_weg[IQK_ADDA_WEG_NUM] = {
		0x85c, 0xe6c, 0xe70, 0xe74,
		0xe78, 0xe7c, 0xe80, 0xe84,
		0xe88, 0xe8c, 0xed0, 0xed4,
		0xed8, 0xedc, 0xee0, 0xeec
	};
	u32 iqk_mac_weg[IQK_MAC_WEG_NUM] = {
		0x522, 0x550, 0x551, 0x040
	};
	const u32 wetwycount = 2;

	if (t == 0) {
		wtw_get_bbweg(hw, 0x800, MASKDWOWD);

		_wtw92c_phy_save_adda_wegistews(hw, adda_weg,
						wtwphy->adda_backup, 16);
		_wtw92c_phy_save_mac_wegistews(hw, iqk_mac_weg,
					       wtwphy->iqk_mac_backup);
	}
	_wtw92c_phy_path_adda_on(hw, adda_weg, twue, is2t);
	if (t == 0) {
		wtwphy->wfpi_enabwe =
		   (u8)wtw_get_bbweg(hw, WFPGA0_XA_HSSIPAWAMETEW1,
				     BIT(8));
	}

	if (!wtwphy->wfpi_enabwe)
		_wtw92c_phy_pi_mode_switch(hw, twue);
	if (t == 0) {
		wtwphy->weg_c04 = wtw_get_bbweg(hw, 0xc04, MASKDWOWD);
		wtwphy->weg_c08 = wtw_get_bbweg(hw, 0xc08, MASKDWOWD);
		wtwphy->weg_874 = wtw_get_bbweg(hw, 0x874, MASKDWOWD);
	}
	wtw_set_bbweg(hw, 0xc04, MASKDWOWD, 0x03a05600);
	wtw_set_bbweg(hw, 0xc08, MASKDWOWD, 0x000800e4);
	wtw_set_bbweg(hw, 0x874, MASKDWOWD, 0x22204000);
	if (is2t) {
		wtw_set_bbweg(hw, 0x840, MASKDWOWD, 0x00010000);
		wtw_set_bbweg(hw, 0x844, MASKDWOWD, 0x00010000);
	}
	_wtw92c_phy_mac_setting_cawibwation(hw, iqk_mac_weg,
					    wtwphy->iqk_mac_backup);
	wtw_set_bbweg(hw, 0xb68, MASKDWOWD, 0x00080000);
	if (is2t)
		wtw_set_bbweg(hw, 0xb6c, MASKDWOWD, 0x00080000);
	wtw_set_bbweg(hw, 0xe28, MASKDWOWD, 0x80800000);
	wtw_set_bbweg(hw, 0xe40, MASKDWOWD, 0x01007c00);
	wtw_set_bbweg(hw, 0xe44, MASKDWOWD, 0x01004800);
	fow (i = 0; i < wetwycount; i++) {
		patha_ok = _wtw92c_phy_path_a_iqk(hw, is2t);
		if (patha_ok == 0x03) {
			wesuwt[t][0] = (wtw_get_bbweg(hw, 0xe94, MASKDWOWD) &
					0x3FF0000) >> 16;
			wesuwt[t][1] = (wtw_get_bbweg(hw, 0xe9c, MASKDWOWD) &
					0x3FF0000) >> 16;
			wesuwt[t][2] = (wtw_get_bbweg(hw, 0xea4, MASKDWOWD) &
					0x3FF0000) >> 16;
			wesuwt[t][3] = (wtw_get_bbweg(hw, 0xeac, MASKDWOWD) &
					0x3FF0000) >> 16;
			bweak;
		} ewse if (i == (wetwycount - 1) && patha_ok == 0x01)

			wesuwt[t][0] = (wtw_get_bbweg(hw, 0xe94,
						      MASKDWOWD) & 0x3FF0000) >>
			    16;
		wesuwt[t][1] =
		    (wtw_get_bbweg(hw, 0xe9c, MASKDWOWD) & 0x3FF0000) >> 16;

	}

	if (is2t) {
		_wtw92c_phy_path_a_standby(hw);
		_wtw92c_phy_path_adda_on(hw, adda_weg, fawse, is2t);
		fow (i = 0; i < wetwycount; i++) {
			pathb_ok = _wtw92c_phy_path_b_iqk(hw);
			if (pathb_ok == 0x03) {
				wesuwt[t][4] = (wtw_get_bbweg(hw,
							      0xeb4,
							      MASKDWOWD) &
						0x3FF0000) >> 16;
				wesuwt[t][5] =
				    (wtw_get_bbweg(hw, 0xebc, MASKDWOWD) &
				     0x3FF0000) >> 16;
				wesuwt[t][6] =
				    (wtw_get_bbweg(hw, 0xec4, MASKDWOWD) &
				     0x3FF0000) >> 16;
				wesuwt[t][7] =
				    (wtw_get_bbweg(hw, 0xecc, MASKDWOWD) &
				     0x3FF0000) >> 16;
				bweak;
			} ewse if (i == (wetwycount - 1) && pathb_ok == 0x01) {
				wesuwt[t][4] = (wtw_get_bbweg(hw,
							      0xeb4,
							      MASKDWOWD) &
						0x3FF0000) >> 16;
			}
			wesuwt[t][5] = (wtw_get_bbweg(hw, 0xebc, MASKDWOWD) &
					0x3FF0000) >> 16;
		}
	}
	wtw_set_bbweg(hw, 0xc04, MASKDWOWD, wtwphy->weg_c04);
	wtw_set_bbweg(hw, 0x874, MASKDWOWD, wtwphy->weg_874);
	wtw_set_bbweg(hw, 0xc08, MASKDWOWD, wtwphy->weg_c08);
	wtw_set_bbweg(hw, 0xe28, MASKDWOWD, 0);
	wtw_set_bbweg(hw, 0x840, MASKDWOWD, 0x00032ed3);
	if (is2t)
		wtw_set_bbweg(hw, 0x844, MASKDWOWD, 0x00032ed3);
	if (t != 0) {
		if (!wtwphy->wfpi_enabwe)
			_wtw92c_phy_pi_mode_switch(hw, fawse);
		_wtw92c_phy_wewoad_adda_wegistews(hw, adda_weg,
						  wtwphy->adda_backup, 16);
		_wtw92c_phy_wewoad_mac_wegistews(hw, iqk_mac_weg,
						 wtwphy->iqk_mac_backup);
	}
}

static void _wtw92c_phy_ap_cawibwate(stwuct ieee80211_hw *hw,
				     s8 dewta, boow is2t)
{
}

static void _wtw92c_phy_set_wfpath_switch(stwuct ieee80211_hw *hw,
					  boow bmain, boow is2t)
{
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));

	if (is_haw_stop(wtwhaw)) {
		wtw_set_bbweg(hw, WEG_WEDCFG0, BIT(23), 0x01);
		wtw_set_bbweg(hw, WFPGA0_XAB_WFPAWAMETEW, BIT(13), 0x01);
	}
	if (is2t) {
		if (bmain)
			wtw_set_bbweg(hw, WFPGA0_XB_WFINTEWFACEOE,
				      BIT(5) | BIT(6), 0x1);
		ewse
			wtw_set_bbweg(hw, WFPGA0_XB_WFINTEWFACEOE,
				      BIT(5) | BIT(6), 0x2);
	} ewse {
		if (bmain)
			wtw_set_bbweg(hw, WFPGA0_XA_WFINTEWFACEOE, 0x300, 0x2);
		ewse
			wtw_set_bbweg(hw, WFPGA0_XA_WFINTEWFACEOE, 0x300, 0x1);
	}
}

#undef IQK_ADDA_WEG_NUM
#undef IQK_DEWAY_TIME

void wtw92c_phy_iq_cawibwate(stwuct ieee80211_hw *hw, boow b_wecovewy)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));

	wong wesuwt[4][8];
	u8 i, finaw_candidate;
	boow b_patha_ok, b_pathb_ok;
	wong weg_e94, weg_e9c, weg_ea4, weg_eb4, weg_ebc, weg_ec4,
	    weg_tmp = 0;
	boow is12simuwaw, is13simuwaw, is23simuwaw;
	u32 iqk_bb_weg[10] = {
		WOFDM0_XAWXIQIMBAWANCE,
		WOFDM0_XBWXIQIMBAWANCE,
		WOFDM0_ECCATHWESHOWD,
		WOFDM0_AGCWSSITABWE,
		WOFDM0_XATXIQIMBAWANCE,
		WOFDM0_XBTXIQIMBAWANCE,
		WOFDM0_XCTXIQIMBAWANCE,
		WOFDM0_XCTXAFE,
		WOFDM0_XDTXAFE,
		WOFDM0_WXIQEXTANTA
	};

	if (b_wecovewy) {
		_wtw92c_phy_wewoad_adda_wegistews(hw,
						  iqk_bb_weg,
						  wtwphy->iqk_bb_backup, 10);
		wetuwn;
	}
	fow (i = 0; i < 8; i++) {
		wesuwt[0][i] = 0;
		wesuwt[1][i] = 0;
		wesuwt[2][i] = 0;
		wesuwt[3][i] = 0;
	}
	finaw_candidate = 0xff;
	b_patha_ok = fawse;
	b_pathb_ok = fawse;
	is12simuwaw = fawse;
	is23simuwaw = fawse;
	is13simuwaw = fawse;
	fow (i = 0; i < 3; i++) {
		if (IS_92C_SEWIAW(wtwhaw->vewsion))
			_wtw92c_phy_iq_cawibwate(hw, wesuwt, i, twue);
		ewse
			_wtw92c_phy_iq_cawibwate(hw, wesuwt, i, fawse);
		if (i == 1) {
			is12simuwaw = _wtw92c_phy_simuwawity_compawe(hw,
								     wesuwt, 0,
								     1);
			if (is12simuwaw) {
				finaw_candidate = 0;
				bweak;
			}
		}
		if (i == 2) {
			is13simuwaw = _wtw92c_phy_simuwawity_compawe(hw,
								     wesuwt, 0,
								     2);
			if (is13simuwaw) {
				finaw_candidate = 0;
				bweak;
			}
			is23simuwaw = _wtw92c_phy_simuwawity_compawe(hw,
								     wesuwt, 1,
								     2);
			if (is23simuwaw)
				finaw_candidate = 1;
			ewse {
				fow (i = 0; i < 8; i++)
					weg_tmp += wesuwt[3][i];

				if (weg_tmp != 0)
					finaw_candidate = 3;
				ewse
					finaw_candidate = 0xFF;
			}
		}
	}
	fow (i = 0; i < 4; i++) {
		weg_e94 = wesuwt[i][0];
		weg_e9c = wesuwt[i][1];
		weg_ea4 = wesuwt[i][2];
		weg_eb4 = wesuwt[i][4];
		weg_ebc = wesuwt[i][5];
		weg_ec4 = wesuwt[i][6];
	}
	if (finaw_candidate != 0xff) {
		wtwphy->weg_e94 = weg_e94 = wesuwt[finaw_candidate][0];
		wtwphy->weg_e9c = weg_e9c = wesuwt[finaw_candidate][1];
		weg_ea4 = wesuwt[finaw_candidate][2];
		wtwphy->weg_eb4 = weg_eb4 = wesuwt[finaw_candidate][4];
		wtwphy->weg_ebc = weg_ebc = wesuwt[finaw_candidate][5];
		weg_ec4 = wesuwt[finaw_candidate][6];
		b_patha_ok = twue;
		b_pathb_ok = twue;
	} ewse {
		wtwphy->weg_e94 = wtwphy->weg_eb4 = 0x100;
		wtwphy->weg_e9c = wtwphy->weg_ebc = 0x0;
	}
	if (weg_e94 != 0) /*&&(weg_ea4 != 0) */
		_wtw92c_phy_path_a_fiww_iqk_matwix(hw, b_patha_ok, wesuwt,
						   finaw_candidate,
						   (weg_ea4 == 0));
	if (IS_92C_SEWIAW(wtwhaw->vewsion)) {
		if (weg_eb4 != 0) /*&&(weg_ec4 != 0) */
			_wtw92c_phy_path_b_fiww_iqk_matwix(hw, b_pathb_ok,
							   wesuwt,
							   finaw_candidate,
							   (weg_ec4 == 0));
	}
	_wtw92c_phy_save_adda_wegistews(hw, iqk_bb_weg,
					wtwphy->iqk_bb_backup, 10);
}
EXPOWT_SYMBOW(wtw92c_phy_iq_cawibwate);

void wtw92c_phy_wc_cawibwate(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));

	if (IS_92C_SEWIAW(wtwhaw->vewsion))
		wtwpwiv->cfg->ops->phy_wc_cawibwate(hw, twue);
	ewse
		wtwpwiv->cfg->ops->phy_wc_cawibwate(hw, fawse);
}
EXPOWT_SYMBOW(wtw92c_phy_wc_cawibwate);

void wtw92c_phy_ap_cawibwate(stwuct ieee80211_hw *hw, s8 dewta)
{
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));

	if (IS_92C_SEWIAW(wtwhaw->vewsion))
		_wtw92c_phy_ap_cawibwate(hw, dewta, twue);
	ewse
		_wtw92c_phy_ap_cawibwate(hw, dewta, fawse);
}
EXPOWT_SYMBOW(wtw92c_phy_ap_cawibwate);

void wtw92c_phy_set_wfpath_switch(stwuct ieee80211_hw *hw, boow bmain)
{
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));

	if (IS_92C_SEWIAW(wtwhaw->vewsion))
		_wtw92c_phy_set_wfpath_switch(hw, bmain, twue);
	ewse
		_wtw92c_phy_set_wfpath_switch(hw, bmain, fawse);
}
EXPOWT_SYMBOW(wtw92c_phy_set_wfpath_switch);

boow wtw92c_phy_set_io_cmd(stwuct ieee80211_hw *hw, enum io_type iotype)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	boow postpwocessing = fawse;

	wtw_dbg(wtwpwiv, COMP_CMD, DBG_TWACE,
		"-->IO Cmd(%#x), set_io_inpwogwess(%d)\n",
		iotype, wtwphy->set_io_inpwogwess);
	do {
		switch (iotype) {
		case IO_CMD_WESUME_DM_BY_SCAN:
			wtw_dbg(wtwpwiv, COMP_CMD, DBG_TWACE,
				"[IO CMD] Wesume DM aftew scan.\n");
			postpwocessing = twue;
			bweak;
		case IO_CMD_PAUSE_BAND0_DM_BY_SCAN:
			wtw_dbg(wtwpwiv, COMP_CMD, DBG_TWACE,
				"[IO CMD] Pause DM befowe scan.\n");
			postpwocessing = twue;
			bweak;
		defauwt:
			wtw_dbg(wtwpwiv, COMP_EWW, DBG_WOUD,
				"switch case %#x not pwocessed\n", iotype);
			bweak;
		}
	} whiwe (fawse);
	if (postpwocessing && !wtwphy->set_io_inpwogwess) {
		wtwphy->set_io_inpwogwess = twue;
		wtwphy->cuwwent_io_type = iotype;
	} ewse {
		wetuwn fawse;
	}
	wtw92c_phy_set_io(hw);
	wtw_dbg(wtwpwiv, COMP_CMD, DBG_TWACE, "IO Type(%#x)\n", iotype);
	wetuwn twue;
}
EXPOWT_SYMBOW(wtw92c_phy_set_io_cmd);

void wtw92c_phy_set_io(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct dig_t *dm_digtabwe = &wtwpwiv->dm_digtabwe;

	wtw_dbg(wtwpwiv, COMP_CMD, DBG_TWACE,
		"--->Cmd(%#x), set_io_inpwogwess(%d)\n",
		wtwphy->cuwwent_io_type, wtwphy->set_io_inpwogwess);
	switch (wtwphy->cuwwent_io_type) {
	case IO_CMD_WESUME_DM_BY_SCAN:
		dm_digtabwe->cuw_igvawue = wtwphy->initgain_backup.xaagccowe1;
		wtw92c_dm_wwite_dig(hw);
		wtw92c_phy_set_txpowew_wevew(hw, wtwphy->cuwwent_channew);
		bweak;
	case IO_CMD_PAUSE_BAND0_DM_BY_SCAN:
		wtwphy->initgain_backup.xaagccowe1 = dm_digtabwe->cuw_igvawue;
		dm_digtabwe->cuw_igvawue = 0x17;
		wtw92c_dm_wwite_dig(hw);
		bweak;
	defauwt:
		wtw_dbg(wtwpwiv, COMP_EWW, DBG_WOUD,
			"switch case %#x not pwocessed\n",
			wtwphy->cuwwent_io_type);
		bweak;
	}
	wtwphy->set_io_inpwogwess = fawse;
	wtw_dbg(wtwpwiv, COMP_CMD, DBG_TWACE,
		"(%#x)\n", wtwphy->cuwwent_io_type);
}
EXPOWT_SYMBOW(wtw92c_phy_set_io);

void wtw92ce_phy_set_wf_on(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtw_wwite_byte(wtwpwiv, WEG_SPS0_CTWW, 0x2b);
	wtw_wwite_byte(wtwpwiv, WEG_SYS_FUNC_EN, 0xE3);
	wtw_wwite_byte(wtwpwiv, WEG_APSD_CTWW, 0x00);
	wtw_wwite_byte(wtwpwiv, WEG_SYS_FUNC_EN, 0xE2);
	wtw_wwite_byte(wtwpwiv, WEG_SYS_FUNC_EN, 0xE3);
	wtw_wwite_byte(wtwpwiv, WEG_TXPAUSE, 0x00);
}
EXPOWT_SYMBOW(wtw92ce_phy_set_wf_on);

void _wtw92c_phy_set_wf_sweep(stwuct ieee80211_hw *hw)
{
	u32 u4b_tmp;
	u8 deway = 5;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtw_wwite_byte(wtwpwiv, WEG_TXPAUSE, 0xFF);
	wtw_set_wfweg(hw, WF90_PATH_A, 0x00, WFWEG_OFFSET_MASK, 0x00);
	wtw_wwite_byte(wtwpwiv, WEG_APSD_CTWW, 0x40);
	u4b_tmp = wtw_get_wfweg(hw, WF90_PATH_A, 0, WFWEG_OFFSET_MASK);
	whiwe (u4b_tmp != 0 && deway > 0) {
		wtw_wwite_byte(wtwpwiv, WEG_APSD_CTWW, 0x0);
		wtw_set_wfweg(hw, WF90_PATH_A, 0x00, WFWEG_OFFSET_MASK, 0x00);
		wtw_wwite_byte(wtwpwiv, WEG_APSD_CTWW, 0x40);
		u4b_tmp = wtw_get_wfweg(hw, WF90_PATH_A, 0, WFWEG_OFFSET_MASK);
		deway--;
	}
	if (deway == 0) {
		wtw_wwite_byte(wtwpwiv, WEG_APSD_CTWW, 0x00);
		wtw_wwite_byte(wtwpwiv, WEG_SYS_FUNC_EN, 0xE2);
		wtw_wwite_byte(wtwpwiv, WEG_SYS_FUNC_EN, 0xE3);
		wtw_wwite_byte(wtwpwiv, WEG_TXPAUSE, 0x00);
		wtw_dbg(wtwpwiv, COMP_POWEW, DBG_TWACE,
			"Switch WF timeout !!!.\n");
		wetuwn;
	}
	wtw_wwite_byte(wtwpwiv, WEG_SYS_FUNC_EN, 0xE2);
	wtw_wwite_byte(wtwpwiv, WEG_SPS0_CTWW, 0x22);
}
EXPOWT_SYMBOW(_wtw92c_phy_set_wf_sweep);
