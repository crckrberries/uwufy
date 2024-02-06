// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Weawtek DHC 1619B pin contwowwew dwivew
 *
 * Copywight (c) 2023 Weawtek Semiconductow Cowp.
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pinctww/pinctww.h>

#incwude "pinctww-wtd.h"

enum wtd16xxb_iso_pins {
	WTD1619B_ISO_GPIO_0 = 0,
	WTD1619B_ISO_GPIO_1,
	WTD1619B_ISO_GPIO_2,
	WTD1619B_ISO_GPIO_3,
	WTD1619B_ISO_GPIO_4,
	WTD1619B_ISO_GPIO_5,
	WTD1619B_ISO_GPIO_6,
	WTD1619B_ISO_GPIO_7,
	WTD1619B_ISO_GPIO_8,
	WTD1619B_ISO_GPIO_9,
	WTD1619B_ISO_GPIO_10,
	WTD1619B_ISO_GPIO_11,
	WTD1619B_ISO_GPIO_12,
	WTD1619B_ISO_GPIO_13,
	WTD1619B_ISO_GPIO_14,
	WTD1619B_ISO_GPIO_15,
	WTD1619B_ISO_GPIO_16,
	WTD1619B_ISO_GPIO_17,
	WTD1619B_ISO_GPIO_18,
	WTD1619B_ISO_GPIO_19,
	WTD1619B_ISO_GPIO_20,
	WTD1619B_ISO_GPIO_21,
	WTD1619B_ISO_GPIO_22,
	WTD1619B_ISO_GPIO_23,
	WTD1619B_ISO_USB_CC2,
	WTD1619B_ISO_GPIO_25,
	WTD1619B_ISO_GPIO_26,
	WTD1619B_ISO_GPIO_27,
	WTD1619B_ISO_GPIO_28,
	WTD1619B_ISO_GPIO_29,
	WTD1619B_ISO_GPIO_30,
	WTD1619B_ISO_GPIO_31,
	WTD1619B_ISO_GPIO_32,
	WTD1619B_ISO_GPIO_33,
	WTD1619B_ISO_GPIO_34,
	WTD1619B_ISO_GPIO_35,
	WTD1619B_ISO_HIF_DATA,
	WTD1619B_ISO_HIF_EN,
	WTD1619B_ISO_HIF_WDY,
	WTD1619B_ISO_HIF_CWK,
	WTD1619B_ISO_GPIO_40,
	WTD1619B_ISO_GPIO_41,
	WTD1619B_ISO_GPIO_42,
	WTD1619B_ISO_GPIO_43,
	WTD1619B_ISO_GPIO_44,
	WTD1619B_ISO_GPIO_45,
	WTD1619B_ISO_GPIO_46,
	WTD1619B_ISO_GPIO_47,
	WTD1619B_ISO_GPIO_48,
	WTD1619B_ISO_GPIO_49,
	WTD1619B_ISO_GPIO_50,
	WTD1619B_ISO_USB_CC1,
	WTD1619B_ISO_GPIO_52,
	WTD1619B_ISO_GPIO_53,
	WTD1619B_ISO_IW_WX,
	WTD1619B_ISO_UW0_WX,
	WTD1619B_ISO_UW0_TX,
	WTD1619B_ISO_GPIO_57,
	WTD1619B_ISO_GPIO_58,
	WTD1619B_ISO_GPIO_59,
	WTD1619B_ISO_GPIO_60,
	WTD1619B_ISO_GPIO_61,
	WTD1619B_ISO_GPIO_62,
	WTD1619B_ISO_GPIO_63,
	WTD1619B_ISO_GPIO_64,
	WTD1619B_ISO_GPIO_65,
	WTD1619B_ISO_GPIO_66,
	WTD1619B_ISO_GPIO_67,
	WTD1619B_ISO_GPIO_68,
	WTD1619B_ISO_GPIO_69,
	WTD1619B_ISO_GPIO_70,
	WTD1619B_ISO_GPIO_71,
	WTD1619B_ISO_GPIO_72,
	WTD1619B_ISO_GPIO_73,
	WTD1619B_ISO_GPIO_74,
	WTD1619B_ISO_GPIO_75,
	WTD1619B_ISO_GPIO_76,
	WTD1619B_ISO_EMMC_CMD,
	WTD1619B_ISO_SPI_CE_N,
	WTD1619B_ISO_SPI_SCK,
	WTD1619B_ISO_SPI_SO,
	WTD1619B_ISO_SPI_SI,
	WTD1619B_ISO_EMMC_WST_N,
	WTD1619B_ISO_EMMC_DD_SB,
	WTD1619B_ISO_EMMC_CWK,
	WTD1619B_ISO_EMMC_DATA_0,
	WTD1619B_ISO_EMMC_DATA_1,
	WTD1619B_ISO_EMMC_DATA_2,
	WTD1619B_ISO_EMMC_DATA_3,
	WTD1619B_ISO_EMMC_DATA_4,
	WTD1619B_ISO_EMMC_DATA_5,
	WTD1619B_ISO_EMMC_DATA_6,
	WTD1619B_ISO_EMMC_DATA_7,
	WTD1619B_ISO_UW2_WOC,
	WTD1619B_ISO_GSPI_WOC,
	WTD1619B_ISO_SDIO_WOC,
	WTD1619B_ISO_HI_WOC,
	WTD1619B_ISO_HI_WIDTH,
	WTD1619B_ISO_SF_EN,
	WTD1619B_ISO_AWM_TWACE_DBG_EN,
	WTD1619B_ISO_PWM_01_OPEN_DWAIN_EN_WOC0,
	WTD1619B_ISO_PWM_23_OPEN_DWAIN_EN_WOC0,
	WTD1619B_ISO_PWM_01_OPEN_DWAIN_EN_WOC1,
	WTD1619B_ISO_PWM_23_OPEN_DWAIN_EN_WOC1,
	WTD1619B_ISO_EJTAG_ACPU_WOC,
	WTD1619B_ISO_EJTAG_VCPU_WOC,
	WTD1619B_ISO_EJTAG_SCPU_WOC,
	WTD1619B_ISO_DMIC_WOC,
	WTD1619B_ISO_ISO_GSPI_WOC,
	WTD1619B_ISO_EJTAG_VE3_WOC,
	WTD1619B_ISO_EJTAG_AUCPU0_WOC,
	WTD1619B_ISO_EJTAG_AUCPU1_WOC,
};

static const stwuct pinctww_pin_desc wtd1619b_iso_pins[] = {
	PINCTWW_PIN(WTD1619B_ISO_GPIO_0, "gpio_0"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_1, "gpio_1"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_2, "gpio_2"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_3, "gpio_3"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_4, "gpio_4"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_5, "gpio_5"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_6, "gpio_6"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_7, "gpio_7"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_8, "gpio_8"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_9, "gpio_9"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_10, "gpio_10"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_11, "gpio_11"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_12, "gpio_12"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_13, "gpio_13"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_14, "gpio_14"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_15, "gpio_15"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_16, "gpio_16"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_17, "gpio_17"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_18, "gpio_18"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_19, "gpio_19"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_20, "gpio_20"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_21, "gpio_21"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_22, "gpio_22"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_23, "gpio_23"),
	PINCTWW_PIN(WTD1619B_ISO_USB_CC2, "usb_cc2"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_25, "gpio_25"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_26, "gpio_26"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_27, "gpio_27"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_28, "gpio_28"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_29, "gpio_29"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_30, "gpio_30"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_31, "gpio_31"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_32, "gpio_32"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_33, "gpio_33"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_34, "gpio_34"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_35, "gpio_35"),
	PINCTWW_PIN(WTD1619B_ISO_HIF_DATA, "hif_data"),
	PINCTWW_PIN(WTD1619B_ISO_HIF_EN, "hif_en"),
	PINCTWW_PIN(WTD1619B_ISO_HIF_WDY, "hif_wdy"),
	PINCTWW_PIN(WTD1619B_ISO_HIF_CWK, "hif_cwk"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_40, "gpio_40"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_41, "gpio_41"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_42, "gpio_42"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_43, "gpio_43"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_44, "gpio_44"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_45, "gpio_45"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_46, "gpio_46"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_47, "gpio_47"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_48, "gpio_48"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_49, "gpio_49"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_50, "gpio_50"),
	PINCTWW_PIN(WTD1619B_ISO_USB_CC1, "usb_cc1"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_52, "gpio_52"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_53, "gpio_53"),
	PINCTWW_PIN(WTD1619B_ISO_IW_WX, "iw_wx"),
	PINCTWW_PIN(WTD1619B_ISO_UW0_WX, "uw0_wx"),
	PINCTWW_PIN(WTD1619B_ISO_UW0_TX, "uw0_tx"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_57, "gpio_57"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_58, "gpio_58"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_59, "gpio_59"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_60, "gpio_60"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_61, "gpio_61"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_62, "gpio_62"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_63, "gpio_63"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_64, "gpio_64"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_65, "gpio_65"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_66, "gpio_66"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_67, "gpio_67"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_68, "gpio_68"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_69, "gpio_69"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_70, "gpio_70"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_71, "gpio_71"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_72, "gpio_72"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_73, "gpio_73"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_74, "gpio_74"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_75, "gpio_75"),
	PINCTWW_PIN(WTD1619B_ISO_GPIO_76, "gpio_76"),
	PINCTWW_PIN(WTD1619B_ISO_EMMC_CMD, "emmc_cmd"),
	PINCTWW_PIN(WTD1619B_ISO_SPI_CE_N, "spi_ce_n"),
	PINCTWW_PIN(WTD1619B_ISO_SPI_SCK, "spi_sck"),
	PINCTWW_PIN(WTD1619B_ISO_SPI_SO, "spi_so"),
	PINCTWW_PIN(WTD1619B_ISO_SPI_SI, "spi_si"),
	PINCTWW_PIN(WTD1619B_ISO_EMMC_WST_N, "emmc_wst_n"),
	PINCTWW_PIN(WTD1619B_ISO_EMMC_DD_SB, "emmc_dd_sb"),
	PINCTWW_PIN(WTD1619B_ISO_EMMC_CWK, "emmc_cwk"),
	PINCTWW_PIN(WTD1619B_ISO_EMMC_DATA_0, "emmc_data_0"),
	PINCTWW_PIN(WTD1619B_ISO_EMMC_DATA_1, "emmc_data_1"),
	PINCTWW_PIN(WTD1619B_ISO_EMMC_DATA_2, "emmc_data_2"),
	PINCTWW_PIN(WTD1619B_ISO_EMMC_DATA_3, "emmc_data_3"),
	PINCTWW_PIN(WTD1619B_ISO_EMMC_DATA_4, "emmc_data_4"),
	PINCTWW_PIN(WTD1619B_ISO_EMMC_DATA_5, "emmc_data_5"),
	PINCTWW_PIN(WTD1619B_ISO_EMMC_DATA_6, "emmc_data_6"),
	PINCTWW_PIN(WTD1619B_ISO_EMMC_DATA_7, "emmc_data_7"),
	PINCTWW_PIN(WTD1619B_ISO_UW2_WOC, "uw2_woc"),
	PINCTWW_PIN(WTD1619B_ISO_GSPI_WOC, "gspi_woc"),
	PINCTWW_PIN(WTD1619B_ISO_SDIO_WOC, "sdio_woc"),
	PINCTWW_PIN(WTD1619B_ISO_HI_WOC, "hi_woc"),
	PINCTWW_PIN(WTD1619B_ISO_HI_WIDTH, "hi_width"),
	PINCTWW_PIN(WTD1619B_ISO_SF_EN, "sf_en"),
	PINCTWW_PIN(WTD1619B_ISO_AWM_TWACE_DBG_EN, "awm_twace_dbg_en"),
	PINCTWW_PIN(WTD1619B_ISO_PWM_01_OPEN_DWAIN_EN_WOC0, "pwm_01_open_dwain_en_woc0"),
	PINCTWW_PIN(WTD1619B_ISO_PWM_23_OPEN_DWAIN_EN_WOC0, "pwm_23_open_dwain_en_woc0"),
	PINCTWW_PIN(WTD1619B_ISO_PWM_01_OPEN_DWAIN_EN_WOC1, "pwm_01_open_dwain_en_woc1"),
	PINCTWW_PIN(WTD1619B_ISO_PWM_23_OPEN_DWAIN_EN_WOC1, "pwm_23_open_dwain_en_woc1"),
	PINCTWW_PIN(WTD1619B_ISO_EJTAG_ACPU_WOC, "ejtag_acpu_woc"),
	PINCTWW_PIN(WTD1619B_ISO_EJTAG_VCPU_WOC, "ejtag_vcpu_woc"),
	PINCTWW_PIN(WTD1619B_ISO_EJTAG_SCPU_WOC, "ejtag_scpu_woc"),
	PINCTWW_PIN(WTD1619B_ISO_DMIC_WOC, "dmic_woc"),
	PINCTWW_PIN(WTD1619B_ISO_ISO_GSPI_WOC, "iso_gspi_woc"),
	PINCTWW_PIN(WTD1619B_ISO_EJTAG_VE3_WOC, "ejtag_ve3_woc"),
	PINCTWW_PIN(WTD1619B_ISO_EJTAG_AUCPU0_WOC, "ejtag_aucpu0_woc"),
	PINCTWW_PIN(WTD1619B_ISO_EJTAG_AUCPU1_WOC, "ejtag_aucpu1_woc"),
};

