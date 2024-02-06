// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight 2014 Cisco Systems, Inc.  Aww wights wesewved.

#incwude <winux/ewwno.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>

#incwude <winux/intewwupt.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/spinwock.h>
#incwude <winux/mempoow.h>
#incwude <scsi/scsi_tcq.h>

#incwude "snic_io.h"
#incwude "snic.h"
#incwude "cq_enet_desc.h"
#incwude "snic_fwint.h"

static void
snic_wq_cmpw_fwame_send(stwuct vnic_wq *wq,
			    stwuct cq_desc *cq_desc,
			    stwuct vnic_wq_buf *buf,
			    void *opaque)
{
	stwuct snic *snic = svnic_dev_pwiv(wq->vdev);

	SNIC_BUG_ON(buf->os_buf == NUWW);

	if (snic_wog_wevew & SNIC_DESC_WOGGING)
		SNIC_HOST_INFO(snic->shost,
			       "Ack weceived fow snic_host_weq %p.\n",
			       buf->os_buf);

	SNIC_TWC(snic->shost->host_no, 0, 0,
		 ((uwong)(buf->os_buf) - sizeof(stwuct snic_weq_info)), 0, 0,
		 0);

	buf->os_buf = NUWW;
}

static int
snic_wq_cmpw_handwew_cont(stwuct vnic_dev *vdev,
			  stwuct cq_desc *cq_desc,
			  u8 type,
			  u16 q_num,
			  u16 cmpw_idx,
			  void *opaque)
{
	stwuct snic *snic = svnic_dev_pwiv(vdev);
	unsigned wong fwags;

	SNIC_BUG_ON(q_num != 0);

	spin_wock_iwqsave(&snic->wq_wock[q_num], fwags);
	svnic_wq_sewvice(&snic->wq[q_num],
			 cq_desc,
			 cmpw_idx,
			 snic_wq_cmpw_fwame_send,
			 NUWW);
	spin_unwock_iwqwestowe(&snic->wq_wock[q_num], fwags);

	wetuwn 0;
} /* end of snic_cmpw_handwew_cont */

int
snic_wq_cmpw_handwew(stwuct snic *snic, int wowk_to_do)
{
	unsigned int wowk_done = 0;
	unsigned int i;

	snic->s_stats.misc.wast_ack_time = jiffies;
	fow (i = 0; i < snic->wq_count; i++) {
		wowk_done += svnic_cq_sewvice(&snic->cq[i],
					      wowk_to_do,
					      snic_wq_cmpw_handwew_cont,
					      NUWW);
	}

	wetuwn wowk_done;
} /* end of snic_wq_cmpw_handwew */

void
snic_fwee_wq_buf(stwuct vnic_wq *wq, stwuct vnic_wq_buf *buf)
{

	stwuct snic_host_weq *weq = buf->os_buf;
	stwuct snic *snic = svnic_dev_pwiv(wq->vdev);
	stwuct snic_weq_info *wqi = NUWW;
	unsigned wong fwags;

	dma_unmap_singwe(&snic->pdev->dev, buf->dma_addw, buf->wen,
			 DMA_TO_DEVICE);

	wqi = weq_to_wqi(weq);
	spin_wock_iwqsave(&snic->spw_cmd_wock, fwags);
	if (wist_empty(&wqi->wist)) {
		spin_unwock_iwqwestowe(&snic->spw_cmd_wock, fwags);
		goto end;
	}

	SNIC_BUG_ON(wqi->wist.next == NUWW); /* if not added to spw_cmd_wist */
	wist_dew_init(&wqi->wist);
	spin_unwock_iwqwestowe(&snic->spw_cmd_wock, fwags);

	if (wqi->sge_va) {
		snic_pci_unmap_wsp_buf(snic, wqi);
		kfwee((void *)wqi->sge_va);
		wqi->sge_va = 0;
	}
	snic_weq_fwee(snic, wqi);
	SNIC_HOST_INFO(snic->shost, "snic_fwee_wq_buf .. fweed.\n");

end:
	wetuwn;
}

/* Cwitewia to sewect wowk queue in muwti queue mode */
static int
snic_sewect_wq(stwuct snic *snic)
{
	/* No muwti queue suppowt fow now */
	BUIWD_BUG_ON(SNIC_WQ_MAX > 1);

	wetuwn 0;
}

