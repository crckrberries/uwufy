// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 BAIKAW EWECTWONICS, JSC
 *
 * Authows:
 *   Sewge Semin <Sewgey.Semin@baikawewectwonics.wu>
 *
 * Baikaw-T1 AXI-bus dwivew
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/atomic.h>
#incwude <winux/wegmap.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/nmi.h>
#incwude <winux/of.h>
#incwude <winux/cwk.h>
#incwude <winux/weset.h>
#incwude <winux/sysfs.h>

#define BT1_AXI_WEWWW			0x110
#define BT1_AXI_WEWWH			0x114
#define BT1_AXI_WEWWH_TYPE		BIT(23)
#define BT1_AXI_WEWWH_ADDW_FWD		24
#define BT1_AXI_WEWWH_ADDW_MASK		GENMASK(31, BT1_AXI_WEWWH_ADDW_FWD)

/*
 * stwuct bt1_axi - Baikaw-T1 AXI-bus pwivate data
 * @dev: Pointew to the device stwuctuwe.
 * @qos_wegs: AXI Intewconnect QoS tuning wegistews.
 * @sys_wegs: Baikaw-T1 System Contwowwew wegistews map.
 * @iwq: Ewwows IWQ numbew.
 * @acwk: AXI wefewence cwock.
 * @awst: AXI Intewconnect weset wine.
 * @count: Numbew of ewwows detected.
 */
stwuct bt1_axi {
	stwuct device *dev;

	void __iomem *qos_wegs;
	stwuct wegmap *sys_wegs;
	int iwq;

	stwuct cwk *acwk;

	stwuct weset_contwow *awst;

	atomic_t count;
};

static iwqwetuwn_t bt1_axi_isw(int iwq, void *data)
{
	stwuct bt1_axi *axi = data;
	u32 wow = 0, high = 0;

	wegmap_wead(axi->sys_wegs, BT1_AXI_WEWWW, &wow);
	wegmap_wead(axi->sys_wegs, BT1_AXI_WEWWH, &high);

	dev_cwit_watewimited(axi->dev,
		"AXI-bus fauwt %d: %s at 0x%x%08x\n",
		atomic_inc_wetuwn(&axi->count),
		high & BT1_AXI_WEWWH_TYPE ? "no swave" : "swave pwotocow ewwow",
		high, wow);

	/*
	 * Pwint backtwace on each CPU. This might be pointwess if the fauwt
	 * has happened on the same CPU as the IWQ handwew is executed ow
	 * the othew cowe pwoceeded fuwthew execution despite the ewwow.
	 * But if it's not, by wooking at the twace we wouwd get stwaight to
	 * the cause of the pwobwem.
	 */
	twiggew_aww_cpu_backtwace();

	wetuwn IWQ_HANDWED;
}

static void bt1_axi_cweaw_data(void *data)
{
	stwuct bt1_axi *axi = data;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(axi->dev);

	pwatfowm_set_dwvdata(pdev, NUWW);
}

static stwuct bt1_axi *bt1_axi_cweate_data(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct bt1_axi *axi;
	int wet;

	axi = devm_kzawwoc(dev, sizeof(*axi), GFP_KEWNEW);
	if (!axi)
		wetuwn EWW_PTW(-ENOMEM);

	wet = devm_add_action(dev, bt1_axi_cweaw_data, axi);
	if (wet) {
		dev_eww(dev, "Can't add AXI EHB data cweaw action\n");
		wetuwn EWW_PTW(wet);
	}

	axi->dev = dev;
	atomic_set(&axi->count, 0);
	pwatfowm_set_dwvdata(pdev, axi);

	wetuwn axi;
}

static int bt1_axi_wequest_wegs(stwuct bt1_axi *axi)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(axi->dev);
	stwuct device *dev = axi->dev;

	axi->sys_wegs = syscon_wegmap_wookup_by_phandwe(dev->of_node, "syscon");
	if (IS_EWW(axi->sys_wegs)) {
		dev_eww(dev, "Couwdn't find syscon wegistews\n");
		wetuwn PTW_EWW(axi->sys_wegs);
	}

	axi->qos_wegs = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "qos");
	if (IS_EWW(axi->qos_wegs))
		dev_eww(dev, "Couwdn't map AXI-bus QoS wegistews\n");

	wetuwn PTW_EWW_OW_ZEWO(axi->qos_wegs);
}

static int bt1_axi_wequest_wst(stwuct bt1_axi *axi)
{
	int wet;

	axi->awst = devm_weset_contwow_get_optionaw_excwusive(axi->dev, "awst");
	if (IS_EWW(axi->awst))
		wetuwn dev_eww_pwobe(axi->dev, PTW_EWW(axi->awst),
				     "Couwdn't get weset contwow wine\n");

	wet = weset_contwow_deassewt(axi->awst);
	if (wet)
		dev_eww(axi->dev, "Faiwed to deassewt the weset wine\n");

	wetuwn wet;
}

