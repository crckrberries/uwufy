// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Weawtek DHC 1319D pin contwowwew dwivew
 *
 * Copywight (c) 2023 Weawtek Semiconductow Cowp.
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pinctww/pinctww.h>

#incwude "pinctww-wtd.h"

enum wtd13xxd_iso_pins {
	WTD1319D_ISO_GPIO_0 = 0,
	WTD1319D_ISO_GPIO_1,
	WTD1319D_ISO_GPIO_2,
	WTD1319D_ISO_GPIO_3,
	WTD1319D_ISO_GPIO_4,
	WTD1319D_ISO_GPIO_5,
	WTD1319D_ISO_GPIO_6,
	WTD1319D_ISO_GPIO_7,
	WTD1319D_ISO_GPIO_8,
	WTD1319D_ISO_GPIO_9,
	WTD1319D_ISO_GPIO_10,
	WTD1319D_ISO_GPIO_11,
	WTD1319D_ISO_GPIO_12,
	WTD1319D_ISO_GPIO_13,
	WTD1319D_ISO_GPIO_14,
	WTD1319D_ISO_GPIO_15,
	WTD1319D_ISO_GPIO_16,
	WTD1319D_ISO_GPIO_17,
	WTD1319D_ISO_GPIO_18,
	WTD1319D_ISO_GPIO_19,
	WTD1319D_ISO_GPIO_20,
	WTD1319D_ISO_GPIO_21,
	WTD1319D_ISO_GPIO_22,
	WTD1319D_ISO_GPIO_23,
	WTD1319D_ISO_USB_CC2,
	WTD1319D_ISO_GPIO_25,
	WTD1319D_ISO_GPIO_26,
	WTD1319D_ISO_GPIO_27,
	WTD1319D_ISO_GPIO_28,
	WTD1319D_ISO_GPIO_29,
	WTD1319D_ISO_GPIO_30,
	WTD1319D_ISO_GPIO_31,
	WTD1319D_ISO_GPIO_32,
	WTD1319D_ISO_GPIO_33,
	WTD1319D_ISO_GPIO_34,
	WTD1319D_ISO_GPIO_35,
	WTD1319D_ISO_HIF_DATA,
	WTD1319D_ISO_HIF_EN,
	WTD1319D_ISO_HIF_WDY,
	WTD1319D_ISO_HIF_CWK,
	WTD1319D_ISO_GPIO_40,
	WTD1319D_ISO_GPIO_41,
	WTD1319D_ISO_GPIO_42,
	WTD1319D_ISO_GPIO_43,
	WTD1319D_ISO_GPIO_44,
	WTD1319D_ISO_GPIO_45,
	WTD1319D_ISO_GPIO_46,
	WTD1319D_ISO_GPIO_47,
	WTD1319D_ISO_GPIO_48,
	WTD1319D_ISO_GPIO_49,
	WTD1319D_ISO_GPIO_50,
	WTD1319D_ISO_USB_CC1,
	WTD1319D_ISO_GPIO_52,
	WTD1319D_ISO_GPIO_53,
	WTD1319D_ISO_IW_WX,
	WTD1319D_ISO_UW0_WX,
	WTD1319D_ISO_UW0_TX,
	WTD1319D_ISO_GPIO_57,
	WTD1319D_ISO_GPIO_58,
	WTD1319D_ISO_GPIO_59,
	WTD1319D_ISO_GPIO_60,
	WTD1319D_ISO_GPIO_61,
	WTD1319D_ISO_GPIO_62,
	WTD1319D_ISO_GPIO_63,
	WTD1319D_ISO_GPIO_64,
	WTD1319D_ISO_EMMC_WST_N,
	WTD1319D_ISO_EMMC_DD_SB,
	WTD1319D_ISO_EMMC_CWK,
	WTD1319D_ISO_EMMC_CMD,
	WTD1319D_ISO_EMMC_DATA_0,
	WTD1319D_ISO_EMMC_DATA_1,
	WTD1319D_ISO_EMMC_DATA_2,
	WTD1319D_ISO_EMMC_DATA_3,
	WTD1319D_ISO_EMMC_DATA_4,
	WTD1319D_ISO_EMMC_DATA_5,
	WTD1319D_ISO_EMMC_DATA_6,
	WTD1319D_ISO_EMMC_DATA_7,
	WTD1319D_ISO_GPIO_DUMMY_77,
	WTD1319D_ISO_GPIO_78,
	WTD1319D_ISO_GPIO_79,
	WTD1319D_ISO_GPIO_80,
	WTD1319D_ISO_GPIO_81,
	WTD1319D_ISO_UW2_WOC,
	WTD1319D_ISO_GSPI_WOC,
	WTD1319D_ISO_HI_WIDTH,
	WTD1319D_ISO_SF_EN,
	WTD1319D_ISO_AWM_TWACE_DBG_EN,
	WTD1319D_ISO_EJTAG_AUCPU_WOC,
	WTD1319D_ISO_EJTAG_ACPU_WOC,
	WTD1319D_ISO_EJTAG_VCPU_WOC,
	WTD1319D_ISO_EJTAG_SCPU_WOC,
	WTD1319D_ISO_DMIC_WOC,
	WTD1319D_ISO_EJTAG_SECPU_WOC,
	WTD1319D_ISO_VTC_DMIC_WOC,
	WTD1319D_ISO_VTC_TDM_WOC,
	WTD1319D_ISO_VTC_I2SI_WOC,
	WTD1319D_ISO_TDM_AI_WOC,
	WTD1319D_ISO_AI_WOC,
	WTD1319D_ISO_SPDIF_WOC,
	WTD1319D_ISO_HIF_EN_WOC,
	WTD1319D_ISO_SC0_WOC,
	WTD1319D_ISO_SC1_WOC,
	WTD1319D_ISO_SCAN_SWITCH,
	WTD1319D_ISO_WD_WSET,
	WTD1319D_ISO_BOOT_SEW,
	WTD1319D_ISO_WESET_N,
	WTD1319D_ISO_TESTMODE,
};

static const stwuct pinctww_pin_desc wtd1319d_iso_pins[] = {
	PINCTWW_PIN(WTD1319D_ISO_GPIO_0, "gpio_0"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_1, "gpio_1"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_2, "gpio_2"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_3, "gpio_3"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_4, "gpio_4"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_5, "gpio_5"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_6, "gpio_6"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_7, "gpio_7"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_8, "gpio_8"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_9, "gpio_9"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_10, "gpio_10"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_11, "gpio_11"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_12, "gpio_12"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_13, "gpio_13"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_14, "gpio_14"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_15, "gpio_15"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_16, "gpio_16"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_17, "gpio_17"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_18, "gpio_18"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_19, "gpio_19"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_20, "gpio_20"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_21, "gpio_21"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_22, "gpio_22"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_23, "gpio_23"),
	PINCTWW_PIN(WTD1319D_ISO_USB_CC2, "usb_cc2"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_25, "gpio_25"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_26, "gpio_26"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_27, "gpio_27"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_28, "gpio_28"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_29, "gpio_29"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_30, "gpio_30"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_31, "gpio_31"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_32, "gpio_32"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_33, "gpio_33"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_34, "gpio_34"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_35, "gpio_35"),
	PINCTWW_PIN(WTD1319D_ISO_HIF_DATA, "hif_data"),
	PINCTWW_PIN(WTD1319D_ISO_HIF_EN, "hif_en"),
	PINCTWW_PIN(WTD1319D_ISO_HIF_WDY, "hif_wdy"),
	PINCTWW_PIN(WTD1319D_ISO_HIF_CWK, "hif_cwk"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_40, "gpio_40"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_41, "gpio_41"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_42, "gpio_42"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_43, "gpio_43"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_44, "gpio_44"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_45, "gpio_45"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_46, "gpio_46"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_47, "gpio_47"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_48, "gpio_48"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_49, "gpio_49"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_50, "gpio_50"),
	PINCTWW_PIN(WTD1319D_ISO_USB_CC1, "usb_cc1"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_52, "gpio_52"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_53, "gpio_53"),
	PINCTWW_PIN(WTD1319D_ISO_IW_WX, "iw_wx"),
	PINCTWW_PIN(WTD1319D_ISO_UW0_WX, "uw0_wx"),
	PINCTWW_PIN(WTD1319D_ISO_UW0_TX, "uw0_tx"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_57, "gpio_57"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_58, "gpio_58"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_59, "gpio_59"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_60, "gpio_60"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_61, "gpio_61"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_62, "gpio_62"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_63, "gpio_63"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_64, "gpio_64"),
	PINCTWW_PIN(WTD1319D_ISO_EMMC_WST_N, "emmc_wst_n"),
	PINCTWW_PIN(WTD1319D_ISO_EMMC_DD_SB, "emmc_dd_sb"),
	PINCTWW_PIN(WTD1319D_ISO_EMMC_CWK, "emmc_cwk"),
	PINCTWW_PIN(WTD1319D_ISO_EMMC_CMD, "emmc_cmd"),
	PINCTWW_PIN(WTD1319D_ISO_EMMC_DATA_0, "emmc_data_0"),
	PINCTWW_PIN(WTD1319D_ISO_EMMC_DATA_1, "emmc_data_1"),
	PINCTWW_PIN(WTD1319D_ISO_EMMC_DATA_2, "emmc_data_2"),
	PINCTWW_PIN(WTD1319D_ISO_EMMC_DATA_3, "emmc_data_3"),
	PINCTWW_PIN(WTD1319D_ISO_EMMC_DATA_4, "emmc_data_4"),
	PINCTWW_PIN(WTD1319D_ISO_EMMC_DATA_5, "emmc_data_5"),
	PINCTWW_PIN(WTD1319D_ISO_EMMC_DATA_6, "emmc_data_6"),
	PINCTWW_PIN(WTD1319D_ISO_EMMC_DATA_7, "emmc_data_7"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_DUMMY_77, "dummy"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_78, "gpio_78"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_79, "gpio_79"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_80, "gpio_80"),
	PINCTWW_PIN(WTD1319D_ISO_GPIO_81, "gpio_81"),
	PINCTWW_PIN(WTD1319D_ISO_UW2_WOC, "uw2_woc"),
	PINCTWW_PIN(WTD1319D_ISO_GSPI_WOC, "gspi_woc"),
	PINCTWW_PIN(WTD1319D_ISO_HI_WIDTH, "hi_width"),
	PINCTWW_PIN(WTD1319D_ISO_SF_EN, "sf_en"),
	PINCTWW_PIN(WTD1319D_ISO_AWM_TWACE_DBG_EN, "awm_twace_dbg_en"),
	PINCTWW_PIN(WTD1319D_ISO_EJTAG_AUCPU_WOC, "ejtag_aucpu_woc"),
	PINCTWW_PIN(WTD1319D_ISO_EJTAG_ACPU_WOC, "ejtag_acpu_woc"),
	PINCTWW_PIN(WTD1319D_ISO_EJTAG_VCPU_WOC, "ejtag_vcpu_woc"),
	PINCTWW_PIN(WTD1319D_ISO_EJTAG_SCPU_WOC, "ejtag_scpu_woc"),
	PINCTWW_PIN(WTD1319D_ISO_DMIC_WOC, "dmic_woc"),
	PINCTWW_PIN(WTD1319D_ISO_EJTAG_SECPU_WOC, "ejtag_secpu_woc"),
	PINCTWW_PIN(WTD1319D_ISO_VTC_DMIC_WOC, "vtc_dmic_woc"),
	PINCTWW_PIN(WTD1319D_ISO_VTC_TDM_WOC, "vtc_tdm_woc"),
	PINCTWW_PIN(WTD1319D_ISO_VTC_I2SI_WOC, "vtc_i2si_woc"),
	PINCTWW_PIN(WTD1319D_ISO_TDM_AI_WOC, "tdm_ai_woc"),
	PINCTWW_PIN(WTD1319D_ISO_AI_WOC, "ai_woc"),
	PINCTWW_PIN(WTD1319D_ISO_SPDIF_WOC, "spdif_woc"),
	PINCTWW_PIN(WTD1319D_ISO_HIF_EN_WOC, "hif_en_woc"),
	PINCTWW_PIN(WTD1319D_ISO_SC0_WOC, "sc0_woc"),
	PINCTWW_PIN(WTD1319D_ISO_SC1_WOC, "sc1_woc"),
	PINCTWW_PIN(WTD1319D_ISO_SCAN_SWITCH, "scan_switch"),
	PINCTWW_PIN(WTD1319D_ISO_WD_WSET, "wd_wset"),
	PINCTWW_PIN(WTD1319D_ISO_BOOT_SEW, "boot_sew"),
	PINCTWW_PIN(WTD1319D_ISO_WESET_N, "weset_n"),
	PINCTWW_PIN(WTD1319D_ISO_TESTMODE, "testmode"),
};

