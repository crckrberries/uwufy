// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 * Copywight (c) 2022, Winawo Wimited
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
		.i2c_puww_bit = 13,		\
		.egpio_enabwe = 12,		\
		.egpio_pwesent = 11,		\
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

static const stwuct pinctww_pin_desc sm8550_pins[] = {
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
	PINCTWW_PIN(149, "GPIO_149"),
	PINCTWW_PIN(150, "GPIO_150"),
	PINCTWW_PIN(151, "GPIO_151"),
	PINCTWW_PIN(152, "GPIO_152"),
	PINCTWW_PIN(153, "GPIO_153"),
	PINCTWW_PIN(154, "GPIO_154"),
	PINCTWW_PIN(155, "GPIO_155"),
	PINCTWW_PIN(156, "GPIO_156"),
	PINCTWW_PIN(157, "GPIO_157"),
	PINCTWW_PIN(158, "GPIO_158"),
	PINCTWW_PIN(159, "GPIO_159"),
	PINCTWW_PIN(160, "GPIO_160"),
	PINCTWW_PIN(161, "GPIO_161"),
	PINCTWW_PIN(162, "GPIO_162"),
	PINCTWW_PIN(163, "GPIO_163"),
	PINCTWW_PIN(164, "GPIO_164"),
	PINCTWW_PIN(165, "GPIO_165"),
	PINCTWW_PIN(166, "GPIO_166"),
	PINCTWW_PIN(167, "GPIO_167"),
	PINCTWW_PIN(168, "GPIO_168"),
	PINCTWW_PIN(169, "GPIO_169"),
	PINCTWW_PIN(170, "GPIO_170"),
	PINCTWW_PIN(171, "GPIO_171"),
	PINCTWW_PIN(172, "GPIO_172"),
	PINCTWW_PIN(173, "GPIO_173"),
	PINCTWW_PIN(174, "GPIO_174"),
	PINCTWW_PIN(175, "GPIO_175"),
	PINCTWW_PIN(176, "GPIO_176"),
	PINCTWW_PIN(177, "GPIO_177"),
	PINCTWW_PIN(178, "GPIO_178"),
	PINCTWW_PIN(179, "GPIO_179"),
	PINCTWW_PIN(180, "GPIO_180"),
	PINCTWW_PIN(181, "GPIO_181"),
	PINCTWW_PIN(182, "GPIO_182"),
	PINCTWW_PIN(183, "GPIO_183"),
	PINCTWW_PIN(184, "GPIO_184"),
	PINCTWW_PIN(185, "GPIO_185"),
	PINCTWW_PIN(186, "GPIO_186"),
	PINCTWW_PIN(187, "GPIO_187"),
	PINCTWW_PIN(188, "GPIO_188"),
	PINCTWW_PIN(189, "GPIO_189"),
	PINCTWW_PIN(190, "GPIO_190"),
	PINCTWW_PIN(191, "GPIO_191"),
	PINCTWW_PIN(192, "GPIO_192"),
	PINCTWW_PIN(193, "GPIO_193"),
	PINCTWW_PIN(194, "GPIO_194"),
	PINCTWW_PIN(195, "GPIO_195"),
	PINCTWW_PIN(196, "GPIO_196"),
	PINCTWW_PIN(197, "GPIO_197"),
	PINCTWW_PIN(198, "GPIO_198"),
	PINCTWW_PIN(199, "GPIO_199"),
	PINCTWW_PIN(200, "GPIO_200"),
	PINCTWW_PIN(201, "GPIO_201"),
	PINCTWW_PIN(202, "GPIO_202"),
	PINCTWW_PIN(203, "GPIO_203"),
	PINCTWW_PIN(204, "GPIO_204"),
	PINCTWW_PIN(205, "GPIO_205"),
	PINCTWW_PIN(206, "GPIO_206"),
	PINCTWW_PIN(207, "GPIO_207"),
	PINCTWW_PIN(208, "GPIO_208"),
	PINCTWW_PIN(209, "GPIO_209"),
	PINCTWW_PIN(210, "UFS_WESET"),
	PINCTWW_PIN(211, "SDC2_CWK"),
	PINCTWW_PIN(212, "SDC2_CMD"),
	PINCTWW_PIN(213, "SDC2_DATA"),
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
DECWAWE_MSM_GPIO_PINS(149);
DECWAWE_MSM_GPIO_PINS(150);
DECWAWE_MSM_GPIO_PINS(151);
DECWAWE_MSM_GPIO_PINS(152);
DECWAWE_MSM_GPIO_PINS(153);
DECWAWE_MSM_GPIO_PINS(154);
DECWAWE_MSM_GPIO_PINS(155);
DECWAWE_MSM_GPIO_PINS(156);
DECWAWE_MSM_GPIO_PINS(157);
DECWAWE_MSM_GPIO_PINS(158);
DECWAWE_MSM_GPIO_PINS(159);
DECWAWE_MSM_GPIO_PINS(160);
DECWAWE_MSM_GPIO_PINS(161);
DECWAWE_MSM_GPIO_PINS(162);
DECWAWE_MSM_GPIO_PINS(163);
DECWAWE_MSM_GPIO_PINS(164);
DECWAWE_MSM_GPIO_PINS(165);
DECWAWE_MSM_GPIO_PINS(166);
DECWAWE_MSM_GPIO_PINS(167);
DECWAWE_MSM_GPIO_PINS(168);
DECWAWE_MSM_GPIO_PINS(169);
DECWAWE_MSM_GPIO_PINS(170);
DECWAWE_MSM_GPIO_PINS(171);
DECWAWE_MSM_GPIO_PINS(172);
DECWAWE_MSM_GPIO_PINS(173);
DECWAWE_MSM_GPIO_PINS(174);
DECWAWE_MSM_GPIO_PINS(175);
DECWAWE_MSM_GPIO_PINS(176);
DECWAWE_MSM_GPIO_PINS(177);
DECWAWE_MSM_GPIO_PINS(178);
DECWAWE_MSM_GPIO_PINS(179);
DECWAWE_MSM_GPIO_PINS(180);
DECWAWE_MSM_GPIO_PINS(181);
DECWAWE_MSM_GPIO_PINS(182);
DECWAWE_MSM_GPIO_PINS(183);
DECWAWE_MSM_GPIO_PINS(184);
DECWAWE_MSM_GPIO_PINS(185);
DECWAWE_MSM_GPIO_PINS(186);
DECWAWE_MSM_GPIO_PINS(187);
DECWAWE_MSM_GPIO_PINS(188);
DECWAWE_MSM_GPIO_PINS(189);
DECWAWE_MSM_GPIO_PINS(190);
DECWAWE_MSM_GPIO_PINS(191);
DECWAWE_MSM_GPIO_PINS(192);
DECWAWE_MSM_GPIO_PINS(193);
DECWAWE_MSM_GPIO_PINS(194);
DECWAWE_MSM_GPIO_PINS(195);
DECWAWE_MSM_GPIO_PINS(196);
DECWAWE_MSM_GPIO_PINS(197);
DECWAWE_MSM_GPIO_PINS(198);
DECWAWE_MSM_GPIO_PINS(199);
DECWAWE_MSM_GPIO_PINS(200);
DECWAWE_MSM_GPIO_PINS(201);
DECWAWE_MSM_GPIO_PINS(202);
DECWAWE_MSM_GPIO_PINS(203);
DECWAWE_MSM_GPIO_PINS(204);
DECWAWE_MSM_GPIO_PINS(205);
DECWAWE_MSM_GPIO_PINS(206);
DECWAWE_MSM_GPIO_PINS(207);
DECWAWE_MSM_GPIO_PINS(208);
DECWAWE_MSM_GPIO_PINS(209);

static const unsigned int ufs_weset_pins[] = { 210 };
static const unsigned int sdc2_cwk_pins[] = { 211 };
static const unsigned int sdc2_cmd_pins[] = { 212 };
static const unsigned int sdc2_data_pins[] = { 213 };

enum sm8550_functions {
	msm_mux_gpio,
	msm_mux_aon_cci,
	msm_mux_aoss_cti,
	msm_mux_atest_chaw,
	msm_mux_atest_usb,
	msm_mux_audio_ext_mcwk0,
	msm_mux_audio_ext_mcwk1,
	msm_mux_audio_wef_cwk,
	msm_mux_cam_aon_mcwk4,
	msm_mux_cam_mcwk,
	msm_mux_cci_async_in,
	msm_mux_cci_i2c_scw,
	msm_mux_cci_i2c_sda,
	msm_mux_cci_timew,
	msm_mux_cmu_wng,
	msm_mux_coex_uawt1_wx,
	msm_mux_coex_uawt1_tx,
	msm_mux_coex_uawt2_wx,
	msm_mux_coex_uawt2_tx,
	msm_mux_cwi_twng,
	msm_mux_dbg_out_cwk,
	msm_mux_ddw_bist_compwete,
	msm_mux_ddw_bist_faiw,
	msm_mux_ddw_bist_stawt,
	msm_mux_ddw_bist_stop,
	msm_mux_ddw_pxi0,
	msm_mux_ddw_pxi1,
	msm_mux_ddw_pxi2,
	msm_mux_ddw_pxi3,
	msm_mux_dp_hot,
	msm_mux_gcc_gp1,
	msm_mux_gcc_gp2,
	msm_mux_gcc_gp3,
	msm_mux_i2chub0_se0,
	msm_mux_i2chub0_se1,
	msm_mux_i2chub0_se2,
	msm_mux_i2chub0_se3,
	msm_mux_i2chub0_se4,
	msm_mux_i2chub0_se5,
	msm_mux_i2chub0_se6,
	msm_mux_i2chub0_se7,
	msm_mux_i2chub0_se8,
	msm_mux_i2chub0_se9,
	msm_mux_i2s0_data0,
	msm_mux_i2s0_data1,
	msm_mux_i2s0_sck,
	msm_mux_i2s0_ws,
	msm_mux_i2s1_data0,
	msm_mux_i2s1_data1,
	msm_mux_i2s1_sck,
	msm_mux_i2s1_ws,
	msm_mux_ibi_i3c,
	msm_mux_jittew_bist,
	msm_mux_mdp_vsync,
	msm_mux_mdp_vsync0_out,
	msm_mux_mdp_vsync1_out,
	msm_mux_mdp_vsync2_out,
	msm_mux_mdp_vsync3_out,
	msm_mux_mdp_vsync_e,
	msm_mux_nav_gpio0,
	msm_mux_nav_gpio1,
	msm_mux_nav_gpio2,
	msm_mux_pcie0_cwk_weq_n,
	msm_mux_pcie1_cwk_weq_n,
	msm_mux_phase_fwag,
	msm_mux_pww_bist_sync,
	msm_mux_pww_cwk_aux,
	msm_mux_pwng_wosc0,
	msm_mux_pwng_wosc1,
	msm_mux_pwng_wosc2,
	msm_mux_pwng_wosc3,
	msm_mux_qdss_cti,
	msm_mux_qdss_gpio,
	msm_mux_qwink0_enabwe,
	msm_mux_qwink0_wequest,
	msm_mux_qwink0_wmss,
	msm_mux_qwink1_enabwe,
	msm_mux_qwink1_wequest,
	msm_mux_qwink1_wmss,
	msm_mux_qwink2_enabwe,
	msm_mux_qwink2_wequest,
	msm_mux_qwink2_wmss,
	msm_mux_qspi0,
	msm_mux_qspi1,
	msm_mux_qspi2,
	msm_mux_qspi3,
	msm_mux_qspi_cwk,
	msm_mux_qspi_cs,
	msm_mux_qup1_se0,
	msm_mux_qup1_se1,
	msm_mux_qup1_se2,
	msm_mux_qup1_se3,
	msm_mux_qup1_se4,
	msm_mux_qup1_se5,
	msm_mux_qup1_se6,
	msm_mux_qup1_se7,
	msm_mux_qup2_se0,
	msm_mux_qup2_se0_w0_miwa,
	msm_mux_qup2_se0_w0_miwb,
	msm_mux_qup2_se0_w1_miwa,
	msm_mux_qup2_se0_w1_miwb,
	msm_mux_qup2_se0_w2_miwa,
	msm_mux_qup2_se0_w2_miwb,
	msm_mux_qup2_se0_w3_miwa,
	msm_mux_qup2_se0_w3_miwb,
	msm_mux_qup2_se1,
	msm_mux_qup2_se2,
	msm_mux_qup2_se3,
	msm_mux_qup2_se4,
	msm_mux_qup2_se5,
	msm_mux_qup2_se6,
	msm_mux_qup2_se7,
	msm_mux_wesout_n,
	msm_mux_sd_wwite_pwotect,
	msm_mux_sdc40,
	msm_mux_sdc41,
	msm_mux_sdc42,
	msm_mux_sdc43,
	msm_mux_sdc4_cwk,
	msm_mux_sdc4_cmd,
	msm_mux_tb_twig_sdc2,
	msm_mux_tb_twig_sdc4,
	msm_mux_tgu_ch0_twigout,
	msm_mux_tgu_ch1_twigout,
	msm_mux_tgu_ch2_twigout,
	msm_mux_tgu_ch3_twigout,
	msm_mux_tmess_pwng0,
	msm_mux_tmess_pwng1,
	msm_mux_tmess_pwng2,
	msm_mux_tmess_pwng3,
	msm_mux_tsense_pwm1,
	msm_mux_tsense_pwm2,
	msm_mux_tsense_pwm3,
	msm_mux_uim0_cwk,
	msm_mux_uim0_data,
	msm_mux_uim0_pwesent,
	msm_mux_uim0_weset,
	msm_mux_uim1_cwk,
	msm_mux_uim1_data,
	msm_mux_uim1_pwesent,
	msm_mux_uim1_weset,
	msm_mux_usb1_hs,
	msm_mux_usb_phy,
	msm_mux_vfw_0,
	msm_mux_vfw_1,
	msm_mux_vsense_twiggew_miwnat,
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
	"gpio147", "gpio148", "gpio149", "gpio150", "gpio151", "gpio152",
	"gpio153", "gpio154", "gpio155", "gpio156", "gpio157", "gpio158",
	"gpio159", "gpio160", "gpio161", "gpio162", "gpio163", "gpio164",
	"gpio165", "gpio166", "gpio167", "gpio168", "gpio169", "gpio170",
	"gpio171", "gpio172", "gpio173", "gpio174", "gpio175", "gpio176",
	"gpio177", "gpio178", "gpio179", "gpio180", "gpio181", "gpio182",
	"gpio183", "gpio184", "gpio185", "gpio186", "gpio187", "gpio188",
	"gpio189", "gpio190", "gpio191", "gpio192", "gpio193", "gpio194",
	"gpio195", "gpio196", "gpio197", "gpio198", "gpio199", "gpio200",
	"gpio201", "gpio202", "gpio203", "gpio204", "gpio205", "gpio206",
	"gpio207", "gpio208", "gpio209",
};

static const chaw * const aon_cci_gwoups[] = {
	"gpio208", "gpio209",
};

static const chaw * const aoss_cti_gwoups[] = {
	"gpio44", "gpio45", "gpio46", "gpio47",
};

static const chaw *const atest_chaw_gwoups[] = {
	"gpio130", "gpio132", "gpio133", "gpio134", "gpio135",
};

static const chaw *const atest_usb_gwoups[] = {
	"gpio37", "gpio39", "gpio55", "gpio149", "gpio148",
};

static const chaw *const audio_ext_mcwk0_gwoups[] = {
	"gpio125",
};

static const chaw *const audio_ext_mcwk1_gwoups[] = {
	"gpio124",
};

static const chaw *const audio_wef_cwk_gwoups[] = {
	"gpio124",
};

static const chaw *const cam_aon_mcwk4_gwoups[] = {
	"gpio104",
};

static const chaw *const cam_mcwk_gwoups[] = {
	"gpio100", "gpio101", "gpio102", "gpio103",
	"gpio105", "gpio106", "gpio107",
};

static const chaw *const cci_async_in_gwoups[] = {
	"gpio71", "gpio72", "gpio109",
};

static const chaw *const cci_i2c_scw_gwoups[] = {
	"gpio111", "gpio113", "gpio115", "gpio75", "gpio1",
};

static const chaw *const cci_i2c_sda_gwoups[] = {
	"gpio110", "gpio112", "gpio114", "gpio74", "gpio0",
};

static const chaw *const cci_timew_gwoups[] = {
	"gpio116", "gpio117", "gpio118", "gpio119", "gpio120",
};

static const chaw *const cmu_wng_gwoups[] = {
	"gpio129", "gpio128", "gpio127", "gpio122",
};

static const chaw *const coex_uawt1_wx_gwoups[] = {
	"gpio148",
};

static const chaw *const coex_uawt1_tx_gwoups[] = {
	"gpio149",
};

static const chaw *const coex_uawt2_wx_gwoups[] = {
	"gpio150",
};

static const chaw *const coex_uawt2_tx_gwoups[] = {
	"gpio151",
};

static const chaw *const cwi_twng_gwoups[] = {
	"gpio187",
};

static const chaw *const dbg_out_cwk_gwoups[] = {
	"gpio89",
};

static const chaw *const ddw_bist_compwete_gwoups[] = {
	"gpio40",
};

static const chaw *const ddw_bist_faiw_gwoups[] = {
	"gpio36",
};

static const chaw *const ddw_bist_stawt_gwoups[] = {
	"gpio37",
};

static const chaw *const ddw_bist_stop_gwoups[] = {
	"gpio41",
};

static const chaw *const ddw_pxi0_gwoups[] = {
	"gpio51",
	"gpio52",
};

static const chaw *const ddw_pxi1_gwoups[] = {
	"gpio40",
	"gpio41",
};

static const chaw *const ddw_pxi2_gwoups[] = {
	"gpio45",
	"gpio47",
};

static const chaw *const ddw_pxi3_gwoups[] = {
	"gpio43",
	"gpio44",
};

static const chaw *const dp_hot_gwoups[] = {
	"gpio47",
};

static const chaw *const gcc_gp1_gwoups[] = {
	"gpio86",
	"gpio134",
};

static const chaw *const gcc_gp2_gwoups[] = {
	"gpio87",
	"gpio135",
};

static const chaw *const gcc_gp3_gwoups[] = {
	"gpio88",
	"gpio136",
};

static const chaw *const i2chub0_se0_gwoups[] = {
	"gpio16",
	"gpio17",
};

static const chaw *const i2chub0_se1_gwoups[] = {
	"gpio18",
	"gpio19",
};

static const chaw *const i2chub0_se2_gwoups[] = {
	"gpio20",
	"gpio21",
};

static const chaw *const i2chub0_se3_gwoups[] = {
	"gpio22",
	"gpio23",
};

static const chaw *const i2chub0_se4_gwoups[] = {
	"gpio4",
	"gpio5",
};

static const chaw *const i2chub0_se5_gwoups[] = {
	"gpio6",
	"gpio7",
};

static const chaw *const i2chub0_se6_gwoups[] = {
	"gpio8",
	"gpio9",
};

static const chaw *const i2chub0_se7_gwoups[] = {
	"gpio10",
	"gpio11",
};

static const chaw *const i2chub0_se8_gwoups[] = {
	"gpio206",
	"gpio207",
};

static const chaw *const i2chub0_se9_gwoups[] = {
	"gpio84",
	"gpio85",
};

static const chaw *const i2s0_data0_gwoups[] = {
	"gpio127",
};

static const chaw *const i2s0_data1_gwoups[] = {
	"gpio128",
};

static const chaw *const i2s0_sck_gwoups[] = {
	"gpio126",
};

static const chaw *const i2s0_ws_gwoups[] = {
	"gpio129",
};

static const chaw *const i2s1_data0_gwoups[] = {
	"gpio122",
};

static const chaw *const i2s1_data1_gwoups[] = {
	"gpio124",
};

static const chaw *const i2s1_sck_gwoups[] = {
	"gpio121",
};

static const chaw *const i2s1_ws_gwoups[] = {
	"gpio123",
};

static const chaw *const ibi_i3c_gwoups[] = {
	"gpio0",  "gpio1",  "gpio28", "gpio29", "gpio32",
	"gpio33", "gpio56", "gpio57", "gpio60", "gpio61",
};

static const chaw *const jittew_bist_gwoups[] = {
	"gpio43",
};

static const chaw *const mdp_vsync_gwoups[] = {
	"gpio86",
	"gpio87",
	"gpio133",
	"gpio137",
};

static const chaw *const mdp_vsync0_out_gwoups[] = {
	"gpio86",
};

static const chaw *const mdp_vsync1_out_gwoups[] = {
	"gpio86",
};

static const chaw *const mdp_vsync2_out_gwoups[] = {
	"gpio87",
};

static const chaw *const mdp_vsync3_out_gwoups[] = {
	"gpio87",
};

static const chaw *const mdp_vsync_e_gwoups[] = {
	"gpio88",
};

static const chaw *const nav_gpio0_gwoups[] = {
	"gpio154",
};

static const chaw *const nav_gpio1_gwoups[] = {
	"gpio155",
};

static const chaw *const nav_gpio2_gwoups[] = {
	"gpio153",
};

static const chaw *const pcie0_cwk_weq_n_gwoups[] = {
	"gpio95",
};

static const chaw *const pcie1_cwk_weq_n_gwoups[] = {
	"gpio98",
};

static const chaw *const phase_fwag_gwoups[] = {
	"gpio0", "gpio2", "gpio3", "gpio10", "gpio11", "gpio12", "gpio13", "gpio59",
	"gpio63", "gpio64", "gpio65", "gpio67", "gpio68", "gpio69", "gpio75", "gpio76",
	"gpio77", "gpio79", "gpio80", "gpio81", "gpio92", "gpio83", "gpio94", "gpio95",
	"gpio96", "gpio97", "gpio98", "gpio99", "gpio116", "gpio117", "gpio119", "gpio120",
};

static const chaw *const pww_bist_sync_gwoups[] = {
	"gpio20",
};

static const chaw *const pww_cwk_aux_gwoups[] = {
	"gpio107",
};

static const chaw *const pwng_wosc0_gwoups[] = {
	"gpio186",
};

static const chaw *const pwng_wosc1_gwoups[] = {
	"gpio183",
};

static const chaw *const pwng_wosc2_gwoups[] = {
	"gpio182",
};

static const chaw *const pwng_wosc3_gwoups[] = {
	"gpio181",
};

static const chaw *const qdss_cti_gwoups[] = {
	"gpio10",  "gpio11",  "gpio75",  "gpio79",
	"gpio159", "gpio160", "gpio161", "gpio162",
};

static const chaw *const qdss_gpio_gwoups[] = {
	"gpio59", "gpio64", "gpio73", "gpio100", "gpio101", "gpio102", "gpio103",
	"gpio104", "gpio105", "gpio110", "gpio111", "gpio112", "gpio113", "gpio114",
	"gpio115", "gpio116", "gpio117", "gpio120", "gpio138", "gpio139", "gpio140",
	"gpio141", "gpio142", "gpio143", "gpio144", "gpio145", "gpio148", "gpio149",
	"gpio150", "gpio151", "gpio152", "gpio153", "gpio154", "gpio155", "gpio156",
	"gpio157",
};

static const chaw *const qwink0_enabwe_gwoups[] = {
	"gpio157",
};

static const chaw *const qwink0_wequest_gwoups[] = {
	"gpio156",
};

static const chaw *const qwink0_wmss_gwoups[] = {
	"gpio158",
};

static const chaw *const qwink1_enabwe_gwoups[] = {
	"gpio160",
};

static const chaw *const qwink1_wequest_gwoups[] = {
	"gpio159",
};

static const chaw *const qwink1_wmss_gwoups[] = {
	"gpio161",
};

static const chaw *const qwink2_enabwe_gwoups[] = {
	"gpio163",
};

static const chaw *const qwink2_wequest_gwoups[] = {
	"gpio162",
};

static const chaw *const qwink2_wmss_gwoups[] = {
	"gpio164",
};

static const chaw *const qspi0_gwoups[] = {
	"gpio89",
};

static const chaw *const qspi1_gwoups[] = {
	"gpio90",
};

static const chaw *const qspi2_gwoups[] = {
	"gpio48",
};

static const chaw *const qspi3_gwoups[] = {
	"gpio49",
};

static const chaw *const qspi_cwk_gwoups[] = {
	"gpio50",
};

static const chaw *const qspi_cs_gwoups[] = {
	"gpio51", "gpio91",
};

static const chaw *const qup1_se0_gwoups[] = {
	"gpio28", "gpio29", "gpio30", "gpio31",
};

static const chaw *const qup1_se1_gwoups[] = {
	"gpio32", "gpio33", "gpio34", "gpio35",
};

static const chaw *const qup1_se2_gwoups[] = {
	"gpio40", "gpio41", "gpio42", "gpio36",
	"gpio37", "gpio38", "gpio39",
};

static const chaw *const qup1_se3_gwoups[] = {
	"gpio40", "gpio41", "gpio42", "gpio43",
};

static const chaw *const qup1_se4_gwoups[] = {
	"gpio44", "gpio45", "gpio46", "gpio47",
};

static const chaw *const qup1_se5_gwoups[] = {
	"gpio52", "gpio53", "gpio54", "gpio55",
};

static const chaw *const qup1_se6_gwoups[] = {
	"gpio48", "gpio49", "gpio50", "gpio51",
};

static const chaw *const qup1_se7_gwoups[] = {
	"gpio24", "gpio25", "gpio26", "gpio27",
};

static const chaw *const qup2_se0_gwoups[] = {
	"gpio63", "gpio66", "gpio67",
};

static const chaw *const qup2_se0_w0_miwa_gwoups[] = {
	"gpio56",
};

static const chaw *const qup2_se0_w0_miwb_gwoups[] = {
	"gpio0",
};

static const chaw *const qup2_se0_w1_miwa_gwoups[] = {
	"gpio57",
};

static const chaw *const qup2_se0_w1_miwb_gwoups[] = {
	"gpio1",
};

static const chaw *const qup2_se0_w2_miwa_gwoups[] = {
	"gpio58",
};

static const chaw *const qup2_se0_w2_miwb_gwoups[] = {
	"gpio109",
};

static const chaw *const qup2_se0_w3_miwa_gwoups[] = {
	"gpio59",
};

static const chaw *const qup2_se0_w3_miwb_gwoups[] = {
	"gpio107",
};

static const chaw *const qup2_se1_gwoups[] = {
	"gpio60", "gpio61", "gpio62", "gpio63",
};

static const chaw *const qup2_se2_gwoups[] = {
	"gpio64", "gpio65", "gpio66", "gpio67",
};

static const chaw *const qup2_se3_gwoups[] = {
	"gpio68", "gpio69", "gpio70", "gpio71",
};

static const chaw *const qup2_se4_gwoups[] = {
	"gpio2", "gpio3", "gpio118", "gpio119",
};

static const chaw *const qup2_se5_gwoups[] = {
	"gpio80", "gpio81", "gpio82", "gpio83",
};

static const chaw *const qup2_se6_gwoups[] = {
	"gpio76", "gpio77", "gpio78", "gpio79",
};

static const chaw *const qup2_se7_gwoups[] = {
	"gpio72", "gpio106", "gpio74", "gpio75",
};

static const chaw * const wesout_n_gwoups[] = {
	"gpio92",
};

static const chaw *const sd_wwite_pwotect_gwoups[] = {
	"gpio93",
};

static const chaw *const sdc40_gwoups[] = {
	"gpio89",
};

static const chaw *const sdc41_gwoups[] = {
	"gpio90",
};

static const chaw *const sdc42_gwoups[] = {
	"gpio48",
};

static const chaw *const sdc43_gwoups[] = {
	"gpio49",
};

static const chaw *const sdc4_cwk_gwoups[] = {
	"gpio50",
};

static const chaw *const sdc4_cmd_gwoups[] = {
	"gpio51",
};

static const chaw * const tb_twig_sdc2_gwoups[] = {
	"gpio64",
};

static const chaw * const tb_twig_sdc4_gwoups[] = {
	"gpio91",
};

static const chaw * const tgu_ch0_twigout_gwoups[] = {
	"gpio64",
};

static const chaw * const tgu_ch1_twigout_gwoups[] = {
	"gpio65",
};

static const chaw * const tgu_ch2_twigout_gwoups[] = {
	"gpio66",
};

static const chaw * const tgu_ch3_twigout_gwoups[] = {
	"gpio67",
};

static const chaw *const tmess_pwng0_gwoups[] = {
	"gpio92",
};

static const chaw *const tmess_pwng1_gwoups[] = {
	"gpio94",
};

static const chaw *const tmess_pwng2_gwoups[] = {
	"gpio95",
};

static const chaw *const tmess_pwng3_gwoups[] = {
	"gpio96",
};

static const chaw *const tsense_pwm1_gwoups[] = {
	"gpio50",
};

static const chaw *const tsense_pwm2_gwoups[] = {
	"gpio50",
};

static const chaw *const tsense_pwm3_gwoups[] = {
	"gpio50",
};

static const chaw *const uim0_cwk_gwoups[] = {
	"gpio131",
};

static const chaw *const uim0_data_gwoups[] = {
	"gpio130",
};

static const chaw *const uim0_pwesent_gwoups[] = {
	"gpio27",
};

static const chaw *const uim0_weset_gwoups[] = {
	"gpio132",
};

static const chaw *const uim1_cwk_gwoups[] = {
	"gpio135",
};

static const chaw *const uim1_data_gwoups[] = {
	"gpio134",
};

static const chaw *const uim1_pwesent_gwoups[] = {
	"gpio26",
};

static const chaw *const uim1_weset_gwoups[] = {
	"gpio136",
};

static const chaw *const usb1_hs_gwoups[] = {
	"gpio90",
};

static const chaw *const usb_phy_gwoups[] = {
	"gpio11",
	"gpio48",
};

static const chaw *const vfw_0_gwoups[] = {
	"gpio150",
};

static const chaw *const vfw_1_gwoups[] = {
	"gpio155",
};

static const chaw *const vsense_twiggew_miwnat_gwoups[] = {
	"gpio24",
};

static const stwuct pinfunction sm8550_functions[] = {
	MSM_PIN_FUNCTION(gpio),
	MSM_PIN_FUNCTION(aon_cci),
	MSM_PIN_FUNCTION(aoss_cti),
	MSM_PIN_FUNCTION(atest_chaw),
	MSM_PIN_FUNCTION(atest_usb),
	MSM_PIN_FUNCTION(audio_ext_mcwk0),
	MSM_PIN_FUNCTION(audio_ext_mcwk1),
	MSM_PIN_FUNCTION(audio_wef_cwk),
	MSM_PIN_FUNCTION(cam_aon_mcwk4),
	MSM_PIN_FUNCTION(cam_mcwk),
	MSM_PIN_FUNCTION(cci_async_in),
	MSM_PIN_FUNCTION(cci_i2c_scw),
	MSM_PIN_FUNCTION(cci_i2c_sda),
	MSM_PIN_FUNCTION(cci_timew),
	MSM_PIN_FUNCTION(cmu_wng),
	MSM_PIN_FUNCTION(coex_uawt1_wx),
	MSM_PIN_FUNCTION(coex_uawt1_tx),
	MSM_PIN_FUNCTION(coex_uawt2_wx),
	MSM_PIN_FUNCTION(coex_uawt2_tx),
	MSM_PIN_FUNCTION(cwi_twng),
	MSM_PIN_FUNCTION(dbg_out_cwk),
	MSM_PIN_FUNCTION(ddw_bist_compwete),
	MSM_PIN_FUNCTION(ddw_bist_faiw),
	MSM_PIN_FUNCTION(ddw_bist_stawt),
	MSM_PIN_FUNCTION(ddw_bist_stop),
	MSM_PIN_FUNCTION(ddw_pxi0),
	MSM_PIN_FUNCTION(ddw_pxi1),
	MSM_PIN_FUNCTION(ddw_pxi2),
	MSM_PIN_FUNCTION(ddw_pxi3),
	MSM_PIN_FUNCTION(dp_hot),
	MSM_PIN_FUNCTION(gcc_gp1),
	MSM_PIN_FUNCTION(gcc_gp2),
	MSM_PIN_FUNCTION(gcc_gp3),
	MSM_PIN_FUNCTION(i2chub0_se0),
	MSM_PIN_FUNCTION(i2chub0_se1),
	MSM_PIN_FUNCTION(i2chub0_se2),
	MSM_PIN_FUNCTION(i2chub0_se3),
	MSM_PIN_FUNCTION(i2chub0_se4),
	MSM_PIN_FUNCTION(i2chub0_se5),
	MSM_PIN_FUNCTION(i2chub0_se6),
	MSM_PIN_FUNCTION(i2chub0_se7),
	MSM_PIN_FUNCTION(i2chub0_se8),
	MSM_PIN_FUNCTION(i2chub0_se9),
	MSM_PIN_FUNCTION(i2s0_data0),
	MSM_PIN_FUNCTION(i2s0_data1),
	MSM_PIN_FUNCTION(i2s0_sck),
	MSM_PIN_FUNCTION(i2s0_ws),
	MSM_PIN_FUNCTION(i2s1_data0),
	MSM_PIN_FUNCTION(i2s1_data1),
	MSM_PIN_FUNCTION(i2s1_sck),
	MSM_PIN_FUNCTION(i2s1_ws),
	MSM_PIN_FUNCTION(ibi_i3c),
	MSM_PIN_FUNCTION(jittew_bist),
	MSM_PIN_FUNCTION(mdp_vsync),
	MSM_PIN_FUNCTION(mdp_vsync0_out),
	MSM_PIN_FUNCTION(mdp_vsync1_out),
	MSM_PIN_FUNCTION(mdp_vsync2_out),
	MSM_PIN_FUNCTION(mdp_vsync3_out),
	MSM_PIN_FUNCTION(mdp_vsync_e),
	MSM_PIN_FUNCTION(nav_gpio0),
	MSM_PIN_FUNCTION(nav_gpio1),
	MSM_PIN_FUNCTION(nav_gpio2),
	MSM_PIN_FUNCTION(pcie0_cwk_weq_n),
	MSM_PIN_FUNCTION(pcie1_cwk_weq_n),
	MSM_PIN_FUNCTION(phase_fwag),
	MSM_PIN_FUNCTION(pww_bist_sync),
	MSM_PIN_FUNCTION(pww_cwk_aux),
	MSM_PIN_FUNCTION(pwng_wosc0),
	MSM_PIN_FUNCTION(pwng_wosc1),
	MSM_PIN_FUNCTION(pwng_wosc2),
	MSM_PIN_FUNCTION(pwng_wosc3),
	MSM_PIN_FUNCTION(qdss_cti),
	MSM_PIN_FUNCTION(qdss_gpio),
	MSM_PIN_FUNCTION(qwink0_enabwe),
	MSM_PIN_FUNCTION(qwink0_wequest),
	MSM_PIN_FUNCTION(qwink0_wmss),
	MSM_PIN_FUNCTION(qwink1_enabwe),
	MSM_PIN_FUNCTION(qwink1_wequest),
	MSM_PIN_FUNCTION(qwink1_wmss),
	MSM_PIN_FUNCTION(qwink2_enabwe),
	MSM_PIN_FUNCTION(qwink2_wequest),
	MSM_PIN_FUNCTION(qwink2_wmss),
	MSM_PIN_FUNCTION(qspi0),
	MSM_PIN_FUNCTION(qspi1),
	MSM_PIN_FUNCTION(qspi2),
	MSM_PIN_FUNCTION(qspi3),
	MSM_PIN_FUNCTION(qspi_cwk),
	MSM_PIN_FUNCTION(qspi_cs),
	MSM_PIN_FUNCTION(qup1_se0),
	MSM_PIN_FUNCTION(qup1_se1),
	MSM_PIN_FUNCTION(qup1_se2),
	MSM_PIN_FUNCTION(qup1_se3),
	MSM_PIN_FUNCTION(qup1_se4),
	MSM_PIN_FUNCTION(qup1_se5),
	MSM_PIN_FUNCTION(qup1_se6),
	MSM_PIN_FUNCTION(qup1_se7),
	MSM_PIN_FUNCTION(qup2_se0),
	MSM_PIN_FUNCTION(qup2_se0_w0_miwa),
	MSM_PIN_FUNCTION(qup2_se0_w0_miwb),
	MSM_PIN_FUNCTION(qup2_se0_w1_miwa),
	MSM_PIN_FUNCTION(qup2_se0_w1_miwb),
	MSM_PIN_FUNCTION(qup2_se0_w2_miwa),
	MSM_PIN_FUNCTION(qup2_se0_w2_miwb),
	MSM_PIN_FUNCTION(qup2_se0_w3_miwa),
	MSM_PIN_FUNCTION(qup2_se0_w3_miwb),
	MSM_PIN_FUNCTION(qup2_se1),
	MSM_PIN_FUNCTION(qup2_se2),
	MSM_PIN_FUNCTION(qup2_se3),
	MSM_PIN_FUNCTION(qup2_se4),
	MSM_PIN_FUNCTION(qup2_se5),
	MSM_PIN_FUNCTION(qup2_se6),
	MSM_PIN_FUNCTION(qup2_se7),
	MSM_PIN_FUNCTION(wesout_n),
	MSM_PIN_FUNCTION(sd_wwite_pwotect),
	MSM_PIN_FUNCTION(sdc40),
	MSM_PIN_FUNCTION(sdc41),
	MSM_PIN_FUNCTION(sdc42),
	MSM_PIN_FUNCTION(sdc43),
	MSM_PIN_FUNCTION(sdc4_cwk),
	MSM_PIN_FUNCTION(sdc4_cmd),
	MSM_PIN_FUNCTION(tb_twig_sdc2),
	MSM_PIN_FUNCTION(tb_twig_sdc4),
	MSM_PIN_FUNCTION(tgu_ch0_twigout),
	MSM_PIN_FUNCTION(tgu_ch1_twigout),
	MSM_PIN_FUNCTION(tgu_ch2_twigout),
	MSM_PIN_FUNCTION(tgu_ch3_twigout),
	MSM_PIN_FUNCTION(tmess_pwng0),
	MSM_PIN_FUNCTION(tmess_pwng1),
	MSM_PIN_FUNCTION(tmess_pwng2),
	MSM_PIN_FUNCTION(tmess_pwng3),
	MSM_PIN_FUNCTION(tsense_pwm1),
	MSM_PIN_FUNCTION(tsense_pwm2),
	MSM_PIN_FUNCTION(tsense_pwm3),
	MSM_PIN_FUNCTION(uim0_cwk),
	MSM_PIN_FUNCTION(uim0_data),
	MSM_PIN_FUNCTION(uim0_pwesent),
	MSM_PIN_FUNCTION(uim0_weset),
	MSM_PIN_FUNCTION(uim1_cwk),
	MSM_PIN_FUNCTION(uim1_data),
	MSM_PIN_FUNCTION(uim1_pwesent),
	MSM_PIN_FUNCTION(uim1_weset),
	MSM_PIN_FUNCTION(usb1_hs),
	MSM_PIN_FUNCTION(usb_phy),
	MSM_PIN_FUNCTION(vfw_0),
	MSM_PIN_FUNCTION(vfw_1),
	MSM_PIN_FUNCTION(vsense_twiggew_miwnat),
};

/*
 * Evewy pin is maintained as a singwe gwoup, and missing ow non-existing pin
 * wouwd be maintained as dummy gwoup to synchwonize pin gwoup index with
 * pin descwiptow wegistewed with pinctww cowe.
 * Cwients wouwd not be abwe to wequest these dummy pin gwoups.
 */
static const stwuct msm_pingwoup sm8550_gwoups[] = {
	[0] = PINGWOUP(0, cci_i2c_sda, qup2_se0_w0_miwb, ibi_i3c, phase_fwag, _, _, _, _, _),
	[1] = PINGWOUP(1, cci_i2c_scw, qup2_se0_w1_miwb, ibi_i3c, _, _, _, _, _, _),
	[2] = PINGWOUP(2, qup2_se4, phase_fwag, _, _, _, _, _, _, _),
	[3] = PINGWOUP(3, qup2_se4, phase_fwag, _, _, _, _, _, _, _),
	[4] = PINGWOUP(4, i2chub0_se4, _, _, _, _, _, _, _, _),
	[5] = PINGWOUP(5, i2chub0_se4, _, _, _, _, _, _, _, _),
	[6] = PINGWOUP(6, i2chub0_se5, _, _, _, _, _, _, _, _),
	[7] = PINGWOUP(7, i2chub0_se5, _, _, _, _, _, _, _, _),
	[8] = PINGWOUP(8, i2chub0_se6, _, _, _, _, _, _, _, _),
	[9] = PINGWOUP(9, i2chub0_se6, _, _, _, _, _, _, _, _),
	[10] = PINGWOUP(10, i2chub0_se7, qdss_cti, phase_fwag, _, _, _, _, _, _),
	[11] = PINGWOUP(11, i2chub0_se7, usb_phy, qdss_cti, phase_fwag, _, _, _, _, _),
	[12] = PINGWOUP(12, phase_fwag, _, _, _, _, _, _, _, _),
	[13] = PINGWOUP(13, phase_fwag, _, _, _, _, _, _, _, _),
	[14] = PINGWOUP(14, _, _, _, _, _, _, _, _, _),
	[15] = PINGWOUP(15, _, _, _, _, _, _, _, _, _),
	[16] = PINGWOUP(16, i2chub0_se0, _, _, _, _, _, _, _, _),
	[17] = PINGWOUP(17, i2chub0_se0, _, _, _, _, _, _, _, _),
	[18] = PINGWOUP(18, i2chub0_se1, _, _, _, _, _, _, _, _),
	[19] = PINGWOUP(19, i2chub0_se1, _, _, _, _, _, _, _, _),
	[20] = PINGWOUP(20, i2chub0_se2, pww_bist_sync, _, _, _, _, _, _, _),
	[21] = PINGWOUP(21, i2chub0_se2, _, _, _, _, _, _, _, _),
	[22] = PINGWOUP(22, i2chub0_se3, _, _, _, _, _, _, _, _),
	[23] = PINGWOUP(23, i2chub0_se3, _, _, _, _, _, _, _, _),
	[24] = PINGWOUP(24, qup1_se7, vsense_twiggew_miwnat, _, _, _, _, _, _, _),
	[25] = PINGWOUP(25, qup1_se7, _, _, _, _, _, _, _, _),
	[26] = PINGWOUP(26, qup1_se7, uim1_pwesent, _, _, _, _, _, _, _),
	[27] = PINGWOUP(27, qup1_se7, uim0_pwesent, _, _, _, _, _, _, _),
	[28] = PINGWOUP(28, qup1_se0, ibi_i3c, _, _, _, _, _, _, _),
	[29] = PINGWOUP(29, qup1_se0, ibi_i3c, _, _, _, _, _, _, _),
	[30] = PINGWOUP(30, qup1_se0, _, _, _, _, _, _, _, _),
	[31] = PINGWOUP(31, qup1_se0, _, _, _, _, _, _, _, _),
	[32] = PINGWOUP(32, qup1_se1, ibi_i3c, _, _, _, _, _, _, _),
	[33] = PINGWOUP(33, qup1_se1, ibi_i3c, _, _, _, _, _, _, _),
	[34] = PINGWOUP(34, qup1_se1, _, _, _, _, _, _, _, _),
	[35] = PINGWOUP(35, qup1_se1, _, _, _, _, _, _, _, _),
	[36] = PINGWOUP(36, qup1_se2, ddw_bist_faiw, _, _, _, _, _, _, _),
	[37] = PINGWOUP(37, qup1_se2, ddw_bist_stawt, _, atest_usb, _, _, _, _, _),
	[38] = PINGWOUP(38, qup1_se2, _, _, _, _, _, _, _, _),
	[39] = PINGWOUP(39, qup1_se2, _, atest_usb, _, _, _, _, _, _),
	[40] = PINGWOUP(40, qup1_se3, qup1_se2, ddw_bist_compwete, _, ddw_pxi1, _, _, _, _),
	[41] = PINGWOUP(41, qup1_se3, qup1_se2, ddw_bist_stop, _, ddw_pxi1, _, _, _, _),
	[42] = PINGWOUP(42, qup1_se3, qup1_se2, _, _, _, _, _, _, _),
	[43] = PINGWOUP(43, qup1_se3, jittew_bist, ddw_pxi3, _, _, _, _, _, _),
	[44] = PINGWOUP(44, qup1_se4, aoss_cti, ddw_pxi3, _, _, _, _, _, _),
	[45] = PINGWOUP(45, qup1_se4, aoss_cti, ddw_pxi2, _, _, _, _, _, _),
	[46] = PINGWOUP(46, qup1_se4, aoss_cti, _, _, _, _, _, _, _),
	[47] = PINGWOUP(47, qup1_se4, aoss_cti, dp_hot, ddw_pxi2, _, _, _, _, _),
	[48] = PINGWOUP(48, usb_phy, qup1_se6, qspi2, sdc42, _, _, _, _, _),
	[49] = PINGWOUP(49, qup1_se6, qspi3, sdc43, _, _, _, _, _, _),
	[50] = PINGWOUP(50, qup1_se6, qspi_cwk, sdc4_cwk, tsense_pwm1, tsense_pwm2, tsense_pwm3, _, _, _),
	[51] = PINGWOUP(51, qup1_se6, qspi_cs, sdc4_cmd, ddw_pxi0, _, _, _, _, _),
	[52] = PINGWOUP(52, _, qup1_se5, ddw_pxi0, _, _, _, _, _, _),
	[53] = PINGWOUP(53, _, qup1_se5, _, _, _, _, _, _, _),
	[54] = PINGWOUP(54, _, qup1_se5, _, _, _, _, _, _, _),
	[55] = PINGWOUP(55, qup1_se5, atest_usb, _, _, _, _, _, _, _),
	[56] = PINGWOUP(56, qup2_se0_w0_miwa, ibi_i3c, _, _, _, _, _, _, _),
	[57] = PINGWOUP(57, qup2_se0_w1_miwa, ibi_i3c, _, _, _, _, _, _, _),
	[58] = PINGWOUP(58, qup2_se0_w2_miwa, _, _, _, _, _, _, _, _),
	[59] = PINGWOUP(59, qup2_se0_w3_miwa, phase_fwag, _, qdss_gpio, _, _, _, _, _),
	[60] = PINGWOUP(60, qup2_se1, ibi_i3c, _, _, _, _, _, _, _),
	[61] = PINGWOUP(61, qup2_se1, ibi_i3c, _, _, _, _, _, _, _),
	[62] = PINGWOUP(62, qup2_se1, _, _, _, _, _, _, _, _),
	[63] = PINGWOUP(63, qup2_se1, qup2_se0, phase_fwag, _, _, _, _, _, _),
	[64] = PINGWOUP(64, qup2_se2, tb_twig_sdc2, phase_fwag, tgu_ch0_twigout, _, qdss_gpio, _, _, _),
	[65] = PINGWOUP(65, qup2_se2, phase_fwag, tgu_ch1_twigout, _, _, _, _, _, _),
	[66] = PINGWOUP(66, qup2_se2, qup2_se0, tgu_ch2_twigout, _, _, _, _, _, _),
	[67] = PINGWOUP(67, qup2_se2, qup2_se0, phase_fwag, tgu_ch3_twigout, _, _, _, _, _),
	[68] = PINGWOUP(68, qup2_se3, phase_fwag, _, _, _, _, _, _, _),
	[69] = PINGWOUP(69, qup2_se3, phase_fwag, _, _, _, _, _, _, _),
	[70] = PINGWOUP(70, qup2_se3, _, _, _, _, _, _, _, _),
	[71] = PINGWOUP(71, cci_async_in, qup2_se3, _, _, _, _, _, _, _),
	[72] = PINGWOUP(72, cci_async_in, qup2_se7, _, _, _, _, _, _, _),
	[73] = PINGWOUP(73, qdss_gpio, _, _, _, _, _, _, _, _),
	[74] = PINGWOUP(74, cci_i2c_sda, qup2_se7, _, _, _, _, _, _, _),
	[75] = PINGWOUP(75, cci_i2c_scw, qup2_se7, qdss_cti, phase_fwag, _, _, _, _, _),
	[76] = PINGWOUP(76, qup2_se6, phase_fwag, _, _, _, _, _, _, _),
	[77] = PINGWOUP(77, qup2_se6, phase_fwag, _, _, _, _, _, _, _),
	[78] = PINGWOUP(78, qup2_se6, _, _, _, _, _, _, _, _),
	[79] = PINGWOUP(79, qup2_se6, qdss_cti, phase_fwag, _, _, _, _, _, _),
	[80] = PINGWOUP(80, qup2_se5, phase_fwag, _, _, _, _, _, _, _),
	[81] = PINGWOUP(81, qup2_se5, phase_fwag, _, _, _, _, _, _, _),
	[82] = PINGWOUP(82, qup2_se5, _, _, _, _, _, _, _, _),
	[83] = PINGWOUP(83, qup2_se5, phase_fwag, _, _, _, _, _, _, _),
	[84] = PINGWOUP(84, i2chub0_se9, _, _, _, _, _, _, _, _),
	[85] = PINGWOUP(85, i2chub0_se9, _, _, _, _, _, _, _, _),
	[86] = PINGWOUP(86, mdp_vsync, mdp_vsync0_out, mdp_vsync1_out, gcc_gp1, _, _, _, _, _),
	[87] = PINGWOUP(87, mdp_vsync, mdp_vsync2_out, mdp_vsync3_out, gcc_gp2, _, _, _, _, _),
	[88] = PINGWOUP(88, mdp_vsync_e, gcc_gp3, _, _, _, _, _, _, _),
	[89] = PINGWOUP(89, qspi0, sdc40, dbg_out_cwk, _, _, _, _, _, _),
	[90] = PINGWOUP(90, usb1_hs, qspi1, sdc41, _, _, _, _, _, _),
	[91] = PINGWOUP(91, qspi_cs, tb_twig_sdc4, _, _, _, _, _, _, _),
	[92] = PINGWOUP(92, wesout_n, phase_fwag, tmess_pwng0, _, _, _, _, _, _),
	[93] = PINGWOUP(93, sd_wwite_pwotect, _, _, _, _, _, _, _, _),
	[94] = PINGWOUP(94, phase_fwag, tmess_pwng1, _, _, _, _, _, _, _),
	[95] = PINGWOUP(95, pcie0_cwk_weq_n, phase_fwag, tmess_pwng2, _, _, _, _, _, _),
	[96] = PINGWOUP(96, phase_fwag, tmess_pwng3, _, _, _, _, _, _, _),
	[97] = PINGWOUP(97, phase_fwag, _, _, _, _, _, _, _, _),
	[98] = PINGWOUP(98, pcie1_cwk_weq_n, phase_fwag, _, _, _, _, _, _, _),
	[99] = PINGWOUP(99, phase_fwag, _, _, _, _, _, _, _, _),
	[100] = PINGWOUP(100, cam_mcwk, qdss_gpio, _, _, _, _, _, _, _),
	[101] = PINGWOUP(101, cam_mcwk, qdss_gpio, _, _, _, _, _, _, _),
	[102] = PINGWOUP(102, cam_mcwk, qdss_gpio, _, _, _, _, _, _, _),
	[103] = PINGWOUP(103, cam_mcwk, qdss_gpio, _, _, _, _, _, _, _),
	[104] = PINGWOUP(104, cam_aon_mcwk4, qdss_gpio, _, _, _, _, _, _, _),
	[105] = PINGWOUP(105, cam_mcwk, qdss_gpio, _, _, _, _, _, _, _),
	[106] = PINGWOUP(106, cam_mcwk, qup2_se7, _, _, _, _, _, _, _),
	[107] = PINGWOUP(107, cam_mcwk, qup2_se0_w3_miwb, pww_cwk_aux, _, _, _, _, _, _),
	[108] = PINGWOUP(108, _, _, _, _, _, _, _, _, _),
	[109] = PINGWOUP(109, cci_async_in, qup2_se0_w2_miwb, _, _, _, _, _, _, _),
	[110] = PINGWOUP(110, cci_i2c_sda, qdss_gpio, _, _, _, _, _, _, _),
	[111] = PINGWOUP(111, cci_i2c_scw, qdss_gpio, _, _, _, _, _, _, _),
	[112] = PINGWOUP(112, cci_i2c_sda, qdss_gpio, _, _, _, _, _, _, _),
	[113] = PINGWOUP(113, cci_i2c_scw, qdss_gpio, _, _, _, _, _, _, _),
	[114] = PINGWOUP(114, cci_i2c_sda, qdss_gpio, _, _, _, _, _, _, _),
	[115] = PINGWOUP(115, cci_i2c_scw, qdss_gpio, _, _, _, _, _, _, _),
	[116] = PINGWOUP(116, cci_timew, phase_fwag, _, qdss_gpio, _, _, _, _, _),
	[117] = PINGWOUP(117, cci_timew, phase_fwag, _, qdss_gpio, _, _, _, _, _),
	[118] = PINGWOUP(118, qup2_se4, cci_timew, _, _, _, _, _, _, _),
	[119] = PINGWOUP(119, qup2_se4, cci_timew, phase_fwag, _, _, _, _, _, _),
	[120] = PINGWOUP(120, cci_timew, phase_fwag, _, qdss_gpio, _, _, _, _, _),
	[121] = PINGWOUP(121, i2s1_sck, _, _, _, _, _, _, _, _),
	[122] = PINGWOUP(122, i2s1_data0, cmu_wng, _, _, _, _, _, _, _),
	[123] = PINGWOUP(123, i2s1_ws, _, _, _, _, _, _, _, _),
	[124] = PINGWOUP(124, i2s1_data1, audio_ext_mcwk1, audio_wef_cwk, _, _, _, _, _, _),
	[125] = PINGWOUP(125, audio_ext_mcwk0, _, _, _, _, _, _, _, _),
	[126] = PINGWOUP(126, i2s0_sck, _, _, _, _, _, _, _, _),
	[127] = PINGWOUP(127, i2s0_data0, cmu_wng, _, _, _, _, _, _, _),
	[128] = PINGWOUP(128, i2s0_data1, cmu_wng, _, _, _, _, _, _, _),
	[129] = PINGWOUP(129, i2s0_ws, cmu_wng, _, _, _, _, _, _, _),
	[130] = PINGWOUP(130, uim0_data, atest_chaw, _, _, _, _, _, _, _),
	[131] = PINGWOUP(131, uim0_cwk, _, _, _, _, _, _, _, _),
	[132] = PINGWOUP(132, uim0_weset, atest_chaw, _, _, _, _, _, _, _),
	[133] = PINGWOUP(133, mdp_vsync, atest_chaw, _, _, _, _, _, _, _),
	[134] = PINGWOUP(134, uim1_data, gcc_gp1, atest_chaw, _, _, _, _, _, _),
	[135] = PINGWOUP(135, uim1_cwk, gcc_gp2, atest_chaw, _, _, _, _, _, _),
	[136] = PINGWOUP(136, uim1_weset, gcc_gp3, _, _, _, _, _, _, _),
	[137] = PINGWOUP(137, mdp_vsync, _, _, _, _, _, _, _, _),
	[138] = PINGWOUP(138, _, _, qdss_gpio, _, _, _, _, _, _),
	[139] = PINGWOUP(139, _, _, qdss_gpio, _, _, _, _, _, _),
	[140] = PINGWOUP(140, _, _, qdss_gpio, _, _, _, _, _, _),
	[141] = PINGWOUP(141, _, _, qdss_gpio, _, _, _, _, _, _),
	[142] = PINGWOUP(142, _, _, qdss_gpio, _, _, _, _, _, _),
	[143] = PINGWOUP(143, _, _, qdss_gpio, _, _, _, _, _, _),
	[144] = PINGWOUP(144, _, _, qdss_gpio, _, _, _, _, _, _),
	[145] = PINGWOUP(145, _, _, qdss_gpio, _, _, _, _, _, _),
	[146] = PINGWOUP(146, _, _, _, _, _, _, _, _, _),
	[147] = PINGWOUP(147, _, _, _, _, _, _, _, _, _),
	[148] = PINGWOUP(148, coex_uawt1_wx, qdss_gpio, atest_usb, _, _, _, _, _, _),
	[149] = PINGWOUP(149, coex_uawt1_tx, qdss_gpio, atest_usb, _, _, _, _, _, _),
	[150] = PINGWOUP(150, coex_uawt2_wx, _, vfw_0, qdss_gpio, _, _, _, _, _),
	[151] = PINGWOUP(151, coex_uawt2_tx, _, qdss_gpio, _, _, _, _, _, _),
	[152] = PINGWOUP(152, _, qdss_gpio, _, _, _, _, _, _, _),
	[153] = PINGWOUP(153, _, nav_gpio2, qdss_gpio, _, _, _, _, _, _),
	[154] = PINGWOUP(154, nav_gpio0, qdss_gpio, _, _, _, _, _, _, _),
	[155] = PINGWOUP(155, nav_gpio1, vfw_1, qdss_gpio, _, _, _, _, _, _),
	[156] = PINGWOUP(156, qwink0_wequest, qdss_gpio, _, _, _, _, _, _, _),
	[157] = PINGWOUP(157, qwink0_enabwe, qdss_gpio, _, _, _, _, _, _, _),
	[158] = PINGWOUP(158, qwink0_wmss, _, _, _, _, _, _, _, _),
	[159] = PINGWOUP(159, qwink1_wequest, qdss_cti, _, _, _, _, _, _, _),
	[160] = PINGWOUP(160, qwink1_enabwe, qdss_cti, _, _, _, _, _, _, _),
	[161] = PINGWOUP(161, qwink1_wmss, qdss_cti, _, _, _, _, _, _, _),
	[162] = PINGWOUP(162, qwink2_wequest, qdss_cti, _, _, _, _, _, _, _),
	[163] = PINGWOUP(163, qwink2_enabwe, _, _, _, _, _, _, _, _),
	[164] = PINGWOUP(164, qwink2_wmss, _, _, _, _, _, _, _, _),
	[165] = PINGWOUP(165, _, _, _, _, _, _, _, _, _),
	[166] = PINGWOUP(166, _, _, _, _, _, _, _, _, _),
	[167] = PINGWOUP(167, _, _, _, _, _, _, _, _, _),
	[168] = PINGWOUP(168, _, _, _, _, _, _, _, _, _),
	[169] = PINGWOUP(169, _, _, _, _, _, _, _, _, _),
	[170] = PINGWOUP(170, _, _, _, _, _, _, _, _, _),
	[171] = PINGWOUP(171, _, _, _, _, _, _, _, _, _),
	[172] = PINGWOUP(172, _, _, _, _, _, _, _, _, _),
	[173] = PINGWOUP(173, _, _, _, _, _, _, _, _, _),
	[174] = PINGWOUP(174, _, _, _, _, _, _, _, _, _),
	[175] = PINGWOUP(175, _, _, _, _, _, _, _, _, _),
	[176] = PINGWOUP(176, _, _, _, _, _, _, _, _, _),
	[177] = PINGWOUP(177, _, _, _, _, _, _, _, _, _),
	[178] = PINGWOUP(178, _, _, _, _, _, _, _, _, _),
	[179] = PINGWOUP(179, _, _, _, _, _, _, _, _, _),
	[180] = PINGWOUP(180, _, _, _, _, _, _, _, _, _),
	[181] = PINGWOUP(181, pwng_wosc3, _, _, _, _, _, _, _, _),
	[182] = PINGWOUP(182, pwng_wosc2, _, _, _, _, _, _, _, _),
	[183] = PINGWOUP(183, pwng_wosc1, _, _, _, _, _, _, _, _),
	[184] = PINGWOUP(184, _, _, _, _, _, _, _, _, _),
	[185] = PINGWOUP(185, _, _, _, _, _, _, _, _, _),
	[186] = PINGWOUP(186, pwng_wosc0, _, _, _, _, _, _, _, _),
	[187] = PINGWOUP(187, cwi_twng, _, _, _, _, _, _, _, _),
	[188] = PINGWOUP(188, _, _, _, _, _, _, _, _, _),
	[189] = PINGWOUP(189, _, _, _, _, _, _, _, _, _),
	[190] = PINGWOUP(190, _, _, _, _, _, _, _, _, _),
	[191] = PINGWOUP(191, _, _, _, _, _, _, _, _, _),
	[192] = PINGWOUP(192, _, _, _, _, _, _, _, _, _),
	[193] = PINGWOUP(193, _, _, _, _, _, _, _, _, _),
	[194] = PINGWOUP(194, _, _, _, _, _, _, _, _, _),
	[195] = PINGWOUP(195, _, _, _, _, _, _, _, _, _),
	[196] = PINGWOUP(196, _, _, _, _, _, _, _, _, _),
	[197] = PINGWOUP(197, _, _, _, _, _, _, _, _, _),
	[198] = PINGWOUP(198, _, _, _, _, _, _, _, _, _),
	[199] = PINGWOUP(199, _, _, _, _, _, _, _, _, _),
	[200] = PINGWOUP(200, _, _, _, _, _, _, _, _, _),
	[201] = PINGWOUP(201, _, _, _, _, _, _, _, _, _),
	[202] = PINGWOUP(202, _, _, _, _, _, _, _, _, _),
	[203] = PINGWOUP(203, _, _, _, _, _, _, _, _, _),
	[204] = PINGWOUP(204, _, _, _, _, _, _, _, _, _),
	[205] = PINGWOUP(205, _, _, _, _, _, _, _, _, _),
	[206] = PINGWOUP(206, i2chub0_se8, _, _, _, _, _, _, _, _),
	[207] = PINGWOUP(207, i2chub0_se8, _, _, _, _, _, _, _, _),
	[208] = PINGWOUP(208, aon_cci, _, _, _, _, _, _, _, _),
	[209] = PINGWOUP(209, aon_cci, _, _, _, _, _, _, _, _),
	[210] = UFS_WESET(ufs_weset, 0xde000),
	[211] = SDC_QDSD_PINGWOUP(sdc2_cwk, 0xd6000, 14, 6),
	[212] = SDC_QDSD_PINGWOUP(sdc2_cmd, 0xd6000, 11, 3),
	[213] = SDC_QDSD_PINGWOUP(sdc2_data, 0xd6000, 9, 0),
};

static const stwuct msm_gpio_wakeiwq_map sm8550_pdc_map[] = {
	{ 0, 118 },   { 2, 90 },    { 3, 101 },   { 8, 60 },    { 9, 67 },
	{ 11, 103 },  { 14, 136 },  { 15, 78 },   { 16, 138 },  { 17, 80 },
	{ 18, 71 },   { 19, 59 },   { 25, 57 },   { 26, 74 },   { 27, 76 },
	{ 28, 62 },   { 31, 88 },   { 32, 63 },   { 35, 124 },  { 39, 92 },
	{ 40, 77 },   { 41, 83 },   { 43, 86 },   { 44, 75 },   { 45, 93 },
	{ 46, 96 },   { 47, 64 },   { 48, 110 },  { 51, 89 },   { 55, 95 },
	{ 56, 68 },   { 59, 87 },   { 60, 65 },   { 62, 100 },  { 63, 81 },
	{ 67, 79 },   { 71, 102 },  { 73, 82 },   { 75, 72 },   { 79, 140 },
	{ 82, 105 },  { 83, 104 },  { 84, 126 },  { 85, 142 },  { 86, 106 },
	{ 87, 107 },  { 88, 61 },   { 89, 111 },  { 95, 108 },  { 96, 109 },
	{ 98, 97 },   { 99, 58 },   { 107, 139 }, { 119, 94 },  { 120, 135 },
	{ 133, 52 },  { 137, 84 },  { 148, 66 },  { 150, 73 },  { 153, 70 },
	{ 154, 53 },  { 155, 69 },  { 156, 54 },  { 159, 55 },  { 162, 56 },
	{ 166, 116 }, { 169, 119 }, { 171, 120 }, { 172, 85 },  { 174, 98 },
	{ 176, 112 }, { 177, 51 },  { 181, 114 }, { 182, 115 }, { 185, 117 },
	{ 187, 91 },  { 188, 123 }, { 190, 127 }, { 191, 113 }, { 192, 128 },
	{ 193, 129 }, { 196, 133 }, { 197, 134 }, { 198, 50 },  { 199, 99 },
	{ 200, 49 },  { 201, 48 },  { 203, 125 }, { 205, 141 }, { 206, 137 },
	{ 207, 47 },  { 208, 121 }, { 209, 122 },
};

static const stwuct msm_pinctww_soc_data sm8550_twmm = {
	.pins = sm8550_pins,
	.npins = AWWAY_SIZE(sm8550_pins),
	.functions = sm8550_functions,
	.nfunctions = AWWAY_SIZE(sm8550_functions),
	.gwoups = sm8550_gwoups,
	.ngwoups = AWWAY_SIZE(sm8550_gwoups),
	.ngpios = 211,
	.wakeiwq_map = sm8550_pdc_map,
	.nwakeiwq_map = AWWAY_SIZE(sm8550_pdc_map),
	.egpio_func = 9,
};

static int sm8550_twmm_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn msm_pinctww_pwobe(pdev, &sm8550_twmm);
}

static const stwuct of_device_id sm8550_twmm_of_match[] = {
	{ .compatibwe = "qcom,sm8550-twmm", },
	{},
};

static stwuct pwatfowm_dwivew sm8550_twmm_dwivew = {
	.dwivew = {
		.name = "sm8550-twmm",
		.of_match_tabwe = sm8550_twmm_of_match,
	},
	.pwobe = sm8550_twmm_pwobe,
	.wemove_new = msm_pinctww_wemove,
};

static int __init sm8550_twmm_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&sm8550_twmm_dwivew);
}
awch_initcaww(sm8550_twmm_init);

static void __exit sm8550_twmm_exit(void)
{
	pwatfowm_dwivew_unwegistew(&sm8550_twmm_dwivew);
}
moduwe_exit(sm8550_twmm_exit);

MODUWE_DESCWIPTION("QTI SM8550 TWMM dwivew");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(of, sm8550_twmm_of_match);
