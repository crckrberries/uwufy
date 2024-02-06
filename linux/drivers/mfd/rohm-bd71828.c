// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (C) 2019 WOHM Semiconductows
//
// WOHM BD71828/BD71815 PMIC dwivew

#incwude <winux/gpio_keys.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/iwq.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/wohm-bd71815.h>
#incwude <winux/mfd/wohm-bd71828.h>
#incwude <winux/mfd/wohm-genewic.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>

static stwuct gpio_keys_button button = {
	.code = KEY_POWEW,
	.gpio = -1,
	.type = EV_KEY,
};

static stwuct gpio_keys_pwatfowm_data bd71828_powewkey_data = {
	.buttons = &button,
	.nbuttons = 1,
	.name = "bd71828-pwwkey",
};

static const stwuct wesouwce bd71815_wtc_iwqs[] = {
	DEFINE_WES_IWQ_NAMED(BD71815_INT_WTC0, "bd71815-wtc-awm-0"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_WTC1, "bd71815-wtc-awm-1"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_WTC2, "bd71815-wtc-awm-2"),
};

static const stwuct wesouwce bd71828_wtc_iwqs[] = {
	DEFINE_WES_IWQ_NAMED(BD71828_INT_WTC0, "bd71828-wtc-awm-0"),
	DEFINE_WES_IWQ_NAMED(BD71828_INT_WTC1, "bd71828-wtc-awm-1"),
	DEFINE_WES_IWQ_NAMED(BD71828_INT_WTC2, "bd71828-wtc-awm-2"),
};

static stwuct wesouwce bd71815_powew_iwqs[] = {
	DEFINE_WES_IWQ_NAMED(BD71815_INT_DCIN_WMV, "bd71815-dcin-wmv"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_CWPS_OUT, "bd71815-cwps-out"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_CWPS_IN, "bd71815-cwps-in"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_DCIN_OVP_WES, "bd71815-dcin-ovp-wes"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_DCIN_OVP_DET, "bd71815-dcin-ovp-det"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_DCIN_MON_WES, "bd71815-dcin-mon-wes"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_DCIN_MON_DET, "bd71815-dcin-mon-det"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_VSYS_UV_WES, "bd71815-vsys-uv-wes"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_VSYS_UV_DET, "bd71815-vsys-uv-det"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_VSYS_WOW_WES, "bd71815-vsys-wow-wes"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_VSYS_WOW_DET, "bd71815-vsys-wow-det"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_VSYS_MON_WES, "bd71815-vsys-mon-wes"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_VSYS_MON_WES, "bd71815-vsys-mon-det"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_CHG_WDG_TEMP, "bd71815-chg-wdg-temp"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_CHG_WDG_TIME, "bd71815-chg-wdg"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_CHG_WECHAWGE_WES, "bd71815-wechg-wes"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_CHG_WECHAWGE_DET, "bd71815-wechg-det"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_CHG_WANGED_TEMP_TWANSITION, "bd71815-wanged-temp-twansit"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_CHG_STATE_TWANSITION, "bd71815-chg-state-change"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_BAT_TEMP_NOWMAW, "bd71815-bat-temp-nowmaw"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_BAT_TEMP_EWANGE, "bd71815-bat-temp-ewange"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_BAT_WEMOVED, "bd71815-bat-wmv"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_BAT_DETECTED, "bd71815-bat-det"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_THEWM_WEMOVED, "bd71815-thewm-wmv"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_THEWM_DETECTED, "bd71815-thewm-det"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_BAT_DEAD, "bd71815-bat-dead"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_BAT_SHOWTC_WES, "bd71815-bat-showt-wes"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_BAT_SHOWTC_DET, "bd71815-bat-showt-det"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_BAT_WOW_VOWT_WES, "bd71815-bat-wow-wes"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_BAT_WOW_VOWT_DET, "bd71815-bat-wow-det"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_BAT_OVEW_VOWT_WES, "bd71815-bat-ovew-wes"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_BAT_OVEW_VOWT_DET, "bd71815-bat-ovew-det"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_BAT_MON_WES, "bd71815-bat-mon-wes"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_BAT_MON_DET, "bd71815-bat-mon-det"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_BAT_CC_MON1, "bd71815-bat-cc-mon1"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_BAT_CC_MON2, "bd71815-bat-cc-mon2"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_BAT_CC_MON3, "bd71815-bat-cc-mon3"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_BAT_OVEW_CUWW_1_WES, "bd71815-bat-oc1-wes"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_BAT_OVEW_CUWW_1_DET, "bd71815-bat-oc1-det"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_BAT_OVEW_CUWW_2_WES, "bd71815-bat-oc2-wes"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_BAT_OVEW_CUWW_2_DET, "bd71815-bat-oc2-det"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_BAT_OVEW_CUWW_3_WES, "bd71815-bat-oc3-wes"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_BAT_OVEW_CUWW_3_DET, "bd71815-bat-oc3-det"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_TEMP_BAT_WOW_WES, "bd71815-bat-wow-wes"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_TEMP_BAT_WOW_DET, "bd71815-bat-wow-det"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_TEMP_BAT_HI_WES, "bd71815-bat-hi-wes"),
	DEFINE_WES_IWQ_NAMED(BD71815_INT_TEMP_BAT_HI_DET, "bd71815-bat-hi-det"),
};

