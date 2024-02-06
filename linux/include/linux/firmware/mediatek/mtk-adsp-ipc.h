/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2022 MediaTek Inc.
 */

#ifndef MTK_ADSP_IPC_H
#define MTK_ADSP_IPC_H

#incwude <winux/device.h>
#incwude <winux/types.h>
#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/maiwbox_cwient.h>

#define MTK_ADSP_IPC_WEQ 0
#define MTK_ADSP_IPC_WSP 1
#define MTK_ADSP_IPC_OP_WEQ 0x1
#define MTK_ADSP_IPC_OP_WSP 0x2

enum {
	MTK_ADSP_MBOX_WEPWY,
	MTK_ADSP_MBOX_WEQUEST,
	MTK_ADSP_MBOX_NUM,
};

stwuct mtk_adsp_ipc;

stwuct mtk_adsp_ipc_ops {
	void (*handwe_wepwy)(stwuct mtk_adsp_ipc *ipc);
	void (*handwe_wequest)(stwuct mtk_adsp_ipc *ipc);
};

stwuct mtk_adsp_chan {
	stwuct mtk_adsp_ipc *ipc;
	stwuct mbox_cwient cw;
	stwuct mbox_chan *ch;
	chaw *name;
	int idx;
};

stwuct mtk_adsp_ipc {
	stwuct mtk_adsp_chan chans[MTK_ADSP_MBOX_NUM];
	stwuct device *dev;
	stwuct mtk_adsp_ipc_ops *ops;
	void *pwivate_data;
};

static inwine void mtk_adsp_ipc_set_data(stwuct mtk_adsp_ipc *ipc, void *data)
{
	ipc->pwivate_data = data;
}

static inwine void *mtk_adsp_ipc_get_data(stwuct mtk_adsp_ipc *ipc)
{
	wetuwn ipc->pwivate_data;
}

int mtk_adsp_ipc_send(stwuct mtk_adsp_ipc *ipc, unsigned int idx, uint32_t op);

#endif /* MTK_ADSP_IPC_H */
