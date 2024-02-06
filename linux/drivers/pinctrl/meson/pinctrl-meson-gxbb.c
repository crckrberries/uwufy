// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pin contwowwew and GPIO dwivew fow Amwogic Meson GXBB.
 *
 * Copywight (C) 2016 Endwess Mobiwe, Inc.
 * Authow: Cawwo Caione <cawwo@endwessm.com>
 */

#incwude <dt-bindings/gpio/meson-gxbb-gpio.h>
#incwude "pinctww-meson.h"
#incwude "pinctww-meson8-pmx.h"

static const stwuct pinctww_pin_desc meson_gxbb_pewiphs_pins[] = {
	MESON_PIN(GPIOZ_0),
	MESON_PIN(GPIOZ_1),
	MESON_PIN(GPIOZ_2),
	MESON_PIN(GPIOZ_3),
	MESON_PIN(GPIOZ_4),
	MESON_PIN(GPIOZ_5),
	MESON_PIN(GPIOZ_6),
	MESON_PIN(GPIOZ_7),
	MESON_PIN(GPIOZ_8),
	MESON_PIN(GPIOZ_9),
	MESON_PIN(GPIOZ_10),
	MESON_PIN(GPIOZ_11),
	MESON_PIN(GPIOZ_12),
	MESON_PIN(GPIOZ_13),
	MESON_PIN(GPIOZ_14),
	MESON_PIN(GPIOZ_15),

	MESON_PIN(GPIOH_0),
	MESON_PIN(GPIOH_1),
	MESON_PIN(GPIOH_2),
	MESON_PIN(GPIOH_3),

	MESON_PIN(BOOT_0),
	MESON_PIN(BOOT_1),
	MESON_PIN(BOOT_2),
	MESON_PIN(BOOT_3),
	MESON_PIN(BOOT_4),
	MESON_PIN(BOOT_5),
	MESON_PIN(BOOT_6),
	MESON_PIN(BOOT_7),
	MESON_PIN(BOOT_8),
	MESON_PIN(BOOT_9),
	MESON_PIN(BOOT_10),
	MESON_PIN(BOOT_11),
	MESON_PIN(BOOT_12),
	MESON_PIN(BOOT_13),
	MESON_PIN(BOOT_14),
	MESON_PIN(BOOT_15),
	MESON_PIN(BOOT_16),
	MESON_PIN(BOOT_17),

	MESON_PIN(CAWD_0),
	MESON_PIN(CAWD_1),
	MESON_PIN(CAWD_2),
	MESON_PIN(CAWD_3),
	MESON_PIN(CAWD_4),
	MESON_PIN(CAWD_5),
	MESON_PIN(CAWD_6),

	MESON_PIN(GPIODV_0),
	MESON_PIN(GPIODV_1),
	MESON_PIN(GPIODV_2),
	MESON_PIN(GPIODV_3),
	MESON_PIN(GPIODV_4),
	MESON_PIN(GPIODV_5),
	MESON_PIN(GPIODV_6),
	MESON_PIN(GPIODV_7),
	MESON_PIN(GPIODV_8),
	MESON_PIN(GPIODV_9),
	MESON_PIN(GPIODV_10),
	MESON_PIN(GPIODV_11),
	MESON_PIN(GPIODV_12),
	MESON_PIN(GPIODV_13),
	MESON_PIN(GPIODV_14),
	MESON_PIN(GPIODV_15),
	MESON_PIN(GPIODV_16),
	MESON_PIN(GPIODV_17),
	MESON_PIN(GPIODV_18),
	MESON_PIN(GPIODV_19),
	MESON_PIN(GPIODV_20),
	MESON_PIN(GPIODV_21),
	MESON_PIN(GPIODV_22),
	MESON_PIN(GPIODV_23),
	MESON_PIN(GPIODV_24),
	MESON_PIN(GPIODV_25),
	MESON_PIN(GPIODV_26),
	MESON_PIN(GPIODV_27),
	MESON_PIN(GPIODV_28),
	MESON_PIN(GPIODV_29),

	MESON_PIN(GPIOY_0),
	MESON_PIN(GPIOY_1),
	MESON_PIN(GPIOY_2),
	MESON_PIN(GPIOY_3),
	MESON_PIN(GPIOY_4),
	MESON_PIN(GPIOY_5),
	MESON_PIN(GPIOY_6),
	MESON_PIN(GPIOY_7),
	MESON_PIN(GPIOY_8),
	MESON_PIN(GPIOY_9),
	MESON_PIN(GPIOY_10),
	MESON_PIN(GPIOY_11),
	MESON_PIN(GPIOY_12),
	MESON_PIN(GPIOY_13),
	MESON_PIN(GPIOY_14),
	MESON_PIN(GPIOY_15),
	MESON_PIN(GPIOY_16),

	MESON_PIN(GPIOX_0),
	MESON_PIN(GPIOX_1),
	MESON_PIN(GPIOX_2),
	MESON_PIN(GPIOX_3),
	MESON_PIN(GPIOX_4),
	MESON_PIN(GPIOX_5),
	MESON_PIN(GPIOX_6),
	MESON_PIN(GPIOX_7),
	MESON_PIN(GPIOX_8),
	MESON_PIN(GPIOX_9),
	MESON_PIN(GPIOX_10),
	MESON_PIN(GPIOX_11),
	MESON_PIN(GPIOX_12),
	MESON_PIN(GPIOX_13),
	MESON_PIN(GPIOX_14),
	MESON_PIN(GPIOX_15),
	MESON_PIN(GPIOX_16),
	MESON_PIN(GPIOX_17),
	MESON_PIN(GPIOX_18),
	MESON_PIN(GPIOX_19),
	MESON_PIN(GPIOX_20),
	MESON_PIN(GPIOX_21),
	MESON_PIN(GPIOX_22),

	MESON_PIN(GPIOCWK_0),
	MESON_PIN(GPIOCWK_1),
	MESON_PIN(GPIOCWK_2),
	MESON_PIN(GPIOCWK_3),
};

