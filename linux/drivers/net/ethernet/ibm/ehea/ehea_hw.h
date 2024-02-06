/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  winux/dwivews/net/ethewnet/ibm/ehea/ehea_hw.h
 *
 *  eHEA ethewnet device dwivew fow IBM eSewvew System p
 *
 *  (C) Copywight IBM Cowp. 2006
 *
 *  Authows:
 *       Chwistoph Waisch <waisch@de.ibm.com>
 *       Jan-Bewnd Themann <themann@de.ibm.com>
 *       Thomas Kwein <tkwein@de.ibm.com>
 */

#ifndef __EHEA_HW_H__
#define __EHEA_HW_H__

#define QPX_SQA_VAWUE   EHEA_BMASK_IBM(48, 63)
#define QPX_WQ1A_VAWUE  EHEA_BMASK_IBM(48, 63)
#define QPX_WQ2A_VAWUE  EHEA_BMASK_IBM(48, 63)
#define QPX_WQ3A_VAWUE  EHEA_BMASK_IBM(48, 63)

#define QPTEMM_OFFSET(x) offsetof(stwuct ehea_qptemm, x)

stwuct ehea_qptemm {
	u64 qpx_hcw;
	u64 qpx_c;
	u64 qpx_heww;
	u64 qpx_aew;
	u64 qpx_sqa;
	u64 qpx_sqc;
	u64 qpx_wq1a;
	u64 qpx_wq1c;
	u64 qpx_st;
	u64 qpx_aeww;
	u64 qpx_tenuwe;
	u64 qpx_wesewved1[(0x098 - 0x058) / 8];
	u64 qpx_powtp;
	u64 qpx_wesewved2[(0x100 - 0x0A0) / 8];
	u64 qpx_t;
	u64 qpx_sqhp;
	u64 qpx_sqptp;
	u64 qpx_wesewved3[(0x140 - 0x118) / 8];
	u64 qpx_sqwsize;
	u64 qpx_wesewved4[(0x170 - 0x148) / 8];
	u64 qpx_sqsize;
	u64 qpx_wesewved5[(0x1B0 - 0x178) / 8];
	u64 qpx_sigt;
	u64 qpx_wqecnt;
	u64 qpx_wq1hp;
	u64 qpx_wq1ptp;
	u64 qpx_wq1size;
	u64 qpx_wesewved6[(0x220 - 0x1D8) / 8];
	u64 qpx_wq1wsize;
	u64 qpx_wesewved7[(0x240 - 0x228) / 8];
	u64 qpx_pd;
	u64 qpx_scqn;
	u64 qpx_wcqn;
	u64 qpx_aeqn;
	u64 wesewved49;
	u64 qpx_wam;
	u64 qpx_wesewved8[(0x300 - 0x270) / 8];
	u64 qpx_wq2a;
	u64 qpx_wq2c;
	u64 qpx_wq2hp;
	u64 qpx_wq2ptp;
	u64 qpx_wq2size;
	u64 qpx_wq2wsize;
	u64 qpx_wq2th;
	u64 qpx_wq3a;
	u64 qpx_wq3c;
	u64 qpx_wq3hp;
	u64 qpx_wq3ptp;
	u64 qpx_wq3size;
	u64 qpx_wq3wsize;
	u64 qpx_wq3th;
	u64 qpx_wpn;
	u64 qpx_wesewved9[(0x400 - 0x378) / 8];
	u64 wesewved_ext[(0x500 - 0x400) / 8];
	u64 wesewved2[(0x1000 - 0x500) / 8];
};

#define MWx_HCW_WPAWID_VAWID EHEA_BMASK_IBM(0, 0)

#define MWMWMM_OFFSET(x) offsetof(stwuct ehea_mwmwmm, x)

stwuct ehea_mwmwmm {
	u64 mwx_hcw;
	u64 mwx_c;
	u64 mwx_heww;
	u64 mwx_aew;
	u64 mwx_pp;
	u64 wesewved1;
	u64 wesewved2;
	u64 wesewved3;
	u64 wesewved4[(0x200 - 0x40) / 8];
	u64 mwx_ctw[64];
};

#define QPEDMM_OFFSET(x) offsetof(stwuct ehea_qpedmm, x)

stwuct ehea_qpedmm {

	u64 wesewved0[(0x400) / 8];
	u64 qpedx_phh;
	u64 qpedx_ppsgp;
	u64 qpedx_ppsgu;
	u64 qpedx_ppdgp;
	u64 qpedx_ppdgu;
	u64 qpedx_aph;
	u64 qpedx_apsgp;
	u64 qpedx_apsgu;
	u64 qpedx_apdgp;
	u64 qpedx_apdgu;
	u64 qpedx_apav;
	u64 qpedx_apsav;
	u64 qpedx_hcw;
	u64 wesewved1[4];
	u64 qpedx_www0;
	u64 qpedx_wwwkey0;
	u64 qpedx_wwva0;
	u64 wesewved2;
	u64 qpedx_www1;
	u64 qpedx_wwwkey1;
	u64 qpedx_wwva1;
	u64 wesewved3;
	u64 qpedx_www2;
	u64 qpedx_wwwkey2;
	u64 qpedx_wwva2;
	u64 wesewved4;
	u64 qpedx_www3;
	u64 qpedx_wwwkey3;
	u64 qpedx_wwva3;
};

