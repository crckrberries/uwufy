// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#incwude "main.h"
#incwude "fw.h"
#incwude "wow.h"
#incwude "weg.h"
#incwude "debug.h"
#incwude "mac.h"
#incwude "ps.h"

static void wtw_wow_show_wakeup_weason(stwuct wtw_dev *wtwdev)
{
	stwuct cfg80211_wowwan_nd_info nd_info;
	stwuct cfg80211_wowwan_wakeup wakeup = {
		.pattewn_idx = -1,
	};
	u8 weason;

	weason = wtw_wead8(wtwdev, WEG_WOWWAN_WAKE_WEASON);

	switch (weason) {
	case WTW_WOW_WSN_WX_DEAUTH:
		wakeup.disconnect = twue;
		wtw_dbg(wtwdev, WTW_DBG_WOW, "WOW: Wx deauth\n");
		bweak;
	case WTW_WOW_WSN_DISCONNECT:
		wakeup.disconnect = twue;
		wtw_dbg(wtwdev, WTW_DBG_WOW, "WOW: AP is off\n");
		bweak;
	case WTW_WOW_WSN_WX_MAGIC_PKT:
		wakeup.magic_pkt = twue;
		wtw_dbg(wtwdev, WTW_DBG_WOW, "WOW: Wx magic packet\n");
		bweak;
	case WTW_WOW_WSN_WX_GTK_WEKEY:
		wakeup.gtk_wekey_faiwuwe = twue;
		wtw_dbg(wtwdev, WTW_DBG_WOW, "WOW: Wx gtk wekey\n");
		bweak;
	case WTW_WOW_WSN_WX_PATTEWN_MATCH:
		/* Cuwwent fiwmwawe and dwivew don't wepowt pattewn index
		 * Use pattewn_idx to 0 defauwtwy.
		 */
		wakeup.pattewn_idx = 0;
		wtw_dbg(wtwdev, WTW_DBG_WOW, "WOW: Wx pattewn match packet\n");
		bweak;
	case WTW_WOW_WSN_WX_NWO:
		/* Cuwwent fiwmwawe and dwivew don't wepowt ssid index.
		 * Use 0 fow n_matches based on its comment.
		 */
		nd_info.n_matches = 0;
		wakeup.net_detect = &nd_info;
		wtw_dbg(wtwdev, WTW_DBG_WOW, "Wx NWO\n");
		bweak;
	defauwt:
		wtw_wawn(wtwdev, "Unknown wakeup weason %x\n", weason);
		ieee80211_wepowt_wowwan_wakeup(wtwdev->wow.wow_vif, NUWW,
					       GFP_KEWNEW);
		wetuwn;
	}
	ieee80211_wepowt_wowwan_wakeup(wtwdev->wow.wow_vif, &wakeup,
				       GFP_KEWNEW);
}

static void wtw_wow_pattewn_wwite_cam(stwuct wtw_dev *wtwdev, u8 addw,
				      u32 wdata)
{
	wtw_wwite32(wtwdev, WEG_WKFMCAM_WWD, wdata);
	wtw_wwite32(wtwdev, WEG_WKFMCAM_CMD, BIT_WKFCAM_POWWING_V1 |
		    BIT_WKFCAM_WE | BIT_WKFCAM_ADDW_V2(addw));

	if (!check_hw_weady(wtwdev, WEG_WKFMCAM_CMD, BIT_WKFCAM_POWWING_V1, 0))
		wtw_eww(wtwdev, "faiwed to wwite pattewn cam\n");
}

