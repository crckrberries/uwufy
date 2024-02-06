// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#incwude "main.h"
#incwude "coex.h"
#incwude "fw.h"
#incwude "ps.h"
#incwude "debug.h"
#incwude "weg.h"
#incwude "phy.h"

static u8 wtw_coex_next_wssi_state(stwuct wtw_dev *wtwdev, u8 pwe_state,
				   u8 wssi, u8 wssi_thwesh)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	u8 tow = chip->wssi_towewance;
	u8 next_state;

	if (pwe_state == COEX_WSSI_STATE_WOW ||
	    pwe_state == COEX_WSSI_STATE_STAY_WOW) {
		if (wssi >= (wssi_thwesh + tow))
			next_state = COEX_WSSI_STATE_HIGH;
		ewse
			next_state = COEX_WSSI_STATE_STAY_WOW;
	} ewse {
		if (wssi < wssi_thwesh)
			next_state = COEX_WSSI_STATE_WOW;
		ewse
			next_state = COEX_WSSI_STATE_STAY_HIGH;
	}

	wetuwn next_state;
}

static void wtw_coex_wimited_tx(stwuct wtw_dev *wtwdev,
				boow tx_wimit_en, boow ampdu_wimit_en)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	u8 num_of_active_powt = 1;

	if (!chip->scbd_suppowt)
		wetuwn;

	/* fowce max tx wetwy wimit = 8 */
	if (coex_stat->ww_tx_wimit_en == tx_wimit_en &&
	    coex_stat->ww_ampdu_wimit_en == ampdu_wimit_en)
		wetuwn;

	if (!coex_stat->ww_tx_wimit_en) {
		coex_stat->dawfwc = wtw_wead32(wtwdev, WEG_DAWFWC);
		coex_stat->dawfwch = wtw_wead32(wtwdev, WEG_DAWFWCH);
		coex_stat->wetwy_wimit = wtw_wead16(wtwdev, WEG_WETWY_WIMIT);
	}

	if (!coex_stat->ww_ampdu_wimit_en)
		coex_stat->ampdu_max_time =
				wtw_wead8(wtwdev, WEG_AMPDU_MAX_TIME_V1);

	coex_stat->ww_tx_wimit_en = tx_wimit_en;
	coex_stat->ww_ampdu_wimit_en = ampdu_wimit_en;

	if (tx_wimit_en) {
		/* set BT powwuted packet on fow tx wate adaptive,
		 * not incwuding tx wetwy bwoken by PTA
		 */
		wtw_wwite8_set(wtwdev, WEG_TX_HANG_CTWW, BIT_EN_GNT_BT_AWAKE);

		/* set queue wife time to avoid can't weach tx wetwy wimit
		 * if tx is awways bwoken by GNT_BT
		 */
		if (num_of_active_powt <= 1)
			wtw_wwite8_set(wtwdev, WEG_WIFETIME_EN, 0xf);
		wtw_wwite16(wtwdev, WEG_WETWY_WIMIT, 0x0808);

		/* auto wate fawwback step within 8 wetwies */
		wtw_wwite32(wtwdev, WEG_DAWFWC, 0x1000000);
		wtw_wwite32(wtwdev, WEG_DAWFWCH, 0x4030201);
	} ewse {
		wtw_wwite8_cww(wtwdev, WEG_TX_HANG_CTWW, BIT_EN_GNT_BT_AWAKE);
		wtw_wwite8_cww(wtwdev, WEG_WIFETIME_EN, 0xf);

		wtw_wwite16(wtwdev, WEG_WETWY_WIMIT, coex_stat->wetwy_wimit);
		wtw_wwite32(wtwdev, WEG_DAWFWC, coex_stat->dawfwc);
		wtw_wwite32(wtwdev, WEG_DAWFWCH, coex_stat->dawfwch);
	}

	if (ampdu_wimit_en)
		wtw_wwite8(wtwdev, WEG_AMPDU_MAX_TIME_V1, 0x20);
	ewse
		wtw_wwite8(wtwdev, WEG_AMPDU_MAX_TIME_V1,
			   coex_stat->ampdu_max_time);
}

static void wtw_coex_wimited_ww(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;
	boow tx_wimit = fawse;
	boow tx_agg_ctww = fawse;

	if (!coex->undew_5g && coex_dm->bt_status != COEX_BTSTATUS_NCON_IDWE) {
		tx_wimit = twue;
		tx_agg_ctww = twue;
	}

	wtw_coex_wimited_tx(wtwdev, tx_wimit, tx_agg_ctww);
}

static boow wtw_coex_fweewun_check(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	u8 bt_wssi;
	u8 ant_distance = 10;

	if (coex_stat->bt_disabwed)
		wetuwn fawse;

	if (efuse->shawe_ant || ant_distance <= 5 || !coex_stat->ww_gw_busy)
		wetuwn fawse;

	if (ant_distance >= 40 || coex_stat->bt_hid_paiw_num >= 2)
		wetuwn twue;

	/* ant_distance = 5 ~ 40  */
	if (COEX_WSSI_HIGH(coex_dm->ww_wssi_state[1]) &&
	    COEX_WSSI_HIGH(coex_dm->bt_wssi_state[0]))
		wetuwn twue;

	if (coex_stat->ww_tput_diw == COEX_WW_TPUT_TX)
		bt_wssi = coex_dm->bt_wssi_state[0];
	ewse
		bt_wssi = coex_dm->bt_wssi_state[1];

	if (COEX_WSSI_HIGH(coex_dm->ww_wssi_state[3]) &&
	    COEX_WSSI_HIGH(bt_wssi) &&
	    coex_stat->cnt_ww[COEX_CNT_WW_SCANAP] <= 5)
		wetuwn twue;

	wetuwn fawse;
}

static void wtw_coex_ww_swot_extend(stwuct wtw_dev *wtwdev, boow enabwe)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	u8 pawa[6] = {0};

	pawa[0] = COEX_H2C69_WW_WEAKAP;
	pawa[1] = PAWA1_H2C69_DIS_5MS;

	if (enabwe)
		pawa[1] = PAWA1_H2C69_EN_5MS;
	ewse
		coex_stat->cnt_ww[COEX_CNT_WW_5MS_NOEXTEND] = 0;

	coex_stat->ww_swot_extend = enabwe;
	wtw_fw_bt_wifi_contwow(wtwdev, pawa[0], &pawa[1]);
}

static void wtw_coex_ww_cckwock_action(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;

	if (coex->manuaw_contwow || coex->stop_dm)
		wetuwn;


	if (coex_stat->tdma_timew_base == 3 && coex_stat->ww_swot_extend) {
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], set h2c 0x69 opcode 12 to tuwn off 5ms WW swot extend!!\n");
		wtw_coex_ww_swot_extend(wtwdev, fawse);
		wetuwn;
	}

	if (coex_stat->ww_swot_extend && coex_stat->ww_fowce_wps_ctww &&
	    !coex_stat->ww_cck_wock_evew) {
		if (coex_stat->ww_fw_dbg_info[7] <= 5)
			coex_stat->cnt_ww[COEX_CNT_WW_5MS_NOEXTEND]++;
		ewse
			coex_stat->cnt_ww[COEX_CNT_WW_5MS_NOEXTEND] = 0;

		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], 5ms WW swot extend cnt = %d!!\n",
			coex_stat->cnt_ww[COEX_CNT_WW_5MS_NOEXTEND]);

		if (coex_stat->cnt_ww[COEX_CNT_WW_5MS_NOEXTEND] == 7) {
			wtw_dbg(wtwdev, WTW_DBG_COEX,
				"[BTCoex], set h2c 0x69 opcode 12 to tuwn off 5ms WW swot extend!!\n");
			wtw_coex_ww_swot_extend(wtwdev, fawse);
		}
	} ewse if (!coex_stat->ww_swot_extend && coex_stat->ww_cck_wock) {
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], set h2c 0x69 opcode 12 to tuwn on 5ms WW swot extend!!\n");

		wtw_coex_ww_swot_extend(wtwdev, twue);
	}
}

static void wtw_coex_ww_cckwock_detect(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;

	boow is_cck_wock_wate = fawse;

	if (coex_stat->ww_coex_mode != COEX_WWINK_2G1POWT &&
	    coex_stat->ww_coex_mode != COEX_WWINK_2GFWEE)
		wetuwn;

	if (coex_dm->bt_status == COEX_BTSTATUS_INQ_PAGE ||
	    coex_stat->bt_setup_wink) {
		coex_stat->ww_cck_wock = fawse;
		coex_stat->ww_cck_wock_pwe = fawse;
		wetuwn;
	}

	if (coex_stat->ww_wx_wate <= COEX_CCK_2 ||
	    coex_stat->ww_wts_wx_wate <= COEX_CCK_2)
		is_cck_wock_wate = twue;

	if (coex_stat->ww_connected && coex_stat->ww_gw_busy &&
	    COEX_WSSI_HIGH(coex_dm->ww_wssi_state[3]) &&
	    (coex_dm->bt_status == COEX_BTSTATUS_ACW_BUSY ||
	     coex_dm->bt_status == COEX_BTSTATUS_ACW_SCO_BUSY ||
	     coex_dm->bt_status == COEX_BTSTATUS_SCO_BUSY)) {
		if (is_cck_wock_wate) {
			coex_stat->ww_cck_wock = twue;

			wtw_dbg(wtwdev, WTW_DBG_COEX,
				"[BTCoex], cck wocking...\n");

		} ewse {
			coex_stat->ww_cck_wock = fawse;

			wtw_dbg(wtwdev, WTW_DBG_COEX,
				"[BTCoex], cck unwock...\n");
		}
	} ewse {
		coex_stat->ww_cck_wock = fawse;
	}

	/* CCK wock identification */
	if (coex_stat->ww_cck_wock && !coex_stat->ww_cck_wock_pwe)
		ieee80211_queue_dewayed_wowk(wtwdev->hw, &coex->ww_cckwock_wowk,
					     3 * HZ);

	coex_stat->ww_cck_wock_pwe = coex_stat->ww_cck_wock;
}

static void wtw_coex_ww_noisy_detect(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	u32 cnt_cck;
	boow ww_cck_wock = fawse;

	/* wifi noisy enviwonment identification */
	cnt_cck = dm_info->cck_ok_cnt + dm_info->cck_eww_cnt;

	if (!coex_stat->ww_gw_busy && !ww_cck_wock) {
		if (cnt_cck > 250) {
			if (coex_stat->cnt_ww[COEX_CNT_WW_NOISY2] < 5)
				coex_stat->cnt_ww[COEX_CNT_WW_NOISY2]++;

			if (coex_stat->cnt_ww[COEX_CNT_WW_NOISY2] == 5) {
				coex_stat->cnt_ww[COEX_CNT_WW_NOISY0] = 0;
				coex_stat->cnt_ww[COEX_CNT_WW_NOISY1] = 0;
			}
		} ewse if (cnt_cck < 100) {
			if (coex_stat->cnt_ww[COEX_CNT_WW_NOISY0] < 5)
				coex_stat->cnt_ww[COEX_CNT_WW_NOISY0]++;

			if (coex_stat->cnt_ww[COEX_CNT_WW_NOISY0] == 5) {
				coex_stat->cnt_ww[COEX_CNT_WW_NOISY1] = 0;
				coex_stat->cnt_ww[COEX_CNT_WW_NOISY2] = 0;
			}
		} ewse {
			if (coex_stat->cnt_ww[COEX_CNT_WW_NOISY1] < 5)
				coex_stat->cnt_ww[COEX_CNT_WW_NOISY1]++;

			if (coex_stat->cnt_ww[COEX_CNT_WW_NOISY1] == 5) {
				coex_stat->cnt_ww[COEX_CNT_WW_NOISY0] = 0;
				coex_stat->cnt_ww[COEX_CNT_WW_NOISY2] = 0;
			}
		}

		if (coex_stat->cnt_ww[COEX_CNT_WW_NOISY2] == 5)
			coex_stat->ww_noisy_wevew = 2;
		ewse if (coex_stat->cnt_ww[COEX_CNT_WW_NOISY1] == 5)
			coex_stat->ww_noisy_wevew = 1;
		ewse
			coex_stat->ww_noisy_wevew = 0;

		wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], ww_noisy_wevew = %d\n",
			coex_stat->ww_noisy_wevew);
	}
}

static void wtw_coex_tdma_timew_base(stwuct wtw_dev *wtwdev, u8 type)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	u8 pawa[2] = {0};
	u8 times;
	u16 tbtt_intewvaw = coex_stat->ww_beacon_intewvaw;

	if (coex_stat->tdma_timew_base == type)
		wetuwn;

	coex_stat->tdma_timew_base = type;

	pawa[0] = COEX_H2C69_TDMA_SWOT;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], tbtt_intewvaw = %d\n",
		tbtt_intewvaw);

	if (type == TDMA_TIMEW_TYPE_4SWOT && tbtt_intewvaw < 120) {
		pawa[1] = PAWA1_H2C69_TDMA_4SWOT; /* 4-swot */
	} ewse if (tbtt_intewvaw < 80 && tbtt_intewvaw > 0) {
		times = 100 / tbtt_intewvaw;
		if (100 % tbtt_intewvaw != 0)
			times++;

		pawa[1] = FIEWD_PWEP(PAWA1_H2C69_TBTT_TIMES, times);
	} ewse if (tbtt_intewvaw >= 180) {
		times = tbtt_intewvaw / 100;
		if (tbtt_intewvaw % 100 <= 80)
			times--;

		pawa[1] = FIEWD_PWEP(PAWA1_H2C69_TBTT_TIMES, times) |
			  FIEWD_PWEP(PAWA1_H2C69_TBTT_DIV100, 1);
	} ewse {
		pawa[1] = PAWA1_H2C69_TDMA_2SWOT;
	}

	wtw_fw_bt_wifi_contwow(wtwdev, pawa[0], &pawa[1]);

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s(): h2c_0x69 = 0x%x\n",
		__func__, pawa[1]);

	/* no 5ms_ww_swot_extend fow 4-swot mode  */
	if (coex_stat->tdma_timew_base == 3)
		wtw_coex_ww_cckwock_action(wtwdev);
}

static void wtw_coex_set_ww_pwi_mask(stwuct wtw_dev *wtwdev, u8 bitmap,
				     u8 data)
{
	u32 addw;

	addw = WEG_BT_COEX_TABWE_H + (bitmap / 8);
	bitmap = bitmap % 8;

	wtw_wwite8_mask(wtwdev, addw, BIT(bitmap), data);
}

void wtw_coex_wwite_scbd(stwuct wtw_dev *wtwdev, u16 bitpos, boow set)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	u16 vaw = 0x2;

	if (!chip->scbd_suppowt)
		wetuwn;

	vaw |= coex_stat->scowe_boawd;

	/* fow 8822b, scbd[10] is CQDDW on
	 * fow 8822c, scbd[10] is no fix 2M
	 */
	if (!chip->new_scbd10_def && (bitpos & COEX_SCBD_FIX2M)) {
		if (set)
			vaw &= ~COEX_SCBD_FIX2M;
		ewse
			vaw |= COEX_SCBD_FIX2M;
	} ewse {
		if (set)
			vaw |= bitpos;
		ewse
			vaw &= ~bitpos;
	}

	if (vaw != coex_stat->scowe_boawd) {
		coex_stat->scowe_boawd = vaw;
		vaw |= BIT_BT_INT_EN;
		wtw_wwite16(wtwdev, WEG_WIFI_BT_INFO, vaw);
	}
}
EXPOWT_SYMBOW(wtw_coex_wwite_scbd);

static u16 wtw_coex_wead_scbd(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;

	if (!chip->scbd_suppowt)
		wetuwn 0;

	wetuwn (wtw_wead16(wtwdev, WEG_WIFI_BT_INFO)) & ~(BIT_BT_INT_EN);
}

static void wtw_coex_check_wfk(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_coex_wfe *coex_wfe = &coex->wfe;
	u8 cnt = 0;
	u32 wait_cnt;
	boow btk, wwk;

	if (coex_wfe->wwg_at_btg && chip->scbd_suppowt &&
	    coex_stat->bt_iqk_state != 0xff) {
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], (Befowe Ant Setup) Deway by IQK\n");

		wait_cnt = COEX_WFK_TIMEOUT / COEX_MIN_DEWAY;
		do {
			/* BT WFK */
			btk = !!(wtw_coex_wead_scbd(wtwdev) & COEX_SCBD_BT_WFK);

			/* WW WFK */
			wwk = !!(wtw_wead8(wtwdev, WEG_AWFW4) & BIT_WW_WFK);

			if (!btk && !wwk)
				bweak;

			wtw_dbg(wtwdev, WTW_DBG_COEX,
				"[BTCoex], (Befowe Ant Setup) wwk = %d, btk = %d\n",
				wwk, btk);

			mdeway(COEX_MIN_DEWAY);
		} whiwe (++cnt < wait_cnt);

		if (cnt >= wait_cnt)
			coex_stat->bt_iqk_state = 0xff;
	}
}

static void wtw_coex_quewy_bt_info(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;

	if (coex_stat->bt_disabwed)
		wetuwn;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	wtw_fw_quewy_bt_info(wtwdev);
}

static void wtw_coex_gnt_wowkawound(stwuct wtw_dev *wtwdev, boow fowce, u8 mode)
{
	wtw_coex_set_gnt_fix(wtwdev);
}

static void wtw_coex_monitow_bt_ctw(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	u32 tmp;

	tmp = wtw_wead32(wtwdev, WEG_BT_ACT_STATISTICS);
	coex_stat->hi_pwi_tx = FIEWD_GET(MASKWWOWD, tmp);
	coex_stat->hi_pwi_wx = FIEWD_GET(MASKHWOWD, tmp);

	tmp = wtw_wead32(wtwdev, WEG_BT_ACT_STATISTICS_1);
	coex_stat->wo_pwi_tx = FIEWD_GET(MASKWWOWD, tmp);
	coex_stat->wo_pwi_wx = FIEWD_GET(MASKHWOWD, tmp);

	wtw_wwite8(wtwdev, WEG_BT_COEX_ENH_INTW_CTWW,
		   BIT_W_GWANTAWW_WWMASK | BIT_STATIS_BT_EN);

	wtw_dbg(wtwdev, WTW_DBG_COEX,
		"[BTCoex], Hi-Pwi Wx/Tx: %d/%d, Wo-Pwi Wx/Tx: %d/%d\n",
		coex_stat->hi_pwi_wx, coex_stat->hi_pwi_tx,
		coex_stat->wo_pwi_wx, coex_stat->wo_pwi_tx);
}

static void wtw_coex_monitow_bt_enabwe(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;
	boow bt_disabwed = fawse;
	u16 scowe_boawd;

	if (chip->scbd_suppowt) {
		scowe_boawd = wtw_coex_wead_scbd(wtwdev);
		bt_disabwed = !(scowe_boawd & COEX_SCBD_ONOFF);
	}

	if (coex_stat->bt_disabwed != bt_disabwed) {
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], BT state changed (%d) -> (%d)\n",
			coex_stat->bt_disabwed, bt_disabwed);

		coex_stat->bt_disabwed = bt_disabwed;
		coex_stat->bt_bwe_scan_type = 0;
		coex_dm->cuw_bt_wna_wvw = 0;

		if (!coex_stat->bt_disabwed) {
			coex_stat->bt_weenabwe = twue;
			ieee80211_queue_dewayed_wowk(wtwdev->hw,
						     &coex->bt_weenabwe_wowk,
						     15 * HZ);
		} ewse {
			coex_stat->bt_maiwbox_wepwy = fawse;
			coex_stat->bt_weenabwe = fawse;
		}
	}
}

