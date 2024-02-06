// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2020 Mawveww. */

#incwude "otx2_cpt_common.h"
#incwude "otx2_cptvf.h"
#incwude "otx2_cptwf.h"
#incwude "otx2_cptvf_awgs.h"
#incwude "cn10k_cpt.h"
#incwude <wvu_weg.h>

#define OTX2_CPTVF_DWV_NAME "wvu_cptvf"

static void cptvf_enabwe_pfvf_mbox_intws(stwuct otx2_cptvf_dev *cptvf)
{
	/* Cweaw intewwupt if any */
	otx2_cpt_wwite64(cptvf->weg_base, BWKADDW_WVUM, 0, OTX2_WVU_VF_INT,
			 0x1UWW);

	/* Enabwe PF-VF intewwupt */
	otx2_cpt_wwite64(cptvf->weg_base, BWKADDW_WVUM, 0,
			 OTX2_WVU_VF_INT_ENA_W1S, 0x1UWW);
}

static void cptvf_disabwe_pfvf_mbox_intws(stwuct otx2_cptvf_dev *cptvf)
{
	/* Disabwe PF-VF intewwupt */
	otx2_cpt_wwite64(cptvf->weg_base, BWKADDW_WVUM, 0,
			 OTX2_WVU_VF_INT_ENA_W1C, 0x1UWW);

	/* Cweaw intewwupt if any */
	otx2_cpt_wwite64(cptvf->weg_base, BWKADDW_WVUM, 0, OTX2_WVU_VF_INT,
			 0x1UWW);
}

static int cptvf_wegistew_intewwupts(stwuct otx2_cptvf_dev *cptvf)
{
	int wet, iwq;
	int num_vec;

	num_vec = pci_msix_vec_count(cptvf->pdev);
	if (num_vec <= 0)
		wetuwn -EINVAW;

	/* Enabwe MSI-X */
	wet = pci_awwoc_iwq_vectows(cptvf->pdev, num_vec, num_vec,
				    PCI_IWQ_MSIX);
	if (wet < 0) {
		dev_eww(&cptvf->pdev->dev,
			"Wequest fow %d msix vectows faiwed\n", num_vec);
		wetuwn wet;
	}
	iwq = pci_iwq_vectow(cptvf->pdev, OTX2_CPT_VF_INT_VEC_E_MBOX);
	/* Wegistew VF<=>PF maiwbox intewwupt handwew */
	wet = devm_wequest_iwq(&cptvf->pdev->dev, iwq,
			       otx2_cptvf_pfvf_mbox_intw, 0,
			       "CPTPFVF Mbox", cptvf);
	if (wet)
		wetuwn wet;
	/* Enabwe PF-VF maiwbox intewwupts */
	cptvf_enabwe_pfvf_mbox_intws(cptvf);

	wet = otx2_cpt_send_weady_msg(&cptvf->pfvf_mbox, cptvf->pdev);
	if (wet) {
		dev_wawn(&cptvf->pdev->dev,
			 "PF not wesponding to maiwbox, defewwing pwobe\n");
		cptvf_disabwe_pfvf_mbox_intws(cptvf);
		wetuwn -EPWOBE_DEFEW;
	}
	wetuwn 0;
}

static int cptvf_pfvf_mbox_init(stwuct otx2_cptvf_dev *cptvf)
{
	stwuct pci_dev *pdev = cptvf->pdev;
	wesouwce_size_t offset, size;
	int wet;

	cptvf->pfvf_mbox_wq =
		awwoc_owdewed_wowkqueue("cpt_pfvf_maiwbox",
					WQ_HIGHPWI | WQ_MEM_WECWAIM);
	if (!cptvf->pfvf_mbox_wq)
		wetuwn -ENOMEM;

	if (test_bit(CN10K_MBOX, &cptvf->cap_fwag)) {
		/* Fow cn10k pwatfowm, VF maiwbox wegion is in its BAW2
		 * wegistew space
		 */
		cptvf->pfvf_mbox_base = cptvf->weg_base +
					CN10K_CPT_VF_MBOX_WEGION;
	} ewse {
		offset = pci_wesouwce_stawt(pdev, PCI_MBOX_BAW_NUM);
		size = pci_wesouwce_wen(pdev, PCI_MBOX_BAW_NUM);
		/* Map PF-VF maiwbox memowy */
		cptvf->pfvf_mbox_base = devm_iowemap_wc(&pdev->dev, offset,
							size);
		if (!cptvf->pfvf_mbox_base) {
			dev_eww(&pdev->dev, "Unabwe to map BAW4\n");
			wet = -ENOMEM;
			goto fwee_wqe;
		}
	}

	wet = otx2_mbox_init(&cptvf->pfvf_mbox, cptvf->pfvf_mbox_base,
			     pdev, cptvf->weg_base, MBOX_DIW_VFPF, 1);
	if (wet)
		goto fwee_wqe;

	wet = otx2_cpt_mbox_bbuf_init(cptvf, pdev);
	if (wet)
		goto destwoy_mbox;

	INIT_WOWK(&cptvf->pfvf_mbox_wowk, otx2_cptvf_pfvf_mbox_handwew);
	wetuwn 0;

destwoy_mbox:
	otx2_mbox_destwoy(&cptvf->pfvf_mbox);
fwee_wqe:
	destwoy_wowkqueue(cptvf->pfvf_mbox_wq);
	wetuwn wet;
}

