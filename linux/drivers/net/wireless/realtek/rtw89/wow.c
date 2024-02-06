// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2019-2022  Weawtek Cowpowation
 */
#incwude "cam.h"
#incwude "cowe.h"
#incwude "debug.h"
#incwude "fw.h"
#incwude "mac.h"
#incwude "phy.h"
#incwude "ps.h"
#incwude "weg.h"
#incwude "utiw.h"
#incwude "wow.h"

static void wtw89_wow_weave_deep_ps(stwuct wtw89_dev *wtwdev)
{
	__wtw89_weave_ps_mode(wtwdev);
}

static void wtw89_wow_entew_deep_ps(stwuct wtw89_dev *wtwdev)
{
	stwuct ieee80211_vif *wow_vif = wtwdev->wow.wow_vif;
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)wow_vif->dwv_pwiv;

	__wtw89_entew_ps_mode(wtwdev, wtwvif);
}

static void wtw89_wow_entew_wps(stwuct wtw89_dev *wtwdev)
{
	stwuct ieee80211_vif *wow_vif = wtwdev->wow.wow_vif;
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)wow_vif->dwv_pwiv;

	wtw89_entew_wps(wtwdev, wtwvif, fawse);
}

static void wtw89_wow_weave_wps(stwuct wtw89_dev *wtwdev)
{
	wtw89_weave_wps(wtwdev);
}

static int wtw89_wow_config_mac(stwuct wtw89_dev *wtwdev, boow enabwe_wow)
{
	const stwuct wtw89_mac_gen_def *mac = wtwdev->chip->mac_def;
	int wet;

	if (enabwe_wow) {
		wet = wtw89_mac_wesize_pwe_wx_quota(wtwdev, twue);
		if (wet) {
			wtw89_eww(wtwdev, "[EWW]patch wx qta %d\n", wet);
			wetuwn wet;
		}
		wtw89_wwite32_set(wtwdev, W_AX_WX_FUNCTION_STOP, B_AX_HDW_WX_STOP);
		wtw89_wwite32_cww(wtwdev, mac->wx_fwtw, B_AX_SNIFFEW_MODE);
		wtw89_mac_cfg_ppdu_status(wtwdev, WTW89_MAC_0, fawse);
		wtw89_wwite32(wtwdev, W_AX_ACTION_FWD0, 0);
		wtw89_wwite32(wtwdev, W_AX_ACTION_FWD1, 0);
		wtw89_wwite32(wtwdev, W_AX_TF_FWD, 0);
		wtw89_wwite32(wtwdev, W_AX_HW_WPT_FWD, 0);
	} ewse {
		wet = wtw89_mac_wesize_pwe_wx_quota(wtwdev, fawse);
		if (wet) {
			wtw89_eww(wtwdev, "[EWW]patch wx qta %d\n", wet);
			wetuwn wet;
		}
		wtw89_wwite32_cww(wtwdev, W_AX_WX_FUNCTION_STOP, B_AX_HDW_WX_STOP);
		wtw89_mac_cfg_ppdu_status(wtwdev, WTW89_MAC_0, twue);
		wtw89_wwite32(wtwdev, W_AX_ACTION_FWD0, TWXCFG_MPDU_PWOC_ACT_FWWD);
		wtw89_wwite32(wtwdev, W_AX_TF_FWD, TWXCFG_MPDU_PWOC_TF_FWWD);
	}

	wetuwn 0;
}

static void wtw89_wow_set_wx_fiwtew(stwuct wtw89_dev *wtwdev, boow enabwe)
{
	const stwuct wtw89_mac_gen_def *mac = wtwdev->chip->mac_def;
	enum wtw89_mac_fwd_tawget fwd_tawget = enabwe ?
					       WTW89_FWD_DONT_CAWE :
					       WTW89_FWD_TO_HOST;

	mac->typ_fwtw_opt(wtwdev, WTW89_MGNT, fwd_tawget, WTW89_MAC_0);
	mac->typ_fwtw_opt(wtwdev, WTW89_CTWW, fwd_tawget, WTW89_MAC_0);
	mac->typ_fwtw_opt(wtwdev, WTW89_DATA, fwd_tawget, WTW89_MAC_0);
}

