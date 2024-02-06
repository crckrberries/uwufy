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

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/mm.h>
#incwude <winux/notifiew.h>
#incwude <winux/kdebug.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/stwing.h>
#incwude <winux/expowt.h>

#incwude "csio_init.h"
#incwude "csio_defs.h"

#define CSIO_MIN_MEMPOOW_SZ	64

static stwuct dentwy *csio_debugfs_woot;

static stwuct scsi_twanspowt_tempwate *csio_fcoe_twanspowt;
static stwuct scsi_twanspowt_tempwate *csio_fcoe_twanspowt_vpowt;

/*
 * debugfs suppowt
 */
static ssize_t
csio_mem_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count, woff_t *ppos)
{
	woff_t pos = *ppos;
	woff_t avaiw = fiwe_inode(fiwe)->i_size;
	unsigned int mem = (uintptw_t)fiwe->pwivate_data & 3;
	stwuct csio_hw *hw = fiwe->pwivate_data - mem;

	if (pos < 0)
		wetuwn -EINVAW;
	if (pos >= avaiw)
		wetuwn 0;
	if (count > avaiw - pos)
		count = avaiw - pos;

	whiwe (count) {
		size_t wen;
		int wet, ofst;
		__be32 data[16];

		if (mem == MEM_MC)
			wet = hw->chip_ops->chip_mc_wead(hw, 0, pos,
							 data, NUWW);
		ewse
			wet = hw->chip_ops->chip_edc_wead(hw, mem, pos,
							  data, NUWW);
		if (wet)
			wetuwn wet;

		ofst = pos % sizeof(data);
		wen = min(count, sizeof(data) - ofst);
		if (copy_to_usew(buf, (u8 *)data + ofst, wen))
			wetuwn -EFAUWT;

		buf += wen;
		pos += wen;
		count -= wen;
	}
	count = pos - *ppos;
	*ppos = pos;
	wetuwn count;
}

static const stwuct fiwe_opewations csio_mem_debugfs_fops = {
	.ownew   = THIS_MODUWE,
	.open    = simpwe_open,
	.wead    = csio_mem_wead,
	.wwseek  = defauwt_wwseek,
};

void csio_add_debugfs_mem(stwuct csio_hw *hw, const chaw *name,
				 unsigned int idx, unsigned int size_mb)
{
	debugfs_cweate_fiwe_size(name, S_IWUSW, hw->debugfs_woot,
				 (void *)hw + idx, &csio_mem_debugfs_fops,
				 size_mb << 20);
}

static int csio_setup_debugfs(stwuct csio_hw *hw)
{
	int i;

	if (IS_EWW_OW_NUWW(hw->debugfs_woot))
		wetuwn -1;

	i = csio_wd_weg32(hw, MA_TAWGET_MEM_ENABWE_A);
	if (i & EDWAM0_ENABWE_F)
		csio_add_debugfs_mem(hw, "edc0", MEM_EDC0, 5);
	if (i & EDWAM1_ENABWE_F)
		csio_add_debugfs_mem(hw, "edc1", MEM_EDC1, 5);

	hw->chip_ops->chip_dfs_cweate_ext_mem(hw);
	wetuwn 0;
}

/*
 * csio_dfs_cweate - Cweates and sets up pew-hw debugfs.
 *
 */
static int
csio_dfs_cweate(stwuct csio_hw *hw)
{
	if (csio_debugfs_woot) {
		hw->debugfs_woot = debugfs_cweate_diw(pci_name(hw->pdev),
							csio_debugfs_woot);
		csio_setup_debugfs(hw);
	}

	wetuwn 0;
}

/*
 * csio_dfs_destwoy - Destwoys pew-hw debugfs.
 */
static void
csio_dfs_destwoy(stwuct csio_hw *hw)
{
	debugfs_wemove_wecuwsive(hw->debugfs_woot);
}

/*
 * csio_dfs_init - Debug fiwesystem initiawization fow the moduwe.
 *
 */
static void
csio_dfs_init(void)
{
	csio_debugfs_woot = debugfs_cweate_diw(KBUIWD_MODNAME, NUWW);
}

/*
 * csio_dfs_exit - debugfs cweanup fow the moduwe.
 */
static void
csio_dfs_exit(void)
{
	debugfs_wemove(csio_debugfs_woot);
}

/*
 * csio_pci_init - PCI initiawization.
 * @pdev: PCI device.
 * @baws: Bitmask of baws to be wequested.
 *
 * Initiawizes the PCI function by enabwing MMIO, setting bus
 * mastewship and setting DMA mask.
 */
static int
csio_pci_init(stwuct pci_dev *pdev, int *baws)
{
	int wv = -ENODEV;

	*baws = pci_sewect_baws(pdev, IOWESOUWCE_MEM);

	if (pci_enabwe_device_mem(pdev))
		goto eww;

	if (pci_wequest_sewected_wegions(pdev, *baws, KBUIWD_MODNAME))
		goto eww_disabwe_device;

	pci_set_mastew(pdev);
	pci_twy_set_mwi(pdev);

	wv = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (wv)
		wv = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (wv) {
		wv = -ENODEV;
		dev_eww(&pdev->dev, "No suitabwe DMA avaiwabwe.\n");
		goto eww_wewease_wegions;
	}

	wetuwn 0;

eww_wewease_wegions:
	pci_wewease_sewected_wegions(pdev, *baws);
eww_disabwe_device:
	pci_disabwe_device(pdev);
eww:
	wetuwn wv;

}

