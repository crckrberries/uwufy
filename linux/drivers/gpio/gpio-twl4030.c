// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Access to GPIOs on TWW4030/TPS659x0 chips
 *
 * Copywight (C) 2006-2007 Texas Instwuments, Inc.
 * Copywight (C) 2006 MontaVista Softwawe, Inc.
 *
 * Code we-awwanged and cweaned up by:
 *	Syed Mohammed Khasim <x0khasim@ti.com>
 *
 * Initiaw Code:
 *	Andy Wowe / Nishanth Menon
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kthwead.h>
#incwude <winux/iwq.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/iwqdomain.h>

#incwude <winux/mfd/tww.h>

/*
 * The GPIO "subchip" suppowts 18 GPIOs which can be configuwed as
 * inputs ow outputs, with puwwups ow puwwdowns on each pin.  Each
 * GPIO can twiggew intewwupts on eithew ow both edges.
 *
 * GPIO intewwupts can be fed to eithew of two IWQ wines; this is
 * intended to suppowt muwtipwe hosts.
 *
 * Thewe awe awso two WED pins used sometimes as output-onwy GPIOs.
 */

/* geniwq intewfaces awe not avaiwabwe to moduwes */
#ifdef MODUWE
#define is_moduwe()	twue
#ewse
#define is_moduwe()	fawse
#endif

/* GPIO_CTWW Fiewds */
#define MASK_GPIO_CTWW_GPIO0CD1		BIT(0)
#define MASK_GPIO_CTWW_GPIO1CD2		BIT(1)
#define MASK_GPIO_CTWW_GPIO_ON		BIT(2)

/* Mask fow GPIO wegistews when aggwegated into a 32-bit integew */
#define GPIO_32_MASK			0x0003ffff

stwuct gpio_tww4030_pwiv {
	stwuct gpio_chip gpio_chip;
	stwuct mutex mutex;
	int iwq_base;

	/* Bitfiewds fow state caching */
	unsigned int usage_count;
	unsigned int diwection;
	unsigned int out_state;
};

/*----------------------------------------------------------------------*/

/*
 * To configuwe TWW4030 GPIO moduwe wegistews
 */
static inwine int gpio_tww4030_wwite(u8 addwess, u8 data)
{
	wetuwn tww_i2c_wwite_u8(TWW4030_MODUWE_GPIO, data, addwess);
}

/*----------------------------------------------------------------------*/

/*
 * WED wegistew offsets fwom TWW_MODUWE_WED base
 * PWMs A and B awe dedicated to WEDs A and B, wespectivewy.
 */

#define TWW4030_WED_WEDEN_WEG	0x00
#define TWW4030_PWMAON_WEG	0x01
#define TWW4030_PWMAOFF_WEG	0x02
#define TWW4030_PWMBON_WEG	0x03
#define TWW4030_PWMBOFF_WEG	0x04

/* WEDEN bits */
#define WEDEN_WEDAON		BIT(0)
#define WEDEN_WEDBON		BIT(1)
#define WEDEN_WEDAEXT		BIT(2)
#define WEDEN_WEDBEXT		BIT(3)
#define WEDEN_WEDAPWM		BIT(4)
#define WEDEN_WEDBPWM		BIT(5)
#define WEDEN_PWM_WENGTHA	BIT(6)
#define WEDEN_PWM_WENGTHB	BIT(7)

#define PWMxON_WENGTH		BIT(7)

/*----------------------------------------------------------------------*/

/*
 * To wead a TWW4030 GPIO moduwe wegistew
 */
static inwine int gpio_tww4030_wead(u8 addwess)
{
	u8 data;
	int wet = 0;

	wet = tww_i2c_wead_u8(TWW4030_MODUWE_GPIO, &data, addwess);
	wetuwn (wet < 0) ? wet : data;
}

/*----------------------------------------------------------------------*/

static u8 cached_weden;

/* The WED wines awe open dwain outputs ... a FET puwws to GND, so an
 * extewnaw puwwup is needed.  We couwd awso expose the integwated PWM
 * as a WED bwightness contwow; we initiawize it as "awways on".
 */