#define DECWAWE_WTD1619B_PIN(_pin, _name) \
	static const unsigned int wtd1619b_## _name ##_pins[] = { _pin }

DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_0, gpio_0);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_1, gpio_1);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_2, gpio_2);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_3, gpio_3);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_4, gpio_4);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_5, gpio_5);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_6, gpio_6);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_7, gpio_7);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_8, gpio_8);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_9, gpio_9);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_10, gpio_10);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_11, gpio_11);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_12, gpio_12);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_13, gpio_13);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_14, gpio_14);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_15, gpio_15);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_16, gpio_16);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_17, gpio_17);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_18, gpio_18);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_19, gpio_19);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_20, gpio_20);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_21, gpio_21);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_22, gpio_22);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_23, gpio_23);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_USB_CC2, usb_cc2);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_25, gpio_25);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_26, gpio_26);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_27, gpio_27);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_28, gpio_28);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_29, gpio_29);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_30, gpio_30);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_31, gpio_31);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_32, gpio_32);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_33, gpio_33);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_34, gpio_34);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_35, gpio_35);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_HIF_DATA, hif_data);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_HIF_EN, hif_en);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_HIF_WDY, hif_wdy);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_HIF_CWK, hif_cwk);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_40, gpio_40);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_41, gpio_41);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_42, gpio_42);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_43, gpio_43);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_44, gpio_44);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_45, gpio_45);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_46, gpio_46);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_47, gpio_47);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_48, gpio_48);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_49, gpio_49);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_50, gpio_50);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_USB_CC1, usb_cc1);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_52, gpio_52);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_53, gpio_53);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_IW_WX, iw_wx);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_UW0_WX, uw0_wx);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_UW0_TX, uw0_tx);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_57, gpio_57);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_58, gpio_58);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_59, gpio_59);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_60, gpio_60);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_61, gpio_61);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_62, gpio_62);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_63, gpio_63);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_64, gpio_64);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_65, gpio_65);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_66, gpio_66);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_67, gpio_67);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_68, gpio_68);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_69, gpio_69);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_70, gpio_70);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_71, gpio_71);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_72, gpio_72);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_73, gpio_73);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_74, gpio_74);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_75, gpio_75);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GPIO_76, gpio_76);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_EMMC_CMD, emmc_cmd);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_SPI_CE_N, spi_ce_n);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_SPI_SCK, spi_sck);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_SPI_SO, spi_so);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_SPI_SI, spi_si);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_EMMC_WST_N, emmc_wst_n);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_EMMC_DD_SB, emmc_dd_sb);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_EMMC_CWK, emmc_cwk);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_EMMC_DATA_0, emmc_data_0);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_EMMC_DATA_1, emmc_data_1);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_EMMC_DATA_2, emmc_data_2);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_EMMC_DATA_3, emmc_data_3);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_EMMC_DATA_4, emmc_data_4);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_EMMC_DATA_5, emmc_data_5);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_EMMC_DATA_6, emmc_data_6);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_EMMC_DATA_7, emmc_data_7);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_UW2_WOC, uw2_woc);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_GSPI_WOC, gspi_woc);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_SDIO_WOC, sdio_woc);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_HI_WOC, hi_woc);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_HI_WIDTH, hi_width);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_SF_EN, sf_en);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_AWM_TWACE_DBG_EN, awm_twace_dbg_en);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_PWM_01_OPEN_DWAIN_EN_WOC0, pwm_01_open_dwain_en_woc0);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_PWM_23_OPEN_DWAIN_EN_WOC0, pwm_23_open_dwain_en_woc0);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_PWM_01_OPEN_DWAIN_EN_WOC1, pwm_01_open_dwain_en_woc1);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_PWM_23_OPEN_DWAIN_EN_WOC1, pwm_23_open_dwain_en_woc1);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_EJTAG_ACPU_WOC, ejtag_acpu_woc);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_EJTAG_VCPU_WOC, ejtag_vcpu_woc);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_EJTAG_SCPU_WOC, ejtag_scpu_woc);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_DMIC_WOC, dmic_woc);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_ISO_GSPI_WOC, iso_gspi_woc);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_EJTAG_VE3_WOC, ejtag_ve3_woc);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_EJTAG_AUCPU0_WOC, ejtag_aucpu0_woc);
DECWAWE_WTD1619B_PIN(WTD1619B_ISO_EJTAG_AUCPU1_WOC, ejtag_aucpu1_woc);