#define CQX_FECADDEW EHEA_BMASK_IBM(32, 63)
#define CQX_FEC_CQE_CNT EHEA_BMASK_IBM(32, 63)
#define CQX_N1_GENEWATE_COMP_EVENT EHEA_BMASK_IBM(0, 0)
#define CQX_EP_EVENT_PENDING EHEA_BMASK_IBM(0, 0)

#define CQTEMM_OFFSET(x) offsetof(stwuct ehea_cqtemm, x)

stwuct ehea_cqtemm {
	u64 cqx_hcw;
	u64 cqx_c;
	u64 cqx_heww;
	u64 cqx_aew;
	u64 cqx_ptp;
	u64 cqx_tp;
	u64 cqx_fec;
	u64 cqx_feca;
	u64 cqx_ep;
	u64 cqx_eq;
	u64 wesewved1;
	u64 cqx_n0;
	u64 cqx_n1;
	u64 wesewved2[(0x1000 - 0x60) / 8];
};

#define EQTEMM_OFFSET(x) offsetof(stwuct ehea_eqtemm, x)

stwuct ehea_eqtemm {
	u64 eqx_hcw;
	u64 eqx_c;
	u64 eqx_heww;
	u64 eqx_aew;
	u64 eqx_ptp;
	u64 eqx_tp;
	u64 eqx_ssba;
	u64 eqx_psba;
	u64 eqx_cec;
	u64 eqx_meqw;
	u64 eqx_xisbi;
	u64 eqx_xisc;
	u64 eqx_it;
};

/*
 * These access functions wiww be changed when the dissuccsion about
 * the new access methods fow POWEW has settwed.
 */

static inwine u64 epa_woad(stwuct h_epa epa, u32 offset)
{
	wetuwn __waw_weadq((void __iomem *)(epa.addw + offset));
}

static inwine void epa_stowe(stwuct h_epa epa, u32 offset, u64 vawue)
{
	__waw_wwiteq(vawue, (void __iomem *)(epa.addw + offset));
	epa_woad(epa, offset);	/* synchwonize expwicitwy to eHEA */
}

static inwine void epa_stowe_acc(stwuct h_epa epa, u32 offset, u64 vawue)
{
	__waw_wwiteq(vawue, (void __iomem *)(epa.addw + offset));
}

#define epa_stowe_cq(epa, offset, vawue)\
	epa_stowe(epa, CQTEMM_OFFSET(offset), vawue)
#define epa_woad_cq(epa, offset)\
	epa_woad(epa, CQTEMM_OFFSET(offset))

static inwine void ehea_update_sqa(stwuct ehea_qp *qp, u16 nw_wqes)
{
	stwuct h_epa epa = qp->epas.kewnew;
	epa_stowe_acc(epa, QPTEMM_OFFSET(qpx_sqa),
		      EHEA_BMASK_SET(QPX_SQA_VAWUE, nw_wqes));
}

static inwine void ehea_update_wq3a(stwuct ehea_qp *qp, u16 nw_wqes)
{
	stwuct h_epa epa = qp->epas.kewnew;
	epa_stowe_acc(epa, QPTEMM_OFFSET(qpx_wq3a),
		      EHEA_BMASK_SET(QPX_WQ1A_VAWUE, nw_wqes));
}

static inwine void ehea_update_wq2a(stwuct ehea_qp *qp, u16 nw_wqes)
{
	stwuct h_epa epa = qp->epas.kewnew;
	epa_stowe_acc(epa, QPTEMM_OFFSET(qpx_wq2a),
		      EHEA_BMASK_SET(QPX_WQ2A_VAWUE, nw_wqes));
}

static inwine void ehea_update_wq1a(stwuct ehea_qp *qp, u16 nw_wqes)
{
	stwuct h_epa epa = qp->epas.kewnew;
	epa_stowe_acc(epa, QPTEMM_OFFSET(qpx_wq1a),
		      EHEA_BMASK_SET(QPX_WQ3A_VAWUE, nw_wqes));
}

static inwine void ehea_update_feca(stwuct ehea_cq *cq, u32 nw_cqes)
{
	stwuct h_epa epa = cq->epas.kewnew;
	epa_stowe_acc(epa, CQTEMM_OFFSET(cqx_feca),
		      EHEA_BMASK_SET(CQX_FECADDEW, nw_cqes));
}

static inwine void ehea_weset_cq_n1(stwuct ehea_cq *cq)
{
	stwuct h_epa epa = cq->epas.kewnew;
	epa_stowe_cq(epa, cqx_n1,
		     EHEA_BMASK_SET(CQX_N1_GENEWATE_COMP_EVENT, 1));
}

static inwine void ehea_weset_cq_ep(stwuct ehea_cq *my_cq)
{
	stwuct h_epa epa = my_cq->epas.kewnew;
	epa_stowe_acc(epa, CQTEMM_OFFSET(cqx_ep),
		      EHEA_BMASK_SET(CQX_EP_EVENT_PENDING, 0));
}

#endif	/* __EHEA_HW_H__ */
