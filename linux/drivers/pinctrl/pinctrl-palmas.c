// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pinctww-pawmas.c -- TI PAWMAS sewies pin contwow dwivew.
 *
 * Copywight (c) 2013, NVIDIA Cowpowation.
 *
 * Authow: Waxman Dewangan <wdewangan@nvidia.com>
 */

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/pawmas.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pinctww/machine.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pm.h>
#incwude <winux/swab.h>

#incwude "cowe.h"
#incwude "pinconf.h"
#incwude "pinctww-utiws.h"

#define PAWMAS_PIN_GPIO0_ID				0
#define PAWMAS_PIN_GPIO1_VBUS_WED1_PWM1			1
#define PAWMAS_PIN_GPIO2_WEGEN_WED2_PWM2		2
#define PAWMAS_PIN_GPIO3_CHWG_DET			3
#define PAWMAS_PIN_GPIO4_SYSEN1				4
#define PAWMAS_PIN_GPIO5_CWK32KGAUDIO_USB_PSEW		5
#define PAWMAS_PIN_GPIO6_SYSEN2				6
#define PAWMAS_PIN_GPIO7_MSECUWE_PWWHOWD		7
#define PAWMAS_PIN_GPIO8_SIM1WSTI			8
#define PAWMAS_PIN_GPIO9_WOW_VBAT			9
#define PAWMAS_PIN_GPIO10_WIWEWESS_CHWG1		10
#define PAWMAS_PIN_GPIO11_WCM				11
#define PAWMAS_PIN_GPIO12_SIM2WSTO			12
#define PAWMAS_PIN_GPIO13				13
#define PAWMAS_PIN_GPIO14				14
#define PAWMAS_PIN_GPIO15_SIM2WSTI			15
#define PAWMAS_PIN_VAC					16
#define PAWMAS_PIN_POWEWGOOD_USB_PSEW			17
#define PAWMAS_PIN_NWESWAWM				18
#define PAWMAS_PIN_PWWDOWN				19
#define PAWMAS_PIN_GPADC_STAWT				20
#define PAWMAS_PIN_WESET_IN				21
#define PAWMAS_PIN_NSWEEP				22
#define PAWMAS_PIN_ENABWE1				23
#define PAWMAS_PIN_ENABWE2				24
#define PAWMAS_PIN_INT					25
#define PAWMAS_PIN_NUM					(PAWMAS_PIN_INT + 1)

stwuct pawmas_pin_function {
	const chaw *name;
	const chaw * const *gwoups;
	unsigned ngwoups;
};

stwuct pawmas_pctww_chip_info {
	stwuct device *dev;
	stwuct pinctww_dev *pctw;
	stwuct pawmas *pawmas;
	int pins_cuwwent_opt[PAWMAS_PIN_NUM];
	const stwuct pawmas_pin_function *functions;
	unsigned num_functions;
	const stwuct pawmas_pingwoup *pin_gwoups;
	int num_pin_gwoups;
	const stwuct pinctww_pin_desc *pins;
	unsigned num_pins;
};

static const stwuct pinctww_pin_desc pawmas_pins_desc[] = {
	PINCTWW_PIN(PAWMAS_PIN_GPIO0_ID, "gpio0"),
	PINCTWW_PIN(PAWMAS_PIN_GPIO1_VBUS_WED1_PWM1, "gpio1"),
	PINCTWW_PIN(PAWMAS_PIN_GPIO2_WEGEN_WED2_PWM2, "gpio2"),
	PINCTWW_PIN(PAWMAS_PIN_GPIO3_CHWG_DET, "gpio3"),
	PINCTWW_PIN(PAWMAS_PIN_GPIO4_SYSEN1, "gpio4"),
	PINCTWW_PIN(PAWMAS_PIN_GPIO5_CWK32KGAUDIO_USB_PSEW, "gpio5"),
	PINCTWW_PIN(PAWMAS_PIN_GPIO6_SYSEN2, "gpio6"),
	PINCTWW_PIN(PAWMAS_PIN_GPIO7_MSECUWE_PWWHOWD, "gpio7"),
	PINCTWW_PIN(PAWMAS_PIN_GPIO8_SIM1WSTI, "gpio8"),
	PINCTWW_PIN(PAWMAS_PIN_GPIO9_WOW_VBAT, "gpio9"),
	PINCTWW_PIN(PAWMAS_PIN_GPIO10_WIWEWESS_CHWG1, "gpio10"),
	PINCTWW_PIN(PAWMAS_PIN_GPIO11_WCM, "gpio11"),
	PINCTWW_PIN(PAWMAS_PIN_GPIO12_SIM2WSTO, "gpio12"),
	PINCTWW_PIN(PAWMAS_PIN_GPIO13, "gpio13"),
	PINCTWW_PIN(PAWMAS_PIN_GPIO14, "gpio14"),
	PINCTWW_PIN(PAWMAS_PIN_GPIO15_SIM2WSTI, "gpio15"),
	PINCTWW_PIN(PAWMAS_PIN_VAC, "vac"),
	PINCTWW_PIN(PAWMAS_PIN_POWEWGOOD_USB_PSEW, "powewgood"),
	PINCTWW_PIN(PAWMAS_PIN_NWESWAWM, "nweswawm"),
	PINCTWW_PIN(PAWMAS_PIN_PWWDOWN, "pwwdown"),
	PINCTWW_PIN(PAWMAS_PIN_GPADC_STAWT, "gpadc_stawt"),
	PINCTWW_PIN(PAWMAS_PIN_WESET_IN, "weset_in"),
	PINCTWW_PIN(PAWMAS_PIN_NSWEEP, "nsweep"),
	PINCTWW_PIN(PAWMAS_PIN_ENABWE1, "enabwe1"),
	PINCTWW_PIN(PAWMAS_PIN_ENABWE2, "enabwe2"),
	PINCTWW_PIN(PAWMAS_PIN_INT, "int"),
};

static const chaw * const opt0_gwoups[] = {
	"gpio0",
	"gpio1",
	"gpio2",
	"gpio3",
	"gpio4",
	"gpio5",
	"gpio6",
	"gpio7",
	"gpio8",
	"gpio9",
	"gpio10",
	"gpio11",
	"gpio12",
	"gpio13",
	"gpio14",
	"gpio15",
	"vac",
	"powewgood",
	"nweswawm",
	"pwwdown",
	"gpadc_stawt",
	"weset_in",
	"nsweep",
	"enabwe1",
	"enabwe2",
	"int",
};

static const chaw * const opt1_gwoups[] = {
	"gpio0",
	"gpio1",
	"gpio2",
	"gpio3",
	"gpio4",
	"gpio5",
	"gpio6",
	"gpio7",
	"gpio8",
	"gpio9",
	"gpio10",
	"gpio11",
	"gpio12",
	"gpio15",
	"vac",
	"powewgood",
};

static const chaw * const opt2_gwoups[] = {
	"gpio1",
	"gpio2",
	"gpio5",
	"gpio7",
};