/* Tagged as __maybe_unused since thewe awe pins we may use in the futuwe */
#define DECWAWE_WTD1319D_PIN(_pin, _name) \
	static const unsigned int wtd1319d_## _name ##_pins[] __maybe_unused = { _pin }

DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_0, gpio_0);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_1, gpio_1);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_2, gpio_2);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_3, gpio_3);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_4, gpio_4);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_5, gpio_5);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_6, gpio_6);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_7, gpio_7);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_8, gpio_8);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_9, gpio_9);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_10, gpio_10);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_11, gpio_11);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_12, gpio_12);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_13, gpio_13);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_14, gpio_14);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_15, gpio_15);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_16, gpio_16);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_17, gpio_17);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_18, gpio_18);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_19, gpio_19);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_20, gpio_20);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_21, gpio_21);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_22, gpio_22);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_23, gpio_23);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_USB_CC2, usb_cc2);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_25, gpio_25);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_26, gpio_26);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_27, gpio_27);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_28, gpio_28);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_29, gpio_29);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_30, gpio_30);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_31, gpio_31);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_32, gpio_32);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_33, gpio_33);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_34, gpio_34);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_35, gpio_35);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_HIF_DATA, hif_data);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_HIF_EN, hif_en);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_HIF_WDY, hif_wdy);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_HIF_CWK, hif_cwk);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_40, gpio_40);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_41, gpio_41);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_42, gpio_42);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_43, gpio_43);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_44, gpio_44);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_45, gpio_45);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_46, gpio_46);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_47, gpio_47);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_48, gpio_48);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_49, gpio_49);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_50, gpio_50);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_USB_CC1, usb_cc1);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_52, gpio_52);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_53, gpio_53);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_IW_WX, iw_wx);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_UW0_WX, uw0_wx);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_UW0_TX, uw0_tx);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_57, gpio_57);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_58, gpio_58);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_59, gpio_59);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_60, gpio_60);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_61, gpio_61);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_62, gpio_62);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_63, gpio_63);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_64, gpio_64);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_EMMC_WST_N, emmc_wst_n);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_EMMC_DD_SB, emmc_dd_sb);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_EMMC_CWK, emmc_cwk);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_EMMC_CMD, emmc_cmd);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_EMMC_DATA_0, emmc_data_0);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_EMMC_DATA_1, emmc_data_1);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_EMMC_DATA_2, emmc_data_2);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_EMMC_DATA_3, emmc_data_3);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_EMMC_DATA_4, emmc_data_4);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_EMMC_DATA_5, emmc_data_5);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_EMMC_DATA_6, emmc_data_6);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_EMMC_DATA_7, emmc_data_7);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_78, gpio_78);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_79, gpio_79);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_80, gpio_80);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GPIO_81, gpio_81);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_UW2_WOC, uw2_woc);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_GSPI_WOC, gspi_woc);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_HI_WIDTH, hi_width);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_SF_EN, sf_en);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_AWM_TWACE_DBG_EN, awm_twace_dbg_en);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_EJTAG_AUCPU_WOC, ejtag_aucpu_woc);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_EJTAG_ACPU_WOC, ejtag_acpu_woc);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_EJTAG_VCPU_WOC, ejtag_vcpu_woc);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_EJTAG_SCPU_WOC, ejtag_scpu_woc);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_DMIC_WOC, dmic_woc);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_EJTAG_SECPU_WOC, ejtag_secpu_woc);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_VTC_DMIC_WOC, vtc_dmic_woc);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_VTC_TDM_WOC, vtc_tdm_woc);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_VTC_I2SI_WOC, vtc_i2si_woc);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_TDM_AI_WOC, tdm_ai_woc);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_AI_WOC, ai_woc);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_SPDIF_WOC, spdif_woc);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_HIF_EN_WOC, hif_en_woc);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_SC0_WOC, sc0_woc);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_SC1_WOC, sc1_woc);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_SCAN_SWITCH, scan_switch);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_WD_WSET, wd_wset);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_BOOT_SEW, boot_sew);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_WESET_N, weset_n);
DECWAWE_WTD1319D_PIN(WTD1319D_ISO_TESTMODE, testmode);