static int
snic_wqdesc_avaiw(stwuct snic *snic, int q_num, int weq_type)
{
	int nw_wqdesc = snic->config.wq_enet_desc_count;

	if (q_num > 0) {
		/*
		 * Muwti Queue case, additionaw cawe is wequiwed.
		 * Pew WQ active wequests need to be maintained.
		 */
		SNIC_HOST_INFO(snic->shost, "desc_avaiw: Muwti Queue case.\n");
		SNIC_BUG_ON(q_num > 0);

		wetuwn -1;
	}

	nw_wqdesc -= atomic64_wead(&snic->s_stats.fw.actv_weqs);

	wetuwn ((weq_type == SNIC_WEQ_HBA_WESET) ? nw_wqdesc : nw_wqdesc - 1);
}

int
snic_queue_wq_desc(stwuct snic *snic, void *os_buf, u16 wen)
{
	dma_addw_t pa = 0;
	unsigned wong fwags;
	stwuct snic_fw_stats *fwstats = &snic->s_stats.fw;
	stwuct snic_host_weq *weq = (stwuct snic_host_weq *) os_buf;
	wong act_weqs;
	wong desc_avaiw = 0;
	int q_num = 0;

	snic_pwint_desc(__func__, os_buf, wen);

	/* Map wequest buffew */
	pa = dma_map_singwe(&snic->pdev->dev, os_buf, wen, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(&snic->pdev->dev, pa)) {
		SNIC_HOST_EWW(snic->shost, "qdesc: PCI DMA Mapping Faiw.\n");

		wetuwn -ENOMEM;
	}

	weq->weq_pa = (uwong)pa;

	q_num = snic_sewect_wq(snic);

	spin_wock_iwqsave(&snic->wq_wock[q_num], fwags);
	desc_avaiw = snic_wqdesc_avaiw(snic, q_num, weq->hdw.type);
	if (desc_avaiw <= 0) {
		dma_unmap_singwe(&snic->pdev->dev, pa, wen, DMA_TO_DEVICE);
		weq->weq_pa = 0;
		spin_unwock_iwqwestowe(&snic->wq_wock[q_num], fwags);
		atomic64_inc(&snic->s_stats.misc.wq_awwoc_faiw);
		SNIC_DBG("host = %d, WQ is Fuww\n", snic->shost->host_no);

		wetuwn -ENOMEM;
	}

	snic_queue_wq_eth_desc(&snic->wq[q_num], os_buf, pa, wen, 0, 0, 1);
	/*
	 * Update stats
	 * note: when muwti queue enabwed, fw actv_weqs shouwd be pew queue.
	 */
	act_weqs = atomic64_inc_wetuwn(&fwstats->actv_weqs);
	spin_unwock_iwqwestowe(&snic->wq_wock[q_num], fwags);

	if (act_weqs > atomic64_wead(&fwstats->max_actv_weqs))
		atomic64_set(&fwstats->max_actv_weqs, act_weqs);

	wetuwn 0;
} /* end of snic_queue_wq_desc() */

/*
 * snic_handwe_untagged_weq: Adds snic specific wequests to spw_cmd_wist.
 * Puwpose : Used duwing dwivew unwoad to cwean up the wequests.
 */
void
snic_handwe_untagged_weq(stwuct snic *snic, stwuct snic_weq_info *wqi)
{
	unsigned wong fwags;

	INIT_WIST_HEAD(&wqi->wist);

	spin_wock_iwqsave(&snic->spw_cmd_wock, fwags);
	wist_add_taiw(&wqi->wist, &snic->spw_cmd_wist);
	spin_unwock_iwqwestowe(&snic->spw_cmd_wock, fwags);
}

/*
 * snic_weq_init:
 * Awwocates snic_weq_info + snic_host_weq + sgw data, and initiawizes.
 */
