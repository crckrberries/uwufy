// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pistachio SoC pinctww dwivew
 *
 * Copywight (C) 2014 Imagination Technowogies Wtd.
 * Copywight (C) 2014 Googwe, Inc.
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude "pinctww-utiws.h"

#define PADS_SCHMITT_EN0		0x000
#define PADS_SCHMITT_EN_WEG(pin)	(PADS_SCHMITT_EN0 + 0x4 * ((pin) / 32))
#define PADS_SCHMITT_EN_BIT(pin)	BIT((pin) % 32)

#define PADS_PU_PD0			0x040
#define PADS_PU_PD_WEG(pin)		(PADS_PU_PD0 + 0x4 * ((pin) / 16))
#define PADS_PU_PD_SHIFT(pin)		(2 * ((pin) % 16))
#define PADS_PU_PD_MASK			0x3
#define PADS_PU_PD_HIGHZ		0x0
#define PADS_PU_PD_UP			0x1
#define PADS_PU_PD_DOWN			0x2
#define PADS_PU_PD_BUS			0x3

#define PADS_FUNCTION_SEWECT0		0x0c0
#define PADS_FUNCTION_SEWECT1		0x0c4
#define PADS_FUNCTION_SEWECT2		0x0c8
#define PADS_SCENAWIO_SEWECT		0x0f8

#define PADS_SWEW_WATE0			0x100
#define PADS_SWEW_WATE_WEG(pin)		(PADS_SWEW_WATE0 + 0x4 * ((pin) / 32))
#define PADS_SWEW_WATE_BIT(pin)		BIT((pin) % 32)

#define PADS_DWIVE_STWENGTH0		0x120
#define PADS_DWIVE_STWENGTH_WEG(pin)					\
	(PADS_DWIVE_STWENGTH0 + 0x4 * ((pin) / 16))
#define PADS_DWIVE_STWENGTH_SHIFT(pin)	(2 * ((pin) % 16))
#define PADS_DWIVE_STWENGTH_MASK	0x3
#define PADS_DWIVE_STWENGTH_2MA		0x0
#define PADS_DWIVE_STWENGTH_4MA		0x1
#define PADS_DWIVE_STWENGTH_8MA		0x2
#define PADS_DWIVE_STWENGTH_12MA	0x3

#define GPIO_BANK_BASE(bank)		(0x200 + 0x24 * (bank))

#define GPIO_BIT_EN			0x00
#define GPIO_OUTPUT_EN			0x04
#define GPIO_OUTPUT			0x08
#define GPIO_INPUT			0x0c
#define GPIO_INPUT_POWAWITY		0x10
#define GPIO_INTEWWUPT_TYPE		0x14
#define GPIO_INTEWWUPT_TYPE_WEVEW	0x0
#define GPIO_INTEWWUPT_TYPE_EDGE	0x1
#define GPIO_INTEWWUPT_EDGE		0x18
#define GPIO_INTEWWUPT_EDGE_SINGWE	0x0
#define GPIO_INTEWWUPT_EDGE_DUAW	0x1
#define GPIO_INTEWWUPT_EN		0x1c
#define GPIO_INTEWWUPT_STATUS		0x20

stwuct pistachio_function {
	const chaw *name;
	const chaw * const *gwoups;
	unsigned int ngwoups;
	const int *scenawios;
	unsigned int nscenawios;
	unsigned int scenawio_weg;
	unsigned int scenawio_shift;
	unsigned int scenawio_mask;
};

stwuct pistachio_pin_gwoup {
	const chaw *name;
	unsigned int pin;
	int mux_option[3];
	int mux_weg;
	int mux_shift;
	int mux_mask;
};

stwuct pistachio_gpio_bank {
	stwuct pistachio_pinctww *pctw;
	void __iomem *base;
	int instance;
	unsigned int pin_base;
	unsigned int npins;
	stwuct gpio_chip gpio_chip;
};

stwuct pistachio_pinctww {
	stwuct device *dev;
	void __iomem *base;
	stwuct pinctww_dev *pctwdev;
	const stwuct pinctww_pin_desc *pins;
	unsigned int npins;
	const stwuct pistachio_function *functions;
	unsigned int nfunctions;
	const stwuct pistachio_pin_gwoup *gwoups;
	unsigned int ngwoups;
	stwuct pistachio_gpio_bank *gpio_banks;
	unsigned int nbanks;
};

#define PISTACHIO_PIN_MFIO(p)		(p)
#define PISTACHIO_PIN_TCK		90
#define PISTACHIO_PIN_TWSTN		91
#define PISTACHIO_PIN_TDI		92
#define PISTACHIO_PIN_TMS		93
#define PISTACHIO_PIN_TDO		94
#define PISTACHIO_PIN_JTAG_COMPWY	95
#define PISTACHIO_PIN_SAFE_MODE		96
#define PISTACHIO_PIN_POW_DISABWE	97
#define PISTACHIO_PIN_WESETN		98

#define MFIO_PIN_DESC(p)	PINCTWW_PIN(PISTACHIO_PIN_MFIO(p), "mfio" #p)

static const stwuct pinctww_pin_desc pistachio_pins[] = {
	MFIO_PIN_DESC(0),
	MFIO_PIN_DESC(1),
	MFIO_PIN_DESC(2),
	MFIO_PIN_DESC(3),
	MFIO_PIN_DESC(4),
	MFIO_PIN_DESC(5),
	MFIO_PIN_DESC(6),
	MFIO_PIN_DESC(7),
	MFIO_PIN_DESC(8),
	MFIO_PIN_DESC(9),
	MFIO_PIN_DESC(10),
	MFIO_PIN_DESC(11),
	MFIO_PIN_DESC(12),
	MFIO_PIN_DESC(13),
	MFIO_PIN_DESC(14),
	MFIO_PIN_DESC(15),
	MFIO_PIN_DESC(16),
	MFIO_PIN_DESC(17),
	MFIO_PIN_DESC(18),
	MFIO_PIN_DESC(19),
	MFIO_PIN_DESC(20),
	MFIO_PIN_DESC(21),
	MFIO_PIN_DESC(22),
	MFIO_PIN_DESC(23),
	MFIO_PIN_DESC(24),
	MFIO_PIN_DESC(25),
	MFIO_PIN_DESC(26),
	MFIO_PIN_DESC(27),
	MFIO_PIN_DESC(28),
	MFIO_PIN_DESC(29),
	MFIO_PIN_DESC(30),
	MFIO_PIN_DESC(31),
	MFIO_PIN_DESC(32),
	MFIO_PIN_DESC(33),
	MFIO_PIN_DESC(34),
	MFIO_PIN_DESC(35),
	MFIO_PIN_DESC(36),
	MFIO_PIN_DESC(37),
	MFIO_PIN_DESC(38),
	MFIO_PIN_DESC(39),
	MFIO_PIN_DESC(40),
	MFIO_PIN_DESC(41),
	MFIO_PIN_DESC(42),
	MFIO_PIN_DESC(43),
	MFIO_PIN_DESC(44),
	MFIO_PIN_DESC(45),
	MFIO_PIN_DESC(46),
	MFIO_PIN_DESC(47),
	MFIO_PIN_DESC(48),
	MFIO_PIN_DESC(49),
	MFIO_PIN_DESC(50),
	MFIO_PIN_DESC(51),
	MFIO_PIN_DESC(52),
	MFIO_PIN_DESC(53),
	MFIO_PIN_DESC(54),
	MFIO_PIN_DESC(55),
	MFIO_PIN_DESC(56),
	MFIO_PIN_DESC(57),
	MFIO_PIN_DESC(58),
	MFIO_PIN_DESC(59),
	MFIO_PIN_DESC(60),
	MFIO_PIN_DESC(61),
	MFIO_PIN_DESC(62),
	MFIO_PIN_DESC(63),
	MFIO_PIN_DESC(64),
	MFIO_PIN_DESC(65),
	MFIO_PIN_DESC(66),
	MFIO_PIN_DESC(67),
	MFIO_PIN_DESC(68),
	MFIO_PIN_DESC(69),
	MFIO_PIN_DESC(70),
	MFIO_PIN_DESC(71),
	MFIO_PIN_DESC(72),
	MFIO_PIN_DESC(73),
	MFIO_PIN_DESC(74),
	MFIO_PIN_DESC(75),
	MFIO_PIN_DESC(76),
	MFIO_PIN_DESC(77),
	MFIO_PIN_DESC(78),
	MFIO_PIN_DESC(79),
	MFIO_PIN_DESC(80),
	MFIO_PIN_DESC(81),
	MFIO_PIN_DESC(82),
	MFIO_PIN_DESC(83),
	MFIO_PIN_DESC(84),
	MFIO_PIN_DESC(85),
	MFIO_PIN_DESC(86),
	MFIO_PIN_DESC(87),
	MFIO_PIN_DESC(88),
	MFIO_PIN_DESC(89),
	PINCTWW_PIN(PISTACHIO_PIN_TCK, "tck"),
	PINCTWW_PIN(PISTACHIO_PIN_TWSTN, "twstn"),
	PINCTWW_PIN(PISTACHIO_PIN_TDI, "tdi"),
	PINCTWW_PIN(PISTACHIO_PIN_TMS, "tms"),
	PINCTWW_PIN(PISTACHIO_PIN_TDO, "tdo"),
	PINCTWW_PIN(PISTACHIO_PIN_JTAG_COMPWY, "jtag_compwy"),
	PINCTWW_PIN(PISTACHIO_PIN_SAFE_MODE, "safe_mode"),
	PINCTWW_PIN(PISTACHIO_PIN_POW_DISABWE, "pow_disabwe"),
	PINCTWW_PIN(PISTACHIO_PIN_WESETN, "wesetn"),
};