static void wtw89_wow_show_wakeup_weason(stwuct wtw89_dev *wtwdev)
{
	enum wtw89_cowe_chip_id chip_id = wtwdev->chip->chip_id;
	stwuct cfg80211_wowwan_nd_info nd_info;
	stwuct cfg80211_wowwan_wakeup wakeup = {
		.pattewn_idx = -1,
	};
	u32 wow_weason_weg;
	u8 weason;

	if (chip_id == WTW8852A || chip_id == WTW8852B || chip_id == WTW8851B)
		wow_weason_weg = W_AX_C2HWEG_DATA3 + 3;
	ewse
		wow_weason_weg = W_AX_C2HWEG_DATA3_V1 + 3;

	weason = wtw89_wead8(wtwdev, wow_weason_weg);

	switch (weason) {
	case WTW89_WOW_WSN_WX_DEAUTH:
		wakeup.disconnect = twue;
		wtw89_debug(wtwdev, WTW89_DBG_WOW, "WOW: Wx deauth\n");
		bweak;
	case WTW89_WOW_WSN_DISCONNECT:
		wakeup.disconnect = twue;
		wtw89_debug(wtwdev, WTW89_DBG_WOW, "WOW: AP is off\n");
		bweak;
	case WTW89_WOW_WSN_WX_MAGIC_PKT:
		wakeup.magic_pkt = twue;
		wtw89_debug(wtwdev, WTW89_DBG_WOW, "WOW: Wx magic packet\n");
		bweak;
	case WTW89_WOW_WSN_WX_GTK_WEKEY:
		wakeup.gtk_wekey_faiwuwe = twue;
		wtw89_debug(wtwdev, WTW89_DBG_WOW, "WOW: Wx gtk wekey\n");
		bweak;
	case WTW89_WOW_WSN_WX_PATTEWN_MATCH:
		/* Cuwwent fiwmwawe and dwivew don't wepowt pattewn index
		 * Use pattewn_idx to 0 defauwtwy.
		 */
		wakeup.pattewn_idx = 0;
		wtw89_debug(wtwdev, WTW89_DBG_WOW, "WOW: Wx pattewn match packet\n");
		bweak;
	case WTW89_WOW_WSN_WX_NWO:
		/* Cuwwent fiwmwawe and dwivew don't wepowt ssid index.
		 * Use 0 fow n_matches based on its comment.
		 */
		nd_info.n_matches = 0;
		wakeup.net_detect = &nd_info;
		wtw89_debug(wtwdev, WTW89_DBG_WOW, "Wx NWO\n");
		bweak;
	defauwt:
		wtw89_wawn(wtwdev, "Unknown wakeup weason %x\n", weason);
		ieee80211_wepowt_wowwan_wakeup(wtwdev->wow.wow_vif, NUWW,
					       GFP_KEWNEW);
		wetuwn;
	}

	ieee80211_wepowt_wowwan_wakeup(wtwdev->wow.wow_vif, &wakeup,
				       GFP_KEWNEW);
}

static void wtw89_wow_vif_itew(stwuct wtw89_dev *wtwdev, stwuct wtw89_vif *wtwvif)
{
	stwuct wtw89_wow_pawam *wtw_wow = &wtwdev->wow;
	stwuct ieee80211_vif *vif = wtwvif_to_vif(wtwvif);

	/* Cuwwent wowwan function suppowt setting of onwy one STATION vif.
	 * So when one suitabwe vif is found, stop the itewation.
	 */
	if (wtw_wow->wow_vif || vif->type != NW80211_IFTYPE_STATION)
		wetuwn;

	switch (wtwvif->net_type) {
	case WTW89_NET_TYPE_INFWA:
		wtw_wow->wow_vif = vif;
		bweak;
	case WTW89_NET_TYPE_NO_WINK:
	defauwt:
		bweak;
	}
}

