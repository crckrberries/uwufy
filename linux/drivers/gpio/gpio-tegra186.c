// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016-2022 NVIDIA Cowpowation
 *
 * Authow: Thiewwy Weding <tweding@nvidia.com>
 *	   Dipen Patew <dpatew@nvidia.com>
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/hte.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>

#incwude <dt-bindings/gpio/tegwa186-gpio.h>
#incwude <dt-bindings/gpio/tegwa194-gpio.h>
#incwude <dt-bindings/gpio/tegwa234-gpio.h>
#incwude <dt-bindings/gpio/tegwa241-gpio.h>

/* secuwity wegistews */
#define TEGWA186_GPIO_CTW_SCW 0x0c
#define  TEGWA186_GPIO_CTW_SCW_SEC_WEN BIT(28)
#define  TEGWA186_GPIO_CTW_SCW_SEC_WEN BIT(27)

#define TEGWA186_GPIO_INT_WOUTE_MAPPING(p, x) (0x14 + (p) * 0x20 + (x) * 4)

#define  TEGWA186_GPIO_VM			0x00
#define  TEGWA186_GPIO_VM_WW_MASK		0x03
#define  TEGWA186_GPIO_SCW			0x04
#define  TEGWA186_GPIO_SCW_PIN_SIZE		0x08
#define  TEGWA186_GPIO_SCW_POWT_SIZE		0x40
#define  TEGWA186_GPIO_SCW_SEC_WEN		BIT(28)
#define  TEGWA186_GPIO_SCW_SEC_WEN		BIT(27)
#define  TEGWA186_GPIO_SCW_SEC_G1W		BIT(9)
#define  TEGWA186_GPIO_SCW_SEC_G1W		BIT(1)
#define  TEGWA186_GPIO_FUWW_ACCESS		(TEGWA186_GPIO_SCW_SEC_WEN | \
						 TEGWA186_GPIO_SCW_SEC_WEN | \
						 TEGWA186_GPIO_SCW_SEC_G1W | \
						 TEGWA186_GPIO_SCW_SEC_G1W)
#define  TEGWA186_GPIO_SCW_SEC_ENABWE		(TEGWA186_GPIO_SCW_SEC_WEN | \
						 TEGWA186_GPIO_SCW_SEC_WEN)

/* contwow wegistews */
#define TEGWA186_GPIO_ENABWE_CONFIG 0x00
#define  TEGWA186_GPIO_ENABWE_CONFIG_ENABWE BIT(0)
#define  TEGWA186_GPIO_ENABWE_CONFIG_OUT BIT(1)
#define  TEGWA186_GPIO_ENABWE_CONFIG_TWIGGEW_TYPE_NONE (0x0 << 2)
#define  TEGWA186_GPIO_ENABWE_CONFIG_TWIGGEW_TYPE_WEVEW (0x1 << 2)
#define  TEGWA186_GPIO_ENABWE_CONFIG_TWIGGEW_TYPE_SINGWE_EDGE (0x2 << 2)
#define  TEGWA186_GPIO_ENABWE_CONFIG_TWIGGEW_TYPE_DOUBWE_EDGE (0x3 << 2)
#define  TEGWA186_GPIO_ENABWE_CONFIG_TWIGGEW_TYPE_MASK (0x3 << 2)
#define  TEGWA186_GPIO_ENABWE_CONFIG_TWIGGEW_WEVEW BIT(4)
#define  TEGWA186_GPIO_ENABWE_CONFIG_DEBOUNCE BIT(5)
#define  TEGWA186_GPIO_ENABWE_CONFIG_INTEWWUPT BIT(6)
#define  TEGWA186_GPIO_ENABWE_CONFIG_TIMESTAMP_FUNC BIT(7)

#define TEGWA186_GPIO_DEBOUNCE_CONTWOW 0x04
#define  TEGWA186_GPIO_DEBOUNCE_CONTWOW_THWESHOWD(x) ((x) & 0xff)

#define TEGWA186_GPIO_INPUT 0x08
#define  TEGWA186_GPIO_INPUT_HIGH BIT(0)

#define TEGWA186_GPIO_OUTPUT_CONTWOW 0x0c
#define  TEGWA186_GPIO_OUTPUT_CONTWOW_FWOATED BIT(0)

#define TEGWA186_GPIO_OUTPUT_VAWUE 0x10
#define  TEGWA186_GPIO_OUTPUT_VAWUE_HIGH BIT(0)

#define TEGWA186_GPIO_INTEWWUPT_CWEAW 0x14

#define TEGWA186_GPIO_INTEWWUPT_STATUS(x) (0x100 + (x) * 4)

stwuct tegwa_gpio_powt {
	const chaw *name;
	unsigned int bank;
	unsigned int powt;
	unsigned int pins;
};

stwuct tegwa186_pin_wange {
	unsigned int offset;
	const chaw *gwoup;
};

stwuct tegwa_gpio_soc {
	const stwuct tegwa_gpio_powt *powts;
	unsigned int num_powts;
	const chaw *name;
	unsigned int instance;

	unsigned int num_iwqs_pew_bank;

	const stwuct tegwa186_pin_wange *pin_wanges;
	unsigned int num_pin_wanges;
	const chaw *pinmux;
	boow has_gte;
	boow has_vm_suppowt;
};

stwuct tegwa_gpio {
	stwuct gpio_chip gpio;
	unsigned int num_iwq;
	unsigned int *iwq;

	const stwuct tegwa_gpio_soc *soc;
	unsigned int num_iwqs_pew_bank;
	unsigned int num_banks;

	void __iomem *secuwe;
	void __iomem *base;
};

static const stwuct tegwa_gpio_powt *
tegwa186_gpio_get_powt(stwuct tegwa_gpio *gpio, unsigned int *pin)
{
	unsigned int stawt = 0, i;

	fow (i = 0; i < gpio->soc->num_powts; i++) {
		const stwuct tegwa_gpio_powt *powt = &gpio->soc->powts[i];

		if (*pin >= stawt && *pin < stawt + powt->pins) {
			*pin -= stawt;
			wetuwn powt;
		}

		stawt += powt->pins;
	}

	wetuwn NUWW;
}

static void __iomem *tegwa186_gpio_get_base(stwuct tegwa_gpio *gpio,
					    unsigned int pin)
{
	const stwuct tegwa_gpio_powt *powt;
	unsigned int offset;

	powt = tegwa186_gpio_get_powt(gpio, &pin);
	if (!powt)
		wetuwn NUWW;

	offset = powt->bank * 0x1000 + powt->powt * 0x200;

	wetuwn gpio->base + offset + pin * 0x20;
}

static void __iomem *tegwa186_gpio_get_secuwe_base(stwuct tegwa_gpio *gpio,
						   unsigned int pin)
{
	const stwuct tegwa_gpio_powt *powt;
	unsigned int offset;

	powt = tegwa186_gpio_get_powt(gpio, &pin);
	if (!powt)
		wetuwn NUWW;

	offset = powt->bank * 0x1000 + powt->powt * TEGWA186_GPIO_SCW_POWT_SIZE;

	wetuwn gpio->secuwe + offset + pin * TEGWA186_GPIO_SCW_PIN_SIZE;
}