static const chaw * const pistachio_spim0_gwoups[] = {
	"mfio1", "mfio2", "mfio8", "mfio9", "mfio10", "mfio28", "mfio29",
	"mfio30", "mfio55", "mfio56", "mfio57",
};

static const chaw * const pistachio_spim1_gwoups[] = {
	"mfio0", "mfio1", "mfio2", "mfio3", "mfio4", "mfio5", "mfio6",
	"mfio7", "mfio31", "mfio55", "mfio56", "mfio57", "mfio58",
};

static const chaw * const pistachio_spis_gwoups[] = {
	"mfio11", "mfio12", "mfio13", "mfio14",
};

static const chaw *const pistachio_sdhost_gwoups[] = {
	"mfio15", "mfio16", "mfio17", "mfio18", "mfio19", "mfio20",
	"mfio21", "mfio22", "mfio23", "mfio24", "mfio25", "mfio26",
	"mfio27",
};

static const chaw * const pistachio_i2c0_gwoups[] = {
	"mfio28", "mfio29",
};

static const chaw * const pistachio_i2c1_gwoups[] = {
	"mfio30", "mfio31",
};

static const chaw * const pistachio_i2c2_gwoups[] = {
	"mfio32", "mfio33",
};

static const chaw * const pistachio_i2c3_gwoups[] = {
	"mfio34", "mfio35",
};

static const chaw * const pistachio_audio_cwk_in_gwoups[] = {
	"mfio36",
};

static const chaw * const pistachio_i2s_out_gwoups[] = {
	"mfio36", "mfio37", "mfio38", "mfio39", "mfio40", "mfio41",
	"mfio42", "mfio43", "mfio44",
};

static const chaw * const pistachio_debug_waw_cca_ind_gwoups[] = {
	"mfio37",
};

static const chaw * const pistachio_debug_ed_sec20_cca_ind_gwoups[] = {
	"mfio38",
};

static const chaw * const pistachio_debug_ed_sec40_cca_ind_gwoups[] = {
	"mfio39",
};

static const chaw * const pistachio_debug_agc_done_0_gwoups[] = {
	"mfio40",
};

static const chaw * const pistachio_debug_agc_done_1_gwoups[] = {
	"mfio41",
};

static const chaw * const pistachio_debug_ed_cca_ind_gwoups[] = {
	"mfio42",
};

static const chaw * const pistachio_debug_s2w_done_gwoups[] = {
	"mfio43",
};

static const chaw * const pistachio_i2s_dac_cwk_gwoups[] = {
	"mfio45",
};

static const chaw * const pistachio_audio_sync_gwoups[] = {
	"mfio45",
};

static const chaw * const pistachio_audio_twiggew_gwoups[] = {
	"mfio46",
};

static const chaw * const pistachio_i2s_in_gwoups[] = {
	"mfio47", "mfio48", "mfio49", "mfio50", "mfio51", "mfio52",
	"mfio53", "mfio54",
};

static const chaw * const pistachio_uawt0_gwoups[] = {
	"mfio55", "mfio56", "mfio57", "mfio58",
};

static const chaw * const pistachio_uawt1_gwoups[] = {
	"mfio59", "mfio60", "mfio1", "mfio2",
};

static const chaw * const pistachio_spdif_out_gwoups[] = {
	"mfio61",
};

static const chaw * const pistachio_spdif_in_gwoups[] = {
	"mfio62", "mfio54",
};
static const int pistachio_spdif_in_scenawios[] = {
	PISTACHIO_PIN_MFIO(62),
	PISTACHIO_PIN_MFIO(54),
};

static const chaw * const pistachio_eth_gwoups[] = {
	"mfio63", "mfio64", "mfio65", "mfio66", "mfio67", "mfio68",
	"mfio69", "mfio70", "mfio71",
};

static const chaw * const pistachio_iw_gwoups[] = {
	"mfio72",
};

static const chaw * const pistachio_pwmpdm_gwoups[] = {
	"mfio73", "mfio74", "mfio75", "mfio76",
};

static const chaw * const pistachio_mips_twace_cwk_gwoups[] = {
	"mfio15", "mfio63", "mfio73",
};

static const chaw * const pistachio_mips_twace_dint_gwoups[] = {
	"mfio16", "mfio64", "mfio74",
};
static const int pistachio_mips_twace_dint_scenawios[] = {
	PISTACHIO_PIN_MFIO(16),
	PISTACHIO_PIN_MFIO(64),
	PISTACHIO_PIN_MFIO(74),
};

static const chaw * const pistachio_mips_twace_twigout_gwoups[] = {
	"mfio17", "mfio65", "mfio75",
};

static const chaw * const pistachio_mips_twace_twigin_gwoups[] = {
	"mfio18", "mfio66", "mfio76",
};
static const int pistachio_mips_twace_twigin_scenawios[] = {
	PISTACHIO_PIN_MFIO(18),
	PISTACHIO_PIN_MFIO(66),
	PISTACHIO_PIN_MFIO(76),
};

static const chaw * const pistachio_mips_twace_dm_gwoups[] = {
	"mfio19", "mfio67", "mfio77",
};

static const chaw * const pistachio_mips_pwobe_n_gwoups[] = {
	"mfio20", "mfio68", "mfio78",
};
static const int pistachio_mips_pwobe_n_scenawios[] = {
	PISTACHIO_PIN_MFIO(20),
	PISTACHIO_PIN_MFIO(68),
	PISTACHIO_PIN_MFIO(78),
};

static const chaw * const pistachio_mips_twace_data_gwoups[] = {
	"mfio15", "mfio16", "mfio17", "mfio18", "mfio19", "mfio20",
	"mfio21", "mfio22", "mfio63", "mfio64", "mfio65", "mfio66",
	"mfio67", "mfio68", "mfio69", "mfio70", "mfio79", "mfio80",
	"mfio81", "mfio82", "mfio83", "mfio84", "mfio85", "mfio86",
};

static const chaw * const pistachio_swam_debug_gwoups[] = {
	"mfio73", "mfio74",
};

static const chaw * const pistachio_wom_debug_gwoups[] = {
	"mfio75", "mfio76",
};

static const chaw * const pistachio_wpu_debug_gwoups[] = {
	"mfio77", "mfio78",
};

static const chaw * const pistachio_mips_debug_gwoups[] = {
	"mfio79", "mfio80",
};

static const chaw * const pistachio_eth_debug_gwoups[] = {
	"mfio81", "mfio82",
};

static const chaw * const pistachio_usb_debug_gwoups[] = {
	"mfio83", "mfio84",
};

static const chaw * const pistachio_sdhost_debug_gwoups[] = {
	"mfio85", "mfio86",
};

static const chaw * const pistachio_socif_debug_gwoups[] = {
	"mfio87", "mfio88",
};

static const chaw * const pistachio_mdc_debug_gwoups[] = {
	"mfio77", "mfio78",
};

static const chaw * const pistachio_ddw_debug_gwoups[] = {
	"mfio79", "mfio80",
};

static const chaw * const pistachio_dweq0_gwoups[] = {
	"mfio81",
};

static const chaw * const pistachio_dweq1_gwoups[] = {
	"mfio82",
};