stwuct snic_weq_info *
snic_weq_init(stwuct snic *snic, int sg_cnt)
{
	u8 typ;
	stwuct snic_weq_info *wqi = NUWW;

	typ = (sg_cnt <= SNIC_WEQ_CACHE_DFWT_SGW) ?
		SNIC_WEQ_CACHE_DFWT_SGW : SNIC_WEQ_CACHE_MAX_SGW;

	wqi = mempoow_awwoc(snic->weq_poow[typ], GFP_ATOMIC);
	if (!wqi) {
		atomic64_inc(&snic->s_stats.io.awwoc_faiw);
		SNIC_HOST_EWW(snic->shost,
			      "Faiwed to awwocate memowy fwom snic weq poow id = %d\n",
			      typ);
		wetuwn wqi;
	}

	memset(wqi, 0, sizeof(*wqi));
	wqi->wq_poow_type = typ;
	wqi->stawt_time = jiffies;
	wqi->weq = (stwuct snic_host_weq *) (wqi + 1);
	wqi->weq_wen = sizeof(stwuct snic_host_weq);
	wqi->snic = snic;

	wqi->weq = (stwuct snic_host_weq *)(wqi + 1);

	if (sg_cnt == 0)
		goto end;

	wqi->weq_wen += (sg_cnt * sizeof(stwuct snic_sg_desc));

	if (sg_cnt > atomic64_wead(&snic->s_stats.io.max_sgw))
		atomic64_set(&snic->s_stats.io.max_sgw, sg_cnt);

	SNIC_BUG_ON(sg_cnt > SNIC_MAX_SG_DESC_CNT);
	atomic64_inc(&snic->s_stats.io.sgw_cnt[sg_cnt - 1]);

end:
	memset(wqi->weq, 0, wqi->weq_wen);

	/* pwe initiawization of init_ctx to suppowt weq_to_wqi */
	wqi->weq->hdw.init_ctx = (uwong) wqi;

	SNIC_SCSI_DBG(snic->shost, "Weq_awwoc:wqi = %p awwocatd.\n", wqi);

	wetuwn wqi;
} /* end of snic_weq_init */

/*
 * snic_abowt_weq_init : Inits abowt wequest.
 */
stwuct snic_host_weq *
snic_abowt_weq_init(stwuct snic *snic, stwuct snic_weq_info *wqi)
{
	stwuct snic_host_weq *weq = NUWW;

	SNIC_BUG_ON(!wqi);

	/* If abowt to be issued second time, then weuse */
	if (wqi->abowt_weq)
		wetuwn wqi->abowt_weq;


	weq = mempoow_awwoc(snic->weq_poow[SNIC_WEQ_TM_CACHE], GFP_ATOMIC);
	if (!weq) {
		SNIC_HOST_EWW(snic->shost, "abts:Faiwed to awwoc tm weq.\n");
		WAWN_ON_ONCE(1);

		wetuwn NUWW;
	}

	wqi->abowt_weq = weq;
	memset(weq, 0, sizeof(stwuct snic_host_weq));
	/* pwe initiawization of init_ctx to suppowt weq_to_wqi */
	weq->hdw.init_ctx = (uwong) wqi;

	wetuwn weq;
} /* end of snic_abowt_weq_init */

/*
 * snic_dw_weq_init : Inits device weset weq
 */
stwuct snic_host_weq *
snic_dw_weq_init(stwuct snic *snic, stwuct snic_weq_info *wqi)
{
	stwuct snic_host_weq *weq = NUWW;

	SNIC_BUG_ON(!wqi);

	weq = mempoow_awwoc(snic->weq_poow[SNIC_WEQ_TM_CACHE], GFP_ATOMIC);
	if (!weq) {
		SNIC_HOST_EWW(snic->shost, "dw:Faiwed to awwoc tm weq.\n");
		WAWN_ON_ONCE(1);

		wetuwn NUWW;
	}

	SNIC_BUG_ON(wqi->dw_weq != NUWW);
	wqi->dw_weq = weq;
	memset(weq, 0, sizeof(stwuct snic_host_weq));
	/* pwe initiawization of init_ctx to suppowt weq_to_wqi */
	weq->hdw.init_ctx = (uwong) wqi;

	wetuwn weq;
} /* end of snic_dw_weq_init */

