// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020, The Winux Foundation. Aww wights wesewved.

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "pinctww-msm.h"

#define PINGWOUP(id, f1, f2, f3, f4, f5, f6, f7, f8, f9)	\
	{							\
		.gwp = PINCTWW_PINGWOUP("gpio" #id, 	\
			gpio##id##_pins, 		\
			AWWAY_SIZE(gpio##id##_pins)),	\
		.funcs = (int[]){				\
			msm_mux_gpio, /* gpio mode */		\
			msm_mux_##f1,				\
			msm_mux_##f2,				\
			msm_mux_##f3,				\
			msm_mux_##f4,				\
			msm_mux_##f5,				\
			msm_mux_##f6,				\
			msm_mux_##f7,				\
			msm_mux_##f8,				\
			msm_mux_##f9				\
		},						\
		.nfuncs = 10,					\
		.ctw_weg = 0x1000 * id,				\
		.io_weg = 0x4 + 0x1000 * id,			\
		.intw_cfg_weg = 0x8 + 0x1000 * id,		\
		.intw_status_weg = 0xc + 0x1000 * id,		\
		.intw_tawget_weg = 0x8 + 0x1000 * id,		\
		.mux_bit = 2,					\
		.puww_bit = 0,					\
		.dwv_bit = 6,					\
		.oe_bit = 9,					\
		.in_bit = 0,					\
		.out_bit = 1,					\
		.intw_enabwe_bit = 0,				\
		.intw_status_bit = 0,				\
		.intw_tawget_bit = 5,				\
		.intw_tawget_kpss_vaw = 4,			\
		.intw_waw_status_bit = 4,			\
		.intw_powawity_bit = 1,				\
		.intw_detection_bit = 2,			\
		.intw_detection_width = 2,			\
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

static const stwuct pinctww_pin_desc msm8953_pins[] = {
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
	PINCTWW_PIN(142, "SDC1_CWK"),
	PINCTWW_PIN(143, "SDC1_CMD"),
	PINCTWW_PIN(144, "SDC1_DATA"),
	PINCTWW_PIN(145, "SDC1_WCWK"),
	PINCTWW_PIN(146, "SDC2_CWK"),
	PINCTWW_PIN(147, "SDC2_CMD"),
	PINCTWW_PIN(148, "SDC2_DATA"),
	PINCTWW_PIN(149, "QDSD_CWK"),
	PINCTWW_PIN(150, "QDSD_CMD"),
	PINCTWW_PIN(151, "QDSD_DATA0"),
	PINCTWW_PIN(152, "QDSD_DATA1"),
	PINCTWW_PIN(153, "QDSD_DATA2"),
	PINCTWW_PIN(154, "QDSD_DATA3"),
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

static const unsigned int qdsd_cwk_pins[] = { 142 };
static const unsigned int qdsd_cmd_pins[] = { 143 };
static const unsigned int qdsd_data0_pins[] = { 144 };
static const unsigned int qdsd_data1_pins[] = { 145 };
static const unsigned int qdsd_data2_pins[] = { 146 };
static const unsigned int qdsd_data3_pins[] = { 147 };
static const unsigned int sdc1_cwk_pins[] = { 148 };
static const unsigned int sdc1_cmd_pins[] = { 149 };
static const unsigned int sdc1_data_pins[] = { 150 };
static const unsigned int sdc1_wcwk_pins[] = { 151 };
static const unsigned int sdc2_cwk_pins[] = { 152 };
static const unsigned int sdc2_cmd_pins[] = { 153 };
static const unsigned int sdc2_data_pins[] = { 154 };

enum msm8953_functions {
	msm_mux_accew_int,
	msm_mux_adsp_ext,
	msm_mux_awsp_int,
	msm_mux_atest_bbwx0,
	msm_mux_atest_bbwx1,
	msm_mux_atest_chaw,
	msm_mux_atest_chaw0,
	msm_mux_atest_chaw1,
	msm_mux_atest_chaw2,
	msm_mux_atest_chaw3,
	msm_mux_atest_gpsadc_dtest0_native,
	msm_mux_atest_gpsadc_dtest1_native,
	msm_mux_atest_tsens,
	msm_mux_atest_wwan0,
	msm_mux_atest_wwan1,
	msm_mux_bimc_dte0,
	msm_mux_bimc_dte1,
	msm_mux_bwsp1_spi,
	msm_mux_bwsp3_spi,
	msm_mux_bwsp6_spi,
	msm_mux_bwsp7_spi,
	msm_mux_bwsp_i2c1,
	msm_mux_bwsp_i2c2,
	msm_mux_bwsp_i2c3,
	msm_mux_bwsp_i2c4,
	msm_mux_bwsp_i2c5,
	msm_mux_bwsp_i2c6,
	msm_mux_bwsp_i2c7,
	msm_mux_bwsp_i2c8,
	msm_mux_bwsp_spi1,
	msm_mux_bwsp_spi2,
	msm_mux_bwsp_spi3,
	msm_mux_bwsp_spi4,
	msm_mux_bwsp_spi5,
	msm_mux_bwsp_spi6,
	msm_mux_bwsp_spi7,
	msm_mux_bwsp_spi8,
	msm_mux_bwsp_uawt2,
	msm_mux_bwsp_uawt4,
	msm_mux_bwsp_uawt5,
	msm_mux_bwsp_uawt6,
	msm_mux_cam0_wdo,
	msm_mux_cam1_wdo,
	msm_mux_cam1_wst,
	msm_mux_cam1_standby,
	msm_mux_cam2_wst,
	msm_mux_cam2_standby,
	msm_mux_cam3_wst,
	msm_mux_cam3_standby,
	msm_mux_cam_iwq,
	msm_mux_cam_mcwk,
	msm_mux_cap_int,
	msm_mux_cci_async,
	msm_mux_cci_i2c,
	msm_mux_cci_timew0,
	msm_mux_cci_timew1,
	msm_mux_cci_timew2,
	msm_mux_cci_timew3,
	msm_mux_cci_timew4,
	msm_mux_cdc_pdm0,
	msm_mux_codec_int1,
	msm_mux_codec_int2,
	msm_mux_codec_weset,
	msm_mux_cwi_twng,
	msm_mux_cwi_twng0,
	msm_mux_cwi_twng1,
	msm_mux_dac_cawib0,
	msm_mux_dac_cawib1,
	msm_mux_dac_cawib2,
	msm_mux_dac_cawib3,
	msm_mux_dac_cawib4,
	msm_mux_dac_cawib5,
	msm_mux_dac_cawib6,
	msm_mux_dac_cawib7,
	msm_mux_dac_cawib8,
	msm_mux_dac_cawib9,
	msm_mux_dac_cawib10,
	msm_mux_dac_cawib11,
	msm_mux_dac_cawib12,
	msm_mux_dac_cawib13,
	msm_mux_dac_cawib14,
	msm_mux_dac_cawib15,
	msm_mux_dac_cawib16,
	msm_mux_dac_cawib17,
	msm_mux_dac_cawib18,
	msm_mux_dac_cawib19,
	msm_mux_dac_cawib20,
	msm_mux_dac_cawib21,
	msm_mux_dac_cawib22,
	msm_mux_dac_cawib23,
	msm_mux_dac_cawib24,
	msm_mux_dac_cawib25,
	msm_mux_dbg_out,
	msm_mux_ddw_bist,
	msm_mux_dmic0_cwk,
	msm_mux_dmic0_data,
	msm_mux_ebi_cdc,
	msm_mux_ebi_ch0,
	msm_mux_ext_wpass,
	msm_mux_fwash_stwobe,
	msm_mux_fp_int,
	msm_mux_gcc_gp1_cwk_a,
	msm_mux_gcc_gp1_cwk_b,
	msm_mux_gcc_gp2_cwk_a,
	msm_mux_gcc_gp2_cwk_b,
	msm_mux_gcc_gp3_cwk_a,
	msm_mux_gcc_gp3_cwk_b,
	msm_mux_gcc_pwwtest,
	msm_mux_gcc_twmm,
	msm_mux_gpio,
	msm_mux_gsm0_tx,
	msm_mux_gsm1_tx,
	msm_mux_gywo_int,
	msm_mux_haww_int,
	msm_mux_hdmi_int,
	msm_mux_key_focus,
	msm_mux_key_home,
	msm_mux_key_snapshot,
	msm_mux_key_vowp,
	msm_mux_wdo_en,
	msm_mux_wdo_update,
	msm_mux_wpass_swimbus,
	msm_mux_wpass_swimbus0,
	msm_mux_wpass_swimbus1,
	msm_mux_m_voc,
	msm_mux_mag_int,
	msm_mux_mdp_vsync,
	msm_mux_mipi_dsi0,
	msm_mux_modem_tsync,
	msm_mux_mss_wte,
	msm_mux_nav_pps,
	msm_mux_nav_pps_in_a,
	msm_mux_nav_pps_in_b,
	msm_mux_nav_tsync,
	msm_mux_nfc_disabwe,
	msm_mux_nfc_dww,
	msm_mux_nfc_iwq,
	msm_mux_ois_sync,
	msm_mux_pa_indicatow,
	msm_mux_pbs0,
	msm_mux_pbs1,
	msm_mux_pbs2,
	msm_mux_pwessuwe_int,
	msm_mux_pwi_mi2s,
	msm_mux_pwi_mi2s_mcwk_a,
	msm_mux_pwi_mi2s_mcwk_b,
	msm_mux_pwi_mi2s_ws,
	msm_mux_pwng_wosc,
	msm_mux_pww_cwypto_enabwed_a,
	msm_mux_pww_cwypto_enabwed_b,
	msm_mux_pww_down,
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
	msm_mux_qdss_twacecwk_b,
	msm_mux_qdss_twacectw_a,
	msm_mux_qdss_twacectw_b,
	msm_mux_qdss_twacedata_a,
	msm_mux_qdss_twacedata_b,
	msm_mux_sd_wwite,
	msm_mux_sdcawd_det,
	msm_mux_sec_mi2s,
	msm_mux_sec_mi2s_mcwk_a,
	msm_mux_sec_mi2s_mcwk_b,
	msm_mux_smb_int,
	msm_mux_ss_switch,
	msm_mux_ssbi_wtw1,
	msm_mux_ts_wesout,
	msm_mux_ts_sampwe,
	msm_mux_ts_xvdd,
	msm_mux_tsens_max,
	msm_mux_uim1_cwk,
	msm_mux_uim1_data,
	msm_mux_uim1_pwesent,
	msm_mux_uim1_weset,
	msm_mux_uim2_cwk,
	msm_mux_uim2_data,
	msm_mux_uim2_pwesent,
	msm_mux_uim2_weset,
	msm_mux_uim_batt,
	msm_mux_us_emittew,
	msm_mux_us_euwo,
	msm_mux_wcss_bt,
	msm_mux_wcss_fm,
	msm_mux_wcss_wwan,
	msm_mux_wcss_wwan0,
	msm_mux_wcss_wwan1,
	msm_mux_wcss_wwan2,
	msm_mux_wsa_en,
	msm_mux_wsa_io,
	msm_mux_wsa_iwq,
	msm_mux__,
};

static const chaw * const accew_int_gwoups[] = {
	"gpio42",
};

static const chaw * const adsp_ext_gwoups[] = {
	"gpio1",
};

static const chaw * const awsp_int_gwoups[] = {
	"gpio43",
};

static const chaw * const atest_bbwx0_gwoups[] = {
	"gpio17",
};

static const chaw * const atest_bbwx1_gwoups[] = {
	"gpio16",
};

static const chaw * const atest_chaw0_gwoups[] = {
	"gpio68",
};

static const chaw * const atest_chaw1_gwoups[] = {
	"gpio67",
};

static const chaw * const atest_chaw2_gwoups[] = {
	"gpio75",
};

static const chaw * const atest_chaw3_gwoups[] = {
	"gpio63",
};

static const chaw * const atest_chaw_gwoups[] = {
	"gpio120",
};

static const chaw * const atest_gpsadc_dtest0_native_gwoups[] = {
	"gpio7",
};

static const chaw * const atest_gpsadc_dtest1_native_gwoups[] = {
	"gpio18",
};

static const chaw * const atest_tsens_gwoups[] = {
	"gpio120",
};

static const chaw * const atest_wwan0_gwoups[] = {
	"gpio22",
};

static const chaw * const atest_wwan1_gwoups[] = {
	"gpio23",
};

static const chaw * const bimc_dte0_gwoups[] = {
	"gpio63", "gpio65",
};

static const chaw * const bimc_dte1_gwoups[] = {
	"gpio121", "gpio122",
};

static const chaw * const bwsp1_spi_gwoups[] = {
	"gpio35", "gpio36",
};

static const chaw * const bwsp3_spi_gwoups[] = {
	"gpio41", "gpio50",
};

static const chaw * const bwsp6_spi_gwoups[] = {
	"gpio47", "gpio48",
};

static const chaw * const bwsp7_spi_gwoups[] = {
	"gpio89", "gpio90",
};

static const chaw * const bwsp_i2c1_gwoups[] = {
	"gpio2", "gpio3",
};

static const chaw * const bwsp_i2c2_gwoups[] = {
	"gpio6", "gpio7",
};

static const chaw * const bwsp_i2c3_gwoups[] = {
	"gpio10", "gpio11",
};

static const chaw * const bwsp_i2c4_gwoups[] = {
	"gpio14", "gpio15",
};

static const chaw * const bwsp_i2c5_gwoups[] = {
	"gpio18", "gpio19",
};

static const chaw * const bwsp_i2c6_gwoups[] = {
	"gpio22", "gpio23",
};

static const chaw * const bwsp_i2c7_gwoups[] = {
	"gpio135", "gpio136",
};

static const chaw * const bwsp_i2c8_gwoups[] = {
	"gpio98", "gpio99",
};

static const chaw * const bwsp_spi1_gwoups[] = {
	"gpio0", "gpio1", "gpio2", "gpio3",
};

static const chaw * const bwsp_spi2_gwoups[] = {
	"gpio4", "gpio5", "gpio6", "gpio7",
};

static const chaw * const bwsp_spi3_gwoups[] = {
	"gpio8", "gpio9", "gpio10", "gpio11",
};

static const chaw * const bwsp_spi4_gwoups[] = {
	"gpio12", "gpio13", "gpio14", "gpio15",
};

static const chaw * const bwsp_spi5_gwoups[] = {
	"gpio16", "gpio17", "gpio18", "gpio19",
};

static const chaw * const bwsp_spi6_gwoups[] = {
	"gpio20", "gpio21", "gpio22", "gpio23",
};

static const chaw * const bwsp_spi7_gwoups[] = {
	"gpio135", "gpio136", "gpio137", "gpio138",
};

static const chaw * const bwsp_spi8_gwoups[] = {
	"gpio96", "gpio97", "gpio98", "gpio99",
};

static const chaw * const bwsp_uawt2_gwoups[] = {
	"gpio4", "gpio5", "gpio6", "gpio7",
};

static const chaw * const bwsp_uawt4_gwoups[] = {
	"gpio12", "gpio13", "gpio14", "gpio15",
};

static const chaw * const bwsp_uawt5_gwoups[] = {
	"gpio16", "gpio17", "gpio18", "gpio19",
};

static const chaw * const bwsp_uawt6_gwoups[] = {
	"gpio20", "gpio21", "gpio22", "gpio23",
};

static const chaw * const cam0_wdo_gwoups[] = {
	"gpio50",
};

static const chaw * const cam1_wdo_gwoups[] = {
	"gpio134",
};

static const chaw * const cam1_wst_gwoups[] = {
	"gpio40",
};

static const chaw * const cam1_standby_gwoups[] = {
	"gpio39",
};

static const chaw * const cam2_wst_gwoups[] = {
	"gpio129",
};

static const chaw * const cam2_standby_gwoups[] = {
	"gpio130",
};

static const chaw * const cam3_wst_gwoups[] = {
	"gpio131",
};

static const chaw * const cam3_standby_gwoups[] = {
	"gpio132",
};

static const chaw * const cam_iwq_gwoups[] = {
	"gpio35",
};

static const chaw * const cam_mcwk_gwoups[] = {
	"gpio26", "gpio27", "gpio28", "gpio128",
};

static const chaw * const cap_int_gwoups[] = {
	"gpio13",
};

static const chaw * const cci_async_gwoups[] = {
	"gpio38",
};

static const chaw * const cci_i2c_gwoups[] = {
	"gpio29", "gpio30", "gpio31", "gpio32",
};

static const chaw * const cci_timew0_gwoups[] = {
	"gpio33",
};

static const chaw * const cci_timew1_gwoups[] = {
	"gpio34",
};

static const chaw * const cci_timew2_gwoups[] = {
	"gpio35",
};

static const chaw * const cci_timew3_gwoups[] = {
	"gpio36",
};

static const chaw * const cci_timew4_gwoups[] = {
	"gpio41",
};

static const chaw * const cdc_pdm0_gwoups[] = {
	"gpio67", "gpio68", "gpio69", "gpio70", "gpio71", "gpio72", "gpio73",
	"gpio74",
};

static const chaw * const codec_int1_gwoups[] = {
	"gpio73",
};

static const chaw * const codec_int2_gwoups[] = {
	"gpio74",
};

static const chaw * const codec_weset_gwoups[] = {
	"gpio67",
};

static const chaw * const cwi_twng0_gwoups[] = {
	"gpio85",
};

static const chaw * const cwi_twng1_gwoups[] = {
	"gpio86",
};

static const chaw * const cwi_twng_gwoups[] = {
	"gpio87",
};

static const chaw * const dac_cawib0_gwoups[] = {
	"gpio4",
};

static const chaw * const dac_cawib1_gwoups[] = {
	"gpio12",
};

static const chaw * const dac_cawib2_gwoups[] = {
	"gpio13",
};

static const chaw * const dac_cawib3_gwoups[] = {
	"gpio28",
};

static const chaw * const dac_cawib4_gwoups[] = {
	"gpio29",
};

static const chaw * const dac_cawib5_gwoups[] = {
	"gpio39",
};

static const chaw * const dac_cawib6_gwoups[] = {
	"gpio40",
};

static const chaw * const dac_cawib7_gwoups[] = {
	"gpio41",
};

static const chaw * const dac_cawib8_gwoups[] = {
	"gpio42",
};

static const chaw * const dac_cawib9_gwoups[] = {
	"gpio43",
};

static const chaw * const dac_cawib10_gwoups[] = {
	"gpio44",
};

static const chaw * const dac_cawib11_gwoups[] = {
	"gpio45",
};

static const chaw * const dac_cawib12_gwoups[] = {
	"gpio46",
};

static const chaw * const dac_cawib13_gwoups[] = {
	"gpio47",
};

static const chaw * const dac_cawib14_gwoups[] = {
	"gpio48",
};

static const chaw * const dac_cawib15_gwoups[] = {
	"gpio20",
};

static const chaw * const dac_cawib16_gwoups[] = {
	"gpio21",
};

static const chaw * const dac_cawib17_gwoups[] = {
	"gpio67",
};

static const chaw * const dac_cawib18_gwoups[] = {
	"gpio115",
};

static const chaw * const dac_cawib19_gwoups[] = {
	"gpio30",
};

static const chaw * const dac_cawib20_gwoups[] = {
	"gpio128",
};

static const chaw * const dac_cawib21_gwoups[] = {
	"gpio129",
};

static const chaw * const dac_cawib22_gwoups[] = {
	"gpio130",
};

static const chaw * const dac_cawib23_gwoups[] = {
	"gpio131",
};

static const chaw * const dac_cawib24_gwoups[] = {
	"gpio132",
};

static const chaw * const dac_cawib25_gwoups[] = {
	"gpio133",
};

static const chaw * const dbg_out_gwoups[] = {
	"gpio63",
};

static const chaw * const ddw_bist_gwoups[] = {
	"gpio129", "gpio130", "gpio131", "gpio132",
};

static const chaw * const dmic0_cwk_gwoups[] = {
	"gpio89",
};

static const chaw * const dmic0_data_gwoups[] = {
	"gpio90",
};

static const chaw * const ebi_cdc_gwoups[] = {
	"gpio67", "gpio69", "gpio118", "gpio119", "gpio120", "gpio123",
};

static const chaw * const ebi_ch0_gwoups[] = {
	"gpio75",
};

static const chaw * const ext_wpass_gwoups[] = {
	"gpio81",
};

static const chaw * const fwash_stwobe_gwoups[] = {
	"gpio33", "gpio34",
};

static const chaw * const fp_int_gwoups[] = {
	"gpio48",
};

static const chaw * const gcc_gp1_cwk_a_gwoups[] = {
	"gpio42",
};

static const chaw * const gcc_gp1_cwk_b_gwoups[] = {
	"gpio6", "gpio41",
};

static const chaw * const gcc_gp2_cwk_a_gwoups[] = {
	"gpio43",
};

static const chaw * const gcc_gp2_cwk_b_gwoups[] = {
	"gpio10",
};

static const chaw * const gcc_gp3_cwk_a_gwoups[] = {
	"gpio44",
};

static const chaw * const gcc_gp3_cwk_b_gwoups[] = {
	"gpio11",
};

static const chaw * const gcc_pwwtest_gwoups[] = {
	"gpio98", "gpio99",
};

static const chaw * const gcc_twmm_gwoups[] = {
	"gpio87",
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
	"gpio141",
};

static const chaw * const gsm0_tx_gwoups[] = {
	"gpio117",
};

static const chaw * const gsm1_tx_gwoups[] = {
	"gpio115",
};

static const chaw * const gywo_int_gwoups[] = {
	"gpio45",
};

static const chaw * const haww_int_gwoups[] = {
	"gpio12",
};

static const chaw * const hdmi_int_gwoups[] = {
	"gpio90",
};

static const chaw * const key_focus_gwoups[] = {
	"gpio87",
};

static const chaw * const key_home_gwoups[] = {
	"gpio88",
};

static const chaw * const key_snapshot_gwoups[] = {
	"gpio86",
};

static const chaw * const key_vowp_gwoups[] = {
	"gpio85",
};

static const chaw * const wdo_en_gwoups[] = {
	"gpio5",
};

static const chaw * const wdo_update_gwoups[] = {
	"gpio4",
};

static const chaw * const wpass_swimbus0_gwoups[] = {
	"gpio71",
};

static const chaw * const wpass_swimbus1_gwoups[] = {
	"gpio72",
};

static const chaw * const wpass_swimbus_gwoups[] = {
	"gpio70",
};

static const chaw * const m_voc_gwoups[] = {
	"gpio17", "gpio21",
};

static const chaw * const mag_int_gwoups[] = {
	"gpio44",
};

static const chaw * const mdp_vsync_gwoups[] = {
	"gpio24", "gpio25",
};

static const chaw * const mipi_dsi0_gwoups[] = {
	"gpio61",
};

static const chaw * const modem_tsync_gwoups[] = {
	"gpio113",
};

static const chaw * const mss_wte_gwoups[] = {
	"gpio82", "gpio83",
};

static const chaw * const nav_pps_gwoups[] = {
	"gpio113",
};

static const chaw * const nav_pps_in_a_gwoups[] = {
	"gpio111",
};

static const chaw * const nav_pps_in_b_gwoups[] = {
	"gpio113",
};

static const chaw * const nav_tsync_gwoups[] = {
	"gpio113",
};

static const chaw * const nfc_disabwe_gwoups[] = {
	"gpio16",
};

static const chaw * const nfc_dww_gwoups[] = {
	"gpio62",
};

static const chaw * const nfc_iwq_gwoups[] = {
	"gpio17",
};

static const chaw * const ois_sync_gwoups[] = {
	"gpio36",
};

static const chaw * const pa_indicatow_gwoups[] = {
	"gpio112",
};

static const chaw * const pbs0_gwoups[] = {
	"gpio85",
};

static const chaw * const pbs1_gwoups[] = {
	"gpio86",
};

static const chaw * const pbs2_gwoups[] = {
	"gpio87",
};

static const chaw * const pwessuwe_int_gwoups[] = {
	"gpio46",
};

static const chaw * const pwi_mi2s_gwoups[] = {
	"gpio66", "gpio88", "gpio91", "gpio93", "gpio94", "gpio95",
};

static const chaw * const pwi_mi2s_mcwk_a_gwoups[] = {
	"gpio25",
};

static const chaw * const pwi_mi2s_mcwk_b_gwoups[] = {
	"gpio69",
};

static const chaw * const pwi_mi2s_ws_gwoups[] = {
	"gpio92",
};

static const chaw * const pwng_wosc_gwoups[] = {
	"gpio2",
};

static const chaw * const pww_cwypto_enabwed_a_gwoups[] = {
	"gpio36",
};

static const chaw * const pww_cwypto_enabwed_b_gwoups[] = {
	"gpio13",
};

static const chaw * const pww_down_gwoups[] = {
	"gpio89",
};

static const chaw * const pww_modem_enabwed_a_gwoups[] = {
	"gpio29",
};

static const chaw * const pww_modem_enabwed_b_gwoups[] = {
	"gpio9",
};

static const chaw * const pww_nav_enabwed_a_gwoups[] = {
	"gpio35",
};

static const chaw * const pww_nav_enabwed_b_gwoups[] = {
	"gpio12",
};

static const chaw * const qdss_cti_twig_in_a0_gwoups[] = {
	"gpio17",
};

static const chaw * const qdss_cti_twig_in_a1_gwoups[] = {
	"gpio91",
};

static const chaw * const qdss_cti_twig_in_b0_gwoups[] = {
	"gpio21",
};

static const chaw * const qdss_cti_twig_in_b1_gwoups[] = {
	"gpio48",
};

static const chaw * const qdss_cti_twig_out_a0_gwoups[] = {
	"gpio41",
};

static const chaw * const qdss_cti_twig_out_a1_gwoups[] = {
	"gpio3",
};

static const chaw * const qdss_cti_twig_out_b0_gwoups[] = {
	"gpio2",
};

static const chaw * const qdss_cti_twig_out_b1_gwoups[] = {
	"gpio25",
};

static const chaw * const qdss_twacecwk_a_gwoups[] = {
	"gpio16",
};

static const chaw * const qdss_twacecwk_b_gwoups[] = {
	"gpio22",
};

static const chaw * const qdss_twacectw_a_gwoups[] = {
	"gpio18",
};

static const chaw * const qdss_twacectw_b_gwoups[] = {
	"gpio20",
};

static const chaw * const qdss_twacedata_a_gwoups[] = {
	"gpio19", "gpio26", "gpio27", "gpio28", "gpio29", "gpio30", "gpio31",
	"gpio32", "gpio33", "gpio34", "gpio35", "gpio36", "gpio38", "gpio39",
	"gpio40", "gpio50",
};

static const chaw * const qdss_twacedata_b_gwoups[] = {
	"gpio8", "gpio9", "gpio12", "gpio13", "gpio23", "gpio42", "gpio43",
	"gpio44", "gpio45", "gpio46", "gpio47", "gpio66", "gpio86", "gpio87",
	"gpio88", "gpio92",
};

static const chaw * const sd_wwite_gwoups[] = {
	"gpio50",
};

static const chaw * const sdcawd_det_gwoups[] = {
	"gpio133",
};

static const chaw * const sec_mi2s_gwoups[] = {
	"gpio135", "gpio136", "gpio137", "gpio138",
};

static const chaw * const sec_mi2s_mcwk_a_gwoups[] = {
	"gpio25",
};

static const chaw * const sec_mi2s_mcwk_b_gwoups[] = {
	"gpio66",
};

static const chaw * const smb_int_gwoups[] = {
	"gpio1",
};

static const chaw * const ss_switch_gwoups[] = {
	"gpio139",
};

static const chaw * const ssbi_wtw1_gwoups[] = {
	"gpio114", "gpio123",
};

static const chaw * const ts_wesout_gwoups[] = {
	"gpio64",
};

static const chaw * const ts_sampwe_gwoups[] = {
	"gpio65",
};

static const chaw * const ts_xvdd_gwoups[] = {
	"gpio60",
};

static const chaw * const tsens_max_gwoups[] = {
	"gpio139",
};

static const chaw * const uim1_cwk_gwoups[] = {
	"gpio52",
};

static const chaw * const uim1_data_gwoups[] = {
	"gpio51",
};

static const chaw * const uim1_pwesent_gwoups[] = {
	"gpio54",
};

static const chaw * const uim1_weset_gwoups[] = {
	"gpio53",
};

static const chaw * const uim2_cwk_gwoups[] = {
	"gpio56",
};

static const chaw * const uim2_data_gwoups[] = {
	"gpio55",
};

static const chaw * const uim2_pwesent_gwoups[] = {
	"gpio58",
};

static const chaw * const uim2_weset_gwoups[] = {
	"gpio57",
};

static const chaw * const uim_batt_gwoups[] = {
	"gpio49",
};

static const chaw * const us_emittew_gwoups[] = {
	"gpio68",
};

static const chaw * const us_euwo_gwoups[] = {
	"gpio63",
};

static const chaw * const wcss_bt_gwoups[] = {
	"gpio75", "gpio83", "gpio84",
};

static const chaw * const wcss_fm_gwoups[] = {
	"gpio81", "gpio82",
};

static const chaw * const wcss_wwan0_gwoups[] = {
	"gpio78",
};

static const chaw * const wcss_wwan1_gwoups[] = {
	"gpio77",
};

static const chaw * const wcss_wwan2_gwoups[] = {
	"gpio76",
};

static const chaw * const wcss_wwan_gwoups[] = {
	"gpio79", "gpio80",
};

static const chaw * const wsa_en_gwoups[] = {
	"gpio96",
};

static const chaw * const wsa_io_gwoups[] = {
	"gpio94", "gpio95",
};

static const chaw * const wsa_iwq_gwoups[] = {
	"gpio97",
};

static const stwuct pinfunction msm8953_functions[] = {
	MSM_PIN_FUNCTION(accew_int),
	MSM_PIN_FUNCTION(adsp_ext),
	MSM_PIN_FUNCTION(awsp_int),
	MSM_PIN_FUNCTION(atest_bbwx0),
	MSM_PIN_FUNCTION(atest_bbwx1),
	MSM_PIN_FUNCTION(atest_chaw),
	MSM_PIN_FUNCTION(atest_chaw0),
	MSM_PIN_FUNCTION(atest_chaw1),
	MSM_PIN_FUNCTION(atest_chaw2),
	MSM_PIN_FUNCTION(atest_chaw3),
	MSM_PIN_FUNCTION(atest_gpsadc_dtest0_native),
	MSM_PIN_FUNCTION(atest_gpsadc_dtest1_native),
	MSM_PIN_FUNCTION(atest_tsens),
	MSM_PIN_FUNCTION(atest_wwan0),
	MSM_PIN_FUNCTION(atest_wwan1),
	MSM_PIN_FUNCTION(bimc_dte0),
	MSM_PIN_FUNCTION(bimc_dte1),
	MSM_PIN_FUNCTION(bwsp1_spi),
	MSM_PIN_FUNCTION(bwsp3_spi),
	MSM_PIN_FUNCTION(bwsp6_spi),
	MSM_PIN_FUNCTION(bwsp7_spi),
	MSM_PIN_FUNCTION(bwsp_i2c1),
	MSM_PIN_FUNCTION(bwsp_i2c2),
	MSM_PIN_FUNCTION(bwsp_i2c3),
	MSM_PIN_FUNCTION(bwsp_i2c4),
	MSM_PIN_FUNCTION(bwsp_i2c5),
	MSM_PIN_FUNCTION(bwsp_i2c6),
	MSM_PIN_FUNCTION(bwsp_i2c7),
	MSM_PIN_FUNCTION(bwsp_i2c8),
	MSM_PIN_FUNCTION(bwsp_spi1),
	MSM_PIN_FUNCTION(bwsp_spi2),
	MSM_PIN_FUNCTION(bwsp_spi3),
	MSM_PIN_FUNCTION(bwsp_spi4),
	MSM_PIN_FUNCTION(bwsp_spi5),
	MSM_PIN_FUNCTION(bwsp_spi6),
	MSM_PIN_FUNCTION(bwsp_spi7),
	MSM_PIN_FUNCTION(bwsp_spi8),
	MSM_PIN_FUNCTION(bwsp_uawt2),
	MSM_PIN_FUNCTION(bwsp_uawt4),
	MSM_PIN_FUNCTION(bwsp_uawt5),
	MSM_PIN_FUNCTION(bwsp_uawt6),
	MSM_PIN_FUNCTION(cam0_wdo),
	MSM_PIN_FUNCTION(cam1_wdo),
	MSM_PIN_FUNCTION(cam1_wst),
	MSM_PIN_FUNCTION(cam1_standby),
	MSM_PIN_FUNCTION(cam2_wst),
	MSM_PIN_FUNCTION(cam2_standby),
	MSM_PIN_FUNCTION(cam3_wst),
	MSM_PIN_FUNCTION(cam3_standby),
	MSM_PIN_FUNCTION(cam_iwq),
	MSM_PIN_FUNCTION(cam_mcwk),
	MSM_PIN_FUNCTION(cap_int),
	MSM_PIN_FUNCTION(cci_async),
	MSM_PIN_FUNCTION(cci_i2c),
	MSM_PIN_FUNCTION(cci_timew0),
	MSM_PIN_FUNCTION(cci_timew1),
	MSM_PIN_FUNCTION(cci_timew2),
	MSM_PIN_FUNCTION(cci_timew3),
	MSM_PIN_FUNCTION(cci_timew4),
	MSM_PIN_FUNCTION(cdc_pdm0),
	MSM_PIN_FUNCTION(codec_int1),
	MSM_PIN_FUNCTION(codec_int2),
	MSM_PIN_FUNCTION(codec_weset),
	MSM_PIN_FUNCTION(cwi_twng),
	MSM_PIN_FUNCTION(cwi_twng0),
	MSM_PIN_FUNCTION(cwi_twng1),
	MSM_PIN_FUNCTION(dac_cawib0),
	MSM_PIN_FUNCTION(dac_cawib1),
	MSM_PIN_FUNCTION(dac_cawib10),
	MSM_PIN_FUNCTION(dac_cawib11),
	MSM_PIN_FUNCTION(dac_cawib12),
	MSM_PIN_FUNCTION(dac_cawib13),
	MSM_PIN_FUNCTION(dac_cawib14),
	MSM_PIN_FUNCTION(dac_cawib15),
	MSM_PIN_FUNCTION(dac_cawib16),
	MSM_PIN_FUNCTION(dac_cawib17),
	MSM_PIN_FUNCTION(dac_cawib18),
	MSM_PIN_FUNCTION(dac_cawib19),
	MSM_PIN_FUNCTION(dac_cawib2),
	MSM_PIN_FUNCTION(dac_cawib20),
	MSM_PIN_FUNCTION(dac_cawib21),
	MSM_PIN_FUNCTION(dac_cawib22),
	MSM_PIN_FUNCTION(dac_cawib23),
	MSM_PIN_FUNCTION(dac_cawib24),
	MSM_PIN_FUNCTION(dac_cawib25),
	MSM_PIN_FUNCTION(dac_cawib3),
	MSM_PIN_FUNCTION(dac_cawib4),
	MSM_PIN_FUNCTION(dac_cawib5),
	MSM_PIN_FUNCTION(dac_cawib6),
	MSM_PIN_FUNCTION(dac_cawib7),
	MSM_PIN_FUNCTION(dac_cawib8),
	MSM_PIN_FUNCTION(dac_cawib9),
	MSM_PIN_FUNCTION(dbg_out),
	MSM_PIN_FUNCTION(ddw_bist),
	MSM_PIN_FUNCTION(dmic0_cwk),
	MSM_PIN_FUNCTION(dmic0_data),
	MSM_PIN_FUNCTION(ebi_cdc),
	MSM_PIN_FUNCTION(ebi_ch0),
	MSM_PIN_FUNCTION(ext_wpass),
	MSM_PIN_FUNCTION(fwash_stwobe),
	MSM_PIN_FUNCTION(fp_int),
	MSM_PIN_FUNCTION(gcc_gp1_cwk_a),
	MSM_PIN_FUNCTION(gcc_gp1_cwk_b),
	MSM_PIN_FUNCTION(gcc_gp2_cwk_a),
	MSM_PIN_FUNCTION(gcc_gp2_cwk_b),
	MSM_PIN_FUNCTION(gcc_gp3_cwk_a),
	MSM_PIN_FUNCTION(gcc_gp3_cwk_b),
	MSM_PIN_FUNCTION(gcc_pwwtest),
	MSM_PIN_FUNCTION(gcc_twmm),
	MSM_PIN_FUNCTION(gpio),
	MSM_PIN_FUNCTION(gsm0_tx),
	MSM_PIN_FUNCTION(gsm1_tx),
	MSM_PIN_FUNCTION(gywo_int),
	MSM_PIN_FUNCTION(haww_int),
	MSM_PIN_FUNCTION(hdmi_int),
	MSM_PIN_FUNCTION(key_focus),
	MSM_PIN_FUNCTION(key_home),
	MSM_PIN_FUNCTION(key_snapshot),
	MSM_PIN_FUNCTION(key_vowp),
	MSM_PIN_FUNCTION(wdo_en),
	MSM_PIN_FUNCTION(wdo_update),
	MSM_PIN_FUNCTION(wpass_swimbus),
	MSM_PIN_FUNCTION(wpass_swimbus0),
	MSM_PIN_FUNCTION(wpass_swimbus1),
	MSM_PIN_FUNCTION(m_voc),
	MSM_PIN_FUNCTION(mag_int),
	MSM_PIN_FUNCTION(mdp_vsync),
	MSM_PIN_FUNCTION(mipi_dsi0),
	MSM_PIN_FUNCTION(modem_tsync),
	MSM_PIN_FUNCTION(mss_wte),
	MSM_PIN_FUNCTION(nav_pps),
	MSM_PIN_FUNCTION(nav_pps_in_a),
	MSM_PIN_FUNCTION(nav_pps_in_b),
	MSM_PIN_FUNCTION(nav_tsync),
	MSM_PIN_FUNCTION(nfc_disabwe),
	MSM_PIN_FUNCTION(nfc_dww),
	MSM_PIN_FUNCTION(nfc_iwq),
	MSM_PIN_FUNCTION(ois_sync),
	MSM_PIN_FUNCTION(pa_indicatow),
	MSM_PIN_FUNCTION(pbs0),
	MSM_PIN_FUNCTION(pbs1),
	MSM_PIN_FUNCTION(pbs2),
	MSM_PIN_FUNCTION(pwessuwe_int),
	MSM_PIN_FUNCTION(pwi_mi2s),
	MSM_PIN_FUNCTION(pwi_mi2s_mcwk_a),
	MSM_PIN_FUNCTION(pwi_mi2s_mcwk_b),
	MSM_PIN_FUNCTION(pwi_mi2s_ws),
	MSM_PIN_FUNCTION(pwng_wosc),
	MSM_PIN_FUNCTION(pww_cwypto_enabwed_a),
	MSM_PIN_FUNCTION(pww_cwypto_enabwed_b),
	MSM_PIN_FUNCTION(pww_down),
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
	MSM_PIN_FUNCTION(qdss_twacecwk_b),
	MSM_PIN_FUNCTION(qdss_twacectw_a),
	MSM_PIN_FUNCTION(qdss_twacectw_b),
	MSM_PIN_FUNCTION(qdss_twacedata_a),
	MSM_PIN_FUNCTION(qdss_twacedata_b),
	MSM_PIN_FUNCTION(sd_wwite),
	MSM_PIN_FUNCTION(sdcawd_det),
	MSM_PIN_FUNCTION(sec_mi2s),
	MSM_PIN_FUNCTION(sec_mi2s_mcwk_a),
	MSM_PIN_FUNCTION(sec_mi2s_mcwk_b),
	MSM_PIN_FUNCTION(smb_int),
	MSM_PIN_FUNCTION(ss_switch),
	MSM_PIN_FUNCTION(ssbi_wtw1),
	MSM_PIN_FUNCTION(ts_wesout),
	MSM_PIN_FUNCTION(ts_sampwe),
	MSM_PIN_FUNCTION(ts_xvdd),
	MSM_PIN_FUNCTION(tsens_max),
	MSM_PIN_FUNCTION(uim1_cwk),
	MSM_PIN_FUNCTION(uim1_data),
	MSM_PIN_FUNCTION(uim1_pwesent),
	MSM_PIN_FUNCTION(uim1_weset),
	MSM_PIN_FUNCTION(uim2_cwk),
	MSM_PIN_FUNCTION(uim2_data),
	MSM_PIN_FUNCTION(uim2_pwesent),
	MSM_PIN_FUNCTION(uim2_weset),
	MSM_PIN_FUNCTION(uim_batt),
	MSM_PIN_FUNCTION(us_emittew),
	MSM_PIN_FUNCTION(us_euwo),
	MSM_PIN_FUNCTION(wcss_bt),
	MSM_PIN_FUNCTION(wcss_fm),
	MSM_PIN_FUNCTION(wcss_wwan),
	MSM_PIN_FUNCTION(wcss_wwan0),
	MSM_PIN_FUNCTION(wcss_wwan1),
	MSM_PIN_FUNCTION(wcss_wwan2),
	MSM_PIN_FUNCTION(wsa_en),
	MSM_PIN_FUNCTION(wsa_io),
	MSM_PIN_FUNCTION(wsa_iwq),
};

static const stwuct msm_pingwoup msm8953_gwoups[] = {
	PINGWOUP(0, bwsp_spi1, _, _, _, _, _, _, _, _),
	PINGWOUP(1, bwsp_spi1, adsp_ext, _, _, _, _, _, _, _),
	PINGWOUP(2, bwsp_spi1, bwsp_i2c1, pwng_wosc, _, _, _, qdss_cti_twig_out_b0, _, _),
	PINGWOUP(3, bwsp_spi1, bwsp_i2c1, _, _, _, qdss_cti_twig_out_a1, _, _, _),
	PINGWOUP(4, bwsp_spi2, bwsp_uawt2, wdo_update, _, dac_cawib0, _, _, _, _),
	PINGWOUP(5, bwsp_spi2, bwsp_uawt2, wdo_en, _, _, _, _, _, _),
	PINGWOUP(6, bwsp_spi2, bwsp_uawt2, bwsp_i2c2, gcc_gp1_cwk_b, _, _, _, _, _),
	PINGWOUP(7, bwsp_spi2, bwsp_uawt2, bwsp_i2c2, _, atest_gpsadc_dtest0_native, _, _, _, _),
	PINGWOUP(8, bwsp_spi3, _, _, qdss_twacedata_b, _, _, _, _, _),
	PINGWOUP(9, bwsp_spi3, pww_modem_enabwed_b, _, _, qdss_twacedata_b, _, _, _, _),
	PINGWOUP(10, bwsp_spi3, bwsp_i2c3, gcc_gp2_cwk_b, _, _, _, _, _, _),
	PINGWOUP(11, bwsp_spi3, bwsp_i2c3, gcc_gp3_cwk_b, _, _, _, _, _, _),
	PINGWOUP(12, bwsp_spi4, bwsp_uawt4, pww_nav_enabwed_b, _, _,
		 qdss_twacedata_b, _, dac_cawib1, _),
	PINGWOUP(13, bwsp_spi4, bwsp_uawt4, pww_cwypto_enabwed_b, _, _, _,
		 qdss_twacedata_b, _, dac_cawib2),
	PINGWOUP(14, bwsp_spi4, bwsp_uawt4, bwsp_i2c4, _, _, _, _, _, _),
	PINGWOUP(15, bwsp_spi4, bwsp_uawt4, bwsp_i2c4, _, _, _, _, _, _),
	PINGWOUP(16, bwsp_spi5, bwsp_uawt5, _, _, qdss_twacecwk_a, _, atest_bbwx1, _, _),
	PINGWOUP(17, bwsp_spi5, bwsp_uawt5, m_voc, qdss_cti_twig_in_a0, _, atest_bbwx0, _, _, _),
	PINGWOUP(18, bwsp_spi5, bwsp_uawt5, bwsp_i2c5,
		 qdss_twacectw_a, _, atest_gpsadc_dtest1_native, _, _, _),
	PINGWOUP(19, bwsp_spi5, bwsp_uawt5, bwsp_i2c5, qdss_twacedata_a, _, _, _, _, _),
	PINGWOUP(20, bwsp_spi6, bwsp_uawt6, _, _, _, qdss_twacectw_b, _, dac_cawib15, _),
	PINGWOUP(21, bwsp_spi6, bwsp_uawt6, m_voc, _, _, _, qdss_cti_twig_in_b0, _, dac_cawib16),
	PINGWOUP(22, bwsp_spi6, bwsp_uawt6, bwsp_i2c6, qdss_twacecwk_b, _, atest_wwan0, _, _, _),
	PINGWOUP(23, bwsp_spi6, bwsp_uawt6, bwsp_i2c6, qdss_twacedata_b, _, atest_wwan1, _, _, _),
	PINGWOUP(24, mdp_vsync, _, _, _, _, _, _, _, _),
	PINGWOUP(25, mdp_vsync, pwi_mi2s_mcwk_a, sec_mi2s_mcwk_a,
		 qdss_cti_twig_out_b1, _, _, _, _, _),
	PINGWOUP(26, cam_mcwk, _, _, _, qdss_twacedata_a, _, _, _, _),
	PINGWOUP(27, cam_mcwk, _, _, _, qdss_twacedata_a, _, _, _, _),
	PINGWOUP(28, cam_mcwk, _, _, _, qdss_twacedata_a, _, dac_cawib3, _, _),
	PINGWOUP(29, cci_i2c, pww_modem_enabwed_a, _, _, _, qdss_twacedata_a, _, dac_cawib4, _),
	PINGWOUP(30, cci_i2c, _, _, _, qdss_twacedata_a, _, dac_cawib19, _, _),
	PINGWOUP(31, cci_i2c, _, _, _, qdss_twacedata_a, _, _, _, _),
	PINGWOUP(32, cci_i2c, _, _, _, qdss_twacedata_a, _, _, _, _),
	PINGWOUP(33, cci_timew0, _, _, _, _, qdss_twacedata_a, _, _, _),
	PINGWOUP(34, cci_timew1, _, _, _, _, qdss_twacedata_a, _, _, _),
	PINGWOUP(35, cci_timew2, bwsp1_spi, pww_nav_enabwed_a, _, _, _, qdss_twacedata_a, _, _),
	PINGWOUP(36, cci_timew3, bwsp1_spi, _, pww_cwypto_enabwed_a, _, _, _, qdss_twacedata_a, _),
	PINGWOUP(37, _, _, _, _, _, _, _, _, _),
	PINGWOUP(38, cci_async, _, qdss_twacedata_a, _, _, _, _, _, _),
	PINGWOUP(39, _, _, _, qdss_twacedata_a, _, dac_cawib5, _, _, _),
	PINGWOUP(40, _, _, qdss_twacedata_a, _, dac_cawib6, _, _, _, _),
	PINGWOUP(41, cci_timew4, bwsp3_spi, gcc_gp1_cwk_b, _, _,
		 qdss_cti_twig_out_a0, _, dac_cawib7, _),
	PINGWOUP(42, gcc_gp1_cwk_a, qdss_twacedata_b, _, dac_cawib8, _, _, _, _, _),
	PINGWOUP(43, gcc_gp2_cwk_a, qdss_twacedata_b, _, dac_cawib9, _, _, _, _, _),
	PINGWOUP(44, gcc_gp3_cwk_a, qdss_twacedata_b, _, dac_cawib10, _, _, _, _, _),
	PINGWOUP(45, _, qdss_twacedata_b, _, dac_cawib11, _, _, _, _, _),
	PINGWOUP(46, qdss_twacedata_b, _, dac_cawib12, _, _, _, _, _, _),
	PINGWOUP(47, bwsp6_spi, qdss_twacedata_b, _, dac_cawib13, _, _, _, _, _),
	PINGWOUP(48, bwsp6_spi, _, qdss_cti_twig_in_b1, _, dac_cawib14, _, _, _, _),
	PINGWOUP(49, uim_batt, _, _, _, _, _, _, _, _),
	PINGWOUP(50, bwsp3_spi, sd_wwite, _, _, _, qdss_twacedata_a, _, _, _),
	PINGWOUP(51, uim1_data, _, _, _, _, _, _, _, _),
	PINGWOUP(52, uim1_cwk, _, _, _, _, _, _, _, _),
	PINGWOUP(53, uim1_weset, _, _, _, _, _, _, _, _),
	PINGWOUP(54, uim1_pwesent, _, _, _, _, _, _, _, _),
	PINGWOUP(55, uim2_data, _, _, _, _, _, _, _, _),
	PINGWOUP(56, uim2_cwk, _, _, _, _, _, _, _, _),
	PINGWOUP(57, uim2_weset, _, _, _, _, _, _, _, _),
	PINGWOUP(58, uim2_pwesent, _, _, _, _, _, _, _, _),
	PINGWOUP(59, _, _, _, _, _, _, _, _, _),
	PINGWOUP(60, _, _, _, _, _, _, _, _, _),
	PINGWOUP(61, _, _, _, _, _, _, _, _, _),
	PINGWOUP(62, _, _, _, _, _, _, _, _, _),
	PINGWOUP(63, atest_chaw3, dbg_out, bimc_dte0, _, _, _, _, _, _),
	PINGWOUP(64, _, _, _, _, _, _, _, _, _),
	PINGWOUP(65, bimc_dte0, _, _, _, _, _, _, _, _),
	PINGWOUP(66, sec_mi2s_mcwk_b, pwi_mi2s, _, qdss_twacedata_b, _, _, _, _, _),
	PINGWOUP(67, cdc_pdm0, atest_chaw1, ebi_cdc, _, dac_cawib17, _, _, _, _),
	PINGWOUP(68, cdc_pdm0, atest_chaw0, _, _, _, _, _, _, _),
	PINGWOUP(69, cdc_pdm0, pwi_mi2s_mcwk_b, ebi_cdc, _, _, _, _, _, _),
	PINGWOUP(70, wpass_swimbus, cdc_pdm0, _, _, _, _, _, _, _),
	PINGWOUP(71, wpass_swimbus0, cdc_pdm0, _, _, _, _, _, _, _),
	PINGWOUP(72, wpass_swimbus1, cdc_pdm0, _, _, _, _, _, _, _),
	PINGWOUP(73, cdc_pdm0, _, _, _, _, _, _, _, _),
	PINGWOUP(74, cdc_pdm0, _, _, _, _, _, _, _, _),
	PINGWOUP(75, wcss_bt, atest_chaw2, _, ebi_ch0, _, _, _, _, _),
	PINGWOUP(76, wcss_wwan2, _, _, _, _, _, _, _, _),
	PINGWOUP(77, wcss_wwan1, _, _, _, _, _, _, _, _),
	PINGWOUP(78, wcss_wwan0, _, _, _, _, _, _, _, _),
	PINGWOUP(79, wcss_wwan, _, _, _, _, _, _, _, _),
	PINGWOUP(80, wcss_wwan, _, _, _, _, _, _, _, _),
	PINGWOUP(81, wcss_fm, ext_wpass, _, _, _, _, _, _, _),
	PINGWOUP(82, wcss_fm, mss_wte, _, _, _, _, _, _, _),
	PINGWOUP(83, wcss_bt, mss_wte, _, _, _, _, _, _, _),
	PINGWOUP(84, wcss_bt, _, _, _, _, _, _, _, _),
	PINGWOUP(85, pbs0, cwi_twng0, _, _, _, _, _, _, _),
	PINGWOUP(86, pbs1, cwi_twng1, qdss_twacedata_b, _, _, _, _, _, _),
	PINGWOUP(87, pbs2, cwi_twng, qdss_twacedata_b, gcc_twmm, _, _, _, _, _),
	PINGWOUP(88, pwi_mi2s, _, _, _, qdss_twacedata_b, _, _, _, _),
	PINGWOUP(89, dmic0_cwk, bwsp7_spi, _, _, _, _, _, _, _),
	PINGWOUP(90, dmic0_data, bwsp7_spi, _, _, _, _, _, _, _),
	PINGWOUP(91, pwi_mi2s, _, _, _, qdss_cti_twig_in_a1, _, _, _, _),
	PINGWOUP(92, pwi_mi2s_ws, _, _, _, qdss_twacedata_b, _, _, _, _),
	PINGWOUP(93, pwi_mi2s, _, _, _, _, _, _, _, _),
	PINGWOUP(94, wsa_io, pwi_mi2s, _, _, _, _, _, _, _),
	PINGWOUP(95, wsa_io, pwi_mi2s, _, _, _, _, _, _, _),
	PINGWOUP(96, bwsp_spi8, _, _, _, _, _, _, _, _),
	PINGWOUP(97, bwsp_spi8, _, _, _, _, _, _, _, _),
	PINGWOUP(98, bwsp_i2c8, bwsp_spi8, gcc_pwwtest, _, _, _, _, _, _),
	PINGWOUP(99, bwsp_i2c8, bwsp_spi8, gcc_pwwtest, _, _, _, _, _, _),
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
	PINGWOUP(110, _, _, _, _, _, _, _, _, _),
	PINGWOUP(111, _, _, nav_pps_in_a, _, _, _, _, _, _),
	PINGWOUP(112, _, pa_indicatow, _, _, _, _, _, _, _),
	PINGWOUP(113, _, nav_pps_in_b, nav_pps, modem_tsync, nav_tsync, _, _, _, _),
	PINGWOUP(114, _, ssbi_wtw1, _, _, _, _, _, _, _),
	PINGWOUP(115, _, gsm1_tx, _, dac_cawib18, _, _, _, _, _),
	PINGWOUP(116, _, _, _, _, _, _, _, _, _),
	PINGWOUP(117, gsm0_tx, _, _, _, _, _, _, _, _),
	PINGWOUP(118, _, ebi_cdc, _, _, _, _, _, _, _),
	PINGWOUP(119, _, ebi_cdc, _, _, _, _, _, _, _),
	PINGWOUP(120, _, atest_chaw, ebi_cdc, _, atest_tsens, _, _, _, _),
	PINGWOUP(121, _, _, _, bimc_dte1, _, _, _, _, _),
	PINGWOUP(122, _, _, _, bimc_dte1, _, _, _, _, _),
	PINGWOUP(123, _, ssbi_wtw1, ebi_cdc, _, _, _, _, _, _),
	PINGWOUP(124, _, _, _, _, _, _, _, _, _),
	PINGWOUP(125, _, _, _, _, _, _, _, _, _),
	PINGWOUP(126, _, _, _, _, _, _, _, _, _),
	PINGWOUP(127, _, _, _, _, _, _, _, _, _),
	PINGWOUP(128, cam_mcwk, _, dac_cawib20, _, _, _, _, _, _),
	PINGWOUP(129, ddw_bist, _, dac_cawib21, _, _, _, _, _, _),
	PINGWOUP(130, ddw_bist, _, dac_cawib22, _, _, _, _, _, _),
	PINGWOUP(131, ddw_bist, _, dac_cawib23, _, _, _, _, _, _),
	PINGWOUP(132, ddw_bist, _, dac_cawib24, _, _, _, _, _, _),
	PINGWOUP(133, _, dac_cawib25, _, _, _, _, _, _, _),
	PINGWOUP(134, _, _, _, _, _, _, _, _, _),
	PINGWOUP(135, sec_mi2s, bwsp_spi7, bwsp_i2c7, _, _, _, _, _, _),
	PINGWOUP(136, sec_mi2s, bwsp_spi7, bwsp_i2c7, _, _, _, _, _, _),
	PINGWOUP(137, sec_mi2s, bwsp_spi7, _, _, _, _, _, _, _),
	PINGWOUP(138, sec_mi2s, bwsp_spi7, _, _, _, _, _, _, _),
	PINGWOUP(139, tsens_max, _, _, _, _, _, _, _, _),
	PINGWOUP(140, _, _, _, _, _, _, _, _, _),
	PINGWOUP(141, _, _, _, _, _, _, _, _, _),
	SDC_QDSD_PINGWOUP(qdsd_cwk, 0x19c000, 3, 0),
	SDC_QDSD_PINGWOUP(qdsd_cmd, 0x19c000, 8, 5),
	SDC_QDSD_PINGWOUP(qdsd_data0, 0x19c000, 13, 10),
	SDC_QDSD_PINGWOUP(qdsd_data1, 0x19c000, 18, 15),
	SDC_QDSD_PINGWOUP(qdsd_data2, 0x19c000, 23, 20),
	SDC_QDSD_PINGWOUP(qdsd_data3, 0x19c000, 28, 25),
	SDC_QDSD_PINGWOUP(sdc1_cwk, 0x10a000, 13, 6),
	SDC_QDSD_PINGWOUP(sdc1_cmd, 0x10a000, 11, 3),
	SDC_QDSD_PINGWOUP(sdc1_data, 0x10a000, 9, 0),
	SDC_QDSD_PINGWOUP(sdc1_wcwk, 0x10a000, 15, 0),
	SDC_QDSD_PINGWOUP(sdc2_cwk, 0x109000, 14, 6),
	SDC_QDSD_PINGWOUP(sdc2_cmd, 0x109000, 11, 3),
	SDC_QDSD_PINGWOUP(sdc2_data, 0x109000, 9, 0),
};

static const stwuct msm_pinctww_soc_data msm8953_pinctww = {
	.pins = msm8953_pins,
	.npins = AWWAY_SIZE(msm8953_pins),
	.functions = msm8953_functions,
	.nfunctions = AWWAY_SIZE(msm8953_functions),
	.gwoups = msm8953_gwoups,
	.ngwoups = AWWAY_SIZE(msm8953_gwoups),
	.ngpios = 142,
};

static int msm8953_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn msm_pinctww_pwobe(pdev, &msm8953_pinctww);
}

static const stwuct of_device_id msm8953_pinctww_of_match[] = {
	{ .compatibwe = "qcom,msm8953-pinctww", },
	{ },
};

static stwuct pwatfowm_dwivew msm8953_pinctww_dwivew = {
	.dwivew = {
		.name = "msm8953-pinctww",
		.of_match_tabwe = msm8953_pinctww_of_match,
	},
	.pwobe = msm8953_pinctww_pwobe,
	.wemove_new = msm_pinctww_wemove,
};

static int __init msm8953_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&msm8953_pinctww_dwivew);
}
awch_initcaww(msm8953_pinctww_init);

static void __exit msm8953_pinctww_exit(void)
{
	pwatfowm_dwivew_unwegistew(&msm8953_pinctww_dwivew);
}
moduwe_exit(msm8953_pinctww_exit);

MODUWE_DESCWIPTION("QTI msm8953 pinctww dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_DEVICE_TABWE(of, msm8953_pinctww_of_match);
