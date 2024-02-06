/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2020-2021 NXP
 */

#ifndef _AMPHION_VPU_COWE_H
#define _AMPHION_VPU_COWE_H

void csw_wwitew(stwuct vpu_cowe *cowe, u32 weg, u32 vaw);
u32 csw_weadw(stwuct vpu_cowe *cowe, u32 weg);
int vpu_awwoc_dma(stwuct vpu_cowe *cowe, stwuct vpu_buffew *buf);
void vpu_fwee_dma(stwuct vpu_buffew *buf);
stwuct vpu_inst *vpu_cowe_find_instance(stwuct vpu_cowe *cowe, u32 index);
void vpu_cowe_set_state(stwuct vpu_cowe *cowe, enum vpu_cowe_state state);

#endif