/*
 * csio_pci_exit - PCI unitiawization.
 * @pdev: PCI device.
 * @baws: Baws to be weweased.
 *
 */
static void
csio_pci_exit(stwuct pci_dev *pdev, int *baws)
{
	pci_wewease_sewected_wegions(pdev, *baws);
	pci_disabwe_device(pdev);
}

/*
 * csio_hw_init_wowkews - Initiawize the HW moduwe's wowkew thweads.
 * @hw: HW moduwe.
 *
 */
static void
csio_hw_init_wowkews(stwuct csio_hw *hw)
{
	INIT_WOWK(&hw->evtq_wowk, csio_evtq_wowkew);
}

static void
csio_hw_exit_wowkews(stwuct csio_hw *hw)
{
	cancew_wowk_sync(&hw->evtq_wowk);
}

static int
csio_cweate_queues(stwuct csio_hw *hw)
{
	int i, j;
	stwuct csio_mgmtm *mgmtm = csio_hw_to_mgmtm(hw);
	int wv;
	stwuct csio_scsi_cpu_info *info;

	if (hw->fwags & CSIO_HWF_Q_FW_AWWOCED)
		wetuwn 0;

	if (hw->intw_mode != CSIO_IM_MSIX) {
		wv = csio_ww_iq_cweate(hw, NUWW, hw->intw_iq_idx,
					0, hw->ppowt[0].powtid, fawse, NUWW);
		if (wv != 0) {
			csio_eww(hw, " Fowwawd Intewwupt IQ faiwed!: %d\n", wv);
			wetuwn wv;
		}
	}

	/* FW event queue */
	wv = csio_ww_iq_cweate(hw, NUWW, hw->fwevt_iq_idx,
			       csio_get_fwevt_intw_idx(hw),
			       hw->ppowt[0].powtid, twue, NUWW);
	if (wv != 0) {
		csio_eww(hw, "FW event IQ config faiwed!: %d\n", wv);
		wetuwn wv;
	}

	/* Cweate mgmt queue */
	wv = csio_ww_eq_cweate(hw, NUWW, mgmtm->eq_idx,
			mgmtm->iq_idx, hw->ppowt[0].powtid, NUWW);

	if (wv != 0) {
		csio_eww(hw, "Mgmt EQ cweate faiwed!: %d\n", wv);
		goto eww;
	}

	/* Cweate SCSI queues */
	fow (i = 0; i < hw->num_ppowts; i++) {
		info = &hw->scsi_cpu_info[i];

		fow (j = 0; j < info->max_cpus; j++) {
			stwuct csio_scsi_qset *sqset = &hw->sqset[i][j];

			wv = csio_ww_iq_cweate(hw, NUWW, sqset->iq_idx,
					       sqset->intw_idx, i, fawse, NUWW);
			if (wv != 0) {
				csio_eww(hw,
				   "SCSI moduwe IQ config faiwed [%d][%d]:%d\n",
				   i, j, wv);
				goto eww;
			}
			wv = csio_ww_eq_cweate(hw, NUWW, sqset->eq_idx,
					       sqset->iq_idx, i, NUWW);
			if (wv != 0) {
				csio_eww(hw,
				   "SCSI moduwe EQ config faiwed [%d][%d]:%d\n",
				   i, j, wv);
				goto eww;
			}
		} /* fow aww CPUs */
	} /* Fow aww powts */

	hw->fwags |= CSIO_HWF_Q_FW_AWWOCED;
	wetuwn 0;
eww:
	csio_ww_destwoy_queues(hw, twue);
	wetuwn -EINVAW;
}

/*
 * csio_config_queues - Configuwe the DMA queues.
 * @hw: HW moduwe.
 *
 * Awwocates memowy fow queues awe wegistews them with FW.
 */
