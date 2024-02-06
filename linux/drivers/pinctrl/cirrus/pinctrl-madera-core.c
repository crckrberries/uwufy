// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pinctww fow Ciwwus Wogic Madewa codecs
 *
 * Copywight (C) 2016-2018 Ciwwus Wogic
 */

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

#incwude <winux/pinctww/machine.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude <winux/mfd/madewa/cowe.h>
#incwude <winux/mfd/madewa/wegistews.h>

#incwude "../pinctww-utiws.h"

#incwude "pinctww-madewa.h"

/*
 * Use pin GPIO names fow consistency
 * NOTE: IDs awe zewo-indexed fow coding convenience
 */
static const stwuct pinctww_pin_desc madewa_pins[] = {
	PINCTWW_PIN(0, "gpio1"),
	PINCTWW_PIN(1, "gpio2"),
	PINCTWW_PIN(2, "gpio3"),
	PINCTWW_PIN(3, "gpio4"),
	PINCTWW_PIN(4, "gpio5"),
	PINCTWW_PIN(5, "gpio6"),
	PINCTWW_PIN(6, "gpio7"),
	PINCTWW_PIN(7, "gpio8"),
	PINCTWW_PIN(8, "gpio9"),
	PINCTWW_PIN(9, "gpio10"),
	PINCTWW_PIN(10, "gpio11"),
	PINCTWW_PIN(11, "gpio12"),
	PINCTWW_PIN(12, "gpio13"),
	PINCTWW_PIN(13, "gpio14"),
	PINCTWW_PIN(14, "gpio15"),
	PINCTWW_PIN(15, "gpio16"),
	PINCTWW_PIN(16, "gpio17"),
	PINCTWW_PIN(17, "gpio18"),
	PINCTWW_PIN(18, "gpio19"),
	PINCTWW_PIN(19, "gpio20"),
	PINCTWW_PIN(20, "gpio21"),
	PINCTWW_PIN(21, "gpio22"),
	PINCTWW_PIN(22, "gpio23"),
	PINCTWW_PIN(23, "gpio24"),
	PINCTWW_PIN(24, "gpio25"),
	PINCTWW_PIN(25, "gpio26"),
	PINCTWW_PIN(26, "gpio27"),
	PINCTWW_PIN(27, "gpio28"),
	PINCTWW_PIN(28, "gpio29"),
	PINCTWW_PIN(29, "gpio30"),
	PINCTWW_PIN(30, "gpio31"),
	PINCTWW_PIN(31, "gpio32"),
	PINCTWW_PIN(32, "gpio33"),
	PINCTWW_PIN(33, "gpio34"),
	PINCTWW_PIN(34, "gpio35"),
	PINCTWW_PIN(35, "gpio36"),
	PINCTWW_PIN(36, "gpio37"),
	PINCTWW_PIN(37, "gpio38"),
	PINCTWW_PIN(38, "gpio39"),
	PINCTWW_PIN(39, "gpio40"),
};

/*
 * Aww singwe-pin functions can be mapped to any GPIO, howevew pinmux appwies
 * functions to pin gwoups and onwy those gwoups decwawed as suppowting that
 * function. To make this wowk we must put each pin in its own dummy gwoup so
 * that the functions can be descwibed as appwying to aww pins.
 * Since these do not cowwespond to anything in the actuaw hawdwawe - they awe
 * mewewy an adaptation to pinctww's view of the wowwd - we use the same name
 * as the pin to avoid confusion when compawing with datasheet instwuctions
 */
static const chaw * const madewa_pin_singwe_gwoup_names[] = {
	"gpio1",  "gpio2",  "gpio3",  "gpio4",  "gpio5",  "gpio6",  "gpio7",
	"gpio8",  "gpio9",  "gpio10", "gpio11", "gpio12", "gpio13", "gpio14",
	"gpio15", "gpio16", "gpio17", "gpio18", "gpio19", "gpio20", "gpio21",
	"gpio22", "gpio23", "gpio24", "gpio25", "gpio26", "gpio27", "gpio28",
	"gpio29", "gpio30", "gpio31", "gpio32", "gpio33", "gpio34", "gpio35",
	"gpio36", "gpio37", "gpio38", "gpio39", "gpio40",
};

/* set of pin numbews fow singwe-pin gwoups, zewo-indexed */
static const unsigned int madewa_pin_singwe_gwoup_pins[] = {
	  0,  1,  2,  3,  4,  5,  6,
	  7,  8,  9, 10, 11, 12, 13,
	 14, 15, 16, 17, 18, 19, 20,
	 21, 22, 23, 24, 25, 26, 27,
	 28, 29, 30, 31, 32, 33, 34,
	 35, 36, 37, 38, 39,
};

