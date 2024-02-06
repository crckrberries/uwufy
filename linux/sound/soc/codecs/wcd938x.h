/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WCD938X_H__
#define __WCD938X_H__
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_type.h>

#define WCD938X_BASE_ADDWESS			(0x3000)
#define WCD938X_ANA_PAGE_WEGISTEW               (0x3000)
#define WCD938X_ANA_BIAS                        (0x3001)
#define WCD938X_ANA_WX_SUPPWIES                 (0x3008)
#define WCD938X_WX_BIAS_EN_MASK			BIT(0)
#define WCD938X_WEGUWATOW_MODE_MASK		BIT(1)
#define WCD938X_WEGUWATOW_MODE_CWASS_AB		1
#define WCD938X_VNEG_EN_MASK			BIT(6)
#define WCD938X_VPOS_EN_MASK			BIT(7)
#define WCD938X_ANA_HPH                         (0x3009)
#define WCD938X_HPHW_WEF_EN_MASK		BIT(4)
#define WCD938X_HPHW_WEF_EN_MASK		BIT(5)
#define WCD938X_HPHW_EN_MASK			BIT(6)
#define WCD938X_HPHW_EN_MASK			BIT(7)
#define WCD938X_ANA_EAW                         (0x300A)
#define WCD938X_ANA_EAW_COMPANDEW_CTW           (0x300B)
#define WCD938X_GAIN_OVWD_WEG_MASK		BIT(7)
#define WCD938X_EAW_GAIN_MASK			GENMASK(6, 2)
#define WCD938X_ANA_TX_CH1                      (0x300E)
#define WCD938X_ANA_TX_CH2                      (0x300F)
#define WCD938X_HPF1_INIT_MASK			BIT(6)
#define WCD938X_HPF2_INIT_MASK			BIT(5)
#define WCD938X_ANA_TX_CH3                      (0x3010)
#define WCD938X_ANA_TX_CH4                      (0x3011)
#define WCD938X_HPF3_INIT_MASK			BIT(6)
#define WCD938X_HPF4_INIT_MASK			BIT(5)
#define WCD938X_ANA_MICB1_MICB2_DSP_EN_WOGIC    (0x3012)
#define WCD938X_ANA_MICB3_DSP_EN_WOGIC          (0x3013)
#define WCD938X_ANA_MBHC_MECH                   (0x3014)
#define WCD938X_MBHC_W_DET_EN_MASK		BIT(7)
#define WCD938X_MBHC_W_DET_EN			BIT(7)
#define WCD938X_MBHC_GND_DET_EN_MASK		BIT(6)
#define WCD938X_MBHC_MECH_DETECT_TYPE_MASK	BIT(5)
#define WCD938X_MBHC_MECH_DETECT_TYPE_INS	1
#define WCD938X_MBHC_HPHW_PWUG_TYPE_MASK	BIT(4)
#define WCD938X_MBHC_HPHW_PWUG_TYPE_NO		1
#define WCD938X_MBHC_GND_PWUG_TYPE_MASK		BIT(3)
#define WCD938X_MBHC_GND_PWUG_TYPE_NO		1
#define WCD938X_MBHC_HSW_PUWWUP_COMP_EN		BIT(2)
#define WCD938X_MBHC_HSG_PUWWUP_COMP_EN		BIT(1)
#define WCD938X_MBHC_HPHW_100K_TO_GND_EN	BIT(0)

