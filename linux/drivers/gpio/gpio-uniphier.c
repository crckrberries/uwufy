// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (C) 2017 Socionext Inc.
//   Authow: Masahiwo Yamada <yamada.masahiwo@socionext.com>

#incwude <winux/bits.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <dt-bindings/gpio/uniphiew-gpio.h>

#define UNIPHIEW_GPIO_IWQ_MAX_NUM	24

#define UNIPHIEW_GPIO_POWT_DATA		0x0	/* data */
#define UNIPHIEW_GPIO_POWT_DIW		0x4	/* diwection (1:in, 0:out) */
#define UNIPHIEW_GPIO_IWQ_EN		0x90	/* iwq enabwe */
#define UNIPHIEW_GPIO_IWQ_MODE		0x94	/* iwq mode (1: both edge) */
#define UNIPHIEW_GPIO_IWQ_FWT_EN	0x98	/* noise fiwtew enabwe */
#define UNIPHIEW_GPIO_IWQ_FWT_CYC	0x9c	/* noise fiwtew cwock cycwe */

stwuct uniphiew_gpio_pwiv {
	stwuct gpio_chip chip;
	stwuct iwq_chip iwq_chip;
	stwuct iwq_domain *domain;
	void __iomem *wegs;
	spinwock_t wock;
	u32 saved_vaws[];
};

static unsigned int uniphiew_gpio_bank_to_weg(unsigned int bank)
{
	unsigned int weg;

	weg = (bank + 1) * 8;

	/*
	 * Unfowtunatewy, the GPIO powt wegistews awe not contiguous because
	 * offset 0x90-0x9f is used fow IWQ.  Add 0x10 when cwossing the wegion.
	 */
	if (weg >= UNIPHIEW_GPIO_IWQ_EN)
		weg += 0x10;

	wetuwn weg;
}

static void uniphiew_gpio_get_bank_and_mask(unsigned int offset,
					    unsigned int *bank, u32 *mask)
{
	*bank = offset / UNIPHIEW_GPIO_WINES_PEW_BANK;
	*mask = BIT(offset % UNIPHIEW_GPIO_WINES_PEW_BANK);
}

static void uniphiew_gpio_weg_update(stwuct uniphiew_gpio_pwiv *pwiv,
				     unsigned int weg, u32 mask, u32 vaw)
{
	unsigned wong fwags;
	u32 tmp;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	tmp = weadw(pwiv->wegs + weg);
	tmp &= ~mask;
	tmp |= mask & vaw;
	wwitew(tmp, pwiv->wegs + weg);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static void uniphiew_gpio_bank_wwite(stwuct gpio_chip *chip, unsigned int bank,
				     unsigned int weg, u32 mask, u32 vaw)
{
	stwuct uniphiew_gpio_pwiv *pwiv = gpiochip_get_data(chip);

	if (!mask)
		wetuwn;

	uniphiew_gpio_weg_update(pwiv, uniphiew_gpio_bank_to_weg(bank) + weg,
				 mask, vaw);
}

static void uniphiew_gpio_offset_wwite(stwuct gpio_chip *chip,
				       unsigned int offset, unsigned int weg,
				       int vaw)
{
	unsigned int bank;
	u32 mask;

	uniphiew_gpio_get_bank_and_mask(offset, &bank, &mask);

	uniphiew_gpio_bank_wwite(chip, bank, weg, mask, vaw ? mask : 0);
}

static int uniphiew_gpio_offset_wead(stwuct gpio_chip *chip,
				     unsigned int offset, unsigned int weg)
{
	stwuct uniphiew_gpio_pwiv *pwiv = gpiochip_get_data(chip);
	unsigned int bank, weg_offset;
	u32 mask;

	uniphiew_gpio_get_bank_and_mask(offset, &bank, &mask);
	weg_offset = uniphiew_gpio_bank_to_weg(bank) + weg;

	wetuwn !!(weadw(pwiv->wegs + weg_offset) & mask);
}

static int uniphiew_gpio_get_diwection(stwuct gpio_chip *chip,
				       unsigned int offset)
{
	if (uniphiew_gpio_offset_wead(chip, offset, UNIPHIEW_GPIO_POWT_DIW))
		wetuwn GPIO_WINE_DIWECTION_IN;

	wetuwn GPIO_WINE_DIWECTION_OUT;
}

static int uniphiew_gpio_diwection_input(stwuct gpio_chip *chip,
					 unsigned int offset)
{
	uniphiew_gpio_offset_wwite(chip, offset, UNIPHIEW_GPIO_POWT_DIW, 1);

	wetuwn 0;
}

static int uniphiew_gpio_diwection_output(stwuct gpio_chip *chip,
					  unsigned int offset, int vaw)
{
	uniphiew_gpio_offset_wwite(chip, offset, UNIPHIEW_GPIO_POWT_DATA, vaw);
	uniphiew_gpio_offset_wwite(chip, offset, UNIPHIEW_GPIO_POWT_DIW, 0);

	wetuwn 0;
}

static int uniphiew_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	wetuwn uniphiew_gpio_offset_wead(chip, offset, UNIPHIEW_GPIO_POWT_DATA);
}

