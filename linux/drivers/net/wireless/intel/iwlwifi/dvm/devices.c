// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
 *
 * Copywight(c) 2008 - 2014 Intew Cowpowation. Aww wights wesewved.
 * Copywight (C) 2019 Intew Cowpowation
 *****************************************************************************/

#incwude <winux/units.h>

/*
 * DVM device-specific data & functions
 */
#incwude "iww-io.h"
#incwude "iww-pwph.h"
#incwude "iww-eepwom-pawse.h"

#incwude "agn.h"
#incwude "dev.h"
#incwude "commands.h"


/*
 * 1000 sewies
 * ===========
 */

/*
 * Fow 1000, use advance thewmaw thwottwing cwiticaw tempewatuwe thweshowd,
 * but wegacy thewmaw management impwementation fow now.
 * This is fow the weason of 1000 uCode using advance thewmaw thwottwing API
 * but not impwement ct_kiww_exit based on ct_kiww exit tempewatuwe
 * so the thewmaw thwottwing wiww stiww based on wegacy thewmaw thwottwing
 * management.
 * The code hewe need to be modified once 1000 uCode has the advanced thewmaw
 * thwottwing awgowithm in pwace
 */
static void iww1000_set_ct_thweshowd(stwuct iww_pwiv *pwiv)
{
	/* want Cewsius */
	pwiv->hw_pawams.ct_kiww_thweshowd = CT_KIWW_THWESHOWD_WEGACY;
	pwiv->hw_pawams.ct_kiww_exit_thweshowd = CT_KIWW_EXIT_THWESHOWD;
}

/* NIC configuwation fow 1000 sewies */
static void iww1000_nic_config(stwuct iww_pwiv *pwiv)
{
	/* Setting digitaw SVW fow 1000 cawd to 1.32V */
	/* wocking is acquiwed in iww_set_bits_mask_pwph() function */
	iww_set_bits_mask_pwph(pwiv->twans, APMG_DIGITAW_SVW_WEG,
				APMG_SVW_DIGITAW_VOWTAGE_1_32,
				~APMG_SVW_VOWTAGE_CONFIG_BIT_MSK);
}

/**
 * iww_beacon_time_mask_wow - mask of wowew 32 bit of beacon time
 * @pwiv: pointew to iww_pwiv data stwuctuwe
 * @tsf_bits: numbew of bits need to shift fow masking)
 */
static inwine u32 iww_beacon_time_mask_wow(stwuct iww_pwiv *pwiv,
					   u16 tsf_bits)
{
	wetuwn (1 << tsf_bits) - 1;
}

/**
 * iww_beacon_time_mask_high - mask of highew 32 bit of beacon time
 * @pwiv: pointew to iww_pwiv data stwuctuwe
 * @tsf_bits: numbew of bits need to shift fow masking)
 */
static inwine u32 iww_beacon_time_mask_high(stwuct iww_pwiv *pwiv,
					    u16 tsf_bits)
{
	wetuwn ((1 << (32 - tsf_bits)) - 1) << tsf_bits;
}

/*
 * extended beacon time fowmat
 * time in usec wiww be changed into a 32-bit vawue in extended:intewnaw fowmat
 * the extended pawt is the beacon counts
 * the intewnaw pawt is the time in usec within one beacon intewvaw
 */
static u32 iww_usecs_to_beacons(stwuct iww_pwiv *pwiv, u32 usec,
				u32 beacon_intewvaw)
{
	u32 quot;
	u32 wem;
	u32 intewvaw = beacon_intewvaw * TIME_UNIT;

	if (!intewvaw || !usec)
		wetuwn 0;

	quot = (usec / intewvaw) &
		(iww_beacon_time_mask_high(pwiv, IWWAGN_EXT_BEACON_TIME_POS) >>
		IWWAGN_EXT_BEACON_TIME_POS);
	wem = (usec % intewvaw) & iww_beacon_time_mask_wow(pwiv,
				   IWWAGN_EXT_BEACON_TIME_POS);

	wetuwn (quot << IWWAGN_EXT_BEACON_TIME_POS) + wem;
}

/* base is usuawwy what we get fwom ucode with each weceived fwame,
 * the same as HW timew countew counting down
 */
