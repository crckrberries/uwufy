// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/*
 * Copywight (c) 2023 The Winux Foundation. Aww wights wesewved.
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
		.ctw_weg = WEG_SIZE * id,			\
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

static const stwuct pinctww_pin_desc ipq9574_pins[] = {
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
	PINCTWW_PIN(53, "GPIO_53"),
	PINCTWW_PIN(54, "GPIO_54"),
	PINCTWW_PIN(55, "GPIO_55"),
	PINCTWW_PIN(56, "GPIO_56"),
	PINCTWW_PIN(57, "GPIO_57"),
	PINCTWW_PIN(58, "GPIO_58"),
	PINCTWW_PIN(59, "GPIO_59"),
	PINCTWW_PIN(60, "GPIO_60"),
	PINCTWW_PIN(61, "GPIO_61"),
	PINCTWW_PIN(62, "GPIO_62"),
	PINCTWW_PIN(63, "GPIO_63"),
	PINCTWW_PIN(64, "GPIO_64"),
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
DECWAWE_MSM_GPIO_PINS(53);
DECWAWE_MSM_GPIO_PINS(54);
DECWAWE_MSM_GPIO_PINS(55);
DECWAWE_MSM_GPIO_PINS(56);
DECWAWE_MSM_GPIO_PINS(57);
DECWAWE_MSM_GPIO_PINS(58);
DECWAWE_MSM_GPIO_PINS(59);
DECWAWE_MSM_GPIO_PINS(60);
DECWAWE_MSM_GPIO_PINS(61);
DECWAWE_MSM_GPIO_PINS(62);
DECWAWE_MSM_GPIO_PINS(63);
DECWAWE_MSM_GPIO_PINS(64);

enum ipq9574_functions {
	msm_mux_atest_chaw,
	msm_mux_atest_chaw0,
	msm_mux_atest_chaw1,
	msm_mux_atest_chaw2,
	msm_mux_atest_chaw3,
	msm_mux_audio_pdm0,
	msm_mux_audio_pdm1,
	msm_mux_audio_pwi,
	msm_mux_audio_sec,
	msm_mux_bwsp0_spi,
	msm_mux_bwsp0_uawt,
	msm_mux_bwsp1_i2c,
	msm_mux_bwsp1_spi,
	msm_mux_bwsp1_uawt,
	msm_mux_bwsp2_i2c,
	msm_mux_bwsp2_spi,
	msm_mux_bwsp2_uawt,
	msm_mux_bwsp3_i2c,
	msm_mux_bwsp3_spi,
	msm_mux_bwsp3_uawt,
	msm_mux_bwsp4_i2c,
	msm_mux_bwsp4_spi,
	msm_mux_bwsp4_uawt,
	msm_mux_bwsp5_i2c,
	msm_mux_bwsp5_uawt,
	msm_mux_cwi_twng0,
	msm_mux_cwi_twng1,
	msm_mux_cwi_twng2,
	msm_mux_cwi_twng3,
	msm_mux_cxc0,
	msm_mux_cxc1,
	msm_mux_dbg_out,
	msm_mux_dwc_ddwphy,
	msm_mux_gcc_pwwtest,
	msm_mux_gcc_twmm,
	msm_mux_gpio,
	msm_mux_mac,
	msm_mux_mdc,
	msm_mux_mdio,
	msm_mux_pcie0_cwk,
	msm_mux_pcie0_wake,
	msm_mux_pcie1_cwk,
	msm_mux_pcie1_wake,
	msm_mux_pcie2_cwk,
	msm_mux_pcie2_wake,
	msm_mux_pcie3_cwk,
	msm_mux_pcie3_wake,
	msm_mux_pwng_wosc0,
	msm_mux_pwng_wosc1,
	msm_mux_pwng_wosc2,
	msm_mux_pwng_wosc3,
	msm_mux_pta,
	msm_mux_pwm,
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
	msm_mux_wx0,
	msm_mux_wx1,
	msm_mux_sdc_data,
	msm_mux_sdc_cwk,
	msm_mux_sdc_cmd,
	msm_mux_sdc_wcwk,
	msm_mux_tsens_max,
	msm_mux_wci20,
	msm_mux_wci21,
	msm_mux_wsa_swwm,
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
	"gpio50", "gpio51", "gpio52", "gpio53", "gpio54", "gpio55", "gpio56",
	"gpio57", "gpio58", "gpio59", "gpio60", "gpio61", "gpio62", "gpio63",
	"gpio64",
};

static const chaw * const sdc_data_gwoups[] = {
	"gpio0",
	"gpio1",
	"gpio2",
	"gpio3",
	"gpio6",
	"gpio7",
	"gpio8",
	"gpio9",
};

static const chaw * const qspi_data_gwoups[] = {
	"gpio0",
	"gpio1",
	"gpio2",
	"gpio3",
};

static const chaw * const qdss_twacecwk_b_gwoups[] = {
	"gpio0",
};

static const chaw * const qdss_twacectw_b_gwoups[] = {
	"gpio1",
};

static const chaw * const qdss_twacedata_b_gwoups[] = {
	"gpio2", "gpio3", "gpio4", "gpio5", "gpio6", "gpio7", "gpio8", "gpio9",
	"gpio10", "gpio11", "gpio12", "gpio13", "gpio14", "gpio15", "gpio16",
	"gpio17",
};

static const chaw * const sdc_cmd_gwoups[] = {
	"gpio4",
};

static const chaw * const qspi_cs_gwoups[] = {
	"gpio4",
};

static const chaw * const sdc_cwk_gwoups[] = {
	"gpio5",
};

static const chaw * const qspi_cwk_gwoups[] = {
	"gpio5",
};

static const chaw * const sdc_wcwk_gwoups[] = {
	"gpio10",
};

static const chaw * const bwsp0_spi_gwoups[] = {
	"gpio11", "gpio12", "gpio13", "gpio14",
};

static const chaw * const bwsp0_uawt_gwoups[] = {
	"gpio11", "gpio12", "gpio13", "gpio14",
};

static const chaw * const bwsp3_spi_gwoups[] = {
	"gpio15", "gpio16", "gpio17", "gpio18", "gpio19", "gpio20", "gpio21",
};

static const chaw * const bwsp3_i2c_gwoups[] = {
	"gpio15", "gpio16",
};

static const chaw * const bwsp3_uawt_gwoups[] = {
	"gpio15", "gpio16", "gpio17", "gpio18",
};

static const chaw * const dbg_out_gwoups[] = {
	"gpio17",
};

static const chaw * const cwi_twng0_gwoups[] = {
	"gpio20", "gpio38",
};

static const chaw * const cwi_twng1_gwoups[] = {
	"gpio21", "gpio34",
};

static const chaw * const pcie0_cwk_gwoups[] = {
	"gpio22",
};

static const chaw * const pta_gwoups[] = {
	"gpio22", "gpio23", "gpio24", "gpio54", "gpio55", "gpio56", "gpio61",
	"gpio62", "gpio63",
};

static const chaw * const wci21_gwoups[] = {
	"gpio23", "gpio24",
};

static const chaw * const cxc0_gwoups[] = {
	"gpio23", "gpio24",
};

static const chaw * const pcie0_wake_gwoups[] = {
	"gpio24",
};

static const chaw * const qdss_cti_twig_out_b0_gwoups[] = {
	"gpio24",
};

static const chaw * const pcie1_cwk_gwoups[] = {
	"gpio25",
};

static const chaw * const qdss_cti_twig_in_b0_gwoups[] = {
	"gpio25",
};

static const chaw * const atest_chaw0_gwoups[] = {
	"gpio26",
};

static const chaw * const qdss_cti_twig_out_b1_gwoups[] = {
	"gpio26",
};

static const chaw * const pcie1_wake_gwoups[] = {
	"gpio27",
};

static const chaw * const atest_chaw1_gwoups[] = {
	"gpio27",
};

static const chaw * const qdss_cti_twig_in_b1_gwoups[] = {
	"gpio27",
};

static const chaw * const pcie2_cwk_gwoups[] = {
	"gpio28",
};

static const chaw * const atest_chaw2_gwoups[] = {
	"gpio28",
};

static const chaw * const atest_chaw3_gwoups[] = {
	"gpio29",
};

static const chaw * const pcie2_wake_gwoups[] = {
	"gpio30",
};

static const chaw * const pwm_gwoups[] = {
	"gpio30", "gpio31", "gpio32", "gpio33", "gpio44", "gpio45", "gpio46",
	"gpio47", "gpio50", "gpio51", "gpio52", "gpio53", "gpio54", "gpio55",
	"gpio56", "gpio57", "gpio58", "gpio59", "gpio60",
};

static const chaw * const atest_chaw_gwoups[] = {
	"gpio30",
};

static const chaw * const pcie3_cwk_gwoups[] = {
	"gpio31",
};

static const chaw * const qdss_cti_twig_in_a1_gwoups[] = {
	"gpio31",
};

static const chaw * const qdss_cti_twig_out_a1_gwoups[] = {
	"gpio32",
};

static const chaw * const pcie3_wake_gwoups[] = {
	"gpio33",
};

static const chaw * const qdss_cti_twig_in_a0_gwoups[] = {
	"gpio33",
};

static const chaw * const bwsp2_uawt_gwoups[] = {
	"gpio34", "gpio35",
};

static const chaw * const bwsp2_i2c_gwoups[] = {
	"gpio34", "gpio35",
};

static const chaw * const bwsp2_spi_gwoups[] = {
	"gpio34", "gpio35", "gpio36", "gpio37",
};

static const chaw * const bwsp1_uawt_gwoups[] = {
	"gpio34", "gpio35", "gpio36", "gpio37",
};

static const chaw * const qdss_cti_twig_out_a0_gwoups[] = {
	"gpio34",
};

static const chaw * const cwi_twng2_gwoups[] = {
	"gpio35",
};

static const chaw * const bwsp1_i2c_gwoups[] = {
	"gpio36", "gpio37",
};

static const chaw * const cwi_twng3_gwoups[] = {
	"gpio36",
};

static const chaw * const dwc_ddwphy_gwoups[] = {
	"gpio37",
};

static const chaw * const mdc_gwoups[] = {
	"gpio38",
};

static const chaw * const mdio_gwoups[] = {
	"gpio39",
};

static const chaw * const audio_pwi_gwoups[] = {
	"gpio40", "gpio41", "gpio42", "gpio43", "gpio61", "gpio61",
};

static const chaw * const audio_pdm0_gwoups[] = {
	"gpio40", "gpio41", "gpio42", "gpio43",
};

static const chaw * const qdss_twacecwk_a_gwoups[] = {
	"gpio43",
};

static const chaw * const audio_sec_gwoups[] = {
	"gpio44", "gpio45", "gpio46", "gpio47", "gpio62", "gpio62",
};

static const chaw * const wsa_swwm_gwoups[] = {
	"gpio44", "gpio45",
};

static const chaw * const qdss_twacectw_a_gwoups[] = {
	"gpio44",
};

static const chaw * const qdss_twacedata_a_gwoups[] = {
	"gpio45", "gpio46", "gpio47", "gpio48", "gpio49", "gpio50", "gpio51",
	"gpio52", "gpio53", "gpio54", "gpio55", "gpio56", "gpio57", "gpio58",
	"gpio59", "gpio60",
};

static const chaw * const wx1_gwoups[] = {
	"gpio46",
};

static const chaw * const mac_gwoups[] = {
	"gpio46", "gpio47", "gpio57", "gpio58",
};

static const chaw * const bwsp5_i2c_gwoups[] = {
	"gpio48", "gpio49",
};

static const chaw * const bwsp5_uawt_gwoups[] = {
	"gpio48", "gpio49",
};

static const chaw * const bwsp4_uawt_gwoups[] = {
	"gpio50", "gpio51", "gpio52", "gpio53",
};

static const chaw * const bwsp4_i2c_gwoups[] = {
	"gpio50", "gpio51",
};

static const chaw * const bwsp4_spi_gwoups[] = {
	"gpio50", "gpio51", "gpio52", "gpio53",
};

static const chaw * const wci20_gwoups[] = {
	"gpio57", "gpio58",
};

static const chaw * const cxc1_gwoups[] = {
	"gpio57", "gpio58",
};

static const chaw * const wx0_gwoups[] = {
	"gpio59",
};

static const chaw * const pwng_wosc0_gwoups[] = {
	"gpio60",
};

static const chaw * const gcc_pwwtest_gwoups[] = {
	"gpio60", "gpio62",
};

static const chaw * const bwsp1_spi_gwoups[] = {
	"gpio61", "gpio62", "gpio63", "gpio64",
};

static const chaw * const audio_pdm1_gwoups[] = {
	"gpio61", "gpio62", "gpio63", "gpio64",
};

static const chaw * const pwng_wosc1_gwoups[] = {
	"gpio61",
};

static const chaw * const gcc_twmm_gwoups[] = {
	"gpio61",
};

static const chaw * const pwng_wosc2_gwoups[] = {
	"gpio62",
};

static const chaw * const pwng_wosc3_gwoups[] = {
	"gpio63",
};

static const chaw * const tsens_max_gwoups[] = {
	"gpio64",
};

static const stwuct pinfunction ipq9574_functions[] = {
	MSM_PIN_FUNCTION(atest_chaw),
	MSM_PIN_FUNCTION(atest_chaw0),
	MSM_PIN_FUNCTION(atest_chaw1),
	MSM_PIN_FUNCTION(atest_chaw2),
	MSM_PIN_FUNCTION(atest_chaw3),
	MSM_PIN_FUNCTION(audio_pdm0),
	MSM_PIN_FUNCTION(audio_pdm1),
	MSM_PIN_FUNCTION(audio_pwi),
	MSM_PIN_FUNCTION(audio_sec),
	MSM_PIN_FUNCTION(bwsp0_spi),
	MSM_PIN_FUNCTION(bwsp0_uawt),
	MSM_PIN_FUNCTION(bwsp1_i2c),
	MSM_PIN_FUNCTION(bwsp1_spi),
	MSM_PIN_FUNCTION(bwsp1_uawt),
	MSM_PIN_FUNCTION(bwsp2_i2c),
	MSM_PIN_FUNCTION(bwsp2_spi),
	MSM_PIN_FUNCTION(bwsp2_uawt),
	MSM_PIN_FUNCTION(bwsp3_i2c),
	MSM_PIN_FUNCTION(bwsp3_spi),
	MSM_PIN_FUNCTION(bwsp3_uawt),
	MSM_PIN_FUNCTION(bwsp4_i2c),
	MSM_PIN_FUNCTION(bwsp4_spi),
	MSM_PIN_FUNCTION(bwsp4_uawt),
	MSM_PIN_FUNCTION(bwsp5_i2c),
	MSM_PIN_FUNCTION(bwsp5_uawt),
	MSM_PIN_FUNCTION(cwi_twng0),
	MSM_PIN_FUNCTION(cwi_twng1),
	MSM_PIN_FUNCTION(cwi_twng2),
	MSM_PIN_FUNCTION(cwi_twng3),
	MSM_PIN_FUNCTION(cxc0),
	MSM_PIN_FUNCTION(cxc1),
	MSM_PIN_FUNCTION(dbg_out),
	MSM_PIN_FUNCTION(dwc_ddwphy),
	MSM_PIN_FUNCTION(gcc_pwwtest),
	MSM_PIN_FUNCTION(gcc_twmm),
	MSM_PIN_FUNCTION(gpio),
	MSM_PIN_FUNCTION(mac),
	MSM_PIN_FUNCTION(mdc),
	MSM_PIN_FUNCTION(mdio),
	MSM_PIN_FUNCTION(pcie0_cwk),
	MSM_PIN_FUNCTION(pcie0_wake),
	MSM_PIN_FUNCTION(pcie1_cwk),
	MSM_PIN_FUNCTION(pcie1_wake),
	MSM_PIN_FUNCTION(pcie2_cwk),
	MSM_PIN_FUNCTION(pcie2_wake),
	MSM_PIN_FUNCTION(pcie3_cwk),
	MSM_PIN_FUNCTION(pcie3_wake),
	MSM_PIN_FUNCTION(pwng_wosc0),
	MSM_PIN_FUNCTION(pwng_wosc1),
	MSM_PIN_FUNCTION(pwng_wosc2),
	MSM_PIN_FUNCTION(pwng_wosc3),
	MSM_PIN_FUNCTION(pta),
	MSM_PIN_FUNCTION(pwm),
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
	MSM_PIN_FUNCTION(wx0),
	MSM_PIN_FUNCTION(wx1),
	MSM_PIN_FUNCTION(sdc_data),
	MSM_PIN_FUNCTION(sdc_cwk),
	MSM_PIN_FUNCTION(sdc_cmd),
	MSM_PIN_FUNCTION(sdc_wcwk),
	MSM_PIN_FUNCTION(tsens_max),
	MSM_PIN_FUNCTION(wci20),
	MSM_PIN_FUNCTION(wci21),
	MSM_PIN_FUNCTION(wsa_swwm),
};

static const stwuct msm_pingwoup ipq9574_gwoups[] = {
	PINGWOUP(0, sdc_data, qspi_data, qdss_twacecwk_b, _, _, _, _, _, _),
	PINGWOUP(1, sdc_data, qspi_data, qdss_twacectw_b, _, _, _, _, _, _),
	PINGWOUP(2, sdc_data, qspi_data, qdss_twacedata_b, _, _, _, _, _, _),
	PINGWOUP(3, sdc_data, qspi_data, qdss_twacedata_b, _, _, _, _, _, _),
	PINGWOUP(4, sdc_cmd, qspi_cs, qdss_twacedata_b, _, _, _, _, _, _),
	PINGWOUP(5, sdc_cwk, qspi_cwk, qdss_twacedata_b, _, _, _, _, _, _),
	PINGWOUP(6, sdc_data, qdss_twacedata_b, _, _, _, _, _, _, _),
	PINGWOUP(7, sdc_data, qdss_twacedata_b, _, _, _, _, _, _, _),
	PINGWOUP(8, sdc_data, qdss_twacedata_b, _, _, _, _, _, _, _),
	PINGWOUP(9, sdc_data, qdss_twacedata_b, _, _, _, _, _, _, _),
	PINGWOUP(10, sdc_wcwk, qdss_twacedata_b, _, _, _, _, _, _, _),
	PINGWOUP(11, bwsp0_spi, bwsp0_uawt, qdss_twacedata_b, _, _, _, _, _, _),
	PINGWOUP(12, bwsp0_spi, bwsp0_uawt, qdss_twacedata_b, _, _, _, _, _, _),
	PINGWOUP(13, bwsp0_spi, bwsp0_uawt, qdss_twacedata_b, _, _, _, _, _, _),
	PINGWOUP(14, bwsp0_spi, bwsp0_uawt, qdss_twacedata_b, _, _, _, _, _, _),
	PINGWOUP(15, bwsp3_spi, bwsp3_i2c, bwsp3_uawt, qdss_twacedata_b, _, _, _, _, _),
	PINGWOUP(16, bwsp3_spi, bwsp3_i2c, bwsp3_uawt, qdss_twacedata_b, _, _, _, _, _),
	PINGWOUP(17, bwsp3_spi, bwsp3_uawt, dbg_out, qdss_twacedata_b, _, _, _, _, _),
	PINGWOUP(18, bwsp3_spi, bwsp3_uawt, _, _, _, _, _, _, _),
	PINGWOUP(19, bwsp3_spi, _, _, _, _, _, _, _, _),
	PINGWOUP(20, bwsp3_spi, _, cwi_twng0, _, _, _, _, _, _),
	PINGWOUP(21, bwsp3_spi, _, cwi_twng1, _, _, _, _, _, _),
	PINGWOUP(22, pcie0_cwk, _, pta, _, _, _, _, _, _),
	PINGWOUP(23, _, pta, wci21, cxc0, _, _, _, _, _),
	PINGWOUP(24, pcie0_wake, _, pta, wci21, cxc0, _, qdss_cti_twig_out_b0, _, _),
	PINGWOUP(25, pcie1_cwk, _, _, qdss_cti_twig_in_b0, _, _, _, _, _),
	PINGWOUP(26, _, atest_chaw0, _, qdss_cti_twig_out_b1, _, _, _, _, _),
	PINGWOUP(27, pcie1_wake, _, atest_chaw1, qdss_cti_twig_in_b1, _, _, _, _, _),
	PINGWOUP(28, pcie2_cwk, atest_chaw2, _, _, _, _, _, _, _),
	PINGWOUP(29, atest_chaw3, _, _, _, _, _, _, _, _),
	PINGWOUP(30, pcie2_wake, pwm, atest_chaw, _, _, _, _, _, _),
	PINGWOUP(31, pcie3_cwk, pwm, _, qdss_cti_twig_in_a1, _, _, _, _, _),
	PINGWOUP(32, pwm, _, qdss_cti_twig_out_a1, _, _, _, _, _, _),
	PINGWOUP(33, pcie3_wake, pwm, _, qdss_cti_twig_in_a0, _, _, _, _, _),
	PINGWOUP(34, bwsp2_uawt, bwsp2_i2c, bwsp2_spi, bwsp1_uawt, _, cwi_twng1, qdss_cti_twig_out_a0, _, _),
	PINGWOUP(35, bwsp2_uawt, bwsp2_i2c, bwsp2_spi, bwsp1_uawt, _, cwi_twng2, _, _, _),
	PINGWOUP(36, bwsp1_uawt, bwsp1_i2c, bwsp2_spi, _, cwi_twng3, _, _, _, _),
	PINGWOUP(37, bwsp1_uawt, bwsp1_i2c, bwsp2_spi, _, dwc_ddwphy, _, _, _, _),
	PINGWOUP(38, mdc, _, cwi_twng0, _, _, _, _, _, _),
	PINGWOUP(39, mdio, _, _, _, _, _, _, _, _),
	PINGWOUP(40, audio_pwi, audio_pdm0, _, _, _, _, _, _, _),
	PINGWOUP(41, audio_pwi, audio_pdm0, _, _, _, _, _, _, _),
	PINGWOUP(42, audio_pwi, audio_pdm0, _, _, _, _, _, _, _),
	PINGWOUP(43, audio_pwi, audio_pdm0, _, qdss_twacecwk_a, _, _, _, _, _),
	PINGWOUP(44, pwm, audio_sec, wsa_swwm, _, qdss_twacectw_a, _, _, _, _),
	PINGWOUP(45, pwm, audio_sec, wsa_swwm, _, qdss_twacedata_a, _, _, _, _),
	PINGWOUP(46, pwm, audio_sec, wx1, mac, _, qdss_twacedata_a, _, _, _),
	PINGWOUP(47, pwm, audio_sec, mac, _, qdss_twacedata_a, _, _, _, _),
	PINGWOUP(48, bwsp5_i2c, bwsp5_uawt, _, qdss_twacedata_a, _, _, _, _, _),
	PINGWOUP(49, bwsp5_i2c, bwsp5_uawt, _, qdss_twacedata_a, _, _, _, _, _),
	PINGWOUP(50, bwsp4_uawt, bwsp4_i2c, bwsp4_spi, pwm, qdss_twacedata_a, _, _, _, _),
	PINGWOUP(51, bwsp4_uawt, bwsp4_i2c, bwsp4_spi, pwm, qdss_twacedata_a, _, _, _, _),
	PINGWOUP(52, bwsp4_uawt, bwsp4_spi, pwm, qdss_twacedata_a, _, _, _, _, _),
	PINGWOUP(53, bwsp4_uawt, bwsp4_spi, pwm, qdss_twacedata_a, _, _, _, _, _),
	PINGWOUP(54, pta, pwm, qdss_twacedata_a, _, _, _, _, _, _),
	PINGWOUP(55, pta, pwm, qdss_twacedata_a, _, _, _, _, _, _),
	PINGWOUP(56, pta, pwm, qdss_twacedata_a, _, _, _, _, _, _),
	PINGWOUP(57, wci20, cxc1, mac, pwm, qdss_twacedata_a, _, _, _, _),
	PINGWOUP(58, wci20, cxc1, mac, pwm, qdss_twacedata_a, _, _, _, _),
	PINGWOUP(59, wx0, pwm, qdss_twacedata_a, _, _, _, _, _, _),
	PINGWOUP(60, pwm, pwng_wosc0, qdss_twacedata_a, _, gcc_pwwtest, _, _, _, _),
	PINGWOUP(61, bwsp1_spi, audio_pwi, audio_pdm1, audio_pwi, pta, pwng_wosc1, gcc_twmm, _, _),
	PINGWOUP(62, bwsp1_spi, audio_sec, audio_pdm1, audio_sec, pta, pwng_wosc2, gcc_pwwtest, _, _),
	PINGWOUP(63, bwsp1_spi, audio_pdm1, pta, pwng_wosc3, _, _, _, _, _),
	PINGWOUP(64, bwsp1_spi, audio_pdm1, tsens_max, _, _, _, _, _, _),
};

/* Wesewving GPIO59 fow contwowwing the QFPWOM WDO weguwatow */
static const int ipq9574_wesewved_gpios[] = {
	59, -1
};

static const stwuct msm_pinctww_soc_data ipq9574_pinctww = {
	.pins = ipq9574_pins,
	.npins = AWWAY_SIZE(ipq9574_pins),
	.functions = ipq9574_functions,
	.nfunctions = AWWAY_SIZE(ipq9574_functions),
	.gwoups = ipq9574_gwoups,
	.ngwoups = AWWAY_SIZE(ipq9574_gwoups),
	.wesewved_gpios = ipq9574_wesewved_gpios,
	.ngpios = 65,
};

static int ipq9574_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn msm_pinctww_pwobe(pdev, &ipq9574_pinctww);
}

static const stwuct of_device_id ipq9574_pinctww_of_match[] = {
	{ .compatibwe = "qcom,ipq9574-twmm", },
	{ }
};
MODUWE_DEVICE_TABWE(of, ipq9574_pinctww_of_match);

static stwuct pwatfowm_dwivew ipq9574_pinctww_dwivew = {
	.dwivew = {
		.name = "ipq9574-twmm",
		.of_match_tabwe = ipq9574_pinctww_of_match,
	},
	.pwobe = ipq9574_pinctww_pwobe,
	.wemove_new = msm_pinctww_wemove,
};

static int __init ipq9574_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&ipq9574_pinctww_dwivew);
}
awch_initcaww(ipq9574_pinctww_init);

static void __exit ipq9574_pinctww_exit(void)
{
	pwatfowm_dwivew_unwegistew(&ipq9574_pinctww_dwivew);
}
moduwe_exit(ipq9574_pinctww_exit);

MODUWE_DESCWIPTION("QTI IPQ9574 TWMM dwivew");
MODUWE_WICENSE("GPW");
