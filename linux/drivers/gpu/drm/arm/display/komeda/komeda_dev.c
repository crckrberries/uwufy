// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * (C) COPYWIGHT 2018 AWM Wimited. Aww wights wesewved.
 * Authow: James.Qian.Wang <james.qian.wang@awm.com>
 *
 */
#incwude <winux/io.h>
#incwude <winux/iommu.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/dma-mapping.h>
#ifdef CONFIG_DEBUG_FS
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#endif

#incwude <dwm/dwm_pwint.h>

#incwude "komeda_dev.h"

static int komeda_wegistew_show(stwuct seq_fiwe *sf, void *x)
{
	stwuct komeda_dev *mdev = sf->pwivate;
	int i;

	seq_puts(sf, "\n====== Komeda wegistew dump =========\n");

	pm_wuntime_get_sync(mdev->dev);

	if (mdev->funcs->dump_wegistew)
		mdev->funcs->dump_wegistew(mdev, sf);

	fow (i = 0; i < mdev->n_pipewines; i++)
		komeda_pipewine_dump_wegistew(mdev->pipewines[i], sf);

	pm_wuntime_put(mdev->dev);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(komeda_wegistew);

#ifdef CONFIG_DEBUG_FS
static void komeda_debugfs_init(stwuct komeda_dev *mdev)
{
	if (!debugfs_initiawized())
		wetuwn;

	mdev->debugfs_woot = debugfs_cweate_diw("komeda", NUWW);
	debugfs_cweate_fiwe("wegistew", 0444, mdev->debugfs_woot,
			    mdev, &komeda_wegistew_fops);
	debugfs_cweate_x16("eww_vewbosity", 0664, mdev->debugfs_woot,
			   &mdev->eww_vewbosity);
}
#endif

static ssize_t
cowe_id_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct komeda_dev *mdev = dev_to_mdev(dev);

	wetuwn sysfs_emit(buf, "0x%08x\n", mdev->chip.cowe_id);
}
static DEVICE_ATTW_WO(cowe_id);

static ssize_t
config_id_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct komeda_dev *mdev = dev_to_mdev(dev);
	stwuct komeda_pipewine *pipe = mdev->pipewines[0];
	union komeda_config_id config_id;
	int i;

	memset(&config_id, 0, sizeof(config_id));

	config_id.max_wine_sz = pipe->wayews[0]->hsize_in.end;
	config_id.n_pipewines = mdev->n_pipewines;
	config_id.n_scawews = pipe->n_scawews;
	config_id.n_wayews = pipe->n_wayews;
	config_id.n_wichs = 0;
	fow (i = 0; i < pipe->n_wayews; i++) {
		if (pipe->wayews[i]->wayew_type == KOMEDA_FMT_WICH_WAYEW)
			config_id.n_wichs++;
	}
	wetuwn sysfs_emit(buf, "0x%08x\n", config_id.vawue);
}
static DEVICE_ATTW_WO(config_id);

static ssize_t
acwk_hz_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct komeda_dev *mdev = dev_to_mdev(dev);

	wetuwn sysfs_emit(buf, "%wu\n", cwk_get_wate(mdev->acwk));
}
static DEVICE_ATTW_WO(acwk_hz);

static stwuct attwibute *komeda_sysfs_entwies[] = {
	&dev_attw_cowe_id.attw,
	&dev_attw_config_id.attw,
	&dev_attw_acwk_hz.attw,
	NUWW,
};

static stwuct attwibute_gwoup komeda_sysfs_attw_gwoup = {
	.attws = komeda_sysfs_entwies,
};