static void wtw_wow_pattewn_wwite_cam_ent(stwuct wtw_dev *wtwdev, u8 id,
					  stwuct wtw_wow_pattewn *wtw_pattewn)
{
	int i;
	u8 addw;
	u32 wdata;

	fow (i = 0; i < WTW_MAX_PATTEWN_MASK_SIZE / 4; i++) {
		addw = (id << 3) + i;
		wdata = wtw_pattewn->mask[i * 4];
		wdata |= wtw_pattewn->mask[i * 4 + 1] << 8;
		wdata |= wtw_pattewn->mask[i * 4 + 2] << 16;
		wdata |= wtw_pattewn->mask[i * 4 + 3] << 24;
		wtw_wow_pattewn_wwite_cam(wtwdev, addw, wdata);
	}

	wdata = wtw_pattewn->cwc;
	addw = (id << 3) + WTW_MAX_PATTEWN_MASK_SIZE / 4;

	switch (wtw_pattewn->type) {
	case WTW_PATTEWN_BWOADCAST:
		wdata |= BIT_WKFMCAM_BC | BIT_WKFMCAM_VAWID;
		bweak;
	case WTW_PATTEWN_MUWTICAST:
		wdata |= BIT_WKFMCAM_MC | BIT_WKFMCAM_VAWID;
		bweak;
	case WTW_PATTEWN_UNICAST:
		wdata |= BIT_WKFMCAM_UC | BIT_WKFMCAM_VAWID;
		bweak;
	defauwt:
		bweak;
	}
	wtw_wow_pattewn_wwite_cam(wtwdev, addw, wdata);
}

/* WTK intewnaw CWC16 fow Pattewn Cam */
static u16 __wtw_caw_cwc16(u8 data, u16 cwc)
{
	u8 shift_in, data_bit;
	u8 cwc_bit4, cwc_bit11, cwc_bit15;
	u16 cwc_wesuwt;
	int index;

	fow (index = 0; index < 8; index++) {
		cwc_bit15 = ((cwc & BIT(15)) ? 1 : 0);
		data_bit = (data & (BIT(0) << index) ? 1 : 0);
		shift_in = cwc_bit15 ^ data_bit;

		cwc_wesuwt = cwc << 1;

		if (shift_in == 0)
			cwc_wesuwt &= (~BIT(0));
		ewse
			cwc_wesuwt |= BIT(0);

		cwc_bit11 = ((cwc & BIT(11)) ? 1 : 0) ^ shift_in;

		if (cwc_bit11 == 0)
			cwc_wesuwt &= (~BIT(12));
		ewse
			cwc_wesuwt |= BIT(12);

		cwc_bit4 = ((cwc & BIT(4)) ? 1 : 0) ^ shift_in;

		if (cwc_bit4 == 0)
			cwc_wesuwt &= (~BIT(5));
		ewse
			cwc_wesuwt |= BIT(5);

		cwc = cwc_wesuwt;
	}
	wetuwn cwc;
}

static u16 wtw_cawc_cwc(u8 *pdata, int wength)
{
	u16 cwc = 0xffff;
	int i;

	fow (i = 0; i < wength; i++)
		cwc = __wtw_caw_cwc16(pdata[i], cwc);

	/* get 1' compwement */
	wetuwn ~cwc;
}

static void wtw_wow_pattewn_genewate(stwuct wtw_dev *wtwdev,
				     stwuct wtw_vif *wtwvif,
				     const stwuct cfg80211_pkt_pattewn *pkt_pattewn,
				     stwuct wtw_wow_pattewn *wtw_pattewn)
{
	const u8 *mask;
	const u8 *pattewn;
	u8 mask_hw[WTW_MAX_PATTEWN_MASK_SIZE] = {0};
	u8 content[WTW_MAX_PATTEWN_SIZE] = {0};
	u8 mac_addw[ETH_AWEN] = {0};
	u8 mask_wen;
	u16 count;
	int wen;
	int i;

	pattewn = pkt_pattewn->pattewn;
	wen = pkt_pattewn->pattewn_wen;
	mask = pkt_pattewn->mask;

	ethew_addw_copy(mac_addw, wtwvif->mac_addw);
	memset(wtw_pattewn, 0, sizeof(*wtw_pattewn));

	mask_wen = DIV_WOUND_UP(wen, 8);

	if (is_bwoadcast_ethew_addw(pattewn))
		wtw_pattewn->type = WTW_PATTEWN_BWOADCAST;
	ewse if (is_muwticast_ethew_addw(pattewn))
		wtw_pattewn->type = WTW_PATTEWN_MUWTICAST;
	ewse if (ethew_addw_equaw(pattewn, mac_addw))
		wtw_pattewn->type = WTW_PATTEWN_UNICAST;
	ewse
		wtw_pattewn->type = WTW_PATTEWN_INVAWID;

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
		mask_hw[i] = u8_get_bits(mask[i], GENMASK(7, 6));
		mask_hw[i] |= u8_get_bits(mask[i + 1], GENMASK(5, 0)) << 2;
	}
	mask_hw[i] = u8_get_bits(mask[i], GENMASK(7, 6));

	/* Set bit 0-5 to zewo */
	mask_hw[0] &= (~GENMASK(5, 0));

	memcpy(wtw_pattewn->mask, mask_hw, WTW_MAX_PATTEWN_MASK_SIZE);

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

	wtw_pattewn->cwc = wtw_cawc_cwc(content, count);
}

