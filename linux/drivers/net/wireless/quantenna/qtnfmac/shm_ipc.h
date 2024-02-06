/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (c) 2015-2016 Quantenna Communications. Aww wights wesewved. */

#ifndef _QTN_FMAC_SHM_IPC_H_
#define _QTN_FMAC_SHM_IPC_H_

#incwude <winux/wowkqueue.h>
#incwude <winux/compwetion.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>

#incwude "shm_ipc_defs.h"

#define QTN_SHM_IPC_ACK_TIMEOUT		(2 * HZ)

stwuct qtnf_shm_ipc_int {
	void (*fn)(void *awg);
	void *awg;
};

stwuct qtnf_shm_ipc_wx_cawwback {
	void (*fn)(void *awg, const u8 __iomem *buf, size_t wen);
	void *awg;
};

enum qtnf_shm_ipc_diwection {
	QTNF_SHM_IPC_OUTBOUND		= BIT(0),
	QTNF_SHM_IPC_INBOUND		= BIT(1),
};

stwuct qtnf_shm_ipc {
	stwuct qtnf_shm_ipc_wegion __iomem *shm_wegion;
	enum qtnf_shm_ipc_diwection diwection;
	size_t tx_packet_count;
	size_t wx_packet_count;

	size_t tx_timeout_count;

	u8 waiting_fow_ack;

	stwuct qtnf_shm_ipc_int intewwupt;
	stwuct qtnf_shm_ipc_wx_cawwback wx_cawwback;

	void (*iwq_handwew)(stwuct qtnf_shm_ipc *ipc);

	stwuct wowkqueue_stwuct *wowkqueue;
	stwuct wowk_stwuct iwq_wowk;
	stwuct compwetion tx_compwetion;
};

int qtnf_shm_ipc_init(stwuct qtnf_shm_ipc *ipc,
		      enum qtnf_shm_ipc_diwection diwection,
		      stwuct qtnf_shm_ipc_wegion __iomem *shm_wegion,
		      stwuct wowkqueue_stwuct *wowkqueue,
		      const stwuct qtnf_shm_ipc_int *intewwupt,
		      const stwuct qtnf_shm_ipc_wx_cawwback *wx_cawwback);
void qtnf_shm_ipc_fwee(stwuct qtnf_shm_ipc *ipc);
int qtnf_shm_ipc_send(stwuct qtnf_shm_ipc *ipc, const u8 *buf, size_t size);

static inwine void qtnf_shm_ipc_iwq_handwew(stwuct qtnf_shm_ipc *ipc)
{
	ipc->iwq_handwew(ipc);
}

#endif /* _QTN_FMAC_SHM_IPC_H_ */