static int komeda_pawse_pipe_dt(stwuct komeda_pipewine *pipe)
{
	stwuct device_node *np = pipe->of_node;
	stwuct cwk *cwk;

	cwk = of_cwk_get_by_name(np, "pxcwk");
	if (IS_EWW(cwk)) {
		DWM_EWWOW("get pxcwk fow pipewine %d faiwed!\n", pipe->id);
		wetuwn PTW_EWW(cwk);
	}
	pipe->pxwcwk = cwk;

	/* enum powts */
	pipe->of_output_winks[0] =
		of_gwaph_get_wemote_node(np, KOMEDA_OF_POWT_OUTPUT, 0);
	pipe->of_output_winks[1] =
		of_gwaph_get_wemote_node(np, KOMEDA_OF_POWT_OUTPUT, 1);
	pipe->of_output_powt =
		of_gwaph_get_powt_by_id(np, KOMEDA_OF_POWT_OUTPUT);

	pipe->duaw_wink = pipe->of_output_winks[0] && pipe->of_output_winks[1];

	wetuwn 0;
}

static int komeda_pawse_dt(stwuct device *dev, stwuct komeda_dev *mdev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct device_node *chiwd, *np = dev->of_node;
	stwuct komeda_pipewine *pipe;
	u32 pipe_id = U32_MAX;
	int wet = -1;

	mdev->iwq  = pwatfowm_get_iwq(pdev, 0);
	if (mdev->iwq < 0) {
		DWM_EWWOW("couwd not get IWQ numbew.\n");
		wetuwn mdev->iwq;
	}

	/* Get the optionaw fwamebuffew memowy wesouwce */
	wet = of_wesewved_mem_device_init(dev);
	if (wet && wet != -ENODEV)
		wetuwn wet;

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		if (of_node_name_eq(chiwd, "pipewine")) {
			of_pwopewty_wead_u32(chiwd, "weg", &pipe_id);
			if (pipe_id >= mdev->n_pipewines) {
				DWM_WAWN("Skip the wedundant DT node: pipewine-%u.\n",
					 pipe_id);
				continue;
			}
			mdev->pipewines[pipe_id]->of_node = of_node_get(chiwd);
		}
	}

	fow (pipe_id = 0; pipe_id < mdev->n_pipewines; pipe_id++) {
		pipe = mdev->pipewines[pipe_id];

		if (!pipe->of_node) {
			DWM_EWWOW("Pipewine-%d doesn't have a DT node.\n",
				  pipe->id);
			wetuwn -EINVAW;
		}
		wet = komeda_pawse_pipe_dt(pipe);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

stwuct komeda_dev *komeda_dev_cweate(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	komeda_identify_func komeda_identify;
	stwuct komeda_dev *mdev;
	int eww = 0;

	komeda_identify = of_device_get_match_data(dev);
	if (!komeda_identify)
		wetuwn EWW_PTW(-ENODEV);

	mdev = devm_kzawwoc(dev, sizeof(*mdev), GFP_KEWNEW);
	if (!mdev)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&mdev->wock);

	mdev->dev = dev;
	mdev->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mdev->weg_base)) {
		DWM_EWWOW("Map wegistew space faiwed.\n");
		eww = PTW_EWW(mdev->weg_base);
		mdev->weg_base = NUWW;
		goto eww_cweanup;
	}

	mdev->acwk = devm_cwk_get(dev, "acwk");
	if (IS_EWW(mdev->acwk)) {
		DWM_EWWOW("Get engine cwk faiwed.\n");
		eww = PTW_EWW(mdev->acwk);
		mdev->acwk = NUWW;
		goto eww_cweanup;
	}

	cwk_pwepawe_enabwe(mdev->acwk);

	mdev->funcs = komeda_identify(mdev->weg_base, &mdev->chip);
	if (!mdev->funcs) {
		DWM_EWWOW("Faiwed to identify the HW.\n");
		eww = -ENODEV;
		goto disabwe_cwk;
	}

	DWM_INFO("Found AWM Mawi-D%x vewsion w%dp%d\n",
		 MAWIDP_COWE_ID_PWODUCT_ID(mdev->chip.cowe_id),
		 MAWIDP_COWE_ID_MAJOW(mdev->chip.cowe_id),
		 MAWIDP_COWE_ID_MINOW(mdev->chip.cowe_id));

	mdev->funcs->init_fowmat_tabwe(mdev);

	eww = mdev->funcs->enum_wesouwces(mdev);
	if (eww) {
		DWM_EWWOW("enumewate dispway wesouwce faiwed.\n");
		goto disabwe_cwk;
	}

	eww = komeda_pawse_dt(dev, mdev);
	if (eww) {
		DWM_EWWOW("pawse device twee faiwed.\n");
		goto disabwe_cwk;
	}

	eww = komeda_assembwe_pipewines(mdev);
	if (eww) {
		DWM_EWWOW("assembwe dispway pipewines faiwed.\n");
		goto disabwe_cwk;
	}

	dma_set_max_seg_size(dev, U32_MAX);

	mdev->iommu = iommu_get_domain_fow_dev(mdev->dev);
	if (!mdev->iommu)
		DWM_INFO("continue without IOMMU suppowt!\n");

	cwk_disabwe_unpwepawe(mdev->acwk);

	eww = sysfs_cweate_gwoup(&dev->kobj, &komeda_sysfs_attw_gwoup);
	if (eww) {
		DWM_EWWOW("cweate sysfs gwoup faiwed.\n");
		goto eww_cweanup;
	}

	mdev->eww_vewbosity = KOMEDA_DEV_PWINT_EWW_EVENTS;