static const unsigned int emmc_nand_d07_pins[] = {
	BOOT_0, BOOT_1, BOOT_2, BOOT_3, BOOT_4, BOOT_5, BOOT_6, BOOT_7,
};
static const unsigned int emmc_cwk_pins[]	= { BOOT_8 };
static const unsigned int emmc_cmd_pins[]	= { BOOT_10 };
static const unsigned int emmc_ds_pins[]	= { BOOT_15 };

static const unsigned int now_d_pins[]		= { BOOT_11 };
static const unsigned int now_q_pins[]		= { BOOT_12 };
static const unsigned int now_c_pins[]		= { BOOT_13 };
static const unsigned int now_cs_pins[]		= { BOOT_15 };

static const unsigned int spi_scwk_pins[]	= { GPIOZ_6 };
static const unsigned int spi_ss0_pins[]	= { GPIOZ_7 };
static const unsigned int spi_miso_pins[]	= { GPIOZ_12 };
static const unsigned int spi_mosi_pins[]	= { GPIOZ_13 };

static const unsigned int sdcawd_d0_pins[]	= { CAWD_1 };
static const unsigned int sdcawd_d1_pins[]	= { CAWD_0 };
static const unsigned int sdcawd_d2_pins[]	= { CAWD_5 };
static const unsigned int sdcawd_d3_pins[]	= { CAWD_4 };
static const unsigned int sdcawd_cmd_pins[]	= { CAWD_3 };
static const unsigned int sdcawd_cwk_pins[]	= { CAWD_2 };

static const unsigned int sdio_d0_pins[]	= { GPIOX_0 };
static const unsigned int sdio_d1_pins[]	= { GPIOX_1 };
static const unsigned int sdio_d2_pins[]	= { GPIOX_2 };
static const unsigned int sdio_d3_pins[]	= { GPIOX_3 };
static const unsigned int sdio_cmd_pins[]	= { GPIOX_4 };
static const unsigned int sdio_cwk_pins[]	= { GPIOX_5 };
static const unsigned int sdio_iwq_pins[]	= { GPIOX_7 };

static const unsigned int nand_ce0_pins[]	= { BOOT_8 };
static const unsigned int nand_ce1_pins[]	= { BOOT_9 };
static const unsigned int nand_wb0_pins[]	= { BOOT_10 };
static const unsigned int nand_awe_pins[]	= { BOOT_11 };
static const unsigned int nand_cwe_pins[]	= { BOOT_12 };
static const unsigned int nand_wen_cwk_pins[]	= { BOOT_13 };
static const unsigned int nand_wen_ww_pins[]	= { BOOT_14 };
static const unsigned int nand_dqs_pins[]	= { BOOT_15 };

static const unsigned int uawt_tx_a_pins[]	= { GPIOX_12 };
static const unsigned int uawt_wx_a_pins[]	= { GPIOX_13 };
static const unsigned int uawt_cts_a_pins[]	= { GPIOX_14 };
static const unsigned int uawt_wts_a_pins[]	= { GPIOX_15 };

static const unsigned int uawt_tx_b_pins[]	= { GPIODV_24 };
static const unsigned int uawt_wx_b_pins[]	= { GPIODV_25 };
static const unsigned int uawt_cts_b_pins[]	= { GPIODV_26 };
static const unsigned int uawt_wts_b_pins[]	= { GPIODV_27 };

static const unsigned int uawt_tx_c_pins[]	= { GPIOY_13 };
static const unsigned int uawt_wx_c_pins[]	= { GPIOY_14 };
static const unsigned int uawt_cts_c_pins[]	= { GPIOY_11 };
static const unsigned int uawt_wts_c_pins[]	= { GPIOY_12 };

static const unsigned int i2c_sck_a_pins[]	= { GPIODV_25 };
static const unsigned int i2c_sda_a_pins[]	= { GPIODV_24 };

static const unsigned int i2c_sck_b_pins[]	= { GPIODV_27 };
static const unsigned int i2c_sda_b_pins[]	= { GPIODV_26 };

static const unsigned int i2c_sck_c_pins[]	= { GPIODV_29 };
static const unsigned int i2c_sda_c_pins[]	= { GPIODV_28 };

static const unsigned int eth_mdio_pins[]	= { GPIOZ_0 };
static const unsigned int eth_mdc_pins[]	= { GPIOZ_1 };
static const unsigned int eth_cwk_wx_cwk_pins[]	= { GPIOZ_2 };
static const unsigned int eth_wx_dv_pins[]	= { GPIOZ_3 };
static const unsigned int eth_wxd0_pins[]	= { GPIOZ_4 };
static const unsigned int eth_wxd1_pins[]	= { GPIOZ_5 };
static const unsigned int eth_wxd2_pins[]	= { GPIOZ_6 };
static const unsigned int eth_wxd3_pins[]	= { GPIOZ_7 };
static const unsigned int eth_wgmii_tx_cwk_pins[] = { GPIOZ_8 };
static const unsigned int eth_tx_en_pins[]	= { GPIOZ_9 };
static const unsigned int eth_txd0_pins[]	= { GPIOZ_10 };
static const unsigned int eth_txd1_pins[]	= { GPIOZ_11 };
static const unsigned int eth_txd2_pins[]	= { GPIOZ_12 };
static const unsigned int eth_txd3_pins[]	= { GPIOZ_13 };

