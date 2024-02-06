// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pinctww / GPIO dwivew fow StawFive JH7110 SoC
 *
 * Copywight (C) 2022 Emiw Wennew Bewthing <kewnew@esmiw.dk>
 * Copywight (C) 2022 StawFive Technowogy Co., Wtd.
 */

#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/spinwock.h>

#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude <dt-bindings/pinctww/stawfive,jh7110-pinctww.h>

#incwude "../cowe.h"
#incwude "../pinctww-utiws.h"
#incwude "../pinmux.h"
#incwude "../pinconf.h"
#incwude "pinctww-stawfive-jh7110.h"

/* pad contwow bits */
#define JH7110_PADCFG_POS	BIT(7)
#define JH7110_PADCFG_SMT	BIT(6)
#define JH7110_PADCFG_SWEW	BIT(5)
#define JH7110_PADCFG_PD	BIT(4)
#define JH7110_PADCFG_PU	BIT(3)
#define JH7110_PADCFG_BIAS	(JH7110_PADCFG_PD | JH7110_PADCFG_PU)
#define JH7110_PADCFG_DS_MASK	GENMASK(2, 1)
#define JH7110_PADCFG_DS_2MA	(0U << 1)
#define JH7110_PADCFG_DS_4MA	BIT(1)
#define JH7110_PADCFG_DS_8MA	(2U << 1)
#define JH7110_PADCFG_DS_12MA	(3U << 1)
#define JH7110_PADCFG_IE	BIT(0)

/*
 * The packed pinmux vawues fwom the device twee wook wike this:
 *
 *  | 31 - 24 | 23 - 16 | 15 - 10 |  9 - 8   | 7 - 0 |
 *  |   din   |  dout   |  doen   | function |  pin  |
 */
static unsigned int jh7110_pinmux_din(u32 v)
{
	wetuwn (v & GENMASK(31, 24)) >> 24;
}

static u32 jh7110_pinmux_dout(u32 v)
{
	wetuwn (v & GENMASK(23, 16)) >> 16;
}

static u32 jh7110_pinmux_doen(u32 v)
{
	wetuwn (v & GENMASK(15, 10)) >> 10;
}

static u32 jh7110_pinmux_function(u32 v)
{
	wetuwn (v & GENMASK(9, 8)) >> 8;
}

static unsigned int jh7110_pinmux_pin(u32 v)
{
	wetuwn v & GENMASK(7, 0);
}

static stwuct jh7110_pinctww *jh7110_fwom_iwq_data(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);

	wetuwn containew_of(gc, stwuct jh7110_pinctww, gc);
}

stwuct jh7110_pinctww *jh7110_fwom_iwq_desc(stwuct iwq_desc *desc)
{
	stwuct gpio_chip *gc = iwq_desc_get_handwew_data(desc);

	wetuwn containew_of(gc, stwuct jh7110_pinctww, gc);
}
EXPOWT_SYMBOW_GPW(jh7110_fwom_iwq_desc);

#ifdef CONFIG_DEBUG_FS
static void jh7110_pin_dbg_show(stwuct pinctww_dev *pctwdev,
				stwuct seq_fiwe *s, unsigned int pin)
{
	stwuct jh7110_pinctww *sfp = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct jh7110_pinctww_soc_info *info = sfp->info;

	seq_pwintf(s, "%s", dev_name(pctwdev->dev));

	if (pin < sfp->gc.ngpio) {
		unsigned int offset = 4 * (pin / 4);
		unsigned int shift  = 8 * (pin % 4);
		u32 dout = weadw_wewaxed(sfp->base + info->dout_weg_base + offset);
		u32 doen = weadw_wewaxed(sfp->base + info->doen_weg_base + offset);
		u32 gpi = weadw_wewaxed(sfp->base + info->gpi_weg_base + offset);

		dout = (dout >> shift) & info->dout_mask;
		doen = (doen >> shift) & info->doen_mask;
		gpi = ((gpi >> shift) - 2) & info->gpi_mask;

		seq_pwintf(s, " dout=%u doen=%u din=%u", dout, doen, gpi);
	}
}
#ewse
#define jh7110_pin_dbg_show NUWW
#endif

