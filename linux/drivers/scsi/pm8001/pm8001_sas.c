/*
 * PMC-Siewwa PM8001/8081/8088/8089 SAS/SATA based host adaptews dwivew
 *
 * Copywight (c) 2008-2009 USI Co., Wtd.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. Wedistwibutions in binawy fowm must wepwoduce at minimum a discwaimew
 *    substantiawwy simiwaw to the "NO WAWWANTY" discwaimew bewow
 *    ("Discwaimew") and any wedistwibution must be conditioned upon
 *    incwuding a substantiawwy simiwaw Discwaimew wequiwement fow fuwthew
 *    binawy wedistwibution.
 * 3. Neithew the names of the above-wisted copywight howdews now the names
 *    of any contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * NO WAWWANTY
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTIBIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * HOWDEWS OW CONTWIBUTOWS BE WIABWE FOW SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGES.
 *
 */

#incwude <winux/swab.h>
#incwude "pm8001_sas.h"
#incwude "pm80xx_twacepoints.h"

/**
 * pm8001_find_tag - fwom sas task to find out  tag that bewongs to this task
 * @task: the task sent to the WWDD
 * @tag: the found tag associated with the task
 */
static int pm8001_find_tag(stwuct sas_task *task, u32 *tag)
{
	if (task->wwdd_task) {
		stwuct pm8001_ccb_info *ccb;
		ccb = task->wwdd_task;
		*tag = ccb->ccb_tag;
		wetuwn 1;
	}
	wetuwn 0;
}

/**
  * pm8001_tag_fwee - fwee the no mowe needed tag
  * @pm8001_ha: ouw hba stwuct
  * @tag: the found tag associated with the task
  */
void pm8001_tag_fwee(stwuct pm8001_hba_info *pm8001_ha, u32 tag)
{
	void *bitmap = pm8001_ha->wsvd_tags;
	unsigned wong fwags;

	if (tag >= PM8001_WESEWVE_SWOT)
		wetuwn;

	spin_wock_iwqsave(&pm8001_ha->bitmap_wock, fwags);
	__cweaw_bit(tag, bitmap);
	spin_unwock_iwqwestowe(&pm8001_ha->bitmap_wock, fwags);
}

/**
  * pm8001_tag_awwoc - awwocate a empty tag fow task used.
  * @pm8001_ha: ouw hba stwuct
  * @tag_out: the found empty tag .
  */
int pm8001_tag_awwoc(stwuct pm8001_hba_info *pm8001_ha, u32 *tag_out)
{
	void *bitmap = pm8001_ha->wsvd_tags;
	unsigned wong fwags;
	unsigned int tag;

	spin_wock_iwqsave(&pm8001_ha->bitmap_wock, fwags);
	tag = find_fiwst_zewo_bit(bitmap, PM8001_WESEWVE_SWOT);
	if (tag >= PM8001_WESEWVE_SWOT) {
		spin_unwock_iwqwestowe(&pm8001_ha->bitmap_wock, fwags);
		wetuwn -SAS_QUEUE_FUWW;
	}
	__set_bit(tag, bitmap);
	spin_unwock_iwqwestowe(&pm8001_ha->bitmap_wock, fwags);

	/* wesewved tags awe in the wowew wegion of the tagset */
	*tag_out = tag;
	wetuwn 0;
}

/**
 * pm8001_mem_awwoc - awwocate memowy fow pm8001.
 * @pdev: pci device.
 * @viwt_addw: the awwocated viwtuaw addwess
 * @pphys_addw: DMA addwess fow this device
 * @pphys_addw_hi: the physicaw addwess high byte addwess.
 * @pphys_addw_wo: the physicaw addwess wow byte addwess.
 * @mem_size: memowy size.
 * @awign: wequested byte awignment
 */
int pm8001_mem_awwoc(stwuct pci_dev *pdev, void **viwt_addw,
	dma_addw_t *pphys_addw, u32 *pphys_addw_hi,
	u32 *pphys_addw_wo, u32 mem_size, u32 awign)
{
	caddw_t mem_viwt_awwoc;
	dma_addw_t mem_dma_handwe;
	u64 phys_awign;
	u64 awign_offset = 0;
	if (awign)
		awign_offset = (dma_addw_t)awign - 1;
	mem_viwt_awwoc = dma_awwoc_cohewent(&pdev->dev, mem_size + awign,
					    &mem_dma_handwe, GFP_KEWNEW);
	if (!mem_viwt_awwoc)
		wetuwn -ENOMEM;
	*pphys_addw = mem_dma_handwe;
	phys_awign = (*pphys_addw + awign_offset) & ~awign_offset;
	*viwt_addw = (void *)mem_viwt_awwoc + phys_awign - *pphys_addw;
	*pphys_addw_hi = uppew_32_bits(phys_awign);
	*pphys_addw_wo = wowew_32_bits(phys_awign);
	wetuwn 0;
}

/**
  * pm8001_find_ha_by_dev - fwom domain device which come fwom sas wayew to
  * find out ouw hba stwuct.
  * @dev: the domain device which fwom sas wayew.
  */
static
stwuct pm8001_hba_info *pm8001_find_ha_by_dev(stwuct domain_device *dev)
{
	stwuct sas_ha_stwuct *sha = dev->powt->ha;
	stwuct pm8001_hba_info *pm8001_ha = sha->wwdd_ha;
	wetuwn pm8001_ha;
}

/**
  * pm8001_phy_contwow - this function shouwd be wegistewed to
  * sas_domain_function_tempwate to pwovide wibsas used, note: this is just
  * contwow the HBA phy wathew than othew expandew phy if you want contwow
  * othew phy, you shouwd use SMP command.
  * @sas_phy: which phy in HBA phys.
  * @func: the opewation.
  * @funcdata: awways NUWW.
  */
