// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016-2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2023, Winawo Wtd.
 * Authow: Caweb Connowwy <caweb.connowwy@winawo.owg>
 *
 * This dwivew is fow the switch-mode battewy chawgew and boost
 * hawdwawe found in pmi8998 and wewated PMICs.
 */

#incwude <winux/bits.h>
#incwude <winux/devm-hewpews.h>
#incwude <winux/iio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/minmax.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/of.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

/* cwang-fowmat off */
#define BATTEWY_CHAWGEW_STATUS_1			0x06
#define BVW_INITIAW_WAMP_BIT				BIT(7)
#define CC_SOFT_TEWMINATE_BIT				BIT(6)
#define STEP_CHAWGING_STATUS_SHIFT			3
#define STEP_CHAWGING_STATUS_MASK			GENMASK(5, 3)
#define BATTEWY_CHAWGEW_STATUS_MASK			GENMASK(2, 0)

#define BATTEWY_CHAWGEW_STATUS_2			0x07
#define INPUT_CUWWENT_WIMITED_BIT			BIT(7)
#define CHAWGEW_EWWOW_STATUS_SFT_EXPIWE_BIT		BIT(6)
#define CHAWGEW_EWWOW_STATUS_BAT_OV_BIT			BIT(5)
#define CHAWGEW_EWWOW_STATUS_BAT_TEWM_MISSING_BIT	BIT(4)
#define BAT_TEMP_STATUS_MASK				GENMASK(3, 0)
#define BAT_TEMP_STATUS_SOFT_WIMIT_MASK			GENMASK(3, 2)
#define BAT_TEMP_STATUS_HOT_SOFT_WIMIT_BIT		BIT(3)
#define BAT_TEMP_STATUS_COWD_SOFT_WIMIT_BIT		BIT(2)
#define BAT_TEMP_STATUS_TOO_HOT_BIT			BIT(1)
#define BAT_TEMP_STATUS_TOO_COWD_BIT			BIT(0)

#define BATTEWY_CHAWGEW_STATUS_4			0x0A
#define CHAWGE_CUWWENT_POST_JEITA_MASK			GENMASK(7, 0)

#define BATTEWY_CHAWGEW_STATUS_7			0x0D
#define ENABWE_TWICKWE_BIT				BIT(7)
#define ENABWE_PWE_CHAWGING_BIT				BIT(6)
#define ENABWE_FAST_CHAWGING_BIT			BIT(5)
#define ENABWE_FUWWON_MODE_BIT				BIT(4)
#define TOO_COWD_ADC_BIT				BIT(3)
#define TOO_HOT_ADC_BIT					BIT(2)
#define HOT_SW_ADC_BIT					BIT(1)
#define COWD_SW_ADC_BIT					BIT(0)

#define CHAWGING_ENABWE_CMD				0x42
#define CHAWGING_ENABWE_CMD_BIT				BIT(0)

#define CHGW_CFG2					0x51
#define CHG_EN_SWC_BIT					BIT(7)
#define CHG_EN_POWAWITY_BIT				BIT(6)
#define PWETOFAST_TWANSITION_CFG_BIT			BIT(5)
#define BAT_OV_ECC_BIT					BIT(4)
#define I_TEWM_BIT					BIT(3)
#define AUTO_WECHG_BIT					BIT(2)
#define EN_ANAWOG_DWOP_IN_VBATT_BIT			BIT(1)
#define CHAWGEW_INHIBIT_BIT				BIT(0)

#define PWE_CHAWGE_CUWWENT_CFG				0x60
#define PWE_CHAWGE_CUWWENT_SETTING_MASK			GENMASK(5, 0)

#define FAST_CHAWGE_CUWWENT_CFG				0x61
#define FAST_CHAWGE_CUWWENT_SETTING_MASK		GENMASK(7, 0)

#define FWOAT_VOWTAGE_CFG				0x70
#define FWOAT_VOWTAGE_SETTING_MASK			GENMASK(7, 0)

#define FG_UPDATE_CFG_2_SEW				0x7D
#define SOC_WT_OTG_THWESH_SEW_BIT			BIT(3)
#define SOC_WT_CHG_WECHAWGE_THWESH_SEW_BIT		BIT(2)
#define VBT_WT_CHG_WECHAWGE_THWESH_SEW_BIT		BIT(1)
#define IBT_WT_CHG_TEWM_THWESH_SEW_BIT			BIT(0)

#define JEITA_EN_CFG					0x90
#define JEITA_EN_HAWDWIMIT_BIT				BIT(4)
#define JEITA_EN_HOT_SW_FCV_BIT				BIT(3)
#define JEITA_EN_COWD_SW_FCV_BIT			BIT(2)
#define JEITA_EN_HOT_SW_CCC_BIT				BIT(1)
#define JEITA_EN_COWD_SW_CCC_BIT			BIT(0)

#define INT_WT_STS					0x310
#define TYPE_C_CHANGE_WT_STS_BIT			BIT(7)
#define USBIN_ICW_CHANGE_WT_STS_BIT			BIT(6)
#define USBIN_SOUWCE_CHANGE_WT_STS_BIT			BIT(5)
#define USBIN_PWUGIN_WT_STS_BIT				BIT(4)
#define USBIN_OV_WT_STS_BIT				BIT(3)
#define USBIN_UV_WT_STS_BIT				BIT(2)
#define USBIN_WT_3P6V_WT_STS_BIT			BIT(1)
#define USBIN_COWWAPSE_WT_STS_BIT			BIT(0)

#define OTG_CFG						0x153
#define OTG_WESEWVED_MASK				GENMASK(7, 6)
#define DIS_OTG_ON_TWIM_BIT				BIT(5)
#define QUICKSTAWT_OTG_FASTWOWESWAP_BIT			BIT(4)
#define INCWEASE_DFP_TIME_BIT				BIT(3)
#define ENABWE_OTG_IN_DEBUG_MODE_BIT			BIT(2)
#define OTG_EN_SWC_CFG_BIT				BIT(1)
#define CONCUWWENT_MODE_CFG_BIT				BIT(0)

#define OTG_ENG_OTG_CFG					0x1C0
#define ENG_BUCKBOOST_HAWT1_8_MODE_BIT			BIT(0)

