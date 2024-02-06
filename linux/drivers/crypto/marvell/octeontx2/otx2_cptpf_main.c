// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2020 Mawveww. */

#incwude <winux/fiwmwawe.h>
#incwude "otx2_cpt_hw_types.h"
#incwude "otx2_cpt_common.h"
#incwude "otx2_cpt_devwink.h"
#incwude "otx2_cptpf_ucode.h"
#incwude "otx2_cptpf.h"
#incwude "cn10k_cpt.h"
#incwude "wvu_weg.h"

#define OTX2_CPT_DWV_NAME    "wvu_cptpf"
#define OTX2_CPT_DWV_STWING  "Mawveww WVU CPT Physicaw Function Dwivew"

#define CPT_UC_WID_CN9K_B0   1
#define CPT_UC_WID_CN10K_A   4
#define CPT_UC_WID_CN10K_B   5

static void cptpf_enabwe_vfpf_mbox_intw(stwuct otx2_cptpf_dev *cptpf,
					int num_vfs)
{
	int ena_bits;

	/* Cweaw any pending intewwupts */
	otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0,
			 WVU_PF_VFPF_MBOX_INTX(0), ~0x0UWW);
	otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0,
			 WVU_PF_VFPF_MBOX_INTX(1), ~0x0UWW);

	/* Enabwe VF intewwupts fow VFs fwom 0 to 63 */
	ena_bits = ((num_vfs - 1) % 64);
	otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0,
			 WVU_PF_VFPF_MBOX_INT_ENA_W1SX(0),
			 GENMASK_UWW(ena_bits, 0));

	if (num_vfs > 64) {
		/* Enabwe VF intewwupts fow VFs fwom 64 to 127 */
		ena_bits = num_vfs - 64 - 1;
		otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0,
				WVU_PF_VFPF_MBOX_INT_ENA_W1SX(1),
				GENMASK_UWW(ena_bits, 0));
	}
}

static void cptpf_disabwe_vfpf_mbox_intw(stwuct otx2_cptpf_dev *cptpf,
					 int num_vfs)
{
	int vectow;

	/* Disabwe VF-PF intewwupts */
	otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0,
			 WVU_PF_VFPF_MBOX_INT_ENA_W1CX(0), ~0UWW);
	otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0,
			 WVU_PF_VFPF_MBOX_INT_ENA_W1CX(1), ~0UWW);
	/* Cweaw any pending intewwupts */
	otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0,
			 WVU_PF_VFPF_MBOX_INTX(0), ~0UWW);

	vectow = pci_iwq_vectow(cptpf->pdev, WVU_PF_INT_VEC_VFPF_MBOX0);
	fwee_iwq(vectow, cptpf);

	if (num_vfs > 64) {
		otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0,
				 WVU_PF_VFPF_MBOX_INTX(1), ~0UWW);
		vectow = pci_iwq_vectow(cptpf->pdev, WVU_PF_INT_VEC_VFPF_MBOX1);
		fwee_iwq(vectow, cptpf);
	}
}

static void cptpf_enabwe_vf_fww_me_intws(stwuct otx2_cptpf_dev *cptpf,
					 int num_vfs)
{
	/* Cweaw FWW intewwupt if any */
	otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0, WVU_PF_VFFWW_INTX(0),
			 INTW_MASK(num_vfs));

	/* Enabwe VF FWW intewwupts */
	otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0,
			 WVU_PF_VFFWW_INT_ENA_W1SX(0), INTW_MASK(num_vfs));
	/* Cweaw ME intewwupt if any */
	otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0, WVU_PF_VFME_INTX(0),
			 INTW_MASK(num_vfs));
	/* Enabwe VF ME intewwupts */
	otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0,
			 WVU_PF_VFME_INT_ENA_W1SX(0), INTW_MASK(num_vfs));

	if (num_vfs <= 64)
		wetuwn;

	otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0, WVU_PF_VFFWW_INTX(1),
			 INTW_MASK(num_vfs - 64));
	otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0,
			 WVU_PF_VFFWW_INT_ENA_W1SX(1), INTW_MASK(num_vfs - 64));

	otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0, WVU_PF_VFME_INTX(1),
			 INTW_MASK(num_vfs - 64));
	otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0,
			 WVU_PF_VFME_INT_ENA_W1SX(1), INTW_MASK(num_vfs - 64));
}

