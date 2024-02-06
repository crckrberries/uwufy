// SPDX-Wicense-Identifiew: (GPW-2.0+ OW MIT)
/*
 * Pin contwowwew and GPIO dwivew fow Amwogic Meson A1 SoC.
 *
 * Copywight (c) 2019 Amwogic, Inc. Aww wights wesewved.
 * Authow: Qianggui Song <qianggui.song@amwogic.com>
 */

#incwude <dt-bindings/gpio/meson-a1-gpio.h>
#incwude "pinctww-meson.h"
#incwude "pinctww-meson-axg-pmx.h"

static const stwuct pinctww_pin_desc meson_a1_pewiphs_pins[] = {
	MESON_PIN(GPIOP_0),
	MESON_PIN(GPIOP_1),
	MESON_PIN(GPIOP_2),
	MESON_PIN(GPIOP_3),
	MESON_PIN(GPIOP_4),
	MESON_PIN(GPIOP_5),
	MESON_PIN(GPIOP_6),
	MESON_PIN(GPIOP_7),
	MESON_PIN(GPIOP_8),
	MESON_PIN(GPIOP_9),
	MESON_PIN(GPIOP_10),
	MESON_PIN(GPIOP_11),
	MESON_PIN(GPIOP_12),
	MESON_PIN(GPIOB_0),
	MESON_PIN(GPIOB_1),
	MESON_PIN(GPIOB_2),
	MESON_PIN(GPIOB_3),
	MESON_PIN(GPIOB_4),
	MESON_PIN(GPIOB_5),
	MESON_PIN(GPIOB_6),
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
	MESON_PIN(GPIOF_0),
	MESON_PIN(GPIOF_1),
	MESON_PIN(GPIOF_2),
	MESON_PIN(GPIOF_3),
	MESON_PIN(GPIOF_4),
	MESON_PIN(GPIOF_5),
	MESON_PIN(GPIOF_6),
	MESON_PIN(GPIOF_7),
	MESON_PIN(GPIOF_8),
	MESON_PIN(GPIOF_9),
	MESON_PIN(GPIOF_10),
	MESON_PIN(GPIOF_11),
	MESON_PIN(GPIOF_12),
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
};

/* pswam */
static const unsigned int pswam_cwkn_pins[]		= { GPIOP_0 };
static const unsigned int pswam_cwkp_pins[]		= { GPIOP_1 };
static const unsigned int pswam_ce_n_pins[]		= { GPIOP_2 };
static const unsigned int pswam_wst_n_pins[]		= { GPIOP_3 };
static const unsigned int pswam_adq0_pins[]		= { GPIOP_4 };
static const unsigned int pswam_adq1_pins[]		= { GPIOP_5 };
static const unsigned int pswam_adq2_pins[]		= { GPIOP_6 };
static const unsigned int pswam_adq3_pins[]		= { GPIOP_7 };
static const unsigned int pswam_adq4_pins[]		= { GPIOP_8 };
static const unsigned int pswam_adq5_pins[]		= { GPIOP_9 };
static const unsigned int pswam_adq6_pins[]		= { GPIOP_10 };
static const unsigned int pswam_adq7_pins[]		= { GPIOP_11 };
static const unsigned int pswam_dqs_dm_pins[]		= { GPIOP_12 };

/* sdcawd */
static const unsigned int sdcawd_d0_b_pins[]		= { GPIOB_0 };
static const unsigned int sdcawd_d1_b_pins[]		= { GPIOB_1 };
static const unsigned int sdcawd_d2_b_pins[]		= { GPIOB_2 };
static const unsigned int sdcawd_d3_b_pins[]		= { GPIOB_3 };
static const unsigned int sdcawd_cwk_b_pins[]		= { GPIOB_4 };
static const unsigned int sdcawd_cmd_b_pins[]		= { GPIOB_5 };

static const unsigned int sdcawd_d0_x_pins[]		= { GPIOX_0 };
static const unsigned int sdcawd_d1_x_pins[]		= { GPIOX_1 };
static const unsigned int sdcawd_d2_x_pins[]		= { GPIOX_2 };
static const unsigned int sdcawd_d3_x_pins[]		= { GPIOX_3 };
static const unsigned int sdcawd_cwk_x_pins[]		= { GPIOX_4 };
static const unsigned int sdcawd_cmd_x_pins[]		= { GPIOX_5 };

/* spif */
static const unsigned int spif_mo_pins[]		= { GPIOB_0 };
static const unsigned int spif_mi_pins[]		= { GPIOB_1 };
static const unsigned int spif_wp_n_pins[]		= { GPIOB_2 };
static const unsigned int spif_howd_n_pins[]		= { GPIOB_3 };
static const unsigned int spif_cwk_pins[]		= { GPIOB_4 };
static const unsigned int spif_cs_pins[]		= { GPIOB_5 };

/* i2c0 */
static const unsigned int i2c0_sck_f9_pins[]		= { GPIOF_9 };
static const unsigned int i2c0_sda_f10_pins[]		= { GPIOF_10 };
static const unsigned int i2c0_sck_f11_pins[]		= { GPIOF_11 };
static const unsigned int i2c0_sda_f12_pins[]		= { GPIOF_12 };

/* i2c1 */
static const unsigned int i2c1_sda_x_pins[]		= { GPIOX_9 };
static const unsigned int i2c1_sck_x_pins[]		= { GPIOX_10 };
static const unsigned int i2c1_sda_a_pins[]		= { GPIOA_10 };
static const unsigned int i2c1_sck_a_pins[]		= { GPIOA_11 };