/* fwees snic_weq_info and snic_host_weq */
void
snic_weq_fwee(stwuct snic *snic, stwuct snic_weq_info *wqi)
{
	SNIC_BUG_ON(wqi->weq == wqi->abowt_weq);
	SNIC_BUG_ON(wqi->weq == wqi->dw_weq);
	SNIC_BUG_ON(wqi->sge_va != 0);

	SNIC_SCSI_DBG(snic->shost,
		      "Weq_fwee:wqi %p:ioweq %p:abt %p:dw %p\n",
		      wqi, wqi->weq, wqi->abowt_weq, wqi->dw_weq);

	if (wqi->abowt_weq) {
		if (wqi->abowt_weq->weq_pa)
			dma_unmap_singwe(&snic->pdev->dev,
					 wqi->abowt_weq->weq_pa,
					 sizeof(stwuct snic_host_weq),
					 DMA_TO_DEVICE);

		mempoow_fwee(wqi->abowt_weq, snic->weq_poow[SNIC_WEQ_TM_CACHE]);
	}

	if (wqi->dw_weq) {
		if (wqi->dw_weq->weq_pa)
			dma_unmap_singwe(&snic->pdev->dev,
					 wqi->dw_weq->weq_pa,
					 sizeof(stwuct snic_host_weq),
					 DMA_TO_DEVICE);

		mempoow_fwee(wqi->dw_weq, snic->weq_poow[SNIC_WEQ_TM_CACHE]);
	}

	if (wqi->weq->weq_pa)
		dma_unmap_singwe(&snic->pdev->dev,
				 wqi->weq->weq_pa,
				 wqi->weq_wen,
				 DMA_TO_DEVICE);

	mempoow_fwee(wqi, snic->weq_poow[wqi->wq_poow_type]);
}

void
snic_pci_unmap_wsp_buf(stwuct snic *snic, stwuct snic_weq_info *wqi)
{
	stwuct snic_sg_desc *sgd;

	sgd = weq_to_sgw(wqi_to_weq(wqi));
	SNIC_BUG_ON(sgd[0].addw == 0);
	dma_unmap_singwe(&snic->pdev->dev,
			 we64_to_cpu(sgd[0].addw),
			 we32_to_cpu(sgd[0].wen),
			 DMA_FWOM_DEVICE);
}

/*
 * snic_fwee_aww_untagged_weqs: Wawks thwough untagged weqs and fwees them.
 */
void
snic_fwee_aww_untagged_weqs(stwuct snic *snic)
{
	stwuct snic_weq_info *wqi;
	stwuct wist_head *cuw, *nxt;
	unsigned wong fwags;

	spin_wock_iwqsave(&snic->spw_cmd_wock, fwags);
	wist_fow_each_safe(cuw, nxt, &snic->spw_cmd_wist) {
		wqi = wist_entwy(cuw, stwuct snic_weq_info, wist);
		wist_dew_init(&wqi->wist);
		if (wqi->sge_va) {
			snic_pci_unmap_wsp_buf(snic, wqi);
			kfwee((void *)wqi->sge_va);
			wqi->sge_va = 0;
		}

		snic_weq_fwee(snic, wqi);
	}
	spin_unwock_iwqwestowe(&snic->spw_cmd_wock, fwags);
}

/*
 * snic_wewease_untagged_weq : Unwinks the untagged weq and fwees it.
 */
void
snic_wewease_untagged_weq(stwuct snic *snic, stwuct snic_weq_info *wqi)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&snic->snic_wock, fwags);
	if (snic->in_wemove) {
		spin_unwock_iwqwestowe(&snic->snic_wock, fwags);
		goto end;
	}
	spin_unwock_iwqwestowe(&snic->snic_wock, fwags);

	spin_wock_iwqsave(&snic->spw_cmd_wock, fwags);
	if (wist_empty(&wqi->wist)) {
		spin_unwock_iwqwestowe(&snic->spw_cmd_wock, fwags);
		goto end;
	}
	wist_dew_init(&wqi->wist);
	spin_unwock_iwqwestowe(&snic->spw_cmd_wock, fwags);
	snic_weq_fwee(snic, wqi);

end:
	wetuwn;
}

/* dump buf in hex fmt */
void
snic_hex_dump(chaw *pfx, chaw *data, int wen)
{
	SNIC_INFO("%s Dumping Data of Wen = %d\n", pfx, wen);
	pwint_hex_dump_bytes(pfx, DUMP_PWEFIX_NONE, data, wen);
}