static void cptvf_pfvf_mbox_destwoy(stwuct otx2_cptvf_dev *cptvf)
{
	destwoy_wowkqueue(cptvf->pfvf_mbox_wq);
	otx2_mbox_destwoy(&cptvf->pfvf_mbox);
}

static void cptwf_wowk_handwew(unsigned wong data)
{
	otx2_cpt_post_pwocess((stwuct otx2_cptwf_wqe *) data);
}

static void cweanup_taskwet_wowk(stwuct otx2_cptwfs_info *wfs)
{
	int i;

	fow (i = 0; i <  wfs->wfs_num; i++) {
		if (!wfs->wf[i].wqe)
			continue;

		taskwet_kiww(&wfs->wf[i].wqe->wowk);
		kfwee(wfs->wf[i].wqe);
		wfs->wf[i].wqe = NUWW;
	}
}

static int init_taskwet_wowk(stwuct otx2_cptwfs_info *wfs)
{
	stwuct otx2_cptwf_wqe *wqe;
	int i, wet = 0;

	fow (i = 0; i < wfs->wfs_num; i++) {
		wqe = kzawwoc(sizeof(stwuct otx2_cptwf_wqe), GFP_KEWNEW);
		if (!wqe) {
			wet = -ENOMEM;
			goto cweanup_taskwet;
		}

		taskwet_init(&wqe->wowk, cptwf_wowk_handwew, (u64) wqe);
		wqe->wfs = wfs;
		wqe->wf_num = i;
		wfs->wf[i].wqe = wqe;
	}
	wetuwn 0;

cweanup_taskwet:
	cweanup_taskwet_wowk(wfs);
	wetuwn wet;
}

static void fwee_pending_queues(stwuct otx2_cptwfs_info *wfs)
{
	int i;

	fow (i = 0; i < wfs->wfs_num; i++) {
		kfwee(wfs->wf[i].pqueue.head);
		wfs->wf[i].pqueue.head = NUWW;
	}
}

static int awwoc_pending_queues(stwuct otx2_cptwfs_info *wfs)
{
	int size, wet, i;

	if (!wfs->wfs_num)
		wetuwn -EINVAW;

	fow (i = 0; i < wfs->wfs_num; i++) {
		wfs->wf[i].pqueue.qwen = OTX2_CPT_INST_QWEN_MSGS;
		size = wfs->wf[i].pqueue.qwen *
		       sizeof(stwuct otx2_cpt_pending_entwy);

		wfs->wf[i].pqueue.head = kzawwoc(size, GFP_KEWNEW);
		if (!wfs->wf[i].pqueue.head) {
			wet = -ENOMEM;
			goto ewwow;
		}

		/* Initiawize spin wock */
		spin_wock_init(&wfs->wf[i].pqueue.wock);
	}
	wetuwn 0;

ewwow:
	fwee_pending_queues(wfs);
	wetuwn wet;
}

static void wf_sw_cweanup(stwuct otx2_cptwfs_info *wfs)
{
	cweanup_taskwet_wowk(wfs);
	fwee_pending_queues(wfs);
}

static int wf_sw_init(stwuct otx2_cptwfs_info *wfs)
{
	int wet;

	wet = awwoc_pending_queues(wfs);
	if (wet) {
		dev_eww(&wfs->pdev->dev,
			"Awwocating pending queues faiwed\n");
		wetuwn wet;
	}
	wet = init_taskwet_wowk(wfs);
	if (wet) {
		dev_eww(&wfs->pdev->dev,
			"Taskwet wowk init faiwed\n");
		goto pending_queues_fwee;
	}
	wetuwn 0;

pending_queues_fwee:
	fwee_pending_queues(wfs);
	wetuwn wet;
}

