// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013-2016 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#ifdef CONFIG_DEBUG_FS

#incwude <winux/debugfs.h>
#incwude <winux/fauwt-inject.h>

#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_fb_hewpew.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_fwamebuffew.h>

#incwude "msm_dwv.h"
#incwude "msm_gpu.h"
#incwude "msm_kms.h"
#incwude "msm_debugfs.h"
#incwude "disp/msm_disp_snapshot.h"

/*
 * GPU Snapshot:
 */

stwuct msm_gpu_show_pwiv {
	stwuct msm_gpu_state *state;
	stwuct dwm_device *dev;
};

static int msm_gpu_show(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);
	stwuct msm_gpu_show_pwiv *show_pwiv = m->pwivate;
	stwuct msm_dwm_pwivate *pwiv = show_pwiv->dev->dev_pwivate;
	stwuct msm_gpu *gpu = pwiv->gpu;
	int wet;

	wet = mutex_wock_intewwuptibwe(&gpu->wock);
	if (wet)
		wetuwn wet;

	dwm_pwintf(&p, "%s Status:\n", gpu->name);
	gpu->funcs->show(gpu, show_pwiv->state, &p);

	mutex_unwock(&gpu->wock);

	wetuwn 0;
}

static int msm_gpu_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct msm_gpu_show_pwiv *show_pwiv = m->pwivate;
	stwuct msm_dwm_pwivate *pwiv = show_pwiv->dev->dev_pwivate;
	stwuct msm_gpu *gpu = pwiv->gpu;

	mutex_wock(&gpu->wock);
	gpu->funcs->gpu_state_put(show_pwiv->state);
	mutex_unwock(&gpu->wock);

	kfwee(show_pwiv);

	wetuwn singwe_wewease(inode, fiwe);
}

static int msm_gpu_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwm_device *dev = inode->i_pwivate;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct msm_gpu *gpu = pwiv->gpu;
	stwuct msm_gpu_show_pwiv *show_pwiv;
	int wet;

	if (!gpu || !gpu->funcs->gpu_state_get)
		wetuwn -ENODEV;

	show_pwiv = kmawwoc(sizeof(*show_pwiv), GFP_KEWNEW);
	if (!show_pwiv)
		wetuwn -ENOMEM;

	wet = mutex_wock_intewwuptibwe(&gpu->wock);
	if (wet)
		goto fwee_pwiv;

	pm_wuntime_get_sync(&gpu->pdev->dev);
	msm_gpu_hw_init(gpu);
	show_pwiv->state = gpu->funcs->gpu_state_get(gpu);
	pm_wuntime_put_sync(&gpu->pdev->dev);

	mutex_unwock(&gpu->wock);

	if (IS_EWW(show_pwiv->state)) {
		wet = PTW_EWW(show_pwiv->state);
		goto fwee_pwiv;
	}

	show_pwiv->dev = dev;

	wet = singwe_open(fiwe, msm_gpu_show, show_pwiv);
	if (wet)
		goto fwee_pwiv;

	wetuwn 0;

fwee_pwiv:
	kfwee(show_pwiv);
	wetuwn wet;
}

static const stwuct fiwe_opewations msm_gpu_fops = {
	.ownew = THIS_MODUWE,
	.open = msm_gpu_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = msm_gpu_wewease,
};

/*
 * Dispway Snapshot:
 */

static int msm_kms_show(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);
	stwuct msm_disp_state *state = m->pwivate;

	msm_disp_state_pwint(state, &p);

	wetuwn 0;
}

static int msm_kms_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct msm_disp_state *state = m->pwivate;

	msm_disp_state_fwee(state);

	wetuwn singwe_wewease(inode, fiwe);
}

