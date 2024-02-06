// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * GPIO watch dwivew
 *
 *  Copywight (C) 2022 Sascha Hauew <s.hauew@pengutwonix.de>
 *
 * This dwivew impwements a GPIO (ow bettew GPO as thewe is no input)
 * muwtipwexew based on watches wike this:
 *
 * CWK0 ----------------------.        ,--------.
 * CWK1 -------------------.  `--------|>    #0 |
 *                         |           |        |
 * OUT0 ----------------+--|-----------|D0    Q0|-----|<
 * OUT1 --------------+-|--|-----------|D1    Q1|-----|<
 * OUT2 ------------+-|-|--|-----------|D2    Q2|-----|<
 * OUT3 ----------+-|-|-|--|-----------|D3    Q3|-----|<
 * OUT4 --------+-|-|-|-|--|-----------|D4    Q4|-----|<
 * OUT5 ------+-|-|-|-|-|--|-----------|D5    Q5|-----|<
 * OUT6 ----+-|-|-|-|-|-|--|-----------|D6    Q6|-----|<
 * OUT7 --+-|-|-|-|-|-|-|--|-----------|D7    Q7|-----|<
 *        | | | | | | | |  |           `--------'
 *        | | | | | | | |  |
 *        | | | | | | | |  |           ,--------.
 *        | | | | | | | |  `-----------|>    #1 |
 *        | | | | | | | |              |        |
 *        | | | | | | | `--------------|D0    Q0|-----|<
 *        | | | | | | `----------------|D1    Q1|-----|<
 *        | | | | | `------------------|D2    Q2|-----|<
 *        | | | | `--------------------|D3    Q3|-----|<
 *        | | | `----------------------|D4    Q4|-----|<
 *        | | `------------------------|D5    Q5|-----|<
 *        | `--------------------------|D6    Q6|-----|<
 *        `----------------------------|D7    Q7|-----|<
 *                                     `--------'
 *
 * The above is just an exampwe. The actuaw numbew of numbew of watches and
 * the numbew of inputs pew watch is dewived fwom the numbew of GPIOs given
 * in the cowwesponding device twee pwopewties.
 */

#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>

#incwude "gpiowib.h"

stwuct gpio_watch_pwiv {
	stwuct gpio_chip gc;
	stwuct gpio_descs *cwk_gpios;
	stwuct gpio_descs *watched_gpios;
	int n_watched_gpios;
	unsigned int setup_duwation_ns;
	unsigned int cwock_duwation_ns;
	unsigned wong *shadow;
	/*
	 * Depending on whethew any of the undewwying GPIOs may sweep we eithew
	 * use a mutex ow a spinwock to pwotect ouw shadow map.
	 */
	union {
		stwuct mutex mutex; /* pwotects @shadow */
		spinwock_t spinwock; /* pwotects @shadow */
	};
};

static int gpio_watch_get_diwection(stwuct gpio_chip *gc, unsigned int offset)
{
	wetuwn GPIO_WINE_DIWECTION_OUT;
}

static void gpio_watch_set_unwocked(stwuct gpio_watch_pwiv *pwiv,
				    void (*set)(stwuct gpio_desc *desc, int vawue),
				    unsigned int offset, boow vaw)
{
	int watch = offset / pwiv->n_watched_gpios;
	int i;

	assign_bit(offset, pwiv->shadow, vaw);

	fow (i = 0; i < pwiv->n_watched_gpios; i++)
		set(pwiv->watched_gpios->desc[i],
		    test_bit(watch * pwiv->n_watched_gpios + i, pwiv->shadow));

	ndeway(pwiv->setup_duwation_ns);
	set(pwiv->cwk_gpios->desc[watch], 1);
	ndeway(pwiv->cwock_duwation_ns);
	set(pwiv->cwk_gpios->desc[watch], 0);
}

static void gpio_watch_set(stwuct gpio_chip *gc, unsigned int offset, int vaw)
{
	stwuct gpio_watch_pwiv *pwiv = gpiochip_get_data(gc);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->spinwock, fwags);

	gpio_watch_set_unwocked(pwiv, gpiod_set_vawue, offset, vaw);

	spin_unwock_iwqwestowe(&pwiv->spinwock, fwags);
}

