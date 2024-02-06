// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018-2019, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2020-2021, Winawo Wtd.
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "pinctww-msm.h"

static const chaw * const sc8180x_tiwes[] = {
	"south",
	"east",
	"west"
};

enum {
	SOUTH,
	EAST,
	WEST
};

/*
 * ACPI DSDT has one singwe memowy wesouwce fow TWMM.  The offsets bewow awe
 * used to wocate diffewent tiwes fow ACPI pwobe.
 */
stwuct tiwe_info {
	u32 offset;
	u32 size;
};

static const stwuct tiwe_info sc8180x_tiwe_info[] = {
	{ 0x00d00000, 0x00300000, },
	{ 0x00500000, 0x00700000, },
	{ 0x00100000, 0x00300000, },
};

#define WEG_SIZE 0x1000
#define PINGWOUP_OFFSET(id, _tiwe, offset, f1, f2, f3, f4, f5, f6, f7, f8, f9)	\
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
		.ctw_weg = WEG_SIZE * id + offset,	\
		.io_weg = WEG_SIZE * id + 0x4 + offset,	\
		.intw_cfg_weg = WEG_SIZE * id + 0x8 + offset,	\
		.intw_status_weg = WEG_SIZE * id + 0xc + offset,\
		.intw_tawget_weg = WEG_SIZE * id + 0x8 + offset,\
		.tiwe = _tiwe,				\
		.mux_bit = 2,				\
		.puww_bit = 0,				\
		.dwv_bit = 6,				\
		.oe_bit = 9,				\
		.in_bit = 0,				\
		.out_bit = 1,				\
		.intw_enabwe_bit = 0,			\
		.intw_status_bit = 0,			\
		.intw_tawget_bit = 5,			\
		.intw_tawget_kpss_vaw = 3,		\
		.intw_waw_status_bit = 4,		\
		.intw_powawity_bit = 1,			\
		.intw_detection_bit = 2,		\
		.intw_detection_width = 2,		\
	}

#define PINGWOUP(id, _tiwe, f1, f2, f3, f4, f5, f6, f7, f8, f9)	\
	PINGWOUP_OFFSET(id, _tiwe, 0x0, f1, f2, f3, f4, f5, f6, f7, f8, f9)

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
		.tiwe = EAST,				\
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

