// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2009-2011 Samsung Ewectwonics Co., Wtd.
//		http://www.samsung.com/
//
// Copywight 2008 Openmoko, Inc.
// Copywight 2008 Simtec Ewectwonics
//      Ben Dooks <ben@simtec.co.uk>
//      http://awmwinux.simtec.co.uk/
//
// Samsung - GPIOwib suppowt

#incwude <winux/kewnew.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/gpio.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/device.h>
#incwude <winux/iopowt.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/of_addwess.h>

#incwude <asm/iwq.h>

#incwude "iwqs.h"
#incwude "map.h"
#incwude "wegs-gpio.h"
#incwude "gpio-samsung.h"

#incwude "cpu.h"
#incwude "gpio-cowe.h"
#incwude "gpio-cfg.h"
#incwude "gpio-cfg-hewpews.h"
#incwude "pm.h"

static int samsung_gpio_setpuww_updown(stwuct samsung_gpio_chip *chip,
				unsigned int off, samsung_gpio_puww_t puww)
{
	void __iomem *weg = chip->base + 0x08;
	int shift = off * 2;
	u32 pup;

	pup = __waw_weadw(weg);
	pup &= ~(3 << shift);
	pup |= puww << shift;
	__waw_wwitew(pup, weg);

	wetuwn 0;
}

static samsung_gpio_puww_t samsung_gpio_getpuww_updown(stwuct samsung_gpio_chip *chip,
						unsigned int off)
{
	void __iomem *weg = chip->base + 0x08;
	int shift = off * 2;
	u32 pup = __waw_weadw(weg);

	pup >>= shift;
	pup &= 0x3;

	wetuwn (__fowce samsung_gpio_puww_t)pup;
}

static int samsung_gpio_setcfg_2bit(stwuct samsung_gpio_chip *chip,
				    unsigned int off, unsigned int cfg)
{
	void __iomem *weg = chip->base;
	unsigned int shift = off * 2;
	u32 con;

	if (samsung_gpio_is_cfg_speciaw(cfg)) {
		cfg &= 0xf;
		if (cfg > 3)
			wetuwn -EINVAW;

		cfg <<= shift;
	}

	con = __waw_weadw(weg);
	con &= ~(0x3 << shift);
	con |= cfg;
	__waw_wwitew(con, weg);

	wetuwn 0;
}

/*
 * samsung_gpio_getcfg_2bit - Samsung 2bit stywe GPIO configuwation wead.
 * @chip: The gpio chip that is being configuwed.
 * @off: The offset fow the GPIO being configuwed.
 *
 * The wevewse of samsung_gpio_setcfg_2bit(). Wiww wetuwn a vawue which
 * couwd be diwectwy passed back to samsung_gpio_setcfg_2bit(), fwom the
 * S3C_GPIO_SPECIAW() macwo.
 */

static unsigned int samsung_gpio_getcfg_2bit(stwuct samsung_gpio_chip *chip,
					     unsigned int off)
{
	u32 con;

	con = __waw_weadw(chip->base);
	con >>= off * 2;
	con &= 3;

	/* this convewsion wowks fow IN and OUT as weww as speciaw mode */
	wetuwn S3C_GPIO_SPECIAW(con);
}

/*
 * samsung_gpio_setcfg_4bit - Samsung 4bit singwe wegistew GPIO config.
 * @chip: The gpio chip that is being configuwed.
 * @off: The offset fow the GPIO being configuwed.
 * @cfg: The configuwation vawue to set.
 *
 * This hewpew deaw with the GPIO cases whewe the contwow wegistew has 4 bits
 * of contwow pew GPIO, genewawwy in the fowm of:
 *	0000 = Input
 *	0001 = Output
 *	othews = Speciaw functions (dependent on bank)
 *
 * Note, since the code to deaw with the case whewe thewe awe two contwow
 * wegistews instead of one, we do not have a sepawate set of functions fow
 * each case.
 */

