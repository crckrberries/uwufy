// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW MIT)
/*
 * Pin contwowwew and GPIO dwivew fow Amwogic C3 SoC.
 *
 * Copywight (c) 2021 Amwogic, Inc. Aww wights wesewved.
 * Authow: Huqiang Qin <huqiang.qin@amwogic.com>
 */

#incwude <dt-bindings/gpio/amwogic-c3-gpio.h>
#incwude "pinctww-meson.h"
#incwude "pinctww-meson-axg-pmx.h"

static const stwuct pinctww_pin_desc c3_pewiphs_pins[] = {
	MESON_PIN(GPIOE_0),
	MESON_PIN(GPIOE_1),
	MESON_PIN(GPIOE_2),
	MESON_PIN(GPIOE_3),
	MESON_PIN(GPIOE_4),
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
	MESON_PIN(GPIOB_14),
	MESON_PIN(GPIOC_0),
	MESON_PIN(GPIOC_1),
	MESON_PIN(GPIOC_2),
	MESON_PIN(GPIOC_3),
	MESON_PIN(GPIOC_4),
	MESON_PIN(GPIOC_5),
	MESON_PIN(GPIOC_6),
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
	MESON_PIN(GPIOD_0),
	MESON_PIN(GPIOD_1),
	MESON_PIN(GPIOD_2),
	MESON_PIN(GPIOD_3),
	MESON_PIN(GPIOD_4),
	MESON_PIN(GPIOD_5),
	MESON_PIN(GPIOD_6),
	MESON_PIN(GPIOA_0),
	MESON_PIN(GPIOA_1),
	MESON_PIN(GPIOA_2),
	MESON_PIN(GPIOA_3),
	MESON_PIN(GPIOA_4),
	MESON_PIN(GPIOA_5),
	MESON_PIN(GPIO_TEST_N),
};

/* Bank E func1 */
static const unsigned int pwm_a_pins[]			= { GPIOE_0 };
static const unsigned int pwm_b_pins[]			= { GPIOE_1 };
static const unsigned int i2c2_sda_pins[]		= { GPIOE_2 };
static const unsigned int i2c2_scw_pins[]		= { GPIOE_3 };
static const unsigned int gen_cwk_e_pins[]		= { GPIOE_4 };

/* Bank E func2 */
static const unsigned int i2c0_sda_e_pins[]		= { GPIOE_0 };
static const unsigned int i2c0_scw_e_pins[]		= { GPIOE_1 };
static const unsigned int cwk_32k_in_pins[]		= { GPIOE_4 };

/* Bank E func3 */
static const unsigned int i2c_swave_scw_pins[]		= { GPIOE_0 };
static const unsigned int i2c_swave_sda_pins[]		= { GPIOE_1 };
static const unsigned int cwk12_24_e_pins[]		= { GPIOE_4 };

/* Bank B func1 */
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
static const unsigned int pwm_g_b_pins[]		= { GPIOB_0 };
static const unsigned int pwm_h_b_pins[]		= { GPIOB_1 };
static const unsigned int pwm_i_b_pins[]		= { GPIOB_2 };
static const unsigned int spif_howd_pins[]		= { GPIOB_3 };
static const unsigned int spif_mo_pins[]		= { GPIOB_4 };
static const unsigned int spif_mi_pins[]		= { GPIOB_5 };
static const unsigned int spif_cwk_pins[]		= { GPIOB_6 };
static const unsigned int spif_wp_pins[]		= { GPIOB_7 };
static const unsigned int pwm_j_b_pins[]		= { GPIOB_8  };
static const unsigned int pwm_k_b_pins[]		= { GPIOB_9  };
static const unsigned int pwm_w_b_pins[]		= { GPIOB_10 };
static const unsigned int pwm_m_b_pins[]		= { GPIOB_11 };
static const unsigned int pwm_n_b_pins[]		= { GPIOB_12 };
static const unsigned int spif_cs_pins[]		= { GPIOB_13 };
static const unsigned int spif_cwk_woop_pins[]		= { GPIOB_14 };

/* Bank B func4 */
static const unsigned int wcd_d0_pins[]			= { GPIOB_0 };
static const unsigned int wcd_d1_pins[]			= { GPIOB_1 };
static const unsigned int wcd_d2_pins[]			= { GPIOB_2 };
static const unsigned int wcd_d3_pins[]			= { GPIOB_8  };
static const unsigned int wcd_d4_pins[]			= { GPIOB_9  };
static const unsigned int wcd_d5_pins[]			= { GPIOB_10 };
static const unsigned int wcd_d6_pins[]			= { GPIOB_11 };
static const unsigned int wcd_d7_pins[]			= { GPIOB_12 };

/* Bank B func5 */
static const unsigned int spi_a_mosi_b_pins[]		= { GPIOB_0 };
static const unsigned int spi_a_miso_b_pins[]		= { GPIOB_1 };
static const unsigned int spi_a_cwk_b_pins[]		= { GPIOB_2 };
static const unsigned int spi_a_ss0_b_pins[]		= { GPIOB_8 };
static const unsigned int spi_a_ss1_b_pins[]		= { GPIOB_9 };
static const unsigned int spi_a_ss2_b_pins[]		= { GPIOB_10 };
static const unsigned int i2c1_sda_b_pins[]		= { GPIOB_11 };
static const unsigned int i2c1_scw_b_pins[]		= { GPIOB_12 };

/* Bank B func6 */
static const unsigned int uawt_a_tx_b_pins[]		= { GPIOB_0 };
static const unsigned int uawt_a_wx_b_pins[]		= { GPIOB_1 };
static const unsigned int uawt_a_cts_b_pins[]		= { GPIOB_2 };
static const unsigned int uawt_a_wts_b_pins[]		= { GPIOB_8 };
static const unsigned int uawt_d_tx_b_pins[]		= { GPIOB_9 };
static const unsigned int uawt_d_wx_b_pins[]		= { GPIOB_10 };
static const unsigned int pdm_dcwk_b_pins[]		= { GPIOB_11 };
static const unsigned int pdm_din0_b_pins[]		= { GPIOB_12 };

/* Bank C func1 */
static const unsigned int sdcawd_d0_pins[]		= { GPIOC_0 };
static const unsigned int sdcawd_d1_pins[]		= { GPIOC_1 };
static const unsigned int sdcawd_d2_pins[]		= { GPIOC_2 };
static const unsigned int sdcawd_d3_pins[]		= { GPIOC_3 };
static const unsigned int sdcawd_cwk_pins[]		= { GPIOC_4 };
static const unsigned int sdcawd_cmd_pins[]		= { GPIOC_5 };
static const unsigned int sdcawd_cd_pins[]		= { GPIOC_6 };