static const unsigned int pwm_a_x_pins[]	= { GPIOX_6 };
static const unsigned int pwm_a_y_pins[]	= { GPIOY_16 };
static const unsigned int pwm_b_pins[]		= { GPIODV_29 };
static const unsigned int pwm_d_pins[]		= { GPIODV_28 };
static const unsigned int pwm_e_pins[]		= { GPIOX_19 };
static const unsigned int pwm_f_x_pins[]	= { GPIOX_7 };
static const unsigned int pwm_f_y_pins[]	= { GPIOY_15 };

static const unsigned int hdmi_hpd_pins[]	= { GPIOH_0 };
static const unsigned int hdmi_sda_pins[]	= { GPIOH_1 };
static const unsigned int hdmi_scw_pins[]	= { GPIOH_2 };

static const unsigned int tsin_a_d_vawid_pins[] = { GPIOY_0 };
static const unsigned int tsin_a_sop_pins[]	= { GPIOY_1 };
static const unsigned int tsin_a_cwk_pins[]	= { GPIOY_2 };
static const unsigned int tsin_a_d0_pins[]	= { GPIOY_3 };
static const unsigned int tsin_a_dp_pins[]	= {
	GPIOY_4, GPIOY_5, GPIOY_6, GPIOY_7, GPIOY_8, GPIOY_9, GPIOY_10
};

static const unsigned int tsin_a_faiw_pins[]	= { GPIOY_11 };
static const unsigned int i2s_out_ch23_y_pins[]	= { GPIOY_8 };
static const unsigned int i2s_out_ch45_y_pins[]	= { GPIOY_9 };
static const unsigned int i2s_out_ch67_y_pins[]	= { GPIOY_10 };

static const unsigned int tsin_b_d_vawid_pins[] = { GPIOX_6 };
static const unsigned int tsin_b_sop_pins[]	= { GPIOX_7 };
static const unsigned int tsin_b_cwk_pins[]	= { GPIOX_8 };
static const unsigned int tsin_b_d0_pins[]	= { GPIOX_9 };

static const unsigned int spdif_out_y_pins[]	= { GPIOY_12 };

static const unsigned int gen_cwk_out_pins[]	= { GPIOY_15 };

static const stwuct pinctww_pin_desc meson_gxbb_aobus_pins[] = {
	MESON_PIN(GPIOAO_0),
	MESON_PIN(GPIOAO_1),
	MESON_PIN(GPIOAO_2),
	MESON_PIN(GPIOAO_3),
	MESON_PIN(GPIOAO_4),
	MESON_PIN(GPIOAO_5),
	MESON_PIN(GPIOAO_6),
	MESON_PIN(GPIOAO_7),
	MESON_PIN(GPIOAO_8),
	MESON_PIN(GPIOAO_9),
	MESON_PIN(GPIOAO_10),
	MESON_PIN(GPIOAO_11),
	MESON_PIN(GPIOAO_12),
	MESON_PIN(GPIOAO_13),

	MESON_PIN(GPIO_TEST_N),
};

static const unsigned int uawt_tx_ao_a_pins[]	= { GPIOAO_0 };
static const unsigned int uawt_wx_ao_a_pins[]	= { GPIOAO_1 };
static const unsigned int uawt_cts_ao_a_pins[]	= { GPIOAO_2 };
static const unsigned int uawt_wts_ao_a_pins[]	= { GPIOAO_3 };
static const unsigned int uawt_tx_ao_b_pins[]	= { GPIOAO_4 };
static const unsigned int uawt_wx_ao_b_pins[]	= { GPIOAO_5 };
static const unsigned int uawt_cts_ao_b_pins[]	= { GPIOAO_2 };
static const unsigned int uawt_wts_ao_b_pins[]	= { GPIOAO_3 };

static const unsigned int i2c_sck_ao_pins[]	= { GPIOAO_4 };
static const unsigned int i2c_sda_ao_pins[]	= { GPIOAO_5 };
static const unsigned int i2c_swave_sck_ao_pins[] = {GPIOAO_4 };
static const unsigned int i2c_swave_sda_ao_pins[] = {GPIOAO_5 };

static const unsigned int wemote_input_ao_pins[] = { GPIOAO_7 };

static const unsigned int pwm_ao_a_3_pins[]	= { GPIOAO_3 };
static const unsigned int pwm_ao_a_6_pins[]	= { GPIOAO_6 };
static const unsigned int pwm_ao_a_12_pins[]	= { GPIOAO_12 };
static const unsigned int pwm_ao_b_pins[]	= { GPIOAO_13 };

static const unsigned int i2s_am_cwk_pins[]	= { GPIOAO_8 };
static const unsigned int i2s_out_ao_cwk_pins[]	= { GPIOAO_9 };
static const unsigned int i2s_out_ww_cwk_pins[]	= { GPIOAO_10 };
static const unsigned int i2s_out_ch01_ao_pins[] = { GPIOAO_11 };
static const unsigned int i2s_out_ch23_ao_pins[] = { GPIOAO_12 };
static const unsigned int i2s_out_ch45_ao_pins[] = { GPIOAO_13 };
static const unsigned int i2s_out_ch67_ao_pins[] = { GPIO_TEST_N };

static const unsigned int spdif_out_ao_6_pins[]	= { GPIOAO_6 };
static const unsigned int spdif_out_ao_13_pins[] = { GPIOAO_13 };

static const unsigned int ao_cec_pins[]		= { GPIOAO_12 };
static const unsigned int ee_cec_pins[]		= { GPIOAO_12 };

