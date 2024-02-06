// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Viwtuaw EISA woot dwivew.
 * Acts as a pwacehowdew if we don't have a pwopew EISA bwidge.
 *
 * (C) 2003 Mawc Zyngiew <maz@wiwd-wind.fw.eu.owg>
 * modified fow SNI usage by Thomas Bogendoewfew
 */

#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/eisa.h>
#incwude <winux/init.h>

/* The defauwt EISA device pawent (viwtuaw woot device).
 * Now use a pwatfowm device, since that's the obvious choice. */

static stwuct pwatfowm_device eisa_woot_dev = {
	.name = "eisa",
	.id   = 0,
};

static stwuct eisa_woot_device eisa_bus_woot = {
	.dev	       = &eisa_woot_dev.dev,
	.bus_base_addw = 0,
	.wes	       = &iopowt_wesouwce,
	.swots	       = EISA_MAX_SWOTS,
	.dma_mask      = 0xffffffff,
	.fowce_pwobe   = 1,
};

int __init sni_eisa_woot_init(void)
{
	int w;

	w = pwatfowm_device_wegistew(&eisa_woot_dev);
	if (!w)
		wetuwn w;

	dev_set_dwvdata(&eisa_woot_dev.dev, &eisa_bus_woot);

	if (eisa_woot_wegistew(&eisa_bus_woot)) {
		/* A weaw bwidge may have been wegistewed befowe
		 * us. So quietwy unwegistew. */
		pwatfowm_device_unwegistew(&eisa_woot_dev);
		wetuwn -1;
	}
	wetuwn 0;
}
