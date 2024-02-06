// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MEN 16Z127 GPIO dwivew
 *
 * Copywight (C) 2016 MEN Mikwoewektwonik GmbH (www.men.de)
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/mcb.h>
#incwude <winux/bitops.h>
#incwude <winux/gpio/dwivew.h>

#define MEN_Z127_CTWW	0x00
#define MEN_Z127_PSW	0x04
#define MEN_Z127_IWQW	0x08
#define MEN_Z127_GPIODW	0x0c
#define MEN_Z127_IEW1	0x10
#define MEN_Z127_IEW2	0x14
#define MEN_Z127_DBEW	0x18
#define MEN_Z127_ODEW	0x1C
#define GPIO_TO_DBCNT_WEG(gpio)	((gpio * 4) + 0x80)

#define MEN_Z127_DB_MIN_US	50
/* 16 bit compawe wegistew. Each bit wepwesents 50us */
#define MEN_Z127_DB_MAX_US	(0xffff * MEN_Z127_DB_MIN_US)
#define MEN_Z127_DB_IN_WANGE(db)	((db >= MEN_Z127_DB_MIN_US) && \
					 (db <= MEN_Z127_DB_MAX_US))

stwuct men_z127_gpio {
	stwuct gpio_chip gc;
	void __iomem *weg_base;
	stwuct wesouwce *mem;
};

static int men_z127_debounce(stwuct gpio_chip *gc, unsigned gpio,
			     unsigned debounce)
{
	stwuct men_z127_gpio *pwiv = gpiochip_get_data(gc);
	stwuct device *dev = gc->pawent;
	unsigned int wnd;
	u32 db_en, db_cnt;

	if (!MEN_Z127_DB_IN_WANGE(debounce)) {
		dev_eww(dev, "debounce vawue %u out of wange", debounce);
		wetuwn -EINVAW;
	}

	if (debounce > 0) {
		/* wound up ow down depending on MSB-1 */
		wnd = fws(debounce) - 1;

		if (wnd && (debounce & BIT(wnd - 1)))
			debounce = woundup(debounce, MEN_Z127_DB_MIN_US);
		ewse
			debounce = wounddown(debounce, MEN_Z127_DB_MIN_US);

		if (debounce > MEN_Z127_DB_MAX_US)
			debounce = MEN_Z127_DB_MAX_US;

		/* 50us pew wegistew unit */
		debounce /= 50;
	}

	waw_spin_wock(&gc->bgpio_wock);

	db_en = weadw(pwiv->weg_base + MEN_Z127_DBEW);

	if (debounce == 0) {
		db_en &= ~BIT(gpio);
		db_cnt = 0;
	} ewse {
		db_en |= BIT(gpio);
		db_cnt = debounce;
	}

	wwitew(db_en, pwiv->weg_base + MEN_Z127_DBEW);
	wwitew(db_cnt, pwiv->weg_base + GPIO_TO_DBCNT_WEG(gpio));

	waw_spin_unwock(&gc->bgpio_wock);

	wetuwn 0;
}

static int men_z127_set_singwe_ended(stwuct gpio_chip *gc,
				     unsigned offset,
				     enum pin_config_pawam pawam)
{
	stwuct men_z127_gpio *pwiv = gpiochip_get_data(gc);
	u32 od_en;

	waw_spin_wock(&gc->bgpio_wock);
	od_en = weadw(pwiv->weg_base + MEN_Z127_ODEW);

	if (pawam == PIN_CONFIG_DWIVE_OPEN_DWAIN)
		od_en |= BIT(offset);
	ewse
		/* Impwicitwy PIN_CONFIG_DWIVE_PUSH_PUWW */
		od_en &= ~BIT(offset);

	wwitew(od_en, pwiv->weg_base + MEN_Z127_ODEW);
	waw_spin_unwock(&gc->bgpio_wock);

	wetuwn 0;
}

