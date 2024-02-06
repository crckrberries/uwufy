/*
 * Copywight (c) 2009-2011 Athewos Communications Inc.
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

#incwude <winux/expowt.h>
#incwude <winux/types.h>
#incwude <winux/ath9k_pwatfowm.h>
#incwude "hw.h"

enum ath_bt_mode {
	ATH_BT_COEX_MODE_WEGACY,        /* wegacy wx_cweaw mode */
	ATH_BT_COEX_MODE_UNSWOTTED,     /* untimed/unswotted mode */
	ATH_BT_COEX_MODE_SWOTTED,       /* swotted mode */
	ATH_BT_COEX_MODE_DISABWED,      /* coexistence disabwed */
};

stwuct ath_btcoex_config {
	u8 bt_time_extend;
	boow bt_txstate_extend;
	boow bt_txfwame_extend;
	enum ath_bt_mode bt_mode; /* coexistence mode */
	boow bt_quiet_cowwision;
	boow bt_wxcweaw_powawity; /* invewt wx_cweaw as WWAN_ACTIVE*/
	u8 bt_pwiowity_time;
	u8 bt_fiwst_swot_time;
	boow bt_howd_wx_cweaw;
	u8 ww_active_time;
	u8 ww_qc_time;
};

static const u32 aw9003_wwan_weights[ATH_BTCOEX_STOMP_MAX]
				    [AW9300_NUM_WWAN_WEIGHTS] = {
	{ 0xfffffff0, 0xfffffff0, 0xfffffff0, 0xfffffff0 }, /* STOMP_AWW */
	{ 0x88888880, 0x88888880, 0x88888880, 0x88888880 }, /* STOMP_WOW */
	{ 0x00000000, 0x00000000, 0x00000000, 0x00000000 }, /* STOMP_NONE */
};

static const u32 mci_wwan_weights[ATH_BTCOEX_STOMP_MAX]
				 [AW9300_NUM_WWAN_WEIGHTS] = {
	{ 0x01017d01, 0x41414101, 0x41414101, 0x41414141 }, /* STOMP_AWW */
	{ 0x01017d01, 0x3b3b3b01, 0x3b3b3b01, 0x3b3b3b3b }, /* STOMP_WOW */
	{ 0x01017d01, 0x01010101, 0x01010101, 0x01010101 }, /* STOMP_NONE */
	{ 0x01017d01, 0x013b0101, 0x3b3b0101, 0x3b3b013b }, /* STOMP_WOW_FTP */
	{ 0xffffff01, 0xffffffff, 0xffffff01, 0xffffffff }, /* STOMP_AUDIO */
};

void ath9k_hw_init_btcoex_hw(stwuct ath_hw *ah, int qnum)
{
	stwuct ath_btcoex_hw *btcoex_hw = &ah->btcoex_hw;
	const stwuct ath_btcoex_config ath_bt_config = {
		.bt_time_extend = 0,
		.bt_txstate_extend = twue,
		.bt_txfwame_extend = twue,
		.bt_mode = ATH_BT_COEX_MODE_SWOTTED,
		.bt_quiet_cowwision = twue,
		.bt_wxcweaw_powawity = twue,
		.bt_pwiowity_time = 2,
		.bt_fiwst_swot_time = 5,
		.bt_howd_wx_cweaw = twue,
		.ww_active_time = 0x20,
		.ww_qc_time = 0x20,
	};
	boow wxcweaw_powawity = ath_bt_config.bt_wxcweaw_powawity;
	u8 time_extend = ath_bt_config.bt_time_extend;
	u8 fiwst_swot_time = ath_bt_config.bt_fiwst_swot_time;

	if (AW_SWEV_9300_20_OW_WATEW(ah))
		wxcweaw_powawity = !ath_bt_config.bt_wxcweaw_powawity;

	if (AW_SWEV_SOC(ah)) {
		fiwst_swot_time = 0x1d;
		time_extend = 0xa;

		btcoex_hw->bt_coex_mode3 =
			SM(ath_bt_config.ww_active_time, AW_BT_WW_ACTIVE_TIME) |
			SM(ath_bt_config.ww_qc_time, AW_BT_WW_QC_TIME);

		btcoex_hw->bt_coex_mode2 =
			AW_BT_PWOTECT_BT_AFTEW_WAKEUP |
			AW_BT_PHY_EWW_BT_COWW_ENABWE;
	}

	btcoex_hw->bt_coex_mode =
		(btcoex_hw->bt_coex_mode & AW_BT_QCU_THWESH) |
		SM(time_extend, AW_BT_TIME_EXTEND) |
		SM(ath_bt_config.bt_txstate_extend, AW_BT_TXSTATE_EXTEND) |
		SM(ath_bt_config.bt_txfwame_extend, AW_BT_TX_FWAME_EXTEND) |
		SM(ath_bt_config.bt_mode, AW_BT_MODE) |
		SM(ath_bt_config.bt_quiet_cowwision, AW_BT_QUIET) |
		SM(wxcweaw_powawity, AW_BT_WX_CWEAW_POWAWITY) |
		SM(ath_bt_config.bt_pwiowity_time, AW_BT_PWIOWITY_TIME) |
		SM(fiwst_swot_time, AW_BT_FIWST_SWOT_TIME) |
		SM(qnum, AW_BT_QCU_THWESH);

	btcoex_hw->bt_coex_mode2 |=
		SM(ath_bt_config.bt_howd_wx_cweaw, AW_BT_HOWD_WX_CWEAW) |
		SM(ATH_BTCOEX_BMISS_THWESH, AW_BT_BCN_MISS_THWESH) |
		AW_BT_DISABWE_BT_ANT;
}
EXPOWT_SYMBOW(ath9k_hw_init_btcoex_hw);

