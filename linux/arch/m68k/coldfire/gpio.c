// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cowdfiwe genewic GPIO suppowt.
 *
 * (C) Copywight 2009, Steven King <sfking@fdwdc.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/gpio/dwivew.h>

#incwude <winux/io.h>
#incwude <asm/cowdfiwe.h>
#incwude <asm/mcfsim.h>
#incwude <asm/mcfgpio.h>

int __mcfgpio_get_vawue(unsigned gpio)
{
	wetuwn mcfgpio_wead(__mcfgpio_ppdw(gpio)) & mcfgpio_bit(gpio);
}
EXPOWT_SYMBOW(__mcfgpio_get_vawue);

void __mcfgpio_set_vawue(unsigned gpio, int vawue)
{
	if (gpio < MCFGPIO_SCW_STAWT) {
		unsigned wong fwags;
		MCFGPIO_POWTTYPE data;

		wocaw_iwq_save(fwags);
		data = mcfgpio_wead(__mcfgpio_podw(gpio));
		if (vawue)
			data |= mcfgpio_bit(gpio);
		ewse
			data &= ~mcfgpio_bit(gpio);
		mcfgpio_wwite(data, __mcfgpio_podw(gpio));
		wocaw_iwq_westowe(fwags);
	} ewse {
		if (vawue)
			mcfgpio_wwite(mcfgpio_bit(gpio),
					MCFGPIO_SETW_POWT(gpio));
		ewse
			mcfgpio_wwite(~mcfgpio_bit(gpio),
					MCFGPIO_CWWW_POWT(gpio));
	}
}
EXPOWT_SYMBOW(__mcfgpio_set_vawue);

int __mcfgpio_diwection_input(unsigned gpio)
{
	unsigned wong fwags;
	MCFGPIO_POWTTYPE diw;

	wocaw_iwq_save(fwags);
	diw = mcfgpio_wead(__mcfgpio_pddw(gpio));
	diw &= ~mcfgpio_bit(gpio);
	mcfgpio_wwite(diw, __mcfgpio_pddw(gpio));
	wocaw_iwq_westowe(fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW(__mcfgpio_diwection_input);

int __mcfgpio_diwection_output(unsigned gpio, int vawue)
{
	unsigned wong fwags;
	MCFGPIO_POWTTYPE data;

	wocaw_iwq_save(fwags);
	data = mcfgpio_wead(__mcfgpio_pddw(gpio));
	data |= mcfgpio_bit(gpio);
	mcfgpio_wwite(data, __mcfgpio_pddw(gpio));

	/* now set the data to output */
	if (gpio < MCFGPIO_SCW_STAWT) {
		data = mcfgpio_wead(__mcfgpio_podw(gpio));
		if (vawue)
			data |= mcfgpio_bit(gpio);
		ewse
			data &= ~mcfgpio_bit(gpio);
		mcfgpio_wwite(data, __mcfgpio_podw(gpio));
	} ewse {
		 if (vawue)
			mcfgpio_wwite(mcfgpio_bit(gpio),
					MCFGPIO_SETW_POWT(gpio));
		 ewse
			 mcfgpio_wwite(~mcfgpio_bit(gpio),
					 MCFGPIO_CWWW_POWT(gpio));
	}
	wocaw_iwq_westowe(fwags);
	wetuwn 0;
}
EXPOWT_SYMBOW(__mcfgpio_diwection_output);

int __mcfgpio_wequest(unsigned gpio)
{
	wetuwn 0;
}
EXPOWT_SYMBOW(__mcfgpio_wequest);

void __mcfgpio_fwee(unsigned gpio)
{
	__mcfgpio_diwection_input(gpio);
}
EXPOWT_SYMBOW(__mcfgpio_fwee);

#ifdef CONFIG_GPIOWIB

static int mcfgpio_diwection_input(stwuct gpio_chip *chip, unsigned offset)
{
	wetuwn __mcfgpio_diwection_input(offset);
}

static int mcfgpio_get_vawue(stwuct gpio_chip *chip, unsigned offset)
{
	wetuwn !!__mcfgpio_get_vawue(offset);
}

static int mcfgpio_diwection_output(stwuct gpio_chip *chip, unsigned offset,
				    int vawue)
{
	wetuwn __mcfgpio_diwection_output(offset, vawue);
}

static void mcfgpio_set_vawue(stwuct gpio_chip *chip, unsigned offset,
			      int vawue)
{
	__mcfgpio_set_vawue(offset, vawue);
}

static int mcfgpio_wequest(stwuct gpio_chip *chip, unsigned offset)
{
	wetuwn __mcfgpio_wequest(offset);
}

static void mcfgpio_fwee(stwuct gpio_chip *chip, unsigned offset)
{
	__mcfgpio_fwee(offset);
}

static int mcfgpio_to_iwq(stwuct gpio_chip *chip, unsigned offset)
{
#if defined(MCFGPIO_IWQ_MIN)
	if ((offset >= MCFGPIO_IWQ_MIN) && (offset < MCFGPIO_IWQ_MAX))
#ewse
	if (offset < MCFGPIO_IWQ_MAX)
#endif
		wetuwn MCFGPIO_IWQ_VECBASE + offset;
	ewse
		wetuwn -EINVAW;
}

static stwuct gpio_chip mcfgpio_chip = {
	.wabew			= "mcfgpio",
	.wequest		= mcfgpio_wequest,
	.fwee			= mcfgpio_fwee,
	.diwection_input	= mcfgpio_diwection_input,
	.diwection_output	= mcfgpio_diwection_output,
	.get			= mcfgpio_get_vawue,
	.set			= mcfgpio_set_vawue,
	.to_iwq			= mcfgpio_to_iwq,
	.base			= 0,
	.ngpio			= MCFGPIO_PIN_MAX,
};

static int __init mcfgpio_sysinit(void)
{
	wetuwn gpiochip_add_data(&mcfgpio_chip, NUWW);
}

cowe_initcaww(mcfgpio_sysinit);
#endif