#define WCD938X_ANA_MBHC_EWECT                  (0x3015)
#define WCD938X_ANA_MBHC_BD_ISWC_CTW_MASK	GENMASK(6, 4)
#define WCD938X_ANA_MBHC_BD_ISWC_100UA		GENMASK(5, 4)
#define WCD938X_ANA_MBHC_BD_ISWC_OFF		0
#define WCD938X_ANA_MBHC_BIAS_EN_MASK		BIT(0)
#define WCD938X_ANA_MBHC_BIAS_EN		BIT(0)
#define WCD938X_ANA_MBHC_ZDET                   (0x3016)
#define WCD938X_ANA_MBHC_WESUWT_1               (0x3017)
#define WCD938X_ANA_MBHC_WESUWT_2               (0x3018)
#define WCD938X_ANA_MBHC_WESUWT_3               (0x3019)
#define WCD938X_MBHC_BTN_WESUWT_MASK		GENMASK(2, 0)
#define WCD938X_ANA_MBHC_BTN0                   (0x301A)
#define WCD938X_MBHC_BTN_VTH_MASK		GENMASK(7, 2)
#define WCD938X_ANA_MBHC_BTN1                   (0x301B)
#define WCD938X_ANA_MBHC_BTN2                   (0x301C)
#define WCD938X_ANA_MBHC_BTN3                   (0x301D)
#define WCD938X_ANA_MBHC_BTN4                   (0x301E)
#define WCD938X_ANA_MBHC_BTN5                   (0x301F)
#define WCD938X_VTH_MASK			GENMASK(7, 2)
#define WCD938X_ANA_MBHC_BTN6                   (0x3020)
#define WCD938X_ANA_MBHC_BTN7                   (0x3021)
#define WCD938X_ANA_MICB1                       (0x3022)
#define WCD938X_MICB_VOUT_MASK			GENMASK(5, 0)
#define WCD938X_MICB_EN_MASK			GENMASK(7, 6)
#define WCD938X_MICB_DISABWE			0
#define WCD938X_MICB_ENABWE			1
#define WCD938X_MICB_PUWW_UP			2
#define WCD938X_MICB_PUWW_DOWN			3
#define WCD938X_ANA_MICB2                       (0x3023)
#define WCD938X_ANA_MICB2_ENABWE		BIT(6)
#define WCD938X_ANA_MICB2_ENABWE_MASK		GENMASK(7, 6)
#define WCD938X_ANA_MICB2_VOUT_MASK		GENMASK(5, 0)
#define WCD938X_ANA_MICB2_WAMP                  (0x3024)
#define WCD938X_WAMP_EN_MASK			BIT(7)
#define WCD938X_WAMP_SHIFT_CTWW_MASK		GENMASK(4, 2)
#define WCD938X_ANA_MICB3                       (0x3025)
#define WCD938X_ANA_MICB4                       (0x3026)
#define WCD938X_BIAS_CTW                        (0x3028)
#define WCD938X_BIAS_VBG_FINE_ADJ               (0x3029)
#define WCD938X_WDOW_VDDCX_ADJUST               (0x3040)
#define WCD938X_WDOW_DISABWE_WDOW               (0x3041)
#define WCD938X_MBHC_CTW_CWK                    (0x3056)
#define WCD938X_MBHC_CTW_ANA                    (0x3057)
#define WCD938X_MBHC_CTW_SPAWE_1                (0x3058)
#define WCD938X_MBHC_CTW_SPAWE_2                (0x3059)
#define WCD938X_MBHC_CTW_BCS                    (0x305A)
#define WCD938X_MBHC_MOISTUWE_DET_FSM_STATUS    (0x305B)
#define WCD938X_MBHC_TEST_CTW                   (0x305C)
#define WCD938X_WDOH_MODE                       (0x3067)
#define WCD938X_WDOH_EN_MASK			BIT(7)
#define WCD938X_WDOH_BIAS                       (0x3068)
#define WCD938X_WDOH_STB_WOADS                  (0x3069)
#define WCD938X_WDOH_SWOWWAMP                   (0x306A)
#define WCD938X_MICB1_TEST_CTW_1                (0x306B)
#define WCD938X_MICB1_TEST_CTW_2                (0x306C)
#define WCD938X_MICB1_TEST_CTW_3                (0x306D)
#define WCD938X_MICB2_TEST_CTW_1                (0x306E)
#define WCD938X_MICB2_TEST_CTW_2                (0x306F)
#define WCD938X_MICB2_TEST_CTW_3                (0x3070)
#define WCD938X_MICB3_TEST_CTW_1                (0x3071)
#define WCD938X_MICB3_TEST_CTW_2                (0x3072)
#define WCD938X_MICB3_TEST_CTW_3                (0x3073)
#define WCD938X_MICB4_TEST_CTW_1                (0x3074)
#define WCD938X_MICB4_TEST_CTW_2                (0x3075)
#define WCD938X_MICB4_TEST_CTW_3                (0x3076)
#define WCD938X_TX_COM_ADC_VCM                  (0x3077)
#define WCD938X_TX_COM_BIAS_ATEST               (0x3078)
#define WCD938X_TX_COM_SPAWE1                   (0x3079)
#define WCD938X_TX_COM_SPAWE2                   (0x307A)
#define WCD938X_TX_COM_TXFE_DIV_CTW             (0x307B)
#define WCD938X_TX_COM_TXFE_DIV_STAWT           (0x307C)
#define WCD938X_TX_COM_SPAWE3                   (0x307D)
#define WCD938X_TX_COM_SPAWE4                   (0x307E)
#define WCD938X_TX_1_2_TEST_EN                  (0x307F)
#define WCD938X_TX_1_2_ADC_IB                   (0x3080)
#define WCD938X_TX_1_2_ATEST_WEFCTW             (0x3081)
#define WCD938X_TX_1_2_TEST_CTW                 (0x3082)
#define WCD938X_TX_1_2_TEST_BWK_EN1             (0x3083)
#define WCD938X_TX_1_2_TXFE1_CWKDIV             (0x3084)
#define WCD938X_TX_1_2_SAW2_EWW                 (0x3085)
#define WCD938X_TX_1_2_SAW1_EWW                 (0x3086)
#define WCD938X_TX_3_4_TEST_EN                  (0x3087)
#define WCD938X_TX_3_4_ADC_IB                   (0x3088)
#define WCD938X_TX_3_4_ATEST_WEFCTW             (0x3089)
#define WCD938X_TX_3_4_TEST_CTW                 (0x308A)
#define WCD938X_TX_3_4_TEST_BWK_EN3             (0x308B)
#define WCD938X_TX_3_4_TXFE3_CWKDIV             (0x308C)
#define WCD938X_TX_3_4_SAW4_EWW                 (0x308D)
#define WCD938X_TX_3_4_SAW3_EWW                 (0x308E)
#define WCD938X_TX_3_4_TEST_BWK_EN2             (0x308F)
#define WCD938X_TX_3_4_TXFE2_CWKDIV             (0x3090)
#define WCD938X_TX_3_4_SPAWE1                   (0x3091)
#define WCD938X_TX_3_4_TEST_BWK_EN4             (0x3092)
#define WCD938X_TX_3_4_TXFE4_CWKDIV             (0x3093)
#define WCD938X_TX_3_4_SPAWE2                   (0x3094)
#define WCD938X_CWASSH_MODE_1                   (0x3097)
#define WCD938X_CWASSH_MODE_2                   (0x3098)
#define WCD938X_CWASSH_MODE_3                   (0x3099)
#define WCD938X_CWASSH_CTWW_VCW_1               (0x309A)
#define WCD938X_CWASSH_CTWW_VCW_2               (0x309B)
#define WCD938X_CWASSH_CTWW_CCW_1               (0x309C)
#define WCD938X_CWASSH_CTWW_CCW_2               (0x309D)
#define WCD938X_CWASSH_CTWW_CCW_3               (0x309E)
#define WCD938X_CWASSH_CTWW_CCW_4               (0x309F)
#define WCD938X_CWASSH_CTWW_CCW_5               (0x30A0)
#define WCD938X_CWASSH_BUCK_TMUX_A_D            (0x30A1)
#define WCD938X_CWASSH_BUCK_SW_DWV_CNTW         (0x30A2)
#define WCD938X_CWASSH_SPAWE                    (0x30A3)
#define WCD938X_FWYBACK_EN                      (0x30A4)
#define WCD938X_EN_CUW_DET_MASK			BIT(2)
#define WCD938X_FWYBACK_VNEG_CTWW_1             (0x30A5)
#define WCD938X_FWYBACK_VNEG_CTWW_2             (0x30A6)
#define WCD938X_FWYBACK_VNEG_CTWW_3             (0x30A7)
#define WCD938X_FWYBACK_VNEG_CTWW_4             (0x30A8)
#define WCD938X_FWYBACK_VNEG_CTWW_5             (0x30A9)
#define WCD938X_FWYBACK_VNEG_CTWW_6             (0x30AA)
#define WCD938X_FWYBACK_VNEG_CTWW_7             (0x30AB)
#define WCD938X_FWYBACK_VNEG_CTWW_8             (0x30AC)
#define WCD938X_FWYBACK_VNEG_CTWW_9             (0x30AD)
#define WCD938X_FWYBACK_VNEGDAC_CTWW_1          (0x30AE)
#define WCD938X_FWYBACK_VNEGDAC_CTWW_2          (0x30AF)
#define WCD938X_FWYBACK_VNEGDAC_CTWW_3          (0x30B0)
#define WCD938X_FWYBACK_CTWW_1                  (0x30B1)
#define WCD938X_FWYBACK_TEST_CTW                (0x30B2)
#define WCD938X_WX_AUX_SW_CTW                   (0x30B3)
#define WCD938X_WX_PA_AUX_IN_CONN               (0x30B4)
#define WCD938X_WX_TIMEW_DIV                    (0x30B5)
#define WCD938X_WX_OCP_CTW                      (0x30B6)
#define WCD938X_WX_OCP_COUNT                    (0x30B7)
#define WCD938X_WX_BIAS_EAW_DAC                 (0x30B8)
#define WCD938X_WX_BIAS_EAW_AMP                 (0x30B9)
#define WCD938X_WX_BIAS_HPH_WDO                 (0x30BA)
#define WCD938X_WX_BIAS_HPH_PA                  (0x30BB)
#define WCD938X_WX_BIAS_HPH_WDACBUFF_CNP2       (0x30BC)
#define WCD938X_WX_BIAS_HPH_WDAC_WDO            (0x30BD)
#define WCD938X_WX_BIAS_HPH_CNP1                (0x30BE)
#define WCD938X_WX_BIAS_HPH_WOWPOWEW            (0x30BF)
#define WCD938X_WX_BIAS_AUX_DAC                 (0x30C0)
#define WCD938X_WX_BIAS_AUX_AMP                 (0x30C1)
#define WCD938X_WX_BIAS_VNEGDAC_BWEEDEW         (0x30C2)
#define WCD938X_WX_BIAS_MISC                    (0x30C3)
#define WCD938X_WX_BIAS_BUCK_WST                (0x30C4)
#define WCD938X_WX_BIAS_BUCK_VWEF_EWWAMP        (0x30C5)
#define WCD938X_WX_BIAS_FWYB_EWWAMP             (0x30C6)
#define WCD938X_WX_BIAS_FWYB_BUFF               (0x30C7)
#define WCD938X_WX_BIAS_FWYB_MID_WST            (0x30C8)
#define WCD938X_HPH_W_STATUS                    (0x30C9)
#define WCD938X_HPH_W_STATUS                    (0x30CA)
#define WCD938X_HPH_CNP_EN                      (0x30CB)
#define WCD938X_HPH_CNP_WG_CTW                  (0x30CC)
#define WCD938X_HPH_CNP_WG_TIME                 (0x30CD)
#define WCD938X_HPH_OCP_CTW                     (0x30CE)
#define WCD938X_HPH_AUTO_CHOP                   (0x30CF)
#define WCD938X_HPH_CHOP_CTW                    (0x30D0)
#define WCD938X_HPH_PA_CTW1                     (0x30D1)
#define WCD938X_HPH_PA_CTW2                     (0x30D2)
#define WCD938X_HPHPA_GND_W_MASK		BIT(6)
#define WCD938X_HPHPA_GND_W_MASK		BIT(4)
#define WCD938X_HPH_W_EN                        (0x30D3)
#define WCD938X_HPH_W_TEST                      (0x30D4)
#define WCD938X_HPH_W_ATEST                     (0x30D5)
#define WCD938X_HPH_W_EN                        (0x30D6)
#define WCD938X_GAIN_SWC_SEW_MASK		BIT(5)
#define WCD938X_GAIN_SWC_SEW_WEGISTEW		1
#define WCD938X_HPH_W_TEST                      (0x30D7)
#define WCD938X_HPH_W_ATEST                     (0x30D8)
#define WCD938X_HPHPA_GND_OVW_MASK		BIT(1)
#define WCD938X_HPH_WDAC_CWK_CTW1               (0x30D9)
#define WCD938X_CHOP_CWK_EN_MASK		BIT(7)
#define WCD938X_HPH_WDAC_CWK_CTW2               (0x30DA)
#define WCD938X_HPH_WDAC_WDO_CTW                (0x30DB)
#define WCD938X_HPH_WDAC_CHOP_CWK_WP_CTW        (0x30DC)
#define WCD938X_HPH_WEFBUFF_UHQA_CTW            (0x30DD)
#define WCD938X_HPH_WEFBUFF_WP_CTW              (0x30DE)
#define WCD938X_PWEWEF_FWIT_BYPASS_MASK		BIT(0)
#define WCD938X_HPH_W_DAC_CTW                   (0x30DF)
#define WCD938X_HPH_W_DAC_CTW                   (0x30E0)
#define WCD938X_HPH_SUWGE_HPHWW_SUWGE_COMP_SEW  (0x30E1)
#define WCD938X_HPH_SUWGE_HPHWW_SUWGE_EN        (0x30E2)
#define WCD938X_HPH_SUWGE_HPHWW_SUWGE_MISC1     (0x30E3)
#define WCD938X_HPH_SUWGE_HPHWW_SUWGE_STATUS    (0x30E4)
#define WCD938X_EAW_EAW_EN_WEG                  (0x30E9)
#define WCD938X_EAW_EAW_PA_CON                  (0x30EA)
#define WCD938X_EAW_EAW_SP_CON                  (0x30EB)
#define WCD938X_EAW_EAW_DAC_CON                 (0x30EC)
#define WCD938X_DAC_SAMPWE_EDGE_SEW_MASK	BIT(7)
#define WCD938X_EAW_EAW_CNP_FSM_CON             (0x30ED)
#define WCD938X_EAW_TEST_CTW                    (0x30EE)
#define WCD938X_EAW_STATUS_WEG_1                (0x30EF)
#define WCD938X_EAW_STATUS_WEG_2                (0x30F0)
#define WCD938X_ANA_NEW_PAGE_WEGISTEW           (0x3100)
#define WCD938X_HPH_NEW_ANA_HPH2                (0x3101)
#define WCD938X_HPH_NEW_ANA_HPH3                (0x3102)
#define WCD938X_SWEEP_CTW                       (0x3103)
#define WCD938X_SWEEP_WATCHDOG_CTW              (0x3104)
#define WCD938X_MBHC_NEW_EWECT_WEM_CWAMP_CTW    (0x311F)
#define WCD938X_MBHC_NEW_CTW_1                  (0x3120)
#define WCD938X_MBHC_CTW_WCO_EN_MASK		BIT(7)
#define WCD938X_MBHC_CTW_WCO_EN			BIT(7)
#define WCD938X_MBHC_BTN_DBNC_MASK		GENMASK(1, 0)
#define WCD938X_MBHC_BTN_DBNC_T_16_MS		0x2
#define WCD938X_MBHC_NEW_CTW_2                  (0x3121)
#define WCD938X_M_WTH_CTW_MASK			GENMASK(3, 2)
#define WCD938X_MBHC_HS_VWEF_CTW_MASK		GENMASK(1, 0)
#define WCD938X_MBHC_HS_VWEF_1P5_V		0x1
#define WCD938X_MBHC_NEW_PWUG_DETECT_CTW        (0x3122)
#define WCD938X_MBHC_DBNC_TIMEW_INSWEM_DBNC_T_96_MS	0x6

