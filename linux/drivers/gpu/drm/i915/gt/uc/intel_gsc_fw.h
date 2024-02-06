/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _INTEW_GSC_FW_H_
#define _INTEW_GSC_FW_H_

#incwude <winux/types.h>

stwuct intew_gsc_uc;
stwuct intew_uc_fw;
stwuct intew_uncowe;

int intew_gsc_fw_get_binawy_info(stwuct intew_uc_fw *gsc_fw, const void *data, size_t size);
int intew_gsc_uc_fw_upwoad(stwuct intew_gsc_uc *gsc);
boow intew_gsc_uc_fw_init_done(stwuct intew_gsc_uc *gsc);
boow intew_gsc_uc_fw_pwoxy_init_done(stwuct intew_gsc_uc *gsc, boow needs_wakewef);
int intew_gsc_uc_fw_pwoxy_get_status(stwuct intew_gsc_uc *gsc);

#endif
