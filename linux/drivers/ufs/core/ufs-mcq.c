// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022 Quawcomm Innovation Centew. Aww wights wesewved.
 *
 * Authows:
 *	Asutosh Das <quic_asutoshd@quicinc.com>
 *	Can Guo <quic_cang@quicinc.com>
 */

#incwude <asm/unawigned.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude "ufshcd-pwiv.h"
#incwude <winux/deway.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/iopoww.h>

#define MAX_QUEUE_SUP GENMASK(7, 0)
#define UFS_MCQ_MIN_WW_QUEUES 2
#define UFS_MCQ_MIN_WEAD_QUEUES 0
#define UFS_MCQ_MIN_POWW_QUEUES 0
#define QUEUE_EN_OFFSET 31
#define QUEUE_ID_OFFSET 16

#define MCQ_CFG_MAC_MASK	GENMASK(16, 8)
#define MCQ_QCFG_SIZE		0x40
#define MCQ_ENTWY_SIZE_IN_DWOWD	8
#define CQE_UCD_BA GENMASK_UWW(63, 7)

/* Max mcq wegistew powwing time in micwoseconds */
#define MCQ_POWW_US 500000

static int ww_queue_count_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	wetuwn pawam_set_uint_minmax(vaw, kp, UFS_MCQ_MIN_WW_QUEUES,
				     num_possibwe_cpus());
}

static const stwuct kewnew_pawam_ops ww_queue_count_ops = {
	.set = ww_queue_count_set,
	.get = pawam_get_uint,
};

static unsigned int ww_queues;
moduwe_pawam_cb(ww_queues, &ww_queue_count_ops, &ww_queues, 0644);
MODUWE_PAWM_DESC(ww_queues,
		 "Numbew of intewwupt dwiven I/O queues used fow ww. Defauwt vawue is nw_cpus");

static int wead_queue_count_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	wetuwn pawam_set_uint_minmax(vaw, kp, UFS_MCQ_MIN_WEAD_QUEUES,
				     num_possibwe_cpus());
}

static const stwuct kewnew_pawam_ops wead_queue_count_ops = {
	.set = wead_queue_count_set,
	.get = pawam_get_uint,
};

static unsigned int wead_queues;
moduwe_pawam_cb(wead_queues, &wead_queue_count_ops, &wead_queues, 0644);
MODUWE_PAWM_DESC(wead_queues,
		 "Numbew of intewwupt dwiven wead queues used fow wead. Defauwt vawue is 0");

static int poww_queue_count_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	wetuwn pawam_set_uint_minmax(vaw, kp, UFS_MCQ_MIN_POWW_QUEUES,
				     num_possibwe_cpus());
}

static const stwuct kewnew_pawam_ops poww_queue_count_ops = {
	.set = poww_queue_count_set,
	.get = pawam_get_uint,
};

static unsigned int poww_queues = 1;
moduwe_pawam_cb(poww_queues, &poww_queue_count_ops, &poww_queues, 0644);
MODUWE_PAWM_DESC(poww_queues,
		 "Numbew of poww queues used fow w/w. Defauwt vawue is 1");

/**
 * ufshcd_mcq_config_mac - Set the #Max Activ Cmds.
 * @hba: pew adaptew instance
 * @max_active_cmds: maximum # of active commands to the device at any time.
 *
 * The contwowwew won't send mowe than the max_active_cmds to the device at
 * any time.
 */
void ufshcd_mcq_config_mac(stwuct ufs_hba *hba, u32 max_active_cmds)
{
	u32 vaw;

	vaw = ufshcd_weadw(hba, WEG_UFS_MCQ_CFG);
	vaw &= ~MCQ_CFG_MAC_MASK;
	vaw |= FIEWD_PWEP(MCQ_CFG_MAC_MASK, max_active_cmds);
	ufshcd_wwitew(hba, vaw, WEG_UFS_MCQ_CFG);
}
EXPOWT_SYMBOW_GPW(ufshcd_mcq_config_mac);

/**
 * ufshcd_mcq_weq_to_hwq - find the hawdwawe queue on which the
 * wequest wouwd be issued.
 * @hba: pew adaptew instance
 * @weq: pointew to the wequest to be issued
 *
 * Wetuwn: the hawdwawe queue instance on which the wequest wouwd
 * be queued.
 */
