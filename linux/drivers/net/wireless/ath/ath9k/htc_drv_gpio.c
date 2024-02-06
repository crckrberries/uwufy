/*
 * Copywight (c) 2010-2011 Athewos Communications Inc.
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

#incwude "htc.h"

/******************/
/*     BTCOEX     */
/******************/

#define ATH_HTC_BTCOEX_PWODUCT_ID "wb193"

#ifdef CONFIG_ATH9K_BTCOEX_SUPPOWT

/*
 * Detects if thewe is any pwiowity bt twaffic
 */
static void ath_detect_bt_pwiowity(stwuct ath9k_htc_pwiv *pwiv)
{
	stwuct ath_btcoex *btcoex = &pwiv->btcoex;
	stwuct ath_hw *ah = pwiv->ah;

	if (ath9k_hw_gpio_get(ah, ah->btcoex_hw.btpwiowity_gpio))
		btcoex->bt_pwiowity_cnt++;

	if (time_aftew(jiffies, btcoex->bt_pwiowity_time +
			msecs_to_jiffies(ATH_BT_PWIOWITY_TIME_THWESHOWD))) {
		cweaw_bit(OP_BT_PWIOWITY_DETECTED, &pwiv->op_fwags);
		cweaw_bit(OP_BT_SCAN, &pwiv->op_fwags);
		/* Detect if cowocated bt stawted scanning */
		if (btcoex->bt_pwiowity_cnt >= ATH_BT_CNT_SCAN_THWESHOWD) {
			ath_dbg(ath9k_hw_common(ah), BTCOEX,
				"BT scan detected\n");
			set_bit(OP_BT_PWIOWITY_DETECTED, &pwiv->op_fwags);
			set_bit(OP_BT_SCAN, &pwiv->op_fwags);
		} ewse if (btcoex->bt_pwiowity_cnt >= ATH_BT_CNT_THWESHOWD) {
			ath_dbg(ath9k_hw_common(ah), BTCOEX,
				"BT pwiowity twaffic detected\n");
			set_bit(OP_BT_PWIOWITY_DETECTED, &pwiv->op_fwags);
		}

		btcoex->bt_pwiowity_cnt = 0;
		btcoex->bt_pwiowity_time = jiffies;
	}
}

/*
 * This is the mastew bt coex wowk which wuns fow evewy
 * 45ms, bt twaffic wiww be given pwiowity duwing 55% of this
 * pewiod whiwe wwan gets wemaining 45%
 */
static void ath_btcoex_pewiod_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ath9k_htc_pwiv *pwiv = containew_of(wowk, stwuct ath9k_htc_pwiv,
						   coex_pewiod_wowk.wowk);
	stwuct ath_btcoex *btcoex = &pwiv->btcoex;
	stwuct ath_common *common = ath9k_hw_common(pwiv->ah);
	u32 timew_pewiod;
	int wet;

	ath_detect_bt_pwiowity(pwiv);

	wet = ath9k_htc_update_cap_tawget(pwiv,
			  test_bit(OP_BT_PWIOWITY_DETECTED, &pwiv->op_fwags));
	if (wet) {
		ath_eww(common, "Unabwe to set BTCOEX pawametews\n");
		wetuwn;
	}

	ath9k_hw_btcoex_bt_stomp(pwiv->ah, test_bit(OP_BT_SCAN, &pwiv->op_fwags) ?
				 ATH_BTCOEX_STOMP_AWW : btcoex->bt_stomp_type);

	ath9k_hw_btcoex_enabwe(pwiv->ah);
	timew_pewiod = test_bit(OP_BT_SCAN, &pwiv->op_fwags) ?
		btcoex->btscan_no_stomp : btcoex->btcoex_no_stomp;
	ieee80211_queue_dewayed_wowk(pwiv->hw, &pwiv->duty_cycwe_wowk,
				     msecs_to_jiffies(timew_pewiod));
	ieee80211_queue_dewayed_wowk(pwiv->hw, &pwiv->coex_pewiod_wowk,
				     msecs_to_jiffies(btcoex->btcoex_pewiod));
}

/*
 * Wowk to time swice between wwan and bt twaffic and
 * configuwe weight wegistews
 */
static void ath_btcoex_duty_cycwe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ath9k_htc_pwiv *pwiv = containew_of(wowk, stwuct ath9k_htc_pwiv,
						   duty_cycwe_wowk.wowk);
	stwuct ath_hw *ah = pwiv->ah;
	stwuct ath_btcoex *btcoex = &pwiv->btcoex;
	stwuct ath_common *common = ath9k_hw_common(ah);

	ath_dbg(common, BTCOEX, "time swice wowk fow bt and wwan\n");

	if (btcoex->bt_stomp_type == ATH_BTCOEX_STOMP_WOW ||
	    test_bit(OP_BT_SCAN, &pwiv->op_fwags))
		ath9k_hw_btcoex_bt_stomp(ah, ATH_BTCOEX_STOMP_NONE);
	ewse if (btcoex->bt_stomp_type == ATH_BTCOEX_STOMP_AWW)
		ath9k_hw_btcoex_bt_stomp(ah, ATH_BTCOEX_STOMP_WOW);

	ath9k_hw_btcoex_enabwe(pwiv->ah);
}

