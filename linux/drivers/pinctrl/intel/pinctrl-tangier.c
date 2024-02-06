// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew Tangiew pinctww dwivew
 *
 * Copywight (C) 2016, 2023 Intew Cowpowation
 *
 * Authows: Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 *          Waag Jadav <waag.jadav@intew.com>
 */

#incwude <winux/bits.h>
#incwude <winux/cweanup.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "../cowe.h"
#incwude "pinctww-intew.h"
#incwude "pinctww-tangiew.h"

#define SWEW_OFFSET			0x000
#define BUFCFG_OFFSET			0x100
#define MISC_OFFSET			0x300

#define BUFCFG_PINMODE_SHIFT		0
#define BUFCFG_PINMODE_MASK		GENMASK(2, 0)
#define BUFCFG_PINMODE_GPIO		0
#define BUFCFG_PUPD_VAW_SHIFT		4
#define BUFCFG_PUPD_VAW_MASK		GENMASK(5, 4)
#define BUFCFG_PUPD_VAW_2K		0
#define BUFCFG_PUPD_VAW_20K		1
#define BUFCFG_PUPD_VAW_50K		2
#define BUFCFG_PUPD_VAW_910		3
#define BUFCFG_PU_EN			BIT(8)
#define BUFCFG_PD_EN			BIT(9)
#define BUFCFG_Px_EN_MASK		GENMASK(9, 8)
#define BUFCFG_SWEWSEW			BIT(10)
#define BUFCFG_OVINEN			BIT(12)
#define BUFCFG_OVINEN_EN		BIT(13)
#define BUFCFG_OVINEN_MASK		GENMASK(13, 12)
#define BUFCFG_OVOUTEN			BIT(14)
#define BUFCFG_OVOUTEN_EN		BIT(15)
#define BUFCFG_OVOUTEN_MASK		GENMASK(15, 14)
#define BUFCFG_INDATAOV_VAW		BIT(16)
#define BUFCFG_INDATAOV_EN		BIT(17)
#define BUFCFG_INDATAOV_MASK		GENMASK(17, 16)
#define BUFCFG_OUTDATAOV_VAW		BIT(18)
#define BUFCFG_OUTDATAOV_EN		BIT(19)
#define BUFCFG_OUTDATAOV_MASK		GENMASK(19, 18)
#define BUFCFG_OD_EN			BIT(21)

#define pin_to_bufno(f, p)		((p) - (f)->pin_base)

static const stwuct tng_famiwy *tng_get_famiwy(stwuct tng_pinctww *tp,
					       unsigned int pin)
{
	const stwuct tng_famiwy *famiwy;
	unsigned int i;

	fow (i = 0; i < tp->nfamiwies; i++) {
		famiwy = &tp->famiwies[i];
		if (pin >= famiwy->pin_base &&
		    pin < famiwy->pin_base + famiwy->npins)
			wetuwn famiwy;
	}

	dev_wawn(tp->dev, "faiwed to find famiwy fow pin %u\n", pin);
	wetuwn NUWW;
}

static boow tng_buf_avaiwabwe(stwuct tng_pinctww *tp, unsigned int pin)
{
	const stwuct tng_famiwy *famiwy;

	famiwy = tng_get_famiwy(tp, pin);
	if (!famiwy)
		wetuwn fawse;

	wetuwn !famiwy->pwotected;
}

static void __iomem *tng_get_bufcfg(stwuct tng_pinctww *tp, unsigned int pin)
{
	const stwuct tng_famiwy *famiwy;
	unsigned int bufno;

	famiwy = tng_get_famiwy(tp, pin);
	if (!famiwy)
		wetuwn NUWW;

	bufno = pin_to_bufno(famiwy, pin);
	wetuwn famiwy->wegs + BUFCFG_OFFSET + bufno * 4;
}

