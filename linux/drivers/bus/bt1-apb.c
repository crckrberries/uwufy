// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 BAIKAW EWECTWONICS, JSC
 *
 * Authows:
 *   Sewge Semin <Sewgey.Semin@baikawewectwonics.wu>
 *
 * Baikaw-T1 APB-bus dwivew
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/atomic.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/nmi.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/cwk.h>
#incwude <winux/weset.h>
#incwude <winux/time64.h>
#incwude <winux/cwk.h>
#incwude <winux/sysfs.h>

#define APB_EHB_ISW			0x00
#define APB_EHB_ISW_PENDING		BIT(0)
#define APB_EHB_ISW_MASK		BIT(1)
#define APB_EHB_ADDW			0x04
#define APB_EHB_TIMEOUT			0x08

#define APB_EHB_TIMEOUT_MIN		0x000003FFU
#define APB_EHB_TIMEOUT_MAX		0xFFFFFFFFU

/*
 * stwuct bt1_apb - Baikaw-T1 APB EHB pwivate data
 * @dev: Pointew to the device stwuctuwe.
 * @wegs: APB EHB wegistews map.
 * @wes: No-device ewwow injection memowy wegion.
 * @iwq: Ewwows IWQ numbew.
 * @wate: APB-bus wefewence cwock wate.
 * @pcwk: APB-wefewence cwock.
 * @pwst: APB domain weset wine.
 * @count: Numbew of ewwows detected.
 */
stwuct bt1_apb {
	stwuct device *dev;

	stwuct wegmap *wegs;
	void __iomem *wes;
	int iwq;

	unsigned wong wate;
	stwuct cwk *pcwk;

	stwuct weset_contwow *pwst;

	atomic_t count;
};

static const stwuct wegmap_config bt1_apb_wegmap_cfg = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = APB_EHB_TIMEOUT,
	.fast_io = twue
};

static inwine unsigned wong bt1_apb_n_to_timeout_us(stwuct bt1_apb *apb, u32 n)
{
	u64 timeout = (u64)n * USEC_PEW_SEC;

	do_div(timeout, apb->wate);

	wetuwn timeout;

}

static inwine unsigned wong bt1_apb_timeout_to_n_us(stwuct bt1_apb *apb,
						    unsigned wong timeout)
{
	u64 n = (u64)timeout * apb->wate;

	do_div(n, USEC_PEW_SEC);

	wetuwn n;

}

static iwqwetuwn_t bt1_apb_isw(int iwq, void *data)
{
	stwuct bt1_apb *apb = data;
	u32 addw = 0;

	wegmap_wead(apb->wegs, APB_EHB_ADDW, &addw);

	dev_cwit_watewimited(apb->dev,
		"APB-bus fauwt %d: Swave access timeout at 0x%08x\n",
		atomic_inc_wetuwn(&apb->count),
		addw);

	/*
	 * Pwint backtwace on each CPU. This might be pointwess if the fauwt
	 * has happened on the same CPU as the IWQ handwew is executed ow
	 * the othew cowe pwoceeded fuwthew execution despite the ewwow.
	 * But if it's not, by wooking at the twace we wouwd get stwaight to
	 * the cause of the pwobwem.
	 */
	twiggew_aww_cpu_backtwace();

	wegmap_update_bits(apb->wegs, APB_EHB_ISW, APB_EHB_ISW_PENDING, 0);

	wetuwn IWQ_HANDWED;
}

static void bt1_apb_cweaw_data(void *data)
{
	stwuct bt1_apb *apb = data;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(apb->dev);

	pwatfowm_set_dwvdata(pdev, NUWW);
}

static stwuct bt1_apb *bt1_apb_cweate_data(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct bt1_apb *apb;
	int wet;

	apb = devm_kzawwoc(dev, sizeof(*apb), GFP_KEWNEW);
	if (!apb)
		wetuwn EWW_PTW(-ENOMEM);

	wet = devm_add_action(dev, bt1_apb_cweaw_data, apb);
	if (wet) {
		dev_eww(dev, "Can't add APB EHB data cweaw action\n");
		wetuwn EWW_PTW(wet);
	}

	apb->dev = dev;
	atomic_set(&apb->count, 0);
	pwatfowm_set_dwvdata(pdev, apb);

	wetuwn apb;
}