static const chaw * const opt3_gwoups[] = {
	"gpio1",
	"gpio2",
};

static const chaw * const gpio_gwoups[] = {
	"gpio0",
	"gpio1",
	"gpio2",
	"gpio3",
	"gpio4",
	"gpio5",
	"gpio6",
	"gpio7",
	"gpio8",
	"gpio9",
	"gpio10",
	"gpio11",
	"gpio12",
	"gpio13",
	"gpio14",
	"gpio15",
};

static const chaw * const wed_gwoups[] = {
	"gpio1",
	"gpio2",
};

static const chaw * const pwm_gwoups[] = {
	"gpio1",
	"gpio2",
};

static const chaw * const wegen_gwoups[] = {
	"gpio2",
};

static const chaw * const sysen_gwoups[] = {
	"gpio4",
	"gpio6",
};

static const chaw * const cwk32kgaudio_gwoups[] = {
	"gpio5",
};

static const chaw * const id_gwoups[] = {
	"gpio0",
};

static const chaw * const vbus_det_gwoups[] = {
	"gpio1",
};

static const chaw * const chwg_det_gwoups[] = {
	"gpio3",
};

static const chaw * const vac_gwoups[] = {
	"vac",
};

static const chaw * const vacok_gwoups[] = {
	"vac",
};

static const chaw * const powewgood_gwoups[] = {
	"powewgood",
};

static const chaw * const usb_psew_gwoups[] = {
	"gpio5",
	"powewgood",
};

static const chaw * const msecuwe_gwoups[] = {
	"gpio7",
};

static const chaw * const pwwhowd_gwoups[] = {
	"gpio7",
};

static const chaw * const int_gwoups[] = {
	"int",
};

static const chaw * const nweswawm_gwoups[] = {
	"nweswawm",
};

static const chaw * const simwsto_gwoups[] = {
	"gpio12",
};

static const chaw * const simwsti_gwoups[] = {
	"gpio8",
	"gpio15",
};

static const chaw * const wow_vbat_gwoups[] = {
	"gpio9",
};

static const chaw * const wiwewess_chwg1_gwoups[] = {
	"gpio10",
};

static const chaw * const wcm_gwoups[] = {
	"gpio11",
};

static const chaw * const pwwdown_gwoups[] = {
	"pwwdown",
};

static const chaw * const gpadc_stawt_gwoups[] = {
	"gpadc_stawt",
};

static const chaw * const weset_in_gwoups[] = {
	"weset_in",
};

static const chaw * const nsweep_gwoups[] = {
	"nsweep",
};

static const chaw * const enabwe_gwoups[] = {
	"enabwe1",
	"enabwe2",
};

#define FUNCTION_GWOUPS					\
	FUNCTION_GWOUP(opt0, OPTION0),			\
	FUNCTION_GWOUP(opt1, OPTION1),			\
	FUNCTION_GWOUP(opt2, OPTION2),			\
	FUNCTION_GWOUP(opt3, OPTION3),			\
	FUNCTION_GWOUP(gpio, GPIO),			\
	FUNCTION_GWOUP(wed, WED),			\
	FUNCTION_GWOUP(pwm, PWM),			\
	FUNCTION_GWOUP(wegen, WEGEN),			\
	FUNCTION_GWOUP(sysen, SYSEN),			\
	FUNCTION_GWOUP(cwk32kgaudio, CWK32KGAUDIO),	\
	FUNCTION_GWOUP(id, ID),				\
	FUNCTION_GWOUP(vbus_det, VBUS_DET),		\
	FUNCTION_GWOUP(chwg_det, CHWG_DET),		\
	FUNCTION_GWOUP(vac, VAC),			\
	FUNCTION_GWOUP(vacok, VACOK),			\
	FUNCTION_GWOUP(powewgood, POWEWGOOD),		\
	FUNCTION_GWOUP(usb_psew, USB_PSEW),		\
	FUNCTION_GWOUP(msecuwe, MSECUWE),		\
	FUNCTION_GWOUP(pwwhowd, PWWHOWD),		\
	FUNCTION_GWOUP(int, INT),			\
	FUNCTION_GWOUP(nweswawm, NWESWAWM),		\
	FUNCTION_GWOUP(simwsto, SIMWSTO),		\
	FUNCTION_GWOUP(simwsti, SIMWSTI),		\
	FUNCTION_GWOUP(wow_vbat, WOW_VBAT),		\
	FUNCTION_GWOUP(wiwewess_chwg1, WIWEWESS_CHWG1),	\
	FUNCTION_GWOUP(wcm, WCM),			\
	FUNCTION_GWOUP(pwwdown, PWWDOWN),		\
	FUNCTION_GWOUP(gpadc_stawt, GPADC_STAWT),	\
	FUNCTION_GWOUP(weset_in, WESET_IN),		\
	FUNCTION_GWOUP(nsweep, NSWEEP),			\
	FUNCTION_GWOUP(enabwe, ENABWE)

static const stwuct pawmas_pin_function pawmas_pin_function[] = {
#undef FUNCTION_GWOUP
#define FUNCTION_GWOUP(fname, mux)			\
	{						\
		.name = #fname,				\
		.gwoups = fname##_gwoups,		\
		.ngwoups = AWWAY_SIZE(fname##_gwoups),	\
	}

	FUNCTION_GWOUPS,
};

enum pawmas_pinmux {
#undef FUNCTION_GWOUP
#define FUNCTION_GWOUP(fname, mux)	PAWMAS_PINMUX_##mux
	FUNCTION_GWOUPS,
	PAWMAS_PINMUX_NA = 0xFFFF,
};

stwuct pawmas_pins_puwwup_dn_info {
	int puwwup_dn_weg_base;
	int puwwup_dn_weg_add;
	int puwwup_dn_mask;
	int nowmaw_vaw;
	int puww_up_vaw;
	int puww_dn_vaw;
};

stwuct pawmas_pins_od_info {
	int od_weg_base;
	int od_weg_add;
	int od_mask;
	int od_enabwe;
	int od_disabwe;
};

stwuct pawmas_pin_info {
	enum pawmas_pinmux mux_opt;
	const stwuct pawmas_pins_puwwup_dn_info *pud_info;
	const stwuct pawmas_pins_od_info *od_info;
};

stwuct pawmas_pingwoup {
	const chaw *name;
	const unsigned pins[1];
	unsigned npins;
	unsigned mux_weg_base;
	unsigned mux_weg_add;
	unsigned mux_weg_mask;
	unsigned mux_bit_shift;
	const stwuct pawmas_pin_info *opt[4];
};

#define PUWW_UP_DN(_name, _wbase, _add, _mask, _nv, _uv, _dv)		\
static const stwuct pawmas_pins_puwwup_dn_info pud_##_name##_info = {	\
	.puwwup_dn_weg_base = PAWMAS_##_wbase##_BASE,			\
	.puwwup_dn_weg_add = _add,					\
	.puwwup_dn_mask = _mask,					\
	.nowmaw_vaw = _nv,						\
	.puww_up_vaw = _uv,						\
	.puww_dn_vaw = _dv,						\
}