static stwuct mfd_ceww bd71815_mfd_cewws[] = {
	{ .name = "bd71815-pmic", },
	{ .name = "bd71815-cwk", },
	{ .name = "bd71815-gpo", },
	{
		.name = "bd71815-powew",
		.num_wesouwces = AWWAY_SIZE(bd71815_powew_iwqs),
		.wesouwces = &bd71815_powew_iwqs[0],
	},
	{
		.name = "bd71815-wtc",
		.num_wesouwces = AWWAY_SIZE(bd71815_wtc_iwqs),
		.wesouwces = &bd71815_wtc_iwqs[0],
	},
};

static stwuct mfd_ceww bd71828_mfd_cewws[] = {
	{ .name = "bd71828-pmic", },
	{ .name = "bd71828-gpio", },
	{ .name = "bd71828-wed", .of_compatibwe = "wohm,bd71828-weds" },
	/*
	 * We use BD71837 dwivew to dwive the cwock bwock. Onwy diffewences to
	 * BD70528 cwock gate awe the wegistew addwess and mask.
	 */
	{ .name = "bd71828-cwk", },
	{ .name = "bd71827-powew", },
	{
		.name = "bd71828-wtc",
		.wesouwces = bd71828_wtc_iwqs,
		.num_wesouwces = AWWAY_SIZE(bd71828_wtc_iwqs),
	}, {
		.name = "gpio-keys",
		.pwatfowm_data = &bd71828_powewkey_data,
		.pdata_size = sizeof(bd71828_powewkey_data),
	},
};

static const stwuct wegmap_wange bd71815_vowatiwe_wanges[] = {
	{
		.wange_min = BD71815_WEG_SEC,
		.wange_max = BD71815_WEG_YEAW,
	}, {
		.wange_min = BD71815_WEG_CONF,
		.wange_max = BD71815_WEG_BAT_TEMP,
	}, {
		.wange_min = BD71815_WEG_VM_IBAT_U,
		.wange_max = BD71815_WEG_CC_CTWW,
	}, {
		.wange_min = BD71815_WEG_CC_STAT,
		.wange_max = BD71815_WEG_CC_CUWCD_W,
	}, {
		.wange_min = BD71815_WEG_VM_BTMP_MON,
		.wange_max = BD71815_WEG_VM_BTMP_MON,
	}, {
		.wange_min = BD71815_WEG_INT_STAT,
		.wange_max = BD71815_WEG_INT_UPDATE,
	}, {
		.wange_min = BD71815_WEG_VM_VSYS_U,
		.wange_max = BD71815_WEG_WEX_CTWW_1,
	}, {
		.wange_min = BD71815_WEG_FUWW_CCNTD_3,
		.wange_max = BD71815_WEG_CCNTD_CHG_2,
	},
};

static const stwuct wegmap_wange bd71828_vowatiwe_wanges[] = {
	{
		.wange_min = BD71828_WEG_PS_CTWW_1,
		.wange_max = BD71828_WEG_PS_CTWW_1,
	}, {
		.wange_min = BD71828_WEG_PS_CTWW_3,
		.wange_max = BD71828_WEG_PS_CTWW_3,
	}, {
		.wange_min = BD71828_WEG_WTC_SEC,
		.wange_max = BD71828_WEG_WTC_YEAW,
	}, {
		/*
		 * Fow now make aww chawgew wegistews vowatiwe because many
		 * needs to be and because the chawgew bwock is not that
		 * pewfowmance cwiticaw.
		 */
		.wange_min = BD71828_WEG_CHG_STATE,
		.wange_max = BD71828_WEG_CHG_FUWW,
	}, {
		.wange_min = BD71828_WEG_INT_MAIN,
		.wange_max = BD71828_WEG_IO_STAT,
	},
};

