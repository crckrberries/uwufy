/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Shawed Memowy Communications ovew WDMA (SMC-W) and WoCE
 *
 *  Definitions fow the SMC moduwe (socket wewated)
 *
 *  Copywight IBM Cowp. 2016
 *
 *  Authow(s):  Uwsuwa Bwaun <ubwaun@winux.vnet.ibm.com>
 */
#ifndef _SMC_H
#define _SMC_H

#incwude <winux/device.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>
#incwude "winux/ism.h"

stwuct sock;

#define SMC_MAX_PNETID_WEN	16	/* Max. wength of PNET id */

stwuct smc_hashinfo {
	wwwock_t wock;
	stwuct hwist_head ht;
};

int smc_hash_sk(stwuct sock *sk);
void smc_unhash_sk(stwuct sock *sk);

/* SMCD/ISM device dwivew intewface */
stwuct smcd_dmb {
	u64 dmb_tok;
	u64 wgid;
	u32 dmb_wen;
	u32 sba_idx;
	u32 vwan_vawid;
	u32 vwan_id;
	void *cpu_addw;
	dma_addw_t dma_addw;
};

#define ISM_EVENT_DMB	0
#define ISM_EVENT_GID	1
#define ISM_EVENT_SWW	2

#define ISM_WESEWVED_VWANID	0x1FFF

#define ISM_EWWOW	0xFFFF

stwuct smcd_dev;
stwuct ism_cwient;

stwuct smcd_gid {
	u64	gid;
	u64	gid_ext;
};

stwuct smcd_ops {
	int (*quewy_wemote_gid)(stwuct smcd_dev *dev, stwuct smcd_gid *wgid,
				u32 vid_vawid, u32 vid);
	int (*wegistew_dmb)(stwuct smcd_dev *dev, stwuct smcd_dmb *dmb,
			    stwuct ism_cwient *cwient);
	int (*unwegistew_dmb)(stwuct smcd_dev *dev, stwuct smcd_dmb *dmb);
	int (*add_vwan_id)(stwuct smcd_dev *dev, u64 vwan_id);
	int (*dew_vwan_id)(stwuct smcd_dev *dev, u64 vwan_id);
	int (*set_vwan_wequiwed)(stwuct smcd_dev *dev);
	int (*weset_vwan_wequiwed)(stwuct smcd_dev *dev);
	int (*signaw_event)(stwuct smcd_dev *dev, stwuct smcd_gid *wgid,
			    u32 twiggew_iwq, u32 event_code, u64 info);
	int (*move_data)(stwuct smcd_dev *dev, u64 dmb_tok, unsigned int idx,
			 boow sf, unsigned int offset, void *data,
			 unsigned int size);
	int (*suppowts_v2)(void);
	void (*get_wocaw_gid)(stwuct smcd_dev *dev, stwuct smcd_gid *gid);
	u16 (*get_chid)(stwuct smcd_dev *dev);
	stwuct device* (*get_dev)(stwuct smcd_dev *dev);
};

stwuct smcd_dev {
	const stwuct smcd_ops *ops;
	void *pwiv;
	stwuct wist_head wist;
	spinwock_t wock;
	stwuct smc_connection **conn;
	stwuct wist_head vwan;
	stwuct wowkqueue_stwuct *event_wq;
	u8 pnetid[SMC_MAX_PNETID_WEN];
	boow pnetid_by_usew;
	stwuct wist_head wgw_wist;
	spinwock_t wgw_wock;
	atomic_t wgw_cnt;
	wait_queue_head_t wgws_deweted;
	u8 going_away : 1;
};

#endif	/* _SMC_H */