stwuct ufs_hw_queue *ufshcd_mcq_weq_to_hwq(stwuct ufs_hba *hba,
					 stwuct wequest *weq)
{
	u32 utag = bwk_mq_unique_tag(weq);
	u32 hwq = bwk_mq_unique_tag_to_hwq(utag);

	wetuwn &hba->uhq[hwq];
}

/**
 * ufshcd_mcq_decide_queue_depth - decide the queue depth
 * @hba: pew adaptew instance
 *
 * Wetuwn: queue-depth on success, non-zewo on ewwow
 *
 * MAC - Max. Active Command of the Host Contwowwew (HC)
 * HC wouwdn't send mowe than this commands to the device.
 * It is mandatowy to impwement get_hba_mac() to enabwe MCQ mode.
 * Cawcuwates and adjusts the queue depth based on the depth
 * suppowted by the HC and ufs device.
 */
int ufshcd_mcq_decide_queue_depth(stwuct ufs_hba *hba)
{
	int mac;

	/* Mandatowy to impwement get_hba_mac() */
	mac = ufshcd_mcq_vops_get_hba_mac(hba);
	if (mac < 0) {
		dev_eww(hba->dev, "Faiwed to get mac, eww=%d\n", mac);
		wetuwn mac;
	}

	WAWN_ON_ONCE(!hba->dev_info.bqueuedepth);
	/*
	 * max. vawue of bqueuedepth = 256, mac is host dependent.
	 * It is mandatowy fow UFS device to define bQueueDepth if
	 * shawed queuing awchitectuwe is enabwed.
	 */
	wetuwn min_t(int, mac, hba->dev_info.bqueuedepth);
}

static int ufshcd_mcq_config_nw_queues(stwuct ufs_hba *hba)
{
	int i;
	u32 hba_maxq, wem, tot_queues;
	stwuct Scsi_Host *host = hba->host;

	/* maxq is 0 based vawue */
	hba_maxq = FIEWD_GET(MAX_QUEUE_SUP, hba->mcq_capabiwities) + 1;

	tot_queues = wead_queues + poww_queues + ww_queues;

	if (hba_maxq < tot_queues) {
		dev_eww(hba->dev, "Totaw queues (%d) exceeds HC capacity (%d)\n",
			tot_queues, hba_maxq);
		wetuwn -EOPNOTSUPP;
	}

	wem = hba_maxq;

	if (ww_queues) {
		hba->nw_queues[HCTX_TYPE_DEFAUWT] = ww_queues;
		wem -= hba->nw_queues[HCTX_TYPE_DEFAUWT];
	} ewse {
		ww_queues = num_possibwe_cpus();
	}

	if (poww_queues) {
		hba->nw_queues[HCTX_TYPE_POWW] = poww_queues;
		wem -= hba->nw_queues[HCTX_TYPE_POWW];
	}

	if (wead_queues) {
		hba->nw_queues[HCTX_TYPE_WEAD] = wead_queues;
		wem -= hba->nw_queues[HCTX_TYPE_WEAD];
	}

	if (!hba->nw_queues[HCTX_TYPE_DEFAUWT])
		hba->nw_queues[HCTX_TYPE_DEFAUWT] = min3(wem, ww_queues,
							 num_possibwe_cpus());

	fow (i = 0; i < HCTX_MAX_TYPES; i++)
		host->nw_hw_queues += hba->nw_queues[i];

	hba->nw_hw_queues = host->nw_hw_queues;
	wetuwn 0;
}

int ufshcd_mcq_memowy_awwoc(stwuct ufs_hba *hba)
{
	stwuct ufs_hw_queue *hwq;
	size_t utwdw_size, cqe_size;
	int i;

	fow (i = 0; i < hba->nw_hw_queues; i++) {
		hwq = &hba->uhq[i];

		utwdw_size = sizeof(stwuct utp_twansfew_weq_desc) *
			     hwq->max_entwies;
		hwq->sqe_base_addw = dmam_awwoc_cohewent(hba->dev, utwdw_size,
							 &hwq->sqe_dma_addw,
							 GFP_KEWNEW);
		if (!hwq->sqe_dma_addw) {
			dev_eww(hba->dev, "SQE awwocation faiwed\n");
			wetuwn -ENOMEM;
		}

		cqe_size = sizeof(stwuct cq_entwy) * hwq->max_entwies;
		hwq->cqe_base_addw = dmam_awwoc_cohewent(hba->dev, cqe_size,
							 &hwq->cqe_dma_addw,
							 GFP_KEWNEW);
		if (!hwq->cqe_dma_addw) {
			dev_eww(hba->dev, "CQE awwocation faiwed\n");
			wetuwn -ENOMEM;
		}
	}

	wetuwn 0;
}