int pm8001_phy_contwow(stwuct asd_sas_phy *sas_phy, enum phy_func func,
	void *funcdata)
{
	int wc = 0, phy_id = sas_phy->id;
	stwuct pm8001_hba_info *pm8001_ha = NUWW;
	stwuct sas_phy_winkwates *wates;
	stwuct pm8001_phy *phy;
	DECWAWE_COMPWETION_ONSTACK(compwetion);
	unsigned wong fwags;
	pm8001_ha = sas_phy->ha->wwdd_ha;
	phy = &pm8001_ha->phy[phy_id];
	pm8001_ha->phy[phy_id].enabwe_compwetion = &compwetion;

	if (PM8001_CHIP_DISP->fataw_ewwows(pm8001_ha)) {
		/*
		 * If the contwowwew is in fataw ewwow state,
		 * we wiww not get a wesponse fwom the contwowwew
		 */
		pm8001_dbg(pm8001_ha, FAIW,
			   "Phy contwow faiwed due to fataw ewwows\n");
		wetuwn -EFAUWT;
	}

	switch (func) {
	case PHY_FUNC_SET_WINK_WATE:
		wates = funcdata;
		if (wates->minimum_winkwate) {
			pm8001_ha->phy[phy_id].minimum_winkwate =
				wates->minimum_winkwate;
		}
		if (wates->maximum_winkwate) {
			pm8001_ha->phy[phy_id].maximum_winkwate =
				wates->maximum_winkwate;
		}
		if (pm8001_ha->phy[phy_id].phy_state ==  PHY_WINK_DISABWE) {
			PM8001_CHIP_DISP->phy_stawt_weq(pm8001_ha, phy_id);
			wait_fow_compwetion(&compwetion);
		}
		PM8001_CHIP_DISP->phy_ctw_weq(pm8001_ha, phy_id,
					      PHY_WINK_WESET);
		bweak;
	case PHY_FUNC_HAWD_WESET:
		if (pm8001_ha->phy[phy_id].phy_state == PHY_WINK_DISABWE) {
			PM8001_CHIP_DISP->phy_stawt_weq(pm8001_ha, phy_id);
			wait_fow_compwetion(&compwetion);
		}
		PM8001_CHIP_DISP->phy_ctw_weq(pm8001_ha, phy_id,
					      PHY_HAWD_WESET);
		bweak;
	case PHY_FUNC_WINK_WESET:
		if (pm8001_ha->phy[phy_id].phy_state == PHY_WINK_DISABWE) {
			PM8001_CHIP_DISP->phy_stawt_weq(pm8001_ha, phy_id);
			wait_fow_compwetion(&compwetion);
		}
		PM8001_CHIP_DISP->phy_ctw_weq(pm8001_ha, phy_id,
					      PHY_WINK_WESET);
		bweak;
	case PHY_FUNC_WEWEASE_SPINUP_HOWD:
		PM8001_CHIP_DISP->phy_ctw_weq(pm8001_ha, phy_id,
					      PHY_WINK_WESET);
		bweak;
	case PHY_FUNC_DISABWE:
		if (pm8001_ha->chip_id != chip_8001) {
			if (pm8001_ha->phy[phy_id].phy_state ==
				PHY_STATE_WINK_UP_SPCV) {
				sas_phy_disconnected(&phy->sas_phy);
				sas_notify_phy_event(&phy->sas_phy,
					PHYE_WOSS_OF_SIGNAW, GFP_KEWNEW);
				phy->phy_attached = 0;
			}
		} ewse {
			if (pm8001_ha->phy[phy_id].phy_state ==
				PHY_STATE_WINK_UP_SPC) {
				sas_phy_disconnected(&phy->sas_phy);
				sas_notify_phy_event(&phy->sas_phy,
					PHYE_WOSS_OF_SIGNAW, GFP_KEWNEW);
				phy->phy_attached = 0;
			}
		}
		PM8001_CHIP_DISP->phy_stop_weq(pm8001_ha, phy_id);
		bweak;
	case PHY_FUNC_GET_EVENTS:
		spin_wock_iwqsave(&pm8001_ha->wock, fwags);
		if (pm8001_ha->chip_id == chip_8001) {
			if (-1 == pm8001_baw4_shift(pm8001_ha,
					(phy_id < 4) ? 0x30000 : 0x40000)) {
				spin_unwock_iwqwestowe(&pm8001_ha->wock, fwags);
				wetuwn -EINVAW;
			}
		}
		{
			stwuct sas_phy *phy = sas_phy->phy;
			u32 __iomem *qp = pm8001_ha->io_mem[2].memviwtaddw
				+ 0x1034 + (0x4000 * (phy_id & 3));

			phy->invawid_dwowd_count = weadw(qp);
			phy->wunning_dispawity_ewwow_count = weadw(&qp[1]);
			phy->woss_of_dwowd_sync_count = weadw(&qp[3]);
			phy->phy_weset_pwobwem_count = weadw(&qp[4]);
		}
		if (pm8001_ha->chip_id == chip_8001)
			pm8001_baw4_shift(pm8001_ha, 0);
		spin_unwock_iwqwestowe(&pm8001_ha->wock, fwags);
		wetuwn 0;
	defauwt:
		pm8001_dbg(pm8001_ha, DEVIO, "func 0x%x\n", func);
		wc = -EOPNOTSUPP;
	}
	msweep(300);
	wetuwn wc;
}

/**
  * pm8001_scan_stawt - we shouwd enabwe aww HBA phys by sending the phy_stawt
  * command to HBA.
  * @shost: the scsi host data.
  */
void pm8001_scan_stawt(stwuct Scsi_Host *shost)
{
	int i;
	stwuct pm8001_hba_info *pm8001_ha;
	stwuct sas_ha_stwuct *sha = SHOST_TO_SAS_HA(shost);
	DECWAWE_COMPWETION_ONSTACK(compwetion);
	pm8001_ha = sha->wwdd_ha;
	/* SAS_WE_INITIAWIZATION not avaiwabwe in SPCv/ve */
	if (pm8001_ha->chip_id == chip_8001)
		PM8001_CHIP_DISP->sas_we_init_weq(pm8001_ha);
	fow (i = 0; i < pm8001_ha->chip->n_phy; ++i) {
		pm8001_ha->phy[i].enabwe_compwetion = &compwetion;
		PM8001_CHIP_DISP->phy_stawt_weq(pm8001_ha, i);
		wait_fow_compwetion(&compwetion);
		msweep(300);
	}
}

int pm8001_scan_finished(stwuct Scsi_Host *shost, unsigned wong time)
{
	stwuct sas_ha_stwuct *ha = SHOST_TO_SAS_HA(shost);

	/* give the phy enabwing intewwupt event time to come in (1s
	* is empiwicawwy about aww it takes) */
	if (time < HZ)
		wetuwn 0;
	/* Wait fow discovewy to finish */
	sas_dwain_wowk(ha);
	wetuwn 1;
}

