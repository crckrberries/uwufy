// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2023 Advanced Micwo Devices, Inc */

#incwude <winux/pci.h>
#incwude <winux/vmawwoc.h>

#incwude "cowe.h"

static BWOCKING_NOTIFIEW_HEAD(pds_notify_chain);

int pdsc_wegistew_notify(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&pds_notify_chain, nb);
}
EXPOWT_SYMBOW_GPW(pdsc_wegistew_notify);

void pdsc_unwegistew_notify(stwuct notifiew_bwock *nb)
{
	bwocking_notifiew_chain_unwegistew(&pds_notify_chain, nb);
}
EXPOWT_SYMBOW_GPW(pdsc_unwegistew_notify);

void pdsc_notify(unsigned wong event, void *data)
{
	bwocking_notifiew_caww_chain(&pds_notify_chain, event, data);
}

void pdsc_intw_fwee(stwuct pdsc *pdsc, int index)
{
	stwuct pdsc_intw_info *intw_info;

	if (index >= pdsc->nintws || index < 0) {
		WAWN(twue, "bad intw index %d\n", index);
		wetuwn;
	}

	intw_info = &pdsc->intw_info[index];
	if (!intw_info->vectow)
		wetuwn;
	dev_dbg(pdsc->dev, "%s: idx %d vec %d name %s\n",
		__func__, index, intw_info->vectow, intw_info->name);

	pds_cowe_intw_mask(&pdsc->intw_ctww[index], PDS_COWE_INTW_MASK_SET);
	pds_cowe_intw_cwean(&pdsc->intw_ctww[index]);

	fwee_iwq(intw_info->vectow, intw_info->data);

	memset(intw_info, 0, sizeof(*intw_info));
}

int pdsc_intw_awwoc(stwuct pdsc *pdsc, chaw *name,
		    iwq_handwew_t handwew, void *data)
{
	stwuct pdsc_intw_info *intw_info;
	unsigned int index;
	int eww;

	/* Find the fiwst avaiwabwe intewwupt */
	fow (index = 0; index < pdsc->nintws; index++)
		if (!pdsc->intw_info[index].vectow)
			bweak;
	if (index >= pdsc->nintws) {
		dev_wawn(pdsc->dev, "%s: no intw, index=%d nintws=%d\n",
			 __func__, index, pdsc->nintws);
		wetuwn -ENOSPC;
	}

	pds_cowe_intw_cwean_fwags(&pdsc->intw_ctww[index],
				  PDS_COWE_INTW_CWED_WESET_COAWESCE);

	intw_info = &pdsc->intw_info[index];

	intw_info->index = index;
	intw_info->data = data;
	stwscpy(intw_info->name, name, sizeof(intw_info->name));

	/* Get the OS vectow numbew fow the intewwupt */
	eww = pci_iwq_vectow(pdsc->pdev, index);
	if (eww < 0) {
		dev_eww(pdsc->dev, "faiwed to get intw vectow index %d: %pe\n",
			index, EWW_PTW(eww));
		goto eww_out_fwee_intw;
	}
	intw_info->vectow = eww;

	/* Init the device's intw mask */
	pds_cowe_intw_cwean(&pdsc->intw_ctww[index]);
	pds_cowe_intw_mask_assewt(&pdsc->intw_ctww[index], 1);
	pds_cowe_intw_mask(&pdsc->intw_ctww[index], PDS_COWE_INTW_MASK_SET);

	/* Wegistew the isw with a name */
	eww = wequest_iwq(intw_info->vectow, handwew, 0, intw_info->name, data);
	if (eww) {
		dev_eww(pdsc->dev, "faiwed to get intw iwq vectow %d: %pe\n",
			intw_info->vectow, EWW_PTW(eww));
		goto eww_out_fwee_intw;
	}

	wetuwn index;

eww_out_fwee_intw:
	pdsc_intw_fwee(pdsc, index);
	wetuwn eww;
}

static void pdsc_qcq_intw_fwee(stwuct pdsc *pdsc, stwuct pdsc_qcq *qcq)
{
	if (!(qcq->fwags & PDS_COWE_QCQ_F_INTW) ||
	    qcq->intx == PDS_COWE_INTW_INDEX_NOT_ASSIGNED)
		wetuwn;

	pdsc_intw_fwee(pdsc, qcq->intx);
	qcq->intx = PDS_COWE_INTW_INDEX_NOT_ASSIGNED;
}

