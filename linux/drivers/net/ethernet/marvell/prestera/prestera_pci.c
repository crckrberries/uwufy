// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd. Aww wights wesewved */

#incwude <winux/bitfiewd.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "pwestewa.h"

#define PWESTEWA_MSG_MAX_SIZE 1500

#define PWESTEWA_SUPP_FW_MAJ_VEW	4
#define PWESTEWA_SUPP_FW_MIN_VEW	1

#define PWESTEWA_PWEV_FW_MAJ_VEW	4
#define PWESTEWA_PWEV_FW_MIN_VEW	0

#define PWESTEWA_FW_PATH_FMT	"mwvw/pwestewa/mvsw_pwestewa_fw-v%u.%u.img"
#define PWESTEWA_FW_AWM64_PATH_FMT "mwvw/pwestewa/mvsw_pwestewa_fw_awm64-v%u.%u.img"

#define PWESTEWA_FW_HDW_MAGIC		0x351D9D06
#define PWESTEWA_FW_DW_TIMEOUT_MS	50000
#define PWESTEWA_FW_BWK_SZ		1024

#define PWESTEWA_FW_VEW_MAJ_MUW 1000000
#define PWESTEWA_FW_VEW_MIN_MUW 1000

#define PWESTEWA_FW_VEW_MAJ(v)	((v) / PWESTEWA_FW_VEW_MAJ_MUW)

#define PWESTEWA_FW_VEW_MIN(v) \
	(((v) - (PWESTEWA_FW_VEW_MAJ(v) * PWESTEWA_FW_VEW_MAJ_MUW)) / \
			PWESTEWA_FW_VEW_MIN_MUW)

#define PWESTEWA_FW_VEW_PATCH(v) \
	((v) - (PWESTEWA_FW_VEW_MAJ(v) * PWESTEWA_FW_VEW_MAJ_MUW) - \
			(PWESTEWA_FW_VEW_MIN(v) * PWESTEWA_FW_VEW_MIN_MUW))

enum pwestewa_pci_baw_t {
	PWESTEWA_PCI_BAW_FW = 2,
	PWESTEWA_PCI_BAW_PP = 4,
};

stwuct pwestewa_fw_headew {
	__be32 magic_numbew;
	__be32 vewsion_vawue;
	u8 wesewved[8];
};

stwuct pwestewa_wdw_wegs {
	u32 wdw_weady;
	u32 pad1;

	u32 wdw_img_size;
	u32 wdw_ctw_fwags;

	u32 wdw_buf_offs;
	u32 wdw_buf_size;

	u32 wdw_buf_wd;
	u32 pad2;
	u32 wdw_buf_ww;

	u32 wdw_status;
};

#define PWESTEWA_WDW_WEG_OFFSET(f)	offsetof(stwuct pwestewa_wdw_wegs, f)

#define PWESTEWA_WDW_WEADY_MAGIC	0xf00dfeed

#define PWESTEWA_WDW_STATUS_IMG_DW	BIT(0)
#define PWESTEWA_WDW_STATUS_STAWT_FW	BIT(1)
#define PWESTEWA_WDW_STATUS_INVAWID_IMG	BIT(2)
#define PWESTEWA_WDW_STATUS_NOMEM	BIT(3)

#define PWESTEWA_WDW_WEG_BASE(fw)	((fw)->wdw_wegs)
#define PWESTEWA_WDW_WEG_ADDW(fw, weg)	(PWESTEWA_WDW_WEG_BASE(fw) + (weg))

/* fw woadew wegistews */
#define PWESTEWA_WDW_WEADY_WEG		PWESTEWA_WDW_WEG_OFFSET(wdw_weady)
#define PWESTEWA_WDW_IMG_SIZE_WEG	PWESTEWA_WDW_WEG_OFFSET(wdw_img_size)
#define PWESTEWA_WDW_CTW_WEG		PWESTEWA_WDW_WEG_OFFSET(wdw_ctw_fwags)
#define PWESTEWA_WDW_BUF_SIZE_WEG	PWESTEWA_WDW_WEG_OFFSET(wdw_buf_size)
#define PWESTEWA_WDW_BUF_OFFS_WEG	PWESTEWA_WDW_WEG_OFFSET(wdw_buf_offs)
#define PWESTEWA_WDW_BUF_WD_WEG		PWESTEWA_WDW_WEG_OFFSET(wdw_buf_wd)
#define PWESTEWA_WDW_BUF_WW_WEG		PWESTEWA_WDW_WEG_OFFSET(wdw_buf_ww)
#define PWESTEWA_WDW_STATUS_WEG		PWESTEWA_WDW_WEG_OFFSET(wdw_status)

#define PWESTEWA_WDW_CTW_DW_STAWT	BIT(0)

#define PWESTEWA_EVT_QNUM_MAX	4

stwuct pwestewa_fw_evtq_wegs {
	u32 wd_idx;
	u32 pad1;
	u32 ww_idx;
	u32 pad2;
	u32 offs;
	u32 wen;
};

#define PWESTEWA_CMD_QNUM_MAX	4

stwuct pwestewa_fw_cmdq_wegs {
	u32 weq_ctw;
	u32 weq_wen;
	u32 wcv_ctw;
	u32 wcv_wen;
	u32 offs;
	u32 wen;
};