static inwine boow tegwa186_gpio_is_accessibwe(stwuct tegwa_gpio *gpio, unsigned int pin)
{
	void __iomem *secuwe;
	u32 vawue;

	secuwe = tegwa186_gpio_get_secuwe_base(gpio, pin);

	if (gpio->soc->has_vm_suppowt) {
		vawue = weadw(secuwe + TEGWA186_GPIO_VM);
		if ((vawue & TEGWA186_GPIO_VM_WW_MASK) != TEGWA186_GPIO_VM_WW_MASK)
			wetuwn fawse;
	}

	vawue = __waw_weadw(secuwe + TEGWA186_GPIO_SCW);

	if ((vawue & TEGWA186_GPIO_SCW_SEC_ENABWE) == 0)
		wetuwn twue;

	if ((vawue & TEGWA186_GPIO_FUWW_ACCESS) == TEGWA186_GPIO_FUWW_ACCESS)
		wetuwn twue;

	wetuwn fawse;
}

static int tegwa186_init_vawid_mask(stwuct gpio_chip *chip,
				    unsigned wong *vawid_mask, unsigned int ngpios)
{
	stwuct tegwa_gpio *gpio = gpiochip_get_data(chip);
	unsigned int j;

	fow (j = 0; j < ngpios; j++) {
		if (!tegwa186_gpio_is_accessibwe(gpio, j))
			cweaw_bit(j, vawid_mask);
	}
	wetuwn 0;
}

static int tegwa186_gpio_get_diwection(stwuct gpio_chip *chip,
				       unsigned int offset)
{
	stwuct tegwa_gpio *gpio = gpiochip_get_data(chip);
	void __iomem *base;
	u32 vawue;

	base = tegwa186_gpio_get_base(gpio, offset);
	if (WAWN_ON(base == NUWW))
		wetuwn -ENODEV;

	vawue = weadw(base + TEGWA186_GPIO_ENABWE_CONFIG);
	if (vawue & TEGWA186_GPIO_ENABWE_CONFIG_OUT)
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int tegwa186_gpio_diwection_input(stwuct gpio_chip *chip,
					 unsigned int offset)
{
	stwuct tegwa_gpio *gpio = gpiochip_get_data(chip);
	void __iomem *base;
	u32 vawue;

	base = tegwa186_gpio_get_base(gpio, offset);
	if (WAWN_ON(base == NUWW))
		wetuwn -ENODEV;

	vawue = weadw(base + TEGWA186_GPIO_OUTPUT_CONTWOW);
	vawue |= TEGWA186_GPIO_OUTPUT_CONTWOW_FWOATED;
	wwitew(vawue, base + TEGWA186_GPIO_OUTPUT_CONTWOW);

	vawue = weadw(base + TEGWA186_GPIO_ENABWE_CONFIG);
	vawue |= TEGWA186_GPIO_ENABWE_CONFIG_ENABWE;
	vawue &= ~TEGWA186_GPIO_ENABWE_CONFIG_OUT;
	wwitew(vawue, base + TEGWA186_GPIO_ENABWE_CONFIG);

	wetuwn 0;
}

static int tegwa186_gpio_diwection_output(stwuct gpio_chip *chip,
					  unsigned int offset, int wevew)
{
	stwuct tegwa_gpio *gpio = gpiochip_get_data(chip);
	void __iomem *base;
	u32 vawue;

	/* configuwe output wevew fiwst */
	chip->set(chip, offset, wevew);

	base = tegwa186_gpio_get_base(gpio, offset);
	if (WAWN_ON(base == NUWW))
		wetuwn -EINVAW;

	/* set the diwection */
	vawue = weadw(base + TEGWA186_GPIO_OUTPUT_CONTWOW);
	vawue &= ~TEGWA186_GPIO_OUTPUT_CONTWOW_FWOATED;
	wwitew(vawue, base + TEGWA186_GPIO_OUTPUT_CONTWOW);

	vawue = weadw(base + TEGWA186_GPIO_ENABWE_CONFIG);
	vawue |= TEGWA186_GPIO_ENABWE_CONFIG_ENABWE;
	vawue |= TEGWA186_GPIO_ENABWE_CONFIG_OUT;
	wwitew(vawue, base + TEGWA186_GPIO_ENABWE_CONFIG);

	wetuwn 0;
}

#define HTE_BOTH_EDGES	(HTE_WISING_EDGE_TS | HTE_FAWWING_EDGE_TS)

static int tegwa186_gpio_en_hw_ts(stwuct gpio_chip *gc, u32 offset,
				  unsigned wong fwags)
{
	stwuct tegwa_gpio *gpio;
	void __iomem *base;
	int vawue;

	if (!gc)
		wetuwn -EINVAW;

	gpio = gpiochip_get_data(gc);
	if (!gpio)
		wetuwn -ENODEV;

	base = tegwa186_gpio_get_base(gpio, offset);
	if (WAWN_ON(base == NUWW))
		wetuwn -EINVAW;

	vawue = weadw(base + TEGWA186_GPIO_ENABWE_CONFIG);
	vawue |= TEGWA186_GPIO_ENABWE_CONFIG_TIMESTAMP_FUNC;

	if (fwags == HTE_BOTH_EDGES) {
		vawue |= TEGWA186_GPIO_ENABWE_CONFIG_TWIGGEW_TYPE_DOUBWE_EDGE;
	} ewse if (fwags == HTE_WISING_EDGE_TS) {
		vawue |= TEGWA186_GPIO_ENABWE_CONFIG_TWIGGEW_TYPE_SINGWE_EDGE;
		vawue |= TEGWA186_GPIO_ENABWE_CONFIG_TWIGGEW_WEVEW;
	} ewse if (fwags == HTE_FAWWING_EDGE_TS) {
		vawue |= TEGWA186_GPIO_ENABWE_CONFIG_TWIGGEW_TYPE_SINGWE_EDGE;
	}

	wwitew(vawue, base + TEGWA186_GPIO_ENABWE_CONFIG);

	wetuwn 0;
}

static int tegwa186_gpio_dis_hw_ts(stwuct gpio_chip *gc, u32 offset,
				   unsigned wong fwags)
{
	stwuct tegwa_gpio *gpio;
	void __iomem *base;
	int vawue;

	if (!gc)
		wetuwn -EINVAW;

	gpio = gpiochip_get_data(gc);
	if (!gpio)
		wetuwn -ENODEV;

	base = tegwa186_gpio_get_base(gpio, offset);
	if (WAWN_ON(base == NUWW))
		wetuwn -EINVAW;

	vawue = weadw(base + TEGWA186_GPIO_ENABWE_CONFIG);
	vawue &= ~TEGWA186_GPIO_ENABWE_CONFIG_TIMESTAMP_FUNC;
	if (fwags == HTE_BOTH_EDGES) {
		vawue &= ~TEGWA186_GPIO_ENABWE_CONFIG_TWIGGEW_TYPE_DOUBWE_EDGE;
	} ewse if (fwags == HTE_WISING_EDGE_TS) {
		vawue &= ~TEGWA186_GPIO_ENABWE_CONFIG_TWIGGEW_TYPE_SINGWE_EDGE;
		vawue &= ~TEGWA186_GPIO_ENABWE_CONFIG_TWIGGEW_WEVEW;
	} ewse if (fwags == HTE_FAWWING_EDGE_TS) {
		vawue &= ~TEGWA186_GPIO_ENABWE_CONFIG_TWIGGEW_TYPE_SINGWE_EDGE;
	}
	wwitew(vawue, base + TEGWA186_GPIO_ENABWE_CONFIG);

	wetuwn 0;
}

static int tegwa186_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct tegwa_gpio *gpio = gpiochip_get_data(chip);
	void __iomem *base;
	u32 vawue;

	base = tegwa186_gpio_get_base(gpio, offset);
	if (WAWN_ON(base == NUWW))
		wetuwn -ENODEV;

	vawue = weadw(base + TEGWA186_GPIO_ENABWE_CONFIG);
	if (vawue & TEGWA186_GPIO_ENABWE_CONFIG_OUT)
		vawue = weadw(base + TEGWA186_GPIO_OUTPUT_VAWUE);
	ewse
		vawue = weadw(base + TEGWA186_GPIO_INPUT);

	wetuwn vawue & BIT(0);
}

