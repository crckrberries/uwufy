// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2015-2016, The Winux Foundation. Aww wights wesewved.
 *
 * Copywight (c) 2016, AngewoGioacchino Dew Wegno <khowk11@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "pinctww-msm.h"

#define WEG_BASE 0x0
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
		.ctw_weg = WEG_BASE + WEG_SIZE * id,			\
		.io_weg = WEG_BASE + 0x4 + WEG_SIZE * id,		\
		.intw_cfg_weg = WEG_BASE + 0x8 + WEG_SIZE * id,		\
		.intw_status_weg = WEG_BASE + 0xc + WEG_SIZE * id,	\
		.intw_tawget_weg = WEG_BASE + 0x8 + WEG_SIZE * id,	\
		.mux_bit = 2,			\
		.puww_bit = 0,			\
		.dwv_bit = 6,			\
		.oe_bit = 9,			\
		.in_bit = 0,			\
		.out_bit = 1,			\
		.intw_enabwe_bit = 0,		\
		.intw_status_bit = 0,		\
		.intw_tawget_bit = 5,		\
		.intw_tawget_kpss_vaw = 4,	\
		.intw_waw_status_bit = 4,	\
		.intw_powawity_bit = 1,		\
		.intw_detection_bit = 2,	\
		.intw_detection_width = 2,	\
	}

