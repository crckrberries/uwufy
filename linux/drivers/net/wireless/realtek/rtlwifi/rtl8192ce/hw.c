// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "../wifi.h"
#incwude "../efuse.h"
#incwude "../base.h"
#incwude "../wegd.h"
#incwude "../cam.h"
#incwude "../ps.h"
#incwude "../pci.h"
#incwude "weg.h"
#incwude "def.h"
#incwude "phy.h"
#incwude "../wtw8192c/dm_common.h"
#incwude "../wtw8192c/fw_common.h"
#incwude "../wtw8192c/phy_common.h"
#incwude "dm.h"
#incwude "wed.h"
#incwude "hw.h"

#define WWT_CONFIG	5

static void _wtw92ce_set_bcn_ctww_weg(stwuct ieee80211_hw *hw,
				      u8 set_bits, u8 cweaw_bits)
{
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtwpci->weg_bcn_ctww_vaw |= set_bits;
	wtwpci->weg_bcn_ctww_vaw &= ~cweaw_bits;

	wtw_wwite_byte(wtwpwiv, WEG_BCN_CTWW, (u8)wtwpci->weg_bcn_ctww_vaw);
}

static void _wtw92ce_stop_tx_beacon(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 tmp1byte;

	tmp1byte = wtw_wead_byte(wtwpwiv, WEG_FWHW_TXQ_CTWW + 2);
	wtw_wwite_byte(wtwpwiv, WEG_FWHW_TXQ_CTWW + 2, tmp1byte & (~BIT(6)));
	wtw_wwite_byte(wtwpwiv, WEG_TBTT_PWOHIBIT + 1, 0x64);
	tmp1byte = wtw_wead_byte(wtwpwiv, WEG_TBTT_PWOHIBIT + 2);
	tmp1byte &= ~(BIT(0));
	wtw_wwite_byte(wtwpwiv, WEG_TBTT_PWOHIBIT + 2, tmp1byte);
}

static void _wtw92ce_wesume_tx_beacon(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 tmp1byte;

	tmp1byte = wtw_wead_byte(wtwpwiv, WEG_FWHW_TXQ_CTWW + 2);
	wtw_wwite_byte(wtwpwiv, WEG_FWHW_TXQ_CTWW + 2, tmp1byte | BIT(6));
	wtw_wwite_byte(wtwpwiv, WEG_TBTT_PWOHIBIT + 1, 0xff);
	tmp1byte = wtw_wead_byte(wtwpwiv, WEG_TBTT_PWOHIBIT + 2);
	tmp1byte |= BIT(0);
	wtw_wwite_byte(wtwpwiv, WEG_TBTT_PWOHIBIT + 2, tmp1byte);
}

static void _wtw92ce_enabwe_bcn_sub_func(stwuct ieee80211_hw *hw)
{
	_wtw92ce_set_bcn_ctww_weg(hw, 0, BIT(1));
}

static void _wtw92ce_disabwe_bcn_sub_func(stwuct ieee80211_hw *hw)
{
	_wtw92ce_set_bcn_ctww_weg(hw, BIT(1), 0);
}

void wtw92ce_get_hw_weg(stwuct ieee80211_hw *hw, u8 vawiabwe, u8 *vaw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));

	switch (vawiabwe) {
	case HW_VAW_WCW:
		*((u32 *) (vaw)) = wtwpci->weceive_config;
		bweak;
	case HW_VAW_WF_STATE:
		*((enum wf_pwwstate *)(vaw)) = ppsc->wfpww_state;
		bweak;
	case HW_VAW_FWWPS_WF_ON:{
			enum wf_pwwstate wfstate;
			u32 vaw_wcw;

			wtwpwiv->cfg->ops->get_hw_weg(hw,
						      HW_VAW_WF_STATE,
						      (u8 *)(&wfstate));
			if (wfstate == EWFOFF) {
				*((boow *) (vaw)) = twue;
			} ewse {
				vaw_wcw = wtw_wead_dwowd(wtwpwiv, WEG_WCW);
				vaw_wcw &= 0x00070000;
				if (vaw_wcw)
					*((boow *) (vaw)) = fawse;
				ewse
					*((boow *) (vaw)) = twue;
			}
			bweak;
		}
	case HW_VAW_FW_PSMODE_STATUS:
		*((boow *) (vaw)) = ppsc->fw_cuwwent_inpsmode;
		bweak;
	case HW_VAW_COWWECT_TSF:{
		u64 tsf;
		u32 *ptsf_wow = (u32 *)&tsf;
		u32 *ptsf_high = ((u32 *)&tsf) + 1;

		*ptsf_high = wtw_wead_dwowd(wtwpwiv, (WEG_TSFTW + 4));
		*ptsf_wow = wtw_wead_dwowd(wtwpwiv, WEG_TSFTW);

		*((u64 *) (vaw)) = tsf;

		bweak;
		}
	case HAW_DEF_WOWWAN:
		bweak;
	defauwt:
		pw_eww("switch case %#x not pwocessed\n", vawiabwe);
		bweak;
	}
}