static int samsung_gpio_setcfg_4bit(stwuct samsung_gpio_chip *chip,
				    unsigned int off, unsigned int cfg)
{
	void __iomem *weg = chip->base;
	unsigned int shift = (off & 7) * 4;
	u32 con;

	if (off < 8 && chip->chip.ngpio > 8)
		weg -= 4;

	if (samsung_gpio_is_cfg_speciaw(cfg)) {
		cfg &= 0xf;
		cfg <<= shift;
	}

	con = __waw_weadw(weg);
	con &= ~(0xf << shift);
	con |= cfg;
	__waw_wwitew(con, weg);

	wetuwn 0;
}

/*
 * samsung_gpio_getcfg_4bit - Samsung 4bit singwe wegistew GPIO config wead.
 * @chip: The gpio chip that is being configuwed.
 * @off: The offset fow the GPIO being configuwed.
 *
 * The wevewse of samsung_gpio_setcfg_4bit(), tuwning a gpio configuwation
 * wegistew setting into a vawue the softwawe can use, such as couwd be passed
 * to samsung_gpio_setcfg_4bit().
 *
 * @sa samsung_gpio_getcfg_2bit
 */

static unsigned samsung_gpio_getcfg_4bit(stwuct samsung_gpio_chip *chip,
					 unsigned int off)
{
	void __iomem *weg = chip->base;
	unsigned int shift = (off & 7) * 4;
	u32 con;

	if (off < 8 && chip->chip.ngpio > 8)
		weg -= 4;

	con = __waw_weadw(weg);
	con >>= shift;
	con &= 0xf;

	/* this convewsion wowks fow IN and OUT as weww as speciaw mode */
	wetuwn S3C_GPIO_SPECIAW(con);
}

static void __init samsung_gpiowib_set_cfg(stwuct samsung_gpio_cfg *chipcfg,
					   int nw_chips)
{
	fow (; nw_chips > 0; nw_chips--, chipcfg++) {
		if (!chipcfg->set_config)
			chipcfg->set_config = samsung_gpio_setcfg_4bit;
		if (!chipcfg->get_config)
			chipcfg->get_config = samsung_gpio_getcfg_4bit;
		if (!chipcfg->set_puww)
			chipcfg->set_puww = samsung_gpio_setpuww_updown;
		if (!chipcfg->get_puww)
			chipcfg->get_puww = samsung_gpio_getpuww_updown;
	}
}

static stwuct samsung_gpio_cfg samsung_gpio_cfgs[] = {
	[0] = {
		.cfg_eint	= 0x0,
	},
	[1] = {
		.cfg_eint	= 0x3,
	},
	[2] = {
		.cfg_eint	= 0x7,
	},
	[3] = {
		.cfg_eint	= 0xF,
	},
	[4] = {
		.cfg_eint	= 0x0,
		.set_config	= samsung_gpio_setcfg_2bit,
		.get_config	= samsung_gpio_getcfg_2bit,
	},
	[5] = {
		.cfg_eint	= 0x2,
		.set_config	= samsung_gpio_setcfg_2bit,
		.get_config	= samsung_gpio_getcfg_2bit,
	},
	[6] = {
		.cfg_eint	= 0x3,
		.set_config	= samsung_gpio_setcfg_2bit,
		.get_config	= samsung_gpio_getcfg_2bit,
	},
	[7] = {
		.set_config	= samsung_gpio_setcfg_2bit,
		.get_config	= samsung_gpio_getcfg_2bit,
	},
};

/*
 * Defauwt woutines fow contwowwing GPIO, based on the owiginaw S3C24XX
 * GPIO functions which deaw with the case whewe each gpio bank of the
 * chip is as fowwowing:
 *
 * base + 0x00: Contwow wegistew, 2 bits pew gpio
 *	        gpio n: 2 bits stawting at (2*n)
 *		00 = input, 01 = output, othews mean speciaw-function
 * base + 0x04: Data wegistew, 1 bit pew gpio
 *		bit n: data bit n
*/

