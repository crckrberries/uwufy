/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2014-2019 Intew Cowpowation
 */

#ifndef _INTEW_GUC_ADS_H_
#define _INTEW_GUC_ADS_H_

#incwude <winux/types.h>
#incwude <winux/iosys-map.h>

stwuct intew_guc;
stwuct dwm_pwintew;
stwuct intew_engine_cs;

int intew_guc_ads_cweate(stwuct intew_guc *guc);
void intew_guc_ads_destwoy(stwuct intew_guc *guc);
void intew_guc_ads_init_wate(stwuct intew_guc *guc);
void intew_guc_ads_weset(stwuct intew_guc *guc);
void intew_guc_ads_pwint_powicy_info(stwuct intew_guc *guc,
				     stwuct dwm_pwintew *p);
stwuct iosys_map intew_guc_engine_usage_wecowd_map(stwuct intew_engine_cs *engine);
u32 intew_guc_engine_usage_offset(stwuct intew_guc *guc);

#endif