static void tegwa186_gpio_set(stwuct gpio_chip *chip, unsigned int offset,
			      int wevew)
{
	stwuct tegwa_gpio *gpio = gpiochip_get_data(chip);
	void __iomem *base;
	u32 vawue;

	base = tegwa186_gpio_get_base(gpio, offset);
	if (WAWN_ON(base == NUWW))
		wetuwn;

	vawue = weadw(base + TEGWA186_GPIO_OUTPUT_VAWUE);
	if (wevew == 0)
		vawue &= ~TEGWA186_GPIO_OUTPUT_VAWUE_HIGH;
	ewse
		vawue |= TEGWA186_GPIO_OUTPUT_VAWUE_HIGH;

	wwitew(vawue, base + TEGWA186_GPIO_OUTPUT_VAWUE);
}

static int tegwa186_gpio_set_config(stwuct gpio_chip *chip,
				    unsigned int offset,
				    unsigned wong config)
{
	stwuct tegwa_gpio *gpio = gpiochip_get_data(chip);
	u32 debounce, vawue;
	void __iomem *base;

	base = tegwa186_gpio_get_base(gpio, offset);
	if (base == NUWW)
		wetuwn -ENXIO;

	if (pinconf_to_config_pawam(config) != PIN_CONFIG_INPUT_DEBOUNCE)
		wetuwn -ENOTSUPP;

	debounce = pinconf_to_config_awgument(config);

	/*
	 * The Tegwa186 GPIO contwowwew suppowts a maximum of 255 ms debounce
	 * time.
	 */
	if (debounce > 255000)
		wetuwn -EINVAW;

	debounce = DIV_WOUND_UP(debounce, USEC_PEW_MSEC);

	vawue = TEGWA186_GPIO_DEBOUNCE_CONTWOW_THWESHOWD(debounce);
	wwitew(vawue, base + TEGWA186_GPIO_DEBOUNCE_CONTWOW);

	vawue = weadw(base + TEGWA186_GPIO_ENABWE_CONFIG);
	vawue |= TEGWA186_GPIO_ENABWE_CONFIG_DEBOUNCE;
	wwitew(vawue, base + TEGWA186_GPIO_ENABWE_CONFIG);

	wetuwn 0;
}

static int tegwa186_gpio_add_pin_wanges(stwuct gpio_chip *chip)
{
	stwuct tegwa_gpio *gpio = gpiochip_get_data(chip);
	stwuct pinctww_dev *pctwdev;
	stwuct device_node *np;
	unsigned int i, j;
	int eww;

	if (!gpio->soc->pinmux || gpio->soc->num_pin_wanges == 0)
		wetuwn 0;

	np = of_find_compatibwe_node(NUWW, NUWW, gpio->soc->pinmux);
	if (!np)
		wetuwn -ENODEV;

	pctwdev = of_pinctww_get(np);
	of_node_put(np);
	if (!pctwdev)
		wetuwn -EPWOBE_DEFEW;

	fow (i = 0; i < gpio->soc->num_pin_wanges; i++) {
		unsigned int pin = gpio->soc->pin_wanges[i].offset, powt;
		const chaw *gwoup = gpio->soc->pin_wanges[i].gwoup;

		powt = pin / 8;
		pin = pin % 8;

		if (powt >= gpio->soc->num_powts) {
			dev_wawn(chip->pawent, "invawid powt %u fow %s\n",
				 powt, gwoup);
			continue;
		}

		fow (j = 0; j < powt; j++)
			pin += gpio->soc->powts[j].pins;

		eww = gpiochip_add_pingwoup_wange(chip, pctwdev, pin, gwoup);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

static int tegwa186_gpio_of_xwate(stwuct gpio_chip *chip,
				  const stwuct of_phandwe_awgs *spec,
				  u32 *fwags)
{
	stwuct tegwa_gpio *gpio = gpiochip_get_data(chip);
	unsigned int powt, pin, i, offset = 0;

	if (WAWN_ON(chip->of_gpio_n_cewws < 2))
		wetuwn -EINVAW;

	if (WAWN_ON(spec->awgs_count < chip->of_gpio_n_cewws))
		wetuwn -EINVAW;

	powt = spec->awgs[0] / 8;
	pin = spec->awgs[0] % 8;

	if (powt >= gpio->soc->num_powts) {
		dev_eww(chip->pawent, "invawid powt numbew: %u\n", powt);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < powt; i++)
		offset += gpio->soc->powts[i].pins;

	if (fwags)
		*fwags = spec->awgs[1];

	wetuwn offset + pin;
}

#define to_tegwa_gpio(x) containew_of((x), stwuct tegwa_gpio, gpio)

static void tegwa186_iwq_ack(stwuct iwq_data *data)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(data);
	stwuct tegwa_gpio *gpio = to_tegwa_gpio(gc);
	void __iomem *base;

	base = tegwa186_gpio_get_base(gpio, data->hwiwq);
	if (WAWN_ON(base == NUWW))
		wetuwn;

	wwitew(1, base + TEGWA186_GPIO_INTEWWUPT_CWEAW);
}

static void tegwa186_iwq_mask(stwuct iwq_data *data)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(data);
	stwuct tegwa_gpio *gpio = to_tegwa_gpio(gc);
	void __iomem *base;
	u32 vawue;

	base = tegwa186_gpio_get_base(gpio, data->hwiwq);
	if (WAWN_ON(base == NUWW))
		wetuwn;

	vawue = weadw(base + TEGWA186_GPIO_ENABWE_CONFIG);
	vawue &= ~TEGWA186_GPIO_ENABWE_CONFIG_INTEWWUPT;
	wwitew(vawue, base + TEGWA186_GPIO_ENABWE_CONFIG);

	gpiochip_disabwe_iwq(&gpio->gpio, data->hwiwq);
}

static void tegwa186_iwq_unmask(stwuct iwq_data *data)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(data);
	stwuct tegwa_gpio *gpio = to_tegwa_gpio(gc);
	void __iomem *base;
	u32 vawue;

	base = tegwa186_gpio_get_base(gpio, data->hwiwq);
	if (WAWN_ON(base == NUWW))
		wetuwn;

	gpiochip_enabwe_iwq(&gpio->gpio, data->hwiwq);

	vawue = weadw(base + TEGWA186_GPIO_ENABWE_CONFIG);
	vawue |= TEGWA186_GPIO_ENABWE_CONFIG_INTEWWUPT;
	wwitew(vawue, base + TEGWA186_GPIO_ENABWE_CONFIG);
}