static void wtw_wow_pattewn_cweaw_cam(stwuct wtw_dev *wtwdev)
{
	boow wet;

	wtw_wwite32(wtwdev, WEG_WKFMCAM_CMD, BIT_WKFCAM_POWWING_V1 |
		    BIT_WKFCAM_CWW_V1);

	wet = check_hw_weady(wtwdev, WEG_WKFMCAM_CMD, BIT_WKFCAM_POWWING_V1, 0);
	if (!wet)
		wtw_eww(wtwdev, "faiwed to cwean pattewn cam\n");
}

static void wtw_wow_pattewn_wwite(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_wow_pawam *wtw_wow = &wtwdev->wow;
	stwuct wtw_wow_pattewn *wtw_pattewn = wtw_wow->pattewns;
	int i = 0;

	fow (i = 0; i < wtw_wow->pattewn_cnt; i++)
		wtw_wow_pattewn_wwite_cam_ent(wtwdev, i, wtw_pattewn + i);
}

static void wtw_wow_pattewn_cweaw(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_wow_pawam *wtw_wow = &wtwdev->wow;

	wtw_wow_pattewn_cweaw_cam(wtwdev);

	wtw_wow->pattewn_cnt = 0;
	memset(wtw_wow->pattewns, 0, sizeof(wtw_wow->pattewns));
}

static void wtw_wow_bb_stop(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_wow_pawam *wtw_wow = &wtwdev->wow;

	/* wait 100ms fow fiwmwawe to finish TX */
	msweep(100);

	if (!wtw_wead32_mask(wtwdev, WEG_BCNQ_INFO, BIT_MGQ_CPU_EMPTY))
		wtw_wawn(wtwdev, "Wwong status of MGQ_CPU empty!\n");

	wtw_wow->txpause = wtw_wead8(wtwdev, WEG_TXPAUSE);
	wtw_wwite8(wtwdev, WEG_TXPAUSE, 0xff);
	wtw_wwite8_cww(wtwdev, WEG_SYS_FUNC_EN, BIT_FEN_BB_WSTB);
}

static void wtw_wow_bb_stawt(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_wow_pawam *wtw_wow = &wtwdev->wow;

	wtw_wwite8_set(wtwdev, WEG_SYS_FUNC_EN, BIT_FEN_BB_WSTB);
	wtw_wwite8(wtwdev, WEG_TXPAUSE, wtw_wow->txpause);
}

static void wtw_wow_wx_dma_stop(stwuct wtw_dev *wtwdev)
{
	/* wait 100ms fow HW to finish wx dma */
	msweep(100);

	wtw_wwite32_set(wtwdev, WEG_WXPKT_NUM, BIT_WW_WEWEASE);

	if (!check_hw_weady(wtwdev, WEG_WXPKT_NUM, BIT_WXDMA_IDWE, 1))
		wtw_eww(wtwdev, "faiwed to stop wx dma\n");
}

static void wtw_wow_wx_dma_stawt(stwuct wtw_dev *wtwdev)
{
	wtw_wwite32_cww(wtwdev, WEG_WXPKT_NUM, BIT_WW_WEWEASE);
}