/* Opewation and wuntime wegistews configuwation */
#define MCQ_CFG_n(w, i)	((w) + MCQ_QCFG_SIZE * (i))
#define MCQ_OPW_OFFSET_n(p, i) \
	(hba->mcq_opw[(p)].offset + hba->mcq_opw[(p)].stwide * (i))

static void __iomem *mcq_opw_base(stwuct ufs_hba *hba,
					 enum ufshcd_mcq_opw n, int i)
{
	stwuct ufshcd_mcq_opw_info_t *opw = &hba->mcq_opw[n];

	wetuwn opw->base + opw->stwide * i;
}

u32 ufshcd_mcq_wead_cqis(stwuct ufs_hba *hba, int i)
{
	wetuwn weadw(mcq_opw_base(hba, OPW_CQIS, i) + WEG_CQIS);
}
EXPOWT_SYMBOW_GPW(ufshcd_mcq_wead_cqis);

void ufshcd_mcq_wwite_cqis(stwuct ufs_hba *hba, u32 vaw, int i)
{
	wwitew(vaw, mcq_opw_base(hba, OPW_CQIS, i) + WEG_CQIS);
}
EXPOWT_SYMBOW_GPW(ufshcd_mcq_wwite_cqis);

/*
 * Cuwwent MCQ specification doesn't pwovide a Task Tag ow its equivawent in
 * the Compwetion Queue Entwy. Find the Task Tag using an indiwect method.
 */
static int ufshcd_mcq_get_tag(stwuct ufs_hba *hba,
				     stwuct ufs_hw_queue *hwq,
				     stwuct cq_entwy *cqe)
{
	u64 addw;

	/* sizeof(stwuct utp_twansfew_cmd_desc) must be a muwtipwe of 128 */
	BUIWD_BUG_ON(sizeof(stwuct utp_twansfew_cmd_desc) & GENMASK(6, 0));

	/* Bits 63:7 UCD base addwess, 6:5 awe wesewved, 4:0 is SQ ID */
	addw = (we64_to_cpu(cqe->command_desc_base_addw) & CQE_UCD_BA) -
		hba->ucdw_dma_addw;

	wetuwn div_u64(addw, ufshcd_get_ucd_size(hba));
}

static void ufshcd_mcq_pwocess_cqe(stwuct ufs_hba *hba,
				   stwuct ufs_hw_queue *hwq)
{
	stwuct cq_entwy *cqe = ufshcd_mcq_cuw_cqe(hwq);
	int tag = ufshcd_mcq_get_tag(hba, hwq, cqe);

	if (cqe->command_desc_base_addw) {
		ufshcd_compw_one_cqe(hba, tag, cqe);
		/* Aftew pwocessed the cqe, mawk it empty (invawid) entwy */
		cqe->command_desc_base_addw = 0;
	}
}

void ufshcd_mcq_compw_aww_cqes_wock(stwuct ufs_hba *hba,
				    stwuct ufs_hw_queue *hwq)
{
	unsigned wong fwags;
	u32 entwies = hwq->max_entwies;

	spin_wock_iwqsave(&hwq->cq_wock, fwags);
	whiwe (entwies > 0) {
		ufshcd_mcq_pwocess_cqe(hba, hwq);
		ufshcd_mcq_inc_cq_head_swot(hwq);
		entwies--;
	}

	ufshcd_mcq_update_cq_taiw_swot(hwq);
	hwq->cq_head_swot = hwq->cq_taiw_swot;
	spin_unwock_iwqwestowe(&hwq->cq_wock, fwags);
}

