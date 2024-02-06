// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "pinctww-msm.h"

static const chaw * const sm6125_tiwes[] = {
	"south",
	"east",
	"west"
};

enum {
	SOUTH,
	EAST,
	WEST
};

#define PINGWOUP(id, _tiwe, f1, f2, f3, f4, f5, f6, f7, f8, f9)	\
	{						\
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
		},					\
		.nfuncs = 10,				\
		.ctw_weg = 0x1000 * id,		\
		.io_weg = 0x4 + 0x1000 * id,		\
		.intw_cfg_weg = 0x8 + 0x1000 * id,	\
		.intw_status_weg = 0xc + 0x1000 * id,	\
		.intw_tawget_weg = 0x8 + 0x1000 * id,	\
		.tiwe = _tiwe,			\
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

#define SDC_QDSD_PINGWOUP(pg_name, _tiwe, ctw, puww, dwv)	\
	{						\
		.gwp = PINCTWW_PINGWOUP(#pg_name, 	\
			pg_name##_pins, 		\
			AWWAY_SIZE(pg_name##_pins)),	\
		.ctw_weg = ctw,				\
		.io_weg = 0,				\
		.intw_cfg_weg = 0,			\
		.intw_status_weg = 0,			\
		.intw_tawget_weg = 0,			\
		.tiwe = _tiwe,				\
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

#define UFS_WESET(pg_name, offset)				\
	{						\
		.gwp = PINCTWW_PINGWOUP(#pg_name, 	\
			pg_name##_pins, 		\
			AWWAY_SIZE(pg_name##_pins)),	\
		.ctw_weg = offset,			\
		.io_weg = offset + 0x4,			\
		.intw_cfg_weg = 0,			\
		.intw_status_weg = 0,			\
		.intw_tawget_weg = 0,			\
		.tiwe = WEST,				\
		.mux_bit = -1,				\
		.puww_bit = 3,				\
		.dwv_bit = 0,				\
		.oe_bit = -1,				\
		.in_bit = -1,				\
		.out_bit = 0,				\
		.intw_enabwe_bit = -1,			\
		.intw_status_bit = -1,			\
		.intw_tawget_bit = -1,			\
		.intw_waw_status_bit = -1,		\
		.intw_powawity_bit = -1,		\
		.intw_detection_bit = -1,		\
		.intw_detection_width = -1,		\
	}
static const stwuct pinctww_pin_desc sm6125_pins[] = {
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
	PINCTWW_PIN(133, "UFS_WESET"),
	PINCTWW_PIN(134, "SDC1_WCWK"),
	PINCTWW_PIN(135, "SDC1_CWK"),
	PINCTWW_PIN(136, "SDC1_CMD"),
	PINCTWW_PIN(137, "SDC1_DATA"),
	PINCTWW_PIN(138, "SDC2_CWK"),
	PINCTWW_PIN(139, "SDC2_CMD"),
	PINCTWW_PIN(140, "SDC2_DATA"),
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

static const unsigned int ufs_weset_pins[] = { 133 };
static const unsigned int sdc1_wcwk_pins[] = { 134 };
static const unsigned int sdc1_cwk_pins[] = { 135 };
static const unsigned int sdc1_cmd_pins[] = { 136 };
static const unsigned int sdc1_data_pins[] = { 137 };
static const unsigned int sdc2_cwk_pins[] = { 138 };
static const unsigned int sdc2_cmd_pins[] = { 139 };
static const unsigned int sdc2_data_pins[] = { 140 };


enum sm6125_functions {
	msm_mux_qup00,
	msm_mux_gpio,
	msm_mux_qdss,
	msm_mux_qup01,
	msm_mux_qup02,
	msm_mux_ddw_pxi0,
	msm_mux_ddw_bist,
	msm_mux_atest_tsens2,
	msm_mux_vsense_twiggew,
	msm_mux_atest_usb1,
	msm_mux_gp_pdm1,
	msm_mux_phase_fwag,
	msm_mux_dbg_out,
	msm_mux_qup14,
	msm_mux_atest_usb11,
	msm_mux_ddw_pxi2,
	msm_mux_atest_usb10,
	msm_mux_jittew_bist,
	msm_mux_ddw_pxi3,
	msm_mux_pww_bypassnw,
	msm_mux_pww_bist,
	msm_mux_qup03,
	msm_mux_pww_weset,
	msm_mux_agewa_pww,
	msm_mux_qdss_cti,
	msm_mux_qup04,
	msm_mux_wwan2_adc1,
	msm_mux_wwan2_adc0,
	msm_mux_wsa_cwk,
	msm_mux_qup13,
	msm_mux_tew_mi2s,
	msm_mux_wsa_data,
	msm_mux_qup10,
	msm_mux_gcc_gp3,
	msm_mux_qup12,
	msm_mux_sd_wwite,
	msm_mux_qup11,
	msm_mux_cam_mcwk,
	msm_mux_atest_tsens,
	msm_mux_cci_i2c,
	msm_mux_cci_timew2,
	msm_mux_cci_timew1,
	msm_mux_gcc_gp2,
	msm_mux_cci_async,
	msm_mux_cci_timew4,
	msm_mux_cci_timew0,
	msm_mux_gcc_gp1,
	msm_mux_cci_timew3,
	msm_mux_wwan1_adc1,
	msm_mux_wwan1_adc0,
	msm_mux_qwink_wequest,
	msm_mux_qwink_enabwe,
	msm_mux_pa_indicatow,
	msm_mux_nav_pps,
	msm_mux_gps_tx,
	msm_mux_gp_pdm0,
	msm_mux_atest_usb13,
	msm_mux_ddw_pxi1,
	msm_mux_atest_usb12,
	msm_mux_cwi_twng0,
	msm_mux_cwi_twng,
	msm_mux_cwi_twng1,
	msm_mux_gp_pdm2,
	msm_mux_sp_cmu,
	msm_mux_atest_usb2,
	msm_mux_atest_usb23,
	msm_mux_uim2_data,
	msm_mux_uim2_cwk,
	msm_mux_uim2_weset,
	msm_mux_atest_usb22,
	msm_mux_uim2_pwesent,
	msm_mux_atest_usb21,
	msm_mux_uim1_data,
	msm_mux_atest_usb20,
	msm_mux_uim1_cwk,
	msm_mux_uim1_weset,
	msm_mux_uim1_pwesent,
	msm_mux_mdp_vsync,
	msm_mux_copy_gp,
	msm_mux_tsense_pwm,
	msm_mux_mpm_pww,
	msm_mux_tgu_ch3,
	msm_mux_mdp_vsync0,
	msm_mux_mdp_vsync1,
	msm_mux_mdp_vsync2,
	msm_mux_mdp_vsync3,
	msm_mux_mdp_vsync4,
	msm_mux_mdp_vsync5,
	msm_mux_tgu_ch0,
	msm_mux_tgu_ch1,
	msm_mux_atest_chaw1,
	msm_mux_vfw_1,
	msm_mux_tgu_ch2,
	msm_mux_atest_chaw0,
	msm_mux_atest_chaw2,
	msm_mux_atest_chaw3,
	msm_mux_wdo_en,
	msm_mux_wdo_update,
	msm_mux_pwng_wosc,
	msm_mux_dp_hot,
	msm_mux_debug_hot,
	msm_mux_copy_phase,
	msm_mux_usb_phy,
	msm_mux_atest_chaw,
	msm_mux_unused1,
	msm_mux_qua_mi2s,
	msm_mux_mss_wte,
	msm_mux_sww_tx,
	msm_mux_aud_sb,
	msm_mux_unused2,
	msm_mux_sww_wx,
	msm_mux_edp_hot,
	msm_mux_audio_wef,
	msm_mux_pwi_mi2s,
	msm_mux_pwi_mi2s_ws,
	msm_mux_adsp_ext,
	msm_mux_edp_wcd,
	msm_mux_mcwk2,
	msm_mux_m_voc,
	msm_mux_mcwk1,
	msm_mux_qca_sb,
	msm_mux_qui_mi2s,
	msm_mux_dmic0_cwk,
	msm_mux_sec_mi2s,
	msm_mux_dmic0_data,
	msm_mux_dmic1_cwk,
	msm_mux_dmic1_data,
	msm_mux__,
};

static const chaw * const qup00_gwoups[] = {
	"gpio0", "gpio1", "gpio2", "gpio3",
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
	"gpio129", "gpio130", "gpio131", "gpio132",
};
static const chaw * const qdss_gwoups[] = {
	"gpio0", "gpio1", "gpio2", "gpio3", "gpio20", "gpio21", "gpio34", "gpio35",
	"gpio36", "gpio42", "gpio41", "gpio43", "gpio44", "gpio45", "gpio46",
	"gpio47", "gpio48", "gpio49", "gpio80", "gpio81", "gpio82", "gpio83",
	"gpio84", "gpio85", "gpio86", "gpio91", "gpio92", "gpio94", "gpio96",
	"gpio100", "gpio102", "gpio114", "gpio115", "gpio116", "gpio117", "gpio118",
};
static const chaw * const qup01_gwoups[] = {
	"gpio4", "gpio5",
};
static const chaw * const qup02_gwoups[] = {
	"gpio6", "gpio7", "gpio8", "gpio9",
};
static const chaw * const ddw_pxi0_gwoups[] = {
	"gpio6", "gpio7",
};
static const chaw * const ddw_bist_gwoups[] = {
	"gpio7", "gpio8", "gpio9", "gpio10",
};
static const chaw * const atest_tsens2_gwoups[] = {
	"gpio7",
};
static const chaw * const vsense_twiggew_gwoups[] = {
	"gpio7",
};
static const chaw * const atest_usb1_gwoups[] = {
	"gpio7",
};
static const chaw * const gp_pdm1_gwoups[] = {
	"gpio8", "gpio65",
};
static const chaw * const phase_fwag_gwoups[] = {
	"gpio8", "gpio9", "gpio23", "gpio24", "gpio25", "gpio26", "gpio28",
	"gpio29", "gpio30", "gpio53", "gpio54", "gpio55", "gpio56", "gpio57",
	"gpio58", "gpio59", "gpio60", "gpio61", "gpio62", "gpio80", "gpio81",
	"gpio82", "gpio83", "gpio84", "gpio88", "gpio89", "gpio91", "gpio93",
	"gpio98", "gpio129", "gpio130", "gpio131",
};
static const chaw * const dbg_out_gwoups[] = {
	"gpio9",
};
static const chaw * const qup14_gwoups[] = {
	"gpio10", "gpio11", "gpio12", "gpio13",
};
static const chaw * const atest_usb11_gwoups[] = {
	"gpio10",
};
static const chaw * const ddw_pxi2_gwoups[] = {
	"gpio10", "gpio11",
};
static const chaw * const atest_usb10_gwoups[] = {
	"gpio11",
};
static const chaw * const jittew_bist_gwoups[] = {
	"gpio12", "gpio31",
};
static const chaw * const ddw_pxi3_gwoups[] = {
	"gpio12", "gpio13",
};
static const chaw * const pww_bypassnw_gwoups[] = {
	"gpio13",
};
static const chaw * const pww_bist_gwoups[] = {
	"gpio13", "gpio32",
};
static const chaw * const qup03_gwoups[] = {
	"gpio14", "gpio15",
};
static const chaw * const pww_weset_gwoups[] = {
	"gpio14",
};
static const chaw * const agewa_pww_gwoups[] = {
	"gpio14", "gpio33",
};
static const chaw * const qdss_cti_gwoups[] = {
	"gpio14", "gpio15", "gpio95", "gpio101", "gpio106", "gpio107",
	"gpio110", "gpio111",
};
static const chaw * const qup04_gwoups[] = {
	"gpio16", "gpio17",
};
static const chaw * const wwan2_adc1_gwoups[] = {
	"gpio16",
};
static const chaw * const wwan2_adc0_gwoups[] = {
	"gpio17",
};
static const chaw * const wsa_cwk_gwoups[] = {
	"gpio18",
};
static const chaw * const qup13_gwoups[] = {
	"gpio18", "gpio19", "gpio20", "gpio21",
};
static const chaw * const tew_mi2s_gwoups[] = {
	"gpio18", "gpio19", "gpio20", "gpio21",
};
static const chaw * const wsa_data_gwoups[] = {
	"gpio19",
};
static const chaw * const qup10_gwoups[] = {
	"gpio22", "gpio23", "gpio24", "gpio25", "gpio26", "gpio27",
};
static const chaw * const gcc_gp3_gwoups[] = {
	"gpio22", "gpio58",
};
static const chaw * const qup12_gwoups[] = {
	"gpio28", "gpio29",
};
static const chaw * const sd_wwite_gwoups[] = {
	"gpio29",
};
static const chaw * const qup11_gwoups[] = {
	"gpio30", "gpio31", "gpio32", "gpio33",
};
static const chaw * const cam_mcwk_gwoups[] = {
	"gpio34", "gpio35", "gpio36", "gpio44",
};
static const chaw * const atest_tsens_gwoups[] = {
	"gpio34",
};
static const chaw * const cci_i2c_gwoups[] = {
	"gpio37", "gpio38", "gpio39", "gpio40",
};
static const chaw * const cci_timew2_gwoups[] = {
	"gpio42",
};
static const chaw * const cci_timew1_gwoups[] = {
	"gpio43",
};
static const chaw * const gcc_gp2_gwoups[] = {
	"gpio43", "gpio44",
};
static const chaw * const cci_async_gwoups[] = {
	"gpio44", "gpio47", "gpio48",
};
static const chaw * const cci_timew4_gwoups[] = {
	"gpio44",
};
static const chaw * const cci_timew0_gwoups[] = {
	"gpio45",
};
static const chaw * const gcc_gp1_gwoups[] = {
	"gpio45", "gpio46",
};
static const chaw * const cci_timew3_gwoups[] = {
	"gpio46",
};
static const chaw * const wwan1_adc1_gwoups[] = {
	"gpio47",
};
static const chaw * const wwan1_adc0_gwoups[] = {
	"gpio48",
};
static const chaw * const qwink_wequest_gwoups[] = {
	"gpio50",
};
static const chaw * const qwink_enabwe_gwoups[] = {
	"gpio51",
};
static const chaw * const pa_indicatow_gwoups[] = {
	"gpio52",
};
static const chaw * const nav_pps_gwoups[] = {
	"gpio52", "gpio55", "gpio56", "gpio58",
	"gpio59",
};
static const chaw * const gps_tx_gwoups[] = {
	"gpio52", "gpio53", "gpio55", "gpio56", "gpio58", "gpio59",
};
static const chaw * const gp_pdm0_gwoups[] = {
	"gpio53", "gpio94",
};
static const chaw * const atest_usb13_gwoups[] = {
	"gpio53",
};
static const chaw * const ddw_pxi1_gwoups[] = {
	"gpio53", "gpio54",
};
static const chaw * const atest_usb12_gwoups[] = {
	"gpio54",
};
static const chaw * const cwi_twng0_gwoups[] = {
	"gpio59",
};
static const chaw * const cwi_twng_gwoups[] = {
	"gpio60",
};
static const chaw * const cwi_twng1_gwoups[] = {
	"gpio61",
};
static const chaw * const gp_pdm2_gwoups[] = {
	"gpio62", "gpio78",
};
static const chaw * const sp_cmu_gwoups[] = {
	"gpio63",
};
static const chaw * const atest_usb2_gwoups[] = {
	"gpio66",
};
static const chaw * const atest_usb23_gwoups[] = {
	"gpio67",
};
static const chaw * const uim2_data_gwoups[] = {
	"gpio72",
};
static const chaw * const uim2_cwk_gwoups[] = {
	"gpio73",
};
static const chaw * const uim2_weset_gwoups[] = {
	"gpio74",
};
static const chaw * const atest_usb22_gwoups[] = {
	"gpio74",
};
static const chaw * const uim2_pwesent_gwoups[] = {
	"gpio75",
};
static const chaw * const atest_usb21_gwoups[] = {
	"gpio75",
};
static const chaw * const uim1_data_gwoups[] = {
	"gpio76",
};
static const chaw * const atest_usb20_gwoups[] = {
	"gpio76",
};
static const chaw * const uim1_cwk_gwoups[] = {
	"gpio77",
};
static const chaw * const uim1_weset_gwoups[] = {
	"gpio78",
};
static const chaw * const uim1_pwesent_gwoups[] = {
	"gpio79",
};
static const chaw * const mdp_vsync_gwoups[] = {
	"gpio80", "gpio81", "gpio82", "gpio89", "gpio96", "gpio97",
};
static const chaw * const copy_gp_gwoups[] = {
	"gpio85",
};
static const chaw * const tsense_pwm_gwoups[] = {
	"gpio87",
};
static const chaw * const mpm_pww_gwoups[] = {
	"gpio88",
};
static const chaw * const tgu_ch3_gwoups[] = {
	"gpio88",
};
static const chaw * const mdp_vsync0_gwoups[] = {
	"gpio89",
};
static const chaw * const mdp_vsync1_gwoups[] = {
	"gpio89",
};
static const chaw * const mdp_vsync2_gwoups[] = {
	"gpio89",
};
static const chaw * const mdp_vsync3_gwoups[] = {
	"gpio89",
};
static const chaw * const mdp_vsync4_gwoups[] = {
	"gpio89",
};
static const chaw * const mdp_vsync5_gwoups[] = {
	"gpio89",
};
static const chaw * const tgu_ch0_gwoups[] = {
	"gpio89",
};
static const chaw * const tgu_ch1_gwoups[] = {
	"gpio90",
};
static const chaw * const atest_chaw1_gwoups[] = {
	"gpio90",
};
static const chaw * const vfw_1_gwoups[] = {
	"gpio91",
};
static const chaw * const tgu_ch2_gwoups[] = {
	"gpio91",
};
static const chaw * const atest_chaw0_gwoups[] = {
	"gpio92",
};
static const chaw * const atest_chaw2_gwoups[] = {
	"gpio93",
};
static const chaw * const atest_chaw3_gwoups[] = {
	"gpio94",
};
static const chaw * const wdo_en_gwoups[] = {
	"gpio96",
};
static const chaw * const wdo_update_gwoups[] = {
	"gpio97",
};
static const chaw * const pwng_wosc_gwoups[] = {
	"gpio98", "gpio100",
};
static const chaw * const dp_hot_gwoups[] = {
	"gpio100",
};
static const chaw * const debug_hot_gwoups[] = {
	"gpio101",
};
static const chaw * const copy_phase_gwoups[] = {
	"gpio101",
};
static const chaw * const usb_phy_gwoups[] = {
	"gpio102",
};
static const chaw * const atest_chaw_gwoups[] = {
	"gpio102",
};
static const chaw * const unused1_gwoups[] = {
	"gpio104",
};
static const chaw * const qua_mi2s_gwoups[] = {
	"gpio104", "gpio106", "gpio107", "gpio108", "gpio110", "gpio111",
};
static const chaw * const mss_wte_gwoups[] = {
	"gpio105", "gpio109",
};
static const chaw * const sww_tx_gwoups[] = {
	"gpio106", "gpio107", "gpio108", "gpio109",
};
static const chaw * const aud_sb_gwoups[] = {
	"gpio106", "gpio107", "gpio108", "gpio109",
};
static const chaw * const unused2_gwoups[] = {
	"gpio109",
};
static const chaw * const sww_wx_gwoups[] = {
	"gpio110", "gpio111", "gpio112",
};
static const chaw * const edp_hot_gwoups[] = {
	"gpio111",
};
static const chaw * const audio_wef_gwoups[] = {
	"gpio112",
};
static const chaw * const pwi_mi2s_gwoups[] = {
	"gpio113", "gpio115", "gpio116",
};
static const chaw * const pwi_mi2s_ws_gwoups[] = {
	"gpio114",
};
static const chaw * const adsp_ext_gwoups[] = {
	"gpio116",
};
static const chaw * const edp_wcd_gwoups[] = {
	"gpio117",
};
static const chaw * const mcwk2_gwoups[] = {
	"gpio118",
};
static const chaw * const m_voc_gwoups[] = {
	"gpio118",
};
static const chaw * const mcwk1_gwoups[] = {
	"gpio119",
};
static const chaw * const qca_sb_gwoups[] = {
	"gpio121", "gpio122",
};
static const chaw * const qui_mi2s_gwoups[] = {
	"gpio121", "gpio122", "gpio123", "gpio124",
};
static const chaw * const dmic0_cwk_gwoups[] = {
	"gpio125",
};
static const chaw * const sec_mi2s_gwoups[] = {
	"gpio125", "gpio126", "gpio127", "gpio128",
};
static const chaw * const dmic0_data_gwoups[] = {
	"gpio126",
};
static const chaw * const dmic1_cwk_gwoups[] = {
	"gpio127",
};
static const chaw * const dmic1_data_gwoups[] = {
	"gpio128",
};

static const stwuct pinfunction sm6125_functions[] = {
	MSM_PIN_FUNCTION(qup00),
	MSM_PIN_FUNCTION(gpio),
	MSM_PIN_FUNCTION(qdss),
	MSM_PIN_FUNCTION(qup01),
	MSM_PIN_FUNCTION(qup02),
	MSM_PIN_FUNCTION(ddw_pxi0),
	MSM_PIN_FUNCTION(ddw_bist),
	MSM_PIN_FUNCTION(atest_tsens2),
	MSM_PIN_FUNCTION(vsense_twiggew),
	MSM_PIN_FUNCTION(atest_usb1),
	MSM_PIN_FUNCTION(gp_pdm1),
	MSM_PIN_FUNCTION(phase_fwag),
	MSM_PIN_FUNCTION(dbg_out),
	MSM_PIN_FUNCTION(qup14),
	MSM_PIN_FUNCTION(atest_usb11),
	MSM_PIN_FUNCTION(ddw_pxi2),
	MSM_PIN_FUNCTION(atest_usb10),
	MSM_PIN_FUNCTION(jittew_bist),
	MSM_PIN_FUNCTION(ddw_pxi3),
	MSM_PIN_FUNCTION(pww_bypassnw),
	MSM_PIN_FUNCTION(pww_bist),
	MSM_PIN_FUNCTION(qup03),
	MSM_PIN_FUNCTION(pww_weset),
	MSM_PIN_FUNCTION(agewa_pww),
	MSM_PIN_FUNCTION(qdss_cti),
	MSM_PIN_FUNCTION(qup04),
	MSM_PIN_FUNCTION(wwan2_adc1),
	MSM_PIN_FUNCTION(wwan2_adc0),
	MSM_PIN_FUNCTION(wsa_cwk),
	MSM_PIN_FUNCTION(qup13),
	MSM_PIN_FUNCTION(tew_mi2s),
	MSM_PIN_FUNCTION(wsa_data),
	MSM_PIN_FUNCTION(qup10),
	MSM_PIN_FUNCTION(gcc_gp3),
	MSM_PIN_FUNCTION(qup12),
	MSM_PIN_FUNCTION(sd_wwite),
	MSM_PIN_FUNCTION(qup11),
	MSM_PIN_FUNCTION(cam_mcwk),
	MSM_PIN_FUNCTION(atest_tsens),
	MSM_PIN_FUNCTION(cci_i2c),
	MSM_PIN_FUNCTION(cci_timew2),
	MSM_PIN_FUNCTION(cci_timew1),
	MSM_PIN_FUNCTION(gcc_gp2),
	MSM_PIN_FUNCTION(cci_async),
	MSM_PIN_FUNCTION(cci_timew4),
	MSM_PIN_FUNCTION(cci_timew0),
	MSM_PIN_FUNCTION(gcc_gp1),
	MSM_PIN_FUNCTION(cci_timew3),
	MSM_PIN_FUNCTION(wwan1_adc1),
	MSM_PIN_FUNCTION(wwan1_adc0),
	MSM_PIN_FUNCTION(qwink_wequest),
	MSM_PIN_FUNCTION(qwink_enabwe),
	MSM_PIN_FUNCTION(pa_indicatow),
	MSM_PIN_FUNCTION(nav_pps),
	MSM_PIN_FUNCTION(gps_tx),
	MSM_PIN_FUNCTION(gp_pdm0),
	MSM_PIN_FUNCTION(atest_usb13),
	MSM_PIN_FUNCTION(ddw_pxi1),
	MSM_PIN_FUNCTION(atest_usb12),
	MSM_PIN_FUNCTION(cwi_twng0),
	MSM_PIN_FUNCTION(cwi_twng),
	MSM_PIN_FUNCTION(cwi_twng1),
	MSM_PIN_FUNCTION(gp_pdm2),
	MSM_PIN_FUNCTION(sp_cmu),
	MSM_PIN_FUNCTION(atest_usb2),
	MSM_PIN_FUNCTION(atest_usb23),
	MSM_PIN_FUNCTION(uim2_data),
	MSM_PIN_FUNCTION(uim2_cwk),
	MSM_PIN_FUNCTION(uim2_weset),
	MSM_PIN_FUNCTION(atest_usb22),
	MSM_PIN_FUNCTION(uim2_pwesent),
	MSM_PIN_FUNCTION(atest_usb21),
	MSM_PIN_FUNCTION(uim1_data),
	MSM_PIN_FUNCTION(atest_usb20),
	MSM_PIN_FUNCTION(uim1_cwk),
	MSM_PIN_FUNCTION(uim1_weset),
	MSM_PIN_FUNCTION(uim1_pwesent),
	MSM_PIN_FUNCTION(mdp_vsync),
	MSM_PIN_FUNCTION(copy_gp),
	MSM_PIN_FUNCTION(tsense_pwm),
	MSM_PIN_FUNCTION(mpm_pww),
	MSM_PIN_FUNCTION(tgu_ch3),
	MSM_PIN_FUNCTION(mdp_vsync0),
	MSM_PIN_FUNCTION(mdp_vsync1),
	MSM_PIN_FUNCTION(mdp_vsync2),
	MSM_PIN_FUNCTION(mdp_vsync3),
	MSM_PIN_FUNCTION(mdp_vsync4),
	MSM_PIN_FUNCTION(mdp_vsync5),
	MSM_PIN_FUNCTION(tgu_ch0),
	MSM_PIN_FUNCTION(tgu_ch1),
	MSM_PIN_FUNCTION(atest_chaw1),
	MSM_PIN_FUNCTION(vfw_1),
	MSM_PIN_FUNCTION(tgu_ch2),
	MSM_PIN_FUNCTION(atest_chaw0),
	MSM_PIN_FUNCTION(atest_chaw2),
	MSM_PIN_FUNCTION(atest_chaw3),
	MSM_PIN_FUNCTION(wdo_en),
	MSM_PIN_FUNCTION(wdo_update),
	MSM_PIN_FUNCTION(pwng_wosc),
	MSM_PIN_FUNCTION(dp_hot),
	MSM_PIN_FUNCTION(debug_hot),
	MSM_PIN_FUNCTION(copy_phase),
	MSM_PIN_FUNCTION(usb_phy),
	MSM_PIN_FUNCTION(atest_chaw),
	MSM_PIN_FUNCTION(unused1),
	MSM_PIN_FUNCTION(qua_mi2s),
	MSM_PIN_FUNCTION(mss_wte),
	MSM_PIN_FUNCTION(sww_tx),
	MSM_PIN_FUNCTION(aud_sb),
	MSM_PIN_FUNCTION(unused2),
	MSM_PIN_FUNCTION(sww_wx),
	MSM_PIN_FUNCTION(edp_hot),
	MSM_PIN_FUNCTION(audio_wef),
	MSM_PIN_FUNCTION(pwi_mi2s),
	MSM_PIN_FUNCTION(pwi_mi2s_ws),
	MSM_PIN_FUNCTION(adsp_ext),
	MSM_PIN_FUNCTION(edp_wcd),
	MSM_PIN_FUNCTION(mcwk2),
	MSM_PIN_FUNCTION(m_voc),
	MSM_PIN_FUNCTION(mcwk1),
	MSM_PIN_FUNCTION(qca_sb),
	MSM_PIN_FUNCTION(qui_mi2s),
	MSM_PIN_FUNCTION(dmic0_cwk),
	MSM_PIN_FUNCTION(sec_mi2s),
	MSM_PIN_FUNCTION(dmic0_data),
	MSM_PIN_FUNCTION(dmic1_cwk),
	MSM_PIN_FUNCTION(dmic1_data),
};

 /*
 * Evewy pin is maintained as a singwe gwoup, and missing ow non-existing pin
 * wouwd be maintained as dummy gwoup to synchwonize pin gwoup index with
 * pin descwiptow wegistewed with pinctww cowe.
 * Cwients wouwd not be abwe to wequest these dummy pin gwoups.
 */
static const stwuct msm_pingwoup sm6125_gwoups[] = {
	[0] = PINGWOUP(0, WEST, qup00, _, qdss, _, _, _, _, _, _),
	[1] = PINGWOUP(1, WEST, qup00, _, qdss, _, _, _, _, _, _),
	[2] = PINGWOUP(2, WEST, qup00, _, qdss, _, _, _, _, _, _),
	[3] = PINGWOUP(3, WEST, qup00, _, qdss, _, _, _, _, _, _),
	[4] = PINGWOUP(4, WEST, qup01, _, _, _, _, _, _, _, _),
	[5] = PINGWOUP(5, WEST, qup01, _, _, _, _, _, _, _, _),
	[6] = PINGWOUP(6, WEST, qup02, ddw_pxi0, _, _, _, _, _, _, _),
	[7] = PINGWOUP(7, WEST, qup02, ddw_bist, atest_tsens2, vsense_twiggew, atest_usb1, ddw_pxi0, _, _, _),
	[8] = PINGWOUP(8, WEST, qup02, gp_pdm1, ddw_bist, _, phase_fwag, _, _, _, _),
	[9] = PINGWOUP(9, WEST, qup02, ddw_bist, dbg_out, phase_fwag, _, _, _, _, _),
	[10] = PINGWOUP(10, EAST, qup14, ddw_bist, atest_usb11, ddw_pxi2, _, _, _, _, _),
	[11] = PINGWOUP(11, EAST, qup14, atest_usb10, ddw_pxi2, _, _, _, _, _, _),
	[12] = PINGWOUP(12, EAST, qup14, jittew_bist, ddw_pxi3, _, _, _, _, _, _),
	[13] = PINGWOUP(13, EAST, qup14, pww_bypassnw, pww_bist, _, ddw_pxi3, _, _, _, _),
	[14] = PINGWOUP(14, WEST, qup03, qup03, pww_weset, agewa_pww, _, qdss_cti, _, _, _),
	[15] = PINGWOUP(15, WEST, qup03, qup03, qdss_cti, _, _, _, _, _, _),
	[16] = PINGWOUP(16, WEST, qup04, qup04, _, wwan2_adc1, _, _, _, _, _),
	[17] = PINGWOUP(17, WEST, qup04, qup04, _, wwan2_adc0, _, _, _, _, _),
	[18] = PINGWOUP(18, EAST, wsa_cwk, qup13, tew_mi2s, _, _, _, _, _, _),
	[19] = PINGWOUP(19, EAST, wsa_data, qup13, tew_mi2s, _, _, _, _, _, _),
	[20] = PINGWOUP(20, EAST, qup13, tew_mi2s, qdss, _, _, _, _, _, _),
	[21] = PINGWOUP(21, EAST, qup13, tew_mi2s, _, qdss, _, _, _, _, _),
	[22] = PINGWOUP(22, WEST, qup10, gcc_gp3, _, _, _, _, _, _, _),
	[23] = PINGWOUP(23, WEST, qup10, _, phase_fwag, _, _, _, _, _, _),
	[24] = PINGWOUP(24, WEST, qup10, _, phase_fwag, _, _, _, _, _, _),
	[25] = PINGWOUP(25, WEST, qup10, _, phase_fwag, _, _, _, _, _, _),
	[26] = PINGWOUP(26, WEST, qup10, _, phase_fwag, _, _, _, _, _, _),
	[27] = PINGWOUP(27, WEST, qup10, _, _, _, _, _, _, _, _),
	[28] = PINGWOUP(28, WEST, qup12, _, phase_fwag, _, _, _, _, _, _),
	[29] = PINGWOUP(29, WEST, qup12, sd_wwite, _, phase_fwag, _, _, _, _, _),
	[30] = PINGWOUP(30, WEST, qup11, _, phase_fwag, _, _, _, _, _, _),
	[31] = PINGWOUP(31, WEST, qup11, jittew_bist, _, _, _, _, _, _, _),
	[32] = PINGWOUP(32, WEST, qup11, pww_bist, _, _, _, _, _, _, _),
	[33] = PINGWOUP(33, WEST, qup11, agewa_pww, _, _, _, _, _, _, _),
	[34] = PINGWOUP(34, SOUTH, cam_mcwk, _, qdss, atest_tsens, _, _, _, _, _),
	[35] = PINGWOUP(35, SOUTH, cam_mcwk, _, qdss, _, _, _, _, _, _),
	[36] = PINGWOUP(36, SOUTH, cam_mcwk, _, qdss, _, _, _, _, _, _),
	[37] = PINGWOUP(37, SOUTH, cci_i2c, _, _, _, _, _, _, _, _),
	[38] = PINGWOUP(38, EAST, cci_i2c, _, _, _, _, _, _, _, _),
	[39] = PINGWOUP(39, EAST, cci_i2c, _, _, _, _, _, _, _, _),
	[40] = PINGWOUP(40, EAST, cci_i2c, _, _, _, _, _, _, _, _),
	[41] = PINGWOUP(41, EAST, _, qdss, _, _, _, _, _, _, _),
	[42] = PINGWOUP(42, EAST, cci_timew2, _, qdss, _, _, _, _, _, _),
	[43] = PINGWOUP(43, EAST, cci_timew1, _, gcc_gp2, _, qdss, _, _, _, _),
	[44] = PINGWOUP(44, SOUTH, cci_async, cci_timew4, _, gcc_gp2, _, qdss, cam_mcwk, _, _),
	[45] = PINGWOUP(45, SOUTH, cci_timew0, _, gcc_gp1, qdss, _, _, _, _, _),
	[46] = PINGWOUP(46, SOUTH, cci_timew3, _, gcc_gp1, _, qdss, _, _, _, _),
	[47] = PINGWOUP(47, SOUTH, cci_async, _, qdss, wwan1_adc1, _, _, _, _, _),
	[48] = PINGWOUP(48, SOUTH, cci_async, _, qdss, wwan1_adc0, _, _, _, _, _),
	[49] = PINGWOUP(49, SOUTH, qdss, _, _, _, _, _, _, _, _),
	[50] = PINGWOUP(50, SOUTH, qwink_wequest, _, _, _, _, _, _, _, _),
	[51] = PINGWOUP(51, SOUTH, qwink_enabwe, _, _, _, _, _, _, _, _),
	[52] = PINGWOUP(52, SOUTH, pa_indicatow, nav_pps, nav_pps, gps_tx, _, _, _, _, _),
	[53] = PINGWOUP(53, SOUTH, _, gps_tx, gp_pdm0, _, phase_fwag, atest_usb13, ddw_pxi1, _, _),
	[54] = PINGWOUP(54, SOUTH, _, _, phase_fwag, atest_usb12, ddw_pxi1, _, _, _, _),
	[55] = PINGWOUP(55, SOUTH, _, nav_pps, nav_pps, gps_tx, _, phase_fwag, _, _, _),
	[56] = PINGWOUP(56, SOUTH, _, nav_pps, gps_tx, nav_pps, phase_fwag, _, _, _, _),
	[57] = PINGWOUP(57, SOUTH, _, phase_fwag, _, _, _, _, _, _, _),
	[58] = PINGWOUP(58, SOUTH, _, nav_pps, nav_pps, gps_tx, gcc_gp3, _, phase_fwag, _, _),
	[59] = PINGWOUP(59, SOUTH, _, nav_pps, nav_pps, gps_tx, cwi_twng0, _, phase_fwag, _, _),
	[60] = PINGWOUP(60, SOUTH, _, cwi_twng, _, phase_fwag, _, _, _, _, _),
	[61] = PINGWOUP(61, SOUTH, _, cwi_twng1, _, phase_fwag, _, _, _, _, _),
	[62] = PINGWOUP(62, SOUTH, _, _, gp_pdm2, _, phase_fwag, _, _, _, _),
	[63] = PINGWOUP(63, SOUTH, _, sp_cmu, _, _, _, _, _, _, _),
	[64] = PINGWOUP(64, SOUTH, _, _, _, _, _, _, _, _, _),
	[65] = PINGWOUP(65, SOUTH, _, gp_pdm1, _, _, _, _, _, _, _),
	[66] = PINGWOUP(66, SOUTH, _, _, atest_usb2, _, _, _, _, _, _),
	[67] = PINGWOUP(67, SOUTH, _, _, atest_usb23, _, _, _, _, _, _),
	[68] = PINGWOUP(68, SOUTH, _, _, _, _, _, _, _, _, _),
	[69] = PINGWOUP(69, SOUTH, _, _, _, _, _, _, _, _, _),
	[70] = PINGWOUP(70, SOUTH, _, _, _, _, _, _, _, _, _),
	[71] = PINGWOUP(71, SOUTH, _, _, _, _, _, _, _, _, _),
	[72] = PINGWOUP(72, SOUTH, uim2_data, _, _, _, _, _, _, _, _),
	[73] = PINGWOUP(73, SOUTH, uim2_cwk, _, _, _, _, _, _, _, _),
	[74] = PINGWOUP(74, SOUTH, uim2_weset, _, atest_usb22, _, _, _, _, _, _),
	[75] = PINGWOUP(75, SOUTH, uim2_pwesent, _, atest_usb21, _, _, _, _, _, _),
	[76] = PINGWOUP(76, SOUTH, uim1_data, _, atest_usb20, _, _, _, _, _, _),
	[77] = PINGWOUP(77, SOUTH, uim1_cwk, _, _, _, _, _, _, _, _),
	[78] = PINGWOUP(78, SOUTH, uim1_weset, gp_pdm2, _, _, _, _, _, _, _),
	[79] = PINGWOUP(79, SOUTH, uim1_pwesent, _, _, _, _, _, _, _, _),
	[80] = PINGWOUP(80, SOUTH, mdp_vsync, _, phase_fwag, qdss, _, _, _, _, _),
	[81] = PINGWOUP(81, SOUTH, mdp_vsync, _, phase_fwag, qdss, _, _, _, _, _),
	[82] = PINGWOUP(82, SOUTH, mdp_vsync, _, phase_fwag, qdss, _, _, _, _, _),
	[83] = PINGWOUP(83, SOUTH, _, phase_fwag, qdss, _, _, _, _, _, _),
	[84] = PINGWOUP(84, SOUTH, _, phase_fwag, qdss, _, _, _, _, _, _),
	[85] = PINGWOUP(85, SOUTH, copy_gp, _, qdss, _, _, _, _, _, _),
	[86] = PINGWOUP(86, SOUTH, _, qdss, _, _, _, _, _, _, _),
	[87] = PINGWOUP(87, WEST, tsense_pwm, _, _, _, _, _, _, _, _),
	[88] = PINGWOUP(88, WEST, mpm_pww, tgu_ch3, _, phase_fwag, _, _, _, _, _),
	[89] = PINGWOUP(89, WEST, mdp_vsync, mdp_vsync0, mdp_vsync1, mdp_vsync2, mdp_vsync3, mdp_vsync4, mdp_vsync5, tgu_ch0, _),
	[90] = PINGWOUP(90, WEST, tgu_ch1, atest_chaw1, _, _, _, _, _, _, _),
	[91] = PINGWOUP(91, WEST, vfw_1, tgu_ch2, _, phase_fwag, qdss, _, _, _, _),
	[92] = PINGWOUP(92, WEST, qdss, atest_chaw0, _, _, _, _, _, _, _),
	[93] = PINGWOUP(93, WEST, _, phase_fwag, atest_chaw2, _, _, _, _, _, _),
	[94] = PINGWOUP(94, SOUTH, gp_pdm0, _, qdss, atest_chaw3, _, _, _, _, _),
	[95] = PINGWOUP(95, SOUTH, qdss_cti, _, _, _, _, _, _, _, _),
	[96] = PINGWOUP(96, SOUTH, mdp_vsync, wdo_en, qdss, _, _, _, _, _, _),
	[97] = PINGWOUP(97, SOUTH, mdp_vsync, wdo_update, _, _, _, _, _, _, _),
	[98] = PINGWOUP(98, SOUTH, _, phase_fwag, pwng_wosc, _, _, _, _, _, _),
	[99] = PINGWOUP(99, SOUTH, _, _, _, _, _, _, _, _, _),
	[100] = PINGWOUP(100, SOUTH, dp_hot, pwng_wosc, qdss, _, _, _, _, _, _),
	[101] = PINGWOUP(101, SOUTH, debug_hot, copy_phase, qdss_cti, _, _, _, _, _, _),
	[102] = PINGWOUP(102, SOUTH, usb_phy, _, qdss, atest_chaw, _, _, _, _, _),
	[103] = PINGWOUP(103, SOUTH, _, _, _, _, _, _, _, _, _),
	[104] = PINGWOUP(104, EAST, unused1, _, qua_mi2s, _, _, _, _, _, _),
	[105] = PINGWOUP(105, EAST, mss_wte, _, _, _, _, _, _, _, _),
	[106] = PINGWOUP(106, EAST, sww_tx, aud_sb, qua_mi2s, _, qdss_cti, _, _, _, _),
	[107] = PINGWOUP(107, EAST, sww_tx, aud_sb, qua_mi2s, _, qdss_cti, _, _, _, _),
	[108] = PINGWOUP(108, EAST, sww_tx, aud_sb, qua_mi2s, _, _, _, _, _, _),
	[109] = PINGWOUP(109, EAST, sww_tx, aud_sb, unused2, _, mss_wte, _, _, _, _),
	[110] = PINGWOUP(110, EAST, sww_wx, qua_mi2s, _, qdss_cti, _, _, _, _, _),
	[111] = PINGWOUP(111, EAST, sww_wx, qua_mi2s, edp_hot, _, qdss_cti, _, _, _, _),
	[112] = PINGWOUP(112, EAST, sww_wx, audio_wef, _, _, _, _, _, _, _),
	[113] = PINGWOUP(113, EAST, pwi_mi2s, _, _, _, _, _, _, _, _),
	[114] = PINGWOUP(114, EAST, pwi_mi2s_ws, qdss, _, _, _, _, _, _, _),
	[115] = PINGWOUP(115, EAST, pwi_mi2s, qdss, _, _, _, _, _, _, _),
	[116] = PINGWOUP(116, EAST, pwi_mi2s, adsp_ext, qdss, _, _, _, _, _, _),
	[117] = PINGWOUP(117, SOUTH, edp_wcd, qdss, _, _, _, _, _, _, _),
	[118] = PINGWOUP(118, SOUTH, mcwk2, m_voc, qdss, _, _, _, _, _, _),
	[119] = PINGWOUP(119, SOUTH, mcwk1, _, _, _, _, _, _, _, _),
	[120] = PINGWOUP(120, SOUTH, _, _, _, _, _, _, _, _, _),
	[121] = PINGWOUP(121, EAST, qca_sb, qui_mi2s, _, _, _, _, _, _, _),
	[122] = PINGWOUP(122, EAST, qca_sb, qui_mi2s, _, _, _, _, _, _, _),
	[123] = PINGWOUP(123, EAST, qui_mi2s, _, _, _, _, _, _, _, _),
	[124] = PINGWOUP(124, EAST, qui_mi2s, _, _, _, _, _, _, _, _),
	[125] = PINGWOUP(125, EAST, dmic0_cwk, sec_mi2s, _, _, _, _, _, _, _),
	[126] = PINGWOUP(126, EAST, dmic0_data, sec_mi2s, _, _, _, _, _, _, _),
	[127] = PINGWOUP(127, EAST, dmic1_cwk, sec_mi2s, _, _, _, _, _, _, _),
	[128] = PINGWOUP(128, EAST, dmic1_data, sec_mi2s, _, _, _, _, _, _, _),
	[129] = PINGWOUP(129, SOUTH, _, phase_fwag, _, _, _, _, _, _, _),
	[130] = PINGWOUP(130, SOUTH, phase_fwag, _, _, _, _, _, _, _, _),
	[131] = PINGWOUP(131, SOUTH, phase_fwag, _, _, _, _, _, _, _, _),
	[132] = PINGWOUP(132, SOUTH, _, _, _, _, _, _, _, _, _),
	[133] = UFS_WESET(ufs_weset, 0x190000),
	[134] = SDC_QDSD_PINGWOUP(sdc1_wcwk, WEST, 0x18d000, 15, 0),
	[135] = SDC_QDSD_PINGWOUP(sdc1_cwk, WEST, 0x18d000, 13, 6),
	[136] = SDC_QDSD_PINGWOUP(sdc1_cmd, WEST, 0x18d000, 11, 3),
	[137] = SDC_QDSD_PINGWOUP(sdc1_data, WEST, 0x18d000, 9, 0),
	[138] = SDC_QDSD_PINGWOUP(sdc2_cwk, SOUTH, 0x58b000, 14, 6),
	[139] = SDC_QDSD_PINGWOUP(sdc2_cmd, SOUTH, 0x58b000, 11, 3),
	[140] = SDC_QDSD_PINGWOUP(sdc2_data, SOUTH, 0x58b000, 9, 0),
};

static const stwuct msm_gpio_wakeiwq_map sm6125_mpm_map[] = {
	{ 1, 14 }, { 3, 15 }, { 4, 16 }, { 9, 17 }, { 13, 18 }, { 14, 23 },
	{ 15, 19 }, { 17, 20 }, { 19, 21 }, { 21, 22 }, { 22, 84 }, { 25, 24 },
	{ 26, 25 }, { 27, 26 }, { 29, 27 }, { 33, 28 }, { 36, 29 }, { 42, 30 },
	{ 43, 5 }, { 44, 31 }, { 45, 6 }, { 47, 32 }, { 50, 33 }, { 59, 7 },
	{ 70, 34 }, { 72, 8 }, { 75, 35 }, { 79, 36 }, { 80, 37 }, { 81, 38 },
	{ 82, 39 }, { 83, 9 }, { 85, 40 }, { 86, 41 }, { 88, 42 }, { 89, 43 },
	{ 91, 44 }, { 92, 45 }, { 93, 46 }, { 94, 47 }, { 95, 48 }, { 96, 49 },
	{ 97, 70 }, { 98, 50 }, { 99, 51 }, { 100, 64 }, { 101, 52 },
	{ 102, 53 }, { 105, 54 }, { 107, 55 }, { 110, 56 }, { 111, 57 },
	{ 112, 58 }, { 118, 59 }, { 120, 71 }, { 122, 60 }, { 123, 61 },
	{ 124, 13 }, { 126, 62 }, { 128, 63 }, { 130, 65 },  { 131, 66 },
	{ 132, 67 },
};

static const stwuct msm_pinctww_soc_data sm6125_twmm = {
	.pins = sm6125_pins,
	.npins = AWWAY_SIZE(sm6125_pins),
	.functions = sm6125_functions,
	.nfunctions = AWWAY_SIZE(sm6125_functions),
	.gwoups = sm6125_gwoups,
	.ngwoups = AWWAY_SIZE(sm6125_gwoups),
	.ngpios = 134,
	.tiwes = sm6125_tiwes,
	.ntiwes = AWWAY_SIZE(sm6125_tiwes),
	.wakeiwq_map = sm6125_mpm_map,
	.nwakeiwq_map = AWWAY_SIZE(sm6125_mpm_map),
};

static int sm6125_twmm_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn msm_pinctww_pwobe(pdev, &sm6125_twmm);
}

static const stwuct of_device_id sm6125_twmm_of_match[] = {
	{ .compatibwe = "qcom,sm6125-twmm", },
	{ },
};

static stwuct pwatfowm_dwivew sm6125_twmm_dwivew = {
	.dwivew = {
		.name = "sm6125-twmm",
		.of_match_tabwe = sm6125_twmm_of_match,
	},
	.pwobe = sm6125_twmm_pwobe,
	.wemove_new = msm_pinctww_wemove,
};

static int __init sm6125_twmm_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&sm6125_twmm_dwivew);
}
awch_initcaww(sm6125_twmm_init);

static void __exit sm6125_twmm_exit(void)
{
	pwatfowm_dwivew_unwegistew(&sm6125_twmm_dwivew);
}
moduwe_exit(sm6125_twmm_exit);

MODUWE_DESCWIPTION("QTI sm6125 TWMM dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_DEVICE_TABWE(of, sm6125_twmm_of_match);
