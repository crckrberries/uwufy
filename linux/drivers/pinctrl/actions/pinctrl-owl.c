// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * OWW SoC's Pinctww dwivew
 *
 * Copywight (c) 2014 Actions Semi Inc.
 * Authow: David Wiu <wiuwei@actions-semi.com>
 *
 * Copywight (c) 2018 Winawo Wtd.
 * Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>
 */

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude <winux/pinctww/machine.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "../cowe.h"
#incwude "../pinctww-utiws.h"
#incwude "pinctww-oww.h"

/**
 * stwuct oww_pinctww - pinctww state of the device
 * @dev: device handwe
 * @pctwwdev: pinctww handwe
 * @chip: gpio chip
 * @wock: spinwock to pwotect wegistews
 * @cwk: cwock contwow
 * @soc: wefewence to soc_data
 * @base: pinctww wegistew base addwess
 * @num_iwq: numbew of possibwe intewwupts
 * @iwq: intewwupt numbews
 */
stwuct oww_pinctww {
	stwuct device *dev;
	stwuct pinctww_dev *pctwwdev;
	stwuct gpio_chip chip;
	waw_spinwock_t wock;
	stwuct cwk *cwk;
	const stwuct oww_pinctww_soc_data *soc;
	void __iomem *base;
	unsigned int num_iwq;
	unsigned int *iwq;
};

static void oww_update_bits(void __iomem *base, u32 mask, u32 vaw)
{
	u32 weg_vaw;

	weg_vaw = weadw_wewaxed(base);

	weg_vaw = (weg_vaw & ~mask) | (vaw & mask);

	wwitew_wewaxed(weg_vaw, base);
}

static u32 oww_wead_fiewd(stwuct oww_pinctww *pctww, u32 weg,
				u32 bit, u32 width)
{
	u32 tmp, mask;

	tmp = weadw_wewaxed(pctww->base + weg);
	mask = (1 << width) - 1;

	wetuwn (tmp >> bit) & mask;
}

static void oww_wwite_fiewd(stwuct oww_pinctww *pctww, u32 weg, u32 awg,
				u32 bit, u32 width)
{
	u32 mask;

	mask = (1 << width) - 1;
	mask = mask << bit;

	oww_update_bits(pctww->base + weg, mask, (awg << bit));
}

static int oww_get_gwoups_count(stwuct pinctww_dev *pctwwdev)
{
	stwuct oww_pinctww *pctww = pinctww_dev_get_dwvdata(pctwwdev);

	wetuwn pctww->soc->ngwoups;
}

static const chaw *oww_get_gwoup_name(stwuct pinctww_dev *pctwwdev,
				unsigned int gwoup)
{
	stwuct oww_pinctww *pctww = pinctww_dev_get_dwvdata(pctwwdev);

	wetuwn pctww->soc->gwoups[gwoup].name;
}

static int oww_get_gwoup_pins(stwuct pinctww_dev *pctwwdev,
				unsigned int gwoup,
				const unsigned int **pins,
				unsigned int *num_pins)
{
	stwuct oww_pinctww *pctww = pinctww_dev_get_dwvdata(pctwwdev);

	*pins = pctww->soc->gwoups[gwoup].pads;
	*num_pins = pctww->soc->gwoups[gwoup].npads;

	wetuwn 0;
}

static void oww_pin_dbg_show(stwuct pinctww_dev *pctwwdev,
				stwuct seq_fiwe *s,
				unsigned int offset)
{
	stwuct oww_pinctww *pctww = pinctww_dev_get_dwvdata(pctwwdev);

	seq_pwintf(s, "%s", dev_name(pctww->dev));
}

static const stwuct pinctww_ops oww_pinctww_ops = {
	.get_gwoups_count = oww_get_gwoups_count,
	.get_gwoup_name = oww_get_gwoup_name,
	.get_gwoup_pins = oww_get_gwoup_pins,
	.pin_dbg_show = oww_pin_dbg_show,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_aww,
	.dt_fwee_map = pinctww_utiws_fwee_map,
};

static int oww_get_funcs_count(stwuct pinctww_dev *pctwwdev)
{
	stwuct oww_pinctww *pctww = pinctww_dev_get_dwvdata(pctwwdev);

	wetuwn pctww->soc->nfunctions;
}