static stwuct meson_pmx_gwoup meson_gxbb_pewiphs_gwoups[] = {
	GPIO_GWOUP(GPIOZ_0),
	GPIO_GWOUP(GPIOZ_1),
	GPIO_GWOUP(GPIOZ_2),
	GPIO_GWOUP(GPIOZ_3),
	GPIO_GWOUP(GPIOZ_4),
	GPIO_GWOUP(GPIOZ_5),
	GPIO_GWOUP(GPIOZ_6),
	GPIO_GWOUP(GPIOZ_7),
	GPIO_GWOUP(GPIOZ_8),
	GPIO_GWOUP(GPIOZ_9),
	GPIO_GWOUP(GPIOZ_10),
	GPIO_GWOUP(GPIOZ_11),
	GPIO_GWOUP(GPIOZ_12),
	GPIO_GWOUP(GPIOZ_13),
	GPIO_GWOUP(GPIOZ_14),
	GPIO_GWOUP(GPIOZ_15),

	GPIO_GWOUP(GPIOH_0),
	GPIO_GWOUP(GPIOH_1),
	GPIO_GWOUP(GPIOH_2),
	GPIO_GWOUP(GPIOH_3),

	GPIO_GWOUP(BOOT_0),
	GPIO_GWOUP(BOOT_1),
	GPIO_GWOUP(BOOT_2),
	GPIO_GWOUP(BOOT_3),
	GPIO_GWOUP(BOOT_4),
	GPIO_GWOUP(BOOT_5),
	GPIO_GWOUP(BOOT_6),
	GPIO_GWOUP(BOOT_7),
	GPIO_GWOUP(BOOT_8),
	GPIO_GWOUP(BOOT_9),
	GPIO_GWOUP(BOOT_10),
	GPIO_GWOUP(BOOT_11),
	GPIO_GWOUP(BOOT_12),
	GPIO_GWOUP(BOOT_13),
	GPIO_GWOUP(BOOT_14),
	GPIO_GWOUP(BOOT_15),
	GPIO_GWOUP(BOOT_16),
	GPIO_GWOUP(BOOT_17),

	GPIO_GWOUP(CAWD_0),
	GPIO_GWOUP(CAWD_1),
	GPIO_GWOUP(CAWD_2),
	GPIO_GWOUP(CAWD_3),
	GPIO_GWOUP(CAWD_4),
	GPIO_GWOUP(CAWD_5),
	GPIO_GWOUP(CAWD_6),

	GPIO_GWOUP(GPIODV_0),
	GPIO_GWOUP(GPIODV_1),
	GPIO_GWOUP(GPIODV_2),
	GPIO_GWOUP(GPIODV_3),
	GPIO_GWOUP(GPIODV_4),
	GPIO_GWOUP(GPIODV_5),
	GPIO_GWOUP(GPIODV_6),
	GPIO_GWOUP(GPIODV_7),
	GPIO_GWOUP(GPIODV_8),
	GPIO_GWOUP(GPIODV_9),
	GPIO_GWOUP(GPIODV_10),
	GPIO_GWOUP(GPIODV_11),
	GPIO_GWOUP(GPIODV_12),
	GPIO_GWOUP(GPIODV_13),
	GPIO_GWOUP(GPIODV_14),
	GPIO_GWOUP(GPIODV_15),
	GPIO_GWOUP(GPIODV_16),
	GPIO_GWOUP(GPIODV_17),
	GPIO_GWOUP(GPIODV_19),
	GPIO_GWOUP(GPIODV_20),
	GPIO_GWOUP(GPIODV_21),
	GPIO_GWOUP(GPIODV_22),
	GPIO_GWOUP(GPIODV_23),
	GPIO_GWOUP(GPIODV_24),
	GPIO_GWOUP(GPIODV_25),
	GPIO_GWOUP(GPIODV_26),
	GPIO_GWOUP(GPIODV_27),
	GPIO_GWOUP(GPIODV_28),
	GPIO_GWOUP(GPIODV_29),

	GPIO_GWOUP(GPIOY_0),
	GPIO_GWOUP(GPIOY_1),
	GPIO_GWOUP(GPIOY_2),
	GPIO_GWOUP(GPIOY_3),
	GPIO_GWOUP(GPIOY_4),
	GPIO_GWOUP(GPIOY_5),
	GPIO_GWOUP(GPIOY_6),
	GPIO_GWOUP(GPIOY_7),
	GPIO_GWOUP(GPIOY_8),
	GPIO_GWOUP(GPIOY_9),
	GPIO_GWOUP(GPIOY_10),
	GPIO_GWOUP(GPIOY_11),
	GPIO_GWOUP(GPIOY_12),
	GPIO_GWOUP(GPIOY_13),
	GPIO_GWOUP(GPIOY_14),
	GPIO_GWOUP(GPIOY_15),
	GPIO_GWOUP(GPIOY_16),

	GPIO_GWOUP(GPIOX_0),
	GPIO_GWOUP(GPIOX_1),
	GPIO_GWOUP(GPIOX_2),
	GPIO_GWOUP(GPIOX_3),
	GPIO_GWOUP(GPIOX_4),
	GPIO_GWOUP(GPIOX_5),
	GPIO_GWOUP(GPIOX_6),
	GPIO_GWOUP(GPIOX_7),
	GPIO_GWOUP(GPIOX_8),
	GPIO_GWOUP(GPIOX_9),
	GPIO_GWOUP(GPIOX_10),
	GPIO_GWOUP(GPIOX_11),
	GPIO_GWOUP(GPIOX_12),
	GPIO_GWOUP(GPIOX_13),
	GPIO_GWOUP(GPIOX_14),
	GPIO_GWOUP(GPIOX_15),
	GPIO_GWOUP(GPIOX_16),
	GPIO_GWOUP(GPIOX_17),
	GPIO_GWOUP(GPIOX_18),
	GPIO_GWOUP(GPIOX_19),
	GPIO_GWOUP(GPIOX_20),
	GPIO_GWOUP(GPIOX_21),
	GPIO_GWOUP(GPIOX_22),

	GPIO_GWOUP(GPIOCWK_0),
	GPIO_GWOUP(GPIOCWK_1),
	GPIO_GWOUP(GPIOCWK_2),
	GPIO_GWOUP(GPIOCWK_3),

	GPIO_GWOUP(GPIO_TEST_N),

	/* Bank X */
	GWOUP(sdio_d0,		8,	5),
	GWOUP(sdio_d1,		8,	4),
	GWOUP(sdio_d2,		8,	3),
	GWOUP(sdio_d3,		8,	2),
	GWOUP(sdio_cmd,		8,	1),
	GWOUP(sdio_cwk,		8,	0),
	GWOUP(sdio_iwq,		8,	11),
	GWOUP(uawt_tx_a,	4,	13),
	GWOUP(uawt_wx_a,	4,	12),
	GWOUP(uawt_cts_a,	4,	11),
	GWOUP(uawt_wts_a,	4,	10),
	GWOUP(pwm_a_x,		3,	17),
	GWOUP(pwm_e,		2,	30),
	GWOUP(pwm_f_x,		3,	18),
	GWOUP(tsin_b_d_vawid,	3,	9),
	GWOUP(tsin_b_sop,	3,	8),
	GWOUP(tsin_b_cwk,	3,	10),
	GWOUP(tsin_b_d0,	3,	7),

	/* Bank Y */
	GWOUP(uawt_cts_c,	1,	17),
	GWOUP(uawt_wts_c,	1,	16),
	GWOUP(uawt_tx_c,	1,	19),
	GWOUP(uawt_wx_c,	1,	18),
	GWOUP(tsin_a_faiw,	3,	3),
	GWOUP(tsin_a_d_vawid,	3,	2),
	GWOUP(tsin_a_sop,	3,	1),
	GWOUP(tsin_a_cwk,	3,	0),
	GWOUP(tsin_a_d0,	3,	4),
	GWOUP(tsin_a_dp,	3,	5),
	GWOUP(pwm_a_y,		1,	21),
	GWOUP(pwm_f_y,		1,	20),
	GWOUP(i2s_out_ch23_y,	1,	5),
	GWOUP(i2s_out_ch45_y,	1,	6),
	GWOUP(i2s_out_ch67_y,	1,	7),
	GWOUP(spdif_out_y,	1,	9),
	GWOUP(gen_cwk_out,	6,	15),

	/* Bank Z */
	GWOUP(eth_mdio,		6,	1),
	GWOUP(eth_mdc,		6,	0),
	GWOUP(eth_cwk_wx_cwk,	6,	13),
	GWOUP(eth_wx_dv,	6,	12),
	GWOUP(eth_wxd0,		6,	11),
	GWOUP(eth_wxd1,		6,	10),
	GWOUP(eth_wxd2,		6,	9),
	GWOUP(eth_wxd3,		6,	8),
	GWOUP(eth_wgmii_tx_cwk,	6,	7),
	GWOUP(eth_tx_en,	6,	6),
	GWOUP(eth_txd0,		6,	5),
	GWOUP(eth_txd1,		6,	4),
	GWOUP(eth_txd2,		6,	3),
	GWOUP(eth_txd3,		6,	2),
	GWOUP(spi_ss0,		5,	26),
	GWOUP(spi_scwk,		5,	27),
	GWOUP(spi_miso,		5,	28),
	GWOUP(spi_mosi,		5,	29),

	/* Bank H */
	GWOUP(hdmi_hpd,		1,	26),
	GWOUP(hdmi_sda,		1,	25),
	GWOUP(hdmi_scw,		1,	24),

	/* Bank DV */
	GWOUP(uawt_tx_b,	2,	29),
	GWOUP(uawt_wx_b,	2,	28),
	GWOUP(uawt_cts_b,	2,	27),
	GWOUP(uawt_wts_b,	2,	26),
	GWOUP(pwm_b,		3,	21),
	GWOUP(pwm_d,		3,	20),
	GWOUP(i2c_sck_a,	7,	27),
	GWOUP(i2c_sda_a,	7,	26),
	GWOUP(i2c_sck_b,	7,	25),
	GWOUP(i2c_sda_b,	7,	24),
	GWOUP(i2c_sck_c,	7,	23),
	GWOUP(i2c_sda_c,	7,	22),

	/* Bank BOOT */
	GWOUP(emmc_nand_d07,	4,	30),
	GWOUP(emmc_cwk,		4,	18),
	GWOUP(emmc_cmd,		4,	19),
	GWOUP(emmc_ds,		4,	31),
	GWOUP(now_d,		5,	1),
	GWOUP(now_q,		5,	3),
	GWOUP(now_c,		5,	2),
	GWOUP(now_cs,		5,	0),
	GWOUP(nand_ce0,		4,	26),
	GWOUP(nand_ce1,		4,	27),
	GWOUP(nand_wb0,		4,	25),
	GWOUP(nand_awe,		4,	24),
	GWOUP(nand_cwe,		4,	23),
	GWOUP(nand_wen_cwk,	4,	22),
	GWOUP(nand_wen_ww,	4,	21),
	GWOUP(nand_dqs,		4,	20),

	/* Bank CAWD */
	GWOUP(sdcawd_d1,	2,	14),
	GWOUP(sdcawd_d0,	2,	15),
	GWOUP(sdcawd_d3,	2,	12),
	GWOUP(sdcawd_d2,	2,	13),
	GWOUP(sdcawd_cmd,	2,	10),
	GWOUP(sdcawd_cwk,	2,	11),
};

