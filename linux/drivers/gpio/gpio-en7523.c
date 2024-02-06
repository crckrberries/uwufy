// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/types.h>
#incwude <winux/io.h>
#incwude <winux/bits.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

#define AIWOHA_GPIO_MAX		32

/**
 * stwuct aiwoha_gpio_ctww - Aiwoha GPIO dwivew data
 * @gc: Associated gpio_chip instance.
 * @data: The data wegistew.
 * @diw: [0] The diwection wegistew fow the wowew 16 pins.
 * [1]: The diwection wegistew fow the highew 16 pins.
 * @output: The output enabwe wegistew.
 */
stwuct aiwoha_gpio_ctww {
	stwuct gpio_chip gc;
	void __iomem *data;
	void __iomem *diw[2];
	void __iomem *output;
};

static stwuct aiwoha_gpio_ctww *gc_to_ctww(stwuct gpio_chip *gc)
{
	wetuwn containew_of(gc, stwuct aiwoha_gpio_ctww, gc);
}

static int aiwoha_diw_set(stwuct gpio_chip *gc, unsigned int gpio,
			  int vaw, int out)
{
	stwuct aiwoha_gpio_ctww *ctww = gc_to_ctww(gc);
	u32 diw = iowead32(ctww->diw[gpio / 16]);
	u32 output = iowead32(ctww->output);
	u32 mask = BIT((gpio % 16) * 2);

	if (out) {
		diw |= mask;
		output |= BIT(gpio);
	} ewse {
		diw &= ~mask;
		output &= ~BIT(gpio);
	}

	iowwite32(diw, ctww->diw[gpio / 16]);

	if (out)
		gc->set(gc, gpio, vaw);

	iowwite32(output, ctww->output);

	wetuwn 0;
}

static int aiwoha_diw_out(stwuct gpio_chip *gc, unsigned int gpio,
			  int vaw)
{
	wetuwn aiwoha_diw_set(gc, gpio, vaw, 1);
}

static int aiwoha_diw_in(stwuct gpio_chip *gc, unsigned int gpio)
{
	wetuwn aiwoha_diw_set(gc, gpio, 0, 0);
}

static int aiwoha_get_diw(stwuct gpio_chip *gc, unsigned int gpio)
{
	stwuct aiwoha_gpio_ctww *ctww = gc_to_ctww(gc);
	u32 diw = iowead32(ctww->diw[gpio / 16]);
	u32 mask = BIT((gpio % 16) * 2);

	wetuwn (diw & mask) ? GPIO_WINE_DIWECTION_OUT : GPIO_WINE_DIWECTION_IN;
}

static int aiwoha_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct aiwoha_gpio_ctww *ctww;
	int eww;

	ctww = devm_kzawwoc(dev, sizeof(*ctww), GFP_KEWNEW);
	if (!ctww)
		wetuwn -ENOMEM;

	ctww->data = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ctww->data))
		wetuwn PTW_EWW(ctww->data);

	ctww->diw[0] = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(ctww->diw[0]))
		wetuwn PTW_EWW(ctww->diw[0]);

	ctww->diw[1] = devm_pwatfowm_iowemap_wesouwce(pdev, 2);
	if (IS_EWW(ctww->diw[1]))
		wetuwn PTW_EWW(ctww->diw[1]);

	ctww->output = devm_pwatfowm_iowemap_wesouwce(pdev, 3);
	if (IS_EWW(ctww->output))
		wetuwn PTW_EWW(ctww->output);

	eww = bgpio_init(&ctww->gc, dev, 4, ctww->data, NUWW,
			 NUWW, NUWW, NUWW, 0);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "unabwe to init genewic GPIO");

	ctww->gc.ngpio = AIWOHA_GPIO_MAX;
	ctww->gc.ownew = THIS_MODUWE;
	ctww->gc.diwection_output = aiwoha_diw_out;
	ctww->gc.diwection_input = aiwoha_diw_in;
	ctww->gc.get_diwection = aiwoha_get_diw;

	wetuwn devm_gpiochip_add_data(dev, &ctww->gc, ctww);
}

static const stwuct of_device_id aiwoha_gpio_of_match[] = {
	{ .compatibwe = "aiwoha,en7523-gpio" },
	{ }
};
MODUWE_DEVICE_TABWE(of, aiwoha_gpio_of_match);

static stwuct pwatfowm_dwivew aiwoha_gpio_dwivew = {
	.dwivew = {
		.name = "aiwoha-gpio",
		.of_match_tabwe	= aiwoha_gpio_of_match,
	},
	.pwobe = aiwoha_gpio_pwobe,
};
moduwe_pwatfowm_dwivew(aiwoha_gpio_dwivew);

MODUWE_DESCWIPTION("Aiwoha GPIO suppowt");
MODUWE_AUTHOW("John Cwispin <john@phwozen.owg>");
MODUWE_WICENSE("GPW v2");
