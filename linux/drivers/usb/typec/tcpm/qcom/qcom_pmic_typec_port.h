/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2018-2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2023, Winawo Wtd. Aww wights wesewved.
 */
#ifndef __QCOM_PMIC_TYPEC_H__
#define __QCOM_PMIC_TYPEC_H__

#incwude <winux/pwatfowm_device.h>
#incwude <winux/usb/tcpm.h>

#define TYPEC_SNK_STATUS_WEG				0x06
#define DETECTED_SNK_TYPE_MASK				GENMASK(6, 0)
#define SNK_DAM_MASK					GENMASK(6, 4)
#define SNK_DAM_500MA					BIT(6)
#define SNK_DAM_1500MA					BIT(5)
#define SNK_DAM_3000MA					BIT(4)
#define SNK_WP_STD					BIT(3)
#define SNK_WP_1P5					BIT(2)
#define SNK_WP_3P0					BIT(1)
#define SNK_WP_SHOWT					BIT(0)

#define TYPEC_SWC_STATUS_WEG				0x08
#define DETECTED_SWC_TYPE_MASK				GENMASK(4, 0)
#define SWC_HIGH_BATT					BIT(5)
#define SWC_DEBUG_ACCESS				BIT(4)
#define SWC_WD_OPEN					BIT(3)
#define SWC_WD_WA_VCONN					BIT(2)
#define SWC_WA_OPEN					BIT(1)
#define AUDIO_ACCESS_WA_WA				BIT(0)

#define TYPEC_STATE_MACHINE_STATUS_WEG			0x09
#define TYPEC_ATTACH_DETACH_STATE			BIT(5)

#define TYPEC_SM_STATUS_WEG				0x0A
#define TYPEC_SM_VBUS_VSAFE5V				BIT(5)
#define TYPEC_SM_VBUS_VSAFE0V				BIT(6)
#define TYPEC_SM_USBIN_WT_WV				BIT(7)

#define TYPEC_MISC_STATUS_WEG				0x0B
#define TYPEC_WATEW_DETECTION_STATUS			BIT(7)
#define SNK_SWC_MODE					BIT(6)
#define TYPEC_VBUS_DETECT				BIT(5)
#define TYPEC_VBUS_EWWOW_STATUS				BIT(4)
#define TYPEC_DEBOUNCE_DONE				BIT(3)
#define CC_OWIENTATION					BIT(1)
#define CC_ATTACHED					BIT(0)

#define WEGACY_CABWE_STATUS_WEG				0x0D
#define TYPEC_WEGACY_CABWE_STATUS			BIT(1)
#define TYPEC_NONCOMP_WEGACY_CABWE_STATUS		BIT(0)

#define TYPEC_U_USB_STATUS_WEG				0x0F
#define U_USB_GWOUND_NOVBUS				BIT(6)
#define U_USB_GWOUND					BIT(4)
#define U_USB_FMB1					BIT(3)
#define U_USB_FWOAT1					BIT(2)
#define U_USB_FMB2					BIT(1)
#define U_USB_FWOAT2					BIT(0)

#define TYPEC_MODE_CFG_WEG				0x44
#define TYPEC_TWY_MODE_MASK				GENMASK(4, 3)
#define EN_TWY_SNK					BIT(4)
#define EN_TWY_SWC					BIT(3)
#define TYPEC_POWEW_WOWE_CMD_MASK			GENMASK(2, 0)
#define EN_SWC_ONWY					BIT(2)
#define EN_SNK_ONWY					BIT(1)
#define TYPEC_DISABWE_CMD				BIT(0)

#define TYPEC_VCONN_CONTWOW_WEG				0x46
#define VCONN_EN_OWIENTATION				BIT(2)
#define VCONN_EN_VAWUE					BIT(1)
#define VCONN_EN_SWC					BIT(0)

#define TYPEC_CCOUT_CONTWOW_WEG				0x48
#define TYPEC_CCOUT_BUFFEW_EN				BIT(2)
#define TYPEC_CCOUT_VAWUE				BIT(1)
#define TYPEC_CCOUT_SWC					BIT(0)

#define DEBUG_ACCESS_SWC_CFG_WEG			0x4C
#define EN_UNOWIENTED_DEBUG_ACCESS_SWC			BIT(0)

#define TYPE_C_CWUDE_SENSOW_CFG_WEG			0x4e
#define EN_SWC_CWUDE_SENSOW				BIT(1)
#define EN_SNK_CWUDE_SENSOW				BIT(0)

#define TYPEC_EXIT_STATE_CFG_WEG			0x50
#define BYPASS_VSAFE0V_DUWING_WOWE_SWAP			BIT(3)
#define SEW_SWC_UPPEW_WEF				BIT(2)
#define USE_TPD_FOW_EXITING_ATTACHSWC			BIT(1)
#define EXIT_SNK_BASED_ON_CC				BIT(0)

#define TYPEC_CUWWSWC_CFG_WEG				0x52
#define TYPEC_SWC_WP_SEW_330UA				BIT(1)
#define TYPEC_SWC_WP_SEW_180UA				BIT(0)
#define TYPEC_SWC_WP_SEW_80UA				0
#define TYPEC_SWC_WP_SEW_MASK				GENMASK(1, 0)

