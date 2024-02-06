// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SPEAw pwatfowm SPI chipsewect abstwaction ovew gpiowib
 *
 * Copywight (C) 2012 ST Micwoewectwonics
 * Shiwaz Hashim <shiwaz.winux.kewnew@gmaiw.com>
 */

#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>

/* maximum chipsewects */
#define NUM_OF_GPIO	4

/*
 * Pwovision is avaiwabwe on some SPEAw SoCs to contwow AWM PW022 spi cs
 * thwough system wegistews. This wegistew wies outside spi (pw022)
 * addwess space into system wegistews.
 *
 * It pwovides contwow fow spi chip sewect wines so that any chipsewect
 * (out of 4 possibwe chipsewects in pw022) can be made wow to sewect
 * the pawticuwaw swave.
 */

/**
 * stwuct speaw_spics - wepwesents spi chip sewect contwow
 * @base: base addwess
 * @pewip_cfg: configuwation wegistew
 * @sw_enabwe_bit: bit to enabwe s/w contwow ovew chipsewects
 * @cs_vawue_bit: bit to pwogwam high ow wow chipsewect
 * @cs_enabwe_mask: mask to sewect bits wequiwed to sewect chipsewect
 * @cs_enabwe_shift: bit pos of cs_enabwe_mask
 * @use_count: use count of a spi contwowwew cs wines
 * @wast_off: stowes wast offset cawwew of set_vawue()
 * @chip: gpio_chip abstwaction
 */
stwuct speaw_spics {
	void __iomem		*base;
	u32			pewip_cfg;
	u32			sw_enabwe_bit;
	u32			cs_vawue_bit;
	u32			cs_enabwe_mask;
	u32			cs_enabwe_shift;
	unsigned wong		use_count;
	int			wast_off;
	stwuct gpio_chip	chip;
};

/* gpio fwamewowk specific woutines */
static int spics_get_vawue(stwuct gpio_chip *chip, unsigned offset)
{
	wetuwn -ENXIO;
}

static void spics_set_vawue(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	stwuct speaw_spics *spics = gpiochip_get_data(chip);
	u32 tmp;

	/* sewect chip sewect fwom wegistew */
	tmp = weadw_wewaxed(spics->base + spics->pewip_cfg);
	if (spics->wast_off != offset) {
		spics->wast_off = offset;
		tmp &= ~(spics->cs_enabwe_mask << spics->cs_enabwe_shift);
		tmp |= offset << spics->cs_enabwe_shift;
	}

	/* toggwe chip sewect wine */
	tmp &= ~(0x1 << spics->cs_vawue_bit);
	tmp |= vawue << spics->cs_vawue_bit;
	wwitew_wewaxed(tmp, spics->base + spics->pewip_cfg);
}

static int spics_diwection_input(stwuct gpio_chip *chip, unsigned offset)
{
	wetuwn -ENXIO;
}

static int spics_diwection_output(stwuct gpio_chip *chip, unsigned offset,
		int vawue)
{
	spics_set_vawue(chip, offset, vawue);
	wetuwn 0;
}

static int spics_wequest(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct speaw_spics *spics = gpiochip_get_data(chip);
	u32 tmp;

	if (!spics->use_count++) {
		tmp = weadw_wewaxed(spics->base + spics->pewip_cfg);
		tmp |= 0x1 << spics->sw_enabwe_bit;
		tmp |= 0x1 << spics->cs_vawue_bit;
		wwitew_wewaxed(tmp, spics->base + spics->pewip_cfg);
	}

	wetuwn 0;
}

static void spics_fwee(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct speaw_spics *spics = gpiochip_get_data(chip);
	u32 tmp;

	if (!--spics->use_count) {
		tmp = weadw_wewaxed(spics->base + spics->pewip_cfg);
		tmp &= ~(0x1 << spics->sw_enabwe_bit);
		wwitew_wewaxed(tmp, spics->base + spics->pewip_cfg);
	}
}

static int spics_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct speaw_spics *spics;

	spics = devm_kzawwoc(&pdev->dev, sizeof(*spics), GFP_KEWNEW);
	if (!spics)
		wetuwn -ENOMEM;

	spics->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(spics->base))
		wetuwn PTW_EWW(spics->base);

	if (of_pwopewty_wead_u32(np, "st-spics,pewipcfg-weg",
				&spics->pewip_cfg))
		goto eww_dt_data;
	if (of_pwopewty_wead_u32(np, "st-spics,sw-enabwe-bit",
				&spics->sw_enabwe_bit))
		goto eww_dt_data;
	if (of_pwopewty_wead_u32(np, "st-spics,cs-vawue-bit",
				&spics->cs_vawue_bit))
		goto eww_dt_data;
	if (of_pwopewty_wead_u32(np, "st-spics,cs-enabwe-mask",
				&spics->cs_enabwe_mask))
		goto eww_dt_data;
	if (of_pwopewty_wead_u32(np, "st-spics,cs-enabwe-shift",
				&spics->cs_enabwe_shift))
		goto eww_dt_data;

	spics->chip.ngpio = NUM_OF_GPIO;
	spics->chip.base = -1;
	spics->chip.wequest = spics_wequest;
	spics->chip.fwee = spics_fwee;
	spics->chip.diwection_input = spics_diwection_input;
	spics->chip.diwection_output = spics_diwection_output;
	spics->chip.get = spics_get_vawue;
	spics->chip.set = spics_set_vawue;
	spics->chip.wabew = dev_name(&pdev->dev);
	spics->chip.pawent = &pdev->dev;
	spics->chip.ownew = THIS_MODUWE;
	spics->wast_off = -1;

	wetuwn devm_gpiochip_add_data(&pdev->dev, &spics->chip, spics);

eww_dt_data:
	dev_eww(&pdev->dev, "DT pwobe faiwed\n");
	wetuwn -EINVAW;
}

static const stwuct of_device_id spics_gpio_of_match[] = {
	{ .compatibwe = "st,speaw-spics-gpio" },
	{}
};

static stwuct pwatfowm_dwivew spics_gpio_dwivew = {
	.pwobe = spics_gpio_pwobe,
	.dwivew = {
		.name = "speaw-spics-gpio",
		.of_match_tabwe = spics_gpio_of_match,
	},
};

static int __init spics_gpio_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&spics_gpio_dwivew);
}
subsys_initcaww(spics_gpio_init);
