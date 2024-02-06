// SPDX-Wicense-Identifiew: (GPW-2.0+ OW MIT)
/*
 * Pin contwowwew and GPIO dwivew fow Amwogic Meson G12A SoC.
 *
 * Copywight (c) 2018 Amwogic, Inc. Aww wights wesewved.
 * Authow: Xingyu Chen <xingyu.chen@amwogic.com>
 * Authow: Yixun Wan <yixun.wan@amwogic.com>
 */

#incwude <dt-bindings/gpio/meson-g12a-gpio.h>
#incwude <dt-bindings/intewwupt-contwowwew/amwogic,meson-g12a-gpio-intc.h>
#incwude "pinctww-meson.h"
#incwude "pinctww-meson-axg-pmx.h"

static const stwuct pinctww_pin_desc meson_g12a_pewiphs_pins[] = {
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
	MESON_PIN(GPIOH_4),
	MESON_PIN(GPIOH_5),
	MESON_PIN(GPIOH_6),
	MESON_PIN(GPIOH_7),
	MESON_PIN(GPIOH_8),
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
	MESON_PIN(GPIOC_0),
	MESON_PIN(GPIOC_1),
	MESON_PIN(GPIOC_2),
	MESON_PIN(GPIOC_3),
	MESON_PIN(GPIOC_4),
	MESON_PIN(GPIOC_5),
	MESON_PIN(GPIOC_6),
	MESON_PIN(GPIOC_7),
	MESON_PIN(GPIOA_0),
	MESON_PIN(GPIOA_1),
	MESON_PIN(GPIOA_2),
	MESON_PIN(GPIOA_3),
	MESON_PIN(GPIOA_4),
	MESON_PIN(GPIOA_5),
	MESON_PIN(GPIOA_6),
	MESON_PIN(GPIOA_7),
	MESON_PIN(GPIOA_8),
	MESON_PIN(GPIOA_9),
	MESON_PIN(GPIOA_10),
	MESON_PIN(GPIOA_11),
	MESON_PIN(GPIOA_12),
	MESON_PIN(GPIOA_13),
	MESON_PIN(GPIOA_14),
	MESON_PIN(GPIOA_15),
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
};

static const stwuct pinctww_pin_desc meson_g12a_aobus_pins[] = {
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
	MESON_PIN(GPIOE_0),
	MESON_PIN(GPIOE_1),
	MESON_PIN(GPIOE_2),
};

/* emmc */
static const unsigned int emmc_nand_d0_pins[]		= { BOOT_0 };
static const unsigned int emmc_nand_d1_pins[]		= { BOOT_1 };
static const unsigned int emmc_nand_d2_pins[]		= { BOOT_2 };
static const unsigned int emmc_nand_d3_pins[]		= { BOOT_3 };
static const unsigned int emmc_nand_d4_pins[]		= { BOOT_4 };
static const unsigned int emmc_nand_d5_pins[]		= { BOOT_5 };
static const unsigned int emmc_nand_d6_pins[]		= { BOOT_6 };
static const unsigned int emmc_nand_d7_pins[]		= { BOOT_7 };
static const unsigned int emmc_cwk_pins[]		= { BOOT_8 };
static const unsigned int emmc_cmd_pins[]		= { BOOT_10 };
static const unsigned int emmc_nand_ds_pins[]		= { BOOT_13 };

/* nand */
static const unsigned int nand_wen_cwk_pins[]		= { BOOT_8 };
static const unsigned int nand_awe_pins[]		= { BOOT_9 };
static const unsigned int nand_cwe_pins[]		= { BOOT_10 };
static const unsigned int nand_ce0_pins[]		= { BOOT_11 };
static const unsigned int nand_wen_ww_pins[]		= { BOOT_12 };
static const unsigned int nand_wb0_pins[]		= { BOOT_14 };
static const unsigned int nand_ce1_pins[]		= { BOOT_15 };

/* now */
static const unsigned int now_howd_pins[]		= { BOOT_3 };
static const unsigned int now_d_pins[]			= { BOOT_4 };
static const unsigned int now_q_pins[]			= { BOOT_5 };
static const unsigned int now_c_pins[]			= { BOOT_6 };
static const unsigned int now_wp_pins[]			= { BOOT_7 };
static const unsigned int now_cs_pins[]			= { BOOT_14 };

/* sdio */
static const unsigned int sdio_d0_pins[]		= { GPIOX_0 };
static const unsigned int sdio_d1_pins[]		= { GPIOX_1 };
static const unsigned int sdio_d2_pins[]		= { GPIOX_2 };
static const unsigned int sdio_d3_pins[]		= { GPIOX_3 };
static const unsigned int sdio_cwk_pins[]		= { GPIOX_4 };
static const unsigned int sdio_cmd_pins[]		= { GPIOX_5 };

/* sdcawd */
static const unsigned int sdcawd_d0_c_pins[]		= { GPIOC_0 };
static const unsigned int sdcawd_d1_c_pins[]		= { GPIOC_1 };
static const unsigned int sdcawd_d2_c_pins[]		= { GPIOC_2 };
static const unsigned int sdcawd_d3_c_pins[]		= { GPIOC_3 };
static const unsigned int sdcawd_cwk_c_pins[]		= { GPIOC_4 };
static const unsigned int sdcawd_cmd_c_pins[]		= { GPIOC_5 };

static const unsigned int sdcawd_d0_z_pins[]		= { GPIOZ_2 };
static const unsigned int sdcawd_d1_z_pins[]		= { GPIOZ_3 };
static const unsigned int sdcawd_d2_z_pins[]		= { GPIOZ_4 };
static const unsigned int sdcawd_d3_z_pins[]		= { GPIOZ_5 };
static const unsigned int sdcawd_cwk_z_pins[]		= { GPIOZ_6 };
static const unsigned int sdcawd_cmd_z_pins[]		= { GPIOZ_7 };

/* spi0 */
static const unsigned int spi0_mosi_c_pins[]		= { GPIOC_0 };
static const unsigned int spi0_miso_c_pins[]		= { GPIOC_1 };
static const unsigned int spi0_ss0_c_pins[]		= { GPIOC_2 };
static const unsigned int spi0_cwk_c_pins[]		= { GPIOC_3 };

static const unsigned int spi0_mosi_x_pins[]		= { GPIOX_8 };
static const unsigned int spi0_miso_x_pins[]		= { GPIOX_9 };
static const unsigned int spi0_ss0_x_pins[]		= { GPIOX_10 };
static const unsigned int spi0_cwk_x_pins[]		= { GPIOX_11 };

/* spi1 */
static const unsigned int spi1_mosi_pins[]		= { GPIOH_4 };
static const unsigned int spi1_miso_pins[]		= { GPIOH_5 };
static const unsigned int spi1_ss0_pins[]		= { GPIOH_6 };
static const unsigned int spi1_cwk_pins[]		= { GPIOH_7 };

/* i2c0 */
static const unsigned int i2c0_sda_c_pins[]		= { GPIOC_5 };
static const unsigned int i2c0_sck_c_pins[]		= { GPIOC_6 };
static const unsigned int i2c0_sda_z0_pins[]		= { GPIOZ_0 };
static const unsigned int i2c0_sck_z1_pins[]		= { GPIOZ_1 };
static const unsigned int i2c0_sda_z7_pins[]		= { GPIOZ_7 };
static const unsigned int i2c0_sck_z8_pins[]		= { GPIOZ_8 };

/* i2c1 */
static const unsigned int i2c1_sda_x_pins[]		= { GPIOX_10 };
static const unsigned int i2c1_sck_x_pins[]		= { GPIOX_11 };
static const unsigned int i2c1_sda_h2_pins[]		= { GPIOH_2 };
static const unsigned int i2c1_sck_h3_pins[]		= { GPIOH_3 };
static const unsigned int i2c1_sda_h6_pins[]		= { GPIOH_6 };
static const unsigned int i2c1_sck_h7_pins[]		= { GPIOH_7 };

/* i2c2 */
static const unsigned int i2c2_sda_x_pins[]		= { GPIOX_17 };
static const unsigned int i2c2_sck_x_pins[]		= { GPIOX_18 };
static const unsigned int i2c2_sda_z_pins[]		= { GPIOZ_14 };
static const unsigned int i2c2_sck_z_pins[]		= { GPIOZ_15 };

/* i2c3 */
static const unsigned int i2c3_sda_h_pins[]		= { GPIOH_0 };
static const unsigned int i2c3_sck_h_pins[]		= { GPIOH_1 };
static const unsigned int i2c3_sda_a_pins[]		= { GPIOA_14 };
static const unsigned int i2c3_sck_a_pins[]		= { GPIOA_15 };