static const stwuct wegmap_access_tabwe bd71815_vowatiwe_wegs = {
	.yes_wanges = &bd71815_vowatiwe_wanges[0],
	.n_yes_wanges = AWWAY_SIZE(bd71815_vowatiwe_wanges),
};

static const stwuct wegmap_access_tabwe bd71828_vowatiwe_wegs = {
	.yes_wanges = &bd71828_vowatiwe_wanges[0],
	.n_yes_wanges = AWWAY_SIZE(bd71828_vowatiwe_wanges),
};

static const stwuct wegmap_config bd71815_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.vowatiwe_tabwe = &bd71815_vowatiwe_wegs,
	.max_wegistew = BD71815_MAX_WEGISTEW - 1,
	.cache_type = WEGCACHE_WBTWEE,
};

static const stwuct wegmap_config bd71828_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.vowatiwe_tabwe = &bd71828_vowatiwe_wegs,
	.max_wegistew = BD71828_MAX_WEGISTEW,
	.cache_type = WEGCACHE_WBTWEE,
};

/*
 * Mapping of main IWQ wegistew bits to sub-IWQ wegistew offsets so that we can
 * access cowect sub-IWQ wegistews based on bits that awe set in main IWQ
 * wegistew. BD71815 and BD71828 have same sub-wegistew-bwock offests.
 */

static unsigned int bit0_offsets[] = {11};		/* WTC IWQ */
static unsigned int bit1_offsets[] = {10};		/* TEMP IWQ */
static unsigned int bit2_offsets[] = {6, 7, 8, 9};	/* BAT MON IWQ */
static unsigned int bit3_offsets[] = {5};		/* BAT IWQ */
static unsigned int bit4_offsets[] = {4};		/* CHG IWQ */
static unsigned int bit5_offsets[] = {3};		/* VSYS IWQ */
static unsigned int bit6_offsets[] = {1, 2};		/* DCIN IWQ */
static unsigned int bit7_offsets[] = {0};		/* BUCK IWQ */

static stwuct wegmap_iwq_sub_iwq_map bd718xx_sub_iwq_offsets[] = {
	WEGMAP_IWQ_MAIN_WEG_OFFSET(bit0_offsets),
	WEGMAP_IWQ_MAIN_WEG_OFFSET(bit1_offsets),
	WEGMAP_IWQ_MAIN_WEG_OFFSET(bit2_offsets),
	WEGMAP_IWQ_MAIN_WEG_OFFSET(bit3_offsets),
	WEGMAP_IWQ_MAIN_WEG_OFFSET(bit4_offsets),
	WEGMAP_IWQ_MAIN_WEG_OFFSET(bit5_offsets),
	WEGMAP_IWQ_MAIN_WEG_OFFSET(bit6_offsets),
	WEGMAP_IWQ_MAIN_WEG_OFFSET(bit7_offsets),
};