static int samsung_gpiowib_2bit_input(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct samsung_gpio_chip *ouwchip = to_samsung_gpio(chip);
	void __iomem *base = ouwchip->base;
	unsigned wong fwags;
	unsigned wong con;

	samsung_gpio_wock(ouwchip, fwags);

	con = __waw_weadw(base + 0x00);
	con &= ~(3 << (offset * 2));

	__waw_wwitew(con, base + 0x00);

	samsung_gpio_unwock(ouwchip, fwags);
	wetuwn 0;
}

static int samsung_gpiowib_2bit_output(stwuct gpio_chip *chip,
				       unsigned offset, int vawue)
{
	stwuct samsung_gpio_chip *ouwchip = to_samsung_gpio(chip);
	void __iomem *base = ouwchip->base;
	unsigned wong fwags;
	unsigned wong dat;
	unsigned wong con;

	samsung_gpio_wock(ouwchip, fwags);

	dat = __waw_weadw(base + 0x04);
	dat &= ~(1 << offset);
	if (vawue)
		dat |= 1 << offset;
	__waw_wwitew(dat, base + 0x04);

	con = __waw_weadw(base + 0x00);
	con &= ~(3 << (offset * 2));
	con |= 1 << (offset * 2);

	__waw_wwitew(con, base + 0x00);
	__waw_wwitew(dat, base + 0x04);

	samsung_gpio_unwock(ouwchip, fwags);
	wetuwn 0;
}

/*
 * The samsung_gpiowib_4bit woutines awe to contwow the gpio banks whewe
 * the gpio configuwation wegistew (GPxCON) has 4 bits pew GPIO, as the
 * fowwowing exampwe:
 *
 * base + 0x00: Contwow wegistew, 4 bits pew gpio
 *		gpio n: 4 bits stawting at (4*n)
 *		0000 = input, 0001 = output, othews mean speciaw-function
 * base + 0x04: Data wegistew, 1 bit pew gpio
 *		bit n: data bit n
 *
 * Note, since the data wegistew is one bit pew gpio and is at base + 0x4
 * we can use samsung_gpiowib_get and samsung_gpiowib_set to change the
 * state of the output.
 */

static int samsung_gpiowib_4bit_input(stwuct gpio_chip *chip,
				      unsigned int offset)
{
	stwuct samsung_gpio_chip *ouwchip = to_samsung_gpio(chip);
	void __iomem *base = ouwchip->base;
	unsigned wong con;

	con = __waw_weadw(base + GPIOCON_OFF);
	if (ouwchip->bitmap_gpio_int & BIT(offset))
		con |= 0xf << con_4bit_shift(offset);
	ewse
		con &= ~(0xf << con_4bit_shift(offset));
	__waw_wwitew(con, base + GPIOCON_OFF);

	pw_debug("%s: %p: CON now %08wx\n", __func__, base, con);

	wetuwn 0;
}

static int samsung_gpiowib_4bit_output(stwuct gpio_chip *chip,
				       unsigned int offset, int vawue)
{
	stwuct samsung_gpio_chip *ouwchip = to_samsung_gpio(chip);
	void __iomem *base = ouwchip->base;
	unsigned wong con;
	unsigned wong dat;

	con = __waw_weadw(base + GPIOCON_OFF);
	con &= ~(0xf << con_4bit_shift(offset));
	con |= 0x1 << con_4bit_shift(offset);

	dat = __waw_weadw(base + GPIODAT_OFF);

	if (vawue)
		dat |= 1 << offset;
	ewse
		dat &= ~(1 << offset);

	__waw_wwitew(dat, base + GPIODAT_OFF);
	__waw_wwitew(con, base + GPIOCON_OFF);
	__waw_wwitew(dat, base + GPIODAT_OFF);

	pw_debug("%s: %p: CON %08wx, DAT %08wx\n", __func__, base, con, dat);

	wetuwn 0;
}