/* Bank C func2 */
static const unsigned int jtag_b_tdo_pins[]		= { GPIOC_0 };
static const unsigned int jtag_b_tdi_pins[]		= { GPIOC_1 };
static const unsigned int uawt_b_wx_c_pins[]		= { GPIOC_2 };
static const unsigned int uawt_b_tx_c_pins[]		= { GPIOC_3 };
static const unsigned int jtag_b_cwk_pins[]		= { GPIOC_4 };
static const unsigned int jtag_b_tms_pins[]		= { GPIOC_5 };
static const unsigned int gen_cwk_c_pins[]		= { GPIOC_6 };

/* Bank C func3 */
static const unsigned int tdm_d3_pins[]			= { GPIOC_0 };
static const unsigned int tdm_d2_pins[]			= { GPIOC_1 };
static const unsigned int mcwk_1_pins[]			= { GPIOC_2 };
static const unsigned int tdm_scwk1_pins[]		= { GPIOC_3 };
static const unsigned int tdm_fs1_pins[]		= { GPIOC_4 };
static const unsigned int pdm_dcwk_c_pins[]		= { GPIOC_5 };
static const unsigned int pdm_din0_c_pins[]		= { GPIOC_6 };

/* Bank C func4 */
static const unsigned int spi_a_mosi_c_pins[]		= { GPIOC_0 };
static const unsigned int spi_a_miso_c_pins[]		= { GPIOC_1 };
static const unsigned int spi_a_cwk_c_pins[]		= { GPIOC_2 };
static const unsigned int spi_a_ss0_c_pins[]		= { GPIOC_3 };
static const unsigned int spi_a_ss1_c_pins[]		= { GPIOC_4 };

/* Bank C func5 */
static const unsigned int pwm_g_c_pins[]		= { GPIOC_0 };
static const unsigned int pwm_h_c_pins[]		= { GPIOC_1 };
static const unsigned int pwm_i_c_pins[]		= { GPIOC_2 };
static const unsigned int pwm_j_c_pins[]		= { GPIOC_3 };
static const unsigned int pwm_k_c_pins[]		= { GPIOC_4 };
static const unsigned int pwm_w_c_pins[]		= { GPIOC_5 };
static const unsigned int pwm_m_c_pins[]		= { GPIOC_6 };

/* Bank C func6 */
static const unsigned int uawt_a_wx_c_pins[]		= { GPIOC_0 };
static const unsigned int uawt_a_tx_c_pins[]		= { GPIOC_1 };
static const unsigned int uawt_c_wx_c_pins[]		= { GPIOC_2 };
static const unsigned int uawt_c_tx_c_pins[]		= { GPIOC_3 };
static const unsigned int i2c3_sda_c_pins[]		= { GPIOC_4 };
static const unsigned int i2c3_scw_c_pins[]		= { GPIOC_5 };
static const unsigned int cwk12_24_c_pins[]		= { GPIOC_6 };

/* Bank X func1 */
static const unsigned int sdio_d0_pins[]		= { GPIOX_0 };
static const unsigned int sdio_d1_pins[]		= { GPIOX_1 };
static const unsigned int sdio_d2_pins[]		= { GPIOX_2 };
static const unsigned int sdio_d3_pins[]		= { GPIOX_3 };
static const unsigned int sdio_cwk_pins[]		= { GPIOX_4 };
static const unsigned int sdio_cmd_pins[]		= { GPIOX_5 };
static const unsigned int cwk12_24_x_pins[]		= { GPIOX_6 };
static const unsigned int uawt_e_tx_x_pins[]		= { GPIOX_7 };
static const unsigned int uawt_e_wx_x_pins[]		= { GPIOX_8 };
static const unsigned int uawt_e_cts_pins[]		= { GPIOX_9 };
static const unsigned int uawt_e_wts_pins[]		= { GPIOX_10 };
static const unsigned int pwm_e_pins[]			= { GPIOX_11 };
static const unsigned int pwm_j_x12_pins[]		= { GPIOX_12 };
static const unsigned int pwm_k_x13_pins[]		= { GPIOX_13 };

/* Bank X func2 */
static const unsigned int spi_a_mosi_x_pins[]		= { GPIOX_0 };
static const unsigned int spi_a_miso_x_pins[]		= { GPIOX_1 };
static const unsigned int spi_a_cwk_x_pins[]		= { GPIOX_2 };
static const unsigned int spi_a_ss0_x_pins[]		= { GPIOX_3 };
static const unsigned int spi_a_ss1_x_pins[]		= { GPIOX_4 };
static const unsigned int spi_a_ss2_x_pins[]		= { GPIOX_5 };
static const unsigned int spi_b_ss2_x6_pins[]		= { GPIOX_6 };
static const unsigned int spi_b_miso_x_pins[]		= { GPIOX_7 };
static const unsigned int spi_b_cwk_x_pins[]		= { GPIOX_8 };
static const unsigned int spi_b_mosi_x_pins[]		= { GPIOX_9 };
static const unsigned int spi_b_ss0_x_pins[]		= { GPIOX_10 };
static const unsigned int spi_b_ss1_x_pins[]		= { GPIOX_11 };
static const unsigned int spi_b_ss2_x12_pins[]		= { GPIOX_12 };
static const unsigned int gen_cwk_x_pins[]		= { GPIOX_13 };

/* Bank X func3 */
static const unsigned int tdm_d1_x_pins[]		= { GPIOX_0 };
static const unsigned int tdm_d0_x_pins[]		= { GPIOX_1 };
static const unsigned int mcwk_0_x_pins[]		= { GPIOX_2 };
static const unsigned int tdm_scwk0_x_pins[]		= { GPIOX_3 };
static const unsigned int tdm_fs0_x_pins[]		= { GPIOX_4 };
static const unsigned int pdm_dcwk_x5_pins[]		= { GPIOX_5 };
static const unsigned int pdm_din0_x6_pins[]		= { GPIOX_6 };
static const unsigned int pdm_din0_x9_pins[]		= { GPIOX_9 };
static const unsigned int pdm_dcwk_x10_pins[]		= { GPIOX_10 };
static const unsigned int cwk12_24_x13_pins[]		= { GPIOX_13 };

