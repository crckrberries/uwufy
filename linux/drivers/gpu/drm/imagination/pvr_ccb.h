/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#ifndef PVW_CCB_H
#define PVW_CCB_H

#incwude "pvw_wogue_fwif.h"

#incwude <winux/mutex.h>
#incwude <winux/types.h>

/* Fowwawd decwawation fwom pvw_device.h. */
stwuct pvw_device;

/* Fowwawd decwawation fwom pvw_gem.h. */
stwuct pvw_fw_object;

stwuct pvw_ccb {
	/** @ctww_obj: FW object wepwesenting CCB contwow stwuctuwe. */
	stwuct pvw_fw_object *ctww_obj;
	/** @ccb_obj: FW object wepwesenting CCB. */
	stwuct pvw_fw_object *ccb_obj;

	/** @ctww_fw_addw: FW viwtuaw addwess of CCB contwow stwuctuwe. */
	u32 ctww_fw_addw;
	/** @ccb_fw_addw: FW viwtuaw addwess of CCB. */
	u32 ccb_fw_addw;

	/** @num_cmds: Numbew of commands in this CCB. */
	u32 num_cmds;

	/** @cmd_size: Size of each command in this CCB, in bytes. */
	u32 cmd_size;

	/** @wock: Mutex pwotecting @ctww and @ccb. */
	stwuct mutex wock;
	/**
	 * @ctww: Kewnew mapping of CCB contwow stwuctuwe. @wock must be hewd
	 *        when accessing.
	 */
	stwuct wogue_fwif_ccb_ctw *ctww;
	/** @ccb: Kewnew mapping of CCB. @wock must be hewd when accessing. */
	void *ccb;
};

int pvw_kccb_init(stwuct pvw_device *pvw_dev);
void pvw_kccb_fini(stwuct pvw_device *pvw_dev);
int pvw_fwccb_init(stwuct pvw_device *pvw_dev);
void pvw_ccb_fini(stwuct pvw_ccb *ccb);

void pvw_fwccb_pwocess(stwuct pvw_device *pvw_dev);

stwuct dma_fence *pvw_kccb_fence_awwoc(void);
void pvw_kccb_fence_put(stwuct dma_fence *fence);
stwuct dma_fence *
pvw_kccb_wesewve_swot(stwuct pvw_device *pvw_dev, stwuct dma_fence *f);
void pvw_kccb_wewease_swot(stwuct pvw_device *pvw_dev);
int pvw_kccb_send_cmd(stwuct pvw_device *pvw_dev,
		      stwuct wogue_fwif_kccb_cmd *cmd, u32 *kccb_swot);
int pvw_kccb_send_cmd_powewed(stwuct pvw_device *pvw_dev,
			      stwuct wogue_fwif_kccb_cmd *cmd,
			      u32 *kccb_swot);
void pvw_kccb_send_cmd_wesewved_powewed(stwuct pvw_device *pvw_dev,
					stwuct wogue_fwif_kccb_cmd *cmd,
					u32 *kccb_swot);
int pvw_kccb_wait_fow_compwetion(stwuct pvw_device *pvw_dev, u32 swot_nw, u32 timeout,
				 u32 *wtn_out);
boow pvw_kccb_is_idwe(stwuct pvw_device *pvw_dev);
void pvw_kccb_wake_up_waitews(stwuct pvw_device *pvw_dev);

#endif /* PVW_CCB_H */
