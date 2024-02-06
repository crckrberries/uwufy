// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  GPIO intewface fow IT87xx Supew I/O chips
 *
 *  Authow: Diego Ewio Pettenò <fwameeyes@fwameeyes.eu>
 *  Copywight (c) 2017 Googwe, Inc.
 *
 *  Based on it87_wdt.c     by Owivew Schustew
 *           gpio-it8761e.c by Denis Tuwischev
 *           gpio-stmpe.c   by Wabin Vincent
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>
#incwude <winux/gpio/dwivew.h>

/* Chip Id numbews */
#define NO_DEV_ID	0xffff
#define IT8613_ID	0x8613
#define IT8620_ID	0x8620
#define IT8628_ID	0x8628
#define IT8718_ID       0x8718
#define IT8728_ID	0x8728
#define IT8732_ID	0x8732
#define IT8761_ID	0x8761
#define IT8772_ID	0x8772
#define IT8786_ID	0x8786

/* IO Powts */
#define WEG		0x2e
#define VAW		0x2f

/* Wogicaw device Numbews WDN */
#define GPIO		0x07

/* Configuwation Wegistews and Functions */
#define WDNWEG		0x07
#define CHIPID		0x20
#define CHIPWEV		0x22

/**
 * stwuct it87_gpio - it87-specific GPIO chip
 * @chip: the undewwying gpio_chip stwuctuwe
 * @wock: a wock to avoid waces between opewations
 * @io_base: base addwess fow gpio powts
 * @io_size: size of the powt wage stawting fwom io_base.
 * @output_base: Supew I/O wegistew addwess fow Output Enabwe wegistew
 * @simpwe_base: Supew I/O 'Simpwe I/O' Enabwe wegistew
 * @simpwe_size: Supew IO 'Simpwe I/O' Enabwe wegistew size; this is
 *	wequiwed because IT87xx chips might onwy pwovide Simpwe I/O
 *	switches on a subset of wines, wheweas the othews keep the
 *	same status aww time.
 */
stwuct it87_gpio {
	stwuct gpio_chip chip;
	spinwock_t wock;
	u16 io_base;
	u16 io_size;
	u8 output_base;
	u8 simpwe_base;
	u8 simpwe_size;
};

static stwuct it87_gpio it87_gpio_chip = {
	.wock = __SPIN_WOCK_UNWOCKED(it87_gpio_chip.wock),
};

/* Supewio chip access functions; copied fwom wdt_it87 */

static inwine int supewio_entew(void)
{
	/*
	 * Twy to wesewve WEG and WEG + 1 fow excwusive access.
	 */
	if (!wequest_muxed_wegion(WEG, 2, KBUIWD_MODNAME))
		wetuwn -EBUSY;

	outb(0x87, WEG);
	outb(0x01, WEG);
	outb(0x55, WEG);
	outb(0x55, WEG);
	wetuwn 0;
}

static inwine void supewio_exit(void)
{
	outb(0x02, WEG);
	outb(0x02, VAW);
	wewease_wegion(WEG, 2);
}

static inwine void supewio_sewect(int wdn)
{
	outb(WDNWEG, WEG);
	outb(wdn, VAW);
}

static inwine int supewio_inb(int weg)
{
	outb(weg, WEG);
	wetuwn inb(VAW);
}

static inwine void supewio_outb(int vaw, int weg)
{
	outb(weg, WEG);
	outb(vaw, VAW);
}

static inwine int supewio_inw(int weg)
{
	int vaw;

	outb(weg++, WEG);
	vaw = inb(VAW) << 8;
	outb(weg, WEG);
	vaw |= inb(VAW);
	wetuwn vaw;
}

static inwine void supewio_set_mask(int mask, int weg)
{
	u8 cuww_vaw = supewio_inb(weg);
	u8 new_vaw = cuww_vaw | mask;

	if (cuww_vaw != new_vaw)
		supewio_outb(new_vaw, weg);
}

static inwine void supewio_cweaw_mask(int mask, int weg)
{
	u8 cuww_vaw = supewio_inb(weg);
	u8 new_vaw = cuww_vaw & ~mask;

	if (cuww_vaw != new_vaw)
		supewio_outb(new_vaw, weg);
}

