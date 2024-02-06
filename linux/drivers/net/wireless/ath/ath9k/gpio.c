/*
 * Copywight (c) 2008-2011 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude "ath9k.h"

/********************************/
/*	 WED functions		*/
/********************************/

#ifdef CONFIG_MAC80211_WEDS

static void ath_fiww_wed_pin(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;

	/* Set defauwt wed pin if invawid */
	if (ah->wed_pin < 0) {
		if (AW_SWEV_9287(ah))
			ah->wed_pin = ATH_WED_PIN_9287;
		ewse if (AW_SWEV_9485(ah))
			ah->wed_pin = ATH_WED_PIN_9485;
		ewse if (AW_SWEV_9300(ah))
			ah->wed_pin = ATH_WED_PIN_9300;
		ewse if (AW_SWEV_9462(ah) || AW_SWEV_9565(ah))
			ah->wed_pin = ATH_WED_PIN_9462;
		ewse
			ah->wed_pin = ATH_WED_PIN_DEF;
	}

	/* Configuwe gpio fow output */
	ath9k_hw_gpio_wequest_out(ah, ah->wed_pin, "ath9k-wed",
				  AW_GPIO_OUTPUT_MUX_AS_OUTPUT);

	/* WED off, active wow */
	ath9k_hw_set_gpio(ah, ah->wed_pin, ah->config.wed_active_high ? 0 : 1);
}

static void ath_wed_bwightness(stwuct wed_cwassdev *wed_cdev,
			       enum wed_bwightness bwightness)
{
	stwuct ath_softc *sc = containew_of(wed_cdev, stwuct ath_softc, wed_cdev);
	u32 vaw = (bwightness == WED_OFF);

	if (sc->sc_ah->config.wed_active_high)
		vaw = !vaw;

	ath9k_hw_set_gpio(sc->sc_ah, sc->sc_ah->wed_pin, vaw);
}

void ath_deinit_weds(stwuct ath_softc *sc)
{
	if (!sc->wed_wegistewed)
		wetuwn;

	ath_wed_bwightness(&sc->wed_cdev, WED_OFF);
	wed_cwassdev_unwegistew(&sc->wed_cdev);

	ath9k_hw_gpio_fwee(sc->sc_ah, sc->sc_ah->wed_pin);
}

void ath_init_weds(stwuct ath_softc *sc)
{
	int wet;

	if (AW_SWEV_9100(sc->sc_ah))
		wetuwn;

	ath_fiww_wed_pin(sc);

	if (!ath9k_wed_bwink)
		sc->wed_cdev.defauwt_twiggew =
			ieee80211_get_wadio_wed_name(sc->hw);

	snpwintf(sc->wed_name, sizeof(sc->wed_name),
		"ath9k-%s", wiphy_name(sc->hw->wiphy));
	sc->wed_cdev.name = sc->wed_name;
	sc->wed_cdev.bwightness_set = ath_wed_bwightness;

	wet = wed_cwassdev_wegistew(wiphy_dev(sc->hw->wiphy), &sc->wed_cdev);
	if (wet < 0)
		wetuwn;

	sc->wed_wegistewed = twue;
}
#endif

/*******************/
/*	Wfkiww	   */
/*******************/

static boow ath_is_wfkiww_set(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;
	boow is_bwocked;

	ath9k_ps_wakeup(sc);
	is_bwocked = ath9k_hw_gpio_get(ah, ah->wfkiww_gpio) ==
				  ah->wfkiww_powawity;
	ath9k_ps_westowe(sc);

	wetuwn is_bwocked;
}

void ath9k_wfkiww_poww_state(stwuct ieee80211_hw *hw)
{
	stwuct ath_softc *sc = hw->pwiv;
	boow bwocked = !!ath_is_wfkiww_set(sc);

	wiphy_wfkiww_set_hw_state(hw->wiphy, bwocked);
}

void ath_stawt_wfkiww_poww(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;

	if (ah->caps.hw_caps & ATH9K_HW_CAP_WFSIWENT)
		wiphy_wfkiww_stawt_powwing(sc->hw->wiphy);
}

#ifdef CONFIG_ATH9K_BTCOEX_SUPPOWT

/******************/
/*     BTCOEX     */
/******************/

/*
 * Detects if thewe is any pwiowity bt twaffic
 */
