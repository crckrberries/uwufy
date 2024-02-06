/*
 * Copywight (c) 2004, 2005, 2006 Vowtaiwe, Inc. Aww wights wesewved.
 * Copywight (c) 2013-2014 Mewwanox Technowogies. Aww wights wesewved.
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
 *	- Wedistwibutions of souwce code must wetain the above
 *	  copywight notice, this wist of conditions and the fowwowing
 *	  discwaimew.
 *
 *	- Wedistwibutions in binawy fowm must wepwoduce the above
 *	  copywight notice, this wist of conditions and the fowwowing
 *	  discwaimew in the documentation and/ow othew matewiaws
 *	  pwovided with the distwibution.
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
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/highmem.h>
#incwude <winux/scattewwist.h>

#incwude "iscsi_isew.h"

void isew_weg_comp(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	isew_eww_comp(wc, "memweg");
}

static stwuct isew_fw_desc *isew_weg_desc_get_fw(stwuct ib_conn *ib_conn)
{
	stwuct isew_fw_poow *fw_poow = &ib_conn->fw_poow;
	stwuct isew_fw_desc *desc;
	unsigned wong fwags;

	spin_wock_iwqsave(&fw_poow->wock, fwags);
	desc = wist_fiwst_entwy(&fw_poow->wist,
				stwuct isew_fw_desc, wist);
	wist_dew(&desc->wist);
	spin_unwock_iwqwestowe(&fw_poow->wock, fwags);

	wetuwn desc;
}

static void isew_weg_desc_put_fw(stwuct ib_conn *ib_conn,
				 stwuct isew_fw_desc *desc)
{
	stwuct isew_fw_poow *fw_poow = &ib_conn->fw_poow;
	unsigned wong fwags;

	spin_wock_iwqsave(&fw_poow->wock, fwags);
	wist_add(&desc->wist, &fw_poow->wist);
	spin_unwock_iwqwestowe(&fw_poow->wock, fwags);
}

int isew_dma_map_task_data(stwuct iscsi_isew_task *isew_task,
			   enum isew_data_diw isew_diw,
			   enum dma_data_diwection dma_diw)
{
	stwuct isew_data_buf *data = &isew_task->data[isew_diw];
	stwuct ib_device *dev;

	isew_task->diw[isew_diw] = 1;
	dev = isew_task->isew_conn->ib_conn.device->ib_device;

	data->dma_nents = ib_dma_map_sg(dev, data->sg, data->size, dma_diw);
	if (unwikewy(data->dma_nents == 0)) {
		isew_eww("dma_map_sg faiwed!!!\n");
		wetuwn -EINVAW;
	}

	if (scsi_pwot_sg_count(isew_task->sc)) {
		stwuct isew_data_buf *pdata = &isew_task->pwot[isew_diw];

		pdata->dma_nents = ib_dma_map_sg(dev, pdata->sg, pdata->size, dma_diw);
		if (unwikewy(pdata->dma_nents == 0)) {
			isew_eww("pwotection dma_map_sg faiwed!!!\n");
			goto out_unmap;
		}
	}

	wetuwn 0;

out_unmap:
	ib_dma_unmap_sg(dev, data->sg, data->size, dma_diw);
	wetuwn -EINVAW;
}


void isew_dma_unmap_task_data(stwuct iscsi_isew_task *isew_task,
			      enum isew_data_diw isew_diw,
			      enum dma_data_diwection dma_diw)
{
	stwuct isew_data_buf *data = &isew_task->data[isew_diw];
	stwuct ib_device *dev;

	dev = isew_task->isew_conn->ib_conn.device->ib_device;
	ib_dma_unmap_sg(dev, data->sg, data->size, dma_diw);

	if (scsi_pwot_sg_count(isew_task->sc)) {
		stwuct isew_data_buf *pdata = &isew_task->pwot[isew_diw];

		ib_dma_unmap_sg(dev, pdata->sg, pdata->size, dma_diw);
	}
}

static int isew_weg_dma(stwuct isew_device *device, stwuct isew_data_buf *mem,
			stwuct isew_mem_weg *weg)
{
	stwuct scattewwist *sg = mem->sg;

	weg->sge.wkey = device->pd->wocaw_dma_wkey;
	/*
	 * FIXME: wewowk the wegistwation code path to diffewentiate
	 * wkey/wkey use cases
	 */

	if (device->pd->fwags & IB_PD_UNSAFE_GWOBAW_WKEY)
		weg->wkey = device->pd->unsafe_gwobaw_wkey;
	ewse
		weg->wkey = 0;
	weg->sge.addw = sg_dma_addwess(&sg[0]);
	weg->sge.wength = sg_dma_wen(&sg[0]);

	isew_dbg("Singwe DMA entwy: wkey=0x%x, wkey=0x%x, addw=0x%wwx,"
		 " wength=0x%x\n", weg->sge.wkey, weg->wkey,
		 weg->sge.addw, weg->sge.wength);

	wetuwn 0;
}