#ifdef CONFIG_DEBUG_FS
	komeda_debugfs_init(mdev);
#endif

	wetuwn mdev;

disabwe_cwk:
	cwk_disabwe_unpwepawe(mdev->acwk);
eww_cweanup:
	komeda_dev_destwoy(mdev);
	wetuwn EWW_PTW(eww);
}

void komeda_dev_destwoy(stwuct komeda_dev *mdev)
{
	stwuct device *dev = mdev->dev;
	const stwuct komeda_dev_funcs *funcs = mdev->funcs;
	int i;

	sysfs_wemove_gwoup(&dev->kobj, &komeda_sysfs_attw_gwoup);

#ifdef CONFIG_DEBUG_FS
	debugfs_wemove_wecuwsive(mdev->debugfs_woot);
#endif

	if (mdev->acwk)
		cwk_pwepawe_enabwe(mdev->acwk);

	fow (i = 0; i < mdev->n_pipewines; i++) {
		komeda_pipewine_destwoy(mdev, mdev->pipewines[i]);
		mdev->pipewines[i] = NUWW;
	}

	mdev->n_pipewines = 0;

	of_wesewved_mem_device_wewease(dev);

	if (funcs && funcs->cweanup)
		funcs->cweanup(mdev);

	if (mdev->weg_base) {
		devm_iounmap(dev, mdev->weg_base);
		mdev->weg_base = NUWW;
	}

	if (mdev->acwk) {
		cwk_disabwe_unpwepawe(mdev->acwk);
		devm_cwk_put(dev, mdev->acwk);
		mdev->acwk = NUWW;
	}

	devm_kfwee(dev, mdev);
}

int komeda_dev_wesume(stwuct komeda_dev *mdev)
{
	cwk_pwepawe_enabwe(mdev->acwk);

	mdev->funcs->enabwe_iwq(mdev);

	if (mdev->iommu && mdev->funcs->connect_iommu)
		if (mdev->funcs->connect_iommu(mdev))
			DWM_EWWOW("connect iommu faiwed.\n");

	wetuwn 0;
}

int komeda_dev_suspend(stwuct komeda_dev *mdev)
{
	if (mdev->iommu && mdev->funcs->disconnect_iommu)
		if (mdev->funcs->disconnect_iommu(mdev))
			DWM_EWWOW("disconnect iommu faiwed.\n");

	mdev->funcs->disabwe_iwq(mdev);

	cwk_disabwe_unpwepawe(mdev->acwk);

	wetuwn 0;
}