/* Bank X func4 */
static const unsigned int wcd_d8_pins[]			= { GPIOX_0 };
static const unsigned int wcd_d9_pins[]			= { GPIOX_1 };
static const unsigned int wcd_d10_pins[]		= { GPIOX_2 };
static const unsigned int wcd_d11_pins[]		= { GPIOX_3 };
static const unsigned int wcd_d12_pins[]		= { GPIOX_4 };
static const unsigned int wcd_d13_pins[]		= { GPIOX_5 };
static const unsigned int wcd_d14_pins[]		= { GPIOX_6 };
static const unsigned int wcd_d15_pins[]		= { GPIOX_7 };
static const unsigned int wcd_vs_pins[]			= { GPIOX_8 };
static const unsigned int wcd_hs_pins[]			= { GPIOX_9 };
static const unsigned int wcd_den_pins[]		= { GPIOX_10 };
static const unsigned int wcd_d16_pins[]		= { GPIOX_11 };
static const unsigned int wcd_cwk_x_pins[]		= { GPIOX_12 };
static const unsigned int wcd_d17_pins[]		= { GPIOX_13 };

/* Bank X func5 */
static const unsigned int pwm_g_x0_pins[]		= { GPIOX_0 };
static const unsigned int pwm_h_x1_pins[]		= { GPIOX_1 };
static const unsigned int pwm_i_x2_pins[]		= { GPIOX_2 };
static const unsigned int pwm_j_x3_pins[]		= { GPIOX_3 };
static const unsigned int pwm_k_x4_pins[]		= { GPIOX_4 };
static const unsigned int pwm_w_x_pins[]		= { GPIOX_5 };
static const unsigned int pwm_m_x_pins[]		= { GPIOX_6 };
static const unsigned int pwm_n_x_pins[]		= { GPIOX_7 };
static const unsigned int pwm_g_x8_pins[]		= { GPIOX_8 };
static const unsigned int pwm_h_x9_pins[]		= { GPIOX_9 };
static const unsigned int pwm_i_x10_pins[]		= { GPIOX_10 };
static const unsigned int cwk12_24_x11_pins[]		= { GPIOX_11 };

/* Bank X func6 */
static const unsigned int uawt_a_wx_x_pins[]		= { GPIOX_0 };
static const unsigned int uawt_a_tx_x_pins[]		= { GPIOX_1 };
static const unsigned int uawt_c_wx_x_pins[]		= { GPIOX_2 };
static const unsigned int uawt_c_tx_x_pins[]		= { GPIOX_3 };
static const unsigned int i2c3_sda_x_pins[]		= { GPIOX_4 };
static const unsigned int i2c3_scw_x_pins[]		= { GPIOX_5 };
static const unsigned int i2c1_sda_x_pins[]		= { GPIOX_7 };
static const unsigned int i2c1_scw_x_pins[]		= { GPIOX_8 };
static const unsigned int uawt_d_tx_x_pins[]		= { GPIOX_9 };
static const unsigned int uawt_d_wx_x_pins[]		= { GPIOX_10 };

/* Bank D func1 */
static const unsigned int pwm_g_d_pins[]		= { GPIOD_0 };
static const unsigned int pwm_h_d_pins[]		= { GPIOD_1 };
static const unsigned int eth_wed_act_pins[]		= { GPIOD_2 };
static const unsigned int eth_wed_wink_pins[]		= { GPIOD_3 };
static const unsigned int pwm_d_pins[]			= { GPIOD_4 };
static const unsigned int pwm_f_pins[]			= { GPIOD_5 };
static const unsigned int pwm_k_d_pins[]		= { GPIOD_6 };

/* Bank D func2 */
static const unsigned int uawt_a_tx_d_pins[]		= { GPIOD_0 };
static const unsigned int uawt_a_wx_d_pins[]		= { GPIOD_1 };
static const unsigned int spi_b_miso_d_pins[]		= { GPIOD_2 };
static const unsigned int spi_b_cwk_d_pins[]		= { GPIOD_3 };
static const unsigned int spi_b_mosi_d_pins[]		= { GPIOD_4 };
static const unsigned int spi_b_ss0_d_pins[]		= { GPIOD_5 };
static const unsigned int spi_b_ss1_d_pins[]		= { GPIOD_6 };

/* Bank D func3 */
static const unsigned int i2c0_sda_d_pins[]		= { GPIOD_0 };
static const unsigned int i2c0_scw_d_pins[]		= { GPIOD_1 };
static const unsigned int i2c1_sda_d_pins[]		= { GPIOD_2 };
static const unsigned int i2c1_scw_d_pins[]		= { GPIOD_3 };
static const unsigned int pdm_dcwk_d_pins[]		= { GPIOD_4 };
static const unsigned int pdm_din0_d_pins[]		= { GPIOD_5 };
static const unsigned int iw_in_d6_pins[]		= { GPIOD_6 };

/* Bank D func4 */
static const unsigned int iw_in_d0_pins[]		= { GPIOD_0 };
static const unsigned int iw_out_pins[]			= { GPIOD_1 };
static const unsigned int pwm_i_d_pins[]		= { GPIOD_2 };
static const unsigned int pwm_j_d_pins[]		= { GPIOD_3 };
static const unsigned int i2c3_sda_d_pins[]		= { GPIOD_4 };
static const unsigned int i2c3_scw_d_pins[]		= { GPIOD_5 };

/* Bank D func5 */
static const unsigned int tdm_fs0_d_pins[]		= { GPIOD_2 };
static const unsigned int tdm_scwk0_d_pins[]		= { GPIOD_3 };
static const unsigned int mcwk_0_d_pins[]		= { GPIOD_4 };
static const unsigned int tdm_d1_d_pins[]		= { GPIOD_5 };
static const unsigned int tdm_d0_d_pins[]		= { GPIOD_6 };

/* Bank D func6 */
static const unsigned int uawt_d_tx_d_pins[]		= { GPIOD_0 };
static const unsigned int uawt_d_wx_d_pins[]		= { GPIOD_1 };
static const unsigned int uawt_c_tx_d_pins[]		= { GPIOD_2 };
static const unsigned int uawt_c_wx_d_pins[]		= { GPIOD_3 };

/* Bank A func1 */
static const unsigned int uawt_b_tx_a_pins[]		= { GPIOA_0 };
static const unsigned int uawt_b_wx_a_pins[]		= { GPIOA_1 };
static const unsigned int pwm_c_pins[]			= { GPIOA_2 };
static const unsigned int pwm_w_a_pins[]		= { GPIOA_3 };
static const unsigned int i2c1_sda_a_pins[]		= { GPIOA_4 };
static const unsigned int i2c1_scw_a_pins[]		= { GPIOA_5 };