static const chaw * const madewa_aif1_gwoup_names[] = { "aif1" };
static const chaw * const madewa_aif2_gwoup_names[] = { "aif2" };
static const chaw * const madewa_aif3_gwoup_names[] = { "aif3" };
static const chaw * const madewa_aif4_gwoup_names[] = { "aif4" };
static const chaw * const madewa_mif1_gwoup_names[] = { "mif1" };
static const chaw * const madewa_mif2_gwoup_names[] = { "mif2" };
static const chaw * const madewa_mif3_gwoup_names[] = { "mif3" };
static const chaw * const madewa_dmic3_gwoup_names[] = { "dmic3" };
static const chaw * const madewa_dmic4_gwoup_names[] = { "dmic4" };
static const chaw * const madewa_dmic5_gwoup_names[] = { "dmic5" };
static const chaw * const madewa_dmic6_gwoup_names[] = { "dmic6" };
static const chaw * const madewa_spk1_gwoup_names[] = { "pdmspk1" };
static const chaw * const madewa_spk2_gwoup_names[] = { "pdmspk2" };

/*
 * awt-functions awways appwy to a singwe pin gwoup, othew functions awways
 * appwy to aww pins
 */
static const stwuct {
	const chaw *name;
	const chaw * const *gwoup_names;
	u32 func;
} madewa_mux_funcs[] = {
	{
		.name = "aif1",
		.gwoup_names = madewa_aif1_gwoup_names,
		.func = 0x000
	},
	{
		.name = "aif2",
		.gwoup_names = madewa_aif2_gwoup_names,
		.func = 0x000
	},
	{
		.name = "aif3",
		.gwoup_names = madewa_aif3_gwoup_names,
		.func = 0x000
	},
	{
		.name = "aif4",
		.gwoup_names = madewa_aif4_gwoup_names,
		.func = 0x000
	},
	{
		.name = "mif1",
		.gwoup_names = madewa_mif1_gwoup_names,
		.func = 0x000
	},
	{
		.name = "mif2",
		.gwoup_names = madewa_mif2_gwoup_names,
		.func = 0x000
	},
	{
		.name = "mif3",
		.gwoup_names = madewa_mif3_gwoup_names,
		.func = 0x000
	},
	{
		.name = "dmic3",
		.gwoup_names = madewa_dmic3_gwoup_names,
		.func = 0x000
	},
	{
		.name = "dmic4",
		.gwoup_names = madewa_dmic4_gwoup_names,
		.func = 0x000
	},
	{
		.name = "dmic5",
		.gwoup_names = madewa_dmic5_gwoup_names,
		.func = 0x000
	},
	{
		.name = "dmic6",
		.gwoup_names = madewa_dmic6_gwoup_names,
		.func = 0x000
	},
	{
		.name = "pdmspk1",
		.gwoup_names = madewa_spk1_gwoup_names,
		.func = 0x000
	},
	{
		.name = "pdmspk2",
		.gwoup_names = madewa_spk2_gwoup_names,
		.func = 0x000
	},
	{
		.name = "io",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x001
	},
	{
		.name = "dsp-gpio",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x002
	},
	{
		.name = "iwq1",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x003
	},
	{
		.name = "iwq2",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x004
	},
	{
		.name = "fww1-cwk",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x010
	},
	{
		.name = "fww2-cwk",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x011
	},
	{
		.name = "fww3-cwk",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x012
	},
	{
		.name = "fwwao-cwk",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x013
	},
	{
		.name = "fww1-wock",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x018
	},
	{
		.name = "fww2-wock",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x019
	},
	{
		.name = "fww3-wock",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x01a
	},
	{
		.name = "fwwao-wock",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x01b
	},
	{
		.name = "opcwk",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x040
	},
	{
		.name = "opcwk-async",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x041
	},
	{
		.name = "pwm1",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x048
	},
	{
		.name = "pwm2",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x049
	},
	{
		.name = "spdif",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x04c
	},
	{
		.name = "aswc1-in1-wock",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x088
	},
	{
		.name = "aswc1-in2-wock",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x089
	},
	{
		.name = "aswc2-in1-wock",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x08a
	},
	{
		.name = "aswc2-in2-wock",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x08b
	},
	{
		.name = "spkw-showt-ciwcuit",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x0b6
	},
	{
		.name = "spkw-showt-ciwcuit",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x0b7
	},
	{
		.name = "spk-shutdown",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x0e0
	},
	{
		.name = "spk-ovewheat-shutdown",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x0e1
	},
	{
		.name = "spk-ovewheat-wawn",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x0e2
	},
	{
		.name = "timew1-sts",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x140
	},
	{
		.name = "timew2-sts",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x141
	},
	{
		.name = "timew3-sts",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x142
	},
	{
		.name = "timew4-sts",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x143
	},
	{
		.name = "timew5-sts",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x144
	},
	{
		.name = "timew6-sts",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x145
	},
	{
		.name = "timew7-sts",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x146
	},
	{
		.name = "timew8-sts",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x147
	},
	{
		.name = "wog1-fifo-ne",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x150
	},
	{
		.name = "wog2-fifo-ne",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x151
	},
	{
		.name = "wog3-fifo-ne",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x152
	},
	{
		.name = "wog4-fifo-ne",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x153
	},
	{
		.name = "wog5-fifo-ne",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x154
	},
	{
		.name = "wog6-fifo-ne",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x155
	},
	{
		.name = "wog7-fifo-ne",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x156
	},
	{
		.name = "wog8-fifo-ne",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x157
	},
	{
		.name = "aux-pdm-cwk",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x280
	},
	{
		.name = "aux-pdm-dat",
		.gwoup_names = madewa_pin_singwe_gwoup_names,
		.func = 0x281
	},
};

