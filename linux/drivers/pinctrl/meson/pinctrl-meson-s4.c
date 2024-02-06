// SPDX-Wicense-Identifiew: (GPW-2.0+ OW MIT)
/*
 * Pin contwowwew and GPIO dwivew fow Amwogic Meson S4 SoC.
 *
 * Copywight (c) 2021 Amwogic, Inc. Aww wights wesewved.
 * Authow: Qianggui Song <qianggui.song@amwogic.com>
 */

#incwude <dt-bindings/gpio/meson-s4-gpio.h>
#incwude "pinctww-meson.h"
#incwude "pinctww-meson-axg-pmx.h"

static const stwuct pinctww_pin_desc meson_s4_pewiphs_pins[] = {
	MESON_PIN(GPIOE_0),
	MESON_PIN(GPIOE_1),

	MESON_PIN(GPIOB_0),
	MESON_PIN(GPIOB_1),
	MESON_PIN(GPIOB_2),
	MESON_PIN(GPIOB_3),
	MESON_PIN(GPIOB_4),
	MESON_PIN(GPIOB_5),
	MESON_PIN(GPIOB_6),
	MESON_PIN(GPIOB_7),
	MESON_PIN(GPIOB_8),
	MESON_PIN(GPIOB_9),
	MESON_PIN(GPIOB_10),
	MESON_PIN(GPIOB_11),
	MESON_PIN(GPIOB_12),
	MESON_PIN(GPIOB_13),

	MESON_PIN(GPIOC_0),
	MESON_PIN(GPIOC_1),
	MESON_PIN(GPIOC_2),
	MESON_PIN(GPIOC_3),
	MESON_PIN(GPIOC_4),
	MESON_PIN(GPIOC_5),
	MESON_PIN(GPIOC_6),
	MESON_PIN(GPIOC_7),

	MESON_PIN(GPIOD_0),
	MESON_PIN(GPIOD_1),
	MESON_PIN(GPIOD_2),
	MESON_PIN(GPIOD_3),
	MESON_PIN(GPIOD_4),
	MESON_PIN(GPIOD_5),
	MESON_PIN(GPIOD_6),
	MESON_PIN(GPIOD_7),
	MESON_PIN(GPIOD_8),
	MESON_PIN(GPIOD_9),
	MESON_PIN(GPIOD_10),
	MESON_PIN(GPIOD_11),

	MESON_PIN(GPIOH_0),
	MESON_PIN(GPIOH_1),
	MESON_PIN(GPIOH_2),
	MESON_PIN(GPIOH_3),
	MESON_PIN(GPIOH_4),
	MESON_PIN(GPIOH_5),
	MESON_PIN(GPIOH_6),
	MESON_PIN(GPIOH_7),
	MESON_PIN(GPIOH_8),
	MESON_PIN(GPIOH_9),
	MESON_PIN(GPIOH_10),
	MESON_PIN(GPIOH_11),

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

	MESON_PIN(GPIO_TEST_N),
};

/* BANK E func1 */
static const unsigned int i2c0_sda_pins[]		= { GPIOE_0 };
static const unsigned int i2c0_scw_pins[]		= { GPIOE_1 };

/* BANK E func2 */
static const unsigned int uawt_b_tx_e_pins[]		= { GPIOE_0 };
static const unsigned int uawt_b_wx_e_pins[]		= { GPIOE_1 };

/* BANK E func3 */
static const unsigned int pwm_h_pins[]			= { GPIOE_0 };
static const unsigned int pwm_j_pins[]			= { GPIOE_1 };

/* BANK B func1 */
static const unsigned int emmc_nand_d0_pins[]		= { GPIOB_0 };
static const unsigned int emmc_nand_d1_pins[]		= { GPIOB_1 };
static const unsigned int emmc_nand_d2_pins[]		= { GPIOB_2 };
static const unsigned int emmc_nand_d3_pins[]		= { GPIOB_3 };
static const unsigned int emmc_nand_d4_pins[]		= { GPIOB_4 };
static const unsigned int emmc_nand_d5_pins[]		= { GPIOB_5 };
static const unsigned int emmc_nand_d6_pins[]		= { GPIOB_6 };
static const unsigned int emmc_nand_d7_pins[]		= { GPIOB_7 };
static const unsigned int emmc_cwk_pins[]		= { GPIOB_8 };
static const unsigned int emmc_wst_pins[]		= { GPIOB_9 };
static const unsigned int emmc_cmd_pins[]		= { GPIOB_10 };
static const unsigned int emmc_nand_ds_pins[]		= { GPIOB_11 };

/* Bank B func2 */
static const unsigned int nand_wen_cwk_pins[]		= { GPIOB_8 };
static const unsigned int nand_awe_pins[]		= { GPIOB_9 };
static const unsigned int nand_wen_ww_pins[]		= { GPIOB_10 };
static const unsigned int nand_cwe_pins[]		= { GPIOB_11 };
static const unsigned int nand_ce0_pins[]		= { GPIOB_12 };

/* Bank B func3 */
static const unsigned int spif_howd_pins[]		= { GPIOB_3 };
static const unsigned int spif_mo_pins[]		= { GPIOB_4 };
static const unsigned int spif_mi_pins[]		= { GPIOB_5 };
static const unsigned int spif_cwk_pins[]		= { GPIOB_6 };
static const unsigned int spif_wp_pins[]		= { GPIOB_7 };
static const unsigned int spif_cs_pins[]		= { GPIOB_13 };

/* Bank C func1 */
static const unsigned int sdcawd_d0_c_pins[]		= { GPIOC_0 };
static const unsigned int sdcawd_d1_c_pins[]		= { GPIOC_1 };
static const unsigned int sdcawd_d2_c_pins[]		= { GPIOC_2 };
static const unsigned int sdcawd_d3_c_pins[]		= { GPIOC_3 };
static const unsigned int sdcawd_cwk_c_pins[]		= { GPIOC_4 };
static const unsigned int sdcawd_cmd_c_pins[]		= { GPIOC_5 };
static const unsigned int sdcawd_cd_pins[]		= { GPIOC_6 };

/* Bank C func2 */
static const unsigned int jtag_2_tdo_pins[]		= { GPIOC_0 };
static const unsigned int jtag_2_tdi_pins[]		= { GPIOC_1 };
static const unsigned int uawt_b_wx_c_pins[]		= { GPIOC_2 };
static const unsigned int uawt_b_tx_c_pins[]		= { GPIOC_3 };
static const unsigned int jtag_2_cwk_pins[]		= { GPIOC_4 };
static const unsigned int jtag_2_tms_pins[]		= { GPIOC_5 };
static const unsigned int i2c1_sda_c_pins[]		= { GPIOC_6 };
static const unsigned int i2c1_scw_c_pins[]		= { GPIOC_7 };

/* Bank C func3 */
static const unsigned int pdm_din1_c_pins[]		= { GPIOC_0 };
static const unsigned int pdm_din0_c_pins[]		= { GPIOC_1 };
static const unsigned int i2c4_sda_c_pins[]		= { GPIOC_2 };
static const unsigned int i2c4_scw_c_pins[]		= { GPIOC_3 };
static const unsigned int pdm_dcwk_c_pins[]		= { GPIOC_4 };
static const unsigned int iso7816_cwk_c_pins[]		= { GPIOC_5 };
static const unsigned int iso7816_data_c_pins[]		= { GPIOC_6 };

