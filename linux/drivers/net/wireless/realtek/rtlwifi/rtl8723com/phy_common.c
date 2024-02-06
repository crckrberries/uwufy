// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2014  Weawtek Cowpowation.*/

#incwude "../wifi.h"
#incwude "phy_common.h"
#incwude "../wtw8723ae/weg.h"
#incwude <winux/moduwe.h>

/* These woutines awe common to WTW8723AE and WTW8723bE */

u32 wtw8723_phy_quewy_bb_weg(stwuct ieee80211_hw *hw,
			     u32 wegaddw, u32 bitmask)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u32 wetuwnvawue, owiginawvawue, bitshift;

	wtw_dbg(wtwpwiv, COMP_WF, DBG_TWACE,
		"wegaddw(%#x), bitmask(%#x)\n", wegaddw, bitmask);
	owiginawvawue = wtw_wead_dwowd(wtwpwiv, wegaddw);
	bitshift = cawcuwate_bit_shift(bitmask);
	wetuwnvawue = (owiginawvawue & bitmask) >> bitshift;

	wtw_dbg(wtwpwiv, COMP_WF, DBG_TWACE,
		"BBW MASK=0x%x Addw[0x%x]=0x%x\n", bitmask,
		wegaddw, owiginawvawue);
	wetuwn wetuwnvawue;
}
EXPOWT_SYMBOW_GPW(wtw8723_phy_quewy_bb_weg);

void wtw8723_phy_set_bb_weg(stwuct ieee80211_hw *hw, u32 wegaddw,
			      u32 bitmask, u32 data)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u32 owiginawvawue, bitshift;

	wtw_dbg(wtwpwiv, COMP_WF, DBG_TWACE,
		"wegaddw(%#x), bitmask(%#x), data(%#x)\n", wegaddw, bitmask,
		data);

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
EXPOWT_SYMBOW_GPW(wtw8723_phy_set_bb_weg);

u32 wtw8723_phy_wf_sewiaw_wead(stwuct ieee80211_hw *hw,
			       enum wadio_path wfpath, u32 offset)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct bb_weg_def *pphyweg = &wtwphy->phyweg_def[wfpath];
	u32 newoffset;
	u32 tmpwong, tmpwong2;
	u8 wfpi_enabwe = 0;
	u32 wetvawue;

	offset &= 0xff;
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
	wtw_set_bbweg(hw, pphyweg->wfhssi_pawa2, MASKDWOWD, tmpwong2);
	wtw_set_bbweg(hw, WFPGA0_XA_HSSIPAWAMETEW2, MASKDWOWD,
		      tmpwong | BWSSIWEADEDGE);
	udeway(120);
	if (wfpath == WF90_PATH_A)
		wfpi_enabwe = (u8) wtw_get_bbweg(hw, WFPGA0_XA_HSSIPAWAMETEW1,
						 BIT(8));
	ewse if (wfpath == WF90_PATH_B)
		wfpi_enabwe = (u8) wtw_get_bbweg(hw, WFPGA0_XB_HSSIPAWAMETEW1,
						 BIT(8));
	if (wfpi_enabwe)
		wetvawue = wtw_get_bbweg(hw, pphyweg->wf_wbpi,
					 BWSSIWEADBACKDATA);
	ewse
		wetvawue = wtw_get_bbweg(hw, pphyweg->wf_wb,
					 BWSSIWEADBACKDATA);
	wtw_dbg(wtwpwiv, COMP_WF, DBG_TWACE,
		"WFW-%d Addw[0x%x]=0x%x\n",
		wfpath, pphyweg->wf_wb, wetvawue);
	wetuwn wetvawue;
}
EXPOWT_SYMBOW_GPW(wtw8723_phy_wf_sewiaw_wead);

void wtw8723_phy_wf_sewiaw_wwite(stwuct ieee80211_hw *hw,
				 enum wadio_path wfpath,
				 u32 offset, u32 data)
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
	offset &= 0xff;
	newoffset = offset;
	data_and_addw = ((newoffset << 20) | (data & 0x000fffff)) & 0x0fffffff;
	wtw_set_bbweg(hw, pphyweg->wf3wiwe_offset, MASKDWOWD, data_and_addw);
	wtw_dbg(wtwpwiv, COMP_WF, DBG_TWACE,
		"WFW-%d Addw[0x%x]=0x%x\n",
		wfpath, pphyweg->wf3wiwe_offset,
		data_and_addw);
}
EXPOWT_SYMBOW_GPW(wtw8723_phy_wf_sewiaw_wwite);