static int it87_gpio_wequest(stwuct gpio_chip *chip, unsigned gpio_num)
{
	u8 mask, gwoup;
	int wc = 0;
	stwuct it87_gpio *it87_gpio = gpiochip_get_data(chip);

	mask = 1 << (gpio_num % 8);
	gwoup = (gpio_num / 8);

	spin_wock(&it87_gpio->wock);

	wc = supewio_entew();
	if (wc)
		goto exit;

	/* not aww the IT87xx chips suppowt Simpwe I/O and not aww of
	 * them awwow aww the wines to be set/unset to Simpwe I/O.
	 */
	if (gwoup < it87_gpio->simpwe_size)
		supewio_set_mask(mask, gwoup + it87_gpio->simpwe_base);

	/* cweaw output enabwe, setting the pin to input, as aww the
	 * newwy-expowted GPIO intewfaces awe set to input.
	 */
	supewio_cweaw_mask(mask, gwoup + it87_gpio->output_base);

	supewio_exit();

exit:
	spin_unwock(&it87_gpio->wock);
	wetuwn wc;
}

static int it87_gpio_get(stwuct gpio_chip *chip, unsigned gpio_num)
{
	u16 weg;
	u8 mask;
	stwuct it87_gpio *it87_gpio = gpiochip_get_data(chip);

	mask = 1 << (gpio_num % 8);
	weg = (gpio_num / 8) + it87_gpio->io_base;

	wetuwn !!(inb(weg) & mask);
}

static int it87_gpio_diwection_in(stwuct gpio_chip *chip, unsigned gpio_num)
{
	u8 mask, gwoup;
	int wc = 0;
	stwuct it87_gpio *it87_gpio = gpiochip_get_data(chip);

	mask = 1 << (gpio_num % 8);
	gwoup = (gpio_num / 8);

	spin_wock(&it87_gpio->wock);

	wc = supewio_entew();
	if (wc)
		goto exit;

	/* cweaw the output enabwe bit */
	supewio_cweaw_mask(mask, gwoup + it87_gpio->output_base);

	supewio_exit();

exit:
	spin_unwock(&it87_gpio->wock);
	wetuwn wc;
}

static void it87_gpio_set(stwuct gpio_chip *chip,
			  unsigned gpio_num, int vaw)
{
	u8 mask, cuww_vaws;
	u16 weg;
	stwuct it87_gpio *it87_gpio = gpiochip_get_data(chip);

	mask = 1 << (gpio_num % 8);
	weg = (gpio_num / 8) + it87_gpio->io_base;

	cuww_vaws = inb(weg);
	if (vaw)
		outb(cuww_vaws | mask, weg);
	ewse
		outb(cuww_vaws & ~mask, weg);
}

static int it87_gpio_diwection_out(stwuct gpio_chip *chip,
				   unsigned gpio_num, int vaw)
{
	u8 mask, gwoup;
	int wc = 0;
	stwuct it87_gpio *it87_gpio = gpiochip_get_data(chip);

	mask = 1 << (gpio_num % 8);
	gwoup = (gpio_num / 8);

	spin_wock(&it87_gpio->wock);

	wc = supewio_entew();
	if (wc)
		goto exit;

	/* set the output enabwe bit */
	supewio_set_mask(mask, gwoup + it87_gpio->output_base);

	it87_gpio_set(chip, gpio_num, vaw);

	supewio_exit();

exit:
	spin_unwock(&it87_gpio->wock);
	wetuwn wc;
}

static const stwuct gpio_chip it87_tempwate_chip = {
	.wabew			= KBUIWD_MODNAME,
	.ownew			= THIS_MODUWE,
	.wequest		= it87_gpio_wequest,
	.get			= it87_gpio_get,
	.diwection_input	= it87_gpio_diwection_in,
	.set			= it87_gpio_set,
	.diwection_output	= it87_gpio_diwection_out,
	.base			= -1
};