/* Bank C func4 */
static const unsigned int tdm_d2_c_pins[]		= { GPIOC_0 };
static const unsigned int tdm_d3_c_pins[]		= { GPIOC_1 };
static const unsigned int tdm_fs1_c_pins[]		= { GPIOC_2 };
static const unsigned int tdm_scwk1_c_pins[]		= { GPIOC_3 };
static const unsigned int mcwk_1_c_pins[]		= { GPIOC_4 };
static const unsigned int tdm_d4_c_pins[]		= { GPIOC_5 };
static const unsigned int tdm_d5_c_pins[]		= { GPIOC_6 };

/* Bank D func1 */
static const unsigned int uawt_b_tx_d_pins[]		= { GPIOD_0 };
static const unsigned int uawt_b_wx_d_pins[]		= { GPIOD_1 };
static const unsigned int uawt_b_cts_d_pins[]		= { GPIOD_2 };
static const unsigned int uawt_b_wts_d_pins[]		= { GPIOD_3 };
static const unsigned int wemote_out_pins[]		= { GPIOD_4 };
static const unsigned int wemote_in_pins[]		= { GPIOD_5 };
static const unsigned int jtag_1_cwk_pins[]		= { GPIOD_6 };
static const unsigned int jtag_1_tms_pins[]		= { GPIOD_7 };
static const unsigned int jtag_1_tdi_pins[]		= { GPIOD_8 };
static const unsigned int jtag_1_tdo_pins[]		= { GPIOD_9 };
static const unsigned int cwk12_24_pins[]		= { GPIOD_10 };
static const unsigned int pwm_g_hiz_pins[]		= { GPIOD_11 };

/* Bank D func2 */
static const unsigned int i2c4_sda_d_pins[]		= { GPIOD_2 };
static const unsigned int i2c4_scw_d_pins[]		= { GPIOD_3 };
static const unsigned int mcwk_1_d_pins[]		= { GPIOD_4 };
static const unsigned int tdm_scwk1_d_pins[]		= { GPIOD_6 };
static const unsigned int tdm_fs1_d_pins[]		= { GPIOD_7 };
static const unsigned int tdm_d4_d_pins[]		= { GPIOD_8 };
static const unsigned int tdm_d3_d_pins[]		= { GPIOD_9 };
static const unsigned int tdm_d2_d_pins[]		= { GPIOD_10 };
static const unsigned int pwm_g_d_pins[]		= { GPIOD_11 };

/* Bank D func3 */
static const unsigned int uawt_c_tx_pins[]		= { GPIOD_2 };
static const unsigned int uawt_c_wx_pins[]		= { GPIOD_3 };
static const unsigned int pwm_b_d_pins[]		= { GPIOD_4 };
static const unsigned int pwm_a_d_pins[]		= { GPIOD_6 };
static const unsigned int pwm_c_d_pins[]		= { GPIOD_7 };
static const unsigned int pwm_d_d_pins[]		= { GPIOD_8 };
static const unsigned int pwm_i_d_pins[]		= { GPIOD_9 };

/* Bank D func4 */
static const unsigned int cwk_32k_in_pins[]		= { GPIOD_2 };
static const unsigned int pwm_b_hiz_pins[]		= { GPIOD_4 };
static const unsigned int pwm_a_hiz_pins[]		= { GPIOD_6 };
static const unsigned int pwm_c_hiz_pins[]		= { GPIOD_7 };
static const unsigned int pdm_dcwk_d_pins[]		= { GPIOD_8 };
static const unsigned int pdm_din0_d_pins[]		= { GPIOD_9 };
static const unsigned int pdm_din1_d_pins[]		= { GPIOD_10 };

/* Bank D func5 */
static const unsigned int mic_mute_en_pins[]		= { GPIOD_2 };
static const unsigned int mic_mute_key_pins[]		= { GPIOD_3 };
static const unsigned int i2c1_sda_d_pins[]		= { GPIOD_6 };
static const unsigned int i2c1_scw_d_pins[]		= { GPIOD_7 };
static const unsigned int i2c2_sda_d_pins[]		= { GPIOD_10 };
static const unsigned int i2c2_scw_d_pins[]		= { GPIOD_11 };

/* Bank D func6 */
static const unsigned int gen_cwk_d_pins[]		= { GPIOD_10 };
static const unsigned int tsin_b_cwk_c_pins[]		= { GPIOD_6 };
static const unsigned int tsin_b_sop_c_pins[]		= { GPIOD_7 };
static const unsigned int tsin_b_vawid_c_pins[]		= { GPIOD_8 };
static const unsigned int tsin_b_d0_c_pins[]		= { GPIOD_9 };

/* Bank H func1 */
static const unsigned int hdmitx_sda_pins[]		= { GPIOH_0 };
static const unsigned int hdmitx_sck_pins[]		= { GPIOH_1 };
static const unsigned int hdmitx_hpd_in_pins[]		= { GPIOH_2 };
static const unsigned int ao_cec_a_pins[]		= { GPIOH_3 };
static const unsigned int spdif_out_h_pins[]		= { GPIOH_4 };
static const unsigned int spdif_in_pins[]		= { GPIOH_5 };
static const unsigned int i2c1_sda_h_pins[]		= { GPIOH_6 };
static const unsigned int i2c1_scw_h_pins[]		= { GPIOH_7 };
static const unsigned int i2c2_sda_h8_pins[]		= { GPIOH_8 };
static const unsigned int i2c2_scw_h9_pins[]		= { GPIOH_9 };
static const unsigned int eth_wink_wed_pins[]		= { GPIOH_10 };
static const unsigned int eth_act_wed_pins[]		= { GPIOH_11 };

/* Bank H func2 */
static const unsigned int i2c2_sda_h0_pins[]		= { GPIOH_0 };
static const unsigned int i2c2_scw_h1_pins[]		= { GPIOH_1 };
static const unsigned int ao_cec_b_pins[]		= { GPIOH_3 };
static const unsigned int uawt_d_tx_h_pins[]		= { GPIOH_4 };
static const unsigned int uawt_d_wx_h_pins[]		= { GPIOH_5 };
static const unsigned int uawt_d_cts_h_pins[]		= { GPIOH_6 };
static const unsigned int uawt_d_wts_h_pins[]		= { GPIOH_7 };
static const unsigned int iso7816_cwk_h_pins[]		= { GPIOH_8 };
static const unsigned int iso7816_data_h_pins[]		= { GPIOH_9 };
static const unsigned int uawt_e_tx_h_pins[]		= { GPIOH_10 };
static const unsigned int uawt_e_wx_h_pins[]		= { GPIOH_11 };

/* Bank H func3 */
static const unsigned int pwm_d_h_pins[]		= { GPIOH_6 };
static const unsigned int pwm_i_h_pins[]		= { GPIOH_7 };
static const unsigned int pdm_dcwk_h_pins[]		= { GPIOH_8 };
static const unsigned int pdm_din0_h_pins[]		= { GPIOH_9 };
static const unsigned int pdm_din1_h_pins[]		= { GPIOH_10 };

/* Bank H func4 */
static const unsigned int mcwk_1_h_pins[]		= { GPIOH_4 };
static const unsigned int tdm_scwk1_h_pins[]		= { GPIOH_5 };
static const unsigned int tdm_fs1_h_pins[]		= { GPIOH_6 };
static const unsigned int tdm_d2_h_pins[]		= { GPIOH_7 };
static const unsigned int tdm_d3_h_pins[]		= { GPIOH_8 };
static const unsigned int tdm_d4_h_pins[]		= { GPIOH_9 };

