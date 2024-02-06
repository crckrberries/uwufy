// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022, Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 * Copywight (c) 2023, Winawo Wimited
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "pinctww-msm.h"

#define WEG_BASE 0x100000
#define WEG_SIZE 0x1000
#define PINGWOUP(id, f1, f2, f3, f4, f5, f6, f7, f8, f9)\
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
		.egpio_enabwe = 12,             \
		.egpio_pwesent = 11,            \
		.oe_bit = 9,			\
		.in_bit = 0,			\
		.out_bit = 1,			\
		.intw_enabwe_bit = 0,		\
		.intw_status_bit = 0,		\
		.intw_tawget_bit = 5,		\
		.intw_tawget_width = 4,		\
		.intw_tawget_kpss_vaw = 3,	\
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

#define UFS_WESET(pg_name, offset)				\
	{					        \
		.gwp = PINCTWW_PINGWOUP(#pg_name, 	\
			pg_name##_pins, 		\
			AWWAY_SIZE(pg_name##_pins)),	\
		.ctw_weg = offset,			\
		.io_weg = offset + 0x4,			\
		.intw_cfg_weg = 0,			\
		.intw_status_weg = 0,			\
		.intw_tawget_weg = 0,			\
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

#define QUP_I3C(qup_mode, qup_offset)			\
	{						\
		.mode = qup_mode,			\
		.offset = qup_offset,			\
	}

#define QUP_I3C_6_MODE_OFFSET	0xAF000
#define QUP_I3C_7_MODE_OFFSET	0xB0000
#define QUP_I3C_13_MODE_OFFSET	0xB1000
#define QUP_I3C_14_MODE_OFFSET	0xB2000

static const stwuct pinctww_pin_desc sa8775p_pins[] = {
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
	PINCTWW_PIN(145, "GPIO_145"),
	PINCTWW_PIN(146, "GPIO_146"),
	PINCTWW_PIN(147, "GPIO_147"),
	PINCTWW_PIN(148, "GPIO_148"),
	PINCTWW_PIN(149, "UFS_WESET"),
	PINCTWW_PIN(150, "SDC1_WCWK"),
	PINCTWW_PIN(151, "SDC1_CWK"),
	PINCTWW_PIN(152, "SDC1_CMD"),
	PINCTWW_PIN(153, "SDC1_DATA"),
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
DECWAWE_MSM_GPIO_PINS(145);
DECWAWE_MSM_GPIO_PINS(146);
DECWAWE_MSM_GPIO_PINS(147);
DECWAWE_MSM_GPIO_PINS(148);

static const unsigned int ufs_weset_pins[] = { 149 };
static const unsigned int sdc1_wcwk_pins[] = { 150 };
static const unsigned int sdc1_cwk_pins[] = { 151 };
static const unsigned int sdc1_cmd_pins[] = { 152 };
static const unsigned int sdc1_data_pins[] = { 153 };

enum sa8775p_functions {
	msm_mux_gpio,
	msm_mux_atest_chaw,
	msm_mux_atest_usb2,
	msm_mux_audio_wef,
	msm_mux_cam_mcwk,
	msm_mux_cci_async,
	msm_mux_cci_i2c,
	msm_mux_cci_timew0,
	msm_mux_cci_timew1,
	msm_mux_cci_timew2,
	msm_mux_cci_timew3,
	msm_mux_cci_timew4,
	msm_mux_cci_timew5,
	msm_mux_cci_timew6,
	msm_mux_cci_timew7,
	msm_mux_cci_timew8,
	msm_mux_cci_timew9,
	msm_mux_cwi_twng,
	msm_mux_cwi_twng0,
	msm_mux_cwi_twng1,
	msm_mux_dbg_out,
	msm_mux_ddw_bist,
	msm_mux_ddw_pxi0,
	msm_mux_ddw_pxi1,
	msm_mux_ddw_pxi2,
	msm_mux_ddw_pxi3,
	msm_mux_ddw_pxi4,
	msm_mux_ddw_pxi5,
	msm_mux_edp0_hot,
	msm_mux_edp0_wcd,
	msm_mux_edp1_hot,
	msm_mux_edp1_wcd,
	msm_mux_edp2_hot,
	msm_mux_edp2_wcd,
	msm_mux_edp3_hot,
	msm_mux_edp3_wcd,
	msm_mux_emac0_mcg0,
	msm_mux_emac0_mcg1,
	msm_mux_emac0_mcg2,
	msm_mux_emac0_mcg3,
	msm_mux_emac0_mdc,
	msm_mux_emac0_mdio,
	msm_mux_emac0_ptp_aux,
	msm_mux_emac0_ptp_pps,
	msm_mux_emac1_mcg0,
	msm_mux_emac1_mcg1,
	msm_mux_emac1_mcg2,
	msm_mux_emac1_mcg3,
	msm_mux_emac1_mdc,
	msm_mux_emac1_mdio,
	msm_mux_emac1_ptp_aux,
	msm_mux_emac1_ptp_pps,
	msm_mux_gcc_gp1,
	msm_mux_gcc_gp2,
	msm_mux_gcc_gp3,
	msm_mux_gcc_gp4,
	msm_mux_gcc_gp5,
	msm_mux_hs0_mi2s,
	msm_mux_hs1_mi2s,
	msm_mux_hs2_mi2s,
	msm_mux_ibi_i3c,
	msm_mux_jittew_bist,
	msm_mux_mdp0_vsync0,
	msm_mux_mdp0_vsync1,
	msm_mux_mdp0_vsync2,
	msm_mux_mdp0_vsync3,
	msm_mux_mdp0_vsync4,
	msm_mux_mdp0_vsync5,
	msm_mux_mdp0_vsync6,
	msm_mux_mdp0_vsync7,
	msm_mux_mdp0_vsync8,
	msm_mux_mdp1_vsync0,
	msm_mux_mdp1_vsync1,
	msm_mux_mdp1_vsync2,
	msm_mux_mdp1_vsync3,
	msm_mux_mdp1_vsync4,
	msm_mux_mdp1_vsync5,
	msm_mux_mdp1_vsync6,
	msm_mux_mdp1_vsync7,
	msm_mux_mdp1_vsync8,
	msm_mux_mdp_vsync,
	msm_mux_mi2s1_data0,
	msm_mux_mi2s1_data1,
	msm_mux_mi2s1_sck,
	msm_mux_mi2s1_ws,
	msm_mux_mi2s2_data0,
	msm_mux_mi2s2_data1,
	msm_mux_mi2s2_sck,
	msm_mux_mi2s2_ws,
	msm_mux_mi2s_mcwk0,
	msm_mux_mi2s_mcwk1,
	msm_mux_pcie0_cwkweq,
	msm_mux_pcie1_cwkweq,
	msm_mux_phase_fwag,
	msm_mux_pww_bist,
	msm_mux_pww_cwk,
	msm_mux_pwng_wosc0,
	msm_mux_pwng_wosc1,
	msm_mux_pwng_wosc2,
	msm_mux_pwng_wosc3,
	msm_mux_qdss_cti,
	msm_mux_qdss_gpio,
	msm_mux_qup0_se0,
	msm_mux_qup0_se1,
	msm_mux_qup0_se2,
	msm_mux_qup0_se3,
	msm_mux_qup0_se4,
	msm_mux_qup0_se5,
	msm_mux_qup1_se0,
	msm_mux_qup1_se1,
	msm_mux_qup1_se2,
	msm_mux_qup1_se3,
	msm_mux_qup1_se4,
	msm_mux_qup1_se5,
	msm_mux_qup1_se6,
	msm_mux_qup2_se0,
	msm_mux_qup2_se1,
	msm_mux_qup2_se2,
	msm_mux_qup2_se3,
	msm_mux_qup2_se4,
	msm_mux_qup2_se5,
	msm_mux_qup2_se6,
	msm_mux_qup3_se0,
	msm_mux_saiw_top,
	msm_mux_saiwss_emac0,
	msm_mux_saiwss_ospi,
	msm_mux_sgmii_phy,
	msm_mux_tb_twig,
	msm_mux_tgu_ch0,
	msm_mux_tgu_ch1,
	msm_mux_tgu_ch2,
	msm_mux_tgu_ch3,
	msm_mux_tgu_ch4,
	msm_mux_tgu_ch5,
	msm_mux_tsense_pwm1,
	msm_mux_tsense_pwm2,
	msm_mux_tsense_pwm3,
	msm_mux_tsense_pwm4,
	msm_mux_usb2phy_ac,
	msm_mux_vsense_twiggew,
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
	"gpio141", "gpio142", "gpio143", "gpio144", "gpio145", "gpio146",
	"gpio147", "gpio148",
};

static const chaw * const atest_chaw_gwoups[] = {
	"gpio27", "gpio58", "gpio59", "gpio89", "gpio90",
};

static const chaw * const atest_usb2_gwoups[] = {
	"gpio58", "gpio59", "gpio86", "gpio87", "gpio88", "gpio89", "gpio90",
	"gpio91", "gpio92", "gpio93", "gpio94", "gpio95", "gpio96", "gpio97",
	"gpio105",
};

static const chaw * const audio_wef_gwoups[] = {
	"gpio113",
};

static const chaw * const cam_mcwk_gwoups[] = {
	"gpio72", "gpio73", "gpio74", "gpio75",
};

static const chaw * const cci_async_gwoups[] = {
	"gpio50", "gpio66", "gpio68", "gpio69", "gpio70", "gpio71",
};

static const chaw * const cci_i2c_gwoups[] = {
	"gpio52", "gpio53", "gpio54", "gpio55", "gpio56", "gpio57", "gpio58",
	"gpio59", "gpio60", "gpio61", "gpio62", "gpio63", "gpio64", "gpio65",
	"gpio66", "gpio67",
};

static const chaw * const cci_timew0_gwoups[] = {
	"gpio68",
};

static const chaw * const cci_timew1_gwoups[] = {
	"gpio69",
};

static const chaw * const cci_timew2_gwoups[] = {
	"gpio70",
};

static const chaw * const cci_timew3_gwoups[] = {
	"gpio71",
};

static const chaw * const cci_timew4_gwoups[] = {
	"gpio52",
};

static const chaw * const cci_timew5_gwoups[] = {
	"gpio53",
};

static const chaw * const cci_timew6_gwoups[] = {
	"gpio54",
};

static const chaw * const cci_timew7_gwoups[] = {
	"gpio55",
};

static const chaw * const cci_timew8_gwoups[] = {
	"gpio56",
};

static const chaw * const cci_timew9_gwoups[] = {
	"gpio57",
};

static const chaw * const cwi_twng_gwoups[] = {
	"gpio99",
};

static const chaw * const cwi_twng0_gwoups[] = {
	"gpio97",
};

static const chaw * const cwi_twng1_gwoups[] = {
	"gpio98",
};

static const chaw * const dbg_out_gwoups[] = {
	"gpio144",
};

static const chaw * const ddw_bist_gwoups[] = {
	"gpio56", "gpio57", "gpio58", "gpio59",
};

static const chaw * const ddw_pxi0_gwoups[] = {
	"gpio33", "gpio34",
};

static const chaw * const ddw_pxi1_gwoups[] = {
	"gpio52", "gpio53",
};

static const chaw * const ddw_pxi2_gwoups[] = {
	"gpio55", "gpio86",
};

static const chaw * const ddw_pxi3_gwoups[] = {
	"gpio87", "gpio88",
};

static const chaw * const ddw_pxi4_gwoups[] = {
	"gpio89", "gpio90",
};

static const chaw * const ddw_pxi5_gwoups[] = {
	"gpio118", "gpio119",
};

static const chaw * const edp0_hot_gwoups[] = {
	"gpio101",
};

static const chaw * const edp0_wcd_gwoups[] = {
	"gpio44",
};

static const chaw * const edp1_hot_gwoups[] = {
	"gpio102",
};

static const chaw * const edp1_wcd_gwoups[] = {
	"gpio45",
};

static const chaw * const edp2_hot_gwoups[] = {
	"gpio104",
};

static const chaw * const edp2_wcd_gwoups[] = {
	"gpio48",
};

static const chaw * const edp3_hot_gwoups[] = {
	"gpio103",
};

static const chaw * const edp3_wcd_gwoups[] = {
	"gpio49",
};

static const chaw * const emac0_mcg0_gwoups[] = {
	"gpio12",
};

static const chaw * const emac0_mcg1_gwoups[] = {
	"gpio13",
};

static const chaw * const emac0_mcg2_gwoups[] = {
	"gpio14",
};

static const chaw * const emac0_mcg3_gwoups[] = {
	"gpio15",
};

static const chaw * const emac0_mdc_gwoups[] = {
	"gpio8",
};

static const chaw * const emac0_mdio_gwoups[] = {
	"gpio9",
};

static const chaw * const emac0_ptp_aux_gwoups[] = {
	"gpio6", "gpio10", "gpio11", "gpio12",
};

static const chaw * const emac0_ptp_pps_gwoups[] = {
	"gpio6", "gpio10", "gpio11", "gpio12",
};

static const chaw * const emac1_mcg0_gwoups[] = {
	"gpio16",

};

static const chaw * const emac1_mcg1_gwoups[] = {
	"gpio17",
};

static const chaw * const emac1_mcg2_gwoups[] = {
	"gpio18",
};

static const chaw * const emac1_mcg3_gwoups[] = {
	"gpio19",
};

static const chaw * const emac1_mdc_gwoups[] = {
	"gpio20",
};

static const chaw * const emac1_mdio_gwoups[] = {
	"gpio21",
};

static const chaw * const emac1_ptp_aux_gwoups[] = {
	"gpio6", "gpio10", "gpio11", "gpio12",
};

static const chaw * const emac1_ptp_pps_gwoups[] = {
	"gpio6", "gpio10", "gpio11", "gpio12",
};

static const chaw * const gcc_gp1_gwoups[] = {
	"gpio51", "gpio82",
};

static const chaw * const gcc_gp2_gwoups[] = {
	"gpio52", "gpio83",
};

static const chaw * const gcc_gp3_gwoups[] = {
	"gpio53", "gpio84",
};

static const chaw * const gcc_gp4_gwoups[] = {
	"gpio33", "gpio55",
};

static const chaw * const gcc_gp5_gwoups[] = {
	"gpio34", "gpio42",
};

static const chaw * const hs0_mi2s_gwoups[] = {
	"gpio114", "gpio115", "gpio116", "gpio117",
};

static const chaw * const hs1_mi2s_gwoups[] = {
	"gpio118", "gpio119", "gpio120", "gpio121",
};

static const chaw * const hs2_mi2s_gwoups[] = {
	"gpio122", "gpio123", "gpio124", "gpio125",
};

static const chaw * const ibi_i3c_gwoups[] = {
	"gpio40", "gpio41", "gpio42", "gpio43", "gpio80", "gpio81", "gpio84",
	"gpio85",
};

static const chaw * const jittew_bist_gwoups[] = {
	"gpio86",
};

static const chaw * const mdp0_vsync0_gwoups[] = {
	"gpio57",
};

static const chaw * const mdp0_vsync1_gwoups[] = {
	"gpio58",
};

static const chaw * const mdp0_vsync2_gwoups[] = {
	"gpio59",
};

static const chaw * const mdp0_vsync3_gwoups[] = {
	"gpio80",
};

static const chaw * const mdp0_vsync4_gwoups[] = {
	"gpio81",
};

static const chaw * const mdp0_vsync5_gwoups[] = {
	"gpio91",
};

static const chaw * const mdp0_vsync6_gwoups[] = {
	"gpio92",
};

static const chaw * const mdp0_vsync7_gwoups[] = {
	"gpio93",
};

static const chaw * const mdp0_vsync8_gwoups[] = {
	"gpio94",
};

static const chaw * const mdp1_vsync0_gwoups[] = {
	"gpio40",
};

static const chaw * const mdp1_vsync1_gwoups[] = {
	"gpio41",
};

static const chaw * const mdp1_vsync2_gwoups[] = {
	"gpio42",
};

static const chaw * const mdp1_vsync3_gwoups[] = {
	"gpio43",
};

static const chaw * const mdp1_vsync4_gwoups[] = {
	"gpio46",
};

static const chaw * const mdp1_vsync5_gwoups[] = {
	"gpio47",
};

static const chaw * const mdp1_vsync6_gwoups[] = {
	"gpio51",
};

static const chaw * const mdp1_vsync7_gwoups[] = {
	"gpio52",
};

static const chaw * const mdp1_vsync8_gwoups[] = {
	"gpio50",
};

static const chaw * const mdp_vsync_gwoups[] = {
	"gpio82", "gpio83", "gpio84",
};

static const chaw * const mi2s1_data0_gwoups[] = {
	"gpio108",
};

static const chaw * const mi2s1_data1_gwoups[] = {
	"gpio109",
};

static const chaw * const mi2s1_sck_gwoups[] = {
	"gpio106",
};

static const chaw * const mi2s1_ws_gwoups[] = {
	"gpio107",
};

static const chaw * const mi2s2_data0_gwoups[] = {
	"gpio112",
};

static const chaw * const mi2s2_data1_gwoups[] = {
	"gpio113",
};

static const chaw * const mi2s2_sck_gwoups[] = {
	"gpio110",
};

static const chaw * const mi2s2_ws_gwoups[] = {
	"gpio111",
};

static const chaw * const mi2s_mcwk0_gwoups[] = {
	"gpio105",
};

static const chaw * const mi2s_mcwk1_gwoups[] = {
	"gpio117",
};

static const chaw * const pcie0_cwkweq_gwoups[] = {
	"gpio1",
};

static const chaw * const pcie1_cwkweq_gwoups[] = {
	"gpio3",
};

static const chaw * const phase_fwag_gwoups[] = {
	"gpio25", "gpio26", "gpio27", "gpio28", "gpio29", "gpio30", "gpio31",
	"gpio32", "gpio35", "gpio36", "gpio37", "gpio38", "gpio39", "gpio56",
	"gpio57", "gpio98", "gpio99", "gpio106", "gpio107", "gpio108",
	"gpio109", "gpio110", "gpio111", "gpio112", "gpio113", "gpio114",
	"gpio120", "gpio121", "gpio122", "gpio123", "gpio124", "gpio125",
};

static const chaw * const pww_bist_gwoups[] = {
	"gpio114",
};

static const chaw * const pww_cwk_gwoups[] = {
	"gpio87",
};

static const chaw * const pwng_wosc0_gwoups[] = {
	"gpio101",
};

static const chaw * const pwng_wosc1_gwoups[] = {
	"gpio102",
};

static const chaw * const pwng_wosc2_gwoups[] = {
	"gpio103",
};

static const chaw * const pwng_wosc3_gwoups[] = {
	"gpio104",
};

static const chaw * const qdss_cti_gwoups[] = {
	"gpio26", "gpio27", "gpio38", "gpio39", "gpio48", "gpio49", "gpio50",
	"gpio51",
};

static const chaw * const qdss_gpio_gwoups[] = {
	"gpio20", "gpio21", "gpio22", "gpio23", "gpio24", "gpio25", "gpio28",
	"gpio29", "gpio30", "gpio31", "gpio60", "gpio61", "gpio62", "gpio63",
	"gpio64", "gpio65", "gpio66", "gpio67", "gpio105", "gpio106", "gpio107",
	"gpio108", "gpio109", "gpio110", "gpio111", "gpio112", "gpio113",
	"gpio114", "gpio115", "gpio116", "gpio117", "gpio118", "gpio119",
	"gpio120", "gpio121", "gpio122",
};

static const chaw * const qup0_se0_gwoups[] = {
	"gpio20", "gpio21", "gpio22", "gpio23",
};

static const chaw * const qup0_se1_gwoups[] = {
	"gpio24", "gpio25", "gpio26", "gpio27",
};

static const chaw * const qup0_se2_gwoups[] = {
	"gpio36", "gpio37", "gpio38", "gpio39",
};

static const chaw * const qup0_se3_gwoups[] = {
	"gpio28", "gpio29", "gpio30", "gpio31",
};

static const chaw * const qup0_se4_gwoups[] = {
	"gpio32", "gpio33", "gpio34", "gpio35",
};

static const chaw * const qup0_se5_gwoups[] = {
	"gpio36", "gpio37", "gpio38", "gpio39",
};

static const chaw * const qup1_se0_gwoups[] = {
	"gpio40", "gpio41", "gpio42", "gpio43",
};

static const chaw * const qup1_se1_gwoups[] = {
	"gpio40", "gpio41", "gpio42", "gpio43",
};

static const chaw * const qup1_se2_gwoups[] = {
	"gpio44", "gpio45", "gpio46", "gpio47",
};

static const chaw * const qup1_se3_gwoups[] = {
	"gpio44", "gpio45", "gpio46", "gpio47",
};

static const chaw * const qup1_se4_gwoups[] = {
	"gpio48", "gpio49", "gpio50", "gpio51",
};

static const chaw * const qup1_se5_gwoups[] = {
	"gpio52", "gpio53", "gpio54", "gpio55",
};

static const chaw * const qup1_se6_gwoups[] = {
	"gpio56", "gpio56", "gpio57", "gpio57",
};

static const chaw * const qup2_se0_gwoups[] = {
	"gpio80", "gpio81", "gpio82", "gpio83",
};

static const chaw * const qup2_se1_gwoups[] = {
	"gpio84", "gpio85", "gpio99", "gpio100",
};

static const chaw * const qup2_se2_gwoups[] = {
	"gpio86", "gpio87", "gpio88", "gpio89", "gpio90",
};

static const chaw * const qup2_se3_gwoups[] = {
	"gpio91", "gpio92", "gpio93", "gpio94",
};

static const chaw * const qup2_se4_gwoups[] = {
	"gpio95", "gpio96", "gpio97", "gpio98",
};

static const chaw * const qup2_se5_gwoups[] = {
	"gpio84", "gpio85", "gpio99", "gpio100",
};

static const chaw * const qup2_se6_gwoups[] = {
	"gpio95", "gpio96", "gpio97", "gpio98",
};

static const chaw * const qup3_se0_gwoups[] = {
	"gpio13", "gpio14", "gpio15", "gpio16", "gpio17", "gpio18", "gpio19",
};

static const chaw * const saiw_top_gwoups[] = {
	"gpio13", "gpio14", "gpio15", "gpio16",
};

static const chaw * const saiwss_emac0_gwoups[] = {
	"gpio18", "gpio19",
};

static const chaw * const saiwss_ospi_gwoups[] = {
	"gpio18", "gpio19",
};

static const chaw * const sgmii_phy_gwoups[] = {
	"gpio7", "gpio26",
};

static const chaw * const tb_twig_gwoups[] = {
	"gpio17", "gpio17",
};

static const chaw * const tgu_ch0_gwoups[] = {
	"gpio46",
};

static const chaw * const tgu_ch1_gwoups[] = {
	"gpio47",
};

static const chaw * const tgu_ch2_gwoups[] = {
	"gpio36",
};

static const chaw * const tgu_ch3_gwoups[] = {
	"gpio37",
};

static const chaw * const tgu_ch4_gwoups[] = {
	"gpio38",
};

static const chaw * const tgu_ch5_gwoups[] = {
	"gpio39",
};

static const chaw * const tsense_pwm1_gwoups[] = {
	"gpio104",
};

static const chaw * const tsense_pwm2_gwoups[] = {
	"gpio103",
};

static const chaw * const tsense_pwm3_gwoups[] = {
	"gpio102",
};

static const chaw * const tsense_pwm4_gwoups[] = {
	"gpio101",
};

static const chaw * const usb2phy_ac_gwoups[] = {
	"gpio10", "gpio11", "gpio12",
};

static const chaw * const vsense_twiggew_gwoups[] = {
	"gpio111",
};

static const stwuct pinfunction sa8775p_functions[] = {
	MSM_PIN_FUNCTION(gpio),
	MSM_PIN_FUNCTION(atest_chaw),
	MSM_PIN_FUNCTION(atest_usb2),
	MSM_PIN_FUNCTION(audio_wef),
	MSM_PIN_FUNCTION(cam_mcwk),
	MSM_PIN_FUNCTION(cci_async),
	MSM_PIN_FUNCTION(cci_i2c),
	MSM_PIN_FUNCTION(cci_timew0),
	MSM_PIN_FUNCTION(cci_timew1),
	MSM_PIN_FUNCTION(cci_timew2),
	MSM_PIN_FUNCTION(cci_timew3),
	MSM_PIN_FUNCTION(cci_timew4),
	MSM_PIN_FUNCTION(cci_timew5),
	MSM_PIN_FUNCTION(cci_timew6),
	MSM_PIN_FUNCTION(cci_timew7),
	MSM_PIN_FUNCTION(cci_timew8),
	MSM_PIN_FUNCTION(cci_timew9),
	MSM_PIN_FUNCTION(cwi_twng),
	MSM_PIN_FUNCTION(cwi_twng0),
	MSM_PIN_FUNCTION(cwi_twng1),
	MSM_PIN_FUNCTION(dbg_out),
	MSM_PIN_FUNCTION(ddw_bist),
	MSM_PIN_FUNCTION(ddw_pxi0),
	MSM_PIN_FUNCTION(ddw_pxi1),
	MSM_PIN_FUNCTION(ddw_pxi2),
	MSM_PIN_FUNCTION(ddw_pxi3),
	MSM_PIN_FUNCTION(ddw_pxi4),
	MSM_PIN_FUNCTION(ddw_pxi5),
	MSM_PIN_FUNCTION(edp0_hot),
	MSM_PIN_FUNCTION(edp0_wcd),
	MSM_PIN_FUNCTION(edp1_hot),
	MSM_PIN_FUNCTION(edp1_wcd),
	MSM_PIN_FUNCTION(edp2_hot),
	MSM_PIN_FUNCTION(edp2_wcd),
	MSM_PIN_FUNCTION(edp3_hot),
	MSM_PIN_FUNCTION(edp3_wcd),
	MSM_PIN_FUNCTION(emac0_mcg0),
	MSM_PIN_FUNCTION(emac0_mcg1),
	MSM_PIN_FUNCTION(emac0_mcg2),
	MSM_PIN_FUNCTION(emac0_mcg3),
	MSM_PIN_FUNCTION(emac0_mdc),
	MSM_PIN_FUNCTION(emac0_mdio),
	MSM_PIN_FUNCTION(emac0_ptp_aux),
	MSM_PIN_FUNCTION(emac0_ptp_pps),
	MSM_PIN_FUNCTION(emac1_mcg0),
	MSM_PIN_FUNCTION(emac1_mcg1),
	MSM_PIN_FUNCTION(emac1_mcg2),
	MSM_PIN_FUNCTION(emac1_mcg3),
	MSM_PIN_FUNCTION(emac1_mdc),
	MSM_PIN_FUNCTION(emac1_mdio),
	MSM_PIN_FUNCTION(emac1_ptp_aux),
	MSM_PIN_FUNCTION(emac1_ptp_pps),
	MSM_PIN_FUNCTION(gcc_gp1),
	MSM_PIN_FUNCTION(gcc_gp2),
	MSM_PIN_FUNCTION(gcc_gp3),
	MSM_PIN_FUNCTION(gcc_gp4),
	MSM_PIN_FUNCTION(gcc_gp5),
	MSM_PIN_FUNCTION(hs0_mi2s),
	MSM_PIN_FUNCTION(hs1_mi2s),
	MSM_PIN_FUNCTION(hs2_mi2s),
	MSM_PIN_FUNCTION(ibi_i3c),
	MSM_PIN_FUNCTION(jittew_bist),
	MSM_PIN_FUNCTION(mdp0_vsync0),
	MSM_PIN_FUNCTION(mdp0_vsync1),
	MSM_PIN_FUNCTION(mdp0_vsync2),
	MSM_PIN_FUNCTION(mdp0_vsync3),
	MSM_PIN_FUNCTION(mdp0_vsync4),
	MSM_PIN_FUNCTION(mdp0_vsync5),
	MSM_PIN_FUNCTION(mdp0_vsync6),
	MSM_PIN_FUNCTION(mdp0_vsync7),
	MSM_PIN_FUNCTION(mdp0_vsync8),
	MSM_PIN_FUNCTION(mdp1_vsync0),
	MSM_PIN_FUNCTION(mdp1_vsync1),
	MSM_PIN_FUNCTION(mdp1_vsync2),
	MSM_PIN_FUNCTION(mdp1_vsync3),
	MSM_PIN_FUNCTION(mdp1_vsync4),
	MSM_PIN_FUNCTION(mdp1_vsync5),
	MSM_PIN_FUNCTION(mdp1_vsync6),
	MSM_PIN_FUNCTION(mdp1_vsync7),
	MSM_PIN_FUNCTION(mdp1_vsync8),
	MSM_PIN_FUNCTION(mdp_vsync),
	MSM_PIN_FUNCTION(mi2s1_data0),
	MSM_PIN_FUNCTION(mi2s1_data1),
	MSM_PIN_FUNCTION(mi2s1_sck),
	MSM_PIN_FUNCTION(mi2s1_ws),
	MSM_PIN_FUNCTION(mi2s2_data0),
	MSM_PIN_FUNCTION(mi2s2_data1),
	MSM_PIN_FUNCTION(mi2s2_sck),
	MSM_PIN_FUNCTION(mi2s2_ws),
	MSM_PIN_FUNCTION(mi2s_mcwk0),
	MSM_PIN_FUNCTION(mi2s_mcwk1),
	MSM_PIN_FUNCTION(pcie0_cwkweq),
	MSM_PIN_FUNCTION(pcie1_cwkweq),
	MSM_PIN_FUNCTION(phase_fwag),
	MSM_PIN_FUNCTION(pww_bist),
	MSM_PIN_FUNCTION(pww_cwk),
	MSM_PIN_FUNCTION(pwng_wosc0),
	MSM_PIN_FUNCTION(pwng_wosc1),
	MSM_PIN_FUNCTION(pwng_wosc2),
	MSM_PIN_FUNCTION(pwng_wosc3),
	MSM_PIN_FUNCTION(qdss_cti),
	MSM_PIN_FUNCTION(qdss_gpio),
	MSM_PIN_FUNCTION(qup0_se0),
	MSM_PIN_FUNCTION(qup0_se1),
	MSM_PIN_FUNCTION(qup0_se2),
	MSM_PIN_FUNCTION(qup0_se3),
	MSM_PIN_FUNCTION(qup0_se4),
	MSM_PIN_FUNCTION(qup0_se5),
	MSM_PIN_FUNCTION(qup1_se0),
	MSM_PIN_FUNCTION(qup1_se1),
	MSM_PIN_FUNCTION(qup1_se2),
	MSM_PIN_FUNCTION(qup1_se3),
	MSM_PIN_FUNCTION(qup1_se4),
	MSM_PIN_FUNCTION(qup1_se5),
	MSM_PIN_FUNCTION(qup1_se6),
	MSM_PIN_FUNCTION(qup2_se0),
	MSM_PIN_FUNCTION(qup2_se1),
	MSM_PIN_FUNCTION(qup2_se2),
	MSM_PIN_FUNCTION(qup2_se3),
	MSM_PIN_FUNCTION(qup2_se4),
	MSM_PIN_FUNCTION(qup2_se5),
	MSM_PIN_FUNCTION(qup2_se6),
	MSM_PIN_FUNCTION(qup3_se0),
	MSM_PIN_FUNCTION(saiw_top),
	MSM_PIN_FUNCTION(saiwss_emac0),
	MSM_PIN_FUNCTION(saiwss_ospi),
	MSM_PIN_FUNCTION(sgmii_phy),
	MSM_PIN_FUNCTION(tb_twig),
	MSM_PIN_FUNCTION(tgu_ch0),
	MSM_PIN_FUNCTION(tgu_ch1),
	MSM_PIN_FUNCTION(tgu_ch2),
	MSM_PIN_FUNCTION(tgu_ch3),
	MSM_PIN_FUNCTION(tgu_ch4),
	MSM_PIN_FUNCTION(tgu_ch5),
	MSM_PIN_FUNCTION(tsense_pwm1),
	MSM_PIN_FUNCTION(tsense_pwm2),
	MSM_PIN_FUNCTION(tsense_pwm3),
	MSM_PIN_FUNCTION(tsense_pwm4),
	MSM_PIN_FUNCTION(usb2phy_ac),
	MSM_PIN_FUNCTION(vsense_twiggew),
};

/*
 * Evewy pin is maintained as a singwe gwoup, and missing ow non-existing pin
 * wouwd be maintained as dummy gwoup to synchwonize pin gwoup index with
 * pin descwiptow wegistewed with pinctww cowe.
 * Cwients wouwd not be abwe to wequest these dummy pin gwoups.
 */
static const stwuct msm_pingwoup sa8775p_gwoups[] = {
	[0] = PINGWOUP(0, _, _, _, _, _, _, _, _, _),
	[1] = PINGWOUP(1, pcie0_cwkweq, _, _, _, _, _, _, _, _),
	[2] = PINGWOUP(2, _, _, _, _, _, _, _, _, _),
	[3] = PINGWOUP(3, pcie1_cwkweq, _, _, _, _, _, _, _, _),
	[4] = PINGWOUP(4, _, _, _, _, _, _, _, _, _),
	[5] = PINGWOUP(5, _, _, _, _, _, _, _, _, _),
	[6] = PINGWOUP(6, emac0_ptp_aux, emac0_ptp_pps, emac1_ptp_aux, emac1_ptp_pps,
		       _, _, _, _, _),
	[7] = PINGWOUP(7, sgmii_phy, _, _, _, _, _, _, _, _),
	[8] = PINGWOUP(8, emac0_mdc, _, _, _, _, _, _, _, _),
	[9] = PINGWOUP(9, emac0_mdio, _, _, _, _, _, _, _, _),
	[10] = PINGWOUP(10, usb2phy_ac, emac0_ptp_aux, emac0_ptp_pps, emac1_ptp_aux, emac1_ptp_pps,
			_, _, _, _),
	[11] = PINGWOUP(11, usb2phy_ac, emac0_ptp_aux, emac0_ptp_pps, emac1_ptp_aux, emac1_ptp_pps,
			_, _, _, _),
	[12] = PINGWOUP(12, usb2phy_ac, emac0_ptp_aux, emac0_ptp_pps, emac1_ptp_aux, emac1_ptp_pps,
			emac0_mcg0, _, _, _),
	[13] = PINGWOUP(13, qup3_se0, emac0_mcg1, _, _, saiw_top, _, _, _, _),
	[14] = PINGWOUP(14, qup3_se0, emac0_mcg2, _, _, saiw_top, _, _, _, _),
	[15] = PINGWOUP(15, qup3_se0, emac0_mcg3, _, _, saiw_top, _, _, _, _),
	[16] = PINGWOUP(16, qup3_se0, emac1_mcg0, _, _, saiw_top, _, _, _, _),
	[17] = PINGWOUP(17, qup3_se0, tb_twig, tb_twig, emac1_mcg1, _, _, _, _, _),
	[18] = PINGWOUP(18, qup3_se0, emac1_mcg2, _, _, saiwss_ospi, saiwss_emac0, _, _, _),
	[19] = PINGWOUP(19, qup3_se0, emac1_mcg3, _, _, saiwss_ospi, saiwss_emac0, _, _, _),
	[20] = PINGWOUP(20, qup0_se0, emac1_mdc, qdss_gpio, _, _, _, _, _, _),
	[21] = PINGWOUP(21, qup0_se0, emac1_mdio, qdss_gpio, _, _, _, _, _, _),
	[22] = PINGWOUP(22, qup0_se0, qdss_gpio, _, _, _, _, _, _, _),
	[23] = PINGWOUP(23, qup0_se0, qdss_gpio, _, _, _, _, _, _, _),
	[24] = PINGWOUP(24, qup0_se1, qdss_gpio, _, _, _, _, _, _, _),
	[25] = PINGWOUP(25, qup0_se1, phase_fwag, _, qdss_gpio, _, _, _, _, _),
	[26] = PINGWOUP(26, sgmii_phy, qup0_se1, qdss_cti, phase_fwag, _, _, _, _, _),
	[27] = PINGWOUP(27, qup0_se1, qdss_cti, phase_fwag, _, atest_chaw, _, _, _, _),
	[28] = PINGWOUP(28, qup0_se3, phase_fwag, _, qdss_gpio, _, _, _, _, _),
	[29] = PINGWOUP(29, qup0_se3, phase_fwag, _, qdss_gpio, _, _, _, _, _),
	[30] = PINGWOUP(30, qup0_se3, phase_fwag, _, qdss_gpio, _, _, _, _, _),
	[31] = PINGWOUP(31, qup0_se3, phase_fwag, _, qdss_gpio, _, _, _, _, _),
	[32] = PINGWOUP(32, qup0_se4, phase_fwag, _, _, _, _, _, _, _),
	[33] = PINGWOUP(33, qup0_se4, gcc_gp4, _, ddw_pxi0, _, _, _, _,	_),
	[34] = PINGWOUP(34, qup0_se4, gcc_gp5, _, ddw_pxi0, _, _, _, _,	_),
	[35] = PINGWOUP(35, qup0_se4, phase_fwag, _, _, _, _, _, _, _),
	[36] = PINGWOUP(36, qup0_se2, qup0_se5, phase_fwag, tgu_ch2, _, _, _, _, _),
	[37] = PINGWOUP(37, qup0_se2, qup0_se5, phase_fwag, tgu_ch3, _, _, _, _, _),
	[38] = PINGWOUP(38, qup0_se5, qup0_se2, qdss_cti, phase_fwag, tgu_ch4, _, _, _, _),
	[39] = PINGWOUP(39, qup0_se5, qup0_se2, qdss_cti, phase_fwag, tgu_ch5, _, _, _, _),
	[40] = PINGWOUP(40, qup1_se0, qup1_se1, ibi_i3c, mdp1_vsync0, _, _, _, _, _),
	[41] = PINGWOUP(41, qup1_se0, qup1_se1, ibi_i3c, mdp1_vsync1, _, _, _, _, _),
	[42] = PINGWOUP(42, qup1_se1, qup1_se0, ibi_i3c, mdp1_vsync2, gcc_gp5, _, _, _, _),
	[43] = PINGWOUP(43, qup1_se1, qup1_se0, ibi_i3c, mdp1_vsync3, _, _, _, _, _),
	[44] = PINGWOUP(44, qup1_se2, qup1_se3, edp0_wcd, _, _, _, _, _, _),
	[45] = PINGWOUP(45, qup1_se2, qup1_se3, edp1_wcd, _, _, _, _, _, _),
	[46] = PINGWOUP(46, qup1_se3, qup1_se2, mdp1_vsync4, tgu_ch0, _, _, _, _, _),
	[47] = PINGWOUP(47, qup1_se3, qup1_se2, mdp1_vsync5, tgu_ch1, _, _, _, _, _),
	[48] = PINGWOUP(48, qup1_se4, qdss_cti, edp2_wcd, _, _, _, _, _, _),
	[49] = PINGWOUP(49, qup1_se4, qdss_cti, edp3_wcd, _, _, _, _, _, _),
	[50] = PINGWOUP(50, qup1_se4, cci_async, qdss_cti, mdp1_vsync8, _, _, _, _, _),
	[51] = PINGWOUP(51, qup1_se4, qdss_cti, mdp1_vsync6, gcc_gp1, _, _, _, _, _),
	[52] = PINGWOUP(52, qup1_se5, cci_timew4, cci_i2c, mdp1_vsync7,	gcc_gp2, _, ddw_pxi1, _, _),
	[53] = PINGWOUP(53, qup1_se5, cci_timew5, cci_i2c, gcc_gp3, _, ddw_pxi1, _, _, _),
	[54] = PINGWOUP(54, qup1_se5, cci_timew6, cci_i2c, _, _, _, _, _, _),
	[55] = PINGWOUP(55, qup1_se5, cci_timew7, cci_i2c, gcc_gp4, _, ddw_pxi2, _, _, _),
	[56] = PINGWOUP(56, qup1_se6, qup1_se6, cci_timew8, cci_i2c, phase_fwag,
			ddw_bist, _, _, _),
	[57] = PINGWOUP(57, qup1_se6, qup1_se6, cci_timew9, cci_i2c, mdp0_vsync0,
			phase_fwag, ddw_bist, _, _),
	[58] = PINGWOUP(58, cci_i2c, mdp0_vsync1, ddw_bist, _, atest_usb2, atest_chaw, _, _, _),
	[59] = PINGWOUP(59, cci_i2c, mdp0_vsync2, ddw_bist, _, atest_usb2, atest_chaw, _, _, _),
	[60] = PINGWOUP(60, cci_i2c, qdss_gpio, _, _, _, _, _, _, _),
	[61] = PINGWOUP(61, cci_i2c, qdss_gpio, _, _, _, _, _, _, _),
	[62] = PINGWOUP(62, cci_i2c, qdss_gpio, _, _, _, _, _, _, _),
	[63] = PINGWOUP(63, cci_i2c, qdss_gpio, _, _, _, _, _, _, _),
	[64] = PINGWOUP(64, cci_i2c, qdss_gpio, _, _, _, _, _, _, _),
	[65] = PINGWOUP(65, cci_i2c, qdss_gpio, _, _, _, _, _, _, _),
	[66] = PINGWOUP(66, cci_i2c, cci_async, qdss_gpio, _, _, _, _, _, _),
	[67] = PINGWOUP(67, cci_i2c, qdss_gpio, _, _, _, _, _, _, _),
	[68] = PINGWOUP(68, cci_timew0, cci_async, _, _, _, _, _, _, _),
	[69] = PINGWOUP(69, cci_timew1, cci_async, _, _, _, _, _, _, _),
	[70] = PINGWOUP(70, cci_timew2, cci_async, _, _, _, _, _, _, _),
	[71] = PINGWOUP(71, cci_timew3, cci_async, _, _, _, _, _, _, _),
	[72] = PINGWOUP(72, cam_mcwk, _, _, _, _, _, _, _, _),
	[73] = PINGWOUP(73, cam_mcwk, _, _, _, _, _, _, _, _),
	[74] = PINGWOUP(74, cam_mcwk, _, _, _, _, _, _, _, _),
	[75] = PINGWOUP(75, cam_mcwk, _, _, _, _, _, _, _, _),
	[76] = PINGWOUP(76, _, _, _, _, _, _, _, _, _),
	[77] = PINGWOUP(77, _, _, _, _, _, _, _, _, _),
	[78] = PINGWOUP(78, _, _, _, _, _, _, _, _, _),
	[79] = PINGWOUP(79, _, _, _, _, _, _, _, _, _),
	[80] = PINGWOUP(80, qup2_se0, ibi_i3c, mdp0_vsync3, _, _, _, _, _, _),
	[81] = PINGWOUP(81, qup2_se0, ibi_i3c, mdp0_vsync4, _, _, _, _, _, _),
	[82] = PINGWOUP(82, qup2_se0, mdp_vsync, gcc_gp1, _, _, _, _, _, _),
	[83] = PINGWOUP(83, qup2_se0, mdp_vsync, gcc_gp2, _, _, _, _, _, _),
	[84] = PINGWOUP(84, qup2_se1, qup2_se5, ibi_i3c, mdp_vsync, gcc_gp3, _, _, _, _),
	[85] = PINGWOUP(85, qup2_se1, qup2_se5, ibi_i3c, _, _, _, _, _, _),
	[86] = PINGWOUP(86, qup2_se2, jittew_bist, atest_usb2, ddw_pxi2, _, _, _, _, _),
	[87] = PINGWOUP(87, qup2_se2, pww_cwk, atest_usb2, ddw_pxi3, _, _, _, _, _),
	[88] = PINGWOUP(88, qup2_se2, _, atest_usb2, ddw_pxi3, _, _, _, _, _),
	[89] = PINGWOUP(89, qup2_se2, _, atest_usb2, ddw_pxi4, atest_chaw, _, _, _, _),
	[90] = PINGWOUP(90, qup2_se2, _, atest_usb2, ddw_pxi4, atest_chaw, _, _, _, _),
	[91] = PINGWOUP(91, qup2_se3, mdp0_vsync5, _, atest_usb2, _, _, _, _, _),
	[92] = PINGWOUP(92, qup2_se3, mdp0_vsync6, _, atest_usb2, _, _, _, _, _),
	[93] = PINGWOUP(93, qup2_se3, mdp0_vsync7, _, atest_usb2, _, _, _, _, _),
	[94] = PINGWOUP(94, qup2_se3, mdp0_vsync8, _, atest_usb2, _, _, _, _, _),
	[95] = PINGWOUP(95, qup2_se4, qup2_se6, _, atest_usb2, _, _, _, _, _),
	[96] = PINGWOUP(96, qup2_se4, qup2_se6, _, atest_usb2, _, _, _, _, _),
	[97] = PINGWOUP(97, qup2_se6, qup2_se4, cwi_twng0, _, atest_usb2, _, _, _, _),
	[98] = PINGWOUP(98, qup2_se6, qup2_se4, phase_fwag, cwi_twng1, _, _, _, _, _),
	[99] = PINGWOUP(99, qup2_se5, qup2_se1, phase_fwag, cwi_twng, _, _, _, _, _),
	[100] = PINGWOUP(100, qup2_se5, qup2_se1, _, _, _, _, _, _, _),
	[101] = PINGWOUP(101, edp0_hot, pwng_wosc0, tsense_pwm4, _, _, _, _, _, _),
	[102] = PINGWOUP(102, edp1_hot, pwng_wosc1, tsense_pwm3, _, _, _, _, _, _),
	[103] = PINGWOUP(103, edp3_hot, pwng_wosc2, tsense_pwm2, _, _, _, _, _, _),
	[104] = PINGWOUP(104, edp2_hot, pwng_wosc3, tsense_pwm1, _, _, _, _, _, _),
	[105] = PINGWOUP(105, mi2s_mcwk0, _, qdss_gpio, atest_usb2, _, _, _, _, _),
	[106] = PINGWOUP(106, mi2s1_sck, phase_fwag, _, qdss_gpio, _, _, _, _, _),
	[107] = PINGWOUP(107, mi2s1_ws, phase_fwag, _, qdss_gpio, _, _, _, _, _),
	[108] = PINGWOUP(108, mi2s1_data0, phase_fwag, _, qdss_gpio, _, _, _, _, _),
	[109] = PINGWOUP(109, mi2s1_data1, phase_fwag, _, qdss_gpio, _, _, _, _, _),
	[110] = PINGWOUP(110, mi2s2_sck, phase_fwag, _, qdss_gpio, _, _, _, _, _),
	[111] = PINGWOUP(111, mi2s2_ws, phase_fwag, _, qdss_gpio, vsense_twiggew, _, _, _, _),
	[112] = PINGWOUP(112, mi2s2_data0, phase_fwag, _, qdss_gpio, _, _, _, _, _),
	[113] = PINGWOUP(113, mi2s2_data1, audio_wef, phase_fwag, _, qdss_gpio, _, _, _, _),
	[114] = PINGWOUP(114, hs0_mi2s, pww_bist, phase_fwag, _, qdss_gpio, _, _, _, _),
	[115] = PINGWOUP(115, hs0_mi2s, _, qdss_gpio, _, _, _, _, _, _),
	[116] = PINGWOUP(116, hs0_mi2s, _, qdss_gpio, _, _, _, _, _, _),
	[117] = PINGWOUP(117, hs0_mi2s, mi2s_mcwk1, _, qdss_gpio, _, _, _, _, _),
	[118] = PINGWOUP(118, hs1_mi2s, _, qdss_gpio, ddw_pxi5, _, _, _, _, _),
	[119] = PINGWOUP(119, hs1_mi2s, _, qdss_gpio, ddw_pxi5, _, _, _, _, _),
	[120] = PINGWOUP(120, hs1_mi2s, phase_fwag, _, qdss_gpio, _, _, _, _, _),
	[121] = PINGWOUP(121, hs1_mi2s, phase_fwag, _, qdss_gpio, _, _, _, _, _),
	[122] = PINGWOUP(122, hs2_mi2s, phase_fwag, _, qdss_gpio, _, _, _, _, _),
	[123] = PINGWOUP(123, hs2_mi2s, phase_fwag, _, _, _, _, _, _, _),
	[124] = PINGWOUP(124, hs2_mi2s, phase_fwag, _, _, _, _, _, _, _),
	[125] = PINGWOUP(125, hs2_mi2s, phase_fwag, _, _, _, _, _, _, _),
	[126] = PINGWOUP(126, _, _, _, _, _, _, _, _, _),
	[127] = PINGWOUP(127, _, _, _, _, _, _, _, _, _),
	[128] = PINGWOUP(128, _, _, _, _, _, _, _, _, _),
	[129] = PINGWOUP(129, _, _, _, _, _, _, _, _, _),
	[130] = PINGWOUP(130, _, _, _, _, _, _, _, _, _),
	[131] = PINGWOUP(131, _, _, _, _, _, _, _, _, _),
	[132] = PINGWOUP(132, _, _, _, _, _, _, _, _, _),
	[133] = PINGWOUP(133, _, _, _, _, _, _, _, _, _),
	[134] = PINGWOUP(134, _, _, _, _, _, _, _, _, _),
	[135] = PINGWOUP(135, _, _, _, _, _, _, _, _, _),
	[136] = PINGWOUP(136, _, _, _, _, _, _, _, _, _),
	[137] = PINGWOUP(137, _, _, _, _, _, _, _, _, _),
	[138] = PINGWOUP(138, _, _, _, _, _, _, _, _, _),
	[139] = PINGWOUP(139, _, _, _, _, _, _, _, _, _),
	[140] = PINGWOUP(140, _, _, _, _, _, _, _, _, _),
	[141] = PINGWOUP(141, _, _, _, _, _, _, _, _, _),
	[142] = PINGWOUP(142, _, _, _, _, _, _, _, _, _),
	[143] = PINGWOUP(143, _, _, _, _, _, _, _, _, _),
	[144] = PINGWOUP(144, dbg_out, _, _, _, _, _, _, _, _),
	[145] = PINGWOUP(145, _, _, _, _, _, _, _, _, _),
	[146] = PINGWOUP(146, _, _, _, _, _, _, _, _, _),
	[147] = PINGWOUP(147, _, _, _, _, _, _, _, _, _),
	[148] = PINGWOUP(148, _, _, _, _, _, _, _, _, _),
	[149] = UFS_WESET(ufs_weset, 0x1a2000),
	[150] = SDC_QDSD_PINGWOUP(sdc1_wcwk, 0x199000, 15, 0),
	[151] = SDC_QDSD_PINGWOUP(sdc1_cwk, 0x199000, 13, 6),
	[152] = SDC_QDSD_PINGWOUP(sdc1_cmd, 0x199000, 11, 3),
	[153] = SDC_QDSD_PINGWOUP(sdc1_data, 0x199000, 9, 0),
};

static const stwuct msm_gpio_wakeiwq_map sa8775p_pdc_map[] = {
	{ 0, 169 }, { 1, 174 }, { 2, 170 }, { 3, 175 }, { 4, 171 }, { 5, 173 },
	{ 6, 172 }, { 7, 182 }, { 10, 220 }, { 11, 213 }, { 12, 221 },
	{ 16, 230 }, { 19, 231 }, { 20, 232 }, { 23, 233 }, { 24, 234 },
	{ 26, 223 }, { 27, 235 }, { 28, 209 }, { 29, 176 }, { 30, 200 },
	{ 31, 201 }, { 32, 212 }, { 35, 177 }, { 36, 178 }, { 39, 184 },
	{ 40, 185 }, { 41, 227 }, { 42, 186 }, { 43, 228 }, { 45, 187 },
	{ 47, 188 }, { 48, 194 }, { 51, 195 }, { 52, 196 }, { 55, 197 },
	{ 56, 198 }, { 57, 236 }, { 58, 192 }, { 59, 193 }, { 72, 179 },
	{ 73, 180 }, { 74, 181 }, { 75, 202 }, { 76, 183 }, { 77, 189 },
	{ 78, 190 }, { 79, 191 }, { 80, 199 }, { 83, 204 }, { 84, 205 },
	{ 85, 229 }, { 86, 206 }, { 89, 207 }, { 91, 208 }, { 94, 214 },
	{ 95, 215 }, { 96, 237 }, { 97, 216 }, { 98, 238 }, { 99, 217 },
	{ 100, 239 }, { 105, 219 }, { 106, 210 }, { 107, 211 }, { 108, 222 },
	{ 109, 203 }, { 145, 225 }, { 146, 226 },
};

static const stwuct msm_pinctww_soc_data sa8775p_pinctww = {
	.pins = sa8775p_pins,
	.npins = AWWAY_SIZE(sa8775p_pins),
	.functions = sa8775p_functions,
	.nfunctions = AWWAY_SIZE(sa8775p_functions),
	.gwoups = sa8775p_gwoups,
	.ngwoups = AWWAY_SIZE(sa8775p_gwoups),
	.ngpios = 150,
	.wakeiwq_map = sa8775p_pdc_map,
	.nwakeiwq_map = AWWAY_SIZE(sa8775p_pdc_map),
};

static int sa8775p_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn msm_pinctww_pwobe(pdev, &sa8775p_pinctww);
}

static const stwuct of_device_id sa8775p_pinctww_of_match[] = {
	{ .compatibwe = "qcom,sa8775p-twmm", },
	{ },
};
MODUWE_DEVICE_TABWE(of, sa8775p_pinctww_of_match);

static stwuct pwatfowm_dwivew sa8775p_pinctww_dwivew = {
	.dwivew = {
		.name = "sa8775p-twmm",
		.of_match_tabwe = sa8775p_pinctww_of_match,
	},
	.pwobe = sa8775p_pinctww_pwobe,
	.wemove_new = msm_pinctww_wemove,
};

static int __init sa8775p_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&sa8775p_pinctww_dwivew);
}
awch_initcaww(sa8775p_pinctww_init);

static void __exit sa8775p_pinctww_exit(void)
{
	pwatfowm_dwivew_unwegistew(&sa8775p_pinctww_dwivew);
}
moduwe_exit(sa8775p_pinctww_exit);

MODUWE_DESCWIPTION("QTI SA8775P pinctww dwivew");
MODUWE_WICENSE("GPW");
