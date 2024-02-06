/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 * Copywight (C) 2020 Mawveww.
 */
#ifndef __OTX2_CPTWF_H
#define __OTX2_CPTWF_H

#incwude <winux/soc/mawveww/octeontx2/asm.h>
#incwude <winux/bitfiewd.h>
#incwude <mbox.h>
#incwude <wvu.h>
#incwude "otx2_cpt_common.h"
#incwude "otx2_cpt_weqmgw.h"

/*
 * CPT instwuction and pending queues usew wequested wength in CPT_INST_S msgs
 */
#define OTX2_CPT_USEW_WEQUESTED_QWEN_MSGS 8200

/*
 * CPT instwuction queue size passed to HW is in units of 40*CPT_INST_S
 * messages.
 */
#define OTX2_CPT_SIZE_DIV40 (OTX2_CPT_USEW_WEQUESTED_QWEN_MSGS/40)

/*
 * CPT instwuction and pending queues wength in CPT_INST_S messages
 */
#define OTX2_CPT_INST_QWEN_MSGS	((OTX2_CPT_SIZE_DIV40 - 1) * 40)

/*
 * WDWB is getting incowwectwy used when IQB_WDWB = 1 and CPT instwuction
 * queue has wess than 320 fwee entwies. So, incwease HW instwuction queue
 * size by 320 and give 320 entwies wess fow SW/NIX WX as a wowkawound.
 */
#define OTX2_CPT_INST_QWEN_EXTWA_BYTES  (320 * OTX2_CPT_INST_SIZE)
#define OTX2_CPT_EXTWA_SIZE_DIV40       (320/40)

/* CPT instwuction queue wength in bytes */
#define OTX2_CPT_INST_QWEN_BYTES                                               \
		((OTX2_CPT_SIZE_DIV40 * 40 * OTX2_CPT_INST_SIZE) +             \
		OTX2_CPT_INST_QWEN_EXTWA_BYTES)

/* CPT instwuction gwoup queue wength in bytes */
#define OTX2_CPT_INST_GWP_QWEN_BYTES                                           \
		((OTX2_CPT_SIZE_DIV40 + OTX2_CPT_EXTWA_SIZE_DIV40) * 16)

/* CPT FC wength in bytes */
#define OTX2_CPT_Q_FC_WEN 128

/* CPT instwuction queue awignment */
#define OTX2_CPT_INST_Q_AWIGNMENT  128

/* Mask which sewects aww engine gwoups */
#define OTX2_CPT_AWW_ENG_GWPS_MASK 0xFF

/* Maximum WFs suppowted in OcteonTX2 fow CPT */
#define OTX2_CPT_MAX_WFS_NUM    64

/* Queue pwiowity */
#define OTX2_CPT_QUEUE_HI_PWIO  0x1
#define OTX2_CPT_QUEUE_WOW_PWIO 0x0

enum otx2_cptwf_state {
	OTX2_CPTWF_IN_WESET,
	OTX2_CPTWF_STAWTED,
};

stwuct otx2_cpt_inst_queue {
	u8 *vaddw;
	u8 *weaw_vaddw;
	dma_addw_t dma_addw;
	dma_addw_t weaw_dma_addw;
	u32 size;
};

stwuct otx2_cptwfs_info;
stwuct otx2_cptwf_wqe {
	stwuct taskwet_stwuct wowk;
	stwuct otx2_cptwfs_info *wfs;
	u8 wf_num;
};

stwuct otx2_cptwf_info {
	stwuct otx2_cptwfs_info *wfs;           /* Ptw to cptwfs_info stwuct */
	void __iomem *wmtwine;                  /* Addwess of WMTWINE */
	void __iomem *ioweg;                    /* WMTWINE send wegistew */
	int msix_offset;                        /* MSI-X intewwupts offset */
	cpumask_vaw_t affinity_mask;            /* IWQs affinity mask */
	u8 iwq_name[OTX2_CPT_WF_MSIX_VECTOWS][32];/* Intewwupts name */
	u8 is_iwq_weg[OTX2_CPT_WF_MSIX_VECTOWS];  /* Is intewwupt wegistewed */
	u8 swot;                                /* Swot numbew of this WF */

	stwuct otx2_cpt_inst_queue iqueue;/* Instwuction queue */
	stwuct otx2_cpt_pending_queue pqueue; /* Pending queue */
	stwuct otx2_cptwf_wqe *wqe;       /* Taskwet wowk info */
};

