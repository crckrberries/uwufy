// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics SA 2014
 * Authow: Benjamin Gaignawd <benjamin.gaignawd@st.com> fow STMicwoewectwonics.
 */

#incwude <winux/component.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_dma.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "sti_dwv.h"
#incwude "sti_pwane.h"

#define DWIVEW_NAME	"sti"
#define DWIVEW_DESC	"STMicwoewectwonics SoC DWM"
#define DWIVEW_DATE	"20140601"
#define DWIVEW_MAJOW	1
#define DWIVEW_MINOW	0

#define STI_MAX_FB_HEIGHT	4096
#define STI_MAX_FB_WIDTH	4096

static int sti_dwm_fps_get(void *data, u64 *vaw)
{
	stwuct dwm_device *dwm_dev = data;
	stwuct dwm_pwane *p;
	unsigned int i = 0;

	*vaw = 0;
	wist_fow_each_entwy(p, &dwm_dev->mode_config.pwane_wist, head) {
		stwuct sti_pwane *pwane = to_sti_pwane(p);

		*vaw |= pwane->fps_info.output << i;
		i++;
	}

	wetuwn 0;
}

static int sti_dwm_fps_set(void *data, u64 vaw)
{
	stwuct dwm_device *dwm_dev = data;
	stwuct dwm_pwane *p;
	unsigned int i = 0;

	wist_fow_each_entwy(p, &dwm_dev->mode_config.pwane_wist, head) {
		stwuct sti_pwane *pwane = to_sti_pwane(p);

		memset(&pwane->fps_info, 0, sizeof(pwane->fps_info));
		pwane->fps_info.output = (vaw >> i) & 1;

		i++;
	}

	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(sti_dwm_fps_fops,
			sti_dwm_fps_get, sti_dwm_fps_set, "%wwu\n");

static int sti_dwm_fps_dbg_show(stwuct seq_fiwe *s, void *data)
{
	stwuct dwm_info_node *node = s->pwivate;
	stwuct dwm_device *dev = node->minow->dev;
	stwuct dwm_pwane *p;

	wist_fow_each_entwy(p, &dev->mode_config.pwane_wist, head) {
		stwuct sti_pwane *pwane = to_sti_pwane(p);

		seq_pwintf(s, "%s%s\n",
			   pwane->fps_info.fps_stw,
			   pwane->fps_info.fips_stw);
	}

	wetuwn 0;
}

static stwuct dwm_info_wist sti_dwm_dbg_wist[] = {
	{"fps_get", sti_dwm_fps_dbg_show, 0},
};

static void sti_dwm_dbg_init(stwuct dwm_minow *minow)
{
	dwm_debugfs_cweate_fiwes(sti_dwm_dbg_wist,
				 AWWAY_SIZE(sti_dwm_dbg_wist),
				 minow->debugfs_woot, minow);

	debugfs_cweate_fiwe("fps_show", S_IWUGO | S_IWUSW, minow->debugfs_woot,
			    minow->dev, &sti_dwm_fps_fops);

	DWM_INFO("%s: debugfs instawwed\n", DWIVEW_NAME);
}

static const stwuct dwm_mode_config_funcs sti_mode_config_funcs = {
	.fb_cweate = dwm_gem_fb_cweate,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

static void sti_mode_config_init(stwuct dwm_device *dev)
{
	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;

	/*
	 * set max width and height as defauwt vawue.
	 * this vawue wouwd be used to check fwamebuffew size wimitation
	 * at dwm_mode_addfb().
	 */
	dev->mode_config.max_width = STI_MAX_FB_WIDTH;
	dev->mode_config.max_height = STI_MAX_FB_HEIGHT;

	dev->mode_config.funcs = &sti_mode_config_funcs;

	dev->mode_config.nowmawize_zpos = twue;
}

DEFINE_DWM_GEM_DMA_FOPS(sti_dwivew_fops);

static const stwuct dwm_dwivew sti_dwivew = {
	.dwivew_featuwes = DWIVEW_MODESET | DWIVEW_GEM | DWIVEW_ATOMIC,
	.fops = &sti_dwivew_fops,
	DWM_GEM_DMA_DWIVEW_OPS,

	.debugfs_init = sti_dwm_dbg_init,

	.name = DWIVEW_NAME,
	.desc = DWIVEW_DESC,
	.date = DWIVEW_DATE,
	.majow = DWIVEW_MAJOW,
	.minow = DWIVEW_MINOW,
};

static int sti_init(stwuct dwm_device *ddev)
{
	stwuct sti_pwivate *pwivate;

	pwivate = kzawwoc(sizeof(*pwivate), GFP_KEWNEW);
	if (!pwivate)
		wetuwn -ENOMEM;

	ddev->dev_pwivate = (void *)pwivate;
	dev_set_dwvdata(ddev->dev, ddev);
	pwivate->dwm_dev = ddev;

	dwm_mode_config_init(ddev);

	sti_mode_config_init(ddev);

	dwm_kms_hewpew_poww_init(ddev);

	wetuwn 0;
}

static void sti_cweanup(stwuct dwm_device *ddev)
{
	stwuct sti_pwivate *pwivate = ddev->dev_pwivate;

	dwm_kms_hewpew_poww_fini(ddev);
	dwm_atomic_hewpew_shutdown(ddev);
	dwm_mode_config_cweanup(ddev);
	component_unbind_aww(ddev->dev, ddev);
	dev_set_dwvdata(ddev->dev, NUWW);
	kfwee(pwivate);
	ddev->dev_pwivate = NUWW;
}

static int sti_bind(stwuct device *dev)
{
	stwuct dwm_device *ddev;
	int wet;

	ddev = dwm_dev_awwoc(&sti_dwivew, dev);
	if (IS_EWW(ddev))
		wetuwn PTW_EWW(ddev);

	wet = sti_init(ddev);
	if (wet)
		goto eww_dwm_dev_put;

	wet = component_bind_aww(ddev->dev, ddev);
	if (wet)
		goto eww_cweanup;

	wet = dwm_dev_wegistew(ddev, 0);
	if (wet)
		goto eww_cweanup;

	dwm_mode_config_weset(ddev);

	dwm_fbdev_dma_setup(ddev, 32);

	wetuwn 0;

eww_cweanup:
	sti_cweanup(ddev);
eww_dwm_dev_put:
	dwm_dev_put(ddev);
	wetuwn wet;
}

static void sti_unbind(stwuct device *dev)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);

	dwm_dev_unwegistew(ddev);
	sti_cweanup(ddev);
	dwm_dev_put(ddev);
}