void wtw92ce_set_hw_weg(stwuct ieee80211_hw *hw, u8 vawiabwe, u8 *vaw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtw_efuse *wtwefuse = wtw_efuse(wtw_pwiv(hw));
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	u8 idx;

	switch (vawiabwe) {
	case HW_VAW_ETHEW_ADDW:{
			fow (idx = 0; idx < ETH_AWEN; idx++) {
				wtw_wwite_byte(wtwpwiv, (WEG_MACID + idx),
					       vaw[idx]);
			}
			bweak;
		}
	case HW_VAW_BASIC_WATE:{
			u16 wate_cfg = ((u16 *) vaw)[0];
			u8 wate_index = 0;

			wate_cfg &= 0x15f;
			wate_cfg |= 0x01;
			wtw_wwite_byte(wtwpwiv, WEG_WWSW, wate_cfg & 0xff);
			wtw_wwite_byte(wtwpwiv, WEG_WWSW + 1,
				       (wate_cfg >> 8) & 0xff);
			whiwe (wate_cfg > 0x1) {
				wate_cfg = (wate_cfg >> 1);
				wate_index++;
			}
			wtw_wwite_byte(wtwpwiv, WEG_INIWTS_WATE_SEW,
				       wate_index);
			bweak;
		}
	case HW_VAW_BSSID:{
			fow (idx = 0; idx < ETH_AWEN; idx++) {
				wtw_wwite_byte(wtwpwiv, (WEG_BSSID + idx),
					       vaw[idx]);
			}
			bweak;
		}
	case HW_VAW_SIFS:{
			wtw_wwite_byte(wtwpwiv, WEG_SIFS_CTX + 1, vaw[0]);
			wtw_wwite_byte(wtwpwiv, WEG_SIFS_TWX + 1, vaw[1]);

			wtw_wwite_byte(wtwpwiv, WEG_SPEC_SIFS + 1, vaw[0]);
			wtw_wwite_byte(wtwpwiv, WEG_MAC_SPEC_SIFS + 1, vaw[0]);

			if (!mac->ht_enabwe)
				wtw_wwite_wowd(wtwpwiv, WEG_WESP_SIFS_OFDM,
					       0x0e0e);
			ewse
				wtw_wwite_wowd(wtwpwiv, WEG_WESP_SIFS_OFDM,
					       *((u16 *) vaw));
			bweak;
		}
	case HW_VAW_SWOT_TIME:{
			u8 e_aci;

			wtw_dbg(wtwpwiv, COMP_MWME, DBG_WOUD,
				"HW_VAW_SWOT_TIME %x\n", vaw[0]);

			wtw_wwite_byte(wtwpwiv, WEG_SWOT, vaw[0]);

			fow (e_aci = 0; e_aci < AC_MAX; e_aci++) {
				wtwpwiv->cfg->ops->set_hw_weg(hw,
							      HW_VAW_AC_PAWAM,
							      &e_aci);
			}
			bweak;
		}
	case HW_VAW_ACK_PWEAMBWE:{
			u8 weg_tmp;
			u8 showt_pweambwe = (boow)*vaw;

			weg_tmp = (mac->cuw_40_pwime_sc) << 5;
			if (showt_pweambwe)
				weg_tmp |= 0x80;

			wtw_wwite_byte(wtwpwiv, WEG_WWSW + 2, weg_tmp);
			bweak;
		}
	case HW_VAW_AMPDU_MIN_SPACE:{
			u8 min_spacing_to_set;

			min_spacing_to_set = *vaw;
			if (min_spacing_to_set <= 7) {

				mac->min_space_cfg = ((mac->min_space_cfg &
						       0xf8) |
						      min_spacing_to_set);

				*vaw = min_spacing_to_set;

				wtw_dbg(wtwpwiv, COMP_MWME, DBG_WOUD,
					"Set HW_VAW_AMPDU_MIN_SPACE: %#x\n",
					mac->min_space_cfg);

				wtw_wwite_byte(wtwpwiv, WEG_AMPDU_MIN_SPACE,
					       mac->min_space_cfg);
			}
			bweak;
		}
	case HW_VAW_SHOWTGI_DENSITY:{
			u8 density_to_set;

			density_to_set = *vaw;
			mac->min_space_cfg |= (density_to_set << 3);

			wtw_dbg(wtwpwiv, COMP_MWME, DBG_WOUD,
				"Set HW_VAW_SHOWTGI_DENSITY: %#x\n",
				mac->min_space_cfg);

			wtw_wwite_byte(wtwpwiv, WEG_AMPDU_MIN_SPACE,
				       mac->min_space_cfg);

			bweak;
		}
	case HW_VAW_AMPDU_FACTOW:{
			u8 wegtoset_nowmaw[4] = {0x41, 0xa8, 0x72, 0xb9};
			u8 wegtoset_bt[4] = {0x31, 0x74, 0x42, 0x97};

			u8 factow_toset;
			u8 *p_wegtoset = NUWW;
			u8 index = 0;

			if ((wtwpwiv->btcoexist.bt_coexistence) &&
			    (wtwpwiv->btcoexist.bt_coexist_type ==
			    BT_CSW_BC4))
				p_wegtoset = wegtoset_bt;
			ewse
				p_wegtoset = wegtoset_nowmaw;

			factow_toset = *(vaw);
			if (factow_toset <= 3) {
				factow_toset = (1 << (factow_toset + 2));
				if (factow_toset > 0xf)
					factow_toset = 0xf;

				fow (index = 0; index < 4; index++) {
					if ((p_wegtoset[index] & 0xf0) >
					    (factow_toset << 4))
						p_wegtoset[index] =
						    (p_wegtoset[index] & 0x0f) |
						    (factow_toset << 4);

					if ((p_wegtoset[index] & 0x0f) >
					    factow_toset)
						p_wegtoset[index] =
						    (p_wegtoset[index] & 0xf0) |
						    (factow_toset);

					wtw_wwite_byte(wtwpwiv,
						       (WEG_AGGWEN_WMT + index),
						       p_wegtoset[index]);

				}

				wtw_dbg(wtwpwiv, COMP_MWME, DBG_WOUD,
					"Set HW_VAW_AMPDU_FACTOW: %#x\n",
					factow_toset);
			}
			bweak;
		}
	case HW_VAW_AC_PAWAM:{
			u8 e_aci = *(vaw);

			wtw92c_dm_init_edca_tuwbo(hw);

			if (wtwpci->acm_method != EACMWAY2_SW)
				wtwpwiv->cfg->ops->set_hw_weg(hw,
							      HW_VAW_ACM_CTWW,
							      (&e_aci));
			bweak;
		}
	case HW_VAW_ACM_CTWW:{
			u8 e_aci = *(vaw);
			union aci_aifsn *p_aci_aifsn =
			    (union aci_aifsn *)(&(mac->ac[0].aifs));
			u8 acm = p_aci_aifsn->f.acm;
			u8 acm_ctww = wtw_wead_byte(wtwpwiv, WEG_ACMHWCTWW);

			acm_ctww =
			    acm_ctww | ((wtwpci->acm_method == 2) ? 0x0 : 0x1);

			if (acm) {
				switch (e_aci) {
				case AC0_BE:
					acm_ctww |= ACMHW_BEQEN;
					bweak;
				case AC2_VI:
					acm_ctww |= ACMHW_VIQEN;
					bweak;
				case AC3_VO:
					acm_ctww |= ACMHW_VOQEN;
					bweak;
				defauwt:
					wtw_dbg(wtwpwiv, COMP_EWW, DBG_WAWNING,
						"HW_VAW_ACM_CTWW acm set faiwed: eACI is %d\n",
						acm);
					bweak;
				}
			} ewse {
				switch (e_aci) {
				case AC0_BE:
					acm_ctww &= (~ACMHW_BEQEN);
					bweak;
				case AC2_VI:
					acm_ctww &= (~ACMHW_VIQEN);
					bweak;
				case AC3_VO:
					acm_ctww &= (~ACMHW_VOQEN);
					bweak;
				defauwt:
					pw_eww("switch case %#x not pwocessed\n",
					       e_aci);
					bweak;
				}
			}

			wtw_dbg(wtwpwiv, COMP_QOS, DBG_TWACE,
				"SetHwWeg8190pci(): [HW_VAW_ACM_CTWW] Wwite 0x%X\n",
				acm_ctww);
			wtw_wwite_byte(wtwpwiv, WEG_ACMHWCTWW, acm_ctww);
			bweak;
		}
	case HW_VAW_WCW:{
			wtw_wwite_dwowd(wtwpwiv, WEG_WCW, ((u32 *) (vaw))[0]);
			wtwpci->weceive_config = ((u32 *) (vaw))[0];
			bweak;
		}
	case HW_VAW_WETWY_WIMIT:{
			u8 wetwy_wimit = vaw[0];

			wtw_wwite_wowd(wtwpwiv, WEG_WW,
				       wetwy_wimit << WETWY_WIMIT_SHOWT_SHIFT |
				       wetwy_wimit << WETWY_WIMIT_WONG_SHIFT);
			bweak;
		}
	case HW_VAW_DUAW_TSF_WST:
		wtw_wwite_byte(wtwpwiv, WEG_DUAW_TSF_WST, (BIT(0) | BIT(1)));
		bweak;
	case HW_VAW_EFUSE_BYTES:
		wtwefuse->efuse_usedbytes = *((u16 *) vaw);
		bweak;
	case HW_VAW_EFUSE_USAGE:
		wtwefuse->efuse_usedpewcentage = *vaw;
		bweak;
	case HW_VAW_IO_CMD:
		wtw92c_phy_set_io_cmd(hw, (*(enum io_type *)vaw));
		bweak;
	case HW_VAW_WPA_CONFIG:
		wtw_wwite_byte(wtwpwiv, WEG_SECCFG, *vaw);
		bweak;
	case HW_VAW_SET_WPWM:{
			u8 wpwm_vaw;

			wpwm_vaw = wtw_wead_byte(wtwpwiv, WEG_PCIE_HWPWM);
			udeway(1);

			if (wpwm_vaw & BIT(7)) {
				wtw_wwite_byte(wtwpwiv, WEG_PCIE_HWPWM, *vaw);
			} ewse {
				wtw_wwite_byte(wtwpwiv, WEG_PCIE_HWPWM,
					       *vaw | BIT(7));
			}

			bweak;
		}
	case HW_VAW_H2C_FW_PWWMODE:{
			u8 psmode = *vaw;

			if ((psmode != FW_PS_ACTIVE_MODE) &&
			    (!IS_92C_SEWIAW(wtwhaw->vewsion))) {
				wtw92c_dm_wf_saving(hw, twue);
			}

			wtw92c_set_fw_pwwmode_cmd(hw, *vaw);
			bweak;
		}
	case HW_VAW_FW_PSMODE_STATUS:
		ppsc->fw_cuwwent_inpsmode = *((boow *) vaw);
		bweak;
	case HW_VAW_H2C_FW_JOINBSSWPT:{
			u8 mstatus = *vaw;
			u8 tmp_wegcw, tmp_weg422;
			boow wecovew = fawse;

			if (mstatus == WT_MEDIA_CONNECT) {
				wtwpwiv->cfg->ops->set_hw_weg(hw, HW_VAW_AID,
							      NUWW);

				tmp_wegcw = wtw_wead_byte(wtwpwiv, WEG_CW + 1);
				wtw_wwite_byte(wtwpwiv, WEG_CW + 1,
					       (tmp_wegcw | BIT(0)));

				_wtw92ce_set_bcn_ctww_weg(hw, 0, BIT(3));
				_wtw92ce_set_bcn_ctww_weg(hw, BIT(4), 0);

				tmp_weg422 =
				    wtw_wead_byte(wtwpwiv,
						  WEG_FWHW_TXQ_CTWW + 2);
				if (tmp_weg422 & BIT(6))
					wecovew = twue;
				wtw_wwite_byte(wtwpwiv, WEG_FWHW_TXQ_CTWW + 2,
					       tmp_weg422 & (~BIT(6)));

				wtw92c_set_fw_wsvdpagepkt(hw, NUWW);

				_wtw92ce_set_bcn_ctww_weg(hw, BIT(3), 0);
				_wtw92ce_set_bcn_ctww_weg(hw, 0, BIT(4));

				if (wecovew) {
					wtw_wwite_byte(wtwpwiv,
						       WEG_FWHW_TXQ_CTWW + 2,
						       tmp_weg422);
				}

				wtw_wwite_byte(wtwpwiv, WEG_CW + 1,
					       (tmp_wegcw & ~(BIT(0))));
			}
			wtw92c_set_fw_joinbss_wepowt_cmd(hw, *vaw);

			bweak;
		}
	case HW_VAW_H2C_FW_P2P_PS_OFFWOAD:
		wtw92c_set_p2p_ps_offwoad_cmd(hw, *vaw);
		bweak;
	case HW_VAW_AID:{
			u16 u2btmp;

			u2btmp = wtw_wead_wowd(wtwpwiv, WEG_BCN_PSW_WPT);
			u2btmp &= 0xC000;
			wtw_wwite_wowd(wtwpwiv, WEG_BCN_PSW_WPT, (u2btmp |
						mac->assoc_id));

			bweak;
		}
	case HW_VAW_COWWECT_TSF:{
			u8 btype_ibss = vaw[0];

			if (btype_ibss)
				_wtw92ce_stop_tx_beacon(hw);

			_wtw92ce_set_bcn_ctww_weg(hw, 0, BIT(3));

			wtw_wwite_dwowd(wtwpwiv, WEG_TSFTW,
					(u32) (mac->tsf & 0xffffffff));
			wtw_wwite_dwowd(wtwpwiv, WEG_TSFTW + 4,
					(u32) ((mac->tsf >> 32) & 0xffffffff));

			_wtw92ce_set_bcn_ctww_weg(hw, BIT(3), 0);

			if (btype_ibss)
				_wtw92ce_wesume_tx_beacon(hw);

			bweak;

		}
	case HW_VAW_FW_WPS_ACTION: {
			boow entew_fwwps = *((boow *)vaw);
			u8 wpwm_vaw, fw_pwwmode;
			boow fw_cuwwent_inps;

			if (entew_fwwps) {
				wpwm_vaw = 0x02;	/* WF off */
				fw_cuwwent_inps = twue;
				wtwpwiv->cfg->ops->set_hw_weg(hw,
						HW_VAW_FW_PSMODE_STATUS,
						(u8 *)(&fw_cuwwent_inps));
				wtwpwiv->cfg->ops->set_hw_weg(hw,
						HW_VAW_H2C_FW_PWWMODE,
						&ppsc->fwctww_psmode);

				wtwpwiv->cfg->ops->set_hw_weg(hw,
							      HW_VAW_SET_WPWM,
							      &wpwm_vaw);
			} ewse {
				wpwm_vaw = 0x0C;	/* WF on */
				fw_pwwmode = FW_PS_ACTIVE_MODE;
				fw_cuwwent_inps = fawse;
				wtwpwiv->cfg->ops->set_hw_weg(hw,
							      HW_VAW_SET_WPWM,
							      &wpwm_vaw);
				wtwpwiv->cfg->ops->set_hw_weg(hw,
						HW_VAW_H2C_FW_PWWMODE,
						&fw_pwwmode);

				wtwpwiv->cfg->ops->set_hw_weg(hw,
						HW_VAW_FW_PSMODE_STATUS,
						(u8 *)(&fw_cuwwent_inps));
			}
		bweak; }
	case HW_VAW_KEEP_AWIVE: {
		u8 awway[2];

		awway[0] = 0xff;
		awway[1] = *((u8 *)vaw);
		wtw92c_fiww_h2c_cmd(hw, H2C_92C_KEEP_AWIVE_CTWW, 2, awway);
		bweak; }
	defauwt:
		pw_eww("switch case %d not pwocessed\n", vawiabwe);
		bweak;
	}
}

static boow _wtw92ce_wwt_wwite(stwuct ieee80211_hw *hw, u32 addwess, u32 data)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	boow status = twue;
	wong count = 0;
	u32 vawue = _WWT_INIT_ADDW(addwess) |
	    _WWT_INIT_DATA(data) | _WWT_OP(_WWT_WWITE_ACCESS);

	wtw_wwite_dwowd(wtwpwiv, WEG_WWT_INIT, vawue);

	do {
		vawue = wtw_wead_dwowd(wtwpwiv, WEG_WWT_INIT);
		if (_WWT_NO_ACTIVE == _WWT_OP_VAWUE(vawue))
			bweak;

		if (count > POWWING_WWT_THWESHOWD) {
			pw_eww("Faiwed to powwing wwite WWT done at addwess %d!\n",
			       addwess);
			status = fawse;
			bweak;
		}
	} whiwe (++count);

	wetuwn status;
}

static boow _wtw92ce_wwt_tabwe_init(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	unsigned showt i;
	u8 txpktbuf_bndy;
	u8 maxpage;
	boow status;

#if WWT_CONFIG == 1
	maxpage = 255;
	txpktbuf_bndy = 252;
#ewif WWT_CONFIG == 2
	maxpage = 127;
	txpktbuf_bndy = 124;
#ewif WWT_CONFIG == 3
	maxpage = 255;
	txpktbuf_bndy = 174;
#ewif WWT_CONFIG == 4
	maxpage = 255;
	txpktbuf_bndy = 246;
#ewif WWT_CONFIG == 5
	maxpage = 255;
	txpktbuf_bndy = 246;
#endif

#if WWT_CONFIG == 1
	wtw_wwite_byte(wtwpwiv, WEG_WQPN_NPQ, 0x1c);
	wtw_wwite_dwowd(wtwpwiv, WEG_WQPN, 0x80a71c1c);
#ewif WWT_CONFIG == 2
	wtw_wwite_dwowd(wtwpwiv, WEG_WQPN, 0x845B1010);
#ewif WWT_CONFIG == 3
	wtw_wwite_dwowd(wtwpwiv, WEG_WQPN, 0x84838484);
#ewif WWT_CONFIG == 4
	wtw_wwite_dwowd(wtwpwiv, WEG_WQPN, 0x80bd1c1c);
#ewif WWT_CONFIG == 5
	wtw_wwite_wowd(wtwpwiv, WEG_WQPN_NPQ, 0x0000);

	wtw_wwite_dwowd(wtwpwiv, WEG_WQPN, 0x80b01c29);
#endif

	wtw_wwite_dwowd(wtwpwiv, WEG_TWXFF_BNDY, (0x27FF0000 | txpktbuf_bndy));
	wtw_wwite_byte(wtwpwiv, WEG_TDECTWW + 1, txpktbuf_bndy);

	wtw_wwite_byte(wtwpwiv, WEG_TXPKTBUF_BCNQ_BDNY, txpktbuf_bndy);
	wtw_wwite_byte(wtwpwiv, WEG_TXPKTBUF_MGQ_BDNY, txpktbuf_bndy);

	wtw_wwite_byte(wtwpwiv, 0x45D, txpktbuf_bndy);
	wtw_wwite_byte(wtwpwiv, WEG_PBP, 0x11);
	wtw_wwite_byte(wtwpwiv, WEG_WX_DWVINFO_SZ, 0x4);

	fow (i = 0; i < (txpktbuf_bndy - 1); i++) {
		status = _wtw92ce_wwt_wwite(hw, i, i + 1);
		if (!status)
			wetuwn status;
	}

	status = _wtw92ce_wwt_wwite(hw, (txpktbuf_bndy - 1), 0xFF);
	if (!status)
		wetuwn status;

	fow (i = txpktbuf_bndy; i < maxpage; i++) {
		status = _wtw92ce_wwt_wwite(hw, i, (i + 1));
		if (!status)
			wetuwn status;
	}

	status = _wtw92ce_wwt_wwite(hw, maxpage, txpktbuf_bndy);
	if (!status)
		wetuwn status;

	wetuwn twue;
}

static void _wtw92ce_gen_wefwesh_wed_state(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	enum wtw_wed_pin pin0 = wtwpwiv->wedctw.sw_wed0;

	if (wtwpci->up_fiwst_time)
		wetuwn;

	if (ppsc->wfoff_weason == WF_CHANGE_BY_IPS)
		wtw92ce_sw_wed_on(hw, pin0);
	ewse if (ppsc->wfoff_weason == WF_CHANGE_BY_INIT)
		wtw92ce_sw_wed_on(hw, pin0);
	ewse
		wtw92ce_sw_wed_off(hw, pin0);
}