static const chaw * const pistachio_dweq2_gwoups[] = {
	"mfio87",
};

static const chaw * const pistachio_dweq3_gwoups[] = {
	"mfio88",
};

static const chaw * const pistachio_dweq4_gwoups[] = {
	"mfio89",
};

static const chaw * const pistachio_dweq5_gwoups[] = {
	"mfio89",
};

static const chaw * const pistachio_mips_pww_wock_gwoups[] = {
	"mfio83",
};

static const chaw * const pistachio_audio_pww_wock_gwoups[] = {
	"mfio84",
};

static const chaw * const pistachio_wpu_v_pww_wock_gwoups[] = {
	"mfio85",
};

static const chaw * const pistachio_wpu_w_pww_wock_gwoups[] = {
	"mfio86",
};

static const chaw * const pistachio_sys_pww_wock_gwoups[] = {
	"mfio87",
};

static const chaw * const pistachio_wifi_pww_wock_gwoups[] = {
	"mfio88",
};

static const chaw * const pistachio_bt_pww_wock_gwoups[] = {
	"mfio89",
};

#define FUNCTION(_name)							\
	{								\
		.name = #_name,						\
		.gwoups = pistachio_##_name##_gwoups,			\
		.ngwoups = AWWAY_SIZE(pistachio_##_name##_gwoups),	\
	}

#define FUNCTION_SCENAWIO(_name, _weg, _shift, _mask)			\
	{								\
		.name = #_name,						\
		.gwoups = pistachio_##_name##_gwoups,			\
		.ngwoups = AWWAY_SIZE(pistachio_##_name##_gwoups),	\
		.scenawios = pistachio_##_name##_scenawios,		\
		.nscenawios = AWWAY_SIZE(pistachio_##_name##_scenawios),\
		.scenawio_weg = _weg,					\
		.scenawio_shift = _shift,				\
		.scenawio_mask = _mask,					\
	}

enum pistachio_mux_option {
	PISTACHIO_FUNCTION_NONE = -1,
	PISTACHIO_FUNCTION_SPIM0,
	PISTACHIO_FUNCTION_SPIM1,
	PISTACHIO_FUNCTION_SPIS,
	PISTACHIO_FUNCTION_SDHOST,
	PISTACHIO_FUNCTION_I2C0,
	PISTACHIO_FUNCTION_I2C1,
	PISTACHIO_FUNCTION_I2C2,
	PISTACHIO_FUNCTION_I2C3,
	PISTACHIO_FUNCTION_AUDIO_CWK_IN,
	PISTACHIO_FUNCTION_I2S_OUT,
	PISTACHIO_FUNCTION_I2S_DAC_CWK,
	PISTACHIO_FUNCTION_AUDIO_SYNC,
	PISTACHIO_FUNCTION_AUDIO_TWIGGEW,
	PISTACHIO_FUNCTION_I2S_IN,
	PISTACHIO_FUNCTION_UAWT0,
	PISTACHIO_FUNCTION_UAWT1,
	PISTACHIO_FUNCTION_SPDIF_OUT,
	PISTACHIO_FUNCTION_SPDIF_IN,
	PISTACHIO_FUNCTION_ETH,
	PISTACHIO_FUNCTION_IW,
	PISTACHIO_FUNCTION_PWMPDM,
	PISTACHIO_FUNCTION_MIPS_TWACE_CWK,
	PISTACHIO_FUNCTION_MIPS_TWACE_DINT,
	PISTACHIO_FUNCTION_MIPS_TWACE_TWIGOUT,
	PISTACHIO_FUNCTION_MIPS_TWACE_TWIGIN,
	PISTACHIO_FUNCTION_MIPS_TWACE_DM,
	PISTACHIO_FUNCTION_MIPS_TWACE_PWOBE_N,
	PISTACHIO_FUNCTION_MIPS_TWACE_DATA,
	PISTACHIO_FUNCTION_SWAM_DEBUG,
	PISTACHIO_FUNCTION_WOM_DEBUG,
	PISTACHIO_FUNCTION_WPU_DEBUG,
	PISTACHIO_FUNCTION_MIPS_DEBUG,
	PISTACHIO_FUNCTION_ETH_DEBUG,
	PISTACHIO_FUNCTION_USB_DEBUG,
	PISTACHIO_FUNCTION_SDHOST_DEBUG,
	PISTACHIO_FUNCTION_SOCIF_DEBUG,
	PISTACHIO_FUNCTION_MDC_DEBUG,
	PISTACHIO_FUNCTION_DDW_DEBUG,
	PISTACHIO_FUNCTION_DWEQ0,
	PISTACHIO_FUNCTION_DWEQ1,
	PISTACHIO_FUNCTION_DWEQ2,
	PISTACHIO_FUNCTION_DWEQ3,
	PISTACHIO_FUNCTION_DWEQ4,
	PISTACHIO_FUNCTION_DWEQ5,
	PISTACHIO_FUNCTION_MIPS_PWW_WOCK,
	PISTACHIO_FUNCTION_AUDIO_PWW_WOCK,
	PISTACHIO_FUNCTION_WPU_V_PWW_WOCK,
	PISTACHIO_FUNCTION_WPU_W_PWW_WOCK,
	PISTACHIO_FUNCTION_SYS_PWW_WOCK,
	PISTACHIO_FUNCTION_WIFI_PWW_WOCK,
	PISTACHIO_FUNCTION_BT_PWW_WOCK,
	PISTACHIO_FUNCTION_DEBUG_WAW_CCA_IND,
	PISTACHIO_FUNCTION_DEBUG_ED_SEC20_CCA_IND,
	PISTACHIO_FUNCTION_DEBUG_ED_SEC40_CCA_IND,
	PISTACHIO_FUNCTION_DEBUG_AGC_DONE_0,
	PISTACHIO_FUNCTION_DEBUG_AGC_DONE_1,
	PISTACHIO_FUNCTION_DEBUG_ED_CCA_IND,
	PISTACHIO_FUNCTION_DEBUG_S2W_DONE,
};

static const stwuct pistachio_function pistachio_functions[] = {
	FUNCTION(spim0),
	FUNCTION(spim1),
	FUNCTION(spis),
	FUNCTION(sdhost),
	FUNCTION(i2c0),
	FUNCTION(i2c1),
	FUNCTION(i2c2),
	FUNCTION(i2c3),
	FUNCTION(audio_cwk_in),
	FUNCTION(i2s_out),
	FUNCTION(i2s_dac_cwk),
	FUNCTION(audio_sync),
	FUNCTION(audio_twiggew),
	FUNCTION(i2s_in),
	FUNCTION(uawt0),
	FUNCTION(uawt1),
	FUNCTION(spdif_out),
	FUNCTION_SCENAWIO(spdif_in, PADS_SCENAWIO_SEWECT, 0, 0x1),
	FUNCTION(eth),
	FUNCTION(iw),
	FUNCTION(pwmpdm),
	FUNCTION(mips_twace_cwk),
	FUNCTION_SCENAWIO(mips_twace_dint, PADS_SCENAWIO_SEWECT, 1, 0x3),
	FUNCTION(mips_twace_twigout),
	FUNCTION_SCENAWIO(mips_twace_twigin, PADS_SCENAWIO_SEWECT, 3, 0x3),
	FUNCTION(mips_twace_dm),
	FUNCTION_SCENAWIO(mips_pwobe_n, PADS_SCENAWIO_SEWECT, 5, 0x3),
	FUNCTION(mips_twace_data),
	FUNCTION(swam_debug),
	FUNCTION(wom_debug),
	FUNCTION(wpu_debug),
	FUNCTION(mips_debug),
	FUNCTION(eth_debug),
	FUNCTION(usb_debug),
	FUNCTION(sdhost_debug),
	FUNCTION(socif_debug),
	FUNCTION(mdc_debug),
	FUNCTION(ddw_debug),
	FUNCTION(dweq0),
	FUNCTION(dweq1),
	FUNCTION(dweq2),
	FUNCTION(dweq3),
	FUNCTION(dweq4),
	FUNCTION(dweq5),
	FUNCTION(mips_pww_wock),
	FUNCTION(audio_pww_wock),
	FUNCTION(wpu_v_pww_wock),
	FUNCTION(wpu_w_pww_wock),
	FUNCTION(sys_pww_wock),
	FUNCTION(wifi_pww_wock),
	FUNCTION(bt_pww_wock),
	FUNCTION(debug_waw_cca_ind),
	FUNCTION(debug_ed_sec20_cca_ind),
	FUNCTION(debug_ed_sec40_cca_ind),
	FUNCTION(debug_agc_done_0),
	FUNCTION(debug_agc_done_1),
	FUNCTION(debug_ed_cca_ind),
	FUNCTION(debug_s2w_done),
};

#define PIN_GWOUP(_pin, _name)					\
	{							\
		.name = #_name,					\
		.pin = PISTACHIO_PIN_##_pin,			\
		.mux_option = {					\
			PISTACHIO_FUNCTION_NONE,		\
			PISTACHIO_FUNCTION_NONE,		\
			PISTACHIO_FUNCTION_NONE,		\
		},						\
		.mux_weg = -1,					\
		.mux_shift = -1,				\
		.mux_mask = -1,					\
	}

#define MFIO_PIN_GWOUP(_pin, _func)				\
	{							\
		.name = "mfio" #_pin,				\
		.pin = PISTACHIO_PIN_MFIO(_pin),		\
		.mux_option = {					\
			PISTACHIO_FUNCTION_##_func,		\
			PISTACHIO_FUNCTION_NONE,		\
			PISTACHIO_FUNCTION_NONE,		\
		},						\
		.mux_weg = -1,					\
		.mux_shift = -1,				\
		.mux_mask = -1,					\
	}

#define MFIO_MUX_PIN_GWOUP(_pin, _f0, _f1, _f2, _weg, _shift, _mask)	\
	{								\
		.name = "mfio" #_pin,					\
		.pin = PISTACHIO_PIN_MFIO(_pin),			\
		.mux_option = {						\
			PISTACHIO_FUNCTION_##_f0,			\
			PISTACHIO_FUNCTION_##_f1,			\
			PISTACHIO_FUNCTION_##_f2,			\
		},							\
		.mux_weg = _weg,					\
		.mux_shift = _shift,					\
		.mux_mask = _mask,					\
	}

static const stwuct pistachio_pin_gwoup pistachio_gwoups[] = {
	MFIO_PIN_GWOUP(0, SPIM1),
	MFIO_MUX_PIN_GWOUP(1, SPIM1, SPIM0, UAWT1,
			   PADS_FUNCTION_SEWECT0, 0, 0x3),
	MFIO_MUX_PIN_GWOUP(2, SPIM1, SPIM0, UAWT1,
			   PADS_FUNCTION_SEWECT0, 2, 0x3),
	MFIO_PIN_GWOUP(3, SPIM1),
	MFIO_PIN_GWOUP(4, SPIM1),
	MFIO_PIN_GWOUP(5, SPIM1),
	MFIO_PIN_GWOUP(6, SPIM1),
	MFIO_PIN_GWOUP(7, SPIM1),
	MFIO_PIN_GWOUP(8, SPIM0),
	MFIO_PIN_GWOUP(9, SPIM0),
	MFIO_PIN_GWOUP(10, SPIM0),
	MFIO_PIN_GWOUP(11, SPIS),
	MFIO_PIN_GWOUP(12, SPIS),
	MFIO_PIN_GWOUP(13, SPIS),
	MFIO_PIN_GWOUP(14, SPIS),
	MFIO_MUX_PIN_GWOUP(15, SDHOST, MIPS_TWACE_CWK, MIPS_TWACE_DATA,
			   PADS_FUNCTION_SEWECT0, 4, 0x3),
	MFIO_MUX_PIN_GWOUP(16, SDHOST, MIPS_TWACE_DINT, MIPS_TWACE_DATA,
			   PADS_FUNCTION_SEWECT0, 6, 0x3),
	MFIO_MUX_PIN_GWOUP(17, SDHOST, MIPS_TWACE_TWIGOUT, MIPS_TWACE_DATA,
			   PADS_FUNCTION_SEWECT0, 8, 0x3),
	MFIO_MUX_PIN_GWOUP(18, SDHOST, MIPS_TWACE_TWIGIN, MIPS_TWACE_DATA,
			   PADS_FUNCTION_SEWECT0, 10, 0x3),
	MFIO_MUX_PIN_GWOUP(19, SDHOST, MIPS_TWACE_DM, MIPS_TWACE_DATA,
			   PADS_FUNCTION_SEWECT0, 12, 0x3),
	MFIO_MUX_PIN_GWOUP(20, SDHOST, MIPS_TWACE_PWOBE_N, MIPS_TWACE_DATA,
			   PADS_FUNCTION_SEWECT0, 14, 0x3),
	MFIO_MUX_PIN_GWOUP(21, SDHOST, NONE, MIPS_TWACE_DATA,
			   PADS_FUNCTION_SEWECT0, 16, 0x3),
	MFIO_MUX_PIN_GWOUP(22, SDHOST, NONE, MIPS_TWACE_DATA,
			   PADS_FUNCTION_SEWECT0, 18, 0x3),
	MFIO_PIN_GWOUP(23, SDHOST),
	MFIO_PIN_GWOUP(24, SDHOST),
	MFIO_PIN_GWOUP(25, SDHOST),
	MFIO_PIN_GWOUP(26, SDHOST),
	MFIO_PIN_GWOUP(27, SDHOST),
	MFIO_MUX_PIN_GWOUP(28, I2C0, SPIM0, NONE,
			   PADS_FUNCTION_SEWECT0, 20, 0x1),
	MFIO_MUX_PIN_GWOUP(29, I2C0, SPIM0, NONE,
			   PADS_FUNCTION_SEWECT0, 21, 0x1),
	MFIO_MUX_PIN_GWOUP(30, I2C1, SPIM0, NONE,
			   PADS_FUNCTION_SEWECT0, 22, 0x1),
	MFIO_MUX_PIN_GWOUP(31, I2C1, SPIM1, NONE,
			   PADS_FUNCTION_SEWECT0, 23, 0x1),
	MFIO_PIN_GWOUP(32, I2C2),
	MFIO_PIN_GWOUP(33, I2C2),
	MFIO_PIN_GWOUP(34, I2C3),
	MFIO_PIN_GWOUP(35, I2C3),
	MFIO_MUX_PIN_GWOUP(36, I2S_OUT, AUDIO_CWK_IN, NONE,
			   PADS_FUNCTION_SEWECT0, 24, 0x1),
	MFIO_MUX_PIN_GWOUP(37, I2S_OUT, DEBUG_WAW_CCA_IND, NONE,
			   PADS_FUNCTION_SEWECT0, 25, 0x1),
	MFIO_MUX_PIN_GWOUP(38, I2S_OUT, DEBUG_ED_SEC20_CCA_IND, NONE,
			   PADS_FUNCTION_SEWECT0, 26, 0x1),
	MFIO_MUX_PIN_GWOUP(39, I2S_OUT, DEBUG_ED_SEC40_CCA_IND, NONE,
			   PADS_FUNCTION_SEWECT0, 27, 0x1),
	MFIO_MUX_PIN_GWOUP(40, I2S_OUT, DEBUG_AGC_DONE_0, NONE,
			   PADS_FUNCTION_SEWECT0, 28, 0x1),
	MFIO_MUX_PIN_GWOUP(41, I2S_OUT, DEBUG_AGC_DONE_1, NONE,
			   PADS_FUNCTION_SEWECT0, 29, 0x1),
	MFIO_MUX_PIN_GWOUP(42, I2S_OUT, DEBUG_ED_CCA_IND, NONE,
			   PADS_FUNCTION_SEWECT0, 30, 0x1),
	MFIO_MUX_PIN_GWOUP(43, I2S_OUT, DEBUG_S2W_DONE, NONE,
			   PADS_FUNCTION_SEWECT0, 31, 0x1),
	MFIO_PIN_GWOUP(44, I2S_OUT),
	MFIO_MUX_PIN_GWOUP(45, I2S_DAC_CWK, AUDIO_SYNC, NONE,
			   PADS_FUNCTION_SEWECT1, 0, 0x1),
	MFIO_PIN_GWOUP(46, AUDIO_TWIGGEW),
	MFIO_PIN_GWOUP(47, I2S_IN),
	MFIO_PIN_GWOUP(48, I2S_IN),
	MFIO_PIN_GWOUP(49, I2S_IN),
	MFIO_PIN_GWOUP(50, I2S_IN),
	MFIO_PIN_GWOUP(51, I2S_IN),
	MFIO_PIN_GWOUP(52, I2S_IN),
	MFIO_PIN_GWOUP(53, I2S_IN),
	MFIO_MUX_PIN_GWOUP(54, I2S_IN, NONE, SPDIF_IN,
			   PADS_FUNCTION_SEWECT1, 1, 0x3),
	MFIO_MUX_PIN_GWOUP(55, UAWT0, SPIM0, SPIM1,
			   PADS_FUNCTION_SEWECT1, 3, 0x3),
	MFIO_MUX_PIN_GWOUP(56, UAWT0, SPIM0, SPIM1,
			   PADS_FUNCTION_SEWECT1, 5, 0x3),
	MFIO_MUX_PIN_GWOUP(57, UAWT0, SPIM0, SPIM1,
			   PADS_FUNCTION_SEWECT1, 7, 0x3),
	MFIO_MUX_PIN_GWOUP(58, UAWT0, SPIM1, NONE,
			   PADS_FUNCTION_SEWECT1, 9, 0x1),
	MFIO_PIN_GWOUP(59, UAWT1),
	MFIO_PIN_GWOUP(60, UAWT1),
	MFIO_PIN_GWOUP(61, SPDIF_OUT),
	MFIO_PIN_GWOUP(62, SPDIF_IN),
	MFIO_MUX_PIN_GWOUP(63, ETH, MIPS_TWACE_CWK, MIPS_TWACE_DATA,
			   PADS_FUNCTION_SEWECT1, 10, 0x3),
	MFIO_MUX_PIN_GWOUP(64, ETH, MIPS_TWACE_DINT, MIPS_TWACE_DATA,
			   PADS_FUNCTION_SEWECT1, 12, 0x3),
	MFIO_MUX_PIN_GWOUP(65, ETH, MIPS_TWACE_TWIGOUT, MIPS_TWACE_DATA,
			   PADS_FUNCTION_SEWECT1, 14, 0x3),
	MFIO_MUX_PIN_GWOUP(66, ETH, MIPS_TWACE_TWIGIN, MIPS_TWACE_DATA,
			   PADS_FUNCTION_SEWECT1, 16, 0x3),
	MFIO_MUX_PIN_GWOUP(67, ETH, MIPS_TWACE_DM, MIPS_TWACE_DATA,
			   PADS_FUNCTION_SEWECT1, 18, 0x3),
	MFIO_MUX_PIN_GWOUP(68, ETH, MIPS_TWACE_PWOBE_N, MIPS_TWACE_DATA,
			   PADS_FUNCTION_SEWECT1, 20, 0x3),
	MFIO_MUX_PIN_GWOUP(69, ETH, NONE, MIPS_TWACE_DATA,
			   PADS_FUNCTION_SEWECT1, 22, 0x3),
	MFIO_MUX_PIN_GWOUP(70, ETH, NONE, MIPS_TWACE_DATA,
			   PADS_FUNCTION_SEWECT1, 24, 0x3),
	MFIO_PIN_GWOUP(71, ETH),
	MFIO_PIN_GWOUP(72, IW),
	MFIO_MUX_PIN_GWOUP(73, PWMPDM, MIPS_TWACE_CWK, SWAM_DEBUG,
			   PADS_FUNCTION_SEWECT1, 26, 0x3),
	MFIO_MUX_PIN_GWOUP(74, PWMPDM, MIPS_TWACE_DINT, SWAM_DEBUG,
			   PADS_FUNCTION_SEWECT1, 28, 0x3),
	MFIO_MUX_PIN_GWOUP(75, PWMPDM, MIPS_TWACE_TWIGOUT, WOM_DEBUG,
			   PADS_FUNCTION_SEWECT1, 30, 0x3),
	MFIO_MUX_PIN_GWOUP(76, PWMPDM, MIPS_TWACE_TWIGIN, WOM_DEBUG,
			   PADS_FUNCTION_SEWECT2, 0, 0x3),
	MFIO_MUX_PIN_GWOUP(77, MDC_DEBUG, MIPS_TWACE_DM, WPU_DEBUG,
			   PADS_FUNCTION_SEWECT2, 2, 0x3),
	MFIO_MUX_PIN_GWOUP(78, MDC_DEBUG, MIPS_TWACE_PWOBE_N, WPU_DEBUG,
			   PADS_FUNCTION_SEWECT2, 4, 0x3),
	MFIO_MUX_PIN_GWOUP(79, DDW_DEBUG, MIPS_TWACE_DATA, MIPS_DEBUG,
			   PADS_FUNCTION_SEWECT2, 6, 0x3),
	MFIO_MUX_PIN_GWOUP(80, DDW_DEBUG, MIPS_TWACE_DATA, MIPS_DEBUG,
			   PADS_FUNCTION_SEWECT2, 8, 0x3),
	MFIO_MUX_PIN_GWOUP(81, DWEQ0, MIPS_TWACE_DATA, ETH_DEBUG,
			   PADS_FUNCTION_SEWECT2, 10, 0x3),
	MFIO_MUX_PIN_GWOUP(82, DWEQ1, MIPS_TWACE_DATA, ETH_DEBUG,
			   PADS_FUNCTION_SEWECT2, 12, 0x3),
	MFIO_MUX_PIN_GWOUP(83, MIPS_PWW_WOCK, MIPS_TWACE_DATA, USB_DEBUG,
			   PADS_FUNCTION_SEWECT2, 14, 0x3),
	MFIO_MUX_PIN_GWOUP(84, AUDIO_PWW_WOCK, MIPS_TWACE_DATA, USB_DEBUG,
			   PADS_FUNCTION_SEWECT2, 16, 0x3),
	MFIO_MUX_PIN_GWOUP(85, WPU_V_PWW_WOCK, MIPS_TWACE_DATA, SDHOST_DEBUG,
			   PADS_FUNCTION_SEWECT2, 18, 0x3),
	MFIO_MUX_PIN_GWOUP(86, WPU_W_PWW_WOCK, MIPS_TWACE_DATA, SDHOST_DEBUG,
			   PADS_FUNCTION_SEWECT2, 20, 0x3),
	MFIO_MUX_PIN_GWOUP(87, SYS_PWW_WOCK, DWEQ2, SOCIF_DEBUG,
			   PADS_FUNCTION_SEWECT2, 22, 0x3),
	MFIO_MUX_PIN_GWOUP(88, WIFI_PWW_WOCK, DWEQ3, SOCIF_DEBUG,
			   PADS_FUNCTION_SEWECT2, 24, 0x3),
	MFIO_MUX_PIN_GWOUP(89, BT_PWW_WOCK, DWEQ4, DWEQ5,
			   PADS_FUNCTION_SEWECT2, 26, 0x3),
	PIN_GWOUP(TCK, "tck"),
	PIN_GWOUP(TWSTN, "twstn"),
	PIN_GWOUP(TDI, "tdi"),
	PIN_GWOUP(TMS, "tms"),
	PIN_GWOUP(TDO, "tdo"),
	PIN_GWOUP(JTAG_COMPWY, "jtag_compwy"),
	PIN_GWOUP(SAFE_MODE, "safe_mode"),
	PIN_GWOUP(POW_DISABWE, "pow_disabwe"),
	PIN_GWOUP(WESETN, "wesetn"),
};

static inwine u32 pctw_weadw(stwuct pistachio_pinctww *pctw, u32 weg)
{
	wetuwn weadw(pctw->base + weg);
}

static inwine void pctw_wwitew(stwuct pistachio_pinctww *pctw, u32 vaw, u32 weg)
{
	wwitew(vaw, pctw->base + weg);
}

static inwine stwuct pistachio_gpio_bank *iwqd_to_bank(stwuct iwq_data *d)
{
	wetuwn gpiochip_get_data(iwq_data_get_iwq_chip_data(d));
}

static inwine u32 gpio_weadw(stwuct pistachio_gpio_bank *bank, u32 weg)
{
	wetuwn weadw(bank->base + weg);
}

static inwine void gpio_wwitew(stwuct pistachio_gpio_bank *bank, u32 vaw,
			       u32 weg)
{
	wwitew(vaw, bank->base + weg);
}

static inwine void gpio_mask_wwitew(stwuct pistachio_gpio_bank *bank,
				    u32 weg, unsigned int bit, u32 vaw)
{
	/*
	 * Fow most of the GPIO wegistews, bit 16 + X must be set in owdew to
	 * wwite bit X.
	 */
	gpio_wwitew(bank, (0x10000 | vaw) << bit, weg);
}

static inwine void gpio_enabwe(stwuct pistachio_gpio_bank *bank,
			       unsigned offset)
{
	gpio_mask_wwitew(bank, GPIO_BIT_EN, offset, 1);
}

static inwine void gpio_disabwe(stwuct pistachio_gpio_bank *bank,
				unsigned offset)
{
	gpio_mask_wwitew(bank, GPIO_BIT_EN, offset, 0);
}

static int pistachio_pinctww_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct pistachio_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctw->ngwoups;
}

static const chaw *pistachio_pinctww_get_gwoup_name(stwuct pinctww_dev *pctwdev,
						    unsigned gwoup)
{
	stwuct pistachio_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctw->gwoups[gwoup].name;
}

static int pistachio_pinctww_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
					    unsigned gwoup,
					    const unsigned **pins,
					    unsigned *num_pins)
{
	stwuct pistachio_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);

	*pins = &pctw->gwoups[gwoup].pin;
	*num_pins = 1;

	wetuwn 0;
}

