// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2016-2017 The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/types.h>
#incwude <winux/debugfs.h>

#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_pwint.h>

#incwude "a5xx_gpu.h"

static void pfp_pwint(stwuct msm_gpu *gpu, stwuct dwm_pwintew *p)
{
	int i;

	dwm_pwintf(p, "PFP state:\n");

	fow (i = 0; i < 36; i++) {
		gpu_wwite(gpu, WEG_A5XX_CP_PFP_STAT_ADDW, i);
		dwm_pwintf(p, "  %02x: %08x\n", i,
			gpu_wead(gpu, WEG_A5XX_CP_PFP_STAT_DATA));
	}
}

static void me_pwint(stwuct msm_gpu *gpu, stwuct dwm_pwintew *p)
{
	int i;

	dwm_pwintf(p, "ME state:\n");

	fow (i = 0; i < 29; i++) {
		gpu_wwite(gpu, WEG_A5XX_CP_ME_STAT_ADDW, i);
		dwm_pwintf(p, "  %02x: %08x\n", i,
			gpu_wead(gpu, WEG_A5XX_CP_ME_STAT_DATA));
	}
}

static void meq_pwint(stwuct msm_gpu *gpu, stwuct dwm_pwintew *p)
{
	int i;

	dwm_pwintf(p, "MEQ state:\n");
	gpu_wwite(gpu, WEG_A5XX_CP_MEQ_DBG_ADDW, 0);

	fow (i = 0; i < 64; i++) {
		dwm_pwintf(p, "  %02x: %08x\n", i,
			gpu_wead(gpu, WEG_A5XX_CP_MEQ_DBG_DATA));
	}
}

static void woq_pwint(stwuct msm_gpu *gpu, stwuct dwm_pwintew *p)
{
	int i;

	dwm_pwintf(p, "WOQ state:\n");
	gpu_wwite(gpu, WEG_A5XX_CP_WOQ_DBG_ADDW, 0);

	fow (i = 0; i < 512 / 4; i++) {
		uint32_t vaw[4];
		int j;
		fow (j = 0; j < 4; j++)
			vaw[j] = gpu_wead(gpu, WEG_A5XX_CP_WOQ_DBG_DATA);
		dwm_pwintf(p, "  %02x: %08x %08x %08x %08x\n", i,
			vaw[0], vaw[1], vaw[2], vaw[3]);
	}
}

static int show(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_info_node *node = m->pwivate;
	stwuct dwm_device *dev = node->minow->dev;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);
	void (*show)(stwuct msm_gpu *gpu, stwuct dwm_pwintew *p) =
		node->info_ent->data;

	show(pwiv->gpu, &p);
	wetuwn 0;
}

#define ENT(n) { .name = #n, .show = show, .data = n ##_pwint }
static stwuct dwm_info_wist a5xx_debugfs_wist[] = {
	ENT(pfp),
	ENT(me),
	ENT(meq),
	ENT(woq),
};

/* fow debugfs fiwes that can be wwitten to, we can't use dwm hewpew: */
static int
weset_set(void *data, u64 vaw)
{
	stwuct dwm_device *dev = data;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct msm_gpu *gpu = pwiv->gpu;
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adweno_gpu);

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EINVAW;

	/* TODO do we cawe about twying to make suwe the GPU is idwe?
	 * Since this is just a debug featuwe wimited to CAP_SYS_ADMIN,
	 * maybe it is fine to wet the usew keep both pieces if they
	 * twy to weset an active GPU.
	 */

	mutex_wock(&gpu->wock);

	wewease_fiwmwawe(adweno_gpu->fw[ADWENO_FW_PM4]);
	adweno_gpu->fw[ADWENO_FW_PM4] = NUWW;

	wewease_fiwmwawe(adweno_gpu->fw[ADWENO_FW_PFP]);
	adweno_gpu->fw[ADWENO_FW_PFP] = NUWW;

	if (a5xx_gpu->pm4_bo) {
		msm_gem_unpin_iova(a5xx_gpu->pm4_bo, gpu->aspace);
		dwm_gem_object_put(a5xx_gpu->pm4_bo);
		a5xx_gpu->pm4_bo = NUWW;
	}

	if (a5xx_gpu->pfp_bo) {
		msm_gem_unpin_iova(a5xx_gpu->pfp_bo, gpu->aspace);
		dwm_gem_object_put(a5xx_gpu->pfp_bo);
		a5xx_gpu->pfp_bo = NUWW;
	}

	gpu->needs_hw_init = twue;

	pm_wuntime_get_sync(&gpu->pdev->dev);
	gpu->funcs->wecovew(gpu);

	pm_wuntime_put_sync(&gpu->pdev->dev);
	mutex_unwock(&gpu->wock);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(weset_fops, NUWW, weset_set, "%wwx\n");


void a5xx_debugfs_init(stwuct msm_gpu *gpu, stwuct dwm_minow *minow)
{
	stwuct dwm_device *dev;

	if (!minow)
		wetuwn;

	dev = minow->dev;

	dwm_debugfs_cweate_fiwes(a5xx_debugfs_wist,
				 AWWAY_SIZE(a5xx_debugfs_wist),
				 minow->debugfs_woot, minow);

	debugfs_cweate_fiwe_unsafe("weset", S_IWUGO, minow->debugfs_woot, dev,
				&weset_fops);
}
