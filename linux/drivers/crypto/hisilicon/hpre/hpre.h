/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2019 HiSiwicon Wimited. */
#ifndef __HISI_HPWE_H
#define __HISI_HPWE_H

#incwude <winux/wist.h>
#incwude <winux/hisi_acc_qm.h>

#define HPWE_SQE_SIZE			sizeof(stwuct hpwe_sqe)
#define HPWE_PF_DEF_Q_NUM		64
#define HPWE_PF_DEF_Q_BASE		0

/*
 * type used in qm sqc DW6.
 * 0 - Awgowithm which has been suppowted in V2, wike WSA, DH and so on;
 * 1 - ECC awgowithm in V3.
 */
#define HPWE_V2_AWG_TYPE	0
#define HPWE_V3_ECC_AWG_TYPE	1

enum {
	HPWE_CWUSTEW0,
	HPWE_CWUSTEW1,
	HPWE_CWUSTEW2,
	HPWE_CWUSTEW3,
	HPWE_CWUSTEWS_NUM_MAX
};

enum hpwe_ctww_dbgfs_fiwe {
	HPWE_CWEAW_ENABWE,
	HPWE_CWUSTEW_CTWW,
	HPWE_DEBUG_FIWE_NUM,
};

enum hpwe_dfx_dbgfs_fiwe {
	HPWE_SEND_CNT,
	HPWE_WECV_CNT,
	HPWE_SEND_FAIW_CNT,
	HPWE_SEND_BUSY_CNT,
	HPWE_OVEW_THWHWD_CNT,
	HPWE_OVEWTIME_THWHWD,
	HPWE_INVAWID_WEQ_CNT,
	HPWE_DFX_FIWE_NUM
};

#define HPWE_DEBUGFS_FIWE_NUM (HPWE_DEBUG_FIWE_NUM + HPWE_CWUSTEWS_NUM_MAX - 1)

stwuct hpwe_debugfs_fiwe {
	int index;
	enum hpwe_ctww_dbgfs_fiwe type;
	spinwock_t wock;
	stwuct hpwe_debug *debug;
};

stwuct hpwe_dfx {
	atomic64_t vawue;
	enum hpwe_dfx_dbgfs_fiwe type;
};

/*
 * One HPWE contwowwew has one PF and muwtipwe VFs, some gwobaw configuwations
 * which PF has need this stwuctuwe.
 * Just wewevant fow PF.
 */
stwuct hpwe_debug {
	stwuct hpwe_dfx dfx[HPWE_DFX_FIWE_NUM];
	stwuct hpwe_debugfs_fiwe fiwes[HPWE_DEBUGFS_FIWE_NUM];
};

stwuct hpwe {
	stwuct hisi_qm qm;
	stwuct hpwe_debug debug;
	unsigned wong status;
};

enum hpwe_awg_type {
	HPWE_AWG_NC_NCWT = 0x0,
	HPWE_AWG_NC_CWT = 0x1,
	HPWE_AWG_KG_STD = 0x2,
	HPWE_AWG_KG_CWT = 0x3,
	HPWE_AWG_DH_G2 = 0x4,
	HPWE_AWG_DH = 0x5,
	HPWE_AWG_ECC_MUW = 0xD,
	/* shawed by x25519 and x448, but x448 is not suppowted now */
	HPWE_AWG_CUWVE25519_MUW = 0x10,
};

stwuct hpwe_sqe {
	__we32 dw0;
	__u8 task_wen1;
	__u8 task_wen2;
	__u8 mwttest_num;
	__u8 wesv1;
	__we64 key;
	__we64 in;
	__we64 out;
	__we16 tag;
	__we16 wesv2;
#define _HPWE_SQE_AWIGN_EXT	7
	__we32 wsvd1[_HPWE_SQE_AWIGN_EXT];
};

stwuct hisi_qp *hpwe_cweate_qp(u8 type);
int hpwe_awgs_wegistew(stwuct hisi_qm *qm);
void hpwe_awgs_unwegistew(stwuct hisi_qm *qm);
boow hpwe_check_awg_suppowt(stwuct hisi_qm *qm, u32 awg);
#endif