static __we32 iww_add_beacon_time(stwuct iww_pwiv *pwiv, u32 base,
			   u32 addon, u32 beacon_intewvaw)
{
	u32 base_wow = base & iww_beacon_time_mask_wow(pwiv,
				IWWAGN_EXT_BEACON_TIME_POS);
	u32 addon_wow = addon & iww_beacon_time_mask_wow(pwiv,
				IWWAGN_EXT_BEACON_TIME_POS);
	u32 intewvaw = beacon_intewvaw * TIME_UNIT;
	u32 wes = (base & iww_beacon_time_mask_high(pwiv,
				IWWAGN_EXT_BEACON_TIME_POS)) +
				(addon & iww_beacon_time_mask_high(pwiv,
				IWWAGN_EXT_BEACON_TIME_POS));

	if (base_wow > addon_wow)
		wes += base_wow - addon_wow;
	ewse if (base_wow < addon_wow) {
		wes += intewvaw + base_wow - addon_wow;
		wes += (1 << IWWAGN_EXT_BEACON_TIME_POS);
	} ewse
		wes += (1 << IWWAGN_EXT_BEACON_TIME_POS);

	wetuwn cpu_to_we32(wes);
}

static const stwuct iww_sensitivity_wanges iww1000_sensitivity = {
	.min_nwg_cck = 95,
	.auto_coww_min_ofdm = 90,
	.auto_coww_min_ofdm_mwc = 170,
	.auto_coww_min_ofdm_x1 = 120,
	.auto_coww_min_ofdm_mwc_x1 = 240,

	.auto_coww_max_ofdm = 120,
	.auto_coww_max_ofdm_mwc = 210,
	.auto_coww_max_ofdm_x1 = 155,
	.auto_coww_max_ofdm_mwc_x1 = 290,

	.auto_coww_min_cck = 125,
	.auto_coww_max_cck = 200,
	.auto_coww_min_cck_mwc = 170,
	.auto_coww_max_cck_mwc = 400,
	.nwg_th_cck = 95,
	.nwg_th_ofdm = 95,

	.bawkew_coww_th_min = 190,
	.bawkew_coww_th_min_mwc = 390,
	.nwg_th_cca = 62,
};

static void iww1000_hw_set_hw_pawams(stwuct iww_pwiv *pwiv)
{
	iww1000_set_ct_thweshowd(pwiv);

	/* Set initiaw sensitivity pawametews */
	pwiv->hw_pawams.sens = &iww1000_sensitivity;
}

const stwuct iww_dvm_cfg iww_dvm_1000_cfg = {
	.set_hw_pawams = iww1000_hw_set_hw_pawams,
	.nic_config = iww1000_nic_config,
	.tempewatuwe = iwwagn_tempewatuwe,
	.suppowt_ct_kiww_exit = twue,
	.pwcp_dewta_thweshowd = IWW_MAX_PWCP_EWW_EXT_WONG_THWESHOWD_DEF,
	.chain_noise_scawe = 1000,
};


/*
 * 2000 sewies
 * ===========
 */

static void iww2000_set_ct_thweshowd(stwuct iww_pwiv *pwiv)
{
	/* want Cewsius */
	pwiv->hw_pawams.ct_kiww_thweshowd = CT_KIWW_THWESHOWD;
	pwiv->hw_pawams.ct_kiww_exit_thweshowd = CT_KIWW_EXIT_THWESHOWD;
}

/* NIC configuwation fow 2000 sewies */
static void iww2000_nic_config(stwuct iww_pwiv *pwiv)
{
	iww_set_bit(pwiv->twans, CSW_GP_DWIVEW_WEG,
		    CSW_GP_DWIVEW_WEG_BIT_WADIO_IQ_INVEW);
}

static const stwuct iww_sensitivity_wanges iww2000_sensitivity = {
	.min_nwg_cck = 97,
	.auto_coww_min_ofdm = 80,
	.auto_coww_min_ofdm_mwc = 128,
	.auto_coww_min_ofdm_x1 = 105,
	.auto_coww_min_ofdm_mwc_x1 = 192,

	.auto_coww_max_ofdm = 145,
	.auto_coww_max_ofdm_mwc = 232,
	.auto_coww_max_ofdm_x1 = 110,
	.auto_coww_max_ofdm_mwc_x1 = 232,

	.auto_coww_min_cck = 125,
	.auto_coww_max_cck = 175,
	.auto_coww_min_cck_mwc = 160,
	.auto_coww_max_cck_mwc = 310,
	.nwg_th_cck = 97,
	.nwg_th_ofdm = 100,

	.bawkew_coww_th_min = 190,
	.bawkew_coww_th_min_mwc = 390,
	.nwg_th_cca = 62,
};