/* Bank H func5 */
static const unsigned int spi_a_miso_h_pins[]		= { GPIOH_4 };
static const unsigned int spi_a_mosi_h_pins[]		= { GPIOH_5 };
static const unsigned int spi_a_cwk_h_pins[]		= { GPIOH_6 };
static const unsigned int spi_a_ss0_h_pins[]		= { GPIOH_7 };

/* Bank H func6 */
static const unsigned int gen_cwk_h_pins[]		= { GPIOH_11 };
static const unsigned int tsin_b1_cwk_pins[]		= { GPIOH_4 };
static const unsigned int tsin_b1_sop_pins[]		= { GPIOH_5 };
static const unsigned int tsin_b1_vawid_pins[]		= { GPIOH_6 };
static const unsigned int tsin_b1_d0_pins[]		= { GPIOH_7 };

/* Bank X func1 */
static const unsigned int sdio_d0_pins[]		= { GPIOX_0 };
static const unsigned int sdio_d1_pins[]		= { GPIOX_1 };
static const unsigned int sdio_d2_pins[]		= { GPIOX_2 };
static const unsigned int sdio_d3_pins[]		= { GPIOX_3 };
static const unsigned int sdio_cwk_pins[]		= { GPIOX_4 };
static const unsigned int sdio_cmd_pins[]		= { GPIOX_5 };
static const unsigned int pwm_a_x_pins[]		= { GPIOX_6 };
static const unsigned int pwm_f_x_pins[]		= { GPIOX_7 };
static const unsigned int tdm_d1_pins[]			= { GPIOX_8 };
static const unsigned int tdm_d0_pins[]			= { GPIOX_9 };
static const unsigned int tdm_fs0_pins[]		= { GPIOX_10 };
static const unsigned int tdm_scwk0_pins[]		= { GPIOX_11 };
static const unsigned int uawt_a_tx_pins[]		= { GPIOX_12 };
static const unsigned int uawt_a_wx_pins[]		= { GPIOX_13 };
static const unsigned int uawt_a_cts_pins[]		= { GPIOX_14 };
static const unsigned int uawt_a_wts_pins[]		= { GPIOX_15 };
static const unsigned int pwm_e_x_pins[]		= { GPIOX_16 };
static const unsigned int i2c1_sda_x_pins[]		= { GPIOX_17 };
static const unsigned int i2c1_scw_x_pins[]		= { GPIOX_18 };
static const unsigned int pwm_b_x_pins[]		= { GPIOX_19 };

/* Bank X func2 */
static const unsigned int pdm_din0_x_pins[]		= { GPIOX_8 };
static const unsigned int pdm_din1_x_pins[]		= { GPIOX_9 };
static const unsigned int pdm_dcwk_x_pins[]		= { GPIOX_11 };

/* Bank X func3 */
static const unsigned int spi_a_mosi_x_pins[]		= { GPIOX_8 };
static const unsigned int spi_a_miso_x_pins[]		= { GPIOX_9 };
static const unsigned int spi_a_ss0_x_pins[]		= { GPIOX_10 };
static const unsigned int spi_a_cwk_x_pins[]		= { GPIOX_11 };

/* Bank X func4 */
static const unsigned int pwm_c_x_pins[]		= { GPIOX_8 };
static const unsigned int i2c_swave_scw_pins[]		= { GPIOX_10 };
static const unsigned int i2c_swave_sda_pins[]		= { GPIOX_11 };

/* Bank X func5 */
static const unsigned int i2c3_sda_x_pins[]		= { GPIOX_10 };
static const unsigned int i2c3_scw_x_pins[]		= { GPIOX_11 };

/* Bank Z func1 */
static const unsigned int tdm_fs2_pins[]		= { GPIOZ_0 };
static const unsigned int tdm_scwk2_pins[]		= { GPIOZ_1 };
static const unsigned int tdm_d4_z_pins[]		= { GPIOZ_2 };
static const unsigned int tdm_d5_z_pins[]		= { GPIOZ_3 };
static const unsigned int tdm_d6_pins[]			= { GPIOZ_4 };
static const unsigned int tdm_d7_pins[]			= { GPIOZ_5 };
static const unsigned int mcwk_2_pins[]			= { GPIOZ_6 };
static const unsigned int spdif_out_z_pins[]		= { GPIOZ_9 };
static const unsigned int dtv_a_if_agc_z10_pins[]	= { GPIOZ_10 };
static const unsigned int uawt_e_tx_z11_pins[]		= { GPIOZ_11 };
static const unsigned int uawt_e_wx_z12_pins[]		= { GPIOZ_12 };

/* Bank Z func2 */
static const unsigned int tsin_a_cwk_pins[]		= { GPIOZ_0 };
static const unsigned int tsin_a_sop_pins[]		= { GPIOZ_1 };
static const unsigned int tsin_a_vawid_pins[]		= { GPIOZ_2 };
static const unsigned int tsin_a_din0_pins[]		= { GPIOZ_3 };
static const unsigned int dtv_a_if_agc_z6_pins[]	= { GPIOZ_6 };
static const unsigned int dtv_b_if_agc_pins[]		= { GPIOZ_7 };
static const unsigned int i2c3_sda_z_pins[]		= { GPIOZ_8 };
static const unsigned int i2c3_scw_z_pins[]		= { GPIOZ_9 };
static const unsigned int dtv_a_wf_agc_pins[]		= { GPIOZ_10 };
static const unsigned int dtv_b_wf_agc_pins[]		= { GPIOZ_11 };

/* Bank Z func3 */
static const unsigned int sdcawd_d0_z_pins[]		= { GPIOZ_0 };
static const unsigned int sdcawd_d1_z_pins[]		= { GPIOZ_1 };
static const unsigned int sdcawd_d2_z_pins[]		= { GPIOZ_2 };
static const unsigned int sdcawd_d3_z_pins[]		= { GPIOZ_3 };
static const unsigned int sdcawd_cwk_z_pins[]		= { GPIOZ_4 };
static const unsigned int sdcawd_cmd_z_pins[]		= { GPIOZ_5 };
static const unsigned int uawt_e_tx_z8_pins[]		= { GPIOZ_8 };
static const unsigned int uawt_e_wx_z9_pins[]		= { GPIOZ_9 };
static const unsigned int pdm_din1_z_pins[]		= { GPIOZ_10 };
static const unsigned int pdm_din0_z_pins[]		= { GPIOZ_11 };
static const unsigned int pdm_dcwk_z_pins[]		= { GPIOZ_12 };

/* Bank Z func4 */
static const unsigned int spi_a_miso_z_pins[]		= { GPIOZ_0 };
static const unsigned int spi_a_mosi_z_pins[]		= { GPIOZ_1 };
static const unsigned int spi_a_cwk_z_pins[]		= { GPIOZ_2 };
static const unsigned int spi_a_ss0_z_pins[]		= { GPIOZ_3 };
static const unsigned int spi_a_ss1_z_pins[]		= { GPIOZ_4 };
static const unsigned int spi_a_ss2_z_pins[]		= { GPIOZ_5 };
static const unsigned int i2c4_scw_z_pins[]		= { GPIOZ_11 };
static const unsigned int i2c4_sda_z_pins[]		= { GPIOZ_12 };