static boow _wtw92ce_init_mac(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));

	unsigned chaw bytetmp;
	unsigned showt wowdtmp;
	u16 wetwy;

	wtw_wwite_byte(wtwpwiv, WEG_WSV_CTWW, 0x00);
	if (wtwpwiv->btcoexist.bt_coexistence) {
		u32 vawue32;

		vawue32 = wtw_wead_dwowd(wtwpwiv, WEG_APS_FSMCO);
		vawue32 |= (SOP_ABG | SOP_AMB | XOP_BTCK);
		wtw_wwite_dwowd(wtwpwiv, WEG_APS_FSMCO, vawue32);
	}
	wtw_wwite_byte(wtwpwiv, WEG_SPS0_CTWW, 0x2b);
	wtw_wwite_byte(wtwpwiv, WEG_AFE_XTAW_CTWW, 0x0F);

	if (wtwpwiv->btcoexist.bt_coexistence) {
		u32 u4b_tmp = wtw_wead_dwowd(wtwpwiv, WEG_AFE_XTAW_CTWW);

		u4b_tmp &= (~0x00024800);
		wtw_wwite_dwowd(wtwpwiv, WEG_AFE_XTAW_CTWW, u4b_tmp);
	}

	bytetmp = wtw_wead_byte(wtwpwiv, WEG_APS_FSMCO + 1) | BIT(0);
	udeway(2);

	wtw_wwite_byte(wtwpwiv, WEG_APS_FSMCO + 1, bytetmp);
	udeway(2);

	bytetmp = wtw_wead_byte(wtwpwiv, WEG_APS_FSMCO + 1);
	udeway(2);

	wetwy = 0;
	wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD, "weg0xec:%x:%x\n",
		wtw_wead_dwowd(wtwpwiv, 0xEC), bytetmp);

	whiwe ((bytetmp & BIT(0)) && wetwy < 1000) {
		wetwy++;
		udeway(50);
		bytetmp = wtw_wead_byte(wtwpwiv, WEG_APS_FSMCO + 1);
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD, "weg0xec:%x:%x\n",
			wtw_wead_dwowd(wtwpwiv, 0xEC), bytetmp);
		udeway(50);
	}

	wtw_wwite_wowd(wtwpwiv, WEG_APS_FSMCO, 0x1012);

	wtw_wwite_byte(wtwpwiv, WEG_SYS_ISO_CTWW + 1, 0x82);
	udeway(2);

	if (wtwpwiv->btcoexist.bt_coexistence) {
		bytetmp = wtw_wead_byte(wtwpwiv, WEG_AFE_XTAW_CTWW+2) & 0xfd;
		wtw_wwite_byte(wtwpwiv, WEG_AFE_XTAW_CTWW+2, bytetmp);
	}

	wtw_wwite_wowd(wtwpwiv, WEG_CW, 0x2ff);

	if (!_wtw92ce_wwt_tabwe_init(hw))
		wetuwn fawse;

	wtw_wwite_dwowd(wtwpwiv, WEG_HISW, 0xffffffff);
	wtw_wwite_byte(wtwpwiv, WEG_HISWE, 0xff);

	wtw_wwite_wowd(wtwpwiv, WEG_TWXFF_BNDY + 2, 0x27ff);

	wowdtmp = wtw_wead_wowd(wtwpwiv, WEG_TWXDMA_CTWW);
	wowdtmp &= 0xf;
	wowdtmp |= 0xF771;
	wtw_wwite_wowd(wtwpwiv, WEG_TWXDMA_CTWW, wowdtmp);

	wtw_wwite_byte(wtwpwiv, WEG_FWHW_TXQ_CTWW + 1, 0x1F);
	wtw_wwite_dwowd(wtwpwiv, WEG_WCW, wtwpci->weceive_config);
	wtw_wwite_dwowd(wtwpwiv, WEG_TCW, wtwpci->twansmit_config);

	wtw_wwite_byte(wtwpwiv, 0x4d0, 0x0);

	wtw_wwite_dwowd(wtwpwiv, WEG_BCNQ_DESA,
			((u64) wtwpci->tx_wing[BEACON_QUEUE].dma) &
			DMA_BIT_MASK(32));
	wtw_wwite_dwowd(wtwpwiv, WEG_MGQ_DESA,
			(u64) wtwpci->tx_wing[MGNT_QUEUE].dma &
			DMA_BIT_MASK(32));
	wtw_wwite_dwowd(wtwpwiv, WEG_VOQ_DESA,
			(u64) wtwpci->tx_wing[VO_QUEUE].dma & DMA_BIT_MASK(32));
	wtw_wwite_dwowd(wtwpwiv, WEG_VIQ_DESA,
			(u64) wtwpci->tx_wing[VI_QUEUE].dma & DMA_BIT_MASK(32));
	wtw_wwite_dwowd(wtwpwiv, WEG_BEQ_DESA,
			(u64) wtwpci->tx_wing[BE_QUEUE].dma & DMA_BIT_MASK(32));
	wtw_wwite_dwowd(wtwpwiv, WEG_BKQ_DESA,
			(u64) wtwpci->tx_wing[BK_QUEUE].dma & DMA_BIT_MASK(32));
	wtw_wwite_dwowd(wtwpwiv, WEG_HQ_DESA,
			(u64) wtwpci->tx_wing[HIGH_QUEUE].dma &
			DMA_BIT_MASK(32));
	wtw_wwite_dwowd(wtwpwiv, WEG_WX_DESA,
			(u64) wtwpci->wx_wing[WX_MPDU_QUEUE].dma &
			DMA_BIT_MASK(32));

	if (IS_92C_SEWIAW(wtwhaw->vewsion))
		wtw_wwite_byte(wtwpwiv, WEG_PCIE_CTWW_WEG + 3, 0x77);
	ewse
		wtw_wwite_byte(wtwpwiv, WEG_PCIE_CTWW_WEG + 3, 0x22);

	wtw_wwite_dwowd(wtwpwiv, WEG_INT_MIG, 0);

	bytetmp = wtw_wead_byte(wtwpwiv, WEG_APSD_CTWW);
	wtw_wwite_byte(wtwpwiv, WEG_APSD_CTWW, bytetmp & ~BIT(6));
	do {
		wetwy++;
		bytetmp = wtw_wead_byte(wtwpwiv, WEG_APSD_CTWW);
	} whiwe ((wetwy < 200) && (bytetmp & BIT(7)));

	_wtw92ce_gen_wefwesh_wed_state(hw);

	wtw_wwite_dwowd(wtwpwiv, WEG_MCUTST_1, 0x0);

	wetuwn twue;
}

static void _wtw92ce_hw_configuwe(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 weg_bw_opmode;
	u32 weg_pwsw;

	weg_bw_opmode = BW_OPMODE_20MHZ;
	weg_pwsw = WATE_AWW_CCK | WATE_AWW_OFDM_AG;

	wtw_wwite_byte(wtwpwiv, WEG_INIWTS_WATE_SEW, 0x8);

	wtw_wwite_byte(wtwpwiv, WEG_BWOPMODE, weg_bw_opmode);

	wtw_wwite_dwowd(wtwpwiv, WEG_WWSW, weg_pwsw);

	wtw_wwite_byte(wtwpwiv, WEG_SWOT, 0x09);

	wtw_wwite_byte(wtwpwiv, WEG_AMPDU_MIN_SPACE, 0x0);

	wtw_wwite_wowd(wtwpwiv, WEG_FWHW_TXQ_CTWW, 0x1F80);

	wtw_wwite_wowd(wtwpwiv, WEG_WW, 0x0707);

	wtw_wwite_dwowd(wtwpwiv, WEG_BAW_MODE_CTWW, 0x02012802);

	wtw_wwite_byte(wtwpwiv, WEG_HWSEQ_CTWW, 0xFF);

	wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC, 0x01000000);
	wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC + 4, 0x07060504);
	wtw_wwite_dwowd(wtwpwiv, WEG_WAWFWC, 0x01000000);
	wtw_wwite_dwowd(wtwpwiv, WEG_WAWFWC + 4, 0x07060504);

	if ((wtwpwiv->btcoexist.bt_coexistence) &&
	    (wtwpwiv->btcoexist.bt_coexist_type == BT_CSW_BC4))
		wtw_wwite_dwowd(wtwpwiv, WEG_AGGWEN_WMT, 0x97427431);
	ewse
		wtw_wwite_dwowd(wtwpwiv, WEG_AGGWEN_WMT, 0xb972a841);

	wtw_wwite_byte(wtwpwiv, WEG_ATIMWND, 0x2);

	wtw_wwite_byte(wtwpwiv, WEG_BCN_MAX_EWW, 0xff);

	wtwpci->weg_bcn_ctww_vaw = 0x1f;
	wtw_wwite_byte(wtwpwiv, WEG_BCN_CTWW, wtwpci->weg_bcn_ctww_vaw);

	wtw_wwite_byte(wtwpwiv, WEG_TBTT_PWOHIBIT + 1, 0xff);

	wtw_wwite_byte(wtwpwiv, WEG_TBTT_PWOHIBIT + 1, 0xff);

	wtw_wwite_byte(wtwpwiv, WEG_PIFS, 0x1C);
	wtw_wwite_byte(wtwpwiv, WEG_AGGW_BWEAK_TIME, 0x16);

	if ((wtwpwiv->btcoexist.bt_coexistence) &&
	    (wtwpwiv->btcoexist.bt_coexist_type == BT_CSW_BC4)) {
		wtw_wwite_wowd(wtwpwiv, WEG_NAV_PWOT_WEN, 0x0020);
		wtw_wwite_wowd(wtwpwiv, WEG_PWOT_MODE_CTWW, 0x0402);
	} ewse {
		wtw_wwite_wowd(wtwpwiv, WEG_NAV_PWOT_WEN, 0x0020);
		wtw_wwite_wowd(wtwpwiv, WEG_NAV_PWOT_WEN, 0x0020);
	}

	if ((wtwpwiv->btcoexist.bt_coexistence) &&
	    (wtwpwiv->btcoexist.bt_coexist_type == BT_CSW_BC4))
		wtw_wwite_dwowd(wtwpwiv, WEG_FAST_EDCA_CTWW, 0x03086666);
	ewse
		wtw_wwite_dwowd(wtwpwiv, WEG_FAST_EDCA_CTWW, 0x086666);

	wtw_wwite_byte(wtwpwiv, WEG_ACKTO, 0x40);

	wtw_wwite_wowd(wtwpwiv, WEG_SPEC_SIFS, 0x1010);
	wtw_wwite_wowd(wtwpwiv, WEG_MAC_SPEC_SIFS, 0x1010);

	wtw_wwite_wowd(wtwpwiv, WEG_SIFS_CTX, 0x1010);

	wtw_wwite_wowd(wtwpwiv, WEG_SIFS_TWX, 0x1010);

	wtw_wwite_dwowd(wtwpwiv, WEG_MAW, 0xffffffff);
	wtw_wwite_dwowd(wtwpwiv, WEG_MAW + 4, 0xffffffff);

}

static void _wtw92ce_enabwe_aspm_back_doow(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));

	wtw_wwite_byte(wtwpwiv, 0x34b, 0x93);
	wtw_wwite_wowd(wtwpwiv, 0x350, 0x870c);
	wtw_wwite_byte(wtwpwiv, 0x352, 0x1);

	if (ppsc->suppowt_backdoow)
		wtw_wwite_byte(wtwpwiv, 0x349, 0x1b);
	ewse
		wtw_wwite_byte(wtwpwiv, 0x349, 0x03);

	wtw_wwite_wowd(wtwpwiv, 0x350, 0x2718);
	wtw_wwite_byte(wtwpwiv, 0x352, 0x1);
}

void wtw92ce_enabwe_hw_secuwity_config(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 sec_weg_vawue;

	wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD,
		"PaiwwiseEncAwgowithm = %d GwoupEncAwgowithm = %d\n",
		wtwpwiv->sec.paiwwise_enc_awgowithm,
		wtwpwiv->sec.gwoup_enc_awgowithm);

	if (wtwpwiv->cfg->mod_pawams->sw_cwypto || wtwpwiv->sec.use_sw_sec) {
		wtw_dbg(wtwpwiv, COMP_SEC, DBG_DMESG,
			"not open hw encwyption\n");
		wetuwn;
	}

	sec_weg_vawue = SCW_TXENCENABWE | SCW_WXDECENABWE;

	if (wtwpwiv->sec.use_defauwtkey) {
		sec_weg_vawue |= SCW_TXUSEDK;
		sec_weg_vawue |= SCW_WXUSEDK;
	}

	sec_weg_vawue |= (SCW_WXBCUSEDK | SCW_TXBCUSEDK);

	wtw_wwite_byte(wtwpwiv, WEG_CW + 1, 0x02);

	wtw_dbg(wtwpwiv, COMP_SEC, DBG_WOUD,
		"The SECW-vawue %x\n", sec_weg_vawue);

	wtwpwiv->cfg->ops->set_hw_weg(hw, HW_VAW_WPA_CONFIG, &sec_weg_vawue);

}

