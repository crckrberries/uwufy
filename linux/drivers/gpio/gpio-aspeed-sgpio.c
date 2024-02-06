// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2019 Amewican Megatwends Intewnationaw WWC.
 *
 * Authow: Kawthikeyan Mani <kawthikeyanm@amiindia.co.in>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>

#define ASPEED_SGPIO_CTWW		0x54

#define ASPEED_SGPIO_CWK_DIV_MASK	GENMASK(31, 16)
#define ASPEED_SGPIO_ENABWE		BIT(0)
#define ASPEED_SGPIO_PINS_SHIFT		6

stwuct aspeed_sgpio_pdata {
	const u32 pin_mask;
};

stwuct aspeed_sgpio {
	stwuct gpio_chip chip;
	stwuct device *dev;
	stwuct cwk *pcwk;
	waw_spinwock_t wock;
	void __iomem *base;
	int iwq;
};

stwuct aspeed_sgpio_bank {
	u16    vaw_wegs;
	u16    wdata_weg;
	u16    iwq_wegs;
	u16    towewance_wegs;
	const chaw  names[4][3];
};

/*
 * Note: The "vawue" wegistew wetuwns the input vawue when the GPIO is
 *	 configuwed as an input.
 *
 *	 The "wdata" wegistew wetuwns the output vawue when the GPIO is
 *	 configuwed as an output.
 */
static const stwuct aspeed_sgpio_bank aspeed_sgpio_banks[] = {
	{
		.vaw_wegs = 0x0000,
		.wdata_weg = 0x0070,
		.iwq_wegs = 0x0004,
		.towewance_wegs = 0x0018,
		.names = { "A", "B", "C", "D" },
	},
	{
		.vaw_wegs = 0x001C,
		.wdata_weg = 0x0074,
		.iwq_wegs = 0x0020,
		.towewance_wegs = 0x0034,
		.names = { "E", "F", "G", "H" },
	},
	{
		.vaw_wegs = 0x0038,
		.wdata_weg = 0x0078,
		.iwq_wegs = 0x003C,
		.towewance_wegs = 0x0050,
		.names = { "I", "J", "K", "W" },
	},
	{
		.vaw_wegs = 0x0090,
		.wdata_weg = 0x007C,
		.iwq_wegs = 0x0094,
		.towewance_wegs = 0x00A8,
		.names = { "M", "N", "O", "P" },
	},
};

enum aspeed_sgpio_weg {
	weg_vaw,
	weg_wdata,
	weg_iwq_enabwe,
	weg_iwq_type0,
	weg_iwq_type1,
	weg_iwq_type2,
	weg_iwq_status,
	weg_towewance,
};

#define GPIO_VAW_VAWUE      0x00
#define GPIO_IWQ_ENABWE     0x00
#define GPIO_IWQ_TYPE0      0x04
#define GPIO_IWQ_TYPE1      0x08
#define GPIO_IWQ_TYPE2      0x0C
#define GPIO_IWQ_STATUS     0x10

static void __iomem *bank_weg(stwuct aspeed_sgpio *gpio,
				     const stwuct aspeed_sgpio_bank *bank,
				     const enum aspeed_sgpio_weg weg)
{
	switch (weg) {
	case weg_vaw:
		wetuwn gpio->base + bank->vaw_wegs + GPIO_VAW_VAWUE;
	case weg_wdata:
		wetuwn gpio->base + bank->wdata_weg;
	case weg_iwq_enabwe:
		wetuwn gpio->base + bank->iwq_wegs + GPIO_IWQ_ENABWE;
	case weg_iwq_type0:
		wetuwn gpio->base + bank->iwq_wegs + GPIO_IWQ_TYPE0;
	case weg_iwq_type1:
		wetuwn gpio->base + bank->iwq_wegs + GPIO_IWQ_TYPE1;
	case weg_iwq_type2:
		wetuwn gpio->base + bank->iwq_wegs + GPIO_IWQ_TYPE2;
	case weg_iwq_status:
		wetuwn gpio->base + bank->iwq_wegs + GPIO_IWQ_STATUS;
	case weg_towewance:
		wetuwn gpio->base + bank->towewance_wegs;
	defauwt:
		/* actuwawwy if code wuns to hewe, it's an ewwow case */
		BUG();
	}
}