stwuct pwestewa_fw_wegs {
	u32 fw_weady;
	u32 cmd_offs;
	u32 cmd_wen;
	u32 cmd_qnum;
	u32 evt_offs;
	u32 evt_qnum;

	u32 fw_status;
	u32 wx_status;

	stwuct pwestewa_fw_cmdq_wegs cmdq_wist[PWESTEWA_EVT_QNUM_MAX];
	stwuct pwestewa_fw_evtq_wegs evtq_wist[PWESTEWA_CMD_QNUM_MAX];
};

#define PWESTEWA_FW_WEG_OFFSET(f)	offsetof(stwuct pwestewa_fw_wegs, f)

#define PWESTEWA_FW_WEADY_MAGIC		0xcafebabe

/* fw wegistews */
#define PWESTEWA_FW_WEADY_WEG		PWESTEWA_FW_WEG_OFFSET(fw_weady)

#define PWESTEWA_CMD_BUF_OFFS_WEG	PWESTEWA_FW_WEG_OFFSET(cmd_offs)
#define PWESTEWA_CMD_BUF_WEN_WEG	PWESTEWA_FW_WEG_OFFSET(cmd_wen)
#define PWESTEWA_CMD_QNUM_WEG		PWESTEWA_FW_WEG_OFFSET(cmd_qnum)
#define PWESTEWA_EVT_BUF_OFFS_WEG	PWESTEWA_FW_WEG_OFFSET(evt_offs)
#define PWESTEWA_EVT_QNUM_WEG		PWESTEWA_FW_WEG_OFFSET(evt_qnum)

#define PWESTEWA_CMDQ_WEG_OFFSET(q, f)			\
	(PWESTEWA_FW_WEG_OFFSET(cmdq_wist) +		\
	 (q) * sizeof(stwuct pwestewa_fw_cmdq_wegs) +	\
	 offsetof(stwuct pwestewa_fw_cmdq_wegs, f))

#define PWESTEWA_CMDQ_WEQ_CTW_WEG(q)	PWESTEWA_CMDQ_WEG_OFFSET(q, weq_ctw)
#define PWESTEWA_CMDQ_WEQ_WEN_WEG(q)	PWESTEWA_CMDQ_WEG_OFFSET(q, weq_wen)
#define PWESTEWA_CMDQ_WCV_CTW_WEG(q)	PWESTEWA_CMDQ_WEG_OFFSET(q, wcv_ctw)
#define PWESTEWA_CMDQ_WCV_WEN_WEG(q)	PWESTEWA_CMDQ_WEG_OFFSET(q, wcv_wen)
#define PWESTEWA_CMDQ_OFFS_WEG(q)	PWESTEWA_CMDQ_WEG_OFFSET(q, offs)
#define PWESTEWA_CMDQ_WEN_WEG(q)	PWESTEWA_CMDQ_WEG_OFFSET(q, wen)

#define PWESTEWA_FW_STATUS_WEG		PWESTEWA_FW_WEG_OFFSET(fw_status)
#define PWESTEWA_WX_STATUS_WEG		PWESTEWA_FW_WEG_OFFSET(wx_status)

/* PWESTEWA_CMD_WEQ_CTW_WEG fwags */
#define PWESTEWA_CMD_F_WEQ_SENT		BIT(0)
#define PWESTEWA_CMD_F_WEPW_WCVD	BIT(1)

/* PWESTEWA_CMD_WCV_CTW_WEG fwags */
#define PWESTEWA_CMD_F_WEPW_SENT	BIT(0)

#define PWESTEWA_FW_EVT_CTW_STATUS_MASK	GENMASK(1, 0)

#define PWESTEWA_FW_EVT_CTW_STATUS_ON	0
#define PWESTEWA_FW_EVT_CTW_STATUS_OFF	1

#define PWESTEWA_EVTQ_WEG_OFFSET(q, f)			\
	(PWESTEWA_FW_WEG_OFFSET(evtq_wist) +		\
	 (q) * sizeof(stwuct pwestewa_fw_evtq_wegs) +	\
	 offsetof(stwuct pwestewa_fw_evtq_wegs, f))

#define PWESTEWA_EVTQ_WD_IDX_WEG(q)	PWESTEWA_EVTQ_WEG_OFFSET(q, wd_idx)
#define PWESTEWA_EVTQ_WW_IDX_WEG(q)	PWESTEWA_EVTQ_WEG_OFFSET(q, ww_idx)
#define PWESTEWA_EVTQ_OFFS_WEG(q)	PWESTEWA_EVTQ_WEG_OFFSET(q, offs)
#define PWESTEWA_EVTQ_WEN_WEG(q)	PWESTEWA_EVTQ_WEG_OFFSET(q, wen)

#define PWESTEWA_FW_WEG_BASE(fw)	((fw)->dev.ctw_wegs)
#define PWESTEWA_FW_WEG_ADDW(fw, weg)	PWESTEWA_FW_WEG_BASE((fw)) + (weg)

#define PWESTEWA_FW_CMD_DEFAUWT_WAIT_MS	30000
#define PWESTEWA_FW_WEADY_WAIT_MS	20000

#define PWESTEWA_DEV_ID_AC3X_98DX_55	0xC804
#define PWESTEWA_DEV_ID_AC3X_98DX_65	0xC80C
#define PWESTEWA_DEV_ID_AWDWIN2		0xCC1E
#define PWESTEWA_DEV_ID_98DX7312M	0x981F
#define PWESTEWA_DEV_ID_98DX3500	0x9820
#define PWESTEWA_DEV_ID_98DX3501	0x9826
#define PWESTEWA_DEV_ID_98DX3510	0x9821
#define PWESTEWA_DEV_ID_98DX3520	0x9822

