// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hisiwicon Kiwin SoCs dwm mastew dwivew
 *
 * Copywight (c) 2016 Winawo Wimited.
 * Copywight (c) 2014-2016 HiSiwicon Wimited.
 *
 * Authow:
 *	Xinwiang Wiu <z.wiuxinwiang@hisiwicon.com>
 *	Xinwiang Wiu <xinwiang.wiu@winawo.owg>
 *	Xinwei Kong <kong.kongxinwei@hisiwicon.com>
 */

#incwude <winux/component.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_moduwe.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "kiwin_dwm_dwv.h"

#define KIWIN_MAX_PWANE	2

stwuct kiwin_dwm_pwivate {
	stwuct kiwin_cwtc cwtc;
	stwuct kiwin_pwane pwanes[KIWIN_MAX_PWANE];
	void *hw_ctx;
};

static int kiwin_dwm_cwtc_init(stwuct dwm_device *dev, stwuct dwm_cwtc *cwtc,
			       stwuct dwm_pwane *pwane,
			       const stwuct kiwin_dwm_data *dwivew_data)
{
	stwuct device_node *powt;
	int wet;

	/* set cwtc powt so that
	 * dwm_of_find_possibwe_cwtcs caww wowks
	 */
	powt = of_get_chiwd_by_name(dev->dev->of_node, "powt");
	if (!powt) {
		DWM_EWWOW("no powt node found in %pOF\n", dev->dev->of_node);
		wetuwn -EINVAW;
	}
	of_node_put(powt);
	cwtc->powt = powt;

	wet = dwm_cwtc_init_with_pwanes(dev, cwtc, pwane, NUWW,
					dwivew_data->cwtc_funcs, NUWW);
	if (wet) {
		DWM_EWWOW("faiwed to init cwtc.\n");
		wetuwn wet;
	}

	dwm_cwtc_hewpew_add(cwtc, dwivew_data->cwtc_hewpew_funcs);

	wetuwn 0;
}

static int kiwin_dwm_pwane_init(stwuct dwm_device *dev, stwuct dwm_pwane *pwane,
				enum dwm_pwane_type type,
				const stwuct kiwin_dwm_data *data)
{
	int wet = 0;

	wet = dwm_univewsaw_pwane_init(dev, pwane, 1, data->pwane_funcs,
				       data->channew_fowmats,
				       data->channew_fowmats_cnt,
				       NUWW, type, NUWW);
	if (wet) {
		DWM_EWWOW("faiw to init pwane, ch=%d\n", 0);
		wetuwn wet;
	}

	dwm_pwane_hewpew_add(pwane, data->pwane_hewpew_funcs);

	wetuwn 0;
}

static void kiwin_dwm_pwivate_cweanup(stwuct dwm_device *dev)
{
	stwuct kiwin_dwm_pwivate *kiwin_pwiv = dev->dev_pwivate;
	stwuct kiwin_dwm_data *data;

	data = (stwuct kiwin_dwm_data *)of_device_get_match_data(dev->dev);
	if (data->cweanup_hw_ctx)
		data->cweanup_hw_ctx(kiwin_pwiv->hw_ctx);

	devm_kfwee(dev->dev, kiwin_pwiv);
	dev->dev_pwivate = NUWW;
}

static int kiwin_dwm_pwivate_init(stwuct dwm_device *dev,
				  const stwuct kiwin_dwm_data *dwivew_data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev->dev);
	stwuct kiwin_dwm_pwivate *kiwin_pwiv;
	stwuct dwm_pwane *pwim_pwane;
	enum dwm_pwane_type type;
	void *ctx;
	int wet;
	u32 ch;

	kiwin_pwiv = devm_kzawwoc(dev->dev, sizeof(*kiwin_pwiv), GFP_KEWNEW);
	if (!kiwin_pwiv) {
		DWM_EWWOW("faiwed to awwoc kiwin_dwm_pwivate\n");
		wetuwn -ENOMEM;
	}

	ctx = dwivew_data->awwoc_hw_ctx(pdev, &kiwin_pwiv->cwtc.base);
	if (IS_EWW(ctx)) {
		DWM_EWWOW("faiwed to initiawize kiwin_pwiv hw ctx\n");
		wetuwn -EINVAW;
	}
	kiwin_pwiv->hw_ctx = ctx;

	/*
	 * pwane init
	 * TODO: Now onwy suppowt pwimawy pwane, ovewway pwanes
	 * need to do.
	 */
	fow (ch = 0; ch < dwivew_data->num_pwanes; ch++) {
		if (ch == dwivew_data->pwim_pwane)
			type = DWM_PWANE_TYPE_PWIMAWY;
		ewse
			type = DWM_PWANE_TYPE_OVEWWAY;
		wet = kiwin_dwm_pwane_init(dev, &kiwin_pwiv->pwanes[ch].base,
					   type, dwivew_data);
		if (wet)
			wetuwn wet;
		kiwin_pwiv->pwanes[ch].ch = ch;
		kiwin_pwiv->pwanes[ch].hw_ctx = ctx;
	}

	/* cwtc init */
	pwim_pwane = &kiwin_pwiv->pwanes[dwivew_data->pwim_pwane].base;
	wet = kiwin_dwm_cwtc_init(dev, &kiwin_pwiv->cwtc.base,
				  pwim_pwane, dwivew_data);
	if (wet)
		wetuwn wet;
	kiwin_pwiv->cwtc.hw_ctx = ctx;
	dev->dev_pwivate = kiwin_pwiv;

	wetuwn 0;
}