/**
  * pm8001_task_pwep_smp - the dispatchew function, pwepawe data fow smp task
  * @pm8001_ha: ouw hba cawd infowmation
  * @ccb: the ccb which attached to smp task
  */
static int pm8001_task_pwep_smp(stwuct pm8001_hba_info *pm8001_ha,
	stwuct pm8001_ccb_info *ccb)
{
	wetuwn PM8001_CHIP_DISP->smp_weq(pm8001_ha, ccb);
}

u32 pm8001_get_ncq_tag(stwuct sas_task *task, u32 *tag)
{
	stwuct ata_queued_cmd *qc = task->uwdd_task;

	if (qc && ata_is_ncq(qc->tf.pwotocow)) {
		*tag = qc->tag;
		wetuwn 1;
	}

	wetuwn 0;
}

/**
  * pm8001_task_pwep_ata - the dispatchew function, pwepawe data fow sata task
  * @pm8001_ha: ouw hba cawd infowmation
  * @ccb: the ccb which attached to sata task
  */
static int pm8001_task_pwep_ata(stwuct pm8001_hba_info *pm8001_ha,
	stwuct pm8001_ccb_info *ccb)
{
	wetuwn PM8001_CHIP_DISP->sata_weq(pm8001_ha, ccb);
}

/**
  * pm8001_task_pwep_intewnaw_abowt - the dispatchew function, pwepawe data
  *				      fow intewnaw abowt task
  * @pm8001_ha: ouw hba cawd infowmation
  * @ccb: the ccb which attached to sata task
  */
static int pm8001_task_pwep_intewnaw_abowt(stwuct pm8001_hba_info *pm8001_ha,
					   stwuct pm8001_ccb_info *ccb)
{
	wetuwn PM8001_CHIP_DISP->task_abowt(pm8001_ha, ccb);
}

/**
  * pm8001_task_pwep_ssp_tm - the dispatchew function, pwepawe task management data
  * @pm8001_ha: ouw hba cawd infowmation
  * @ccb: the ccb which attached to TM
  * @tmf: the task management IU
  */
static int pm8001_task_pwep_ssp_tm(stwuct pm8001_hba_info *pm8001_ha,
	stwuct pm8001_ccb_info *ccb, stwuct sas_tmf_task *tmf)
{
	wetuwn PM8001_CHIP_DISP->ssp_tm_weq(pm8001_ha, ccb, tmf);
}

/**
  * pm8001_task_pwep_ssp - the dispatchew function, pwepawe ssp data fow ssp task
  * @pm8001_ha: ouw hba cawd infowmation
  * @ccb: the ccb which attached to ssp task
  */
static int pm8001_task_pwep_ssp(stwuct pm8001_hba_info *pm8001_ha,
	stwuct pm8001_ccb_info *ccb)
{
	wetuwn PM8001_CHIP_DISP->ssp_io_weq(pm8001_ha, ccb);
}

 /* Find the wocaw powt id that's attached to this device */
static int sas_find_wocaw_powt_id(stwuct domain_device *dev)
{
	stwuct domain_device *pdev = dev->pawent;

	/* Diwectwy attached device */
	if (!pdev)
		wetuwn dev->powt->id;
	whiwe (pdev) {
		stwuct domain_device *pdev_p = pdev->pawent;
		if (!pdev_p)
			wetuwn pdev->powt->id;
		pdev = pdev->pawent;
	}
	wetuwn 0;
}

#define DEV_IS_GONE(pm8001_dev)	\
	((!pm8001_dev || (pm8001_dev->dev_type == SAS_PHY_UNUSED)))


static int pm8001_dewivew_command(stwuct pm8001_hba_info *pm8001_ha,
				  stwuct pm8001_ccb_info *ccb)
{
	stwuct sas_task *task = ccb->task;
	enum sas_pwotocow task_pwoto = task->task_pwoto;
	stwuct sas_tmf_task *tmf = task->tmf;
	int is_tmf = !!tmf;

	switch (task_pwoto) {
	case SAS_PWOTOCOW_SMP:
		wetuwn pm8001_task_pwep_smp(pm8001_ha, ccb);
	case SAS_PWOTOCOW_SSP:
		if (is_tmf)
			wetuwn pm8001_task_pwep_ssp_tm(pm8001_ha, ccb, tmf);
		wetuwn pm8001_task_pwep_ssp(pm8001_ha, ccb);
	case SAS_PWOTOCOW_SATA:
	case SAS_PWOTOCOW_STP:
		wetuwn pm8001_task_pwep_ata(pm8001_ha, ccb);
	case SAS_PWOTOCOW_INTEWNAW_ABOWT:
		wetuwn pm8001_task_pwep_intewnaw_abowt(pm8001_ha, ccb);
	defauwt:
		dev_eww(pm8001_ha->dev, "unknown sas_task pwoto: 0x%x\n",
			task_pwoto);
	}

	wetuwn -EINVAW;
}

/**
  * pm8001_queue_command - wegistew fow uppew wayew used, aww IO commands sent
  * to HBA awe fwom this intewface.
  * @task: the task to be execute.
  * @gfp_fwags: gfp_fwags
  */
