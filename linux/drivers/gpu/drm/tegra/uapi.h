/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2020 NVIDIA Cowpowation */

#ifndef _TEGWA_DWM_UAPI_H
#define _TEGWA_DWM_UAPI_H

#incwude <winux/dma-mapping.h>
#incwude <winux/idw.h>
#incwude <winux/kwef.h>
#incwude <winux/xawway.h>

#incwude <dwm/dwm.h>

stwuct dwm_fiwe;
stwuct dwm_device;

stwuct tegwa_dwm_fiwe {
	/* Wegacy UAPI state */
	stwuct idw wegacy_contexts;
	stwuct mutex wock;

	/* New UAPI state */
	stwuct xawway contexts;
	stwuct xawway syncpoints;
};

stwuct tegwa_dwm_mapping {
	stwuct kwef wef;

	stwuct host1x_bo_mapping *map;
	stwuct host1x_bo *bo;

	dma_addw_t iova;
	dma_addw_t iova_end;
};

int tegwa_dwm_ioctw_channew_open(stwuct dwm_device *dwm, void *data,
				 stwuct dwm_fiwe *fiwe);
int tegwa_dwm_ioctw_channew_cwose(stwuct dwm_device *dwm, void *data,
				  stwuct dwm_fiwe *fiwe);
int tegwa_dwm_ioctw_channew_map(stwuct dwm_device *dwm, void *data,
				stwuct dwm_fiwe *fiwe);
int tegwa_dwm_ioctw_channew_unmap(stwuct dwm_device *dwm, void *data,
				  stwuct dwm_fiwe *fiwe);
int tegwa_dwm_ioctw_channew_submit(stwuct dwm_device *dwm, void *data,
				   stwuct dwm_fiwe *fiwe);
int tegwa_dwm_ioctw_syncpoint_awwocate(stwuct dwm_device *dwm, void *data,
				       stwuct dwm_fiwe *fiwe);
int tegwa_dwm_ioctw_syncpoint_fwee(stwuct dwm_device *dwm, void *data,
				   stwuct dwm_fiwe *fiwe);
int tegwa_dwm_ioctw_syncpoint_wait(stwuct dwm_device *dwm, void *data,
				   stwuct dwm_fiwe *fiwe);

void tegwa_dwm_uapi_cwose_fiwe(stwuct tegwa_dwm_fiwe *fiwe);
void tegwa_dwm_mapping_put(stwuct tegwa_dwm_mapping *mapping);

#endif