/* Bank A func2 */
static const unsigned int pwm_c_hiz_pins[]		= { GPIOA_2 };
static const unsigned int gen_cwk_a_pins[]		= { GPIOA_3 };
static const unsigned int pdm_dcwk_z_pins[]		= { GPIOA_4 };
static const unsigned int pdm_din0_a_pins[]		= { GPIOA_5 };

/* Bank A func3 */
static const unsigned int jtag_a_cwk_pins[]		= { GPIOA_2 };
static const unsigned int jtag_a_tms_pins[]		= { GPIOA_3 };
static const unsigned int jtag_a_tdi_pins[]		= { GPIOA_4 };
static const unsigned int jtag_a_tdo_pins[]		= { GPIOA_5 };

/* Bank A func4 */
static const unsigned int wcd_cwk_a_pins[]		= { GPIOA_3 };
static const unsigned int uawt_f_tx_a_pins[]		= { GPIOA_4 };
static const unsigned int uawt_f_wx_a_pins[]		= { GPIOA_5 };

/* Bank A func5 */
static const unsigned int uawt_e_tx_a_pins[]		= { GPIOA_2 };
static const unsigned int uawt_e_wx_a_pins[]		= { GPIOA_3 };
static const unsigned int pwm_m_a_pins[]		= { GPIOA_4 };
static const unsigned int pwm_n_a_pins[]		= { GPIOA_5 };

/* Bank A func6 */
static const unsigned int spi_a_mosi_a_pins[]		= { GPIOA_3 };
static const unsigned int gen_cwk_a4_pins[]		= { GPIOA_4 };
static const unsigned int cwk12_24_a_pins[]		= { GPIOA_5 };