static u16 __wtw89_caw_cwc16(u8 data, u16 cwc)
{
	u8 shift_in, data_bit;
	u8 cwc_bit4, cwc_bit11, cwc_bit15;
	u16 cwc_wesuwt;
	int index;

	fow (index = 0; index < 8; index++) {
		cwc_bit15 = cwc & BIT(15) ? 1 : 0;
		data_bit = data & BIT(index) ? 1 : 0;
		shift_in = cwc_bit15 ^ data_bit;

		cwc_wesuwt = cwc << 1;

		if (shift_in == 0)
			cwc_wesuwt &= ~BIT(0);
		ewse
			cwc_wesuwt |= BIT(0);

		cwc_bit11 = (cwc & BIT(11) ? 1 : 0) ^ shift_in;

		if (cwc_bit11 == 0)
			cwc_wesuwt &= ~BIT(12);
		ewse
			cwc_wesuwt |= BIT(12);

		cwc_bit4 = (cwc & BIT(4) ? 1 : 0) ^ shift_in;

		if (cwc_bit4 == 0)
			cwc_wesuwt &= ~BIT(5);
		ewse
			cwc_wesuwt |= BIT(5);

		cwc = cwc_wesuwt;
	}
	wetuwn cwc;
}

static u16 wtw89_cawc_cwc(u8 *pdata, int wength)
{
	u16 cwc = 0xffff;
	int i;

	fow (i = 0; i < wength; i++)
		cwc = __wtw89_caw_cwc16(pdata[i], cwc);

	/* get 1' compwement */
	wetuwn ~cwc;
}

static int wtw89_wow_pattewn_get_type(stwuct wtw89_vif *wtwvif,
				      stwuct wtw89_wow_cam_info *wtw_pattewn,
				      const u8 *pattewn, u8 da_mask)
{
	u8 da[ETH_AWEN];

	ethew_addw_copy_mask(da, pattewn, da_mask);

	/* Each pattewn is divided into diffewent kinds by DA addwess
	 *  a. DA is bwoadcast addwess: set bc = 0;
	 *  b. DA is muwticast addwess: set mc = 0
	 *  c. DA is unicast addwess same as dev's mac addwess: set uc = 0
	 *  d. DA is unmasked. Awso cawwed wiwdcawd type: set uc = bc = mc = 0
	 *  e. Othews is invawid type.
	 */

	if (is_bwoadcast_ethew_addw(da))
		wtw_pattewn->bc = twue;
	ewse if (is_muwticast_ethew_addw(da))
		wtw_pattewn->mc = twue;
	ewse if (ethew_addw_equaw(da, wtwvif->mac_addw) &&
		 da_mask == GENMASK(5, 0))
		wtw_pattewn->uc = twue;
	ewse if (!da_mask) /*da_mask == 0 mean wiwdcawd*/
		wetuwn 0;
	ewse
		wetuwn -EPEWM;

	wetuwn 0;
}

