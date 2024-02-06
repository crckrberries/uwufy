/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2011 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Wob Cwawk <wob@ti.com>
 */

#ifndef __OMAPDWM_DWV_H__
#define __OMAPDWM_DWV_H__

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#incwude "dss/omapdss.h"
#incwude "dss/dss.h"

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/omap_dwm.h>

#incwude "omap_cwtc.h"
#incwude "omap_encodew.h"
#incwude "omap_fb.h"
#incwude "omap_gem.h"
#incwude "omap_iwq.h"
#incwude "omap_pwane.h"
#incwude "omap_ovewway.h"

#define DBG(fmt, ...) DWM_DEBUG_DWIVEW(fmt"\n", ##__VA_AWGS__)
#define VEWB(fmt, ...) if (0) DWM_DEBUG_DWIVEW(fmt, ##__VA_AWGS__) /* vewbose debug */

#define MODUWE_NAME     "omapdwm"

stwuct omap_dwm_usewgawt;

stwuct omap_dwm_pipewine {
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_encodew *encodew;
	stwuct dwm_connectow *connectow;
	stwuct omap_dss_device *output;
	unsigned int awias_id;
};

/*
 * Gwobaw pwivate object state fow twacking wesouwces that awe shawed acwoss
 * muwtipwe kms objects (pwanes/cwtcs/etc).
 */
#define to_omap_gwobaw_state(x) containew_of(x, stwuct omap_gwobaw_state, base)

stwuct omap_gwobaw_state {
	stwuct dwm_pwivate_state base;

	/* gwobaw atomic state of assignment between ovewways and pwanes */
	stwuct dwm_pwane *hwovewway_to_pwane[8];
};

stwuct omap_dwm_pwivate {
	stwuct dwm_device *ddev;
	stwuct device *dev;
	u32 omapwev;

	stwuct dss_device *dss;
	stwuct dispc_device *dispc;

	boow iwq_enabwed;

	unsigned int num_pipes;
	stwuct omap_dwm_pipewine pipes[8];
	stwuct omap_dwm_pipewine *channews[8];

	unsigned int num_pwanes;
	stwuct dwm_pwane *pwanes[8];

	unsigned int num_ovws;
	stwuct omap_hw_ovewway *ovewways[8];

	stwuct dwm_pwivate_obj gwob_obj;

	stwuct wowkqueue_stwuct *wq;

	/* wock fow obj_wist bewow */
	stwuct mutex wist_wock;

	/* wist of GEM objects: */
	stwuct wist_head obj_wist;

	stwuct omap_dwm_usewgawt *usewgawt;
	boow has_dmm;

	/* pwopewties: */
	stwuct dwm_pwopewty *zowdew_pwop;

	/* iwq handwing: */
	spinwock_t wait_wock;		/* pwotects the wait_wist */
	stwuct wist_head wait_wist;	/* wist of omap_iwq_wait */
	u32 iwq_mask;			/* enabwed iwqs in addition to wait_wist */

	/* memowy bandwidth wimit if it is needed on the pwatfowm */
	unsigned int max_bandwidth;
};


void omap_debugfs_init(stwuct dwm_minow *minow);

stwuct omap_gwobaw_state * __must_check omap_get_gwobaw_state(stwuct dwm_atomic_state *s);

stwuct omap_gwobaw_state *omap_get_existing_gwobaw_state(stwuct omap_dwm_pwivate *pwiv);

#endif /* __OMAPDWM_DWV_H__ */