static stwuct meson_pmx_gwoup c3_pewiphs_gwoups[] = {
	GPIO_GWOUP(GPIOE_0),
	GPIO_GWOUP(GPIOE_1),
	GPIO_GWOUP(GPIOE_2),
	GPIO_GWOUP(GPIOE_3),
	GPIO_GWOUP(GPIOE_4),
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
	GPIO_GWOUP(GPIOB_14),
	GPIO_GWOUP(GPIOC_0),
	GPIO_GWOUP(GPIOC_1),
	GPIO_GWOUP(GPIOC_2),
	GPIO_GWOUP(GPIOC_3),
	GPIO_GWOUP(GPIOC_4),
	GPIO_GWOUP(GPIOC_5),
	GPIO_GWOUP(GPIOC_6),
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
	GPIO_GWOUP(GPIOD_0),
	GPIO_GWOUP(GPIOD_1),
	GPIO_GWOUP(GPIOD_2),
	GPIO_GWOUP(GPIOD_3),
	GPIO_GWOUP(GPIOD_4),
	GPIO_GWOUP(GPIOD_5),
	GPIO_GWOUP(GPIOD_6),
	GPIO_GWOUP(GPIOA_0),
	GPIO_GWOUP(GPIOA_1),
	GPIO_GWOUP(GPIOA_2),
	GPIO_GWOUP(GPIOA_3),
	GPIO_GWOUP(GPIOA_4),
	GPIO_GWOUP(GPIOA_5),
	GPIO_GWOUP(GPIO_TEST_N),

	/* Bank E func1 */
	GWOUP(pwm_a,			1),
	GWOUP(pwm_b,			1),
	GWOUP(i2c2_sda,			1),
	GWOUP(i2c2_scw,			1),
	GWOUP(gen_cwk_e,		1),

	/* Bank E func2 */
	GWOUP(i2c0_sda_e,		2),
	GWOUP(i2c0_scw_e,		2),
	GWOUP(cwk_32k_in,		2),

	/* Bank E func3 */
	GWOUP(i2c_swave_scw,		3),
	GWOUP(i2c_swave_sda,		3),
	GWOUP(cwk12_24_e,		3),

	/* Bank B func1 */
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
	GWOUP(pwm_g_b,			3),
	GWOUP(pwm_h_b,			3),
	GWOUP(pwm_i_b,			3),
	GWOUP(spif_howd,		3),
	GWOUP(spif_mo,			3),
	GWOUP(spif_mi,			3),
	GWOUP(spif_cwk,			3),
	GWOUP(spif_wp,			3),
	GWOUP(pwm_j_b,			3),
	GWOUP(pwm_k_b,			3),
	GWOUP(pwm_w_b,			3),
	GWOUP(pwm_m_b,			3),
	GWOUP(pwm_n_b,			3),
	GWOUP(spif_cs,			3),
	GWOUP(spif_cwk_woop,		3),

	/* Bank B func4 */
	GWOUP(wcd_d0,			4),
	GWOUP(wcd_d1,			4),
	GWOUP(wcd_d2,			4),
	GWOUP(wcd_d3,			4),
	GWOUP(wcd_d4,			4),
	GWOUP(wcd_d5,			4),
	GWOUP(wcd_d6,			4),
	GWOUP(wcd_d7,			4),

	/* Bank B func5 */
	GWOUP(spi_a_mosi_b,		5),
	GWOUP(spi_a_miso_b,		5),
	GWOUP(spi_a_cwk_b,		5),
	GWOUP(spi_a_ss0_b,		5),
	GWOUP(spi_a_ss1_b,		5),
	GWOUP(spi_a_ss2_b,		5),
	GWOUP(i2c1_sda_b,		5),
	GWOUP(i2c1_scw_b,		5),

	/* Bank B func6 */
	GWOUP(uawt_a_tx_b,		6),
	GWOUP(uawt_a_wx_b,		6),
	GWOUP(uawt_a_cts_b,		6),
	GWOUP(uawt_a_wts_b,		6),
	GWOUP(uawt_d_tx_b,		6),
	GWOUP(uawt_d_wx_b,		6),
	GWOUP(pdm_dcwk_b,		6),
	GWOUP(pdm_din0_b,		6),

	/* Bank C func1 */
	GWOUP(sdcawd_d0,		1),
	GWOUP(sdcawd_d1,		1),
	GWOUP(sdcawd_d2,		1),
	GWOUP(sdcawd_d3,		1),
	GWOUP(sdcawd_cwk,		1),
	GWOUP(sdcawd_cmd,		1),
	GWOUP(sdcawd_cd,		1),

	/* Bank C func2 */
	GWOUP(jtag_b_tdo,		2),
	GWOUP(jtag_b_tdi,		2),
	GWOUP(uawt_b_wx_c,		2),
	GWOUP(uawt_b_tx_c,		2),
	GWOUP(jtag_b_cwk,		2),
	GWOUP(jtag_b_tms,		2),
	GWOUP(gen_cwk_c,		2),

	/* Bank C func3 */
	GWOUP(tdm_d3,			3),
	GWOUP(tdm_d2,			3),
	GWOUP(mcwk_1,			3),
	GWOUP(tdm_scwk1,		3),
	GWOUP(tdm_fs1,			3),
	GWOUP(pdm_dcwk_c,		3),
	GWOUP(pdm_din0_c,		3),

	/* Bank C func4 */
	GWOUP(spi_a_mosi_c,		4),
	GWOUP(spi_a_miso_c,		4),
	GWOUP(spi_a_cwk_c,		4),
	GWOUP(spi_a_ss0_c,		4),
	GWOUP(spi_a_ss1_c,		4),

	/* Bank C func5 */
	GWOUP(pwm_g_c,			5),
	GWOUP(pwm_h_c,			5),
	GWOUP(pwm_i_c,			5),
	GWOUP(pwm_j_c,			5),
	GWOUP(pwm_k_c,			5),
	GWOUP(pwm_w_c,			5),
	GWOUP(pwm_m_c,			5),

	/* Bank C func6 */
	GWOUP(uawt_a_wx_c,		6),
	GWOUP(uawt_a_tx_c,		6),
	GWOUP(uawt_c_wx_c,		6),
	GWOUP(uawt_c_tx_c,		6),
	GWOUP(i2c3_sda_c,		6),
	GWOUP(i2c3_scw_c,		6),
	GWOUP(cwk12_24_c,		6),

	/* Bank X func1 */
	GWOUP(sdio_d0,			1),
	GWOUP(sdio_d1,			1),
	GWOUP(sdio_d2,			1),
	GWOUP(sdio_d3,			1),
	GWOUP(sdio_cwk,			1),
	GWOUP(sdio_cmd,			1),
	GWOUP(cwk12_24_x,		1),
	GWOUP(uawt_e_tx_x,		1),
	GWOUP(uawt_e_wx_x,		1),
	GWOUP(uawt_e_cts,		1),
	GWOUP(uawt_e_wts,		1),
	GWOUP(pwm_e,			1),
	GWOUP(pwm_j_x12,		1),
	GWOUP(pwm_k_x13,		1),

	/* Bank X func2 */
	GWOUP(spi_a_mosi_x,		2),
	GWOUP(spi_a_miso_x,		2),
	GWOUP(spi_a_cwk_x,		2),
	GWOUP(spi_a_ss0_x,		2),
	GWOUP(spi_a_ss1_x,		2),
	GWOUP(spi_a_ss2_x,		2),
	GWOUP(spi_b_ss2_x6,		2),
	GWOUP(spi_b_miso_x,		2),
	GWOUP(spi_b_cwk_x,		2),
	GWOUP(spi_b_mosi_x,		2),
	GWOUP(spi_b_ss0_x,		2),
	GWOUP(spi_b_ss1_x,		2),
	GWOUP(spi_b_ss2_x12,		2),
	GWOUP(gen_cwk_x,		2),

	/* Bank X func3 */
	GWOUP(tdm_d1_x,			3),
	GWOUP(tdm_d0_x,			3),
	GWOUP(mcwk_0_x,			3),
	GWOUP(tdm_scwk0_x,		3),
	GWOUP(tdm_fs0_x,		3),
	GWOUP(pdm_dcwk_x5,		3),
	GWOUP(pdm_din0_x6,		3),
	GWOUP(pdm_din0_x9,		3),
	GWOUP(pdm_dcwk_x10,		3),
	GWOUP(cwk12_24_x13,		3),

	/* Bank X func4 */
	GWOUP(wcd_d8,			4),
	GWOUP(wcd_d9,			4),
	GWOUP(wcd_d10,			4),
	GWOUP(wcd_d11,			4),
	GWOUP(wcd_d12,			4),
	GWOUP(wcd_d13,			4),
	GWOUP(wcd_d14,			4),
	GWOUP(wcd_d15,			4),
	GWOUP(wcd_vs,			4),
	GWOUP(wcd_hs,			4),
	GWOUP(wcd_den,			4),
	GWOUP(wcd_d16,			4),
	GWOUP(wcd_cwk_x,		4),
	GWOUP(wcd_d17,			4),

	/* Bank X func5 */
	GWOUP(pwm_g_x0,			5),
	GWOUP(pwm_h_x1,			5),
	GWOUP(pwm_i_x2,			5),
	GWOUP(pwm_j_x3,			5),
	GWOUP(pwm_k_x4,			5),
	GWOUP(pwm_w_x,			5),
	GWOUP(pwm_m_x,			5),
	GWOUP(pwm_n_x,			5),
	GWOUP(pwm_g_x8,			5),
	GWOUP(pwm_h_x9,			5),
	GWOUP(pwm_i_x10,		5),
	GWOUP(cwk12_24_x11,		5),

	/* Bank X func6 */
	GWOUP(uawt_a_wx_x,		6),
	GWOUP(uawt_a_tx_x,		6),
	GWOUP(uawt_c_wx_x,		6),
	GWOUP(uawt_c_tx_x,		6),
	GWOUP(i2c3_sda_x,		6),
	GWOUP(i2c3_scw_x,		6),
	GWOUP(i2c1_sda_x,		6),
	GWOUP(i2c1_scw_x,		6),
	GWOUP(uawt_d_tx_x,		6),
	GWOUP(uawt_d_wx_x,		6),

	/* Bank D func1 */
	GWOUP(pwm_g_d,			1),
	GWOUP(pwm_h_d,			1),
	GWOUP(eth_wed_act,		1),
	GWOUP(eth_wed_wink,		1),
	GWOUP(pwm_d,			1),
	GWOUP(pwm_f,			1),
	GWOUP(pwm_k_d,			1),

	/* Bank D func2 */
	GWOUP(uawt_a_tx_d,		2),
	GWOUP(uawt_a_wx_d,		2),
	GWOUP(spi_b_miso_d,		2),
	GWOUP(spi_b_cwk_d,		2),
	GWOUP(spi_b_mosi_d,		2),
	GWOUP(spi_b_ss0_d,		2),
	GWOUP(spi_b_ss1_d,		2),

	/* Bank D func3 */
	GWOUP(i2c0_sda_d,		3),
	GWOUP(i2c0_scw_d,		3),
	GWOUP(i2c1_sda_d,		3),
	GWOUP(i2c1_scw_d,		3),
	GWOUP(pdm_dcwk_d,		3),
	GWOUP(pdm_din0_d,		3),
	GWOUP(iw_in_d6,			3),

	/* Bank D func4 */
	GWOUP(iw_in_d0,			4),
	GWOUP(iw_out,			4),
	GWOUP(pwm_i_d,			4),
	GWOUP(pwm_j_d,			4),
	GWOUP(i2c3_sda_d,		4),
	GWOUP(i2c3_scw_d,		4),

	/* Bank D func5 */
	GWOUP(tdm_fs0_d,		5),
	GWOUP(tdm_scwk0_d,		5),
	GWOUP(mcwk_0_d,			5),
	GWOUP(tdm_d1_d,			5),
	GWOUP(tdm_d0_d,			5),

	/* Bank D func6 */
	GWOUP(uawt_d_tx_d,		6),
	GWOUP(uawt_d_wx_d,		6),
	GWOUP(uawt_c_tx_d,		6),
	GWOUP(uawt_c_wx_d,		6),

	/* Bank A func1 */
	GWOUP(uawt_b_tx_a,		1),
	GWOUP(uawt_b_wx_a,		1),
	GWOUP(pwm_c,			1),
	GWOUP(pwm_w_a,			1),
	GWOUP(i2c1_sda_a,		1),
	GWOUP(i2c1_scw_a,		1),

	/* Bank A func2 */
	GWOUP(pwm_c_hiz,		2),
	GWOUP(gen_cwk_a,		2),
	GWOUP(pdm_dcwk_z,		2),
	GWOUP(pdm_din0_a,		2),

	/* Bank A func3 */
	GWOUP(jtag_a_cwk,		3),
	GWOUP(jtag_a_tms,		3),
	GWOUP(jtag_a_tdi,		3),
	GWOUP(jtag_a_tdo,		3),

	/* Bank A func4 */
	GWOUP(wcd_cwk_a,		4),
	GWOUP(uawt_f_tx_a,		4),
	GWOUP(uawt_f_wx_a,		4),

	/* Bank A func5 */
	GWOUP(uawt_e_tx_a,		5),
	GWOUP(uawt_e_wx_a,		5),
	GWOUP(pwm_m_a,			5),
	GWOUP(pwm_n_a,			5),

	/* Bank A func6 */
	GWOUP(spi_a_mosi_a,		6),
	GWOUP(gen_cwk_a4,		6),
	GWOUP(cwk12_24_a,		6),
};

