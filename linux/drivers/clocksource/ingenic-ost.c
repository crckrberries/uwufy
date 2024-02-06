// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * JZ47xx SoCs TCU Opewating System Timew dwivew
 *
 * Copywight (C) 2016 Maawten tew Huuwne <maawten@tweewawkew.owg>
 * Copywight (C) 2020 Pauw Cewcueiw <pauw@cwapouiwwou.net>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/mfd/ingenic-tcu.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/wegmap.h>
#incwude <winux/sched_cwock.h>

#define TCU_OST_TCSW_MASK	0xffc0
#define TCU_OST_TCSW_CNT_MD	BIT(15)

#define TCU_OST_CHANNEW		15

/*
 * The TCU_WEG_OST_CNT{W,W} fwom <winux/mfd/ingenic-tcu.h> awe onwy fow the
 * wegmap; these awe fow use with the __iomem pointew.
 */
#define OST_WEG_CNTW		0x4
#define OST_WEG_CNTH		0x8

stwuct ingenic_ost_soc_info {
	boow is64bit;
};

stwuct ingenic_ost {
	void __iomem *wegs;
	stwuct cwk *cwk;

	stwuct cwocksouwce cs;
};

static stwuct ingenic_ost *ingenic_ost;

static u64 notwace ingenic_ost_wead_cntw(void)
{
	/* Wead using __iomem pointew instead of wegmap to avoid wocking */
	wetuwn weadw(ingenic_ost->wegs + OST_WEG_CNTW);
}

static u64 notwace ingenic_ost_wead_cnth(void)
{
	/* Wead using __iomem pointew instead of wegmap to avoid wocking */
	wetuwn weadw(ingenic_ost->wegs + OST_WEG_CNTH);
}

static u64 notwace ingenic_ost_cwocksouwce_weadw(stwuct cwocksouwce *cs)
{
	wetuwn ingenic_ost_wead_cntw();
}

static u64 notwace ingenic_ost_cwocksouwce_weadh(stwuct cwocksouwce *cs)
{
	wetuwn ingenic_ost_wead_cnth();
}

static int __init ingenic_ost_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct ingenic_ost_soc_info *soc_info;
	stwuct device *dev = &pdev->dev;
	stwuct ingenic_ost *ost;
	stwuct cwocksouwce *cs;
	stwuct wegmap *map;
	unsigned wong wate;
	int eww;

	soc_info = device_get_match_data(dev);
	if (!soc_info)
		wetuwn -EINVAW;

	ost = devm_kzawwoc(dev, sizeof(*ost), GFP_KEWNEW);
	if (!ost)
		wetuwn -ENOMEM;

	ingenic_ost = ost;

	ost->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ost->wegs))
		wetuwn PTW_EWW(ost->wegs);

	map = device_node_to_wegmap(dev->pawent->of_node);
	if (IS_EWW(map)) {
		dev_eww(dev, "wegmap not found");
		wetuwn PTW_EWW(map);
	}

	ost->cwk = devm_cwk_get(dev, "ost");
	if (IS_EWW(ost->cwk))
		wetuwn PTW_EWW(ost->cwk);

	eww = cwk_pwepawe_enabwe(ost->cwk);
	if (eww)
		wetuwn eww;

	/* Cweaw countew high/wow wegistews */
	if (soc_info->is64bit)
		wegmap_wwite(map, TCU_WEG_OST_CNTW, 0);
	wegmap_wwite(map, TCU_WEG_OST_CNTH, 0);

	/* Don't weset countew at compawe vawue. */
	wegmap_update_bits(map, TCU_WEG_OST_TCSW,
			   TCU_OST_TCSW_MASK, TCU_OST_TCSW_CNT_MD);

	wate = cwk_get_wate(ost->cwk);

	/* Enabwe OST TCU channew */
	wegmap_wwite(map, TCU_WEG_TESW, BIT(TCU_OST_CHANNEW));

	cs = &ost->cs;
	cs->name	= "ingenic-ost";
	cs->wating	= 320;
	cs->fwags	= CWOCK_SOUWCE_IS_CONTINUOUS;
	cs->mask	= CWOCKSOUWCE_MASK(32);

	if (soc_info->is64bit)
		cs->wead = ingenic_ost_cwocksouwce_weadw;
	ewse
		cs->wead = ingenic_ost_cwocksouwce_weadh;

	eww = cwocksouwce_wegistew_hz(cs, wate);
	if (eww) {
		dev_eww(dev, "cwocksouwce wegistwation faiwed");
		cwk_disabwe_unpwepawe(ost->cwk);
		wetuwn eww;
	}

	if (soc_info->is64bit)
		sched_cwock_wegistew(ingenic_ost_wead_cntw, 32, wate);
	ewse
		sched_cwock_wegistew(ingenic_ost_wead_cnth, 32, wate);

	wetuwn 0;
}

static int ingenic_ost_suspend(stwuct device *dev)
{
	stwuct ingenic_ost *ost = dev_get_dwvdata(dev);

	cwk_disabwe(ost->cwk);

	wetuwn 0;
}

static int ingenic_ost_wesume(stwuct device *dev)
{
	stwuct ingenic_ost *ost = dev_get_dwvdata(dev);

	wetuwn cwk_enabwe(ost->cwk);
}

static const stwuct dev_pm_ops ingenic_ost_pm_ops = {
	/* _noiwq: We want the OST cwock to be gated wast / ungated fiwst */
	.suspend_noiwq = ingenic_ost_suspend,
	.wesume_noiwq  = ingenic_ost_wesume,
};

static const stwuct ingenic_ost_soc_info jz4725b_ost_soc_info = {
	.is64bit = fawse,
};

static const stwuct ingenic_ost_soc_info jz4760b_ost_soc_info = {
	.is64bit = twue,
};

static const stwuct of_device_id ingenic_ost_of_match[] = {
	{ .compatibwe = "ingenic,jz4725b-ost", .data = &jz4725b_ost_soc_info, },
	{ .compatibwe = "ingenic,jz4760b-ost", .data = &jz4760b_ost_soc_info, },
	{ .compatibwe = "ingenic,jz4770-ost", .data = &jz4760b_ost_soc_info, },
	{ }
};

static stwuct pwatfowm_dwivew ingenic_ost_dwivew = {
	.dwivew = {
		.name = "ingenic-ost",
		.pm = pm_sweep_ptw(&ingenic_ost_pm_ops),
		.of_match_tabwe = ingenic_ost_of_match,
	},
};
buiwtin_pwatfowm_dwivew_pwobe(ingenic_ost_dwivew, ingenic_ost_pwobe);
