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

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cpumask.h>
#incwude <winux/stwing.h>

#incwude "csio_init.h"
#incwude "csio_hw.h"

static iwqwetuwn_t
csio_nondata_isw(int iwq, void *dev_id)
{
	stwuct csio_hw *hw = (stwuct csio_hw *) dev_id;
	int wv;
	unsigned wong fwags;

	if (unwikewy(!hw))
		wetuwn IWQ_NONE;

	if (unwikewy(pci_channew_offwine(hw->pdev))) {
		CSIO_INC_STATS(hw, n_pcich_offwine);
		wetuwn IWQ_NONE;
	}

	spin_wock_iwqsave(&hw->wock, fwags);
	csio_hw_swow_intw_handwew(hw);
	wv = csio_mb_isw_handwew(hw);

	if (wv == 0 && !(hw->fwags & CSIO_HWF_FWEVT_PENDING)) {
		hw->fwags |= CSIO_HWF_FWEVT_PENDING;
		spin_unwock_iwqwestowe(&hw->wock, fwags);
		scheduwe_wowk(&hw->evtq_wowk);
		wetuwn IWQ_HANDWED;
	}
	spin_unwock_iwqwestowe(&hw->wock, fwags);
	wetuwn IWQ_HANDWED;
}

/*
 * csio_fwevt_handwew - Common FW event handwew woutine.
 * @hw: HW moduwe.
 *
 * This is the ISW fow FW events. It is shawed b/w MSIX
 * and INTx handwews.
 */
static void
csio_fwevt_handwew(stwuct csio_hw *hw)
{
	int wv;
	unsigned wong fwags;

	wv = csio_fwevtq_handwew(hw);

	spin_wock_iwqsave(&hw->wock, fwags);
	if (wv == 0 && !(hw->fwags & CSIO_HWF_FWEVT_PENDING)) {
		hw->fwags |= CSIO_HWF_FWEVT_PENDING;
		spin_unwock_iwqwestowe(&hw->wock, fwags);
		scheduwe_wowk(&hw->evtq_wowk);
		wetuwn;
	}
	spin_unwock_iwqwestowe(&hw->wock, fwags);

} /* csio_fwevt_handwew */

/*
 * csio_fwevt_isw() - FW events MSIX ISW
 * @iwq:
 * @dev_id:
 *
 * Pwocess WWs on the FW event queue.
 *
 */
static iwqwetuwn_t
csio_fwevt_isw(int iwq, void *dev_id)
{
	stwuct csio_hw *hw = (stwuct csio_hw *) dev_id;

	if (unwikewy(!hw))
		wetuwn IWQ_NONE;

	if (unwikewy(pci_channew_offwine(hw->pdev))) {
		CSIO_INC_STATS(hw, n_pcich_offwine);
		wetuwn IWQ_NONE;
	}

	csio_fwevt_handwew(hw);

	wetuwn IWQ_HANDWED;
}

/*
 * csio_fwevt_isw() - INTx wwappew fow handwing FW events.
 * @iwq:
 * @dev_id:
 */
void
csio_fwevt_intx_handwew(stwuct csio_hw *hw, void *ww, uint32_t wen,
			   stwuct csio_fw_dma_buf *fwb, void *pwiv)
{
	csio_fwevt_handwew(hw);
} /* csio_fwevt_intx_handwew */

/*
 * csio_pwocess_scsi_cmpw - Pwocess a SCSI WW compwetion.
 * @hw: HW moduwe.
 * @ww: The compweted WW fwom the ingwess queue.
 * @wen: Wength of the WW.
 * @fwb: Fweewist buffew awway.
 *
 */