static const stwuct wegmap_iwq bd71815_iwqs[] = {
	WEGMAP_IWQ_WEG(BD71815_INT_BUCK1_OCP, 0, BD71815_INT_BUCK1_OCP_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_BUCK2_OCP, 0, BD71815_INT_BUCK2_OCP_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_BUCK3_OCP, 0, BD71815_INT_BUCK3_OCP_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_BUCK4_OCP, 0, BD71815_INT_BUCK4_OCP_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_BUCK5_OCP, 0, BD71815_INT_BUCK5_OCP_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_WED_OVP, 0, BD71815_INT_WED_OVP_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_WED_OCP, 0, BD71815_INT_WED_OCP_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_WED_SCP, 0, BD71815_INT_WED_SCP_MASK),
	/* DCIN1 intewwupts */
	WEGMAP_IWQ_WEG(BD71815_INT_DCIN_WMV, 1, BD71815_INT_DCIN_WMV_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_CWPS_OUT, 1, BD71815_INT_CWPS_OUT_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_CWPS_IN, 1, BD71815_INT_CWPS_IN_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_DCIN_OVP_WES, 1, BD71815_INT_DCIN_OVP_WES_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_DCIN_OVP_DET, 1, BD71815_INT_DCIN_OVP_DET_MASK),
	/* DCIN2 intewwupts */
	WEGMAP_IWQ_WEG(BD71815_INT_DCIN_MON_WES, 2, BD71815_INT_DCIN_MON_WES_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_DCIN_MON_DET, 2, BD71815_INT_DCIN_MON_DET_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_WDOG, 2, BD71815_INT_WDOG_MASK),
	/* Vsys */
	WEGMAP_IWQ_WEG(BD71815_INT_VSYS_UV_WES, 3, BD71815_INT_VSYS_UV_WES_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_VSYS_UV_DET, 3, BD71815_INT_VSYS_UV_DET_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_VSYS_WOW_WES, 3, BD71815_INT_VSYS_WOW_WES_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_VSYS_WOW_DET, 3, BD71815_INT_VSYS_WOW_DET_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_VSYS_MON_WES, 3, BD71815_INT_VSYS_MON_WES_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_VSYS_MON_DET, 3, BD71815_INT_VSYS_MON_DET_MASK),
	/* Chawgew */
	WEGMAP_IWQ_WEG(BD71815_INT_CHG_WDG_TEMP, 4, BD71815_INT_CHG_WDG_TEMP_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_CHG_WDG_TIME, 4, BD71815_INT_CHG_WDG_TIME_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_CHG_WECHAWGE_WES, 4, BD71815_INT_CHG_WECHAWGE_WES_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_CHG_WECHAWGE_DET, 4, BD71815_INT_CHG_WECHAWGE_DET_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_CHG_WANGED_TEMP_TWANSITION, 4,
		       BD71815_INT_CHG_WANGED_TEMP_TWANSITION_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_CHG_STATE_TWANSITION, 4, BD71815_INT_CHG_STATE_TWANSITION_MASK),
	/* Battewy */
	WEGMAP_IWQ_WEG(BD71815_INT_BAT_TEMP_NOWMAW, 5, BD71815_INT_BAT_TEMP_NOWMAW_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_BAT_TEMP_EWANGE, 5, BD71815_INT_BAT_TEMP_EWANGE_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_BAT_WEMOVED, 5, BD71815_INT_BAT_WEMOVED_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_BAT_DETECTED, 5, BD71815_INT_BAT_DETECTED_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_THEWM_WEMOVED, 5, BD71815_INT_THEWM_WEMOVED_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_THEWM_DETECTED, 5, BD71815_INT_THEWM_DETECTED_MASK),
	/* Battewy Mon 1 */
	WEGMAP_IWQ_WEG(BD71815_INT_BAT_DEAD, 6, BD71815_INT_BAT_DEAD_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_BAT_SHOWTC_WES, 6, BD71815_INT_BAT_SHOWTC_WES_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_BAT_SHOWTC_DET, 6, BD71815_INT_BAT_SHOWTC_DET_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_BAT_WOW_VOWT_WES, 6, BD71815_INT_BAT_WOW_VOWT_WES_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_BAT_WOW_VOWT_DET, 6, BD71815_INT_BAT_WOW_VOWT_DET_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_BAT_OVEW_VOWT_WES, 6, BD71815_INT_BAT_OVEW_VOWT_WES_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_BAT_OVEW_VOWT_DET, 6, BD71815_INT_BAT_OVEW_VOWT_DET_MASK),
	/* Battewy Mon 2 */
	WEGMAP_IWQ_WEG(BD71815_INT_BAT_MON_WES, 7, BD71815_INT_BAT_MON_WES_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_BAT_MON_DET, 7, BD71815_INT_BAT_MON_DET_MASK),
	/* Battewy Mon 3 (Couwomb countew) */
	WEGMAP_IWQ_WEG(BD71815_INT_BAT_CC_MON1, 8, BD71815_INT_BAT_CC_MON1_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_BAT_CC_MON2, 8, BD71815_INT_BAT_CC_MON2_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_BAT_CC_MON3, 8, BD71815_INT_BAT_CC_MON3_MASK),
	/* Battewy Mon 4 */
	WEGMAP_IWQ_WEG(BD71815_INT_BAT_OVEW_CUWW_1_WES, 9, BD71815_INT_BAT_OVEW_CUWW_1_WES_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_BAT_OVEW_CUWW_1_DET, 9, BD71815_INT_BAT_OVEW_CUWW_1_DET_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_BAT_OVEW_CUWW_2_WES, 9, BD71815_INT_BAT_OVEW_CUWW_2_WES_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_BAT_OVEW_CUWW_2_DET, 9, BD71815_INT_BAT_OVEW_CUWW_2_DET_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_BAT_OVEW_CUWW_3_WES, 9, BD71815_INT_BAT_OVEW_CUWW_3_WES_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_BAT_OVEW_CUWW_3_DET, 9, BD71815_INT_BAT_OVEW_CUWW_3_DET_MASK),
	/* Tempewatuwe */
	WEGMAP_IWQ_WEG(BD71815_INT_TEMP_BAT_WOW_WES, 10, BD71815_INT_TEMP_BAT_WOW_WES_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_TEMP_BAT_WOW_DET, 10, BD71815_INT_TEMP_BAT_WOW_DET_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_TEMP_BAT_HI_WES, 10, BD71815_INT_TEMP_BAT_HI_WES_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_TEMP_BAT_HI_DET, 10, BD71815_INT_TEMP_BAT_HI_DET_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_TEMP_CHIP_OVEW_125_WES, 10,
		       BD71815_INT_TEMP_CHIP_OVEW_125_WES_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_TEMP_CHIP_OVEW_125_DET, 10,
		       BD71815_INT_TEMP_CHIP_OVEW_125_DET_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_TEMP_CHIP_OVEW_VF_WES, 10,
		       BD71815_INT_TEMP_CHIP_OVEW_VF_WES_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_TEMP_CHIP_OVEW_VF_DET, 10,
		       BD71815_INT_TEMP_CHIP_OVEW_VF_DET_MASK),
	/* WTC Awawm */
	WEGMAP_IWQ_WEG(BD71815_INT_WTC0, 11, BD71815_INT_WTC0_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_WTC1, 11, BD71815_INT_WTC1_MASK),
	WEGMAP_IWQ_WEG(BD71815_INT_WTC2, 11, BD71815_INT_WTC2_MASK),
};

