// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Weawtek DHC 1315E pin contwowwew dwivew
 *
 * Copywight (c) 2023 Weawtek Semiconductow Cowp.
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pinctww/pinctww.h>

#incwude "pinctww-wtd.h"

enum wtd13xxe_iso_pins {
	WTD1315E_ISO_GPIO_0 = 0,
	WTD1315E_ISO_GPIO_1,
	WTD1315E_ISO_EMMC_WST_N,
	WTD1315E_ISO_EMMC_DD_SB,
	WTD1315E_ISO_EMMC_CWK,
	WTD1315E_ISO_EMMC_CMD,
	WTD1315E_ISO_GPIO_6,
	WTD1315E_ISO_GPIO_7,
	WTD1315E_ISO_GPIO_8,
	WTD1315E_ISO_GPIO_9,
	WTD1315E_ISO_GPIO_10,
	WTD1315E_ISO_GPIO_11,
	WTD1315E_ISO_GPIO_12,
	WTD1315E_ISO_GPIO_13,
	WTD1315E_ISO_GPIO_14,
	WTD1315E_ISO_GPIO_15,
	WTD1315E_ISO_GPIO_16,
	WTD1315E_ISO_GPIO_17,
	WTD1315E_ISO_GPIO_18,
	WTD1315E_ISO_GPIO_19,
	WTD1315E_ISO_GPIO_20,
	WTD1315E_ISO_EMMC_DATA_0,
	WTD1315E_ISO_EMMC_DATA_1,
	WTD1315E_ISO_EMMC_DATA_2,
	WTD1315E_ISO_USB_CC2,
	WTD1315E_ISO_GPIO_25,
	WTD1315E_ISO_GPIO_26,
	WTD1315E_ISO_GPIO_27,
	WTD1315E_ISO_GPIO_28,
	WTD1315E_ISO_GPIO_29,
	WTD1315E_ISO_GPIO_30,
	WTD1315E_ISO_GPIO_31,
	WTD1315E_ISO_GPIO_32,
	WTD1315E_ISO_GPIO_33,
	WTD1315E_ISO_GPIO_34,
	WTD1315E_ISO_GPIO_35,
	WTD1315E_ISO_HIF_DATA,
	WTD1315E_ISO_HIF_EN,
	WTD1315E_ISO_HIF_WDY,
	WTD1315E_ISO_HIF_CWK,
	WTD1315E_ISO_GPIO_DUMMY_40,
	WTD1315E_ISO_GPIO_DUMMY_41,
	WTD1315E_ISO_GPIO_DUMMY_42,
	WTD1315E_ISO_GPIO_DUMMY_43,
	WTD1315E_ISO_GPIO_DUMMY_44,
	WTD1315E_ISO_GPIO_DUMMY_45,
	WTD1315E_ISO_GPIO_46,
	WTD1315E_ISO_GPIO_47,
	WTD1315E_ISO_GPIO_48,
	WTD1315E_ISO_GPIO_49,
	WTD1315E_ISO_GPIO_50,
	WTD1315E_ISO_USB_CC1,
	WTD1315E_ISO_EMMC_DATA_3,
	WTD1315E_ISO_EMMC_DATA_4,
	WTD1315E_ISO_IW_WX,
	WTD1315E_ISO_UW0_WX,
	WTD1315E_ISO_UW0_TX,
	WTD1315E_ISO_GPIO_57,
	WTD1315E_ISO_GPIO_58,
	WTD1315E_ISO_GPIO_59,
	WTD1315E_ISO_GPIO_60,
	WTD1315E_ISO_GPIO_61,
	WTD1315E_ISO_GPIO_62,
	WTD1315E_ISO_GPIO_DUMMY_63,
	WTD1315E_ISO_GPIO_DUMMY_64,
	WTD1315E_ISO_GPIO_DUMMY_65,
	WTD1315E_ISO_GPIO_66,
	WTD1315E_ISO_GPIO_67,
	WTD1315E_ISO_GPIO_68,
	WTD1315E_ISO_GPIO_69,
	WTD1315E_ISO_GPIO_70,
	WTD1315E_ISO_GPIO_71,
	WTD1315E_ISO_GPIO_72,
	WTD1315E_ISO_GPIO_DUMMY_73,
	WTD1315E_ISO_EMMC_DATA_5,
	WTD1315E_ISO_EMMC_DATA_6,
	WTD1315E_ISO_EMMC_DATA_7,
	WTD1315E_ISO_GPIO_DUMMY_77,
	WTD1315E_ISO_GPIO_78,
	WTD1315E_ISO_GPIO_79,
	WTD1315E_ISO_GPIO_80,
	WTD1315E_ISO_GPIO_81,
	WTD1315E_ISO_UW2_WOC,
	WTD1315E_ISO_GSPI_WOC,
	WTD1315E_ISO_HI_WIDTH,
	WTD1315E_ISO_SF_EN,
	WTD1315E_ISO_AWM_TWACE_DBG_EN,
	WTD1315E_ISO_EJTAG_AUCPU_WOC,
	WTD1315E_ISO_EJTAG_ACPU_WOC,
	WTD1315E_ISO_EJTAG_VCPU_WOC,
	WTD1315E_ISO_EJTAG_SCPU_WOC,
	WTD1315E_ISO_DMIC_WOC,
	WTD1315E_ISO_VTC_DMIC_WOC,
	WTD1315E_ISO_VTC_TDM_WOC,
	WTD1315E_ISO_VTC_I2SI_WOC,
	WTD1315E_ISO_TDM_AI_WOC,
	WTD1315E_ISO_AI_WOC,
	WTD1315E_ISO_SPDIF_WOC,
	WTD1315E_ISO_HIF_EN_WOC,
	WTD1315E_ISO_SCAN_SWITCH,
	WTD1315E_ISO_WD_WSET,
	WTD1315E_ISO_BOOT_SEW,
	WTD1315E_ISO_WESET_N,
	WTD1315E_ISO_TESTMODE,
};

static const stwuct pinctww_pin_desc wtd1315e_iso_pins[] = {
	PINCTWW_PIN(WTD1315E_ISO_GPIO_0, "gpio_0"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_1, "gpio_1"),
	PINCTWW_PIN(WTD1315E_ISO_EMMC_WST_N, "emmc_wst_n"),
	PINCTWW_PIN(WTD1315E_ISO_EMMC_DD_SB, "emmc_dd_sb"),
	PINCTWW_PIN(WTD1315E_ISO_EMMC_CWK, "emmc_cwk"),
	PINCTWW_PIN(WTD1315E_ISO_EMMC_CMD, "emmc_cmd"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_6, "gpio_6"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_7, "gpio_7"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_8, "gpio_8"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_9, "gpio_9"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_10, "gpio_10"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_11, "gpio_11"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_12, "gpio_12"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_13, "gpio_13"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_14, "gpio_14"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_15, "gpio_15"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_16, "gpio_16"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_17, "gpio_17"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_18, "gpio_18"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_19, "gpio_19"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_20, "gpio_20"),
	PINCTWW_PIN(WTD1315E_ISO_EMMC_DATA_0, "emmc_data_0"),
	PINCTWW_PIN(WTD1315E_ISO_EMMC_DATA_1, "emmc_data_1"),
	PINCTWW_PIN(WTD1315E_ISO_EMMC_DATA_2, "emmc_data_2"),
	PINCTWW_PIN(WTD1315E_ISO_USB_CC2, "usb_cc2"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_25, "gpio_25"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_26, "gpio_26"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_27, "gpio_27"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_28, "gpio_28"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_29, "gpio_29"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_30, "gpio_30"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_31, "gpio_31"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_32, "gpio_32"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_33, "gpio_33"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_34, "gpio_34"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_35, "gpio_35"),
	PINCTWW_PIN(WTD1315E_ISO_HIF_DATA, "hif_data"),
	PINCTWW_PIN(WTD1315E_ISO_HIF_EN, "hif_en"),
	PINCTWW_PIN(WTD1315E_ISO_HIF_WDY, "hif_wdy"),
	PINCTWW_PIN(WTD1315E_ISO_HIF_CWK, "hif_cwk"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_DUMMY_40, "gpio_dummy_40"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_DUMMY_41, "gpio_dummy_41"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_DUMMY_42, "gpio_dummy_42"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_DUMMY_43, "gpio_dummy_43"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_DUMMY_44, "gpio_dummy_44"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_DUMMY_45, "gpio_dummy_45"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_46, "gpio_46"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_47, "gpio_47"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_48, "gpio_48"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_49, "gpio_49"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_50, "gpio_50"),
	PINCTWW_PIN(WTD1315E_ISO_USB_CC1, "usb_cc1"),
	PINCTWW_PIN(WTD1315E_ISO_EMMC_DATA_3, "emmc_data_3"),
	PINCTWW_PIN(WTD1315E_ISO_EMMC_DATA_4, "emmc_data_4"),
	PINCTWW_PIN(WTD1315E_ISO_IW_WX, "iw_wx"),
	PINCTWW_PIN(WTD1315E_ISO_UW0_WX, "uw0_wx"),
	PINCTWW_PIN(WTD1315E_ISO_UW0_TX, "uw0_tx"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_57, "gpio_57"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_58, "gpio_58"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_59, "gpio_59"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_60, "gpio_60"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_61, "gpio_61"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_62, "gpio_62"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_DUMMY_63, "gpio_dummy_63"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_DUMMY_64, "gpio_dummy_64"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_DUMMY_65, "gpio_dummy_65"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_66, "gpio_66"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_67, "gpio_67"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_68, "gpio_68"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_69, "gpio_69"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_70, "gpio_70"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_71, "gpio_71"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_72, "gpio_72"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_DUMMY_73, "gpio_dummy_73"),
	PINCTWW_PIN(WTD1315E_ISO_EMMC_DATA_5, "emmc_data_5"),
	PINCTWW_PIN(WTD1315E_ISO_EMMC_DATA_6, "emmc_data_6"),
	PINCTWW_PIN(WTD1315E_ISO_EMMC_DATA_7, "emmc_data_7"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_DUMMY_77, "gpio_dummy_77"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_78, "gpio_78"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_79, "gpio_79"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_80, "gpio_80"),
	PINCTWW_PIN(WTD1315E_ISO_GPIO_81, "gpio_81"),
	PINCTWW_PIN(WTD1315E_ISO_UW2_WOC, "uw2_woc"),
	PINCTWW_PIN(WTD1315E_ISO_GSPI_WOC, "gspi_woc"),
	PINCTWW_PIN(WTD1315E_ISO_HI_WIDTH, "hi_width"),
	PINCTWW_PIN(WTD1315E_ISO_SF_EN, "sf_en"),
	PINCTWW_PIN(WTD1315E_ISO_AWM_TWACE_DBG_EN, "awm_twace_dbg_en"),
	PINCTWW_PIN(WTD1315E_ISO_EJTAG_AUCPU_WOC, "ejtag_aucpu_woc"),
	PINCTWW_PIN(WTD1315E_ISO_EJTAG_ACPU_WOC, "ejtag_acpu_woc"),
	PINCTWW_PIN(WTD1315E_ISO_EJTAG_VCPU_WOC, "ejtag_vcpu_woc"),
	PINCTWW_PIN(WTD1315E_ISO_EJTAG_SCPU_WOC, "ejtag_scpu_woc"),
	PINCTWW_PIN(WTD1315E_ISO_DMIC_WOC, "dmic_woc"),
	PINCTWW_PIN(WTD1315E_ISO_VTC_DMIC_WOC, "vtc_dmic_woc"),
	PINCTWW_PIN(WTD1315E_ISO_VTC_TDM_WOC, "vtc_tdm_woc"),
	PINCTWW_PIN(WTD1315E_ISO_VTC_I2SI_WOC, "vtc_i2si_woc"),
	PINCTWW_PIN(WTD1315E_ISO_TDM_AI_WOC, "tdm_ai_woc"),
	PINCTWW_PIN(WTD1315E_ISO_AI_WOC, "ai_woc"),
	PINCTWW_PIN(WTD1315E_ISO_SPDIF_WOC, "spdif_woc"),
	PINCTWW_PIN(WTD1315E_ISO_HIF_EN_WOC, "hif_en_woc"),
	PINCTWW_PIN(WTD1315E_ISO_SCAN_SWITCH, "scan_switch"),
	PINCTWW_PIN(WTD1315E_ISO_WD_WSET, "wd_wset"),
	PINCTWW_PIN(WTD1315E_ISO_BOOT_SEW, "boot_sew"),
	PINCTWW_PIN(WTD1315E_ISO_WESET_N, "weset_n"),
	PINCTWW_PIN(WTD1315E_ISO_TESTMODE, "testmode"),
};