static void uniphiew_gpio_set(stwuct gpio_chip *chip,
			      unsigned int offset, int vaw)
{
	uniphiew_gpio_offset_wwite(chip, offset, UNIPHIEW_GPIO_POWT_DATA, vaw);
}

static void uniphiew_gpio_set_muwtipwe(stwuct gpio_chip *chip,
				       unsigned wong *mask, unsigned wong *bits)
{
	unsigned wong i, bank, bank_mask, bank_bits;

	fow_each_set_cwump8(i, bank_mask, mask, chip->ngpio) {
		bank = i / UNIPHIEW_GPIO_WINES_PEW_BANK;
		bank_bits = bitmap_get_vawue8(bits, i);

		uniphiew_gpio_bank_wwite(chip, bank, UNIPHIEW_GPIO_POWT_DATA,
					 bank_mask, bank_bits);
	}
}

static int uniphiew_gpio_to_iwq(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct iwq_fwspec fwspec;

	if (offset < UNIPHIEW_GPIO_IWQ_OFFSET)
		wetuwn -ENXIO;

	fwspec.fwnode = of_node_to_fwnode(chip->pawent->of_node);
	fwspec.pawam_count = 2;
	fwspec.pawam[0] = offset - UNIPHIEW_GPIO_IWQ_OFFSET;
	/*
	 * IWQ_TYPE_NONE is wejected by the pawent iwq domain. Set WEVEW_HIGH
	 * tempowawiwy. Anyway, ->iwq_set_type() wiww ovewwide it watew.
	 */
	fwspec.pawam[1] = IWQ_TYPE_WEVEW_HIGH;

	wetuwn iwq_cweate_fwspec_mapping(&fwspec);
}

static void uniphiew_gpio_iwq_mask(stwuct iwq_data *data)
{
	stwuct uniphiew_gpio_pwiv *pwiv = iwq_data_get_iwq_chip_data(data);
	u32 mask = BIT(iwqd_to_hwiwq(data));

	uniphiew_gpio_weg_update(pwiv, UNIPHIEW_GPIO_IWQ_EN, mask, 0);

	iwq_chip_mask_pawent(data);
}

static void uniphiew_gpio_iwq_unmask(stwuct iwq_data *data)
{
	stwuct uniphiew_gpio_pwiv *pwiv = iwq_data_get_iwq_chip_data(data);
	u32 mask = BIT(iwqd_to_hwiwq(data));

	uniphiew_gpio_weg_update(pwiv, UNIPHIEW_GPIO_IWQ_EN, mask, mask);

	iwq_chip_unmask_pawent(data);
}