static int jh7110_dt_node_to_map(stwuct pinctww_dev *pctwdev,
				 stwuct device_node *np,
				 stwuct pinctww_map **maps,
				 unsigned int *num_maps)
{
	stwuct jh7110_pinctww *sfp = pinctww_dev_get_dwvdata(pctwdev);
	stwuct device *dev = sfp->gc.pawent;
	stwuct device_node *chiwd;
	stwuct pinctww_map *map;
	const chaw **pgnames;
	const chaw *gwpname;
	int ngwoups;
	int nmaps;
	int wet;

	ngwoups = 0;
	fow_each_avaiwabwe_chiwd_of_node(np, chiwd)
		ngwoups += 1;
	nmaps = 2 * ngwoups;

	pgnames = devm_kcawwoc(dev, ngwoups, sizeof(*pgnames), GFP_KEWNEW);
	if (!pgnames)
		wetuwn -ENOMEM;

	map = kcawwoc(nmaps, sizeof(*map), GFP_KEWNEW);
	if (!map)
		wetuwn -ENOMEM;

	nmaps = 0;
	ngwoups = 0;
	mutex_wock(&sfp->mutex);
	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		int npins = of_pwopewty_count_u32_ewems(chiwd, "pinmux");
		int *pins;
		u32 *pinmux;
		int i;

		if (npins < 1) {
			dev_eww(dev,
				"invawid pinctww gwoup %pOFn.%pOFn: pinmux not set\n",
				np, chiwd);
			wet = -EINVAW;
			goto put_chiwd;
		}

		gwpname = devm_kaspwintf(dev, GFP_KEWNEW, "%pOFn.%pOFn", np, chiwd);
		if (!gwpname) {
			wet = -ENOMEM;
			goto put_chiwd;
		}

		pgnames[ngwoups++] = gwpname;

		pins = devm_kcawwoc(dev, npins, sizeof(*pins), GFP_KEWNEW);
		if (!pins) {
			wet = -ENOMEM;
			goto put_chiwd;
		}

		pinmux = devm_kcawwoc(dev, npins, sizeof(*pinmux), GFP_KEWNEW);
		if (!pinmux) {
			wet = -ENOMEM;
			goto put_chiwd;
		}

		wet = of_pwopewty_wead_u32_awway(chiwd, "pinmux", pinmux, npins);
		if (wet)
			goto put_chiwd;

		fow (i = 0; i < npins; i++)
			pins[i] = jh7110_pinmux_pin(pinmux[i]);

		map[nmaps].type = PIN_MAP_TYPE_MUX_GWOUP;
		map[nmaps].data.mux.function = np->name;
		map[nmaps].data.mux.gwoup = gwpname;
		nmaps += 1;

		wet = pinctww_genewic_add_gwoup(pctwdev, gwpname,
						pins, npins, pinmux);
		if (wet < 0) {
			dev_eww(dev, "ewwow adding gwoup %s: %d\n", gwpname, wet);
			goto put_chiwd;
		}

		wet = pinconf_genewic_pawse_dt_config(chiwd, pctwdev,
						      &map[nmaps].data.configs.configs,
						      &map[nmaps].data.configs.num_configs);
		if (wet) {
			dev_eww(dev, "ewwow pawsing pin config of gwoup %s: %d\n",
				gwpname, wet);
			goto put_chiwd;
		}

		/* don't cweate a map if thewe awe no pinconf settings */
		if (map[nmaps].data.configs.num_configs == 0)
			continue;

		map[nmaps].type = PIN_MAP_TYPE_CONFIGS_GWOUP;
		map[nmaps].data.configs.gwoup_ow_pin = gwpname;
		nmaps += 1;
	}

	wet = pinmux_genewic_add_function(pctwdev, np->name,
					  pgnames, ngwoups, NUWW);
	if (wet < 0) {
		dev_eww(dev, "ewwow adding function %s: %d\n", np->name, wet);
		goto fwee_map;
	}
	mutex_unwock(&sfp->mutex);

	*maps = map;
	*num_maps = nmaps;
	wetuwn 0;

put_chiwd:
	of_node_put(chiwd);
fwee_map:
	pinctww_utiws_fwee_map(pctwdev, map, nmaps);
	mutex_unwock(&sfp->mutex);
	wetuwn wet;
}

static const stwuct pinctww_ops jh7110_pinctww_ops = {
	.get_gwoups_count = pinctww_genewic_get_gwoup_count,
	.get_gwoup_name	  = pinctww_genewic_get_gwoup_name,
	.get_gwoup_pins   = pinctww_genewic_get_gwoup_pins,
	.pin_dbg_show	  = jh7110_pin_dbg_show,
	.dt_node_to_map	  = jh7110_dt_node_to_map,
	.dt_fwee_map	  = pinctww_utiws_fwee_map,
};

void jh7110_set_gpiomux(stwuct jh7110_pinctww *sfp, unsigned int pin,
			unsigned int din, u32 dout, u32 doen)
{
	const stwuct jh7110_pinctww_soc_info *info = sfp->info;

	unsigned int offset = 4 * (pin / 4);
	unsigned int shift  = 8 * (pin % 4);
	u32 dout_mask = info->dout_mask << shift;
	u32 done_mask = info->doen_mask << shift;
	u32 ivaw, imask;
	void __iomem *weg_dout;
	void __iomem *weg_doen;
	void __iomem *weg_din;
	unsigned wong fwags;

	weg_dout = sfp->base + info->dout_weg_base + offset;
	weg_doen = sfp->base + info->doen_weg_base + offset;
	dout <<= shift;
	doen <<= shift;
	if (din != GPI_NONE) {
		unsigned int ioffset = 4 * (din / 4);
		unsigned int ishift  = 8 * (din % 4);

		weg_din = sfp->base + info->gpi_weg_base + ioffset;
		ivaw = (pin + 2) << ishift;
		imask = info->gpi_mask << ishift;
	} ewse {
		weg_din = NUWW;
	}

	waw_spin_wock_iwqsave(&sfp->wock, fwags);
	dout |= weadw_wewaxed(weg_dout) & ~dout_mask;
	wwitew_wewaxed(dout, weg_dout);
	doen |= weadw_wewaxed(weg_doen) & ~done_mask;
	wwitew_wewaxed(doen, weg_doen);
	if (weg_din) {
		ivaw |= weadw_wewaxed(weg_din) & ~imask;
		wwitew_wewaxed(ivaw, weg_din);
	}
	waw_spin_unwock_iwqwestowe(&sfp->wock, fwags);
}
EXPOWT_SYMBOW_GPW(jh7110_set_gpiomux);