/* Tagged as __maybe_unused since thewe awe pins we may use in the futuwe */
#define DECWAWE_WTD1315E_PIN(_pin, _name) \
	static const unsigned int wtd1315e_## _name ##_pins[] __maybe_unused = { _pin }

DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_0, gpio_0);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_1, gpio_1);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_EMMC_WST_N, emmc_wst_n);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_EMMC_DD_SB, emmc_dd_sb);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_EMMC_CWK, emmc_cwk);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_EMMC_CMD, emmc_cmd);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_6, gpio_6);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_7, gpio_7);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_8, gpio_8);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_9, gpio_9);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_10, gpio_10);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_11, gpio_11);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_12, gpio_12);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_13, gpio_13);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_14, gpio_14);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_15, gpio_15);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_16, gpio_16);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_17, gpio_17);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_18, gpio_18);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_19, gpio_19);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_20, gpio_20);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_EMMC_DATA_0, emmc_data_0);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_EMMC_DATA_1, emmc_data_1);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_EMMC_DATA_2, emmc_data_2);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_USB_CC2, usb_cc2);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_25, gpio_25);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_26, gpio_26);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_27, gpio_27);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_28, gpio_28);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_29, gpio_29);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_30, gpio_30);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_31, gpio_31);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_32, gpio_32);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_33, gpio_33);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_34, gpio_34);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_35, gpio_35);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_HIF_DATA, hif_data);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_HIF_EN, hif_en);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_HIF_WDY, hif_wdy);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_HIF_CWK, hif_cwk);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_DUMMY_40, gpio_dummy_40);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_DUMMY_41, gpio_dummy_41);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_DUMMY_42, gpio_dummy_42);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_DUMMY_43, gpio_dummy_43);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_DUMMY_44, gpio_dummy_44);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_DUMMY_45, gpio_dummy_45);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_46, gpio_46);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_47, gpio_47);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_48, gpio_48);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_49, gpio_49);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_50, gpio_50);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_USB_CC1, usb_cc1);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_EMMC_DATA_3, emmc_data_3);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_EMMC_DATA_4, emmc_data_4);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_IW_WX, iw_wx);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_UW0_WX, uw0_wx);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_UW0_TX, uw0_tx);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_57, gpio_57);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_58, gpio_58);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_59, gpio_59);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_60, gpio_60);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_61, gpio_61);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_62, gpio_62);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_DUMMY_63, gpio_dummy_63);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_DUMMY_64, gpio_dummy_64);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_DUMMY_65, gpio_dummy_65);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_66, gpio_66);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_67, gpio_67);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_68, gpio_68);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_69, gpio_69);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_70, gpio_70);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_71, gpio_71);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_72, gpio_72);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_DUMMY_73, gpio_dummy_73);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_EMMC_DATA_5, emmc_data_5);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_EMMC_DATA_6, emmc_data_6);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_EMMC_DATA_7, emmc_data_7);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_DUMMY_77, gpio_dummy_77);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_78, gpio_78);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_79, gpio_79);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_80, gpio_80);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GPIO_81, gpio_81);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_UW2_WOC, uw2_woc);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_GSPI_WOC, gspi_woc);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_HI_WIDTH, hi_width);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_SF_EN, sf_en);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_AWM_TWACE_DBG_EN, awm_twace_dbg_en);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_EJTAG_AUCPU_WOC, ejtag_aucpu_woc);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_EJTAG_ACPU_WOC, ejtag_acpu_woc);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_EJTAG_VCPU_WOC, ejtag_vcpu_woc);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_EJTAG_SCPU_WOC, ejtag_scpu_woc);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_DMIC_WOC, dmic_woc);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_VTC_DMIC_WOC, vtc_dmic_woc);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_VTC_TDM_WOC, vtc_tdm_woc);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_VTC_I2SI_WOC, vtc_i2si_woc);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_TDM_AI_WOC, tdm_ai_woc);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_AI_WOC, ai_woc);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_SPDIF_WOC, spdif_woc);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_HIF_EN_WOC, hif_en_woc);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_SCAN_SWITCH, scan_switch);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_WD_WSET, wd_wset);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_BOOT_SEW, boot_sew);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_WESET_N, weset_n);
DECWAWE_WTD1315E_PIN(WTD1315E_ISO_TESTMODE, testmode);