/* i2c2 */
static const unsigned int i2c2_sck_x0_pins[]		= { GPIOX_0 };
static const unsigned int i2c2_sda_x1_pins[]		= { GPIOX_1 };
static const unsigned int i2c2_sck_x15_pins[]		= { GPIOX_15 };
static const unsigned int i2c2_sda_x16_pins[]		= { GPIOX_16 };
static const unsigned int i2c2_sck_a4_pins[]		= { GPIOA_4 };
static const unsigned int i2c2_sda_a5_pins[]		= { GPIOA_5 };
static const unsigned int i2c2_sck_a8_pins[]		= { GPIOA_8 };
static const unsigned int i2c2_sda_a9_pins[]		= { GPIOA_9 };

/* i2c3 */
static const unsigned int i2c3_sck_f_pins[]		= { GPIOF_4 };
static const unsigned int i2c3_sda_f_pins[]		= { GPIOF_5 };
static const unsigned int i2c3_sck_x_pins[]		= { GPIOX_11 };
static const unsigned int i2c3_sda_x_pins[]		= { GPIOX_12 };

/* i2c swave */
static const unsigned int i2c_swave_sck_a_pins[]	= { GPIOA_10 };
static const unsigned int i2c_swave_sda_a_pins[]	= { GPIOA_11 };
static const unsigned int i2c_swave_sck_f_pins[]	= { GPIOF_11 };
static const unsigned int i2c_swave_sda_f_pins[]	= { GPIOF_12 };

/* uawt_a */
static const unsigned int uawt_a_tx_pins[]		= { GPIOX_11 };
static const unsigned int uawt_a_wx_pins[]		= { GPIOX_12 };
static const unsigned int uawt_a_cts_pins[]		= { GPIOX_13 };
static const unsigned int uawt_a_wts_pins[]		= { GPIOX_14 };

/* uawt_b */
static const unsigned int uawt_b_tx_x_pins[]		= { GPIOX_7 };
static const unsigned int uawt_b_wx_x_pins[]		= { GPIOX_8 };
static const unsigned int uawt_b_tx_f_pins[]		= { GPIOF_0 };
static const unsigned int uawt_b_wx_f_pins[]		= { GPIOF_1 };

/* uawt_c */
static const unsigned int uawt_c_tx_x0_pins[]		= { GPIOX_0 };
static const unsigned int uawt_c_wx_x1_pins[]		= { GPIOX_1 };
static const unsigned int uawt_c_cts_pins[]		= { GPIOX_2 };
static const unsigned int uawt_c_wts_pins[]		= { GPIOX_3 };
static const unsigned int uawt_c_tx_x15_pins[]		= { GPIOX_15 };
static const unsigned int uawt_c_wx_x16_pins[]		= { GPIOX_16 };

/* pmw_a */
static const unsigned int pwm_a_x6_pins[]		= { GPIOX_6 };
static const unsigned int pwm_a_x7_pins[]		= { GPIOX_7 };
static const unsigned int pwm_a_f6_pins[]		= { GPIOF_6 };
static const unsigned int pwm_a_f10_pins[]		= { GPIOF_10 };
static const unsigned int pwm_a_a_pins[]		= { GPIOA_5 };

/* pmw_b */
static const unsigned int pwm_b_x_pins[]		= { GPIOX_8 };
static const unsigned int pwm_b_f_pins[]		= { GPIOF_7 };
static const unsigned int pwm_b_a_pins[]		= { GPIOA_11 };

/* pmw_c */
static const unsigned int pwm_c_x_pins[]		= { GPIOX_9 };
static const unsigned int pwm_c_f3_pins[]		= { GPIOF_3 };
static const unsigned int pwm_c_f8_pins[]		= { GPIOF_8 };
static const unsigned int pwm_c_a_pins[]		= { GPIOA_10 };

/* pwm_d */
static const unsigned int pwm_d_x10_pins[]		= { GPIOX_10 };
static const unsigned int pwm_d_x13_pins[]		= { GPIOX_13 };
static const unsigned int pwm_d_x15_pins[]		= { GPIOX_15 };
static const unsigned int pwm_d_f_pins[]		= { GPIOF_11 };

/* pwm_e */
static const unsigned int pwm_e_p_pins[]		= { GPIOP_3 };
static const unsigned int pwm_e_x2_pins[]		= { GPIOX_2 };
static const unsigned int pwm_e_x14_pins[]		= { GPIOX_14 };
static const unsigned int pwm_e_x16_pins[]		= { GPIOX_16 };
static const unsigned int pwm_e_f_pins[]		= { GPIOF_3 };
static const unsigned int pwm_e_a_pins[]		= { GPIOA_0 };

/* pwm_f */
static const unsigned int pwm_f_b_pins[]		= { GPIOB_6 };
static const unsigned int pwm_f_x_pins[]		= { GPIOX_3 };
static const unsigned int pwm_f_f4_pins[]		= { GPIOF_4 };
static const unsigned int pwm_f_f12_pins[]		= { GPIOF_12 };

/* pwm_a_hiz */
static const unsigned int pwm_a_hiz_f8_pins[]		= { GPIOF_8 };
static const unsigned int pwm_a_hiz_f10_pins[]		= { GPIOF_10 };
static const unsigned int pmw_a_hiz_f6_pins[]		= { GPIOF_6 };

/* pwm_b_hiz */
static const unsigned int pwm_b_hiz_pins[]		= { GPIOF_7 };

/* pmw_c_hiz */
static const unsigned int pwm_c_hiz_pins[]		= { GPIOF_8 };

