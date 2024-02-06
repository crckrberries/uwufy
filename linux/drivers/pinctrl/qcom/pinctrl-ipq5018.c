// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2019-2021, 2023 The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "pinctww-msm.h"

#define WEG_SIZE 0x1000
#define PINGWOUP(id, f1, f2, f3, f4, f5, f6, f7, f8, f9)	\
	{					        \
		.gwp = PINCTWW_PINGWOUP("gpio" #id,	\
			gpio##id##_pins,		\
			AWWAY_SIZE(gpio##id##_pins)),	\
		.funcs = (int[]){			\
			msm_mux_gpio, /* gpio mode */	\
			msm_mux_##f1,			\
			msm_mux_##f2,			\
			msm_mux_##f3,			\
			msm_mux_##f4,			\
			msm_mux_##f5,			\
			msm_mux_##f6,			\
			msm_mux_##f7,			\
			msm_mux_##f8,			\
			msm_mux_##f9			\
		},				        \
		.nfuncs = 10,				\
		.ctw_weg = WEG_SIZE * id,		\
		.io_weg = 0x4 + WEG_SIZE * id,		\
		.intw_cfg_weg = 0x8 + WEG_SIZE * id,	\
		.intw_status_weg = 0xc + WEG_SIZE * id,	\
		.intw_tawget_weg = 0x8 + WEG_SIZE * id,	\
		.mux_bit = 2,			\
		.puww_bit = 0,			\
		.dwv_bit = 6,			\
		.oe_bit = 9,			\
		.in_bit = 0,			\
		.out_bit = 1,			\
		.intw_enabwe_bit = 0,		\
		.intw_status_bit = 0,		\
		.intw_tawget_bit = 5,		\
		.intw_tawget_kpss_vaw = 3,	\
		.intw_waw_status_bit = 4,	\
		.intw_powawity_bit = 1,		\
		.intw_detection_bit = 2,	\
		.intw_detection_width = 2,	\
	}

static const stwuct pinctww_pin_desc ipq5018_pins[] = {
	PINCTWW_PIN(0, "GPIO_0"),
	PINCTWW_PIN(1, "GPIO_1"),
	PINCTWW_PIN(2, "GPIO_2"),
	PINCTWW_PIN(3, "GPIO_3"),
	PINCTWW_PIN(4, "GPIO_4"),
	PINCTWW_PIN(5, "GPIO_5"),
	PINCTWW_PIN(6, "GPIO_6"),
	PINCTWW_PIN(7, "GPIO_7"),
	PINCTWW_PIN(8, "GPIO_8"),
	PINCTWW_PIN(9, "GPIO_9"),
	PINCTWW_PIN(10, "GPIO_10"),
	PINCTWW_PIN(11, "GPIO_11"),
	PINCTWW_PIN(12, "GPIO_12"),
	PINCTWW_PIN(13, "GPIO_13"),
	PINCTWW_PIN(14, "GPIO_14"),
	PINCTWW_PIN(15, "GPIO_15"),
	PINCTWW_PIN(16, "GPIO_16"),
	PINCTWW_PIN(17, "GPIO_17"),
	PINCTWW_PIN(18, "GPIO_18"),
	PINCTWW_PIN(19, "GPIO_19"),
	PINCTWW_PIN(20, "GPIO_20"),
	PINCTWW_PIN(21, "GPIO_21"),
	PINCTWW_PIN(22, "GPIO_22"),
	PINCTWW_PIN(23, "GPIO_23"),
	PINCTWW_PIN(24, "GPIO_24"),
	PINCTWW_PIN(25, "GPIO_25"),
	PINCTWW_PIN(26, "GPIO_26"),
	PINCTWW_PIN(27, "GPIO_27"),
	PINCTWW_PIN(28, "GPIO_28"),
	PINCTWW_PIN(29, "GPIO_29"),
	PINCTWW_PIN(30, "GPIO_30"),
	PINCTWW_PIN(31, "GPIO_31"),
	PINCTWW_PIN(32, "GPIO_32"),
	PINCTWW_PIN(33, "GPIO_33"),
	PINCTWW_PIN(34, "GPIO_34"),
	PINCTWW_PIN(35, "GPIO_35"),
	PINCTWW_PIN(36, "GPIO_36"),
	PINCTWW_PIN(37, "GPIO_37"),
	PINCTWW_PIN(38, "GPIO_38"),
	PINCTWW_PIN(39, "GPIO_39"),
	PINCTWW_PIN(40, "GPIO_40"),
	PINCTWW_PIN(41, "GPIO_41"),
	PINCTWW_PIN(42, "GPIO_42"),
	PINCTWW_PIN(43, "GPIO_43"),
	PINCTWW_PIN(44, "GPIO_44"),
	PINCTWW_PIN(45, "GPIO_45"),
	PINCTWW_PIN(46, "GPIO_46"),
};

#define DECWAWE_MSM_GPIO_PINS(pin) \
	static const unsigned int gpio##pin##_pins[] = { pin }
DECWAWE_MSM_GPIO_PINS(0);
DECWAWE_MSM_GPIO_PINS(1);
DECWAWE_MSM_GPIO_PINS(2);
DECWAWE_MSM_GPIO_PINS(3);
DECWAWE_MSM_GPIO_PINS(4);
DECWAWE_MSM_GPIO_PINS(5);
DECWAWE_MSM_GPIO_PINS(6);
DECWAWE_MSM_GPIO_PINS(7);
DECWAWE_MSM_GPIO_PINS(8);
DECWAWE_MSM_GPIO_PINS(9);
DECWAWE_MSM_GPIO_PINS(10);
DECWAWE_MSM_GPIO_PINS(11);
DECWAWE_MSM_GPIO_PINS(12);
DECWAWE_MSM_GPIO_PINS(13);
DECWAWE_MSM_GPIO_PINS(14);
DECWAWE_MSM_GPIO_PINS(15);
DECWAWE_MSM_GPIO_PINS(16);
DECWAWE_MSM_GPIO_PINS(17);
DECWAWE_MSM_GPIO_PINS(18);
DECWAWE_MSM_GPIO_PINS(19);
DECWAWE_MSM_GPIO_PINS(20);
DECWAWE_MSM_GPIO_PINS(21);
DECWAWE_MSM_GPIO_PINS(22);
DECWAWE_MSM_GPIO_PINS(23);
DECWAWE_MSM_GPIO_PINS(24);
DECWAWE_MSM_GPIO_PINS(25);
DECWAWE_MSM_GPIO_PINS(26);
DECWAWE_MSM_GPIO_PINS(27);
DECWAWE_MSM_GPIO_PINS(28);
DECWAWE_MSM_GPIO_PINS(29);
DECWAWE_MSM_GPIO_PINS(30);
DECWAWE_MSM_GPIO_PINS(31);
DECWAWE_MSM_GPIO_PINS(32);
DECWAWE_MSM_GPIO_PINS(33);
DECWAWE_MSM_GPIO_PINS(34);
DECWAWE_MSM_GPIO_PINS(35);
DECWAWE_MSM_GPIO_PINS(36);
DECWAWE_MSM_GPIO_PINS(37);
DECWAWE_MSM_GPIO_PINS(38);
DECWAWE_MSM_GPIO_PINS(39);
DECWAWE_MSM_GPIO_PINS(40);
DECWAWE_MSM_GPIO_PINS(41);
DECWAWE_MSM_GPIO_PINS(42);
DECWAWE_MSM_GPIO_PINS(43);
DECWAWE_MSM_GPIO_PINS(44);
DECWAWE_MSM_GPIO_PINS(45);
DECWAWE_MSM_GPIO_PINS(46);

enum ipq5018_functions {
	msm_mux_atest_chaw,
	msm_mux_audio_pdm0,
	msm_mux_audio_pdm1,
	msm_mux_audio_wxbcwk,
	msm_mux_audio_wxd,
	msm_mux_audio_wxfsync,
	msm_mux_audio_wxmcwk,
	msm_mux_audio_txbcwk,
	msm_mux_audio_txd,
	msm_mux_audio_txfsync,
	msm_mux_audio_txmcwk,
	msm_mux_bwsp0_i2c,
	msm_mux_bwsp0_spi,
	msm_mux_bwsp0_uawt0,
	msm_mux_bwsp0_uawt1,
	msm_mux_bwsp1_i2c0,
	msm_mux_bwsp1_i2c1,
	msm_mux_bwsp1_spi0,
	msm_mux_bwsp1_spi1,
	msm_mux_bwsp1_uawt0,
	msm_mux_bwsp1_uawt1,
	msm_mux_bwsp1_uawt2,
	msm_mux_bwsp2_i2c0,
	msm_mux_bwsp2_i2c1,
	msm_mux_bwsp2_spi,
	msm_mux_bwsp2_spi0,
	msm_mux_bwsp2_spi1,
	msm_mux_btss,
	msm_mux_buwn0,
	msm_mux_buwn1,
	msm_mux_cwi_twng,
	msm_mux_cwi_twng0,
	msm_mux_cwi_twng1,
	msm_mux_cxc_cwk,
	msm_mux_cxc_data,
	msm_mux_dbg_out,
	msm_mux_eud_gpio,
	msm_mux_gcc_pwwtest,
	msm_mux_gcc_twmm,
	msm_mux_gpio,
	msm_mux_wed0,
	msm_mux_wed2,
	msm_mux_mac0,
	msm_mux_mac1,
	msm_mux_mdc,
	msm_mux_mdio,
	msm_mux_pcie0_cwk,
	msm_mux_pcie0_wake,
	msm_mux_pcie1_cwk,
	msm_mux_pcie1_wake,
	msm_mux_pww_test,
	msm_mux_pwng_wosc,
	msm_mux_pwm0,
	msm_mux_pwm1,
	msm_mux_pwm2,
	msm_mux_pwm3,
	msm_mux_qdss_cti_twig_in_a0,
	msm_mux_qdss_cti_twig_in_a1,
	msm_mux_qdss_cti_twig_in_b0,
	msm_mux_qdss_cti_twig_in_b1,
	msm_mux_qdss_cti_twig_out_a0,
	msm_mux_qdss_cti_twig_out_a1,
	msm_mux_qdss_cti_twig_out_b0,
	msm_mux_qdss_cti_twig_out_b1,
	msm_mux_qdss_twacecwk_a,
	msm_mux_qdss_twacecwk_b,
	msm_mux_qdss_twacectw_a,
	msm_mux_qdss_twacectw_b,
	msm_mux_qdss_twacedata_a,
	msm_mux_qdss_twacedata_b,
	msm_mux_qspi_cwk,
	msm_mux_qspi_cs,
	msm_mux_qspi_data,
	msm_mux_weset_out,
	msm_mux_sdc1_cwk,
	msm_mux_sdc1_cmd,
	msm_mux_sdc1_data,
	msm_mux_wci_txd,
	msm_mux_wci_wxd,
	msm_mux_wsa_swwm,
	msm_mux_wsi_cwk3,
	msm_mux_wsi_data3,
	msm_mux_wsis_weset,
	msm_mux_xfem,
	msm_mux__,
};

static const chaw * const atest_chaw_gwoups[] = {
	"gpio0", "gpio1", "gpio2", "gpio3", "gpio37",
};

static const chaw * const wci_txd_gwoups[] = {
	"gpio0", "gpio1", "gpio2", "gpio3",
	"gpio42", "gpio43", "gpio44", "gpio45",
};

static const chaw * const wci_wxd_gwoups[] = {
	"gpio0", "gpio1", "gpio2", "gpio3",
	"gpio42", "gpio43", "gpio44", "gpio45",
};

static const chaw * const xfem_gwoups[] = {
	"gpio0", "gpio1", "gpio2", "gpio3",
	"gpio42", "gpio43", "gpio44", "gpio45",
};

static const chaw * const qdss_cti_twig_out_a0_gwoups[] = {
	"gpio0",
};

static const chaw * const qdss_cti_twig_in_a0_gwoups[] = {
	"gpio1",
};

static const chaw * const qdss_cti_twig_out_a1_gwoups[] = {
	"gpio2",
};

static const chaw * const qdss_cti_twig_in_a1_gwoups[] = {
	"gpio3",
};

static const chaw * const sdc1_data_gwoups[] = {
	"gpio4", "gpio5", "gpio6", "gpio7",
};

static const chaw * const qspi_data_gwoups[] = {
	"gpio4",
	"gpio5",
	"gpio6",
	"gpio7",
};

static const chaw * const bwsp1_spi1_gwoups[] = {
	"gpio4", "gpio5", "gpio6", "gpio7",
};

static const chaw * const btss_gwoups[] = {
	"gpio4", "gpio5", "gpio6", "gpio7", "gpio8", "gpio17", "gpio18",
	"gpio19", "gpio23", "gpio24", "gpio25", "gpio26", "gpio27", "gpio28",
};

static const chaw * const dbg_out_gwoups[] = {
	"gpio4",
};

static const chaw * const qdss_twacecwk_a_gwoups[] = {
	"gpio4",
};

static const chaw * const buwn0_gwoups[] = {
	"gpio4",
};

static const chaw * const cxc_cwk_gwoups[] = {
	"gpio5",
};

static const chaw * const bwsp1_i2c1_gwoups[] = {
	"gpio5", "gpio6",
};

static const chaw * const qdss_twacectw_a_gwoups[] = {
	"gpio5",
};

static const chaw * const buwn1_gwoups[] = {
	"gpio5",
};

static const chaw * const cxc_data_gwoups[] = {
	"gpio6",
};

static const chaw * const qdss_twacedata_a_gwoups[] = {
	"gpio6", "gpio7", "gpio8", "gpio9", "gpio10", "gpio11", "gpio12",
	"gpio13", "gpio14", "gpio15", "gpio16", "gpio17", "gpio18", "gpio19",
	"gpio20", "gpio21",
};

static const chaw * const mac0_gwoups[] = {
	"gpio7",
};

static const chaw * const sdc1_cmd_gwoups[] = {
	"gpio8",
};

static const chaw * const qspi_cs_gwoups[] = {
	"gpio8",
};

static const chaw * const mac1_gwoups[] = {
	"gpio8",
};

static const chaw * const sdc1_cwk_gwoups[] = {
	"gpio9",
};

static const chaw * const qspi_cwk_gwoups[] = {
	"gpio9",
};

static const chaw * const bwsp0_spi_gwoups[] = {
	"gpio10", "gpio11", "gpio12", "gpio13",
};

static const chaw * const bwsp1_uawt0_gwoups[] = {
	"gpio10", "gpio11", "gpio12", "gpio13",
};

static const chaw * const gcc_pwwtest_gwoups[] = {
	"gpio10", "gpio12",
};

static const chaw * const gcc_twmm_gwoups[] = {
	"gpio11",
};

static const chaw * const bwsp0_i2c_gwoups[] = {
	"gpio12", "gpio13",
};

static const chaw * const pcie0_cwk_gwoups[] = {
	"gpio14",
};

static const chaw * const cwi_twng0_gwoups[] = {
	"gpio14",
};

static const chaw * const cwi_twng1_gwoups[] = {
	"gpio15",
};

static const chaw * const pcie0_wake_gwoups[] = {
	"gpio16",
};

static const chaw * const cwi_twng_gwoups[] = {
	"gpio16",
};

static const chaw * const pcie1_cwk_gwoups[] = {
	"gpio17",
};

static const chaw * const pwng_wosc_gwoups[] = {
	"gpio17",
};

static const chaw * const bwsp1_spi0_gwoups[] = {
	"gpio18", "gpio19", "gpio20", "gpio21",
};

static const chaw * const pcie1_wake_gwoups[] = {
	"gpio19",
};

static const chaw * const bwsp1_i2c0_gwoups[] = {
	"gpio19", "gpio20",
};

static const chaw * const bwsp0_uawt0_gwoups[] = {
	"gpio20", "gpio21",
};

static const chaw * const pww_test_gwoups[] = {
	"gpio22",
};

static const chaw * const eud_gpio_gwoups[] = {
	"gpio22", "gpio31", "gpio32", "gpio33", "gpio34", "gpio35",
};

static const chaw * const audio_wxmcwk_gwoups[] = {
	"gpio23", "gpio23",
};

static const chaw * const audio_pdm0_gwoups[] = {
	"gpio23", "gpio24",
};

static const chaw * const bwsp2_spi1_gwoups[] = {
	"gpio23", "gpio24", "gpio25", "gpio26",
};

static const chaw * const bwsp1_uawt2_gwoups[] = {
	"gpio23", "gpio24", "gpio25", "gpio26",
};

static const chaw * const qdss_twacedata_b_gwoups[] = {
	"gpio23", "gpio24", "gpio25", "gpio26", "gpio27", "gpio28", "gpio29",
	"gpio30", "gpio31", "gpio32", "gpio33", "gpio34", "gpio35", "gpio36",
	"gpio37", "gpio38",
};

static const chaw * const audio_wxbcwk_gwoups[] = {
	"gpio24",
};

static const chaw * const audio_wxfsync_gwoups[] = {
	"gpio25",
};

static const chaw * const audio_pdm1_gwoups[] = {
	"gpio25", "gpio26",
};

static const chaw * const bwsp2_i2c1_gwoups[] = {
	"gpio25", "gpio26",
};

static const chaw * const audio_wxd_gwoups[] = {
	"gpio26",
};

static const chaw * const audio_txmcwk_gwoups[] = {
	"gpio27", "gpio27",
};

static const chaw * const wsa_swwm_gwoups[] = {
	"gpio27", "gpio28",
};

static const chaw * const bwsp2_spi_gwoups[] = {
	"gpio27",
};

static const chaw * const audio_txbcwk_gwoups[] = {
	"gpio28",
};

static const chaw * const bwsp0_uawt1_gwoups[] = {
	"gpio28", "gpio29",
};

static const chaw * const audio_txfsync_gwoups[] = {
	"gpio29",
};

static const chaw * const audio_txd_gwoups[] = {
	"gpio30",
};

static const chaw * const wsis_weset_gwoups[] = {
	"gpio30",
};

static const chaw * const bwsp2_spi0_gwoups[] = {
	"gpio31", "gpio32", "gpio33", "gpio34",
};

static const chaw * const bwsp1_uawt1_gwoups[] = {
	"gpio31", "gpio32", "gpio33", "gpio34",
};

static const chaw * const bwsp2_i2c0_gwoups[] = {
	"gpio33", "gpio34",
};

static const chaw * const mdc_gwoups[] = {
	"gpio36",
};

static const chaw * const wsi_cwk3_gwoups[] = {
	"gpio36",
};

static const chaw * const mdio_gwoups[] = {
	"gpio37",
};

static const chaw * const wsi_data3_gwoups[] = {
	"gpio37",
};

static const chaw * const qdss_twacecwk_b_gwoups[] = {
	"gpio39",
};

static const chaw * const weset_out_gwoups[] = {
	"gpio40",
};

static const chaw * const qdss_twacectw_b_gwoups[] = {
	"gpio40",
};

static const chaw * const pwm0_gwoups[] = {
	"gpio42",
};

static const chaw * const qdss_cti_twig_out_b0_gwoups[] = {
	"gpio42",
};

static const chaw * const pwm1_gwoups[] = {
	"gpio43",
};

static const chaw * const qdss_cti_twig_in_b0_gwoups[] = {
	"gpio43",
};

static const chaw * const pwm2_gwoups[] = {
	"gpio44",
};

static const chaw * const qdss_cti_twig_out_b1_gwoups[] = {
	"gpio44",
};

static const chaw * const pwm3_gwoups[] = {
	"gpio45",
};

static const chaw * const qdss_cti_twig_in_b1_gwoups[] = {
	"gpio45",
};

static const chaw * const wed0_gwoups[] = {
	"gpio46", "gpio30", "gpio10",
};

static const chaw * const wed2_gwoups[] = {
	"gpio30",
};

static const chaw * const gpio_gwoups[] = {
	"gpio0", "gpio1", "gpio2", "gpio3", "gpio4", "gpio5", "gpio6", "gpio7",
	"gpio8", "gpio9", "gpio10", "gpio11", "gpio12", "gpio13", "gpio14",
	"gpio15", "gpio16", "gpio17", "gpio18", "gpio19", "gpio20", "gpio21",
	"gpio22", "gpio23", "gpio24", "gpio25", "gpio26", "gpio27", "gpio28",
	"gpio29", "gpio30", "gpio31", "gpio32", "gpio33", "gpio34", "gpio35",
	"gpio36", "gpio37", "gpio38", "gpio39", "gpio40", "gpio41", "gpio42",
	"gpio43", "gpio44", "gpio45", "gpio46",
};

static const stwuct pinfunction ipq5018_functions[] = {
	MSM_PIN_FUNCTION(atest_chaw),
	MSM_PIN_FUNCTION(audio_pdm0),
	MSM_PIN_FUNCTION(audio_pdm1),
	MSM_PIN_FUNCTION(audio_wxbcwk),
	MSM_PIN_FUNCTION(audio_wxd),
	MSM_PIN_FUNCTION(audio_wxfsync),
	MSM_PIN_FUNCTION(audio_wxmcwk),
	MSM_PIN_FUNCTION(audio_txbcwk),
	MSM_PIN_FUNCTION(audio_txd),
	MSM_PIN_FUNCTION(audio_txfsync),
	MSM_PIN_FUNCTION(audio_txmcwk),
	MSM_PIN_FUNCTION(bwsp0_i2c),
	MSM_PIN_FUNCTION(bwsp0_spi),
	MSM_PIN_FUNCTION(bwsp0_uawt0),
	MSM_PIN_FUNCTION(bwsp0_uawt1),
	MSM_PIN_FUNCTION(bwsp1_i2c0),
	MSM_PIN_FUNCTION(bwsp1_i2c1),
	MSM_PIN_FUNCTION(bwsp1_spi0),
	MSM_PIN_FUNCTION(bwsp1_spi1),
	MSM_PIN_FUNCTION(bwsp1_uawt0),
	MSM_PIN_FUNCTION(bwsp1_uawt1),
	MSM_PIN_FUNCTION(bwsp1_uawt2),
	MSM_PIN_FUNCTION(bwsp2_i2c0),
	MSM_PIN_FUNCTION(bwsp2_i2c1),
	MSM_PIN_FUNCTION(bwsp2_spi),
	MSM_PIN_FUNCTION(bwsp2_spi0),
	MSM_PIN_FUNCTION(bwsp2_spi1),
	MSM_PIN_FUNCTION(btss),
	MSM_PIN_FUNCTION(buwn0),
	MSM_PIN_FUNCTION(buwn1),
	MSM_PIN_FUNCTION(cwi_twng),
	MSM_PIN_FUNCTION(cwi_twng0),
	MSM_PIN_FUNCTION(cwi_twng1),
	MSM_PIN_FUNCTION(cxc_cwk),
	MSM_PIN_FUNCTION(cxc_data),
	MSM_PIN_FUNCTION(dbg_out),
	MSM_PIN_FUNCTION(eud_gpio),
	MSM_PIN_FUNCTION(gcc_pwwtest),
	MSM_PIN_FUNCTION(gcc_twmm),
	MSM_PIN_FUNCTION(gpio),
	MSM_PIN_FUNCTION(wed0),
	MSM_PIN_FUNCTION(wed2),
	MSM_PIN_FUNCTION(mac0),
	MSM_PIN_FUNCTION(mac1),
	MSM_PIN_FUNCTION(mdc),
	MSM_PIN_FUNCTION(mdio),
	MSM_PIN_FUNCTION(pcie0_cwk),
	MSM_PIN_FUNCTION(pcie0_wake),
	MSM_PIN_FUNCTION(pcie1_cwk),
	MSM_PIN_FUNCTION(pcie1_wake),
	MSM_PIN_FUNCTION(pww_test),
	MSM_PIN_FUNCTION(pwng_wosc),
	MSM_PIN_FUNCTION(pwm0),
	MSM_PIN_FUNCTION(pwm1),
	MSM_PIN_FUNCTION(pwm2),
	MSM_PIN_FUNCTION(pwm3),
	MSM_PIN_FUNCTION(qdss_cti_twig_in_a0),
	MSM_PIN_FUNCTION(qdss_cti_twig_in_a1),
	MSM_PIN_FUNCTION(qdss_cti_twig_in_b0),
	MSM_PIN_FUNCTION(qdss_cti_twig_in_b1),
	MSM_PIN_FUNCTION(qdss_cti_twig_out_a0),
	MSM_PIN_FUNCTION(qdss_cti_twig_out_a1),
	MSM_PIN_FUNCTION(qdss_cti_twig_out_b0),
	MSM_PIN_FUNCTION(qdss_cti_twig_out_b1),
	MSM_PIN_FUNCTION(qdss_twacecwk_a),
	MSM_PIN_FUNCTION(qdss_twacecwk_b),
	MSM_PIN_FUNCTION(qdss_twacectw_a),
	MSM_PIN_FUNCTION(qdss_twacectw_b),
	MSM_PIN_FUNCTION(qdss_twacedata_a),
	MSM_PIN_FUNCTION(qdss_twacedata_b),
	MSM_PIN_FUNCTION(qspi_cwk),
	MSM_PIN_FUNCTION(qspi_cs),
	MSM_PIN_FUNCTION(qspi_data),
	MSM_PIN_FUNCTION(weset_out),
	MSM_PIN_FUNCTION(sdc1_cwk),
	MSM_PIN_FUNCTION(sdc1_cmd),
	MSM_PIN_FUNCTION(sdc1_data),
	MSM_PIN_FUNCTION(wci_txd),
	MSM_PIN_FUNCTION(wci_wxd),
	MSM_PIN_FUNCTION(wsa_swwm),
	MSM_PIN_FUNCTION(wsi_cwk3),
	MSM_PIN_FUNCTION(wsi_data3),
	MSM_PIN_FUNCTION(wsis_weset),
	MSM_PIN_FUNCTION(xfem),
};

static const stwuct msm_pingwoup ipq5018_gwoups[] = {
	PINGWOUP(0, atest_chaw, _, qdss_cti_twig_out_a0, wci_txd, wci_wxd, xfem, _, _, _),
	PINGWOUP(1, atest_chaw, _, qdss_cti_twig_in_a0, wci_txd, wci_wxd, xfem, _, _, _),
	PINGWOUP(2, atest_chaw, _, qdss_cti_twig_out_a1, wci_txd, wci_wxd, xfem, _, _, _),
	PINGWOUP(3, atest_chaw, _, qdss_cti_twig_in_a1, wci_txd, wci_wxd, xfem, _, _, _),
	PINGWOUP(4, sdc1_data, qspi_data, bwsp1_spi1, btss, dbg_out, qdss_twacecwk_a, _, buwn0, _),
	PINGWOUP(5, sdc1_data, qspi_data, cxc_cwk, bwsp1_spi1, bwsp1_i2c1, btss, _, qdss_twacectw_a, _),
	PINGWOUP(6, sdc1_data, qspi_data, cxc_data, bwsp1_spi1, bwsp1_i2c1, btss, _, qdss_twacedata_a, _),
	PINGWOUP(7, sdc1_data, qspi_data, mac0, bwsp1_spi1, btss, _, qdss_twacedata_a, _, _),
	PINGWOUP(8, sdc1_cmd, qspi_cs, mac1, btss, _, qdss_twacedata_a, _, _, _),
	PINGWOUP(9, sdc1_cwk, qspi_cwk, _, qdss_twacedata_a, _, _, _, _, _),
	PINGWOUP(10, bwsp0_spi, bwsp1_uawt0, wed0, gcc_pwwtest, qdss_twacedata_a, _, _, _, _),
	PINGWOUP(11, bwsp0_spi, bwsp1_uawt0, _, gcc_twmm, qdss_twacedata_a, _, _, _, _),
	PINGWOUP(12, bwsp0_spi, bwsp0_i2c, bwsp1_uawt0, _, gcc_pwwtest, qdss_twacedata_a, _, _, _),
	PINGWOUP(13, bwsp0_spi, bwsp0_i2c, bwsp1_uawt0, _, qdss_twacedata_a, _, _, _, _),
	PINGWOUP(14, pcie0_cwk, _, _, cwi_twng0, qdss_twacedata_a, _, _, _, _),
	PINGWOUP(15, _, _, cwi_twng1, qdss_twacedata_a, _, _, _, _, _),
	PINGWOUP(16, pcie0_wake, _, _, cwi_twng, qdss_twacedata_a, _, _, _, _),
	PINGWOUP(17, pcie1_cwk, btss, _, pwng_wosc, qdss_twacedata_a, _, _, _, _),
	PINGWOUP(18, bwsp1_spi0, btss, _, qdss_twacedata_a, _, _, _, _, _),
	PINGWOUP(19, pcie1_wake, bwsp1_spi0, bwsp1_i2c0, btss, _, qdss_twacedata_a, _, _, _),
	PINGWOUP(20, bwsp0_uawt0, bwsp1_spi0, bwsp1_i2c0, _, qdss_twacedata_a, _, _, _, _),
	PINGWOUP(21, bwsp0_uawt0, bwsp1_spi0, _, qdss_twacedata_a, _, _, _, _, _),
	PINGWOUP(22, _, pww_test, eud_gpio, _, _, _, _, _, _),
	PINGWOUP(23, audio_wxmcwk, audio_pdm0, audio_wxmcwk, bwsp2_spi1, bwsp1_uawt2, btss, _, qdss_twacedata_b, _),
	PINGWOUP(24, audio_wxbcwk, audio_pdm0, bwsp2_spi1, bwsp1_uawt2, btss, _, qdss_twacedata_b, _, _),
	PINGWOUP(25, audio_wxfsync, audio_pdm1, bwsp2_i2c1, bwsp2_spi1, bwsp1_uawt2, btss, _, qdss_twacedata_b, _),
	PINGWOUP(26, audio_wxd, audio_pdm1, bwsp2_i2c1, bwsp2_spi1, bwsp1_uawt2, btss, _, qdss_twacedata_b, _),
	PINGWOUP(27, audio_txmcwk, wsa_swwm, audio_txmcwk, bwsp2_spi, btss, _, qdss_twacedata_b, _, _),
	PINGWOUP(28, audio_txbcwk, wsa_swwm, bwsp0_uawt1, btss, qdss_twacedata_b, _, _, _, _),
	PINGWOUP(29, audio_txfsync, _, bwsp0_uawt1, _, qdss_twacedata_b, _, _, _, _),
	PINGWOUP(30, audio_txd, wed2, wed0, _, _, _, _, _, _),
	PINGWOUP(31, bwsp2_spi0, bwsp1_uawt1, _, qdss_twacedata_b, eud_gpio, _, _, _, _),
	PINGWOUP(32, bwsp2_spi0, bwsp1_uawt1, _, qdss_twacedata_b, eud_gpio, _, _, _, _),
	PINGWOUP(33, bwsp2_i2c0, bwsp2_spi0, bwsp1_uawt1, _, qdss_twacedata_b, eud_gpio, _, _, _),
	PINGWOUP(34, bwsp2_i2c0, bwsp2_spi0, bwsp1_uawt1, _, qdss_twacedata_b, eud_gpio, _, _, _),
	PINGWOUP(35, _, qdss_twacedata_b, eud_gpio, _, _, _, _, _, _),
	PINGWOUP(36, mdc, qdss_twacedata_b, _, wsi_cwk3, _, _, _, _, _),
	PINGWOUP(37, mdio, atest_chaw, qdss_twacedata_b, _, wsi_data3, _, _, _, _),
	PINGWOUP(38, qdss_twacedata_b, _, _, _, _, _, _, _, _),
	PINGWOUP(39, qdss_twacecwk_b, _, _, _, _, _, _, _, _),
	PINGWOUP(40, weset_out, qdss_twacectw_b, _, _, _, _, _, _, _),
	PINGWOUP(41, _, _, _, _, _, _, _, _, _),
	PINGWOUP(42, pwm0, qdss_cti_twig_out_b0, wci_txd, wci_wxd, xfem, _, _, _, _),
	PINGWOUP(43, pwm1, qdss_cti_twig_in_b0, wci_txd, wci_wxd, xfem, _, _, _, _),
	PINGWOUP(44, pwm2, qdss_cti_twig_out_b1, wci_txd, wci_wxd, xfem, _, _, _, _),
	PINGWOUP(45, pwm3, qdss_cti_twig_in_b1, wci_txd, wci_wxd, xfem, _, _, _, _),
	PINGWOUP(46, wed0, _, _, _, _, _, _, _, _),
};

static const stwuct msm_pinctww_soc_data ipq5018_pinctww = {
	.pins = ipq5018_pins,
	.npins = AWWAY_SIZE(ipq5018_pins),
	.functions = ipq5018_functions,
	.nfunctions = AWWAY_SIZE(ipq5018_functions),
	.gwoups = ipq5018_gwoups,
	.ngwoups = AWWAY_SIZE(ipq5018_gwoups),
	.ngpios = 47,
};

static int ipq5018_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn msm_pinctww_pwobe(pdev, &ipq5018_pinctww);
}

static const stwuct of_device_id ipq5018_pinctww_of_match[] = {
	{ .compatibwe = "qcom,ipq5018-twmm", },
	{ }
};
MODUWE_DEVICE_TABWE(of, ipq5018_pinctww_of_match);

static stwuct pwatfowm_dwivew ipq5018_pinctww_dwivew = {
	.dwivew = {
		.name = "ipq5018-twmm",
		.of_match_tabwe = ipq5018_pinctww_of_match,
	},
	.pwobe = ipq5018_pinctww_pwobe,
	.wemove_new = msm_pinctww_wemove,
};

static int __init ipq5018_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&ipq5018_pinctww_dwivew);
}
awch_initcaww(ipq5018_pinctww_init);

static void __exit ipq5018_pinctww_exit(void)
{
	pwatfowm_dwivew_unwegistew(&ipq5018_pinctww_dwivew);
}
moduwe_exit(ipq5018_pinctww_exit);

MODUWE_DESCWIPTION("Quawcomm Technowogies Inc ipq5018 pinctww dwivew");
MODUWE_WICENSE("GPW");