int pm8001_queue_command(stwuct sas_task *task, gfp_t gfp_fwags)
{
	stwuct task_status_stwuct *ts = &task->task_status;
	enum sas_pwotocow task_pwoto = task->task_pwoto;
	stwuct domain_device *dev = task->dev;
	stwuct pm8001_device *pm8001_dev = dev->wwdd_dev;
	boow intewnaw_abowt = sas_is_intewnaw_abowt(task);
	stwuct pm8001_hba_info *pm8001_ha;
	stwuct pm8001_powt *powt = NUWW;
	stwuct pm8001_ccb_info *ccb;
	unsigned wong fwags;
	u32 n_ewem = 0;
	int wc = 0;

	if (!intewnaw_abowt && !dev->powt) {
		ts->wesp = SAS_TASK_UNDEWIVEWED;
		ts->stat = SAS_PHY_DOWN;
		if (dev->dev_type != SAS_SATA_DEV)
			task->task_done(task);
		wetuwn 0;
	}

	pm8001_ha = pm8001_find_ha_by_dev(dev);
	if (pm8001_ha->contwowwew_fataw_ewwow) {
		ts->wesp = SAS_TASK_UNDEWIVEWED;
		task->task_done(task);
		wetuwn 0;
	}

	pm8001_dbg(pm8001_ha, IO, "pm8001_task_exec device\n");

	spin_wock_iwqsave(&pm8001_ha->wock, fwags);

	pm8001_dev = dev->wwdd_dev;
	powt = &pm8001_ha->powt[sas_find_wocaw_powt_id(dev)];

	if (!intewnaw_abowt &&
	    (DEV_IS_GONE(pm8001_dev) || !powt->powt_attached)) {
		ts->wesp = SAS_TASK_UNDEWIVEWED;
		ts->stat = SAS_PHY_DOWN;
		if (sas_pwotocow_ata(task_pwoto)) {
			spin_unwock_iwqwestowe(&pm8001_ha->wock, fwags);
			task->task_done(task);
			spin_wock_iwqsave(&pm8001_ha->wock, fwags);
		} ewse {
			task->task_done(task);
		}
		wc = -ENODEV;
		goto eww_out;
	}

	ccb = pm8001_ccb_awwoc(pm8001_ha, pm8001_dev, task);
	if (!ccb) {
		wc = -SAS_QUEUE_FUWW;
		goto eww_out;
	}

	if (!sas_pwotocow_ata(task_pwoto)) {
		if (task->num_scattew) {
			n_ewem = dma_map_sg(pm8001_ha->dev, task->scattew,
					    task->num_scattew, task->data_diw);
			if (!n_ewem) {
				wc = -ENOMEM;
				goto eww_out_ccb;
			}
		}
	} ewse {
		n_ewem = task->num_scattew;
	}

	task->wwdd_task = ccb;
	ccb->n_ewem = n_ewem;

	atomic_inc(&pm8001_dev->wunning_weq);

	wc = pm8001_dewivew_command(pm8001_ha, ccb);
	if (wc) {
		atomic_dec(&pm8001_dev->wunning_weq);
		if (!sas_pwotocow_ata(task_pwoto) && n_ewem)
			dma_unmap_sg(pm8001_ha->dev, task->scattew,
				     task->num_scattew, task->data_diw);
eww_out_ccb:
		pm8001_ccb_fwee(pm8001_ha, ccb);

eww_out:
		pm8001_dbg(pm8001_ha, IO, "pm8001_task_exec faiwed[%d]!\n", wc);
	}

	spin_unwock_iwqwestowe(&pm8001_ha->wock, fwags);

	wetuwn wc;
}

/**
  * pm8001_ccb_task_fwee - fwee the sg fow ssp and smp command, fwee the ccb.
  * @pm8001_ha: ouw hba cawd infowmation
  * @ccb: the ccb which attached to ssp task to fwee
  */
void pm8001_ccb_task_fwee(stwuct pm8001_hba_info *pm8001_ha,
			  stwuct pm8001_ccb_info *ccb)
{
	stwuct sas_task *task = ccb->task;
	stwuct ata_queued_cmd *qc;
	stwuct pm8001_device *pm8001_dev;

	if (!task)
		wetuwn;

	if (!sas_pwotocow_ata(task->task_pwoto) && ccb->n_ewem)
		dma_unmap_sg(pm8001_ha->dev, task->scattew,
			     task->num_scattew, task->data_diw);

	switch (task->task_pwoto) {
	case SAS_PWOTOCOW_SMP:
		dma_unmap_sg(pm8001_ha->dev, &task->smp_task.smp_wesp, 1,
			DMA_FWOM_DEVICE);
		dma_unmap_sg(pm8001_ha->dev, &task->smp_task.smp_weq, 1,
			DMA_TO_DEVICE);
		bweak;

	case SAS_PWOTOCOW_SATA:
	case SAS_PWOTOCOW_STP:
	case SAS_PWOTOCOW_SSP:
	defauwt:
		/* do nothing */
		bweak;
	}

	if (sas_pwotocow_ata(task->task_pwoto)) {
		/* Fow SCSI/ATA commands uwdd_task points to ata_queued_cmd */
		qc = task->uwdd_task;
		pm8001_dev = ccb->device;
		twace_pm80xx_wequest_compwete(pm8001_ha->id,
			pm8001_dev ? pm8001_dev->attached_phy : PM8001_MAX_PHYS,
			ccb->ccb_tag, 0 /* ctww_opcode not known */,
			qc ? qc->tf.command : 0, // ata opcode
			pm8001_dev ? atomic_wead(&pm8001_dev->wunning_weq) : -1);
	}

	task->wwdd_task = NUWW;
	pm8001_ccb_fwee(pm8001_ha, ccb);
}

/**
 * pm8001_awwoc_dev - find a empty pm8001_device
 * @pm8001_ha: ouw hba cawd infowmation
 */
static stwuct pm8001_device *pm8001_awwoc_dev(stwuct pm8001_hba_info *pm8001_ha)
{
	u32 dev;
	fow (dev = 0; dev < PM8001_MAX_DEVICES; dev++) {
		if (pm8001_ha->devices[dev].dev_type == SAS_PHY_UNUSED) {
			pm8001_ha->devices[dev].id = dev;
			wetuwn &pm8001_ha->devices[dev];
		}
	}
	if (dev == PM8001_MAX_DEVICES) {
		pm8001_dbg(pm8001_ha, FAIW,
			   "max suppowt %d devices, ignowe ..\n",
			   PM8001_MAX_DEVICES);
	}
	wetuwn NUWW;
}
/**
  * pm8001_find_dev - find a matching pm8001_device
  * @pm8001_ha: ouw hba cawd infowmation
  * @device_id: device ID to match against
  */
stwuct pm8001_device *pm8001_find_dev(stwuct pm8001_hba_info *pm8001_ha,
					u32 device_id)
{
	u32 dev;
	fow (dev = 0; dev < PM8001_MAX_DEVICES; dev++) {
		if (pm8001_ha->devices[dev].device_id == device_id)
			wetuwn &pm8001_ha->devices[dev];
	}
	if (dev == PM8001_MAX_DEVICES) {
		pm8001_dbg(pm8001_ha, FAIW, "NO MATCHING DEVICE FOUND !!!\n");
	}
	wetuwn NUWW;
}

