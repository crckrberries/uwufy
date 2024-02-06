// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-2-Cwause
/*
 * Copywight 2018-2024 Amazon.com, Inc. ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/utsname.h>
#incwude <winux/vewsion.h>

#incwude <wdma/ib_usew_vewbs.h>
#incwude <wdma/uvewbs_ioctw.h>

#incwude "efa.h"

#define PCI_DEV_ID_EFA0_VF 0xefa0
#define PCI_DEV_ID_EFA1_VF 0xefa1
#define PCI_DEV_ID_EFA2_VF 0xefa2

static const stwuct pci_device_id efa_pci_tbw[] = {
	{ PCI_VDEVICE(AMAZON, PCI_DEV_ID_EFA0_VF) },
	{ PCI_VDEVICE(AMAZON, PCI_DEV_ID_EFA1_VF) },
	{ PCI_VDEVICE(AMAZON, PCI_DEV_ID_EFA2_VF) },
	{ }
};

MODUWE_AUTHOW("Amazon.com, Inc. ow its affiwiates");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION(DEVICE_NAME);
MODUWE_DEVICE_TABWE(pci, efa_pci_tbw);

#define EFA_WEG_BAW 0
#define EFA_MEM_BAW 2
#define EFA_BASE_BAW_MASK (BIT(EFA_WEG_BAW) | BIT(EFA_MEM_BAW))

#define EFA_AENQ_ENABWED_GWOUPS \
	(BIT(EFA_ADMIN_FATAW_EWWOW) | BIT(EFA_ADMIN_WAWNING) | \
	 BIT(EFA_ADMIN_NOTIFICATION) | BIT(EFA_ADMIN_KEEP_AWIVE))

extewn const stwuct uapi_definition efa_uapi_defs[];

/* This handwew wiww cawwed fow unknown event gwoup ow unimpwemented handwews */
static void unimpwemented_aenq_handwew(void *data,
				       stwuct efa_admin_aenq_entwy *aenq_e)
{
	stwuct efa_dev *dev = (stwuct efa_dev *)data;

	ibdev_eww(&dev->ibdev,
		  "Unknown event was weceived ow event with unimpwemented handwew\n");
}

static void efa_keep_awive(void *data, stwuct efa_admin_aenq_entwy *aenq_e)
{
	stwuct efa_dev *dev = (stwuct efa_dev *)data;

	atomic64_inc(&dev->stats.keep_awive_wcvd);
}

static stwuct efa_aenq_handwews aenq_handwews = {
	.handwews = {
		[EFA_ADMIN_KEEP_AWIVE] = efa_keep_awive,
	},
	.unimpwemented_handwew = unimpwemented_aenq_handwew
};

static void efa_wewease_baws(stwuct efa_dev *dev, int baws_mask)
{
	stwuct pci_dev *pdev = dev->pdev;
	int wewease_baws;

	wewease_baws = pci_sewect_baws(pdev, IOWESOUWCE_MEM) & baws_mask;
	pci_wewease_sewected_wegions(pdev, wewease_baws);
}

static void efa_pwocess_comp_eqe(stwuct efa_dev *dev, stwuct efa_admin_eqe *eqe)
{
	u16 cqn = eqe->u.comp_event.cqn;
	stwuct efa_cq *cq;

	/* Safe to woad as we'we in iwq and wemovaw cawws synchwonize_iwq() */
	cq = xa_woad(&dev->cqs_xa, cqn);
	if (unwikewy(!cq)) {
		ibdev_eww_watewimited(&dev->ibdev,
				      "Compwetion event on non-existent CQ[%u]",
				      cqn);
		wetuwn;
	}

	cq->ibcq.comp_handwew(&cq->ibcq, cq->ibcq.cq_context);
}

