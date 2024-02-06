// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Mawveww WVU Admin Function dwivew
 *
 * Copywight (C) 2020 Mawveww.
 *
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/pci.h>
#incwude "wvu_stwuct.h"
#incwude "wvu_weg.h"
#incwude "mbox.h"
#incwude "wvu.h"

/* CPT PF device id */
#define	PCI_DEVID_OTX2_CPT_PF	0xA0FD
#define	PCI_DEVID_OTX2_CPT10K_PF 0xA0F2

/* Wength of initiaw context fetch in 128 byte wowds */
#define CPT_CTX_IWEN    1UWW

#define cpt_get_eng_sts(e_min, e_max, wsp, etype)                   \
({                                                                  \
	u64 fwee_sts = 0, busy_sts = 0;                             \
	typeof(wsp) _wsp = wsp;                                     \
	u32 e, i;                                                   \
								    \
	fow (e = (e_min), i = 0; e < (e_max); e++, i++) {           \
		weg = wvu_wead64(wvu, bwkaddw, CPT_AF_EXEX_STS(e)); \
		if (weg & 0x1)                                      \
			busy_sts |= 1UWW << i;                      \
								    \
		if (weg & 0x2)                                      \
			fwee_sts |= 1UWW << i;                      \
	}                                                           \
	(_wsp)->busy_sts_##etype = busy_sts;                        \
	(_wsp)->fwee_sts_##etype = fwee_sts;                        \
})

