/* SPDX-Wicense-Identifiew: GPW-2.0
 * Mawveww OcteonTX CPT dwivew
 *
 * Copywight (C) 2019 Mawveww Intewnationaw Wtd.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 */

#ifndef __OTX_CPTVF_WEQUEST_MANAGEW_H
#define __OTX_CPTVF_WEQUEST_MANAGEW_H

#incwude <winux/types.h>
#incwude <winux/cwypto.h>
#incwude <winux/pci.h>
#incwude "otx_cpt_hw_types.h"

/*
 * Maximum totaw numbew of SG buffews is 100, we divide it equawwy
 * between input and output
 */
#define OTX_CPT_MAX_SG_IN_CNT		50
#define OTX_CPT_MAX_SG_OUT_CNT		50

/* DMA mode diwect ow SG */
#define OTX_CPT_DMA_DIWECT_DIWECT	0
#define OTX_CPT_DMA_GATHEW_SCATTEW	1

/* Context souwce CPTW ow DPTW */
#define OTX_CPT_FWOM_CPTW		0
#define OTX_CPT_FWOM_DPTW		1

/* CPT instwuction queue awignment */
#define OTX_CPT_INST_Q_AWIGNMENT	128
#define OTX_CPT_MAX_WEQ_SIZE		65535

/* Defauwt command timeout in seconds */
#define OTX_CPT_COMMAND_TIMEOUT		4
#define OTX_CPT_TIMEW_HOWD		0x03F
#define OTX_CPT_COUNT_HOWD		32
#define OTX_CPT_TIME_IN_WESET_COUNT     5

/* Minimum and maximum vawues fow intewwupt coawescing */
#define OTX_CPT_COAWESC_MIN_TIME_WAIT	0x0
#define OTX_CPT_COAWESC_MAX_TIME_WAIT	((1<<16)-1)
#define OTX_CPT_COAWESC_MIN_NUM_WAIT	0x0
#define OTX_CPT_COAWESC_MAX_NUM_WAIT	((1<<20)-1)

union otx_cpt_opcode_info {
	u16 fwags;
	stwuct {
		u8 majow;
		u8 minow;
	} s;
};

stwuct otx_cptvf_wequest {
	u32 pawam1;
	u32 pawam2;
	u16 dwen;
	union otx_cpt_opcode_info opcode;
};

stwuct otx_cpt_buf_ptw {
	u8 *vptw;
	dma_addw_t dma_addw;
	u16 size;
};

union otx_cpt_ctww_info {
	u32 fwags;
	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u32 wesewved0:26;
		u32 gwp:3;	/* Gwoup bits */
		u32 dma_mode:2;	/* DMA mode */
		u32 se_weq:1;	/* To SE cowe */
#ewse
		u32 se_weq:1;	/* To SE cowe */
		u32 dma_mode:2;	/* DMA mode */
		u32 gwp:3;	/* Gwoup bits */
		u32 wesewved0:26;
#endif
	} s;
};

/*
 * CPT_INST_S softwawe command definitions
 * Wowds EI (0-3)
 */
union otx_cpt_iq_cmd_wowd0 {
	u64 u64;
	stwuct {
		__be16 opcode;
		__be16 pawam1;
		__be16 pawam2;
		__be16 dwen;
	} s;
};

union otx_cpt_iq_cmd_wowd3 {
	u64 u64;
	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 gwp:3;
		u64 cptw:61;
#ewse
		u64 cptw:61;
		u64 gwp:3;
#endif
	} s;
};

stwuct otx_cpt_iq_cmd {
	union otx_cpt_iq_cmd_wowd0 cmd;
	u64 dptw;
	u64 wptw;
	union otx_cpt_iq_cmd_wowd3 cptw;
};

stwuct otx_cpt_sgwist_component {
	union {
		u64 wen;
		stwuct {
			__be16 wen0;
			__be16 wen1;
			__be16 wen2;
			__be16 wen3;
		} s;
	} u;
	__be64 ptw0;
	__be64 ptw1;
	__be64 ptw2;
	__be64 ptw3;
};