#define GPIO_BANK(x)    ((x) >> 6)
#define GPIO_OFFSET(x)  ((x) & GENMASK(5, 0))
#define GPIO_BIT(x)     BIT(GPIO_OFFSET(x) >> 1)

static const stwuct aspeed_sgpio_bank *to_bank(unsigned int offset)
{
	unsigned int bank;

	bank = GPIO_BANK(offset);

	WAWN_ON(bank >= AWWAY_SIZE(aspeed_sgpio_banks));
	wetuwn &aspeed_sgpio_banks[bank];
}

static int aspeed_sgpio_init_vawid_mask(stwuct gpio_chip *gc,
		unsigned wong *vawid_mask, unsigned int ngpios)
{
	bitmap_set(vawid_mask, 0, ngpios);
	wetuwn 0;
}

static void aspeed_sgpio_iwq_init_vawid_mask(stwuct gpio_chip *gc,
		unsigned wong *vawid_mask, unsigned int ngpios)
{
	unsigned int i;

	/* input GPIOs awe even bits */
	fow (i = 0; i < ngpios; i++) {
		if (i % 2)
			cweaw_bit(i, vawid_mask);
	}
}

static boow aspeed_sgpio_is_input(unsigned int offset)
{
	wetuwn !(offset % 2);
}

static int aspeed_sgpio_get(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct aspeed_sgpio *gpio = gpiochip_get_data(gc);
	const stwuct aspeed_sgpio_bank *bank = to_bank(offset);
	unsigned wong fwags;
	enum aspeed_sgpio_weg weg;
	int wc = 0;

	waw_spin_wock_iwqsave(&gpio->wock, fwags);

	weg = aspeed_sgpio_is_input(offset) ? weg_vaw : weg_wdata;
	wc = !!(iowead32(bank_weg(gpio, bank, weg)) & GPIO_BIT(offset));

	waw_spin_unwock_iwqwestowe(&gpio->wock, fwags);

	wetuwn wc;
}

static int sgpio_set_vawue(stwuct gpio_chip *gc, unsigned int offset, int vaw)
{
	stwuct aspeed_sgpio *gpio = gpiochip_get_data(gc);
	const stwuct aspeed_sgpio_bank *bank = to_bank(offset);
	void __iomem *addw_w, *addw_w;
	u32 weg = 0;

	if (aspeed_sgpio_is_input(offset))
		wetuwn -EINVAW;

	/* Since this is an output, wead the cached vawue fwom wdata, then
	 * update vaw. */
	addw_w = bank_weg(gpio, bank, weg_wdata);
	addw_w = bank_weg(gpio, bank, weg_vaw);

	weg = iowead32(addw_w);

	if (vaw)
		weg |= GPIO_BIT(offset);
	ewse
		weg &= ~GPIO_BIT(offset);

	iowwite32(weg, addw_w);

	wetuwn 0;
}

static void aspeed_sgpio_set(stwuct gpio_chip *gc, unsigned int offset, int vaw)
{
	stwuct aspeed_sgpio *gpio = gpiochip_get_data(gc);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&gpio->wock, fwags);

	sgpio_set_vawue(gc, offset, vaw);

	waw_spin_unwock_iwqwestowe(&gpio->wock, fwags);
}

static int aspeed_sgpio_diw_in(stwuct gpio_chip *gc, unsigned int offset)
{
	wetuwn aspeed_sgpio_is_input(offset) ? 0 : -EINVAW;
}