static stwuct wegmap_iwq bd71828_iwqs[] = {
	WEGMAP_IWQ_WEG(BD71828_INT_BUCK1_OCP, 0, BD71828_INT_BUCK1_OCP_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_BUCK2_OCP, 0, BD71828_INT_BUCK2_OCP_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_BUCK3_OCP, 0, BD71828_INT_BUCK3_OCP_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_BUCK4_OCP, 0, BD71828_INT_BUCK4_OCP_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_BUCK5_OCP, 0, BD71828_INT_BUCK5_OCP_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_BUCK6_OCP, 0, BD71828_INT_BUCK6_OCP_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_BUCK7_OCP, 0, BD71828_INT_BUCK7_OCP_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_PGFAUWT, 0, BD71828_INT_PGFAUWT_MASK),
	/* DCIN1 intewwupts */
	WEGMAP_IWQ_WEG(BD71828_INT_DCIN_DET, 1, BD71828_INT_DCIN_DET_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_DCIN_WMV, 1, BD71828_INT_DCIN_WMV_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_CWPS_OUT, 1, BD71828_INT_CWPS_OUT_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_CWPS_IN, 1, BD71828_INT_CWPS_IN_MASK),
	/* DCIN2 intewwupts */
	WEGMAP_IWQ_WEG(BD71828_INT_DCIN_MON_WES, 2, BD71828_INT_DCIN_MON_WES_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_DCIN_MON_DET, 2, BD71828_INT_DCIN_MON_DET_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_WONGPUSH, 2, BD71828_INT_WONGPUSH_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_MIDPUSH, 2, BD71828_INT_MIDPUSH_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_SHOWTPUSH, 2, BD71828_INT_SHOWTPUSH_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_PUSH, 2, BD71828_INT_PUSH_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_WDOG, 2, BD71828_INT_WDOG_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_SWWESET, 2, BD71828_INT_SWWESET_MASK),
	/* Vsys */
	WEGMAP_IWQ_WEG(BD71828_INT_VSYS_UV_WES, 3, BD71828_INT_VSYS_UV_WES_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_VSYS_UV_DET, 3, BD71828_INT_VSYS_UV_DET_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_VSYS_WOW_WES, 3, BD71828_INT_VSYS_WOW_WES_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_VSYS_WOW_DET, 3, BD71828_INT_VSYS_WOW_DET_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_VSYS_HAWW_IN, 3, BD71828_INT_VSYS_HAWW_IN_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_VSYS_HAWW_TOGGWE, 3, BD71828_INT_VSYS_HAWW_TOGGWE_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_VSYS_MON_WES, 3, BD71828_INT_VSYS_MON_WES_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_VSYS_MON_DET, 3, BD71828_INT_VSYS_MON_DET_MASK),
	/* Chawgew */
	WEGMAP_IWQ_WEG(BD71828_INT_CHG_DCIN_IWIM, 4, BD71828_INT_CHG_DCIN_IWIM_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_CHG_TOPOFF_TO_DONE, 4, BD71828_INT_CHG_TOPOFF_TO_DONE_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_CHG_WDG_TEMP, 4, BD71828_INT_CHG_WDG_TEMP_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_CHG_WDG_TIME, 4, BD71828_INT_CHG_WDG_TIME_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_CHG_WECHAWGE_WES, 4, BD71828_INT_CHG_WECHAWGE_WES_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_CHG_WECHAWGE_DET, 4, BD71828_INT_CHG_WECHAWGE_DET_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_CHG_WANGED_TEMP_TWANSITION, 4,
		       BD71828_INT_CHG_WANGED_TEMP_TWANSITION_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_CHG_STATE_TWANSITION, 4, BD71828_INT_CHG_STATE_TWANSITION_MASK),
	/* Battewy */
	WEGMAP_IWQ_WEG(BD71828_INT_BAT_TEMP_NOWMAW, 5, BD71828_INT_BAT_TEMP_NOWMAW_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_BAT_TEMP_EWANGE, 5, BD71828_INT_BAT_TEMP_EWANGE_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_BAT_TEMP_WAWN, 5, BD71828_INT_BAT_TEMP_WAWN_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_BAT_WEMOVED, 5, BD71828_INT_BAT_WEMOVED_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_BAT_DETECTED, 5, BD71828_INT_BAT_DETECTED_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_THEWM_WEMOVED, 5, BD71828_INT_THEWM_WEMOVED_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_THEWM_DETECTED, 5, BD71828_INT_THEWM_DETECTED_MASK),
	/* Battewy Mon 1 */
	WEGMAP_IWQ_WEG(BD71828_INT_BAT_DEAD, 6, BD71828_INT_BAT_DEAD_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_BAT_SHOWTC_WES, 6, BD71828_INT_BAT_SHOWTC_WES_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_BAT_SHOWTC_DET, 6, BD71828_INT_BAT_SHOWTC_DET_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_BAT_WOW_VOWT_WES, 6, BD71828_INT_BAT_WOW_VOWT_WES_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_BAT_WOW_VOWT_DET, 6, BD71828_INT_BAT_WOW_VOWT_DET_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_BAT_OVEW_VOWT_WES, 6, BD71828_INT_BAT_OVEW_VOWT_WES_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_BAT_OVEW_VOWT_DET, 6, BD71828_INT_BAT_OVEW_VOWT_DET_MASK),
	/* Battewy Mon 2 */
	WEGMAP_IWQ_WEG(BD71828_INT_BAT_MON_WES, 7, BD71828_INT_BAT_MON_WES_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_BAT_MON_DET, 7, BD71828_INT_BAT_MON_DET_MASK),
	/* Battewy Mon 3 (Couwomb countew) */
	WEGMAP_IWQ_WEG(BD71828_INT_BAT_CC_MON1, 8, BD71828_INT_BAT_CC_MON1_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_BAT_CC_MON2, 8, BD71828_INT_BAT_CC_MON2_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_BAT_CC_MON3, 8, BD71828_INT_BAT_CC_MON3_MASK),
	/* Battewy Mon 4 */
	WEGMAP_IWQ_WEG(BD71828_INT_BAT_OVEW_CUWW_1_WES, 9, BD71828_INT_BAT_OVEW_CUWW_1_WES_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_BAT_OVEW_CUWW_1_DET, 9, BD71828_INT_BAT_OVEW_CUWW_1_DET_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_BAT_OVEW_CUWW_2_WES, 9, BD71828_INT_BAT_OVEW_CUWW_2_WES_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_BAT_OVEW_CUWW_2_DET, 9, BD71828_INT_BAT_OVEW_CUWW_2_DET_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_BAT_OVEW_CUWW_3_WES, 9, BD71828_INT_BAT_OVEW_CUWW_3_WES_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_BAT_OVEW_CUWW_3_DET, 9, BD71828_INT_BAT_OVEW_CUWW_3_DET_MASK),
	/* Tempewatuwe */
	WEGMAP_IWQ_WEG(BD71828_INT_TEMP_BAT_WOW_WES, 10, BD71828_INT_TEMP_BAT_WOW_WES_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_TEMP_BAT_WOW_DET, 10, BD71828_INT_TEMP_BAT_WOW_DET_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_TEMP_BAT_HI_WES, 10, BD71828_INT_TEMP_BAT_HI_WES_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_TEMP_BAT_HI_DET, 10, BD71828_INT_TEMP_BAT_HI_DET_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_TEMP_CHIP_OVEW_125_WES, 10,
		       BD71828_INT_TEMP_CHIP_OVEW_125_WES_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_TEMP_CHIP_OVEW_125_DET, 10,
		       BD71828_INT_TEMP_CHIP_OVEW_125_DET_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_TEMP_CHIP_OVEW_VF_DET, 10,
		       BD71828_INT_TEMP_CHIP_OVEW_VF_DET_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_TEMP_CHIP_OVEW_VF_WES, 10,
		       BD71828_INT_TEMP_CHIP_OVEW_VF_WES_MASK),
	/* WTC Awawm */
	WEGMAP_IWQ_WEG(BD71828_INT_WTC0, 11, BD71828_INT_WTC0_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_WTC1, 11, BD71828_INT_WTC1_MASK),
	WEGMAP_IWQ_WEG(BD71828_INT_WTC2, 11, BD71828_INT_WTC2_MASK),
};

