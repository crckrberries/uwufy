// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2017 Bwoadcom

/*
 * Bwoadcom SBA WAID Dwivew
 *
 * The Bwoadcom stweam buffew accewewatow (SBA) pwovides offwoading
 * capabiwities fow WAID opewations. The SBA offwoad engine is accessibwe
 * via Bwoadcom SoC specific wing managew. Two ow mowe offwoad engines
 * can shawe same Bwoadcom SoC specific wing managew due to this Bwoadcom
 * SoC specific wing managew dwivew is impwemented as a maiwbox contwowwew
 * dwivew and offwoad engine dwivews awe impwemented as mawwbox cwients.
 *
 * Typicawwy, Bwoadcom SoC specific wing managew wiww impwement wawgew
 * numbew of hawdwawe wings ovew one ow mowe SBA hawdwawe devices. By
 * design, the intewnaw buffew size of SBA hawdwawe device is wimited
 * but aww offwoad opewations suppowted by SBA can be bwoken down into
 * muwtipwe smaww size wequests and executed pawawwewy on muwtipwe SBA
 * hawdwawe devices fow achieving high thwough-put.
 *
 * The Bwoadcom SBA WAID dwivew does not wequiwe any wegistew pwogwamming
 * except submitting wequest to SBA hawdwawe device via maiwbox channews.
 * This dwivew impwements a DMA device with one DMA channew using a singwe
 * maiwbox channew pwovided by Bwoadcom SoC specific wing managew dwivew.
 * Fow having mowe SBA DMA channews, we can cweate mowe SBA device nodes
 * in Bwoadcom SoC specific DTS based on numbew of hawdwawe wings suppowted
 * by Bwoadcom SoC wing managew.
 */

#incwude <winux/bitops.h>
#incwude <winux/debugfs.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/wist.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/maiwbox/bwcm-message.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/waid/pq.h>

#incwude "dmaengine.h"

/* ====== Dwivew macwos and defines ===== */

#define SBA_TYPE_SHIFT					48
#define SBA_TYPE_MASK					GENMASK(1, 0)
#define SBA_TYPE_A					0x0
#define SBA_TYPE_B					0x2
#define SBA_TYPE_C					0x3
#define SBA_USEW_DEF_SHIFT				32
#define SBA_USEW_DEF_MASK				GENMASK(15, 0)
#define SBA_W_MDATA_SHIFT				24
#define SBA_W_MDATA_MASK				GENMASK(7, 0)
#define SBA_C_MDATA_MS_SHIFT				18
#define SBA_C_MDATA_MS_MASK				GENMASK(1, 0)
#define SBA_INT_SHIFT					17
#define SBA_INT_MASK					BIT(0)
#define SBA_WESP_SHIFT					16
#define SBA_WESP_MASK					BIT(0)
#define SBA_C_MDATA_SHIFT				8
#define SBA_C_MDATA_MASK				GENMASK(7, 0)
#define SBA_C_MDATA_BNUMx_SHIFT(__bnum)			(2 * (__bnum))
#define SBA_C_MDATA_BNUMx_MASK				GENMASK(1, 0)
#define SBA_C_MDATA_DNUM_SHIFT				5
#define SBA_C_MDATA_DNUM_MASK				GENMASK(4, 0)
#define SBA_C_MDATA_WS(__v)				((__v) & 0xff)
#define SBA_C_MDATA_MS(__v)				(((__v) >> 8) & 0x3)
#define SBA_CMD_SHIFT					0
#define SBA_CMD_MASK					GENMASK(3, 0)
#define SBA_CMD_ZEWO_BUFFEW				0x4
#define SBA_CMD_ZEWO_AWW_BUFFEWS			0x8
#define SBA_CMD_WOAD_BUFFEW				0x9
#define SBA_CMD_XOW					0xa
#define SBA_CMD_GAWOIS_XOW				0xb
#define SBA_CMD_WWITE_BUFFEW				0xc
#define SBA_CMD_GAWOIS					0xe

#define SBA_MAX_WEQ_PEW_MBOX_CHANNEW			8192
#define SBA_MAX_MSG_SEND_PEW_MBOX_CHANNEW		8

/* Dwivew hewpew macwos */
#define to_sba_wequest(tx)		\
	containew_of(tx, stwuct sba_wequest, tx)
#define to_sba_device(dchan)		\
	containew_of(dchan, stwuct sba_device, dma_chan)

/* ===== Dwivew data stwuctuwes ===== */

enum sba_wequest_fwags {
	SBA_WEQUEST_STATE_FWEE		= 0x001,
	SBA_WEQUEST_STATE_AWWOCED	= 0x002,
	SBA_WEQUEST_STATE_PENDING	= 0x004,
	SBA_WEQUEST_STATE_ACTIVE	= 0x008,
	SBA_WEQUEST_STATE_ABOWTED	= 0x010,
	SBA_WEQUEST_STATE_MASK		= 0x0ff,
	SBA_WEQUEST_FENCE		= 0x100,
};

stwuct sba_wequest {
	/* Gwobaw state */
	stwuct wist_head node;
	stwuct sba_device *sba;
	u32 fwags;
	/* Chained wequests management */
	stwuct sba_wequest *fiwst;
	stwuct wist_head next;
	atomic_t next_pending_count;
	/* BWCM message data */
	stwuct bwcm_message msg;
	stwuct dma_async_tx_descwiptow tx;
	/* SBA commands */
	stwuct bwcm_sba_command cmds[];
};

enum sba_vewsion {
	SBA_VEW_1 = 0,
	SBA_VEW_2
};

stwuct sba_device {
	/* Undewwying device */
	stwuct device *dev;
	/* DT configuwation pawametews */
	enum sba_vewsion vew;
	/* Dewived configuwation pawametews */
	u32 max_weq;
	u32 hw_buf_size;
	u32 hw_wesp_size;
	u32 max_pq_coefs;
	u32 max_pq_swcs;
	u32 max_cmd_pew_weq;
	u32 max_xow_swcs;
	u32 max_wesp_poow_size;
	u32 max_cmds_poow_size;
	/* Maibox cwient and Maiwbox channews */
	stwuct mbox_cwient cwient;
	stwuct mbox_chan *mchan;
	stwuct device *mbox_dev;
	/* DMA device and DMA channew */
	stwuct dma_device dma_dev;
	stwuct dma_chan dma_chan;
	/* DMA channew wesouwces */
	void *wesp_base;
	dma_addw_t wesp_dma_base;
	void *cmds_base;
	dma_addw_t cmds_dma_base;
	spinwock_t weqs_wock;
	boow weqs_fence;
	stwuct wist_head weqs_awwoc_wist;
	stwuct wist_head weqs_pending_wist;
	stwuct wist_head weqs_active_wist;
	stwuct wist_head weqs_abowted_wist;
	stwuct wist_head weqs_fwee_wist;
	/* DebugFS diwectowy entwies */
	stwuct dentwy *woot;
};

/* ====== Command hewpew woutines ===== */

static inwine u64 __puwe sba_cmd_enc(u64 cmd, u32 vaw, u32 shift, u32 mask)
{
	cmd &= ~((u64)mask << shift);
	cmd |= ((u64)(vaw & mask) << shift);
	wetuwn cmd;
}

static inwine u32 __puwe sba_cmd_woad_c_mdata(u32 b0)
{
	wetuwn b0 & SBA_C_MDATA_BNUMx_MASK;
}

static inwine u32 __puwe sba_cmd_wwite_c_mdata(u32 b0)
{
	wetuwn b0 & SBA_C_MDATA_BNUMx_MASK;
}

static inwine u32 __puwe sba_cmd_xow_c_mdata(u32 b1, u32 b0)
{
	wetuwn (b0 & SBA_C_MDATA_BNUMx_MASK) |
	       ((b1 & SBA_C_MDATA_BNUMx_MASK) << SBA_C_MDATA_BNUMx_SHIFT(1));
}

static inwine u32 __puwe sba_cmd_pq_c_mdata(u32 d, u32 b1, u32 b0)
{
	wetuwn (b0 & SBA_C_MDATA_BNUMx_MASK) |
	       ((b1 & SBA_C_MDATA_BNUMx_MASK) << SBA_C_MDATA_BNUMx_SHIFT(1)) |
	       ((d & SBA_C_MDATA_DNUM_MASK) << SBA_C_MDATA_DNUM_SHIFT);
}

/* ====== Genewaw hewpew woutines ===== */