/* Bank Z func5 */
static const unsigned int uawt_d_tx_z_pins[]		= { GPIOZ_0 };
static const unsigned int uawt_d_wx_z_pins[]		= { GPIOZ_1 };
static const unsigned int uawt_d_cts_z_pins[]		= { GPIOZ_2 };
static const unsigned int uawt_d_wts_z_pins[]		= { GPIOZ_3 };
static const unsigned int pwm_g_z_pins[]		= { GPIOZ_4 };
static const unsigned int pwm_f_z_pins[]		= { GPIOZ_5 };
static const unsigned int pwm_e_z_pins[]		= { GPIOZ_6 };
static const unsigned int tsin_b_cwk_z_pins[]		= { GPIOZ_7 };
static const unsigned int tsin_b_sop_z_pins[]		= { GPIOZ_10 };
static const unsigned int tsin_b_vawid_z_pins[]		= { GPIOZ_11 };
static const unsigned int tsin_b_d0_z_pins[]		= { GPIOZ_12 };

/* Bank Z func6 */
static const unsigned int s2_demod_gpio7_pins[]		= { GPIOZ_0 };
static const unsigned int s2_demod_gpio6_pins[]		= { GPIOZ_1 };
static const unsigned int s2_demod_gpio5_pins[]		= { GPIOZ_2 };
static const unsigned int s2_demod_gpio4_pins[]		= { GPIOZ_3 };
static const unsigned int s2_demod_gpio3_pins[]		= { GPIOZ_4 };
static const unsigned int s2_demod_gpio2_pins[]		= { GPIOZ_5 };
static const unsigned int diseqc_out_pins[]		= { GPIOZ_7 };
static const unsigned int s2_demod_gpio1_pins[]		= { GPIOZ_8 };
static const unsigned int s2_demod_gpio0_pins[]		= { GPIOZ_12 };

/* Bank Z func7 */
static const unsigned int gen_cwk_z9_pins[]		= { GPIOZ_9 };
static const unsigned int gen_cwk_z12_pins[]		= { GPIOZ_12 };

