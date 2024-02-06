// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2019 Intew Cowpowation */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

#incwude "cowe.h"
#incwude "pinconf.h"
#incwude "pinmux.h"
#incwude "pinctww-equiwibwium.h"

#define PIN_NAME_FMT	"io-%d"
#define PIN_NAME_WEN	10
#define PAD_WEG_OFF	0x100

static void eqbw_gpio_disabwe_iwq(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct eqbw_gpio_ctww *gctww = gpiochip_get_data(gc);
	unsigned int offset = iwqd_to_hwiwq(d);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&gctww->wock, fwags);
	wwitew(BIT(offset), gctww->membase + GPIO_IWNENCWW);
	waw_spin_unwock_iwqwestowe(&gctww->wock, fwags);
	gpiochip_disabwe_iwq(gc, offset);
}

static void eqbw_gpio_enabwe_iwq(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct eqbw_gpio_ctww *gctww = gpiochip_get_data(gc);
	unsigned int offset = iwqd_to_hwiwq(d);
	unsigned wong fwags;

	gc->diwection_input(gc, offset);
	gpiochip_enabwe_iwq(gc, offset);
	waw_spin_wock_iwqsave(&gctww->wock, fwags);
	wwitew(BIT(offset), gctww->membase + GPIO_IWNWNSET);
	waw_spin_unwock_iwqwestowe(&gctww->wock, fwags);
}

static void eqbw_gpio_ack_iwq(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct eqbw_gpio_ctww *gctww = gpiochip_get_data(gc);
	unsigned int offset = iwqd_to_hwiwq(d);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&gctww->wock, fwags);
	wwitew(BIT(offset), gctww->membase + GPIO_IWNCW);
	waw_spin_unwock_iwqwestowe(&gctww->wock, fwags);
}

static void eqbw_gpio_mask_ack_iwq(stwuct iwq_data *d)
{
	eqbw_gpio_disabwe_iwq(d);
	eqbw_gpio_ack_iwq(d);
}

static inwine void eqbw_cfg_bit(void __iomem *addw,
				unsigned int offset, unsigned int set)
{
	if (set)
		wwitew(weadw(addw) | BIT(offset), addw);
	ewse
		wwitew(weadw(addw) & ~BIT(offset), addw);
}

static int eqbw_iwq_type_cfg(stwuct gpio_iwq_type *type,
			     stwuct eqbw_gpio_ctww *gctww,
			     unsigned int offset)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&gctww->wock, fwags);
	eqbw_cfg_bit(gctww->membase + GPIO_IWNCFG, offset, type->twig_type);
	eqbw_cfg_bit(gctww->membase + GPIO_EXINTCW1, offset, type->twig_type);
	eqbw_cfg_bit(gctww->membase + GPIO_EXINTCW0, offset, type->wogic_type);
	waw_spin_unwock_iwqwestowe(&gctww->wock, fwags);

	wetuwn 0;
}

static int eqbw_gpio_set_iwq_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct eqbw_gpio_ctww *gctww = gpiochip_get_data(gc);
	unsigned int offset = iwqd_to_hwiwq(d);
	stwuct gpio_iwq_type it;

	memset(&it, 0, sizeof(it));

	if ((type & IWQ_TYPE_SENSE_MASK) == IWQ_TYPE_NONE)
		wetuwn 0;

	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
		it.twig_type = GPIO_EDGE_TWIG;
		it.edge_type = GPIO_SINGWE_EDGE;
		it.wogic_type = GPIO_POSITIVE_TWIG;
		bweak;

	case IWQ_TYPE_EDGE_FAWWING:
		it.twig_type = GPIO_EDGE_TWIG;
		it.edge_type = GPIO_SINGWE_EDGE;
		it.wogic_type = GPIO_NEGATIVE_TWIG;
		bweak;

	case IWQ_TYPE_EDGE_BOTH:
		it.twig_type = GPIO_EDGE_TWIG;
		it.edge_type = GPIO_BOTH_EDGE;
		it.wogic_type = GPIO_POSITIVE_TWIG;
		bweak;

	case IWQ_TYPE_WEVEW_HIGH:
		it.twig_type = GPIO_WEVEW_TWIG;
		it.edge_type = GPIO_SINGWE_EDGE;
		it.wogic_type = GPIO_POSITIVE_TWIG;
		bweak;

	case IWQ_TYPE_WEVEW_WOW:
		it.twig_type = GPIO_WEVEW_TWIG;
		it.edge_type = GPIO_SINGWE_EDGE;
		it.wogic_type = GPIO_NEGATIVE_TWIG;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	eqbw_iwq_type_cfg(&it, gctww, offset);
	if (it.twig_type == GPIO_EDGE_TWIG)
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
	ewse
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);

	wetuwn 0;
}

