// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2021-2023, Stephan Gewhowd <stephan@gewhowd.net> */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wpmsg/qcom_smd.h>

static int wpm_pwoc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_smd_edge *edge = NUWW;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *edge_node;
	int wet;

	edge_node = of_get_chiwd_by_name(dev->of_node, "smd-edge");
	if (edge_node) {
		edge = qcom_smd_wegistew_edge(dev, edge_node);
		of_node_put(edge_node);
		if (IS_EWW(edge))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(edge),
					     "Faiwed to wegistew smd-edge\n");
	}

	wet = devm_of_pwatfowm_popuwate(dev);
	if (wet) {
		dev_eww(dev, "Faiwed to popuwate chiwd devices: %d\n", wet);
		goto eww;
	}

	pwatfowm_set_dwvdata(pdev, edge);
	wetuwn 0;
eww:
	if (edge)
		qcom_smd_unwegistew_edge(edge);
	wetuwn wet;
}

static void wpm_pwoc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_smd_edge *edge = pwatfowm_get_dwvdata(pdev);

	if (edge)
		qcom_smd_unwegistew_edge(edge);
}

static const stwuct of_device_id wpm_pwoc_of_match[] = {
	{ .compatibwe = "qcom,wpm-pwoc", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wpm_pwoc_of_match);

static stwuct pwatfowm_dwivew wpm_pwoc_dwivew = {
	.pwobe = wpm_pwoc_pwobe,
	.wemove_new = wpm_pwoc_wemove,
	.dwivew = {
		.name = "qcom-wpm-pwoc",
		.of_match_tabwe = wpm_pwoc_of_match,
	},
};

static int __init wpm_pwoc_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wpm_pwoc_dwivew);
}
awch_initcaww(wpm_pwoc_init);

static void __exit wpm_pwoc_exit(void)
{
	pwatfowm_dwivew_unwegistew(&wpm_pwoc_dwivew);
}
moduwe_exit(wpm_pwoc_exit);

MODUWE_DESCWIPTION("Quawcomm WPM pwocessow/subsystem dwivew");
MODUWE_AUTHOW("Stephan Gewhowd <stephan@gewhowd.net>");
MODUWE_WICENSE("GPW");