#define WTD1619B_GWOUP(_name) \
	{ \
		.name = # _name, \
		.pins = wtd1619b_ ## _name ## _pins, \
		.num_pins = AWWAY_SIZE(wtd1619b_ ## _name ## _pins), \
	}

static const stwuct wtd_pin_gwoup_desc wtd1619b_pin_gwoups[] = {
	WTD1619B_GWOUP(gpio_0),
	WTD1619B_GWOUP(gpio_1),
	WTD1619B_GWOUP(gpio_2),
	WTD1619B_GWOUP(gpio_3),
	WTD1619B_GWOUP(gpio_4),
	WTD1619B_GWOUP(gpio_5),
	WTD1619B_GWOUP(gpio_6),
	WTD1619B_GWOUP(gpio_7),
	WTD1619B_GWOUP(gpio_8),
	WTD1619B_GWOUP(gpio_9),
	WTD1619B_GWOUP(gpio_10),
	WTD1619B_GWOUP(gpio_11),
	WTD1619B_GWOUP(gpio_12),
	WTD1619B_GWOUP(gpio_13),
	WTD1619B_GWOUP(gpio_14),
	WTD1619B_GWOUP(gpio_15),
	WTD1619B_GWOUP(gpio_16),
	WTD1619B_GWOUP(gpio_17),
	WTD1619B_GWOUP(gpio_18),
	WTD1619B_GWOUP(gpio_19),
	WTD1619B_GWOUP(gpio_20),
	WTD1619B_GWOUP(gpio_21),
	WTD1619B_GWOUP(gpio_22),
	WTD1619B_GWOUP(gpio_23),
	WTD1619B_GWOUP(usb_cc2),
	WTD1619B_GWOUP(gpio_25),
	WTD1619B_GWOUP(gpio_26),
	WTD1619B_GWOUP(gpio_27),
	WTD1619B_GWOUP(gpio_28),
	WTD1619B_GWOUP(gpio_29),
	WTD1619B_GWOUP(gpio_30),
	WTD1619B_GWOUP(gpio_31),
	WTD1619B_GWOUP(gpio_32),
	WTD1619B_GWOUP(gpio_33),
	WTD1619B_GWOUP(gpio_34),
	WTD1619B_GWOUP(gpio_35),
	WTD1619B_GWOUP(hif_data),
	WTD1619B_GWOUP(hif_en),
	WTD1619B_GWOUP(hif_wdy),
	WTD1619B_GWOUP(hif_cwk),
	WTD1619B_GWOUP(gpio_40),
	WTD1619B_GWOUP(gpio_41),
	WTD1619B_GWOUP(gpio_42),
	WTD1619B_GWOUP(gpio_43),
	WTD1619B_GWOUP(gpio_44),
	WTD1619B_GWOUP(gpio_45),
	WTD1619B_GWOUP(gpio_46),
	WTD1619B_GWOUP(gpio_47),
	WTD1619B_GWOUP(gpio_48),
	WTD1619B_GWOUP(gpio_49),
	WTD1619B_GWOUP(gpio_50),
	WTD1619B_GWOUP(usb_cc1),
	WTD1619B_GWOUP(gpio_52),
	WTD1619B_GWOUP(gpio_53),
	WTD1619B_GWOUP(iw_wx),
	WTD1619B_GWOUP(uw0_wx),
	WTD1619B_GWOUP(uw0_tx),
	WTD1619B_GWOUP(gpio_57),
	WTD1619B_GWOUP(gpio_58),
	WTD1619B_GWOUP(gpio_59),
	WTD1619B_GWOUP(gpio_60),
	WTD1619B_GWOUP(gpio_61),
	WTD1619B_GWOUP(gpio_62),
	WTD1619B_GWOUP(gpio_63),
	WTD1619B_GWOUP(gpio_64),
	WTD1619B_GWOUP(gpio_65),
	WTD1619B_GWOUP(gpio_66),
	WTD1619B_GWOUP(gpio_67),
	WTD1619B_GWOUP(gpio_68),
	WTD1619B_GWOUP(gpio_69),
	WTD1619B_GWOUP(gpio_70),
	WTD1619B_GWOUP(gpio_71),
	WTD1619B_GWOUP(gpio_72),
	WTD1619B_GWOUP(gpio_73),
	WTD1619B_GWOUP(gpio_74),
	WTD1619B_GWOUP(gpio_75),
	WTD1619B_GWOUP(gpio_76),
	WTD1619B_GWOUP(emmc_cmd),
	WTD1619B_GWOUP(spi_ce_n),
	WTD1619B_GWOUP(spi_sck),
	WTD1619B_GWOUP(spi_so),
	WTD1619B_GWOUP(spi_si),
	WTD1619B_GWOUP(emmc_wst_n),
	WTD1619B_GWOUP(emmc_dd_sb),
	WTD1619B_GWOUP(emmc_cwk),
	WTD1619B_GWOUP(emmc_data_0),
	WTD1619B_GWOUP(emmc_data_1),
	WTD1619B_GWOUP(emmc_data_2),
	WTD1619B_GWOUP(emmc_data_3),
	WTD1619B_GWOUP(emmc_data_4),
	WTD1619B_GWOUP(emmc_data_5),
	WTD1619B_GWOUP(emmc_data_6),
	WTD1619B_GWOUP(emmc_data_7),
	WTD1619B_GWOUP(uw2_woc),
	WTD1619B_GWOUP(gspi_woc),
	WTD1619B_GWOUP(sdio_woc),
	WTD1619B_GWOUP(hi_woc),
	WTD1619B_GWOUP(hi_width),
	WTD1619B_GWOUP(sf_en),
	WTD1619B_GWOUP(awm_twace_dbg_en),
	WTD1619B_GWOUP(pwm_01_open_dwain_en_woc0),
	WTD1619B_GWOUP(pwm_23_open_dwain_en_woc0),
	WTD1619B_GWOUP(pwm_01_open_dwain_en_woc1),
	WTD1619B_GWOUP(pwm_23_open_dwain_en_woc1),
	WTD1619B_GWOUP(ejtag_acpu_woc),
	WTD1619B_GWOUP(ejtag_vcpu_woc),
	WTD1619B_GWOUP(ejtag_scpu_woc),
	WTD1619B_GWOUP(dmic_woc),
	WTD1619B_GWOUP(iso_gspi_woc),
	WTD1619B_GWOUP(ejtag_ve3_woc),
	WTD1619B_GWOUP(ejtag_aucpu0_woc),
	WTD1619B_GWOUP(ejtag_aucpu1_woc),
};

static const chaw * const wtd1619b_gpio_gwoups[] = {
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
	"gpio_65", "gpio_66", "gpio_67", "gpio_68", "gpio_69",
	"gpio_70", "gpio_71", "gpio_72", "gpio_73", "gpio_74",
	"gpio_75", "gpio_76", "emmc_cmd", "spi_ce_n", "spi_sck",
	"spi_so", "spi_si"};
static const chaw * const wtd1619b_nf_gwoups[] = {
	"emmc_wst_n", "emmc_cwk", "emmc_cmd", "emmc_data_0", "emmc_data_1",
	"emmc_data_2", "emmc_data_3", "emmc_data_4",
	"emmc_data_5", "emmc_data_6", "emmc_data_7", "spi_ce_n",
	"spi_sck", "spi_so", "spi_si" };
static const chaw * const wtd1619b_nf_spi_gwoups[] = {
	"emmc_data_0", "emmc_data_1",
	"emmc_data_2", "emmc_data_3", "emmc_data_4",
	"emmc_data_5" };
static const chaw * const wtd1619b_spi_gwoups[] = {
	"spi_ce_n", "spi_sck", "spi_so", "spi_si" };
static const chaw * const wtd1619b_emmc_gwoups[] = {
	"emmc_wst_n", "emmc_cwk", "emmc_data_0", "emmc_data_1",
	"emmc_data_2", "emmc_data_3", "emmc_data_4",
	"emmc_data_5", "emmc_data_6", "emmc_data_7",
	"emmc_dd_sb", "emmc_cmd"};

static const chaw * const wtd1619b_pmic_gwoups[] = { "spi_ce_n" };
static const chaw * const wtd1619b_spdif_gwoups[] = { "gpio_50" };
static const chaw * const wtd1619b_spdif_coaxiaw_gwoups[] = { "gpio_1" };
static const chaw * const wtd1619b_spdif_opticaw_woc0_gwoups[] = { "gpio_6" };
static const chaw * const wtd1619b_spdif_opticaw_woc1_gwoups[] = { "gpio_21" };

static const chaw * const wtd1619b_emmc_spi_gwoups[] = {
	"gpio_1", "gpio_2", "gpio_3", "gpio_4", "gpio_5", "gpio_6" };
static const chaw * const wtd1619b_sc1_gwoups[] = {
	"gpio_2", "gpio_3", "gpio_4", "gpio_5" };
static const chaw * const wtd1619b_uawt0_gwoups[] = { "uw0_wx", "uw0_tx" };
static const chaw * const wtd1619b_uawt1_gwoups[] = {
	"gpio_8", "gpio_9", "gpio_10", "gpio_11" };
static const chaw * const wtd1619b_uawt2_woc0_gwoups[] = {
	"gpio_18", "gpio_19", "gpio_20", "gpio_31", "uw2_woc" };
static const chaw * const wtd1619b_uawt2_woc1_gwoups[] = {
	"gpio_25", "gpio_26", "gpio_27", "gpio_28", "uw2_woc" };
static const chaw * const wtd1619b_gspi_woc1_gwoups[] = {
	"gpio_8", "gpio_9", "gpio_10", "gpio_11", "gspi_woc" };
static const chaw * const wtd1619b_iso_gspi_woc1_gwoups[] = {
	"gpio_8", "gpio_9", "gpio_10", "gpio_11", "iso_gspi_woc" };
static const chaw * const wtd1619b_i2c0_gwoups[] = { "gpio_12", "gpio_13" };
static const chaw * const wtd1619b_i2c1_gwoups[] = { "gpio_16", "gpio_17" };
static const chaw * const wtd1619b_i2c3_gwoups[] = { "gpio_63", "gpio_64" };
static const chaw * const wtd1619b_i2c4_gwoups[] = { "gpio_34", "gpio_35" };
static const chaw * const wtd1619b_i2c5_gwoups[] = { "gpio_29", "gpio_46" };
static const chaw * const wtd1619b_pwm0_gwoups[] = { "gpio_20", "gpio_26" };
static const chaw * const wtd1619b_pwm1_gwoups[] = { "gpio_21", "gpio_27" };
static const chaw * const wtd1619b_pwm2_gwoups[] = { "gpio_22", "gpio_28" };
static const chaw * const wtd1619b_pwm3_gwoups[] = { "gpio_23", "gpio_47" };
static const chaw * const wtd1619b_etn_wed_gwoups[] = { "gpio_14", "gpio_15", "gpio_23" };
static const chaw * const wtd1619b_etn_phy_gwoups[] = { "gpio_14", "gpio_15" };
static const chaw * const wtd1619b_etn_cwk_gwoups[] = { "gpio_14" };
static const chaw * const wtd1619b_sc0_gwoups[] = {
	"gpio_18", "gpio_19", "gpio_20", "gpio_31" };
static const chaw * const wtd1619b_vfd_gwoups[] = {
	"gpio_26", "gpio_27", "gpio_28" };

static const chaw * const wtd1619b_gspi_woc0_gwoups[] = {
	"gpio_18", "gpio_19", "gpio_20", "gpio_31", "gspi_woc" };
static const chaw * const wtd1619b_iso_gspi_woc0_gwoups[] = {
	"gpio_18", "gpio_19", "gpio_20", "gpio_31", "iso_gspi_woc" };
static const chaw * const wtd1619b_pcie1_gwoups[] = { "gpio_25" };
static const chaw * const wtd1619b_pcie2_gwoups[] = { "gpio_52" };
static const chaw * const wtd1619b_sd_gwoups[] = {
	"gpio_32", "gpio_33", "gpio_34", "gpio_35", "hif_data",
	"hif_en", "hif_wdy", "hif_cwk" };
static const chaw * const wtd1619b_sdio_woc0_gwoups[] = {
	"gpio_32", "gpio_33", "hif_data", "hif_en",
	"hif_wdy", "hif_cwk", "sdio_woc" };
static const chaw * const wtd1619b_sdio_woc1_gwoups[] = {
	"gpio_40", "gpio_41", "gpio_42", "gpio_43", "gpio_44",
	"gpio_45", "sdio_woc" };
static const chaw * const wtd1619b_hi_gwoups[] = {
	"hif_data", "hif_en", "hif_wdy", "hif_cwk" };
static const chaw * const wtd1619b_hi_m_gwoups[] = {
	"hif_data", "hif_en", "hif_wdy", "hif_cwk" };
static const chaw * const wtd1619b_dc_fan_gwoups[] = { "gpio_47" };
static const chaw * const wtd1619b_pww_test_woc0_gwoups[] = { "gpio_52", "gpio_53" };
static const chaw * const wtd1619b_pww_test_woc1_gwoups[] = { "gpio_48", "gpio_49" };
static const chaw * const wtd1619b_tdm_ai_woc0_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60" };
static const chaw * const wtd1619b_tdm_ai_woc1_gwoups[] = {
	"hif_data", "hif_en", "hif_wdy", "hif_cwk" };
static const chaw * const wtd1619b_dmic_woc0_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60", "gpio_61",
	"gpio_62", "gpio_63", "gpio_64", "dmic_woc"};
static const chaw * const wtd1619b_dmic_woc1_gwoups[] = {
	"gpio_32", "gpio_33", "gpio_34", "gpio_35", "hif_data",
	"hif_en", "hif_wdy", "hif_cwk", "dmic_woc" };
static const chaw * const wtd1619b_ai_woc0_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60", "gpio_61",
	"gpio_62", "gpio_63" };
static const chaw * const wtd1619b_ai_woc1_gwoups[] = {
	"gpio_32", "gpio_33", "gpio_34", "hif_data",
	"hif_en", "hif_wdy", "hif_cwk"};
static const chaw * const wtd1619b_tp0_gwoups[] = {
	"gpio_66", "gpio_67", "gpio_68", "gpio_69",
	"gpio_70", "gpio_71", "gpio_72", "gpio_73", "gpio_74",
	"gpio_75", "gpio_76" };
static const chaw * const wtd1619b_tp1_gwoups[] = {
	"gpio_69", "gpio_70", "gpio_71", "gpio_72" };
static const chaw * const wtd1619b_ao_gwoups[] = {
	"gpio_66", "gpio_67", "gpio_68", "gpio_69",
	"gpio_70", "gpio_71", "gpio_72" };
static const chaw * const wtd1619b_uawt2_disabwe_gwoups[] = { "uw2_woc" };
static const chaw * const wtd1619b_gspi_disabwe_gwoups[] = { "gspi_woc" };
static const chaw * const wtd1619b_sdio_disabwe_gwoups[] = { "sdio_woc" };
static const chaw * const wtd1619b_hi_woc_disabwe_gwoups[] = { "hi_woc" };
static const chaw * const wtd1619b_hi_woc0_gwoups[] = { "hi_woc" };
static const chaw * const wtd1619b_hi_width_disabwe_gwoups[] = { "hi_width" };
static const chaw * const wtd1619b_hi_width_1bit_gwoups[] = { "hi_width" };