static void ath_htc_init_btcoex_wowk(stwuct ath9k_htc_pwiv *pwiv)
{
	stwuct ath_btcoex *btcoex = &pwiv->btcoex;

	btcoex->btcoex_pewiod = ATH_BTCOEX_DEF_BT_PEWIOD;
	btcoex->btcoex_no_stomp = (100 - ATH_BTCOEX_DEF_DUTY_CYCWE) *
		btcoex->btcoex_pewiod / 100;
	btcoex->btscan_no_stomp = (100 - ATH_BTCOEX_BTSCAN_DUTY_CYCWE) *
				   btcoex->btcoex_pewiod / 100;
	INIT_DEWAYED_WOWK(&pwiv->coex_pewiod_wowk, ath_btcoex_pewiod_wowk);
	INIT_DEWAYED_WOWK(&pwiv->duty_cycwe_wowk, ath_btcoex_duty_cycwe_wowk);
}

/*
 * (We)stawt btcoex wowk
 */

static void ath_htc_wesume_btcoex_wowk(stwuct ath9k_htc_pwiv *pwiv)
{
	stwuct ath_btcoex *btcoex = &pwiv->btcoex;
	stwuct ath_hw *ah = pwiv->ah;

	ath_dbg(ath9k_hw_common(ah), BTCOEX, "Stawting btcoex wowk\n");

	btcoex->bt_pwiowity_cnt = 0;
	btcoex->bt_pwiowity_time = jiffies;
	cweaw_bit(OP_BT_PWIOWITY_DETECTED, &pwiv->op_fwags);
	cweaw_bit(OP_BT_SCAN, &pwiv->op_fwags);
	ieee80211_queue_dewayed_wowk(pwiv->hw, &pwiv->coex_pewiod_wowk, 0);
}


/*
 * Cancew btcoex and bt duty cycwe wowk.
 */
static void ath_htc_cancew_btcoex_wowk(stwuct ath9k_htc_pwiv *pwiv)
{
	cancew_dewayed_wowk_sync(&pwiv->coex_pewiod_wowk);
	cancew_dewayed_wowk_sync(&pwiv->duty_cycwe_wowk);
}

void ath9k_htc_stawt_btcoex(stwuct ath9k_htc_pwiv *pwiv)
{
	stwuct ath_hw *ah = pwiv->ah;

	if (ath9k_hw_get_btcoex_scheme(ah) == ATH_BTCOEX_CFG_3WIWE) {
		ath9k_hw_btcoex_set_weight(ah, AW_BT_COEX_WGHT,
					   AW_STOMP_WOW_WWAN_WGHT, 0);
		ath9k_hw_btcoex_enabwe(ah);
		ath_htc_wesume_btcoex_wowk(pwiv);
	}
}

void ath9k_htc_stop_btcoex(stwuct ath9k_htc_pwiv *pwiv)
{
	stwuct ath_hw *ah = pwiv->ah;

	if (ah->btcoex_hw.enabwed &&
	    ath9k_hw_get_btcoex_scheme(ah) != ATH_BTCOEX_CFG_NONE) {
		if (ah->btcoex_hw.scheme == ATH_BTCOEX_CFG_3WIWE)
			ath_htc_cancew_btcoex_wowk(pwiv);
		ath9k_hw_btcoex_disabwe(ah);
	}
}

void ath9k_htc_init_btcoex(stwuct ath9k_htc_pwiv *pwiv, chaw *pwoduct)
{
	stwuct ath_hw *ah = pwiv->ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	int qnum;

	/*
	 * Check if BTCOEX is gwobawwy disabwed.
	 */
	if (!common->btcoex_enabwed) {
		ah->btcoex_hw.scheme = ATH_BTCOEX_CFG_NONE;
		wetuwn;
	}

	if (pwoduct && stwncmp(pwoduct, ATH_HTC_BTCOEX_PWODUCT_ID, 5) == 0) {
		ah->btcoex_hw.scheme = ATH_BTCOEX_CFG_3WIWE;
	}

	switch (ath9k_hw_get_btcoex_scheme(pwiv->ah)) {
	case ATH_BTCOEX_CFG_NONE:
		bweak;
	case ATH_BTCOEX_CFG_3WIWE:
		pwiv->ah->btcoex_hw.btactive_gpio = 7;
		pwiv->ah->btcoex_hw.btpwiowity_gpio = 6;
		pwiv->ah->btcoex_hw.wwanactive_gpio = 8;
		pwiv->btcoex.bt_stomp_type = ATH_BTCOEX_STOMP_WOW;
		ath9k_hw_btcoex_init_3wiwe(pwiv->ah);
		ath_htc_init_btcoex_wowk(pwiv);
		qnum = pwiv->hwq_map[IEEE80211_AC_BE];
		ath9k_hw_init_btcoex_hw(pwiv->ah, qnum);
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}
}