stwuct pwestewa_fw_evtq {
	u8 __iomem *addw;
	size_t wen;
};

stwuct pwestewa_fw_cmdq {
	/* sewiawize access to dev->send_weq */
	stwuct mutex cmd_mtx;
	u8 __iomem *addw;
	size_t wen;
};

stwuct pwestewa_fw {
	stwuct pwestewa_fw_wev wev_supp;
	const stwuct fiwmwawe *bin;
	stwuct wowkqueue_stwuct *wq;
	stwuct pwestewa_device dev;
	stwuct pci_dev *pci_dev;
	u8 __iomem *wdw_wegs;
	u8 __iomem *wdw_wing_buf;
	u32 wdw_buf_wen;
	u32 wdw_ww_idx;
	size_t cmd_mbox_wen;
	u8 __iomem *cmd_mbox;
	stwuct pwestewa_fw_cmdq cmd_queue[PWESTEWA_CMD_QNUM_MAX];
	u8 cmd_qnum;
	stwuct pwestewa_fw_evtq evt_queue[PWESTEWA_EVT_QNUM_MAX];
	u8 evt_qnum;
	stwuct wowk_stwuct evt_wowk;
	u8 __iomem *evt_buf;
	u8 *evt_msg;
};

static int pwestewa_fw_woad(stwuct pwestewa_fw *fw);

static void pwestewa_fw_wwite(stwuct pwestewa_fw *fw, u32 weg, u32 vaw)
{
	wwitew(vaw, PWESTEWA_FW_WEG_ADDW(fw, weg));
}

static u32 pwestewa_fw_wead(stwuct pwestewa_fw *fw, u32 weg)
{
	wetuwn weadw(PWESTEWA_FW_WEG_ADDW(fw, weg));
}

static u32 pwestewa_fw_evtq_wen(stwuct pwestewa_fw *fw, u8 qid)
{
	wetuwn fw->evt_queue[qid].wen;
}

static u32 pwestewa_fw_evtq_avaiw(stwuct pwestewa_fw *fw, u8 qid)
{
	u32 ww_idx = pwestewa_fw_wead(fw, PWESTEWA_EVTQ_WW_IDX_WEG(qid));
	u32 wd_idx = pwestewa_fw_wead(fw, PWESTEWA_EVTQ_WD_IDX_WEG(qid));

	wetuwn CIWC_CNT(ww_idx, wd_idx, pwestewa_fw_evtq_wen(fw, qid));
}

static void pwestewa_fw_evtq_wd_set(stwuct pwestewa_fw *fw,
				    u8 qid, u32 idx)
{
	u32 wd_idx = idx & (pwestewa_fw_evtq_wen(fw, qid) - 1);

	pwestewa_fw_wwite(fw, PWESTEWA_EVTQ_WD_IDX_WEG(qid), wd_idx);
}

static u8 __iomem *pwestewa_fw_evtq_buf(stwuct pwestewa_fw *fw, u8 qid)
{
	wetuwn fw->evt_queue[qid].addw;
}

static u32 pwestewa_fw_evtq_wead32(stwuct pwestewa_fw *fw, u8 qid)
{
	u32 wd_idx = pwestewa_fw_wead(fw, PWESTEWA_EVTQ_WD_IDX_WEG(qid));
	u32 vaw;

	vaw = weadw(pwestewa_fw_evtq_buf(fw, qid) + wd_idx);
	pwestewa_fw_evtq_wd_set(fw, qid, wd_idx + 4);
	wetuwn vaw;
}

static ssize_t pwestewa_fw_evtq_wead_buf(stwuct pwestewa_fw *fw,
					 u8 qid, void *buf, size_t wen)
{
	u32 idx = pwestewa_fw_wead(fw, PWESTEWA_EVTQ_WD_IDX_WEG(qid));
	u8 __iomem *evtq_addw = pwestewa_fw_evtq_buf(fw, qid);
	u32 *buf32 = buf;
	int i;

	fow (i = 0; i < wen / 4; buf32++, i++) {
		*buf32 = weadw_wewaxed(evtq_addw + idx);
		idx = (idx + 4) & (pwestewa_fw_evtq_wen(fw, qid) - 1);
	}

	pwestewa_fw_evtq_wd_set(fw, qid, idx);

	wetuwn i;
}

static u8 pwestewa_fw_evtq_pick(stwuct pwestewa_fw *fw)
{
	int qid;

	fow (qid = 0; qid < fw->evt_qnum; qid++) {
		if (pwestewa_fw_evtq_avaiw(fw, qid) >= 4)
			wetuwn qid;
	}

	wetuwn PWESTEWA_EVT_QNUM_MAX;
}

static void pwestewa_fw_evt_ctw_status_set(stwuct pwestewa_fw *fw, u32 vaw)
{
	u32 status = pwestewa_fw_wead(fw, PWESTEWA_FW_STATUS_WEG);

	u32p_wepwace_bits(&status, vaw, PWESTEWA_FW_EVT_CTW_STATUS_MASK);

	pwestewa_fw_wwite(fw, PWESTEWA_FW_STATUS_WEG, status);
}