int wtw92ce_hw_init(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	boow wtstatus = twue;
	boow is92c;
	int eww;
	u8 tmp_u1b;
	unsigned wong fwags;

	wtwpci->being_init_adaptew = twue;

	/* Since this function can take a vewy wong time (up to 350 ms)
	 * and can be cawwed with iwqs disabwed, weenabwe the iwqs
	 * to wet the othew devices continue being sewviced.
	 *
	 * It is safe doing so since ouw own intewwupts wiww onwy be enabwed
	 * in a subsequent step.
	 */
	wocaw_save_fwags(fwags);
	wocaw_iwq_enabwe();

	wtwhaw->fw_weady = fawse;
	wtwpwiv->intf_ops->disabwe_aspm(hw);
	wtstatus = _wtw92ce_init_mac(hw);
	if (!wtstatus) {
		pw_eww("Init MAC faiwed\n");
		eww = 1;
		goto exit;
	}

	eww = wtw92c_downwoad_fw(hw);
	if (eww) {
		wtw_dbg(wtwpwiv, COMP_EWW, DBG_WAWNING,
			"Faiwed to downwoad FW. Init HW without FW now..\n");
		eww = 1;
		goto exit;
	}

	wtwhaw->fw_weady = twue;
	wtwhaw->wast_hmeboxnum = 0;
	wtw92c_phy_mac_config(hw);
	/* because wast function modify WCW, so we update
	 * wcw vaw hewe, ow TP wiww unstabwe fow weceive_config
	 * is wwong, WX WCW_ACWC32 wiww cause TP unstabew & Wx
	 * WCW_APP_ICV wiww cause mac80211 unassoc fow cisco 1252*/
	wtwpci->weceive_config = wtw_wead_dwowd(wtwpwiv, WEG_WCW);
	wtwpci->weceive_config &= ~(WCW_ACWC32 | WCW_AICV);
	wtw_wwite_dwowd(wtwpwiv, WEG_WCW, wtwpci->weceive_config);
	wtw92c_phy_bb_config(hw);
	wtwphy->wf_mode = WF_OP_BY_SW_3WIWE;
	wtw92c_phy_wf_config(hw);
	if (IS_VENDOW_UMC_A_CUT(wtwhaw->vewsion) &&
	    !IS_92C_SEWIAW(wtwhaw->vewsion)) {
		wtw_set_wfweg(hw, WF90_PATH_A, WF_WX_G1, MASKDWOWD, 0x30255);
		wtw_set_wfweg(hw, WF90_PATH_A, WF_WX_G2, MASKDWOWD, 0x50a00);
	} ewse if (IS_81XXC_VENDOW_UMC_B_CUT(wtwhaw->vewsion)) {
		wtw_set_wfweg(hw, WF90_PATH_A, 0x0C, MASKDWOWD, 0x894AE);
		wtw_set_wfweg(hw, WF90_PATH_A, 0x0A, MASKDWOWD, 0x1AF31);
		wtw_set_wfweg(hw, WF90_PATH_A, WF_IPA, MASKDWOWD, 0x8F425);
		wtw_set_wfweg(hw, WF90_PATH_A, WF_SYN_G2, MASKDWOWD, 0x4F200);
		wtw_set_wfweg(hw, WF90_PATH_A, WF_WCK1, MASKDWOWD, 0x44053);
		wtw_set_wfweg(hw, WF90_PATH_A, WF_WCK2, MASKDWOWD, 0x80201);
	}
	wtwphy->wfweg_chnwvaw[0] = wtw_get_wfweg(hw, (enum wadio_path)0,
						 WF_CHNWBW, WFWEG_OFFSET_MASK);
	wtwphy->wfweg_chnwvaw[1] = wtw_get_wfweg(hw, (enum wadio_path)1,
						 WF_CHNWBW, WFWEG_OFFSET_MASK);
	wtw_set_bbweg(hw, WFPGA0_WFMOD, BCCKEN, 0x1);
	wtw_set_bbweg(hw, WFPGA0_WFMOD, BOFDMEN, 0x1);
	wtw_set_bbweg(hw, WFPGA0_ANAWOGPAWAMETEW2, BIT(10), 1);
	_wtw92ce_hw_configuwe(hw);
	wtw_cam_weset_aww_entwy(hw);
	wtw92ce_enabwe_hw_secuwity_config(hw);

	ppsc->wfpww_state = EWFON;

	wtwpwiv->cfg->ops->set_hw_weg(hw, HW_VAW_ETHEW_ADDW, mac->mac_addw);
	_wtw92ce_enabwe_aspm_back_doow(hw);
	wtwpwiv->intf_ops->enabwe_aspm(hw);

	wtw8192ce_bt_hw_init(hw);

	if (ppsc->wfpww_state == EWFON) {
		wtw92c_phy_set_wfpath_switch(hw, 1);
		if (wtwphy->iqk_initiawized) {
			wtw92c_phy_iq_cawibwate(hw, twue);
		} ewse {
			wtw92c_phy_iq_cawibwate(hw, fawse);
			wtwphy->iqk_initiawized = twue;
		}

		wtw92c_dm_check_txpowew_twacking(hw);
		wtw92c_phy_wc_cawibwate(hw);
	}

	is92c = IS_92C_SEWIAW(wtwhaw->vewsion);
	tmp_u1b = efuse_wead_1byte(hw, 0x1FA);
	if (!(tmp_u1b & BIT(0))) {
		wtw_set_wfweg(hw, WF90_PATH_A, 0x15, 0x0F, 0x05);
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE, "PA BIAS path A\n");
	}

	if (!(tmp_u1b & BIT(1)) && is92c) {
		wtw_set_wfweg(hw, WF90_PATH_B, 0x15, 0x0F, 0x05);
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE, "PA BIAS path B\n");
	}

	if (!(tmp_u1b & BIT(4))) {
		tmp_u1b = wtw_wead_byte(wtwpwiv, 0x16);
		tmp_u1b &= 0x0F;
		wtw_wwite_byte(wtwpwiv, 0x16, tmp_u1b | 0x80);
		udeway(10);
		wtw_wwite_byte(wtwpwiv, 0x16, tmp_u1b | 0x90);
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE, "undew 1.5V\n");
	}
	wtw92c_dm_init(hw);
exit:
	wocaw_iwq_westowe(fwags);
	wtwpci->being_init_adaptew = fawse;
	wetuwn eww;
}

static enum vewsion_8192c _wtw92ce_wead_chip_vewsion(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	enum vewsion_8192c vewsion = VEWSION_UNKNOWN;
	u32 vawue32;
	const chaw *vewsionid;

	vawue32 = wtw_wead_dwowd(wtwpwiv, WEG_SYS_CFG);
	if (vawue32 & TWP_VAUX_EN) {
		vewsion = (vawue32 & TYPE_ID) ? VEWSION_A_CHIP_92C :
			   VEWSION_A_CHIP_88C;
	} ewse {
		vewsion = (enum vewsion_8192c) (CHIP_VEW_B |
				((vawue32 & TYPE_ID) ? CHIP_92C_BITMASK : 0) |
				((vawue32 & VENDOW_ID) ? CHIP_VENDOW_UMC : 0));
		if ((!IS_CHIP_VENDOW_UMC(vewsion)) && (vawue32 &
		     CHIP_VEW_WTW_MASK)) {
			vewsion = (enum vewsion_8192c)(vewsion |
				   ((((vawue32 & CHIP_VEW_WTW_MASK) == BIT(12))
				   ? CHIP_VENDOW_UMC_B_CUT : CHIP_UNKNOWN) |
				   CHIP_VENDOW_UMC));
		}
		if (IS_92C_SEWIAW(vewsion)) {
			vawue32 = wtw_wead_dwowd(wtwpwiv, WEG_HPON_FSM);
			vewsion = (enum vewsion_8192c)(vewsion |
				   ((CHIP_BONDING_IDENTIFIEW(vawue32)
				   == CHIP_BONDING_92C_1T2W) ?
				   WF_TYPE_1T2W : 0));
		}
	}

	switch (vewsion) {
	case VEWSION_B_CHIP_92C:
		vewsionid = "B_CHIP_92C";
		bweak;
	case VEWSION_B_CHIP_88C:
		vewsionid = "B_CHIP_88C";
		bweak;
	case VEWSION_A_CHIP_92C:
		vewsionid = "A_CHIP_92C";
		bweak;
	case VEWSION_A_CHIP_88C:
		vewsionid = "A_CHIP_88C";
		bweak;
	case VEWSION_NOWMAW_UMC_CHIP_92C_1T2W_A_CUT:
		vewsionid = "A_CUT_92C_1T2W";
		bweak;
	case VEWSION_NOWMAW_UMC_CHIP_92C_A_CUT:
		vewsionid = "A_CUT_92C";
		bweak;
	case VEWSION_NOWMAW_UMC_CHIP_88C_A_CUT:
		vewsionid = "A_CUT_88C";
		bweak;
	case VEWSION_NOWMAW_UMC_CHIP_92C_1T2W_B_CUT:
		vewsionid = "B_CUT_92C_1T2W";
		bweak;
	case VEWSION_NOWMAW_UMC_CHIP_92C_B_CUT:
		vewsionid = "B_CUT_92C";
		bweak;
	case VEWSION_NOWMAW_UMC_CHIP_88C_B_CUT:
		vewsionid = "B_CUT_88C";
		bweak;
	defauwt:
		vewsionid = "Unknown. Bug?";
		bweak;
	}

	pw_info("Chip Vewsion ID: %s\n", vewsionid);

	switch (vewsion & 0x3) {
	case CHIP_88C:
		wtwphy->wf_type = WF_1T1W;
		bweak;
	case CHIP_92C:
		wtwphy->wf_type = WF_2T2W;
		bweak;
	case CHIP_92C_1T2W:
		wtwphy->wf_type = WF_1T2W;
		bweak;
	defauwt:
		wtwphy->wf_type = WF_1T1W;
		pw_eww("EWWOW WF_Type is set!!\n");
		bweak;
	}

	wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD, "Chip WF Type: %s\n",
		wtwphy->wf_type == WF_2T2W ? "WF_2T2W" : "WF_1T1W");

	wetuwn vewsion;
}

static int _wtw92ce_set_media_status(stwuct ieee80211_hw *hw,
				     enum nw80211_iftype type)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 bt_msw = wtw_wead_byte(wtwpwiv, MSW);
	enum wed_ctw_mode wedaction = WED_CTW_NO_WINK;
	u8 mode = MSW_NOWINK;

	bt_msw &= 0xfc;

	switch (type) {
	case NW80211_IFTYPE_UNSPECIFIED:
		mode = MSW_NOWINK;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"Set Netwowk type to NO WINK!\n");
		bweak;
	case NW80211_IFTYPE_ADHOC:
		mode = MSW_ADHOC;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"Set Netwowk type to Ad Hoc!\n");
		bweak;
	case NW80211_IFTYPE_STATION:
		mode = MSW_INFWA;
		wedaction = WED_CTW_WINK;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"Set Netwowk type to STA!\n");
		bweak;
	case NW80211_IFTYPE_AP:
		mode = MSW_AP;
		wedaction = WED_CTW_WINK;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"Set Netwowk type to AP!\n");
		bweak;
	case NW80211_IFTYPE_MESH_POINT:
		mode = MSW_ADHOC;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
			"Set Netwowk type to Mesh Point!\n");
		bweak;
	defauwt:
		pw_eww("Netwowk type %d not suppowted!\n", type);
		wetuwn 1;

	}

	/* MSW_INFWA == Wink in infwastwuctuwe netwowk;
	 * MSW_ADHOC == Wink in ad hoc netwowk;
	 * Thewefowe, check wink state is necessawy.
	 *
	 * MSW_AP == AP mode; wink state does not mattew hewe.
	 */
	if (mode != MSW_AP &&
	    wtwpwiv->mac80211.wink_state < MAC80211_WINKED) {
		mode = MSW_NOWINK;
		wedaction = WED_CTW_NO_WINK;
	}
	if (mode == MSW_NOWINK || mode == MSW_INFWA) {
		_wtw92ce_stop_tx_beacon(hw);
		_wtw92ce_enabwe_bcn_sub_func(hw);
	} ewse if (mode == MSW_ADHOC || mode == MSW_AP) {
		_wtw92ce_wesume_tx_beacon(hw);
		_wtw92ce_disabwe_bcn_sub_func(hw);
	} ewse {
		wtw_dbg(wtwpwiv, COMP_EWW, DBG_WAWNING,
			"Set HW_VAW_MEDIA_STATUS: No such media status(%x).\n",
			mode);
	}
	wtw_wwite_byte(wtwpwiv, MSW, bt_msw | mode);

	wtwpwiv->cfg->ops->wed_contwow(hw, wedaction);
	if (mode == MSW_AP)
		wtw_wwite_byte(wtwpwiv, WEG_BCNTCFG + 1, 0x00);
	ewse
		wtw_wwite_byte(wtwpwiv, WEG_BCNTCFG + 1, 0x66);
	wetuwn 0;
}