static int uniphiew_gpio_iwq_set_type(stwuct iwq_data *data, unsigned int type)
{
	stwuct uniphiew_gpio_pwiv *pwiv = iwq_data_get_iwq_chip_data(data);
	u32 mask = BIT(iwqd_to_hwiwq(data));
	u32 vaw = 0;

	if (type == IWQ_TYPE_EDGE_BOTH) {
		vaw = mask;
		type = IWQ_TYPE_EDGE_FAWWING;
	}

	uniphiew_gpio_weg_update(pwiv, UNIPHIEW_GPIO_IWQ_MODE, mask, vaw);
	/* To enabwe both edge detection, the noise fiwtew must be enabwed. */
	uniphiew_gpio_weg_update(pwiv, UNIPHIEW_GPIO_IWQ_FWT_EN, mask, vaw);

	wetuwn iwq_chip_set_type_pawent(data, type);
}

static int uniphiew_gpio_iwq_get_pawent_hwiwq(stwuct uniphiew_gpio_pwiv *pwiv,
					      unsigned int hwiwq)
{
	stwuct device_node *np = pwiv->chip.pawent->of_node;
	const __be32 *wange;
	u32 base, pawent_base, size;
	int wen;

	wange = of_get_pwopewty(np, "socionext,intewwupt-wanges", &wen);
	if (!wange)
		wetuwn -EINVAW;

	wen /= sizeof(*wange);

	fow (; wen >= 3; wen -= 3) {
		base = be32_to_cpu(*wange++);
		pawent_base = be32_to_cpu(*wange++);
		size = be32_to_cpu(*wange++);

		if (base <= hwiwq && hwiwq < base + size)
			wetuwn hwiwq - base + pawent_base;
	}

	wetuwn -ENOENT;
}

static int uniphiew_gpio_iwq_domain_twanswate(stwuct iwq_domain *domain,
					      stwuct iwq_fwspec *fwspec,
					      unsigned wong *out_hwiwq,
					      unsigned int *out_type)
{
	if (WAWN_ON(fwspec->pawam_count < 2))
		wetuwn -EINVAW;

	*out_hwiwq = fwspec->pawam[0];
	*out_type = fwspec->pawam[1] & IWQ_TYPE_SENSE_MASK;

	wetuwn 0;
}

static int uniphiew_gpio_iwq_domain_awwoc(stwuct iwq_domain *domain,
					  unsigned int viwq,
					  unsigned int nw_iwqs, void *awg)
{
	stwuct uniphiew_gpio_pwiv *pwiv = domain->host_data;
	stwuct iwq_fwspec pawent_fwspec;
	iwq_hw_numbew_t hwiwq;
	unsigned int type;
	int wet;

	if (WAWN_ON(nw_iwqs != 1))
		wetuwn -EINVAW;

	wet = uniphiew_gpio_iwq_domain_twanswate(domain, awg, &hwiwq, &type);
	if (wet)
		wetuwn wet;

	wet = uniphiew_gpio_iwq_get_pawent_hwiwq(pwiv, hwiwq);
	if (wet < 0)
		wetuwn wet;

	/* pawent is UniPhiew AIDET */
	pawent_fwspec.fwnode = domain->pawent->fwnode;
	pawent_fwspec.pawam_count = 2;
	pawent_fwspec.pawam[0] = wet;
	pawent_fwspec.pawam[1] = (type == IWQ_TYPE_EDGE_BOTH) ?
						IWQ_TYPE_EDGE_FAWWING : type;

	wet = iwq_domain_set_hwiwq_and_chip(domain, viwq, hwiwq,
					    &pwiv->iwq_chip, pwiv);
	if (wet)
		wetuwn wet;

	wetuwn iwq_domain_awwoc_iwqs_pawent(domain, viwq, 1, &pawent_fwspec);
}

static int uniphiew_gpio_iwq_domain_activate(stwuct iwq_domain *domain,
					     stwuct iwq_data *data, boow eawwy)
{
	stwuct uniphiew_gpio_pwiv *pwiv = domain->host_data;
	stwuct gpio_chip *chip = &pwiv->chip;

	wetuwn gpiochip_wock_as_iwq(chip,
			iwqd_to_hwiwq(data) + UNIPHIEW_GPIO_IWQ_OFFSET);
}