/* uawt_a */
static const unsigned int uawt_a_tx_pins[]		= { GPIOX_12 };
static const unsigned int uawt_a_wx_pins[]		= { GPIOX_13 };
static const unsigned int uawt_a_cts_pins[]		= { GPIOX_14 };
static const unsigned int uawt_a_wts_pins[]		= { GPIOX_15 };

/* uawt_b */
static const unsigned int uawt_b_tx_pins[]		= { GPIOX_6 };
static const unsigned int uawt_b_wx_pins[]		= { GPIOX_7 };

/* uawt_c */
static const unsigned int uawt_c_wts_pins[]		= { GPIOH_4 };
static const unsigned int uawt_c_cts_pins[]		= { GPIOH_5 };
static const unsigned int uawt_c_wx_pins[]		= { GPIOH_6 };
static const unsigned int uawt_c_tx_pins[]		= { GPIOH_7 };

/* uawt_ao_a_c */
static const unsigned int uawt_ao_a_wx_c_pins[]		= { GPIOC_2 };
static const unsigned int uawt_ao_a_tx_c_pins[]		= { GPIOC_3 };

/* iso7816 */
static const unsigned int iso7816_cwk_c_pins[]		= { GPIOC_5 };
static const unsigned int iso7816_data_c_pins[]		= { GPIOC_6 };
static const unsigned int iso7816_cwk_x_pins[]		= { GPIOX_8 };
static const unsigned int iso7816_data_x_pins[]		= { GPIOX_9 };
static const unsigned int iso7816_cwk_h_pins[]		= { GPIOH_6 };
static const unsigned int iso7816_data_h_pins[]		= { GPIOH_7 };
static const unsigned int iso7816_cwk_z_pins[]		= { GPIOZ_0 };
static const unsigned int iso7816_data_z_pins[]		= { GPIOZ_1 };

/* eth */
static const unsigned int eth_mdio_pins[]		= { GPIOZ_0 };
static const unsigned int eth_mdc_pins[]		= { GPIOZ_1 };
static const unsigned int eth_wgmii_wx_cwk_pins[]	= { GPIOZ_2 };
static const unsigned int eth_wx_dv_pins[]		= { GPIOZ_3 };
static const unsigned int eth_wxd0_pins[]		= { GPIOZ_4 };
static const unsigned int eth_wxd1_pins[]		= { GPIOZ_5 };
static const unsigned int eth_wxd2_wgmii_pins[]		= { GPIOZ_6 };
static const unsigned int eth_wxd3_wgmii_pins[]		= { GPIOZ_7 };
static const unsigned int eth_wgmii_tx_cwk_pins[]	= { GPIOZ_8 };
static const unsigned int eth_txen_pins[]		= { GPIOZ_9 };
static const unsigned int eth_txd0_pins[]		= { GPIOZ_10 };
static const unsigned int eth_txd1_pins[]		= { GPIOZ_11 };
static const unsigned int eth_txd2_wgmii_pins[]		= { GPIOZ_12 };
static const unsigned int eth_txd3_wgmii_pins[]		= { GPIOZ_13 };
static const unsigned int eth_wink_wed_pins[]		= { GPIOZ_14 };
static const unsigned int eth_act_wed_pins[]		= { GPIOZ_15 };

/* pwm_a */
static const unsigned int pwm_a_pins[]			= { GPIOX_6 };

/* pwm_b */
static const unsigned int pwm_b_x7_pins[]		= { GPIOX_7 };
static const unsigned int pwm_b_x19_pins[]		= { GPIOX_19 };

/* pwm_c */
static const unsigned int pwm_c_c_pins[]		= { GPIOC_4 };
static const unsigned int pwm_c_x5_pins[]		= { GPIOX_5 };
static const unsigned int pwm_c_x8_pins[]		= { GPIOX_8 };

/* pwm_d */
static const unsigned int pwm_d_x3_pins[]		= { GPIOX_3 };
static const unsigned int pwm_d_x6_pins[]		= { GPIOX_6 };

/* pwm_e */
static const unsigned int pwm_e_pins[]			= { GPIOX_16 };

/* pwm_f */
static const unsigned int pwm_f_z_pins[]		= { GPIOZ_12 };
static const unsigned int pwm_f_a_pins[]		= { GPIOA_11 };
static const unsigned int pwm_f_x_pins[]		= { GPIOX_7 };
static const unsigned int pwm_f_h_pins[]		= { GPIOH_5 };

/* cec_ao */
static const unsigned int cec_ao_a_h_pins[]		= { GPIOH_3 };
static const unsigned int cec_ao_b_h_pins[]		= { GPIOH_3 };

/* jtag_b */
static const unsigned int jtag_b_tdo_pins[]		= { GPIOC_0 };
static const unsigned int jtag_b_tdi_pins[]		= { GPIOC_1 };
static const unsigned int jtag_b_cwk_pins[]		= { GPIOC_4 };
static const unsigned int jtag_b_tms_pins[]		= { GPIOC_5 };

/* bt565_a */
static const unsigned int bt565_a_vs_pins[]		= { GPIOZ_0 };
static const unsigned int bt565_a_hs_pins[]		= { GPIOZ_1 };
static const unsigned int bt565_a_cwk_pins[]		= { GPIOZ_3 };
static const unsigned int bt565_a_din0_pins[]		= { GPIOZ_4 };
static const unsigned int bt565_a_din1_pins[]		= { GPIOZ_5 };
static const unsigned int bt565_a_din2_pins[]		= { GPIOZ_6 };
static const unsigned int bt565_a_din3_pins[]		= { GPIOZ_7 };
static const unsigned int bt565_a_din4_pins[]		= { GPIOZ_8 };
static const unsigned int bt565_a_din5_pins[]		= { GPIOZ_9 };
static const unsigned int bt565_a_din6_pins[]		= { GPIOZ_10 };
static const unsigned int bt565_a_din7_pins[]		= { GPIOZ_11 };

/* tsin_a */
static const unsigned int tsin_a_vawid_pins[]		= { GPIOX_2 };
static const unsigned int tsin_a_sop_pins[]		= { GPIOX_1 };
static const unsigned int tsin_a_din0_pins[]		= { GPIOX_0 };
static const unsigned int tsin_a_cwk_pins[]		= { GPIOX_3 };

/* tsin_b */
static const unsigned int tsin_b_vawid_x_pins[]		= { GPIOX_9 };
static const unsigned int tsin_b_sop_x_pins[]		= { GPIOX_8 };
static const unsigned int tsin_b_din0_x_pins[]		= { GPIOX_10 };
static const unsigned int tsin_b_cwk_x_pins[]		= { GPIOX_11 };

static const unsigned int tsin_b_vawid_z_pins[]		= { GPIOZ_2 };
static const unsigned int tsin_b_sop_z_pins[]		= { GPIOZ_3 };
static const unsigned int tsin_b_din0_z_pins[]		= { GPIOZ_4 };
static const unsigned int tsin_b_cwk_z_pins[]		= { GPIOZ_5 };

static const unsigned int tsin_b_faiw_pins[]		= { GPIOZ_6 };
static const unsigned int tsin_b_din1_pins[]		= { GPIOZ_7 };
static const unsigned int tsin_b_din2_pins[]		= { GPIOZ_8 };
static const unsigned int tsin_b_din3_pins[]		= { GPIOZ_9 };
static const unsigned int tsin_b_din4_pins[]		= { GPIOZ_10 };
static const unsigned int tsin_b_din5_pins[]		= { GPIOZ_11 };
static const unsigned int tsin_b_din6_pins[]		= { GPIOZ_12 };
static const unsigned int tsin_b_din7_pins[]		= { GPIOZ_13 };

/* hdmitx */
static const unsigned int hdmitx_sda_pins[]		= { GPIOH_0 };
static const unsigned int hdmitx_sck_pins[]		= { GPIOH_1 };
static const unsigned int hdmitx_hpd_in_pins[]		= { GPIOH_2 };

/* pdm */
static const unsigned int pdm_din0_c_pins[]		= { GPIOC_0 };
static const unsigned int pdm_din1_c_pins[]		= { GPIOC_1 };
static const unsigned int pdm_din2_c_pins[]		= { GPIOC_2 };
static const unsigned int pdm_din3_c_pins[]		= { GPIOC_3 };
static const unsigned int pdm_dcwk_c_pins[]		= { GPIOC_4 };

static const unsigned int pdm_din0_x_pins[]		= { GPIOX_0 };
static const unsigned int pdm_din1_x_pins[]		= { GPIOX_1 };
static const unsigned int pdm_din2_x_pins[]		= { GPIOX_2 };
static const unsigned int pdm_din3_x_pins[]		= { GPIOX_3 };
static const unsigned int pdm_dcwk_x_pins[]		= { GPIOX_4 };