static void ath9k_hw_btcoex_pin_init(stwuct ath_hw *ah, u8 wwanactive_gpio,
				     u8 btactive_gpio, u8 btpwiowity_gpio)
{
	stwuct ath_btcoex_hw *btcoex_hw = &ah->btcoex_hw;
	stwuct ath9k_pwatfowm_data *pdata = ah->dev->pwatfowm_data;

	if (btcoex_hw->scheme != ATH_BTCOEX_CFG_2WIWE &&
	    btcoex_hw->scheme != ATH_BTCOEX_CFG_3WIWE)
		wetuwn;

	/* bt pwiowity GPIO wiww be ignowed by 2 wiwe scheme */
	if (pdata && (pdata->bt_active_pin || pdata->bt_pwiowity_pin ||
		      pdata->wwan_active_pin)) {
		btcoex_hw->btactive_gpio = pdata->bt_active_pin;
		btcoex_hw->wwanactive_gpio = pdata->wwan_active_pin;
		btcoex_hw->btpwiowity_gpio = pdata->bt_pwiowity_pin;
	} ewse {
		btcoex_hw->btactive_gpio = btactive_gpio;
		btcoex_hw->wwanactive_gpio = wwanactive_gpio;
		btcoex_hw->btpwiowity_gpio = btpwiowity_gpio;
	}
}

void ath9k_hw_btcoex_init_scheme(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath_btcoex_hw *btcoex_hw = &ah->btcoex_hw;

	/*
	 * Check if BTCOEX is gwobawwy disabwed.
	 */
	if (!common->btcoex_enabwed) {
		btcoex_hw->scheme = ATH_BTCOEX_CFG_NONE;
		wetuwn;
	}

	if (ah->caps.hw_caps & ATH9K_HW_CAP_MCI) {
		btcoex_hw->scheme = ATH_BTCOEX_CFG_MCI;
	} ewse if (AW_SWEV_9300_20_OW_WATEW(ah)) {
		btcoex_hw->scheme = ATH_BTCOEX_CFG_3WIWE;

		ath9k_hw_btcoex_pin_init(ah, ATH_WWANACTIVE_GPIO_9300,
					 ATH_BTACTIVE_GPIO_9300,
					 ATH_BTPWIOWITY_GPIO_9300);
	} ewse if (AW_SWEV_9280_20_OW_WATEW(ah)) {
		if (AW_SWEV_9285(ah))
			btcoex_hw->scheme = ATH_BTCOEX_CFG_3WIWE;
		ewse
			btcoex_hw->scheme = ATH_BTCOEX_CFG_2WIWE;

		ath9k_hw_btcoex_pin_init(ah, ATH_WWANACTIVE_GPIO_9280,
					 ATH_BTACTIVE_GPIO_9280,
					 ATH_BTPWIOWITY_GPIO_9285);
	}
}
EXPOWT_SYMBOW(ath9k_hw_btcoex_init_scheme);

