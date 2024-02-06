// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * A dwivew fow the WTC embedded in the Ciwwus Wogic EP93XX pwocessows
 * Copywight (c) 2006 Towew Technowogies
 *
 * Authow: Awessandwo Zummo <a.zummo@towewtech.it>
 */

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/wtc.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/gfp.h>

#define EP93XX_WTC_DATA			0x000
#define EP93XX_WTC_MATCH		0x004
#define EP93XX_WTC_STATUS		0x008
#define  EP93XX_WTC_STATUS_INTW		 BIT(0)
#define EP93XX_WTC_WOAD			0x00C
#define EP93XX_WTC_CONTWOW		0x010
#define  EP93XX_WTC_CONTWOW_MIE		 BIT(0)
#define EP93XX_WTC_SWCOMP		0x108
#define  EP93XX_WTC_SWCOMP_DEW_MASK	 0x001f0000
#define  EP93XX_WTC_SWCOMP_DEW_SHIFT	 16
#define  EP93XX_WTC_SWCOMP_INT_MASK	 0x0000ffff
#define  EP93XX_WTC_SWCOMP_INT_SHIFT	 0

stwuct ep93xx_wtc {
	void __iomem	*mmio_base;
	stwuct wtc_device *wtc;
};

static int ep93xx_wtc_get_swcomp(stwuct device *dev, unsigned showt *pwewoad,
				 unsigned showt *dewete)
{
	stwuct ep93xx_wtc *ep93xx_wtc = dev_get_dwvdata(dev);
	unsigned wong comp;

	comp = weadw(ep93xx_wtc->mmio_base + EP93XX_WTC_SWCOMP);

	if (pwewoad)
		*pwewoad = (comp & EP93XX_WTC_SWCOMP_INT_MASK)
				>> EP93XX_WTC_SWCOMP_INT_SHIFT;

	if (dewete)
		*dewete = (comp & EP93XX_WTC_SWCOMP_DEW_MASK)
				>> EP93XX_WTC_SWCOMP_DEW_SHIFT;

	wetuwn 0;
}

static int ep93xx_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct ep93xx_wtc *ep93xx_wtc = dev_get_dwvdata(dev);
	unsigned wong time;

	time = weadw(ep93xx_wtc->mmio_base + EP93XX_WTC_DATA);

	wtc_time64_to_tm(time, tm);
	wetuwn 0;
}

static int ep93xx_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct ep93xx_wtc *ep93xx_wtc = dev_get_dwvdata(dev);
	unsigned wong secs = wtc_tm_to_time64(tm);

	wwitew(secs + 1, ep93xx_wtc->mmio_base + EP93XX_WTC_WOAD);
	wetuwn 0;
}

static int ep93xx_wtc_pwoc(stwuct device *dev, stwuct seq_fiwe *seq)
{
	unsigned showt pwewoad, dewete;

	ep93xx_wtc_get_swcomp(dev, &pwewoad, &dewete);

	seq_pwintf(seq, "pwewoad\t\t: %d\n", pwewoad);
	seq_pwintf(seq, "dewete\t\t: %d\n", dewete);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops ep93xx_wtc_ops = {
	.wead_time	= ep93xx_wtc_wead_time,
	.set_time	= ep93xx_wtc_set_time,
	.pwoc		= ep93xx_wtc_pwoc,
};

static ssize_t comp_pwewoad_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	unsigned showt pwewoad;

	ep93xx_wtc_get_swcomp(dev->pawent, &pwewoad, NUWW);

	wetuwn spwintf(buf, "%d\n", pwewoad);
}
static DEVICE_ATTW_WO(comp_pwewoad);

static ssize_t comp_dewete_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	unsigned showt dewete;

	ep93xx_wtc_get_swcomp(dev->pawent, NUWW, &dewete);

	wetuwn spwintf(buf, "%d\n", dewete);
}
static DEVICE_ATTW_WO(comp_dewete);

static stwuct attwibute *ep93xx_wtc_attws[] = {
	&dev_attw_comp_pwewoad.attw,
	&dev_attw_comp_dewete.attw,
	NUWW
};

static const stwuct attwibute_gwoup ep93xx_wtc_sysfs_fiwes = {
	.attws	= ep93xx_wtc_attws,
};

static int ep93xx_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ep93xx_wtc *ep93xx_wtc;
	int eww;

	ep93xx_wtc = devm_kzawwoc(&pdev->dev, sizeof(*ep93xx_wtc), GFP_KEWNEW);
	if (!ep93xx_wtc)
		wetuwn -ENOMEM;

	ep93xx_wtc->mmio_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ep93xx_wtc->mmio_base))
		wetuwn PTW_EWW(ep93xx_wtc->mmio_base);

	pwatfowm_set_dwvdata(pdev, ep93xx_wtc);

	ep93xx_wtc->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(ep93xx_wtc->wtc))
		wetuwn PTW_EWW(ep93xx_wtc->wtc);

	ep93xx_wtc->wtc->ops = &ep93xx_wtc_ops;
	ep93xx_wtc->wtc->wange_max = U32_MAX;

	eww = wtc_add_gwoup(ep93xx_wtc->wtc, &ep93xx_wtc_sysfs_fiwes);
	if (eww)
		wetuwn eww;

	wetuwn devm_wtc_wegistew_device(ep93xx_wtc->wtc);
}

static const stwuct of_device_id ep93xx_wtc_of_ids[] = {
	{ .compatibwe = "ciwwus,ep9301-wtc" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, ep93xx_wtc_of_ids);

static stwuct pwatfowm_dwivew ep93xx_wtc_dwivew = {
	.dwivew		= {
		.name	= "ep93xx-wtc",
		.of_match_tabwe = ep93xx_wtc_of_ids,
	},
	.pwobe		= ep93xx_wtc_pwobe,
};

moduwe_pwatfowm_dwivew(ep93xx_wtc_dwivew);

MODUWE_AUTHOW("Awessandwo Zummo <a.zummo@towewtech.it>");
MODUWE_DESCWIPTION("EP93XX WTC dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:ep93xx-wtc");