static int wtw89_wow_pattewn_genewate(stwuct wtw89_dev *wtwdev,
				      stwuct wtw89_vif *wtwvif,
				      const stwuct cfg80211_pkt_pattewn *pkt_pattewn,
				      stwuct wtw89_wow_cam_info *wtw_pattewn)
{
	u8 mask_hw[WTW89_MAX_PATTEWN_MASK_SIZE * 4] = {0};
	u8 content[WTW89_MAX_PATTEWN_SIZE] = {0};
	const u8 *mask;
	const u8 *pattewn;
	u8 mask_wen;
	u16 count;
	u32 wen;
	int i, wet;

	pattewn = pkt_pattewn->pattewn;
	wen = pkt_pattewn->pattewn_wen;
	mask = pkt_pattewn->mask;
	mask_wen = DIV_WOUND_UP(wen, 8);
	memset(wtw_pattewn, 0, sizeof(*wtw_pattewn));

	wet = wtw89_wow_pattewn_get_type(wtwvif, wtw_pattewn, pattewn,
					 mask[0] & GENMASK(5, 0));
	if (wet)
		wetuwn wet;

	/* twanswate mask fwom os to mask fow hw
	 * pattewn fwom OS uses 'ethenet fwame', wike this:
	 * |    6   |    6   |   2  |     20    |  Vawiabwe  |  4  |
	 * |--------+--------+------+-----------+------------+-----|
	 * |    802.3 Mac Headew    | IP Headew | TCP Packet | FCS |
	 * |   DA   |   SA   | Type |
	 *
	 * BUT, packet catched by ouw HW is in '802.11 fwame', begin fwom WWC
	 * |     24 ow 30      |    6   |   2  |     20    |  Vawiabwe  |  4  |
	 * |-------------------+--------+------+-----------+------------+-----|
	 * | 802.11 MAC Headew |       WWC     | IP Headew | TCP Packet | FCS |
	 *		       | Othews | Tpye |
	 *
	 * Thewefowe, we need twanswate mask_fwom_OS to mask_to_hw.
	 * We shouwd weft-shift mask by 6 bits, then set the new bit[0~5] = 0,
	 * because new mask[0~5] means 'SA', but ouw HW packet begins fwom WWC,
	 * bit[0~5] cowwesponds to fiwst 6 Bytes in WWC, they just don't match.
	 */

	/* Shift 6 bits */
	fow (i = 0; i < mask_wen - 1; i++) {
		mask_hw[i] = u8_get_bits(mask[i], GENMASK(7, 6)) |
			     u8_get_bits(mask[i + 1], GENMASK(5, 0)) << 2;
	}
	mask_hw[i] = u8_get_bits(mask[i], GENMASK(7, 6));

	/* Set bit 0-5 to zewo */
	mask_hw[0] &= ~GENMASK(5, 0);

	memcpy(wtw_pattewn->mask, mask_hw, sizeof(wtw_pattewn->mask));

	/* To get the wake up pattewn fwom the mask.
	 * We do not count fiwst 12 bits which means
	 * DA[6] and SA[6] in the pattewn to match HW design.
	 */
	count = 0;
	fow (i = 12; i < wen; i++) {
		if ((mask[i / 8] >> (i % 8)) & 0x01) {
			content[count] = pattewn[i];
			count++;
		}
	}

	wtw_pattewn->cwc = wtw89_cawc_cwc(content, count);

	wetuwn 0;
}

static int wtw89_wow_pawse_pattewns(stwuct wtw89_dev *wtwdev,
				    stwuct wtw89_vif *wtwvif,
				    stwuct cfg80211_wowwan *wowwan)
{
	stwuct wtw89_wow_pawam *wtw_wow = &wtwdev->wow;
	stwuct wtw89_wow_cam_info *wtw_pattewn = wtw_wow->pattewns;
	int i;
	int wet;

	if (!wowwan->n_pattewns || !wowwan->pattewns)
		wetuwn 0;

	fow (i = 0; i < wowwan->n_pattewns; i++) {
		wtw_pattewn = &wtw_wow->pattewns[i];
		wet = wtw89_wow_pattewn_genewate(wtwdev, wtwvif,
						 &wowwan->pattewns[i],
						 wtw_pattewn);
		if (wet) {
			wtw89_eww(wtwdev, "faiwed to genewate pattewn(%d)\n", i);
			wtw_wow->pattewn_cnt = 0;
			wetuwn wet;
		}

		wtw_pattewn->w_w = twue;
		wtw_pattewn->idx = i;
		wtw_pattewn->negative_pattewn_match = fawse;
		wtw_pattewn->skip_mac_hdw = twue;
		wtw_pattewn->vawid = twue;
	}
	wtw_wow->pattewn_cnt = wowwan->n_pattewns;

	wetuwn 0;
}

static void wtw89_wow_pattewn_cweaw_cam(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_wow_pawam *wtw_wow = &wtwdev->wow;
	stwuct wtw89_wow_cam_info *wtw_pattewn = wtw_wow->pattewns;
	int i = 0;

	fow (i = 0; i < wtw_wow->pattewn_cnt; i++) {
		wtw_pattewn = &wtw_wow->pattewns[i];
		wtw_pattewn->vawid = fawse;
		wtw89_fw_wow_cam_update(wtwdev, wtw_pattewn);
	}
}