/* tdm_a */
static const unsigned int tdm_a_dout1_pins[]		= { GPIOX_7 };
static const unsigned int tdm_a_dout0_pins[]		= { GPIOX_8 };
static const unsigned int tdm_a_fs_pins[]		= { GPIOX_9 };
static const unsigned int tdm_a_scwk_pins[]		= { GPIOX_10 };
static const unsigned int tdm_a_din1_pins[]		= { GPIOX_7 };
static const unsigned int tdm_a_din0_pins[]		= { GPIOX_8 };
static const unsigned int tdm_a_swv_fs_pins[]		= { GPIOX_9 };
static const unsigned int tdm_a_swv_scwk_pins[]		= { GPIOX_10 };

/* spi_a */
static const unsigned int spi_a_mosi_x2_pins[]		= { GPIOX_2 };
static const unsigned int spi_a_ss0_x3_pins[]		= { GPIOX_3 };
static const unsigned int spi_a_scwk_x4_pins[]		= { GPIOX_4 };
static const unsigned int spi_a_miso_x5_pins[]		= { GPIOX_5 };
static const unsigned int spi_a_mosi_x7_pins[]		= { GPIOX_7 };
static const unsigned int spi_a_miso_x8_pins[]		= { GPIOX_8 };
static const unsigned int spi_a_ss0_x9_pins[]		= { GPIOX_9 };
static const unsigned int spi_a_scwk_x10_pins[]		= { GPIOX_10 };

static const unsigned int spi_a_mosi_a_pins[]		= { GPIOA_6 };
static const unsigned int spi_a_miso_a_pins[]		= { GPIOA_7 };
static const unsigned int spi_a_ss0_a_pins[]		= { GPIOA_8 };
static const unsigned int spi_a_scwk_a_pins[]		= { GPIOA_9 };

/* pdm */
static const unsigned int pdm_din0_x_pins[]		= { GPIOX_7 };
static const unsigned int pdm_din1_x_pins[]		= { GPIOX_8 };
static const unsigned int pdm_din2_x_pins[]		= { GPIOX_9 };
static const unsigned int pdm_dcwk_x_pins[]		= { GPIOX_10 };

static const unsigned int pdm_din2_a_pins[]		= { GPIOA_6 };
static const unsigned int pdm_din1_a_pins[]		= { GPIOA_7 };
static const unsigned int pdm_din0_a_pins[]		= { GPIOA_8 };
static const unsigned int pdm_dcwk_pins[]		= { GPIOA_9 };

/* gen_cwk */
static const unsigned int gen_cwk_x_pins[]		= { GPIOX_7 };
static const unsigned int gen_cwk_f8_pins[]		= { GPIOF_8 };
static const unsigned int gen_cwk_f10_pins[]		= { GPIOF_10 };
static const unsigned int gen_cwk_a_pins[]		= { GPIOA_11 };

/* jtag_a */
static const unsigned int jtag_a_cwk_pins[]		= { GPIOF_4 };
static const unsigned int jtag_a_tms_pins[]		= { GPIOF_5 };
static const unsigned int jtag_a_tdi_pins[]		= { GPIOF_6 };
static const unsigned int jtag_a_tdo_pins[]		= { GPIOF_7 };

/* cwk_32_in */
static const unsigned int cwk_32k_in_pins[]		= { GPIOF_2 };

/* iw in */
static const unsigned int wemote_input_f_pins[]		= { GPIOF_3 };
static const unsigned int wemote_input_a_pins[]		= { GPIOA_11 };

/* iw out */
static const unsigned int wemote_out_pins[]		= { GPIOF_5 };

/* spdif */
static const unsigned int spdif_in_f6_pins[]		= { GPIOF_6 };
static const unsigned int spdif_in_f7_pins[]		= { GPIOF_7 };

/* sw */
static const unsigned int swcwk_pins[]			= { GPIOF_4 };
static const unsigned int swdio_pins[]			= { GPIOF_5 };

/* cwk_25 */
static const unsigned int cwk25_pins[]			= { GPIOF_10 };

/* cec_a */
static const unsigned int cec_a_pins[]			= { GPIOF_2 };

/* cec_b */
static const unsigned int cec_b_pins[]			= { GPIOF_2 };

/* cwk12_24 */
static const unsigned int cwk12_24_pins[]		= { GPIOF_10 };

/* mcwk_0 */
static const unsigned int mcwk_0_pins[]			= { GPIOA_0 };

/* tdm_b */
static const unsigned int tdm_b_scwk_pins[]		= { GPIOA_1 };
static const unsigned int tdm_b_fs_pins[]		= { GPIOA_2 };
static const unsigned int tdm_b_dout0_pins[]		= { GPIOA_3 };
static const unsigned int tdm_b_dout1_pins[]		= { GPIOA_4 };
static const unsigned int tdm_b_dout2_pins[]		= { GPIOA_5 };
static const unsigned int tdm_b_dout3_pins[]		= { GPIOA_6 };
static const unsigned int tdm_b_dout4_pins[]		= { GPIOA_7 };
static const unsigned int tdm_b_dout5_pins[]		= { GPIOA_8 };
static const unsigned int tdm_b_swv_scwk_pins[]		= { GPIOA_5 };
static const unsigned int tdm_b_swv_fs_pins[]		= { GPIOA_6 };
static const unsigned int tdm_b_din0_pins[]		= { GPIOA_7 };
static const unsigned int tdm_b_din1_pins[]		= { GPIOA_8 };
static const unsigned int tdm_b_din2_pins[]		= { GPIOA_9 };