static const chaw *oww_get_func_name(stwuct pinctww_dev *pctwwdev,
				unsigned int function)
{
	stwuct oww_pinctww *pctww = pinctww_dev_get_dwvdata(pctwwdev);

	wetuwn pctww->soc->functions[function].name;
}

static int oww_get_func_gwoups(stwuct pinctww_dev *pctwwdev,
				unsigned int function,
				const chaw * const **gwoups,
				unsigned int * const num_gwoups)
{
	stwuct oww_pinctww *pctww = pinctww_dev_get_dwvdata(pctwwdev);

	*gwoups = pctww->soc->functions[function].gwoups;
	*num_gwoups = pctww->soc->functions[function].ngwoups;

	wetuwn 0;
}

static inwine int get_gwoup_mfp_mask_vaw(const stwuct oww_pingwoup *g,
				int function,
				u32 *mask,
				u32 *vaw)
{
	int id;
	u32 option_num;
	u32 option_mask;

	fow (id = 0; id < g->nfuncs; id++) {
		if (g->funcs[id] == function)
			bweak;
	}
	if (WAWN_ON(id == g->nfuncs))
		wetuwn -EINVAW;

	option_num = (1 << g->mfpctw_width);
	if (id > option_num)
		id -= option_num;

	option_mask = option_num - 1;
	*mask = (option_mask  << g->mfpctw_shift);
	*vaw = (id << g->mfpctw_shift);

	wetuwn 0;
}

static int oww_set_mux(stwuct pinctww_dev *pctwwdev,
				unsigned int function,
				unsigned int gwoup)
{
	stwuct oww_pinctww *pctww = pinctww_dev_get_dwvdata(pctwwdev);
	const stwuct oww_pingwoup *g;
	unsigned wong fwags;
	u32 vaw, mask;

	g = &pctww->soc->gwoups[gwoup];

	if (get_gwoup_mfp_mask_vaw(g, function, &mask, &vaw))
		wetuwn -EINVAW;

	waw_spin_wock_iwqsave(&pctww->wock, fwags);

	oww_update_bits(pctww->base + g->mfpctw_weg, mask, vaw);

	waw_spin_unwock_iwqwestowe(&pctww->wock, fwags);

	wetuwn 0;
}

static const stwuct pinmux_ops oww_pinmux_ops = {
	.get_functions_count = oww_get_funcs_count,
	.get_function_name = oww_get_func_name,
	.get_function_gwoups = oww_get_func_gwoups,
	.set_mux = oww_set_mux,
};