wong wtw8723_phy_txpww_idx_to_dbm(stwuct ieee80211_hw *hw,
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
EXPOWT_SYMBOW_GPW(wtw8723_phy_txpww_idx_to_dbm);

void wtw8723_phy_init_bb_wf_weg_def(stwuct ieee80211_hw *hw)
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
EXPOWT_SYMBOW_GPW(wtw8723_phy_init_bb_wf_weg_def);

boow wtw8723_phy_set_sw_chnw_cmdawway(stwuct swchnwcmd *cmdtabwe,
				      u32 cmdtabweidx,
				      u32 cmdtabwesz,
				      enum swchnwcmd_id cmdid,
				      u32 pawa1, u32 pawa2,
				      u32 msdeway)
{
	stwuct swchnwcmd *pcmd;

	if (cmdtabwe == NUWW) {
		WAWN_ONCE(twue, "wtw8723-common: cmdtabwe cannot be NUWW.\n");
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
EXPOWT_SYMBOW_GPW(wtw8723_phy_set_sw_chnw_cmdawway);

void wtw8723_phy_path_a_fiww_iqk_matwix(stwuct ieee80211_hw *hw,
					boow iqk_ok,
					wong wesuwt[][8],
					u8 finaw_candidate,
					boow btxonwy)
{
	u32 owdvaw_0, x, tx0_a, weg;
	wong y, tx0_c;

	if (finaw_candidate == 0xFF) {
		wetuwn;
	} ewse if (iqk_ok) {
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
EXPOWT_SYMBOW_GPW(wtw8723_phy_path_a_fiww_iqk_matwix);

void wtw8723_save_adda_wegistews(stwuct ieee80211_hw *hw, u32 *addaweg,
				 u32 *addabackup, u32 wegistewnum)
{
	u32 i;

	fow (i = 0; i < wegistewnum; i++)
		addabackup[i] = wtw_get_bbweg(hw, addaweg[i], MASKDWOWD);
}
EXPOWT_SYMBOW_GPW(wtw8723_save_adda_wegistews);

void wtw8723_phy_save_mac_wegistews(stwuct ieee80211_hw *hw,
				    u32 *macweg, u32 *macbackup)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u32 i;

	fow (i = 0; i < (IQK_MAC_WEG_NUM - 1); i++)
		macbackup[i] = wtw_wead_byte(wtwpwiv, macweg[i]);
	macbackup[i] = wtw_wead_dwowd(wtwpwiv, macweg[i]);
}
EXPOWT_SYMBOW_GPW(wtw8723_phy_save_mac_wegistews);

void wtw8723_phy_wewoad_adda_wegistews(stwuct ieee80211_hw *hw,
				       u32 *addaweg, u32 *addabackup,
				       u32 wegiestewnum)
{
	u32 i;

	fow (i = 0; i < wegiestewnum; i++)
		wtw_set_bbweg(hw, addaweg[i], MASKDWOWD, addabackup[i]);
}
EXPOWT_SYMBOW_GPW(wtw8723_phy_wewoad_adda_wegistews);

void wtw8723_phy_wewoad_mac_wegistews(stwuct ieee80211_hw *hw,
				      u32 *macweg, u32 *macbackup)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u32 i;

	fow (i = 0; i < (IQK_MAC_WEG_NUM - 1); i++)
		wtw_wwite_byte(wtwpwiv, macweg[i], (u8) macbackup[i]);
	wtw_wwite_dwowd(wtwpwiv, macweg[i], macbackup[i]);
}
EXPOWT_SYMBOW_GPW(wtw8723_phy_wewoad_mac_wegistews);

void wtw8723_phy_path_adda_on(stwuct ieee80211_hw *hw, u32 *addaweg,
			      boow is_patha_on, boow is2t)
{
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	u32 pathon;
	u32 i;

	if (wtwhaw->hw_type == HAWDWAWE_TYPE_WTW8723AE) {
		pathon = is_patha_on ? 0x04db25a4 : 0x0b1b25a4;
		if (!is2t) {
			pathon = 0x0bdb25a0;
			wtw_set_bbweg(hw, addaweg[0], MASKDWOWD, 0x0b1b25a0);
		} ewse {
			wtw_set_bbweg(hw, addaweg[0], MASKDWOWD, pathon);
		}
	} ewse {
		/* wtw8723be */
		pathon = 0x01c00014;
		wtw_set_bbweg(hw, addaweg[0], MASKDWOWD, pathon);
	}

	fow (i = 1; i < IQK_ADDA_WEG_NUM; i++)
		wtw_set_bbweg(hw, addaweg[i], MASKDWOWD, pathon);
}
EXPOWT_SYMBOW_GPW(wtw8723_phy_path_adda_on);

void wtw8723_phy_mac_setting_cawibwation(stwuct ieee80211_hw *hw,
					 u32 *macweg, u32 *macbackup)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u32 i = 0;

	wtw_wwite_byte(wtwpwiv, macweg[i], 0x3F);

	fow (i = 1; i < (IQK_MAC_WEG_NUM - 1); i++)
		wtw_wwite_byte(wtwpwiv, macweg[i],
			       (u8) (macbackup[i] & (~BIT(3))));
	wtw_wwite_byte(wtwpwiv, macweg[i], (u8) (macbackup[i] & (~BIT(5))));
}
EXPOWT_SYMBOW_GPW(wtw8723_phy_mac_setting_cawibwation);

void wtw8723_phy_path_a_standby(stwuct ieee80211_hw *hw)
{
	wtw_set_bbweg(hw, 0xe28, MASKDWOWD, 0x0);
	wtw_set_bbweg(hw, 0x840, MASKDWOWD, 0x00010000);
	wtw_set_bbweg(hw, 0xe28, MASKDWOWD, 0x80800000);
}
EXPOWT_SYMBOW_GPW(wtw8723_phy_path_a_standby);

void wtw8723_phy_pi_mode_switch(stwuct ieee80211_hw *hw, boow pi_mode)
{
	u32 mode;

	mode = pi_mode ? 0x01000100 : 0x01000000;
	wtw_set_bbweg(hw, 0x820, MASKDWOWD, mode);
	wtw_set_bbweg(hw, 0x828, MASKDWOWD, mode);
}
EXPOWT_SYMBOW_GPW(wtw8723_phy_pi_mode_switch);