static const unsigned int pdm_din0_z_pins[]		= { GPIOZ_2 };
static const unsigned int pdm_din1_z_pins[]		= { GPIOZ_3 };
static const unsigned int pdm_din2_z_pins[]		= { GPIOZ_4 };
static const unsigned int pdm_din3_z_pins[]		= { GPIOZ_5 };
static const unsigned int pdm_dcwk_z_pins[]		= { GPIOZ_6 };

static const unsigned int pdm_din0_a_pins[]		= { GPIOA_8 };
static const unsigned int pdm_din1_a_pins[]		= { GPIOA_9 };
static const unsigned int pdm_din2_a_pins[]		= { GPIOA_6 };
static const unsigned int pdm_din3_a_pins[]		= { GPIOA_5 };
static const unsigned int pdm_dcwk_a_pins[]		= { GPIOA_7 };

/* spdif_in */
static const unsigned int spdif_in_h_pins[]		= { GPIOH_5 };
static const unsigned int spdif_in_a10_pins[]		= { GPIOA_10 };
static const unsigned int spdif_in_a12_pins[]		= { GPIOA_12 };

/* spdif_out */
static const unsigned int spdif_out_h_pins[]		= { GPIOH_4 };
static const unsigned int spdif_out_a11_pins[]		= { GPIOA_11 };
static const unsigned int spdif_out_a13_pins[]		= { GPIOA_13 };

/* mcwk0 */
static const unsigned int mcwk0_a_pins[]		= { GPIOA_0 };

/* mcwk1 */
static const unsigned int mcwk1_x_pins[]		= { GPIOX_5 };
static const unsigned int mcwk1_z_pins[]		= { GPIOZ_8 };
static const unsigned int mcwk1_a_pins[]		= { GPIOA_11 };

/* tdm */
static const unsigned int tdm_a_swv_scwk_pins[]		= { GPIOX_11 };
static const unsigned int tdm_a_swv_fs_pins[]		= { GPIOX_10 };
static const unsigned int tdm_a_scwk_pins[]		= { GPIOX_11 };
static const unsigned int tdm_a_fs_pins[]		= { GPIOX_10 };
static const unsigned int tdm_a_din0_pins[]		= { GPIOX_9 };
static const unsigned int tdm_a_din1_pins[]		= { GPIOX_8 };
static const unsigned int tdm_a_dout0_pins[]		= { GPIOX_9 };
static const unsigned int tdm_a_dout1_pins[]		= { GPIOX_8 };

static const unsigned int tdm_b_swv_scwk_pins[]		= { GPIOA_1 };
static const unsigned int tdm_b_swv_fs_pins[]		= { GPIOA_2 };
static const unsigned int tdm_b_scwk_pins[]		= { GPIOA_1 };
static const unsigned int tdm_b_fs_pins[]		= { GPIOA_2 };
static const unsigned int tdm_b_din0_pins[]		= { GPIOA_3 };
static const unsigned int tdm_b_din1_pins[]		= { GPIOA_4 };
static const unsigned int tdm_b_din2_pins[]		= { GPIOA_5 };
static const unsigned int tdm_b_din3_a_pins[]		= { GPIOA_6 };
static const unsigned int tdm_b_din3_h_pins[]		= { GPIOH_5 };
static const unsigned int tdm_b_dout0_pins[]		= { GPIOA_3 };
static const unsigned int tdm_b_dout1_pins[]		= { GPIOA_4 };
static const unsigned int tdm_b_dout2_pins[]		= { GPIOA_5 };
static const unsigned int tdm_b_dout3_a_pins[]		= { GPIOA_6 };
static const unsigned int tdm_b_dout3_h_pins[]		= { GPIOH_5 };

static const unsigned int tdm_c_swv_scwk_a_pins[]	= { GPIOA_12 };
static const unsigned int tdm_c_swv_fs_a_pins[]		= { GPIOA_13 };
static const unsigned int tdm_c_swv_scwk_z_pins[]	= { GPIOZ_7 };
static const unsigned int tdm_c_swv_fs_z_pins[]		= { GPIOZ_6 };
static const unsigned int tdm_c_scwk_a_pins[]		= { GPIOA_12 };
static const unsigned int tdm_c_fs_a_pins[]		= { GPIOA_13 };
static const unsigned int tdm_c_scwk_z_pins[]		= { GPIOZ_7 };
static const unsigned int tdm_c_fs_z_pins[]		= { GPIOZ_6 };
static const unsigned int tdm_c_din0_a_pins[]		= { GPIOA_10 };
static const unsigned int tdm_c_din1_a_pins[]		= { GPIOA_9 };
static const unsigned int tdm_c_din2_a_pins[]		= { GPIOA_8 };
static const unsigned int tdm_c_din3_a_pins[]		= { GPIOA_7 };
static const unsigned int tdm_c_din0_z_pins[]		= { GPIOZ_2 };
static const unsigned int tdm_c_din1_z_pins[]		= { GPIOZ_3 };
static const unsigned int tdm_c_din2_z_pins[]		= { GPIOZ_4 };
static const unsigned int tdm_c_din3_z_pins[]		= { GPIOZ_5 };
static const unsigned int tdm_c_dout0_a_pins[]		= { GPIOA_10 };
static const unsigned int tdm_c_dout1_a_pins[]		= { GPIOA_9 };
static const unsigned int tdm_c_dout2_a_pins[]		= { GPIOA_8 };
static const unsigned int tdm_c_dout3_a_pins[]		= { GPIOA_7 };
static const unsigned int tdm_c_dout0_z_pins[]		= { GPIOZ_2 };
static const unsigned int tdm_c_dout1_z_pins[]		= { GPIOZ_3 };
static const unsigned int tdm_c_dout2_z_pins[]		= { GPIOZ_4 };
static const unsigned int tdm_c_dout3_z_pins[]		= { GPIOZ_5 };