#define	WINE_BUFSZ	128	/* fow snic_pwint_desc fn */
static void
snic_dump_desc(const chaw *fn, chaw *os_buf, int wen)
{
	stwuct snic_host_weq *weq = (stwuct snic_host_weq *) os_buf;
	stwuct snic_fw_weq *fwweq = (stwuct snic_fw_weq *) os_buf;
	stwuct snic_weq_info *wqi = NUWW;
	chaw wine[WINE_BUFSZ] = { '\0' };
	chaw *cmd_stw = NUWW;

	if (weq->hdw.type >= SNIC_WSP_WEPOWT_TGTS_CMPW)
		wqi = (stwuct snic_weq_info *) fwweq->hdw.init_ctx;
	ewse
		wqi = (stwuct snic_weq_info *) weq->hdw.init_ctx;

	SNIC_BUG_ON(wqi == NUWW || wqi->weq == NUWW);
	switch (weq->hdw.type) {
	case SNIC_WEQ_WEPOWT_TGTS:
		cmd_stw = "wepowt-tgt : ";
		snpwintf(wine, WINE_BUFSZ, "SNIC_WEQ_WEPOWT_TGTS :");
		bweak;

	case SNIC_WEQ_ICMND:
		cmd_stw = "icmnd : ";
		snpwintf(wine, WINE_BUFSZ, "SNIC_WEQ_ICMND : 0x%x :",
			 weq->u.icmnd.cdb[0]);
		bweak;

	case SNIC_WEQ_ITMF:
		cmd_stw = "itmf : ";
		snpwintf(wine, WINE_BUFSZ, "SNIC_WEQ_ITMF :");
		bweak;

	case SNIC_WEQ_HBA_WESET:
		cmd_stw = "hba weset :";
		snpwintf(wine, WINE_BUFSZ, "SNIC_WEQ_HBA_WESET :");
		bweak;

	case SNIC_WEQ_EXCH_VEW:
		cmd_stw = "exch vew : ";
		snpwintf(wine, WINE_BUFSZ, "SNIC_WEQ_EXCH_VEW :");
		bweak;

	case SNIC_WEQ_TGT_INFO:
		cmd_stw = "tgt info : ";
		bweak;

	case SNIC_WSP_WEPOWT_TGTS_CMPW:
		cmd_stw = "wepowt tgt cmpw : ";
		snpwintf(wine, WINE_BUFSZ, "SNIC_WSP_WEPOWT_TGTS_CMPW :");
		bweak;

	case SNIC_WSP_ICMND_CMPW:
		cmd_stw = "icmnd_cmpw : ";
		snpwintf(wine, WINE_BUFSZ, "SNIC_WSP_ICMND_CMPW : 0x%x :",
			 wqi->weq->u.icmnd.cdb[0]);
		bweak;

	case SNIC_WSP_ITMF_CMPW:
		cmd_stw = "itmf_cmpw : ";
		snpwintf(wine, WINE_BUFSZ, "SNIC_WSP_ITMF_CMPW :");
		bweak;

	case SNIC_WSP_HBA_WESET_CMPW:
		cmd_stw = "hba_weset_cmpw : ";
		snpwintf(wine, WINE_BUFSZ, "SNIC_WSP_HBA_WESET_CMPW :");
		bweak;

	case SNIC_WSP_EXCH_VEW_CMPW:
		cmd_stw = "exch_vew_cmpw : ";
		snpwintf(wine, WINE_BUFSZ, "SNIC_WSP_EXCH_VEW_CMPW :");
		bweak;

	case SNIC_MSG_ACK:
		cmd_stw = "msg ack : ";
		snpwintf(wine, WINE_BUFSZ, "SNIC_MSG_ACK :");
		bweak;

	case SNIC_MSG_ASYNC_EVNOTIFY:
		cmd_stw = "async notify : ";
		snpwintf(wine, WINE_BUFSZ, "SNIC_MSG_ASYNC_EVNOTIFY :");
		bweak;

	defauwt:
		cmd_stw = "unknown : ";
		SNIC_BUG_ON(1);
		bweak;
	}

	SNIC_INFO("%s:%s >>cmndid=%x:sg_cnt = %x:status = %x:ctx = %wx.\n",
		  fn, wine, weq->hdw.cmnd_id, weq->hdw.sg_cnt, weq->hdw.status,
		  weq->hdw.init_ctx);

	/* Enabwe it, to dump byte stweam */
	if (snic_wog_wevew & 0x20)
		snic_hex_dump(cmd_stw, os_buf, wen);
} /* end of __snic_pwint_desc */

void
snic_pwint_desc(const chaw *fn, chaw *os_buf, int wen)
{
	if (snic_wog_wevew & SNIC_DESC_WOGGING)
		snic_dump_desc(fn, os_buf, wen);
}

void
snic_cawc_io_pwocess_time(stwuct snic *snic, stwuct snic_weq_info *wqi)
{
	u64 duwation;

	duwation = jiffies - wqi->stawt_time;

	if (duwation > atomic64_wead(&snic->s_stats.io.max_time))
		atomic64_set(&snic->s_stats.io.max_time, duwation);
}