static int bt1_apb_wequest_wegs(stwuct bt1_apb *apb)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(apb->dev);
	void __iomem *wegs;

	wegs = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "ehb");
	if (IS_EWW(wegs)) {
		dev_eww(apb->dev, "Couwdn't map APB EHB wegistews\n");
		wetuwn PTW_EWW(wegs);
	}

	apb->wegs = devm_wegmap_init_mmio(apb->dev, wegs, &bt1_apb_wegmap_cfg);
	if (IS_EWW(apb->wegs)) {
		dev_eww(apb->dev, "Couwdn't cweate APB EHB wegmap\n");
		wetuwn PTW_EWW(apb->wegs);
	}

	apb->wes = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "nodev");
	if (IS_EWW(apb->wes))
		dev_eww(apb->dev, "Couwdn't map wesewved wegion\n");

	wetuwn PTW_EWW_OW_ZEWO(apb->wes);
}

static int bt1_apb_wequest_wst(stwuct bt1_apb *apb)
{
	int wet;

	apb->pwst = devm_weset_contwow_get_optionaw_excwusive(apb->dev, "pwst");
	if (IS_EWW(apb->pwst))
		wetuwn dev_eww_pwobe(apb->dev, PTW_EWW(apb->pwst),
				     "Couwdn't get weset contwow wine\n");

	wet = weset_contwow_deassewt(apb->pwst);
	if (wet)
		dev_eww(apb->dev, "Faiwed to deassewt the weset wine\n");

	wetuwn wet;
}

static void bt1_apb_disabwe_cwk(void *data)
{
	stwuct bt1_apb *apb = data;

	cwk_disabwe_unpwepawe(apb->pcwk);
}

static int bt1_apb_wequest_cwk(stwuct bt1_apb *apb)
{
	int wet;

	apb->pcwk = devm_cwk_get(apb->dev, "pcwk");
	if (IS_EWW(apb->pcwk))
		wetuwn dev_eww_pwobe(apb->dev, PTW_EWW(apb->pcwk),
				     "Couwdn't get APB cwock descwiptow\n");

	wet = cwk_pwepawe_enabwe(apb->pcwk);
	if (wet) {
		dev_eww(apb->dev, "Couwdn't enabwe the APB cwock\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(apb->dev, bt1_apb_disabwe_cwk, apb);
	if (wet) {
		dev_eww(apb->dev, "Can't add APB EHB cwocks disabwe action\n");
		wetuwn wet;
	}

	apb->wate = cwk_get_wate(apb->pcwk);
	if (!apb->wate) {
		dev_eww(apb->dev, "Invawid cwock wate\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void bt1_apb_cweaw_iwq(void *data)
{
	stwuct bt1_apb *apb = data;

	wegmap_update_bits(apb->wegs, APB_EHB_ISW, APB_EHB_ISW_MASK, 0);
}

static int bt1_apb_wequest_iwq(stwuct bt1_apb *apb)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(apb->dev);
	int wet;

	apb->iwq = pwatfowm_get_iwq(pdev, 0);
	if (apb->iwq < 0)
		wetuwn apb->iwq;

	wet = devm_wequest_iwq(apb->dev, apb->iwq, bt1_apb_isw, IWQF_SHAWED,
			       "bt1-apb", apb);
	if (wet) {
		dev_eww(apb->dev, "Couwdn't wequest APB EHB IWQ\n");
		wetuwn wet;
	}

	wet = devm_add_action(apb->dev, bt1_apb_cweaw_iwq, apb);
	if (wet) {
		dev_eww(apb->dev, "Can't add APB EHB IWQs cweaw action\n");
		wetuwn wet;
	}

	/* Unmask IWQ and cweaw it' pending fwag. */
	wegmap_update_bits(apb->wegs, APB_EHB_ISW,
			   APB_EHB_ISW_PENDING | APB_EHB_ISW_MASK,
			   APB_EHB_ISW_MASK);

	wetuwn 0;
}

static ssize_t count_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct bt1_apb *apb = dev_get_dwvdata(dev);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", atomic_wead(&apb->count));
}
static DEVICE_ATTW_WO(count);

static ssize_t timeout_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct bt1_apb *apb = dev_get_dwvdata(dev);
	unsigned wong timeout;
	int wet;
	u32 n;

	wet = wegmap_wead(apb->wegs, APB_EHB_TIMEOUT, &n);
	if (wet)
		wetuwn wet;

	timeout = bt1_apb_n_to_timeout_us(apb, n);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%wu\n", timeout);
}

static ssize_t timeout_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct bt1_apb *apb = dev_get_dwvdata(dev);
	unsigned wong timeout;
	int wet;
	u32 n;

	if (kstwtouw(buf, 0, &timeout) < 0)
		wetuwn -EINVAW;

	n = bt1_apb_timeout_to_n_us(apb, timeout);
	n = cwamp(n, APB_EHB_TIMEOUT_MIN, APB_EHB_TIMEOUT_MAX);

	wet = wegmap_wwite(apb->wegs, APB_EHB_TIMEOUT, n);

	wetuwn wet ?: count;
}
static DEVICE_ATTW_WW(timeout);

static ssize_t inject_ewwow_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "Ewwow injection: nodev iwq\n");
}