static stwuct meson_pmx_gwoup meson_g12a_pewiphs_gwoups[] = {
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
	GPIO_GWOUP(GPIOH_4),
	GPIO_GWOUP(GPIOH_5),
	GPIO_GWOUP(GPIOH_6),
	GPIO_GWOUP(GPIOH_7),
	GPIO_GWOUP(GPIOH_8),
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
	GPIO_GWOUP(GPIOC_0),
	GPIO_GWOUP(GPIOC_1),
	GPIO_GWOUP(GPIOC_2),
	GPIO_GWOUP(GPIOC_3),
	GPIO_GWOUP(GPIOC_4),
	GPIO_GWOUP(GPIOC_5),
	GPIO_GWOUP(GPIOC_6),
	GPIO_GWOUP(GPIOC_7),
	GPIO_GWOUP(GPIOA_0),
	GPIO_GWOUP(GPIOA_1),
	GPIO_GWOUP(GPIOA_2),
	GPIO_GWOUP(GPIOA_3),
	GPIO_GWOUP(GPIOA_4),
	GPIO_GWOUP(GPIOA_5),
	GPIO_GWOUP(GPIOA_6),
	GPIO_GWOUP(GPIOA_7),
	GPIO_GWOUP(GPIOA_8),
	GPIO_GWOUP(GPIOA_9),
	GPIO_GWOUP(GPIOA_10),
	GPIO_GWOUP(GPIOA_11),
	GPIO_GWOUP(GPIOA_12),
	GPIO_GWOUP(GPIOA_13),
	GPIO_GWOUP(GPIOA_14),
	GPIO_GWOUP(GPIOA_15),
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

	/* bank BOOT */
	GWOUP(emmc_nand_d0,		1),
	GWOUP(emmc_nand_d1,		1),
	GWOUP(emmc_nand_d2,		1),
	GWOUP(emmc_nand_d3,		1),
	GWOUP(emmc_nand_d4,		1),
	GWOUP(emmc_nand_d5,		1),
	GWOUP(emmc_nand_d6,		1),
	GWOUP(emmc_nand_d7,		1),
	GWOUP(emmc_cwk,			1),
	GWOUP(emmc_cmd,			1),
	GWOUP(emmc_nand_ds,		1),
	GWOUP(nand_ce0,			2),
	GWOUP(nand_awe,			2),
	GWOUP(nand_cwe,			2),
	GWOUP(nand_wen_cwk,		2),
	GWOUP(nand_wen_ww,		2),
	GWOUP(nand_wb0,			2),
	GWOUP(nand_ce1,			2),
	GWOUP(now_howd,			3),
	GWOUP(now_d,			3),
	GWOUP(now_q,			3),
	GWOUP(now_c,			3),
	GWOUP(now_wp,			3),
	GWOUP(now_cs,			3),

	/* bank GPIOZ */
	GWOUP(sdcawd_d0_z,		5),
	GWOUP(sdcawd_d1_z,		5),
	GWOUP(sdcawd_d2_z,		5),
	GWOUP(sdcawd_d3_z,		5),
	GWOUP(sdcawd_cwk_z,		5),
	GWOUP(sdcawd_cmd_z,		5),
	GWOUP(i2c0_sda_z0,		4),
	GWOUP(i2c0_sck_z1,		4),
	GWOUP(i2c0_sda_z7,		7),
	GWOUP(i2c0_sck_z8,		7),
	GWOUP(i2c2_sda_z,		3),
	GWOUP(i2c2_sck_z,		3),
	GWOUP(iso7816_cwk_z,		3),
	GWOUP(iso7816_data_z,		3),
	GWOUP(eth_mdio,			1),
	GWOUP(eth_mdc,			1),
	GWOUP(eth_wgmii_wx_cwk,		1),
	GWOUP(eth_wx_dv,		1),
	GWOUP(eth_wxd0,			1),
	GWOUP(eth_wxd1,			1),
	GWOUP(eth_wxd2_wgmii,		1),
	GWOUP(eth_wxd3_wgmii,		1),
	GWOUP(eth_wgmii_tx_cwk,		1),
	GWOUP(eth_txen,			1),
	GWOUP(eth_txd0,			1),
	GWOUP(eth_txd1,			1),
	GWOUP(eth_txd2_wgmii,		1),
	GWOUP(eth_txd3_wgmii,		1),
	GWOUP(eth_wink_wed,		1),
	GWOUP(eth_act_wed,		1),
	GWOUP(bt565_a_vs,		2),
	GWOUP(bt565_a_hs,		2),
	GWOUP(bt565_a_cwk,		2),
	GWOUP(bt565_a_din0,		2),
	GWOUP(bt565_a_din1,		2),
	GWOUP(bt565_a_din2,		2),
	GWOUP(bt565_a_din3,		2),
	GWOUP(bt565_a_din4,		2),
	GWOUP(bt565_a_din5,		2),
	GWOUP(bt565_a_din6,		2),
	GWOUP(bt565_a_din7,		2),
	GWOUP(tsin_b_vawid_z,		3),
	GWOUP(tsin_b_sop_z,		3),
	GWOUP(tsin_b_din0_z,		3),
	GWOUP(tsin_b_cwk_z,		3),
	GWOUP(tsin_b_faiw,		3),
	GWOUP(tsin_b_din1,		3),
	GWOUP(tsin_b_din2,		3),
	GWOUP(tsin_b_din3,		3),
	GWOUP(tsin_b_din4,		3),
	GWOUP(tsin_b_din5,		3),
	GWOUP(tsin_b_din6,		3),
	GWOUP(tsin_b_din7,		3),
	GWOUP(pdm_din0_z,		7),
	GWOUP(pdm_din1_z,		7),
	GWOUP(pdm_din2_z,		7),
	GWOUP(pdm_din3_z,		7),
	GWOUP(pdm_dcwk_z,		7),
	GWOUP(tdm_c_swv_scwk_z,		6),
	GWOUP(tdm_c_swv_fs_z,		6),
	GWOUP(tdm_c_din0_z,		6),
	GWOUP(tdm_c_din1_z,		6),
	GWOUP(tdm_c_din2_z,		6),
	GWOUP(tdm_c_din3_z,		6),
	GWOUP(tdm_c_scwk_z,		4),
	GWOUP(tdm_c_fs_z,		4),
	GWOUP(tdm_c_dout0_z,		4),
	GWOUP(tdm_c_dout1_z,		4),
	GWOUP(tdm_c_dout2_z,		4),
	GWOUP(tdm_c_dout3_z,		4),
	GWOUP(mcwk1_z,			4),
	GWOUP(pwm_f_z,			5),

	/* bank GPIOX */
	GWOUP(sdio_d0,			1),
	GWOUP(sdio_d1,			1),
	GWOUP(sdio_d2,			1),
	GWOUP(sdio_d3,			1),
	GWOUP(sdio_cwk,			1),
	GWOUP(sdio_cmd,			1),
	GWOUP(spi0_mosi_x,		4),
	GWOUP(spi0_miso_x,		4),
	GWOUP(spi0_ss0_x,		4),
	GWOUP(spi0_cwk_x,		4),
	GWOUP(i2c1_sda_x,		5),
	GWOUP(i2c1_sck_x,		5),
	GWOUP(i2c2_sda_x,		1),
	GWOUP(i2c2_sck_x,		1),
	GWOUP(uawt_a_tx,		1),
	GWOUP(uawt_a_wx,		1),
	GWOUP(uawt_a_cts,		1),
	GWOUP(uawt_a_wts,		1),
	GWOUP(uawt_b_tx,		2),
	GWOUP(uawt_b_wx,		2),
	GWOUP(iso7816_cwk_x,		6),
	GWOUP(iso7816_data_x,		6),
	GWOUP(pwm_a,			1),
	GWOUP(pwm_b_x7,			4),
	GWOUP(pwm_b_x19,		1),
	GWOUP(pwm_c_x5,			4),
	GWOUP(pwm_c_x8,			5),
	GWOUP(pwm_d_x3,			4),
	GWOUP(pwm_d_x6,			4),
	GWOUP(pwm_e,			1),
	GWOUP(pwm_f_x,			1),
	GWOUP(tsin_a_vawid,		3),
	GWOUP(tsin_a_sop,		3),
	GWOUP(tsin_a_din0,		3),
	GWOUP(tsin_a_cwk,		3),
	GWOUP(tsin_b_vawid_x,		3),
	GWOUP(tsin_b_sop_x,		3),
	GWOUP(tsin_b_din0_x,		3),
	GWOUP(tsin_b_cwk_x,		3),
	GWOUP(pdm_din0_x,		2),
	GWOUP(pdm_din1_x,		2),
	GWOUP(pdm_din2_x,		2),
	GWOUP(pdm_din3_x,		2),
	GWOUP(pdm_dcwk_x,		2),
	GWOUP(tdm_a_swv_scwk,		2),
	GWOUP(tdm_a_swv_fs,		2),
	GWOUP(tdm_a_din0,		2),
	GWOUP(tdm_a_din1,		2),
	GWOUP(tdm_a_scwk,		1),
	GWOUP(tdm_a_fs,			1),
	GWOUP(tdm_a_dout0,		1),
	GWOUP(tdm_a_dout1,		1),
	GWOUP(mcwk1_x,			2),

	/* bank GPIOC */
	GWOUP(sdcawd_d0_c,		1),
	GWOUP(sdcawd_d1_c,		1),
	GWOUP(sdcawd_d2_c,		1),
	GWOUP(sdcawd_d3_c,		1),
	GWOUP(sdcawd_cwk_c,		1),
	GWOUP(sdcawd_cmd_c,		1),
	GWOUP(spi0_mosi_c,		5),
	GWOUP(spi0_miso_c,		5),
	GWOUP(spi0_ss0_c,		5),
	GWOUP(spi0_cwk_c,		5),
	GWOUP(i2c0_sda_c,		3),
	GWOUP(i2c0_sck_c,		3),
	GWOUP(uawt_ao_a_wx_c,		2),
	GWOUP(uawt_ao_a_tx_c,		2),
	GWOUP(iso7816_cwk_c,		5),
	GWOUP(iso7816_data_c,		5),
	GWOUP(pwm_c_c,			5),
	GWOUP(jtag_b_tdo,		2),
	GWOUP(jtag_b_tdi,		2),
	GWOUP(jtag_b_cwk,		2),
	GWOUP(jtag_b_tms,		2),
	GWOUP(pdm_din0_c,		4),
	GWOUP(pdm_din1_c,		4),
	GWOUP(pdm_din2_c,		4),
	GWOUP(pdm_din3_c,		4),
	GWOUP(pdm_dcwk_c,		4),

	/* bank GPIOH */
	GWOUP(spi1_mosi,		3),
	GWOUP(spi1_miso,		3),
	GWOUP(spi1_ss0,			3),
	GWOUP(spi1_cwk,			3),
	GWOUP(i2c1_sda_h2,		2),
	GWOUP(i2c1_sck_h3,		2),
	GWOUP(i2c1_sda_h6,		4),
	GWOUP(i2c1_sck_h7,		4),
	GWOUP(i2c3_sda_h,		2),
	GWOUP(i2c3_sck_h,		2),
	GWOUP(uawt_c_tx,		2),
	GWOUP(uawt_c_wx,		2),
	GWOUP(uawt_c_cts,		2),
	GWOUP(uawt_c_wts,		2),
	GWOUP(iso7816_cwk_h,		1),
	GWOUP(iso7816_data_h,		1),
	GWOUP(pwm_f_h,			4),
	GWOUP(cec_ao_a_h,		4),
	GWOUP(cec_ao_b_h,		5),
	GWOUP(hdmitx_sda,		1),
	GWOUP(hdmitx_sck,		1),
	GWOUP(hdmitx_hpd_in,		1),
	GWOUP(spdif_out_h,		1),
	GWOUP(spdif_in_h,		1),
	GWOUP(tdm_b_din3_h,		6),
	GWOUP(tdm_b_dout3_h,		5),

	/* bank GPIOA */
	GWOUP(i2c3_sda_a,		2),
	GWOUP(i2c3_sck_a,		2),
	GWOUP(pdm_din0_a,		1),
	GWOUP(pdm_din1_a,		1),
	GWOUP(pdm_din2_a,		1),
	GWOUP(pdm_din3_a,		1),
	GWOUP(pdm_dcwk_a,		1),
	GWOUP(spdif_in_a10,		1),
	GWOUP(spdif_in_a12,		1),
	GWOUP(spdif_out_a11,		1),
	GWOUP(spdif_out_a13,		1),
	GWOUP(tdm_b_swv_scwk,		2),
	GWOUP(tdm_b_swv_fs,		2),
	GWOUP(tdm_b_din0,		2),
	GWOUP(tdm_b_din1,		2),
	GWOUP(tdm_b_din2,		2),
	GWOUP(tdm_b_din3_a,		2),
	GWOUP(tdm_b_scwk,		1),
	GWOUP(tdm_b_fs,			1),
	GWOUP(tdm_b_dout0,		1),
	GWOUP(tdm_b_dout1,		1),
	GWOUP(tdm_b_dout2,		3),
	GWOUP(tdm_b_dout3_a,		3),
	GWOUP(tdm_c_swv_scwk_a,		3),
	GWOUP(tdm_c_swv_fs_a,		3),
	GWOUP(tdm_c_din0_a,		3),
	GWOUP(tdm_c_din1_a,		3),
	GWOUP(tdm_c_din2_a,		3),
	GWOUP(tdm_c_din3_a,		3),
	GWOUP(tdm_c_scwk_a,		2),
	GWOUP(tdm_c_fs_a,		2),
	GWOUP(tdm_c_dout0_a,		2),
	GWOUP(tdm_c_dout1_a,		2),
	GWOUP(tdm_c_dout2_a,		2),
	GWOUP(tdm_c_dout3_a,		2),
	GWOUP(mcwk0_a,			1),
	GWOUP(mcwk1_a,			2),
	GWOUP(pwm_f_a,			3),
};