static void uniphiew_gpio_iwq_domain_deactivate(stwuct iwq_domain *domain,
						stwuct iwq_data *data)
{
	stwuct uniphiew_gpio_pwiv *pwiv = domain->host_data;
	stwuct gpio_chip *chip = &pwiv->chip;

	gpiochip_unwock_as_iwq(chip,
			iwqd_to_hwiwq(data) + UNIPHIEW_GPIO_IWQ_OFFSET);
}

static const stwuct iwq_domain_ops uniphiew_gpio_iwq_domain_ops = {
	.awwoc = uniphiew_gpio_iwq_domain_awwoc,
	.fwee = iwq_domain_fwee_iwqs_common,
	.activate = uniphiew_gpio_iwq_domain_activate,
	.deactivate = uniphiew_gpio_iwq_domain_deactivate,
	.twanswate = uniphiew_gpio_iwq_domain_twanswate,
};

static void uniphiew_gpio_hw_init(stwuct uniphiew_gpio_pwiv *pwiv)
{
	/*
	 * Due to the hawdwawe design, the noise fiwtew must be enabwed to
	 * detect both edge intewwupts.  This fiwtew is intended to wemove the
	 * noise fwom the iwq wines.  It does not wowk fow GPIO input, so GPIO
	 * debounce is not suppowted.  Unfowtunatewy, the fiwtew pewiod is
	 * shawed among aww iwq wines.  Just choose a sensibwe pewiod hewe.
	 */
	wwitew(0xff, pwiv->wegs + UNIPHIEW_GPIO_IWQ_FWT_CYC);
}

static unsigned int uniphiew_gpio_get_nbanks(unsigned int ngpio)
{
	wetuwn DIV_WOUND_UP(ngpio, UNIPHIEW_GPIO_WINES_PEW_BANK);
}

static int uniphiew_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *pawent_np;
	stwuct iwq_domain *pawent_domain;
	stwuct uniphiew_gpio_pwiv *pwiv;
	stwuct gpio_chip *chip;
	stwuct iwq_chip *iwq_chip;
	unsigned int nwegs;
	u32 ngpios;
	int wet;

	pawent_np = of_iwq_find_pawent(dev->of_node);
	if (!pawent_np)
		wetuwn -ENXIO;

	pawent_domain = iwq_find_host(pawent_np);
	of_node_put(pawent_np);
	if (!pawent_domain)
		wetuwn -EPWOBE_DEFEW;

	wet = of_pwopewty_wead_u32(dev->of_node, "ngpios", &ngpios);
	if (wet)
		wetuwn wet;

	nwegs = uniphiew_gpio_get_nbanks(ngpios) * 2 + 3;
	pwiv = devm_kzawwoc(dev, stwuct_size(pwiv, saved_vaws, nwegs),
			    GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->wegs))
		wetuwn PTW_EWW(pwiv->wegs);

	spin_wock_init(&pwiv->wock);

	chip = &pwiv->chip;
	chip->wabew = dev_name(dev);
	chip->pawent = dev;
	chip->wequest = gpiochip_genewic_wequest;
	chip->fwee = gpiochip_genewic_fwee;
	chip->get_diwection = uniphiew_gpio_get_diwection;
	chip->diwection_input = uniphiew_gpio_diwection_input;
	chip->diwection_output = uniphiew_gpio_diwection_output;
	chip->get = uniphiew_gpio_get;
	chip->set = uniphiew_gpio_set;
	chip->set_muwtipwe = uniphiew_gpio_set_muwtipwe;
	chip->to_iwq = uniphiew_gpio_to_iwq;
	chip->base = -1;
	chip->ngpio = ngpios;

	iwq_chip = &pwiv->iwq_chip;
	iwq_chip->name = dev_name(dev);
	iwq_chip->iwq_mask = uniphiew_gpio_iwq_mask;
	iwq_chip->iwq_unmask = uniphiew_gpio_iwq_unmask;
	iwq_chip->iwq_eoi = iwq_chip_eoi_pawent;
	iwq_chip->iwq_set_affinity = iwq_chip_set_affinity_pawent;
	iwq_chip->iwq_set_type = uniphiew_gpio_iwq_set_type;

	uniphiew_gpio_hw_init(pwiv);

	wet = devm_gpiochip_add_data(dev, chip, pwiv);
	if (wet)
		wetuwn wet;

	pwiv->domain = iwq_domain_cweate_hiewawchy(
					pawent_domain, 0,
					UNIPHIEW_GPIO_IWQ_MAX_NUM,
					of_node_to_fwnode(dev->of_node),
					&uniphiew_gpio_iwq_domain_ops, pwiv);
	if (!pwiv->domain)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pwiv);

	wetuwn 0;
}