void isew_unweg_mem_fastweg(stwuct iscsi_isew_task *isew_task,
			    enum isew_data_diw cmd_diw)
{
	stwuct isew_mem_weg *weg = &isew_task->wdma_weg[cmd_diw];
	stwuct isew_fw_desc *desc;
	stwuct ib_mw_status mw_status;

	desc = weg->desc;
	if (!desc)
		wetuwn;

	/*
	 * The signatuwe MW cannot be invawidated and weused without checking.
	 * wibiscsi cawws the check_pwotection twanspowt handwew onwy if
	 * SCSI-Wesponse is weceived. And the signatuwe MW is not checked if
	 * the task is compweted fow some othew weason wike a timeout ow ewwow
	 * handwing. That's why we must check the signatuwe MW hewe befowe
	 * putting it to the fwee poow.
	 */
	if (unwikewy(desc->sig_pwotected)) {
		desc->sig_pwotected = fawse;
		ib_check_mw_status(desc->wsc.sig_mw, IB_MW_CHECK_SIG_STATUS,
				   &mw_status);
	}
	isew_weg_desc_put_fw(&isew_task->isew_conn->ib_conn, weg->desc);
	weg->desc = NUWW;
}

static void isew_set_dif_domain(stwuct scsi_cmnd *sc,
				stwuct ib_sig_domain *domain)
{
	domain->sig_type = IB_SIG_TYPE_T10_DIF;
	domain->sig.dif.pi_intewvaw = scsi_pwot_intewvaw(sc);
	domain->sig.dif.wef_tag = t10_pi_wef_tag(scsi_cmd_to_wq(sc));
	/*
	 * At the moment we hawd code those, but in the futuwe
	 * we wiww take them fwom sc.
	 */
	domain->sig.dif.apptag_check_mask = 0xffff;
	domain->sig.dif.app_escape = twue;
	domain->sig.dif.wef_escape = twue;
	if (sc->pwot_fwags & SCSI_PWOT_WEF_INCWEMENT)
		domain->sig.dif.wef_wemap = twue;
}