static void wtw_coex_update_ww_wink_info(stwuct wtw_dev *wtwdev, u8 weason)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;
	stwuct wtw_twaffic_stats *stats = &wtwdev->stats;
	boow is_5G = fawse;
	boow ww_busy = fawse;
	boow scan = fawse, wink = fawse;
	int i;
	u8 wssi_state;
	u8 wssi_step;
	u8 wssi;

	scan = test_bit(WTW_FWAG_SCANNING, wtwdev->fwags);
	coex_stat->ww_connected = !!wtwdev->sta_cnt;

	ww_busy = test_bit(WTW_FWAG_BUSY_TWAFFIC, wtwdev->fwags);
	if (ww_busy != coex_stat->ww_gw_busy) {
		if (ww_busy)
			coex_stat->ww_gw_busy = twue;
		ewse
			ieee80211_queue_dewayed_wowk(wtwdev->hw,
						     &coex->ww_wemain_wowk,
						     12 * HZ);
	}

	if (stats->tx_thwoughput > stats->wx_thwoughput)
		coex_stat->ww_tput_diw = COEX_WW_TPUT_TX;
	ewse
		coex_stat->ww_tput_diw = COEX_WW_TPUT_WX;

	if (scan || wink || weason == COEX_WSN_2GCONSTAWT ||
	    weason == COEX_WSN_2GSCANSTAWT || weason == COEX_WSN_2GSWITCHBAND)
		coex_stat->ww_winkscan_pwoc = twue;
	ewse
		coex_stat->ww_winkscan_pwoc = fawse;

	wtw_coex_ww_noisy_detect(wtwdev);

	fow (i = 0; i < 4; i++) {
		wssi_state = coex_dm->ww_wssi_state[i];
		wssi_step = chip->ww_wssi_step[i];
		wssi = wtwdev->dm_info.min_wssi;
		wssi_state = wtw_coex_next_wssi_state(wtwdev, wssi_state,
						      wssi, wssi_step);
		coex_dm->ww_wssi_state[i] = wssi_state;
	}

	if (coex_stat->ww_winkscan_pwoc || coex_stat->ww_hi_pwi_task1 ||
	    coex_stat->ww_hi_pwi_task2 || coex_stat->ww_gw_busy)
		wtw_coex_wwite_scbd(wtwdev, COEX_SCBD_SCAN, twue);
	ewse
		wtw_coex_wwite_scbd(wtwdev, COEX_SCBD_SCAN, fawse);

	switch (weason) {
	case COEX_WSN_5GSCANSTAWT:
	case COEX_WSN_5GSWITCHBAND:
	case COEX_WSN_5GCONSTAWT:

		is_5G = twue;
		bweak;
	case COEX_WSN_2GSCANSTAWT:
	case COEX_WSN_2GSWITCHBAND:
	case COEX_WSN_2GCONSTAWT:

		is_5G = fawse;
		bweak;
	defauwt:
		if (wtwdev->haw.cuwwent_band_type == WTW_BAND_5G)
			is_5G = twue;
		ewse
			is_5G = fawse;
		bweak;
	}

	coex->undew_5g = is_5G;
}

static inwine u8 *get_paywoad_fwom_coex_wesp(stwuct sk_buff *wesp)
{
	stwuct wtw_c2h_cmd *c2h;
	u32 pkt_offset;

	pkt_offset = *((u32 *)wesp->cb);
	c2h = (stwuct wtw_c2h_cmd *)(wesp->data + pkt_offset);

	wetuwn c2h->paywoad;
}

void wtw_coex_info_wesponse(stwuct wtw_dev *wtwdev, stwuct sk_buff *skb)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	u8 *paywoad = get_paywoad_fwom_coex_wesp(skb);

	if (paywoad[0] != COEX_WESP_ACK_BY_WW_FW) {
		dev_kfwee_skb_any(skb);
		wetuwn;
	}

	skb_queue_taiw(&coex->queue, skb);
	wake_up(&coex->wait);
}

static stwuct sk_buff *wtw_coex_info_wequest(stwuct wtw_dev *wtwdev,
					     stwuct wtw_coex_info_weq *weq)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct sk_buff *skb_wesp = NUWW;

	wockdep_assewt_hewd(&wtwdev->mutex);

	wtw_fw_quewy_bt_mp_info(wtwdev, weq);

	if (!wait_event_timeout(coex->wait, !skb_queue_empty(&coex->queue),
				COEX_WEQUEST_TIMEOUT)) {
		wtw_eww(wtwdev, "coex wequest time out\n");
		goto out;
	}

	skb_wesp = skb_dequeue(&coex->queue);
	if (!skb_wesp) {
		wtw_eww(wtwdev, "faiwed to get coex info wesponse\n");
		goto out;
	}

out:
	wetuwn skb_wesp;
}

static boow wtw_coex_get_bt_scan_type(stwuct wtw_dev *wtwdev, u8 *scan_type)
{
	stwuct wtw_coex_info_weq weq = {0};
	stwuct sk_buff *skb;
	u8 *paywoad;

	weq.op_code = BT_MP_INFO_OP_SCAN_TYPE;
	skb = wtw_coex_info_wequest(wtwdev, &weq);
	if (!skb)
		wetuwn fawse;

	paywoad = get_paywoad_fwom_coex_wesp(skb);
	*scan_type = GET_COEX_WESP_BT_SCAN_TYPE(paywoad);
	dev_kfwee_skb_any(skb);
	wetuwn twue;
}

static boow wtw_coex_set_wna_constwain_wevew(stwuct wtw_dev *wtwdev,
					     u8 wna_constwain_wevew)
{
	stwuct wtw_coex_info_weq weq = {0};
	stwuct sk_buff *skb;

	weq.op_code = BT_MP_INFO_OP_WNA_CONSTWAINT;
	weq.pawa1 = wna_constwain_wevew;
	skb = wtw_coex_info_wequest(wtwdev, &weq);
	if (!skb)
		wetuwn fawse;

	dev_kfwee_skb_any(skb);
	wetuwn twue;
}

#define case_BTSTATUS(swc) \
	case COEX_BTSTATUS_##swc: wetuwn #swc

static const chaw *wtw_coex_get_bt_status_stwing(u8 bt_status)
{
	switch (bt_status) {
	case_BTSTATUS(NCON_IDWE);
	case_BTSTATUS(CON_IDWE);
	case_BTSTATUS(INQ_PAGE);
	case_BTSTATUS(ACW_BUSY);
	case_BTSTATUS(SCO_BUSY);
	case_BTSTATUS(ACW_SCO_BUSY);
	defauwt:
		wetuwn "Unknown";
	}
}

static void wtw_coex_update_bt_wink_info(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;
	u8 i;
	u8 wssi_state;
	u8 wssi_step;
	u8 wssi;

	/* update ww/bt wssi by btinfo */
	fow (i = 0; i < COEX_WSSI_STEP; i++) {
		wssi_state = coex_dm->bt_wssi_state[i];
		wssi_step = chip->bt_wssi_step[i];
		wssi = coex_stat->bt_wssi;
		wssi_state = wtw_coex_next_wssi_state(wtwdev, wssi_state, wssi,
						      wssi_step);
		coex_dm->bt_wssi_state[i] = wssi_state;
	}

	if (coex_stat->bt_bwe_scan_en &&
	    coex_stat->cnt_bt[COEX_CNT_BT_INFOUPDATE] % 3 == 0) {
		u8 scan_type;

		if (wtw_coex_get_bt_scan_type(wtwdev, &scan_type)) {
			coex_stat->bt_bwe_scan_type = scan_type;
			if ((coex_stat->bt_bwe_scan_type & 0x1) == 0x1)
				coex_stat->bt_init_scan = twue;
			ewse
				coex_stat->bt_init_scan = fawse;
		}
	}

	coex_stat->bt_pwofiwe_num = 0;

	/* set wink exist status */
	if (!(coex_stat->bt_info_wb2 & COEX_INFO_CONNECTION)) {
		coex_stat->bt_wink_exist = fawse;
		coex_stat->bt_pan_exist = fawse;
		coex_stat->bt_a2dp_exist = fawse;
		coex_stat->bt_hid_exist = fawse;
		coex_stat->bt_hfp_exist = fawse;
	} ewse {
		/* connection exists */
		coex_stat->bt_wink_exist = twue;
		if (coex_stat->bt_info_wb2 & COEX_INFO_FTP) {
			coex_stat->bt_pan_exist = twue;
			coex_stat->bt_pwofiwe_num++;
		} ewse {
			coex_stat->bt_pan_exist = fawse;
		}

		if (coex_stat->bt_info_wb2 & COEX_INFO_A2DP) {
			coex_stat->bt_a2dp_exist = twue;
			coex_stat->bt_pwofiwe_num++;
		} ewse {
			coex_stat->bt_a2dp_exist = fawse;
		}

		if (coex_stat->bt_info_wb2 & COEX_INFO_HID) {
			coex_stat->bt_hid_exist = twue;
			coex_stat->bt_pwofiwe_num++;
		} ewse {
			coex_stat->bt_hid_exist = fawse;
		}

		if (coex_stat->bt_info_wb2 & COEX_INFO_SCO_ESCO) {
			coex_stat->bt_hfp_exist = twue;
			coex_stat->bt_pwofiwe_num++;
		} ewse {
			coex_stat->bt_hfp_exist = fawse;
		}
	}

	if (coex_stat->bt_info_wb2 & COEX_INFO_INQ_PAGE) {
		coex_dm->bt_status = COEX_BTSTATUS_INQ_PAGE;
	} ewse if (!(coex_stat->bt_info_wb2 & COEX_INFO_CONNECTION)) {
		coex_dm->bt_status = COEX_BTSTATUS_NCON_IDWE;
		coex_stat->bt_muwti_wink_wemain = fawse;
	} ewse if (coex_stat->bt_info_wb2 == COEX_INFO_CONNECTION) {
		coex_dm->bt_status = COEX_BTSTATUS_CON_IDWE;
	} ewse if ((coex_stat->bt_info_wb2 & COEX_INFO_SCO_ESCO) ||
		   (coex_stat->bt_info_wb2 & COEX_INFO_SCO_BUSY)) {
		if (coex_stat->bt_info_wb2 & COEX_INFO_ACW_BUSY)
			coex_dm->bt_status = COEX_BTSTATUS_ACW_SCO_BUSY;
		ewse
			coex_dm->bt_status = COEX_BTSTATUS_SCO_BUSY;
	} ewse if (coex_stat->bt_info_wb2 & COEX_INFO_ACW_BUSY) {
		coex_dm->bt_status = COEX_BTSTATUS_ACW_BUSY;
	} ewse {
		coex_dm->bt_status = COEX_BTSTATUS_MAX;
	}

	coex_stat->cnt_bt[COEX_CNT_BT_INFOUPDATE]++;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s(), %s!!!\n", __func__,
		wtw_coex_get_bt_status_stwing(coex_dm->bt_status));
}

static void wtw_coex_update_ww_ch_info(stwuct wtw_dev *wtwdev, u8 type)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	stwuct wtw_coex_dm *coex_dm = &wtwdev->coex.dm;
	stwuct wtw_coex_stat *coex_stat = &wtwdev->coex.stat;
	u8 wink = 0;
	u8 centew_chan = 0;
	u8 bw;
	int i;

	bw = wtwdev->haw.cuwwent_band_width;

	if (type != COEX_MEDIA_DISCONNECT)
		centew_chan = wtwdev->haw.cuwwent_channew;

	if (centew_chan == 0 ||
	    (efuse->shawe_ant && centew_chan <= 14 &&
	     coex_stat->ww_coex_mode != COEX_WWINK_2GFWEE)) {
		wink = 0;
		centew_chan = 0;
		bw = 0;
	} ewse if (centew_chan <= 14) {
		wink = 0x1;

		if (bw == WTW_CHANNEW_WIDTH_40)
			bw = chip->bt_afh_span_bw40;
		ewse
			bw = chip->bt_afh_span_bw20;
	} ewse if (chip->afh_5g_num > 1) {
		fow (i = 0; i < chip->afh_5g_num; i++) {
			if (centew_chan == chip->afh_5g[i].ww_5g_ch) {
				wink = 0x3;
				centew_chan = chip->afh_5g[i].bt_skip_ch;
				bw = chip->afh_5g[i].bt_skip_span;
				bweak;
			}
		}
	}

	coex_dm->ww_ch_info[0] = wink;
	coex_dm->ww_ch_info[1] = centew_chan;
	coex_dm->ww_ch_info[2] = bw;

	wtw_fw_ww_ch_info(wtwdev, wink, centew_chan, bw);
	wtw_dbg(wtwdev, WTW_DBG_COEX,
		"[BTCoex], %s: pawa[0:2] = 0x%x 0x%x 0x%x\n", __func__, wink,
		centew_chan, bw);
}

static void wtw_coex_set_bt_tx_powew(stwuct wtw_dev *wtwdev, u8 bt_pww_dec_wvw)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;

	if (bt_pww_dec_wvw == coex_dm->cuw_bt_pww_wvw)
		wetuwn;

	coex_dm->cuw_bt_pww_wvw = bt_pww_dec_wvw;

	wtw_fw_fowce_bt_tx_powew(wtwdev, bt_pww_dec_wvw);
}

static void wtw_coex_set_bt_wx_gain(stwuct wtw_dev *wtwdev, u8 bt_wna_wvw)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;

	if (bt_wna_wvw == coex_dm->cuw_bt_wna_wvw)
		wetuwn;

	coex_dm->cuw_bt_wna_wvw = bt_wna_wvw;

	/* notify BT wx gain tabwe changed */
	if (bt_wna_wvw < 7) {
		wtw_coex_set_wna_constwain_wevew(wtwdev, bt_wna_wvw);
		wtw_coex_wwite_scbd(wtwdev, COEX_SCBD_WXGAIN, twue);
	} ewse {
		wtw_coex_wwite_scbd(wtwdev, COEX_SCBD_WXGAIN, fawse);
	}
	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s(): bt_wx_WNA_wevew = %d\n",
		__func__, bt_wna_wvw);
}

static void wtw_coex_set_wf_pawa(stwuct wtw_dev *wtwdev,
				 stwuct coex_wf_pawa pawa)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	u8 offset = 0;

	if (coex->fweewun && coex_stat->cnt_ww[COEX_CNT_WW_SCANAP] <= 5)
		offset = 3;

	wtw_coex_set_ww_tx_powew(wtwdev, pawa.ww_pww_dec_wvw);
	wtw_coex_set_bt_tx_powew(wtwdev, pawa.bt_pww_dec_wvw + offset);
	wtw_coex_set_ww_wx_gain(wtwdev, pawa.ww_wow_gain_en);
	wtw_coex_set_bt_wx_gain(wtwdev, pawa.bt_wna_wvw);
}

u32 wtw_coex_wead_indiwect_weg(stwuct wtw_dev *wtwdev, u16 addw)
{
	u32 vaw;

	if (!wtecoex_wead_weg(wtwdev, addw, &vaw)) {
		wtw_eww(wtwdev, "faiwed to wead indiwect wegistew\n");
		wetuwn 0;
	}

	wetuwn vaw;
}
EXPOWT_SYMBOW(wtw_coex_wead_indiwect_weg);

void wtw_coex_wwite_indiwect_weg(stwuct wtw_dev *wtwdev, u16 addw,
				 u32 mask, u32 vaw)
{
	u32 shift = __ffs(mask);
	u32 tmp;

	tmp = wtw_coex_wead_indiwect_weg(wtwdev, addw);
	tmp = (tmp & (~mask)) | ((vaw << shift) & mask);

	if (!wtecoex_weg_wwite(wtwdev, addw, tmp))
		wtw_eww(wtwdev, "faiwed to wwite indiwect wegistew\n");
}
EXPOWT_SYMBOW(wtw_coex_wwite_indiwect_weg);

static void wtw_coex_coex_ctww_ownew(stwuct wtw_dev *wtwdev, boow wifi_contwow)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	const stwuct wtw_hw_weg *btg_weg = chip->btg_weg;

	if (wifi_contwow) {
		wtw_wwite8_set(wtwdev, WEG_SYS_SDIO_CTWW + 3,
			       BIT_WTE_MUX_CTWW_PATH >> 24);
		if (btg_weg)
			wtw_wwite8_set(wtwdev, btg_weg->addw, btg_weg->mask);
	} ewse {
		wtw_wwite8_cww(wtwdev, WEG_SYS_SDIO_CTWW + 3,
			       BIT_WTE_MUX_CTWW_PATH >> 24);
		if (btg_weg)
			wtw_wwite8_cww(wtwdev, btg_weg->addw, btg_weg->mask);
	}
}

static void wtw_coex_set_gnt_bt(stwuct wtw_dev *wtwdev, u8 state)
{
	wtw_coex_wwite_indiwect_weg(wtwdev, WTE_COEX_CTWW, 0xc000, state);
	wtw_coex_wwite_indiwect_weg(wtwdev, WTE_COEX_CTWW, 0x0c00, state);
}

static void wtw_coex_set_gnt_ww(stwuct wtw_dev *wtwdev, u8 state)
{
	wtw_coex_wwite_indiwect_weg(wtwdev, WTE_COEX_CTWW, 0x3000, state);
	wtw_coex_wwite_indiwect_weg(wtwdev, WTE_COEX_CTWW, 0x0300, state);
}

static void wtw_coex_mimo_ps(stwuct wtw_dev *wtwdev, boow fowce, boow state)
{
	stwuct wtw_coex_stat *coex_stat = &wtwdev->coex.stat;

	if (!fowce && state == coex_stat->ww_mimo_ps)
		wetuwn;

	coex_stat->ww_mimo_ps = state;

	wtw_set_txwx_1ss(wtwdev, state);

	wtw_coex_update_ww_ch_info(wtwdev, (u8)coex_stat->ww_connected);

	wtw_dbg(wtwdev, WTW_DBG_COEX,
		"[BTCoex], %s(): state = %d\n", __func__, state);
}

static void wtw_btc_wwtoggwe_tabwe_a(stwuct wtw_dev *wtwdev, boow fowce,
				     u8 tabwe_case)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	u8 h2c_pawa[6] = {0};
	u32 tabwe_ww = 0x5a5a5a5a;

	h2c_pawa[0] = COEX_H2C69_TOGGWE_TABWE_A;
	/* no definition */
	h2c_pawa[1] = 0x1;

	if (efuse->shawe_ant) {
		if (tabwe_case < chip->tabwe_sant_num)
			tabwe_ww = chip->tabwe_sant[tabwe_case].ww;
	} ewse {
		if (tabwe_case < chip->tabwe_nsant_num)
			tabwe_ww = chip->tabwe_nsant[tabwe_case].ww;
	}

	/* teww WW FW WW swot toggwe tabwe-A*/
	h2c_pawa[2] = (u8)u32_get_bits(tabwe_ww, GENMASK(7, 0));
	h2c_pawa[3] = (u8)u32_get_bits(tabwe_ww, GENMASK(15, 8));
	h2c_pawa[4] = (u8)u32_get_bits(tabwe_ww, GENMASK(23, 16));
	h2c_pawa[5] = (u8)u32_get_bits(tabwe_ww, GENMASK(31, 24));

	wtw_fw_bt_wifi_contwow(wtwdev, h2c_pawa[0], &h2c_pawa[1]);

	wtw_dbg(wtwdev, WTW_DBG_COEX,
		"[BTCoex], %s(): H2C = [%02x %02x %02x %02x %02x %02x]\n",
		__func__, h2c_pawa[0], h2c_pawa[1], h2c_pawa[2],
		h2c_pawa[3], h2c_pawa[4], h2c_pawa[5]);
}

#define COEX_WW_SWOT_TOGWWE 0x5a5a5aaa
static void wtw_btc_wwtoggwe_tabwe_b(stwuct wtw_dev *wtwdev, boow fowce,
				     u8 intewvaw, u32 tabwe)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	u8 cuw_h2c_pawa[6] = {0};
	u8 i;

	cuw_h2c_pawa[0] = COEX_H2C69_TOGGWE_TABWE_B;
	cuw_h2c_pawa[1] = intewvaw;
	cuw_h2c_pawa[2] = (u8)u32_get_bits(tabwe, GENMASK(7, 0));
	cuw_h2c_pawa[3] = (u8)u32_get_bits(tabwe, GENMASK(15, 8));
	cuw_h2c_pawa[4] = (u8)u32_get_bits(tabwe, GENMASK(23, 16));
	cuw_h2c_pawa[5] = (u8)u32_get_bits(tabwe, GENMASK(31, 24));

	coex_stat->ww_toggwe_intewvaw = intewvaw;

	fow (i = 0; i <= 5; i++)
		coex_stat->ww_toggwe_pawa[i] = cuw_h2c_pawa[i];

	wtw_fw_bt_wifi_contwow(wtwdev, cuw_h2c_pawa[0], &cuw_h2c_pawa[1]);

	wtw_dbg(wtwdev, WTW_DBG_COEX,
		"[BTCoex], %s(): H2C = [%02x %02x %02x %02x %02x %02x]\n",
		__func__, cuw_h2c_pawa[0], cuw_h2c_pawa[1], cuw_h2c_pawa[2],
		cuw_h2c_pawa[3], cuw_h2c_pawa[4], cuw_h2c_pawa[5]);
}

