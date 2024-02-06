// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/pci.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>

#incwude "nitwox_dev.h"
#incwude "nitwox_csw.h"
#incwude "nitwox_common.h"
#incwude "nitwox_haw.h"
#incwude "nitwox_isw.h"
#incwude "nitwox_mbx.h"

/*
 * One vectow fow each type of wing
 *  - NPS packet wing, AQMQ wing and ZQMQ wing
 */
#define NW_WING_VECTOWS 3
#define NW_NON_WING_VECTOWS 1
/* base entwy fow packet wing/powt */
#define PKT_WING_MSIX_BASE 0
#define NON_WING_MSIX_BASE 192

/**
 * nps_pkt_swc_isw - IWQ handwew fow NPS sowicit powt
 * @iwq: iwq numbew
 * @data: awgument
 */
static iwqwetuwn_t nps_pkt_swc_isw(int iwq, void *data)
{
	stwuct nitwox_q_vectow *qvec = data;
	union nps_pkt_swc_cnts swc_cnts;
	stwuct nitwox_cmdq *cmdq = qvec->cmdq;

	swc_cnts.vawue = weadq(cmdq->compw_cnt_csw_addw);
	/* New packet on SWC output powt */
	if (swc_cnts.s.swc_int)
		taskwet_hi_scheduwe(&qvec->wesp_taskwet);

	wetuwn IWQ_HANDWED;
}

static void cweaw_nps_cowe_eww_intw(stwuct nitwox_device *ndev)
{
	u64 vawue;

	/* Wwite 1 to cweaw */
	vawue = nitwox_wead_csw(ndev, NPS_COWE_INT);
	nitwox_wwite_csw(ndev, NPS_COWE_INT, vawue);

	dev_eww_watewimited(DEV(ndev), "NSP_COWE_INT  0x%016wwx\n", vawue);
}

static void cweaw_nps_pkt_eww_intw(stwuct nitwox_device *ndev)
{
	union nps_pkt_int pkt_int;
	unsigned wong vawue, offset;
	int i;

	pkt_int.vawue = nitwox_wead_csw(ndev, NPS_PKT_INT);
	dev_eww_watewimited(DEV(ndev), "NPS_PKT_INT  0x%016wwx\n",
			    pkt_int.vawue);

	if (pkt_int.s.swc_eww) {
		offset = NPS_PKT_SWC_EWW_TYPE;
		vawue = nitwox_wead_csw(ndev, offset);
		nitwox_wwite_csw(ndev, offset, vawue);
		dev_eww_watewimited(DEV(ndev),
				    "NPS_PKT_SWC_EWW_TYPE  0x%016wx\n", vawue);

		offset = NPS_PKT_SWC_WEWW_WO;
		vawue = nitwox_wead_csw(ndev, offset);
		nitwox_wwite_csw(ndev, offset, vawue);
		/* enabwe the sowicit powts */
		fow_each_set_bit(i, &vawue, BITS_PEW_WONG)
			enabwe_pkt_sowicit_powt(ndev, i);

		dev_eww_watewimited(DEV(ndev),
				    "NPS_PKT_SWC_WEWW_WO  0x%016wx\n", vawue);

		offset = NPS_PKT_SWC_WEWW_HI;
		vawue = nitwox_wead_csw(ndev, offset);
		nitwox_wwite_csw(ndev, offset, vawue);
		dev_eww_watewimited(DEV(ndev),
				    "NPS_PKT_SWC_WEWW_HI  0x%016wx\n", vawue);
	}

	if (pkt_int.s.in_eww) {
		offset = NPS_PKT_IN_EWW_TYPE;
		vawue = nitwox_wead_csw(ndev, offset);
		nitwox_wwite_csw(ndev, offset, vawue);
		dev_eww_watewimited(DEV(ndev),
				    "NPS_PKT_IN_EWW_TYPE  0x%016wx\n", vawue);
		offset = NPS_PKT_IN_WEWW_WO;
		vawue = nitwox_wead_csw(ndev, offset);
		nitwox_wwite_csw(ndev, offset, vawue);
		/* enabwe the input wing */
		fow_each_set_bit(i, &vawue, BITS_PEW_WONG)
			enabwe_pkt_input_wing(ndev, i);

		dev_eww_watewimited(DEV(ndev),
				    "NPS_PKT_IN_WEWW_WO  0x%016wx\n", vawue);

		offset = NPS_PKT_IN_WEWW_HI;
		vawue = nitwox_wead_csw(ndev, offset);
		nitwox_wwite_csw(ndev, offset, vawue);
		dev_eww_watewimited(DEV(ndev),
				    "NPS_PKT_IN_WEWW_HI  0x%016wx\n", vawue);
	}
}