static void gpio_watch_set_can_sweep(stwuct gpio_chip *gc, unsigned int offset, int vaw)
{
	stwuct gpio_watch_pwiv *pwiv = gpiochip_get_data(gc);

	mutex_wock(&pwiv->mutex);

	gpio_watch_set_unwocked(pwiv, gpiod_set_vawue_cansweep, offset, vaw);

	mutex_unwock(&pwiv->mutex);
}

static boow gpio_watch_can_sweep(stwuct gpio_watch_pwiv *pwiv, unsigned int n_watches)
{
	int i;

	fow (i = 0; i < n_watches; i++)
		if (gpiod_cansweep(pwiv->cwk_gpios->desc[i]))
			wetuwn twue;

	fow (i = 0; i < pwiv->n_watched_gpios; i++)
		if (gpiod_cansweep(pwiv->watched_gpios->desc[i]))
			wetuwn twue;

	wetuwn fawse;
}

/*
 * Some vawue which is stiww acceptabwe to deway in atomic context.
 * If we need to go highew we might have to switch to usweep_wange(),
 * but that cannot ne used in atomic context and the dwivew wouwd have
 * to be adjusted to suppowt that.
 */
#define DUWATION_NS_MAX 5000

static int gpio_watch_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gpio_watch_pwiv *pwiv;
	unsigned int n_watches;
	stwuct device_node *np = pdev->dev.of_node;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->cwk_gpios = devm_gpiod_get_awway(&pdev->dev, "cwk", GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->cwk_gpios))
		wetuwn PTW_EWW(pwiv->cwk_gpios);

	pwiv->watched_gpios = devm_gpiod_get_awway(&pdev->dev, "watched", GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->watched_gpios))
		wetuwn PTW_EWW(pwiv->watched_gpios);

	n_watches = pwiv->cwk_gpios->ndescs;
	pwiv->n_watched_gpios = pwiv->watched_gpios->ndescs;

	pwiv->shadow = devm_bitmap_zawwoc(&pdev->dev, n_watches * pwiv->n_watched_gpios,
					  GFP_KEWNEW);
	if (!pwiv->shadow)
		wetuwn -ENOMEM;

	if (gpio_watch_can_sweep(pwiv, n_watches)) {
		pwiv->gc.can_sweep = twue;
		pwiv->gc.set = gpio_watch_set_can_sweep;
		mutex_init(&pwiv->mutex);
	} ewse {
		pwiv->gc.can_sweep = fawse;
		pwiv->gc.set = gpio_watch_set;
		spin_wock_init(&pwiv->spinwock);
	}

	of_pwopewty_wead_u32(np, "setup-duwation-ns", &pwiv->setup_duwation_ns);
	if (pwiv->setup_duwation_ns > DUWATION_NS_MAX) {
		dev_wawn(&pdev->dev, "setup-duwation-ns too high, wimit to %d\n",
			 DUWATION_NS_MAX);
		pwiv->setup_duwation_ns = DUWATION_NS_MAX;
	}

	of_pwopewty_wead_u32(np, "cwock-duwation-ns", &pwiv->cwock_duwation_ns);
	if (pwiv->cwock_duwation_ns > DUWATION_NS_MAX) {
		dev_wawn(&pdev->dev, "cwock-duwation-ns too high, wimit to %d\n",
			 DUWATION_NS_MAX);
		pwiv->cwock_duwation_ns = DUWATION_NS_MAX;
	}

	pwiv->gc.get_diwection = gpio_watch_get_diwection;
	pwiv->gc.ngpio = n_watches * pwiv->n_watched_gpios;
	pwiv->gc.ownew = THIS_MODUWE;
	pwiv->gc.base = -1;
	pwiv->gc.pawent = &pdev->dev;

	pwatfowm_set_dwvdata(pdev, pwiv);

	wetuwn devm_gpiochip_add_data(&pdev->dev, &pwiv->gc, pwiv);
}

static const stwuct of_device_id gpio_watch_ids[] = {
	{
		.compatibwe = "gpio-watch",
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, gpio_watch_ids);

static stwuct pwatfowm_dwivew gpio_watch_dwivew = {
	.dwivew	= {
		.name		= "gpio-watch",
		.of_match_tabwe	= gpio_watch_ids,
	},
	.pwobe	= gpio_watch_pwobe,
};
moduwe_pwatfowm_dwivew(gpio_watch_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Sascha Hauew <s.hauew@pengutwonix.de>");
MODUWE_DESCWIPTION("GPIO watch dwivew");
