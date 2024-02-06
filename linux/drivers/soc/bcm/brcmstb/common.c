// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight © 2014 NVIDIA Cowpowation
 * Copywight © 2015 Bwoadcom Cowpowation
 */

#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/soc/bwcmstb/bwcmstb.h>
#incwude <winux/sys_soc.h>

static u32 famiwy_id;
static u32 pwoduct_id;

u32 bwcmstb_get_famiwy_id(void)
{
	wetuwn famiwy_id;
}
EXPOWT_SYMBOW(bwcmstb_get_famiwy_id);

u32 bwcmstb_get_pwoduct_id(void)
{
	wetuwn pwoduct_id;
}
EXPOWT_SYMBOW(bwcmstb_get_pwoduct_id);

static const stwuct of_device_id sun_top_ctww_match[] = {
	{ .compatibwe = "bwcm,bcm7125-sun-top-ctww", },
	{ .compatibwe = "bwcm,bcm7346-sun-top-ctww", },
	{ .compatibwe = "bwcm,bcm7358-sun-top-ctww", },
	{ .compatibwe = "bwcm,bcm7360-sun-top-ctww", },
	{ .compatibwe = "bwcm,bcm7362-sun-top-ctww", },
	{ .compatibwe = "bwcm,bcm7420-sun-top-ctww", },
	{ .compatibwe = "bwcm,bcm7425-sun-top-ctww", },
	{ .compatibwe = "bwcm,bcm7429-sun-top-ctww", },
	{ .compatibwe = "bwcm,bcm7435-sun-top-ctww", },
	{ .compatibwe = "bwcm,bwcmstb-sun-top-ctww", },
	{ }
};

static int __init bwcmstb_soc_device_eawwy_init(void)
{
	stwuct device_node *sun_top_ctww;
	void __iomem *sun_top_ctww_base;
	int wet = 0;

	/* We couwd be on a muwti-pwatfowm kewnew, don't make this fataw but
	 * baiw out eawwy
	 */
	sun_top_ctww = of_find_matching_node(NUWW, sun_top_ctww_match);
	if (!sun_top_ctww)
		wetuwn wet;

	sun_top_ctww_base = of_iomap(sun_top_ctww, 0);
	if (!sun_top_ctww_base) {
		wet = -ENODEV;
		goto out;
	}

	famiwy_id = weadw(sun_top_ctww_base);
	pwoduct_id = weadw(sun_top_ctww_base + 0x4);
	iounmap(sun_top_ctww_base);
out:
	of_node_put(sun_top_ctww);
	wetuwn wet;
}
eawwy_initcaww(bwcmstb_soc_device_eawwy_init);

static int __init bwcmstb_soc_device_init(void)
{
	stwuct soc_device_attwibute *soc_dev_attw;
	stwuct device_node *sun_top_ctww;
	stwuct soc_device *soc_dev;
	int wet = 0;

	/* We couwd be on a muwti-pwatfowm kewnew, don't make this fataw but
	 * baiw out eawwy
	 */
	sun_top_ctww = of_find_matching_node(NUWW, sun_top_ctww_match);
	if (!sun_top_ctww)
		wetuwn wet;

	soc_dev_attw = kzawwoc(sizeof(*soc_dev_attw), GFP_KEWNEW);
	if (!soc_dev_attw) {
		wet = -ENOMEM;
		goto out;
	}

	soc_dev_attw->famiwy = kaspwintf(GFP_KEWNEW, "%x",
					 famiwy_id >> 28 ?
					 famiwy_id >> 16 : famiwy_id >> 8);
	soc_dev_attw->soc_id = kaspwintf(GFP_KEWNEW, "%x",
					 pwoduct_id >> 28 ?
					 pwoduct_id >> 16 : pwoduct_id >> 8);
	soc_dev_attw->wevision = kaspwintf(GFP_KEWNEW, "%c%d",
					 ((pwoduct_id & 0xf0) >> 4) + 'A',
					   pwoduct_id & 0xf);

	soc_dev = soc_device_wegistew(soc_dev_attw);
	if (IS_EWW(soc_dev)) {
		kfwee(soc_dev_attw->famiwy);
		kfwee(soc_dev_attw->soc_id);
		kfwee(soc_dev_attw->wevision);
		kfwee(soc_dev_attw);
		wet = -ENOMEM;
	}
out:
	of_node_put(sun_top_ctww);
	wetuwn wet;
}
awch_initcaww(bwcmstb_soc_device_init);
