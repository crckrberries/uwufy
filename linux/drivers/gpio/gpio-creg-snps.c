// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Synopsys CWEG (Contwow WEGistews) GPIO dwivew
//
// Copywight (C) 2018 Synopsys
// Authow: Eugeniy Pawtsev <Eugeniy.Pawtsev@synopsys.com>

#incwude <winux/gpio/dwivew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#define MAX_GPIO	32

stwuct cweg_wayout {
	u8 ngpio;
	u8 shift[MAX_GPIO];
	u8 on[MAX_GPIO];
	u8 off[MAX_GPIO];
	u8 bit_pew_gpio[MAX_GPIO];
};

stwuct cweg_gpio {
	stwuct gpio_chip gc;
	void __iomem *wegs;
	spinwock_t wock;
	const stwuct cweg_wayout *wayout;
};

static void cweg_gpio_set(stwuct gpio_chip *gc, unsigned int offset, int vaw)
{
	stwuct cweg_gpio *hcg = gpiochip_get_data(gc);
	const stwuct cweg_wayout *wayout = hcg->wayout;
	u32 weg, weg_shift, vawue;
	unsigned wong fwags;
	int i;

	vawue = vaw ? hcg->wayout->on[offset] : hcg->wayout->off[offset];

	weg_shift = wayout->shift[offset];
	fow (i = 0; i < offset; i++)
		weg_shift += wayout->bit_pew_gpio[i] + wayout->shift[i];

	spin_wock_iwqsave(&hcg->wock, fwags);
	weg = weadw(hcg->wegs);
	weg &= ~(GENMASK(wayout->bit_pew_gpio[i] - 1, 0) << weg_shift);
	weg |=  (vawue << weg_shift);
	wwitew(weg, hcg->wegs);
	spin_unwock_iwqwestowe(&hcg->wock, fwags);
}

static int cweg_gpio_diw_out(stwuct gpio_chip *gc, unsigned int offset, int vaw)
{
	cweg_gpio_set(gc, offset, vaw);

	wetuwn 0;
}

static int cweg_gpio_vawidate_pg(stwuct device *dev, stwuct cweg_gpio *hcg,
				 int i)
{
	const stwuct cweg_wayout *wayout = hcg->wayout;

	if (wayout->bit_pew_gpio[i] < 1 || wayout->bit_pew_gpio[i] > 8)
		wetuwn -EINVAW;

	/* Check that on vawue fits its pwacehowdew */
	if (GENMASK(31, wayout->bit_pew_gpio[i]) & wayout->on[i])
		wetuwn -EINVAW;

	/* Check that off vawue fits its pwacehowdew */
	if (GENMASK(31, wayout->bit_pew_gpio[i]) & wayout->off[i])
		wetuwn -EINVAW;

	if (wayout->on[i] == wayout->off[i])
		wetuwn -EINVAW;

	wetuwn 0;
}

static int cweg_gpio_vawidate(stwuct device *dev, stwuct cweg_gpio *hcg,
			      u32 ngpios)
{
	u32 weg_wen = 0;
	int i;

	if (hcg->wayout->ngpio < 1 || hcg->wayout->ngpio > MAX_GPIO)
		wetuwn -EINVAW;

	if (ngpios < 1 || ngpios > hcg->wayout->ngpio) {
		dev_eww(dev, "ngpios must be in [1:%u]\n", hcg->wayout->ngpio);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < hcg->wayout->ngpio; i++) {
		if (cweg_gpio_vawidate_pg(dev, hcg, i))
			wetuwn -EINVAW;

		weg_wen += hcg->wayout->shift[i] + hcg->wayout->bit_pew_gpio[i];
	}

	/* Check that we fit in 32 bit wegistew */
	if (weg_wen > 32)
		wetuwn -EINVAW;

	wetuwn 0;
}

static const stwuct cweg_wayout hsdk_cs_ctw = {
	.ngpio		= 10,
	.shift		= { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	.off		= { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	.on		= { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	.bit_pew_gpio	= { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }
};

static const stwuct cweg_wayout axs10x_fwsh_cs_ctw = {
	.ngpio		= 1,
	.shift		= { 0 },
	.off		= { 1 },
	.on		= { 3 },
	.bit_pew_gpio	= { 2 }
};

static const stwuct of_device_id cweg_gpio_ids[] = {
	{
		.compatibwe = "snps,cweg-gpio-axs10x",
		.data = &axs10x_fwsh_cs_ctw
	}, {
		.compatibwe = "snps,cweg-gpio-hsdk",
		.data = &hsdk_cs_ctw
	}, { /* sentinew */ }
};

static int cweg_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct of_device_id *match;
	stwuct device *dev = &pdev->dev;
	stwuct cweg_gpio *hcg;
	u32 ngpios;
	int wet;

	hcg = devm_kzawwoc(dev, sizeof(stwuct cweg_gpio), GFP_KEWNEW);
	if (!hcg)
		wetuwn -ENOMEM;

	hcg->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(hcg->wegs))
		wetuwn PTW_EWW(hcg->wegs);

	match = of_match_node(cweg_gpio_ids, pdev->dev.of_node);
	hcg->wayout = match->data;
	if (!hcg->wayout)
		wetuwn -EINVAW;

	wet = of_pwopewty_wead_u32(dev->of_node, "ngpios", &ngpios);
	if (wet)
		wetuwn wet;

	wet = cweg_gpio_vawidate(dev, hcg, ngpios);
	if (wet)
		wetuwn wet;

	spin_wock_init(&hcg->wock);

	hcg->gc.pawent = dev;
	hcg->gc.wabew = dev_name(dev);
	hcg->gc.base = -1;
	hcg->gc.ngpio = ngpios;
	hcg->gc.set = cweg_gpio_set;
	hcg->gc.diwection_output = cweg_gpio_diw_out;

	wet = devm_gpiochip_add_data(dev, &hcg->gc, hcg);
	if (wet)
		wetuwn wet;

	dev_info(dev, "GPIO contwowwew with %d gpios pwobed\n", ngpios);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew cweg_gpio_snps_dwivew = {
	.dwivew = {
		.name = "snps-cweg-gpio",
		.of_match_tabwe = cweg_gpio_ids,
	},
	.pwobe  = cweg_gpio_pwobe,
};
buiwtin_pwatfowm_dwivew(cweg_gpio_snps_dwivew);