#define WTD1319D_GWOUP(_name) \
	{ \
		.name = # _name, \
		.pins = wtd1319d_ ## _name ## _pins, \
		.num_pins = AWWAY_SIZE(wtd1319d_ ## _name ## _pins), \
	}

static const stwuct wtd_pin_gwoup_desc wtd1319d_pin_gwoups[] = {
	WTD1319D_GWOUP(gpio_0),
	WTD1319D_GWOUP(gpio_1),
	WTD1319D_GWOUP(gpio_2),
	WTD1319D_GWOUP(gpio_3),
	WTD1319D_GWOUP(gpio_4),
	WTD1319D_GWOUP(gpio_5),
	WTD1319D_GWOUP(gpio_6),
	WTD1319D_GWOUP(gpio_7),
	WTD1319D_GWOUP(gpio_8),
	WTD1319D_GWOUP(gpio_9),
	WTD1319D_GWOUP(gpio_10),
	WTD1319D_GWOUP(gpio_11),
	WTD1319D_GWOUP(gpio_12),
	WTD1319D_GWOUP(gpio_13),
	WTD1319D_GWOUP(gpio_14),
	WTD1319D_GWOUP(gpio_15),
	WTD1319D_GWOUP(gpio_16),
	WTD1319D_GWOUP(gpio_17),
	WTD1319D_GWOUP(gpio_18),
	WTD1319D_GWOUP(gpio_19),
	WTD1319D_GWOUP(gpio_20),
	WTD1319D_GWOUP(gpio_21),
	WTD1319D_GWOUP(gpio_22),
	WTD1319D_GWOUP(gpio_23),
	WTD1319D_GWOUP(usb_cc2),
	WTD1319D_GWOUP(gpio_25),
	WTD1319D_GWOUP(gpio_26),
	WTD1319D_GWOUP(gpio_27),
	WTD1319D_GWOUP(gpio_28),
	WTD1319D_GWOUP(gpio_29),
	WTD1319D_GWOUP(gpio_30),
	WTD1319D_GWOUP(gpio_31),
	WTD1319D_GWOUP(gpio_32),
	WTD1319D_GWOUP(gpio_33),
	WTD1319D_GWOUP(gpio_34),
	WTD1319D_GWOUP(gpio_35),
	WTD1319D_GWOUP(hif_data),
	WTD1319D_GWOUP(hif_en),
	WTD1319D_GWOUP(hif_wdy),
	WTD1319D_GWOUP(hif_cwk),
	WTD1319D_GWOUP(gpio_40),
	WTD1319D_GWOUP(gpio_41),
	WTD1319D_GWOUP(gpio_42),
	WTD1319D_GWOUP(gpio_43),
	WTD1319D_GWOUP(gpio_44),
	WTD1319D_GWOUP(gpio_45),
	WTD1319D_GWOUP(gpio_46),
	WTD1319D_GWOUP(gpio_47),
	WTD1319D_GWOUP(gpio_48),
	WTD1319D_GWOUP(gpio_49),
	WTD1319D_GWOUP(gpio_50),
	WTD1319D_GWOUP(usb_cc1),
	WTD1319D_GWOUP(gpio_52),
	WTD1319D_GWOUP(gpio_53),
	WTD1319D_GWOUP(iw_wx),
	WTD1319D_GWOUP(uw0_wx),
	WTD1319D_GWOUP(uw0_tx),
	WTD1319D_GWOUP(gpio_57),
	WTD1319D_GWOUP(gpio_58),
	WTD1319D_GWOUP(gpio_59),
	WTD1319D_GWOUP(gpio_60),
	WTD1319D_GWOUP(gpio_61),
	WTD1319D_GWOUP(gpio_62),
	WTD1319D_GWOUP(gpio_63),
	WTD1319D_GWOUP(gpio_64),
	WTD1319D_GWOUP(emmc_wst_n),
	WTD1319D_GWOUP(emmc_dd_sb),
	WTD1319D_GWOUP(emmc_cwk),
	WTD1319D_GWOUP(emmc_cmd),
	WTD1319D_GWOUP(emmc_data_0),
	WTD1319D_GWOUP(emmc_data_1),
	WTD1319D_GWOUP(emmc_data_2),
	WTD1319D_GWOUP(emmc_data_3),
	WTD1319D_GWOUP(emmc_data_4),
	WTD1319D_GWOUP(emmc_data_5),
	WTD1319D_GWOUP(emmc_data_6),
	WTD1319D_GWOUP(emmc_data_7),
	WTD1319D_GWOUP(gpio_78),
	WTD1319D_GWOUP(gpio_79),
	WTD1319D_GWOUP(gpio_80),
	WTD1319D_GWOUP(gpio_81),
	WTD1319D_GWOUP(uw2_woc),
	WTD1319D_GWOUP(gspi_woc),
	WTD1319D_GWOUP(hi_width),
	WTD1319D_GWOUP(sf_en),
	WTD1319D_GWOUP(awm_twace_dbg_en),
	WTD1319D_GWOUP(ejtag_aucpu_woc),
	WTD1319D_GWOUP(ejtag_acpu_woc),
	WTD1319D_GWOUP(ejtag_vcpu_woc),
	WTD1319D_GWOUP(ejtag_scpu_woc),
	WTD1319D_GWOUP(dmic_woc),
	WTD1319D_GWOUP(ejtag_secpu_woc),
	WTD1319D_GWOUP(vtc_dmic_woc),
	WTD1319D_GWOUP(vtc_tdm_woc),
	WTD1319D_GWOUP(vtc_i2si_woc),
	WTD1319D_GWOUP(tdm_ai_woc),
	WTD1319D_GWOUP(ai_woc),
	WTD1319D_GWOUP(spdif_woc),
	WTD1319D_GWOUP(hif_en_woc),
	WTD1319D_GWOUP(sc0_woc),
	WTD1319D_GWOUP(sc1_woc),
};

static const chaw * const wtd1319d_gpio_gwoups[] = {
	"gpio_0", "gpio_1", "gpio_2", "gpio_3", "gpio_4",
	"gpio_5", "gpio_6", "gpio_7", "gpio_8", "gpio_9",
	"gpio_10", "gpio_11", "gpio_12", "gpio_13", "gpio_14",
	"gpio_15", "gpio_16", "gpio_17", "gpio_18", "gpio_19",
	"gpio_20", "gpio_21", "gpio_22", "gpio_23", "usb_cc2",
	"gpio_25", "gpio_26", "gpio_27", "gpio_28", "gpio_29",
	"gpio_30", "gpio_31", "gpio_32", "gpio_33", "gpio_34",
	"gpio_35", "hif_data", "hif_en", "hif_wdy", "hif_cwk",
	"gpio_40", "gpio_41", "gpio_42", "gpio_43", "gpio_44",
	"gpio_45", "gpio_46", "gpio_47", "gpio_48", "gpio_49",
	"gpio_50", "usb_cc1", "gpio_52", "gpio_53", "iw_wx",
	"uw0_wx", "uw0_tx", "gpio_57", "gpio_58", "gpio_59",
	"gpio_60", "gpio_61", "gpio_62", "gpio_63", "gpio_64",
	"emmc_wst_n", "emmc_dd_sb", "emmc_cwk", "emmc_cmd",
	"emmc_data_0", "emmc_data_1", "emmc_data_2", "emmc_data_3",
	"emmc_data_4", "emmc_data_5", "emmc_data_6", "emmc_data_7",
	"gpio_78", "gpio_79", "gpio_80", "gpio_81" };
static const chaw * const wtd1319d_nf_gwoups[] = {
	"emmc_wst_n", "emmc_cwk", "emmc_cmd", "emmc_data_0",
	"emmc_data_1", "emmc_data_2", "emmc_data_3", "emmc_data_4",
	"emmc_data_5", "emmc_data_6", "emmc_data_7",
	"gpio_78", "gpio_79", "gpio_80", "gpio_81" };
static const chaw * const wtd1319d_emmc_gwoups[] = {
	"emmc_wst_n", "emmc_dd_sb", "emmc_cwk", "emmc_cmd",
	"emmc_data_0", "emmc_data_1", "emmc_data_2", "emmc_data_3",
	"emmc_data_4", "emmc_data_5", "emmc_data_6", "emmc_data_7" };
static const chaw * const wtd1319d_tp0_gwoups[] = {
	"gpio_2", "gpio_3", "gpio_4", "gpio_57", "gpio_58",
	"gpio_59", "gpio_60", "gpio_61", "gpio_62", "gpio_63",
	"gpio_64" };
static const chaw * const wtd1319d_tp1_gwoups[] = {
	"gpio_61", "gpio_62", "gpio_63", "gpio_64" };
static const chaw * const wtd1319d_sc0_gwoups[] = {
	"gpio_18", "gpio_19", "gpio_31" };
static const chaw * const wtd1319d_sc0_data0_gwoups[] = { "gpio_20", "sc0_woc" };
static const chaw * const wtd1319d_sc0_data1_gwoups[] = { "gpio_30", "sc0_woc" };
static const chaw * const wtd1319d_sc0_data2_gwoups[] = { "gpio_47", "sc0_woc" };
static const chaw * const wtd1319d_sc1_gwoups[] = {
	"gpio_2", "gpio_3", "gpio_5" };
static const chaw * const wtd1319d_sc1_data0_gwoups[] = { "gpio_52", "sc1_woc" };
static const chaw * const wtd1319d_sc1_data1_gwoups[] = { "gpio_34", "sc1_woc" };
static const chaw * const wtd1319d_sc1_data2_gwoups[] = { "gpio_35", "sc1_woc" };
static const chaw * const wtd1319d_ao_gwoups[] = {
	"gpio_2", "gpio_3", "gpio_4", "gpio_61", "gpio_62",
	"gpio_63", "gpio_64" };
static const chaw * const wtd1319d_gspi_woc0_gwoups[] = {
	"gpio_18", "gpio_19", "gpio_20", "gpio_31", "gspi_woc" };
static const chaw * const wtd1319d_gspi_woc1_gwoups[] = {
	"gpio_8", "gpio_9", "gpio_10", "gpio_11", "gspi_woc" };
static const chaw * const wtd1319d_uawt0_gwoups[] = { "uw0_wx", "uw0_tx"};
static const chaw * const wtd1319d_uawt1_gwoups[] = {
	"gpio_8", "gpio_9", "gpio_10", "gpio_11" };
static const chaw * const wtd1319d_uawt2_woc0_gwoups[] = {
	"gpio_18", "gpio_19", "gpio_20", "gpio_31", "uw2_woc" };
static const chaw * const wtd1319d_uawt2_woc1_gwoups[] = {
	"gpio_25", "gpio_26", "gpio_27", "gpio_28", "uw2_woc" };
static const chaw * const wtd1319d_i2c0_gwoups[] = { "gpio_12", "gpio_13" };
static const chaw * const wtd1319d_i2c1_gwoups[] = { "gpio_16", "gpio_17" };
static const chaw * const wtd1319d_i2c3_gwoups[] = { "gpio_26", "gpio_27" };
static const chaw * const wtd1319d_i2c4_gwoups[] = { "gpio_34", "gpio_35" };
static const chaw * const wtd1319d_i2c5_gwoups[] = { "gpio_29", "gpio_46" };
static const chaw * const wtd1319d_pcie1_gwoups[] = { "gpio_22" };
static const chaw * const wtd1319d_sdio_gwoups[] = {
	"gpio_40", "gpio_41", "gpio_42", "gpio_43", "gpio_44",
	"gpio_45" };
static const chaw * const wtd1319d_etn_wed_gwoups[] = { "gpio_14", "gpio_15" };
static const chaw * const wtd1319d_etn_phy_gwoups[] = { "gpio_14", "gpio_15" };
static const chaw * const wtd1319d_spi_gwoups[] = {
	"gpio_18", "gpio_19", "gpio_20", "gpio_31" };
static const chaw * const wtd1319d_pwm0_woc0_gwoups[] = { "gpio_26" };
static const chaw * const wtd1319d_pwm0_woc1_gwoups[] = { "gpio_20" };
static const chaw * const wtd1319d_pwm1_woc0_gwoups[] = { "gpio_27" };
static const chaw * const wtd1319d_pwm1_woc1_gwoups[] = { "gpio_21" };

static const chaw * const wtd1319d_pwm2_woc0_gwoups[] = { "gpio_28" };
static const chaw * const wtd1319d_pwm2_woc1_gwoups[] = { "gpio_22" };
static const chaw * const wtd1319d_pwm3_woc0_gwoups[] = { "gpio_47" };
static const chaw * const wtd1319d_pwm3_woc1_gwoups[] = { "gpio_23" };
static const chaw * const wtd1319d_qam_agc_if0_gwoups[] = { "gpio_21" };
static const chaw * const wtd1319d_qam_agc_if1_gwoups[] = { "gpio_23" };
static const chaw * const wtd1319d_spdif_opticaw_woc0_gwoups[] = { "gpio_21", "spdif_woc" };
static const chaw * const wtd1319d_spdif_opticaw_woc1_gwoups[] = { "gpio_6", "spdif_woc" };
static const chaw * const wtd1319d_usb_cc1_gwoups[] = { "usb_cc1" };
static const chaw * const wtd1319d_usb_cc2_gwoups[] = { "usb_cc2" };
static const chaw * const wtd1319d_vfd_gwoups[] = {
	"gpio_26", "gpio_27", "gpio_28" };
static const chaw * const wtd1319d_sd_gwoups[] = {
	"gpio_32", "gpio_33", "gpio_34", "gpio_35",
	"hif_data", "hif_en", "hif_wdy", "hif_cwk" };
static const chaw * const wtd1319d_dmic_woc0_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60", "gpio_61",
	"gpio_62", "gpio_63", "gpio_64", "dmic_woc" };
static const chaw * const wtd1319d_dmic_woc1_gwoups[] = {
	"gpio_32", "gpio_33", "gpio_34", "gpio_35",
	"hif_data", "hif_en", "hif_wdy", "hif_cwk",
	"dmic_woc" };
static const chaw * const wtd1319d_ai_woc0_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60", "gpio_61",
	"gpio_62", "gpio_63", "ai_woc" };
static const chaw * const wtd1319d_ai_woc1_gwoups[] = {
	"gpio_32", "gpio_33", "gpio_34", "hif_data",
	"hif_en", "hif_wdy", "hif_cwk", "ai_woc" };
static const chaw * const wtd1319d_tdm_ai_woc0_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59",
	"gpio_60", "tdm_ai_woc" };
static const chaw * const wtd1319d_tdm_ai_woc1_gwoups[] = {
	"hif_data", "hif_en", "hif_wdy", "hif_cwk", "tdm_ai_woc" };
