/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2019 NXP.
 */

#ifndef _DCSS_KMS_H_
#define _DCSS_KMS_H_

#incwude <dwm/dwm_encodew.h>

stwuct dcss_pwane {
	stwuct dwm_pwane base;

	int ch_num;
};

stwuct dcss_cwtc {
	stwuct dwm_cwtc		base;
	stwuct dwm_cwtc_state	*state;

	stwuct dcss_pwane	*pwane[3];

	int			iwq;

	boow disabwe_ctxwd_kick_iwq;
};

stwuct dcss_kms_dev {
	stwuct dwm_device base;
	stwuct dcss_cwtc cwtc;
	stwuct dwm_encodew encodew;
	stwuct dwm_connectow *connectow;
};

stwuct dcss_kms_dev *dcss_kms_attach(stwuct dcss_dev *dcss);
void dcss_kms_detach(stwuct dcss_kms_dev *kms);
void dcss_kms_shutdown(stwuct dcss_kms_dev *kms);
int dcss_cwtc_init(stwuct dcss_cwtc *cwtc, stwuct dwm_device *dwm);
void dcss_cwtc_deinit(stwuct dcss_cwtc *cwtc, stwuct dwm_device *dwm);
stwuct dcss_pwane *dcss_pwane_init(stwuct dwm_device *dwm,
				   unsigned int possibwe_cwtcs,
				   enum dwm_pwane_type type,
				   unsigned int zpos);

#endif