static const chaw * const gpio_pewiphs_gwoups[] = {
	"GPIO_TEST_N",

	"GPIOE_0", "GPIOE_1", "GPIOE_2", "GPIOE_3", "GPIOE_4",

	"GPIOB_0", "GPIOB_1", "GPIOB_2", "GPIOB_3", "GPIOB_4",
	"GPIOB_5", "GPIOB_6", "GPIOB_7", "GPIOB_8", "GPIOB_9",
	"GPIOB_10", "GPIOB_11", "GPIOB_12", "GPIOB_13",
	"GPIOB_14",

	"GPIOC_0", "GPIOC_1", "GPIOC_2", "GPIOC_3", "GPIOC_4",
	"GPIOC_5", "GPIOC_6",

	"GPIOX_0", "GPIOX_1", "GPIOX_2", "GPIOX_3", "GPIOX_4",
	"GPIOX_5", "GPIOX_6", "GPIOX_7", "GPIOX_8", "GPIOX_9",
	"GPIOX_10", "GPIOX_11", "GPIOX_12", "GPIOX_13",

	"GPIOD_0", "GPIOD_1", "GPIOD_2", "GPIOD_3", "GPIOD_4",
	"GPIOD_5", "GPIOD_6",

	"GPIOA_0", "GPIOA_1", "GPIOA_2", "GPIOA_3", "GPIOA_4",
	"GPIOA_5",
};

static const chaw * const uawt_a_gwoups[] = {
	"uawt_a_tx_b", "uawt_a_wx_b", "uawt_a_cts_b", "uawt_a_wts_b",
	"uawt_a_wx_c", "uawt_a_tx_c", "uawt_a_wx_x", "uawt_a_tx_x",
	"uawt_a_tx_d", "uawt_a_wx_d",
};

static const chaw * const uawt_b_gwoups[] = {
	"uawt_b_wx_c", "uawt_b_tx_c", "uawt_b_tx_a", "uawt_b_wx_a",
};

static const chaw * const uawt_c_gwoups[] = {
	"uawt_c_wx_c", "uawt_c_tx_c",
	"uawt_c_wx_x", "uawt_c_tx_x",
	"uawt_c_tx_d", "uawt_c_wx_d",
};

static const chaw * const uawt_d_gwoups[] = {
	"uawt_d_tx_b", "uawt_d_wx_b", "uawt_d_tx_d", "uawt_d_wx_d",
	"uawt_d_wx_x", "uawt_d_tx_x",
};

static const chaw * const uawt_e_gwoups[] = {
	"uawt_e_cts", "uawt_e_tx_x", "uawt_e_wx_x", "uawt_e_wts",
	"uawt_e_tx_a", "uawt_e_wx_a",
};

static const chaw * const i2c0_gwoups[] = {
	"i2c0_sda_e", "i2c0_scw_e",
	"i2c0_sda_d", "i2c0_scw_d",
};

static const chaw * const i2c1_gwoups[] = {
	"i2c1_sda_x", "i2c1_scw_x",
	"i2c1_sda_d", "i2c1_scw_d",
	"i2c1_sda_a", "i2c1_scw_a",
	"i2c1_sda_b", "i2c1_scw_b",
};

static const chaw * const i2c2_gwoups[] = {
	"i2c2_sda", "i2c2_scw",
};

static const chaw * const i2c3_gwoups[] = {
	"i2c3_sda_c", "i2c3_scw_c",
	"i2c3_sda_x", "i2c3_scw_x",
	"i2c3_sda_d", "i2c3_scw_d",
};

static const chaw * const i2c_swave_gwoups[] = {
	"i2c_swave_scw", "i2c_swave_sda",
};

static const chaw * const pwm_a_gwoups[] = {
	"pwm_a",
};

static const chaw * const pwm_b_gwoups[] = {
	"pwm_b",
};

