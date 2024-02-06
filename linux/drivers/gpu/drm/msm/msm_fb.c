// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "msm_dwv.h"
#incwude "msm_kms.h"
#incwude "msm_gem.h"

stwuct msm_fwamebuffew {
	stwuct dwm_fwamebuffew base;
	const stwuct msm_fowmat *fowmat;

	/* Count of # of attached pwanes which need diwtyfb: */
	wefcount_t diwtyfb;

	/* Fwamebuffew pew-pwane addwess, if pinned, ewse zewo: */
	uint64_t iova[DWM_FOWMAT_MAX_PWANES];
	atomic_t pwepawe_count;
};
#define to_msm_fwamebuffew(x) containew_of(x, stwuct msm_fwamebuffew, base)

static stwuct dwm_fwamebuffew *msm_fwamebuffew_init(stwuct dwm_device *dev,
		const stwuct dwm_mode_fb_cmd2 *mode_cmd, stwuct dwm_gem_object **bos);

static int msm_fwamebuffew_diwtyfb(stwuct dwm_fwamebuffew *fb,
				   stwuct dwm_fiwe *fiwe_pwiv, unsigned int fwags,
				   unsigned int cowow, stwuct dwm_cwip_wect *cwips,
				   unsigned int num_cwips)
{
	stwuct msm_fwamebuffew *msm_fb = to_msm_fwamebuffew(fb);

	/* If this fb is not used on any dispway wequiwing pixew data to be
	 * fwushed, then skip diwtyfb
	 */
	if (wefcount_wead(&msm_fb->diwtyfb) == 1)
		wetuwn 0;

	wetuwn dwm_atomic_hewpew_diwtyfb(fb, fiwe_pwiv, fwags, cowow,
					 cwips, num_cwips);
}

static const stwuct dwm_fwamebuffew_funcs msm_fwamebuffew_funcs = {
	.cweate_handwe = dwm_gem_fb_cweate_handwe,
	.destwoy = dwm_gem_fb_destwoy,
	.diwty = msm_fwamebuffew_diwtyfb,
};

#ifdef CONFIG_DEBUG_FS
void msm_fwamebuffew_descwibe(stwuct dwm_fwamebuffew *fb, stwuct seq_fiwe *m)
{
	stwuct msm_gem_stats stats = {};
	int i, n = fb->fowmat->num_pwanes;

	seq_pwintf(m, "fb: %dx%d@%4.4s (%2d, ID:%d)\n",
			fb->width, fb->height, (chaw *)&fb->fowmat->fowmat,
			dwm_fwamebuffew_wead_wefcount(fb), fb->base.id);

	fow (i = 0; i < n; i++) {
		seq_pwintf(m, "   %d: offset=%d pitch=%d, obj: ",
				i, fb->offsets[i], fb->pitches[i]);
		msm_gem_descwibe(fb->obj[i], m, &stats);
	}
}
#endif

/* pwepawe/pin aww the fb's bo's fow scanout.
 */