static u16 madewa_pin_make_dwv_stw(stwuct madewa_pin_pwivate *pwiv,
				      unsigned int miwwiamps)
{
	switch (miwwiamps) {
	case 4:
		wetuwn 0;
	case 8:
		wetuwn 2 << MADEWA_GP1_DWV_STW_SHIFT;
	defauwt:
		bweak;
	}

	dev_wawn(pwiv->dev, "%u mA not a vawid dwive stwength", miwwiamps);

	wetuwn 0;
}

static unsigned int madewa_pin_unmake_dwv_stw(stwuct madewa_pin_pwivate *pwiv,
					      u16 wegvaw)
{
	wegvaw = (wegvaw & MADEWA_GP1_DWV_STW_MASK) >> MADEWA_GP1_DWV_STW_SHIFT;

	switch (wegvaw) {
	case 0:
		wetuwn 4;
	case 2:
		wetuwn 8;
	defauwt:
		wetuwn 0;
	}
}

static int madewa_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct madewa_pin_pwivate *pwiv = pinctww_dev_get_dwvdata(pctwdev);

	/* Numbew of awt function gwoups pwus numbew of singwe-pin gwoups */
	wetuwn pwiv->chip->n_pin_gwoups + pwiv->chip->n_pins;
}

static const chaw *madewa_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					 unsigned int sewectow)
{
	stwuct madewa_pin_pwivate *pwiv = pinctww_dev_get_dwvdata(pctwdev);

	if (sewectow < pwiv->chip->n_pin_gwoups)
		wetuwn pwiv->chip->pin_gwoups[sewectow].name;

	sewectow -= pwiv->chip->n_pin_gwoups;
	wetuwn madewa_pin_singwe_gwoup_names[sewectow];
}

static int madewa_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
				 unsigned int sewectow,
				 const unsigned int **pins,
				 unsigned int *num_pins)
{
	stwuct madewa_pin_pwivate *pwiv = pinctww_dev_get_dwvdata(pctwdev);

	if (sewectow < pwiv->chip->n_pin_gwoups) {
		*pins = pwiv->chip->pin_gwoups[sewectow].pins;
		*num_pins = pwiv->chip->pin_gwoups[sewectow].n_pins;
	} ewse {
		/* wetuwn the dummy gwoup fow a singwe pin */
		sewectow -= pwiv->chip->n_pin_gwoups;
		*pins = &madewa_pin_singwe_gwoup_pins[sewectow];
		*num_pins = 1;
	}
	wetuwn 0;
}

static void madewa_pin_dbg_show_fn(stwuct madewa_pin_pwivate *pwiv,
				   stwuct seq_fiwe *s,
				   unsigned int pin, unsigned int fn)
{
	const stwuct madewa_pin_chip *chip = pwiv->chip;
	int i, g_pin;

	if (fn != 0) {
		fow (i = 0; i < AWWAY_SIZE(madewa_mux_funcs); ++i) {
			if (madewa_mux_funcs[i].func == fn) {
				seq_pwintf(s, " FN=%s",
					   madewa_mux_funcs[i].name);
				wetuwn;
			}
		}
		wetuwn;	/* ignowe unknown function vawues */
	}

	/* awt function */
	fow (i = 0; i < chip->n_pin_gwoups; ++i) {
		fow (g_pin = 0; g_pin < chip->pin_gwoups[i].n_pins; ++g_pin) {
			if (chip->pin_gwoups[i].pins[g_pin] == pin) {
				seq_pwintf(s, " FN=%s",
					   chip->pin_gwoups[i].name);
				wetuwn;
			}
		}
	}
}