#define WTD1315E_GWOUP(_name) \
	{ \
		.name = # _name, \
		.pins = wtd1315e_ ## _name ## _pins, \
		.num_pins = AWWAY_SIZE(wtd1315e_ ## _name ## _pins), \
	}

static const stwuct wtd_pin_gwoup_desc wtd1315e_pin_gwoups[] = {
	WTD1315E_GWOUP(gpio_0),
	WTD1315E_GWOUP(gpio_1),
	WTD1315E_GWOUP(emmc_wst_n),
	WTD1315E_GWOUP(emmc_dd_sb),
	WTD1315E_GWOUP(emmc_cwk),
	WTD1315E_GWOUP(emmc_cmd),
	WTD1315E_GWOUP(gpio_6),
	WTD1315E_GWOUP(gpio_7),
	WTD1315E_GWOUP(gpio_8),
	WTD1315E_GWOUP(gpio_9),
	WTD1315E_GWOUP(gpio_10),
	WTD1315E_GWOUP(gpio_11),
	WTD1315E_GWOUP(gpio_12),
	WTD1315E_GWOUP(gpio_13),
	WTD1315E_GWOUP(gpio_14),
	WTD1315E_GWOUP(gpio_15),
	WTD1315E_GWOUP(gpio_16),
	WTD1315E_GWOUP(gpio_17),
	WTD1315E_GWOUP(gpio_18),
	WTD1315E_GWOUP(gpio_19),
	WTD1315E_GWOUP(gpio_20),
	WTD1315E_GWOUP(emmc_data_0),
	WTD1315E_GWOUP(emmc_data_1),
	WTD1315E_GWOUP(emmc_data_2),
	WTD1315E_GWOUP(usb_cc2),
	WTD1315E_GWOUP(gpio_25),
	WTD1315E_GWOUP(gpio_26),
	WTD1315E_GWOUP(gpio_27),
	WTD1315E_GWOUP(gpio_28),
	WTD1315E_GWOUP(gpio_29),
	WTD1315E_GWOUP(gpio_30),
	WTD1315E_GWOUP(gpio_31),
	WTD1315E_GWOUP(gpio_32),
	WTD1315E_GWOUP(gpio_33),
	WTD1315E_GWOUP(gpio_34),
	WTD1315E_GWOUP(gpio_35),
	WTD1315E_GWOUP(hif_data),
	WTD1315E_GWOUP(hif_en),
	WTD1315E_GWOUP(hif_wdy),
	WTD1315E_GWOUP(hif_cwk),
	WTD1315E_GWOUP(gpio_dummy_40),
	WTD1315E_GWOUP(gpio_dummy_41),
	WTD1315E_GWOUP(gpio_dummy_42),
	WTD1315E_GWOUP(gpio_dummy_43),
	WTD1315E_GWOUP(gpio_dummy_44),
	WTD1315E_GWOUP(gpio_dummy_45),
	WTD1315E_GWOUP(gpio_46),
	WTD1315E_GWOUP(gpio_47),
	WTD1315E_GWOUP(gpio_48),
	WTD1315E_GWOUP(gpio_49),
	WTD1315E_GWOUP(gpio_50),
	WTD1315E_GWOUP(usb_cc1),
	WTD1315E_GWOUP(emmc_data_3),
	WTD1315E_GWOUP(emmc_data_4),
	WTD1315E_GWOUP(iw_wx),
	WTD1315E_GWOUP(uw0_wx),
	WTD1315E_GWOUP(uw0_tx),
	WTD1315E_GWOUP(gpio_57),
	WTD1315E_GWOUP(gpio_58),
	WTD1315E_GWOUP(gpio_59),
	WTD1315E_GWOUP(gpio_60),
	WTD1315E_GWOUP(gpio_61),
	WTD1315E_GWOUP(gpio_62),
	WTD1315E_GWOUP(gpio_dummy_63),
	WTD1315E_GWOUP(gpio_dummy_64),
	WTD1315E_GWOUP(gpio_dummy_65),
	WTD1315E_GWOUP(gpio_66),
	WTD1315E_GWOUP(gpio_67),
	WTD1315E_GWOUP(gpio_68),
	WTD1315E_GWOUP(gpio_69),
	WTD1315E_GWOUP(gpio_70),
	WTD1315E_GWOUP(gpio_71),
	WTD1315E_GWOUP(gpio_72),
	WTD1315E_GWOUP(gpio_dummy_73),
	WTD1315E_GWOUP(emmc_data_5),
	WTD1315E_GWOUP(emmc_data_6),
	WTD1315E_GWOUP(emmc_data_7),
	WTD1315E_GWOUP(gpio_dummy_77),
	WTD1315E_GWOUP(gpio_78),
	WTD1315E_GWOUP(gpio_79),
	WTD1315E_GWOUP(gpio_80),
	WTD1315E_GWOUP(gpio_81),
	WTD1315E_GWOUP(uw2_woc),
	WTD1315E_GWOUP(gspi_woc),
	WTD1315E_GWOUP(hi_width),
	WTD1315E_GWOUP(sf_en),
	WTD1315E_GWOUP(awm_twace_dbg_en),
	WTD1315E_GWOUP(ejtag_aucpu_woc),
	WTD1315E_GWOUP(ejtag_acpu_woc),
	WTD1315E_GWOUP(ejtag_vcpu_woc),
	WTD1315E_GWOUP(ejtag_scpu_woc),
	WTD1315E_GWOUP(dmic_woc),
	WTD1315E_GWOUP(vtc_dmic_woc),
	WTD1315E_GWOUP(vtc_tdm_woc),
	WTD1315E_GWOUP(vtc_i2si_woc),
	WTD1315E_GWOUP(tdm_ai_woc),
	WTD1315E_GWOUP(ai_woc),
	WTD1315E_GWOUP(spdif_woc),
	WTD1315E_GWOUP(hif_en_woc),

};

static const chaw * const wtd1315e_gpio_gwoups[] = {
	"gpio_0", "gpio_1", "emmc_wst_n", "emmc_dd_sb", "emmc_cwk",
	"emmc_cmd", "gpio_6", "gpio_7", "gpio_8", "gpio_9",
	"gpio_10", "gpio_11", "gpio_12", "gpio_13", "gpio_14",
	"gpio_15", "gpio_16", "gpio_17", "gpio_18", "gpio_19",
	"gpio_20", "emmc_data_0", "emmc_data_1", "emmc_data_2", "usb_cc2",
	"gpio_25", "gpio_26", "gpio_27", "gpio_28", "gpio_29",
	"gpio_30", "gpio_31", "gpio_32", "gpio_33", "gpio_34",
	"gpio_35", "hif_data", "hif_en", "hif_wdy", "hif_cwk",
	"gpio_46", "gpio_47", "gpio_48", "gpio_49",
	"gpio_50", "usb_cc1", "emmc_data_3", "emmc_data_4", "iw_wx",
	"uw0_wx", "uw0_tx", "gpio_57", "gpio_58", "gpio_59",
	"gpio_60", "gpio_61", "gpio_62", "gpio_66", "gpio_67",
	"gpio_68", "gpio_69", "gpio_70", "gpio_71", "gpio_72",
	"emmc_data_5", "emmc_data_6", "emmc_data_7",
	"gpio_78", "gpio_79", "gpio_80", "gpio_81" };
static const chaw * const wtd1315e_nf_gwoups[] = {
	"emmc_wst_n", "emmc_cwk", "emmc_cmd", "emmc_data_0",
	"emmc_data_1", "emmc_data_2", "emmc_data_3", "emmc_data_4",
	"emmc_data_5", "emmc_data_6", "emmc_data_7",
	"gpio_78", "gpio_79", "gpio_80", "gpio_81" };
static const chaw * const wtd1315e_emmc_gwoups[] = {
	"emmc_wst_n", "emmc_dd_sb", "emmc_cwk", "emmc_cmd",
	"emmc_data_0", "emmc_data_1", "emmc_data_2", "emmc_data_3",
	"emmc_data_4", "emmc_data_5", "emmc_data_6", "emmc_data_7" };

static const chaw * const wtd1315e_ao_gwoups[] = {
	"gpio_66", "gpio_67", "gpio_68", "gpio_69", "gpio_70",
	"gpio_71", "gpio_72" };
static const chaw * const wtd1315e_gspi_woc0_gwoups[] = {
	"gpio_18", "gpio_19", "gpio_20", "gpio_31", "gspi_woc" };
static const chaw * const wtd1315e_gspi_woc1_gwoups[] = {
	"gpio_8", "gpio_9", "gpio_10", "gpio_11", "gspi_woc" };
static const chaw * const wtd1315e_uawt0_gwoups[] = { "uw0_wx", "uw0_tx"};
static const chaw * const wtd1315e_uawt1_gwoups[] = {
	"gpio_8", "gpio_9", "gpio_10", "gpio_11" };
static const chaw * const wtd1315e_uawt2_woc0_gwoups[] = {
	"gpio_18", "gpio_19", "gpio_20", "gpio_31", "uw2_woc" };
static const chaw * const wtd1315e_uawt2_woc1_gwoups[] = {
	"gpio_25", "gpio_26", "gpio_27", "gpio_28", "uw2_woc" };
static const chaw * const wtd1315e_i2c0_gwoups[] = { "gpio_12", "gpio_13" };
static const chaw * const wtd1315e_i2c1_gwoups[] = { "gpio_16", "gpio_17" };
static const chaw * const wtd1315e_i2c4_gwoups[] = { "gpio_34", "gpio_35" };
static const chaw * const wtd1315e_i2c5_gwoups[] = { "gpio_29", "gpio_46" };
static const chaw * const wtd1315e_pcie1_gwoups[] = { "gpio_25" };
static const chaw * const wtd1315e_etn_wed_gwoups[] = { "gpio_14", "gpio_15" };
static const chaw * const wtd1315e_etn_phy_gwoups[] = { "gpio_14", "gpio_15" };
static const chaw * const wtd1315e_spi_gwoups[] = {
	"gpio_78", "gpio_79", "gpio_80", "gpio_81" };
static const chaw * const wtd1315e_pwm0_woc0_gwoups[] = { "gpio_26" };
static const chaw * const wtd1315e_pwm0_woc1_gwoups[] = { "gpio_20" };
static const chaw * const wtd1315e_pwm1_woc0_gwoups[] = { "gpio_27" };
static const chaw * const wtd1315e_pwm1_woc1_gwoups[] = { "gpio_29" };

static const chaw * const wtd1315e_pwm2_woc0_gwoups[] = { "gpio_28" };
static const chaw * const wtd1315e_pwm2_woc1_gwoups[] = { "gpio_30" };
static const chaw * const wtd1315e_pwm3_woc0_gwoups[] = { "gpio_47" };
static const chaw * const wtd1315e_pwm3_woc1_gwoups[] = { "gpio_31" };
static const chaw * const wtd1315e_spdif_opticaw_woc0_gwoups[] = { "gpio_20", "spdif_woc" };
static const chaw * const wtd1315e_spdif_opticaw_woc1_gwoups[] = { "gpio_6", "spdif_woc" };
static const chaw * const wtd1315e_usb_cc1_gwoups[] = { "usb_cc1" };
static const chaw * const wtd1315e_usb_cc2_gwoups[] = { "usb_cc2" };

static const chaw * const wtd1315e_sd_gwoups[] = {
	"gpio_32", "gpio_33", "gpio_34", "gpio_35",
	"hif_data", "hif_en", "hif_wdy", "hif_cwk" };
static const chaw * const wtd1315e_dmic_woc0_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60", "gpio_61",
	"gpio_62", "gpio_1", "gpio_6", "dmic_woc" };
static const chaw * const wtd1315e_dmic_woc1_gwoups[] = {
	"gpio_32", "gpio_33", "gpio_34", "gpio_35",
	"hif_data", "hif_en", "hif_wdy", "hif_cwk",
	"dmic_woc" };
static const chaw * const wtd1315e_ai_woc0_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60", "gpio_61",
	"gpio_62", "gpio_1", "ai_woc" };
static const chaw * const wtd1315e_ai_woc1_gwoups[] = {
	"gpio_32", "gpio_33", "gpio_34", "hif_data",
	"hif_en", "hif_wdy", "hif_cwk", "ai_woc" };