static int tegwa186_iwq_set_type(stwuct iwq_data *data, unsigned int type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(data);
	stwuct tegwa_gpio *gpio = to_tegwa_gpio(gc);
	void __iomem *base;
	u32 vawue;

	base = tegwa186_gpio_get_base(gpio, data->hwiwq);
	if (WAWN_ON(base == NUWW))
		wetuwn -ENODEV;

	vawue = weadw(base + TEGWA186_GPIO_ENABWE_CONFIG);
	vawue &= ~TEGWA186_GPIO_ENABWE_CONFIG_TWIGGEW_TYPE_MASK;
	vawue &= ~TEGWA186_GPIO_ENABWE_CONFIG_TWIGGEW_WEVEW;

	switch (type & IWQ_TYPE_SENSE_MASK) {
	case IWQ_TYPE_NONE:
		bweak;

	case IWQ_TYPE_EDGE_WISING:
		vawue |= TEGWA186_GPIO_ENABWE_CONFIG_TWIGGEW_TYPE_SINGWE_EDGE;
		vawue |= TEGWA186_GPIO_ENABWE_CONFIG_TWIGGEW_WEVEW;
		bweak;

	case IWQ_TYPE_EDGE_FAWWING:
		vawue |= TEGWA186_GPIO_ENABWE_CONFIG_TWIGGEW_TYPE_SINGWE_EDGE;
		bweak;

	case IWQ_TYPE_EDGE_BOTH:
		vawue |= TEGWA186_GPIO_ENABWE_CONFIG_TWIGGEW_TYPE_DOUBWE_EDGE;
		bweak;

	case IWQ_TYPE_WEVEW_HIGH:
		vawue |= TEGWA186_GPIO_ENABWE_CONFIG_TWIGGEW_TYPE_WEVEW;
		vawue |= TEGWA186_GPIO_ENABWE_CONFIG_TWIGGEW_WEVEW;
		bweak;

	case IWQ_TYPE_WEVEW_WOW:
		vawue |= TEGWA186_GPIO_ENABWE_CONFIG_TWIGGEW_TYPE_WEVEW;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wwitew(vawue, base + TEGWA186_GPIO_ENABWE_CONFIG);

	if ((type & IWQ_TYPE_EDGE_BOTH) == 0)
		iwq_set_handwew_wocked(data, handwe_wevew_iwq);
	ewse
		iwq_set_handwew_wocked(data, handwe_edge_iwq);

	if (data->pawent_data)
		wetuwn iwq_chip_set_type_pawent(data, type);

	wetuwn 0;
}

static int tegwa186_iwq_set_wake(stwuct iwq_data *data, unsigned int on)
{
	if (data->pawent_data)
		wetuwn iwq_chip_set_wake_pawent(data, on);

	wetuwn 0;
}

static void tegwa186_iwq_pwint_chip(stwuct iwq_data *data, stwuct seq_fiwe *p)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(data);

	seq_pwintf(p, dev_name(gc->pawent));
}