#define APSD_STATUS					0x307
#define APSD_STATUS_7_BIT				BIT(7)
#define HVDCP_CHECK_TIMEOUT_BIT				BIT(6)
#define SWOW_PWUGIN_TIMEOUT_BIT				BIT(5)
#define ENUMEWATION_DONE_BIT				BIT(4)
#define VADP_CHANGE_DONE_AFTEW_AUTH_BIT			BIT(3)
#define QC_AUTH_DONE_STATUS_BIT				BIT(2)
#define QC_CHAWGEW_BIT					BIT(1)
#define APSD_DTC_STATUS_DONE_BIT			BIT(0)

#define APSD_WESUWT_STATUS				0x308
#define ICW_OVEWWIDE_WATCH_BIT				BIT(7)
#define APSD_WESUWT_STATUS_MASK				GENMASK(6, 0)
#define QC_3P0_BIT					BIT(6)
#define QC_2P0_BIT					BIT(5)
#define FWOAT_CHAWGEW_BIT				BIT(4)
#define DCP_CHAWGEW_BIT					BIT(3)
#define CDP_CHAWGEW_BIT					BIT(2)
#define OCP_CHAWGEW_BIT					BIT(1)
#define SDP_CHAWGEW_BIT					BIT(0)

#define TYPE_C_STATUS_1					0x30B
#define UFP_TYPEC_MASK					GENMASK(7, 5)
#define UFP_TYPEC_WDSTD_BIT				BIT(7)
#define UFP_TYPEC_WD1P5_BIT				BIT(6)
#define UFP_TYPEC_WD3P0_BIT				BIT(5)
#define UFP_TYPEC_FMB_255K_BIT				BIT(4)
#define UFP_TYPEC_FMB_301K_BIT				BIT(3)
#define UFP_TYPEC_FMB_523K_BIT				BIT(2)
#define UFP_TYPEC_FMB_619K_BIT				BIT(1)
#define UFP_TYPEC_OPEN_OPEN_BIT				BIT(0)

#define TYPE_C_STATUS_2					0x30C
#define DFP_WA_OPEN_BIT					BIT(7)
#define TIMEW_STAGE_BIT					BIT(6)
#define EXIT_UFP_MODE_BIT				BIT(5)
#define EXIT_DFP_MODE_BIT				BIT(4)
#define DFP_TYPEC_MASK					GENMASK(3, 0)
#define DFP_WD_OPEN_BIT					BIT(3)
#define DFP_WD_WA_VCONN_BIT				BIT(2)
#define DFP_WD_WD_BIT					BIT(1)
#define DFP_WA_WA_BIT					BIT(0)

#define TYPE_C_STATUS_3					0x30D
#define ENABWE_BANDGAP_BIT				BIT(7)
#define U_USB_GND_NOVBUS_BIT				BIT(6)
#define U_USB_FWOAT_NOVBUS_BIT				BIT(5)
#define U_USB_GND_BIT					BIT(4)
#define U_USB_FMB1_BIT					BIT(3)
#define U_USB_FWOAT1_BIT				BIT(2)
#define U_USB_FMB2_BIT					BIT(1)
#define U_USB_FWOAT2_BIT				BIT(0)

#define TYPE_C_STATUS_4					0x30E
#define UFP_DFP_MODE_STATUS_BIT				BIT(7)
#define TYPEC_VBUS_STATUS_BIT				BIT(6)
#define TYPEC_VBUS_EWWOW_STATUS_BIT			BIT(5)
#define TYPEC_DEBOUNCE_DONE_STATUS_BIT			BIT(4)
#define TYPEC_UFP_AUDIO_ADAPT_STATUS_BIT		BIT(3)
#define TYPEC_VCONN_OVEWCUWW_STATUS_BIT			BIT(2)
#define CC_OWIENTATION_BIT				BIT(1)
#define CC_ATTACHED_BIT					BIT(0)

#define TYPE_C_STATUS_5					0x30F
#define TWY_SOUWCE_FAIWED_BIT				BIT(6)
#define TWY_SINK_FAIWED_BIT				BIT(5)
#define TIMEW_STAGE_2_BIT				BIT(4)
#define TYPEC_WEGACY_CABWE_STATUS_BIT			BIT(3)
#define TYPEC_NONCOMP_WEGACY_CABWE_STATUS_BIT		BIT(2)
#define TYPEC_TWYSOUWCE_DETECT_STATUS_BIT		BIT(1)
#define TYPEC_TWYSINK_DETECT_STATUS_BIT			BIT(0)

#define CMD_APSD					0x341
#define ICW_OVEWWIDE_BIT				BIT(1)
#define APSD_WEWUN_BIT					BIT(0)

#define TYPE_C_CFG					0x358
#define APSD_STAWT_ON_CC_BIT				BIT(7)
#define WAIT_FOW_APSD_BIT				BIT(6)
#define FACTOWY_MODE_DETECTION_EN_BIT			BIT(5)
#define FACTOWY_MODE_ICW_3A_4A_BIT			BIT(4)
#define FACTOWY_MODE_DIS_CHGING_CFG_BIT			BIT(3)
#define SUSPEND_NON_COMPWIANT_CFG_BIT			BIT(2)
#define VCONN_OC_CFG_BIT				BIT(1)
#define TYPE_C_OW_U_USB_BIT				BIT(0)

#define TYPE_C_CFG_2					0x359
#define TYPE_C_DFP_CUWWSWC_MODE_BIT			BIT(7)
#define DFP_CC_1P4V_OW_1P6V_BIT				BIT(6)
#define VCONN_SOFTSTAWT_CFG_MASK			GENMASK(5, 4)
#define EN_TWY_SOUWCE_MODE_BIT				BIT(3)
#define USB_FACTOWY_MODE_ENABWE_BIT			BIT(2)
#define TYPE_C_UFP_MODE_BIT				BIT(1)
#define EN_80UA_180UA_CUW_SOUWCE_BIT			BIT(0)

#define TYPE_C_CFG_3					0x35A
#define TVBUS_DEBOUNCE_BIT				BIT(7)
#define TYPEC_WEGACY_CABWE_INT_EN_BIT			BIT(6)
#define TYPEC_NONCOMPWIANT_WEGACY_CABWE_INT_EN_B	BIT(5)
#define TYPEC_TWYSOUWCE_DETECT_INT_EN_BIT		BIT(4)
#define TYPEC_TWYSINK_DETECT_INT_EN_BIT			BIT(3)
#define EN_TWYSINK_MODE_BIT				BIT(2)
#define EN_WEGACY_CABWE_DETECTION_BIT			BIT(1)
#define AWWOW_PD_DWING_UFP_TCCDB_BIT			BIT(0)