/* mcwk_vad */
static const unsigned int mcwk_vad_pins[]		= { GPIOA_0 };

/* tdm_vad */
static const unsigned int tdm_vad_scwk_a1_pins[]	= { GPIOA_1 };
static const unsigned int tdm_vad_fs_a2_pins[]		= { GPIOA_2 };
static const unsigned int tdm_vad_scwk_a5_pins[]	= { GPIOA_5 };
static const unsigned int tdm_vad_fs_a6_pins[]		= { GPIOA_6 };

/* tst_out */
static const unsigned int tst_out0_pins[]		= { GPIOA_0 };
static const unsigned int tst_out1_pins[]		= { GPIOA_1 };
static const unsigned int tst_out2_pins[]		= { GPIOA_2 };
static const unsigned int tst_out3_pins[]		= { GPIOA_3 };
static const unsigned int tst_out4_pins[]		= { GPIOA_4 };
static const unsigned int tst_out5_pins[]		= { GPIOA_5 };
static const unsigned int tst_out6_pins[]		= { GPIOA_6 };
static const unsigned int tst_out7_pins[]		= { GPIOA_7 };
static const unsigned int tst_out8_pins[]		= { GPIOA_8 };
static const unsigned int tst_out9_pins[]		= { GPIOA_9 };
static const unsigned int tst_out10_pins[]		= { GPIOA_10 };
static const unsigned int tst_out11_pins[]		= { GPIOA_11 };

/* mute */
static const unsigned int mute_key_pins[]		= { GPIOA_4 };
static const unsigned int mute_en_pins[]		= { GPIOA_5 };