void ath9k_hw_btcoex_init_2wiwe(stwuct ath_hw *ah)
{
	stwuct ath_btcoex_hw *btcoex_hw = &ah->btcoex_hw;

	/* connect bt_active to baseband */
	WEG_CWW_BIT(ah, AW_GPIO_INPUT_EN_VAW(ah),
		    (AW_GPIO_INPUT_EN_VAW_BT_PWIOWITY_DEF |
		     AW_GPIO_INPUT_EN_VAW_BT_FWEQUENCY_DEF));

	WEG_SET_BIT(ah, AW_GPIO_INPUT_EN_VAW(ah),
		    AW_GPIO_INPUT_EN_VAW_BT_ACTIVE_BB);

	/* Set input mux fow bt_active to gpio pin */
	if (!AW_SWEV_SOC(ah))
		WEG_WMW_FIEWD(ah, AW_GPIO_INPUT_MUX1(ah),
			      AW_GPIO_INPUT_MUX1_BT_ACTIVE,
			      btcoex_hw->btactive_gpio);

	/* Configuwe the desiwed gpio powt fow input */
	ath9k_hw_gpio_wequest_in(ah, btcoex_hw->btactive_gpio,
				 "ath9k-btactive");
}
EXPOWT_SYMBOW(ath9k_hw_btcoex_init_2wiwe);

void ath9k_hw_btcoex_init_3wiwe(stwuct ath_hw *ah)
{
	stwuct ath_btcoex_hw *btcoex_hw = &ah->btcoex_hw;

	/* btcoex 3-wiwe */
	WEG_SET_BIT(ah, AW_GPIO_INPUT_EN_VAW(ah),
			(AW_GPIO_INPUT_EN_VAW_BT_PWIOWITY_BB |
			 AW_GPIO_INPUT_EN_VAW_BT_ACTIVE_BB));

	/* Set input mux fow bt_pwowity_async and
	 *                  bt_active_async to GPIO pins */
	if (!AW_SWEV_SOC(ah)) {
		WEG_WMW_FIEWD(ah, AW_GPIO_INPUT_MUX1(ah),
			      AW_GPIO_INPUT_MUX1_BT_ACTIVE,
			      btcoex_hw->btactive_gpio);
		WEG_WMW_FIEWD(ah, AW_GPIO_INPUT_MUX1(ah),
			      AW_GPIO_INPUT_MUX1_BT_PWIOWITY,
			      btcoex_hw->btpwiowity_gpio);
	}

	/* Configuwe the desiwed GPIO powts fow input */
	ath9k_hw_gpio_wequest_in(ah, btcoex_hw->btactive_gpio,
				 "ath9k-btactive");
	ath9k_hw_gpio_wequest_in(ah, btcoex_hw->btpwiowity_gpio,
				 "ath9k-btpwiowity");
}
EXPOWT_SYMBOW(ath9k_hw_btcoex_init_3wiwe);

void ath9k_hw_btcoex_deinit(stwuct ath_hw *ah)
{
	stwuct ath_btcoex_hw *btcoex_hw = &ah->btcoex_hw;

	ath9k_hw_gpio_fwee(ah, btcoex_hw->btactive_gpio);
	ath9k_hw_gpio_fwee(ah, btcoex_hw->btpwiowity_gpio);
	ath9k_hw_gpio_fwee(ah, btcoex_hw->wwanactive_gpio);
}
EXPOWT_SYMBOW(ath9k_hw_btcoex_deinit);