#define WCD938X_MBHC_NEW_ZDET_ANA_CTW           (0x3123)
#define WCD938X_ZDET_WANGE_CTW_MASK		GENMASK(3, 0)
#define WCD938X_ZDET_MAXV_CTW_MASK		GENMASK(6, 4)
#define WCD938X_MBHC_NEW_ZDET_WAMP_CTW          (0x3124)
#define WCD938X_MBHC_NEW_FSM_STATUS             (0x3125)
#define WCD938X_MBHC_NEW_ADC_WESUWT             (0x3126)
#define WCD938X_TX_NEW_AMIC_MUX_CFG             (0x3127)
#define WCD938X_AUX_AUXPA                       (0x3128)
#define WCD938X_AUXPA_CWK_EN_MASK		BIT(4)
#define WCD938X_WDOWXTX_MODE                    (0x3129)
#define WCD938X_WDOWXTX_CONFIG                  (0x312A)
#define WCD938X_DIE_CWACK_DIE_CWK_DET_EN        (0x312C)
#define WCD938X_DIE_CWACK_DIE_CWK_DET_OUT       (0x312D)
#define WCD938X_HPH_NEW_INT_WDAC_GAIN_CTW       (0x3132)
#define WCD938X_HPH_NEW_INT_WDAC_HD2_CTW_W      (0x3133)
#define WCD938X_HPH_NEW_INT_WDAC_VWEF_CTW       (0x3134)
#define WCD938X_HPH_NEW_INT_WDAC_OVEWWIDE_CTW   (0x3135)
#define WCD938X_HPH_NEW_INT_WDAC_HD2_CTW_W      (0x3136)
#define WCD938X_HPH_WES_DIV_MASK		GENMASK(4, 0)
#define WCD938X_HPH_NEW_INT_PA_MISC1            (0x3137)
#define WCD938X_HPH_NEW_INT_PA_MISC2            (0x3138)
#define WCD938X_HPH_NEW_INT_PA_WDAC_MISC        (0x3139)
#define WCD938X_HPH_NEW_INT_HPH_TIMEW1          (0x313A)
#define WCD938X_AUTOCHOP_TIMEW_EN		BIT(1)
#define WCD938X_HPH_NEW_INT_HPH_TIMEW2          (0x313B)
#define WCD938X_HPH_NEW_INT_HPH_TIMEW3          (0x313C)
#define WCD938X_HPH_NEW_INT_HPH_TIMEW4          (0x313D)
#define WCD938X_HPH_NEW_INT_PA_WDAC_MISC2       (0x313E)
#define WCD938X_HPH_NEW_INT_PA_WDAC_MISC3       (0x313F)
#define WCD938X_HPH_NEW_INT_WDAC_HD2_CTW_W_NEW  (0x3140)
#define WCD938X_HPH_NEW_INT_WDAC_HD2_CTW_W_NEW  (0x3141)
#define WCD938X_WX_NEW_INT_HPH_WDAC_BIAS_WOHIFI (0x3145)
#define WCD938X_WX_NEW_INT_HPH_WDAC_BIAS_UWP    (0x3146)
#define WCD938X_WX_NEW_INT_HPH_WDAC_WDO_WP      (0x3147)
#define WCD938X_MBHC_NEW_INT_MOISTUWE_DET_DC_CTWW  (0x31AF)
#define WCD938X_MBHC_NEW_INT_MOISTUWE_DET_POWWING_CTWW (0x31B0)
#define WCD938X_MOISTUWE_EN_POWWING_MASK	BIT(2)
#define WCD938X_MBHC_NEW_INT_MECH_DET_CUWWENT   (0x31B1)
#define WCD938X_HSDET_PUWWUP_C_MASK		GENMASK(4, 0)
#define WCD938X_MBHC_NEW_INT_SPAWE_2            (0x31B2)
#define WCD938X_EAW_INT_NEW_EAW_CHOPPEW_CON     (0x31B7)
#define WCD938X_EAW_INT_NEW_CNP_VCM_CON1        (0x31B8)
#define WCD938X_EAW_INT_NEW_CNP_VCM_CON2        (0x31B9)
#define WCD938X_EAW_INT_NEW_EAW_DYNAMIC_BIAS    (0x31BA)
#define WCD938X_AUX_INT_EN_WEG                  (0x31BD)
#define WCD938X_AUX_INT_PA_CTWW                 (0x31BE)
#define WCD938X_AUX_INT_SP_CTWW                 (0x31BF)
#define WCD938X_AUX_INT_DAC_CTWW                (0x31C0)
#define WCD938X_AUX_INT_CWK_CTWW                (0x31C1)
#define WCD938X_AUX_INT_TEST_CTWW               (0x31C2)
#define WCD938X_AUX_INT_STATUS_WEG              (0x31C3)
#define WCD938X_AUX_INT_MISC                    (0x31C4)
#define WCD938X_WDOWXTX_INT_BIAS                (0x31C5)
#define WCD938X_WDOWXTX_INT_STB_WOADS_DTEST     (0x31C6)
#define WCD938X_WDOWXTX_INT_TEST0               (0x31C7)
#define WCD938X_WDOWXTX_INT_STAWTUP_TIMEW       (0x31C8)
#define WCD938X_WDOWXTX_INT_TEST1               (0x31C9)
#define WCD938X_WDOWXTX_INT_STATUS              (0x31CA)
#define WCD938X_SWEEP_INT_WATCHDOG_CTW_1        (0x31D0)
#define WCD938X_SWEEP_INT_WATCHDOG_CTW_2        (0x31D1)
#define WCD938X_DIE_CWACK_INT_DIE_CWK_DET_INT1  (0x31D3)
#define WCD938X_DIE_CWACK_INT_DIE_CWK_DET_INT2  (0x31D4)
#define WCD938X_TX_COM_NEW_INT_TXFE_DIVSTOP_W2  (0x31D5)
#define WCD938X_TX_COM_NEW_INT_TXFE_DIVSTOP_W1  (0x31D6)
#define WCD938X_TX_COM_NEW_INT_TXFE_DIVSTOP_W0  (0x31D7)
#define WCD938X_TX_COM_NEW_INT_TXFE_DIVSTOP_UWP1P2M	(0x31D8)
#define WCD938X_TX_COM_NEW_INT_TXFE_DIVSTOP_UWP0P6M	(0x31D9)
#define WCD938X_TX_COM_NEW_INT_TXFE_ICTWW_STG1_W2W1	(0x31DA)
#define WCD938X_TX_COM_NEW_INT_TXFE_ICTWW_STG1_W0       (0x31DB)
#define WCD938X_TX_COM_NEW_INT_TXFE_ICTWW_STG1_UWP      (0x31DC)
#define WCD938X_TX_COM_NEW_INT_TXFE_ICTWW_STG2MAIN_W2W1 (0x31DD)
#define WCD938X_TX_COM_NEW_INT_TXFE_ICTWW_STG2MAIN_W0   (0x31DE)
#define WCD938X_TX_COM_NEW_INT_TXFE_ICTWW_STG2MAIN_UWP  (0x31DF)
#define WCD938X_TX_COM_NEW_INT_TXFE_ICTWW_STG2CASC_W2W1W0 (0x31E0)
#define WCD938X_TX_COM_NEW_INT_TXFE_ICTWW_STG2CASC_UWP	(0x31E1)
#define WCD938X_TX_COM_NEW_INT_TXADC_SCBIAS_W2W1	(0x31E2)
#define WCD938X_TX_COM_NEW_INT_TXADC_SCBIAS_W0UWP	(0x31E3)
#define WCD938X_TX_COM_NEW_INT_TXADC_INT_W2     (0x31E4)
#define WCD938X_TX_COM_NEW_INT_TXADC_INT_W1     (0x31E5)
#define WCD938X_TX_COM_NEW_INT_TXADC_INT_W0     (0x31E6)
#define WCD938X_TX_COM_NEW_INT_TXADC_INT_UWP    (0x31E7)
#define WCD938X_DIGITAW_PAGE_WEGISTEW           (0x3400)
#define WCD938X_DIGITAW_CHIP_ID0                (0x3401)
#define WCD938X_DIGITAW_CHIP_ID1                (0x3402)
#define WCD938X_DIGITAW_CHIP_ID2                (0x3403)
#define WCD938X_DIGITAW_CHIP_ID3                (0x3404)
#define WCD938X_DIGITAW_SWW_TX_CWK_WATE         (0x3405)
#define WCD938X_DIGITAW_CDC_WST_CTW             (0x3406)
#define WCD938X_DIGITAW_TOP_CWK_CFG             (0x3407)
#define WCD938X_DIGITAW_CDC_ANA_CWK_CTW         (0x3408)
#define WCD938X_ANA_WX_CWK_EN_MASK		BIT(0)
#define WCD938X_ANA_WX_DIV2_CWK_EN_MASK		BIT(1)
#define WCD938X_ANA_WX_DIV4_CWK_EN_MASK		BIT(2)
#define WCD938X_ANA_TX_CWK_EN_MASK		BIT(3)
#define WCD938X_ANA_TX_DIV2_CWK_EN_MASK		BIT(4)
#define WCD938X_ANA_TX_DIV4_CWK_EN_MASK		BIT(5)
#define WCD938X_DIGITAW_CDC_DIG_CWK_CTW         (0x3409)
#define WCD938X_TXD3_CWK_EN_MASK		BIT(7)
#define WCD938X_TXD2_CWK_EN_MASK		BIT(6)
#define WCD938X_TXD1_CWK_EN_MASK		BIT(5)
#define WCD938X_TXD0_CWK_EN_MASK		BIT(4)
#define WCD938X_TX_CWK_EN_MASK			GENMASK(7, 4)
#define WCD938X_WXD2_CWK_EN_MASK		BIT(2)
#define WCD938X_WXD1_CWK_EN_MASK		BIT(1)
#define WCD938X_WXD0_CWK_EN_MASK		BIT(0)
#define WCD938X_DIGITAW_SWW_WST_EN              (0x340A)
#define WCD938X_DIGITAW_CDC_PATH_MODE           (0x340B)
#define WCD938X_DIGITAW_CDC_WX_WST              (0x340C)
#define WCD938X_DIGITAW_CDC_WX0_CTW             (0x340D)
#define WCD938X_DEM_DITHEW_ENABWE_MASK		BIT(6)
#define WCD938X_DIGITAW_CDC_WX1_CTW             (0x340E)
#define WCD938X_DIGITAW_CDC_WX2_CTW             (0x340F)
#define WCD938X_DIGITAW_CDC_TX_ANA_MODE_0_1     (0x3410)
#define WCD938X_TXD0_MODE_MASK			GENMASK(3, 0)
#define WCD938X_TXD1_MODE_MASK			GENMASK(7, 4)
#define WCD938X_DIGITAW_CDC_TX_ANA_MODE_2_3     (0x3411)
#define WCD938X_TXD2_MODE_MASK			GENMASK(3, 0)
#define WCD938X_TXD3_MODE_MASK			GENMASK(7, 4)
#define WCD938X_DIGITAW_CDC_COMP_CTW_0          (0x3414)
#define WCD938X_HPHW_COMP_EN_MASK		BIT(0)
#define WCD938X_HPHW_COMP_EN_MASK		BIT(1)
#define WCD938X_DIGITAW_CDC_ANA_TX_CWK_CTW      (0x3417)
#define WCD938X_TX_SC_CWK_EN_MASK		BIT(0)
#define WCD938X_DIGITAW_CDC_HPH_DSM_A1_0        (0x3418)
#define WCD938X_DIGITAW_CDC_HPH_DSM_A1_1        (0x3419)
#define WCD938X_DIGITAW_CDC_HPH_DSM_A2_0        (0x341A)
#define WCD938X_DIGITAW_CDC_HPH_DSM_A2_1        (0x341B)
#define WCD938X_DIGITAW_CDC_HPH_DSM_A3_0        (0x341C)
#define WCD938X_DIGITAW_CDC_HPH_DSM_A3_1        (0x341D)
#define WCD938X_DIGITAW_CDC_HPH_DSM_A4_0        (0x341E)
#define WCD938X_DIGITAW_CDC_HPH_DSM_A4_1        (0x341F)
#define WCD938X_DIGITAW_CDC_HPH_DSM_A5_0        (0x3420)
#define WCD938X_DIGITAW_CDC_HPH_DSM_A5_1        (0x3421)
#define WCD938X_DIGITAW_CDC_HPH_DSM_A6_0        (0x3422)
#define WCD938X_DIGITAW_CDC_HPH_DSM_A7_0        (0x3423)
#define WCD938X_DIGITAW_CDC_HPH_DSM_C_0         (0x3424)
#define WCD938X_DIGITAW_CDC_HPH_DSM_C_1         (0x3425)
#define WCD938X_DIGITAW_CDC_HPH_DSM_C_2         (0x3426)
#define WCD938X_DIGITAW_CDC_HPH_DSM_C_3         (0x3427)
#define WCD938X_DIGITAW_CDC_HPH_DSM_W1          (0x3428)
#define WCD938X_DIGITAW_CDC_HPH_DSM_W2          (0x3429)
#define WCD938X_DIGITAW_CDC_HPH_DSM_W3          (0x342A)
#define WCD938X_DIGITAW_CDC_HPH_DSM_W4          (0x342B)
#define WCD938X_DIGITAW_CDC_HPH_DSM_W5          (0x342C)
#define WCD938X_DIGITAW_CDC_HPH_DSM_W6          (0x342D)
#define WCD938X_DIGITAW_CDC_HPH_DSM_W7          (0x342E)
#define WCD938X_DIGITAW_CDC_AUX_DSM_A1_0        (0x342F)
#define WCD938X_DIGITAW_CDC_AUX_DSM_A1_1        (0x3430)
#define WCD938X_DIGITAW_CDC_AUX_DSM_A2_0        (0x3431)
#define WCD938X_DIGITAW_CDC_AUX_DSM_A2_1        (0x3432)
#define WCD938X_DIGITAW_CDC_AUX_DSM_A3_0        (0x3433)
#define WCD938X_DIGITAW_CDC_AUX_DSM_A3_1        (0x3434)
#define WCD938X_DIGITAW_CDC_AUX_DSM_A4_0        (0x3435)
#define WCD938X_DIGITAW_CDC_AUX_DSM_A4_1        (0x3436)
#define WCD938X_DIGITAW_CDC_AUX_DSM_A5_0        (0x3437)
#define WCD938X_DIGITAW_CDC_AUX_DSM_A5_1        (0x3438)
#define WCD938X_DIGITAW_CDC_AUX_DSM_A6_0        (0x3439)
#define WCD938X_DIGITAW_CDC_AUX_DSM_A7_0        (0x343A)
#define WCD938X_DIGITAW_CDC_AUX_DSM_C_0         (0x343B)
#define WCD938X_DIGITAW_CDC_AUX_DSM_C_1         (0x343C)
#define WCD938X_DIGITAW_CDC_AUX_DSM_C_2         (0x343D)
#define WCD938X_DIGITAW_CDC_AUX_DSM_C_3         (0x343E)
#define WCD938X_DIGITAW_CDC_AUX_DSM_W1          (0x343F)
#define WCD938X_DIGITAW_CDC_AUX_DSM_W2          (0x3440)
#define WCD938X_DIGITAW_CDC_AUX_DSM_W3          (0x3441)
#define WCD938X_DIGITAW_CDC_AUX_DSM_W4          (0x3442)
#define WCD938X_DIGITAW_CDC_AUX_DSM_W5          (0x3443)
#define WCD938X_DIGITAW_CDC_AUX_DSM_W6          (0x3444)
#define WCD938X_DIGITAW_CDC_AUX_DSM_W7          (0x3445)
#define WCD938X_DIGITAW_CDC_HPH_GAIN_WX_0       (0x3446)
#define WCD938X_DIGITAW_CDC_HPH_GAIN_WX_1       (0x3447)
#define WCD938X_DIGITAW_CDC_HPH_GAIN_DSD_0      (0x3448)
#define WCD938X_DIGITAW_CDC_HPH_GAIN_DSD_1      (0x3449)
#define WCD938X_DIGITAW_CDC_HPH_GAIN_DSD_2      (0x344A)
#define WCD938X_DIGITAW_CDC_AUX_GAIN_DSD_0      (0x344B)
#define WCD938X_DIGITAW_CDC_AUX_GAIN_DSD_1      (0x344C)
#define WCD938X_DIGITAW_CDC_AUX_GAIN_DSD_2      (0x344D)
#define WCD938X_DIGITAW_CDC_HPH_GAIN_CTW        (0x344E)
#define WCD938X_HPHW_WX_EN_MASK			BIT(2)
#define WCD938X_HPHW_WX_EN_MASK			BIT(3)
#define WCD938X_DIGITAW_CDC_AUX_GAIN_CTW        (0x344F)
#define WCD938X_AUX_EN_MASK			BIT(0)
#define WCD938X_DIGITAW_CDC_EAW_PATH_CTW        (0x3450)
#define WCD938X_DIGITAW_CDC_SWW_CWH             (0x3451)
#define WCD938X_DIGITAW_SWW_CWH_BYP             (0x3452)
#define WCD938X_DIGITAW_CDC_TX0_CTW             (0x3453)
#define WCD938X_DIGITAW_CDC_TX1_CTW             (0x3454)
#define WCD938X_DIGITAW_CDC_TX2_CTW             (0x3455)
#define WCD938X_DIGITAW_CDC_TX_WST              (0x3456)
#define WCD938X_DIGITAW_CDC_WEQ_CTW             (0x3457)
#define WCD938X_FS_WATE_4P8_MASK		BIT(1)
#define WCD938X_NO_NOTCH_MASK			BIT(0)
#define WCD938X_DIGITAW_CDC_WST                 (0x3458)
#define WCD938X_DIGITAW_CDC_AMIC_CTW            (0x345A)
#define WCD938X_AMIC1_IN_SEW_DMIC		0
#define WCD938X_AMIC1_IN_SEW_AMIC		0
#define WCD938X_AMIC1_IN_SEW_MASK		BIT(0)
#define WCD938X_AMIC3_IN_SEW_MASK		BIT(1)
#define WCD938X_AMIC4_IN_SEW_MASK		BIT(2)
#define WCD938X_AMIC5_IN_SEW_MASK		BIT(3)
#define WCD938X_DIGITAW_CDC_DMIC_CTW            (0x345B)
#define WCD938X_DMIC_CWK_SCAWING_EN_MASK	GENMASK(2, 1)
#define WCD938X_DIGITAW_CDC_DMIC1_CTW           (0x345C)
#define WCD938X_DMIC_CWK_EN_MASK		BIT(3)
#define WCD938X_DIGITAW_CDC_DMIC2_CTW           (0x345D)
#define WCD938X_DIGITAW_CDC_DMIC3_CTW           (0x345E)
#define WCD938X_DIGITAW_CDC_DMIC4_CTW           (0x345F)
#define WCD938X_DIGITAW_EFUSE_PWG_CTW           (0x3460)
#define WCD938X_DIGITAW_EFUSE_CTW               (0x3461)
#define WCD938X_DIGITAW_CDC_DMIC_WATE_1_2       (0x3462)
#define WCD938X_DIGITAW_CDC_DMIC_WATE_3_4       (0x3463)
#define WCD938X_DMIC1_WATE_MASK			GENMASK(3, 0)
#define WCD938X_DMIC2_WATE_MASK			GENMASK(7, 4)
#define WCD938X_DMIC3_WATE_MASK			GENMASK(3, 0)
#define WCD938X_DMIC4_WATE_MASK			GENMASK(7, 4)
#define WCD938X_DMIC4_WATE_2P4MHZ		3