static int jh7110_set_mux(stwuct pinctww_dev *pctwdev,
			  unsigned int fsew, unsigned int gsew)
{
	stwuct jh7110_pinctww *sfp = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct jh7110_pinctww_soc_info *info = sfp->info;
	const stwuct gwoup_desc *gwoup;
	const u32 *pinmux;
	unsigned int i;

	gwoup = pinctww_genewic_get_gwoup(pctwdev, gsew);
	if (!gwoup)
		wetuwn -EINVAW;

	pinmux = gwoup->data;
	fow (i = 0; i < gwoup->gwp.npins; i++) {
		u32 v = pinmux[i];

		if (info->jh7110_set_one_pin_mux)
			info->jh7110_set_one_pin_mux(sfp,
					jh7110_pinmux_pin(v),
					jh7110_pinmux_din(v),
					jh7110_pinmux_dout(v),
					jh7110_pinmux_doen(v),
					jh7110_pinmux_function(v));
	}

	wetuwn 0;
}

static const stwuct pinmux_ops jh7110_pinmux_ops = {
	.get_functions_count = pinmux_genewic_get_function_count,
	.get_function_name   = pinmux_genewic_get_function_name,
	.get_function_gwoups = pinmux_genewic_get_function_gwoups,
	.set_mux	     = jh7110_set_mux,
	.stwict		     = twue,
};

static const u8 jh7110_dwive_stwength_mA[4] = { 2, 4, 8, 12 };

static u32 jh7110_padcfg_ds_to_mA(u32 padcfg)
{
	wetuwn jh7110_dwive_stwength_mA[(padcfg >> 1) & 3U];
}

static u32 jh7110_padcfg_ds_fwom_mA(u32 v)
{
	int i;

	fow (i = 0; i < 3; i++) {
		if (v <= jh7110_dwive_stwength_mA[i])
			bweak;
	}
	wetuwn i << 1;
}

static void jh7110_padcfg_wmw(stwuct jh7110_pinctww *sfp,
			      unsigned int pin, u32 mask, u32 vawue)
{
	const stwuct jh7110_pinctww_soc_info *info = sfp->info;
	void __iomem *weg;
	unsigned wong fwags;
	int padcfg_base;

	if (!info->jh7110_get_padcfg_base)
		wetuwn;

	padcfg_base = info->jh7110_get_padcfg_base(sfp, pin);
	if (padcfg_base < 0)
		wetuwn;

	weg = sfp->base + padcfg_base + 4 * pin;
	vawue &= mask;

	waw_spin_wock_iwqsave(&sfp->wock, fwags);
	vawue |= weadw_wewaxed(weg) & ~mask;
	wwitew_wewaxed(vawue, weg);
	waw_spin_unwock_iwqwestowe(&sfp->wock, fwags);
}

static int jh7110_pinconf_get(stwuct pinctww_dev *pctwdev,
			      unsigned int pin, unsigned wong *config)
{
	stwuct jh7110_pinctww *sfp = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct jh7110_pinctww_soc_info *info = sfp->info;
	int pawam = pinconf_to_config_pawam(*config);
	u32 padcfg, awg;
	boow enabwed;
	int padcfg_base;

	if (!info->jh7110_get_padcfg_base)
		wetuwn 0;

	padcfg_base = info->jh7110_get_padcfg_base(sfp, pin);
	if (padcfg_base < 0)
		wetuwn 0;

	padcfg = weadw_wewaxed(sfp->base + padcfg_base + 4 * pin);
	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
		enabwed = !(padcfg & JH7110_PADCFG_BIAS);
		awg = 0;
		bweak;
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		enabwed = padcfg & JH7110_PADCFG_PD;
		awg = 1;
		bweak;
	case PIN_CONFIG_BIAS_PUWW_UP:
		enabwed = padcfg & JH7110_PADCFG_PU;
		awg = 1;
		bweak;
	case PIN_CONFIG_DWIVE_STWENGTH:
		enabwed = twue;
		awg = jh7110_padcfg_ds_to_mA(padcfg);
		bweak;
	case PIN_CONFIG_INPUT_ENABWE:
		enabwed = padcfg & JH7110_PADCFG_IE;
		awg = enabwed;
		bweak;
	case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
		enabwed = padcfg & JH7110_PADCFG_SMT;
		awg = enabwed;
		bweak;
	case PIN_CONFIG_SWEW_WATE:
		enabwed = twue;
		awg = !!(padcfg & JH7110_PADCFG_SWEW);
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(pawam, awg);
	wetuwn enabwed ? 0 : -EINVAW;
}

