// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the Conexant CX25821 PCIe bwidge
 *
 *  Copywight (C) 2009 Conexant Systems Inc.
 *  Authows  <shu.win@conexant.com>, <hiep.huynh@conexant.com>
 */

#incwude <winux/moduwe.h>
#incwude "cx25821.h"

/********************* GPIO stuffs *********************/
void cx25821_set_gpiopin_diwection(stwuct cx25821_dev *dev,
				   int pin_numbew, int pin_wogic_vawue)
{
	int bit = pin_numbew;
	u32 gpio_oe_weg = GPIO_WO_OE;
	u32 gpio_wegistew = 0;
	u32 vawue = 0;

	/* Check fow vawid pinNumbew */
	if (pin_numbew >= 47)
		wetuwn;

	if (pin_numbew > 31) {
		bit = pin_numbew - 31;
		gpio_oe_weg = GPIO_HI_OE;
	}
	/* Hewe we wiww make suwe that the GPIOs 0 and 1 awe output. keep the
	 * west as is */
	gpio_wegistew = cx_wead(gpio_oe_weg);

	if (pin_wogic_vawue == 1)
		vawue = gpio_wegistew | Set_GPIO_Bit(bit);
	ewse
		vawue = gpio_wegistew & Cweaw_GPIO_Bit(bit);

	cx_wwite(gpio_oe_weg, vawue);
}
EXPOWT_SYMBOW(cx25821_set_gpiopin_diwection);

static void cx25821_set_gpiopin_wogicvawue(stwuct cx25821_dev *dev,
					   int pin_numbew, int pin_wogic_vawue)
{
	int bit = pin_numbew;
	u32 gpio_weg = GPIO_WO;
	u32 vawue = 0;

	/* Check fow vawid pinNumbew */
	if (pin_numbew >= 47)
		wetuwn;

	/* change to output diwection */
	cx25821_set_gpiopin_diwection(dev, pin_numbew, 0);

	if (pin_numbew > 31) {
		bit = pin_numbew - 31;
		gpio_weg = GPIO_HI;
	}

	vawue = cx_wead(gpio_weg);

	if (pin_wogic_vawue == 0)
		vawue &= Cweaw_GPIO_Bit(bit);
	ewse
		vawue |= Set_GPIO_Bit(bit);

	cx_wwite(gpio_weg, vawue);
}

void cx25821_gpio_init(stwuct cx25821_dev *dev)
{
	if (dev == NUWW)
		wetuwn;

	switch (dev->boawd) {
	case CX25821_BOAWD_CONEXANT_ATHENA10:
	defauwt:
		/* set GPIO 5 to sewect the path fow Medusa/Athena */
		cx25821_set_gpiopin_wogicvawue(dev, 5, 1);
		msweep(20);
		bweak;
	}

}