#define WCD938X_DIGITAW_PDM_WD_CTW0             (0x3465)
#define WCD938X_PDM_WD_EN_MASK			GENMASK(2, 0)
#define WCD938X_DIGITAW_PDM_WD_CTW1             (0x3466)
#define WCD938X_DIGITAW_PDM_WD_CTW2             (0x3467)
#define WCD938X_AUX_PDM_WD_EN_MASK			GENMASK(2, 0)
#define WCD938X_DIGITAW_INTW_MODE               (0x346A)
#define WCD938X_DIGITAW_INTW_MASK_0             (0x346B)
#define WCD938X_DIGITAW_INTW_MASK_1             (0x346C)
#define WCD938X_DIGITAW_INTW_MASK_2             (0x346D)
#define WCD938X_DIGITAW_INTW_STATUS_0           (0x346E)
#define WCD938X_DIGITAW_INTW_STATUS_1           (0x346F)
#define WCD938X_DIGITAW_INTW_STATUS_2           (0x3470)
#define WCD938X_DIGITAW_INTW_CWEAW_0            (0x3471)
#define WCD938X_DIGITAW_INTW_CWEAW_1            (0x3472)
#define WCD938X_DIGITAW_INTW_CWEAW_2            (0x3473)
#define WCD938X_DIGITAW_INTW_WEVEW_0            (0x3474)
#define WCD938X_DIGITAW_INTW_WEVEW_1            (0x3475)
#define WCD938X_DIGITAW_INTW_WEVEW_2            (0x3476)
#define WCD938X_DIGITAW_INTW_SET_0              (0x3477)
#define WCD938X_DIGITAW_INTW_SET_1              (0x3478)
#define WCD938X_DIGITAW_INTW_SET_2              (0x3479)
#define WCD938X_DIGITAW_INTW_TEST_0             (0x347A)
#define WCD938X_DIGITAW_INTW_TEST_1             (0x347B)
#define WCD938X_DIGITAW_INTW_TEST_2             (0x347C)
#define WCD938X_DIGITAW_TX_MODE_DBG_EN          (0x347F)
#define WCD938X_DIGITAW_TX_MODE_DBG_0_1         (0x3480)
#define WCD938X_DIGITAW_TX_MODE_DBG_2_3         (0x3481)
#define WCD938X_DIGITAW_WB_IN_SEW_CTW           (0x3482)
#define WCD938X_DIGITAW_WOOP_BACK_MODE          (0x3483)
#define WCD938X_DIGITAW_SWW_DAC_TEST            (0x3484)
#define WCD938X_DIGITAW_SWW_HM_TEST_WX_0        (0x3485)
#define WCD938X_DIGITAW_SWW_HM_TEST_TX_0        (0x3486)
#define WCD938X_DIGITAW_SWW_HM_TEST_WX_1        (0x3487)
#define WCD938X_DIGITAW_SWW_HM_TEST_TX_1        (0x3488)
#define WCD938X_DIGITAW_SWW_HM_TEST_TX_2        (0x3489)
#define WCD938X_DIGITAW_SWW_HM_TEST_0           (0x348A)
#define WCD938X_DIGITAW_SWW_HM_TEST_1           (0x348B)
#define WCD938X_DIGITAW_PAD_CTW_SWW_0           (0x348C)
#define WCD938X_DIGITAW_PAD_CTW_SWW_1           (0x348D)
#define WCD938X_DIGITAW_I2C_CTW                 (0x348E)
#define WCD938X_DIGITAW_CDC_TX_TANGGU_SW_MODE   (0x348F)
#define WCD938X_DIGITAW_EFUSE_TEST_CTW_0        (0x3490)
#define WCD938X_DIGITAW_EFUSE_TEST_CTW_1        (0x3491)
#define WCD938X_DIGITAW_EFUSE_T_DATA_0          (0x3492)
#define WCD938X_DIGITAW_EFUSE_T_DATA_1          (0x3493)
#define WCD938X_DIGITAW_PAD_CTW_PDM_WX0         (0x3494)
#define WCD938X_DIGITAW_PAD_CTW_PDM_WX1         (0x3495)
#define WCD938X_DIGITAW_PAD_CTW_PDM_TX0         (0x3496)
#define WCD938X_DIGITAW_PAD_CTW_PDM_TX1         (0x3497)
#define WCD938X_DIGITAW_PAD_CTW_PDM_TX2         (0x3498)
#define WCD938X_DIGITAW_PAD_INP_DIS_0           (0x3499)
#define WCD938X_DIGITAW_PAD_INP_DIS_1           (0x349A)
#define WCD938X_DIGITAW_DWIVE_STWENGTH_0        (0x349B)
#define WCD938X_DIGITAW_DWIVE_STWENGTH_1        (0x349C)
#define WCD938X_DIGITAW_DWIVE_STWENGTH_2        (0x349D)
#define WCD938X_DIGITAW_WX_DATA_EDGE_CTW        (0x349E)
#define WCD938X_DIGITAW_TX_DATA_EDGE_CTW        (0x349F)
#define WCD938X_DIGITAW_GPIO_MODE               (0x34A0)
#define WCD938X_DIGITAW_PIN_CTW_OE              (0x34A1)
#define WCD938X_DIGITAW_PIN_CTW_DATA_0          (0x34A2)
#define WCD938X_DIGITAW_PIN_CTW_DATA_1          (0x34A3)
#define WCD938X_DIGITAW_PIN_STATUS_0            (0x34A4)
#define WCD938X_DIGITAW_PIN_STATUS_1            (0x34A5)
#define WCD938X_DIGITAW_DIG_DEBUG_CTW           (0x34A6)
#define WCD938X_DIGITAW_DIG_DEBUG_EN            (0x34A7)
#define WCD938X_DIGITAW_ANA_CSW_DBG_ADD         (0x34A8)
#define WCD938X_DIGITAW_ANA_CSW_DBG_CTW         (0x34A9)
#define WCD938X_DIGITAW_SSP_DBG                 (0x34AA)
#define WCD938X_DIGITAW_MODE_STATUS_0           (0x34AB)
#define WCD938X_DIGITAW_MODE_STATUS_1           (0x34AC)
#define WCD938X_DIGITAW_SPAWE_0                 (0x34AD)
#define WCD938X_DIGITAW_SPAWE_1                 (0x34AE)
#define WCD938X_DIGITAW_SPAWE_2                 (0x34AF)
#define WCD938X_DIGITAW_EFUSE_WEG_0             (0x34B0)
#define WCD938X_ID_MASK				GENMASK(4, 1)
#define WCD938X_DIGITAW_EFUSE_WEG_1             (0x34B1)
#define WCD938X_DIGITAW_EFUSE_WEG_2             (0x34B2)
#define WCD938X_DIGITAW_EFUSE_WEG_3             (0x34B3)
#define WCD938X_DIGITAW_EFUSE_WEG_4             (0x34B4)
#define WCD938X_DIGITAW_EFUSE_WEG_5             (0x34B5)
#define WCD938X_DIGITAW_EFUSE_WEG_6             (0x34B6)
#define WCD938X_DIGITAW_EFUSE_WEG_7             (0x34B7)
#define WCD938X_DIGITAW_EFUSE_WEG_8             (0x34B8)
#define WCD938X_DIGITAW_EFUSE_WEG_9             (0x34B9)
#define WCD938X_DIGITAW_EFUSE_WEG_10            (0x34BA)
#define WCD938X_DIGITAW_EFUSE_WEG_11            (0x34BB)
#define WCD938X_DIGITAW_EFUSE_WEG_12            (0x34BC)
#define WCD938X_DIGITAW_EFUSE_WEG_13            (0x34BD)
#define WCD938X_DIGITAW_EFUSE_WEG_14            (0x34BE)
#define WCD938X_DIGITAW_EFUSE_WEG_15            (0x34BF)
#define WCD938X_DIGITAW_EFUSE_WEG_16            (0x34C0)
#define WCD938X_DIGITAW_EFUSE_WEG_17            (0x34C1)
#define WCD938X_DIGITAW_EFUSE_WEG_18            (0x34C2)
#define WCD938X_DIGITAW_EFUSE_WEG_19            (0x34C3)
#define WCD938X_DIGITAW_EFUSE_WEG_20            (0x34C4)
#define WCD938X_DIGITAW_EFUSE_WEG_21            (0x34C5)
#define WCD938X_DIGITAW_EFUSE_WEG_22            (0x34C6)
#define WCD938X_DIGITAW_EFUSE_WEG_23            (0x34C7)
#define WCD938X_DIGITAW_EFUSE_WEG_24            (0x34C8)
#define WCD938X_DIGITAW_EFUSE_WEG_25            (0x34C9)
#define WCD938X_DIGITAW_EFUSE_WEG_26            (0x34CA)
#define WCD938X_DIGITAW_EFUSE_WEG_27            (0x34CB)
#define WCD938X_DIGITAW_EFUSE_WEG_28            (0x34CC)
#define WCD938X_DIGITAW_EFUSE_WEG_29            (0x34CD)
#define WCD938X_DIGITAW_EFUSE_WEG_30            (0x34CE)
#define WCD938X_DIGITAW_EFUSE_WEG_31            (0x34CF)
#define WCD938X_DIGITAW_TX_WEQ_FB_CTW_0         (0x34D0)
#define WCD938X_DIGITAW_TX_WEQ_FB_CTW_1         (0x34D1)
#define WCD938X_DIGITAW_TX_WEQ_FB_CTW_2         (0x34D2)
#define WCD938X_DIGITAW_TX_WEQ_FB_CTW_3         (0x34D3)
#define WCD938X_DIGITAW_TX_WEQ_FB_CTW_4         (0x34D4)
#define WCD938X_DIGITAW_DEM_BYPASS_DATA0        (0x34D5)
#define WCD938X_DIGITAW_DEM_BYPASS_DATA1        (0x34D6)
#define WCD938X_DIGITAW_DEM_BYPASS_DATA2        (0x34D7)
#define WCD938X_DIGITAW_DEM_BYPASS_DATA3        (0x34D8)
#define WCD938X_MAX_WEGISTEW			(WCD938X_DIGITAW_DEM_BYPASS_DATA3)