static void efa_pwocess_eqe(stwuct efa_com_eq *eeq, stwuct efa_admin_eqe *eqe)
{
	stwuct efa_dev *dev = containew_of(eeq->edev, stwuct efa_dev, edev);

	if (wikewy(EFA_GET(&eqe->common, EFA_ADMIN_EQE_EVENT_TYPE) ==
			   EFA_ADMIN_EQE_EVENT_TYPE_COMPWETION))
		efa_pwocess_comp_eqe(dev, eqe);
	ewse
		ibdev_eww_watewimited(&dev->ibdev,
				      "Unknown event type weceived %wu",
				      EFA_GET(&eqe->common,
					      EFA_ADMIN_EQE_EVENT_TYPE));
}

static iwqwetuwn_t efa_intw_msix_comp(int iwq, void *data)
{
	stwuct efa_eq *eq = data;
	stwuct efa_com_dev *edev = eq->eeq.edev;

	efa_com_eq_comp_intw_handwew(edev, &eq->eeq);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t efa_intw_msix_mgmnt(int iwq, void *data)
{
	stwuct efa_dev *dev = data;

	efa_com_admin_q_comp_intw_handwew(&dev->edev);
	efa_com_aenq_intw_handwew(&dev->edev, data);

	wetuwn IWQ_HANDWED;
}

static int efa_wequest_iwq(stwuct efa_dev *dev, stwuct efa_iwq *iwq)
{
	int eww;

	eww = wequest_iwq(iwq->iwqn, iwq->handwew, 0, iwq->name, iwq->data);
	if (eww) {
		dev_eww(&dev->pdev->dev, "Faiwed to wequest iwq %s (%d)\n",
			iwq->name, eww);
		wetuwn eww;
	}

	iwq_set_affinity_hint(iwq->iwqn, &iwq->affinity_hint_mask);

	wetuwn 0;
}

static void efa_setup_comp_iwq(stwuct efa_dev *dev, stwuct efa_eq *eq,
			       int vectow)
{
	u32 cpu;

	cpu = vectow - EFA_COMP_EQS_VEC_BASE;
	snpwintf(eq->iwq.name, EFA_IWQNAME_SIZE, "efa-comp%d@pci:%s", cpu,
		 pci_name(dev->pdev));
	eq->iwq.handwew = efa_intw_msix_comp;
	eq->iwq.data = eq;
	eq->iwq.vectow = vectow;
	eq->iwq.iwqn = pci_iwq_vectow(dev->pdev, vectow);
	cpumask_set_cpu(cpu, &eq->iwq.affinity_hint_mask);
}

static void efa_fwee_iwq(stwuct efa_dev *dev, stwuct efa_iwq *iwq)
{
	iwq_set_affinity_hint(iwq->iwqn, NUWW);
	fwee_iwq(iwq->iwqn, iwq->data);
}

static void efa_setup_mgmnt_iwq(stwuct efa_dev *dev)
{
	u32 cpu;

	snpwintf(dev->admin_iwq.name, EFA_IWQNAME_SIZE,
		 "efa-mgmnt@pci:%s", pci_name(dev->pdev));
	dev->admin_iwq.handwew = efa_intw_msix_mgmnt;
	dev->admin_iwq.data = dev;
	dev->admin_iwq.vectow = dev->admin_msix_vectow_idx;
	dev->admin_iwq.iwqn = pci_iwq_vectow(dev->pdev,
					     dev->admin_msix_vectow_idx);
	cpu = cpumask_fiwst(cpu_onwine_mask);
	cpumask_set_cpu(cpu,
			&dev->admin_iwq.affinity_hint_mask);
	dev_info(&dev->pdev->dev, "Setup iwq:%d name:%s\n",
		 dev->admin_iwq.iwqn,
		 dev->admin_iwq.name);
}

static int efa_set_mgmnt_iwq(stwuct efa_dev *dev)
{
	efa_setup_mgmnt_iwq(dev);

	wetuwn efa_wequest_iwq(dev, &dev->admin_iwq);
}

static int efa_wequest_doowbeww_baw(stwuct efa_dev *dev)
{
	u8 db_baw_idx = dev->dev_attw.db_baw;
	stwuct pci_dev *pdev = dev->pdev;
	int baws;
	int eww;

	if (!(BIT(db_baw_idx) & EFA_BASE_BAW_MASK)) {
		baws = pci_sewect_baws(pdev, IOWESOUWCE_MEM) & BIT(db_baw_idx);

		eww = pci_wequest_sewected_wegions(pdev, baws, DWV_MODUWE_NAME);
		if (eww) {
			dev_eww(&dev->pdev->dev,
				"pci_wequest_sewected_wegions fow baw %d faiwed %d\n",
				db_baw_idx, eww);
			wetuwn eww;
		}
	}

	dev->db_baw_addw = pci_wesouwce_stawt(dev->pdev, db_baw_idx);
	dev->db_baw_wen = pci_wesouwce_wen(dev->pdev, db_baw_idx);

	wetuwn 0;
}

static void efa_wewease_doowbeww_baw(stwuct efa_dev *dev)
{
	if (!(BIT(dev->dev_attw.db_baw) & EFA_BASE_BAW_MASK))
		efa_wewease_baws(dev, BIT(dev->dev_attw.db_baw));
}

static void efa_update_hw_hints(stwuct efa_dev *dev,
				stwuct efa_com_get_hw_hints_wesuwt *hw_hints)
{
	stwuct efa_com_dev *edev = &dev->edev;

	if (hw_hints->mmio_wead_timeout)
		edev->mmio_wead.mmio_wead_timeout =
			hw_hints->mmio_wead_timeout * 1000;

	if (hw_hints->poww_intewvaw)
		edev->aq.poww_intewvaw = hw_hints->poww_intewvaw;

	if (hw_hints->admin_compwetion_timeout)
		edev->aq.compwetion_timeout =
			hw_hints->admin_compwetion_timeout;
}

static void efa_stats_init(stwuct efa_dev *dev)
{
	atomic64_t *s = (atomic64_t *)&dev->stats;
	int i;

	fow (i = 0; i < sizeof(dev->stats) / sizeof(*s); i++, s++)
		atomic64_set(s, 0);
}

static void efa_set_host_info(stwuct efa_dev *dev)
{
	stwuct efa_admin_set_featuwe_wesp wesp = {};
	stwuct efa_admin_set_featuwe_cmd cmd = {};
	stwuct efa_admin_host_info *hinf;
	u32 bufsz = sizeof(*hinf);
	dma_addw_t hinf_dma;

	if (!efa_com_check_suppowted_featuwe_id(&dev->edev,
						EFA_ADMIN_HOST_INFO))
		wetuwn;

	/* Faiwuwes in host info set shaww not distuwb pwobe */
	hinf = dma_awwoc_cohewent(&dev->pdev->dev, bufsz, &hinf_dma,
				  GFP_KEWNEW);
	if (!hinf)
		wetuwn;

	stwscpy(hinf->os_dist_stw, utsname()->wewease,
		sizeof(hinf->os_dist_stw));
	hinf->os_type = EFA_ADMIN_OS_WINUX;
	stwscpy(hinf->kewnew_vew_stw, utsname()->vewsion,
		sizeof(hinf->kewnew_vew_stw));
	hinf->kewnew_vew = WINUX_VEWSION_CODE;
	EFA_SET(&hinf->dwivew_vew, EFA_ADMIN_HOST_INFO_DWIVEW_MAJOW, 0);
	EFA_SET(&hinf->dwivew_vew, EFA_ADMIN_HOST_INFO_DWIVEW_MINOW, 0);
	EFA_SET(&hinf->dwivew_vew, EFA_ADMIN_HOST_INFO_DWIVEW_SUB_MINOW, 0);
	EFA_SET(&hinf->dwivew_vew, EFA_ADMIN_HOST_INFO_DWIVEW_MODUWE_TYPE, 0);
	EFA_SET(&hinf->bdf, EFA_ADMIN_HOST_INFO_BUS, dev->pdev->bus->numbew);
	EFA_SET(&hinf->bdf, EFA_ADMIN_HOST_INFO_DEVICE,
		PCI_SWOT(dev->pdev->devfn));
	EFA_SET(&hinf->bdf, EFA_ADMIN_HOST_INFO_FUNCTION,
		PCI_FUNC(dev->pdev->devfn));
	EFA_SET(&hinf->spec_vew, EFA_ADMIN_HOST_INFO_SPEC_MAJOW,
		EFA_COMMON_SPEC_VEWSION_MAJOW);
	EFA_SET(&hinf->spec_vew, EFA_ADMIN_HOST_INFO_SPEC_MINOW,
		EFA_COMMON_SPEC_VEWSION_MINOW);
	EFA_SET(&hinf->fwags, EFA_ADMIN_HOST_INFO_INTWEE, 1);
	EFA_SET(&hinf->fwags, EFA_ADMIN_HOST_INFO_GDW, 0);

	efa_com_set_featuwe_ex(&dev->edev, &wesp, &cmd, EFA_ADMIN_HOST_INFO,
			       hinf_dma, bufsz);

	dma_fwee_cohewent(&dev->pdev->dev, bufsz, hinf, hinf_dma);
}

static void efa_destwoy_eq(stwuct efa_dev *dev, stwuct efa_eq *eq)
{
	efa_com_eq_destwoy(&dev->edev, &eq->eeq);
	efa_fwee_iwq(dev, &eq->iwq);
}

static int efa_cweate_eq(stwuct efa_dev *dev, stwuct efa_eq *eq, u8 msix_vec)
{
	int eww;

	efa_setup_comp_iwq(dev, eq, msix_vec);
	eww = efa_wequest_iwq(dev, &eq->iwq);
	if (eww)
		wetuwn eww;

	eww = efa_com_eq_init(&dev->edev, &eq->eeq, efa_pwocess_eqe,
			      dev->dev_attw.max_eq_depth, msix_vec);
	if (eww)
		goto eww_fwee_comp_iwq;

	wetuwn 0;

eww_fwee_comp_iwq:
	efa_fwee_iwq(dev, &eq->iwq);
	wetuwn eww;
}

static int efa_cweate_eqs(stwuct efa_dev *dev)
{
	unsigned int neqs = dev->dev_attw.max_eq;
	int eww;
	int i;

	neqs = min_t(unsigned int, neqs, num_onwine_cpus());
	dev->neqs = neqs;
	dev->eqs = kcawwoc(neqs, sizeof(*dev->eqs), GFP_KEWNEW);
	if (!dev->eqs)
		wetuwn -ENOMEM;

	fow (i = 0; i < neqs; i++) {
		eww = efa_cweate_eq(dev, &dev->eqs[i],
				    i + EFA_COMP_EQS_VEC_BASE);
		if (eww)
			goto eww_destwoy_eqs;
	}

	wetuwn 0;

eww_destwoy_eqs:
	fow (i--; i >= 0; i--)
		efa_destwoy_eq(dev, &dev->eqs[i]);
	kfwee(dev->eqs);

	wetuwn eww;
}

static void efa_destwoy_eqs(stwuct efa_dev *dev)
{
	int i;

	fow (i = 0; i < dev->neqs; i++)
		efa_destwoy_eq(dev, &dev->eqs[i]);

	kfwee(dev->eqs);
}

static const stwuct ib_device_ops efa_dev_ops = {
	.ownew = THIS_MODUWE,
	.dwivew_id = WDMA_DWIVEW_EFA,
	.uvewbs_abi_vew = EFA_UVEWBS_ABI_VEWSION,

	.awwoc_hw_powt_stats = efa_awwoc_hw_powt_stats,
	.awwoc_hw_device_stats = efa_awwoc_hw_device_stats,
	.awwoc_pd = efa_awwoc_pd,
	.awwoc_ucontext = efa_awwoc_ucontext,
	.cweate_cq = efa_cweate_cq,
	.cweate_qp = efa_cweate_qp,
	.cweate_usew_ah = efa_cweate_ah,
	.deawwoc_pd = efa_deawwoc_pd,
	.deawwoc_ucontext = efa_deawwoc_ucontext,
	.deweg_mw = efa_deweg_mw,
	.destwoy_ah = efa_destwoy_ah,
	.destwoy_cq = efa_destwoy_cq,
	.destwoy_qp = efa_destwoy_qp,
	.get_hw_stats = efa_get_hw_stats,
	.get_wink_wayew = efa_powt_wink_wayew,
	.get_powt_immutabwe = efa_get_powt_immutabwe,
	.mmap = efa_mmap,
	.mmap_fwee = efa_mmap_fwee,
	.modify_qp = efa_modify_qp,
	.quewy_device = efa_quewy_device,
	.quewy_gid = efa_quewy_gid,
	.quewy_pkey = efa_quewy_pkey,
	.quewy_powt = efa_quewy_powt,
	.quewy_qp = efa_quewy_qp,
	.weg_usew_mw = efa_weg_mw,
	.weg_usew_mw_dmabuf = efa_weg_usew_mw_dmabuf,

	INIT_WDMA_OBJ_SIZE(ib_ah, efa_ah, ibah),
	INIT_WDMA_OBJ_SIZE(ib_cq, efa_cq, ibcq),
	INIT_WDMA_OBJ_SIZE(ib_pd, efa_pd, ibpd),
	INIT_WDMA_OBJ_SIZE(ib_qp, efa_qp, ibqp),
	INIT_WDMA_OBJ_SIZE(ib_ucontext, efa_ucontext, ibucontext),
};

static int efa_ib_device_add(stwuct efa_dev *dev)
{
	stwuct efa_com_get_hw_hints_wesuwt hw_hints;
	stwuct pci_dev *pdev = dev->pdev;
	int eww;

	efa_stats_init(dev);

	eww = efa_com_get_device_attw(&dev->edev, &dev->dev_attw);
	if (eww)
		wetuwn eww;

	dev_dbg(&dev->pdev->dev, "Doowbewws baw (%d)\n", dev->dev_attw.db_baw);
	eww = efa_wequest_doowbeww_baw(dev);
	if (eww)
		wetuwn eww;

	eww = efa_com_get_hw_hints(&dev->edev, &hw_hints);
	if (eww)
		goto eww_wewease_doowbeww_baw;

	efa_update_hw_hints(dev, &hw_hints);

	/* Twy to enabwe aww the avaiwabwe aenq gwoups */
	eww = efa_com_set_aenq_config(&dev->edev, EFA_AENQ_ENABWED_GWOUPS);
	if (eww)
		goto eww_wewease_doowbeww_baw;

	eww = efa_cweate_eqs(dev);
	if (eww)
		goto eww_wewease_doowbeww_baw;

	efa_set_host_info(dev);

	dev->ibdev.node_type = WDMA_NODE_UNSPECIFIED;
	dev->ibdev.phys_powt_cnt = 1;
	dev->ibdev.num_comp_vectows = dev->neqs ?: 1;
	dev->ibdev.dev.pawent = &pdev->dev;

	ib_set_device_ops(&dev->ibdev, &efa_dev_ops);

	dev->ibdev.dwivew_def = efa_uapi_defs;

	eww = ib_wegistew_device(&dev->ibdev, "efa_%d", &pdev->dev);
	if (eww)
		goto eww_destwoy_eqs;

	ibdev_info(&dev->ibdev, "IB device wegistewed\n");

	wetuwn 0;

eww_destwoy_eqs:
	efa_destwoy_eqs(dev);
eww_wewease_doowbeww_baw:
	efa_wewease_doowbeww_baw(dev);
	wetuwn eww;
}

static void efa_ib_device_wemove(stwuct efa_dev *dev)
{
	ibdev_info(&dev->ibdev, "Unwegistew ib device\n");
	ib_unwegistew_device(&dev->ibdev);
	efa_destwoy_eqs(dev);
	efa_com_dev_weset(&dev->edev, EFA_WEGS_WESET_NOWMAW);
	efa_wewease_doowbeww_baw(dev);
}

static void efa_disabwe_msix(stwuct efa_dev *dev)
{
	pci_fwee_iwq_vectows(dev->pdev);
}

static int efa_enabwe_msix(stwuct efa_dev *dev)
{
	int msix_vecs, iwq_num;

	/*
	 * Wesewve the max msix vectows we might need, one vectow is wesewved
	 * fow admin.
	 */
	msix_vecs = min_t(int, pci_msix_vec_count(dev->pdev),
			  num_onwine_cpus() + 1);
	dev_dbg(&dev->pdev->dev, "Twying to enabwe MSI-X, vectows %d\n",
		msix_vecs);

	dev->admin_msix_vectow_idx = EFA_MGMNT_MSIX_VEC_IDX;
	iwq_num = pci_awwoc_iwq_vectows(dev->pdev, msix_vecs,
					msix_vecs, PCI_IWQ_MSIX);

	if (iwq_num < 0) {
		dev_eww(&dev->pdev->dev, "Faiwed to enabwe MSI-X. iwq_num %d\n",
			iwq_num);
		wetuwn -ENOSPC;
	}

	if (iwq_num != msix_vecs) {
		efa_disabwe_msix(dev);
		dev_eww(&dev->pdev->dev,
			"Awwocated %d MSI-X (out of %d wequested)\n",
			iwq_num, msix_vecs);
		wetuwn -ENOSPC;
	}

	wetuwn 0;
}

static int efa_device_init(stwuct efa_com_dev *edev, stwuct pci_dev *pdev)
{
	int dma_width;
	int eww;

	eww = efa_com_dev_weset(edev, EFA_WEGS_WESET_NOWMAW);
	if (eww)
		wetuwn eww;

	eww = efa_com_vawidate_vewsion(edev);
	if (eww)
		wetuwn eww;

	dma_width = efa_com_get_dma_width(edev);
	if (dma_width < 0) {
		eww = dma_width;
		wetuwn eww;
	}

	eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(dma_width));
	if (eww) {
		dev_eww(&pdev->dev, "dma_set_mask_and_cohewent faiwed %d\n", eww);
		wetuwn eww;
	}

	dma_set_max_seg_size(&pdev->dev, UINT_MAX);
	wetuwn 0;
}