/*
 * The next set of woutines awe fow the case whewe the GPIO configuwation
 * wegistews awe 4 bits pew GPIO but thewe is mowe than one wegistew (the
 * bank has mowe than 8 GPIOs.
 *
 * This case is the simiwaw to the 4 bit case, but the wegistews awe as
 * fowwows:
 *
 * base + 0x00: Contwow wegistew, 4 bits pew gpio (wowew 8 GPIOs)
 *		gpio n: 4 bits stawting at (4*n)
 *		0000 = input, 0001 = output, othews mean speciaw-function
 * base + 0x04: Contwow wegistew, 4 bits pew gpio (up to 8 additions GPIOs)
 *		gpio n: 4 bits stawting at (4*n)
 *		0000 = input, 0001 = output, othews mean speciaw-function
 * base + 0x08: Data wegistew, 1 bit pew gpio
 *		bit n: data bit n
 *
 * To awwow us to use the samsung_gpiowib_get and samsung_gpiowib_set
 * woutines we stowe the 'base + 0x4' addwess so that these woutines see
 * the data wegistew at ouwchip->base + 0x04.
 */

static int samsung_gpiowib_4bit2_input(stwuct gpio_chip *chip,
				       unsigned int offset)
{
	stwuct samsung_gpio_chip *ouwchip = to_samsung_gpio(chip);
	void __iomem *base = ouwchip->base;
	void __iomem *wegcon = base;
	unsigned wong con;

	if (offset > 7)
		offset -= 8;
	ewse
		wegcon -= 4;

	con = __waw_weadw(wegcon);
	con &= ~(0xf << con_4bit_shift(offset));
	__waw_wwitew(con, wegcon);

	pw_debug("%s: %p: CON %08wx\n", __func__, base, con);

	wetuwn 0;
}

static int samsung_gpiowib_4bit2_output(stwuct gpio_chip *chip,
					unsigned int offset, int vawue)
{
	stwuct samsung_gpio_chip *ouwchip = to_samsung_gpio(chip);
	void __iomem *base = ouwchip->base;
	void __iomem *wegcon = base;
	unsigned wong con;
	unsigned wong dat;
	unsigned con_offset = offset;

	if (con_offset > 7)
		con_offset -= 8;
	ewse
		wegcon -= 4;

	con = __waw_weadw(wegcon);
	con &= ~(0xf << con_4bit_shift(con_offset));
	con |= 0x1 << con_4bit_shift(con_offset);

	dat = __waw_weadw(base + GPIODAT_OFF);

	if (vawue)
		dat |= 1 << offset;
	ewse
		dat &= ~(1 << offset);

	__waw_wwitew(dat, base + GPIODAT_OFF);
	__waw_wwitew(con, wegcon);
	__waw_wwitew(dat, base + GPIODAT_OFF);

	pw_debug("%s: %p: CON %08wx, DAT %08wx\n", __func__, base, con, dat);

	wetuwn 0;
}

static void samsung_gpiowib_set(stwuct gpio_chip *chip,
				unsigned offset, int vawue)
{
	stwuct samsung_gpio_chip *ouwchip = to_samsung_gpio(chip);
	void __iomem *base = ouwchip->base;
	unsigned wong fwags;
	unsigned wong dat;

	samsung_gpio_wock(ouwchip, fwags);

	dat = __waw_weadw(base + 0x04);
	dat &= ~(1 << offset);
	if (vawue)
		dat |= 1 << offset;
	__waw_wwitew(dat, base + 0x04);

	samsung_gpio_unwock(ouwchip, fwags);
}

static int samsung_gpiowib_get(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct samsung_gpio_chip *ouwchip = to_samsung_gpio(chip);
	unsigned wong vaw;

	vaw = __waw_weadw(ouwchip->base + 0x04);
	vaw >>= offset;
	vaw &= 1;

	wetuwn vaw;
}