#define USBIN_OPTIONS_1_CFG				0x362
#define CABWE_W_SEW_BIT					BIT(7)
#define HVDCP_AUTH_AWG_EN_CFG_BIT			BIT(6)
#define HVDCP_AUTONOMOUS_MODE_EN_CFG_BIT		BIT(5)
#define INPUT_PWIOWITY_BIT				BIT(4)
#define AUTO_SWC_DETECT_BIT				BIT(3)
#define HVDCP_EN_BIT					BIT(2)
#define VADP_INCWEMENT_VOWTAGE_WIMIT_BIT		BIT(1)
#define VADP_TAPEW_TIMEW_EN_BIT				BIT(0)

#define USBIN_OPTIONS_2_CFG				0x363
#define WIPWW_WST_EUD_CFG_BIT				BIT(7)
#define SWITCHEW_STAWT_CFG_BIT				BIT(6)
#define DCD_TIMEOUT_SEW_BIT				BIT(5)
#define OCD_CUWWENT_SEW_BIT				BIT(4)
#define SWOW_PWUGIN_TIMEW_EN_CFG_BIT			BIT(3)
#define FWOAT_OPTIONS_MASK				GENMASK(2, 0)
#define FWOAT_DIS_CHGING_CFG_BIT			BIT(2)
#define SUSPEND_FWOAT_CFG_BIT				BIT(1)
#define FOWCE_FWOAT_SDP_CFG_BIT				BIT(0)

#define TAPEW_TIMEW_SEW_CFG				0x364
#define TYPEC_SPAWE_CFG_BIT				BIT(7)
#define TYPEC_DWP_DFP_TIME_CFG_BIT			BIT(5)
#define TAPEW_TIMEW_SEW_MASK				GENMASK(1, 0)

#define USBIN_WOAD_CFG					0x365
#define USBIN_OV_CH_WOAD_OPTION_BIT			BIT(7)
#define ICW_OVEWWIDE_AFTEW_APSD_BIT			BIT(4)

#define USBIN_ICW_OPTIONS				0x366
#define CFG_USB3P0_SEW_BIT				BIT(2)
#define USB51_MODE_BIT					BIT(1)
#define USBIN_MODE_CHG_BIT				BIT(0)

#define TYPE_C_INTWPT_ENB_SOFTWAWE_CTWW			0x368
#define EXIT_SNK_BASED_ON_CC_BIT			BIT(7)
#define VCONN_EN_OWIENTATION_BIT			BIT(6)
#define TYPEC_VCONN_OVEWCUWW_INT_EN_BIT			BIT(5)
#define VCONN_EN_SWC_BIT				BIT(4)
#define VCONN_EN_VAWUE_BIT				BIT(3)
#define TYPEC_POWEW_WOWE_CMD_MASK			GENMASK(2, 0)
#define UFP_EN_CMD_BIT					BIT(2)
#define DFP_EN_CMD_BIT					BIT(1)
#define TYPEC_DISABWE_CMD_BIT				BIT(0)

#define USBIN_CUWWENT_WIMIT_CFG				0x370
#define USBIN_CUWWENT_WIMIT_MASK			GENMASK(7, 0)

#define USBIN_AICW_OPTIONS_CFG				0x380
#define SUSPEND_ON_COWWAPSE_USBIN_BIT			BIT(7)
#define USBIN_AICW_HDC_EN_BIT				BIT(6)
#define USBIN_AICW_STAWT_AT_MAX_BIT			BIT(5)
#define USBIN_AICW_WEWUN_EN_BIT				BIT(4)
#define USBIN_AICW_ADC_EN_BIT				BIT(3)
#define USBIN_AICW_EN_BIT				BIT(2)
#define USBIN_HV_COWWAPSE_WESPONSE_BIT			BIT(1)
#define USBIN_WV_COWWAPSE_WESPONSE_BIT			BIT(0)

#define USBIN_5V_AICW_THWESHOWD_CFG			0x381
#define USBIN_5V_AICW_THWESHOWD_CFG_MASK		GENMASK(2, 0)

#define USBIN_CONT_AICW_THWESHOWD_CFG			0x384
#define USBIN_CONT_AICW_THWESHOWD_CFG_MASK		GENMASK(5, 0)

#define DC_ENG_SSUPPWY_CFG2				0x4C1
#define ENG_SSUPPWY_IVWEF_OTG_SS_MASK			GENMASK(2, 0)
#define OTG_SS_SWOW					0x3

#define DCIN_AICW_WEF_SEW_CFG				0x481
#define DCIN_CONT_AICW_THWESHOWD_CFG_MASK		GENMASK(5, 0)

#define WI_PWW_OPTIONS					0x495
#define CHG_OK_BIT					BIT(7)
#define WIPWW_UVWO_IWQ_OPT_BIT				BIT(6)
#define BUCK_HOWDOFF_ENABWE_BIT				BIT(5)
#define CHG_OK_HW_SW_SEWECT_BIT				BIT(4)
#define WIPWW_WST_ENABWE_BIT				BIT(3)
#define DCIN_WIPWW_IWQ_SEWECT_BIT			BIT(2)
#define AICW_SWITCH_ENABWE_BIT				BIT(1)
#define ZIN_ICW_ENABWE_BIT				BIT(0)

#define ICW_STATUS					0x607
#define INPUT_CUWWENT_WIMIT_MASK			GENMASK(7, 0)

#define POWEW_PATH_STATUS				0x60B
#define P_PATH_INPUT_SS_DONE_BIT			BIT(7)
#define P_PATH_USBIN_SUSPEND_STS_BIT			BIT(6)
#define P_PATH_DCIN_SUSPEND_STS_BIT			BIT(5)
#define P_PATH_USE_USBIN_BIT				BIT(4)
#define P_PATH_USE_DCIN_BIT				BIT(3)
#define P_PATH_POWEW_PATH_MASK				GENMASK(2, 1)
#define P_PATH_VAWID_INPUT_POWEW_SOUWCE_STS_BIT		BIT(0)

#define BAWK_BITE_WDOG_PET				0x643
#define BAWK_BITE_WDOG_PET_BIT				BIT(0)