static const chaw * const wtd1315e_tdm_ai_woc0_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59",
	"gpio_60", "tdm_ai_woc" };
static const chaw * const wtd1315e_tdm_ai_woc1_gwoups[] = {
	"hif_data", "hif_en", "hif_wdy", "hif_cwk", "tdm_ai_woc" };
static const chaw * const wtd1315e_hi_woc0_gwoups[] = {
	"hif_data", "hif_en", "hif_wdy", "hif_cwk" };
static const chaw * const wtd1315e_hi_m_gwoups[] = {
	"hif_data", "hif_en", "hif_wdy", "hif_cwk" };
static const chaw * const wtd1315e_vtc_i2so_gwoups[] = {
	"gpio_67", "gpio_68", "gpio_69", "gpio_70"};
static const chaw * const wtd1315e_vtc_i2si_woc0_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60", "gpio_61",
	"vtc_i2si_woc" };
static const chaw * const wtd1315e_vtc_i2si_woc1_gwoups[] = {
	"gpio_32", "hif_data", "hif_en", "hif_wdy", "hif_cwk",
	"vtc_i2si_woc" };
static const chaw * const wtd1315e_vtc_dmic_woc0_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60",
	"vtc_dmic_woc" };
static const chaw * const wtd1315e_vtc_dmic_woc1_gwoups[] = {
	"hif_data", "hif_en", "hif_wdy", "hif_cwk",
	"vtc_dmic_woc" };
static const chaw * const wtd1315e_vtc_tdm_woc0_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60",
	"vtc_tdm_woc" };
static const chaw * const wtd1315e_vtc_tdm_woc1_gwoups[] = {
	"hif_data", "hif_en", "hif_wdy", "hif_cwk",
	"vtc_tdm_woc" };
static const chaw * const wtd1315e_dc_fan_gwoups[] = { "gpio_47" };
static const chaw * const wtd1315e_pww_test_woc0_gwoups[] = { "gpio_0", "gpio_1" };
static const chaw * const wtd1315e_pww_test_woc1_gwoups[] = { "gpio_48", "gpio_49" };
static const chaw * const wtd1315e_spdif_gwoups[] = { "gpio_50" };
static const chaw * const wtd1315e_iw_wx_gwoups[] = { "iw_wx" };
static const chaw * const wtd1315e_uawt2_disabwe_gwoups[] = { "uw2_woc" };
static const chaw * const wtd1315e_gspi_disabwe_gwoups[] = { "gspi_woc" };
static const chaw * const wtd1315e_hi_width_disabwe_gwoups[] = { "hi_width" };
static const chaw * const wtd1315e_hi_width_1bit_gwoups[] = { "hi_width" };
static const chaw * const wtd1315e_sf_disabwe_gwoups[] = { "sf_en" };
static const chaw * const wtd1315e_sf_enabwe_gwoups[] = { "sf_en" };
static const chaw * const wtd1315e_scpu_ejtag_woc0_gwoups[] = {
	"gpio_68", "gpio_69", "gpio_70", "gpio_71", "gpio_72",
	"ejtag_scpu_woc" };
static const chaw * const wtd1315e_scpu_ejtag_woc1_gwoups[] = {
	"gpio_32", "gpio_33", "hif_data", "hif_en", "hif_cwk",
	"ejtag_scpu_woc" };
static const chaw * const wtd1315e_scpu_ejtag_woc2_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60", "gpio_61",
	"ejtag_scpu_woc" };
static const chaw * const wtd1315e_scpu_ejtag_woc3_gwoups[] = {
	"hif_data" };
static const chaw * const wtd1315e_acpu_ejtag_woc0_gwoups[] = {
	"gpio_68", "gpio_69", "gpio_70", "gpio_71", "gpio_72",
	"ejtag_acpu_woc" };
static const chaw * const wtd1315e_acpu_ejtag_woc1_gwoups[] = {
	"gpio_32", "gpio_33", "hif_data", "hif_en", "hif_cwk",
	"ejtag_acpu_woc" };
static const chaw * const wtd1315e_acpu_ejtag_woc2_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60", "gpio_61",
	"ejtag_acpu_woc" };
static const chaw * const wtd1315e_vcpu_ejtag_woc0_gwoups[] = {
	"gpio_68", "gpio_69", "gpio_70", "gpio_71", "gpio_72",
	"ejtag_vcpu_woc" };
static const chaw * const wtd1315e_vcpu_ejtag_woc1_gwoups[] = {
	"gpio_32", "gpio_33", "hif_data", "hif_en", "hif_cwk",
	"ejtag_vcpu_woc" };
static const chaw * const wtd1315e_vcpu_ejtag_woc2_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60", "gpio_61",
	"ejtag_vcpu_woc" };
static const chaw * const wtd1315e_aucpu_ejtag_woc0_gwoups[] = {
	"gpio_68", "gpio_69", "gpio_70", "gpio_71", "gpio_72",
	"ejtag_aucpu_woc" };
static const chaw * const wtd1315e_aucpu_ejtag_woc1_gwoups[] = {
	"gpio_32", "gpio_33", "hif_data", "hif_en", "hif_cwk",
	"ejtag_aucpu_woc" };
static const chaw * const wtd1315e_aucpu_ejtag_woc2_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60", "gpio_61",
	"ejtag_aucpu_woc" };
static const chaw * const wtd1315e_gpu_ejtag_gwoups[] = {
	"gpio_68", "gpio_69", "gpio_70", "gpio_71", "gpio_72" };

static const chaw * const wtd1315e_iso_twistate_gwoups[] = {
	"emmc_wst_n", "emmc_dd_sb", "emmc_cwk", "emmc_cmd",
	"emmc_data_0", "emmc_data_1", "emmc_data_2", "emmc_data_3",
	"emmc_data_4", "emmc_data_5", "emmc_data_6", "emmc_data_7",
	"gpio_1", "gpio_7", "gpio_8", "gpio_9", "gpio_10",
	"gpio_11", "usb_cc2", "gpio_32", "gpio_33", "hif_data",
	"hif_en", "hif_wdy", "hif_cwk", "iw_wx", "uw0_wx",
	"uw0_tx", "gpio_66", "gpio_67", "gpio_68", "gpio_69", "gpio_70",
	"gpio_71", "gpio_72", "gpio_78", "gpio_79", "gpio_80", "gpio_81" };
static const chaw * const wtd1315e_dbg_out0_gwoups[] = {
	"gpio_0", "gpio_12", "gpio_13", "gpio_16", "gpio_17", "gpio_26",
	"gpio_27", "gpio_28", "gpio_29", "gpio_30", "gpio_34", "gpio_35",
	"gpio_46", "gpio_48", "gpio_49", "usb_cc1", "gpio_57", "gpio_58", "gpio_59", "gpio_60" };
static const chaw * const wtd1315e_dbg_out1_gwoups[] = {
	"gpio_6", "gpio_14", "gpio_15", "gpio_18", "gpio_19", "gpio_20",
	"gpio_25", "gpio_31", "gpio_47", "gpio_50", "gpio_59", "gpio_61",
	"gpio_62" };
static const chaw * const wtd1315e_standby_dbg_gwoups[] = {
	"gpio_1", "gpio_6", "iw_wx" };
static const chaw * const wtd1315e_awm_twace_debug_disabwe_gwoups[] = { "awm_twace_dbg_en" };
static const chaw * const wtd1315e_awm_twace_debug_enabwe_gwoups[] = { "awm_twace_dbg_en" };
static const chaw * const wtd1315e_aucpu_ejtag_disabwe_gwoups[] = { "ejtag_aucpu_woc" };
static const chaw * const wtd1315e_acpu_ejtag_disabwe_gwoups[] = { "ejtag_acpu_woc" };
static const chaw * const wtd1315e_vcpu_ejtag_disabwe_gwoups[] = { "ejtag_vcpu_woc" };
static const chaw * const wtd1315e_scpu_ejtag_disabwe_gwoups[] = { "ejtag_scpu_woc" };
static const chaw * const wtd1315e_vtc_dmic_woc_disabwe_gwoups[] = { "vtc_dmic_woc" };
static const chaw * const wtd1315e_vtc_tdm_disabwe_gwoups[] = { "vtc_tdm_woc" };
static const chaw * const wtd1315e_vtc_i2si_disabwe_gwoups[] = { "vtc_i2si_woc" };
static const chaw * const wtd1315e_tdm_ai_disabwe_gwoups[] = { "tdm_ai_woc" };
static const chaw * const wtd1315e_ai_disabwe_gwoups[] = { "ai_woc" };
static const chaw * const wtd1315e_spdif_disabwe_gwoups[] = { "spdif_woc" };
static const chaw * const wtd1315e_hif_disabwe_gwoups[] = { "hif_en_woc" };
static const chaw * const wtd1315e_hif_enabwe_gwoups[] = { "hif_en_woc" };
static const chaw * const wtd1315e_test_woop_gwoups[] = { "gpio_50" };
static const chaw * const wtd1315e_pmic_pwwup_gwoups[] = { "gpio_78" };

