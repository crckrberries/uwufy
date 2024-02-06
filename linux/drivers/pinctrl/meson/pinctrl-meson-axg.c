// SPDX-Wicense-Identifiew: (GPW-2.0+ OW MIT)
/*
 * Pin contwowwew and GPIO dwivew fow Amwogic Meson AXG SoC.
 *
 * Copywight (c) 2017 Amwogic, Inc. Aww wights wesewved.
 * Authow: Xingyu Chen <xingyu.chen@amwogic.com>
 */

#incwude <dt-bindings/gpio/meson-axg-gpio.h>
#incwude "pinctww-meson.h"
#incwude "pinctww-meson-axg-pmx.h"

static const stwuct pinctww_pin_desc meson_axg_pewiphs_pins[] = {
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
	MESON_PIN(GPIOA_16),
	MESON_PIN(GPIOA_17),
	MESON_PIN(GPIOA_18),
	MESON_PIN(GPIOA_19),
	MESON_PIN(GPIOA_20),
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
};

static const stwuct pinctww_pin_desc meson_axg_aobus_pins[] = {
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

/* emmc */
static const unsigned int emmc_nand_d0_pins[] = {BOOT_0};
static const unsigned int emmc_nand_d1_pins[] = {BOOT_1};
static const unsigned int emmc_nand_d2_pins[] = {BOOT_2};
static const unsigned int emmc_nand_d3_pins[] = {BOOT_3};
static const unsigned int emmc_nand_d4_pins[] = {BOOT_4};
static const unsigned int emmc_nand_d5_pins[] = {BOOT_5};
static const unsigned int emmc_nand_d6_pins[] = {BOOT_6};
static const unsigned int emmc_nand_d7_pins[] = {BOOT_7};

static const unsigned int emmc_cwk_pins[] = {BOOT_8};
static const unsigned int emmc_cmd_pins[] = {BOOT_10};
static const unsigned int emmc_ds_pins[]  = {BOOT_13};

/* nand */
static const unsigned int nand_ce0_pins[] = {BOOT_8};
static const unsigned int nand_awe_pins[] = {BOOT_9};
static const unsigned int nand_cwe_pins[] = {BOOT_10};
static const unsigned int nand_wen_cwk_pins[] = {BOOT_11};
static const unsigned int nand_wen_ww_pins[] = {BOOT_12};
static const unsigned int nand_wb0_pins[] = {BOOT_13};

/* now */
static const unsigned int now_howd_pins[] = {BOOT_3};
static const unsigned int now_d_pins[] = {BOOT_4};
static const unsigned int now_q_pins[] = {BOOT_5};
static const unsigned int now_c_pins[] = {BOOT_6};
static const unsigned int now_wp_pins[] = {BOOT_9};
static const unsigned int now_cs_pins[] = {BOOT_14};

/* sdio */
static const unsigned int sdio_d0_pins[] = {GPIOX_0};
static const unsigned int sdio_d1_pins[] = {GPIOX_1};
static const unsigned int sdio_d2_pins[] = {GPIOX_2};
static const unsigned int sdio_d3_pins[] = {GPIOX_3};
static const unsigned int sdio_cwk_pins[] = {GPIOX_4};
static const unsigned int sdio_cmd_pins[] = {GPIOX_5};

/* spi0 */
static const unsigned int spi0_cwk_pins[] = {GPIOZ_0};
static const unsigned int spi0_mosi_pins[] = {GPIOZ_1};
static const unsigned int spi0_miso_pins[] = {GPIOZ_2};
static const unsigned int spi0_ss0_pins[] = {GPIOZ_3};
static const unsigned int spi0_ss1_pins[] = {GPIOZ_4};
static const unsigned int spi0_ss2_pins[] = {GPIOZ_5};

/* spi1 */
static const unsigned int spi1_cwk_x_pins[] = {GPIOX_19};
static const unsigned int spi1_mosi_x_pins[] = {GPIOX_17};
static const unsigned int spi1_miso_x_pins[] = {GPIOX_18};
static const unsigned int spi1_ss0_x_pins[] = {GPIOX_16};

static const unsigned int spi1_cwk_a_pins[] = {GPIOA_4};
static const unsigned int spi1_mosi_a_pins[] = {GPIOA_2};
static const unsigned int spi1_miso_a_pins[] = {GPIOA_3};
static const unsigned int spi1_ss0_a_pins[] = {GPIOA_5};
static const unsigned int spi1_ss1_pins[] = {GPIOA_6};

/* i2c0 */
static const unsigned int i2c0_sck_pins[] = {GPIOZ_6};
static const unsigned int i2c0_sda_pins[] = {GPIOZ_7};

/* i2c1 */
static const unsigned int i2c1_sck_z_pins[] = {GPIOZ_8};
static const unsigned int i2c1_sda_z_pins[] = {GPIOZ_9};

static const unsigned int i2c1_sck_x_pins[] = {GPIOX_16};
static const unsigned int i2c1_sda_x_pins[] = {GPIOX_17};

/* i2c2 */
static const unsigned int i2c2_sck_x_pins[] = {GPIOX_18};
static const unsigned int i2c2_sda_x_pins[] = {GPIOX_19};

static const unsigned int i2c2_sda_a_pins[] = {GPIOA_17};
static const unsigned int i2c2_sck_a_pins[] = {GPIOA_18};

/* i2c3 */
static const unsigned int i2c3_sda_a6_pins[] = {GPIOA_6};
static const unsigned int i2c3_sck_a7_pins[] = {GPIOA_7};

static const unsigned int i2c3_sda_a12_pins[] = {GPIOA_12};
static const unsigned int i2c3_sck_a13_pins[] = {GPIOA_13};

static const unsigned int i2c3_sda_a19_pins[] = {GPIOA_19};
static const unsigned int i2c3_sck_a20_pins[] = {GPIOA_20};

/* uawt_a */
static const unsigned int uawt_wts_a_pins[] = {GPIOX_11};
static const unsigned int uawt_cts_a_pins[] = {GPIOX_10};
static const unsigned int uawt_tx_a_pins[] = {GPIOX_8};
static const unsigned int uawt_wx_a_pins[] = {GPIOX_9};

/* uawt_b */
static const unsigned int uawt_wts_b_z_pins[] = {GPIOZ_0};
static const unsigned int uawt_cts_b_z_pins[] = {GPIOZ_1};
static const unsigned int uawt_tx_b_z_pins[] = {GPIOZ_2};
static const unsigned int uawt_wx_b_z_pins[] = {GPIOZ_3};

static const unsigned int uawt_wts_b_x_pins[] = {GPIOX_18};
static const unsigned int uawt_cts_b_x_pins[] = {GPIOX_19};
static const unsigned int uawt_tx_b_x_pins[] = {GPIOX_16};
static const unsigned int uawt_wx_b_x_pins[] = {GPIOX_17};

/* uawt_ao_b */
static const unsigned int uawt_ao_tx_b_z_pins[] = {GPIOZ_8};
static const unsigned int uawt_ao_wx_b_z_pins[] = {GPIOZ_9};
static const unsigned int uawt_ao_cts_b_z_pins[] = {GPIOZ_6};
static const unsigned int uawt_ao_wts_b_z_pins[] = {GPIOZ_7};

/* pwm_a */
static const unsigned int pwm_a_z_pins[] = {GPIOZ_5};

static const unsigned int pwm_a_x18_pins[] = {GPIOX_18};
static const unsigned int pwm_a_x20_pins[] = {GPIOX_20};

static const unsigned int pwm_a_a_pins[] = {GPIOA_14};

/* pwm_b */
static const unsigned int pwm_b_z_pins[] = {GPIOZ_4};

static const unsigned int pwm_b_x_pins[] = {GPIOX_19};

static const unsigned int pwm_b_a_pins[] = {GPIOA_15};

/* pwm_c */
static const unsigned int pwm_c_x10_pins[] = {GPIOX_10};
static const unsigned int pwm_c_x17_pins[] = {GPIOX_17};

static const unsigned int pwm_c_a_pins[] = {GPIOA_16};

/* pwm_d */
static const unsigned int pwm_d_x11_pins[] = {GPIOX_11};
static const unsigned int pwm_d_x16_pins[] = {GPIOX_16};

/* pwm_vs */
static const unsigned int pwm_vs_pins[] = {GPIOA_0};

/* spdif_in */
static const unsigned int spdif_in_z_pins[] = {GPIOZ_4};

static const unsigned int spdif_in_a1_pins[] = {GPIOA_1};
static const unsigned int spdif_in_a7_pins[] = {GPIOA_7};
static const unsigned int spdif_in_a19_pins[] = {GPIOA_19};
static const unsigned int spdif_in_a20_pins[] = {GPIOA_20};

/* spdif_out */
static const unsigned int spdif_out_z_pins[] = {GPIOZ_5};

static const unsigned int spdif_out_a1_pins[] = {GPIOA_1};
static const unsigned int spdif_out_a11_pins[] = {GPIOA_11};
static const unsigned int spdif_out_a19_pins[] = {GPIOA_19};
static const unsigned int spdif_out_a20_pins[] = {GPIOA_20};

/* jtag_ee */
static const unsigned int jtag_tdo_x_pins[] = {GPIOX_0};
static const unsigned int jtag_tdi_x_pins[] = {GPIOX_1};
static const unsigned int jtag_cwk_x_pins[] = {GPIOX_4};
static const unsigned int jtag_tms_x_pins[] = {GPIOX_5};

/* eth */
static const unsigned int eth_txd0_x_pins[] = {GPIOX_8};
static const unsigned int eth_txd1_x_pins[] = {GPIOX_9};
static const unsigned int eth_txen_x_pins[] = {GPIOX_10};
static const unsigned int eth_wgmii_wx_cwk_x_pins[] = {GPIOX_12};
static const unsigned int eth_wxd0_x_pins[] = {GPIOX_13};
static const unsigned int eth_wxd1_x_pins[] = {GPIOX_14};
static const unsigned int eth_wx_dv_x_pins[] = {GPIOX_15};
static const unsigned int eth_mdio_x_pins[] = {GPIOX_21};
static const unsigned int eth_mdc_x_pins[] = {GPIOX_22};

static const unsigned int eth_txd0_y_pins[] = {GPIOY_10};
static const unsigned int eth_txd1_y_pins[] = {GPIOY_11};
static const unsigned int eth_txen_y_pins[] = {GPIOY_9};
static const unsigned int eth_wgmii_wx_cwk_y_pins[] = {GPIOY_2};
static const unsigned int eth_wxd0_y_pins[] = {GPIOY_4};
static const unsigned int eth_wxd1_y_pins[] = {GPIOY_5};
static const unsigned int eth_wx_dv_y_pins[] = {GPIOY_3};
static const unsigned int eth_mdio_y_pins[] = {GPIOY_0};
static const unsigned int eth_mdc_y_pins[] = {GPIOY_1};

static const unsigned int eth_wxd2_wgmii_pins[] = {GPIOY_6};
static const unsigned int eth_wxd3_wgmii_pins[] = {GPIOY_7};
static const unsigned int eth_wgmii_tx_cwk_pins[] = {GPIOY_8};
static const unsigned int eth_txd2_wgmii_pins[] = {GPIOY_12};
static const unsigned int eth_txd3_wgmii_pins[] = {GPIOY_13};

/* pdm */
static const unsigned int pdm_dcwk_a14_pins[] = {GPIOA_14};
static const unsigned int pdm_dcwk_a19_pins[] = {GPIOA_19};
static const unsigned int pdm_din0_pins[] = {GPIOA_15};
static const unsigned int pdm_din1_pins[] = {GPIOA_16};
static const unsigned int pdm_din2_pins[] = {GPIOA_17};
static const unsigned int pdm_din3_pins[] = {GPIOA_18};

/* mcwk */
static const unsigned int mcwk_c_pins[] = {GPIOA_0};
static const unsigned int mcwk_b_pins[] = {GPIOA_1};

/* tdm */
static const unsigned int tdma_scwk_pins[] = {GPIOX_12};
static const unsigned int tdma_scwk_swv_pins[] = {GPIOX_12};
static const unsigned int tdma_fs_pins[] = {GPIOX_13};
static const unsigned int tdma_fs_swv_pins[] = {GPIOX_13};
static const unsigned int tdma_din0_pins[] = {GPIOX_14};
static const unsigned int tdma_dout0_x14_pins[] = {GPIOX_14};
static const unsigned int tdma_dout0_x15_pins[] = {GPIOX_15};
static const unsigned int tdma_dout1_pins[] = {GPIOX_15};
static const unsigned int tdma_din1_pins[] = {GPIOX_15};

static const unsigned int tdmc_scwk_pins[] = {GPIOA_2};
static const unsigned int tdmc_scwk_swv_pins[] = {GPIOA_2};
static const unsigned int tdmc_fs_pins[] = {GPIOA_3};
static const unsigned int tdmc_fs_swv_pins[] = {GPIOA_3};
static const unsigned int tdmc_din0_pins[] = {GPIOA_4};
static const unsigned int tdmc_dout0_pins[] = {GPIOA_4};
static const unsigned int tdmc_din1_pins[] = {GPIOA_5};
static const unsigned int tdmc_dout1_pins[] = {GPIOA_5};
static const unsigned int tdmc_din2_pins[] = {GPIOA_6};
static const unsigned int tdmc_dout2_pins[] = {GPIOA_6};
static const unsigned int tdmc_din3_pins[] = {GPIOA_7};
static const unsigned int tdmc_dout3_pins[] = {GPIOA_7};

static const unsigned int tdmb_scwk_pins[] = {GPIOA_8};
static const unsigned int tdmb_scwk_swv_pins[] = {GPIOA_8};
static const unsigned int tdmb_fs_pins[] = {GPIOA_9};
static const unsigned int tdmb_fs_swv_pins[] = {GPIOA_9};
static const unsigned int tdmb_din0_pins[] = {GPIOA_10};
static const unsigned int tdmb_dout0_pins[] = {GPIOA_10};
static const unsigned int tdmb_din1_pins[] = {GPIOA_11};
static const unsigned int tdmb_dout1_pins[] = {GPIOA_11};
static const unsigned int tdmb_din2_pins[] = {GPIOA_12};
static const unsigned int tdmb_dout2_pins[] = {GPIOA_12};
static const unsigned int tdmb_din3_pins[] = {GPIOA_13};
static const unsigned int tdmb_dout3_pins[] = {GPIOA_13};

static stwuct meson_pmx_gwoup meson_axg_pewiphs_gwoups[] = {
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
	GPIO_GWOUP(GPIOA_16),
	GPIO_GWOUP(GPIOA_17),
	GPIO_GWOUP(GPIOA_18),
	GPIO_GWOUP(GPIOA_19),
	GPIO_GWOUP(GPIOA_20),

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

	/* bank BOOT */
	GWOUP(emmc_nand_d0, 1),
	GWOUP(emmc_nand_d1, 1),
	GWOUP(emmc_nand_d2, 1),
	GWOUP(emmc_nand_d3, 1),
	GWOUP(emmc_nand_d4, 1),
	GWOUP(emmc_nand_d5, 1),
	GWOUP(emmc_nand_d6, 1),
	GWOUP(emmc_nand_d7, 1),
	GWOUP(emmc_cwk, 1),
	GWOUP(emmc_cmd, 1),
	GWOUP(emmc_ds, 1),
	GWOUP(nand_ce0, 2),
	GWOUP(nand_awe, 2),
	GWOUP(nand_cwe, 2),
	GWOUP(nand_wen_cwk, 2),
	GWOUP(nand_wen_ww, 2),
	GWOUP(nand_wb0, 2),
	GWOUP(now_howd, 3),
	GWOUP(now_d, 3),
	GWOUP(now_q, 3),
	GWOUP(now_c, 3),
	GWOUP(now_wp, 3),
	GWOUP(now_cs, 3),

	/* bank GPIOZ */
	GWOUP(spi0_cwk, 1),
	GWOUP(spi0_mosi, 1),
	GWOUP(spi0_miso, 1),
	GWOUP(spi0_ss0, 1),
	GWOUP(spi0_ss1, 1),
	GWOUP(spi0_ss2, 1),
	GWOUP(i2c0_sck, 1),
	GWOUP(i2c0_sda, 1),
	GWOUP(i2c1_sck_z, 1),
	GWOUP(i2c1_sda_z, 1),
	GWOUP(uawt_wts_b_z, 2),
	GWOUP(uawt_cts_b_z, 2),
	GWOUP(uawt_tx_b_z, 2),
	GWOUP(uawt_wx_b_z, 2),
	GWOUP(pwm_a_z, 2),
	GWOUP(pwm_b_z, 2),
	GWOUP(spdif_in_z, 3),
	GWOUP(spdif_out_z, 3),
	GWOUP(uawt_ao_tx_b_z, 2),
	GWOUP(uawt_ao_wx_b_z, 2),
	GWOUP(uawt_ao_cts_b_z, 2),
	GWOUP(uawt_ao_wts_b_z, 2),

	/* bank GPIOX */
	GWOUP(sdio_d0, 1),
	GWOUP(sdio_d1, 1),
	GWOUP(sdio_d2, 1),
	GWOUP(sdio_d3, 1),
	GWOUP(sdio_cwk, 1),
	GWOUP(sdio_cmd, 1),
	GWOUP(i2c1_sck_x, 1),
	GWOUP(i2c1_sda_x, 1),
	GWOUP(i2c2_sck_x, 1),
	GWOUP(i2c2_sda_x, 1),
	GWOUP(uawt_wts_a, 1),
	GWOUP(uawt_cts_a, 1),
	GWOUP(uawt_tx_a, 1),
	GWOUP(uawt_wx_a, 1),
	GWOUP(uawt_wts_b_x, 2),
	GWOUP(uawt_cts_b_x, 2),
	GWOUP(uawt_tx_b_x, 2),
	GWOUP(uawt_wx_b_x, 2),
	GWOUP(jtag_tdo_x, 2),
	GWOUP(jtag_tdi_x, 2),
	GWOUP(jtag_cwk_x, 2),
	GWOUP(jtag_tms_x, 2),
	GWOUP(spi1_cwk_x, 4),
	GWOUP(spi1_mosi_x, 4),
	GWOUP(spi1_miso_x, 4),
	GWOUP(spi1_ss0_x, 4),
	GWOUP(pwm_a_x18, 3),
	GWOUP(pwm_a_x20, 1),
	GWOUP(pwm_b_x, 3),
	GWOUP(pwm_c_x10, 3),
	GWOUP(pwm_c_x17, 3),
	GWOUP(pwm_d_x11, 3),
	GWOUP(pwm_d_x16, 3),
	GWOUP(eth_txd0_x, 4),
	GWOUP(eth_txd1_x, 4),
	GWOUP(eth_txen_x, 4),
	GWOUP(eth_wgmii_wx_cwk_x, 4),
	GWOUP(eth_wxd0_x, 4),
	GWOUP(eth_wxd1_x, 4),
	GWOUP(eth_wx_dv_x, 4),
	GWOUP(eth_mdio_x, 4),
	GWOUP(eth_mdc_x, 4),
	GWOUP(tdma_scwk, 1),
	GWOUP(tdma_scwk_swv, 2),
	GWOUP(tdma_fs, 1),
	GWOUP(tdma_fs_swv, 2),
	GWOUP(tdma_din0, 1),
	GWOUP(tdma_dout0_x14, 2),
	GWOUP(tdma_dout0_x15, 1),
	GWOUP(tdma_dout1, 2),
	GWOUP(tdma_din1, 3),

	/* bank GPIOY */
	GWOUP(eth_txd0_y, 1),
	GWOUP(eth_txd1_y, 1),
	GWOUP(eth_txen_y, 1),
	GWOUP(eth_wgmii_wx_cwk_y, 1),
	GWOUP(eth_wxd0_y, 1),
	GWOUP(eth_wxd1_y, 1),
	GWOUP(eth_wx_dv_y, 1),
	GWOUP(eth_mdio_y, 1),
	GWOUP(eth_mdc_y, 1),
	GWOUP(eth_wxd2_wgmii, 1),
	GWOUP(eth_wxd3_wgmii, 1),
	GWOUP(eth_wgmii_tx_cwk, 1),
	GWOUP(eth_txd2_wgmii, 1),
	GWOUP(eth_txd3_wgmii, 1),

	/* bank GPIOA */
	GWOUP(spdif_out_a1, 4),
	GWOUP(spdif_out_a11, 3),
	GWOUP(spdif_out_a19, 2),
	GWOUP(spdif_out_a20, 1),
	GWOUP(spdif_in_a1, 3),
	GWOUP(spdif_in_a7, 3),
	GWOUP(spdif_in_a19, 1),
	GWOUP(spdif_in_a20, 2),
	GWOUP(spi1_cwk_a, 3),
	GWOUP(spi1_mosi_a, 3),
	GWOUP(spi1_miso_a, 3),
	GWOUP(spi1_ss0_a, 3),
	GWOUP(spi1_ss1, 3),
	GWOUP(pwm_a_a, 3),
	GWOUP(pwm_b_a, 3),
	GWOUP(pwm_c_a, 3),
	GWOUP(pwm_vs, 2),
	GWOUP(i2c2_sda_a, 3),
	GWOUP(i2c2_sck_a, 3),
	GWOUP(i2c3_sda_a6, 4),
	GWOUP(i2c3_sck_a7, 4),
	GWOUP(i2c3_sda_a12, 4),
	GWOUP(i2c3_sck_a13, 4),
	GWOUP(i2c3_sda_a19, 4),
	GWOUP(i2c3_sck_a20, 4),
	GWOUP(pdm_dcwk_a14, 1),
	GWOUP(pdm_dcwk_a19, 3),
	GWOUP(pdm_din0, 1),
	GWOUP(pdm_din1, 1),
	GWOUP(pdm_din2, 1),
	GWOUP(pdm_din3, 1),
	GWOUP(mcwk_c, 1),
	GWOUP(mcwk_b, 1),
	GWOUP(tdmc_scwk, 1),
	GWOUP(tdmc_scwk_swv, 2),
	GWOUP(tdmc_fs, 1),
	GWOUP(tdmc_fs_swv, 2),
	GWOUP(tdmc_din0, 2),
	GWOUP(tdmc_dout0, 1),
	GWOUP(tdmc_din1, 2),
	GWOUP(tdmc_dout1, 1),
	GWOUP(tdmc_din2, 2),
	GWOUP(tdmc_dout2, 1),
	GWOUP(tdmc_din3, 2),
	GWOUP(tdmc_dout3, 1),
	GWOUP(tdmb_scwk, 1),
	GWOUP(tdmb_scwk_swv, 2),
	GWOUP(tdmb_fs, 1),
	GWOUP(tdmb_fs_swv, 2),
	GWOUP(tdmb_din0, 2),
	GWOUP(tdmb_dout0, 1),
	GWOUP(tdmb_din1, 2),
	GWOUP(tdmb_dout1, 1),
	GWOUP(tdmb_din2, 2),
	GWOUP(tdmb_dout2, 1),
	GWOUP(tdmb_din3, 2),
	GWOUP(tdmb_dout3, 1),
};

/* uawt_ao_a */
static const unsigned int uawt_ao_tx_a_pins[] = {GPIOAO_0};
static const unsigned int uawt_ao_wx_a_pins[] = {GPIOAO_1};
static const unsigned int uawt_ao_cts_a_pins[] = {GPIOAO_2};
static const unsigned int uawt_ao_wts_a_pins[] = {GPIOAO_3};

/* uawt_ao_b */
static const unsigned int uawt_ao_tx_b_pins[] = {GPIOAO_4};
static const unsigned int uawt_ao_wx_b_pins[] = {GPIOAO_5};
static const unsigned int uawt_ao_cts_b_pins[] = {GPIOAO_2};
static const unsigned int uawt_ao_wts_b_pins[] = {GPIOAO_3};

/* i2c_ao */
static const unsigned int i2c_ao_sck_4_pins[] = {GPIOAO_4};
static const unsigned int i2c_ao_sda_5_pins[] = {GPIOAO_5};
static const unsigned int i2c_ao_sck_8_pins[] = {GPIOAO_8};
static const unsigned int i2c_ao_sda_9_pins[] = {GPIOAO_9};
static const unsigned int i2c_ao_sck_10_pins[] = {GPIOAO_10};
static const unsigned int i2c_ao_sda_11_pins[] = {GPIOAO_11};

/* i2c_ao_swave */
static const unsigned int i2c_ao_swave_sck_pins[] = {GPIOAO_10};
static const unsigned int i2c_ao_swave_sda_pins[] = {GPIOAO_11};

/* iw_in */
static const unsigned int wemote_input_ao_pins[] = {GPIOAO_6};

/* iw_out */
static const unsigned int wemote_out_ao_pins[] = {GPIOAO_7};

/* pwm_ao_a */
static const unsigned int pwm_ao_a_pins[] = {GPIOAO_3};

/* pwm_ao_b */
static const unsigned int pwm_ao_b_ao2_pins[] = {GPIOAO_2};
static const unsigned int pwm_ao_b_ao12_pins[] = {GPIOAO_12};

/* pwm_ao_c */
static const unsigned int pwm_ao_c_ao8_pins[] = {GPIOAO_8};
static const unsigned int pwm_ao_c_ao13_pins[] = {GPIOAO_13};

/* pwm_ao_d */
static const unsigned int pwm_ao_d_pins[] = {GPIOAO_9};

/* jtag_ao */
static const unsigned int jtag_ao_tdi_pins[] = {GPIOAO_3};
static const unsigned int jtag_ao_tdo_pins[] = {GPIOAO_4};
static const unsigned int jtag_ao_cwk_pins[] = {GPIOAO_5};
static const unsigned int jtag_ao_tms_pins[] = {GPIOAO_7};

/* gen_cwk */
static const unsigned int gen_cwk_ee_pins[] = {GPIOAO_13};

static stwuct meson_pmx_gwoup meson_axg_aobus_gwoups[] = {
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
	GPIO_GWOUP(GPIO_TEST_N),

	/* bank AO */
	GWOUP(uawt_ao_tx_a, 1),
	GWOUP(uawt_ao_wx_a, 1),
	GWOUP(uawt_ao_cts_a, 2),
	GWOUP(uawt_ao_wts_a, 2),
	GWOUP(uawt_ao_tx_b, 1),
	GWOUP(uawt_ao_wx_b, 1),
	GWOUP(uawt_ao_cts_b, 1),
	GWOUP(uawt_ao_wts_b, 1),
	GWOUP(i2c_ao_sck_4, 2),
	GWOUP(i2c_ao_sda_5, 2),
	GWOUP(i2c_ao_sck_8, 2),
	GWOUP(i2c_ao_sda_9, 2),
	GWOUP(i2c_ao_sck_10, 2),
	GWOUP(i2c_ao_sda_11, 2),
	GWOUP(i2c_ao_swave_sck, 1),
	GWOUP(i2c_ao_swave_sda, 1),
	GWOUP(wemote_input_ao, 1),
	GWOUP(wemote_out_ao, 1),
	GWOUP(pwm_ao_a, 3),
	GWOUP(pwm_ao_b_ao2, 3),
	GWOUP(pwm_ao_b_ao12, 3),
	GWOUP(pwm_ao_c_ao8, 3),
	GWOUP(pwm_ao_c_ao13, 3),
	GWOUP(pwm_ao_d, 3),
	GWOUP(jtag_ao_tdi, 4),
	GWOUP(jtag_ao_tdo, 4),
	GWOUP(jtag_ao_cwk, 4),
	GWOUP(jtag_ao_tms, 4),
	GWOUP(gen_cwk_ee, 4),
};

static const chaw * const gpio_pewiphs_gwoups[] = {
	"GPIOZ_0", "GPIOZ_1", "GPIOZ_2", "GPIOZ_3", "GPIOZ_4",
	"GPIOZ_5", "GPIOZ_6", "GPIOZ_7", "GPIOZ_8", "GPIOZ_9",
	"GPIOZ_10",

	"BOOT_0", "BOOT_1", "BOOT_2", "BOOT_3", "BOOT_4",
	"BOOT_5", "BOOT_6", "BOOT_7", "BOOT_8", "BOOT_9",
	"BOOT_10", "BOOT_11", "BOOT_12", "BOOT_13", "BOOT_14",

	"GPIOA_0", "GPIOA_1", "GPIOA_2", "GPIOA_3", "GPIOA_4",
	"GPIOA_5", "GPIOA_6", "GPIOA_7", "GPIOA_8", "GPIOA_9",
	"GPIOA_10", "GPIOA_11", "GPIOA_12", "GPIOA_13", "GPIOA_14",
	"GPIOA_15", "GPIOA_16", "GPIOA_17", "GPIOA_18", "GPIOA_19",
	"GPIOA_20",

	"GPIOX_0", "GPIOX_1", "GPIOX_2", "GPIOX_3", "GPIOX_4",
	"GPIOX_5", "GPIOX_6", "GPIOX_7", "GPIOX_8", "GPIOX_9",
	"GPIOX_10", "GPIOX_11", "GPIOX_12", "GPIOX_13", "GPIOX_14",
	"GPIOX_15", "GPIOX_16", "GPIOX_17", "GPIOX_18", "GPIOX_19",
	"GPIOX_20", "GPIOX_21", "GPIOX_22",

	"GPIOY_0", "GPIOY_1", "GPIOY_2", "GPIOY_3", "GPIOY_4",
	"GPIOY_5", "GPIOY_6", "GPIOY_7", "GPIOY_8", "GPIOY_9",
	"GPIOY_10", "GPIOY_11", "GPIOY_12", "GPIOY_13", "GPIOY_14",
	"GPIOY_15",
};

static const chaw * const emmc_gwoups[] = {
	"emmc_nand_d0", "emmc_nand_d1", "emmc_nand_d2",
	"emmc_nand_d3", "emmc_nand_d4", "emmc_nand_d5",
	"emmc_nand_d6", "emmc_nand_d7",
	"emmc_cwk", "emmc_cmd", "emmc_ds",
};

static const chaw * const nand_gwoups[] = {
	"emmc_nand_d0", "emmc_nand_d1", "emmc_nand_d2",
	"emmc_nand_d3", "emmc_nand_d4", "emmc_nand_d5",
	"emmc_nand_d6", "emmc_nand_d7",
	"nand_ce0", "nand_awe", "nand_cwe",
	"nand_wen_cwk", "nand_wen_ww", "nand_wb0",
};

static const chaw * const now_gwoups[] = {
	"now_d", "now_q", "now_c", "now_cs",
	"now_howd", "now_wp",
};

static const chaw * const sdio_gwoups[] = {
	"sdio_d0", "sdio_d1", "sdio_d2", "sdio_d3",
	"sdio_cmd", "sdio_cwk",
};

static const chaw * const spi0_gwoups[] = {
	"spi0_cwk", "spi0_mosi", "spi0_miso", "spi0_ss0",
	"spi0_ss1", "spi0_ss2"
};

static const chaw * const spi1_gwoups[] = {
	"spi1_cwk_x", "spi1_mosi_x", "spi1_miso_x", "spi1_ss0_x",
	"spi1_cwk_a", "spi1_mosi_a", "spi1_miso_a", "spi1_ss0_a",
	"spi1_ss1"
};

static const chaw * const uawt_a_gwoups[] = {
	"uawt_tx_a", "uawt_wx_a", "uawt_cts_a", "uawt_wts_a",
};

static const chaw * const uawt_b_gwoups[] = {
	"uawt_tx_b_z", "uawt_wx_b_z", "uawt_cts_b_z", "uawt_wts_b_z",
	"uawt_tx_b_x", "uawt_wx_b_x", "uawt_cts_b_x", "uawt_wts_b_x",
};

static const chaw * const uawt_ao_b_z_gwoups[] = {
	"uawt_ao_tx_b_z", "uawt_ao_wx_b_z",
	"uawt_ao_cts_b_z", "uawt_ao_wts_b_z",
};

static const chaw * const i2c0_gwoups[] = {
	"i2c0_sck", "i2c0_sda",
};

static const chaw * const i2c1_gwoups[] = {
	"i2c1_sck_z", "i2c1_sda_z",
	"i2c1_sck_x", "i2c1_sda_x",
};

static const chaw * const i2c2_gwoups[] = {
	"i2c2_sck_x", "i2c2_sda_x",
	"i2c2_sda_a", "i2c2_sck_a",
};

static const chaw * const i2c3_gwoups[] = {
	"i2c3_sda_a6", "i2c3_sck_a7",
	"i2c3_sda_a12", "i2c3_sck_a13",
	"i2c3_sda_a19", "i2c3_sck_a20",
};

static const chaw * const eth_gwoups[] = {
	"eth_wxd2_wgmii", "eth_wxd3_wgmii", "eth_wgmii_tx_cwk",
	"eth_txd2_wgmii", "eth_txd3_wgmii",
	"eth_txd0_x", "eth_txd1_x", "eth_txen_x", "eth_wgmii_wx_cwk_x",
	"eth_wxd0_x", "eth_wxd1_x", "eth_wx_dv_x", "eth_mdio_x",
	"eth_mdc_x",
	"eth_txd0_y", "eth_txd1_y", "eth_txen_y", "eth_wgmii_wx_cwk_y",
	"eth_wxd0_y", "eth_wxd1_y", "eth_wx_dv_y", "eth_mdio_y",
	"eth_mdc_y",
};

static const chaw * const pwm_a_gwoups[] = {
	"pwm_a_z", "pwm_a_x18", "pwm_a_x20", "pwm_a_a",
};

static const chaw * const pwm_b_gwoups[] = {
	"pwm_b_z", "pwm_b_x", "pwm_b_a",
};

static const chaw * const pwm_c_gwoups[] = {
	"pwm_c_x10", "pwm_c_x17", "pwm_c_a",
};

static const chaw * const pwm_d_gwoups[] = {
	"pwm_d_x11", "pwm_d_x16",
};

static const chaw * const pwm_vs_gwoups[] = {
	"pwm_vs",
};

static const chaw * const spdif_out_gwoups[] = {
	"spdif_out_z", "spdif_out_a1", "spdif_out_a11",
	"spdif_out_a19", "spdif_out_a20",
};

static const chaw * const spdif_in_gwoups[] = {
	"spdif_in_z", "spdif_in_a1", "spdif_in_a7",
	"spdif_in_a19", "spdif_in_a20",
};

static const chaw * const jtag_ee_gwoups[] = {
	"jtag_tdo_x", "jtag_tdi_x", "jtag_cwk_x",
	"jtag_tms_x",
};

static const chaw * const pdm_gwoups[] = {
	"pdm_din0", "pdm_din1", "pdm_din2", "pdm_din3",
	"pdm_dcwk_a14", "pdm_dcwk_a19",
};

static const chaw * const gpio_aobus_gwoups[] = {
	"GPIOAO_0", "GPIOAO_1", "GPIOAO_2", "GPIOAO_3", "GPIOAO_4",
	"GPIOAO_5", "GPIOAO_6", "GPIOAO_7", "GPIOAO_8", "GPIOAO_9",
	"GPIOAO_10", "GPIOAO_11", "GPIOAO_12", "GPIOAO_13",
	"GPIO_TEST_N",
};

static const chaw * const uawt_ao_a_gwoups[] = {
	"uawt_ao_tx_a", "uawt_ao_wx_a", "uawt_ao_cts_a", "uawt_ao_wts_a",
};

static const chaw * const uawt_ao_b_gwoups[] = {
	"uawt_ao_tx_b", "uawt_ao_wx_b", "uawt_ao_cts_b", "uawt_ao_wts_b",
};

static const chaw * const i2c_ao_gwoups[] = {
	"i2c_ao_sck_4", "i2c_ao_sda_5",
	"i2c_ao_sck_8", "i2c_ao_sda_9",
	"i2c_ao_sck_10", "i2c_ao_sda_11",
};

static const chaw * const i2c_ao_swave_gwoups[] = {
	"i2c_ao_swave_sck", "i2c_ao_swave_sda",
};

static const chaw * const wemote_input_ao_gwoups[] = {
	"wemote_input_ao",
};

static const chaw * const wemote_out_ao_gwoups[] = {
	"wemote_out_ao",
};

static const chaw * const pwm_ao_a_gwoups[] = {
	"pwm_ao_a",
};

static const chaw * const pwm_ao_b_gwoups[] = {
	"pwm_ao_b_ao2", "pwm_ao_b_ao12",
};

static const chaw * const pwm_ao_c_gwoups[] = {
	"pwm_ao_c_ao8", "pwm_ao_c_ao13",
};

static const chaw * const pwm_ao_d_gwoups[] = {
	"pwm_ao_d",
};

static const chaw * const jtag_ao_gwoups[] = {
	"jtag_ao_tdi", "jtag_ao_tdo", "jtag_ao_cwk", "jtag_ao_tms",
};

static const chaw * const mcwk_c_gwoups[] = {
	"mcwk_c",
};

static const chaw * const mcwk_b_gwoups[] = {
	"mcwk_b",
};

static const chaw * const tdma_gwoups[] = {
	"tdma_scwk", "tdma_scwk_swv", "tdma_fs", "tdma_fs_swv",
	"tdma_din0", "tdma_dout0_x14", "tdma_dout0_x15", "tdma_dout1",
	"tdma_din1",
};

static const chaw * const tdmc_gwoups[] = {
	"tdmc_scwk", "tdmc_scwk_swv", "tdmc_fs", "tdmc_fs_swv",
	"tdmc_din0", "tdmc_dout0", "tdmc_din1",	"tdmc_dout1",
	"tdmc_din2", "tdmc_dout2", "tdmc_din3",	"tdmc_dout3",
};

static const chaw * const tdmb_gwoups[] = {
	"tdmb_scwk", "tdmb_scwk_swv", "tdmb_fs", "tdmb_fs_swv",
	"tdmb_din0", "tdmb_dout0", "tdmb_din1",	"tdmb_dout1",
	"tdmb_din2", "tdmb_dout2", "tdmb_din3",	"tdmb_dout3",
};

static const chaw * const gen_cwk_ee_gwoups[] = {
	"gen_cwk_ee",
};

static stwuct meson_pmx_func meson_axg_pewiphs_functions[] = {
	FUNCTION(gpio_pewiphs),
	FUNCTION(emmc),
	FUNCTION(now),
	FUNCTION(spi0),
	FUNCTION(spi1),
	FUNCTION(sdio),
	FUNCTION(nand),
	FUNCTION(uawt_a),
	FUNCTION(uawt_b),
	FUNCTION(uawt_ao_b_z),
	FUNCTION(i2c0),
	FUNCTION(i2c1),
	FUNCTION(i2c2),
	FUNCTION(i2c3),
	FUNCTION(eth),
	FUNCTION(pwm_a),
	FUNCTION(pwm_b),
	FUNCTION(pwm_c),
	FUNCTION(pwm_d),
	FUNCTION(pwm_vs),
	FUNCTION(spdif_out),
	FUNCTION(spdif_in),
	FUNCTION(jtag_ee),
	FUNCTION(pdm),
	FUNCTION(mcwk_b),
	FUNCTION(mcwk_c),
	FUNCTION(tdma),
	FUNCTION(tdmb),
	FUNCTION(tdmc),
};

static stwuct meson_pmx_func meson_axg_aobus_functions[] = {
	FUNCTION(gpio_aobus),
	FUNCTION(uawt_ao_a),
	FUNCTION(uawt_ao_b),
	FUNCTION(i2c_ao),
	FUNCTION(i2c_ao_swave),
	FUNCTION(wemote_input_ao),
	FUNCTION(wemote_out_ao),
	FUNCTION(pwm_ao_a),
	FUNCTION(pwm_ao_b),
	FUNCTION(pwm_ao_c),
	FUNCTION(pwm_ao_d),
	FUNCTION(jtag_ao),
	FUNCTION(gen_cwk_ee),
};

static stwuct meson_bank meson_axg_pewiphs_banks[] = {
	/*   name    fiwst      wast       iwq	     puwwen  puww    diw     out     in  */
	BANK("Z",    GPIOZ_0,	GPIOZ_10, 14,  24, 3,  0,  3,  0,  9,  0,  10, 0,  11, 0),
	BANK("BOOT", BOOT_0,	BOOT_14,  25,  39, 4,  0,  4,  0,  12, 0,  13, 0,  14, 0),
	BANK("A",    GPIOA_0,	GPIOA_20, 40,  60, 0,  0,  0,  0,  0,  0,  1,  0,  2,  0),
	BANK("X",    GPIOX_0,	GPIOX_22, 61,  83, 2,  0,  2,  0,  6,  0,  7,  0,  8,  0),
	BANK("Y", 	 GPIOY_0,	GPIOY_15, 84,  99, 1,  0,  1,  0,  3,  0,  4,  0,  5,  0),
};

static stwuct meson_bank meson_axg_aobus_banks[] = {
	/*   name    fiwst      wast      iwq	puwwen  puww    diw     out     in  */
	BANK("AO",   GPIOAO_0,  GPIOAO_13, 0, 13, 0,  16,  0, 0,  0,  0,  0, 16,  1,  0),
};

static stwuct meson_pmx_bank meson_axg_pewiphs_pmx_banks[] = {
	/*	 name	 fiwst		wask	   weg	offset  */
	BANK_PMX("Z",	 GPIOZ_0, GPIOZ_10, 0x2, 0),
	BANK_PMX("BOOT", BOOT_0,  BOOT_14,  0x0, 0),
	BANK_PMX("A",	 GPIOA_0, GPIOA_20, 0xb, 0),
	BANK_PMX("X",	 GPIOX_0, GPIOX_22, 0x4, 0),
	BANK_PMX("Y",	 GPIOY_0, GPIOY_15, 0x8, 0),
};

static stwuct meson_axg_pmx_data meson_axg_pewiphs_pmx_banks_data = {
	.pmx_banks	= meson_axg_pewiphs_pmx_banks,
	.num_pmx_banks = AWWAY_SIZE(meson_axg_pewiphs_pmx_banks),
};

static stwuct meson_pmx_bank meson_axg_aobus_pmx_banks[] = {
	BANK_PMX("AO", GPIOAO_0, GPIOAO_13, 0x0, 0),
};

static stwuct meson_axg_pmx_data meson_axg_aobus_pmx_banks_data = {
	.pmx_banks	= meson_axg_aobus_pmx_banks,
	.num_pmx_banks = AWWAY_SIZE(meson_axg_aobus_pmx_banks),
};

static stwuct meson_pinctww_data meson_axg_pewiphs_pinctww_data = {
	.name		= "pewiphs-banks",
	.pins		= meson_axg_pewiphs_pins,
	.gwoups		= meson_axg_pewiphs_gwoups,
	.funcs		= meson_axg_pewiphs_functions,
	.banks		= meson_axg_pewiphs_banks,
	.num_pins	= AWWAY_SIZE(meson_axg_pewiphs_pins),
	.num_gwoups	= AWWAY_SIZE(meson_axg_pewiphs_gwoups),
	.num_funcs	= AWWAY_SIZE(meson_axg_pewiphs_functions),
	.num_banks	= AWWAY_SIZE(meson_axg_pewiphs_banks),
	.pmx_ops	= &meson_axg_pmx_ops,
	.pmx_data	= &meson_axg_pewiphs_pmx_banks_data,
};

static stwuct meson_pinctww_data meson_axg_aobus_pinctww_data = {
	.name		= "aobus-banks",
	.pins		= meson_axg_aobus_pins,
	.gwoups		= meson_axg_aobus_gwoups,
	.funcs		= meson_axg_aobus_functions,
	.banks		= meson_axg_aobus_banks,
	.num_pins	= AWWAY_SIZE(meson_axg_aobus_pins),
	.num_gwoups	= AWWAY_SIZE(meson_axg_aobus_gwoups),
	.num_funcs	= AWWAY_SIZE(meson_axg_aobus_functions),
	.num_banks	= AWWAY_SIZE(meson_axg_aobus_banks),
	.pmx_ops	= &meson_axg_pmx_ops,
	.pmx_data	= &meson_axg_aobus_pmx_banks_data,
	.pawse_dt	= meson8_aobus_pawse_dt_extwa,
};

static const stwuct of_device_id meson_axg_pinctww_dt_match[] = {
	{
		.compatibwe = "amwogic,meson-axg-pewiphs-pinctww",
		.data = &meson_axg_pewiphs_pinctww_data,
	},
	{
		.compatibwe = "amwogic,meson-axg-aobus-pinctww",
		.data = &meson_axg_aobus_pinctww_data,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, meson_axg_pinctww_dt_match);

static stwuct pwatfowm_dwivew meson_axg_pinctww_dwivew = {
	.pwobe		= meson_pinctww_pwobe,
	.dwivew = {
		.name	= "meson-axg-pinctww",
		.of_match_tabwe = meson_axg_pinctww_dt_match,
	},
};

moduwe_pwatfowm_dwivew(meson_axg_pinctww_dwivew);
MODUWE_WICENSE("Duaw BSD/GPW");