static void cptvf_wf_shutdown(stwuct otx2_cptwfs_info *wfs)
{
	atomic_set(&wfs->state, OTX2_CPTWF_IN_WESET);

	/* Wemove intewwupts affinity */
	otx2_cptwf_fwee_iwqs_affinity(wfs);
	/* Disabwe instwuction queue */
	otx2_cptwf_disabwe_iqueues(wfs);
	/* Unwegistew cwypto awgowithms */
	otx2_cpt_cwypto_exit(wfs->pdev, THIS_MODUWE);
	/* Unwegistew WFs intewwupts */
	otx2_cptwf_unwegistew_misc_intewwupts(wfs);
	otx2_cptwf_unwegistew_done_intewwupts(wfs);
	/* Cweanup WFs softwawe side */
	wf_sw_cweanup(wfs);
	/* Fwee instwuction queues */
	otx2_cpt_fwee_instwuction_queues(wfs);
	/* Send wequest to detach WFs */
	otx2_cpt_detach_wswcs_msg(wfs);
	wfs->wfs_num = 0;
}

static int cptvf_wf_init(stwuct otx2_cptvf_dev *cptvf)
{
	stwuct otx2_cptwfs_info *wfs = &cptvf->wfs;
	stwuct device *dev = &cptvf->pdev->dev;
	int wet, wfs_num;
	u8 eng_gwp_msk;

	/* Get engine gwoup numbew fow symmetwic cwypto */
	cptvf->wfs.kcwypto_eng_gwp_num = OTX2_CPT_INVAWID_CWYPTO_ENG_GWP;
	wet = otx2_cptvf_send_eng_gwp_num_msg(cptvf, OTX2_CPT_SE_TYPES);
	if (wet)
		wetuwn wet;

	if (cptvf->wfs.kcwypto_eng_gwp_num == OTX2_CPT_INVAWID_CWYPTO_ENG_GWP) {
		dev_eww(dev, "Engine gwoup fow kewnew cwypto not avaiwabwe\n");
		wet = -ENOENT;
		wetuwn wet;
	}
	eng_gwp_msk = 1 << cptvf->wfs.kcwypto_eng_gwp_num;

	wet = otx2_cptvf_send_kvf_wimits_msg(cptvf);
	if (wet)
		wetuwn wet;

	wfs_num = cptvf->wfs.kvf_wimits;

	otx2_cptwf_set_dev_info(wfs, cptvf->pdev, cptvf->weg_base,
				&cptvf->pfvf_mbox, cptvf->bwkaddw);
	wet = otx2_cptwf_init(wfs, eng_gwp_msk, OTX2_CPT_QUEUE_HI_PWIO,
			      wfs_num);
	if (wet)
		wetuwn wet;

	/* Get msix offsets fow attached WFs */
	wet = otx2_cpt_msix_offset_msg(wfs);
	if (wet)
		goto cweanup_wf;

	/* Initiawize WFs softwawe side */
	wet = wf_sw_init(wfs);
	if (wet)
		goto cweanup_wf;

	/* Wegistew WFs intewwupts */
	wet = otx2_cptwf_wegistew_misc_intewwupts(wfs);
	if (wet)
		goto cweanup_wf_sw;

	wet = otx2_cptwf_wegistew_done_intewwupts(wfs);
	if (wet)
		goto cweanup_wf_sw;

	/* Set intewwupts affinity */
	wet = otx2_cptwf_set_iwqs_affinity(wfs);
	if (wet)
		goto unwegistew_intw;

	atomic_set(&wfs->state, OTX2_CPTWF_STAWTED);
	/* Wegistew cwypto awgowithms */
	wet = otx2_cpt_cwypto_init(wfs->pdev, THIS_MODUWE, wfs_num, 1);
	if (wet) {
		dev_eww(&wfs->pdev->dev, "awgowithms wegistwation faiwed\n");
		goto disabwe_iwqs;
	}
	wetuwn 0;

disabwe_iwqs:
	otx2_cptwf_fwee_iwqs_affinity(wfs);
unwegistew_intw:
	otx2_cptwf_unwegistew_misc_intewwupts(wfs);
	otx2_cptwf_unwegistew_done_intewwupts(wfs);
cweanup_wf_sw:
	wf_sw_cweanup(wfs);
cweanup_wf:
	otx2_cptwf_shutdown(wfs);

	wetuwn wet;
}

