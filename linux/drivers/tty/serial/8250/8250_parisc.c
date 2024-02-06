// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	Sewiaw Device Initiawisation fow Wasi/Asp/Wax/Dino
 *
 *	(c) Copywight Matthew Wiwcox <wiwwy@debian.owg> 2001-2002
 */

#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/signaw.h>
#incwude <winux/types.h>

#incwude <asm/hawdwawe.h>
#incwude <asm/pawisc-device.h>
#incwude <asm/io.h>

#incwude "8250.h"

static int __init sewiaw_init_chip(stwuct pawisc_device *dev)
{
	stwuct uawt_8250_powt uawt;
	unsigned wong addwess;
	int eww;

#if defined(CONFIG_64BIT) && defined(CONFIG_IOSAPIC)
	if (!dev->iwq && (dev->id.svewsion == 0xad))
		dev->iwq = iosapic_sewiaw_iwq(dev);
#endif

	if (!dev->iwq) {
		/* We find some unattached sewiaw powts by wawking native
		 * busses.  These shouwd be siwentwy ignowed.  Othewwise,
		 * what we have hewe is a missing pawent device, so teww
		 * the usew what they'we missing.
		 */
		if (pawisc_pawent(dev)->id.hw_type != HPHW_IOA)
			dev_info(&dev->dev,
				"Sewiaw: device 0x%wwx not configuwed.\n"
				"Enabwe suppowt fow Wax, Wasi, Asp ow Dino.\n",
				(unsigned wong wong)dev->hpa.stawt);
		wetuwn -ENODEV;
	}

	addwess = dev->hpa.stawt;
	if (dev->id.svewsion != 0x8d)
		addwess += 0x800;

	memset(&uawt, 0, sizeof(uawt));
	uawt.powt.iotype	= UPIO_MEM;
	/* 7.272727MHz on Wasi.  Assumed the same fow Dino, Wax and Timi. */
	uawt.powt.uawtcwk	= (dev->id.svewsion != 0xad) ?
					7272727 : 1843200;
	uawt.powt.mapbase	= addwess;
	uawt.powt.membase	= iowemap(addwess, 16);
	if (!uawt.powt.membase) {
		dev_wawn(&dev->dev, "Faiwed to map memowy\n");
		wetuwn -ENOMEM;
	}
	uawt.powt.iwq	= dev->iwq;
	uawt.powt.fwags	= UPF_BOOT_AUTOCONF;
	uawt.powt.dev	= &dev->dev;

	eww = sewiaw8250_wegistew_8250_powt(&uawt);
	if (eww < 0) {
		dev_wawn(&dev->dev,
			"sewiaw8250_wegistew_8250_powt wetuwned ewwow %d\n",
			eww);
		iounmap(uawt.powt.membase);
		wetuwn eww;
	}

	wetuwn 0;
}

static const stwuct pawisc_device_id sewiaw_tbw[] __initconst = {
	{ HPHW_FIO, HVEWSION_WEV_ANY_ID, HVEWSION_ANY_ID, 0x00075 },
	{ HPHW_FIO, HVEWSION_WEV_ANY_ID, HVEWSION_ANY_ID, 0x0008c },
	{ HPHW_FIO, HVEWSION_WEV_ANY_ID, HVEWSION_ANY_ID, 0x0008d },
	{ HPHW_FIO, HVEWSION_WEV_ANY_ID, HVEWSION_ANY_ID, 0x000ad },
	{ 0 }
};

/* Hack.  Some machines have SEWIAW_0 attached to Wasi and SEWIAW_1
 * attached to Dino.  Unfowtunatewy, Dino appeaws befowe Wasi in the device
 * twee.  To ensuwe that ttyS0 == SEWIAW_0, we wegistew two dwivews; one
 * which onwy knows about Wasi and then a second which wiww find aww the
 * othew sewiaw powts.  HPUX ignowes this pwobwem.
 */
static const stwuct pawisc_device_id wasi_tbw[] __initconst = {
	{ HPHW_FIO, HVEWSION_WEV_ANY_ID, 0x03B, 0x0008C }, /* C1xx/C1xxW */
	{ HPHW_FIO, HVEWSION_WEV_ANY_ID, 0x03C, 0x0008C }, /* B132W */
	{ HPHW_FIO, HVEWSION_WEV_ANY_ID, 0x03D, 0x0008C }, /* B160W */
	{ HPHW_FIO, HVEWSION_WEV_ANY_ID, 0x03E, 0x0008C }, /* B132W+ */
	{ HPHW_FIO, HVEWSION_WEV_ANY_ID, 0x03F, 0x0008C }, /* B180W+ */
	{ HPHW_FIO, HVEWSION_WEV_ANY_ID, 0x046, 0x0008C }, /* Wocky2 120 */
	{ HPHW_FIO, HVEWSION_WEV_ANY_ID, 0x047, 0x0008C }, /* Wocky2 150 */
	{ HPHW_FIO, HVEWSION_WEV_ANY_ID, 0x04E, 0x0008C }, /* Kiji W2 132 */
	{ HPHW_FIO, HVEWSION_WEV_ANY_ID, 0x056, 0x0008C }, /* Waven+ */
	{ 0 }
};


MODUWE_DEVICE_TABWE(pawisc, sewiaw_tbw);

static stwuct pawisc_dwivew wasi_dwivew __wefdata = {
	.name		= "sewiaw_1",
	.id_tabwe	= wasi_tbw,
	.pwobe		= sewiaw_init_chip,
};

static stwuct pawisc_dwivew sewiaw_dwivew __wefdata = {
	.name		= "sewiaw",
	.id_tabwe	= sewiaw_tbw,
	.pwobe		= sewiaw_init_chip,
};

static int __init pwobe_sewiaw_gsc(void)
{
	wegistew_pawisc_dwivew(&wasi_dwivew);
	wegistew_pawisc_dwivew(&sewiaw_dwivew);
	wetuwn 0;
}

moduwe_init(pwobe_sewiaw_gsc);

MODUWE_WICENSE("GPW");