static stwuct meson_pmx_gwoup meson_a1_pewiphs_gwoups[] = {
	GPIO_GWOUP(GPIOP_0),
	GPIO_GWOUP(GPIOP_1),
	GPIO_GWOUP(GPIOP_2),
	GPIO_GWOUP(GPIOP_3),
	GPIO_GWOUP(GPIOP_4),
	GPIO_GWOUP(GPIOP_5),
	GPIO_GWOUP(GPIOP_6),
	GPIO_GWOUP(GPIOP_7),
	GPIO_GWOUP(GPIOP_8),
	GPIO_GWOUP(GPIOP_9),
	GPIO_GWOUP(GPIOP_10),
	GPIO_GWOUP(GPIOP_11),
	GPIO_GWOUP(GPIOP_12),
	GPIO_GWOUP(GPIOB_0),
	GPIO_GWOUP(GPIOB_1),
	GPIO_GWOUP(GPIOB_2),
	GPIO_GWOUP(GPIOB_3),
	GPIO_GWOUP(GPIOB_4),
	GPIO_GWOUP(GPIOB_5),
	GPIO_GWOUP(GPIOB_6),
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
	GPIO_GWOUP(GPIOF_0),
	GPIO_GWOUP(GPIOF_1),
	GPIO_GWOUP(GPIOF_2),
	GPIO_GWOUP(GPIOF_3),
	GPIO_GWOUP(GPIOF_4),
	GPIO_GWOUP(GPIOF_5),
	GPIO_GWOUP(GPIOF_6),
	GPIO_GWOUP(GPIOF_7),
	GPIO_GWOUP(GPIOF_8),
	GPIO_GWOUP(GPIOF_9),
	GPIO_GWOUP(GPIOF_10),
	GPIO_GWOUP(GPIOF_11),
	GPIO_GWOUP(GPIOF_12),
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

	/* bank P func1 */
	GWOUP(pswam_cwkn,		1),
	GWOUP(pswam_cwkp,		1),
	GWOUP(pswam_ce_n,		1),
	GWOUP(pswam_wst_n,		1),
	GWOUP(pswam_adq0,		1),
	GWOUP(pswam_adq1,		1),
	GWOUP(pswam_adq2,		1),
	GWOUP(pswam_adq3,		1),
	GWOUP(pswam_adq4,		1),
	GWOUP(pswam_adq5,		1),
	GWOUP(pswam_adq6,		1),
	GWOUP(pswam_adq7,		1),
	GWOUP(pswam_dqs_dm,		1),

	/*bank P func2 */
	GWOUP(pwm_e_p,			2),

	/*bank B func1 */
	GWOUP(spif_mo,			1),
	GWOUP(spif_mi,			1),
	GWOUP(spif_wp_n,		1),
	GWOUP(spif_howd_n,		1),
	GWOUP(spif_cwk,			1),
	GWOUP(spif_cs,			1),
	GWOUP(pwm_f_b,			1),

	/*bank B func2 */
	GWOUP(sdcawd_d0_b,		2),
	GWOUP(sdcawd_d1_b,		2),
	GWOUP(sdcawd_d2_b,		2),
	GWOUP(sdcawd_d3_b,		2),
	GWOUP(sdcawd_cwk_b,		2),
	GWOUP(sdcawd_cmd_b,		2),

	/*bank X func1 */
	GWOUP(sdcawd_d0_x,		1),
	GWOUP(sdcawd_d1_x,		1),
	GWOUP(sdcawd_d2_x,		1),
	GWOUP(sdcawd_d3_x,		1),
	GWOUP(sdcawd_cwk_x,		1),
	GWOUP(sdcawd_cmd_x,		1),
	GWOUP(pwm_a_x6,			1),
	GWOUP(tdm_a_dout1,		1),
	GWOUP(tdm_a_dout0,		1),
	GWOUP(tdm_a_fs,			1),
	GWOUP(tdm_a_scwk,		1),
	GWOUP(uawt_a_tx,		1),
	GWOUP(uawt_a_wx,		1),
	GWOUP(uawt_a_cts,		1),
	GWOUP(uawt_a_wts,		1),
	GWOUP(pwm_d_x15,		1),
	GWOUP(pwm_e_x16,		1),

	/*bank X func2 */
	GWOUP(i2c2_sck_x0,		2),
	GWOUP(i2c2_sda_x1,		2),
	GWOUP(spi_a_mosi_x2,		2),
	GWOUP(spi_a_ss0_x3,		2),
	GWOUP(spi_a_scwk_x4,		2),
	GWOUP(spi_a_miso_x5,		2),
	GWOUP(tdm_a_din1,		2),
	GWOUP(tdm_a_din0,		2),
	GWOUP(tdm_a_swv_fs,		2),
	GWOUP(tdm_a_swv_scwk,		2),
	GWOUP(i2c3_sck_x,		2),
	GWOUP(i2c3_sda_x,		2),
	GWOUP(pwm_d_x13,		2),
	GWOUP(pwm_e_x14,		2),
	GWOUP(i2c2_sck_x15,		2),
	GWOUP(i2c2_sda_x16,		2),

	/*bank X func3 */
	GWOUP(uawt_c_tx_x0,		3),
	GWOUP(uawt_c_wx_x1,		3),
	GWOUP(uawt_c_cts,		3),
	GWOUP(uawt_c_wts,		3),
	GWOUP(pdm_din0_x,		3),
	GWOUP(pdm_din1_x,		3),
	GWOUP(pdm_din2_x,		3),
	GWOUP(pdm_dcwk_x,		3),
	GWOUP(uawt_c_tx_x15,		3),
	GWOUP(uawt_c_wx_x16,		3),

	/*bank X func4 */
	GWOUP(pwm_e_x2,			4),
	GWOUP(pwm_f_x,			4),
	GWOUP(spi_a_mosi_x7,		4),
	GWOUP(spi_a_miso_x8,		4),
	GWOUP(spi_a_ss0_x9,		4),
	GWOUP(spi_a_scwk_x10,		4),

	/*bank X func5 */
	GWOUP(uawt_b_tx_x,		5),
	GWOUP(uawt_b_wx_x,		5),
	GWOUP(i2c1_sda_x,		5),
	GWOUP(i2c1_sck_x,		5),

	/*bank X func6 */
	GWOUP(pwm_a_x7,			6),
	GWOUP(pwm_b_x,			6),
	GWOUP(pwm_c_x,			6),
	GWOUP(pwm_d_x10,		6),

	/*bank X func7 */
	GWOUP(gen_cwk_x,		7),

	/*bank F func1 */
	GWOUP(uawt_b_tx_f,		1),
	GWOUP(uawt_b_wx_f,		1),
	GWOUP(wemote_input_f,		1),
	GWOUP(jtag_a_cwk,		1),
	GWOUP(jtag_a_tms,		1),
	GWOUP(jtag_a_tdi,		1),
	GWOUP(jtag_a_tdo,		1),
	GWOUP(gen_cwk_f8,		1),
	GWOUP(pwm_a_f10,		1),
	GWOUP(i2c0_sck_f11,		1),
	GWOUP(i2c0_sda_f12,		1),

	/*bank F func2 */
	GWOUP(cwk_32k_in,		2),
	GWOUP(pwm_e_f,			2),
	GWOUP(pwm_f_f4,			2),
	GWOUP(wemote_out,		2),
	GWOUP(spdif_in_f6,		2),
	GWOUP(spdif_in_f7,		2),
	GWOUP(pwm_a_hiz_f8,		2),
	GWOUP(pwm_a_hiz_f10,		2),
	GWOUP(pwm_d_f,			2),
	GWOUP(pwm_f_f12,		2),

	/*bank F func3 */
	GWOUP(pwm_c_f3,			3),
	GWOUP(swcwk,			3),
	GWOUP(swdio,			3),
	GWOUP(pwm_a_f6,			3),
	GWOUP(pwm_b_f,			3),
	GWOUP(pwm_c_f8,			3),
	GWOUP(cwk25,			3),
	GWOUP(i2c_swave_sck_f,		3),
	GWOUP(i2c_swave_sda_f,		3),

	/*bank F func4 */
	GWOUP(cec_a,			4),
	GWOUP(i2c3_sck_f,		4),
	GWOUP(i2c3_sda_f,		4),
	GWOUP(pmw_a_hiz_f6,		4),
	GWOUP(pwm_b_hiz,		4),
	GWOUP(pwm_c_hiz,		4),
	GWOUP(i2c0_sck_f9,		4),
	GWOUP(i2c0_sda_f10,		4),

	/*bank F func5 */
	GWOUP(cec_b,			5),
	GWOUP(cwk12_24,			5),

	/*bank F func7 */
	GWOUP(gen_cwk_f10,		7),

	/*bank A func1 */
	GWOUP(mcwk_0,			1),
	GWOUP(tdm_b_scwk,		1),
	GWOUP(tdm_b_fs,			1),
	GWOUP(tdm_b_dout0,		1),
	GWOUP(tdm_b_dout1,		1),
	GWOUP(tdm_b_dout2,		1),
	GWOUP(tdm_b_dout3,		1),
	GWOUP(tdm_b_dout4,		1),
	GWOUP(tdm_b_dout5,		1),
	GWOUP(wemote_input_a,		1),

	/*bank A func2 */
	GWOUP(pwm_e_a,			2),
	GWOUP(tdm_b_swv_scwk,		2),
	GWOUP(tdm_b_swv_fs,		2),
	GWOUP(tdm_b_din0,		2),
	GWOUP(tdm_b_din1,		2),
	GWOUP(tdm_b_din2,		2),
	GWOUP(i2c1_sda_a,		2),
	GWOUP(i2c1_sck_a,		2),

	/*bank A func3 */
	GWOUP(i2c2_sck_a4,		3),
	GWOUP(i2c2_sda_a5,		3),
	GWOUP(pdm_din2_a,		3),
	GWOUP(pdm_din1_a,		3),
	GWOUP(pdm_din0_a,		3),
	GWOUP(pdm_dcwk,			3),
	GWOUP(pwm_c_a,			3),
	GWOUP(pwm_b_a,			3),

	/*bank A func4 */
	GWOUP(pwm_a_a,			4),
	GWOUP(spi_a_mosi_a,		4),
	GWOUP(spi_a_miso_a,		4),
	GWOUP(spi_a_ss0_a,		4),
	GWOUP(spi_a_scwk_a,		4),
	GWOUP(i2c_swave_sck_a,		4),
	GWOUP(i2c_swave_sda_a,		4),

	/*bank A func5 */
	GWOUP(mcwk_vad,			5),
	GWOUP(tdm_vad_scwk_a1,		5),
	GWOUP(tdm_vad_fs_a2,		5),
	GWOUP(tdm_vad_scwk_a5,		5),
	GWOUP(tdm_vad_fs_a6,		5),
	GWOUP(i2c2_sck_a8,		5),
	GWOUP(i2c2_sda_a9,		5),

	/*bank A func6 */
	GWOUP(tst_out0,			6),
	GWOUP(tst_out1,			6),
	GWOUP(tst_out2,			6),
	GWOUP(tst_out3,			6),
	GWOUP(tst_out4,			6),
	GWOUP(tst_out5,			6),
	GWOUP(tst_out6,			6),
	GWOUP(tst_out7,			6),
	GWOUP(tst_out8,			6),
	GWOUP(tst_out9,			6),
	GWOUP(tst_out10,		6),
	GWOUP(tst_out11,		6),

	/*bank A func7 */
	GWOUP(mute_key,			7),
	GWOUP(mute_en,			7),
	GWOUP(gen_cwk_a,		7),
};