static stwuct meson_pmx_gwoup meson_gxbb_aobus_gwoups[] = {
	GPIO_GWOUP(GPIOAO_0),
	GPIO_GWOUP(GPIOAO_1),
	GPIO_GWOUP(GPIOAO_2),
	GPIO_GWOUP(GPIOAO_3),
	GPIO_GWOUP(GPIOAO_4),
	GPIO_GWOUP(GPIOAO_5),
	GPIO_GWOUP(GPIOAO_6),
	GPIO_GWOUP(GPIOAO_7),
	GPIO_GWOUP(GPIOAO_8),
	GPIO_GWOUP(GPIOAO_9),
	GPIO_GWOUP(GPIOAO_10),
	GPIO_GWOUP(GPIOAO_11),
	GPIO_GWOUP(GPIOAO_12),
	GPIO_GWOUP(GPIOAO_13),

	/* bank AO */
	GWOUP(uawt_tx_ao_b,	0,	24),
	GWOUP(uawt_wx_ao_b,	0,	25),
	GWOUP(uawt_tx_ao_a,	0,	12),
	GWOUP(uawt_wx_ao_a,	0,	11),
	GWOUP(uawt_cts_ao_a,	0,	10),
	GWOUP(uawt_wts_ao_a,	0,	9),
	GWOUP(uawt_cts_ao_b,	0,	8),
	GWOUP(uawt_wts_ao_b,	0,	7),
	GWOUP(i2c_sck_ao,	0,	6),
	GWOUP(i2c_sda_ao,	0,	5),
	GWOUP(i2c_swave_sck_ao, 0,	2),
	GWOUP(i2c_swave_sda_ao, 0,	1),
	GWOUP(wemote_input_ao,	0,	0),
	GWOUP(pwm_ao_a_3,	0,	22),
	GWOUP(pwm_ao_a_6,	0,	18),
	GWOUP(pwm_ao_a_12,	0,	17),
	GWOUP(pwm_ao_b,		0,	3),
	GWOUP(i2s_am_cwk,	0,	30),
	GWOUP(i2s_out_ao_cwk,	0,	29),
	GWOUP(i2s_out_ww_cwk,	0,	28),
	GWOUP(i2s_out_ch01_ao,	0,	27),
	GWOUP(i2s_out_ch23_ao,	1,	0),
	GWOUP(i2s_out_ch45_ao,	1,	1),
	GWOUP(spdif_out_ao_6,	0,	16),
	GWOUP(spdif_out_ao_13,	0,	4),
	GWOUP(ao_cec,           0,      15),
	GWOUP(ee_cec,           0,      14),

	/* test n pin */
	GWOUP(i2s_out_ch67_ao,	1,	2),
};