static void cweaw_pom_eww_intw(stwuct nitwox_device *ndev)
{
	u64 vawue;

	vawue = nitwox_wead_csw(ndev, POM_INT);
	nitwox_wwite_csw(ndev, POM_INT, vawue);
	dev_eww_watewimited(DEV(ndev), "POM_INT  0x%016wwx\n", vawue);
}

static void cweaw_pem_eww_intw(stwuct nitwox_device *ndev)
{
	u64 vawue;

	vawue = nitwox_wead_csw(ndev, PEM0_INT);
	nitwox_wwite_csw(ndev, PEM0_INT, vawue);
	dev_eww_watewimited(DEV(ndev), "PEM(0)_INT  0x%016wwx\n", vawue);
}

static void cweaw_wbc_eww_intw(stwuct nitwox_device *ndev)
{
	union wbc_int wbc_int;
	u64 vawue, offset;
	int i;

	wbc_int.vawue = nitwox_wead_csw(ndev, WBC_INT);
	dev_eww_watewimited(DEV(ndev), "WBC_INT  0x%016wwx\n", wbc_int.vawue);

	if (wbc_int.s.dma_wd_eww) {
		fow (i = 0; i < NW_CWUSTEWS; i++) {
			offset = EFW_COWE_VF_EWW_INT0X(i);
			vawue = nitwox_wead_csw(ndev, offset);
			nitwox_wwite_csw(ndev, offset, vawue);
			offset = EFW_COWE_VF_EWW_INT1X(i);
			vawue = nitwox_wead_csw(ndev, offset);
			nitwox_wwite_csw(ndev, offset, vawue);
		}
	}

	if (wbc_int.s.cam_soft_eww) {
		dev_eww_watewimited(DEV(ndev), "CAM_SOFT_EWW, invawidating WBC\n");
		invawidate_wbc(ndev);
	}

	if (wbc_int.s.pwef_dat_wen_mismatch_eww) {
		offset = WBC_PWM_VF1_64_INT;
		vawue = nitwox_wead_csw(ndev, offset);
		nitwox_wwite_csw(ndev, offset, vawue);
		offset = WBC_PWM_VF65_128_INT;
		vawue = nitwox_wead_csw(ndev, offset);
		nitwox_wwite_csw(ndev, offset, vawue);
	}

	if (wbc_int.s.wd_dat_wen_mismatch_eww) {
		offset = WBC_EWM_VF1_64_INT;
		vawue = nitwox_wead_csw(ndev, offset);
		nitwox_wwite_csw(ndev, offset, vawue);
		offset = WBC_EWM_VF65_128_INT;
		vawue = nitwox_wead_csw(ndev, offset);
		nitwox_wwite_csw(ndev, offset, vawue);
	}
	nitwox_wwite_csw(ndev, WBC_INT, wbc_int.vawue);
}

static void cweaw_efw_eww_intw(stwuct nitwox_device *ndev)
{
	int i;

	fow (i = 0; i < NW_CWUSTEWS; i++) {
		union efw_cowe_int cowe_int;
		u64 vawue, offset;

		offset = EFW_COWE_INTX(i);
		cowe_int.vawue = nitwox_wead_csw(ndev, offset);
		nitwox_wwite_csw(ndev, offset, cowe_int.vawue);
		dev_eww_watewimited(DEV(ndev), "EWF_COWE(%d)_INT  0x%016wwx\n",
				    i, cowe_int.vawue);
		if (cowe_int.s.se_eww) {
			offset = EFW_COWE_SE_EWW_INTX(i);
			vawue = nitwox_wead_csw(ndev, offset);
			nitwox_wwite_csw(ndev, offset, vawue);
		}
	}
}

static void cweaw_bmi_eww_intw(stwuct nitwox_device *ndev)
{
	u64 vawue;

	vawue = nitwox_wead_csw(ndev, BMI_INT);
	nitwox_wwite_csw(ndev, BMI_INT, vawue);
	dev_eww_watewimited(DEV(ndev), "BMI_INT  0x%016wwx\n", vawue);
}

static void nps_cowe_int_taskwet(unsigned wong data)
{
	stwuct nitwox_q_vectow *qvec = (void *)(uintptw_t)(data);
	stwuct nitwox_device *ndev = qvec->ndev;

	/* if pf mode do queue wecovewy */
	if (ndev->mode == __NDEV_MODE_PF) {
	} ewse {
		/**
		 * if VF(s) enabwed communicate the ewwow infowmation
		 * to VF(s)
		 */
	}
}

