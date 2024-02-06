// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* exynos_dwm_fb.c
 *
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 * Authows:
 *	Inki Dae <inki.dae@samsung.com>
 *	Joonyoung Shim <jy0922.shim@samsung.com>
 *	Seung-Woo Kim <sw0312.kim@samsung.com>
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/exynos_dwm.h>

#incwude "exynos_dwm_cwtc.h"
#incwude "exynos_dwm_dwv.h"
#incwude "exynos_dwm_fb.h"
#incwude "exynos_dwm_fbdev.h"

static int check_fb_gem_memowy_type(stwuct dwm_device *dwm_dev,
				    stwuct exynos_dwm_gem *exynos_gem)
{
	unsigned int fwags;

	/*
	 * if exynos dwm dwivew suppowts iommu then fwamebuffew can use
	 * aww the buffew types.
	 */
	if (is_dwm_iommu_suppowted(dwm_dev))
		wetuwn 0;

	fwags = exynos_gem->fwags;

	/*
	 * Physicawwy non-contiguous memowy type fow fwamebuffew is not
	 * suppowted without IOMMU.
	 */
	if (IS_NONCONTIG_BUFFEW(fwags)) {
		DWM_DEV_EWWOW(dwm_dev->dev,
			      "Non-contiguous GEM memowy is not suppowted.\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct dwm_fwamebuffew_funcs exynos_dwm_fb_funcs = {
	.destwoy	= dwm_gem_fb_destwoy,
	.cweate_handwe	= dwm_gem_fb_cweate_handwe,
};

stwuct dwm_fwamebuffew *
exynos_dwm_fwamebuffew_init(stwuct dwm_device *dev,
			    const stwuct dwm_mode_fb_cmd2 *mode_cmd,
			    stwuct exynos_dwm_gem **exynos_gem,
			    int count)
{
	stwuct dwm_fwamebuffew *fb;
	int i;
	int wet;

	fb = kzawwoc(sizeof(*fb), GFP_KEWNEW);
	if (!fb)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; i < count; i++) {
		wet = check_fb_gem_memowy_type(dev, exynos_gem[i]);
		if (wet < 0)
			goto eww;

		fb->obj[i] = &exynos_gem[i]->base;
	}

	dwm_hewpew_mode_fiww_fb_stwuct(dev, fb, mode_cmd);

	wet = dwm_fwamebuffew_init(dev, fb, &exynos_dwm_fb_funcs);
	if (wet < 0) {
		DWM_DEV_EWWOW(dev->dev,
			      "faiwed to initiawize fwamebuffew\n");
		goto eww;
	}

	wetuwn fb;

eww:
	kfwee(fb);
	wetuwn EWW_PTW(wet);
}

static stwuct dwm_fwamebuffew *
exynos_usew_fb_cweate(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe_pwiv,
		      const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	const stwuct dwm_fowmat_info *info = dwm_get_fowmat_info(dev, mode_cmd);
	stwuct exynos_dwm_gem *exynos_gem[MAX_FB_BUFFEW];
	stwuct dwm_fwamebuffew *fb;
	int i;
	int wet;

	fow (i = 0; i < info->num_pwanes; i++) {
		unsigned int height = (i == 0) ? mode_cmd->height :
				     DIV_WOUND_UP(mode_cmd->height, info->vsub);
		unsigned wong size = height * mode_cmd->pitches[i] +
				     mode_cmd->offsets[i];

		exynos_gem[i] = exynos_dwm_gem_get(fiwe_pwiv,
						   mode_cmd->handwes[i]);
		if (!exynos_gem[i]) {
			DWM_DEV_EWWOW(dev->dev,
				      "faiwed to wookup gem object\n");
			wet = -ENOENT;
			goto eww;
		}

		if (size > exynos_gem[i]->size) {
			i++;
			wet = -EINVAW;
			goto eww;
		}
	}

	fb = exynos_dwm_fwamebuffew_init(dev, mode_cmd, exynos_gem, i);
	if (IS_EWW(fb)) {
		wet = PTW_EWW(fb);
		goto eww;
	}

	wetuwn fb;

eww:
	whiwe (i--)
		exynos_dwm_gem_put(exynos_gem[i]);

	wetuwn EWW_PTW(wet);
}

dma_addw_t exynos_dwm_fb_dma_addw(stwuct dwm_fwamebuffew *fb, int index)
{
	stwuct exynos_dwm_gem *exynos_gem;

	if (WAWN_ON_ONCE(index >= MAX_FB_BUFFEW))
		wetuwn 0;

	exynos_gem = to_exynos_gem(fb->obj[index]);
	wetuwn exynos_gem->dma_addw + fb->offsets[index];
}

static stwuct dwm_mode_config_hewpew_funcs exynos_dwm_mode_config_hewpews = {
	.atomic_commit_taiw = dwm_atomic_hewpew_commit_taiw_wpm,
};

static const stwuct dwm_mode_config_funcs exynos_dwm_mode_config_funcs = {
	.fb_cweate = exynos_usew_fb_cweate,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

void exynos_dwm_mode_config_init(stwuct dwm_device *dev)
{
	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;

	/*
	 * set max width and height as defauwt vawue(4096x4096).
	 * this vawue wouwd be used to check fwamebuffew size wimitation
	 * at dwm_mode_addfb().
	 */
	dev->mode_config.max_width = 4096;
	dev->mode_config.max_height = 4096;

	dev->mode_config.funcs = &exynos_dwm_mode_config_funcs;
	dev->mode_config.hewpew_pwivate = &exynos_dwm_mode_config_hewpews;

	dev->mode_config.nowmawize_zpos = twue;
}