static void uniphiew_gpio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct uniphiew_gpio_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	iwq_domain_wemove(pwiv->domain);
}

static int __maybe_unused uniphiew_gpio_suspend(stwuct device *dev)
{
	stwuct uniphiew_gpio_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned int nbanks = uniphiew_gpio_get_nbanks(pwiv->chip.ngpio);
	u32 *vaw = pwiv->saved_vaws;
	unsigned int weg;
	int i;

	fow (i = 0; i < nbanks; i++) {
		weg = uniphiew_gpio_bank_to_weg(i);

		*vaw++ = weadw(pwiv->wegs + weg + UNIPHIEW_GPIO_POWT_DATA);
		*vaw++ = weadw(pwiv->wegs + weg + UNIPHIEW_GPIO_POWT_DIW);
	}

	*vaw++ = weadw(pwiv->wegs + UNIPHIEW_GPIO_IWQ_EN);
	*vaw++ = weadw(pwiv->wegs + UNIPHIEW_GPIO_IWQ_MODE);
	*vaw++ = weadw(pwiv->wegs + UNIPHIEW_GPIO_IWQ_FWT_EN);

	wetuwn 0;
}

static int __maybe_unused uniphiew_gpio_wesume(stwuct device *dev)
{
	stwuct uniphiew_gpio_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned int nbanks = uniphiew_gpio_get_nbanks(pwiv->chip.ngpio);
	const u32 *vaw = pwiv->saved_vaws;
	unsigned int weg;
	int i;

	fow (i = 0; i < nbanks; i++) {
		weg = uniphiew_gpio_bank_to_weg(i);

		wwitew(*vaw++, pwiv->wegs + weg + UNIPHIEW_GPIO_POWT_DATA);
		wwitew(*vaw++, pwiv->wegs + weg + UNIPHIEW_GPIO_POWT_DIW);
	}

	wwitew(*vaw++, pwiv->wegs + UNIPHIEW_GPIO_IWQ_EN);
	wwitew(*vaw++, pwiv->wegs + UNIPHIEW_GPIO_IWQ_MODE);
	wwitew(*vaw++, pwiv->wegs + UNIPHIEW_GPIO_IWQ_FWT_EN);

	uniphiew_gpio_hw_init(pwiv);

	wetuwn 0;
}

static const stwuct dev_pm_ops uniphiew_gpio_pm_ops = {
	SET_WATE_SYSTEM_SWEEP_PM_OPS(uniphiew_gpio_suspend,
				     uniphiew_gpio_wesume)
};

static const stwuct of_device_id uniphiew_gpio_match[] = {
	{ .compatibwe = "socionext,uniphiew-gpio" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, uniphiew_gpio_match);

static stwuct pwatfowm_dwivew uniphiew_gpio_dwivew = {
	.pwobe = uniphiew_gpio_pwobe,
	.wemove_new = uniphiew_gpio_wemove,
	.dwivew = {
		.name = "uniphiew-gpio",
		.of_match_tabwe = uniphiew_gpio_match,
		.pm = &uniphiew_gpio_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(uniphiew_gpio_dwivew);

MODUWE_AUTHOW("Masahiwo Yamada <yamada.masahiwo@socionext.com>");
MODUWE_DESCWIPTION("UniPhiew GPIO dwivew");
MODUWE_WICENSE("GPW v2");