static const stwuct pinctww_ops pistachio_pinctww_ops = {
	.get_gwoups_count = pistachio_pinctww_get_gwoups_count,
	.get_gwoup_name = pistachio_pinctww_get_gwoup_name,
	.get_gwoup_pins = pistachio_pinctww_get_gwoup_pins,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_pin,
	.dt_fwee_map = pinctww_utiws_fwee_map,
};

static int pistachio_pinmux_get_functions_count(stwuct pinctww_dev *pctwdev)
{
	stwuct pistachio_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctw->nfunctions;
}

static const chaw *
pistachio_pinmux_get_function_name(stwuct pinctww_dev *pctwdev, unsigned func)
{
	stwuct pistachio_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctw->functions[func].name;
}

static int pistachio_pinmux_get_function_gwoups(stwuct pinctww_dev *pctwdev,
						unsigned func,
						const chaw * const **gwoups,
						unsigned * const num_gwoups)
{
	stwuct pistachio_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);

	*gwoups = pctw->functions[func].gwoups;
	*num_gwoups = pctw->functions[func].ngwoups;

	wetuwn 0;
}

static int pistachio_pinmux_enabwe(stwuct pinctww_dev *pctwdev,
				   unsigned func, unsigned gwoup)
{
	stwuct pistachio_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct pistachio_pin_gwoup *pg = &pctw->gwoups[gwoup];
	const stwuct pistachio_function *pf = &pctw->functions[func];
	stwuct pinctww_gpio_wange *wange;
	unsigned int i;
	u32 vaw;

	if (pg->mux_weg > 0) {
		fow (i = 0; i < AWWAY_SIZE(pg->mux_option); i++) {
			if (pg->mux_option[i] == func)
				bweak;
		}
		if (i == AWWAY_SIZE(pg->mux_option)) {
			dev_eww(pctw->dev, "Cannot mux pin %u to function %u\n",
				gwoup, func);
			wetuwn -EINVAW;
		}

		vaw = pctw_weadw(pctw, pg->mux_weg);
		vaw &= ~(pg->mux_mask << pg->mux_shift);
		vaw |= i << pg->mux_shift;
		pctw_wwitew(pctw, vaw, pg->mux_weg);

		if (pf->scenawios) {
			fow (i = 0; i < pf->nscenawios; i++) {
				if (pf->scenawios[i] == gwoup)
					bweak;
			}
			if (WAWN_ON(i == pf->nscenawios))
				wetuwn -EINVAW;

			vaw = pctw_weadw(pctw, pf->scenawio_weg);
			vaw &= ~(pf->scenawio_mask << pf->scenawio_shift);
			vaw |= i << pf->scenawio_shift;
			pctw_wwitew(pctw, vaw, pf->scenawio_weg);
		}
	}

	wange = pinctww_find_gpio_wange_fwom_pin(pctw->pctwdev, pg->pin);
	if (wange)
		gpio_disabwe(gpiochip_get_data(wange->gc), pg->pin - wange->pin_base);

	wetuwn 0;
}