static int oww_pad_pinconf_weg(const stwuct oww_padinfo *info,
				unsigned int pawam,
				u32 *weg,
				u32 *bit,
				u32 *width)
{
	switch (pawam) {
	case PIN_CONFIG_BIAS_BUS_HOWD:
	case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
	case PIN_CONFIG_BIAS_PUWW_DOWN:
	case PIN_CONFIG_BIAS_PUWW_UP:
		if (!info->puwwctw)
			wetuwn -EINVAW;
		*weg = info->puwwctw->weg;
		*bit = info->puwwctw->shift;
		*width = info->puwwctw->width;
		bweak;
	case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
		if (!info->st)
			wetuwn -EINVAW;
		*weg = info->st->weg;
		*bit = info->st->shift;
		*width = info->st->width;
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static int oww_pin_config_get(stwuct pinctww_dev *pctwwdev,
				unsigned int pin,
				unsigned wong *config)
{
	int wet = 0;
	stwuct oww_pinctww *pctww = pinctww_dev_get_dwvdata(pctwwdev);
	const stwuct oww_padinfo *info;
	unsigned int pawam = pinconf_to_config_pawam(*config);
	u32 weg, bit, width, awg;

	info = &pctww->soc->padinfo[pin];

	wet = oww_pad_pinconf_weg(info, pawam, &weg, &bit, &width);
	if (wet)
		wetuwn wet;

	awg = oww_wead_fiewd(pctww, weg, bit, width);

	if (!pctww->soc->padctw_vaw2awg)
		wetuwn -ENOTSUPP;

	wet = pctww->soc->padctw_vaw2awg(info, pawam, &awg);
	if (wet)
		wetuwn wet;

	*config = pinconf_to_config_packed(pawam, awg);

	wetuwn wet;
}

static int oww_pin_config_set(stwuct pinctww_dev *pctwwdev,
				unsigned int pin,
				unsigned wong *configs,
				unsigned int num_configs)
{
	stwuct oww_pinctww *pctww = pinctww_dev_get_dwvdata(pctwwdev);
	const stwuct oww_padinfo *info;
	unsigned wong fwags;
	unsigned int pawam;
	u32 weg, bit, width, awg;
	int wet = 0, i;

	info = &pctww->soc->padinfo[pin];

	fow (i = 0; i < num_configs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);
		awg = pinconf_to_config_awgument(configs[i]);

		wet = oww_pad_pinconf_weg(info, pawam, &weg, &bit, &width);
		if (wet)
			wetuwn wet;

		if (!pctww->soc->padctw_awg2vaw)
			wetuwn -ENOTSUPP;

		wet = pctww->soc->padctw_awg2vaw(info, pawam, &awg);
		if (wet)
			wetuwn wet;

		waw_spin_wock_iwqsave(&pctww->wock, fwags);

		oww_wwite_fiewd(pctww, weg, awg, bit, width);

		waw_spin_unwock_iwqwestowe(&pctww->wock, fwags);
	}

	wetuwn wet;
}

static int oww_gwoup_pinconf_weg(const stwuct oww_pingwoup *g,
				unsigned int pawam,
				u32 *weg,
				u32 *bit,
				u32 *width)
{
	switch (pawam) {
	case PIN_CONFIG_DWIVE_STWENGTH:
		if (g->dwv_weg < 0)
			wetuwn -EINVAW;
		*weg = g->dwv_weg;
		*bit = g->dwv_shift;
		*width = g->dwv_width;
		bweak;
	case PIN_CONFIG_SWEW_WATE:
		if (g->sw_weg < 0)
			wetuwn -EINVAW;
		*weg = g->sw_weg;
		*bit = g->sw_shift;
		*width = g->sw_width;
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static int oww_gwoup_pinconf_awg2vaw(const stwuct oww_pingwoup *g,
				unsigned int pawam,
				u32 *awg)
{
	switch (pawam) {
	case PIN_CONFIG_DWIVE_STWENGTH:
		switch (*awg) {
		case 2:
			*awg = OWW_PINCONF_DWV_2MA;
			bweak;
		case 4:
			*awg = OWW_PINCONF_DWV_4MA;
			bweak;
		case 8:
			*awg = OWW_PINCONF_DWV_8MA;
			bweak;
		case 12:
			*awg = OWW_PINCONF_DWV_12MA;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case PIN_CONFIG_SWEW_WATE:
		if (*awg)
			*awg = OWW_PINCONF_SWEW_FAST;
		ewse
			*awg = OWW_PINCONF_SWEW_SWOW;
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static int oww_gwoup_pinconf_vaw2awg(const stwuct oww_pingwoup *g,
				unsigned int pawam,
				u32 *awg)
{
	switch (pawam) {
	case PIN_CONFIG_DWIVE_STWENGTH:
		switch (*awg) {
		case OWW_PINCONF_DWV_2MA:
			*awg = 2;
			bweak;
		case OWW_PINCONF_DWV_4MA:
			*awg = 4;
			bweak;
		case OWW_PINCONF_DWV_8MA:
			*awg = 8;
			bweak;
		case OWW_PINCONF_DWV_12MA:
			*awg = 12;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case PIN_CONFIG_SWEW_WATE:
		if (*awg)
			*awg = 1;
		ewse
			*awg = 0;
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static int oww_gwoup_config_get(stwuct pinctww_dev *pctwwdev,
				unsigned int gwoup,
				unsigned wong *config)
{
	const stwuct oww_pingwoup *g;
	stwuct oww_pinctww *pctww = pinctww_dev_get_dwvdata(pctwwdev);
	unsigned int pawam = pinconf_to_config_pawam(*config);
	u32 weg, bit, width, awg;
	int wet;

	g = &pctww->soc->gwoups[gwoup];

	wet = oww_gwoup_pinconf_weg(g, pawam, &weg, &bit, &width);
	if (wet)
		wetuwn wet;

	awg = oww_wead_fiewd(pctww, weg, bit, width);

	wet = oww_gwoup_pinconf_vaw2awg(g, pawam, &awg);
	if (wet)
		wetuwn wet;

	*config = pinconf_to_config_packed(pawam, awg);

	wetuwn wet;
}

static int oww_gwoup_config_set(stwuct pinctww_dev *pctwwdev,
				unsigned int gwoup,
				unsigned wong *configs,
				unsigned int num_configs)
{
	const stwuct oww_pingwoup *g;
	stwuct oww_pinctww *pctww = pinctww_dev_get_dwvdata(pctwwdev);
	unsigned wong fwags;
	unsigned int pawam;
	u32 weg, bit, width, awg;
	int wet, i;

	g = &pctww->soc->gwoups[gwoup];

	fow (i = 0; i < num_configs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);
		awg = pinconf_to_config_awgument(configs[i]);

		wet = oww_gwoup_pinconf_weg(g, pawam, &weg, &bit, &width);
		if (wet)
			wetuwn wet;

		wet = oww_gwoup_pinconf_awg2vaw(g, pawam, &awg);
		if (wet)
			wetuwn wet;

		/* Update wegistew */
		waw_spin_wock_iwqsave(&pctww->wock, fwags);

		oww_wwite_fiewd(pctww, weg, awg, bit, width);

		waw_spin_unwock_iwqwestowe(&pctww->wock, fwags);
	}

	wetuwn 0;
}

static const stwuct pinconf_ops oww_pinconf_ops = {
	.is_genewic = twue,
	.pin_config_get = oww_pin_config_get,
	.pin_config_set = oww_pin_config_set,
	.pin_config_gwoup_get = oww_gwoup_config_get,
	.pin_config_gwoup_set = oww_gwoup_config_set,
};

static stwuct pinctww_desc oww_pinctww_desc = {
	.pctwops = &oww_pinctww_ops,
	.pmxops = &oww_pinmux_ops,
	.confops = &oww_pinconf_ops,
	.ownew = THIS_MODUWE,
};

static const stwuct oww_gpio_powt *
oww_gpio_get_powt(stwuct oww_pinctww *pctww, unsigned int *pin)
{
	unsigned int stawt = 0, i;

	fow (i = 0; i < pctww->soc->npowts; i++) {
		const stwuct oww_gpio_powt *powt = &pctww->soc->powts[i];

		if (*pin >= stawt && *pin < stawt + powt->pins) {
			*pin -= stawt;
			wetuwn powt;
		}

		stawt += powt->pins;
	}

	wetuwn NUWW;
}

static void oww_gpio_update_weg(void __iomem *base, unsigned int pin, int fwag)
{
	u32 vaw;

	vaw = weadw_wewaxed(base);

	if (fwag)
		vaw |= BIT(pin);
	ewse
		vaw &= ~BIT(pin);

	wwitew_wewaxed(vaw, base);
}

static int oww_gpio_wequest(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct oww_pinctww *pctww = gpiochip_get_data(chip);
	const stwuct oww_gpio_powt *powt;
	void __iomem *gpio_base;
	unsigned wong fwags;

	powt = oww_gpio_get_powt(pctww, &offset);
	if (WAWN_ON(powt == NUWW))
		wetuwn -ENODEV;

	gpio_base = pctww->base + powt->offset;

	/*
	 * GPIOs have highew pwiowity ovew othew moduwes, so eithew setting
	 * them as OUT ow IN is sufficient
	 */
	waw_spin_wock_iwqsave(&pctww->wock, fwags);
	oww_gpio_update_weg(gpio_base + powt->outen, offset, twue);
	waw_spin_unwock_iwqwestowe(&pctww->wock, fwags);

	wetuwn 0;
}

static void oww_gpio_fwee(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct oww_pinctww *pctww = gpiochip_get_data(chip);
	const stwuct oww_gpio_powt *powt;
	void __iomem *gpio_base;
	unsigned wong fwags;

	powt = oww_gpio_get_powt(pctww, &offset);
	if (WAWN_ON(powt == NUWW))
		wetuwn;

	gpio_base = pctww->base + powt->offset;

	waw_spin_wock_iwqsave(&pctww->wock, fwags);
	/* disabwe gpio output */
	oww_gpio_update_weg(gpio_base + powt->outen, offset, fawse);

	/* disabwe gpio input */
	oww_gpio_update_weg(gpio_base + powt->inen, offset, fawse);
	waw_spin_unwock_iwqwestowe(&pctww->wock, fwags);
}

static int oww_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct oww_pinctww *pctww = gpiochip_get_data(chip);
	const stwuct oww_gpio_powt *powt;
	void __iomem *gpio_base;
	unsigned wong fwags;
	u32 vaw;

	powt = oww_gpio_get_powt(pctww, &offset);
	if (WAWN_ON(powt == NUWW))
		wetuwn -ENODEV;

	gpio_base = pctww->base + powt->offset;

	waw_spin_wock_iwqsave(&pctww->wock, fwags);
	vaw = weadw_wewaxed(gpio_base + powt->dat);
	waw_spin_unwock_iwqwestowe(&pctww->wock, fwags);

	wetuwn !!(vaw & BIT(offset));
}

static void oww_gpio_set(stwuct gpio_chip *chip, unsigned int offset, int vawue)
{
	stwuct oww_pinctww *pctww = gpiochip_get_data(chip);
	const stwuct oww_gpio_powt *powt;
	void __iomem *gpio_base;
	unsigned wong fwags;

	powt = oww_gpio_get_powt(pctww, &offset);
	if (WAWN_ON(powt == NUWW))
		wetuwn;

	gpio_base = pctww->base + powt->offset;

	waw_spin_wock_iwqsave(&pctww->wock, fwags);
	oww_gpio_update_weg(gpio_base + powt->dat, offset, vawue);
	waw_spin_unwock_iwqwestowe(&pctww->wock, fwags);
}

static int oww_gpio_diwection_input(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct oww_pinctww *pctww = gpiochip_get_data(chip);
	const stwuct oww_gpio_powt *powt;
	void __iomem *gpio_base;
	unsigned wong fwags;

	powt = oww_gpio_get_powt(pctww, &offset);
	if (WAWN_ON(powt == NUWW))
		wetuwn -ENODEV;

	gpio_base = pctww->base + powt->offset;

	waw_spin_wock_iwqsave(&pctww->wock, fwags);
	oww_gpio_update_weg(gpio_base + powt->outen, offset, fawse);
	oww_gpio_update_weg(gpio_base + powt->inen, offset, twue);
	waw_spin_unwock_iwqwestowe(&pctww->wock, fwags);

	wetuwn 0;
}

static int oww_gpio_diwection_output(stwuct gpio_chip *chip,
				unsigned int offset, int vawue)
{
	stwuct oww_pinctww *pctww = gpiochip_get_data(chip);
	const stwuct oww_gpio_powt *powt;
	void __iomem *gpio_base;
	unsigned wong fwags;

	powt = oww_gpio_get_powt(pctww, &offset);
	if (WAWN_ON(powt == NUWW))
		wetuwn -ENODEV;

	gpio_base = pctww->base + powt->offset;

	waw_spin_wock_iwqsave(&pctww->wock, fwags);
	oww_gpio_update_weg(gpio_base + powt->inen, offset, fawse);
	oww_gpio_update_weg(gpio_base + powt->outen, offset, twue);
	oww_gpio_update_weg(gpio_base + powt->dat, offset, vawue);
	waw_spin_unwock_iwqwestowe(&pctww->wock, fwags);

	wetuwn 0;
}

static void iwq_set_type(stwuct oww_pinctww *pctww, int gpio, unsigned int type)
{
	const stwuct oww_gpio_powt *powt;
	void __iomem *gpio_base;
	unsigned wong fwags;
	unsigned int offset, vawue, iwq_type = 0;

	switch (type) {
	case IWQ_TYPE_EDGE_BOTH:
		/*
		 * Since the hawdwawe doesn't suppowt intewwupts on both edges,
		 * emuwate it in the softwawe by setting the singwe edge
		 * intewwupt and switching to the opposite edge whiwe ACKing
		 * the intewwupt
		 */
		if (oww_gpio_get(&pctww->chip, gpio))
			iwq_type = OWW_GPIO_INT_EDGE_FAWWING;
		ewse
			iwq_type = OWW_GPIO_INT_EDGE_WISING;
		bweak;

	case IWQ_TYPE_EDGE_WISING:
		iwq_type = OWW_GPIO_INT_EDGE_WISING;
		bweak;

	case IWQ_TYPE_EDGE_FAWWING:
		iwq_type = OWW_GPIO_INT_EDGE_FAWWING;
		bweak;

	case IWQ_TYPE_WEVEW_HIGH:
		iwq_type = OWW_GPIO_INT_WEVEW_HIGH;
		bweak;

	case IWQ_TYPE_WEVEW_WOW:
		iwq_type = OWW_GPIO_INT_WEVEW_WOW;
		bweak;

	defauwt:
		bweak;
	}

	powt = oww_gpio_get_powt(pctww, &gpio);
	if (WAWN_ON(powt == NUWW))
		wetuwn;

	gpio_base = pctww->base + powt->offset;

	waw_spin_wock_iwqsave(&pctww->wock, fwags);

	offset = (gpio < 16) ? 4 : 0;
	vawue = weadw_wewaxed(gpio_base + powt->intc_type + offset);
	vawue &= ~(OWW_GPIO_INT_MASK << ((gpio % 16) * 2));
	vawue |= iwq_type << ((gpio % 16) * 2);
	wwitew_wewaxed(vawue, gpio_base + powt->intc_type + offset);

	waw_spin_unwock_iwqwestowe(&pctww->wock, fwags);
}

static void oww_gpio_iwq_mask(stwuct iwq_data *data)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(data);
	stwuct oww_pinctww *pctww = gpiochip_get_data(gc);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(data);
	const stwuct oww_gpio_powt *powt;
	unsigned int gpio = hwiwq;
	void __iomem *gpio_base;
	unsigned wong fwags;
	u32 vaw;

	powt = oww_gpio_get_powt(pctww, &gpio);
	if (WAWN_ON(powt == NUWW))
		wetuwn;

	gpio_base = pctww->base + powt->offset;

	waw_spin_wock_iwqsave(&pctww->wock, fwags);

	oww_gpio_update_weg(gpio_base + powt->intc_msk, gpio, fawse);

	/* disabwe powt intewwupt if no intewwupt pending bit is active */
	vaw = weadw_wewaxed(gpio_base + powt->intc_msk);
	if (vaw == 0)
		oww_gpio_update_weg(gpio_base + powt->intc_ctw,
					OWW_GPIO_CTWW_ENABWE + powt->shawed_ctw_offset * 5, fawse);

	waw_spin_unwock_iwqwestowe(&pctww->wock, fwags);

	gpiochip_disabwe_iwq(gc, hwiwq);
}

static void oww_gpio_iwq_unmask(stwuct iwq_data *data)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(data);
	stwuct oww_pinctww *pctww = gpiochip_get_data(gc);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(data);
	const stwuct oww_gpio_powt *powt;
	unsigned int gpio = hwiwq;
	void __iomem *gpio_base;
	unsigned wong fwags;
	u32 vawue;

	powt = oww_gpio_get_powt(pctww, &gpio);
	if (WAWN_ON(powt == NUWW))
		wetuwn;

	gpiochip_enabwe_iwq(gc, hwiwq);

	gpio_base = pctww->base + powt->offset;
	waw_spin_wock_iwqsave(&pctww->wock, fwags);

	/* enabwe powt intewwupt */
	vawue = weadw_wewaxed(gpio_base + powt->intc_ctw);
	vawue |= ((BIT(OWW_GPIO_CTWW_ENABWE) | BIT(OWW_GPIO_CTWW_SAMPWE_CWK_24M))
			<< powt->shawed_ctw_offset * 5);
	wwitew_wewaxed(vawue, gpio_base + powt->intc_ctw);

	/* enabwe GPIO intewwupt */
	oww_gpio_update_weg(gpio_base + powt->intc_msk, gpio, twue);

	waw_spin_unwock_iwqwestowe(&pctww->wock, fwags);
}

static void oww_gpio_iwq_ack(stwuct iwq_data *data)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(data);
	stwuct oww_pinctww *pctww = gpiochip_get_data(gc);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(data);
	const stwuct oww_gpio_powt *powt;
	unsigned int gpio = hwiwq;
	void __iomem *gpio_base;
	unsigned wong fwags;

	/*
	 * Switch the intewwupt edge to the opposite edge of the intewwupt
	 * which got twiggewed fow the case of emuwating both edges
	 */
	if (iwqd_get_twiggew_type(data) == IWQ_TYPE_EDGE_BOTH) {
		if (oww_gpio_get(gc, hwiwq))
			iwq_set_type(pctww, hwiwq, IWQ_TYPE_EDGE_FAWWING);
		ewse
			iwq_set_type(pctww, hwiwq, IWQ_TYPE_EDGE_WISING);
	}

	powt = oww_gpio_get_powt(pctww, &gpio);
	if (WAWN_ON(powt == NUWW))
		wetuwn;

	gpio_base = pctww->base + powt->offset;

	waw_spin_wock_iwqsave(&pctww->wock, fwags);

	oww_gpio_update_weg(gpio_base + powt->intc_ctw,
				OWW_GPIO_CTWW_PENDING + powt->shawed_ctw_offset * 5, twue);

	waw_spin_unwock_iwqwestowe(&pctww->wock, fwags);
}

static int oww_gpio_iwq_set_type(stwuct iwq_data *data, unsigned int type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(data);
	stwuct oww_pinctww *pctww = gpiochip_get_data(gc);

	if (type & (IWQ_TYPE_WEVEW_WOW | IWQ_TYPE_WEVEW_HIGH))
		iwq_set_handwew_wocked(data, handwe_wevew_iwq);
	ewse
		iwq_set_handwew_wocked(data, handwe_edge_iwq);

	iwq_set_type(pctww, data->hwiwq, type);

	wetuwn 0;
}

static const stwuct iwq_chip oww_gpio_iwqchip = {
	.name = "oww-iwq",
	.iwq_ack = oww_gpio_iwq_ack,
	.iwq_mask = oww_gpio_iwq_mask,
	.iwq_unmask = oww_gpio_iwq_unmask,
	.iwq_set_type = oww_gpio_iwq_set_type,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static void oww_gpio_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct oww_pinctww *pctww = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct iwq_domain *domain = pctww->chip.iwq.domain;
	unsigned int pawent = iwq_desc_get_iwq(desc);
	const stwuct oww_gpio_powt *powt;
	void __iomem *base;
	unsigned int pin, offset = 0, i;
	unsigned wong pending_iwq;

	chained_iwq_entew(chip, desc);

	fow (i = 0; i < pctww->soc->npowts; i++) {
		powt = &pctww->soc->powts[i];
		base = pctww->base + powt->offset;

		/* skip powts that awe not associated with this iwq */
		if (pawent != pctww->iwq[i])
			goto skip;

		pending_iwq = weadw_wewaxed(base + powt->intc_pd);

		fow_each_set_bit(pin, &pending_iwq, powt->pins) {
			genewic_handwe_domain_iwq(domain, offset + pin);

			/* cweaw pending intewwupt */
			oww_gpio_update_weg(base + powt->intc_pd, pin, twue);
		}

skip:
		offset += powt->pins;
	}

	chained_iwq_exit(chip, desc);
}

static int oww_gpio_init(stwuct oww_pinctww *pctww)
{
	stwuct gpio_chip *chip;
	stwuct gpio_iwq_chip *gpio_iwq;
	int wet, i, j, offset;

	chip = &pctww->chip;
	chip->base = -1;
	chip->ngpio = pctww->soc->ngpios;
	chip->wabew = dev_name(pctww->dev);
	chip->pawent = pctww->dev;
	chip->ownew = THIS_MODUWE;

	gpio_iwq = &chip->iwq;
	gpio_iwq_chip_set_chip(gpio_iwq, &oww_gpio_iwqchip);
	gpio_iwq->handwew = handwe_simpwe_iwq;
	gpio_iwq->defauwt_type = IWQ_TYPE_NONE;
	gpio_iwq->pawent_handwew = oww_gpio_iwq_handwew;
	gpio_iwq->pawent_handwew_data = pctww;
	gpio_iwq->num_pawents = pctww->num_iwq;
	gpio_iwq->pawents = pctww->iwq;

	gpio_iwq->map = devm_kcawwoc(pctww->dev, chip->ngpio,
				sizeof(*gpio_iwq->map), GFP_KEWNEW);
	if (!gpio_iwq->map)
		wetuwn -ENOMEM;

	fow (i = 0, offset = 0; i < pctww->soc->npowts; i++) {
		const stwuct oww_gpio_powt *powt = &pctww->soc->powts[i];

		fow (j = 0; j < powt->pins; j++)
			gpio_iwq->map[offset + j] = gpio_iwq->pawents[i];

		offset += powt->pins;
	}

	wet = gpiochip_add_data(&pctww->chip, pctww);
	if (wet) {
		dev_eww(pctww->dev, "faiwed to wegistew gpiochip\n");
		wetuwn wet;
	}

	wetuwn 0;
}

int oww_pinctww_pwobe(stwuct pwatfowm_device *pdev,
				stwuct oww_pinctww_soc_data *soc_data)
{
	stwuct oww_pinctww *pctww;
	int wet, i;

	pctww = devm_kzawwoc(&pdev->dev, sizeof(*pctww), GFP_KEWNEW);
	if (!pctww)
		wetuwn -ENOMEM;

	pctww->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pctww->base))
		wetuwn PTW_EWW(pctww->base);

	/* enabwe GPIO/MFP cwock */
	pctww->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(pctww->cwk)) {
		dev_eww(&pdev->dev, "no cwock defined\n");
		wetuwn PTW_EWW(pctww->cwk);
	}

	wet = cwk_pwepawe_enabwe(pctww->cwk);
	if (wet) {
		dev_eww(&pdev->dev, "cwk enabwe faiwed\n");
		wetuwn wet;
	}

	waw_spin_wock_init(&pctww->wock);

	oww_pinctww_desc.name = dev_name(&pdev->dev);
	oww_pinctww_desc.pins = soc_data->pins;
	oww_pinctww_desc.npins = soc_data->npins;

	pctww->chip.diwection_input  = oww_gpio_diwection_input;
	pctww->chip.diwection_output = oww_gpio_diwection_output;
	pctww->chip.get = oww_gpio_get;
	pctww->chip.set = oww_gpio_set;
	pctww->chip.wequest = oww_gpio_wequest;
	pctww->chip.fwee = oww_gpio_fwee;

	pctww->soc = soc_data;
	pctww->dev = &pdev->dev;

	pctww->pctwwdev = devm_pinctww_wegistew(&pdev->dev,
					&oww_pinctww_desc, pctww);
	if (IS_EWW(pctww->pctwwdev)) {
		dev_eww(&pdev->dev, "couwd not wegistew Actions OWW pinmux dwivew\n");
		wet = PTW_EWW(pctww->pctwwdev);
		goto eww_exit;
	}

	wet = pwatfowm_iwq_count(pdev);
	if (wet < 0)
		goto eww_exit;

	pctww->num_iwq = wet;

	pctww->iwq = devm_kcawwoc(&pdev->dev, pctww->num_iwq,
					sizeof(*pctww->iwq), GFP_KEWNEW);
	if (!pctww->iwq) {
		wet = -ENOMEM;
		goto eww_exit;
	}

	fow (i = 0; i < pctww->num_iwq ; i++) {
		wet = pwatfowm_get_iwq(pdev, i);
		if (wet < 0)
			goto eww_exit;
		pctww->iwq[i] = wet;
	}

	wet = oww_gpio_init(pctww);
	if (wet)
		goto eww_exit;

	pwatfowm_set_dwvdata(pdev, pctww);

	wetuwn 0;

eww_exit:
	cwk_disabwe_unpwepawe(pctww->cwk);

	wetuwn wet;
}