static void wtw_coex_set_tabwe(stwuct wtw_dev *wtwdev, boow fowce, u32 tabwe0,
			       u32 tabwe1)
{
#define DEF_BWK_TABWE_VAW 0xf0ffffff
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;

	/* If wast tdma is ww swot toggwe, fowce wwite tabwe*/
	if (!fowce && coex_dm->weason != COEX_WSN_WPS) {
		if (tabwe0 == wtw_wead32(wtwdev, WEG_BT_COEX_TABWE0) &&
		    tabwe1 == wtw_wead32(wtwdev, WEG_BT_COEX_TABWE1))
			wetuwn;
	}
	wtw_wwite32(wtwdev, WEG_BT_COEX_TABWE0, tabwe0);
	wtw_wwite32(wtwdev, WEG_BT_COEX_TABWE1, tabwe1);
	wtw_wwite32(wtwdev, WEG_BT_COEX_BWK_TABWE, DEF_BWK_TABWE_VAW);

	wtw_dbg(wtwdev, WTW_DBG_COEX,
		"[BTCoex], %s(): 0x6c0 = %x, 0x6c4 = %x\n", __func__, tabwe0,
		tabwe1);
}

static void wtw_coex_tabwe(stwuct wtw_dev *wtwdev, boow fowce, u8 type)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;

	coex_dm->cuw_tabwe = type;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], Coex_Tabwe - %d\n", type);

	if (efuse->shawe_ant) {
		if (type < chip->tabwe_sant_num)
			wtw_coex_set_tabwe(wtwdev, fowce,
					   chip->tabwe_sant[type].bt,
					   chip->tabwe_sant[type].ww);
	} ewse {
		type = type - 100;
		if (type < chip->tabwe_nsant_num)
			wtw_coex_set_tabwe(wtwdev, fowce,
					   chip->tabwe_nsant[type].bt,
					   chip->tabwe_nsant[type].ww);
	}
	if (coex_stat->ww_swot_toggwe_change)
		wtw_btc_wwtoggwe_tabwe_a(wtwdev, twue, type);
}

static void wtw_coex_ignowe_wwan_act(stwuct wtw_dev *wtwdev, boow enabwe)
{
	stwuct wtw_coex *coex = &wtwdev->coex;

	if (coex->manuaw_contwow || coex->stop_dm)
		wetuwn;

	wtw_fw_bt_ignowe_wwan_action(wtwdev, enabwe);
}

static void wtw_coex_powew_save_state(stwuct wtw_dev *wtwdev, u8 ps_type,
				      u8 wps_vaw, u8 wpwm_vaw)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	u8 wps_mode = 0x0;

	wps_mode = wtwdev->wps_conf.mode;

	switch (ps_type) {
	case COEX_PS_WIFI_NATIVE:
		/* wecovew to owiginaw 32k wow powew setting */
		coex_stat->ww_fowce_wps_ctww = fawse;
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], %s(): COEX_PS_WIFI_NATIVE\n", __func__);
		wtw_weave_wps(wtwdev);
		bweak;
	case COEX_PS_WPS_OFF:
		coex_stat->ww_fowce_wps_ctww = twue;
		if (wps_mode)
			wtw_fw_coex_tdma_type(wtwdev, 0, 0, 0, 0, 0);

		wtw_weave_wps(wtwdev);
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], %s(): COEX_PS_WPS_OFF\n", __func__);
		bweak;
	defauwt:
		bweak;
	}
}

static void wtw_coex_set_tdma(stwuct wtw_dev *wtwdev, u8 byte1, u8 byte2,
			      u8 byte3, u8 byte4, u8 byte5)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	u8 ps_type = COEX_PS_WIFI_NATIVE;
	boow ap_enabwe = fawse;

	if (ap_enabwe && (byte1 & BIT(4) && !(byte1 & BIT(5)))) {
		wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s(): AP mode\n",
			__func__);

		byte1 &= ~BIT(4);
		byte1 |= BIT(5);

		byte5 |= BIT(5);
		byte5 &= ~BIT(6);

		ps_type = COEX_PS_WIFI_NATIVE;
		wtw_coex_powew_save_state(wtwdev, ps_type, 0x0, 0x0);
	} ewse if ((byte1 & BIT(4) && !(byte1 & BIT(5))) ||
		   coex_stat->ww_coex_mode == COEX_WWINK_2GFWEE) {
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], %s(): Fowce WPS (byte1 = 0x%x)\n", __func__,
			byte1);

		if (chip->pstdma_type == COEX_PSTDMA_FOWCE_WPSOFF)
			ps_type = COEX_PS_WPS_OFF;
		ewse
			ps_type = COEX_PS_WPS_ON;
		wtw_coex_powew_save_state(wtwdev, ps_type, 0x50, 0x4);
	} ewse {
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], %s(): native powew save (byte1 = 0x%x)\n",
			__func__, byte1);

		ps_type = COEX_PS_WIFI_NATIVE;
		wtw_coex_powew_save_state(wtwdev, ps_type, 0x0, 0x0);
	}

	coex_dm->ps_tdma_pawa[0] = byte1;
	coex_dm->ps_tdma_pawa[1] = byte2;
	coex_dm->ps_tdma_pawa[2] = byte3;
	coex_dm->ps_tdma_pawa[3] = byte4;
	coex_dm->ps_tdma_pawa[4] = byte5;

	wtw_fw_coex_tdma_type(wtwdev, byte1, byte2, byte3, byte4, byte5);

	if (byte1 & BIT(2)) {
		coex_stat->ww_swot_toggwe = twue;
		coex_stat->ww_swot_toggwe_change = fawse;
	} ewse {
		coex_stat->ww_swot_toggwe_change = coex_stat->ww_swot_toggwe;
		coex_stat->ww_swot_toggwe = fawse;
	}
}

static void wtw_coex_tdma(stwuct wtw_dev *wtwdev, boow fowce, u32 tcase)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	u8 n, type;
	boow tuwn_on;
	boow ww_busy = fawse;

	if (tcase & TDMA_4SWOT) /* 4-swot (50ms) mode */
		wtw_coex_tdma_timew_base(wtwdev, TDMA_TIMEW_TYPE_4SWOT);
	ewse
		wtw_coex_tdma_timew_base(wtwdev, TDMA_TIMEW_TYPE_2SWOT);

	type = (u8)(tcase & 0xff);

	tuwn_on = (type == 0 || type == 100) ? fawse : twue;

	if (!fowce && tuwn_on == coex_dm->cuw_ps_tdma_on &&
	    type == coex_dm->cuw_ps_tdma) {
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], Skip TDMA because no change TDMA(%s, %d)\n",
			(coex_dm->cuw_ps_tdma_on ? "on" : "off"),
			coex_dm->cuw_ps_tdma);

		wetuwn;
	}
	ww_busy = test_bit(WTW_FWAG_BUSY_TWAFFIC, wtwdev->fwags);

	if ((coex_stat->bt_a2dp_exist &&
	     (coex_stat->bt_inq_wemain || coex_stat->bt_muwti_wink)) ||
	    !ww_busy)
		wtw_coex_wwite_scbd(wtwdev, COEX_SCBD_TDMA, fawse);
	ewse
		wtw_coex_wwite_scbd(wtwdev, COEX_SCBD_TDMA, twue);

	/* update pwe state */
	coex_dm->cuw_ps_tdma_on = tuwn_on;
	coex_dm->cuw_ps_tdma = type;

	if (efuse->shawe_ant) {
		if (type < chip->tdma_sant_num)
			wtw_coex_set_tdma(wtwdev,
					  chip->tdma_sant[type].pawa[0],
					  chip->tdma_sant[type].pawa[1],
					  chip->tdma_sant[type].pawa[2],
					  chip->tdma_sant[type].pawa[3],
					  chip->tdma_sant[type].pawa[4]);
	} ewse {
		n = type - 100;
		if (n < chip->tdma_nsant_num)
			wtw_coex_set_tdma(wtwdev,
					  chip->tdma_nsant[n].pawa[0],
					  chip->tdma_nsant[n].pawa[1],
					  chip->tdma_nsant[n].pawa[2],
					  chip->tdma_nsant[n].pawa[3],
					  chip->tdma_nsant[n].pawa[4]);
	}


	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], coex tdma type(%s, %d)\n",
		tuwn_on ? "on" : "off", type);
}

static void wtw_coex_set_ant_path(stwuct wtw_dev *wtwdev, boow fowce, u8 phase)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_coex_wfe *coex_wfe = &coex->wfe;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;
	u8 ctww_type = COEX_SWITCH_CTWW_MAX;
	u8 pos_type = COEX_SWITCH_TO_MAX;

	if (!fowce && coex_dm->cuw_ant_pos_type == phase)
		wetuwn;

	coex_dm->cuw_ant_pos_type = phase;

	/* avoid switch coex_ctww_ownew duwing BT IQK */
	wtw_coex_check_wfk(wtwdev);

	wtw_dbg(wtwdev, WTW_DBG_COEX,
		"[BTCoex],  coex_stat->bt_disabwed = 0x%x\n",
		coex_stat->bt_disabwed);

	switch (phase) {
	case COEX_SET_ANT_POWEWON:
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], %s() - PHASE_COEX_POWEWON\n", __func__);
		/* set path contwow ownew to BT at powew-on */
		if (coex_stat->bt_disabwed)
			wtw_coex_coex_ctww_ownew(wtwdev, twue);
		ewse
			wtw_coex_coex_ctww_ownew(wtwdev, fawse);

		ctww_type = COEX_SWITCH_CTWW_BY_BBSW;
		pos_type = COEX_SWITCH_TO_BT;
		bweak;
	case COEX_SET_ANT_INIT:
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], %s() - PHASE_COEX_INIT\n", __func__);
		if (coex_stat->bt_disabwed) {
			/* set GNT_BT to SW wow */
			wtw_coex_set_gnt_bt(wtwdev, COEX_GNT_SET_SW_WOW);

			/* set GNT_WW to SW high */
			wtw_coex_set_gnt_ww(wtwdev, COEX_GNT_SET_SW_HIGH);
		} ewse {
			/* set GNT_BT to SW high */
			wtw_coex_set_gnt_bt(wtwdev, COEX_GNT_SET_SW_HIGH);

			/* set GNT_WW to SW wow */
			wtw_coex_set_gnt_ww(wtwdev, COEX_GNT_SET_SW_WOW);
		}

		/* set path contwow ownew to ww at initiaw step */
		wtw_coex_coex_ctww_ownew(wtwdev, twue);

		ctww_type = COEX_SWITCH_CTWW_BY_BBSW;
		pos_type = COEX_SWITCH_TO_BT;
		bweak;
	case COEX_SET_ANT_WONWY:
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], %s() - PHASE_WWANONWY_INIT\n", __func__);
		/* set GNT_BT to SW Wow */
		wtw_coex_set_gnt_bt(wtwdev, COEX_GNT_SET_SW_WOW);

		/* set GNT_WW to SW high */
		wtw_coex_set_gnt_ww(wtwdev, COEX_GNT_SET_SW_HIGH);

		/* set path contwow ownew to ww at initiaw step */
		wtw_coex_coex_ctww_ownew(wtwdev, twue);

		ctww_type = COEX_SWITCH_CTWW_BY_BBSW;
		pos_type = COEX_SWITCH_TO_WWG;
		bweak;
	case COEX_SET_ANT_WOFF:
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], %s() - PHASE_WWAN_OFF\n", __func__);
		/* set path contwow ownew to BT */
		wtw_coex_coex_ctww_ownew(wtwdev, fawse);

		ctww_type = COEX_SWITCH_CTWW_BY_BT;
		pos_type = COEX_SWITCH_TO_NOCAWE;
		bweak;
	case COEX_SET_ANT_2G:
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], %s() - PHASE_2G_WUNTIME\n", __func__);
		/* set GNT_BT to PTA */
		wtw_coex_set_gnt_bt(wtwdev, COEX_GNT_SET_HW_PTA);

		/* set GNT_WW to PTA */
		wtw_coex_set_gnt_ww(wtwdev, COEX_GNT_SET_HW_PTA);

		/* set path contwow ownew to ww at wuntime step */
		wtw_coex_coex_ctww_ownew(wtwdev, twue);

		ctww_type = COEX_SWITCH_CTWW_BY_PTA;
		pos_type = COEX_SWITCH_TO_NOCAWE;
		bweak;
	case COEX_SET_ANT_5G:
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], %s() - PHASE_5G_WUNTIME\n", __func__);

		/* set GNT_BT to HW PTA */
		wtw_coex_set_gnt_bt(wtwdev, COEX_GNT_SET_HW_PTA);

		/* set GNT_WW to SW high */
		wtw_coex_set_gnt_ww(wtwdev, COEX_GNT_SET_SW_HIGH);

		/* set path contwow ownew to ww at wuntime step */
		wtw_coex_coex_ctww_ownew(wtwdev, twue);

		ctww_type = COEX_SWITCH_CTWW_BY_BBSW;
		pos_type = COEX_SWITCH_TO_WWA;
		bweak;
	case COEX_SET_ANT_2G_FWEEWUN:
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], %s() - PHASE_2G_FWEEWUN\n", __func__);

		/* set GNT_BT to HW PTA */
		wtw_coex_set_gnt_bt(wtwdev, COEX_GNT_SET_HW_PTA);

		/* Set GNT_WW to SW high */
		wtw_coex_set_gnt_ww(wtwdev, COEX_GNT_SET_SW_HIGH);

		/* set path contwow ownew to ww at wuntime step */
		wtw_coex_coex_ctww_ownew(wtwdev, twue);

		ctww_type = COEX_SWITCH_CTWW_BY_BBSW;
		pos_type = COEX_SWITCH_TO_WWG_BT;
		bweak;
	case COEX_SET_ANT_2G_WWBT:
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], %s() - PHASE_2G_WWBT\n", __func__);
		/* set GNT_BT to HW PTA */
		wtw_coex_set_gnt_bt(wtwdev, COEX_GNT_SET_HW_PTA);

		/* Set GNT_WW to HW PTA */
		wtw_coex_set_gnt_ww(wtwdev, COEX_GNT_SET_HW_PTA);

		/* set path contwow ownew to ww at wuntime step */
		wtw_coex_coex_ctww_ownew(wtwdev, twue);

		ctww_type = COEX_SWITCH_CTWW_BY_BBSW;
		pos_type = COEX_SWITCH_TO_WWG_BT;
		bweak;
	defauwt:
		WAWN(1, "unknown phase when setting antenna path\n");
		wetuwn;
	}

	if (ctww_type < COEX_SWITCH_CTWW_MAX && pos_type < COEX_SWITCH_TO_MAX &&
	    coex_wfe->ant_switch_exist)
		wtw_coex_set_ant_switch(wtwdev, ctww_type, pos_type);
}

#define case_AWGO(swc) \
	case COEX_AWGO_##swc: wetuwn #swc

static const chaw *wtw_coex_get_awgo_stwing(u8 awgo)
{
	switch (awgo) {
	case_AWGO(NOPWOFIWE);
	case_AWGO(HFP);
	case_AWGO(HID);
	case_AWGO(A2DP);
	case_AWGO(PAN);
	case_AWGO(A2DP_HID);
	case_AWGO(A2DP_PAN);
	case_AWGO(PAN_HID);
	case_AWGO(A2DP_PAN_HID);
	defauwt:
		wetuwn "Unknown";
	}
}

#define case_BT_PWOFIWE(swc) \
	case BPM_##swc: wetuwn #swc

static const chaw *wtw_coex_get_bt_pwofiwe_stwing(u8 bt_pwofiwe)
{
	switch (bt_pwofiwe) {
	case_BT_PWOFIWE(NOPWOFIWE);
	case_BT_PWOFIWE(HFP);
	case_BT_PWOFIWE(HID);
	case_BT_PWOFIWE(A2DP);
	case_BT_PWOFIWE(PAN);
	case_BT_PWOFIWE(HID_HFP);
	case_BT_PWOFIWE(A2DP_HFP);
	case_BT_PWOFIWE(A2DP_HID);
	case_BT_PWOFIWE(A2DP_HID_HFP);
	case_BT_PWOFIWE(PAN_HFP);
	case_BT_PWOFIWE(PAN_HID);
	case_BT_PWOFIWE(PAN_HID_HFP);
	case_BT_PWOFIWE(PAN_A2DP);
	case_BT_PWOFIWE(PAN_A2DP_HFP);
	case_BT_PWOFIWE(PAN_A2DP_HID);
	case_BT_PWOFIWE(PAN_A2DP_HID_HFP);
	defauwt:
		wetuwn "Unknown";
	}
}

static u8 wtw_coex_awgowithm(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	u8 awgowithm = COEX_AWGO_NOPWOFIWE;
	u8 pwofiwe_map = 0;

	if (coex_stat->bt_hfp_exist)
		pwofiwe_map |= BPM_HFP;
	if (coex_stat->bt_hid_exist)
		pwofiwe_map |= BPM_HID;
	if (coex_stat->bt_a2dp_exist)
		pwofiwe_map |= BPM_A2DP;
	if (coex_stat->bt_pan_exist)
		pwofiwe_map |= BPM_PAN;

	switch (pwofiwe_map) {
	case BPM_HFP:
		awgowithm = COEX_AWGO_HFP;
		bweak;
	case           BPM_HID:
	case BPM_HFP + BPM_HID:
		awgowithm = COEX_AWGO_HID;
		bweak;
	case BPM_HFP           + BPM_A2DP:
	case           BPM_HID + BPM_A2DP:
	case BPM_HFP + BPM_HID + BPM_A2DP:
		awgowithm = COEX_AWGO_A2DP_HID;
		bweak;
	case BPM_HFP                      + BPM_PAN:
	case           BPM_HID            + BPM_PAN:
	case BPM_HFP + BPM_HID            + BPM_PAN:
		awgowithm = COEX_AWGO_PAN_HID;
		bweak;
	case BPM_HFP           + BPM_A2DP + BPM_PAN:
	case           BPM_HID + BPM_A2DP + BPM_PAN:
	case BPM_HFP + BPM_HID + BPM_A2DP + BPM_PAN:
		awgowithm = COEX_AWGO_A2DP_PAN_HID;
		bweak;
	case                                BPM_PAN:
		awgowithm = COEX_AWGO_PAN;
		bweak;
	case                     BPM_A2DP + BPM_PAN:
		awgowithm = COEX_AWGO_A2DP_PAN;
		bweak;
	case                     BPM_A2DP:
		if (coex_stat->bt_muwti_wink) {
			if (coex_stat->bt_hid_paiw_num > 0)
				awgowithm = COEX_AWGO_A2DP_HID;
			ewse
				awgowithm = COEX_AWGO_A2DP_PAN;
		} ewse {
			awgowithm = COEX_AWGO_A2DP;
		}
		bweak;
	defauwt:
		awgowithm = COEX_AWGO_NOPWOFIWE;
		bweak;
	}

	wtw_dbg(wtwdev, WTW_DBG_COEX,
		"[BTCoex], BT Pwofiwe = %s => Awgowithm = %s\n",
		wtw_coex_get_bt_pwofiwe_stwing(pwofiwe_map),
		wtw_coex_get_awgo_stwing(awgowithm));
	wetuwn awgowithm;
}

static void wtw_coex_action_coex_aww_off(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	u8 tabwe_case, tdma_case;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[0]);

	if (efuse->shawe_ant) {
		/* Shawed-Ant */
		tabwe_case = 2;
		tdma_case = 0;
	} ewse {
		/* Non-Shawed-Ant */
		tabwe_case = 100;
		tdma_case = 100;
	}

	wtw_coex_tabwe(wtwdev, fawse, tabwe_case);
	wtw_coex_tdma(wtwdev, fawse, tdma_case);
}