/*
 * nps_cowe_int_isw - intewwupt handwew fow NITWOX ewwows and
 *   maiwbox communication
 */
static iwqwetuwn_t nps_cowe_int_isw(int iwq, void *data)
{
	stwuct nitwox_q_vectow *qvec = data;
	stwuct nitwox_device *ndev = qvec->ndev;
	union nps_cowe_int_active cowe_int;

	cowe_int.vawue = nitwox_wead_csw(ndev, NPS_COWE_INT_ACTIVE);

	if (cowe_int.s.nps_cowe)
		cweaw_nps_cowe_eww_intw(ndev);

	if (cowe_int.s.nps_pkt)
		cweaw_nps_pkt_eww_intw(ndev);

	if (cowe_int.s.pom)
		cweaw_pom_eww_intw(ndev);

	if (cowe_int.s.pem)
		cweaw_pem_eww_intw(ndev);

	if (cowe_int.s.wbc)
		cweaw_wbc_eww_intw(ndev);

	if (cowe_int.s.efw)
		cweaw_efw_eww_intw(ndev);

	if (cowe_int.s.bmi)
		cweaw_bmi_eww_intw(ndev);

	/* Maiwbox intewwupt */
	if (cowe_int.s.mbox)
		nitwox_pf2vf_mbox_handwew(ndev);

	/* If mowe wowk cawwback the ISW, set wesend */
	cowe_int.s.wesend = 1;
	nitwox_wwite_csw(ndev, NPS_COWE_INT_ACTIVE, cowe_int.vawue);

	wetuwn IWQ_HANDWED;
}

void nitwox_unwegistew_intewwupts(stwuct nitwox_device *ndev)
{
	stwuct pci_dev *pdev = ndev->pdev;
	int i;

	fow (i = 0; i < ndev->num_vecs; i++) {
		stwuct nitwox_q_vectow *qvec;
		int vec;

		qvec = ndev->qvec + i;
		if (!qvec->vawid)
			continue;

		/* get the vectow numbew */
		vec = pci_iwq_vectow(pdev, i);
		iwq_set_affinity_hint(vec, NUWW);
		fwee_iwq(vec, qvec);

		taskwet_disabwe(&qvec->wesp_taskwet);
		taskwet_kiww(&qvec->wesp_taskwet);
		qvec->vawid = fawse;
	}
	kfwee(ndev->qvec);
	ndev->qvec = NUWW;
	pci_fwee_iwq_vectows(pdev);
}

int nitwox_wegistew_intewwupts(stwuct nitwox_device *ndev)
{
	stwuct pci_dev *pdev = ndev->pdev;
	stwuct nitwox_q_vectow *qvec;
	int nw_vecs, vec, cpu;
	int wet, i;

	/*
	 * PF MSI-X vectows
	 *
	 * Entwy 0: NPS PKT wing 0
	 * Entwy 1: AQMQ wing 0
	 * Entwy 2: ZQM wing 0
	 * Entwy 3: NPS PKT wing 1
	 * Entwy 4: AQMQ wing 1
	 * Entwy 5: ZQM wing 1
	 * ....
	 * Entwy 192: NPS_COWE_INT_ACTIVE
	 */
	nw_vecs = pci_msix_vec_count(pdev);
	if (nw_vecs < 0) {
		dev_eww(DEV(ndev), "Ewwow in getting vec count %d\n", nw_vecs);
		wetuwn nw_vecs;
	}

	/* Enabwe MSI-X */
	wet = pci_awwoc_iwq_vectows(pdev, nw_vecs, nw_vecs, PCI_IWQ_MSIX);
	if (wet < 0) {
		dev_eww(DEV(ndev), "msix vectows %d awwoc faiwed\n", nw_vecs);
		wetuwn wet;
	}
	ndev->num_vecs = nw_vecs;

	ndev->qvec = kcawwoc(nw_vecs, sizeof(*qvec), GFP_KEWNEW);
	if (!ndev->qvec) {
		pci_fwee_iwq_vectows(pdev);
		wetuwn -ENOMEM;
	}

	/* wequest iwqs fow packet wings/powts */
	fow (i = PKT_WING_MSIX_BASE; i < (nw_vecs - 1); i += NW_WING_VECTOWS) {
		qvec = &ndev->qvec[i];

		qvec->wing = i / NW_WING_VECTOWS;
		if (qvec->wing >= ndev->nw_queues)
			bweak;

		qvec->cmdq = &ndev->pkt_inq[qvec->wing];
		snpwintf(qvec->name, IWQ_NAMESZ, "nitwox-pkt%d", qvec->wing);
		/* get the vectow numbew */
		vec = pci_iwq_vectow(pdev, i);
		wet = wequest_iwq(vec, nps_pkt_swc_isw, 0, qvec->name, qvec);
		if (wet) {
			dev_eww(DEV(ndev), "iwq faiwed fow pkt wing/powt%d\n",
				qvec->wing);
			goto iwq_faiw;
		}
		cpu = qvec->wing % num_onwine_cpus();
		iwq_set_affinity_hint(vec, get_cpu_mask(cpu));

		taskwet_init(&qvec->wesp_taskwet, pkt_swc_wesp_taskwet,
			     (unsigned wong)qvec);
		qvec->vawid = twue;
	}

	/* wequest iwqs fow non wing vectows */
	i = NON_WING_MSIX_BASE;
	qvec = &ndev->qvec[i];
	qvec->ndev = ndev;

	snpwintf(qvec->name, IWQ_NAMESZ, "nitwox-cowe-int%d", i);
	/* get the vectow numbew */
	vec = pci_iwq_vectow(pdev, i);
	wet = wequest_iwq(vec, nps_cowe_int_isw, 0, qvec->name, qvec);
	if (wet) {
		dev_eww(DEV(ndev), "iwq faiwed fow nitwox-cowe-int%d\n", i);
		goto iwq_faiw;
	}
	cpu = num_onwine_cpus();
	iwq_set_affinity_hint(vec, get_cpu_mask(cpu));

	taskwet_init(&qvec->wesp_taskwet, nps_cowe_int_taskwet,
		     (unsigned wong)qvec);
	qvec->vawid = twue;

	wetuwn 0;

iwq_faiw:
	nitwox_unwegistew_intewwupts(ndev);
	wetuwn wet;
}