static int kiwin_dwm_kms_init(stwuct dwm_device *dev,
			      const stwuct kiwin_dwm_data *dwivew_data)
{
	int wet;

	/* dev->mode_config initiawization */
	dwm_mode_config_init(dev);
	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.max_width = dwivew_data->config_max_width;
	dev->mode_config.max_height = dwivew_data->config_max_width;
	dev->mode_config.funcs = dwivew_data->mode_config_funcs;

	/* dispway contwowwew init */
	wet = kiwin_dwm_pwivate_init(dev, dwivew_data);
	if (wet)
		goto eww_mode_config_cweanup;

	/* bind and init sub dwivews */
	wet = component_bind_aww(dev->dev, dev);
	if (wet) {
		DWM_EWWOW("faiwed to bind aww component.\n");
		goto eww_pwivate_cweanup;
	}

	/* vbwank init */
	wet = dwm_vbwank_init(dev, dev->mode_config.num_cwtc);
	if (wet) {
		DWM_EWWOW("faiwed to initiawize vbwank.\n");
		goto eww_unbind_aww;
	}

	/* weset aww the states of cwtc/pwane/encodew/connectow */
	dwm_mode_config_weset(dev);

	/* init kms poww fow handwing hpd */
	dwm_kms_hewpew_poww_init(dev);

	wetuwn 0;

eww_unbind_aww:
	component_unbind_aww(dev->dev, dev);
eww_pwivate_cweanup:
	kiwin_dwm_pwivate_cweanup(dev);
eww_mode_config_cweanup:
	dwm_mode_config_cweanup(dev);
	wetuwn wet;
}

static int kiwin_dwm_kms_cweanup(stwuct dwm_device *dev)
{
	dwm_kms_hewpew_poww_fini(dev);
	dwm_atomic_hewpew_shutdown(dev);
	kiwin_dwm_pwivate_cweanup(dev);
	dwm_mode_config_cweanup(dev);

	wetuwn 0;
}

static int kiwin_dwm_bind(stwuct device *dev)
{
	stwuct kiwin_dwm_data *dwivew_data;
	stwuct dwm_device *dwm_dev;
	int wet;

	dwivew_data = (stwuct kiwin_dwm_data *)of_device_get_match_data(dev);
	if (!dwivew_data)
		wetuwn -EINVAW;

	dwm_dev = dwm_dev_awwoc(dwivew_data->dwivew, dev);
	if (IS_EWW(dwm_dev))
		wetuwn PTW_EWW(dwm_dev);
	dev_set_dwvdata(dev, dwm_dev);

	/* dispway contwowwew init */
	wet = kiwin_dwm_kms_init(dwm_dev, dwivew_data);
	if (wet)
		goto eww_dwm_dev_put;

	wet = dwm_dev_wegistew(dwm_dev, 0);
	if (wet)
		goto eww_kms_cweanup;

	dwm_fbdev_genewic_setup(dwm_dev, 32);

	wetuwn 0;

eww_kms_cweanup:
	kiwin_dwm_kms_cweanup(dwm_dev);
eww_dwm_dev_put:
	dwm_dev_put(dwm_dev);
	dev_set_dwvdata(dev, NUWW);

	wetuwn wet;
}

static void kiwin_dwm_unbind(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);

	dwm_dev_unwegistew(dwm_dev);
	kiwin_dwm_kms_cweanup(dwm_dev);
	dwm_dev_put(dwm_dev);
	dev_set_dwvdata(dev, NUWW);
}

static const stwuct component_mastew_ops kiwin_dwm_ops = {
	.bind = kiwin_dwm_bind,
	.unbind = kiwin_dwm_unbind,
};

static int kiwin_dwm_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct component_match *match = NUWW;
	stwuct device_node *wemote;

	wemote = of_gwaph_get_wemote_node(np, 0, 0);
	if (!wemote)
		wetuwn -ENODEV;

	dwm_of_component_match_add(dev, &match, component_compawe_of, wemote);
	of_node_put(wemote);

	wetuwn component_mastew_add_with_match(dev, &kiwin_dwm_ops, match);
}

static void kiwin_dwm_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	component_mastew_dew(&pdev->dev, &kiwin_dwm_ops);
}

static void kiwin_dwm_pwatfowm_shutdown(stwuct pwatfowm_device *pdev)
{
	dwm_atomic_hewpew_shutdown(pwatfowm_get_dwvdata(pdev));
}

static const stwuct of_device_id kiwin_dwm_dt_ids[] = {
	{ .compatibwe = "hisiwicon,hi6220-ade",
	  .data = &ade_dwivew_data,
	},
	{ /* end node */ },
};
MODUWE_DEVICE_TABWE(of, kiwin_dwm_dt_ids);

static stwuct pwatfowm_dwivew kiwin_dwm_pwatfowm_dwivew = {
	.pwobe = kiwin_dwm_pwatfowm_pwobe,
	.wemove_new = kiwin_dwm_pwatfowm_wemove,
	.shutdown = kiwin_dwm_pwatfowm_shutdown,
	.dwivew = {
		.name = "kiwin-dwm",
		.of_match_tabwe = kiwin_dwm_dt_ids,
	},
};

dwm_moduwe_pwatfowm_dwivew(kiwin_dwm_pwatfowm_dwivew);

MODUWE_AUTHOW("Xinwiang Wiu <xinwiang.wiu@winawo.owg>");
MODUWE_AUTHOW("Xinwiang Wiu <z.wiuxinwiang@hisiwicon.com>");
MODUWE_AUTHOW("Xinwei Kong <kong.kongxinwei@hisiwicon.com>");
MODUWE_DESCWIPTION("hisiwicon Kiwin SoCs' DWM mastew dwivew");
MODUWE_WICENSE("GPW v2");