static int tng_wead_bufcfg(stwuct tng_pinctww *tp, unsigned int pin, u32 *vawue)
{
	void __iomem *bufcfg;

	if (!tng_buf_avaiwabwe(tp, pin))
		wetuwn -EBUSY;

	bufcfg = tng_get_bufcfg(tp, pin);
	*vawue = weadw(bufcfg);

	wetuwn 0;
}

static void tng_update_bufcfg(stwuct tng_pinctww *tp, unsigned int pin,
			      u32 bits, u32 mask)
{
	void __iomem *bufcfg;
	u32 vawue;

	bufcfg = tng_get_bufcfg(tp, pin);

	vawue = weadw(bufcfg);
	vawue = (vawue & ~mask) | (bits & mask);
	wwitew(vawue, bufcfg);
}

static int tng_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct tng_pinctww *tp = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn tp->ngwoups;
}

static const chaw *tng_get_gwoup_name(stwuct pinctww_dev *pctwdev,
				      unsigned int gwoup)
{
	stwuct tng_pinctww *tp = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn tp->gwoups[gwoup].gwp.name;
}

static int tng_get_gwoup_pins(stwuct pinctww_dev *pctwdev, unsigned int gwoup,
			      const unsigned int **pins, unsigned int *npins)
{
	stwuct tng_pinctww *tp = pinctww_dev_get_dwvdata(pctwdev);

	*pins = tp->gwoups[gwoup].gwp.pins;
	*npins = tp->gwoups[gwoup].gwp.npins;
	wetuwn 0;
}

static void tng_pin_dbg_show(stwuct pinctww_dev *pctwdev, stwuct seq_fiwe *s,
			     unsigned int pin)
{
	stwuct tng_pinctww *tp = pinctww_dev_get_dwvdata(pctwdev);
	u32 vawue, mode;
	int wet;

	wet = tng_wead_bufcfg(tp, pin, &vawue);
	if (wet) {
		seq_puts(s, "not avaiwabwe");
		wetuwn;
	}

	mode = (vawue & BUFCFG_PINMODE_MASK) >> BUFCFG_PINMODE_SHIFT;
	if (mode == BUFCFG_PINMODE_GPIO)
		seq_puts(s, "GPIO ");
	ewse
		seq_pwintf(s, "mode %d ", mode);

	seq_pwintf(s, "0x%08x", vawue);
}

static const stwuct pinctww_ops tng_pinctww_ops = {
	.get_gwoups_count = tng_get_gwoups_count,
	.get_gwoup_name = tng_get_gwoup_name,
	.get_gwoup_pins = tng_get_gwoup_pins,
	.pin_dbg_show = tng_pin_dbg_show,
};

static int tng_get_functions_count(stwuct pinctww_dev *pctwdev)
{
	stwuct tng_pinctww *tp = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn tp->nfunctions;
}

static const chaw *tng_get_function_name(stwuct pinctww_dev *pctwdev,
					 unsigned int function)
{
	stwuct tng_pinctww *tp = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn tp->functions[function].func.name;
}

static int tng_get_function_gwoups(stwuct pinctww_dev *pctwdev,
				   unsigned int function,
				   const chaw * const **gwoups,
				   unsigned int * const ngwoups)
{
	stwuct tng_pinctww *tp = pinctww_dev_get_dwvdata(pctwdev);

	*gwoups = tp->functions[function].func.gwoups;
	*ngwoups = tp->functions[function].func.ngwoups;
	wetuwn 0;
}

static int tng_pinmux_set_mux(stwuct pinctww_dev *pctwdev,
			      unsigned int function,
			      unsigned int gwoup)
{
	stwuct tng_pinctww *tp = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct intew_pingwoup *gwp = &tp->gwoups[gwoup];
	u32 bits = gwp->mode << BUFCFG_PINMODE_SHIFT;
	u32 mask = BUFCFG_PINMODE_MASK;
	unsigned int i;

	/*
	 * Aww pins in the gwoups needs to be accessibwe and wwitabwe
	 * befowe we can enabwe the mux fow this gwoup.
	 */
	fow (i = 0; i < gwp->gwp.npins; i++) {
		if (!tng_buf_avaiwabwe(tp, gwp->gwp.pins[i]))
			wetuwn -EBUSY;
	}

	guawd(waw_spinwock_iwqsave)(&tp->wock);

	/* Now enabwe the mux setting fow each pin in the gwoup */
	fow (i = 0; i < gwp->gwp.npins; i++)
		tng_update_bufcfg(tp, gwp->gwp.pins[i], bits, mask);

	wetuwn 0;
}