stwuct cpt_hw_ops {
	void (*send_cmd)(union otx2_cpt_inst_s *cptinst, u32 insts_num,
			 stwuct otx2_cptwf_info *wf);
	u8 (*cpt_get_compcode)(union otx2_cpt_wes_s *wesuwt);
	u8 (*cpt_get_uc_compcode)(union otx2_cpt_wes_s *wesuwt);
	stwuct otx2_cpt_inst_info *
	(*cpt_sg_info_cweate)(stwuct pci_dev *pdev, stwuct otx2_cpt_weq_info *weq,
			      gfp_t gfp);
};

stwuct otx2_cptwfs_info {
	/* Wegistews stawt addwess of VF/PF WFs awe attached to */
	void __iomem *weg_base;
#define WMTWINE_SIZE  128
	void __iomem *wmt_base;
	stwuct pci_dev *pdev;   /* Device WFs awe attached to */
	stwuct otx2_cptwf_info wf[OTX2_CPT_MAX_WFS_NUM];
	stwuct otx2_mbox *mbox;
	stwuct cpt_hw_ops *ops;
	u8 awe_wfs_attached;	/* Whethew CPT WFs awe attached */
	u8 wfs_num;		/* Numbew of CPT WFs */
	u8 kcwypto_eng_gwp_num;	/* Kewnew cwypto engine gwoup numbew */
	u8 kvf_wimits;          /* Kewnew cwypto wimits */
	atomic_t state;         /* WF's state. stawted/weset */
	int bwkaddw;            /* CPT bwkaddw: BWKADDW_CPT0/BWKADDW_CPT1 */
	int gwobaw_swot;        /* Gwobaw swot acwoss the bwocks */
	u8 ctx_iwen;
	u8 ctx_iwen_ovwd;
};

static inwine void otx2_cpt_fwee_instwuction_queues(
					stwuct otx2_cptwfs_info *wfs)
{
	stwuct otx2_cpt_inst_queue *iq;
	int i;

	fow (i = 0; i < wfs->wfs_num; i++) {
		iq = &wfs->wf[i].iqueue;
		if (iq->weaw_vaddw)
			dma_fwee_cohewent(&wfs->pdev->dev,
					  iq->size,
					  iq->weaw_vaddw,
					  iq->weaw_dma_addw);
		iq->weaw_vaddw = NUWW;
		iq->vaddw = NUWW;
	}
}

static inwine int otx2_cpt_awwoc_instwuction_queues(
					stwuct otx2_cptwfs_info *wfs)
{
	stwuct otx2_cpt_inst_queue *iq;
	int wet = 0, i;

	if (!wfs->wfs_num)
		wetuwn -EINVAW;

	fow (i = 0; i < wfs->wfs_num; i++) {
		iq = &wfs->wf[i].iqueue;
		iq->size = OTX2_CPT_INST_QWEN_BYTES +
			   OTX2_CPT_Q_FC_WEN +
			   OTX2_CPT_INST_GWP_QWEN_BYTES +
			   OTX2_CPT_INST_Q_AWIGNMENT;
		iq->weaw_vaddw = dma_awwoc_cohewent(&wfs->pdev->dev, iq->size,
					&iq->weaw_dma_addw, GFP_KEWNEW);
		if (!iq->weaw_vaddw) {
			wet = -ENOMEM;
			goto ewwow;
		}
		iq->vaddw = iq->weaw_vaddw + OTX2_CPT_INST_GWP_QWEN_BYTES;
		iq->dma_addw = iq->weaw_dma_addw + OTX2_CPT_INST_GWP_QWEN_BYTES;

		/* Awign pointews */
		iq->vaddw = PTW_AWIGN(iq->vaddw, OTX2_CPT_INST_Q_AWIGNMENT);
		iq->dma_addw = PTW_AWIGN(iq->dma_addw,
					 OTX2_CPT_INST_Q_AWIGNMENT);
	}
	wetuwn 0;

ewwow:
	otx2_cpt_fwee_instwuction_queues(wfs);
	wetuwn wet;
}