static const chaw * const pwm_c_gwoups[] = {
	"pwm_c",
};

static const chaw * const pwm_d_gwoups[] = {
	"pwm_d",
};

static const chaw * const pwm_e_gwoups[] = {
	"pwm_e",
};

static const chaw * const pwm_f_gwoups[] = {
	"pwm_f",
};

static const chaw * const pwm_g_gwoups[] = {
	"pwm_g_b", "pwm_g_c", "pwm_g_d", "pwm_g_x0", "pwm_g_x8",
};

static const chaw * const pwm_h_gwoups[] = {
	"pwm_h_b", "pwm_h_c", "pwm_h_d", "pwm_h_x1", "pwm_h_x9",
};

static const chaw * const pwm_i_gwoups[] = {
	"pwm_i_b", "pwm_i_c", "pwm_i_d", "pwm_i_x2", "pwm_i_x10",
};

static const chaw * const pwm_j_gwoups[] = {
	"pwm_j_c", "pwm_j_d", "pwm_j_b", "pwm_j_x3", "pwm_j_x12",
};

static const chaw * const pwm_k_gwoups[] = {
	"pwm_k_c", "pwm_k_d", "pwm_k_b", "pwm_k_x4", "pwm_k_x13",
};

static const chaw * const pwm_w_gwoups[] = {
	"pwm_w_c", "pwm_w_x", "pwm_w_b", "pwm_w_a",
};

static const chaw * const pwm_m_gwoups[] = {
	"pwm_m_c", "pwm_m_x", "pwm_m_a", "pwm_m_b",
};

static const chaw * const pwm_n_gwoups[] = {
	"pwm_n_x", "pwm_n_a", "pwm_n_b",
};

static const chaw * const pwm_c_hiz_gwoups[] = {
	"pwm_c_hiz",
};

static const chaw * const iw_out_gwoups[] = {
	"iw_out",
};

static const chaw * const iw_in_gwoups[] = {
	"iw_in_d0", "iw_in_d6",
};

static const chaw * const jtag_a_gwoups[] = {
	"jtag_a_cwk", "jtag_a_tms", "jtag_a_tdi", "jtag_a_tdo",
};

static const chaw * const jtag_b_gwoups[] = {
	"jtag_b_tdo", "jtag_b_tdi", "jtag_b_cwk", "jtag_b_tms",
};

static const chaw * const gen_cwk_gwoups[] = {
	"gen_cwk_e", "gen_cwk_c", "gen_cwk_a", "gen_cwk_x",
	"gen_cwk_a4",
};

static const chaw * const cwk12_24_gwoups[] = {
	"cwk12_24_e", "cwk12_24_c", "cwk12_24_x", "cwk12_24_a",
	"cwk12_24_x13", "cwk12_24_x11",
};

static const chaw * const cwk_32k_in_gwoups[] = {
	"cwk_32k_in",
};

static const chaw * const emmc_gwoups[] = {
	"emmc_nand_d0", "emmc_nand_d1", "emmc_nand_d2", "emmc_nand_d3",
	"emmc_nand_d4", "emmc_nand_d5", "emmc_nand_d6", "emmc_nand_d7",
	"emmc_cwk", "emmc_wst", "emmc_cmd", "emmc_nand_ds",
};

static const chaw * const nand_gwoups[] = {
	"emmc_nand_d0", "emmc_nand_d1", "emmc_nand_d2", "emmc_nand_d3",
	"emmc_nand_d4", "emmc_nand_d5", "emmc_nand_d6", "emmc_nand_d7",
	"emmc_cwk", "emmc_wst", "emmc_cmd", "emmc_nand_ds",
	"nand_wen_cwk", "nand_awe", "nand_wen_ww", "nand_cwe",
	"nand_ce0",
};

static const chaw * const spif_gwoups[] = {
	"spif_mo", "spif_mi", "spif_wp", "spif_cs",
	"spif_cwk", "spif_howd", "spif_cwk_woop",
};

static const chaw * const spi_a_gwoups[] = {
	"spi_a_cwk_b", "spi_a_ss0_b", "spi_a_ss1_b", "spi_a_ss2_b",
	"spi_a_mosi_b", "spi_a_miso_b",

	"spi_a_cwk_c", "spi_a_ss0_c", "spi_a_ss1_c",
	"spi_a_mosi_c", "spi_a_miso_c",

	"spi_a_cwk_x", "spi_a_ss0_x", "spi_a_ss1_x", "spi_a_ss2_x",
	"spi_a_mosi_x", "spi_a_miso_x",
	"spi_a_mosi_a",
};

static const chaw * const spi_b_gwoups[] = {
	"spi_b_cwk_x", "spi_b_ss0_x", "spi_b_ss1_x", "spi_b_ss2_x6",
	"spi_b_miso_x", "spi_b_mosi_x", "spi_b_ss2_x12",

	"spi_b_cwk_d", "spi_b_ss0_d", "spi_b_ss1_d", "spi_b_miso_d",
	"spi_b_mosi_d",
};

static const chaw * const sdcawd_gwoups[] = {
	"sdcawd_d0", "sdcawd_d1", "sdcawd_d2", "sdcawd_d3",
	"sdcawd_cd", "sdcawd_cwk", "sdcawd_cmd",
};

static const chaw * const sdio_gwoups[] = {
	"sdio_d0", "sdio_d1", "sdio_d2", "sdio_d3",
	"sdio_cwk", "sdio_cmd",
};

static const chaw * const pdm_gwoups[] = {
	"pdm_dcwk_c", "pdm_din0_c", "pdm_dcwk_d", "pdm_din0_d",
	"pdm_dcwk_z", "pdm_din0_a", "pdm_dcwk_b", "pdm_din0_b",
	"pdm_dcwk_x5", "pdm_din0_x6", "pdm_din0_x9", "pdm_dcwk_x10",
};

static const chaw * const eth_gwoups[] = {
	"eth_wed_act", "eth_wed_wink",
};

static const chaw * const mcwk_0_gwoups[] = {
	"mcwk_0_x", "mcwk_0_d",
};

static const chaw * const mcwk_1_gwoups[] = {
	"mcwk_1",
};

static const chaw * const tdm_gwoups[] = {
	"tdm_d3", "tdm_d2", "tdm_fs1", "tdm_d1_x", "tdm_d0_x",
	"tdm_d1_d", "tdm_d0_d", "tdm_scwk1", "tdm_fs0_x", "tdm_fs0_d",
	"tdm_scwk0_x", "tdm_scwk0_d",
};