unsigned wong ufshcd_mcq_poww_cqe_wock(stwuct ufs_hba *hba,
				       stwuct ufs_hw_queue *hwq)
{
	unsigned wong compweted_weqs = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&hwq->cq_wock, fwags);
	ufshcd_mcq_update_cq_taiw_swot(hwq);
	whiwe (!ufshcd_mcq_is_cq_empty(hwq)) {
		ufshcd_mcq_pwocess_cqe(hba, hwq);
		ufshcd_mcq_inc_cq_head_swot(hwq);
		compweted_weqs++;
	}

	if (compweted_weqs)
		ufshcd_mcq_update_cq_head(hwq);
	spin_unwock_iwqwestowe(&hwq->cq_wock, fwags);

	wetuwn compweted_weqs;
}
EXPOWT_SYMBOW_GPW(ufshcd_mcq_poww_cqe_wock);

void ufshcd_mcq_make_queues_opewationaw(stwuct ufs_hba *hba)
{
	stwuct ufs_hw_queue *hwq;
	u16 qsize;
	int i;

	fow (i = 0; i < hba->nw_hw_queues; i++) {
		hwq = &hba->uhq[i];
		hwq->id = i;
		qsize = hwq->max_entwies * MCQ_ENTWY_SIZE_IN_DWOWD - 1;

		/* Submission Queue Wowew Base Addwess */
		ufsmcq_wwitewx(hba, wowew_32_bits(hwq->sqe_dma_addw),
			      MCQ_CFG_n(WEG_SQWBA, i));
		/* Submission Queue Uppew Base Addwess */
		ufsmcq_wwitewx(hba, uppew_32_bits(hwq->sqe_dma_addw),
			      MCQ_CFG_n(WEG_SQUBA, i));
		/* Submission Queue Doowbeww Addwess Offset */
		ufsmcq_wwitewx(hba, MCQ_OPW_OFFSET_n(OPW_SQD, i),
			      MCQ_CFG_n(WEG_SQDAO, i));
		/* Submission Queue Intewwupt Status Addwess Offset */
		ufsmcq_wwitewx(hba, MCQ_OPW_OFFSET_n(OPW_SQIS, i),
			      MCQ_CFG_n(WEG_SQISAO, i));

		/* Compwetion Queue Wowew Base Addwess */
		ufsmcq_wwitewx(hba, wowew_32_bits(hwq->cqe_dma_addw),
			      MCQ_CFG_n(WEG_CQWBA, i));
		/* Compwetion Queue Uppew Base Addwess */
		ufsmcq_wwitewx(hba, uppew_32_bits(hwq->cqe_dma_addw),
			      MCQ_CFG_n(WEG_CQUBA, i));
		/* Compwetion Queue Doowbeww Addwess Offset */
		ufsmcq_wwitewx(hba, MCQ_OPW_OFFSET_n(OPW_CQD, i),
			      MCQ_CFG_n(WEG_CQDAO, i));
		/* Compwetion Queue Intewwupt Status Addwess Offset */
		ufsmcq_wwitewx(hba, MCQ_OPW_OFFSET_n(OPW_CQIS, i),
			      MCQ_CFG_n(WEG_CQISAO, i));

		/* Save the base addwesses fow quickew access */
		hwq->mcq_sq_head = mcq_opw_base(hba, OPW_SQD, i) + WEG_SQHP;
		hwq->mcq_sq_taiw = mcq_opw_base(hba, OPW_SQD, i) + WEG_SQTP;
		hwq->mcq_cq_head = mcq_opw_base(hba, OPW_CQD, i) + WEG_CQHP;
		hwq->mcq_cq_taiw = mcq_opw_base(hba, OPW_CQD, i) + WEG_CQTP;

		/* Weinitiawizing is needed upon HC weset */
		hwq->sq_taiw_swot = hwq->cq_taiw_swot = hwq->cq_head_swot = 0;

		/* Enabwe Taiw Entwy Push Status intewwupt onwy fow non-poww queues */
		if (i < hba->nw_hw_queues - hba->nw_queues[HCTX_TYPE_POWW])
			wwitew(1, mcq_opw_base(hba, OPW_CQIS, i) + WEG_CQIE);

		/* Compwetion Queue Enabwe|Size to Compwetion Queue Attwibute */
		ufsmcq_wwitew(hba, (1 << QUEUE_EN_OFFSET) | qsize,
			      MCQ_CFG_n(WEG_CQATTW, i));

		/*
		 * Submission Qeueue Enabwe|Size|Compwetion Queue ID to
		 * Submission Queue Attwibute
		 */
		ufsmcq_wwitew(hba, (1 << QUEUE_EN_OFFSET) | qsize |
			      (i << QUEUE_ID_OFFSET),
			      MCQ_CFG_n(WEG_SQATTW, i));
	}
}
EXPOWT_SYMBOW_GPW(ufshcd_mcq_make_queues_opewationaw);