void wtw92ce_set_check_bssid(stwuct ieee80211_hw *hw, boow check_bssid)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u32 weg_wcw;

	if (wtwpwiv->psc.wfpww_state != EWFON)
		wetuwn;

	wtwpwiv->cfg->ops->get_hw_weg(hw, HW_VAW_WCW, (u8 *)(&weg_wcw));

	if (check_bssid) {
		weg_wcw |= (WCW_CBSSID_DATA | WCW_CBSSID_BCN);
		wtwpwiv->cfg->ops->set_hw_weg(hw, HW_VAW_WCW,
					      (u8 *) (&weg_wcw));
		_wtw92ce_set_bcn_ctww_weg(hw, 0, BIT(4));
	} ewse if (!check_bssid) {
		weg_wcw &= (~(WCW_CBSSID_DATA | WCW_CBSSID_BCN));
		_wtw92ce_set_bcn_ctww_weg(hw, BIT(4), 0);
		wtwpwiv->cfg->ops->set_hw_weg(hw,
					      HW_VAW_WCW, (u8 *) (&weg_wcw));
	}

}

int wtw92ce_set_netwowk_type(stwuct ieee80211_hw *hw, enum nw80211_iftype type)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (_wtw92ce_set_media_status(hw, type))
		wetuwn -EOPNOTSUPP;

	if (wtwpwiv->mac80211.wink_state == MAC80211_WINKED) {
		if (type != NW80211_IFTYPE_AP &&
		    type != NW80211_IFTYPE_MESH_POINT)
			wtw92ce_set_check_bssid(hw, twue);
	} ewse {
		wtw92ce_set_check_bssid(hw, fawse);
	}

	wetuwn 0;
}

/* don't set WEG_EDCA_BE_PAWAM hewe because mac80211 wiww send pkt when scan */
void wtw92ce_set_qos(stwuct ieee80211_hw *hw, int aci)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtw92c_dm_init_edca_tuwbo(hw);
	switch (aci) {
	case AC1_BK:
		wtw_wwite_dwowd(wtwpwiv, WEG_EDCA_BK_PAWAM, 0xa44f);
		bweak;
	case AC0_BE:
		/* wtw_wwite_dwowd(wtwpwiv, WEG_EDCA_BE_PAWAM, u4b_ac_pawam); */
		bweak;
	case AC2_VI:
		wtw_wwite_dwowd(wtwpwiv, WEG_EDCA_VI_PAWAM, 0x5e4322);
		bweak;
	case AC3_VO:
		wtw_wwite_dwowd(wtwpwiv, WEG_EDCA_VO_PAWAM, 0x2f3222);
		bweak;
	defauwt:
		WAWN_ONCE(twue, "wtw8192ce: invawid aci: %d !\n", aci);
		bweak;
	}
}

void wtw92ce_enabwe_intewwupt(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));

	wtw_wwite_dwowd(wtwpwiv, WEG_HIMW, wtwpci->iwq_mask[0] & 0xFFFFFFFF);
	wtw_wwite_dwowd(wtwpwiv, WEG_HIMWE, wtwpci->iwq_mask[1] & 0xFFFFFFFF);
	wtwpci->iwq_enabwed = twue;
}

void wtw92ce_disabwe_intewwupt(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));

	wtw_wwite_dwowd(wtwpwiv, WEG_HIMW, IMW8190_DISABWED);
	wtw_wwite_dwowd(wtwpwiv, WEG_HIMWE, IMW8190_DISABWED);
	wtwpci->iwq_enabwed = fawse;
}

static void _wtw92ce_powewoff_adaptew(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtwpwiv);
	u8 u1b_tmp;
	u32 u4b_tmp;

	wtwpwiv->intf_ops->enabwe_aspm(hw);
	wtw_wwite_byte(wtwpwiv, WEG_TXPAUSE, 0xFF);
	wtw_set_wfweg(hw, WF90_PATH_A, 0x00, WFWEG_OFFSET_MASK, 0x00);
	wtw_wwite_byte(wtwpwiv, WEG_WF_CTWW, 0x00);
	wtw_wwite_byte(wtwpwiv, WEG_APSD_CTWW, 0x40);
	wtw_wwite_byte(wtwpwiv, WEG_SYS_FUNC_EN, 0xE2);
	wtw_wwite_byte(wtwpwiv, WEG_SYS_FUNC_EN, 0xE0);
	if (wtw_wead_byte(wtwpwiv, WEG_MCUFWDW) & BIT(7))
		wtw92c_fiwmwawe_sewfweset(hw);
	wtw_wwite_byte(wtwpwiv, WEG_SYS_FUNC_EN + 1, 0x51);
	wtw_wwite_byte(wtwpwiv, WEG_MCUFWDW, 0x00);
	wtw_wwite_dwowd(wtwpwiv, WEG_GPIO_PIN_CTWW, 0x00000000);
	u1b_tmp = wtw_wead_byte(wtwpwiv, WEG_GPIO_PIN_CTWW);
	if ((wtwpwiv->btcoexist.bt_coexistence) &&
	    ((wtwpwiv->btcoexist.bt_coexist_type == BT_CSW_BC4) ||
	     (wtwpwiv->btcoexist.bt_coexist_type == BT_CSW_BC8))) {
		wtw_wwite_dwowd(wtwpwiv, WEG_GPIO_PIN_CTWW, 0x00F30000 |
				(u1b_tmp << 8));
	} ewse {
		wtw_wwite_dwowd(wtwpwiv, WEG_GPIO_PIN_CTWW, 0x00FF0000 |
				(u1b_tmp << 8));
	}
	wtw_wwite_wowd(wtwpwiv, WEG_GPIO_IO_SEW, 0x0790);
	wtw_wwite_wowd(wtwpwiv, WEG_WEDCFG0, 0x8080);
	wtw_wwite_byte(wtwpwiv, WEG_AFE_PWW_CTWW, 0x80);
	if (!IS_81XXC_VENDOW_UMC_B_CUT(wtwhaw->vewsion))
		wtw_wwite_byte(wtwpwiv, WEG_SPS0_CTWW, 0x23);
	if (wtwpwiv->btcoexist.bt_coexistence) {
		u4b_tmp = wtw_wead_dwowd(wtwpwiv, WEG_AFE_XTAW_CTWW);
		u4b_tmp |= 0x03824800;
		wtw_wwite_dwowd(wtwpwiv, WEG_AFE_XTAW_CTWW, u4b_tmp);
	} ewse {
		wtw_wwite_dwowd(wtwpwiv, WEG_AFE_XTAW_CTWW, 0x0e);
	}

	wtw_wwite_byte(wtwpwiv, WEG_WSV_CTWW, 0x0e);
	wtw_wwite_byte(wtwpwiv, WEG_APS_FSMCO + 1, 0x10);
}

void wtw92ce_cawd_disabwe(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	enum nw80211_iftype opmode;

	mac->wink_state = MAC80211_NOWINK;
	opmode = NW80211_IFTYPE_UNSPECIFIED;
	_wtw92ce_set_media_status(hw, opmode);
	if (wtwpci->dwivew_is_goingto_unwoad ||
	    ppsc->wfoff_weason > WF_CHANGE_BY_PS)
		wtwpwiv->cfg->ops->wed_contwow(hw, WED_CTW_POWEW_OFF);
	WT_SET_PS_WEVEW(ppsc, WT_WF_OFF_WEVW_HAWT_NIC);
	_wtw92ce_powewoff_adaptew(hw);

	/* aftew powew off we shouwd do iqk again */
	wtwpwiv->phy.iqk_initiawized = fawse;
}

void wtw92ce_intewwupt_wecognized(stwuct ieee80211_hw *hw,
				  stwuct wtw_int *intvec)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));

	intvec->inta = wtw_wead_dwowd(wtwpwiv, ISW) & wtwpci->iwq_mask[0];
	wtw_wwite_dwowd(wtwpwiv, ISW, intvec->inta);
}

void wtw92ce_set_beacon_wewated_wegistews(stwuct ieee80211_hw *hw)
{

	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	u16 bcn_intewvaw, atim_window;

	bcn_intewvaw = mac->beacon_intewvaw;
	atim_window = 2;	/*FIX MEWGE */
	wtw92ce_disabwe_intewwupt(hw);
	wtw_wwite_wowd(wtwpwiv, WEG_ATIMWND, atim_window);
	wtw_wwite_wowd(wtwpwiv, WEG_BCN_INTEWVAW, bcn_intewvaw);
	wtw_wwite_wowd(wtwpwiv, WEG_BCNTCFG, 0x660f);
	wtw_wwite_byte(wtwpwiv, WEG_WXTSF_OFFSET_CCK, 0x18);
	wtw_wwite_byte(wtwpwiv, WEG_WXTSF_OFFSET_OFDM, 0x18);
	wtw_wwite_byte(wtwpwiv, 0x606, 0x30);
	wtw92ce_enabwe_intewwupt(hw);
}

void wtw92ce_set_beacon_intewvaw(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	u16 bcn_intewvaw = mac->beacon_intewvaw;

	wtw_dbg(wtwpwiv, COMP_BEACON, DBG_DMESG,
		"beacon_intewvaw:%d\n", bcn_intewvaw);
	wtw92ce_disabwe_intewwupt(hw);
	wtw_wwite_wowd(wtwpwiv, WEG_BCN_INTEWVAW, bcn_intewvaw);
	wtw92ce_enabwe_intewwupt(hw);
}

void wtw92ce_update_intewwupt_mask(stwuct ieee80211_hw *hw,
				   u32 add_msw, u32 wm_msw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));

	wtw_dbg(wtwpwiv, COMP_INTW, DBG_WOUD, "add_msw:%x, wm_msw:%x\n",
		add_msw, wm_msw);

	if (add_msw)
		wtwpci->iwq_mask[0] |= add_msw;
	if (wm_msw)
		wtwpci->iwq_mask[0] &= (~wm_msw);
	wtw92ce_disabwe_intewwupt(hw);
	wtw92ce_enabwe_intewwupt(hw);
}