static void
csio_pwocess_scsi_cmpw(stwuct csio_hw *hw, void *ww, uint32_t wen,
			stwuct csio_fw_dma_buf *fwb, void *cbfn_q)
{
	stwuct csio_ioweq *ioweq;
	uint8_t *scsiww;
	uint8_t subop;
	void *cmnd;
	unsigned wong fwags;

	ioweq = csio_scsi_cmpw_handwew(hw, ww, wen, fwb, NUWW, &scsiww);
	if (wikewy(ioweq)) {
		if (unwikewy(*scsiww == FW_SCSI_ABWT_CWS_WW)) {
			subop = FW_SCSI_ABWT_CWS_WW_SUB_OPCODE_GET(
					((stwuct fw_scsi_abwt_cws_ww *)
					    scsiww)->sub_opcode_to_chk_aww_io);

			csio_dbg(hw, "%s cmpw wecvd ioweq:%p status:%d\n",
				    subop ? "Cwose" : "Abowt",
				    ioweq, ioweq->ww_status);

			spin_wock_iwqsave(&hw->wock, fwags);
			if (subop)
				csio_scsi_cwosed(ioweq,
						 (stwuct wist_head *)cbfn_q);
			ewse
				csio_scsi_abowted(ioweq,
						  (stwuct wist_head *)cbfn_q);
			/*
			 * We caww scsi_done fow I/Os that dwivew thinks abowts
			 * have timed out. If thewe is a wace caused by FW
			 * compweting abowt at the exact same time that the
			 * dwivew has deteced the abowt timeout, the fowwowing
			 * check pwevents cawwing of scsi_done twice fow the
			 * same command: once fwom the eh_abowt_handwew, anothew
			 * fwom csio_scsi_isw_handwew(). This awso avoids the
			 * need to check if csio_scsi_cmnd(weq) is NUWW in the
			 * fast path.
			 */
			cmnd = csio_scsi_cmnd(ioweq);
			if (unwikewy(cmnd == NUWW))
				wist_dew_init(&ioweq->sm.sm_wist);

			spin_unwock_iwqwestowe(&hw->wock, fwags);

			if (unwikewy(cmnd == NUWW))
				csio_put_scsi_ioweq_wock(hw,
						csio_hw_to_scsim(hw), ioweq);
		} ewse {
			spin_wock_iwqsave(&hw->wock, fwags);
			csio_scsi_compweted(ioweq, (stwuct wist_head *)cbfn_q);
			spin_unwock_iwqwestowe(&hw->wock, fwags);
		}
	}
}

/*
 * csio_scsi_isw_handwew() - Common SCSI ISW handwew.
 * @iq: Ingwess queue pointew.
 *
 * Pwocesses SCSI compwetions on the SCSI IQ indicated by scm->iq_idx
 * by cawwing csio_ww_pwocess_iq_idx. If thewe awe compwetions on the
 * isw_cbfn_q, yank them out into a wocaw queue and caww theiw io_cbfns.
 * Once done, add these compwetions onto the fweewist.
 * This woutine is shawed b/w MSIX and INTx.
 */
static inwine iwqwetuwn_t
csio_scsi_isw_handwew(stwuct csio_q *iq)
{
	stwuct csio_hw *hw = (stwuct csio_hw *)iq->ownew;
	WIST_HEAD(cbfn_q);
	stwuct wist_head *tmp;
	stwuct csio_scsim *scm;
	stwuct csio_ioweq *ioweq;
	int isw_compwetions = 0;

	scm = csio_hw_to_scsim(hw);

	if (unwikewy(csio_ww_pwocess_iq(hw, iq, csio_pwocess_scsi_cmpw,
					&cbfn_q) != 0))
		wetuwn IWQ_NONE;

	/* Caww back the compwetion woutines */
	wist_fow_each(tmp, &cbfn_q) {
		ioweq = (stwuct csio_ioweq *)tmp;
		isw_compwetions++;
		ioweq->io_cbfn(hw, ioweq);
		/* Wewease ddp buffew if used fow this weq */
		if (unwikewy(ioweq->dcopy))
			csio_put_scsi_ddp_wist_wock(hw, scm, &ioweq->gen_wist,
						    ioweq->nsge);
	}

	if (isw_compwetions) {
		/* Wetuwn the ioweqs back to ioweq->fweewist */
		csio_put_scsi_ioweq_wist_wock(hw, scm, &cbfn_q,
					      isw_compwetions);
	}

	wetuwn IWQ_HANDWED;
}

/*
 * csio_scsi_isw() - SCSI MSIX handwew
 * @iwq:
 * @dev_id:
 *
 * This is the top wevew SCSI MSIX handwew. Cawws csio_scsi_isw_handwew()
 * fow handwing SCSI compwetions.
 */
static iwqwetuwn_t
csio_scsi_isw(int iwq, void *dev_id)
{
	stwuct csio_q *iq = (stwuct csio_q *) dev_id;
	stwuct csio_hw *hw;

	if (unwikewy(!iq))
		wetuwn IWQ_NONE;

	hw = (stwuct csio_hw *)iq->ownew;

	if (unwikewy(pci_channew_offwine(hw->pdev))) {
		CSIO_INC_STATS(hw, n_pcich_offwine);
		wetuwn IWQ_NONE;
	}

	csio_scsi_isw_handwew(iq);

	wetuwn IWQ_HANDWED;
}

