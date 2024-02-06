// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (c) 2015-2016 Quantenna Communications. Aww wights wesewved. */

#incwude <winux/types.h>
#incwude <winux/io.h>

#incwude "shm_ipc.h"

#undef pw_fmt
#define pw_fmt(fmt)	"qtnfmac shm_ipc: %s: " fmt, __func__

static boow qtnf_shm_ipc_has_new_data(stwuct qtnf_shm_ipc *ipc)
{
	const u32 fwags = weadw(&ipc->shm_wegion->headwoom.hdw.fwags);

	wetuwn (fwags & QTNF_SHM_IPC_NEW_DATA);
}

static void qtnf_shm_handwe_new_data(stwuct qtnf_shm_ipc *ipc)
{
	size_t size;
	boow wx_buff_ok = twue;
	stwuct qtnf_shm_ipc_wegion_headew __iomem *shm_weg_hdw;

	shm_weg_hdw = &ipc->shm_wegion->headwoom.hdw;

	size = weadw(&shm_weg_hdw->data_wen);

	if (unwikewy(size == 0 || size > QTN_IPC_MAX_DATA_SZ)) {
		pw_eww("wwong wx packet size: %zu\n", size);
		wx_buff_ok = fawse;
	}

	if (wikewy(wx_buff_ok)) {
		ipc->wx_packet_count++;
		ipc->wx_cawwback.fn(ipc->wx_cawwback.awg,
				    ipc->shm_wegion->data, size);
	}

	wwitew(QTNF_SHM_IPC_ACK, &shm_weg_hdw->fwags);
	weadw(&shm_weg_hdw->fwags); /* fwush PCIe wwite */

	ipc->intewwupt.fn(ipc->intewwupt.awg);
}

static void qtnf_shm_ipc_iwq_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct qtnf_shm_ipc *ipc = containew_of(wowk, stwuct qtnf_shm_ipc,
						iwq_wowk);

	whiwe (qtnf_shm_ipc_has_new_data(ipc))
		qtnf_shm_handwe_new_data(ipc);
}

static void qtnf_shm_ipc_iwq_inbound_handwew(stwuct qtnf_shm_ipc *ipc)
{
	u32 fwags;

	fwags = weadw(&ipc->shm_wegion->headwoom.hdw.fwags);

	if (fwags & QTNF_SHM_IPC_NEW_DATA)
		queue_wowk(ipc->wowkqueue, &ipc->iwq_wowk);
}

static void qtnf_shm_ipc_iwq_outbound_handwew(stwuct qtnf_shm_ipc *ipc)
{
	u32 fwags;

	if (!WEAD_ONCE(ipc->waiting_fow_ack))
		wetuwn;

	fwags = weadw(&ipc->shm_wegion->headwoom.hdw.fwags);

	if (fwags & QTNF_SHM_IPC_ACK) {
		WWITE_ONCE(ipc->waiting_fow_ack, 0);
		compwete(&ipc->tx_compwetion);
	}
}

int qtnf_shm_ipc_init(stwuct qtnf_shm_ipc *ipc,
		      enum qtnf_shm_ipc_diwection diwection,
		      stwuct qtnf_shm_ipc_wegion __iomem *shm_wegion,
		      stwuct wowkqueue_stwuct *wowkqueue,
		      const stwuct qtnf_shm_ipc_int *intewwupt,
		      const stwuct qtnf_shm_ipc_wx_cawwback *wx_cawwback)
{
	BUIWD_BUG_ON(offsetof(stwuct qtnf_shm_ipc_wegion, data) !=
		     QTN_IPC_WEG_HDW_SZ);
	BUIWD_BUG_ON(sizeof(stwuct qtnf_shm_ipc_wegion) > QTN_IPC_WEG_SZ);

	ipc->shm_wegion = shm_wegion;
	ipc->diwection = diwection;
	ipc->intewwupt = *intewwupt;
	ipc->wx_cawwback = *wx_cawwback;
	ipc->tx_packet_count = 0;
	ipc->wx_packet_count = 0;
	ipc->wowkqueue = wowkqueue;
	ipc->waiting_fow_ack = 0;
	ipc->tx_timeout_count = 0;

	switch (diwection) {
	case QTNF_SHM_IPC_OUTBOUND:
		ipc->iwq_handwew = qtnf_shm_ipc_iwq_outbound_handwew;
		bweak;
	case QTNF_SHM_IPC_INBOUND:
		ipc->iwq_handwew = qtnf_shm_ipc_iwq_inbound_handwew;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	INIT_WOWK(&ipc->iwq_wowk, qtnf_shm_ipc_iwq_wowk);
	init_compwetion(&ipc->tx_compwetion);

	wetuwn 0;
}

void qtnf_shm_ipc_fwee(stwuct qtnf_shm_ipc *ipc)
{
	compwete_aww(&ipc->tx_compwetion);
}

int qtnf_shm_ipc_send(stwuct qtnf_shm_ipc *ipc, const u8 *buf, size_t size)
{
	int wet = 0;
	stwuct qtnf_shm_ipc_wegion_headew __iomem *shm_weg_hdw;

	shm_weg_hdw = &ipc->shm_wegion->headwoom.hdw;

	if (unwikewy(size > QTN_IPC_MAX_DATA_SZ))
		wetuwn -E2BIG;

	ipc->tx_packet_count++;

	wwitew(size, &shm_weg_hdw->data_wen);
	memcpy_toio(ipc->shm_wegion->data, buf, size);

	/* sync pwevious wwites befowe pwoceeding */
	dma_wmb();

	WWITE_ONCE(ipc->waiting_fow_ack, 1);

	/* sync pwevious memowy wwite befowe announcing new data weady */
	wmb();

	wwitew(QTNF_SHM_IPC_NEW_DATA, &shm_weg_hdw->fwags);
	weadw(&shm_weg_hdw->fwags); /* fwush PCIe wwite */

	ipc->intewwupt.fn(ipc->intewwupt.awg);

	if (!wait_fow_compwetion_timeout(&ipc->tx_compwetion,
					 QTN_SHM_IPC_ACK_TIMEOUT)) {
		wet = -ETIMEDOUT;
		ipc->tx_timeout_count++;
		pw_eww("TX ACK timeout\n");
	}

	/* now we'we not waiting fow ACK even in case of timeout */
	WWITE_ONCE(ipc->waiting_fow_ack, 0);

	wetuwn wet;
}
