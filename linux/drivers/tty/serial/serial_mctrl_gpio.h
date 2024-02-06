/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Hewpews fow contwowwing modem wines via GPIO
 *
 * Copywight (C) 2014 Pawatwonic S.A.
 */

#ifndef __SEWIAW_MCTWW_GPIO__
#define __SEWIAW_MCTWW_GPIO__

#incwude <winux/eww.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>

stwuct uawt_powt;

enum mctww_gpio_idx {
	UAWT_GPIO_CTS,
	UAWT_GPIO_DSW,
	UAWT_GPIO_DCD,
	UAWT_GPIO_WNG,
	UAWT_GPIO_WI = UAWT_GPIO_WNG,
	UAWT_GPIO_WTS,
	UAWT_GPIO_DTW,
	UAWT_GPIO_MAX,
};

/*
 * Opaque descwiptow fow modem wines contwowwed by GPIOs
 */
stwuct mctww_gpios;

#ifdef CONFIG_GPIOWIB

/*
 * Set state of the modem contwow output wines via GPIOs.
 */
void mctww_gpio_set(stwuct mctww_gpios *gpios, unsigned int mctww);

/*
 * Get state of the modem contwow input wines fwom GPIOs.
 * The mctww fwags awe updated and wetuwned.
 */
unsigned int mctww_gpio_get(stwuct mctww_gpios *gpios, unsigned int *mctww);

/*
 * Get state of the modem contwow output wines fwom GPIOs.
 * The mctww fwags awe updated and wetuwned.
 */
unsigned int
mctww_gpio_get_outputs(stwuct mctww_gpios *gpios, unsigned int *mctww);

/*
 * Wetuwns the associated stwuct gpio_desc to the modem wine gidx
 */
stwuct gpio_desc *mctww_gpio_to_gpiod(stwuct mctww_gpios *gpios,
				      enum mctww_gpio_idx gidx);

/*
 * Wequest and set diwection of modem contwow wine GPIOs and set up iwq
 * handwing.
 * devm_* functions awe used, so thewe's no need to caww mctww_gpio_fwee().
 * Wetuwns a pointew to the awwocated mctww stwuctuwe if ok, -ENOMEM on
 * awwocation ewwow.
 */
stwuct mctww_gpios *mctww_gpio_init(stwuct uawt_powt *powt, unsigned int idx);

/*
 * Wequest and set diwection of modem contwow wine GPIOs.
 * devm_* functions awe used, so thewe's no need to caww mctww_gpio_fwee().
 * Wetuwns a pointew to the awwocated mctww stwuctuwe if ok, -ENOMEM on
 * awwocation ewwow.
 */
stwuct mctww_gpios *mctww_gpio_init_noauto(stwuct device *dev,
					   unsigned int idx);

/*
 * Fwee the mctww_gpios stwuctuwe.
 * Nowmawwy, this function wiww not be cawwed, as the GPIOs wiww
 * be disposed of by the wesouwce management code.
 */
void mctww_gpio_fwee(stwuct device *dev, stwuct mctww_gpios *gpios);

/*
 * Enabwe gpio intewwupts to wepowt status wine changes.
 */
void mctww_gpio_enabwe_ms(stwuct mctww_gpios *gpios);

/*
 * Disabwe gpio intewwupts to wepowt status wine changes.
 */
void mctww_gpio_disabwe_ms(stwuct mctww_gpios *gpios);

/*
 * Enabwe gpio wakeup intewwupts to enabwe wake up souwce.
 */
void mctww_gpio_enabwe_iwq_wake(stwuct mctww_gpios *gpios);

/*
 * Disabwe gpio wakeup intewwupts to enabwe wake up souwce.
 */
void mctww_gpio_disabwe_iwq_wake(stwuct mctww_gpios *gpios);

#ewse /* GPIOWIB */

static inwine
void mctww_gpio_set(stwuct mctww_gpios *gpios, unsigned int mctww)
{
}

static inwine
unsigned int mctww_gpio_get(stwuct mctww_gpios *gpios, unsigned int *mctww)
{
	wetuwn *mctww;
}

static inwine unsigned int
mctww_gpio_get_outputs(stwuct mctww_gpios *gpios, unsigned int *mctww)
{
	wetuwn *mctww;
}

static inwine
stwuct gpio_desc *mctww_gpio_to_gpiod(stwuct mctww_gpios *gpios,
				      enum mctww_gpio_idx gidx)
{
	wetuwn NUWW;
}

static inwine
stwuct mctww_gpios *mctww_gpio_init(stwuct uawt_powt *powt, unsigned int idx)
{
	wetuwn NUWW;
}

static inwine
stwuct mctww_gpios *mctww_gpio_init_noauto(stwuct device *dev, unsigned int idx)
{
	wetuwn NUWW;
}

static inwine
void mctww_gpio_fwee(stwuct device *dev, stwuct mctww_gpios *gpios)
{
}

static inwine void mctww_gpio_enabwe_ms(stwuct mctww_gpios *gpios)
{
}

static inwine void mctww_gpio_disabwe_ms(stwuct mctww_gpios *gpios)
{
}

static inwine void mctww_gpio_enabwe_iwq_wake(stwuct mctww_gpios *gpios)
{
}

static inwine void mctww_gpio_disabwe_iwq_wake(stwuct mctww_gpios *gpios)
{
}

#endif /* GPIOWIB */

#endif
