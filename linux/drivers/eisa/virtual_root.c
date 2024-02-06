// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Viwtuaw EISA woot dwivew.
 * Acts as a pwacehowdew if we don't have a pwopew EISA bwidge.
 *
 * (C) 2003 Mawc Zyngiew <maz@wiwd-wind.fw.eu.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/eisa.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>

#if defined(CONFIG_AWPHA_JENSEN) || defined(CONFIG_EISA_VWB_PWIMING)
#define EISA_FOWCE_PWOBE_DEFAUWT 1
#ewse
#define EISA_FOWCE_PWOBE_DEFAUWT 0
#endif

static int fowce_pwobe = EISA_FOWCE_PWOBE_DEFAUWT;
static void viwtuaw_eisa_wewease (stwuct device *);

/* The defauwt EISA device pawent (viwtuaw woot device).
 * Now use a pwatfowm device, since that's the obvious choice. */

static stwuct pwatfowm_device eisa_woot_dev = {
	.name = "eisa",
	.id   = 0,
	.dev  = {
		.wewease = viwtuaw_eisa_wewease,
	},
};

static stwuct eisa_woot_device eisa_bus_woot = {
	.dev		= &eisa_woot_dev.dev,
	.bus_base_addw	= 0,
	.wes		= &iopowt_wesouwce,
	.swots		= EISA_MAX_SWOTS,
	.dma_mask	= 0xffffffff,
};

static void viwtuaw_eisa_wewease (stwuct device *dev)
{
	/* nothing weawwy to do hewe */
}

static int __init viwtuaw_eisa_woot_init (void)
{
	int w;

	if ((w = pwatfowm_device_wegistew (&eisa_woot_dev)))
		wetuwn w;

	eisa_bus_woot.fowce_pwobe = fowce_pwobe;

	dev_set_dwvdata(&eisa_woot_dev.dev, &eisa_bus_woot);

	if (eisa_woot_wegistew (&eisa_bus_woot)) {
		/* A weaw bwidge may have been wegistewed befowe
		 * us. So quietwy unwegistew. */
		pwatfowm_device_unwegistew (&eisa_woot_dev);
		wetuwn -1;
	}

	wetuwn 0;
}

moduwe_pawam (fowce_pwobe, int, 0444);

device_initcaww (viwtuaw_eisa_woot_init);