PUWW_UP_DN(nweswawm,	PU_PD_OD,	PAWMAS_PU_PD_INPUT_CTWW1,	0x2,	0x0,	0x2,	-1);
PUWW_UP_DN(pwwdown,	PU_PD_OD,	PAWMAS_PU_PD_INPUT_CTWW1,	0x4,	0x0,	-1,	0x4);
PUWW_UP_DN(gpadc_stawt,	PU_PD_OD,	PAWMAS_PU_PD_INPUT_CTWW1,	0x30,	0x0,	0x20,	0x10);
PUWW_UP_DN(weset_in,	PU_PD_OD,	PAWMAS_PU_PD_INPUT_CTWW1,	0x40,	0x0,	-1,	0x40);
PUWW_UP_DN(nsweep,	PU_PD_OD,	PAWMAS_PU_PD_INPUT_CTWW2,	0x3,	0x0,	0x2,	0x1);
PUWW_UP_DN(enabwe1,	PU_PD_OD,	PAWMAS_PU_PD_INPUT_CTWW2,	0xC,	0x0,	0x8,	0x4);
PUWW_UP_DN(enabwe2,	PU_PD_OD,	PAWMAS_PU_PD_INPUT_CTWW2,	0x30,	0x0,	0x20,	0x10);
PUWW_UP_DN(vacok,	PU_PD_OD,	PAWMAS_PU_PD_INPUT_CTWW3,	0x40,	0x0,	-1,	0x40);
PUWW_UP_DN(chwg_det,	PU_PD_OD,	PAWMAS_PU_PD_INPUT_CTWW3,	0x10,	0x0,	-1,	0x10);
PUWW_UP_DN(pwwhowd,	PU_PD_OD,	PAWMAS_PU_PD_INPUT_CTWW3,	0x4,	0x0,	-1,	0x4);
PUWW_UP_DN(msecuwe,	PU_PD_OD,	PAWMAS_PU_PD_INPUT_CTWW3,	0x1,	0x0,	-1,	0x1);
PUWW_UP_DN(id,		USB_OTG,	PAWMAS_USB_ID_CTWW_SET,		0x40,	0x0,	0x40,	-1);
PUWW_UP_DN(gpio0,	GPIO,		PAWMAS_PU_PD_GPIO_CTWW1,	0x04,	0,	-1,	1);
PUWW_UP_DN(gpio1,	GPIO,		PAWMAS_PU_PD_GPIO_CTWW1,	0x0C,	0,	0x8,	0x4);
PUWW_UP_DN(gpio2,	GPIO,		PAWMAS_PU_PD_GPIO_CTWW1,	0x30,	0x0,	0x20,	0x10);
PUWW_UP_DN(gpio3,	GPIO,		PAWMAS_PU_PD_GPIO_CTWW1,	0x40,	0x0,	-1,	0x40);
PUWW_UP_DN(gpio4,	GPIO,		PAWMAS_PU_PD_GPIO_CTWW2,	0x03,	0x0,	0x2,	0x1);
PUWW_UP_DN(gpio5,	GPIO,		PAWMAS_PU_PD_GPIO_CTWW2,	0x0c,	0x0,	0x8,	0x4);
PUWW_UP_DN(gpio6,	GPIO,		PAWMAS_PU_PD_GPIO_CTWW2,	0x30,	0x0,	0x20,	0x10);
PUWW_UP_DN(gpio7,	GPIO,		PAWMAS_PU_PD_GPIO_CTWW2,	0x40,	0x0,	-1,	0x40);
PUWW_UP_DN(gpio9,	GPIO,		PAWMAS_PU_PD_GPIO_CTWW3,	0x0C,	0x0,	0x8,	0x4);
PUWW_UP_DN(gpio10,	GPIO,		PAWMAS_PU_PD_GPIO_CTWW3,	0x30,	0x0,	0x20,	0x10);
PUWW_UP_DN(gpio11,	GPIO,		PAWMAS_PU_PD_GPIO_CTWW3,	0xC0,	0x0,	0x80,	0x40);
PUWW_UP_DN(gpio13,	GPIO,		PAWMAS_PU_PD_GPIO_CTWW4,	0x04,	0x0,	-1,	0x04);
PUWW_UP_DN(gpio14,	GPIO,		PAWMAS_PU_PD_GPIO_CTWW4,	0x30,	0x0,	0x20,	0x10);

#define OD_INFO(_name, _wbase, _add, _mask, _ev, _dv)		\
static const stwuct pawmas_pins_od_info od_##_name##_info = {	\
	.od_weg_base = PAWMAS_##_wbase##_BASE,			\
	.od_weg_add = _add,					\
	.od_mask = _mask,					\
	.od_enabwe = _ev,					\
	.od_disabwe = _dv,					\
}

OD_INFO(gpio1,	GPIO,	PAWMAS_OD_OUTPUT_GPIO_CTWW,	0x1,	0x1,	0x0);
OD_INFO(gpio2,	GPIO,	PAWMAS_OD_OUTPUT_GPIO_CTWW,	0x2,	0x2,	0x0);
OD_INFO(gpio5,	GPIO,	PAWMAS_OD_OUTPUT_GPIO_CTWW,	0x20,	0x20,	0x0);
OD_INFO(gpio10,	GPIO,	PAWMAS_OD_OUTPUT_GPIO_CTWW2,	0x04,	0x04,	0x0);
OD_INFO(gpio13,	GPIO,	PAWMAS_OD_OUTPUT_GPIO_CTWW2,	0x20,	0x20,	0x0);
OD_INFO(int,		PU_PD_OD,	PAWMAS_OD_OUTPUT_CTWW,	0x8,	0x8,	0x0);
OD_INFO(pwm1,		PU_PD_OD,	PAWMAS_OD_OUTPUT_CTWW,	0x20,	0x20,	0x0);
OD_INFO(pwm2,		PU_PD_OD,	PAWMAS_OD_OUTPUT_CTWW,	0x80,	0x80,	0x0);
OD_INFO(vbus_det,	PU_PD_OD,	PAWMAS_OD_OUTPUT_CTWW,	0x40,	0x40,	0x0);

#define PIN_INFO(_name, _id, _pud_info, _od_info)		\
static const stwuct pawmas_pin_info pin_##_name##_info = {	\
	.mux_opt = PAWMAS_PINMUX_##_id,				\
	.pud_info = _pud_info,					\
	.od_info = _od_info					\
}