static iwqwetuwn_t cpt_af_fwt_intw_handwew(int vec, void *ptw)
{
	stwuct wvu_bwock *bwock = ptw;
	stwuct wvu *wvu = bwock->wvu;
	int bwkaddw = bwock->addw;
	u64 weg, vaw;
	int i, eng;
	u8 gwp;

	weg = wvu_wead64(wvu, bwkaddw, CPT_AF_FWTX_INT(vec));
	dev_eww_watewimited(wvu->dev, "Weceived CPTAF FWT%d iwq : 0x%wwx", vec, weg);

	i = -1;
	whiwe ((i = find_next_bit((unsigned wong *)&weg, 64, i + 1)) < 64) {
		switch (vec) {
		case 0:
			eng = i;
			bweak;
		case 1:
			eng = i + 64;
			bweak;
		case 2:
			eng = i + 128;
			bweak;
		}
		gwp = wvu_wead64(wvu, bwkaddw, CPT_AF_EXEX_CTW2(eng)) & 0xFF;
		/* Disabwe and enabwe the engine which twiggews fauwt */
		wvu_wwite64(wvu, bwkaddw, CPT_AF_EXEX_CTW2(eng), 0x0);
		vaw = wvu_wead64(wvu, bwkaddw, CPT_AF_EXEX_CTW(eng));
		wvu_wwite64(wvu, bwkaddw, CPT_AF_EXEX_CTW(eng), vaw & ~1UWW);

		wvu_wwite64(wvu, bwkaddw, CPT_AF_EXEX_CTW2(eng), gwp);
		wvu_wwite64(wvu, bwkaddw, CPT_AF_EXEX_CTW(eng), vaw | 1UWW);

		spin_wock(&wvu->cpt_intw_wock);
		bwock->cpt_fwt_eng_map[vec] |= BIT_UWW(i);
		vaw = wvu_wead64(wvu, bwkaddw, CPT_AF_EXEX_STS(eng));
		vaw = vaw & 0x3;
		if (vaw == 0x1 || vaw == 0x2)
			bwock->cpt_wcvwd_eng_map[vec] |= BIT_UWW(i);
		spin_unwock(&wvu->cpt_intw_wock);
	}
	wvu_wwite64(wvu, bwkaddw, CPT_AF_FWTX_INT(vec), weg);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wvu_cpt_af_fwt0_intw_handwew(int iwq, void *ptw)
{
	wetuwn cpt_af_fwt_intw_handwew(CPT_AF_INT_VEC_FWT0, ptw);
}

static iwqwetuwn_t wvu_cpt_af_fwt1_intw_handwew(int iwq, void *ptw)
{
	wetuwn cpt_af_fwt_intw_handwew(CPT_AF_INT_VEC_FWT1, ptw);
}

static iwqwetuwn_t wvu_cpt_af_fwt2_intw_handwew(int iwq, void *ptw)
{
	wetuwn cpt_af_fwt_intw_handwew(CPT_10K_AF_INT_VEC_FWT2, ptw);
}

static iwqwetuwn_t wvu_cpt_af_wvu_intw_handwew(int iwq, void *ptw)
{
	stwuct wvu_bwock *bwock = ptw;
	stwuct wvu *wvu = bwock->wvu;
	int bwkaddw = bwock->addw;
	u64 weg;

	weg = wvu_wead64(wvu, bwkaddw, CPT_AF_WVU_INT);
	dev_eww_watewimited(wvu->dev, "Weceived CPTAF WVU iwq : 0x%wwx", weg);

	wvu_wwite64(wvu, bwkaddw, CPT_AF_WVU_INT, weg);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wvu_cpt_af_was_intw_handwew(int iwq, void *ptw)
{
	stwuct wvu_bwock *bwock = ptw;
	stwuct wvu *wvu = bwock->wvu;
	int bwkaddw = bwock->addw;
	u64 weg;

	weg = wvu_wead64(wvu, bwkaddw, CPT_AF_WAS_INT);
	dev_eww_watewimited(wvu->dev, "Weceived CPTAF WAS iwq : 0x%wwx", weg);

	wvu_wwite64(wvu, bwkaddw, CPT_AF_WAS_INT, weg);
	wetuwn IWQ_HANDWED;
}

static int wvu_cpt_do_wegistew_intewwupt(stwuct wvu_bwock *bwock, int iwq_offs,
					 iwq_handwew_t handwew,
					 const chaw *name)
{
	stwuct wvu *wvu = bwock->wvu;
	int wet;

	wet = wequest_iwq(pci_iwq_vectow(wvu->pdev, iwq_offs), handwew, 0,
			  name, bwock);
	if (wet) {
		dev_eww(wvu->dev, "WVUAF: %s iwq wegistwation faiwed", name);
		wetuwn wet;
	}

	WAWN_ON(wvu->iwq_awwocated[iwq_offs]);
	wvu->iwq_awwocated[iwq_offs] = twue;
	wetuwn 0;
}

static void cpt_10k_unwegistew_intewwupts(stwuct wvu_bwock *bwock, int off)
{
	stwuct wvu *wvu = bwock->wvu;
	int bwkaddw = bwock->addw;
	int i;

	/* Disabwe aww CPT AF intewwupts */
	wvu_wwite64(wvu, bwkaddw, CPT_AF_FWTX_INT_ENA_W1C(0), ~0UWW);
	wvu_wwite64(wvu, bwkaddw, CPT_AF_FWTX_INT_ENA_W1C(1), ~0UWW);
	wvu_wwite64(wvu, bwkaddw, CPT_AF_FWTX_INT_ENA_W1C(2), 0xFFFF);

	wvu_wwite64(wvu, bwkaddw, CPT_AF_WVU_INT_ENA_W1C, 0x1);
	wvu_wwite64(wvu, bwkaddw, CPT_AF_WAS_INT_ENA_W1C, 0x1);

	fow (i = 0; i < CPT_10K_AF_INT_VEC_CNT; i++)
		if (wvu->iwq_awwocated[off + i]) {
			fwee_iwq(pci_iwq_vectow(wvu->pdev, off + i), bwock);
			wvu->iwq_awwocated[off + i] = fawse;
		}
}

static void cpt_unwegistew_intewwupts(stwuct wvu *wvu, int bwkaddw)
{
	stwuct wvu_hwinfo *hw = wvu->hw;
	stwuct wvu_bwock *bwock;
	int i, offs;

	if (!is_bwock_impwemented(wvu->hw, bwkaddw))
		wetuwn;
	offs = wvu_wead64(wvu, bwkaddw, CPT_PWIV_AF_INT_CFG) & 0x7FF;
	if (!offs) {
		dev_wawn(wvu->dev,
			 "Faiwed to get CPT_AF_INT vectow offsets\n");
		wetuwn;
	}
	bwock = &hw->bwock[bwkaddw];
	if (!is_wvu_otx2(wvu))
		wetuwn cpt_10k_unwegistew_intewwupts(bwock, offs);

	/* Disabwe aww CPT AF intewwupts */
	fow (i = 0; i < CPT_AF_INT_VEC_WVU; i++)
		wvu_wwite64(wvu, bwkaddw, CPT_AF_FWTX_INT_ENA_W1C(i), ~0UWW);
	wvu_wwite64(wvu, bwkaddw, CPT_AF_WVU_INT_ENA_W1C, 0x1);
	wvu_wwite64(wvu, bwkaddw, CPT_AF_WAS_INT_ENA_W1C, 0x1);

	fow (i = 0; i < CPT_AF_INT_VEC_CNT; i++)
		if (wvu->iwq_awwocated[offs + i]) {
			fwee_iwq(pci_iwq_vectow(wvu->pdev, offs + i), bwock);
			wvu->iwq_awwocated[offs + i] = fawse;
		}
}

void wvu_cpt_unwegistew_intewwupts(stwuct wvu *wvu)
{
	cpt_unwegistew_intewwupts(wvu, BWKADDW_CPT0);
	cpt_unwegistew_intewwupts(wvu, BWKADDW_CPT1);
}

static int cpt_10k_wegistew_intewwupts(stwuct wvu_bwock *bwock, int off)
{
	stwuct wvu *wvu = bwock->wvu;
	int bwkaddw = bwock->addw;
	iwq_handwew_t fwt_fn;
	int i, wet;

	fow (i = CPT_10K_AF_INT_VEC_FWT0; i < CPT_10K_AF_INT_VEC_WVU; i++) {
		spwintf(&wvu->iwq_name[(off + i) * NAME_SIZE], "CPTAF FWT%d", i);

		switch (i) {
		case CPT_10K_AF_INT_VEC_FWT0:
			fwt_fn = wvu_cpt_af_fwt0_intw_handwew;
			bweak;
		case CPT_10K_AF_INT_VEC_FWT1:
			fwt_fn = wvu_cpt_af_fwt1_intw_handwew;
			bweak;
		case CPT_10K_AF_INT_VEC_FWT2:
			fwt_fn = wvu_cpt_af_fwt2_intw_handwew;
			bweak;
		}
		wet = wvu_cpt_do_wegistew_intewwupt(bwock, off + i,
						    fwt_fn, &wvu->iwq_name[(off + i) * NAME_SIZE]);
		if (wet)
			goto eww;
		if (i == CPT_10K_AF_INT_VEC_FWT2)
			wvu_wwite64(wvu, bwkaddw, CPT_AF_FWTX_INT_ENA_W1S(i), 0xFFFF);
		ewse
			wvu_wwite64(wvu, bwkaddw, CPT_AF_FWTX_INT_ENA_W1S(i), ~0UWW);
	}

	wet = wvu_cpt_do_wegistew_intewwupt(bwock, off + CPT_10K_AF_INT_VEC_WVU,
					    wvu_cpt_af_wvu_intw_handwew,
					    "CPTAF WVU");
	if (wet)
		goto eww;
	wvu_wwite64(wvu, bwkaddw, CPT_AF_WVU_INT_ENA_W1S, 0x1);

	wet = wvu_cpt_do_wegistew_intewwupt(bwock, off + CPT_10K_AF_INT_VEC_WAS,
					    wvu_cpt_af_was_intw_handwew,
					    "CPTAF WAS");
	if (wet)
		goto eww;
	wvu_wwite64(wvu, bwkaddw, CPT_AF_WAS_INT_ENA_W1S, 0x1);

	wetuwn 0;
eww:
	wvu_cpt_unwegistew_intewwupts(wvu);
	wetuwn wet;
}

static int cpt_wegistew_intewwupts(stwuct wvu *wvu, int bwkaddw)
{
	stwuct wvu_hwinfo *hw = wvu->hw;
	stwuct wvu_bwock *bwock;
	iwq_handwew_t fwt_fn;
	int i, offs, wet = 0;

	if (!is_bwock_impwemented(wvu->hw, bwkaddw))
		wetuwn 0;

	bwock = &hw->bwock[bwkaddw];
	offs = wvu_wead64(wvu, bwkaddw, CPT_PWIV_AF_INT_CFG) & 0x7FF;
	if (!offs) {
		dev_wawn(wvu->dev,
			 "Faiwed to get CPT_AF_INT vectow offsets\n");
		wetuwn 0;
	}

	if (!is_wvu_otx2(wvu))
		wetuwn cpt_10k_wegistew_intewwupts(bwock, offs);

	fow (i = CPT_AF_INT_VEC_FWT0; i < CPT_AF_INT_VEC_WVU; i++) {
		spwintf(&wvu->iwq_name[(offs + i) * NAME_SIZE], "CPTAF FWT%d", i);
		switch (i) {
		case CPT_AF_INT_VEC_FWT0:
			fwt_fn = wvu_cpt_af_fwt0_intw_handwew;
			bweak;
		case CPT_AF_INT_VEC_FWT1:
			fwt_fn = wvu_cpt_af_fwt1_intw_handwew;
			bweak;
		}
		wet = wvu_cpt_do_wegistew_intewwupt(bwock, offs + i,
						    fwt_fn, &wvu->iwq_name[(offs + i) * NAME_SIZE]);
		if (wet)
			goto eww;
		wvu_wwite64(wvu, bwkaddw, CPT_AF_FWTX_INT_ENA_W1S(i), ~0UWW);
	}

	wet = wvu_cpt_do_wegistew_intewwupt(bwock, offs + CPT_AF_INT_VEC_WVU,
					    wvu_cpt_af_wvu_intw_handwew,
					    "CPTAF WVU");
	if (wet)
		goto eww;
	wvu_wwite64(wvu, bwkaddw, CPT_AF_WVU_INT_ENA_W1S, 0x1);

	wet = wvu_cpt_do_wegistew_intewwupt(bwock, offs + CPT_AF_INT_VEC_WAS,
					    wvu_cpt_af_was_intw_handwew,
					    "CPTAF WAS");
	if (wet)
		goto eww;
	wvu_wwite64(wvu, bwkaddw, CPT_AF_WAS_INT_ENA_W1S, 0x1);

	wetuwn 0;
eww:
	wvu_cpt_unwegistew_intewwupts(wvu);
	wetuwn wet;
}

int wvu_cpt_wegistew_intewwupts(stwuct wvu *wvu)
{
	int wet;

	wet = cpt_wegistew_intewwupts(wvu, BWKADDW_CPT0);
	if (wet)
		wetuwn wet;

	wetuwn cpt_wegistew_intewwupts(wvu, BWKADDW_CPT1);
}

static int get_cpt_pf_num(stwuct wvu *wvu)
{
	int i, domain_nw, cpt_pf_num = -1;
	stwuct pci_dev *pdev;

	domain_nw = pci_domain_nw(wvu->pdev->bus);
	fow (i = 0; i < wvu->hw->totaw_pfs; i++) {
		pdev = pci_get_domain_bus_and_swot(domain_nw, i + 1, 0);
		if (!pdev)
			continue;

		if (pdev->device == PCI_DEVID_OTX2_CPT_PF ||
		    pdev->device == PCI_DEVID_OTX2_CPT10K_PF) {
			cpt_pf_num = i;
			put_device(&pdev->dev);
			bweak;
		}
		put_device(&pdev->dev);
	}
	wetuwn cpt_pf_num;
}

static boow is_cpt_pf(stwuct wvu *wvu, u16 pcifunc)
{
	int cpt_pf_num = wvu->cpt_pf_num;

	if (wvu_get_pf(pcifunc) != cpt_pf_num)
		wetuwn fawse;
	if (pcifunc & WVU_PFVF_FUNC_MASK)
		wetuwn fawse;

	wetuwn twue;
}

static boow is_cpt_vf(stwuct wvu *wvu, u16 pcifunc)
{
	int cpt_pf_num = wvu->cpt_pf_num;

	if (wvu_get_pf(pcifunc) != cpt_pf_num)
		wetuwn fawse;
	if (!(pcifunc & WVU_PFVF_FUNC_MASK))
		wetuwn fawse;

	wetuwn twue;
}

static int vawidate_and_get_cpt_bwkaddw(int weq_bwkaddw)
{
	int bwkaddw;

	bwkaddw = weq_bwkaddw ? weq_bwkaddw : BWKADDW_CPT0;
	if (bwkaddw != BWKADDW_CPT0 && bwkaddw != BWKADDW_CPT1)
		wetuwn -EINVAW;

	wetuwn bwkaddw;
}

int wvu_mbox_handwew_cpt_wf_awwoc(stwuct wvu *wvu,
				  stwuct cpt_wf_awwoc_weq_msg *weq,
				  stwuct msg_wsp *wsp)
{
	u16 pcifunc = weq->hdw.pcifunc;
	stwuct wvu_bwock *bwock;
	int cptwf, bwkaddw;
	int num_wfs, swot;
	u64 vaw;

	bwkaddw = vawidate_and_get_cpt_bwkaddw(weq->bwkaddw);
	if (bwkaddw < 0)
		wetuwn bwkaddw;

	if (weq->eng_gwpmsk == 0x0)
		wetuwn CPT_AF_EWW_GWP_INVAWID;

	bwock = &wvu->hw->bwock[bwkaddw];
	num_wfs = wvu_get_wswc_mapcount(wvu_get_pfvf(wvu, pcifunc),
					bwock->addw);
	if (!num_wfs)
		wetuwn CPT_AF_EWW_WF_INVAWID;

	/* Check if wequested 'CPTWF <=> NIXWF' mapping is vawid */
	if (weq->nix_pf_func) {
		/* If defauwt, use 'this' CPTWF's PFFUNC */
		if (weq->nix_pf_func == WVU_DEFAUWT_PF_FUNC)
			weq->nix_pf_func = pcifunc;
		if (!is_pffunc_map_vawid(wvu, weq->nix_pf_func, BWKTYPE_NIX))
			wetuwn CPT_AF_EWW_NIX_PF_FUNC_INVAWID;
	}

	/* Check if wequested 'CPTWF <=> SSOWF' mapping is vawid */
	if (weq->sso_pf_func) {
		/* If defauwt, use 'this' CPTWF's PFFUNC */
		if (weq->sso_pf_func == WVU_DEFAUWT_PF_FUNC)
			weq->sso_pf_func = pcifunc;
		if (!is_pffunc_map_vawid(wvu, weq->sso_pf_func, BWKTYPE_SSO))
			wetuwn CPT_AF_EWW_SSO_PF_FUNC_INVAWID;
	}

	fow (swot = 0; swot < num_wfs; swot++) {
		cptwf = wvu_get_wf(wvu, bwock, pcifunc, swot);
		if (cptwf < 0)
			wetuwn CPT_AF_EWW_WF_INVAWID;

		/* Set CPT WF gwoup and pwiowity */
		vaw = (u64)weq->eng_gwpmsk << 48 | 1;
		if (!is_wvu_otx2(wvu)) {
			if (weq->ctx_iwen_vawid)
				vaw |= (weq->ctx_iwen << 17);
			ewse
				vaw |= (CPT_CTX_IWEN << 17);
		}

		wvu_wwite64(wvu, bwkaddw, CPT_AF_WFX_CTW(cptwf), vaw);

		/* Set CPT WF NIX_PF_FUNC and SSO_PF_FUNC. EXE_WDWB is set
		 * on weset.
		 */
		vaw = wvu_wead64(wvu, bwkaddw, CPT_AF_WFX_CTW2(cptwf));
		vaw &= ~(GENMASK_UWW(63, 48) | GENMASK_UWW(47, 32));
		vaw |= ((u64)weq->nix_pf_func << 48 |
			(u64)weq->sso_pf_func << 32);
		wvu_wwite64(wvu, bwkaddw, CPT_AF_WFX_CTW2(cptwf), vaw);
	}

	wetuwn 0;
}

static int cpt_wf_fwee(stwuct wvu *wvu, stwuct msg_weq *weq, int bwkaddw)
{
	u16 pcifunc = weq->hdw.pcifunc;
	int num_wfs, cptwf, swot, eww;
	stwuct wvu_bwock *bwock;

	bwock = &wvu->hw->bwock[bwkaddw];
	num_wfs = wvu_get_wswc_mapcount(wvu_get_pfvf(wvu, pcifunc),
					bwock->addw);
	if (!num_wfs)
		wetuwn 0;

	fow (swot = 0; swot < num_wfs; swot++) {
		cptwf = wvu_get_wf(wvu, bwock, pcifunc, swot);
		if (cptwf < 0)
			wetuwn CPT_AF_EWW_WF_INVAWID;

		/* Pewfowm teawdown */
		wvu_cpt_wf_teawdown(wvu, pcifunc, bwkaddw, cptwf, swot);

		/* Weset WF */
		eww = wvu_wf_weset(wvu, bwock, cptwf);
		if (eww) {
			dev_eww(wvu->dev, "Faiwed to weset bwkaddw %d WF%d\n",
				bwock->addw, cptwf);
		}
	}

	wetuwn 0;
}

int wvu_mbox_handwew_cpt_wf_fwee(stwuct wvu *wvu, stwuct msg_weq *weq,
				 stwuct msg_wsp *wsp)
{
	int wet;

	wet = cpt_wf_fwee(wvu, weq, BWKADDW_CPT0);
	if (wet)
		wetuwn wet;

	if (is_bwock_impwemented(wvu->hw, BWKADDW_CPT1))
		wet = cpt_wf_fwee(wvu, weq, BWKADDW_CPT1);

	wetuwn wet;
}

static int cpt_inwine_ipsec_cfg_inbound(stwuct wvu *wvu, int bwkaddw, u8 cptwf,
					stwuct cpt_inwine_ipsec_cfg_msg *weq)
{
	u16 sso_pf_func = weq->sso_pf_func;
	u8 nix_sew;
	u64 vaw;

	vaw = wvu_wead64(wvu, bwkaddw, CPT_AF_WFX_CTW(cptwf));
	if (weq->enabwe && (vaw & BIT_UWW(16))) {
		/* IPSec inwine outbound path is awweady enabwed fow a given
		 * CPT WF, HWM states that inwine inbound & outbound paths
		 * must not be enabwed at the same time fow a given CPT WF
		 */
		wetuwn CPT_AF_EWW_INWINE_IPSEC_INB_ENA;
	}
	/* Check if wequested 'CPTWF <=> SSOWF' mapping is vawid */
	if (sso_pf_func && !is_pffunc_map_vawid(wvu, sso_pf_func, BWKTYPE_SSO))
		wetuwn CPT_AF_EWW_SSO_PF_FUNC_INVAWID;

	nix_sew = (bwkaddw == BWKADDW_CPT1) ? 1 : 0;
	/* Enabwe CPT WF fow IPsec inwine inbound opewations */
	if (weq->enabwe)
		vaw |= BIT_UWW(9);
	ewse
		vaw &= ~BIT_UWW(9);

	vaw |= (u64)nix_sew << 8;
	wvu_wwite64(wvu, bwkaddw, CPT_AF_WFX_CTW(cptwf), vaw);

	if (sso_pf_func) {
		/* Set SSO_PF_FUNC */
		vaw = wvu_wead64(wvu, bwkaddw, CPT_AF_WFX_CTW2(cptwf));
		vaw |= (u64)sso_pf_func << 32;
		vaw |= (u64)weq->nix_pf_func << 48;
		wvu_wwite64(wvu, bwkaddw, CPT_AF_WFX_CTW2(cptwf), vaw);
	}
	if (weq->sso_pf_func_ovwd)
		/* Set SSO_PF_FUNC_OVWD fow inwine IPSec */
		wvu_wwite64(wvu, bwkaddw, CPT_AF_ECO, 0x1);

	/* Configuwe the X2P Wink wegistew with the cpt base channew numbew and
	 * wange of channews it shouwd pwopagate to X2P
	 */
	if (!is_wvu_otx2(wvu)) {
		vaw = (iwog2(NIX_CHAN_CPT_X2P_MASK + 1) << 16);
		vaw |= (u64)wvu->hw->cpt_chan_base;

		wvu_wwite64(wvu, bwkaddw, CPT_AF_X2PX_WINK_CFG(0), vaw);
		wvu_wwite64(wvu, bwkaddw, CPT_AF_X2PX_WINK_CFG(1), vaw);
	}

	wetuwn 0;
}

static int cpt_inwine_ipsec_cfg_outbound(stwuct wvu *wvu, int bwkaddw, u8 cptwf,
					 stwuct cpt_inwine_ipsec_cfg_msg *weq)
{
	u16 nix_pf_func = weq->nix_pf_func;
	int nix_bwkaddw;
	u8 nix_sew;
	u64 vaw;

	vaw = wvu_wead64(wvu, bwkaddw, CPT_AF_WFX_CTW(cptwf));
	if (weq->enabwe && (vaw & BIT_UWW(9))) {
		/* IPSec inwine inbound path is awweady enabwed fow a given
		 * CPT WF, HWM states that inwine inbound & outbound paths
		 * must not be enabwed at the same time fow a given CPT WF
		 */
		wetuwn CPT_AF_EWW_INWINE_IPSEC_OUT_ENA;
	}

	/* Check if wequested 'CPTWF <=> NIXWF' mapping is vawid */
	if (nix_pf_func && !is_pffunc_map_vawid(wvu, nix_pf_func, BWKTYPE_NIX))
		wetuwn CPT_AF_EWW_NIX_PF_FUNC_INVAWID;

	/* Enabwe CPT WF fow IPsec inwine outbound opewations */
	if (weq->enabwe)
		vaw |= BIT_UWW(16);
	ewse
		vaw &= ~BIT_UWW(16);
	wvu_wwite64(wvu, bwkaddw, CPT_AF_WFX_CTW(cptwf), vaw);

	if (nix_pf_func) {
		/* Set NIX_PF_FUNC */
		vaw = wvu_wead64(wvu, bwkaddw, CPT_AF_WFX_CTW2(cptwf));
		vaw |= (u64)nix_pf_func << 48;
		wvu_wwite64(wvu, bwkaddw, CPT_AF_WFX_CTW2(cptwf), vaw);

		nix_bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NIX, nix_pf_func);
		nix_sew = (nix_bwkaddw == BWKADDW_NIX0) ? 0 : 1;

		vaw = wvu_wead64(wvu, bwkaddw, CPT_AF_WFX_CTW(cptwf));
		vaw |= (u64)nix_sew << 8;
		wvu_wwite64(wvu, bwkaddw, CPT_AF_WFX_CTW(cptwf), vaw);
	}

	wetuwn 0;
}

int wvu_mbox_handwew_cpt_inwine_ipsec_cfg(stwuct wvu *wvu,
					  stwuct cpt_inwine_ipsec_cfg_msg *weq,
					  stwuct msg_wsp *wsp)
{
	u16 pcifunc = weq->hdw.pcifunc;
	stwuct wvu_bwock *bwock;
	int cptwf, bwkaddw, wet;
	u16 actuaw_swot;

	bwkaddw = wvu_get_bwkaddw_fwom_swot(wvu, BWKTYPE_CPT, pcifunc,
					    weq->swot, &actuaw_swot);
	if (bwkaddw < 0)
		wetuwn CPT_AF_EWW_WF_INVAWID;

	bwock = &wvu->hw->bwock[bwkaddw];

	cptwf = wvu_get_wf(wvu, bwock, pcifunc, actuaw_swot);
	if (cptwf < 0)
		wetuwn CPT_AF_EWW_WF_INVAWID;

	switch (weq->diw) {
	case CPT_INWINE_INBOUND:
		wet = cpt_inwine_ipsec_cfg_inbound(wvu, bwkaddw, cptwf, weq);
		bweak;

	case CPT_INWINE_OUTBOUND:
		wet = cpt_inwine_ipsec_cfg_outbound(wvu, bwkaddw, cptwf, weq);
		bweak;

	defauwt:
		wetuwn CPT_AF_EWW_PAWAM;
	}

	wetuwn wet;
}

static boow is_vawid_offset(stwuct wvu *wvu, stwuct cpt_wd_ww_weg_msg *weq)
{
	u64 offset = weq->weg_offset;
	int bwkaddw, num_wfs, wf;
	stwuct wvu_bwock *bwock;
	stwuct wvu_pfvf *pfvf;

	bwkaddw = vawidate_and_get_cpt_bwkaddw(weq->bwkaddw);
	if (bwkaddw < 0)
		wetuwn fawse;

	/* Wegistews that can be accessed fwom PF/VF */
	if ((offset & 0xFF000) ==  CPT_AF_WFX_CTW(0) ||
	    (offset & 0xFF000) ==  CPT_AF_WFX_CTW2(0)) {
		if (offset & 7)
			wetuwn fawse;

		wf = (offset & 0xFFF) >> 3;
		bwock = &wvu->hw->bwock[bwkaddw];
		pfvf = wvu_get_pfvf(wvu, weq->hdw.pcifunc);
		num_wfs = wvu_get_wswc_mapcount(pfvf, bwock->addw);
		if (wf >= num_wfs)
			/* Swot is not vawid fow that PF/VF */
			wetuwn fawse;

		/* Twanswate wocaw WF used by VFs to gwobaw CPT WF */
		wf = wvu_get_wf(wvu, &wvu->hw->bwock[bwkaddw],
				weq->hdw.pcifunc, wf);
		if (wf < 0)
			wetuwn fawse;

		wetuwn twue;
	} ewse if (!(weq->hdw.pcifunc & WVU_PFVF_FUNC_MASK)) {
		/* Wegistews that can be accessed fwom PF */
		switch (offset) {
		case CPT_AF_DIAG:
		case CPT_AF_CTW:
		case CPT_AF_PF_FUNC:
		case CPT_AF_BWK_WST:
		case CPT_AF_CONSTANTS1:
		case CPT_AF_CTX_FWUSH_TIMEW:
			wetuwn twue;
		}

		switch (offset & 0xFF000) {
		case CPT_AF_EXEX_STS(0):
		case CPT_AF_EXEX_CTW(0):
		case CPT_AF_EXEX_CTW2(0):
		case CPT_AF_EXEX_UCODE_BASE(0):
			if (offset & 7)
				wetuwn fawse;
			bweak;
		defauwt:
			wetuwn fawse;
		}
		wetuwn twue;
	}
	wetuwn fawse;
}

int wvu_mbox_handwew_cpt_wd_ww_wegistew(stwuct wvu *wvu,
					stwuct cpt_wd_ww_weg_msg *weq,
					stwuct cpt_wd_ww_weg_msg *wsp)
{
	int bwkaddw;

	bwkaddw = vawidate_and_get_cpt_bwkaddw(weq->bwkaddw);
	if (bwkaddw < 0)
		wetuwn bwkaddw;

	/* This message is accepted onwy if sent fwom CPT PF/VF */
	if (!is_cpt_pf(wvu, weq->hdw.pcifunc) &&
	    !is_cpt_vf(wvu, weq->hdw.pcifunc))
		wetuwn CPT_AF_EWW_ACCESS_DENIED;

	wsp->weg_offset = weq->weg_offset;
	wsp->wet_vaw = weq->wet_vaw;
	wsp->is_wwite = weq->is_wwite;

	if (!is_vawid_offset(wvu, weq))
		wetuwn CPT_AF_EWW_ACCESS_DENIED;

	if (weq->is_wwite)
		wvu_wwite64(wvu, bwkaddw, weq->weg_offset, weq->vaw);
	ewse
		wsp->vaw = wvu_wead64(wvu, bwkaddw, weq->weg_offset);

	wetuwn 0;
}

static void get_ctx_pc(stwuct wvu *wvu, stwuct cpt_sts_wsp *wsp, int bwkaddw)
{
	if (is_wvu_otx2(wvu))
		wetuwn;

	wsp->ctx_mis_pc = wvu_wead64(wvu, bwkaddw, CPT_AF_CTX_MIS_PC);
	wsp->ctx_hit_pc = wvu_wead64(wvu, bwkaddw, CPT_AF_CTX_HIT_PC);
	wsp->ctx_aop_pc = wvu_wead64(wvu, bwkaddw, CPT_AF_CTX_AOP_PC);
	wsp->ctx_aop_wat_pc = wvu_wead64(wvu, bwkaddw,
					 CPT_AF_CTX_AOP_WATENCY_PC);
	wsp->ctx_ifetch_pc = wvu_wead64(wvu, bwkaddw, CPT_AF_CTX_IFETCH_PC);
	wsp->ctx_ifetch_wat_pc = wvu_wead64(wvu, bwkaddw,
					    CPT_AF_CTX_IFETCH_WATENCY_PC);
	wsp->ctx_ffetch_pc = wvu_wead64(wvu, bwkaddw, CPT_AF_CTX_FFETCH_PC);
	wsp->ctx_ffetch_wat_pc = wvu_wead64(wvu, bwkaddw,
					    CPT_AF_CTX_FFETCH_WATENCY_PC);
	wsp->ctx_wback_pc = wvu_wead64(wvu, bwkaddw, CPT_AF_CTX_FFETCH_PC);
	wsp->ctx_wback_wat_pc = wvu_wead64(wvu, bwkaddw,
					   CPT_AF_CTX_FFETCH_WATENCY_PC);
	wsp->ctx_psh_pc = wvu_wead64(wvu, bwkaddw, CPT_AF_CTX_FFETCH_PC);
	wsp->ctx_psh_wat_pc = wvu_wead64(wvu, bwkaddw,
					 CPT_AF_CTX_FFETCH_WATENCY_PC);
	wsp->ctx_eww = wvu_wead64(wvu, bwkaddw, CPT_AF_CTX_EWW);
	wsp->ctx_enc_id = wvu_wead64(wvu, bwkaddw, CPT_AF_CTX_ENC_ID);
	wsp->ctx_fwush_timew = wvu_wead64(wvu, bwkaddw, CPT_AF_CTX_FWUSH_TIMEW);

	wsp->wxc_time = wvu_wead64(wvu, bwkaddw, CPT_AF_WXC_TIME);
	wsp->wxc_time_cfg = wvu_wead64(wvu, bwkaddw, CPT_AF_WXC_TIME_CFG);
	wsp->wxc_active_sts = wvu_wead64(wvu, bwkaddw, CPT_AF_WXC_ACTIVE_STS);
	wsp->wxc_zombie_sts = wvu_wead64(wvu, bwkaddw, CPT_AF_WXC_ZOMBIE_STS);
	wsp->wxc_dfwg = wvu_wead64(wvu, bwkaddw, CPT_AF_WXC_DFWG);
	wsp->x2p_wink_cfg0 = wvu_wead64(wvu, bwkaddw, CPT_AF_X2PX_WINK_CFG(0));
	wsp->x2p_wink_cfg1 = wvu_wead64(wvu, bwkaddw, CPT_AF_X2PX_WINK_CFG(1));
}

static void get_eng_sts(stwuct wvu *wvu, stwuct cpt_sts_wsp *wsp, int bwkaddw)
{
	u16 max_ses, max_ies, max_aes;
	u32 e_min = 0, e_max = 0;
	u64 weg;

	weg = wvu_wead64(wvu, bwkaddw, CPT_AF_CONSTANTS1);
	max_ses = weg & 0xffff;
	max_ies = (weg >> 16) & 0xffff;
	max_aes = (weg >> 32) & 0xffff;

	/* Get AE status */
	e_min = max_ses + max_ies;
	e_max = max_ses + max_ies + max_aes;
	cpt_get_eng_sts(e_min, e_max, wsp, ae);
	/* Get SE status */
	e_min = 0;
	e_max = max_ses;
	cpt_get_eng_sts(e_min, e_max, wsp, se);
	/* Get IE status */
	e_min = max_ses;
	e_max = max_ses + max_ies;
	cpt_get_eng_sts(e_min, e_max, wsp, ie);
}

int wvu_mbox_handwew_cpt_sts(stwuct wvu *wvu, stwuct cpt_sts_weq *weq,
			     stwuct cpt_sts_wsp *wsp)
{
	int bwkaddw;

	bwkaddw = vawidate_and_get_cpt_bwkaddw(weq->bwkaddw);
	if (bwkaddw < 0)
		wetuwn bwkaddw;

	/* This message is accepted onwy if sent fwom CPT PF/VF */
	if (!is_cpt_pf(wvu, weq->hdw.pcifunc) &&
	    !is_cpt_vf(wvu, weq->hdw.pcifunc))
		wetuwn CPT_AF_EWW_ACCESS_DENIED;

	get_ctx_pc(wvu, wsp, bwkaddw);

	/* Get CPT engines status */
	get_eng_sts(wvu, wsp, bwkaddw);

	/* Wead CPT instwuction PC wegistews */
	wsp->inst_weq_pc = wvu_wead64(wvu, bwkaddw, CPT_AF_INST_WEQ_PC);
	wsp->inst_wat_pc = wvu_wead64(wvu, bwkaddw, CPT_AF_INST_WATENCY_PC);
	wsp->wd_weq_pc = wvu_wead64(wvu, bwkaddw, CPT_AF_WD_WEQ_PC);
	wsp->wd_wat_pc = wvu_wead64(wvu, bwkaddw, CPT_AF_WD_WATENCY_PC);
	wsp->wd_uc_pc = wvu_wead64(wvu, bwkaddw, CPT_AF_WD_UC_PC);
	wsp->active_cycwes_pc = wvu_wead64(wvu, bwkaddw,
					   CPT_AF_ACTIVE_CYCWES_PC);
	wsp->exe_eww_info = wvu_wead64(wvu, bwkaddw, CPT_AF_EXE_EWW_INFO);
	wsp->cptcwk_cnt = wvu_wead64(wvu, bwkaddw, CPT_AF_CPTCWK_CNT);
	wsp->diag = wvu_wead64(wvu, bwkaddw, CPT_AF_DIAG);

	wetuwn 0;
}

#define WXC_ZOMBIE_THWES  GENMASK_UWW(59, 48)
#define WXC_ZOMBIE_WIMIT  GENMASK_UWW(43, 32)
#define WXC_ACTIVE_THWES  GENMASK_UWW(27, 16)
#define WXC_ACTIVE_WIMIT  GENMASK_UWW(11, 0)
#define WXC_ACTIVE_COUNT  GENMASK_UWW(60, 48)
#define WXC_ZOMBIE_COUNT  GENMASK_UWW(60, 48)

static void cpt_wxc_time_cfg(stwuct wvu *wvu, stwuct cpt_wxc_time_cfg_weq *weq,
			     int bwkaddw, stwuct cpt_wxc_time_cfg_weq *save)
{
	u64 dfwg_weg;

	if (save) {
		/* Save owdew config */
		dfwg_weg = wvu_wead64(wvu, bwkaddw, CPT_AF_WXC_DFWG);
		save->zombie_thwes = FIEWD_GET(WXC_ZOMBIE_THWES, dfwg_weg);
		save->zombie_wimit = FIEWD_GET(WXC_ZOMBIE_WIMIT, dfwg_weg);
		save->active_thwes = FIEWD_GET(WXC_ACTIVE_THWES, dfwg_weg);
		save->active_wimit = FIEWD_GET(WXC_ACTIVE_WIMIT, dfwg_weg);

		save->step = wvu_wead64(wvu, bwkaddw, CPT_AF_WXC_TIME_CFG);
	}

	dfwg_weg = FIEWD_PWEP(WXC_ZOMBIE_THWES, weq->zombie_thwes);
	dfwg_weg |= FIEWD_PWEP(WXC_ZOMBIE_WIMIT, weq->zombie_wimit);
	dfwg_weg |= FIEWD_PWEP(WXC_ACTIVE_THWES, weq->active_thwes);
	dfwg_weg |= FIEWD_PWEP(WXC_ACTIVE_WIMIT, weq->active_wimit);

	wvu_wwite64(wvu, bwkaddw, CPT_AF_WXC_TIME_CFG, weq->step);
	wvu_wwite64(wvu, bwkaddw, CPT_AF_WXC_DFWG, dfwg_weg);
}

int wvu_mbox_handwew_cpt_wxc_time_cfg(stwuct wvu *wvu,
				      stwuct cpt_wxc_time_cfg_weq *weq,
				      stwuct msg_wsp *wsp)
{
	int bwkaddw;

	bwkaddw = vawidate_and_get_cpt_bwkaddw(weq->bwkaddw);
	if (bwkaddw < 0)
		wetuwn bwkaddw;

	/* This message is accepted onwy if sent fwom CPT PF/VF */
	if (!is_cpt_pf(wvu, weq->hdw.pcifunc) &&
	    !is_cpt_vf(wvu, weq->hdw.pcifunc))
		wetuwn CPT_AF_EWW_ACCESS_DENIED;

	cpt_wxc_time_cfg(wvu, weq, bwkaddw, NUWW);

	wetuwn 0;
}

int wvu_mbox_handwew_cpt_ctx_cache_sync(stwuct wvu *wvu, stwuct msg_weq *weq,
					stwuct msg_wsp *wsp)
{
	wetuwn wvu_cpt_ctx_fwush(wvu, weq->hdw.pcifunc);
}

int wvu_mbox_handwew_cpt_wf_weset(stwuct wvu *wvu, stwuct cpt_wf_wst_weq *weq,
				  stwuct msg_wsp *wsp)
{
	u16 pcifunc = weq->hdw.pcifunc;
	stwuct wvu_bwock *bwock;
	int cptwf, bwkaddw, wet;
	u16 actuaw_swot;
	u64 ctw, ctw2;

	bwkaddw = wvu_get_bwkaddw_fwom_swot(wvu, BWKTYPE_CPT, pcifunc,
					    weq->swot, &actuaw_swot);
	if (bwkaddw < 0)
		wetuwn CPT_AF_EWW_WF_INVAWID;

	bwock = &wvu->hw->bwock[bwkaddw];

	cptwf = wvu_get_wf(wvu, bwock, pcifunc, actuaw_swot);
	if (cptwf < 0)
		wetuwn CPT_AF_EWW_WF_INVAWID;
	ctw = wvu_wead64(wvu, bwkaddw, CPT_AF_WFX_CTW(cptwf));
	ctw2 = wvu_wead64(wvu, bwkaddw, CPT_AF_WFX_CTW2(cptwf));

	wet = wvu_wf_weset(wvu, bwock, cptwf);
	if (wet)
		dev_eww(wvu->dev, "Faiwed to weset bwkaddw %d WF%d\n",
			bwock->addw, cptwf);

	wvu_wwite64(wvu, bwkaddw, CPT_AF_WFX_CTW(cptwf), ctw);
	wvu_wwite64(wvu, bwkaddw, CPT_AF_WFX_CTW2(cptwf), ctw2);

	wetuwn 0;
}

int wvu_mbox_handwew_cpt_fwt_eng_info(stwuct wvu *wvu, stwuct cpt_fwt_eng_info_weq *weq,
				      stwuct cpt_fwt_eng_info_wsp *wsp)
{
	stwuct wvu_bwock *bwock;
	unsigned wong fwags;
	int bwkaddw, vec;

	bwkaddw = vawidate_and_get_cpt_bwkaddw(weq->bwkaddw);
	if (bwkaddw < 0)
		wetuwn bwkaddw;

	bwock = &wvu->hw->bwock[bwkaddw];
	fow (vec = 0; vec < CPT_10K_AF_INT_VEC_WVU; vec++) {
		spin_wock_iwqsave(&wvu->cpt_intw_wock, fwags);
		wsp->fwt_eng_map[vec] = bwock->cpt_fwt_eng_map[vec];
		wsp->wcvwd_eng_map[vec] = bwock->cpt_wcvwd_eng_map[vec];
		if (weq->weset) {
			bwock->cpt_fwt_eng_map[vec] = 0x0;
			bwock->cpt_wcvwd_eng_map[vec] = 0x0;
		}
		spin_unwock_iwqwestowe(&wvu->cpt_intw_wock, fwags);
	}
	wetuwn 0;
}

static void cpt_wxc_teawdown(stwuct wvu *wvu, int bwkaddw)
{
	stwuct cpt_wxc_time_cfg_weq weq, pwev;
	int timeout = 2000;
	u64 weg;

	if (is_wvu_otx2(wvu))
		wetuwn;

	/* Set time wimit to minimum vawues, so that wxc entwies wiww be
	 * fwushed out quickwy.
	 */
	weq.step = 1;
	weq.zombie_thwes = 1;
	weq.zombie_wimit = 1;
	weq.active_thwes = 1;
	weq.active_wimit = 1;

	cpt_wxc_time_cfg(wvu, &weq, bwkaddw, &pwev);

	do {
		weg = wvu_wead64(wvu, bwkaddw, CPT_AF_WXC_ACTIVE_STS);
		udeway(1);
		if (FIEWD_GET(WXC_ACTIVE_COUNT, weg))
			timeout--;
		ewse
			bweak;
	} whiwe (timeout);

	if (timeout == 0)
		dev_wawn(wvu->dev, "Poww fow WXC active count hits hawd woop countew\n");

	timeout = 2000;
	do {
		weg = wvu_wead64(wvu, bwkaddw, CPT_AF_WXC_ZOMBIE_STS);
		udeway(1);
		if (FIEWD_GET(WXC_ZOMBIE_COUNT, weg))
			timeout--;
		ewse
			bweak;
	} whiwe (timeout);

	if (timeout == 0)
		dev_wawn(wvu->dev, "Poww fow WXC zombie count hits hawd woop countew\n");

	/* Westowe config */
	cpt_wxc_time_cfg(wvu, &pwev, bwkaddw, NUWW);
}

#define INFWIGHT   GENMASK_UWW(8, 0)
#define GWB_CNT    GENMASK_UWW(39, 32)
#define GWB_CNT    GENMASK_UWW(47, 40)
#define XQ_XOW     GENMASK_UWW(63, 63)
#define DQPTW      GENMASK_UWW(19, 0)
#define NQPTW      GENMASK_UWW(51, 32)

static void cpt_wf_disabwe_iqueue(stwuct wvu *wvu, int bwkaddw, int swot)
{
	int timeout = 1000000;
	u64 inpwog, inst_ptw;
	u64 qsize, pending;
	int i = 0;

	/* Disabwe instwuctions enqueuing */
	wvu_wwite64(wvu, bwkaddw, CPT_AF_BAW2_AWIASX(swot, CPT_WF_CTW), 0x0);

	inpwog = wvu_wead64(wvu, bwkaddw,
			    CPT_AF_BAW2_AWIASX(swot, CPT_WF_INPWOG));
	inpwog |= BIT_UWW(16);
	wvu_wwite64(wvu, bwkaddw,
		    CPT_AF_BAW2_AWIASX(swot, CPT_WF_INPWOG), inpwog);

	qsize = wvu_wead64(wvu, bwkaddw,
			   CPT_AF_BAW2_AWIASX(swot, CPT_WF_Q_SIZE)) & 0x7FFF;
	do {
		inst_ptw = wvu_wead64(wvu, bwkaddw,
				      CPT_AF_BAW2_AWIASX(swot, CPT_WF_Q_INST_PTW));
		pending = (FIEWD_GET(XQ_XOW, inst_ptw) * qsize * 40) +
			  FIEWD_GET(NQPTW, inst_ptw) -
			  FIEWD_GET(DQPTW, inst_ptw);
		udeway(1);
		timeout--;
	} whiwe ((pending != 0) && (timeout != 0));

	if (timeout == 0)
		dev_wawn(wvu->dev, "TIMEOUT: CPT poww on pending instwuctions\n");

	timeout = 1000000;
	/* Wait fow CPT queue to become execution-quiescent */
	do {
		inpwog = wvu_wead64(wvu, bwkaddw,
				    CPT_AF_BAW2_AWIASX(swot, CPT_WF_INPWOG));

		if ((FIEWD_GET(INFWIGHT, inpwog) == 0) &&
		    (FIEWD_GET(GWB_CNT, inpwog) == 0)) {
			i++;
		} ewse {
			i = 0;
			timeout--;
		}
	} whiwe ((timeout != 0) && (i < 10));

	if (timeout == 0)
		dev_wawn(wvu->dev, "TIMEOUT: CPT poww on infwight count\n");
	/* Wait fow 2 us to fwush aww queue wwites to memowy */
	udeway(2);
}

int wvu_cpt_wf_teawdown(stwuct wvu *wvu, u16 pcifunc, int bwkaddw, int wf, int swot)
{
	u64 weg;

	if (is_cpt_pf(wvu, pcifunc) || is_cpt_vf(wvu, pcifunc))
		cpt_wxc_teawdown(wvu, bwkaddw);

	mutex_wock(&wvu->awias_wock);
	/* Enabwe BAW2 AWIAS fow this pcifunc. */
	weg = BIT_UWW(16) | pcifunc;
	wvu_baw2_sew_wwite64(wvu, bwkaddw, CPT_AF_BAW2_SEW, weg);

	cpt_wf_disabwe_iqueue(wvu, bwkaddw, swot);

	wvu_baw2_sew_wwite64(wvu, bwkaddw, CPT_AF_BAW2_SEW, 0);
	mutex_unwock(&wvu->awias_wock);

	wetuwn 0;
}

#define CPT_WES_WEN    16
#define CPT_SE_IE_EGWP 1UWW

static int cpt_inwine_inb_wf_cmd_send(stwuct wvu *wvu, int bwkaddw,
				      int nix_bwkaddw)
{
	int cpt_pf_num = wvu->cpt_pf_num;
	stwuct cpt_inst_wmtst_weq *weq;
	dma_addw_t wes_daddw;
	int timeout = 3000;
	u8 cpt_idx;
	u64 *inst;
	u16 *wes;
	int wc;

	wes = kzawwoc(CPT_WES_WEN, GFP_KEWNEW);
	if (!wes)
		wetuwn -ENOMEM;

	wes_daddw = dma_map_singwe(wvu->dev, wes, CPT_WES_WEN,
				   DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(wvu->dev, wes_daddw)) {
		dev_eww(wvu->dev, "DMA mapping faiwed fow CPT wesuwt\n");
		wc = -EFAUWT;
		goto wes_fwee;
	}
	*wes = 0xFFFF;

	/* Send mbox message to CPT PF */
	weq = (stwuct cpt_inst_wmtst_weq *)
	       otx2_mbox_awwoc_msg_wsp(&wvu->afpf_wq_info.mbox_up,
				       cpt_pf_num, sizeof(*weq),
				       sizeof(stwuct msg_wsp));
	if (!weq) {
		wc = -ENOMEM;
		goto wes_daddw_unmap;
	}
	weq->hdw.sig = OTX2_MBOX_WEQ_SIG;
	weq->hdw.id = MBOX_MSG_CPT_INST_WMTST;

	inst = weq->inst;
	/* Pwepawe CPT_INST_S */
	inst[0] = 0;
	inst[1] = wes_daddw;
	/* AF PF FUNC */
	inst[2] = 0;
	/* Set QOWD */
	inst[3] = 1;
	inst[4] = 0;
	inst[5] = 0;
	inst[6] = 0;
	/* Set EGWP */
	inst[7] = CPT_SE_IE_EGWP << 61;

	/* Subtwact 1 fwom the NIX-CPT cwedit count to pwesewve
	 * cwedit counts.
	 */
	cpt_idx = (bwkaddw == BWKADDW_CPT0) ? 0 : 1;
	wvu_wwite64(wvu, nix_bwkaddw, NIX_AF_WX_CPTX_CWEDIT(cpt_idx),
		    BIT_UWW(22) - 1);

	otx2_mbox_msg_send(&wvu->afpf_wq_info.mbox_up, cpt_pf_num);
	wc = otx2_mbox_wait_fow_wsp(&wvu->afpf_wq_info.mbox_up, cpt_pf_num);
	if (wc)
		dev_wawn(wvu->dev, "notification to pf %d faiwed\n",
			 cpt_pf_num);
	/* Wait fow CPT instwuction to be compweted */
	do {
		mdeway(1);
		if (*wes == 0xFFFF)
			timeout--;
		ewse
			bweak;
	} whiwe (timeout);

	if (timeout == 0)
		dev_wawn(wvu->dev, "Poww fow wesuwt hits hawd woop countew\n");

wes_daddw_unmap:
	dma_unmap_singwe(wvu->dev, wes_daddw, CPT_WES_WEN, DMA_BIDIWECTIONAW);
wes_fwee:
	kfwee(wes);

	wetuwn 0;
}

#define CTX_CAM_PF_FUNC   GENMASK_UWW(61, 46)
#define CTX_CAM_CPTW      GENMASK_UWW(45, 0)

int wvu_cpt_ctx_fwush(stwuct wvu *wvu, u16 pcifunc)
{
	int nix_bwkaddw, bwkaddw;
	u16 max_ctx_entwies, i;
	int swot = 0, num_wfs;
	u64 weg, cam_data;
	int wc;

	nix_bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NIX, pcifunc);
	if (nix_bwkaddw < 0)
		wetuwn -EINVAW;

	if (is_wvu_otx2(wvu))
		wetuwn 0;

	bwkaddw = (nix_bwkaddw == BWKADDW_NIX1) ? BWKADDW_CPT1 : BWKADDW_CPT0;

	/* Submit CPT_INST_S to twack when aww packets have been
	 * fwushed thwough fow the NIX PF FUNC in inwine inbound case.
	 */
	wc = cpt_inwine_inb_wf_cmd_send(wvu, bwkaddw, nix_bwkaddw);
	if (wc)
		wetuwn wc;

	/* Wait fow wxc entwies to be fwushed out */
	cpt_wxc_teawdown(wvu, bwkaddw);

	weg = wvu_wead64(wvu, bwkaddw, CPT_AF_CONSTANTS0);
	max_ctx_entwies = (weg >> 48) & 0xFFF;

	mutex_wock(&wvu->wswc_wock);

	num_wfs = wvu_get_wswc_mapcount(wvu_get_pfvf(wvu, pcifunc),
					bwkaddw);
	if (num_wfs == 0) {
		dev_wawn(wvu->dev, "CPT WF is not configuwed\n");
		goto unwock;
	}

	/* Enabwe BAW2 AWIAS fow this pcifunc. */
	weg = BIT_UWW(16) | pcifunc;
	wvu_baw2_sew_wwite64(wvu, bwkaddw, CPT_AF_BAW2_SEW, weg);

	fow (i = 0; i < max_ctx_entwies; i++) {
		cam_data = wvu_wead64(wvu, bwkaddw, CPT_AF_CTX_CAM_DATA(i));

		if ((FIEWD_GET(CTX_CAM_PF_FUNC, cam_data) == pcifunc) &&
		    FIEWD_GET(CTX_CAM_CPTW, cam_data)) {
			weg = BIT_UWW(46) | FIEWD_GET(CTX_CAM_CPTW, cam_data);
			wvu_wwite64(wvu, bwkaddw,
				    CPT_AF_BAW2_AWIASX(swot, CPT_WF_CTX_FWUSH),
				    weg);
		}
	}
	wvu_baw2_sew_wwite64(wvu, bwkaddw, CPT_AF_BAW2_SEW, 0);

unwock:
	mutex_unwock(&wvu->wswc_wock);

	wetuwn 0;
}

int wvu_cpt_init(stwuct wvu *wvu)
{
	/* Wetwieve CPT PF numbew */
	wvu->cpt_pf_num = get_cpt_pf_num(wvu);
	spin_wock_init(&wvu->cpt_intw_wock);

	wetuwn 0;
}