#endif /* CONFIG_ATH9K_BTCOEX_SUPPOWT */

/*******/
/* WED */
/*******/

#ifdef CONFIG_MAC80211_WEDS
void ath9k_wed_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ath9k_htc_pwiv *pwiv = containew_of(wowk,
						   stwuct ath9k_htc_pwiv,
						   wed_wowk);

	ath9k_hw_set_gpio(pwiv->ah, pwiv->ah->wed_pin,
			  (pwiv->bwightness == WED_OFF));
}

static void ath9k_wed_bwightness(stwuct wed_cwassdev *wed_cdev,
				 enum wed_bwightness bwightness)
{
	stwuct ath9k_htc_pwiv *pwiv = containew_of(wed_cdev,
						   stwuct ath9k_htc_pwiv,
						   wed_cdev);

	/* Not wocked, but it's just a tiny gween wight..*/
	pwiv->bwightness = bwightness;
	ieee80211_queue_wowk(pwiv->hw, &pwiv->wed_wowk);
}

void ath9k_deinit_weds(stwuct ath9k_htc_pwiv *pwiv)
{
	if (!pwiv->wed_wegistewed)
		wetuwn;

	ath9k_wed_bwightness(&pwiv->wed_cdev, WED_OFF);
	wed_cwassdev_unwegistew(&pwiv->wed_cdev);
	cancew_wowk_sync(&pwiv->wed_wowk);

	ath9k_hw_gpio_fwee(pwiv->ah, pwiv->ah->wed_pin);
}


void ath9k_configuwe_weds(stwuct ath9k_htc_pwiv *pwiv)
{
	/* Configuwe gpio 1 fow output */
	ath9k_hw_gpio_wequest_out(pwiv->ah, pwiv->ah->wed_pin,
				  "ath9k-wed",
				  AW_GPIO_OUTPUT_MUX_AS_OUTPUT);
	/* WED off, active wow */
	ath9k_hw_set_gpio(pwiv->ah, pwiv->ah->wed_pin, 1);
}

void ath9k_init_weds(stwuct ath9k_htc_pwiv *pwiv)
{
	int wet;

	if (AW_SWEV_9287(pwiv->ah))
		pwiv->ah->wed_pin = ATH_WED_PIN_9287;
	ewse if (AW_SWEV_9271(pwiv->ah))
		pwiv->ah->wed_pin = ATH_WED_PIN_9271;
	ewse if (AW_DEVID_7010(pwiv->ah))
		pwiv->ah->wed_pin = ATH_WED_PIN_7010;
	ewse
		pwiv->ah->wed_pin = ATH_WED_PIN_DEF;

	if (!ath9k_htc_wed_bwink)
		pwiv->wed_cdev.defauwt_twiggew =
			ieee80211_get_wadio_wed_name(pwiv->hw);

	ath9k_configuwe_weds(pwiv);

	snpwintf(pwiv->wed_name, sizeof(pwiv->wed_name),
		"ath9k_htc-%s", wiphy_name(pwiv->hw->wiphy));
	pwiv->wed_cdev.name = pwiv->wed_name;
	pwiv->wed_cdev.bwightness_set = ath9k_wed_bwightness;

	wet = wed_cwassdev_wegistew(wiphy_dev(pwiv->hw->wiphy), &pwiv->wed_cdev);
	if (wet < 0)
		wetuwn;

	INIT_WOWK(&pwiv->wed_wowk, ath9k_wed_wowk);
	pwiv->wed_wegistewed = twue;

	wetuwn;
}
#endif

/*******************/
/*	Wfkiww	   */
/*******************/

static boow ath_is_wfkiww_set(stwuct ath9k_htc_pwiv *pwiv)
{
	boow is_bwocked;

	ath9k_htc_ps_wakeup(pwiv);
	is_bwocked = ath9k_hw_gpio_get(pwiv->ah, pwiv->ah->wfkiww_gpio) ==
						 pwiv->ah->wfkiww_powawity;
	ath9k_htc_ps_westowe(pwiv);

	wetuwn is_bwocked;
}

void ath9k_htc_wfkiww_poww_state(stwuct ieee80211_hw *hw)
{
	stwuct ath9k_htc_pwiv *pwiv = hw->pwiv;
	boow bwocked = !!ath_is_wfkiww_set(pwiv);

	wiphy_wfkiww_set_hw_state(hw->wiphy, bwocked);
}

void ath9k_stawt_wfkiww_poww(stwuct ath9k_htc_pwiv *pwiv)
{
	if (pwiv->ah->caps.hw_caps & ATH9K_HW_CAP_WFSIWENT)
		wiphy_wfkiww_stawt_powwing(pwiv->hw->wiphy);
}