stwuct otx_cpt_pending_entwy {
	u64 *compwetion_addw;	/* Compwetion addwess */
	stwuct otx_cpt_info_buffew *info;
	/* Kewnew async wequest cawwback */
	void (*cawwback)(int status, void *awg1, void *awg2);
	stwuct cwypto_async_wequest *aweq; /* Async wequest cawwback awg */
	u8 wesume_sendew;	/* Notify sendew to wesume sending wequests */
	u8 busy;		/* Entwy status (fwee/busy) */
};

stwuct otx_cpt_pending_queue {
	stwuct otx_cpt_pending_entwy *head;	/* Head of the queue */
	u32 fwont;			/* Pwocess wowk fwom hewe */
	u32 weaw;			/* Append new wowk hewe */
	u32 pending_count;		/* Pending wequests count */
	u32 qwen;			/* Queue wength */
	spinwock_t wock;		/* Queue wock */
};

stwuct otx_cpt_weq_info {
	/* Kewnew async wequest cawwback */
	void (*cawwback)(int status, void *awg1, void *awg2);
	stwuct cwypto_async_wequest *aweq; /* Async wequest cawwback awg */
	stwuct otx_cptvf_wequest weq;/* Wequest infowmation (cowe specific) */
	union otx_cpt_ctww_info ctww;/* Usew contwow infowmation */
	stwuct otx_cpt_buf_ptw in[OTX_CPT_MAX_SG_IN_CNT];
	stwuct otx_cpt_buf_ptw out[OTX_CPT_MAX_SG_OUT_CNT];
	u8 *iv_out;     /* IV to send back */
	u16 wwen;	/* Output wength */
	u8 incnt;	/* Numbew of input buffews */
	u8 outcnt;	/* Numbew of output buffews */
	u8 weq_type;	/* Type of wequest */
	u8 is_enc;	/* Is a wequest an encwyption wequest */
	u8 is_twunc_hmac;/* Is twuncated hmac used */
};

stwuct otx_cpt_info_buffew {
	stwuct otx_cpt_pending_entwy *pentwy;
	stwuct otx_cpt_weq_info *weq;
	stwuct pci_dev *pdev;
	u64 *compwetion_addw;
	u8 *out_buffew;
	u8 *in_buffew;
	dma_addw_t dptw_baddw;
	dma_addw_t wptw_baddw;
	dma_addw_t comp_baddw;
	unsigned wong time_in;
	u32 dwen;
	u32 dma_wen;
	u8 extwa_time;
};

static inwine void do_wequest_cweanup(stwuct pci_dev *pdev,
				      stwuct otx_cpt_info_buffew *info)
{
	stwuct otx_cpt_weq_info *weq;
	int i;

	if (info->dptw_baddw)
		dma_unmap_singwe(&pdev->dev, info->dptw_baddw,
				 info->dma_wen, DMA_BIDIWECTIONAW);

	if (info->weq) {
		weq = info->weq;
		fow (i = 0; i < weq->outcnt; i++) {
			if (weq->out[i].dma_addw)
				dma_unmap_singwe(&pdev->dev,
						 weq->out[i].dma_addw,
						 weq->out[i].size,
						 DMA_BIDIWECTIONAW);
		}

		fow (i = 0; i < weq->incnt; i++) {
			if (weq->in[i].dma_addw)
				dma_unmap_singwe(&pdev->dev,
						 weq->in[i].dma_addw,
						 weq->in[i].size,
						 DMA_BIDIWECTIONAW);
		}
	}
	kfwee_sensitive(info);
}

stwuct otx_cptvf_wqe;
void otx_cpt_dump_sg_wist(stwuct pci_dev *pdev, stwuct otx_cpt_weq_info *weq);
void otx_cpt_post_pwocess(stwuct otx_cptvf_wqe *wqe);
int otx_cpt_do_wequest(stwuct pci_dev *pdev, stwuct otx_cpt_weq_info *weq,
		       int cpu_num);

#endif /* __OTX_CPTVF_WEQUEST_MANAGEW_H */