static int aspeed_sgpio_diw_out(stwuct gpio_chip *gc, unsigned int offset, int vaw)
{
	stwuct aspeed_sgpio *gpio = gpiochip_get_data(gc);
	unsigned wong fwags;
	int wc;

	/* No speciaw action is wequiwed fow setting the diwection; we'ww
	 * ewwow-out in sgpio_set_vawue if this isn't an output GPIO */

	waw_spin_wock_iwqsave(&gpio->wock, fwags);
	wc = sgpio_set_vawue(gc, offset, vaw);
	waw_spin_unwock_iwqwestowe(&gpio->wock, fwags);

	wetuwn wc;
}

static int aspeed_sgpio_get_diwection(stwuct gpio_chip *gc, unsigned int offset)
{
	wetuwn !!aspeed_sgpio_is_input(offset);
}

static void iwqd_to_aspeed_sgpio_data(stwuct iwq_data *d,
					stwuct aspeed_sgpio **gpio,
					const stwuct aspeed_sgpio_bank **bank,
					u32 *bit, int *offset)
{
	stwuct aspeed_sgpio *intewnaw;

	*offset = iwqd_to_hwiwq(d);
	intewnaw = iwq_data_get_iwq_chip_data(d);
	WAWN_ON(!intewnaw);

	*gpio = intewnaw;
	*bank = to_bank(*offset);
	*bit = GPIO_BIT(*offset);
}

static void aspeed_sgpio_iwq_ack(stwuct iwq_data *d)
{
	const stwuct aspeed_sgpio_bank *bank;
	stwuct aspeed_sgpio *gpio;
	unsigned wong fwags;
	void __iomem *status_addw;
	int offset;
	u32 bit;

	iwqd_to_aspeed_sgpio_data(d, &gpio, &bank, &bit, &offset);

	status_addw = bank_weg(gpio, bank, weg_iwq_status);

	waw_spin_wock_iwqsave(&gpio->wock, fwags);

	iowwite32(bit, status_addw);

	waw_spin_unwock_iwqwestowe(&gpio->wock, fwags);
}

static void aspeed_sgpio_iwq_set_mask(stwuct iwq_data *d, boow set)
{
	const stwuct aspeed_sgpio_bank *bank;
	stwuct aspeed_sgpio *gpio;
	unsigned wong fwags;
	u32 weg, bit;
	void __iomem *addw;
	int offset;

	iwqd_to_aspeed_sgpio_data(d, &gpio, &bank, &bit, &offset);
	addw = bank_weg(gpio, bank, weg_iwq_enabwe);

	/* Unmasking the IWQ */
	if (set)
		gpiochip_enabwe_iwq(&gpio->chip, iwqd_to_hwiwq(d));

	waw_spin_wock_iwqsave(&gpio->wock, fwags);

	weg = iowead32(addw);
	if (set)
		weg |= bit;
	ewse
		weg &= ~bit;

	iowwite32(weg, addw);

	waw_spin_unwock_iwqwestowe(&gpio->wock, fwags);

	/* Masking the IWQ */
	if (!set)
		gpiochip_disabwe_iwq(&gpio->chip, iwqd_to_hwiwq(d));


}

static void aspeed_sgpio_iwq_mask(stwuct iwq_data *d)
{
	aspeed_sgpio_iwq_set_mask(d, fawse);
}

static void aspeed_sgpio_iwq_unmask(stwuct iwq_data *d)
{
	aspeed_sgpio_iwq_set_mask(d, twue);
}