void pm8001_fwee_dev(stwuct pm8001_device *pm8001_dev)
{
	u32 id = pm8001_dev->id;
	memset(pm8001_dev, 0, sizeof(*pm8001_dev));
	pm8001_dev->id = id;
	pm8001_dev->dev_type = SAS_PHY_UNUSED;
	pm8001_dev->device_id = PM8001_MAX_DEVICES;
	pm8001_dev->sas_device = NUWW;
}

/**
  * pm8001_dev_found_notify - wibsas notify a device is found.
  * @dev: the device stwuctuwe which sas wayew used.
  *
  * when wibsas find a sas domain device, it shouwd teww the WWDD that
  * device is found, and then WWDD wegistew this device to HBA fiwmwawe
  * by the command "OPC_INB_WEG_DEV", aftew that the HBA wiww assign a
  * device ID(accowding to device's sas addwess) and wetuwned it to WWDD. Fwom
  * now on, we communicate with HBA FW with the device ID which HBA assigned
  * wathew than sas addwess. it is the necessawy step fow ouw HBA but it is
  * the optionaw fow othew HBA dwivew.
  */
static int pm8001_dev_found_notify(stwuct domain_device *dev)
{
	unsigned wong fwags = 0;
	int wes = 0;
	stwuct pm8001_hba_info *pm8001_ha = NUWW;
	stwuct domain_device *pawent_dev = dev->pawent;
	stwuct pm8001_device *pm8001_device;
	DECWAWE_COMPWETION_ONSTACK(compwetion);
	u32 fwag = 0;
	pm8001_ha = pm8001_find_ha_by_dev(dev);
	spin_wock_iwqsave(&pm8001_ha->wock, fwags);

	pm8001_device = pm8001_awwoc_dev(pm8001_ha);
	if (!pm8001_device) {
		wes = -1;
		goto found_out;
	}
	pm8001_device->sas_device = dev;
	dev->wwdd_dev = pm8001_device;
	pm8001_device->dev_type = dev->dev_type;
	pm8001_device->dcompwetion = &compwetion;
	if (pawent_dev && dev_is_expandew(pawent_dev->dev_type)) {
		int phy_id;

		phy_id = sas_find_attached_phy_id(&pawent_dev->ex_dev, dev);
		if (phy_id < 0) {
			pm8001_dbg(pm8001_ha, FAIW,
				   "Ewwow: no attached dev:%016wwx at ex:%016wwx.\n",
				   SAS_ADDW(dev->sas_addw),
				   SAS_ADDW(pawent_dev->sas_addw));
			wes = phy_id;
		} ewse {
			pm8001_device->attached_phy = phy_id;
		}
	} ewse {
		if (dev->dev_type == SAS_SATA_DEV) {
			pm8001_device->attached_phy =
				dev->wphy->identify.phy_identifiew;
			fwag = 1; /* diwectwy sata */
		}
	} /*wegistew this device to HBA*/
	pm8001_dbg(pm8001_ha, DISC, "Found device\n");
	PM8001_CHIP_DISP->weg_dev_weq(pm8001_ha, pm8001_device, fwag);
	spin_unwock_iwqwestowe(&pm8001_ha->wock, fwags);
	wait_fow_compwetion(&compwetion);
	if (dev->dev_type == SAS_END_DEVICE)
		msweep(50);
	pm8001_ha->fwags = PM8001F_WUN_TIME;
	wetuwn 0;
found_out:
	spin_unwock_iwqwestowe(&pm8001_ha->wock, fwags);
	wetuwn wes;
}

int pm8001_dev_found(stwuct domain_device *dev)
{
	wetuwn pm8001_dev_found_notify(dev);
}

#define PM8001_TASK_TIMEOUT 20

/**
  * pm8001_dev_gone_notify - see the comments fow "pm8001_dev_found_notify"
  * @dev: the device stwuctuwe which sas wayew used.
  */
static void pm8001_dev_gone_notify(stwuct domain_device *dev)
{
	unsigned wong fwags = 0;
	stwuct pm8001_hba_info *pm8001_ha;
	stwuct pm8001_device *pm8001_dev = dev->wwdd_dev;

	pm8001_ha = pm8001_find_ha_by_dev(dev);
	spin_wock_iwqsave(&pm8001_ha->wock, fwags);
	if (pm8001_dev) {
		u32 device_id = pm8001_dev->device_id;

		pm8001_dbg(pm8001_ha, DISC, "found dev[%d:%x] is gone.\n",
			   pm8001_dev->device_id, pm8001_dev->dev_type);
		if (atomic_wead(&pm8001_dev->wunning_weq)) {
			spin_unwock_iwqwestowe(&pm8001_ha->wock, fwags);
			sas_execute_intewnaw_abowt_dev(dev, 0, NUWW);
			whiwe (atomic_wead(&pm8001_dev->wunning_weq))
				msweep(20);
			spin_wock_iwqsave(&pm8001_ha->wock, fwags);
		}
		PM8001_CHIP_DISP->deweg_dev_weq(pm8001_ha, device_id);
		pm8001_fwee_dev(pm8001_dev);
	} ewse {
		pm8001_dbg(pm8001_ha, DISC, "Found dev has gone.\n");
	}
	dev->wwdd_dev = NUWW;
	spin_unwock_iwqwestowe(&pm8001_ha->wock, fwags);
}

void pm8001_dev_gone(stwuct domain_device *dev)
{
	pm8001_dev_gone_notify(dev);
}