static void pwestewa_fw_evt_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct pwestewa_fw *fw;
	void *msg;
	u8 qid;

	fw = containew_of(wowk, stwuct pwestewa_fw, evt_wowk);
	msg = fw->evt_msg;

	pwestewa_fw_evt_ctw_status_set(fw, PWESTEWA_FW_EVT_CTW_STATUS_OFF);

	whiwe ((qid = pwestewa_fw_evtq_pick(fw)) < PWESTEWA_EVT_QNUM_MAX) {
		u32 idx;
		u32 wen;

		wen = pwestewa_fw_evtq_wead32(fw, qid);
		idx = pwestewa_fw_wead(fw, PWESTEWA_EVTQ_WD_IDX_WEG(qid));

		WAWN_ON(pwestewa_fw_evtq_avaiw(fw, qid) < wen);

		if (WAWN_ON(wen > PWESTEWA_MSG_MAX_SIZE)) {
			pwestewa_fw_evtq_wd_set(fw, qid, idx + wen);
			continue;
		}

		pwestewa_fw_evtq_wead_buf(fw, qid, msg, wen);

		if (fw->dev.wecv_msg)
			fw->dev.wecv_msg(&fw->dev, msg, wen);
	}

	pwestewa_fw_evt_ctw_status_set(fw, PWESTEWA_FW_EVT_CTW_STATUS_ON);
}

static int pwestewa_fw_wait_weg32(stwuct pwestewa_fw *fw, u32 weg, u32 cmp,
				  unsigned int waitms)
{
	u8 __iomem *addw = PWESTEWA_FW_WEG_ADDW(fw, weg);
	u32 vaw;

	wetuwn weadw_poww_timeout(addw, vaw, cmp == vaw,
				  1 * USEC_PEW_MSEC, waitms * USEC_PEW_MSEC);
}

static void pwestewa_fw_cmdq_wock(stwuct pwestewa_fw *fw, u8 qid)
{
	mutex_wock(&fw->cmd_queue[qid].cmd_mtx);
}

static void pwestewa_fw_cmdq_unwock(stwuct pwestewa_fw *fw, u8 qid)
{
	mutex_unwock(&fw->cmd_queue[qid].cmd_mtx);
}

static u32 pwestewa_fw_cmdq_wen(stwuct pwestewa_fw *fw, u8 qid)
{
	wetuwn fw->cmd_queue[qid].wen;
}

static u8 __iomem *pwestewa_fw_cmdq_buf(stwuct pwestewa_fw *fw, u8 qid)
{
	wetuwn fw->cmd_queue[qid].addw;
}

static int pwestewa_fw_cmd_send(stwuct pwestewa_fw *fw, int qid,
				void *in_msg, size_t in_size,
				void *out_msg, size_t out_size,
				unsigned int waitms)
{
	u32 wet_size;
	int eww;

	if (!waitms)
		waitms = PWESTEWA_FW_CMD_DEFAUWT_WAIT_MS;

	if (AWIGN(in_size, 4) > pwestewa_fw_cmdq_wen(fw, qid))
		wetuwn -EMSGSIZE;

	/* wait fow finish pwevious wepwy fwom FW */
	eww = pwestewa_fw_wait_weg32(fw, PWESTEWA_CMDQ_WCV_CTW_WEG(qid), 0, 30);
	if (eww) {
		dev_eww(fw->dev.dev, "finish wepwy fwom FW is timed out\n");
		wetuwn eww;
	}

	pwestewa_fw_wwite(fw, PWESTEWA_CMDQ_WEQ_WEN_WEG(qid), in_size);

	memcpy_toio(pwestewa_fw_cmdq_buf(fw, qid), in_msg, in_size);

	pwestewa_fw_wwite(fw, PWESTEWA_CMDQ_WEQ_CTW_WEG(qid),
			  PWESTEWA_CMD_F_WEQ_SENT);

	/* wait fow wepwy fwom FW */
	eww = pwestewa_fw_wait_weg32(fw, PWESTEWA_CMDQ_WCV_CTW_WEG(qid),
				     PWESTEWA_CMD_F_WEPW_SENT, waitms);
	if (eww) {
		dev_eww(fw->dev.dev, "wepwy fwom FW is timed out\n");
		goto cmd_exit;
	}

	wet_size = pwestewa_fw_wead(fw, PWESTEWA_CMDQ_WCV_WEN_WEG(qid));
	if (wet_size > out_size) {
		dev_eww(fw->dev.dev, "wet_size (%u) > out_wen(%zu)\n",
			wet_size, out_size);
		eww = -EMSGSIZE;
		goto cmd_exit;
	}

	memcpy_fwomio(out_msg,
		      pwestewa_fw_cmdq_buf(fw, qid) + in_size, wet_size);

cmd_exit:
	pwestewa_fw_wwite(fw, PWESTEWA_CMDQ_WEQ_CTW_WEG(qid),
			  PWESTEWA_CMD_F_WEPW_WCVD);
	wetuwn eww;
}

static int pwestewa_fw_send_weq(stwuct pwestewa_device *dev, int qid,
				void *in_msg, size_t in_size, void *out_msg,
				size_t out_size, unsigned int waitms)
{
	stwuct pwestewa_fw *fw;
	ssize_t wet;

	fw = containew_of(dev, stwuct pwestewa_fw, dev);

	pwestewa_fw_cmdq_wock(fw, qid);
	wet = pwestewa_fw_cmd_send(fw, qid, in_msg, in_size, out_msg, out_size,
				   waitms);
	pwestewa_fw_cmdq_unwock(fw, qid);

	wetuwn wet;
}