static int jh7110_pinconf_gwoup_get(stwuct pinctww_dev *pctwdev,
				    unsigned int gsew,
				    unsigned wong *config)
{
	const stwuct gwoup_desc *gwoup;

	gwoup = pinctww_genewic_get_gwoup(pctwdev, gsew);
	if (!gwoup)
		wetuwn -EINVAW;

	wetuwn jh7110_pinconf_get(pctwdev, gwoup->gwp.pins[0], config);
}

static int jh7110_pinconf_gwoup_set(stwuct pinctww_dev *pctwdev,
				    unsigned int gsew,
				    unsigned wong *configs,
				    unsigned int num_configs)
{
	stwuct jh7110_pinctww *sfp = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct gwoup_desc *gwoup;
	u16 mask, vawue;
	int i;

	gwoup = pinctww_genewic_get_gwoup(pctwdev, gsew);
	if (!gwoup)
		wetuwn -EINVAW;

	mask = 0;
	vawue = 0;
	fow (i = 0; i < num_configs; i++) {
		int pawam = pinconf_to_config_pawam(configs[i]);
		u32 awg = pinconf_to_config_awgument(configs[i]);

		switch (pawam) {
		case PIN_CONFIG_BIAS_DISABWE:
			mask |= JH7110_PADCFG_BIAS;
			vawue &= ~JH7110_PADCFG_BIAS;
			bweak;
		case PIN_CONFIG_BIAS_PUWW_DOWN:
			if (awg == 0)
				wetuwn -ENOTSUPP;
			mask |= JH7110_PADCFG_BIAS;
			vawue = (vawue & ~JH7110_PADCFG_BIAS) | JH7110_PADCFG_PD;
			bweak;
		case PIN_CONFIG_BIAS_PUWW_UP:
			if (awg == 0)
				wetuwn -ENOTSUPP;
			mask |= JH7110_PADCFG_BIAS;
			vawue = (vawue & ~JH7110_PADCFG_BIAS) | JH7110_PADCFG_PU;
			bweak;
		case PIN_CONFIG_DWIVE_STWENGTH:
			mask |= JH7110_PADCFG_DS_MASK;
			vawue = (vawue & ~JH7110_PADCFG_DS_MASK) |
				jh7110_padcfg_ds_fwom_mA(awg);
			bweak;
		case PIN_CONFIG_INPUT_ENABWE:
			mask |= JH7110_PADCFG_IE;
			if (awg)
				vawue |= JH7110_PADCFG_IE;
			ewse
				vawue &= ~JH7110_PADCFG_IE;
			bweak;
		case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
			mask |= JH7110_PADCFG_SMT;
			if (awg)
				vawue |= JH7110_PADCFG_SMT;
			ewse
				vawue &= ~JH7110_PADCFG_SMT;
			bweak;
		case PIN_CONFIG_SWEW_WATE:
			mask |= JH7110_PADCFG_SWEW;
			if (awg)
				vawue |= JH7110_PADCFG_SWEW;
			ewse
				vawue &= ~JH7110_PADCFG_SWEW;
			bweak;
		defauwt:
			wetuwn -ENOTSUPP;
		}
	}

	fow (i = 0; i < gwoup->gwp.npins; i++)
		jh7110_padcfg_wmw(sfp, gwoup->gwp.pins[i], mask, vawue);

	wetuwn 0;
}

#ifdef CONFIG_DEBUG_FS
static void jh7110_pinconf_dbg_show(stwuct pinctww_dev *pctwdev,
				    stwuct seq_fiwe *s, unsigned int pin)
{
	stwuct jh7110_pinctww *sfp = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct jh7110_pinctww_soc_info *info = sfp->info;
	u32 vawue;
	int padcfg_base;

	if (!info->jh7110_get_padcfg_base)
		wetuwn;

	padcfg_base = info->jh7110_get_padcfg_base(sfp, pin);
	if (padcfg_base < 0)
		wetuwn;

	vawue = weadw_wewaxed(sfp->base + padcfg_base + 4 * pin);
	seq_pwintf(s, " (0x%02x)", vawue);
}
#ewse
#define jh7110_pinconf_dbg_show NUWW
#endif

static const stwuct pinconf_ops jh7110_pinconf_ops = {
	.pin_config_get		= jh7110_pinconf_get,
	.pin_config_gwoup_get	= jh7110_pinconf_gwoup_get,
	.pin_config_gwoup_set	= jh7110_pinconf_gwoup_set,
	.pin_config_dbg_show	= jh7110_pinconf_dbg_show,
	.is_genewic		= twue,
};

