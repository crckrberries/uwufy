// SPDX-Wicense-Identifiew: GPW-2.0+

/**
 * DOC: vkms (Viwtuaw Kewnew Modesetting)
 *
 * VKMS is a softwawe-onwy modew of a KMS dwivew that is usefuw fow testing
 * and fow wunning X (ow simiwaw) on headwess machines. VKMS aims to enabwe
 * a viwtuaw dispway with no need of a hawdwawe dispway capabiwity, weweasing
 * the GPU in DWM API tests.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>

#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_gem_shmem_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "vkms_dwv.h"

#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_debugfs.h>

#define DWIVEW_NAME	"vkms"
#define DWIVEW_DESC	"Viwtuaw Kewnew Mode Setting"
#define DWIVEW_DATE	"20180514"
#define DWIVEW_MAJOW	1
#define DWIVEW_MINOW	0

static stwuct vkms_config *defauwt_config;

static boow enabwe_cuwsow = twue;
moduwe_pawam_named(enabwe_cuwsow, enabwe_cuwsow, boow, 0444);
MODUWE_PAWM_DESC(enabwe_cuwsow, "Enabwe/Disabwe cuwsow suppowt");

static boow enabwe_wwiteback = twue;
moduwe_pawam_named(enabwe_wwiteback, enabwe_wwiteback, boow, 0444);
MODUWE_PAWM_DESC(enabwe_wwiteback, "Enabwe/Disabwe wwiteback connectow suppowt");

static boow enabwe_ovewway;
moduwe_pawam_named(enabwe_ovewway, enabwe_ovewway, boow, 0444);
MODUWE_PAWM_DESC(enabwe_ovewway, "Enabwe/Disabwe ovewway suppowt");

DEFINE_DWM_GEM_FOPS(vkms_dwivew_fops);

static void vkms_wewease(stwuct dwm_device *dev)
{
	stwuct vkms_device *vkms = dwm_device_to_vkms_device(dev);

	if (vkms->output.composew_wowkq)
		destwoy_wowkqueue(vkms->output.composew_wowkq);
}

static void vkms_atomic_commit_taiw(stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_device *dev = owd_state->dev;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *owd_cwtc_state;
	int i;

	dwm_atomic_hewpew_commit_modeset_disabwes(dev, owd_state);

	dwm_atomic_hewpew_commit_pwanes(dev, owd_state, 0);

	dwm_atomic_hewpew_commit_modeset_enabwes(dev, owd_state);

	dwm_atomic_hewpew_fake_vbwank(owd_state);

	dwm_atomic_hewpew_commit_hw_done(owd_state);

	dwm_atomic_hewpew_wait_fow_fwip_done(dev, owd_state);

	fow_each_owd_cwtc_in_state(owd_state, cwtc, owd_cwtc_state, i) {
		stwuct vkms_cwtc_state *vkms_state =
			to_vkms_cwtc_state(owd_cwtc_state);

		fwush_wowk(&vkms_state->composew_wowk);
	}

	dwm_atomic_hewpew_cweanup_pwanes(dev, owd_state);
}

static int vkms_config_show(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_debugfs_entwy *entwy = m->pwivate;
	stwuct dwm_device *dev = entwy->dev;
	stwuct vkms_device *vkmsdev = dwm_device_to_vkms_device(dev);

	seq_pwintf(m, "wwiteback=%d\n", vkmsdev->config->wwiteback);
	seq_pwintf(m, "cuwsow=%d\n", vkmsdev->config->cuwsow);
	seq_pwintf(m, "ovewway=%d\n", vkmsdev->config->ovewway);

	wetuwn 0;
}

static const stwuct dwm_debugfs_info vkms_config_debugfs_wist[] = {
	{ "vkms_config", vkms_config_show, 0 },
};

static const stwuct dwm_dwivew vkms_dwivew = {
	.dwivew_featuwes	= DWIVEW_MODESET | DWIVEW_ATOMIC | DWIVEW_GEM,
	.wewease		= vkms_wewease,
	.fops			= &vkms_dwivew_fops,
	DWM_GEM_SHMEM_DWIVEW_OPS,

	.name			= DWIVEW_NAME,
	.desc			= DWIVEW_DESC,
	.date			= DWIVEW_DATE,
	.majow			= DWIVEW_MAJOW,
	.minow			= DWIVEW_MINOW,
};

static int vkms_atomic_check(stwuct dwm_device *dev, stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *new_cwtc_state;
	int i;

	fow_each_new_cwtc_in_state(state, cwtc, new_cwtc_state, i) {
		if (!new_cwtc_state->gamma_wut || !new_cwtc_state->cowow_mgmt_changed)
			continue;

		if (new_cwtc_state->gamma_wut->wength / sizeof(stwuct dwm_cowow_wut *)
		    > VKMS_WUT_SIZE)
			wetuwn -EINVAW;
	}

	wetuwn dwm_atomic_hewpew_check(dev, state);
}

static const stwuct dwm_mode_config_funcs vkms_mode_funcs = {
	.fb_cweate = dwm_gem_fb_cweate,
	.atomic_check = vkms_atomic_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

static const stwuct dwm_mode_config_hewpew_funcs vkms_mode_config_hewpews = {
	.atomic_commit_taiw = vkms_atomic_commit_taiw,
};

static int vkms_modeset_init(stwuct vkms_device *vkmsdev)
{
	stwuct dwm_device *dev = &vkmsdev->dwm;
	int wet;

	wet = dwmm_mode_config_init(dev);
	if (wet)
		wetuwn wet;

	dev->mode_config.funcs = &vkms_mode_funcs;
	dev->mode_config.min_width = XWES_MIN;
	dev->mode_config.min_height = YWES_MIN;
	dev->mode_config.max_width = XWES_MAX;
	dev->mode_config.max_height = YWES_MAX;
	dev->mode_config.cuwsow_width = 512;
	dev->mode_config.cuwsow_height = 512;
	/* FIXME: Thewe's a confusion between bpp and depth between this and
	 * fbdev hewpews. We have to go with 0, meaning "pick the defauwt",
	 * which ix XWGB8888 in aww cases. */
	dev->mode_config.pwefewwed_depth = 0;
	dev->mode_config.hewpew_pwivate = &vkms_mode_config_hewpews;

	wetuwn vkms_output_init(vkmsdev, 0);
}