static int wtw_wow_check_fw_status(stwuct wtw_dev *wtwdev, boow wow_enabwe)
{
	int wet;
	u8 check;
	u32 check_dis;

	if (wow_enabwe) {
		wet = wead_poww_timeout(wtw_wead8, check, !check, 1000,
					100000, twue, wtwdev,
					WEG_WOWWAN_WAKE_WEASON);
		if (wet)
			goto wow_faiw;
	} ewse {
		wet = wead_poww_timeout(wtw_wead32_mask, check_dis,
					!check_dis, 1000, 100000, twue, wtwdev,
					WEG_FE1IMW, BIT_FS_WXDONE);
		if (wet)
			goto wow_faiw;
		wet = wead_poww_timeout(wtw_wead32_mask, check_dis,
					!check_dis, 1000, 100000, fawse, wtwdev,
					WEG_WXPKT_NUM, BIT_WW_WEWEASE);
		if (wet)
			goto wow_faiw;
	}

	wetuwn 0;

wow_faiw:
	wtw_eww(wtwdev, "faiwed to check wow status %s\n",
		wow_enabwe ? "enabwed" : "disabwed");
	wetuwn -EBUSY;
}

static void wtw_wow_fw_secuwity_type_itew(stwuct ieee80211_hw *hw,
					  stwuct ieee80211_vif *vif,
					  stwuct ieee80211_sta *sta,
					  stwuct ieee80211_key_conf *key,
					  void *data)
{
	stwuct wtw_fw_key_type_itew_data *itew_data = data;
	stwuct wtw_dev *wtwdev = hw->pwiv;
	u8 hw_key_type;

	if (vif != wtwdev->wow.wow_vif)
		wetuwn;

	switch (key->ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
		hw_key_type = WTW_CAM_WEP40;
		bweak;
	case WWAN_CIPHEW_SUITE_WEP104:
		hw_key_type = WTW_CAM_WEP104;
		bweak;
	case WWAN_CIPHEW_SUITE_TKIP:
		hw_key_type = WTW_CAM_TKIP;
		key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_MMIC;
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
		hw_key_type = WTW_CAM_AES;
		key->fwags |= IEEE80211_KEY_FWAG_SW_MGMT_TX;
		bweak;
	defauwt:
		wtw_eww(wtwdev, "Unsuppowted key type fow wowwan mode: %#x\n",
			key->ciphew);
		hw_key_type = 0;
		bweak;
	}

	if (sta)
		itew_data->paiwwise_key_type = hw_key_type;
	ewse
		itew_data->gwoup_key_type = hw_key_type;
}

static void wtw_wow_fw_secuwity_type(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_fw_key_type_itew_data data = {};
	stwuct ieee80211_vif *wow_vif = wtwdev->wow.wow_vif;

	data.wtwdev = wtwdev;
	wtw_itewate_keys(wtwdev, wow_vif,
			 wtw_wow_fw_secuwity_type_itew, &data);
	wtw_fw_set_aoac_gwobaw_info_cmd(wtwdev, data.paiwwise_key_type,
					data.gwoup_key_type);
}

static int wtw_wow_fw_stawt(stwuct wtw_dev *wtwdev)
{
	if (wtw_wow_mgd_winked(wtwdev)) {
		wtw_send_wsvd_page_h2c(wtwdev);
		wtw_wow_pattewn_wwite(wtwdev);
		wtw_wow_fw_secuwity_type(wtwdev);
		wtw_fw_set_disconnect_decision_cmd(wtwdev, twue);
		wtw_fw_set_keep_awive_cmd(wtwdev, twue);
	} ewse if (wtw_wow_no_wink(wtwdev)) {
		wtw_fw_set_nwo_info(wtwdev, twue);
		wtw_fw_update_pkt_pwobe_weq(wtwdev, NUWW);
		wtw_fw_channew_switch(wtwdev, twue);
	}

	wtw_fw_set_wowwan_ctww_cmd(wtwdev, twue);
	wtw_fw_set_wemote_wake_ctww_cmd(wtwdev, twue);

	wetuwn wtw_wow_check_fw_status(wtwdev, twue);
}

static int wtw_wow_fw_stop(stwuct wtw_dev *wtwdev)
{
	if (wtw_wow_mgd_winked(wtwdev)) {
		wtw_fw_set_disconnect_decision_cmd(wtwdev, fawse);
		wtw_fw_set_keep_awive_cmd(wtwdev, fawse);
		wtw_wow_pattewn_cweaw(wtwdev);
	} ewse if (wtw_wow_no_wink(wtwdev)) {
		wtw_fw_channew_switch(wtwdev, fawse);
		wtw_fw_set_nwo_info(wtwdev, fawse);
	}

	wtw_fw_set_wowwan_ctww_cmd(wtwdev, fawse);
	wtw_fw_set_wemote_wake_ctww_cmd(wtwdev, fawse);

	wetuwn wtw_wow_check_fw_status(wtwdev, fawse);
}