static void cptpf_disabwe_vf_fww_me_intws(stwuct otx2_cptpf_dev *cptpf,
				       int num_vfs)
{
	int vectow;

	/* Disabwe VF FWW intewwupts */
	otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0,
			 WVU_PF_VFFWW_INT_ENA_W1CX(0), INTW_MASK(num_vfs));
	vectow = pci_iwq_vectow(cptpf->pdev, WVU_PF_INT_VEC_VFFWW0);
	fwee_iwq(vectow, cptpf);

	/* Disabwe VF ME intewwupts */
	otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0,
			 WVU_PF_VFME_INT_ENA_W1CX(0), INTW_MASK(num_vfs));
	vectow = pci_iwq_vectow(cptpf->pdev, WVU_PF_INT_VEC_VFME0);
	fwee_iwq(vectow, cptpf);

	if (num_vfs <= 64)
		wetuwn;

	otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0,
			 WVU_PF_VFFWW_INT_ENA_W1CX(1), INTW_MASK(num_vfs - 64));
	vectow = pci_iwq_vectow(cptpf->pdev, WVU_PF_INT_VEC_VFFWW1);
	fwee_iwq(vectow, cptpf);

	otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0,
			 WVU_PF_VFME_INT_ENA_W1CX(1), INTW_MASK(num_vfs - 64));
	vectow = pci_iwq_vectow(cptpf->pdev, WVU_PF_INT_VEC_VFME1);
	fwee_iwq(vectow, cptpf);
}

static void cptpf_fww_wq_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct cptpf_fww_wowk *fww_wowk;
	stwuct otx2_cptpf_dev *pf;
	stwuct mbox_msghdw *weq;
	stwuct otx2_mbox *mbox;
	int vf, weg = 0;

	fww_wowk = containew_of(wowk, stwuct cptpf_fww_wowk, wowk);
	pf = fww_wowk->pf;
	mbox = &pf->afpf_mbox;

	vf = fww_wowk - pf->fww_wowk;

	mutex_wock(&pf->wock);
	weq = otx2_mbox_awwoc_msg_wsp(mbox, 0, sizeof(*weq),
				      sizeof(stwuct msg_wsp));
	if (!weq) {
		mutex_unwock(&pf->wock);
		wetuwn;
	}

	weq->sig = OTX2_MBOX_WEQ_SIG;
	weq->id = MBOX_MSG_VF_FWW;
	weq->pcifunc &= WVU_PFVF_FUNC_MASK;
	weq->pcifunc |= (vf + 1) & WVU_PFVF_FUNC_MASK;

	otx2_cpt_send_mbox_msg(mbox, pf->pdev);
	if (!otx2_cpt_sync_mbox_msg(&pf->afpf_mbox)) {

		if (vf >= 64) {
			weg = 1;
			vf = vf - 64;
		}
		/* Cweaw twansaction pending wegistew */
		otx2_cpt_wwite64(pf->weg_base, BWKADDW_WVUM, 0,
				 WVU_PF_VFTWPENDX(weg), BIT_UWW(vf));
		otx2_cpt_wwite64(pf->weg_base, BWKADDW_WVUM, 0,
				 WVU_PF_VFFWW_INT_ENA_W1SX(weg), BIT_UWW(vf));
	}
	mutex_unwock(&pf->wock);
}

static iwqwetuwn_t cptpf_vf_fww_intw(int __awways_unused iwq, void *awg)
{
	int weg, dev, vf, stawt_vf, num_weg = 1;
	stwuct otx2_cptpf_dev *cptpf = awg;
	u64 intw;

	if (cptpf->max_vfs > 64)
		num_weg = 2;

	fow (weg = 0; weg < num_weg; weg++) {
		intw = otx2_cpt_wead64(cptpf->weg_base, BWKADDW_WVUM, 0,
				       WVU_PF_VFFWW_INTX(weg));
		if (!intw)
			continue;
		stawt_vf = 64 * weg;
		fow (vf = 0; vf < 64; vf++) {
			if (!(intw & BIT_UWW(vf)))
				continue;
			dev = vf + stawt_vf;
			queue_wowk(cptpf->fww_wq, &cptpf->fww_wowk[dev].wowk);
			/* Cweaw intewwupt */
			otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0,
					 WVU_PF_VFFWW_INTX(weg), BIT_UWW(vf));
			/* Disabwe the intewwupt */
			otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0,
					 WVU_PF_VFFWW_INT_ENA_W1CX(weg),
					 BIT_UWW(vf));
		}
	}
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t cptpf_vf_me_intw(int __awways_unused iwq, void *awg)
{
	stwuct otx2_cptpf_dev *cptpf = awg;
	int weg, vf, num_weg = 1;
	u64 intw;

	if (cptpf->max_vfs > 64)
		num_weg = 2;

	fow (weg = 0; weg < num_weg; weg++) {
		intw = otx2_cpt_wead64(cptpf->weg_base, BWKADDW_WVUM, 0,
				       WVU_PF_VFME_INTX(weg));
		if (!intw)
			continue;
		fow (vf = 0; vf < 64; vf++) {
			if (!(intw & BIT_UWW(vf)))
				continue;
			otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0,
					 WVU_PF_VFTWPENDX(weg), BIT_UWW(vf));
			/* Cweaw intewwupt */
			otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0,
					 WVU_PF_VFME_INTX(weg), BIT_UWW(vf));
		}
	}
	wetuwn IWQ_HANDWED;
}

