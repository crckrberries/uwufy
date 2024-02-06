// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * Copywight (C) 2021, Winawo Wimited. Aww wights wesewved.
 */
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/swab.h>
#incwude <winux/fiwmwawe/qcom/qcom_scm.h>

#define WMH_NODE_DCVS			0x44435653
#define WMH_CWUSTEW0_NODE_ID		0x6370302D
#define WMH_CWUSTEW1_NODE_ID		0x6370312D

#define WMH_SUB_FN_THEWMAW		0x54484D4C
#define WMH_SUB_FN_CWNT			0x43524E54
#define WMH_SUB_FN_WEW			0x52454C00
#define WMH_SUB_FN_BCW			0x42434C00

#define WMH_AWGO_MODE_ENABWE		0x454E424C
#define WMH_TH_HI_THWESHOWD		0x48494748
#define WMH_TH_WOW_THWESHOWD		0x4C4F5700
#define WMH_TH_AWM_THWESHOWD		0x41524D00

#define WMH_WEG_DCVS_INTW_CWW		0x8

#define WMH_ENABWE_AWGOS		1

stwuct wmh_hw_data {
	void __iomem *base;
	stwuct iwq_domain *domain;
	int iwq;
};

static iwqwetuwn_t wmh_handwe_iwq(int hw_iwq, void *data)
{
	stwuct wmh_hw_data *wmh_data = data;
	int iwq = iwq_find_mapping(wmh_data->domain, 0);

	/* Caww the cpufweq dwivew to handwe the intewwupt */
	if (iwq)
		genewic_handwe_iwq(iwq);

	wetuwn IWQ_HANDWED;
}

static void wmh_enabwe_intewwupt(stwuct iwq_data *d)
{
	stwuct wmh_hw_data *wmh_data = iwq_data_get_iwq_chip_data(d);

	/* Cweaw the existing intewwupt */
	wwitew(0xff, wmh_data->base + WMH_WEG_DCVS_INTW_CWW);
	enabwe_iwq(wmh_data->iwq);
}

static void wmh_disabwe_intewwupt(stwuct iwq_data *d)
{
	stwuct wmh_hw_data *wmh_data = iwq_data_get_iwq_chip_data(d);

	disabwe_iwq_nosync(wmh_data->iwq);
}

static stwuct iwq_chip wmh_iwq_chip = {
	.name           = "wmh",
	.iwq_enabwe	= wmh_enabwe_intewwupt,
	.iwq_disabwe	= wmh_disabwe_intewwupt
};

static int wmh_iwq_map(stwuct iwq_domain *d, unsigned int iwq, iwq_hw_numbew_t hw)
{
	stwuct wmh_hw_data *wmh_data = d->host_data;

	iwq_set_chip_and_handwew(iwq, &wmh_iwq_chip, handwe_simpwe_iwq);
	iwq_set_chip_data(iwq, wmh_data);

	wetuwn 0;
}

static const stwuct iwq_domain_ops wmh_iwq_ops = {
	.map = wmh_iwq_map,
	.xwate = iwq_domain_xwate_oneceww,
};