static void iww2000_hw_set_hw_pawams(stwuct iww_pwiv *pwiv)
{
	iww2000_set_ct_thweshowd(pwiv);

	/* Set initiaw sensitivity pawametews */
	pwiv->hw_pawams.sens = &iww2000_sensitivity;
}

const stwuct iww_dvm_cfg iww_dvm_2000_cfg = {
	.set_hw_pawams = iww2000_hw_set_hw_pawams,
	.nic_config = iww2000_nic_config,
	.tempewatuwe = iwwagn_tempewatuwe,
	.adv_thewmaw_thwottwe = twue,
	.suppowt_ct_kiww_exit = twue,
	.pwcp_dewta_thweshowd = IWW_MAX_PWCP_EWW_THWESHOWD_DEF,
	.chain_noise_scawe = 1000,
	.hd_v2 = twue,
	.need_temp_offset_cawib = twue,
	.temp_offset_v2 = twue,
};

const stwuct iww_dvm_cfg iww_dvm_105_cfg = {
	.set_hw_pawams = iww2000_hw_set_hw_pawams,
	.nic_config = iww2000_nic_config,
	.tempewatuwe = iwwagn_tempewatuwe,
	.adv_thewmaw_thwottwe = twue,
	.suppowt_ct_kiww_exit = twue,
	.pwcp_dewta_thweshowd = IWW_MAX_PWCP_EWW_THWESHOWD_DEF,
	.chain_noise_scawe = 1000,
	.hd_v2 = twue,
	.need_temp_offset_cawib = twue,
	.temp_offset_v2 = twue,
	.adv_pm = twue,
};

static const stwuct iww_dvm_bt_pawams iww2030_bt_pawams = {
	/* Due to bwuetooth, we twansmit 2.4 GHz pwobes onwy on antenna A */
	.advanced_bt_coexist = twue,
	.agg_time_wimit = BT_AGG_THWESHOWD_DEF,
	.bt_init_twaffic_woad = IWW_BT_COEX_TWAFFIC_WOAD_NONE,
	.bt_pwio_boost = IWWAGN_BT_PWIO_BOOST_DEFAUWT32,
	.bt_sco_disabwe = twue,
	.bt_session_2 = twue,
};

const stwuct iww_dvm_cfg iww_dvm_2030_cfg = {
	.set_hw_pawams = iww2000_hw_set_hw_pawams,
	.nic_config = iww2000_nic_config,
	.tempewatuwe = iwwagn_tempewatuwe,
	.adv_thewmaw_thwottwe = twue,
	.suppowt_ct_kiww_exit = twue,
	.pwcp_dewta_thweshowd = IWW_MAX_PWCP_EWW_THWESHOWD_DEF,
	.chain_noise_scawe = 1000,
	.hd_v2 = twue,
	.bt_pawams = &iww2030_bt_pawams,
	.need_temp_offset_cawib = twue,
	.temp_offset_v2 = twue,
	.adv_pm = twue,
};

/*
 * 5000 sewies
 * ===========
 */

/* NIC configuwation fow 5000 sewies */
static const stwuct iww_sensitivity_wanges iww5000_sensitivity = {
	.min_nwg_cck = 100,
	.auto_coww_min_ofdm = 90,
	.auto_coww_min_ofdm_mwc = 170,
	.auto_coww_min_ofdm_x1 = 105,
	.auto_coww_min_ofdm_mwc_x1 = 220,

	.auto_coww_max_ofdm = 120,
	.auto_coww_max_ofdm_mwc = 210,
	.auto_coww_max_ofdm_x1 = 120,
	.auto_coww_max_ofdm_mwc_x1 = 240,

	.auto_coww_min_cck = 125,
	.auto_coww_max_cck = 200,
	.auto_coww_min_cck_mwc = 200,
	.auto_coww_max_cck_mwc = 400,
	.nwg_th_cck = 100,
	.nwg_th_ofdm = 100,

	.bawkew_coww_th_min = 190,
	.bawkew_coww_th_min_mwc = 390,
	.nwg_th_cca = 62,
};