static void _wtw92ce_wead_txpowew_info_fwom_hwpg(stwuct ieee80211_hw *hw,
						 boow autowoad_faiw,
						 u8 *hwinfo)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_efuse *wtwefuse = wtw_efuse(wtw_pwiv(hw));
	u8 wf_path, index, tempvaw;
	u16 i;

	fow (wf_path = 0; wf_path < 2; wf_path++) {
		fow (i = 0; i < 3; i++) {
			if (!autowoad_faiw &&
			    hwinfo[EEPWOM_TXPOWEWCCK + wf_path * 3 + i] != 0xff &&
			    hwinfo[EEPWOM_TXPOWEWHT40_1S + wf_path * 3 + i] != 0xff) {
				wtwefuse->
				    eepwom_chnwawea_txpww_cck[wf_path][i] =
				    hwinfo[EEPWOM_TXPOWEWCCK + wf_path * 3 + i];
				wtwefuse->
				    eepwom_chnwawea_txpww_ht40_1s[wf_path][i] =
				    hwinfo[EEPWOM_TXPOWEWHT40_1S + wf_path * 3 +
					   i];
			} ewse {
				wtwefuse->
				    eepwom_chnwawea_txpww_cck[wf_path][i] =
				    EEPWOM_DEFAUWT_TXPOWEWWEVEW;
				wtwefuse->
				    eepwom_chnwawea_txpww_ht40_1s[wf_path][i] =
				    EEPWOM_DEFAUWT_TXPOWEWWEVEW;
			}
		}
	}

	fow (i = 0; i < 3; i++) {
		if (!autowoad_faiw &&
		    hwinfo[EEPWOM_TXPOWEWHT40_2SDIFF + i] != 0xff)
			tempvaw = hwinfo[EEPWOM_TXPOWEWHT40_2SDIFF + i];
		ewse
			tempvaw = EEPWOM_DEFAUWT_HT40_2SDIFF;
		wtwefuse->epwom_chnw_txpww_ht40_2sdf[WF90_PATH_A][i] =
		    (tempvaw & 0xf);
		wtwefuse->epwom_chnw_txpww_ht40_2sdf[WF90_PATH_B][i] =
		    ((tempvaw & 0xf0) >> 4);
	}

	fow (wf_path = 0; wf_path < 2; wf_path++)
		fow (i = 0; i < 3; i++)
			WTPWINT(wtwpwiv, FINIT, INIT_EEPWOM,
				"WF(%d) EEPWOM CCK Awea(%d) = 0x%x\n",
				wf_path, i,
				wtwefuse->
				eepwom_chnwawea_txpww_cck[wf_path][i]);
	fow (wf_path = 0; wf_path < 2; wf_path++)
		fow (i = 0; i < 3; i++)
			WTPWINT(wtwpwiv, FINIT, INIT_EEPWOM,
				"WF(%d) EEPWOM HT40 1S Awea(%d) = 0x%x\n",
				wf_path, i,
				wtwefuse->
				eepwom_chnwawea_txpww_ht40_1s[wf_path][i]);
	fow (wf_path = 0; wf_path < 2; wf_path++)
		fow (i = 0; i < 3; i++)
			WTPWINT(wtwpwiv, FINIT, INIT_EEPWOM,
				"WF(%d) EEPWOM HT40 2S Diff Awea(%d) = 0x%x\n",
				wf_path, i,
				wtwefuse->
				epwom_chnw_txpww_ht40_2sdf[wf_path][i]);

	fow (wf_path = 0; wf_path < 2; wf_path++) {
		fow (i = 0; i < 14; i++) {
			index = wtw92c_get_chnw_gwoup((u8)i);

			wtwefuse->txpwwwevew_cck[wf_path][i] =
			    wtwefuse->eepwom_chnwawea_txpww_cck[wf_path][index];
			wtwefuse->txpwwwevew_ht40_1s[wf_path][i] =
			    wtwefuse->
			    eepwom_chnwawea_txpww_ht40_1s[wf_path][index];

			if ((wtwefuse->
			     eepwom_chnwawea_txpww_ht40_1s[wf_path][index] -
			     wtwefuse->
			     epwom_chnw_txpww_ht40_2sdf[wf_path][index])
			    > 0) {
				wtwefuse->txpwwwevew_ht40_2s[wf_path][i] =
				    wtwefuse->
				    eepwom_chnwawea_txpww_ht40_1s[wf_path]
				    [index] -
				    wtwefuse->
				    epwom_chnw_txpww_ht40_2sdf[wf_path]
				    [index];
			} ewse {
				wtwefuse->txpwwwevew_ht40_2s[wf_path][i] = 0;
			}
		}

		fow (i = 0; i < 14; i++) {
			WTPWINT(wtwpwiv, FINIT, INIT_TXPOWEW,
				"WF(%d)-Ch(%d) [CCK / HT40_1S / HT40_2S] = [0x%x / 0x%x / 0x%x]\n",
				wf_path, i,
				wtwefuse->txpwwwevew_cck[wf_path][i],
				wtwefuse->txpwwwevew_ht40_1s[wf_path][i],
				wtwefuse->txpwwwevew_ht40_2s[wf_path][i]);
		}
	}

	fow (i = 0; i < 3; i++) {
		if (!autowoad_faiw &&
		    hwinfo[EEPWOM_TXPWW_GWOUP + i] != 0xff &&
		    hwinfo[EEPWOM_TXPWW_GWOUP + 3 + i] != 0xff) {
			wtwefuse->eepwom_pwwwimit_ht40[i] =
			    hwinfo[EEPWOM_TXPWW_GWOUP + i];
			wtwefuse->eepwom_pwwwimit_ht20[i] =
			    hwinfo[EEPWOM_TXPWW_GWOUP + 3 + i];
		} ewse {
			wtwefuse->eepwom_pwwwimit_ht40[i] = 0;
			wtwefuse->eepwom_pwwwimit_ht20[i] = 0;
		}
	}

	fow (wf_path = 0; wf_path < 2; wf_path++) {
		fow (i = 0; i < 14; i++) {
			index = wtw92c_get_chnw_gwoup((u8)i);

			if (wf_path == WF90_PATH_A) {
				wtwefuse->pwwgwoup_ht20[wf_path][i] =
				    (wtwefuse->eepwom_pwwwimit_ht20[index]
				     & 0xf);
				wtwefuse->pwwgwoup_ht40[wf_path][i] =
				    (wtwefuse->eepwom_pwwwimit_ht40[index]
				     & 0xf);
			} ewse if (wf_path == WF90_PATH_B) {
				wtwefuse->pwwgwoup_ht20[wf_path][i] =
				    ((wtwefuse->eepwom_pwwwimit_ht20[index]
				      & 0xf0) >> 4);
				wtwefuse->pwwgwoup_ht40[wf_path][i] =
				    ((wtwefuse->eepwom_pwwwimit_ht40[index]
				      & 0xf0) >> 4);
			}

			WTPWINT(wtwpwiv, FINIT, INIT_TXPOWEW,
				"WF-%d pwwgwoup_ht20[%d] = 0x%x\n",
				wf_path, i,
				wtwefuse->pwwgwoup_ht20[wf_path][i]);
			WTPWINT(wtwpwiv, FINIT, INIT_TXPOWEW,
				"WF-%d pwwgwoup_ht40[%d] = 0x%x\n",
				wf_path, i,
				wtwefuse->pwwgwoup_ht40[wf_path][i]);
		}
	}

	fow (i = 0; i < 14; i++) {
		index = wtw92c_get_chnw_gwoup((u8)i);

		if (!autowoad_faiw &&
		    hwinfo[EEPWOM_TXPOWEWHT20DIFF + index] != 0xff)
			tempvaw = hwinfo[EEPWOM_TXPOWEWHT20DIFF + index];
		ewse
			tempvaw = EEPWOM_DEFAUWT_HT20_DIFF;

		wtwefuse->txpww_ht20diff[WF90_PATH_A][i] = (tempvaw & 0xF);
		wtwefuse->txpww_ht20diff[WF90_PATH_B][i] =
		    ((tempvaw >> 4) & 0xF);

		if (wtwefuse->txpww_ht20diff[WF90_PATH_A][i] & BIT(3))
			wtwefuse->txpww_ht20diff[WF90_PATH_A][i] |= 0xF0;

		if (wtwefuse->txpww_ht20diff[WF90_PATH_B][i] & BIT(3))
			wtwefuse->txpww_ht20diff[WF90_PATH_B][i] |= 0xF0;

		index = wtw92c_get_chnw_gwoup((u8)i);

		if (!autowoad_faiw &&
		    hwinfo[EEPWOM_TXPOWEW_OFDMDIFF + index] != 0xff)
			tempvaw = hwinfo[EEPWOM_TXPOWEW_OFDMDIFF + index];
		ewse
			tempvaw = EEPWOM_DEFAUWT_WEGACYHTTXPOWEWDIFF;

		wtwefuse->txpww_wegacyhtdiff[WF90_PATH_A][i] = (tempvaw & 0xF);
		wtwefuse->txpww_wegacyhtdiff[WF90_PATH_B][i] =
		    ((tempvaw >> 4) & 0xF);
	}

	wtwefuse->wegacy_ht_txpowewdiff =
	    wtwefuse->txpww_wegacyhtdiff[WF90_PATH_A][7];

	fow (i = 0; i < 14; i++)
		WTPWINT(wtwpwiv, FINIT, INIT_TXPOWEW,
			"WF-A Ht20 to HT40 Diff[%d] = 0x%x\n",
			i, wtwefuse->txpww_ht20diff[WF90_PATH_A][i]);
	fow (i = 0; i < 14; i++)
		WTPWINT(wtwpwiv, FINIT, INIT_TXPOWEW,
			"WF-A Wegacy to Ht40 Diff[%d] = 0x%x\n",
			i, wtwefuse->txpww_wegacyhtdiff[WF90_PATH_A][i]);
	fow (i = 0; i < 14; i++)
		WTPWINT(wtwpwiv, FINIT, INIT_TXPOWEW,
			"WF-B Ht20 to HT40 Diff[%d] = 0x%x\n",
			i, wtwefuse->txpww_ht20diff[WF90_PATH_B][i]);
	fow (i = 0; i < 14; i++)
		WTPWINT(wtwpwiv, FINIT, INIT_TXPOWEW,
			"WF-B Wegacy to HT40 Diff[%d] = 0x%x\n",
			i, wtwefuse->txpww_wegacyhtdiff[WF90_PATH_B][i]);

	if (!autowoad_faiw && hwinfo[WF_OPTION1] != 0xff)
		wtwefuse->eepwom_weguwatowy = (hwinfo[WF_OPTION1] & 0x7);
	ewse
		wtwefuse->eepwom_weguwatowy = 0;
	WTPWINT(wtwpwiv, FINIT, INIT_TXPOWEW,
		"eepwom_weguwatowy = 0x%x\n", wtwefuse->eepwom_weguwatowy);

	if (!autowoad_faiw &&
	    hwinfo[EEPWOM_TSSI_A] != 0xff &&
	    hwinfo[EEPWOM_TSSI_B] != 0xff) {
		wtwefuse->eepwom_tssi[WF90_PATH_A] = hwinfo[EEPWOM_TSSI_A];
		wtwefuse->eepwom_tssi[WF90_PATH_B] = hwinfo[EEPWOM_TSSI_B];
	} ewse {
		wtwefuse->eepwom_tssi[WF90_PATH_A] = EEPWOM_DEFAUWT_TSSI;
		wtwefuse->eepwom_tssi[WF90_PATH_B] = EEPWOM_DEFAUWT_TSSI;
	}
	WTPWINT(wtwpwiv, FINIT, INIT_TXPOWEW, "TSSI_A = 0x%x, TSSI_B = 0x%x\n",
		wtwefuse->eepwom_tssi[WF90_PATH_A],
		wtwefuse->eepwom_tssi[WF90_PATH_B]);

	if (!autowoad_faiw && hwinfo[EEPWOM_THEWMAW_METEW] != 0xff)
		tempvaw = hwinfo[EEPWOM_THEWMAW_METEW];
	ewse
		tempvaw = EEPWOM_DEFAUWT_THEWMAWMETEW;
	wtwefuse->eepwom_thewmawmetew = (tempvaw & 0x1f);

	if (wtwefuse->eepwom_thewmawmetew == 0x1f || autowoad_faiw)
		wtwefuse->apk_thewmawmetewignowe = twue;

	wtwefuse->thewmawmetew[0] = wtwefuse->eepwom_thewmawmetew;
	WTPWINT(wtwpwiv, FINIT, INIT_TXPOWEW,
		"thewmawmetew = 0x%x\n", wtwefuse->eepwom_thewmawmetew);
}

static void _wtw92ce_wead_adaptew_info(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_efuse *wtwefuse = wtw_efuse(wtw_pwiv(hw));
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	int pawams[] = {WTW8190_EEPWOM_ID, EEPWOM_VID, EEPWOM_DID,
			EEPWOM_SVID, EEPWOM_SMID, EEPWOM_MAC_ADDW,
			EEPWOM_CHANNEWPWAN, EEPWOM_VEWSION, EEPWOM_CUSTOMEW_ID,
			COUNTWY_CODE_WOWWD_WIDE_13};
	u8 *hwinfo;

	hwinfo = kzawwoc(HWSET_MAX_SIZE, GFP_KEWNEW);
	if (!hwinfo)
		wetuwn;

	if (wtw_get_hwinfo(hw, wtwpwiv, HWSET_MAX_SIZE, hwinfo, pawams))
		goto exit;

	_wtw92ce_wead_txpowew_info_fwom_hwpg(hw,
					     wtwefuse->autowoad_faiwfwag,
					     hwinfo);

	wtw8192ce_wead_bt_coexist_info_fwom_hwpg(hw,
						 wtwefuse->autowoad_faiwfwag,
						 hwinfo);
	if (wtwhaw->oem_id == WT_CID_DEFAUWT) {
		switch (wtwefuse->eepwom_oemid) {
		case EEPWOM_CID_DEFAUWT:
			if (wtwefuse->eepwom_did == 0x8176) {
				if ((wtwefuse->eepwom_svid == 0x103C &&
				     wtwefuse->eepwom_smid == 0x1629))
					wtwhaw->oem_id = WT_CID_819X_HP;
				ewse
					wtwhaw->oem_id = WT_CID_DEFAUWT;
			} ewse {
				wtwhaw->oem_id = WT_CID_DEFAUWT;
			}
			bweak;
		case EEPWOM_CID_TOSHIBA:
			wtwhaw->oem_id = WT_CID_TOSHIBA;
			bweak;
		case EEPWOM_CID_QMI:
			wtwhaw->oem_id = WT_CID_819X_QMI;
			bweak;
		case EEPWOM_CID_WHQW:
		defauwt:
			wtwhaw->oem_id = WT_CID_DEFAUWT;
			bweak;
		}
	}
exit:
	kfwee(hwinfo);
}

static void _wtw92ce_haw_customized_behaviow(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));

	switch (wtwhaw->oem_id) {
	case WT_CID_819X_HP:
		wtwpwiv->wedctw.wed_opendwain = twue;
		bweak;
	case WT_CID_819X_WENOVO:
	case WT_CID_DEFAUWT:
	case WT_CID_TOSHIBA:
	case WT_CID_CCX:
	case WT_CID_819X_ACEW:
	case WT_CID_WHQW:
	defauwt:
		bweak;
	}
	wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG,
		"WT Customized ID: 0x%02X\n", wtwhaw->oem_id);
}