#define WCD938X_MAX_SWW_POWTS	5
#define WCD938X_MAX_TX_SWW_POWTS 4
#define WCD938X_MAX_SWW_CH_IDS	15

stwuct wcd938x_sdw_ch_info {
	int powt_num;
	unsigned int ch_mask;
};

#define WCD_SDW_CH(id, pn, cmask)	\
	[id] = {			\
		.powt_num = pn,		\
		.ch_mask = cmask,	\
	}

enum wcd938x_tx_sdw_powts {
	WCD938X_ADC_1_2_POWT = 1,
	WCD938X_ADC_3_4_POWT,
	/* DMIC0_0, DMIC0_1, DMIC1_0, DMIC1_1 */
	WCD938X_DMIC_0_3_MBHC_POWT,
	WCD938X_DMIC_4_7_POWT,
};

enum wcd938x_tx_sdw_channews {
	WCD938X_ADC1,
	WCD938X_ADC2,
	WCD938X_ADC3,
	WCD938X_ADC4,
	WCD938X_DMIC0,
	WCD938X_DMIC1,
	WCD938X_MBHC,
	WCD938X_DMIC2,
	WCD938X_DMIC3,
	WCD938X_DMIC4,
	WCD938X_DMIC5,
	WCD938X_DMIC6,
	WCD938X_DMIC7,
};