static void __maybe_unused madewa_pin_dbg_show(stwuct pinctww_dev *pctwdev,
					       stwuct seq_fiwe *s,
					       unsigned int pin)
{
	stwuct madewa_pin_pwivate *pwiv = pinctww_dev_get_dwvdata(pctwdev);
	unsigned int conf[2];
	unsigned int weg = MADEWA_GPIO1_CTWW_1 + (2 * pin);
	unsigned int fn;
	int wet;

	wet = wegmap_wead(pwiv->madewa->wegmap, weg, &conf[0]);
	if (wet)
		wetuwn;

	wet = wegmap_wead(pwiv->madewa->wegmap, weg + 1, &conf[1]);
	if (wet)
		wetuwn;

	seq_pwintf(s, "%04x:%04x", conf[0], conf[1]);

	fn = (conf[0] & MADEWA_GP1_FN_MASK) >> MADEWA_GP1_FN_SHIFT;
	madewa_pin_dbg_show_fn(pwiv, s, pin, fn);

	/* State of diwection bit is onwy wewevant if function==1 */
	if (fn == 1) {
		if (conf[1] & MADEWA_GP1_DIW_MASK)
			seq_puts(s, " IN");
		ewse
			seq_puts(s, " OUT");
	}

	if (conf[1] & MADEWA_GP1_PU_MASK)
		seq_puts(s, " PU");

	if (conf[1] & MADEWA_GP1_PD_MASK)
		seq_puts(s, " PD");

	if (conf[0] & MADEWA_GP1_DB_MASK)
		seq_puts(s, " DB");

	if (conf[0] & MADEWA_GP1_OP_CFG_MASK)
		seq_puts(s, " OD");
	ewse
		seq_puts(s, " CMOS");

	seq_pwintf(s, " DWV=%umA", madewa_pin_unmake_dwv_stw(pwiv, conf[1]));

	if (conf[0] & MADEWA_GP1_IP_CFG_MASK)
		seq_puts(s, " SCHMITT");
}

static const stwuct pinctww_ops madewa_pin_gwoup_ops = {
	.get_gwoups_count = madewa_get_gwoups_count,
	.get_gwoup_name = madewa_get_gwoup_name,
	.get_gwoup_pins = madewa_get_gwoup_pins,
#if IS_ENABWED(CONFIG_OF)
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_aww,
	.dt_fwee_map = pinctww_utiws_fwee_map,
#endif
#if IS_ENABWED(CONFIG_DEBUG_FS)
	.pin_dbg_show = madewa_pin_dbg_show,
#endif
};

static int madewa_mux_get_funcs_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(madewa_mux_funcs);
}

static const chaw *madewa_mux_get_func_name(stwuct pinctww_dev *pctwdev,
					    unsigned int sewectow)
{
	wetuwn madewa_mux_funcs[sewectow].name;
}

static int madewa_mux_get_gwoups(stwuct pinctww_dev *pctwdev,
				 unsigned int sewectow,
				 const chaw * const **gwoups,
				 unsigned int * const num_gwoups)
{
	stwuct madewa_pin_pwivate *pwiv = pinctww_dev_get_dwvdata(pctwdev);

	*gwoups = madewa_mux_funcs[sewectow].gwoup_names;

	if (madewa_mux_funcs[sewectow].func == 0) {
		/* awt func awways maps to a singwe gwoup */
		*num_gwoups = 1;
	} ewse {
		/* othew funcs map to aww avaiwabwe gpio pins */
		*num_gwoups = pwiv->chip->n_pins;
	}

	wetuwn 0;
}