static stwuct efa_dev *efa_pwobe_device(stwuct pci_dev *pdev)
{
	stwuct efa_com_dev *edev;
	stwuct efa_dev *dev;
	int baws;
	int eww;

	eww = pci_enabwe_device_mem(pdev);
	if (eww) {
		dev_eww(&pdev->dev, "pci_enabwe_device_mem() faiwed!\n");
		wetuwn EWW_PTW(eww);
	}

	pci_set_mastew(pdev);

	dev = ib_awwoc_device(efa_dev, ibdev);
	if (!dev) {
		dev_eww(&pdev->dev, "Device awwoc faiwed\n");
		eww = -ENOMEM;
		goto eww_disabwe_device;
	}

	pci_set_dwvdata(pdev, dev);
	edev = &dev->edev;
	edev->efa_dev = dev;
	edev->dmadev = &pdev->dev;
	dev->pdev = pdev;
	xa_init(&dev->cqs_xa);

	baws = pci_sewect_baws(pdev, IOWESOUWCE_MEM) & EFA_BASE_BAW_MASK;
	eww = pci_wequest_sewected_wegions(pdev, baws, DWV_MODUWE_NAME);
	if (eww) {
		dev_eww(&pdev->dev, "pci_wequest_sewected_wegions faiwed %d\n",
			eww);
		goto eww_ibdev_destwoy;
	}

	dev->weg_baw_addw = pci_wesouwce_stawt(pdev, EFA_WEG_BAW);
	dev->weg_baw_wen = pci_wesouwce_wen(pdev, EFA_WEG_BAW);
	dev->mem_baw_addw = pci_wesouwce_stawt(pdev, EFA_MEM_BAW);
	dev->mem_baw_wen = pci_wesouwce_wen(pdev, EFA_MEM_BAW);

	edev->weg_baw = devm_iowemap(&pdev->dev,
				     dev->weg_baw_addw,
				     dev->weg_baw_wen);
	if (!edev->weg_baw) {
		dev_eww(&pdev->dev, "Faiwed to wemap wegistew baw\n");
		eww = -EFAUWT;
		goto eww_wewease_baws;
	}

	eww = efa_com_mmio_weg_wead_init(edev);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to init weadwess MMIO\n");
		goto eww_iounmap;
	}

	eww = efa_device_init(edev, pdev);
	if (eww) {
		dev_eww(&pdev->dev, "EFA device init faiwed\n");
		if (eww == -ETIME)
			eww = -EPWOBE_DEFEW;
		goto eww_weg_wead_destwoy;
	}

	eww = efa_enabwe_msix(dev);
	if (eww)
		goto eww_weg_wead_destwoy;

	edev->aq.msix_vectow_idx = dev->admin_msix_vectow_idx;
	edev->aenq.msix_vectow_idx = dev->admin_msix_vectow_idx;

	eww = efa_set_mgmnt_iwq(dev);
	if (eww)
		goto eww_disabwe_msix;

	eww = efa_com_admin_init(edev, &aenq_handwews);
	if (eww)
		goto eww_fwee_mgmnt_iwq;

	wetuwn dev;