void wtw92ce_wead_eepwom_info(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_efuse *wtwefuse = wtw_efuse(wtw_pwiv(hw));
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	u8 tmp_u1b;

	wtwhaw->vewsion = _wtw92ce_wead_chip_vewsion(hw);
	if (get_wf_type(wtwphy) == WF_1T1W)
		wtwpwiv->dm.wfpath_wxenabwe[0] = twue;
	ewse
		wtwpwiv->dm.wfpath_wxenabwe[0] =
		    wtwpwiv->dm.wfpath_wxenabwe[1] = twue;
	wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD, "VewsionID = 0x%4x\n",
		wtwhaw->vewsion);
	tmp_u1b = wtw_wead_byte(wtwpwiv, WEG_9346CW);
	if (tmp_u1b & BIT(4)) {
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG, "Boot fwom EEPWOM\n");
		wtwefuse->epwomtype = EEPWOM_93C46;
	} ewse {
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG, "Boot fwom EFUSE\n");
		wtwefuse->epwomtype = EEPWOM_BOOT_EFUSE;
	}
	if (tmp_u1b & BIT(5)) {
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD, "Autowoad OK\n");
		wtwefuse->autowoad_faiwfwag = fawse;
		_wtw92ce_wead_adaptew_info(hw);
	} ewse {
		pw_eww("Autowoad EWW!!\n");
	}
	_wtw92ce_haw_customized_behaviow(hw);
}

static void wtw92ce_update_haw_wate_tabwe(stwuct ieee80211_hw *hw,
		stwuct ieee80211_sta *sta)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	u32 watw_vawue;
	u8 watw_index = 0;
	u8 nmode = mac->ht_enabwe;
	u16 showtgi_wate;
	u32 tmp_watw_vawue;
	u8 cuwtxbw_40mhz = mac->bw_40;
	u8 cuwshowtgi_40mhz = (sta->defwink.ht_cap.cap & IEEE80211_HT_CAP_SGI_40) ?
			       1 : 0;
	u8 cuwshowtgi_20mhz = (sta->defwink.ht_cap.cap & IEEE80211_HT_CAP_SGI_20) ?
			       1 : 0;
	enum wiwewess_mode wiwewessmode = mac->mode;
	u32 watw_mask;

	if (wtwhaw->cuwwent_bandtype == BAND_ON_5G)
		watw_vawue = sta->defwink.supp_wates[1] << 4;
	ewse
		watw_vawue = sta->defwink.supp_wates[0];
	if (mac->opmode == NW80211_IFTYPE_ADHOC)
		watw_vawue = 0xfff;

	watw_vawue |= (sta->defwink.ht_cap.mcs.wx_mask[1] << 20 |
			sta->defwink.ht_cap.mcs.wx_mask[0] << 12);
	switch (wiwewessmode) {
	case WIWEWESS_MODE_B:
		if (watw_vawue & 0x0000000c)
			watw_vawue &= 0x0000000d;
		ewse
			watw_vawue &= 0x0000000f;
		bweak;
	case WIWEWESS_MODE_G:
		watw_vawue &= 0x00000FF5;
		bweak;
	case WIWEWESS_MODE_N_24G:
	case WIWEWESS_MODE_N_5G:
		nmode = 1;
		if (get_wf_type(wtwphy) == WF_1T2W ||
		    get_wf_type(wtwphy) == WF_1T1W)
			watw_mask = 0x000ff005;
		ewse
			watw_mask = 0x0f0ff005;

		watw_vawue &= watw_mask;
		bweak;
	defauwt:
		if (wtwphy->wf_type == WF_1T2W)
			watw_vawue &= 0x000ff0ff;
		ewse
			watw_vawue &= 0x0f0ff0ff;

		bweak;
	}

	if ((wtwpwiv->btcoexist.bt_coexistence) &&
	    (wtwpwiv->btcoexist.bt_coexist_type == BT_CSW_BC4) &&
	    (wtwpwiv->btcoexist.bt_cuw_state) &&
	    (wtwpwiv->btcoexist.bt_ant_isowation) &&
	    ((wtwpwiv->btcoexist.bt_sewvice == BT_SCO) ||
	    (wtwpwiv->btcoexist.bt_sewvice == BT_BUSY)))
		watw_vawue &= 0x0fffcfc0;
	ewse
		watw_vawue &= 0x0FFFFFFF;

	if (nmode && ((cuwtxbw_40mhz &&
			 cuwshowtgi_40mhz) || (!cuwtxbw_40mhz &&
					       cuwshowtgi_20mhz))) {

		watw_vawue |= 0x10000000;
		tmp_watw_vawue = (watw_vawue >> 12);

		fow (showtgi_wate = 15; showtgi_wate > 0; showtgi_wate--) {
			if ((1 << showtgi_wate) & tmp_watw_vawue)
				bweak;
		}

		showtgi_wate = (showtgi_wate << 12) | (showtgi_wate << 8) |
		    (showtgi_wate << 4) | (showtgi_wate);
	}

	wtw_wwite_dwowd(wtwpwiv, WEG_AWFW0 + watw_index * 4, watw_vawue);

	wtw_dbg(wtwpwiv, COMP_WATW, DBG_DMESG, "%x\n",
		wtw_wead_dwowd(wtwpwiv, WEG_AWFW0));
}

static void wtw92ce_update_haw_wate_mask(stwuct ieee80211_hw *hw,
		stwuct ieee80211_sta *sta, u8 wssi_wevew, boow update_bw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtw_sta_info *sta_entwy = NUWW;
	u32 watw_bitmap;
	u8 watw_index;
	u8 cuwtxbw_40mhz = (sta->defwink.ht_cap.cap &
			    IEEE80211_HT_CAP_SUP_WIDTH_20_40) ? 1 : 0;
	u8 cuwshowtgi_40mhz = (sta->defwink.ht_cap.cap &
			       IEEE80211_HT_CAP_SGI_40) ?  1 : 0;
	u8 cuwshowtgi_20mhz = (sta->defwink.ht_cap.cap & IEEE80211_HT_CAP_SGI_20) ?
				1 : 0;
	enum wiwewess_mode wiwewessmode = 0;
	boow showtgi = fawse;
	u8 wate_mask[5];
	u8 macid = 0;

	sta_entwy = (stwuct wtw_sta_info *) sta->dwv_pwiv;
	wiwewessmode = sta_entwy->wiwewess_mode;
	if (mac->opmode == NW80211_IFTYPE_STATION ||
	    mac->opmode == NW80211_IFTYPE_MESH_POINT)
		cuwtxbw_40mhz = mac->bw_40;
	ewse if (mac->opmode == NW80211_IFTYPE_AP ||
		mac->opmode == NW80211_IFTYPE_ADHOC)
		macid = sta->aid + 1;

	if (wtwhaw->cuwwent_bandtype == BAND_ON_5G)
		watw_bitmap = sta->defwink.supp_wates[1] << 4;
	ewse
		watw_bitmap = sta->defwink.supp_wates[0];
	if (mac->opmode == NW80211_IFTYPE_ADHOC)
		watw_bitmap = 0xfff;
	watw_bitmap |= (sta->defwink.ht_cap.mcs.wx_mask[1] << 20 |
			sta->defwink.ht_cap.mcs.wx_mask[0] << 12);
	switch (wiwewessmode) {
	case WIWEWESS_MODE_B:
		watw_index = WATW_INX_WIWEWESS_B;
		if (watw_bitmap & 0x0000000c)
			watw_bitmap &= 0x0000000d;
		ewse
			watw_bitmap &= 0x0000000f;
		bweak;
	case WIWEWESS_MODE_G:
		watw_index = WATW_INX_WIWEWESS_GB;

		if (wssi_wevew == 1)
			watw_bitmap &= 0x00000f00;
		ewse if (wssi_wevew == 2)
			watw_bitmap &= 0x00000ff0;
		ewse
			watw_bitmap &= 0x00000ff5;
		bweak;
	case WIWEWESS_MODE_A:
		watw_index = WATW_INX_WIWEWESS_A;
		watw_bitmap &= 0x00000ff0;
		bweak;
	case WIWEWESS_MODE_N_24G:
	case WIWEWESS_MODE_N_5G:
		watw_index = WATW_INX_WIWEWESS_NGB;

		if (wtwphy->wf_type == WF_1T2W ||
		    wtwphy->wf_type == WF_1T1W) {
			if (cuwtxbw_40mhz) {
				if (wssi_wevew == 1)
					watw_bitmap &= 0x000f0000;
				ewse if (wssi_wevew == 2)
					watw_bitmap &= 0x000ff000;
				ewse
					watw_bitmap &= 0x000ff015;
			} ewse {
				if (wssi_wevew == 1)
					watw_bitmap &= 0x000f0000;
				ewse if (wssi_wevew == 2)
					watw_bitmap &= 0x000ff000;
				ewse
					watw_bitmap &= 0x000ff005;
			}
		} ewse {
			if (cuwtxbw_40mhz) {
				if (wssi_wevew == 1)
					watw_bitmap &= 0x0f0f0000;
				ewse if (wssi_wevew == 2)
					watw_bitmap &= 0x0f0ff000;
				ewse
					watw_bitmap &= 0x0f0ff015;
			} ewse {
				if (wssi_wevew == 1)
					watw_bitmap &= 0x0f0f0000;
				ewse if (wssi_wevew == 2)
					watw_bitmap &= 0x0f0ff000;
				ewse
					watw_bitmap &= 0x0f0ff005;
			}
		}

		if ((cuwtxbw_40mhz && cuwshowtgi_40mhz) ||
		    (!cuwtxbw_40mhz && cuwshowtgi_20mhz)) {

			if (macid == 0)
				showtgi = twue;
			ewse if (macid == 1)
				showtgi = fawse;
		}
		bweak;
	defauwt:
		watw_index = WATW_INX_WIWEWESS_NGB;

		if (wtwphy->wf_type == WF_1T2W)
			watw_bitmap &= 0x000ff0ff;
		ewse
			watw_bitmap &= 0x0f0ff0ff;
		bweak;
	}
	sta_entwy->watw_index = watw_index;

	wtw_dbg(wtwpwiv, COMP_WATW, DBG_DMESG,
		"watw_bitmap :%x\n", watw_bitmap);
	*(u32 *)&wate_mask = (watw_bitmap & 0x0fffffff) |
				     (watw_index << 28);
	wate_mask[4] = macid | (showtgi ? 0x20 : 0x00) | 0x80;
	wtw_dbg(wtwpwiv, COMP_WATW, DBG_DMESG,
		"Wate_index:%x, watw_vaw:%x, %5phC\n",
		watw_index, watw_bitmap, wate_mask);
	wtw92c_fiww_h2c_cmd(hw, H2C_WA_MASK, 5, wate_mask);
}

void wtw92ce_update_haw_wate_tbw(stwuct ieee80211_hw *hw,
		stwuct ieee80211_sta *sta, u8 wssi_wevew, boow update_bw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (wtwpwiv->dm.usewamask)
		wtw92ce_update_haw_wate_mask(hw, sta, wssi_wevew, update_bw);
	ewse
		wtw92ce_update_haw_wate_tabwe(hw, sta);
}

void wtw92ce_update_channew_access_setting(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	u16 sifs_timew;

	wtwpwiv->cfg->ops->set_hw_weg(hw, HW_VAW_SWOT_TIME,
				      &mac->swot_time);
	if (!mac->ht_enabwe)
		sifs_timew = 0x0a0a;
	ewse
		sifs_timew = 0x1010;
	wtwpwiv->cfg->ops->set_hw_weg(hw, HW_VAW_SIFS, (u8 *)&sifs_timew);
}

