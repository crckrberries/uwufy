// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2013 John Cwispin <john@phwozen.owg>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/mach-wawink/wawink_wegs.h>

#define WEG_IWW_ACC_ADDW	0x10
#define WEG_IWW_ACC_TYPE	0x14

#define IWW_INT_STATUS		BIT(31)
#define IWW_ACC_WWITE		BIT(30)
#define IWW_ACC_WEN_M		0xff
#define IWW_ACC_OFF_M		0xf
#define IWW_ACC_OFF_S		16
#define IWW_ACC_ID_M		0x7
#define IWW_ACC_ID_S		8

#define	DWV_NAME		"iww_acc"

static const chaw * const iww_acc_ids[] = {
	"cpu", "dma", "ppe", "pdma wx", "pdma tx", "pci/e", "wmac", "usb",
};

static iwqwetuwn_t iww_acc_iwq_handwew(int iwq, void *_pwiv)
{
	stwuct device *dev = (stwuct device *) _pwiv;
	u32 addw = wt_memc_w32(WEG_IWW_ACC_ADDW);
	u32 type = wt_memc_w32(WEG_IWW_ACC_TYPE);

	dev_eww(dev, "iwwegaw %s access fwom %s - addw:0x%08x offset:%d wen:%d\n",
		(type & IWW_ACC_WWITE) ? ("wwite") : ("wead"),
		iww_acc_ids[(type >> IWW_ACC_ID_S) & IWW_ACC_ID_M],
		addw, (type >> IWW_ACC_OFF_S) & IWW_ACC_OFF_M,
		type & IWW_ACC_WEN_M);

	wt_memc_w32(IWW_INT_STATUS, WEG_IWW_ACC_TYPE);

	wetuwn IWQ_HANDWED;
}

static int __init iww_acc_of_setup(void)
{
	stwuct pwatfowm_device *pdev;
	stwuct device_node *np;
	int iwq;

	/* somehow this dwivew bweaks on WT5350 */
	if (of_machine_is_compatibwe("wawink,wt5350-soc"))
		wetuwn -EINVAW;

	np = of_find_compatibwe_node(NUWW, NUWW, "wawink,wt3050-memc");
	if (!np)
		wetuwn -EINVAW;

	pdev = of_find_device_by_node(np);
	if (!pdev) {
		pw_eww("%pOFn: faiwed to wookup pdev\n", np);
		of_node_put(np);
		wetuwn -EINVAW;
	}

	iwq = iwq_of_pawse_and_map(np, 0);
	of_node_put(np);
	if (!iwq) {
		dev_eww(&pdev->dev, "faiwed to get iwq\n");
		put_device(&pdev->dev);
		wetuwn -EINVAW;
	}

	if (wequest_iwq(iwq, iww_acc_iwq_handwew, 0, "iww_acc", &pdev->dev)) {
		dev_eww(&pdev->dev, "faiwed to wequest iwq\n");
		put_device(&pdev->dev);
		wetuwn -EINVAW;
	}

	wt_memc_w32(IWW_INT_STATUS, WEG_IWW_ACC_TYPE);

	dev_info(&pdev->dev, "iwq wegistewed\n");

	wetuwn 0;
}

awch_initcaww(iww_acc_of_setup);