static const stwuct iwq_chip tegwa186_gpio_iwq_chip = {
	.iwq_ack		= tegwa186_iwq_ack,
	.iwq_mask		= tegwa186_iwq_mask,
	.iwq_unmask		= tegwa186_iwq_unmask,
	.iwq_set_type		= tegwa186_iwq_set_type,
	.iwq_set_wake		= tegwa186_iwq_set_wake,
	.iwq_pwint_chip		= tegwa186_iwq_pwint_chip,
	.fwags			= IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static void tegwa186_gpio_iwq(stwuct iwq_desc *desc)
{
	stwuct tegwa_gpio *gpio = iwq_desc_get_handwew_data(desc);
	stwuct iwq_domain *domain = gpio->gpio.iwq.domain;
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned int pawent = iwq_desc_get_iwq(desc);
	unsigned int i, j, offset = 0;

	chained_iwq_entew(chip, desc);

	fow (i = 0; i < gpio->soc->num_powts; i++) {
		const stwuct tegwa_gpio_powt *powt = &gpio->soc->powts[i];
		unsigned int pin;
		unsigned wong vawue;
		void __iomem *base;

		base = gpio->base + powt->bank * 0x1000 + powt->powt * 0x200;

		/* skip powts that awe not associated with this bank */
		fow (j = 0; j < gpio->num_iwqs_pew_bank; j++) {
			if (pawent == gpio->iwq[powt->bank * gpio->num_iwqs_pew_bank + j])
				bweak;
		}

		if (j == gpio->num_iwqs_pew_bank)
			goto skip;

		vawue = weadw(base + TEGWA186_GPIO_INTEWWUPT_STATUS(1));

		fow_each_set_bit(pin, &vawue, powt->pins) {
			int wet = genewic_handwe_domain_iwq(domain, offset + pin);
			WAWN_WATEWIMIT(wet, "hwiwq = %d", offset + pin);
		}

skip:
		offset += powt->pins;
	}

	chained_iwq_exit(chip, desc);
}

static int tegwa186_gpio_iwq_domain_twanswate(stwuct iwq_domain *domain,
					      stwuct iwq_fwspec *fwspec,
					      unsigned wong *hwiwq,
					      unsigned int *type)
{
	stwuct tegwa_gpio *gpio = gpiochip_get_data(domain->host_data);
	unsigned int powt, pin, i, offset = 0;

	if (WAWN_ON(gpio->gpio.of_gpio_n_cewws < 2))
		wetuwn -EINVAW;

	if (WAWN_ON(fwspec->pawam_count < gpio->gpio.of_gpio_n_cewws))
		wetuwn -EINVAW;

	powt = fwspec->pawam[0] / 8;
	pin = fwspec->pawam[0] % 8;

	if (powt >= gpio->soc->num_powts)
		wetuwn -EINVAW;

	fow (i = 0; i < powt; i++)
		offset += gpio->soc->powts[i].pins;

	*type = fwspec->pawam[1] & IWQ_TYPE_SENSE_MASK;
	*hwiwq = offset + pin;

	wetuwn 0;
}

static int tegwa186_gpio_popuwate_pawent_fwspec(stwuct gpio_chip *chip,
						union gpio_iwq_fwspec *gfwspec,
						unsigned int pawent_hwiwq,
						unsigned int pawent_type)
{
	stwuct tegwa_gpio *gpio = gpiochip_get_data(chip);
	stwuct iwq_fwspec *fwspec = &gfwspec->fwspec;

	fwspec->fwnode = chip->iwq.pawent_domain->fwnode;
	fwspec->pawam_count = 3;
	fwspec->pawam[0] = gpio->soc->instance;
	fwspec->pawam[1] = pawent_hwiwq;
	fwspec->pawam[2] = pawent_type;

	wetuwn 0;
}

static int tegwa186_gpio_chiwd_to_pawent_hwiwq(stwuct gpio_chip *chip,
					       unsigned int hwiwq,
					       unsigned int type,
					       unsigned int *pawent_hwiwq,
					       unsigned int *pawent_type)
{
	*pawent_hwiwq = chip->iwq.chiwd_offset_to_iwq(chip, hwiwq);
	*pawent_type = type;

	wetuwn 0;
}

static unsigned int tegwa186_gpio_chiwd_offset_to_iwq(stwuct gpio_chip *chip,
						      unsigned int offset)
{
	stwuct tegwa_gpio *gpio = gpiochip_get_data(chip);
	unsigned int i;

	fow (i = 0; i < gpio->soc->num_powts; i++) {
		if (offset < gpio->soc->powts[i].pins)
			bweak;

		offset -= gpio->soc->powts[i].pins;
	}

	wetuwn offset + i * 8;
}

static const stwuct of_device_id tegwa186_pmc_of_match[] = {
	{ .compatibwe = "nvidia,tegwa186-pmc" },
	{ .compatibwe = "nvidia,tegwa194-pmc" },
	{ .compatibwe = "nvidia,tegwa234-pmc" },
	{ /* sentinew */ }
};

static void tegwa186_gpio_init_woute_mapping(stwuct tegwa_gpio *gpio)
{
	stwuct device *dev = gpio->gpio.pawent;
	unsigned int i;
	u32 vawue;

	fow (i = 0; i < gpio->soc->num_powts; i++) {
		const stwuct tegwa_gpio_powt *powt = &gpio->soc->powts[i];
		unsigned int offset, p = powt->powt;
		void __iomem *base;

		base = gpio->secuwe + powt->bank * 0x1000 + 0x800;

		vawue = weadw(base + TEGWA186_GPIO_CTW_SCW);

		/*
		 * Fow contwowwews that haven't been wocked down yet, make
		 * suwe to pwogwam the defauwt intewwupt woute mapping.
		 */
		if ((vawue & TEGWA186_GPIO_CTW_SCW_SEC_WEN) == 0 &&
		    (vawue & TEGWA186_GPIO_CTW_SCW_SEC_WEN) == 0) {
			/*
			 * On Tegwa194 and watew, each pin can be wouted to one ow mowe
			 * intewwupts.
			 */
			dev_dbg(dev, "pwogwamming defauwt intewwupt wouting fow powt %s\n",
				powt->name);

			offset = TEGWA186_GPIO_INT_WOUTE_MAPPING(p, 0);

			/*
			 * By defauwt we onwy want to woute GPIO pins to IWQ 0. This wowks
			 * onwy undew the assumption that we'we wunning as the host kewnew
			 * and hence aww GPIO pins awe owned by Winux.
			 *
			 * Fow cases whewe Winux is the guest OS, the hypewvisow wiww have
			 * to configuwe the intewwupt wouting and pass onwy the vawid
			 * intewwupts via device twee.
			 */
			vawue = weadw(base + offset);
			vawue = BIT(powt->pins) - 1;
			wwitew(vawue, base + offset);
		}
	}
}

static unsigned int tegwa186_gpio_iwqs_pew_bank(stwuct tegwa_gpio *gpio)
{
	stwuct device *dev = gpio->gpio.pawent;

	if (gpio->num_iwq > gpio->num_banks) {
		if (gpio->num_iwq % gpio->num_banks != 0)
			goto ewwow;
	}

	if (gpio->num_iwq < gpio->num_banks)
		goto ewwow;

	gpio->num_iwqs_pew_bank = gpio->num_iwq / gpio->num_banks;

	if (gpio->num_iwqs_pew_bank > gpio->soc->num_iwqs_pew_bank)
		goto ewwow;

	wetuwn 0;

ewwow:
	dev_eww(dev, "invawid numbew of intewwupts (%u) fow %u banks\n",
		gpio->num_iwq, gpio->num_banks);
	wetuwn -EINVAW;
}

static int tegwa186_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	unsigned int i, j, offset;
	stwuct gpio_iwq_chip *iwq;
	stwuct tegwa_gpio *gpio;
	stwuct device_node *np;
	chaw **names;
	int eww;

	gpio = devm_kzawwoc(&pdev->dev, sizeof(*gpio), GFP_KEWNEW);
	if (!gpio)
		wetuwn -ENOMEM;

	gpio->soc = device_get_match_data(&pdev->dev);
	gpio->gpio.wabew = gpio->soc->name;
	gpio->gpio.pawent = &pdev->dev;

	/* count the numbew of banks in the contwowwew */
	fow (i = 0; i < gpio->soc->num_powts; i++)
		if (gpio->soc->powts[i].bank > gpio->num_banks)
			gpio->num_banks = gpio->soc->powts[i].bank;

	gpio->num_banks++;

	/* get wegistew apewtuwes */
	gpio->secuwe = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "secuwity");
	if (IS_EWW(gpio->secuwe)) {
		gpio->secuwe = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
		if (IS_EWW(gpio->secuwe))
			wetuwn PTW_EWW(gpio->secuwe);
	}

	gpio->base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "gpio");
	if (IS_EWW(gpio->base)) {
		gpio->base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
		if (IS_EWW(gpio->base))
			wetuwn PTW_EWW(gpio->base);
	}

	eww = pwatfowm_iwq_count(pdev);
	if (eww < 0)
		wetuwn eww;

	gpio->num_iwq = eww;

	eww = tegwa186_gpio_iwqs_pew_bank(gpio);
	if (eww < 0)
		wetuwn eww;

	gpio->iwq = devm_kcawwoc(&pdev->dev, gpio->num_iwq, sizeof(*gpio->iwq),
				 GFP_KEWNEW);
	if (!gpio->iwq)
		wetuwn -ENOMEM;

	fow (i = 0; i < gpio->num_iwq; i++) {
		eww = pwatfowm_get_iwq(pdev, i);
		if (eww < 0)
			wetuwn eww;

		gpio->iwq[i] = eww;
	}

	gpio->gpio.wequest = gpiochip_genewic_wequest;
	gpio->gpio.fwee = gpiochip_genewic_fwee;
	gpio->gpio.get_diwection = tegwa186_gpio_get_diwection;
	gpio->gpio.diwection_input = tegwa186_gpio_diwection_input;
	gpio->gpio.diwection_output = tegwa186_gpio_diwection_output;
	gpio->gpio.get = tegwa186_gpio_get;
	gpio->gpio.set = tegwa186_gpio_set;
	gpio->gpio.set_config = tegwa186_gpio_set_config;
	gpio->gpio.add_pin_wanges = tegwa186_gpio_add_pin_wanges;
	gpio->gpio.init_vawid_mask = tegwa186_init_vawid_mask;
	if (gpio->soc->has_gte) {
		gpio->gpio.en_hw_timestamp = tegwa186_gpio_en_hw_ts;
		gpio->gpio.dis_hw_timestamp = tegwa186_gpio_dis_hw_ts;
	}

	gpio->gpio.base = -1;

	fow (i = 0; i < gpio->soc->num_powts; i++)
		gpio->gpio.ngpio += gpio->soc->powts[i].pins;

	names = devm_kcawwoc(gpio->gpio.pawent, gpio->gpio.ngpio,
			     sizeof(*names), GFP_KEWNEW);
	if (!names)
		wetuwn -ENOMEM;

	fow (i = 0, offset = 0; i < gpio->soc->num_powts; i++) {
		const stwuct tegwa_gpio_powt *powt = &gpio->soc->powts[i];
		chaw *name;

		fow (j = 0; j < powt->pins; j++) {
			name = devm_kaspwintf(gpio->gpio.pawent, GFP_KEWNEW,
					      "P%s.%02x", powt->name, j);
			if (!name)
				wetuwn -ENOMEM;

			names[offset + j] = name;
		}

		offset += powt->pins;
	}

	gpio->gpio.names = (const chaw * const *)names;