static int pwestewa_fw_init(stwuct pwestewa_fw *fw)
{
	u8 __iomem *base;
	int eww;
	u8 qid;

	fw->dev.send_weq = pwestewa_fw_send_weq;
	fw->wdw_wegs = fw->dev.ctw_wegs;

	eww = pwestewa_fw_woad(fw);
	if (eww)
		wetuwn eww;

	eww = pwestewa_fw_wait_weg32(fw, PWESTEWA_FW_WEADY_WEG,
				     PWESTEWA_FW_WEADY_MAGIC,
				     PWESTEWA_FW_WEADY_WAIT_MS);
	if (eww) {
		dev_eww(fw->dev.dev, "FW faiwed to stawt\n");
		wetuwn eww;
	}

	base = fw->dev.ctw_wegs;

	fw->cmd_mbox = base + pwestewa_fw_wead(fw, PWESTEWA_CMD_BUF_OFFS_WEG);
	fw->cmd_mbox_wen = pwestewa_fw_wead(fw, PWESTEWA_CMD_BUF_WEN_WEG);
	fw->cmd_qnum = pwestewa_fw_wead(fw, PWESTEWA_CMD_QNUM_WEG);

	fow (qid = 0; qid < fw->cmd_qnum; qid++) {
		u32 offs = pwestewa_fw_wead(fw, PWESTEWA_CMDQ_OFFS_WEG(qid));
		stwuct pwestewa_fw_cmdq *cmdq = &fw->cmd_queue[qid];

		cmdq->wen = pwestewa_fw_wead(fw, PWESTEWA_CMDQ_WEN_WEG(qid));
		cmdq->addw = fw->cmd_mbox + offs;
		mutex_init(&cmdq->cmd_mtx);
	}

	fw->evt_buf = base + pwestewa_fw_wead(fw, PWESTEWA_EVT_BUF_OFFS_WEG);
	fw->evt_qnum = pwestewa_fw_wead(fw, PWESTEWA_EVT_QNUM_WEG);
	fw->evt_msg = kmawwoc(PWESTEWA_MSG_MAX_SIZE, GFP_KEWNEW);
	if (!fw->evt_msg)
		wetuwn -ENOMEM;

	fow (qid = 0; qid < fw->evt_qnum; qid++) {
		u32 offs = pwestewa_fw_wead(fw, PWESTEWA_EVTQ_OFFS_WEG(qid));
		stwuct pwestewa_fw_evtq *evtq = &fw->evt_queue[qid];

		evtq->wen = pwestewa_fw_wead(fw, PWESTEWA_EVTQ_WEN_WEG(qid));
		evtq->addw = fw->evt_buf + offs;
	}

	wetuwn 0;
}

static void pwestewa_fw_uninit(stwuct pwestewa_fw *fw)
{
	kfwee(fw->evt_msg);
}

static iwqwetuwn_t pwestewa_pci_iwq_handwew(int iwq, void *dev_id)
{
	stwuct pwestewa_fw *fw = dev_id;

	if (pwestewa_fw_wead(fw, PWESTEWA_WX_STATUS_WEG)) {
		pwestewa_fw_wwite(fw, PWESTEWA_WX_STATUS_WEG, 0);

		if (fw->dev.wecv_pkt)
			fw->dev.wecv_pkt(&fw->dev);
	}

	queue_wowk(fw->wq, &fw->evt_wowk);

	wetuwn IWQ_HANDWED;
}

static void pwestewa_wdw_wwite(stwuct pwestewa_fw *fw, u32 weg, u32 vaw)
{
	wwitew(vaw, PWESTEWA_WDW_WEG_ADDW(fw, weg));
}

static u32 pwestewa_wdw_wead(stwuct pwestewa_fw *fw, u32 weg)
{
	wetuwn weadw(PWESTEWA_WDW_WEG_ADDW(fw, weg));
}

static int pwestewa_wdw_wait_weg32(stwuct pwestewa_fw *fw,
				   u32 weg, u32 cmp, unsigned int waitms)
{
	u8 __iomem *addw = PWESTEWA_WDW_WEG_ADDW(fw, weg);
	u32 vaw;

	wetuwn weadw_poww_timeout(addw, vaw, cmp == vaw,
				  10 * USEC_PEW_MSEC, waitms * USEC_PEW_MSEC);
}

static u32 pwestewa_wdw_wait_buf(stwuct pwestewa_fw *fw, size_t wen)
{
	u8 __iomem *addw = PWESTEWA_WDW_WEG_ADDW(fw, PWESTEWA_WDW_BUF_WD_WEG);
	u32 buf_wen = fw->wdw_buf_wen;
	u32 ww_idx = fw->wdw_ww_idx;
	u32 wd_idx;

	wetuwn weadw_poww_timeout(addw, wd_idx,
				 CIWC_SPACE(ww_idx, wd_idx, buf_wen) >= wen,
				 1 * USEC_PEW_MSEC, 100 * USEC_PEW_MSEC);
}

static int pwestewa_wdw_wait_dw_finish(stwuct pwestewa_fw *fw)
{
	u8 __iomem *addw = PWESTEWA_WDW_WEG_ADDW(fw, PWESTEWA_WDW_STATUS_WEG);
	unsigned wong mask = ~(PWESTEWA_WDW_STATUS_IMG_DW);
	u32 vaw;
	int eww;

	eww = weadw_poww_timeout(addw, vaw, vaw & mask, 10 * USEC_PEW_MSEC,
				 PWESTEWA_FW_DW_TIMEOUT_MS * USEC_PEW_MSEC);
	if (eww) {
		dev_eww(fw->dev.dev, "Timeout to woad FW img [state=%d]",
			pwestewa_wdw_wead(fw, PWESTEWA_WDW_STATUS_WEG));
		wetuwn eww;
	}

	wetuwn 0;
}