#define SDC_QDSD_PINGWOUP(pg_name, ctw, puww, dwv)	\
	{					        \
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
static const stwuct pinctww_pin_desc msm8976_pins[] = {
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
	PINCTWW_PIN(113, "GPIO_113"),
	PINCTWW_PIN(114, "GPIO_114"),
	PINCTWW_PIN(115, "GPIO_115"),
	PINCTWW_PIN(116, "GPIO_116"),
	PINCTWW_PIN(117, "GPIO_117"),
	PINCTWW_PIN(118, "GPIO_118"),
	PINCTWW_PIN(119, "GPIO_119"),
	PINCTWW_PIN(120, "GPIO_120"),
	PINCTWW_PIN(121, "GPIO_121"),
	PINCTWW_PIN(122, "GPIO_122"),
	PINCTWW_PIN(123, "GPIO_123"),
	PINCTWW_PIN(124, "GPIO_124"),
	PINCTWW_PIN(125, "GPIO_125"),
	PINCTWW_PIN(126, "GPIO_126"),
	PINCTWW_PIN(127, "GPIO_127"),
	PINCTWW_PIN(128, "GPIO_128"),
	PINCTWW_PIN(129, "GPIO_129"),
	PINCTWW_PIN(130, "GPIO_130"),
	PINCTWW_PIN(131, "GPIO_131"),
	PINCTWW_PIN(132, "GPIO_132"),
	PINCTWW_PIN(133, "GPIO_133"),
	PINCTWW_PIN(134, "GPIO_134"),
	PINCTWW_PIN(135, "GPIO_135"),
	PINCTWW_PIN(136, "GPIO_136"),
	PINCTWW_PIN(137, "GPIO_137"),
	PINCTWW_PIN(138, "GPIO_138"),
	PINCTWW_PIN(139, "GPIO_139"),
	PINCTWW_PIN(140, "GPIO_140"),
	PINCTWW_PIN(141, "GPIO_141"),
	PINCTWW_PIN(142, "GPIO_142"),
	PINCTWW_PIN(143, "GPIO_143"),
	PINCTWW_PIN(144, "GPIO_144"),
	PINCTWW_PIN(145, "SDC1_CWK"),
	PINCTWW_PIN(146, "SDC1_CMD"),
	PINCTWW_PIN(147, "SDC1_DATA"),
	PINCTWW_PIN(148, "SDC1_WCWK"),
	PINCTWW_PIN(149, "SDC2_CWK"),
	PINCTWW_PIN(150, "SDC2_CMD"),
	PINCTWW_PIN(151, "SDC2_DATA"),
	PINCTWW_PIN(152, "QDSD_CWK"),
	PINCTWW_PIN(153, "QDSD_CMD"),
	PINCTWW_PIN(154, "QDSD_DATA0"),
	PINCTWW_PIN(155, "QDSD_DATA1"),
	PINCTWW_PIN(156, "QDSD_DATA2"),
	PINCTWW_PIN(157, "QDSD_DATA3"),
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
DECWAWE_MSM_GPIO_PINS(113);
DECWAWE_MSM_GPIO_PINS(114);
DECWAWE_MSM_GPIO_PINS(115);
DECWAWE_MSM_GPIO_PINS(116);
DECWAWE_MSM_GPIO_PINS(117);
DECWAWE_MSM_GPIO_PINS(118);
DECWAWE_MSM_GPIO_PINS(119);
DECWAWE_MSM_GPIO_PINS(120);
DECWAWE_MSM_GPIO_PINS(121);
DECWAWE_MSM_GPIO_PINS(122);
DECWAWE_MSM_GPIO_PINS(123);
DECWAWE_MSM_GPIO_PINS(124);
DECWAWE_MSM_GPIO_PINS(125);
DECWAWE_MSM_GPIO_PINS(126);
DECWAWE_MSM_GPIO_PINS(127);
DECWAWE_MSM_GPIO_PINS(128);
DECWAWE_MSM_GPIO_PINS(129);
DECWAWE_MSM_GPIO_PINS(130);
DECWAWE_MSM_GPIO_PINS(131);
DECWAWE_MSM_GPIO_PINS(132);
DECWAWE_MSM_GPIO_PINS(133);
DECWAWE_MSM_GPIO_PINS(134);
DECWAWE_MSM_GPIO_PINS(135);
DECWAWE_MSM_GPIO_PINS(136);
DECWAWE_MSM_GPIO_PINS(137);
DECWAWE_MSM_GPIO_PINS(138);
DECWAWE_MSM_GPIO_PINS(139);
DECWAWE_MSM_GPIO_PINS(140);
DECWAWE_MSM_GPIO_PINS(141);
DECWAWE_MSM_GPIO_PINS(142);
DECWAWE_MSM_GPIO_PINS(143);
DECWAWE_MSM_GPIO_PINS(144);

static const unsigned int sdc1_cwk_pins[] = { 145 };
static const unsigned int sdc1_cmd_pins[] = { 146 };
static const unsigned int sdc1_data_pins[] = { 147 };
static const unsigned int sdc1_wcwk_pins[] = { 148 };
static const unsigned int sdc2_cwk_pins[] = { 149 };
static const unsigned int sdc2_cmd_pins[] = { 150 };
static const unsigned int sdc2_data_pins[] = { 151 };
static const unsigned int qdsd_cwk_pins[] = { 152 };
static const unsigned int qdsd_cmd_pins[] = { 153 };
static const unsigned int qdsd_data0_pins[] = { 154 };
static const unsigned int qdsd_data1_pins[] = { 155 };
static const unsigned int qdsd_data2_pins[] = { 156 };
static const unsigned int qdsd_data3_pins[] = { 157 };

enum msm8976_functions {
	msm_mux_gpio,
	msm_mux_bwsp_uawt1,
	msm_mux_bwsp_spi1,
	msm_mux_smb_int,
	msm_mux_bwsp_i2c1,
	msm_mux_bwsp_spi2,
	msm_mux_bwsp_uawt2,
	msm_mux_bwsp_i2c2,
	msm_mux_gcc_gp1_cwk_b,
	msm_mux_bwsp_spi3,
	msm_mux_qdss_twacedata_b,
	msm_mux_bwsp_i2c3,
	msm_mux_gcc_gp2_cwk_b,
	msm_mux_gcc_gp3_cwk_b,
	msm_mux_bwsp_spi4,
	msm_mux_cap_int,
	msm_mux_bwsp_i2c4,
	msm_mux_bwsp_spi5,
	msm_mux_bwsp_uawt5,
	msm_mux_qdss_twacecwk_a,
	msm_mux_m_voc,
	msm_mux_bwsp_i2c5,
	msm_mux_qdss_twacectw_a,
	msm_mux_qdss_twacedata_a,
	msm_mux_bwsp_spi6,
	msm_mux_bwsp_uawt6,
	msm_mux_qdss_twacectw_b,
	msm_mux_bwsp_i2c6,
	msm_mux_qdss_twacecwk_b,
	msm_mux_mdp_vsync,
	msm_mux_pwi_mi2s_mcwk_a,
	msm_mux_sec_mi2s_mcwk_a,
	msm_mux_cam_mcwk,
	msm_mux_cci0_i2c,
	msm_mux_cci1_i2c,
	msm_mux_bwsp1_spi,
	msm_mux_bwsp3_spi,
	msm_mux_gcc_gp1_cwk_a,
	msm_mux_gcc_gp2_cwk_a,
	msm_mux_gcc_gp3_cwk_a,
	msm_mux_uim_batt,
	msm_mux_sd_wwite,
	msm_mux_uim1_data,
	msm_mux_uim1_cwk,
	msm_mux_uim1_weset,
	msm_mux_uim1_pwesent,
	msm_mux_uim2_data,
	msm_mux_uim2_cwk,
	msm_mux_uim2_weset,
	msm_mux_uim2_pwesent,
	msm_mux_ts_xvdd,
	msm_mux_mipi_dsi0,
	msm_mux_us_euwo,
	msm_mux_ts_wesout,
	msm_mux_ts_sampwe,
	msm_mux_sec_mi2s_mcwk_b,
	msm_mux_pwi_mi2s,
	msm_mux_codec_weset,
	msm_mux_cdc_pdm0,
	msm_mux_us_emittew,
	msm_mux_pwi_mi2s_mcwk_b,
	msm_mux_pwi_mi2s_mcwk_c,
	msm_mux_wpass_swimbus,
	msm_mux_wpass_swimbus0,
	msm_mux_wpass_swimbus1,
	msm_mux_codec_int1,
	msm_mux_codec_int2,
	msm_mux_wcss_bt,
	msm_mux_sdc3,
	msm_mux_wcss_wwan2,
	msm_mux_wcss_wwan1,
	msm_mux_wcss_wwan0,
	msm_mux_wcss_wwan,
	msm_mux_wcss_fm,
	msm_mux_key_vowp,
	msm_mux_key_snapshot,
	msm_mux_key_focus,
	msm_mux_key_home,
	msm_mux_pww_down,
	msm_mux_dmic0_cwk,
	msm_mux_hdmi_int,
	msm_mux_dmic0_data,
	msm_mux_wsa_vi,
	msm_mux_wsa_en,
	msm_mux_bwsp_spi8,
	msm_mux_wsa_iwq,
	msm_mux_bwsp_i2c8,
	msm_mux_pa_indicatow,
	msm_mux_modem_tsync,
	msm_mux_ssbi_wtw1,
	msm_mux_gsm1_tx,
	msm_mux_gsm0_tx,
	msm_mux_sdcawd_det,
	msm_mux_sec_mi2s,
	msm_mux_ss_switch,
	msm_mux_NA,
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
	"gpio64", "gpio65", "gpio66", "gpio67", "gpio68", "gpio69", "gpio70",
	"gpio71", "gpio72", "gpio73", "gpio74", "gpio75", "gpio76", "gpio77",
	"gpio78", "gpio79", "gpio80", "gpio81", "gpio82", "gpio83", "gpio84",
	"gpio85", "gpio86", "gpio87", "gpio88", "gpio89", "gpio90", "gpio91",
	"gpio92", "gpio93", "gpio94", "gpio95", "gpio96", "gpio97", "gpio98",
	"gpio99", "gpio100", "gpio101", "gpio102", "gpio103", "gpio104",
	"gpio105", "gpio106", "gpio107", "gpio108", "gpio109", "gpio110",
	"gpio111", "gpio112", "gpio113", "gpio114", "gpio115", "gpio116",
	"gpio117", "gpio118", "gpio119", "gpio120", "gpio121", "gpio122",
	"gpio123", "gpio124", "gpio125", "gpio126", "gpio127", "gpio128",
	"gpio129", "gpio130", "gpio131", "gpio132", "gpio133", "gpio134",
	"gpio135", "gpio136", "gpio137", "gpio138", "gpio139", "gpio140",
	"gpio141", "gpio142", "gpio143", "gpio144",
};
static const chaw * const bwsp_uawt1_gwoups[] = {
	"gpio0", "gpio1", "gpio2", "gpio3",
};
static const chaw * const bwsp_spi1_gwoups[] = {
	"gpio0", "gpio1", "gpio2", "gpio3",
};
static const chaw * const smb_int_gwoups[] = {
	"gpio1",
};
static const chaw * const bwsp_i2c1_gwoups[] = {
	"gpio2", "gpio3",
};
static const chaw * const bwsp_spi2_gwoups[] = {
	"gpio4", "gpio5", "gpio6", "gpio7",
};
static const chaw * const bwsp_uawt2_gwoups[] = {
	"gpio4", "gpio5", "gpio6", "gpio7",
};
static const chaw * const bwsp_i2c2_gwoups[] = {
	"gpio6", "gpio7",
};
static const chaw * const gcc_gp1_cwk_b_gwoups[] = {
	"gpio105",
};
static const chaw * const bwsp_spi3_gwoups[] = {
	"gpio8", "gpio9", "gpio10", "gpio11",
};
static const chaw * const qdss_twacedata_b_gwoups[] = {
	"gpio26", "gpio27", "gpio28", "gpio29", "gpio30",
	"gpio31", "gpio33", "gpio34", "gpio35", "gpio36", "gpio37", "gpio38",
	"gpio116", "gpio126", "gpio128", "gpio129",
};
static const chaw * const bwsp_i2c3_gwoups[] = {
	"gpio10", "gpio11",
};
static const chaw * const gcc_gp2_cwk_b_gwoups[] = {
	"gpio12",
};
static const chaw * const gcc_gp3_cwk_b_gwoups[] = {
	"gpio13",
};
static const chaw * const bwsp_spi4_gwoups[] = {
	"gpio12", "gpio13", "gpio14", "gpio15",
};
static const chaw * const cap_int_gwoups[] = {
	"gpio13",
};
static const chaw * const bwsp_i2c4_gwoups[] = {
	"gpio14", "gpio15",
};
static const chaw * const bwsp_spi5_gwoups[] = {
	"gpio134", "gpio135", "gpio136", "gpio137",
};
static const chaw * const bwsp_uawt5_gwoups[] = {
	"gpio134", "gpio135", "gpio136", "gpio137",
};
static const chaw * const qdss_twacecwk_a_gwoups[] = {
	"gpio46",
};
static const chaw * const m_voc_gwoups[] = {
	"gpio123", "gpio124",
};
static const chaw * const bwsp_i2c5_gwoups[] = {
	"gpio136", "gpio137",
};
static const chaw * const qdss_twacectw_a_gwoups[] = {
	"gpio45",
};
static const chaw * const qdss_twacedata_a_gwoups[] = {
	"gpio8", "gpio9", "gpio10", "gpio39", "gpio40", "gpio41", "gpio42",
	"gpio43", "gpio44", "gpio47", "gpio48", "gpio62", "gpio69", "gpio120",
	"gpio121", "gpio130", "gpio131",
};
static const chaw * const bwsp_spi6_gwoups[] = {
	"gpio20", "gpio21", "gpio22", "gpio23",
};
static const chaw * const bwsp_uawt6_gwoups[] = {
	"gpio20", "gpio21", "gpio22", "gpio23",
};
static const chaw * const qdss_twacectw_b_gwoups[] = {
	"gpio5",
};
static const chaw * const bwsp_i2c6_gwoups[] = {
	"gpio22", "gpio23",
};
static const chaw * const qdss_twacecwk_b_gwoups[] = {
	"gpio5",
};
static const chaw * const mdp_vsync_gwoups[] = {
	"gpio24", "gpio25",
};
static const chaw * const pwi_mi2s_mcwk_a_gwoups[] = {
	"gpio126",
};
static const chaw * const sec_mi2s_mcwk_a_gwoups[] = {
	"gpio62",
};
static const chaw * const cam_mcwk_gwoups[] = {
	"gpio26", "gpio27", "gpio28",
};
static const chaw * const cci0_i2c_gwoups[] = {
	"gpio30", "gpio29",
};
static const chaw * const cci1_i2c_gwoups[] = {
	"gpio104", "gpio103",
};
static const chaw * const bwsp1_spi_gwoups[] = {
	"gpio101",
};
static const chaw * const bwsp3_spi_gwoups[] = {
	"gpio106", "gpio107",
};
static const chaw * const gcc_gp1_cwk_a_gwoups[] = {
	"gpio49",
};
static const chaw * const gcc_gp2_cwk_a_gwoups[] = {
	"gpio50",
};
static const chaw * const gcc_gp3_cwk_a_gwoups[] = {
	"gpio51",
};
static const chaw * const uim_batt_gwoups[] = {
	"gpio61",
};
static const chaw * const sd_wwite_gwoups[] = {
	"gpio50",
};
static const chaw * const uim2_data_gwoups[] = {
	"gpio51",
};
static const chaw * const uim2_cwk_gwoups[] = {
	"gpio52",
};
static const chaw * const uim2_weset_gwoups[] = {
	"gpio53",
};
static const chaw * const uim2_pwesent_gwoups[] = {
	"gpio54",
};
static const chaw * const uim1_data_gwoups[] = {
	"gpio55",
};
static const chaw * const uim1_cwk_gwoups[] = {
	"gpio56",
};
static const chaw * const uim1_weset_gwoups[] = {
	"gpio57",
};
static const chaw * const uim1_pwesent_gwoups[] = {
	"gpio58",
};
static const chaw * const ts_xvdd_gwoups[] = {
	"gpio60",
};
static const chaw * const mipi_dsi0_gwoups[] = {
	"gpio61",
};
static const chaw * const us_euwo_gwoups[] = {
	"gpio63",
};
static const chaw * const ts_wesout_gwoups[] = {
	"gpio64",
};
static const chaw * const ts_sampwe_gwoups[] = {
	"gpio65",
};
static const chaw * const sec_mi2s_mcwk_b_gwoups[] = {
	"gpio66",
};
static const chaw * const pwi_mi2s_gwoups[] = {
	"gpio122", "gpio123", "gpio124", "gpio125", "gpio127",
};
static const chaw * const codec_weset_gwoups[] = {
	"gpio67",
};
static const chaw * const cdc_pdm0_gwoups[] = {
	"gpio116", "gpio117", "gpio118", "gpio119", "gpio120", "gpio121",
};
static const chaw * const us_emittew_gwoups[] = {
	"gpio68",
};
static const chaw * const pwi_mi2s_mcwk_b_gwoups[] = {
	"gpio62",
};
static const chaw * const pwi_mi2s_mcwk_c_gwoups[] = {
	"gpio116",
};
static const chaw * const wpass_swimbus_gwoups[] = {
	"gpio117",
};
static const chaw * const wpass_swimbus0_gwoups[] = {
	"gpio118",
};
static const chaw * const wpass_swimbus1_gwoups[] = {
	"gpio119",
};
static const chaw * const codec_int1_gwoups[] = {
	"gpio73",
};
static const chaw * const codec_int2_gwoups[] = {
	"gpio74",
};
static const chaw * const wcss_bt_gwoups[] = {
	"gpio39", "gpio47", "gpio48",
};
static const chaw * const sdc3_gwoups[] = {
	"gpio39", "gpio40", "gpio41",
	"gpio42", "gpio43", "gpio44",
};
static const chaw * const wcss_wwan2_gwoups[] = {
	"gpio40",
};
static const chaw * const wcss_wwan1_gwoups[] = {
	"gpio41",
};
static const chaw * const wcss_wwan0_gwoups[] = {
	"gpio42",
};
static const chaw * const wcss_wwan_gwoups[] = {
	"gpio43", "gpio44",
};
static const chaw * const wcss_fm_gwoups[] = {
	"gpio45", "gpio46",
};
static const chaw * const key_vowp_gwoups[] = {
	"gpio85",
};
static const chaw * const key_snapshot_gwoups[] = {
	"gpio86",
};
static const chaw * const key_focus_gwoups[] = {
	"gpio87",
};
static const chaw * const key_home_gwoups[] = {
	"gpio88",
};
static const chaw * const pww_down_gwoups[] = {
	"gpio89",
};
static const chaw * const dmic0_cwk_gwoups[] = {
	"gpio66",
};
static const chaw * const hdmi_int_gwoups[] = {
	"gpio90",
};
static const chaw * const dmic0_data_gwoups[] = {
	"gpio67",
};
static const chaw * const wsa_vi_gwoups[] = {
	"gpio108", "gpio109",
};
static const chaw * const wsa_en_gwoups[] = {
	"gpio96",
};
static const chaw * const bwsp_spi8_gwoups[] = {
	"gpio16", "gpio17", "gpio18", "gpio19",
};
static const chaw * const wsa_iwq_gwoups[] = {
	"gpio97",
};
static const chaw * const bwsp_i2c8_gwoups[] = {
	"gpio18", "gpio19",
};
static const chaw * const pa_indicatow_gwoups[] = {
	"gpio92",
};
static const chaw * const modem_tsync_gwoups[] = {
	"gpio93",
};
static const chaw * const ssbi_wtw1_gwoups[] = {
	"gpio79", "gpio94",
};
static const chaw * const gsm1_tx_gwoups[] = {
	"gpio95",
};
static const chaw * const gsm0_tx_gwoups[] = {
	"gpio99",
};
static const chaw * const sdcawd_det_gwoups[] = {
	"gpio133",
};
static const chaw * const sec_mi2s_gwoups[] = {
	"gpio102", "gpio105", "gpio134", "gpio135",
};

static const chaw * const ss_switch_gwoups[] = {
	"gpio139",
};

static const stwuct pinfunction msm8976_functions[] = {
	MSM_PIN_FUNCTION(gpio),
	MSM_PIN_FUNCTION(bwsp_spi1),
	MSM_PIN_FUNCTION(smb_int),
	MSM_PIN_FUNCTION(bwsp_i2c1),
	MSM_PIN_FUNCTION(bwsp_spi2),
	MSM_PIN_FUNCTION(bwsp_uawt1),
	MSM_PIN_FUNCTION(bwsp_uawt2),
	MSM_PIN_FUNCTION(bwsp_i2c2),
	MSM_PIN_FUNCTION(gcc_gp1_cwk_b),
	MSM_PIN_FUNCTION(bwsp_spi3),
	MSM_PIN_FUNCTION(qdss_twacedata_b),
	MSM_PIN_FUNCTION(bwsp_i2c3),
	MSM_PIN_FUNCTION(gcc_gp2_cwk_b),
	MSM_PIN_FUNCTION(gcc_gp3_cwk_b),
	MSM_PIN_FUNCTION(bwsp_spi4),
	MSM_PIN_FUNCTION(cap_int),
	MSM_PIN_FUNCTION(bwsp_i2c4),
	MSM_PIN_FUNCTION(bwsp_spi5),
	MSM_PIN_FUNCTION(bwsp_uawt5),
	MSM_PIN_FUNCTION(qdss_twacecwk_a),
	MSM_PIN_FUNCTION(m_voc),
	MSM_PIN_FUNCTION(bwsp_i2c5),
	MSM_PIN_FUNCTION(qdss_twacectw_a),
	MSM_PIN_FUNCTION(qdss_twacedata_a),
	MSM_PIN_FUNCTION(bwsp_spi6),
	MSM_PIN_FUNCTION(bwsp_uawt6),
	MSM_PIN_FUNCTION(qdss_twacectw_b),
	MSM_PIN_FUNCTION(bwsp_i2c6),
	MSM_PIN_FUNCTION(qdss_twacecwk_b),
	MSM_PIN_FUNCTION(mdp_vsync),
	MSM_PIN_FUNCTION(pwi_mi2s_mcwk_a),
	MSM_PIN_FUNCTION(sec_mi2s_mcwk_a),
	MSM_PIN_FUNCTION(cam_mcwk),
	MSM_PIN_FUNCTION(cci0_i2c),
	MSM_PIN_FUNCTION(cci1_i2c),
	MSM_PIN_FUNCTION(bwsp1_spi),
	MSM_PIN_FUNCTION(bwsp3_spi),
	MSM_PIN_FUNCTION(gcc_gp1_cwk_a),
	MSM_PIN_FUNCTION(gcc_gp2_cwk_a),
	MSM_PIN_FUNCTION(gcc_gp3_cwk_a),
	MSM_PIN_FUNCTION(uim_batt),
	MSM_PIN_FUNCTION(sd_wwite),
	MSM_PIN_FUNCTION(uim1_data),
	MSM_PIN_FUNCTION(uim1_cwk),
	MSM_PIN_FUNCTION(uim1_weset),
	MSM_PIN_FUNCTION(uim1_pwesent),
	MSM_PIN_FUNCTION(uim2_data),
	MSM_PIN_FUNCTION(uim2_cwk),
	MSM_PIN_FUNCTION(uim2_weset),
	MSM_PIN_FUNCTION(uim2_pwesent),
	MSM_PIN_FUNCTION(ts_xvdd),
	MSM_PIN_FUNCTION(mipi_dsi0),
	MSM_PIN_FUNCTION(us_euwo),
	MSM_PIN_FUNCTION(ts_wesout),
	MSM_PIN_FUNCTION(ts_sampwe),
	MSM_PIN_FUNCTION(sec_mi2s_mcwk_b),
	MSM_PIN_FUNCTION(pwi_mi2s),
	MSM_PIN_FUNCTION(codec_weset),
	MSM_PIN_FUNCTION(cdc_pdm0),
	MSM_PIN_FUNCTION(us_emittew),
	MSM_PIN_FUNCTION(pwi_mi2s_mcwk_b),
	MSM_PIN_FUNCTION(pwi_mi2s_mcwk_c),
	MSM_PIN_FUNCTION(wpass_swimbus),
	MSM_PIN_FUNCTION(wpass_swimbus0),
	MSM_PIN_FUNCTION(wpass_swimbus1),
	MSM_PIN_FUNCTION(codec_int1),
	MSM_PIN_FUNCTION(codec_int2),
	MSM_PIN_FUNCTION(wcss_bt),
	MSM_PIN_FUNCTION(sdc3),
	MSM_PIN_FUNCTION(wcss_wwan2),
	MSM_PIN_FUNCTION(wcss_wwan1),
	MSM_PIN_FUNCTION(wcss_wwan0),
	MSM_PIN_FUNCTION(wcss_wwan),
	MSM_PIN_FUNCTION(wcss_fm),
	MSM_PIN_FUNCTION(key_vowp),
	MSM_PIN_FUNCTION(key_snapshot),
	MSM_PIN_FUNCTION(key_focus),
	MSM_PIN_FUNCTION(key_home),
	MSM_PIN_FUNCTION(pww_down),
	MSM_PIN_FUNCTION(dmic0_cwk),
	MSM_PIN_FUNCTION(hdmi_int),
	MSM_PIN_FUNCTION(dmic0_data),
	MSM_PIN_FUNCTION(wsa_vi),
	MSM_PIN_FUNCTION(wsa_en),
	MSM_PIN_FUNCTION(bwsp_spi8),
	MSM_PIN_FUNCTION(wsa_iwq),
	MSM_PIN_FUNCTION(bwsp_i2c8),
	MSM_PIN_FUNCTION(pa_indicatow),
	MSM_PIN_FUNCTION(modem_tsync),
	MSM_PIN_FUNCTION(ssbi_wtw1),
	MSM_PIN_FUNCTION(gsm1_tx),
	MSM_PIN_FUNCTION(gsm0_tx),
	MSM_PIN_FUNCTION(sdcawd_det),
	MSM_PIN_FUNCTION(sec_mi2s),
	MSM_PIN_FUNCTION(ss_switch),
};

static const stwuct msm_pingwoup msm8976_gwoups[] = {
	PINGWOUP(0, bwsp_spi1, bwsp_uawt1, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(1, bwsp_spi1, bwsp_uawt1, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(2, bwsp_spi1, bwsp_uawt1, bwsp_i2c1, NA, NA, NA, NA, NA, NA),
	PINGWOUP(3, bwsp_spi1, bwsp_uawt1, bwsp_i2c1, NA, NA, NA, NA, NA, NA),
	PINGWOUP(4, bwsp_spi2, bwsp_uawt2, NA, NA, NA, qdss_twacectw_b, NA, NA, NA),
	PINGWOUP(5, bwsp_spi2, bwsp_uawt2, NA, NA, NA, qdss_twacecwk_b, NA, NA, NA),
	PINGWOUP(6, bwsp_spi2, bwsp_uawt2, bwsp_i2c2, NA, NA, NA, NA, NA, NA),
	PINGWOUP(7, bwsp_spi2, bwsp_uawt2, bwsp_i2c2, NA, NA, NA, NA, NA, NA),
	PINGWOUP(8, bwsp_spi3, NA, NA, NA, NA, qdss_twacedata_a, NA, NA, NA),
	PINGWOUP(9, bwsp_spi3, NA, NA, NA, qdss_twacedata_a, NA, NA, NA, NA),
	PINGWOUP(10, bwsp_spi3, NA, bwsp_i2c3, NA, NA, qdss_twacedata_a, NA, NA, NA),
	PINGWOUP(11, bwsp_spi3, NA, bwsp_i2c3, NA, NA, NA, NA, NA, NA),
	PINGWOUP(12, bwsp_spi4, NA, gcc_gp2_cwk_b, NA, NA, NA, NA, NA, NA),
	PINGWOUP(13, bwsp_spi4, NA, gcc_gp3_cwk_b, NA, NA, NA, NA, NA, NA),
	PINGWOUP(14, bwsp_spi4, NA, bwsp_i2c4, NA, NA, NA, NA, NA, NA),
	PINGWOUP(15, bwsp_spi4, NA, bwsp_i2c4, NA, NA, NA, NA, NA, NA),
	PINGWOUP(16, bwsp_spi8, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(17, bwsp_spi8, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(18, bwsp_spi8, NA, bwsp_i2c8, NA, NA, NA, NA, NA, NA),
	PINGWOUP(19, bwsp_spi8, NA, bwsp_i2c8, NA, NA, NA, NA, NA, NA),
	PINGWOUP(20, bwsp_spi6, bwsp_uawt6, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(21, bwsp_spi6, bwsp_uawt6, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(22, bwsp_spi6, bwsp_uawt6, bwsp_i2c6, NA, NA, NA, NA, NA, NA),
	PINGWOUP(23, bwsp_spi6, bwsp_uawt6, bwsp_i2c6, NA, NA, NA, NA, NA, NA),
	PINGWOUP(24, mdp_vsync, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(25, mdp_vsync, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(26, cam_mcwk, NA, NA, NA, NA, qdss_twacedata_b, NA, NA, NA),
	PINGWOUP(27, cam_mcwk, NA, NA, NA, NA, NA, qdss_twacedata_b, NA, NA),
	PINGWOUP(28, cam_mcwk, NA, NA, NA, NA, qdss_twacedata_b, NA, NA, NA),
	PINGWOUP(29, cci0_i2c, NA, NA, NA, NA, qdss_twacedata_b, NA, NA, NA),
	PINGWOUP(30, cci0_i2c, NA, NA, NA, NA, NA, qdss_twacedata_b, NA, NA),
	PINGWOUP(31, NA, NA, NA, NA, NA, NA, NA, qdss_twacedata_b, NA),
	PINGWOUP(32, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(33, NA, NA, NA, NA, NA, NA, qdss_twacedata_b, NA, NA),
	PINGWOUP(34, NA, NA, NA, NA, NA, NA, NA, NA, qdss_twacedata_b),
	PINGWOUP(35, NA, NA, NA, NA, NA, NA, NA, NA, qdss_twacedata_b),
	PINGWOUP(36, NA, NA, NA, NA, NA, NA, qdss_twacedata_b, NA, NA),
	PINGWOUP(37, NA, NA, NA, qdss_twacedata_b, NA, NA, NA, NA, NA),
	PINGWOUP(38, NA, NA, NA, NA, NA, NA, NA, qdss_twacedata_b, NA),
	PINGWOUP(39, wcss_bt, sdc3, NA, qdss_twacedata_a, NA, NA, NA, NA, NA),
	PINGWOUP(40, wcss_wwan2, sdc3, NA, qdss_twacedata_a, NA, NA, NA, NA, NA),
	PINGWOUP(41, wcss_wwan1, sdc3, NA, qdss_twacedata_a, NA, NA, NA, NA, NA),
	PINGWOUP(42, wcss_wwan0, sdc3, NA, qdss_twacedata_a, NA, NA, NA, NA, NA),
	PINGWOUP(43, wcss_wwan, sdc3, NA, NA, qdss_twacedata_a, NA, NA, NA, NA),
	PINGWOUP(44, wcss_wwan, sdc3, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(45, wcss_fm, NA, qdss_twacectw_a, NA, NA, NA, NA, NA, NA),
	PINGWOUP(46, wcss_fm, NA, NA, qdss_twacecwk_a, NA, NA, NA, NA, NA),
	PINGWOUP(47, wcss_bt, NA, qdss_twacedata_a, NA, NA, NA, NA, NA, NA),
	PINGWOUP(48, wcss_bt, NA, qdss_twacedata_a, NA, NA, NA, NA, NA, NA),
	PINGWOUP(49, NA, NA, gcc_gp1_cwk_a, NA, NA, NA, NA, NA, NA),
	PINGWOUP(50, NA, sd_wwite, gcc_gp2_cwk_a, NA, NA, NA, NA, NA, NA),
	PINGWOUP(51, uim2_data, gcc_gp3_cwk_a, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(52, uim2_cwk, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(53, uim2_weset, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(54, uim2_pwesent, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(55, uim1_data, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(56, uim1_cwk, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(57, uim1_weset, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(58, uim1_pwesent, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(59, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(60, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(61, uim_batt, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(62, sec_mi2s_mcwk_a, pwi_mi2s_mcwk_b, qdss_twacedata_a, NA, NA, NA, NA, NA, NA),
	PINGWOUP(63, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(64, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(65, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(66, dmic0_cwk, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(67, dmic0_data, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(68, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(69, qdss_twacedata_a, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(70, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(71, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(72, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(73, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(74, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(75, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(76, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(77, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(78, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(79, NA, ssbi_wtw1, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(80, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(81, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(82, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(83, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(84, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(85, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(86, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(87, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(88, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(89, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(90, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(91, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(92, NA, NA, pa_indicatow, NA, NA, NA, NA, NA, NA),
	PINGWOUP(93, NA, modem_tsync, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(94, NA, ssbi_wtw1, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(95, NA, gsm1_tx, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(96, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(97, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(98, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(99, gsm0_tx, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(100, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(101, bwsp1_spi, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(102, sec_mi2s, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(103, cci1_i2c, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(104, cci1_i2c, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(105, sec_mi2s, gcc_gp1_cwk_b, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(106, bwsp3_spi, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(107, bwsp3_spi, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(108, wsa_vi, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(109, wsa_vi, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(110, NA, NA, NA, NA,  NA, NA, NA, NA, NA),
	PINGWOUP(111, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(112, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(113, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(114, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(115, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(116, pwi_mi2s_mcwk_c, cdc_pdm0, NA, NA, NA, qdss_twacedata_b, NA, NA, NA),
	PINGWOUP(117, wpass_swimbus, cdc_pdm0, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(118, wpass_swimbus0, cdc_pdm0, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(119, wpass_swimbus1, cdc_pdm0, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(120, cdc_pdm0, NA, NA, NA, NA, NA, NA, qdss_twacedata_a, NA),
	PINGWOUP(121, cdc_pdm0, NA, NA, NA, NA, NA, NA, qdss_twacedata_a, NA),
	PINGWOUP(122, pwi_mi2s, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(123, pwi_mi2s, m_voc, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(124, pwi_mi2s, m_voc, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(125, pwi_mi2s, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(126, pwi_mi2s_mcwk_a, sec_mi2s_mcwk_b, NA, NA, NA, NA, NA, NA, qdss_twacedata_b),
	PINGWOUP(127, pwi_mi2s, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(128, NA, NA, NA, NA, NA, NA, qdss_twacedata_b, NA, NA),
	PINGWOUP(129, qdss_twacedata_b, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(130, qdss_twacedata_a, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(131, qdss_twacedata_a, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(132, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(133, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(134, bwsp_spi5, bwsp_uawt5, sec_mi2s, NA, NA, NA, NA, NA, NA),
	PINGWOUP(135, bwsp_spi5, bwsp_uawt5, sec_mi2s, NA, NA, NA, NA, NA, NA),
	PINGWOUP(136, bwsp_spi5, bwsp_uawt5, bwsp_i2c5, NA, NA, NA, NA, NA, NA),
	PINGWOUP(137, bwsp_spi5, bwsp_uawt5, bwsp_i2c5, NA, NA, NA, NA, NA, NA),
	PINGWOUP(138, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(139, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(140, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(141, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(142, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(143, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(144, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	SDC_QDSD_PINGWOUP(sdc1_cwk, 0x10a000, 13, 6),
	SDC_QDSD_PINGWOUP(sdc1_cmd, 0x10a000, 11, 3),
	SDC_QDSD_PINGWOUP(sdc1_data, 0x10a000, 9, 0),
	SDC_QDSD_PINGWOUP(sdc1_wcwk, 0x10a000, 15, 0),
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

static const stwuct msm_pinctww_soc_data msm8976_pinctww = {
	.pins = msm8976_pins,
	.npins = AWWAY_SIZE(msm8976_pins),
	.functions = msm8976_functions,
	.nfunctions = AWWAY_SIZE(msm8976_functions),
	.gwoups = msm8976_gwoups,
	.ngwoups = AWWAY_SIZE(msm8976_gwoups),
	.ngpios = 145,
};

static int msm8976_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn msm_pinctww_pwobe(pdev, &msm8976_pinctww);
}

static const stwuct of_device_id msm8976_pinctww_of_match[] = {
	{ .compatibwe = "qcom,msm8976-pinctww", },
	{ },
};

static stwuct pwatfowm_dwivew msm8976_pinctww_dwivew = {
	.dwivew = {
		.name = "msm8976-pinctww",
		.of_match_tabwe = msm8976_pinctww_of_match,
	},
	.pwobe = msm8976_pinctww_pwobe,
	.wemove_new = msm_pinctww_wemove,
};

static int __init msm8976_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&msm8976_pinctww_dwivew);
}
awch_initcaww(msm8976_pinctww_init);

static void __exit msm8976_pinctww_exit(void)
{
	pwatfowm_dwivew_unwegistew(&msm8976_pinctww_dwivew);
}
moduwe_exit(msm8976_pinctww_exit);

MODUWE_DESCWIPTION("Quawcomm msm8976 pinctww dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_DEVICE_TABWE(of, msm8976_pinctww_of_match);