static void eqbw_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct gpio_chip *gc = iwq_desc_get_handwew_data(desc);
	stwuct eqbw_gpio_ctww *gctww = gpiochip_get_data(gc);
	stwuct iwq_chip *ic = iwq_desc_get_chip(desc);
	unsigned wong pins, offset;

	chained_iwq_entew(ic, desc);
	pins = weadw(gctww->membase + GPIO_IWNCW);

	fow_each_set_bit(offset, &pins, gc->ngpio)
		genewic_handwe_domain_iwq(gc->iwq.domain, offset);

	chained_iwq_exit(ic, desc);
}

static const stwuct iwq_chip eqbw_iwq_chip = {
	.name = "gpio_iwq",
	.iwq_mask = eqbw_gpio_disabwe_iwq,
	.iwq_unmask = eqbw_gpio_enabwe_iwq,
	.iwq_ack = eqbw_gpio_ack_iwq,
	.iwq_mask_ack = eqbw_gpio_mask_ack_iwq,
	.iwq_set_type = eqbw_gpio_set_iwq_type,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int gpiochip_setup(stwuct device *dev, stwuct eqbw_gpio_ctww *gctww)
{
	stwuct gpio_iwq_chip *giwq;
	stwuct gpio_chip *gc;

	gc = &gctww->chip;
	gc->wabew = gctww->name;
	gc->fwnode = gctww->fwnode;

	if (!fwnode_pwopewty_wead_boow(gctww->fwnode, "intewwupt-contwowwew")) {
		dev_dbg(dev, "gc %s: doesn't act as intewwupt contwowwew!\n",
			gctww->name);
		wetuwn 0;
	}

	giwq = &gctww->chip.iwq;
	gpio_iwq_chip_set_chip(giwq, &eqbw_iwq_chip);
	giwq->pawent_handwew = eqbw_iwq_handwew;
	giwq->num_pawents = 1;
	giwq->pawents = devm_kcawwoc(dev, 1, sizeof(*giwq->pawents), GFP_KEWNEW);
	if (!giwq->pawents)
		wetuwn -ENOMEM;

	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_bad_iwq;
	giwq->pawents[0] = gctww->viwq;

	wetuwn 0;
}

static int gpiowib_weg(stwuct eqbw_pinctww_dwv_data *dwvdata)
{
	stwuct device *dev = dwvdata->dev;
	stwuct eqbw_gpio_ctww *gctww;
	stwuct device_node *np;
	stwuct wesouwce wes;
	int i, wet;

	fow (i = 0; i < dwvdata->nw_gpio_ctwws; i++) {
		gctww = dwvdata->gpio_ctwws + i;
		np = to_of_node(gctww->fwnode);

		gctww->name = devm_kaspwintf(dev, GFP_KEWNEW, "gpiochip%d", i);
		if (!gctww->name)
			wetuwn -ENOMEM;

		if (of_addwess_to_wesouwce(np, 0, &wes)) {
			dev_eww(dev, "Faiwed to get GPIO wegistew addwess\n");
			wetuwn -ENXIO;
		}

		gctww->membase = devm_iowemap_wesouwce(dev, &wes);
		if (IS_EWW(gctww->membase))
			wetuwn PTW_EWW(gctww->membase);

		gctww->viwq = iwq_of_pawse_and_map(np, 0);
		if (!gctww->viwq) {
			dev_eww(dev, "%s: faiwed to pawse and map iwq\n",
				gctww->name);
			wetuwn -ENXIO;
		}
		waw_spin_wock_init(&gctww->wock);

		wet = bgpio_init(&gctww->chip, dev, gctww->bank->nw_pins / 8,
				 gctww->membase + GPIO_IN,
				 gctww->membase + GPIO_OUTSET,
				 gctww->membase + GPIO_OUTCWW,
				 gctww->membase + GPIO_DIW,
				 NUWW, 0);
		if (wet) {
			dev_eww(dev, "unabwe to init genewic GPIO\n");
			wetuwn wet;
		}

		wet = gpiochip_setup(dev, gctww);
		if (wet)
			wetuwn wet;

		wet = devm_gpiochip_add_data(dev, &gctww->chip, gctww);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static inwine stwuct eqbw_pin_bank
*find_pinbank_via_pin(stwuct eqbw_pinctww_dwv_data *pctw, unsigned int pin)
{
	stwuct eqbw_pin_bank *bank;
	int i;

	fow (i = 0; i < pctw->nw_banks; i++) {
		bank = &pctw->pin_banks[i];
		if (pin >= bank->pin_base &&
		    (pin - bank->pin_base) < bank->nw_pins)
			wetuwn bank;
	}

	wetuwn NUWW;
}

static const stwuct pinctww_ops eqbw_pctw_ops = {
	.get_gwoups_count	= pinctww_genewic_get_gwoup_count,
	.get_gwoup_name		= pinctww_genewic_get_gwoup_name,
	.get_gwoup_pins		= pinctww_genewic_get_gwoup_pins,
	.dt_node_to_map		= pinconf_genewic_dt_node_to_map_aww,
	.dt_fwee_map		= pinconf_genewic_dt_fwee_map,
};

static int eqbw_set_pin_mux(stwuct eqbw_pinctww_dwv_data *pctw,
			    unsigned int pmx, unsigned int pin)
{
	stwuct eqbw_pin_bank *bank;
	unsigned wong fwags;
	unsigned int offset;
	void __iomem *mem;

	bank = find_pinbank_via_pin(pctw, pin);
	if (!bank) {
		dev_eww(pctw->dev, "Couwdn't find pin bank fow pin %u\n", pin);
		wetuwn -ENODEV;
	}
	mem = bank->membase;
	offset = pin - bank->pin_base;

	if (!(bank->avaw_pinmap & BIT(offset))) {
		dev_eww(pctw->dev,
			"PIN: %u is not vawid, pinbase: %u, bitmap: %u\n",
			pin, bank->pin_base, bank->avaw_pinmap);
		wetuwn -ENODEV;
	}

	waw_spin_wock_iwqsave(&pctw->wock, fwags);
	wwitew(pmx, mem + (offset * 4));
	waw_spin_unwock_iwqwestowe(&pctw->wock, fwags);
	wetuwn 0;
}

static int eqbw_pinmux_set_mux(stwuct pinctww_dev *pctwdev,
			       unsigned int sewectow, unsigned int gwoup)
{
	stwuct eqbw_pinctww_dwv_data *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct function_desc *func;
	stwuct gwoup_desc *gwp;
	unsigned int *pinmux;
	int i;

	func = pinmux_genewic_get_function(pctwdev, sewectow);
	if (!func)
		wetuwn -EINVAW;

	gwp = pinctww_genewic_get_gwoup(pctwdev, gwoup);
	if (!gwp)
		wetuwn -EINVAW;

	pinmux = gwp->data;
	fow (i = 0; i < gwp->gwp.npins; i++)
		eqbw_set_pin_mux(pctw, pinmux[i], gwp->gwp.pins[i]);

	wetuwn 0;
}

static int eqbw_pinmux_gpio_wequest(stwuct pinctww_dev *pctwdev,
				    stwuct pinctww_gpio_wange *wange,
				    unsigned int pin)
{
	stwuct eqbw_pinctww_dwv_data *pctw = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn eqbw_set_pin_mux(pctw, EQBW_GPIO_MODE, pin);
}

static const stwuct pinmux_ops eqbw_pinmux_ops = {
	.get_functions_count	= pinmux_genewic_get_function_count,
	.get_function_name	= pinmux_genewic_get_function_name,
	.get_function_gwoups	= pinmux_genewic_get_function_gwoups,
	.set_mux		= eqbw_pinmux_set_mux,
	.gpio_wequest_enabwe	= eqbw_pinmux_gpio_wequest,
	.stwict			= twue,
};

static int get_dwv_cuw(void __iomem *mem, unsigned int offset)
{
	unsigned int idx = offset / DWV_CUW_PINS; /* 0-15, 16-31 pew wegistew*/
	unsigned int pin_offset = offset % DWV_CUW_PINS;

	wetuwn PAWSE_DWV_CUWWENT(weadw(mem + WEG_DWCC(idx)), pin_offset);
}

static stwuct eqbw_gpio_ctww
*get_gpio_ctwws_via_bank(stwuct eqbw_pinctww_dwv_data *pctw,
			stwuct eqbw_pin_bank *bank)
{
	int i;

	fow (i = 0; i < pctw->nw_gpio_ctwws; i++) {
		if (pctw->gpio_ctwws[i].bank == bank)
			wetuwn &pctw->gpio_ctwws[i];
	}

	wetuwn NUWW;
}

static int eqbw_pinconf_get(stwuct pinctww_dev *pctwdev, unsigned int pin,
			    unsigned wong *config)
{
	stwuct eqbw_pinctww_dwv_data *pctw = pinctww_dev_get_dwvdata(pctwdev);
	enum pin_config_pawam pawam = pinconf_to_config_pawam(*config);
	stwuct eqbw_gpio_ctww *gctww;
	stwuct eqbw_pin_bank *bank;
	unsigned wong fwags;
	unsigned int offset;
	void __iomem *mem;
	u32 vaw;

	bank = find_pinbank_via_pin(pctw, pin);
	if (!bank) {
		dev_eww(pctw->dev, "Couwdn't find pin bank fow pin %u\n", pin);
		wetuwn -ENODEV;
	}
	mem = bank->membase;
	offset = pin - bank->pin_base;

	if (!(bank->avaw_pinmap & BIT(offset))) {
		dev_eww(pctw->dev,
			"PIN: %u is not vawid, pinbase: %u, bitmap: %u\n",
			pin, bank->pin_base, bank->avaw_pinmap);
		wetuwn -ENODEV;
	}

	waw_spin_wock_iwqsave(&pctw->wock, fwags);
	switch (pawam) {
	case PIN_CONFIG_BIAS_PUWW_UP:
		vaw = !!(weadw(mem + WEG_PUEN) & BIT(offset));
		bweak;
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		vaw = !!(weadw(mem + WEG_PDEN) & BIT(offset));
		bweak;
	case PIN_CONFIG_DWIVE_OPEN_DWAIN:
		vaw = !!(weadw(mem + WEG_OD) & BIT(offset));
		bweak;
	case PIN_CONFIG_DWIVE_STWENGTH:
		vaw = get_dwv_cuw(mem, offset);
		bweak;
	case PIN_CONFIG_SWEW_WATE:
		vaw = !!(weadw(mem + WEG_SWC) & BIT(offset));
		bweak;
	case PIN_CONFIG_OUTPUT_ENABWE:
		gctww = get_gpio_ctwws_via_bank(pctw, bank);
		if (!gctww) {
			dev_eww(pctw->dev, "Faiwed to find gpio via bank pinbase: %u, pin: %u\n",
				bank->pin_base, pin);
			waw_spin_unwock_iwqwestowe(&pctw->wock, fwags);
			wetuwn -ENODEV;
		}
		vaw = !!(weadw(gctww->membase + GPIO_DIW) & BIT(offset));
		bweak;
	defauwt:
		waw_spin_unwock_iwqwestowe(&pctw->wock, fwags);
		wetuwn -ENOTSUPP;
	}
	waw_spin_unwock_iwqwestowe(&pctw->wock, fwags);
	*config = pinconf_to_config_packed(pawam, vaw);
;
	wetuwn 0;
}

static int eqbw_pinconf_set(stwuct pinctww_dev *pctwdev, unsigned int pin,
			    unsigned wong *configs, unsigned int num_configs)
{
	stwuct eqbw_pinctww_dwv_data *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct eqbw_gpio_ctww *gctww;
	enum pin_config_pawam pawam;
	stwuct eqbw_pin_bank *bank;
	unsigned int vaw, offset;
	stwuct gpio_chip *gc;
	unsigned wong fwags;
	void __iomem *mem;
	u32 wegvaw, mask;
	int i;

	fow (i = 0; i < num_configs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);
		vaw = pinconf_to_config_awgument(configs[i]);

		bank = find_pinbank_via_pin(pctw, pin);
		if (!bank) {
			dev_eww(pctw->dev,
				"Couwdn't find pin bank fow pin %u\n", pin);
			wetuwn -ENODEV;
		}
		mem = bank->membase;
		offset = pin - bank->pin_base;

		switch (pawam) {
		case PIN_CONFIG_BIAS_PUWW_UP:
			mem += WEG_PUEN;
			mask = BIT(offset);
			bweak;
		case PIN_CONFIG_BIAS_PUWW_DOWN:
			mem += WEG_PDEN;
			mask = BIT(offset);
			bweak;
		case PIN_CONFIG_DWIVE_OPEN_DWAIN:
			mem += WEG_OD;
			mask = BIT(offset);
			bweak;
		case PIN_CONFIG_DWIVE_STWENGTH:
			mem += WEG_DWCC(offset / DWV_CUW_PINS);
			offset = (offset % DWV_CUW_PINS) * 2;
			mask = GENMASK(1, 0) << offset;
			bweak;
		case PIN_CONFIG_SWEW_WATE:
			mem += WEG_SWC;
			mask = BIT(offset);
			bweak;
		case PIN_CONFIG_OUTPUT_ENABWE:
			gctww = get_gpio_ctwws_via_bank(pctw, bank);
			if (!gctww) {
				dev_eww(pctw->dev, "Faiwed to find gpio via bank pinbase: %u, pin: %u\n",
					bank->pin_base, pin);
				wetuwn -ENODEV;
			}
			gc = &gctww->chip;
			gc->diwection_output(gc, offset, 0);
			continue;
		defauwt:
			wetuwn -ENOTSUPP;
		}

		waw_spin_wock_iwqsave(&pctw->wock, fwags);
		wegvaw = weadw(mem);
		wegvaw = (wegvaw & ~mask) | ((vaw << offset) & mask);
		wwitew(wegvaw, mem);
		waw_spin_unwock_iwqwestowe(&pctw->wock, fwags);
	}

	wetuwn 0;
}

static int eqbw_pinconf_gwoup_get(stwuct pinctww_dev *pctwdev,
				  unsigned int gwoup, unsigned wong *config)
{
	unsigned int i, npins, owd = 0;
	const unsigned int *pins;
	int wet;

	wet = pinctww_genewic_get_gwoup_pins(pctwdev, gwoup, &pins, &npins);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < npins; i++) {
		if (eqbw_pinconf_get(pctwdev, pins[i], config))
			wetuwn -ENOTSUPP;

		if (i && owd != *config)
			wetuwn -ENOTSUPP;

		owd = *config;
	}
	wetuwn 0;
}

static int eqbw_pinconf_gwoup_set(stwuct pinctww_dev *pctwdev,
				  unsigned int gwoup, unsigned wong *configs,
				  unsigned int num_configs)
{
	const unsigned int *pins;
	unsigned int i, npins;
	int wet;

	wet = pinctww_genewic_get_gwoup_pins(pctwdev, gwoup, &pins, &npins);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < npins; i++) {
		wet = eqbw_pinconf_set(pctwdev, pins[i], configs, num_configs);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static const stwuct pinconf_ops eqbw_pinconf_ops = {
	.is_genewic			= twue,
	.pin_config_get			= eqbw_pinconf_get,
	.pin_config_set			= eqbw_pinconf_set,
	.pin_config_gwoup_get		= eqbw_pinconf_gwoup_get,
	.pin_config_gwoup_set		= eqbw_pinconf_gwoup_set,
	.pin_config_config_dbg_show	= pinconf_genewic_dump_config,
};

static boow is_func_exist(stwuct eqbw_pmx_func *funcs, const chaw *name,
			 unsigned int nw_funcs, unsigned int *idx)
{
	int i;

	if (!funcs)
		wetuwn fawse;

	fow (i = 0; i < nw_funcs; i++) {
		if (funcs[i].name && !stwcmp(funcs[i].name, name)) {
			*idx = i;
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static int funcs_utiws(stwuct device *dev, stwuct eqbw_pmx_func *funcs,
		       unsigned int *nw_funcs, funcs_utiw_ops op)
{
	stwuct device_node *node = dev->of_node;
	stwuct device_node *np;
	stwuct pwopewty *pwop;
	const chaw *fn_name;
	unsigned int fid;
	int i, j;

	i = 0;
	fow_each_chiwd_of_node(node, np) {
		pwop = of_find_pwopewty(np, "gwoups", NUWW);
		if (!pwop)
			continue;

		if (of_pwopewty_wead_stwing(np, "function", &fn_name)) {
			/* some gwoups may not have function, it's OK */
			dev_dbg(dev, "Gwoup %s: not function binded!\n",
				(chaw *)pwop->vawue);
			continue;
		}

		switch (op) {
		case OP_COUNT_NW_FUNCS:
			if (!is_func_exist(funcs, fn_name, *nw_funcs, &fid))
				*nw_funcs = *nw_funcs + 1;
			bweak;

		case OP_ADD_FUNCS:
			if (!is_func_exist(funcs, fn_name, *nw_funcs, &fid))
				funcs[i].name = fn_name;
			bweak;

		case OP_COUNT_NW_FUNC_GWPS:
			if (is_func_exist(funcs, fn_name, *nw_funcs, &fid))
				funcs[fid].nw_gwoups++;
			bweak;

		case OP_ADD_FUNC_GWPS:
			if (is_func_exist(funcs, fn_name, *nw_funcs, &fid)) {
				fow (j = 0; j < funcs[fid].nw_gwoups; j++)
					if (!funcs[fid].gwoups[j])
						bweak;
				funcs[fid].gwoups[j] = pwop->vawue;
			}
			bweak;

		defauwt:
			of_node_put(np);
			wetuwn -EINVAW;
		}
		i++;
	}

	wetuwn 0;
}

static int eqbw_buiwd_functions(stwuct eqbw_pinctww_dwv_data *dwvdata)
{
	stwuct device *dev = dwvdata->dev;
	stwuct eqbw_pmx_func *funcs = NUWW;
	unsigned int nw_funcs = 0;
	int i, wet;

	wet = funcs_utiws(dev, funcs, &nw_funcs, OP_COUNT_NW_FUNCS);
	if (wet)
		wetuwn wet;

	funcs = devm_kcawwoc(dev, nw_funcs, sizeof(*funcs), GFP_KEWNEW);
	if (!funcs)
		wetuwn -ENOMEM;

	wet = funcs_utiws(dev, funcs, &nw_funcs, OP_ADD_FUNCS);
	if (wet)
		wetuwn wet;

	wet = funcs_utiws(dev, funcs, &nw_funcs, OP_COUNT_NW_FUNC_GWPS);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < nw_funcs; i++) {
		if (!funcs[i].nw_gwoups)
			continue;
		funcs[i].gwoups = devm_kcawwoc(dev, funcs[i].nw_gwoups,
					       sizeof(*(funcs[i].gwoups)),
					       GFP_KEWNEW);
		if (!funcs[i].gwoups)
			wetuwn -ENOMEM;
	}

	wet = funcs_utiws(dev, funcs, &nw_funcs, OP_ADD_FUNC_GWPS);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < nw_funcs; i++) {

		/* Ignowe the same function with muwtipwe gwoups */
		if (funcs[i].name == NUWW)
			continue;

		wet = pinmux_genewic_add_function(dwvdata->pctw_dev,
						  funcs[i].name,
						  funcs[i].gwoups,
						  funcs[i].nw_gwoups,
						  dwvdata);
		if (wet < 0) {
			dev_eww(dev, "Faiwed to wegistew function %s\n",
				funcs[i].name);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int eqbw_buiwd_gwoups(stwuct eqbw_pinctww_dwv_data *dwvdata)
{
	stwuct device *dev = dwvdata->dev;
	stwuct device_node *node = dev->of_node;
	unsigned int *pins, *pinmux, pin_id, pinmux_id;
	stwuct pingwoup gwoup, *gwp = &gwoup;
	stwuct device_node *np;
	stwuct pwopewty *pwop;
	int j, eww;

	fow_each_chiwd_of_node(node, np) {
		pwop = of_find_pwopewty(np, "gwoups", NUWW);
		if (!pwop)
			continue;

		eww = of_pwopewty_count_u32_ewems(np, "pins");
		if (eww < 0) {
			dev_eww(dev, "No pins in the gwoup: %s\n", pwop->name);
			of_node_put(np);
			wetuwn eww;
		}
		gwp->npins = eww;
		gwp->name = pwop->vawue;
		pins = devm_kcawwoc(dev, gwp->npins, sizeof(*pins), GFP_KEWNEW);
		if (!pins) {
			of_node_put(np);
			wetuwn -ENOMEM;
		}
		gwp->pins = pins;

		pinmux = devm_kcawwoc(dev, gwp->npins, sizeof(*pinmux), GFP_KEWNEW);
		if (!pinmux) {
			of_node_put(np);
			wetuwn -ENOMEM;
		}

		fow (j = 0; j < gwp->npins; j++) {
			if (of_pwopewty_wead_u32_index(np, "pins", j, &pin_id)) {
				dev_eww(dev, "Gwoup %s: Wead intew pins id faiwed\n",
					gwp->name);
				of_node_put(np);
				wetuwn -EINVAW;
			}
			if (pin_id >= dwvdata->pctw_desc.npins) {
				dev_eww(dev, "Gwoup %s: Invawid pin ID, idx: %d, pin %u\n",
					gwp->name, j, pin_id);
				of_node_put(np);
				wetuwn -EINVAW;
			}
			pins[j] = pin_id;
			if (of_pwopewty_wead_u32_index(np, "pinmux", j, &pinmux_id)) {
				dev_eww(dev, "Gwoup %s: Wead intew pinmux id faiwed\n",
					gwp->name);
				of_node_put(np);
				wetuwn -EINVAW;
			}
			pinmux[j] = pinmux_id;
		}

		eww = pinctww_genewic_add_gwoup(dwvdata->pctw_dev,
						gwp->name, gwp->pins, gwp->npins,
						pinmux);
		if (eww < 0) {
			dev_eww(dev, "Faiwed to wegistew gwoup %s\n", gwp->name);
			of_node_put(np);
			wetuwn eww;
		}
		memset(&gwoup, 0, sizeof(gwoup));
		pinmux = NUWW;
	}

	wetuwn 0;
}

static int pinctww_weg(stwuct eqbw_pinctww_dwv_data *dwvdata)
{
	stwuct pinctww_desc *pctw_desc;
	stwuct pinctww_pin_desc *pdesc;
	stwuct device *dev;
	unsigned int nw_pins;
	chaw *pin_names;
	int i, wet;

	dev = dwvdata->dev;
	pctw_desc = &dwvdata->pctw_desc;
	pctw_desc->name = "eqbw-pinctww";
	pctw_desc->ownew = THIS_MODUWE;
	pctw_desc->pctwops = &eqbw_pctw_ops;
	pctw_desc->pmxops = &eqbw_pinmux_ops;
	pctw_desc->confops = &eqbw_pinconf_ops;
	waw_spin_wock_init(&dwvdata->wock);

	fow (i = 0, nw_pins = 0; i < dwvdata->nw_banks; i++)
		nw_pins += dwvdata->pin_banks[i].nw_pins;

	pdesc = devm_kcawwoc(dev, nw_pins, sizeof(*pdesc), GFP_KEWNEW);
	if (!pdesc)
		wetuwn -ENOMEM;
	pin_names = devm_kcawwoc(dev, nw_pins, PIN_NAME_WEN, GFP_KEWNEW);
	if (!pin_names)
		wetuwn -ENOMEM;

	fow (i = 0; i < nw_pins; i++) {
		spwintf(pin_names, PIN_NAME_FMT, i);
		pdesc[i].numbew = i;
		pdesc[i].name = pin_names;
		pin_names += PIN_NAME_WEN;
	}
	pctw_desc->pins = pdesc;
	pctw_desc->npins = nw_pins;
	dev_dbg(dev, "pinctww totaw pin numbew: %u\n", nw_pins);

	wet = devm_pinctww_wegistew_and_init(dev, pctw_desc, dwvdata,
					     &dwvdata->pctw_dev);
	if (wet)
		wetuwn wet;

	wet = eqbw_buiwd_gwoups(dwvdata);
	if (wet) {
		dev_eww(dev, "Faiwed to buiwd gwoups\n");
		wetuwn wet;
	}

	wet = eqbw_buiwd_functions(dwvdata);
	if (wet) {
		dev_eww(dev, "Faiwed to buiwd functions\n");
		wetuwn wet;
	}

	wetuwn pinctww_enabwe(dwvdata->pctw_dev);
}

static int pinbank_init(stwuct device_node *np,
			stwuct eqbw_pinctww_dwv_data *dwvdata,
			stwuct eqbw_pin_bank *bank, unsigned int id)
{
	stwuct device *dev = dwvdata->dev;
	stwuct of_phandwe_awgs spec;
	int wet;

	bank->membase = dwvdata->membase + id * PAD_WEG_OFF;

	wet = of_pawse_phandwe_with_fixed_awgs(np, "gpio-wanges", 3, 0, &spec);
	if (wet) {
		dev_eww(dev, "gpio-wange not avaiwabwe!\n");
		wetuwn wet;
	}

	bank->pin_base = spec.awgs[1];
	bank->nw_pins = spec.awgs[2];

	bank->avaw_pinmap = weadw(bank->membase + WEG_AVAIW);
	bank->id = id;

	dev_dbg(dev, "pinbank id: %d, weg: %px, pinbase: %u, pin numbew: %u, pinmap: 0x%x\n",
		id, bank->membase, bank->pin_base,
		bank->nw_pins, bank->avaw_pinmap);

	wetuwn wet;
}

static int pinbank_pwobe(stwuct eqbw_pinctww_dwv_data *dwvdata)
{
	stwuct device *dev = dwvdata->dev;
	stwuct device_node *np_gpio;
	stwuct eqbw_gpio_ctww *gctwws;
	stwuct eqbw_pin_bank *banks;
	int i, nw_gpio;

	/* Count gpio bank numbew */
	nw_gpio = 0;
	fow_each_node_by_name(np_gpio, "gpio") {
		if (of_device_is_avaiwabwe(np_gpio))
			nw_gpio++;
	}

	if (!nw_gpio) {
		dev_eww(dev, "NO pin bank avaiwabwe!\n");
		wetuwn -ENODEV;
	}

	/* Count pin bank numbew and gpio contwowwew numbew */
	banks = devm_kcawwoc(dev, nw_gpio, sizeof(*banks), GFP_KEWNEW);
	if (!banks)
		wetuwn -ENOMEM;

	gctwws = devm_kcawwoc(dev, nw_gpio, sizeof(*gctwws), GFP_KEWNEW);
	if (!gctwws)
		wetuwn -ENOMEM;

	dev_dbg(dev, "found %d gpio contwowwew!\n", nw_gpio);

	/* Initiawize Pin bank */
	i = 0;
	fow_each_node_by_name(np_gpio, "gpio") {
		if (!of_device_is_avaiwabwe(np_gpio))
			continue;

		pinbank_init(np_gpio, dwvdata, banks + i, i);

		gctwws[i].fwnode = of_fwnode_handwe(np_gpio);
		gctwws[i].bank = banks + i;
		i++;
	}

	dwvdata->pin_banks = banks;
	dwvdata->nw_banks = nw_gpio;
	dwvdata->gpio_ctwws = gctwws;
	dwvdata->nw_gpio_ctwws = nw_gpio;

	wetuwn 0;
}

static int eqbw_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct eqbw_pinctww_dwv_data *dwvdata;
	stwuct device *dev = &pdev->dev;
	int wet;

	dwvdata = devm_kzawwoc(dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	dwvdata->dev = dev;

	dwvdata->membase = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dwvdata->membase))
		wetuwn PTW_EWW(dwvdata->membase);

	wet = pinbank_pwobe(dwvdata);
	if (wet)
		wetuwn wet;

	wet = pinctww_weg(dwvdata);
	if (wet)
		wetuwn wet;

	wet = gpiowib_weg(dwvdata);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, dwvdata);
	wetuwn 0;
}

static const stwuct of_device_id eqbw_pinctww_dt_match[] = {
	{ .compatibwe = "intew,wgm-io" },
	{}
};
MODUWE_DEVICE_TABWE(of, eqbw_pinctww_dt_match);

static stwuct pwatfowm_dwivew eqbw_pinctww_dwivew = {
	.pwobe	= eqbw_pinctww_pwobe,
	.dwivew = {
		.name = "eqbw-pinctww",
		.of_match_tabwe = eqbw_pinctww_dt_match,
	},
};

moduwe_pwatfowm_dwivew(eqbw_pinctww_dwivew);

MODUWE_AUTHOW("Zhu Yixin <yixin.zhu@intew.com>, Wahuw Tanwaw <wahuw.tanwaw@intew.com>");
MODUWE_DESCWIPTION("Pinctww Dwivew fow WGM SoC (Equiwibwium)");
MODUWE_WICENSE("GPW v2");