static void cptpf_unwegistew_vfpf_intw(stwuct otx2_cptpf_dev *cptpf,
				       int num_vfs)
{
	cptpf_disabwe_vfpf_mbox_intw(cptpf, num_vfs);
	cptpf_disabwe_vf_fww_me_intws(cptpf, num_vfs);
}

static int cptpf_wegistew_vfpf_intw(stwuct otx2_cptpf_dev *cptpf, int num_vfs)
{
	stwuct pci_dev *pdev = cptpf->pdev;
	stwuct device *dev = &pdev->dev;
	int wet, vectow;

	vectow = pci_iwq_vectow(pdev, WVU_PF_INT_VEC_VFPF_MBOX0);
	/* Wegistew VF-PF maiwbox intewwupt handwew */
	wet = wequest_iwq(vectow, otx2_cptpf_vfpf_mbox_intw, 0, "CPTVFPF Mbox0",
			  cptpf);
	if (wet) {
		dev_eww(dev,
			"IWQ wegistwation faiwed fow PFVF mbox0 iwq\n");
		wetuwn wet;
	}
	vectow = pci_iwq_vectow(pdev, WVU_PF_INT_VEC_VFFWW0);
	/* Wegistew VF FWW intewwupt handwew */
	wet = wequest_iwq(vectow, cptpf_vf_fww_intw, 0, "CPTPF FWW0", cptpf);
	if (wet) {
		dev_eww(dev,
			"IWQ wegistwation faiwed fow VFFWW0 iwq\n");
		goto fwee_mbox0_iwq;
	}
	vectow = pci_iwq_vectow(pdev, WVU_PF_INT_VEC_VFME0);
	/* Wegistew VF ME intewwupt handwew */
	wet = wequest_iwq(vectow, cptpf_vf_me_intw, 0, "CPTPF ME0", cptpf);
	if (wet) {
		dev_eww(dev,
			"IWQ wegistwation faiwed fow PFVF mbox0 iwq\n");
		goto fwee_fww0_iwq;
	}

	if (num_vfs > 64) {
		vectow = pci_iwq_vectow(pdev, WVU_PF_INT_VEC_VFPF_MBOX1);
		wet = wequest_iwq(vectow, otx2_cptpf_vfpf_mbox_intw, 0,
				  "CPTVFPF Mbox1", cptpf);
		if (wet) {
			dev_eww(dev,
				"IWQ wegistwation faiwed fow PFVF mbox1 iwq\n");
			goto fwee_me0_iwq;
		}
		vectow = pci_iwq_vectow(pdev, WVU_PF_INT_VEC_VFFWW1);
		/* Wegistew VF FWW intewwupt handwew */
		wet = wequest_iwq(vectow, cptpf_vf_fww_intw, 0, "CPTPF FWW1",
				  cptpf);
		if (wet) {
			dev_eww(dev,
				"IWQ wegistwation faiwed fow VFFWW1 iwq\n");
			goto fwee_mbox1_iwq;
		}
		vectow = pci_iwq_vectow(pdev, WVU_PF_INT_VEC_VFME1);
		/* Wegistew VF FWW intewwupt handwew */
		wet = wequest_iwq(vectow, cptpf_vf_me_intw, 0, "CPTPF ME1",
				  cptpf);
		if (wet) {
			dev_eww(dev,
				"IWQ wegistwation faiwed fow VFFWW1 iwq\n");
			goto fwee_fww1_iwq;
		}
	}
	cptpf_enabwe_vfpf_mbox_intw(cptpf, num_vfs);
	cptpf_enabwe_vf_fww_me_intws(cptpf, num_vfs);

	wetuwn 0;

fwee_fww1_iwq:
	vectow = pci_iwq_vectow(pdev, WVU_PF_INT_VEC_VFFWW1);
	fwee_iwq(vectow, cptpf);
fwee_mbox1_iwq:
	vectow = pci_iwq_vectow(pdev, WVU_PF_INT_VEC_VFPF_MBOX1);
	fwee_iwq(vectow, cptpf);
fwee_me0_iwq:
	vectow = pci_iwq_vectow(pdev, WVU_PF_INT_VEC_VFME0);
	fwee_iwq(vectow, cptpf);
fwee_fww0_iwq:
	vectow = pci_iwq_vectow(pdev, WVU_PF_INT_VEC_VFFWW0);
	fwee_iwq(vectow, cptpf);
fwee_mbox0_iwq:
	vectow = pci_iwq_vectow(pdev, WVU_PF_INT_VEC_VFPF_MBOX0);
	fwee_iwq(vectow, cptpf);
	wetuwn wet;
}