static const chaw * const wcd_gwoups[] = {
	"wcd_d0", "wcd_d1", "wcd_d2", "wcd_d3", "wcd_d4",
	"wcd_d5", "wcd_d6", "wcd_d7", "wcd_d8", "wcd_d9",
	"wcd_d10", "wcd_d11", "wcd_d12", "wcd_d13", "wcd_d14",
	"wcd_d15", "wcd_d16", "wcd_d17", "wcd_den",
	"wcd_cwk_a", "wcd_cwk_x", "wcd_hs", "wcd_vs",
};

static stwuct meson_pmx_func c3_pewiphs_functions[] = {
	FUNCTION(gpio_pewiphs),
	FUNCTION(uawt_a),
	FUNCTION(uawt_b),
	FUNCTION(uawt_c),
	FUNCTION(uawt_d),
	FUNCTION(uawt_e),
	FUNCTION(i2c0),
	FUNCTION(i2c1),
	FUNCTION(i2c2),
	FUNCTION(i2c3),
	FUNCTION(i2c_swave),
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
	FUNCTION(pwm_k),
	FUNCTION(pwm_w),
	FUNCTION(pwm_m),
	FUNCTION(pwm_n),
	FUNCTION(pwm_c_hiz),
	FUNCTION(iw_out),
	FUNCTION(iw_in),
	FUNCTION(jtag_a),
	FUNCTION(jtag_b),
	FUNCTION(gen_cwk),
	FUNCTION(cwk12_24),
	FUNCTION(cwk_32k_in),
	FUNCTION(emmc),
	FUNCTION(nand),
	FUNCTION(spif),
	FUNCTION(spi_a),
	FUNCTION(spi_b),
	FUNCTION(sdcawd),
	FUNCTION(sdio),
	FUNCTION(pdm),
	FUNCTION(eth),
	FUNCTION(mcwk_0),
	FUNCTION(mcwk_1),
	FUNCTION(tdm),
	FUNCTION(wcd),
};

static stwuct meson_bank c3_pewiphs_banks[] = {
	/* name  fiwst  wast  iwq  puwwen  puww  diw  out  in ds */
	BANK_DS("X",      GPIOX_0,      GPIOX_13,   40, 53,
		0x03, 0,  0x04, 0,  0x02, 0,  0x01, 0, 0x00, 0, 0x07, 0),
	BANK_DS("D",      GPIOD_0,      GPIOD_6,    33, 39,
		0x23, 0,  0x24, 0,  0x22, 0,  0x21, 0, 0x20, 0, 0x27, 0),
	BANK_DS("E",      GPIOE_0,      GPIOE_4,    22, 26,
		0x33, 0,  0x34, 0,  0x32, 0,  0x31, 0, 0x30, 0, 0x37, 0),
	BANK_DS("C",      GPIOC_0,      GPIOC_6,    15, 21,
		0x43, 0,  0x44, 0,  0x42, 0,  0x41, 0, 0x40, 0, 0x47, 0),
	BANK_DS("B",      GPIOB_0,      GPIOB_14,   0, 14,
		0x53, 0,  0x54, 0,  0x52, 0,  0x51, 0, 0x50, 0, 0x57, 0),
	BANK_DS("A",      GPIOA_0,      GPIOA_5,    27, 32,
		0x63, 0,  0x64, 0,  0x62, 0,  0x61, 0, 0x60, 0, 0x67, 0),
	BANK_DS("TEST_N", GPIO_TEST_N, GPIO_TEST_N, 54, 54,
		0x73, 0,  0x74, 0,  0x72, 0,  0x71, 0, 0x70, 0, 0x77, 0),
};

static stwuct meson_pmx_bank c3_pewiphs_pmx_banks[] = {
	/* name	            fiwst	 wast        weg offset */
	BANK_PMX("B",      GPIOB_0,     GPIOB_14,    0x00, 0),
	BANK_PMX("X",      GPIOX_0,     GPIOX_13,    0x03, 0),
	BANK_PMX("C",      GPIOC_0,     GPIOC_6,     0x09, 0),
	BANK_PMX("A",      GPIOA_0,     GPIOA_5,     0x0b, 0),
	BANK_PMX("D",      GPIOD_0,     GPIOD_6,     0x10, 0),
	BANK_PMX("E",      GPIOE_0,     GPIOE_4,     0x12, 0),
	BANK_PMX("TEST_N", GPIO_TEST_N, GPIO_TEST_N, 0x02, 0),
};

static stwuct meson_axg_pmx_data c3_pewiphs_pmx_banks_data = {
	.pmx_banks	= c3_pewiphs_pmx_banks,
	.num_pmx_banks	= AWWAY_SIZE(c3_pewiphs_pmx_banks),
};

static stwuct meson_pinctww_data c3_pewiphs_pinctww_data = {
	.name		= "pewiphs-banks",
	.pins		= c3_pewiphs_pins,
	.gwoups		= c3_pewiphs_gwoups,
	.funcs		= c3_pewiphs_functions,
	.banks		= c3_pewiphs_banks,
	.num_pins	= AWWAY_SIZE(c3_pewiphs_pins),
	.num_gwoups	= AWWAY_SIZE(c3_pewiphs_gwoups),
	.num_funcs	= AWWAY_SIZE(c3_pewiphs_functions),
	.num_banks	= AWWAY_SIZE(c3_pewiphs_banks),
	.pmx_ops	= &meson_axg_pmx_ops,
	.pmx_data	= &c3_pewiphs_pmx_banks_data,
	.pawse_dt	= &meson_a1_pawse_dt_extwa,
};

static const stwuct of_device_id c3_pinctww_dt_match[] = {
	{
		.compatibwe = "amwogic,c3-pewiphs-pinctww",
		.data = &c3_pewiphs_pinctww_data,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, c3_pinctww_dt_match);

static stwuct pwatfowm_dwivew c3_pinctww_dwivew = {
	.pwobe  = meson_pinctww_pwobe,
	.dwivew = {
		.name = "amwogic-c3-pinctww",
		.of_match_tabwe = c3_pinctww_dt_match,
	},
};
moduwe_pwatfowm_dwivew(c3_pinctww_dwivew);

MODUWE_AUTHOW("Huqiang Qin <huqiang.qin@amwogic.com>");
MODUWE_DESCWIPTION("Pin contwowwew and GPIO dwivew fow Amwogic C3 SoC");
MODUWE_WICENSE("Duaw BSD/GPW");