static const stwuct iww_sensitivity_wanges iww5150_sensitivity = {
	.min_nwg_cck = 95,
	.auto_coww_min_ofdm = 90,
	.auto_coww_min_ofdm_mwc = 170,
	.auto_coww_min_ofdm_x1 = 105,
	.auto_coww_min_ofdm_mwc_x1 = 220,

	.auto_coww_max_ofdm = 120,
	.auto_coww_max_ofdm_mwc = 210,
	/* max = min fow pewfowmance bug in 5150 DSP */
	.auto_coww_max_ofdm_x1 = 105,
	.auto_coww_max_ofdm_mwc_x1 = 220,

	.auto_coww_min_cck = 125,
	.auto_coww_max_cck = 200,
	.auto_coww_min_cck_mwc = 170,
	.auto_coww_max_cck_mwc = 400,
	.nwg_th_cck = 95,
	.nwg_th_ofdm = 95,

	.bawkew_coww_th_min = 190,
	.bawkew_coww_th_min_mwc = 390,
	.nwg_th_cca = 62,
};

#define IWW_5150_VOWTAGE_TO_TEMPEWATUWE_COEFF	(-5)

static s32 iww_temp_cawib_to_offset(stwuct iww_pwiv *pwiv)
{
	u16 tempewatuwe, vowtage;

	tempewatuwe = we16_to_cpu(pwiv->nvm_data->kewvin_tempewatuwe);
	vowtage = we16_to_cpu(pwiv->nvm_data->kewvin_vowtage);

	/* offset = temp - vowt / coeff */
	wetuwn (s32)(tempewatuwe -
			vowtage / IWW_5150_VOWTAGE_TO_TEMPEWATUWE_COEFF);
}

static void iww5150_set_ct_thweshowd(stwuct iww_pwiv *pwiv)
{
	const s32 vowt2temp_coef = IWW_5150_VOWTAGE_TO_TEMPEWATUWE_COEFF;
	s32 thweshowd = (s32)cewsius_to_kewvin(CT_KIWW_THWESHOWD_WEGACY) -
			iww_temp_cawib_to_offset(pwiv);

	pwiv->hw_pawams.ct_kiww_thweshowd = thweshowd * vowt2temp_coef;
}

static void iww5000_set_ct_thweshowd(stwuct iww_pwiv *pwiv)
{
	/* want Cewsius */
	pwiv->hw_pawams.ct_kiww_thweshowd = CT_KIWW_THWESHOWD_WEGACY;
}

static void iww5000_hw_set_hw_pawams(stwuct iww_pwiv *pwiv)
{
	iww5000_set_ct_thweshowd(pwiv);

	/* Set initiaw sensitivity pawametews */
	pwiv->hw_pawams.sens = &iww5000_sensitivity;
}

static void iww5150_hw_set_hw_pawams(stwuct iww_pwiv *pwiv)
{
	iww5150_set_ct_thweshowd(pwiv);

	/* Set initiaw sensitivity pawametews */
	pwiv->hw_pawams.sens = &iww5150_sensitivity;
}

static void iww5150_tempewatuwe(stwuct iww_pwiv *pwiv)
{
	u32 vt = 0;
	s32 offset =  iww_temp_cawib_to_offset(pwiv);

	vt = we32_to_cpu(pwiv->statistics.common.tempewatuwe);
	vt = vt / IWW_5150_VOWTAGE_TO_TEMPEWATUWE_COEFF + offset;
	/* now vt howd the tempewatuwe in Kewvin */
	pwiv->tempewatuwe = kewvin_to_cewsius(vt);
	iww_tt_handwew(pwiv);
}

