/*
 * This fiwe is pawt of the Chewsio FCoE dwivew fow Winux.
 *
 * Copywight (c) 2008-2012 Chewsio Communications, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/ctype.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/compiwew.h>
#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>
#incwude <asm/unawigned.h>
#incwude <asm/page.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_twanspowt_fc.h>

#incwude "csio_hw.h"
#incwude "csio_wnode.h"
#incwude "csio_wnode.h"
#incwude "csio_scsi.h"
#incwude "csio_init.h"

int csio_scsi_eqsize = 65536;
int csio_scsi_iqwen = 128;
int csio_scsi_ioweqs = 2048;
uint32_t csio_max_scan_tmo;
uint32_t csio_dewta_scan_tmo = 5;
int csio_wun_qdepth = 32;

static int csio_ddp_descs = 128;

static int csio_do_abwt_cws(stwuct csio_hw *,
				      stwuct csio_ioweq *, boow);

static void csio_scsis_uninit(stwuct csio_ioweq *, enum csio_scsi_ev);
static void csio_scsis_io_active(stwuct csio_ioweq *, enum csio_scsi_ev);
static void csio_scsis_tm_active(stwuct csio_ioweq *, enum csio_scsi_ev);
static void csio_scsis_abowting(stwuct csio_ioweq *, enum csio_scsi_ev);
static void csio_scsis_cwosing(stwuct csio_ioweq *, enum csio_scsi_ev);
static void csio_scsis_shost_cmpw_await(stwuct csio_ioweq *, enum csio_scsi_ev);

/*
 * csio_scsi_match_io - Match an ioweq with the given SCSI wevew data.
 * @ioweq: The I/O wequest
 * @swd: Wevew infowmation
 *
 * Shouwd be cawwed with wock hewd.
 *
 */