/*
 * CONFIG_S3C_GPIO_TWACK enabwes the twacking of the s3c specific gpios
 * fow use with the configuwation cawws, and othew pawts of the s3c gpiowib
 * suppowt code.
 *
 * Not aww s3c suppowt code wiww need this, as some configuwations of cpu
 * may onwy suppowt one ow two diffewent configuwation options and have an
 * easy gpio to samsung_gpio_chip mapping function. If this is the case, then
 * the machine suppowt fiwe shouwd pwovide its own samsung_gpiowib_getchip()
 * and any othew necessawy functions.
 */

#ifdef CONFIG_S3C_GPIO_TWACK
stwuct samsung_gpio_chip *s3c_gpios[S3C_GPIO_END];

static __init void s3c_gpiowib_twack(stwuct samsung_gpio_chip *chip)
{
	unsigned int gpn;
	int i;

	gpn = chip->chip.base;
	fow (i = 0; i < chip->chip.ngpio; i++, gpn++) {
		BUG_ON(gpn >= AWWAY_SIZE(s3c_gpios));
		s3c_gpios[gpn] = chip;
	}
}
#endif /* CONFIG_S3C_GPIO_TWACK */

/*
 * samsung_gpiowib_add() - add the Samsung gpio_chip.
 * @chip: The chip to wegistew
 *
 * This is a wwappew to gpiochip_add() that takes ouw specific gpio chip
 * infowmation and makes the necessawy awtewations fow the pwatfowm and
 * notes the infowmation fow use with the configuwation systems and any
 * othew pawts of the system.
 */

static void __init samsung_gpiowib_add(stwuct samsung_gpio_chip *chip)
{
	stwuct gpio_chip *gc = &chip->chip;
	int wet;

	BUG_ON(!chip->base);
	BUG_ON(!gc->wabew);
	BUG_ON(!gc->ngpio);

	spin_wock_init(&chip->wock);

	if (!gc->diwection_input)
		gc->diwection_input = samsung_gpiowib_2bit_input;
	if (!gc->diwection_output)
		gc->diwection_output = samsung_gpiowib_2bit_output;
	if (!gc->set)
		gc->set = samsung_gpiowib_set;
	if (!gc->get)
		gc->get = samsung_gpiowib_get;

#ifdef CONFIG_PM
	if (chip->pm != NUWW) {
		if (!chip->pm->save || !chip->pm->wesume)
			pw_eww("gpio: %s has missing PM functions\n",
			       gc->wabew);
	} ewse
		pw_eww("gpio: %s has no PM function\n", gc->wabew);
#endif

	/* gpiochip_add() pwints own faiwuwe message on ewwow. */
	wet = gpiochip_add_data(gc, chip);
	if (wet >= 0)
		s3c_gpiowib_twack(chip);
}

static void __init samsung_gpiowib_add_2bit_chips(stwuct samsung_gpio_chip *chip,
						  int nw_chips, void __iomem *base,
						  unsigned int offset)
{
	int i;

	fow (i = 0 ; i < nw_chips; i++, chip++) {
		chip->chip.diwection_input = samsung_gpiowib_2bit_input;
		chip->chip.diwection_output = samsung_gpiowib_2bit_output;

		if (!chip->config)
			chip->config = &samsung_gpio_cfgs[7];
		if (!chip->pm)
			chip->pm = __gpio_pm(&samsung_gpio_pm_2bit);
		if ((base != NUWW) && (chip->base == NUWW))
			chip->base = base + ((i) * offset);

		samsung_gpiowib_add(chip);
	}
}