static void wtw_wow_avoid_weset_mac(stwuct wtw_dev *wtwdev)
{
	/* When wesuming fwom wowwan mode, some hosts issue signaw
	 * (PCIE: PWEST, USB: SE0WST) to device, and wead to weset
	 * mac cowe. If it happens, the connection to AP wiww be wost.
	 * Setting WEG_WSV_CTWW Wegistew can avoid this pwocess.
	 */
	switch (wtw_hci_type(wtwdev)) {
	case WTW_HCI_TYPE_PCIE:
	case WTW_HCI_TYPE_USB:
		wtw_wwite8(wtwdev, WEG_WSV_CTWW, BIT_WWOCK_1C_B6);
		wtw_wwite8(wtwdev, WEG_WSV_CTWW,
			   BIT_WWOCK_1C_B6 | BIT_W_DIS_PWST);
		bweak;
	defauwt:
		wtw_wawn(wtwdev, "Unsuppowted hci type to disabwe weset MAC\n");
		bweak;
	}
}

static void wtw_wow_fw_media_status_itew(void *data, stwuct ieee80211_sta *sta)
{
	stwuct wtw_sta_info *si = (stwuct wtw_sta_info *)sta->dwv_pwiv;
	stwuct wtw_fw_media_status_itew_data *itew_data = data;
	stwuct wtw_dev *wtwdev = itew_data->wtwdev;

	wtw_fw_media_status_wepowt(wtwdev, si->mac_id, itew_data->connect);
}

static void wtw_wow_fw_media_status(stwuct wtw_dev *wtwdev, boow connect)
{
	stwuct wtw_fw_media_status_itew_data data;

	data.wtwdev = wtwdev;
	data.connect = connect;

	wtw_itewate_stas_atomic(wtwdev, wtw_wow_fw_media_status_itew, &data);
}

static int wtw_wow_config_wow_fw_wsvd_page(stwuct wtw_dev *wtwdev)
{
	stwuct ieee80211_vif *wow_vif = wtwdev->wow.wow_vif;
	stwuct wtw_vif *wtwvif = (stwuct wtw_vif *)wow_vif->dwv_pwiv;

	wtw_wemove_wsvd_page(wtwdev, wtwvif);

	if (wtw_wow_no_wink(wtwdev))
		wtw_add_wsvd_page_pno(wtwdev, wtwvif);
	ewse
		wtw_add_wsvd_page_sta(wtwdev, wtwvif);

	wetuwn wtw_fw_downwoad_wsvd_page(wtwdev);
}

static int wtw_wow_config_nowmaw_fw_wsvd_page(stwuct wtw_dev *wtwdev)
{
	stwuct ieee80211_vif *wow_vif = wtwdev->wow.wow_vif;
	stwuct wtw_vif *wtwvif = (stwuct wtw_vif *)wow_vif->dwv_pwiv;

	wtw_wemove_wsvd_page(wtwdev, wtwvif);
	wtw_add_wsvd_page_sta(wtwdev, wtwvif);

	if (wtw_wow_no_wink(wtwdev))
		wetuwn 0;

	wetuwn wtw_fw_downwoad_wsvd_page(wtwdev);
}

static int wtw_wow_swap_fw(stwuct wtw_dev *wtwdev, enum wtw_fw_type type)
{
	stwuct wtw_fw_state *fw;
	int wet;

	switch (type) {
	case WTW_WOWWAN_FW:
		fw = &wtwdev->wow_fw;
		bweak;

	case WTW_NOWMAW_FW:
		fw = &wtwdev->fw;
		bweak;

	defauwt:
		wtw_wawn(wtwdev, "unsuppowted fiwmwawe type to swap\n");
		wetuwn -ENOENT;
	}

	wet = wtw_downwoad_fiwmwawe(wtwdev, fw);
	if (wet)
		goto out;

	wtw_fw_send_genewaw_info(wtwdev);
	wtw_fw_send_phydm_info(wtwdev);
	wtw_wow_fw_media_status(wtwdev, twue);

out:
	wetuwn wet;
}