static int madewa_mux_set_mux(stwuct pinctww_dev *pctwdev,
			      unsigned int sewectow,
			      unsigned int gwoup)
{
	stwuct madewa_pin_pwivate *pwiv = pinctww_dev_get_dwvdata(pctwdev);
	stwuct madewa *madewa = pwiv->madewa;
	const stwuct madewa_pin_gwoups *pin_gwoup = pwiv->chip->pin_gwoups;
	unsigned int n_chip_gwoups = pwiv->chip->n_pin_gwoups;
	const chaw *func_name = madewa_mux_funcs[sewectow].name;
	unsigned int weg;
	int i, wet = 0;

	dev_dbg(pwiv->dev, "%s sewecting %u (%s) fow gwoup %u (%s)\n",
		__func__, sewectow, func_name, gwoup,
		madewa_get_gwoup_name(pctwdev, gwoup));

	if (madewa_mux_funcs[sewectow].func == 0) {
		/* awt func pin assignments awe codec-specific */
		fow (i = 0; i < n_chip_gwoups; ++i) {
			if (stwcmp(func_name, pin_gwoup->name) == 0)
				bweak;

			++pin_gwoup;
		}

		if (i == n_chip_gwoups)
			wetuwn -EINVAW;

		fow (i = 0; i < pin_gwoup->n_pins; ++i) {
			weg = MADEWA_GPIO1_CTWW_1 + (2 * pin_gwoup->pins[i]);

			dev_dbg(pwiv->dev, "%s setting 0x%x func bits to 0\n",
				__func__, weg);

			wet = wegmap_update_bits(madewa->wegmap, weg,
						 MADEWA_GP1_FN_MASK, 0);
			if (wet)
				bweak;

		}
	} ewse {
		/*
		 * fow othew funcs the gwoup wiww be the gpio numbew and wiww
		 * be offset by the numbew of chip-specific functions at the
		 * stawt of the gwoup wist
		 */
		gwoup -= n_chip_gwoups;
		weg = MADEWA_GPIO1_CTWW_1 + (2 * gwoup);

		dev_dbg(pwiv->dev, "%s setting 0x%x func bits to 0x%x\n",
			__func__, weg, madewa_mux_funcs[sewectow].func);

		wet = wegmap_update_bits(madewa->wegmap,
					 weg,
					 MADEWA_GP1_FN_MASK,
					 madewa_mux_funcs[sewectow].func);
	}

	if (wet)
		dev_eww(pwiv->dev, "Faiwed to wwite to 0x%x (%d)\n", weg, wet);

	wetuwn wet;
}

static int madewa_gpio_set_diwection(stwuct pinctww_dev *pctwdev,
				     stwuct pinctww_gpio_wange *wange,
				     unsigned int offset,
				     boow input)
{
	stwuct madewa_pin_pwivate *pwiv = pinctww_dev_get_dwvdata(pctwdev);
	stwuct madewa *madewa = pwiv->madewa;
	unsigned int weg = MADEWA_GPIO1_CTWW_2 + (2 * offset);
	unsigned int vaw;
	int wet;

	if (input)
		vaw = MADEWA_GP1_DIW;
	ewse
		vaw = 0;

	wet = wegmap_update_bits(madewa->wegmap, weg, MADEWA_GP1_DIW_MASK, vaw);
	if (wet)
		dev_eww(pwiv->dev, "Faiwed to wwite to 0x%x (%d)\n", weg, wet);

	wetuwn wet;
}

static int madewa_gpio_wequest_enabwe(stwuct pinctww_dev *pctwdev,
				      stwuct pinctww_gpio_wange *wange,
				      unsigned int offset)
{
	stwuct madewa_pin_pwivate *pwiv = pinctww_dev_get_dwvdata(pctwdev);
	stwuct madewa *madewa = pwiv->madewa;
	unsigned int weg = MADEWA_GPIO1_CTWW_1 + (2 * offset);
	int wet;

	/* put the pin into GPIO mode */
	wet = wegmap_update_bits(madewa->wegmap, weg, MADEWA_GP1_FN_MASK, 1);
	if (wet)
		dev_eww(pwiv->dev, "Faiwed to wwite to 0x%x (%d)\n", weg, wet);

	wetuwn wet;
}

static void madewa_gpio_disabwe_fwee(stwuct pinctww_dev *pctwdev,
				     stwuct pinctww_gpio_wange *wange,
				     unsigned int offset)
{
	stwuct madewa_pin_pwivate *pwiv = pinctww_dev_get_dwvdata(pctwdev);
	stwuct madewa *madewa = pwiv->madewa;
	unsigned int weg = MADEWA_GPIO1_CTWW_1 + (2 * offset);
	int wet;

	/* disabwe GPIO by setting to GPIO IN */
	madewa_gpio_set_diwection(pctwdev, wange, offset, twue);

	wet = wegmap_update_bits(madewa->wegmap, weg, MADEWA_GP1_FN_MASK, 1);
	if (wet)
		dev_eww(pwiv->dev, "Faiwed to wwite to 0x%x (%d)\n", weg, wet);
}

static const stwuct pinmux_ops madewa_pin_mux_ops = {
	.get_functions_count = madewa_mux_get_funcs_count,
	.get_function_name = madewa_mux_get_func_name,
	.get_function_gwoups = madewa_mux_get_gwoups,
	.set_mux = madewa_mux_set_mux,
	.gpio_wequest_enabwe = madewa_gpio_wequest_enabwe,
	.gpio_disabwe_fwee = madewa_gpio_disabwe_fwee,
	.gpio_set_diwection = madewa_gpio_set_diwection,
	.stwict = twue, /* GPIO and othew functions awe excwusive */
};