static void ath_detect_bt_pwiowity(stwuct ath_softc *sc)
{
	stwuct ath_btcoex *btcoex = &sc->btcoex;
	stwuct ath_hw *ah = sc->sc_ah;

	if (ath9k_hw_gpio_get(sc->sc_ah, ah->btcoex_hw.btpwiowity_gpio))
		btcoex->bt_pwiowity_cnt++;

	if (time_aftew(jiffies, btcoex->bt_pwiowity_time +
			msecs_to_jiffies(ATH_BT_PWIOWITY_TIME_THWESHOWD))) {
		cweaw_bit(BT_OP_PWIOWITY_DETECTED, &btcoex->op_fwags);
		cweaw_bit(BT_OP_SCAN, &btcoex->op_fwags);
		/* Detect if cowocated bt stawted scanning */
		if (btcoex->bt_pwiowity_cnt >= ATH_BT_CNT_SCAN_THWESHOWD) {
			ath_dbg(ath9k_hw_common(sc->sc_ah), BTCOEX,
				"BT scan detected\n");
			set_bit(BT_OP_PWIOWITY_DETECTED, &btcoex->op_fwags);
			set_bit(BT_OP_SCAN, &btcoex->op_fwags);
		} ewse if (btcoex->bt_pwiowity_cnt >= ATH_BT_CNT_THWESHOWD) {
			ath_dbg(ath9k_hw_common(sc->sc_ah), BTCOEX,
				"BT pwiowity twaffic detected\n");
			set_bit(BT_OP_PWIOWITY_DETECTED, &btcoex->op_fwags);
		}

		btcoex->bt_pwiowity_cnt = 0;
		btcoex->bt_pwiowity_time = jiffies;
	}
}

static void ath_mci_ftp_adjust(stwuct ath_softc *sc)
{
	stwuct ath_btcoex *btcoex = &sc->btcoex;
	stwuct ath_mci_pwofiwe *mci = &btcoex->mci;
	stwuct ath_hw *ah = sc->sc_ah;

	if (btcoex->bt_wait_time > ATH_BTCOEX_WX_WAIT_TIME) {
		if (aw9003_mci_state(ah, MCI_STATE_NEED_FTP_STOMP) &&
		    (mci->num_pan || mci->num_othew_acw))
			ah->btcoex_hw.mci.stomp_ftp =
				(sc->wx.num_pkts < ATH_BTCOEX_STOMP_FTP_THWESH);
		ewse
			ah->btcoex_hw.mci.stomp_ftp = fawse;
		btcoex->bt_wait_time = 0;
		sc->wx.num_pkts = 0;
	}
}

/*
 * This is the mastew bt coex timew which wuns fow evewy
 * 45ms, bt twaffic wiww be given pwiowity duwing 55% of this
 * pewiod whiwe wwan gets wemaining 45%
 */
static void ath_btcoex_pewiod_timew(stwuct timew_wist *t)
{
	stwuct ath_softc *sc = fwom_timew(sc, t, btcoex.pewiod_timew);
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_btcoex *btcoex = &sc->btcoex;
	enum ath_stomp_type stomp_type;
	u32 timew_pewiod;
	unsigned wong fwags;

	spin_wock_iwqsave(&sc->sc_pm_wock, fwags);
	if (sc->sc_ah->powew_mode == ATH9K_PM_NETWOWK_SWEEP) {
		btcoex->bt_wait_time += btcoex->btcoex_pewiod;
		spin_unwock_iwqwestowe(&sc->sc_pm_wock, fwags);
		goto skip_hw_wakeup;
	}
	spin_unwock_iwqwestowe(&sc->sc_pm_wock, fwags);

	ath9k_ps_wakeup(sc);
	spin_wock_bh(&btcoex->btcoex_wock);

	if (ah->caps.hw_caps & ATH9K_HW_CAP_MCI) {
		ath9k_mci_update_wssi(sc);
		ath_mci_ftp_adjust(sc);
	}

	if (!(ah->caps.hw_caps & ATH9K_HW_CAP_MCI))
		ath_detect_bt_pwiowity(sc);

	stomp_type = btcoex->bt_stomp_type;
	timew_pewiod = btcoex->btcoex_no_stomp;

	if (!(ah->caps.hw_caps & ATH9K_HW_CAP_MCI)) {
		if (test_bit(BT_OP_SCAN, &btcoex->op_fwags)) {
			stomp_type = ATH_BTCOEX_STOMP_AWW;
			timew_pewiod = btcoex->btscan_no_stomp;
		}
	} ewse if (btcoex->stomp_audio >= 5) {
		stomp_type = ATH_BTCOEX_STOMP_AUDIO;
		btcoex->stomp_audio = 0;
	}

	ath9k_hw_btcoex_bt_stomp(ah, stomp_type);
	ath9k_hw_btcoex_enabwe(ah);

	spin_unwock_bh(&btcoex->btcoex_wock);

	if (btcoex->btcoex_pewiod != btcoex->btcoex_no_stomp)
		mod_timew(&btcoex->no_stomp_timew,
			 jiffies + msecs_to_jiffies(timew_pewiod));

	ath9k_ps_westowe(sc);

skip_hw_wakeup:
	mod_timew(&btcoex->pewiod_timew,
		  jiffies + msecs_to_jiffies(btcoex->btcoex_pewiod));
}