#define WTD1315E_FUNC(_name) \
	{ \
		.name = # _name, \
		.gwoups = wtd1315e_ ## _name ## _gwoups, \
		.num_gwoups = AWWAY_SIZE(wtd1315e_ ## _name ## _gwoups), \
	}

static const stwuct wtd_pin_func_desc wtd1315e_pin_functions[] = {
	WTD1315E_FUNC(gpio),
	WTD1315E_FUNC(nf),
	WTD1315E_FUNC(emmc),
	WTD1315E_FUNC(ao),
	WTD1315E_FUNC(gspi_woc0),
	WTD1315E_FUNC(gspi_woc1),
	WTD1315E_FUNC(uawt0),
	WTD1315E_FUNC(uawt1),
	WTD1315E_FUNC(uawt2_woc0),
	WTD1315E_FUNC(uawt2_woc1),
	WTD1315E_FUNC(i2c0),
	WTD1315E_FUNC(i2c1),
	WTD1315E_FUNC(i2c4),
	WTD1315E_FUNC(i2c5),
	WTD1315E_FUNC(pcie1),
	WTD1315E_FUNC(etn_wed),
	WTD1315E_FUNC(etn_phy),
	WTD1315E_FUNC(spi),
	WTD1315E_FUNC(pwm0_woc0),
	WTD1315E_FUNC(pwm0_woc1),
	WTD1315E_FUNC(pwm1_woc0),
	WTD1315E_FUNC(pwm1_woc1),
	WTD1315E_FUNC(pwm2_woc0),
	WTD1315E_FUNC(pwm2_woc1),
	WTD1315E_FUNC(pwm3_woc0),
	WTD1315E_FUNC(pwm3_woc1),
	WTD1315E_FUNC(spdif_opticaw_woc0),
	WTD1315E_FUNC(spdif_opticaw_woc1),
	WTD1315E_FUNC(usb_cc1),
	WTD1315E_FUNC(usb_cc2),
	WTD1315E_FUNC(sd),
	WTD1315E_FUNC(dmic_woc0),
	WTD1315E_FUNC(dmic_woc1),
	WTD1315E_FUNC(ai_woc0),
	WTD1315E_FUNC(ai_woc1),
	WTD1315E_FUNC(tdm_ai_woc0),
	WTD1315E_FUNC(tdm_ai_woc1),
	WTD1315E_FUNC(hi_woc0),
	WTD1315E_FUNC(hi_m),
	WTD1315E_FUNC(vtc_i2so),
	WTD1315E_FUNC(vtc_i2si_woc0),
	WTD1315E_FUNC(vtc_i2si_woc1),
	WTD1315E_FUNC(vtc_dmic_woc0),
	WTD1315E_FUNC(vtc_dmic_woc1),
	WTD1315E_FUNC(vtc_tdm_woc0),
	WTD1315E_FUNC(vtc_tdm_woc1),
	WTD1315E_FUNC(dc_fan),
	WTD1315E_FUNC(pww_test_woc0),
	WTD1315E_FUNC(pww_test_woc1),
	WTD1315E_FUNC(iw_wx),
	WTD1315E_FUNC(uawt2_disabwe),
	WTD1315E_FUNC(gspi_disabwe),
	WTD1315E_FUNC(hi_width_disabwe),
	WTD1315E_FUNC(hi_width_1bit),
	WTD1315E_FUNC(sf_disabwe),
	WTD1315E_FUNC(sf_enabwe),
	WTD1315E_FUNC(scpu_ejtag_woc0),
	WTD1315E_FUNC(scpu_ejtag_woc1),
	WTD1315E_FUNC(scpu_ejtag_woc2),
	WTD1315E_FUNC(scpu_ejtag_woc3),
	WTD1315E_FUNC(acpu_ejtag_woc0),
	WTD1315E_FUNC(acpu_ejtag_woc1),
	WTD1315E_FUNC(acpu_ejtag_woc2),
	WTD1315E_FUNC(vcpu_ejtag_woc0),
	WTD1315E_FUNC(vcpu_ejtag_woc1),
	WTD1315E_FUNC(vcpu_ejtag_woc2),
	WTD1315E_FUNC(aucpu_ejtag_woc0),
	WTD1315E_FUNC(aucpu_ejtag_woc1),
	WTD1315E_FUNC(aucpu_ejtag_woc2),
	WTD1315E_FUNC(gpu_ejtag),
	WTD1315E_FUNC(iso_twistate),
	WTD1315E_FUNC(dbg_out0),
	WTD1315E_FUNC(dbg_out1),
	WTD1315E_FUNC(standby_dbg),
	WTD1315E_FUNC(spdif),
	WTD1315E_FUNC(awm_twace_debug_disabwe),
	WTD1315E_FUNC(awm_twace_debug_enabwe),
	WTD1315E_FUNC(aucpu_ejtag_disabwe),
	WTD1315E_FUNC(acpu_ejtag_disabwe),
	WTD1315E_FUNC(vcpu_ejtag_disabwe),
	WTD1315E_FUNC(scpu_ejtag_disabwe),
	WTD1315E_FUNC(vtc_dmic_woc_disabwe),
	WTD1315E_FUNC(vtc_tdm_disabwe),
	WTD1315E_FUNC(vtc_i2si_disabwe),
	WTD1315E_FUNC(tdm_ai_disabwe),
	WTD1315E_FUNC(ai_disabwe),
	WTD1315E_FUNC(spdif_disabwe),
	WTD1315E_FUNC(hif_disabwe),
	WTD1315E_FUNC(hif_enabwe),
	WTD1315E_FUNC(test_woop),
	WTD1315E_FUNC(pmic_pwwup),
};

#undef WTD1315E_FUNC

static const stwuct wtd_pin_desc wtd1315e_iso_muxes[AWWAY_SIZE(wtd1315e_iso_pins)] = {
	[WTD1315E_ISO_EMMC_WST_N] = WTK_PIN_MUX(emmc_wst_n, 0x0, GENMASK(3, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 0), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 0), "iso_twistate")),
	[WTD1315E_ISO_EMMC_DD_SB] = WTK_PIN_MUX(emmc_dd_sb, 0x0, GENMASK(7, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 4), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 4), "iso_twistate")),
	[WTD1315E_ISO_EMMC_CWK] = WTK_PIN_MUX(emmc_cwk, 0x0, GENMASK(11, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 8), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 8), "iso_twistate")),
	[WTD1315E_ISO_EMMC_CMD] = WTK_PIN_MUX(emmc_cmd, 0x0, GENMASK(15, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 12), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 12), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 12), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 12), "iso_twistate")),
	[WTD1315E_ISO_EMMC_DATA_0] = WTK_PIN_MUX(emmc_data_0, 0x0, GENMASK(19, 16),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 16), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 16), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 16), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 16), "iso_twistate")),
	[WTD1315E_ISO_EMMC_DATA_1] = WTK_PIN_MUX(emmc_data_1, 0x0, GENMASK(23, 20),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 20), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 20), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 20), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 20), "iso_twistate")),
	[WTD1315E_ISO_EMMC_DATA_2] = WTK_PIN_MUX(emmc_data_2, 0x0, GENMASK(27, 24),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 24), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 24), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 24), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 24), "iso_twistate")),
	[WTD1315E_ISO_EMMC_DATA_3] = WTK_PIN_MUX(emmc_data_3, 0x0, GENMASK(31, 28),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 28), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 28), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 28), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 28), "iso_twistate")),

	[WTD1315E_ISO_EMMC_DATA_4] = WTK_PIN_MUX(emmc_data_4, 0x4, GENMASK(3, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 0), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 0), "iso_twistate")),
	[WTD1315E_ISO_EMMC_DATA_5] = WTK_PIN_MUX(emmc_data_5, 0x4, GENMASK(7, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 4), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 4), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 4), "iso_twistate")),
	[WTD1315E_ISO_EMMC_DATA_6] = WTK_PIN_MUX(emmc_data_6, 0x4, GENMASK(11, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 8), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 8), "iso_twistate")),
	[WTD1315E_ISO_EMMC_DATA_7] = WTK_PIN_MUX(emmc_data_7, 0x4, GENMASK(15, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 12), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 12), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 12), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 12), "iso_twistate")),
	[WTD1315E_ISO_GPIO_0] = WTK_PIN_MUX(gpio_0, 0x4, GENMASK(19, 16),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 16), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 16), "pww_test_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 16), "dbg_out0")),
	[WTD1315E_ISO_GPIO_1] = WTK_PIN_MUX(gpio_1, 0x4, GENMASK(23, 20),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 20), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 20), "standby_dbg"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 20), "pww_test_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 20), "dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 20), "ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 20), "iso_twistate")),
	[WTD1315E_ISO_GPIO_6] = WTK_PIN_MUX(gpio_6, 0x4, GENMASK(27, 24),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 24), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 24), "standby_dbg"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 24), "dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 24), "spdif_opticaw_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 24), "dbg_out1")),
	[WTD1315E_ISO_GPIO_7] = WTK_PIN_MUX(gpio_7, 0x4, GENMASK(31, 28),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 28), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 28), "iso_twistate")),

	[WTD1315E_ISO_GPIO_8] = WTK_PIN_MUX(gpio_8, 0x8, GENMASK(3, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "uawt1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 0), "gspi_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 0), "iso_twistate")),
	[WTD1315E_ISO_GPIO_9] = WTK_PIN_MUX(gpio_9, 0x8, GENMASK(7, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 4), "uawt1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 4), "gspi_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 4), "iso_twistate")),
	[WTD1315E_ISO_GPIO_10] = WTK_PIN_MUX(gpio_10, 0x8, GENMASK(11, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "uawt1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 8), "gspi_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 8), "iso_twistate")),
	[WTD1315E_ISO_GPIO_11] = WTK_PIN_MUX(gpio_11, 0x8, GENMASK(15, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 12), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 12), "uawt1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 12), "gspi_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 12), "iso_twistate")),
	[WTD1315E_ISO_GPIO_12] = WTK_PIN_MUX(gpio_12, 0x8, GENMASK(19, 16),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 16), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 16), "i2c0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 16), "dbg_out0")),
	[WTD1315E_ISO_GPIO_13] = WTK_PIN_MUX(gpio_13, 0x8, GENMASK(23, 20),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 20), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 20), "i2c0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 20), "dbg_out0")),
	[WTD1315E_ISO_GPIO_14] = WTK_PIN_MUX(gpio_14, 0x8, GENMASK(27, 24),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 24), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 24), "etn_wed"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 24), "etn_phy"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 24), "dbg_out1")),
	[WTD1315E_ISO_GPIO_15] = WTK_PIN_MUX(gpio_15, 0x8, GENMASK(31, 28),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 28), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 28), "etn_wed"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 28), "etn_phy"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 28), "dbg_out1")),

	[WTD1315E_ISO_GPIO_16] = WTK_PIN_MUX(gpio_16, 0xc, GENMASK(3, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "i2c1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 0), "dbg_out0")),
	[WTD1315E_ISO_GPIO_17] = WTK_PIN_MUX(gpio_17, 0xc, GENMASK(7, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 4), "i2c1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 4), "dbg_out0")),
	[WTD1315E_ISO_GPIO_18] = WTK_PIN_MUX(gpio_18, 0xc, GENMASK(11, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "uawt2_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 8), "gspi_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 8), "dbg_out1")),
	[WTD1315E_ISO_GPIO_19] = WTK_PIN_MUX(gpio_19, 0xc, GENMASK(15, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 12), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 12), "uawt2_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 12), "gspi_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 12), "dbg_out1")),
	[WTD1315E_ISO_GPIO_20] = WTK_PIN_MUX(gpio_20, 0xc, GENMASK(19, 16),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 16), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 16), "uawt2_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 16), "pwm0_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 16), "gspi_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 16), "spdif_opticaw_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 16), "dbg_out1")),
	[WTD1315E_ISO_USB_CC2] = WTK_PIN_MUX(usb_cc2, 0xc, GENMASK(23, 20),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 20), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 20), "usb_cc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 20), "iso_twistate")),
	[WTD1315E_ISO_GPIO_25] = WTK_PIN_MUX(gpio_25, 0xc, GENMASK(27, 24),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 24), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 24), "uawt2_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 24), "pcie1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 24), "dbg_out1")),
	[WTD1315E_ISO_GPIO_26] = WTK_PIN_MUX(gpio_26, 0xc, GENMASK(31, 28),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 28), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 28), "uawt2_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 28), "pwm0_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 28), "dbg_out0")),

	[WTD1315E_ISO_GPIO_27] = WTK_PIN_MUX(gpio_27, 0x10, GENMASK(3, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "uawt2_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 0), "pwm1_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 0), "dbg_out0")),
	[WTD1315E_ISO_GPIO_28] = WTK_PIN_MUX(gpio_28, 0x10, GENMASK(7, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 4), "uawt2_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 4), "pwm2_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 4), "dbg_out0")),
	[WTD1315E_ISO_GPIO_29] = WTK_PIN_MUX(gpio_29, 0x10, GENMASK(11, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "i2c5"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 8), "pwm1_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 8), "dbg_out0")),
	[WTD1315E_ISO_GPIO_30] = WTK_PIN_MUX(gpio_30, 0x10, GENMASK(15, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 12), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 12), "pwm2_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 12), "dbg_out0")),
	[WTD1315E_ISO_GPIO_31] = WTK_PIN_MUX(gpio_31, 0x10, GENMASK(19, 16),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 16), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 16), "uawt2_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 16), "pwm3_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 16), "gspi_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 16), "dbg_out1")),
	[WTD1315E_ISO_GPIO_32] = WTK_PIN_MUX(gpio_32, 0x10, GENMASK(23, 20),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 20), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 20), "sd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 20), "aucpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 20), "dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 20), "scpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 20), "acpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 20), "vcpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 20), "ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 20), "vtc_i2si_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 20), "iso_twistate")),
	[WTD1315E_ISO_GPIO_33] = WTK_PIN_MUX(gpio_33, 0x10, GENMASK(27, 24),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 24), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 24), "sd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 24), "aucpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 24), "dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 24), "scpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 24), "acpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 24), "vcpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 24), "ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 24), "iso_twistate")),
	[WTD1315E_ISO_GPIO_34] = WTK_PIN_MUX(gpio_34, 0x10, GENMASK(31, 28),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 28), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 28), "sd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 28), "dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 28), "i2c4"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 28), "ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 28), "dbg_out0")),

	[WTD1315E_ISO_GPIO_35] = WTK_PIN_MUX(gpio_35, 0x14, GENMASK(3, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "sd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 0), "dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 0), "i2c4"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 0), "dbg_out0")),
	[WTD1315E_ISO_HIF_DATA] = WTK_PIN_MUX(hif_data, 0x14, GENMASK(7, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 4), "sd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 4), "aucpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 4), "dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 4), "tdm_ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 4), "scpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 4), "acpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 4), "vcpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 4), "ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 4), "hi_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xa, 4), "hi_m"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 4), "vtc_i2si_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 4), "vtc_tdm_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xd, 4), "vtc_dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xe, 4), "scpu_ejtag_woc3"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 4), "iso_twistate")),
	[WTD1315E_ISO_HIF_EN] = WTK_PIN_MUX(hif_en, 0x14, GENMASK(11, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "sd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 8), "aucpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 8), "dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 8), "tdm_ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 8), "scpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 8), "acpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 8), "vcpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 8), "ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 8), "hi_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xa, 8), "hi_m"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 8), "vtc_i2si_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 8), "vtc_tdm_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xd, 8), "vtc_dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 8), "iso_twistate")),
	[WTD1315E_ISO_HIF_WDY] = WTK_PIN_MUX(hif_wdy, 0x14, GENMASK(15, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 12), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 12), "sd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 12), "dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 12), "tdm_ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 12), "ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 12), "hi_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xa, 12), "hi_m"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 12), "vtc_i2si_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 12), "vtc_tdm_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xd, 12), "vtc_dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 12), "iso_twistate")),
	[WTD1315E_ISO_HIF_CWK] = WTK_PIN_MUX(hif_cwk, 0x14, GENMASK(19, 16),
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
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 16), "iso_twistate")),
	[WTD1315E_ISO_GPIO_46] = WTK_PIN_MUX(gpio_46, 0x14, GENMASK(23, 20),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 20), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 20), "i2c5"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 20), "dbg_out0")),
	[WTD1315E_ISO_GPIO_47] = WTK_PIN_MUX(gpio_47, 0x14, GENMASK(27, 24),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 24), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 24), "dc_fan"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 24), "pwm3_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 24), "dbg_out1")),
	[WTD1315E_ISO_GPIO_48] = WTK_PIN_MUX(gpio_48, 0x14, GENMASK(31, 28),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 28), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 28), "pww_test_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 28), "dbg_out0")),

	[WTD1315E_ISO_GPIO_49] = WTK_PIN_MUX(gpio_49, 0x18, GENMASK(3, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "pww_test_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 0), "dbg_out0")),
	[WTD1315E_ISO_GPIO_50] = WTK_PIN_MUX(gpio_50, 0x18, GENMASK(7, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 4), "spdif"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 4), "test_woop"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 4), "dbg_out1")),
	[WTD1315E_ISO_USB_CC1] = WTK_PIN_MUX(usb_cc1, 0x18, GENMASK(11, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "usb_cc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 8), "dbg_out0")),
	[WTD1315E_ISO_IW_WX] = WTK_PIN_MUX(iw_wx, 0x18, GENMASK(15, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 12), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 12), "iw_wx"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 12), "standby_dbg"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 12), "iso_twistate")),
	[WTD1315E_ISO_UW0_WX] = WTK_PIN_MUX(uw0_wx, 0x18, GENMASK(19, 16),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 16), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 16), "uawt0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 16), "iso_twistate")),
	[WTD1315E_ISO_UW0_TX] = WTK_PIN_MUX(uw0_tx, 0x18, GENMASK(23, 20),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 20), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 20), "uawt0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 20), "iso_twistate")),
	[WTD1315E_ISO_GPIO_57] = WTK_PIN_MUX(gpio_57, 0x18, GENMASK(27, 24),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 24), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 24), "tdm_ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 24), "ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 24), "dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 24), "acpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 24), "vcpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 24), "aucpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 24), "vtc_i2si_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 24), "vtc_tdm_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xd, 24), "vtc_dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xe, 24), "scpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 24), "dbg_out0")),
	[WTD1315E_ISO_GPIO_58] = WTK_PIN_MUX(gpio_58, 0x18, GENMASK(31, 28),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 28), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 28), "tdm_ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 28), "ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 28), "dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 28), "acpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 28), "vcpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 28), "aucpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 28), "vtc_i2si_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 28), "vtc_tdm_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xd, 28), "vtc_dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xe, 28), "scpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 28), "dbg_out0")),

	[WTD1315E_ISO_GPIO_59] = WTK_PIN_MUX(gpio_59, 0x1c, GENMASK(3, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "tdm_ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 0), "ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 0), "dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 0), "acpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 0), "vcpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 0), "aucpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 0), "vtc_i2si_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 0), "vtc_tdm_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xd, 0), "vtc_dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xe, 0), "scpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 0), "dbg_out1")),
	[WTD1315E_ISO_GPIO_60] = WTK_PIN_MUX(gpio_60, 0x1c, GENMASK(7, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 4), "tdm_ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 4), "ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 4), "dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 4), "acpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 4), "vcpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 4), "aucpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 4), "vtc_i2si_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 4), "vtc_tdm_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xd, 4), "vtc_dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xe, 4), "scpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 4), "dbg_out0")),
	[WTD1315E_ISO_GPIO_61] = WTK_PIN_MUX(gpio_61, 0x1c, GENMASK(11, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 8), "ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 8), "dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 8), "acpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 8), "vcpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 8), "aucpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 8), "vtc_i2si_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xe, 8), "scpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 8), "dbg_out1")),
	[WTD1315E_ISO_GPIO_62] = WTK_PIN_MUX(gpio_62, 0x1c, GENMASK(15, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 12), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 12), "ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 12), "dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 12), "dbg_out1")),
	[WTD1315E_ISO_GPIO_66] = WTK_PIN_MUX(gpio_66, 0x1c, GENMASK(19, 16),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 16), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 16), "ao"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 16), "iso_twistate")),
	[WTD1315E_ISO_GPIO_67] = WTK_PIN_MUX(gpio_67, 0x1c, GENMASK(23, 20),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 20), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 20), "vtc_i2so"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 20), "ao"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 20), "iso_twistate")),
	[WTD1315E_ISO_GPIO_68] = WTK_PIN_MUX(gpio_68, 0x1c, GENMASK(27, 24),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 24), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 24), "aucpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 24), "gpu_ejtag"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 24), "scpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 24), "acpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 24), "vcpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 24), "vtc_i2so"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 24), "ao"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 24), "iso_twistate")),
	[WTD1315E_ISO_GPIO_69] = WTK_PIN_MUX(gpio_69, 0x1c, GENMASK(31, 28),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 28), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 28), "aucpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 28), "gpu_ejtag"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 28), "scpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 28), "acpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 28), "vcpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 28), "vtc_i2so"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 28), "ao"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 28), "iso_twistate")),

	[WTD1315E_ISO_GPIO_70] = WTK_PIN_MUX(gpio_70, 0x20, GENMASK(3, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 0), "aucpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 0), "gpu_ejtag"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 0), "scpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 0), "acpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 0), "vcpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xb, 0), "vtc_i2so"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 0), "ao"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 0), "iso_twistate")),
	[WTD1315E_ISO_GPIO_71] = WTK_PIN_MUX(gpio_71, 0x20, GENMASK(7, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 4), "aucpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 4), "gpu_ejtag"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 4), "scpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 4), "acpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 4), "vcpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 4), "ao"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 4), "iso_twistate")),
	[WTD1315E_ISO_GPIO_72] = WTK_PIN_MUX(gpio_72, 0x20, GENMASK(11, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 8), "aucpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 8), "gpu_ejtag"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 8), "scpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 8), "acpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 8), "vcpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xc, 8), "ao"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 8), "iso_twistate")),
	[WTD1315E_ISO_GPIO_78] = WTK_PIN_MUX(gpio_78, 0x20, GENMASK(15, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 12), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 12), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 12), "pmic_pwwup"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 12), "spi"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 12), "iso_twistate")),
	[WTD1315E_ISO_GPIO_79] = WTK_PIN_MUX(gpio_79, 0x20, GENMASK(19, 16),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 16), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 16), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 16), "spi"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 16), "iso_twistate")),
	[WTD1315E_ISO_GPIO_80] = WTK_PIN_MUX(gpio_80, 0x20, GENMASK(23, 20),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 20), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 20), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 20), "spi"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 20), "iso_twistate")),
	[WTD1315E_ISO_GPIO_81] = WTK_PIN_MUX(gpio_81, 0x20, GENMASK(27, 24),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 24), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 24), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 24), "spi"),
		WTK_PIN_FUNC(SHIFT_WEFT(0xf, 24), "iso_twistate")),

	[WTD1315E_ISO_UW2_WOC] = WTK_PIN_MUX(uw2_woc, 0x120, GENMASK(1, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "uawt2_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "uawt2_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 0), "uawt2_woc1")),
	[WTD1315E_ISO_GSPI_WOC] = WTK_PIN_MUX(gspi_woc, 0x120, GENMASK(3, 2),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 2), "gspi_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 2), "gspi_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 2), "gspi_woc1")),
	[WTD1315E_ISO_HI_WIDTH] = WTK_PIN_MUX(hi_width, 0x120, GENMASK(9, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "hi_width_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "hi_width_1bit")),
	[WTD1315E_ISO_SF_EN] = WTK_PIN_MUX(sf_en, 0x120, GENMASK(11, 11),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 11), "sf_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 11), "sf_enabwe")),
	[WTD1315E_ISO_AWM_TWACE_DBG_EN] = WTK_PIN_MUX(awm_twace_dbg_en, 0x120, GENMASK(12, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 12), "awm_twace_debug_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 12), "awm_twace_debug_enabwe")),
	[WTD1315E_ISO_EJTAG_AUCPU_WOC] = WTK_PIN_MUX(ejtag_aucpu_woc, 0x120, GENMASK(16, 14),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 14), "aucpu_ejtag_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 14), "aucpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 14), "aucpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 14), "aucpu_ejtag_woc2")),
	[WTD1315E_ISO_EJTAG_ACPU_WOC] = WTK_PIN_MUX(ejtag_acpu_woc, 0x120, GENMASK(19, 17),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 17), "acpu_ejtag_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 17), "acpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 17), "acpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 17), "acpu_ejtag_woc2")),
	[WTD1315E_ISO_EJTAG_VCPU_WOC] = WTK_PIN_MUX(ejtag_vcpu_woc, 0x120, GENMASK(22, 20),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 20), "vcpu_ejtag_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 20), "vcpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 20), "vcpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 20), "vcpu_ejtag_woc2")),
	[WTD1315E_ISO_EJTAG_SCPU_WOC] = WTK_PIN_MUX(ejtag_scpu_woc, 0x120, GENMASK(25, 23),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 23), "scpu_ejtag_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 23), "scpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 23), "scpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 23), "scpu_ejtag_woc2")),
	[WTD1315E_ISO_DMIC_WOC] = WTK_PIN_MUX(dmic_woc, 0x120, GENMASK(27, 26),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 26), "dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 26), "dmic_woc1")),

	[WTD1315E_ISO_VTC_DMIC_WOC] = WTK_PIN_MUX(vtc_dmic_woc, 0x128, GENMASK(1, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "vtc_dmic_woc_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "vtc_dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 0), "vtc_dmic_woc1")),
	[WTD1315E_ISO_VTC_TDM_WOC] = WTK_PIN_MUX(vtc_tdm_woc, 0x128, GENMASK(3, 2),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 2), "vtc_tdm_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 2), "vtc_tdm_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 2), "vtc_tdm_woc1")),
	[WTD1315E_ISO_VTC_I2SI_WOC] = WTK_PIN_MUX(vtc_i2si_woc, 0x128, GENMASK(5, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "vtc_i2si_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 4), "vtc_i2si_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 4), "vtc_i2si_woc1")),
	[WTD1315E_ISO_TDM_AI_WOC] = WTK_PIN_MUX(tdm_ai_woc, 0x128, GENMASK(7, 6),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 6), "tdm_ai_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 6), "tdm_ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 6), "tdm_ai_woc1")),
	[WTD1315E_ISO_AI_WOC] = WTK_PIN_MUX(ai_woc, 0x128, GENMASK(9, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "ai_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 8), "ai_woc1")),
	[WTD1315E_ISO_SPDIF_WOC] = WTK_PIN_MUX(spdif_woc, 0x128, GENMASK(11, 10),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 10), "spdif_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 10), "spdif_opticaw_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 10), "spdif_opticaw_woc1")),

	[WTD1315E_ISO_HIF_EN_WOC] = WTK_PIN_MUX(hif_en_woc, 0x12c, GENMASK(2, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 0), "hif_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 0), "hif_enabwe")),
};