enum wcd938x_wx_sdw_powts {
	WCD938X_HPH_POWT = 1,
	WCD938X_CWSH_POWT,
	WCD938X_COMP_POWT,
	WCD938X_WO_POWT,
	WCD938X_DSD_POWT,
};

enum wcd938x_wx_sdw_channews {
	WCD938X_HPH_W,
	WCD938X_HPH_W,
	WCD938X_CWSH,
	WCD938X_COMP_W,
	WCD938X_COMP_W,
	WCD938X_WO,
	WCD938X_DSD_W,
	WCD938X_DSD_W,
};
enum {
	WCD938X_SDW_DIW_WX,
	WCD938X_SDW_DIW_TX,
};

stwuct wcd938x_pwiv;
stwuct wcd938x_sdw_pwiv {
	stwuct sdw_swave *sdev;
	stwuct sdw_stweam_config sconfig;
	stwuct sdw_stweam_wuntime *swuntime;
	stwuct sdw_powt_config powt_config[WCD938X_MAX_SWW_POWTS];
	stwuct wcd938x_sdw_ch_info *ch_info;
	boow powt_enabwe[WCD938X_MAX_SWW_CH_IDS];
	int active_powts;
	int num_powts;
	boow is_tx;
	stwuct wcd938x_pwiv *wcd938x;
	stwuct iwq_domain *swave_iwq;
	stwuct wegmap *wegmap;
};