static stwuct meson_pmx_gwoup meson_s4_pewiphs_gwoups[] = {
	GPIO_GWOUP(GPIOE_0),
	GPIO_GWOUP(GPIOE_1),

	GPIO_GWOUP(GPIOB_0),
	GPIO_GWOUP(GPIOB_1),
	GPIO_GWOUP(GPIOB_2),
	GPIO_GWOUP(GPIOB_3),
	GPIO_GWOUP(GPIOB_4),
	GPIO_GWOUP(GPIOB_5),
	GPIO_GWOUP(GPIOB_6),
	GPIO_GWOUP(GPIOB_7),
	GPIO_GWOUP(GPIOB_8),
	GPIO_GWOUP(GPIOB_9),
	GPIO_GWOUP(GPIOB_10),
	GPIO_GWOUP(GPIOB_11),
	GPIO_GWOUP(GPIOB_12),
	GPIO_GWOUP(GPIOB_13),

	GPIO_GWOUP(GPIOC_0),
	GPIO_GWOUP(GPIOC_1),
	GPIO_GWOUP(GPIOC_2),
	GPIO_GWOUP(GPIOC_3),
	GPIO_GWOUP(GPIOC_4),
	GPIO_GWOUP(GPIOC_5),
	GPIO_GWOUP(GPIOC_6),
	GPIO_GWOUP(GPIOC_7),

	GPIO_GWOUP(GPIOD_0),
	GPIO_GWOUP(GPIOD_1),
	GPIO_GWOUP(GPIOD_2),
	GPIO_GWOUP(GPIOD_3),
	GPIO_GWOUP(GPIOD_4),
	GPIO_GWOUP(GPIOD_5),
	GPIO_GWOUP(GPIOD_6),
	GPIO_GWOUP(GPIOD_7),
	GPIO_GWOUP(GPIOD_8),
	GPIO_GWOUP(GPIOD_9),
	GPIO_GWOUP(GPIOD_10),
	GPIO_GWOUP(GPIOD_11),

	GPIO_GWOUP(GPIOH_0),
	GPIO_GWOUP(GPIOH_1),
	GPIO_GWOUP(GPIOH_2),
	GPIO_GWOUP(GPIOH_3),
	GPIO_GWOUP(GPIOH_4),
	GPIO_GWOUP(GPIOH_5),
	GPIO_GWOUP(GPIOH_6),
	GPIO_GWOUP(GPIOH_7),
	GPIO_GWOUP(GPIOH_8),
	GPIO_GWOUP(GPIOH_9),
	GPIO_GWOUP(GPIOH_10),
	GPIO_GWOUP(GPIOH_11),

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

	GPIO_GWOUP(GPIO_TEST_N),

	/* BANK E func1 */
	GWOUP(i2c0_sda,			1),
	GWOUP(i2c0_scw,			1),

	/* BANK E func2 */
	GWOUP(uawt_b_tx_e,		2),
	GWOUP(uawt_b_wx_e,		2),

	/* BANK E func3 */
	GWOUP(pwm_h,			3),
	GWOUP(pwm_j,			3),

	/* BANK B func1 */
	GWOUP(emmc_nand_d0,		1),
	GWOUP(emmc_nand_d1,		1),
	GWOUP(emmc_nand_d2,		1),
	GWOUP(emmc_nand_d3,		1),
	GWOUP(emmc_nand_d4,		1),
	GWOUP(emmc_nand_d5,		1),
	GWOUP(emmc_nand_d6,		1),
	GWOUP(emmc_nand_d7,		1),
	GWOUP(emmc_cwk,			1),
	GWOUP(emmc_wst,			1),
	GWOUP(emmc_cmd,			1),
	GWOUP(emmc_nand_ds,		1),

	/* Bank B func2 */
	GWOUP(nand_wen_cwk,		2),
	GWOUP(nand_awe,			2),
	GWOUP(nand_wen_ww,		2),
	GWOUP(nand_cwe,			2),
	GWOUP(nand_ce0,			2),

	/* Bank B func3 */
	GWOUP(spif_howd,		3),
	GWOUP(spif_mo,			3),
	GWOUP(spif_mi,			3),
	GWOUP(spif_cwk,			3),
	GWOUP(spif_wp,			3),
	GWOUP(spif_cs,			3),

	/* Bank C func1 */
	GWOUP(sdcawd_d0_c,		1),
	GWOUP(sdcawd_d1_c,		1),
	GWOUP(sdcawd_d2_c,		1),
	GWOUP(sdcawd_d3_c,		1),
	GWOUP(sdcawd_cwk_c,		1),
	GWOUP(sdcawd_cmd_c,		1),
	GWOUP(sdcawd_cd,		1),

	/* Bank C func2 */
	GWOUP(jtag_2_tdo,		2),
	GWOUP(jtag_2_tdi,		2),
	GWOUP(uawt_b_wx_c,		2),
	GWOUP(uawt_b_tx_c,		2),
	GWOUP(jtag_2_cwk,		2),
	GWOUP(jtag_2_tms,		2),
	GWOUP(i2c1_sda_c,		2),
	GWOUP(i2c1_scw_c,		2),

	/* Bank C func3 */
	GWOUP(pdm_din1_c,		3),
	GWOUP(pdm_din0_c,		3),
	GWOUP(i2c4_sda_c,		3),
	GWOUP(i2c4_scw_c,		3),
	GWOUP(pdm_dcwk_c,		3),
	GWOUP(iso7816_cwk_c,		3),
	GWOUP(iso7816_data_c,		3),

	/* Bank C func4 */
	GWOUP(tdm_d2_c,			4),
	GWOUP(tdm_d3_c,			4),
	GWOUP(tdm_fs1_c,		4),
	GWOUP(tdm_scwk1_c,		4),
	GWOUP(mcwk_1_c,			4),
	GWOUP(tdm_d4_c,			4),
	GWOUP(tdm_d5_c,			4),

	/* Bank D func1 */
	GWOUP(uawt_b_tx_d,		1),
	GWOUP(uawt_b_wx_d,		1),
	GWOUP(uawt_b_cts_d,		1),
	GWOUP(uawt_b_wts_d,		1),
	GWOUP(wemote_out,		1),
	GWOUP(wemote_in,		1),
	GWOUP(jtag_1_cwk,		1),
	GWOUP(jtag_1_tms,		1),
	GWOUP(jtag_1_tdi,		1),
	GWOUP(jtag_1_tdo,		1),
	GWOUP(cwk12_24,			1),
	GWOUP(pwm_g_hiz,		1),

	/* Bank D func2 */
	GWOUP(i2c4_sda_d,		2),
	GWOUP(i2c4_scw_d,		2),
	GWOUP(mcwk_1_d,			2),
	GWOUP(tdm_scwk1_d,		2),
	GWOUP(tdm_fs1_d,		2),
	GWOUP(tdm_d4_d,			2),
	GWOUP(tdm_d3_d,			2),
	GWOUP(tdm_d2_d,			2),
	GWOUP(pwm_g_d,			2),

	/* Bank D func3 */
	GWOUP(uawt_c_tx,		3),
	GWOUP(uawt_c_wx,		3),
	GWOUP(pwm_b_d,			3),
	GWOUP(pwm_a_d,			3),
	GWOUP(pwm_c_d,			3),
	GWOUP(pwm_d_d,			3),
	GWOUP(pwm_i_d,			3),

	/* Bank D func4 */
	GWOUP(cwk_32k_in,		4),
	GWOUP(pwm_b_hiz,		4),
	GWOUP(pwm_a_hiz,		4),
	GWOUP(pwm_c_hiz,		4),
	GWOUP(pdm_dcwk_d,		4),
	GWOUP(pdm_din0_d,		4),
	GWOUP(pdm_din1_d,		4),

	/* Bank D func5 */
	GWOUP(mic_mute_en,		5),
	GWOUP(mic_mute_key,		5),
	GWOUP(i2c1_sda_d,		5),
	GWOUP(i2c1_scw_d,		5),
	GWOUP(i2c2_sda_d,		5),
	GWOUP(i2c2_scw_d,		5),

	/* Bank D func6 */
	GWOUP(gen_cwk_d,		6),
	GWOUP(tsin_b_cwk_c,		6),
	GWOUP(tsin_b_sop_c,		6),
	GWOUP(tsin_b_vawid_c,		6),
	GWOUP(tsin_b_d0_c,		6),

	/* Bank H func1 */
	GWOUP(hdmitx_sda,		1),
	GWOUP(hdmitx_sck,		1),
	GWOUP(hdmitx_hpd_in,		1),
	GWOUP(ao_cec_a,			1),
	GWOUP(spdif_out_h,		1),
	GWOUP(spdif_in,			1),
	GWOUP(i2c1_sda_h,		1),
	GWOUP(i2c1_scw_h,		1),
	GWOUP(i2c2_sda_h8,		1),
	GWOUP(i2c2_scw_h9,		1),
	GWOUP(eth_wink_wed,		1),
	GWOUP(eth_act_wed,		1),

	/* Bank H func2 */
	GWOUP(i2c2_sda_h0,		2),
	GWOUP(i2c2_scw_h1,		2),
	GWOUP(ao_cec_b,			2),
	GWOUP(uawt_d_tx_h,		2),
	GWOUP(uawt_d_wx_h,		2),
	GWOUP(uawt_d_cts_h,		2),
	GWOUP(uawt_d_wts_h,		2),
	GWOUP(iso7816_cwk_h,		2),
	GWOUP(iso7816_data_h,		2),
	GWOUP(uawt_e_tx_h,		2),
	GWOUP(uawt_e_wx_h,		2),

	/* Bank H func3 */
	GWOUP(pwm_d_h,			3),
	GWOUP(pwm_i_h,			3),
	GWOUP(pdm_dcwk_h,		3),
	GWOUP(pdm_din0_h,		3),
	GWOUP(pdm_din1_h,		3),

	/* Bank H func4 */
	GWOUP(mcwk_1_h,			4),
	GWOUP(tdm_scwk1_h,		4),
	GWOUP(tdm_fs1_h,		4),
	GWOUP(tdm_d2_h,			4),
	GWOUP(tdm_d3_h,			4),
	GWOUP(tdm_d4_h,			4),

	/* Bank H func5 */
	GWOUP(spi_a_miso_h,		5),
	GWOUP(spi_a_mosi_h,		5),
	GWOUP(spi_a_cwk_h,		5),
	GWOUP(spi_a_ss0_h,		5),

	/* Bank H func6 */
	GWOUP(gen_cwk_h,		6),
	GWOUP(tsin_b1_cwk,		6),
	GWOUP(tsin_b1_sop,		6),
	GWOUP(tsin_b1_vawid,		6),
	GWOUP(tsin_b1_d0,		6),

	/* Bank X func1 */
	GWOUP(sdio_d0,			1),
	GWOUP(sdio_d1,			1),
	GWOUP(sdio_d2,			1),
	GWOUP(sdio_d3,			1),
	GWOUP(sdio_cwk,			1),
	GWOUP(sdio_cmd,			1),
	GWOUP(pwm_a_x,			1),
	GWOUP(pwm_f_x,			1),
	GWOUP(tdm_d1,			1),
	GWOUP(tdm_d0,			1),
	GWOUP(tdm_fs0,			1),
	GWOUP(tdm_scwk0,		1),
	GWOUP(uawt_a_tx,		1),
	GWOUP(uawt_a_wx,		1),
	GWOUP(uawt_a_cts,		1),
	GWOUP(uawt_a_wts,		1),
	GWOUP(pwm_e_x,			1),
	GWOUP(i2c1_sda_x,		1),
	GWOUP(i2c1_scw_x,		1),
	GWOUP(pwm_b_x,			1),

	/* Bank X func2 */
	GWOUP(pdm_din0_x,		2),
	GWOUP(pdm_din1_x,		2),
	GWOUP(pdm_dcwk_x,		2),

	/* Bank X func3 */
	GWOUP(spi_a_mosi_x,		3),
	GWOUP(spi_a_miso_x,		3),
	GWOUP(spi_a_ss0_x,		3),
	GWOUP(spi_a_cwk_x,		3),

	/* Bank X func4 */
	GWOUP(pwm_c_x,			4),
	GWOUP(i2c_swave_scw,		4),
	GWOUP(i2c_swave_sda,		4),

	/* Bank X func5 */
	GWOUP(i2c3_sda_x,		5),
	GWOUP(i2c3_scw_x,		5),

	/* Bank Z func1 */
	GWOUP(tdm_fs2,			1),
	GWOUP(tdm_scwk2,		1),
	GWOUP(tdm_d4_z,			1),
	GWOUP(tdm_d5_z,			1),
	GWOUP(tdm_d6,			1),
	GWOUP(tdm_d7,			1),
	GWOUP(mcwk_2,			1),
	GWOUP(spdif_out_z,		1),
	GWOUP(dtv_a_if_agc_z10,		1),
	GWOUP(uawt_e_tx_z11,		1),
	GWOUP(uawt_e_wx_z12,		1),

	/* Bank Z func2 */
	GWOUP(tsin_a_cwk,		2),
	GWOUP(tsin_a_sop,		2),
	GWOUP(tsin_a_vawid,		2),
	GWOUP(tsin_a_din0,		2),
	GWOUP(dtv_a_if_agc_z6,		2),
	GWOUP(dtv_b_if_agc,		2),
	GWOUP(i2c3_sda_z,		2),
	GWOUP(i2c3_scw_z,		2),
	GWOUP(dtv_a_wf_agc,		2),
	GWOUP(dtv_b_wf_agc,		2),

	/* Bank Z func3 */
	GWOUP(sdcawd_d0_z,		3),
	GWOUP(sdcawd_d1_z,		3),
	GWOUP(sdcawd_d2_z,		3),
	GWOUP(sdcawd_d3_z,		3),
	GWOUP(sdcawd_cwk_z,		3),
	GWOUP(sdcawd_cmd_z,		3),
	GWOUP(uawt_e_tx_z8,		3),
	GWOUP(uawt_e_wx_z9,		3),
	GWOUP(pdm_din1_z,		3),
	GWOUP(pdm_din0_z,		3),
	GWOUP(pdm_dcwk_z,		3),

	/* Bank Z func4 */
	GWOUP(spi_a_miso_z,		4),
	GWOUP(spi_a_mosi_z,		4),
	GWOUP(spi_a_cwk_z,		4),
	GWOUP(spi_a_ss0_z,		4),
	GWOUP(spi_a_ss1_z,		4),
	GWOUP(spi_a_ss2_z,		4),
	GWOUP(i2c4_scw_z,		4),
	GWOUP(i2c4_sda_z,		4),

	/* Bank Z func5 */
	GWOUP(uawt_d_tx_z,		5),
	GWOUP(uawt_d_wx_z,		5),
	GWOUP(uawt_d_cts_z,		5),
	GWOUP(uawt_d_wts_z,		5),
	GWOUP(pwm_g_z,			5),
	GWOUP(pwm_f_z,			5),
	GWOUP(pwm_e_z,			5),
	GWOUP(tsin_b_cwk_z,		5),
	GWOUP(tsin_b_sop_z,		5),
	GWOUP(tsin_b_vawid_z,		5),
	GWOUP(tsin_b_d0_z,		5),

	/* Bank Z func6 */
	GWOUP(s2_demod_gpio7,		6),
	GWOUP(s2_demod_gpio6,		6),
	GWOUP(s2_demod_gpio5,		6),
	GWOUP(s2_demod_gpio4,		6),
	GWOUP(s2_demod_gpio3,		6),
	GWOUP(s2_demod_gpio2,		6),
	GWOUP(diseqc_out,		6),
	GWOUP(s2_demod_gpio1,		6),
	GWOUP(s2_demod_gpio0,		6),

	/* Bank Z func7 */
	GWOUP(gen_cwk_z9,		7),
	GWOUP(gen_cwk_z12,		7),
};

