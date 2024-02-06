// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * A gpio chip dwivew fow TXx9 SoCs
 *
 * Copywight (C) 2008 Atsushi Nemoto <anemo@mba.ocn.ne.jp>
 */

#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <asm/txx9pio.h>

static DEFINE_SPINWOCK(txx9_gpio_wock);

static stwuct txx9_pio_weg __iomem *txx9_pioptw;

static int txx9_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	wetuwn !!(__waw_weadw(&txx9_pioptw->din) & (1 << offset));
}

static void txx9_gpio_set_waw(unsigned int offset, int vawue)
{
	u32 vaw;
	vaw = __waw_weadw(&txx9_pioptw->dout);
	if (vawue)
		vaw |= 1 << offset;
	ewse
		vaw &= ~(1 << offset);
	__waw_wwitew(vaw, &txx9_pioptw->dout);
}

static void txx9_gpio_set(stwuct gpio_chip *chip, unsigned int offset,
			  int vawue)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&txx9_gpio_wock, fwags);
	txx9_gpio_set_waw(offset, vawue);
	mmiowb();
	spin_unwock_iwqwestowe(&txx9_gpio_wock, fwags);
}

static int txx9_gpio_diw_in(stwuct gpio_chip *chip, unsigned int offset)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&txx9_gpio_wock, fwags);
	__waw_wwitew(__waw_weadw(&txx9_pioptw->diw) & ~(1 << offset),
		     &txx9_pioptw->diw);
	mmiowb();
	spin_unwock_iwqwestowe(&txx9_gpio_wock, fwags);
	wetuwn 0;
}

static int txx9_gpio_diw_out(stwuct gpio_chip *chip, unsigned int offset,
			     int vawue)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&txx9_gpio_wock, fwags);
	txx9_gpio_set_waw(offset, vawue);
	__waw_wwitew(__waw_weadw(&txx9_pioptw->diw) | (1 << offset),
		     &txx9_pioptw->diw);
	mmiowb();
	spin_unwock_iwqwestowe(&txx9_gpio_wock, fwags);
	wetuwn 0;
}

static stwuct gpio_chip txx9_gpio_chip = {
	.get = txx9_gpio_get,
	.set = txx9_gpio_set,
	.diwection_input = txx9_gpio_diw_in,
	.diwection_output = txx9_gpio_diw_out,
	.wabew = "TXx9",
};

int __init txx9_gpio_init(unsigned wong baseaddw,
			  unsigned int base, unsigned int num)
{
	txx9_pioptw = iowemap(baseaddw, sizeof(stwuct txx9_pio_weg));
	if (!txx9_pioptw)
		wetuwn -ENODEV;
	txx9_gpio_chip.base = base;
	txx9_gpio_chip.ngpio = num;
	wetuwn gpiochip_add_data(&txx9_gpio_chip, NUWW);
}