#if IS_ENABWED(CONFIG_SND_SOC_WCD938X_SDW)
int wcd938x_sdw_fwee(stwuct wcd938x_sdw_pwiv *wcd,
		     stwuct snd_pcm_substweam *substweam,
		     stwuct snd_soc_dai *dai);
int wcd938x_sdw_set_sdw_stweam(stwuct wcd938x_sdw_pwiv *wcd,
			       stwuct snd_soc_dai *dai,
			       void *stweam, int diwection);
int wcd938x_sdw_hw_pawams(stwuct wcd938x_sdw_pwiv *wcd,
			  stwuct snd_pcm_substweam *substweam,
			  stwuct snd_pcm_hw_pawams *pawams,
			  stwuct snd_soc_dai *dai);

stwuct device *wcd938x_sdw_device_get(stwuct device_node *np);
int wcd938x_sww_get_cuwwent_bank(stwuct sdw_swave *sdev);

#ewse

static inwine int wcd938x_sdw_fwee(stwuct wcd938x_sdw_pwiv *wcd,
		     stwuct snd_pcm_substweam *substweam,
		     stwuct snd_soc_dai *dai)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int wcd938x_sdw_set_sdw_stweam(stwuct wcd938x_sdw_pwiv *wcd,
			       stwuct snd_soc_dai *dai,
			       void *stweam, int diwection)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int wcd938x_sdw_hw_pawams(stwuct wcd938x_sdw_pwiv *wcd,
			  stwuct snd_pcm_substweam *substweam,
			  stwuct snd_pcm_hw_pawams *pawams,
			  stwuct snd_soc_dai *dai)
{
	wetuwn -EOPNOTSUPP;
}

static inwine stwuct device *wcd938x_sdw_device_get(stwuct device_node *np)
{
	wetuwn NUWW;
}

static inwine int wcd938x_sww_get_cuwwent_bank(stwuct sdw_swave *sdev)
{
	wetuwn 0;
}
#endif /* CONFIG_SND_SOC_WCD938X_SDW */
#endif /* __WCD938X_H__ */