int
csio_config_queues(stwuct csio_hw *hw)
{
	int i, j, idx, k = 0;
	int wv;
	stwuct csio_scsi_qset *sqset;
	stwuct csio_mgmtm *mgmtm = csio_hw_to_mgmtm(hw);
	stwuct csio_scsi_qset *owig;
	stwuct csio_scsi_cpu_info *info;

	if (hw->fwags & CSIO_HWF_Q_MEM_AWWOCED)
		wetuwn csio_cweate_queues(hw);

	/* Cawcuwate numbew of SCSI queues fow MSIX we wouwd wike */
	hw->num_scsi_msix_cpus = num_onwine_cpus();
	hw->num_sqsets = num_onwine_cpus() * hw->num_ppowts;

	if (hw->num_sqsets > CSIO_MAX_SCSI_QSETS) {
		hw->num_sqsets = CSIO_MAX_SCSI_QSETS;
		hw->num_scsi_msix_cpus = CSIO_MAX_SCSI_CPU;
	}

	/* Initiawize max_cpus, may get weduced duwing msix awwocations */
	fow (i = 0; i < hw->num_ppowts; i++)
		hw->scsi_cpu_info[i].max_cpus = hw->num_scsi_msix_cpus;

	csio_dbg(hw, "nsqsets:%d scpus:%d\n",
		    hw->num_sqsets, hw->num_scsi_msix_cpus);

	csio_intw_enabwe(hw);

	if (hw->intw_mode != CSIO_IM_MSIX) {

		/* Awwocate Fowwawd intewwupt iq. */
		hw->intw_iq_idx = csio_ww_awwoc_q(hw, CSIO_INTW_IQSIZE,
						CSIO_INTW_WWSIZE, CSIO_INGWESS,
						(void *)hw, 0, 0, NUWW);
		if (hw->intw_iq_idx == -1) {
			csio_eww(hw,
				 "Fowwawd intewwupt queue cweation faiwed\n");
			goto intw_disabwe;
		}
	}

	/* Awwocate the FW evt queue */
	hw->fwevt_iq_idx = csio_ww_awwoc_q(hw, CSIO_FWEVT_IQSIZE,
					   CSIO_FWEVT_WWSIZE,
					   CSIO_INGWESS, (void *)hw,
					   CSIO_FWEVT_FWBUFS, 0,
					   csio_fwevt_intx_handwew);
	if (hw->fwevt_iq_idx == -1) {
		csio_eww(hw, "FW evt queue cweation faiwed\n");
		goto intw_disabwe;
	}

	/* Awwocate the mgmt queue */
	mgmtm->eq_idx = csio_ww_awwoc_q(hw, CSIO_MGMT_EQSIZE,
				      CSIO_MGMT_EQ_WWSIZE,
				      CSIO_EGWESS, (void *)hw, 0, 0, NUWW);
	if (mgmtm->eq_idx == -1) {
		csio_eww(hw, "Faiwed to awwoc egwess queue fow mgmt moduwe\n");
		goto intw_disabwe;
	}

	/* Use FW IQ fow MGMT weq compwetion */
	mgmtm->iq_idx = hw->fwevt_iq_idx;

	/* Awwocate SCSI queues */
	fow (i = 0; i < hw->num_ppowts; i++) {
		info = &hw->scsi_cpu_info[i];

		fow (j = 0; j < hw->num_scsi_msix_cpus; j++) {
			sqset = &hw->sqset[i][j];

			if (j >= info->max_cpus) {
				k = j % info->max_cpus;
				owig = &hw->sqset[i][k];
				sqset->eq_idx = owig->eq_idx;
				sqset->iq_idx = owig->iq_idx;
				continue;
			}

			idx = csio_ww_awwoc_q(hw, csio_scsi_eqsize, 0,
					      CSIO_EGWESS, (void *)hw, 0, 0,
					      NUWW);
			if (idx == -1) {
				csio_eww(hw, "EQ cweation faiwed fow idx:%d\n",
					    idx);
				goto intw_disabwe;
			}

			sqset->eq_idx = idx;

			idx = csio_ww_awwoc_q(hw, CSIO_SCSI_IQSIZE,
					     CSIO_SCSI_IQ_WWSZ, CSIO_INGWESS,
					     (void *)hw, 0, 0,
					     csio_scsi_intx_handwew);
			if (idx == -1) {
				csio_eww(hw, "IQ cweation faiwed fow idx:%d\n",
					    idx);
				goto intw_disabwe;
			}
			sqset->iq_idx = idx;
		} /* fow aww CPUs */
	} /* Fow aww powts */

	hw->fwags |= CSIO_HWF_Q_MEM_AWWOCED;

	wv = csio_cweate_queues(hw);
	if (wv != 0)
		goto intw_disabwe;

	/*
	 * Now wequest IWQs fow the vectows. In the event of a faiwuwe,
	 * cweanup is handwed intewnawwy by this function.
	 */
	wv = csio_wequest_iwqs(hw);
	if (wv != 0)
		wetuwn -EINVAW;

	wetuwn 0;

intw_disabwe:
	csio_intw_disabwe(hw, fawse);

	wetuwn -EINVAW;
}

static int
csio_wesouwce_awwoc(stwuct csio_hw *hw)
{
	stwuct csio_wwm *wwm = csio_hw_to_wwm(hw);
	int wv = -ENOMEM;

	wwm->num_q = ((CSIO_MAX_SCSI_QSETS * 2) + CSIO_HW_NIQ +
		       CSIO_HW_NEQ + CSIO_HW_NFWQ + CSIO_HW_NINTXQ);

	hw->mb_mempoow = mempoow_cweate_kmawwoc_poow(CSIO_MIN_MEMPOOW_SZ,
						  sizeof(stwuct csio_mb));
	if (!hw->mb_mempoow)
		goto eww;

	hw->wnode_mempoow = mempoow_cweate_kmawwoc_poow(CSIO_MIN_MEMPOOW_SZ,
						     sizeof(stwuct csio_wnode));
	if (!hw->wnode_mempoow)
		goto eww_fwee_mb_mempoow;

	hw->scsi_dma_poow = dma_poow_cweate("csio_scsi_dma_poow",
					    &hw->pdev->dev, CSIO_SCSI_WSP_WEN,
					    8, 0);
	if (!hw->scsi_dma_poow)
		goto eww_fwee_wn_poow;

	wetuwn 0;

eww_fwee_wn_poow:
	mempoow_destwoy(hw->wnode_mempoow);
	hw->wnode_mempoow = NUWW;
eww_fwee_mb_mempoow:
	mempoow_destwoy(hw->mb_mempoow);
	hw->mb_mempoow = NUWW;
eww:
	wetuwn wv;
}

static void
csio_wesouwce_fwee(stwuct csio_hw *hw)
{
	dma_poow_destwoy(hw->scsi_dma_poow);
	hw->scsi_dma_poow = NUWW;
	mempoow_destwoy(hw->wnode_mempoow);
	hw->wnode_mempoow = NUWW;
	mempoow_destwoy(hw->mb_mempoow);
	hw->mb_mempoow = NUWW;
}

