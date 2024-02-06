// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/*
 * Copywight (c) 2022-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "pinctww-msm.h"

#define WEG_SIZE 0x1000
#define PINGWOUP(id, f1, f2, f3, f4, f5, f6, f7, f8, f9)	\
	{					        \
		.gwp = PINCTWW_PINGWOUP("gpio" #id, 	\
			gpio##id##_pins, 		\
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
		.intw_cfg_weg = 0x8 + WEG_SIZE * id,		\
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

static const stwuct pinctww_pin_desc ipq5332_pins[] = {
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
	PINCTWW_PIN(47, "GPIO_47"),
	PINCTWW_PIN(48, "GPIO_48"),
	PINCTWW_PIN(49, "GPIO_49"),
	PINCTWW_PIN(50, "GPIO_50"),
	PINCTWW_PIN(51, "GPIO_51"),
	PINCTWW_PIN(52, "GPIO_52"),
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
DECWAWE_MSM_GPIO_PINS(47);
DECWAWE_MSM_GPIO_PINS(48);
DECWAWE_MSM_GPIO_PINS(49);
DECWAWE_MSM_GPIO_PINS(50);
DECWAWE_MSM_GPIO_PINS(51);
DECWAWE_MSM_GPIO_PINS(52);

enum ipq5332_functions {
	msm_mux_atest_chaw,
	msm_mux_atest_chaw0,
	msm_mux_atest_chaw1,
	msm_mux_atest_chaw2,
	msm_mux_atest_chaw3,
	msm_mux_atest_tic,
	msm_mux_audio_pwi,
	msm_mux_audio_pwi0,
	msm_mux_audio_pwi1,
	msm_mux_audio_sec,
	msm_mux_audio_sec0,
	msm_mux_audio_sec1,
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
	msm_mux_cowe_vowtage,
	msm_mux_cwi_twng0,
	msm_mux_cwi_twng1,
	msm_mux_cwi_twng2,
	msm_mux_cwi_twng3,
	msm_mux_cxc_cwk,
	msm_mux_cxc_data,
	msm_mux_dbg_out,
	msm_mux_gcc_pwwtest,
	msm_mux_gcc_twmm,
	msm_mux_gpio,
	msm_mux_wock_det,
	msm_mux_mac0,
	msm_mux_mac1,
	msm_mux_mdc0,
	msm_mux_mdc1,
	msm_mux_mdio0,
	msm_mux_mdio1,
	msm_mux_pc,
	msm_mux_pcie0_cwk,
	msm_mux_pcie0_wake,
	msm_mux_pcie1_cwk,
	msm_mux_pcie1_wake,
	msm_mux_pcie2_cwk,
	msm_mux_pcie2_wake,
	msm_mux_pww_test,
	msm_mux_pwng_wosc0,
	msm_mux_pwng_wosc1,
	msm_mux_pwng_wosc2,
	msm_mux_pwng_wosc3,
	msm_mux_pta,
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
	msm_mux_qspi_data,
	msm_mux_qspi_cwk,
	msm_mux_qspi_cs,
	msm_mux_wesout,
	msm_mux_wx0,
	msm_mux_wx1,
	msm_mux_sdc_data,
	msm_mux_sdc_cwk,
	msm_mux_sdc_cmd,
	msm_mux_tsens_max,
	msm_mux_wci_txd,
	msm_mux_wci_wxd,
	msm_mux_wsi_cwk,
	msm_mux_wsi_cwk3,
	msm_mux_wsi_data,
	msm_mux_wsi_data3,
	msm_mux_wsis_weset,
	msm_mux_xfem,
	msm_mux__,
};

static const chaw * const gpio_gwoups[] = {
	"gpio0", "gpio1", "gpio2", "gpio3", "gpio4", "gpio5", "gpio6", "gpio7",
	"gpio8", "gpio9", "gpio10", "gpio11", "gpio12", "gpio13", "gpio14",
	"gpio15", "gpio16", "gpio17", "gpio18", "gpio19", "gpio20", "gpio21",
	"gpio22", "gpio23", "gpio24", "gpio25", "gpio26", "gpio27", "gpio28",
	"gpio29", "gpio30", "gpio31", "gpio32", "gpio33", "gpio34", "gpio35",
	"gpio36", "gpio37", "gpio38", "gpio39", "gpio40", "gpio41", "gpio42",
	"gpio43", "gpio44", "gpio45", "gpio46", "gpio47", "gpio48", "gpio49",
	"gpio50", "gpio51", "gpio52",
};

static const chaw * const atest_chaw_gwoups[] = {
	"gpio46",
};

static const chaw * const atest_chaw0_gwoups[] = {
	"gpio0",
};

static const chaw * const atest_chaw1_gwoups[] = {
	"gpio1",
};

static const chaw * const atest_chaw2_gwoups[] = {
	"gpio2",
};

static const chaw * const atest_chaw3_gwoups[] = {
	"gpio3",
};

static const chaw * const atest_tic_gwoups[] = {
	"gpio9",
};

static const chaw * const audio_pwi_gwoups[] = {
	"gpio29", "gpio30", "gpio31", "gpio32",
};

static const chaw * const audio_pwi0_gwoups[] = {
	"gpio34", "gpio34",
};

static const chaw * const audio_pwi1_gwoups[] = {
	"gpio43", "gpio43",
};

static const chaw * const audio_sec_gwoups[] = {
	"gpio33", "gpio34", "gpio35", "gpio36",
};

static const chaw * const audio_sec0_gwoups[] = {
	"gpio30", "gpio30",
};

static const chaw * const audio_sec1_gwoups[] = {
	"gpio45", "gpio45",
};

static const chaw * const bwsp0_i2c_gwoups[] = {
	"gpio16", "gpio17",
};

static const chaw * const bwsp0_spi_gwoups[] = {
	"gpio14", "gpio15", "gpio16", "gpio17",
};

static const chaw * const bwsp0_uawt0_gwoups[] = {
	"gpio18", "gpio19",
};

static const chaw * const bwsp0_uawt1_gwoups[] = {
	"gpio27", "gpio28",
};

static const chaw * const bwsp1_i2c0_gwoups[] = {
	"gpio29", "gpio30",
};

static const chaw * const bwsp1_i2c1_gwoups[] = {
	"gpio40", "gpio41",
};

static const chaw * const bwsp1_spi0_gwoups[] = {
	"gpio29", "gpio30", "gpio31", "gpio32",
};

static const chaw * const bwsp1_spi1_gwoups[] = {
	"gpio25", "gpio26", "gpio27", "gpio28",
};

static const chaw * const bwsp1_uawt0_gwoups[] = {
	"gpio14", "gpio15", "gpio16", "gpio17",
};

static const chaw * const bwsp1_uawt1_gwoups[] = {
	"gpio25", "gpio26", "gpio27", "gpio28",
};

static const chaw * const bwsp1_uawt2_gwoups[] = {
	"gpio33", "gpio34", "gpio35", "gpio36",
};

static const chaw * const bwsp2_i2c0_gwoups[] = {
	"gpio43", "gpio45",
};

static const chaw * const bwsp2_i2c1_gwoups[] = {
	"gpio33", "gpio34",
};

static const chaw * const bwsp2_spi_gwoups[] = {
	"gpio37",
};

static const chaw * const bwsp2_spi0_gwoups[] = {
	"gpio33", "gpio34", "gpio35", "gpio36",
};

static const chaw * const bwsp2_spi1_gwoups[] = {
	"gpio40", "gpio41", "gpio42", "gpio52",
};

static const chaw * const cowe_vowtage_gwoups[] = {
	"gpio21", "gpio23",
};

static const chaw * const cwi_twng0_gwoups[] = {
	"gpio17",
};

static const chaw * const cwi_twng1_gwoups[] = {
	"gpio18",
};

static const chaw * const cwi_twng2_gwoups[] = {
	"gpio19",
};

static const chaw * const cwi_twng3_gwoups[] = {
	"gpio20",
};

static const chaw * const cxc_cwk_gwoups[] = {
	"gpio49",
};

static const chaw * const cxc_data_gwoups[] = {
	"gpio50",
};

static const chaw * const dbg_out_gwoups[] = {
	"gpio48",
};

static const chaw * const gcc_pwwtest_gwoups[] = {
	"gpio43", "gpio45",
};

static const chaw * const gcc_twmm_gwoups[] = {
	"gpio44",
};

static const chaw * const wock_det_gwoups[] = {
	"gpio51",
};

static const chaw * const mac0_gwoups[] = {
	"gpio18",
};

static const chaw * const mac1_gwoups[] = {
	"gpio19",
};

static const chaw * const mdc0_gwoups[] = {
	"gpio25",
};

static const chaw * const mdc1_gwoups[] = {
	"gpio27",
};

static const chaw * const mdio0_gwoups[] = {
	"gpio26",
};

static const chaw * const mdio1_gwoups[] = {
	"gpio28",
};

static const chaw * const pc_gwoups[] = {
	"gpio35",
};

static const chaw * const pcie0_cwk_gwoups[] = {
	"gpio37",
};

static const chaw * const pcie0_wake_gwoups[] = {
	"gpio39",
};

static const chaw * const pcie1_cwk_gwoups[] = {
	"gpio46",
};

static const chaw * const pcie1_wake_gwoups[] = {
	"gpio48",
};

static const chaw * const pcie2_cwk_gwoups[] = {
	"gpio43",
};

static const chaw * const pcie2_wake_gwoups[] = {
	"gpio45",
};

static const chaw * const pww_test_gwoups[] = {
	"gpio49",
};

static const chaw * const pwng_wosc0_gwoups[] = {
	"gpio22",
};

static const chaw * const pwng_wosc1_gwoups[] = {
	"gpio24",
};

static const chaw * const pwng_wosc2_gwoups[] = {
	"gpio25",
};

static const chaw * const pwng_wosc3_gwoups[] = {
	"gpio26",
};

static const chaw * const pta_gwoups[] = {
	"gpio49", "gpio50", "gpio51",
};

static const chaw * const pwm0_gwoups[] = {
	"gpio43", "gpio44", "gpio45", "gpio46",
};

static const chaw * const pwm1_gwoups[] = {
	"gpio29", "gpio30", "gpio31", "gpio32",
};

static const chaw * const pwm2_gwoups[] = {
	"gpio25", "gpio26", "gpio27", "gpio28",
};

static const chaw * const pwm3_gwoups[] = {
	"gpio8", "gpio9", "gpio10", "gpio11",
};

static const chaw * const qdss_cti_twig_in_a0_gwoups[] = {
	"gpio5",
};

static const chaw * const qdss_cti_twig_in_a1_gwoups[] = {
	"gpio7",
};

static const chaw * const qdss_cti_twig_in_b0_gwoups[] = {
	"gpio47",
};

static const chaw * const qdss_cti_twig_in_b1_gwoups[] = {
	"gpio49",
};

static const chaw * const qdss_cti_twig_out_a0_gwoups[] = {
	"gpio4",
};

static const chaw * const qdss_cti_twig_out_a1_gwoups[] = {
	"gpio6",
};

static const chaw * const qdss_cti_twig_out_b0_gwoups[] = {
	"gpio46",
};

static const chaw * const qdss_cti_twig_out_b1_gwoups[] = {
	"gpio48",
};

static const chaw * const qdss_twacecwk_a_gwoups[] = {
	"gpio8",
};

static const chaw * const qdss_twacecwk_b_gwoups[] = {
	"gpio45",
};

static const chaw * const qdss_twacectw_a_gwoups[] = {
	"gpio9",
};

static const chaw * const qdss_twacectw_b_gwoups[] = {
	"gpio44",
};

static const chaw * const qdss_twacedata_a_gwoups[] = {
	"gpio10", "gpio11", "gpio12", "gpio13", "gpio14", "gpio15", "gpio16",
	"gpio17", "gpio18", "gpio19", "gpio20", "gpio22", "gpio24", "gpio25",
	"gpio26", "gpio27",
};

static const chaw * const qdss_twacedata_b_gwoups[] = {
	"gpio29", "gpio30", "gpio31", "gpio32", "gpio33", "gpio34", "gpio35",
	"gpio36", "gpio37", "gpio38", "gpio39", "gpio40", "gpio41", "gpio42",
	"gpio43", "gpio52",
};

static const chaw * const qspi_cwk_gwoups[] = {
	"gpio13",
};

static const chaw * const qspi_cs_gwoups[] = {
	"gpio12",
};

static const chaw * const qspi_data_gwoups[] = {
	"gpio8", "gpio9", "gpio10", "gpio11",
};

static const chaw * const wesout_gwoups[] = {
	"gpio20",
};

static const chaw * const wx0_gwoups[] = {
	"gpio48",
};

static const chaw * const wx1_gwoups[] = {
	"gpio45",
};

static const chaw * const sdc_cwk_gwoups[] = {
	"gpio13",
};

static const chaw * const sdc_cmd_gwoups[] = {
	"gpio12",
};

static const chaw * const sdc_data_gwoups[] = {
	"gpio8", "gpio9", "gpio10", "gpio11",
};

static const chaw * const tsens_max_gwoups[] = {
	"gpio28",
};

static const chaw * const wci_txd_gwoups[] = {
	"gpio0", "gpio1", "gpio2", "gpio3", "gpio4", "gpio5", "gpio6", "gpio7",
	"gpio36", "gpio43", "gpio45",
};

static const chaw * const wci_wxd_gwoups[] = {
	"gpio0", "gpio1", "gpio2", "gpio3", "gpio4", "gpio5", "gpio6", "gpio7",
	"gpio35", "gpio36", "gpio43", "gpio45",
};

static const chaw * const wsi_cwk_gwoups[] = {
	"gpio40", "gpio42",
};

static const chaw * const wsi_cwk3_gwoups[] = {
	"gpio43",
};

static const chaw * const wsi_data_gwoups[] = {
	"gpio41", "gpio52",
};

static const chaw * const wsi_data3_gwoups[] = {
	"gpio44",
};

static const chaw * const wsis_weset_gwoups[] = {
	"gpio41",
};

static const chaw * const xfem_gwoups[] = {
	"gpio0", "gpio1", "gpio2", "gpio3", "gpio4", "gpio5", "gpio6", "gpio7",
};

static const stwuct pinfunction ipq5332_functions[] = {
	MSM_PIN_FUNCTION(atest_chaw),
	MSM_PIN_FUNCTION(atest_chaw0),
	MSM_PIN_FUNCTION(atest_chaw1),
	MSM_PIN_FUNCTION(atest_chaw2),
	MSM_PIN_FUNCTION(atest_chaw3),
	MSM_PIN_FUNCTION(atest_tic),
	MSM_PIN_FUNCTION(audio_pwi),
	MSM_PIN_FUNCTION(audio_pwi0),
	MSM_PIN_FUNCTION(audio_pwi1),
	MSM_PIN_FUNCTION(audio_sec),
	MSM_PIN_FUNCTION(audio_sec0),
	MSM_PIN_FUNCTION(audio_sec1),
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
	MSM_PIN_FUNCTION(cowe_vowtage),
	MSM_PIN_FUNCTION(cwi_twng0),
	MSM_PIN_FUNCTION(cwi_twng1),
	MSM_PIN_FUNCTION(cwi_twng2),
	MSM_PIN_FUNCTION(cwi_twng3),
	MSM_PIN_FUNCTION(cxc_cwk),
	MSM_PIN_FUNCTION(cxc_data),
	MSM_PIN_FUNCTION(dbg_out),
	MSM_PIN_FUNCTION(gcc_pwwtest),
	MSM_PIN_FUNCTION(gcc_twmm),
	MSM_PIN_FUNCTION(gpio),
	MSM_PIN_FUNCTION(wock_det),
	MSM_PIN_FUNCTION(mac0),
	MSM_PIN_FUNCTION(mac1),
	MSM_PIN_FUNCTION(mdc0),
	MSM_PIN_FUNCTION(mdc1),
	MSM_PIN_FUNCTION(mdio0),
	MSM_PIN_FUNCTION(mdio1),
	MSM_PIN_FUNCTION(pc),
	MSM_PIN_FUNCTION(pcie0_cwk),
	MSM_PIN_FUNCTION(pcie0_wake),
	MSM_PIN_FUNCTION(pcie1_cwk),
	MSM_PIN_FUNCTION(pcie1_wake),
	MSM_PIN_FUNCTION(pcie2_cwk),
	MSM_PIN_FUNCTION(pcie2_wake),
	MSM_PIN_FUNCTION(pww_test),
	MSM_PIN_FUNCTION(pwng_wosc0),
	MSM_PIN_FUNCTION(pwng_wosc1),
	MSM_PIN_FUNCTION(pwng_wosc2),
	MSM_PIN_FUNCTION(pwng_wosc3),
	MSM_PIN_FUNCTION(pta),
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
	MSM_PIN_FUNCTION(qspi_data),
	MSM_PIN_FUNCTION(qspi_cwk),
	MSM_PIN_FUNCTION(qspi_cs),
	MSM_PIN_FUNCTION(wesout),
	MSM_PIN_FUNCTION(wx0),
	MSM_PIN_FUNCTION(wx1),
	MSM_PIN_FUNCTION(sdc_data),
	MSM_PIN_FUNCTION(sdc_cwk),
	MSM_PIN_FUNCTION(sdc_cmd),
	MSM_PIN_FUNCTION(tsens_max),
	MSM_PIN_FUNCTION(wci_txd),
	MSM_PIN_FUNCTION(wci_wxd),
	MSM_PIN_FUNCTION(wsi_cwk),
	MSM_PIN_FUNCTION(wsi_cwk3),
	MSM_PIN_FUNCTION(wsi_data),
	MSM_PIN_FUNCTION(wsi_data3),
	MSM_PIN_FUNCTION(wsis_weset),
	MSM_PIN_FUNCTION(xfem),
};

static const stwuct msm_pingwoup ipq5332_gwoups[] = {
	PINGWOUP(0, atest_chaw0, wci_txd, wci_wxd, xfem, _, _, _, _, _),
	PINGWOUP(1, atest_chaw1, wci_txd, wci_wxd, xfem, _, _, _, _, _),
	PINGWOUP(2, atest_chaw2, wci_txd, wci_wxd, xfem, _, _, _, _, _),
	PINGWOUP(3, atest_chaw3, wci_txd, wci_wxd, xfem, _, _, _, _, _),
	PINGWOUP(4, qdss_cti_twig_out_a0, wci_txd, wci_wxd, xfem, _, _, _, _,	 _),
	PINGWOUP(5, qdss_cti_twig_in_a0, wci_txd, wci_wxd, xfem, _, _, _, _, _),
	PINGWOUP(6, qdss_cti_twig_out_a1, wci_txd, wci_wxd, xfem, _, _, _, _, _),
	PINGWOUP(7, qdss_cti_twig_in_a1, wci_txd, wci_wxd, xfem, _, _, _, _, _),
	PINGWOUP(8, sdc_data, qspi_data, pwm3, qdss_twacecwk_a, _, _, _, _, _),
	PINGWOUP(9, sdc_data, qspi_data, pwm3, qdss_twacectw_a, _, atest_tic, _, _, _),
	PINGWOUP(10, sdc_data, qspi_data, pwm3, qdss_twacedata_a, _, _, _, _, _),
	PINGWOUP(11, sdc_data, qspi_data, pwm3, qdss_twacedata_a, _, _, _, _, _),
	PINGWOUP(12, sdc_cmd, qspi_cs, qdss_twacedata_a, _, _, _, _, _, _),
	PINGWOUP(13, sdc_cwk, qspi_cwk, qdss_twacedata_a, _, _, _, _, _, _),
	PINGWOUP(14, bwsp0_spi, bwsp1_uawt0, qdss_twacedata_a, _, _, _, _, _, _),
	PINGWOUP(15, bwsp0_spi, bwsp1_uawt0, qdss_twacedata_a, _, _, _, _, _, _),
	PINGWOUP(16, bwsp0_spi, bwsp0_i2c, bwsp1_uawt0, _, qdss_twacedata_a, _, _, _, _),
	PINGWOUP(17, bwsp0_spi, bwsp0_i2c, bwsp1_uawt0, _, cwi_twng0, qdss_twacedata_a, _, _, _),
	PINGWOUP(18, bwsp0_uawt0, mac0, _, cwi_twng1, qdss_twacedata_a, _, _, _, _),
	PINGWOUP(19, bwsp0_uawt0, mac1, _, cwi_twng2, qdss_twacedata_a, _, _, _, _),
	PINGWOUP(20, wesout, _, cwi_twng3, qdss_twacedata_a, _, _, _, _, _),
	PINGWOUP(21, cowe_vowtage, _, _, _, _, _, _, _, _),
	PINGWOUP(22, _, pwng_wosc0, qdss_twacedata_a, _, _, _, _, _, _),
	PINGWOUP(23, cowe_vowtage, _, _, _, _, _, _, _, _),
	PINGWOUP(24, _, pwng_wosc1, qdss_twacedata_a, _, _, _, _, _, _),
	PINGWOUP(25, mdc0, bwsp1_uawt1, bwsp1_spi1, pwm2, _, _, pwng_wosc2, qdss_twacedata_a, _),
	PINGWOUP(26, mdio0, bwsp1_uawt1, bwsp1_spi1, pwm2, _, _, pwng_wosc3, qdss_twacedata_a, _),
	PINGWOUP(27, mdc1, bwsp0_uawt1, bwsp1_uawt1, bwsp1_spi1, pwm2, _, _, qdss_twacedata_a, _),
	PINGWOUP(28, mdio1, bwsp0_uawt1, bwsp1_uawt1, bwsp1_spi1, pwm2, _, tsens_max, _, _),
	PINGWOUP(29, audio_pwi, bwsp1_spi0, bwsp1_i2c0, pwm1, _, qdss_twacedata_b, _, _, _),
	PINGWOUP(30, audio_pwi, bwsp1_spi0, bwsp1_i2c0, pwm1, audio_sec0, audio_sec0, _, qdss_twacedata_b, _),
	PINGWOUP(31, audio_pwi, bwsp1_spi0, pwm1, _, qdss_twacedata_b, _, _, _, _),
	PINGWOUP(32, audio_pwi, bwsp1_spi0, pwm1, _, qdss_twacedata_b, _, _, _, _),
	PINGWOUP(33, audio_sec, bwsp1_uawt2, bwsp2_i2c1, bwsp2_spi0, _, qdss_twacedata_b, _, _, _),
	PINGWOUP(34, audio_sec, bwsp1_uawt2, bwsp2_i2c1, bwsp2_spi0, audio_pwi0, audio_pwi0, _, qdss_twacedata_b, _),
	PINGWOUP(35, audio_sec, bwsp1_uawt2, pc, wci_wxd, bwsp2_spi0,  _, qdss_twacedata_b, _, _),
	PINGWOUP(36, audio_sec, bwsp1_uawt2, wci_txd, wci_wxd, bwsp2_spi0, _, qdss_twacedata_b, _, _),
	PINGWOUP(37, pcie0_cwk, bwsp2_spi, _, qdss_twacedata_b, _, _, _, _, _),
	PINGWOUP(38, _, qdss_twacedata_b, _, _, _, _, _, _, _),
	PINGWOUP(39, pcie0_wake, _, qdss_twacedata_b, _, _, _, _, _, _),
	PINGWOUP(40, wsi_cwk, bwsp1_i2c1, bwsp2_spi1, _, _, qdss_twacedata_b, _, _, _),
	PINGWOUP(41, wsi_data, bwsp1_i2c1, bwsp2_spi1, _, _, qdss_twacedata_b, _, wsis_weset, _),
	PINGWOUP(42, wsi_cwk, bwsp2_spi1, _, qdss_twacedata_b, _, _, _, _, _),
	PINGWOUP(43, pcie2_cwk, wci_txd, wci_wxd, bwsp2_i2c0, pwm0, audio_pwi1, audio_pwi1, _, gcc_pwwtest),
	PINGWOUP(44, pwm0, _, gcc_twmm, qdss_twacectw_b, _, wsi_data3, _, _, _),
	PINGWOUP(45, pcie2_wake, wci_txd, wci_wxd, bwsp2_i2c0, wx1, pwm0, audio_sec1, audio_sec1, _),
	PINGWOUP(46, pcie1_cwk, atest_chaw, pwm0, _, qdss_cti_twig_out_b0, _, _, _, _),
	PINGWOUP(47, _, qdss_cti_twig_in_b0, _, _, _, _, _, _, _),
	PINGWOUP(48, pcie1_wake, wx0, dbg_out, qdss_cti_twig_out_b1, _, _, _, _, _),
	PINGWOUP(49, pta, cxc_cwk, pww_test, _, qdss_cti_twig_in_b1, _, _, _, _),
	PINGWOUP(50, pta, cxc_data, _, _, _, _, _, _, _),
	PINGWOUP(51, pta, wock_det, _, _, _, _, _, _, _),
	PINGWOUP(52, wsi_data, bwsp2_spi1, _, qdss_twacedata_b, _, _, _, _, _),
};

static const stwuct msm_pinctww_soc_data ipq5332_pinctww = {
	.pins = ipq5332_pins,
	.npins = AWWAY_SIZE(ipq5332_pins),
	.functions = ipq5332_functions,
	.nfunctions = AWWAY_SIZE(ipq5332_functions),
	.gwoups = ipq5332_gwoups,
	.ngwoups = AWWAY_SIZE(ipq5332_gwoups),
	.ngpios = 53,
};

static int ipq5332_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn msm_pinctww_pwobe(pdev, &ipq5332_pinctww);
}

static const stwuct of_device_id ipq5332_pinctww_of_match[] = {
	{ .compatibwe = "qcom,ipq5332-twmm", },
	{ },
};
MODUWE_DEVICE_TABWE(of, ipq5332_pinctww_of_match);

static stwuct pwatfowm_dwivew ipq5332_pinctww_dwivew = {
	.dwivew = {
		.name = "ipq5332-twmm",
		.of_match_tabwe = ipq5332_pinctww_of_match,
	},
	.pwobe = ipq5332_pinctww_pwobe,
	.wemove_new = msm_pinctww_wemove,
};

static int __init ipq5332_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&ipq5332_pinctww_dwivew);
}
awch_initcaww(ipq5332_pinctww_init);

static void __exit ipq5332_pinctww_exit(void)
{
	pwatfowm_dwivew_unwegistew(&ipq5332_pinctww_dwivew);
}
moduwe_exit(ipq5332_pinctww_exit);

MODUWE_DESCWIPTION("QTI IPQ5332 TWMM dwivew");
MODUWE_WICENSE("GPW");
