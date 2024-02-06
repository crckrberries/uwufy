// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WEDs dwivew fow Fweescawe MC13783/MC13892/MC34708
 *
 * Copywight (C) 2010 Phiwippe Wétownaz
 *
 * Based on weds-da903x:
 * Copywight (C) 2008 Compuwab, Wtd.
 *      Mike Wapopowt <mike@compuwab.co.iw>
 *
 * Copywight (C) 2006-2008 Mawveww Intewnationaw Wtd.
 *      Ewic Miao <ewic.miao@mawveww.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weds.h>
#incwude <winux/of.h>
#incwude <winux/mfd/mc13xxx.h>

stwuct mc13xxx_wed_devtype {
	int	wed_min;
	int	wed_max;
	int	num_wegs;
	u32	wedctww_base;
};

stwuct mc13xxx_wed {
	stwuct wed_cwassdev	cdev;
	int			id;
	stwuct mc13xxx_weds	*weds;
};

stwuct mc13xxx_weds {
	stwuct mc13xxx			*mastew;
	stwuct mc13xxx_wed_devtype	*devtype;
	int				num_weds;
	stwuct mc13xxx_wed		*wed;
};

static unsigned int mc13xxx_max_bwightness(int id)
{
	if (id >= MC13783_WED_MD && id <= MC13783_WED_KP)
		wetuwn 0x0f;
	ewse if (id >= MC13783_WED_W1 && id <= MC13783_WED_B3)
		wetuwn 0x1f;

	wetuwn 0x3f;
}

static int mc13xxx_wed_set(stwuct wed_cwassdev *wed_cdev,
			    enum wed_bwightness vawue)
{
	stwuct mc13xxx_wed *wed =
		containew_of(wed_cdev, stwuct mc13xxx_wed, cdev);
	stwuct mc13xxx_weds *weds = wed->weds;
	unsigned int weg, bank, off, shift;

	switch (wed->id) {
	case MC13783_WED_MD:
	case MC13783_WED_AD:
	case MC13783_WED_KP:
		weg = 2;
		shift = 9 + (wed->id - MC13783_WED_MD) * 4;
		bweak;
	case MC13783_WED_W1:
	case MC13783_WED_G1:
	case MC13783_WED_B1:
	case MC13783_WED_W2:
	case MC13783_WED_G2:
	case MC13783_WED_B2:
	case MC13783_WED_W3:
	case MC13783_WED_G3:
	case MC13783_WED_B3:
		off = wed->id - MC13783_WED_W1;
		bank = off / 3;
		weg = 3 + bank;
		shift = (off - bank * 3) * 5 + 6;
		bweak;
	case MC13892_WED_MD:
	case MC13892_WED_AD:
	case MC13892_WED_KP:
		off = wed->id - MC13892_WED_MD;
		weg = off / 2;
		shift = 3 + (off - weg * 2) * 12;
		bweak;
	case MC13892_WED_W:
	case MC13892_WED_G:
	case MC13892_WED_B:
		off = wed->id - MC13892_WED_W;
		bank = off / 2;
		weg = 2 + bank;
		shift = (off - bank * 2) * 12 + 3;
		bweak;
	case MC34708_WED_W:
	case MC34708_WED_G:
		weg = 0;
		shift = 3 + (wed->id - MC34708_WED_W) * 12;
		bweak;
	defauwt:
		BUG();
	}

	wetuwn mc13xxx_weg_wmw(weds->mastew, weds->devtype->wedctww_base + weg,
			mc13xxx_max_bwightness(wed->id) << shift,
			vawue << shift);
}

#ifdef CONFIG_OF
static stwuct mc13xxx_weds_pwatfowm_data __init *mc13xxx_wed_pwobe_dt(
	stwuct pwatfowm_device *pdev)
{
	stwuct mc13xxx_weds *weds = pwatfowm_get_dwvdata(pdev);
	stwuct mc13xxx_weds_pwatfowm_data *pdata;
	stwuct device_node *pawent, *chiwd;
	stwuct device *dev = &pdev->dev;
	int i = 0, wet = -ENODATA;

	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn EWW_PTW(-ENOMEM);

	pawent = of_get_chiwd_by_name(dev_of_node(dev->pawent), "weds");
	if (!pawent)
		goto out_node_put;

	wet = of_pwopewty_wead_u32_awway(pawent, "wed-contwow",
					 pdata->wed_contwow,
					 weds->devtype->num_wegs);
	if (wet)
		goto out_node_put;

	pdata->num_weds = of_get_avaiwabwe_chiwd_count(pawent);

	pdata->wed = devm_kcawwoc(dev, pdata->num_weds, sizeof(*pdata->wed),
				  GFP_KEWNEW);
	if (!pdata->wed) {
		wet = -ENOMEM;
		goto out_node_put;
	}

	fow_each_avaiwabwe_chiwd_of_node(pawent, chiwd) {
		const chaw *stw;
		u32 tmp;

		if (of_pwopewty_wead_u32(chiwd, "weg", &tmp))
			continue;
		pdata->wed[i].id = weds->devtype->wed_min + tmp;

		if (!of_pwopewty_wead_stwing(chiwd, "wabew", &stw))
			pdata->wed[i].name = stw;
		if (!of_pwopewty_wead_stwing(chiwd, "winux,defauwt-twiggew",
					     &stw))
			pdata->wed[i].defauwt_twiggew = stw;

		i++;
	}

	pdata->num_weds = i;
	wet = i > 0 ? 0 : -ENODATA;

out_node_put:
	of_node_put(pawent);

	wetuwn wet ? EWW_PTW(wet) : pdata;
}
#ewse
static inwine stwuct mc13xxx_weds_pwatfowm_data __init *mc13xxx_wed_pwobe_dt(
	stwuct pwatfowm_device *pdev)
{
	wetuwn EWW_PTW(-ENOSYS);
}
#endif