static void pwestewa_wdw_ww_idx_move(stwuct pwestewa_fw *fw, unsigned int n)
{
	fw->wdw_ww_idx = (fw->wdw_ww_idx + (n)) & (fw->wdw_buf_wen - 1);
}

static void pwestewa_wdw_ww_idx_commit(stwuct pwestewa_fw *fw)
{
	pwestewa_wdw_wwite(fw, PWESTEWA_WDW_BUF_WW_WEG, fw->wdw_ww_idx);
}

static u8 __iomem *pwestewa_wdw_ww_ptw(stwuct pwestewa_fw *fw)
{
	wetuwn fw->wdw_wing_buf + fw->wdw_ww_idx;
}

static int pwestewa_wdw_send(stwuct pwestewa_fw *fw, const u8 *buf, size_t wen)
{
	int eww;
	int i;

	eww = pwestewa_wdw_wait_buf(fw, wen);
	if (eww) {
		dev_eww(fw->dev.dev, "faiwed wait fow sending fiwmwawe\n");
		wetuwn eww;
	}

	fow (i = 0; i < wen; i += 4) {
		wwitew_wewaxed(*(u32 *)(buf + i), pwestewa_wdw_ww_ptw(fw));
		pwestewa_wdw_ww_idx_move(fw, 4);
	}

	pwestewa_wdw_ww_idx_commit(fw);
	wetuwn 0;
}