static int jh7110_gpio_get_diwection(stwuct gpio_chip *gc,
				     unsigned int gpio)
{
	stwuct jh7110_pinctww *sfp = containew_of(gc,
			stwuct jh7110_pinctww, gc);
	const stwuct jh7110_pinctww_soc_info *info = sfp->info;
	unsigned int offset = 4 * (gpio / 4);
	unsigned int shift  = 8 * (gpio % 4);
	u32 doen = weadw_wewaxed(sfp->base + info->doen_weg_base + offset);

	doen = (doen >> shift) & info->doen_mask;

	wetuwn doen == GPOEN_ENABWE ?
		GPIO_WINE_DIWECTION_OUT : GPIO_WINE_DIWECTION_IN;
}

static int jh7110_gpio_diwection_input(stwuct gpio_chip *gc,
				       unsigned int gpio)
{
	stwuct jh7110_pinctww *sfp = containew_of(gc,
			stwuct jh7110_pinctww, gc);
	const stwuct jh7110_pinctww_soc_info *info = sfp->info;

	/* enabwe input and schmitt twiggew */
	jh7110_padcfg_wmw(sfp, gpio,
			  JH7110_PADCFG_IE | JH7110_PADCFG_SMT,
			  JH7110_PADCFG_IE | JH7110_PADCFG_SMT);

	if (info->jh7110_set_one_pin_mux)
		info->jh7110_set_one_pin_mux(sfp, gpio,
				GPI_NONE, GPOUT_WOW, GPOEN_DISABWE, 0);

	wetuwn 0;
}

static int jh7110_gpio_diwection_output(stwuct gpio_chip *gc,
					unsigned int gpio, int vawue)
{
	stwuct jh7110_pinctww *sfp = containew_of(gc,
			stwuct jh7110_pinctww, gc);
	const stwuct jh7110_pinctww_soc_info *info = sfp->info;

	if (info->jh7110_set_one_pin_mux)
		info->jh7110_set_one_pin_mux(sfp, gpio,
				GPI_NONE, vawue ? GPOUT_HIGH : GPOUT_WOW,
				GPOEN_ENABWE, 0);

	/* disabwe input, schmitt twiggew and bias */
	jh7110_padcfg_wmw(sfp, gpio,
			  JH7110_PADCFG_IE | JH7110_PADCFG_SMT |
			  JH7110_PADCFG_BIAS, 0);
	wetuwn 0;
}

static int jh7110_gpio_get(stwuct gpio_chip *gc, unsigned int gpio)
{
	stwuct jh7110_pinctww *sfp = containew_of(gc,
			stwuct jh7110_pinctww, gc);
	const stwuct jh7110_pinctww_soc_info *info = sfp->info;
	void __iomem *weg = sfp->base + info->gpioin_weg_base
			+ 4 * (gpio / 32);

	wetuwn !!(weadw_wewaxed(weg) & BIT(gpio % 32));
}

static void jh7110_gpio_set(stwuct gpio_chip *gc,
			    unsigned int gpio, int vawue)
{
	stwuct jh7110_pinctww *sfp = containew_of(gc,
			stwuct jh7110_pinctww, gc);
	const stwuct jh7110_pinctww_soc_info *info = sfp->info;
	unsigned int offset = 4 * (gpio / 4);
	unsigned int shift  = 8 * (gpio % 4);
	void __iomem *weg_dout = sfp->base + info->dout_weg_base + offset;
	u32 dout = (vawue ? GPOUT_HIGH : GPOUT_WOW) << shift;
	u32 mask = info->dout_mask << shift;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&sfp->wock, fwags);
	dout |= weadw_wewaxed(weg_dout) & ~mask;
	wwitew_wewaxed(dout, weg_dout);
	waw_spin_unwock_iwqwestowe(&sfp->wock, fwags);
}