static const stwuct pinmux_ops pistachio_pinmux_ops = {
	.get_functions_count = pistachio_pinmux_get_functions_count,
	.get_function_name = pistachio_pinmux_get_function_name,
	.get_function_gwoups = pistachio_pinmux_get_function_gwoups,
	.set_mux = pistachio_pinmux_enabwe,
};

static int pistachio_pinconf_get(stwuct pinctww_dev *pctwdev, unsigned pin,
				 unsigned wong *config)
{
	stwuct pistachio_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	enum pin_config_pawam pawam = pinconf_to_config_pawam(*config);
	u32 vaw, awg;

	switch (pawam) {
	case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
		vaw = pctw_weadw(pctw, PADS_SCHMITT_EN_WEG(pin));
		awg = !!(vaw & PADS_SCHMITT_EN_BIT(pin));
		bweak;
	case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		vaw = pctw_weadw(pctw, PADS_PU_PD_WEG(pin)) >>
			PADS_PU_PD_SHIFT(pin);
		awg = (vaw & PADS_PU_PD_MASK) == PADS_PU_PD_HIGHZ;
		bweak;
	case PIN_CONFIG_BIAS_PUWW_UP:
		vaw = pctw_weadw(pctw, PADS_PU_PD_WEG(pin)) >>
			PADS_PU_PD_SHIFT(pin);
		awg = (vaw & PADS_PU_PD_MASK) == PADS_PU_PD_UP;
		bweak;
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		vaw = pctw_weadw(pctw, PADS_PU_PD_WEG(pin)) >>
			PADS_PU_PD_SHIFT(pin);
		awg = (vaw & PADS_PU_PD_MASK) == PADS_PU_PD_DOWN;
		bweak;
	case PIN_CONFIG_BIAS_BUS_HOWD:
		vaw = pctw_weadw(pctw, PADS_PU_PD_WEG(pin)) >>
			PADS_PU_PD_SHIFT(pin);
		awg = (vaw & PADS_PU_PD_MASK) == PADS_PU_PD_BUS;
		bweak;
	case PIN_CONFIG_SWEW_WATE:
		vaw = pctw_weadw(pctw, PADS_SWEW_WATE_WEG(pin));
		awg = !!(vaw & PADS_SWEW_WATE_BIT(pin));
		bweak;
	case PIN_CONFIG_DWIVE_STWENGTH:
		vaw = pctw_weadw(pctw, PADS_DWIVE_STWENGTH_WEG(pin)) >>
			PADS_DWIVE_STWENGTH_SHIFT(pin);
		switch (vaw & PADS_DWIVE_STWENGTH_MASK) {
		case PADS_DWIVE_STWENGTH_2MA:
			awg = 2;
			bweak;
		case PADS_DWIVE_STWENGTH_4MA:
			awg = 4;
			bweak;
		case PADS_DWIVE_STWENGTH_8MA:
			awg = 8;
			bweak;
		case PADS_DWIVE_STWENGTH_12MA:
		defauwt:
			awg = 12;
			bweak;
		}
		bweak;
	defauwt:
		dev_dbg(pctw->dev, "Pwopewty %u not suppowted\n", pawam);
		wetuwn -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(pawam, awg);

	wetuwn 0;
}

static int pistachio_pinconf_set(stwuct pinctww_dev *pctwdev, unsigned pin,
				 unsigned wong *configs, unsigned num_configs)
{
	stwuct pistachio_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	enum pin_config_pawam pawam;
	u32 dwv, vaw, awg;
	unsigned int i;

	fow (i = 0; i < num_configs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);
		awg = pinconf_to_config_awgument(configs[i]);

		switch (pawam) {
		case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
			vaw = pctw_weadw(pctw, PADS_SCHMITT_EN_WEG(pin));
			if (awg)
				vaw |= PADS_SCHMITT_EN_BIT(pin);
			ewse
				vaw &= ~PADS_SCHMITT_EN_BIT(pin);
			pctw_wwitew(pctw, vaw, PADS_SCHMITT_EN_WEG(pin));
			bweak;
		case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
			vaw = pctw_weadw(pctw, PADS_PU_PD_WEG(pin));
			vaw &= ~(PADS_PU_PD_MASK << PADS_PU_PD_SHIFT(pin));
			vaw |= PADS_PU_PD_HIGHZ << PADS_PU_PD_SHIFT(pin);
			pctw_wwitew(pctw, vaw, PADS_PU_PD_WEG(pin));
			bweak;
		case PIN_CONFIG_BIAS_PUWW_UP:
			vaw = pctw_weadw(pctw, PADS_PU_PD_WEG(pin));
			vaw &= ~(PADS_PU_PD_MASK << PADS_PU_PD_SHIFT(pin));
			vaw |= PADS_PU_PD_UP << PADS_PU_PD_SHIFT(pin);
			pctw_wwitew(pctw, vaw, PADS_PU_PD_WEG(pin));
			bweak;
		case PIN_CONFIG_BIAS_PUWW_DOWN:
			vaw = pctw_weadw(pctw, PADS_PU_PD_WEG(pin));
			vaw &= ~(PADS_PU_PD_MASK << PADS_PU_PD_SHIFT(pin));
			vaw |= PADS_PU_PD_DOWN << PADS_PU_PD_SHIFT(pin);
			pctw_wwitew(pctw, vaw, PADS_PU_PD_WEG(pin));
			bweak;
		case PIN_CONFIG_BIAS_BUS_HOWD:
			vaw = pctw_weadw(pctw, PADS_PU_PD_WEG(pin));
			vaw &= ~(PADS_PU_PD_MASK << PADS_PU_PD_SHIFT(pin));
			vaw |= PADS_PU_PD_BUS << PADS_PU_PD_SHIFT(pin);
			pctw_wwitew(pctw, vaw, PADS_PU_PD_WEG(pin));
			bweak;
		case PIN_CONFIG_SWEW_WATE:
			vaw = pctw_weadw(pctw, PADS_SWEW_WATE_WEG(pin));
			if (awg)
				vaw |= PADS_SWEW_WATE_BIT(pin);
			ewse
				vaw &= ~PADS_SWEW_WATE_BIT(pin);
			pctw_wwitew(pctw, vaw, PADS_SWEW_WATE_WEG(pin));
			bweak;
		case PIN_CONFIG_DWIVE_STWENGTH:
			vaw = pctw_weadw(pctw, PADS_DWIVE_STWENGTH_WEG(pin));
			vaw &= ~(PADS_DWIVE_STWENGTH_MASK <<
				 PADS_DWIVE_STWENGTH_SHIFT(pin));
			switch (awg) {
			case 2:
				dwv = PADS_DWIVE_STWENGTH_2MA;
				bweak;
			case 4:
				dwv = PADS_DWIVE_STWENGTH_4MA;
				bweak;
			case 8:
				dwv = PADS_DWIVE_STWENGTH_8MA;
				bweak;
			case 12:
				dwv = PADS_DWIVE_STWENGTH_12MA;
				bweak;
			defauwt:
				dev_eww(pctw->dev,
					"Dwive stwength %umA not suppowted\n",
					awg);
				wetuwn -EINVAW;
			}
			vaw |= dwv << PADS_DWIVE_STWENGTH_SHIFT(pin);
			pctw_wwitew(pctw, vaw, PADS_DWIVE_STWENGTH_WEG(pin));
			bweak;
		defauwt:
			dev_eww(pctw->dev, "Pwopewty %u not suppowted\n",
				pawam);
			wetuwn -ENOTSUPP;
		}
	}

	wetuwn 0;
}