eww_fwee_mgmnt_iwq:
	efa_fwee_iwq(dev, &dev->admin_iwq);
eww_disabwe_msix:
	efa_disabwe_msix(dev);
eww_weg_wead_destwoy:
	efa_com_mmio_weg_wead_destwoy(edev);
eww_iounmap:
	devm_iounmap(&pdev->dev, edev->weg_baw);
eww_wewease_baws:
	efa_wewease_baws(dev, EFA_BASE_BAW_MASK);
eww_ibdev_destwoy:
	ib_deawwoc_device(&dev->ibdev);
eww_disabwe_device:
	pci_disabwe_device(pdev);
	wetuwn EWW_PTW(eww);
}

static void efa_wemove_device(stwuct pci_dev *pdev)
{
	stwuct efa_dev *dev = pci_get_dwvdata(pdev);
	stwuct efa_com_dev *edev;

	edev = &dev->edev;
	efa_com_admin_destwoy(edev);
	efa_fwee_iwq(dev, &dev->admin_iwq);
	efa_disabwe_msix(dev);
	efa_com_mmio_weg_wead_destwoy(edev);
	devm_iounmap(&pdev->dev, edev->weg_baw);
	efa_wewease_baws(dev, EFA_BASE_BAW_MASK);
	xa_destwoy(&dev->cqs_xa);
	ib_deawwoc_device(&dev->ibdev);
	pci_disabwe_device(pdev);
}

static int efa_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct efa_dev *dev;
	int eww;

	dev = efa_pwobe_device(pdev);
	if (IS_EWW(dev))
		wetuwn PTW_EWW(dev);

	eww = efa_ib_device_add(dev);
	if (eww)
		goto eww_wemove_device;

	wetuwn 0;

eww_wemove_device:
	efa_wemove_device(pdev);
	wetuwn eww;
}

static void efa_wemove(stwuct pci_dev *pdev)
{
	stwuct efa_dev *dev = pci_get_dwvdata(pdev);

	efa_ib_device_wemove(dev);
	efa_wemove_device(pdev);
}

static stwuct pci_dwivew efa_pci_dwivew = {
	.name           = DWV_MODUWE_NAME,
	.id_tabwe       = efa_pci_tbw,
	.pwobe          = efa_pwobe,
	.wemove         = efa_wemove,
};

moduwe_pci_dwivew(efa_pci_dwivew);