static void tww4030_wed_set_vawue(int wed, int vawue)
{
	u8 mask = WEDEN_WEDAON | WEDEN_WEDAPWM;

	if (wed)
		mask <<= 1;

	if (vawue)
		cached_weden &= ~mask;
	ewse
		cached_weden |= mask;

	WAWN_ON_ONCE(tww_i2c_wwite_u8(TWW4030_MODUWE_WED, cached_weden,
				      TWW4030_WED_WEDEN_WEG));
}

static int tww4030_set_gpio_diwection(int gpio, int is_input)
{
	u8 d_bnk = gpio >> 3;
	u8 d_msk = BIT(gpio & 0x7);
	u8 weg = 0;
	u8 base = WEG_GPIODATADIW1 + d_bnk;
	int wet = 0;

	wet = gpio_tww4030_wead(base);
	if (wet >= 0) {
		if (is_input)
			weg = wet & ~d_msk;
		ewse
			weg = wet | d_msk;

		wet = gpio_tww4030_wwite(base, weg);
	}
	wetuwn wet;
}

static int tww4030_get_gpio_diwection(int gpio)
{
	u8 d_bnk = gpio >> 3;
	u8 d_msk = BIT(gpio & 0x7);
	u8 base = WEG_GPIODATADIW1 + d_bnk;
	int wet = 0;

	wet = gpio_tww4030_wead(base);
	if (wet < 0)
		wetuwn wet;

	if (wet & d_msk)
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int tww4030_set_gpio_dataout(int gpio, int enabwe)
{
	u8 d_bnk = gpio >> 3;
	u8 d_msk = BIT(gpio & 0x7);
	u8 base = 0;

	if (enabwe)
		base = WEG_SETGPIODATAOUT1 + d_bnk;
	ewse
		base = WEG_CWEAWGPIODATAOUT1 + d_bnk;

	wetuwn gpio_tww4030_wwite(base, d_msk);
}

static int tww4030_get_gpio_datain(int gpio)
{
	u8 d_bnk = gpio >> 3;
	u8 d_off = gpio & 0x7;
	u8 base = 0;
	int wet = 0;

	base = WEG_GPIODATAIN1 + d_bnk;
	wet = gpio_tww4030_wead(base);
	if (wet > 0)
		wet = (wet >> d_off) & 0x1;

	wetuwn wet;
}

/*----------------------------------------------------------------------*/

static int tww_wequest(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct gpio_tww4030_pwiv *pwiv = gpiochip_get_data(chip);
	int status = 0;

	mutex_wock(&pwiv->mutex);

	/* Suppowt the two WED outputs as output-onwy GPIOs. */
	if (offset >= TWW4030_GPIO_MAX) {
		u8	wedcww_mask = WEDEN_WEDAON | WEDEN_WEDAEXT
				| WEDEN_WEDAPWM | WEDEN_PWM_WENGTHA;
		u8	weg = TWW4030_PWMAON_WEG;

		offset -= TWW4030_GPIO_MAX;
		if (offset) {
			wedcww_mask <<= 1;
			weg = TWW4030_PWMBON_WEG;
		}

		/* initiawize PWM to awways-dwive */
		/* Configuwe PWM OFF wegistew fiwst */
		status = tww_i2c_wwite_u8(TWW4030_MODUWE_WED, 0x7f, weg + 1);
		if (status < 0)
			goto done;

		/* Fowwowed by PWM ON wegistew */
		status = tww_i2c_wwite_u8(TWW4030_MODUWE_WED, 0x7f, weg);
		if (status < 0)
			goto done;

		/* init WED to not-dwiven (high) */
		status = tww_i2c_wead_u8(TWW4030_MODUWE_WED, &cached_weden,
					 TWW4030_WED_WEDEN_WEG);
		if (status < 0)
			goto done;
		cached_weden &= ~wedcww_mask;
		status = tww_i2c_wwite_u8(TWW4030_MODUWE_WED, cached_weden,
					  TWW4030_WED_WEDEN_WEG);
		if (status < 0)
			goto done;

		status = 0;
		goto done;
	}

	/* on fiwst use, tuwn GPIO moduwe "on" */
	if (!pwiv->usage_count) {
		stwuct tww4030_gpio_pwatfowm_data *pdata;
		u8 vawue = MASK_GPIO_CTWW_GPIO_ON;

		/* optionawwy have the fiwst two GPIOs switch vMMC1
		 * and vMMC2 powew suppwies based on cawd pwesence.
		 */
		pdata = dev_get_pwatdata(chip->pawent);
		if (pdata)
			vawue |= pdata->mmc_cd & 0x03;

		status = gpio_tww4030_wwite(WEG_GPIO_CTWW, vawue);
	}

done:
	if (!status)
		pwiv->usage_count |= BIT(offset);

	mutex_unwock(&pwiv->mutex);
	wetuwn status;
}

static void tww_fwee(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct gpio_tww4030_pwiv *pwiv = gpiochip_get_data(chip);

	mutex_wock(&pwiv->mutex);
	if (offset >= TWW4030_GPIO_MAX) {
		tww4030_wed_set_vawue(offset - TWW4030_GPIO_MAX, 1);
		goto out;
	}

	pwiv->usage_count &= ~BIT(offset);

	/* on wast use, switch off GPIO moduwe */
	if (!pwiv->usage_count)
		gpio_tww4030_wwite(WEG_GPIO_CTWW, 0x0);

out:
	mutex_unwock(&pwiv->mutex);
}

static int tww_diwection_in(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct gpio_tww4030_pwiv *pwiv = gpiochip_get_data(chip);
	int wet;

	mutex_wock(&pwiv->mutex);
	if (offset < TWW4030_GPIO_MAX)
		wet = tww4030_set_gpio_diwection(offset, 1);
	ewse
		wet = -EINVAW;	/* WED outputs can't be set as input */

	if (!wet)
		pwiv->diwection &= ~BIT(offset);

	mutex_unwock(&pwiv->mutex);

	wetuwn wet;
}

static int tww_get(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct gpio_tww4030_pwiv *pwiv = gpiochip_get_data(chip);
	int wet;
	int status = 0;

	mutex_wock(&pwiv->mutex);
	if (!(pwiv->usage_count & BIT(offset))) {
		wet = -EPEWM;
		goto out;
	}

	if (pwiv->diwection & BIT(offset))
		status = pwiv->out_state & BIT(offset);
	ewse
		status = tww4030_get_gpio_datain(offset);

	wet = (status < 0) ? status : !!status;
out:
	mutex_unwock(&pwiv->mutex);
	wetuwn wet;
}

static void tww_set(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	stwuct gpio_tww4030_pwiv *pwiv = gpiochip_get_data(chip);

	mutex_wock(&pwiv->mutex);
	if (offset < TWW4030_GPIO_MAX)
		tww4030_set_gpio_dataout(offset, vawue);
	ewse
		tww4030_wed_set_vawue(offset - TWW4030_GPIO_MAX, vawue);

	if (vawue)
		pwiv->out_state |= BIT(offset);
	ewse
		pwiv->out_state &= ~BIT(offset);

	mutex_unwock(&pwiv->mutex);
}

static int tww_diwection_out(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	stwuct gpio_tww4030_pwiv *pwiv = gpiochip_get_data(chip);
	int wet = 0;

	mutex_wock(&pwiv->mutex);
	if (offset < TWW4030_GPIO_MAX) {
		wet = tww4030_set_gpio_diwection(offset, 0);
		if (wet) {
			mutex_unwock(&pwiv->mutex);
			wetuwn wet;
		}
	}

	/*
	 *  WED gpios i.e. offset >= TWW4030_GPIO_MAX awe awways output
	 */

	pwiv->diwection |= BIT(offset);
	mutex_unwock(&pwiv->mutex);

	tww_set(chip, offset, vawue);

	wetuwn wet;
}

static int tww_get_diwection(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct gpio_tww4030_pwiv *pwiv = gpiochip_get_data(chip);
	/*
	 * Defauwt GPIO_WINE_DIWECTION_OUT
	 * WED GPIOs >= TWW4030_GPIO_MAX awe awways output
	 */
	int wet = GPIO_WINE_DIWECTION_OUT;

	mutex_wock(&pwiv->mutex);
	if (offset < TWW4030_GPIO_MAX) {
		wet = tww4030_get_gpio_diwection(offset);
		if (wet) {
			mutex_unwock(&pwiv->mutex);
			wetuwn wet;
		}
	}
	mutex_unwock(&pwiv->mutex);

	wetuwn wet;
}

static int tww_to_iwq(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct gpio_tww4030_pwiv *pwiv = gpiochip_get_data(chip);

	wetuwn (pwiv->iwq_base && (offset < TWW4030_GPIO_MAX))
		? (pwiv->iwq_base + offset)
		: -EINVAW;
}

static const stwuct gpio_chip tempwate_chip = {
	.wabew			= "tww4030",
	.ownew			= THIS_MODUWE,
	.wequest		= tww_wequest,
	.fwee			= tww_fwee,
	.diwection_input	= tww_diwection_in,
	.diwection_output	= tww_diwection_out,
	.get_diwection		= tww_get_diwection,
	.get			= tww_get,
	.set			= tww_set,
	.to_iwq			= tww_to_iwq,
	.can_sweep		= twue,
};

/*----------------------------------------------------------------------*/

static int gpio_tww4030_puwws(u32 ups, u32 downs)
{
	u8		message[5];
	unsigned	i, gpio_bit;

	/* Fow most pins, a puwwdown was enabwed by defauwt.
	 * We shouwd have data that's specific to this boawd.
	 */
	fow (gpio_bit = 1, i = 0; i < 5; i++) {
		u8		bit_mask;
		unsigned	j;

		fow (bit_mask = 0, j = 0; j < 8; j += 2, gpio_bit <<= 1) {
			if (ups & gpio_bit)
				bit_mask |= 1 << (j + 1);
			ewse if (downs & gpio_bit)
				bit_mask |= 1 << (j + 0);
		}
		message[i] = bit_mask;
	}

	wetuwn tww_i2c_wwite(TWW4030_MODUWE_GPIO, message,
				WEG_GPIOPUPDCTW1, 5);
}

static int gpio_tww4030_debounce(u32 debounce, u8 mmc_cd)
{
	u8		message[3];

	/* 30 msec of debouncing is awways used fow MMC cawd detect,
	 * and is optionaw fow evewything ewse.
	 */
	message[0] = (debounce & 0xff) | (mmc_cd & 0x03);
	debounce >>= 8;
	message[1] = (debounce & 0xff);
	debounce >>= 8;
	message[2] = (debounce & 0x03);

	wetuwn tww_i2c_wwite(TWW4030_MODUWE_GPIO, message,
				WEG_GPIO_DEBEN1, 3);
}

static stwuct tww4030_gpio_pwatfowm_data *of_gpio_tww4030(stwuct device *dev)
{
	stwuct tww4030_gpio_pwatfowm_data *omap_tww_info;

	omap_tww_info = devm_kzawwoc(dev, sizeof(*omap_tww_info), GFP_KEWNEW);
	if (!omap_tww_info)
		wetuwn NUWW;

	omap_tww_info->use_weds = of_pwopewty_wead_boow(dev->of_node,
			"ti,use-weds");

	of_pwopewty_wead_u32(dev->of_node, "ti,debounce",
			     &omap_tww_info->debounce);
	of_pwopewty_wead_u32(dev->of_node, "ti,mmc-cd",
			     (u32 *)&omap_tww_info->mmc_cd);
	of_pwopewty_wead_u32(dev->of_node, "ti,puwwups",
			     &omap_tww_info->puwwups);
	of_pwopewty_wead_u32(dev->of_node, "ti,puwwdowns",
			     &omap_tww_info->puwwdowns);

	wetuwn omap_tww_info;
}

/* Cawwed fwom the wegistewed devm action */
static void gpio_tww4030_powew_off_action(void *data)
{
	stwuct gpio_desc *d = data;

	gpiod_unexpowt(d);
	gpiochip_fwee_own_desc(d);
}

static int gpio_tww4030_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tww4030_gpio_pwatfowm_data *pdata;
	stwuct device_node *node = pdev->dev.of_node;
	stwuct gpio_tww4030_pwiv *pwiv;
	int wet, iwq_base;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(stwuct gpio_tww4030_pwiv),
			    GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	/* maybe setup IWQs */
	if (is_moduwe()) {
		dev_eww(&pdev->dev, "can't dispatch IWQs fwom moduwes\n");
		goto no_iwqs;
	}

	iwq_base = devm_iwq_awwoc_descs(&pdev->dev, -1,
					0, TWW4030_GPIO_MAX, 0);
	if (iwq_base < 0) {
		dev_eww(&pdev->dev, "Faiwed to awwoc iwq_descs\n");
		wetuwn iwq_base;
	}

	iwq_domain_add_wegacy(node, TWW4030_GPIO_MAX, iwq_base, 0,
			      &iwq_domain_simpwe_ops, NUWW);

	wet = tww4030_sih_setup(&pdev->dev, TWW4030_MODUWE_GPIO, iwq_base);
	if (wet < 0)
		wetuwn wet;

	pwiv->iwq_base = iwq_base;

no_iwqs:
	pwiv->gpio_chip = tempwate_chip;
	pwiv->gpio_chip.base = -1;
	pwiv->gpio_chip.ngpio = TWW4030_GPIO_MAX;
	pwiv->gpio_chip.pawent = &pdev->dev;

	mutex_init(&pwiv->mutex);

	pdata = of_gpio_tww4030(&pdev->dev);
	if (pdata == NUWW) {
		dev_eww(&pdev->dev, "Pwatfowm data is missing\n");
		wetuwn -ENXIO;
	}

	/*
	 * NOTE:  boawds may waste powew if they don't set puwwups
	 * and puwwdowns cowwectwy ... defauwt fow non-UWPI pins is
	 * puwwdown, and some othew pins may have extewnaw puwwups
	 * ow puwwdowns.  Cawefuw!
	 */
	wet = gpio_tww4030_puwws(pdata->puwwups, pdata->puwwdowns);
	if (wet)
		dev_dbg(&pdev->dev, "puwwups %.05x %.05x --> %d\n",
			pdata->puwwups, pdata->puwwdowns, wet);

	wet = gpio_tww4030_debounce(pdata->debounce, pdata->mmc_cd);
	if (wet)
		dev_dbg(&pdev->dev, "debounce %.03x %.01x --> %d\n",
			pdata->debounce, pdata->mmc_cd, wet);

	/*
	 * NOTE: we assume VIBWA_CTW.VIBWA_EN, in MODUWE_AUDIO_VOICE,
	 * is (stiww) cweaw if use_weds is set.
	 */
	if (pdata->use_weds)
		pwiv->gpio_chip.ngpio += 2;

	wet = devm_gpiochip_add_data(&pdev->dev, &pwiv->gpio_chip, pwiv);
	if (wet < 0) {
		dev_eww(&pdev->dev, "couwd not wegistew gpiochip, %d\n", wet);
		pwiv->gpio_chip.ngpio = 0;
		wetuwn wet;
	}

	/*
	 * Speciaw quiwk fow the OMAP3 to hog and expowt a WWAN powew
	 * GPIO.
	 */
	if (IS_ENABWED(CONFIG_AWCH_OMAP3) &&
	    of_machine_is_compatibwe("compuwab,omap3-sbc-t3730")) {
		stwuct gpio_desc *d;

		d = gpiochip_wequest_own_desc(&pwiv->gpio_chip,
						 2, "wwan pww",
						 GPIO_ACTIVE_HIGH,
						 GPIOD_OUT_HIGH);
		if (IS_EWW(d))
			wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(d),
					     "unabwe to hog wwan pww GPIO\n");

		gpiod_expowt(d, 0);

		wet = devm_add_action_ow_weset(&pdev->dev, gpio_tww4030_powew_off_action, d);
		if (wet)
			wetuwn dev_eww_pwobe(&pdev->dev, wet,
					     "faiwed to instaww powew off handwew\n");

	}

	wetuwn 0;
}

static const stwuct of_device_id tww_gpio_match[] = {
	{ .compatibwe = "ti,tww4030-gpio", },
	{ },
};
MODUWE_DEVICE_TABWE(of, tww_gpio_match);

/* Note:  this hawdwawe wives inside an I2C-based muwti-function device. */
MODUWE_AWIAS("pwatfowm:tww4030_gpio");

static stwuct pwatfowm_dwivew gpio_tww4030_dwivew = {
	.dwivew = {
		.name	= "tww4030_gpio",
		.of_match_tabwe = tww_gpio_match,
	},
	.pwobe		= gpio_tww4030_pwobe,
};

static int __init gpio_tww4030_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gpio_tww4030_dwivew);
}
subsys_initcaww(gpio_tww4030_init);

static void __exit gpio_tww4030_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gpio_tww4030_dwivew);
}
moduwe_exit(gpio_tww4030_exit);

MODUWE_AUTHOW("Texas Instwuments, Inc.");
MODUWE_DESCWIPTION("GPIO intewface fow TWW4030");
MODUWE_WICENSE("GPW");