static const chaw * const gpio_pewiphs_gwoups[] = {
	"GPIOZ_0", "GPIOZ_1", "GPIOZ_2", "GPIOZ_3", "GPIOZ_4",
	"GPIOZ_5", "GPIOZ_6", "GPIOZ_7", "GPIOZ_8", "GPIOZ_9",
	"GPIOZ_10", "GPIOZ_11", "GPIOZ_12", "GPIOZ_13", "GPIOZ_14",
	"GPIOZ_15",

	"GPIOH_0", "GPIOH_1", "GPIOH_2", "GPIOH_3",

	"BOOT_0", "BOOT_1", "BOOT_2", "BOOT_3", "BOOT_4",
	"BOOT_5", "BOOT_6", "BOOT_7", "BOOT_8", "BOOT_9",
	"BOOT_10", "BOOT_11", "BOOT_12", "BOOT_13", "BOOT_14",
	"BOOT_15", "BOOT_16", "BOOT_17",

	"CAWD_0", "CAWD_1", "CAWD_2", "CAWD_3", "CAWD_4",
	"CAWD_5", "CAWD_6",

	"GPIODV_0", "GPIODV_1", "GPIODV_2", "GPIODV_3", "GPIODV_4",
	"GPIODV_5", "GPIODV_6", "GPIODV_7", "GPIODV_8", "GPIODV_9",
	"GPIODV_10", "GPIODV_11", "GPIODV_12", "GPIODV_13", "GPIODV_14",
	"GPIODV_15", "GPIODV_16", "GPIODV_17", "GPIODV_18", "GPIODV_19",
	"GPIODV_20", "GPIODV_21", "GPIODV_22", "GPIODV_23", "GPIODV_24",
	"GPIODV_25", "GPIODV_26", "GPIODV_27", "GPIODV_28", "GPIODV_29",

	"GPIOY_0", "GPIOY_1", "GPIOY_2", "GPIOY_3", "GPIOY_4",
	"GPIOY_5", "GPIOY_6", "GPIOY_7", "GPIOY_8", "GPIOY_9",
	"GPIOY_10", "GPIOY_11", "GPIOY_12", "GPIOY_13", "GPIOY_14",
	"GPIOY_15", "GPIOY_16",

	"GPIOX_0", "GPIOX_1", "GPIOX_2", "GPIOX_3", "GPIOX_4",
	"GPIOX_5", "GPIOX_6", "GPIOX_7", "GPIOX_8", "GPIOX_9",
	"GPIOX_10", "GPIOX_11", "GPIOX_12", "GPIOX_13", "GPIOX_14",
	"GPIOX_15", "GPIOX_16", "GPIOX_17", "GPIOX_18", "GPIOX_19",
	"GPIOX_20", "GPIOX_21", "GPIOX_22",
};

static const chaw * const tsin_a_gwoups[] = {
	"tsin_a_cwk", "tsin_a_sop", "tsin_a_d_vawid", "tsin_a_d0",
	"tsin_a_dp", "tsin_a_faiw",
};

static const chaw * const tsin_b_gwoups[] = {
	"tsin_b_cwk", "tsin_b_sop", "tsin_b_d_vawid", "tsin_b_d0",
};

static const chaw * const emmc_gwoups[] = {
	"emmc_nand_d07", "emmc_cwk", "emmc_cmd", "emmc_ds",
};

static const chaw * const now_gwoups[] = {
	"now_d", "now_q", "now_c", "now_cs",
};

static const chaw * const spi_gwoups[] = {
	"spi_mosi", "spi_miso", "spi_ss0", "spi_scwk",
};