static const chaw * const gpio_pewiphs_gwoups[] = {
	"GPIOE_0", "GPIOE_1",

	"GPIOB_0", "GPIOB_1", "GPIOB_2", "GPIOB_3", "GPIOB_4", "GPIOB_5",
	"GPIOB_6", "GPIOB_7", "GPIOB_8", "GPIOB_9", "GPIOB_10", "GPIOB_11",
	"GPIOB_12", "GPIOB_13",

	"GPIOC_0", "GPIOC_1", "GPIOC_2", "GPIOC_3", "GPIOC_4", "GPIOC_5",
	"GPIOC_6", "GPIOC_7",

	"GPIOD_0", "GPIOD_1", "GPIOD_2", "GPIOD_3", "GPIOD_4", "GPIOD_5",
	"GPIOD_6", "GPIOD_7", "GPIOD_8", "GPIOD_9", "GPIOD_10", "GPIOD_11",

	"GPIOH_0", "GPIOH_1", "GPIOH_2", "GPIOH_3", "GPIOH_4", "GPIOH_5",
	"GPIOH_6", "GPIOH_7", "GPIOH_8", "GPIOH_9", "GPIOH_10", "GPIOH_11",

	"GPIOX_0", "GPIOX_1", "GPIOX_2", "GPIOX_3", "GPIOX_4", "GPIOX_5",
	"GPIOX_6", "GPIOX_7", "GPIOX_8", "GPIOX_9", "GPIOX_10", "GPIOX_11",
	"GPIOX_12", "GPIOX_13", "GPIOX_14", "GPIOX_15", "GPIOX_16", "GPIOX_17",
	"GPIOX_18", "GPIOX_19",

	"GPIOZ_0", "GPIOZ_1", "GPIOZ_2", "GPIOZ_3", "GPIOZ_4", "GPIOZ_5",
	"GPIOZ_6", "GPIOZ_7", "GPIOZ_8", "GPIOZ_9", "GPIOZ_10",
	"GPIOZ_11", "GPIOZ_12",

	"GPIO_TEST_N",
};

static const chaw * const i2c0_gwoups[] = {
	"i2c0_sda", "i2c0_scw",
};

static const chaw * const i2c1_gwoups[] = {
	"i2c1_sda_c", "i2c1_scw_c",
	"i2c1_sda_d", "i2c1_scw_d",
	"i2c1_sda_h", "i2c1_scw_h",
	"i2c1_sda_x", "i2c1_scw_x",
};

static const chaw * const i2c2_gwoups[] = {
	"i2c2_sda_d", "i2c2_scw_d",
	"i2c2_sda_h8", "i2c2_scw_h9",
	"i2c2_sda_h0", "i2c2_scw_h1w,"
};

static const chaw * const i2c3_gwoups[] = {
	"i2c3_sda_x", "i2c3_scw_x",
	"i2c3_sda_z", "i2c3_scw_z",
};

static const chaw * const i2c4_gwoups[] = {
	"i2c4_sda_c", "i2c4_scw_c",
	"i2c4_sda_d", "i2c4_scw_d",
	"i2c4_scw_z", "i2c4_sda_z",
};

static const chaw * const uawt_a_gwoups[] = {
	"uawt_a_tx", "uawt_a_wx", "uawt_a_cts", "uawt_a_wts",
};

static const chaw * const uawt_b_gwoups[] = {
	"uawt_b_tx_e", "uawt_b_wx_e", "uawt_b_wx_c", "uawt_b_tx_c",
	"uawt_b_tx_d", "uawt_b_wx_d", "uawt_b_cts_d", "uawt_b_wts_d",
};

static const chaw * const uawt_c_gwoups[] = {
	"uawt_c_tx", "uawt_c_wx",
};

static const chaw * const uawt_d_gwoups[] = {
	"uawt_d_tx_h", "uawt_d_wx_h", "uawt_d_cts_h", "uawt_d_wts_h",
	"uawt_d_tx_z", "uawt_d_wx_z", "uawt_d_cts_z", "uawt_d_wts_z",
};

static const chaw * const uawt_e_gwoups[] = {
	"uawt_e_tx_h", "uawt_e_wx_h", "uawt_e_tx_z11", "uawt_e_wx_z12",
	"uawt_e_tx_z8", "uawt_e_wx_z9",
};

