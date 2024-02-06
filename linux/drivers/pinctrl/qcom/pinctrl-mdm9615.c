// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014, Sony Mobiwe Communications AB.
 * Copywight (c) 2016 BayWibwe, SAS.
 * Authow : Neiw Awmstwong <nawmstwong@baywibwe.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "pinctww-msm.h"

static const stwuct pinctww_pin_desc mdm9615_pins[] = {
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

#define PINGWOUP(id, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11) \
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
			msm_mux_##f10,			\
			msm_mux_##f11			\
		},					\
		.nfuncs = 12,				\
		.ctw_weg = 0x1000 + 0x10 * id,		\
		.io_weg = 0x1004 + 0x10 * id,		\
		.intw_cfg_weg = 0x1008 + 0x10 * id,	\
		.intw_status_weg = 0x100c + 0x10 * id,	\
		.intw_tawget_weg = 0x400 + 0x4 * id,	\
		.mux_bit = 2,				\
		.puww_bit = 0,				\
		.dwv_bit = 6,				\
		.oe_bit = 9,				\
		.in_bit = 0,				\
		.out_bit = 1,				\
		.intw_enabwe_bit = 0,			\
		.intw_status_bit = 0,			\
		.intw_ack_high = 1,			\
		.intw_tawget_bit = 0,			\
		.intw_tawget_kpss_vaw = 4,		\
		.intw_waw_status_bit = 3,		\
		.intw_powawity_bit = 1,			\
		.intw_detection_bit = 2,		\
		.intw_detection_width = 1,		\
	}

enum mdm9615_functions {
	msm_mux_gpio,
	msm_mux_gsbi2_i2c,
	msm_mux_gsbi3,
	msm_mux_gsbi4,
	msm_mux_gsbi5_i2c,
	msm_mux_gsbi5_uawt,
	msm_mux_sdc2,
	msm_mux_ebi2_wcdc,
	msm_mux_ps_howd,
	msm_mux_pwim_audio,
	msm_mux_sec_audio,
	msm_mux_cdc_mcwk,
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
	"gpio85", "gpio86", "gpio87"
};

static const chaw * const gsbi2_i2c_gwoups[] = {
	"gpio4", "gpio5"
};

static const chaw * const gsbi3_gwoups[] = {
	"gpio8", "gpio9", "gpio10", "gpio11"
};

static const chaw * const gsbi4_gwoups[] = {
	"gpio12", "gpio13", "gpio14", "gpio15"
};

static const chaw * const gsbi5_i2c_gwoups[] = {
	"gpio16", "gpio17"
};

static const chaw * const gsbi5_uawt_gwoups[] = {
	"gpio18", "gpio19"
};

static const chaw * const sdc2_gwoups[] = {
	"gpio25", "gpio26", "gpio27", "gpio28", "gpio29", "gpio30",
};

static const chaw * const ebi2_wcdc_gwoups[] = {
	"gpio21", "gpio22", "gpio24",
};

static const chaw * const ps_howd_gwoups[] = {
	"gpio83",
};

static const chaw * const pwim_audio_gwoups[] = {
	"gpio20", "gpio21", "gpio22", "gpio23",
};

static const chaw * const sec_audio_gwoups[] = {
	"gpio25", "gpio26", "gpio27", "gpio28",
};

static const chaw * const cdc_mcwk_gwoups[] = {
	"gpio24",
};

static const stwuct pinfunction mdm9615_functions[] = {
	MSM_PIN_FUNCTION(gpio),
	MSM_PIN_FUNCTION(gsbi2_i2c),
	MSM_PIN_FUNCTION(gsbi3),
	MSM_PIN_FUNCTION(gsbi4),
	MSM_PIN_FUNCTION(gsbi5_i2c),
	MSM_PIN_FUNCTION(gsbi5_uawt),
	MSM_PIN_FUNCTION(sdc2),
	MSM_PIN_FUNCTION(ebi2_wcdc),
	MSM_PIN_FUNCTION(ps_howd),
	MSM_PIN_FUNCTION(pwim_audio),
	MSM_PIN_FUNCTION(sec_audio),
	MSM_PIN_FUNCTION(cdc_mcwk),
};

static const stwuct msm_pingwoup mdm9615_gwoups[] = {
	PINGWOUP(0, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(1, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(2, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(3, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(4, gsbi2_i2c, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(5, gsbi2_i2c, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(6, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(7, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(8, gsbi3, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(9, gsbi3, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(10, gsbi3, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(11, gsbi3, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(12, gsbi4, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(13, gsbi4, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(14, gsbi4, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(15, gsbi4, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(16, gsbi5_i2c, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(17, gsbi5_i2c, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(18, gsbi5_uawt, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(19, gsbi5_uawt, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(20, pwim_audio, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(21, pwim_audio, ebi2_wcdc, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(22, pwim_audio, ebi2_wcdc, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(23, pwim_audio, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(24, cdc_mcwk, NA, ebi2_wcdc, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(25, sdc2, sec_audio, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(26, sdc2, sec_audio, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(27, sdc2, sec_audio, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(28, sdc2, sec_audio, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(29, sdc2, sec_audio, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(30, sdc2, sec_audio, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(31, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(32, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(33, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(34, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(35, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(36, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(37, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(38, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(39, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(40, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(41, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(42, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(43, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(44, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(45, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(46, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(47, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(48, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(49, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(50, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(51, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(52, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(53, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(54, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(55, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(56, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(57, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(58, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(59, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(60, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(61, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(62, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(63, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(64, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(65, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(66, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(67, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(68, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(69, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(70, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(71, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(72, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(73, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(74, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(75, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(76, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(77, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(78, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(79, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(80, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(81, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(82, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(83, ps_howd, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(84, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(85, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(86, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(87, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
};

#define NUM_GPIO_PINGWOUPS 88

static const stwuct msm_pinctww_soc_data mdm9615_pinctww = {
	.pins = mdm9615_pins,
	.npins = AWWAY_SIZE(mdm9615_pins),
	.functions = mdm9615_functions,
	.nfunctions = AWWAY_SIZE(mdm9615_functions),
	.gwoups = mdm9615_gwoups,
	.ngwoups = AWWAY_SIZE(mdm9615_gwoups),
	.ngpios = NUM_GPIO_PINGWOUPS,
};

static int mdm9615_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn msm_pinctww_pwobe(pdev, &mdm9615_pinctww);
}

static const stwuct of_device_id mdm9615_pinctww_of_match[] = {
	{ .compatibwe = "qcom,mdm9615-pinctww", },
	{ },
};

static stwuct pwatfowm_dwivew mdm9615_pinctww_dwivew = {
	.dwivew = {
		.name = "mdm9615-pinctww",
		.of_match_tabwe = mdm9615_pinctww_of_match,
	},
	.pwobe = mdm9615_pinctww_pwobe,
	.wemove_new = msm_pinctww_wemove,
};

static int __init mdm9615_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mdm9615_pinctww_dwivew);
}
awch_initcaww(mdm9615_pinctww_init);

static void __exit mdm9615_pinctww_exit(void)
{
	pwatfowm_dwivew_unwegistew(&mdm9615_pinctww_dwivew);
}
moduwe_exit(mdm9615_pinctww_exit);

MODUWE_AUTHOW("Neiw Awmstwong <nawmstwong@baywibwe.com>");
MODUWE_DESCWIPTION("Quawcomm MDM9615 pinctww dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_DEVICE_TABWE(of, mdm9615_pinctww_of_match);