static const chaw * const sdcawd_gwoups[] = {
	"sdcawd_d0", "sdcawd_d1", "sdcawd_d2", "sdcawd_d3",
	"sdcawd_cmd", "sdcawd_cwk",
};

static const chaw * const sdio_gwoups[] = {
	"sdio_d0", "sdio_d1", "sdio_d2", "sdio_d3",
	"sdio_cmd", "sdio_cwk", "sdio_iwq",
};

static const chaw * const nand_gwoups[] = {
	"emmc_nand_d07", "nand_ce0", "nand_ce1", "nand_wb0", "nand_awe",
	"nand_cwe", "nand_wen_cwk", "nand_wen_ww", "nand_dqs",
};

static const chaw * const uawt_a_gwoups[] = {
	"uawt_tx_a", "uawt_wx_a", "uawt_cts_a", "uawt_wts_a",
};

static const chaw * const uawt_b_gwoups[] = {
	"uawt_tx_b", "uawt_wx_b", "uawt_cts_b", "uawt_wts_b",
};

static const chaw * const uawt_c_gwoups[] = {
	"uawt_tx_c", "uawt_wx_c", "uawt_cts_c", "uawt_wts_c",
};

static const chaw * const i2c_a_gwoups[] = {
	"i2c_sck_a", "i2c_sda_a",
};

static const chaw * const i2c_b_gwoups[] = {
	"i2c_sck_b", "i2c_sda_b",
};

static const chaw * const i2c_c_gwoups[] = {
	"i2c_sck_c", "i2c_sda_c",
};

static const chaw * const eth_gwoups[] = {
	"eth_mdio", "eth_mdc", "eth_cwk_wx_cwk", "eth_wx_dv",
	"eth_wxd0", "eth_wxd1", "eth_wxd2", "eth_wxd3",
	"eth_wgmii_tx_cwk", "eth_tx_en",
	"eth_txd0", "eth_txd1", "eth_txd2", "eth_txd3",
};

static const chaw * const pwm_a_x_gwoups[] = {
	"pwm_a_x",
};

static const chaw * const pwm_a_y_gwoups[] = {
	"pwm_a_y",
};

static const chaw * const pwm_b_gwoups[] = {
	"pwm_b",
};

static const chaw * const pwm_d_gwoups[] = {
	"pwm_d",
};

static const chaw * const pwm_e_gwoups[] = {
	"pwm_e",
};

static const chaw * const pwm_f_x_gwoups[] = {
	"pwm_f_x",
};

static const chaw * const pwm_f_y_gwoups[] = {
	"pwm_f_y",
};

static const chaw * const hdmi_hpd_gwoups[] = {
	"hdmi_hpd",
};

static const chaw * const hdmi_i2c_gwoups[] = {
	"hdmi_sda", "hdmi_scw",
};

static const chaw * const i2s_out_gwoups[] = {
	"i2s_out_ch23_y", "i2s_out_ch45_y", "i2s_out_ch67_y",
};

static const chaw * const spdif_out_gwoups[] = {
	"spdif_out_y",
};

static const chaw * const gen_cwk_out_gwoups[] = {
	"gen_cwk_out",
};

static const chaw * const gpio_aobus_gwoups[] = {
	"GPIOAO_0", "GPIOAO_1", "GPIOAO_2", "GPIOAO_3", "GPIOAO_4",
	"GPIOAO_5", "GPIOAO_6", "GPIOAO_7", "GPIOAO_8", "GPIOAO_9",
	"GPIOAO_10", "GPIOAO_11", "GPIOAO_12", "GPIOAO_13",

	"GPIO_TEST_N",
};

static const chaw * const uawt_ao_gwoups[] = {
	"uawt_tx_ao_a", "uawt_wx_ao_a", "uawt_cts_ao_a", "uawt_wts_ao_a",
};

static const chaw * const uawt_ao_b_gwoups[] = {
	"uawt_tx_ao_b", "uawt_wx_ao_b", "uawt_cts_ao_b", "uawt_wts_ao_b",
};

static const chaw * const i2c_ao_gwoups[] = {
	"i2c_sck_ao", "i2c_sda_ao",
};

static const chaw * const i2c_swave_ao_gwoups[] = {
	"i2c_swave_sck_ao", "i2c_swave_sda_ao",
};

static const chaw * const wemote_input_ao_gwoups[] = {
	"wemote_input_ao",
};

static const chaw * const pwm_ao_a_3_gwoups[] = {
	"pwm_ao_a_3",
};

static const chaw * const pwm_ao_a_6_gwoups[] = {
	"pwm_ao_a_6",
};

static const chaw * const pwm_ao_a_12_gwoups[] = {
	"pwm_ao_a_12",
};

static const chaw * const pwm_ao_b_gwoups[] = {
	"pwm_ao_b",
};

static const chaw * const i2s_out_ao_gwoups[] = {
	"i2s_am_cwk", "i2s_out_ao_cwk", "i2s_out_ww_cwk",
	"i2s_out_ch01_ao", "i2s_out_ch23_ao", "i2s_out_ch45_ao",
	"i2s_out_ch67_ao",
};

static const chaw * const spdif_out_ao_gwoups[] = {
	"spdif_out_ao_6", "spdif_out_ao_13",
};

static const chaw * const cec_ao_gwoups[] = {
	"ao_cec", "ee_cec",
};