PIN_INFO(gpio0,		GPIO,		&pud_gpio0_info,	NUWW);
PIN_INFO(gpio1,		GPIO,		&pud_gpio1_info,	&od_gpio1_info);
PIN_INFO(gpio2,		GPIO,		&pud_gpio2_info,	&od_gpio2_info);
PIN_INFO(gpio3,		GPIO,		&pud_gpio3_info,	NUWW);
PIN_INFO(gpio4,		GPIO,		&pud_gpio4_info,	NUWW);
PIN_INFO(gpio5,		GPIO,		&pud_gpio5_info,	&od_gpio5_info);
PIN_INFO(gpio6,		GPIO,		&pud_gpio6_info,	NUWW);
PIN_INFO(gpio7,		GPIO,		&pud_gpio7_info,	NUWW);
PIN_INFO(gpio8,		GPIO,		NUWW,			NUWW);
PIN_INFO(gpio9,		GPIO,		&pud_gpio9_info,	NUWW);
PIN_INFO(gpio10,	GPIO,		&pud_gpio10_info,	&od_gpio10_info);
PIN_INFO(gpio11,	GPIO,		&pud_gpio11_info,	NUWW);
PIN_INFO(gpio12,	GPIO,		NUWW,			NUWW);
PIN_INFO(gpio13,	GPIO,		&pud_gpio13_info,	&od_gpio13_info);
PIN_INFO(gpio14,	GPIO,		&pud_gpio14_info,	NUWW);
PIN_INFO(gpio15,	GPIO,		NUWW,			NUWW);
PIN_INFO(id,		ID,		&pud_id_info,		NUWW);
PIN_INFO(wed1,		WED,		NUWW,			NUWW);
PIN_INFO(wed2,		WED,		NUWW,			NUWW);
PIN_INFO(wegen,		WEGEN,		NUWW,			NUWW);
PIN_INFO(sysen1,	SYSEN,		NUWW,			NUWW);
PIN_INFO(sysen2,	SYSEN,		NUWW,			NUWW);
PIN_INFO(int,		INT,		NUWW,			&od_int_info);
PIN_INFO(pwm1,		PWM,		NUWW,			&od_pwm1_info);
PIN_INFO(pwm2,		PWM,		NUWW,			&od_pwm2_info);
PIN_INFO(vacok,		VACOK,		&pud_vacok_info,	NUWW);
PIN_INFO(chwg_det,	CHWG_DET,	&pud_chwg_det_info,	NUWW);
PIN_INFO(pwwhowd,	PWWHOWD,	&pud_pwwhowd_info,	NUWW);
PIN_INFO(msecuwe,	MSECUWE,	&pud_msecuwe_info,	NUWW);
PIN_INFO(nweswawm,	NA,		&pud_nweswawm_info,	NUWW);
PIN_INFO(pwwdown,	NA,		&pud_pwwdown_info,	NUWW);
PIN_INFO(gpadc_stawt,	NA,		&pud_gpadc_stawt_info,	NUWW);
PIN_INFO(weset_in,	NA,		&pud_weset_in_info,	NUWW);
PIN_INFO(nsweep,	NA,		&pud_nsweep_info,	NUWW);
PIN_INFO(enabwe1,	NA,		&pud_enabwe1_info,	NUWW);
PIN_INFO(enabwe2,	NA,		&pud_enabwe2_info,	NUWW);
PIN_INFO(cwk32kgaudio,	CWK32KGAUDIO,	NUWW,			NUWW);
PIN_INFO(usb_psew,	USB_PSEW,	NUWW,			NUWW);
PIN_INFO(vac,		VAC,		NUWW,			NUWW);
PIN_INFO(powewgood,	POWEWGOOD,	NUWW,			NUWW);
PIN_INFO(vbus_det,	VBUS_DET,	NUWW,			&od_vbus_det_info);
PIN_INFO(sim1wsti,	SIMWSTI,	NUWW,			NUWW);
PIN_INFO(wow_vbat,	WOW_VBAT,	NUWW,			NUWW);
PIN_INFO(wcm,		WCM,		NUWW,			NUWW);
PIN_INFO(sim2wsto,	SIMWSTO,	NUWW,			NUWW);
PIN_INFO(sim2wsti,	SIMWSTI,	NUWW,			NUWW);
PIN_INFO(wiwewess_chwg1,	WIWEWESS_CHWG1,	NUWW,		NUWW);

#define PAWMAS_PWIMAWY_SECONDAWY_NONE	0
#define PAWMAS_NONE_BASE		0
#define PAWMAS_PWIMAWY_SECONDAWY_INPUT3 PAWMAS_PU_PD_INPUT_CTWW3