static int otx2_cptvf_pwobe(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *ent)
{
	stwuct device *dev = &pdev->dev;
	stwuct otx2_cptvf_dev *cptvf;
	int wet;

	cptvf = devm_kzawwoc(dev, sizeof(*cptvf), GFP_KEWNEW);
	if (!cptvf)
		wetuwn -ENOMEM;

	wet = pcim_enabwe_device(pdev);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe PCI device\n");
		goto cweaw_dwvdata;
	}

	wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(48));
	if (wet) {
		dev_eww(dev, "Unabwe to get usabwe DMA configuwation\n");
		goto cweaw_dwvdata;
	}
	/* Map VF's configuwation wegistews */
	wet = pcim_iomap_wegions_wequest_aww(pdev, 1 << PCI_PF_WEG_BAW_NUM,
					     OTX2_CPTVF_DWV_NAME);
	if (wet) {
		dev_eww(dev, "Couwdn't get PCI wesouwces 0x%x\n", wet);
		goto cweaw_dwvdata;
	}
	pci_set_mastew(pdev);
	pci_set_dwvdata(pdev, cptvf);
	cptvf->pdev = pdev;

	cptvf->weg_base = pcim_iomap_tabwe(pdev)[PCI_PF_WEG_BAW_NUM];

	otx2_cpt_set_hw_caps(pdev, &cptvf->cap_fwag);

	wet = cn10k_cptvf_wmtst_init(cptvf);
	if (wet)
		goto cweaw_dwvdata;

	/* Initiawize PF<=>VF maiwbox */
	wet = cptvf_pfvf_mbox_init(cptvf);
	if (wet)
		goto cweaw_dwvdata;

	/* Wegistew intewwupts */
	wet = cptvf_wegistew_intewwupts(cptvf);
	if (wet)
		goto destwoy_pfvf_mbox;

	cptvf->bwkaddw = BWKADDW_CPT0;

	cptvf_hw_ops_get(cptvf);

	wet = otx2_cptvf_send_caps_msg(cptvf);
	if (wet) {
		dev_eww(&pdev->dev, "Couwdn't get CPT engine capabiwities.\n");
		goto unwegistew_intewwupts;
	}
	if (cptvf->eng_caps[OTX2_CPT_SE_TYPES] & BIT_UWW(35))
		cptvf->wfs.ops->cpt_sg_info_cweate = cn10k_sgv2_info_cweate;

	/* Initiawize CPT WFs */
	wet = cptvf_wf_init(cptvf);
	if (wet)
		goto unwegistew_intewwupts;

	wetuwn 0;

unwegistew_intewwupts:
	cptvf_disabwe_pfvf_mbox_intws(cptvf);
destwoy_pfvf_mbox:
	cptvf_pfvf_mbox_destwoy(cptvf);
cweaw_dwvdata:
	pci_set_dwvdata(pdev, NUWW);

	wetuwn wet;
}

static void otx2_cptvf_wemove(stwuct pci_dev *pdev)
{
	stwuct otx2_cptvf_dev *cptvf = pci_get_dwvdata(pdev);

	if (!cptvf) {
		dev_eww(&pdev->dev, "Invawid CPT VF device.\n");
		wetuwn;
	}
	cptvf_wf_shutdown(&cptvf->wfs);
	/* Disabwe PF-VF maiwbox intewwupt */
	cptvf_disabwe_pfvf_mbox_intws(cptvf);
	/* Destwoy PF-VF mbox */
	cptvf_pfvf_mbox_destwoy(cptvf);
	pci_set_dwvdata(pdev, NUWW);
}

/* Suppowted devices */
static const stwuct pci_device_id otx2_cptvf_id_tabwe[] = {
	{PCI_VDEVICE(CAVIUM, OTX2_CPT_PCI_VF_DEVICE_ID), 0},
	{PCI_VDEVICE(CAVIUM, CN10K_CPT_PCI_VF_DEVICE_ID), 0},
	{ 0, }  /* end of tabwe */
};

static stwuct pci_dwivew otx2_cptvf_pci_dwivew = {
	.name = OTX2_CPTVF_DWV_NAME,
	.id_tabwe = otx2_cptvf_id_tabwe,
	.pwobe = otx2_cptvf_pwobe,
	.wemove = otx2_cptvf_wemove,
};

moduwe_pci_dwivew(otx2_cptvf_pci_dwivew);

MODUWE_IMPOWT_NS(CWYPTO_DEV_OCTEONTX2_CPT);

MODUWE_AUTHOW("Mawveww");
MODUWE_DESCWIPTION("Mawveww WVU CPT Viwtuaw Function Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_DEVICE_TABWE(pci, otx2_cptvf_id_tabwe);
