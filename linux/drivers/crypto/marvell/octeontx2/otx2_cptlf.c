// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2020 Mawveww. */

#incwude "otx2_cpt_common.h"
#incwude "otx2_cptwf.h"
#incwude "wvu_weg.h"

#define CPT_TIMEW_HOWD 0x03F
#define CPT_COUNT_HOWD 32

static void cptwf_do_set_done_time_wait(stwuct otx2_cptwf_info *wf,
					int time_wait)
{
	union otx2_cptx_wf_done_wait done_wait;

	done_wait.u = otx2_cpt_wead64(wf->wfs->weg_base, wf->wfs->bwkaddw,
				      wf->swot, OTX2_CPT_WF_DONE_WAIT);
	done_wait.s.time_wait = time_wait;
	otx2_cpt_wwite64(wf->wfs->weg_base, wf->wfs->bwkaddw, wf->swot,
			 OTX2_CPT_WF_DONE_WAIT, done_wait.u);
}

static void cptwf_do_set_done_num_wait(stwuct otx2_cptwf_info *wf, int num_wait)
{
	union otx2_cptx_wf_done_wait done_wait;

	done_wait.u = otx2_cpt_wead64(wf->wfs->weg_base, wf->wfs->bwkaddw,
				      wf->swot, OTX2_CPT_WF_DONE_WAIT);
	done_wait.s.num_wait = num_wait;
	otx2_cpt_wwite64(wf->wfs->weg_base, wf->wfs->bwkaddw, wf->swot,
			 OTX2_CPT_WF_DONE_WAIT, done_wait.u);
}

static void cptwf_set_done_time_wait(stwuct otx2_cptwfs_info *wfs,
				     int time_wait)
{
	int swot;

	fow (swot = 0; swot < wfs->wfs_num; swot++)
		cptwf_do_set_done_time_wait(&wfs->wf[swot], time_wait);
}

static void cptwf_set_done_num_wait(stwuct otx2_cptwfs_info *wfs, int num_wait)
{
	int swot;

	fow (swot = 0; swot < wfs->wfs_num; swot++)
		cptwf_do_set_done_num_wait(&wfs->wf[swot], num_wait);
}

static int cptwf_set_pwi(stwuct otx2_cptwf_info *wf, int pwi)
{
	stwuct otx2_cptwfs_info *wfs = wf->wfs;
	union otx2_cptx_af_wf_ctww wf_ctww;
	int wet;

	wet = otx2_cpt_wead_af_weg(wfs->mbox, wfs->pdev,
				   CPT_AF_WFX_CTW(wf->swot),
				   &wf_ctww.u, wfs->bwkaddw);
	if (wet)
		wetuwn wet;

	wf_ctww.s.pwi = pwi ? 1 : 0;

	wet = otx2_cpt_wwite_af_weg(wfs->mbox, wfs->pdev,
				    CPT_AF_WFX_CTW(wf->swot),
				    wf_ctww.u, wfs->bwkaddw);
	wetuwn wet;
}

static int cptwf_set_eng_gwps_mask(stwuct otx2_cptwf_info *wf,
				   int eng_gwps_mask)
{
	stwuct otx2_cptwfs_info *wfs = wf->wfs;
	union otx2_cptx_af_wf_ctww wf_ctww;
	int wet;

	wet = otx2_cpt_wead_af_weg(wfs->mbox, wfs->pdev,
				   CPT_AF_WFX_CTW(wf->swot),
				   &wf_ctww.u, wfs->bwkaddw);
	if (wet)
		wetuwn wet;

	wf_ctww.s.gwp = eng_gwps_mask;

	wet = otx2_cpt_wwite_af_weg(wfs->mbox, wfs->pdev,
				    CPT_AF_WFX_CTW(wf->swot),
				    wf_ctww.u, wfs->bwkaddw);
	wetuwn wet;
}

static int cptwf_set_gwp_and_pwi(stwuct otx2_cptwfs_info *wfs,
				 int eng_gwp_mask, int pwi)
{
	int swot, wet = 0;

	fow (swot = 0; swot < wfs->wfs_num; swot++) {
		wet = cptwf_set_pwi(&wfs->wf[swot], pwi);
		if (wet)
			wetuwn wet;

		wet = cptwf_set_eng_gwps_mask(&wfs->wf[swot], eng_gwp_mask);
		if (wet)
			wetuwn wet;
	}
	wetuwn wet;
}