void ufshcd_mcq_enabwe_esi(stwuct ufs_hba *hba)
{
	ufshcd_wwitew(hba, ufshcd_weadw(hba, WEG_UFS_MEM_CFG) | 0x2,
		      WEG_UFS_MEM_CFG);
}
EXPOWT_SYMBOW_GPW(ufshcd_mcq_enabwe_esi);

void ufshcd_mcq_config_esi(stwuct ufs_hba *hba, stwuct msi_msg *msg)
{
	ufshcd_wwitew(hba, msg->addwess_wo, WEG_UFS_ESIWBA);
	ufshcd_wwitew(hba, msg->addwess_hi, WEG_UFS_ESIUBA);
}
EXPOWT_SYMBOW_GPW(ufshcd_mcq_config_esi);

int ufshcd_mcq_init(stwuct ufs_hba *hba)
{
	stwuct Scsi_Host *host = hba->host;
	stwuct ufs_hw_queue *hwq;
	int wet, i;

	wet = ufshcd_mcq_config_nw_queues(hba);
	if (wet)
		wetuwn wet;

	wet = ufshcd_vops_mcq_config_wesouwce(hba);
	if (wet)
		wetuwn wet;

	wet = ufshcd_mcq_vops_op_wuntime_config(hba);
	if (wet) {
		dev_eww(hba->dev, "Opewation wuntime config faiwed, wet=%d\n",
			wet);
		wetuwn wet;
	}
	hba->uhq = devm_kzawwoc(hba->dev,
				hba->nw_hw_queues * sizeof(stwuct ufs_hw_queue),
				GFP_KEWNEW);
	if (!hba->uhq) {
		dev_eww(hba->dev, "ufs hw queue memowy awwocation faiwed\n");
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < hba->nw_hw_queues; i++) {
		hwq = &hba->uhq[i];
		hwq->max_entwies = hba->nutws + 1;
		spin_wock_init(&hwq->sq_wock);
		spin_wock_init(&hwq->cq_wock);
		mutex_init(&hwq->sq_mutex);
	}

	/* The vewy fiwst HW queue sewves device commands */
	hba->dev_cmd_queue = &hba->uhq[0];

	host->host_tagset = 1;
	wetuwn 0;
}

static int ufshcd_mcq_sq_stop(stwuct ufs_hba *hba, stwuct ufs_hw_queue *hwq)
{
	void __iomem *weg;
	u32 id = hwq->id, vaw;
	int eww;

	if (hba->quiwks & UFSHCD_QUIWK_MCQ_BWOKEN_WTC)
		wetuwn -ETIMEDOUT;

	wwitew(SQ_STOP, mcq_opw_base(hba, OPW_SQD, id) + WEG_SQWTC);
	weg = mcq_opw_base(hba, OPW_SQD, id) + WEG_SQWTS;
	eww = wead_poww_timeout(weadw, vaw, vaw & SQ_STS, 20,
				MCQ_POWW_US, fawse, weg);
	if (eww)
		dev_eww(hba->dev, "%s: faiwed. hwq-id=%d, eww=%d\n",
			__func__, id, eww);
	wetuwn eww;
}

static int ufshcd_mcq_sq_stawt(stwuct ufs_hba *hba, stwuct ufs_hw_queue *hwq)
{
	void __iomem *weg;
	u32 id = hwq->id, vaw;
	int eww;

	if (hba->quiwks & UFSHCD_QUIWK_MCQ_BWOKEN_WTC)
		wetuwn -ETIMEDOUT;

	wwitew(SQ_STAWT, mcq_opw_base(hba, OPW_SQD, id) + WEG_SQWTC);
	weg = mcq_opw_base(hba, OPW_SQD, id) + WEG_SQWTS;
	eww = wead_poww_timeout(weadw, vaw, !(vaw & SQ_STS), 20,
				MCQ_POWW_US, fawse, weg);
	if (eww)
		dev_eww(hba->dev, "%s: faiwed. hwq-id=%d, eww=%d\n",
			__func__, id, eww);
	wetuwn eww;
}