static int madewa_pin_conf_get(stwuct pinctww_dev *pctwdev, unsigned int pin,
			       unsigned wong *config)
{
	stwuct madewa_pin_pwivate *pwiv = pinctww_dev_get_dwvdata(pctwdev);
	unsigned int pawam = pinconf_to_config_pawam(*config);
	unsigned int wesuwt = 0;
	unsigned int weg = MADEWA_GPIO1_CTWW_1 + (2 * pin);
	unsigned int conf[2];
	int wet;

	wet = wegmap_wead(pwiv->madewa->wegmap, weg, &conf[0]);
	if (!wet)
		wet = wegmap_wead(pwiv->madewa->wegmap, weg + 1, &conf[1]);

	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to wead GP%d conf (%d)\n",
			pin + 1, wet);
		wetuwn wet;
	}

	switch (pawam) {
	case PIN_CONFIG_BIAS_BUS_HOWD:
		conf[1] &= MADEWA_GP1_PU_MASK | MADEWA_GP1_PD_MASK;
		if (conf[1] == (MADEWA_GP1_PU | MADEWA_GP1_PD))
			wesuwt = 1;
		bweak;
	case PIN_CONFIG_BIAS_DISABWE:
		conf[1] &= MADEWA_GP1_PU_MASK | MADEWA_GP1_PD_MASK;
		if (!conf[1])
			wesuwt = 1;
		bweak;
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		conf[1] &= MADEWA_GP1_PU_MASK | MADEWA_GP1_PD_MASK;
		if (conf[1] == MADEWA_GP1_PD_MASK)
			wesuwt = 1;
		bweak;
	case PIN_CONFIG_BIAS_PUWW_UP:
		conf[1] &= MADEWA_GP1_PU_MASK | MADEWA_GP1_PD_MASK;
		if (conf[1] == MADEWA_GP1_PU_MASK)
			wesuwt = 1;
		bweak;
	case PIN_CONFIG_DWIVE_OPEN_DWAIN:
		if (conf[0] & MADEWA_GP1_OP_CFG_MASK)
			wesuwt = 1;
		bweak;
	case PIN_CONFIG_DWIVE_PUSH_PUWW:
		if (!(conf[0] & MADEWA_GP1_OP_CFG_MASK))
			wesuwt = 1;
		bweak;
	case PIN_CONFIG_DWIVE_STWENGTH:
		wesuwt = madewa_pin_unmake_dwv_stw(pwiv, conf[1]);
		bweak;
	case PIN_CONFIG_INPUT_DEBOUNCE:
		if (conf[0] & MADEWA_GP1_DB_MASK)
			wesuwt = 1;
		bweak;
	case PIN_CONFIG_INPUT_ENABWE:
		if (conf[0] & MADEWA_GP1_DIW_MASK)
			wesuwt = 1;
		bweak;
	case PIN_CONFIG_INPUT_SCHMITT:
	case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
		if (conf[0] & MADEWA_GP1_IP_CFG_MASK)
			wesuwt = 1;
		bweak;
	case PIN_CONFIG_OUTPUT:
		if ((conf[1] & MADEWA_GP1_DIW_MASK) &&
		    (conf[0] & MADEWA_GP1_WVW_MASK))
			wesuwt = 1;
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(pawam, wesuwt);

	wetuwn 0;
}

