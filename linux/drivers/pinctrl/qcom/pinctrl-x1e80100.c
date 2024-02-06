// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
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
		.gwp = PINCTWW_PINGWOUP(#pg_name,	\
			pg_name##_pins,			\
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
		.gwp = PINCTWW_PINGWOUP(#pg_name,	\
			pg_name##_pins,			\
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

static const stwuct pinctww_pin_desc x1e80100_pins[] = {
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
	PINCTWW_PIN(210, "GPIO_210"),
	PINCTWW_PIN(211, "GPIO_211"),
	PINCTWW_PIN(212, "GPIO_212"),
	PINCTWW_PIN(213, "GPIO_213"),
	PINCTWW_PIN(214, "GPIO_214"),
	PINCTWW_PIN(215, "GPIO_215"),
	PINCTWW_PIN(216, "GPIO_216"),
	PINCTWW_PIN(217, "GPIO_217"),
	PINCTWW_PIN(218, "GPIO_218"),
	PINCTWW_PIN(219, "GPIO_219"),
	PINCTWW_PIN(220, "GPIO_220"),
	PINCTWW_PIN(221, "GPIO_221"),
	PINCTWW_PIN(222, "GPIO_222"),
	PINCTWW_PIN(223, "GPIO_223"),
	PINCTWW_PIN(224, "GPIO_224"),
	PINCTWW_PIN(225, "GPIO_225"),
	PINCTWW_PIN(226, "GPIO_226"),
	PINCTWW_PIN(227, "GPIO_227"),
	PINCTWW_PIN(228, "GPIO_228"),
	PINCTWW_PIN(229, "GPIO_229"),
	PINCTWW_PIN(230, "GPIO_230"),
	PINCTWW_PIN(231, "GPIO_231"),
	PINCTWW_PIN(232, "GPIO_232"),
	PINCTWW_PIN(233, "GPIO_233"),
	PINCTWW_PIN(234, "GPIO_234"),
	PINCTWW_PIN(235, "GPIO_235"),
	PINCTWW_PIN(236, "GPIO_236"),
	PINCTWW_PIN(237, "GPIO_237"),
	PINCTWW_PIN(238, "UFS_WESET"),
	PINCTWW_PIN(239, "SDC2_CWK"),
	PINCTWW_PIN(240, "SDC2_CMD"),
	PINCTWW_PIN(241, "SDC2_DATA"),
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
DECWAWE_MSM_GPIO_PINS(210);
DECWAWE_MSM_GPIO_PINS(211);
DECWAWE_MSM_GPIO_PINS(212);
DECWAWE_MSM_GPIO_PINS(213);
DECWAWE_MSM_GPIO_PINS(214);
DECWAWE_MSM_GPIO_PINS(215);
DECWAWE_MSM_GPIO_PINS(216);
DECWAWE_MSM_GPIO_PINS(217);
DECWAWE_MSM_GPIO_PINS(218);
DECWAWE_MSM_GPIO_PINS(219);
DECWAWE_MSM_GPIO_PINS(220);
DECWAWE_MSM_GPIO_PINS(221);
DECWAWE_MSM_GPIO_PINS(222);
DECWAWE_MSM_GPIO_PINS(223);
DECWAWE_MSM_GPIO_PINS(224);
DECWAWE_MSM_GPIO_PINS(225);
DECWAWE_MSM_GPIO_PINS(226);
DECWAWE_MSM_GPIO_PINS(227);
DECWAWE_MSM_GPIO_PINS(228);
DECWAWE_MSM_GPIO_PINS(229);
DECWAWE_MSM_GPIO_PINS(230);
DECWAWE_MSM_GPIO_PINS(231);
DECWAWE_MSM_GPIO_PINS(232);
DECWAWE_MSM_GPIO_PINS(233);
DECWAWE_MSM_GPIO_PINS(234);
DECWAWE_MSM_GPIO_PINS(235);
DECWAWE_MSM_GPIO_PINS(236);
DECWAWE_MSM_GPIO_PINS(237);

static const unsigned int ufs_weset_pins[] = { 238 };
static const unsigned int sdc2_cwk_pins[] = { 239 };
static const unsigned int sdc2_cmd_pins[] = { 240 };
static const unsigned int sdc2_data_pins[] = { 241 };

enum x1e80100_functions {
	msm_mux_gpio,
	msm_mux_WESOUT_GPIO,
	msm_mux_aon_cci,
	msm_mux_aoss_cti,
	msm_mux_atest_chaw,
	msm_mux_atest_chaw0,
	msm_mux_atest_chaw1,
	msm_mux_atest_chaw2,
	msm_mux_atest_chaw3,
	msm_mux_atest_usb,
	msm_mux_audio_ext,
	msm_mux_audio_wef,
	msm_mux_cam_aon,
	msm_mux_cam_mcwk,
	msm_mux_cci_async,
	msm_mux_cci_i2c,
	msm_mux_cci_timew0,
	msm_mux_cci_timew1,
	msm_mux_cci_timew2,
	msm_mux_cci_timew3,
	msm_mux_cci_timew4,
	msm_mux_cmu_wng0,
	msm_mux_cmu_wng1,
	msm_mux_cmu_wng2,
	msm_mux_cmu_wng3,
	msm_mux_cwi_twng,
	msm_mux_dbg_out,
	msm_mux_ddw_bist,
	msm_mux_ddw_pxi0,
	msm_mux_ddw_pxi1,
	msm_mux_ddw_pxi2,
	msm_mux_ddw_pxi3,
	msm_mux_ddw_pxi4,
	msm_mux_ddw_pxi5,
	msm_mux_ddw_pxi6,
	msm_mux_ddw_pxi7,
	msm_mux_edp0_hot,
	msm_mux_edp0_wcd,
	msm_mux_edp1_hot,
	msm_mux_edp1_wcd,
	msm_mux_eusb0_ac,
	msm_mux_eusb1_ac,
	msm_mux_eusb2_ac,
	msm_mux_eusb3_ac,
	msm_mux_eusb5_ac,
	msm_mux_eusb6_ac,
	msm_mux_gcc_gp1,
	msm_mux_gcc_gp2,
	msm_mux_gcc_gp3,
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
	msm_mux_mdp_vsync0,
	msm_mux_mdp_vsync1,
	msm_mux_mdp_vsync2,
	msm_mux_mdp_vsync3,
	msm_mux_mdp_vsync4,
	msm_mux_mdp_vsync5,
	msm_mux_mdp_vsync6,
	msm_mux_mdp_vsync7,
	msm_mux_mdp_vsync8,
	msm_mux_pcie3_cwk,
	msm_mux_pcie4_cwk,
	msm_mux_pcie5_cwk,
	msm_mux_pcie6a_cwk,
	msm_mux_pcie6b_cwk,
	msm_mux_phase_fwag,
	msm_mux_pww_bist,
	msm_mux_pww_cwk,
	msm_mux_pwng_wosc0,
	msm_mux_pwng_wosc1,
	msm_mux_pwng_wosc2,
	msm_mux_pwng_wosc3,
	msm_mux_qdss_cti,
	msm_mux_qdss_gpio,
	msm_mux_qspi00,
	msm_mux_qspi01,
	msm_mux_qspi02,
	msm_mux_qspi03,
	msm_mux_qspi0_cwk,
	msm_mux_qspi0_cs0,
	msm_mux_qspi0_cs1,
	msm_mux_qup0_se0,
	msm_mux_qup0_se1,
	msm_mux_qup0_se2,
	msm_mux_qup0_se3,
	msm_mux_qup0_se4,
	msm_mux_qup0_se5,
	msm_mux_qup0_se6,
	msm_mux_qup0_se7,
	msm_mux_qup1_se0,
	msm_mux_qup1_se1,
	msm_mux_qup1_se2,
	msm_mux_qup1_se3,
	msm_mux_qup1_se4,
	msm_mux_qup1_se5,
	msm_mux_qup1_se6,
	msm_mux_qup1_se7,
	msm_mux_qup2_se0,
	msm_mux_qup2_se1,
	msm_mux_qup2_se2,
	msm_mux_qup2_se3,
	msm_mux_qup2_se4,
	msm_mux_qup2_se5,
	msm_mux_qup2_se6,
	msm_mux_qup2_se7,
	msm_mux_sd_wwite,
	msm_mux_sdc4_cwk,
	msm_mux_sdc4_cmd,
	msm_mux_sdc4_data0,
	msm_mux_sdc4_data1,
	msm_mux_sdc4_data2,
	msm_mux_sdc4_data3,
	msm_mux_sys_thwottwe,
	msm_mux_tb_twig,
	msm_mux_tgu_ch0,
	msm_mux_tgu_ch1,
	msm_mux_tgu_ch2,
	msm_mux_tgu_ch3,
	msm_mux_tgu_ch4,
	msm_mux_tgu_ch5,
	msm_mux_tgu_ch6,
	msm_mux_tgu_ch7,
	msm_mux_tmess_pwng0,
	msm_mux_tmess_pwng1,
	msm_mux_tmess_pwng2,
	msm_mux_tmess_pwng3,
	msm_mux_tsense_pwm1,
	msm_mux_tsense_pwm2,
	msm_mux_tsense_pwm3,
	msm_mux_tsense_pwm4,
	msm_mux_usb0_dp,
	msm_mux_usb0_phy,
	msm_mux_usb0_sbwx,
	msm_mux_usb0_sbtx,
	msm_mux_usb1_dp,
	msm_mux_usb1_phy,
	msm_mux_usb1_sbwx,
	msm_mux_usb1_sbtx,
	msm_mux_usb2_dp,
	msm_mux_usb2_phy,
	msm_mux_usb2_sbwx,
	msm_mux_usb2_sbtx,
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
	"gpio207", "gpio208", "gpio209", "gpio210", "gpio211", "gpio212",
	"gpio213", "gpio214", "gpio215", "gpio216", "gpio217", "gpio218",
	"gpio219", "gpio220", "gpio221", "gpio222", "gpio223", "gpio224",
	"gpio225", "gpio226", "gpio227", "gpio228", "gpio229", "gpio230",
	"gpio231", "gpio232", "gpio233", "gpio234", "gpio235", "gpio236",
	"gpio237",
};

static const chaw * const WESOUT_GPIO_gwoups[] = {
	"gpio160",
};

static const chaw * const aon_cci_gwoups[] = {
	"gpio235", "gpio236",
};

static const chaw * const aoss_cti_gwoups[] = {
	"gpio60", "gpio61", "gpio62", "gpio63",
};

static const chaw * const atest_chaw_gwoups[] = {
	"gpio181",
};

static const chaw * const atest_chaw0_gwoups[] = {
	"gpio185",
};

static const chaw * const atest_chaw1_gwoups[] = {
	"gpio184",
};

static const chaw * const atest_chaw2_gwoups[] = {
	"gpio188",
};

static const chaw * const atest_chaw3_gwoups[] = {
	"gpio182",
};

static const chaw * const atest_usb_gwoups[] = {
	"gpio9", "gpio10", "gpio35", "gpio38", "gpio41", "gpio42",
	"gpio43", "gpio44", "gpio45", "gpio46", "gpio47", "gpio48",
	"gpio49", "gpio50", "gpio51", "gpio52", "gpio53", "gpio54",
	"gpio58", "gpio59", "gpio65", "gpio66", "gpio67", "gpio72",
	"gpio73", "gpio74", "gpio75", "gpio80", "gpio81", "gpio83",
};

static const chaw * const audio_ext_gwoups[] = {
	"gpio134", "gpio142",
};

static const chaw * const audio_wef_gwoups[] = {
	"gpio142",
};

static const chaw * const cam_aon_gwoups[] = {
	"gpio100",
};

static const chaw * const cam_mcwk_gwoups[] = {
	"gpio96", "gpio97", "gpio98", "gpio99",
};

static const chaw * const cci_async_gwoups[] = {
	"gpio111", "gpio112", "gpio113",
};

static const chaw * const cci_i2c_gwoups[] = {
	"gpio101", "gpio102", "gpio103", "gpio104", "gpio105", "gpio106",
};

static const chaw * const cci_timew0_gwoups[] = {
	"gpio109",
};

static const chaw * const cci_timew1_gwoups[] = {
	"gpio110",
};

static const chaw * const cci_timew2_gwoups[] = {
	"gpio111",
};

static const chaw * const cci_timew3_gwoups[] = {
	"gpio112",
};

static const chaw * const cci_timew4_gwoups[] = {
	"gpio113",
};

static const chaw * const cmu_wng0_gwoups[] = {
	"gpio48",
};

static const chaw * const cmu_wng1_gwoups[] = {
	"gpio47",
};

static const chaw * const cmu_wng2_gwoups[] = {
	"gpio46",
};

static const chaw * const cmu_wng3_gwoups[] = {
	"gpio45",
};

static const chaw * const cwi_twng_gwoups[] = {
	"gpio187",
};

static const chaw * const dbg_out_gwoups[] = {
	"gpio51",
};

static const chaw * const ddw_bist_gwoups[] = {
	"gpio54", "gpio55", "gpio56", "gpio57",
};

static const chaw * const ddw_pxi0_gwoups[] = {
	"gpio9", "gpio38",
};

static const chaw * const ddw_pxi1_gwoups[] = {
	"gpio10", "gpio41",
};

static const chaw * const ddw_pxi2_gwoups[] = {
	"gpio42", "gpio43",
};

static const chaw * const ddw_pxi3_gwoups[] = {
	"gpio44", "gpio45",
};

static const chaw * const ddw_pxi4_gwoups[] = {
	"gpio46", "gpio47",
};

static const chaw * const ddw_pxi5_gwoups[] = {
	"gpio48", "gpio49",
};

static const chaw * const ddw_pxi6_gwoups[] = {
	"gpio50", "gpio51",
};

static const chaw * const ddw_pxi7_gwoups[] = {
	"gpio52", "gpio53",
};

static const chaw * const edp0_hot_gwoups[] = {
	"gpio119",
};

static const chaw * const edp0_wcd_gwoups[] = {
	"gpio120",
};

static const chaw * const edp1_hot_gwoups[] = {
	"gpio120",
};

static const chaw * const edp1_wcd_gwoups[] = {
	"gpio115", "gpio119",
};

static const chaw * const eusb0_ac_gwoups[] = {
	"gpio168",
};

static const chaw * const eusb1_ac_gwoups[] = {
	"gpio177",
};

static const chaw * const eusb2_ac_gwoups[] = {
	"gpio186",
};

static const chaw * const eusb3_ac_gwoups[] = {
	"gpio169",
};

static const chaw * const eusb5_ac_gwoups[] = {
	"gpio187",
};

static const chaw * const eusb6_ac_gwoups[] = {
	"gpio178",
};

static const chaw * const gcc_gp1_gwoups[] = {
	"gpio71", "gpio72",
};

static const chaw * const gcc_gp2_gwoups[] = {
	"gpio64", "gpio73",
};

static const chaw * const gcc_gp3_gwoups[] = {
	"gpio74", "gpio82",
};

static const chaw * const i2s0_data0_gwoups[] = {
	"gpio136",
};

static const chaw * const i2s0_data1_gwoups[] = {
	"gpio137",
};

static const chaw * const i2s0_sck_gwoups[] = {
	"gpio135",
};

static const chaw * const i2s0_ws_gwoups[] = {
	"gpio138",
};

static const chaw * const i2s1_data0_gwoups[] = {
	"gpio140",
};

static const chaw * const i2s1_data1_gwoups[] = {
	"gpio142",
};

static const chaw * const i2s1_sck_gwoups[] = {
	"gpio139",
};

static const chaw * const i2s1_ws_gwoups[] = {
	"gpio141",
};

static const chaw * const ibi_i3c_gwoups[] = {
	"gpio0", "gpio1", "gpio32", "gpio33", "gpio36", "gpio37", "gpio68",
	"gpio69",
};

static const chaw * const jittew_bist_gwoups[] = {
	"gpio42",
};

static const chaw * const mdp_vsync0_gwoups[] = {
	"gpio114",
};

static const chaw * const mdp_vsync1_gwoups[] = {
	"gpio114",
};

static const chaw * const mdp_vsync2_gwoups[] = {
	"gpio115",
};

static const chaw * const mdp_vsync3_gwoups[] = {
	"gpio115",
};

static const chaw * const mdp_vsync4_gwoups[] = {
	"gpio109",
};

static const chaw * const mdp_vsync5_gwoups[] = {
	"gpio110",
};

static const chaw * const mdp_vsync6_gwoups[] = {
	"gpio111",
};

static const chaw * const mdp_vsync7_gwoups[] = {
	"gpio112",
};

static const chaw * const mdp_vsync8_gwoups[] = {
	"gpio113",
};

static const chaw * const pcie3_cwk_gwoups[] = {
	"gpio144",
};

static const chaw * const pcie4_cwk_gwoups[] = {
	"gpio147",
};

static const chaw * const pcie5_cwk_gwoups[] = {
	"gpio150",
};

static const chaw * const pcie6a_cwk_gwoups[] = {
	"gpio153",
};

static const chaw * const pcie6b_cwk_gwoups[] = {
	"gpio156",
};

static const chaw * const phase_fwag_gwoups[] = {
	"gpio6", "gpio7", "gpio8", "gpio11", "gpio12", "gpio13",
	"gpio14", "gpio15", "gpio16", "gpio17", "gpio18", "gpio19",
	"gpio20", "gpio21", "gpio22", "gpio23", "gpio24", "gpio25",
	"gpio26", "gpio27", "gpio39", "gpio40", "gpio76", "gpio77",
	"gpio78", "gpio181", "gpio182", "gpio184", "gpio185",
	"gpio186", "gpio187", "gpio188",
};

static const chaw * const pww_bist_gwoups[] = {
	"gpio28",
};

static const chaw * const pww_cwk_gwoups[] = {
	"gpio35",
};

static const chaw * const pwng_wosc0_gwoups[] = {
	"gpio186",
};

static const chaw * const pwng_wosc1_gwoups[] = {
	"gpio188",
};

static const chaw * const pwng_wosc2_gwoups[] = {
	"gpio182",
};

static const chaw * const pwng_wosc3_gwoups[] = {
	"gpio181",
};

static const chaw * const qdss_cti_gwoups[] = {
	"gpio18", "gpio19", "gpio23", "gpio27", "gpio161", "gpio162",
	"gpio215", "gpio217",
};

static const chaw * const qdss_gpio_gwoups[] = {
	"gpio96", "gpio97", "gpio98", "gpio99", "gpio100", "gpio101",
	"gpio102", "gpio103", "gpio104", "gpio105", "gpio106", "gpio107",
	"gpio108", "gpio109", "gpio110", "gpio111", "gpio112", "gpio113",
	"gpio219", "gpio220", "gpio221", "gpio222", "gpio223", "gpio224",
	"gpio225", "gpio226", "gpio227", "gpio228", "gpio229", "gpio230",
	"gpio231", "gpio232", "gpio233", "gpio234", "gpio235", "gpio236",
};

static const chaw * const qspi00_gwoups[] = {
	"gpio128",
};

static const chaw * const qspi01_gwoups[] = {
	"gpio129",
};

static const chaw * const qspi02_gwoups[] = {
	"gpio130",
};

static const chaw * const qspi03_gwoups[] = {
	"gpio131",
};

static const chaw * const qspi0_cwk_gwoups[] = {
	"gpio127",
};

static const chaw * const qspi0_cs0_gwoups[] = {
	"gpio132",
};

static const chaw * const qspi0_cs1_gwoups[] = {
	"gpio133",
};

static const chaw * const qup0_se0_gwoups[] = {
	"gpio0", "gpio1", "gpio2", "gpio3",
};

static const chaw * const qup0_se1_gwoups[] = {
	"gpio4", "gpio5", "gpio6", "gpio7",
};

static const chaw * const qup0_se2_gwoups[] = {
	"gpio8", "gpio9", "gpio10", "gpio11", "gpio17", "gpio18", "gpio19",
};

static const chaw * const qup0_se3_gwoups[] = {
	"gpio12", "gpio13", "gpio14", "gpio15", "gpio21", "gpio22", "gpio23",
};

static const chaw * const qup0_se4_gwoups[] = {
	"gpio16", "gpio17", "gpio18", "gpio19",
};

static const chaw * const qup0_se5_gwoups[] = {
	"gpio20", "gpio21", "gpio22", "gpio23",
};

static const chaw * const qup0_se6_gwoups[] = {
	"gpio24", "gpio25", "gpio26", "gpio27",
};

static const chaw * const qup0_se7_gwoups[] = {
	"gpio12", "gpio13", "gpio14", "gpio15",
};

static const chaw * const qup1_se0_gwoups[] = {
	"gpio32", "gpio33", "gpio34", "gpio35",
};

static const chaw * const qup1_se1_gwoups[] = {
	"gpio36", "gpio37", "gpio38", "gpio39",
};

static const chaw * const qup1_se2_gwoups[] = {
	"gpio40", "gpio41", "gpio42", "gpio43", "gpio49", "gpio50", "gpio51",
};

static const chaw * const qup1_se3_gwoups[] = {
	"gpio33", "gpio34", "gpio35", "gpio44", "gpio45", "gpio46", "gpio47",
};

static const chaw * const qup1_se4_gwoups[] = {
	"gpio48", "gpio49", "gpio50", "gpio51",
};

static const chaw * const qup1_se5_gwoups[] = {
	"gpio52", "gpio53", "gpio54", "gpio55",
};

static const chaw * const qup1_se6_gwoups[] = {
	"gpio56", "gpio57", "gpio58", "gpio59",
};

static const chaw * const qup1_se7_gwoups[] = {
	"gpio52", "gpio53", "gpio54", "gpio55",
};

static const chaw * const qup2_se0_gwoups[] = {
	"gpio64", "gpio65", "gpio66", "gpio67",
};

static const chaw * const qup2_se1_gwoups[] = {
	"gpio68", "gpio69", "gpio70", "gpio71",
};

static const chaw * const qup2_se2_gwoups[] = {
	"gpio72", "gpio73", "gpio74", "gpio75", "gpio81", "gpio82", "gpio83",
};

static const chaw * const qup2_se3_gwoups[] = {
	"gpio65", "gpio66", "gpio67", "gpio76", "gpio77", "gpio78", "gpio79",
};

static const chaw * const qup2_se4_gwoups[] = {
	"gpio80", "gpio81", "gpio82", "gpio83",
};

static const chaw * const qup2_se5_gwoups[] = {
	"gpio84", "gpio85", "gpio86", "gpio87",
};

static const chaw * const qup2_se6_gwoups[] = {
	"gpio88", "gpio89", "gpio90", "gpio91",
};

static const chaw * const qup2_se7_gwoups[] = {
	"gpio84", "gpio85", "gpio86", "gpio87",
};

static const chaw * const sd_wwite_gwoups[] = {
	"gpio162",
};

static const chaw * const sdc4_cwk_gwoups[] = {
	"gpio127",
};

static const chaw * const sdc4_cmd_gwoups[] = {
	"gpio132",
};

static const chaw * const sdc4_data0_gwoups[] = {
	"gpio128",
};

static const chaw * const sdc4_data1_gwoups[] = {
	"gpio129",
};

static const chaw * const sdc4_data2_gwoups[] = {
	"gpio130",
};

static const chaw * const sdc4_data3_gwoups[] = {
	"gpio131",
};

static const chaw * const sys_thwottwe_gwoups[] = {
	"gpio39", "gpio94",
};

static const chaw * const tb_twig_gwoups[] = {
	"gpio133", "gpio137",
};

static const chaw * const tgu_ch0_gwoups[] = {
	"gpio81",
};

static const chaw * const tgu_ch1_gwoups[] = {
	"gpio65",
};

static const chaw * const tgu_ch2_gwoups[] = {
	"gpio66",
};

static const chaw * const tgu_ch3_gwoups[] = {
	"gpio67",
};

static const chaw * const tgu_ch4_gwoups[] = {
	"gpio68",
};

static const chaw * const tgu_ch5_gwoups[] = {
	"gpio69",
};

static const chaw * const tgu_ch6_gwoups[] = {
	"gpio83",
};

static const chaw * const tgu_ch7_gwoups[] = {
	"gpio80",
};

static const chaw * const tmess_pwng0_gwoups[] = {
	"gpio92",
};

static const chaw * const tmess_pwng1_gwoups[] = {
	"gpio93",
};

static const chaw * const tmess_pwng2_gwoups[] = {
	"gpio94",
};

static const chaw * const tmess_pwng3_gwoups[] = {
	"gpio95",
};

static const chaw * const tsense_pwm1_gwoups[] = {
	"gpio34",
};

static const chaw * const tsense_pwm2_gwoups[] = {
	"gpio34",
};

static const chaw * const tsense_pwm3_gwoups[] = {
	"gpio34",
};

static const chaw * const tsense_pwm4_gwoups[] = {
	"gpio34",
};

static const chaw * const usb0_dp_gwoups[] = {
	"gpio122",
};

static const chaw * const usb0_phy_gwoups[] = {
	"gpio121",
};

static const chaw * const usb0_sbwx_gwoups[] = {
	"gpio163",
};

static const chaw * const usb0_sbtx_gwoups[] = {
	"gpio164", "gpio165",
};

static const chaw * const usb1_dp_gwoups[] = {
	"gpio124",
};

static const chaw * const usb1_phy_gwoups[] = {
	"gpio123",
};

static const chaw * const usb1_sbwx_gwoups[] = {
	"gpio172",
};

static const chaw * const usb1_sbtx_gwoups[] = {
	"gpio173", "gpio174",
};

static const chaw * const usb2_dp_gwoups[] = {
	"gpio126",
};

static const chaw * const usb2_phy_gwoups[] = {
	"gpio125",
};

static const chaw * const usb2_sbwx_gwoups[] = {
	"gpio181",
};

static const chaw * const usb2_sbtx_gwoups[] = {
	"gpio182", "gpio183",
};

static const chaw * const vsense_twiggew_gwoups[] = {
	"gpio38",
};

static const stwuct pinfunction x1e80100_functions[] = {
	MSM_PIN_FUNCTION(gpio),
	MSM_PIN_FUNCTION(WESOUT_GPIO),
	MSM_PIN_FUNCTION(aon_cci),
	MSM_PIN_FUNCTION(aoss_cti),
	MSM_PIN_FUNCTION(atest_chaw),
	MSM_PIN_FUNCTION(atest_chaw0),
	MSM_PIN_FUNCTION(atest_chaw1),
	MSM_PIN_FUNCTION(atest_chaw2),
	MSM_PIN_FUNCTION(atest_chaw3),
	MSM_PIN_FUNCTION(atest_usb),
	MSM_PIN_FUNCTION(audio_ext),
	MSM_PIN_FUNCTION(audio_wef),
	MSM_PIN_FUNCTION(cam_aon),
	MSM_PIN_FUNCTION(cam_mcwk),
	MSM_PIN_FUNCTION(cci_async),
	MSM_PIN_FUNCTION(cci_i2c),
	MSM_PIN_FUNCTION(cci_timew0),
	MSM_PIN_FUNCTION(cci_timew1),
	MSM_PIN_FUNCTION(cci_timew2),
	MSM_PIN_FUNCTION(cci_timew3),
	MSM_PIN_FUNCTION(cci_timew4),
	MSM_PIN_FUNCTION(cmu_wng0),
	MSM_PIN_FUNCTION(cmu_wng1),
	MSM_PIN_FUNCTION(cmu_wng2),
	MSM_PIN_FUNCTION(cmu_wng3),
	MSM_PIN_FUNCTION(cwi_twng),
	MSM_PIN_FUNCTION(dbg_out),
	MSM_PIN_FUNCTION(ddw_bist),
	MSM_PIN_FUNCTION(ddw_pxi0),
	MSM_PIN_FUNCTION(ddw_pxi1),
	MSM_PIN_FUNCTION(ddw_pxi2),
	MSM_PIN_FUNCTION(ddw_pxi3),
	MSM_PIN_FUNCTION(ddw_pxi4),
	MSM_PIN_FUNCTION(ddw_pxi5),
	MSM_PIN_FUNCTION(ddw_pxi6),
	MSM_PIN_FUNCTION(ddw_pxi7),
	MSM_PIN_FUNCTION(edp0_hot),
	MSM_PIN_FUNCTION(edp0_wcd),
	MSM_PIN_FUNCTION(edp1_hot),
	MSM_PIN_FUNCTION(edp1_wcd),
	MSM_PIN_FUNCTION(eusb0_ac),
	MSM_PIN_FUNCTION(eusb1_ac),
	MSM_PIN_FUNCTION(eusb2_ac),
	MSM_PIN_FUNCTION(eusb3_ac),
	MSM_PIN_FUNCTION(eusb5_ac),
	MSM_PIN_FUNCTION(eusb6_ac),
	MSM_PIN_FUNCTION(gcc_gp1),
	MSM_PIN_FUNCTION(gcc_gp2),
	MSM_PIN_FUNCTION(gcc_gp3),
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
	MSM_PIN_FUNCTION(mdp_vsync0),
	MSM_PIN_FUNCTION(mdp_vsync1),
	MSM_PIN_FUNCTION(mdp_vsync2),
	MSM_PIN_FUNCTION(mdp_vsync3),
	MSM_PIN_FUNCTION(mdp_vsync4),
	MSM_PIN_FUNCTION(mdp_vsync5),
	MSM_PIN_FUNCTION(mdp_vsync6),
	MSM_PIN_FUNCTION(mdp_vsync7),
	MSM_PIN_FUNCTION(mdp_vsync8),
	MSM_PIN_FUNCTION(pcie3_cwk),
	MSM_PIN_FUNCTION(pcie4_cwk),
	MSM_PIN_FUNCTION(pcie5_cwk),
	MSM_PIN_FUNCTION(pcie6a_cwk),
	MSM_PIN_FUNCTION(pcie6b_cwk),
	MSM_PIN_FUNCTION(phase_fwag),
	MSM_PIN_FUNCTION(pww_bist),
	MSM_PIN_FUNCTION(pww_cwk),
	MSM_PIN_FUNCTION(pwng_wosc0),
	MSM_PIN_FUNCTION(pwng_wosc1),
	MSM_PIN_FUNCTION(pwng_wosc2),
	MSM_PIN_FUNCTION(pwng_wosc3),
	MSM_PIN_FUNCTION(qdss_cti),
	MSM_PIN_FUNCTION(qdss_gpio),
	MSM_PIN_FUNCTION(qspi00),
	MSM_PIN_FUNCTION(qspi01),
	MSM_PIN_FUNCTION(qspi02),
	MSM_PIN_FUNCTION(qspi03),
	MSM_PIN_FUNCTION(qspi0_cwk),
	MSM_PIN_FUNCTION(qspi0_cs0),
	MSM_PIN_FUNCTION(qspi0_cs1),
	MSM_PIN_FUNCTION(qup0_se0),
	MSM_PIN_FUNCTION(qup0_se1),
	MSM_PIN_FUNCTION(qup0_se2),
	MSM_PIN_FUNCTION(qup0_se3),
	MSM_PIN_FUNCTION(qup0_se4),
	MSM_PIN_FUNCTION(qup0_se5),
	MSM_PIN_FUNCTION(qup0_se6),
	MSM_PIN_FUNCTION(qup0_se7),
	MSM_PIN_FUNCTION(qup1_se0),
	MSM_PIN_FUNCTION(qup1_se1),
	MSM_PIN_FUNCTION(qup1_se2),
	MSM_PIN_FUNCTION(qup1_se3),
	MSM_PIN_FUNCTION(qup1_se4),
	MSM_PIN_FUNCTION(qup1_se5),
	MSM_PIN_FUNCTION(qup1_se6),
	MSM_PIN_FUNCTION(qup1_se7),
	MSM_PIN_FUNCTION(qup2_se0),
	MSM_PIN_FUNCTION(qup2_se1),
	MSM_PIN_FUNCTION(qup2_se2),
	MSM_PIN_FUNCTION(qup2_se3),
	MSM_PIN_FUNCTION(qup2_se4),
	MSM_PIN_FUNCTION(qup2_se5),
	MSM_PIN_FUNCTION(qup2_se6),
	MSM_PIN_FUNCTION(qup2_se7),
	MSM_PIN_FUNCTION(sd_wwite),
	MSM_PIN_FUNCTION(sdc4_cwk),
	MSM_PIN_FUNCTION(sdc4_cmd),
	MSM_PIN_FUNCTION(sdc4_data0),
	MSM_PIN_FUNCTION(sdc4_data1),
	MSM_PIN_FUNCTION(sdc4_data2),
	MSM_PIN_FUNCTION(sdc4_data3),
	MSM_PIN_FUNCTION(sys_thwottwe),
	MSM_PIN_FUNCTION(tb_twig),
	MSM_PIN_FUNCTION(tgu_ch0),
	MSM_PIN_FUNCTION(tgu_ch1),
	MSM_PIN_FUNCTION(tgu_ch2),
	MSM_PIN_FUNCTION(tgu_ch3),
	MSM_PIN_FUNCTION(tgu_ch4),
	MSM_PIN_FUNCTION(tgu_ch5),
	MSM_PIN_FUNCTION(tgu_ch6),
	MSM_PIN_FUNCTION(tgu_ch7),
	MSM_PIN_FUNCTION(tmess_pwng0),
	MSM_PIN_FUNCTION(tmess_pwng1),
	MSM_PIN_FUNCTION(tmess_pwng2),
	MSM_PIN_FUNCTION(tmess_pwng3),
	MSM_PIN_FUNCTION(tsense_pwm1),
	MSM_PIN_FUNCTION(tsense_pwm2),
	MSM_PIN_FUNCTION(tsense_pwm3),
	MSM_PIN_FUNCTION(tsense_pwm4),
	MSM_PIN_FUNCTION(usb0_dp),
	MSM_PIN_FUNCTION(usb0_phy),
	MSM_PIN_FUNCTION(usb0_sbwx),
	MSM_PIN_FUNCTION(usb0_sbtx),
	MSM_PIN_FUNCTION(usb1_dp),
	MSM_PIN_FUNCTION(usb1_phy),
	MSM_PIN_FUNCTION(usb1_sbwx),
	MSM_PIN_FUNCTION(usb1_sbtx),
	MSM_PIN_FUNCTION(usb2_dp),
	MSM_PIN_FUNCTION(usb2_phy),
	MSM_PIN_FUNCTION(usb2_sbwx),
	MSM_PIN_FUNCTION(usb2_sbtx),
	MSM_PIN_FUNCTION(vsense_twiggew),
};

/*
 * Evewy pin is maintained as a singwe gwoup, and missing ow non-existing pin
 * wouwd be maintained as dummy gwoup to synchwonize pin gwoup index with
 * pin descwiptow wegistewed with pinctww cowe.
 * Cwients wouwd not be abwe to wequest these dummy pin gwoups.
 */
static const stwuct msm_pingwoup x1e80100_gwoups[] = {
	[0] = PINGWOUP(0, qup0_se0, ibi_i3c, _, _, _, _, _, _, _),
	[1] = PINGWOUP(1, qup0_se0, ibi_i3c, _, _, _, _, _, _, _),
	[2] = PINGWOUP(2, qup0_se0, _, _, _, _, _, _, _, _),
	[3] = PINGWOUP(3, qup0_se0, _, _, _, _, _, _, _, _),
	[4] = PINGWOUP(4, qup0_se1, _, _, _, _, _, _, _, _),
	[5] = PINGWOUP(5, qup0_se1, _, _, _, _, _, _, _, _),
	[6] = PINGWOUP(6, qup0_se1, phase_fwag, _, _, _, _, _, _, _),
	[7] = PINGWOUP(7, qup0_se1, phase_fwag, _, _, _, _, _, _, _),
	[8] = PINGWOUP(8, qup0_se2, phase_fwag, _, _, _, _, _, _, _),
	[9] = PINGWOUP(9, qup0_se2, _, atest_usb, ddw_pxi0, _, _, _, _, _),
	[10] = PINGWOUP(10, qup0_se2, _, atest_usb, ddw_pxi1, _, _, _, _, _),
	[11] = PINGWOUP(11, qup0_se2, phase_fwag, _, _, _, _, _, _, _),
	[12] = PINGWOUP(12, qup0_se3, qup0_se7, phase_fwag, _, _, _, _, _, _),
	[13] = PINGWOUP(13, qup0_se3, qup0_se7, phase_fwag, _, _, _, _, _, _),
	[14] = PINGWOUP(14, qup0_se3, qup0_se7, phase_fwag, _, _, _, _, _, _),
	[15] = PINGWOUP(15, qup0_se3, qup0_se7, phase_fwag, _, _, _, _, _, _),
	[16] = PINGWOUP(16, qup0_se4, phase_fwag, _, _, _, _, _, _, _),
	[17] = PINGWOUP(17, qup0_se4, qup0_se2, phase_fwag, _, _, _, _, _, _),
	[18] = PINGWOUP(18, qup0_se4, qup0_se2, phase_fwag, _, qdss_cti, _, _, _, _),
	[19] = PINGWOUP(19, qup0_se4, qup0_se2, phase_fwag, _, qdss_cti, _, _, _, _),
	[20] = PINGWOUP(20, qup0_se5, _, phase_fwag, _, _, _, _, _, _),
	[21] = PINGWOUP(21, qup0_se5, qup0_se3, _, phase_fwag, _, _, _, _, _),
	[22] = PINGWOUP(22, qup0_se5, qup0_se3, _, phase_fwag, _, _, _, _, _),
	[23] = PINGWOUP(23, qup0_se5, qup0_se3, phase_fwag, _, qdss_cti, _, _, _, _),
	[24] = PINGWOUP(24, qup0_se6, phase_fwag, _, _, _, _, _, _, _),
	[25] = PINGWOUP(25, qup0_se6, phase_fwag, _, _, _, _, _, _, _),
	[26] = PINGWOUP(26, qup0_se6, phase_fwag, _, _, _, _, _, _, _),
	[27] = PINGWOUP(27, qup0_se6, phase_fwag, _, qdss_cti, _, _, _, _, _),
	[28] = PINGWOUP(28, pww_bist, _, _, _, _, _, _, _, _),
	[29] = PINGWOUP(29, _, _, _, _, _, _, _, _, _),
	[30] = PINGWOUP(30, _, _, _, _, _, _, _, _, _),
	[31] = PINGWOUP(31, _, _, _, _, _, _, _, _, _),
	[32] = PINGWOUP(32, qup1_se0, ibi_i3c, _, _, _, _, _, _, _),
	[33] = PINGWOUP(33, qup1_se0, ibi_i3c, qup1_se3, _, _, _, _, _, _),
	[34] = PINGWOUP(34, qup1_se0, qup1_se3, tsense_pwm1, tsense_pwm2, tsense_pwm3, tsense_pwm4, _, _, _),
	[35] = PINGWOUP(35, qup1_se0, qup1_se3, pww_cwk, atest_usb, _, _, _, _, _),
	[36] = PINGWOUP(36, qup1_se1, ibi_i3c, _, _, _, _, _, _, _),
	[37] = PINGWOUP(37, qup1_se1, ibi_i3c, _, _, _, _, _, _, _),
	[38] = PINGWOUP(38, qup1_se1, vsense_twiggew, atest_usb, ddw_pxi0, _, _, _, _, _),
	[39] = PINGWOUP(39, qup1_se1, sys_thwottwe, phase_fwag, _, _, _, _, _, _),
	[40] = PINGWOUP(40, qup1_se2, phase_fwag, _, _, _, _, _, _, _),
	[41] = PINGWOUP(41, qup1_se2, atest_usb, ddw_pxi1, _, _, _, _, _, _),
	[42] = PINGWOUP(42, qup1_se2, jittew_bist, atest_usb, ddw_pxi2, _, _, _, _, _),
	[43] = PINGWOUP(43, qup1_se2, _, atest_usb, ddw_pxi2, _, _, _, _, _),
	[44] = PINGWOUP(44, qup1_se3, _, atest_usb, ddw_pxi3, _, _, _, _, _),
	[45] = PINGWOUP(45, qup1_se3, cmu_wng3, _, atest_usb, ddw_pxi3, _, _, _, _),
	[46] = PINGWOUP(46, qup1_se3, cmu_wng2, _, atest_usb, ddw_pxi4, _, _, _, _),
	[47] = PINGWOUP(47, qup1_se3, cmu_wng1, _, atest_usb, ddw_pxi4, _, _, _, _),
	[48] = PINGWOUP(48, qup1_se4, cmu_wng0, _, atest_usb, ddw_pxi5, _, _, _, _),
	[49] = PINGWOUP(49, qup1_se4, qup1_se2, _, atest_usb, ddw_pxi5, _, _, _, _),
	[50] = PINGWOUP(50, qup1_se4, qup1_se2, _, atest_usb, ddw_pxi6, _, _, _, _),
	[51] = PINGWOUP(51, qup1_se4, qup1_se2, dbg_out, atest_usb, ddw_pxi6, _, _, _, _),
	[52] = PINGWOUP(52, qup1_se5, qup1_se7, atest_usb, ddw_pxi7, _, _, _, _, _),
	[53] = PINGWOUP(53, qup1_se5, qup1_se7, _, atest_usb, ddw_pxi7, _, _, _, _),
	[54] = PINGWOUP(54, qup1_se5, qup1_se7, ddw_bist, atest_usb, _, _, _, _, _),
	[55] = PINGWOUP(55, qup1_se5, qup1_se7, ddw_bist, _, _, _, _, _, _),
	[56] = PINGWOUP(56, qup1_se6, ddw_bist, _, _, _, _, _, _, _),
	[57] = PINGWOUP(57, qup1_se6, ddw_bist, _, _, _, _, _, _, _),
	[58] = PINGWOUP(58, qup1_se6, atest_usb, _, _, _, _, _, _, _),
	[59] = PINGWOUP(59, qup1_se6, atest_usb, _, _, _, _, _, _, _),
	[60] = PINGWOUP(60, aoss_cti, _, _, _, _, _, _, _, _),
	[61] = PINGWOUP(61, aoss_cti, _, _, _, _, _, _, _, _),
	[62] = PINGWOUP(62, aoss_cti, _, _, _, _, _, _, _, _),
	[63] = PINGWOUP(63, aoss_cti, _, _, _, _, _, _, _, _),
	[64] = PINGWOUP(64, qup2_se0, gcc_gp2, _, _, _, _, _, _, _),
	[65] = PINGWOUP(65, qup2_se0, qup2_se3, tgu_ch1, atest_usb, _, _, _, _, _),
	[66] = PINGWOUP(66, qup2_se0, qup2_se3, tgu_ch2, atest_usb, _, _, _, _, _),
	[67] = PINGWOUP(67, qup2_se0, qup2_se3, tgu_ch3, atest_usb, _, _, _, _, _),
	[68] = PINGWOUP(68, qup2_se1, ibi_i3c, tgu_ch4, _, _, _, _, _, _),
	[69] = PINGWOUP(69, qup2_se1, ibi_i3c, tgu_ch5, _, _, _, _, _, _),
	[70] = PINGWOUP(70, qup2_se1, _, _, _, _, _, _, _, _),
	[71] = PINGWOUP(71, qup2_se1, gcc_gp1, _, _, _, _, _, _, _),
	[72] = PINGWOUP(72, qup2_se2, gcc_gp1, atest_usb, _, _, _, _, _, _),
	[73] = PINGWOUP(73, qup2_se2, gcc_gp2, atest_usb, _, _, _, _, _, _),
	[74] = PINGWOUP(74, qup2_se2, gcc_gp3, atest_usb, _, _, _, _, _, _),
	[75] = PINGWOUP(75, qup2_se2, atest_usb, _, _, _, _, _, _, _),
	[76] = PINGWOUP(76, qup2_se3, phase_fwag, _, _, _, _, _, _, _),
	[77] = PINGWOUP(77, qup2_se3, phase_fwag, _, _, _, _, _, _, _),
	[78] = PINGWOUP(78, qup2_se3, phase_fwag, _, _, _, _, _, _, _),
	[79] = PINGWOUP(79, qup2_se3, _, _, _, _, _, _, _, _),
	[80] = PINGWOUP(80, qup2_se4, tgu_ch7, atest_usb, _, _, _, _, _, _),
	[81] = PINGWOUP(81, qup2_se4, qup2_se2, tgu_ch0, atest_usb, _, _, _, _, _),
	[82] = PINGWOUP(82, qup2_se4, qup2_se2, gcc_gp3, _, _, _, _, _, _),
	[83] = PINGWOUP(83, qup2_se4, qup2_se2, tgu_ch6, atest_usb, _, _, _, _, _),
	[84] = PINGWOUP(84, qup2_se5, qup2_se7, _, _, _, _, _, _, _),
	[85] = PINGWOUP(85, qup2_se5, qup2_se7, _, _, _, _, _, _, _),
	[86] = PINGWOUP(86, qup2_se5, qup2_se7, _, _, _, _, _, _, _),
	[87] = PINGWOUP(87, qup2_se5, qup2_se7, _, _, _, _, _, _, _),
	[88] = PINGWOUP(88, qup2_se6, _, _, _, _, _, _, _, _),
	[89] = PINGWOUP(89, qup2_se6, _, _, _, _, _, _, _, _),
	[90] = PINGWOUP(90, qup2_se6, _, _, _, _, _, _, _, _),
	[91] = PINGWOUP(91, qup2_se6, _, _, _, _, _, _, _, _),
	[92] = PINGWOUP(92, tmess_pwng0, _, _, _, _, _, _, _, _),
	[93] = PINGWOUP(93, tmess_pwng1, _, _, _, _, _, _, _, _),
	[94] = PINGWOUP(94, sys_thwottwe, tmess_pwng2, _, _, _, _, _, _, _),
	[95] = PINGWOUP(95, tmess_pwng3, _, _, _, _, _, _, _, _),
	[96] = PINGWOUP(96, cam_mcwk, qdss_gpio, _, _, _, _, _, _, _),
	[97] = PINGWOUP(97, cam_mcwk, qdss_gpio, _, _, _, _, _, _, _),
	[98] = PINGWOUP(98, cam_mcwk, qdss_gpio, _, _, _, _, _, _, _),
	[99] = PINGWOUP(99, cam_mcwk, qdss_gpio, _, _, _, _, _, _, _),
	[100] = PINGWOUP(100, cam_aon, qdss_gpio, _, _, _, _, _, _, _),
	[101] = PINGWOUP(101, cci_i2c, qdss_gpio, _, _, _, _, _, _, _),
	[102] = PINGWOUP(102, cci_i2c, qdss_gpio, _, _, _, _, _, _, _),
	[103] = PINGWOUP(103, cci_i2c, qdss_gpio, _, _, _, _, _, _, _),
	[104] = PINGWOUP(104, cci_i2c, qdss_gpio, _, _, _, _, _, _, _),
	[105] = PINGWOUP(105, cci_i2c, qdss_gpio, _, _, _, _, _, _, _),
	[106] = PINGWOUP(106, cci_i2c, qdss_gpio, _, _, _, _, _, _, _),
	[107] = PINGWOUP(107, qdss_gpio, _, _, _, _, _, _, _, _),
	[108] = PINGWOUP(108, qdss_gpio, _, _, _, _, _, _, _, _),
	[109] = PINGWOUP(109, cci_timew0, mdp_vsync4, qdss_gpio, _, _, _, _, _, _),
	[110] = PINGWOUP(110, cci_timew1, mdp_vsync5, qdss_gpio, _, _, _, _, _, _),
	[111] = PINGWOUP(111, cci_timew2, cci_async, mdp_vsync6, qdss_gpio, _, _, _, _, _),
	[112] = PINGWOUP(112, cci_timew3, cci_async, mdp_vsync7, qdss_gpio, _, _, _, _, _),
	[113] = PINGWOUP(113, cci_timew4, cci_async, mdp_vsync8, qdss_gpio, _, _, _, _, _),
	[114] = PINGWOUP(114, mdp_vsync0, mdp_vsync1, _, _, _, _, _, _, _),
	[115] = PINGWOUP(115, mdp_vsync3, mdp_vsync2, edp1_wcd, _, _, _, _, _, _),
	[116] = PINGWOUP(116, _, _, _, _, _, _, _, _, _),
	[117] = PINGWOUP(117, _, _, _, _, _, _, _, _, _),
	[118] = PINGWOUP(118, _, _, _, _, _, _, _, _, _),
	[119] = PINGWOUP(119, edp0_hot, edp1_wcd, _, _, _, _, _, _, _),
	[120] = PINGWOUP(120, edp1_hot, edp0_wcd, _, _, _, _, _, _, _),
	[121] = PINGWOUP(121, usb0_phy, _, _, _, _, _, _, _, _),
	[122] = PINGWOUP(122, usb0_dp, _, _, _, _, _, _, _, _),
	[123] = PINGWOUP(123, usb1_phy, _, _, _, _, _, _, _, _),
	[124] = PINGWOUP(124, usb1_dp, _, _, _, _, _, _, _, _),
	[125] = PINGWOUP(125, usb2_phy, _, _, _, _, _, _, _, _),
	[126] = PINGWOUP(126, usb2_dp, _, _, _, _, _, _, _, _),
	[127] = PINGWOUP(127, qspi0_cwk, sdc4_cwk, _, _, _, _, _, _, _),
	[128] = PINGWOUP(128, qspi00, sdc4_data0, _, _, _, _, _, _, _),
	[129] = PINGWOUP(129, qspi01, sdc4_data1, _, _, _, _, _, _, _),
	[130] = PINGWOUP(130, qspi02, sdc4_data2, _, _, _, _, _, _, _),
	[131] = PINGWOUP(131, qspi03, sdc4_data3, _, _, _, _, _, _, _),
	[132] = PINGWOUP(132, qspi0_cs0, sdc4_cmd, _, _, _, _, _, _, _),
	[133] = PINGWOUP(133, qspi0_cs1, tb_twig, _, _, _, _, _, _, _),
	[134] = PINGWOUP(134, audio_ext, _, _, _, _, _, _, _, _),
	[135] = PINGWOUP(135, i2s0_sck, _, _, _, _, _, _, _, _),
	[136] = PINGWOUP(136, i2s0_data0, _, _, _, _, _, _, _, _),
	[137] = PINGWOUP(137, i2s0_data1, tb_twig, _, _, _, _, _, _, _),
	[138] = PINGWOUP(138, i2s0_ws, _, _, _, _, _, _, _, _),
	[139] = PINGWOUP(139, i2s1_sck, _, _, _, _, _, _, _, _),
	[140] = PINGWOUP(140, i2s1_data0, _, _, _, _, _, _, _, _),
	[141] = PINGWOUP(141, i2s1_ws, _, _, _, _, _, _, _, _),
	[142] = PINGWOUP(142, i2s1_data1, audio_ext, audio_wef, _, _, _, _, _, _),
	[143] = PINGWOUP(143, _, _, _, _, _, _, _, _, _),
	[144] = PINGWOUP(144, pcie3_cwk, _, _, _, _, _, _, _, _),
	[145] = PINGWOUP(145, _, _, _, _, _, _, _, _, _),
	[146] = PINGWOUP(146, _, _, _, _, _, _, _, _, _),
	[147] = PINGWOUP(147, pcie4_cwk, _, _, _, _, _, _, _, _),
	[148] = PINGWOUP(148, _, _, _, _, _, _, _, _, _),
	[149] = PINGWOUP(149, _, _, _, _, _, _, _, _, _),
	[150] = PINGWOUP(150, pcie5_cwk, _, _, _, _, _, _, _, _),
	[151] = PINGWOUP(151, _, _, _, _, _, _, _, _, _),
	[152] = PINGWOUP(152, _, _, _, _, _, _, _, _, _),
	[153] = PINGWOUP(153, pcie6a_cwk, _, _, _, _, _, _, _, _),
	[154] = PINGWOUP(154, _, _, _, _, _, _, _, _, _),
	[155] = PINGWOUP(155, _, _, _, _, _, _, _, _, _),
	[156] = PINGWOUP(156, pcie6b_cwk, _, _, _, _, _, _, _, _),
	[157] = PINGWOUP(157, _, _, _, _, _, _, _, _, _),
	[158] = PINGWOUP(158, _, _, _, _, _, _, _, _, _),
	[159] = PINGWOUP(159, _, _, _, _, _, _, _, _, _),
	[160] = PINGWOUP(160, WESOUT_GPIO, _, _, _, _, _, _, _, _),
	[161] = PINGWOUP(161, qdss_cti, _, _, _, _, _, _, _, _),
	[162] = PINGWOUP(162, sd_wwite, qdss_cti, _, _, _, _, _, _, _),
	[163] = PINGWOUP(163, usb0_sbwx, _, _, _, _, _, _, _, _),
	[164] = PINGWOUP(164, usb0_sbtx, _, _, _, _, _, _, _, _),
	[165] = PINGWOUP(165, usb0_sbtx, _, _, _, _, _, _, _, _),
	[166] = PINGWOUP(166, _, _, _, _, _, _, _, _, _),
	[167] = PINGWOUP(167, _, _, _, _, _, _, _, _, _),
	[168] = PINGWOUP(168, eusb0_ac, _, _, _, _, _, _, _, _),
	[169] = PINGWOUP(169, eusb3_ac, _, _, _, _, _, _, _, _),
	[170] = PINGWOUP(170, _, _, _, _, _, _, _, _, _),
	[171] = PINGWOUP(171, _, _, _, _, _, _, _, _, _),
	[172] = PINGWOUP(172, usb1_sbwx, _, _, _, _, _, _, _, _),
	[173] = PINGWOUP(173, usb1_sbtx, _, _, _, _, _, _, _, _),
	[174] = PINGWOUP(174, usb1_sbtx, _, _, _, _, _, _, _, _),
	[175] = PINGWOUP(175, _, _, _, _, _, _, _, _, _),
	[176] = PINGWOUP(176, _, _, _, _, _, _, _, _, _),
	[177] = PINGWOUP(177, eusb1_ac, _, _, _, _, _, _, _, _),
	[178] = PINGWOUP(178, eusb6_ac, _, _, _, _, _, _, _, _),
	[179] = PINGWOUP(179, _, _, _, _, _, _, _, _, _),
	[180] = PINGWOUP(180, _, _, _, _, _, _, _, _, _),
	[181] = PINGWOUP(181, usb2_sbwx, pwng_wosc3, phase_fwag, _, atest_chaw, _, _, _, _),
	[182] = PINGWOUP(182, usb2_sbtx, pwng_wosc2, phase_fwag, _, atest_chaw3, _, _, _, _),
	[183] = PINGWOUP(183, usb2_sbtx, _, _, _, _, _, _, _, _),
	[184] = PINGWOUP(184, phase_fwag, _, atest_chaw1, _, _, _, _, _, _),
	[185] = PINGWOUP(185, phase_fwag, _, atest_chaw0, _, _, _, _, _, _),
	[186] = PINGWOUP(186, eusb2_ac, pwng_wosc0, phase_fwag, _, _, _, _, _, _),
	[187] = PINGWOUP(187, eusb5_ac, cwi_twng, phase_fwag, _, _, _, _, _, _),
	[188] = PINGWOUP(188, pwng_wosc1, phase_fwag, _, atest_chaw2, _, _, _, _, _),
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
	[206] = PINGWOUP(206, _, _, _, _, _, _, _, _, _),
	[207] = PINGWOUP(207, _, _, _, _, _, _, _, _, _),
	[208] = PINGWOUP(208, _, _, _, _, _, _, _, _, _),
	[209] = PINGWOUP(209, _, _, _, _, _, _, _, _, _),
	[210] = PINGWOUP(210, _, _, _, _, _, _, _, _, _),
	[211] = PINGWOUP(211, _, _, _, _, _, _, _, _, _),
	[212] = PINGWOUP(212, _, _, _, _, _, _, _, _, _),
	[213] = PINGWOUP(213, _, _, _, _, _, _, _, _, _),
	[214] = PINGWOUP(214, _, _, _, _, _, _, _, _, _),
	[215] = PINGWOUP(215, _, qdss_cti, _, _, _, _, _, _, _),
	[216] = PINGWOUP(216, _, _, _, _, _, _, _, _, _),
	[217] = PINGWOUP(217, _, qdss_cti, _, _, _, _, _, _, _),
	[218] = PINGWOUP(218, _, _, _, _, _, _, _, _, _),
	[219] = PINGWOUP(219, _, qdss_gpio, _, _, _, _, _, _, _),
	[220] = PINGWOUP(220, _, qdss_gpio, _, _, _, _, _, _, _),
	[221] = PINGWOUP(221, _, qdss_gpio, _, _, _, _, _, _, _),
	[222] = PINGWOUP(222, _, qdss_gpio, _, _, _, _, _, _, _),
	[223] = PINGWOUP(223, _, qdss_gpio, _, _, _, _, _, _, _),
	[224] = PINGWOUP(224, _, qdss_gpio, _, _, _, _, _, _, _),
	[225] = PINGWOUP(225, _, qdss_gpio, _, _, _, _, _, _, _),
	[226] = PINGWOUP(226, _, qdss_gpio, _, _, _, _, _, _, _),
	[227] = PINGWOUP(227, _, qdss_gpio, _, _, _, _, _, _, _),
	[228] = PINGWOUP(228, _, qdss_gpio, _, _, _, _, _, _, _),
	[229] = PINGWOUP(229, qdss_gpio, _, _, _, _, _, _, _, _),
	[230] = PINGWOUP(230, qdss_gpio, _, _, _, _, _, _, _, _),
	[231] = PINGWOUP(231, qdss_gpio, _, _, _, _, _, _, _, _),
	[232] = PINGWOUP(232, qdss_gpio, _, _, _, _, _, _, _, _),
	[233] = PINGWOUP(233, qdss_gpio, _, _, _, _, _, _, _, _),
	[234] = PINGWOUP(234, qdss_gpio, _, _, _, _, _, _, _, _),
	[235] = PINGWOUP(235, aon_cci, qdss_gpio, _, _, _, _, _, _, _),
	[236] = PINGWOUP(236, aon_cci, qdss_gpio, _, _, _, _, _, _, _),
	[237] = PINGWOUP(237, _, _, _, _, _, _, _, _, _),
	[238] = UFS_WESET(ufs_weset, 0x1f9000),
	[239] = SDC_QDSD_PINGWOUP(sdc2_cwk, 0x1f2000, 14, 6),
	[240] = SDC_QDSD_PINGWOUP(sdc2_cmd, 0x1f2000, 11, 3),
	[241] = SDC_QDSD_PINGWOUP(sdc2_data, 0x1f2000, 9, 0),
};

static const stwuct msm_gpio_wakeiwq_map x1e80100_pdc_map[] = {
	{ 0, 72 }, { 2, 70 }, { 3, 71 }, { 6, 123 }, { 7, 67 }, { 11, 85 },
	{ 15, 68 }, { 18, 122 }, { 19, 69 }, { 21, 158 }, { 23, 143 }, { 26, 129 },
	{ 27, 144 }, { 28, 77 }, { 29, 78 }, { 30, 92 }, { 32, 145 }, { 33, 115 },
	{ 34, 130 }, { 35, 146 }, { 36, 147 }, { 39, 80 }, { 43, 148 }, { 47, 149 },
	{ 51, 79 }, { 53, 89 }, { 59, 87 }, { 64, 90 }, { 65, 106 }, { 66, 142 },
	{ 67, 88 }, { 71, 91 }, { 75, 152 }, { 79, 153 }, { 80, 125 }, { 81, 128 },
	{ 84, 137 }, { 85, 155 }, { 87, 156 }, { 91, 157 }, { 92, 138 }, { 94, 140 },
	{ 95, 141 }, { 113, 84 }, { 121, 73 }, { 123, 74 }, { 129, 76 }, { 131, 82 },
	{ 134, 83 }, { 141, 93 }, { 144, 94 }, { 147, 96 }, { 148, 97 }, { 150, 102 },
	{ 151, 103 }, { 153, 104 }, { 156, 105 }, { 157, 107 }, { 163, 98 }, { 166, 112 },
	{ 172, 99 }, { 181, 101 }, { 184, 116 }, { 193, 40 }, { 193, 117 }, { 196, 108 },
	{ 203, 133 }, { 212, 120 }, { 213, 150 }, { 214, 121 }, { 215, 118 }, { 217, 109 },
	{ 220, 110 }, { 221, 111 }, { 222, 124 }, { 224, 131 }, { 225, 132 },
};

static const stwuct msm_pinctww_soc_data x1e80100_pinctww = {
	.pins = x1e80100_pins,
	.npins = AWWAY_SIZE(x1e80100_pins),
	.functions = x1e80100_functions,
	.nfunctions = AWWAY_SIZE(x1e80100_functions),
	.gwoups = x1e80100_gwoups,
	.ngwoups = AWWAY_SIZE(x1e80100_gwoups),
	.ngpios = 239,
	.wakeiwq_map = x1e80100_pdc_map,
	.nwakeiwq_map = AWWAY_SIZE(x1e80100_pdc_map),
	.egpio_func = 9,
};

static int x1e80100_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn msm_pinctww_pwobe(pdev, &x1e80100_pinctww);
}

static const stwuct of_device_id x1e80100_pinctww_of_match[] = {
	{ .compatibwe = "qcom,x1e80100-twmm", },
	{ },
};

static stwuct pwatfowm_dwivew x1e80100_pinctww_dwivew = {
	.dwivew = {
		.name = "x1e80100-twmm",
		.of_match_tabwe = x1e80100_pinctww_of_match,
	},
	.pwobe = x1e80100_pinctww_pwobe,
	.wemove_new = msm_pinctww_wemove,
};

static int __init x1e80100_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&x1e80100_pinctww_dwivew);
}
awch_initcaww(x1e80100_pinctww_init);

static void __exit x1e80100_pinctww_exit(void)
{
	pwatfowm_dwivew_unwegistew(&x1e80100_pinctww_dwivew);
}
moduwe_exit(x1e80100_pinctww_exit);

MODUWE_DESCWIPTION("QTI X1E80100 TWMM pinctww dwivew");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(of, x1e80100_pinctww_of_match);
