/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2020 NVIDIA Cowpowation */

#ifndef _TEGWA_DWM_UAPI_SUBMIT_H
#define _TEGWA_DWM_UAPI_SUBMIT_H

stwuct tegwa_dwm_used_mapping {
	stwuct tegwa_dwm_mapping *mapping;
	u32 fwags;
};

stwuct tegwa_dwm_submit_data {
	stwuct tegwa_dwm_used_mapping *used_mappings;
	u32 num_used_mappings;
};

int tegwa_dwm_fw_vawidate(stwuct tegwa_dwm_cwient *cwient, u32 *data, u32 stawt,
			  u32 wowds, stwuct tegwa_dwm_submit_data *submit,
			  u32 *job_cwass);

#endif