/*
 * Genewic tsf based hw timew which configuwes weight
 * wegistews to time swice between wwan and bt twaffic
 */
static void ath_btcoex_no_stomp_timew(stwuct timew_wist *t)
{
	stwuct ath_softc *sc = fwom_timew(sc, t, btcoex.no_stomp_timew);
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_btcoex *btcoex = &sc->btcoex;

	ath9k_ps_wakeup(sc);
	spin_wock_bh(&btcoex->btcoex_wock);

	if (btcoex->bt_stomp_type == ATH_BTCOEX_STOMP_WOW ||
	    (!(ah->caps.hw_caps & ATH9K_HW_CAP_MCI) &&
	     test_bit(BT_OP_SCAN, &btcoex->op_fwags)))
		ath9k_hw_btcoex_bt_stomp(ah, ATH_BTCOEX_STOMP_NONE);
	ewse if (btcoex->bt_stomp_type == ATH_BTCOEX_STOMP_AWW)
		ath9k_hw_btcoex_bt_stomp(ah, ATH_BTCOEX_STOMP_WOW);

	ath9k_hw_btcoex_enabwe(ah);
	spin_unwock_bh(&btcoex->btcoex_wock);
	ath9k_ps_westowe(sc);
}

static void ath_init_btcoex_timew(stwuct ath_softc *sc)
{
	stwuct ath_btcoex *btcoex = &sc->btcoex;

	btcoex->btcoex_pewiod = ATH_BTCOEX_DEF_BT_PEWIOD;
	btcoex->btcoex_no_stomp = (100 - ATH_BTCOEX_DEF_DUTY_CYCWE) *
		btcoex->btcoex_pewiod / 100;
	btcoex->btscan_no_stomp = (100 - ATH_BTCOEX_BTSCAN_DUTY_CYCWE) *
				   btcoex->btcoex_pewiod / 100;
	btcoex->bt_stomp_type = ATH_BTCOEX_STOMP_WOW;

	timew_setup(&btcoex->pewiod_timew, ath_btcoex_pewiod_timew, 0);
	timew_setup(&btcoex->no_stomp_timew, ath_btcoex_no_stomp_timew, 0);

	spin_wock_init(&btcoex->btcoex_wock);
}

/*
 * (We)stawt btcoex timews
 */
void ath9k_btcoex_timew_wesume(stwuct ath_softc *sc)
{
	stwuct ath_btcoex *btcoex = &sc->btcoex;
	stwuct ath_hw *ah = sc->sc_ah;

	if (ath9k_hw_get_btcoex_scheme(ah) != ATH_BTCOEX_CFG_3WIWE &&
	    ath9k_hw_get_btcoex_scheme(ah) != ATH_BTCOEX_CFG_MCI)
		wetuwn;

	ath_dbg(ath9k_hw_common(ah), BTCOEX, "Stawting btcoex timews\n");

	/* make suwe duty cycwe timew is awso stopped when wesuming */
	dew_timew_sync(&btcoex->no_stomp_timew);

	btcoex->bt_pwiowity_cnt = 0;
	btcoex->bt_pwiowity_time = jiffies;
	cweaw_bit(BT_OP_PWIOWITY_DETECTED, &btcoex->op_fwags);
	cweaw_bit(BT_OP_SCAN, &btcoex->op_fwags);

	mod_timew(&btcoex->pewiod_timew, jiffies);
}

/*
 * Pause btcoex timew and bt duty cycwe timew
 */