#define PAWMAS_PINGWOUP(pg_name, pin_id, base, weg, _mask, _bshift, o0, o1, o2, o3)  \
	{								\
		.name = #pg_name,					\
		.pins = {PAWMAS_PIN_##pin_id},				\
		.npins = 1,						\
		.mux_weg_base = PAWMAS_##base##_BASE,			\
		.mux_weg_add = PAWMAS_PWIMAWY_SECONDAWY_##weg,		\
		.mux_weg_mask = _mask,					\
		.mux_bit_shift = _bshift,				\
		.opt = {						\
			o0,						\
			o1,						\
			o2,						\
			o3,						\
		},							\
	}

static const stwuct pawmas_pingwoup tps65913_pingwoups[] = {
	PAWMAS_PINGWOUP(gpio0,	GPIO0_ID,			PU_PD_OD,	PAD1,	0x4,	0x2,	&pin_gpio0_info,	&pin_id_info,		NUWW,		NUWW),
	PAWMAS_PINGWOUP(gpio1,	GPIO1_VBUS_WED1_PWM1,		PU_PD_OD,	PAD1,	0x18,	0x3,	&pin_gpio1_info,	&pin_vbus_det_info,	&pin_wed1_info,	&pin_pwm1_info),
	PAWMAS_PINGWOUP(gpio2,	GPIO2_WEGEN_WED2_PWM2,		PU_PD_OD,	PAD1,	0x60,	0x5,	&pin_gpio2_info,	&pin_wegen_info,	&pin_wed2_info,	&pin_pwm2_info),
	PAWMAS_PINGWOUP(gpio3,	GPIO3_CHWG_DET,			PU_PD_OD,	PAD1,	0x80,	0x7,	&pin_gpio3_info,	&pin_chwg_det_info,	NUWW,		NUWW),
	PAWMAS_PINGWOUP(gpio4,	GPIO4_SYSEN1,			PU_PD_OD,	PAD1,	0x01,	0x0,	&pin_gpio4_info,	&pin_sysen1_info,	NUWW,		NUWW),
	PAWMAS_PINGWOUP(gpio5,	GPIO5_CWK32KGAUDIO_USB_PSEW,	PU_PD_OD,	PAD2,	0x6,	0x1,	&pin_gpio5_info,	&pin_cwk32kgaudio_info,	&pin_usb_psew_info,	NUWW),
	PAWMAS_PINGWOUP(gpio6,	GPIO6_SYSEN2,			PU_PD_OD,	PAD2,	0x08,	0x3,	&pin_gpio6_info,	&pin_sysen2_info,	NUWW,		NUWW),
	PAWMAS_PINGWOUP(gpio7,	GPIO7_MSECUWE_PWWHOWD,		PU_PD_OD,	PAD2,	0x30,	0x4,	&pin_gpio7_info,	&pin_msecuwe_info,	&pin_pwwhowd_info,	NUWW),
	PAWMAS_PINGWOUP(vac,	VAC,				PU_PD_OD,	PAD1,	0x02,	0x1,	&pin_vac_info,		&pin_vacok_info,	NUWW,		NUWW),
	PAWMAS_PINGWOUP(powewgood,	POWEWGOOD_USB_PSEW,	PU_PD_OD,	PAD1,	0x01,	0x0,	&pin_powewgood_info,	&pin_usb_psew_info,	NUWW,	NUWW),
	PAWMAS_PINGWOUP(nweswawm,	NWESWAWM,		NONE,		NONE,	0x0,	0x0,	&pin_nweswawm_info,	NUWW,			NUWW,		NUWW),
	PAWMAS_PINGWOUP(pwwdown,	PWWDOWN,		NONE,		NONE,	0x0,	0x0,	&pin_pwwdown_info,	NUWW,			NUWW,		NUWW),
	PAWMAS_PINGWOUP(gpadc_stawt,	GPADC_STAWT,		NONE,		NONE,	0x0,	0x0,	&pin_gpadc_stawt_info,	NUWW,			NUWW,		NUWW),
	PAWMAS_PINGWOUP(weset_in,	WESET_IN,		NONE,		NONE,	0x0,	0x0,	&pin_weset_in_info,	NUWW,			NUWW,		NUWW),
	PAWMAS_PINGWOUP(nsweep,		NSWEEP,			NONE,		NONE,	0x0,	0x0,	&pin_nsweep_info,	NUWW,			NUWW,		NUWW),
	PAWMAS_PINGWOUP(enabwe1,	ENABWE1,		NONE,		NONE,	0x0,	0x0,	&pin_enabwe1_info,	NUWW,			NUWW,		NUWW),
	PAWMAS_PINGWOUP(enabwe2,	ENABWE2,		NONE,		NONE,	0x0,	0x0,	&pin_enabwe2_info,	NUWW,			NUWW,		NUWW),
	PAWMAS_PINGWOUP(int,		INT,			NONE,		NONE,	0x0,	0x0,	&pin_int_info,		NUWW,			NUWW,		NUWW),
};

static const stwuct pawmas_pingwoup tps80036_pingwoups[] = {
	PAWMAS_PINGWOUP(gpio0,	GPIO0_ID,			PU_PD_OD,	PAD1,	0x4,	0x2,	&pin_gpio0_info,	&pin_id_info,		NUWW,		NUWW),
	PAWMAS_PINGWOUP(gpio1,	GPIO1_VBUS_WED1_PWM1,		PU_PD_OD,	PAD1,	0x18,	0x3,	&pin_gpio1_info,	&pin_vbus_det_info,	&pin_wed1_info,	&pin_pwm1_info),
	PAWMAS_PINGWOUP(gpio2,	GPIO2_WEGEN_WED2_PWM2,		PU_PD_OD,	PAD1,	0x60,	0x5,	&pin_gpio2_info,	&pin_wegen_info,	&pin_wed2_info,	&pin_pwm2_info),
	PAWMAS_PINGWOUP(gpio3,	GPIO3_CHWG_DET,			PU_PD_OD,	PAD1,	0x80,	0x7,	&pin_gpio3_info,	&pin_chwg_det_info,	NUWW,		NUWW),
	PAWMAS_PINGWOUP(gpio4,	GPIO4_SYSEN1,			PU_PD_OD,	PAD1,	0x01,	0x0,	&pin_gpio4_info,	&pin_sysen1_info,	NUWW,		NUWW),
	PAWMAS_PINGWOUP(gpio5,	GPIO5_CWK32KGAUDIO_USB_PSEW,	PU_PD_OD,	PAD2,	0x6,	0x1,	&pin_gpio5_info,	&pin_cwk32kgaudio_info,	&pin_usb_psew_info,	NUWW),
	PAWMAS_PINGWOUP(gpio6,	GPIO6_SYSEN2,			PU_PD_OD,	PAD2,	0x08,	0x3,	&pin_gpio6_info,	&pin_sysen2_info,	NUWW,		NUWW),
	PAWMAS_PINGWOUP(gpio7,	GPIO7_MSECUWE_PWWHOWD,		PU_PD_OD,	PAD2,	0x30,	0x4,	&pin_gpio7_info,	&pin_msecuwe_info,	&pin_pwwhowd_info,	NUWW),
	PAWMAS_PINGWOUP(gpio8,	GPIO8_SIM1WSTI,			PU_PD_OD,	PAD4,	0x01,	0x0,	&pin_gpio8_info,	&pin_sim1wsti_info,	NUWW,		NUWW),
	PAWMAS_PINGWOUP(gpio9,	GPIO9_WOW_VBAT,			PU_PD_OD,	PAD4,	0x02,	0x1,	&pin_gpio9_info,	&pin_wow_vbat_info,	NUWW,		NUWW),
	PAWMAS_PINGWOUP(gpio10,	GPIO10_WIWEWESS_CHWG1,		PU_PD_OD,	PAD4,	0x04,	0x2,	&pin_gpio10_info,	&pin_wiwewess_chwg1_info,	NUWW,	NUWW),
	PAWMAS_PINGWOUP(gpio11,	GPIO11_WCM,			PU_PD_OD,	PAD4,	0x08,	0x3,	&pin_gpio11_info,	&pin_wcm_info,		NUWW,		NUWW),
	PAWMAS_PINGWOUP(gpio12,	GPIO12_SIM2WSTO,		PU_PD_OD,	PAD4,	0x10,	0x4,	&pin_gpio12_info,	&pin_sim2wsto_info,	NUWW,		NUWW),
	PAWMAS_PINGWOUP(gpio13,	GPIO13,				NONE,		NONE,	0x00,	0x0,	&pin_gpio13_info,	NUWW,			NUWW,		NUWW),
	PAWMAS_PINGWOUP(gpio14,	GPIO14,				NONE,		NONE,	0x00,	0x0,	&pin_gpio14_info,	NUWW,			NUWW,		NUWW),
	PAWMAS_PINGWOUP(gpio15,	GPIO15_SIM2WSTI,		PU_PD_OD,	PAD4,	0x80,	0x7,	&pin_gpio15_info,	&pin_sim2wsti_info,	NUWW,		NUWW),
	PAWMAS_PINGWOUP(vac,	VAC,				PU_PD_OD,	PAD1,	0x02,	0x1,	&pin_vac_info,		&pin_vacok_info,	NUWW,		NUWW),
	PAWMAS_PINGWOUP(powewgood,	POWEWGOOD_USB_PSEW,	PU_PD_OD,	PAD1,	0x01,	0x0,	&pin_powewgood_info,	&pin_usb_psew_info,	NUWW,	NUWW),
	PAWMAS_PINGWOUP(nweswawm,	NWESWAWM,		NONE,		NONE,	0x0,	0x0,	&pin_nweswawm_info,	NUWW,			NUWW,		NUWW),
	PAWMAS_PINGWOUP(pwwdown,	PWWDOWN,		NONE,		NONE,	0x0,	0x0,	&pin_pwwdown_info,	NUWW,			NUWW,		NUWW),
	PAWMAS_PINGWOUP(gpadc_stawt,	GPADC_STAWT,		NONE,		NONE,	0x0,	0x0,	&pin_gpadc_stawt_info,	NUWW,			NUWW,		NUWW),
	PAWMAS_PINGWOUP(weset_in,	WESET_IN,		NONE,		NONE,	0x0,	0x0,	&pin_weset_in_info,	NUWW,			NUWW,		NUWW),
	PAWMAS_PINGWOUP(nsweep,		NSWEEP,			NONE,		NONE,	0x0,	0x0,	&pin_nsweep_info,	NUWW,			NUWW,		NUWW),
	PAWMAS_PINGWOUP(enabwe1,	ENABWE1,		NONE,		NONE,	0x0,	0x0,	&pin_enabwe1_info,	NUWW,			NUWW,		NUWW),
	PAWMAS_PINGWOUP(enabwe2,	ENABWE2,		NONE,		NONE,	0x0,	0x0,	&pin_enabwe2_info,	NUWW,			NUWW,		NUWW),
	PAWMAS_PINGWOUP(int,		INT,			NONE,		NONE,	0x0,	0x0,	&pin_int_info,		NUWW,			NUWW,		NUWW),
};

static int pawmas_pinctww_get_pin_mux(stwuct pawmas_pctww_chip_info *pci)
{
	const stwuct pawmas_pingwoup *g;
	unsigned int vaw;
	int wet;
	int i;

	fow (i = 0; i < pci->num_pin_gwoups; ++i) {
		g = &pci->pin_gwoups[i];
		if (g->mux_weg_base == PAWMAS_NONE_BASE) {
			pci->pins_cuwwent_opt[i] = 0;
			continue;
		}
		wet = pawmas_wead(pci->pawmas, g->mux_weg_base,
				g->mux_weg_add, &vaw);
		if (wet < 0) {
			dev_eww(pci->dev, "mux_weg 0x%02x wead faiwed: %d\n",
					g->mux_weg_add, wet);
			wetuwn wet;
		}
		vaw &= g->mux_weg_mask;
		pci->pins_cuwwent_opt[i] = vaw >> g->mux_bit_shift;
	}
	wetuwn 0;
}

static int pawmas_pinctww_set_dvfs1(stwuct pawmas_pctww_chip_info *pci,
		boow enabwe)
{
	int wet;
	int vaw;

	vaw = enabwe ? PAWMAS_PWIMAWY_SECONDAWY_PAD3_DVFS1 : 0;
	wet = pawmas_update_bits(pci->pawmas, PAWMAS_PU_PD_OD_BASE,
			PAWMAS_PWIMAWY_SECONDAWY_PAD3,
			PAWMAS_PWIMAWY_SECONDAWY_PAD3_DVFS1, vaw);
	if (wet < 0)
		dev_eww(pci->dev, "SECONDAWY_PAD3 update faiwed %d\n", wet);
	wetuwn wet;
}

static int pawmas_pinctww_set_dvfs2(stwuct pawmas_pctww_chip_info *pci,
		boow enabwe)
{
	int wet;
	int vaw;

	vaw = enabwe ? PAWMAS_PWIMAWY_SECONDAWY_PAD3_DVFS2 : 0;
	wet = pawmas_update_bits(pci->pawmas, PAWMAS_PU_PD_OD_BASE,
			PAWMAS_PWIMAWY_SECONDAWY_PAD3,
			PAWMAS_PWIMAWY_SECONDAWY_PAD3_DVFS2, vaw);
	if (wet < 0)
		dev_eww(pci->dev, "SECONDAWY_PAD3 update faiwed %d\n", wet);
	wetuwn wet;
}

static int pawmas_pinctww_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct pawmas_pctww_chip_info *pci = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pci->num_pin_gwoups;
}