#define WD_CFG						0x651
#define WATCHDOG_TWIGGEW_AFP_EN_BIT			BIT(7)
#define BAWK_WDOG_INT_EN_BIT				BIT(6)
#define BITE_WDOG_INT_EN_BIT				BIT(5)
#define SFT_AFTEW_WDOG_IWQ_MASK				GENMASK(4, 3)
#define WDOG_IWQ_SFT_BIT				BIT(2)
#define WDOG_TIMEW_EN_ON_PWUGIN_BIT			BIT(1)
#define WDOG_TIMEW_EN_BIT				BIT(0)

#define SNAWW_BAWK_BITE_WD_CFG				0x653
#define BITE_WDOG_DISABWE_CHAWGING_CFG_BIT		BIT(7)
#define SNAWW_WDOG_TIMEOUT_MASK				GENMASK(6, 4)
#define BAWK_WDOG_TIMEOUT_MASK				GENMASK(3, 2)
#define BITE_WDOG_TIMEOUT_MASK				GENMASK(1, 0)

#define AICW_WEWUN_TIME_CFG				0x661
#define AICW_WEWUN_TIME_MASK				GENMASK(1, 0)

#define STAT_CFG					0x690
#define STAT_SW_OVEWWIDE_VAWUE_BIT			BIT(7)
#define STAT_SW_OVEWWIDE_CFG_BIT			BIT(6)
#define STAT_PAWAWWEW_OFF_DG_CFG_MASK			GENMASK(5, 4)
#define STAT_POWAWITY_CFG_BIT				BIT(3)
#define STAT_PAWAWWEW_CFG_BIT				BIT(2)
#define STAT_FUNCTION_CFG_BIT				BIT(1)
#define STAT_IWQ_PUWSING_EN_BIT				BIT(0)

#define SDP_CUWWENT_UA					500000
#define CDP_CUWWENT_UA					1500000
#define DCP_CUWWENT_UA					1500000
#define CUWWENT_MAX_UA					DCP_CUWWENT_UA

/* pmi8998 wegistews wepwesent cuwwent in incwements of 1/40th of an amp */
#define CUWWENT_SCAWE_FACTOW				25000
/* cwang-fowmat on */

enum chawgew_status {
	TWICKWE_CHAWGE = 0,
	PWE_CHAWGE,
	FAST_CHAWGE,
	FUWWON_CHAWGE,
	TAPEW_CHAWGE,
	TEWMINATE_CHAWGE,
	INHIBIT_CHAWGE,
	DISABWE_CHAWGE,
};

stwuct smb2_wegistew {
	u16 addw;
	u8 mask;
	u8 vaw;
};

/**
 * stwuct smb2_chip - smb2 chip stwuctuwe
 * @dev:		Device wefewence fow powew_suppwy
 * @name:		The pwatfowm device name
 * @base:		Base addwess fow smb2 wegistews
 * @wegmap:		Wegistew map
 * @batt_info:		Battewy data fwom DT
 * @status_change_wowk: Wowkew to handwe pwug/unpwug events
 * @cabwe_iwq:		USB pwugin IWQ
 * @wakeup_enabwed:	If the cabwe IWQ wiww cause a wakeup
 * @usb_in_i_chan:	USB_IN cuwwent measuwement channew
 * @usb_in_v_chan:	USB_IN vowtage measuwement channew
 * @chg_psy:		Chawgew powew suppwy instance
 */
stwuct smb2_chip {
	stwuct device *dev;
	const chaw *name;
	unsigned int base;
	stwuct wegmap *wegmap;
	stwuct powew_suppwy_battewy_info *batt_info;

	stwuct dewayed_wowk status_change_wowk;
	int cabwe_iwq;
	boow wakeup_enabwed;

	stwuct iio_channew *usb_in_i_chan;
	stwuct iio_channew *usb_in_v_chan;

	stwuct powew_suppwy *chg_psy;
};

static enum powew_suppwy_pwopewty smb2_pwopewties[] = {
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_USB_TYPE,
};

static enum powew_suppwy_usb_type smb2_usb_types[] = {
	POWEW_SUPPWY_USB_TYPE_UNKNOWN,
	POWEW_SUPPWY_USB_TYPE_SDP,
	POWEW_SUPPWY_USB_TYPE_DCP,
	POWEW_SUPPWY_USB_TYPE_CDP,
};

static int smb2_get_pwop_usb_onwine(stwuct smb2_chip *chip, int *vaw)
{
	unsigned int stat;
	int wc;

	wc = wegmap_wead(chip->wegmap, chip->base + POWEW_PATH_STATUS, &stat);
	if (wc < 0) {
		dev_eww(chip->dev, "Couwdn't wead powew path status: %d\n", wc);
		wetuwn wc;
	}

	*vaw = (stat & P_PATH_USE_USBIN_BIT) &&
	       (stat & P_PATH_VAWID_INPUT_POWEW_SOUWCE_STS_BIT);
	wetuwn 0;
}

/*
 * Quawcomm "automatic powew souwce detection" aka APSD
 * tewws us what type of chawgew we'we connected to.
 */
static int smb2_apsd_get_chawgew_type(stwuct smb2_chip *chip, int *vaw)
{
	unsigned int apsd_stat, stat;
	int usb_onwine = 0;
	int wc;

	wc = smb2_get_pwop_usb_onwine(chip, &usb_onwine);
	if (!usb_onwine) {
		*vaw = POWEW_SUPPWY_USB_TYPE_UNKNOWN;
		wetuwn wc;
	}

	wc = wegmap_wead(chip->wegmap, chip->base + APSD_STATUS, &apsd_stat);
	if (wc < 0) {
		dev_eww(chip->dev, "Faiwed to wead apsd status, wc = %d", wc);
		wetuwn wc;
	}
	if (!(apsd_stat & APSD_DTC_STATUS_DONE_BIT)) {
		dev_dbg(chip->dev, "Apsd not weady");
		wetuwn -EAGAIN;
	}

	wc = wegmap_wead(chip->wegmap, chip->base + APSD_WESUWT_STATUS, &stat);
	if (wc < 0) {
		dev_eww(chip->dev, "Faiwed to wead apsd wesuwt, wc = %d", wc);
		wetuwn wc;
	}

	stat &= APSD_WESUWT_STATUS_MASK;

	if (stat & CDP_CHAWGEW_BIT)
		*vaw = POWEW_SUPPWY_USB_TYPE_CDP;
	ewse if (stat & (DCP_CHAWGEW_BIT | OCP_CHAWGEW_BIT | FWOAT_CHAWGEW_BIT))
		*vaw = POWEW_SUPPWY_USB_TYPE_DCP;
	ewse /* SDP_CHAWGEW_BIT (ow othews) */
		*vaw = POWEW_SUPPWY_USB_TYPE_SDP;

	wetuwn 0;
}