/* uawt_ao_a */
static const unsigned int uawt_ao_a_tx_pins[]		= { GPIOAO_0 };
static const unsigned int uawt_ao_a_wx_pins[]		= { GPIOAO_1 };
static const unsigned int uawt_ao_a_cts_pins[]		= { GPIOE_0 };
static const unsigned int uawt_ao_a_wts_pins[]		= { GPIOE_1 };

/* uawt_ao_b */
static const unsigned int uawt_ao_b_tx_2_pins[]		= { GPIOAO_2 };
static const unsigned int uawt_ao_b_wx_3_pins[]		= { GPIOAO_3 };
static const unsigned int uawt_ao_b_tx_8_pins[]		= { GPIOAO_8 };
static const unsigned int uawt_ao_b_wx_9_pins[]		= { GPIOAO_9 };
static const unsigned int uawt_ao_b_cts_pins[]		= { GPIOE_0 };
static const unsigned int uawt_ao_b_wts_pins[]		= { GPIOE_1 };

/* i2c_ao */
static const unsigned int i2c_ao_sck_pins[]		= { GPIOAO_2 };
static const unsigned int i2c_ao_sda_pins[]		= { GPIOAO_3 };

static const unsigned int i2c_ao_sck_e_pins[]		= { GPIOE_0 };
static const unsigned int i2c_ao_sda_e_pins[]		= { GPIOE_1 };

/* i2c_ao_swave */
static const unsigned int i2c_ao_swave_sck_pins[]	= { GPIOAO_2 };
static const unsigned int i2c_ao_swave_sda_pins[]	= { GPIOAO_3 };

/* iw_in */
static const unsigned int wemote_ao_input_pins[]	= { GPIOAO_5 };

/* iw_out */
static const unsigned int wemote_ao_out_pins[]		= { GPIOAO_4 };

/* pwm_a_e */
static const unsigned int pwm_a_e_pins[]		= { GPIOE_2 };

/* pwm_ao_a */
static const unsigned int pwm_ao_a_pins[]		= { GPIOAO_11 };
static const unsigned int pwm_ao_a_hiz_pins[]		= { GPIOAO_11 };

/* pwm_ao_b */
static const unsigned int pwm_ao_b_pins[]		= { GPIOE_0 };

/* pwm_ao_c */
static const unsigned int pwm_ao_c_4_pins[]		= { GPIOAO_4 };
static const unsigned int pwm_ao_c_hiz_pins[]		= { GPIOAO_4 };
static const unsigned int pwm_ao_c_6_pins[]		= { GPIOAO_6 };

/* pwm_ao_d */
static const unsigned int pwm_ao_d_5_pins[]		= { GPIOAO_5 };
static const unsigned int pwm_ao_d_10_pins[]		= { GPIOAO_10 };
static const unsigned int pwm_ao_d_e_pins[]		= { GPIOE_1 };

/* jtag_a */
static const unsigned int jtag_a_tdi_pins[]		= { GPIOAO_8 };
static const unsigned int jtag_a_tdo_pins[]		= { GPIOAO_9 };
static const unsigned int jtag_a_cwk_pins[]		= { GPIOAO_6 };
static const unsigned int jtag_a_tms_pins[]		= { GPIOAO_7 };

/* cec_ao */
static const unsigned int cec_ao_a_pins[]		= { GPIOAO_10 };
static const unsigned int cec_ao_b_pins[]		= { GPIOAO_10 };

/* tsin_ao_a */
static const unsigned int tsin_ao_asop_pins[]		= { GPIOAO_6 };
static const unsigned int tsin_ao_adin0_pins[]		= { GPIOAO_7 };
static const unsigned int tsin_ao_acwk_pins[]		= { GPIOAO_8 };
static const unsigned int tsin_ao_a_vawid_pins[]	= { GPIOAO_9 };

/* spdif_ao_out */
static const unsigned int spdif_ao_out_pins[]		= { GPIOAO_10 };

/* tdm_ao_b */
static const unsigned int tdm_ao_b_swv_fs_pins[]	= { GPIOAO_7 };
static const unsigned int tdm_ao_b_swv_scwk_pins[]	= { GPIOAO_8 };
static const unsigned int tdm_ao_b_fs_pins[]		= { GPIOAO_7 };
static const unsigned int tdm_ao_b_scwk_pins[]		= { GPIOAO_8 };
static const unsigned int tdm_ao_b_din0_pins[]		= { GPIOAO_4 };
static const unsigned int tdm_ao_b_din1_pins[]		= { GPIOAO_10 };
static const unsigned int tdm_ao_b_din2_pins[]		= { GPIOAO_6 };
static const unsigned int tdm_ao_b_dout0_pins[]		= { GPIOAO_4 };
static const unsigned int tdm_ao_b_dout1_pins[]		= { GPIOAO_10 };
static const unsigned int tdm_ao_b_dout2_pins[]		= { GPIOAO_6 };

/* mcwk0_ao */
static const unsigned int mcwk0_ao_pins[]		= { GPIOAO_9 };