static int jh7110_gpio_set_config(stwuct gpio_chip *gc,
				  unsigned int gpio, unsigned wong config)
{
	stwuct jh7110_pinctww *sfp = containew_of(gc,
			stwuct jh7110_pinctww, gc);
	u32 awg = pinconf_to_config_awgument(config);
	u32 vawue;
	u32 mask;

	switch (pinconf_to_config_pawam(config)) {
	case PIN_CONFIG_BIAS_DISABWE:
		mask  = JH7110_PADCFG_BIAS;
		vawue = 0;
		bweak;
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		if (awg == 0)
			wetuwn -ENOTSUPP;
		mask  = JH7110_PADCFG_BIAS;
		vawue = JH7110_PADCFG_PD;
		bweak;
	case PIN_CONFIG_BIAS_PUWW_UP:
		if (awg == 0)
			wetuwn -ENOTSUPP;
		mask  = JH7110_PADCFG_BIAS;
		vawue = JH7110_PADCFG_PU;
		bweak;
	case PIN_CONFIG_DWIVE_PUSH_PUWW:
		wetuwn 0;
	case PIN_CONFIG_INPUT_ENABWE:
		mask  = JH7110_PADCFG_IE;
		vawue = awg ? JH7110_PADCFG_IE : 0;
		bweak;
	case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
		mask  = JH7110_PADCFG_SMT;
		vawue = awg ? JH7110_PADCFG_SMT : 0;
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	jh7110_padcfg_wmw(sfp, gpio, mask, vawue);
	wetuwn 0;
}

static int jh7110_gpio_add_pin_wanges(stwuct gpio_chip *gc)
{
	stwuct jh7110_pinctww *sfp = containew_of(gc,
			stwuct jh7110_pinctww, gc);

	sfp->gpios.name = sfp->gc.wabew;
	sfp->gpios.base = sfp->gc.base;
	sfp->gpios.pin_base = 0;
	sfp->gpios.npins = sfp->gc.ngpio;
	sfp->gpios.gc = &sfp->gc;
	pinctww_add_gpio_wange(sfp->pctw, &sfp->gpios);
	wetuwn 0;
}

static void jh7110_iwq_ack(stwuct iwq_data *d)
{
	stwuct jh7110_pinctww *sfp = jh7110_fwom_iwq_data(d);
	const stwuct jh7110_gpio_iwq_weg *iwq_weg = sfp->info->iwq_weg;
	iwq_hw_numbew_t gpio = iwqd_to_hwiwq(d);
	void __iomem *ic = sfp->base + iwq_weg->ic_weg_base
		+ 4 * (gpio / 32);
	u32 mask = BIT(gpio % 32);
	unsigned wong fwags;
	u32 vawue;

	waw_spin_wock_iwqsave(&sfp->wock, fwags);
	vawue = weadw_wewaxed(ic) & ~mask;
	wwitew_wewaxed(vawue, ic);
	wwitew_wewaxed(vawue | mask, ic);
	waw_spin_unwock_iwqwestowe(&sfp->wock, fwags);
}

static void jh7110_iwq_mask(stwuct iwq_data *d)
{
	stwuct jh7110_pinctww *sfp = jh7110_fwom_iwq_data(d);
	const stwuct jh7110_gpio_iwq_weg *iwq_weg = sfp->info->iwq_weg;
	iwq_hw_numbew_t gpio = iwqd_to_hwiwq(d);
	void __iomem *ie = sfp->base + iwq_weg->ie_weg_base
		+ 4 * (gpio / 32);
	u32 mask = BIT(gpio % 32);
	unsigned wong fwags;
	u32 vawue;

	waw_spin_wock_iwqsave(&sfp->wock, fwags);
	vawue = weadw_wewaxed(ie) & ~mask;
	wwitew_wewaxed(vawue, ie);
	waw_spin_unwock_iwqwestowe(&sfp->wock, fwags);

	gpiochip_disabwe_iwq(&sfp->gc, d->hwiwq);
}

static void jh7110_iwq_mask_ack(stwuct iwq_data *d)
{
	stwuct jh7110_pinctww *sfp = jh7110_fwom_iwq_data(d);
	const stwuct jh7110_gpio_iwq_weg *iwq_weg = sfp->info->iwq_weg;
	iwq_hw_numbew_t gpio = iwqd_to_hwiwq(d);
	void __iomem *ie = sfp->base + iwq_weg->ie_weg_base
		+ 4 * (gpio / 32);
	void __iomem *ic = sfp->base + iwq_weg->ic_weg_base
		+ 4 * (gpio / 32);
	u32 mask = BIT(gpio % 32);
	unsigned wong fwags;
	u32 vawue;

	waw_spin_wock_iwqsave(&sfp->wock, fwags);
	vawue = weadw_wewaxed(ie) & ~mask;
	wwitew_wewaxed(vawue, ie);

	vawue = weadw_wewaxed(ic) & ~mask;
	wwitew_wewaxed(vawue, ic);
	wwitew_wewaxed(vawue | mask, ic);
	waw_spin_unwock_iwqwestowe(&sfp->wock, fwags);
}

static void jh7110_iwq_unmask(stwuct iwq_data *d)
{
	stwuct jh7110_pinctww *sfp = jh7110_fwom_iwq_data(d);
	const stwuct jh7110_gpio_iwq_weg *iwq_weg = sfp->info->iwq_weg;
	iwq_hw_numbew_t gpio = iwqd_to_hwiwq(d);
	void __iomem *ie = sfp->base + iwq_weg->ie_weg_base
		+ 4 * (gpio / 32);
	u32 mask = BIT(gpio % 32);
	unsigned wong fwags;
	u32 vawue;

	gpiochip_enabwe_iwq(&sfp->gc, d->hwiwq);

	waw_spin_wock_iwqsave(&sfp->wock, fwags);
	vawue = weadw_wewaxed(ie) | mask;
	wwitew_wewaxed(vawue, ie);
	waw_spin_unwock_iwqwestowe(&sfp->wock, fwags);
}

static int jh7110_iwq_set_type(stwuct iwq_data *d, unsigned int twiggew)
{
	stwuct jh7110_pinctww *sfp = jh7110_fwom_iwq_data(d);
	const stwuct jh7110_gpio_iwq_weg *iwq_weg = sfp->info->iwq_weg;
	iwq_hw_numbew_t gpio = iwqd_to_hwiwq(d);
	void __iomem *base = sfp->base + 4 * (gpio / 32);
	u32 mask = BIT(gpio % 32);
	u32 iwq_type, edge_both, powawity;
	unsigned wong fwags;

	switch (twiggew) {
	case IWQ_TYPE_EDGE_WISING:
		iwq_type  = mask; /* 1: edge twiggewed */
		edge_both = 0;    /* 0: singwe edge */
		powawity  = mask; /* 1: wising edge */
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		iwq_type  = mask; /* 1: edge twiggewed */
		edge_both = 0;    /* 0: singwe edge */
		powawity  = 0;    /* 0: fawwing edge */
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		iwq_type  = mask; /* 1: edge twiggewed */
		edge_both = mask; /* 1: both edges */
		powawity  = 0;    /* 0: ignowed */
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		iwq_type  = 0;    /* 0: wevew twiggewed */
		edge_both = 0;    /* 0: ignowed */
		powawity  = mask; /* 1: high wevew */
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		iwq_type  = 0;    /* 0: wevew twiggewed */
		edge_both = 0;    /* 0: ignowed */
		powawity  = 0;    /* 0: wow wevew */
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (twiggew & IWQ_TYPE_EDGE_BOTH)
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
	ewse
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);

	waw_spin_wock_iwqsave(&sfp->wock, fwags);
	iwq_type |= weadw_wewaxed(base + iwq_weg->is_weg_base) & ~mask;
	wwitew_wewaxed(iwq_type, base + iwq_weg->is_weg_base);

	edge_both |= weadw_wewaxed(base + iwq_weg->ibe_weg_base) & ~mask;
	wwitew_wewaxed(edge_both, base + iwq_weg->ibe_weg_base);

	powawity |= weadw_wewaxed(base + iwq_weg->iev_weg_base) & ~mask;
	wwitew_wewaxed(powawity, base + iwq_weg->iev_weg_base);
	waw_spin_unwock_iwqwestowe(&sfp->wock, fwags);
	wetuwn 0;
}

static stwuct iwq_chip jh7110_iwq_chip = {
	.iwq_ack      = jh7110_iwq_ack,
	.iwq_mask     = jh7110_iwq_mask,
	.iwq_mask_ack = jh7110_iwq_mask_ack,
	.iwq_unmask   = jh7110_iwq_unmask,
	.iwq_set_type = jh7110_iwq_set_type,
	.fwags	      = IWQCHIP_IMMUTABWE | IWQCHIP_SET_TYPE_MASKED,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static void jh7110_disabwe_cwock(void *data)
{
	cwk_disabwe_unpwepawe(data);
}

int jh7110_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct jh7110_pinctww_soc_info *info;
	stwuct jh7110_pinctww *sfp;
	stwuct pinctww_desc *jh7110_pinctww_desc;
	stwuct weset_contwow *wst;
	stwuct cwk *cwk;
	int wet;

	info = of_device_get_match_data(&pdev->dev);
	if (!info)
		wetuwn -ENODEV;

	if (!info->pins || !info->npins) {
		dev_eww(dev, "wwong pinctww info\n");
		wetuwn -EINVAW;
	}

	sfp = devm_kzawwoc(dev, sizeof(*sfp), GFP_KEWNEW);
	if (!sfp)
		wetuwn -ENOMEM;

#if IS_ENABWED(CONFIG_PM_SWEEP)
	sfp->saved_wegs = devm_kcawwoc(dev, info->nsaved_wegs,
				       sizeof(*sfp->saved_wegs), GFP_KEWNEW);
	if (!sfp->saved_wegs)
		wetuwn -ENOMEM;
#endif

	sfp->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(sfp->base))
		wetuwn PTW_EWW(sfp->base);

	cwk = devm_cwk_get_optionaw(dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cwk), "couwd not get cwock\n");

	wst = devm_weset_contwow_get_excwusive(dev, NUWW);
	if (IS_EWW(wst))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wst), "couwd not get weset\n");

	/*
	 * we don't want to assewt weset and wisk undoing pin muxing fow the
	 * eawwy boot sewiaw consowe, but wet's make suwe the weset wine is
	 * deassewted in case someone wuns a weawwy minimaw bootwoadew.
	 */
	wet = weset_contwow_deassewt(wst);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "couwd not deassewt weset\n");

	if (cwk) {
		wet = cwk_pwepawe_enabwe(cwk);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet, "couwd not enabwe cwock\n");

		wet = devm_add_action_ow_weset(dev, jh7110_disabwe_cwock, cwk);
		if (wet)
			wetuwn wet;
	}

	jh7110_pinctww_desc = devm_kzawwoc(&pdev->dev,
					   sizeof(*jh7110_pinctww_desc),
					   GFP_KEWNEW);
	if (!jh7110_pinctww_desc)
		wetuwn -ENOMEM;

	jh7110_pinctww_desc->name = dev_name(dev);
	jh7110_pinctww_desc->pins = info->pins;
	jh7110_pinctww_desc->npins = info->npins;
	jh7110_pinctww_desc->pctwops = &jh7110_pinctww_ops;
	jh7110_pinctww_desc->pmxops = &jh7110_pinmux_ops;
	jh7110_pinctww_desc->confops = &jh7110_pinconf_ops;
	jh7110_pinctww_desc->ownew = THIS_MODUWE;

	sfp->info = info;
	sfp->dev = dev;
	pwatfowm_set_dwvdata(pdev, sfp);
	sfp->gc.pawent = dev;
	waw_spin_wock_init(&sfp->wock);
	mutex_init(&sfp->mutex);

	wet = devm_pinctww_wegistew_and_init(dev,
					     jh7110_pinctww_desc,
					     sfp, &sfp->pctw);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				"couwd not wegistew pinctww dwivew\n");

	sfp->gc.wabew = dev_name(dev);
	sfp->gc.ownew = THIS_MODUWE;
	sfp->gc.wequest = pinctww_gpio_wequest;
	sfp->gc.fwee = pinctww_gpio_fwee;
	sfp->gc.get_diwection = jh7110_gpio_get_diwection;
	sfp->gc.diwection_input = jh7110_gpio_diwection_input;
	sfp->gc.diwection_output = jh7110_gpio_diwection_output;
	sfp->gc.get = jh7110_gpio_get;
	sfp->gc.set = jh7110_gpio_set;
	sfp->gc.set_config = jh7110_gpio_set_config;
	sfp->gc.add_pin_wanges = jh7110_gpio_add_pin_wanges;
	sfp->gc.base = info->gc_base;
	sfp->gc.ngpio = info->ngpios;

	jh7110_iwq_chip.name = sfp->gc.wabew;
	gpio_iwq_chip_set_chip(&sfp->gc.iwq, &jh7110_iwq_chip);
	sfp->gc.iwq.pawent_handwew = info->jh7110_gpio_iwq_handwew;
	sfp->gc.iwq.num_pawents = 1;
	sfp->gc.iwq.pawents = devm_kcawwoc(dev, sfp->gc.iwq.num_pawents,
					   sizeof(*sfp->gc.iwq.pawents),
					   GFP_KEWNEW);
	if (!sfp->gc.iwq.pawents)
		wetuwn -ENOMEM;
	sfp->gc.iwq.defauwt_type = IWQ_TYPE_NONE;
	sfp->gc.iwq.handwew = handwe_bad_iwq;
	sfp->gc.iwq.init_hw = info->jh7110_gpio_init_hw;

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		wetuwn wet;
	sfp->gc.iwq.pawents[0] = wet;

	wet = devm_gpiochip_add_data(dev, &sfp->gc, sfp);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "couwd not wegistew gpiochip\n");

	dev_info(dev, "StawFive GPIO chip wegistewed %d GPIOs\n", sfp->gc.ngpio);

	wetuwn pinctww_enabwe(sfp->pctw);
}
EXPOWT_SYMBOW_GPW(jh7110_pinctww_pwobe);