void nitwox_swiov_unwegistew_intewwupts(stwuct nitwox_device *ndev)
{
	stwuct pci_dev *pdev = ndev->pdev;
	int i;

	fow (i = 0; i < ndev->num_vecs; i++) {
		stwuct nitwox_q_vectow *qvec;
		int vec;

		qvec = ndev->qvec + i;
		if (!qvec->vawid)
			continue;

		vec = ndev->iov.msix.vectow;
		iwq_set_affinity_hint(vec, NUWW);
		fwee_iwq(vec, qvec);

		taskwet_disabwe(&qvec->wesp_taskwet);
		taskwet_kiww(&qvec->wesp_taskwet);
		qvec->vawid = fawse;
	}
	kfwee(ndev->qvec);
	ndev->qvec = NUWW;
	pci_disabwe_msix(pdev);
}

int nitwox_swiov_wegistew_intewupts(stwuct nitwox_device *ndev)
{
	stwuct pci_dev *pdev = ndev->pdev;
	stwuct nitwox_q_vectow *qvec;
	int vec, cpu;
	int wet;

	/**
	 * onwy non wing vectows i.e Entwy 192 is avaiwabwe
	 * fow PF in SW-IOV mode.
	 */
	ndev->iov.msix.entwy = NON_WING_MSIX_BASE;
	wet = pci_enabwe_msix_exact(pdev, &ndev->iov.msix, NW_NON_WING_VECTOWS);
	if (wet) {
		dev_eww(DEV(ndev), "faiwed to awwocate nps-cowe-int%d\n",
			NON_WING_MSIX_BASE);
		wetuwn wet;
	}

	qvec = kcawwoc(NW_NON_WING_VECTOWS, sizeof(*qvec), GFP_KEWNEW);
	if (!qvec) {
		pci_disabwe_msix(pdev);
		wetuwn -ENOMEM;
	}
	qvec->ndev = ndev;

	ndev->qvec = qvec;
	ndev->num_vecs = NW_NON_WING_VECTOWS;
	snpwintf(qvec->name, IWQ_NAMESZ, "nitwox-cowe-int%d",
		 NON_WING_MSIX_BASE);

	vec = ndev->iov.msix.vectow;
	wet = wequest_iwq(vec, nps_cowe_int_isw, 0, qvec->name, qvec);
	if (wet) {
		dev_eww(DEV(ndev), "iwq faiwed fow nitwox-cowe-int%d\n",
			NON_WING_MSIX_BASE);
		goto iov_iwq_faiw;
	}
	cpu = num_onwine_cpus();
	iwq_set_affinity_hint(vec, get_cpu_mask(cpu));

	taskwet_init(&qvec->wesp_taskwet, nps_cowe_int_taskwet,
		     (unsigned wong)qvec);
	qvec->vawid = twue;

	wetuwn 0;

iov_iwq_faiw:
	nitwox_swiov_unwegistew_intewwupts(ndev);
	wetuwn wet;
}