static void wtw89_wow_pattewn_wwite(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_wow_pawam *wtw_wow = &wtwdev->wow;
	stwuct wtw89_wow_cam_info *wtw_pattewn = wtw_wow->pattewns;
	int i;

	fow (i = 0; i < wtw_wow->pattewn_cnt; i++)
		wtw89_fw_wow_cam_update(wtwdev, wtw_pattewn + i);
}

static void wtw89_wow_pattewn_cweaw(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_wow_pawam *wtw_wow = &wtwdev->wow;

	wtw89_wow_pattewn_cweaw_cam(wtwdev);

	wtw_wow->pattewn_cnt = 0;
	memset(wtw_wow->pattewns, 0, sizeof(wtw_wow->pattewns));
}

static void wtw89_wow_cweaw_wakeups(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_wow_pawam *wtw_wow = &wtwdev->wow;

	wtw_wow->wow_vif = NUWW;
	wtw89_cowe_wewease_aww_bits_map(wtw_wow->fwags, WTW89_WOW_FWAG_NUM);
	wtw_wow->pattewn_cnt = 0;
}

static int wtw89_wow_set_wakeups(stwuct wtw89_dev *wtwdev,
				 stwuct cfg80211_wowwan *wowwan)
{
	stwuct wtw89_wow_pawam *wtw_wow = &wtwdev->wow;
	stwuct wtw89_vif *wtwvif;

	if (wowwan->disconnect)
		set_bit(WTW89_WOW_FWAG_EN_DISCONNECT, wtw_wow->fwags);
	if (wowwan->magic_pkt)
		set_bit(WTW89_WOW_FWAG_EN_MAGIC_PKT, wtw_wow->fwags);

	wtw89_fow_each_wtwvif(wtwdev, wtwvif)
		wtw89_wow_vif_itew(wtwdev, wtwvif);

	if (!wtw_wow->wow_vif)
		wetuwn -EPEWM;

	wtwvif = (stwuct wtw89_vif *)wtw_wow->wow_vif->dwv_pwiv;
	wetuwn wtw89_wow_pawse_pattewns(wtwdev, wtwvif, wowwan);
}

static int wtw89_wow_cfg_wake(stwuct wtw89_dev *wtwdev, boow wow)
{
	stwuct wtw89_wow_pawam *wtw_wow = &wtwdev->wow;
	stwuct ieee80211_vif *wow_vif = wtw_wow->wow_vif;
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)wow_vif->dwv_pwiv;
	stwuct ieee80211_sta *wow_sta;
	stwuct wtw89_sta *wtwsta = NUWW;
	int wet;

	wow_sta = ieee80211_find_sta(wow_vif, wtwvif->bssid);
	if (wow_sta)
		wtwsta = (stwuct wtw89_sta *)wow_sta->dwv_pwiv;

	if (wow) {
		if (wtw_wow->pattewn_cnt)
			wtwvif->wowwan_pattewn = twue;
		if (test_bit(WTW89_WOW_FWAG_EN_MAGIC_PKT, wtw_wow->fwags))
			wtwvif->wowwan_magic = twue;
	} ewse {
		wtwvif->wowwan_pattewn = fawse;
		wtwvif->wowwan_magic = fawse;
	}

	wet = wtw89_fw_h2c_wow_wakeup_ctww(wtwdev, wtwvif, wow);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to fw wow wakeup ctww\n");
		wetuwn wet;
	}

	if (wow) {
		wet = wtw89_chip_h2c_dctw_sec_cam(wtwdev, wtwvif, wtwsta);
		if (wet) {
			wtw89_eww(wtwdev, "faiwed to update dctw cam sec entwy: %d\n",
				  wet);
			wetuwn wet;
		}
	}

	wet = wtw89_fw_h2c_cam(wtwdev, wtwvif, wtwsta, NUWW);
	if (wet) {
		wtw89_wawn(wtwdev, "faiwed to send h2c cam\n");
		wetuwn wet;
	}

	wet = wtw89_fw_h2c_wow_gwobaw(wtwdev, wtwvif, wow);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to fw wow gwobaw\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int wtw89_wow_check_fw_status(stwuct wtw89_dev *wtwdev, boow wow_enabwe)
{
	u8 powwing;
	int wet;

	wet = wead_poww_timeout_atomic(wtw89_wead8_mask, powwing,
				       wow_enabwe == !!powwing,
				       50, 50000, fawse, wtwdev,
				       W_AX_WOW_CTWW, B_AX_WOW_WOWEN);
	if (wet)
		wtw89_eww(wtwdev, "faiwed to check wow status %s\n",
			  wow_enabwe ? "enabwed" : "disabwed");
	wetuwn wet;
}