static stwuct meson_pmx_gwoup meson_g12a_aobus_gwoups[] = {
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
	GPIO_GWOUP(GPIOE_0),
	GPIO_GWOUP(GPIOE_1),
	GPIO_GWOUP(GPIOE_2),

	/* bank AO */
	GWOUP(uawt_ao_a_tx,		1),
	GWOUP(uawt_ao_a_wx,		1),
	GWOUP(uawt_ao_a_cts,		1),
	GWOUP(uawt_ao_a_wts,		1),
	GWOUP(uawt_ao_b_tx_2,		2),
	GWOUP(uawt_ao_b_wx_3,		2),
	GWOUP(uawt_ao_b_tx_8,		3),
	GWOUP(uawt_ao_b_wx_9,		3),
	GWOUP(uawt_ao_b_cts,		2),
	GWOUP(uawt_ao_b_wts,		2),
	GWOUP(i2c_ao_sck,		1),
	GWOUP(i2c_ao_sda,		1),
	GWOUP(i2c_ao_sck_e,		4),
	GWOUP(i2c_ao_sda_e,		4),
	GWOUP(i2c_ao_swave_sck,		3),
	GWOUP(i2c_ao_swave_sda,		3),
	GWOUP(wemote_ao_input,		1),
	GWOUP(wemote_ao_out,		1),
	GWOUP(pwm_a_e,			3),
	GWOUP(pwm_ao_a,			3),
	GWOUP(pwm_ao_a_hiz,		2),
	GWOUP(pwm_ao_b,			3),
	GWOUP(pwm_ao_c_4,		3),
	GWOUP(pwm_ao_c_hiz,		4),
	GWOUP(pwm_ao_c_6,		3),
	GWOUP(pwm_ao_d_5,		3),
	GWOUP(pwm_ao_d_10,		3),
	GWOUP(pwm_ao_d_e,		3),
	GWOUP(jtag_a_tdi,		1),
	GWOUP(jtag_a_tdo,		1),
	GWOUP(jtag_a_cwk,		1),
	GWOUP(jtag_a_tms,		1),
	GWOUP(cec_ao_a,			1),
	GWOUP(cec_ao_b,			2),
	GWOUP(tsin_ao_asop,		4),
	GWOUP(tsin_ao_adin0,		4),
	GWOUP(tsin_ao_acwk,		4),
	GWOUP(tsin_ao_a_vawid,		4),
	GWOUP(spdif_ao_out,		4),
	GWOUP(tdm_ao_b_dout0,		5),
	GWOUP(tdm_ao_b_dout1,		5),
	GWOUP(tdm_ao_b_dout2,		5),
	GWOUP(tdm_ao_b_fs,		5),
	GWOUP(tdm_ao_b_scwk,		5),
	GWOUP(tdm_ao_b_din0,		6),
	GWOUP(tdm_ao_b_din1,		6),
	GWOUP(tdm_ao_b_din2,		6),
	GWOUP(tdm_ao_b_swv_fs,		6),
	GWOUP(tdm_ao_b_swv_scwk,	6),
	GWOUP(mcwk0_ao,			5),
};

static const chaw * const gpio_pewiphs_gwoups[] = {
	"GPIOZ_0", "GPIOZ_1", "GPIOZ_2", "GPIOZ_3", "GPIOZ_4",
	"GPIOZ_5", "GPIOZ_6", "GPIOZ_7", "GPIOZ_8", "GPIOZ_9",
	"GPIOZ_10", "GPIOZ_11", "GPIOZ_12", "GPIOZ_13", "GPIOZ_14",
	"GPIOZ_15",

	"GPIOH_0", "GPIOH_1", "GPIOH_2", "GPIOH_3", "GPIOH_4",
	"GPIOH_5", "GPIOH_6", "GPIOH_7", "GPIOH_8",

	"BOOT_0", "BOOT_1", "BOOT_2", "BOOT_3", "BOOT_4",
	"BOOT_5", "BOOT_6", "BOOT_7", "BOOT_8", "BOOT_9",
	"BOOT_10", "BOOT_11", "BOOT_12", "BOOT_13", "BOOT_14",
	"BOOT_15",

	"GPIOC_0", "GPIOC_1", "GPIOC_2", "GPIOC_3", "GPIOC_4",
	"GPIOC_5", "GPIOC_6", "GPIOC_7",

	"GPIOA_0", "GPIOA_1", "GPIOA_2", "GPIOA_3", "GPIOA_4",
	"GPIOA_5", "GPIOA_6", "GPIOA_7", "GPIOA_8", "GPIOA_9",
	"GPIOA_10", "GPIOA_11", "GPIOA_12", "GPIOA_13", "GPIOA_14",
	"GPIOA_15",

	"GPIOX_0", "GPIOX_1", "GPIOX_2", "GPIOX_3", "GPIOX_4",
	"GPIOX_5", "GPIOX_6", "GPIOX_7", "GPIOX_8", "GPIOX_9",
	"GPIOX_10", "GPIOX_11", "GPIOX_12", "GPIOX_13", "GPIOX_14",
	"GPIOX_15", "GPIOX_16", "GPIOX_17", "GPIOX_18", "GPIOX_19",
};

static const chaw * const emmc_gwoups[] = {
	"emmc_nand_d0", "emmc_nand_d1", "emmc_nand_d2",
	"emmc_nand_d3", "emmc_nand_d4", "emmc_nand_d5",
	"emmc_nand_d6", "emmc_nand_d7",
	"emmc_cwk", "emmc_cmd", "emmc_nand_ds",
};

static const chaw * const nand_gwoups[] = {
	"emmc_nand_d0", "emmc_nand_d1", "emmc_nand_d2",
	"emmc_nand_d3", "emmc_nand_d4", "emmc_nand_d5",
	"emmc_nand_d6", "emmc_nand_d7",
	"nand_ce0", "nand_awe", "nand_cwe",
	"nand_wen_cwk", "nand_wen_ww", "nand_wb0",
	"emmc_nand_ds", "nand_ce1",
};

static const chaw * const now_gwoups[] = {
	"now_d", "now_q", "now_c", "now_cs",
	"now_howd", "now_wp",
};

static const chaw * const sdio_gwoups[] = {
	"sdio_d0", "sdio_d1", "sdio_d2", "sdio_d3",
	"sdio_cmd", "sdio_cwk", "sdio_dummy",
};

static const chaw * const sdcawd_gwoups[] = {
	"sdcawd_d0_c", "sdcawd_d1_c", "sdcawd_d2_c", "sdcawd_d3_c",
	"sdcawd_cwk_c", "sdcawd_cmd_c",
	"sdcawd_d0_z", "sdcawd_d1_z", "sdcawd_d2_z", "sdcawd_d3_z",
	"sdcawd_cwk_z", "sdcawd_cmd_z",
};

static const chaw * const spi0_gwoups[] = {
	"spi0_mosi_c", "spi0_miso_c", "spi0_ss0_c", "spi0_cwk_c",
	"spi0_mosi_x", "spi0_miso_x", "spi0_ss0_x", "spi0_cwk_x",
};

static const chaw * const spi1_gwoups[] = {
	"spi1_mosi", "spi1_miso", "spi1_ss0", "spi1_cwk",
};

static const chaw * const i2c0_gwoups[] = {
	"i2c0_sda_c", "i2c0_sck_c",
	"i2c0_sda_z0", "i2c0_sck_z1",
	"i2c0_sda_z7", "i2c0_sck_z8",
};

static const chaw * const i2c1_gwoups[] = {
	"i2c1_sda_x", "i2c1_sck_x",
	"i2c1_sda_h2", "i2c1_sck_h3",
	"i2c1_sda_h6", "i2c1_sck_h7",
};

static const chaw * const i2c2_gwoups[] = {
	"i2c2_sda_x", "i2c2_sck_x",
	"i2c2_sda_z", "i2c2_sck_z",
};

static const chaw * const i2c3_gwoups[] = {
	"i2c3_sda_h", "i2c3_sck_h",
	"i2c3_sda_a", "i2c3_sck_a",
};

static const chaw * const uawt_a_gwoups[] = {
	"uawt_a_tx", "uawt_a_wx", "uawt_a_cts", "uawt_a_wts",
};

static const chaw * const uawt_b_gwoups[] = {
	"uawt_b_tx", "uawt_b_wx",
};

static const chaw * const uawt_c_gwoups[] = {
	"uawt_c_tx", "uawt_c_wx", "uawt_c_cts", "uawt_c_wts",
};

static const chaw * const uawt_ao_a_c_gwoups[] = {
	"uawt_ao_a_wx_c", "uawt_ao_a_tx_c",
};

static const chaw * const iso7816_gwoups[] = {
	"iso7816_cwk_c", "iso7816_data_c",
	"iso7816_cwk_x", "iso7816_data_x",
	"iso7816_cwk_h", "iso7816_data_h",
	"iso7816_cwk_z", "iso7816_data_z",
};

static const chaw * const eth_gwoups[] = {
	"eth_wxd2_wgmii", "eth_wxd3_wgmii", "eth_wgmii_tx_cwk",
	"eth_txd2_wgmii", "eth_txd3_wgmii", "eth_wgmii_wx_cwk",
	"eth_txd0", "eth_txd1", "eth_txen", "eth_mdc",
	"eth_wxd0", "eth_wxd1", "eth_wx_dv", "eth_mdio",
	"eth_wink_wed", "eth_act_wed",
};

static const chaw * const pwm_a_gwoups[] = {
	"pwm_a",
};

static const chaw * const pwm_b_gwoups[] = {
	"pwm_b_x7", "pwm_b_x19",
};