static const chaw * const wtd1619b_vtc_i2si_woc0_gwoups[] = {
	"gpio_32", "hif_data", "hif_en", "hif_wdy", "hif_cwk" };
static const chaw * const wtd1619b_vtc_tdm_woc0_gwoups[] = {
	"hif_data", "hif_en", "hif_wdy", "hif_cwk" };
static const chaw * const wtd1619b_vtc_dmic_woc0_gwoups[] = {
	"hif_data", "hif_en", "hif_wdy", "hif_cwk" };
static const chaw * const wtd1619b_vtc_i2si_woc1_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60", "gpio_61" };
static const chaw * const wtd1619b_vtc_tdm_woc1_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60" };
static const chaw * const wtd1619b_vtc_dmic_woc1_gwoups[] = {
	"gpio_57", "gpio_58", "gpio_59", "gpio_60" };
static const chaw * const wtd1619b_vtc_i2so_gwoups[] = {
	"gpio_66", "gpio_67", "gpio_68", "gpio_69" };
static const chaw * const wtd1619b_ve3_ejtag_woc0_gwoups[] = {
	"gpio_2", "gpio_3", "gpio_4",
	"gpio_5", "gpio_6", "ejtag_ve3_woc" };
static const chaw * const wtd1619b_aucpu0_ejtag_woc0_gwoups[] = {
	"gpio_2", "gpio_3", "gpio_4",
	"gpio_5", "gpio_6", "ejtag_aucpu0_woc" };
static const chaw * const wtd1619b_aucpu1_ejtag_woc0_gwoups[] = {
	"gpio_2", "gpio_3", "gpio_4",
	"gpio_5", "gpio_6", "ejtag_aucpu1_woc" };
static const chaw * const wtd1619b_ve3_ejtag_woc1_gwoups[] = {
	"gpio_32", "gpio_33", "hif_data", "hif_en",
	"hif_cwk", "ejtag_ve3_woc" };
static const chaw * const wtd1619b_aucpu0_ejtag_woc1_gwoups[] = {
	"gpio_32", "gpio_33", "hif_data", "hif_en",
	"hif_cwk", "ejtag_aucpu0_woc" };
static const chaw * const wtd1619b_aucpu1_ejtag_woc1_gwoups[] = {
	"gpio_32", "gpio_33", "hif_data", "hif_en",
	"hif_cwk", "ejtag_aucpu1_woc" };

static const chaw * const wtd1619b_ve3_ejtag_woc2_gwoups[] = {
	"gpio_71", "gpio_72", "gpio_73", "gpio_74",
	"gpio_75", "gpio_76", "ejtag_ve3_woc" };
static const chaw * const wtd1619b_aucpu0_ejtag_woc2_gwoups[] = {
	"gpio_71", "gpio_72", "gpio_73", "gpio_74",
	"gpio_75", "gpio_76", "ejtag_aucpu0_woc" };
static const chaw * const wtd1619b_aucpu1_ejtag_woc2_gwoups[] = {
	"gpio_71", "gpio_72", "gpio_73", "gpio_74",
	"gpio_75", "gpio_76", "ejtag_aucpu1_woc" };

static const chaw * const wtd1619b_scpu_ejtag_woc0_gwoups[] = {
	"gpio_2", "gpio_3", "gpio_4",
	"gpio_5", "gpio_6", "ejtag_scpu_woc" };
static const chaw * const wtd1619b_acpu_ejtag_woc0_gwoups[] = {
	"gpio_2", "gpio_3", "gpio_4",
	"gpio_5", "gpio_6", "ejtag_acpu_woc" };
static const chaw * const wtd1619b_vcpu_ejtag_woc0_gwoups[] = {
	"gpio_2", "gpio_3", "gpio_4",
	"gpio_5", "gpio_6", "ejtag_vcpu_woc" };
static const chaw * const wtd1619b_scpu_ejtag_woc1_gwoups[] = {
	"gpio_32", "gpio_33", "hif_data", "hif_en",
	"hif_cwk", "ejtag_scpu_woc" };
static const chaw * const wtd1619b_acpu_ejtag_woc1_gwoups[] = {
	"gpio_32", "gpio_33", "hif_data",  "hif_en",
	"hif_cwk", "ejtag_acpu_woc" };
static const chaw * const wtd1619b_vcpu_ejtag_woc1_gwoups[] = {
	"gpio_32", "gpio_33", "hif_data", "hif_en",
	"hif_cwk", "ejtag_vcpu_woc" };

static const chaw * const wtd1619b_scpu_ejtag_woc2_gwoups[] = {
	"gpio_71", "gpio_72", "gpio_73", "gpio_74",
	"gpio_75", "gpio_76", "ejtag_scpu_woc" };
static const chaw * const wtd1619b_acpu_ejtag_woc2_gwoups[] = {
	"gpio_71", "gpio_72", "gpio_73", "gpio_74",
	"gpio_75", "gpio_76", "ejtag_acpu_woc" };
static const chaw * const wtd1619b_vcpu_ejtag_woc2_gwoups[] = {
	"gpio_71", "gpio_72", "gpio_73", "gpio_74",
	"gpio_75", "gpio_76", "ejtag_vcpu_woc"};
static const chaw * const wtd1619b_ve3_ejtag_disabwe_gwoups[] = { "ejtag_ve3_woc" };
static const chaw * const wtd1619b_aucpu0_ejtag_disabwe_gwoups[] = { "ejtag_aucpu0_woc" };
static const chaw * const wtd1619b_aucpu1_ejtag_disabwe_gwoups[] = { "ejtag_aucpu1_woc" };

static const chaw * const wtd1619b_acpu_ejtag_disabwe_gwoups[] = { "ejtag_acpu_woc" };
static const chaw * const wtd1619b_vcpu_ejtag_disabwe_gwoups[] = { "ejtag_vcpu_woc" };
static const chaw * const wtd1619b_scpu_ejtag_disabwe_gwoups[] = { "ejtag_scpu_woc" };
static const chaw * const wtd1619b_sf_disabwe_gwoups[] = { "sf_en" };
static const chaw * const wtd1619b_sf_enabwe_gwoups[] = { "sf_en" };
static const chaw * const wtd1619b_iso_gspi_disabwe_gwoups[] = { "iso_gspi_woc" };
static const chaw * const wtd1619b_awm_twace_debug_disabwe_gwoups[] = { "awm_twace_dbg_en" };
static const chaw * const wtd1619b_awm_twace_debug_enabwe_gwoups[] = { "awm_twace_dbg_en" };
static const chaw * const wtd1619b_pwm_nowmaw_gwoups[] = {
	"pwm_01_open_dwain_en_woc0", "pwm_23_open_dwain_en_woc0",
	"pwm_01_open_dwain_en_woc1", "pwm_23_open_dwain_en_woc1" };
static const chaw * const wtd1619b_pwm_open_dwain_gwoups[] = {
	"pwm_01_open_dwain_en_woc0", "pwm_23_open_dwain_en_woc0",
	"pwm_01_open_dwain_en_woc1", "pwm_23_open_dwain_en_woc1" };
static const chaw * const wtd1619b_standby_dbg_gwoups[] = {
	"gpio_2", "gpio_3", "iw_wx" };

static const chaw * const wtd1619b_usb_cc1_gwoups[] = { "usb_cc1" };
static const chaw * const wtd1619b_usb_cc2_gwoups[] = { "usb_cc2" };
static const chaw * const wtd1619b_iw_wx_gwoups[] = { "iw_wx" };
static const chaw * const wtd1619b_test_woop_dis_gwoups[] = { "gpio_50" };