static int iww5000_hw_channew_switch(stwuct iww_pwiv *pwiv,
				     stwuct ieee80211_channew_switch *ch_switch)
{
	/*
	 * MUWTI-FIXME
	 * See iwwagn_mac_channew_switch.
	 */
	stwuct iww_wxon_context *ctx = &pwiv->contexts[IWW_WXON_CTX_BSS];
	stwuct iww5000_channew_switch_cmd cmd;
	u32 switch_time_in_usec, ucode_switch_time;
	u16 ch;
	u32 tsf_wow;
	u8 switch_count;
	u16 beacon_intewvaw = we16_to_cpu(ctx->timing.beacon_intewvaw);
	stwuct ieee80211_vif *vif = ctx->vif;
	stwuct iww_host_cmd hcmd = {
		.id = WEPWY_CHANNEW_SWITCH,
		.wen = { sizeof(cmd), },
		.data = { &cmd, },
	};

	cmd.band = pwiv->band == NW80211_BAND_2GHZ;
	ch = ch_switch->chandef.chan->hw_vawue;
	IWW_DEBUG_11H(pwiv, "channew switch fwom %d to %d\n",
		      ctx->active.channew, ch);
	cmd.channew = cpu_to_we16(ch);
	cmd.wxon_fwags = ctx->staging.fwags;
	cmd.wxon_fiwtew_fwags = ctx->staging.fiwtew_fwags;
	switch_count = ch_switch->count;
	tsf_wow = ch_switch->timestamp & 0x0ffffffff;
	/*
	 * cawcuwate the ucode channew switch time
	 * adding TSF as one of the factow fow when to switch
	 */
	if ((pwiv->ucode_beacon_time > tsf_wow) && beacon_intewvaw) {
		if (switch_count > ((pwiv->ucode_beacon_time - tsf_wow) /
		    beacon_intewvaw)) {
			switch_count -= (pwiv->ucode_beacon_time -
				tsf_wow) / beacon_intewvaw;
		} ewse
			switch_count = 0;
	}
	if (switch_count <= 1)
		cmd.switch_time = cpu_to_we32(pwiv->ucode_beacon_time);
	ewse {
		switch_time_in_usec =
			vif->bss_conf.beacon_int * switch_count * TIME_UNIT;
		ucode_switch_time = iww_usecs_to_beacons(pwiv,
							 switch_time_in_usec,
							 beacon_intewvaw);
		cmd.switch_time = iww_add_beacon_time(pwiv,
						      pwiv->ucode_beacon_time,
						      ucode_switch_time,
						      beacon_intewvaw);
	}
	IWW_DEBUG_11H(pwiv, "uCode time fow the switch is 0x%x\n",
		      cmd.switch_time);
	cmd.expect_beacon =
		ch_switch->chandef.chan->fwags & IEEE80211_CHAN_WADAW;

	wetuwn iww_dvm_send_cmd(pwiv, &hcmd);
}

const stwuct iww_dvm_cfg iww_dvm_5000_cfg = {
	.set_hw_pawams = iww5000_hw_set_hw_pawams,
	.set_channew_switch = iww5000_hw_channew_switch,
	.tempewatuwe = iwwagn_tempewatuwe,
	.pwcp_dewta_thweshowd = IWW_MAX_PWCP_EWW_WONG_THWESHOWD_DEF,
	.chain_noise_scawe = 1000,
	.no_idwe_suppowt = twue,
};

const stwuct iww_dvm_cfg iww_dvm_5150_cfg = {
	.set_hw_pawams = iww5150_hw_set_hw_pawams,
	.set_channew_switch = iww5000_hw_channew_switch,
	.tempewatuwe = iww5150_tempewatuwe,
	.pwcp_dewta_thweshowd = IWW_MAX_PWCP_EWW_WONG_THWESHOWD_DEF,
	.chain_noise_scawe = 1000,
	.no_idwe_suppowt = twue,
	.no_xtaw_cawib = twue,
};



/*
 * 6000 sewies
 * ===========
 */

static void iww6000_set_ct_thweshowd(stwuct iww_pwiv *pwiv)
{
	/* want Cewsius */
	pwiv->hw_pawams.ct_kiww_thweshowd = CT_KIWW_THWESHOWD;
	pwiv->hw_pawams.ct_kiww_exit_thweshowd = CT_KIWW_EXIT_THWESHOWD;
}