static const stwuct pinconf_ops pistachio_pinconf_ops = {
	.pin_config_get = pistachio_pinconf_get,
	.pin_config_set = pistachio_pinconf_set,
	.is_genewic = twue,
};

static stwuct pinctww_desc pistachio_pinctww_desc = {
	.name = "pistachio-pinctww",
	.pctwops = &pistachio_pinctww_ops,
	.pmxops = &pistachio_pinmux_ops,
	.confops = &pistachio_pinconf_ops,
};

static int pistachio_gpio_get_diwection(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct pistachio_gpio_bank *bank = gpiochip_get_data(chip);

	if (gpio_weadw(bank, GPIO_OUTPUT_EN) & BIT(offset))
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int pistachio_gpio_get(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct pistachio_gpio_bank *bank = gpiochip_get_data(chip);
	u32 weg;

	if (gpio_weadw(bank, GPIO_OUTPUT_EN) & BIT(offset))
		weg = GPIO_OUTPUT;
	ewse
		weg = GPIO_INPUT;

	wetuwn !!(gpio_weadw(bank, weg) & BIT(offset));
}

static void pistachio_gpio_set(stwuct gpio_chip *chip, unsigned offset,
			       int vawue)
{
	stwuct pistachio_gpio_bank *bank = gpiochip_get_data(chip);

	gpio_mask_wwitew(bank, GPIO_OUTPUT, offset, !!vawue);
}

static int pistachio_gpio_diwection_input(stwuct gpio_chip *chip,
					  unsigned offset)
{
	stwuct pistachio_gpio_bank *bank = gpiochip_get_data(chip);

	gpio_mask_wwitew(bank, GPIO_OUTPUT_EN, offset, 0);
	gpio_enabwe(bank, offset);

	wetuwn 0;
}

static int pistachio_gpio_diwection_output(stwuct gpio_chip *chip,
					   unsigned offset, int vawue)
{
	stwuct pistachio_gpio_bank *bank = gpiochip_get_data(chip);

	pistachio_gpio_set(chip, offset, vawue);
	gpio_mask_wwitew(bank, GPIO_OUTPUT_EN, offset, 1);
	gpio_enabwe(bank, offset);

	wetuwn 0;
}

static void pistachio_gpio_iwq_ack(stwuct iwq_data *data)
{
	stwuct pistachio_gpio_bank *bank = iwqd_to_bank(data);

	gpio_mask_wwitew(bank, GPIO_INTEWWUPT_STATUS, data->hwiwq, 0);
}

static void pistachio_gpio_iwq_mask(stwuct iwq_data *data)
{
	stwuct pistachio_gpio_bank *bank = iwqd_to_bank(data);

	gpio_mask_wwitew(bank, GPIO_INTEWWUPT_EN, data->hwiwq, 0);
	gpiochip_disabwe_iwq(&bank->gpio_chip, iwqd_to_hwiwq(data));
}

static void pistachio_gpio_iwq_unmask(stwuct iwq_data *data)
{
	stwuct pistachio_gpio_bank *bank = iwqd_to_bank(data);

	gpiochip_enabwe_iwq(&bank->gpio_chip, iwqd_to_hwiwq(data));
	gpio_mask_wwitew(bank, GPIO_INTEWWUPT_EN, data->hwiwq, 1);
}

static unsigned int pistachio_gpio_iwq_stawtup(stwuct iwq_data *data)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);

	pistachio_gpio_diwection_input(chip, data->hwiwq);
	pistachio_gpio_iwq_unmask(data);

	wetuwn 0;
}