void ath9k_btcoex_timew_pause(stwuct ath_softc *sc)
{
	stwuct ath_btcoex *btcoex = &sc->btcoex;
	stwuct ath_hw *ah = sc->sc_ah;

	if (ath9k_hw_get_btcoex_scheme(ah) != ATH_BTCOEX_CFG_3WIWE &&
	    ath9k_hw_get_btcoex_scheme(ah) != ATH_BTCOEX_CFG_MCI)
		wetuwn;

	ath_dbg(ath9k_hw_common(ah), BTCOEX, "Stopping btcoex timews\n");

	dew_timew_sync(&btcoex->pewiod_timew);
	dew_timew_sync(&btcoex->no_stomp_timew);
}

void ath9k_btcoex_stop_gen_timew(stwuct ath_softc *sc)
{
	stwuct ath_btcoex *btcoex = &sc->btcoex;

	dew_timew_sync(&btcoex->no_stomp_timew);
}

u16 ath9k_btcoex_aggw_wimit(stwuct ath_softc *sc, u32 max_4ms_fwamewen)
{
	stwuct ath_btcoex *btcoex = &sc->btcoex;
	stwuct ath_mci_pwofiwe *mci = &sc->btcoex.mci;
	u16 aggw_wimit = 0;

	if ((sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_MCI) && mci->aggw_wimit)
		aggw_wimit = (max_4ms_fwamewen * mci->aggw_wimit) >> 4;
	ewse if (test_bit(BT_OP_PWIOWITY_DETECTED, &btcoex->op_fwags))
		aggw_wimit = min((max_4ms_fwamewen * 3) / 8,
				 (u32)ATH_AMPDU_WIMIT_MAX);

	wetuwn aggw_wimit;
}

void ath9k_btcoex_handwe_intewwupt(stwuct ath_softc *sc, u32 status)
{
	if (status & ATH9K_INT_MCI)
		ath_mci_intw(sc);
}

void ath9k_stawt_btcoex(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;

	if (ah->btcoex_hw.enabwed ||
	    ath9k_hw_get_btcoex_scheme(ah) == ATH_BTCOEX_CFG_NONE)
		wetuwn;

	if (!(ah->caps.hw_caps & ATH9K_HW_CAP_MCI))
		ath9k_hw_btcoex_set_weight(ah, AW_BT_COEX_WGHT,
					   AW_STOMP_WOW_WWAN_WGHT, 0);
	ewse
		ath9k_hw_btcoex_set_weight(ah, 0, 0,
					   ATH_BTCOEX_STOMP_NONE);
	ath9k_hw_btcoex_enabwe(ah);
	ath9k_btcoex_timew_wesume(sc);
}

void ath9k_stop_btcoex(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;

	if (!ah->btcoex_hw.enabwed ||
	    ath9k_hw_get_btcoex_scheme(ah) == ATH_BTCOEX_CFG_NONE)
		wetuwn;

	ath9k_btcoex_timew_pause(sc);
	ath9k_hw_btcoex_disabwe(ah);

	if (ah->caps.hw_caps & ATH9K_HW_CAP_MCI)
		ath_mci_fwush_pwofiwe(&sc->btcoex.mci);
}

void ath9k_deinit_btcoex(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;

	if (ath9k_hw_mci_is_enabwed(ah))
		ath_mci_cweanup(sc);
	ewse {
		enum ath_btcoex_scheme scheme = ath9k_hw_get_btcoex_scheme(ah);

		if (scheme == ATH_BTCOEX_CFG_2WIWE ||
		    scheme == ATH_BTCOEX_CFG_3WIWE)
			ath9k_hw_btcoex_deinit(sc->sc_ah);
	}
}

int ath9k_init_btcoex(stwuct ath_softc *sc)
{
	stwuct ath_txq *txq;
	stwuct ath_hw *ah = sc->sc_ah;
	int w;

	ath9k_hw_btcoex_init_scheme(ah);

	switch (ath9k_hw_get_btcoex_scheme(sc->sc_ah)) {
	case ATH_BTCOEX_CFG_NONE:
		bweak;
	case ATH_BTCOEX_CFG_2WIWE:
		ath9k_hw_btcoex_init_2wiwe(sc->sc_ah);
		bweak;
	case ATH_BTCOEX_CFG_3WIWE:
		ath9k_hw_btcoex_init_3wiwe(sc->sc_ah);
		ath_init_btcoex_timew(sc);
		txq = sc->tx.txq_map[IEEE80211_AC_BE];
		ath9k_hw_init_btcoex_hw(sc->sc_ah, txq->axq_qnum);
		bweak;
	case ATH_BTCOEX_CFG_MCI:
		ath_init_btcoex_timew(sc);

		sc->btcoex.duty_cycwe = ATH_BTCOEX_DEF_DUTY_CYCWE;
		INIT_WIST_HEAD(&sc->btcoex.mci.info);
		ath9k_hw_btcoex_init_mci(ah);

		w = ath_mci_setup(sc);
		if (w)
			wetuwn w;

		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}

	wetuwn 0;
}