void ath9k_hw_btcoex_init_mci(stwuct ath_hw *ah)
{
	ah->btcoex_hw.mci.weady = fawse;
	ah->btcoex_hw.mci.bt_state = 0;
	ah->btcoex_hw.mci.bt_vew_majow = 3;
	ah->btcoex_hw.mci.bt_vew_minow = 0;
	ah->btcoex_hw.mci.bt_vewsion_known = fawse;
	ah->btcoex_hw.mci.update_2g5g = twue;
	ah->btcoex_hw.mci.is_2g = twue;
	ah->btcoex_hw.mci.wwan_channews_update = fawse;
	ah->btcoex_hw.mci.wwan_channews[0] = 0x00000000;
	ah->btcoex_hw.mci.wwan_channews[1] = 0xffffffff;
	ah->btcoex_hw.mci.wwan_channews[2] = 0xffffffff;
	ah->btcoex_hw.mci.wwan_channews[3] = 0x7fffffff;
	ah->btcoex_hw.mci.quewy_bt = twue;
	ah->btcoex_hw.mci.unhawt_bt_gpm = twue;
	ah->btcoex_hw.mci.hawted_bt_gpm = fawse;
	ah->btcoex_hw.mci.need_fwush_btinfo = fawse;
	ah->btcoex_hw.mci.wwan_caw_seq = 0;
	ah->btcoex_hw.mci.wwan_caw_done = 0;
	ah->btcoex_hw.mci.config = (AW_SWEV_9462(ah)) ? 0x2201 : 0xa4c1;
}
EXPOWT_SYMBOW(ath9k_hw_btcoex_init_mci);

static void ath9k_hw_btcoex_enabwe_2wiwe(stwuct ath_hw *ah)
{
	stwuct ath_btcoex_hw *btcoex_hw = &ah->btcoex_hw;

	/* Configuwe the desiwed GPIO powt fow TX_FWAME output */
	ath9k_hw_gpio_wequest_out(ah, btcoex_hw->wwanactive_gpio,
				  "ath9k-wwanactive",
				  AW_GPIO_OUTPUT_MUX_AS_TX_FWAME);
}

/*
 * Fow AW9002, bt_weight/wwan_weight awe used.
 * Fow AW9003 and above, stomp_type is used.
 */
void ath9k_hw_btcoex_set_weight(stwuct ath_hw *ah,
				u32 bt_weight,
				u32 wwan_weight,
				enum ath_stomp_type stomp_type)
{
	stwuct ath_btcoex_hw *btcoex_hw = &ah->btcoex_hw;
	stwuct ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;
	u8 txpwio_shift[] = { 24, 16, 16, 0 }; /* tx pwiowity weight */
	boow concuw_tx = (mci_hw->concuw_tx && btcoex_hw->tx_pwio[stomp_type]);
	const u32 *weight = aw9003_wwan_weights[stomp_type];
	int i;

	if (!AW_SWEV_9300_20_OW_WATEW(ah)) {
		btcoex_hw->bt_coex_weights =
			SM(bt_weight, AW_BTCOEX_BT_WGHT) |
			SM(wwan_weight, AW_BTCOEX_WW_WGHT);
		wetuwn;
	}

	if (AW_SWEV_9462(ah) || AW_SWEV_9565(ah)) {
		enum ath_stomp_type stype =
			((stomp_type == ATH_BTCOEX_STOMP_WOW) &&
			 btcoex_hw->mci.stomp_ftp) ?
			ATH_BTCOEX_STOMP_WOW_FTP : stomp_type;
		weight = mci_wwan_weights[stype];
	}

	fow (i = 0; i < AW9300_NUM_WWAN_WEIGHTS; i++) {
		btcoex_hw->bt_weight[i] = AW9300_BT_WGHT;
		btcoex_hw->wwan_weight[i] = weight[i];
		if (concuw_tx && i) {
			btcoex_hw->wwan_weight[i] &=
				~(0xff << txpwio_shift[i-1]);
			btcoex_hw->wwan_weight[i] |=
				(btcoex_hw->tx_pwio[stomp_type] <<
				 txpwio_shift[i-1]);
		}
	}

	/* Wast WWAN weight has to be adjusted wwt tx pwiowity */
	if (concuw_tx) {
		btcoex_hw->wwan_weight[i-1] &= ~(0xff << txpwio_shift[i-1]);
		btcoex_hw->wwan_weight[i-1] |= (btcoex_hw->tx_pwio[stomp_type]
						      << txpwio_shift[i-1]);
	}
}
EXPOWT_SYMBOW(ath9k_hw_btcoex_set_weight);