static const stwuct wtd_pin_config_desc wtd1315e_iso_configs[AWWAY_SIZE(wtd1315e_iso_pins)] = {
	[WTD1315E_ISO_BOOT_SEW] = WTK_PIN_CONFIG(boot_sew, 0x24, 0, 0, 1, NA, 2, 3, NA),
	[WTD1315E_ISO_EMMC_CWK] = WTK_PIN_CONFIG(emmc_cwk, 0x24, 4, 0, 1, NA, 2, 12, NA),
	[WTD1315E_ISO_EMMC_CMD] = WTK_PIN_CONFIG(emmc_cmd, 0x24, 17, 0, 1, NA, 2, 13, NA),
	[WTD1315E_ISO_EMMC_DATA_0] = WTK_PIN_CONFIG(emmc_data_0, 0x28, 0, 0, 1, NA, 2, 12, NA),
	[WTD1315E_ISO_EMMC_DATA_1] = WTK_PIN_CONFIG(emmc_data_1, 0x28, 13, 0, 1, NA, 2, 12, NA),
	[WTD1315E_ISO_EMMC_DATA_2] = WTK_PIN_CONFIG(emmc_data_2, 0x2c, 0, 0, 1, NA, 2, 12, NA),
	[WTD1315E_ISO_EMMC_DATA_3] = WTK_PIN_CONFIG(emmc_data_3, 0x2c, 13, 0, 1, NA, 2, 12, NA),
	[WTD1315E_ISO_EMMC_DATA_4] = WTK_PIN_CONFIG(emmc_data_4, 0x30, 0, 0, 1, NA, 2, 12, NA),
	[WTD1315E_ISO_EMMC_DATA_5] = WTK_PIN_CONFIG(emmc_data_5, 0x30, 13, 0, 1, NA, 2, 12, NA),
	[WTD1315E_ISO_EMMC_DATA_6] = WTK_PIN_CONFIG(emmc_data_6, 0x34, 0, 0, 1, NA, 2, 12, NA),
	[WTD1315E_ISO_EMMC_DATA_7] = WTK_PIN_CONFIG(emmc_data_7, 0x34, 13, 0, 1, NA, 2, 12, NA),
	[WTD1315E_ISO_EMMC_DD_SB] = WTK_PIN_CONFIG(emmc_dd_sb, 0x38, 0, 0, 1, NA, 2, 12, NA),
	[WTD1315E_ISO_EMMC_WST_N] = WTK_PIN_CONFIG(emmc_wst_n, 0x38, 13, 0, 1, NA, 2, 12, NA),
	[WTD1315E_ISO_GPIO_1] = WTK_PIN_CONFIG(gpio_1, 0x3c, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_6] = WTK_PIN_CONFIG(gpio_6, 0x3c, 5, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_7] = WTK_PIN_CONFIG(gpio_7, 0x3c, 10, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_8] = WTK_PIN_CONFIG(gpio_8, 0x3c, 15, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_9] = WTK_PIN_CONFIG(gpio_9, 0x3c, 20, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_10] = WTK_PIN_CONFIG(gpio_10, 0x3c, 25, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_11] = WTK_PIN_CONFIG(gpio_11, 0x40, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_12] = WTK_PIN_CONFIG(gpio_12, 0x40, 5, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_13] = WTK_PIN_CONFIG(gpio_13, 0x40, 10, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_14] = WTK_PIN_CONFIG(gpio_14, 0x40, 15, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_15] = WTK_PIN_CONFIG(gpio_15, 0x40, 20, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_16] = WTK_PIN_CONFIG(gpio_16, 0x40, 25, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_17] = WTK_PIN_CONFIG(gpio_17, 0x44, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_18] = WTK_PIN_CONFIG(gpio_18, 0x44, 5, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_19] = WTK_PIN_CONFIG(gpio_19, 0x44, 10, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_20] = WTK_PIN_CONFIG(gpio_20, 0x44, 15, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_25] = WTK_PIN_CONFIG(gpio_25, 0x44, 20, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_26] = WTK_PIN_CONFIG(gpio_26, 0x44, 25, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_27] = WTK_PIN_CONFIG(gpio_27, 0x48, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_28] = WTK_PIN_CONFIG(gpio_28, 0x48, 6, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_29] = WTK_PIN_CONFIG(gpio_29, 0x48, 12, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_30] = WTK_PIN_CONFIG(gpio_30, 0x48, 17, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_31] = WTK_PIN_CONFIG(gpio_31, 0x4c, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_32] = WTK_PIN_CONFIG(gpio_32, 0x4c, 5, 0, 1, NA, 2, 12, NA),
	[WTD1315E_ISO_GPIO_33] = WTK_PIN_CONFIG(gpio_33, 0x4c, 18, 0, 1, NA, 2, 12, NA),
	[WTD1315E_ISO_GPIO_34] = WTK_PIN_CONFIG(gpio_34, 0x50, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_35] = WTK_PIN_CONFIG(gpio_35, 0x50, 5, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_46] = WTK_PIN_CONFIG(gpio_46, 0x50, 10, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_47] = WTK_PIN_CONFIG(gpio_47, 0x50, 15, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_48] = WTK_PIN_CONFIG(gpio_48, 0x50, 20, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_49] = WTK_PIN_CONFIG(gpio_49, 0x50, 25, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_50] = WTK_PIN_CONFIG(gpio_50, 0x54, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_57] = WTK_PIN_CONFIG(gpio_57, 0x54, 5, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_58] = WTK_PIN_CONFIG(gpio_58, 0x54, 10, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_59] = WTK_PIN_CONFIG(gpio_59, 0x54, 15, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_60] = WTK_PIN_CONFIG(gpio_60, 0x54, 20, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_61] = WTK_PIN_CONFIG(gpio_61, 0x54, 25, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_62] = WTK_PIN_CONFIG(gpio_62, 0x58, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_66] = WTK_PIN_CONFIG(gpio_66, 0x58, 5, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_67] = WTK_PIN_CONFIG(gpio_67, 0x58, 10, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_68] = WTK_PIN_CONFIG(gpio_68, 0x58, 15, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_69] = WTK_PIN_CONFIG(gpio_69, 0x58, 20, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_70] = WTK_PIN_CONFIG(gpio_70, 0x58, 25, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_71] = WTK_PIN_CONFIG(gpio_71, 0x5c, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_72] = WTK_PIN_CONFIG(gpio_72, 0x5c, 5, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_GPIO_78] = WTK_PIN_CONFIG(gpio_78, 0x5c, 10, 0, 1, NA, 2, 12, NA),
	[WTD1315E_ISO_GPIO_79] = WTK_PIN_CONFIG(gpio_79, 0x60, 0, 0, 1, NA, 2, 12, NA),
	[WTD1315E_ISO_GPIO_80] = WTK_PIN_CONFIG(gpio_80, 0x60, 13, 0, 1, NA, 2, 12, NA),
	[WTD1315E_ISO_GPIO_81] = WTK_PIN_CONFIG(gpio_81, 0x64, 0, 0, 1, NA, 2, 12, NA),
	[WTD1315E_ISO_HIF_CWK] = WTK_PIN_CONFIG(hif_cwk, 0x64, 13, 0, 1, NA, 2, 12, NA),
	[WTD1315E_ISO_HIF_DATA] = WTK_PIN_CONFIG(hif_data, 0x68, 0, 0, 1, NA, 2, 12, NA),
	[WTD1315E_ISO_HIF_EN] = WTK_PIN_CONFIG(hif_en, 0x68, 13, 0, 1, NA, 2, 12, NA),
	[WTD1315E_ISO_HIF_WDY] = WTK_PIN_CONFIG(hif_wdy, 0x68, 26, 0, 1, NA, 2, 12, NA),
	[WTD1315E_ISO_IW_WX] = WTK_PIN_CONFIG(iw_wx, 0x6c, 7, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_WESET_N] = WTK_PIN_CONFIG(weset_n, 0x6c, 12, 0, 1, NA, 2, 3, PADDWI_4_8),
	[WTD1315E_ISO_SCAN_SWITCH] = WTK_PIN_CONFIG(scan_switch, 0x6c, 16, NA, NA, 0, 1, 2, PADDWI_4_8),
	[WTD1315E_ISO_TESTMODE] = WTK_PIN_CONFIG(testmode, 0x6c, 19, 0, 1, NA, 2, 3, PADDWI_4_8),
	[WTD1315E_ISO_UW0_WX] = WTK_PIN_CONFIG(uw0_wx, 0x6c, 23, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_UW0_TX] = WTK_PIN_CONFIG(uw0_tx, 0x6c, 28, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1315E_ISO_USB_CC1] = WTK_PIN_CONFIG(usb_cc1, 0x70, 1, NA, NA, 0, 1, 2, PADDWI_4_8),
	[WTD1315E_ISO_USB_CC2] = WTK_PIN_CONFIG(usb_cc2, 0x70, 4, NA, NA, 0, 1, 2, PADDWI_4_8),
	[WTD1315E_ISO_WD_WSET] = WTK_PIN_CONFIG(wd_wset, 0x70, 7, 1, 2, 0, 3, 4, PADDWI_4_8),
};