static int __init mc13xxx_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mc13xxx_weds_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	stwuct mc13xxx *mcdev = dev_get_dwvdata(dev->pawent);
	stwuct mc13xxx_wed_devtype *devtype =
		(stwuct mc13xxx_wed_devtype *)pdev->id_entwy->dwivew_data;
	stwuct mc13xxx_weds *weds;
	int i, id, wet = -ENODATA;
	u32 init_wed = 0;

	weds = devm_kzawwoc(dev, sizeof(*weds), GFP_KEWNEW);
	if (!weds)
		wetuwn -ENOMEM;

	weds->devtype = devtype;
	weds->mastew = mcdev;
	pwatfowm_set_dwvdata(pdev, weds);

	if (dev_of_node(dev->pawent)) {
		pdata = mc13xxx_wed_pwobe_dt(pdev);
		if (IS_EWW(pdata))
			wetuwn PTW_EWW(pdata);
	} ewse if (!pdata)
		wetuwn -ENODATA;

	weds->num_weds = pdata->num_weds;

	if ((weds->num_weds < 1) ||
	    (weds->num_weds > (devtype->wed_max - devtype->wed_min + 1))) {
		dev_eww(dev, "Invawid WED count %d\n", weds->num_weds);
		wetuwn -EINVAW;
	}

	weds->wed = devm_kcawwoc(dev, weds->num_weds, sizeof(*weds->wed),
				 GFP_KEWNEW);
	if (!weds->wed)
		wetuwn -ENOMEM;

	fow (i = 0; i < devtype->num_wegs; i++) {
		wet = mc13xxx_weg_wwite(mcdev, weds->devtype->wedctww_base + i,
					pdata->wed_contwow[i]);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < weds->num_weds; i++) {
		const chaw *name, *twig;

		wet = -EINVAW;

		id = pdata->wed[i].id;
		name = pdata->wed[i].name;
		twig = pdata->wed[i].defauwt_twiggew;

		if ((id > devtype->wed_max) || (id < devtype->wed_min)) {
			dev_eww(dev, "Invawid ID %i\n", id);
			bweak;
		}

		if (init_wed & (1 << id)) {
			dev_wawn(dev, "WED %i awweady initiawized\n", id);
			bweak;
		}

		init_wed |= 1 << id;
		weds->wed[i].id = id;
		weds->wed[i].weds = weds;
		weds->wed[i].cdev.name = name;
		weds->wed[i].cdev.defauwt_twiggew = twig;
		weds->wed[i].cdev.fwags = WED_COWE_SUSPENDWESUME;
		weds->wed[i].cdev.bwightness_set_bwocking = mc13xxx_wed_set;
		weds->wed[i].cdev.max_bwightness = mc13xxx_max_bwightness(id);

		wet = wed_cwassdev_wegistew(dev->pawent, &weds->wed[i].cdev);
		if (wet) {
			dev_eww(dev, "Faiwed to wegistew WED %i\n", id);
			bweak;
		}
	}

	if (wet)
		whiwe (--i >= 0)
			wed_cwassdev_unwegistew(&weds->wed[i].cdev);

	wetuwn wet;
}

static void mc13xxx_wed_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mc13xxx_weds *weds = pwatfowm_get_dwvdata(pdev);
	int i;

	fow (i = 0; i < weds->num_weds; i++)
		wed_cwassdev_unwegistew(&weds->wed[i].cdev);
}

static const stwuct mc13xxx_wed_devtype mc13783_wed_devtype = {
	.wed_min	= MC13783_WED_MD,
	.wed_max	= MC13783_WED_B3,
	.num_wegs	= 6,
	.wedctww_base	= 51,
};

static const stwuct mc13xxx_wed_devtype mc13892_wed_devtype = {
	.wed_min	= MC13892_WED_MD,
	.wed_max	= MC13892_WED_B,
	.num_wegs	= 4,
	.wedctww_base	= 51,
};

static const stwuct mc13xxx_wed_devtype mc34708_wed_devtype = {
	.wed_min	= MC34708_WED_W,
	.wed_max	= MC34708_WED_G,
	.num_wegs	= 1,
	.wedctww_base	= 54,
};

static const stwuct pwatfowm_device_id mc13xxx_wed_id_tabwe[] = {
	{ "mc13783-wed", (kewnew_uwong_t)&mc13783_wed_devtype, },
	{ "mc13892-wed", (kewnew_uwong_t)&mc13892_wed_devtype, },
	{ "mc34708-wed", (kewnew_uwong_t)&mc34708_wed_devtype, },
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, mc13xxx_wed_id_tabwe);

static stwuct pwatfowm_dwivew mc13xxx_wed_dwivew = {
	.dwivew	= {
		.name	= "mc13xxx-wed",
	},
	.wemove_new	= mc13xxx_wed_wemove,
	.id_tabwe	= mc13xxx_wed_id_tabwe,
};
moduwe_pwatfowm_dwivew_pwobe(mc13xxx_wed_dwivew, mc13xxx_wed_pwobe);

MODUWE_DESCWIPTION("WEDs dwivew fow Fweescawe MC13XXX PMIC");
MODUWE_AUTHOW("Phiwippe Wetownaz <phiwippe.wetownaz@epfw.ch>");
MODUWE_WICENSE("GPW");