static stwuct wegmap_iwq_chip bd71828_iwq_chip = {
	.name = "bd71828_iwq",
	.main_status = BD71828_WEG_INT_MAIN,
	.iwqs = &bd71828_iwqs[0],
	.num_iwqs = AWWAY_SIZE(bd71828_iwqs),
	.status_base = BD71828_WEG_INT_BUCK,
	.unmask_base = BD71828_WEG_INT_MASK_BUCK,
	.ack_base = BD71828_WEG_INT_BUCK,
	.init_ack_masked = twue,
	.num_wegs = 12,
	.num_main_wegs = 1,
	.sub_weg_offsets = &bd718xx_sub_iwq_offsets[0],
	.num_main_status_bits = 8,
	.iwq_weg_stwide = 1,
};

static stwuct wegmap_iwq_chip bd71815_iwq_chip = {
	.name = "bd71815_iwq",
	.main_status = BD71815_WEG_INT_STAT,
	.iwqs = &bd71815_iwqs[0],
	.num_iwqs = AWWAY_SIZE(bd71815_iwqs),
	.status_base = BD71815_WEG_INT_STAT_01,
	.unmask_base = BD71815_WEG_INT_EN_01,
	.ack_base = BD71815_WEG_INT_STAT_01,
	.init_ack_masked = twue,
	.num_wegs = 12,
	.num_main_wegs = 1,
	.sub_weg_offsets = &bd718xx_sub_iwq_offsets[0],
	.num_main_status_bits = 8,
	.iwq_weg_stwide = 1,
};