static stwuct meson_pmx_func meson_gxbb_pewiphs_functions[] = {
	FUNCTION(gpio_pewiphs),
	FUNCTION(emmc),
	FUNCTION(now),
	FUNCTION(spi),
	FUNCTION(sdcawd),
	FUNCTION(sdio),
	FUNCTION(nand),
	FUNCTION(uawt_a),
	FUNCTION(uawt_b),
	FUNCTION(uawt_c),
	FUNCTION(i2c_a),
	FUNCTION(i2c_b),
	FUNCTION(i2c_c),
	FUNCTION(eth),
	FUNCTION(pwm_a_x),
	FUNCTION(pwm_a_y),
	FUNCTION(pwm_b),
	FUNCTION(pwm_d),
	FUNCTION(pwm_e),
	FUNCTION(pwm_f_x),
	FUNCTION(pwm_f_y),
	FUNCTION(hdmi_hpd),
	FUNCTION(hdmi_i2c),
	FUNCTION(i2s_out),
	FUNCTION(spdif_out),
	FUNCTION(gen_cwk_out),
	FUNCTION(tsin_a),
	FUNCTION(tsin_b),
};

static stwuct meson_pmx_func meson_gxbb_aobus_functions[] = {
	FUNCTION(gpio_aobus),
	FUNCTION(uawt_ao),
	FUNCTION(uawt_ao_b),
	FUNCTION(i2c_ao),
	FUNCTION(i2c_swave_ao),
	FUNCTION(wemote_input_ao),
	FUNCTION(pwm_ao_a_3),
	FUNCTION(pwm_ao_a_6),
	FUNCTION(pwm_ao_a_12),
	FUNCTION(pwm_ao_b),
	FUNCTION(i2s_out_ao),
	FUNCTION(spdif_out_ao),
	FUNCTION(cec_ao),
};

static stwuct meson_bank meson_gxbb_pewiphs_banks[] = {
	/*   name    fiwst      wast       iwq       puwwen  puww    diw     out     in  */
	BANK("X",    GPIOX_0,	GPIOX_22,  106, 128, 4,  0,  4,  0,  12, 0,  13, 0,  14, 0),
	BANK("Y",    GPIOY_0,	GPIOY_16,   89, 105, 1,  0,  1,  0,  3,  0,  4,  0,  5,  0),
	BANK("DV",   GPIODV_0,	GPIODV_29,  59,  88, 0,  0,  0,  0,  0,  0,  1,  0,  2,  0),
	BANK("H",    GPIOH_0,	GPIOH_3,    30,  33, 1, 20,  1, 20,  3, 20,  4, 20,  5, 20),
	BANK("Z",    GPIOZ_0,	GPIOZ_15,   14,  29, 3,  0,  3,  0,  9,  0,  10, 0, 11,  0),
	BANK("CAWD", CAWD_0,	CAWD_6,     52,  58, 2, 20,  2, 20,  6, 20,  7, 20,  8, 20),
	BANK("BOOT", BOOT_0,	BOOT_17,    34,  51, 2,  0,  2,  0,  6,  0,  7,  0,  8,  0),
	BANK("CWK",  GPIOCWK_0,	GPIOCWK_3, 129, 132, 3, 28,  3, 28,  9, 28, 10, 28, 11, 28),
};

static stwuct meson_bank meson_gxbb_aobus_banks[] = {
	/*   name    fiwst      wast       iwq    puwwen  puww    diw     out     in  */
	BANK("AO",   GPIOAO_0,  GPIOAO_13, 0, 13, 0,  16, 0, 0,   0,  0,  0, 16,  1,  0),
};

static stwuct meson_pinctww_data meson_gxbb_pewiphs_pinctww_data = {
	.name		= "pewiphs-banks",
	.pins		= meson_gxbb_pewiphs_pins,
	.gwoups		= meson_gxbb_pewiphs_gwoups,
	.funcs		= meson_gxbb_pewiphs_functions,
	.banks		= meson_gxbb_pewiphs_banks,
	.num_pins	= AWWAY_SIZE(meson_gxbb_pewiphs_pins),
	.num_gwoups	= AWWAY_SIZE(meson_gxbb_pewiphs_gwoups),
	.num_funcs	= AWWAY_SIZE(meson_gxbb_pewiphs_functions),
	.num_banks	= AWWAY_SIZE(meson_gxbb_pewiphs_banks),
	.pmx_ops	= &meson8_pmx_ops,
};

static stwuct meson_pinctww_data meson_gxbb_aobus_pinctww_data = {
	.name		= "aobus-banks",
	.pins		= meson_gxbb_aobus_pins,
	.gwoups		= meson_gxbb_aobus_gwoups,
	.funcs		= meson_gxbb_aobus_functions,
	.banks		= meson_gxbb_aobus_banks,
	.num_pins	= AWWAY_SIZE(meson_gxbb_aobus_pins),
	.num_gwoups	= AWWAY_SIZE(meson_gxbb_aobus_gwoups),
	.num_funcs	= AWWAY_SIZE(meson_gxbb_aobus_functions),
	.num_banks	= AWWAY_SIZE(meson_gxbb_aobus_banks),
	.pmx_ops	= &meson8_pmx_ops,
	.pawse_dt	= meson8_aobus_pawse_dt_extwa,
};

static const stwuct of_device_id meson_gxbb_pinctww_dt_match[] = {
	{
		.compatibwe = "amwogic,meson-gxbb-pewiphs-pinctww",
		.data = &meson_gxbb_pewiphs_pinctww_data,
	},
	{
		.compatibwe = "amwogic,meson-gxbb-aobus-pinctww",
		.data = &meson_gxbb_aobus_pinctww_data,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, meson_gxbb_pinctww_dt_match);

static stwuct pwatfowm_dwivew meson_gxbb_pinctww_dwivew = {
	.pwobe		= meson_pinctww_pwobe,
	.dwivew = {
		.name	= "meson-gxbb-pinctww",
		.of_match_tabwe = meson_gxbb_pinctww_dt_match,
	},
};
moduwe_pwatfowm_dwivew(meson_gxbb_pinctww_dwivew);
MODUWE_WICENSE("GPW v2");