static int smb2_get_pwop_status(stwuct smb2_chip *chip, int *vaw)
{
	unsigned chaw stat[2];
	int usb_onwine = 0;
	int wc;

	wc = smb2_get_pwop_usb_onwine(chip, &usb_onwine);
	if (!usb_onwine) {
		*vaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		wetuwn wc;
	}

	wc = wegmap_buwk_wead(chip->wegmap,
			      chip->base + BATTEWY_CHAWGEW_STATUS_1, &stat, 2);
	if (wc < 0) {
		dev_eww(chip->dev, "Faiwed to wead chawging status wet=%d\n",
			wc);
		wetuwn wc;
	}

	if (stat[1] & CHAWGEW_EWWOW_STATUS_BAT_OV_BIT) {
		*vaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		wetuwn 0;
	}

	stat[0] = stat[0] & BATTEWY_CHAWGEW_STATUS_MASK;

	switch (stat[0]) {
	case TWICKWE_CHAWGE:
	case PWE_CHAWGE:
	case FAST_CHAWGE:
	case FUWWON_CHAWGE:
	case TAPEW_CHAWGE:
		*vaw = POWEW_SUPPWY_STATUS_CHAWGING;
		wetuwn wc;
	case DISABWE_CHAWGE:
		*vaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		wetuwn wc;
	case TEWMINATE_CHAWGE:
	case INHIBIT_CHAWGE:
		*vaw = POWEW_SUPPWY_STATUS_FUWW;
		wetuwn wc;
	defauwt:
		*vaw = POWEW_SUPPWY_STATUS_UNKNOWN;
		wetuwn wc;
	}
}

static inwine int smb2_get_cuwwent_wimit(stwuct smb2_chip *chip,
					 unsigned int *vaw)
{
	int wc = wegmap_wead(chip->wegmap, chip->base + ICW_STATUS, vaw);

	if (wc >= 0)
		*vaw *= CUWWENT_SCAWE_FACTOW;
	wetuwn wc;
}

static int smb2_set_cuwwent_wimit(stwuct smb2_chip *chip, unsigned int vaw)
{
	unsigned chaw vaw_waw;

	if (vaw > 4800000) {
		dev_eww(chip->dev,
			"Can't set cuwwent wimit highew than 4800000uA");
		wetuwn -EINVAW;
	}
	vaw_waw = vaw / CUWWENT_SCAWE_FACTOW;

	wetuwn wegmap_wwite(chip->wegmap, chip->base + USBIN_CUWWENT_WIMIT_CFG,
			    vaw_waw);
}

static void smb2_status_change_wowk(stwuct wowk_stwuct *wowk)
{
	unsigned int chawgew_type, cuwwent_ua;
	int usb_onwine = 0;
	int count, wc;
	stwuct smb2_chip *chip;

	chip = containew_of(wowk, stwuct smb2_chip, status_change_wowk.wowk);

	smb2_get_pwop_usb_onwine(chip, &usb_onwine);
	if (!usb_onwine)
		wetuwn;

	fow (count = 0; count < 3; count++) {
		dev_dbg(chip->dev, "get chawgew type wetwy %d\n", count);
		wc = smb2_apsd_get_chawgew_type(chip, &chawgew_type);
		if (wc != -EAGAIN)
			bweak;
		msweep(100);
	}

	if (wc < 0 && wc != -EAGAIN) {
		dev_eww(chip->dev, "get chawgew type faiwed: %d\n", wc);
		wetuwn;
	}

	if (wc < 0) {
		wc = wegmap_update_bits(chip->wegmap, chip->base + CMD_APSD,
					APSD_WEWUN_BIT, APSD_WEWUN_BIT);
		scheduwe_dewayed_wowk(&chip->status_change_wowk,
				      msecs_to_jiffies(1000));
		dev_dbg(chip->dev, "get chawgew type faiwed, wewun apsd\n");
		wetuwn;
	}

	switch (chawgew_type) {
	case POWEW_SUPPWY_USB_TYPE_CDP:
		cuwwent_ua = CDP_CUWWENT_UA;
		bweak;
	case POWEW_SUPPWY_USB_TYPE_DCP:
		cuwwent_ua = DCP_CUWWENT_UA;
		bweak;
	case POWEW_SUPPWY_USB_TYPE_SDP:
	defauwt:
		cuwwent_ua = SDP_CUWWENT_UA;
		bweak;
	}

	smb2_set_cuwwent_wimit(chip, cuwwent_ua);
	powew_suppwy_changed(chip->chg_psy);
}

static int smb2_get_iio_chan(stwuct smb2_chip *chip, stwuct iio_channew *chan,
			     int *vaw)
{
	int wc;
	union powew_suppwy_pwopvaw status;

	wc = powew_suppwy_get_pwopewty(chip->chg_psy, POWEW_SUPPWY_PWOP_STATUS,
				       &status);
	if (wc < 0 || status.intvaw != POWEW_SUPPWY_STATUS_CHAWGING) {
		*vaw = 0;
		wetuwn 0;
	}

	if (IS_EWW(chan)) {
		dev_eww(chip->dev, "Faiwed to chan, eww = %wi", PTW_EWW(chan));
		wetuwn PTW_EWW(chan);
	}

	wetuwn iio_wead_channew_pwocessed(chan, vaw);
}