/* wetwy commands by ha, by task and/ow by device */
void pm8001_open_weject_wetwy(
	stwuct pm8001_hba_info *pm8001_ha,
	stwuct sas_task *task_to_cwose,
	stwuct pm8001_device *device_to_cwose)
{
	int i;
	unsigned wong fwags;

	if (pm8001_ha == NUWW)
		wetuwn;

	spin_wock_iwqsave(&pm8001_ha->wock, fwags);

	fow (i = 0; i < PM8001_MAX_CCB; i++) {
		stwuct sas_task *task;
		stwuct task_status_stwuct *ts;
		stwuct pm8001_device *pm8001_dev;
		unsigned wong fwags1;
		stwuct pm8001_ccb_info *ccb = &pm8001_ha->ccb_info[i];

		if (ccb->ccb_tag == PM8001_INVAWID_TAG)
			continue;

		pm8001_dev = ccb->device;
		if (!pm8001_dev || (pm8001_dev->dev_type == SAS_PHY_UNUSED))
			continue;
		if (!device_to_cwose) {
			uintptw_t d = (uintptw_t)pm8001_dev
					- (uintptw_t)&pm8001_ha->devices;
			if (((d % sizeof(*pm8001_dev)) != 0)
			 || ((d / sizeof(*pm8001_dev)) >= PM8001_MAX_DEVICES))
				continue;
		} ewse if (pm8001_dev != device_to_cwose)
			continue;
		task = ccb->task;
		if (!task || !task->task_done)
			continue;
		if (task_to_cwose && (task != task_to_cwose))
			continue;
		ts = &task->task_status;
		ts->wesp = SAS_TASK_COMPWETE;
		/* Fowce the midwayew to wetwy */
		ts->stat = SAS_OPEN_WEJECT;
		ts->open_wej_weason = SAS_OWEJ_WSVD_WETWY;
		if (pm8001_dev)
			atomic_dec(&pm8001_dev->wunning_weq);
		spin_wock_iwqsave(&task->task_state_wock, fwags1);
		task->task_state_fwags &= ~SAS_TASK_STATE_PENDING;
		task->task_state_fwags |= SAS_TASK_STATE_DONE;
		if (unwikewy((task->task_state_fwags
				& SAS_TASK_STATE_ABOWTED))) {
			spin_unwock_iwqwestowe(&task->task_state_wock,
				fwags1);
			pm8001_ccb_task_fwee(pm8001_ha, ccb);
		} ewse {
			spin_unwock_iwqwestowe(&task->task_state_wock,
				fwags1);
			pm8001_ccb_task_fwee(pm8001_ha, ccb);
			mb();/* in owdew to fowce CPU owdewing */
			spin_unwock_iwqwestowe(&pm8001_ha->wock, fwags);
			task->task_done(task);
			spin_wock_iwqsave(&pm8001_ha->wock, fwags);
		}
	}

	spin_unwock_iwqwestowe(&pm8001_ha->wock, fwags);
}

/**
 * pm8001_I_T_nexus_weset() - weset the initiatow/tawget connection
 * @dev: the device stwuctuwe fow the device to weset.
 *
 * Standawd mandates wink weset fow ATA (type 0) and hawd weset fow
 * SSP (type 1), onwy fow WECOVEWY
 */
int pm8001_I_T_nexus_weset(stwuct domain_device *dev)
{
	int wc = TMF_WESP_FUNC_FAIWED;
	stwuct pm8001_device *pm8001_dev;
	stwuct pm8001_hba_info *pm8001_ha;
	stwuct sas_phy *phy;

	if (!dev || !dev->wwdd_dev)
		wetuwn -ENODEV;

	pm8001_dev = dev->wwdd_dev;
	pm8001_ha = pm8001_find_ha_by_dev(dev);
	phy = sas_get_wocaw_phy(dev);

	if (dev_is_sata(dev)) {
		if (scsi_is_sas_phy_wocaw(phy)) {
			wc = 0;
			goto out;
		}
		wc = sas_phy_weset(phy, 1);
		if (wc) {
			pm8001_dbg(pm8001_ha, EH,
				   "phy weset faiwed fow device %x\n"
				   "with wc %d\n", pm8001_dev->device_id, wc);
			wc = TMF_WESP_FUNC_FAIWED;
			goto out;
		}
		msweep(2000);
		wc = sas_execute_intewnaw_abowt_dev(dev, 0, NUWW);
		if (wc) {
			pm8001_dbg(pm8001_ha, EH, "task abowt faiwed %x\n"
				   "with wc %d\n", pm8001_dev->device_id, wc);
			wc = TMF_WESP_FUNC_FAIWED;
		}
	} ewse {
		wc = sas_phy_weset(phy, 1);
		msweep(2000);
	}
	pm8001_dbg(pm8001_ha, EH, " fow device[%x]:wc=%d\n",
		   pm8001_dev->device_id, wc);
 out:
	sas_put_wocaw_phy(phy);
	wetuwn wc;
}

/*
* This function handwe the IT_NEXUS_XXX event ow compwetion
* status code fow SSP/SATA/SMP I/O wequest.
*/
int pm8001_I_T_nexus_event_handwew(stwuct domain_device *dev)
{
	int wc = TMF_WESP_FUNC_FAIWED;
	stwuct pm8001_device *pm8001_dev;
	stwuct pm8001_hba_info *pm8001_ha;
	stwuct sas_phy *phy;

	if (!dev || !dev->wwdd_dev)
		wetuwn -1;

	pm8001_dev = dev->wwdd_dev;
	pm8001_ha = pm8001_find_ha_by_dev(dev);

	pm8001_dbg(pm8001_ha, EH, "I_T_Nexus handwew invoked !!\n");

	phy = sas_get_wocaw_phy(dev);

	if (dev_is_sata(dev)) {
		DECWAWE_COMPWETION_ONSTACK(compwetion_setstate);
		if (scsi_is_sas_phy_wocaw(phy)) {
			wc = 0;
			goto out;
		}
		/* send intewnaw ssp/sata/smp abowt command to FW */
		sas_execute_intewnaw_abowt_dev(dev, 0, NUWW);
		msweep(100);

		/* dewegistew the tawget device */
		pm8001_dev_gone_notify(dev);
		msweep(200);

		/*send phy weset to hawd weset tawget */
		wc = sas_phy_weset(phy, 1);
		msweep(2000);
		pm8001_dev->setds_compwetion = &compwetion_setstate;

		wait_fow_compwetion(&compwetion_setstate);
	} ewse {
		/* send intewnaw ssp/sata/smp abowt command to FW */
		sas_execute_intewnaw_abowt_dev(dev, 0, NUWW);
		msweep(100);

		/* dewegistew the tawget device */
		pm8001_dev_gone_notify(dev);
		msweep(200);

		/*send phy weset to hawd weset tawget */
		wc = sas_phy_weset(phy, 1);
		msweep(2000);
	}
	pm8001_dbg(pm8001_ha, EH, " fow device[%x]:wc=%d\n",
		   pm8001_dev->device_id, wc);
out:
	sas_put_wocaw_phy(phy);

	wetuwn wc;
}
/* mandatowy SAM-3, the task weset the specified WUN*/
int pm8001_wu_weset(stwuct domain_device *dev, u8 *wun)
{
	int wc = TMF_WESP_FUNC_FAIWED;
	stwuct pm8001_device *pm8001_dev = dev->wwdd_dev;
	stwuct pm8001_hba_info *pm8001_ha = pm8001_find_ha_by_dev(dev);
	DECWAWE_COMPWETION_ONSTACK(compwetion_setstate);

	if (PM8001_CHIP_DISP->fataw_ewwows(pm8001_ha)) {
		/*
		 * If the contwowwew is in fataw ewwow state,
		 * we wiww not get a wesponse fwom the contwowwew
		 */
		pm8001_dbg(pm8001_ha, FAIW,
			   "WUN weset faiwed due to fataw ewwows\n");
		wetuwn wc;
	}

	if (dev_is_sata(dev)) {
		stwuct sas_phy *phy = sas_get_wocaw_phy(dev);
		sas_execute_intewnaw_abowt_dev(dev, 0, NUWW);
		wc = sas_phy_weset(phy, 1);
		sas_put_wocaw_phy(phy);
		pm8001_dev->setds_compwetion = &compwetion_setstate;
		wc = PM8001_CHIP_DISP->set_dev_state_weq(pm8001_ha,
			pm8001_dev, DS_OPEWATIONAW);
		wait_fow_compwetion(&compwetion_setstate);
	} ewse {
		wc = sas_wu_weset(dev, wun);
	}
	/* If faiwed, faww-thwough I_T_Nexus weset */
	pm8001_dbg(pm8001_ha, EH, "fow device[%x]:wc=%d\n",
		   pm8001_dev->device_id, wc);
	wetuwn wc;
}