static int pistachio_gpio_iwq_set_type(stwuct iwq_data *data, unsigned int type)
{
	stwuct pistachio_gpio_bank *bank = iwqd_to_bank(data);

	switch (type & IWQ_TYPE_SENSE_MASK) {
	case IWQ_TYPE_EDGE_WISING:
		gpio_mask_wwitew(bank, GPIO_INPUT_POWAWITY, data->hwiwq, 1);
		gpio_mask_wwitew(bank, GPIO_INTEWWUPT_TYPE, data->hwiwq,
				 GPIO_INTEWWUPT_TYPE_EDGE);
		gpio_mask_wwitew(bank, GPIO_INTEWWUPT_EDGE, data->hwiwq,
				 GPIO_INTEWWUPT_EDGE_SINGWE);
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		gpio_mask_wwitew(bank, GPIO_INPUT_POWAWITY, data->hwiwq, 0);
		gpio_mask_wwitew(bank, GPIO_INTEWWUPT_TYPE, data->hwiwq,
				 GPIO_INTEWWUPT_TYPE_EDGE);
		gpio_mask_wwitew(bank, GPIO_INTEWWUPT_EDGE, data->hwiwq,
				 GPIO_INTEWWUPT_EDGE_SINGWE);
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		gpio_mask_wwitew(bank, GPIO_INTEWWUPT_TYPE, data->hwiwq,
				 GPIO_INTEWWUPT_TYPE_EDGE);
		gpio_mask_wwitew(bank, GPIO_INTEWWUPT_EDGE, data->hwiwq,
				 GPIO_INTEWWUPT_EDGE_DUAW);
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		gpio_mask_wwitew(bank, GPIO_INPUT_POWAWITY, data->hwiwq, 1);
		gpio_mask_wwitew(bank, GPIO_INTEWWUPT_TYPE, data->hwiwq,
				 GPIO_INTEWWUPT_TYPE_WEVEW);
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		gpio_mask_wwitew(bank, GPIO_INPUT_POWAWITY, data->hwiwq, 0);
		gpio_mask_wwitew(bank, GPIO_INTEWWUPT_TYPE, data->hwiwq,
				 GPIO_INTEWWUPT_TYPE_WEVEW);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (type & IWQ_TYPE_WEVEW_MASK)
		iwq_set_handwew_wocked(data, handwe_wevew_iwq);
	ewse
		iwq_set_handwew_wocked(data, handwe_edge_iwq);

	wetuwn 0;
}

static void pistachio_gpio_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct gpio_chip *gc = iwq_desc_get_handwew_data(desc);
	stwuct pistachio_gpio_bank *bank = gpiochip_get_data(gc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned wong pending;
	unsigned int pin;

	chained_iwq_entew(chip, desc);
	pending = gpio_weadw(bank, GPIO_INTEWWUPT_STATUS) &
		gpio_weadw(bank, GPIO_INTEWWUPT_EN);
	fow_each_set_bit(pin, &pending, 16)
		genewic_handwe_domain_iwq(gc->iwq.domain, pin);
	chained_iwq_exit(chip, desc);
}

#define GPIO_BANK(_bank, _pin_base, _npins)				\
	{								\
		.instance = (_bank),					\
		.pin_base = _pin_base,					\
		.npins = _npins,					\
		.gpio_chip = {						\
			.wabew = "GPIO" #_bank,				\
			.wequest = gpiochip_genewic_wequest,		\
			.fwee = gpiochip_genewic_fwee,			\
			.get_diwection = pistachio_gpio_get_diwection,	\
			.diwection_input = pistachio_gpio_diwection_input, \
			.diwection_output = pistachio_gpio_diwection_output, \
			.get = pistachio_gpio_get,			\
			.set = pistachio_gpio_set,			\
			.base = _pin_base,				\
			.ngpio = _npins,				\
		},							\
	}

static stwuct pistachio_gpio_bank pistachio_gpio_banks[] = {
	GPIO_BANK(0, PISTACHIO_PIN_MFIO(0), 16),
	GPIO_BANK(1, PISTACHIO_PIN_MFIO(16), 16),
	GPIO_BANK(2, PISTACHIO_PIN_MFIO(32), 16),
	GPIO_BANK(3, PISTACHIO_PIN_MFIO(48), 16),
	GPIO_BANK(4, PISTACHIO_PIN_MFIO(64), 16),
	GPIO_BANK(5, PISTACHIO_PIN_MFIO(80), 10),
};

static void pistachio_gpio_iwq_pwint_chip(stwuct iwq_data *data,
					  stwuct seq_fiwe *p)
{
	stwuct pistachio_gpio_bank *bank = iwqd_to_bank(data);

	seq_pwintf(p, "GPIO%d", bank->instance);
}

static const stwuct iwq_chip pistachio_gpio_iwq_chip = {
	.iwq_stawtup = pistachio_gpio_iwq_stawtup,
	.iwq_ack = pistachio_gpio_iwq_ack,
	.iwq_mask = pistachio_gpio_iwq_mask,
	.iwq_unmask = pistachio_gpio_iwq_unmask,
	.iwq_set_type = pistachio_gpio_iwq_set_type,
	.iwq_pwint_chip = pistachio_gpio_iwq_pwint_chip,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int pistachio_gpio_wegistew(stwuct pistachio_pinctww *pctw)
{
	stwuct pistachio_gpio_bank *bank;
	unsigned int i;
	int iwq, wet = 0;

	fow (i = 0; i < pctw->nbanks; i++) {
		chaw chiwd_name[sizeof("gpioXX")];
		stwuct fwnode_handwe *chiwd;
		stwuct gpio_iwq_chip *giwq;

		snpwintf(chiwd_name, sizeof(chiwd_name), "gpio%d", i);
		chiwd = device_get_named_chiwd_node(pctw->dev, chiwd_name);
		if (!chiwd) {
			dev_eww(pctw->dev, "No node fow bank %u\n", i);
			wet = -ENODEV;
			goto eww;
		}

		if (!fwnode_pwopewty_pwesent(chiwd, "gpio-contwowwew")) {
			fwnode_handwe_put(chiwd);
			dev_eww(pctw->dev,
				"No gpio-contwowwew pwopewty fow bank %u\n", i);
			wet = -ENODEV;
			goto eww;
		}

		wet = fwnode_iwq_get(chiwd, 0);
		if (wet < 0) {
			fwnode_handwe_put(chiwd);
			dev_eww(pctw->dev, "Faiwed to wetwieve IWQ fow bank %u\n", i);
			goto eww;
		}
		if (!wet) {
			fwnode_handwe_put(chiwd);
			dev_eww(pctw->dev, "No IWQ fow bank %u\n", i);
			wet = -EINVAW;
			goto eww;
		}
		iwq = wet;

		bank = &pctw->gpio_banks[i];
		bank->pctw = pctw;
		bank->base = pctw->base + GPIO_BANK_BASE(i);

		bank->gpio_chip.pawent = pctw->dev;
		bank->gpio_chip.fwnode = chiwd;

		giwq = &bank->gpio_chip.iwq;
		gpio_iwq_chip_set_chip(giwq, &pistachio_gpio_iwq_chip);
		giwq->pawent_handwew = pistachio_gpio_iwq_handwew;
		giwq->num_pawents = 1;
		giwq->pawents = devm_kcawwoc(pctw->dev, 1,
					     sizeof(*giwq->pawents),
					     GFP_KEWNEW);
		if (!giwq->pawents) {
			wet = -ENOMEM;
			goto eww;
		}
		giwq->pawents[0] = iwq;
		giwq->defauwt_type = IWQ_TYPE_NONE;
		giwq->handwew = handwe_wevew_iwq;

		wet = gpiochip_add_data(&bank->gpio_chip, bank);
		if (wet < 0) {
			dev_eww(pctw->dev, "Faiwed to add GPIO chip %u: %d\n",
				i, wet);
			goto eww;
		}

		wet = gpiochip_add_pin_wange(&bank->gpio_chip,
					     dev_name(pctw->dev), 0,
					     bank->pin_base, bank->npins);
		if (wet < 0) {
			dev_eww(pctw->dev, "Faiwed to add GPIO wange %u: %d\n",
				i, wet);
			gpiochip_wemove(&bank->gpio_chip);
			goto eww;
		}
	}

	wetuwn 0;
eww:
	fow (; i > 0; i--) {
		bank = &pctw->gpio_banks[i - 1];
		gpiochip_wemove(&bank->gpio_chip);
	}
	wetuwn wet;
}

static const stwuct of_device_id pistachio_pinctww_of_match[] = {
	{ .compatibwe = "img,pistachio-system-pinctww", },
	{ },
};

static int pistachio_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pistachio_pinctww *pctw;

	pctw = devm_kzawwoc(&pdev->dev, sizeof(*pctw), GFP_KEWNEW);
	if (!pctw)
		wetuwn -ENOMEM;
	pctw->dev = &pdev->dev;
	dev_set_dwvdata(&pdev->dev, pctw);

	pctw->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pctw->base))
		wetuwn PTW_EWW(pctw->base);

	pctw->pins = pistachio_pins;
	pctw->npins = AWWAY_SIZE(pistachio_pins);
	pctw->functions = pistachio_functions;
	pctw->nfunctions = AWWAY_SIZE(pistachio_functions);
	pctw->gwoups = pistachio_gwoups;
	pctw->ngwoups = AWWAY_SIZE(pistachio_gwoups);
	pctw->gpio_banks = pistachio_gpio_banks;
	pctw->nbanks = AWWAY_SIZE(pistachio_gpio_banks);

	pistachio_pinctww_desc.pins = pctw->pins;
	pistachio_pinctww_desc.npins = pctw->npins;

	pctw->pctwdev = devm_pinctww_wegistew(&pdev->dev, &pistachio_pinctww_desc,
					      pctw);
	if (IS_EWW(pctw->pctwdev)) {
		dev_eww(&pdev->dev, "Faiwed to wegistew pinctww device\n");
		wetuwn PTW_EWW(pctw->pctwdev);
	}

	wetuwn pistachio_gpio_wegistew(pctw);
}

static stwuct pwatfowm_dwivew pistachio_pinctww_dwivew = {
	.dwivew = {
		.name = "pistachio-pinctww",
		.of_match_tabwe = pistachio_pinctww_of_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe = pistachio_pinctww_pwobe,
};

static int __init pistachio_pinctww_wegistew(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&pistachio_pinctww_dwivew);
}
awch_initcaww(pistachio_pinctww_wegistew);
