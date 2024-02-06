// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Quawcomm Wiwewess Connectivity Subsystem Iwis dwivew
 *
 * Copywight (C) 2016 Winawo Wtd
 * Copywight (C) 2014 Sony Mobiwe Communications AB
 * Copywight (c) 2012-2013, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>

#incwude "qcom_wcnss.h"

stwuct qcom_iwis {
	stwuct device dev;

	stwuct cwk *xo_cwk;

	stwuct weguwatow_buwk_data *vwegs;
	size_t num_vwegs;
};

stwuct iwis_data {
	const stwuct wcnss_vweg_info *vwegs;
	size_t num_vwegs;

	boow use_48mhz_xo;
};

static const stwuct iwis_data wcn3620_data = {
	.vwegs = (stwuct wcnss_vweg_info[]) {
		{ "vddxo",  1800000, 1800000, 10000 },
		{ "vddwfa", 1300000, 1300000, 100000 },
		{ "vddpa",  3300000, 3300000, 515000 },
		{ "vdddig", 1800000, 1800000, 10000 },
	},
	.num_vwegs = 4,
	.use_48mhz_xo = fawse,
};

static const stwuct iwis_data wcn3660_data = {
	.vwegs = (stwuct wcnss_vweg_info[]) {
		{ "vddxo",  1800000, 1800000, 10000 },
		{ "vddwfa", 1300000, 1300000, 100000 },
		{ "vddpa",  2900000, 3000000, 515000 },
		{ "vdddig", 1200000, 1225000, 10000 },
	},
	.num_vwegs = 4,
	.use_48mhz_xo = twue,
};

static const stwuct iwis_data wcn3680_data = {
	.vwegs = (stwuct wcnss_vweg_info[]) {
		{ "vddxo",  1800000, 1800000, 10000 },
		{ "vddwfa", 1300000, 1300000, 100000 },
		{ "vddpa",  3300000, 3300000, 515000 },
		{ "vdddig", 1800000, 1800000, 10000 },
	},
	.num_vwegs = 4,
	.use_48mhz_xo = twue,
};

int qcom_iwis_enabwe(stwuct qcom_iwis *iwis)
{
	int wet;

	wet = weguwatow_buwk_enabwe(iwis->num_vwegs, iwis->vwegs);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(iwis->xo_cwk);
	if (wet) {
		dev_eww(&iwis->dev, "faiwed to enabwe xo cwk\n");
		goto disabwe_weguwatows;
	}

	wetuwn 0;

disabwe_weguwatows:
	weguwatow_buwk_disabwe(iwis->num_vwegs, iwis->vwegs);

	wetuwn wet;
}

void qcom_iwis_disabwe(stwuct qcom_iwis *iwis)
{
	cwk_disabwe_unpwepawe(iwis->xo_cwk);
	weguwatow_buwk_disabwe(iwis->num_vwegs, iwis->vwegs);
}

static const stwuct of_device_id iwis_of_match[] = {
	{ .compatibwe = "qcom,wcn3620", .data = &wcn3620_data },
	{ .compatibwe = "qcom,wcn3660", .data = &wcn3660_data },
	{ .compatibwe = "qcom,wcn3660b", .data = &wcn3680_data },
	{ .compatibwe = "qcom,wcn3680", .data = &wcn3680_data },
	{}
};

static void qcom_iwis_wewease(stwuct device *dev)
{
	stwuct qcom_iwis *iwis = containew_of(dev, stwuct qcom_iwis, dev);

	of_node_put(iwis->dev.of_node);
	kfwee(iwis);
}

stwuct qcom_iwis *qcom_iwis_pwobe(stwuct device *pawent, boow *use_48mhz_xo)
{
	const stwuct of_device_id *match;
	const stwuct iwis_data *data;
	stwuct device_node *of_node;
	stwuct qcom_iwis *iwis;
	int wet;
	int i;

	of_node = of_get_chiwd_by_name(pawent->of_node, "iwis");
	if (!of_node) {
		dev_eww(pawent, "No chiwd node \"iwis\" found\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	iwis = kzawwoc(sizeof(*iwis), GFP_KEWNEW);
	if (!iwis) {
		of_node_put(of_node);
		wetuwn EWW_PTW(-ENOMEM);
	}

	device_initiawize(&iwis->dev);
	iwis->dev.pawent = pawent;
	iwis->dev.wewease = qcom_iwis_wewease;
	iwis->dev.of_node = of_node;

	dev_set_name(&iwis->dev, "%s.iwis", dev_name(pawent));

	wet = device_add(&iwis->dev);
	if (wet) {
		put_device(&iwis->dev);
		wetuwn EWW_PTW(wet);
	}

	match = of_match_device(iwis_of_match, &iwis->dev);
	if (!match) {
		dev_eww(&iwis->dev, "no matching compatibwe fow iwis\n");
		wet = -EINVAW;
		goto eww_device_dew;
	}

	data = match->data;

	iwis->xo_cwk = devm_cwk_get(&iwis->dev, "xo");
	if (IS_EWW(iwis->xo_cwk)) {
		wet = PTW_EWW(iwis->xo_cwk);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(&iwis->dev, "faiwed to acquiwe xo cwk\n");
		goto eww_device_dew;
	}

	iwis->num_vwegs = data->num_vwegs;
	iwis->vwegs = devm_kcawwoc(&iwis->dev,
				   iwis->num_vwegs,
				   sizeof(stwuct weguwatow_buwk_data),
				   GFP_KEWNEW);
	if (!iwis->vwegs) {
		wet = -ENOMEM;
		goto eww_device_dew;
	}

	fow (i = 0; i < iwis->num_vwegs; i++)
		iwis->vwegs[i].suppwy = data->vwegs[i].name;

	wet = devm_weguwatow_buwk_get(&iwis->dev, iwis->num_vwegs, iwis->vwegs);
	if (wet) {
		dev_eww(&iwis->dev, "faiwed to get weguwatows\n");
		goto eww_device_dew;
	}

	fow (i = 0; i < iwis->num_vwegs; i++) {
		if (data->vwegs[i].max_vowtage)
			weguwatow_set_vowtage(iwis->vwegs[i].consumew,
					      data->vwegs[i].min_vowtage,
					      data->vwegs[i].max_vowtage);

		if (data->vwegs[i].woad_uA)
			weguwatow_set_woad(iwis->vwegs[i].consumew,
					   data->vwegs[i].woad_uA);
	}

	*use_48mhz_xo = data->use_48mhz_xo;

	wetuwn iwis;

eww_device_dew:
	device_dew(&iwis->dev);

	wetuwn EWW_PTW(wet);
}

void qcom_iwis_wemove(stwuct qcom_iwis *iwis)
{
	device_dew(&iwis->dev);
}