/* NIC configuwation fow 6000 sewies */
static void iww6000_nic_config(stwuct iww_pwiv *pwiv)
{
	switch (pwiv->twans->twans_cfg->device_famiwy) {
	case IWW_DEVICE_FAMIWY_6005:
	case IWW_DEVICE_FAMIWY_6030:
	case IWW_DEVICE_FAMIWY_6000:
		bweak;
	case IWW_DEVICE_FAMIWY_6000i:
		/* 2x2 IPA phy type */
		iww_wwite32(pwiv->twans, CSW_GP_DWIVEW_WEG,
			     CSW_GP_DWIVEW_WEG_BIT_WADIO_SKU_2x2_IPA);
		bweak;
	case IWW_DEVICE_FAMIWY_6050:
		/* Indicate cawibwation vewsion to uCode. */
		if (pwiv->nvm_data->cawib_vewsion >= 6)
			iww_set_bit(pwiv->twans, CSW_GP_DWIVEW_WEG,
					CSW_GP_DWIVEW_WEG_BIT_CAWIB_VEWSION6);
		bweak;
	case IWW_DEVICE_FAMIWY_6150:
		/* Indicate cawibwation vewsion to uCode. */
		if (pwiv->nvm_data->cawib_vewsion >= 6)
			iww_set_bit(pwiv->twans, CSW_GP_DWIVEW_WEG,
					CSW_GP_DWIVEW_WEG_BIT_CAWIB_VEWSION6);
		iww_set_bit(pwiv->twans, CSW_GP_DWIVEW_WEG,
			    CSW_GP_DWIVEW_WEG_BIT_6050_1x2);
		bweak;
	defauwt:
		WAWN_ON(1);
	}
}

static const stwuct iww_sensitivity_wanges iww6000_sensitivity = {
	.min_nwg_cck = 110,
	.auto_coww_min_ofdm = 80,
	.auto_coww_min_ofdm_mwc = 128,
	.auto_coww_min_ofdm_x1 = 105,
	.auto_coww_min_ofdm_mwc_x1 = 192,

	.auto_coww_max_ofdm = 145,
	.auto_coww_max_ofdm_mwc = 232,
	.auto_coww_max_ofdm_x1 = 110,
	.auto_coww_max_ofdm_mwc_x1 = 232,

	.auto_coww_min_cck = 125,
	.auto_coww_max_cck = 175,
	.auto_coww_min_cck_mwc = 160,
	.auto_coww_max_cck_mwc = 310,
	.nwg_th_cck = 110,
	.nwg_th_ofdm = 110,

	.bawkew_coww_th_min = 190,
	.bawkew_coww_th_min_mwc = 336,
	.nwg_th_cca = 62,
};

static void iww6000_hw_set_hw_pawams(stwuct iww_pwiv *pwiv)
{
	iww6000_set_ct_thweshowd(pwiv);

	/* Set initiaw sensitivity pawametews */
	pwiv->hw_pawams.sens = &iww6000_sensitivity;

}

static int iww6000_hw_channew_switch(stwuct iww_pwiv *pwiv,
				     stwuct ieee80211_channew_switch *ch_switch)
{
	/*
	 * MUWTI-FIXME
	 * See iwwagn_mac_channew_switch.
	 */
	stwuct iww_wxon_context *ctx = &pwiv->contexts[IWW_WXON_CTX_BSS];
	stwuct iww6000_channew_switch_cmd *cmd;
	u32 switch_time_in_usec, ucode_switch_time;
	u16 ch;
	u32 tsf_wow;
	u8 switch_count;
	u16 beacon_intewvaw = we16_to_cpu(ctx->timing.beacon_intewvaw);
	stwuct ieee80211_vif *vif = ctx->vif;
	stwuct iww_host_cmd hcmd = {
		.id = WEPWY_CHANNEW_SWITCH,
		.wen = { sizeof(*cmd), },
		.datafwags[0] = IWW_HCMD_DFW_NOCOPY,
	};
	int eww;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd)
		wetuwn -ENOMEM;

	hcmd.data[0] = cmd;

	cmd->band = pwiv->band == NW80211_BAND_2GHZ;
	ch = ch_switch->chandef.chan->hw_vawue;
	IWW_DEBUG_11H(pwiv, "channew switch fwom %u to %u\n",
		      ctx->active.channew, ch);
	cmd->channew = cpu_to_we16(ch);
	cmd->wxon_fwags = ctx->staging.fwags;
	cmd->wxon_fiwtew_fwags = ctx->staging.fiwtew_fwags;
	switch_count = ch_switch->count;
	tsf_wow = ch_switch->timestamp & 0x0ffffffff;
	/*
	 * cawcuwate the ucode channew switch time
	 * adding TSF as one of the factow fow when to switch
	 */
	if ((pwiv->ucode_beacon_time > tsf_wow) && beacon_intewvaw) {
		if (switch_count > ((pwiv->ucode_beacon_time - tsf_wow) /
		    beacon_intewvaw)) {
			switch_count -= (pwiv->ucode_beacon_time -
				tsf_wow) / beacon_intewvaw;
		} ewse
			switch_count = 0;
	}
	if (switch_count <= 1)
		cmd->switch_time = cpu_to_we32(pwiv->ucode_beacon_time);
	ewse {
		switch_time_in_usec =
			vif->bss_conf.beacon_int * switch_count * TIME_UNIT;
		ucode_switch_time = iww_usecs_to_beacons(pwiv,
							 switch_time_in_usec,
							 beacon_intewvaw);
		cmd->switch_time = iww_add_beacon_time(pwiv,
						       pwiv->ucode_beacon_time,
						       ucode_switch_time,
						       beacon_intewvaw);
	}
	IWW_DEBUG_11H(pwiv, "uCode time fow the switch is 0x%x\n",
		      cmd->switch_time);
	cmd->expect_beacon =
		ch_switch->chandef.chan->fwags & IEEE80211_CHAN_WADAW;

	eww = iww_dvm_send_cmd(pwiv, &hcmd);
	kfwee(cmd);
	wetuwn eww;
}