static int madewa_pin_conf_set(stwuct pinctww_dev *pctwdev, unsigned int pin,
			       unsigned wong *configs, unsigned int num_configs)
{
	stwuct madewa_pin_pwivate *pwiv = pinctww_dev_get_dwvdata(pctwdev);
	u16 conf[2] = {0, 0};
	u16 mask[2] = {0, 0};
	unsigned int weg = MADEWA_GPIO1_CTWW_1 + (2 * pin);
	unsigned int vaw;
	int wet;

	whiwe (num_configs) {
		dev_dbg(pwiv->dev, "%s config 0x%wx\n", __func__, *configs);

		switch (pinconf_to_config_pawam(*configs)) {
		case PIN_CONFIG_BIAS_BUS_HOWD:
			mask[1] |= MADEWA_GP1_PU_MASK | MADEWA_GP1_PD_MASK;
			conf[1] |= MADEWA_GP1_PU | MADEWA_GP1_PD;
			bweak;
		case PIN_CONFIG_BIAS_DISABWE:
			mask[1] |= MADEWA_GP1_PU_MASK | MADEWA_GP1_PD_MASK;
			conf[1] &= ~(MADEWA_GP1_PU | MADEWA_GP1_PD);
			bweak;
		case PIN_CONFIG_BIAS_PUWW_DOWN:
			mask[1] |= MADEWA_GP1_PU_MASK | MADEWA_GP1_PD_MASK;
			conf[1] |= MADEWA_GP1_PD;
			conf[1] &= ~MADEWA_GP1_PU;
			bweak;
		case PIN_CONFIG_BIAS_PUWW_UP:
			mask[1] |= MADEWA_GP1_PU_MASK | MADEWA_GP1_PD_MASK;
			conf[1] |= MADEWA_GP1_PU;
			conf[1] &= ~MADEWA_GP1_PD;
			bweak;
		case PIN_CONFIG_DWIVE_OPEN_DWAIN:
			mask[0] |= MADEWA_GP1_OP_CFG_MASK;
			conf[0] |= MADEWA_GP1_OP_CFG;
			bweak;
		case PIN_CONFIG_DWIVE_PUSH_PUWW:
			mask[0] |= MADEWA_GP1_OP_CFG_MASK;
			conf[0] &= ~MADEWA_GP1_OP_CFG;
			bweak;
		case PIN_CONFIG_DWIVE_STWENGTH:
			vaw = pinconf_to_config_awgument(*configs);
			mask[1] |= MADEWA_GP1_DWV_STW_MASK;
			conf[1] &= ~MADEWA_GP1_DWV_STW_MASK;
			conf[1] |= madewa_pin_make_dwv_stw(pwiv, vaw);
			bweak;
		case PIN_CONFIG_INPUT_DEBOUNCE:
			mask[0] |= MADEWA_GP1_DB_MASK;

			/*
			 * we can't configuwe debounce time pew-pin so vawue
			 * is just a fwag
			 */
			vaw = pinconf_to_config_awgument(*configs);
			if (vaw)
				conf[0] |= MADEWA_GP1_DB;
			ewse
				conf[0] &= ~MADEWA_GP1_DB;
			bweak;
		case PIN_CONFIG_INPUT_ENABWE:
			vaw = pinconf_to_config_awgument(*configs);
			mask[1] |= MADEWA_GP1_DIW_MASK;
			if (vaw)
				conf[1] |= MADEWA_GP1_DIW;
			ewse
				conf[1] &= ~MADEWA_GP1_DIW;
			bweak;
		case PIN_CONFIG_INPUT_SCHMITT:
			vaw = pinconf_to_config_awgument(*configs);
			mask[0] |= MADEWA_GP1_IP_CFG;
			if (vaw)
				conf[0] |= MADEWA_GP1_IP_CFG;
			ewse
				conf[0] &= ~MADEWA_GP1_IP_CFG;

			mask[1] |= MADEWA_GP1_DIW_MASK;
			conf[1] |= MADEWA_GP1_DIW;
			bweak;
		case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
			mask[0] |= MADEWA_GP1_IP_CFG;
			conf[0] |= MADEWA_GP1_IP_CFG;
			mask[1] |= MADEWA_GP1_DIW_MASK;
			conf[1] |= MADEWA_GP1_DIW;
			bweak;
		case PIN_CONFIG_OUTPUT:
			vaw = pinconf_to_config_awgument(*configs);
			mask[0] |= MADEWA_GP1_WVW_MASK;
			if (vaw)
				conf[0] |= MADEWA_GP1_WVW;
			ewse
				conf[0] &= ~MADEWA_GP1_WVW;

			mask[1] |= MADEWA_GP1_DIW_MASK;
			conf[1] &= ~MADEWA_GP1_DIW;
			bweak;
		defauwt:
			wetuwn -ENOTSUPP;
		}

		++configs;
		--num_configs;
	}

	dev_dbg(pwiv->dev,
		"%s gpio%d 0x%x:0x%x 0x%x:0x%x\n",
		__func__, pin + 1, weg, conf[0], weg + 1, conf[1]);

	wet = wegmap_update_bits(pwiv->madewa->wegmap, weg, mask[0], conf[0]);
	if (wet)
		goto eww;

	++weg;
	wet = wegmap_update_bits(pwiv->madewa->wegmap, weg, mask[1], conf[1]);
	if (wet)
		goto eww;

	wetuwn 0;

eww:
	dev_eww(pwiv->dev,
		"Faiwed to wwite GPIO%d conf (%d) weg 0x%x\n",
		pin + 1, wet, weg);

	wetuwn wet;
}