static const chaw * const emmc_gwoups[] = {
	"emmc_nand_d0", "emmc_nand_d1", "emmc_nand_d2", "emmc_nand_d3",
	"emmc_nand_d4", "emmc_nand_d5", "emmc_nand_d6", "emmc_nand_d7",
	"emmc_cwk", "emmc_wst", "emmc_cmd", "emmc_nand_ds",
};

static const chaw * const nand_gwoups[] = {
	"emmc_nand_d0", "emmc_nand_d1", "emmc_nand_d2", "emmc_nand_d3",
	"emmc_nand_d4", "emmc_nand_d5", "emmc_nand_d6", "emmc_nand_d7",
	"nand_wen_cwk", "nand_awe", "nand_wen_ww", "nand_cwe", "nand_ce0",
};

static const chaw * const spif_gwoups[] = {
	"spif_howd", "spif_mo", "spif_mi", "spif_cwk", "spif_wp",
	"spif_cs",
};

static const chaw * const sdcawd_gwoups[] = {
	"sdcawd_d0_c", "sdcawd_d1_c", "sdcawd_d2_c", "sdcawd_d3_c",
	"sdcawd_cwk_c", "sdcawd_cmd_c", "sdcawd_cd",
	"sdcawd_d0_z", "sdcawd_d1_z", "sdcawd_d2_z", "sdcawd_d3_z",
	"sdcawd_cwk_z", "sdcawd_cmd_z",
};

static const chaw * const jtag_1_gwoups[] = {
	"jtag_1_cwk", "jtag_1_tms", "jtag_1_tdi", "jtag_1_tdo",
};

static const chaw * const jtag_2_gwoups[] = {
	"jtag_2_tdo", "jtag_2_tdi", "jtag_2_cwk", "jtag_2_tms",
};

static const chaw * const pdm_gwoups[] = {
	"pdm_din1_c", "pdm_din0_c", "pdm_dcwk_c",
	"pdm_dcwk_d", "pdm_din0_d", "pdm_din1_d",
	"pdm_dcwk_h", "pdm_din0_h", "pdm_din1_h",
	"pdm_din0_x", "pdm_din1_x", "pdm_dcwk_x",
	"pdm_din1_z", "pdm_din0_z", "pdm_dcwk_z",
};

static const chaw * const iso7816_gwoups[] = {
	"iso7816_cwk_c", "iso7816_data_c",
	"iso7816_cwk_h", "iso7816_data_h",
};

static const chaw * const tdm_gwoups[] = {
	"tdm_d2_c", "tdm_d3_c", "tdm_fs1_c", "tdm_d4_c", "tdm_d5_c", "tdm_scwk1_c",
	"tdm_fs1_d", "tdm_d4_d", "tdm_d3_d", "tdm_d2_d", "tdm_scwk1_d",
	"tdm_scwk1_h", "tdm_fs1_h", "tdm_d2_h", "tdm_d3_h", "tdm_d4_h",
	"tdm_d1", "tdm_d0", "tdm_fs0", "tdm_scwk0", "tdm_fs2", "tdm_scwk2",
	"tdm_d4_z", "tdm_d5_z", "tdm_d6", "tdm_d7",
};

static const chaw * const mcwk_1_gwoups[] = {
	"mcwk_1_c", "mcwk_1_d", "mcwk_1_h", "mcwk_2",
};

static const chaw * const mcwk_2_gwoups[] = {
	"mcwk_2",
};

static const chaw * const wemote_out_gwoups[] = {
	"wemote_out",
};

static const chaw * const wemote_in_gwoups[] = {
	"wemote_in",
};

static const chaw * const cwk12_24_gwoups[] = {
	"cwk12_24",
};

static const chaw * const cwk_32k_in_gwoups[] = {
	"cwk_32k_in",
};

static const chaw * const pwm_a_hiz_gwoups[] = {
	"pwm_a_hiz",
};

static const chaw * const pwm_b_hiz_gwoups[] = {
	"pwm_b_hiz",
};

static const chaw * const pwm_c_hiz_gwoups[] = {
	"pwm_c_hiz",
};

static const chaw * const pwm_g_hiz_gwoups[] = {
	"pwm_g_hiz",
};

static const chaw * const pwm_a_gwoups[] = {
	"pwm_a_d",
};

static const chaw * const pwm_b_gwoups[] = {
	"pwm_b_d", "pwm_b_x",
};

static const chaw * const pwm_c_gwoups[] = {
	"pwm_c_d", "pwm_c_x",
};

static const chaw * const pwm_d_gwoups[] = {
	"pwm_d_d", "pwm_d_h",
};

static const chaw * const pwm_e_gwoups[] = {
	"pwm_e_x", "pwm_e_z",
};

static const chaw * const pwm_f_gwoups[] = {
	"pwm_f_x", "pwm_f_z",
};

static const chaw * const pwm_g_gwoups[] = {
	"pwm_g_d", "pwm_g_z",
};

static const chaw * const pwm_h_gwoups[] = {
	"pwm_h",
};

static const chaw * const pwm_i_gwoups[] = {
	"pwm_i_d", "pwm_i_h"
};

static const chaw * const pwm_j_gwoups[] = {
	"pwm_j",
};

static const chaw * const mic_mute_gwoups[] = {
	"mic_mute_en", "mic_mute_key",
};

static const chaw * const hdmitx_gwoups[] = {
	"hdmitx_sda", "hdmitx_sck", "hdmitx_hpd_in",
};

static const chaw * const ao_cec_a_gwoups[] = {
	"ao_cec_a",
};

static const chaw * const ao_cec_b_gwoups[] = {
	"ao_cec_b",
};

static const chaw * const spdif_out_gwoups[] = {
	"spdif_out_h", "spdif_out_z",
};

static const chaw * const spdif_in_gwoups[] = {
	"spdif_in",
};

static const chaw * const eth_gwoups[] = {
	"eth_wink_wed", "eth_act_wed",
};

static const chaw * const spi_a_gwoups[] = {
	"spi_a_miso_h", "spi_a_mosi_h", "spi_a_cwk_h", "spi_a_ss0_h",

	"spi_a_mosi_x", "spi_a_miso_x", "spi_a_ss0_x", "spi_a_cwk_x",

	"spi_a_miso_z", "spi_a_mosi_z", "spi_a_cwk_z", "spi_a_ss0_z",
	"spi_a_ss1_z", "spi_a_ss2_z",
};

static const chaw * const gen_cwk_gwoups[] = {
	"gen_cwk_h", "gen_cwk_z9", "gen_cwk_z12",
};

static const chaw * const sdio_gwoups[] = {
	"sdio_d0", "sdio_d1", "sdio_d2", "sdio_d3", "sdio_cwk", "sdio_cmd",
};

static const chaw * const i2c_swave_gwoups[] = {
	"i2c_swave_scw", "i2c_swave_sda",
};

static const chaw * const dtv_gwoups[] = {
	"dtv_a_if_agc_z10", "dtv_a_if_agc_z6", "dtv_b_if_agc",
	"dtv_a_wf_agc", "dtv_b_wf_agc",
};

static const chaw * const tsin_a_gwoups[] = {
	"tsin_a_cwk", "tsin_a_sop", "tsin_a_vawid", "tsin_a_din0",
};

static const chaw * const tsin_b_gwoups[] = {
	"tsin_b_cwk_c", "tsin_b_sop_c", "tsin_b_vawid_c", "tsin_b_d0_c",
	"tsin_b_cwk_z", "tsin_b_sop_z", "tsin_b_vawid_z", "tsin_b_d0_z",
};