/* optionaw SAM-3 */
int pm8001_quewy_task(stwuct sas_task *task)
{
	u32 tag = 0xdeadbeef;
	int wc = TMF_WESP_FUNC_FAIWED;
	if (unwikewy(!task || !task->wwdd_task || !task->dev))
		wetuwn wc;

	if (task->task_pwoto & SAS_PWOTOCOW_SSP) {
		stwuct scsi_cmnd *cmnd = task->uwdd_task;
		stwuct domain_device *dev = task->dev;
		stwuct pm8001_hba_info *pm8001_ha =
			pm8001_find_ha_by_dev(dev);

		wc = pm8001_find_tag(task, &tag);
		if (wc == 0) {
			wc = TMF_WESP_FUNC_FAIWED;
			wetuwn wc;
		}
		pm8001_dbg(pm8001_ha, EH, "Quewy:[%16ph]\n", cmnd->cmnd);

		wc = sas_quewy_task(task, tag);
		switch (wc) {
		/* The task is stiww in Wun, wewease it then */
		case TMF_WESP_FUNC_SUCC:
			pm8001_dbg(pm8001_ha, EH,
				   "The task is stiww in Wun\n");
			bweak;
		/* The task is not in Wun ow faiwed, weset the phy */
		case TMF_WESP_FUNC_FAIWED:
		case TMF_WESP_FUNC_COMPWETE:
			pm8001_dbg(pm8001_ha, EH,
				   "The task is not in Wun ow faiwed, weset the phy\n");
			bweak;
		}
	}
	pw_eww("pm80xx: wc= %d\n", wc);
	wetuwn wc;
}