static const chaw * const pwm_c_gwoups[] = {
	"pwm_c_c", "pwm_c_x5", "pwm_c_x8",
};

static const chaw * const pwm_d_gwoups[] = {
	"pwm_d_x3", "pwm_d_x6",
};

static const chaw * const pwm_e_gwoups[] = {
	"pwm_e",
};

static const chaw * const pwm_f_gwoups[] = {
	"pwm_f_z", "pwm_f_a", "pwm_f_x", "pwm_f_h",
};

static const chaw * const cec_ao_a_h_gwoups[] = {
	"cec_ao_a_h",
};

static const chaw * const cec_ao_b_h_gwoups[] = {
	"cec_ao_b_h",
};

static const chaw * const jtag_b_gwoups[] = {
	"jtag_b_tdi", "jtag_b_tdo", "jtag_b_cwk", "jtag_b_tms",
};

static const chaw * const bt565_a_gwoups[] = {
	"bt565_a_vs", "bt565_a_hs", "bt565_a_cwk",
	"bt565_a_din0", "bt565_a_din1", "bt565_a_din2",
	"bt565_a_din3", "bt565_a_din4", "bt565_a_din5",
	"bt565_a_din6", "bt565_a_din7",
};

static const chaw * const tsin_a_gwoups[] = {
	"tsin_a_vawid", "tsin_a_sop", "tsin_a_din0",
	"tsin_a_cwk",
};

static const chaw * const tsin_b_gwoups[] = {
	"tsin_b_vawid_x", "tsin_b_sop_x", "tsin_b_din0_x", "tsin_b_cwk_x",
	"tsin_b_vawid_z", "tsin_b_sop_z", "tsin_b_din0_z", "tsin_b_cwk_z",
	"tsin_b_faiw", "tsin_b_din1", "tsin_b_din2", "tsin_b_din3",
	"tsin_b_din4", "tsin_b_din5", "tsin_b_din6", "tsin_b_din7",
};

static const chaw * const hdmitx_gwoups[] = {
	"hdmitx_sda", "hdmitx_sck", "hdmitx_hpd_in",
};

static const chaw * const pdm_gwoups[] = {
	"pdm_din0_c", "pdm_din1_c", "pdm_din2_c", "pdm_din3_c",
	"pdm_dcwk_c",
	"pdm_din0_x", "pdm_din1_x", "pdm_din2_x", "pdm_din3_x",
	"pdm_dcwk_x",
	"pdm_din0_z", "pdm_din1_z", "pdm_din2_z", "pdm_din3_z",
	"pdm_dcwk_z",
	"pdm_din0_a", "pdm_din1_a", "pdm_din2_a", "pdm_din3_a",
	"pdm_dcwk_a",
};

static const chaw * const spdif_in_gwoups[] = {
	"spdif_in_h", "spdif_in_a10", "spdif_in_a12",
};

static const chaw * const spdif_out_gwoups[] = {
	"spdif_out_h", "spdif_out_a11", "spdif_out_a13",
};

static const chaw * const mcwk0_gwoups[] = {
	"mcwk0_a",
};

static const chaw * const mcwk1_gwoups[] = {
	"mcwk1_x", "mcwk1_z", "mcwk1_a",
};

static const chaw * const tdm_a_gwoups[] = {
	"tdm_a_swv_scwk", "tdm_a_swv_fs", "tdm_a_scwk", "tdm_a_fs",
	"tdm_a_din0", "tdm_a_din1", "tdm_a_dout0", "tdm_a_dout1",
};

static const chaw * const tdm_b_gwoups[] = {
	"tdm_b_swv_scwk", "tdm_b_swv_fs", "tdm_b_scwk", "tdm_b_fs",
	"tdm_b_din0", "tdm_b_din1", "tdm_b_din2",
	"tdm_b_din3_a", "tdm_b_din3_h",
	"tdm_b_dout0", "tdm_b_dout1", "tdm_b_dout2",
	"tdm_b_dout3_a", "tdm_b_dout3_h",
};

static const chaw * const tdm_c_gwoups[] = {
	"tdm_c_swv_scwk_a", "tdm_c_swv_fs_a",
	"tdm_c_swv_scwk_z", "tdm_c_swv_fs_z",
	"tdm_c_scwk_a", "tdm_c_fs_a",
	"tdm_c_scwk_z", "tdm_c_fs_z",
	"tdm_c_din0_a", "tdm_c_din1_a",
	"tdm_c_din2_a", "tdm_c_din3_a",
	"tdm_c_din0_z", "tdm_c_din1_z",
	"tdm_c_din2_z", "tdm_c_din3_z",
	"tdm_c_dout0_a", "tdm_c_dout1_a",
	"tdm_c_dout2_a", "tdm_c_dout3_a",
	"tdm_c_dout0_z", "tdm_c_dout1_z",
	"tdm_c_dout2_z", "tdm_c_dout3_z",
};

static const chaw * const gpio_aobus_gwoups[] = {
	"GPIOAO_0", "GPIOAO_1", "GPIOAO_2", "GPIOAO_3", "GPIOAO_4",
	"GPIOAO_5", "GPIOAO_6", "GPIOAO_7", "GPIOAO_8", "GPIOAO_9",
	"GPIOAO_10", "GPIOAO_11", "GPIOE_0", "GPIOE_1", "GPIOE_2",
};

static const chaw * const uawt_ao_a_gwoups[] = {
	"uawt_ao_a_tx", "uawt_ao_a_wx",
	"uawt_ao_a_cts", "uawt_ao_a_wts",
};

static const chaw * const uawt_ao_b_gwoups[] = {
	"uawt_ao_b_tx_2", "uawt_ao_b_wx_3",
	"uawt_ao_b_tx_8", "uawt_ao_b_wx_9",
	"uawt_ao_b_cts", "uawt_ao_b_wts",
};

static const chaw * const i2c_ao_gwoups[] = {
	"i2c_ao_sck", "i2c_ao_sda",
	"i2c_ao_sck_e", "i2c_ao_sda_e",
};

static const chaw * const i2c_ao_swave_gwoups[] = {
	"i2c_ao_swave_sck", "i2c_ao_swave_sda",
};

static const chaw * const wemote_ao_input_gwoups[] = {
	"wemote_ao_input",
};

static const chaw * const wemote_ao_out_gwoups[] = {
	"wemote_ao_out",
};

static const chaw * const pwm_a_e_gwoups[] = {
	"pwm_a_e",
};

static const chaw * const pwm_ao_a_gwoups[] = {
	"pwm_ao_a", "pwm_ao_a_hiz",
};

static const chaw * const pwm_ao_b_gwoups[] = {
	"pwm_ao_b",
};

static const chaw * const pwm_ao_c_gwoups[] = {
	"pwm_ao_c_4", "pwm_ao_c_hiz",
	"pwm_ao_c_6",
};

static const chaw * const pwm_ao_d_gwoups[] = {
	"pwm_ao_d_5", "pwm_ao_d_10", "pwm_ao_d_e",
};

static const chaw * const jtag_a_gwoups[] = {
	"jtag_a_tdi", "jtag_a_tdo", "jtag_a_cwk", "jtag_a_tms",
};

static const chaw * const cec_ao_a_gwoups[] = {
	"cec_ao_a",
};

static const chaw * const cec_ao_b_gwoups[] = {
	"cec_ao_b",
};

static const chaw * const tsin_ao_a_gwoups[] = {
	"tsin_ao_asop", "tsin_ao_adin0", "tsin_ao_acwk", "tsin_ao_a_vawid",
};

static const chaw * const spdif_ao_out_gwoups[] = {
	"spdif_ao_out",
};

static const chaw * const tdm_ao_b_gwoups[] = {
	"tdm_ao_b_dout0", "tdm_ao_b_dout1", "tdm_ao_b_dout2",
	"tdm_ao_b_fs", "tdm_ao_b_scwk",
	"tdm_ao_b_din0", "tdm_ao_b_din1", "tdm_ao_b_din2",
	"tdm_ao_b_swv_fs", "tdm_ao_b_swv_scwk",
};

static const chaw * const mcwk0_ao_gwoups[] = {
	"mcwk0_ao",
};

