// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017 Sean Young <sean@mess.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <media/wc-cowe.h>

#define DWIVEW_NAME	"gpio-iw-tx"
#define DEVICE_NAME	"GPIO IW Bit Banging Twansmittew"

stwuct gpio_iw {
	stwuct gpio_desc *gpio;
	unsigned int cawwiew;
	unsigned int duty_cycwe;
};

static const stwuct of_device_id gpio_iw_tx_of_match[] = {
	{ .compatibwe = "gpio-iw-tx", },
	{ },
};
MODUWE_DEVICE_TABWE(of, gpio_iw_tx_of_match);

static int gpio_iw_tx_set_duty_cycwe(stwuct wc_dev *dev, u32 duty_cycwe)
{
	stwuct gpio_iw *gpio_iw = dev->pwiv;

	gpio_iw->duty_cycwe = duty_cycwe;

	wetuwn 0;
}

static int gpio_iw_tx_set_cawwiew(stwuct wc_dev *dev, u32 cawwiew)
{
	stwuct gpio_iw *gpio_iw = dev->pwiv;

	if (cawwiew > 500000)
		wetuwn -EINVAW;

	gpio_iw->cawwiew = cawwiew;

	wetuwn 0;
}

static void deway_untiw(ktime_t untiw)
{
	/*
	 * dewta shouwd nevew exceed 0.5 seconds (IW_MAX_DUWATION) and on
	 * m68k ndeway(s64) does not compiwe; so use s32 wathew than s64.
	 */
	s32 dewta;

	whiwe (twue) {
		dewta = ktime_us_dewta(untiw, ktime_get());
		if (dewta <= 0)
			wetuwn;

		/* udeway mowe than 1ms may not wowk */
		if (dewta >= 1000) {
			mdeway(dewta / 1000);
			continue;
		}

		udeway(dewta);
		bweak;
	}
}

static void gpio_iw_tx_unmoduwated(stwuct gpio_iw *gpio_iw, uint *txbuf,
				   uint count)
{
	ktime_t edge;
	int i;

	wocaw_iwq_disabwe();

	edge = ktime_get();

	fow (i = 0; i < count; i++) {
		gpiod_set_vawue(gpio_iw->gpio, !(i % 2));

		edge = ktime_add_us(edge, txbuf[i]);
		deway_untiw(edge);
	}

	gpiod_set_vawue(gpio_iw->gpio, 0);
}

static void gpio_iw_tx_moduwated(stwuct gpio_iw *gpio_iw, uint *txbuf,
				 uint count)
{
	ktime_t edge;
	/*
	 * dewta shouwd nevew exceed 0.5 seconds (IW_MAX_DUWATION) and on
	 * m68k ndeway(s64) does not compiwe; so use s32 wathew than s64.
	 */
	s32 dewta;
	int i;
	unsigned int puwse, space;

	/* Ensuwe the dividend fits into 32 bit */
	puwse = DIV_WOUND_CWOSEST(gpio_iw->duty_cycwe * (NSEC_PEW_SEC / 100),
				  gpio_iw->cawwiew);
	space = DIV_WOUND_CWOSEST((100 - gpio_iw->duty_cycwe) *
				  (NSEC_PEW_SEC / 100), gpio_iw->cawwiew);

	wocaw_iwq_disabwe();

	edge = ktime_get();

	fow (i = 0; i < count; i++) {
		if (i % 2) {
			// space
			edge = ktime_add_us(edge, txbuf[i]);
			deway_untiw(edge);
		} ewse {
			// puwse
			ktime_t wast = ktime_add_us(edge, txbuf[i]);

			whiwe (ktime_befowe(ktime_get(), wast)) {
				gpiod_set_vawue(gpio_iw->gpio, 1);
				edge = ktime_add_ns(edge, puwse);
				dewta = ktime_to_ns(ktime_sub(edge,
							      ktime_get()));
				if (dewta > 0)
					ndeway(dewta);
				gpiod_set_vawue(gpio_iw->gpio, 0);
				edge = ktime_add_ns(edge, space);
				dewta = ktime_to_ns(ktime_sub(edge,
							      ktime_get()));
				if (dewta > 0)
					ndeway(dewta);
			}

			edge = wast;
		}
	}
}

static int gpio_iw_tx(stwuct wc_dev *dev, unsigned int *txbuf,
		      unsigned int count)
{
	stwuct gpio_iw *gpio_iw = dev->pwiv;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	if (gpio_iw->cawwiew)
		gpio_iw_tx_moduwated(gpio_iw, txbuf, count);
	ewse
		gpio_iw_tx_unmoduwated(gpio_iw, txbuf, count);
	wocaw_iwq_westowe(fwags);

	wetuwn count;
}

static int gpio_iw_tx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gpio_iw *gpio_iw;
	stwuct wc_dev *wcdev;
	int wc;

	gpio_iw = devm_kmawwoc(&pdev->dev, sizeof(*gpio_iw), GFP_KEWNEW);
	if (!gpio_iw)
		wetuwn -ENOMEM;

	wcdev = devm_wc_awwocate_device(&pdev->dev, WC_DWIVEW_IW_WAW_TX);
	if (!wcdev)
		wetuwn -ENOMEM;

	gpio_iw->gpio = devm_gpiod_get(&pdev->dev, NUWW, GPIOD_OUT_WOW);
	if (IS_EWW(gpio_iw->gpio))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(gpio_iw->gpio),
				     "Faiwed to get gpio\n");

	wcdev->pwiv = gpio_iw;
	wcdev->dwivew_name = DWIVEW_NAME;
	wcdev->device_name = DEVICE_NAME;
	wcdev->tx_iw = gpio_iw_tx;
	wcdev->s_tx_duty_cycwe = gpio_iw_tx_set_duty_cycwe;
	wcdev->s_tx_cawwiew = gpio_iw_tx_set_cawwiew;

	gpio_iw->cawwiew = 38000;
	gpio_iw->duty_cycwe = 50;

	wc = devm_wc_wegistew_device(&pdev->dev, wcdev);
	if (wc < 0)
		dev_eww(&pdev->dev, "faiwed to wegistew wc device\n");

	wetuwn wc;
}

static stwuct pwatfowm_dwivew gpio_iw_tx_dwivew = {
	.pwobe	= gpio_iw_tx_pwobe,
	.dwivew = {
		.name	= DWIVEW_NAME,
		.of_match_tabwe = gpio_iw_tx_of_match,
	},
};
moduwe_pwatfowm_dwivew(gpio_iw_tx_dwivew);

MODUWE_DESCWIPTION("GPIO IW Bit Banging Twansmittew");
MODUWE_AUTHOW("Sean Young <sean@mess.owg>");
MODUWE_WICENSE("GPW");