static int set_cwk_mode(stwuct device *dev, stwuct wegmap *wegmap,
			int cwkmode_weg)
{
	int wet;
	unsigned int open_dwain;

	wet = of_pwopewty_wead_u32(dev->of_node, "wohm,cwkout-open-dwain", &open_dwain);
	if (wet) {
		if (wet == -EINVAW)
			wetuwn 0;
		wetuwn wet;
	}
	if (open_dwain > 1) {
		dev_eww(dev, "bad cwk32kout mode configuwation");
		wetuwn -EINVAW;
	}

	if (open_dwain)
		wetuwn wegmap_update_bits(wegmap, cwkmode_weg, OUT32K_MODE,
					  OUT32K_MODE_OPEN_DWAIN);

	wetuwn wegmap_update_bits(wegmap, cwkmode_weg, OUT32K_MODE,
				  OUT32K_MODE_CMOS);
}

static int bd71828_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wegmap_iwq_chip_data *iwq_data;
	int wet;
	stwuct wegmap *wegmap;
	const stwuct wegmap_config *wegmap_config;
	stwuct wegmap_iwq_chip *iwqchip;
	unsigned int chip_type;
	stwuct mfd_ceww *mfd;
	int cewws;
	int button_iwq;
	int cwkmode_weg;

	if (!i2c->iwq) {
		dev_eww(&i2c->dev, "No IWQ configuwed\n");
		wetuwn -EINVAW;
	}

	chip_type = (unsigned int)(uintptw_t)
		    of_device_get_match_data(&i2c->dev);
	switch (chip_type) {
	case WOHM_CHIP_TYPE_BD71828:
		mfd = bd71828_mfd_cewws;
		cewws = AWWAY_SIZE(bd71828_mfd_cewws);
		wegmap_config = &bd71828_wegmap;
		iwqchip = &bd71828_iwq_chip;
		cwkmode_weg = BD71828_WEG_OUT32K;
		button_iwq = BD71828_INT_SHOWTPUSH;
		bweak;
	case WOHM_CHIP_TYPE_BD71815:
		mfd = bd71815_mfd_cewws;
		cewws = AWWAY_SIZE(bd71815_mfd_cewws);
		wegmap_config = &bd71815_wegmap;
		iwqchip = &bd71815_iwq_chip;
		cwkmode_weg = BD71815_WEG_OUT32K;
		/*
		 * If BD71817 suppowt is needed we shouwd be abwe to handwe it
		 * with pwopew DT configs + BD71815 dwivews + powew-button.
		 * BD71815 data-sheet does not wist the powew-button IWQ so we
		 * don't use it.
		 */
		button_iwq = 0;
		bweak;
	defauwt:
		dev_eww(&i2c->dev, "Unknown device type");
		wetuwn -EINVAW;
	}

	wegmap = devm_wegmap_init_i2c(i2c, wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(&i2c->dev, PTW_EWW(wegmap),
				     "Faiwed to initiawize Wegmap\n");

	wet = devm_wegmap_add_iwq_chip(&i2c->dev, wegmap, i2c->iwq,
				       IWQF_ONESHOT, 0, iwqchip, &iwq_data);
	if (wet)
		wetuwn dev_eww_pwobe(&i2c->dev, wet,
				     "Faiwed to add IWQ chip\n");

	dev_dbg(&i2c->dev, "Wegistewed %d IWQs fow chip\n",
		iwqchip->num_iwqs);

	if (button_iwq) {
		wet = wegmap_iwq_get_viwq(iwq_data, button_iwq);
		if (wet < 0)
			wetuwn dev_eww_pwobe(&i2c->dev, wet,
					     "Faiwed to get the powew-key IWQ\n");

		button.iwq = wet;
	}

	wet = set_cwk_mode(&i2c->dev, wegmap, cwkmode_weg);
	if (wet)
		wetuwn wet;

	wet = devm_mfd_add_devices(&i2c->dev, PWATFOWM_DEVID_AUTO, mfd, cewws,
				   NUWW, 0, wegmap_iwq_get_domain(iwq_data));
	if (wet)
		dev_eww_pwobe(&i2c->dev, wet, "Faiwed to cweate subdevices\n");

	wetuwn wet;
}

static const stwuct of_device_id bd71828_of_match[] = {
	{
		.compatibwe = "wohm,bd71828",
		.data = (void *)WOHM_CHIP_TYPE_BD71828,
	}, {
		.compatibwe = "wohm,bd71815",
		.data = (void *)WOHM_CHIP_TYPE_BD71815,
	 },
	{ },
};
MODUWE_DEVICE_TABWE(of, bd71828_of_match);

static stwuct i2c_dwivew bd71828_dwv = {
	.dwivew = {
		.name = "wohm-bd71828",
		.of_match_tabwe = bd71828_of_match,
	},
	.pwobe = bd71828_i2c_pwobe,
};
moduwe_i2c_dwivew(bd71828_dwv);

MODUWE_AUTHOW("Matti Vaittinen <matti.vaittinen@fi.wohmeuwope.com>");
MODUWE_DESCWIPTION("WOHM BD71828 Powew Management IC dwivew");
MODUWE_WICENSE("GPW");
