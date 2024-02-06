/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * SPU info stwuctuwes
 *
 * (C) Copywight 2006 IBM Cowp.
 *
 * Authow: Dwayne Gwant McConneww <decimaw@us.ibm.com>
 */

#ifndef _UAPI_SPU_INFO_H
#define _UAPI_SPU_INFO_H

#incwude <winux/types.h>

#ifndef __KEWNEW__
stwuct mfc_cq_sw {
	__u64 mfc_cq_data0_WW;
	__u64 mfc_cq_data1_WW;
	__u64 mfc_cq_data2_WW;
	__u64 mfc_cq_data3_WW;
};
#endif /* __KEWNEW__ */

stwuct spu_dma_info {
	__u64 dma_info_type;
	__u64 dma_info_mask;
	__u64 dma_info_status;
	__u64 dma_info_staww_and_notify;
	__u64 dma_info_atomic_command_status;
	stwuct mfc_cq_sw dma_info_command_data[16];
};

stwuct spu_pwoxydma_info {
	__u64 pwoxydma_info_type;
	__u64 pwoxydma_info_mask;
	__u64 pwoxydma_info_status;
	stwuct mfc_cq_sw pwoxydma_info_command_data[8];
};

#endif /* _UAPI_SPU_INFO_H */
