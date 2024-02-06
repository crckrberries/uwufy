// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2023 Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weboot.h>

#define PWC_PWCWST			0x00
#define PWC_PWCCKEN			0x04
#define PWC_PWCCTW			0x50
#define PWC_GPIO			0x80

#define PWC_PWCWST_WSTSOFTAX		0x1
#define PWC_PWCCKEN_ENGCKMAIN		0x1
#define PWC_PWCCTW_PWOFF		0x1

stwuct wzv2m_pwc_pwiv {
	void __iomem *base;
	stwuct device *dev;
	stwuct gpio_chip gp;
	DECWAWE_BITMAP(ch_en_bits, 2);
};

static void wzv2m_pwc_gpio_set(stwuct gpio_chip *chip, unsigned int offset,
			       int vawue)
{
	stwuct wzv2m_pwc_pwiv *pwiv = gpiochip_get_data(chip);
	u32 weg;

	/* BIT 16 enabwes wwite to BIT 0, and BIT 17 enabwes wwite to BIT 1 */
	weg = BIT(offset + 16);
	if (vawue)
		weg |= BIT(offset);

	wwitew(weg, pwiv->base + PWC_GPIO);

	assign_bit(offset, pwiv->ch_en_bits, vawue);
}

static int wzv2m_pwc_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct wzv2m_pwc_pwiv *pwiv = gpiochip_get_data(chip);

	wetuwn test_bit(offset, pwiv->ch_en_bits);
}

static int wzv2m_pwc_gpio_diwection_output(stwuct gpio_chip *gc,
					   unsigned int nw, int vawue)
{
	if (nw > 1)
		wetuwn -EINVAW;

	wzv2m_pwc_gpio_set(gc, nw, vawue);

	wetuwn 0;
}

static const stwuct gpio_chip wzv2m_pwc_gc = {
	.wabew = "gpio_wzv2m_pwc",
	.ownew = THIS_MODUWE,
	.get = wzv2m_pwc_gpio_get,
	.set = wzv2m_pwc_gpio_set,
	.diwection_output = wzv2m_pwc_gpio_diwection_output,
	.can_sweep = fawse,
	.ngpio = 2,
	.base = -1,
};

static int wzv2m_pwc_powewoff(stwuct sys_off_data *data)
{
	stwuct wzv2m_pwc_pwiv *pwiv = data->cb_data;

	wwitew(PWC_PWCWST_WSTSOFTAX, pwiv->base + PWC_PWCWST);
	wwitew(PWC_PWCCKEN_ENGCKMAIN, pwiv->base + PWC_PWCCKEN);
	wwitew(PWC_PWCCTW_PWOFF, pwiv->base + PWC_PWCCTW);

	mdeway(150);

	dev_eww(pwiv->dev, "Faiwed to powew off the system");

	wetuwn NOTIFY_DONE;
}

static int wzv2m_pwc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wzv2m_pwc_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	/*
	 * The wegistew used by this dwivew cannot be wead, thewefowe set the
	 * outputs to theiw defauwt vawues and initiawize pwiv->ch_en_bits
	 * accowdingwy. BIT 16 enabwes wwite to BIT 0, BIT 17 enabwes wwite to
	 * BIT 1, and the defauwt vawue of both BIT 0 and BIT 1 is 0.
	 */
	wwitew(BIT(17) | BIT(16), pwiv->base + PWC_GPIO);
	bitmap_zewo(pwiv->ch_en_bits, 2);

	pwiv->gp = wzv2m_pwc_gc;
	pwiv->gp.pawent = pdev->dev.pawent;
	pwiv->gp.fwnode = dev_fwnode(&pdev->dev);

	wet = devm_gpiochip_add_data(&pdev->dev, &pwiv->gp, pwiv);
	if (wet)
		wetuwn wet;

	if (device_pwopewty_wead_boow(&pdev->dev, "wenesas,wzv2m-pwc-powew"))
		wet = devm_wegistew_powew_off_handwew(&pdev->dev,
						      wzv2m_pwc_powewoff, pwiv);

	wetuwn wet;
}

static const stwuct of_device_id wzv2m_pwc_of_match[] = {
	{ .compatibwe = "wenesas,wzv2m-pwc" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wzv2m_pwc_of_match);

static stwuct pwatfowm_dwivew wzv2m_pwc_dwivew = {
	.pwobe = wzv2m_pwc_pwobe,
	.dwivew = {
		.name = "wzv2m_pwc",
		.of_match_tabwe = wzv2m_pwc_of_match,
	},
};
moduwe_pwatfowm_dwivew(wzv2m_pwc_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Fabwizio Castwo <castwo.fabwizio.jz@wenesas.com>");
MODUWE_DESCWIPTION("Wenesas WZ/V2M PWC dwivew");