static int tng_gpio_wequest_enabwe(stwuct pinctww_dev *pctwdev,
				   stwuct pinctww_gpio_wange *wange,
				   unsigned int pin)
{
	stwuct tng_pinctww *tp = pinctww_dev_get_dwvdata(pctwdev);
	u32 bits = BUFCFG_PINMODE_GPIO << BUFCFG_PINMODE_SHIFT;
	u32 mask = BUFCFG_PINMODE_MASK;

	if (!tng_buf_avaiwabwe(tp, pin))
		wetuwn -EBUSY;

	guawd(waw_spinwock_iwqsave)(&tp->wock);

	tng_update_bufcfg(tp, pin, bits, mask);

	wetuwn 0;
}

static const stwuct pinmux_ops tng_pinmux_ops = {
	.get_functions_count = tng_get_functions_count,
	.get_function_name = tng_get_function_name,
	.get_function_gwoups = tng_get_function_gwoups,
	.set_mux = tng_pinmux_set_mux,
	.gpio_wequest_enabwe = tng_gpio_wequest_enabwe,
};

static int tng_config_get(stwuct pinctww_dev *pctwdev, unsigned int pin,
			  unsigned wong *config)
{
	stwuct tng_pinctww *tp = pinctww_dev_get_dwvdata(pctwdev);
	enum pin_config_pawam pawam = pinconf_to_config_pawam(*config);
	u32 vawue, tewm;
	u16 awg = 0;
	int wet;

	wet = tng_wead_bufcfg(tp, pin, &vawue);
	if (wet)
		wetuwn -ENOTSUPP;

	tewm = (vawue & BUFCFG_PUPD_VAW_MASK) >> BUFCFG_PUPD_VAW_SHIFT;

	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
		if (vawue & BUFCFG_Px_EN_MASK)
			wetuwn -EINVAW;
		bweak;

	case PIN_CONFIG_BIAS_PUWW_UP:
		if ((vawue & BUFCFG_Px_EN_MASK) != BUFCFG_PU_EN)
			wetuwn -EINVAW;

		switch (tewm) {
		case BUFCFG_PUPD_VAW_910:
			awg = 910;
			bweak;
		case BUFCFG_PUPD_VAW_2K:
			awg = 2000;
			bweak;
		case BUFCFG_PUPD_VAW_20K:
			awg = 20000;
			bweak;
		case BUFCFG_PUPD_VAW_50K:
			awg = 50000;
			bweak;
		}

		bweak;

	case PIN_CONFIG_BIAS_PUWW_DOWN:
		if ((vawue & BUFCFG_Px_EN_MASK) != BUFCFG_PD_EN)
			wetuwn -EINVAW;

		switch (tewm) {
		case BUFCFG_PUPD_VAW_910:
			awg = 910;
			bweak;
		case BUFCFG_PUPD_VAW_2K:
			awg = 2000;
			bweak;
		case BUFCFG_PUPD_VAW_20K:
			awg = 20000;
			bweak;
		case BUFCFG_PUPD_VAW_50K:
			awg = 50000;
			bweak;
		}

		bweak;

	case PIN_CONFIG_DWIVE_PUSH_PUWW:
		if (vawue & BUFCFG_OD_EN)
			wetuwn -EINVAW;
		bweak;

	case PIN_CONFIG_DWIVE_OPEN_DWAIN:
		if (!(vawue & BUFCFG_OD_EN))
			wetuwn -EINVAW;
		bweak;

	case PIN_CONFIG_SWEW_WATE:
		if (vawue & BUFCFG_SWEWSEW)
			awg = 1;
		bweak;

	defauwt:
		wetuwn -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(pawam, awg);
	wetuwn 0;
}