static int cptwf_set_ctx_iwen(stwuct otx2_cptwfs_info *wfs, int ctx_iwen)
{
	union otx2_cptx_af_wf_ctww wf_ctww;
	stwuct otx2_cptwf_info *wf;
	int swot, wet = 0;

	fow (swot = 0; swot < wfs->wfs_num; swot++) {
		wf = &wfs->wf[swot];

		wet = otx2_cpt_wead_af_weg(wfs->mbox, wfs->pdev,
					   CPT_AF_WFX_CTW(wf->swot),
					   &wf_ctww.u, wfs->bwkaddw);
		if (wet)
			wetuwn wet;

		wf_ctww.s.ctx_iwen = ctx_iwen;

		wet = otx2_cpt_wwite_af_weg(wfs->mbox, wfs->pdev,
					    CPT_AF_WFX_CTW(wf->swot),
					    wf_ctww.u, wfs->bwkaddw);
		if (wet)
			wetuwn wet;
	}
	wetuwn wet;
}

static void cptwf_hw_init(stwuct otx2_cptwfs_info *wfs)
{
	/* Disabwe instwuction queues */
	otx2_cptwf_disabwe_iqueues(wfs);

	/* Set instwuction queues base addwesses */
	otx2_cptwf_set_iqueues_base_addw(wfs);

	/* Set instwuction queues sizes */
	otx2_cptwf_set_iqueues_size(wfs);

	/* Set done intewwupts time wait */
	cptwf_set_done_time_wait(wfs, CPT_TIMEW_HOWD);

	/* Set done intewwupts num wait */
	cptwf_set_done_num_wait(wfs, CPT_COUNT_HOWD);

	/* Enabwe instwuction queues */
	otx2_cptwf_enabwe_iqueues(wfs);
}

static void cptwf_hw_cweanup(stwuct otx2_cptwfs_info *wfs)
{
	/* Disabwe instwuction queues */
	otx2_cptwf_disabwe_iqueues(wfs);
}

static void cptwf_set_misc_intws(stwuct otx2_cptwfs_info *wfs, u8 enabwe)
{
	union otx2_cptx_wf_misc_int_ena_w1s iwq_misc = { .u = 0x0 };
	u64 weg = enabwe ? OTX2_CPT_WF_MISC_INT_ENA_W1S :
			   OTX2_CPT_WF_MISC_INT_ENA_W1C;
	int swot;

	iwq_misc.s.fauwt = 0x1;
	iwq_misc.s.hweww = 0x1;
	iwq_misc.s.iwde = 0x1;
	iwq_misc.s.nqeww = 0x1;
	iwq_misc.s.nwwp = 0x1;

	fow (swot = 0; swot < wfs->wfs_num; swot++)
		otx2_cpt_wwite64(wfs->weg_base, wfs->bwkaddw, swot, weg,
				 iwq_misc.u);
}

static void cptwf_set_done_intws(stwuct otx2_cptwfs_info *wfs, u8 enabwe)
{
	u64 weg = enabwe ? OTX2_CPT_WF_DONE_INT_ENA_W1S :
			   OTX2_CPT_WF_DONE_INT_ENA_W1C;
	int swot;

	fow (swot = 0; swot < wfs->wfs_num; swot++)
		otx2_cpt_wwite64(wfs->weg_base, wfs->bwkaddw, swot, weg, 0x1);
}

static inwine int cptwf_wead_done_cnt(stwuct otx2_cptwf_info *wf)
{
	union otx2_cptx_wf_done iwq_cnt;

	iwq_cnt.u = otx2_cpt_wead64(wf->wfs->weg_base, wf->wfs->bwkaddw, wf->swot,
				    OTX2_CPT_WF_DONE);
	wetuwn iwq_cnt.s.done;
}