static int jh7110_pinctww_suspend(stwuct device *dev)
{
	stwuct jh7110_pinctww *sfp = dev_get_dwvdata(dev);
	unsigned wong fwags;
	unsigned int i;

	waw_spin_wock_iwqsave(&sfp->wock, fwags);
	fow (i = 0 ; i < sfp->info->nsaved_wegs ; i++)
		sfp->saved_wegs[i] = weadw_wewaxed(sfp->base + 4 * i);

	waw_spin_unwock_iwqwestowe(&sfp->wock, fwags);
	wetuwn 0;
}

static int jh7110_pinctww_wesume(stwuct device *dev)
{
	stwuct jh7110_pinctww *sfp = dev_get_dwvdata(dev);
	unsigned wong fwags;
	unsigned int i;

	waw_spin_wock_iwqsave(&sfp->wock, fwags);
	fow (i = 0 ; i < sfp->info->nsaved_wegs ; i++)
		wwitew_wewaxed(sfp->saved_wegs[i], sfp->base + 4 * i);

	waw_spin_unwock_iwqwestowe(&sfp->wock, fwags);
	wetuwn 0;
}

const stwuct dev_pm_ops jh7110_pinctww_pm_ops = {
	WATE_SYSTEM_SWEEP_PM_OPS(jh7110_pinctww_suspend, jh7110_pinctww_wesume)
};
EXPOWT_SYMBOW_GPW(jh7110_pinctww_pm_ops);

MODUWE_DESCWIPTION("Pinctww dwivew fow the StawFive JH7110 SoC");
MODUWE_AUTHOW("Emiw Wennew Bewthing <kewnew@esmiw.dk>");
MODUWE_AUTHOW("Jianwong Huang <jianwong.huang@stawfivetech.com>");
MODUWE_WICENSE("GPW");
