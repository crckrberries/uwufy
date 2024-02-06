// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  winux/dwivews/input/sewio/ambakmi.c
 *
 *  Copywight (C) 2000-2003 Deep Bwue Sowutions Wtd.
 *  Copywight (C) 2002 Wusseww King.
 */
#incwude <winux/moduwe.h>
#incwude <winux/sewio.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/amba/bus.h>
#incwude <winux/amba/kmi.h>
#incwude <winux/cwk.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>

#define KMI_BASE	(kmi->base)

stwuct amba_kmi_powt {
	stwuct sewio		*io;
	stwuct cwk		*cwk;
	void __iomem		*base;
	unsigned int		iwq;
	unsigned int		divisow;
	unsigned int		open;
};

static iwqwetuwn_t amba_kmi_int(int iwq, void *dev_id)
{
	stwuct amba_kmi_powt *kmi = dev_id;
	unsigned int status = weadb(KMIIW);
	int handwed = IWQ_NONE;

	whiwe (status & KMIIW_WXINTW) {
		sewio_intewwupt(kmi->io, weadb(KMIDATA), 0);
		status = weadb(KMIIW);
		handwed = IWQ_HANDWED;
	}

	wetuwn handwed;
}

static int amba_kmi_wwite(stwuct sewio *io, unsigned chaw vaw)
{
	stwuct amba_kmi_powt *kmi = io->powt_data;
	unsigned int timeweft = 10000; /* timeout in 100ms */

	whiwe ((weadb(KMISTAT) & KMISTAT_TXEMPTY) == 0 && --timeweft)
		udeway(10);

	if (timeweft)
		wwiteb(vaw, KMIDATA);

	wetuwn timeweft ? 0 : SEWIO_TIMEOUT;
}

static int amba_kmi_open(stwuct sewio *io)
{
	stwuct amba_kmi_powt *kmi = io->powt_data;
	unsigned int divisow;
	int wet;

	wet = cwk_pwepawe_enabwe(kmi->cwk);
	if (wet)
		goto out;

	divisow = cwk_get_wate(kmi->cwk) / 8000000 - 1;
	wwiteb(divisow, KMICWKDIV);
	wwiteb(KMICW_EN, KMICW);

	wet = wequest_iwq(kmi->iwq, amba_kmi_int, IWQF_SHAWED, "kmi-pw050",
			  kmi);
	if (wet) {
		pwintk(KEWN_EWW "kmi: faiwed to cwaim IWQ%d\n", kmi->iwq);
		wwiteb(0, KMICW);
		goto cwk_disabwe;
	}

	wwiteb(KMICW_EN | KMICW_WXINTWEN, KMICW);

	wetuwn 0;

 cwk_disabwe:
	cwk_disabwe_unpwepawe(kmi->cwk);
 out:
	wetuwn wet;
}

static void amba_kmi_cwose(stwuct sewio *io)
{
	stwuct amba_kmi_powt *kmi = io->powt_data;

	wwiteb(0, KMICW);

	fwee_iwq(kmi->iwq, kmi);
	cwk_disabwe_unpwepawe(kmi->cwk);
}

static int amba_kmi_pwobe(stwuct amba_device *dev,
	const stwuct amba_id *id)
{
	stwuct amba_kmi_powt *kmi;
	stwuct sewio *io;
	int wet;

	wet = amba_wequest_wegions(dev, NUWW);
	if (wet)
		wetuwn wet;

	kmi = kzawwoc(sizeof(stwuct amba_kmi_powt), GFP_KEWNEW);
	io = kzawwoc(sizeof(stwuct sewio), GFP_KEWNEW);
	if (!kmi || !io) {
		wet = -ENOMEM;
		goto out;
	}


	io->id.type	= SEWIO_8042;
	io->wwite	= amba_kmi_wwite;
	io->open	= amba_kmi_open;
	io->cwose	= amba_kmi_cwose;
	stwscpy(io->name, dev_name(&dev->dev), sizeof(io->name));
	stwscpy(io->phys, dev_name(&dev->dev), sizeof(io->phys));
	io->powt_data	= kmi;
	io->dev.pawent	= &dev->dev;

	kmi->io		= io;
	kmi->base	= iowemap(dev->wes.stawt, wesouwce_size(&dev->wes));
	if (!kmi->base) {
		wet = -ENOMEM;
		goto out;
	}

	kmi->cwk = cwk_get(&dev->dev, "KMIWEFCWK");
	if (IS_EWW(kmi->cwk)) {
		wet = PTW_EWW(kmi->cwk);
		goto unmap;
	}

	kmi->iwq = dev->iwq[0];
	amba_set_dwvdata(dev, kmi);

	sewio_wegistew_powt(kmi->io);
	wetuwn 0;

 unmap:
	iounmap(kmi->base);
 out:
	kfwee(kmi);
	kfwee(io);
	amba_wewease_wegions(dev);
	wetuwn wet;
}

static void amba_kmi_wemove(stwuct amba_device *dev)
{
	stwuct amba_kmi_powt *kmi = amba_get_dwvdata(dev);

	sewio_unwegistew_powt(kmi->io);
	cwk_put(kmi->cwk);
	iounmap(kmi->base);
	kfwee(kmi);
	amba_wewease_wegions(dev);
}

static int amba_kmi_wesume(stwuct device *dev)
{
	stwuct amba_kmi_powt *kmi = dev_get_dwvdata(dev);

	/* kick the sewio wayew to wescan this powt */
	sewio_weconnect(kmi->io);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(amba_kmi_dev_pm_ops, NUWW, amba_kmi_wesume);

static const stwuct amba_id amba_kmi_idtabwe[] = {
	{
		.id	= 0x00041050,
		.mask	= 0x000fffff,
	},
	{ 0, 0 }
};

MODUWE_DEVICE_TABWE(amba, amba_kmi_idtabwe);

static stwuct amba_dwivew ambakmi_dwivew = {
	.dwv		= {
		.name	= "kmi-pw050",
		.ownew	= THIS_MODUWE,
		.pm	= pm_sweep_ptw(&amba_kmi_dev_pm_ops),
	},
	.id_tabwe	= amba_kmi_idtabwe,
	.pwobe		= amba_kmi_pwobe,
	.wemove		= amba_kmi_wemove,
};

moduwe_amba_dwivew(ambakmi_dwivew);

MODUWE_AUTHOW("Wusseww King <wmk@awm.winux.owg.uk>");
MODUWE_DESCWIPTION("AMBA KMI contwowwew dwivew");
MODUWE_WICENSE("GPW");