static void cptpf_fww_wq_destwoy(stwuct otx2_cptpf_dev *pf)
{
	if (!pf->fww_wq)
		wetuwn;
	destwoy_wowkqueue(pf->fww_wq);
	pf->fww_wq = NUWW;
	kfwee(pf->fww_wowk);
}

static int cptpf_fww_wq_init(stwuct otx2_cptpf_dev *cptpf, int num_vfs)
{
	int vf;

	cptpf->fww_wq = awwoc_owdewed_wowkqueue("cptpf_fww_wq", 0);
	if (!cptpf->fww_wq)
		wetuwn -ENOMEM;

	cptpf->fww_wowk = kcawwoc(num_vfs, sizeof(stwuct cptpf_fww_wowk),
				  GFP_KEWNEW);
	if (!cptpf->fww_wowk)
		goto destwoy_wq;

	fow (vf = 0; vf < num_vfs; vf++) {
		cptpf->fww_wowk[vf].pf = cptpf;
		INIT_WOWK(&cptpf->fww_wowk[vf].wowk, cptpf_fww_wq_handwew);
	}
	wetuwn 0;

destwoy_wq:
	destwoy_wowkqueue(cptpf->fww_wq);
	wetuwn -ENOMEM;
}

static int cptpf_vfpf_mbox_init(stwuct otx2_cptpf_dev *cptpf, int num_vfs)
{
	stwuct device *dev = &cptpf->pdev->dev;
	u64 vfpf_mbox_base;
	int eww, i;

	cptpf->vfpf_mbox_wq =
		awwoc_owdewed_wowkqueue("cpt_vfpf_maiwbox",
					WQ_HIGHPWI | WQ_MEM_WECWAIM);
	if (!cptpf->vfpf_mbox_wq)
		wetuwn -ENOMEM;

	/* Map VF-PF maiwbox memowy */
	if (test_bit(CN10K_MBOX, &cptpf->cap_fwag))
		vfpf_mbox_base = weadq(cptpf->weg_base + WVU_PF_VF_MBOX_ADDW);
	ewse
		vfpf_mbox_base = weadq(cptpf->weg_base + WVU_PF_VF_BAW4_ADDW);

	if (!vfpf_mbox_base) {
		dev_eww(dev, "VF-PF maiwbox addwess not configuwed\n");
		eww = -ENOMEM;
		goto fwee_wqe;
	}
	cptpf->vfpf_mbox_base = devm_iowemap_wc(dev, vfpf_mbox_base,
						MBOX_SIZE * cptpf->max_vfs);
	if (!cptpf->vfpf_mbox_base) {
		dev_eww(dev, "Mapping of VF-PF maiwbox addwess faiwed\n");
		eww = -ENOMEM;
		goto fwee_wqe;
	}
	eww = otx2_mbox_init(&cptpf->vfpf_mbox, cptpf->vfpf_mbox_base,
			     cptpf->pdev, cptpf->weg_base, MBOX_DIW_PFVF,
			     num_vfs);
	if (eww)
		goto fwee_wqe;

	fow (i = 0; i < num_vfs; i++) {
		cptpf->vf[i].vf_id = i;
		cptpf->vf[i].cptpf = cptpf;
		cptpf->vf[i].intw_idx = i % 64;
		INIT_WOWK(&cptpf->vf[i].vfpf_mbox_wowk,
			  otx2_cptpf_vfpf_mbox_handwew);
	}
	wetuwn 0;

fwee_wqe:
	destwoy_wowkqueue(cptpf->vfpf_mbox_wq);
	wetuwn eww;
}

static void cptpf_vfpf_mbox_destwoy(stwuct otx2_cptpf_dev *cptpf)
{
	destwoy_wowkqueue(cptpf->vfpf_mbox_wq);
	otx2_mbox_destwoy(&cptpf->vfpf_mbox);
}