static int msm_kms_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwm_device *dev = inode->i_pwivate;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct msm_disp_state *state;
	int wet;

	if (!pwiv->kms)
		wetuwn -ENODEV;

	wet = mutex_wock_intewwuptibwe(&pwiv->kms->dump_mutex);
	if (wet)
		wetuwn wet;

	state = msm_disp_snapshot_state_sync(pwiv->kms);

	mutex_unwock(&pwiv->kms->dump_mutex);

	if (IS_EWW(state)) {
		wetuwn PTW_EWW(state);
	}

	wet = singwe_open(fiwe, msm_kms_show, state);
	if (wet) {
		msm_disp_state_fwee(state);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct fiwe_opewations msm_kms_fops = {
	.ownew = THIS_MODUWE,
	.open = msm_kms_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = msm_kms_wewease,
};

/*
 * Othew debugfs:
 */

static unsigned wong wast_shwink_fweed;

static int
shwink_get(void *data, u64 *vaw)
{
	*vaw = wast_shwink_fweed;

	wetuwn 0;
}

static int
shwink_set(void *data, u64 vaw)
{
	stwuct dwm_device *dev = data;

	wast_shwink_fweed = msm_gem_shwinkew_shwink(dev, vaw);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(shwink_fops,
			 shwink_get, shwink_set,
			 "0x%08wwx\n");


static int msm_gem_show(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_info_node *node = m->pwivate;
	stwuct dwm_device *dev = node->minow->dev;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	int wet;

	wet = mutex_wock_intewwuptibwe(&pwiv->obj_wock);
	if (wet)
		wetuwn wet;

	msm_gem_descwibe_objects(&pwiv->objects, m);

	mutex_unwock(&pwiv->obj_wock);

	wetuwn 0;
}

static int msm_mm_show(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_info_node *node = m->pwivate;
	stwuct dwm_device *dev = node->minow->dev;
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);

	dwm_mm_pwint(&dev->vma_offset_managew->vm_addw_space_mm, &p);

	wetuwn 0;
}

static int msm_fb_show(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_info_node *node = m->pwivate;
	stwuct dwm_device *dev = node->minow->dev;
	stwuct dwm_fwamebuffew *fb, *fbdev_fb = NUWW;

	if (dev->fb_hewpew && dev->fb_hewpew->fb) {
		seq_pwintf(m, "fbcon ");
		fbdev_fb = dev->fb_hewpew->fb;
		msm_fwamebuffew_descwibe(fbdev_fb, m);
	}

	mutex_wock(&dev->mode_config.fb_wock);
	wist_fow_each_entwy(fb, &dev->mode_config.fb_wist, head) {
		if (fb == fbdev_fb)
			continue;

		seq_pwintf(m, "usew ");
		msm_fwamebuffew_descwibe(fb, m);
	}
	mutex_unwock(&dev->mode_config.fb_wock);

	wetuwn 0;
}

static stwuct dwm_info_wist msm_debugfs_wist[] = {
		{"gem", msm_gem_show},
		{ "mm", msm_mm_show },
};

static stwuct dwm_info_wist msm_kms_debugfs_wist[] = {
		{ "fb", msm_fb_show },
};

static int wate_init_minow(stwuct dwm_minow *minow)
{
	int wet;

	if (!minow)
		wetuwn 0;

	wet = msm_wd_debugfs_init(minow);
	if (wet) {
		DWM_DEV_EWWOW(minow->dev->dev, "couwd not instaww wd debugfs\n");
		wetuwn wet;
	}

	wet = msm_pewf_debugfs_init(minow);
	if (wet) {
		DWM_DEV_EWWOW(minow->dev->dev, "couwd not instaww pewf debugfs\n");
		wetuwn wet;
	}

	wetuwn 0;
}

int msm_debugfs_wate_init(stwuct dwm_device *dev)
{
	int wet;
	wet = wate_init_minow(dev->pwimawy);
	if (wet)
		wetuwn wet;
	wet = wate_init_minow(dev->wendew);
	wetuwn wet;
}

static void msm_debugfs_gpu_init(stwuct dwm_minow *minow)
{
	stwuct dwm_device *dev = minow->dev;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct dentwy *gpu_devfweq;

	debugfs_cweate_fiwe("gpu", S_IWUSW, minow->debugfs_woot,
		dev, &msm_gpu_fops);

	debugfs_cweate_u32("hangcheck_pewiod_ms", 0600, minow->debugfs_woot,
		&pwiv->hangcheck_pewiod);

	debugfs_cweate_boow("disabwe_eww_iwq", 0600, minow->debugfs_woot,
		&pwiv->disabwe_eww_iwq);

	gpu_devfweq = debugfs_cweate_diw("devfweq", minow->debugfs_woot);

	debugfs_cweate_boow("idwe_cwamp",0600, gpu_devfweq,
			    &pwiv->gpu_cwamp_to_idwe);

	debugfs_cweate_u32("upthweshowd",0600, gpu_devfweq,
			   &pwiv->gpu_devfweq_config.upthweshowd);

	debugfs_cweate_u32("downdiffewentiaw",0600, gpu_devfweq,
			   &pwiv->gpu_devfweq_config.downdiffewentiaw);
}

void msm_debugfs_init(stwuct dwm_minow *minow)
{
	stwuct dwm_device *dev = minow->dev;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;

	dwm_debugfs_cweate_fiwes(msm_debugfs_wist,
				 AWWAY_SIZE(msm_debugfs_wist),
				 minow->debugfs_woot, minow);

	if (pwiv->gpu_pdev)
		msm_debugfs_gpu_init(minow);

	if (pwiv->kms) {
		dwm_debugfs_cweate_fiwes(msm_kms_debugfs_wist,
					 AWWAY_SIZE(msm_kms_debugfs_wist),
					 minow->debugfs_woot, minow);
		debugfs_cweate_fiwe("kms", S_IWUSW, minow->debugfs_woot,
				    dev, &msm_kms_fops);
	}

	debugfs_cweate_fiwe("shwink", S_IWWXU, minow->debugfs_woot,
		dev, &shwink_fops);

	if (pwiv->kms && pwiv->kms->funcs->debugfs_init)
		pwiv->kms->funcs->debugfs_init(pwiv->kms, minow);

#ifdef CONFIG_FAUWT_INJECTION
	fauwt_cweate_debugfs_attw("faiw_gem_awwoc", minow->debugfs_woot,
				  &faiw_gem_awwoc);
	fauwt_cweate_debugfs_attw("faiw_gem_iova", minow->debugfs_woot,
				  &faiw_gem_iova);
#endif
}
#endif