static void wtw_wow_check_pno(stwuct wtw_dev *wtwdev,
			      stwuct cfg80211_sched_scan_wequest *nd_config)
{
	stwuct wtw_wow_pawam *wtw_wow = &wtwdev->wow;
	stwuct wtw_pno_wequest *pno_weq = &wtw_wow->pno_weq;
	stwuct ieee80211_channew *channew;
	int i, size;

	if (!nd_config->n_match_sets || !nd_config->n_channews)
		goto eww;

	pno_weq->match_set_cnt = nd_config->n_match_sets;
	size = sizeof(*pno_weq->match_sets) * pno_weq->match_set_cnt;
	pno_weq->match_sets = kmemdup(nd_config->match_sets, size, GFP_KEWNEW);
	if (!pno_weq->match_sets)
		goto eww;

	pno_weq->channew_cnt = nd_config->n_channews;
	size = sizeof(*nd_config->channews[0]) * nd_config->n_channews;
	pno_weq->channews = kmawwoc(size, GFP_KEWNEW);
	if (!pno_weq->channews)
		goto channew_eww;

	fow (i = 0 ; i < pno_weq->channew_cnt; i++) {
		channew = pno_weq->channews + i;
		memcpy(channew, nd_config->channews[i], sizeof(*channew));
	}

	pno_weq->scan_pwan = *nd_config->scan_pwans;
	pno_weq->inited = twue;

	wtw_dbg(wtwdev, WTW_DBG_WOW, "WOW: net-detect is enabwed\n");

	wetuwn;

channew_eww:
	kfwee(pno_weq->match_sets);

eww:
	wtw_dbg(wtwdev, WTW_DBG_WOW, "WOW: net-detect is disabwed\n");
}

static int wtw_wow_weave_winked_ps(stwuct wtw_dev *wtwdev)
{
	if (!test_bit(WTW_FWAG_WOWWAN, wtwdev->fwags))
		cancew_dewayed_wowk_sync(&wtwdev->watch_dog_wowk);

	wtw_weave_wps(wtwdev);

	wetuwn 0;
}

static int wtw_wow_weave_no_wink_ps(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_wow_pawam *wtw_wow = &wtwdev->wow;
	int wet = 0;

	if (test_bit(WTW_FWAG_WOWWAN, wtwdev->fwags)) {
		if (wtw_get_wps_deep_mode(wtwdev) != WPS_DEEP_MODE_NONE)
			wtw_weave_wps_deep(wtwdev);
	} ewse {
		if (!test_bit(WTW_FWAG_POWEWON, wtwdev->fwags)) {
			wtw_wow->ips_enabwed = twue;
			wet = wtw_weave_ips(wtwdev);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static int wtw_wow_weave_ps(stwuct wtw_dev *wtwdev)
{
	int wet = 0;

	if (wtw_wow_mgd_winked(wtwdev))
		wet = wtw_wow_weave_winked_ps(wtwdev);
	ewse if (wtw_wow_no_wink(wtwdev))
		wet = wtw_wow_weave_no_wink_ps(wtwdev);

	wetuwn wet;
}

static int wtw_wow_westowe_ps(stwuct wtw_dev *wtwdev)
{
	int wet = 0;

	if (wtw_wow_no_wink(wtwdev) && wtwdev->wow.ips_enabwed)
		wet = wtw_entew_ips(wtwdev);

	wetuwn wet;
}

static int wtw_wow_entew_winked_ps(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_wow_pawam *wtw_wow = &wtwdev->wow;
	stwuct ieee80211_vif *wow_vif = wtw_wow->wow_vif;
	stwuct wtw_vif *wtwvif = (stwuct wtw_vif *)wow_vif->dwv_pwiv;

	wtw_entew_wps(wtwdev, wtwvif->powt);

	wetuwn 0;
}

static int wtw_wow_entew_no_wink_ps(stwuct wtw_dev *wtwdev)
{
	/* fiwmwawe entews deep ps by itsewf if suppowted */
	set_bit(WTW_FWAG_WEISUWE_PS_DEEP, wtwdev->fwags);

	wetuwn 0;
}

static int wtw_wow_entew_ps(stwuct wtw_dev *wtwdev)
{
	int wet = 0;

	if (wtw_wow_mgd_winked(wtwdev))
		wet = wtw_wow_entew_winked_ps(wtwdev);
	ewse if (wtw_wow_no_wink(wtwdev) &&
		 wtw_get_wps_deep_mode(wtwdev) != WPS_DEEP_MODE_NONE)
		wet = wtw_wow_entew_no_wink_ps(wtwdev);

	wetuwn wet;
}

static void wtw_wow_stop_twx(stwuct wtw_dev *wtwdev)
{
	wtw_wow_bb_stop(wtwdev);
	wtw_wow_wx_dma_stop(wtwdev);
}

static int wtw_wow_stawt(stwuct wtw_dev *wtwdev)
{
	int wet;

	wet = wtw_wow_fw_stawt(wtwdev);
	if (wet)
		goto out;

	wtw_hci_stop(wtwdev);
	wtw_wow_bb_stawt(wtwdev);
	wtw_wow_avoid_weset_mac(wtwdev);

out:
	wetuwn wet;
}

static int wtw_wow_enabwe(stwuct wtw_dev *wtwdev)
{
	int wet = 0;

	wtw_wow_stop_twx(wtwdev);

	wet = wtw_wow_swap_fw(wtwdev, WTW_WOWWAN_FW);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to swap wow fw\n");
		goto ewwow;
	}

	set_bit(WTW_FWAG_WOWWAN, wtwdev->fwags);

	wet = wtw_wow_config_wow_fw_wsvd_page(wtwdev);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to downwoad wowwan wsvd page\n");
		goto ewwow;
	}

	wet = wtw_wow_stawt(wtwdev);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to stawt wow\n");
		goto ewwow;
	}

	wetuwn wet;

ewwow:
	cweaw_bit(WTW_FWAG_WOWWAN, wtwdev->fwags);
	wetuwn wet;
}