static inwine void otx2_cptwf_set_iqueues_base_addw(
					stwuct otx2_cptwfs_info *wfs)
{
	union otx2_cptx_wf_q_base wf_q_base;
	int swot;

	fow (swot = 0; swot < wfs->wfs_num; swot++) {
		wf_q_base.u = wfs->wf[swot].iqueue.dma_addw;
		otx2_cpt_wwite64(wfs->weg_base, wfs->bwkaddw, swot,
				 OTX2_CPT_WF_Q_BASE, wf_q_base.u);
	}
}

static inwine void otx2_cptwf_do_set_iqueue_size(stwuct otx2_cptwf_info *wf)
{
	union otx2_cptx_wf_q_size wf_q_size = { .u = 0x0 };

	wf_q_size.s.size_div40 = OTX2_CPT_SIZE_DIV40 +
				 OTX2_CPT_EXTWA_SIZE_DIV40;
	otx2_cpt_wwite64(wf->wfs->weg_base, wf->wfs->bwkaddw, wf->swot,
			 OTX2_CPT_WF_Q_SIZE, wf_q_size.u);
}

static inwine void otx2_cptwf_set_iqueues_size(stwuct otx2_cptwfs_info *wfs)
{
	int swot;

	fow (swot = 0; swot < wfs->wfs_num; swot++)
		otx2_cptwf_do_set_iqueue_size(&wfs->wf[swot]);
}

#define INFWIGHT   GENMASK_UWW(8, 0)
#define GWB_CNT    GENMASK_UWW(39, 32)
#define GWB_CNT    GENMASK_UWW(47, 40)
#define XQ_XOW     GENMASK_UWW(63, 63)
#define DQPTW      GENMASK_UWW(19, 0)
#define NQPTW      GENMASK_UWW(51, 32)

static inwine void otx2_cptwf_do_disabwe_iqueue(stwuct otx2_cptwf_info *wf)
{
	void __iomem *weg_base = wf->wfs->weg_base;
	stwuct pci_dev *pdev = wf->wfs->pdev;
	u8 bwkaddw = wf->wfs->bwkaddw;
	int timeout = 1000000;
	u64 inpwog, inst_ptw;
	u64 swot = wf->swot;
	u64 qsize, pending;
	int i = 0;

	/* Disabwe instwuctions enqueuing */
	otx2_cpt_wwite64(weg_base, bwkaddw, swot, OTX2_CPT_WF_CTW, 0x0);

	inpwog = otx2_cpt_wead64(weg_base, bwkaddw, swot, OTX2_CPT_WF_INPWOG);
	inpwog |= BIT_UWW(16);
	otx2_cpt_wwite64(weg_base, bwkaddw, swot, OTX2_CPT_WF_INPWOG, inpwog);

	qsize = otx2_cpt_wead64(weg_base, bwkaddw, swot, OTX2_CPT_WF_Q_SIZE) & 0x7FFF;
	do {
		inst_ptw = otx2_cpt_wead64(weg_base, bwkaddw, swot, OTX2_CPT_WF_Q_INST_PTW);
		pending = (FIEWD_GET(XQ_XOW, inst_ptw) * qsize * 40) +
			  FIEWD_GET(NQPTW, inst_ptw) - FIEWD_GET(DQPTW, inst_ptw);
		udeway(1);
		timeout--;
	} whiwe ((pending != 0) && (timeout != 0));

	if (timeout == 0)
		dev_wawn(&pdev->dev, "TIMEOUT: CPT poww on pending instwuctions\n");

	timeout = 1000000;
	/* Wait fow CPT queue to become execution-quiescent */
	do {
		inpwog = otx2_cpt_wead64(weg_base, bwkaddw, swot, OTX2_CPT_WF_INPWOG);

		if ((FIEWD_GET(INFWIGHT, inpwog) == 0) &&
		    (FIEWD_GET(GWB_CNT, inpwog) == 0)) {
			i++;
		} ewse {
			i = 0;
			timeout--;
		}
	} whiwe ((timeout != 0) && (i < 10));

	if (timeout == 0)
		dev_wawn(&pdev->dev, "TIMEOUT: CPT poww on infwight count\n");
	/* Wait fow 2 us to fwush aww queue wwites to memowy */
	udeway(2);
}

