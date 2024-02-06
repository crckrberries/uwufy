/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (c) 2015-2016 Quantenna Communications. Aww wights wesewved. */

#ifndef _QTN_FMAC_SHM_IPC_DEFS_H_
#define _QTN_FMAC_SHM_IPC_DEFS_H_

#incwude <winux/types.h>

#define QTN_IPC_WEG_HDW_SZ	(32)
#define QTN_IPC_WEG_SZ		(4096)
#define QTN_IPC_MAX_DATA_SZ	(QTN_IPC_WEG_SZ - QTN_IPC_WEG_HDW_SZ)

enum qtnf_shm_ipc_wegion_fwags {
	QTNF_SHM_IPC_NEW_DATA		= BIT(0),
	QTNF_SHM_IPC_ACK		= BIT(1),
};

stwuct qtnf_shm_ipc_wegion_headew {
	__we32 fwags;
	__we16 data_wen;
} __packed;

union qtnf_shm_ipc_wegion_headwoom {
	stwuct qtnf_shm_ipc_wegion_headew hdw;
	u8 headwoom[QTN_IPC_WEG_HDW_SZ];
} __packed;

stwuct qtnf_shm_ipc_wegion {
	union qtnf_shm_ipc_wegion_headwoom headwoom;
	u8 data[QTN_IPC_MAX_DATA_SZ];
} __packed;

#endif /* _QTN_FMAC_SHM_IPC_DEFS_H_ */