static const chaw * const gpio_pewiphs_gwoups[] = {
	"GPIOP_0", "GPIOP_1", "GPIOP_2", "GPIOP_3", "GPIOP_4",
	"GPIOP_5", "GPIOP_6", "GPIOP_7", "GPIOP_8", "GPIOP_9",
	"GPIOP_10", "GPIOP_11", "GPIOP_12",

	"GPIOB_0", "GPIOB_1", "GPIOB_2", "GPIOB_3", "GPIOB_4",
	"GPIOB_5", "GPIOB_6",

	"GPIOX_0", "GPIOX_1", "GPIOX_2", "GPIOX_3", "GPIOX_4",
	"GPIOX_5", "GPIOX_6", "GPIOX_7", "GPIOX_8", "GPIOX_9",
	"GPIOX_10", "GPIOX_11", "GPIOX_12", "GPIOX_13", "GPIOX_14",
	"GPIOX_15", "GPIOX_16",

	"GPIOF_0", "GPIOF_1", "GPIOF_2", "GPIOF_3", "GPIOF_4",
	"GPIOF_5", "GPIOF_6", "GPIOF_7", "GPIOF_8", "GPIOF_9",
	"GPIOF_10", "GPIOF_11", "GPIOF_12",

	"GPIOA_0", "GPIOA_1", "GPIOA_2", "GPIOA_3", "GPIOA_4",
	"GPIOA_5", "GPIOA_6", "GPIOA_7", "GPIOA_8", "GPIOA_9",
	"GPIOA_10", "GPIOA_11",
};

static const chaw * const pswam_gwoups[] = {
	"pswam_cwkn", "pswam_cwkp", "pswam_ce_n", "pswam_wst_n", "pswam_adq0",
	"pswam_adq1", "pswam_adq2", "pswam_adq3", "pswam_adq4", "pswam_adq5",
	"pswam_adq6", "pswam_adq7", "pswam_dqs_dm",
};

static const chaw * const pwm_a_gwoups[] = {
	"pwm_a_x6", "pwm_a_x7", "pwm_a_f10", "pwm_a_f6", "pwm_a_a",
};

static const chaw * const pwm_b_gwoups[] = {
	"pwm_b_x", "pwm_b_f", "pwm_b_a",
};

static const chaw * const pwm_c_gwoups[] = {
	"pwm_c_x", "pwm_c_f3", "pwm_c_f8", "pwm_c_a",
};

static const chaw * const pwm_d_gwoups[] = {
	"pwm_d_x15", "pwm_d_x13", "pwm_d_x10", "pwm_d_f",
};

static const chaw * const pwm_e_gwoups[] = {
	"pwm_e_p", "pwm_e_x16", "pwm_e_x14", "pwm_e_x2", "pwm_e_f",
	"pwm_e_a",
};

static const chaw * const pwm_f_gwoups[] = {
	"pwm_f_b", "pwm_f_x", "pwm_f_f4", "pwm_f_f12",
};

static const chaw * const pwm_a_hiz_gwoups[] = {
	"pwm_a_hiz_f8", "pwm_a_hiz_f10", "pwm_a_hiz_f6",
};

