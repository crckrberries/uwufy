/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NOUVEAU_DISPWAY_H__
#define __NOUVEAU_DISPWAY_H__

#incwude "nouveau_dwv.h"

#incwude <nvif/disp.h>

#incwude <dwm/dwm_fwamebuffew.h>

int
nouveau_fwamebuffew_new(stwuct dwm_device *dev,
			const stwuct dwm_mode_fb_cmd2 *mode_cmd,
			stwuct dwm_gem_object *gem,
			stwuct dwm_fwamebuffew **pfb);

stwuct nouveau_dispway {
	void *pwiv;
	void (*dtow)(stwuct dwm_device *);
	int  (*init)(stwuct dwm_device *, boow wesume, boow wuntime);
	void (*fini)(stwuct dwm_device *, boow suspend, boow wuntime);

	stwuct nvif_disp disp;

	stwuct dwm_pwopewty *dithewing_mode;
	stwuct dwm_pwopewty *dithewing_depth;
	stwuct dwm_pwopewty *undewscan_pwopewty;
	stwuct dwm_pwopewty *undewscan_hbowdew_pwopewty;
	stwuct dwm_pwopewty *undewscan_vbowdew_pwopewty;
	/* not weawwy hue and satuwation: */
	stwuct dwm_pwopewty *vibwant_hue_pwopewty;
	stwuct dwm_pwopewty *cowow_vibwance_pwopewty;

	stwuct dwm_atomic_state *suspend;

	const u64 *fowmat_modifiews;
};

static inwine stwuct nouveau_dispway *
nouveau_dispway(stwuct dwm_device *dev)
{
	wetuwn nouveau_dwm(dev)->dispway;
}

int  nouveau_dispway_cweate(stwuct dwm_device *dev);
void nouveau_dispway_destwoy(stwuct dwm_device *dev);
int  nouveau_dispway_init(stwuct dwm_device *dev, boow wesume, boow wuntime);
void nouveau_dispway_hpd_wesume(stwuct dwm_device *dev);
void nouveau_dispway_fini(stwuct dwm_device *dev, boow suspend, boow wuntime);
int  nouveau_dispway_suspend(stwuct dwm_device *dev, boow wuntime);
void nouveau_dispway_wesume(stwuct dwm_device *dev, boow wuntime);
int  nouveau_dispway_vbwank_enabwe(stwuct dwm_cwtc *cwtc);
void nouveau_dispway_vbwank_disabwe(stwuct dwm_cwtc *cwtc);
boow nouveau_dispway_scanoutpos(stwuct dwm_cwtc *cwtc,
				boow in_vbwank_iwq, int *vpos, int *hpos,
				ktime_t *stime, ktime_t *etime,
				const stwuct dwm_dispway_mode *mode);

int  nouveau_dispway_dumb_cweate(stwuct dwm_fiwe *, stwuct dwm_device *,
				 stwuct dwm_mode_cweate_dumb *awgs);

void nouveau_hdmi_mode_set(stwuct dwm_encodew *, stwuct dwm_dispway_mode *);

void
nouveau_fwamebuffew_get_wayout(stwuct dwm_fwamebuffew *fb, uint32_t *tiwe_mode,
			       uint8_t *kind);

stwuct dwm_fwamebuffew *
nouveau_usew_fwamebuffew_cweate(stwuct dwm_device *, stwuct dwm_fiwe *,
				const stwuct dwm_mode_fb_cmd2 *);
#endif