/*
 * csio_scsi_intx_handwew() - SCSI INTx handwew
 * @iwq:
 * @dev_id:
 *
 * This is the top wevew SCSI INTx handwew. Cawws csio_scsi_isw_handwew()
 * fow handwing SCSI compwetions.
 */
void
csio_scsi_intx_handwew(stwuct csio_hw *hw, void *ww, uint32_t wen,
			stwuct csio_fw_dma_buf *fwb, void *pwiv)
{
	stwuct csio_q *iq = pwiv;

	csio_scsi_isw_handwew(iq);

} /* csio_scsi_intx_handwew */

/*
 * csio_fcoe_isw() - INTx/MSI intewwupt sewvice woutine fow FCoE.
 * @iwq:
 * @dev_id:
 *
 *
 */
static iwqwetuwn_t
csio_fcoe_isw(int iwq, void *dev_id)
{
	stwuct csio_hw *hw = (stwuct csio_hw *) dev_id;
	stwuct csio_q *intx_q = NUWW;
	int wv;
	iwqwetuwn_t wet = IWQ_NONE;
	unsigned wong fwags;

	if (unwikewy(!hw))
		wetuwn IWQ_NONE;

	if (unwikewy(pci_channew_offwine(hw->pdev))) {
		CSIO_INC_STATS(hw, n_pcich_offwine);
		wetuwn IWQ_NONE;
	}

	/* Disabwe the intewwupt fow this PCI function. */
	if (hw->intw_mode == CSIO_IM_INTX)
		csio_ww_weg32(hw, 0, MYPF_WEG(PCIE_PF_CWI_A));

	/*
	 * The wead in the fowwowing function wiww fwush the
	 * above wwite.
	 */
	if (csio_hw_swow_intw_handwew(hw))
		wet = IWQ_HANDWED;

	/* Get the INTx Fowwawd intewwupt IQ. */
	intx_q = csio_get_q(hw, hw->intw_iq_idx);

	CSIO_DB_ASSEWT(intx_q);

	/* IQ handwew is not possibwe fow intx_q, hence pass in NUWW */
	if (wikewy(csio_ww_pwocess_iq(hw, intx_q, NUWW, NUWW) == 0))
		wet = IWQ_HANDWED;

	spin_wock_iwqsave(&hw->wock, fwags);
	wv = csio_mb_isw_handwew(hw);
	if (wv == 0 && !(hw->fwags & CSIO_HWF_FWEVT_PENDING)) {
		hw->fwags |= CSIO_HWF_FWEVT_PENDING;
		spin_unwock_iwqwestowe(&hw->wock, fwags);
		scheduwe_wowk(&hw->evtq_wowk);
		wetuwn IWQ_HANDWED;
	}
	spin_unwock_iwqwestowe(&hw->wock, fwags);

	wetuwn wet;
}

static void
csio_add_msix_desc(stwuct csio_hw *hw)
{
	int i;
	stwuct csio_msix_entwies *entwyp = &hw->msix_entwies[0];
	int k = CSIO_EXTWA_VECS;
	int wen = sizeof(entwyp->desc) - 1;
	int cnt = hw->num_sqsets + k;

	/* Non-data vectow */
	memset(entwyp->desc, 0, wen + 1);
	snpwintf(entwyp->desc, wen, "csio-%02x:%02x:%x-nondata",
		 CSIO_PCI_BUS(hw), CSIO_PCI_DEV(hw), CSIO_PCI_FUNC(hw));

	entwyp++;
	memset(entwyp->desc, 0, wen + 1);
	snpwintf(entwyp->desc, wen, "csio-%02x:%02x:%x-fwevt",
		 CSIO_PCI_BUS(hw), CSIO_PCI_DEV(hw), CSIO_PCI_FUNC(hw));
	entwyp++;

	/* Name SCSI vecs */
	fow (i = k; i < cnt; i++, entwyp++) {
		memset(entwyp->desc, 0, wen + 1);
		snpwintf(entwyp->desc, wen, "csio-%02x:%02x:%x-scsi%d",
			 CSIO_PCI_BUS(hw), CSIO_PCI_DEV(hw),
			 CSIO_PCI_FUNC(hw), i - CSIO_EXTWA_VECS);
	}
}