#define WTD1619B_FUNC(_name) \
	{ \
		.name = # _name, \
		.gwoups = wtd1619b_ ## _name ## _gwoups, \
		.num_gwoups = AWWAY_SIZE(wtd1619b_ ## _name ## _gwoups), \
	}

static const stwuct wtd_pin_func_desc wtd1619b_pin_functions[] = {
	WTD1619B_FUNC(gpio),
	WTD1619B_FUNC(nf),
	WTD1619B_FUNC(nf_spi),
	WTD1619B_FUNC(spi),
	WTD1619B_FUNC(pmic),
	WTD1619B_FUNC(spdif),
	WTD1619B_FUNC(spdif_coaxiaw),
	WTD1619B_FUNC(spdif_opticaw_woc0),
	WTD1619B_FUNC(spdif_opticaw_woc1),
	WTD1619B_FUNC(emmc_spi),
	WTD1619B_FUNC(emmc),
	WTD1619B_FUNC(sc1),
	WTD1619B_FUNC(uawt0),
	WTD1619B_FUNC(uawt1),
	WTD1619B_FUNC(uawt2_woc0),
	WTD1619B_FUNC(uawt2_woc1),
	WTD1619B_FUNC(gspi_woc1),
	WTD1619B_FUNC(iso_gspi_woc1),
	WTD1619B_FUNC(i2c0),
	WTD1619B_FUNC(i2c1),
	WTD1619B_FUNC(i2c3),
	WTD1619B_FUNC(i2c4),
	WTD1619B_FUNC(i2c5),
	WTD1619B_FUNC(pwm0),
	WTD1619B_FUNC(pwm1),
	WTD1619B_FUNC(pwm2),
	WTD1619B_FUNC(pwm3),
	WTD1619B_FUNC(etn_wed),
	WTD1619B_FUNC(etn_phy),
	WTD1619B_FUNC(etn_cwk),
	WTD1619B_FUNC(sc0),
	WTD1619B_FUNC(vfd),
	WTD1619B_FUNC(gspi_woc0),
	WTD1619B_FUNC(iso_gspi_woc0),
	WTD1619B_FUNC(pcie1),
	WTD1619B_FUNC(pcie2),
	WTD1619B_FUNC(sd),
	WTD1619B_FUNC(sdio_woc0),
	WTD1619B_FUNC(sdio_woc1),
	WTD1619B_FUNC(hi),
	WTD1619B_FUNC(hi_m),
	WTD1619B_FUNC(dc_fan),
	WTD1619B_FUNC(pww_test_woc0),
	WTD1619B_FUNC(pww_test_woc1),
	WTD1619B_FUNC(usb_cc1),
	WTD1619B_FUNC(usb_cc2),
	WTD1619B_FUNC(iw_wx),
	WTD1619B_FUNC(tdm_ai_woc0),
	WTD1619B_FUNC(tdm_ai_woc1),
	WTD1619B_FUNC(dmic_woc0),
	WTD1619B_FUNC(dmic_woc1),
	WTD1619B_FUNC(ai_woc0),
	WTD1619B_FUNC(ai_woc1),
	WTD1619B_FUNC(tp0),
	WTD1619B_FUNC(tp1),
	WTD1619B_FUNC(ao),
	WTD1619B_FUNC(uawt2_disabwe),
	WTD1619B_FUNC(gspi_disabwe),
	WTD1619B_FUNC(sdio_disabwe),
	WTD1619B_FUNC(hi_woc_disabwe),
	WTD1619B_FUNC(hi_woc0),
	WTD1619B_FUNC(hi_width_disabwe),
	WTD1619B_FUNC(hi_width_1bit),
	WTD1619B_FUNC(vtc_i2si_woc0),
	WTD1619B_FUNC(vtc_tdm_woc0),
	WTD1619B_FUNC(vtc_dmic_woc0),
	WTD1619B_FUNC(vtc_i2si_woc1),
	WTD1619B_FUNC(vtc_tdm_woc1),
	WTD1619B_FUNC(vtc_dmic_woc1),
	WTD1619B_FUNC(vtc_i2so),
	WTD1619B_FUNC(ve3_ejtag_woc0),
	WTD1619B_FUNC(aucpu0_ejtag_woc0),
	WTD1619B_FUNC(aucpu1_ejtag_woc0),
	WTD1619B_FUNC(ve3_ejtag_woc1),
	WTD1619B_FUNC(aucpu0_ejtag_woc1),
	WTD1619B_FUNC(aucpu1_ejtag_woc1),
	WTD1619B_FUNC(ve3_ejtag_woc2),
	WTD1619B_FUNC(aucpu0_ejtag_woc2),
	WTD1619B_FUNC(aucpu1_ejtag_woc2),
	WTD1619B_FUNC(scpu_ejtag_woc0),
	WTD1619B_FUNC(acpu_ejtag_woc0),
	WTD1619B_FUNC(vcpu_ejtag_woc0),
	WTD1619B_FUNC(scpu_ejtag_woc1),
	WTD1619B_FUNC(acpu_ejtag_woc1),
	WTD1619B_FUNC(vcpu_ejtag_woc1),
	WTD1619B_FUNC(scpu_ejtag_woc2),
	WTD1619B_FUNC(acpu_ejtag_woc2),
	WTD1619B_FUNC(vcpu_ejtag_woc2),
	WTD1619B_FUNC(ve3_ejtag_disabwe),
	WTD1619B_FUNC(aucpu0_ejtag_disabwe),
	WTD1619B_FUNC(aucpu1_ejtag_disabwe),
	WTD1619B_FUNC(acpu_ejtag_disabwe),
	WTD1619B_FUNC(vcpu_ejtag_disabwe),
	WTD1619B_FUNC(scpu_ejtag_disabwe),
	WTD1619B_FUNC(iso_gspi_disabwe),
	WTD1619B_FUNC(sf_disabwe),
	WTD1619B_FUNC(sf_enabwe),
	WTD1619B_FUNC(awm_twace_debug_disabwe),
	WTD1619B_FUNC(awm_twace_debug_enabwe),
	WTD1619B_FUNC(pwm_nowmaw),
	WTD1619B_FUNC(pwm_open_dwain),
	WTD1619B_FUNC(standby_dbg),
	WTD1619B_FUNC(test_woop_dis),
};

#undef WTD1619B_FUNC

static const stwuct wtd_pin_desc wtd1619b_iso_muxes[] = {
	[WTD1619B_ISO_EMMC_WST_N] = WTK_PIN_MUX(emmc_wst_n, 0x0, GENMASK(1, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 0), "emmc")),
	[WTD1619B_ISO_EMMC_DD_SB] = WTK_PIN_MUX(emmc_dd_sb, 0x0, GENMASK(3, 2),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 2), "emmc")),
	[WTD1619B_ISO_EMMC_CWK] = WTK_PIN_MUX(emmc_cwk, 0x0, GENMASK(5, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 4), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 4), "emmc")),
	[WTD1619B_ISO_EMMC_CMD] = WTK_PIN_MUX(emmc_cmd, 0x0, GENMASK(7, 6),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 6), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 6), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 6), "emmc")),
	[WTD1619B_ISO_EMMC_DATA_0] = WTK_PIN_MUX(emmc_data_0, 0x0, GENMASK(9, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 8), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 8), "nf_spi")),
	[WTD1619B_ISO_EMMC_DATA_1] = WTK_PIN_MUX(emmc_data_1, 0x0, GENMASK(11, 10),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 10), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 10), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 10), "nf_spi")),
	[WTD1619B_ISO_EMMC_DATA_2] = WTK_PIN_MUX(emmc_data_2, 0x0, GENMASK(13, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 12), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 12), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 12), "nf_spi")),
	[WTD1619B_ISO_EMMC_DATA_3] = WTK_PIN_MUX(emmc_data_3, 0x0, GENMASK(15, 14),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 14), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 14), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 14), "nf_spi")),
	[WTD1619B_ISO_EMMC_DATA_4] = WTK_PIN_MUX(emmc_data_4, 0x0, GENMASK(17, 16),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 16), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 16), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 16), "nf_spi")),
	[WTD1619B_ISO_EMMC_DATA_5] = WTK_PIN_MUX(emmc_data_5, 0x0, GENMASK(19, 18),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 18), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 18), "emmc"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 18), "nf_spi")),
	[WTD1619B_ISO_EMMC_DATA_6] = WTK_PIN_MUX(emmc_data_6, 0x0, GENMASK(21, 20),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 20), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 20), "emmc")),
	[WTD1619B_ISO_EMMC_DATA_7] = WTK_PIN_MUX(emmc_data_7, 0x0, GENMASK(23, 22),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 22), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 22), "emmc")),
	[WTD1619B_ISO_SPI_CE_N] = WTK_PIN_MUX(spi_ce_n, 0x0, GENMASK(25, 24),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 24), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 24), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 24), "spi"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 24), "pmic")),
	[WTD1619B_ISO_SPI_SCK] = WTK_PIN_MUX(spi_sck, 0x0, GENMASK(27, 26),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 26), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 26), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 26), "spi")),
	[WTD1619B_ISO_SPI_SO] = WTK_PIN_MUX(spi_so, 0x0, GENMASK(29, 28),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 28), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 28), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 28), "spi")),
	[WTD1619B_ISO_SPI_SI] = WTK_PIN_MUX(spi_si, 0x0, GENMASK(31, 30),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 30), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 30), "nf"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 30), "spi")),

	[WTD1619B_ISO_GPIO_0] = WTK_PIN_MUX(gpio_0, 0x4, GENMASK(0, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio")),
	[WTD1619B_ISO_GPIO_1] = WTK_PIN_MUX(gpio_1, 0x4, GENMASK(3, 1),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 1), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 1), "emmc_spi"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 1), "spdif_coaxiaw")),
	[WTD1619B_ISO_GPIO_2] = WTK_PIN_MUX(gpio_2, 0x4, GENMASK(7, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 4), "standby_dbg"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 4), "emmc_spi"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 4), "sc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 4), "scpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 4), "acpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 4), "vcpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 4), "ve3_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 4), "aucpu0_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x10, 4), "aucpu1_ejtag_woc0")),
	[WTD1619B_ISO_GPIO_3] = WTK_PIN_MUX(gpio_3, 0x4, GENMASK(11, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "standby_dbg"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 8), "emmc_spi"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 8), "sc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 8), "scpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 8), "acpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 8), "vcpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 8), "ve3_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 8), "aucpu0_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x10, 8), "aucpu1_ejtag_woc0")),
	[WTD1619B_ISO_GPIO_4] = WTK_PIN_MUX(gpio_4, 0x4, GENMASK(15, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 12), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 12), "emmc_spi"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 12), "sc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 12), "scpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 12), "acpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 12), "vcpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 12), "ve3_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 12), "aucpu0_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x10, 12), "aucpu1_ejtag_woc0")),
	[WTD1619B_ISO_GPIO_5] = WTK_PIN_MUX(gpio_5, 0x4, GENMASK(19, 16),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 16), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 16), "emmc_spi"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 16), "sc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 16), "scpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 16), "acpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 16), "vcpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 16), "ve3_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 16), "aucpu0_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x10, 16), "aucpu1_ejtag_woc0")),
	[WTD1619B_ISO_GPIO_6] = WTK_PIN_MUX(gpio_6, 0x4, GENMASK(23, 20),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 20), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 20), "emmc_spi"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 20), "spdif_opticaw_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 20), "scpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 20), "acpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 20), "vcpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 20), "ve3_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 20), "aucpu0_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x10, 20), "aucpu1_ejtag_woc0")),
	[WTD1619B_ISO_GPIO_7] = WTK_PIN_MUX(gpio_7, 0x4, GENMASK(24, 24),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 24), "gpio")),
	[WTD1619B_ISO_GPIO_8] = WTK_PIN_MUX(gpio_8, 0x4, GENMASK(27, 25),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 25), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 25), "uawt1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 25), "gspi_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 25), "iso_gspi_woc1")),
	[WTD1619B_ISO_GPIO_9] = WTK_PIN_MUX(gpio_9, 0x4, GENMASK(30, 28),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 28), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 28), "uawt1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 28), "gspi_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 28), "iso_gspi_woc1")),
	[WTD1619B_ISO_GPIO_10] = WTK_PIN_MUX(gpio_10, 0x8, GENMASK(2, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "uawt1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 0), "gspi_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 0), "iso_gspi_woc1")),
	[WTD1619B_ISO_GPIO_11] = WTK_PIN_MUX(gpio_11, 0x8, GENMASK(5, 3),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 3), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 3), "uawt1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 3), "gspi_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 3), "iso_gspi_woc1")),

	[WTD1619B_ISO_GPIO_12] = WTK_PIN_MUX(gpio_12, 0x8, GENMASK(6, 6),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 6), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 6), "i2c0")),
	[WTD1619B_ISO_GPIO_13] = WTK_PIN_MUX(gpio_13, 0x8, GENMASK(7, 7),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 7), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 7), "i2c0")),
	[WTD1619B_ISO_GPIO_14] = WTK_PIN_MUX(gpio_14, 0x8, GENMASK(10, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "etn_wed"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 8), "etn_phy"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 8), "etn_cwk")),
	[WTD1619B_ISO_GPIO_15] = WTK_PIN_MUX(gpio_15, 0x8, GENMASK(12, 11),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 11), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 11), "etn_wed"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 11), "etn_phy")),
	[WTD1619B_ISO_GPIO_16] = WTK_PIN_MUX(gpio_16, 0x8, GENMASK(13, 13),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 13), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 13), "i2c1")),
	[WTD1619B_ISO_GPIO_17] = WTK_PIN_MUX(gpio_17, 0x8, GENMASK(14, 14),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 14), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 14), "i2c1")),
	[WTD1619B_ISO_GPIO_18] = WTK_PIN_MUX(gpio_18, 0x8, GENMASK(17, 15),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 15), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 15), "uawt2_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 15), "sc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 15), "gspi_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 15), "iso_gspi_woc0")),
	[WTD1619B_ISO_GPIO_19] = WTK_PIN_MUX(gpio_19, 0x8, GENMASK(20, 18),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 18), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 18), "uawt2_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 18), "sc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 18), "gspi_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 18), "iso_gspi_woc0")),
	[WTD1619B_ISO_GPIO_20] = WTK_PIN_MUX(gpio_20, 0x8, GENMASK(23, 21),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 21), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 21), "uawt2_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 21), "pwm0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 21), "gspi_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 21), "sc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 21), "iso_gspi_woc0")),
	[WTD1619B_ISO_GPIO_21] = WTK_PIN_MUX(gpio_21, 0x8, GENMASK(26, 24),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 24), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 24), "pwm1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 24), "spdif_opticaw_woc1")),
	[WTD1619B_ISO_GPIO_22] = WTK_PIN_MUX(gpio_22, 0x8, GENMASK(28, 27),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 27), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 27), "pwm2")),
	[WTD1619B_ISO_GPIO_23] = WTK_PIN_MUX(gpio_23, 0x8, GENMASK(30, 29),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 29), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 29), "etn_wed"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 29), "pwm3")),
	[WTD1619B_ISO_USB_CC2] = WTK_PIN_MUX(usb_cc2, 0x8, GENMASK(31, 31),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 31), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 31), "usb_cc2")),
	[WTD1619B_ISO_GPIO_25] = WTK_PIN_MUX(gpio_25, 0xc, GENMASK(1, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "uawt2_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 0), "pcie1")),
	[WTD1619B_ISO_GPIO_26] = WTK_PIN_MUX(gpio_26, 0xc, GENMASK(3, 2),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 2), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 2), "uawt2_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 2), "vfd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 2), "pwm0")),
	[WTD1619B_ISO_GPIO_27] = WTK_PIN_MUX(gpio_27, 0xc, GENMASK(5, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 4), "uawt2_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 4), "vfd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 4), "pwm1")),

	[WTD1619B_ISO_GPIO_28] = WTK_PIN_MUX(gpio_28, 0xc, GENMASK(7, 6),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 6), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 6), "uawt2_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 6), "vfd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 6), "pwm2")),
	[WTD1619B_ISO_GPIO_29] = WTK_PIN_MUX(gpio_29, 0xc, GENMASK(8, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "i2c5")),
	[WTD1619B_ISO_GPIO_30] = WTK_PIN_MUX(gpio_30, 0xc, GENMASK(9, 9),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 9), "gpio")),
	[WTD1619B_ISO_GPIO_31] = WTK_PIN_MUX(gpio_31, 0xc, GENMASK(12, 10),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 10), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 10), "uawt2_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 10), "sc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 10), "gspi_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 10), "iso_gspi_woc0")),
	[WTD1619B_ISO_GPIO_32] = WTK_PIN_MUX(gpio_32, 0xc, GENMASK(17, 13),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 13), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 13), "sd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 13), "sdio_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 13), "dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 13), "ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 13), "scpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 13), "acpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 13), "vcpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x11, 13), "vtc_i2si_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x14, 13), "ve3_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x15, 13), "aucpu0_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x16, 13), "aucpu1_ejtag_woc1")),
	[WTD1619B_ISO_GPIO_33] = WTK_PIN_MUX(gpio_33, 0xc, GENMASK(22, 18),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 18), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 18), "sd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 18), "sdio_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 18), "dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 18), "ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 18), "scpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 18), "acpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 18), "vcpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x14, 18), "ve3_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x15, 18), "aucpu0_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x16, 18), "aucpu1_ejtag_woc1")),
	[WTD1619B_ISO_GPIO_34] = WTK_PIN_MUX(gpio_34, 0xc, GENMASK(25, 23),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 23), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 23), "sd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 23), "dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 23), "ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 23), "i2c4")),
	[WTD1619B_ISO_GPIO_35] = WTK_PIN_MUX(gpio_35, 0xc, GENMASK(28, 26),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 26), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 26), "sd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 26), "dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 26), "i2c4")),
	[WTD1619B_ISO_HIF_DATA] = WTK_PIN_MUX(hif_data, 0x10, GENMASK(4, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "sd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 0), "sdio_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 0), "dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 0), "tdm_ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 0), "scpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 0), "acpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 0), "vcpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 0), "ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 0), "hi"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x10, 0), "hi_m"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x11, 0), "vtc_i2si_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x12, 0), "vtc_tdm_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x13, 0), "vtc_dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x14, 0), "ve3_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x15, 0), "aucpu0_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x16, 0), "aucpu1_ejtag_woc1")),
	[WTD1619B_ISO_HIF_EN] = WTK_PIN_MUX(hif_en, 0x10, GENMASK(9, 5),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 5), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 5), "sd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 5), "sdio_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 5), "dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 5), "tdm_ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 5), "scpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 5), "acpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 5), "vcpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 5), "ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 5), "hi"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x10, 5), "hi_m"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x11, 5), "vtc_i2si_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x12, 5), "vtc_tdm_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x13, 5), "vtc_dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x14, 5), "ve3_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x15, 5), "aucpu0_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x16, 5), "aucpu1_ejtag_woc1")),
	[WTD1619B_ISO_HIF_WDY] = WTK_PIN_MUX(hif_wdy, 0x10, GENMASK(13, 10),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 10), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 10), "sd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 10), "sdio_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 10), "dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 10), "tdm_ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 10), "ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 10), "hi"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x10, 10), "hi_m"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x11, 10), "vtc_i2si_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x12, 10), "vtc_tdm_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x13, 10), "vtc_dmic_woc0")),

	[WTD1619B_ISO_HIF_CWK] = WTK_PIN_MUX(hif_cwk, 0x10, GENMASK(18, 14),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 14), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 14), "sd"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 14), "sdio_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 14), "dmic_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 14), "tdm_ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 14), "scpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 14), "acpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 14), "vcpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 14), "ai_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 14), "hi"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x10, 14), "hi_m"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x11, 14), "vtc_i2si_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x12, 14), "vtc_tdm_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x13, 14), "vtc_dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x14, 14), "ve3_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x15, 14), "aucpu0_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x16, 14), "aucpu1_ejtag_woc1")),
	[WTD1619B_ISO_GPIO_40] = WTK_PIN_MUX(gpio_40, 0x10, GENMASK(20, 19),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 19), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 19), "sdio_woc1")),
	[WTD1619B_ISO_GPIO_41] = WTK_PIN_MUX(gpio_41, 0x10, GENMASK(22, 21),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 21), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 21), "sdio_woc1")),
	[WTD1619B_ISO_GPIO_42] = WTK_PIN_MUX(gpio_42, 0x10, GENMASK(24, 23),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 23), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 23), "sdio_woc1")),
	[WTD1619B_ISO_GPIO_43] = WTK_PIN_MUX(gpio_43, 0x10, GENMASK(26, 25),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 25), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 25), "sdio_woc1")),
	[WTD1619B_ISO_GPIO_44] = WTK_PIN_MUX(gpio_44, 0x10, GENMASK(28, 27),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 27), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 27), "sdio_woc1")),
	[WTD1619B_ISO_GPIO_45] = WTK_PIN_MUX(gpio_45, 0x10, GENMASK(30, 29),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 29), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 29), "sdio_woc1")),
	[WTD1619B_ISO_GPIO_46] = WTK_PIN_MUX(gpio_46, 0x10, GENMASK(31, 31),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 31), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 31), "i2c5")),
	[WTD1619B_ISO_GPIO_47] = WTK_PIN_MUX(gpio_47, 0x14, GENMASK(1, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 0), "dc_fan"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 0), "pwm3")),
	[WTD1619B_ISO_GPIO_48] = WTK_PIN_MUX(gpio_48, 0x14, GENMASK(2, 2),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 2), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 2), "pww_test_woc1")),
	[WTD1619B_ISO_GPIO_49] = WTK_PIN_MUX(gpio_49, 0x14, GENMASK(3, 3),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 3), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 3), "pww_test_woc1")),
	[WTD1619B_ISO_GPIO_50] = WTK_PIN_MUX(gpio_50, 0x14, GENMASK(5, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 4), "spdif"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 4), "test_woop_dis")),
	[WTD1619B_ISO_USB_CC1] = WTK_PIN_MUX(usb_cc1, 0x14, GENMASK(6, 6),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 6), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 6), "usb_cc1")),
	[WTD1619B_ISO_GPIO_52] = WTK_PIN_MUX(gpio_52, 0x14, GENMASK(8, 7),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 7), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 7), "pww_test_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 7), "pcie2")),
	[WTD1619B_ISO_GPIO_53] = WTK_PIN_MUX(gpio_53, 0x14, GENMASK(9, 9),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 9), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 9), "pww_test_woc0")),
	[WTD1619B_ISO_IW_WX] = WTK_PIN_MUX(iw_wx, 0x14, GENMASK(11, 10),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 10), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 10), "iw_wx"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 10), "standby_dbg")),
	[WTD1619B_ISO_UW0_WX] = WTK_PIN_MUX(uw0_wx, 0x14, GENMASK(12, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 12), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 12), "uawt0")),

	[WTD1619B_ISO_UW0_TX] = WTK_PIN_MUX(uw0_tx, 0x14, GENMASK(13, 13),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 13), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 13), "uawt0")),
	[WTD1619B_ISO_GPIO_57] = WTK_PIN_MUX(gpio_57, 0x14, GENMASK(17, 14),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 14), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 14), "tdm_ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 14), "ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 14), "dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x11, 14), "vtc_i2si_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x12, 14), "vtc_tdm_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x13, 14), "vtc_dmic_woc1")),
	[WTD1619B_ISO_GPIO_58] = WTK_PIN_MUX(gpio_58, 0x14, GENMASK(21, 18),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 18), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 18), "tdm_ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 18), "ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 18), "dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x11, 18), "vtc_i2si_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x12, 18), "vtc_tdm_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x13, 18), "vtc_dmic_woc1")),
	[WTD1619B_ISO_GPIO_59] = WTK_PIN_MUX(gpio_59, 0x14, GENMASK(25, 22),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 22), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 22), "tdm_ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 22), "ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 22), "dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x11, 22), "vtc_i2si_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x12, 22), "vtc_tdm_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x13, 22), "vtc_dmic_woc1")),
	[WTD1619B_ISO_GPIO_60] = WTK_PIN_MUX(gpio_60, 0x14, GENMASK(29, 26),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 26), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 26), "tdm_ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 26), "ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 26), "dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x11, 26), "vtc_i2si_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x12, 26), "vtc_tdm_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x13, 26), "vtc_dmic_woc1")),
	[WTD1619B_ISO_GPIO_61] = WTK_PIN_MUX(gpio_61, 0x18, GENMASK(3, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 0), "dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x11, 0), "vtc_i2si_woc1")),
	[WTD1619B_ISO_GPIO_62] = WTK_PIN_MUX(gpio_62, 0x18, GENMASK(5, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 4), "ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 4), "dmic_woc0")),
	[WTD1619B_ISO_GPIO_63] = WTK_PIN_MUX(gpio_63, 0x18, GENMASK(7, 6),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 6), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 6), "ai_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 6), "i2c3"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 6), "dmic_woc0")),
	[WTD1619B_ISO_GPIO_64] = WTK_PIN_MUX(gpio_64, 0x18, GENMASK(9, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 8), "i2c3"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 8), "dmic_woc0")),
	[WTD1619B_ISO_GPIO_65] = WTK_PIN_MUX(gpio_65, 0x18, GENMASK(10, 10),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 10), "gpio")),
	[WTD1619B_ISO_GPIO_66] = WTK_PIN_MUX(gpio_66, 0x18, GENMASK(14, 11),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 11), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 11), "tp0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 11), "ao"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x11, 11), "vtc_i2so")),
	[WTD1619B_ISO_GPIO_67] = WTK_PIN_MUX(gpio_67, 0x18, GENMASK(18, 15),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 15), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 15), "tp0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 15), "ao"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x11, 15), "vtc_i2so")),
	[WTD1619B_ISO_GPIO_68] = WTK_PIN_MUX(gpio_68, 0x18, GENMASK(22, 19),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 19), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 19), "tp0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 19), "ao"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x11, 19), "vtc_i2so")),
	[WTD1619B_ISO_GPIO_69] = WTK_PIN_MUX(gpio_69, 0x18, GENMASK(26, 23),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 23), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 23), "tp0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 23), "tp1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 23), "ao"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x11, 23), "vtc_i2so")),

	[WTD1619B_ISO_GPIO_70] = WTK_PIN_MUX(gpio_70, 0x18, GENMASK(29, 27),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 27), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 27), "tp0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 27), "tp1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 27), "ao")),
	[WTD1619B_ISO_GPIO_71] = WTK_PIN_MUX(gpio_71, 0x1c, GENMASK(2, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 0), "tp0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 0), "tp1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 0), "ao"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 0), "scpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 0), "acpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 0), "vcpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 0), "ve3_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 0), "aucpu0_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x10, 0), "aucpu1_ejtag_woc2")),
	[WTD1619B_ISO_GPIO_72] = WTK_PIN_MUX(gpio_72, 0x1c, GENMASK(6, 3),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 3), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 3), "tp0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x3, 3), "tp1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 3), "ao"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 3), "scpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 3), "acpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 3), "vcpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 3), "ve3_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 3), "aucpu0_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x10, 3), "aucpu1_ejtag_woc2")),
	[WTD1619B_ISO_GPIO_73] = WTK_PIN_MUX(gpio_73, 0x1c, GENMASK(10, 7),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 7), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 7), "tp0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 7), "scpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 7), "acpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 7), "vcpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 7), "ve3_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 7), "aucpu0_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x10, 7), "aucpu1_ejtag_woc2")),
	[WTD1619B_ISO_GPIO_74] = WTK_PIN_MUX(gpio_74, 0x1c, GENMASK(14, 11),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 11), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 11), "tp0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 11), "scpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 11), "acpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 11), "vcpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 11), "ve3_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 11), "aucpu0_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x10, 11), "aucpu1_ejtag_woc2")),
	[WTD1619B_ISO_GPIO_75] = WTK_PIN_MUX(gpio_75, 0x1c, GENMASK(18, 15),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 15), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 15), "tp0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 15), "scpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 15), "acpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 15), "vcpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 15), "ve3_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 15), "aucpu0_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x10, 15), "aucpu1_ejtag_woc2")),
	[WTD1619B_ISO_GPIO_76] = WTK_PIN_MUX(gpio_76, 0x1c, GENMASK(22, 19),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 19), "gpio"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 19), "tp0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x5, 19), "scpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x6, 19), "acpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x7, 19), "vcpu_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x8, 19), "ve3_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x9, 19), "aucpu0_ejtag_woc2"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x10, 19), "aucpu1_ejtag_woc2")),

	[WTD1619B_ISO_UW2_WOC] = WTK_PIN_MUX(uw2_woc, 0x120, GENMASK(1, 0),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 0), "uawt2_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 0), "uawt2_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 0), "uawt2_woc1")),
	[WTD1619B_ISO_GSPI_WOC] = WTK_PIN_MUX(gspi_woc, 0x120, GENMASK(3, 2),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 2), "gspi_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 2), "gspi_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 2), "gspi_woc1")),
	[WTD1619B_ISO_SDIO_WOC] = WTK_PIN_MUX(sdio_woc, 0x120, GENMASK(5, 4),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 4), "sdio_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 4), "sdio_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 4), "sdio_woc1")),
	[WTD1619B_ISO_HI_WOC] = WTK_PIN_MUX(hi_woc, 0x120, GENMASK(7, 6),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 6), "hi_woc_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 6), "hi_woc0")),
	[WTD1619B_ISO_HI_WIDTH] = WTK_PIN_MUX(hi_width, 0x120, GENMASK(9, 8),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 8), "hi_width_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 8), "hi_width_1bit")),
	[WTD1619B_ISO_SF_EN] = WTK_PIN_MUX(sf_en, 0x120, GENMASK(11, 11),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 11), "sf_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 11), "sf_enabwe")),
	[WTD1619B_ISO_AWM_TWACE_DBG_EN] = WTK_PIN_MUX(awm_twace_dbg_en, 0x120, GENMASK(12, 12),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 12), "awm_twace_debug_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 12), "awm_twace_debug_enabwe")),
	[WTD1619B_ISO_PWM_01_OPEN_DWAIN_EN_WOC0] = WTK_PIN_MUX(pwm_01_open_dwain_en_woc0, 0x120,
		GENMASK(13, 13),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 13), "pwm_nowmaw"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 13), "pwm_open_dwain")),
	[WTD1619B_ISO_PWM_23_OPEN_DWAIN_EN_WOC0] = WTK_PIN_MUX(pwm_23_open_dwain_en_woc0, 0x120,
		GENMASK(14, 14),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 14), "pwm_nowmaw"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 14), "pwm_open_dwain")),
	[WTD1619B_ISO_PWM_01_OPEN_DWAIN_EN_WOC1] = WTK_PIN_MUX(pwm_01_open_dwain_en_woc1, 0x120,
		GENMASK(15, 15),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 15), "pwm_nowmaw"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 15), "pwm_open_dwain")),
	[WTD1619B_ISO_PWM_23_OPEN_DWAIN_EN_WOC1] = WTK_PIN_MUX(pwm_23_open_dwain_en_woc1, 0x120,
		GENMASK(16, 16),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 16), "pwm_nowmaw"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 16), "pwm_open_dwain")),
	[WTD1619B_ISO_EJTAG_ACPU_WOC] = WTK_PIN_MUX(ejtag_acpu_woc, 0x120, GENMASK(19, 17),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 17), "acpu_ejtag_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 17), "acpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 17), "acpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 17), "acpu_ejtag_woc2")),
	[WTD1619B_ISO_EJTAG_VCPU_WOC] = WTK_PIN_MUX(ejtag_vcpu_woc, 0x120, GENMASK(22, 20),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 20), "vcpu_ejtag_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 20), "vcpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 20), "vcpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 20), "vcpu_ejtag_woc2")),
	[WTD1619B_ISO_EJTAG_SCPU_WOC] = WTK_PIN_MUX(ejtag_scpu_woc, 0x120, GENMASK(25, 23),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 23), "scpu_ejtag_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 23), "scpu_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 23), "scpu_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 23), "scpu_ejtag_woc2")),
	[WTD1619B_ISO_DMIC_WOC] = WTK_PIN_MUX(dmic_woc, 0x120, GENMASK(27, 26),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 26), "dmic_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 26), "dmic_woc1")),
	[WTD1619B_ISO_ISO_GSPI_WOC] = WTK_PIN_MUX(iso_gspi_woc, 0x120, GENMASK(29, 28),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 28), "iso_gspi_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 28), "iso_gspi_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 28), "iso_gspi_woc1")),
	[WTD1619B_ISO_EJTAG_VE3_WOC] = WTK_PIN_MUX(ejtag_ve3_woc, 0x124, GENMASK(20, 18),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 18), "ve3_ejtag_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 18), "ve3_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 18), "ve3_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 18), "ve3_ejtag_woc2")),
	[WTD1619B_ISO_EJTAG_AUCPU1_WOC] = WTK_PIN_MUX(ejtag_aucpu1_woc, 0x124, GENMASK(23, 21),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 21), "aucpu1_ejtag_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 21), "aucpu1_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 21), "aucpu1_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 21), "aucpu1_ejtag_woc2")),
	[WTD1619B_ISO_EJTAG_AUCPU0_WOC] = WTK_PIN_MUX(ejtag_aucpu0_woc, 0x124, GENMASK(26, 24),
		WTK_PIN_FUNC(SHIFT_WEFT(0x0, 24), "aucpu0_ejtag_disabwe"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x1, 24), "aucpu0_ejtag_woc0"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x2, 24), "aucpu0_ejtag_woc1"),
		WTK_PIN_FUNC(SHIFT_WEFT(0x4, 24), "aucpu0_ejtag_woc2")),
};