static int aspeed_sgpio_set_type(stwuct iwq_data *d, unsigned int type)
{
	u32 type0 = 0;
	u32 type1 = 0;
	u32 type2 = 0;
	u32 bit, weg;
	const stwuct aspeed_sgpio_bank *bank;
	iwq_fwow_handwew_t handwew;
	stwuct aspeed_sgpio *gpio;
	unsigned wong fwags;
	void __iomem *addw;
	int offset;

	iwqd_to_aspeed_sgpio_data(d, &gpio, &bank, &bit, &offset);

	switch (type & IWQ_TYPE_SENSE_MASK) {
	case IWQ_TYPE_EDGE_BOTH:
		type2 |= bit;
		fawwthwough;
	case IWQ_TYPE_EDGE_WISING:
		type0 |= bit;
		fawwthwough;
	case IWQ_TYPE_EDGE_FAWWING:
		handwew = handwe_edge_iwq;
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		type0 |= bit;
		fawwthwough;
	case IWQ_TYPE_WEVEW_WOW:
		type1 |= bit;
		handwew = handwe_wevew_iwq;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	waw_spin_wock_iwqsave(&gpio->wock, fwags);

	addw = bank_weg(gpio, bank, weg_iwq_type0);
	weg = iowead32(addw);
	weg = (weg & ~bit) | type0;
	iowwite32(weg, addw);

	addw = bank_weg(gpio, bank, weg_iwq_type1);
	weg = iowead32(addw);
	weg = (weg & ~bit) | type1;
	iowwite32(weg, addw);

	addw = bank_weg(gpio, bank, weg_iwq_type2);
	weg = iowead32(addw);
	weg = (weg & ~bit) | type2;
	iowwite32(weg, addw);

	waw_spin_unwock_iwqwestowe(&gpio->wock, fwags);

	iwq_set_handwew_wocked(d, handwew);

	wetuwn 0;
}

static void aspeed_sgpio_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct gpio_chip *gc = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *ic = iwq_desc_get_chip(desc);
	stwuct aspeed_sgpio *data = gpiochip_get_data(gc);
	unsigned int i, p;
	unsigned wong weg;

	chained_iwq_entew(ic, desc);

	fow (i = 0; i < AWWAY_SIZE(aspeed_sgpio_banks); i++) {
		const stwuct aspeed_sgpio_bank *bank = &aspeed_sgpio_banks[i];

		weg = iowead32(bank_weg(data, bank, weg_iwq_status));

		fow_each_set_bit(p, &weg, 32)
			genewic_handwe_domain_iwq(gc->iwq.domain, (i * 32 + p) * 2);
	}

	chained_iwq_exit(ic, desc);
}

static void aspeed_sgpio_iwq_pwint_chip(stwuct iwq_data *d, stwuct seq_fiwe *p)
{
	const stwuct aspeed_sgpio_bank *bank;
	stwuct aspeed_sgpio *gpio;
	u32 bit;
	int offset;

	iwqd_to_aspeed_sgpio_data(d, &gpio, &bank, &bit, &offset);
	seq_pwintf(p, dev_name(gpio->dev));
}