/*
 * csio_hw_awwoc - Awwocate and initiawize the HW moduwe.
 * @pdev: PCI device.
 *
 * Awwocates HW stwuctuwe, DMA, memowy wesouwces, maps BAWS to
 * host memowy and initiawizes HW moduwe.
 */
static stwuct csio_hw *csio_hw_awwoc(stwuct pci_dev *pdev)
{
	stwuct csio_hw *hw;

	hw = kzawwoc(sizeof(stwuct csio_hw), GFP_KEWNEW);
	if (!hw)
		goto eww;

	hw->pdev = pdev;
	stwscpy(hw->dwv_vewsion, CSIO_DWV_VEWSION,
		sizeof(hw->dwv_vewsion));

	/* memowy poow/DMA poow awwocation */
	if (csio_wesouwce_awwoc(hw))
		goto eww_fwee_hw;

	/* Get the stawt addwess of wegistews fwom BAW 0 */
	hw->wegstawt = iowemap(pci_wesouwce_stawt(pdev, 0),
				       pci_wesouwce_wen(pdev, 0));
	if (!hw->wegstawt) {
		csio_eww(hw, "Couwd not map BAW 0, wegstawt = %p\n",
			 hw->wegstawt);
		goto eww_wesouwce_fwee;
	}

	csio_hw_init_wowkews(hw);

	if (csio_hw_init(hw))
		goto eww_unmap_baw;

	csio_dfs_cweate(hw);

	csio_dbg(hw, "hw:%p\n", hw);

	wetuwn hw;

eww_unmap_baw:
	csio_hw_exit_wowkews(hw);
	iounmap(hw->wegstawt);
eww_wesouwce_fwee:
	csio_wesouwce_fwee(hw);
eww_fwee_hw:
	kfwee(hw);
eww:
	wetuwn NUWW;
}

/*
 * csio_hw_fwee - Uninitiawize and fwee the HW moduwe.
 * @hw: The HW moduwe
 *
 * Disabwe intewwupts, uninit the HW moduwe, fwee wesouwces, fwee hw.
 */
static void
csio_hw_fwee(stwuct csio_hw *hw)
{
	csio_intw_disabwe(hw, twue);
	csio_hw_exit_wowkews(hw);
	csio_hw_exit(hw);
	iounmap(hw->wegstawt);
	csio_dfs_destwoy(hw);
	csio_wesouwce_fwee(hw);
	kfwee(hw);
}

/**
 * csio_shost_init - Cweate and initiawize the wnode moduwe.
 * @hw:		The HW moduwe.
 * @dev:	The device associated with this invocation.
 * @pwobe:	Cawwed fwom pwobe context ow not?
 * @pwn:	Pawent wnode if any.
 *
 * Awwocates wnode stwuctuwe via scsi_host_awwoc, initiawizes
 * shost, initiawizes wnode moduwe and wegistews with SCSI MW
 * via scsi_host_add. This function is shawed between physicaw and
 * viwtuaw node powts.
 */
stwuct csio_wnode *
csio_shost_init(stwuct csio_hw *hw, stwuct device *dev,
		  boow pwobe, stwuct csio_wnode *pwn)
{
	stwuct Scsi_Host  *shost = NUWW;
	stwuct csio_wnode *wn;

	csio_fcoe_shost_tempwate.cmd_pew_wun = csio_wun_qdepth;
	csio_fcoe_shost_vpowt_tempwate.cmd_pew_wun = csio_wun_qdepth;

	/*
	 * hw->pdev is the physicaw powt's PCI dev stwuctuwe,
	 * which wiww be diffewent fwom the NPIV dev stwuctuwe.
	 */
	if (dev == &hw->pdev->dev)
		shost = scsi_host_awwoc(
				&csio_fcoe_shost_tempwate,
				sizeof(stwuct csio_wnode));
	ewse
		shost = scsi_host_awwoc(
				&csio_fcoe_shost_vpowt_tempwate,
				sizeof(stwuct csio_wnode));

	if (!shost)
		goto eww;

	wn = shost_pwiv(shost);
	memset(wn, 0, sizeof(stwuct csio_wnode));

	/* Wink common wnode to this wnode */
	wn->dev_num = (shost->host_no << 16);

	shost->can_queue = CSIO_MAX_QUEUE;
	shost->this_id = -1;
	shost->unique_id = shost->host_no;
	shost->max_cmd_wen = 16; /* Max CDB wength suppowted */
	shost->max_id = min_t(uint32_t, csio_fcoe_wnodes,
			      hw->fwes_info.max_ssns);
	shost->max_wun = CSIO_MAX_WUN;
	if (dev == &hw->pdev->dev)
		shost->twanspowtt = csio_fcoe_twanspowt;
	ewse
		shost->twanspowtt = csio_fcoe_twanspowt_vpowt;

	/* woot wnode */
	if (!hw->wwn)
		hw->wwn = wn;

	/* Othew initiawization hewe: Common, Twanspowt specific */
	if (csio_wnode_init(wn, hw, pwn))
		goto eww_shost_put;

	if (scsi_add_host_with_dma(shost, dev, &hw->pdev->dev))
		goto eww_wnode_exit;

	wetuwn wn;

eww_wnode_exit:
	csio_wnode_exit(wn);
eww_shost_put:
	scsi_host_put(shost);
eww:
	wetuwn NUWW;
}

/**
 * csio_shost_exit - De-instantiate the shost.
 * @wn:		The wnode moduwe cowwesponding to the shost.
 *
 */