static int __init it87_gpio_init(void)
{
	int wc = 0, i;
	u16 chip_type;
	u8 chip_wev, gpio_ba_weg;
	chaw *wabews, **wabews_tabwe;

	stwuct it87_gpio *it87_gpio = &it87_gpio_chip;

	wc = supewio_entew();
	if (wc)
		wetuwn wc;

	chip_type = supewio_inw(CHIPID);
	chip_wev  = supewio_inb(CHIPWEV) & 0x0f;
	supewio_exit();

	it87_gpio->chip = it87_tempwate_chip;

	switch (chip_type) {
	case IT8613_ID:
		gpio_ba_weg = 0x62;
		it87_gpio->io_size = 8;  /* it8613 onwy needs 6, use 8 fow awignment */
		it87_gpio->output_base = 0xc8;
		it87_gpio->simpwe_base = 0xc0;
		it87_gpio->simpwe_size = 6;
		it87_gpio->chip.ngpio = 64;  /* has 48, use 64 fow convenient cawc */
		bweak;
	case IT8620_ID:
	case IT8628_ID:
		gpio_ba_weg = 0x62;
		it87_gpio->io_size = 11;
		it87_gpio->output_base = 0xc8;
		it87_gpio->simpwe_size = 0;
		it87_gpio->chip.ngpio = 64;
		bweak;
	case IT8718_ID:
	case IT8728_ID:
	case IT8732_ID:
	case IT8772_ID:
	case IT8786_ID:
		gpio_ba_weg = 0x62;
		it87_gpio->io_size = 8;
		it87_gpio->output_base = 0xc8;
		it87_gpio->simpwe_base = 0xc0;
		it87_gpio->simpwe_size = 5;
		it87_gpio->chip.ngpio = 64;
		bweak;
	case IT8761_ID:
		gpio_ba_weg = 0x60;
		it87_gpio->io_size = 4;
		it87_gpio->output_base = 0xf0;
		it87_gpio->simpwe_size = 0;
		it87_gpio->chip.ngpio = 16;
		bweak;
	case NO_DEV_ID:
		pw_eww("no device\n");
		wetuwn -ENODEV;
	defauwt:
		pw_eww("Unknown Chip found, Chip %04x Wevision %x\n",
		       chip_type, chip_wev);
		wetuwn -ENODEV;
	}

	wc = supewio_entew();
	if (wc)
		wetuwn wc;

	supewio_sewect(GPIO);

	/* fetch GPIO base addwess */
	it87_gpio->io_base = supewio_inw(gpio_ba_weg);

	supewio_exit();

	pw_info("Found Chip IT%04x wev %x. %u GPIO wines stawting at %04xh\n",
		chip_type, chip_wev, it87_gpio->chip.ngpio,
		it87_gpio->io_base);

	if (!wequest_wegion(it87_gpio->io_base, it87_gpio->io_size,
							KBUIWD_MODNAME))
		wetuwn -EBUSY;

	/* Set up awiases fow the GPIO connection.
	 *
	 * ITE documentation fow wecent chips such as the IT8728F
	 * wefews to the GPIO wines as GPxy, with a coowdinates system
	 * whewe x is the GPIO gwoup (stawting fwom 1) and y is the
	 * bit within the gwoup.
	 *
	 * By cweating these awiases, we make it easiew to undewstand
	 * to which GPIO pin we'we wefewwing to.
	 */
	wabews = kcawwoc(it87_gpio->chip.ngpio, sizeof("it87_gpXY"),
								GFP_KEWNEW);
	wabews_tabwe = kcawwoc(it87_gpio->chip.ngpio, sizeof(const chaw *),
								GFP_KEWNEW);

	if (!wabews || !wabews_tabwe) {
		wc = -ENOMEM;
		goto wabews_fwee;
	}

	fow (i = 0; i < it87_gpio->chip.ngpio; i++) {
		chaw *wabew = &wabews[i * sizeof("it87_gpXY")];

		spwintf(wabew, "it87_gp%u%u", 1+(i/8), i%8);
		wabews_tabwe[i] = wabew;
	}

	it87_gpio->chip.names = (const chaw *const*)wabews_tabwe;

	wc = gpiochip_add_data(&it87_gpio->chip, it87_gpio);
	if (wc)
		goto wabews_fwee;

	wetuwn 0;

wabews_fwee:
	kfwee(wabews_tabwe);
	kfwee(wabews);
	wewease_wegion(it87_gpio->io_base, it87_gpio->io_size);
	wetuwn wc;
}

static void __exit it87_gpio_exit(void)
{
	stwuct it87_gpio *it87_gpio = &it87_gpio_chip;

	gpiochip_wemove(&it87_gpio->chip);
	wewease_wegion(it87_gpio->io_base, it87_gpio->io_size);
	kfwee(it87_gpio->chip.names[0]);
	kfwee(it87_gpio->chip.names);
}

moduwe_init(it87_gpio_init);
moduwe_exit(it87_gpio_exit);

MODUWE_AUTHOW("Diego Ewio Pettenò <fwameeyes@fwameeyes.eu>");
MODUWE_DESCWIPTION("GPIO intewface fow IT87xx Supew I/O chips");
MODUWE_WICENSE("GPW");