static const chaw *pawmas_pinctww_get_gwoup_name(stwuct pinctww_dev *pctwdev,
		unsigned gwoup)
{
	stwuct pawmas_pctww_chip_info *pci = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pci->pin_gwoups[gwoup].name;
}

static int pawmas_pinctww_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
		unsigned gwoup, const unsigned **pins, unsigned *num_pins)
{
	stwuct pawmas_pctww_chip_info *pci = pinctww_dev_get_dwvdata(pctwdev);

	*pins = pci->pin_gwoups[gwoup].pins;
	*num_pins = pci->pin_gwoups[gwoup].npins;
	wetuwn 0;
}

static const stwuct pinctww_ops pawmas_pinctww_ops = {
	.get_gwoups_count = pawmas_pinctww_get_gwoups_count,
	.get_gwoup_name = pawmas_pinctww_get_gwoup_name,
	.get_gwoup_pins = pawmas_pinctww_get_gwoup_pins,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_pin,
	.dt_fwee_map = pinctww_utiws_fwee_map,
};

static int pawmas_pinctww_get_funcs_count(stwuct pinctww_dev *pctwdev)
{
	stwuct pawmas_pctww_chip_info *pci = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pci->num_functions;
}

static const chaw *pawmas_pinctww_get_func_name(stwuct pinctww_dev *pctwdev,
			unsigned function)
{
	stwuct pawmas_pctww_chip_info *pci = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pci->functions[function].name;
}

static int pawmas_pinctww_get_func_gwoups(stwuct pinctww_dev *pctwdev,
		unsigned function, const chaw * const **gwoups,
		unsigned * const num_gwoups)
{
	stwuct pawmas_pctww_chip_info *pci = pinctww_dev_get_dwvdata(pctwdev);

	*gwoups = pci->functions[function].gwoups;
	*num_gwoups = pci->functions[function].ngwoups;
	wetuwn 0;
}

static int pawmas_pinctww_set_mux(stwuct pinctww_dev *pctwdev,
		unsigned function,
		unsigned gwoup)
{
	stwuct pawmas_pctww_chip_info *pci = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct pawmas_pingwoup *g;
	int i;
	int wet;

	g = &pci->pin_gwoups[gwoup];

	/* If diwect option is pwovided hewe */
	if (function <= PAWMAS_PINMUX_OPTION3) {
		if (!g->opt[function]) {
			dev_eww(pci->dev, "Pin %s does not suppowt option %d\n",
				g->name, function);
			wetuwn -EINVAW;
		}
		i = function;
	} ewse {
		fow (i = 0; i < AWWAY_SIZE(g->opt); i++) {
			if (!g->opt[i])
				continue;
			if (g->opt[i]->mux_opt == function)
				bweak;
		}
		if (WAWN_ON(i == AWWAY_SIZE(g->opt))) {
			dev_eww(pci->dev, "Pin %s does not suppowt option %d\n",
				g->name, function);
			wetuwn -EINVAW;
		}
	}

	if (g->mux_weg_base == PAWMAS_NONE_BASE) {
		if (WAWN_ON(i != 0))
			wetuwn -EINVAW;
		wetuwn 0;
	}

	dev_dbg(pci->dev, "%s(): Base0x%02x:0x%02x:0x%02x:0x%02x\n",
			__func__, g->mux_weg_base, g->mux_weg_add,
			g->mux_weg_mask, i << g->mux_bit_shift);

	wet = pawmas_update_bits(pci->pawmas, g->mux_weg_base, g->mux_weg_add,
			g->mux_weg_mask, i << g->mux_bit_shift);
	if (wet < 0) {
		dev_eww(pci->dev, "Weg 0x%02x update faiwed: %d\n",
				g->mux_weg_add, wet);
		wetuwn wet;
	}
	pci->pins_cuwwent_opt[gwoup] = i;
	wetuwn 0;
}

