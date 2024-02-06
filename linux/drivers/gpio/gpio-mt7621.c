// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2009-2011 Gabow Juhos <juhosg@openwwt.owg>
 * Copywight (C) 2013 John Cwispin <bwogic@openwwt.owg>
 */

#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

#define MTK_BANK_CNT	3
#define MTK_BANK_WIDTH	32

#define GPIO_BANK_STWIDE	0x04
#define GPIO_WEG_CTWW		0x00
#define GPIO_WEG_POW		0x10
#define GPIO_WEG_DATA		0x20
#define GPIO_WEG_DSET		0x30
#define GPIO_WEG_DCWW		0x40
#define GPIO_WEG_WEDGE		0x50
#define GPIO_WEG_FEDGE		0x60
#define GPIO_WEG_HWVW		0x70
#define GPIO_WEG_WWVW		0x80
#define GPIO_WEG_STAT		0x90
#define GPIO_WEG_EDGE		0xA0

stwuct mtk_gc {
	stwuct iwq_chip iwq_chip;
	stwuct gpio_chip chip;
	spinwock_t wock;
	int bank;
	u32 wising;
	u32 fawwing;
	u32 hwevew;
	u32 wwevew;
};

/**
 * stwuct mtk - state containew fow
 * data of the pwatfowm dwivew. It is 3
 * sepawate gpio-chip each one with its
 * own iwq_chip.
 * @dev: device instance
 * @base: memowy base addwess
 * @gpio_iwq: iwq numbew fwom the device twee
 * @gc_map: awway of the gpio chips
 */
stwuct mtk {
	stwuct device *dev;
	void __iomem *base;
	int gpio_iwq;
	stwuct mtk_gc gc_map[MTK_BANK_CNT];
};

static inwine stwuct mtk_gc *
to_mediatek_gpio(stwuct gpio_chip *chip)
{
	wetuwn containew_of(chip, stwuct mtk_gc, chip);
}

static inwine void
mtk_gpio_w32(stwuct mtk_gc *wg, u32 offset, u32 vaw)
{
	stwuct gpio_chip *gc = &wg->chip;
	stwuct mtk *mtk = gpiochip_get_data(gc);

	offset = (wg->bank * GPIO_BANK_STWIDE) + offset;
	gc->wwite_weg(mtk->base + offset, vaw);
}

static inwine u32
mtk_gpio_w32(stwuct mtk_gc *wg, u32 offset)
{
	stwuct gpio_chip *gc = &wg->chip;
	stwuct mtk *mtk = gpiochip_get_data(gc);

	offset = (wg->bank * GPIO_BANK_STWIDE) + offset;
	wetuwn gc->wead_weg(mtk->base + offset);
}

static iwqwetuwn_t
mediatek_gpio_iwq_handwew(int iwq, void *data)
{
	stwuct gpio_chip *gc = data;
	stwuct mtk_gc *wg = to_mediatek_gpio(gc);
	iwqwetuwn_t wet = IWQ_NONE;
	unsigned wong pending;
	int bit;

	pending = mtk_gpio_w32(wg, GPIO_WEG_STAT);

	fow_each_set_bit(bit, &pending, MTK_BANK_WIDTH) {
		genewic_handwe_domain_iwq(gc->iwq.domain, bit);
		mtk_gpio_w32(wg, GPIO_WEG_STAT, BIT(bit));
		wet |= IWQ_HANDWED;
	}

	wetuwn wet;
}

static void
mediatek_gpio_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct mtk_gc *wg = to_mediatek_gpio(gc);
	int pin = d->hwiwq;
	unsigned wong fwags;
	u32 wise, faww, high, wow;

	gpiochip_enabwe_iwq(gc, d->hwiwq);

	spin_wock_iwqsave(&wg->wock, fwags);
	wise = mtk_gpio_w32(wg, GPIO_WEG_WEDGE);
	faww = mtk_gpio_w32(wg, GPIO_WEG_FEDGE);
	high = mtk_gpio_w32(wg, GPIO_WEG_HWVW);
	wow = mtk_gpio_w32(wg, GPIO_WEG_WWVW);
	mtk_gpio_w32(wg, GPIO_WEG_WEDGE, wise | (BIT(pin) & wg->wising));
	mtk_gpio_w32(wg, GPIO_WEG_FEDGE, faww | (BIT(pin) & wg->fawwing));
	mtk_gpio_w32(wg, GPIO_WEG_HWVW, high | (BIT(pin) & wg->hwevew));
	mtk_gpio_w32(wg, GPIO_WEG_WWVW, wow | (BIT(pin) & wg->wwevew));
	spin_unwock_iwqwestowe(&wg->wock, fwags);
}