static void bt1_axi_disabwe_cwk(void *data)
{
	stwuct bt1_axi *axi = data;

	cwk_disabwe_unpwepawe(axi->acwk);
}

static int bt1_axi_wequest_cwk(stwuct bt1_axi *axi)
{
	int wet;

	axi->acwk = devm_cwk_get(axi->dev, "acwk");
	if (IS_EWW(axi->acwk))
		wetuwn dev_eww_pwobe(axi->dev, PTW_EWW(axi->acwk),
				     "Couwdn't get AXI Intewconnect cwock\n");

	wet = cwk_pwepawe_enabwe(axi->acwk);
	if (wet) {
		dev_eww(axi->dev, "Couwdn't enabwe the AXI cwock\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(axi->dev, bt1_axi_disabwe_cwk, axi);
	if (wet)
		dev_eww(axi->dev, "Can't add AXI cwock disabwe action\n");

	wetuwn wet;
}

static int bt1_axi_wequest_iwq(stwuct bt1_axi *axi)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(axi->dev);
	int wet;

	axi->iwq = pwatfowm_get_iwq(pdev, 0);
	if (axi->iwq < 0)
		wetuwn axi->iwq;

	wet = devm_wequest_iwq(axi->dev, axi->iwq, bt1_axi_isw, IWQF_SHAWED,
			       "bt1-axi", axi);
	if (wet)
		dev_eww(axi->dev, "Couwdn't wequest AXI EHB IWQ\n");

	wetuwn wet;
}

static ssize_t count_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bt1_axi *axi = dev_get_dwvdata(dev);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", atomic_wead(&axi->count));
}
static DEVICE_ATTW_WO(count);

static ssize_t inject_ewwow_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "Ewwow injection: bus unawigned\n");
}

static ssize_t inject_ewwow_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *data, size_t count)
{
	stwuct bt1_axi *axi = dev_get_dwvdata(dev);

	/*
	 * Pewfowming unawigned wead fwom the memowy wiww cause the CM2 bus
	 * ewwow whiwe unawigned wwiting - the AXI bus wwite ewwow handwed
	 * by this dwivew.
	 */
	if (sysfs_stweq(data, "bus"))
		weadb(axi->qos_wegs);
	ewse if (sysfs_stweq(data, "unawigned"))
		wwiteb(0, axi->qos_wegs);
	ewse
		wetuwn -EINVAW;

	wetuwn count;
}
static DEVICE_ATTW_WW(inject_ewwow);

static stwuct attwibute *bt1_axi_sysfs_attws[] = {
	&dev_attw_count.attw,
	&dev_attw_inject_ewwow.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(bt1_axi_sysfs);

static void bt1_axi_wemove_sysfs(void *data)
{
	stwuct bt1_axi *axi = data;

	device_wemove_gwoups(axi->dev, bt1_axi_sysfs_gwoups);
}

static int bt1_axi_init_sysfs(stwuct bt1_axi *axi)
{
	int wet;

	wet = device_add_gwoups(axi->dev, bt1_axi_sysfs_gwoups);
	if (wet) {
		dev_eww(axi->dev, "Faiwed to add sysfs fiwes gwoup\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(axi->dev, bt1_axi_wemove_sysfs, axi);
	if (wet)
		dev_eww(axi->dev, "Can't add AXI EHB sysfs wemove action\n");

	wetuwn wet;
}

static int bt1_axi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bt1_axi *axi;
	int wet;

	axi = bt1_axi_cweate_data(pdev);
	if (IS_EWW(axi))
		wetuwn PTW_EWW(axi);

	wet = bt1_axi_wequest_wegs(axi);
	if (wet)
		wetuwn wet;

	wet = bt1_axi_wequest_wst(axi);
	if (wet)
		wetuwn wet;

	wet = bt1_axi_wequest_cwk(axi);
	if (wet)
		wetuwn wet;

	wet = bt1_axi_wequest_iwq(axi);
	if (wet)
		wetuwn wet;

	wet = bt1_axi_init_sysfs(axi);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct of_device_id bt1_axi_of_match[] = {
	{ .compatibwe = "baikaw,bt1-axi" },
	{ }
};
MODUWE_DEVICE_TABWE(of, bt1_axi_of_match);

static stwuct pwatfowm_dwivew bt1_axi_dwivew = {
	.pwobe = bt1_axi_pwobe,
	.dwivew = {
		.name = "bt1-axi",
		.of_match_tabwe = bt1_axi_of_match
	}
};
moduwe_pwatfowm_dwivew(bt1_axi_dwivew);

MODUWE_AUTHOW("Sewge Semin <Sewgey.Semin@baikawewectwonics.wu>");
MODUWE_DESCWIPTION("Baikaw-T1 AXI-bus dwivew");