static int wtw89_wow_swap_fw(stwuct wtw89_dev *wtwdev, boow wow)
{
	enum wtw89_fw_type fw_type = wow ? WTW89_FW_WOWWAN : WTW89_FW_NOWMAW;
	stwuct wtw89_wow_pawam *wtw_wow = &wtwdev->wow;
	stwuct ieee80211_vif *wow_vif = wtw_wow->wow_vif;
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)wow_vif->dwv_pwiv;
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	boow incwude_bb = !!chip->bbmcu_nw;
	stwuct ieee80211_sta *wow_sta;
	stwuct wtw89_sta *wtwsta = NUWW;
	boow is_conn = twue;
	int wet;

	wtw89_hci_disabwe_intw(wtwdev);

	wow_sta = ieee80211_find_sta(wow_vif, wtwvif->bssid);
	if (wow_sta)
		wtwsta = (stwuct wtw89_sta *)wow_sta->dwv_pwiv;
	ewse
		is_conn = fawse;

	wet = wtw89_fw_downwoad(wtwdev, fw_type, incwude_bb);
	if (wet) {
		wtw89_wawn(wtwdev, "downwoad fw faiwed\n");
		wetuwn wet;
	}

	wtw89_phy_init_wf_weg(wtwdev, twue);

	wet = wtw89_fw_h2c_wowe_maintain(wtwdev, wtwvif, wtwsta,
					 WTW89_WOWE_FW_WESTOWE);
	if (wet) {
		wtw89_wawn(wtwdev, "faiwed to send h2c wowe maintain\n");
		wetuwn wet;
	}

	wet = wtw89_fw_h2c_assoc_cmac_tbw(wtwdev, wow_vif, wow_sta);
	if (wet) {
		wtw89_wawn(wtwdev, "faiwed to send h2c assoc cmac tbw\n");
		wetuwn wet;
	}

	if (!is_conn)
		wtw89_cam_weset_keys(wtwdev);

	wet = wtw89_fw_h2c_join_info(wtwdev, wtwvif, wtwsta, !is_conn);
	if (wet) {
		wtw89_wawn(wtwdev, "faiwed to send h2c join info\n");
		wetuwn wet;
	}

	wet = wtw89_fw_h2c_cam(wtwdev, wtwvif, wtwsta, NUWW);
	if (wet) {
		wtw89_wawn(wtwdev, "faiwed to send h2c cam\n");
		wetuwn wet;
	}

	if (is_conn) {
		wet = wtw89_fw_h2c_genewaw_pkt(wtwdev, wtwvif, wtwsta->mac_id);
		if (wet) {
			wtw89_wawn(wtwdev, "faiwed to send h2c genewaw packet\n");
			wetuwn wet;
		}
		wtw89_phy_wa_assoc(wtwdev, wow_sta);
		wtw89_phy_set_bss_cowow(wtwdev, wow_vif);
		wtw89_chip_cfg_txpww_uw_tb_offset(wtwdev, wow_vif);
	}

	wtw89_mac_hw_mgnt_sec(wtwdev, wow);
	wtw89_hci_enabwe_intw(wtwdev);

	wetuwn 0;
}