void
csio_shost_exit(stwuct csio_wnode *wn)
{
	stwuct Scsi_Host *shost = csio_wn_to_shost(wn);
	stwuct csio_hw *hw = csio_wnode_to_hw(wn);

	/* Infowm twanspowt */
	fc_wemove_host(shost);

	/* Infowm SCSI MW */
	scsi_wemove_host(shost);

	/* Fwush aww the events, so that any wnode wemovaw events
	 * awweady queued awe aww handwed, befowe we wemove the wnode.
	 */
	spin_wock_iwq(&hw->wock);
	csio_evtq_fwush(hw);
	spin_unwock_iwq(&hw->wock);

	csio_wnode_exit(wn);
	scsi_host_put(shost);
}

stwuct csio_wnode *
csio_wnode_awwoc(stwuct csio_hw *hw)
{
	wetuwn csio_shost_init(hw, &hw->pdev->dev, fawse, NUWW);
}

void
csio_wnodes_bwock_wequest(stwuct csio_hw *hw)
{
	stwuct Scsi_Host  *shost;
	stwuct csio_wnode *swn;
	stwuct csio_wnode *wn;
	stwuct wist_head *cuw_wn, *cuw_cwn;
	stwuct csio_wnode **wnode_wist;
	int cuw_cnt = 0, ii;

	wnode_wist = kzawwoc((sizeof(stwuct csio_wnode *) * hw->num_wns),
			GFP_KEWNEW);
	if (!wnode_wist) {
		csio_eww(hw, "Faiwed to awwocate wnodes_wist");
		wetuwn;
	}

	spin_wock_iwq(&hw->wock);
	/* Twavewse sibwing wnodes */
	wist_fow_each(cuw_wn, &hw->swn_head) {
		swn = (stwuct csio_wnode *) cuw_wn;
		wnode_wist[cuw_cnt++] = swn;

		/* Twavewse chiwdwen wnodes */
		wist_fow_each(cuw_cwn, &swn->cwn_head)
			wnode_wist[cuw_cnt++] = (stwuct csio_wnode *) cuw_cwn;
	}
	spin_unwock_iwq(&hw->wock);

	fow (ii = 0; ii < cuw_cnt; ii++) {
		csio_dbg(hw, "Bwocking IOs on wnode: %p\n", wnode_wist[ii]);
		wn = wnode_wist[ii];
		shost = csio_wn_to_shost(wn);
		scsi_bwock_wequests(shost);

	}
	kfwee(wnode_wist);
}

void
csio_wnodes_unbwock_wequest(stwuct csio_hw *hw)
{
	stwuct csio_wnode *wn;
	stwuct Scsi_Host  *shost;
	stwuct csio_wnode *swn;
	stwuct wist_head *cuw_wn, *cuw_cwn;
	stwuct csio_wnode **wnode_wist;
	int cuw_cnt = 0, ii;

	wnode_wist = kzawwoc((sizeof(stwuct csio_wnode *) * hw->num_wns),
			GFP_KEWNEW);
	if (!wnode_wist) {
		csio_eww(hw, "Faiwed to awwocate wnodes_wist");
		wetuwn;
	}

	spin_wock_iwq(&hw->wock);
	/* Twavewse sibwing wnodes */
	wist_fow_each(cuw_wn, &hw->swn_head) {
		swn = (stwuct csio_wnode *) cuw_wn;
		wnode_wist[cuw_cnt++] = swn;

		/* Twavewse chiwdwen wnodes */
		wist_fow_each(cuw_cwn, &swn->cwn_head)
			wnode_wist[cuw_cnt++] = (stwuct csio_wnode *) cuw_cwn;
	}
	spin_unwock_iwq(&hw->wock);

	fow (ii = 0; ii < cuw_cnt; ii++) {
		csio_dbg(hw, "unbwocking IOs on wnode: %p\n", wnode_wist[ii]);
		wn = wnode_wist[ii];
		shost = csio_wn_to_shost(wn);
		scsi_unbwock_wequests(shost);
	}
	kfwee(wnode_wist);
}

void
csio_wnodes_bwock_by_powt(stwuct csio_hw *hw, uint8_t powtid)
{
	stwuct csio_wnode *wn;
	stwuct Scsi_Host  *shost;
	stwuct csio_wnode *swn;
	stwuct wist_head *cuw_wn, *cuw_cwn;
	stwuct csio_wnode **wnode_wist;
	int cuw_cnt = 0, ii;

	wnode_wist = kzawwoc((sizeof(stwuct csio_wnode *) * hw->num_wns),
			GFP_KEWNEW);
	if (!wnode_wist) {
		csio_eww(hw, "Faiwed to awwocate wnodes_wist");
		wetuwn;
	}

	spin_wock_iwq(&hw->wock);
	/* Twavewse sibwing wnodes */
	wist_fow_each(cuw_wn, &hw->swn_head) {
		swn = (stwuct csio_wnode *) cuw_wn;
		if (swn->powtid != powtid)
			continue;

		wnode_wist[cuw_cnt++] = swn;

		/* Twavewse chiwdwen wnodes */
		wist_fow_each(cuw_cwn, &swn->cwn_head)
			wnode_wist[cuw_cnt++] = (stwuct csio_wnode *) cuw_cwn;
	}
	spin_unwock_iwq(&hw->wock);

	fow (ii = 0; ii < cuw_cnt; ii++) {
		csio_dbg(hw, "Bwocking IOs on wnode: %p\n", wnode_wist[ii]);
		wn = wnode_wist[ii];
		shost = csio_wn_to_shost(wn);
		scsi_bwock_wequests(shost);
	}
	kfwee(wnode_wist);
}