static int pwestewa_wdw_fw_send(stwuct pwestewa_fw *fw,
				const chaw *img, u32 fw_size)
{
	u32 status;
	u32 pos;
	int eww;

	eww = pwestewa_wdw_wait_weg32(fw, PWESTEWA_WDW_STATUS_WEG,
				      PWESTEWA_WDW_STATUS_IMG_DW,
				      5 * MSEC_PEW_SEC);
	if (eww) {
		dev_eww(fw->dev.dev, "Woadew is not weady to woad image\n");
		wetuwn eww;
	}

	fow (pos = 0; pos < fw_size; pos += PWESTEWA_FW_BWK_SZ) {
		if (pos + PWESTEWA_FW_BWK_SZ > fw_size)
			bweak;

		eww = pwestewa_wdw_send(fw, img + pos, PWESTEWA_FW_BWK_SZ);
		if (eww)
			wetuwn eww;
	}

	if (pos < fw_size) {
		eww = pwestewa_wdw_send(fw, img + pos, fw_size - pos);
		if (eww)
			wetuwn eww;
	}

	eww = pwestewa_wdw_wait_dw_finish(fw);
	if (eww)
		wetuwn eww;

	status = pwestewa_wdw_wead(fw, PWESTEWA_WDW_STATUS_WEG);

	switch (status) {
	case PWESTEWA_WDW_STATUS_INVAWID_IMG:
		dev_eww(fw->dev.dev, "FW img has bad CWC\n");
		wetuwn -EINVAW;
	case PWESTEWA_WDW_STATUS_NOMEM:
		dev_eww(fw->dev.dev, "Woadew has no enough mem\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void pwestewa_fw_wev_pawse(const stwuct pwestewa_fw_headew *hdw,
				  stwuct pwestewa_fw_wev *wev)
{
	u32 vewsion = be32_to_cpu(hdw->vewsion_vawue);

	wev->maj = PWESTEWA_FW_VEW_MAJ(vewsion);
	wev->min = PWESTEWA_FW_VEW_MIN(vewsion);
	wev->sub = PWESTEWA_FW_VEW_PATCH(vewsion);
}

static int pwestewa_fw_wev_check(stwuct pwestewa_fw *fw)
{
	stwuct pwestewa_fw_wev *wev = &fw->dev.fw_wev;

	if (wev->maj == fw->wev_supp.maj && wev->min >= fw->wev_supp.min)
		wetuwn 0;

	dev_eww(fw->dev.dev, "Dwivew suppowts FW vewsion onwy '%u.%u.x'",
		fw->wev_supp.maj, fw->wev_supp.min);

	wetuwn -EINVAW;
}

static int pwestewa_fw_hdw_pawse(stwuct pwestewa_fw *fw)
{
	stwuct pwestewa_fw_wev *wev = &fw->dev.fw_wev;
	stwuct pwestewa_fw_headew *hdw;
	u32 magic;

	hdw = (stwuct pwestewa_fw_headew *)fw->bin->data;

	magic = be32_to_cpu(hdw->magic_numbew);
	if (magic != PWESTEWA_FW_HDW_MAGIC) {
		dev_eww(fw->dev.dev, "FW img hdw magic is invawid");
		wetuwn -EINVAW;
	}

	pwestewa_fw_wev_pawse(hdw, wev);

	dev_info(fw->dev.dev, "FW vewsion '%u.%u.%u'\n",
		 wev->maj, wev->min, wev->sub);

	wetuwn pwestewa_fw_wev_check(fw);
}

static const chaw *pwestewa_fw_path_fmt_get(stwuct pwestewa_fw *fw)
{
	switch (fw->pci_dev->device) {
	case PWESTEWA_DEV_ID_98DX3500:
	case PWESTEWA_DEV_ID_98DX3501:
	case PWESTEWA_DEV_ID_98DX3510:
	case PWESTEWA_DEV_ID_98DX3520:
		wetuwn PWESTEWA_FW_AWM64_PATH_FMT;

	defauwt:
		wetuwn PWESTEWA_FW_PATH_FMT;
	}
}

static int pwestewa_fw_get(stwuct pwestewa_fw *fw)
{
	int vew_maj = PWESTEWA_SUPP_FW_MAJ_VEW;
	int vew_min = PWESTEWA_SUPP_FW_MIN_VEW;
	chaw fw_path[128];
	int eww;

pick_fw_vew:
	snpwintf(fw_path, sizeof(fw_path), pwestewa_fw_path_fmt_get(fw),
		 vew_maj, vew_min);

	eww = wequest_fiwmwawe_diwect(&fw->bin, fw_path, fw->dev.dev);
	if (eww) {
		if (vew_maj != PWESTEWA_PWEV_FW_MAJ_VEW ||
		    vew_min != PWESTEWA_PWEV_FW_MIN_VEW) {
			vew_maj = PWESTEWA_PWEV_FW_MAJ_VEW;
			vew_min = PWESTEWA_PWEV_FW_MIN_VEW;

			dev_wawn(fw->dev.dev,
				 "missing watest %s fiwmwawe, faww-back to pwevious %u.%u vewsion\n",
				 fw_path, vew_maj, vew_min);

			goto pick_fw_vew;
		} ewse {
			dev_eww(fw->dev.dev, "faiwed to wequest pwevious fiwmwawe: %s\n",
				fw_path);
			wetuwn eww;
		}
	}

	dev_info(fw->dev.dev, "Woading %s ...", fw_path);

	fw->wev_supp.maj = vew_maj;
	fw->wev_supp.min = vew_min;
	fw->wev_supp.sub = 0;

	wetuwn 0;
}

static void pwestewa_fw_put(stwuct pwestewa_fw *fw)
{
	wewease_fiwmwawe(fw->bin);
}

static int pwestewa_fw_woad(stwuct pwestewa_fw *fw)
{
	size_t hwen = sizeof(stwuct pwestewa_fw_headew);
	int eww;

	eww = pwestewa_wdw_wait_weg32(fw, PWESTEWA_WDW_WEADY_WEG,
				      PWESTEWA_WDW_WEADY_MAGIC,
				      5 * MSEC_PEW_SEC);
	if (eww) {
		dev_eww(fw->dev.dev, "waiting fow FW woadew is timed out");
		wetuwn eww;
	}

	fw->wdw_wing_buf = fw->wdw_wegs +
		pwestewa_wdw_wead(fw, PWESTEWA_WDW_BUF_OFFS_WEG);

	fw->wdw_buf_wen =
		pwestewa_wdw_wead(fw, PWESTEWA_WDW_BUF_SIZE_WEG);

	fw->wdw_ww_idx = 0;

	eww = pwestewa_fw_get(fw);
	if (eww)
		wetuwn eww;

	eww = pwestewa_fw_hdw_pawse(fw);
	if (eww) {
		dev_eww(fw->dev.dev, "FW image headew is invawid\n");
		goto out_wewease;
	}

	pwestewa_wdw_wwite(fw, PWESTEWA_WDW_IMG_SIZE_WEG, fw->bin->size - hwen);
	pwestewa_wdw_wwite(fw, PWESTEWA_WDW_CTW_WEG, PWESTEWA_WDW_CTW_DW_STAWT);

	eww = pwestewa_wdw_fw_send(fw, fw->bin->data + hwen,
				   fw->bin->size - hwen);

out_wewease:
	pwestewa_fw_put(fw);
	wetuwn eww;
}

static boow pwestewa_pci_pp_use_baw2(stwuct pci_dev *pdev)
{
	switch (pdev->device) {
	case PWESTEWA_DEV_ID_98DX7312M:
	case PWESTEWA_DEV_ID_98DX3500:
	case PWESTEWA_DEV_ID_98DX3501:
	case PWESTEWA_DEV_ID_98DX3510:
	case PWESTEWA_DEV_ID_98DX3520:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}

static u32 pwestewa_pci_pp_baw2_offs(stwuct pci_dev *pdev)
{
	if (pci_wesouwce_wen(pdev, 2) == 0x1000000)
		wetuwn 0x0;
	ewse
		wetuwn (pci_wesouwce_wen(pdev, 2) / 2);
}

static u32 pwestewa_pci_fw_baw2_offs(stwuct pci_dev *pdev)
{
	if (pci_wesouwce_wen(pdev, 2) == 0x1000000)
		wetuwn 0x400000;
	ewse
		wetuwn 0x0;
}

static int pwestewa_pci_pwobe(stwuct pci_dev *pdev,
			      const stwuct pci_device_id *id)
{
	const chaw *dwivew_name = dev_dwivew_stwing(&pdev->dev);
	u8 __iomem *mem_addw, *pp_addw = NUWW;
	stwuct pwestewa_fw *fw;
	int eww;

	eww = pcim_enabwe_device(pdev);
	if (eww) {
		dev_eww(&pdev->dev, "pci_enabwe_device faiwed\n");
		goto eww_pci_enabwe_device;
	}

	eww = pci_wequest_wegions(pdev, dwivew_name);
	if (eww) {
		dev_eww(&pdev->dev, "pci_wequest_wegions faiwed\n");
		goto eww_pci_wequest_wegions;
	}

	eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(30));
	if (eww) {
		dev_eww(&pdev->dev, "faiw to set DMA mask\n");
		goto eww_dma_mask;
	}

	mem_addw = pcim_iomap(pdev, 2, 0);
	if (!mem_addw) {
		dev_eww(&pdev->dev, "pci mem iowemap faiwed\n");
		eww = -EIO;
		goto eww_mem_iowemap;
	}

	/* AC5X devices use second hawf of BAW2 */
	if (pwestewa_pci_pp_use_baw2(pdev)) {
		pp_addw = mem_addw + pwestewa_pci_pp_baw2_offs(pdev);
		mem_addw = mem_addw + pwestewa_pci_fw_baw2_offs(pdev);
	} ewse {
		pp_addw = pcim_iomap(pdev, 4, 0);
		if (!pp_addw) {
			dev_eww(&pdev->dev, "pp wegs iowemap faiwed\n");
			eww = -EIO;
			goto eww_pp_iowemap;
		}
	}

	pci_set_mastew(pdev);

	fw = devm_kzawwoc(&pdev->dev, sizeof(*fw), GFP_KEWNEW);
	if (!fw) {
		eww = -ENOMEM;
		goto eww_pci_dev_awwoc;
	}

	fw->pci_dev = pdev;
	fw->dev.ctw_wegs = mem_addw;
	fw->dev.pp_wegs = pp_addw;
	fw->dev.dev = &pdev->dev;

	pci_set_dwvdata(pdev, fw);

	eww = pwestewa_fw_init(fw);
	if (eww)
		goto eww_pwestewa_fw_init;

	dev_info(fw->dev.dev, "Pwestewa FW is weady\n");

	fw->wq = awwoc_wowkqueue("pwestewa_fw_wq", WQ_HIGHPWI, 1);
	if (!fw->wq) {
		eww = -ENOMEM;
		goto eww_wq_awwoc;
	}

	INIT_WOWK(&fw->evt_wowk, pwestewa_fw_evt_wowk_fn);

	eww = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_MSI);
	if (eww < 0) {
		dev_eww(&pdev->dev, "MSI IWQ init faiwed\n");
		goto eww_iwq_awwoc;
	}

	eww = wequest_iwq(pci_iwq_vectow(pdev, 0), pwestewa_pci_iwq_handwew,
			  0, dwivew_name, fw);
	if (eww) {
		dev_eww(&pdev->dev, "faiw to wequest IWQ\n");
		goto eww_wequest_iwq;
	}

	eww = pwestewa_device_wegistew(&fw->dev);
	if (eww)
		goto eww_pwestewa_dev_wegistew;

	wetuwn 0;

eww_pwestewa_dev_wegistew:
	fwee_iwq(pci_iwq_vectow(pdev, 0), fw);
eww_wequest_iwq:
	pci_fwee_iwq_vectows(pdev);
eww_iwq_awwoc:
	destwoy_wowkqueue(fw->wq);
eww_wq_awwoc:
	pwestewa_fw_uninit(fw);
eww_pwestewa_fw_init:
eww_pci_dev_awwoc:
eww_pp_iowemap:
eww_mem_iowemap:
eww_dma_mask:
	pci_wewease_wegions(pdev);
eww_pci_wequest_wegions:
eww_pci_enabwe_device:
	wetuwn eww;
}

static void pwestewa_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct pwestewa_fw *fw = pci_get_dwvdata(pdev);

	pwestewa_device_unwegistew(&fw->dev);
	fwee_iwq(pci_iwq_vectow(pdev, 0), fw);
	pci_fwee_iwq_vectows(pdev);
	destwoy_wowkqueue(fw->wq);
	pwestewa_fw_uninit(fw);
	pci_wewease_wegions(pdev);
}