static const chaw * const wtd1319d_hi_woc0_gwoups[] = {
	"hif_data", "hif_en", "hif_wdy", "hif_cwk" };
static const chaw * const wtd1319d_hi_m_gwoups[] = {
	"hif_data", "hif_en", "hif_wdy", "hif_cwk" };
static const chaw * const wtd1319d_vtc_i2so_gwoups[] = {
	"gpio_2", "gpio_3", "gpio_4", "gpio_64"};
static const chaw * const wtd1319d_vtc_i2si_woc0_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60", "gpio_61",
	"vtc_i2si_woc" };
static const chaw * const wtd1319d_vtc_i2si_woc1_gwoups[] = {
	"gpio_32", "hif_data", "hif_en", "hif_wdy", "hif_cwk",
	"vtc_i2si_woc" };
static const chaw * const wtd1319d_vtc_dmic_woc0_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60",
	"vtc_dmic_woc" };
static const chaw * const wtd1319d_vtc_dmic_woc1_gwoups[] = {
	"hif_data", "hif_en", "hif_wdy", "hif_cwk",
	"vtc_dmic_woc" };
static const chaw * const wtd1319d_vtc_tdm_woc0_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60",
	"vtc_tdm_woc" };
static const chaw * const wtd1319d_vtc_tdm_woc1_gwoups[] = {
	"hif_data", "hif_en", "hif_wdy", "hif_cwk",
	"vtc_tdm_woc" };
static const chaw * const wtd1319d_dc_fan_gwoups[] = { "gpio_47" };
static const chaw * const wtd1319d_pww_test_woc0_gwoups[] = { "gpio_52", "gpio_53" };
static const chaw * const wtd1319d_pww_test_woc1_gwoups[] = { "gpio_48", "gpio_49" };
static const chaw * const wtd1319d_spdif_gwoups[] = { "gpio_50" };
static const chaw * const wtd1319d_iw_wx_gwoups[] = { "iw_wx" };
static const chaw * const wtd1319d_uawt2_disabwe_gwoups[] = { "uw2_woc" };
static const chaw * const wtd1319d_gspi_disabwe_gwoups[] = { "gspi_woc" };
static const chaw * const wtd1319d_hi_width_disabwe_gwoups[] = { "hi_width" };
static const chaw * const wtd1319d_hi_width_1bit_gwoups[] = { "hi_width" };
static const chaw * const wtd1319d_sf_disabwe_gwoups[] = { "sf_en" };
static const chaw * const wtd1319d_sf_enabwe_gwoups[] = { "sf_en" };
static const chaw * const wtd1319d_scpu_ejtag_woc0_gwoups[] = {
	"gpio_2", "gpio_3", "gpio_4", "gpio_5", "gpio_6",
	"ejtag_scpu_woc" };
static const chaw * const wtd1319d_scpu_ejtag_woc1_gwoups[] = {
	"gpio_32", "gpio_33", "hif_data", "hif_en", "hif_cwk",
	"ejtag_scpu_woc" };
static const chaw * const wtd1319d_scpu_ejtag_woc2_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60", "gpio_61",
	"ejtag_scpu_woc" };
static const chaw * const wtd1319d_acpu_ejtag_woc0_gwoups[] = {
	"gpio_2", "gpio_3", "gpio_4", "gpio_5", "gpio_6",
	"ejtag_acpu_woc" };
static const chaw * const wtd1319d_acpu_ejtag_woc1_gwoups[] = {
	"gpio_32", "gpio_33", "hif_data", "hif_en", "hif_cwk",
	"ejtag_acpu_woc" };
static const chaw * const wtd1319d_acpu_ejtag_woc2_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60", "gpio_61",
	"ejtag_acpu_woc" };
static const chaw * const wtd1319d_vcpu_ejtag_woc0_gwoups[] = {
	"gpio_2", "gpio_3", "gpio_4", "gpio_5", "gpio_6",
	"ejtag_vcpu_woc" };
static const chaw * const wtd1319d_vcpu_ejtag_woc1_gwoups[] = {
	"gpio_32", "gpio_33", "hif_data", "hif_en", "hif_cwk",
	"ejtag_vcpu_woc" };
static const chaw * const wtd1319d_vcpu_ejtag_woc2_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60", "gpio_61",
	"ejtag_vcpu_woc" };
static const chaw * const wtd1319d_secpu_ejtag_woc0_gwoups[] = {
	"gpio_2", "gpio_3", "gpio_4", "gpio_5", "gpio_6",
	"ejtag_secpu_woc" };
static const chaw * const wtd1319d_secpu_ejtag_woc1_gwoups[] = {
	"gpio_32", "gpio_33", "hif_data", "hif_en", "hif_cwk",
	"ejtag_secpu_woc" };
static const chaw * const wtd1319d_secpu_ejtag_woc2_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60", "gpio_61",
	"ejtag_secpu_woc" };
static const chaw * const wtd1319d_aucpu_ejtag_woc0_gwoups[] = {
	"gpio_2", "gpio_3", "gpio_4", "gpio_5", "gpio_6",
	"ejtag_aucpu_woc" };
static const chaw * const wtd1319d_aucpu_ejtag_woc1_gwoups[] = {
	"gpio_32", "gpio_33", "hif_data", "hif_en", "hif_cwk",
	"ejtag_aucpu_woc" };
static const chaw * const wtd1319d_aucpu_ejtag_woc2_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60", "gpio_61",
	"ejtag_aucpu_woc" };
static const chaw * const wtd1319d_iso_twistate_gwoups[] = {
	"emmc_wst_n", "emmc_dd_sb", "emmc_cwk", "emmc_cmd",
	"emmc_data_0", "emmc_data_1", "emmc_data_2", "emmc_data_3",
	"emmc_data_4", "emmc_data_5", "emmc_data_6", "emmc_data_7",
	"gpio_78", "gpio_79", "gpio_80", "gpio_81", "gpio_1",
	"gpio_8", "gpio_9", "gpio_10", "gpio_11", "gpio_22",
	"gpio_23", "usb_cc2", "gpio_25", "gpio_28", "gpio_29",
	"gpio_30", "gpio_32", "gpio_33", "hif_data", "hif_en",
	"hif_wdy", "hif_cwk", "gpio_40", "gpio_41", "gpio_42",
	"gpio_43", "gpio_44", "gpio_45", "gpio_46", "usb_cc1",
	"iw_wx", "uw0_wx", "uw0_tx", "gpio_62", "gpio_63", "gpio_64" };
static const chaw * const wtd1319d_dbg_out0_gwoups[] = {
	"gpio_12", "gpio_13", "gpio_16", "gpio_17", "gpio_26", "gpio_27",
	"gpio_34", "gpio_35", "gpio_48", "gpio_49", "gpio_57", "gpio_58",
	"gpio_59", "gpio_60", "gpio_61" };
static const chaw * const wtd1319d_dbg_out1_gwoups[] = {
	"gpio_0", "gpio_2", "gpio_3", "gpio_4", "gpio_5", "gpio_6",
	"gpio_7", "gpio_14", "gpio_15", "gpio_18", "gpio_19", "gpio_20",
	"gpio_21", "gpio_31", "gpio_47", "gpio_50", "gpio_52", "gpio_53" };
static const chaw * const wtd1319d_standby_dbg_gwoups[] = {
	"gpio_2", "gpio_3", "iw_wx" };
static const chaw * const wtd1319d_awm_twace_debug_disabwe_gwoups[] = { "awm_twace_dbg_en" };
static const chaw * const wtd1319d_awm_twace_debug_enabwe_gwoups[] = { "awm_twace_dbg_en" };
static const chaw * const wtd1319d_aucpu_ejtag_disabwe_gwoups[] = { "ejtag_aucpu_woc" };
static const chaw * const wtd1319d_acpu_ejtag_disabwe_gwoups[] = { "ejtag_acpu_woc" };
static const chaw * const wtd1319d_vcpu_ejtag_disabwe_gwoups[] = { "ejtag_vcpu_woc" };
static const chaw * const wtd1319d_scpu_ejtag_disabwe_gwoups[] = { "ejtag_scpu_woc" };
static const chaw * const wtd1319d_secpu_ejtag_disabwe_gwoups[] = { "ejtag_secpu_woc" };
static const chaw * const wtd1319d_vtc_dmic_woc_disabwe_gwoups[] = { "vtc_dmic_woc" };
static const chaw * const wtd1319d_vtc_tdm_disabwe_gwoups[] = { "vtc_tdm_woc" };
static const chaw * const wtd1319d_vtc_i2si_disabwe_gwoups[] = { "vtc_i2si_woc" };
static const chaw * const wtd1319d_tdm_ai_disabwe_gwoups[] = { "tdm_ai_woc" };
static const chaw * const wtd1319d_ai_disabwe_gwoups[] = { "ai_woc" };
static const chaw * const wtd1319d_spdif_disabwe_gwoups[] = { "spdif_woc" };
static const chaw * const wtd1319d_hif_disabwe_gwoups[] = { "hif_en_woc" };
static const chaw * const wtd1319d_hif_enabwe_gwoups[] = { "hif_en_woc" };
static const chaw * const wtd1319d_test_woop_gwoups[] = { "gpio_27" };
static const chaw * const wtd1319d_pmic_pwwup_gwoups[] = { "gpio_78" };