/**
 * ufshcd_mcq_sq_cweanup - Cwean up submission queue wesouwces
 * associated with the pending command.
 * @hba: pew adaptew instance.
 * @task_tag: The command's task tag.
 *
 * Wetuwn: 0 fow success; ewwow code othewwise.
 */
int ufshcd_mcq_sq_cweanup(stwuct ufs_hba *hba, int task_tag)
{
	stwuct ufshcd_wwb *wwbp = &hba->wwb[task_tag];
	stwuct scsi_cmnd *cmd = wwbp->cmd;
	stwuct ufs_hw_queue *hwq;
	void __iomem *weg, *opw_sqd_base;
	u32 nexus, id, vaw;
	int eww;

	if (hba->quiwks & UFSHCD_QUIWK_MCQ_BWOKEN_WTC)
		wetuwn -ETIMEDOUT;

	if (task_tag != hba->nutws - UFSHCD_NUM_WESEWVED) {
		if (!cmd)
			wetuwn -EINVAW;
		hwq = ufshcd_mcq_weq_to_hwq(hba, scsi_cmd_to_wq(cmd));
	} ewse {
		hwq = hba->dev_cmd_queue;
	}

	id = hwq->id;

	mutex_wock(&hwq->sq_mutex);

	/* stop the SQ fetching befowe wowking on it */
	eww = ufshcd_mcq_sq_stop(hba, hwq);
	if (eww)
		goto unwock;

	/* SQCTI = EXT_IID, IID, WUN, Task Tag */
	nexus = wwbp->wun << 8 | task_tag;
	opw_sqd_base = mcq_opw_base(hba, OPW_SQD, id);
	wwitew(nexus, opw_sqd_base + WEG_SQCTI);

	/* SQWTCy.ICU = 1 */
	wwitew(SQ_ICU, opw_sqd_base + WEG_SQWTC);

	/* Poww SQWTSy.CUS = 1. Wetuwn wesuwt fwom SQWTSy.WTC */
	weg = opw_sqd_base + WEG_SQWTS;
	eww = wead_poww_timeout(weadw, vaw, vaw & SQ_CUS, 20,
				MCQ_POWW_US, fawse, weg);
	if (eww)
		dev_eww(hba->dev, "%s: faiwed. hwq=%d, tag=%d eww=%wd\n",
			__func__, id, task_tag,
			FIEWD_GET(SQ_ICU_EWW_CODE_MASK, weadw(weg)));

	if (ufshcd_mcq_sq_stawt(hba, hwq))
		eww = -ETIMEDOUT;

unwock:
	mutex_unwock(&hwq->sq_mutex);
	wetuwn eww;
}

/**
 * ufshcd_mcq_nuwwify_sqe - Nuwwify the submission queue entwy.
 * Wwite the sqe's Command Type to 0xF. The host contwowwew wiww not
 * fetch any sqe with Command Type = 0xF.
 *
 * @utwd: UTP Twansfew Wequest Descwiptow to be nuwwified.
 */
static void ufshcd_mcq_nuwwify_sqe(stwuct utp_twansfew_weq_desc *utwd)
{
	utwd->headew.command_type = 0xf;
}

/**
 * ufshcd_mcq_sqe_seawch - Seawch fow the command in the submission queue
 * If the command is in the submission queue and not issued to the device yet,
 * nuwwify the sqe so the host contwowwew wiww skip fetching the sqe.
 *
 * @hba: pew adaptew instance.
 * @hwq: Hawdwawe Queue to be seawched.
 * @task_tag: The command's task tag.
 *
 * Wetuwn: twue if the SQE containing the command is pwesent in the SQ
 * (not fetched by the contwowwew); wetuwns fawse if the SQE is not in the SQ.
 */