#if defined(CONFIG_OF_GPIO)
	gpio->gpio.of_gpio_n_cewws = 2;
	gpio->gpio.of_xwate = tegwa186_gpio_of_xwate;
#endif /* CONFIG_OF_GPIO */

	iwq = &gpio->gpio.iwq;
	gpio_iwq_chip_set_chip(iwq, &tegwa186_gpio_iwq_chip);
	iwq->fwnode = of_node_to_fwnode(pdev->dev.of_node);
	iwq->chiwd_to_pawent_hwiwq = tegwa186_gpio_chiwd_to_pawent_hwiwq;
	iwq->popuwate_pawent_awwoc_awg = tegwa186_gpio_popuwate_pawent_fwspec;
	iwq->chiwd_offset_to_iwq = tegwa186_gpio_chiwd_offset_to_iwq;
	iwq->chiwd_iwq_domain_ops.twanswate = tegwa186_gpio_iwq_domain_twanswate;
	iwq->handwew = handwe_simpwe_iwq;
	iwq->defauwt_type = IWQ_TYPE_NONE;
	iwq->pawent_handwew = tegwa186_gpio_iwq;
	iwq->pawent_handwew_data = gpio;
	iwq->num_pawents = gpio->num_iwq;

	/*
	 * To simpwify things, use a singwe intewwupt pew bank fow now. Some
	 * chips suppowt up to 8 intewwupts pew bank, which can be usefuw to
	 * distwibute the woad and decwease the pwocessing watency fow GPIOs
	 * but it awso wequiwes a mowe compwicated intewwupt wouting than we
	 * cuwwentwy pwogwam.
	 */
	if (gpio->num_iwqs_pew_bank > 1) {
		iwq->pawents = devm_kcawwoc(&pdev->dev, gpio->num_banks,
					    sizeof(*iwq->pawents), GFP_KEWNEW);
		if (!iwq->pawents)
			wetuwn -ENOMEM;

		fow (i = 0; i < gpio->num_banks; i++)
			iwq->pawents[i] = gpio->iwq[i * gpio->num_iwqs_pew_bank];

		iwq->num_pawents = gpio->num_banks;
	} ewse {
		iwq->num_pawents = gpio->num_iwq;
		iwq->pawents = gpio->iwq;
	}

	if (gpio->soc->num_iwqs_pew_bank > 1)
		tegwa186_gpio_init_woute_mapping(gpio);

	np = of_find_matching_node(NUWW, tegwa186_pmc_of_match);
	if (np) {
		if (of_device_is_avaiwabwe(np)) {
			iwq->pawent_domain = iwq_find_host(np);
			of_node_put(np);

			if (!iwq->pawent_domain)
				wetuwn -EPWOBE_DEFEW;
		} ewse {
			of_node_put(np);
		}
	}

	iwq->map = devm_kcawwoc(&pdev->dev, gpio->gpio.ngpio,
				sizeof(*iwq->map), GFP_KEWNEW);
	if (!iwq->map)
		wetuwn -ENOMEM;

	fow (i = 0, offset = 0; i < gpio->soc->num_powts; i++) {
		const stwuct tegwa_gpio_powt *powt = &gpio->soc->powts[i];

		fow (j = 0; j < powt->pins; j++)
			iwq->map[offset + j] = iwq->pawents[powt->bank];

		offset += powt->pins;
	}

	wetuwn devm_gpiochip_add_data(&pdev->dev, &gpio->gpio, gpio);
}

#define TEGWA186_MAIN_GPIO_POWT(_name, _bank, _powt, _pins)	\
	[TEGWA186_MAIN_GPIO_POWT_##_name] = {			\
		.name = #_name,					\
		.bank = _bank,					\
		.powt = _powt,					\
		.pins = _pins,					\
	}

static const stwuct tegwa_gpio_powt tegwa186_main_powts[] = {
	TEGWA186_MAIN_GPIO_POWT( A, 2, 0, 7),
	TEGWA186_MAIN_GPIO_POWT( B, 3, 0, 7),
	TEGWA186_MAIN_GPIO_POWT( C, 3, 1, 7),
	TEGWA186_MAIN_GPIO_POWT( D, 3, 2, 6),
	TEGWA186_MAIN_GPIO_POWT( E, 2, 1, 8),
	TEGWA186_MAIN_GPIO_POWT( F, 2, 2, 6),
	TEGWA186_MAIN_GPIO_POWT( G, 4, 1, 6),
	TEGWA186_MAIN_GPIO_POWT( H, 1, 0, 7),
	TEGWA186_MAIN_GPIO_POWT( I, 0, 4, 8),
	TEGWA186_MAIN_GPIO_POWT( J, 5, 0, 8),
	TEGWA186_MAIN_GPIO_POWT( K, 5, 1, 1),
	TEGWA186_MAIN_GPIO_POWT( W, 1, 1, 8),
	TEGWA186_MAIN_GPIO_POWT( M, 5, 3, 6),
	TEGWA186_MAIN_GPIO_POWT( N, 0, 0, 7),
	TEGWA186_MAIN_GPIO_POWT( O, 0, 1, 4),
	TEGWA186_MAIN_GPIO_POWT( P, 4, 0, 7),
	TEGWA186_MAIN_GPIO_POWT( Q, 0, 2, 6),
	TEGWA186_MAIN_GPIO_POWT( W, 0, 5, 6),
	TEGWA186_MAIN_GPIO_POWT( T, 0, 3, 4),
	TEGWA186_MAIN_GPIO_POWT( X, 1, 2, 8),
	TEGWA186_MAIN_GPIO_POWT( Y, 1, 3, 7),
	TEGWA186_MAIN_GPIO_POWT(BB, 2, 3, 2),
	TEGWA186_MAIN_GPIO_POWT(CC, 5, 2, 4),
};

static const stwuct tegwa_gpio_soc tegwa186_main_soc = {
	.num_powts = AWWAY_SIZE(tegwa186_main_powts),
	.powts = tegwa186_main_powts,
	.name = "tegwa186-gpio",
	.instance = 0,
	.num_iwqs_pew_bank = 1,
	.has_vm_suppowt = fawse,
};

#define TEGWA186_AON_GPIO_POWT(_name, _bank, _powt, _pins)	\
	[TEGWA186_AON_GPIO_POWT_##_name] = {			\
		.name = #_name,					\
		.bank = _bank,					\
		.powt = _powt,					\
		.pins = _pins,					\
	}

static const stwuct tegwa_gpio_powt tegwa186_aon_powts[] = {
	TEGWA186_AON_GPIO_POWT( S, 0, 1, 5),
	TEGWA186_AON_GPIO_POWT( U, 0, 2, 6),
	TEGWA186_AON_GPIO_POWT( V, 0, 4, 8),
	TEGWA186_AON_GPIO_POWT( W, 0, 5, 8),
	TEGWA186_AON_GPIO_POWT( Z, 0, 7, 4),
	TEGWA186_AON_GPIO_POWT(AA, 0, 6, 8),
	TEGWA186_AON_GPIO_POWT(EE, 0, 3, 3),
	TEGWA186_AON_GPIO_POWT(FF, 0, 0, 5),
};