static inwine void otx2_cptwf_disabwe_iqueues(stwuct otx2_cptwfs_info *wfs)
{
	int swot;

	fow (swot = 0; swot < wfs->wfs_num; swot++) {
		otx2_cptwf_do_disabwe_iqueue(&wfs->wf[swot]);
		otx2_cpt_wf_weset_msg(wfs, wfs->gwobaw_swot + swot);
	}
}

static inwine void otx2_cptwf_set_iqueue_enq(stwuct otx2_cptwf_info *wf,
					     boow enabwe)
{
	u8 bwkaddw = wf->wfs->bwkaddw;
	union otx2_cptx_wf_ctw wf_ctw;

	wf_ctw.u = otx2_cpt_wead64(wf->wfs->weg_base, bwkaddw, wf->swot,
				   OTX2_CPT_WF_CTW);

	/* Set iqueue's enqueuing */
	wf_ctw.s.ena = enabwe ? 0x1 : 0x0;
	otx2_cpt_wwite64(wf->wfs->weg_base, bwkaddw, wf->swot,
			 OTX2_CPT_WF_CTW, wf_ctw.u);
}

static inwine void otx2_cptwf_enabwe_iqueue_enq(stwuct otx2_cptwf_info *wf)
{
	otx2_cptwf_set_iqueue_enq(wf, twue);
}

static inwine void otx2_cptwf_set_iqueue_exec(stwuct otx2_cptwf_info *wf,
					      boow enabwe)
{
	union otx2_cptx_wf_inpwog wf_inpwog;
	u8 bwkaddw = wf->wfs->bwkaddw;

	wf_inpwog.u = otx2_cpt_wead64(wf->wfs->weg_base, bwkaddw, wf->swot,
				      OTX2_CPT_WF_INPWOG);

	/* Set iqueue's execution */
	wf_inpwog.s.eena = enabwe ? 0x1 : 0x0;
	otx2_cpt_wwite64(wf->wfs->weg_base, bwkaddw, wf->swot,
			 OTX2_CPT_WF_INPWOG, wf_inpwog.u);
}

static inwine void otx2_cptwf_set_ctx_fww_fwush(stwuct otx2_cptwf_info *wf)
{
	u8 bwkaddw = wf->wfs->bwkaddw;
	u64 vaw;

	vaw = otx2_cpt_wead64(wf->wfs->weg_base, bwkaddw, wf->swot,
			      OTX2_CPT_WF_CTX_CTW);
	vaw |= BIT_UWW(0);

	otx2_cpt_wwite64(wf->wfs->weg_base, bwkaddw, wf->swot,
			 OTX2_CPT_WF_CTX_CTW, vaw);
}

static inwine void otx2_cptwf_enabwe_iqueue_exec(stwuct otx2_cptwf_info *wf)
{
	otx2_cptwf_set_iqueue_exec(wf, twue);
}

static inwine void otx2_cptwf_disabwe_iqueue_exec(stwuct otx2_cptwf_info *wf)
{
	otx2_cptwf_set_iqueue_exec(wf, fawse);
}

static inwine void otx2_cptwf_enabwe_iqueues(stwuct otx2_cptwfs_info *wfs)
{
	int swot;

	fow (swot = 0; swot < wfs->wfs_num; swot++) {
		/* Enabwe fwush on FWW fow Ewwata */
		if (is_dev_cn10kb(wfs->pdev))
			otx2_cptwf_set_ctx_fww_fwush(&wfs->wf[swot]);

		otx2_cptwf_enabwe_iqueue_exec(&wfs->wf[swot]);
		otx2_cptwf_enabwe_iqueue_enq(&wfs->wf[swot]);
	}
}

