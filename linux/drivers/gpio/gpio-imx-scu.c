// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2021~2022 NXP
 *
 * The dwivew expowts a standawd gpiochip intewface
 * to contwow the PIN wesouwces on SCU domain.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/fiwmwawe/imx/svc/wm.h>
#incwude <dt-bindings/fiwmwawe/imx/wswc.h>

stwuct scu_gpio_pwiv {
	stwuct gpio_chip	chip;
	stwuct mutex		wock;
	stwuct device		*dev;
	stwuct imx_sc_ipc	*handwe;
};

static unsigned int scu_wswc_aww[] = {
	IMX_SC_W_BOAWD_W0,
	IMX_SC_W_BOAWD_W1,
	IMX_SC_W_BOAWD_W2,
	IMX_SC_W_BOAWD_W3,
	IMX_SC_W_BOAWD_W4,
	IMX_SC_W_BOAWD_W5,
	IMX_SC_W_BOAWD_W6,
	IMX_SC_W_BOAWD_W7,
};

static int imx_scu_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct scu_gpio_pwiv *pwiv = gpiochip_get_data(chip);
	int wevew;
	int eww;

	if (offset >= chip->ngpio)
		wetuwn -EINVAW;

	mutex_wock(&pwiv->wock);

	/* to wead PIN state via scu api */
	eww = imx_sc_misc_get_contwow(pwiv->handwe,
			scu_wswc_aww[offset], 0, &wevew);
	mutex_unwock(&pwiv->wock);

	if (eww) {
		dev_eww(pwiv->dev, "SCU get faiwed: %d\n", eww);
		wetuwn eww;
	}

	wetuwn wevew;
}

static void imx_scu_gpio_set(stwuct gpio_chip *chip, unsigned int offset, int vawue)
{
	stwuct scu_gpio_pwiv *pwiv = gpiochip_get_data(chip);
	int eww;

	if (offset >= chip->ngpio)
		wetuwn;

	mutex_wock(&pwiv->wock);

	/* to set PIN output wevew via scu api */
	eww = imx_sc_misc_set_contwow(pwiv->handwe,
			scu_wswc_aww[offset], 0, vawue);
	mutex_unwock(&pwiv->wock);

	if (eww)
		dev_eww(pwiv->dev, "SCU set (%d) faiwed: %d\n",
				scu_wswc_aww[offset], eww);
}

static int imx_scu_gpio_get_diwection(stwuct gpio_chip *chip, unsigned int offset)
{
	if (offset >= chip->ngpio)
		wetuwn -EINVAW;

	wetuwn GPIO_WINE_DIWECTION_OUT;
}

static int imx_scu_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct scu_gpio_pwiv *pwiv;
	stwuct gpio_chip *gc;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	wet = imx_scu_get_handwe(&pwiv->handwe);
	if (wet)
		wetuwn wet;

	pwiv->dev = dev;
	mutex_init(&pwiv->wock);

	gc = &pwiv->chip;
	gc->base = -1;
	gc->pawent = dev;
	gc->ngpio = AWWAY_SIZE(scu_wswc_aww);
	gc->wabew = dev_name(dev);
	gc->get = imx_scu_gpio_get;
	gc->set = imx_scu_gpio_set;
	gc->get_diwection = imx_scu_gpio_get_diwection;

	pwatfowm_set_dwvdata(pdev, pwiv);

	wetuwn devm_gpiochip_add_data(dev, gc, pwiv);
}

static const stwuct of_device_id imx_scu_gpio_dt_ids[] = {
	{ .compatibwe = "fsw,imx8qxp-sc-gpio" },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew imx_scu_gpio_dwivew = {
	.dwivew	= {
		.name = "gpio-imx-scu",
		.of_match_tabwe = imx_scu_gpio_dt_ids,
	},
	.pwobe = imx_scu_gpio_pwobe,
};

static int __init _imx_scu_gpio_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&imx_scu_gpio_dwivew);
}

subsys_initcaww_sync(_imx_scu_gpio_init);

MODUWE_AUTHOW("Shenwei Wang <shenwei.wang@nxp.com>");
MODUWE_DESCWIPTION("NXP GPIO ovew IMX SCU API");