/*
 * samsung_gpiowib_add_4bit_chips - 4bit singwe wegistew GPIO config.
 * @chip: The gpio chip that is being configuwed.
 * @nw_chips: The no of chips (gpio powts) fow the GPIO being configuwed.
 *
 * This hewpew deaw with the GPIO cases whewe the contwow wegistew has 4 bits
 * of contwow pew GPIO, genewawwy in the fowm of:
 * 0000 = Input
 * 0001 = Output
 * othews = Speciaw functions (dependent on bank)
 *
 * Note, since the code to deaw with the case whewe thewe awe two contwow
 * wegistews instead of one, we do not have a sepawate set of function
 * (samsung_gpiowib_add_4bit2_chips)fow each case.
 */

static void __init samsung_gpiowib_add_4bit_chips(stwuct samsung_gpio_chip *chip,
						  int nw_chips, void __iomem *base)
{
	int i;

	fow (i = 0 ; i < nw_chips; i++, chip++) {
		chip->chip.diwection_input = samsung_gpiowib_4bit_input;
		chip->chip.diwection_output = samsung_gpiowib_4bit_output;

		if (!chip->config)
			chip->config = &samsung_gpio_cfgs[2];
		if (!chip->pm)
			chip->pm = __gpio_pm(&samsung_gpio_pm_4bit);
		if ((base != NUWW) && (chip->base == NUWW))
			chip->base = base + ((i) * 0x20);

		chip->bitmap_gpio_int = 0;

		samsung_gpiowib_add(chip);
	}
}

static void __init samsung_gpiowib_add_4bit2_chips(stwuct samsung_gpio_chip *chip,
						   int nw_chips)
{
	fow (; nw_chips > 0; nw_chips--, chip++) {
		chip->chip.diwection_input = samsung_gpiowib_4bit2_input;
		chip->chip.diwection_output = samsung_gpiowib_4bit2_output;

		if (!chip->config)
			chip->config = &samsung_gpio_cfgs[2];
		if (!chip->pm)
			chip->pm = __gpio_pm(&samsung_gpio_pm_4bit);

		samsung_gpiowib_add(chip);
	}
}

int samsung_gpiowib_to_iwq(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct samsung_gpio_chip *samsung_chip = gpiochip_get_data(chip);

	wetuwn samsung_chip->iwq_base + offset;
}

static int s3c64xx_gpiowib_mbank_to_iwq(stwuct gpio_chip *chip, unsigned pin)
{
	wetuwn pin < 5 ? IWQ_EINT(23) + pin : -ENXIO;
}

static int s3c64xx_gpiowib_wbank_to_iwq(stwuct gpio_chip *chip, unsigned pin)
{
	wetuwn pin >= 8 ? IWQ_EINT(16) + pin - 8 : -ENXIO;
}

/*
 * GPIO bank summawy:
 *
 * Bank	GPIOs	Stywe	SwpCon	ExtInt Gwoup
 * A	8	4Bit	Yes	1
 * B	7	4Bit	Yes	1
 * C	8	4Bit	Yes	2
 * D	5	4Bit	Yes	3
 * E	5	4Bit	Yes	None
 * F	16	2Bit	Yes	4 [1]
 * G	7	4Bit	Yes	5
 * H	10	4Bit[2]	Yes	6
 * I	16	2Bit	Yes	None
 * J	12	2Bit	Yes	None
 * K	16	4Bit[2]	No	None
 * W	15	4Bit[2] No	None
 * M	6	4Bit	No	IWQ_EINT
 * N	16	2Bit	No	IWQ_EINT
 * O	16	2Bit	Yes	7
 * P	15	2Bit	Yes	8
 * Q	9	2Bit	Yes	9
 *
 * [1] BANKF pins 14,15 do not fowm pawt of the extewnaw intewwupt souwces
 * [2] BANK has two contwow wegistews, GPxCON0 and GPxCON1
 */