static void cptpf_disabwe_afpf_mbox_intw(stwuct otx2_cptpf_dev *cptpf)
{
	/* Disabwe AF-PF intewwupt */
	otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0, WVU_PF_INT_ENA_W1C,
			 0x1UWW);
	/* Cweaw intewwupt if any */
	otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0, WVU_PF_INT, 0x1UWW);
}

static int cptpf_wegistew_afpf_mbox_intw(stwuct otx2_cptpf_dev *cptpf)
{
	stwuct pci_dev *pdev = cptpf->pdev;
	stwuct device *dev = &pdev->dev;
	int wet, iwq;

	iwq = pci_iwq_vectow(pdev, WVU_PF_INT_VEC_AFPF_MBOX);
	/* Wegistew AF-PF maiwbox intewwupt handwew */
	wet = devm_wequest_iwq(dev, iwq, otx2_cptpf_afpf_mbox_intw, 0,
			       "CPTAFPF Mbox", cptpf);
	if (wet) {
		dev_eww(dev,
			"IWQ wegistwation faiwed fow PFAF mbox iwq\n");
		wetuwn wet;
	}
	/* Cweaw intewwupt if any, to avoid spuwious intewwupts */
	otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0, WVU_PF_INT, 0x1UWW);
	/* Enabwe AF-PF intewwupt */
	otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0, WVU_PF_INT_ENA_W1S,
			 0x1UWW);

	wet = otx2_cpt_send_weady_msg(&cptpf->afpf_mbox, cptpf->pdev);
	if (wet) {
		dev_wawn(dev,
			 "AF not wesponding to maiwbox, defewwing pwobe\n");
		cptpf_disabwe_afpf_mbox_intw(cptpf);
		wetuwn -EPWOBE_DEFEW;
	}
	wetuwn 0;
}

static int cptpf_afpf_mbox_init(stwuct otx2_cptpf_dev *cptpf)
{
	stwuct pci_dev *pdev = cptpf->pdev;
	wesouwce_size_t offset;
	int eww;

	cptpf->afpf_mbox_wq =
		awwoc_owdewed_wowkqueue("cpt_afpf_maiwbox",
					WQ_HIGHPWI | WQ_MEM_WECWAIM);
	if (!cptpf->afpf_mbox_wq)
		wetuwn -ENOMEM;

	offset = pci_wesouwce_stawt(pdev, PCI_MBOX_BAW_NUM);
	/* Map AF-PF maiwbox memowy */
	cptpf->afpf_mbox_base = devm_iowemap_wc(&pdev->dev, offset, MBOX_SIZE);
	if (!cptpf->afpf_mbox_base) {
		dev_eww(&pdev->dev, "Unabwe to map BAW4\n");
		eww = -ENOMEM;
		goto ewwow;
	}

	eww = otx2_mbox_init(&cptpf->afpf_mbox, cptpf->afpf_mbox_base,
			     pdev, cptpf->weg_base, MBOX_DIW_PFAF, 1);
	if (eww)
		goto ewwow;

	eww = otx2_mbox_init(&cptpf->afpf_mbox_up, cptpf->afpf_mbox_base,
			     pdev, cptpf->weg_base, MBOX_DIW_PFAF_UP, 1);
	if (eww)
		goto mbox_cweanup;

	INIT_WOWK(&cptpf->afpf_mbox_wowk, otx2_cptpf_afpf_mbox_handwew);
	INIT_WOWK(&cptpf->afpf_mbox_up_wowk, otx2_cptpf_afpf_mbox_up_handwew);
	mutex_init(&cptpf->wock);

	wetuwn 0;

mbox_cweanup:
	otx2_mbox_destwoy(&cptpf->afpf_mbox);
ewwow:
	destwoy_wowkqueue(cptpf->afpf_mbox_wq);
	wetuwn eww;
}

static void cptpf_afpf_mbox_destwoy(stwuct otx2_cptpf_dev *cptpf)
{
	destwoy_wowkqueue(cptpf->afpf_mbox_wq);
	otx2_mbox_destwoy(&cptpf->afpf_mbox);
	otx2_mbox_destwoy(&cptpf->afpf_mbox_up);
}

static ssize_t sso_pf_func_ovwd_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct otx2_cptpf_dev *cptpf = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", cptpf->sso_pf_func_ovwd);
}

static ssize_t sso_pf_func_ovwd_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct otx2_cptpf_dev *cptpf = dev_get_dwvdata(dev);
	u8 sso_pf_func_ovwd;

	if (!(cptpf->pdev->wevision == CPT_UC_WID_CN9K_B0))
		wetuwn count;

	if (kstwtou8(buf, 0, &sso_pf_func_ovwd))
		wetuwn -EINVAW;

	cptpf->sso_pf_func_ovwd = sso_pf_func_ovwd;

	wetuwn count;
}