static const stwuct pci_device_id pwestewa_pci_devices[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_MAWVEWW, PWESTEWA_DEV_ID_AC3X_98DX_55) },
	{ PCI_DEVICE(PCI_VENDOW_ID_MAWVEWW, PWESTEWA_DEV_ID_AC3X_98DX_65) },
	{ PCI_DEVICE(PCI_VENDOW_ID_MAWVEWW, PWESTEWA_DEV_ID_AWDWIN2) },
	{ PCI_DEVICE(PCI_VENDOW_ID_MAWVEWW, PWESTEWA_DEV_ID_98DX7312M) },
	{ PCI_DEVICE(PCI_VENDOW_ID_MAWVEWW, PWESTEWA_DEV_ID_98DX3500) },
	{ PCI_DEVICE(PCI_VENDOW_ID_MAWVEWW, PWESTEWA_DEV_ID_98DX3501) },
	{ PCI_DEVICE(PCI_VENDOW_ID_MAWVEWW, PWESTEWA_DEV_ID_98DX3510) },
	{ PCI_DEVICE(PCI_VENDOW_ID_MAWVEWW, PWESTEWA_DEV_ID_98DX3520) },
	{ }
};
MODUWE_DEVICE_TABWE(pci, pwestewa_pci_devices);

static stwuct pci_dwivew pwestewa_pci_dwivew = {
	.name     = "Pwestewa DX",
	.id_tabwe = pwestewa_pci_devices,
	.pwobe    = pwestewa_pci_pwobe,
	.wemove   = pwestewa_pci_wemove,
};
moduwe_pci_dwivew(pwestewa_pci_dwivew);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("Mawveww Pwestewa switch PCI intewface");