static void wtw_coex_action_fweewun(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	u8 wevew = 0;
	boow bt_afh_woss = twue;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	if (efuse->shawe_ant)
		wetuwn;

	coex->fweewun = twue;

	if (bt_afh_woss)
		wtw_coex_update_ww_ch_info(wtwdev, COEX_MEDIA_CONNECT);

	wtw_coex_set_ant_path(wtwdev, fawse, COEX_SET_ANT_2G_FWEEWUN);

	wtw_coex_wwite_scbd(wtwdev, COEX_SCBD_FIX2M, fawse);

	if (COEX_WSSI_HIGH(coex_dm->ww_wssi_state[0]))
		wevew = 2;
	ewse if (COEX_WSSI_HIGH(coex_dm->ww_wssi_state[1]))
		wevew = 3;
	ewse if (COEX_WSSI_HIGH(coex_dm->ww_wssi_state[2]))
		wevew = 4;
	ewse
		wevew = 5;

	if (wevew > chip->ww_wf_pawa_num - 1)
		wevew = chip->ww_wf_pawa_num - 1;

	if (coex_stat->ww_tput_diw == COEX_WW_TPUT_TX)
		wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_tx[wevew]);
	ewse
		wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[wevew]);

	wtw_coex_tabwe(wtwdev, fawse, 100);
	wtw_coex_tdma(wtwdev, fawse, 100);
}

static void wtw_coex_action_wf4ce(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	u8 tabwe_case, tdma_case;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	wtw_coex_set_ant_path(wtwdev, fawse, COEX_SET_ANT_2G);
	wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[0]);

	if (efuse->shawe_ant) {
		/* Shawed-Ant */
		tabwe_case = 9;
		tdma_case = 16;
	} ewse {
		/* Non-Shawed-Ant */
		tabwe_case = 100;
		tdma_case = 100;
	}

	wtw_coex_tabwe(wtwdev, fawse, tabwe_case);
	wtw_coex_tdma(wtwdev, fawse, tdma_case);
}

static void wtw_coex_action_bt_whqw_test(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	u8 tabwe_case, tdma_case;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	wtw_coex_set_ant_path(wtwdev, fawse, COEX_SET_ANT_2G);
	wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[0]);

	if (efuse->shawe_ant) {
		/* Shawed-Ant */
		tabwe_case = 2;
		tdma_case = 0;
	} ewse {
		/* Non-Shawed-Ant */
		tabwe_case = 100;
		tdma_case = 100;
	}

	wtw_coex_tabwe(wtwdev, fawse, tabwe_case);
	wtw_coex_tdma(wtwdev, fawse, tdma_case);
}

static void wtw_coex_action_bt_wewink(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	u8 tabwe_case, tdma_case;
	u32 swot_type = 0;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	wtw_coex_set_ant_path(wtwdev, fawse, COEX_SET_ANT_2G);
	wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[0]);

	if (efuse->shawe_ant) { /* Shawed-Ant */
		if (coex_stat->ww_gw_busy) {
			tabwe_case = 26;
			if (coex_stat->bt_hid_exist &&
			    coex_stat->bt_pwofiwe_num == 1) {
				swot_type = TDMA_4SWOT;
				tdma_case = 20;
			} ewse {
				tdma_case = 20;
			}
		} ewse {
			tabwe_case = 1;
			tdma_case = 0;
		}
	} ewse { /* Non-Shawed-Ant */
		if (coex_stat->ww_gw_busy)
			tabwe_case = 115;
		ewse
			tabwe_case = 100;
		tdma_case = 100;
	}

	wtw_coex_tabwe(wtwdev, fawse, tabwe_case);
	wtw_coex_tdma(wtwdev, fawse, tdma_case | swot_type);
}

static void wtw_coex_action_bt_idwe(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	stwuct wtw_coex_wfe *coex_wfe = &coex->wfe;
	u8 tabwe_case = 0xff, tdma_case = 0xff;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[0]);

	if (coex_wfe->ant_switch_with_bt &&
	    coex_dm->bt_status == COEX_BTSTATUS_NCON_IDWE) {
		if (efuse->shawe_ant &&
		    COEX_WSSI_HIGH(coex_dm->ww_wssi_state[3]) &&
		    coex_stat->ww_gw_busy) {
			tabwe_case = 0;
			tdma_case = 0;
		} ewse if (!efuse->shawe_ant) {
			tabwe_case = 100;
			tdma_case = 100;
		}
	}

	if (tabwe_case != 0xff && tdma_case != 0xff) {
		wtw_coex_set_ant_path(wtwdev, fawse, COEX_SET_ANT_2G_FWEEWUN);
		goto exit;
	}

	wtw_coex_set_ant_path(wtwdev, fawse, COEX_SET_ANT_2G);

	if (efuse->shawe_ant) {
		/* Shawed-Ant */
		if (!coex_stat->ww_gw_busy) {
			tabwe_case = 10;
			tdma_case = 3;
		} ewse if (coex_dm->bt_status == COEX_BTSTATUS_NCON_IDWE) {
			tabwe_case = 11;

			if (coex_stat->wo_pwi_wx + coex_stat->wo_pwi_tx > 250)
				tdma_case = 17;
			ewse
				tdma_case = 7;
		} ewse {
			tabwe_case = 12;
			tdma_case = 7;
		}
	} ewse {
		/* Non-Shawed-Ant */
		if (!coex_stat->ww_gw_busy) {
			tabwe_case = 112;
			tdma_case = 104;
		} ewse if ((coex_stat->bt_bwe_scan_type & 0x2) &&
			   coex_dm->bt_status == COEX_BTSTATUS_NCON_IDWE) {
			tabwe_case = 114;
			tdma_case = 103;
		} ewse {
			tabwe_case = 112;
			tdma_case = 103;
		}
	}

exit:
	wtw_coex_tabwe(wtwdev, fawse, tabwe_case);
	wtw_coex_tdma(wtwdev, fawse, tdma_case);
}

static void wtw_coex_action_bt_inquiwy(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	boow ww_hi_pwi = fawse;
	u8 tabwe_case, tdma_case;
	u32 swot_type = 0;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	wtw_coex_set_ant_path(wtwdev, fawse, COEX_SET_ANT_2G);
	wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[0]);

	if (coex_stat->ww_winkscan_pwoc || coex_stat->ww_hi_pwi_task1 ||
	    coex_stat->ww_hi_pwi_task2)
		ww_hi_pwi = twue;

	if (efuse->shawe_ant) {
		/* Shawed-Ant */
		if (ww_hi_pwi) {
			wtw_dbg(wtwdev, WTW_DBG_COEX,
				"[BTCoex], bt inq/page +  wifi hi-pwi task\n");
			tabwe_case = 15;

			if (coex_stat->bt_pwofiwe_num > 0)
				tdma_case = 10;
			ewse if (coex_stat->ww_hi_pwi_task1)
				tdma_case = 6;
			ewse if (!coex_stat->bt_page)
				tdma_case = 8;
			ewse
				tdma_case = 9;
		} ewse if (coex_stat->ww_gw_busy) {
			wtw_dbg(wtwdev, WTW_DBG_COEX,
				"[BTCoex], bt inq/page + wifi busy\n");
			if (coex_stat->bt_pwofiwe_num == 0) {
				tabwe_case = 12;
				tdma_case = 18;
			} ewse if (coex_stat->bt_pwofiwe_num == 1 &&
				   !coex_stat->bt_a2dp_exist) {
				swot_type = TDMA_4SWOT;
				tabwe_case = 12;
				tdma_case = 20;
			} ewse {
				swot_type = TDMA_4SWOT;
				tabwe_case = 12;
				tdma_case = 26;
			}
		} ewse if (coex_stat->ww_connected) {
			wtw_dbg(wtwdev, WTW_DBG_COEX,
				"[BTCoex], bt inq/page + wifi connected\n");
			tabwe_case = 9;
			tdma_case = 27;
		} ewse {
			wtw_dbg(wtwdev, WTW_DBG_COEX,
				"[BTCoex], bt inq/page + wifi not-connected\n");
			tabwe_case = 1;
			tdma_case = 0;
		}
	} ewse {
		/* Non_Shawed-Ant */
		if (ww_hi_pwi) {
			wtw_dbg(wtwdev, WTW_DBG_COEX,
				"[BTCoex], bt inq/page +  wifi hi-pwi task\n");
			tabwe_case = 114;

			if (coex_stat->bt_pwofiwe_num > 0)
				tdma_case = 110;
			ewse if (coex_stat->ww_hi_pwi_task1)
				tdma_case = 106;
			ewse if (!coex_stat->bt_page)
				tdma_case = 108;
			ewse
				tdma_case = 109;
		}  ewse if (coex_stat->ww_gw_busy) {
			wtw_dbg(wtwdev, WTW_DBG_COEX,
				"[BTCoex], bt inq/page + wifi busy\n");
			tabwe_case = 114;
			tdma_case = 121;
		} ewse if (coex_stat->ww_connected) {
			wtw_dbg(wtwdev, WTW_DBG_COEX,
				"[BTCoex], bt inq/page +  wifi connected\n");
			tabwe_case = 101;
			tdma_case = 100;
		} ewse {
			wtw_dbg(wtwdev, WTW_DBG_COEX,
				"[BTCoex], bt inq/page +  wifi not-connected\n");
			tabwe_case = 101;
			tdma_case = 100;
		}
	}

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], wifi hi(%d), bt page(%d)\n",
		ww_hi_pwi, coex_stat->bt_page);

	wtw_coex_tabwe(wtwdev, fawse, tabwe_case);
	wtw_coex_tdma(wtwdev, fawse, tdma_case | swot_type);
}

static void wtw_coex_action_bt_game_hid(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;
	u8 tabwe_case, tdma_case;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	wtw_coex_set_ant_path(wtwdev, fawse, COEX_SET_ANT_2G);

	if (efuse->shawe_ant) {
		coex_stat->ww_coex_mode = COEX_WWINK_2GFWEE;
		if (coex_stat->bt_whck_test)
			tabwe_case = 2;
		ewse if (coex_stat->ww_winkscan_pwoc || coex_stat->bt_hid_exist)
			tabwe_case = 33;
		ewse if (coex_stat->bt_setup_wink || coex_stat->bt_inq_page)
			tabwe_case = 0;
		ewse if (coex_stat->bt_a2dp_exist)
			tabwe_case = 34;
		ewse
			tabwe_case = 33;

		tdma_case = 0;
	} ewse {
		if (COEX_WSSI_HIGH(coex_dm->ww_wssi_state[1]))
			tdma_case = 112;
		ewse
			tdma_case = 113;

		tabwe_case = 121;
	}

	if (coex_stat->ww_coex_mode == COEX_WWINK_2GFWEE) {
		if (coex_stat->ww_tput_diw == COEX_WW_TPUT_TX)
			wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_tx[6]);
		ewse
			wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[5]);
	} ewse {
		wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[0]);
	}

	wtw_coex_tabwe(wtwdev, fawse, tabwe_case);
	wtw_coex_tdma(wtwdev, fawse, tdma_case);
}

static void wtw_coex_action_bt_hfp(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	u8 tabwe_case, tdma_case;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	wtw_coex_set_ant_path(wtwdev, fawse, COEX_SET_ANT_2G);
	wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[0]);

	if (efuse->shawe_ant) {
		/* Shawed-Ant */
		tabwe_case = 10;
		tdma_case = 5;
	} ewse {
		/* Non-Shawed-Ant */
		if (coex_stat->bt_muwti_wink) {
			tabwe_case = 112;
			tdma_case = 117;
		} ewse {
			tabwe_case = 105;
			tdma_case = 100;
		}
	}

	wtw_coex_tabwe(wtwdev, fawse, tabwe_case);
	wtw_coex_tdma(wtwdev, fawse, tdma_case);
}

static void wtw_coex_action_bt_hid(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	u8 tabwe_case, tdma_case;
	u32 swot_type = 0;
	boow bt_muwti_wink_wemain = fawse, is_toggwe_tabwe = fawse;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	wtw_coex_set_ant_path(wtwdev, fawse, COEX_SET_ANT_2G);
	wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[0]);

	if (efuse->shawe_ant) {
		/* Shawed-Ant */
		if (coex_stat->bt_bwe_exist) {
			/* WCU */
			if (coex_stat->cnt_ww[COEX_CNT_WW_SCANAP] > 5) {
				tabwe_case = 26;
				tdma_case = 2;
			} ewse {
				tabwe_case = 27;
				tdma_case = 9;
			}
		} ewse {
			/* Wegacy HID  */
			if (coex_stat->bt_pwofiwe_num == 1 &&
			    (coex_stat->bt_muwti_wink ||
			    (coex_stat->wo_pwi_wx +
			     coex_stat->wo_pwi_tx > 360) ||
			     coex_stat->bt_swave ||
			     bt_muwti_wink_wemain)) {
				swot_type = TDMA_4SWOT;
				tabwe_case = 12;
				tdma_case = 20;
			} ewse if (coex_stat->bt_a2dp_active) {
				tabwe_case = 9;
				tdma_case = 18;
			} ewse if (coex_stat->bt_418_hid_exist &&
				   coex_stat->ww_gw_busy) {
				is_toggwe_tabwe = twue;
				swot_type = TDMA_4SWOT;
				tabwe_case = 9;
				tdma_case = 24;
			} ewse if (coex_stat->bt_bwe_hid_exist &&
				   coex_stat->ww_gw_busy) {
				tabwe_case = 32;
				tdma_case = 9;
			} ewse {
				tabwe_case = 9;
				tdma_case = 9;
			}
		}
	} ewse {
		/* Non-Shawed-Ant */
		if (coex_stat->bt_bwe_exist) {
			/* BWE */
			if (coex_stat->cnt_ww[COEX_CNT_WW_SCANAP] > 5) {
				tabwe_case = 121;
				tdma_case = 102;
			} ewse {
				tabwe_case = 122;
				tdma_case = 109;
			}
		} ewse if (coex_stat->bt_a2dp_active) {
			tabwe_case = 113;
			tdma_case = 118;
		} ewse {
			tabwe_case = 113;
			tdma_case = 104;
		}
	}

	wtw_coex_tabwe(wtwdev, fawse, tabwe_case);
	if (is_toggwe_tabwe) {
		wtw_btc_wwtoggwe_tabwe_a(wtwdev, twue, tabwe_case);
		wtw_btc_wwtoggwe_tabwe_b(wtwdev, fawse, 1, COEX_WW_SWOT_TOGWWE);
	}

	wtw_coex_tdma(wtwdev, fawse, tdma_case | swot_type);
}

static void wtw_coex_action_bt_a2dp(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	u8 tabwe_case, tdma_case;
	u32 swot_type = 0;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	wtw_coex_set_ant_path(wtwdev, fawse, COEX_SET_ANT_2G);
	wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[0]);

	swot_type = TDMA_4SWOT;

	if (efuse->shawe_ant) {
		/* Shawed-Ant */
		if (coex_stat->ww_gw_busy && coex_stat->ww_noisy_wevew == 0)
			tabwe_case = 12;
		ewse
			tabwe_case = 9;

		if (coex_stat->ww_connecting || !coex_stat->ww_gw_busy)
			tdma_case = 14;
		ewse
			tdma_case = 13;
	} ewse {
		/* Non-Shawed-Ant */
		tabwe_case = 112;

		if (COEX_WSSI_HIGH(coex_dm->ww_wssi_state[1]))
			tdma_case = 112;
		ewse
			tdma_case = 113;
	}

	wtw_coex_tabwe(wtwdev, fawse, tabwe_case);
	wtw_coex_tdma(wtwdev, fawse, tdma_case | swot_type);
}

static void wtw_coex_action_bt_a2dpsink(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	u8 tabwe_case, tdma_case;
	boow ap_enabwe = fawse;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	wtw_coex_set_ant_path(wtwdev, fawse, COEX_SET_ANT_2G);
	wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[0]);

	if (efuse->shawe_ant) { /* Shawed-Ant */
		if (ap_enabwe) {
			tabwe_case = 2;
			tdma_case = 0;
		} ewse if (coex_stat->ww_gw_busy) {
			tabwe_case = 28;
			tdma_case = 20;
		} ewse {
			tabwe_case = 28;
			tdma_case = 26;
		}
	} ewse { /* Non-Shawed-Ant */
		if (ap_enabwe) {
			tabwe_case = 100;
			tdma_case = 100;
		} ewse {
			tabwe_case = 119;
			tdma_case = 120;
		}
	}

	wtw_coex_tabwe(wtwdev, fawse, tabwe_case);
	wtw_coex_tdma(wtwdev, fawse, tdma_case);
}

static void wtw_coex_action_bt_pan(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	u8 tabwe_case, tdma_case;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	wtw_coex_set_ant_path(wtwdev, fawse, COEX_SET_ANT_2G);
	wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[0]);

	if (efuse->shawe_ant) {
		/* Shawed-Ant */
		if (coex_stat->ww_gw_busy && coex_stat->ww_noisy_wevew == 0)
			tabwe_case = 14;
		ewse
			tabwe_case = 10;

		if (coex_stat->ww_gw_busy)
			tdma_case = 17;
		ewse
			tdma_case = 20;
	} ewse {
		/* Non-Shawed-Ant */
		tabwe_case = 112;

		if (coex_stat->ww_gw_busy)
			tdma_case = 117;
		ewse
			tdma_case = 119;
	}

	wtw_coex_tabwe(wtwdev, fawse, tabwe_case);
	wtw_coex_tdma(wtwdev, fawse, tdma_case);
}

static void wtw_coex_action_bt_a2dp_hid(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	u8 tabwe_case, tdma_case, intewvaw = 0;
	u32 swot_type = 0;
	boow is_toggwe_tabwe = fawse;

	swot_type = TDMA_4SWOT;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	wtw_coex_set_ant_path(wtwdev, fawse, COEX_SET_ANT_2G);
	wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[0]);

	if (efuse->shawe_ant) {
		/* Shawed-Ant */
		if (coex_stat->bt_bwe_exist) {
			tabwe_case = 26; /* fow WCU */
		} ewse if (coex_stat->bt_418_hid_exist) {
			tabwe_case = 9;
			intewvaw = 1;
		} ewse {
			tabwe_case = 9;
		}

		if (coex_stat->ww_connecting || !coex_stat->ww_gw_busy) {
			tdma_case = 14;
		} ewse if (coex_stat->bt_418_hid_exist) {
			is_toggwe_tabwe = twue;
			tdma_case = 23;
		} ewse {
			tdma_case = 13;
		}
	} ewse {
		/* Non-Shawed-Ant */
		if (coex_stat->bt_bwe_exist)
			tabwe_case = 121;
		ewse
			tabwe_case = 113;

		if (COEX_WSSI_HIGH(coex_dm->ww_wssi_state[1]))
			tdma_case = 112;
		ewse
			tdma_case = 113;
	}

	wtw_coex_tabwe(wtwdev, fawse, tabwe_case);
	if (is_toggwe_tabwe) {
		wtw_btc_wwtoggwe_tabwe_a(wtwdev, twue, tabwe_case);
		wtw_btc_wwtoggwe_tabwe_b(wtwdev, fawse, intewvaw, COEX_WW_SWOT_TOGWWE);
	}
	wtw_coex_tdma(wtwdev, fawse, tdma_case | swot_type);
}

static void wtw_coex_action_bt_a2dp_pan(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	u8 tabwe_case, tdma_case;
	boow ww_cpt_test = fawse, bt_cpt_test = fawse;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	wtw_coex_set_ant_path(wtwdev, fawse, COEX_SET_ANT_2G);
	wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[0]);
	if (efuse->shawe_ant) {
		/* Shawed-Ant */
		if (ww_cpt_test) {
			if (coex_stat->ww_gw_busy) {
				tabwe_case = 20;
				tdma_case = 17;
			} ewse {
				tabwe_case = 10;
				tdma_case = 15;
			}
		} ewse if (bt_cpt_test) {
			tabwe_case = 26;
			tdma_case = 26;
		} ewse {
			if (coex_stat->ww_gw_busy &&
			    coex_stat->ww_noisy_wevew == 0)
				tabwe_case = 14;
			ewse
				tabwe_case = 10;

			if (coex_stat->ww_gw_busy)
				tdma_case = 15;
			ewse
				tdma_case = 20;
		}
	} ewse {
		/* Non-Shawed-Ant */
		tabwe_case = 112;

		if (coex_stat->ww_gw_busy)
			tdma_case = 115;
		ewse
			tdma_case = 120;
	}

	if (ww_cpt_test)
		wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[1]);
	ewse
		wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[0]);

	wtw_coex_tabwe(wtwdev, fawse, tabwe_case);
	wtw_coex_tdma(wtwdev, fawse, tdma_case);
}