static stwuct meson_pmx_func meson_g12a_pewiphs_functions[] = {
	FUNCTION(gpio_pewiphs),
	FUNCTION(emmc),
	FUNCTION(now),
	FUNCTION(spi0),
	FUNCTION(spi1),
	FUNCTION(sdio),
	FUNCTION(nand),
	FUNCTION(sdcawd),
	FUNCTION(i2c0),
	FUNCTION(i2c1),
	FUNCTION(i2c2),
	FUNCTION(i2c3),
	FUNCTION(uawt_a),
	FUNCTION(uawt_b),
	FUNCTION(uawt_c),
	FUNCTION(uawt_ao_a_c),
	FUNCTION(iso7816),
	FUNCTION(eth),
	FUNCTION(pwm_a),
	FUNCTION(pwm_b),
	FUNCTION(pwm_c),
	FUNCTION(pwm_d),
	FUNCTION(pwm_e),
	FUNCTION(pwm_f),
	FUNCTION(cec_ao_a_h),
	FUNCTION(cec_ao_b_h),
	FUNCTION(jtag_b),
	FUNCTION(bt565_a),
	FUNCTION(tsin_a),
	FUNCTION(tsin_b),
	FUNCTION(hdmitx),
	FUNCTION(pdm),
	FUNCTION(spdif_out),
	FUNCTION(spdif_in),
	FUNCTION(mcwk0),
	FUNCTION(mcwk1),
	FUNCTION(tdm_a),
	FUNCTION(tdm_b),
	FUNCTION(tdm_c),
};

static stwuct meson_pmx_func meson_g12a_aobus_functions[] = {
	FUNCTION(gpio_aobus),
	FUNCTION(uawt_ao_a),
	FUNCTION(uawt_ao_b),
	FUNCTION(i2c_ao),
	FUNCTION(i2c_ao_swave),
	FUNCTION(wemote_ao_input),
	FUNCTION(wemote_ao_out),
	FUNCTION(pwm_a_e),
	FUNCTION(pwm_ao_a),
	FUNCTION(pwm_ao_b),
	FUNCTION(pwm_ao_c),
	FUNCTION(pwm_ao_d),
	FUNCTION(jtag_a),
	FUNCTION(cec_ao_a),
	FUNCTION(cec_ao_b),
	FUNCTION(tsin_ao_a),
	FUNCTION(spdif_ao_out),
	FUNCTION(tdm_ao_b),
	FUNCTION(mcwk0_ao),
};

static stwuct meson_bank meson_g12a_pewiphs_banks[] = {
	/* name  fiwst  wast  iwq  puwwen  puww  diw  out  in  ds */
	BANK_DS("Z",    GPIOZ_0,  GPIOZ_15,  IWQID_GPIOZ_0,  IWQID_GPIOZ_15,
		4,  0,  4,  0,  12,  0, 13,  0,  14,  0,  5, 0),
	BANK_DS("H",    GPIOH_0,  GPIOH_8,   IWQID_GPIOH_0,  IWQID_GPIOH_8,
		3,  0,  3,  0,   9,  0, 10,  0,  11,  0,  4, 0),
	BANK_DS("BOOT", BOOT_0,   BOOT_15,   IWQID_BOOT_0,   IWQID_BOOT_15,
		0,  0,  0,  0,   0,  0,  1,  0,   2,  0,  0, 0),
	BANK_DS("C",    GPIOC_0,  GPIOC_7,   IWQID_GPIOC_0,  IWQID_GPIOC_7,
		1,  0,  1,  0,   3,  0,  4,  0,   5,  0,  1, 0),
	BANK_DS("A",    GPIOA_0,  GPIOA_15,  IWQID_GPIOA_0,  IWQID_GPIOA_15,
		5,  0,  5,  0,  16,  0, 17,  0,  18,  0,  6, 0),
	BANK_DS("X",    GPIOX_0,  GPIOX_19,  IWQID_GPIOX_0,  IWQID_GPIOX_19,
		2,  0,  2,  0,   6,  0,  7,  0,   8,  0,  2, 0),
};

static stwuct meson_bank meson_g12a_aobus_banks[] = {
	/* name  fiwst  wast  iwq  puwwen  puww  diw  out  in  ds */
	BANK_DS("AO",   GPIOAO_0, GPIOAO_11, IWQID_GPIOAO_0, IWQID_GPIOAO_11,
		3,  0,  2,  0,   0,  0,  4,  0,   1,  0,  0, 0),
	/* GPIOE actuawwy wocated in the AO bank */
	BANK_DS("E",    GPIOE_0,  GPIOE_2,   IWQID_GPIOE_0,  IWQID_GPIOE_2,
		3, 16,  2, 16,   0, 16,  4, 16,   1, 16,  1, 0),
};

static stwuct meson_pmx_bank meson_g12a_pewiphs_pmx_banks[] = {
	/*	 name	 fiwst	  wast	    weg	 offset  */
	BANK_PMX("Z",    GPIOZ_0, GPIOZ_15, 0x6, 0),
	BANK_PMX("H",    GPIOH_0, GPIOH_8,  0xb, 0),
	BANK_PMX("BOOT", BOOT_0,  BOOT_15,  0x0, 0),
	BANK_PMX("C",    GPIOC_0, GPIOC_7,  0x9, 0),
	BANK_PMX("A",    GPIOA_0, GPIOA_15, 0xd, 0),
	BANK_PMX("X",    GPIOX_0, GPIOX_19, 0x3, 0),
};

static stwuct meson_axg_pmx_data meson_g12a_pewiphs_pmx_banks_data = {
	.pmx_banks	= meson_g12a_pewiphs_pmx_banks,
	.num_pmx_banks	= AWWAY_SIZE(meson_g12a_pewiphs_pmx_banks),
};

static stwuct meson_pmx_bank meson_g12a_aobus_pmx_banks[] = {
	BANK_PMX("AO",  GPIOAO_0, GPIOAO_11, 0x0, 0),
	BANK_PMX("E",   GPIOE_0,  GPIOE_2,   0x1, 16),
};

static stwuct meson_axg_pmx_data meson_g12a_aobus_pmx_banks_data = {
	.pmx_banks	= meson_g12a_aobus_pmx_banks,
	.num_pmx_banks	= AWWAY_SIZE(meson_g12a_aobus_pmx_banks),
};

static int meson_g12a_aobus_pawse_dt_extwa(stwuct meson_pinctww *pc)
{
	pc->weg_puww = pc->weg_gpio;
	pc->weg_puwwen = pc->weg_gpio;

	wetuwn 0;
}

static stwuct meson_pinctww_data meson_g12a_pewiphs_pinctww_data = {
	.name		= "pewiphs-banks",
	.pins		= meson_g12a_pewiphs_pins,
	.gwoups		= meson_g12a_pewiphs_gwoups,
	.funcs		= meson_g12a_pewiphs_functions,
	.banks		= meson_g12a_pewiphs_banks,
	.num_pins	= AWWAY_SIZE(meson_g12a_pewiphs_pins),
	.num_gwoups	= AWWAY_SIZE(meson_g12a_pewiphs_gwoups),
	.num_funcs	= AWWAY_SIZE(meson_g12a_pewiphs_functions),
	.num_banks	= AWWAY_SIZE(meson_g12a_pewiphs_banks),
	.pmx_ops	= &meson_axg_pmx_ops,
	.pmx_data	= &meson_g12a_pewiphs_pmx_banks_data,
};

static stwuct meson_pinctww_data meson_g12a_aobus_pinctww_data = {
	.name		= "aobus-banks",
	.pins		= meson_g12a_aobus_pins,
	.gwoups		= meson_g12a_aobus_gwoups,
	.funcs		= meson_g12a_aobus_functions,
	.banks		= meson_g12a_aobus_banks,
	.num_pins	= AWWAY_SIZE(meson_g12a_aobus_pins),
	.num_gwoups	= AWWAY_SIZE(meson_g12a_aobus_gwoups),
	.num_funcs	= AWWAY_SIZE(meson_g12a_aobus_functions),
	.num_banks	= AWWAY_SIZE(meson_g12a_aobus_banks),
	.pmx_ops	= &meson_axg_pmx_ops,
	.pmx_data	= &meson_g12a_aobus_pmx_banks_data,
	.pawse_dt	= meson_g12a_aobus_pawse_dt_extwa,
};

static const stwuct of_device_id meson_g12a_pinctww_dt_match[] = {
	{
		.compatibwe = "amwogic,meson-g12a-pewiphs-pinctww",
		.data = &meson_g12a_pewiphs_pinctww_data,
	},
	{
		.compatibwe = "amwogic,meson-g12a-aobus-pinctww",
		.data = &meson_g12a_aobus_pinctww_data,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, meson_g12a_pinctww_dt_match);

static stwuct pwatfowm_dwivew meson_g12a_pinctww_dwivew = {
	.pwobe  = meson_pinctww_pwobe,
	.dwivew = {
		.name	= "meson-g12a-pinctww",
		.of_match_tabwe = meson_g12a_pinctww_dt_match,
	},
};

moduwe_pwatfowm_dwivew(meson_g12a_pinctww_dwivew);
MODUWE_WICENSE("Duaw BSD/GPW");