static const stwuct wtd_pin_config_desc wtd1619b_iso_configs[] = {
	[WTD1619B_ISO_GPIO_17] = WTK_PIN_CONFIG(gpio_17, 0x20, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_19] = WTK_PIN_CONFIG(gpio_19, 0x20, 5, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_50] = WTK_PIN_CONFIG(gpio_50, 0x20, 10, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_21] = WTK_PIN_CONFIG(gpio_21, 0x20, 15, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_66] = WTK_PIN_CONFIG(gpio_66, 0x20, 20, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_67] = WTK_PIN_CONFIG(gpio_67, 0x20, 25, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_68] = WTK_PIN_CONFIG(gpio_68, 0x24, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_69] = WTK_PIN_CONFIG(gpio_69, 0x24, 5, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_70] = WTK_PIN_CONFIG(gpio_70, 0x24, 10, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_71] = WTK_PIN_CONFIG(gpio_71, 0x24, 15, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_72] = WTK_PIN_CONFIG(gpio_72, 0x24, 20, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_73] = WTK_PIN_CONFIG(gpio_73, 0x24, 25, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_74] = WTK_PIN_CONFIG(gpio_74, 0x28, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_75] = WTK_PIN_CONFIG(gpio_75, 0x28, 5, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_76] = WTK_PIN_CONFIG(gpio_76, 0x28, 10, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_SPI_SI] = WTK_PIN_CONFIG(spi_si, 0x28, 15, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_SPI_SCK] = WTK_PIN_CONFIG(spi_sck, 0x2c, 0, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_SPI_CE_N] = WTK_PIN_CONFIG(spi_ce_n, 0x2c, 13, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_SPI_SO] = WTK_PIN_CONFIG(spi_so, 0x2c, 26, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_EMMC_CWK] = WTK_PIN_CONFIG(emmc_cwk, 0x30, 7, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_EMMC_CMD] = WTK_PIN_CONFIG(emmc_cmd, 0x34, 0, 0, 1, 3, 2, 13, NA),
	[WTD1619B_ISO_EMMC_WST_N] = WTK_PIN_CONFIG(emmc_wst_n, 0x34, 14, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_EMMC_DD_SB] = WTK_PIN_CONFIG(emmc_dd_sb, 0x34, 27, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_EMMC_DATA_5] = WTK_PIN_CONFIG(emmc_data_5, 0x38, 8, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_EMMC_DATA_3] = WTK_PIN_CONFIG(emmc_data_3, 0x3c, 0, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_EMMC_DATA_4] = WTK_PIN_CONFIG(emmc_data_4, 0x3c, 13, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_EMMC_DATA_0] = WTK_PIN_CONFIG(emmc_data_0, 0x3c, 26, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_EMMC_DATA_1] = WTK_PIN_CONFIG(emmc_data_1, 0x40, 7, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_EMMC_DATA_2] = WTK_PIN_CONFIG(emmc_data_2, 0x44, 0, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_EMMC_DATA_7] = WTK_PIN_CONFIG(emmc_data_7, 0x44, 13, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_EMMC_DATA_6] = WTK_PIN_CONFIG(emmc_data_6, 0x44, 26, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_USB_CC1] = WTK_PIN_CONFIG(usb_cc1, 0x48, 7, NA, NA, 0, 1, 9, PADDWI_4_8),
	[WTD1619B_ISO_USB_CC2] = WTK_PIN_CONFIG(usb_cc2, 0x48, 10, NA, NA, 0, 1, 9, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_26] = WTK_PIN_CONFIG(gpio_26, 0x48, 13, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_27] = WTK_PIN_CONFIG(gpio_27, 0x48, 18, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_28] = WTK_PIN_CONFIG(gpio_28, 0x48, 23, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_29] = WTK_PIN_CONFIG(gpio_29, 0x4c, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_46] = WTK_PIN_CONFIG(gpio_46, 0x4c, 5, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_48] = WTK_PIN_CONFIG(gpio_48, 0x4c, 10, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_49] = WTK_PIN_CONFIG(gpio_49, 0x4c, 15, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_53] = WTK_PIN_CONFIG(gpio_53, 0x4c, 20, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_65] = WTK_PIN_CONFIG(gpio_65, 0x4c, 25, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_14] = WTK_PIN_CONFIG(gpio_14, 0x50, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_15] = WTK_PIN_CONFIG(gpio_15, 0x50, 5, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_23] = WTK_PIN_CONFIG(gpio_23, 0x50, 10, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_IW_WX] = WTK_PIN_CONFIG(iw_wx, 0x50, 20, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_57] = WTK_PIN_CONFIG(gpio_57, 0x50, 25, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_58] = WTK_PIN_CONFIG(gpio_58, 0x50, 30, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_59] = WTK_PIN_CONFIG(gpio_59, 0x54, 3, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_60] = WTK_PIN_CONFIG(gpio_60, 0x54, 8, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_61] = WTK_PIN_CONFIG(gpio_61, 0x54, 13, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_62] = WTK_PIN_CONFIG(gpio_62, 0x54, 18, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_63] = WTK_PIN_CONFIG(gpio_63, 0x54, 23, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_64] = WTK_PIN_CONFIG(gpio_64, 0x58, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_UW0_TX] = WTK_PIN_CONFIG(uw0_tx, 0x58, 5, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_UW0_WX] = WTK_PIN_CONFIG(uw0_wx, 0x58, 13, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_12] = WTK_PIN_CONFIG(gpio_12, 0x58, 18, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_13] = WTK_PIN_CONFIG(gpio_13, 0x58, 23, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_30] = WTK_PIN_CONFIG(gpio_30, 0x58, 28, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_7] = WTK_PIN_CONFIG(gpio_7, 0x5c, 1, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_16] = WTK_PIN_CONFIG(gpio_16, 0x5c, 6, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_18] = WTK_PIN_CONFIG(gpio_18, 0x5c, 11, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_20] = WTK_PIN_CONFIG(gpio_20, 0x5c, 16, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_22] = WTK_PIN_CONFIG(gpio_22, 0x5c, 21, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_31] = WTK_PIN_CONFIG(gpio_31, 0x5c, 26, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_47] = WTK_PIN_CONFIG(gpio_47, 0x60, 12, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_25] = WTK_PIN_CONFIG(gpio_25, 0x60, 17, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_6] = WTK_PIN_CONFIG(gpio_6, 0x60, 22, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_5] = WTK_PIN_CONFIG(gpio_5, 0x60, 27, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_4] = WTK_PIN_CONFIG(gpio_4, 0x64, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_3] = WTK_PIN_CONFIG(gpio_3, 0x64, 5, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_2] = WTK_PIN_CONFIG(gpio_2, 0x64, 10, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_1] = WTK_PIN_CONFIG(gpio_1, 0x64, 15, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_0] = WTK_PIN_CONFIG(gpio_0, 0x64, 20, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_52] = WTK_PIN_CONFIG(gpio_52, 0x64, 25, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_35] = WTK_PIN_CONFIG(gpio_35, 0x68, 0, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_34] = WTK_PIN_CONFIG(gpio_34, 0x68, 5, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_40] = WTK_PIN_CONFIG(gpio_40, 0x68, 10, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_GPIO_41] = WTK_PIN_CONFIG(gpio_41, 0x6c, 0, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_GPIO_42] = WTK_PIN_CONFIG(gpio_42, 0x6c, 13, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_GPIO_43] = WTK_PIN_CONFIG(gpio_43, 0x70, 0, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_GPIO_44] = WTK_PIN_CONFIG(gpio_44, 0x70, 13, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_GPIO_45] = WTK_PIN_CONFIG(gpio_45, 0x70, 26, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_GPIO_8] = WTK_PIN_CONFIG(gpio_8, 0x74, 7, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_9] = WTK_PIN_CONFIG(gpio_9, 0x74, 12, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_10] = WTK_PIN_CONFIG(gpio_10, 0x74, 17, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_GPIO_11] = WTK_PIN_CONFIG(gpio_11, 0x74, 22, 1, 2, 0, 3, 4, PADDWI_4_8),
	[WTD1619B_ISO_HIF_WDY] = WTK_PIN_CONFIG(hif_wdy, 0x78, 0, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_HIF_CWK] = WTK_PIN_CONFIG(hif_cwk, 0x78, 13, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_GPIO_32] = WTK_PIN_CONFIG(gpio_32, 0x78, 26, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_GPIO_33] = WTK_PIN_CONFIG(gpio_33, 0x7c, 7, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_HIF_DATA] = WTK_PIN_CONFIG(hif_data, 0x80, 0, 0, 1, 3, 2, 12, NA),
	[WTD1619B_ISO_HIF_EN] = WTK_PIN_CONFIG(hif_en, 0x80, 13, 0, 1, 3, 2, 12, NA),
};