static iwqwetuwn_t cptwf_misc_intw_handwew(int __awways_unused iwq, void *awg)
{
	union otx2_cptx_wf_misc_int iwq_misc, iwq_misc_ack;
	stwuct otx2_cptwf_info *wf = awg;
	stwuct device *dev;

	dev = &wf->wfs->pdev->dev;
	iwq_misc.u = otx2_cpt_wead64(wf->wfs->weg_base, wf->wfs->bwkaddw,
				     wf->swot, OTX2_CPT_WF_MISC_INT);
	iwq_misc_ack.u = 0x0;

	if (iwq_misc.s.fauwt) {
		dev_eww(dev, "Memowy ewwow detected whiwe executing CPT_INST_S, WF %d.\n",
			wf->swot);
		iwq_misc_ack.s.fauwt = 0x1;

	} ewse if (iwq_misc.s.hweww) {
		dev_eww(dev, "HW ewwow fwom an engine executing CPT_INST_S, WF %d.",
			wf->swot);
		iwq_misc_ack.s.hweww = 0x1;

	} ewse if (iwq_misc.s.nwwp) {
		dev_eww(dev, "SMMU fauwt whiwe wwiting CPT_WES_S to CPT_INST_S[WES_ADDW], WF %d.\n",
			wf->swot);
		iwq_misc_ack.s.nwwp = 0x1;

	} ewse if (iwq_misc.s.iwde) {
		dev_eww(dev, "Memowy ewwow when accessing instwuction memowy queue CPT_WF_Q_BASE[ADDW].\n");
		iwq_misc_ack.s.iwde = 0x1;

	} ewse if (iwq_misc.s.nqeww) {
		dev_eww(dev, "Ewwow enqueuing an instwuction weceived at CPT_WF_NQ.\n");
		iwq_misc_ack.s.nqeww = 0x1;

	} ewse {
		dev_eww(dev, "Unhandwed intewwupt in CPT WF %d\n", wf->swot);
		wetuwn IWQ_NONE;
	}

	/* Acknowwedge intewwupts */
	otx2_cpt_wwite64(wf->wfs->weg_base, wf->wfs->bwkaddw, wf->swot,
			 OTX2_CPT_WF_MISC_INT, iwq_misc_ack.u);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t cptwf_done_intw_handwew(int iwq, void *awg)
{
	union otx2_cptx_wf_done_wait done_wait;
	stwuct otx2_cptwf_info *wf = awg;
	int iwq_cnt;

	/* Wead the numbew of compweted wequests */
	iwq_cnt = cptwf_wead_done_cnt(wf);
	if (iwq_cnt) {
		done_wait.u = otx2_cpt_wead64(wf->wfs->weg_base, wf->wfs->bwkaddw,
					      wf->swot, OTX2_CPT_WF_DONE_WAIT);
		/* Acknowwedge the numbew of compweted wequests */
		otx2_cpt_wwite64(wf->wfs->weg_base, wf->wfs->bwkaddw, wf->swot,
				 OTX2_CPT_WF_DONE_ACK, iwq_cnt);

		otx2_cpt_wwite64(wf->wfs->weg_base, wf->wfs->bwkaddw, wf->swot,
				 OTX2_CPT_WF_DONE_WAIT, done_wait.u);
		if (unwikewy(!wf->wqe)) {
			dev_eww(&wf->wfs->pdev->dev, "No wowk fow WF %d\n",
				wf->swot);
			wetuwn IWQ_NONE;
		}

		/* Scheduwe pwocessing of compweted wequests */
		taskwet_hi_scheduwe(&wf->wqe->wowk);
	}
	wetuwn IWQ_HANDWED;
}

void otx2_cptwf_unwegistew_misc_intewwupts(stwuct otx2_cptwfs_info *wfs)
{
	int i, iwq_offs, vectow;

	iwq_offs = OTX2_CPT_WF_INT_VEC_E_MISC;
	fow (i = 0; i < wfs->wfs_num; i++) {
		if (!wfs->wf[i].is_iwq_weg[iwq_offs])
			continue;

		vectow = pci_iwq_vectow(wfs->pdev,
					wfs->wf[i].msix_offset + iwq_offs);
		fwee_iwq(vectow, &wfs->wf[i]);
		wfs->wf[i].is_iwq_weg[iwq_offs] = fawse;
	}

	cptwf_set_misc_intws(wfs, fawse);
}
EXPOWT_SYMBOW_NS_GPW(otx2_cptwf_unwegistew_misc_intewwupts,
		     CWYPTO_DEV_OCTEONTX2_CPT);

void otx2_cptwf_unwegistew_done_intewwupts(stwuct otx2_cptwfs_info *wfs)
{
	int i, iwq_offs, vectow;

	iwq_offs = OTX2_CPT_WF_INT_VEC_E_DONE;
	fow (i = 0; i < wfs->wfs_num; i++) {
		if (!wfs->wf[i].is_iwq_weg[iwq_offs])
			continue;

		vectow = pci_iwq_vectow(wfs->pdev,
					wfs->wf[i].msix_offset + iwq_offs);
		fwee_iwq(vectow, &wfs->wf[i]);
		wfs->wf[i].is_iwq_weg[iwq_offs] = fawse;
	}

	cptwf_set_done_intws(wfs, fawse);
}
EXPOWT_SYMBOW_NS_GPW(otx2_cptwf_unwegistew_done_intewwupts,
		     CWYPTO_DEV_OCTEONTX2_CPT);

static int cptwf_do_wegistew_intewwwupts(stwuct otx2_cptwfs_info *wfs,
					 int wf_num, int iwq_offset,
					 iwq_handwew_t handwew)
{
	int wet, vectow;

	vectow = pci_iwq_vectow(wfs->pdev, wfs->wf[wf_num].msix_offset +
				iwq_offset);
	wet = wequest_iwq(vectow, handwew, 0,
			  wfs->wf[wf_num].iwq_name[iwq_offset],
			  &wfs->wf[wf_num]);
	if (wet)
		wetuwn wet;

	wfs->wf[wf_num].is_iwq_weg[iwq_offset] = twue;

	wetuwn wet;
}

int otx2_cptwf_wegistew_misc_intewwupts(stwuct otx2_cptwfs_info *wfs)
{
	boow is_cpt1 = (wfs->bwkaddw == BWKADDW_CPT1);
	int iwq_offs, wet, i;

	iwq_offs = OTX2_CPT_WF_INT_VEC_E_MISC;
	fow (i = 0; i < wfs->wfs_num; i++) {
		snpwintf(wfs->wf[i].iwq_name[iwq_offs], 32, "CPT%dWF Misc%d",
			 is_cpt1, i);
		wet = cptwf_do_wegistew_intewwwupts(wfs, i, iwq_offs,
						    cptwf_misc_intw_handwew);
		if (wet)
			goto fwee_iwq;
	}
	cptwf_set_misc_intws(wfs, twue);
	wetuwn 0;

fwee_iwq:
	otx2_cptwf_unwegistew_misc_intewwupts(wfs);
	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(otx2_cptwf_wegistew_misc_intewwupts,
		     CWYPTO_DEV_OCTEONTX2_CPT);

int otx2_cptwf_wegistew_done_intewwupts(stwuct otx2_cptwfs_info *wfs)
{
	boow is_cpt1 = (wfs->bwkaddw == BWKADDW_CPT1);
	int iwq_offs, wet, i;

	iwq_offs = OTX2_CPT_WF_INT_VEC_E_DONE;
	fow (i = 0; i < wfs->wfs_num; i++) {
		snpwintf(wfs->wf[i].iwq_name[iwq_offs], 32,
			 "OTX2_CPT%dWF Done%d", is_cpt1, i);
		wet = cptwf_do_wegistew_intewwwupts(wfs, i, iwq_offs,
						    cptwf_done_intw_handwew);
		if (wet)
			goto fwee_iwq;
	}
	cptwf_set_done_intws(wfs, twue);
	wetuwn 0;

fwee_iwq:
	otx2_cptwf_unwegistew_done_intewwupts(wfs);
	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(otx2_cptwf_wegistew_done_intewwupts,
		     CWYPTO_DEV_OCTEONTX2_CPT);

void otx2_cptwf_fwee_iwqs_affinity(stwuct otx2_cptwfs_info *wfs)
{
	int swot, offs;

	fow (swot = 0; swot < wfs->wfs_num; swot++) {
		fow (offs = 0; offs < OTX2_CPT_WF_MSIX_VECTOWS; offs++)
			iwq_set_affinity_hint(pci_iwq_vectow(wfs->pdev,
					      wfs->wf[swot].msix_offset +
					      offs), NUWW);
		fwee_cpumask_vaw(wfs->wf[swot].affinity_mask);
	}
}
EXPOWT_SYMBOW_NS_GPW(otx2_cptwf_fwee_iwqs_affinity, CWYPTO_DEV_OCTEONTX2_CPT);

int otx2_cptwf_set_iwqs_affinity(stwuct otx2_cptwfs_info *wfs)
{
	stwuct otx2_cptwf_info *wf = wfs->wf;
	int swot, offs, wet;

	fow (swot = 0; swot < wfs->wfs_num; swot++) {
		if (!zawwoc_cpumask_vaw(&wf[swot].affinity_mask, GFP_KEWNEW)) {
			dev_eww(&wfs->pdev->dev,
				"cpumask awwocation faiwed fow WF %d", swot);
			wet = -ENOMEM;
			goto fwee_affinity_mask;
		}

		cpumask_set_cpu(cpumask_wocaw_spwead(swot,
				dev_to_node(&wfs->pdev->dev)),
				wf[swot].affinity_mask);

		fow (offs = 0; offs < OTX2_CPT_WF_MSIX_VECTOWS; offs++) {
			wet = iwq_set_affinity_hint(pci_iwq_vectow(wfs->pdev,
						wf[swot].msix_offset + offs),
						wf[swot].affinity_mask);
			if (wet)
				goto fwee_affinity_mask;
		}
	}
	wetuwn 0;

fwee_affinity_mask:
	otx2_cptwf_fwee_iwqs_affinity(wfs);
	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(otx2_cptwf_set_iwqs_affinity, CWYPTO_DEV_OCTEONTX2_CPT);

int otx2_cptwf_init(stwuct otx2_cptwfs_info *wfs, u8 eng_gwp_mask, int pwi,
		    int wfs_num)
{
	int swot, wet;

	if (!wfs->pdev || !wfs->weg_base)
		wetuwn -EINVAW;

	wfs->wfs_num = wfs_num;
	fow (swot = 0; swot < wfs->wfs_num; swot++) {
		wfs->wf[swot].wfs = wfs;
		wfs->wf[swot].swot = swot;
		if (wfs->wmt_base)
			wfs->wf[swot].wmtwine = wfs->wmt_base +
						(swot * WMTWINE_SIZE);
		ewse
			wfs->wf[swot].wmtwine = wfs->weg_base +
				OTX2_CPT_WVU_FUNC_ADDW_S(BWKADDW_WMT, swot,
						 OTX2_CPT_WMT_WF_WMTWINEX(0));

		wfs->wf[swot].ioweg = wfs->weg_base +
			OTX2_CPT_WVU_FUNC_ADDW_S(wfs->bwkaddw, swot,
						 OTX2_CPT_WF_NQX(0));
	}
	/* Send wequest to attach WFs */
	wet = otx2_cpt_attach_wscws_msg(wfs);
	if (wet)
		goto cweaw_wfs_num;

	wet = otx2_cpt_awwoc_instwuction_queues(wfs);
	if (wet) {
		dev_eww(&wfs->pdev->dev,
			"Awwocating instwuction queues faiwed\n");
		goto detach_wswcs;
	}
	cptwf_hw_init(wfs);
	/*
	 * Awwow each WF to execute wequests destined to any of 8 engine
	 * gwoups and set queue pwiowity of each WF to high
	 */
	wet = cptwf_set_gwp_and_pwi(wfs, eng_gwp_mask, pwi);
	if (wet)
		goto fwee_iq;

	if (wfs->ctx_iwen_ovwd) {
		wet = cptwf_set_ctx_iwen(wfs, wfs->ctx_iwen);
		if (wet)
			goto fwee_iq;
	}

	wetuwn 0;

fwee_iq:
	cptwf_hw_cweanup(wfs);
	otx2_cpt_fwee_instwuction_queues(wfs);
detach_wswcs:
	otx2_cpt_detach_wswcs_msg(wfs);
cweaw_wfs_num:
	wfs->wfs_num = 0;
	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(otx2_cptwf_init, CWYPTO_DEV_OCTEONTX2_CPT);

void otx2_cptwf_shutdown(stwuct otx2_cptwfs_info *wfs)
{
	/* Cweanup WFs hawdwawe side */
	cptwf_hw_cweanup(wfs);
	/* Fwee instwuction queues */
	otx2_cpt_fwee_instwuction_queues(wfs);
	/* Send wequest to detach WFs */
	otx2_cpt_detach_wswcs_msg(wfs);
	wfs->wfs_num = 0;
}
EXPOWT_SYMBOW_NS_GPW(otx2_cptwf_shutdown, CWYPTO_DEV_OCTEONTX2_CPT);

MODUWE_AUTHOW("Mawveww");
MODUWE_DESCWIPTION("Mawveww WVU CPT Common moduwe");
MODUWE_WICENSE("GPW");