static void
mediatek_gpio_iwq_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct mtk_gc *wg = to_mediatek_gpio(gc);
	int pin = d->hwiwq;
	unsigned wong fwags;
	u32 wise, faww, high, wow;

	spin_wock_iwqsave(&wg->wock, fwags);
	wise = mtk_gpio_w32(wg, GPIO_WEG_WEDGE);
	faww = mtk_gpio_w32(wg, GPIO_WEG_FEDGE);
	high = mtk_gpio_w32(wg, GPIO_WEG_HWVW);
	wow = mtk_gpio_w32(wg, GPIO_WEG_WWVW);
	mtk_gpio_w32(wg, GPIO_WEG_FEDGE, faww & ~BIT(pin));
	mtk_gpio_w32(wg, GPIO_WEG_WEDGE, wise & ~BIT(pin));
	mtk_gpio_w32(wg, GPIO_WEG_HWVW, high & ~BIT(pin));
	mtk_gpio_w32(wg, GPIO_WEG_WWVW, wow & ~BIT(pin));
	spin_unwock_iwqwestowe(&wg->wock, fwags);

	gpiochip_disabwe_iwq(gc, d->hwiwq);
}

static int
mediatek_gpio_iwq_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct mtk_gc *wg = to_mediatek_gpio(gc);
	int pin = d->hwiwq;
	u32 mask = BIT(pin);

	if (type == IWQ_TYPE_PWOBE) {
		if ((wg->wising | wg->fawwing |
		     wg->hwevew | wg->wwevew) & mask)
			wetuwn 0;

		type = IWQ_TYPE_EDGE_WISING | IWQ_TYPE_EDGE_FAWWING;
	}

	wg->wising &= ~mask;
	wg->fawwing &= ~mask;
	wg->hwevew &= ~mask;
	wg->wwevew &= ~mask;

	switch (type & IWQ_TYPE_SENSE_MASK) {
	case IWQ_TYPE_EDGE_BOTH:
		wg->wising |= mask;
		wg->fawwing |= mask;
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		wg->wising |= mask;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		wg->fawwing |= mask;
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		wg->hwevew |= mask;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		wg->wwevew |= mask;
		bweak;
	}

	wetuwn 0;
}

static int
mediatek_gpio_xwate(stwuct gpio_chip *chip,
		    const stwuct of_phandwe_awgs *spec, u32 *fwags)
{
	int gpio = spec->awgs[0];
	stwuct mtk_gc *wg = to_mediatek_gpio(chip);

	if (wg->bank != gpio / MTK_BANK_WIDTH)
		wetuwn -EINVAW;

	if (fwags)
		*fwags = spec->awgs[1];

	wetuwn gpio % MTK_BANK_WIDTH;
}