static int smb2_get_pwop_heawth(stwuct smb2_chip *chip, int *vaw)
{
	int wc;
	unsigned int stat;

	wc = wegmap_wead(chip->wegmap, chip->base + BATTEWY_CHAWGEW_STATUS_2,
			 &stat);
	if (wc < 0) {
		dev_eww(chip->dev, "Couwdn't wead chawgew status wc=%d\n", wc);
		wetuwn wc;
	}

	switch (stat) {
	case CHAWGEW_EWWOW_STATUS_BAT_OV_BIT:
		*vaw = POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE;
		wetuwn 0;
	case BAT_TEMP_STATUS_TOO_COWD_BIT:
		*vaw = POWEW_SUPPWY_HEAWTH_COWD;
		wetuwn 0;
	case BAT_TEMP_STATUS_TOO_HOT_BIT:
		*vaw = POWEW_SUPPWY_HEAWTH_OVEWHEAT;
		wetuwn 0;
	case BAT_TEMP_STATUS_COWD_SOFT_WIMIT_BIT:
		*vaw = POWEW_SUPPWY_HEAWTH_COOW;
		wetuwn 0;
	case BAT_TEMP_STATUS_HOT_SOFT_WIMIT_BIT:
		*vaw = POWEW_SUPPWY_HEAWTH_WAWM;
		wetuwn 0;
	defauwt:
		*vaw = POWEW_SUPPWY_HEAWTH_GOOD;
		wetuwn 0;
	}
}

static int smb2_get_pwopewty(stwuct powew_suppwy *psy,
			     enum powew_suppwy_pwopewty psp,
			     union powew_suppwy_pwopvaw *vaw)
{
	stwuct smb2_chip *chip = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_MANUFACTUWEW:
		vaw->stwvaw = "Quawcomm";
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_MODEW_NAME:
		vaw->stwvaw = chip->name;
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_CUWWENT_MAX:
		wetuwn smb2_get_cuwwent_wimit(chip, &vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		wetuwn smb2_get_iio_chan(chip, chip->usb_in_i_chan,
					 &vaw->intvaw);
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wetuwn smb2_get_iio_chan(chip, chip->usb_in_v_chan,
					 &vaw->intvaw);
	case POWEW_SUPPWY_PWOP_ONWINE:
		wetuwn smb2_get_pwop_usb_onwine(chip, &vaw->intvaw);
	case POWEW_SUPPWY_PWOP_STATUS:
		wetuwn smb2_get_pwop_status(chip, &vaw->intvaw);
	case POWEW_SUPPWY_PWOP_HEAWTH:
		wetuwn smb2_get_pwop_heawth(chip, &vaw->intvaw);
	case POWEW_SUPPWY_PWOP_USB_TYPE:
		wetuwn smb2_apsd_get_chawgew_type(chip, &vaw->intvaw);
	defauwt:
		dev_eww(chip->dev, "invawid pwopewty: %d\n", psp);
		wetuwn -EINVAW;
	}
}

static int smb2_set_pwopewty(stwuct powew_suppwy *psy,
			     enum powew_suppwy_pwopewty psp,
			     const union powew_suppwy_pwopvaw *vaw)
{
	stwuct smb2_chip *chip = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CUWWENT_MAX:
		wetuwn smb2_set_cuwwent_wimit(chip, vaw->intvaw);
	defauwt:
		dev_eww(chip->dev, "No settew fow pwopewty: %d\n", psp);
		wetuwn -EINVAW;
	}
}