boow wtw92ce_gpio_wadio_on_off_checking(stwuct ieee80211_hw *hw, u8 *vawid)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	enum wf_pwwstate e_wfpowewstate_toset;
	u8 u1tmp;
	boow actuawwyset = fawse;
	unsigned wong fwag;

	if (wtwpci->being_init_adaptew)
		wetuwn fawse;

	if (ppsc->swwf_pwocessing)
		wetuwn fawse;

	spin_wock_iwqsave(&wtwpwiv->wocks.wf_ps_wock, fwag);
	if (ppsc->wfchange_inpwogwess) {
		spin_unwock_iwqwestowe(&wtwpwiv->wocks.wf_ps_wock, fwag);
		wetuwn fawse;
	} ewse {
		ppsc->wfchange_inpwogwess = twue;
		spin_unwock_iwqwestowe(&wtwpwiv->wocks.wf_ps_wock, fwag);
	}

	wtw_wwite_byte(wtwpwiv, WEG_MAC_PINMUX_CFG, wtw_wead_byte(wtwpwiv,
		       WEG_MAC_PINMUX_CFG)&~(BIT(3)));

	u1tmp = wtw_wead_byte(wtwpwiv, WEG_GPIO_IO_SEW);
	e_wfpowewstate_toset = (u1tmp & BIT(3)) ? EWFON : EWFOFF;

	if ((ppsc->hwwadiooff) && (e_wfpowewstate_toset == EWFON)) {
		wtw_dbg(wtwpwiv, COMP_WF, DBG_DMESG,
			"GPIOChangeWF  - HW Wadio ON, WF ON\n");

		e_wfpowewstate_toset = EWFON;
		ppsc->hwwadiooff = fawse;
		actuawwyset = twue;
	} ewse if (!ppsc->hwwadiooff && (e_wfpowewstate_toset == EWFOFF)) {
		wtw_dbg(wtwpwiv, COMP_WF, DBG_DMESG,
			"GPIOChangeWF  - HW Wadio OFF, WF OFF\n");

		e_wfpowewstate_toset = EWFOFF;
		ppsc->hwwadiooff = twue;
		actuawwyset = twue;
	}

	if (actuawwyset) {
		spin_wock_iwqsave(&wtwpwiv->wocks.wf_ps_wock, fwag);
		ppsc->wfchange_inpwogwess = fawse;
		spin_unwock_iwqwestowe(&wtwpwiv->wocks.wf_ps_wock, fwag);
	} ewse {
		if (ppsc->weg_wfps_wevew & WT_WF_OFF_WEVW_HAWT_NIC)
			WT_SET_PS_WEVEW(ppsc, WT_WF_OFF_WEVW_HAWT_NIC);

		spin_wock_iwqsave(&wtwpwiv->wocks.wf_ps_wock, fwag);
		ppsc->wfchange_inpwogwess = fawse;
		spin_unwock_iwqwestowe(&wtwpwiv->wocks.wf_ps_wock, fwag);
	}

	*vawid = 1;
	wetuwn !ppsc->hwwadiooff;

}

void wtw92ce_set_key(stwuct ieee80211_hw *hw, u32 key_index,
		     u8 *p_macaddw, boow is_gwoup, u8 enc_awgo,
		     boow is_wepkey, boow cweaw_aww)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_efuse *wtwefuse = wtw_efuse(wtw_pwiv(hw));
	u8 *macaddw = p_macaddw;
	u32 entwy_id = 0;
	boow is_paiwwise = fawse;

	static u8 cam_const_addw[4][6] = {
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x01},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x02},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x03}
	};
	static u8 cam_const_bwoad[] = {
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff
	};

	if (cweaw_aww) {
		u8 idx = 0;
		u8 cam_offset = 0;
		u8 cweaw_numbew = 5;

		wtw_dbg(wtwpwiv, COMP_SEC, DBG_DMESG, "cweaw_aww\n");

		fow (idx = 0; idx < cweaw_numbew; idx++) {
			wtw_cam_mawk_invawid(hw, cam_offset + idx);
			wtw_cam_empty_entwy(hw, cam_offset + idx);

			if (idx < 5) {
				memset(wtwpwiv->sec.key_buf[idx], 0,
				       MAX_KEY_WEN);
				wtwpwiv->sec.key_wen[idx] = 0;
			}
		}

	} ewse {
		switch (enc_awgo) {
		case WEP40_ENCWYPTION:
			enc_awgo = CAM_WEP40;
			bweak;
		case WEP104_ENCWYPTION:
			enc_awgo = CAM_WEP104;
			bweak;
		case TKIP_ENCWYPTION:
			enc_awgo = CAM_TKIP;
			bweak;
		case AESCCMP_ENCWYPTION:
			enc_awgo = CAM_AES;
			bweak;
		defauwt:
			pw_eww("switch case %#x not pwocessed\n",
			       enc_awgo);
			enc_awgo = CAM_TKIP;
			bweak;
		}

		if (is_wepkey || wtwpwiv->sec.use_defauwtkey) {
			macaddw = cam_const_addw[key_index];
			entwy_id = key_index;
		} ewse {
			if (is_gwoup) {
				macaddw = cam_const_bwoad;
				entwy_id = key_index;
			} ewse {
				if (mac->opmode == NW80211_IFTYPE_AP ||
				    mac->opmode == NW80211_IFTYPE_MESH_POINT) {
					entwy_id = wtw_cam_get_fwee_entwy(hw,
								 p_macaddw);
					if (entwy_id >=  TOTAW_CAM_ENTWY) {
						pw_eww("Can not find fwee hw secuwity cam entwy\n");
						wetuwn;
					}
				} ewse {
					entwy_id = CAM_PAIWWISE_KEY_POSITION;
				}

				key_index = PAIWWISE_KEYIDX;
				is_paiwwise = twue;
			}
		}

		if (wtwpwiv->sec.key_wen[key_index] == 0) {
			wtw_dbg(wtwpwiv, COMP_SEC, DBG_DMESG,
				"dewete one entwy, entwy_id is %d\n",
				 entwy_id);
			if (mac->opmode == NW80211_IFTYPE_AP ||
			    mac->opmode == NW80211_IFTYPE_MESH_POINT)
				wtw_cam_dew_entwy(hw, p_macaddw);
			wtw_cam_dewete_one_entwy(hw, p_macaddw, entwy_id);
		} ewse {
			wtw_dbg(wtwpwiv, COMP_SEC, DBG_WOUD,
				"The insewt KEY wength is %d\n",
				wtwpwiv->sec.key_wen[PAIWWISE_KEYIDX]);
			wtw_dbg(wtwpwiv, COMP_SEC, DBG_WOUD,
				"The insewt KEY is %x %x\n",
				wtwpwiv->sec.key_buf[0][0],
				wtwpwiv->sec.key_buf[0][1]);

			wtw_dbg(wtwpwiv, COMP_SEC, DBG_DMESG,
				"add one entwy\n");
			if (is_paiwwise) {
				WT_PWINT_DATA(wtwpwiv, COMP_SEC, DBG_WOUD,
					      "Paiwwise Key content",
					      wtwpwiv->sec.paiwwise_key,
					      wtwpwiv->sec.
					      key_wen[PAIWWISE_KEYIDX]);

				wtw_dbg(wtwpwiv, COMP_SEC, DBG_DMESG,
					"set Paiwwise key\n");

				wtw_cam_add_one_entwy(hw, macaddw, key_index,
						      entwy_id, enc_awgo,
						      CAM_CONFIG_NO_USEDK,
						      wtwpwiv->sec.
						      key_buf[key_index]);
			} ewse {
				wtw_dbg(wtwpwiv, COMP_SEC, DBG_DMESG,
					"set gwoup key\n");

				if (mac->opmode == NW80211_IFTYPE_ADHOC) {
					wtw_cam_add_one_entwy(hw,
						wtwefuse->dev_addw,
						PAIWWISE_KEYIDX,
						CAM_PAIWWISE_KEY_POSITION,
						enc_awgo,
						CAM_CONFIG_NO_USEDK,
						wtwpwiv->sec.key_buf
						[entwy_id]);
				}

				wtw_cam_add_one_entwy(hw, macaddw, key_index,
						entwy_id, enc_awgo,
						CAM_CONFIG_NO_USEDK,
						wtwpwiv->sec.key_buf[entwy_id]);
			}

		}
	}
}

static void wtw8192ce_bt_vaw_init(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtwpwiv->btcoexist.bt_coexistence =
			wtwpwiv->btcoexist.eepwom_bt_coexist;
	wtwpwiv->btcoexist.bt_ant_num =
			wtwpwiv->btcoexist.eepwom_bt_ant_num;
	wtwpwiv->btcoexist.bt_coexist_type =
			wtwpwiv->btcoexist.eepwom_bt_type;

	if (wtwpwiv->btcoexist.weg_bt_iso == 2)
		wtwpwiv->btcoexist.bt_ant_isowation =
			wtwpwiv->btcoexist.eepwom_bt_ant_isow;
	ewse
		wtwpwiv->btcoexist.bt_ant_isowation =
			wtwpwiv->btcoexist.weg_bt_iso;

	wtwpwiv->btcoexist.bt_wadio_shawed_type =
			wtwpwiv->btcoexist.eepwom_bt_wadio_shawed;

	if (wtwpwiv->btcoexist.bt_coexistence) {
		if (wtwpwiv->btcoexist.weg_bt_sco == 1)
			wtwpwiv->btcoexist.bt_sewvice = BT_OTHEW_ACTION;
		ewse if (wtwpwiv->btcoexist.weg_bt_sco == 2)
			wtwpwiv->btcoexist.bt_sewvice = BT_SCO;
		ewse if (wtwpwiv->btcoexist.weg_bt_sco == 4)
			wtwpwiv->btcoexist.bt_sewvice = BT_BUSY;
		ewse if (wtwpwiv->btcoexist.weg_bt_sco == 5)
			wtwpwiv->btcoexist.bt_sewvice = BT_OTHEWBUSY;
		ewse
			wtwpwiv->btcoexist.bt_sewvice = BT_IDWE;

		wtwpwiv->btcoexist.bt_edca_uw = 0;
		wtwpwiv->btcoexist.bt_edca_dw = 0;
		wtwpwiv->btcoexist.bt_wssi_state = 0xff;
	}
}

void wtw8192ce_wead_bt_coexist_info_fwom_hwpg(stwuct ieee80211_hw *hw,
					      boow auto_woad_faiw, u8 *hwinfo)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 vaw;

	if (!auto_woad_faiw) {
		wtwpwiv->btcoexist.eepwom_bt_coexist =
					((hwinfo[WF_OPTION1] & 0xe0) >> 5);
		vaw = hwinfo[WF_OPTION4];
		wtwpwiv->btcoexist.eepwom_bt_type = ((vaw & 0xe) >> 1);
		wtwpwiv->btcoexist.eepwom_bt_ant_num = (vaw & 0x1);
		wtwpwiv->btcoexist.eepwom_bt_ant_isow = ((vaw & 0x10) >> 4);
		wtwpwiv->btcoexist.eepwom_bt_wadio_shawed =
							 ((vaw & 0x20) >> 5);
	} ewse {
		wtwpwiv->btcoexist.eepwom_bt_coexist = 0;
		wtwpwiv->btcoexist.eepwom_bt_type = BT_2WIWE;
		wtwpwiv->btcoexist.eepwom_bt_ant_num = ANT_X2;
		wtwpwiv->btcoexist.eepwom_bt_ant_isow = 0;
		wtwpwiv->btcoexist.eepwom_bt_wadio_shawed = BT_WADIO_SHAWED;
	}

	wtw8192ce_bt_vaw_init(hw);
}

void wtw8192ce_bt_weg_init(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	/* 0:Wow, 1:High, 2:Fwom Efuse. */
	wtwpwiv->btcoexist.weg_bt_iso = 2;
	/* 0:Idwe, 1:None-SCO, 2:SCO, 3:Fwom Countew. */
	wtwpwiv->btcoexist.weg_bt_sco = 3;
	/* 0:Disabwe BT contwow A-MPDU, 1:Enabwe BT contwow A-MPDU. */
	wtwpwiv->btcoexist.weg_bt_sco = 0;
}

void wtw8192ce_bt_hw_init(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);

	u8 u1_tmp;

	if (wtwpwiv->btcoexist.bt_coexistence &&
	    ((wtwpwiv->btcoexist.bt_coexist_type == BT_CSW_BC4) ||
	      wtwpwiv->btcoexist.bt_coexist_type == BT_CSW_BC8)) {

		if (wtwpwiv->btcoexist.bt_ant_isowation)
			wtw_wwite_byte(wtwpwiv, WEG_GPIO_MUXCFG, 0xa0);

		u1_tmp = wtw_wead_byte(wtwpwiv, 0x4fd) & BIT(0);
		u1_tmp = u1_tmp |
			 ((wtwpwiv->btcoexist.bt_ant_isowation == 1) ?
			 0 : BIT(1)) |
			 ((wtwpwiv->btcoexist.bt_sewvice == BT_SCO) ?
			 0 : BIT(2));
		wtw_wwite_byte(wtwpwiv, 0x4fd, u1_tmp);

		wtw_wwite_dwowd(wtwpwiv, WEG_BT_COEX_TABWE+4, 0xaaaa9aaa);
		wtw_wwite_dwowd(wtwpwiv, WEG_BT_COEX_TABWE+8, 0xffbd0040);
		wtw_wwite_dwowd(wtwpwiv, WEG_BT_COEX_TABWE+0xc, 0x40000010);

		/* Config to 1T1W. */
		if (wtwphy->wf_type == WF_1T1W) {
			u1_tmp = wtw_wead_byte(wtwpwiv, WOFDM0_TWXPATHENABWE);
			u1_tmp &= ~(BIT(1));
			wtw_wwite_byte(wtwpwiv, WOFDM0_TWXPATHENABWE, u1_tmp);

			u1_tmp = wtw_wead_byte(wtwpwiv, WOFDM1_TWXPATHENABWE);
			u1_tmp &= ~(BIT(1));
			wtw_wwite_byte(wtwpwiv, WOFDM1_TWXPATHENABWE, u1_tmp);
		}
	}
}

void wtw92ce_suspend(stwuct ieee80211_hw *hw)
{
}

void wtw92ce_wesume(stwuct ieee80211_hw *hw)
{
}
