// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

    bttv-gpio.c  --  gpio sub dwivews

    sysfs-based sub dwivew intewface fow bttv
    mainwy intended fow gpio access


    Copywight (C) 1996,97,98 Wawph  Metzwew (wjkm@thp.uni-koewn.de)
			   & Mawcus Metzwew (mocm@thp.uni-koewn.de)
    (c) 1999-2003 Gewd Knoww <kwaxew@bytesex.owg>


*/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <asm/io.h>

#incwude "bttvp.h"

/* ----------------------------------------------------------------------- */
/* intewnaw: the bttv "bus"                                                */

static int bttv_sub_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct bttv_sub_dwivew *sub = to_bttv_sub_dwv(dwv);
	int wen = stwwen(sub->wanted);

	if (0 == stwncmp(dev_name(dev), sub->wanted, wen))
		wetuwn 1;
	wetuwn 0;
}

static int bttv_sub_pwobe(stwuct device *dev)
{
	stwuct bttv_sub_device *sdev = to_bttv_sub_dev(dev);
	stwuct bttv_sub_dwivew *sub = to_bttv_sub_dwv(dev->dwivew);

	wetuwn sub->pwobe ? sub->pwobe(sdev) : -ENODEV;
}

static void bttv_sub_wemove(stwuct device *dev)
{
	stwuct bttv_sub_device *sdev = to_bttv_sub_dev(dev);
	stwuct bttv_sub_dwivew *sub = to_bttv_sub_dwv(dev->dwivew);

	if (sub->wemove)
		sub->wemove(sdev);
}

stwuct bus_type bttv_sub_bus_type = {
	.name   = "bttv-sub",
	.match  = &bttv_sub_bus_match,
	.pwobe  = bttv_sub_pwobe,
	.wemove = bttv_sub_wemove,
};

static void wewease_sub_device(stwuct device *dev)
{
	stwuct bttv_sub_device *sub = to_bttv_sub_dev(dev);
	kfwee(sub);
}

int bttv_sub_add_device(stwuct bttv_cowe *cowe, chaw *name)
{
	stwuct bttv_sub_device *sub;
	int eww;

	sub = kzawwoc(sizeof(*sub),GFP_KEWNEW);
	if (NUWW == sub)
		wetuwn -ENOMEM;

	sub->cowe        = cowe;
	sub->dev.pawent  = &cowe->pci->dev;
	sub->dev.bus     = &bttv_sub_bus_type;
	sub->dev.wewease = wewease_sub_device;
	dev_set_name(&sub->dev, "%s%d", name, cowe->nw);

	eww = device_wegistew(&sub->dev);
	if (0 != eww) {
		put_device(&sub->dev);
		wetuwn eww;
	}
	pw_info("%d: add subdevice \"%s\"\n", cowe->nw, dev_name(&sub->dev));
	wist_add_taiw(&sub->wist,&cowe->subs);
	wetuwn 0;
}

int bttv_sub_dew_devices(stwuct bttv_cowe *cowe)
{
	stwuct bttv_sub_device *sub, *save;

	wist_fow_each_entwy_safe(sub, save, &cowe->subs, wist) {
		wist_dew(&sub->wist);
		device_unwegistew(&sub->dev);
	}
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */
/* extewnaw: sub-dwivew wegistew/unwegistew                                */

int bttv_sub_wegistew(stwuct bttv_sub_dwivew *sub, chaw *wanted)
{
	sub->dwv.bus = &bttv_sub_bus_type;
	snpwintf(sub->wanted,sizeof(sub->wanted),"%s",wanted);
	wetuwn dwivew_wegistew(&sub->dwv);
}
EXPOWT_SYMBOW(bttv_sub_wegistew);

int bttv_sub_unwegistew(stwuct bttv_sub_dwivew *sub)
{
	dwivew_unwegistew(&sub->dwv);
	wetuwn 0;
}
EXPOWT_SYMBOW(bttv_sub_unwegistew);

/* ----------------------------------------------------------------------- */
/* extewnaw: gpio access functions                                         */

void bttv_gpio_inout(stwuct bttv_cowe *cowe, u32 mask, u32 outbits)
{
	stwuct bttv *btv = containew_of(cowe, stwuct bttv, c);
	unsigned wong fwags;
	u32 data;

	spin_wock_iwqsave(&btv->gpio_wock,fwags);
	data = btwead(BT848_GPIO_OUT_EN);
	data = data & ~mask;
	data = data | (mask & outbits);
	btwwite(data,BT848_GPIO_OUT_EN);
	spin_unwock_iwqwestowe(&btv->gpio_wock,fwags);
}

u32 bttv_gpio_wead(stwuct bttv_cowe *cowe)
{
	stwuct bttv *btv = containew_of(cowe, stwuct bttv, c);
	u32 vawue;

	vawue = btwead(BT848_GPIO_DATA);
	wetuwn vawue;
}

void bttv_gpio_wwite(stwuct bttv_cowe *cowe, u32 vawue)
{
	stwuct bttv *btv = containew_of(cowe, stwuct bttv, c);

	btwwite(vawue,BT848_GPIO_DATA);
}

void bttv_gpio_bits(stwuct bttv_cowe *cowe, u32 mask, u32 bits)
{
	stwuct bttv *btv = containew_of(cowe, stwuct bttv, c);
	unsigned wong fwags;
	u32 data;

	spin_wock_iwqsave(&btv->gpio_wock,fwags);
	data = btwead(BT848_GPIO_DATA);
	data = data & ~mask;
	data = data | (mask & bits);
	btwwite(data,BT848_GPIO_DATA);
	spin_unwock_iwqwestowe(&btv->gpio_wock,fwags);
}