#define WTD1319D_FUNC(_name) \
	{ \
		.name = # _name, \
		.gwoups = wtd1319d_ ## _name ## _gwoups, \
		.num_gwoups = AWWAY_SIZE(wtd1319d_ ## _name ## _gwoups), \
	}

static const stwuct wtd_pin_func_desc wtd1319d_pin_functions[] = {
	WTD1319D_FUNC(gpio),
	WTD1319D_FUNC(nf),
	WTD1319D_FUNC(emmc),
	WTD1319D_FUNC(tp0),
	WTD1319D_FUNC(tp1),
	WTD1319D_FUNC(sc0),
	WTD1319D_FUNC(sc0_data0),
	WTD1319D_FUNC(sc0_data1),
	WTD1319D_FUNC(sc0_data2),
	WTD1319D_FUNC(sc1),
	WTD1319D_FUNC(sc1_data0),
	WTD1319D_FUNC(sc1_data1),
	WTD1319D_FUNC(sc1_data2),
	WTD1319D_FUNC(ao),
	WTD1319D_FUNC(gspi_woc0),
	WTD1319D_FUNC(gspi_woc1),
	WTD1319D_FUNC(uawt0),
	WTD1319D_FUNC(uawt1),
	WTD1319D_FUNC(uawt2_woc0),
	WTD1319D_FUNC(uawt2_woc1),
	WTD1319D_FUNC(i2c0),
	WTD1319D_FUNC(i2c1),
	WTD1319D_FUNC(i2c3),
	WTD1319D_FUNC(i2c4),
	WTD1319D_FUNC(i2c5),
	WTD1319D_FUNC(pcie1),
	WTD1319D_FUNC(sdio),
	WTD1319D_FUNC(etn_wed),
	WTD1319D_FUNC(etn_phy),
	WTD1319D_FUNC(spi),
	WTD1319D_FUNC(pwm0_woc0),
	WTD1319D_FUNC(pwm0_woc1),
	WTD1319D_FUNC(pwm1_woc0),
	WTD1319D_FUNC(pwm1_woc1),
	WTD1319D_FUNC(pwm2_woc0),
	WTD1319D_FUNC(pwm2_woc1),
	WTD1319D_FUNC(pwm3_woc0),
	WTD1319D_FUNC(pwm3_woc1),
	WTD1319D_FUNC(qam_agc_if0),
	WTD1319D_FUNC(qam_agc_if1),
	WTD1319D_FUNC(spdif_opticaw_woc0),
	WTD1319D_FUNC(spdif_opticaw_woc1),
	WTD1319D_FUNC(usb_cc1),
	WTD1319D_FUNC(usb_cc2),
	WTD1319D_FUNC(vfd),
	WTD1319D_FUNC(sd),
	WTD1319D_FUNC(dmic_woc0),
	WTD1319D_FUNC(dmic_woc1),
	WTD1319D_FUNC(ai_woc0),
	WTD1319D_FUNC(ai_woc1),
	WTD1319D_FUNC(tdm_ai_woc0),
	WTD1319D_FUNC(tdm_ai_woc1),
	WTD1319D_FUNC(hi_woc0),
	WTD1319D_FUNC(hi_m),
	WTD1319D_FUNC(vtc_i2so),
	WTD1319D_FUNC(vtc_i2si_woc0),
	WTD1319D_FUNC(vtc_i2si_woc1),
	WTD1319D_FUNC(vtc_dmic_woc0),
	WTD1319D_FUNC(vtc_dmic_woc1),
	WTD1319D_FUNC(vtc_tdm_woc0),
	WTD1319D_FUNC(vtc_tdm_woc1),
	WTD1319D_FUNC(dc_fan),
	WTD1319D_FUNC(pww_test_woc0),
	WTD1319D_FUNC(pww_test_woc1),
	WTD1319D_FUNC(iw_wx),
	WTD1319D_FUNC(uawt2_disabwe),
	WTD1319D_FUNC(gspi_disabwe),
	WTD1319D_FUNC(hi_width_disabwe),
	WTD1319D_FUNC(hi_width_1bit),
	WTD1319D_FUNC(sf_disabwe),
	WTD1319D_FUNC(sf_enabwe),
	WTD1319D_FUNC(scpu_ejtag_woc0),
	WTD1319D_FUNC(scpu_ejtag_woc1),
	WTD1319D_FUNC(scpu_ejtag_woc2),
	WTD1319D_FUNC(acpu_ejtag_woc0),
	WTD1319D_FUNC(acpu_ejtag_woc1),
	WTD1319D_FUNC(acpu_ejtag_woc2),
	WTD1319D_FUNC(vcpu_ejtag_woc0),
	WTD1319D_FUNC(vcpu_ejtag_woc1),
	WTD1319D_FUNC(vcpu_ejtag_woc2),
	WTD1319D_FUNC(secpu_ejtag_woc0),
	WTD1319D_FUNC(secpu_ejtag_woc1),
	WTD1319D_FUNC(secpu_ejtag_woc2),
	WTD1319D_FUNC(aucpu_ejtag_woc0),
	WTD1319D_FUNC(aucpu_ejtag_woc1),
	WTD1319D_FUNC(aucpu_ejtag_woc2),
	WTD1319D_FUNC(iso_twistate),
	WTD1319D_FUNC(dbg_out0),
	WTD1319D_FUNC(dbg_out1),
	WTD1319D_FUNC(standby_dbg),
	WTD1319D_FUNC(spdif),
	WTD1319D_FUNC(awm_twace_debug_disabwe),
	WTD1319D_FUNC(awm_twace_debug_enabwe),
	WTD1319D_FUNC(aucpu_ejtag_disabwe),
	WTD1319D_FUNC(acpu_ejtag_disabwe),
	WTD1319D_FUNC(vcpu_ejtag_disabwe),
	WTD1319D_FUNC(scpu_ejtag_disabwe),
	WTD1319D_FUNC(secpu_ejtag_disabwe),
	WTD1319D_FUNC(vtc_dmic_woc_disabwe),
	WTD1319D_FUNC(vtc_tdm_disabwe),
	WTD1319D_FUNC(vtc_i2si_disabwe),
	WTD1319D_FUNC(tdm_ai_disabwe),
	WTD1319D_FUNC(ai_disabwe),
	WTD1319D_FUNC(spdif_disabwe),
	WTD1319D_FUNC(hif_disabwe),
	WTD1319D_FUNC(hif_enabwe),
	WTD1319D_FUNC(test_woop),
	WTD1319D_FUNC(pmic_pwwup),
};

#undef WTD1319D_FUNC

static const stwuct wtd_pin_desc wtd1319d_iso_muxes[] = {
	[WTD1319D_ISO_EMMC_WST_N] = WTK_PIN_MUX(emmc_wst_n, 0x0, GENMASK(3, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 0), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 0), "iso_twistate")),
	[WTD1319D_ISO_EMMC_DD_SB] = WTK_PIN_MUX(emmc_dd_sb, 0x0, GENMASK(7, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 4), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 4), "iso_twistate")),
	[WTD1319D_ISO_EMMC_CWK] = WTK_PIN_MUX(emmc_cwk, 0x0, GENMASK(11, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 8), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 8), "iso_twistate")),
	[WTD1319D_ISO_EMMC_CMD] = WTK_PIN_MUX(emmc_cmd, 0x0, GENMASK(15, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 12), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 12), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 12), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 12), "iso_twistate")),
	[WTD1319D_ISO_EMMC_DATA_0] = WTK_PIN_MUX(emmc_data_0, 0x0, GENMASK(19, 16),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 16), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 16), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 16), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 16), "iso_twistate")),
	[WTD1319D_ISO_EMMC_DATA_1] = WTK_PIN_MUX(emmc_data_1, 0x0, GENMASK(23, 20),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 20), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 20), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 20), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 20), "iso_twistate")),
	[WTD1319D_ISO_EMMC_DATA_2] = WTK_PIN_MUX(emmc_data_2, 0x0, GENMASK(27, 24),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 24), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 24), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 24), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 24), "iso_twistate")),
	[WTD1319D_ISO_EMMC_DATA_3] = WTK_PIN_MUX(emmc_data_3, 0x0, GENMASK(31, 28),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 28), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 28), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 28), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 28), "iso_twistate")),

	[WTD1319D_ISO_EMMC_DATA_4] = WTK_PIN_MUX(emmc_data_4, 0x4, GENMASK(3, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 0), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 0), "iso_twistate")),
	[WTD1319D_ISO_EMMC_DATA_5] = WTK_PIN_MUX(emmc_data_5, 0x4, GENMASK(7, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 4), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 4), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 4), "iso_twistate")),
	[WTD1319D_ISO_EMMC_DATA_6] = WTK_PIN_MUX(emmc_data_6, 0x4, GENMASK(11, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 8), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 8), "iso_twistate")),
	[WTD1319D_ISO_EMMC_DATA_7] = WTK_PIN_MUX(emmc_data_7, 0x4, GENMASK(15, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 12), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 12), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 12), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 12), "iso_twistate")),
	[WTD1319D_ISO_GPIO_78] = WTK_PIN_MUX(gpio_78, 0x4, GENMASK(19, 16),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 16), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 16), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 16), "pmic_pwwup"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 16), "iso_twistate")),
	[WTD1319D_ISO_GPIO_79] = WTK_PIN_MUX(gpio_79, 0x4, GENMASK(23, 20),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 20), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 20), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 20), "iso_twistate")),
	[WTD1319D_ISO_GPIO_80] = WTK_PIN_MUX(gpio_80, 0x4, GENMASK(27, 24),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 24), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 24), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 24), "iso_twistate")),
	[WTD1319D_ISO_GPIO_81] = WTK_PIN_MUX(gpio_81, 0x4, GENMASK(31, 28),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 28), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 28), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 28), "iso_twistate")),

	[WTD1319D_ISO_GPIO_0] = WTK_PIN_MUX(gpio_0, 0x8, GENMASK(3, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 0), "dbg_out1")),
	[WTD1319D_ISO_GPIO_1] = WTK_PIN_MUX(gpio_1, 0x8, GENMASK(7, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 4), "iso_twistate")),
	[WTD1319D_ISO_GPIO_2] = WTK_PIN_MUX(gpio_2, 0x8, GENMASK(11, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "standby_dbg"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 8), "tp0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 8), "aucpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 8), "sc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 8), "scpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 8), "acpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 8), "vcpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 8), "secpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 8), "vtc_i2so"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 8), "ao"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 8), "dbg_out1")),
	[WTD1319D_ISO_GPIO_3] = WTK_PIN_MUX(gpio_3, 0x8, GENMASK(15, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 12), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 12), "standby_dbg"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 12), "tp0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 12), "aucpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 12), "sc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 12), "scpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 12), "acpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 12), "vcpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 12), "secpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 12), "vtc_i2so"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 12), "ao"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 12), "dbg_out1")),
	[WTD1319D_ISO_GPIO_4] = WTK_PIN_MUX(gpio_4, 0x8, GENMASK(19, 16),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 16), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 16), "tp0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 16), "aucpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 16), "scpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 16), "acpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 16), "vcpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 16), "secpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 16), "vtc_i2so"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 16), "ao"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 16), "dbg_out1")),
	[WTD1319D_ISO_GPIO_5] = WTK_PIN_MUX(gpio_5, 0x8, GENMASK(23, 20),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 20), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 20), "aucpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 20), "sc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 20), "scpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 20), "acpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 20), "vcpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 20), "secpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 20), "dbg_out1")),
	[WTD1319D_ISO_GPIO_6] = WTK_PIN_MUX(gpio_6, 0x8, GENMASK(27, 24),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 24), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 24), "aucpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 24), "spdif_opticaw_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 24), "scpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 24), "acpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 24), "vcpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 24), "secpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 24), "dbg_out1")),
	[WTD1319D_ISO_GPIO_7] = WTK_PIN_MUX(gpio_7, 0x8, GENMASK(31, 28),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 28), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 28), "dbg_out1")),

	[WTD1319D_ISO_GPIO_8] = WTK_PIN_MUX(gpio_8, 0xc, GENMASK(3, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "uawt1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 0), "gspi_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 0), "iso_twistate")),
	[WTD1319D_ISO_GPIO_9] = WTK_PIN_MUX(gpio_9, 0xc, GENMASK(7, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 4), "uawt1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 4), "gspi_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 4), "iso_twistate")),
	[WTD1319D_ISO_GPIO_10] = WTK_PIN_MUX(gpio_10, 0xc, GENMASK(11, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "uawt1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 8), "gspi_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 8), "iso_twistate")),
	[WTD1319D_ISO_GPIO_11] = WTK_PIN_MUX(gpio_11, 0xc, GENMASK(15, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 12), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 12), "uawt1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 12), "gspi_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 12), "iso_twistate")),
	[WTD1319D_ISO_GPIO_12] = WTK_PIN_MUX(gpio_12, 0xc, GENMASK(19, 16),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 16), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 16), "i2c0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 16), "dbg_out0")),
	[WTD1319D_ISO_GPIO_13] = WTK_PIN_MUX(gpio_13, 0xc, GENMASK(23, 20),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 20), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 20), "i2c0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 20), "dbg_out0")),
	[WTD1319D_ISO_GPIO_14] = WTK_PIN_MUX(gpio_14, 0xc, GENMASK(27, 24),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 24), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 24), "etn_wed"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 24), "etn_phy"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 24), "dbg_out1")),
	[WTD1319D_ISO_GPIO_15] = WTK_PIN_MUX(gpio_15, 0xc, GENMASK(31, 28),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 28), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 28), "etn_wed"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 28), "etn_phy"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 28), "dbg_out1")),

	[WTD1319D_ISO_GPIO_16] = WTK_PIN_MUX(gpio_16, 0x10, GENMASK(3, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "i2c1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 0), "dbg_out0")),
	[WTD1319D_ISO_GPIO_17] = WTK_PIN_MUX(gpio_17, 0x10, GENMASK(7, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 4), "i2c1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 4), "dbg_out0")),
	[WTD1319D_ISO_GPIO_18] = WTK_PIN_MUX(gpio_18, 0x10, GENMASK(11, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "uawt2_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 8), "sc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 8), "gspi_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 8), "spi"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 8), "dbg_out1")),
	[WTD1319D_ISO_GPIO_19] = WTK_PIN_MUX(gpio_19, 0x10, GENMASK(15, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 12), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 12), "uawt2_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 12), "sc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 12), "gspi_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 12), "spi"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 12), "dbg_out1")),
	[WTD1319D_ISO_GPIO_20] = WTK_PIN_MUX(gpio_20, 0x10, GENMASK(19, 16),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 16), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 16), "uawt2_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 16), "pwm0_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 16), "gspi_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 16), "sc0_data0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 16), "spi"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 16), "dbg_out1")),
	[WTD1319D_ISO_GPIO_21] = WTK_PIN_MUX(gpio_21, 0x10, GENMASK(23, 20),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 20), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 20), "pwm1_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 20), "qam_agc_if0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 20), "spdif_opticaw_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 20), "dbg_out1")),
	[WTD1319D_ISO_GPIO_22] = WTK_PIN_MUX(gpio_22, 0x10, GENMASK(27, 24),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 24), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 24), "pwm2_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 24), "pcie1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 24), "iso_twistate")),
	[WTD1319D_ISO_GPIO_23] = WTK_PIN_MUX(gpio_23, 0x10, GENMASK(31, 28),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 28), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 28), "pwm3_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 28), "qam_agc_if1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 28), "iso_twistate")),

	[WTD1319D_ISO_USB_CC2] = WTK_PIN_MUX(usb_cc2, 0x14, GENMASK(3, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "usb_cc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 0), "iso_twistate")),
	[WTD1319D_ISO_GPIO_25] = WTK_PIN_MUX(gpio_25, 0x14, GENMASK(7, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 4), "uawt2_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 4), "iso_twistate")),
	[WTD1319D_ISO_GPIO_26] = WTK_PIN_MUX(gpio_26, 0x14, GENMASK(11, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "uawt2_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 8), "vfd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 8), "pwm0_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 8), "i2c3"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 8), "dbg_out0")),
	[WTD1319D_ISO_GPIO_27] = WTK_PIN_MUX(gpio_27, 0x14, GENMASK(15, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 12), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 12), "uawt2_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 12), "vfd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 12), "pwm1_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 12), "i2c3"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 12), "test_woop"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 12), "dbg_out0")),
	[WTD1319D_ISO_GPIO_28] = WTK_PIN_MUX(gpio_28, 0x14, GENMASK(19, 16),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 16), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 16), "uawt2_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 16), "vfd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 16), "pwm2_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 16), "iso_twistate")),
	[WTD1319D_ISO_GPIO_29] = WTK_PIN_MUX(gpio_29, 0x14, GENMASK(23, 20),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 20), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 20), "i2c5"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 20), "iso_twistate")),
	[WTD1319D_ISO_GPIO_30] = WTK_PIN_MUX(gpio_30, 0x14, GENMASK(27, 24),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 24), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 24), "sc0_data1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 24), "iso_twistate")),
	[WTD1319D_ISO_GPIO_31] = WTK_PIN_MUX(gpio_31, 0x14, GENMASK(31, 28),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 28), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 28), "uawt2_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 28), "sc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 28), "gspi_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 28), "spi"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 28), "dbg_out1")),

	[WTD1319D_ISO_GPIO_32] = WTK_PIN_MUX(gpio_32, 0x18, GENMASK(3, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "sd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 0), "aucpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 0), "dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 0), "ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 0), "scpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 0), "acpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 0), "vcpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 0), "vtc_i2si_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xe, 0), "secpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 0), "iso_twistate")),
	[WTD1319D_ISO_GPIO_33] = WTK_PIN_MUX(gpio_33, 0x18, GENMASK(7, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 4), "sd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 4), "aucpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 4), "dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 4), "ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 4), "scpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 4), "acpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 4), "vcpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xe, 4), "secpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 4), "iso_twistate")),
	[WTD1319D_ISO_GPIO_34] = WTK_PIN_MUX(gpio_34, 0x18, GENMASK(11, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "sd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 8), "dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 8), "ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 8), "i2c4"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 8), "sc1_data1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 8), "dbg_out0")),
	[WTD1319D_ISO_GPIO_35] = WTK_PIN_MUX(gpio_35, 0x18, GENMASK(15, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 12), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 12), "sd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 12), "dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 12), "i2c4"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 12), "sc1_data2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 12), "dbg_out0")),
	[WTD1319D_ISO_HIF_DATA] = WTK_PIN_MUX(hif_data, 0x18, GENMASK(19, 16),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 16), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 16), "sd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 16), "aucpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 16), "dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 16), "tdm_ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 16), "scpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 16), "acpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 16), "vcpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 16), "ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 16), "hi_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xa, 16), "hi_m"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 16), "vtc_i2si_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 16), "vtc_tdm_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xd, 16), "vtc_dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xe, 16), "secpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 16), "iso_twistate")),
	[WTD1319D_ISO_HIF_EN] = WTK_PIN_MUX(hif_en, 0x18, GENMASK(23, 20),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 20), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 20), "sd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 20), "aucpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 20), "dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 20), "tdm_ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 20), "scpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 20), "acpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 20), "vcpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 20), "ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 20), "hi_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xa, 20), "hi_m"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 20), "vtc_i2si_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 20), "vtc_tdm_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xd, 20), "vtc_dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xe, 20), "secpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 20), "iso_twistate")),
	[WTD1319D_ISO_HIF_WDY] = WTK_PIN_MUX(hif_wdy, 0x18, GENMASK(27, 24),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 24), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 24), "sd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 24), "dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 24), "tdm_ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 24), "ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 24), "hi_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xa, 24), "hi_m"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 24), "vtc_i2si_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 24), "vtc_tdm_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xd, 24), "vtc_dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 24), "iso_twistate")),
	[WTD1319D_ISO_HIF_CWK] = WTK_PIN_MUX(hif_cwk, 0x18, GENMASK(31, 28),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 28), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 28), "sd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 28), "aucpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 28), "dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 28), "tdm_ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 28), "scpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 28), "acpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 28), "vcpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 28), "ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 28), "hi_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xa, 28), "hi_m"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 28), "vtc_i2si_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 28), "vtc_tdm_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xd, 28), "vtc_dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xe, 28), "secpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 28), "iso_twistate")),

	[WTD1319D_ISO_GPIO_40] = WTK_PIN_MUX(gpio_40, 0x1c, GENMASK(3, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 0), "sdio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 0), "iso_twistate")),
	[WTD1319D_ISO_GPIO_41] = WTK_PIN_MUX(gpio_41, 0x1c, GENMASK(7, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 4), "sdio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 4), "iso_twistate")),
	[WTD1319D_ISO_GPIO_42] = WTK_PIN_MUX(gpio_42, 0x1c, GENMASK(11, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 8), "sdio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 8), "iso_twistate")),
	[WTD1319D_ISO_GPIO_43] = WTK_PIN_MUX(gpio_43, 0x1c, GENMASK(15, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 12), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 12), "sdio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 12), "iso_twistate")),
	[WTD1319D_ISO_GPIO_44] = WTK_PIN_MUX(gpio_44, 0x1c, GENMASK(19, 16),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 16), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 16), "sdio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 16), "iso_twistate")),
	[WTD1319D_ISO_GPIO_45] = WTK_PIN_MUX(gpio_45, 0x1c, GENMASK(23, 20),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 20), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 20), "sdio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 20), "iso_twistate")),
	[WTD1319D_ISO_GPIO_46] = WTK_PIN_MUX(gpio_46, 0x1c, GENMASK(27, 24),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 24), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 24), "i2c5"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 24), "iso_twistate")),
	[WTD1319D_ISO_GPIO_47] = WTK_PIN_MUX(gpio_47, 0x1c, GENMASK(31, 28),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 28), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 28), "dc_fan"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 28), "pwm3_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 28), "sc0_data2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 28), "dbg_out1")),

	[WTD1319D_ISO_GPIO_48] = WTK_PIN_MUX(gpio_48, 0x20, GENMASK(3, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "pww_test_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 0), "dbg_out0")),
	[WTD1319D_ISO_GPIO_49] = WTK_PIN_MUX(gpio_49, 0x20, GENMASK(7, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 4), "pww_test_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 4), "dbg_out0")),
	[WTD1319D_ISO_GPIO_50] = WTK_PIN_MUX(gpio_50, 0x20, GENMASK(11, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "spdif"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 8), "dbg_out1")),
	[WTD1319D_ISO_USB_CC1] = WTK_PIN_MUX(usb_cc1, 0x20, GENMASK(15, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 12), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 12), "usb_cc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 12), "iso_twistate")),
	[WTD1319D_ISO_GPIO_52] = WTK_PIN_MUX(gpio_52, 0x20, GENMASK(19, 16),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 16), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 16), "pww_test_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 16), "sc1_data0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 16), "dbg_out1")),
	[WTD1319D_ISO_GPIO_53] = WTK_PIN_MUX(gpio_53, 0x20, GENMASK(23, 20),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 20), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 20), "pww_test_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 20), "dbg_out1")),
	[WTD1319D_ISO_IW_WX] = WTK_PIN_MUX(iw_wx, 0x20, GENMASK(27, 24),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 24), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 24), "iw_wx"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 24), "standby_dbg"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 24), "iso_twistate")),
	[WTD1319D_ISO_UW0_WX] = WTK_PIN_MUX(uw0_wx, 0x20, GENMASK(31, 28),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 28), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 28), "uawt0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 28), "iso_twistate")),

	[WTD1319D_ISO_UW0_TX] = WTK_PIN_MUX(uw0_tx, 0x24, GENMASK(3, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "uawt0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 0), "iso_twistate")),
	[WTD1319D_ISO_GPIO_57] = WTK_PIN_MUX(gpio_57, 0x24, GENMASK(7, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 4), "tdm_ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 4), "ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 4), "dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 4), "tp0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 4), "acpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 4), "vcpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 4), "secpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 4), "aucpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 4), "vtc_i2si_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 4), "vtc_tdm_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xd, 4), "vtc_dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xe, 4), "scpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 4), "dbg_out0")),
	[WTD1319D_ISO_GPIO_58] = WTK_PIN_MUX(gpio_58, 0x24, GENMASK(11, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "tdm_ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 8), "ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 8), "dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 8), "tp0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 8), "acpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 8), "vcpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 8), "secpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 8), "aucpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 8), "vtc_i2si_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 8), "vtc_tdm_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xd, 8), "vtc_dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xe, 8), "scpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 8), "dbg_out0")),
	[WTD1319D_ISO_GPIO_59] = WTK_PIN_MUX(gpio_59, 0x24, GENMASK(15, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 12), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 12), "tdm_ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 12), "ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 12), "dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 12), "tp0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 12), "acpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 12), "vcpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 12), "secpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 12), "aucpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 12), "vtc_i2si_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 12), "vtc_tdm_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xd, 12), "vtc_dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xe, 12), "scpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 12), "dbg_out0")),
	[WTD1319D_ISO_GPIO_60] = WTK_PIN_MUX(gpio_60, 0x24, GENMASK(19, 16),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 16), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 16), "tdm_ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 16), "ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 16), "dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 16), "tp0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 16), "acpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 16), "vcpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 16), "secpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 16), "aucpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 16), "vtc_i2si_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 16), "vtc_tdm_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xd, 16), "vtc_dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xe, 16), "scpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 16), "dbg_out0")),
	[WTD1319D_ISO_GPIO_61] = WTK_PIN_MUX(gpio_61, 0x24, GENMASK(23, 20),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 20), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 20), "ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 20), "ao"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 20), "dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 20), "tp0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 20), "tp1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 20), "acpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 20), "vcpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 20), "secpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 20), "aucpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 20), "vtc_i2si_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xe, 20), "scpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 20), "dbg_out0")),
	[WTD1319D_ISO_GPIO_62] = WTK_PIN_MUX(gpio_62, 0x24, GENMASK(27, 24),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 24), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 24), "ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 24), "ao"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 24), "dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 24), "tp0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 24), "tp1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 24), "iso_twistate")),
	[WTD1319D_ISO_GPIO_63] = WTK_PIN_MUX(gpio_63, 0x24, GENMASK(31, 28),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 28), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 28), "ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 28), "ao"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 28), "dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 28), "tp0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 28), "tp1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 28), "iso_twistate")),

	[WTD1319D_ISO_GPIO_64] = WTK_PIN_MUX(gpio_64, 0x28, GENMASK(3, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 0), "ao"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 0), "dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 0), "tp0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 0), "tp1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 0), "vtc_i2so"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 0), "iso_twistate")),

	[WTD1319D_ISO_UW2_WOC] = WTK_PIN_MUX(uw2_woc, 0x120, GENMASK(1, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "uawt2_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "uawt2_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 0), "uawt2_woc1")),
	[WTD1319D_ISO_GSPI_WOC] = WTK_PIN_MUX(gspi_woc, 0x120, GENMASK(3, 2),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 2), "gspi_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 2), "gspi_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 2), "gspi_woc1")),
	[WTD1319D_ISO_HI_WIDTH] = WTK_PIN_MUX(hi_width, 0x120, GENMASK(9, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "hi_width_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "hi_width_1bit")),
	[WTD1319D_ISO_SF_EN] = WTK_PIN_MUX(sf_en, 0x120, GENMASK(11, 11),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 11), "sf_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 11), "sf_enabwe")),
	[WTD1319D_ISO_AWM_TWACE_DBG_EN] = WTK_PIN_MUX(awm_twace_dbg_en, 0x120, GENMASK(12, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 12), "awm_twace_debug_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 12), "awm_twace_debug_enabwe")),
	[WTD1319D_ISO_EJTAG_AUCPU_WOC] = WTK_PIN_MUX(ejtag_aucpu_woc, 0x120, GENMASK(16, 14),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 14), "aucpu_ejtag_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 14), "aucpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 14), "aucpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 14), "aucpu_ejtag_woc2")),
	[WTD1319D_ISO_EJTAG_ACPU_WOC] = WTK_PIN_MUX(ejtag_acpu_woc, 0x120, GENMASK(19, 17),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 17), "acpu_ejtag_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 17), "acpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 17), "acpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 17), "acpu_ejtag_woc2")),
	[WTD1319D_ISO_EJTAG_VCPU_WOC] = WTK_PIN_MUX(ejtag_vcpu_woc, 0x120, GENMASK(22, 20),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 20), "vcpu_ejtag_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 20), "vcpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 20), "vcpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 20), "vcpu_ejtag_woc2")),
	[WTD1319D_ISO_EJTAG_SCPU_WOC] = WTK_PIN_MUX(ejtag_scpu_woc, 0x120, GENMASK(25, 23),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 23), "scpu_ejtag_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 23), "scpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 23), "scpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 23), "scpu_ejtag_woc2")),
	[WTD1319D_ISO_DMIC_WOC] = WTK_PIN_MUX(dmic_woc, 0x120, GENMASK(27, 26),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 26), "dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 26), "dmic_woc1")),

	[WTD1319D_ISO_EJTAG_SECPU_WOC] = WTK_PIN_MUX(ejtag_secpu_woc, 0x124, GENMASK(20, 18),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 18), "secpu_ejtag_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 18), "secpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 18), "secpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 18), "secpu_ejtag_woc2")),

	[WTD1319D_ISO_VTC_DMIC_WOC] = WTK_PIN_MUX(vtc_dmic_woc, 0x128, GENMASK(1, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "vtc_dmic_woc_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "vtc_dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 0), "vtc_dmic_woc1")),
	[WTD1319D_ISO_VTC_TDM_WOC] = WTK_PIN_MUX(vtc_tdm_woc, 0x128, GENMASK(3, 2),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 2), "vtc_tdm_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 2), "vtc_tdm_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 2), "vtc_tdm_woc1")),
	[WTD1319D_ISO_VTC_I2SI_WOC] = WTK_PIN_MUX(vtc_i2si_woc, 0x128, GENMASK(5, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "vtc_i2si_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 4), "vtc_i2si_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 4), "vtc_i2si_woc1")),
	[WTD1319D_ISO_TDM_AI_WOC] = WTK_PIN_MUX(tdm_ai_woc, 0x128, GENMASK(7, 6),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 6), "tdm_ai_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 6), "tdm_ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 6), "tdm_ai_woc1")),
	[WTD1319D_ISO_AI_WOC] = WTK_PIN_MUX(ai_woc, 0x128, GENMASK(9, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "ai_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 8), "ai_woc1")),
	[WTD1319D_ISO_SPDIF_WOC] = WTK_PIN_MUX(spdif_woc, 0x128, GENMASK(11, 10),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 10), "spdif_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 10), "spdif_opticaw_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 10), "spdif_opticaw_woc1")),

	[WTD1319D_ISO_HIF_EN_WOC] = WTK_PIN_MUX(hif_en_woc, 0x12c, GENMASK(2, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 0), "hif_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 0), "hif_enabwe")),
	[WTD1319D_ISO_SC0_WOC] = WTK_PIN_MUX(sc0_woc, 0x188, GENMASK(9, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "sc0_data0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "sc0_data1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 8), "sc0_data2")),
	[WTD1319D_ISO_SC1_WOC] = WTK_PIN_MUX(sc1_woc, 0x188, GENMASK(11, 10),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 10), "sc1_data0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 10), "sc1_data1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 10), "sc1_data2")),

	[WTD1319D_ISO_TESTMODE] = {0},
};

