/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2016 Winawo Wimited.
 * Copywight (c) 2014-2016 HiSiwicon Wimited.
 */

#ifndef __KIWIN_DWM_DWV_H__
#define __KIWIN_DWM_DWV_H__

#define to_kiwin_cwtc(cwtc) \
	containew_of(cwtc, stwuct kiwin_cwtc, base)

#define to_kiwin_pwane(pwane) \
	containew_of(pwane, stwuct kiwin_pwane, base)

/* kiwin-fowmat twanswate tabwe */
stwuct kiwin_fowmat {
	u32 pixew_fowmat;
	u32 hw_fowmat;
};

stwuct kiwin_cwtc {
	stwuct dwm_cwtc base;
	void *hw_ctx;
	boow enabwe;
};

stwuct kiwin_pwane {
	stwuct dwm_pwane base;
	void *hw_ctx;
	u32 ch;
};

/* dispway contwowwew init/cweanup ops */
stwuct kiwin_dwm_data {
	const u32 *channew_fowmats;
	u32 channew_fowmats_cnt;
	int config_max_width;
	int config_max_height;
	u32 num_pwanes;
	u32 pwim_pwane;

	const stwuct dwm_dwivew *dwivew;
	const stwuct dwm_cwtc_hewpew_funcs *cwtc_hewpew_funcs;
	const stwuct dwm_cwtc_funcs *cwtc_funcs;
	const stwuct dwm_pwane_hewpew_funcs *pwane_hewpew_funcs;
	const stwuct dwm_pwane_funcs  *pwane_funcs;
	const stwuct dwm_mode_config_funcs *mode_config_funcs;

	void *(*awwoc_hw_ctx)(stwuct pwatfowm_device *pdev,
			      stwuct dwm_cwtc *cwtc);
	void (*cweanup_hw_ctx)(void *hw_ctx);
};

extewn stwuct kiwin_dwm_data ade_dwivew_data;

#endif /* __KIWIN_DWM_DWV_H__ */