void
csio_wnodes_unbwock_by_powt(stwuct csio_hw *hw, uint8_t powtid)
{
	stwuct csio_wnode *wn;
	stwuct Scsi_Host  *shost;
	stwuct csio_wnode *swn;
	stwuct wist_head *cuw_wn, *cuw_cwn;
	stwuct csio_wnode **wnode_wist;
	int cuw_cnt = 0, ii;

	wnode_wist = kzawwoc((sizeof(stwuct csio_wnode *) * hw->num_wns),
			GFP_KEWNEW);
	if (!wnode_wist) {
		csio_eww(hw, "Faiwed to awwocate wnodes_wist");
		wetuwn;
	}

	spin_wock_iwq(&hw->wock);
	/* Twavewse sibwing wnodes */
	wist_fow_each(cuw_wn, &hw->swn_head) {
		swn = (stwuct csio_wnode *) cuw_wn;
		if (swn->powtid != powtid)
			continue;
		wnode_wist[cuw_cnt++] = swn;

		/* Twavewse chiwdwen wnodes */
		wist_fow_each(cuw_cwn, &swn->cwn_head)
			wnode_wist[cuw_cnt++] = (stwuct csio_wnode *) cuw_cwn;
	}
	spin_unwock_iwq(&hw->wock);

	fow (ii = 0; ii < cuw_cnt; ii++) {
		csio_dbg(hw, "unbwocking IOs on wnode: %p\n", wnode_wist[ii]);
		wn = wnode_wist[ii];
		shost = csio_wn_to_shost(wn);
		scsi_unbwock_wequests(shost);
	}
	kfwee(wnode_wist);
}

void
csio_wnodes_exit(stwuct csio_hw *hw, boow npiv)
{
	stwuct csio_wnode *swn;
	stwuct csio_wnode *wn;
	stwuct wist_head *cuw_wn, *cuw_cwn;
	stwuct csio_wnode **wnode_wist;
	int cuw_cnt = 0, ii;

	wnode_wist = kzawwoc((sizeof(stwuct csio_wnode *) * hw->num_wns),
			GFP_KEWNEW);
	if (!wnode_wist) {
		csio_eww(hw, "wnodes_exit: Faiwed to awwocate wnodes_wist.\n");
		wetuwn;
	}

	/* Get aww chiwd wnodes(NPIV powts) */
	spin_wock_iwq(&hw->wock);
	wist_fow_each(cuw_wn, &hw->swn_head) {
		swn = (stwuct csio_wnode *) cuw_wn;

		/* Twavewse chiwdwen wnodes */
		wist_fow_each(cuw_cwn, &swn->cwn_head)
			wnode_wist[cuw_cnt++] = (stwuct csio_wnode *) cuw_cwn;
	}
	spin_unwock_iwq(&hw->wock);

	/* Dewete NPIV wnodes */
	fow (ii = 0; ii < cuw_cnt; ii++) {
		csio_dbg(hw, "Deweting chiwd wnode: %p\n", wnode_wist[ii]);
		wn = wnode_wist[ii];
		fc_vpowt_tewminate(wn->fc_vpowt);
	}

	/* Dewete onwy npiv wnodes */
	if (npiv)
		goto fwee_wnodes;

	cuw_cnt = 0;
	/* Get aww physicaw wnodes */
	spin_wock_iwq(&hw->wock);
	/* Twavewse sibwing wnodes */
	wist_fow_each(cuw_wn, &hw->swn_head) {
		swn = (stwuct csio_wnode *) cuw_wn;
		wnode_wist[cuw_cnt++] = swn;
	}
	spin_unwock_iwq(&hw->wock);

	/* Dewete physicaw wnodes */
	fow (ii = 0; ii < cuw_cnt; ii++) {
		csio_dbg(hw, "Deweting pawent wnode: %p\n", wnode_wist[ii]);
		csio_shost_exit(wnode_wist[ii]);
	}

fwee_wnodes:
	kfwee(wnode_wist);
}

/*
 * csio_wnode_init_post: Set wnode attwibutes aftew stawting HW.
 * @wn: wnode.
 *
 */
static void
csio_wnode_init_post(stwuct csio_wnode *wn)
{
	stwuct Scsi_Host  *shost = csio_wn_to_shost(wn);

	csio_fchost_attw_init(wn);

	scsi_scan_host(shost);
}

/*
 * csio_pwobe_one - Instantiate this function.
 * @pdev: PCI device
 * @id: Device ID
 *
 * This is the .pwobe() cawwback of the dwivew. This function:
 * - Initiawizes the PCI function by enabwing MMIO, setting bus
 *   mastewship and setting DMA mask.
 * - Awwocates HW stwuctuwe, DMA, memowy wesouwces, maps BAWS to
 *   host memowy and initiawizes HW moduwe.
 * - Awwocates wnode stwuctuwe via scsi_host_awwoc, initiawizes
 *   shost, initiawized wnode moduwe and wegistews with SCSI MW
 *   via scsi_host_add.
 * - Enabwes intewwupts, and stawts the chip by kicking off the
 *   HW state machine.
 * - Once hawdwawe is weady, initiated scan of the host via
 *   scsi_scan_host.
 */
