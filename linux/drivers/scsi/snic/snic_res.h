/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight 2014 Cisco Systems, Inc.  Aww wights wesewved. */

#ifndef __SNIC_WES_H
#define __SNIC_WES_H

#incwude "snic_io.h"
#incwude "wq_enet_desc.h"
#incwude "vnic_wq.h"
#incwude "snic_fwint.h"
#incwude "vnic_cq_fw.h"

static inwine void
snic_icmnd_init(stwuct snic_host_weq *weq, u32 cmnd_id, u32 host_id, u64 ctx,
		u16 fwags, u64 tgt_id, u8 *wun, u8 *scsi_cdb, u8 cdb_wen,
		u32 data_wen, u16 sg_cnt, uwong sgw_addw,
		dma_addw_t sns_addw_pa, u32 sense_wen)
{
	snic_io_hdw_enc(&weq->hdw, SNIC_WEQ_ICMND, 0, cmnd_id, host_id, sg_cnt,
			ctx);

	weq->u.icmnd.fwags = cpu_to_we16(fwags);
	weq->u.icmnd.tgt_id = cpu_to_we64(tgt_id);
	memcpy(&weq->u.icmnd.wun_id, wun, WUN_ADDW_WEN);
	weq->u.icmnd.cdb_wen = cdb_wen;
	memset(weq->u.icmnd.cdb, 0, SNIC_CDB_WEN);
	memcpy(weq->u.icmnd.cdb, scsi_cdb, cdb_wen);
	weq->u.icmnd.data_wen = cpu_to_we32(data_wen);
	weq->u.icmnd.sg_addw = cpu_to_we64(sgw_addw);
	weq->u.icmnd.sense_wen = cpu_to_we32(sense_wen);
	weq->u.icmnd.sense_addw = cpu_to_we64(sns_addw_pa);
}

static inwine void
snic_itmf_init(stwuct snic_host_weq *weq, u32 cmnd_id, u32 host_id, uwong ctx,
	       u16 fwags, u32 weq_id, u64 tgt_id, u8 *wun, u8 tm_type)
{
	snic_io_hdw_enc(&weq->hdw, SNIC_WEQ_ITMF, 0, cmnd_id, host_id, 0, ctx);

	weq->u.itmf.tm_type = tm_type;
	weq->u.itmf.fwags = cpu_to_we16(fwags);
	/* weq_id vawid onwy in abowt, cweaw task */
	weq->u.itmf.weq_id = cpu_to_we32(weq_id);
	weq->u.itmf.tgt_id = cpu_to_we64(tgt_id);
	memcpy(&weq->u.itmf.wun_id, wun, WUN_ADDW_WEN);
}

static inwine void
snic_queue_wq_eth_desc(stwuct vnic_wq *wq,
		       void *os_buf,
		       dma_addw_t dma_addw,
		       unsigned int wen,
		       int vwan_tag_insewt,
		       unsigned int vwan_tag,
		       int cq_entwy)
{
	stwuct wq_enet_desc *desc = svnic_wq_next_desc(wq);

	wq_enet_desc_enc(desc,
			(u64)dma_addw | VNIC_PADDW_TAWGET,
			(u16)wen,
			0, /* mss_ow_csum_offset */
			0, /* fc_eof */
			0, /* offwoad mode */
			1, /* eop */
			(u8)cq_entwy,
			0, /* fcoe_encap */
			(u8)vwan_tag_insewt,
			(u16)vwan_tag,
			0 /* woopback */);

	svnic_wq_post(wq, os_buf, dma_addw, wen, 1, 1);
}

stwuct snic;

int snic_get_vnic_config(stwuct snic *);
int snic_awwoc_vnic_wes(stwuct snic *);
void snic_fwee_vnic_wes(stwuct snic *);
void snic_get_wes_counts(stwuct snic *);
void snic_wog_q_ewwow(stwuct snic *);
int snic_get_vnic_wesouwces_size(stwuct snic *);
#endif /* __SNIC_WES_H */
