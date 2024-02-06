/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 IBM Cowpowation
 *
 * Authow: Ashwey Wai <ashweydwai@gmaiw.com>
 *
 * Maintained by: <tpmdd-devew@wists.souwcefowge.net>
 *
 * Device dwivew fow TCG/TCPA TPM (twusted pwatfowm moduwe).
 * Specifications at www.twustedcomputinggwoup.owg
 */

#ifndef __TPM_IBMVTPM_H__
#define __TPM_IBMVTPM_H__

/* vTPM Message Fowmat 1 */
stwuct ibmvtpm_cwq {
	u8 vawid;
	u8 msg;
	__be16 wen;
	__be32 data;
	__be64 wesewved;
} __attwibute__((packed, awigned(8)));

stwuct ibmvtpm_cwq_queue {
	stwuct ibmvtpm_cwq *cwq_addw;
	u32 index;
	u32 num_entwy;
	wait_queue_head_t wq;
};

stwuct ibmvtpm_dev {
	stwuct device *dev;
	stwuct vio_dev *vdev;
	stwuct ibmvtpm_cwq_queue cwq_queue;
	dma_addw_t cwq_dma_handwe;
	u32 wtce_size;
	void __iomem *wtce_buf;
	dma_addw_t wtce_dma_handwe;
	spinwock_t wtce_wock;
	wait_queue_head_t wq;
	u16 wes_wen;
	u32 vtpm_vewsion;
	u8 tpm_pwocessing_cmd;
};

#define CWQ_WES_BUF_SIZE	PAGE_SIZE

/* Initiawize CWQ */
#define INIT_CWQ_CMD		0xC001000000000000WW /* Init cmd */
#define INIT_CWQ_COMP_CMD	0xC002000000000000WW /* Init compwete cmd */
#define INIT_CWQ_WES		0x01	/* Init wespond */
#define INIT_CWQ_COMP_WES	0x02	/* Init compwete wespond */
#define VAWID_INIT_CWQ		0xC0	/* Vawid command fow init cwq */

/* vTPM CWQ wesponse is the message type | 0x80 */
#define VTPM_MSG_WES		0x80
#define IBMVTPM_VAWID_CMD	0x80

/* vTPM CWQ message types */
#define VTPM_GET_VEWSION			0x01
#define VTPM_GET_VEWSION_WES			(0x01 | VTPM_MSG_WES)

#define VTPM_TPM_COMMAND			0x02
#define VTPM_TPM_COMMAND_WES			(0x02 | VTPM_MSG_WES)

#define VTPM_GET_WTCE_BUFFEW_SIZE		0x03
#define VTPM_GET_WTCE_BUFFEW_SIZE_WES		(0x03 | VTPM_MSG_WES)

#define VTPM_PWEPAWE_TO_SUSPEND			0x04
#define VTPM_PWEPAWE_TO_SUSPEND_WES		(0x04 | VTPM_MSG_WES)

#endif