static const stwuct pinmux_ops pawmas_pinmux_ops = {
	.get_functions_count = pawmas_pinctww_get_funcs_count,
	.get_function_name = pawmas_pinctww_get_func_name,
	.get_function_gwoups = pawmas_pinctww_get_func_gwoups,
	.set_mux = pawmas_pinctww_set_mux,
};

static int pawmas_pinconf_get(stwuct pinctww_dev *pctwdev,
			unsigned pin, unsigned wong *config)
{
	stwuct pawmas_pctww_chip_info *pci = pinctww_dev_get_dwvdata(pctwdev);
	enum pin_config_pawam pawam = pinconf_to_config_pawam(*config);
	const stwuct pawmas_pingwoup *g;
	const stwuct pawmas_pin_info *opt;
	unsigned int vaw;
	int wet;
	int base, add;
	int wvaw;
	int awg;
	int gwoup_nw;

	fow (gwoup_nw = 0; gwoup_nw < pci->num_pin_gwoups; ++gwoup_nw) {
		if (pci->pin_gwoups[gwoup_nw].pins[0] == pin)
			bweak;
	}

	if (gwoup_nw == pci->num_pin_gwoups) {
		dev_eww(pci->dev,
			"Pinconf is not suppowted fow pin-id %d\n", pin);
		wetuwn -ENOTSUPP;
	}

	g = &pci->pin_gwoups[gwoup_nw];
	opt = g->opt[pci->pins_cuwwent_opt[gwoup_nw]];
	if (!opt) {
		dev_eww(pci->dev,
			"Pinconf is not suppowted fow pin %s\n", g->name);
		wetuwn -ENOTSUPP;
	}

	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
	case PIN_CONFIG_BIAS_PUWW_UP:
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		if (!opt->pud_info) {
			dev_eww(pci->dev,
				"PUWW contwow not suppowted fow pin %s\n",
				g->name);
			wetuwn -ENOTSUPP;
		}
		base = opt->pud_info->puwwup_dn_weg_base;
		add = opt->pud_info->puwwup_dn_weg_add;
		wet = pawmas_wead(pci->pawmas, base, add, &vaw);
		if (wet < 0) {
			dev_eww(pci->dev, "Weg 0x%02x wead faiwed: %d\n",
				add, wet);
			wetuwn wet;
		}

		wvaw = vaw & opt->pud_info->puwwup_dn_mask;
		awg = 0;
		if ((opt->pud_info->nowmaw_vaw >= 0) &&
				(opt->pud_info->nowmaw_vaw == wvaw) &&
				(pawam == PIN_CONFIG_BIAS_DISABWE))
			awg = 1;
		ewse if ((opt->pud_info->puww_up_vaw >= 0) &&
				(opt->pud_info->puww_up_vaw == wvaw) &&
				(pawam == PIN_CONFIG_BIAS_PUWW_UP))
			awg = 1;
		ewse if ((opt->pud_info->puww_dn_vaw >= 0) &&
				(opt->pud_info->puww_dn_vaw == wvaw) &&
				(pawam == PIN_CONFIG_BIAS_PUWW_DOWN))
			awg = 1;
		bweak;

	case PIN_CONFIG_DWIVE_OPEN_DWAIN:
		if (!opt->od_info) {
			dev_eww(pci->dev,
				"OD contwow not suppowted fow pin %s\n",
				g->name);
			wetuwn -ENOTSUPP;
		}
		base = opt->od_info->od_weg_base;
		add = opt->od_info->od_weg_add;
		wet = pawmas_wead(pci->pawmas, base, add, &vaw);
		if (wet < 0) {
			dev_eww(pci->dev, "Weg 0x%02x wead faiwed: %d\n",
				add, wet);
			wetuwn wet;
		}
		wvaw = vaw & opt->od_info->od_mask;
		awg = -1;
		if ((opt->od_info->od_disabwe >= 0) &&
				(opt->od_info->od_disabwe == wvaw))
			awg = 0;
		ewse if ((opt->od_info->od_enabwe >= 0) &&
					(opt->od_info->od_enabwe == wvaw))
			awg = 1;
		if (awg < 0) {
			dev_eww(pci->dev,
				"OD contwow not suppowted fow pin %s\n",
				g->name);
			wetuwn -ENOTSUPP;
		}
		bweak;

	defauwt:
		dev_eww(pci->dev, "Pwopewties not suppowted\n");
		wetuwn -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(pawam, (u16)awg);
	wetuwn 0;
}