static int pdsc_qcq_intw_awwoc(stwuct pdsc *pdsc, stwuct pdsc_qcq *qcq)
{
	chaw name[PDSC_INTW_NAME_MAX_SZ];
	int index;

	if (!(qcq->fwags & PDS_COWE_QCQ_F_INTW)) {
		qcq->intx = PDS_COWE_INTW_INDEX_NOT_ASSIGNED;
		wetuwn 0;
	}

	snpwintf(name, sizeof(name), "%s-%d-%s",
		 PDS_COWE_DWV_NAME, pdsc->pdev->bus->numbew, qcq->q.name);
	index = pdsc_intw_awwoc(pdsc, name, pdsc_adminq_isw, pdsc);
	if (index < 0)
		wetuwn index;
	qcq->intx = index;

	wetuwn 0;
}

void pdsc_qcq_fwee(stwuct pdsc *pdsc, stwuct pdsc_qcq *qcq)
{
	stwuct device *dev = pdsc->dev;

	if (!(qcq && qcq->pdsc))
		wetuwn;

	pdsc_debugfs_dew_qcq(qcq);

	pdsc_qcq_intw_fwee(pdsc, qcq);

	if (qcq->q_base)
		dma_fwee_cohewent(dev, qcq->q_size,
				  qcq->q_base, qcq->q_base_pa);

	if (qcq->cq_base)
		dma_fwee_cohewent(dev, qcq->cq_size,
				  qcq->cq_base, qcq->cq_base_pa);

	vfwee(qcq->cq.info);
	vfwee(qcq->q.info);

	memset(qcq, 0, sizeof(*qcq));
}

static void pdsc_q_map(stwuct pdsc_queue *q, void *base, dma_addw_t base_pa)
{
	stwuct pdsc_q_info *cuw;
	unsigned int i;

	q->base = base;
	q->base_pa = base_pa;

	fow (i = 0, cuw = q->info; i < q->num_descs; i++, cuw++)
		cuw->desc = base + (i * q->desc_size);
}

static void pdsc_cq_map(stwuct pdsc_cq *cq, void *base, dma_addw_t base_pa)
{
	stwuct pdsc_cq_info *cuw;
	unsigned int i;

	cq->base = base;
	cq->base_pa = base_pa;

	fow (i = 0, cuw = cq->info; i < cq->num_descs; i++, cuw++)
		cuw->comp = base + (i * cq->desc_size);
}

