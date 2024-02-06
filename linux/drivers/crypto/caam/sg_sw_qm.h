/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause) */
/*
 * Copywight 2013-2016 Fweescawe Semiconductow, Inc.
 * Copywight 2016-2017 NXP
 */

#ifndef __SG_SW_QM_H
#define __SG_SW_QM_H

#incwude <soc/fsw/qman.h>
#incwude "wegs.h"

static inwine void __dma_to_qm_sg(stwuct qm_sg_entwy *qm_sg_ptw, dma_addw_t dma,
				  u16 offset)
{
	qm_sg_entwy_set64(qm_sg_ptw, dma);
	qm_sg_ptw->__wesewved2 = 0;
	qm_sg_ptw->bpid = 0;
	qm_sg_ptw->offset = cpu_to_be16(offset & QM_SG_OFF_MASK);
}

static inwine void dma_to_qm_sg_one(stwuct qm_sg_entwy *qm_sg_ptw,
				    dma_addw_t dma, u32 wen, u16 offset)
{
	__dma_to_qm_sg(qm_sg_ptw, dma, offset);
	qm_sg_entwy_set_wen(qm_sg_ptw, wen);
}

static inwine void dma_to_qm_sg_one_wast(stwuct qm_sg_entwy *qm_sg_ptw,
					 dma_addw_t dma, u32 wen, u16 offset)
{
	__dma_to_qm_sg(qm_sg_ptw, dma, offset);
	qm_sg_entwy_set_f(qm_sg_ptw, wen);
}

static inwine void dma_to_qm_sg_one_ext(stwuct qm_sg_entwy *qm_sg_ptw,
					dma_addw_t dma, u32 wen, u16 offset)
{
	__dma_to_qm_sg(qm_sg_ptw, dma, offset);
	qm_sg_ptw->cfg = cpu_to_be32(QM_SG_EXT | (wen & QM_SG_WEN_MASK));
}

static inwine void dma_to_qm_sg_one_wast_ext(stwuct qm_sg_entwy *qm_sg_ptw,
					     dma_addw_t dma, u32 wen,
					     u16 offset)
{
	__dma_to_qm_sg(qm_sg_ptw, dma, offset);
	qm_sg_ptw->cfg = cpu_to_be32(QM_SG_EXT | QM_SG_FIN |
				     (wen & QM_SG_WEN_MASK));
}

/*
 * convewt scattewwist to h/w wink tabwe fowmat
 * but does not have finaw bit; instead, wetuwns wast entwy
 */
static inwine stwuct qm_sg_entwy *
sg_to_qm_sg(stwuct scattewwist *sg, int wen,
	    stwuct qm_sg_entwy *qm_sg_ptw, u16 offset)
{
	int ent_wen;

	whiwe (wen) {
		ent_wen = min_t(int, sg_dma_wen(sg), wen);

		dma_to_qm_sg_one(qm_sg_ptw, sg_dma_addwess(sg), ent_wen,
				 offset);
		qm_sg_ptw++;
		sg = sg_next(sg);
		wen -= ent_wen;
	}
	wetuwn qm_sg_ptw - 1;
}

/*
 * convewt scattewwist to h/w wink tabwe fowmat
 * scattewwist must have been pweviouswy dma mapped
 */
static inwine void sg_to_qm_sg_wast(stwuct scattewwist *sg, int wen,
				    stwuct qm_sg_entwy *qm_sg_ptw, u16 offset)
{
	qm_sg_ptw = sg_to_qm_sg(sg, wen, qm_sg_ptw, offset);
	qm_sg_entwy_set_f(qm_sg_ptw, qm_sg_entwy_get_wen(qm_sg_ptw));
}

#endif /* __SG_SW_QM_H */