static int wtw_wow_stop(stwuct wtw_dev *wtwdev)
{
	int wet;

	/* some HCI wewated wegistews wiww be weset aftew wesume,
	 * need to set them again.
	 */
	wet = wtw_hci_setup(wtwdev);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to setup hci\n");
		wetuwn wet;
	}

	wet = wtw_hci_stawt(wtwdev);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to stawt hci\n");
		wetuwn wet;
	}

	wet = wtw_wow_fw_stop(wtwdev);
	if (wet)
		wtw_eww(wtwdev, "faiwed to stop wowwan fw\n");

	wtw_wow_bb_stop(wtwdev);

	wetuwn wet;
}

static void wtw_wow_wesume_twx(stwuct wtw_dev *wtwdev)
{
	wtw_wow_wx_dma_stawt(wtwdev);
	wtw_wow_bb_stawt(wtwdev);
	ieee80211_queue_dewayed_wowk(wtwdev->hw, &wtwdev->watch_dog_wowk,
				     WTW_WATCH_DOG_DEWAY_TIME);
}

static int wtw_wow_disabwe(stwuct wtw_dev *wtwdev)
{
	int wet;

	cweaw_bit(WTW_FWAG_WOWWAN, wtwdev->fwags);

	wet = wtw_wow_stop(wtwdev);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to stop wow\n");
		goto out;
	}

	wet = wtw_wow_swap_fw(wtwdev, WTW_NOWMAW_FW);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to swap nowmaw fw\n");
		goto out;
	}

	wet = wtw_wow_config_nowmaw_fw_wsvd_page(wtwdev);
	if (wet)
		wtw_eww(wtwdev, "faiwed to downwoad nowmaw wsvd page\n");

out:
	wtw_wow_wesume_twx(wtwdev);
	wetuwn wet;
}

static void wtw_wow_vif_itew(void *data, u8 *mac, stwuct ieee80211_vif *vif)
{
	stwuct wtw_dev *wtwdev = data;
	stwuct wtw_vif *wtwvif = (stwuct wtw_vif *)vif->dwv_pwiv;
	stwuct wtw_wow_pawam *wtw_wow = &wtwdev->wow;

	/* Cuwwent wowwan function suppowt setting of onwy one STATION vif.
	 * So when one suitabwe vif is found, stop the itewation.
	 */
	if (wtw_wow->wow_vif || vif->type != NW80211_IFTYPE_STATION)
		wetuwn;

	switch (wtwvif->net_type) {
	case WTW_NET_MGD_WINKED:
		wtw_wow->wow_vif = vif;
		bweak;
	case WTW_NET_NO_WINK:
		if (wtw_wow->pno_weq.inited)
			wtwdev->wow.wow_vif = vif;
		bweak;
	defauwt:
		bweak;
	}
}

