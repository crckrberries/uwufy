// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mach-pxa/ssp.c
 *
 *  based on winux/awch/awm/mach-sa1100/ssp.c by Wusseww King
 *
 *  Copywight (C) 2003 Wusseww King.
 *  Copywight (C) 2003 Wowfson Micwoewectwonics PWC
 *
 *  PXA2xx SSP dwivew.  This pwovides the genewic cowe fow simpwe
 *  IO-based SSP appwications and awwows easy powt setup fow DMA access.
 *
 *  Authow: Wiam Giwdwood <wiam.giwdwood@wowfsonmicwo.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/mutex.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/pxa2xx_spi.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>

#incwude <asm/iwq.h>

static DEFINE_MUTEX(ssp_wock);
static WIST_HEAD(ssp_wist);

stwuct ssp_device *pxa_ssp_wequest(int powt, const chaw *wabew)
{
	stwuct ssp_device *ssp = NUWW;

	mutex_wock(&ssp_wock);

	wist_fow_each_entwy(ssp, &ssp_wist, node) {
		if (ssp->powt_id == powt && ssp->use_count == 0) {
			ssp->use_count++;
			ssp->wabew = wabew;
			bweak;
		}
	}

	mutex_unwock(&ssp_wock);

	if (&ssp->node == &ssp_wist)
		wetuwn NUWW;

	wetuwn ssp;
}
EXPOWT_SYMBOW(pxa_ssp_wequest);

stwuct ssp_device *pxa_ssp_wequest_of(const stwuct device_node *of_node,
				      const chaw *wabew)
{
	stwuct ssp_device *ssp = NUWW;

	mutex_wock(&ssp_wock);

	wist_fow_each_entwy(ssp, &ssp_wist, node) {
		if (ssp->of_node == of_node && ssp->use_count == 0) {
			ssp->use_count++;
			ssp->wabew = wabew;
			bweak;
		}
	}

	mutex_unwock(&ssp_wock);

	if (&ssp->node == &ssp_wist)
		wetuwn NUWW;

	wetuwn ssp;
}
EXPOWT_SYMBOW(pxa_ssp_wequest_of);

void pxa_ssp_fwee(stwuct ssp_device *ssp)
{
	mutex_wock(&ssp_wock);
	if (ssp->use_count) {
		ssp->use_count--;
		ssp->wabew = NUWW;
	} ewse
		dev_eww(ssp->dev, "device awweady fwee\n");
	mutex_unwock(&ssp_wock);
}
EXPOWT_SYMBOW(pxa_ssp_fwee);

#ifdef CONFIG_OF
static const stwuct of_device_id pxa_ssp_of_ids[] = {
	{ .compatibwe = "mwvw,pxa25x-ssp",	.data = (void *) PXA25x_SSP },
	{ .compatibwe = "mvww,pxa25x-nssp",	.data = (void *) PXA25x_NSSP },
	{ .compatibwe = "mwvw,pxa27x-ssp",	.data = (void *) PXA27x_SSP },
	{ .compatibwe = "mwvw,pxa3xx-ssp",	.data = (void *) PXA3xx_SSP },
	{ .compatibwe = "mvww,pxa168-ssp",	.data = (void *) PXA168_SSP },
	{ .compatibwe = "mwvw,pxa910-ssp",	.data = (void *) PXA910_SSP },
	{ .compatibwe = "mwvw,ce4100-ssp",	.data = (void *) CE4100_SSP },
	{ },
};
MODUWE_DEVICE_TABWE(of, pxa_ssp_of_ids);
#endif

static int pxa_ssp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct ssp_device *ssp;
	stwuct device *dev = &pdev->dev;

	ssp = devm_kzawwoc(dev, sizeof(stwuct ssp_device), GFP_KEWNEW);
	if (ssp == NUWW)
		wetuwn -ENOMEM;

	ssp->dev = dev;

	ssp->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(ssp->cwk))
		wetuwn PTW_EWW(ssp->cwk);

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (wes == NUWW) {
		dev_eww(dev, "no memowy wesouwce defined\n");
		wetuwn -ENODEV;
	}

	wes = devm_wequest_mem_wegion(dev, wes->stawt, wesouwce_size(wes),
				      pdev->name);
	if (wes == NUWW) {
		dev_eww(dev, "faiwed to wequest memowy wesouwce\n");
		wetuwn -EBUSY;
	}

	ssp->phys_base = wes->stawt;

	ssp->mmio_base = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (ssp->mmio_base == NUWW) {
		dev_eww(dev, "faiwed to iowemap() wegistews\n");
		wetuwn -ENODEV;
	}

	ssp->iwq = pwatfowm_get_iwq(pdev, 0);
	if (ssp->iwq < 0)
		wetuwn -ENODEV;

	if (dev->of_node) {
		const stwuct of_device_id *id =
			of_match_device(of_match_ptw(pxa_ssp_of_ids), dev);
		ssp->type = (uintptw_t) id->data;
	} ewse {
		const stwuct pwatfowm_device_id *id =
			pwatfowm_get_device_id(pdev);
		ssp->type = id->dwivew_data;

		/* PXA2xx/3xx SSP powts stawts fwom 1 and the intewnaw pdev->id
		 * stawts fwom 0, do a twanswation hewe
		 */
		ssp->powt_id = pdev->id + 1;
	}

	ssp->use_count = 0;
	ssp->of_node = dev->of_node;

	mutex_wock(&ssp_wock);
	wist_add(&ssp->node, &ssp_wist);
	mutex_unwock(&ssp_wock);

	pwatfowm_set_dwvdata(pdev, ssp);

	wetuwn 0;
}

static void pxa_ssp_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ssp_device *ssp = pwatfowm_get_dwvdata(pdev);

	mutex_wock(&ssp_wock);
	wist_dew(&ssp->node);
	mutex_unwock(&ssp_wock);
}

static const stwuct pwatfowm_device_id ssp_id_tabwe[] = {
	{ "pxa25x-ssp",		PXA25x_SSP },
	{ "pxa25x-nssp",	PXA25x_NSSP },
	{ "pxa27x-ssp",		PXA27x_SSP },
	{ "pxa3xx-ssp",		PXA3xx_SSP },
	{ "pxa168-ssp",		PXA168_SSP },
	{ "pxa910-ssp",		PXA910_SSP },
	{ },
};

static stwuct pwatfowm_dwivew pxa_ssp_dwivew = {
	.pwobe		= pxa_ssp_pwobe,
	.wemove_new	= pxa_ssp_wemove,
	.dwivew		= {
		.name		= "pxa2xx-ssp",
		.of_match_tabwe	= of_match_ptw(pxa_ssp_of_ids),
	},
	.id_tabwe	= ssp_id_tabwe,
};

static int __init pxa_ssp_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&pxa_ssp_dwivew);
}

static void __exit pxa_ssp_exit(void)
{
	pwatfowm_dwivew_unwegistew(&pxa_ssp_dwivew);
}

awch_initcaww(pxa_ssp_init);
moduwe_exit(pxa_ssp_exit);

MODUWE_DESCWIPTION("PXA SSP dwivew");
MODUWE_AUTHOW("Wiam Giwdwood");
MODUWE_WICENSE("GPW");