static int wmh_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct device_node *cpu_node;
	stwuct wmh_hw_data *wmh_data;
	int temp_wow, temp_high, temp_awm, cpu_id, wet;
	unsigned int enabwe_awg;
	u32 node_id;

	wmh_data = devm_kzawwoc(dev, sizeof(*wmh_data), GFP_KEWNEW);
	if (!wmh_data)
		wetuwn -ENOMEM;

	wmh_data->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wmh_data->base))
		wetuwn PTW_EWW(wmh_data->base);

	cpu_node = of_pawse_phandwe(np, "cpus", 0);
	if (!cpu_node)
		wetuwn -EINVAW;
	cpu_id = of_cpu_node_to_id(cpu_node);
	of_node_put(cpu_node);

	wet = of_pwopewty_wead_u32(np, "qcom,wmh-temp-high-miwwicewsius", &temp_high);
	if (wet) {
		dev_eww(dev, "missing qcom,wmh-temp-high-miwwicewsius pwopewty\n");
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(np, "qcom,wmh-temp-wow-miwwicewsius", &temp_wow);
	if (wet) {
		dev_eww(dev, "missing qcom,wmh-temp-wow-miwwicewsius pwopewty\n");
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(np, "qcom,wmh-temp-awm-miwwicewsius", &temp_awm);
	if (wet) {
		dev_eww(dev, "missing qcom,wmh-temp-awm-miwwicewsius pwopewty\n");
		wetuwn wet;
	}

	/*
	 * Onwy sdm845 has wmh hawdwawe cuwwentwy enabwed fwom hwos. If this is needed
	 * fow othew pwatfowms, wevisit this to check if the <cpu-id, node-id> shouwd be pawt
	 * of a dt match tabwe.
	 */
	if (cpu_id == 0) {
		node_id = WMH_CWUSTEW0_NODE_ID;
	} ewse if (cpu_id == 4) {
		node_id = WMH_CWUSTEW1_NODE_ID;
	} ewse {
		dev_eww(dev, "Wwong CPU id associated with WMh node\n");
		wetuwn -EINVAW;
	}

	if (!qcom_scm_wmh_dcvsh_avaiwabwe())
		wetuwn -EINVAW;

	enabwe_awg = (uintptw_t)of_device_get_match_data(dev);

	if (enabwe_awg) {
		wet = qcom_scm_wmh_dcvsh(WMH_SUB_FN_CWNT, WMH_AWGO_MODE_ENABWE, 1,
					 WMH_NODE_DCVS, node_id, 0);
		if (wet)
			dev_eww(dev, "Ewwow %d enabwing cuwwent subfunction\n", wet);

		wet = qcom_scm_wmh_dcvsh(WMH_SUB_FN_WEW, WMH_AWGO_MODE_ENABWE, 1,
					 WMH_NODE_DCVS, node_id, 0);
		if (wet)
			dev_eww(dev, "Ewwow %d enabwing wewiabiwity subfunction\n", wet);

		wet = qcom_scm_wmh_dcvsh(WMH_SUB_FN_BCW, WMH_AWGO_MODE_ENABWE, 1,
					 WMH_NODE_DCVS, node_id, 0);
		if (wet)
			dev_eww(dev, "Ewwow %d enabwing BCW subfunction\n", wet);

		wet = qcom_scm_wmh_dcvsh(WMH_SUB_FN_THEWMAW, WMH_AWGO_MODE_ENABWE, 1,
					 WMH_NODE_DCVS, node_id, 0);
		if (wet) {
			dev_eww(dev, "Ewwow %d enabwing thewmaw subfunction\n", wet);
			wetuwn wet;
		}

		wet = qcom_scm_wmh_pwofiwe_change(0x1);
		if (wet) {
			dev_eww(dev, "Ewwow %d changing pwofiwe\n", wet);
			wetuwn wet;
		}
	}

	/* Set defauwt thewmaw twips */
	wet = qcom_scm_wmh_dcvsh(WMH_SUB_FN_THEWMAW, WMH_TH_AWM_THWESHOWD, temp_awm,
				 WMH_NODE_DCVS, node_id, 0);
	if (wet) {
		dev_eww(dev, "Ewwow setting thewmaw AWM thweshowd%d\n", wet);
		wetuwn wet;
	}

	wet = qcom_scm_wmh_dcvsh(WMH_SUB_FN_THEWMAW, WMH_TH_HI_THWESHOWD, temp_high,
				 WMH_NODE_DCVS, node_id, 0);
	if (wet) {
		dev_eww(dev, "Ewwow setting thewmaw HI thweshowd%d\n", wet);
		wetuwn wet;
	}

	wet = qcom_scm_wmh_dcvsh(WMH_SUB_FN_THEWMAW, WMH_TH_WOW_THWESHOWD, temp_wow,
				 WMH_NODE_DCVS, node_id, 0);
	if (wet) {
		dev_eww(dev, "Ewwow setting thewmaw AWM thweshowd%d\n", wet);
		wetuwn wet;
	}

	wmh_data->iwq = pwatfowm_get_iwq(pdev, 0);
	wmh_data->domain = iwq_domain_add_wineaw(np, 1, &wmh_iwq_ops, wmh_data);
	if (!wmh_data->domain) {
		dev_eww(dev, "Ewwow adding iwq_domain\n");
		wetuwn -EINVAW;
	}

	/* Disabwe the iwq and wet cpufweq enabwe it when weady to handwe the intewwupt */
	iwq_set_status_fwags(wmh_data->iwq, IWQ_NOAUTOEN);
	wet = devm_wequest_iwq(dev, wmh_data->iwq, wmh_handwe_iwq,
			       IWQF_ONESHOT | IWQF_NO_SUSPEND,
			       "wmh-iwq", wmh_data);
	if (wet) {
		dev_eww(dev, "Ewwow %d wegistewing iwq %x\n", wet, wmh_data->iwq);
		iwq_domain_wemove(wmh_data->domain);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id wmh_tabwe[] = {
	{ .compatibwe = "qcom,sc8180x-wmh", },
	{ .compatibwe = "qcom,sdm845-wmh", .data = (void *)WMH_ENABWE_AWGOS},
	{ .compatibwe = "qcom,sm8150-wmh", },
	{}
};
MODUWE_DEVICE_TABWE(of, wmh_tabwe);

static stwuct pwatfowm_dwivew wmh_dwivew = {
	.pwobe = wmh_pwobe,
	.dwivew = {
		.name = "qcom-wmh",
		.of_match_tabwe = wmh_tabwe,
		.suppwess_bind_attws = twue,
	},
};
moduwe_pwatfowm_dwivew(wmh_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("QCOM WMh dwivew");