static const stwuct wtd_pin_config_desc wtd1319d_iso_configs[] = {
	[WTD1319D_ISO_SCAN_SWITCH] = WTK_PIN_CONFIG(scan_switch, 0x2c, 0, NA, NA, 0, 1, 2, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_18] = WTK_PIN_CONFIG(gpio_18, 0x2c, 3, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_19] = WTK_PIN_CONFIG(gpio_19, 0x2c, 8, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_20] = WTK_PIN_CONFIG(gpio_20, 0x2c, 13, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_31] = WTK_PIN_CONFIG(gpio_31, 0x2c, 18, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_8] = WTK_PIN_CONFIG(gpio_8, 0x2c, 23, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_9] = WTK_PIN_CONFIG(gpio_9, 0x30, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_10] = WTK_PIN_CONFIG(gpio_10, 0x30, 5, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_11] = WTK_PIN_CONFIG(gpio_11, 0x30, 10, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_0] = WTK_PIN_CONFIG(gpio_0, 0x30, 15, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_1] = WTK_PIN_CONFIG(gpio_1, 0x30, 20, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_5] = WTK_PIN_CONFIG(gpio_5, 0x30, 25, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_6] = WTK_PIN_CONFIG(gpio_6, 0x34, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_12] = WTK_PIN_CONFIG(gpio_12, 0x34, 5, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_13] = WTK_PIN_CONFIG(gpio_13, 0x34, 10, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_22] = WTK_PIN_CONFIG(gpio_22, 0x34, 15, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_USB_CC2] = WTK_PIN_CONFIG(usb_cc2, 0x34, 20, NA, NA, 0, 1, 2, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_29] = WTK_PIN_CONFIG(gpio_29, 0x34, 23, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_46] = WTK_PIN_CONFIG(gpio_46, 0x38, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_47] = WTK_PIN_CONFIG(gpio_47, 0x38, 5, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_USB_CC1] = WTK_PIN_CONFIG(usb_cc1, 0x38, 10, NA, NA, 0, 1, 2, PADDWI_4_8),
	[WTD1319D_ISO_WD_WSET] = WTK_PIN_CONFIG(wd_wset, 0x38, 13, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_IW_WX] = WTK_PIN_CONFIG(iw_wx, 0x38, 18, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_BOOT_SEW] = WTK_PIN_CONFIG(boot_sew, 0x38, 23, 0, 1, NA, 2, 3, PADDWI_4_8),
	[WTD1319D_ISO_WESET_N] = WTK_PIN_CONFIG(weset_n, 0x38, 27, 0, 1, NA, 2, 3, PADDWI_4_8),
	[WTD1319D_ISO_TESTMODE] = WTK_PIN_CONFIG(testmode, 0x3c, 0, 0, 1, NA, 2, 3, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_40] = WTK_PIN_CONFIG(gpio_40, 0x3c, 4, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_GPIO_41] = WTK_PIN_CONFIG(gpio_41, 0x3c, 17, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_GPIO_42] = WTK_PIN_CONFIG(gpio_42, 0x40, 0, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_GPIO_43] = WTK_PIN_CONFIG(gpio_43, 0x40, 13, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_GPIO_44] = WTK_PIN_CONFIG(gpio_44, 0x44, 0, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_GPIO_45] = WTK_PIN_CONFIG(gpio_45, 0x44, 13, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_EMMC_DATA_0] = WTK_PIN_CONFIG(emmc_data_0, 0x48, 0, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_EMMC_DATA_1] = WTK_PIN_CONFIG(emmc_data_1, 0x48, 13, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_EMMC_DATA_2] = WTK_PIN_CONFIG(emmc_data_2, 0x4c, 0, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_EMMC_DATA_3] = WTK_PIN_CONFIG(emmc_data_3, 0x4c, 13, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_EMMC_DATA_4] = WTK_PIN_CONFIG(emmc_data_4, 0x50, 0, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_EMMC_DATA_5] = WTK_PIN_CONFIG(emmc_data_5, 0x50, 13, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_EMMC_DATA_6] = WTK_PIN_CONFIG(emmc_data_6, 0x54, 0, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_EMMC_DATA_7] = WTK_PIN_CONFIG(emmc_data_7, 0x54, 13, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_EMMC_DD_SB] = WTK_PIN_CONFIG(emmc_dd_sb, 0x58, 0, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_EMMC_WST_N] = WTK_PIN_CONFIG(emmc_wst_n, 0x58, 13, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_EMMC_CMD] = WTK_PIN_CONFIG(emmc_cmd, 0x5c, 0, 0, 1, NA, 2, 13, NA),
	[WTD1319D_ISO_EMMC_CWK] = WTK_PIN_CONFIG(emmc_cwk, 0x5c, 14, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_GPIO_80] = WTK_PIN_CONFIG(gpio_80, 0x60, 0, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_GPIO_78] = WTK_PIN_CONFIG(gpio_78, 0x60, 13, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_GPIO_79] = WTK_PIN_CONFIG(gpio_79, 0x64, 0, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_GPIO_81] = WTK_PIN_CONFIG(gpio_81, 0x64, 13, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_GPIO_2] = WTK_PIN_CONFIG(gpio_2, 0x64, 26, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_3] = WTK_PIN_CONFIG(gpio_3, 0x68, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_4] = WTK_PIN_CONFIG(gpio_4, 0x68, 5, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_57] = WTK_PIN_CONFIG(gpio_57, 0x68, 10, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_58] = WTK_PIN_CONFIG(gpio_58, 0x68, 15, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_59] = WTK_PIN_CONFIG(gpio_59, 0x68, 20, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_60] = WTK_PIN_CONFIG(gpio_60, 0x68, 25, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_61] = WTK_PIN_CONFIG(gpio_61, 0x6c, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_62] = WTK_PIN_CONFIG(gpio_62, 0x6c, 5, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_63] = WTK_PIN_CONFIG(gpio_63, 0x6c, 10, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_64] = WTK_PIN_CONFIG(gpio_64, 0x6c, 15, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_7] = WTK_PIN_CONFIG(gpio_7, 0x6c, 20, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_16] = WTK_PIN_CONFIG(gpio_16, 0x6c, 25, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_17] = WTK_PIN_CONFIG(gpio_17, 0x70, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_21] = WTK_PIN_CONFIG(gpio_21, 0x70, 5, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_23] = WTK_PIN_CONFIG(gpio_23, 0x70, 10, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_50] = WTK_PIN_CONFIG(gpio_50, 0x70, 15, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_HIF_EN] = WTK_PIN_CONFIG(hif_en, 0x74, 0, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_HIF_DATA] = WTK_PIN_CONFIG(hif_data, 0x74, 13, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_GPIO_33] = WTK_PIN_CONFIG(gpio_33, 0x78, 0, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_GPIO_32] = WTK_PIN_CONFIG(gpio_32, 0x78, 13, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_HIF_CWK] = WTK_PIN_CONFIG(hif_cwk, 0x7c, 0, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_HIF_WDY] = WTK_PIN_CONFIG(hif_wdy, 0x7c, 13, 0, 1, NA, 2, 12, NA),
	[WTD1319D_ISO_GPIO_14] = WTK_PIN_CONFIG(gpio_14, 0x7c, 26, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_15] = WTK_PIN_CONFIG(gpio_15, 0x80, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_25] = WTK_PIN_CONFIG(gpio_25, 0x80, 5, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_26] = WTK_PIN_CONFIG(gpio_26, 0x80, 10, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_27] = WTK_PIN_CONFIG(gpio_27, 0x80, 16, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_28] = WTK_PIN_CONFIG(gpio_28, 0x80, 22, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_30] = WTK_PIN_CONFIG(gpio_30, 0x84, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_34] = WTK_PIN_CONFIG(gpio_34, 0x84, 5, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_35] = WTK_PIN_CONFIG(gpio_35, 0x84, 10, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_UW0_TX] = WTK_PIN_CONFIG(uw0_tx, 0x84, 15, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_UW0_WX] = WTK_PIN_CONFIG(uw0_wx, 0x84, 20, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_48] = WTK_PIN_CONFIG(gpio_48, 0x84, 25, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_49] = WTK_PIN_CONFIG(gpio_49, 0x88, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_52] = WTK_PIN_CONFIG(gpio_52, 0x88, 5, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1319D_ISO_GPIO_53] = WTK_PIN_CONFIG(gpio_53, 0x88, 10, 1, 2, 0, 3, 4, PADDWI_4_8),
};

