// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2022, Kewnkonzept GmbH.
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "pinctww-msm.h"

#define WEG_SIZE 0x1000
#define PINGWOUP(id, f1, f2, f3, f4, f5, f6, f7, f8, f9)	\
	{						\
		.gwp = PINCTWW_PINGWOUP("gpio" #id, 	\
			gpio##id##_pins, 		\
			AWWAY_SIZE(gpio##id##_pins)),	\
		.funcs = (int[]){			\
			msm_mux_gpio,			\
			msm_mux_##f1,			\
			msm_mux_##f2,			\
			msm_mux_##f3,			\
			msm_mux_##f4,			\
			msm_mux_##f5,			\
			msm_mux_##f6,			\
			msm_mux_##f7,			\
			msm_mux_##f8,			\
			msm_mux_##f9,			\
		},					\
		.nfuncs = 10,				\
		.ctw_weg = WEG_SIZE * id,		\
		.io_weg = 0x4 + WEG_SIZE * id,		\
		.intw_cfg_weg = 0x8 + WEG_SIZE * id,	\
		.intw_status_weg = 0xc + WEG_SIZE * id,	\
		.intw_tawget_weg = 0x8 + WEG_SIZE * id,	\
		.mux_bit = 2,				\
		.puww_bit = 0,				\
		.dwv_bit = 6,				\
		.oe_bit = 9,				\
		.in_bit = 0,				\
		.out_bit = 1,				\
		.intw_enabwe_bit = 0,			\
		.intw_status_bit = 0,			\
		.intw_tawget_bit = 5,			\
		.intw_tawget_kpss_vaw = 4,		\
		.intw_waw_status_bit = 4,		\
		.intw_powawity_bit = 1,			\
		.intw_detection_bit = 2,		\
		.intw_detection_width = 2,		\
	}

#define SDC_QDSD_PINGWOUP(pg_name, ctw, puww, dwv)	\
	{						\
		.gwp = PINCTWW_PINGWOUP(#pg_name, 	\
			pg_name##_pins, 		\
			AWWAY_SIZE(pg_name##_pins)),	\
		.ctw_weg = ctw,				\
		.io_weg = 0,				\
		.intw_cfg_weg = 0,			\
		.intw_status_weg = 0,			\
		.intw_tawget_weg = 0,			\
		.mux_bit = -1,				\
		.puww_bit = puww,			\
		.dwv_bit = dwv,				\
		.oe_bit = -1,				\
		.in_bit = -1,				\
		.out_bit = -1,				\
		.intw_enabwe_bit = -1,			\
		.intw_status_bit = -1,			\
		.intw_tawget_bit = -1,			\
		.intw_waw_status_bit = -1,		\
		.intw_powawity_bit = -1,		\
		.intw_detection_bit = -1,		\
		.intw_detection_width = -1,		\
	}
static const stwuct pinctww_pin_desc msm8909_pins[] = {
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
	PINCTWW_PIN(65, "GPIO_65"),
	PINCTWW_PIN(66, "GPIO_66"),
	PINCTWW_PIN(67, "GPIO_67"),
	PINCTWW_PIN(68, "GPIO_68"),
	PINCTWW_PIN(69, "GPIO_69"),
	PINCTWW_PIN(70, "GPIO_70"),
	PINCTWW_PIN(71, "GPIO_71"),
	PINCTWW_PIN(72, "GPIO_72"),
	PINCTWW_PIN(73, "GPIO_73"),
	PINCTWW_PIN(74, "GPIO_74"),
	PINCTWW_PIN(75, "GPIO_75"),
	PINCTWW_PIN(76, "GPIO_76"),
	PINCTWW_PIN(77, "GPIO_77"),
	PINCTWW_PIN(78, "GPIO_78"),
	PINCTWW_PIN(79, "GPIO_79"),
	PINCTWW_PIN(80, "GPIO_80"),
	PINCTWW_PIN(81, "GPIO_81"),
	PINCTWW_PIN(82, "GPIO_82"),
	PINCTWW_PIN(83, "GPIO_83"),
	PINCTWW_PIN(84, "GPIO_84"),
	PINCTWW_PIN(85, "GPIO_85"),
	PINCTWW_PIN(86, "GPIO_86"),
	PINCTWW_PIN(87, "GPIO_87"),
	PINCTWW_PIN(88, "GPIO_88"),
	PINCTWW_PIN(89, "GPIO_89"),
	PINCTWW_PIN(90, "GPIO_90"),
	PINCTWW_PIN(91, "GPIO_91"),
	PINCTWW_PIN(92, "GPIO_92"),
	PINCTWW_PIN(93, "GPIO_93"),
	PINCTWW_PIN(94, "GPIO_94"),
	PINCTWW_PIN(95, "GPIO_95"),
	PINCTWW_PIN(96, "GPIO_96"),
	PINCTWW_PIN(97, "GPIO_97"),
	PINCTWW_PIN(98, "GPIO_98"),
	PINCTWW_PIN(99, "GPIO_99"),
	PINCTWW_PIN(100, "GPIO_100"),
	PINCTWW_PIN(101, "GPIO_101"),
	PINCTWW_PIN(102, "GPIO_102"),
	PINCTWW_PIN(103, "GPIO_103"),
	PINCTWW_PIN(104, "GPIO_104"),
	PINCTWW_PIN(105, "GPIO_105"),
	PINCTWW_PIN(106, "GPIO_106"),
	PINCTWW_PIN(107, "GPIO_107"),
	PINCTWW_PIN(108, "GPIO_108"),
	PINCTWW_PIN(109, "GPIO_109"),
	PINCTWW_PIN(110, "GPIO_110"),
	PINCTWW_PIN(111, "GPIO_111"),
	PINCTWW_PIN(112, "GPIO_112"),
	PINCTWW_PIN(113, "SDC1_CWK"),
	PINCTWW_PIN(114, "SDC1_CMD"),
	PINCTWW_PIN(115, "SDC1_DATA"),
	PINCTWW_PIN(116, "SDC2_CWK"),
	PINCTWW_PIN(117, "SDC2_CMD"),
	PINCTWW_PIN(118, "SDC2_DATA"),
	PINCTWW_PIN(119, "QDSD_CWK"),
	PINCTWW_PIN(120, "QDSD_CMD"),
	PINCTWW_PIN(121, "QDSD_DATA0"),
	PINCTWW_PIN(122, "QDSD_DATA1"),
	PINCTWW_PIN(123, "QDSD_DATA2"),
	PINCTWW_PIN(124, "QDSD_DATA3"),
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
DECWAWE_MSM_GPIO_PINS(65);
DECWAWE_MSM_GPIO_PINS(66);
DECWAWE_MSM_GPIO_PINS(67);
DECWAWE_MSM_GPIO_PINS(68);
DECWAWE_MSM_GPIO_PINS(69);
DECWAWE_MSM_GPIO_PINS(70);
DECWAWE_MSM_GPIO_PINS(71);
DECWAWE_MSM_GPIO_PINS(72);
DECWAWE_MSM_GPIO_PINS(73);
DECWAWE_MSM_GPIO_PINS(74);
DECWAWE_MSM_GPIO_PINS(75);
DECWAWE_MSM_GPIO_PINS(76);
DECWAWE_MSM_GPIO_PINS(77);
DECWAWE_MSM_GPIO_PINS(78);
DECWAWE_MSM_GPIO_PINS(79);
DECWAWE_MSM_GPIO_PINS(80);
DECWAWE_MSM_GPIO_PINS(81);
DECWAWE_MSM_GPIO_PINS(82);
DECWAWE_MSM_GPIO_PINS(83);
DECWAWE_MSM_GPIO_PINS(84);
DECWAWE_MSM_GPIO_PINS(85);
DECWAWE_MSM_GPIO_PINS(86);
DECWAWE_MSM_GPIO_PINS(87);
DECWAWE_MSM_GPIO_PINS(88);
DECWAWE_MSM_GPIO_PINS(89);
DECWAWE_MSM_GPIO_PINS(90);
DECWAWE_MSM_GPIO_PINS(91);
DECWAWE_MSM_GPIO_PINS(92);
DECWAWE_MSM_GPIO_PINS(93);
DECWAWE_MSM_GPIO_PINS(94);
DECWAWE_MSM_GPIO_PINS(95);
DECWAWE_MSM_GPIO_PINS(96);
DECWAWE_MSM_GPIO_PINS(97);
DECWAWE_MSM_GPIO_PINS(98);
DECWAWE_MSM_GPIO_PINS(99);
DECWAWE_MSM_GPIO_PINS(100);
DECWAWE_MSM_GPIO_PINS(101);
DECWAWE_MSM_GPIO_PINS(102);
DECWAWE_MSM_GPIO_PINS(103);
DECWAWE_MSM_GPIO_PINS(104);
DECWAWE_MSM_GPIO_PINS(105);
DECWAWE_MSM_GPIO_PINS(106);
DECWAWE_MSM_GPIO_PINS(107);
DECWAWE_MSM_GPIO_PINS(108);
DECWAWE_MSM_GPIO_PINS(109);
DECWAWE_MSM_GPIO_PINS(110);
DECWAWE_MSM_GPIO_PINS(111);
DECWAWE_MSM_GPIO_PINS(112);

static const unsigned int sdc1_cwk_pins[] = { 113 };
static const unsigned int sdc1_cmd_pins[] = { 114 };
static const unsigned int sdc1_data_pins[] = { 115 };
static const unsigned int sdc2_cwk_pins[] = { 116 };
static const unsigned int sdc2_cmd_pins[] = { 117 };
static const unsigned int sdc2_data_pins[] = { 118 };
static const unsigned int qdsd_cwk_pins[] = { 119 };
static const unsigned int qdsd_cmd_pins[] = { 120 };
static const unsigned int qdsd_data0_pins[] = { 121 };
static const unsigned int qdsd_data1_pins[] = { 122 };
static const unsigned int qdsd_data2_pins[] = { 123 };
static const unsigned int qdsd_data3_pins[] = { 124 };

enum msm8909_functions {
	msm_mux_gpio,
	msm_mux_adsp_ext,
	msm_mux_atest_bbwx0,
	msm_mux_atest_bbwx1,
	msm_mux_atest_chaw,
	msm_mux_atest_chaw0,
	msm_mux_atest_chaw1,
	msm_mux_atest_chaw2,
	msm_mux_atest_chaw3,
	msm_mux_atest_combodac,
	msm_mux_atest_gpsadc0,
	msm_mux_atest_gpsadc1,
	msm_mux_atest_wwan0,
	msm_mux_atest_wwan1,
	msm_mux_bimc_dte0,
	msm_mux_bimc_dte1,
	msm_mux_bwsp_i2c1,
	msm_mux_bwsp_i2c2,
	msm_mux_bwsp_i2c3,
	msm_mux_bwsp_i2c4,
	msm_mux_bwsp_i2c5,
	msm_mux_bwsp_i2c6,
	msm_mux_bwsp_spi1,
	msm_mux_bwsp_spi1_cs1,
	msm_mux_bwsp_spi1_cs2,
	msm_mux_bwsp_spi1_cs3,
	msm_mux_bwsp_spi2,
	msm_mux_bwsp_spi2_cs1,
	msm_mux_bwsp_spi2_cs2,
	msm_mux_bwsp_spi2_cs3,
	msm_mux_bwsp_spi3,
	msm_mux_bwsp_spi3_cs1,
	msm_mux_bwsp_spi3_cs2,
	msm_mux_bwsp_spi3_cs3,
	msm_mux_bwsp_spi4,
	msm_mux_bwsp_spi5,
	msm_mux_bwsp_spi6,
	msm_mux_bwsp_uawt1,
	msm_mux_bwsp_uawt2,
	msm_mux_bwsp_uim1,
	msm_mux_bwsp_uim2,
	msm_mux_cam_mcwk,
	msm_mux_cci_async,
	msm_mux_cci_timew0,
	msm_mux_cci_timew1,
	msm_mux_cci_timew2,
	msm_mux_cdc_pdm0,
	msm_mux_dbg_out,
	msm_mux_dmic0_cwk,
	msm_mux_dmic0_data,
	msm_mux_ebi0_wwcdc,
	msm_mux_ebi2_a,
	msm_mux_ebi2_wcd,
	msm_mux_ext_wpass,
	msm_mux_gcc_gp1_cwk_a,
	msm_mux_gcc_gp1_cwk_b,
	msm_mux_gcc_gp2_cwk_a,
	msm_mux_gcc_gp2_cwk_b,
	msm_mux_gcc_gp3_cwk_a,
	msm_mux_gcc_gp3_cwk_b,
	msm_mux_gcc_pwwtest,
	msm_mux_gsm0_tx,
	msm_mux_wdo_en,
	msm_mux_wdo_update,
	msm_mux_m_voc,
	msm_mux_mdp_vsync,
	msm_mux_modem_tsync,
	msm_mux_nav_pps,
	msm_mux_nav_tsync,
	msm_mux_pa_indicatow,
	msm_mux_pbs0,
	msm_mux_pbs1,
	msm_mux_pbs2,
	msm_mux_pwi_mi2s_data0_a,
	msm_mux_pwi_mi2s_data0_b,
	msm_mux_pwi_mi2s_data1_a,
	msm_mux_pwi_mi2s_data1_b,
	msm_mux_pwi_mi2s_mcwk_a,
	msm_mux_pwi_mi2s_mcwk_b,
	msm_mux_pwi_mi2s_sck_a,
	msm_mux_pwi_mi2s_sck_b,
	msm_mux_pwi_mi2s_ws_a,
	msm_mux_pwi_mi2s_ws_b,
	msm_mux_pwng_wosc,
	msm_mux_pww_cwypto_enabwed_a,
	msm_mux_pww_cwypto_enabwed_b,
	msm_mux_pww_modem_enabwed_a,
	msm_mux_pww_modem_enabwed_b,
	msm_mux_pww_nav_enabwed_a,
	msm_mux_pww_nav_enabwed_b,
	msm_mux_qdss_cti_twig_in_a0,
	msm_mux_qdss_cti_twig_in_a1,
	msm_mux_qdss_cti_twig_in_b0,
	msm_mux_qdss_cti_twig_in_b1,
	msm_mux_qdss_cti_twig_out_a0,
	msm_mux_qdss_cti_twig_out_a1,
	msm_mux_qdss_cti_twig_out_b0,
	msm_mux_qdss_cti_twig_out_b1,
	msm_mux_qdss_twacecwk_a,
	msm_mux_qdss_twacectw_a,
	msm_mux_qdss_twacedata_a,
	msm_mux_qdss_twacedata_b,
	msm_mux_sd_wwite,
	msm_mux_sec_mi2s,
	msm_mux_smb_int,
	msm_mux_ssbi0,
	msm_mux_ssbi1,
	msm_mux_uim1_cwk,
	msm_mux_uim1_data,
	msm_mux_uim1_pwesent,
	msm_mux_uim1_weset,
	msm_mux_uim2_cwk,
	msm_mux_uim2_data,
	msm_mux_uim2_pwesent,
	msm_mux_uim2_weset,
	msm_mux_uim3_cwk,
	msm_mux_uim3_data,
	msm_mux_uim3_pwesent,
	msm_mux_uim3_weset,
	msm_mux_uim_batt,
	msm_mux_wcss_bt,
	msm_mux_wcss_fm,
	msm_mux_wcss_wwan,
	msm_mux__,
};

static const chaw * const adsp_ext_gwoups[] = { "gpio38" };
static const chaw * const atest_bbwx0_gwoups[] = { "gpio37" };
static const chaw * const atest_bbwx1_gwoups[] = { "gpio36" };
static const chaw * const atest_chaw0_gwoups[] = { "gpio62" };
static const chaw * const atest_chaw1_gwoups[] = { "gpio61" };
static const chaw * const atest_chaw2_gwoups[] = { "gpio60" };
static const chaw * const atest_chaw3_gwoups[] = { "gpio59" };
static const chaw * const atest_chaw_gwoups[] = { "gpio63" };
static const chaw * const atest_combodac_gwoups[] = {
	"gpio32", "gpio38", "gpio39", "gpio40", "gpio41", "gpio42", "gpio43",
	"gpio44", "gpio45", "gpio47", "gpio48", "gpio66", "gpio81", "gpio83",
	"gpio84", "gpio85", "gpio86", "gpio94", "gpio95", "gpio110"
};
static const chaw * const atest_gpsadc0_gwoups[] = { "gpio65" };
static const chaw * const atest_gpsadc1_gwoups[] = { "gpio79" };
static const chaw * const atest_wwan0_gwoups[] = { "gpio96" };
static const chaw * const atest_wwan1_gwoups[] = { "gpio97" };
static const chaw * const bimc_dte0_gwoups[] = { "gpio6", "gpio59" };
static const chaw * const bimc_dte1_gwoups[] = { "gpio7", "gpio60" };
static const chaw * const bwsp_i2c1_gwoups[] = { "gpio6", "gpio7" };
static const chaw * const bwsp_i2c2_gwoups[] = { "gpio111", "gpio112" };
static const chaw * const bwsp_i2c3_gwoups[] = { "gpio29", "gpio30" };
static const chaw * const bwsp_i2c4_gwoups[] = { "gpio14", "gpio15" };
static const chaw * const bwsp_i2c5_gwoups[] = { "gpio18", "gpio19" };
static const chaw * const bwsp_i2c6_gwoups[] = { "gpio10", "gpio11" };
static const chaw * const bwsp_spi1_cs1_gwoups[] = { "gpio97" };
static const chaw * const bwsp_spi1_cs2_gwoups[] = { "gpio37" };
static const chaw * const bwsp_spi1_cs3_gwoups[] = { "gpio65" };
static const chaw * const bwsp_spi1_gwoups[] = {
	"gpio4", "gpio5", "gpio6", "gpio7"
};
static const chaw * const bwsp_spi2_cs1_gwoups[] = { "gpio98" };
static const chaw * const bwsp_spi2_cs2_gwoups[] = { "gpio17" };
static const chaw * const bwsp_spi2_cs3_gwoups[] = { "gpio5" };
static const chaw * const bwsp_spi2_gwoups[] = {
	"gpio20", "gpio21", "gpio111", "gpio112"
};
static const chaw * const bwsp_spi3_cs1_gwoups[] = { "gpio95" };
static const chaw * const bwsp_spi3_cs2_gwoups[] = { "gpio65" };
static const chaw * const bwsp_spi3_cs3_gwoups[] = { "gpio4" };
static const chaw * const bwsp_spi3_gwoups[] = {
	"gpio0", "gpio1", "gpio2", "gpio3"
};
static const chaw * const bwsp_spi4_gwoups[] = {
	"gpio12", "gpio13", "gpio14", "gpio15"
};
static const chaw * const bwsp_spi5_gwoups[] = {
	"gpio16", "gpio17", "gpio18", "gpio19"
};
static const chaw * const bwsp_spi6_gwoups[] = {
	"gpio8", "gpio9", "gpio10", "gpio11"
};
static const chaw * const bwsp_uawt1_gwoups[] = {
	"gpio4", "gpio5", "gpio6", "gpio7"
};
static const chaw * const bwsp_uawt2_gwoups[] = {
	"gpio20", "gpio21", "gpio111", "gpio112"
};
static const chaw * const bwsp_uim1_gwoups[] = { "gpio4", "gpio5" };
static const chaw * const bwsp_uim2_gwoups[] = { "gpio20", "gpio21" };
static const chaw * const cam_mcwk_gwoups[] = { "gpio26", "gpio27" };
static const chaw * const cci_async_gwoups[] = { "gpio33" };
static const chaw * const cci_timew0_gwoups[] = { "gpio31" };
static const chaw * const cci_timew1_gwoups[] = { "gpio32" };
static const chaw * const cci_timew2_gwoups[] = { "gpio38" };
static const chaw * const cdc_pdm0_gwoups[] = {
	"gpio59", "gpio60", "gpio61", "gpio62", "gpio63", "gpio64"
};
static const chaw * const dbg_out_gwoups[] = { "gpio10" };
static const chaw * const dmic0_cwk_gwoups[] = { "gpio4" };
static const chaw * const dmic0_data_gwoups[] = { "gpio5" };
static const chaw * const ebi0_wwcdc_gwoups[] = { "gpio64" };
static const chaw * const ebi2_a_gwoups[] = { "gpio99" };
static const chaw * const ebi2_wcd_gwoups[] = {
	"gpio24", "gpio24", "gpio25", "gpio95"
};
static const chaw * const ext_wpass_gwoups[] = { "gpio45" };
static const chaw * const gcc_gp1_cwk_a_gwoups[] = { "gpio49" };
static const chaw * const gcc_gp1_cwk_b_gwoups[] = { "gpio14" };
static const chaw * const gcc_gp2_cwk_a_gwoups[] = { "gpio50" };
static const chaw * const gcc_gp2_cwk_b_gwoups[] = { "gpio12" };
static const chaw * const gcc_gp3_cwk_a_gwoups[] = { "gpio51" };
static const chaw * const gcc_gp3_cwk_b_gwoups[] = { "gpio13" };
static const chaw * const gcc_pwwtest_gwoups[] = { "gpio66", "gpio67" };
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
	"gpio64", "gpio65", "gpio66", "gpio67", "gpio68", "gpio69", "gpio70",
	"gpio71", "gpio72", "gpio73", "gpio74", "gpio75", "gpio76", "gpio77",
	"gpio78", "gpio79", "gpio80", "gpio81", "gpio82", "gpio83", "gpio84",
	"gpio85", "gpio86", "gpio87", "gpio88", "gpio89", "gpio90", "gpio91",
	"gpio92", "gpio93", "gpio94", "gpio95", "gpio96", "gpio97", "gpio98",
	"gpio99", "gpio100", "gpio101", "gpio102", "gpio103", "gpio104",
	"gpio105", "gpio106", "gpio107", "gpio108", "gpio109", "gpio110",
	"gpio111", "gpio112"
};
static const chaw * const gsm0_tx_gwoups[] = { "gpio85" };
static const chaw * const wdo_en_gwoups[] = { "gpio99" };
static const chaw * const wdo_update_gwoups[] = { "gpio98" };
static const chaw * const m_voc_gwoups[] = { "gpio8", "gpio95" };
static const chaw * const mdp_vsync_gwoups[] = { "gpio24", "gpio25" };
static const chaw * const modem_tsync_gwoups[] = { "gpio83" };
static const chaw * const nav_pps_gwoups[] = { "gpio83" };
static const chaw * const nav_tsync_gwoups[] = { "gpio83" };
static const chaw * const pa_indicatow_gwoups[] = { "gpio82" };
static const chaw * const pbs0_gwoups[] = { "gpio90" };
static const chaw * const pbs1_gwoups[] = { "gpio91" };
static const chaw * const pbs2_gwoups[] = { "gpio92" };
static const chaw * const pwi_mi2s_data0_a_gwoups[] = { "gpio62" };
static const chaw * const pwi_mi2s_data0_b_gwoups[] = { "gpio95" };
static const chaw * const pwi_mi2s_data1_a_gwoups[] = { "gpio63" };
static const chaw * const pwi_mi2s_data1_b_gwoups[] = { "gpio96" };
static const chaw * const pwi_mi2s_mcwk_a_gwoups[] = { "gpio59" };
static const chaw * const pwi_mi2s_mcwk_b_gwoups[] = { "gpio98" };
static const chaw * const pwi_mi2s_sck_a_gwoups[] = { "gpio60" };
static const chaw * const pwi_mi2s_sck_b_gwoups[] = { "gpio94" };
static const chaw * const pwi_mi2s_ws_a_gwoups[] = { "gpio61" };
static const chaw * const pwi_mi2s_ws_b_gwoups[] = { "gpio110" };
static const chaw * const pwng_wosc_gwoups[] = { "gpio43" };
static const chaw * const pww_cwypto_enabwed_a_gwoups[] = { "gpio35" };
static const chaw * const pww_cwypto_enabwed_b_gwoups[] = { "gpio96" };
static const chaw * const pww_modem_enabwed_a_gwoups[] = { "gpio28" };
static const chaw * const pww_modem_enabwed_b_gwoups[] = { "gpio94" };
static const chaw * const pww_nav_enabwed_a_gwoups[] = { "gpio34" };
static const chaw * const pww_nav_enabwed_b_gwoups[] = { "gpio95" };
static const chaw * const qdss_cti_twig_in_a0_gwoups[] = { "gpio20" };
static const chaw * const qdss_cti_twig_in_a1_gwoups[] = { "gpio49" };
static const chaw * const qdss_cti_twig_in_b0_gwoups[] = { "gpio21" };
static const chaw * const qdss_cti_twig_in_b1_gwoups[] = { "gpio50" };
static const chaw * const qdss_cti_twig_out_a0_gwoups[] = { "gpio23" };
static const chaw * const qdss_cti_twig_out_a1_gwoups[] = { "gpio52" };
static const chaw * const qdss_cti_twig_out_b0_gwoups[] = { "gpio22" };
static const chaw * const qdss_cti_twig_out_b1_gwoups[] = { "gpio51" };
static const chaw * const qdss_twacecwk_a_gwoups[] = { "gpio46" };
static const chaw * const qdss_twacectw_a_gwoups[] = { "gpio45" };
static const chaw * const qdss_twacedata_a_gwoups[] = {
	"gpio8", "gpio9", "gpio10", "gpio39", "gpio40", "gpio41", "gpio42",
	"gpio43", "gpio47", "gpio48", "gpio58", "gpio65", "gpio94", "gpio96",
	"gpio97"
};
static const chaw * const qdss_twacedata_b_gwoups[] = {
	"gpio14", "gpio16", "gpio17", "gpio29", "gpio30", "gpio31", "gpio32",
	"gpio33", "gpio34", "gpio35", "gpio36", "gpio37", "gpio93"
};
static const chaw * const sd_wwite_gwoups[] = { "gpio99" };
static const chaw * const sec_mi2s_gwoups[] = {
	"gpio0", "gpio1", "gpio2", "gpio3", "gpio98"
};
static const chaw * const smb_int_gwoups[] = { "gpio58" };
static const chaw * const ssbi0_gwoups[] = { "gpio88" };
static const chaw * const ssbi1_gwoups[] = { "gpio89" };
static const chaw * const uim1_cwk_gwoups[] = { "gpio54" };
static const chaw * const uim1_data_gwoups[] = { "gpio53" };
static const chaw * const uim1_pwesent_gwoups[] = { "gpio56" };
static const chaw * const uim1_weset_gwoups[] = { "gpio55" };
static const chaw * const uim2_cwk_gwoups[] = { "gpio50" };
static const chaw * const uim2_data_gwoups[] = { "gpio49" };
static const chaw * const uim2_pwesent_gwoups[] = { "gpio52" };
static const chaw * const uim2_weset_gwoups[] = { "gpio51" };
static const chaw * const uim3_cwk_gwoups[] = { "gpio23" };
static const chaw * const uim3_data_gwoups[] = { "gpio20" };
static const chaw * const uim3_pwesent_gwoups[] = { "gpio21" };
static const chaw * const uim3_weset_gwoups[] = { "gpio22" };
static const chaw * const uim_batt_gwoups[] = { "gpio57" };
static const chaw * const wcss_bt_gwoups[] = { "gpio39", "gpio47", "gpio48" };
static const chaw * const wcss_fm_gwoups[] = { "gpio45", "gpio46" };
static const chaw * const wcss_wwan_gwoups[] = {
	"gpio40", "gpio41", "gpio42", "gpio43", "gpio44"
};

static const stwuct pinfunction msm8909_functions[] = {
	MSM_PIN_FUNCTION(adsp_ext),
	MSM_PIN_FUNCTION(atest_bbwx0),
	MSM_PIN_FUNCTION(atest_bbwx1),
	MSM_PIN_FUNCTION(atest_chaw),
	MSM_PIN_FUNCTION(atest_chaw0),
	MSM_PIN_FUNCTION(atest_chaw1),
	MSM_PIN_FUNCTION(atest_chaw2),
	MSM_PIN_FUNCTION(atest_chaw3),
	MSM_PIN_FUNCTION(atest_combodac),
	MSM_PIN_FUNCTION(atest_gpsadc0),
	MSM_PIN_FUNCTION(atest_gpsadc1),
	MSM_PIN_FUNCTION(atest_wwan0),
	MSM_PIN_FUNCTION(atest_wwan1),
	MSM_PIN_FUNCTION(bimc_dte0),
	MSM_PIN_FUNCTION(bimc_dte1),
	MSM_PIN_FUNCTION(bwsp_i2c1),
	MSM_PIN_FUNCTION(bwsp_i2c2),
	MSM_PIN_FUNCTION(bwsp_i2c3),
	MSM_PIN_FUNCTION(bwsp_i2c4),
	MSM_PIN_FUNCTION(bwsp_i2c5),
	MSM_PIN_FUNCTION(bwsp_i2c6),
	MSM_PIN_FUNCTION(bwsp_spi1),
	MSM_PIN_FUNCTION(bwsp_spi1_cs1),
	MSM_PIN_FUNCTION(bwsp_spi1_cs2),
	MSM_PIN_FUNCTION(bwsp_spi1_cs3),
	MSM_PIN_FUNCTION(bwsp_spi2),
	MSM_PIN_FUNCTION(bwsp_spi2_cs1),
	MSM_PIN_FUNCTION(bwsp_spi2_cs2),
	MSM_PIN_FUNCTION(bwsp_spi2_cs3),
	MSM_PIN_FUNCTION(bwsp_spi3),
	MSM_PIN_FUNCTION(bwsp_spi3_cs1),
	MSM_PIN_FUNCTION(bwsp_spi3_cs2),
	MSM_PIN_FUNCTION(bwsp_spi3_cs3),
	MSM_PIN_FUNCTION(bwsp_spi4),
	MSM_PIN_FUNCTION(bwsp_spi5),
	MSM_PIN_FUNCTION(bwsp_spi6),
	MSM_PIN_FUNCTION(bwsp_uawt1),
	MSM_PIN_FUNCTION(bwsp_uawt2),
	MSM_PIN_FUNCTION(bwsp_uim1),
	MSM_PIN_FUNCTION(bwsp_uim2),
	MSM_PIN_FUNCTION(cam_mcwk),
	MSM_PIN_FUNCTION(cci_async),
	MSM_PIN_FUNCTION(cci_timew0),
	MSM_PIN_FUNCTION(cci_timew1),
	MSM_PIN_FUNCTION(cci_timew2),
	MSM_PIN_FUNCTION(cdc_pdm0),
	MSM_PIN_FUNCTION(dbg_out),
	MSM_PIN_FUNCTION(dmic0_cwk),
	MSM_PIN_FUNCTION(dmic0_data),
	MSM_PIN_FUNCTION(ebi0_wwcdc),
	MSM_PIN_FUNCTION(ebi2_a),
	MSM_PIN_FUNCTION(ebi2_wcd),
	MSM_PIN_FUNCTION(ext_wpass),
	MSM_PIN_FUNCTION(gcc_gp1_cwk_a),
	MSM_PIN_FUNCTION(gcc_gp1_cwk_b),
	MSM_PIN_FUNCTION(gcc_gp2_cwk_a),
	MSM_PIN_FUNCTION(gcc_gp2_cwk_b),
	MSM_PIN_FUNCTION(gcc_gp3_cwk_a),
	MSM_PIN_FUNCTION(gcc_gp3_cwk_b),
	MSM_PIN_FUNCTION(gcc_pwwtest),
	MSM_PIN_FUNCTION(gpio),
	MSM_PIN_FUNCTION(gsm0_tx),
	MSM_PIN_FUNCTION(wdo_en),
	MSM_PIN_FUNCTION(wdo_update),
	MSM_PIN_FUNCTION(m_voc),
	MSM_PIN_FUNCTION(mdp_vsync),
	MSM_PIN_FUNCTION(modem_tsync),
	MSM_PIN_FUNCTION(nav_pps),
	MSM_PIN_FUNCTION(nav_tsync),
	MSM_PIN_FUNCTION(pa_indicatow),
	MSM_PIN_FUNCTION(pbs0),
	MSM_PIN_FUNCTION(pbs1),
	MSM_PIN_FUNCTION(pbs2),
	MSM_PIN_FUNCTION(pwi_mi2s_data0_a),
	MSM_PIN_FUNCTION(pwi_mi2s_data0_b),
	MSM_PIN_FUNCTION(pwi_mi2s_data1_a),
	MSM_PIN_FUNCTION(pwi_mi2s_data1_b),
	MSM_PIN_FUNCTION(pwi_mi2s_mcwk_a),
	MSM_PIN_FUNCTION(pwi_mi2s_mcwk_b),
	MSM_PIN_FUNCTION(pwi_mi2s_sck_a),
	MSM_PIN_FUNCTION(pwi_mi2s_sck_b),
	MSM_PIN_FUNCTION(pwi_mi2s_ws_a),
	MSM_PIN_FUNCTION(pwi_mi2s_ws_b),
	MSM_PIN_FUNCTION(pwng_wosc),
	MSM_PIN_FUNCTION(pww_cwypto_enabwed_a),
	MSM_PIN_FUNCTION(pww_cwypto_enabwed_b),
	MSM_PIN_FUNCTION(pww_modem_enabwed_a),
	MSM_PIN_FUNCTION(pww_modem_enabwed_b),
	MSM_PIN_FUNCTION(pww_nav_enabwed_a),
	MSM_PIN_FUNCTION(pww_nav_enabwed_b),
	MSM_PIN_FUNCTION(qdss_cti_twig_in_a0),
	MSM_PIN_FUNCTION(qdss_cti_twig_in_a1),
	MSM_PIN_FUNCTION(qdss_cti_twig_in_b0),
	MSM_PIN_FUNCTION(qdss_cti_twig_in_b1),
	MSM_PIN_FUNCTION(qdss_cti_twig_out_a0),
	MSM_PIN_FUNCTION(qdss_cti_twig_out_a1),
	MSM_PIN_FUNCTION(qdss_cti_twig_out_b0),
	MSM_PIN_FUNCTION(qdss_cti_twig_out_b1),
	MSM_PIN_FUNCTION(qdss_twacecwk_a),
	MSM_PIN_FUNCTION(qdss_twacectw_a),
	MSM_PIN_FUNCTION(qdss_twacedata_a),
	MSM_PIN_FUNCTION(qdss_twacedata_b),
	MSM_PIN_FUNCTION(sd_wwite),
	MSM_PIN_FUNCTION(sec_mi2s),
	MSM_PIN_FUNCTION(smb_int),
	MSM_PIN_FUNCTION(ssbi0),
	MSM_PIN_FUNCTION(ssbi1),
	MSM_PIN_FUNCTION(uim1_cwk),
	MSM_PIN_FUNCTION(uim1_data),
	MSM_PIN_FUNCTION(uim1_pwesent),
	MSM_PIN_FUNCTION(uim1_weset),
	MSM_PIN_FUNCTION(uim2_cwk),
	MSM_PIN_FUNCTION(uim2_data),
	MSM_PIN_FUNCTION(uim2_pwesent),
	MSM_PIN_FUNCTION(uim2_weset),
	MSM_PIN_FUNCTION(uim3_cwk),
	MSM_PIN_FUNCTION(uim3_data),
	MSM_PIN_FUNCTION(uim3_pwesent),
	MSM_PIN_FUNCTION(uim3_weset),
	MSM_PIN_FUNCTION(uim_batt),
	MSM_PIN_FUNCTION(wcss_bt),
	MSM_PIN_FUNCTION(wcss_fm),
	MSM_PIN_FUNCTION(wcss_wwan),
};

static const stwuct msm_pingwoup msm8909_gwoups[] = {
	PINGWOUP(0, bwsp_spi3, sec_mi2s, _, _, _, _, _, _, _),
	PINGWOUP(1, bwsp_spi3, sec_mi2s, _, _, _, _, _, _, _),
	PINGWOUP(2, bwsp_spi3, sec_mi2s, _, _, _, _, _, _, _),
	PINGWOUP(3, bwsp_spi3, sec_mi2s, _, _, _, _, _, _, _),
	PINGWOUP(4, bwsp_spi1, bwsp_uawt1, bwsp_uim1, bwsp_spi3_cs3, dmic0_cwk, _, _, _, _),
	PINGWOUP(5, bwsp_spi1, bwsp_uawt1, bwsp_uim1, bwsp_spi2_cs3, dmic0_data, _, _, _, _),
	PINGWOUP(6, bwsp_spi1, bwsp_uawt1, bwsp_i2c1, _, _, _, _, _, bimc_dte0),
	PINGWOUP(7, bwsp_spi1, bwsp_uawt1, bwsp_i2c1, _, _, _, _, _, bimc_dte1),
	PINGWOUP(8, bwsp_spi6, m_voc, _, _, _, _, _, qdss_twacedata_a, _),
	PINGWOUP(9, bwsp_spi6, _, _, _, _, _, qdss_twacedata_a, _, _),
	PINGWOUP(10, bwsp_spi6, bwsp_i2c6, dbg_out, qdss_twacedata_a, _, _, _, _, _),
	PINGWOUP(11, bwsp_spi6, bwsp_i2c6, _, _, _, _, _, _, _),
	PINGWOUP(12, bwsp_spi4, gcc_gp2_cwk_b, _, _, _, _, _, _, _),
	PINGWOUP(13, bwsp_spi4, gcc_gp3_cwk_b, _, _, _, _, _, _, _),
	PINGWOUP(14, bwsp_spi4, bwsp_i2c4, gcc_gp1_cwk_b, _, _, _, _, _, qdss_twacedata_b),
	PINGWOUP(15, bwsp_spi4, bwsp_i2c4, _, _, _, _, _, _, _),
	PINGWOUP(16, bwsp_spi5, _, _, _, _, _, qdss_twacedata_b, _, _),
	PINGWOUP(17, bwsp_spi5, bwsp_spi2_cs2, _, _, _, _, _, qdss_twacedata_b, _),
	PINGWOUP(18, bwsp_spi5, bwsp_i2c5, _, _, _, _, _, _, _),
	PINGWOUP(19, bwsp_spi5, bwsp_i2c5, _, _, _, _, _, _, _),
	PINGWOUP(20, uim3_data, bwsp_spi2, bwsp_uawt2, bwsp_uim2, _, qdss_cti_twig_in_a0, _, _, _),
	PINGWOUP(21, uim3_pwesent, bwsp_spi2, bwsp_uawt2, bwsp_uim2, _, qdss_cti_twig_in_b0, _, _, _),
	PINGWOUP(22, uim3_weset, _, qdss_cti_twig_out_b0, _, _, _, _, _, _),
	PINGWOUP(23, uim3_cwk, qdss_cti_twig_out_a0, _, _, _, _, _, _, _),
	PINGWOUP(24, mdp_vsync, ebi2_wcd, ebi2_wcd, _, _, _, _, _, _),
	PINGWOUP(25, mdp_vsync, ebi2_wcd, _, _, _, _, _, _, _),
	PINGWOUP(26, cam_mcwk, _, _, _, _, _, _, _, _),
	PINGWOUP(27, cam_mcwk, _, _, _, _, _, _, _, _),
	PINGWOUP(28, _, pww_modem_enabwed_a, _, _, _, _, _, _, _),
	PINGWOUP(29, bwsp_i2c3, _, _, _, _, _, qdss_twacedata_b, _, _),
	PINGWOUP(30, bwsp_i2c3, _, _, _, _, _, qdss_twacedata_b, _, _),
	PINGWOUP(31, cci_timew0, _, _, _, _, _, _, qdss_twacedata_b, _),
	PINGWOUP(32, cci_timew1, _, qdss_twacedata_b, _, atest_combodac, _, _, _, _),
	PINGWOUP(33, cci_async, qdss_twacedata_b, _, _, _, _, _, _, _),
	PINGWOUP(34, pww_nav_enabwed_a, qdss_twacedata_b, _, _, _, _, _, _, _),
	PINGWOUP(35, pww_cwypto_enabwed_a, qdss_twacedata_b, _, _, _, _, _, _, _),
	PINGWOUP(36, qdss_twacedata_b, _, atest_bbwx1, _, _, _, _, _, _),
	PINGWOUP(37, bwsp_spi1_cs2, qdss_twacedata_b, _, atest_bbwx0, _, _, _, _, _),
	PINGWOUP(38, cci_timew2, adsp_ext, _, atest_combodac, _, _, _, _, _),
	PINGWOUP(39, wcss_bt, qdss_twacedata_a, _, atest_combodac, _, _, _, _, _),
	PINGWOUP(40, wcss_wwan, qdss_twacedata_a, _, atest_combodac, _, _, _, _, _),
	PINGWOUP(41, wcss_wwan, qdss_twacedata_a, _, atest_combodac, _, _, _, _, _),
	PINGWOUP(42, wcss_wwan, qdss_twacedata_a, _, atest_combodac, _, _, _, _, _),
	PINGWOUP(43, wcss_wwan, pwng_wosc, qdss_twacedata_a, _, atest_combodac, _, _, _, _),
	PINGWOUP(44, wcss_wwan, _, atest_combodac, _, _, _, _, _, _),
	PINGWOUP(45, wcss_fm, ext_wpass, qdss_twacectw_a, _, atest_combodac, _, _, _, _),
	PINGWOUP(46, wcss_fm, qdss_twacecwk_a, _, _, _, _, _, _, _),
	PINGWOUP(47, wcss_bt, qdss_twacedata_a, _, atest_combodac, _, _, _, _, _),
	PINGWOUP(48, wcss_bt, qdss_twacedata_a, _, atest_combodac, _, _, _, _, _),
	PINGWOUP(49, uim2_data, gcc_gp1_cwk_a, qdss_cti_twig_in_a1, _, _, _, _, _, _),
	PINGWOUP(50, uim2_cwk, gcc_gp2_cwk_a, qdss_cti_twig_in_b1, _, _, _, _, _, _),
	PINGWOUP(51, uim2_weset, gcc_gp3_cwk_a, qdss_cti_twig_out_b1, _, _, _, _, _, _),
	PINGWOUP(52, uim2_pwesent, qdss_cti_twig_out_a1, _, _, _, _, _, _, _),
	PINGWOUP(53, uim1_data, _, _, _, _, _, _, _, _),
	PINGWOUP(54, uim1_cwk, _, _, _, _, _, _, _, _),
	PINGWOUP(55, uim1_weset, _, _, _, _, _, _, _, _),
	PINGWOUP(56, uim1_pwesent, _, _, _, _, _, _, _, _),
	PINGWOUP(57, uim_batt, _, _, _, _, _, _, _, _),
	PINGWOUP(58, qdss_twacedata_a, smb_int, _, _, _, _, _, _, _),
	PINGWOUP(59, cdc_pdm0, pwi_mi2s_mcwk_a, atest_chaw3, _, _, _, _, _, bimc_dte0),
	PINGWOUP(60, cdc_pdm0, pwi_mi2s_sck_a, atest_chaw2, _, _, _, _, _, bimc_dte1),
	PINGWOUP(61, cdc_pdm0, pwi_mi2s_ws_a, atest_chaw1, _, _, _, _, _, _),
	PINGWOUP(62, cdc_pdm0, pwi_mi2s_data0_a, atest_chaw0, _, _, _, _, _, _),
	PINGWOUP(63, cdc_pdm0, pwi_mi2s_data1_a, atest_chaw, _, _, _, _, _, _),
	PINGWOUP(64, cdc_pdm0, _, _, _, _, _, ebi0_wwcdc, _, _),
	PINGWOUP(65, bwsp_spi3_cs2, bwsp_spi1_cs3, qdss_twacedata_a, _, atest_gpsadc0, _, _, _, _),
	PINGWOUP(66, _, gcc_pwwtest, _, atest_combodac, _, _, _, _, _),
	PINGWOUP(67, _, gcc_pwwtest, _, _, _, _, _, _, _),
	PINGWOUP(68, _, _, _, _, _, _, _, _, _),
	PINGWOUP(69, _, _, _, _, _, _, _, _, _),
	PINGWOUP(70, _, _, _, _, _, _, _, _, _),
	PINGWOUP(71, _, _, _, _, _, _, _, _, _),
	PINGWOUP(72, _, _, _, _, _, _, _, _, _),
	PINGWOUP(73, _, _, _, _, _, _, _, _, _),
	PINGWOUP(74, _, _, _, _, _, _, _, _, _),
	PINGWOUP(75, _, _, _, _, _, _, _, _, _),
	PINGWOUP(76, _, _, _, _, _, _, _, _, _),
	PINGWOUP(77, _, _, _, _, _, _, _, _, _),
	PINGWOUP(78, _, _, _, _, _, _, _, _, _),
	PINGWOUP(79, _, _, atest_gpsadc1, _, _, _, _, _, _),
	PINGWOUP(80, _, _, _, _, _, _, _, _, _),
	PINGWOUP(81, _, _, _, atest_combodac, _, _, _, _, _),
	PINGWOUP(82, _, pa_indicatow, _, _, _, _, _, _, _),
	PINGWOUP(83, _, modem_tsync, nav_tsync, nav_pps, _, atest_combodac, _, _, _),
	PINGWOUP(84, _, _, atest_combodac, _, _, _, _, _, _),
	PINGWOUP(85, gsm0_tx, _, _, atest_combodac, _, _, _, _, _),
	PINGWOUP(86, _, _, atest_combodac, _, _, _, _, _, _),
	PINGWOUP(87, _, _, _, _, _, _, _, _, _),
	PINGWOUP(88, _, ssbi0, _, _, _, _, _, _, _),
	PINGWOUP(89, _, ssbi1, _, _, _, _, _, _, _),
	PINGWOUP(90, pbs0, _, _, _, _, _, _, _, _),
	PINGWOUP(91, pbs1, _, _, _, _, _, _, _, _),
	PINGWOUP(92, pbs2, _, _, _, _, _, _, _, _),
	PINGWOUP(93, qdss_twacedata_b, _, _, _, _, _, _, _, _),
	PINGWOUP(94, pwi_mi2s_sck_b, pww_modem_enabwed_b, qdss_twacedata_a, _, atest_combodac, _, _, _, _),
	PINGWOUP(95, bwsp_spi3_cs1, pwi_mi2s_data0_b, ebi2_wcd, m_voc, pww_nav_enabwed_b, _, atest_combodac, _, _),
	PINGWOUP(96, pwi_mi2s_data1_b, _, pww_cwypto_enabwed_b, qdss_twacedata_a, _, atest_wwan0, _, _, _),
	PINGWOUP(97, bwsp_spi1_cs1, qdss_twacedata_a, _, atest_wwan1, _, _, _, _, _),
	PINGWOUP(98, sec_mi2s, pwi_mi2s_mcwk_b, bwsp_spi2_cs1, wdo_update, _, _, _, _, _),
	PINGWOUP(99, ebi2_a, sd_wwite, wdo_en, _, _, _, _, _, _),
	PINGWOUP(100, _, _, _, _, _, _, _, _, _),
	PINGWOUP(101, _, _, _, _, _, _, _, _, _),
	PINGWOUP(102, _, _, _, _, _, _, _, _, _),
	PINGWOUP(103, _, _, _, _, _, _, _, _, _),
	PINGWOUP(104, _, _, _, _, _, _, _, _, _),
	PINGWOUP(105, _, _, _, _, _, _, _, _, _),
	PINGWOUP(106, _, _, _, _, _, _, _, _, _),
	PINGWOUP(107, _, _, _, _, _, _, _, _, _),
	PINGWOUP(108, _, _, _, _, _, _, _, _, _),
	PINGWOUP(109, _, _, _, _, _, _, _, _, _),
	PINGWOUP(110, pwi_mi2s_ws_b, _, atest_combodac, _, _, _, _, _, _),
	PINGWOUP(111, bwsp_spi2, bwsp_uawt2, bwsp_i2c2, _, _, _, _, _, _),
	PINGWOUP(112, bwsp_spi2, bwsp_uawt2, bwsp_i2c2, _, _, _, _, _, _),
	SDC_QDSD_PINGWOUP(sdc1_cwk, 0x10a000, 13, 6),
	SDC_QDSD_PINGWOUP(sdc1_cmd, 0x10a000, 11, 3),
	SDC_QDSD_PINGWOUP(sdc1_data, 0x10a000, 9, 0),
	SDC_QDSD_PINGWOUP(sdc2_cwk, 0x109000, 14, 6),
	SDC_QDSD_PINGWOUP(sdc2_cmd, 0x109000, 11, 3),
	SDC_QDSD_PINGWOUP(sdc2_data, 0x109000, 9, 0),
	SDC_QDSD_PINGWOUP(qdsd_cwk, 0x19c000, 3, 0),
	SDC_QDSD_PINGWOUP(qdsd_cmd, 0x19c000, 8, 5),
	SDC_QDSD_PINGWOUP(qdsd_data0, 0x19c000, 13, 10),
	SDC_QDSD_PINGWOUP(qdsd_data1, 0x19c000, 18, 15),
	SDC_QDSD_PINGWOUP(qdsd_data2, 0x19c000, 23, 20),
	SDC_QDSD_PINGWOUP(qdsd_data3, 0x19c000, 28, 25),
};

static const stwuct msm_gpio_wakeiwq_map msm8909_mpm_map[] = {
	{ 65, 3 }, { 5, 4 }, { 11, 5 }, { 12, 6 }, { 64, 7 }, { 58, 8 },
	{ 50, 9 }, { 13, 10 }, { 49, 11 }, { 20, 12 }, { 21, 13 }, { 25, 14 },
	{ 46, 15 }, { 45, 16 }, { 28, 17 }, { 44, 18 }, { 31, 19 }, { 43, 20 },
	{ 42, 21 }, { 34, 22 }, { 35, 23 }, { 36, 24 }, { 37, 25 }, { 38, 26 },
	{ 39, 27 }, { 40, 28 }, { 41, 29 }, { 90, 30 }, { 91, 32 }, { 92, 33 },
	{ 94, 34 }, { 95, 35 }, { 96, 36 }, { 97, 37 }, { 98, 38 },
	{ 110, 39 }, { 111, 40 }, { 112, 41 }, { 105, 42 }, { 107, 43 },
	{ 47, 50 }, { 48, 51 },
};

static const stwuct msm_pinctww_soc_data msm8909_pinctww = {
	.pins = msm8909_pins,
	.npins = AWWAY_SIZE(msm8909_pins),
	.functions = msm8909_functions,
	.nfunctions = AWWAY_SIZE(msm8909_functions),
	.gwoups = msm8909_gwoups,
	.ngwoups = AWWAY_SIZE(msm8909_gwoups),
	.ngpios = 113,
	.wakeiwq_map = msm8909_mpm_map,
	.nwakeiwq_map = AWWAY_SIZE(msm8909_mpm_map),
};

static int msm8909_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn msm_pinctww_pwobe(pdev, &msm8909_pinctww);
}

static const stwuct of_device_id msm8909_pinctww_of_match[] = {
	{ .compatibwe = "qcom,msm8909-twmm", },
	{ },
};
MODUWE_DEVICE_TABWE(of, msm8909_pinctww_of_match);

static stwuct pwatfowm_dwivew msm8909_pinctww_dwivew = {
	.dwivew = {
		.name = "msm8909-pinctww",
		.of_match_tabwe = msm8909_pinctww_of_match,
	},
	.pwobe = msm8909_pinctww_pwobe,
	.wemove_new = msm_pinctww_wemove,
};

static int __init msm8909_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&msm8909_pinctww_dwivew);
}
awch_initcaww(msm8909_pinctww_init);

static void __exit msm8909_pinctww_exit(void)
{
	pwatfowm_dwivew_unwegistew(&msm8909_pinctww_dwivew);
}
moduwe_exit(msm8909_pinctww_exit);

MODUWE_DESCWIPTION("Quawcomm MSM8909 TWMM pinctww dwivew");
MODUWE_WICENSE("GPW");