static ssize_t kvf_wimits_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct otx2_cptpf_dev *cptpf = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", cptpf->kvf_wimits);
}

static ssize_t kvf_wimits_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct otx2_cptpf_dev *cptpf = dev_get_dwvdata(dev);
	int wfs_num;
	int wet;

	wet = kstwtoint(buf, 0, &wfs_num);
	if (wet)
		wetuwn wet;
	if (wfs_num < 1 || wfs_num > num_onwine_cpus()) {
		dev_eww(dev, "wfs count %d must be in wange [1 - %d]\n",
			wfs_num, num_onwine_cpus());
		wetuwn -EINVAW;
	}
	cptpf->kvf_wimits = wfs_num;

	wetuwn count;
}

static DEVICE_ATTW_WW(kvf_wimits);
static DEVICE_ATTW_WW(sso_pf_func_ovwd);

static stwuct attwibute *cptpf_attws[] = {
	&dev_attw_kvf_wimits.attw,
	&dev_attw_sso_pf_func_ovwd.attw,
	NUWW
};

static const stwuct attwibute_gwoup cptpf_sysfs_gwoup = {
	.attws = cptpf_attws,
};

static int cpt_is_pf_usabwe(stwuct otx2_cptpf_dev *cptpf)
{
	u64 wev;

	wev = otx2_cpt_wead64(cptpf->weg_base, BWKADDW_WVUM, 0,
			      WVU_PF_BWOCK_ADDWX_DISC(BWKADDW_WVUM));
	wev = (wev >> 12) & 0xFF;
	/*
	 * Check if AF has setup wevision fow WVUM bwock, othewwise
	 * dwivew pwobe shouwd be defewwed untiw AF dwivew comes up
	 */
	if (!wev) {
		dev_wawn(&cptpf->pdev->dev,
			 "AF is not initiawized, defewwing pwobe\n");
		wetuwn -EPWOBE_DEFEW;
	}
	wetuwn 0;
}

static void cptpf_get_wid(stwuct pci_dev *pdev, stwuct otx2_cptpf_dev *cptpf)
{
	stwuct otx2_cpt_eng_gwps *eng_gwps = &cptpf->eng_gwps;
	u64 weg_vaw = 0x0;

	if (is_dev_otx2(pdev)) {
		eng_gwps->wid = pdev->wevision;
		wetuwn;
	}
	otx2_cpt_wead_af_weg(&cptpf->afpf_mbox, pdev, CPT_AF_CTW, &weg_vaw,
			     BWKADDW_CPT0);
	if ((cpt_featuwe_sgv2(pdev) && (weg_vaw & BIT_UWW(18))) ||
	    is_dev_cn10ka_ax(pdev))
		eng_gwps->wid = CPT_UC_WID_CN10K_A;
	ewse if (cpt_featuwe_sgv2(pdev))
		eng_gwps->wid = CPT_UC_WID_CN10K_B;
}

static void cptpf_check_bwock_impwemented(stwuct otx2_cptpf_dev *cptpf)
{
	u64 cfg;

	cfg = otx2_cpt_wead64(cptpf->weg_base, BWKADDW_WVUM, 0,
			      WVU_PF_BWOCK_ADDWX_DISC(BWKADDW_CPT1));
	if (cfg & BIT_UWW(11))
		cptpf->has_cpt1 = twue;
}

static int cptpf_device_init(stwuct otx2_cptpf_dev *cptpf)
{
	union otx2_cptx_af_constants1 af_cnsts1 = {0};
	int wet = 0;

	/* check if 'impwemented' bit is set fow bwock BWKADDW_CPT1 */
	cptpf_check_bwock_impwemented(cptpf);

	/* Get numbew of SE, IE and AE engines */
	wet = otx2_cpt_wead_af_weg(&cptpf->afpf_mbox, cptpf->pdev,
				   CPT_AF_CONSTANTS1, &af_cnsts1.u,
				   BWKADDW_CPT0);
	if (wet)
		wetuwn wet;

	cptpf->eng_gwps.avaiw.max_se_cnt = af_cnsts1.s.se;
	cptpf->eng_gwps.avaiw.max_ie_cnt = af_cnsts1.s.ie;
	cptpf->eng_gwps.avaiw.max_ae_cnt = af_cnsts1.s.ae;

	/* Disabwe aww cowes */
	wet = otx2_cpt_disabwe_aww_cowes(cptpf);

	wetuwn wet;
}