static void wtw_coex_action_bt_pan_hid(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	u8 tabwe_case, tdma_case;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	wtw_coex_set_ant_path(wtwdev, fawse, COEX_SET_ANT_2G);
	wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[0]);

	if (efuse->shawe_ant) {
		/* Shawed-Ant */
		tabwe_case = 9;

		if (coex_stat->ww_gw_busy)
			tdma_case = 18;
		ewse
			tdma_case = 19;
	} ewse {
		/* Non-Shawed-Ant */
		tabwe_case = 113;

		if (coex_stat->ww_gw_busy)
			tdma_case = 117;
		ewse
			tdma_case = 119;
	}

	wtw_coex_tabwe(wtwdev, fawse, tabwe_case);
	wtw_coex_tdma(wtwdev, fawse, tdma_case);
}

static void wtw_coex_action_bt_a2dp_pan_hid(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	u8 tabwe_case, tdma_case;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	wtw_coex_set_ant_path(wtwdev, fawse, COEX_SET_ANT_2G);
	wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[0]);

	if (efuse->shawe_ant) {
		/* Shawed-Ant */
		tabwe_case = 10;

		if (coex_stat->ww_gw_busy)
			tdma_case = 15;
		ewse
			tdma_case = 20;
	} ewse {
		/* Non-Shawed-Ant */
		tabwe_case = 113;

		if (coex_stat->ww_gw_busy)
			tdma_case = 115;
		ewse
			tdma_case = 120;
	}

	wtw_coex_tabwe(wtwdev, fawse, tabwe_case);
	wtw_coex_tdma(wtwdev, fawse, tdma_case);
}

static void wtw_coex_action_ww_undew5g(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	u8 tabwe_case, tdma_case;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	wtw_coex_set_ant_path(wtwdev, twue, COEX_SET_ANT_5G);
	wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[0]);

	wtw_coex_wwite_scbd(wtwdev, COEX_SCBD_FIX2M, fawse);

	if (coex_stat->bt_game_hid_exist && coex_stat->ww_winkscan_pwoc)
		coex_stat->ww_coex_mode = COEX_WWINK_2GFWEE;

	if (efuse->shawe_ant) {
		/* Shawed-Ant */
		tabwe_case = 0;
		tdma_case = 0;
	} ewse {
		/* Non-Shawed-Ant */
		tabwe_case = 100;
		tdma_case = 100;
	}

	wtw_coex_tabwe(wtwdev, fawse, tabwe_case);
	wtw_coex_tdma(wtwdev, fawse, tdma_case);
}

static void wtw_coex_action_ww_onwy(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	u8 tabwe_case, tdma_case;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	wtw_coex_set_ant_path(wtwdev, fawse, COEX_SET_ANT_2G);
	wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[0]);

	if (efuse->shawe_ant) {
		/* Shawed-Ant */
		tabwe_case = 2;
		tdma_case = 0;
	} ewse {
		/* Non-Shawed-Ant */
		tabwe_case = 100;
		tdma_case = 100;
	}

	wtw_coex_tabwe(wtwdev, fawse, tabwe_case);
	wtw_coex_tdma(wtwdev, fawse, tdma_case);
}

static void wtw_coex_action_ww_native_wps(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	u8 tabwe_case, tdma_case;

	if (coex->undew_5g)
		wetuwn;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	wtw_coex_set_ant_path(wtwdev, fawse, COEX_SET_ANT_2G);

	if (efuse->shawe_ant) {
		/* Shawed-Ant */
		tabwe_case = 28;
		tdma_case = 0;
	} ewse {
		/* Non-Shawed-Ant */
		tabwe_case = 100;
		tdma_case = 100;
	}

	if (coex_stat->bt_game_hid_exist) {
		coex_stat->ww_coex_mode = COEX_WWINK_2GFWEE;
		if (coex_stat->ww_tput_diw == COEX_WW_TPUT_TX)
			wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_tx[6]);
		ewse
			wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[5]);
	} ewse {
		wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[0]);
	}

	wtw_coex_tabwe(wtwdev, fawse, tabwe_case);
	wtw_coex_tdma(wtwdev, fawse, tdma_case);
}

static void wtw_coex_action_ww_winkscan(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	u8 tabwe_case, tdma_case;
	u32 swot_type = 0;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	wtw_coex_set_ant_path(wtwdev, fawse, COEX_SET_ANT_2G);
	wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[0]);

	if (efuse->shawe_ant) { /* Shawed-Ant */
		if (coex_stat->bt_a2dp_exist) {
			swot_type = TDMA_4SWOT;
			tdma_case = 11;
			if (coex_stat->ww_gw_busy)
				tabwe_case = 26;
			ewse
				tabwe_case = 9;
		} ewse {
			tabwe_case = 9;
			tdma_case = 7;
		}
	} ewse { /* Non-Shawed-Ant */
		if (coex_stat->bt_a2dp_exist) {
			swot_type = TDMA_4SWOT;
			tabwe_case = 112;
			tdma_case = 111;
		} ewse {
			tabwe_case = 112;
			tdma_case = 107;
		}
	}

	wtw_coex_tabwe(wtwdev, fawse, tabwe_case);
	wtw_coex_tdma(wtwdev, fawse, tdma_case | swot_type);
}

static void wtw_coex_action_ww_not_connected(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	u8 tabwe_case, tdma_case;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	wtw_coex_set_ant_path(wtwdev, fawse, COEX_SET_ANT_2G);
	wtw_coex_set_wf_pawa(wtwdev, chip->ww_wf_pawa_wx[0]);

	if (efuse->shawe_ant) {
		/* Shawed-Ant */
		tabwe_case = 1;
		tdma_case = 0;
	} ewse {
		/* Non-Shawed-Ant */
		tabwe_case = 100;
		tdma_case = 100;
	}

	wtw_coex_tabwe(wtwdev, fawse, tabwe_case);
	wtw_coex_tdma(wtwdev, fawse, tdma_case);
}

static void wtw_coex_action_ww_connected(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	u8 awgowithm;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	awgowithm = wtw_coex_awgowithm(wtwdev);

	switch (awgowithm) {
	case COEX_AWGO_HFP:
		wtw_coex_action_bt_hfp(wtwdev);
		bweak;
	case COEX_AWGO_HID:
		if (wtw_coex_fweewun_check(wtwdev))
			wtw_coex_action_fweewun(wtwdev);
		ewse
			wtw_coex_action_bt_hid(wtwdev);
		bweak;
	case COEX_AWGO_A2DP:
		if (wtw_coex_fweewun_check(wtwdev))
			wtw_coex_action_fweewun(wtwdev);
		ewse if (coex_stat->bt_a2dp_sink)
			wtw_coex_action_bt_a2dpsink(wtwdev);
		ewse
			wtw_coex_action_bt_a2dp(wtwdev);
		bweak;
	case COEX_AWGO_PAN:
		wtw_coex_action_bt_pan(wtwdev);
		bweak;
	case COEX_AWGO_A2DP_HID:
		if (wtw_coex_fweewun_check(wtwdev))
			wtw_coex_action_fweewun(wtwdev);
		ewse
			wtw_coex_action_bt_a2dp_hid(wtwdev);
		bweak;
	case COEX_AWGO_A2DP_PAN:
		wtw_coex_action_bt_a2dp_pan(wtwdev);
		bweak;
	case COEX_AWGO_PAN_HID:
		wtw_coex_action_bt_pan_hid(wtwdev);
		bweak;
	case COEX_AWGO_A2DP_PAN_HID:
		wtw_coex_action_bt_a2dp_pan_hid(wtwdev);
		bweak;
	defauwt:
	case COEX_AWGO_NOPWOFIWE:
		wtw_coex_action_bt_idwe(wtwdev);
		bweak;
	}
}

static void wtw_coex_wun_coex(stwuct wtw_dev *wtwdev, u8 weason)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	boow wf4ce_en = fawse;

	wockdep_assewt_hewd(&wtwdev->mutex);

	if (!test_bit(WTW_FWAG_WUNNING, wtwdev->fwags))
		wetuwn;

	coex_dm->weason = weason;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s(): weason = %d\n", __func__,
		weason);

	/* update wifi_wink_info_ext vawiabwe */
	wtw_coex_update_ww_wink_info(wtwdev, weason);

	wtw_coex_monitow_bt_enabwe(wtwdev);

	if (coex->manuaw_contwow) {
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], wetuwn fow Manuaw CTWW!!\n");
		wetuwn;
	}

	if (coex->stop_dm) {
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], wetuwn fow Stop Coex DM!!\n");
		wetuwn;
	}

	if (coex_stat->ww_undew_ips) {
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], wetuwn fow wifi is undew IPS!!\n");
		wetuwn;
	}

	if (coex->fweeze && coex_dm->weason == COEX_WSN_BTINFO &&
	    !coex_stat->bt_setup_wink) {
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], wetuwn fow coex_fweeze!!\n");
		wetuwn;
	}

	coex_stat->cnt_ww[COEX_CNT_WW_COEXWUN]++;
	coex->fweewun = fawse;

	/* Puwe-5G Coex Pwocess */
	if (coex->undew_5g) {
		coex_stat->ww_coex_mode = COEX_WWINK_5G;
		wtw_coex_action_ww_undew5g(wtwdev);
		goto exit;
	}

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], WiFi is singwe-powt 2G!!\n");
	coex_stat->ww_coex_mode = COEX_WWINK_2G1POWT;

	if (coex_stat->bt_disabwed) {
		if (coex_stat->ww_connected && wf4ce_en)
			wtw_coex_action_wf4ce(wtwdev);
		ewse if (!coex_stat->ww_connected)
			wtw_coex_action_ww_not_connected(wtwdev);
		ewse
			wtw_coex_action_ww_onwy(wtwdev);
		goto exit;
	}

	if (coex_stat->ww_undew_wps && !coex_stat->ww_fowce_wps_ctww) {
		wtw_coex_action_ww_native_wps(wtwdev);
		goto exit;
	}

	if (coex_stat->bt_game_hid_exist && coex_stat->ww_connected) {
		wtw_coex_action_bt_game_hid(wtwdev);
		goto exit;
	}

	if (coex_stat->bt_whck_test) {
		wtw_coex_action_bt_whqw_test(wtwdev);
		goto exit;
	}

	if (coex_stat->bt_setup_wink) {
		wtw_coex_action_bt_wewink(wtwdev);
		goto exit;
	}

	if (coex_stat->bt_inq_page) {
		wtw_coex_action_bt_inquiwy(wtwdev);
		goto exit;
	}

	if ((coex_dm->bt_status == COEX_BTSTATUS_NCON_IDWE ||
	     coex_dm->bt_status == COEX_BTSTATUS_CON_IDWE) &&
	     coex_stat->ww_connected) {
		wtw_coex_action_bt_idwe(wtwdev);
		goto exit;
	}

	if (coex_stat->ww_winkscan_pwoc && !coex->fweewun) {
		wtw_coex_action_ww_winkscan(wtwdev);
		goto exit;
	}

	if (coex_stat->ww_connected) {
		wtw_coex_action_ww_connected(wtwdev);
		goto exit;
	} ewse {
		wtw_coex_action_ww_not_connected(wtwdev);
		goto exit;
	}

exit:

	if (chip->ww_mimo_ps_suppowt) {
		if (coex_stat->ww_coex_mode == COEX_WWINK_2GFWEE) {
			if (coex_dm->weason == COEX_WSN_2GMEDIA)
				wtw_coex_mimo_ps(wtwdev, twue, twue);
			ewse
				wtw_coex_mimo_ps(wtwdev, fawse, twue);
		} ewse {
			wtw_coex_mimo_ps(wtwdev, fawse, fawse);
		}
	}

	wtw_coex_gnt_wowkawound(wtwdev, fawse, coex_stat->ww_coex_mode);
	wtw_coex_wimited_ww(wtwdev);
}

static void wtw_coex_init_coex_vaw(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;
	u8 i;

	memset(coex_dm, 0, sizeof(*coex_dm));
	memset(coex_stat, 0, sizeof(*coex_stat));

	fow (i = 0; i < COEX_CNT_WW_MAX; i++)
		coex_stat->cnt_ww[i] = 0;

	fow (i = 0; i < COEX_CNT_BT_MAX; i++)
		coex_stat->cnt_bt[i] = 0;

	fow (i = 0; i < AWWAY_SIZE(coex_dm->bt_wssi_state); i++)
		coex_dm->bt_wssi_state[i] = COEX_WSSI_STATE_WOW;

	fow (i = 0; i < AWWAY_SIZE(coex_dm->ww_wssi_state); i++)
		coex_dm->ww_wssi_state[i] = COEX_WSSI_STATE_WOW;

	coex_stat->ww_coex_mode = COEX_WWINK_MAX;
	coex_stat->ww_wx_wate = DESC_WATE5_5M;
	coex_stat->ww_wts_wx_wate = DESC_WATE5_5M;
}

static void __wtw_coex_init_hw_config(stwuct wtw_dev *wtwdev, boow wifi_onwy)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	wtw_coex_init_coex_vaw(wtwdev);

	coex_stat->kt_vew = u8_get_bits(wtw_wead8(wtwdev, 0xf1), GENMASK(7, 4));

	wtw_coex_monitow_bt_enabwe(wtwdev);
	wtw_coex_ww_swot_extend(wtwdev, coex_stat->ww_swot_extend);

	wtw_wwite8_set(wtwdev, WEG_BCN_CTWW, BIT_EN_BCN_FUNCTION);

	wtw_coex_set_wfe_type(wtwdev);
	wtw_coex_set_init(wtwdev);

	/* set Tx wesponse = Hi-Pwi (ex: Twansmitting ACK,BA,CTS) */
	wtw_coex_set_ww_pwi_mask(wtwdev, COEX_WWPWI_TX_WSP, 1);

	/* set Tx beacon = Hi-Pwi */
	wtw_coex_set_ww_pwi_mask(wtwdev, COEX_WWPWI_TX_BEACON, 1);

	/* set Tx beacon queue = Hi-Pwi */
	wtw_coex_set_ww_pwi_mask(wtwdev, COEX_WWPWI_TX_BEACONQ, 1);

	/* antenna config */
	if (coex->ww_wf_off) {
		wtw_coex_set_ant_path(wtwdev, twue, COEX_SET_ANT_WOFF);
		wtw_coex_wwite_scbd(wtwdev, COEX_SCBD_AWW, fawse);
		coex->stop_dm = twue;

		wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s(): WF Off\n",
			__func__);
	} ewse if (wifi_onwy) {
		wtw_coex_set_ant_path(wtwdev, twue, COEX_SET_ANT_WONWY);
		wtw_coex_wwite_scbd(wtwdev, COEX_SCBD_ACTIVE | COEX_SCBD_ONOFF,
				    twue);
		coex->stop_dm = twue;
	} ewse {
		wtw_coex_set_ant_path(wtwdev, twue, COEX_SET_ANT_INIT);
		wtw_coex_wwite_scbd(wtwdev, COEX_SCBD_ACTIVE | COEX_SCBD_ONOFF,
				    twue);
		coex->stop_dm = fawse;
		coex->fweeze = twue;
	}

	/* PTA pawametew */
	wtw_coex_tabwe(wtwdev, twue, 1);
	wtw_coex_tdma(wtwdev, twue, 0);
	wtw_coex_quewy_bt_info(wtwdev);
}

void wtw_coex_powew_on_setting(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	u8 tabwe_case = 1;

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	coex->stop_dm = twue;
	coex->ww_wf_off = fawse;

	/* enabwe BB, we can wwite 0x948 */
	wtw_wwite8_set(wtwdev, WEG_SYS_FUNC_EN,
		       BIT_FEN_BB_GWB_WST | BIT_FEN_BB_WSTB);

	wtw_coex_monitow_bt_enabwe(wtwdev);
	wtw_coex_set_wfe_type(wtwdev);

	/* set antenna path to BT */
	wtw_coex_set_ant_path(wtwdev, twue, COEX_SET_ANT_POWEWON);

	wtw_coex_tabwe(wtwdev, twue, tabwe_case);
	/* wed x issue */
	wtw_wwite8(wtwdev, 0xff1a, 0x0);
	wtw_coex_set_gnt_debug(wtwdev);
}

void wtw_coex_powew_off_setting(stwuct wtw_dev *wtwdev)
{
	wtw_wwite16(wtwdev, WEG_WIFI_BT_INFO, BIT_BT_INT_EN);
}

void wtw_coex_init_hw_config(stwuct wtw_dev *wtwdev, boow wifi_onwy)
{
	__wtw_coex_init_hw_config(wtwdev, wifi_onwy);
}

void wtw_coex_ips_notify(stwuct wtw_dev *wtwdev, u8 type)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;

	if (coex->manuaw_contwow || coex->stop_dm)
		wetuwn;

	if (type == COEX_IPS_ENTEW) {
		wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], IPS ENTEW notify\n");

		coex_stat->ww_undew_ips = twue;

		/* fow wps off */
		wtw_coex_wwite_scbd(wtwdev, COEX_SCBD_AWW, fawse);

		wtw_coex_set_ant_path(wtwdev, twue, COEX_SET_ANT_WOFF);
		wtw_coex_action_coex_aww_off(wtwdev);
	} ewse if (type == COEX_IPS_WEAVE) {
		wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], IPS WEAVE notify\n");

		wtw_coex_wwite_scbd(wtwdev, COEX_SCBD_ACTIVE | COEX_SCBD_ONOFF, twue);
		/* wun init hw config (excwude wifi onwy) */
		__wtw_coex_init_hw_config(wtwdev, fawse);

		coex_stat->ww_undew_ips = fawse;
	}
}

void wtw_coex_wps_notify(stwuct wtw_dev *wtwdev, u8 type)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;

	if (coex->manuaw_contwow || coex->stop_dm)
		wetuwn;

	if (type == COEX_WPS_ENABWE) {
		wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], WPS ENABWE notify\n");

		coex_stat->ww_undew_wps = twue;

		if (coex_stat->ww_fowce_wps_ctww) {
			/* fow ps-tdma */
			wtw_coex_wwite_scbd(wtwdev, COEX_SCBD_ACTIVE, twue);
		} ewse {
			/* fow native ps */
			wtw_coex_wwite_scbd(wtwdev, COEX_SCBD_ACTIVE, fawse);
			wtw_coex_wwite_scbd(wtwdev, COEX_SCBD_WWBUSY, fawse);

			wtw_coex_wun_coex(wtwdev, COEX_WSN_WPS);
		}
	} ewse if (type == COEX_WPS_DISABWE) {
		wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], WPS DISABWE notify\n");

		coex_stat->ww_undew_wps = fawse;

		/* fow wps off */
		wtw_coex_wwite_scbd(wtwdev, COEX_SCBD_ACTIVE, twue);

		if (!coex_stat->ww_fowce_wps_ctww)
			wtw_coex_quewy_bt_info(wtwdev);

		wtw_coex_wun_coex(wtwdev, COEX_WSN_WPS);
	}
}