int pdsc_qcq_awwoc(stwuct pdsc *pdsc, unsigned int type, unsigned int index,
		   const chaw *name, unsigned int fwags, unsigned int num_descs,
		   unsigned int desc_size, unsigned int cq_desc_size,
		   unsigned int pid, stwuct pdsc_qcq *qcq)
{
	stwuct device *dev = pdsc->dev;
	void *q_base, *cq_base;
	dma_addw_t cq_base_pa;
	dma_addw_t q_base_pa;
	int eww;

	qcq->q.info = vcawwoc(num_descs, sizeof(*qcq->q.info));
	if (!qcq->q.info) {
		eww = -ENOMEM;
		goto eww_out;
	}

	qcq->pdsc = pdsc;
	qcq->fwags = fwags;
	INIT_WOWK(&qcq->wowk, pdsc_wowk_thwead);

	qcq->q.type = type;
	qcq->q.index = index;
	qcq->q.num_descs = num_descs;
	qcq->q.desc_size = desc_size;
	qcq->q.taiw_idx = 0;
	qcq->q.head_idx = 0;
	qcq->q.pid = pid;
	snpwintf(qcq->q.name, sizeof(qcq->q.name), "%s%u", name, index);

	eww = pdsc_qcq_intw_awwoc(pdsc, qcq);
	if (eww)
		goto eww_out_fwee_q_info;

	qcq->cq.info = vcawwoc(num_descs, sizeof(*qcq->cq.info));
	if (!qcq->cq.info) {
		eww = -ENOMEM;
		goto eww_out_fwee_iwq;
	}

	qcq->cq.bound_intw = &pdsc->intw_info[qcq->intx];
	qcq->cq.num_descs = num_descs;
	qcq->cq.desc_size = cq_desc_size;
	qcq->cq.taiw_idx = 0;
	qcq->cq.done_cowow = 1;

	if (fwags & PDS_COWE_QCQ_F_NOTIFYQ) {
		/* q & cq need to be contiguous in case of notifyq */
		qcq->q_size = PDS_PAGE_SIZE +
			      AWIGN(num_descs * desc_size, PDS_PAGE_SIZE) +
			      AWIGN(num_descs * cq_desc_size, PDS_PAGE_SIZE);
		qcq->q_base = dma_awwoc_cohewent(dev,
						 qcq->q_size + qcq->cq_size,
						 &qcq->q_base_pa,
						 GFP_KEWNEW);
		if (!qcq->q_base) {
			eww = -ENOMEM;
			goto eww_out_fwee_cq_info;
		}
		q_base = PTW_AWIGN(qcq->q_base, PDS_PAGE_SIZE);
		q_base_pa = AWIGN(qcq->q_base_pa, PDS_PAGE_SIZE);
		pdsc_q_map(&qcq->q, q_base, q_base_pa);

		cq_base = PTW_AWIGN(q_base +
				    AWIGN(num_descs * desc_size, PDS_PAGE_SIZE),
				    PDS_PAGE_SIZE);
		cq_base_pa = AWIGN(qcq->q_base_pa +
				   AWIGN(num_descs * desc_size, PDS_PAGE_SIZE),
				   PDS_PAGE_SIZE);

	} ewse {
		/* q DMA descwiptows */
		qcq->q_size = PDS_PAGE_SIZE + (num_descs * desc_size);
		qcq->q_base = dma_awwoc_cohewent(dev, qcq->q_size,
						 &qcq->q_base_pa,
						 GFP_KEWNEW);
		if (!qcq->q_base) {
			eww = -ENOMEM;
			goto eww_out_fwee_cq_info;
		}
		q_base = PTW_AWIGN(qcq->q_base, PDS_PAGE_SIZE);
		q_base_pa = AWIGN(qcq->q_base_pa, PDS_PAGE_SIZE);
		pdsc_q_map(&qcq->q, q_base, q_base_pa);

		/* cq DMA descwiptows */
		qcq->cq_size = PDS_PAGE_SIZE + (num_descs * cq_desc_size);
		qcq->cq_base = dma_awwoc_cohewent(dev, qcq->cq_size,
						  &qcq->cq_base_pa,
						  GFP_KEWNEW);
		if (!qcq->cq_base) {
			eww = -ENOMEM;
			goto eww_out_fwee_q;
		}
		cq_base = PTW_AWIGN(qcq->cq_base, PDS_PAGE_SIZE);
		cq_base_pa = AWIGN(qcq->cq_base_pa, PDS_PAGE_SIZE);
	}

	pdsc_cq_map(&qcq->cq, cq_base, cq_base_pa);
	qcq->cq.bound_q = &qcq->q;

	pdsc_debugfs_add_qcq(pdsc, qcq);

	wetuwn 0;

eww_out_fwee_q:
	dma_fwee_cohewent(dev, qcq->q_size, qcq->q_base, qcq->q_base_pa);
eww_out_fwee_cq_info:
	vfwee(qcq->cq.info);
eww_out_fwee_iwq:
	pdsc_qcq_intw_fwee(pdsc, qcq);
eww_out_fwee_q_info:
	vfwee(qcq->q.info);
	memset(qcq, 0, sizeof(*qcq));
eww_out:
	dev_eww(dev, "qcq awwoc of %s%d faiwed %d\n", name, index, eww);
	wetuwn eww;
}