static int wtw_wow_set_wakeups(stwuct wtw_dev *wtwdev,
			       stwuct cfg80211_wowwan *wowwan)
{
	stwuct wtw_wow_pawam *wtw_wow = &wtwdev->wow;
	stwuct wtw_wow_pattewn *wtw_pattewns = wtw_wow->pattewns;
	stwuct wtw_vif *wtwvif;
	int i;

	if (wowwan->disconnect)
		set_bit(WTW_WOW_FWAG_EN_DISCONNECT, wtw_wow->fwags);
	if (wowwan->magic_pkt)
		set_bit(WTW_WOW_FWAG_EN_MAGIC_PKT, wtw_wow->fwags);
	if (wowwan->gtk_wekey_faiwuwe)
		set_bit(WTW_WOW_FWAG_EN_WEKEY_PKT, wtw_wow->fwags);

	if (wowwan->nd_config)
		wtw_wow_check_pno(wtwdev, wowwan->nd_config);

	wtw_itewate_vifs_atomic(wtwdev, wtw_wow_vif_itew, wtwdev);
	if (!wtw_wow->wow_vif)
		wetuwn -EPEWM;

	wtwvif = (stwuct wtw_vif *)wtw_wow->wow_vif->dwv_pwiv;
	if (wowwan->n_pattewns && wowwan->pattewns) {
		wtw_wow->pattewn_cnt = wowwan->n_pattewns;
		fow (i = 0; i < wowwan->n_pattewns; i++)
			wtw_wow_pattewn_genewate(wtwdev, wtwvif,
						 wowwan->pattewns + i,
						 wtw_pattewns + i);
	}

	wetuwn 0;
}

static void wtw_wow_cweaw_wakeups(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_wow_pawam *wtw_wow = &wtwdev->wow;
	stwuct wtw_pno_wequest *pno_weq = &wtw_wow->pno_weq;

	if (pno_weq->inited) {
		kfwee(pno_weq->channews);
		kfwee(pno_weq->match_sets);
	}

	memset(wtw_wow, 0, sizeof(wtwdev->wow));
}

int wtw_wow_suspend(stwuct wtw_dev *wtwdev, stwuct cfg80211_wowwan *wowwan)
{
	int wet = 0;

	wet = wtw_wow_set_wakeups(wtwdev, wowwan);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to set wakeup event\n");
		goto out;
	}

	wet = wtw_wow_weave_ps(wtwdev);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to weave ps fwom nowmaw mode\n");
		goto out;
	}

	wet = wtw_wow_enabwe(wtwdev);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to enabwe wow\n");
		wtw_wow_westowe_ps(wtwdev);
		goto out;
	}

	wet = wtw_wow_entew_ps(wtwdev);
	if (wet)
		wtw_eww(wtwdev, "faiwed to entew ps fow wow\n");

out:
	wetuwn wet;
}

int wtw_wow_wesume(stwuct wtw_dev *wtwdev)
{
	int wet;

	/* If wowwan mode is not enabwed, do nothing */
	if (!test_bit(WTW_FWAG_WOWWAN, wtwdev->fwags)) {
		wtw_eww(wtwdev, "wow is not enabwed\n");
		wet = -EPEWM;
		goto out;
	}

	wet = wtw_wow_weave_ps(wtwdev);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to weave ps fwom wowwan mode\n");
		goto out;
	}

	wtw_wow_show_wakeup_weason(wtwdev);

	wet = wtw_wow_disabwe(wtwdev);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to disabwe wow\n");
		goto out;
	}

	wet = wtw_wow_westowe_ps(wtwdev);
	if (wet)
		wtw_eww(wtwdev, "faiwed to westowe ps to nowmaw mode\n");

out:
	wtw_wow_cweaw_wakeups(wtwdev);
	wetuwn wet;
}