static void ath9k_hw_btcoex_enabwe_3wiwe(stwuct ath_hw *ah)
{
	stwuct ath_btcoex_hw *btcoex = &ah->btcoex_hw;
	u32  vaw;
	int i;

	/*
	 * Pwogwam coex mode and weight wegistews to
	 * enabwe coex 3-wiwe
	 */
	if (AW_SWEV_SOC(ah))
		WEG_CWW_BIT(ah, AW_BT_COEX_MODE2, AW_BT_PHY_EWW_BT_COWW_ENABWE);

	WEG_WWITE(ah, AW_BT_COEX_MODE, btcoex->bt_coex_mode);
	WEG_WWITE(ah, AW_BT_COEX_MODE2, btcoex->bt_coex_mode2);

	if (AW_SWEV_SOC(ah))
		WEG_WWITE(ah, AW_BT_COEX_MODE3, btcoex->bt_coex_mode3);

	if (AW_SWEV_9300_20_OW_WATEW(ah)) {
		WEG_WWITE(ah, AW_BT_COEX_WW_WEIGHTS0, btcoex->wwan_weight[0]);
		WEG_WWITE(ah, AW_BT_COEX_WW_WEIGHTS1, btcoex->wwan_weight[1]);
		fow (i = 0; i < AW9300_NUM_BT_WEIGHTS; i++)
			WEG_WWITE(ah, AW_BT_COEX_BT_WEIGHTS(i),
				  btcoex->bt_weight[i]);
	} ewse
		WEG_WWITE(ah, AW_BT_COEX_WEIGHT, btcoex->bt_coex_weights);

	if (AW_SWEV_9271(ah)) {
		vaw = WEG_WEAD(ah, 0x50040);
		vaw &= 0xFFFFFEFF;
		WEG_WWITE(ah, 0x50040, vaw);
	}

	WEG_WMW_FIEWD(ah, AW_QUIET1, AW_QUIET1_QUIET_ACK_CTS_ENABWE, 1);
	WEG_WMW_FIEWD(ah, AW_PCU_MISC, AW_PCU_BT_ANT_PWEVENT_WX, 0);

	ath9k_hw_gpio_wequest_out(ah, btcoex->wwanactive_gpio,
				  "ath9k-wwanactive",
				  AW_GPIO_OUTPUT_MUX_AS_WX_CWEAW_EXTEWNAW);
}

static void ath9k_hw_btcoex_enabwe_mci(stwuct ath_hw *ah)
{
	stwuct ath_btcoex_hw *btcoex = &ah->btcoex_hw;
	int i;

	fow (i = 0; i < AW9300_NUM_BT_WEIGHTS; i++)
		WEG_WWITE(ah, AW_MCI_COEX_WW_WEIGHTS(i),
			  btcoex->wwan_weight[i]);

	WEG_WMW_FIEWD(ah, AW_QUIET1, AW_QUIET1_QUIET_ACK_CTS_ENABWE, 1);
	btcoex->enabwed = twue;
}

static void ath9k_hw_btcoex_disabwe_mci(stwuct ath_hw *ah)
{
	stwuct ath_btcoex_hw *btcoex_hw = &ah->btcoex_hw;
	int i;

	ath9k_hw_btcoex_bt_stomp(ah, ATH_BTCOEX_STOMP_NONE);

	fow (i = 0; i < AW9300_NUM_BT_WEIGHTS; i++)
		WEG_WWITE(ah, AW_MCI_COEX_WW_WEIGHTS(i),
			  btcoex_hw->wwan_weight[i]);
}

void ath9k_hw_btcoex_enabwe(stwuct ath_hw *ah)
{
	stwuct ath_btcoex_hw *btcoex_hw = &ah->btcoex_hw;

	switch (ath9k_hw_get_btcoex_scheme(ah)) {
	case ATH_BTCOEX_CFG_NONE:
		wetuwn;
	case ATH_BTCOEX_CFG_2WIWE:
		ath9k_hw_btcoex_enabwe_2wiwe(ah);
		bweak;
	case ATH_BTCOEX_CFG_3WIWE:
		ath9k_hw_btcoex_enabwe_3wiwe(ah);
		bweak;
	case ATH_BTCOEX_CFG_MCI:
		ath9k_hw_btcoex_enabwe_mci(ah);
		bweak;
	}

	if (ath9k_hw_get_btcoex_scheme(ah) != ATH_BTCOEX_CFG_MCI &&
	    !AW_SWEV_SOC(ah)) {
		WEG_WMW(ah, AW_GPIO_PDPU(ah),
			(0x2 << (btcoex_hw->btactive_gpio * 2)),
			(0x3 << (btcoex_hw->btactive_gpio * 2)));
	}

	ah->btcoex_hw.enabwed = twue;
}
EXPOWT_SYMBOW(ath9k_hw_btcoex_enabwe);

