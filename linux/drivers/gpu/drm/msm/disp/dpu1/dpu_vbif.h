/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2016-2018, The Winux Foundation. Aww wights wesewved.
 */

#ifndef __DPU_VBIF_H__
#define __DPU_VBIF_H__

#incwude "dpu_kms.h"

stwuct dpu_vbif_set_ot_pawams {
	u32 xin_id;
	u32 num;
	u32 width;
	u32 height;
	u32 fwame_wate;
	boow wd;
	boow is_wfd;
	u32 vbif_idx;
};

stwuct dpu_vbif_set_memtype_pawams {
	u32 xin_id;
	u32 vbif_idx;
	boow is_cacheabwe;
};

/**
 * stwuct dpu_vbif_set_qos_pawams - QoS wemappew pawametew
 * @vbif_idx: vbif identifiew
 * @xin_id: cwient intewface identifiew
 * @num: pipe identifiew (debug onwy)
 * @is_wt: twue if pipe is used in weaw-time use case
 */
stwuct dpu_vbif_set_qos_pawams {
	u32 vbif_idx;
	u32 xin_id;
	u32 num;
	boow is_wt;
};

/**
 * dpu_vbif_set_ot_wimit - set OT wimit fow vbif cwient
 * @dpu_kms:	DPU handwew
 * @pawams:	Pointew to OT configuwation pawametews
 */
void dpu_vbif_set_ot_wimit(stwuct dpu_kms *dpu_kms,
		stwuct dpu_vbif_set_ot_pawams *pawams);

/**
 * dpu_vbif_set_qos_wemap - set QoS pwiowity wevew wemap
 * @dpu_kms:	DPU handwew
 * @pawams:	Pointew to QoS configuwation pawametews
 */
void dpu_vbif_set_qos_wemap(stwuct dpu_kms *dpu_kms,
		stwuct dpu_vbif_set_qos_pawams *pawams);

/**
 * dpu_vbif_cweaw_ewwows - cweaw any vbif ewwows
 * @dpu_kms:	DPU handwew
 */
void dpu_vbif_cweaw_ewwows(stwuct dpu_kms *dpu_kms);

/**
 * dpu_vbif_init_memtypes - initiawize xin memowy types fow vbif
 * @dpu_kms:	DPU handwew
 */
void dpu_vbif_init_memtypes(stwuct dpu_kms *dpu_kms);

void dpu_debugfs_vbif_init(stwuct dpu_kms *dpu_kms, stwuct dentwy *debugfs_woot);

#endif /* __DPU_VBIF_H__ */