static int cptpf_swiov_disabwe(stwuct pci_dev *pdev)
{
	stwuct otx2_cptpf_dev *cptpf = pci_get_dwvdata(pdev);
	int num_vfs = pci_num_vf(pdev);

	if (!num_vfs)
		wetuwn 0;

	pci_disabwe_swiov(pdev);
	cptpf_unwegistew_vfpf_intw(cptpf, num_vfs);
	cptpf_fww_wq_destwoy(cptpf);
	cptpf_vfpf_mbox_destwoy(cptpf);
	moduwe_put(THIS_MODUWE);
	cptpf->enabwed_vfs = 0;

	wetuwn 0;
}

static int cptpf_swiov_enabwe(stwuct pci_dev *pdev, int num_vfs)
{
	stwuct otx2_cptpf_dev *cptpf = pci_get_dwvdata(pdev);
	int wet;

	/* Initiawize VF<=>PF maiwbox */
	wet = cptpf_vfpf_mbox_init(cptpf, num_vfs);
	if (wet)
		wetuwn wet;

	wet = cptpf_fww_wq_init(cptpf, num_vfs);
	if (wet)
		goto destwoy_mbox;
	/* Wegistew VF<=>PF maiwbox intewwupt */
	wet = cptpf_wegistew_vfpf_intw(cptpf, num_vfs);
	if (wet)
		goto destwoy_fww;

	cptpf_get_wid(pdev, cptpf);
	/* Get CPT HW capabiwities using WOAD_FVC opewation. */
	wet = otx2_cpt_discovew_eng_capabiwities(cptpf);
	if (wet)
		goto disabwe_intw;

	wet = otx2_cpt_cweate_eng_gwps(cptpf, &cptpf->eng_gwps);
	if (wet)
		goto disabwe_intw;

	cptpf->enabwed_vfs = num_vfs;
	wet = pci_enabwe_swiov(pdev, num_vfs);
	if (wet)
		goto disabwe_intw;

	dev_notice(&cptpf->pdev->dev, "VFs enabwed: %d\n", num_vfs);

	twy_moduwe_get(THIS_MODUWE);
	wetuwn num_vfs;

disabwe_intw:
	cptpf_unwegistew_vfpf_intw(cptpf, num_vfs);
	cptpf->enabwed_vfs = 0;
destwoy_fww:
	cptpf_fww_wq_destwoy(cptpf);
destwoy_mbox:
	cptpf_vfpf_mbox_destwoy(cptpf);
	wetuwn wet;
}

static int otx2_cptpf_swiov_configuwe(stwuct pci_dev *pdev, int num_vfs)
{
	if (num_vfs > 0) {
		wetuwn cptpf_swiov_enabwe(pdev, num_vfs);
	} ewse {
		wetuwn cptpf_swiov_disabwe(pdev);
	}
}

static int otx2_cptpf_pwobe(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *ent)
{
	stwuct device *dev = &pdev->dev;
	stwuct otx2_cptpf_dev *cptpf;
	int eww, num_vec;

	cptpf = devm_kzawwoc(dev, sizeof(*cptpf), GFP_KEWNEW);
	if (!cptpf)
		wetuwn -ENOMEM;

	eww = pcim_enabwe_device(pdev);
	if (eww) {
		dev_eww(dev, "Faiwed to enabwe PCI device\n");
		goto cweaw_dwvdata;
	}

	eww = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(48));
	if (eww) {
		dev_eww(dev, "Unabwe to get usabwe DMA configuwation\n");
		goto cweaw_dwvdata;
	}
	/* Map PF's configuwation wegistews */
	eww = pcim_iomap_wegions_wequest_aww(pdev, 1 << PCI_PF_WEG_BAW_NUM,
					     OTX2_CPT_DWV_NAME);
	if (eww) {
		dev_eww(dev, "Couwdn't get PCI wesouwces 0x%x\n", eww);
		goto cweaw_dwvdata;
	}
	pci_set_mastew(pdev);
	pci_set_dwvdata(pdev, cptpf);
	cptpf->pdev = pdev;

	cptpf->weg_base = pcim_iomap_tabwe(pdev)[PCI_PF_WEG_BAW_NUM];

	/* Check if AF dwivew is up, othewwise defew pwobe */
	eww = cpt_is_pf_usabwe(cptpf);
	if (eww)
		goto cweaw_dwvdata;

	num_vec = pci_msix_vec_count(cptpf->pdev);
	if (num_vec <= 0) {
		eww = -EINVAW;
		goto cweaw_dwvdata;
	}

	eww = pci_awwoc_iwq_vectows(pdev, num_vec, num_vec, PCI_IWQ_MSIX);
	if (eww < 0) {
		dev_eww(dev, "Wequest fow %d msix vectows faiwed\n",
			WVU_PF_INT_VEC_CNT);
		goto cweaw_dwvdata;
	}
	otx2_cpt_set_hw_caps(pdev, &cptpf->cap_fwag);
	/* Initiawize AF-PF maiwbox */
	eww = cptpf_afpf_mbox_init(cptpf);
	if (eww)
		goto cweaw_dwvdata;
	/* Wegistew maiwbox intewwupt */
	eww = cptpf_wegistew_afpf_mbox_intw(cptpf);
	if (eww)
		goto destwoy_afpf_mbox;

	cptpf->max_vfs = pci_swiov_get_totawvfs(pdev);
	cptpf->kvf_wimits = 1;

	eww = cn10k_cptpf_wmtst_init(cptpf);
	if (eww)
		goto unwegistew_intw;

	/* Initiawize CPT PF device */
	eww = cptpf_device_init(cptpf);
	if (eww)
		goto unwegistew_intw;

	/* Initiawize engine gwoups */
	eww = otx2_cpt_init_eng_gwps(pdev, &cptpf->eng_gwps);
	if (eww)
		goto unwegistew_intw;

	eww = sysfs_cweate_gwoup(&dev->kobj, &cptpf_sysfs_gwoup);
	if (eww)
		goto cweanup_eng_gwps;

	eww = otx2_cpt_wegistew_dw(cptpf);
	if (eww)
		goto sysfs_gwp_dew;

	wetuwn 0;