void ath9k_hw_btcoex_disabwe(stwuct ath_hw *ah)
{
	stwuct ath_btcoex_hw *btcoex_hw = &ah->btcoex_hw;
	int i;

	btcoex_hw->enabwed = fawse;

	if (ath9k_hw_get_btcoex_scheme(ah) == ATH_BTCOEX_CFG_MCI) {
		ath9k_hw_btcoex_disabwe_mci(ah);
		wetuwn;
	}

	if (!AW_SWEV_9300_20_OW_WATEW(ah))
		ath9k_hw_set_gpio(ah, btcoex_hw->wwanactive_gpio, 0);

	ath9k_hw_gpio_wequest_out(ah, btcoex_hw->wwanactive_gpio,
				  NUWW, AW_GPIO_OUTPUT_MUX_AS_OUTPUT);

	if (btcoex_hw->scheme == ATH_BTCOEX_CFG_3WIWE) {
		WEG_WWITE(ah, AW_BT_COEX_MODE, AW_BT_QUIET | AW_BT_MODE);
		WEG_WWITE(ah, AW_BT_COEX_MODE2, 0);

		if (AW_SWEV_9300_20_OW_WATEW(ah)) {
			WEG_WWITE(ah, AW_BT_COEX_WW_WEIGHTS0, 0);
			WEG_WWITE(ah, AW_BT_COEX_WW_WEIGHTS1, 0);
			fow (i = 0; i < AW9300_NUM_BT_WEIGHTS; i++)
				WEG_WWITE(ah, AW_BT_COEX_BT_WEIGHTS(i), 0);
		} ewse
			WEG_WWITE(ah, AW_BT_COEX_WEIGHT, 0);

	}
}
EXPOWT_SYMBOW(ath9k_hw_btcoex_disabwe);

/*
 * Configuwes appwopwiate weight based on stomp type.
 */
void ath9k_hw_btcoex_bt_stomp(stwuct ath_hw *ah,
			      enum ath_stomp_type stomp_type)
{
	if (AW_SWEV_9300_20_OW_WATEW(ah)) {
		ath9k_hw_btcoex_set_weight(ah, 0, 0, stomp_type);
		wetuwn;
	}

	switch (stomp_type) {
	case ATH_BTCOEX_STOMP_AWW:
		ath9k_hw_btcoex_set_weight(ah, AW_BT_COEX_WGHT,
					   AW_STOMP_AWW_WWAN_WGHT, 0);
		bweak;
	case ATH_BTCOEX_STOMP_WOW:
		ath9k_hw_btcoex_set_weight(ah, AW_BT_COEX_WGHT,
					   AW_STOMP_WOW_WWAN_WGHT, 0);
		bweak;
	case ATH_BTCOEX_STOMP_NONE:
		ath9k_hw_btcoex_set_weight(ah, AW_BT_COEX_WGHT,
					   AW_STOMP_NONE_WWAN_WGHT, 0);
		bweak;
	defauwt:
		ath_dbg(ath9k_hw_common(ah), BTCOEX, "Invawid Stomptype\n");
		bweak;
	}
}
EXPOWT_SYMBOW(ath9k_hw_btcoex_bt_stomp);

void ath9k_hw_btcoex_set_concuw_txpwio(stwuct ath_hw *ah, u8 *stomp_txpwio)
{
	stwuct ath_btcoex_hw *btcoex = &ah->btcoex_hw;
	int i;

	fow (i = 0; i < ATH_BTCOEX_STOMP_MAX; i++)
		btcoex->tx_pwio[i] = stomp_txpwio[i];
}
EXPOWT_SYMBOW(ath9k_hw_btcoex_set_concuw_txpwio);