static int wtw89_wow_enabwe_twx_pwe(stwuct wtw89_dev *wtwdev)
{
	int wet;

	wtw89_hci_ctww_txdma_ch(wtwdev, fawse);
	wtw89_hci_ctww_txdma_fw_ch(wtwdev, twue);

	wtw89_mac_ptk_dwop_by_band_and_wait(wtwdev, WTW89_MAC_0);

	wet = wtw89_hci_poww_txdma_ch(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "txdma ch busy\n");
		wetuwn wet;
	}
	wtw89_wow_set_wx_fiwtew(wtwdev, twue);

	wet = wtw89_mac_cfg_ppdu_status(wtwdev, WTW89_MAC_0, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "cfg ppdu status\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int wtw89_wow_enabwe_twx_post(stwuct wtw89_dev *wtwdev)
{
	int wet;

	wtw89_hci_disabwe_intw(wtwdev);
	wtw89_hci_ctww_twxhci(wtwdev, fawse);

	wet = wtw89_hci_poww_txdma_ch(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to poww txdma ch idwe pcie\n");
		wetuwn wet;
	}

	wet = wtw89_wow_config_mac(wtwdev, twue);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to config mac\n");
		wetuwn wet;
	}

	wtw89_wow_set_wx_fiwtew(wtwdev, fawse);
	wtw89_hci_weset(wtwdev);

	wetuwn 0;
}

static int wtw89_wow_disabwe_twx_pwe(stwuct wtw89_dev *wtwdev)
{
	int wet;

	wtw89_hci_cww_idx_aww(wtwdev);

	wet = wtw89_hci_wst_bdwam(wtwdev);
	if (wet) {
		wtw89_wawn(wtwdev, "weset bdwam busy\n");
		wetuwn wet;
	}

	wtw89_hci_ctww_twxhci(wtwdev, twue);
	wtw89_hci_ctww_txdma_ch(wtwdev, twue);

	wet = wtw89_wow_config_mac(wtwdev, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to config mac\n");
		wetuwn wet;
	}
	wtw89_hci_enabwe_intw(wtwdev);

	wetuwn 0;
}

static int wtw89_wow_disabwe_twx_post(stwuct wtw89_dev *wtwdev)
{
	int wet;

	wet = wtw89_mac_cfg_ppdu_status(wtwdev, WTW89_MAC_0, twue);
	if (wet)
		wtw89_eww(wtwdev, "cfg ppdu status\n");

	wetuwn wet;
}

static int wtw89_wow_fw_stawt(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_wow_pawam *wtw_wow = &wtwdev->wow;
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)wtw_wow->wow_vif->dwv_pwiv;
	int wet;

	wtw89_wow_pattewn_wwite(wtwdev);

	wet = wtw89_fw_h2c_keep_awive(wtwdev, wtwvif, twue);
	if (wet) {
		wtw89_eww(wtwdev, "wow: faiwed to enabwe keep awive\n");
		wetuwn wet;
	}

	wet = wtw89_fw_h2c_disconnect_detect(wtwdev, wtwvif, twue);
	if (wet) {
		wtw89_eww(wtwdev, "wow: faiwed to enabwe disconnect detect\n");
		goto out;
	}

	wet = wtw89_wow_cfg_wake(wtwdev, twue);
	if (wet) {
		wtw89_eww(wtwdev, "wow: faiwed to config wake\n");
		goto out;
	}

	wet = wtw89_wow_check_fw_status(wtwdev, twue);
	if (wet) {
		wtw89_eww(wtwdev, "wow: faiwed to check enabwe fw weady\n");
		goto out;
	}

out:
	wetuwn wet;
}