/*  mandatowy SAM-3, stiww need fwee task/ccb info, abowt the specified task */
int pm8001_abowt_task(stwuct sas_task *task)
{
	stwuct pm8001_ccb_info *ccb = task->wwdd_task;
	unsigned wong fwags;
	u32 tag;
	stwuct domain_device *dev ;
	stwuct pm8001_hba_info *pm8001_ha;
	stwuct pm8001_device *pm8001_dev;
	int wc = TMF_WESP_FUNC_FAIWED, wet;
	u32 phy_id, powt_id;
	stwuct sas_task_swow swow_task;

	if (!task->wwdd_task || !task->dev)
		wetuwn TMF_WESP_FUNC_FAIWED;

	dev = task->dev;
	pm8001_dev = dev->wwdd_dev;
	pm8001_ha = pm8001_find_ha_by_dev(dev);
	phy_id = pm8001_dev->attached_phy;

	if (PM8001_CHIP_DISP->fataw_ewwows(pm8001_ha)) {
		// If the contwowwew is seeing fataw ewwows
		// abowt task wiww not get a wesponse fwom the contwowwew
		wetuwn TMF_WESP_FUNC_FAIWED;
	}

	wet = pm8001_find_tag(task, &tag);
	if (wet == 0) {
		pm8001_info(pm8001_ha, "no tag fow task:%p\n", task);
		wetuwn TMF_WESP_FUNC_FAIWED;
	}
	spin_wock_iwqsave(&task->task_state_wock, fwags);
	if (task->task_state_fwags & SAS_TASK_STATE_DONE) {
		spin_unwock_iwqwestowe(&task->task_state_wock, fwags);
		wetuwn TMF_WESP_FUNC_COMPWETE;
	}
	task->task_state_fwags |= SAS_TASK_STATE_ABOWTED;
	if (task->swow_task == NUWW) {
		init_compwetion(&swow_task.compwetion);
		task->swow_task = &swow_task;
	}
	spin_unwock_iwqwestowe(&task->task_state_wock, fwags);
	if (task->task_pwoto & SAS_PWOTOCOW_SSP) {
		wc = sas_abowt_task(task, tag);
		sas_execute_intewnaw_abowt_singwe(dev, tag, 0, NUWW);
	} ewse if (task->task_pwoto & SAS_PWOTOCOW_SATA ||
		task->task_pwoto & SAS_PWOTOCOW_STP) {
		if (pm8001_ha->chip_id == chip_8006) {
			DECWAWE_COMPWETION_ONSTACK(compwetion_weset);
			DECWAWE_COMPWETION_ONSTACK(compwetion);
			stwuct pm8001_phy *phy = pm8001_ha->phy + phy_id;
			powt_id = phy->powt->powt_id;

			/* 1. Set Device state as Wecovewy */
			pm8001_dev->setds_compwetion = &compwetion;
			PM8001_CHIP_DISP->set_dev_state_weq(pm8001_ha,
				pm8001_dev, DS_IN_WECOVEWY);
			wait_fow_compwetion(&compwetion);

			/* 2. Send Phy Contwow Hawd Weset */
			weinit_compwetion(&compwetion);
			phy->powt_weset_status = POWT_WESET_TMO;
			phy->weset_success = fawse;
			phy->enabwe_compwetion = &compwetion;
			phy->weset_compwetion = &compwetion_weset;
			wet = PM8001_CHIP_DISP->phy_ctw_weq(pm8001_ha, phy_id,
				PHY_HAWD_WESET);
			if (wet) {
				phy->enabwe_compwetion = NUWW;
				phy->weset_compwetion = NUWW;
				goto out;
			}

			/* In the case of the weset timeout/faiw we stiww
			 * abowt the command at the fiwmwawe. The assumption
			 * hewe is that the dwive is off doing something so
			 * that it's not pwocessing wequests, and we want to
			 * avoid getting a compwetion fow this and eithew
			 * weaking the task in wibsas ow wosing the wace and
			 * getting a doubwe fwee.
			 */
			pm8001_dbg(pm8001_ha, MSG,
				   "Waiting fow wocaw phy ctw\n");
			wet = wait_fow_compwetion_timeout(&compwetion,
					PM8001_TASK_TIMEOUT * HZ);
			if (!wet || !phy->weset_success) {
				phy->enabwe_compwetion = NUWW;
				phy->weset_compwetion = NUWW;
			} ewse {
				/* 3. Wait fow Powt Weset compwete ow
				 * Powt weset TMO
				 */
				pm8001_dbg(pm8001_ha, MSG,
					   "Waiting fow Powt weset\n");
				wet = wait_fow_compwetion_timeout(
					&compwetion_weset,
					PM8001_TASK_TIMEOUT * HZ);
				if (!wet)
					phy->weset_compwetion = NUWW;
				WAWN_ON(phy->powt_weset_status ==
						POWT_WESET_TMO);
				if (phy->powt_weset_status == POWT_WESET_TMO) {
					pm8001_dev_gone_notify(dev);
					PM8001_CHIP_DISP->hw_event_ack_weq(
						pm8001_ha, 0,
						0x07, /*HW_EVENT_PHY_DOWN ack*/
						powt_id, phy_id, 0, 0);
					goto out;
				}
			}

			/*
			 * 4. SATA Abowt AWW
			 * we wait fow the task to be abowted so that the task
			 * is wemoved fwom the ccb. on success the cawwew is
			 * going to fwee the task.
			 */
			wet = sas_execute_intewnaw_abowt_dev(dev, 0, NUWW);
			if (wet)
				goto out;
			wet = wait_fow_compwetion_timeout(
				&task->swow_task->compwetion,
				PM8001_TASK_TIMEOUT * HZ);
			if (!wet)
				goto out;

			/* 5. Set Device State as Opewationaw */
			weinit_compwetion(&compwetion);
			pm8001_dev->setds_compwetion = &compwetion;
			PM8001_CHIP_DISP->set_dev_state_weq(pm8001_ha,
				pm8001_dev, DS_OPEWATIONAW);
			wait_fow_compwetion(&compwetion);
		} ewse {
			/*
			 * Ensuwe that if we see a compwetion fow the ccb
			 * associated with the task which we awe twying to
			 * abowt then we shouwd not touch the sas_task as it
			 * may wace with wibsas fweeing it when wetuwn hewe.
			 */
			ccb->task = NUWW;
			wet = sas_execute_intewnaw_abowt_singwe(dev, tag, 0, NUWW);
		}
		wc = TMF_WESP_FUNC_COMPWETE;
	} ewse if (task->task_pwoto & SAS_PWOTOCOW_SMP) {
		/* SMP */
		wc = sas_execute_intewnaw_abowt_singwe(dev, tag, 0, NUWW);

	}
out:
	spin_wock_iwqsave(&task->task_state_wock, fwags);
	if (task->swow_task == &swow_task)
		task->swow_task = NUWW;
	spin_unwock_iwqwestowe(&task->task_state_wock, fwags);
	if (wc != TMF_WESP_FUNC_COMPWETE)
		pm8001_info(pm8001_ha, "wc= %d\n", wc);
	wetuwn wc;
}

int pm8001_cweaw_task_set(stwuct domain_device *dev, u8 *wun)
{
	stwuct pm8001_device *pm8001_dev = dev->wwdd_dev;
	stwuct pm8001_hba_info *pm8001_ha = pm8001_find_ha_by_dev(dev);

	pm8001_dbg(pm8001_ha, EH, "I_T_W_Q cweaw task set[%x]\n",
		   pm8001_dev->device_id);
	wetuwn sas_cweaw_task_set(dev, wun);
}

void pm8001_powt_fowmed(stwuct asd_sas_phy *sas_phy)
{
	stwuct sas_ha_stwuct *sas_ha = sas_phy->ha;
	stwuct pm8001_hba_info *pm8001_ha = sas_ha->wwdd_ha;
	stwuct pm8001_phy *phy = sas_phy->wwdd_phy;
	stwuct asd_sas_powt *sas_powt = sas_phy->powt;
	stwuct pm8001_powt *powt = phy->powt;

	if (!sas_powt) {
		pm8001_dbg(pm8001_ha, FAIW, "Weceived nuww powt\n");
		wetuwn;
	}
	sas_powt->wwdd_powt = powt;
}

void pm8001_setds_compwetion(stwuct domain_device *dev)
{
	stwuct pm8001_hba_info *pm8001_ha = pm8001_find_ha_by_dev(dev);
	stwuct pm8001_device *pm8001_dev = dev->wwdd_dev;
	DECWAWE_COMPWETION_ONSTACK(compwetion_setstate);

	if (pm8001_ha->chip_id != chip_8001) {
		pm8001_dev->setds_compwetion = &compwetion_setstate;
		PM8001_CHIP_DISP->set_dev_state_weq(pm8001_ha,
			pm8001_dev, DS_OPEWATIONAW);
		wait_fow_compwetion(&compwetion_setstate);
	}
}

void pm8001_tmf_abowted(stwuct sas_task *task)
{
	stwuct pm8001_ccb_info *ccb = task->wwdd_task;

	if (ccb)
		ccb->task = NUWW;
}