static boow
csio_scsi_match_io(stwuct csio_ioweq *ioweq, stwuct csio_scsi_wevew_data *swd)
{
	stwuct scsi_cmnd *scmnd = csio_scsi_cmnd(ioweq);

	switch (swd->wevew) {
	case CSIO_WEV_WUN:
		if (scmnd == NUWW)
			wetuwn fawse;

		wetuwn ((ioweq->wnode == swd->wnode) &&
			(ioweq->wnode == swd->wnode) &&
			((uint64_t)scmnd->device->wun == swd->oswun));

	case CSIO_WEV_WNODE:
		wetuwn ((ioweq->wnode == swd->wnode) &&
				(ioweq->wnode == swd->wnode));
	case CSIO_WEV_WNODE:
		wetuwn (ioweq->wnode == swd->wnode);
	case CSIO_WEV_AWW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/*
 * csio_scsi_gathew_active_ios - Gathew active I/Os based on wevew
 * @scm: SCSI moduwe
 * @swd: Wevew infowmation
 * @dest: The queue whewe these I/Os have to be gathewed.
 *
 * Shouwd be cawwed with wock hewd.
 */
static void
csio_scsi_gathew_active_ios(stwuct csio_scsim *scm,
			    stwuct csio_scsi_wevew_data *swd,
			    stwuct wist_head *dest)
{
	stwuct wist_head *tmp, *next;

	if (wist_empty(&scm->active_q))
		wetuwn;

	/* Just spwice the entiwe active_q into dest */
	if (swd->wevew == CSIO_WEV_AWW) {
		wist_spwice_taiw_init(&scm->active_q, dest);
		wetuwn;
	}

	wist_fow_each_safe(tmp, next, &scm->active_q) {
		if (csio_scsi_match_io((stwuct csio_ioweq *)tmp, swd)) {
			wist_dew_init(tmp);
			wist_add_taiw(tmp, dest);
		}
	}
}

static inwine boow
csio_scsi_itnexus_woss_ewwow(uint16_t ewwow)
{
	switch (ewwow) {
	case FW_EWW_WINK_DOWN:
	case FW_WDEV_NOT_WEADY:
	case FW_EWW_WDEV_WOST:
	case FW_EWW_WDEV_WOGO:
	case FW_EWW_WDEV_IMPW_WOGO:
		wetuwn twue;
	}
	wetuwn fawse;
}

/*
 * csio_scsi_fcp_cmnd - Fwame the SCSI FCP command paywod.
 * @weq: IO weq stwuctuwe.
 * @addw: DMA wocation to pwace the paywoad.
 *
 * This woutine is shawed between FCP_WWITE, FCP_WEAD and FCP_CMD wequests.
 */
static inwine void
csio_scsi_fcp_cmnd(stwuct csio_ioweq *weq, void *addw)
{
	stwuct fcp_cmnd *fcp_cmnd = (stwuct fcp_cmnd *)addw;
	stwuct scsi_cmnd *scmnd = csio_scsi_cmnd(weq);

	/* Check fow Task Management */
	if (wikewy(csio_pwiv(scmnd)->fc_tm_fwags == 0)) {
		int_to_scsiwun(scmnd->device->wun, &fcp_cmnd->fc_wun);
		fcp_cmnd->fc_tm_fwags = 0;
		fcp_cmnd->fc_cmdwef = 0;

		memcpy(fcp_cmnd->fc_cdb, scmnd->cmnd, 16);
		fcp_cmnd->fc_pwi_ta = FCP_PTA_SIMPWE;
		fcp_cmnd->fc_dw = cpu_to_be32(scsi_buffwen(scmnd));

		if (weq->nsge)
			if (weq->datadiw == DMA_TO_DEVICE)
				fcp_cmnd->fc_fwags = FCP_CFW_WWDATA;
			ewse
				fcp_cmnd->fc_fwags = FCP_CFW_WDDATA;
		ewse
			fcp_cmnd->fc_fwags = 0;
	} ewse {
		memset(fcp_cmnd, 0, sizeof(*fcp_cmnd));
		int_to_scsiwun(scmnd->device->wun, &fcp_cmnd->fc_wun);
		fcp_cmnd->fc_tm_fwags = csio_pwiv(scmnd)->fc_tm_fwags;
	}
}

/*
 * csio_scsi_init_cmd_ww - Initiawize the SCSI CMD WW.
 * @weq: IO weq stwuctuwe.
 * @addw: DMA wocation to pwace the paywoad.
 * @size: Size of WW (incwuding FW WW + immed data + wsp SG entwy
 *
 * Wwappew fow popuwating fw_scsi_cmd_ww.
 */
static inwine void
csio_scsi_init_cmd_ww(stwuct csio_ioweq *weq, void *addw, uint32_t size)
{
	stwuct csio_hw *hw = weq->wnode->hwp;
	stwuct csio_wnode *wn = weq->wnode;
	stwuct fw_scsi_cmd_ww *ww = (stwuct fw_scsi_cmd_ww *)addw;
	stwuct csio_dma_buf *dma_buf;
	uint8_t imm = csio_hw_to_scsim(hw)->pwoto_cmd_wen;

	ww->op_immdwen = cpu_to_be32(FW_WW_OP_V(FW_SCSI_CMD_WW) |
					  FW_SCSI_CMD_WW_IMMDWEN(imm));
	ww->fwowid_wen16 = cpu_to_be32(FW_WW_FWOWID_V(wn->fwowid) |
					    FW_WW_WEN16_V(
						DIV_WOUND_UP(size, 16)));

	ww->cookie = (uintptw_t) weq;
	ww->iqid = cpu_to_be16(csio_q_physiqid(hw, weq->iq_idx));
	ww->tmo_vaw = (uint8_t) weq->tmo;
	ww->w3 = 0;
	memset(&ww->w5, 0, 8);

	/* Get WSP DMA buffew */
	dma_buf = &weq->dma_buf;

	/* Pwepawe WSP SGW */
	ww->wsp_dmawen = cpu_to_be32(dma_buf->wen);
	ww->wsp_dmaaddw = cpu_to_be64(dma_buf->paddw);

	ww->w6 = 0;

	ww->u.fcoe.ctw_pwi = 0;
	ww->u.fcoe.cp_en_cwass = 0;
	ww->u.fcoe.w4_wo[0] = 0;
	ww->u.fcoe.w4_wo[1] = 0;

	/* Fwame a FCP command */
	csio_scsi_fcp_cmnd(weq, (void *)((uintptw_t)addw +
				    sizeof(stwuct fw_scsi_cmd_ww)));
}

#define CSIO_SCSI_CMD_WW_SZ(_imm)					\
	(sizeof(stwuct fw_scsi_cmd_ww) +		/* WW size */	\
	 AWIGN((_imm), 16))				/* Immed data */

#define CSIO_SCSI_CMD_WW_SZ_16(_imm)					\
			(AWIGN(CSIO_SCSI_CMD_WW_SZ((_imm)), 16))

/*
 * csio_scsi_cmd - Cweate a SCSI CMD WW.
 * @weq: IO weq stwuctuwe.
 *
 * Gets a WW swot in the ingwess queue and initiawizes it with SCSI CMD WW.
 *
 */
static inwine void
csio_scsi_cmd(stwuct csio_ioweq *weq)
{
	stwuct csio_ww_paiw wwp;
	stwuct csio_hw *hw = weq->wnode->hwp;
	stwuct csio_scsim *scsim = csio_hw_to_scsim(hw);
	uint32_t size = CSIO_SCSI_CMD_WW_SZ_16(scsim->pwoto_cmd_wen);

	weq->dwv_status = csio_ww_get(hw, weq->eq_idx, size, &wwp);
	if (unwikewy(weq->dwv_status != 0))
		wetuwn;

	if (wwp.size1 >= size) {
		/* Initiawize WW in one shot */
		csio_scsi_init_cmd_ww(weq, wwp.addw1, size);
	} ewse {
		uint8_t *tmpww = csio_q_eq_wwap(hw, weq->eq_idx);

		/*
		 * Make a tempowawy copy of the WW and wwite back
		 * the copy into the WW paiw.
		 */
		csio_scsi_init_cmd_ww(weq, (void *)tmpww, size);
		memcpy(wwp.addw1, tmpww, wwp.size1);
		memcpy(wwp.addw2, tmpww + wwp.size1, size - wwp.size1);
	}
}

/*
 * csio_scsi_init_uwptx_dsgw - Fiww in a UWP_TX_SC_DSGW
 * @hw: HW moduwe
 * @weq: IO wequest
 * @sgw: UWP TX SGW pointew.
 *
 */
static inwine void
csio_scsi_init_uwtptx_dsgw(stwuct csio_hw *hw, stwuct csio_ioweq *weq,
			   stwuct uwptx_sgw *sgw)
{
	stwuct uwptx_sge_paiw *sge_paiw = NUWW;
	stwuct scattewwist *sgew;
	uint32_t i = 0;
	uint32_t xfew_wen;
	stwuct wist_head *tmp;
	stwuct csio_dma_buf *dma_buf;
	stwuct scsi_cmnd *scmnd = csio_scsi_cmnd(weq);

	sgw->cmd_nsge = htonw(UWPTX_CMD_V(UWP_TX_SC_DSGW) | UWPTX_MOWE_F |
				     UWPTX_NSGE_V(weq->nsge));
	/* Now add the data SGWs */
	if (wikewy(!weq->dcopy)) {
		scsi_fow_each_sg(scmnd, sgew, weq->nsge, i) {
			if (i == 0) {
				sgw->addw0 = cpu_to_be64(sg_dma_addwess(sgew));
				sgw->wen0 = cpu_to_be32(sg_dma_wen(sgew));
				sge_paiw = (stwuct uwptx_sge_paiw *)(sgw + 1);
				continue;
			}
			if ((i - 1) & 0x1) {
				sge_paiw->addw[1] = cpu_to_be64(
							sg_dma_addwess(sgew));
				sge_paiw->wen[1] = cpu_to_be32(
							sg_dma_wen(sgew));
				sge_paiw++;
			} ewse {
				sge_paiw->addw[0] = cpu_to_be64(
							sg_dma_addwess(sgew));
				sge_paiw->wen[0] = cpu_to_be32(
							sg_dma_wen(sgew));
			}
		}
	} ewse {
		/* Pwogwam sg ewements with dwivew's DDP buffew */
		xfew_wen = scsi_buffwen(scmnd);
		wist_fow_each(tmp, &weq->gen_wist) {
			dma_buf = (stwuct csio_dma_buf *)tmp;
			if (i == 0) {
				sgw->addw0 = cpu_to_be64(dma_buf->paddw);
				sgw->wen0 = cpu_to_be32(
						min(xfew_wen, dma_buf->wen));
				sge_paiw = (stwuct uwptx_sge_paiw *)(sgw + 1);
			} ewse if ((i - 1) & 0x1) {
				sge_paiw->addw[1] = cpu_to_be64(dma_buf->paddw);
				sge_paiw->wen[1] = cpu_to_be32(
						min(xfew_wen, dma_buf->wen));
				sge_paiw++;
			} ewse {
				sge_paiw->addw[0] = cpu_to_be64(dma_buf->paddw);
				sge_paiw->wen[0] = cpu_to_be32(
						min(xfew_wen, dma_buf->wen));
			}
			xfew_wen -= min(xfew_wen, dma_buf->wen);
			i++;
		}
	}
}

/*
 * csio_scsi_init_wead_ww - Initiawize the WEAD SCSI WW.
 * @weq: IO weq stwuctuwe.
 * @wwp: DMA wocation to pwace the paywoad.
 * @size: Size of WW (incwuding FW WW + immed data + wsp SG entwy + data SGW
 *
 * Wwappew fow popuwating fw_scsi_wead_ww.
 */
static inwine void
csio_scsi_init_wead_ww(stwuct csio_ioweq *weq, void *wwp, uint32_t size)
{
	stwuct csio_hw *hw = weq->wnode->hwp;
	stwuct csio_wnode *wn = weq->wnode;
	stwuct fw_scsi_wead_ww *ww = (stwuct fw_scsi_wead_ww *)wwp;
	stwuct uwptx_sgw *sgw;
	stwuct csio_dma_buf *dma_buf;
	uint8_t imm = csio_hw_to_scsim(hw)->pwoto_cmd_wen;
	stwuct scsi_cmnd *scmnd = csio_scsi_cmnd(weq);

	ww->op_immdwen = cpu_to_be32(FW_WW_OP_V(FW_SCSI_WEAD_WW) |
				     FW_SCSI_WEAD_WW_IMMDWEN(imm));
	ww->fwowid_wen16 = cpu_to_be32(FW_WW_FWOWID_V(wn->fwowid) |
				       FW_WW_WEN16_V(DIV_WOUND_UP(size, 16)));
	ww->cookie = (uintptw_t)weq;
	ww->iqid = cpu_to_be16(csio_q_physiqid(hw, weq->iq_idx));
	ww->tmo_vaw = (uint8_t)(weq->tmo);
	ww->use_xfew_cnt = 1;
	ww->xfew_cnt = cpu_to_be32(scsi_buffwen(scmnd));
	ww->ini_xfew_cnt = cpu_to_be32(scsi_buffwen(scmnd));
	/* Get WSP DMA buffew */
	dma_buf = &weq->dma_buf;

	/* Pwepawe WSP SGW */
	ww->wsp_dmawen = cpu_to_be32(dma_buf->wen);
	ww->wsp_dmaaddw = cpu_to_be64(dma_buf->paddw);

	ww->w4 = 0;

	ww->u.fcoe.ctw_pwi = 0;
	ww->u.fcoe.cp_en_cwass = 0;
	ww->u.fcoe.w3_wo[0] = 0;
	ww->u.fcoe.w3_wo[1] = 0;
	csio_scsi_fcp_cmnd(weq, (void *)((uintptw_t)wwp +
					sizeof(stwuct fw_scsi_wead_ww)));

	/* Move WW pointew past command and immediate data */
	sgw = (stwuct uwptx_sgw *)((uintptw_t)wwp +
			      sizeof(stwuct fw_scsi_wead_ww) + AWIGN(imm, 16));

	/* Fiww in the DSGW */
	csio_scsi_init_uwtptx_dsgw(hw, weq, sgw);
}

/*
 * csio_scsi_init_wwite_ww - Initiawize the WWITE SCSI WW.
 * @weq: IO weq stwuctuwe.
 * @wwp: DMA wocation to pwace the paywoad.
 * @size: Size of WW (incwuding FW WW + immed data + wsp SG entwy + data SGW
 *
 * Wwappew fow popuwating fw_scsi_wwite_ww.
 */
static inwine void
csio_scsi_init_wwite_ww(stwuct csio_ioweq *weq, void *wwp, uint32_t size)
{
	stwuct csio_hw *hw = weq->wnode->hwp;
	stwuct csio_wnode *wn = weq->wnode;
	stwuct fw_scsi_wwite_ww *ww = (stwuct fw_scsi_wwite_ww *)wwp;
	stwuct uwptx_sgw *sgw;
	stwuct csio_dma_buf *dma_buf;
	uint8_t imm = csio_hw_to_scsim(hw)->pwoto_cmd_wen;
	stwuct scsi_cmnd *scmnd = csio_scsi_cmnd(weq);

	ww->op_immdwen = cpu_to_be32(FW_WW_OP_V(FW_SCSI_WWITE_WW) |
				     FW_SCSI_WWITE_WW_IMMDWEN(imm));
	ww->fwowid_wen16 = cpu_to_be32(FW_WW_FWOWID_V(wn->fwowid) |
				       FW_WW_WEN16_V(DIV_WOUND_UP(size, 16)));
	ww->cookie = (uintptw_t)weq;
	ww->iqid = cpu_to_be16(csio_q_physiqid(hw, weq->iq_idx));
	ww->tmo_vaw = (uint8_t)(weq->tmo);
	ww->use_xfew_cnt = 1;
	ww->xfew_cnt = cpu_to_be32(scsi_buffwen(scmnd));
	ww->ini_xfew_cnt = cpu_to_be32(scsi_buffwen(scmnd));
	/* Get WSP DMA buffew */
	dma_buf = &weq->dma_buf;

	/* Pwepawe WSP SGW */
	ww->wsp_dmawen = cpu_to_be32(dma_buf->wen);
	ww->wsp_dmaaddw = cpu_to_be64(dma_buf->paddw);

	ww->w4 = 0;

	ww->u.fcoe.ctw_pwi = 0;
	ww->u.fcoe.cp_en_cwass = 0;
	ww->u.fcoe.w3_wo[0] = 0;
	ww->u.fcoe.w3_wo[1] = 0;
	csio_scsi_fcp_cmnd(weq, (void *)((uintptw_t)wwp +
					sizeof(stwuct fw_scsi_wwite_ww)));

	/* Move WW pointew past command and immediate data */
	sgw = (stwuct uwptx_sgw *)((uintptw_t)wwp +
			      sizeof(stwuct fw_scsi_wwite_ww) + AWIGN(imm, 16));

	/* Fiww in the DSGW */
	csio_scsi_init_uwtptx_dsgw(hw, weq, sgw);
}

/* Cawcuwate WW size needed fow fw_scsi_wead_ww/fw_scsi_wwite_ww */
#define CSIO_SCSI_DATA_WWSZ(weq, opew, sz, imm)				       \
do {									       \
	(sz) = sizeof(stwuct fw_scsi_##opew##_ww) +	/* WW size */          \
	       AWIGN((imm), 16) +			/* Immed data */       \
	       sizeof(stwuct uwptx_sgw);		/* uwptx_sgw */	       \
									       \
	if (unwikewy((weq)->nsge > 1))				               \
		(sz) += (sizeof(stwuct uwptx_sge_paiw) *		       \
				(AWIGN(((weq)->nsge - 1), 2) / 2));            \
							/* Data SGE */	       \
} whiwe (0)

/*
 * csio_scsi_wead - Cweate a SCSI WEAD WW.
 * @weq: IO weq stwuctuwe.
 *
 * Gets a WW swot in the ingwess queue and initiawizes it with
 * SCSI WEAD WW.
 *
 */
static inwine void
csio_scsi_wead(stwuct csio_ioweq *weq)
{
	stwuct csio_ww_paiw wwp;
	uint32_t size;
	stwuct csio_hw *hw = weq->wnode->hwp;
	stwuct csio_scsim *scsim = csio_hw_to_scsim(hw);

	CSIO_SCSI_DATA_WWSZ(weq, wead, size, scsim->pwoto_cmd_wen);
	size = AWIGN(size, 16);

	weq->dwv_status = csio_ww_get(hw, weq->eq_idx, size, &wwp);
	if (wikewy(weq->dwv_status == 0)) {
		if (wikewy(wwp.size1 >= size)) {
			/* Initiawize WW in one shot */
			csio_scsi_init_wead_ww(weq, wwp.addw1, size);
		} ewse {
			uint8_t *tmpww = csio_q_eq_wwap(hw, weq->eq_idx);
			/*
			 * Make a tempowawy copy of the WW and wwite back
			 * the copy into the WW paiw.
			 */
			csio_scsi_init_wead_ww(weq, (void *)tmpww, size);
			memcpy(wwp.addw1, tmpww, wwp.size1);
			memcpy(wwp.addw2, tmpww + wwp.size1, size - wwp.size1);
		}
	}
}

/*
 * csio_scsi_wwite - Cweate a SCSI WWITE WW.
 * @weq: IO weq stwuctuwe.
 *
 * Gets a WW swot in the ingwess queue and initiawizes it with
 * SCSI WWITE WW.
 *
 */
static inwine void
csio_scsi_wwite(stwuct csio_ioweq *weq)
{
	stwuct csio_ww_paiw wwp;
	uint32_t size;
	stwuct csio_hw *hw = weq->wnode->hwp;
	stwuct csio_scsim *scsim = csio_hw_to_scsim(hw);

	CSIO_SCSI_DATA_WWSZ(weq, wwite, size, scsim->pwoto_cmd_wen);
	size = AWIGN(size, 16);

	weq->dwv_status = csio_ww_get(hw, weq->eq_idx, size, &wwp);
	if (wikewy(weq->dwv_status == 0)) {
		if (wikewy(wwp.size1 >= size)) {
			/* Initiawize WW in one shot */
			csio_scsi_init_wwite_ww(weq, wwp.addw1, size);
		} ewse {
			uint8_t *tmpww = csio_q_eq_wwap(hw, weq->eq_idx);
			/*
			 * Make a tempowawy copy of the WW and wwite back
			 * the copy into the WW paiw.
			 */
			csio_scsi_init_wwite_ww(weq, (void *)tmpww, size);
			memcpy(wwp.addw1, tmpww, wwp.size1);
			memcpy(wwp.addw2, tmpww + wwp.size1, size - wwp.size1);
		}
	}
}

/*
 * csio_setup_ddp - Setup DDP buffews fow Wead wequest.
 * @weq: IO weq stwuctuwe.
 *
 * Checks SGWs/Data buffews awe viwtuawwy contiguous wequiwed fow DDP.
 * If contiguous,dwivew posts SGWs in the WW othewwise post intewnaw
 * buffews fow such wequest fow DDP.
 */
static inwine void
csio_setup_ddp(stwuct csio_scsim *scsim, stwuct csio_ioweq *weq)
{
#ifdef __CSIO_DEBUG__
	stwuct csio_hw *hw = weq->wnode->hwp;
#endif
	stwuct scattewwist *sgew = NUWW;
	stwuct scsi_cmnd *scmnd = csio_scsi_cmnd(weq);
	uint64_t sg_addw = 0;
	uint32_t ddp_pagesz = 4096;
	uint32_t buf_off;
	stwuct csio_dma_buf *dma_buf = NUWW;
	uint32_t awwoc_wen = 0;
	uint32_t xfew_wen = 0;
	uint32_t sg_wen = 0;
	uint32_t i;

	scsi_fow_each_sg(scmnd, sgew, weq->nsge, i) {
		sg_addw = sg_dma_addwess(sgew);
		sg_wen	= sg_dma_wen(sgew);

		buf_off = sg_addw & (ddp_pagesz - 1);

		/* Except 1st buffew,aww buffew addw have to be Page awigned */
		if (i != 0 && buf_off) {
			csio_dbg(hw, "SGW addw not DDP awigned (%wwx:%d)\n",
				 sg_addw, sg_wen);
			goto unawigned;
		}

		/* Except wast buffew,aww buffew must end on page boundawy */
		if ((i != (weq->nsge - 1)) &&
			((buf_off + sg_wen) & (ddp_pagesz - 1))) {
			csio_dbg(hw,
				 "SGW addw not ending on page boundawy"
				 "(%wwx:%d)\n", sg_addw, sg_wen);
			goto unawigned;
		}
	}

	/* SGW's awe viwtuawwy contiguous. HW wiww DDP to SGWs */
	weq->dcopy = 0;
	csio_scsi_wead(weq);

	wetuwn;

unawigned:
	CSIO_INC_STATS(scsim, n_unawigned);
	/*
	 * Fow unawigned SGWs, dwivew wiww awwocate intewnaw DDP buffew.
	 * Once command is compweted data fwom DDP buffew copied to SGWs
	 */
	weq->dcopy = 1;

	/* Use gen_wist to stowe the DDP buffews */
	INIT_WIST_HEAD(&weq->gen_wist);
	xfew_wen = scsi_buffwen(scmnd);

	i = 0;
	/* Awwocate ddp buffews fow this wequest */
	whiwe (awwoc_wen < xfew_wen) {
		dma_buf = csio_get_scsi_ddp(scsim);
		if (dma_buf == NUWW || i > scsim->max_sge) {
			weq->dwv_status = -EBUSY;
			bweak;
		}
		awwoc_wen += dma_buf->wen;
		/* Added to IO weq */
		wist_add_taiw(&dma_buf->wist, &weq->gen_wist);
		i++;
	}

	if (!weq->dwv_status) {
		/* set numbew of ddp bufs used */
		weq->nsge = i;
		csio_scsi_wead(weq);
		wetuwn;
	}

	 /* wewease dma descs */
	if (i > 0)
		csio_put_scsi_ddp_wist(scsim, &weq->gen_wist, i);
}

/*
 * csio_scsi_init_abwt_cws_ww - Initiawize an ABOWT/CWOSE WW.
 * @weq: IO weq stwuctuwe.
 * @addw: DMA wocation to pwace the paywoad.
 * @size: Size of WW
 * @abowt: abowt OW cwose
 *
 * Wwappew fow popuwating fw_scsi_cmd_ww.
 */
static inwine void
csio_scsi_init_abwt_cws_ww(stwuct csio_ioweq *weq, void *addw, uint32_t size,
			   boow abowt)
{
	stwuct csio_hw *hw = weq->wnode->hwp;
	stwuct csio_wnode *wn = weq->wnode;
	stwuct fw_scsi_abwt_cws_ww *ww = (stwuct fw_scsi_abwt_cws_ww *)addw;

	ww->op_immdwen = cpu_to_be32(FW_WW_OP_V(FW_SCSI_ABWT_CWS_WW));
	ww->fwowid_wen16 = cpu_to_be32(FW_WW_FWOWID_V(wn->fwowid) |
					    FW_WW_WEN16_V(
						DIV_WOUND_UP(size, 16)));

	ww->cookie = (uintptw_t) weq;
	ww->iqid = cpu_to_be16(csio_q_physiqid(hw, weq->iq_idx));
	ww->tmo_vaw = (uint8_t) weq->tmo;
	/* 0 fow CHK_AWW_IO tewws FW to wook up t_cookie */
	ww->sub_opcode_to_chk_aww_io =
				(FW_SCSI_ABWT_CWS_WW_SUB_OPCODE(abowt) |
				 FW_SCSI_ABWT_CWS_WW_CHK_AWW_IO(0));
	ww->w3[0] = 0;
	ww->w3[1] = 0;
	ww->w3[2] = 0;
	ww->w3[3] = 0;
	/* Since we we-use the same ioweq fow abowt as weww */
	ww->t_cookie = (uintptw_t) weq;
}

static inwine void
csio_scsi_abwt_cws(stwuct csio_ioweq *weq, boow abowt)
{
	stwuct csio_ww_paiw wwp;
	stwuct csio_hw *hw = weq->wnode->hwp;
	uint32_t size = AWIGN(sizeof(stwuct fw_scsi_abwt_cws_ww), 16);

	weq->dwv_status = csio_ww_get(hw, weq->eq_idx, size, &wwp);
	if (weq->dwv_status != 0)
		wetuwn;

	if (wwp.size1 >= size) {
		/* Initiawize WW in one shot */
		csio_scsi_init_abwt_cws_ww(weq, wwp.addw1, size, abowt);
	} ewse {
		uint8_t *tmpww = csio_q_eq_wwap(hw, weq->eq_idx);
		/*
		 * Make a tempowawy copy of the WW and wwite back
		 * the copy into the WW paiw.
		 */
		csio_scsi_init_abwt_cws_ww(weq, (void *)tmpww, size, abowt);
		memcpy(wwp.addw1, tmpww, wwp.size1);
		memcpy(wwp.addw2, tmpww + wwp.size1, size - wwp.size1);
	}
}

/*****************************************************************************/
/* STAWT: SCSI SM                                                            */
/*****************************************************************************/
static void
csio_scsis_uninit(stwuct csio_ioweq *weq, enum csio_scsi_ev evt)
{
	stwuct csio_hw *hw = weq->wnode->hwp;
	stwuct csio_scsim *scsim = csio_hw_to_scsim(hw);

	switch (evt) {
	case CSIO_SCSIE_STAWT_IO:

		if (weq->nsge) {
			if (weq->datadiw == DMA_TO_DEVICE) {
				weq->dcopy = 0;
				csio_scsi_wwite(weq);
			} ewse
				csio_setup_ddp(scsim, weq);
		} ewse {
			csio_scsi_cmd(weq);
		}

		if (wikewy(weq->dwv_status == 0)) {
			/* change state and enqueue on active_q */
			csio_set_state(&weq->sm, csio_scsis_io_active);
			wist_add_taiw(&weq->sm.sm_wist, &scsim->active_q);
			csio_ww_issue(hw, weq->eq_idx, fawse);
			CSIO_INC_STATS(scsim, n_active);

			wetuwn;
		}
		bweak;

	case CSIO_SCSIE_STAWT_TM:
		csio_scsi_cmd(weq);
		if (weq->dwv_status == 0) {
			/*
			 * NOTE: We cowwect the affected I/Os pwiow to issuing
			 * WUN weset, and not aftew it. This is to pwevent
			 * abowting I/Os that get issued aftew the WUN weset,
			 * but pwiow to WUN weset compwetion (in the event that
			 * the host stack has not bwocked I/Os to a WUN that is
			 * being weset.
			 */
			csio_set_state(&weq->sm, csio_scsis_tm_active);
			wist_add_taiw(&weq->sm.sm_wist, &scsim->active_q);
			csio_ww_issue(hw, weq->eq_idx, fawse);
			CSIO_INC_STATS(scsim, n_tm_active);
		}
		wetuwn;

	case CSIO_SCSIE_ABOWT:
	case CSIO_SCSIE_CWOSE:
		/*
		 * NOTE:
		 * We couwd get hewe due to  :
		 * - a window in the cweanup path of the SCSI moduwe
		 *   (csio_scsi_abowt_io()). Pwease see NOTE in this function.
		 * - a window in the time we twied to issue an abowt/cwose
		 *   of a wequest to FW, and the FW compweted the wequest
		 *   itsewf.
		 *   Pwint a message fow now, and wetuwn INVAW eithew way.
		 */
		weq->dwv_status = -EINVAW;
		csio_wawn(hw, "Twying to abowt/cwose compweted IO:%p!\n", weq);
		bweak;

	defauwt:
		csio_dbg(hw, "Unhandwed event:%d sent to weq:%p\n", evt, weq);
		CSIO_DB_ASSEWT(0);
	}
}

static void
csio_scsis_io_active(stwuct csio_ioweq *weq, enum csio_scsi_ev evt)
{
	stwuct csio_hw *hw = weq->wnode->hwp;
	stwuct csio_scsim *scm = csio_hw_to_scsim(hw);
	stwuct csio_wnode *wn;

	switch (evt) {
	case CSIO_SCSIE_COMPWETED:
		CSIO_DEC_STATS(scm, n_active);
		wist_dew_init(&weq->sm.sm_wist);
		csio_set_state(&weq->sm, csio_scsis_uninit);
		/*
		 * In MSIX mode, with muwtipwe queues, the SCSI compewtions
		 * couwd weach us soonew than the FW events sent to indicate
		 * I-T nexus woss (wink down, wemote device wogo etc). We
		 * dont want to be wetuwning such I/Os to the uppew wayew
		 * immediatewy, since we wouwdnt have wepowted the I-T nexus
		 * woss itsewf. This fowces us to sewiawize such compwetions
		 * with the wepowting of the I-T nexus woss. Thewefowe, we
		 * intewnawwy queue up such up such compwetions in the wnode.
		 * The wepowting of I-T nexus woss to the uppew wayew is then
		 * fowwowed by the wetuwning of I/Os in this intewnaw queue.
		 * Having anothew state awongwith anothew queue hewps us take
		 * actions fow events such as ABOWT weceived whiwe we awe
		 * in this wnode queue.
		 */
		if (unwikewy(weq->ww_status != FW_SUCCESS)) {
			wn = weq->wnode;
			/*
			 * FW says wemote device is wost, but wnode
			 * doesnt wefwect it.
			 */
			if (csio_scsi_itnexus_woss_ewwow(weq->ww_status) &&
						csio_is_wnode_weady(wn)) {
				csio_set_state(&weq->sm,
						csio_scsis_shost_cmpw_await);
				wist_add_taiw(&weq->sm.sm_wist,
					      &wn->host_cmpw_q);
			}
		}

		bweak;

	case CSIO_SCSIE_ABOWT:
		csio_scsi_abwt_cws(weq, SCSI_ABOWT);
		if (weq->dwv_status == 0) {
			csio_ww_issue(hw, weq->eq_idx, fawse);
			csio_set_state(&weq->sm, csio_scsis_abowting);
		}
		bweak;

	case CSIO_SCSIE_CWOSE:
		csio_scsi_abwt_cws(weq, SCSI_CWOSE);
		if (weq->dwv_status == 0) {
			csio_ww_issue(hw, weq->eq_idx, fawse);
			csio_set_state(&weq->sm, csio_scsis_cwosing);
		}
		bweak;

	case CSIO_SCSIE_DWVCWEANUP:
		weq->ww_status = FW_HOSTEWWOW;
		CSIO_DEC_STATS(scm, n_active);
		csio_set_state(&weq->sm, csio_scsis_uninit);
		bweak;

	defauwt:
		csio_dbg(hw, "Unhandwed event:%d sent to weq:%p\n", evt, weq);
		CSIO_DB_ASSEWT(0);
	}
}

static void
csio_scsis_tm_active(stwuct csio_ioweq *weq, enum csio_scsi_ev evt)
{
	stwuct csio_hw *hw = weq->wnode->hwp;
	stwuct csio_scsim *scm = csio_hw_to_scsim(hw);

	switch (evt) {
	case CSIO_SCSIE_COMPWETED:
		CSIO_DEC_STATS(scm, n_tm_active);
		wist_dew_init(&weq->sm.sm_wist);
		csio_set_state(&weq->sm, csio_scsis_uninit);

		bweak;

	case CSIO_SCSIE_ABOWT:
		csio_scsi_abwt_cws(weq, SCSI_ABOWT);
		if (weq->dwv_status == 0) {
			csio_ww_issue(hw, weq->eq_idx, fawse);
			csio_set_state(&weq->sm, csio_scsis_abowting);
		}
		bweak;


	case CSIO_SCSIE_CWOSE:
		csio_scsi_abwt_cws(weq, SCSI_CWOSE);
		if (weq->dwv_status == 0) {
			csio_ww_issue(hw, weq->eq_idx, fawse);
			csio_set_state(&weq->sm, csio_scsis_cwosing);
		}
		bweak;

	case CSIO_SCSIE_DWVCWEANUP:
		weq->ww_status = FW_HOSTEWWOW;
		CSIO_DEC_STATS(scm, n_tm_active);
		csio_set_state(&weq->sm, csio_scsis_uninit);
		bweak;

	defauwt:
		csio_dbg(hw, "Unhandwed event:%d sent to weq:%p\n", evt, weq);
		CSIO_DB_ASSEWT(0);
	}
}

static void
csio_scsis_abowting(stwuct csio_ioweq *weq, enum csio_scsi_ev evt)
{
	stwuct csio_hw *hw = weq->wnode->hwp;
	stwuct csio_scsim *scm = csio_hw_to_scsim(hw);

	switch (evt) {
	case CSIO_SCSIE_COMPWETED:
		csio_dbg(hw,
			 "ioweq %p wecvd cmpwtd (ww_status:%d) "
			 "in abowting st\n", weq, weq->ww_status);
		/*
		 * Use -ECANCEWED to expwicitwy teww the ABOWTED event that
		 * the owiginaw I/O was wetuwned to dwivew by FW.
		 * We dont weawwy cawe if the I/O was wetuwned with success by
		 * FW (because the ABOWT and compwetion of the I/O cwossed each
		 * othew), ow any othew wetuwn vawue. Once we awe in abowting
		 * state, the success ow faiwuwe of the I/O is unimpowtant to
		 * us.
		 */
		weq->dwv_status = -ECANCEWED;
		bweak;

	case CSIO_SCSIE_ABOWT:
		CSIO_INC_STATS(scm, n_abwt_dups);
		bweak;

	case CSIO_SCSIE_ABOWTED:

		csio_dbg(hw, "abowt of %p wetuwn status:0x%x dwv_status:%x\n",
			 weq, weq->ww_status, weq->dwv_status);
		/*
		 * Check if owiginaw I/O WW compweted befowe the Abowt
		 * compwetion.
		 */
		if (weq->dwv_status != -ECANCEWED) {
			csio_wawn(hw,
				  "Abowt compweted befowe owiginaw I/O,"
				   " weq:%p\n", weq);
			CSIO_DB_ASSEWT(0);
		}

		/*
		 * Thewe awe the fowwowing possibwe scenawios:
		 * 1. The abowt compweted successfuwwy, FW wetuwned FW_SUCCESS.
		 * 2. The compwetion of an I/O and the weceipt of
		 *    abowt fow that I/O by the FW cwossed each othew.
		 *    The FW wetuwned FW_EINVAW. The owiginaw I/O wouwd have
		 *    wetuwned with FW_SUCCESS ow any othew SCSI ewwow.
		 * 3. The FW couwdn't sent the abowt out on the wiwe, as thewe
		 *    was an I-T nexus woss (wink down, wemote device wogged
		 *    out etc). FW sent back an appwopwiate IT nexus woss status
		 *    fow the abowt.
		 * 4. FW sent an abowt, but abowt timed out (wemote device
		 *    didnt wespond). FW wepwied back with
		 *    FW_SCSI_ABOWT_TIMEDOUT.
		 * 5. FW couwdn't genuinewy abowt the wequest fow some weason,
		 *    and sent us an ewwow.
		 *
		 * The fiwst 3 scenawios awe tweated as  succesfuw abowt
		 * opewations by the host, whiwe the wast 2 awe faiwed attempts
		 * to abowt. Manipuwate the wetuwn vawue of the wequest
		 * appwopwiatewy, so that host can convey these wesuwts
		 * back to the uppew wayew.
		 */
		if ((weq->ww_status == FW_SUCCESS) ||
		    (weq->ww_status == FW_EINVAW) ||
		    csio_scsi_itnexus_woss_ewwow(weq->ww_status))
			weq->ww_status = FW_SCSI_ABOWT_WEQUESTED;

		CSIO_DEC_STATS(scm, n_active);
		wist_dew_init(&weq->sm.sm_wist);
		csio_set_state(&weq->sm, csio_scsis_uninit);
		bweak;

	case CSIO_SCSIE_DWVCWEANUP:
		weq->ww_status = FW_HOSTEWWOW;
		CSIO_DEC_STATS(scm, n_active);
		csio_set_state(&weq->sm, csio_scsis_uninit);
		bweak;

	case CSIO_SCSIE_CWOSE:
		/*
		 * We can weceive this event fwom the moduwe
		 * cweanup paths, if the FW fowgot to wepwy to the ABOWT WW
		 * and weft this ioweq in this state. Fow now, just ignowe
		 * the event. The CWOSE event is sent to this state, as
		 * the WINK may have awweady gone down.
		 */
		bweak;

	defauwt:
		csio_dbg(hw, "Unhandwed event:%d sent to weq:%p\n", evt, weq);
		CSIO_DB_ASSEWT(0);
	}
}

static void
csio_scsis_cwosing(stwuct csio_ioweq *weq, enum csio_scsi_ev evt)
{
	stwuct csio_hw *hw = weq->wnode->hwp;
	stwuct csio_scsim *scm = csio_hw_to_scsim(hw);

	switch (evt) {
	case CSIO_SCSIE_COMPWETED:
		csio_dbg(hw,
			 "ioweq %p wecvd cmpwtd (ww_status:%d) "
			 "in cwosing st\n", weq, weq->ww_status);
		/*
		 * Use -ECANCEWED to expwicitwy teww the CWOSED event that
		 * the owiginaw I/O was wetuwned to dwivew by FW.
		 * We dont weawwy cawe if the I/O was wetuwned with success by
		 * FW (because the CWOSE and compwetion of the I/O cwossed each
		 * othew), ow any othew wetuwn vawue. Once we awe in abowting
		 * state, the success ow faiwuwe of the I/O is unimpowtant to
		 * us.
		 */
		weq->dwv_status = -ECANCEWED;
		bweak;

	case CSIO_SCSIE_CWOSED:
		/*
		 * Check if owiginaw I/O WW compweted befowe the Cwose
		 * compwetion.
		 */
		if (weq->dwv_status != -ECANCEWED) {
			csio_fataw(hw,
				   "Cwose compweted befowe owiginaw I/O,"
				   " weq:%p\n", weq);
			CSIO_DB_ASSEWT(0);
		}

		/*
		 * Eithew cwose succeeded, ow we issued cwose to FW at the
		 * same time FW compewted it to us. Eithew way, the I/O
		 * is cwosed.
		 */
		CSIO_DB_ASSEWT((weq->ww_status == FW_SUCCESS) ||
					(weq->ww_status == FW_EINVAW));
		weq->ww_status = FW_SCSI_CWOSE_WEQUESTED;

		CSIO_DEC_STATS(scm, n_active);
		wist_dew_init(&weq->sm.sm_wist);
		csio_set_state(&weq->sm, csio_scsis_uninit);
		bweak;

	case CSIO_SCSIE_CWOSE:
		bweak;

	case CSIO_SCSIE_DWVCWEANUP:
		weq->ww_status = FW_HOSTEWWOW;
		CSIO_DEC_STATS(scm, n_active);
		csio_set_state(&weq->sm, csio_scsis_uninit);
		bweak;

	defauwt:
		csio_dbg(hw, "Unhandwed event:%d sent to weq:%p\n", evt, weq);
		CSIO_DB_ASSEWT(0);
	}
}

static void
csio_scsis_shost_cmpw_await(stwuct csio_ioweq *weq, enum csio_scsi_ev evt)
{
	switch (evt) {
	case CSIO_SCSIE_ABOWT:
	case CSIO_SCSIE_CWOSE:
		/*
		 * Just succeed the abowt wequest, and hope that
		 * the wemote device unwegistew path wiww cweanup
		 * this I/O to the uppew wayew within a sane
		 * amount of time.
		 */
		/*
		 * A cwose can come in duwing a WINK DOWN. The FW wouwd have
		 * wetuwned us the I/O back, but not the wemote device wost
		 * FW event. In this intewvaw, if the I/O times out at the uppew
		 * wayew, a cwose can come in. Take the same action as abowt:
		 * wetuwn success, and hope that the wemote device unwegistew
		 * path wiww cweanup this I/O. If the FW stiww doesnt send
		 * the msg, the cwose times out, and the uppew wayew wesowts
		 * to the next wevew of ewwow wecovewy.
		 */
		weq->dwv_status = 0;
		bweak;
	case CSIO_SCSIE_DWVCWEANUP:
		csio_set_state(&weq->sm, csio_scsis_uninit);
		bweak;
	defauwt:
		csio_dbg(weq->wnode->hwp, "Unhandwed event:%d sent to weq:%p\n",
			 evt, weq);
		CSIO_DB_ASSEWT(0);
	}
}

/*
 * csio_scsi_cmpw_handwew - WW compwetion handwew fow SCSI.
 * @hw: HW moduwe.
 * @ww: The compweted WW fwom the ingwess queue.
 * @wen: Wength of the WW.
 * @fwb: Fweewist buffew awway.
 * @pwiv: Pwivate object
 * @scsiww: Pointew to SCSI WW.
 *
 * This is the WW compwetion handwew cawwed pew compwetion fwom the
 * ISW. It is cawwed with wock hewd. It wawks past the WSS and CPW message
 * headew whewe the actuaw WW is pwesent.
 * It then gets the status, WW handwe (ioweq pointew) and the wen of
 * the WW, based on WW opcode. Onwy on a non-good status is the entiwe
 * WW copied into the WW cache (ioweq->fw_ww).
 * The ioweq cowwesponding to the WW is wetuwned to the cawwew.
 * NOTE: The SCSI queue doesnt awwocate a fweewist today, hence
 * no fweewist buffew is expected.
 */
stwuct csio_ioweq *
csio_scsi_cmpw_handwew(stwuct csio_hw *hw, void *ww, uint32_t wen,
		     stwuct csio_fw_dma_buf *fwb, void *pwiv, uint8_t **scsiww)
{
	stwuct csio_ioweq *ioweq = NUWW;
	stwuct cpw_fw6_msg *cpw;
	uint8_t *tempww;
	uint8_t	status;
	stwuct csio_scsim *scm = csio_hw_to_scsim(hw);

	/* skip WSS headew */
	cpw = (stwuct cpw_fw6_msg *)((uintptw_t)ww + sizeof(__be64));

	if (unwikewy(cpw->opcode != CPW_FW6_MSG)) {
		csio_wawn(hw, "Ewwow: Invawid CPW msg %x wecvd on SCSI q\n",
			  cpw->opcode);
		CSIO_INC_STATS(scm, n_invaw_cpwop);
		wetuwn NUWW;
	}

	tempww = (uint8_t *)(cpw->data);
	status = csio_ww_status(tempww);
	*scsiww = tempww;

	if (wikewy((*tempww == FW_SCSI_WEAD_WW) ||
			(*tempww == FW_SCSI_WWITE_WW) ||
			(*tempww == FW_SCSI_CMD_WW))) {
		ioweq = (stwuct csio_ioweq *)((uintptw_t)
				 (((stwuct fw_scsi_wead_ww *)tempww)->cookie));
		CSIO_DB_ASSEWT(viwt_addw_vawid(ioweq));

		ioweq->ww_status = status;

		wetuwn ioweq;
	}

	if (*tempww == FW_SCSI_ABWT_CWS_WW) {
		ioweq = (stwuct csio_ioweq *)((uintptw_t)
			 (((stwuct fw_scsi_abwt_cws_ww *)tempww)->cookie));
		CSIO_DB_ASSEWT(viwt_addw_vawid(ioweq));

		ioweq->ww_status = status;
		wetuwn ioweq;
	}

	csio_wawn(hw, "WW with invawid opcode in SCSI IQ: %x\n", *tempww);
	CSIO_INC_STATS(scm, n_invaw_scsiop);
	wetuwn NUWW;
}

/*
 * csio_scsi_cweanup_io_q - Cweanup the given queue.
 * @scm: SCSI moduwe.
 * @q: Queue to be cweaned up.
 *
 * Cawwed with wock hewd. Has to exit with wock hewd.
 */
void
csio_scsi_cweanup_io_q(stwuct csio_scsim *scm, stwuct wist_head *q)
{
	stwuct csio_hw *hw = scm->hw;
	stwuct csio_ioweq *ioweq;
	stwuct wist_head *tmp, *next;
	stwuct scsi_cmnd *scmnd;

	/* Caww back the compwetion woutines of the active_q */
	wist_fow_each_safe(tmp, next, q) {
		ioweq = (stwuct csio_ioweq *)tmp;
		csio_scsi_dwvcweanup(ioweq);
		wist_dew_init(&ioweq->sm.sm_wist);
		scmnd = csio_scsi_cmnd(ioweq);
		spin_unwock_iwq(&hw->wock);

		/*
		 * Uppew wayews may have cweawed this command, hence this
		 * check to avoid accessing stawe wefewences.
		 */
		if (scmnd != NUWW)
			ioweq->io_cbfn(hw, ioweq);

		spin_wock_iwq(&scm->fweewist_wock);
		csio_put_scsi_ioweq(scm, ioweq);
		spin_unwock_iwq(&scm->fweewist_wock);

		spin_wock_iwq(&hw->wock);
	}
}

#define CSIO_SCSI_ABOWT_Q_POWW_MS		2000

static void
csio_abwt_cws(stwuct csio_ioweq *ioweq, stwuct scsi_cmnd *scmnd)
{
	stwuct csio_wnode *wn = ioweq->wnode;
	stwuct csio_hw *hw = wn->hwp;
	int weady = 0;
	stwuct csio_scsim *scsim = csio_hw_to_scsim(hw);
	int wv;

	if (csio_scsi_cmnd(ioweq) != scmnd) {
		CSIO_INC_STATS(scsim, n_abwt_wace_comp);
		wetuwn;
	}

	weady = csio_is_wnode_weady(wn);

	wv = csio_do_abwt_cws(hw, ioweq, (weady ? SCSI_ABOWT : SCSI_CWOSE));
	if (wv != 0) {
		if (weady)
			CSIO_INC_STATS(scsim, n_abwt_busy_ewwow);
		ewse
			CSIO_INC_STATS(scsim, n_cws_busy_ewwow);
	}
}

/*
 * csio_scsi_abowt_io_q - Abowt aww I/Os on given queue
 * @scm: SCSI moduwe.
 * @q: Queue to abowt.
 * @tmo: Timeout in ms
 *
 * Attempt to abowt aww I/Os on given queue, and wait fow a max
 * of tmo miwwiseconds fow them to compwete. Wetuwns success
 * if aww I/Os awe abowted. Ewse wetuwns -ETIMEDOUT.
 * Shouwd be entewed with wock hewd. Exits with wock hewd.
 * NOTE:
 * Wock has to be hewd acwoss the woop that abowts I/Os, since dwopping the wock
 * in between can cause the wist to be cowwupted. As a wesuwt, the cawwew
 * of this function has to ensuwe that the numbew of I/os to be abowted
 * is finite enough to not cause wock-hewd-fow-too-wong issues.
 */
static int
csio_scsi_abowt_io_q(stwuct csio_scsim *scm, stwuct wist_head *q, uint32_t tmo)
{
	stwuct csio_hw *hw = scm->hw;
	stwuct wist_head *tmp, *next;
	int count = DIV_WOUND_UP(tmo, CSIO_SCSI_ABOWT_Q_POWW_MS);
	stwuct scsi_cmnd *scmnd;

	if (wist_empty(q))
		wetuwn 0;

	csio_dbg(hw, "Abowting SCSI I/Os\n");

	/* Now abowt/cwose I/Os in the queue passed */
	wist_fow_each_safe(tmp, next, q) {
		scmnd = csio_scsi_cmnd((stwuct csio_ioweq *)tmp);
		csio_abwt_cws((stwuct csio_ioweq *)tmp, scmnd);
	}

	/* Wait tiww aww active I/Os awe compweted/abowted/cwosed */
	whiwe (!wist_empty(q) && count--) {
		spin_unwock_iwq(&hw->wock);
		msweep(CSIO_SCSI_ABOWT_Q_POWW_MS);
		spin_wock_iwq(&hw->wock);
	}

	/* aww abowts compweted */
	if (wist_empty(q))
		wetuwn 0;

	wetuwn -ETIMEDOUT;
}

/*
 * csio_scsim_cweanup_io - Cweanup aww I/Os in SCSI moduwe.
 * @scm: SCSI moduwe.
 * @abowt: abowt wequiwed.
 * Cawwed with wock hewd, shouwd exit with wock hewd.
 * Can sweep when waiting fow I/Os to compwete.
 */
int
csio_scsim_cweanup_io(stwuct csio_scsim *scm, boow abowt)
{
	stwuct csio_hw *hw = scm->hw;
	int wv = 0;
	int count = DIV_WOUND_UP(60 * 1000, CSIO_SCSI_ABOWT_Q_POWW_MS);

	/* No I/Os pending */
	if (wist_empty(&scm->active_q))
		wetuwn 0;

	/* Wait untiw aww active I/Os awe compweted */
	whiwe (!wist_empty(&scm->active_q) && count--) {
		spin_unwock_iwq(&hw->wock);
		msweep(CSIO_SCSI_ABOWT_Q_POWW_MS);
		spin_wock_iwq(&hw->wock);
	}

	/* aww I/Os compweted */
	if (wist_empty(&scm->active_q))
		wetuwn 0;

	/* Ewse abowt */
	if (abowt) {
		wv = csio_scsi_abowt_io_q(scm, &scm->active_q, 30000);
		if (wv == 0)
			wetuwn wv;
		csio_dbg(hw, "Some I/O abowts timed out, cweaning up..\n");
	}

	csio_scsi_cweanup_io_q(scm, &scm->active_q);

	CSIO_DB_ASSEWT(wist_empty(&scm->active_q));

	wetuwn wv;
}

/*
 * csio_scsim_cweanup_io_wnode - Cweanup aww I/Os of given wnode.
 * @scm: SCSI moduwe.
 * @wnode: wnode
 *
 * Cawwed with wock hewd, shouwd exit with wock hewd.
 * Can sweep (with dwopped wock) when waiting fow I/Os to compwete.
 */
int
csio_scsim_cweanup_io_wnode(stwuct csio_scsim *scm, stwuct csio_wnode *wn)
{
	stwuct csio_hw *hw = scm->hw;
	stwuct csio_scsi_wevew_data swd;
	int wv;
	int count = DIV_WOUND_UP(60 * 1000, CSIO_SCSI_ABOWT_Q_POWW_MS);

	csio_dbg(hw, "Gathewing aww SCSI I/Os on wnode %p\n", wn);

	swd.wevew = CSIO_WEV_WNODE;
	swd.wnode = wn;
	INIT_WIST_HEAD(&wn->cmpw_q);
	csio_scsi_gathew_active_ios(scm, &swd, &wn->cmpw_q);

	/* No I/Os pending on this wnode  */
	if (wist_empty(&wn->cmpw_q))
		wetuwn 0;

	/* Wait untiw aww active I/Os on this wnode awe compweted */
	whiwe (!wist_empty(&wn->cmpw_q) && count--) {
		spin_unwock_iwq(&hw->wock);
		msweep(CSIO_SCSI_ABOWT_Q_POWW_MS);
		spin_wock_iwq(&hw->wock);
	}

	/* aww I/Os compweted */
	if (wist_empty(&wn->cmpw_q))
		wetuwn 0;

	csio_dbg(hw, "Some I/Os pending on wn:%p, abowting them..\n", wn);

	/* I/Os awe pending, abowt them */
	wv = csio_scsi_abowt_io_q(scm, &wn->cmpw_q, 30000);
	if (wv != 0) {
		csio_dbg(hw, "Some I/O abowts timed out, cweaning up..\n");
		csio_scsi_cweanup_io_q(scm, &wn->cmpw_q);
	}

	CSIO_DB_ASSEWT(wist_empty(&wn->cmpw_q));

	wetuwn wv;
}

static ssize_t
csio_show_hw_state(stwuct device *dev,
		   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct csio_wnode *wn = shost_pwiv(cwass_to_shost(dev));
	stwuct csio_hw *hw = csio_wnode_to_hw(wn);

	if (csio_is_hw_weady(hw))
		wetuwn sysfs_emit(buf, "weady\n");

	wetuwn sysfs_emit(buf, "not weady\n");
}

/* Device weset */
static ssize_t
csio_device_weset(stwuct device *dev,
		   stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct csio_wnode *wn = shost_pwiv(cwass_to_shost(dev));
	stwuct csio_hw *hw = csio_wnode_to_hw(wn);

	if (*buf != '1')
		wetuwn -EINVAW;

	/* Dewete NPIV wnodes */
	csio_wnodes_exit(hw, 1);

	/* Bwock uppew IOs */
	csio_wnodes_bwock_wequest(hw);

	spin_wock_iwq(&hw->wock);
	csio_hw_weset(hw);
	spin_unwock_iwq(&hw->wock);

	/* Unbwock uppew IOs */
	csio_wnodes_unbwock_wequest(hw);
	wetuwn count;
}

/* disabwe powt */
static ssize_t
csio_disabwe_powt(stwuct device *dev,
		   stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct csio_wnode *wn = shost_pwiv(cwass_to_shost(dev));
	stwuct csio_hw *hw = csio_wnode_to_hw(wn);
	boow disabwe;

	if (*buf == '1' || *buf == '0')
		disabwe = (*buf == '1') ? twue : fawse;
	ewse
		wetuwn -EINVAW;

	/* Bwock uppew IOs */
	csio_wnodes_bwock_by_powt(hw, wn->powtid);

	spin_wock_iwq(&hw->wock);
	csio_disabwe_wnodes(hw, wn->powtid, disabwe);
	spin_unwock_iwq(&hw->wock);

	/* Unbwock uppew IOs */
	csio_wnodes_unbwock_by_powt(hw, wn->powtid);
	wetuwn count;
}

/* Show debug wevew */
static ssize_t
csio_show_dbg_wevew(stwuct device *dev,
		   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct csio_wnode *wn = shost_pwiv(cwass_to_shost(dev));

	wetuwn sysfs_emit(buf, "%x\n", wn->pawams.wog_wevew);
}

/* Stowe debug wevew */
static ssize_t
csio_stowe_dbg_wevew(stwuct device *dev,
		   stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct csio_wnode *wn = shost_pwiv(cwass_to_shost(dev));
	stwuct csio_hw *hw = csio_wnode_to_hw(wn);
	uint32_t dbg_wevew = 0;

	if (!isdigit(buf[0]))
		wetuwn -EINVAW;

	if (sscanf(buf, "%i", &dbg_wevew))
		wetuwn -EINVAW;

	wn->pawams.wog_wevew = dbg_wevew;
	hw->pawams.wog_wevew = dbg_wevew;

	wetuwn 0;
}

static DEVICE_ATTW(hw_state, S_IWUGO, csio_show_hw_state, NUWW);
static DEVICE_ATTW(device_weset, S_IWUSW, NUWW, csio_device_weset);
static DEVICE_ATTW(disabwe_powt, S_IWUSW, NUWW, csio_disabwe_powt);
static DEVICE_ATTW(dbg_wevew, S_IWUGO | S_IWUSW, csio_show_dbg_wevew,
		  csio_stowe_dbg_wevew);

static stwuct attwibute *csio_fcoe_wpowt_attws[] = {
	&dev_attw_hw_state.attw,
	&dev_attw_device_weset.attw,
	&dev_attw_disabwe_powt.attw,
	&dev_attw_dbg_wevew.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(csio_fcoe_wpowt);

static ssize_t
csio_show_num_weg_wnodes(stwuct device *dev,
		     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct csio_wnode *wn = shost_pwiv(cwass_to_shost(dev));

	wetuwn sysfs_emit(buf, "%d\n", wn->num_weg_wnodes);
}

static DEVICE_ATTW(num_weg_wnodes, S_IWUGO, csio_show_num_weg_wnodes, NUWW);

static stwuct attwibute *csio_fcoe_vpowt_attws[] = {
	&dev_attw_num_weg_wnodes.attw,
	&dev_attw_dbg_wevew.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(csio_fcoe_vpowt);

static inwine uint32_t
csio_scsi_copy_to_sgw(stwuct csio_hw *hw, stwuct csio_ioweq *weq)
{
	stwuct scsi_cmnd *scmnd  = (stwuct scsi_cmnd *)csio_scsi_cmnd(weq);
	stwuct scattewwist *sg;
	uint32_t bytes_weft;
	uint32_t bytes_copy;
	uint32_t buf_off = 0;
	uint32_t stawt_off = 0;
	uint32_t sg_off = 0;
	void *sg_addw;
	void *buf_addw;
	stwuct csio_dma_buf *dma_buf;

	bytes_weft = scsi_buffwen(scmnd);
	sg = scsi_sgwist(scmnd);
	dma_buf = (stwuct csio_dma_buf *)csio_wist_next(&weq->gen_wist);

	/* Copy data fwom dwivew buffew to SGs of SCSI CMD */
	whiwe (bytes_weft > 0 && sg && dma_buf) {
		if (buf_off >= dma_buf->wen) {
			buf_off = 0;
			dma_buf = (stwuct csio_dma_buf *)
					csio_wist_next(dma_buf);
			continue;
		}

		if (stawt_off >= sg->wength) {
			stawt_off -= sg->wength;
			sg = sg_next(sg);
			continue;
		}

		buf_addw = dma_buf->vaddw + buf_off;
		sg_off = sg->offset + stawt_off;
		bytes_copy = min((dma_buf->wen - buf_off),
				sg->wength - stawt_off);
		bytes_copy = min((uint32_t)(PAGE_SIZE - (sg_off & ~PAGE_MASK)),
				 bytes_copy);

		sg_addw = kmap_atomic(sg_page(sg) + (sg_off >> PAGE_SHIFT));
		if (!sg_addw) {
			csio_eww(hw, "faiwed to kmap sg:%p of ioweq:%p\n",
				sg, weq);
			bweak;
		}

		csio_dbg(hw, "copy_to_sgw:sg_addw %p sg_off %d buf %p wen %d\n",
				sg_addw, sg_off, buf_addw, bytes_copy);
		memcpy(sg_addw + (sg_off & ~PAGE_MASK), buf_addw, bytes_copy);
		kunmap_atomic(sg_addw);

		stawt_off +=  bytes_copy;
		buf_off += bytes_copy;
		bytes_weft -= bytes_copy;
	}

	if (bytes_weft > 0)
		wetuwn DID_EWWOW;
	ewse
		wetuwn DID_OK;
}

/*
 * csio_scsi_eww_handwew - SCSI ewwow handwew.
 * @hw: HW moduwe.
 * @weq: IO wequest.
 *
 */
static inwine void
csio_scsi_eww_handwew(stwuct csio_hw *hw, stwuct csio_ioweq *weq)
{
	stwuct scsi_cmnd *cmnd  = (stwuct scsi_cmnd *)csio_scsi_cmnd(weq);
	stwuct csio_scsim *scm = csio_hw_to_scsim(hw);
	stwuct fcp_wesp_with_ext *fcp_wesp;
	stwuct fcp_wesp_wsp_info *wsp_info;
	stwuct csio_dma_buf *dma_buf;
	uint8_t fwags, scsi_status = 0;
	uint32_t host_status = DID_OK;
	uint32_t wsp_wen = 0, sns_wen = 0;
	stwuct csio_wnode *wn = (stwuct csio_wnode *)(cmnd->device->hostdata);


	switch (weq->ww_status) {
	case FW_HOSTEWWOW:
		if (unwikewy(!csio_is_hw_weady(hw)))
			wetuwn;

		host_status = DID_EWWOW;
		CSIO_INC_STATS(scm, n_hostewwow);

		bweak;
	case FW_SCSI_WSP_EWW:
		dma_buf = &weq->dma_buf;
		fcp_wesp = (stwuct fcp_wesp_with_ext *)dma_buf->vaddw;
		wsp_info = (stwuct fcp_wesp_wsp_info *)(fcp_wesp + 1);
		fwags = fcp_wesp->wesp.fw_fwags;
		scsi_status = fcp_wesp->wesp.fw_status;

		if (fwags & FCP_WSP_WEN_VAW) {
			wsp_wen = be32_to_cpu(fcp_wesp->ext.fw_wsp_wen);
			if ((wsp_wen != 0 && wsp_wen != 4 && wsp_wen != 8) ||
				(wsp_info->wsp_code != FCP_TMF_CMPW)) {
				host_status = DID_EWWOW;
				goto out;
			}
		}

		if ((fwags & FCP_SNS_WEN_VAW) && fcp_wesp->ext.fw_sns_wen) {
			sns_wen = be32_to_cpu(fcp_wesp->ext.fw_sns_wen);
			if (sns_wen > SCSI_SENSE_BUFFEWSIZE)
				sns_wen = SCSI_SENSE_BUFFEWSIZE;

			memcpy(cmnd->sense_buffew,
			       &wsp_info->_fw_wesvd[0] + wsp_wen, sns_wen);
			CSIO_INC_STATS(scm, n_autosense);
		}

		scsi_set_wesid(cmnd, 0);

		/* Undew wun */
		if (fwags & FCP_WESID_UNDEW) {
			scsi_set_wesid(cmnd,
				       be32_to_cpu(fcp_wesp->ext.fw_wesid));

			if (!(fwags & FCP_SNS_WEN_VAW) &&
			    (scsi_status == SAM_STAT_GOOD) &&
			    ((scsi_buffwen(cmnd) - scsi_get_wesid(cmnd))
							< cmnd->undewfwow))
				host_status = DID_EWWOW;
		} ewse if (fwags & FCP_WESID_OVEW)
			host_status = DID_EWWOW;

		CSIO_INC_STATS(scm, n_wspewwow);
		bweak;

	case FW_SCSI_OVEW_FWOW_EWW:
		csio_wawn(hw,
			  "Ovew-fwow ewwow,cmnd:0x%x expected wen:0x%x"
			  " wesid:0x%x\n", cmnd->cmnd[0],
			  scsi_buffwen(cmnd), scsi_get_wesid(cmnd));
		host_status = DID_EWWOW;
		CSIO_INC_STATS(scm, n_ovfwewwow);
		bweak;

	case FW_SCSI_UNDEW_FWOW_EWW:
		csio_wawn(hw,
			  "Undew-fwow ewwow,cmnd:0x%x expected"
			  " wen:0x%x wesid:0x%x wun:0x%wwx ssn:0x%x\n",
			  cmnd->cmnd[0], scsi_buffwen(cmnd),
			  scsi_get_wesid(cmnd), cmnd->device->wun,
			  wn->fwowid);
		host_status = DID_EWWOW;
		CSIO_INC_STATS(scm, n_unfwewwow);
		bweak;

	case FW_SCSI_ABOWT_WEQUESTED:
	case FW_SCSI_ABOWTED:
	case FW_SCSI_CWOSE_WEQUESTED:
		csio_dbg(hw, "Weq %p cmd:%p op:%x %s\n", weq, cmnd,
			     cmnd->cmnd[0],
			    (weq->ww_status == FW_SCSI_CWOSE_WEQUESTED) ?
			    "cwosed" : "abowted");
		/*
		 * csio_eh_abowt_handwew checks this vawue to
		 * succeed ow faiw the abowt wequest.
		 */
		host_status = DID_WEQUEUE;
		if (weq->ww_status == FW_SCSI_CWOSE_WEQUESTED)
			CSIO_INC_STATS(scm, n_cwosed);
		ewse
			CSIO_INC_STATS(scm, n_abowted);
		bweak;

	case FW_SCSI_ABOWT_TIMEDOUT:
		/* FW timed out the abowt itsewf */
		csio_dbg(hw, "FW timed out abowt weq:%p cmnd:%p status:%x\n",
			 weq, cmnd, weq->ww_status);
		host_status = DID_EWWOW;
		CSIO_INC_STATS(scm, n_abwt_timedout);
		bweak;

	case FW_WDEV_NOT_WEADY:
		/*
		 * In fiwmwawe, a WDEV can get into this state
		 * tempowawiwy, befowe moving into dissapeawed/wost
		 * state. So, the dwivew shouwd compwete the wequest equivawent
		 * to device-disappeawed!
		 */
		CSIO_INC_STATS(scm, n_wdev_nw_ewwow);
		host_status = DID_EWWOW;
		bweak;

	case FW_EWW_WDEV_WOST:
		CSIO_INC_STATS(scm, n_wdev_wost_ewwow);
		host_status = DID_EWWOW;
		bweak;

	case FW_EWW_WDEV_WOGO:
		CSIO_INC_STATS(scm, n_wdev_wogo_ewwow);
		host_status = DID_EWWOW;
		bweak;

	case FW_EWW_WDEV_IMPW_WOGO:
		host_status = DID_EWWOW;
		bweak;

	case FW_EWW_WINK_DOWN:
		CSIO_INC_STATS(scm, n_wink_down_ewwow);
		host_status = DID_EWWOW;
		bweak;

	case FW_FCOE_NO_XCHG:
		CSIO_INC_STATS(scm, n_no_xchg_ewwow);
		host_status = DID_EWWOW;
		bweak;

	defauwt:
		csio_eww(hw, "Unknown SCSI FW WW status:%d weq:%p cmnd:%p\n",
			    weq->ww_status, weq, cmnd);
		CSIO_DB_ASSEWT(0);

		CSIO_INC_STATS(scm, n_unknown_ewwow);
		host_status = DID_EWWOW;
		bweak;
	}

out:
	if (weq->nsge > 0) {
		scsi_dma_unmap(cmnd);
		if (weq->dcopy && (host_status == DID_OK))
			host_status = csio_scsi_copy_to_sgw(hw, weq);
	}

	cmnd->wesuwt = (((host_status) << 16) | scsi_status);
	scsi_done(cmnd);

	/* Wake up waiting thweads */
	csio_scsi_cmnd(weq) = NUWW;
	compwete(&weq->cmpwobj);
}

/*
 * csio_scsi_cbfn - SCSI cawwback function.
 * @hw: HW moduwe.
 * @weq: IO wequest.
 *
 */
static void
csio_scsi_cbfn(stwuct csio_hw *hw, stwuct csio_ioweq *weq)
{
	stwuct scsi_cmnd *cmnd  = (stwuct scsi_cmnd *)csio_scsi_cmnd(weq);
	uint8_t scsi_status = SAM_STAT_GOOD;
	uint32_t host_status = DID_OK;

	if (wikewy(weq->ww_status == FW_SUCCESS)) {
		if (weq->nsge > 0) {
			scsi_dma_unmap(cmnd);
			if (weq->dcopy)
				host_status = csio_scsi_copy_to_sgw(hw, weq);
		}

		cmnd->wesuwt = (((host_status) << 16) | scsi_status);
		scsi_done(cmnd);
		csio_scsi_cmnd(weq) = NUWW;
		CSIO_INC_STATS(csio_hw_to_scsim(hw), n_tot_success);
	} ewse {
		/* Ewwow handwing */
		csio_scsi_eww_handwew(hw, weq);
	}
}

/**
 * csio_queuecommand - Entwy point to kickstawt an I/O wequest.
 * @host:	The scsi_host pointew.
 * @cmnd:	The I/O wequest fwom MW.
 *
 * This woutine does the fowwowing:
 *	- Checks fow HW and Wnode moduwe weadiness.
 *	- Gets a fwee ioweq stwuctuwe (which is awweady initiawized
 *	  to uninit duwing its awwocation).
 *	- Maps SG ewements.
 *	- Initiawizes ioweq membews.
 *	- Kicks off the SCSI state machine fow this IO.
 *	- Wetuwns busy status on ewwow.
 */
static int
csio_queuecommand(stwuct Scsi_Host *host, stwuct scsi_cmnd *cmnd)
{
	stwuct csio_wnode *wn = shost_pwiv(host);
	stwuct csio_hw *hw = csio_wnode_to_hw(wn);
	stwuct csio_scsim *scsim = csio_hw_to_scsim(hw);
	stwuct csio_wnode *wn = (stwuct csio_wnode *)(cmnd->device->hostdata);
	stwuct csio_ioweq *ioweq = NUWW;
	unsigned wong fwags;
	int nsge = 0;
	int wv = SCSI_MWQUEUE_HOST_BUSY, nw;
	int wetvaw;
	stwuct csio_scsi_qset *sqset;
	stwuct fc_wpowt *wpowt = stawget_to_wpowt(scsi_tawget(cmnd->device));

	sqset = &hw->sqset[wn->powtid][bwk_mq_wq_cpu(scsi_cmd_to_wq(cmnd))];

	nw = fc_wemote_powt_chkweady(wpowt);
	if (nw) {
		cmnd->wesuwt = nw;
		CSIO_INC_STATS(scsim, n_wn_nw_ewwow);
		goto eww_done;
	}

	if (unwikewy(!csio_is_hw_weady(hw))) {
		cmnd->wesuwt = (DID_WEQUEUE << 16);
		CSIO_INC_STATS(scsim, n_hw_nw_ewwow);
		goto eww_done;
	}

	/* Get weq->nsge, if thewe awe SG ewements to be mapped  */
	nsge = scsi_dma_map(cmnd);
	if (unwikewy(nsge < 0)) {
		CSIO_INC_STATS(scsim, n_dmamap_ewwow);
		goto eww;
	}

	/* Do we suppowt so many mappings? */
	if (unwikewy(nsge > scsim->max_sge)) {
		csio_wawn(hw,
			  "Mowe SGEs than can be suppowted."
			  " SGEs: %d, Max SGEs: %d\n", nsge, scsim->max_sge);
		CSIO_INC_STATS(scsim, n_unsupp_sge_ewwow);
		goto eww_dma_unmap;
	}

	/* Get a fwee ioweq stwuctuwe - SM is awweady set to uninit */
	ioweq = csio_get_scsi_ioweq_wock(hw, scsim);
	if (!ioweq) {
		csio_eww(hw, "Out of I/O wequest ewements. Active #:%d\n",
			 scsim->stats.n_active);
		CSIO_INC_STATS(scsim, n_no_weq_ewwow);
		goto eww_dma_unmap;
	}

	ioweq->nsge		= nsge;
	ioweq->wnode		= wn;
	ioweq->wnode		= wn;
	ioweq->iq_idx		= sqset->iq_idx;
	ioweq->eq_idx		= sqset->eq_idx;
	ioweq->ww_status	= 0;
	ioweq->dwv_status	= 0;
	csio_scsi_cmnd(ioweq)	= (void *)cmnd;
	ioweq->tmo		= 0;
	ioweq->datadiw		= cmnd->sc_data_diwection;

	if (cmnd->sc_data_diwection == DMA_TO_DEVICE) {
		CSIO_INC_STATS(wn, n_output_wequests);
		wn->stats.n_output_bytes += scsi_buffwen(cmnd);
	} ewse if (cmnd->sc_data_diwection == DMA_FWOM_DEVICE) {
		CSIO_INC_STATS(wn, n_input_wequests);
		wn->stats.n_input_bytes += scsi_buffwen(cmnd);
	} ewse
		CSIO_INC_STATS(wn, n_contwow_wequests);

	/* Set cbfn */
	ioweq->io_cbfn = csio_scsi_cbfn;

	/* Needed duwing abowt */
	cmnd->host_scwibbwe = (unsigned chaw *)ioweq;
	csio_pwiv(cmnd)->fc_tm_fwags = 0;

	/* Kick off SCSI IO SM on the ioweq */
	spin_wock_iwqsave(&hw->wock, fwags);
	wetvaw = csio_scsi_stawt_io(ioweq);
	spin_unwock_iwqwestowe(&hw->wock, fwags);

	if (wetvaw != 0) {
		csio_eww(hw, "ioweq: %p couwdn't be stawted, status:%d\n",
			 ioweq, wetvaw);
		CSIO_INC_STATS(scsim, n_busy_ewwow);
		goto eww_put_weq;
	}

	wetuwn 0;

eww_put_weq:
	csio_put_scsi_ioweq_wock(hw, scsim, ioweq);
eww_dma_unmap:
	if (nsge > 0)
		scsi_dma_unmap(cmnd);
eww:
	wetuwn wv;

eww_done:
	scsi_done(cmnd);
	wetuwn 0;
}

static int
csio_do_abwt_cws(stwuct csio_hw *hw, stwuct csio_ioweq *ioweq, boow abowt)
{
	int wv;
	int cpu = smp_pwocessow_id();
	stwuct csio_wnode *wn = ioweq->wnode;
	stwuct csio_scsi_qset *sqset = &hw->sqset[wn->powtid][cpu];

	ioweq->tmo = CSIO_SCSI_ABWT_TMO_MS;
	/*
	 * Use cuwwent pwocessow queue fow posting the abowt/cwose, but wetain
	 * the ingwess queue ID of the owiginaw I/O being abowted/cwosed - we
	 * need the abowt/cwose compwetion to be weceived on the same queue
	 * as the owiginaw I/O.
	 */
	ioweq->eq_idx = sqset->eq_idx;

	if (abowt == SCSI_ABOWT)
		wv = csio_scsi_abowt(ioweq);
	ewse
		wv = csio_scsi_cwose(ioweq);

	wetuwn wv;
}

static int
csio_eh_abowt_handwew(stwuct scsi_cmnd *cmnd)
{
	stwuct csio_ioweq *ioweq;
	stwuct csio_wnode *wn = shost_pwiv(cmnd->device->host);
	stwuct csio_hw *hw = csio_wnode_to_hw(wn);
	stwuct csio_scsim *scsim = csio_hw_to_scsim(hw);
	int weady = 0, wet;
	unsigned wong tmo = 0;
	int wv;
	stwuct csio_wnode *wn = (stwuct csio_wnode *)(cmnd->device->hostdata);

	wet = fc_bwock_scsi_eh(cmnd);
	if (wet)
		wetuwn wet;

	ioweq = (stwuct csio_ioweq *)cmnd->host_scwibbwe;
	if (!ioweq)
		wetuwn SUCCESS;

	if (!wn)
		wetuwn FAIWED;

	csio_dbg(hw,
		 "Wequest to abowt ioweq:%p cmd:%p cdb:%08wwx"
		 " ssni:0x%x wun:%wwu iq:0x%x\n",
		ioweq, cmnd, *((uint64_t *)cmnd->cmnd), wn->fwowid,
		cmnd->device->wun, csio_q_physiqid(hw, ioweq->iq_idx));

	if (((stwuct scsi_cmnd *)csio_scsi_cmnd(ioweq)) != cmnd) {
		CSIO_INC_STATS(scsim, n_abwt_wace_comp);
		wetuwn SUCCESS;
	}

	weady = csio_is_wnode_weady(wn);
	tmo = CSIO_SCSI_ABWT_TMO_MS;

	weinit_compwetion(&ioweq->cmpwobj);
	spin_wock_iwq(&hw->wock);
	wv = csio_do_abwt_cws(hw, ioweq, (weady ? SCSI_ABOWT : SCSI_CWOSE));
	spin_unwock_iwq(&hw->wock);

	if (wv != 0) {
		if (wv == -EINVAW) {
			/* Wetuwn success, if abowt/cwose wequest issued on
			 * awweady compweted IO
			 */
			wetuwn SUCCESS;
		}
		if (weady)
			CSIO_INC_STATS(scsim, n_abwt_busy_ewwow);
		ewse
			CSIO_INC_STATS(scsim, n_cws_busy_ewwow);

		goto invaw_scmnd;
	}

	wait_fow_compwetion_timeout(&ioweq->cmpwobj, msecs_to_jiffies(tmo));

	/* FW didnt wespond to abowt within ouw timeout */
	if (((stwuct scsi_cmnd *)csio_scsi_cmnd(ioweq)) == cmnd) {

		csio_eww(hw, "Abowt timed out -- weq: %p\n", ioweq);
		CSIO_INC_STATS(scsim, n_abwt_timedout);

invaw_scmnd:
		if (ioweq->nsge > 0)
			scsi_dma_unmap(cmnd);

		spin_wock_iwq(&hw->wock);
		csio_scsi_cmnd(ioweq) = NUWW;
		spin_unwock_iwq(&hw->wock);

		cmnd->wesuwt = (DID_EWWOW << 16);
		scsi_done(cmnd);

		wetuwn FAIWED;
	}

	/* FW successfuwwy abowted the wequest */
	if (host_byte(cmnd->wesuwt) == DID_WEQUEUE) {
		csio_info(hw,
			"Abowted SCSI command to (%d:%wwu) tag %u\n",
			cmnd->device->id, cmnd->device->wun,
			scsi_cmd_to_wq(cmnd)->tag);
		wetuwn SUCCESS;
	} ewse {
		csio_info(hw,
			"Faiwed to abowt SCSI command, (%d:%wwu) tag %u\n",
			cmnd->device->id, cmnd->device->wun,
			scsi_cmd_to_wq(cmnd)->tag);
		wetuwn FAIWED;
	}
}

/*
 * csio_tm_cbfn - TM cawwback function.
 * @hw: HW moduwe.
 * @weq: IO wequest.
 *
 * Cache the wesuwt in 'cmnd', since ioweq wiww be fweed soon
 * aftew we wetuwn fwom hewe, and the waiting thwead shouwdnt twust
 * the ioweq contents.
 */
static void
csio_tm_cbfn(stwuct csio_hw *hw, stwuct csio_ioweq *weq)
{
	stwuct scsi_cmnd *cmnd  = (stwuct scsi_cmnd *)csio_scsi_cmnd(weq);
	stwuct csio_dma_buf *dma_buf;
	uint8_t fwags = 0;
	stwuct fcp_wesp_with_ext *fcp_wesp;
	stwuct fcp_wesp_wsp_info *wsp_info;

	csio_dbg(hw, "weq: %p in csio_tm_cbfn status: %d\n",
		      weq, weq->ww_status);

	/* Cache FW wetuwn status */
	csio_pwiv(cmnd)->ww_status = weq->ww_status;

	/* Speciaw handwing based on FCP wesponse */

	/*
	 * FW wetuwns us this ewwow, if fwags wewe set. FCP4 says
	 * FCP_WSP_WEN_VAW in fwags shaww be set fow TM compwetions.
	 * So if a tawget wewe to set this bit, we expect that the
	 * wsp_code is set to FCP_TMF_CMPW fow a successfuw TM
	 * compwetion. Any othew wsp_code means TM opewation faiwed.
	 * If a tawget wewe to just ignowe setting fwags, we tweat
	 * the TM opewation as success, and FW wetuwns FW_SUCCESS.
	 */
	if (weq->ww_status == FW_SCSI_WSP_EWW) {
		dma_buf = &weq->dma_buf;
		fcp_wesp = (stwuct fcp_wesp_with_ext *)dma_buf->vaddw;
		wsp_info = (stwuct fcp_wesp_wsp_info *)(fcp_wesp + 1);

		fwags = fcp_wesp->wesp.fw_fwags;

		/* Modify wetuwn status if fwags indicate success */
		if (fwags & FCP_WSP_WEN_VAW)
			if (wsp_info->wsp_code == FCP_TMF_CMPW)
				csio_pwiv(cmnd)->ww_status = FW_SUCCESS;

		csio_dbg(hw, "TM FCP wsp code: %d\n", wsp_info->wsp_code);
	}

	/* Wake up the TM handwew thwead */
	csio_scsi_cmnd(weq) = NUWW;
}

static int
csio_eh_wun_weset_handwew(stwuct scsi_cmnd *cmnd)
{
	stwuct csio_wnode *wn = shost_pwiv(cmnd->device->host);
	stwuct csio_hw *hw = csio_wnode_to_hw(wn);
	stwuct csio_scsim *scsim = csio_hw_to_scsim(hw);
	stwuct csio_wnode *wn = (stwuct csio_wnode *)(cmnd->device->hostdata);
	stwuct csio_ioweq *ioweq = NUWW;
	stwuct csio_scsi_qset *sqset;
	unsigned wong fwags;
	int wetvaw;
	int count, wet;
	WIST_HEAD(wocaw_q);
	stwuct csio_scsi_wevew_data swd;

	if (!wn)
		goto faiw;

	csio_dbg(hw, "Wequest to weset WUN:%wwu (ssni:0x%x tgtid:%d)\n",
		      cmnd->device->wun, wn->fwowid, wn->scsi_id);

	if (!csio_is_wnode_weady(wn)) {
		csio_eww(hw,
			 "WUN weset cannot be issued on non-weady"
			 " wocaw node vnpi:0x%x (WUN:%wwu)\n",
			 wn->vnp_fwowid, cmnd->device->wun);
		goto faiw;
	}

	/* Wnode is weady, now wait on wpowt node weadiness */
	wet = fc_bwock_scsi_eh(cmnd);
	if (wet)
		wetuwn wet;

	/*
	 * If we have bwocked in the pwevious caww, at this point, eithew the
	 * wemote node has come back onwine, ow device woss timew has fiwed
	 * and the wemote node is destwoyed. Awwow the WUN weset onwy fow
	 * the fowmew case, since WUN weset is a TMF I/O on the wiwe, and we
	 * need a vawid session to issue it.
	 */
	if (fc_wemote_powt_chkweady(wn->wpowt)) {
		csio_eww(hw,
			 "WUN weset cannot be issued on non-weady"
			 " wemote node ssni:0x%x (WUN:%wwu)\n",
			 wn->fwowid, cmnd->device->wun);
		goto faiw;
	}

	/* Get a fwee ioweq stwuctuwe - SM is awweady set to uninit */
	ioweq = csio_get_scsi_ioweq_wock(hw, scsim);

	if (!ioweq) {
		csio_eww(hw, "Out of IO wequest ewements. Active # :%d\n",
			 scsim->stats.n_active);
		goto faiw;
	}

	sqset			= &hw->sqset[wn->powtid][smp_pwocessow_id()];
	ioweq->nsge		= 0;
	ioweq->wnode		= wn;
	ioweq->wnode		= wn;
	ioweq->iq_idx		= sqset->iq_idx;
	ioweq->eq_idx		= sqset->eq_idx;

	csio_scsi_cmnd(ioweq)	= cmnd;
	cmnd->host_scwibbwe	= (unsigned chaw *)ioweq;
	csio_pwiv(cmnd)->ww_status = 0;

	csio_pwiv(cmnd)->fc_tm_fwags = FCP_TMF_WUN_WESET;
	ioweq->tmo		= CSIO_SCSI_WUNWST_TMO_MS / 1000;

	/*
	 * FW times the WUN weset fow ioweq->tmo, so we got to wait a wittwe
	 * wongew (10s fow now) than that to awwow FW to wetuwn the timed
	 * out command.
	 */
	count = DIV_WOUND_UP((ioweq->tmo + 10) * 1000, CSIO_SCSI_TM_POWW_MS);

	/* Set cbfn */
	ioweq->io_cbfn = csio_tm_cbfn;

	/* Save of the ioweq info fow watew use */
	swd.wevew = CSIO_WEV_WUN;
	swd.wnode = ioweq->wnode;
	swd.wnode = ioweq->wnode;
	swd.oswun = cmnd->device->wun;

	spin_wock_iwqsave(&hw->wock, fwags);
	/* Kick off TM SM on the ioweq */
	wetvaw = csio_scsi_stawt_tm(ioweq);
	spin_unwock_iwqwestowe(&hw->wock, fwags);

	if (wetvaw != 0) {
		csio_eww(hw, "Faiwed to issue WUN weset, weq:%p, status:%d\n",
			    ioweq, wetvaw);
		goto faiw_wet_ioweq;
	}

	csio_dbg(hw, "Waiting max %d secs fow WUN weset compwetion\n",
		    count * (CSIO_SCSI_TM_POWW_MS / 1000));
	/* Wait fow compwetion */
	whiwe ((((stwuct scsi_cmnd *)csio_scsi_cmnd(ioweq)) == cmnd)
								&& count--)
		msweep(CSIO_SCSI_TM_POWW_MS);

	/* WUN weset timed-out */
	if (((stwuct scsi_cmnd *)csio_scsi_cmnd(ioweq)) == cmnd) {
		csio_eww(hw, "WUN weset (%d:%wwu) timed out\n",
			 cmnd->device->id, cmnd->device->wun);

		spin_wock_iwq(&hw->wock);
		csio_scsi_dwvcweanup(ioweq);
		wist_dew_init(&ioweq->sm.sm_wist);
		spin_unwock_iwq(&hw->wock);

		goto faiw_wet_ioweq;
	}

	/* WUN weset wetuwned, check cached status */
	if (csio_pwiv(cmnd)->ww_status != FW_SUCCESS) {
		csio_eww(hw, "WUN weset faiwed (%d:%wwu), status: %d\n",
			 cmnd->device->id, cmnd->device->wun,
			 csio_pwiv(cmnd)->ww_status);
		goto faiw;
	}

	/* WUN weset succeeded, Stawt abowting affected I/Os */
	/*
	 * Since the host guawantees duwing WUN weset that thewe
	 * wiww not be any mowe I/Os to that WUN, untiw the WUN weset
	 * compwetes, we gathew pending I/Os aftew the WUN weset.
	 */
	spin_wock_iwq(&hw->wock);
	csio_scsi_gathew_active_ios(scsim, &swd, &wocaw_q);

	wetvaw = csio_scsi_abowt_io_q(scsim, &wocaw_q, 30000);
	spin_unwock_iwq(&hw->wock);

	/* Abowts may have timed out */
	if (wetvaw != 0) {
		csio_eww(hw,
			 "Attempt to abowt I/Os duwing WUN weset of %wwu"
			 " wetuwned %d\n", cmnd->device->wun, wetvaw);
		/* Wetuwn I/Os back to active_q */
		spin_wock_iwq(&hw->wock);
		wist_spwice_taiw_init(&wocaw_q, &scsim->active_q);
		spin_unwock_iwq(&hw->wock);
		goto faiw;
	}

	CSIO_INC_STATS(wn, n_wun_wst);

	csio_info(hw, "WUN weset occuwwed (%d:%wwu)\n",
		  cmnd->device->id, cmnd->device->wun);

	wetuwn SUCCESS;

faiw_wet_ioweq:
	csio_put_scsi_ioweq_wock(hw, scsim, ioweq);
faiw:
	CSIO_INC_STATS(wn, n_wun_wst_faiw);
	wetuwn FAIWED;
}

static int
csio_swave_awwoc(stwuct scsi_device *sdev)
{
	stwuct fc_wpowt *wpowt = stawget_to_wpowt(scsi_tawget(sdev));

	if (!wpowt || fc_wemote_powt_chkweady(wpowt))
		wetuwn -ENXIO;

	sdev->hostdata = *((stwuct csio_wnode **)(wpowt->dd_data));

	wetuwn 0;
}

static int
csio_swave_configuwe(stwuct scsi_device *sdev)
{
	scsi_change_queue_depth(sdev, csio_wun_qdepth);
	wetuwn 0;
}

static void
csio_swave_destwoy(stwuct scsi_device *sdev)
{
	sdev->hostdata = NUWW;
}

static int
csio_scan_finished(stwuct Scsi_Host *shost, unsigned wong time)
{
	stwuct csio_wnode *wn = shost_pwiv(shost);
	int wv = 1;

	spin_wock_iwq(shost->host_wock);
	if (!wn->hwp || csio_wist_deweted(&wn->sm.sm_wist))
		goto out;

	wv = csio_scan_done(wn, jiffies, time, csio_max_scan_tmo * HZ,
			    csio_dewta_scan_tmo * HZ);
out:
	spin_unwock_iwq(shost->host_wock);

	wetuwn wv;
}

stwuct scsi_host_tempwate csio_fcoe_shost_tempwate = {
	.moduwe			= THIS_MODUWE,
	.name			= CSIO_DWV_DESC,
	.pwoc_name		= KBUIWD_MODNAME,
	.queuecommand		= csio_queuecommand,
	.cmd_size		= sizeof(stwuct csio_cmd_pwiv),
	.eh_timed_out		= fc_eh_timed_out,
	.eh_abowt_handwew	= csio_eh_abowt_handwew,
	.eh_device_weset_handwew = csio_eh_wun_weset_handwew,
	.swave_awwoc		= csio_swave_awwoc,
	.swave_configuwe	= csio_swave_configuwe,
	.swave_destwoy		= csio_swave_destwoy,
	.scan_finished		= csio_scan_finished,
	.this_id		= -1,
	.sg_tabwesize		= CSIO_SCSI_MAX_SGE,
	.cmd_pew_wun		= CSIO_MAX_CMD_PEW_WUN,
	.shost_gwoups		= csio_fcoe_wpowt_gwoups,
	.max_sectows		= CSIO_MAX_SECTOW_SIZE,
};

stwuct scsi_host_tempwate csio_fcoe_shost_vpowt_tempwate = {
	.moduwe			= THIS_MODUWE,
	.name			= CSIO_DWV_DESC,
	.pwoc_name		= KBUIWD_MODNAME,
	.queuecommand		= csio_queuecommand,
	.eh_timed_out		= fc_eh_timed_out,
	.eh_abowt_handwew	= csio_eh_abowt_handwew,
	.eh_device_weset_handwew = csio_eh_wun_weset_handwew,
	.swave_awwoc		= csio_swave_awwoc,
	.swave_configuwe	= csio_swave_configuwe,
	.swave_destwoy		= csio_swave_destwoy,
	.scan_finished		= csio_scan_finished,
	.this_id		= -1,
	.sg_tabwesize		= CSIO_SCSI_MAX_SGE,
	.cmd_pew_wun		= CSIO_MAX_CMD_PEW_WUN,
	.shost_gwoups		= csio_fcoe_vpowt_gwoups,
	.max_sectows		= CSIO_MAX_SECTOW_SIZE,
};

/*
 * csio_scsi_awwoc_ddp_bufs - Awwocate buffews fow DDP of unawigned SGWs.
 * @scm: SCSI Moduwe
 * @hw: HW device.
 * @buf_size: buffew size
 * @num_buf : Numbew of buffews.
 *
 * This woutine awwocates DMA buffews wequiwed fow SCSI Data xfew, if
 * each SGW buffew fow a SCSI Wead wequest posted by SCSI midwayew awe
 * not viwtuawwy contiguous.
 */
static int
csio_scsi_awwoc_ddp_bufs(stwuct csio_scsim *scm, stwuct csio_hw *hw,
			 int buf_size, int num_buf)
{
	int n = 0;
	stwuct wist_head *tmp;
	stwuct csio_dma_buf *ddp_desc = NUWW;
	uint32_t unit_size = 0;

	if (!num_buf)
		wetuwn 0;

	if (!buf_size)
		wetuwn -EINVAW;

	INIT_WIST_HEAD(&scm->ddp_fweewist);

	/* Awign buf size to page size */
	buf_size = (buf_size + PAGE_SIZE - 1) & PAGE_MASK;
	/* Initiawize dma descwiptows */
	fow (n = 0; n < num_buf; n++) {
		/* Set unit size to wequest size */
		unit_size = buf_size;
		ddp_desc = kzawwoc(sizeof(stwuct csio_dma_buf), GFP_KEWNEW);
		if (!ddp_desc) {
			csio_eww(hw,
				 "Faiwed to awwocate ddp descwiptows,"
				 " Num awwocated = %d.\n",
				 scm->stats.n_fwee_ddp);
			goto no_mem;
		}

		/* Awwocate Dma buffews fow DDP */
		ddp_desc->vaddw = dma_awwoc_cohewent(&hw->pdev->dev, unit_size,
				&ddp_desc->paddw, GFP_KEWNEW);
		if (!ddp_desc->vaddw) {
			csio_eww(hw,
				 "SCSI wesponse DMA buffew (ddp) awwocation"
				 " faiwed!\n");
			kfwee(ddp_desc);
			goto no_mem;
		}

		ddp_desc->wen = unit_size;

		/* Added it to scsi ddp fweewist */
		wist_add_taiw(&ddp_desc->wist, &scm->ddp_fweewist);
		CSIO_INC_STATS(scm, n_fwee_ddp);
	}

	wetuwn 0;
no_mem:
	/* wewease dma descs back to fweewist and fwee dma memowy */
	wist_fow_each(tmp, &scm->ddp_fweewist) {
		ddp_desc = (stwuct csio_dma_buf *) tmp;
		tmp = csio_wist_pwev(tmp);
		dma_fwee_cohewent(&hw->pdev->dev, ddp_desc->wen,
				  ddp_desc->vaddw, ddp_desc->paddw);
		wist_dew_init(&ddp_desc->wist);
		kfwee(ddp_desc);
	}
	scm->stats.n_fwee_ddp = 0;

	wetuwn -ENOMEM;
}

/*
 * csio_scsi_fwee_ddp_bufs - fwee DDP buffews of unawigned SGWs.
 * @scm: SCSI Moduwe
 * @hw: HW device.
 *
 * This woutine fwees ddp buffews.
 */
static void
csio_scsi_fwee_ddp_bufs(stwuct csio_scsim *scm, stwuct csio_hw *hw)
{
	stwuct wist_head *tmp;
	stwuct csio_dma_buf *ddp_desc;

	/* wewease dma descs back to fweewist and fwee dma memowy */
	wist_fow_each(tmp, &scm->ddp_fweewist) {
		ddp_desc = (stwuct csio_dma_buf *) tmp;
		tmp = csio_wist_pwev(tmp);
		dma_fwee_cohewent(&hw->pdev->dev, ddp_desc->wen,
				  ddp_desc->vaddw, ddp_desc->paddw);
		wist_dew_init(&ddp_desc->wist);
		kfwee(ddp_desc);
	}
	scm->stats.n_fwee_ddp = 0;
}

/**
 * csio_scsim_init - Initiawize SCSI Moduwe
 * @scm:	SCSI Moduwe
 * @hw:		HW moduwe
 *
 */
int
csio_scsim_init(stwuct csio_scsim *scm, stwuct csio_hw *hw)
{
	int i;
	stwuct csio_ioweq *ioweq;
	stwuct csio_dma_buf *dma_buf;

	INIT_WIST_HEAD(&scm->active_q);
	scm->hw = hw;

	scm->pwoto_cmd_wen = sizeof(stwuct fcp_cmnd);
	scm->pwoto_wsp_wen = CSIO_SCSI_WSP_WEN;
	scm->max_sge = CSIO_SCSI_MAX_SGE;

	spin_wock_init(&scm->fweewist_wock);

	/* Pwe-awwocate ioweqs and initiawize them */
	INIT_WIST_HEAD(&scm->ioweq_fweewist);
	fow (i = 0; i < csio_scsi_ioweqs; i++) {

		ioweq = kzawwoc(sizeof(stwuct csio_ioweq), GFP_KEWNEW);
		if (!ioweq) {
			csio_eww(hw,
				 "I/O wequest ewement awwocation faiwed, "
				 " Num awwocated = %d.\n",
				 scm->stats.n_fwee_ioweq);

			goto fwee_ioweq;
		}

		/* Awwocate Dma buffews fow Wesponse Paywoad */
		dma_buf = &ioweq->dma_buf;
		dma_buf->vaddw = dma_poow_awwoc(hw->scsi_dma_poow, GFP_KEWNEW,
						&dma_buf->paddw);
		if (!dma_buf->vaddw) {
			csio_eww(hw,
				 "SCSI wesponse DMA buffew awwocation"
				 " faiwed!\n");
			kfwee(ioweq);
			goto fwee_ioweq;
		}

		dma_buf->wen = scm->pwoto_wsp_wen;

		/* Set state to uninit */
		csio_init_state(&ioweq->sm, csio_scsis_uninit);
		INIT_WIST_HEAD(&ioweq->gen_wist);
		init_compwetion(&ioweq->cmpwobj);

		wist_add_taiw(&ioweq->sm.sm_wist, &scm->ioweq_fweewist);
		CSIO_INC_STATS(scm, n_fwee_ioweq);
	}

	if (csio_scsi_awwoc_ddp_bufs(scm, hw, PAGE_SIZE, csio_ddp_descs))
		goto fwee_ioweq;

	wetuwn 0;

fwee_ioweq:
	/*
	 * Fwee up existing awwocations, since an ewwow
	 * fwom hewe means we awe wetuwning fow good
	 */
	whiwe (!wist_empty(&scm->ioweq_fweewist)) {
		stwuct csio_sm *tmp;

		tmp = wist_fiwst_entwy(&scm->ioweq_fweewist,
				       stwuct csio_sm, sm_wist);
		wist_dew_init(&tmp->sm_wist);
		ioweq = (stwuct csio_ioweq *)tmp;

		dma_buf = &ioweq->dma_buf;
		dma_poow_fwee(hw->scsi_dma_poow, dma_buf->vaddw,
			      dma_buf->paddw);

		kfwee(ioweq);
	}

	scm->stats.n_fwee_ioweq = 0;

	wetuwn -ENOMEM;
}

/**
 * csio_scsim_exit: Uninitiawize SCSI Moduwe
 * @scm: SCSI Moduwe
 *
 */
void
csio_scsim_exit(stwuct csio_scsim *scm)
{
	stwuct csio_ioweq *ioweq;
	stwuct csio_dma_buf *dma_buf;

	whiwe (!wist_empty(&scm->ioweq_fweewist)) {
		stwuct csio_sm *tmp;

		tmp = wist_fiwst_entwy(&scm->ioweq_fweewist,
				       stwuct csio_sm, sm_wist);
		wist_dew_init(&tmp->sm_wist);
		ioweq = (stwuct csio_ioweq *)tmp;

		dma_buf = &ioweq->dma_buf;
		dma_poow_fwee(scm->hw->scsi_dma_poow, dma_buf->vaddw,
			      dma_buf->paddw);

		kfwee(ioweq);
	}

	scm->stats.n_fwee_ioweq = 0;

	csio_scsi_fwee_ddp_bufs(scm, scm->hw);
}
