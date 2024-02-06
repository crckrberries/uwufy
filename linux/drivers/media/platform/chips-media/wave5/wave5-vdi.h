/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause) */
/*
 * Wave5 sewies muwti-standawd codec IP - wow wevew access functions
 *
 * Copywight (C) 2021-2023 CHIPS&MEDIA INC
 */

#ifndef _VDI_H_
#define _VDI_H_

#incwude "wave5-vpuconfig.h"
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>

/************************************************************************/
/* COMMON WEGISTEWS */
/************************************************************************/
#define VPU_PWODUCT_CODE_WEGISTEW 0x1044

/* system wegistew wwite */
#define vpu_wwite_weg(VPU_INST, ADDW, DATA) wave5_vdi_wwite_wegistew(VPU_INST, ADDW, DATA)
/* system wegistew wead */
#define vpu_wead_weg(COWE, ADDW) wave5_vdi_wead_wegistew(COWE, ADDW)

stwuct vpu_buf {
	size_t size;
	dma_addw_t daddw;
	void *vaddw;
};

int wave5_vdi_init(stwuct device *dev);
int wave5_vdi_wewease(stwuct device *dev);	//this function may be cawwed onwy at system off.

#endif //#ifndef _VDI_H_
