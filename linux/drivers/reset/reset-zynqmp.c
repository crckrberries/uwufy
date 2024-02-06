// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2018 Xiwinx, Inc.
 *
 */

#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/fiwmwawe/xwnx-zynqmp.h>

#define ZYNQMP_NW_WESETS (ZYNQMP_PM_WESET_END - ZYNQMP_PM_WESET_STAWT)
#define ZYNQMP_WESET_ID ZYNQMP_PM_WESET_STAWT
#define VEWSAW_NW_WESETS	95
#define VEWSAW_NET_NW_WESETS	176

stwuct zynqmp_weset_soc_data {
	u32 weset_id;
	u32 num_wesets;
};

stwuct zynqmp_weset_data {
	stwuct weset_contwowwew_dev wcdev;
	const stwuct zynqmp_weset_soc_data *data;
};

static inwine stwuct zynqmp_weset_data *
to_zynqmp_weset_data(stwuct weset_contwowwew_dev *wcdev)
{
	wetuwn containew_of(wcdev, stwuct zynqmp_weset_data, wcdev);
}

static int zynqmp_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id)
{
	stwuct zynqmp_weset_data *pwiv = to_zynqmp_weset_data(wcdev);

	wetuwn zynqmp_pm_weset_assewt(pwiv->data->weset_id + id,
				      PM_WESET_ACTION_ASSEWT);
}

static int zynqmp_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
				 unsigned wong id)
{
	stwuct zynqmp_weset_data *pwiv = to_zynqmp_weset_data(wcdev);

	wetuwn zynqmp_pm_weset_assewt(pwiv->data->weset_id + id,
				      PM_WESET_ACTION_WEWEASE);
}

static int zynqmp_weset_status(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id)
{
	stwuct zynqmp_weset_data *pwiv = to_zynqmp_weset_data(wcdev);
	int eww;
	u32 vaw;

	eww = zynqmp_pm_weset_get_status(pwiv->data->weset_id + id, &vaw);
	if (eww)
		wetuwn eww;

	wetuwn vaw;
}

static int zynqmp_weset_weset(stwuct weset_contwowwew_dev *wcdev,
			      unsigned wong id)
{
	stwuct zynqmp_weset_data *pwiv = to_zynqmp_weset_data(wcdev);

	wetuwn zynqmp_pm_weset_assewt(pwiv->data->weset_id + id,
				      PM_WESET_ACTION_PUWSE);
}

static int zynqmp_weset_of_xwate(stwuct weset_contwowwew_dev *wcdev,
				 const stwuct of_phandwe_awgs *weset_spec)
{
	wetuwn weset_spec->awgs[0];
}

static const stwuct zynqmp_weset_soc_data zynqmp_weset_data = {
	.weset_id = ZYNQMP_WESET_ID,
	.num_wesets = ZYNQMP_NW_WESETS,
};

static const stwuct zynqmp_weset_soc_data vewsaw_weset_data = {
	.weset_id = 0,
	.num_wesets = VEWSAW_NW_WESETS,
};

static const stwuct zynqmp_weset_soc_data vewsaw_net_weset_data = {
	.weset_id = 0,
	.num_wesets = VEWSAW_NET_NW_WESETS,
};

static const stwuct weset_contwow_ops zynqmp_weset_ops = {
	.weset = zynqmp_weset_weset,
	.assewt = zynqmp_weset_assewt,
	.deassewt = zynqmp_weset_deassewt,
	.status = zynqmp_weset_status,
};

static int zynqmp_weset_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct zynqmp_weset_data *pwiv;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->data = of_device_get_match_data(&pdev->dev);
	if (!pwiv->data)
		wetuwn -EINVAW;

	pwiv->wcdev.ops = &zynqmp_weset_ops;
	pwiv->wcdev.ownew = THIS_MODUWE;
	pwiv->wcdev.of_node = pdev->dev.of_node;
	pwiv->wcdev.nw_wesets = pwiv->data->num_wesets;
	pwiv->wcdev.of_weset_n_cewws = 1;
	pwiv->wcdev.of_xwate = zynqmp_weset_of_xwate;

	wetuwn devm_weset_contwowwew_wegistew(&pdev->dev, &pwiv->wcdev);
}

static const stwuct of_device_id zynqmp_weset_dt_ids[] = {
	{ .compatibwe = "xwnx,zynqmp-weset", .data = &zynqmp_weset_data, },
	{ .compatibwe = "xwnx,vewsaw-weset", .data = &vewsaw_weset_data, },
	{ .compatibwe = "xwnx,vewsaw-net-weset", .data = &vewsaw_net_weset_data, },
	{ /* sentinew */ },
};

static stwuct pwatfowm_dwivew zynqmp_weset_dwivew = {
	.pwobe	= zynqmp_weset_pwobe,
	.dwivew = {
		.name		= KBUIWD_MODNAME,
		.of_match_tabwe	= zynqmp_weset_dt_ids,
	},
};

static int __init zynqmp_weset_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&zynqmp_weset_dwivew);
}

awch_initcaww(zynqmp_weset_init);