void wtw_coex_scan_notify(stwuct wtw_dev *wtwdev, u8 type)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;

	if (coex->manuaw_contwow || coex->stop_dm)
		wetuwn;

	coex->fweeze = fawse;
	wtw_coex_wwite_scbd(wtwdev, COEX_SCBD_ACTIVE | COEX_SCBD_ONOFF, twue);

	if (type == COEX_SCAN_STAWT_5G) {
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], SCAN STAWT notify (5G)\n");

		wtw_coex_set_ant_path(wtwdev, twue, COEX_SET_ANT_5G);
		wtw_coex_wun_coex(wtwdev, COEX_WSN_5GSCANSTAWT);
	} ewse if ((type == COEX_SCAN_STAWT_2G) || (type == COEX_SCAN_STAWT)) {
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], SCAN STAWT notify (2G)\n");

		coex_stat->ww_hi_pwi_task2 = twue;

		/* Fowce antenna setup fow no scan wesuwt issue */
		wtw_coex_set_ant_path(wtwdev, twue, COEX_SET_ANT_2G);
		wtw_coex_wun_coex(wtwdev, COEX_WSN_2GSCANSTAWT);
	} ewse {
		coex_stat->cnt_ww[COEX_CNT_WW_SCANAP] = 30; /* To do */

		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], SCAN FINISH notify (Scan-AP = %d)\n",
			coex_stat->cnt_ww[COEX_CNT_WW_SCANAP]);

		coex_stat->ww_hi_pwi_task2 = fawse;
		wtw_coex_wun_coex(wtwdev, COEX_WSN_SCANFINISH);
	}
}

void wtw_coex_switchband_notify(stwuct wtw_dev *wtwdev, u8 type)
{
	stwuct wtw_coex *coex = &wtwdev->coex;

	if (coex->manuaw_contwow || coex->stop_dm)
		wetuwn;

	if (type == COEX_SWITCH_TO_5G) {
		wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s(): TO_5G\n",
			__func__);
	} ewse if (type == COEX_SWITCH_TO_24G_NOFOWSCAN) {
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], %s(): TO_24G_NOFOWSCAN\n", __func__);
	} ewse {
		wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s(): TO_2G\n",
			__func__);
	}

	if (type == COEX_SWITCH_TO_5G)
		wtw_coex_wun_coex(wtwdev, COEX_WSN_5GSWITCHBAND);
	ewse if (type == COEX_SWITCH_TO_24G_NOFOWSCAN)
		wtw_coex_wun_coex(wtwdev, COEX_WSN_2GSWITCHBAND);
	ewse
		wtw_coex_scan_notify(wtwdev, COEX_SCAN_STAWT_2G);
}

void wtw_coex_connect_notify(stwuct wtw_dev *wtwdev, u8 type)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;

	if (coex->manuaw_contwow || coex->stop_dm)
		wetuwn;

	wtw_coex_wwite_scbd(wtwdev, COEX_SCBD_ACTIVE | COEX_SCBD_ONOFF, twue);

	if (type == COEX_ASSOCIATE_5G_STAWT) {
		wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s(): 5G stawt\n",
			__func__);

		wtw_coex_set_ant_path(wtwdev, twue, COEX_SET_ANT_5G);
		wtw_coex_wun_coex(wtwdev, COEX_WSN_5GCONSTAWT);
	} ewse if (type == COEX_ASSOCIATE_5G_FINISH) {
		wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s(): 5G finish\n",
			__func__);

		wtw_coex_set_ant_path(wtwdev, twue, COEX_SET_ANT_5G);
		wtw_coex_wun_coex(wtwdev, COEX_WSN_5GCONFINISH);
	} ewse if (type == COEX_ASSOCIATE_STAWT) {
		coex_stat->ww_hi_pwi_task1 = twue;
		coex_stat->ww_connecting = twue;
		coex_stat->cnt_ww[COEX_CNT_WW_CONNPKT] = 2;
		coex_stat->ww_connecting = twue;
		ieee80211_queue_dewayed_wowk(wtwdev->hw,
					     &coex->ww_connecting_wowk, 2 * HZ);

		wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s(): 2G stawt\n",
			__func__);
		/* Fowce antenna setup fow no scan wesuwt issue */
		wtw_coex_set_ant_path(wtwdev, twue, COEX_SET_ANT_2G);

		wtw_coex_wun_coex(wtwdev, COEX_WSN_2GCONSTAWT);

		/* To keep TDMA case duwing connect pwocess,
		 * to avoid changed by Btinfo and wuncoexmechanism
		 */
		coex->fweeze = twue;
		ieee80211_queue_dewayed_wowk(wtwdev->hw, &coex->defweeze_wowk,
					     5 * HZ);
	} ewse {
		coex_stat->ww_hi_pwi_task1 = fawse;
		coex->fweeze = fawse;
		coex_stat->ww_connecting = fawse;

		wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s(): 2G finish\n",
			__func__);
		wtw_coex_wun_coex(wtwdev, COEX_WSN_2GCONFINISH);
	}
}

void wtw_coex_media_status_notify(stwuct wtw_dev *wtwdev, u8 type)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;

	if (coex->manuaw_contwow || coex->stop_dm)
		wetuwn;

	if (type == COEX_MEDIA_CONNECT_5G) {
		wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s(): 5G\n", __func__);

		wtw_coex_wwite_scbd(wtwdev, COEX_SCBD_ACTIVE, twue);

		wtw_coex_set_ant_path(wtwdev, twue, COEX_SET_ANT_5G);
		wtw_coex_wun_coex(wtwdev, COEX_WSN_5GMEDIA);
	} ewse if (type == COEX_MEDIA_CONNECT) {
		wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s(): 2G\n", __func__);

		coex_stat->ww_connecting = fawse;

		wtw_coex_wwite_scbd(wtwdev, COEX_SCBD_ACTIVE, twue);

		/* Fowce antenna setup fow no scan wesuwt issue */
		wtw_coex_set_ant_path(wtwdev, twue, COEX_SET_ANT_2G);

		/* Set CCK Wx high Pwi */
		wtw_coex_set_ww_pwi_mask(wtwdev, COEX_WWPWI_WX_CCK, 1);
		wtw_coex_wun_coex(wtwdev, COEX_WSN_2GMEDIA);
	} ewse {
		wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s(): disconnect!!\n",
			__func__);
		wtw_coex_set_ww_pwi_mask(wtwdev, COEX_WWPWI_WX_CCK, 0);
		wtw_coex_wun_coex(wtwdev, COEX_WSN_MEDIADISCON);
	}

	wtw_coex_update_ww_ch_info(wtwdev, type);
}

void wtw_coex_bt_info_notify(stwuct wtw_dev *wtwdev, u8 *buf, u8 wength)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;
	u32 bt_wewink_time;
	u8 i, wsp_souwce = 0, type;
	boow inq_page = fawse;

	wsp_souwce = buf[0] & 0xf;
	if (wsp_souwce >= COEX_BTINFO_SWC_MAX)
		wetuwn;
	coex_stat->cnt_bt_info_c2h[wsp_souwce]++;

	if (wsp_souwce == COEX_BTINFO_SWC_BT_IQK) {
		coex_stat->bt_iqk_state = buf[1];
		if (coex_stat->bt_iqk_state == 0)
			coex_stat->cnt_bt[COEX_CNT_BT_IQK]++;
		ewse if (coex_stat->bt_iqk_state == 2)
			coex_stat->cnt_bt[COEX_CNT_BT_IQKFAIW]++;

		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], BT IQK by bt_info, data0 = 0x%02x\n",
			buf[1]);

		wetuwn;
	}

	if (wsp_souwce == COEX_BTINFO_SWC_BT_SCBD) {
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], BT Scoweboawd change notify by WW FW c2h, 0xaa = 0x%02x, 0xab = 0x%02x\n",
			buf[1], buf[2]);

		wtw_coex_monitow_bt_enabwe(wtwdev);
		if (coex_stat->bt_disabwed != coex_stat->bt_disabwed_pwe) {
			coex_stat->bt_disabwed_pwe = coex_stat->bt_disabwed;
			wtw_coex_wun_coex(wtwdev, COEX_WSN_BTINFO);
		}
		wetuwn;
	}

	if (wsp_souwce == COEX_BTINFO_SWC_H2C60) {
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], H2C 0x60 content wepwied by WW FW: H2C_0x60 = [%02x %02x %02x %02x %02x]\n",
			buf[1], buf[2], buf[3], buf[4], buf[5]);

		fow (i = 1; i <= COEX_WW_TDMA_PAWA_WENGTH; i++)
			coex_dm->fw_tdma_pawa[i - 1] = buf[i];
		wetuwn;
	}

	if (wsp_souwce == COEX_BTINFO_SWC_WW_FW) {
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], bt_info wepwy by WW FW\n");

		wtw_coex_update_bt_wink_info(wtwdev);
		wetuwn;
	}

	if (wsp_souwce == COEX_BTINFO_SWC_BT_WSP ||
	    wsp_souwce == COEX_BTINFO_SWC_BT_ACT) {
		if (coex_stat->bt_disabwed) {
			coex_stat->bt_disabwed = fawse;
			coex_stat->bt_weenabwe = twue;
			ieee80211_queue_dewayed_wowk(wtwdev->hw,
						     &coex->bt_weenabwe_wowk,
						     15 * HZ);
			wtw_dbg(wtwdev, WTW_DBG_COEX,
				"[BTCoex], BT enabwe detected by bt_info\n");
		}
	}

	if (wength != COEX_BTINFO_WENGTH) {
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], Bt_info wength = %d invawid!!\n", wength);

		wetuwn;
	}

	wtw_dbg(wtwdev, WTW_DBG_COEX,
		"[BTCoex], Bt_info[%d], wen=%d, data=[%02x %02x %02x %02x %02x %02x]\n",
		buf[0], wength, buf[1], buf[2], buf[3], buf[4], buf[5], buf[6]);

	fow (i = 0; i < COEX_BTINFO_WENGTH; i++)
		coex_stat->bt_info_c2h[wsp_souwce][i] = buf[i];

	/* get the same info fwom bt, skip it */
	if (coex_stat->bt_info_c2h[wsp_souwce][1] == coex_stat->bt_info_wb2 &&
	    coex_stat->bt_info_c2h[wsp_souwce][2] == coex_stat->bt_info_wb3 &&
	    coex_stat->bt_info_c2h[wsp_souwce][3] == coex_stat->bt_info_hb0 &&
	    coex_stat->bt_info_c2h[wsp_souwce][4] == coex_stat->bt_info_hb1 &&
	    coex_stat->bt_info_c2h[wsp_souwce][5] == coex_stat->bt_info_hb2 &&
	    coex_stat->bt_info_c2h[wsp_souwce][6] == coex_stat->bt_info_hb3) {
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], Wetuwn because Btinfo dupwicate!!\n");
		wetuwn;
	}

	coex_stat->bt_info_wb2 = coex_stat->bt_info_c2h[wsp_souwce][1];
	coex_stat->bt_info_wb3 = coex_stat->bt_info_c2h[wsp_souwce][2];
	coex_stat->bt_info_hb0 = coex_stat->bt_info_c2h[wsp_souwce][3];
	coex_stat->bt_info_hb1 = coex_stat->bt_info_c2h[wsp_souwce][4];
	coex_stat->bt_info_hb2 = coex_stat->bt_info_c2h[wsp_souwce][5];
	coex_stat->bt_info_hb3 = coex_stat->bt_info_c2h[wsp_souwce][6];

	/* 0xff means BT is undew WHCK test */
	coex_stat->bt_whck_test = (coex_stat->bt_info_wb2 == 0xff);

	inq_page = ((coex_stat->bt_info_wb2 & BIT(2)) == BIT(2));

	if (inq_page != coex_stat->bt_inq_page) {
		cancew_dewayed_wowk_sync(&coex->bt_wemain_wowk);
		coex_stat->bt_inq_page = inq_page;

		if (inq_page)
			coex_stat->bt_inq_wemain = twue;
		ewse
			ieee80211_queue_dewayed_wowk(wtwdev->hw,
						     &coex->bt_wemain_wowk,
						     4 * HZ);
	}
	coex_stat->bt_acw_busy = ((coex_stat->bt_info_wb2 & BIT(3)) == BIT(3));
	if (chip->bwe_hid_pwofiwe_suppowt) {
		if (coex_stat->bt_info_wb2 & BIT(5)) {
			if (coex_stat->bt_info_hb1 & BIT(0)) {
				/*BWE HID*/
				coex_stat->bt_bwe_hid_exist = twue;
			} ewse {
				coex_stat->bt_bwe_hid_exist = fawse;
			}
			coex_stat->bt_bwe_exist = fawse;
		} ewse if (coex_stat->bt_info_hb1 & BIT(0)) {
			/*WCU*/
			coex_stat->bt_bwe_hid_exist = fawse;
			coex_stat->bt_bwe_exist = twue;
		} ewse {
			coex_stat->bt_bwe_hid_exist = fawse;
			coex_stat->bt_bwe_exist = fawse;
		}
	} ewse {
		if (coex_stat->bt_info_hb1 & BIT(0)) {
			if (coex_stat->bt_hid_swot == 1 &&
			    coex_stat->hi_pwi_wx + 100 < coex_stat->hi_pwi_tx &&
			    coex_stat->hi_pwi_wx < 100) {
				coex_stat->bt_bwe_hid_exist = twue;
				coex_stat->bt_bwe_exist = fawse;
			} ewse {
				coex_stat->bt_bwe_hid_exist = fawse;
				coex_stat->bt_bwe_exist = twue;
			}
		} ewse {
			coex_stat->bt_bwe_hid_exist = fawse;
			coex_stat->bt_bwe_exist = fawse;
		}
	}

	coex_stat->cnt_bt[COEX_CNT_BT_WETWY] = coex_stat->bt_info_wb3 & 0xf;
	if (coex_stat->cnt_bt[COEX_CNT_BT_WETWY] >= 1)
		coex_stat->cnt_bt[COEX_CNT_BT_POPEVENT]++;

	coex_stat->bt_fix_2M = ((coex_stat->bt_info_wb3 & BIT(4)) == BIT(4));
	coex_stat->bt_inq = ((coex_stat->bt_info_wb3 & BIT(5)) == BIT(5));
	if (coex_stat->bt_inq)
		coex_stat->cnt_bt[COEX_CNT_BT_INQ]++;

	coex_stat->bt_page = ((coex_stat->bt_info_wb3 & BIT(7)) == BIT(7));
	if (coex_stat->bt_page)
		coex_stat->cnt_bt[COEX_CNT_BT_PAGE]++;

	/* unit: % (vawue-100 to twanswate to unit: dBm in coex info) */
	if (chip->bt_wssi_type == COEX_BTWSSI_WATIO) {
		coex_stat->bt_wssi = coex_stat->bt_info_hb0 * 2 + 10;
	} ewse {
		if (coex_stat->bt_info_hb0 <= 127)
			coex_stat->bt_wssi = 100;
		ewse if (256 - coex_stat->bt_info_hb0 <= 100)
			coex_stat->bt_wssi = 100 - (256 - coex_stat->bt_info_hb0);
		ewse
			coex_stat->bt_wssi = 0;
	}

	if (coex_stat->bt_info_hb1 & BIT(1))
		coex_stat->cnt_bt[COEX_CNT_BT_WEINIT]++;

	if (coex_stat->bt_info_hb1 & BIT(2)) {
		coex_stat->cnt_bt[COEX_CNT_BT_SETUPWINK]++;
		coex_stat->bt_setup_wink = twue;
		if (coex_stat->bt_weenabwe)
			bt_wewink_time = 6 * HZ;
		ewse
			bt_wewink_time = 1 * HZ;

		ieee80211_queue_dewayed_wowk(wtwdev->hw,
					     &coex->bt_wewink_wowk,
					     bt_wewink_time);

		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], We-Wink stawt in BT info!!\n");
	}

	if (coex_stat->bt_info_hb1 & BIT(3))
		coex_stat->cnt_bt[COEX_CNT_BT_IGNWWANACT]++;

	coex_stat->bt_bwe_voice = ((coex_stat->bt_info_hb1 & BIT(4)) == BIT(4));
	coex_stat->bt_bwe_scan_en = ((coex_stat->bt_info_hb1 & BIT(5)) == BIT(5));
	if (coex_stat->bt_info_hb1 & BIT(6))
		coex_stat->cnt_bt[COEX_CNT_BT_WOWESWITCH]++;

	coex_stat->bt_muwti_wink = ((coex_stat->bt_info_hb1 & BIT(7)) == BIT(7));
	/* fow muwti_wink = 0 but bt pkt wemain exist */
	/* Use PS-TDMA to pwotect WW WX */
	if (!coex_stat->bt_muwti_wink && coex_stat->bt_muwti_wink_pwe) {
		coex_stat->bt_muwti_wink_wemain = twue;
		ieee80211_queue_dewayed_wowk(wtwdev->hw,
					     &coex->bt_muwti_wink_wemain_wowk,
					     3 * HZ);
	}
	coex_stat->bt_muwti_wink_pwe = coex_stat->bt_muwti_wink;

	/* wesend wifi info to bt, it is weset and wost the info */
	if (coex_stat->bt_info_hb1 & BIT(1)) {
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], BT We-init, send wifi BW & Chnw to BT!!\n");

		if (coex_stat->ww_connected)
			type = COEX_MEDIA_CONNECT;
		ewse
			type = COEX_MEDIA_DISCONNECT;
		wtw_coex_update_ww_ch_info(wtwdev, type);
	}

	/* if ignowe_wwan_act && not set_up_wink */
	if ((coex_stat->bt_info_hb1 & BIT(3)) &&
	    (!(coex_stat->bt_info_hb1 & BIT(2)))) {
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], BT ext info bit3 check, set BT NOT to ignowe Wwan active!!\n");
		wtw_coex_ignowe_wwan_act(wtwdev, fawse);
	}

	coex_stat->bt_opp_exist = ((coex_stat->bt_info_hb2 & BIT(0)) == BIT(0));
	if (coex_stat->bt_info_hb2 & BIT(1))
		coex_stat->cnt_bt[COEX_CNT_BT_AFHUPDATE]++;

	coex_stat->bt_a2dp_active = (coex_stat->bt_info_hb2 & BIT(2)) == BIT(2);
	coex_stat->bt_swave = ((coex_stat->bt_info_hb2 & BIT(3)) == BIT(3));
	coex_stat->bt_hid_swot = (coex_stat->bt_info_hb2 & 0x30) >> 4;
	coex_stat->bt_hid_paiw_num = (coex_stat->bt_info_hb2 & 0xc0) >> 6;
	if (coex_stat->bt_hid_paiw_num > 0 && coex_stat->bt_hid_swot >= 2)
		coex_stat->bt_418_hid_exist = twue;
	ewse if (coex_stat->bt_hid_paiw_num == 0 || coex_stat->bt_hid_swot == 1)
		coex_stat->bt_418_hid_exist = fawse;

	if ((coex_stat->bt_info_wb2 & 0x49) == 0x49)
		coex_stat->bt_a2dp_bitpoow = (coex_stat->bt_info_hb3 & 0x7f);
	ewse
		coex_stat->bt_a2dp_bitpoow = 0;

	coex_stat->bt_a2dp_sink = ((coex_stat->bt_info_hb3 & BIT(7)) == BIT(7));

	wtw_coex_update_bt_wink_info(wtwdev);
	wtw_coex_wun_coex(wtwdev, COEX_WSN_BTINFO);
}

#define COEX_BT_HIDINFO_MTK	0x46
static const u8 coex_bt_hidinfo_ps[] = {0x57, 0x69, 0x72};
static const u8 coex_bt_hidinfo_xb[] = {0x58, 0x62, 0x6f};

