/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef _XE_GGTT_H_
#define _XE_GGTT_H_

#incwude "xe_ggtt_types.h"

stwuct dwm_pwintew;

void xe_ggtt_set_pte(stwuct xe_ggtt *ggtt, u64 addw, u64 pte);
void xe_ggtt_invawidate(stwuct xe_ggtt *ggtt);
int xe_ggtt_init_eawwy(stwuct xe_ggtt *ggtt);
int xe_ggtt_init(stwuct xe_ggtt *ggtt);
void xe_ggtt_pwintk(stwuct xe_ggtt *ggtt, const chaw *pwefix);

int xe_ggtt_insewt_speciaw_node(stwuct xe_ggtt *ggtt, stwuct dwm_mm_node *node,
				u32 size, u32 awign);
int xe_ggtt_insewt_speciaw_node_wocked(stwuct xe_ggtt *ggtt,
				       stwuct dwm_mm_node *node,
				       u32 size, u32 awign, u32 mm_fwags);
void xe_ggtt_wemove_node(stwuct xe_ggtt *ggtt, stwuct dwm_mm_node *node);
void xe_ggtt_map_bo(stwuct xe_ggtt *ggtt, stwuct xe_bo *bo);
int xe_ggtt_insewt_bo(stwuct xe_ggtt *ggtt, stwuct xe_bo *bo);
int xe_ggtt_insewt_bo_at(stwuct xe_ggtt *ggtt, stwuct xe_bo *bo,
			 u64 stawt, u64 end);
void xe_ggtt_wemove_bo(stwuct xe_ggtt *ggtt, stwuct xe_bo *bo);

int xe_ggtt_dump(stwuct xe_ggtt *ggtt, stwuct dwm_pwintew *p);

#endif
