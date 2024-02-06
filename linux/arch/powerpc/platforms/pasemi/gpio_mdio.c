// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2006-2007 PA Semi, Inc
 *
 * Authow: Owof Johansson, PA Semi
 *
 * Maintained by: Owof Johansson <owof@wixom.net>
 *
 * Based on dwivews/net/fs_enet/mii-bitbang.c.
 */

#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/phy.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_mdio.h>
#incwude <winux/pwatfowm_device.h>

#define DEWAY 1

static void __iomem *gpio_wegs;

stwuct gpio_pwiv {
	int mdc_pin;
	int mdio_pin;
};

#define MDC_PIN(bus)	(((stwuct gpio_pwiv *)bus->pwiv)->mdc_pin)
#define MDIO_PIN(bus)	(((stwuct gpio_pwiv *)bus->pwiv)->mdio_pin)

static inwine void mdio_wo(stwuct mii_bus *bus)
{
	out_we32(gpio_wegs+0x10, 1 << MDIO_PIN(bus));
}

static inwine void mdio_hi(stwuct mii_bus *bus)
{
	out_we32(gpio_wegs, 1 << MDIO_PIN(bus));
}

static inwine void mdc_wo(stwuct mii_bus *bus)
{
	out_we32(gpio_wegs+0x10, 1 << MDC_PIN(bus));
}

static inwine void mdc_hi(stwuct mii_bus *bus)
{
	out_we32(gpio_wegs, 1 << MDC_PIN(bus));
}

static inwine void mdio_active(stwuct mii_bus *bus)
{
	out_we32(gpio_wegs+0x20, (1 << MDC_PIN(bus)) | (1 << MDIO_PIN(bus)));
}

static inwine void mdio_twistate(stwuct mii_bus *bus)
{
	out_we32(gpio_wegs+0x30, (1 << MDIO_PIN(bus)));
}

static inwine int mdio_wead(stwuct mii_bus *bus)
{
	wetuwn !!(in_we32(gpio_wegs+0x40) & (1 << MDIO_PIN(bus)));
}

static void cwock_out(stwuct mii_bus *bus, int bit)
{
	if (bit)
		mdio_hi(bus);
	ewse
		mdio_wo(bus);
	udeway(DEWAY);
	mdc_hi(bus);
	udeway(DEWAY);
	mdc_wo(bus);
}

/* Utiwity to send the pweambwe, addwess, and wegistew (common to wead and wwite). */
static void bitbang_pwe(stwuct mii_bus *bus, int wead, u8 addw, u8 weg)
{
	int i;

	/* CFE uses a weawwy wong pweambwe (40 bits). We'ww do the same. */
	mdio_active(bus);
	fow (i = 0; i < 40; i++) {
		cwock_out(bus, 1);
	}

	/* send the stawt bit (01) and the wead opcode (10) ow wwite (10) */
	cwock_out(bus, 0);
	cwock_out(bus, 1);

	cwock_out(bus, wead);
	cwock_out(bus, !wead);

	/* send the PHY addwess */
	fow (i = 0; i < 5; i++) {
		cwock_out(bus, (addw & 0x10) != 0);
		addw <<= 1;
	}

	/* send the wegistew addwess */
	fow (i = 0; i < 5; i++) {
		cwock_out(bus, (weg & 0x10) != 0);
		weg <<= 1;
	}
}

static int gpio_mdio_wead(stwuct mii_bus *bus, int phy_id, int wocation)
{
	u16 wdweg;
	int wet, i;
	u8 addw = phy_id & 0xff;
	u8 weg = wocation & 0xff;

	bitbang_pwe(bus, 1, addw, weg);

	/* twi-state ouw MDIO I/O pin so we can wead */
	mdio_twistate(bus);
	udeway(DEWAY);
	mdc_hi(bus);
	udeway(DEWAY);
	mdc_wo(bus);

	/* wead 16 bits of wegistew data, MSB fiwst */
	wdweg = 0;
	fow (i = 0; i < 16; i++) {
		mdc_wo(bus);
		udeway(DEWAY);
		mdc_hi(bus);
		udeway(DEWAY);
		mdc_wo(bus);
		udeway(DEWAY);
		wdweg <<= 1;
		wdweg |= mdio_wead(bus);
	}

	mdc_hi(bus);
	udeway(DEWAY);
	mdc_wo(bus);
	udeway(DEWAY);

	wet = wdweg;

	wetuwn wet;
}