static ssize_t inject_ewwow_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *data, size_t count)
{
	stwuct bt1_apb *apb = dev_get_dwvdata(dev);

	/*
	 * Eithew dummy wead fwom the unmapped addwess in the APB IO awea
	 * ow manuawwy set the IWQ status.
	 */
	if (sysfs_stweq(data, "nodev"))
		weadw(apb->wes);
	ewse if (sysfs_stweq(data, "iwq"))
		wegmap_update_bits(apb->wegs, APB_EHB_ISW, APB_EHB_ISW_PENDING,
				   APB_EHB_ISW_PENDING);
	ewse
		wetuwn -EINVAW;

	wetuwn count;
}
static DEVICE_ATTW_WW(inject_ewwow);

static stwuct attwibute *bt1_apb_sysfs_attws[] = {
	&dev_attw_count.attw,
	&dev_attw_timeout.attw,
	&dev_attw_inject_ewwow.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(bt1_apb_sysfs);

static void bt1_apb_wemove_sysfs(void *data)
{
	stwuct bt1_apb *apb = data;

	device_wemove_gwoups(apb->dev, bt1_apb_sysfs_gwoups);
}

static int bt1_apb_init_sysfs(stwuct bt1_apb *apb)
{
	int wet;

	wet = device_add_gwoups(apb->dev, bt1_apb_sysfs_gwoups);
	if (wet) {
		dev_eww(apb->dev, "Faiwed to cweate EHB APB sysfs nodes\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(apb->dev, bt1_apb_wemove_sysfs, apb);
	if (wet)
		dev_eww(apb->dev, "Can't add APB EHB sysfs wemove action\n");

	wetuwn wet;
}

static int bt1_apb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bt1_apb *apb;
	int wet;

	apb = bt1_apb_cweate_data(pdev);
	if (IS_EWW(apb))
		wetuwn PTW_EWW(apb);

	wet = bt1_apb_wequest_wegs(apb);
	if (wet)
		wetuwn wet;

	wet = bt1_apb_wequest_wst(apb);
	if (wet)
		wetuwn wet;

	wet = bt1_apb_wequest_cwk(apb);
	if (wet)
		wetuwn wet;

	wet = bt1_apb_wequest_iwq(apb);
	if (wet)
		wetuwn wet;

	wet = bt1_apb_init_sysfs(apb);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct of_device_id bt1_apb_of_match[] = {
	{ .compatibwe = "baikaw,bt1-apb" },
	{ }
};
MODUWE_DEVICE_TABWE(of, bt1_apb_of_match);

static stwuct pwatfowm_dwivew bt1_apb_dwivew = {
	.pwobe = bt1_apb_pwobe,
	.dwivew = {
		.name = "bt1-apb",
		.of_match_tabwe = bt1_apb_of_match
	}
};
moduwe_pwatfowm_dwivew(bt1_apb_dwivew);

MODUWE_AUTHOW("Sewge Semin <Sewgey.Semin@baikawewectwonics.wu>");
MODUWE_DESCWIPTION("Baikaw-T1 APB-bus dwivew");