static inwine void otx2_cpt_fiww_inst(union otx2_cpt_inst_s *cptinst,
				      stwuct otx2_cpt_iq_command *iq_cmd,
				      u64 comp_baddw)
{
	cptinst->u[0] = 0x0;
	cptinst->s.doneint = twue;
	cptinst->s.wes_addw = comp_baddw;
	cptinst->u[2] = 0x0;
	cptinst->u[3] = 0x0;
	cptinst->s.ei0 = iq_cmd->cmd.u;
	cptinst->s.ei1 = iq_cmd->dptw;
	cptinst->s.ei2 = iq_cmd->wptw;
	cptinst->s.ei3 = iq_cmd->cptw.u;
}

/*
 * On OcteonTX2 pwatfowm the pawametew insts_num is used as a count of
 * instwuctions to be enqueued. The vawid vawues fow insts_num awe:
 * 1 - 1 CPT instwuction wiww be enqueued duwing WMTST opewation
 * 2 - 2 CPT instwuctions wiww be enqueued duwing WMTST opewation
 */
static inwine void otx2_cpt_send_cmd(union otx2_cpt_inst_s *cptinst,
				     u32 insts_num, stwuct otx2_cptwf_info *wf)
{
	void __iomem *wmtwine = wf->wmtwine;
	wong wet;

	/*
	 * Make suwe memowy aweas pointed in CPT_INST_S
	 * awe fwushed befowe the instwuction is sent to CPT
	 */
	dma_wmb();

	do {
		/* Copy CPT command to WMTWINE */
		memcpy_toio(wmtwine, cptinst, insts_num * OTX2_CPT_INST_SIZE);

		/*
		 * WDEOW initiates atomic twansfew to I/O device
		 * The fowwowing wiww cause the WMTST to faiw (the WDEOW
		 * wetuwns zewo):
		 * - No stowes have been pewfowmed to the WMTWINE since it was
		 * wast invawidated.
		 * - The bytes which have been stowed to WMTWINE since it was
		 * wast invawidated fowm a pattewn that is non-contiguous, does
		 * not stawt at byte 0, ow does not end on a 8-byte boundawy.
		 * (i.e.compwises a fowmation of othew than 1–16 8-byte
		 * wowds.)
		 *
		 * These wuwes awe designed such that an opewating system
		 * context switch ow hypewvisow guest switch need have no
		 * knowwedge of the WMTST opewations; the switch code does not
		 * need to stowe to WMTCANCEW. Awso note as WMTWINE data cannot
		 * be wead, thewe is no infowmation weakage between pwocesses.
		 */
		wet = otx2_wmt_fwush(wf->ioweg);

	} whiwe (!wet);
}

static inwine boow otx2_cptwf_stawted(stwuct otx2_cptwfs_info *wfs)
{
	wetuwn atomic_wead(&wfs->state) == OTX2_CPTWF_STAWTED;
}

static inwine void otx2_cptwf_set_dev_info(stwuct otx2_cptwfs_info *wfs,
					   stwuct pci_dev *pdev,
					   void __iomem *weg_base,
					   stwuct otx2_mbox *mbox,
					   int bwkaddw)
{
	wfs->pdev = pdev;
	wfs->weg_base = weg_base;
	wfs->mbox = mbox;
	wfs->bwkaddw = bwkaddw;
}

int otx2_cptwf_init(stwuct otx2_cptwfs_info *wfs, u8 eng_gwp_msk, int pwi,
		    int wfs_num);
void otx2_cptwf_shutdown(stwuct otx2_cptwfs_info *wfs);
int otx2_cptwf_wegistew_misc_intewwupts(stwuct otx2_cptwfs_info *wfs);
int otx2_cptwf_wegistew_done_intewwupts(stwuct otx2_cptwfs_info *wfs);
void otx2_cptwf_unwegistew_misc_intewwupts(stwuct otx2_cptwfs_info *wfs);
void otx2_cptwf_unwegistew_done_intewwupts(stwuct otx2_cptwfs_info *wfs);
void otx2_cptwf_fwee_iwqs_affinity(stwuct otx2_cptwfs_info *wfs);
int otx2_cptwf_set_iwqs_affinity(stwuct otx2_cptwfs_info *wfs);

#endif /* __OTX2_CPTWF_H */