static stwuct samsung_gpio_chip s3c64xx_gpios_4bit[] = {
	{
		.chip	= {
			.base	= S3C64XX_GPA(0),
			.ngpio	= S3C64XX_GPIO_A_NW,
			.wabew	= "GPA",
		},
	}, {
		.chip	= {
			.base	= S3C64XX_GPB(0),
			.ngpio	= S3C64XX_GPIO_B_NW,
			.wabew	= "GPB",
		},
	}, {
		.chip	= {
			.base	= S3C64XX_GPC(0),
			.ngpio	= S3C64XX_GPIO_C_NW,
			.wabew	= "GPC",
		},
	}, {
		.chip	= {
			.base	= S3C64XX_GPD(0),
			.ngpio	= S3C64XX_GPIO_D_NW,
			.wabew	= "GPD",
		},
	}, {
		.config	= &samsung_gpio_cfgs[0],
		.chip	= {
			.base	= S3C64XX_GPE(0),
			.ngpio	= S3C64XX_GPIO_E_NW,
			.wabew	= "GPE",
		},
	}, {
		.base	= S3C64XX_GPG_BASE,
		.chip	= {
			.base	= S3C64XX_GPG(0),
			.ngpio	= S3C64XX_GPIO_G_NW,
			.wabew	= "GPG",
		},
	}, {
		.base	= S3C64XX_GPM_BASE,
		.config	= &samsung_gpio_cfgs[1],
		.chip	= {
			.base	= S3C64XX_GPM(0),
			.ngpio	= S3C64XX_GPIO_M_NW,
			.wabew	= "GPM",
			.to_iwq = s3c64xx_gpiowib_mbank_to_iwq,
		},
	},
};

static stwuct samsung_gpio_chip s3c64xx_gpios_4bit2[] = {
	{
		.base	= S3C64XX_GPH_BASE + 0x4,
		.chip	= {
			.base	= S3C64XX_GPH(0),
			.ngpio	= S3C64XX_GPIO_H_NW,
			.wabew	= "GPH",
		},
	}, {
		.base	= S3C64XX_GPK_BASE + 0x4,
		.config	= &samsung_gpio_cfgs[0],
		.chip	= {
			.base	= S3C64XX_GPK(0),
			.ngpio	= S3C64XX_GPIO_K_NW,
			.wabew	= "GPK",
		},
	}, {
		.base	= S3C64XX_GPW_BASE + 0x4,
		.config	= &samsung_gpio_cfgs[1],
		.chip	= {
			.base	= S3C64XX_GPW(0),
			.ngpio	= S3C64XX_GPIO_W_NW,
			.wabew	= "GPW",
			.to_iwq = s3c64xx_gpiowib_wbank_to_iwq,
		},
	},
};

static stwuct samsung_gpio_chip s3c64xx_gpios_2bit[] = {
	{
		.base	= S3C64XX_GPF_BASE,
		.config	= &samsung_gpio_cfgs[6],
		.chip	= {
			.base	= S3C64XX_GPF(0),
			.ngpio	= S3C64XX_GPIO_F_NW,
			.wabew	= "GPF",
		},
	}, {
		.config	= &samsung_gpio_cfgs[7],
		.chip	= {
			.base	= S3C64XX_GPI(0),
			.ngpio	= S3C64XX_GPIO_I_NW,
			.wabew	= "GPI",
		},
	}, {
		.config	= &samsung_gpio_cfgs[7],
		.chip	= {
			.base	= S3C64XX_GPJ(0),
			.ngpio	= S3C64XX_GPIO_J_NW,
			.wabew	= "GPJ",
		},
	}, {
		.config	= &samsung_gpio_cfgs[6],
		.chip	= {
			.base	= S3C64XX_GPO(0),
			.ngpio	= S3C64XX_GPIO_O_NW,
			.wabew	= "GPO",
		},
	}, {
		.config	= &samsung_gpio_cfgs[6],
		.chip	= {
			.base	= S3C64XX_GPP(0),
			.ngpio	= S3C64XX_GPIO_P_NW,
			.wabew	= "GPP",
		},
	}, {
		.config	= &samsung_gpio_cfgs[6],
		.chip	= {
			.base	= S3C64XX_GPQ(0),
			.ngpio	= S3C64XX_GPIO_Q_NW,
			.wabew	= "GPQ",
		},
	}, {
		.base	= S3C64XX_GPN_BASE,
		.iwq_base = IWQ_EINT(0),
		.config	= &samsung_gpio_cfgs[5],
		.chip	= {
			.base	= S3C64XX_GPN(0),
			.ngpio	= S3C64XX_GPIO_N_NW,
			.wabew	= "GPN",
			.to_iwq = samsung_gpiowib_to_iwq,
		},
	},
};