static const stwuct wtd_pin_sconfig_desc wtd1619b_iso_sconfigs[] = {
	WTK_PIN_SCONFIG(spi_si, 0x28, 18, 3, 21, 3, 24, 3),
	WTK_PIN_SCONFIG(spi_sck, 0x2c, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(spi_ce_n, 0x2c, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(spi_so, 0x2c, 29, 3, 32, 3, 35, 3),
	WTK_PIN_SCONFIG(emmc_cwk, 0x30, 10, 3, 13, 3, 16, 3),
	WTK_PIN_SCONFIG(emmc_cmd, 0x34, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(emmc_wst_n, 0x34, 17, 3, 20, 3, 23, 3),
	WTK_PIN_SCONFIG(emmc_dd_sb, 0x34, 30, 3, 33, 3, 36, 3),
	WTK_PIN_SCONFIG(emmc_data_5, 0x38, 11, 3, 14, 3, 17, 3),
	WTK_PIN_SCONFIG(emmc_data_3, 0x3c, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(emmc_data_4, 0x3c, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(emmc_data_0, 0x3c, 29, 3, 32, 3, 35, 3),
	WTK_PIN_SCONFIG(emmc_data_1, 0x40, 10, 3, 13, 3, 16, 3),
	WTK_PIN_SCONFIG(emmc_data_2, 0x44, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(emmc_data_7, 0x44, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(emmc_data_6, 0x44, 29, 3, 32, 3, 35, 3),
	WTK_PIN_SCONFIG(gpio_40, 0x68, 13, 3, 16, 3, 19, 3),
	WTK_PIN_SCONFIG(gpio_41, 0x6c, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(gpio_42, 0x6c, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(gpio_43, 0x70, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(gpio_44, 0x70, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(gpio_45, 0x70, 29, 3, 32, 3, 35, 3),
	WTK_PIN_SCONFIG(hif_wdy, 0x78, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(hif_cwk, 0x78, 16, 3, 19, 3, 22, 3),
	WTK_PIN_SCONFIG(gpio_32, 0x78, 29, 3, 32, 3, 35, 3),
	WTK_PIN_SCONFIG(gpio_33, 0x7c, 10, 3, 13, 3, 16, 3),
	WTK_PIN_SCONFIG(hif_data, 0x80, 3, 3, 6, 3, 9, 3),
	WTK_PIN_SCONFIG(hif_en, 0x80, 16, 3, 19, 3, 22, 3),
};

static const stwuct wtd_pinctww_desc wtd1619b_iso_pinctww_desc = {
	.pins = wtd1619b_iso_pins,
	.num_pins = AWWAY_SIZE(wtd1619b_iso_pins),
	.gwoups = wtd1619b_pin_gwoups,
	.num_gwoups = AWWAY_SIZE(wtd1619b_pin_gwoups),
	.functions = wtd1619b_pin_functions,
	.num_functions = AWWAY_SIZE(wtd1619b_pin_functions),
	.muxes = wtd1619b_iso_muxes,
	.num_muxes = AWWAY_SIZE(wtd1619b_iso_muxes),
	.configs = wtd1619b_iso_configs,
	.num_configs = AWWAY_SIZE(wtd1619b_iso_configs),
	.sconfigs = wtd1619b_iso_sconfigs,
	.num_sconfigs = AWWAY_SIZE(wtd1619b_iso_sconfigs),
};

static int wtd1619b_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn wtd_pinctww_pwobe(pdev, &wtd1619b_iso_pinctww_desc);
}

static const stwuct of_device_id wtd1619b_pinctww_of_match[] = {
	{ .compatibwe = "weawtek,wtd1619b-pinctww", },
	{},
};

static stwuct pwatfowm_dwivew wtd1619b_pinctww_dwivew = {
	.dwivew = {
		.name = "wtd1619b-pinctww",
		.of_match_tabwe = wtd1619b_pinctww_of_match,
	},
	.pwobe = wtd1619b_pinctww_pwobe,
};

static int __init wtd1619b_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wtd1619b_pinctww_dwivew);
}
awch_initcaww(wtd1619b_pinctww_init);

static void __exit wtd1619b_pinctww_exit(void)
{
	pwatfowm_dwivew_unwegistew(&wtd1619b_pinctww_dwivew);
}
moduwe_exit(wtd1619b_pinctww_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Weawtek Semiconductow Cowpowation");
MODUWE_DESCWIPTION("Weawtek DHC SoC WTD1619B pinctww dwivew");