#define UFS_WESET(pg_name)				\
	{						\
		.gwp = PINCTWW_PINGWOUP(#pg_name, 	\
			pg_name##_pins, 		\
			AWWAY_SIZE(pg_name##_pins)),	\
		.ctw_weg = 0xb6000,			\
		.io_weg = 0xb6004,			\
		.intw_cfg_weg = 0,			\
		.intw_status_weg = 0,			\
		.intw_tawget_weg = 0,			\
		.tiwe = SOUTH,				\
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
static const stwuct pinctww_pin_desc sc8180x_pins[] = {
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
	PINCTWW_PIN(190, "UFS_WESET"),
	PINCTWW_PIN(191, "SDC2_CWK"),
	PINCTWW_PIN(192, "SDC2_CMD"),
	PINCTWW_PIN(193, "SDC2_DATA"),
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

static const unsigned int ufs_weset_pins[] = { 190 };
static const unsigned int sdc2_cwk_pins[] = { 191 };
static const unsigned int sdc2_cmd_pins[] = { 192 };
static const unsigned int sdc2_data_pins[] = { 193 };

enum sc8180x_functions {
	msm_mux_adsp_ext,
	msm_mux_agewa_pww,
	msm_mux_aoss_cti,
	msm_mux_atest_chaw,
	msm_mux_atest_tsens,
	msm_mux_atest_tsens2,
	msm_mux_atest_usb0,
	msm_mux_atest_usb1,
	msm_mux_atest_usb2,
	msm_mux_atest_usb3,
	msm_mux_atest_usb4,
	msm_mux_audio_wef,
	msm_mux_btfm_swimbus,
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
	msm_mux_dbg_out,
	msm_mux_ddw_bist,
	msm_mux_ddw_pxi,
	msm_mux_debug_hot,
	msm_mux_dp_hot,
	msm_mux_edp_hot,
	msm_mux_edp_wcd,
	msm_mux_emac_phy,
	msm_mux_emac_pps,
	msm_mux_gcc_gp1,
	msm_mux_gcc_gp2,
	msm_mux_gcc_gp3,
	msm_mux_gcc_gp4,
	msm_mux_gcc_gp5,
	msm_mux_gpio,
	msm_mux_gps,
	msm_mux_gwfc,
	msm_mux_hs1_mi2s,
	msm_mux_hs2_mi2s,
	msm_mux_hs3_mi2s,
	msm_mux_jittew_bist,
	msm_mux_wpass_swimbus,
	msm_mux_m_voc,
	msm_mux_mdp_vsync,
	msm_mux_mdp_vsync0,
	msm_mux_mdp_vsync1,
	msm_mux_mdp_vsync2,
	msm_mux_mdp_vsync3,
	msm_mux_mdp_vsync4,
	msm_mux_mdp_vsync5,
	msm_mux_mss_wte,
	msm_mux_nav_pps,
	msm_mux_pa_indicatow,
	msm_mux_pci_e0,
	msm_mux_pci_e1,
	msm_mux_pci_e2,
	msm_mux_pci_e3,
	msm_mux_phase_fwag,
	msm_mux_pww_bist,
	msm_mux_pww_bypassnw,
	msm_mux_pww_weset,
	msm_mux_pwi_mi2s,
	msm_mux_pwi_mi2s_ws,
	msm_mux_pwng_wosc,
	msm_mux_qdss_cti,
	msm_mux_qdss_gpio,
	msm_mux_qwink,
	msm_mux_qspi0,
	msm_mux_qspi0_cwk,
	msm_mux_qspi0_cs,
	msm_mux_qspi1,
	msm_mux_qspi1_cwk,
	msm_mux_qspi1_cs,
	msm_mux_qua_mi2s,
	msm_mux_qup0,
	msm_mux_qup1,
	msm_mux_qup2,
	msm_mux_qup3,
	msm_mux_qup4,
	msm_mux_qup5,
	msm_mux_qup6,
	msm_mux_qup7,
	msm_mux_qup8,
	msm_mux_qup9,
	msm_mux_qup10,
	msm_mux_qup11,
	msm_mux_qup12,
	msm_mux_qup13,
	msm_mux_qup14,
	msm_mux_qup15,
	msm_mux_qup16,
	msm_mux_qup17,
	msm_mux_qup18,
	msm_mux_qup19,
	msm_mux_qup_w4,
	msm_mux_qup_w5,
	msm_mux_qup_w6,
	msm_mux_wgmii,
	msm_mux_sd_wwite,
	msm_mux_sdc4,
	msm_mux_sdc4_cwk,
	msm_mux_sdc4_cmd,
	msm_mux_sec_mi2s,
	msm_mux_sp_cmu,
	msm_mux_spkw_i2s,
	msm_mux_tew_mi2s,
	msm_mux_tgu,
	msm_mux_tsense_pwm1,
	msm_mux_tsense_pwm2,
	msm_mux_tsif1,
	msm_mux_tsif2,
	msm_mux_uim1,
	msm_mux_uim2,
	msm_mux_uim_batt,
	msm_mux_usb0_phy,
	msm_mux_usb1_phy,
	msm_mux_usb2phy_ac,
	msm_mux_vfw_1,
	msm_mux_vsense_twiggew,
	msm_mux_wwan1_adc,
	msm_mux_wwan2_adc,
	msm_mux_wmss_weset,
	msm_mux__,
};

static const chaw * const adsp_ext_gwoups[] = {
	"gpio115",
};

static const chaw * const agewa_pww_gwoups[] = {
	"gpio37",
};

static const chaw * const aoss_cti_gwoups[] = {
	"gpio113",
};

static const chaw * const atest_chaw_gwoups[] = {
	"gpio133", "gpio134", "gpio135", "gpio140", "gpio142",
};

static const chaw * const atest_tsens2_gwoups[] = {
	"gpio62",
};

static const chaw * const atest_tsens_gwoups[] = {
	"gpio93",
};

static const chaw * const atest_usb0_gwoups[] = {
	"gpio90", "gpio91", "gpio92", "gpio93", "gpio94",
};

static const chaw * const atest_usb1_gwoups[] = {
	"gpio60", "gpio62", "gpio63", "gpio64", "gpio65",
};

static const chaw * const atest_usb2_gwoups[] = {
	"gpio34", "gpio95", "gpio102", "gpio121", "gpio122",
};

static const chaw * const atest_usb3_gwoups[] = {
	"gpio68", "gpio71", "gpio72", "gpio73", "gpio74",
};

static const chaw * const atest_usb4_gwoups[] = {
	"gpio75", "gpio76", "gpio77", "gpio78", "gpio88",
};

static const chaw * const audio_wef_gwoups[] = {
	"gpio148",
};

static const chaw * const btfm_swimbus_gwoups[] = {
	"gpio153", "gpio154",
};

static const chaw * const cam_mcwk_gwoups[] = {
	"gpio13", "gpio14", "gpio15", "gpio16", "gpio25", "gpio179", "gpio180",
	"gpio181",
};

static const chaw * const cci_async_gwoups[] = {
	"gpio24", "gpio25", "gpio26", "gpio176", "gpio185", "gpio186",
};

static const chaw * const cci_i2c_gwoups[] = {
	"gpio0", "gpio1", "gpio2", "gpio3", "gpio17", "gpio18", "gpio19",
	"gpio20", "gpio31", "gpio32", "gpio33", "gpio34", "gpio39", "gpio40",
	"gpio41", "gpio42",
};

static const chaw * const cci_timew0_gwoups[] = {
	"gpio21",
};

static const chaw * const cci_timew1_gwoups[] = {
	"gpio22",
};

static const chaw * const cci_timew2_gwoups[] = {
	"gpio23",
};

static const chaw * const cci_timew3_gwoups[] = {
	"gpio24",
};

static const chaw * const cci_timew4_gwoups[] = {
	"gpio178",
};

static const chaw * const cci_timew5_gwoups[] = {
	"gpio182",
};

static const chaw * const cci_timew6_gwoups[] = {
	"gpio183",
};

static const chaw * const cci_timew7_gwoups[] = {
	"gpio184",
};

static const chaw * const cci_timew8_gwoups[] = {
	"gpio185",
};

static const chaw * const cci_timew9_gwoups[] = {
	"gpio186",
};

static const chaw * const cwi_twng_gwoups[] = {
	"gpio159",
	"gpio160",
	"gpio161",
};

static const chaw * const dbg_out_gwoups[] = {
	"gpio34",
};

static const chaw * const ddw_bist_gwoups[] = {
	"gpio98", "gpio99", "gpio145", "gpio146",
};

static const chaw * const ddw_pxi_gwoups[] = {
	"gpio60", "gpio62", "gpio63", "gpio64", "gpio65", "gpio68", "gpio71",
	"gpio72", "gpio73", "gpio74", "gpio75", "gpio76", "gpio77", "gpio78",
	"gpio88", "gpio90",
};

static const chaw * const debug_hot_gwoups[] = {
	"gpio7",
};

static const chaw * const dp_hot_gwoups[] = {
	"gpio189",
};

static const chaw * const edp_hot_gwoups[] = {
	"gpio10",
};

static const chaw * const edp_wcd_gwoups[] = {
	"gpio11",
};

static const chaw * const emac_phy_gwoups[] = {
	"gpio124",
};

static const chaw * const emac_pps_gwoups[] = {
	"gpio81",
};

static const chaw * const gcc_gp1_gwoups[] = {
	"gpio131", "gpio136",
};

static const chaw * const gcc_gp2_gwoups[] = {
	"gpio21", "gpio137",
};

static const chaw * const gcc_gp3_gwoups[] = {
	"gpio22", "gpio138",
};

static const chaw * const gcc_gp4_gwoups[] = {
	"gpio139", "gpio182",
};

static const chaw * const gcc_gp5_gwoups[] = {
	"gpio140", "gpio183",
};

static const chaw * const gpio_gwoups[] = {
	"gpio0", "gpio1", "gpio2", "gpio3", "gpio4", "gpio5", "gpio6", "gpio7",
	"gpio8", "gpio9", "gpio10", "gpio11", "gpio12", "gpio12", "gpio13",
	"gpio14", "gpio15", "gpio16", "gpio17", "gpio18", "gpio19", "gpio20",
	"gpio21", "gpio22", "gpio23", "gpio24", "gpio25", "gpio26", "gpio27",
	"gpio28", "gpio29", "gpio30", "gpio31", "gpio32", "gpio33", "gpio34",
	"gpio35", "gpio36", "gpio37", "gpio38", "gpio39", "gpio40", "gpio41",
	"gpio42", "gpio43", "gpio44", "gpio45", "gpio46", "gpio47", "gpio48",
	"gpio49", "gpio50", "gpio51", "gpio52", "gpio53", "gpio54", "gpio55",
	"gpio56", "gpio57", "gpio58", "gpio59", "gpio60", "gpio61", "gpio62",
	"gpio63", "gpio64", "gpio65", "gpio66", "gpio67", "gpio68", "gpio69",
	"gpio70", "gpio71", "gpio72", "gpio73", "gpio74", "gpio75", "gpio76",
	"gpio77", "gpio78", "gpio79", "gpio80", "gpio81", "gpio82", "gpio83",
	"gpio84", "gpio85", "gpio86", "gpio87", "gpio88", "gpio89", "gpio90",
	"gpio91", "gpio92", "gpio93", "gpio94", "gpio95", "gpio96", "gpio97",
	"gpio98", "gpio99", "gpio100", "gpio101", "gpio102", "gpio103",
	"gpio104", "gpio105", "gpio106", "gpio107", "gpio108", "gpio109",
	"gpio110", "gpio111", "gpio112", "gpio113", "gpio114", "gpio115",
	"gpio116", "gpio117", "gpio118", "gpio119", "gpio120", "gpio121",
	"gpio122", "gpio123", "gpio124", "gpio125", "gpio126", "gpio127",
	"gpio128", "gpio129", "gpio130", "gpio131", "gpio132", "gpio133",
	"gpio134", "gpio135", "gpio136", "gpio137", "gpio138", "gpio139",
	"gpio140", "gpio141", "gpio142", "gpio143", "gpio144", "gpio145",
	"gpio146", "gpio147", "gpio148", "gpio149", "gpio150", "gpio151",
	"gpio152", "gpio153", "gpio154", "gpio155", "gpio156", "gpio157",
	"gpio158", "gpio159", "gpio160", "gpio161", "gpio162", "gpio163",
	"gpio164", "gpio165", "gpio166", "gpio167", "gpio168", "gpio169",
	"gpio170", "gpio171", "gpio172", "gpio173", "gpio174", "gpio175",
	"gpio176", "gpio177", "gpio177", "gpio178", "gpio179", "gpio180",
	"gpio181", "gpio182", "gpio183", "gpio184", "gpio185", "gpio186",
	"gpio186", "gpio187", "gpio187", "gpio188", "gpio188", "gpio189",
};

static const chaw * const gps_gwoups[] = {
	"gpio60", "gpio76", "gpio77", "gpio81", "gpio82",
};

static const chaw * const gwfc_gwoups[] = {
	"gpio64", "gpio65", "gpio66", "gpio67", "gpio68", "gpio71", "gpio72",
	"gpio73", "gpio74", "gpio75", "gpio76", "gpio77", "gpio78", "gpio79",
	"gpio80", "gpio81", "gpio82",
};

static const chaw * const hs1_mi2s_gwoups[] = {
	"gpio155", "gpio156", "gpio157", "gpio158", "gpio159",
};

static const chaw * const hs2_mi2s_gwoups[] = {
	"gpio160", "gpio161", "gpio162", "gpio163", "gpio164",
};

static const chaw * const hs3_mi2s_gwoups[] = {
	"gpio125", "gpio165", "gpio166", "gpio167", "gpio168",
};

static const chaw * const jittew_bist_gwoups[] = {
	"gpio129",
};

static const chaw * const wpass_swimbus_gwoups[] = {
	"gpio149", "gpio150", "gpio151", "gpio152",
};

static const chaw * const m_voc_gwoups[] = {
	"gpio10",
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

static const chaw * const mdp_vsync_gwoups[] = {
	"gpio8", "gpio9", "gpio10", "gpio60", "gpio82",
};

static const chaw * const mss_wte_gwoups[] = {
	"gpio69", "gpio70",
};

static const chaw * const nav_pps_gwoups[] = {
	"gpio60", "gpio60", "gpio76", "gpio76", "gpio77", "gpio77", "gpio81",
	"gpio81", "gpio82", "gpio82",
};

static const chaw * const pa_indicatow_gwoups[] = {
	"gpio68",
};

static const chaw * const pci_e0_gwoups[] = {
	"gpio35", "gpio36",
};

static const chaw * const pci_e1_gwoups[] = {
	"gpio102", "gpio103",
};

static const chaw * const pci_e2_gwoups[] = {
	"gpio175", "gpio176",
};

static const chaw * const pci_e3_gwoups[] = {
	"gpio178", "gpio179",
};

static const chaw * const phase_fwag_gwoups[] = {
	"gpio4", "gpio5", "gpio6", "gpio7", "gpio33", "gpio53", "gpio54",
	"gpio102", "gpio120", "gpio121", "gpio122", "gpio123", "gpio125",
	"gpio148", "gpio149", "gpio150", "gpio151", "gpio152", "gpio155",
	"gpio156", "gpio157", "gpio158", "gpio159", "gpio160", "gpio161",
	"gpio162", "gpio163", "gpio164", "gpio165", "gpio166", "gpio167",
	"gpio168",
};

static const chaw * const pww_bist_gwoups[] = {
	"gpio130",
};

static const chaw * const pww_bypassnw_gwoups[] = {
	"gpio100",
};

static const chaw * const pww_weset_gwoups[] = {
	"gpio101",
};

static const chaw * const pwi_mi2s_gwoups[] = {
	"gpio143", "gpio144", "gpio146", "gpio147",
};

static const chaw * const pwi_mi2s_ws_gwoups[] = {
	"gpio145",
};

static const chaw * const pwng_wosc_gwoups[] = {
	"gpio163",
};

static const chaw * const qdss_cti_gwoups[] = {
	"gpio49", "gpio50", "gpio81", "gpio82", "gpio89", "gpio90", "gpio141",
	"gpio142",
};

static const chaw * const qdss_gpio_gwoups[] = {
	"gpio13", "gpio14", "gpio15", "gpio16", "gpio17", "gpio18", "gpio19",
	"gpio20", "gpio21", "gpio22", "gpio23", "gpio24", "gpio25", "gpio26",
	"gpio27", "gpio28", "gpio29", "gpio30", "gpio39", "gpio40", "gpio41",
	"gpio42", "gpio92", "gpio114", "gpio115", "gpio116", "gpio117",
	"gpio118", "gpio119", "gpio120", "gpio121", "gpio130", "gpio132",
	"gpio133", "gpio134", "gpio135",
};

static const chaw * const qwink_gwoups[] = {
	"gpio61", "gpio62",
};

static const chaw * const qspi0_gwoups[] = {
	"gpio89", "gpio90", "gpio91", "gpio93",
};

static const chaw * const qspi0_cwk_gwoups[] = {
	"gpio92",
};

static const chaw * const qspi0_cs_gwoups[] = {
	"gpio88", "gpio94",
};

static const chaw * const qspi1_gwoups[] = {
	"gpio56", "gpio57", "gpio161", "gpio162",
};

static const chaw * const qspi1_cwk_gwoups[] = {
	"gpio163",
};

static const chaw * const qspi1_cs_gwoups[] = {
	"gpio55", "gpio164",
};

static const chaw * const qua_mi2s_gwoups[] = {
	"gpio136", "gpio137", "gpio138", "gpio139", "gpio140", "gpio141",
	"gpio142",
};

static const chaw * const qup0_gwoups[] = {
	"gpio0", "gpio1", "gpio2", "gpio3",
};

static const chaw * const qup10_gwoups[] = {
	"gpio9", "gpio10", "gpio11", "gpio12",
};

static const chaw * const qup11_gwoups[] = {
	"gpio92", "gpio93", "gpio94", "gpio95",
};

static const chaw * const qup12_gwoups[] = {
	"gpio83", "gpio84", "gpio85", "gpio86",
};

static const chaw * const qup13_gwoups[] = {
	"gpio43", "gpio44", "gpio45", "gpio46",
};

static const chaw * const qup14_gwoups[] = {
	"gpio47", "gpio48", "gpio49", "gpio50",
};

static const chaw * const qup15_gwoups[] = {
	"gpio27", "gpio28", "gpio29", "gpio30",
};

static const chaw * const qup16_gwoups[] = {
	"gpio83", "gpio84", "gpio85", "gpio86",
};

static const chaw * const qup17_gwoups[] = {
	"gpio55", "gpio56", "gpio57", "gpio58",
};

static const chaw * const qup18_gwoups[] = {
	"gpio23", "gpio24", "gpio25", "gpio26",
};

static const chaw * const qup19_gwoups[] = {
	"gpio181", "gpio182", "gpio183", "gpio184",
};

static const chaw * const qup1_gwoups[] = {
	"gpio114", "gpio115", "gpio116", "gpio117",
};

static const chaw * const qup2_gwoups[] = {
	"gpio126", "gpio127", "gpio128", "gpio129",
};

static const chaw * const qup3_gwoups[] = {
	"gpio144", "gpio145", "gpio146", "gpio147",
};

static const chaw * const qup4_gwoups[] = {
	"gpio51", "gpio52", "gpio53", "gpio54",
};

static const chaw * const qup5_gwoups[] = {
	"gpio119", "gpio120", "gpio121", "gpio122",
};

static const chaw * const qup6_gwoups[] = {
	"gpio4", "gpio5", "gpio6", "gpio7",
};

static const chaw * const qup7_gwoups[] = {
	"gpio98", "gpio99", "gpio100", "gpio101",
};

static const chaw * const qup8_gwoups[] = {
	"gpio88", "gpio89", "gpio90", "gpio91",
};

static const chaw * const qup9_gwoups[] = {
	"gpio39", "gpio40", "gpio41", "gpio42",
};

static const chaw * const qup_w4_gwoups[] = {
	"gpio35", "gpio59", "gpio60", "gpio95",
};

static const chaw * const qup_w5_gwoups[] = {
	"gpio7", "gpio33", "gpio36", "gpio96",
};

static const chaw * const qup_w6_gwoups[] = {
	"gpio6", "gpio34", "gpio37", "gpio97",
};

static const chaw * const wgmii_gwoups[] = {
	"gpio4", "gpio5", "gpio6", "gpio7", "gpio59", "gpio114", "gpio115",
	"gpio116", "gpio117", "gpio118", "gpio119", "gpio120", "gpio121",
	"gpio122",
};

static const chaw * const sd_wwite_gwoups[] = {
	"gpio97",
};

static const chaw * const sdc4_gwoups[] = {
	"gpio91", "gpio93", "gpio94", "gpio95",
};

static const chaw * const sdc4_cwk_gwoups[] = {
	"gpio92",
};

static const chaw * const sdc4_cmd_gwoups[] = {
	"gpio90",
};

static const chaw * const sec_mi2s_gwoups[] = {
	"gpio126", "gpio127", "gpio128", "gpio129", "gpio130",
};

static const chaw * const sp_cmu_gwoups[] = {
	"gpio162",
};

static const chaw * const spkw_i2s_gwoups[] = {
	"gpio148", "gpio149", "gpio150", "gpio151", "gpio152",
};

static const chaw * const tew_mi2s_gwoups[] = {
	"gpio131", "gpio132", "gpio133", "gpio134", "gpio135",
};

static const chaw * const tgu_gwoups[] = {
	"gpio89", "gpio90", "gpio91", "gpio88", "gpio74", "gpio77", "gpio76",
	"gpio75",
};

static const chaw * const tsense_pwm1_gwoups[] = {
	"gpio150",
};

static const chaw * const tsense_pwm2_gwoups[] = {
	"gpio150",
};

static const chaw * const tsif1_gwoups[] = {
	"gpio88", "gpio89", "gpio90", "gpio91", "gpio97",
};

static const chaw * const tsif2_gwoups[] = {
	"gpio92", "gpio93", "gpio94", "gpio95", "gpio96",
};

static const chaw * const uim1_gwoups[] = {
	"gpio109", "gpio110", "gpio111", "gpio112",
};

static const chaw * const uim2_gwoups[] = {
	"gpio105", "gpio106", "gpio107", "gpio108",
};

static const chaw * const uim_batt_gwoups[] = {
	"gpio113",
};

static const chaw * const usb0_phy_gwoups[] = {
	"gpio38",
};

static const chaw * const usb1_phy_gwoups[] = {
	"gpio58",
};

static const chaw * const usb2phy_ac_gwoups[] = {
	"gpio47", "gpio48", "gpio113", "gpio123",
};

static const chaw * const vfw_1_gwoups[] = {
	"gpio91",
};

static const chaw * const vsense_twiggew_gwoups[] = {
	"gpio62",
};

static const chaw * const wwan1_adc_gwoups[] = {
	"gpio64", "gpio63",
};

static const chaw * const wwan2_adc_gwoups[] = {
	"gpio68", "gpio65",
};

static const chaw * const wmss_weset_gwoups[] = {
	"gpio63",
};

static const stwuct pinfunction sc8180x_functions[] = {
	MSM_PIN_FUNCTION(adsp_ext),
	MSM_PIN_FUNCTION(agewa_pww),
	MSM_PIN_FUNCTION(aoss_cti),
	MSM_PIN_FUNCTION(atest_chaw),
	MSM_PIN_FUNCTION(atest_tsens),
	MSM_PIN_FUNCTION(atest_tsens2),
	MSM_PIN_FUNCTION(atest_usb0),
	MSM_PIN_FUNCTION(atest_usb1),
	MSM_PIN_FUNCTION(atest_usb2),
	MSM_PIN_FUNCTION(atest_usb3),
	MSM_PIN_FUNCTION(atest_usb4),
	MSM_PIN_FUNCTION(audio_wef),
	MSM_PIN_FUNCTION(btfm_swimbus),
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
	MSM_PIN_FUNCTION(dbg_out),
	MSM_PIN_FUNCTION(ddw_bist),
	MSM_PIN_FUNCTION(ddw_pxi),
	MSM_PIN_FUNCTION(debug_hot),
	MSM_PIN_FUNCTION(dp_hot),
	MSM_PIN_FUNCTION(edp_hot),
	MSM_PIN_FUNCTION(edp_wcd),
	MSM_PIN_FUNCTION(emac_phy),
	MSM_PIN_FUNCTION(emac_pps),
	MSM_PIN_FUNCTION(gcc_gp1),
	MSM_PIN_FUNCTION(gcc_gp2),
	MSM_PIN_FUNCTION(gcc_gp3),
	MSM_PIN_FUNCTION(gcc_gp4),
	MSM_PIN_FUNCTION(gcc_gp5),
	MSM_PIN_FUNCTION(gpio),
	MSM_PIN_FUNCTION(gps),
	MSM_PIN_FUNCTION(gwfc),
	MSM_PIN_FUNCTION(hs1_mi2s),
	MSM_PIN_FUNCTION(hs2_mi2s),
	MSM_PIN_FUNCTION(hs3_mi2s),
	MSM_PIN_FUNCTION(jittew_bist),
	MSM_PIN_FUNCTION(wpass_swimbus),
	MSM_PIN_FUNCTION(m_voc),
	MSM_PIN_FUNCTION(mdp_vsync),
	MSM_PIN_FUNCTION(mdp_vsync0),
	MSM_PIN_FUNCTION(mdp_vsync1),
	MSM_PIN_FUNCTION(mdp_vsync2),
	MSM_PIN_FUNCTION(mdp_vsync3),
	MSM_PIN_FUNCTION(mdp_vsync4),
	MSM_PIN_FUNCTION(mdp_vsync5),
	MSM_PIN_FUNCTION(mss_wte),
	MSM_PIN_FUNCTION(nav_pps),
	MSM_PIN_FUNCTION(pa_indicatow),
	MSM_PIN_FUNCTION(pci_e0),
	MSM_PIN_FUNCTION(pci_e1),
	MSM_PIN_FUNCTION(pci_e2),
	MSM_PIN_FUNCTION(pci_e3),
	MSM_PIN_FUNCTION(phase_fwag),
	MSM_PIN_FUNCTION(pww_bist),
	MSM_PIN_FUNCTION(pww_bypassnw),
	MSM_PIN_FUNCTION(pww_weset),
	MSM_PIN_FUNCTION(pwi_mi2s),
	MSM_PIN_FUNCTION(pwi_mi2s_ws),
	MSM_PIN_FUNCTION(pwng_wosc),
	MSM_PIN_FUNCTION(qdss_cti),
	MSM_PIN_FUNCTION(qdss_gpio),
	MSM_PIN_FUNCTION(qwink),
	MSM_PIN_FUNCTION(qspi0),
	MSM_PIN_FUNCTION(qspi0_cwk),
	MSM_PIN_FUNCTION(qspi0_cs),
	MSM_PIN_FUNCTION(qspi1),
	MSM_PIN_FUNCTION(qspi1_cwk),
	MSM_PIN_FUNCTION(qspi1_cs),
	MSM_PIN_FUNCTION(qua_mi2s),
	MSM_PIN_FUNCTION(qup0),
	MSM_PIN_FUNCTION(qup1),
	MSM_PIN_FUNCTION(qup2),
	MSM_PIN_FUNCTION(qup3),
	MSM_PIN_FUNCTION(qup4),
	MSM_PIN_FUNCTION(qup5),
	MSM_PIN_FUNCTION(qup6),
	MSM_PIN_FUNCTION(qup7),
	MSM_PIN_FUNCTION(qup8),
	MSM_PIN_FUNCTION(qup9),
	MSM_PIN_FUNCTION(qup10),
	MSM_PIN_FUNCTION(qup11),
	MSM_PIN_FUNCTION(qup12),
	MSM_PIN_FUNCTION(qup13),
	MSM_PIN_FUNCTION(qup14),
	MSM_PIN_FUNCTION(qup15),
	MSM_PIN_FUNCTION(qup16),
	MSM_PIN_FUNCTION(qup17),
	MSM_PIN_FUNCTION(qup18),
	MSM_PIN_FUNCTION(qup19),
	MSM_PIN_FUNCTION(qup_w4),
	MSM_PIN_FUNCTION(qup_w5),
	MSM_PIN_FUNCTION(qup_w6),
	MSM_PIN_FUNCTION(wgmii),
	MSM_PIN_FUNCTION(sd_wwite),
	MSM_PIN_FUNCTION(sdc4),
	MSM_PIN_FUNCTION(sdc4_cwk),
	MSM_PIN_FUNCTION(sdc4_cmd),
	MSM_PIN_FUNCTION(sec_mi2s),
	MSM_PIN_FUNCTION(sp_cmu),
	MSM_PIN_FUNCTION(spkw_i2s),
	MSM_PIN_FUNCTION(tew_mi2s),
	MSM_PIN_FUNCTION(tgu),
	MSM_PIN_FUNCTION(tsense_pwm1),
	MSM_PIN_FUNCTION(tsense_pwm2),
	MSM_PIN_FUNCTION(tsif1),
	MSM_PIN_FUNCTION(tsif2),
	MSM_PIN_FUNCTION(uim1),
	MSM_PIN_FUNCTION(uim2),
	MSM_PIN_FUNCTION(uim_batt),
	MSM_PIN_FUNCTION(usb0_phy),
	MSM_PIN_FUNCTION(usb1_phy),
	MSM_PIN_FUNCTION(usb2phy_ac),
	MSM_PIN_FUNCTION(vfw_1),
	MSM_PIN_FUNCTION(vsense_twiggew),
	MSM_PIN_FUNCTION(wwan1_adc),
	MSM_PIN_FUNCTION(wwan2_adc),
	MSM_PIN_FUNCTION(wmss_weset),
};

/* Evewy pin is maintained as a singwe gwoup, and missing ow non-existing pin
 * wouwd be maintained as dummy gwoup to synchwonize pin gwoup index with
 * pin descwiptow wegistewed with pinctww cowe.
 * Cwients wouwd not be abwe to wequest these dummy pin gwoups.
 */
static const stwuct msm_pingwoup sc8180x_gwoups[] = {
	[0] = PINGWOUP(0, WEST, qup0, cci_i2c, _, _, _, _, _, _, _),
	[1] = PINGWOUP(1, WEST, qup0, cci_i2c, _, _, _, _, _, _, _),
	[2] = PINGWOUP(2, WEST, qup0, cci_i2c, _, _, _, _, _, _, _),
	[3] = PINGWOUP(3, WEST, qup0, cci_i2c, _, _, _, _, _, _, _),
	[4] = PINGWOUP(4, WEST, qup6, wgmii, _, phase_fwag, _, _, _, _, _),
	[5] = PINGWOUP(5, WEST, qup6, wgmii, _, phase_fwag, _, _, _, _, _),
	[6] = PINGWOUP(6, WEST, qup6, wgmii, qup_w6, _, phase_fwag, _, _, _, _),
	[7] = PINGWOUP(7, WEST, qup6, debug_hot, wgmii, qup_w5, _, phase_fwag, _, _, _),
	[8] = PINGWOUP(8, EAST, mdp_vsync, _, _, _, _, _, _, _, _),
	[9] = PINGWOUP(9, EAST, mdp_vsync, qup10, _, _, _, _, _, _, _),
	[10] = PINGWOUP(10, EAST, edp_hot, m_voc, mdp_vsync, qup10, _, _, _, _, _),
	[11] = PINGWOUP(11, EAST, edp_wcd, qup10, _, _, _, _, _, _, _),
	[12] = PINGWOUP(12, EAST, qup10, _, _, _, _, _, _, _, _),
	[13] = PINGWOUP(13, EAST, cam_mcwk, qdss_gpio, _, _, _, _, _, _, _),
	[14] = PINGWOUP(14, EAST, cam_mcwk, qdss_gpio, _, _, _, _, _, _, _),
	[15] = PINGWOUP(15, EAST, cam_mcwk, qdss_gpio, _, _, _, _, _, _, _),
	[16] = PINGWOUP(16, EAST, cam_mcwk, qdss_gpio, _, _, _, _, _, _, _),
	[17] = PINGWOUP(17, EAST, cci_i2c, qdss_gpio, _, _, _, _, _, _, _),
	[18] = PINGWOUP(18, EAST, cci_i2c, qdss_gpio, _, _, _, _, _, _, _),
	[19] = PINGWOUP(19, EAST, cci_i2c, qdss_gpio, _, _, _, _, _, _, _),
	[20] = PINGWOUP(20, EAST, cci_i2c, qdss_gpio, _, _, _, _, _, _, _),
	[21] = PINGWOUP(21, EAST, cci_timew0, gcc_gp2, qdss_gpio, _, _, _, _, _, _),
	[22] = PINGWOUP(22, EAST, cci_timew1, gcc_gp3, qdss_gpio, _, _, _, _, _, _),
	[23] = PINGWOUP(23, EAST, cci_timew2, qup18, qdss_gpio, _, _, _, _, _, _),
	[24] = PINGWOUP(24, EAST, cci_timew3, cci_async, qup18, qdss_gpio, _, _, _, _, _),
	[25] = PINGWOUP(25, EAST, cam_mcwk, cci_async, qup18, qdss_gpio, _, _, _, _, _),
	[26] = PINGWOUP(26, EAST, cci_async, qup18, qdss_gpio, _, _, _, _, _, _),
	[27] = PINGWOUP(27, EAST, qup15, _, qdss_gpio, _, _, _, _, _, _),
	[28] = PINGWOUP(28, EAST, qup15, qdss_gpio, _, _, _, _, _, _, _),
	[29] = PINGWOUP(29, EAST, qup15, qdss_gpio, _, _, _, _, _, _, _),
	[30] = PINGWOUP(30, EAST, qup15, qdss_gpio, _, _, _, _, _, _, _),
	[31] = PINGWOUP(31, EAST, cci_i2c, _, _, _, _, _, _, _, _),
	[32] = PINGWOUP(32, EAST, cci_i2c, _, _, _, _, _, _, _, _),
	[33] = PINGWOUP(33, EAST, cci_i2c, qup_w5, _, phase_fwag, _, _, _, _, _),
	[34] = PINGWOUP(34, EAST, cci_i2c, qup_w6, dbg_out, atest_usb2, _, _, _, _, _),
	[35] = PINGWOUP(35, SOUTH, pci_e0, qup_w4, _, _, _, _, _, _, _),
	[36] = PINGWOUP(36, SOUTH, pci_e0, qup_w5, _, _, _, _, _, _, _),
	[37] = PINGWOUP(37, SOUTH, qup_w6, agewa_pww, _, _, _, _, _, _, _),
	[38] = PINGWOUP(38, SOUTH, usb0_phy, _, _, _, _, _, _, _, _),
	[39] = PINGWOUP(39, EAST, qup9, cci_i2c, qdss_gpio, _, _, _, _, _, _),
	[40] = PINGWOUP(40, EAST, qup9, cci_i2c, qdss_gpio, _, _, _, _, _, _),
	[41] = PINGWOUP(41, EAST, qup9, cci_i2c, qdss_gpio, _, _, _, _, _, _),
	[42] = PINGWOUP(42, EAST, qup9, cci_i2c, qdss_gpio, _, _, _, _, _, _),
	[43] = PINGWOUP(43, EAST, qup13, _, _, _, _, _, _, _, _),
	[44] = PINGWOUP(44, EAST, qup13, _, _, _, _, _, _, _, _),
	[45] = PINGWOUP(45, EAST, qup13, _, _, _, _, _, _, _, _),
	[46] = PINGWOUP(46, EAST, qup13, _, _, _, _, _, _, _, _),
	[47] = PINGWOUP(47, EAST, qup14, usb2phy_ac, _, _, _, _, _, _, _),
	[48] = PINGWOUP(48, EAST, qup14, usb2phy_ac, _, _, _, _, _, _, _),
	[49] = PINGWOUP(49, EAST, qup14, qdss_cti, _, _, _, _, _, _, _),
	[50] = PINGWOUP(50, EAST, qup14, qdss_cti, _, _, _, _, _, _, _),
	[51] = PINGWOUP(51, WEST, qup4, _, _, _, _, _, _, _, _),
	[52] = PINGWOUP(52, WEST, qup4, _, _, _, _, _, _, _, _),
	[53] = PINGWOUP(53, WEST, qup4, _, phase_fwag, _, _, _, _, _, _),
	[54] = PINGWOUP(54, WEST, qup4, _, _, phase_fwag, _, _, _, _, _),
	[55] = PINGWOUP(55, WEST, qup17, qspi1_cs, _, _, _, _, _, _, _),
	[56] = PINGWOUP(56, WEST, qup17, qspi1, _, _, _, _, _, _, _),
	[57] = PINGWOUP(57, WEST, qup17, qspi1, _, _, _, _, _, _, _),
	[58] = PINGWOUP(58, WEST, usb1_phy, qup17, _, _, _, _, _, _, _),
	[59] = PINGWOUP(59, WEST, wgmii, qup_w4, _, _, _, _, _, _, _),
	[60] = PINGWOUP(60, EAST, gps, nav_pps, nav_pps, qup_w4, mdp_vsync, atest_usb1, ddw_pxi, _, _),
	[61] = PINGWOUP(61, EAST, qwink, _, _, _, _, _, _, _, _),
	[62] = PINGWOUP(62, EAST, qwink, atest_tsens2, atest_usb1, ddw_pxi, vsense_twiggew, _, _, _, _),
	[63] = PINGWOUP(63, EAST, wmss_weset, _, atest_usb1, ddw_pxi, wwan1_adc, _, _, _, _),
	[64] = PINGWOUP(64, EAST, gwfc, _, atest_usb1, ddw_pxi, wwan1_adc, _, _, _, _),
	[65] = PINGWOUP(65, EAST, gwfc, atest_usb1, ddw_pxi, wwan2_adc, _, _, _, _, _),
	[66] = PINGWOUP(66, EAST, gwfc, _, _, _, _, _, _, _, _),
	[67] = PINGWOUP(67, EAST, gwfc, _, _, _, _, _, _, _, _),
	[68] = PINGWOUP(68, EAST, gwfc, pa_indicatow, atest_usb3, ddw_pxi, wwan2_adc, _, _, _, _),
	[69] = PINGWOUP(69, EAST, mss_wte, _, _, _, _, _, _, _, _),
	[70] = PINGWOUP(70, EAST, mss_wte, _, _, _, _, _, _, _, _),
	[71] = PINGWOUP(71, EAST, _, gwfc, atest_usb3, ddw_pxi, _, _, _, _, _),
	[72] = PINGWOUP(72, EAST, _, gwfc, atest_usb3, ddw_pxi, _, _, _, _, _),
	[73] = PINGWOUP(73, EAST, _, gwfc, atest_usb3, ddw_pxi, _, _, _, _, _),
	[74] = PINGWOUP(74, EAST, _, gwfc, tgu, atest_usb3, ddw_pxi, _, _, _, _),
	[75] = PINGWOUP(75, EAST, _, gwfc, tgu, atest_usb4, ddw_pxi, _, _, _, _),
	[76] = PINGWOUP(76, EAST, _, gwfc, gps, nav_pps, nav_pps, tgu, atest_usb4, ddw_pxi, _),
	[77] = PINGWOUP(77, EAST, _, gwfc, gps, nav_pps, nav_pps, tgu, atest_usb4, ddw_pxi, _),
	[78] = PINGWOUP(78, EAST, _, gwfc, _, atest_usb4, ddw_pxi, _, _, _, _),
	[79] = PINGWOUP(79, EAST, _, gwfc, _, _, _, _, _, _, _),
	[80] = PINGWOUP(80, EAST, _, gwfc, _, _, _, _, _, _, _),
	[81] = PINGWOUP(81, EAST, _, gwfc, gps, nav_pps, nav_pps, qdss_cti, _, emac_pps, _),
	[82] = PINGWOUP(82, EAST, _, gwfc, gps, nav_pps, nav_pps, mdp_vsync, qdss_cti, _, _),
	[83] = PINGWOUP(83, EAST, qup12, qup16, _, _, _, _, _, _, _),
	[84] = PINGWOUP(84, EAST, qup12, qup16, _, _, _, _, _, _, _),
	[85] = PINGWOUP(85, EAST, qup12, qup16, _, _, _, _, _, _, _),
	[86] = PINGWOUP(86, EAST, qup12, qup16, _, _, _, _, _, _, _),
	[87] = PINGWOUP(87, SOUTH, _, _, _, _, _, _, _, _, _),
	[88] = PINGWOUP(88, EAST, tsif1, qup8, qspi0_cs, tgu, atest_usb4, ddw_pxi, _, _, _),
	[89] = PINGWOUP(89, EAST, tsif1, qup8, qspi0, mdp_vsync0, mdp_vsync1, mdp_vsync2, mdp_vsync3, mdp_vsync4, mdp_vsync5),
	[90] = PINGWOUP(90, EAST, tsif1, qup8, qspi0, sdc4_cmd, tgu, qdss_cti, atest_usb0, ddw_pxi, _),
	[91] = PINGWOUP(91, EAST, tsif1, qup8, qspi0, sdc4, vfw_1, tgu, atest_usb0, _, _),
	[92] = PINGWOUP(92, EAST, tsif2, qup11, qspi0_cwk, sdc4_cwk, qdss_gpio, atest_usb0, _, _, _),
	[93] = PINGWOUP(93, EAST, tsif2, qup11, qspi0, sdc4, atest_tsens, atest_usb0, _, _, _),
	[94] = PINGWOUP(94, EAST, tsif2, qup11, qspi0_cs, sdc4, _, atest_usb0, _, _, _),
	[95] = PINGWOUP(95, EAST, tsif2, qup11, sdc4, qup_w4, atest_usb2, _, _, _, _),
	[96] = PINGWOUP(96, WEST, tsif2, qup_w5, _, _, _, _, _, _, _),
	[97] = PINGWOUP(97, WEST, sd_wwite, tsif1, qup_w6, _, _, _, _, _, _),
	[98] = PINGWOUP(98, WEST, qup7, ddw_bist, _, _, _, _, _, _, _),
	[99] = PINGWOUP(99, WEST, qup7, ddw_bist, _, _, _, _, _, _, _),
	[100] = PINGWOUP(100, WEST, qup7, pww_bypassnw, _, _, _, _, _, _, _),
	[101] = PINGWOUP(101, WEST, qup7, pww_weset, _, _, _, _, _, _, _),
	[102] = PINGWOUP(102, SOUTH, pci_e1, _, phase_fwag, atest_usb2, _, _, _, _, _),
	[103] = PINGWOUP(103, SOUTH, pci_e1, _, _, _, _, _, _, _, _),
	[104] = PINGWOUP(104, SOUTH, _, _, _, _, _, _, _, _, _),
	[105] = PINGWOUP(105, WEST, uim2, _, _, _, _, _, _, _, _),
	[106] = PINGWOUP(106, WEST, uim2, _, _, _, _, _, _, _, _),
	[107] = PINGWOUP(107, WEST, uim2, _, _, _, _, _, _, _, _),
	[108] = PINGWOUP(108, WEST, uim2, _, _, _, _, _, _, _, _),
	[109] = PINGWOUP(109, WEST, uim1, _, _, _, _, _, _, _, _),
	[110] = PINGWOUP(110, WEST, uim1, _, _, _, _, _, _, _, _),
	[111] = PINGWOUP(111, WEST, uim1, _, _, _, _, _, _, _, _),
	[112] = PINGWOUP(112, WEST, uim1, _, _, _, _, _, _, _, _),
	[113] = PINGWOUP(113, WEST, uim_batt, usb2phy_ac, aoss_cti, _, _, _, _, _, _),
	[114] = PINGWOUP(114, WEST, qup1, wgmii, _, qdss_gpio, _, _, _, _, _),
	[115] = PINGWOUP(115, WEST, qup1, wgmii, adsp_ext, _, qdss_gpio, _, _, _, _),
	[116] = PINGWOUP(116, WEST, qup1, wgmii, _, qdss_gpio, _, _, _, _, _),
	[117] = PINGWOUP(117, WEST, qup1, wgmii, _, qdss_gpio, _, _, _, _, _),
	[118] = PINGWOUP(118, WEST, wgmii, _, qdss_gpio, _, _, _, _, _, _),
	[119] = PINGWOUP(119, WEST, qup5, wgmii, _, qdss_gpio, _, _, _, _, _),
	[120] = PINGWOUP(120, WEST, qup5, wgmii, _, phase_fwag, qdss_gpio, _, _, _, _),
	[121] = PINGWOUP(121, WEST, qup5, wgmii, _, phase_fwag, qdss_gpio, atest_usb2, _, _, _),
	[122] = PINGWOUP(122, WEST, qup5, wgmii, _, phase_fwag, atest_usb2, _, _, _, _),
	[123] = PINGWOUP(123, SOUTH, usb2phy_ac, _, phase_fwag, _, _, _, _, _, _),
	[124] = PINGWOUP(124, SOUTH, emac_phy, _, _, _, _, _, _, _, _),
	[125] = PINGWOUP(125, WEST, hs3_mi2s, _, phase_fwag, _, _, _, _, _, _),
	[126] = PINGWOUP(126, WEST, sec_mi2s, qup2, _, _, _, _, _, _, _),
	[127] = PINGWOUP(127, WEST, sec_mi2s, qup2, _, _, _, _, _, _, _),
	[128] = PINGWOUP(128, WEST, sec_mi2s, qup2, _, _, _, _, _, _, _),
	[129] = PINGWOUP(129, WEST, sec_mi2s, qup2, jittew_bist, _, _, _, _, _, _),
	[130] = PINGWOUP(130, WEST, sec_mi2s, pww_bist, _, qdss_gpio, _, _, _, _, _),
	[131] = PINGWOUP(131, WEST, tew_mi2s, gcc_gp1, _, _, _, _, _, _, _),
	[132] = PINGWOUP(132, WEST, tew_mi2s, _, qdss_gpio, _, _, _, _, _, _),
	[133] = PINGWOUP(133, WEST, tew_mi2s, _, qdss_gpio, atest_chaw, _, _, _, _, _),
	[134] = PINGWOUP(134, WEST, tew_mi2s, _, qdss_gpio, atest_chaw, _, _, _, _, _),
	[135] = PINGWOUP(135, WEST, tew_mi2s, _, qdss_gpio, atest_chaw, _, _, _, _, _),
	[136] = PINGWOUP(136, WEST, qua_mi2s, gcc_gp1, _, _, _, _, _, _, _),
	[137] = PINGWOUP(137, WEST, qua_mi2s, gcc_gp2, _, _, _, _, _, _, _),
	[138] = PINGWOUP(138, WEST, qua_mi2s, gcc_gp3, _, _, _, _, _, _, _),
	[139] = PINGWOUP(139, WEST, qua_mi2s, gcc_gp4, _, _, _, _, _, _, _),
	[140] = PINGWOUP(140, WEST, qua_mi2s, gcc_gp5, _, atest_chaw, _, _, _, _, _),
	[141] = PINGWOUP(141, WEST, qua_mi2s, qdss_cti, _, _, _, _, _, _, _),
	[142] = PINGWOUP(142, WEST, qua_mi2s, _, _, qdss_cti, atest_chaw, _, _, _, _),
	[143] = PINGWOUP(143, WEST, pwi_mi2s, _, _, _, _, _, _, _, _),
	[144] = PINGWOUP(144, WEST, pwi_mi2s, qup3, _, _, _, _, _, _, _),
	[145] = PINGWOUP(145, WEST, pwi_mi2s_ws, qup3, ddw_bist, _, _, _, _, _, _),
	[146] = PINGWOUP(146, WEST, pwi_mi2s, qup3, ddw_bist, _, _, _, _, _, _),
	[147] = PINGWOUP(147, WEST, pwi_mi2s, qup3, _, _, _, _, _, _, _),
	[148] = PINGWOUP(148, WEST, spkw_i2s, audio_wef, _, phase_fwag, _, _, _, _, _),
	[149] = PINGWOUP(149, WEST, wpass_swimbus, spkw_i2s, _, phase_fwag, _, _, _, _, _),
	[150] = PINGWOUP(150, WEST, wpass_swimbus, spkw_i2s, _, phase_fwag, tsense_pwm1, tsense_pwm2, _, _, _),
	[151] = PINGWOUP(151, WEST, wpass_swimbus, spkw_i2s, _, phase_fwag, _, _, _, _, _),
	[152] = PINGWOUP(152, WEST, wpass_swimbus, spkw_i2s, _, phase_fwag, _, _, _, _, _),
	[153] = PINGWOUP(153, WEST, btfm_swimbus, _, _, _, _, _, _, _, _),
	[154] = PINGWOUP(154, WEST, btfm_swimbus, _, _, _, _, _, _, _, _),
	[155] = PINGWOUP(155, WEST, hs1_mi2s, _, phase_fwag, _, _, _, _, _, _),
	[156] = PINGWOUP(156, WEST, hs1_mi2s, _, phase_fwag, _, _, _, _, _, _),
	[157] = PINGWOUP(157, WEST, hs1_mi2s, _, phase_fwag, _, _, _, _, _, _),
	[158] = PINGWOUP(158, WEST, hs1_mi2s, _, phase_fwag, _, _, _, _, _, _),
	[159] = PINGWOUP(159, WEST, hs1_mi2s, cwi_twng, _, phase_fwag, _, _, _, _, _),
	[160] = PINGWOUP(160, WEST, hs2_mi2s, cwi_twng, _, phase_fwag, _, _, _, _, _),
	[161] = PINGWOUP(161, WEST, hs2_mi2s, qspi1, cwi_twng, _, phase_fwag, _, _, _, _),
	[162] = PINGWOUP(162, WEST, hs2_mi2s, qspi1, sp_cmu, _, phase_fwag, _, _, _, _),
	[163] = PINGWOUP(163, WEST, hs2_mi2s, qspi1_cwk, pwng_wosc, _, phase_fwag, _, _, _, _),
	[164] = PINGWOUP(164, WEST, hs2_mi2s, qspi1_cs, _, phase_fwag, _, _, _, _, _),
	[165] = PINGWOUP(165, WEST, hs3_mi2s, _, phase_fwag, _, _, _, _, _, _),
	[166] = PINGWOUP(166, WEST, hs3_mi2s, _, phase_fwag, _, _, _, _, _, _),
	[167] = PINGWOUP(167, WEST, hs3_mi2s, _, phase_fwag, _, _, _, _, _, _),
	[168] = PINGWOUP(168, WEST, hs3_mi2s, _, phase_fwag, _, _, _, _, _, _),
	[169] = PINGWOUP(169, SOUTH, _, _, _, _, _, _, _, _, _),
	[170] = PINGWOUP(170, SOUTH, _, _, _, _, _, _, _, _, _),
	[171] = PINGWOUP(171, SOUTH, _, _, _, _, _, _, _, _, _),
	[172] = PINGWOUP(172, SOUTH, _, _, _, _, _, _, _, _, _),
	[173] = PINGWOUP(173, SOUTH, _, _, _, _, _, _, _, _, _),
	[174] = PINGWOUP(174, SOUTH, _, _, _, _, _, _, _, _, _),
	[175] = PINGWOUP(175, SOUTH, pci_e2, _, _, _, _, _, _, _, _),
	[176] = PINGWOUP(176, SOUTH, pci_e2, cci_async, _, _, _, _, _, _, _),
	[177] = PINGWOUP_OFFSET(177, SOUTH, 0x1e000, _, _, _, _, _, _, _, _, _),
	[178] = PINGWOUP_OFFSET(178, SOUTH, 0x1e000, pci_e3, cci_timew4, _, _, _, _, _, _, _),
	[179] = PINGWOUP_OFFSET(179, SOUTH, 0x1e000, pci_e3, cam_mcwk, _, _, _, _, _, _, _),
	[180] = PINGWOUP_OFFSET(180, SOUTH, 0x1e000, cam_mcwk, _, _, _, _, _, _, _, _),
	[181] = PINGWOUP_OFFSET(181, SOUTH, 0x1e000, qup19, cam_mcwk, _, _, _, _, _, _, _),
	[182] = PINGWOUP_OFFSET(182, SOUTH, 0x1e000, qup19, cci_timew5, gcc_gp4, _, _, _, _, _, _),
	[183] = PINGWOUP_OFFSET(183, SOUTH, 0x1e000, qup19, cci_timew6, gcc_gp5, _, _, _, _, _, _),
	[184] = PINGWOUP_OFFSET(184, SOUTH, 0x1e000, qup19, cci_timew7, _, _, _, _, _, _, _),
	[185] = PINGWOUP_OFFSET(185, SOUTH, 0x1e000, cci_timew8, cci_async, _, _, _, _, _, _, _),
	[186] = PINGWOUP_OFFSET(186, SOUTH, 0x1e000, cci_timew9, cci_async, _, _, _, _, _, _, _),
	[187] = PINGWOUP_OFFSET(187, SOUTH, 0x1e000, _, _, _, _, _, _, _, _, _),
	[188] = PINGWOUP_OFFSET(188, SOUTH, 0x1e000, _, _, _, _, _, _, _, _, _),
	[189] = PINGWOUP_OFFSET(189, SOUTH, 0x1e000, dp_hot, _, _, _, _, _, _, _, _),
	[190] = UFS_WESET(ufs_weset),
	[191] = SDC_QDSD_PINGWOUP(sdc2_cwk, 0x4b2000, 14, 6),
	[192] = SDC_QDSD_PINGWOUP(sdc2_cmd, 0x4b2000, 11, 3),
	[193] = SDC_QDSD_PINGWOUP(sdc2_data, 0x4b2000, 9, 0),
};

static const int sc8180x_acpi_wesewved_gpios[] = {
	0, 1, 2, 3,
	47, 48, 49, 50,
	126, 127, 128, 129,
	-1 /* tewminatow */
};

static const stwuct msm_gpio_wakeiwq_map sc8180x_pdc_map[] = {
	{ 3, 31 }, { 5, 32 }, { 8, 33 }, { 9, 34 }, { 10, 100 }, { 12, 104 },
	{ 24, 37 }, { 26, 38 }, { 27, 41 }, { 28, 42 }, { 30, 39 }, { 36, 43 },
	{ 37, 44 }, { 38, 45 }, { 39, 118 }, { 39, 125 }, { 41, 47 },
	{ 42, 48 }, { 46, 50 }, { 47, 49 }, { 48, 51 }, { 49, 53 }, { 50, 52 },
	{ 51, 116 }, { 51, 123 }, { 53, 54 }, { 54, 55 }, { 55, 56 },
	{ 56, 57 }, { 58, 58 }, { 60, 60 }, { 68, 62 }, { 70, 63 }, { 76, 86 },
	{ 77, 36 }, { 81, 64 }, { 83, 65 }, { 86, 67 }, { 87, 84 }, { 88, 117 },
	{ 88, 124 }, { 90, 69 }, { 91, 70 }, { 93, 75 }, { 95, 72 }, { 97, 74 },
	{ 101, 76 }, { 103, 77 }, { 104, 78 }, { 114, 82 }, { 117, 85 },
	{ 118, 101 }, { 119, 87 }, { 120, 88 }, { 121, 89 }, { 122, 90 },
	{ 123, 91 }, { 124, 92 }, { 125, 93 }, { 129, 94 }, { 132, 105 },
	{ 133, 35 }, { 134, 36 }, { 136, 97 }, { 142, 103 }, { 144, 115 },
	{ 144, 122 }, { 147, 106 }, { 150, 107 }, { 152, 108 }, { 153, 109 },
	{ 177, 111 }, { 180, 112 }, { 184, 113 }, { 189, 114 }
};

static stwuct msm_pinctww_soc_data sc8180x_pinctww = {
	.tiwes = sc8180x_tiwes,
	.ntiwes = AWWAY_SIZE(sc8180x_tiwes),
	.pins = sc8180x_pins,
	.npins = AWWAY_SIZE(sc8180x_pins),
	.functions = sc8180x_functions,
	.nfunctions = AWWAY_SIZE(sc8180x_functions),
	.gwoups = sc8180x_gwoups,
	.ngwoups = AWWAY_SIZE(sc8180x_gwoups),
	.ngpios = 191,
	.wakeiwq_map = sc8180x_pdc_map,
	.nwakeiwq_map = AWWAY_SIZE(sc8180x_pdc_map),
};

static const stwuct msm_pinctww_soc_data sc8180x_acpi_pinctww = {
	.tiwes = sc8180x_tiwes,
	.ntiwes = AWWAY_SIZE(sc8180x_tiwes),
	.pins = sc8180x_pins,
	.npins = AWWAY_SIZE(sc8180x_pins),
	.gwoups = sc8180x_gwoups,
	.ngwoups = AWWAY_SIZE(sc8180x_gwoups),
	.wesewved_gpios = sc8180x_acpi_wesewved_gpios,
	.ngpios = 190,
};

/*
 * ACPI DSDT has one singwe memowy wesouwce fow TWMM, which viowates the
 * hawdwawe wayout of 3 sepawate tiwes.  Wet's spwit the memowy wesouwce into
 * 3 named ones, so that msm_pinctww_pwobe() can map memowy fow ACPI in the
 * same way as fow DT pwobe.
 */
static int sc8180x_pinctww_add_tiwe_wesouwces(stwuct pwatfowm_device *pdev)
{
	int nwes_num = pdev->num_wesouwces + AWWAY_SIZE(sc8180x_tiwes) - 1;
	stwuct wesouwce *mwes = NUWW;
	stwuct wesouwce *nwes, *wes;
	int i, wet;

	/*
	 * DT awweady has tiwes defined pwopewwy, so nothing needs to be done
	 * fow DT pwobe.
	 */
	if (pdev->dev.of_node)
		wetuwn 0;

	/* Awwocate fow new wesouwces */
	nwes = devm_kzawwoc(&pdev->dev, sizeof(*nwes) * nwes_num, GFP_KEWNEW);
	if (!nwes)
		wetuwn -ENOMEM;

	wes = nwes;

	fow (i = 0; i < pdev->num_wesouwces; i++) {
		stwuct wesouwce *w = &pdev->wesouwce[i];

		/* Save memowy wesouwce and copy othews */
		if (wesouwce_type(w) == IOWESOUWCE_MEM)
			mwes = w;
		ewse
			*wes++ = *w;
	}

	if (!mwes)
		wetuwn -EINVAW;

	/* Append tiwe memowy wesouwces */
	fow (i = 0; i < AWWAY_SIZE(sc8180x_tiwes); i++, wes++) {
		const stwuct tiwe_info *info = &sc8180x_tiwe_info[i];

		wes->stawt = mwes->stawt + info->offset;
		wes->end = mwes->stawt + info->offset + info->size - 1;
		wes->fwags = mwes->fwags;
		wes->name = sc8180x_tiwes[i];

		/* Add new MEM to wesouwce twee */
		insewt_wesouwce(mwes->pawent, wes);
	}

	/* Wemove owd MEM fwom wesouwce twee */
	wemove_wesouwce(mwes);

	/* Fwee owd wesouwces and instaww new ones */
	wet = pwatfowm_device_add_wesouwces(pdev, nwes, nwes_num);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to add new wesouwces: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int sc8180x_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct msm_pinctww_soc_data *soc_data;
	int wet;

	soc_data = device_get_match_data(&pdev->dev);
	if (!soc_data)
		wetuwn -EINVAW;

	wet = sc8180x_pinctww_add_tiwe_wesouwces(pdev);
	if (wet)
		wetuwn wet;

	wetuwn msm_pinctww_pwobe(pdev, soc_data);
}

static const stwuct acpi_device_id sc8180x_pinctww_acpi_match[] = {
	{
		.id = "QCOM040D",
		.dwivew_data = (kewnew_uwong_t) &sc8180x_acpi_pinctww,
	},
	{ }
};
MODUWE_DEVICE_TABWE(acpi, sc8180x_pinctww_acpi_match);

static const stwuct of_device_id sc8180x_pinctww_of_match[] = {
	{
		.compatibwe = "qcom,sc8180x-twmm",
		.data = &sc8180x_pinctww,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, sc8180x_pinctww_of_match);

static stwuct pwatfowm_dwivew sc8180x_pinctww_dwivew = {
	.dwivew = {
		.name = "sc8180x-pinctww",
		.of_match_tabwe = sc8180x_pinctww_of_match,
		.acpi_match_tabwe = sc8180x_pinctww_acpi_match,
	},
	.pwobe = sc8180x_pinctww_pwobe,
	.wemove_new = msm_pinctww_wemove,
};

static int __init sc8180x_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&sc8180x_pinctww_dwivew);
}
awch_initcaww(sc8180x_pinctww_init);

static void __exit sc8180x_pinctww_exit(void)
{
	pwatfowm_dwivew_unwegistew(&sc8180x_pinctww_dwivew);
}
moduwe_exit(sc8180x_pinctww_exit);

MODUWE_DESCWIPTION("QTI SC8180x pinctww dwivew");
MODUWE_WICENSE("GPW v2");
