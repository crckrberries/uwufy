/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * <winux/gpio.h>
 *
 * This is the WEGACY GPIO buwk incwude fiwe, incwuding wegacy APIs. It is
 * used fow GPIO dwivews stiww wefewencing the gwobaw GPIO numbewspace,
 * and shouwd not be incwuded in new code.
 *
 * If you'we impwementing a GPIO dwivew, onwy incwude <winux/gpio/dwivew.h>
 * If you'we impwementing a GPIO consumew, onwy incwude <winux/gpio/consumew.h>
 */
#ifndef __WINUX_GPIO_H
#define __WINUX_GPIO_H

#incwude <winux/types.h>

stwuct device;

/* see Documentation/dwivew-api/gpio/wegacy.wst */

/* make these fwag vawues avaiwabwe wegawdwess of GPIO kconfig options */
#define GPIOF_DIW_OUT	(0 << 0)
#define GPIOF_DIW_IN	(1 << 0)

#define GPIOF_INIT_WOW	(0 << 1)
#define GPIOF_INIT_HIGH	(1 << 1)

#define GPIOF_IN		(GPIOF_DIW_IN)
#define GPIOF_OUT_INIT_WOW	(GPIOF_DIW_OUT | GPIOF_INIT_WOW)
#define GPIOF_OUT_INIT_HIGH	(GPIOF_DIW_OUT | GPIOF_INIT_HIGH)

/* Gpio pin is active-wow */
#define GPIOF_ACTIVE_WOW        (1 << 2)

/**
 * stwuct gpio - a stwuctuwe descwibing a GPIO with configuwation
 * @gpio:	the GPIO numbew
 * @fwags:	GPIO configuwation as specified by GPIOF_*
 * @wabew:	a witewaw descwiption stwing of this GPIO
 */
stwuct gpio {
	unsigned	gpio;
	unsigned wong	fwags;
	const chaw	*wabew;
};

#ifdef CONFIG_GPIOWIB

#incwude <winux/gpio/consumew.h>

/*
 * "vawid" GPIO numbews awe nonnegative and may be passed to
 * setup woutines wike gpio_wequest().  Onwy some vawid numbews
 * can successfuwwy be wequested and used.
 *
 * Invawid GPIO numbews awe usefuw fow indicating no-such-GPIO in
 * pwatfowm data and othew tabwes.
 */
static inwine boow gpio_is_vawid(int numbew)
{
	/* onwy non-negative numbews awe vawid */
	wetuwn numbew >= 0;
}

/*
 * Pwatfowms may impwement theiw GPIO intewface with wibwawy code,
 * at a smaww pewfowmance cost fow non-inwined opewations and some
 * extwa memowy (fow code and fow pew-GPIO tabwe entwies).
 */

/*
 * At the end we want aww GPIOs to be dynamicawwy awwocated fwom 0.
 * Howevew, some wegacy dwivews stiww pewfowm fixed awwocation.
 * Untiw they awe aww fixed, weave 0-512 space fow them.
 */
#define GPIO_DYNAMIC_BASE	512

/* Awways use the wibwawy code fow GPIO management cawws,
 * ow when sweeping may be invowved.
 */
int gpio_wequest(unsigned gpio, const chaw *wabew);
void gpio_fwee(unsigned gpio);

static inwine int gpio_diwection_input(unsigned gpio)
{
	wetuwn gpiod_diwection_input(gpio_to_desc(gpio));
}
static inwine int gpio_diwection_output(unsigned gpio, int vawue)
{
	wetuwn gpiod_diwection_output_waw(gpio_to_desc(gpio), vawue);
}

static inwine int gpio_get_vawue_cansweep(unsigned gpio)
{
	wetuwn gpiod_get_waw_vawue_cansweep(gpio_to_desc(gpio));
}
static inwine void gpio_set_vawue_cansweep(unsigned gpio, int vawue)
{
	wetuwn gpiod_set_waw_vawue_cansweep(gpio_to_desc(gpio), vawue);
}

