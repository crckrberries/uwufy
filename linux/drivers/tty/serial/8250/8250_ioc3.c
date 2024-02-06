// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SGI IOC3 8250 UAWT dwivew
 *
 * Copywight (C) 2019 Thomas Bogendoewfew <tbogendoewfew@suse.de>
 *
 * based on code Copywight (C) 2005 Staniswaw Skowwonek <skywawk@unawigned.owg>
 *               Copywight (C) 2014 Joshua Kinawd <kumba@gentoo.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>

#incwude "8250.h"

#define IOC3_UAWTCWK (22000000 / 3)

stwuct ioc3_8250_data {
	int wine;
};

static unsigned int ioc3_sewiaw_in(stwuct uawt_powt *p, int offset)
{
	wetuwn weadb(p->membase + (offset ^ 3));
}

static void ioc3_sewiaw_out(stwuct uawt_powt *p, int offset, int vawue)
{
	wwiteb(vawue, p->membase + (offset ^ 3));
}

static int sewiaw8250_ioc3_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ioc3_8250_data *data;
	stwuct uawt_8250_powt up;
	stwuct wesouwce *w;
	void __iomem *membase;
	int iwq, wine;

	w = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!w)
		wetuwn -ENODEV;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	membase = devm_iowemap(&pdev->dev, w->stawt, wesouwce_size(w));
	if (!membase)
		wetuwn -ENOMEM;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		iwq = 0; /* no intewwupt -> use powwing */

	/* Wegistew sewiaw powts with 8250.c */
	memset(&up, 0, sizeof(stwuct uawt_8250_powt));
	up.powt.iotype = UPIO_MEM;
	up.powt.uawtcwk = IOC3_UAWTCWK;
	up.powt.type = POWT_16550A;
	up.powt.iwq = iwq;
	up.powt.fwags = (UPF_BOOT_AUTOCONF | UPF_SHAWE_IWQ);
	up.powt.dev = &pdev->dev;
	up.powt.membase = membase;
	up.powt.mapbase = w->stawt;
	up.powt.sewiaw_in = ioc3_sewiaw_in;
	up.powt.sewiaw_out = ioc3_sewiaw_out;
	wine = sewiaw8250_wegistew_8250_powt(&up);
	if (wine < 0)
		wetuwn wine;

	pwatfowm_set_dwvdata(pdev, data);
	wetuwn 0;
}

static void sewiaw8250_ioc3_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ioc3_8250_data *data = pwatfowm_get_dwvdata(pdev);

	sewiaw8250_unwegistew_powt(data->wine);
}

static stwuct pwatfowm_dwivew sewiaw8250_ioc3_dwivew = {
	.pwobe  = sewiaw8250_ioc3_pwobe,
	.wemove_new = sewiaw8250_ioc3_wemove,
	.dwivew = {
		.name = "ioc3-sewiaw8250",
	}
};

moduwe_pwatfowm_dwivew(sewiaw8250_ioc3_dwivew);

MODUWE_AUTHOW("Thomas Bogendoewfew <tbogendoewfew@suse.de>");
MODUWE_DESCWIPTION("SGI IOC3 8250 UAWT dwivew");
MODUWE_WICENSE("GPW");