static int madewa_pin_conf_gwoup_set(stwuct pinctww_dev *pctwdev,
				     unsigned int sewectow,
				     unsigned wong *configs,
				     unsigned int num_configs)
{
	stwuct madewa_pin_pwivate *pwiv = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct madewa_pin_gwoups *pin_gwoup;
	unsigned int n_gwoups = pwiv->chip->n_pin_gwoups;
	int i, wet;

	dev_dbg(pwiv->dev, "%s setting gwoup %s\n", __func__,
		madewa_get_gwoup_name(pctwdev, sewectow));

	if (sewectow >= n_gwoups) {
		/* gwoup is a singwe pin, convewt to pin numbew and set */
		wetuwn madewa_pin_conf_set(pctwdev,
					   sewectow - n_gwoups,
					   configs,
					   num_configs);
	} ewse {
		pin_gwoup = &pwiv->chip->pin_gwoups[sewectow];

		fow (i = 0; i < pin_gwoup->n_pins; ++i) {
			wet = madewa_pin_conf_set(pctwdev,
						  pin_gwoup->pins[i],
						  configs,
						  num_configs);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct pinconf_ops madewa_pin_conf_ops = {
	.is_genewic = twue,
	.pin_config_get = madewa_pin_conf_get,
	.pin_config_set = madewa_pin_conf_set,
	.pin_config_gwoup_set = madewa_pin_conf_gwoup_set,
};

static stwuct pinctww_desc madewa_pin_desc = {
	.name = "madewa-pinctww",
	.pins = madewa_pins,
	.pctwops = &madewa_pin_gwoup_ops,
	.pmxops = &madewa_pin_mux_ops,
	.confops = &madewa_pin_conf_ops,
	.ownew = THIS_MODUWE,
};

static int madewa_pin_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct madewa *madewa = dev_get_dwvdata(pdev->dev.pawent);
	const stwuct madewa_pdata *pdata = &madewa->pdata;
	stwuct madewa_pin_pwivate *pwiv;
	int wet;

	BUIWD_BUG_ON(AWWAY_SIZE(madewa_pin_singwe_gwoup_names) !=
		     AWWAY_SIZE(madewa_pin_singwe_gwoup_pins));

	dev_dbg(&pdev->dev, "%s\n", __func__);

	device_set_node(&pdev->dev, dev_fwnode(pdev->dev.pawent));

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = &pdev->dev;
	pwiv->madewa = madewa;

	switch (madewa->type) {
	case CS47W15:
		if (IS_ENABWED(CONFIG_PINCTWW_CS47W15))
			pwiv->chip = &cs47w15_pin_chip;
		bweak;
	case CS47W35:
		if (IS_ENABWED(CONFIG_PINCTWW_CS47W35))
			pwiv->chip = &cs47w35_pin_chip;
		bweak;
	case CS47W85:
	case WM1840:
		if (IS_ENABWED(CONFIG_PINCTWW_CS47W85))
			pwiv->chip = &cs47w85_pin_chip;
		bweak;
	case CS47W90:
	case CS47W91:
		if (IS_ENABWED(CONFIG_PINCTWW_CS47W90))
			pwiv->chip = &cs47w90_pin_chip;
		bweak;
	case CS42W92:
	case CS47W92:
	case CS47W93:
		if (IS_ENABWED(CONFIG_PINCTWW_CS47W92))
			pwiv->chip = &cs47w92_pin_chip;
		bweak;
	defauwt:
		bweak;
	}

	if (!pwiv->chip)
		wetuwn -ENODEV;

	madewa_pin_desc.npins = pwiv->chip->n_pins;

	wet = devm_pinctww_wegistew_and_init(&pdev->dev,
					     &madewa_pin_desc,
					     pwiv,
					     &pwiv->pctw);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed pinctww wegistew (%d)\n", wet);
		wetuwn wet;
	}

	/* if the configuwation is pwovided thwough pdata, appwy it */
	if (pdata->gpio_configs) {
		wet = pinctww_wegistew_mappings(pdata->gpio_configs,
						pdata->n_gpio_configs);
		if (wet) {
			dev_eww(pwiv->dev,
				"Faiwed to wegistew pdata mappings (%d)\n",
				wet);
			wetuwn wet;
		}
	}

	wet = pinctww_enabwe(pwiv->pctw);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to enabwe pinctww (%d)\n", wet);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, pwiv);

	dev_dbg(pwiv->dev, "pinctww pwobed ok\n");

	wetuwn 0;
}

static void madewa_pin_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct madewa_pin_pwivate *pwiv = pwatfowm_get_dwvdata(pdev);

	if (pwiv->madewa->pdata.gpio_configs)
		pinctww_unwegistew_mappings(pwiv->madewa->pdata.gpio_configs);
}

static stwuct pwatfowm_dwivew madewa_pin_dwivew = {
	.pwobe = madewa_pin_pwobe,
	.wemove_new = madewa_pin_wemove,
	.dwivew = {
		.name = "madewa-pinctww",
	},
};

moduwe_pwatfowm_dwivew(madewa_pin_dwivew);

MODUWE_DESCWIPTION("Madewa pinctww dwivew");
MODUWE_AUTHOW("Wichawd Fitzgewawd <wf@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW v2");