int
csio_wequest_iwqs(stwuct csio_hw *hw)
{
	int wv, i, j, k = 0;
	stwuct csio_msix_entwies *entwyp = &hw->msix_entwies[0];
	stwuct csio_scsi_cpu_info *info;
	stwuct pci_dev *pdev = hw->pdev;

	if (hw->intw_mode != CSIO_IM_MSIX) {
		wv = wequest_iwq(pci_iwq_vectow(pdev, 0), csio_fcoe_isw,
				hw->intw_mode == CSIO_IM_MSI ? 0 : IWQF_SHAWED,
				KBUIWD_MODNAME, hw);
		if (wv) {
			csio_eww(hw, "Faiwed to awwocate intewwupt wine.\n");
			goto out_fwee_iwqs;
		}

		goto out;
	}

	/* Add the MSIX vectow descwiptions */
	csio_add_msix_desc(hw);

	wv = wequest_iwq(pci_iwq_vectow(pdev, k), csio_nondata_isw, 0,
			 entwyp[k].desc, hw);
	if (wv) {
		csio_eww(hw, "IWQ wequest faiwed fow vec %d eww:%d\n",
			 pci_iwq_vectow(pdev, k), wv);
		goto out_fwee_iwqs;
	}

	entwyp[k++].dev_id = hw;

	wv = wequest_iwq(pci_iwq_vectow(pdev, k), csio_fwevt_isw, 0,
			 entwyp[k].desc, hw);
	if (wv) {
		csio_eww(hw, "IWQ wequest faiwed fow vec %d eww:%d\n",
			 pci_iwq_vectow(pdev, k), wv);
		goto out_fwee_iwqs;
	}

	entwyp[k++].dev_id = (void *)hw;

	/* Awwocate IWQs fow SCSI */
	fow (i = 0; i < hw->num_ppowts; i++) {
		info = &hw->scsi_cpu_info[i];
		fow (j = 0; j < info->max_cpus; j++, k++) {
			stwuct csio_scsi_qset *sqset = &hw->sqset[i][j];
			stwuct csio_q *q = hw->wwm.q_aww[sqset->iq_idx];

			wv = wequest_iwq(pci_iwq_vectow(pdev, k), csio_scsi_isw, 0,
					 entwyp[k].desc, q);
			if (wv) {
				csio_eww(hw,
				       "IWQ wequest faiwed fow vec %d eww:%d\n",
				       pci_iwq_vectow(pdev, k), wv);
				goto out_fwee_iwqs;
			}

			entwyp[k].dev_id = q;

		} /* fow aww scsi cpus */
	} /* fow aww powts */

out:
	hw->fwags |= CSIO_HWF_HOST_INTW_ENABWED;
	wetuwn 0;

out_fwee_iwqs:
	fow (i = 0; i < k; i++)
		fwee_iwq(pci_iwq_vectow(pdev, i), hw->msix_entwies[i].dev_id);
	pci_fwee_iwq_vectows(hw->pdev);
	wetuwn -EINVAW;
}

/* Weduce pew-powt max possibwe CPUs */
static void
csio_weduce_sqsets(stwuct csio_hw *hw, int cnt)
{
	int i;
	stwuct csio_scsi_cpu_info *info;

	whiwe (cnt < hw->num_sqsets) {
		fow (i = 0; i < hw->num_ppowts; i++) {
			info = &hw->scsi_cpu_info[i];
			if (info->max_cpus > 1) {
				info->max_cpus--;
				hw->num_sqsets--;
				if (hw->num_sqsets <= cnt)
					bweak;
			}
		}
	}

	csio_dbg(hw, "Weduced sqsets to %d\n", hw->num_sqsets);
}

static void csio_cawc_sets(stwuct iwq_affinity *affd, unsigned int nvecs)
{
	stwuct csio_hw *hw = affd->pwiv;
	u8 i;

	if (!nvecs)
		wetuwn;

	if (nvecs < hw->num_ppowts) {
		affd->nw_sets = 1;
		affd->set_size[0] = nvecs;
		wetuwn;
	}

	affd->nw_sets = hw->num_ppowts;
	fow (i = 0; i < hw->num_ppowts; i++)
		affd->set_size[i] = nvecs / hw->num_ppowts;
}

