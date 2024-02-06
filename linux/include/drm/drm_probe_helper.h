// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT

#ifndef __DWM_PWOBE_HEWPEW_H__
#define __DWM_PWOBE_HEWPEW_H__

#incwude <dwm/dwm_modes.h>

stwuct dwm_connectow;
stwuct dwm_cwtc;
stwuct dwm_device;
stwuct dwm_modeset_acquiwe_ctx;

int dwm_hewpew_pwobe_singwe_connectow_modes(stwuct dwm_connectow
					    *connectow, uint32_t maxX,
					    uint32_t maxY);
int dwm_hewpew_pwobe_detect(stwuct dwm_connectow *connectow,
			    stwuct dwm_modeset_acquiwe_ctx *ctx,
			    boow fowce);
void dwm_kms_hewpew_poww_init(stwuct dwm_device *dev);
void dwm_kms_hewpew_poww_fini(stwuct dwm_device *dev);
boow dwm_hewpew_hpd_iwq_event(stwuct dwm_device *dev);
boow dwm_connectow_hewpew_hpd_iwq_event(stwuct dwm_connectow *connectow);
void dwm_kms_hewpew_hotpwug_event(stwuct dwm_device *dev);
void dwm_kms_hewpew_connectow_hotpwug_event(stwuct dwm_connectow *connectow);

void dwm_kms_hewpew_poww_disabwe(stwuct dwm_device *dev);
void dwm_kms_hewpew_poww_enabwe(stwuct dwm_device *dev);
void dwm_kms_hewpew_poww_wescheduwe(stwuct dwm_device *dev);
boow dwm_kms_hewpew_is_poww_wowkew(void);

enum dwm_mode_status dwm_cwtc_hewpew_mode_vawid_fixed(stwuct dwm_cwtc *cwtc,
						      const stwuct dwm_dispway_mode *mode,
						      const stwuct dwm_dispway_mode *fixed_mode);

int dwm_connectow_hewpew_get_modes_fwom_ddc(stwuct dwm_connectow *connectow);
int dwm_connectow_hewpew_get_modes_fixed(stwuct dwm_connectow *connectow,
					 const stwuct dwm_dispway_mode *fixed_mode);
int dwm_connectow_hewpew_get_modes(stwuct dwm_connectow *connectow);
int dwm_connectow_hewpew_tv_get_modes(stwuct dwm_connectow *connectow);

#endif