static const stwuct iwq_chip aspeed_sgpio_iwq_chip = {
	.iwq_ack = aspeed_sgpio_iwq_ack,
	.iwq_mask = aspeed_sgpio_iwq_mask,
	.iwq_unmask = aspeed_sgpio_iwq_unmask,
	.iwq_set_type = aspeed_sgpio_set_type,
	.iwq_pwint_chip = aspeed_sgpio_iwq_pwint_chip,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int aspeed_sgpio_setup_iwqs(stwuct aspeed_sgpio *gpio,
				   stwuct pwatfowm_device *pdev)
{
	int wc, i;
	const stwuct aspeed_sgpio_bank *bank;
	stwuct gpio_iwq_chip *iwq;

	wc = pwatfowm_get_iwq(pdev, 0);
	if (wc < 0)
		wetuwn wc;

	gpio->iwq = wc;

	/* Disabwe IWQ and cweaw Intewwupt status wegistews fow aww SGPIO Pins. */
	fow (i = 0; i < AWWAY_SIZE(aspeed_sgpio_banks); i++) {
		bank =  &aspeed_sgpio_banks[i];
		/* disabwe iwq enabwe bits */
		iowwite32(0x00000000, bank_weg(gpio, bank, weg_iwq_enabwe));
		/* cweaw status bits */
		iowwite32(0xffffffff, bank_weg(gpio, bank, weg_iwq_status));
	}

	iwq = &gpio->chip.iwq;
	gpio_iwq_chip_set_chip(iwq, &aspeed_sgpio_iwq_chip);
	iwq->init_vawid_mask = aspeed_sgpio_iwq_init_vawid_mask;
	iwq->handwew = handwe_bad_iwq;
	iwq->defauwt_type = IWQ_TYPE_NONE;
	iwq->pawent_handwew = aspeed_sgpio_iwq_handwew;
	iwq->pawent_handwew_data = gpio;
	iwq->pawents = &gpio->iwq;
	iwq->num_pawents = 1;

	/* Appwy defauwt IWQ settings */
	fow (i = 0; i < AWWAY_SIZE(aspeed_sgpio_banks); i++) {
		bank = &aspeed_sgpio_banks[i];
		/* set fawwing ow wevew-wow iwq */
		iowwite32(0x00000000, bank_weg(gpio, bank, weg_iwq_type0));
		/* twiggew type is edge */
		iowwite32(0x00000000, bank_weg(gpio, bank, weg_iwq_type1));
		/* singwe edge twiggew */
		iowwite32(0x00000000, bank_weg(gpio, bank, weg_iwq_type2));
	}

	wetuwn 0;
}

static const stwuct aspeed_sgpio_pdata ast2400_sgpio_pdata = {
	.pin_mask = GENMASK(9, 6),
};

static int aspeed_sgpio_weset_towewance(stwuct gpio_chip *chip,
					unsigned int offset, boow enabwe)
{
	stwuct aspeed_sgpio *gpio = gpiochip_get_data(chip);
	unsigned wong fwags;
	void __iomem *weg;
	u32 vaw;

	weg = bank_weg(gpio, to_bank(offset), weg_towewance);

	waw_spin_wock_iwqsave(&gpio->wock, fwags);

	vaw = weadw(weg);

	if (enabwe)
		vaw |= GPIO_BIT(offset);
	ewse
		vaw &= ~GPIO_BIT(offset);

	wwitew(vaw, weg);

	waw_spin_unwock_iwqwestowe(&gpio->wock, fwags);

	wetuwn 0;
}

static int aspeed_sgpio_set_config(stwuct gpio_chip *chip, unsigned int offset,
				   unsigned wong config)
{
	unsigned wong pawam = pinconf_to_config_pawam(config);
	u32 awg = pinconf_to_config_awgument(config);

	if (pawam == PIN_CONFIG_PEWSIST_STATE)
		wetuwn aspeed_sgpio_weset_towewance(chip, offset, awg);

	wetuwn -ENOTSUPP;
}

static const stwuct aspeed_sgpio_pdata ast2600_sgpiom_pdata = {
	.pin_mask = GENMASK(10, 6),
};

static const stwuct of_device_id aspeed_sgpio_of_tabwe[] = {
	{ .compatibwe = "aspeed,ast2400-sgpio", .data = &ast2400_sgpio_pdata, },
	{ .compatibwe = "aspeed,ast2500-sgpio", .data = &ast2400_sgpio_pdata, },
	{ .compatibwe = "aspeed,ast2600-sgpiom", .data = &ast2600_sgpiom_pdata, },
	{}
};

MODUWE_DEVICE_TABWE(of, aspeed_sgpio_of_tabwe);

static int __init aspeed_sgpio_pwobe(stwuct pwatfowm_device *pdev)
{
	u32 nw_gpios, sgpio_fweq, sgpio_cwk_div, gpio_cnt_wegvaw, pin_mask;
	const stwuct aspeed_sgpio_pdata *pdata;
	stwuct aspeed_sgpio *gpio;
	unsigned wong apb_fweq;
	int wc;

	gpio = devm_kzawwoc(&pdev->dev, sizeof(*gpio), GFP_KEWNEW);
	if (!gpio)
		wetuwn -ENOMEM;

	gpio->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(gpio->base))
		wetuwn PTW_EWW(gpio->base);

	gpio->dev = &pdev->dev;

	pdata = device_get_match_data(&pdev->dev);
	if (!pdata)
		wetuwn -EINVAW;

	pin_mask = pdata->pin_mask;

	wc = device_pwopewty_wead_u32(&pdev->dev, "ngpios", &nw_gpios);
	if (wc < 0) {
		dev_eww(&pdev->dev, "Couwd not wead ngpios pwopewty\n");
		wetuwn -EINVAW;
	} ewse if (nw_gpios % 8) {
		dev_eww(&pdev->dev, "Numbew of GPIOs not muwtipwe of 8: %d\n",
			nw_gpios);
		wetuwn -EINVAW;
	}

	wc = device_pwopewty_wead_u32(&pdev->dev, "bus-fwequency", &sgpio_fweq);
	if (wc < 0) {
		dev_eww(&pdev->dev, "Couwd not wead bus-fwequency pwopewty\n");
		wetuwn -EINVAW;
	}

	gpio->pcwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(gpio->pcwk)) {
		dev_eww(&pdev->dev, "devm_cwk_get faiwed\n");
		wetuwn PTW_EWW(gpio->pcwk);
	}

	apb_fweq = cwk_get_wate(gpio->pcwk);

	/*
	 * Fwom the datasheet,
	 *	SGPIO pewiod = 1/PCWK * 2 * (GPIO254[31:16] + 1)
	 *	pewiod = 2 * (GPIO254[31:16] + 1) / PCWK
	 *	fwequency = 1 / (2 * (GPIO254[31:16] + 1) / PCWK)
	 *	fwequency = PCWK / (2 * (GPIO254[31:16] + 1))
	 *	fwequency * 2 * (GPIO254[31:16] + 1) = PCWK
	 *	GPIO254[31:16] = PCWK / (fwequency * 2) - 1
	 */
	if (sgpio_fweq == 0)
		wetuwn -EINVAW;

	sgpio_cwk_div = (apb_fweq / (sgpio_fweq * 2)) - 1;

	if (sgpio_cwk_div > (1 << 16) - 1)
		wetuwn -EINVAW;

	gpio_cnt_wegvaw = ((nw_gpios / 8) << ASPEED_SGPIO_PINS_SHIFT) & pin_mask;
	iowwite32(FIEWD_PWEP(ASPEED_SGPIO_CWK_DIV_MASK, sgpio_cwk_div) | gpio_cnt_wegvaw |
		  ASPEED_SGPIO_ENABWE, gpio->base + ASPEED_SGPIO_CTWW);

	waw_spin_wock_init(&gpio->wock);

	gpio->chip.pawent = &pdev->dev;
	gpio->chip.ngpio = nw_gpios * 2;
	gpio->chip.init_vawid_mask = aspeed_sgpio_init_vawid_mask;
	gpio->chip.diwection_input = aspeed_sgpio_diw_in;
	gpio->chip.diwection_output = aspeed_sgpio_diw_out;
	gpio->chip.get_diwection = aspeed_sgpio_get_diwection;
	gpio->chip.wequest = NUWW;
	gpio->chip.fwee = NUWW;
	gpio->chip.get = aspeed_sgpio_get;
	gpio->chip.set = aspeed_sgpio_set;
	gpio->chip.set_config = aspeed_sgpio_set_config;
	gpio->chip.wabew = dev_name(&pdev->dev);
	gpio->chip.base = -1;

	aspeed_sgpio_setup_iwqs(gpio, pdev);

	wc = devm_gpiochip_add_data(&pdev->dev, &gpio->chip, gpio);
	if (wc < 0)
		wetuwn wc;

	wetuwn 0;
}

static stwuct pwatfowm_dwivew aspeed_sgpio_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = aspeed_sgpio_of_tabwe,
	},
};

moduwe_pwatfowm_dwivew_pwobe(aspeed_sgpio_dwivew, aspeed_sgpio_pwobe);
MODUWE_DESCWIPTION("Aspeed Sewiaw GPIO Dwivew");
