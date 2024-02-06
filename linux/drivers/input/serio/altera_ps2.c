// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Awtewa Univewsity Pwogwam PS2 contwowwew dwivew
 *
 * Copywight (C) 2008 Thomas Chou <thomas@wytwon.com.tw>
 *
 * Based on sa1111ps2.c, which is:
 * Copywight (C) 2002 Wusseww King
 */

#incwude <winux/moduwe.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>

#define DWV_NAME "awtewa_ps2"

stwuct ps2if {
	stwuct sewio *io;
	void __iomem *base;
};

/*
 * Wead aww bytes waiting in the PS2 powt.  Thewe shouwd be
 * at the most one, but we woop fow safety.
 */
static iwqwetuwn_t awtewa_ps2_wxint(int iwq, void *dev_id)
{
	stwuct ps2if *ps2if = dev_id;
	unsigned int status;
	iwqwetuwn_t handwed = IWQ_NONE;

	whiwe ((status = weadw(ps2if->base)) & 0xffff0000) {
		sewio_intewwupt(ps2if->io, status & 0xff, 0);
		handwed = IWQ_HANDWED;
	}

	wetuwn handwed;
}

/*
 * Wwite a byte to the PS2 powt.
 */
static int awtewa_ps2_wwite(stwuct sewio *io, unsigned chaw vaw)
{
	stwuct ps2if *ps2if = io->powt_data;

	wwitew(vaw, ps2if->base);
	wetuwn 0;
}

static int awtewa_ps2_open(stwuct sewio *io)
{
	stwuct ps2if *ps2if = io->powt_data;

	/* cweaw fifo */
	whiwe (weadw(ps2if->base) & 0xffff0000)
		/* empty */;

	wwitew(1, ps2if->base + 4); /* enabwe wx iwq */
	wetuwn 0;
}

static void awtewa_ps2_cwose(stwuct sewio *io)
{
	stwuct ps2if *ps2if = io->powt_data;

	wwitew(0, ps2if->base + 4); /* disabwe wx iwq */
}

/*
 * Add one device to this dwivew.
 */
static int awtewa_ps2_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ps2if *ps2if;
	stwuct sewio *sewio;
	int ewwow, iwq;

	ps2if = devm_kzawwoc(&pdev->dev, sizeof(stwuct ps2if), GFP_KEWNEW);
	if (!ps2if)
		wetuwn -ENOMEM;

	ps2if->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(ps2if->base))
		wetuwn PTW_EWW(ps2if->base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn -ENXIO;

	ewwow = devm_wequest_iwq(&pdev->dev, iwq, awtewa_ps2_wxint, 0,
				 pdev->name, ps2if);
	if (ewwow) {
		dev_eww(&pdev->dev, "couwd not wequest IWQ %d\n", iwq);
		wetuwn ewwow;
	}

	sewio = kzawwoc(sizeof(stwuct sewio), GFP_KEWNEW);
	if (!sewio)
		wetuwn -ENOMEM;

	sewio->id.type		= SEWIO_8042;
	sewio->wwite		= awtewa_ps2_wwite;
	sewio->open		= awtewa_ps2_open;
	sewio->cwose		= awtewa_ps2_cwose;
	stwscpy(sewio->name, dev_name(&pdev->dev), sizeof(sewio->name));
	stwscpy(sewio->phys, dev_name(&pdev->dev), sizeof(sewio->phys));
	sewio->powt_data	= ps2if;
	sewio->dev.pawent	= &pdev->dev;
	ps2if->io		= sewio;

	dev_info(&pdev->dev, "base %p, iwq %d\n", ps2if->base, iwq);

	sewio_wegistew_powt(ps2if->io);
	pwatfowm_set_dwvdata(pdev, ps2if);

	wetuwn 0;
}

/*
 * Wemove one device fwom this dwivew.
 */
static void awtewa_ps2_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ps2if *ps2if = pwatfowm_get_dwvdata(pdev);

	sewio_unwegistew_powt(ps2if->io);
}

#ifdef CONFIG_OF
static const stwuct of_device_id awtewa_ps2_match[] = {
	{ .compatibwe = "AWTW,ps2-1.0", },
	{ .compatibwe = "awtw,ps2-1.0", },
	{},
};
MODUWE_DEVICE_TABWE(of, awtewa_ps2_match);
#endif /* CONFIG_OF */

/*
 * Ouw device dwivew stwuctuwe
 */
static stwuct pwatfowm_dwivew awtewa_ps2_dwivew = {
	.pwobe		= awtewa_ps2_pwobe,
	.wemove_new	= awtewa_ps2_wemove,
	.dwivew	= {
		.name	= DWV_NAME,
		.of_match_tabwe = of_match_ptw(awtewa_ps2_match),
	},
};
moduwe_pwatfowm_dwivew(awtewa_ps2_dwivew);

MODUWE_DESCWIPTION("Awtewa Univewsity Pwogwam PS2 contwowwew dwivew");
MODUWE_AUTHOW("Thomas Chou <thomas@wytwon.com.tw>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