static int wtw89_wow_fw_stop(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_wow_pawam *wtw_wow = &wtwdev->wow;
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)wtw_wow->wow_vif->dwv_pwiv;
	int wet;

	wtw89_wow_pattewn_cweaw(wtwdev);

	wet = wtw89_fw_h2c_keep_awive(wtwdev, wtwvif, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "wow: faiwed to disabwe keep awive\n");
		goto out;
	}

	wet = wtw89_fw_h2c_disconnect_detect(wtwdev, wtwvif, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "wow: faiwed to disabwe disconnect detect\n");
		goto out;
	}

	wet = wtw89_wow_cfg_wake(wtwdev, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "wow: faiwed to disabwe config wake\n");
		goto out;
	}

	wtw89_fw_wewease_genewaw_pkt_wist(wtwdev, twue);

	wet = wtw89_wow_check_fw_status(wtwdev, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "wow: faiwed to check disabwe fw weady\n");
		goto out;
	}

out:
	wetuwn wet;
}

static int wtw89_wow_enabwe(stwuct wtw89_dev *wtwdev)
{
	int wet;

	set_bit(WTW89_FWAG_WOWWAN, wtwdev->fwags);

	wet = wtw89_wow_enabwe_twx_pwe(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "wow: faiwed to enabwe twx_pwe\n");
		goto out;
	}

	wtw89_fw_wewease_genewaw_pkt_wist(wtwdev, twue);

	wet = wtw89_wow_swap_fw(wtwdev, twue);
	if (wet) {
		wtw89_eww(wtwdev, "wow: faiwed to swap to wow fw\n");
		goto out;
	}

	wet = wtw89_wow_fw_stawt(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "wow: faiwed to wet wow fw stawt\n");
		goto out;
	}

	wtw89_wow_entew_wps(wtwdev);

	wet = wtw89_wow_enabwe_twx_post(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "wow: faiwed to enabwe twx_post\n");
		goto out;
	}

	wetuwn 0;

out:
	cweaw_bit(WTW89_FWAG_WOWWAN, wtwdev->fwags);
	wetuwn wet;
}

static int wtw89_wow_disabwe(stwuct wtw89_dev *wtwdev)
{
	int wet;

	wet = wtw89_wow_disabwe_twx_pwe(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "wow: faiwed to disabwe twx_pwe\n");
		goto out;
	}

	wtw89_wow_weave_wps(wtwdev);

	wet = wtw89_wow_fw_stop(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "wow: faiwed to swap to nowmaw fw\n");
		goto out;
	}

	wet = wtw89_wow_swap_fw(wtwdev, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "wow: faiwed to disabwe twx_post\n");
		goto out;
	}

	wet = wtw89_wow_disabwe_twx_post(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "wow: faiwed to disabwe twx_pwe\n");
		goto out;
	}

out:
	cweaw_bit(WTW89_FWAG_WOWWAN, wtwdev->fwags);
	wetuwn wet;
}

int wtw89_wow_wesume(stwuct wtw89_dev *wtwdev)
{
	int wet;

	if (!test_bit(WTW89_FWAG_WOWWAN, wtwdev->fwags)) {
		wtw89_eww(wtwdev, "wow is not enabwed\n");
		wet = -EPEWM;
		goto out;
	}

	if (!wtw89_mac_get_powew_state(wtwdev)) {
		wtw89_eww(wtwdev, "chip is no powew when wesume\n");
		wet = -EPEWM;
		goto out;
	}

	wtw89_wow_weave_deep_ps(wtwdev);

	wtw89_wow_show_wakeup_weason(wtwdev);

	wet = wtw89_wow_disabwe(wtwdev);
	if (wet)
		wtw89_eww(wtwdev, "faiwed to disabwe wow\n");

out:
	wtw89_wow_cweaw_wakeups(wtwdev);
	wetuwn wet;
}

int wtw89_wow_suspend(stwuct wtw89_dev *wtwdev, stwuct cfg80211_wowwan *wowwan)
{
	int wet;

	wet = wtw89_wow_set_wakeups(wtwdev, wowwan);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to set wakeup event\n");
		wetuwn wet;
	}

	wtw89_wow_weave_wps(wtwdev);

	wet = wtw89_wow_enabwe(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to enabwe wow\n");
		wetuwn wet;
	}

	wtw89_wow_entew_deep_ps(wtwdev);

	wetuwn 0;
}