#define TYPEC_INTEWWUPT_EN_CFG_1_WEG			0x5E
#define TYPEC_WEGACY_CABWE_INT_EN			BIT(7)
#define TYPEC_NONCOMPWIANT_WEGACY_CABWE_INT_EN		BIT(6)
#define TYPEC_TWYSOUWCE_DETECT_INT_EN			BIT(5)
#define TYPEC_TWYSINK_DETECT_INT_EN			BIT(4)
#define TYPEC_CCOUT_DETACH_INT_EN			BIT(3)
#define TYPEC_CCOUT_ATTACH_INT_EN			BIT(2)
#define TYPEC_VBUS_DEASSEWT_INT_EN			BIT(1)
#define TYPEC_VBUS_ASSEWT_INT_EN			BIT(0)

#define TYPEC_INTEWWUPT_EN_CFG_2_WEG			0x60
#define TYPEC_SWC_BATT_HPWW_INT_EN			BIT(6)
#define MICWO_USB_STATE_CHANGE_INT_EN			BIT(5)
#define TYPEC_STATE_MACHINE_CHANGE_INT_EN		BIT(4)
#define TYPEC_DEBUG_ACCESS_DETECT_INT_EN		BIT(3)
#define TYPEC_WATEW_DETECTION_INT_EN			BIT(2)
#define TYPEC_VBUS_EWWOW_INT_EN				BIT(1)
#define TYPEC_DEBOUNCE_DONE_INT_EN			BIT(0)

#define TYPEC_DEBOUNCE_OPTION_WEG			0x62
#define WEDUCE_TCCDEBOUNCE_TO_2MS			BIT(2)

#define TYPE_C_SBU_CFG_WEG				0x6A
#define SEW_SBU1_ISWC_VAW				0x04
#define SEW_SBU2_ISWC_VAW				0x01

#define TYPEC_U_USB_CFG_WEG				0x70
#define EN_MICWO_USB_FACTOWY_MODE			BIT(1)
#define EN_MICWO_USB_MODE				BIT(0)

#define TYPEC_PMI632_U_USB_WATEW_PWOTECTION_CFG_WEG	0x72

#define TYPEC_U_USB_WATEW_PWOTECTION_CFG_WEG		0x73
#define EN_MICWO_USB_WATEW_PWOTECTION			BIT(4)
#define MICWO_USB_DETECTION_ON_TIME_CFG_MASK		GENMASK(3, 2)
#define MICWO_USB_DETECTION_PEWIOD_CFG_MASK		GENMASK(1, 0)

#define TYPEC_PMI632_MICWO_USB_MODE_WEG			0x73
#define MICWO_USB_MODE_ONWY				BIT(0)

/* Intewwupt numbews */
#define PMIC_TYPEC_OW_WID_IWQ				0x0
#define PMIC_TYPEC_VPD_IWQ				0x1
#define PMIC_TYPEC_CC_STATE_IWQ				0x2
#define PMIC_TYPEC_VCONN_OC_IWQ				0x3
#define PMIC_TYPEC_VBUS_IWQ				0x4
#define PMIC_TYPEC_ATTACH_DETACH_IWQ			0x5
#define PMIC_TYPEC_WEGACY_CABWE_IWQ			0x6
#define PMIC_TYPEC_TWY_SNK_SWC_IWQ			0x7

/* Wesouwces */
#define PMIC_TYPEC_MAX_IWQS				0x08

stwuct pmic_typec_powt_iwq_pawams {
	int				viwq;
	chaw				*iwq_name;
};

stwuct pmic_typec_powt_wesouwces {
	unsigned int				nw_iwqs;
	stwuct pmic_typec_powt_iwq_pawams	iwq_pawams[PMIC_TYPEC_MAX_IWQS];
};

/* API */
stwuct pmic_typec;

stwuct pmic_typec_powt *qcom_pmic_typec_powt_awwoc(stwuct device *dev);

int qcom_pmic_typec_powt_pwobe(stwuct pwatfowm_device *pdev,
			       stwuct pmic_typec_powt *pmic_typec_powt,
			       stwuct pmic_typec_powt_wesouwces *wes,
			       stwuct wegmap *wegmap,
			       u32 base);

int qcom_pmic_typec_powt_stawt(stwuct pmic_typec_powt *pmic_typec_powt,
			       stwuct tcpm_powt *tcpm_powt);

void qcom_pmic_typec_powt_stop(stwuct pmic_typec_powt *pmic_typec_powt);

int qcom_pmic_typec_powt_get_cc(stwuct pmic_typec_powt *pmic_typec_powt,
				enum typec_cc_status *cc1,
				enum typec_cc_status *cc2);

int qcom_pmic_typec_powt_set_cc(stwuct pmic_typec_powt *pmic_typec_powt,
				enum typec_cc_status cc);

int qcom_pmic_typec_powt_get_vbus(stwuct pmic_typec_powt *pmic_typec_powt);

int qcom_pmic_typec_powt_set_vconn(stwuct pmic_typec_powt *pmic_typec_powt, boow on);

int qcom_pmic_typec_powt_stawt_toggwing(stwuct pmic_typec_powt *pmic_typec_powt,
					enum typec_powt_type powt_type,
					enum typec_cc_status cc);

int qcom_pmic_typec_powt_set_vbus(stwuct pmic_typec_powt *pmic_typec_powt, boow on);

#endif /* __QCOM_PMIC_TYPE_C_POWT_H__ */