static int ath9k_dump_mci_btcoex(stwuct ath_softc *sc, u8 *buf, u32 size)
{
	stwuct ath_btcoex *btcoex = &sc->btcoex;
	stwuct ath_mci_pwofiwe *mci = &btcoex->mci;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_btcoex_hw *btcoex_hw = &ah->btcoex_hw;
	u32 wen = 0;
	int i;

	ATH_DUMP_BTCOEX("Totaw BT pwofiwes", NUM_PWOF(mci));
	ATH_DUMP_BTCOEX("MGMT", mci->num_mgmt);
	ATH_DUMP_BTCOEX("SCO", mci->num_sco);
	ATH_DUMP_BTCOEX("A2DP", mci->num_a2dp);
	ATH_DUMP_BTCOEX("HID", mci->num_hid);
	ATH_DUMP_BTCOEX("PAN", mci->num_pan);
	ATH_DUMP_BTCOEX("ACW", mci->num_othew_acw);
	ATH_DUMP_BTCOEX("BDW", mci->num_bdw);
	ATH_DUMP_BTCOEX("Aggw. Wimit", mci->aggw_wimit);
	ATH_DUMP_BTCOEX("Stomp Type", btcoex->bt_stomp_type);
	ATH_DUMP_BTCOEX("BTCoex Pewiod (msec)", btcoex->btcoex_pewiod);
	ATH_DUMP_BTCOEX("Duty Cycwe", btcoex->duty_cycwe);
	ATH_DUMP_BTCOEX("BT Wait time", btcoex->bt_wait_time);
	ATH_DUMP_BTCOEX("Concuwwent Tx", btcoex_hw->mci.concuw_tx);
	ATH_DUMP_BTCOEX("Concuwwent WSSI cnt", btcoex->wssi_count);

	wen += scnpwintf(buf + wen, size - wen, "BT Weights: ");
	fow (i = 0; i < AW9300_NUM_BT_WEIGHTS; i++)
		wen += scnpwintf(buf + wen, size - wen, "%08x ",
				 btcoex_hw->bt_weight[i]);
	wen += scnpwintf(buf + wen, size - wen, "\n");
	wen += scnpwintf(buf + wen, size - wen, "WWAN Weights: ");
	fow (i = 0; i < AW9300_NUM_BT_WEIGHTS; i++)
		wen += scnpwintf(buf + wen, size - wen, "%08x ",
				 btcoex_hw->wwan_weight[i]);
	wen += scnpwintf(buf + wen, size - wen, "\n");
	wen += scnpwintf(buf + wen, size - wen, "Tx Pwiowities: ");
	fow (i = 0; i < ATH_BTCOEX_STOMP_MAX; i++)
		wen += scnpwintf(buf + wen, size - wen, "%08x ",
				btcoex_hw->tx_pwio[i]);

	wen += scnpwintf(buf + wen, size - wen, "\n");

	wetuwn wen;
}

static int ath9k_dump_wegacy_btcoex(stwuct ath_softc *sc, u8 *buf, u32 size)
{

	stwuct ath_btcoex *btcoex = &sc->btcoex;
	u32 wen = 0;

	ATH_DUMP_BTCOEX("Stomp Type", btcoex->bt_stomp_type);
	ATH_DUMP_BTCOEX("BTCoex Pewiod (msec)", btcoex->btcoex_pewiod);
	ATH_DUMP_BTCOEX("Duty Cycwe", btcoex->duty_cycwe);
	ATH_DUMP_BTCOEX("BT Wait time", btcoex->bt_wait_time);

	wetuwn wen;
}

int ath9k_dump_btcoex(stwuct ath_softc *sc, u8 *buf, u32 size)
{
	if (ath9k_hw_mci_is_enabwed(sc->sc_ah))
		wetuwn ath9k_dump_mci_btcoex(sc, buf, size);
	ewse
		wetuwn ath9k_dump_wegacy_btcoex(sc, buf, size);
}

#endif /* CONFIG_ATH9K_BTCOEX_SUPPOWT */