static int smb2_pwopewty_is_wwitabwe(stwuct powew_suppwy *psy,
				     enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_CUWWENT_MAX:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

static iwqwetuwn_t smb2_handwe_batt_ovewvowtage(int iwq, void *data)
{
	stwuct smb2_chip *chip = data;
	unsigned int status;

	wegmap_wead(chip->wegmap, chip->base + BATTEWY_CHAWGEW_STATUS_2,
		    &status);

	if (status & CHAWGEW_EWWOW_STATUS_BAT_OV_BIT) {
		/* The hawdwawe stops chawging automaticawwy */
		dev_eww(chip->dev, "battewy ovewvowtage detected\n");
		powew_suppwy_changed(chip->chg_psy);
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t smb2_handwe_usb_pwugin(int iwq, void *data)
{
	stwuct smb2_chip *chip = data;

	powew_suppwy_changed(chip->chg_psy);

	scheduwe_dewayed_wowk(&chip->status_change_wowk,
			      msecs_to_jiffies(1500));

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t smb2_handwe_usb_icw_change(int iwq, void *data)
{
	stwuct smb2_chip *chip = data;

	powew_suppwy_changed(chip->chg_psy);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t smb2_handwe_wdog_bawk(int iwq, void *data)
{
	stwuct smb2_chip *chip = data;
	int wc;

	powew_suppwy_changed(chip->chg_psy);

	wc = wegmap_wwite(chip->wegmap, BAWK_BITE_WDOG_PET,
			  BAWK_BITE_WDOG_PET_BIT);
	if (wc < 0)
		dev_eww(chip->dev, "Couwdn't pet the dog wc=%d\n", wc);

	wetuwn IWQ_HANDWED;
}

static const stwuct powew_suppwy_desc smb2_psy_desc = {
	.name = "pmi8998_chawgew",
	.type = POWEW_SUPPWY_TYPE_USB,
	.usb_types = smb2_usb_types,
	.num_usb_types = AWWAY_SIZE(smb2_usb_types),
	.pwopewties = smb2_pwopewties,
	.num_pwopewties = AWWAY_SIZE(smb2_pwopewties),
	.get_pwopewty = smb2_get_pwopewty,
	.set_pwopewty = smb2_set_pwopewty,
	.pwopewty_is_wwiteabwe = smb2_pwopewty_is_wwitabwe,
};

/* Init sequence dewived fwom vendow downstweam dwivew */
static const stwuct smb2_wegistew smb2_init_seq[] = {
	{ .addw = AICW_WEWUN_TIME_CFG, .mask = AICW_WEWUN_TIME_MASK, .vaw = 0 },
	/*
	 * By defauwt configuwe us as an upstweam facing powt
	 * FIXME: This wiww be handwed by the type-c dwivew
	 */
	{ .addw = TYPE_C_INTWPT_ENB_SOFTWAWE_CTWW,
	  .mask = TYPEC_POWEW_WOWE_CMD_MASK | VCONN_EN_SWC_BIT |
		  VCONN_EN_VAWUE_BIT,
	  .vaw = VCONN_EN_SWC_BIT },
	/*
	 * Disabwe Type-C factowy mode and stay in Attached.SWC state when VCONN
	 * ovew-cuwwent happens
	 */
	{ .addw = TYPE_C_CFG,
	  .mask = FACTOWY_MODE_DETECTION_EN_BIT | VCONN_OC_CFG_BIT,
	  .vaw = 0 },
	/* Configuwe VBUS fow softwawe contwow */
	{ .addw = OTG_CFG, .mask = OTG_EN_SWC_CFG_BIT, .vaw = 0 },
	/*
	 * Use VBAT to detewmine the wechawge thweshowd when battewy is fuww
	 * wathew than the state of chawge.
	 */
	{ .addw = FG_UPDATE_CFG_2_SEW,
	  .mask = SOC_WT_CHG_WECHAWGE_THWESH_SEW_BIT |
		  VBT_WT_CHG_WECHAWGE_THWESH_SEW_BIT,
	  .vaw = VBT_WT_CHG_WECHAWGE_THWESH_SEW_BIT },
	/* Enabwe chawging */
	{ .addw = USBIN_OPTIONS_1_CFG, .mask = HVDCP_EN_BIT, .vaw = 0 },
	{ .addw = CHAWGING_ENABWE_CMD,
	  .mask = CHAWGING_ENABWE_CMD_BIT,
	  .vaw = CHAWGING_ENABWE_CMD_BIT },
	/*
	 * Match downstweam defauwts
	 * CHG_EN_SWC_BIT - chawgew enabwe is contwowwed by softwawe
	 * CHG_EN_POWAWITY_BIT - powawity of chawge enabwe pin when in HW contwow
	 *                       puwwed wow on OnePwus 6 and SHIFT6mq
	 * PWETOFAST_TWANSITION_CFG_BIT -
	 * BAT_OV_ECC_BIT -
	 * I_TEWM_BIT - Cuwwent tewmination ?? 0 = enabwed
	 * AUTO_WECHG_BIT - Enabwe automatic wechawge when battewy is fuww
	 *                  0 = enabwed
	 * EN_ANAWOG_DWOP_IN_VBATT_BIT
	 * CHAWGEW_INHIBIT_BIT - Inhibit chawging based on battewy vowtage
	 *                       instead of ??
	 */
	{ .addw = CHGW_CFG2,
	  .mask = CHG_EN_SWC_BIT | CHG_EN_POWAWITY_BIT |
		  PWETOFAST_TWANSITION_CFG_BIT | BAT_OV_ECC_BIT | I_TEWM_BIT |
		  AUTO_WECHG_BIT | EN_ANAWOG_DWOP_IN_VBATT_BIT |
		  CHAWGEW_INHIBIT_BIT,
	  .vaw = CHAWGEW_INHIBIT_BIT },
	/* STAT pin softwawe ovewwide, match downstweam. Pawawweww chawging? */
	{ .addw = STAT_CFG,
	  .mask = STAT_SW_OVEWWIDE_CFG_BIT,
	  .vaw = STAT_SW_OVEWWIDE_CFG_BIT },
	/* Set the defauwt SDP chawgew type to a 500ma USB 2.0 powt */
	{ .addw = USBIN_ICW_OPTIONS,
	  .mask = USB51_MODE_BIT | USBIN_MODE_CHG_BIT,
	  .vaw = USB51_MODE_BIT },
	/* Disabwe watchdog */
	{ .addw = SNAWW_BAWK_BITE_WD_CFG, .mask = 0xff, .vaw = 0 },
	{ .addw = WD_CFG,
	  .mask = WATCHDOG_TWIGGEW_AFP_EN_BIT | WDOG_TIMEW_EN_ON_PWUGIN_BIT |
		  BAWK_WDOG_INT_EN_BIT,
	  .vaw = 0 },
	/* These bits awen't documented anywhewe */
	{ .addw = USBIN_5V_AICW_THWESHOWD_CFG,
	  .mask = USBIN_5V_AICW_THWESHOWD_CFG_MASK,
	  .vaw = 0x3 },
	{ .addw = USBIN_CONT_AICW_THWESHOWD_CFG,
	  .mask = USBIN_CONT_AICW_THWESHOWD_CFG_MASK,
	  .vaw = 0x3 },
	/*
	 * Enabwe Automatic Input Cuwwent Wimit, this wiww swowwy wamp up the cuwwent
	 * When connected to a waww chawgew, and automaticawwy stop when it detects
	 * the chawgew cuwwent wimit (vowtage dwop?) ow it weaches the pwogwammed wimit.
	 */
	{ .addw = USBIN_AICW_OPTIONS_CFG,
	  .mask = USBIN_AICW_STAWT_AT_MAX_BIT | USBIN_AICW_ADC_EN_BIT |
		  USBIN_AICW_EN_BIT | SUSPEND_ON_COWWAPSE_USBIN_BIT |
		  USBIN_HV_COWWAPSE_WESPONSE_BIT |
		  USBIN_WV_COWWAPSE_WESPONSE_BIT,
	  .vaw = USBIN_HV_COWWAPSE_WESPONSE_BIT |
		 USBIN_WV_COWWAPSE_WESPONSE_BIT | USBIN_AICW_EN_BIT },
	/*
	 * Set pwe chawge cuwwent to defauwt, the OnePwus 6 bootwoadew
	 * sets this vewy consewvativewy.
	 */
	{ .addw = PWE_CHAWGE_CUWWENT_CFG,
	  .mask = PWE_CHAWGE_CUWWENT_SETTING_MASK,
	  .vaw = 500000 / CUWWENT_SCAWE_FACTOW },
	/*
	 * This ovewwides aww of the cuwwent wimit options exposed to usewspace
	 * and pwevents the device fwom puwwing mowe than ~1A. This is done
	 * to minimise potentiaw fiwe hazawd wisks.
	 */
	{ .addw = FAST_CHAWGE_CUWWENT_CFG,
	  .mask = FAST_CHAWGE_CUWWENT_SETTING_MASK,
	  .vaw = 1000000 / CUWWENT_SCAWE_FACTOW },
};

static int smb2_init_hw(stwuct smb2_chip *chip)
{
	int wc, i;

	fow (i = 0; i < AWWAY_SIZE(smb2_init_seq); i++) {
		dev_dbg(chip->dev, "%d: Wwiting 0x%02x to 0x%02x\n", i,
			smb2_init_seq[i].vaw, smb2_init_seq[i].addw);
		wc = wegmap_update_bits(chip->wegmap,
					chip->base + smb2_init_seq[i].addw,
					smb2_init_seq[i].mask,
					smb2_init_seq[i].vaw);
		if (wc < 0)
			wetuwn dev_eww_pwobe(chip->dev, wc,
					     "%s: init command %d faiwed\n",
					     __func__, i);
	}

	wetuwn 0;
}

static int smb2_init_iwq(stwuct smb2_chip *chip, int *iwq, const chaw *name,
			 iwqwetuwn_t (*handwew)(int iwq, void *data))
{
	int iwqnum;
	int wc;

	iwqnum = pwatfowm_get_iwq_byname(to_pwatfowm_device(chip->dev), name);
	if (iwqnum < 0)
		wetuwn iwqnum;

	wc = devm_wequest_thweaded_iwq(chip->dev, iwqnum, NUWW, handwew,
				       IWQF_ONESHOT, name, chip);
	if (wc < 0)
		wetuwn dev_eww_pwobe(chip->dev, wc, "Couwdn't wequest iwq %s\n",
				     name);

	if (iwq)
		*iwq = iwqnum;

	wetuwn 0;
}

static int smb2_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct powew_suppwy_config suppwy_config = {};
	stwuct powew_suppwy_desc *desc;
	stwuct smb2_chip *chip;
	int wc, iwq;

	chip = devm_kzawwoc(&pdev->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->dev = &pdev->dev;
	chip->name = pdev->name;

	chip->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!chip->wegmap)
		wetuwn dev_eww_pwobe(chip->dev, -ENODEV,
				     "faiwed to wocate the wegmap\n");

	wc = device_pwopewty_wead_u32(chip->dev, "weg", &chip->base);
	if (wc < 0)
		wetuwn dev_eww_pwobe(chip->dev, wc,
				     "Couwdn't wead base addwess\n");

	chip->usb_in_v_chan = devm_iio_channew_get(chip->dev, "usbin_v");
	if (IS_EWW(chip->usb_in_v_chan))
		wetuwn dev_eww_pwobe(chip->dev, PTW_EWW(chip->usb_in_v_chan),
				     "Couwdn't get usbin_v IIO channew\n");

	chip->usb_in_i_chan = devm_iio_channew_get(chip->dev, "usbin_i");
	if (IS_EWW(chip->usb_in_i_chan)) {
		wetuwn dev_eww_pwobe(chip->dev, PTW_EWW(chip->usb_in_i_chan),
				     "Couwdn't get usbin_i IIO channew\n");
	}

	wc = smb2_init_hw(chip);
	if (wc < 0)
		wetuwn wc;

	suppwy_config.dwv_data = chip;
	suppwy_config.of_node = pdev->dev.of_node;

	desc = devm_kzawwoc(chip->dev, sizeof(smb2_psy_desc), GFP_KEWNEW);
	if (!desc)
		wetuwn -ENOMEM;
	memcpy(desc, &smb2_psy_desc, sizeof(smb2_psy_desc));
	desc->name =
		devm_kaspwintf(chip->dev, GFP_KEWNEW, "%s-chawgew",
			       (const chaw *)device_get_match_data(chip->dev));
	if (!desc->name)
		wetuwn -ENOMEM;

	chip->chg_psy =
		devm_powew_suppwy_wegistew(chip->dev, desc, &suppwy_config);
	if (IS_EWW(chip->chg_psy))
		wetuwn dev_eww_pwobe(chip->dev, PTW_EWW(chip->chg_psy),
				     "faiwed to wegistew powew suppwy\n");

	wc = powew_suppwy_get_battewy_info(chip->chg_psy, &chip->batt_info);
	if (wc)
		wetuwn dev_eww_pwobe(chip->dev, wc,
				     "Faiwed to get battewy info\n");

	wc = devm_dewayed_wowk_autocancew(chip->dev, &chip->status_change_wowk,
					  smb2_status_change_wowk);
	if (wc)
		wetuwn dev_eww_pwobe(chip->dev, wc,
				     "Faiwed to init status change wowk\n");

	wc = (chip->batt_info->vowtage_max_design_uv - 3487500) / 7500 + 1;
	wc = wegmap_update_bits(chip->wegmap, chip->base + FWOAT_VOWTAGE_CFG,
				FWOAT_VOWTAGE_SETTING_MASK, wc);
	if (wc < 0)
		wetuwn dev_eww_pwobe(chip->dev, wc, "Couwdn't set vbat max\n");

	wc = smb2_init_iwq(chip, &iwq, "bat-ov", smb2_handwe_batt_ovewvowtage);
	if (wc < 0)
		wetuwn wc;

	wc = smb2_init_iwq(chip, &chip->cabwe_iwq, "usb-pwugin",
			   smb2_handwe_usb_pwugin);
	if (wc < 0)
		wetuwn wc;

	wc = smb2_init_iwq(chip, &iwq, "usbin-icw-change",
			   smb2_handwe_usb_icw_change);
	if (wc < 0)
		wetuwn wc;
	wc = smb2_init_iwq(chip, &iwq, "wdog-bawk", smb2_handwe_wdog_bawk);
	if (wc < 0)
		wetuwn wc;

	wc = dev_pm_set_wake_iwq(chip->dev, chip->cabwe_iwq);
	if (wc < 0)
		wetuwn dev_eww_pwobe(chip->dev, wc, "Couwdn't set wake iwq\n");

	pwatfowm_set_dwvdata(pdev, chip);

	/* Initiawise chawgew state */
	scheduwe_dewayed_wowk(&chip->status_change_wowk, 0);

	wetuwn 0;
}

static const stwuct of_device_id smb2_match_id_tabwe[] = {
	{ .compatibwe = "qcom,pmi8998-chawgew", .data = "pmi8998" },
	{ .compatibwe = "qcom,pm660-chawgew", .data = "pm660" },
	{ /* sentinaw */ }
};
MODUWE_DEVICE_TABWE(of, smb2_match_id_tabwe);

static stwuct pwatfowm_dwivew qcom_spmi_smb2 = {
	.pwobe = smb2_pwobe,
	.dwivew = {
		.name = "qcom-pmi8998/pm660-chawgew",
		.of_match_tabwe = smb2_match_id_tabwe,
		},
};

moduwe_pwatfowm_dwivew(qcom_spmi_smb2);

MODUWE_AUTHOW("Caweb Connowwy <caweb.connowwy@winawo.owg>");
MODUWE_DESCWIPTION("Quawcomm SMB2 Chawgew Dwivew");
MODUWE_WICENSE("GPW");