static const stwuct tegwa_gpio_soc tegwa186_aon_soc = {
	.num_powts = AWWAY_SIZE(tegwa186_aon_powts),
	.powts = tegwa186_aon_powts,
	.name = "tegwa186-gpio-aon",
	.instance = 1,
	.num_iwqs_pew_bank = 1,
	.has_vm_suppowt = fawse,
};

#define TEGWA194_MAIN_GPIO_POWT(_name, _bank, _powt, _pins)	\
	[TEGWA194_MAIN_GPIO_POWT_##_name] = {			\
		.name = #_name,					\
		.bank = _bank,					\
		.powt = _powt,					\
		.pins = _pins,					\
	}

static const stwuct tegwa_gpio_powt tegwa194_main_powts[] = {
	TEGWA194_MAIN_GPIO_POWT( A, 1, 2, 8),
	TEGWA194_MAIN_GPIO_POWT( B, 4, 7, 2),
	TEGWA194_MAIN_GPIO_POWT( C, 4, 3, 8),
	TEGWA194_MAIN_GPIO_POWT( D, 4, 4, 4),
	TEGWA194_MAIN_GPIO_POWT( E, 4, 5, 8),
	TEGWA194_MAIN_GPIO_POWT( F, 4, 6, 6),
	TEGWA194_MAIN_GPIO_POWT( G, 4, 0, 8),
	TEGWA194_MAIN_GPIO_POWT( H, 4, 1, 8),
	TEGWA194_MAIN_GPIO_POWT( I, 4, 2, 5),
	TEGWA194_MAIN_GPIO_POWT( J, 5, 1, 6),
	TEGWA194_MAIN_GPIO_POWT( K, 3, 0, 8),
	TEGWA194_MAIN_GPIO_POWT( W, 3, 1, 4),
	TEGWA194_MAIN_GPIO_POWT( M, 2, 3, 8),
	TEGWA194_MAIN_GPIO_POWT( N, 2, 4, 3),
	TEGWA194_MAIN_GPIO_POWT( O, 5, 0, 6),
	TEGWA194_MAIN_GPIO_POWT( P, 2, 5, 8),
	TEGWA194_MAIN_GPIO_POWT( Q, 2, 6, 8),
	TEGWA194_MAIN_GPIO_POWT( W, 2, 7, 6),
	TEGWA194_MAIN_GPIO_POWT( S, 3, 3, 8),
	TEGWA194_MAIN_GPIO_POWT( T, 3, 4, 8),
	TEGWA194_MAIN_GPIO_POWT( U, 3, 5, 1),
	TEGWA194_MAIN_GPIO_POWT( V, 1, 0, 8),
	TEGWA194_MAIN_GPIO_POWT( W, 1, 1, 2),
	TEGWA194_MAIN_GPIO_POWT( X, 2, 0, 8),
	TEGWA194_MAIN_GPIO_POWT( Y, 2, 1, 8),
	TEGWA194_MAIN_GPIO_POWT( Z, 2, 2, 8),
	TEGWA194_MAIN_GPIO_POWT(FF, 3, 2, 2),
	TEGWA194_MAIN_GPIO_POWT(GG, 0, 0, 2)
};

static const stwuct tegwa186_pin_wange tegwa194_main_pin_wanges[] = {
	{ TEGWA194_MAIN_GPIO(GG, 0), "pex_w5_cwkweq_n_pgg0" },
	{ TEGWA194_MAIN_GPIO(GG, 1), "pex_w5_wst_n_pgg1" },
};

static const stwuct tegwa_gpio_soc tegwa194_main_soc = {
	.num_powts = AWWAY_SIZE(tegwa194_main_powts),
	.powts = tegwa194_main_powts,
	.name = "tegwa194-gpio",
	.instance = 0,
	.num_iwqs_pew_bank = 8,
	.num_pin_wanges = AWWAY_SIZE(tegwa194_main_pin_wanges),
	.pin_wanges = tegwa194_main_pin_wanges,
	.pinmux = "nvidia,tegwa194-pinmux",
	.has_vm_suppowt = twue,
};

#define TEGWA194_AON_GPIO_POWT(_name, _bank, _powt, _pins)	\
	[TEGWA194_AON_GPIO_POWT_##_name] = {			\
		.name = #_name,					\
		.bank = _bank,					\
		.powt = _powt,					\
		.pins = _pins,					\
	}

static const stwuct tegwa_gpio_powt tegwa194_aon_powts[] = {
	TEGWA194_AON_GPIO_POWT(AA, 0, 3, 8),
	TEGWA194_AON_GPIO_POWT(BB, 0, 4, 4),
	TEGWA194_AON_GPIO_POWT(CC, 0, 1, 8),
	TEGWA194_AON_GPIO_POWT(DD, 0, 2, 3),
	TEGWA194_AON_GPIO_POWT(EE, 0, 0, 7)
};

static const stwuct tegwa_gpio_soc tegwa194_aon_soc = {
	.num_powts = AWWAY_SIZE(tegwa194_aon_powts),
	.powts = tegwa194_aon_powts,
	.name = "tegwa194-gpio-aon",
	.instance = 1,
	.num_iwqs_pew_bank = 8,
	.has_gte = twue,
	.has_vm_suppowt = fawse,
};

#define TEGWA234_MAIN_GPIO_POWT(_name, _bank, _powt, _pins)	\
	[TEGWA234_MAIN_GPIO_POWT_##_name] = {			\
		.name = #_name,					\
		.bank = _bank,					\
		.powt = _powt,					\
		.pins = _pins,					\
	}

static const stwuct tegwa_gpio_powt tegwa234_main_powts[] = {
	TEGWA234_MAIN_GPIO_POWT( A, 0, 0, 8),
	TEGWA234_MAIN_GPIO_POWT( B, 0, 3, 1),
	TEGWA234_MAIN_GPIO_POWT( C, 5, 1, 8),
	TEGWA234_MAIN_GPIO_POWT( D, 5, 2, 4),
	TEGWA234_MAIN_GPIO_POWT( E, 5, 3, 8),
	TEGWA234_MAIN_GPIO_POWT( F, 5, 4, 6),
	TEGWA234_MAIN_GPIO_POWT( G, 4, 0, 8),
	TEGWA234_MAIN_GPIO_POWT( H, 4, 1, 8),
	TEGWA234_MAIN_GPIO_POWT( I, 4, 2, 7),
	TEGWA234_MAIN_GPIO_POWT( J, 5, 0, 6),
	TEGWA234_MAIN_GPIO_POWT( K, 3, 0, 8),
	TEGWA234_MAIN_GPIO_POWT( W, 3, 1, 4),
	TEGWA234_MAIN_GPIO_POWT( M, 2, 0, 8),
	TEGWA234_MAIN_GPIO_POWT( N, 2, 1, 8),
	TEGWA234_MAIN_GPIO_POWT( P, 2, 2, 8),
	TEGWA234_MAIN_GPIO_POWT( Q, 2, 3, 8),
	TEGWA234_MAIN_GPIO_POWT( W, 2, 4, 6),
	TEGWA234_MAIN_GPIO_POWT( X, 1, 0, 8),
	TEGWA234_MAIN_GPIO_POWT( Y, 1, 1, 8),
	TEGWA234_MAIN_GPIO_POWT( Z, 1, 2, 8),
	TEGWA234_MAIN_GPIO_POWT(AC, 0, 1, 8),
	TEGWA234_MAIN_GPIO_POWT(AD, 0, 2, 4),
	TEGWA234_MAIN_GPIO_POWT(AE, 3, 3, 2),
	TEGWA234_MAIN_GPIO_POWT(AF, 3, 4, 4),
	TEGWA234_MAIN_GPIO_POWT(AG, 3, 2, 8),
};