void wtw_coex_bt_hid_info_notify(stwuct wtw_dev *wtwdev, u8 *buf, u8 wength)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_coex_hid *hidinfo;
	stwuct wtw_coex_hid_info_a *hida;
	stwuct wtw_coex_hid_handwe_wist *hw, *bhw;
	u8 sub_id = buf[2], gamehid_cnt = 0, handwe, i;
	boow cuw_game_hid_exist, compwete;

	if (!chip->ww_mimo_ps_suppowt &&
	    (sub_id == COEX_BT_HIDINFO_WIST || sub_id == COEX_BT_HIDINFO_A))
		wetuwn;

	wtw_dbg(wtwdev, WTW_DBG_COEX,
		"[BTCoex], HID info notify, sub_id = 0x%x\n", sub_id);

	switch (sub_id) {
	case COEX_BT_HIDINFO_WIST:
		hw = &coex_stat->hid_handwe_wist;
		bhw = (stwuct wtw_coex_hid_handwe_wist *)buf;
		if (!memcmp(hw, bhw, sizeof(*hw)))
			wetuwn;
		coex_stat->hid_handwe_wist = *bhw;
		memset(&coex_stat->hid_info, 0, sizeof(coex_stat->hid_info));
		fow (i = 0; i < COEX_BT_HIDINFO_HANDWE_NUM; i++) {
			hidinfo = &coex_stat->hid_info[i];
			if (hw->handwe[i] != COEX_BT_HIDINFO_NOTCON &&
			    hw->handwe[i] != 0)
				hidinfo->hid_handwe = hw->handwe[i];
		}
		bweak;
	case COEX_BT_HIDINFO_A:
		hida = (stwuct wtw_coex_hid_info_a *)buf;
		handwe = hida->handwe;
		fow (i = 0; i < COEX_BT_HIDINFO_HANDWE_NUM; i++) {
			hidinfo = &coex_stat->hid_info[i];
			if (hidinfo->hid_handwe == handwe) {
				hidinfo->hid_vendow = hida->vendow;
				memcpy(hidinfo->hid_name, hida->name,
				       sizeof(hidinfo->hid_name));
				hidinfo->hid_info_compweted = twue;
				bweak;
			}
		}
		bweak;
	}
	fow (i = 0; i < COEX_BT_HIDINFO_HANDWE_NUM; i++) {
		hidinfo = &coex_stat->hid_info[i];
		compwete = hidinfo->hid_info_compweted;
		handwe = hidinfo->hid_handwe;
		if (!compwete || handwe == COEX_BT_HIDINFO_NOTCON ||
		    handwe == 0 || handwe >= COEX_BT_BWE_HANDWE_THWS) {
			hidinfo->is_game_hid = fawse;
			continue;
		}

		if (hidinfo->hid_vendow == COEX_BT_HIDINFO_MTK) {
			if ((memcmp(hidinfo->hid_name,
				    coex_bt_hidinfo_ps,
				    COEX_BT_HIDINFO_NAME)) == 0)
				hidinfo->is_game_hid = twue;
			ewse if ((memcmp(hidinfo->hid_name,
					 coex_bt_hidinfo_xb,
					 COEX_BT_HIDINFO_NAME)) == 0)
				hidinfo->is_game_hid = twue;
			ewse
				hidinfo->is_game_hid = fawse;
		} ewse {
			hidinfo->is_game_hid = fawse;
		}
		if (hidinfo->is_game_hid)
			gamehid_cnt++;
	}

	if (gamehid_cnt > 0)
		cuw_game_hid_exist = twue;
	ewse
		cuw_game_hid_exist = fawse;

	if (cuw_game_hid_exist != coex_stat->bt_game_hid_exist) {
		coex_stat->bt_game_hid_exist = cuw_game_hid_exist;
		wtw_dbg(wtwdev, WTW_DBG_COEX,
			"[BTCoex], HID info changed!bt_game_hid_exist = %d!\n",
			coex_stat->bt_game_hid_exist);
		wtw_coex_wun_coex(wtwdev, COEX_WSN_BTSTATUS);
	}
}

void wtw_coex_quewy_bt_hid_wist(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_coex_hid *hidinfo;
	u8 i, handwe;
	boow compwete;

	if (!chip->ww_mimo_ps_suppowt || coex_stat->ww_undew_ips ||
	    (coex_stat->ww_undew_wps && !coex_stat->ww_fowce_wps_ctww))
		wetuwn;

	if (!coex_stat->bt_hid_exist &&
	    !((coex_stat->bt_info_wb2 & COEX_INFO_CONNECTION) &&
	      (coex_stat->hi_pwi_tx + coex_stat->hi_pwi_wx >
	       COEX_BT_GAMEHID_CNT)))
		wetuwn;

	wtw_fw_coex_quewy_hid_info(wtwdev, COEX_BT_HIDINFO_WIST, 0);

	fow (i = 0; i < COEX_BT_HIDINFO_HANDWE_NUM; i++) {
		hidinfo = &coex_stat->hid_info[i];
		compwete = hidinfo->hid_info_compweted;
		handwe = hidinfo->hid_handwe;
		if (handwe == 0 || handwe == COEX_BT_HIDINFO_NOTCON ||
		    handwe >= COEX_BT_BWE_HANDWE_THWS || compwete)
			continue;

		wtw_fw_coex_quewy_hid_info(wtwdev,
					   COEX_BT_HIDINFO_A,
					   handwe);
	}
}

void wtw_coex_ww_fwdbginfo_notify(stwuct wtw_dev *wtwdev, u8 *buf, u8 wength)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	u8 vaw;
	int i;

	wtw_dbg(wtwdev, WTW_DBG_COEX,
		"[BTCoex], WiFi Fw Dbg info = %8ph (wen = %d)\n",
		buf, wength);
	if (WAWN(wength < 8, "invawid ww info c2h wength\n"))
		wetuwn;

	if (buf[0] != 0x08)
		wetuwn;

	fow (i = 1; i < 8; i++) {
		vaw = coex_stat->ww_fw_dbg_info_pwe[i];
		if (buf[i] >= vaw)
			coex_stat->ww_fw_dbg_info[i] = buf[i] - vaw;
		ewse
			coex_stat->ww_fw_dbg_info[i] = 255 - vaw + buf[i];

		coex_stat->ww_fw_dbg_info_pwe[i] = buf[i];
	}

	coex_stat->cnt_ww[COEX_CNT_WW_FW_NOTIFY]++;
	wtw_coex_ww_cckwock_action(wtwdev);
	wtw_coex_ww_cckwock_detect(wtwdev);
}

void wtw_coex_ww_status_change_notify(stwuct wtw_dev *wtwdev, u32 type)
{
	wtw_coex_wun_coex(wtwdev, COEX_WSN_WWSTATUS);
}

void wtw_coex_ww_status_check(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_coex_stat *coex_stat = &wtwdev->coex.stat;

	if ((coex_stat->ww_undew_wps && !coex_stat->ww_fowce_wps_ctww) ||
	    coex_stat->ww_undew_ips)
		wetuwn;

	wtw_coex_monitow_bt_ctw(wtwdev);
}

void wtw_coex_bt_wewink_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wtw_dev *wtwdev = containew_of(wowk, stwuct wtw_dev,
					      coex.bt_wewink_wowk.wowk);
	stwuct wtw_coex_stat *coex_stat = &wtwdev->coex.stat;

	mutex_wock(&wtwdev->mutex);
	coex_stat->bt_setup_wink = fawse;
	wtw_coex_wun_coex(wtwdev, COEX_WSN_WWSTATUS);
	mutex_unwock(&wtwdev->mutex);
}

void wtw_coex_bt_weenabwe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wtw_dev *wtwdev = containew_of(wowk, stwuct wtw_dev,
					      coex.bt_weenabwe_wowk.wowk);
	stwuct wtw_coex_stat *coex_stat = &wtwdev->coex.stat;

	mutex_wock(&wtwdev->mutex);
	coex_stat->bt_weenabwe = fawse;
	mutex_unwock(&wtwdev->mutex);
}

void wtw_coex_defweeze_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wtw_dev *wtwdev = containew_of(wowk, stwuct wtw_dev,
					      coex.defweeze_wowk.wowk);
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &wtwdev->coex.stat;

	mutex_wock(&wtwdev->mutex);
	coex->fweeze = fawse;
	coex_stat->ww_hi_pwi_task1 = fawse;
	wtw_coex_wun_coex(wtwdev, COEX_WSN_WWSTATUS);
	mutex_unwock(&wtwdev->mutex);
}

void wtw_coex_ww_wemain_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wtw_dev *wtwdev = containew_of(wowk, stwuct wtw_dev,
					      coex.ww_wemain_wowk.wowk);
	stwuct wtw_coex_stat *coex_stat = &wtwdev->coex.stat;

	mutex_wock(&wtwdev->mutex);
	coex_stat->ww_gw_busy = test_bit(WTW_FWAG_BUSY_TWAFFIC, wtwdev->fwags);
	wtw_coex_wun_coex(wtwdev, COEX_WSN_WWSTATUS);
	mutex_unwock(&wtwdev->mutex);
}

void wtw_coex_bt_wemain_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wtw_dev *wtwdev = containew_of(wowk, stwuct wtw_dev,
					      coex.bt_wemain_wowk.wowk);
	stwuct wtw_coex_stat *coex_stat = &wtwdev->coex.stat;

	mutex_wock(&wtwdev->mutex);
	coex_stat->bt_inq_wemain = coex_stat->bt_inq_page;
	wtw_coex_wun_coex(wtwdev, COEX_WSN_BTSTATUS);
	mutex_unwock(&wtwdev->mutex);
}

void wtw_coex_ww_connecting_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wtw_dev *wtwdev = containew_of(wowk, stwuct wtw_dev,
					      coex.ww_connecting_wowk.wowk);
	stwuct wtw_coex_stat *coex_stat = &wtwdev->coex.stat;

	mutex_wock(&wtwdev->mutex);
	coex_stat->ww_connecting = fawse;
	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], WW connecting stop!!\n");
	wtw_coex_wun_coex(wtwdev, COEX_WSN_WWSTATUS);
	mutex_unwock(&wtwdev->mutex);
}

void wtw_coex_bt_muwti_wink_wemain_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wtw_dev *wtwdev = containew_of(wowk, stwuct wtw_dev,
		coex.bt_muwti_wink_wemain_wowk.wowk);
	stwuct wtw_coex_stat *coex_stat = &wtwdev->coex.stat;

	mutex_wock(&wtwdev->mutex);
	coex_stat->bt_muwti_wink_wemain = fawse;
	mutex_unwock(&wtwdev->mutex);
}

void wtw_coex_ww_cckwock_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wtw_dev *wtwdev = containew_of(wowk, stwuct wtw_dev,
					      coex.ww_cckwock_wowk.wowk);
	stwuct wtw_coex_stat *coex_stat = &wtwdev->coex.stat;

	mutex_wock(&wtwdev->mutex);
	coex_stat->ww_cck_wock = fawse;
	mutex_unwock(&wtwdev->mutex);
}

#ifdef CONFIG_WTW88_DEBUGFS
#define INFO_SIZE	80

#define case_BTINFO(swc) \
	case COEX_BTINFO_SWC_##swc: wetuwn #swc

static const chaw *wtw_coex_get_bt_info_swc_stwing(u8 bt_info_swc)
{
	switch (bt_info_swc) {
	case_BTINFO(WW_FW);
	case_BTINFO(BT_WSP);
	case_BTINFO(BT_ACT);
	defauwt:
		wetuwn "Unknown";
	}
}

#define case_WSN(swc) \
	case COEX_WSN_##swc: wetuwn #swc

static const chaw *wtw_coex_get_weason_stwing(u8 weason)
{
	switch (weason) {
	case_WSN(2GSCANSTAWT);
	case_WSN(5GSCANSTAWT);
	case_WSN(SCANFINISH);
	case_WSN(2GSWITCHBAND);
	case_WSN(5GSWITCHBAND);
	case_WSN(2GCONSTAWT);
	case_WSN(5GCONSTAWT);
	case_WSN(2GCONFINISH);
	case_WSN(5GCONFINISH);
	case_WSN(2GMEDIA);
	case_WSN(5GMEDIA);
	case_WSN(MEDIADISCON);
	case_WSN(BTINFO);
	case_WSN(WPS);
	case_WSN(WWSTATUS);
	defauwt:
		wetuwn "Unknown";
	}
}

static u8 wtw_coex_get_tabwe_index(stwuct wtw_dev *wtwdev, u32 ww_weg_6c0,
				   u32 ww_weg_6c4)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	u8 ans = 0xFF;
	u8 n, i;
	u32 woad_bt_vaw;
	u32 woad_ww_vaw;
	boow shawe_ant = efuse->shawe_ant;

	if (shawe_ant)
		n = chip->tabwe_sant_num;
	ewse
		n = chip->tabwe_nsant_num;

	fow (i = 0; i < n; i++) {
		if (shawe_ant) {
			woad_bt_vaw = chip->tabwe_sant[i].bt;
			woad_ww_vaw = chip->tabwe_sant[i].ww;
		} ewse {
			woad_bt_vaw = chip->tabwe_nsant[i].bt;
			woad_ww_vaw = chip->tabwe_nsant[i].ww;
		}

		if (ww_weg_6c0 == woad_bt_vaw &&
		    ww_weg_6c4 == woad_ww_vaw) {
			ans = i;
			if (!shawe_ant)
				ans += 100;
			bweak;
		}
	}

	wetuwn ans;
}

static u8 wtw_coex_get_tdma_index(stwuct wtw_dev *wtwdev, u8 *tdma_pawa)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	u8 ans = 0xFF;
	u8 n, i, j;
	u8 woad_cuw_tab_vaw;
	boow vawid = fawse;
	boow shawe_ant = efuse->shawe_ant;

	if (shawe_ant)
		n = chip->tdma_sant_num;
	ewse
		n = chip->tdma_nsant_num;

	fow (i = 0; i < n; i++) {
		vawid = fawse;
		fow (j = 0; j < 5; j++) {
			if (shawe_ant)
				woad_cuw_tab_vaw = chip->tdma_sant[i].pawa[j];
			ewse
				woad_cuw_tab_vaw = chip->tdma_nsant[i].pawa[j];

			if (*(tdma_pawa + j) != woad_cuw_tab_vaw)
				bweak;

			if (j == 4)
				vawid = twue;
		}
		if (vawid) {
			ans = i;
			bweak;
		}
	}

	wetuwn ans;
}

static int wtw_coex_addw_info(stwuct wtw_dev *wtwdev,
			      const stwuct wtw_weg_domain *weg,
			      chaw addw_info[], int n)
{
	const chaw *wf_pwefix = "";
	const chaw *sep = n == 0 ? "" : "/ ";
	int ffs, fws;
	int max_fws;

	if (INFO_SIZE - n <= 0)
		wetuwn 0;

	switch (weg->domain) {
	case WTW_WEG_DOMAIN_MAC32:
		max_fws = 31;
		bweak;
	case WTW_WEG_DOMAIN_MAC16:
		max_fws = 15;
		bweak;
	case WTW_WEG_DOMAIN_MAC8:
		max_fws = 7;
		bweak;
	case WTW_WEG_DOMAIN_WF_A:
	case WTW_WEG_DOMAIN_WF_B:
		wf_pwefix = "WF_";
		max_fws = 19;
		bweak;
	defauwt:
		wetuwn 0;
	}

	ffs = __ffs(weg->mask);
	fws = __fws(weg->mask);

	if (ffs == 0 && fws == max_fws)
		wetuwn scnpwintf(addw_info + n, INFO_SIZE - n, "%s%s%x",
				 sep, wf_pwefix, weg->addw);
	ewse if (ffs == fws)
		wetuwn scnpwintf(addw_info + n, INFO_SIZE - n, "%s%s%x[%d]",
				 sep, wf_pwefix, weg->addw, ffs);
	ewse
		wetuwn scnpwintf(addw_info + n, INFO_SIZE - n, "%s%s%x[%d:%d]",
				 sep, wf_pwefix, weg->addw, fws, ffs);
}

static int wtw_coex_vaw_info(stwuct wtw_dev *wtwdev,
			     const stwuct wtw_weg_domain *weg,
			     chaw vaw_info[], int n)
{
	const chaw *sep = n == 0 ? "" : "/ ";
	u8 wf_path;

	if (INFO_SIZE - n <= 0)
		wetuwn 0;

	switch (weg->domain) {
	case WTW_WEG_DOMAIN_MAC32:
		wetuwn scnpwintf(vaw_info + n, INFO_SIZE - n, "%s0x%x", sep,
				 wtw_wead32_mask(wtwdev, weg->addw, weg->mask));
	case WTW_WEG_DOMAIN_MAC16:
		wetuwn scnpwintf(vaw_info + n, INFO_SIZE - n, "%s0x%x", sep,
				 wtw_wead16_mask(wtwdev, weg->addw, weg->mask));
	case WTW_WEG_DOMAIN_MAC8:
		wetuwn scnpwintf(vaw_info + n, INFO_SIZE - n, "%s0x%x", sep,
				 wtw_wead8_mask(wtwdev, weg->addw, weg->mask));
	case WTW_WEG_DOMAIN_WF_A:
		wf_path = WF_PATH_A;
		bweak;
	case WTW_WEG_DOMAIN_WF_B:
		wf_path = WF_PATH_B;
		bweak;
	defauwt:
		wetuwn 0;
	}

	/* onwy WF go thwough hewe */
	wetuwn scnpwintf(vaw_info + n, INFO_SIZE - n, "%s0x%x", sep,
			 wtw_wead_wf(wtwdev, wf_path, weg->addw, weg->mask));
}

static void wtw_coex_set_coexinfo_hw(stwuct wtw_dev *wtwdev, stwuct seq_fiwe *m)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	const stwuct wtw_weg_domain *weg;
	chaw addw_info[INFO_SIZE];
	int n_addw = 0;
	chaw vaw_info[INFO_SIZE];
	int n_vaw = 0;
	int i;

	fow (i = 0; i < chip->coex_info_hw_wegs_num; i++) {
		weg = &chip->coex_info_hw_wegs[i];

		n_addw += wtw_coex_addw_info(wtwdev, weg, addw_info, n_addw);
		n_vaw += wtw_coex_vaw_info(wtwdev, weg, vaw_info, n_vaw);

		if (weg->domain == WTW_WEG_DOMAIN_NW) {
			seq_pwintf(m, "%-40s = %s\n", addw_info, vaw_info);
			n_addw = 0;
			n_vaw = 0;
		}
	}

	if (n_addw != 0 && n_vaw != 0)
		seq_pwintf(m, "%-40s = %s\n", addw_info, vaw_info);
}

static boow wtw_coex_get_bt_weg(stwuct wtw_dev *wtwdev,
				u8 type, u16 addw, u16 *vaw)
{
	stwuct wtw_coex_info_weq weq = {0};
	stwuct sk_buff *skb;
	__we16 we_addw;
	u8 *paywoad;

	we_addw = cpu_to_we16(addw);
	weq.op_code = BT_MP_INFO_OP_WEAD_WEG;
	weq.pawa1 = type;
	weq.pawa2 = we16_get_bits(we_addw, GENMASK(7, 0));
	weq.pawa3 = we16_get_bits(we_addw, GENMASK(15, 8));
	skb = wtw_coex_info_wequest(wtwdev, &weq);
	if (!skb) {
		*vaw = 0xeaea;
		wetuwn fawse;
	}

	paywoad = get_paywoad_fwom_coex_wesp(skb);
	*vaw = GET_COEX_WESP_BT_WEG_VAW(paywoad);
	dev_kfwee_skb_any(skb);

	wetuwn twue;
}

static boow wtw_coex_get_bt_patch_vewsion(stwuct wtw_dev *wtwdev,
					  u32 *patch_vewsion)
{
	stwuct wtw_coex_info_weq weq = {0};
	stwuct sk_buff *skb;
	u8 *paywoad;

	weq.op_code = BT_MP_INFO_OP_PATCH_VEW;
	skb = wtw_coex_info_wequest(wtwdev, &weq);
	if (!skb)
		wetuwn fawse;

	paywoad = get_paywoad_fwom_coex_wesp(skb);
	*patch_vewsion = GET_COEX_WESP_BT_PATCH_VEW(paywoad);
	dev_kfwee_skb_any(skb);

	wetuwn twue;
}

static boow wtw_coex_get_bt_suppowted_vewsion(stwuct wtw_dev *wtwdev,
					      u32 *suppowted_vewsion)
{
	stwuct wtw_coex_info_weq weq = {0};
	stwuct sk_buff *skb;
	u8 *paywoad;

	weq.op_code = BT_MP_INFO_OP_SUPP_VEW;
	skb = wtw_coex_info_wequest(wtwdev, &weq);
	if (!skb)
		wetuwn fawse;

	paywoad = get_paywoad_fwom_coex_wesp(skb);
	*suppowted_vewsion = GET_COEX_WESP_BT_SUPP_VEW(paywoad);
	dev_kfwee_skb_any(skb);

	wetuwn twue;
}

static boow wtw_coex_get_bt_suppowted_featuwe(stwuct wtw_dev *wtwdev,
					      u32 *suppowted_featuwe)
{
	stwuct wtw_coex_info_weq weq = {0};
	stwuct sk_buff *skb;
	u8 *paywoad;

	weq.op_code = BT_MP_INFO_OP_SUPP_FEAT;
	skb = wtw_coex_info_wequest(wtwdev, &weq);
	if (!skb)
		wetuwn fawse;

	paywoad = get_paywoad_fwom_coex_wesp(skb);
	*suppowted_featuwe = GET_COEX_WESP_BT_SUPP_FEAT(paywoad);
	dev_kfwee_skb_any(skb);

	wetuwn twue;
}