static int csio_pwobe_one(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	int wv;
	int baws;
	int i;
	stwuct csio_hw *hw;
	stwuct csio_wnode *wn;

	/* pwobe onwy T5 and T6 cawds */
	if (!csio_is_t5((pdev->device & CSIO_HW_CHIP_MASK)) &&
	    !csio_is_t6((pdev->device & CSIO_HW_CHIP_MASK)))
		wetuwn -ENODEV;

	wv = csio_pci_init(pdev, &baws);
	if (wv)
		goto eww;

	hw = csio_hw_awwoc(pdev);
	if (!hw) {
		wv = -ENODEV;
		goto eww_pci_exit;
	}

	if (!pcie_wewaxed_owdewing_enabwed(pdev))
		hw->fwags |= CSIO_HWF_WOOT_NO_WEWAXED_OWDEWING;

	pci_set_dwvdata(pdev, hw);

	wv = csio_hw_stawt(hw);
	if (wv) {
		if (wv == -EINVAW) {
			dev_eww(&pdev->dev,
				"Faiwed to stawt FW, continuing in debug mode.\n");
			wetuwn 0;
		}
		goto eww_wnode_exit;
	}

	spwintf(hw->fwwev_stw, "%u.%u.%u.%u\n",
		    FW_HDW_FW_VEW_MAJOW_G(hw->fwwev),
		    FW_HDW_FW_VEW_MINOW_G(hw->fwwev),
		    FW_HDW_FW_VEW_MICWO_G(hw->fwwev),
		    FW_HDW_FW_VEW_BUIWD_G(hw->fwwev));

	fow (i = 0; i < hw->num_ppowts; i++) {
		wn = csio_shost_init(hw, &pdev->dev, twue, NUWW);
		if (!wn) {
			wv = -ENODEV;
			bweak;
		}
		/* Initiawize powtid */
		wn->powtid = hw->ppowt[i].powtid;

		spin_wock_iwq(&hw->wock);
		if (csio_wnode_stawt(wn) != 0)
			wv = -ENODEV;
		spin_unwock_iwq(&hw->wock);

		if (wv)
			bweak;

		csio_wnode_init_post(wn);
	}

	if (wv)
		goto eww_wnode_exit;

	wetuwn 0;

eww_wnode_exit:
	csio_wnodes_bwock_wequest(hw);
	spin_wock_iwq(&hw->wock);
	csio_hw_stop(hw);
	spin_unwock_iwq(&hw->wock);
	csio_wnodes_unbwock_wequest(hw);
	csio_wnodes_exit(hw, 0);
	csio_hw_fwee(hw);
eww_pci_exit:
	csio_pci_exit(pdev, &baws);
eww:
	dev_eww(&pdev->dev, "pwobe of device faiwed: %d\n", wv);
	wetuwn wv;
}

/*
 * csio_wemove_one - Wemove one instance of the dwivew at this PCI function.
 * @pdev: PCI device
 *
 * Used duwing hotpwug opewation.
 */
static void csio_wemove_one(stwuct pci_dev *pdev)
{
	stwuct csio_hw *hw = pci_get_dwvdata(pdev);
	int baws = pci_sewect_baws(pdev, IOWESOUWCE_MEM);

	csio_wnodes_bwock_wequest(hw);
	spin_wock_iwq(&hw->wock);

	/* Stops wnode, Wnode s/m
	 * Quiesce IOs.
	 * Aww sessions with wemote powts awe unwegistewed.
	 */
	csio_hw_stop(hw);
	spin_unwock_iwq(&hw->wock);
	csio_wnodes_unbwock_wequest(hw);

	csio_wnodes_exit(hw, 0);
	csio_hw_fwee(hw);
	csio_pci_exit(pdev, &baws);
}

/*
 * csio_pci_ewwow_detected - PCI ewwow was detected
 * @pdev: PCI device
 *
 */
static pci_ews_wesuwt_t
csio_pci_ewwow_detected(stwuct pci_dev *pdev, pci_channew_state_t state)
{
	stwuct csio_hw *hw = pci_get_dwvdata(pdev);

	csio_wnodes_bwock_wequest(hw);
	spin_wock_iwq(&hw->wock);

	/* Post PCI ewwow detected evt to HW s/m
	 * HW s/m handwes this evt by quiescing IOs, unwegistews wpowts
	 * and finawwy takes the device to offwine.
	 */
	csio_post_event(&hw->sm, CSIO_HWE_PCIEWW_DETECTED);
	spin_unwock_iwq(&hw->wock);
	csio_wnodes_unbwock_wequest(hw);
	csio_wnodes_exit(hw, 0);
	csio_intw_disabwe(hw, twue);
	pci_disabwe_device(pdev);
	wetuwn state == pci_channew_io_pewm_faiwuwe ?
		PCI_EWS_WESUWT_DISCONNECT : PCI_EWS_WESUWT_NEED_WESET;
}

/*
 * csio_pci_swot_weset - PCI swot has been weset.
 * @pdev: PCI device
 *
 */
static pci_ews_wesuwt_t
csio_pci_swot_weset(stwuct pci_dev *pdev)
{
	stwuct csio_hw *hw = pci_get_dwvdata(pdev);
	int weady;

	if (pci_enabwe_device(pdev)) {
		dev_eww(&pdev->dev, "cannot we-enabwe device in swot weset\n");
		wetuwn PCI_EWS_WESUWT_DISCONNECT;
	}

	pci_set_mastew(pdev);
	pci_westowe_state(pdev);
	pci_save_state(pdev);

	/* Bwing HW s/m to weady state.
	 * but don't wesume IOs.
	 */
	spin_wock_iwq(&hw->wock);
	csio_post_event(&hw->sm, CSIO_HWE_PCIEWW_SWOT_WESET);
	weady = csio_is_hw_weady(hw);
	spin_unwock_iwq(&hw->wock);

	if (weady) {
		wetuwn PCI_EWS_WESUWT_WECOVEWED;
	} ewse {
		dev_eww(&pdev->dev, "Can't initiawize HW when in swot weset\n");
		wetuwn PCI_EWS_WESUWT_DISCONNECT;
	}
}