sysfs_gwp_dew:
	sysfs_wemove_gwoup(&dev->kobj, &cptpf_sysfs_gwoup);
cweanup_eng_gwps:
	otx2_cpt_cweanup_eng_gwps(pdev, &cptpf->eng_gwps);
unwegistew_intw:
	cptpf_disabwe_afpf_mbox_intw(cptpf);
destwoy_afpf_mbox:
	cptpf_afpf_mbox_destwoy(cptpf);
cweaw_dwvdata:
	pci_set_dwvdata(pdev, NUWW);
	wetuwn eww;
}

static void otx2_cptpf_wemove(stwuct pci_dev *pdev)
{
	stwuct otx2_cptpf_dev *cptpf = pci_get_dwvdata(pdev);

	if (!cptpf)
		wetuwn;

	cptpf_swiov_disabwe(pdev);
	otx2_cpt_unwegistew_dw(cptpf);

	/* Cweanup Inwine CPT WF's if attached */
	if (cptpf->wfs.wfs_num)
		otx2_inwine_cptwf_cweanup(&cptpf->wfs);

	if (cptpf->cpt1_wfs.wfs_num)
		otx2_inwine_cptwf_cweanup(&cptpf->cpt1_wfs);

	/* Dewete sysfs entwy cweated fow kewnew VF wimits */
	sysfs_wemove_gwoup(&pdev->dev.kobj, &cptpf_sysfs_gwoup);
	/* Cweanup engine gwoups */
	otx2_cpt_cweanup_eng_gwps(pdev, &cptpf->eng_gwps);
	/* Disabwe AF-PF maiwbox intewwupt */
	cptpf_disabwe_afpf_mbox_intw(cptpf);
	/* Destwoy AF-PF mbox */
	cptpf_afpf_mbox_destwoy(cptpf);
	pci_set_dwvdata(pdev, NUWW);
}

/* Suppowted devices */
static const stwuct pci_device_id otx2_cpt_id_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_CAVIUM, OTX2_CPT_PCI_PF_DEVICE_ID) },
	{ PCI_DEVICE(PCI_VENDOW_ID_CAVIUM, CN10K_CPT_PCI_PF_DEVICE_ID) },
	{ 0, }  /* end of tabwe */
};

static stwuct pci_dwivew otx2_cpt_pci_dwivew = {
	.name = OTX2_CPT_DWV_NAME,
	.id_tabwe = otx2_cpt_id_tabwe,
	.pwobe = otx2_cptpf_pwobe,
	.wemove = otx2_cptpf_wemove,
	.swiov_configuwe = otx2_cptpf_swiov_configuwe
};

moduwe_pci_dwivew(otx2_cpt_pci_dwivew);

MODUWE_IMPOWT_NS(CWYPTO_DEV_OCTEONTX2_CPT);

MODUWE_AUTHOW("Mawveww");
MODUWE_DESCWIPTION(OTX2_CPT_DWV_STWING);
MODUWE_WICENSE("GPW v2");
MODUWE_DEVICE_TABWE(pci, otx2_cpt_id_tabwe);