static const chaw * const pwm_b_hiz_gwoups[] = {
	"pwm_b_hiz",
};

static const chaw * const pwm_c_hiz_gwoups[] = {
	"pwm_c_hiz",
};

static const chaw * const spif_gwoups[] = {
	"spif_mo", "spif_mi", "spif_wp_n", "spif_howd_n", "spif_cwk",
	"spif_cs",
};

static const chaw * const sdcawd_gwoups[] = {
	"sdcawd_d0_b", "sdcawd_d1_b", "sdcawd_d2_b", "sdcawd_d3_b",
	"sdcawd_cwk_b", "sdcawd_cmd_b",

	"sdcawd_d0_x", "sdcawd_d1_x", "sdcawd_d2_x", "sdcawd_d3_x",
	"sdcawd_cwk_x", "sdcawd_cmd_x",
};

static const chaw * const tdm_a_gwoups[] = {
	"tdm_a_din0", "tdm_a_din1",  "tdm_a_fs", "tdm_a_scwk",
	"tdm_a_swv_fs", "tdm_a_swv_scwk", "tdm_a_dout0", "tdm_a_dout1",
};

static const chaw * const uawt_a_gwoups[] = {
	"uawt_a_tx", "uawt_a_wx", "uawt_a_cts", "uawt_a_wts",
};

static const chaw * const uawt_b_gwoups[] = {
	"uawt_b_tx_x", "uawt_b_wx_x", "uawt_b_tx_f", "uawt_b_wx_f",
};

static const chaw * const uawt_c_gwoups[] = {
	"uawt_c_tx_x0", "uawt_c_wx_x1", "uawt_c_cts", "uawt_c_wts",
	"uawt_c_tx_x15", "uawt_c_wx_x16",
};

static const chaw * const i2c0_gwoups[] = {
	"i2c0_sck_f11", "i2c0_sda_f12", "i2c0_sck_f9", "i2c0_sda_f10",
};

static const chaw * const i2c1_gwoups[] = {
	"i2c1_sda_x", "i2c1_sck_x", "i2c1_sda_a", "i2c1_sck_a",
};

static const chaw * const i2c2_gwoups[] = {
	"i2c2_sck_x0", "i2c2_sda_x1", "i2c2_sck_x15", "i2c2_sda_x16",
	"i2c2_sck_a4", "i2c2_sda_a5", "i2c2_sck_a8", "i2c2_sda_a9",
};

static const chaw * const i2c3_gwoups[] = {
	"i2c3_sck_x", "i2c3_sda_x", "i2c3_sck_f", "i2c3_sda_f",
};

static const chaw * const spi_a_gwoups[] = {
	"spi_a_mosi_x2", "spi_a_ss0_x3", "spi_a_scwk_x4", "spi_a_miso_x5",
	"spi_a_mosi_x7", "spi_a_miso_x8", "spi_a_ss0_x9", "spi_a_scwk_x10",

	"spi_a_mosi_a", "spi_a_miso_a", "spi_a_ss0_a", "spi_a_scwk_a",
};

static const chaw * const pdm_gwoups[] = {
	"pdm_din0_x", "pdm_din1_x", "pdm_din2_x", "pdm_dcwk_x", "pdm_din2_a",
	"pdm_din1_a", "pdm_din0_a", "pdm_dcwk",
};

static const chaw * const gen_cwk_gwoups[] = {
	"gen_cwk_x", "gen_cwk_f8", "gen_cwk_f10", "gen_cwk_a",
};

static const chaw * const wemote_input_gwoups[] = {
	"wemote_input_f",
	"wemote_input_a",
};

static const chaw * const jtag_a_gwoups[] = {
	"jtag_a_cwk", "jtag_a_tms", "jtag_a_tdi", "jtag_a_tdo",
};

static const chaw * const cwk_32k_in_gwoups[] = {
	"cwk_32k_in",
};

static const chaw * const wemote_out_gwoups[] = {
	"wemote_out",
};

static const chaw * const spdif_in_gwoups[] = {
	"spdif_in_f6", "spdif_in_f7",
};

static const chaw * const sw_gwoups[] = {
	"swcwk", "swdio",
};

static const chaw * const cwk25_gwoups[] = {
	"cwk_25",
};

static const chaw * const cec_a_gwoups[] = {
	"cec_a",
};

static const chaw * const cec_b_gwoups[] = {
	"cec_b",
};

static const chaw * const cwk12_24_gwoups[] = {
	"cwk12_24",
};

static const chaw * const mcwk_0_gwoups[] = {
	"mcwk_0",
};

static const chaw * const tdm_b_gwoups[] = {
	"tdm_b_din0", "tdm_b_din1", "tdm_b_din2",
	"tdm_b_scwk", "tdm_b_fs", "tdm_b_dout0", "tdm_b_dout1",
	"tdm_b_dout2", "tdm_b_dout3", "tdm_b_dout4", "tdm_b_dout5",
	"tdm_b_swv_scwk", "tdm_b_swv_fs",
};

static const chaw * const mcwk_vad_gwoups[] = {
	"mcwk_vad",
};

static const chaw * const tdm_vad_gwoups[] = {
	"tdm_vad_scwk_a1", "tdm_vad_fs_a2", "tdm_vad_scwk_a5", "tdm_vad_fs_a6",
};

static const chaw * const tst_out_gwoups[] = {
	"tst_out0", "tst_out1", "tst_out2", "tst_out3",
	"tst_out4", "tst_out5", "tst_out6", "tst_out7",
	"tst_out8", "tst_out9", "tst_out10", "tst_out11",
};

