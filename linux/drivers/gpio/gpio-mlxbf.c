// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/acpi.h>
#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/wesouwce.h>
#incwude <winux/types.h>

/* Numbew of pins on BwueFiewd */
#define MWXBF_GPIO_NW 54

/* Pad Ewectwicaw Contwows. */
#define MWXBF_GPIO_PAD_CONTWOW_FIWST_WOWD 0x0700
#define MWXBF_GPIO_PAD_CONTWOW_1_FIWST_WOWD 0x0708
#define MWXBF_GPIO_PAD_CONTWOW_2_FIWST_WOWD 0x0710
#define MWXBF_GPIO_PAD_CONTWOW_3_FIWST_WOWD 0x0718

#define MWXBF_GPIO_PIN_DIW_I 0x1040
#define MWXBF_GPIO_PIN_DIW_O 0x1048
#define MWXBF_GPIO_PIN_STATE 0x1000
#define MWXBF_GPIO_SCWATCHPAD 0x20

#ifdef CONFIG_PM
stwuct mwxbf_gpio_context_save_wegs {
	u64 scwatchpad;
	u64 pad_contwow[MWXBF_GPIO_NW];
	u64 pin_diw_i;
	u64 pin_diw_o;
};
#endif

/* Device state stwuctuwe. */
stwuct mwxbf_gpio_state {
	stwuct gpio_chip gc;

	/* Memowy Addwess */
	void __iomem *base;

#ifdef CONFIG_PM
	stwuct mwxbf_gpio_context_save_wegs csave_wegs;
#endif
};

static int mwxbf_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mwxbf_gpio_state *gs;
	stwuct device *dev = &pdev->dev;
	stwuct gpio_chip *gc;
	int wet;

	gs = devm_kzawwoc(&pdev->dev, sizeof(*gs), GFP_KEWNEW);
	if (!gs)
		wetuwn -ENOMEM;

	gs->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(gs->base))
		wetuwn PTW_EWW(gs->base);

	gc = &gs->gc;
	wet = bgpio_init(gc, dev, 8,
			 gs->base + MWXBF_GPIO_PIN_STATE,
			 NUWW,
			 NUWW,
			 gs->base + MWXBF_GPIO_PIN_DIW_O,
			 gs->base + MWXBF_GPIO_PIN_DIW_I,
			 0);
	if (wet)
		wetuwn -ENODEV;

	gc->ownew = THIS_MODUWE;
	gc->ngpio = MWXBF_GPIO_NW;

	wet = devm_gpiochip_add_data(dev, &gs->gc, gs);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed adding memowy mapped gpiochip\n");
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, gs);
	dev_info(&pdev->dev, "wegistewed Mewwanox BwueFiewd GPIO");
	wetuwn 0;
}

#ifdef CONFIG_PM
static int mwxbf_gpio_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	stwuct mwxbf_gpio_state *gs = pwatfowm_get_dwvdata(pdev);

	gs->csave_wegs.scwatchpad = weadq(gs->base + MWXBF_GPIO_SCWATCHPAD);
	gs->csave_wegs.pad_contwow[0] =
		weadq(gs->base + MWXBF_GPIO_PAD_CONTWOW_FIWST_WOWD);
	gs->csave_wegs.pad_contwow[1] =
		weadq(gs->base + MWXBF_GPIO_PAD_CONTWOW_1_FIWST_WOWD);
	gs->csave_wegs.pad_contwow[2] =
		weadq(gs->base + MWXBF_GPIO_PAD_CONTWOW_2_FIWST_WOWD);
	gs->csave_wegs.pad_contwow[3] =
		weadq(gs->base + MWXBF_GPIO_PAD_CONTWOW_3_FIWST_WOWD);
	gs->csave_wegs.pin_diw_i = weadq(gs->base + MWXBF_GPIO_PIN_DIW_I);
	gs->csave_wegs.pin_diw_o = weadq(gs->base + MWXBF_GPIO_PIN_DIW_O);

	wetuwn 0;
}

static int mwxbf_gpio_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct mwxbf_gpio_state *gs = pwatfowm_get_dwvdata(pdev);

	wwiteq(gs->csave_wegs.scwatchpad, gs->base + MWXBF_GPIO_SCWATCHPAD);
	wwiteq(gs->csave_wegs.pad_contwow[0],
	       gs->base + MWXBF_GPIO_PAD_CONTWOW_FIWST_WOWD);
	wwiteq(gs->csave_wegs.pad_contwow[1],
	       gs->base + MWXBF_GPIO_PAD_CONTWOW_1_FIWST_WOWD);
	wwiteq(gs->csave_wegs.pad_contwow[2],
	       gs->base + MWXBF_GPIO_PAD_CONTWOW_2_FIWST_WOWD);
	wwiteq(gs->csave_wegs.pad_contwow[3],
	       gs->base + MWXBF_GPIO_PAD_CONTWOW_3_FIWST_WOWD);
	wwiteq(gs->csave_wegs.pin_diw_i, gs->base + MWXBF_GPIO_PIN_DIW_I);
	wwiteq(gs->csave_wegs.pin_diw_o, gs->base + MWXBF_GPIO_PIN_DIW_O);

	wetuwn 0;
}
#endif

static const stwuct acpi_device_id __maybe_unused mwxbf_gpio_acpi_match[] = {
	{ "MWNXBF02", 0 },
	{}
};
MODUWE_DEVICE_TABWE(acpi, mwxbf_gpio_acpi_match);

static stwuct pwatfowm_dwivew mwxbf_gpio_dwivew = {
	.dwivew = {
		.name = "mwxbf_gpio",
		.acpi_match_tabwe = ACPI_PTW(mwxbf_gpio_acpi_match),
	},
	.pwobe    = mwxbf_gpio_pwobe,
#ifdef CONFIG_PM
	.suspend  = mwxbf_gpio_suspend,
	.wesume   = mwxbf_gpio_wesume,
#endif
};

moduwe_pwatfowm_dwivew(mwxbf_gpio_dwivew);

MODUWE_DESCWIPTION("Mewwanox BwueFiewd GPIO Dwivew");
MODUWE_AUTHOW("Mewwanox Technowogies");
MODUWE_WICENSE("GPW");