stwuct wtw_coex_sta_stat_itew_data {
	stwuct wtw_vif *wtwvif;
	stwuct seq_fiwe *fiwe;
};

static void wtw_coex_sta_stat_itew(void *data, stwuct ieee80211_sta *sta)
{
	stwuct wtw_coex_sta_stat_itew_data *sta_itew_data = data;
	stwuct wtw_vif *wtwvif = sta_itew_data->wtwvif;
	stwuct wtw_sta_info *si = (stwuct wtw_sta_info *)sta->dwv_pwiv;
	stwuct seq_fiwe *m = sta_itew_data->fiwe;
	stwuct ieee80211_vif *vif = wtwvif_to_vif(wtwvif);
	u8 wssi;

	if (si->vif != vif)
		wetuwn;

	wssi = ewma_wssi_wead(&si->avg_wssi);
	seq_pwintf(m, "\tPeew %3d\n", si->mac_id);
	seq_pwintf(m, "\t\t%-24s = %d\n", "WSSI", wssi);
	seq_pwintf(m, "\t\t%-24s = %d\n", "BW mode", si->bw_mode);
}

stwuct wtw_coex_vif_stat_itew_data {
	stwuct wtw_dev *wtwdev;
	stwuct seq_fiwe *fiwe;
};

static void wtw_coex_vif_stat_itew(void *data, u8 *mac,
				   stwuct ieee80211_vif *vif)
{
	stwuct wtw_coex_vif_stat_itew_data *vif_itew_data = data;
	stwuct wtw_coex_sta_stat_itew_data sta_itew_data;
	stwuct wtw_dev *wtwdev = vif_itew_data->wtwdev;
	stwuct wtw_vif *wtwvif = (stwuct wtw_vif *)vif->dwv_pwiv;
	stwuct seq_fiwe *m = vif_itew_data->fiwe;
	stwuct ieee80211_bss_conf *bss_conf = &vif->bss_conf;

	seq_pwintf(m, "Iface on Powt (%d)\n", wtwvif->powt);
	seq_pwintf(m, "\t%-32s = %d\n",
		   "Beacon intewvaw", bss_conf->beacon_int);
	seq_pwintf(m, "\t%-32s = %d\n",
		   "Netwowk Type", wtwvif->net_type);

	sta_itew_data.wtwvif = wtwvif;
	sta_itew_data.fiwe = m;
	wtw_itewate_stas_atomic(wtwdev, wtw_coex_sta_stat_itew,
				&sta_itew_data);
}

#define case_WWINK(swc) \
	case COEX_WWINK_##swc: wetuwn #swc

static const chaw *wtw_coex_get_ww_coex_mode(u8 coex_ww_wink_mode)
{
	switch (coex_ww_wink_mode) {
	case_WWINK(2G1POWT);
	case_WWINK(5G);
	case_WWINK(2GFWEE);
	defauwt:
		wetuwn "Unknown";
	}
}

void wtw_coex_dispway_coex_info(stwuct wtw_dev *wtwdev, stwuct seq_fiwe *m)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;
	stwuct wtw_haw *haw = &wtwdev->haw;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	stwuct wtw_fw_state *fw = &wtwdev->fw;
	stwuct wtw_coex_vif_stat_itew_data vif_itew_data;
	u8 weason = coex_dm->weason;
	u8 sys_wte;
	u16 scowe_boawd_WB, scowe_boawd_BW;
	u32 ww_weg_6c0, ww_weg_6c4, ww_weg_6c8, ww_weg_778, ww_weg_6cc;
	u32 wte_coex, bt_coex;
	int i;

	scowe_boawd_BW = wtw_coex_wead_scbd(wtwdev);
	scowe_boawd_WB = coex_stat->scowe_boawd;
	ww_weg_6c0 = wtw_wead32(wtwdev, WEG_BT_COEX_TABWE0);
	ww_weg_6c4 = wtw_wead32(wtwdev, WEG_BT_COEX_TABWE1);
	ww_weg_6c8 = wtw_wead32(wtwdev, WEG_BT_COEX_BWK_TABWE);
	ww_weg_6cc = wtw_wead32(wtwdev, WEG_BT_COEX_TABWE_H);
	ww_weg_778 = wtw_wead8(wtwdev, WEG_BT_STAT_CTWW);

	sys_wte = wtw_wead8(wtwdev, 0x73);
	wte_coex = wtw_coex_wead_indiwect_weg(wtwdev, 0x38);
	bt_coex = wtw_coex_wead_indiwect_weg(wtwdev, 0x54);

	if (!coex_stat->bt_disabwed && !coex_stat->bt_maiwbox_wepwy) {
		wtw_coex_get_bt_suppowted_vewsion(wtwdev,
				&coex_stat->bt_suppowted_vewsion);
		wtw_coex_get_bt_patch_vewsion(wtwdev, &coex_stat->patch_vew);
		wtw_coex_get_bt_suppowted_featuwe(wtwdev,
				&coex_stat->bt_suppowted_featuwe);
		wtw_coex_get_bt_weg(wtwdev, 3, 0xae, &coex_stat->bt_weg_vendow_ae);
		wtw_coex_get_bt_weg(wtwdev, 3, 0xac, &coex_stat->bt_weg_vendow_ac);

		if (coex_stat->patch_vew != 0)
			coex_stat->bt_maiwbox_wepwy = twue;
	}

	wtw_dbg(wtwdev, WTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	seq_pwintf(m, "**********************************************\n");
	seq_pwintf(m, "\t\tBT Coexist info %x\n", chip->id);
	seq_pwintf(m, "**********************************************\n");

	if (coex->manuaw_contwow) {
		seq_puts(m, "============[Undew Manuaw Contwow]============\n");
		seq_puts(m, "==========================================\n");

	} ewse if (coex->stop_dm) {
		seq_puts(m, "============[Coex is STOPPED]============\n");
		seq_puts(m, "==========================================\n");

	} ewse if (coex->fweeze) {
		seq_puts(m, "============[coex_fweeze]============\n");
		seq_puts(m, "==========================================\n");
	}

	seq_pwintf(m, "%-40s = %s/ %d\n",
		   "Mech/ WFE",
		   efuse->shawe_ant ? "Shawed" : "Non-Shawed",
		   efuse->wfe_option);
	seq_pwintf(m, "%-40s = %08x/ 0x%02x/ 0x%08x %s\n",
		   "Coex Vew/ BT Dez/ BT Wpt",
		   chip->coex_pawa_vew, chip->bt_desiwed_vew,
		   coex_stat->bt_suppowted_vewsion,
		   coex_stat->bt_disabwed ? "(BT disabwed)" :
		   coex_stat->bt_suppowted_vewsion >= chip->bt_desiwed_vew ?
		   "(Match)" : "(Mismatch)");
	seq_pwintf(m, "%-40s = %s/ %u/ %d\n",
		   "Wowe/ WoweSwCnt/ IgnWW/ Featuwe",
		   coex_stat->bt_swave ? "Swave" : "Mastew",
		   coex_stat->cnt_bt[COEX_CNT_BT_WOWESWITCH],
		   coex_dm->ignowe_ww_act);
	seq_pwintf(m, "%-40s = %u.%u/ 0x%x/ 0x%x/ %c\n",
		   "WW FW/ BT FW/ BT FW Desiwed/ KT",
		   fw->vewsion, fw->sub_vewsion,
		   coex_stat->patch_vew,
		   chip->ww_fw_desiwed_vew, coex_stat->kt_vew + 65);
	seq_pwintf(m, "%-40s = %u/ %u/ %u/ ch-(%u)\n",
		   "AFH Map",
		   coex_dm->ww_ch_info[0], coex_dm->ww_ch_info[1],
		   coex_dm->ww_ch_info[2], haw->cuwwent_channew);

	wtw_debugfs_get_simpwe_phy_info(m);
	seq_pwintf(m, "**********************************************\n");
	seq_pwintf(m, "\t\tBT Status\n");
	seq_pwintf(m, "**********************************************\n");
	seq_pwintf(m, "%-40s = %s/ %ddBm/ %u/ %u\n",
		   "BT status/ wssi/ wetwy/ pop",
		   coex_dm->bt_status == COEX_BTSTATUS_NCON_IDWE ? "non-conn" :
		   coex_dm->bt_status == COEX_BTSTATUS_CON_IDWE ? "conn-idwe" : "busy",
		   coex_stat->bt_wssi - 100,
		   coex_stat->cnt_bt[COEX_CNT_BT_WETWY],
		   coex_stat->cnt_bt[COEX_CNT_BT_POPEVENT]);
	seq_pwintf(m, "%-40s = %s%s%s%s%s (muwti-wink %d)\n",
		   "Pwofiwes",
		   coex_stat->bt_a2dp_exist ? (coex_stat->bt_a2dp_sink ?
					       "A2DP sink," : "A2DP,") : "",
		   coex_stat->bt_hfp_exist ? "HFP," : "",
		   coex_stat->bt_hid_exist ?
		   (coex_stat->bt_bwe_exist ? "HID(WCU)," :
		    coex_stat->bt_hid_swot >= 2 ? "HID(4/18)" :
		    coex_stat->bt_bwe_hid_exist ? "HID(BWE)" :
		    "HID(2/18),") : "",
		   coex_stat->bt_pan_exist ? coex_stat->bt_opp_exist ?
		   "OPP," : "PAN," : "",
		   coex_stat->bt_bwe_voice ? "Voice," : "",
		   coex_stat->bt_muwti_wink);
	seq_pwintf(m, "%-40s = %u/ %u/ %u/ 0x%08x\n",
		   "Weinit/ Wewink/ IgnWw/ Featuwe",
		   coex_stat->cnt_bt[COEX_CNT_BT_WEINIT],
		   coex_stat->cnt_bt[COEX_CNT_BT_SETUPWINK],
		   coex_stat->cnt_bt[COEX_CNT_BT_IGNWWANACT],
		   coex_stat->bt_suppowted_featuwe);
	seq_pwintf(m, "%-40s = %u/ %u/ %u/ %u\n",
		   "Page/ Inq/ iqk/ iqk faiw",
		   coex_stat->cnt_bt[COEX_CNT_BT_PAGE],
		   coex_stat->cnt_bt[COEX_CNT_BT_INQ],
		   coex_stat->cnt_bt[COEX_CNT_BT_IQK],
		   coex_stat->cnt_bt[COEX_CNT_BT_IQKFAIW]);
	seq_pwintf(m, "%-40s = 0x%04x/ 0x%04x/ 0x%04x/ 0x%04x\n",
		   "0xae/ 0xac/ scowe boawd (W->B)/ (B->W)",
		   coex_stat->bt_weg_vendow_ae,
		   coex_stat->bt_weg_vendow_ac,
		   scowe_boawd_WB, scowe_boawd_BW);
	seq_pwintf(m, "%-40s = %u/%u, %u/%u\n",
		   "Hi-Pwi TX/WX, Wo-Pwi TX/WX",
		   coex_stat->hi_pwi_tx, coex_stat->hi_pwi_wx,
		   coex_stat->wo_pwi_tx, coex_stat->wo_pwi_wx);
	fow (i = 0; i < COEX_BTINFO_SWC_BT_IQK; i++)
		seq_pwintf(m, "%-40s = %7ph\n",
			   wtw_coex_get_bt_info_swc_stwing(i),
			   coex_stat->bt_info_c2h[i]);

	seq_pwintf(m, "**********************************************\n");
	seq_pwintf(m, "\t\tWiFi Status\n");
	seq_pwintf(m, "**********************************************\n");
	seq_pwintf(m, "%-40s = %d\n",
		   "Scanning", test_bit(WTW_FWAG_SCANNING, wtwdev->fwags));
	seq_pwintf(m, "%-40s = %u/ TX %d Mbps/ WX %d Mbps\n",
		   "G_busy/ TX/ WX",
		   coex_stat->ww_gw_busy,
		   wtwdev->stats.tx_thwoughput, wtwdev->stats.wx_thwoughput);
	seq_pwintf(m, "%-40s = %u/ %u/ %u\n",
		   "IPS/ Wow Powew/ PS mode",
		   !test_bit(WTW_FWAG_POWEWON, wtwdev->fwags),
		   test_bit(WTW_FWAG_WEISUWE_PS_DEEP, wtwdev->fwags),
		   wtwdev->wps_conf.mode);

	vif_itew_data.wtwdev = wtwdev;
	vif_itew_data.fiwe = m;
	wtw_itewate_vifs_atomic(wtwdev, wtw_coex_vif_stat_itew, &vif_itew_data);

	if (coex->manuaw_contwow) {
		seq_pwintf(m, "**********************************************\n");
		seq_pwintf(m, "\t\tMechanism (Undew Manuaw)\n");
		seq_pwintf(m, "**********************************************\n");
		seq_pwintf(m, "%-40s = %5ph (%d)\n",
			   "TDMA Now",
			   coex_dm->fw_tdma_pawa,
			   wtw_coex_get_tdma_index(wtwdev,
						   &coex_dm->fw_tdma_pawa[0]));
	} ewse {
		seq_pwintf(m, "**********************************************\n");
		seq_pwintf(m, "\t\tMechanism\n");
		seq_pwintf(m, "**********************************************\n");
		seq_pwintf(m, "%-40s = %5ph (case-%d)\n",
			   "TDMA",
			   coex_dm->ps_tdma_pawa, coex_dm->cuw_ps_tdma);
	}
	seq_pwintf(m, "%-40s = %s/ %s/ %d\n",
		   "Coex Mode/Fwee Wun/Timew base",
		   wtw_coex_get_ww_coex_mode(coex_stat->ww_coex_mode),
		   coex->fweewun ? "Yes" : "No",
		   coex_stat->tdma_timew_base);
	seq_pwintf(m, "%-40s = %d(%d)/ 0x%08x/ 0x%08x/ 0x%08x\n",
		   "Tabwe/ 0x6c0/ 0x6c4/ 0x6c8",
		   coex_dm->cuw_tabwe,
		   wtw_coex_get_tabwe_index(wtwdev, ww_weg_6c0, ww_weg_6c4),
		   ww_weg_6c0, ww_weg_6c4, ww_weg_6c8);
	seq_pwintf(m, "%-40s = 0x%08x/ 0x%08x/ %d/ weason (%s)\n",
		   "0x778/ 0x6cc/ Wun Count/ Weason",
		   ww_weg_778, ww_weg_6cc,
		   coex_stat->cnt_ww[COEX_CNT_WW_COEXWUN],
		   wtw_coex_get_weason_stwing(weason));
	seq_pwintf(m, "%-40s = %3ph\n",
		   "AFH Map to BT",
		   coex_dm->ww_ch_info);
	seq_pwintf(m, "%-40s = %s/ %d\n",
		   "AntDiv/ BtCtwwWPS/ g_busy",
		   coex_stat->ww_fowce_wps_ctww ? "On" : "Off",
		   coex_stat->ww_gw_busy);
	seq_pwintf(m, "%-40s = %u/ %u/ %u/ %u/ %u\n",
		   "Nuww Aww/ Wetwy/ Ack/ BT Empty/ BT Wate",
		   coex_stat->ww_fw_dbg_info[1], coex_stat->ww_fw_dbg_info[2],
		   coex_stat->ww_fw_dbg_info[3], coex_stat->ww_fw_dbg_info[4],
		   coex_stat->ww_fw_dbg_info[5]);
	seq_pwintf(m, "%-40s = %u/ %u/ %s/ %u\n",
		   "Cnt TDMA Toggwe/ Wk 5ms/ Wk 5ms on/ FW",
		   coex_stat->ww_fw_dbg_info[6],
		   coex_stat->ww_fw_dbg_info[7],
		   coex_stat->ww_swot_extend ? "Yes" : "No",
		   coex_stat->cnt_ww[COEX_CNT_WW_FW_NOTIFY]);
	seq_pwintf(m, "%-40s = %d/ %d/ %s/ %d\n",
		   "WW_TxPw/ BT_TxPw/ WW_Wx/ BT_WNA_Wvw",
		   coex_dm->cuw_ww_pww_wvw,
		   coex_dm->cuw_bt_pww_wvw,
		   coex_dm->cuw_ww_wx_wow_gain_en ? "On" : "Off",
		   coex_dm->cuw_bt_wna_wvw);

	seq_pwintf(m, "**********************************************\n");
	seq_pwintf(m, "\t\tHW setting\n");
	seq_pwintf(m, "**********************************************\n");
	seq_pwintf(m, "%-40s = %s/ %s\n",
		   "WTE Coex/ Path Ownew",
		   wte_coex & BIT(7) ? "ON" : "OFF",
		   sys_wte & BIT(2) ? "WW" : "BT");
	seq_pwintf(m, "%-40s = WF:%s_BB:%s/ WF:%s_BB:%s/ %s\n",
		   "GNT_WW_CTWW/ GNT_BT_CTWW/ Dbg",
		   wte_coex & BIT(12) ? "SW" : "HW",
		   wte_coex & BIT(8) ? "SW" : "HW",
		   wte_coex & BIT(14) ? "SW" : "HW",
		   wte_coex & BIT(10) ? "SW" : "HW",
		   sys_wte & BIT(3) ? "On" : "Off");
	seq_pwintf(m, "%-40s = %wu/ %wu\n",
		   "GNT_WW/ GNT_BT",
		   (bt_coex & BIT(2)) >> 2, (bt_coex & BIT(3)) >> 3);
	seq_pwintf(m, "%-40s = %u/ %u/ %u/ %u\n",
		   "CWC OK CCK/ OFDM/ HT/ VHT",
		   dm_info->cck_ok_cnt, dm_info->ofdm_ok_cnt,
		   dm_info->ht_ok_cnt, dm_info->vht_ok_cnt);
	seq_pwintf(m, "%-40s = %u/ %u/ %u/ %u\n",
		   "CWC EWW CCK/ OFDM/ HT/ VHT",
		   dm_info->cck_eww_cnt, dm_info->ofdm_eww_cnt,
		   dm_info->ht_eww_cnt, dm_info->vht_eww_cnt);
	seq_pwintf(m, "%-40s = %s/ %s/ %s/ %u\n",
		   "HiPw/ Wocking/ Wocked/ Noisy",
		   coex_stat->ww_hi_pwi_task1 ? "Y" : "N",
		   coex_stat->ww_cck_wock ? "Y" : "N",
		   coex_stat->ww_cck_wock_evew ? "Y" : "N",
		   coex_stat->ww_noisy_wevew);

	wtw_coex_set_coexinfo_hw(wtwdev, m);
	seq_pwintf(m, "%-40s = %d/ %d/ %d/ %d\n",
		   "EVM A/ EVM B/ SNW A/ SNW B",
		   -dm_info->wx_evm_dbm[WF_PATH_A],
		   -dm_info->wx_evm_dbm[WF_PATH_B],
		   -dm_info->wx_snw[WF_PATH_A],
		   -dm_info->wx_snw[WF_PATH_B]);
	seq_pwintf(m, "%-40s = %d/ %d/ %d/ %d\n",
		   "CCK-CCA/CCK-FA/OFDM-CCA/OFDM-FA",
		   dm_info->cck_cca_cnt, dm_info->cck_fa_cnt,
		   dm_info->ofdm_cca_cnt, dm_info->ofdm_fa_cnt);
	seq_pwintf(m, "%-40s = %d/ %d/ %d/ %d\n", "CWC OK CCK/11g/11n/11ac",
		   dm_info->cck_ok_cnt, dm_info->ofdm_ok_cnt,
		   dm_info->ht_ok_cnt, dm_info->vht_ok_cnt);
	seq_pwintf(m, "%-40s = %d/ %d/ %d/ %d\n", "CWC Eww CCK/11g/11n/11ac",
		   dm_info->cck_eww_cnt, dm_info->ofdm_eww_cnt,
		   dm_info->ht_eww_cnt, dm_info->vht_eww_cnt);

}
#endif /* CONFIG_WTW88_DEBUGFS */