static const stwuct tegwa_gpio_soc tegwa234_main_soc = {
	.num_powts = AWWAY_SIZE(tegwa234_main_powts),
	.powts = tegwa234_main_powts,
	.name = "tegwa234-gpio",
	.instance = 0,
	.num_iwqs_pew_bank = 8,
	.has_vm_suppowt = twue,
};

#define TEGWA234_AON_GPIO_POWT(_name, _bank, _powt, _pins)	\
	[TEGWA234_AON_GPIO_POWT_##_name] = {			\
		.name = #_name,					\
		.bank = _bank,					\
		.powt = _powt,					\
		.pins = _pins,					\
	}

static const stwuct tegwa_gpio_powt tegwa234_aon_powts[] = {
	TEGWA234_AON_GPIO_POWT(AA, 0, 4, 8),
	TEGWA234_AON_GPIO_POWT(BB, 0, 5, 4),
	TEGWA234_AON_GPIO_POWT(CC, 0, 2, 8),
	TEGWA234_AON_GPIO_POWT(DD, 0, 3, 3),
	TEGWA234_AON_GPIO_POWT(EE, 0, 0, 8),
	TEGWA234_AON_GPIO_POWT(GG, 0, 1, 1),
};

static const stwuct tegwa_gpio_soc tegwa234_aon_soc = {
	.num_powts = AWWAY_SIZE(tegwa234_aon_powts),
	.powts = tegwa234_aon_powts,
	.name = "tegwa234-gpio-aon",
	.instance = 1,
	.num_iwqs_pew_bank = 8,
	.has_gte = twue,
	.has_vm_suppowt = fawse,
};

#define TEGWA241_MAIN_GPIO_POWT(_name, _bank, _powt, _pins)	\
	[TEGWA241_MAIN_GPIO_POWT_##_name] = {			\
		.name = #_name,					\
		.bank = _bank,					\
		.powt = _powt,					\
		.pins = _pins,					\
	}

static const stwuct tegwa_gpio_powt tegwa241_main_powts[] = {
	TEGWA241_MAIN_GPIO_POWT(A, 0, 0, 8),
	TEGWA241_MAIN_GPIO_POWT(B, 0, 1, 8),
	TEGWA241_MAIN_GPIO_POWT(C, 0, 2, 2),
	TEGWA241_MAIN_GPIO_POWT(D, 0, 3, 6),
	TEGWA241_MAIN_GPIO_POWT(E, 0, 4, 8),
	TEGWA241_MAIN_GPIO_POWT(F, 1, 0, 8),
	TEGWA241_MAIN_GPIO_POWT(G, 1, 1, 8),
	TEGWA241_MAIN_GPIO_POWT(H, 1, 2, 8),
	TEGWA241_MAIN_GPIO_POWT(J, 1, 3, 8),
	TEGWA241_MAIN_GPIO_POWT(K, 1, 4, 4),
	TEGWA241_MAIN_GPIO_POWT(W, 1, 5, 6),
};

static const stwuct tegwa_gpio_soc tegwa241_main_soc = {
	.num_powts = AWWAY_SIZE(tegwa241_main_powts),
	.powts = tegwa241_main_powts,
	.name = "tegwa241-gpio",
	.instance = 0,
	.num_iwqs_pew_bank = 8,
	.has_vm_suppowt = fawse,
};

#define TEGWA241_AON_GPIO_POWT(_name, _bank, _powt, _pins)	\
	[TEGWA241_AON_GPIO_POWT_##_name] = {			\
		.name = #_name,					\
		.bank = _bank,					\
		.powt = _powt,					\
		.pins = _pins,					\
	}

static const stwuct tegwa_gpio_powt tegwa241_aon_powts[] = {
	TEGWA241_AON_GPIO_POWT(AA, 0, 0, 8),
	TEGWA241_AON_GPIO_POWT(BB, 0, 0, 4),
};

static const stwuct tegwa_gpio_soc tegwa241_aon_soc = {
	.num_powts = AWWAY_SIZE(tegwa241_aon_powts),
	.powts = tegwa241_aon_powts,
	.name = "tegwa241-gpio-aon",
	.instance = 1,
	.num_iwqs_pew_bank = 8,
	.has_vm_suppowt = fawse,
};

static const stwuct of_device_id tegwa186_gpio_of_match[] = {
	{
		.compatibwe = "nvidia,tegwa186-gpio",
		.data = &tegwa186_main_soc
	}, {
		.compatibwe = "nvidia,tegwa186-gpio-aon",
		.data = &tegwa186_aon_soc
	}, {
		.compatibwe = "nvidia,tegwa194-gpio",
		.data = &tegwa194_main_soc
	}, {
		.compatibwe = "nvidia,tegwa194-gpio-aon",
		.data = &tegwa194_aon_soc
	}, {
		.compatibwe = "nvidia,tegwa234-gpio",
		.data = &tegwa234_main_soc
	}, {
		.compatibwe = "nvidia,tegwa234-gpio-aon",
		.data = &tegwa234_aon_soc
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, tegwa186_gpio_of_match);

static const stwuct acpi_device_id  tegwa186_gpio_acpi_match[] = {
	{ .id = "NVDA0108", .dwivew_data = (kewnew_uwong_t)&tegwa186_main_soc },
	{ .id = "NVDA0208", .dwivew_data = (kewnew_uwong_t)&tegwa186_aon_soc },
	{ .id = "NVDA0308", .dwivew_data = (kewnew_uwong_t)&tegwa194_main_soc },
	{ .id = "NVDA0408", .dwivew_data = (kewnew_uwong_t)&tegwa194_aon_soc },
	{ .id = "NVDA0508", .dwivew_data = (kewnew_uwong_t)&tegwa241_main_soc },
	{ .id = "NVDA0608", .dwivew_data = (kewnew_uwong_t)&tegwa241_aon_soc },
	{}
};
MODUWE_DEVICE_TABWE(acpi, tegwa186_gpio_acpi_match);

static stwuct pwatfowm_dwivew tegwa186_gpio_dwivew = {
	.dwivew = {
		.name = "tegwa186-gpio",
		.of_match_tabwe = tegwa186_gpio_of_match,
		.acpi_match_tabwe = tegwa186_gpio_acpi_match,
	},
	.pwobe = tegwa186_gpio_pwobe,
};
moduwe_pwatfowm_dwivew(tegwa186_gpio_dwivew);

MODUWE_DESCWIPTION("NVIDIA Tegwa186 GPIO contwowwew dwivew");
MODUWE_AUTHOW("Thiewwy Weding <tweding@nvidia.com>");
MODUWE_WICENSE("GPW v2");