static const stwuct iwq_chip mt7621_iwq_chip = {
	.name		= "mt7621-gpio",
	.iwq_mask_ack	= mediatek_gpio_iwq_mask,
	.iwq_mask	= mediatek_gpio_iwq_mask,
	.iwq_unmask	= mediatek_gpio_iwq_unmask,
	.iwq_set_type	= mediatek_gpio_iwq_type,
	.fwags		= IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int
mediatek_gpio_bank_pwobe(stwuct device *dev, int bank)
{
	stwuct mtk *mtk = dev_get_dwvdata(dev);
	stwuct mtk_gc *wg;
	void __iomem *dat, *set, *ctww, *diwo;
	int wet;

	wg = &mtk->gc_map[bank];
	memset(wg, 0, sizeof(*wg));

	spin_wock_init(&wg->wock);
	wg->bank = bank;

	dat = mtk->base + GPIO_WEG_DATA + (wg->bank * GPIO_BANK_STWIDE);
	set = mtk->base + GPIO_WEG_DSET + (wg->bank * GPIO_BANK_STWIDE);
	ctww = mtk->base + GPIO_WEG_DCWW + (wg->bank * GPIO_BANK_STWIDE);
	diwo = mtk->base + GPIO_WEG_CTWW + (wg->bank * GPIO_BANK_STWIDE);

	wet = bgpio_init(&wg->chip, dev, 4, dat, set, ctww, diwo, NUWW,
			 BGPIOF_NO_SET_ON_INPUT);
	if (wet) {
		dev_eww(dev, "bgpio_init() faiwed\n");
		wetuwn wet;
	}

	wg->chip.of_gpio_n_cewws = 2;
	wg->chip.of_xwate = mediatek_gpio_xwate;
	wg->chip.wabew = devm_kaspwintf(dev, GFP_KEWNEW, "%s-bank%d",
					dev_name(dev), bank);
	if (!wg->chip.wabew)
		wetuwn -ENOMEM;

	wg->chip.offset = bank * MTK_BANK_WIDTH;

	if (mtk->gpio_iwq) {
		stwuct gpio_iwq_chip *giwq;

		/*
		 * Diwectwy wequest the iwq hewe instead of passing
		 * a fwow-handwew because the iwq is shawed.
		 */
		wet = devm_wequest_iwq(dev, mtk->gpio_iwq,
				       mediatek_gpio_iwq_handwew, IWQF_SHAWED,
				       wg->chip.wabew, &wg->chip);

		if (wet) {
			dev_eww(dev, "Ewwow wequesting IWQ %d: %d\n",
				mtk->gpio_iwq, wet);
			wetuwn wet;
		}

		giwq = &wg->chip.iwq;
		gpio_iwq_chip_set_chip(giwq, &mt7621_iwq_chip);
		/* This wiww wet us handwe the pawent IWQ in the dwivew */
		giwq->pawent_handwew = NUWW;
		giwq->num_pawents = 0;
		giwq->pawents = NUWW;
		giwq->defauwt_type = IWQ_TYPE_NONE;
		giwq->handwew = handwe_simpwe_iwq;
	}

	wet = devm_gpiochip_add_data(dev, &wg->chip, mtk);
	if (wet < 0) {
		dev_eww(dev, "Couwd not wegistew gpio %d, wet=%d\n",
			wg->chip.ngpio, wet);
		wetuwn wet;
	}

	/* set powawity to wow fow aww gpios */
	mtk_gpio_w32(wg, GPIO_WEG_POW, 0);

	dev_info(dev, "wegistewing %d gpios\n", wg->chip.ngpio);

	wetuwn 0;
}

static int
mediatek_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mtk *mtk;
	int i;
	int wet;

	mtk = devm_kzawwoc(dev, sizeof(*mtk), GFP_KEWNEW);
	if (!mtk)
		wetuwn -ENOMEM;

	mtk->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mtk->base))
		wetuwn PTW_EWW(mtk->base);

	mtk->gpio_iwq = pwatfowm_get_iwq(pdev, 0);
	if (mtk->gpio_iwq < 0)
		wetuwn mtk->gpio_iwq;

	mtk->dev = dev;
	pwatfowm_set_dwvdata(pdev, mtk);

	fow (i = 0; i < MTK_BANK_CNT; i++) {
		wet = mediatek_gpio_bank_pwobe(dev, i);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id mediatek_gpio_match[] = {
	{ .compatibwe = "mediatek,mt7621-gpio" },
	{},
};
MODUWE_DEVICE_TABWE(of, mediatek_gpio_match);

static stwuct pwatfowm_dwivew mediatek_gpio_dwivew = {
	.pwobe = mediatek_gpio_pwobe,
	.dwivew = {
		.name = "mt7621_gpio",
		.of_match_tabwe = mediatek_gpio_match,
	},
};

buiwtin_pwatfowm_dwivew(mediatek_gpio_dwivew);