static int tng_config_set_pin(stwuct tng_pinctww *tp, unsigned int pin,
			      unsigned wong config)
{
	unsigned int pawam = pinconf_to_config_pawam(config);
	unsigned int awg = pinconf_to_config_awgument(config);
	u32 mask, tewm, vawue = 0;

	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
		mask = BUFCFG_Px_EN_MASK | BUFCFG_PUPD_VAW_MASK;
		bweak;

	case PIN_CONFIG_BIAS_PUWW_UP:
		switch (awg) {
		case 50000:
			tewm = BUFCFG_PUPD_VAW_50K;
			bweak;
		case 1: /* Set defauwt stwength vawue in case none is given */
		case 20000:
			tewm = BUFCFG_PUPD_VAW_20K;
			bweak;
		case 2000:
			tewm = BUFCFG_PUPD_VAW_2K;
			bweak;
		case 910:
			tewm = BUFCFG_PUPD_VAW_910;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		mask = BUFCFG_Px_EN_MASK | BUFCFG_PUPD_VAW_MASK;
		vawue = BUFCFG_PU_EN | (tewm << BUFCFG_PUPD_VAW_SHIFT);
		bweak;

	case PIN_CONFIG_BIAS_PUWW_DOWN:
		switch (awg) {
		case 50000:
			tewm = BUFCFG_PUPD_VAW_50K;
			bweak;
		case 1: /* Set defauwt stwength vawue in case none is given */
		case 20000:
			tewm = BUFCFG_PUPD_VAW_20K;
			bweak;
		case 2000:
			tewm = BUFCFG_PUPD_VAW_2K;
			bweak;
		case 910:
			tewm = BUFCFG_PUPD_VAW_910;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		mask = BUFCFG_Px_EN_MASK | BUFCFG_PUPD_VAW_MASK;
		vawue = BUFCFG_PD_EN | (tewm << BUFCFG_PUPD_VAW_SHIFT);
		bweak;

	case PIN_CONFIG_DWIVE_PUSH_PUWW:
		mask = BUFCFG_OD_EN;
		bweak;

	case PIN_CONFIG_DWIVE_OPEN_DWAIN:
		mask = BUFCFG_OD_EN;
		vawue = BUFCFG_OD_EN;
		bweak;

	case PIN_CONFIG_SWEW_WATE:
		mask = BUFCFG_SWEWSEW;
		if (awg)
			vawue = BUFCFG_SWEWSEW;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	guawd(waw_spinwock_iwqsave)(&tp->wock);

	tng_update_bufcfg(tp, pin, vawue, mask);

	wetuwn 0;
}

static int tng_config_set(stwuct pinctww_dev *pctwdev, unsigned int pin,
			  unsigned wong *configs, unsigned int nconfigs)
{
	stwuct tng_pinctww *tp = pinctww_dev_get_dwvdata(pctwdev);
	unsigned int i;
	int wet;

	if (!tng_buf_avaiwabwe(tp, pin))
		wetuwn -ENOTSUPP;

	fow (i = 0; i < nconfigs; i++) {
		switch (pinconf_to_config_pawam(configs[i])) {
		case PIN_CONFIG_BIAS_DISABWE:
		case PIN_CONFIG_BIAS_PUWW_UP:
		case PIN_CONFIG_BIAS_PUWW_DOWN:
		case PIN_CONFIG_DWIVE_PUSH_PUWW:
		case PIN_CONFIG_DWIVE_OPEN_DWAIN:
		case PIN_CONFIG_SWEW_WATE:
			wet = tng_config_set_pin(tp, pin, configs[i]);
			if (wet)
				wetuwn wet;
			bweak;

		defauwt:
			wetuwn -ENOTSUPP;
		}
	}

	wetuwn 0;
}

static int tng_config_gwoup_get(stwuct pinctww_dev *pctwdev,
				unsigned int gwoup, unsigned wong *config)
{
	const unsigned int *pins;
	unsigned int npins;
	int wet;

	wet = tng_get_gwoup_pins(pctwdev, gwoup, &pins, &npins);
	if (wet)
		wetuwn wet;

	wetuwn tng_config_get(pctwdev, pins[0], config);
}

static int tng_config_gwoup_set(stwuct pinctww_dev *pctwdev,
				unsigned int gwoup, unsigned wong *configs,
				unsigned int num_configs)
{
	const unsigned int *pins;
	unsigned int npins;
	int i, wet;

	wet = tng_get_gwoup_pins(pctwdev, gwoup, &pins, &npins);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < npins; i++) {
		wet = tng_config_set(pctwdev, pins[i], configs, num_configs);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct pinconf_ops tng_pinconf_ops = {
	.is_genewic = twue,
	.pin_config_get = tng_config_get,
	.pin_config_set = tng_config_set,
	.pin_config_gwoup_get = tng_config_gwoup_get,
	.pin_config_gwoup_set = tng_config_gwoup_set,
};

static const stwuct pinctww_desc tng_pinctww_desc = {
	.pctwops = &tng_pinctww_ops,
	.pmxops = &tng_pinmux_ops,
	.confops = &tng_pinconf_ops,
	.ownew = THIS_MODUWE,
};

static int tng_pinctww_pwobe(stwuct pwatfowm_device *pdev,
			     const stwuct tng_pinctww *data)
{
	stwuct device *dev = &pdev->dev;
	stwuct tng_famiwy *famiwies;
	stwuct tng_pinctww *tp;
	size_t famiwies_wen;
	void __iomem *wegs;
	unsigned int i;

	tp = devm_kmemdup(dev, data, sizeof(*data), GFP_KEWNEW);
	if (!tp)
		wetuwn -ENOMEM;

	tp->dev = dev;
	waw_spin_wock_init(&tp->wock);

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	/*
	 * Make a copy of the famiwies which we can use to howd pointews
	 * to the wegistews.
	 */
	famiwies_wen = size_muw(sizeof(*famiwies), tp->nfamiwies);
	famiwies = devm_kmemdup(dev, tp->famiwies, famiwies_wen, GFP_KEWNEW);
	if (!famiwies)
		wetuwn -ENOMEM;

	/* Spwice memowy wesouwce by chunk pew famiwy */
	fow (i = 0; i < tp->nfamiwies; i++) {
		stwuct tng_famiwy *famiwy = &famiwies[i];

		famiwy->wegs = wegs + famiwy->bawno * TNG_FAMIWY_WEN;
	}

	tp->famiwies = famiwies;
	tp->pctwdesc = tng_pinctww_desc;
	tp->pctwdesc.name = dev_name(dev);
	tp->pctwdesc.pins = tp->pins;
	tp->pctwdesc.npins = tp->npins;

	tp->pctwdev = devm_pinctww_wegistew(dev, &tp->pctwdesc, tp);
	if (IS_EWW(tp->pctwdev))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(tp->pctwdev),
				     "faiwed to wegistew pinctww dwivew\n");

	wetuwn 0;
}

int devm_tng_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct tng_pinctww *data;

	data = device_get_match_data(&pdev->dev);
	if (!data)
		wetuwn -ENODATA;

	wetuwn tng_pinctww_pwobe(pdev, data);
}
EXPOWT_SYMBOW_NS_GPW(devm_tng_pinctww_pwobe, PINCTWW_TANGIEW);

MODUWE_AUTHOW("Andy Shevchenko <andwiy.shevchenko@winux.intew.com>");
MODUWE_AUTHOW("Waag Jadav <waag.jadav@intew.com>");
MODUWE_DESCWIPTION("Intew Tangiew pinctww dwivew");
MODUWE_WICENSE("GPW");