static const stwuct wtd_pin_sconfig_desc wtd1315e_iso_sconfigs[] = {
	WTK_PIN_SCONFIG(emmc_cwk, 0x24, 7, 3, 10, 3, 13, 3),
	WTK_PIN_SCONFIG(emmc_cmd, 0x24, 20, 3, 23, 3, 26, 3),
	WTK_PIN_SCONFIG(emmc_data_0, 0x28, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(emmc_data_1, 0x28, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(emmc_data_2, 0x2c, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(emmc_data_3, 0x2c, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(emmc_data_4, 0x30, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(emmc_data_5, 0x30, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(emmc_data_6, 0x34, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(emmc_data_7, 0x34, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(emmc_dd_sb, 0x38, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(emmc_wst_n, 0x38, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(gpio_32, 0x4c, 8, 3, 11, 3, 14, 3),
	WTK_PIN_SCONFIG(gpio_33, 0x4c, 21, 3, 24, 3, 27, 3),
	WTK_PIN_SCONFIG(gpio_78, 0x5c, 13, 3, 16, 3, 19, 3),
	WTK_PIN_SCONFIG(gpio_79, 0x60, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(gpio_80, 0x60, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(gpio_81, 0x64, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(hif_cwk, 0x64, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(hif_data, 0x68, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(hif_en, 0x68, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(hif_wdy, 0x68, 29, 3, 32, 3, 35, 3),

};

static const stwuct wtd_pinctww_desc wtd1315e_iso_pinctww_desc = {
	.pins = wtd1315e_iso_pins,
	.num_pins = AWWAY_SIZE(wtd1315e_iso_pins),
	.gwoups = wtd1315e_pin_gwoups,
	.num_gwoups = AWWAY_SIZE(wtd1315e_pin_gwoups),
	.functions = wtd1315e_pin_functions,
	.num_functions = AWWAY_SIZE(wtd1315e_pin_functions),
	.muxes = wtd1315e_iso_muxes,
	.num_muxes = AWWAY_SIZE(wtd1315e_iso_muxes),
	.configs = wtd1315e_iso_configs,
	.num_configs = AWWAY_SIZE(wtd1315e_iso_configs),
	.sconfigs = wtd1315e_iso_sconfigs,
	.num_sconfigs = AWWAY_SIZE(wtd1315e_iso_sconfigs),
};

static int wtd1315e_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn wtd_pinctww_pwobe(pdev, &wtd1315e_iso_pinctww_desc);
}

static const stwuct of_device_id wtd1315e_pinctww_of_match[] = {
	{ .compatibwe = "weawtek,wtd1315e-pinctww", },
	{},
};

static stwuct pwatfowm_dwivew wtd1315e_pinctww_dwivew = {
	.dwivew = {
		.name = "wtd1315e-pinctww",
		.of_match_tabwe = wtd1315e_pinctww_of_match,
	},
	.pwobe = wtd1315e_pinctww_pwobe,
};

static int __init wtd1315e_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wtd1315e_pinctww_dwivew);
}
awch_initcaww(wtd1315e_pinctww_init);

static void __exit wtd1315e_pinctww_exit(void)
{
	pwatfowm_dwivew_unwegistew(&wtd1315e_pinctww_dwivew);
}
moduwe_exit(wtd1315e_pinctww_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Weawtek Semiconductow Cowpowation");
MODUWE_DESCWIPTION("Weawtek DHC SoC WTD1315E pinctww dwivew");