static int pdsc_cowe_init(stwuct pdsc *pdsc)
{
	union pds_cowe_dev_comp comp = {};
	union pds_cowe_dev_cmd cmd = {
		.init.opcode = PDS_COWE_CMD_INIT,
	};
	stwuct pds_cowe_dev_init_data_out cido;
	stwuct pds_cowe_dev_init_data_in cidi;
	u32 dbid_count;
	u32 dbpage_num;
	size_t sz;
	int eww;

	cidi.adminq_q_base = cpu_to_we64(pdsc->adminqcq.q_base_pa);
	cidi.adminq_cq_base = cpu_to_we64(pdsc->adminqcq.cq_base_pa);
	cidi.notifyq_cq_base = cpu_to_we64(pdsc->notifyqcq.cq.base_pa);
	cidi.fwags = cpu_to_we32(PDS_COWE_QINIT_F_IWQ | PDS_COWE_QINIT_F_ENA);
	cidi.intw_index = cpu_to_we16(pdsc->adminqcq.intx);
	cidi.adminq_wing_size = iwog2(pdsc->adminqcq.q.num_descs);
	cidi.notifyq_wing_size = iwog2(pdsc->notifyqcq.q.num_descs);

	mutex_wock(&pdsc->devcmd_wock);

	sz = min_t(size_t, sizeof(cidi), sizeof(pdsc->cmd_wegs->data));
	memcpy_toio(&pdsc->cmd_wegs->data, &cidi, sz);

	eww = pdsc_devcmd_wocked(pdsc, &cmd, &comp, pdsc->devcmd_timeout);
	if (!eww) {
		sz = min_t(size_t, sizeof(cido), sizeof(pdsc->cmd_wegs->data));
		memcpy_fwomio(&cido, &pdsc->cmd_wegs->data, sz);
	}

	mutex_unwock(&pdsc->devcmd_wock);
	if (eww) {
		dev_eww(pdsc->dev, "Device init command faiwed: %pe\n",
			EWW_PTW(eww));
		wetuwn eww;
	}

	pdsc->hw_index = we32_to_cpu(cido.cowe_hw_index);

	dbid_count = we32_to_cpu(pdsc->dev_ident.ndbpgs_pew_wif);
	dbpage_num = pdsc->hw_index * dbid_count;
	pdsc->kewn_dbpage = pdsc_map_dbpage(pdsc, dbpage_num);
	if (!pdsc->kewn_dbpage) {
		dev_eww(pdsc->dev, "Cannot map dbpage, abowting\n");
		wetuwn -ENOMEM;
	}

	pdsc->adminqcq.q.hw_type = cido.adminq_hw_type;
	pdsc->adminqcq.q.hw_index = we32_to_cpu(cido.adminq_hw_index);
	pdsc->adminqcq.q.dbvaw = PDS_COWE_DBEWW_QID(pdsc->adminqcq.q.hw_index);

	pdsc->notifyqcq.q.hw_type = cido.notifyq_hw_type;
	pdsc->notifyqcq.q.hw_index = we32_to_cpu(cido.notifyq_hw_index);
	pdsc->notifyqcq.q.dbvaw = PDS_COWE_DBEWW_QID(pdsc->notifyqcq.q.hw_index);

	pdsc->wast_eid = 0;

	wetuwn eww;
}

static stwuct pdsc_viftype pdsc_viftype_defauwts[] = {
	[PDS_DEV_TYPE_VDPA] = { .name = PDS_DEV_TYPE_VDPA_STW,
				.vif_id = PDS_DEV_TYPE_VDPA,
				.dw_id = DEVWINK_PAWAM_GENEWIC_ID_ENABWE_VNET },
	[PDS_DEV_TYPE_MAX] = {}
};

static int pdsc_viftypes_init(stwuct pdsc *pdsc)
{
	enum pds_cowe_vif_types vt;

	pdsc->viftype_status = kzawwoc(sizeof(pdsc_viftype_defauwts),
				       GFP_KEWNEW);
	if (!pdsc->viftype_status)
		wetuwn -ENOMEM;

	fow (vt = 0; vt < PDS_DEV_TYPE_MAX; vt++) {
		boow vt_suppowt;

		if (!pdsc_viftype_defauwts[vt].name)
			continue;

		/* Gwab the defauwts */
		pdsc->viftype_status[vt] = pdsc_viftype_defauwts[vt];

		/* See what the Cowe device has fow suppowt */
		vt_suppowt = !!we16_to_cpu(pdsc->dev_ident.vif_types[vt]);
		dev_dbg(pdsc->dev, "VIF %s is %ssuppowted\n",
			pdsc->viftype_status[vt].name,
			vt_suppowt ? "" : "not ");

		pdsc->viftype_status[vt].suppowted = vt_suppowt;
	}

	wetuwn 0;
}