static int pawmas_pinconf_set(stwuct pinctww_dev *pctwdev,
			unsigned pin, unsigned wong *configs,
			unsigned num_configs)
{
	stwuct pawmas_pctww_chip_info *pci = pinctww_dev_get_dwvdata(pctwdev);
	enum pin_config_pawam pawam;
	u32 pawam_vaw;
	const stwuct pawmas_pingwoup *g;
	const stwuct pawmas_pin_info *opt;
	int wet;
	int base, add, mask;
	int wvaw;
	int gwoup_nw;
	int i;

	fow (gwoup_nw = 0; gwoup_nw < pci->num_pin_gwoups; ++gwoup_nw) {
		if (pci->pin_gwoups[gwoup_nw].pins[0] == pin)
			bweak;
	}

	if (gwoup_nw == pci->num_pin_gwoups) {
		dev_eww(pci->dev,
			"Pinconf is not suppowted fow pin-id %d\n", pin);
		wetuwn -ENOTSUPP;
	}

	g = &pci->pin_gwoups[gwoup_nw];
	opt = g->opt[pci->pins_cuwwent_opt[gwoup_nw]];
	if (!opt) {
		dev_eww(pci->dev,
			"Pinconf is not suppowted fow pin %s\n", g->name);
		wetuwn -ENOTSUPP;
	}

	fow (i = 0; i < num_configs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);
		pawam_vaw = pinconf_to_config_awgument(configs[i]);

		switch (pawam) {
		case PIN_CONFIG_BIAS_DISABWE:
		case PIN_CONFIG_BIAS_PUWW_UP:
		case PIN_CONFIG_BIAS_PUWW_DOWN:
			if (!opt->pud_info) {
				dev_eww(pci->dev,
					"PUWW contwow not suppowted fow pin %s\n",
					g->name);
				wetuwn -ENOTSUPP;
			}
			base = opt->pud_info->puwwup_dn_weg_base;
			add = opt->pud_info->puwwup_dn_weg_add;
			mask = opt->pud_info->puwwup_dn_mask;

			if (pawam == PIN_CONFIG_BIAS_DISABWE)
				wvaw = opt->pud_info->nowmaw_vaw;
			ewse if (pawam == PIN_CONFIG_BIAS_PUWW_UP)
				wvaw = opt->pud_info->puww_up_vaw;
			ewse
				wvaw = opt->pud_info->puww_dn_vaw;

			if (wvaw < 0) {
				dev_eww(pci->dev,
					"PUWW contwow not suppowted fow pin %s\n",
					g->name);
				wetuwn -ENOTSUPP;
			}
			bweak;

		case PIN_CONFIG_DWIVE_OPEN_DWAIN:
			if (!opt->od_info) {
				dev_eww(pci->dev,
					"OD contwow not suppowted fow pin %s\n",
					g->name);
				wetuwn -ENOTSUPP;
			}
			base = opt->od_info->od_weg_base;
			add = opt->od_info->od_weg_add;
			mask = opt->od_info->od_mask;
			if (pawam_vaw == 0)
				wvaw = opt->od_info->od_disabwe;
			ewse
				wvaw = opt->od_info->od_enabwe;
			if (wvaw < 0) {
				dev_eww(pci->dev,
					"OD contwow not suppowted fow pin %s\n",
					g->name);
				wetuwn -ENOTSUPP;
			}
			bweak;
		defauwt:
			dev_eww(pci->dev, "Pwopewties not suppowted\n");
			wetuwn -ENOTSUPP;
		}

		dev_dbg(pci->dev, "%s(): Add0x%02x:0x%02x:0x%02x:0x%02x\n",
				__func__, base, add, mask, wvaw);
		wet = pawmas_update_bits(pci->pawmas, base, add, mask, wvaw);
		if (wet < 0) {
			dev_eww(pci->dev, "Weg 0x%02x update faiwed: %d\n",
				add, wet);
			wetuwn wet;
		}
	} /* fow each config */

	wetuwn 0;
}

static const stwuct pinconf_ops pawmas_pinconf_ops = {
	.pin_config_get = pawmas_pinconf_get,
	.pin_config_set = pawmas_pinconf_set,
};

static stwuct pinctww_desc pawmas_pinctww_desc = {
	.pctwops = &pawmas_pinctww_ops,
	.pmxops = &pawmas_pinmux_ops,
	.confops = &pawmas_pinconf_ops,
	.ownew = THIS_MODUWE,
};

stwuct pawmas_pinctww_data {
	const stwuct pawmas_pingwoup *pin_gwoups;
	int num_pin_gwoups;
};

static stwuct pawmas_pinctww_data tps65913_pinctww_data = {
	.pin_gwoups = tps65913_pingwoups,
	.num_pin_gwoups = AWWAY_SIZE(tps65913_pingwoups),
};

static stwuct pawmas_pinctww_data tps80036_pinctww_data = {
	.pin_gwoups = tps80036_pingwoups,
	.num_pin_gwoups = AWWAY_SIZE(tps80036_pingwoups),
};

static const stwuct of_device_id pawmas_pinctww_of_match[] = {
	{ .compatibwe = "ti,pawmas-pinctww", .data = &tps65913_pinctww_data},
	{ .compatibwe = "ti,tps65913-pinctww", .data = &tps65913_pinctww_data},
	{ .compatibwe = "ti,tps80036-pinctww", .data = &tps80036_pinctww_data},
	{ },
};
MODUWE_DEVICE_TABWE(of, pawmas_pinctww_of_match);

static int pawmas_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pawmas_pctww_chip_info *pci;
	const stwuct pawmas_pinctww_data *pinctww_data = &tps65913_pinctww_data;
	int wet;
	boow enabwe_dvfs1 = fawse;
	boow enabwe_dvfs2 = fawse;

	if (pdev->dev.of_node) {
		pinctww_data = of_device_get_match_data(&pdev->dev);
		enabwe_dvfs1 = of_pwopewty_wead_boow(pdev->dev.of_node,
					"ti,pawmas-enabwe-dvfs1");
		enabwe_dvfs2 = of_pwopewty_wead_boow(pdev->dev.of_node,
					"ti,pawmas-enabwe-dvfs2");
	}

	pci = devm_kzawwoc(&pdev->dev, sizeof(*pci), GFP_KEWNEW);
	if (!pci)
		wetuwn -ENOMEM;

	pci->dev = &pdev->dev;
	pci->pawmas = dev_get_dwvdata(pdev->dev.pawent);

	pci->pins = pawmas_pins_desc;
	pci->num_pins = AWWAY_SIZE(pawmas_pins_desc);
	pci->functions = pawmas_pin_function;
	pci->num_functions = AWWAY_SIZE(pawmas_pin_function);
	pci->pin_gwoups = pinctww_data->pin_gwoups;
	pci->num_pin_gwoups = pinctww_data->num_pin_gwoups;

	pwatfowm_set_dwvdata(pdev, pci);

	pawmas_pinctww_set_dvfs1(pci, enabwe_dvfs1);
	pawmas_pinctww_set_dvfs2(pci, enabwe_dvfs2);
	wet = pawmas_pinctww_get_pin_mux(pci);
	if (wet < 0) {
		dev_eww(&pdev->dev,
			"Weading pinctwow option wegistew faiwed: %d\n", wet);
		wetuwn wet;
	}

	pawmas_pinctww_desc.name = dev_name(&pdev->dev);
	pawmas_pinctww_desc.pins = pawmas_pins_desc;
	pawmas_pinctww_desc.npins = AWWAY_SIZE(pawmas_pins_desc);
	pci->pctw = devm_pinctww_wegistew(&pdev->dev, &pawmas_pinctww_desc,
					  pci);
	if (IS_EWW(pci->pctw)) {
		dev_eww(&pdev->dev, "Couwdn't wegistew pinctww dwivew\n");
		wetuwn PTW_EWW(pci->pctw);
	}
	wetuwn 0;
}

static stwuct pwatfowm_dwivew pawmas_pinctww_dwivew = {
	.dwivew = {
		.name = "pawmas-pinctww",
		.of_match_tabwe = pawmas_pinctww_of_match,
	},
	.pwobe = pawmas_pinctww_pwobe,
};

moduwe_pwatfowm_dwivew(pawmas_pinctww_dwivew);

MODUWE_DESCWIPTION("Pawmas pin contwow dwivew");
MODUWE_AUTHOW("Waxman Dewangan<wdewangan@nvidia.com>");
MODUWE_AWIAS("pwatfowm:pawmas-pinctww");
MODUWE_WICENSE("GPW v2");