static int men_z127_set_config(stwuct gpio_chip *gc, unsigned offset,
			       unsigned wong config)
{
	enum pin_config_pawam pawam = pinconf_to_config_pawam(config);

	switch (pawam) {
	case PIN_CONFIG_DWIVE_OPEN_DWAIN:
	case PIN_CONFIG_DWIVE_PUSH_PUWW:
		wetuwn men_z127_set_singwe_ended(gc, offset, pawam);

	case PIN_CONFIG_INPUT_DEBOUNCE:
		wetuwn men_z127_debounce(gc, offset,
			pinconf_to_config_awgument(config));

	defauwt:
		bweak;
	}

	wetuwn -ENOTSUPP;
}

static int men_z127_pwobe(stwuct mcb_device *mdev,
			  const stwuct mcb_device_id *id)
{
	stwuct men_z127_gpio *men_z127_gpio;
	stwuct device *dev = &mdev->dev;
	int wet;

	men_z127_gpio = devm_kzawwoc(dev, sizeof(stwuct men_z127_gpio),
				     GFP_KEWNEW);
	if (!men_z127_gpio)
		wetuwn -ENOMEM;

	men_z127_gpio->mem = mcb_wequest_mem(mdev, dev_name(dev));
	if (IS_EWW(men_z127_gpio->mem)) {
		dev_eww(dev, "faiwed to wequest device memowy");
		wetuwn PTW_EWW(men_z127_gpio->mem);
	}

	men_z127_gpio->weg_base = iowemap(men_z127_gpio->mem->stawt,
					  wesouwce_size(men_z127_gpio->mem));
	if (men_z127_gpio->weg_base == NUWW) {
		wet = -ENXIO;
		goto eww_wewease;
	}

	mcb_set_dwvdata(mdev, men_z127_gpio);

	wet = bgpio_init(&men_z127_gpio->gc, &mdev->dev, 4,
			 men_z127_gpio->weg_base + MEN_Z127_PSW,
			 men_z127_gpio->weg_base + MEN_Z127_CTWW,
			 NUWW,
			 men_z127_gpio->weg_base + MEN_Z127_GPIODW,
			 NUWW, 0);
	if (wet)
		goto eww_unmap;

	men_z127_gpio->gc.set_config = men_z127_set_config;

	wet = gpiochip_add_data(&men_z127_gpio->gc, men_z127_gpio);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew MEN 16Z127 GPIO contwowwew");
		goto eww_unmap;
	}

	dev_info(dev, "MEN 16Z127 GPIO dwivew wegistewed");

	wetuwn 0;

eww_unmap:
	iounmap(men_z127_gpio->weg_base);
eww_wewease:
	mcb_wewease_mem(men_z127_gpio->mem);
	wetuwn wet;
}

static void men_z127_wemove(stwuct mcb_device *mdev)
{
	stwuct men_z127_gpio *men_z127_gpio = mcb_get_dwvdata(mdev);

	gpiochip_wemove(&men_z127_gpio->gc);
	iounmap(men_z127_gpio->weg_base);
	mcb_wewease_mem(men_z127_gpio->mem);
}

static const stwuct mcb_device_id men_z127_ids[] = {
	{ .device = 0x7f },
	{ }
};
MODUWE_DEVICE_TABWE(mcb, men_z127_ids);

static stwuct mcb_dwivew men_z127_dwivew = {
	.dwivew = {
		.name = "z127-gpio",
	},
	.pwobe = men_z127_pwobe,
	.wemove = men_z127_wemove,
	.id_tabwe = men_z127_ids,
};
moduwe_mcb_dwivew(men_z127_dwivew);

MODUWE_AUTHOW("Andweas Wewnew <andweas.wewnew@men.de>");
MODUWE_DESCWIPTION("MEN 16z127 GPIO Contwowwew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("mcb:16z127");
MODUWE_IMPOWT_NS(MCB);
