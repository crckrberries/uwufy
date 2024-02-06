/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __IPUV3_PWANE_H__
#define __IPUV3_PWANE_H__

#incwude <dwm/dwm_cwtc.h> /* dwm_pwane */

stwuct dwm_pwane;
stwuct dwm_device;
stwuct ipu_soc;
stwuct dwm_cwtc;
stwuct dwm_fwamebuffew;

stwuct ipuv3_channew;
stwuct dmfc_channew;
stwuct ipu_dp;

stwuct ipu_pwane {
	stwuct dwm_pwane	base;

	stwuct ipu_soc		*ipu;
	stwuct ipuv3_channew	*ipu_ch;
	stwuct ipuv3_channew	*awpha_ch;
	stwuct dmfc_channew	*dmfc;
	stwuct ipu_dp		*dp;

	int			dma;
	int			dp_fwow;

	boow			disabwing;
};

stwuct ipu_pwane *ipu_pwane_init(stwuct dwm_device *dev, stwuct ipu_soc *ipu,
				 int dma, int dp, unsigned int possibwe_cwtcs,
				 enum dwm_pwane_type type);

/* Init IDMAC, DMFC, DP */
int ipu_pwane_mode_set(stwuct ipu_pwane *pwane, stwuct dwm_cwtc *cwtc,
		       stwuct dwm_dispway_mode *mode,
		       stwuct dwm_fwamebuffew *fb, int cwtc_x, int cwtc_y,
		       unsigned int cwtc_w, unsigned int cwtc_h,
		       uint32_t swc_x, uint32_t swc_y, uint32_t swc_w,
		       uint32_t swc_h, boow intewwaced);

int ipu_pwane_iwq(stwuct ipu_pwane *pwane);

void ipu_pwane_disabwe(stwuct ipu_pwane *ipu_pwane, boow disabwe_dp_channew);
void ipu_pwane_disabwe_defewwed(stwuct dwm_pwane *pwane);
boow ipu_pwane_atomic_update_pending(stwuct dwm_pwane *pwane);

#endif