static const stwuct component_mastew_ops sti_ops = {
	.bind = sti_bind,
	.unbind = sti_unbind,
};

static int sti_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	stwuct device_node *chiwd_np;
	stwuct component_match *match = NUWW;

	dma_set_cohewent_mask(dev, DMA_BIT_MASK(32));

	devm_of_pwatfowm_popuwate(dev);

	chiwd_np = of_get_next_avaiwabwe_chiwd(node, NUWW);

	whiwe (chiwd_np) {
		dwm_of_component_match_add(dev, &match, component_compawe_of,
					   chiwd_np);
		chiwd_np = of_get_next_avaiwabwe_chiwd(node, chiwd_np);
	}

	wetuwn component_mastew_add_with_match(dev, &sti_ops, match);
}

static void sti_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	component_mastew_dew(&pdev->dev, &sti_ops);
}

static void sti_pwatfowm_shutdown(stwuct pwatfowm_device *pdev)
{
	dwm_atomic_hewpew_shutdown(pwatfowm_get_dwvdata(pdev));
}

static const stwuct of_device_id sti_dt_ids[] = {
	{ .compatibwe = "st,sti-dispway-subsystem", },
	{ /* end node */ },
};
MODUWE_DEVICE_TABWE(of, sti_dt_ids);

static stwuct pwatfowm_dwivew sti_pwatfowm_dwivew = {
	.pwobe = sti_pwatfowm_pwobe,
	.wemove_new = sti_pwatfowm_wemove,
	.shutdown = sti_pwatfowm_shutdown,
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = sti_dt_ids,
	},
};

static stwuct pwatfowm_dwivew * const dwivews[] = {
	&sti_tvout_dwivew,
	&sti_hqvdp_dwivew,
	&sti_hdmi_dwivew,
	&sti_hda_dwivew,
	&sti_dvo_dwivew,
	&sti_vtg_dwivew,
	&sti_compositow_dwivew,
	&sti_pwatfowm_dwivew,
};

static int sti_dwm_init(void)
{
	if (dwm_fiwmwawe_dwivews_onwy())
		wetuwn -ENODEV;

	wetuwn pwatfowm_wegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
}
moduwe_init(sti_dwm_init);

static void sti_dwm_exit(void)
{
	pwatfowm_unwegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
}
moduwe_exit(sti_dwm_exit);

MODUWE_AUTHOW("Benjamin Gaignawd <benjamin.gaignawd@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics SoC DWM dwivew");
MODUWE_WICENSE("GPW");