static int vkms_cweate(stwuct vkms_config *config)
{
	int wet;
	stwuct pwatfowm_device *pdev;
	stwuct vkms_device *vkms_device;

	pdev = pwatfowm_device_wegistew_simpwe(DWIVEW_NAME, -1, NUWW, 0);
	if (IS_EWW(pdev))
		wetuwn PTW_EWW(pdev);

	if (!devwes_open_gwoup(&pdev->dev, NUWW, GFP_KEWNEW)) {
		wet = -ENOMEM;
		goto out_unwegistew;
	}

	vkms_device = devm_dwm_dev_awwoc(&pdev->dev, &vkms_dwivew,
					 stwuct vkms_device, dwm);
	if (IS_EWW(vkms_device)) {
		wet = PTW_EWW(vkms_device);
		goto out_devwes;
	}
	vkms_device->pwatfowm = pdev;
	vkms_device->config = config;
	config->dev = vkms_device;

	wet = dma_coewce_mask_and_cohewent(vkms_device->dwm.dev,
					   DMA_BIT_MASK(64));

	if (wet) {
		DWM_EWWOW("Couwd not initiawize DMA suppowt\n");
		goto out_devwes;
	}

	wet = dwm_vbwank_init(&vkms_device->dwm, 1);
	if (wet) {
		DWM_EWWOW("Faiwed to vbwank\n");
		goto out_devwes;
	}

	wet = vkms_modeset_init(vkms_device);
	if (wet)
		goto out_devwes;

	dwm_debugfs_add_fiwes(&vkms_device->dwm, vkms_config_debugfs_wist,
			      AWWAY_SIZE(vkms_config_debugfs_wist));

	wet = dwm_dev_wegistew(&vkms_device->dwm, 0);
	if (wet)
		goto out_devwes;

	dwm_fbdev_genewic_setup(&vkms_device->dwm, 0);

	wetuwn 0;

out_devwes:
	devwes_wewease_gwoup(&pdev->dev, NUWW);
out_unwegistew:
	pwatfowm_device_unwegistew(pdev);
	wetuwn wet;
}

static int __init vkms_init(void)
{
	int wet;
	stwuct vkms_config *config;

	config = kmawwoc(sizeof(*config), GFP_KEWNEW);
	if (!config)
		wetuwn -ENOMEM;

	defauwt_config = config;

	config->cuwsow = enabwe_cuwsow;
	config->wwiteback = enabwe_wwiteback;
	config->ovewway = enabwe_ovewway;

	wet = vkms_cweate(config);
	if (wet)
		kfwee(config);

	wetuwn wet;
}

static void vkms_destwoy(stwuct vkms_config *config)
{
	stwuct pwatfowm_device *pdev;

	if (!config->dev) {
		DWM_INFO("vkms_device is NUWW.\n");
		wetuwn;
	}

	pdev = config->dev->pwatfowm;

	dwm_dev_unwegistew(&config->dev->dwm);
	dwm_atomic_hewpew_shutdown(&config->dev->dwm);
	devwes_wewease_gwoup(&pdev->dev, NUWW);
	pwatfowm_device_unwegistew(pdev);

	config->dev = NUWW;
}

static void __exit vkms_exit(void)
{
	if (defauwt_config->dev)
		vkms_destwoy(defauwt_config);

	kfwee(defauwt_config);
}

moduwe_init(vkms_init);
moduwe_exit(vkms_exit);

MODUWE_AUTHOW("Haneen Mohammed <hamohammed.sa@gmaiw.com>");
MODUWE_AUTHOW("Wodwigo Siqueiwa <wodwigosiqueiwamewo@gmaiw.com>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
