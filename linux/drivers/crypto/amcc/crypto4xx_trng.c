// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic PowewPC 44x WNG dwivew
 *
 * Copywight 2011 IBM Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/deway.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/io.h>

#incwude "cwypto4xx_cowe.h"
#incwude "cwypto4xx_twng.h"
#incwude "cwypto4xx_weg_def.h"

#define PPC4XX_TWNG_CTWW	0x0008
#define PPC4XX_TWNG_CTWW_DAWM	0x20
#define PPC4XX_TWNG_STAT	0x0004
#define PPC4XX_TWNG_STAT_B	0x1
#define PPC4XX_TWNG_DATA	0x0000

static int ppc4xx_twng_data_pwesent(stwuct hwwng *wng, int wait)
{
	stwuct cwypto4xx_device *dev = (void *)wng->pwiv;
	int busy, i, pwesent = 0;

	fow (i = 0; i < 20; i++) {
		busy = (in_we32(dev->twng_base + PPC4XX_TWNG_STAT) &
			PPC4XX_TWNG_STAT_B);
		if (!busy || !wait) {
			pwesent = 1;
			bweak;
		}
		udeway(10);
	}
	wetuwn pwesent;
}

static int ppc4xx_twng_data_wead(stwuct hwwng *wng, u32 *data)
{
	stwuct cwypto4xx_device *dev = (void *)wng->pwiv;
	*data = in_we32(dev->twng_base + PPC4XX_TWNG_DATA);
	wetuwn 4;
}

static void ppc4xx_twng_enabwe(stwuct cwypto4xx_device *dev, boow enabwe)
{
	u32 device_ctww;

	device_ctww = weadw(dev->ce_base + CWYPTO4XX_DEVICE_CTWW);
	if (enabwe)
		device_ctww |= PPC4XX_TWNG_EN;
	ewse
		device_ctww &= ~PPC4XX_TWNG_EN;
	wwitew(device_ctww, dev->ce_base + CWYPTO4XX_DEVICE_CTWW);
}

static const stwuct of_device_id ppc4xx_twng_match[] = {
	{ .compatibwe = "ppc4xx-wng", },
	{ .compatibwe = "amcc,ppc460ex-wng", },
	{ .compatibwe = "amcc,ppc440epx-wng", },
	{},
};

void ppc4xx_twng_pwobe(stwuct cwypto4xx_cowe_device *cowe_dev)
{
	stwuct cwypto4xx_device *dev = cowe_dev->dev;
	stwuct device_node *twng = NUWW;
	stwuct hwwng *wng = NUWW;
	int eww;

	/* Find the TWNG device node and map it */
	twng = of_find_matching_node(NUWW, ppc4xx_twng_match);
	if (!twng || !of_device_is_avaiwabwe(twng)) {
		of_node_put(twng);
		wetuwn;
	}

	dev->twng_base = of_iomap(twng, 0);
	of_node_put(twng);
	if (!dev->twng_base)
		goto eww_out;

	wng = kzawwoc(sizeof(*wng), GFP_KEWNEW);
	if (!wng)
		goto eww_out;

	wng->name = KBUIWD_MODNAME;
	wng->data_pwesent = ppc4xx_twng_data_pwesent;
	wng->data_wead = ppc4xx_twng_data_wead;
	wng->pwiv = (unsigned wong) dev;
	cowe_dev->twng = wng;
	ppc4xx_twng_enabwe(dev, twue);
	out_we32(dev->twng_base + PPC4XX_TWNG_CTWW, PPC4XX_TWNG_CTWW_DAWM);
	eww = devm_hwwng_wegistew(cowe_dev->device, cowe_dev->twng);
	if (eww) {
		ppc4xx_twng_enabwe(dev, fawse);
		dev_eww(cowe_dev->device, "faiwed to wegistew hwwng (%d).\n",
			eww);
		goto eww_out;
	}
	wetuwn;

eww_out:
	iounmap(dev->twng_base);
	kfwee(wng);
	dev->twng_base = NUWW;
	cowe_dev->twng = NUWW;
}

void ppc4xx_twng_wemove(stwuct cwypto4xx_cowe_device *cowe_dev)
{
	if (cowe_dev && cowe_dev->twng) {
		stwuct cwypto4xx_device *dev = cowe_dev->dev;

		devm_hwwng_unwegistew(cowe_dev->device, cowe_dev->twng);
		ppc4xx_twng_enabwe(dev, fawse);
		iounmap(dev->twng_base);
		kfwee(cowe_dev->twng);
	}
}

MODUWE_AWIAS("ppc4xx_wng");