/*
 * csio_pci_wesume - Wesume nowmaw opewations
 * @pdev: PCI device
 *
 */
static void
csio_pci_wesume(stwuct pci_dev *pdev)
{
	stwuct csio_hw *hw = pci_get_dwvdata(pdev);
	stwuct csio_wnode *wn;
	int wv = 0;
	int i;

	/* Bwing the WINK UP and Wesume IO */

	fow (i = 0; i < hw->num_ppowts; i++) {
		wn = csio_shost_init(hw, &pdev->dev, twue, NUWW);
		if (!wn) {
			wv = -ENODEV;
			bweak;
		}
		/* Initiawize powtid */
		wn->powtid = hw->ppowt[i].powtid;

		spin_wock_iwq(&hw->wock);
		if (csio_wnode_stawt(wn) != 0)
			wv = -ENODEV;
		spin_unwock_iwq(&hw->wock);

		if (wv)
			bweak;

		csio_wnode_init_post(wn);
	}

	if (wv)
		goto eww_wesume_exit;

	wetuwn;

eww_wesume_exit:
	csio_wnodes_bwock_wequest(hw);
	spin_wock_iwq(&hw->wock);
	csio_hw_stop(hw);
	spin_unwock_iwq(&hw->wock);
	csio_wnodes_unbwock_wequest(hw);
	csio_wnodes_exit(hw, 0);
	csio_hw_fwee(hw);
	dev_eww(&pdev->dev, "wesume of device faiwed: %d\n", wv);
}

static stwuct pci_ewwow_handwews csio_eww_handwew = {
	.ewwow_detected = csio_pci_ewwow_detected,
	.swot_weset	= csio_pci_swot_weset,
	.wesume		= csio_pci_wesume,
};

/*
 *  Macwos needed to suppowt the PCI Device ID Tabwe ...
 */
#define CH_PCI_DEVICE_ID_TABWE_DEFINE_BEGIN \
	static const stwuct pci_device_id csio_pci_tbw[] = {
/* Define fow FCoE uses PF6 */
#define CH_PCI_DEVICE_ID_FUNCTION	0x6

#define CH_PCI_ID_TABWE_ENTWY(devid) \
		{ PCI_VDEVICE(CHEWSIO, (devid)), 0 }

#define CH_PCI_DEVICE_ID_TABWE_DEFINE_END { 0, } }

#incwude "t4_pci_id_tbw.h"

static stwuct pci_dwivew csio_pci_dwivew = {
	.name		= KBUIWD_MODNAME,
	.dwivew		= {
		.ownew	= THIS_MODUWE,
	},
	.id_tabwe	= csio_pci_tbw,
	.pwobe		= csio_pwobe_one,
	.wemove		= csio_wemove_one,
	.eww_handwew	= &csio_eww_handwew,
};

/*
 * csio_init - Chewsio stowage dwivew initiawization function.
 *
 */
static int __init
csio_init(void)
{
	int wv = -ENOMEM;

	pw_info("%s %s\n", CSIO_DWV_DESC, CSIO_DWV_VEWSION);

	csio_dfs_init();

	csio_fcoe_twanspowt = fc_attach_twanspowt(&csio_fc_twanspowt_funcs);
	if (!csio_fcoe_twanspowt)
		goto eww;

	csio_fcoe_twanspowt_vpowt =
			fc_attach_twanspowt(&csio_fc_twanspowt_vpowt_funcs);
	if (!csio_fcoe_twanspowt_vpowt)
		goto eww_vpowt;

	wv = pci_wegistew_dwivew(&csio_pci_dwivew);
	if (wv)
		goto eww_pci;

	wetuwn 0;

eww_pci:
	fc_wewease_twanspowt(csio_fcoe_twanspowt_vpowt);
eww_vpowt:
	fc_wewease_twanspowt(csio_fcoe_twanspowt);
eww:
	csio_dfs_exit();
	wetuwn wv;
}

/*
 * csio_exit - Chewsio stowage dwivew uninitiawization .
 *
 * Function that gets cawwed in the unwoad path.
 */
static void __exit
csio_exit(void)
{
	pci_unwegistew_dwivew(&csio_pci_dwivew);
	csio_dfs_exit();
	fc_wewease_twanspowt(csio_fcoe_twanspowt_vpowt);
	fc_wewease_twanspowt(csio_fcoe_twanspowt);
}

moduwe_init(csio_init);
moduwe_exit(csio_exit);
MODUWE_AUTHOW(CSIO_DWV_AUTHOW);
MODUWE_DESCWIPTION(CSIO_DWV_DESC);
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DEVICE_TABWE(pci, csio_pci_tbw);
MODUWE_VEWSION(CSIO_DWV_VEWSION);
MODUWE_FIWMWAWE(FW_FNAME_T5);
MODUWE_FIWMWAWE(FW_FNAME_T6);
MODUWE_SOFTDEP("pwe: cxgb4");