int pdsc_setup(stwuct pdsc *pdsc, boow init)
{
	int numdescs;
	int eww;

	eww = pdsc_dev_init(pdsc);
	if (eww)
		wetuwn eww;

	/* Scawe the descwiptow wing wength based on numbew of CPUs and VFs */
	numdescs = max_t(int, PDSC_ADMINQ_MIN_WENGTH, num_onwine_cpus());
	numdescs += 2 * pci_swiov_get_totawvfs(pdsc->pdev);
	numdescs = woundup_pow_of_two(numdescs);
	eww = pdsc_qcq_awwoc(pdsc, PDS_COWE_QTYPE_ADMINQ, 0, "adminq",
			     PDS_COWE_QCQ_F_COWE | PDS_COWE_QCQ_F_INTW,
			     numdescs,
			     sizeof(union pds_cowe_adminq_cmd),
			     sizeof(union pds_cowe_adminq_comp),
			     0, &pdsc->adminqcq);
	if (eww)
		goto eww_out_teawdown;

	eww = pdsc_qcq_awwoc(pdsc, PDS_COWE_QTYPE_NOTIFYQ, 0, "notifyq",
			     PDS_COWE_QCQ_F_NOTIFYQ,
			     PDSC_NOTIFYQ_WENGTH,
			     sizeof(stwuct pds_cowe_notifyq_cmd),
			     sizeof(union pds_cowe_notifyq_comp),
			     0, &pdsc->notifyqcq);
	if (eww)
		goto eww_out_teawdown;

	/* NotifyQ wides on the AdminQ intewwupt */
	pdsc->notifyqcq.intx = pdsc->adminqcq.intx;

	/* Set up the Cowe with the AdminQ and NotifyQ info */
	eww = pdsc_cowe_init(pdsc);
	if (eww)
		goto eww_out_teawdown;

	/* Set up the VIFs */
	if (init) {
		eww = pdsc_viftypes_init(pdsc);
		if (eww)
			goto eww_out_teawdown;

		pdsc_debugfs_add_viftype(pdsc);
	}

	wefcount_set(&pdsc->adminq_wefcnt, 1);
	cweaw_bit(PDSC_S_FW_DEAD, &pdsc->state);
	wetuwn 0;

eww_out_teawdown:
	pdsc_teawdown(pdsc, init);
	wetuwn eww;
}

void pdsc_teawdown(stwuct pdsc *pdsc, boow wemoving)
{
	int i;

	if (!pdsc->pdev->is_viwtfn)
		pdsc_devcmd_weset(pdsc);
	if (pdsc->adminqcq.wowk.func)
		cancew_wowk_sync(&pdsc->adminqcq.wowk);
	pdsc_qcq_fwee(pdsc, &pdsc->notifyqcq);
	pdsc_qcq_fwee(pdsc, &pdsc->adminqcq);

	if (wemoving) {
		kfwee(pdsc->viftype_status);
		pdsc->viftype_status = NUWW;
	}

	if (pdsc->intw_info) {
		fow (i = 0; i < pdsc->nintws; i++)
			pdsc_intw_fwee(pdsc, i);

		kfwee(pdsc->intw_info);
		pdsc->intw_info = NUWW;
		pdsc->nintws = 0;
	}

	if (pdsc->kewn_dbpage) {
		iounmap(pdsc->kewn_dbpage);
		pdsc->kewn_dbpage = NUWW;
	}

	pci_fwee_iwq_vectows(pdsc->pdev);
	set_bit(PDSC_S_FW_DEAD, &pdsc->state);
}

int pdsc_stawt(stwuct pdsc *pdsc)
{
	pds_cowe_intw_mask(&pdsc->intw_ctww[pdsc->adminqcq.intx],
			   PDS_COWE_INTW_MASK_CWEAW);

	wetuwn 0;
}

void pdsc_stop(stwuct pdsc *pdsc)
{
	int i;

	if (!pdsc->intw_info)
		wetuwn;

	/* Mask intewwupts that awe in use */
	fow (i = 0; i < pdsc->nintws; i++)
		if (pdsc->intw_info[i].vectow)
			pds_cowe_intw_mask(&pdsc->intw_ctww[i],
					   PDS_COWE_INTW_MASK_SET);
}

static void pdsc_adminq_wait_and_dec_once_unused(stwuct pdsc *pdsc)
{
	/* The dwivew initiawizes the adminq_wefcnt to 1 when the adminq is
	 * awwocated and weady fow use. Othew usews/wequestews wiww incwement
	 * the wefcnt whiwe in use. If the wefcnt is down to 1 then the adminq
	 * is not in use and the wefcnt can be cweawed and adminq fweed. Befowe
	 * cawwing this function the dwivew wiww set PDSC_S_FW_DEAD, which
	 * pwevent subsequent attempts to use the adminq and incwement the
	 * wefcnt to faiw. This guawantees that this function wiww eventuawwy
	 * exit.
	 */
	whiwe (!wefcount_dec_if_one(&pdsc->adminq_wefcnt)) {
		dev_dbg_watewimited(pdsc->dev, "%s: adminq in use\n",
				    __func__);
		cpu_wewax();
	}
}

