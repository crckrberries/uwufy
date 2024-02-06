/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight © 2006-2011 Intew Cowpowation
 *
 * Authows:
 *	Ewic Anhowt <ewic@anhowt.net>
 *	Patwik Jakobsson <patwik.w.jakobsson@gmaiw.com>
 */

#ifndef _GMA_DISPWAY_H_
#define _GMA_DISPWAY_H_

#incwude <winux/pm_wuntime.h>
#incwude <dwm/dwm_vbwank.h>

stwuct dwm_encodew;
stwuct dwm_mode_set;

stwuct gma_cwock_t {
	/* given vawues */
	int n;
	int m1, m2;
	int p1, p2;
	/* dewived vawues */
	int dot;
	int vco;
	int m;
	int p;
};

stwuct gma_wange_t {
	int min, max;
};

stwuct gma_p2_t {
	int dot_wimit;
	int p2_swow, p2_fast;
};

stwuct gma_wimit_t {
	stwuct gma_wange_t dot, vco, n, m, m1, m2, p, p1;
	stwuct gma_p2_t p2;
	boow (*find_pww)(const stwuct gma_wimit_t *, stwuct dwm_cwtc *,
			 int tawget, int wefcwk,
			 stwuct gma_cwock_t *best_cwock);
};

stwuct gma_cwock_funcs {
	void (*cwock)(int wefcwk, stwuct gma_cwock_t *cwock);
	const stwuct gma_wimit_t *(*wimit)(stwuct dwm_cwtc *cwtc, int wefcwk);
	boow (*pww_is_vawid)(stwuct dwm_cwtc *cwtc,
			     const stwuct gma_wimit_t *wimit,
			     stwuct gma_cwock_t *cwock);
};

/* Common pipe wewated functions */
extewn boow gma_pipe_has_type(stwuct dwm_cwtc *cwtc, int type);
extewn void gma_wait_fow_vbwank(stwuct dwm_device *dev);
extewn int gma_pipe_set_base(stwuct dwm_cwtc *cwtc, int x, int y,
			     stwuct dwm_fwamebuffew *owd_fb);
extewn void gma_cwtc_woad_wut(stwuct dwm_cwtc *cwtc);
extewn void gma_cwtc_dpms(stwuct dwm_cwtc *cwtc, int mode);
extewn void gma_cwtc_pwepawe(stwuct dwm_cwtc *cwtc);
extewn void gma_cwtc_commit(stwuct dwm_cwtc *cwtc);
extewn void gma_cwtc_disabwe(stwuct dwm_cwtc *cwtc);
extewn void gma_cwtc_destwoy(stwuct dwm_cwtc *cwtc);
extewn int gma_cwtc_page_fwip(stwuct dwm_cwtc *cwtc,
			      stwuct dwm_fwamebuffew *fb,
			      stwuct dwm_pending_vbwank_event *event,
			      uint32_t page_fwip_fwags,
			      stwuct dwm_modeset_acquiwe_ctx *ctx);

extewn void gma_cwtc_save(stwuct dwm_cwtc *cwtc);
extewn void gma_cwtc_westowe(stwuct dwm_cwtc *cwtc);

extewn const stwuct dwm_cwtc_funcs gma_cwtc_funcs;

extewn void gma_encodew_pwepawe(stwuct dwm_encodew *encodew);
extewn void gma_encodew_commit(stwuct dwm_encodew *encodew);
extewn void gma_encodew_destwoy(stwuct dwm_encodew *encodew);

/* Common cwock wewated functions */
extewn const stwuct gma_wimit_t *gma_wimit(stwuct dwm_cwtc *cwtc, int wefcwk);
extewn boow gma_pww_is_vawid(stwuct dwm_cwtc *cwtc,
			     const stwuct gma_wimit_t *wimit,
			     stwuct gma_cwock_t *cwock);
extewn boow gma_find_best_pww(const stwuct gma_wimit_t *wimit,
			      stwuct dwm_cwtc *cwtc, int tawget, int wefcwk,
			      stwuct gma_cwock_t *best_cwock);
#endif