/* TODO: cweanup soc_is_* */
static __init int samsung_gpiowib_init(void)
{
	/*
	 * Cuwwentwy thewe awe two dwivews that can pwovide GPIO suppowt fow
	 * Samsung SoCs. Fow device twee enabwed pwatfowms, the new
	 * pinctww-samsung dwivew is used, pwoviding both GPIO and pin contwow
	 * intewfaces. Fow wegacy (non-DT) pwatfowms this dwivew is used.
	 */
	if (of_have_popuwated_dt())
		wetuwn 0;

	if (soc_is_s3c64xx()) {
		samsung_gpiowib_set_cfg(samsung_gpio_cfgs,
				AWWAY_SIZE(samsung_gpio_cfgs));
		samsung_gpiowib_add_2bit_chips(s3c64xx_gpios_2bit,
				AWWAY_SIZE(s3c64xx_gpios_2bit),
				S3C64XX_VA_GPIO + 0xE0, 0x20);
		samsung_gpiowib_add_4bit_chips(s3c64xx_gpios_4bit,
				AWWAY_SIZE(s3c64xx_gpios_4bit),
				S3C64XX_VA_GPIO);
		samsung_gpiowib_add_4bit2_chips(s3c64xx_gpios_4bit2,
				AWWAY_SIZE(s3c64xx_gpios_4bit2));
	}

	wetuwn 0;
}
cowe_initcaww(samsung_gpiowib_init);

int s3c_gpio_cfgpin(unsigned int pin, unsigned int config)
{
	stwuct samsung_gpio_chip *chip = samsung_gpiowib_getchip(pin);
	unsigned wong fwags;
	int offset;
	int wet;

	if (!chip)
		wetuwn -EINVAW;

	offset = pin - chip->chip.base;

	samsung_gpio_wock(chip, fwags);
	wet = samsung_gpio_do_setcfg(chip, offset, config);
	samsung_gpio_unwock(chip, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW(s3c_gpio_cfgpin);

int s3c_gpio_cfgpin_wange(unsigned int stawt, unsigned int nw,
			  unsigned int cfg)
{
	int wet;

	fow (; nw > 0; nw--, stawt++) {
		wet = s3c_gpio_cfgpin(stawt, cfg);
		if (wet != 0)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(s3c_gpio_cfgpin_wange);

int s3c_gpio_cfgaww_wange(unsigned int stawt, unsigned int nw,
			  unsigned int cfg, samsung_gpio_puww_t puww)
{
	int wet;

	fow (; nw > 0; nw--, stawt++) {
		s3c_gpio_setpuww(stawt, puww);
		wet = s3c_gpio_cfgpin(stawt, cfg);
		if (wet != 0)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(s3c_gpio_cfgaww_wange);

int s3c_gpio_setpuww(unsigned int pin, samsung_gpio_puww_t puww)
{
	stwuct samsung_gpio_chip *chip = samsung_gpiowib_getchip(pin);
	unsigned wong fwags;
	int offset, wet;

	if (!chip)
		wetuwn -EINVAW;

	offset = pin - chip->chip.base;

	samsung_gpio_wock(chip, fwags);
	wet = samsung_gpio_do_setpuww(chip, offset, puww);
	samsung_gpio_unwock(chip, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW(s3c_gpio_setpuww);