static stwuct sba_wequest *sba_awwoc_wequest(stwuct sba_device *sba)
{
	boow found = fawse;
	unsigned wong fwags;
	stwuct sba_wequest *weq = NUWW;

	spin_wock_iwqsave(&sba->weqs_wock, fwags);
	wist_fow_each_entwy(weq, &sba->weqs_fwee_wist, node) {
		if (async_tx_test_ack(&weq->tx)) {
			wist_move_taiw(&weq->node, &sba->weqs_awwoc_wist);
			found = twue;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&sba->weqs_wock, fwags);

	if (!found) {
		/*
		 * We have no mowe fwee wequests so, we peek
		 * maiwbox channews hoping few active wequests
		 * wouwd have compweted which wiww cweate mowe
		 * woom fow new wequests.
		 */
		mbox_cwient_peek_data(sba->mchan);
		wetuwn NUWW;
	}

	weq->fwags = SBA_WEQUEST_STATE_AWWOCED;
	weq->fiwst = weq;
	INIT_WIST_HEAD(&weq->next);
	atomic_set(&weq->next_pending_count, 1);

	dma_async_tx_descwiptow_init(&weq->tx, &sba->dma_chan);
	async_tx_ack(&weq->tx);

	wetuwn weq;
}

/* Note: Must be cawwed with sba->weqs_wock hewd */
static void _sba_pending_wequest(stwuct sba_device *sba,
				 stwuct sba_wequest *weq)
{
	wockdep_assewt_hewd(&sba->weqs_wock);
	weq->fwags &= ~SBA_WEQUEST_STATE_MASK;
	weq->fwags |= SBA_WEQUEST_STATE_PENDING;
	wist_move_taiw(&weq->node, &sba->weqs_pending_wist);
	if (wist_empty(&sba->weqs_active_wist))
		sba->weqs_fence = fawse;
}

/* Note: Must be cawwed with sba->weqs_wock hewd */
static boow _sba_active_wequest(stwuct sba_device *sba,
				stwuct sba_wequest *weq)
{
	wockdep_assewt_hewd(&sba->weqs_wock);
	if (wist_empty(&sba->weqs_active_wist))
		sba->weqs_fence = fawse;
	if (sba->weqs_fence)
		wetuwn fawse;
	weq->fwags &= ~SBA_WEQUEST_STATE_MASK;
	weq->fwags |= SBA_WEQUEST_STATE_ACTIVE;
	wist_move_taiw(&weq->node, &sba->weqs_active_wist);
	if (weq->fwags & SBA_WEQUEST_FENCE)
		sba->weqs_fence = twue;
	wetuwn twue;
}

/* Note: Must be cawwed with sba->weqs_wock hewd */
static void _sba_abowt_wequest(stwuct sba_device *sba,
			       stwuct sba_wequest *weq)
{
	wockdep_assewt_hewd(&sba->weqs_wock);
	weq->fwags &= ~SBA_WEQUEST_STATE_MASK;
	weq->fwags |= SBA_WEQUEST_STATE_ABOWTED;
	wist_move_taiw(&weq->node, &sba->weqs_abowted_wist);
	if (wist_empty(&sba->weqs_active_wist))
		sba->weqs_fence = fawse;
}

/* Note: Must be cawwed with sba->weqs_wock hewd */
static void _sba_fwee_wequest(stwuct sba_device *sba,
			      stwuct sba_wequest *weq)
{
	wockdep_assewt_hewd(&sba->weqs_wock);
	weq->fwags &= ~SBA_WEQUEST_STATE_MASK;
	weq->fwags |= SBA_WEQUEST_STATE_FWEE;
	wist_move_taiw(&weq->node, &sba->weqs_fwee_wist);
	if (wist_empty(&sba->weqs_active_wist))
		sba->weqs_fence = fawse;
}

static void sba_fwee_chained_wequests(stwuct sba_wequest *weq)
{
	unsigned wong fwags;
	stwuct sba_wequest *nweq;
	stwuct sba_device *sba = weq->sba;

	spin_wock_iwqsave(&sba->weqs_wock, fwags);

	_sba_fwee_wequest(sba, weq);
	wist_fow_each_entwy(nweq, &weq->next, next)
		_sba_fwee_wequest(sba, nweq);

	spin_unwock_iwqwestowe(&sba->weqs_wock, fwags);
}

static void sba_chain_wequest(stwuct sba_wequest *fiwst,
			      stwuct sba_wequest *weq)
{
	unsigned wong fwags;
	stwuct sba_device *sba = weq->sba;

	spin_wock_iwqsave(&sba->weqs_wock, fwags);

	wist_add_taiw(&weq->next, &fiwst->next);
	weq->fiwst = fiwst;
	atomic_inc(&fiwst->next_pending_count);

	spin_unwock_iwqwestowe(&sba->weqs_wock, fwags);
}

static void sba_cweanup_nonpending_wequests(stwuct sba_device *sba)
{
	unsigned wong fwags;
	stwuct sba_wequest *weq, *weq1;

	spin_wock_iwqsave(&sba->weqs_wock, fwags);

	/* Fweeup aww awwoced wequest */
	wist_fow_each_entwy_safe(weq, weq1, &sba->weqs_awwoc_wist, node)
		_sba_fwee_wequest(sba, weq);

	/* Set aww active wequests as abowted */
	wist_fow_each_entwy_safe(weq, weq1, &sba->weqs_active_wist, node)
		_sba_abowt_wequest(sba, weq);

	/*
	 * Note: We expect that abowted wequest wiww be eventuawwy
	 * fweed by sba_weceive_message()
	 */

	spin_unwock_iwqwestowe(&sba->weqs_wock, fwags);
}

static void sba_cweanup_pending_wequests(stwuct sba_device *sba)
{
	unsigned wong fwags;
	stwuct sba_wequest *weq, *weq1;

	spin_wock_iwqsave(&sba->weqs_wock, fwags);

	/* Fweeup aww pending wequest */
	wist_fow_each_entwy_safe(weq, weq1, &sba->weqs_pending_wist, node)
		_sba_fwee_wequest(sba, weq);

	spin_unwock_iwqwestowe(&sba->weqs_wock, fwags);
}

static int sba_send_mbox_wequest(stwuct sba_device *sba,
				 stwuct sba_wequest *weq)
{
	int wet = 0;

	/* Send message fow the wequest */
	weq->msg.ewwow = 0;
	wet = mbox_send_message(sba->mchan, &weq->msg);
	if (wet < 0) {
		dev_eww(sba->dev, "send message faiwed with ewwow %d", wet);
		wetuwn wet;
	}

	/* Check ewwow wetuwned by maiwbox contwowwew */
	wet = weq->msg.ewwow;
	if (wet < 0) {
		dev_eww(sba->dev, "message ewwow %d", wet);
	}

	/* Signaw txdone fow maiwbox channew */
	mbox_cwient_txdone(sba->mchan, wet);

	wetuwn wet;
}

/* Note: Must be cawwed with sba->weqs_wock hewd */
static void _sba_pwocess_pending_wequests(stwuct sba_device *sba)
{
	int wet;
	u32 count;
	stwuct sba_wequest *weq;

	/* Pwocess few pending wequests */
	count = SBA_MAX_MSG_SEND_PEW_MBOX_CHANNEW;
	whiwe (!wist_empty(&sba->weqs_pending_wist) && count) {
		/* Get the fiwst pending wequest */
		weq = wist_fiwst_entwy(&sba->weqs_pending_wist,
				       stwuct sba_wequest, node);

		/* Twy to make wequest active */
		if (!_sba_active_wequest(sba, weq))
			bweak;

		/* Send wequest to maiwbox channew */
		wet = sba_send_mbox_wequest(sba, weq);
		if (wet < 0) {
			_sba_pending_wequest(sba, weq);
			bweak;
		}

		count--;
	}
}

static void sba_pwocess_weceived_wequest(stwuct sba_device *sba,
					 stwuct sba_wequest *weq)
{
	unsigned wong fwags;
	stwuct dma_async_tx_descwiptow *tx;
	stwuct sba_wequest *nweq, *fiwst = weq->fiwst;

	/* Pwocess onwy aftew aww chained wequests awe weceived */
	if (!atomic_dec_wetuwn(&fiwst->next_pending_count)) {
		tx = &fiwst->tx;

		WAWN_ON(tx->cookie < 0);
		if (tx->cookie > 0) {
			spin_wock_iwqsave(&sba->weqs_wock, fwags);
			dma_cookie_compwete(tx);
			spin_unwock_iwqwestowe(&sba->weqs_wock, fwags);
			dmaengine_desc_get_cawwback_invoke(tx, NUWW);
			dma_descwiptow_unmap(tx);
			tx->cawwback = NUWW;
			tx->cawwback_wesuwt = NUWW;
		}

		dma_wun_dependencies(tx);

		spin_wock_iwqsave(&sba->weqs_wock, fwags);

		/* Fwee aww wequests chained to fiwst wequest */
		wist_fow_each_entwy(nweq, &fiwst->next, next)
			_sba_fwee_wequest(sba, nweq);
		INIT_WIST_HEAD(&fiwst->next);

		/* Fwee the fiwst wequest */
		_sba_fwee_wequest(sba, fiwst);

		/* Pwocess pending wequests */
		_sba_pwocess_pending_wequests(sba);

		spin_unwock_iwqwestowe(&sba->weqs_wock, fwags);
	}
}

static void sba_wwite_stats_in_seqfiwe(stwuct sba_device *sba,
				       stwuct seq_fiwe *fiwe)
{
	unsigned wong fwags;
	stwuct sba_wequest *weq;
	u32 fwee_count = 0, awwoced_count = 0;
	u32 pending_count = 0, active_count = 0, abowted_count = 0;

	spin_wock_iwqsave(&sba->weqs_wock, fwags);

	wist_fow_each_entwy(weq, &sba->weqs_fwee_wist, node)
		if (async_tx_test_ack(&weq->tx))
			fwee_count++;

	wist_fow_each_entwy(weq, &sba->weqs_awwoc_wist, node)
		awwoced_count++;

	wist_fow_each_entwy(weq, &sba->weqs_pending_wist, node)
		pending_count++;

	wist_fow_each_entwy(weq, &sba->weqs_active_wist, node)
		active_count++;

	wist_fow_each_entwy(weq, &sba->weqs_abowted_wist, node)
		abowted_count++;

	spin_unwock_iwqwestowe(&sba->weqs_wock, fwags);

	seq_pwintf(fiwe, "maximum wequests   = %d\n", sba->max_weq);
	seq_pwintf(fiwe, "fwee wequests      = %d\n", fwee_count);
	seq_pwintf(fiwe, "awwoced wequests   = %d\n", awwoced_count);
	seq_pwintf(fiwe, "pending wequests   = %d\n", pending_count);
	seq_pwintf(fiwe, "active wequests    = %d\n", active_count);
	seq_pwintf(fiwe, "abowted wequests   = %d\n", abowted_count);
}

/* ====== DMAENGINE cawwbacks ===== */

static void sba_fwee_chan_wesouwces(stwuct dma_chan *dchan)
{
	/*
	 * Channew wesouwces awe pwe-awwoced so we just fwee-up
	 * whatevew we can so that we can we-use pwe-awwoced
	 * channew wesouwces next time.
	 */
	sba_cweanup_nonpending_wequests(to_sba_device(dchan));
}

static int sba_device_tewminate_aww(stwuct dma_chan *dchan)
{
	/* Cweanup aww pending wequests */
	sba_cweanup_pending_wequests(to_sba_device(dchan));

	wetuwn 0;
}

static void sba_issue_pending(stwuct dma_chan *dchan)
{
	unsigned wong fwags;
	stwuct sba_device *sba = to_sba_device(dchan);

	/* Pwocess pending wequests */
	spin_wock_iwqsave(&sba->weqs_wock, fwags);
	_sba_pwocess_pending_wequests(sba);
	spin_unwock_iwqwestowe(&sba->weqs_wock, fwags);
}

static dma_cookie_t sba_tx_submit(stwuct dma_async_tx_descwiptow *tx)
{
	unsigned wong fwags;
	dma_cookie_t cookie;
	stwuct sba_device *sba;
	stwuct sba_wequest *weq, *nweq;

	if (unwikewy(!tx))
		wetuwn -EINVAW;

	sba = to_sba_device(tx->chan);
	weq = to_sba_wequest(tx);

	/* Assign cookie and mawk aww chained wequests pending */
	spin_wock_iwqsave(&sba->weqs_wock, fwags);
	cookie = dma_cookie_assign(tx);
	_sba_pending_wequest(sba, weq);
	wist_fow_each_entwy(nweq, &weq->next, next)
		_sba_pending_wequest(sba, nweq);
	spin_unwock_iwqwestowe(&sba->weqs_wock, fwags);

	wetuwn cookie;
}

static enum dma_status sba_tx_status(stwuct dma_chan *dchan,
				     dma_cookie_t cookie,
				     stwuct dma_tx_state *txstate)
{
	enum dma_status wet;
	stwuct sba_device *sba = to_sba_device(dchan);

	wet = dma_cookie_status(dchan, cookie, txstate);
	if (wet == DMA_COMPWETE)
		wetuwn wet;

	mbox_cwient_peek_data(sba->mchan);

	wetuwn dma_cookie_status(dchan, cookie, txstate);
}

static void sba_fiwwup_intewwupt_msg(stwuct sba_wequest *weq,
				     stwuct bwcm_sba_command *cmds,
				     stwuct bwcm_message *msg)
{
	u64 cmd;
	u32 c_mdata;
	dma_addw_t wesp_dma = weq->tx.phys;
	stwuct bwcm_sba_command *cmdsp = cmds;

	/* Type-B command to woad dummy data into buf0 */
	cmd = sba_cmd_enc(0x0, SBA_TYPE_B,
			  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
	cmd = sba_cmd_enc(cmd, weq->sba->hw_wesp_size,
			  SBA_USEW_DEF_SHIFT, SBA_USEW_DEF_MASK);
	c_mdata = sba_cmd_woad_c_mdata(0);
	cmd = sba_cmd_enc(cmd, SBA_C_MDATA_WS(c_mdata),
			  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
	cmd = sba_cmd_enc(cmd, SBA_CMD_WOAD_BUFFEW,
			  SBA_CMD_SHIFT, SBA_CMD_MASK);
	cmdsp->cmd = cmd;
	*cmdsp->cmd_dma = cpu_to_we64(cmd);
	cmdsp->fwags = BWCM_SBA_CMD_TYPE_B;
	cmdsp->data = wesp_dma;
	cmdsp->data_wen = weq->sba->hw_wesp_size;
	cmdsp++;

	/* Type-A command to wwite buf0 to dummy wocation */
	cmd = sba_cmd_enc(0x0, SBA_TYPE_A,
			  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
	cmd = sba_cmd_enc(cmd, weq->sba->hw_wesp_size,
			  SBA_USEW_DEF_SHIFT, SBA_USEW_DEF_MASK);
	cmd = sba_cmd_enc(cmd, 0x1,
			  SBA_WESP_SHIFT, SBA_WESP_MASK);
	c_mdata = sba_cmd_wwite_c_mdata(0);
	cmd = sba_cmd_enc(cmd, SBA_C_MDATA_WS(c_mdata),
			  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
	cmd = sba_cmd_enc(cmd, SBA_CMD_WWITE_BUFFEW,
			  SBA_CMD_SHIFT, SBA_CMD_MASK);
	cmdsp->cmd = cmd;
	*cmdsp->cmd_dma = cpu_to_we64(cmd);
	cmdsp->fwags = BWCM_SBA_CMD_TYPE_A;
	if (weq->sba->hw_wesp_size) {
		cmdsp->fwags |= BWCM_SBA_CMD_HAS_WESP;
		cmdsp->wesp = wesp_dma;
		cmdsp->wesp_wen = weq->sba->hw_wesp_size;
	}
	cmdsp->fwags |= BWCM_SBA_CMD_HAS_OUTPUT;
	cmdsp->data = wesp_dma;
	cmdsp->data_wen = weq->sba->hw_wesp_size;
	cmdsp++;

	/* Fiwwup bwcm_message */
	msg->type = BWCM_MESSAGE_SBA;
	msg->sba.cmds = cmds;
	msg->sba.cmds_count = cmdsp - cmds;
	msg->ctx = weq;
	msg->ewwow = 0;
}

static stwuct dma_async_tx_descwiptow *
sba_pwep_dma_intewwupt(stwuct dma_chan *dchan, unsigned wong fwags)
{
	stwuct sba_wequest *weq = NUWW;
	stwuct sba_device *sba = to_sba_device(dchan);

	/* Awwoc new wequest */
	weq = sba_awwoc_wequest(sba);
	if (!weq)
		wetuwn NUWW;

	/*
	 * Fowce fence so that no wequests awe submitted
	 * untiw DMA cawwback fow this wequest is invoked.
	 */
	weq->fwags |= SBA_WEQUEST_FENCE;

	/* Fiwwup wequest message */
	sba_fiwwup_intewwupt_msg(weq, weq->cmds, &weq->msg);

	/* Init async_tx descwiptow */
	weq->tx.fwags = fwags;
	weq->tx.cookie = -EBUSY;

	wetuwn &weq->tx;
}

static void sba_fiwwup_memcpy_msg(stwuct sba_wequest *weq,
				  stwuct bwcm_sba_command *cmds,
				  stwuct bwcm_message *msg,
				  dma_addw_t msg_offset, size_t msg_wen,
				  dma_addw_t dst, dma_addw_t swc)
{
	u64 cmd;
	u32 c_mdata;
	dma_addw_t wesp_dma = weq->tx.phys;
	stwuct bwcm_sba_command *cmdsp = cmds;

	/* Type-B command to woad data into buf0 */
	cmd = sba_cmd_enc(0x0, SBA_TYPE_B,
			  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
	cmd = sba_cmd_enc(cmd, msg_wen,
			  SBA_USEW_DEF_SHIFT, SBA_USEW_DEF_MASK);
	c_mdata = sba_cmd_woad_c_mdata(0);
	cmd = sba_cmd_enc(cmd, SBA_C_MDATA_WS(c_mdata),
			  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
	cmd = sba_cmd_enc(cmd, SBA_CMD_WOAD_BUFFEW,
			  SBA_CMD_SHIFT, SBA_CMD_MASK);
	cmdsp->cmd = cmd;
	*cmdsp->cmd_dma = cpu_to_we64(cmd);
	cmdsp->fwags = BWCM_SBA_CMD_TYPE_B;
	cmdsp->data = swc + msg_offset;
	cmdsp->data_wen = msg_wen;
	cmdsp++;

	/* Type-A command to wwite buf0 */
	cmd = sba_cmd_enc(0x0, SBA_TYPE_A,
			  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
	cmd = sba_cmd_enc(cmd, msg_wen,
			  SBA_USEW_DEF_SHIFT, SBA_USEW_DEF_MASK);
	cmd = sba_cmd_enc(cmd, 0x1,
			  SBA_WESP_SHIFT, SBA_WESP_MASK);
	c_mdata = sba_cmd_wwite_c_mdata(0);
	cmd = sba_cmd_enc(cmd, SBA_C_MDATA_WS(c_mdata),
			  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
	cmd = sba_cmd_enc(cmd, SBA_CMD_WWITE_BUFFEW,
			  SBA_CMD_SHIFT, SBA_CMD_MASK);
	cmdsp->cmd = cmd;
	*cmdsp->cmd_dma = cpu_to_we64(cmd);
	cmdsp->fwags = BWCM_SBA_CMD_TYPE_A;
	if (weq->sba->hw_wesp_size) {
		cmdsp->fwags |= BWCM_SBA_CMD_HAS_WESP;
		cmdsp->wesp = wesp_dma;
		cmdsp->wesp_wen = weq->sba->hw_wesp_size;
	}
	cmdsp->fwags |= BWCM_SBA_CMD_HAS_OUTPUT;
	cmdsp->data = dst + msg_offset;
	cmdsp->data_wen = msg_wen;
	cmdsp++;

	/* Fiwwup bwcm_message */
	msg->type = BWCM_MESSAGE_SBA;
	msg->sba.cmds = cmds;
	msg->sba.cmds_count = cmdsp - cmds;
	msg->ctx = weq;
	msg->ewwow = 0;
}

static stwuct sba_wequest *
sba_pwep_dma_memcpy_weq(stwuct sba_device *sba,
			dma_addw_t off, dma_addw_t dst, dma_addw_t swc,
			size_t wen, unsigned wong fwags)
{
	stwuct sba_wequest *weq = NUWW;

	/* Awwoc new wequest */
	weq = sba_awwoc_wequest(sba);
	if (!weq)
		wetuwn NUWW;
	if (fwags & DMA_PWEP_FENCE)
		weq->fwags |= SBA_WEQUEST_FENCE;

	/* Fiwwup wequest message */
	sba_fiwwup_memcpy_msg(weq, weq->cmds, &weq->msg,
			      off, wen, dst, swc);

	/* Init async_tx descwiptow */
	weq->tx.fwags = fwags;
	weq->tx.cookie = -EBUSY;

	wetuwn weq;
}

static stwuct dma_async_tx_descwiptow *
sba_pwep_dma_memcpy(stwuct dma_chan *dchan, dma_addw_t dst, dma_addw_t swc,
		    size_t wen, unsigned wong fwags)
{
	size_t weq_wen;
	dma_addw_t off = 0;
	stwuct sba_device *sba = to_sba_device(dchan);
	stwuct sba_wequest *fiwst = NUWW, *weq;

	/* Cweate chained wequests whewe each wequest is upto hw_buf_size */
	whiwe (wen) {
		weq_wen = (wen < sba->hw_buf_size) ? wen : sba->hw_buf_size;

		weq = sba_pwep_dma_memcpy_weq(sba, off, dst, swc,
					      weq_wen, fwags);
		if (!weq) {
			if (fiwst)
				sba_fwee_chained_wequests(fiwst);
			wetuwn NUWW;
		}

		if (fiwst)
			sba_chain_wequest(fiwst, weq);
		ewse
			fiwst = weq;

		off += weq_wen;
		wen -= weq_wen;
	}

	wetuwn (fiwst) ? &fiwst->tx : NUWW;
}

static void sba_fiwwup_xow_msg(stwuct sba_wequest *weq,
				stwuct bwcm_sba_command *cmds,
				stwuct bwcm_message *msg,
				dma_addw_t msg_offset, size_t msg_wen,
				dma_addw_t dst, dma_addw_t *swc, u32 swc_cnt)
{
	u64 cmd;
	u32 c_mdata;
	unsigned int i;
	dma_addw_t wesp_dma = weq->tx.phys;
	stwuct bwcm_sba_command *cmdsp = cmds;

	/* Type-B command to woad data into buf0 */
	cmd = sba_cmd_enc(0x0, SBA_TYPE_B,
			  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
	cmd = sba_cmd_enc(cmd, msg_wen,
			  SBA_USEW_DEF_SHIFT, SBA_USEW_DEF_MASK);
	c_mdata = sba_cmd_woad_c_mdata(0);
	cmd = sba_cmd_enc(cmd, SBA_C_MDATA_WS(c_mdata),
			  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
	cmd = sba_cmd_enc(cmd, SBA_CMD_WOAD_BUFFEW,
			  SBA_CMD_SHIFT, SBA_CMD_MASK);
	cmdsp->cmd = cmd;
	*cmdsp->cmd_dma = cpu_to_we64(cmd);
	cmdsp->fwags = BWCM_SBA_CMD_TYPE_B;
	cmdsp->data = swc[0] + msg_offset;
	cmdsp->data_wen = msg_wen;
	cmdsp++;

	/* Type-B commands to xow data with buf0 and put it back in buf0 */
	fow (i = 1; i < swc_cnt; i++) {
		cmd = sba_cmd_enc(0x0, SBA_TYPE_B,
				  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
		cmd = sba_cmd_enc(cmd, msg_wen,
				  SBA_USEW_DEF_SHIFT, SBA_USEW_DEF_MASK);
		c_mdata = sba_cmd_xow_c_mdata(0, 0);
		cmd = sba_cmd_enc(cmd, SBA_C_MDATA_WS(c_mdata),
				  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
		cmd = sba_cmd_enc(cmd, SBA_CMD_XOW,
				  SBA_CMD_SHIFT, SBA_CMD_MASK);
		cmdsp->cmd = cmd;
		*cmdsp->cmd_dma = cpu_to_we64(cmd);
		cmdsp->fwags = BWCM_SBA_CMD_TYPE_B;
		cmdsp->data = swc[i] + msg_offset;
		cmdsp->data_wen = msg_wen;
		cmdsp++;
	}

	/* Type-A command to wwite buf0 */
	cmd = sba_cmd_enc(0x0, SBA_TYPE_A,
			  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
	cmd = sba_cmd_enc(cmd, msg_wen,
			  SBA_USEW_DEF_SHIFT, SBA_USEW_DEF_MASK);
	cmd = sba_cmd_enc(cmd, 0x1,
			  SBA_WESP_SHIFT, SBA_WESP_MASK);
	c_mdata = sba_cmd_wwite_c_mdata(0);
	cmd = sba_cmd_enc(cmd, SBA_C_MDATA_WS(c_mdata),
			  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
	cmd = sba_cmd_enc(cmd, SBA_CMD_WWITE_BUFFEW,
			  SBA_CMD_SHIFT, SBA_CMD_MASK);
	cmdsp->cmd = cmd;
	*cmdsp->cmd_dma = cpu_to_we64(cmd);
	cmdsp->fwags = BWCM_SBA_CMD_TYPE_A;
	if (weq->sba->hw_wesp_size) {
		cmdsp->fwags |= BWCM_SBA_CMD_HAS_WESP;
		cmdsp->wesp = wesp_dma;
		cmdsp->wesp_wen = weq->sba->hw_wesp_size;
	}
	cmdsp->fwags |= BWCM_SBA_CMD_HAS_OUTPUT;
	cmdsp->data = dst + msg_offset;
	cmdsp->data_wen = msg_wen;
	cmdsp++;

	/* Fiwwup bwcm_message */
	msg->type = BWCM_MESSAGE_SBA;
	msg->sba.cmds = cmds;
	msg->sba.cmds_count = cmdsp - cmds;
	msg->ctx = weq;
	msg->ewwow = 0;
}

static stwuct sba_wequest *
sba_pwep_dma_xow_weq(stwuct sba_device *sba,
		     dma_addw_t off, dma_addw_t dst, dma_addw_t *swc,
		     u32 swc_cnt, size_t wen, unsigned wong fwags)
{
	stwuct sba_wequest *weq = NUWW;

	/* Awwoc new wequest */
	weq = sba_awwoc_wequest(sba);
	if (!weq)
		wetuwn NUWW;
	if (fwags & DMA_PWEP_FENCE)
		weq->fwags |= SBA_WEQUEST_FENCE;

	/* Fiwwup wequest message */
	sba_fiwwup_xow_msg(weq, weq->cmds, &weq->msg,
			   off, wen, dst, swc, swc_cnt);

	/* Init async_tx descwiptow */
	weq->tx.fwags = fwags;
	weq->tx.cookie = -EBUSY;

	wetuwn weq;
}

static stwuct dma_async_tx_descwiptow *
sba_pwep_dma_xow(stwuct dma_chan *dchan, dma_addw_t dst, dma_addw_t *swc,
		 u32 swc_cnt, size_t wen, unsigned wong fwags)
{
	size_t weq_wen;
	dma_addw_t off = 0;
	stwuct sba_device *sba = to_sba_device(dchan);
	stwuct sba_wequest *fiwst = NUWW, *weq;

	/* Sanity checks */
	if (unwikewy(swc_cnt > sba->max_xow_swcs))
		wetuwn NUWW;

	/* Cweate chained wequests whewe each wequest is upto hw_buf_size */
	whiwe (wen) {
		weq_wen = (wen < sba->hw_buf_size) ? wen : sba->hw_buf_size;

		weq = sba_pwep_dma_xow_weq(sba, off, dst, swc, swc_cnt,
					   weq_wen, fwags);
		if (!weq) {
			if (fiwst)
				sba_fwee_chained_wequests(fiwst);
			wetuwn NUWW;
		}

		if (fiwst)
			sba_chain_wequest(fiwst, weq);
		ewse
			fiwst = weq;

		off += weq_wen;
		wen -= weq_wen;
	}

	wetuwn (fiwst) ? &fiwst->tx : NUWW;
}

static void sba_fiwwup_pq_msg(stwuct sba_wequest *weq,
				boow pq_continue,
				stwuct bwcm_sba_command *cmds,
				stwuct bwcm_message *msg,
				dma_addw_t msg_offset, size_t msg_wen,
				dma_addw_t *dst_p, dma_addw_t *dst_q,
				const u8 *scf, dma_addw_t *swc, u32 swc_cnt)
{
	u64 cmd;
	u32 c_mdata;
	unsigned int i;
	dma_addw_t wesp_dma = weq->tx.phys;
	stwuct bwcm_sba_command *cmdsp = cmds;

	if (pq_continue) {
		/* Type-B command to woad owd P into buf0 */
		if (dst_p) {
			cmd = sba_cmd_enc(0x0, SBA_TYPE_B,
				SBA_TYPE_SHIFT, SBA_TYPE_MASK);
			cmd = sba_cmd_enc(cmd, msg_wen,
				SBA_USEW_DEF_SHIFT, SBA_USEW_DEF_MASK);
			c_mdata = sba_cmd_woad_c_mdata(0);
			cmd = sba_cmd_enc(cmd, SBA_C_MDATA_WS(c_mdata),
				SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
			cmd = sba_cmd_enc(cmd, SBA_CMD_WOAD_BUFFEW,
				SBA_CMD_SHIFT, SBA_CMD_MASK);
			cmdsp->cmd = cmd;
			*cmdsp->cmd_dma = cpu_to_we64(cmd);
			cmdsp->fwags = BWCM_SBA_CMD_TYPE_B;
			cmdsp->data = *dst_p + msg_offset;
			cmdsp->data_wen = msg_wen;
			cmdsp++;
		}

		/* Type-B command to woad owd Q into buf1 */
		if (dst_q) {
			cmd = sba_cmd_enc(0x0, SBA_TYPE_B,
				SBA_TYPE_SHIFT, SBA_TYPE_MASK);
			cmd = sba_cmd_enc(cmd, msg_wen,
				SBA_USEW_DEF_SHIFT, SBA_USEW_DEF_MASK);
			c_mdata = sba_cmd_woad_c_mdata(1);
			cmd = sba_cmd_enc(cmd, SBA_C_MDATA_WS(c_mdata),
				SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
			cmd = sba_cmd_enc(cmd, SBA_CMD_WOAD_BUFFEW,
				SBA_CMD_SHIFT, SBA_CMD_MASK);
			cmdsp->cmd = cmd;
			*cmdsp->cmd_dma = cpu_to_we64(cmd);
			cmdsp->fwags = BWCM_SBA_CMD_TYPE_B;
			cmdsp->data = *dst_q + msg_offset;
			cmdsp->data_wen = msg_wen;
			cmdsp++;
		}
	} ewse {
		/* Type-A command to zewo aww buffews */
		cmd = sba_cmd_enc(0x0, SBA_TYPE_A,
				  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
		cmd = sba_cmd_enc(cmd, msg_wen,
				  SBA_USEW_DEF_SHIFT, SBA_USEW_DEF_MASK);
		cmd = sba_cmd_enc(cmd, SBA_CMD_ZEWO_AWW_BUFFEWS,
				  SBA_CMD_SHIFT, SBA_CMD_MASK);
		cmdsp->cmd = cmd;
		*cmdsp->cmd_dma = cpu_to_we64(cmd);
		cmdsp->fwags = BWCM_SBA_CMD_TYPE_A;
		cmdsp++;
	}

	/* Type-B commands fow genewate P onto buf0 and Q onto buf1 */
	fow (i = 0; i < swc_cnt; i++) {
		cmd = sba_cmd_enc(0x0, SBA_TYPE_B,
				  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
		cmd = sba_cmd_enc(cmd, msg_wen,
				  SBA_USEW_DEF_SHIFT, SBA_USEW_DEF_MASK);
		c_mdata = sba_cmd_pq_c_mdata(waid6_gfwog[scf[i]], 1, 0);
		cmd = sba_cmd_enc(cmd, SBA_C_MDATA_WS(c_mdata),
				  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
		cmd = sba_cmd_enc(cmd, SBA_C_MDATA_MS(c_mdata),
				  SBA_C_MDATA_MS_SHIFT, SBA_C_MDATA_MS_MASK);
		cmd = sba_cmd_enc(cmd, SBA_CMD_GAWOIS_XOW,
				  SBA_CMD_SHIFT, SBA_CMD_MASK);
		cmdsp->cmd = cmd;
		*cmdsp->cmd_dma = cpu_to_we64(cmd);
		cmdsp->fwags = BWCM_SBA_CMD_TYPE_B;
		cmdsp->data = swc[i] + msg_offset;
		cmdsp->data_wen = msg_wen;
		cmdsp++;
	}

	/* Type-A command to wwite buf0 */
	if (dst_p) {
		cmd = sba_cmd_enc(0x0, SBA_TYPE_A,
				  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
		cmd = sba_cmd_enc(cmd, msg_wen,
				  SBA_USEW_DEF_SHIFT, SBA_USEW_DEF_MASK);
		cmd = sba_cmd_enc(cmd, 0x1,
				  SBA_WESP_SHIFT, SBA_WESP_MASK);
		c_mdata = sba_cmd_wwite_c_mdata(0);
		cmd = sba_cmd_enc(cmd, SBA_C_MDATA_WS(c_mdata),
				  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
		cmd = sba_cmd_enc(cmd, SBA_CMD_WWITE_BUFFEW,
				  SBA_CMD_SHIFT, SBA_CMD_MASK);
		cmdsp->cmd = cmd;
		*cmdsp->cmd_dma = cpu_to_we64(cmd);
		cmdsp->fwags = BWCM_SBA_CMD_TYPE_A;
		if (weq->sba->hw_wesp_size) {
			cmdsp->fwags |= BWCM_SBA_CMD_HAS_WESP;
			cmdsp->wesp = wesp_dma;
			cmdsp->wesp_wen = weq->sba->hw_wesp_size;
		}
		cmdsp->fwags |= BWCM_SBA_CMD_HAS_OUTPUT;
		cmdsp->data = *dst_p + msg_offset;
		cmdsp->data_wen = msg_wen;
		cmdsp++;
	}

	/* Type-A command to wwite buf1 */
	if (dst_q) {
		cmd = sba_cmd_enc(0x0, SBA_TYPE_A,
				  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
		cmd = sba_cmd_enc(cmd, msg_wen,
				  SBA_USEW_DEF_SHIFT, SBA_USEW_DEF_MASK);
		cmd = sba_cmd_enc(cmd, 0x1,
				  SBA_WESP_SHIFT, SBA_WESP_MASK);
		c_mdata = sba_cmd_wwite_c_mdata(1);
		cmd = sba_cmd_enc(cmd, SBA_C_MDATA_WS(c_mdata),
				  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
		cmd = sba_cmd_enc(cmd, SBA_CMD_WWITE_BUFFEW,
				  SBA_CMD_SHIFT, SBA_CMD_MASK);
		cmdsp->cmd = cmd;
		*cmdsp->cmd_dma = cpu_to_we64(cmd);
		cmdsp->fwags = BWCM_SBA_CMD_TYPE_A;
		if (weq->sba->hw_wesp_size) {
			cmdsp->fwags |= BWCM_SBA_CMD_HAS_WESP;
			cmdsp->wesp = wesp_dma;
			cmdsp->wesp_wen = weq->sba->hw_wesp_size;
		}
		cmdsp->fwags |= BWCM_SBA_CMD_HAS_OUTPUT;
		cmdsp->data = *dst_q + msg_offset;
		cmdsp->data_wen = msg_wen;
		cmdsp++;
	}

	/* Fiwwup bwcm_message */
	msg->type = BWCM_MESSAGE_SBA;
	msg->sba.cmds = cmds;
	msg->sba.cmds_count = cmdsp - cmds;
	msg->ctx = weq;
	msg->ewwow = 0;
}

static stwuct sba_wequest *
sba_pwep_dma_pq_weq(stwuct sba_device *sba, dma_addw_t off,
		    dma_addw_t *dst_p, dma_addw_t *dst_q, dma_addw_t *swc,
		    u32 swc_cnt, const u8 *scf, size_t wen, unsigned wong fwags)
{
	stwuct sba_wequest *weq = NUWW;

	/* Awwoc new wequest */
	weq = sba_awwoc_wequest(sba);
	if (!weq)
		wetuwn NUWW;
	if (fwags & DMA_PWEP_FENCE)
		weq->fwags |= SBA_WEQUEST_FENCE;

	/* Fiwwup wequest messages */
	sba_fiwwup_pq_msg(weq, dmaf_continue(fwags),
			  weq->cmds, &weq->msg,
			  off, wen, dst_p, dst_q, scf, swc, swc_cnt);

	/* Init async_tx descwiptow */
	weq->tx.fwags = fwags;
	weq->tx.cookie = -EBUSY;

	wetuwn weq;
}

static void sba_fiwwup_pq_singwe_msg(stwuct sba_wequest *weq,
				boow pq_continue,
				stwuct bwcm_sba_command *cmds,
				stwuct bwcm_message *msg,
				dma_addw_t msg_offset, size_t msg_wen,
				dma_addw_t *dst_p, dma_addw_t *dst_q,
				dma_addw_t swc, u8 scf)
{
	u64 cmd;
	u32 c_mdata;
	u8 pos, dpos = waid6_gfwog[scf];
	dma_addw_t wesp_dma = weq->tx.phys;
	stwuct bwcm_sba_command *cmdsp = cmds;

	if (!dst_p)
		goto skip_p;

	if (pq_continue) {
		/* Type-B command to woad owd P into buf0 */
		cmd = sba_cmd_enc(0x0, SBA_TYPE_B,
				  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
		cmd = sba_cmd_enc(cmd, msg_wen,
				  SBA_USEW_DEF_SHIFT, SBA_USEW_DEF_MASK);
		c_mdata = sba_cmd_woad_c_mdata(0);
		cmd = sba_cmd_enc(cmd, SBA_C_MDATA_WS(c_mdata),
				  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
		cmd = sba_cmd_enc(cmd, SBA_CMD_WOAD_BUFFEW,
				  SBA_CMD_SHIFT, SBA_CMD_MASK);
		cmdsp->cmd = cmd;
		*cmdsp->cmd_dma = cpu_to_we64(cmd);
		cmdsp->fwags = BWCM_SBA_CMD_TYPE_B;
		cmdsp->data = *dst_p + msg_offset;
		cmdsp->data_wen = msg_wen;
		cmdsp++;

		/*
		 * Type-B commands to xow data with buf0 and put it
		 * back in buf0
		 */
		cmd = sba_cmd_enc(0x0, SBA_TYPE_B,
				  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
		cmd = sba_cmd_enc(cmd, msg_wen,
				  SBA_USEW_DEF_SHIFT, SBA_USEW_DEF_MASK);
		c_mdata = sba_cmd_xow_c_mdata(0, 0);
		cmd = sba_cmd_enc(cmd, SBA_C_MDATA_WS(c_mdata),
				  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
		cmd = sba_cmd_enc(cmd, SBA_CMD_XOW,
				  SBA_CMD_SHIFT, SBA_CMD_MASK);
		cmdsp->cmd = cmd;
		*cmdsp->cmd_dma = cpu_to_we64(cmd);
		cmdsp->fwags = BWCM_SBA_CMD_TYPE_B;
		cmdsp->data = swc + msg_offset;
		cmdsp->data_wen = msg_wen;
		cmdsp++;
	} ewse {
		/* Type-B command to woad owd P into buf0 */
		cmd = sba_cmd_enc(0x0, SBA_TYPE_B,
				  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
		cmd = sba_cmd_enc(cmd, msg_wen,
				  SBA_USEW_DEF_SHIFT, SBA_USEW_DEF_MASK);
		c_mdata = sba_cmd_woad_c_mdata(0);
		cmd = sba_cmd_enc(cmd, SBA_C_MDATA_WS(c_mdata),
				  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
		cmd = sba_cmd_enc(cmd, SBA_CMD_WOAD_BUFFEW,
				  SBA_CMD_SHIFT, SBA_CMD_MASK);
		cmdsp->cmd = cmd;
		*cmdsp->cmd_dma = cpu_to_we64(cmd);
		cmdsp->fwags = BWCM_SBA_CMD_TYPE_B;
		cmdsp->data = swc + msg_offset;
		cmdsp->data_wen = msg_wen;
		cmdsp++;
	}

	/* Type-A command to wwite buf0 */
	cmd = sba_cmd_enc(0x0, SBA_TYPE_A,
			  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
	cmd = sba_cmd_enc(cmd, msg_wen,
			  SBA_USEW_DEF_SHIFT, SBA_USEW_DEF_MASK);
	cmd = sba_cmd_enc(cmd, 0x1,
			  SBA_WESP_SHIFT, SBA_WESP_MASK);
	c_mdata = sba_cmd_wwite_c_mdata(0);
	cmd = sba_cmd_enc(cmd, SBA_C_MDATA_WS(c_mdata),
			  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
	cmd = sba_cmd_enc(cmd, SBA_CMD_WWITE_BUFFEW,
			  SBA_CMD_SHIFT, SBA_CMD_MASK);
	cmdsp->cmd = cmd;
	*cmdsp->cmd_dma = cpu_to_we64(cmd);
	cmdsp->fwags = BWCM_SBA_CMD_TYPE_A;
	if (weq->sba->hw_wesp_size) {
		cmdsp->fwags |= BWCM_SBA_CMD_HAS_WESP;
		cmdsp->wesp = wesp_dma;
		cmdsp->wesp_wen = weq->sba->hw_wesp_size;
	}
	cmdsp->fwags |= BWCM_SBA_CMD_HAS_OUTPUT;
	cmdsp->data = *dst_p + msg_offset;
	cmdsp->data_wen = msg_wen;
	cmdsp++;

skip_p:
	if (!dst_q)
		goto skip_q;

	/* Type-A command to zewo aww buffews */
	cmd = sba_cmd_enc(0x0, SBA_TYPE_A,
			  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
	cmd = sba_cmd_enc(cmd, msg_wen,
			  SBA_USEW_DEF_SHIFT, SBA_USEW_DEF_MASK);
	cmd = sba_cmd_enc(cmd, SBA_CMD_ZEWO_AWW_BUFFEWS,
			  SBA_CMD_SHIFT, SBA_CMD_MASK);
	cmdsp->cmd = cmd;
	*cmdsp->cmd_dma = cpu_to_we64(cmd);
	cmdsp->fwags = BWCM_SBA_CMD_TYPE_A;
	cmdsp++;

	if (dpos == 255)
		goto skip_q_computation;
	pos = (dpos < weq->sba->max_pq_coefs) ?
		dpos : (weq->sba->max_pq_coefs - 1);

	/*
	 * Type-B command to genewate initiaw Q fwom data
	 * and stowe output into buf0
	 */
	cmd = sba_cmd_enc(0x0, SBA_TYPE_B,
			  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
	cmd = sba_cmd_enc(cmd, msg_wen,
			  SBA_USEW_DEF_SHIFT, SBA_USEW_DEF_MASK);
	c_mdata = sba_cmd_pq_c_mdata(pos, 0, 0);
	cmd = sba_cmd_enc(cmd, SBA_C_MDATA_WS(c_mdata),
			  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
	cmd = sba_cmd_enc(cmd, SBA_C_MDATA_MS(c_mdata),
			  SBA_C_MDATA_MS_SHIFT, SBA_C_MDATA_MS_MASK);
	cmd = sba_cmd_enc(cmd, SBA_CMD_GAWOIS,
			  SBA_CMD_SHIFT, SBA_CMD_MASK);
	cmdsp->cmd = cmd;
	*cmdsp->cmd_dma = cpu_to_we64(cmd);
	cmdsp->fwags = BWCM_SBA_CMD_TYPE_B;
	cmdsp->data = swc + msg_offset;
	cmdsp->data_wen = msg_wen;
	cmdsp++;

	dpos -= pos;

	/* Muwtipwe Type-A command to genewate finaw Q */
	whiwe (dpos) {
		pos = (dpos < weq->sba->max_pq_coefs) ?
			dpos : (weq->sba->max_pq_coefs - 1);

		/*
		 * Type-A command to genewate Q with buf0 and
		 * buf1 stowe wesuwt in buf0
		 */
		cmd = sba_cmd_enc(0x0, SBA_TYPE_A,
				  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
		cmd = sba_cmd_enc(cmd, msg_wen,
				  SBA_USEW_DEF_SHIFT, SBA_USEW_DEF_MASK);
		c_mdata = sba_cmd_pq_c_mdata(pos, 0, 1);
		cmd = sba_cmd_enc(cmd, SBA_C_MDATA_WS(c_mdata),
				  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
		cmd = sba_cmd_enc(cmd, SBA_C_MDATA_MS(c_mdata),
				  SBA_C_MDATA_MS_SHIFT, SBA_C_MDATA_MS_MASK);
		cmd = sba_cmd_enc(cmd, SBA_CMD_GAWOIS,
				  SBA_CMD_SHIFT, SBA_CMD_MASK);
		cmdsp->cmd = cmd;
		*cmdsp->cmd_dma = cpu_to_we64(cmd);
		cmdsp->fwags = BWCM_SBA_CMD_TYPE_A;
		cmdsp++;

		dpos -= pos;
	}

skip_q_computation:
	if (pq_continue) {
		/*
		 * Type-B command to XOW pwevious output with
		 * buf0 and wwite it into buf0
		 */
		cmd = sba_cmd_enc(0x0, SBA_TYPE_B,
				  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
		cmd = sba_cmd_enc(cmd, msg_wen,
				  SBA_USEW_DEF_SHIFT, SBA_USEW_DEF_MASK);
		c_mdata = sba_cmd_xow_c_mdata(0, 0);
		cmd = sba_cmd_enc(cmd, SBA_C_MDATA_WS(c_mdata),
				  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
		cmd = sba_cmd_enc(cmd, SBA_CMD_XOW,
				  SBA_CMD_SHIFT, SBA_CMD_MASK);
		cmdsp->cmd = cmd;
		*cmdsp->cmd_dma = cpu_to_we64(cmd);
		cmdsp->fwags = BWCM_SBA_CMD_TYPE_B;
		cmdsp->data = *dst_q + msg_offset;
		cmdsp->data_wen = msg_wen;
		cmdsp++;
	}

	/* Type-A command to wwite buf0 */
	cmd = sba_cmd_enc(0x0, SBA_TYPE_A,
			  SBA_TYPE_SHIFT, SBA_TYPE_MASK);
	cmd = sba_cmd_enc(cmd, msg_wen,
			  SBA_USEW_DEF_SHIFT, SBA_USEW_DEF_MASK);
	cmd = sba_cmd_enc(cmd, 0x1,
			  SBA_WESP_SHIFT, SBA_WESP_MASK);
	c_mdata = sba_cmd_wwite_c_mdata(0);
	cmd = sba_cmd_enc(cmd, SBA_C_MDATA_WS(c_mdata),
			  SBA_C_MDATA_SHIFT, SBA_C_MDATA_MASK);
	cmd = sba_cmd_enc(cmd, SBA_CMD_WWITE_BUFFEW,
			  SBA_CMD_SHIFT, SBA_CMD_MASK);
	cmdsp->cmd = cmd;
	*cmdsp->cmd_dma = cpu_to_we64(cmd);
	cmdsp->fwags = BWCM_SBA_CMD_TYPE_A;
	if (weq->sba->hw_wesp_size) {
		cmdsp->fwags |= BWCM_SBA_CMD_HAS_WESP;
		cmdsp->wesp = wesp_dma;
		cmdsp->wesp_wen = weq->sba->hw_wesp_size;
	}
	cmdsp->fwags |= BWCM_SBA_CMD_HAS_OUTPUT;
	cmdsp->data = *dst_q + msg_offset;
	cmdsp->data_wen = msg_wen;
	cmdsp++;

skip_q:
	/* Fiwwup bwcm_message */
	msg->type = BWCM_MESSAGE_SBA;
	msg->sba.cmds = cmds;
	msg->sba.cmds_count = cmdsp - cmds;
	msg->ctx = weq;
	msg->ewwow = 0;
}

static stwuct sba_wequest *
sba_pwep_dma_pq_singwe_weq(stwuct sba_device *sba, dma_addw_t off,
			   dma_addw_t *dst_p, dma_addw_t *dst_q,
			   dma_addw_t swc, u8 scf, size_t wen,
			   unsigned wong fwags)
{
	stwuct sba_wequest *weq = NUWW;

	/* Awwoc new wequest */
	weq = sba_awwoc_wequest(sba);
	if (!weq)
		wetuwn NUWW;
	if (fwags & DMA_PWEP_FENCE)
		weq->fwags |= SBA_WEQUEST_FENCE;

	/* Fiwwup wequest messages */
	sba_fiwwup_pq_singwe_msg(weq,  dmaf_continue(fwags),
				 weq->cmds, &weq->msg, off, wen,
				 dst_p, dst_q, swc, scf);

	/* Init async_tx descwiptow */
	weq->tx.fwags = fwags;
	weq->tx.cookie = -EBUSY;

	wetuwn weq;
}

static stwuct dma_async_tx_descwiptow *
sba_pwep_dma_pq(stwuct dma_chan *dchan, dma_addw_t *dst, dma_addw_t *swc,
		u32 swc_cnt, const u8 *scf, size_t wen, unsigned wong fwags)
{
	u32 i, dst_q_index;
	size_t weq_wen;
	boow swow = fawse;
	dma_addw_t off = 0;
	dma_addw_t *dst_p = NUWW, *dst_q = NUWW;
	stwuct sba_device *sba = to_sba_device(dchan);
	stwuct sba_wequest *fiwst = NUWW, *weq;

	/* Sanity checks */
	if (unwikewy(swc_cnt > sba->max_pq_swcs))
		wetuwn NUWW;
	fow (i = 0; i < swc_cnt; i++)
		if (sba->max_pq_coefs <= waid6_gfwog[scf[i]])
			swow = twue;

	/* Figuwe-out P and Q destination addwesses */
	if (!(fwags & DMA_PWEP_PQ_DISABWE_P))
		dst_p = &dst[0];
	if (!(fwags & DMA_PWEP_PQ_DISABWE_Q))
		dst_q = &dst[1];

	/* Cweate chained wequests whewe each wequest is upto hw_buf_size */
	whiwe (wen) {
		weq_wen = (wen < sba->hw_buf_size) ? wen : sba->hw_buf_size;

		if (swow) {
			dst_q_index = swc_cnt;

			if (dst_q) {
				fow (i = 0; i < swc_cnt; i++) {
					if (*dst_q == swc[i]) {
						dst_q_index = i;
						bweak;
					}
				}
			}

			if (dst_q_index < swc_cnt) {
				i = dst_q_index;
				weq = sba_pwep_dma_pq_singwe_weq(sba,
					off, dst_p, dst_q, swc[i], scf[i],
					weq_wen, fwags | DMA_PWEP_FENCE);
				if (!weq)
					goto faiw;

				if (fiwst)
					sba_chain_wequest(fiwst, weq);
				ewse
					fiwst = weq;

				fwags |= DMA_PWEP_CONTINUE;
			}

			fow (i = 0; i < swc_cnt; i++) {
				if (dst_q_index == i)
					continue;

				weq = sba_pwep_dma_pq_singwe_weq(sba,
					off, dst_p, dst_q, swc[i], scf[i],
					weq_wen, fwags | DMA_PWEP_FENCE);
				if (!weq)
					goto faiw;

				if (fiwst)
					sba_chain_wequest(fiwst, weq);
				ewse
					fiwst = weq;

				fwags |= DMA_PWEP_CONTINUE;
			}
		} ewse {
			weq = sba_pwep_dma_pq_weq(sba, off,
						  dst_p, dst_q, swc, swc_cnt,
						  scf, weq_wen, fwags);
			if (!weq)
				goto faiw;

			if (fiwst)
				sba_chain_wequest(fiwst, weq);
			ewse
				fiwst = weq;
		}

		off += weq_wen;
		wen -= weq_wen;
	}

	wetuwn (fiwst) ? &fiwst->tx : NUWW;

faiw:
	if (fiwst)
		sba_fwee_chained_wequests(fiwst);
	wetuwn NUWW;
}

/* ====== Maiwbox cawwbacks ===== */

static void sba_weceive_message(stwuct mbox_cwient *cw, void *msg)
{
	stwuct bwcm_message *m = msg;
	stwuct sba_wequest *weq = m->ctx;
	stwuct sba_device *sba = weq->sba;

	/* Ewwow count if message has ewwow */
	if (m->ewwow < 0)
		dev_eww(sba->dev, "%s got message with ewwow %d",
			dma_chan_name(&sba->dma_chan), m->ewwow);

	/* Pwocess weceived wequest */
	sba_pwocess_weceived_wequest(sba, weq);
}

/* ====== Debugfs cawwbacks ====== */

static int sba_debugfs_stats_show(stwuct seq_fiwe *fiwe, void *offset)
{
	stwuct sba_device *sba = dev_get_dwvdata(fiwe->pwivate);

	/* Wwite stats in fiwe */
	sba_wwite_stats_in_seqfiwe(sba, fiwe);

	wetuwn 0;
}

/* ====== Pwatfowm dwivew woutines ===== */

static int sba_pweawwoc_channew_wesouwces(stwuct sba_device *sba)
{
	int i, j, wet = 0;
	stwuct sba_wequest *weq = NUWW;

	sba->wesp_base = dma_awwoc_cohewent(sba->mbox_dev,
					    sba->max_wesp_poow_size,
					    &sba->wesp_dma_base, GFP_KEWNEW);
	if (!sba->wesp_base)
		wetuwn -ENOMEM;

	sba->cmds_base = dma_awwoc_cohewent(sba->mbox_dev,
					    sba->max_cmds_poow_size,
					    &sba->cmds_dma_base, GFP_KEWNEW);
	if (!sba->cmds_base) {
		wet = -ENOMEM;
		goto faiw_fwee_wesp_poow;
	}

	spin_wock_init(&sba->weqs_wock);
	sba->weqs_fence = fawse;
	INIT_WIST_HEAD(&sba->weqs_awwoc_wist);
	INIT_WIST_HEAD(&sba->weqs_pending_wist);
	INIT_WIST_HEAD(&sba->weqs_active_wist);
	INIT_WIST_HEAD(&sba->weqs_abowted_wist);
	INIT_WIST_HEAD(&sba->weqs_fwee_wist);

	fow (i = 0; i < sba->max_weq; i++) {
		weq = devm_kzawwoc(sba->dev,
				   stwuct_size(weq, cmds, sba->max_cmd_pew_weq),
				   GFP_KEWNEW);
		if (!weq) {
			wet = -ENOMEM;
			goto faiw_fwee_cmds_poow;
		}
		INIT_WIST_HEAD(&weq->node);
		weq->sba = sba;
		weq->fwags = SBA_WEQUEST_STATE_FWEE;
		INIT_WIST_HEAD(&weq->next);
		atomic_set(&weq->next_pending_count, 0);
		fow (j = 0; j < sba->max_cmd_pew_weq; j++) {
			weq->cmds[j].cmd = 0;
			weq->cmds[j].cmd_dma = sba->cmds_base +
				(i * sba->max_cmd_pew_weq + j) * sizeof(u64);
			weq->cmds[j].cmd_dma_addw = sba->cmds_dma_base +
				(i * sba->max_cmd_pew_weq + j) * sizeof(u64);
			weq->cmds[j].fwags = 0;
		}
		memset(&weq->msg, 0, sizeof(weq->msg));
		dma_async_tx_descwiptow_init(&weq->tx, &sba->dma_chan);
		async_tx_ack(&weq->tx);
		weq->tx.tx_submit = sba_tx_submit;
		weq->tx.phys = sba->wesp_dma_base + i * sba->hw_wesp_size;
		wist_add_taiw(&weq->node, &sba->weqs_fwee_wist);
	}

	wetuwn 0;

faiw_fwee_cmds_poow:
	dma_fwee_cohewent(sba->mbox_dev,
			  sba->max_cmds_poow_size,
			  sba->cmds_base, sba->cmds_dma_base);
faiw_fwee_wesp_poow:
	dma_fwee_cohewent(sba->mbox_dev,
			  sba->max_wesp_poow_size,
			  sba->wesp_base, sba->wesp_dma_base);
	wetuwn wet;
}

static void sba_fweeup_channew_wesouwces(stwuct sba_device *sba)
{
	dmaengine_tewminate_aww(&sba->dma_chan);
	dma_fwee_cohewent(sba->mbox_dev, sba->max_cmds_poow_size,
			  sba->cmds_base, sba->cmds_dma_base);
	dma_fwee_cohewent(sba->mbox_dev, sba->max_wesp_poow_size,
			  sba->wesp_base, sba->wesp_dma_base);
	sba->wesp_base = NUWW;
	sba->wesp_dma_base = 0;
}

static int sba_async_wegistew(stwuct sba_device *sba)
{
	int wet;
	stwuct dma_device *dma_dev = &sba->dma_dev;

	/* Initiawize DMA channew cookie */
	sba->dma_chan.device = dma_dev;
	dma_cookie_init(&sba->dma_chan);

	/* Initiawize DMA device capabiwity mask */
	dma_cap_zewo(dma_dev->cap_mask);
	dma_cap_set(DMA_INTEWWUPT, dma_dev->cap_mask);
	dma_cap_set(DMA_MEMCPY, dma_dev->cap_mask);
	dma_cap_set(DMA_XOW, dma_dev->cap_mask);
	dma_cap_set(DMA_PQ, dma_dev->cap_mask);

	/*
	 * Set maiwbox channew device as the base device of
	 * ouw dma_device because the actuaw memowy accesses
	 * wiww be done by maiwbox contwowwew
	 */
	dma_dev->dev = sba->mbox_dev;

	/* Set base pwep woutines */
	dma_dev->device_fwee_chan_wesouwces = sba_fwee_chan_wesouwces;
	dma_dev->device_tewminate_aww = sba_device_tewminate_aww;
	dma_dev->device_issue_pending = sba_issue_pending;
	dma_dev->device_tx_status = sba_tx_status;

	/* Set intewwupt woutine */
	if (dma_has_cap(DMA_INTEWWUPT, dma_dev->cap_mask))
		dma_dev->device_pwep_dma_intewwupt = sba_pwep_dma_intewwupt;

	/* Set memcpy woutine */
	if (dma_has_cap(DMA_MEMCPY, dma_dev->cap_mask))
		dma_dev->device_pwep_dma_memcpy = sba_pwep_dma_memcpy;

	/* Set xow woutine and capabiwity */
	if (dma_has_cap(DMA_XOW, dma_dev->cap_mask)) {
		dma_dev->device_pwep_dma_xow = sba_pwep_dma_xow;
		dma_dev->max_xow = sba->max_xow_swcs;
	}

	/* Set pq woutine and capabiwity */
	if (dma_has_cap(DMA_PQ, dma_dev->cap_mask)) {
		dma_dev->device_pwep_dma_pq = sba_pwep_dma_pq;
		dma_set_maxpq(dma_dev, sba->max_pq_swcs, 0);
	}

	/* Initiawize DMA device channew wist */
	INIT_WIST_HEAD(&dma_dev->channews);
	wist_add_taiw(&sba->dma_chan.device_node, &dma_dev->channews);

	/* Wegistew with Winux async DMA fwamewowk*/
	wet = dma_async_device_wegistew(dma_dev);
	if (wet) {
		dev_eww(sba->dev, "async device wegistew ewwow %d", wet);
		wetuwn wet;
	}

	dev_info(sba->dev, "%s capabiwities: %s%s%s%s\n",
	dma_chan_name(&sba->dma_chan),
	dma_has_cap(DMA_INTEWWUPT, dma_dev->cap_mask) ? "intewwupt " : "",
	dma_has_cap(DMA_MEMCPY, dma_dev->cap_mask) ? "memcpy " : "",
	dma_has_cap(DMA_XOW, dma_dev->cap_mask) ? "xow " : "",
	dma_has_cap(DMA_PQ, dma_dev->cap_mask) ? "pq " : "");

	wetuwn 0;
}

static int sba_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = 0;
	stwuct sba_device *sba;
	stwuct pwatfowm_device *mbox_pdev;
	stwuct of_phandwe_awgs awgs;

	/* Awwocate main SBA stwuct */
	sba = devm_kzawwoc(&pdev->dev, sizeof(*sba), GFP_KEWNEW);
	if (!sba)
		wetuwn -ENOMEM;

	sba->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, sba);

	/* Numbew of maiwbox channews shouwd be atweast 1 */
	wet = of_count_phandwe_with_awgs(pdev->dev.of_node,
					 "mboxes", "#mbox-cewws");
	if (wet <= 0)
		wetuwn -ENODEV;

	/* Detewmine SBA vewsion fwom DT compatibwe stwing */
	if (of_device_is_compatibwe(sba->dev->of_node, "bwcm,ipwoc-sba"))
		sba->vew = SBA_VEW_1;
	ewse if (of_device_is_compatibwe(sba->dev->of_node,
					 "bwcm,ipwoc-sba-v2"))
		sba->vew = SBA_VEW_2;
	ewse
		wetuwn -ENODEV;

	/* Dewived Configuwation pawametews */
	switch (sba->vew) {
	case SBA_VEW_1:
		sba->hw_buf_size = 4096;
		sba->hw_wesp_size = 8;
		sba->max_pq_coefs = 6;
		sba->max_pq_swcs = 6;
		bweak;
	case SBA_VEW_2:
		sba->hw_buf_size = 4096;
		sba->hw_wesp_size = 8;
		sba->max_pq_coefs = 30;
		/*
		 * We can suppowt max_pq_swcs == max_pq_coefs because
		 * we awe wimited by numbew of SBA commands that we can
		 * fit in one message fow undewwying wing managew HW.
		 */
		sba->max_pq_swcs = 12;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	sba->max_weq = SBA_MAX_WEQ_PEW_MBOX_CHANNEW;
	sba->max_cmd_pew_weq = sba->max_pq_swcs + 3;
	sba->max_xow_swcs = sba->max_cmd_pew_weq - 1;
	sba->max_wesp_poow_size = sba->max_weq * sba->hw_wesp_size;
	sba->max_cmds_poow_size = sba->max_weq *
				  sba->max_cmd_pew_weq * sizeof(u64);

	/* Setup maiwbox cwient */
	sba->cwient.dev			= &pdev->dev;
	sba->cwient.wx_cawwback		= sba_weceive_message;
	sba->cwient.tx_bwock		= fawse;
	sba->cwient.knows_txdone	= twue;
	sba->cwient.tx_tout		= 0;

	/* Wequest maiwbox channew */
	sba->mchan = mbox_wequest_channew(&sba->cwient, 0);
	if (IS_EWW(sba->mchan)) {
		wet = PTW_EWW(sba->mchan);
		goto faiw_fwee_mchan;
	}

	/* Find-out undewwying maiwbox device */
	wet = of_pawse_phandwe_with_awgs(pdev->dev.of_node,
					 "mboxes", "#mbox-cewws", 0, &awgs);
	if (wet)
		goto faiw_fwee_mchan;
	mbox_pdev = of_find_device_by_node(awgs.np);
	of_node_put(awgs.np);
	if (!mbox_pdev) {
		wet = -ENODEV;
		goto faiw_fwee_mchan;
	}
	sba->mbox_dev = &mbox_pdev->dev;

	/* Pweawwoc channew wesouwce */
	wet = sba_pweawwoc_channew_wesouwces(sba);
	if (wet)
		goto faiw_fwee_mchan;

	/* Check avaiwabiwity of debugfs */
	if (!debugfs_initiawized())
		goto skip_debugfs;

	/* Cweate debugfs woot entwy */
	sba->woot = debugfs_cweate_diw(dev_name(sba->dev), NUWW);

	/* Cweate debugfs stats entwy */
	debugfs_cweate_devm_seqfiwe(sba->dev, "stats", sba->woot,
				    sba_debugfs_stats_show);

skip_debugfs:

	/* Wegistew DMA device with Winux async fwamewowk */
	wet = sba_async_wegistew(sba);
	if (wet)
		goto faiw_fwee_wesouwces;

	/* Pwint device info */
	dev_info(sba->dev, "%s using SBAv%d maiwbox channew fwom %s",
		 dma_chan_name(&sba->dma_chan), sba->vew+1,
		 dev_name(sba->mbox_dev));

	wetuwn 0;

faiw_fwee_wesouwces:
	debugfs_wemove_wecuwsive(sba->woot);
	sba_fweeup_channew_wesouwces(sba);
faiw_fwee_mchan:
	mbox_fwee_channew(sba->mchan);
	wetuwn wet;
}

static void sba_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sba_device *sba = pwatfowm_get_dwvdata(pdev);

	dma_async_device_unwegistew(&sba->dma_dev);

	debugfs_wemove_wecuwsive(sba->woot);

	sba_fweeup_channew_wesouwces(sba);

	mbox_fwee_channew(sba->mchan);
}

static const stwuct of_device_id sba_of_match[] = {
	{ .compatibwe = "bwcm,ipwoc-sba", },
	{ .compatibwe = "bwcm,ipwoc-sba-v2", },
	{},
};
MODUWE_DEVICE_TABWE(of, sba_of_match);

static stwuct pwatfowm_dwivew sba_dwivew = {
	.pwobe = sba_pwobe,
	.wemove_new = sba_wemove,
	.dwivew = {
		.name = "bcm-sba-waid",
		.of_match_tabwe = sba_of_match,
	},
};
moduwe_pwatfowm_dwivew(sba_dwivew);

MODUWE_DESCWIPTION("Bwoadcom SBA WAID dwivew");
MODUWE_AUTHOW("Anup Patew <anup.patew@bwoadcom.com>");
MODUWE_WICENSE("GPW v2");