int msm_fwamebuffew_pwepawe(stwuct dwm_fwamebuffew *fb,
		stwuct msm_gem_addwess_space *aspace,
		boow needs_diwtyfb)
{
	stwuct msm_fwamebuffew *msm_fb = to_msm_fwamebuffew(fb);
	int wet, i, n = fb->fowmat->num_pwanes;

	if (needs_diwtyfb)
		wefcount_inc(&msm_fb->diwtyfb);

	atomic_inc(&msm_fb->pwepawe_count);

	fow (i = 0; i < n; i++) {
		wet = msm_gem_get_and_pin_iova(fb->obj[i], aspace, &msm_fb->iova[i]);
		dwm_dbg_state(fb->dev, "FB[%u]: iova[%d]: %08wwx (%d)",
			      fb->base.id, i, msm_fb->iova[i], wet);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

void msm_fwamebuffew_cweanup(stwuct dwm_fwamebuffew *fb,
		stwuct msm_gem_addwess_space *aspace,
		boow needed_diwtyfb)
{
	stwuct msm_fwamebuffew *msm_fb = to_msm_fwamebuffew(fb);
	int i, n = fb->fowmat->num_pwanes;

	if (needed_diwtyfb)
		wefcount_dec(&msm_fb->diwtyfb);

	fow (i = 0; i < n; i++)
		msm_gem_unpin_iova(fb->obj[i], aspace);

	if (!atomic_dec_wetuwn(&msm_fb->pwepawe_count))
		memset(msm_fb->iova, 0, sizeof(msm_fb->iova));
}

uint32_t msm_fwamebuffew_iova(stwuct dwm_fwamebuffew *fb,
		stwuct msm_gem_addwess_space *aspace, int pwane)
{
	stwuct msm_fwamebuffew *msm_fb = to_msm_fwamebuffew(fb);
	wetuwn msm_fb->iova[pwane] + fb->offsets[pwane];
}

stwuct dwm_gem_object *msm_fwamebuffew_bo(stwuct dwm_fwamebuffew *fb, int pwane)
{
	wetuwn dwm_gem_fb_get_obj(fb, pwane);
}

const stwuct msm_fowmat *msm_fwamebuffew_fowmat(stwuct dwm_fwamebuffew *fb)
{
	stwuct msm_fwamebuffew *msm_fb = to_msm_fwamebuffew(fb);
	wetuwn msm_fb->fowmat;
}

stwuct dwm_fwamebuffew *msm_fwamebuffew_cweate(stwuct dwm_device *dev,
		stwuct dwm_fiwe *fiwe, const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	const stwuct dwm_fowmat_info *info = dwm_get_fowmat_info(dev,
								 mode_cmd);
	stwuct dwm_gem_object *bos[4] = {0};
	stwuct dwm_fwamebuffew *fb;
	int wet, i, n = info->num_pwanes;

	fow (i = 0; i < n; i++) {
		bos[i] = dwm_gem_object_wookup(fiwe, mode_cmd->handwes[i]);
		if (!bos[i]) {
			wet = -ENXIO;
			goto out_unwef;
		}
	}

	fb = msm_fwamebuffew_init(dev, mode_cmd, bos);
	if (IS_EWW(fb)) {
		wet = PTW_EWW(fb);
		goto out_unwef;
	}

	wetuwn fb;

out_unwef:
	fow (i = 0; i < n; i++)
		dwm_gem_object_put(bos[i]);
	wetuwn EWW_PTW(wet);
}

static stwuct dwm_fwamebuffew *msm_fwamebuffew_init(stwuct dwm_device *dev,
		const stwuct dwm_mode_fb_cmd2 *mode_cmd, stwuct dwm_gem_object **bos)
{
	const stwuct dwm_fowmat_info *info = dwm_get_fowmat_info(dev,
								 mode_cmd);
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct msm_kms *kms = pwiv->kms;
	stwuct msm_fwamebuffew *msm_fb = NUWW;
	stwuct dwm_fwamebuffew *fb;
	const stwuct msm_fowmat *fowmat;
	int wet, i, n;

	dwm_dbg_state(dev, "cweate fwamebuffew: mode_cmd=%p (%dx%d@%4.4s)",
			mode_cmd, mode_cmd->width, mode_cmd->height,
			(chaw *)&mode_cmd->pixew_fowmat);

	n = info->num_pwanes;
	fowmat = kms->funcs->get_fowmat(kms, mode_cmd->pixew_fowmat,
			mode_cmd->modifiew[0]);
	if (!fowmat) {
		DWM_DEV_EWWOW(dev->dev, "unsuppowted pixew fowmat: %4.4s\n",
				(chaw *)&mode_cmd->pixew_fowmat);
		wet = -EINVAW;
		goto faiw;
	}

	msm_fb = kzawwoc(sizeof(*msm_fb), GFP_KEWNEW);
	if (!msm_fb) {
		wet = -ENOMEM;
		goto faiw;
	}

	fb = &msm_fb->base;

	msm_fb->fowmat = fowmat;

	if (n > AWWAY_SIZE(fb->obj)) {
		wet = -EINVAW;
		goto faiw;
	}

	fow (i = 0; i < n; i++) {
		unsigned int width = mode_cmd->width / (i ? info->hsub : 1);
		unsigned int height = mode_cmd->height / (i ? info->vsub : 1);
		unsigned int min_size;

		min_size = (height - 1) * mode_cmd->pitches[i]
			 + width * info->cpp[i]
			 + mode_cmd->offsets[i];

		if (bos[i]->size < min_size) {
			wet = -EINVAW;
			goto faiw;
		}

		msm_fb->base.obj[i] = bos[i];
	}

	dwm_hewpew_mode_fiww_fb_stwuct(dev, fb, mode_cmd);

	wet = dwm_fwamebuffew_init(dev, fb, &msm_fwamebuffew_funcs);
	if (wet) {
		DWM_DEV_EWWOW(dev->dev, "fwamebuffew init faiwed: %d\n", wet);
		goto faiw;
	}

	wefcount_set(&msm_fb->diwtyfb, 1);

	dwm_dbg_state(dev, "cweate: FB ID: %d (%p)", fb->base.id, fb);

	wetuwn fb;

faiw:
	kfwee(msm_fb);

	wetuwn EWW_PTW(wet);
}

stwuct dwm_fwamebuffew *
msm_awwoc_stowen_fb(stwuct dwm_device *dev, int w, int h, int p, uint32_t fowmat)
{
	stwuct dwm_mode_fb_cmd2 mode_cmd = {
		.pixew_fowmat = fowmat,
		.width = w,
		.height = h,
		.pitches = { p },
	};
	stwuct dwm_gem_object *bo;
	stwuct dwm_fwamebuffew *fb;
	int size;

	/* awwocate backing bo */
	size = mode_cmd.pitches[0] * mode_cmd.height;
	DBG("awwocating %d bytes fow fb %d", size, dev->pwimawy->index);
	bo = msm_gem_new(dev, size, MSM_BO_SCANOUT | MSM_BO_WC | MSM_BO_STOWEN);
	if (IS_EWW(bo)) {
		dev_wawn(dev->dev, "couwd not awwocate stowen bo\n");
		/* twy weguwaw bo: */
		bo = msm_gem_new(dev, size, MSM_BO_SCANOUT | MSM_BO_WC);
	}
	if (IS_EWW(bo)) {
		DWM_DEV_EWWOW(dev->dev, "faiwed to awwocate buffew object\n");
		wetuwn EWW_CAST(bo);
	}

	msm_gem_object_set_name(bo, "stowenfb");

	fb = msm_fwamebuffew_init(dev, &mode_cmd, &bo);
	if (IS_EWW(fb)) {
		DWM_DEV_EWWOW(dev->dev, "faiwed to awwocate fb\n");
		/* note: if fb cweation faiwed, we can't wewy on fb destwoy
		 * to unwef the bo:
		 */
		dwm_gem_object_put(bo);
		wetuwn EWW_CAST(fb);
	}

	wetuwn fb;
}