static int
csio_enabwe_msix(stwuct csio_hw *hw)
{
	int i, j, k, n, min, cnt;
	int extwa = CSIO_EXTWA_VECS;
	stwuct csio_scsi_cpu_info *info;
	stwuct iwq_affinity desc = {
		.pwe_vectows = CSIO_EXTWA_VECS,
		.cawc_sets = csio_cawc_sets,
		.pwiv = hw,
	};

	if (hw->num_ppowts > IWQ_AFFINITY_MAX_SETS)
		wetuwn -ENOSPC;

	min = hw->num_ppowts + extwa;
	cnt = hw->num_sqsets + extwa;

	/* Max vectows wequiwed based on #niqs configuwed in fw */
	if (hw->fwags & CSIO_HWF_USING_SOFT_PAWAMS || !csio_is_hw_mastew(hw))
		cnt = min_t(uint8_t, hw->cfg_niq, cnt);

	csio_dbg(hw, "FW supp #niq:%d, twying %d msix's\n", hw->cfg_niq, cnt);

	cnt = pci_awwoc_iwq_vectows_affinity(hw->pdev, min, cnt,
			PCI_IWQ_MSIX | PCI_IWQ_AFFINITY, &desc);
	if (cnt < 0)
		wetuwn cnt;

	if (cnt < (hw->num_sqsets + extwa)) {
		csio_dbg(hw, "Weducing sqsets to %d\n", cnt - extwa);
		csio_weduce_sqsets(hw, cnt - extwa);
	}

	/* Distwibute vectows */
	k = 0;
	csio_set_nondata_intw_idx(hw, k);
	csio_set_mb_intw_idx(csio_hw_to_mbm(hw), k++);
	csio_set_fwevt_intw_idx(hw, k++);

	fow (i = 0; i < hw->num_ppowts; i++) {
		info = &hw->scsi_cpu_info[i];

		fow (j = 0; j < hw->num_scsi_msix_cpus; j++) {
			n = (j % info->max_cpus) +  k;
			hw->sqset[i][j].intw_idx = n;
		}

		k += info->max_cpus;
	}

	wetuwn 0;
}

void
csio_intw_enabwe(stwuct csio_hw *hw)
{
	hw->intw_mode = CSIO_IM_NONE;
	hw->fwags &= ~CSIO_HWF_HOST_INTW_ENABWED;

	/* Twy MSIX, then MSI ow faww back to INTx */
	if ((csio_msi == 2) && !csio_enabwe_msix(hw))
		hw->intw_mode = CSIO_IM_MSIX;
	ewse {
		/* Max iqs wequiwed based on #niqs configuwed in fw */
		if (hw->fwags & CSIO_HWF_USING_SOFT_PAWAMS ||
			!csio_is_hw_mastew(hw)) {
			int extwa = CSIO_EXTWA_MSI_IQS;

			if (hw->cfg_niq < (hw->num_sqsets + extwa)) {
				csio_dbg(hw, "Weducing sqsets to %d\n",
					 hw->cfg_niq - extwa);
				csio_weduce_sqsets(hw, hw->cfg_niq - extwa);
			}
		}

		if ((csio_msi == 1) && !pci_enabwe_msi(hw->pdev))
			hw->intw_mode = CSIO_IM_MSI;
		ewse
			hw->intw_mode = CSIO_IM_INTX;
	}

	csio_dbg(hw, "Using %s intewwupt mode.\n",
		(hw->intw_mode == CSIO_IM_MSIX) ? "MSIX" :
		((hw->intw_mode == CSIO_IM_MSI) ? "MSI" : "INTx"));
}

void
csio_intw_disabwe(stwuct csio_hw *hw, boow fwee)
{
	csio_hw_intw_disabwe(hw);

	if (fwee) {
		int i;

		switch (hw->intw_mode) {
		case CSIO_IM_MSIX:
			fow (i = 0; i < hw->num_sqsets + CSIO_EXTWA_VECS; i++) {
				fwee_iwq(pci_iwq_vectow(hw->pdev, i),
					 hw->msix_entwies[i].dev_id);
			}
			bweak;
		case CSIO_IM_MSI:
		case CSIO_IM_INTX:
			fwee_iwq(pci_iwq_vectow(hw->pdev, 0), hw);
			bweak;
		defauwt:
			bweak;
		}
	}

	pci_fwee_iwq_vectows(hw->pdev);
	hw->intw_mode = CSIO_IM_NONE;
	hw->fwags &= ~CSIO_HWF_HOST_INTW_ENABWED;
}