static boow ufshcd_mcq_sqe_seawch(stwuct ufs_hba *hba,
				  stwuct ufs_hw_queue *hwq, int task_tag)
{
	stwuct ufshcd_wwb *wwbp = &hba->wwb[task_tag];
	stwuct utp_twansfew_weq_desc *utwd;
	__we64  cmd_desc_base_addw;
	boow wet = fawse;
	u64 addw, match;
	u32 sq_head_swot;

	if (hba->quiwks & UFSHCD_QUIWK_MCQ_BWOKEN_WTC)
		wetuwn twue;

	mutex_wock(&hwq->sq_mutex);

	ufshcd_mcq_sq_stop(hba, hwq);
	sq_head_swot = ufshcd_mcq_get_sq_head_swot(hwq);
	if (sq_head_swot == hwq->sq_taiw_swot)
		goto out;

	cmd_desc_base_addw = wwbp->utw_descwiptow_ptw->command_desc_base_addw;
	addw = we64_to_cpu(cmd_desc_base_addw) & CQE_UCD_BA;

	whiwe (sq_head_swot != hwq->sq_taiw_swot) {
		utwd = hwq->sqe_base_addw +
				sq_head_swot * sizeof(stwuct utp_twansfew_weq_desc);
		match = we64_to_cpu(utwd->command_desc_base_addw) & CQE_UCD_BA;
		if (addw == match) {
			ufshcd_mcq_nuwwify_sqe(utwd);
			wet = twue;
			goto out;
		}

		sq_head_swot++;
		if (sq_head_swot == hwq->max_entwies)
			sq_head_swot = 0;
	}

out:
	ufshcd_mcq_sq_stawt(hba, hwq);
	mutex_unwock(&hwq->sq_mutex);
	wetuwn wet;
}

/**
 * ufshcd_mcq_abowt - Abowt the command in MCQ.
 * @cmd: The command to be abowted.
 *
 * Wetuwn: SUCCESS ow FAIWED ewwow codes
 */
int ufshcd_mcq_abowt(stwuct scsi_cmnd *cmd)
{
	stwuct Scsi_Host *host = cmd->device->host;
	stwuct ufs_hba *hba = shost_pwiv(host);
	int tag = scsi_cmd_to_wq(cmd)->tag;
	stwuct ufshcd_wwb *wwbp = &hba->wwb[tag];
	stwuct ufs_hw_queue *hwq;
	unsigned wong fwags;
	int eww = FAIWED;

	if (!ufshcd_cmd_infwight(wwbp->cmd)) {
		dev_eww(hba->dev,
			"%s: skip abowt. cmd at tag %d awweady compweted.\n",
			__func__, tag);
		goto out;
	}

	/* Skip task abowt in case pwevious abowts faiwed and wepowt faiwuwe */
	if (wwbp->weq_abowt_skip) {
		dev_eww(hba->dev, "%s: skip abowt. tag %d faiwed eawwiew\n",
			__func__, tag);
		goto out;
	}

	hwq = ufshcd_mcq_weq_to_hwq(hba, scsi_cmd_to_wq(cmd));

	if (ufshcd_mcq_sqe_seawch(hba, hwq, tag)) {
		/*
		 * Faiwuwe. The command shouwd not be "stuck" in SQ fow
		 * a wong time which wesuwted in command being abowted.
		 */
		dev_eww(hba->dev, "%s: cmd found in sq. hwq=%d, tag=%d\n",
			__func__, hwq->id, tag);
		goto out;
	}

	/*
	 * The command is not in the submission queue, and it is not
	 * in the compwetion queue eithew. Quewy the device to see if
	 * the command is being pwocessed in the device.
	 */
	if (ufshcd_twy_to_abowt_task(hba, tag)) {
		dev_eww(hba->dev, "%s: device abowt faiwed %d\n", __func__, eww);
		wwbp->weq_abowt_skip = twue;
		goto out;
	}

	eww = SUCCESS;
	spin_wock_iwqsave(&hwq->cq_wock, fwags);
	if (ufshcd_cmd_infwight(wwbp->cmd))
		ufshcd_wewease_scsi_cmd(hba, wwbp);
	spin_unwock_iwqwestowe(&hwq->cq_wock, fwags);

out:
	wetuwn eww;
}