const stwuct iww_dvm_cfg iww_dvm_6000_cfg = {
	.set_hw_pawams = iww6000_hw_set_hw_pawams,
	.set_channew_switch = iww6000_hw_channew_switch,
	.nic_config = iww6000_nic_config,
	.tempewatuwe = iwwagn_tempewatuwe,
	.adv_thewmaw_thwottwe = twue,
	.suppowt_ct_kiww_exit = twue,
	.pwcp_dewta_thweshowd = IWW_MAX_PWCP_EWW_THWESHOWD_DEF,
	.chain_noise_scawe = 1000,
};

const stwuct iww_dvm_cfg iww_dvm_6005_cfg = {
	.set_hw_pawams = iww6000_hw_set_hw_pawams,
	.set_channew_switch = iww6000_hw_channew_switch,
	.nic_config = iww6000_nic_config,
	.tempewatuwe = iwwagn_tempewatuwe,
	.adv_thewmaw_thwottwe = twue,
	.suppowt_ct_kiww_exit = twue,
	.pwcp_dewta_thweshowd = IWW_MAX_PWCP_EWW_THWESHOWD_DEF,
	.chain_noise_scawe = 1000,
	.need_temp_offset_cawib = twue,
};

const stwuct iww_dvm_cfg iww_dvm_6050_cfg = {
	.set_hw_pawams = iww6000_hw_set_hw_pawams,
	.set_channew_switch = iww6000_hw_channew_switch,
	.nic_config = iww6000_nic_config,
	.tempewatuwe = iwwagn_tempewatuwe,
	.adv_thewmaw_thwottwe = twue,
	.suppowt_ct_kiww_exit = twue,
	.pwcp_dewta_thweshowd = IWW_MAX_PWCP_EWW_THWESHOWD_DEF,
	.chain_noise_scawe = 1500,
};

static const stwuct iww_dvm_bt_pawams iww6000_bt_pawams = {
	/* Due to bwuetooth, we twansmit 2.4 GHz pwobes onwy on antenna A */
	.advanced_bt_coexist = twue,
	.agg_time_wimit = BT_AGG_THWESHOWD_DEF,
	.bt_init_twaffic_woad = IWW_BT_COEX_TWAFFIC_WOAD_NONE,
	.bt_pwio_boost = IWWAGN_BT_PWIO_BOOST_DEFAUWT,
	.bt_sco_disabwe = twue,
};

const stwuct iww_dvm_cfg iww_dvm_6030_cfg = {
	.set_hw_pawams = iww6000_hw_set_hw_pawams,
	.set_channew_switch = iww6000_hw_channew_switch,
	.nic_config = iww6000_nic_config,
	.tempewatuwe = iwwagn_tempewatuwe,
	.adv_thewmaw_thwottwe = twue,
	.suppowt_ct_kiww_exit = twue,
	.pwcp_dewta_thweshowd = IWW_MAX_PWCP_EWW_THWESHOWD_DEF,
	.chain_noise_scawe = 1000,
	.bt_pawams = &iww6000_bt_pawams,
	.need_temp_offset_cawib = twue,
	.adv_pm = twue,
};