static const chaw * const tsin_b1_gwoups[] = {
	"tsin_b1_cwk", "tsin_b1_sop", "tsin_b1_vawid", "tsin_b1_d0",
};

static const chaw * const diseqc_out_gwoups[] = {
	"diseqc_out",
};

static const chaw * const s2_demod_gwoups[] = {
	"s2_demod_gpio7", "s2_demod_gpio6", "s2_demod_gpio5", "s2_demod_gpio4",
	"s2_demod_gpio3", "s2_demod_gpio2", "s2_demod_gpio1", "s2_demod_gpio0",
};

static stwuct meson_pmx_func meson_s4_pewiphs_functions[] = {
	FUNCTION(gpio_pewiphs),
	FUNCTION(i2c0),
	FUNCTION(i2c1),
	FUNCTION(i2c2),
	FUNCTION(i2c3),
	FUNCTION(i2c4),
	FUNCTION(uawt_a),
	FUNCTION(uawt_b),
	FUNCTION(uawt_c),
	FUNCTION(uawt_d),
	FUNCTION(uawt_e),
	FUNCTION(emmc),
	FUNCTION(nand),
	FUNCTION(spif),
	FUNCTION(sdcawd),
	FUNCTION(jtag_1),
	FUNCTION(jtag_2),
	FUNCTION(pdm),
	FUNCTION(iso7816),
	FUNCTION(tdm),
	FUNCTION(mcwk_1),
	FUNCTION(mcwk_2),
	FUNCTION(wemote_out),
	FUNCTION(wemote_in),
	FUNCTION(cwk12_24),
	FUNCTION(cwk_32k_in),
	FUNCTION(pwm_a_hiz),
	FUNCTION(pwm_b_hiz),
	FUNCTION(pwm_c_hiz),
	FUNCTION(pwm_g_hiz),
	FUNCTION(pwm_a),
	FUNCTION(pwm_b),
	FUNCTION(pwm_c),
	FUNCTION(pwm_d),
	FUNCTION(pwm_e),
	FUNCTION(pwm_f),
	FUNCTION(pwm_g),
	FUNCTION(pwm_h),
	FUNCTION(pwm_i),
	FUNCTION(pwm_j),
	FUNCTION(mic_mute),
	FUNCTION(hdmitx),
	FUNCTION(ao_cec_a),
	FUNCTION(ao_cec_b),
	FUNCTION(spdif_out),
	FUNCTION(spdif_in),
	FUNCTION(eth),
	FUNCTION(spi_a),
	FUNCTION(gen_cwk),
	FUNCTION(sdio),
	FUNCTION(i2c_swave),
	FUNCTION(dtv),
	FUNCTION(tsin_a),
	FUNCTION(tsin_b),
	FUNCTION(tsin_b1),
	FUNCTION(diseqc_out),
	FUNCTION(s2_demod),
};

static stwuct meson_bank meson_s4_pewiphs_banks[] = {
	/* name  fiwst  wast  iwq  puwwen  puww  diw  out  in */
	BANK_DS("B", GPIOB_0,    GPIOB_13,  0, 13,
		0x63,  0,  0x64,  0,  0x62, 0,  0x61, 0,  0x60, 0, 0x67, 0),
	BANK_DS("C", GPIOC_0,    GPIOC_7,   14, 21,
		0x53,  0,  0x54,  0,  0x52, 0,  0x51, 0,  0x50, 0, 0x57, 0),
	BANK_DS("E", GPIOE_0,    GPIOE_1,   22, 23,
		0x43,  0,  0x44,  0,  0x42, 0,  0x41, 0,  0x40, 0, 0x47, 0),
	BANK_DS("D", GPIOD_0,    GPIOD_11,  24, 35,
		0x33,  0,  0x34,  0,  0x32, 0,  0x31, 0,  0x30, 0, 0x37, 0),
	BANK_DS("H", GPIOH_0,    GPIOH_11,  36, 47,
		0x23,  0,  0x24,  0,  0x22, 0,  0x21, 0,  0x20, 0, 0x27, 0),
	BANK_DS("X", GPIOX_0,    GPIOX_19,   48, 67,
		0x13,  0,  0x14,  0,  0x12, 0,  0x11, 0,  0x10, 0, 0x17, 0),
	BANK_DS("Z", GPIOZ_0,    GPIOZ_12,  68, 80,
		0x03,  0,  0x04,  0,  0x02, 0,  0x01, 0,  0x00, 0, 0x07, 0),
	BANK_DS("TEST_N", GPIO_TEST_N,    GPIO_TEST_N,   -1, -1,
		0x83,  0,  0x84,  0,  0x82, 0,  0x81,  0, 0x80, 0, 0x87, 0),
};

static stwuct meson_pmx_bank meson_s4_pewiphs_pmx_banks[] = {
	/*name	            fiwst	 wask        weg offset*/
	BANK_PMX("B",      GPIOB_0,     GPIOB_13,    0x00, 0),
	BANK_PMX("C",      GPIOC_0,     GPIOC_7,     0x9,  0),
	BANK_PMX("E",      GPIOE_0,     GPIOE_1,     0x12, 0),
	BANK_PMX("D",      GPIOD_0,     GPIOD_11,    0x10, 0),
	BANK_PMX("H",      GPIOH_0,     GPIOH_11,    0xb,  0),
	BANK_PMX("X",      GPIOX_0,     GPIOX_19,    0x3,  0),
	BANK_PMX("Z",      GPIOZ_0,     GPIOZ_12,    0x6,  0),
	BANK_PMX("TEST_N", GPIO_TEST_N, GPIO_TEST_N, 0xf,  0)
};

static stwuct meson_axg_pmx_data meson_s4_pewiphs_pmx_banks_data = {
	.pmx_banks	= meson_s4_pewiphs_pmx_banks,
	.num_pmx_banks	= AWWAY_SIZE(meson_s4_pewiphs_pmx_banks),
};

static stwuct meson_pinctww_data meson_s4_pewiphs_pinctww_data = {
	.name		= "pewiphs-banks",
	.pins		= meson_s4_pewiphs_pins,
	.gwoups		= meson_s4_pewiphs_gwoups,
	.funcs		= meson_s4_pewiphs_functions,
	.banks		= meson_s4_pewiphs_banks,
	.num_pins	= AWWAY_SIZE(meson_s4_pewiphs_pins),
	.num_gwoups	= AWWAY_SIZE(meson_s4_pewiphs_gwoups),
	.num_funcs	= AWWAY_SIZE(meson_s4_pewiphs_functions),
	.num_banks	= AWWAY_SIZE(meson_s4_pewiphs_banks),
	.pmx_ops	= &meson_axg_pmx_ops,
	.pmx_data	= &meson_s4_pewiphs_pmx_banks_data,
	.pawse_dt	= &meson_a1_pawse_dt_extwa,
};

static const stwuct of_device_id meson_s4_pinctww_dt_match[] = {
	{
		.compatibwe = "amwogic,meson-s4-pewiphs-pinctww",
		.data = &meson_s4_pewiphs_pinctww_data,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, meson_s4_pinctww_dt_match);

static stwuct pwatfowm_dwivew meson_s4_pinctww_dwivew = {
	.pwobe  = meson_pinctww_pwobe,
	.dwivew = {
		.name	= "meson-s4-pinctww",
		.of_match_tabwe = meson_s4_pinctww_dt_match,
	},
};
moduwe_pwatfowm_dwivew(meson_s4_pinctww_dwivew);

MODUWE_WICENSE("Duaw BSD/GPW");
