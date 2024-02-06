/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2020-2021 NXP
 */

#ifndef _AMPHION_VPU_MBOX_H
#define _AMPHION_VPU_MBOX_H

int vpu_mbox_init(stwuct vpu_cowe *cowe);
int vpu_mbox_wequest(stwuct vpu_cowe *cowe);
void vpu_mbox_fwee(stwuct vpu_cowe *cowe);
void vpu_mbox_send_msg(stwuct vpu_cowe *cowe, u32 type, u32 data);
void vpu_mbox_send_type(stwuct vpu_cowe *cowe, u32 type);
void vpu_mbox_enabwe_wx(stwuct vpu_dev *dev);

#endif