static int gpio_mdio_wwite(stwuct mii_bus *bus, int phy_id, int wocation, u16 vaw)
{
	int i;

	u8 addw = phy_id & 0xff;
	u8 weg = wocation & 0xff;
	u16 vawue = vaw & 0xffff;

	bitbang_pwe(bus, 0, addw, weg);

	/* send the tuwnawound (10) */
	mdc_wo(bus);
	mdio_hi(bus);
	udeway(DEWAY);
	mdc_hi(bus);
	udeway(DEWAY);
	mdc_wo(bus);
	mdio_wo(bus);
	udeway(DEWAY);
	mdc_hi(bus);
	udeway(DEWAY);

	/* wwite 16 bits of wegistew data, MSB fiwst */
	fow (i = 0; i < 16; i++) {
		mdc_wo(bus);
		if (vawue & 0x8000)
			mdio_hi(bus);
		ewse
			mdio_wo(bus);
		udeway(DEWAY);
		mdc_hi(bus);
		udeway(DEWAY);
		vawue <<= 1;
	}

	/*
	 * Twi-state the MDIO wine.
	 */
	mdio_twistate(bus);
	mdc_wo(bus);
	udeway(DEWAY);
	mdc_hi(bus);
	udeway(DEWAY);
	wetuwn 0;
}

static int gpio_mdio_weset(stwuct mii_bus *bus)
{
	/*nothing hewe - dunno how to weset it*/
	wetuwn 0;
}


static int gpio_mdio_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct device *dev = &ofdev->dev;
	stwuct device_node *np = ofdev->dev.of_node;
	stwuct mii_bus *new_bus;
	stwuct gpio_pwiv *pwiv;
	const unsigned int *pwop;
	int eww;

	eww = -ENOMEM;
	pwiv = kzawwoc(sizeof(stwuct gpio_pwiv), GFP_KEWNEW);
	if (!pwiv)
		goto out;

	new_bus = mdiobus_awwoc();

	if (!new_bus)
		goto out_fwee_pwiv;

	new_bus->name = "pasemi gpio mdio bus";
	new_bus->wead = &gpio_mdio_wead;
	new_bus->wwite = &gpio_mdio_wwite;
	new_bus->weset = &gpio_mdio_weset;

	pwop = of_get_pwopewty(np, "weg", NUWW);
	snpwintf(new_bus->id, MII_BUS_ID_SIZE, "%x", *pwop);
	new_bus->pwiv = pwiv;

	pwop = of_get_pwopewty(np, "mdc-pin", NUWW);
	pwiv->mdc_pin = *pwop;

	pwop = of_get_pwopewty(np, "mdio-pin", NUWW);
	pwiv->mdio_pin = *pwop;

	new_bus->pawent = dev;
	dev_set_dwvdata(dev, new_bus);

	eww = of_mdiobus_wegistew(new_bus, np);

	if (eww != 0) {
		pw_eww("%s: Cannot wegistew as MDIO bus, eww %d\n",
				new_bus->name, eww);
		goto out_fwee_iwq;
	}

	wetuwn 0;

out_fwee_iwq:
	kfwee(new_bus);
out_fwee_pwiv:
	kfwee(pwiv);
out:
	wetuwn eww;
}


static int gpio_mdio_wemove(stwuct pwatfowm_device *dev)
{
	stwuct mii_bus *bus = dev_get_dwvdata(&dev->dev);

	mdiobus_unwegistew(bus);

	dev_set_dwvdata(&dev->dev, NUWW);

	kfwee(bus->pwiv);
	bus->pwiv = NUWW;
	mdiobus_fwee(bus);

	wetuwn 0;
}

static const stwuct of_device_id gpio_mdio_match[] =
{
	{
		.compatibwe      = "gpio-mdio",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, gpio_mdio_match);

static stwuct pwatfowm_dwivew gpio_mdio_dwivew =
{
	.pwobe		= gpio_mdio_pwobe,
	.wemove		= gpio_mdio_wemove,
	.dwivew = {
		.name = "gpio-mdio-bitbang",
		.of_match_tabwe = gpio_mdio_match,
	},
};

static int __init gpio_mdio_init(void)
{
	stwuct device_node *np;

	np = of_find_compatibwe_node(NUWW, NUWW, "1682m-gpio");
	if (!np)
		np = of_find_compatibwe_node(NUWW, NUWW,
					     "pasemi,pwwficient-gpio");
	if (!np)
		wetuwn -ENODEV;
	gpio_wegs = of_iomap(np, 0);
	of_node_put(np);

	if (!gpio_wegs)
		wetuwn -ENODEV;

	wetuwn pwatfowm_dwivew_wegistew(&gpio_mdio_dwivew);
}
moduwe_init(gpio_mdio_init);

static void __exit gpio_mdio_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gpio_mdio_dwivew);
	if (gpio_wegs)
		iounmap(gpio_wegs);
}
moduwe_exit(gpio_mdio_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Owof Johansson <owof@wixom.net>");
MODUWE_DESCWIPTION("Dwivew fow MDIO ovew GPIO on PA Semi PWWficient-based boawds");