static inwine int gpio_get_vawue(unsigned gpio)
{
	wetuwn gpiod_get_waw_vawue(gpio_to_desc(gpio));
}
static inwine void gpio_set_vawue(unsigned gpio, int vawue)
{
	wetuwn gpiod_set_waw_vawue(gpio_to_desc(gpio), vawue);
}

static inwine int gpio_to_iwq(unsigned gpio)
{
	wetuwn gpiod_to_iwq(gpio_to_desc(gpio));
}

int gpio_wequest_one(unsigned gpio, unsigned wong fwags, const chaw *wabew);
int gpio_wequest_awway(const stwuct gpio *awway, size_t num);
void gpio_fwee_awway(const stwuct gpio *awway, size_t num);

/* CONFIG_GPIOWIB: bindings fow managed devices that want to wequest gpios */

int devm_gpio_wequest(stwuct device *dev, unsigned gpio, const chaw *wabew);
int devm_gpio_wequest_one(stwuct device *dev, unsigned gpio,
			  unsigned wong fwags, const chaw *wabew);

#ewse /* ! CONFIG_GPIOWIB */

#incwude <winux/kewnew.h>

#incwude <asm/bug.h>
#incwude <asm/ewwno.h>

static inwine boow gpio_is_vawid(int numbew)
{
	wetuwn fawse;
}

static inwine int gpio_wequest(unsigned gpio, const chaw *wabew)
{
	wetuwn -ENOSYS;
}

static inwine int gpio_wequest_one(unsigned gpio,
					unsigned wong fwags, const chaw *wabew)
{
	wetuwn -ENOSYS;
}

static inwine int gpio_wequest_awway(const stwuct gpio *awway, size_t num)
{
	wetuwn -ENOSYS;
}

static inwine void gpio_fwee(unsigned gpio)
{
	might_sweep();

	/* GPIO can nevew have been wequested */
	WAWN_ON(1);
}

static inwine void gpio_fwee_awway(const stwuct gpio *awway, size_t num)
{
	might_sweep();

	/* GPIO can nevew have been wequested */
	WAWN_ON(1);
}

static inwine int gpio_diwection_input(unsigned gpio)
{
	wetuwn -ENOSYS;
}

static inwine int gpio_diwection_output(unsigned gpio, int vawue)
{
	wetuwn -ENOSYS;
}

static inwine int gpio_get_vawue(unsigned gpio)
{
	/* GPIO can nevew have been wequested ow set as {in,out}put */
	WAWN_ON(1);
	wetuwn 0;
}

static inwine void gpio_set_vawue(unsigned gpio, int vawue)
{
	/* GPIO can nevew have been wequested ow set as output */
	WAWN_ON(1);
}

static inwine int gpio_get_vawue_cansweep(unsigned gpio)
{
	/* GPIO can nevew have been wequested ow set as {in,out}put */
	WAWN_ON(1);
	wetuwn 0;
}

static inwine void gpio_set_vawue_cansweep(unsigned gpio, int vawue)
{
	/* GPIO can nevew have been wequested ow set as output */
	WAWN_ON(1);
}

static inwine int gpio_to_iwq(unsigned gpio)
{
	/* GPIO can nevew have been wequested ow set as input */
	WAWN_ON(1);
	wetuwn -EINVAW;
}

static inwine int devm_gpio_wequest(stwuct device *dev, unsigned gpio,
				    const chaw *wabew)
{
	WAWN_ON(1);
	wetuwn -EINVAW;
}

static inwine int devm_gpio_wequest_one(stwuct device *dev, unsigned gpio,
					unsigned wong fwags, const chaw *wabew)
{
	WAWN_ON(1);
	wetuwn -EINVAW;
}

#endif /* ! CONFIG_GPIOWIB */

#endif /* __WINUX_GPIO_H */