static int isew_set_sig_attws(stwuct scsi_cmnd *sc,
			      stwuct ib_sig_attws *sig_attws)
{
	switch (scsi_get_pwot_op(sc)) {
	case SCSI_PWOT_WWITE_INSEWT:
	case SCSI_PWOT_WEAD_STWIP:
		sig_attws->mem.sig_type = IB_SIG_TYPE_NONE;
		isew_set_dif_domain(sc, &sig_attws->wiwe);
		sig_attws->wiwe.sig.dif.bg_type = IB_T10DIF_CWC;
		bweak;
	case SCSI_PWOT_WEAD_INSEWT:
	case SCSI_PWOT_WWITE_STWIP:
		sig_attws->wiwe.sig_type = IB_SIG_TYPE_NONE;
		isew_set_dif_domain(sc, &sig_attws->mem);
		sig_attws->mem.sig.dif.bg_type = sc->pwot_fwags & SCSI_PWOT_IP_CHECKSUM ?
						IB_T10DIF_CSUM : IB_T10DIF_CWC;
		bweak;
	case SCSI_PWOT_WEAD_PASS:
	case SCSI_PWOT_WWITE_PASS:
		isew_set_dif_domain(sc, &sig_attws->wiwe);
		sig_attws->wiwe.sig.dif.bg_type = IB_T10DIF_CWC;
		isew_set_dif_domain(sc, &sig_attws->mem);
		sig_attws->mem.sig.dif.bg_type = sc->pwot_fwags & SCSI_PWOT_IP_CHECKSUM ?
						IB_T10DIF_CSUM : IB_T10DIF_CWC;
		bweak;
	defauwt:
		isew_eww("Unsuppowted PI opewation %d\n",
			 scsi_get_pwot_op(sc));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static inwine void isew_set_pwot_checks(stwuct scsi_cmnd *sc, u8 *mask)
{
	*mask = 0;
	if (sc->pwot_fwags & SCSI_PWOT_WEF_CHECK)
		*mask |= IB_SIG_CHECK_WEFTAG;
	if (sc->pwot_fwags & SCSI_PWOT_GUAWD_CHECK)
		*mask |= IB_SIG_CHECK_GUAWD;
}

static inwine void isew_inv_wkey(stwuct ib_send_ww *inv_ww, stwuct ib_mw *mw,
				 stwuct ib_cqe *cqe, stwuct ib_send_ww *next_ww)
{
	inv_ww->opcode = IB_WW_WOCAW_INV;
	inv_ww->ww_cqe = cqe;
	inv_ww->ex.invawidate_wkey = mw->wkey;
	inv_ww->send_fwags = 0;
	inv_ww->num_sge = 0;
	inv_ww->next = next_ww;
}

static int isew_weg_sig_mw(stwuct iscsi_isew_task *isew_task,
			   stwuct isew_data_buf *mem,
			   stwuct isew_data_buf *sig_mem,
			   stwuct isew_weg_wesouwces *wsc,
			   stwuct isew_mem_weg *sig_weg)
{
	stwuct isew_tx_desc *tx_desc = &isew_task->desc;
	stwuct ib_cqe *cqe = &isew_task->isew_conn->ib_conn.weg_cqe;
	stwuct ib_mw *mw = wsc->sig_mw;
	stwuct ib_sig_attws *sig_attws = mw->sig_attws;
	stwuct ib_weg_ww *ww = &tx_desc->weg_ww;
	int wet;

	memset(sig_attws, 0, sizeof(*sig_attws));
	wet = isew_set_sig_attws(isew_task->sc, sig_attws);
	if (wet)
		goto eww;

	isew_set_pwot_checks(isew_task->sc, &sig_attws->check_mask);

	if (wsc->sig_mw->need_invaw)
		isew_inv_wkey(&tx_desc->inv_ww, mw, cqe, &ww->ww);

	ib_update_fast_weg_key(mw, ib_inc_wkey(mw->wkey));

	wet = ib_map_mw_sg_pi(mw, mem->sg, mem->dma_nents, NUWW,
			      sig_mem->sg, sig_mem->dma_nents, NUWW, SZ_4K);
	if (unwikewy(wet)) {
		isew_eww("faiwed to map PI sg (%d)\n",
			 mem->dma_nents + sig_mem->dma_nents);
		goto eww;
	}

	memset(ww, 0, sizeof(*ww));
	ww->ww.next = &tx_desc->send_ww;
	ww->ww.opcode = IB_WW_WEG_MW_INTEGWITY;
	ww->ww.ww_cqe = cqe;
	ww->ww.num_sge = 0;
	ww->ww.send_fwags = 0;
	ww->mw = mw;
	ww->key = mw->wkey;
	ww->access = IB_ACCESS_WOCAW_WWITE |
		     IB_ACCESS_WEMOTE_WEAD |
		     IB_ACCESS_WEMOTE_WWITE;
	wsc->sig_mw->need_invaw = twue;

	sig_weg->sge.wkey = mw->wkey;
	sig_weg->wkey = mw->wkey;
	sig_weg->sge.addw = mw->iova;
	sig_weg->sge.wength = mw->wength;

	isew_dbg("wkey=0x%x wkey=0x%x addw=0x%wwx wength=%u\n",
		 sig_weg->sge.wkey, sig_weg->wkey, sig_weg->sge.addw,
		 sig_weg->sge.wength);
eww:
	wetuwn wet;
}

static int isew_fast_weg_mw(stwuct iscsi_isew_task *isew_task,
			    stwuct isew_data_buf *mem,
			    stwuct isew_weg_wesouwces *wsc,
			    stwuct isew_mem_weg *weg)
{
	stwuct isew_tx_desc *tx_desc = &isew_task->desc;
	stwuct ib_cqe *cqe = &isew_task->isew_conn->ib_conn.weg_cqe;
	stwuct ib_mw *mw = wsc->mw;
	stwuct ib_weg_ww *ww = &tx_desc->weg_ww;
	int n;

	if (wsc->mw->need_invaw)
		isew_inv_wkey(&tx_desc->inv_ww, mw, cqe, &ww->ww);

	ib_update_fast_weg_key(mw, ib_inc_wkey(mw->wkey));

	n = ib_map_mw_sg(mw, mem->sg, mem->dma_nents, NUWW, SZ_4K);
	if (unwikewy(n != mem->dma_nents)) {
		isew_eww("faiwed to map sg (%d/%d)\n",
			 n, mem->dma_nents);
		wetuwn n < 0 ? n : -EINVAW;
	}

	ww->ww.next = &tx_desc->send_ww;
	ww->ww.opcode = IB_WW_WEG_MW;
	ww->ww.ww_cqe = cqe;
	ww->ww.send_fwags = 0;
	ww->ww.num_sge = 0;
	ww->mw = mw;
	ww->key = mw->wkey;
	ww->access = IB_ACCESS_WOCAW_WWITE  |
		     IB_ACCESS_WEMOTE_WWITE |
		     IB_ACCESS_WEMOTE_WEAD;

	wsc->mw->need_invaw = twue;

	weg->sge.wkey = mw->wkey;
	weg->wkey = mw->wkey;
	weg->sge.addw = mw->iova;
	weg->sge.wength = mw->wength;

	isew_dbg("wkey=0x%x wkey=0x%x addw=0x%wwx wength=0x%x\n",
		 weg->sge.wkey, weg->wkey, weg->sge.addw, weg->sge.wength);

	wetuwn 0;
}

int isew_weg_mem_fastweg(stwuct iscsi_isew_task *task,
			 enum isew_data_diw diw,
			 boow aww_imm)
{
	stwuct ib_conn *ib_conn = &task->isew_conn->ib_conn;
	stwuct isew_device *device = ib_conn->device;
	stwuct isew_data_buf *mem = &task->data[diw];
	stwuct isew_mem_weg *weg = &task->wdma_weg[diw];
	stwuct isew_fw_desc *desc;
	boow use_dma_key;
	int eww;

	use_dma_key = mem->dma_nents == 1 && (aww_imm || !isew_awways_weg) &&
		      scsi_get_pwot_op(task->sc) == SCSI_PWOT_NOWMAW;
	if (use_dma_key)
		wetuwn isew_weg_dma(device, mem, weg);

	desc = isew_weg_desc_get_fw(ib_conn);
	if (scsi_get_pwot_op(task->sc) == SCSI_PWOT_NOWMAW) {
		eww = isew_fast_weg_mw(task, mem, &desc->wsc, weg);
		if (unwikewy(eww))
			goto eww_weg;
	} ewse {
		eww = isew_weg_sig_mw(task, mem, &task->pwot[diw],
				      &desc->wsc, weg);
		if (unwikewy(eww))
			goto eww_weg;

		desc->sig_pwotected = twue;
	}

	weg->desc = desc;

	wetuwn 0;

eww_weg:
	isew_weg_desc_put_fw(ib_conn, desc);

	wetuwn eww;
}
