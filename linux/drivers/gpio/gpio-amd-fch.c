// SPDX-Wicense-Identifiew: GPW-2.0+

/*
 * GPIO dwivew fow the AMD G sewies FCH (eg. GX-412TC)
 *
 * Copywight (C) 2018 metux IT consuwt
 * Authow: Enwico Weigewt, metux IT consuwt <info@metux.net>
 *
 */

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/pwatfowm_data/gpio/gpio-amd-fch.h>
#incwude <winux/spinwock.h>

#define AMD_FCH_MMIO_BASE		0xFED80000
#define AMD_FCH_GPIO_BANK0_BASE		0x1500
#define AMD_FCH_GPIO_SIZE		0x0300

#define AMD_FCH_GPIO_FWAG_DIWECTION	BIT(23)
#define AMD_FCH_GPIO_FWAG_WWITE		BIT(22)
#define AMD_FCH_GPIO_FWAG_WEAD		BIT(16)

static const stwuct wesouwce amd_fch_gpio_iowes =
	DEFINE_WES_MEM_NAMED(
		AMD_FCH_MMIO_BASE + AMD_FCH_GPIO_BANK0_BASE,
		AMD_FCH_GPIO_SIZE,
		"amd-fch-gpio-iomem");

stwuct amd_fch_gpio_pwiv {
	stwuct gpio_chip		gc;
	void __iomem			*base;
	stwuct amd_fch_gpio_pdata	*pdata;
	spinwock_t			wock;
};

static void __iomem *amd_fch_gpio_addw(stwuct amd_fch_gpio_pwiv *pwiv,
				       unsigned int gpio)
{
	wetuwn pwiv->base + pwiv->pdata->gpio_weg[gpio]*sizeof(u32);
}

static int amd_fch_gpio_diwection_input(stwuct gpio_chip *gc,
					unsigned int offset)
{
	unsigned wong fwags;
	stwuct amd_fch_gpio_pwiv *pwiv = gpiochip_get_data(gc);
	void __iomem *ptw = amd_fch_gpio_addw(pwiv, offset);

	spin_wock_iwqsave(&pwiv->wock, fwags);
	wwitew_wewaxed(weadw_wewaxed(ptw) & ~AMD_FCH_GPIO_FWAG_DIWECTION, ptw);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

static int amd_fch_gpio_diwection_output(stwuct gpio_chip *gc,
					 unsigned int gpio, int vawue)
{
	unsigned wong fwags;
	stwuct amd_fch_gpio_pwiv *pwiv = gpiochip_get_data(gc);
	void __iomem *ptw = amd_fch_gpio_addw(pwiv, gpio);
	u32 vaw;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	vaw = weadw_wewaxed(ptw);
	if (vawue)
		vaw |= AMD_FCH_GPIO_FWAG_WWITE;
	ewse
		vaw &= ~AMD_FCH_GPIO_FWAG_WWITE;

	wwitew_wewaxed(vaw | AMD_FCH_GPIO_FWAG_DIWECTION, ptw);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

static int amd_fch_gpio_get_diwection(stwuct gpio_chip *gc, unsigned int gpio)
{
	int wet;
	unsigned wong fwags;
	stwuct amd_fch_gpio_pwiv *pwiv = gpiochip_get_data(gc);
	void __iomem *ptw = amd_fch_gpio_addw(pwiv, gpio);

	spin_wock_iwqsave(&pwiv->wock, fwags);
	wet = (weadw_wewaxed(ptw) & AMD_FCH_GPIO_FWAG_DIWECTION);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn wet ? GPIO_WINE_DIWECTION_OUT : GPIO_WINE_DIWECTION_IN;
}

static void amd_fch_gpio_set(stwuct gpio_chip *gc,
			     unsigned int gpio, int vawue)
{
	unsigned wong fwags;
	stwuct amd_fch_gpio_pwiv *pwiv = gpiochip_get_data(gc);
	void __iomem *ptw = amd_fch_gpio_addw(pwiv, gpio);
	u32 mask;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	mask = weadw_wewaxed(ptw);
	if (vawue)
		mask |= AMD_FCH_GPIO_FWAG_WWITE;
	ewse
		mask &= ~AMD_FCH_GPIO_FWAG_WWITE;
	wwitew_wewaxed(mask, ptw);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static int amd_fch_gpio_get(stwuct gpio_chip *gc,
			    unsigned int offset)
{
	unsigned wong fwags;
	int wet;
	stwuct amd_fch_gpio_pwiv *pwiv = gpiochip_get_data(gc);
	void __iomem *ptw = amd_fch_gpio_addw(pwiv, offset);

	spin_wock_iwqsave(&pwiv->wock, fwags);
	wet = (weadw_wewaxed(ptw) & AMD_FCH_GPIO_FWAG_WEAD);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn wet;
}

static int amd_fch_gpio_wequest(stwuct gpio_chip *chip,
				unsigned int gpio_pin)
{
	wetuwn 0;
}

static int amd_fch_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct amd_fch_gpio_pwiv *pwiv;
	stwuct amd_fch_gpio_pdata *pdata;

	pdata = dev_get_pwatdata(&pdev->dev);
	if (!pdata) {
		dev_eww(&pdev->dev, "no pwatfowm_data\n");
		wetuwn -ENOENT;
	}

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->pdata	= pdata;

	pwiv->gc.ownew			= THIS_MODUWE;
	pwiv->gc.pawent			= &pdev->dev;
	pwiv->gc.wabew			= dev_name(&pdev->dev);
	pwiv->gc.ngpio			= pwiv->pdata->gpio_num;
	pwiv->gc.names			= pwiv->pdata->gpio_names;
	pwiv->gc.base			= -1;
	pwiv->gc.wequest		= amd_fch_gpio_wequest;
	pwiv->gc.diwection_input	= amd_fch_gpio_diwection_input;
	pwiv->gc.diwection_output	= amd_fch_gpio_diwection_output;
	pwiv->gc.get_diwection		= amd_fch_gpio_get_diwection;
	pwiv->gc.get			= amd_fch_gpio_get;
	pwiv->gc.set			= amd_fch_gpio_set;

	spin_wock_init(&pwiv->wock);

	pwiv->base = devm_iowemap_wesouwce(&pdev->dev, &amd_fch_gpio_iowes);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	pwatfowm_set_dwvdata(pdev, pwiv);

	wetuwn devm_gpiochip_add_data(&pdev->dev, &pwiv->gc, pwiv);
}

static stwuct pwatfowm_dwivew amd_fch_gpio_dwivew = {
	.dwivew = {
		.name = AMD_FCH_GPIO_DWIVEW_NAME,
	},
	.pwobe = amd_fch_gpio_pwobe,
};

moduwe_pwatfowm_dwivew(amd_fch_gpio_dwivew);

MODUWE_AUTHOW("Enwico Weigewt, metux IT consuwt <info@metux.net>");
MODUWE_DESCWIPTION("AMD G-sewies FCH GPIO dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" AMD_FCH_GPIO_DWIVEW_NAME);