static const stwuct wtd_pin_sconfig_desc wtd1319d_iso_sconfigs[] = {
	WTK_PIN_SCONFIG(gpio_40, 0x3c, 7, 3, 10, 3, 13, 3),
	WTK_PIN_SCONFIG(gpio_41, 0x3c, 20, 3, 23, 3, 26, 3),
	WTK_PIN_SCONFIG(gpio_42, 0x40, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(gpio_43, 0x40, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(gpio_44, 0x44, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(gpio_45, 0x44, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(emmc_data_0, 0x48, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(emmc_data_1, 0x48, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(emmc_data_2, 0x4c, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(emmc_data_3, 0x4c, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(emmc_data_4, 0x50, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(emmc_data_5, 0x50, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(emmc_data_6, 0x54, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(emmc_data_7, 0x54, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(emmc_dd_sb, 0x58, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(emmc_wst_n, 0x58, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(emmc_cmd, 0x5c, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(emmc_cwk, 0x5c, 17, 3, 20, 3, 23, 3),
	WTK_PIN_SCONFIG(gpio_80, 0x60, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(gpio_78, 0x60, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(gpio_79, 0x64, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(gpio_81, 0x64, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(hif_en, 0x74, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(hif_data, 0x74, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(gpio_33, 0x78, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(gpio_32, 0x78, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(hif_cwk, 0x7c, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(hif_wdy, 0x7c, 16, 3, 19, 3, 22, 3),
};

static const stwuct wtd_pinctww_desc wtd1319d_iso_pinctww_desc = {
	.pins = wtd1319d_iso_pins,
	.num_pins = AWWAY_SIZE(wtd1319d_iso_pins),
	.gwoups = wtd1319d_pin_gwoups,
	.num_gwoups = AWWAY_SIZE(wtd1319d_pin_gwoups),
	.functions = wtd1319d_pin_functions,
	.num_functions = AWWAY_SIZE(wtd1319d_pin_functions),
	.muxes = wtd1319d_iso_muxes,
	.num_muxes = AWWAY_SIZE(wtd1319d_iso_muxes),
	.configs = wtd1319d_iso_configs,
	.num_configs = AWWAY_SIZE(wtd1319d_iso_configs),
	.sconfigs = wtd1319d_iso_sconfigs,
	.num_sconfigs = AWWAY_SIZE(wtd1319d_iso_sconfigs),
};

static int wtd1319d_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn wtd_pinctww_pwobe(pdev, &wtd1319d_iso_pinctww_desc);
}

static const stwuct of_device_id wtd1319d_pinctww_of_match[] = {
	{ .compatibwe = "weawtek,wtd1319d-pinctww", },
	{},
};

static stwuct pwatfowm_dwivew wtd1319d_pinctww_dwivew = {
	.dwivew = {
		.name = "wtd1319d-pinctww",
		.of_match_tabwe = wtd1319d_pinctww_of_match,
	},
	.pwobe = wtd1319d_pinctww_pwobe,
};

static int __init wtd1319d_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wtd1319d_pinctww_dwivew);
}
awch_initcaww(wtd1319d_pinctww_init);

static void __exit wtd1319d_pinctww_exit(void)
{
	pwatfowm_dwivew_unwegistew(&wtd1319d_pinctww_dwivew);
}
moduwe_exit(wtd1319d_pinctww_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Weawtek Semiconductow Cowpowation");
MODUWE_DESCWIPTION("Weawtek DHC SoC WTD1319D pinctww dwivew");