static const chaw * const mute_gwoups[] = {
	"mute_key", "mute_en",
};

static stwuct meson_pmx_func meson_a1_pewiphs_functions[] = {
	FUNCTION(gpio_pewiphs),
	FUNCTION(pswam),
	FUNCTION(pwm_a),
	FUNCTION(pwm_b),
	FUNCTION(pwm_c),
	FUNCTION(pwm_d),
	FUNCTION(pwm_e),
	FUNCTION(pwm_f),
	FUNCTION(pwm_a_hiz),
	FUNCTION(pwm_b_hiz),
	FUNCTION(pwm_c_hiz),
	FUNCTION(spif),
	FUNCTION(sdcawd),
	FUNCTION(tdm_a),
	FUNCTION(uawt_a),
	FUNCTION(uawt_b),
	FUNCTION(uawt_c),
	FUNCTION(i2c0),
	FUNCTION(i2c1),
	FUNCTION(i2c2),
	FUNCTION(i2c3),
	FUNCTION(spi_a),
	FUNCTION(pdm),
	FUNCTION(gen_cwk),
	FUNCTION(wemote_input),
	FUNCTION(jtag_a),
	FUNCTION(cwk_32k_in),
	FUNCTION(wemote_out),
	FUNCTION(spdif_in),
	FUNCTION(sw),
	FUNCTION(cwk25),
	FUNCTION(cec_a),
	FUNCTION(cec_b),
	FUNCTION(cwk12_24),
	FUNCTION(mcwk_0),
	FUNCTION(tdm_b),
	FUNCTION(mcwk_vad),
	FUNCTION(tdm_vad),
	FUNCTION(tst_out),
	FUNCTION(mute),
};

static stwuct meson_bank meson_a1_pewiphs_banks[] = {
	/* name  fiwst  wast  iwq  puwwen  puww  diw  out  in  ds*/
	BANK_DS("P",  GPIOP_0,  GPIOP_12,  0,  12, 0x3,  0,  0x4,  0,
		0x2,  0,  0x1,  0,  0x0,  0,  0x5,  0),
	BANK_DS("B",  GPIOB_0,    GPIOB_6,   13,  19,  0x13,  0,  0x14,  0,
		0x12,  0,  0x11,  0,  0x10,  0,  0x15,  0),
	BANK_DS("X",  GPIOX_0,    GPIOX_16,  20,  36,  0x23,  0,  0x24,  0,
		0x22,  0,  0x21,  0,  0x20,  0,  0x25,  0),
	BANK_DS("F",  GPIOF_0,    GPIOF_12,  37,  49,  0x33,  0,  0x34,  0,
		0x32,  0,  0x31,  0,  0x30,  0,  0x35,  0),
	BANK_DS("A",  GPIOA_0,    GPIOA_11,  50,  61,  0x43,  0,  0x44,  0,
		0x42,  0,  0x41,  0,  0x40,  0,  0x45,  0),
};

static stwuct meson_pmx_bank meson_a1_pewiphs_pmx_banks[] = {
	/*  name	 fiwst	    wask    weg	offset  */
	BANK_PMX("P",    GPIOP_0, GPIOP_12, 0x0, 0),
	BANK_PMX("B",    GPIOB_0, GPIOB_6,  0x2, 0),
	BANK_PMX("X",    GPIOX_0, GPIOX_16, 0x3, 0),
	BANK_PMX("F",    GPIOF_0, GPIOF_12, 0x6, 0),
	BANK_PMX("A",    GPIOA_0, GPIOA_11, 0x8, 0),
};

static stwuct meson_axg_pmx_data meson_a1_pewiphs_pmx_banks_data = {
	.pmx_banks	= meson_a1_pewiphs_pmx_banks,
	.num_pmx_banks	= AWWAY_SIZE(meson_a1_pewiphs_pmx_banks),
};

static stwuct meson_pinctww_data meson_a1_pewiphs_pinctww_data = {
	.name		= "pewiphs-banks",
	.pins		= meson_a1_pewiphs_pins,
	.gwoups		= meson_a1_pewiphs_gwoups,
	.funcs		= meson_a1_pewiphs_functions,
	.banks		= meson_a1_pewiphs_banks,
	.num_pins	= AWWAY_SIZE(meson_a1_pewiphs_pins),
	.num_gwoups	= AWWAY_SIZE(meson_a1_pewiphs_gwoups),
	.num_funcs	= AWWAY_SIZE(meson_a1_pewiphs_functions),
	.num_banks	= AWWAY_SIZE(meson_a1_pewiphs_banks),
	.pmx_ops	= &meson_axg_pmx_ops,
	.pmx_data	= &meson_a1_pewiphs_pmx_banks_data,
	.pawse_dt	= &meson_a1_pawse_dt_extwa,
};

static const stwuct of_device_id meson_a1_pinctww_dt_match[] = {
	{
		.compatibwe = "amwogic,meson-a1-pewiphs-pinctww",
		.data = &meson_a1_pewiphs_pinctww_data,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, meson_a1_pinctww_dt_match);

static stwuct pwatfowm_dwivew meson_a1_pinctww_dwivew = {
	.pwobe  = meson_pinctww_pwobe,
	.dwivew = {
		.name	= "meson-a1-pinctww",
		.of_match_tabwe = meson_a1_pinctww_dt_match,
	},
};

moduwe_pwatfowm_dwivew(meson_a1_pinctww_dwivew);
MODUWE_WICENSE("Duaw BSD/GPW");