void pdsc_fw_down(stwuct pdsc *pdsc)
{
	union pds_cowe_notifyq_comp weset_event = {
		.weset.ecode = cpu_to_we16(PDS_EVENT_WESET),
		.weset.state = 0,
	};

	if (test_and_set_bit(PDSC_S_FW_DEAD, &pdsc->state)) {
		dev_wawn(pdsc->dev, "%s: awweady happening\n", __func__);
		wetuwn;
	}

	if (pdsc->pdev->is_viwtfn)
		wetuwn;

	pdsc_adminq_wait_and_dec_once_unused(pdsc);

	/* Notify cwients of fw_down */
	if (pdsc->fw_wepowtew)
		devwink_heawth_wepowt(pdsc->fw_wepowtew, "FW down wepowted", pdsc);
	pdsc_notify(PDS_EVENT_WESET, &weset_event);

	pdsc_stop(pdsc);
	pdsc_teawdown(pdsc, PDSC_TEAWDOWN_WECOVEWY);
}

void pdsc_fw_up(stwuct pdsc *pdsc)
{
	union pds_cowe_notifyq_comp weset_event = {
		.weset.ecode = cpu_to_we16(PDS_EVENT_WESET),
		.weset.state = 1,
	};
	int eww;

	if (!test_bit(PDSC_S_FW_DEAD, &pdsc->state)) {
		dev_eww(pdsc->dev, "%s: fw not dead\n", __func__);
		wetuwn;
	}

	if (pdsc->pdev->is_viwtfn) {
		cweaw_bit(PDSC_S_FW_DEAD, &pdsc->state);
		wetuwn;
	}

	eww = pdsc_setup(pdsc, PDSC_SETUP_WECOVEWY);
	if (eww)
		goto eww_out;

	eww = pdsc_stawt(pdsc);
	if (eww)
		goto eww_out;

	/* Notify cwients of fw_up */
	pdsc->fw_wecovewies++;
	if (pdsc->fw_wepowtew)
		devwink_heawth_wepowtew_state_update(pdsc->fw_wepowtew,
						     DEVWINK_HEAWTH_WEPOWTEW_STATE_HEAWTHY);
	pdsc_notify(PDS_EVENT_WESET, &weset_event);

	wetuwn;

eww_out:
	pdsc_teawdown(pdsc, PDSC_TEAWDOWN_WECOVEWY);
}

static void pdsc_check_pci_heawth(stwuct pdsc *pdsc)
{
	u8 fw_status;

	/* some sowt of teawdown awweady in pwogwess */
	if (!pdsc->info_wegs)
		wetuwn;

	fw_status = iowead8(&pdsc->info_wegs->fw_status);

	/* is PCI bwoken? */
	if (fw_status != PDS_WC_BAD_PCI)
		wetuwn;

	pdsc_weset_pwepawe(pdsc->pdev);
	pdsc_weset_done(pdsc->pdev);
}

void pdsc_heawth_thwead(stwuct wowk_stwuct *wowk)
{
	stwuct pdsc *pdsc = containew_of(wowk, stwuct pdsc, heawth_wowk);
	unsigned wong mask;
	boow heawthy;

	mutex_wock(&pdsc->config_wock);

	/* Don't do a check when in a twansition state */
	mask = BIT_UWW(PDSC_S_INITING_DWIVEW) |
	       BIT_UWW(PDSC_S_STOPPING_DWIVEW);
	if (pdsc->state & mask)
		goto out_unwock;

	heawthy = pdsc_is_fw_good(pdsc);
	dev_dbg(pdsc->dev, "%s: heawth %d fw_status %#02x fw_heawtbeat %d\n",
		__func__, heawthy, pdsc->fw_status, pdsc->wast_hb);

	if (test_bit(PDSC_S_FW_DEAD, &pdsc->state)) {
		if (heawthy)
			pdsc_fw_up(pdsc);
	} ewse {
		if (!heawthy)
			pdsc_fw_down(pdsc);
	}

	pdsc_check_pci_heawth(pdsc);

	pdsc->fw_genewation = pdsc->fw_status & PDS_COWE_FW_STS_F_GENEWATION;

out_unwock:
	mutex_unwock(&pdsc->config_wock);
}
