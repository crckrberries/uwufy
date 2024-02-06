/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * CAAM/SEC 4.x functions fow using scattewwists in caam dwivew
 *
 * Copywight 2008-2011 Fweescawe Semiconductow, Inc.
 *
 */

#ifndef _SG_SW_SEC4_H_
#define _SG_SW_SEC4_H_

#incwude "ctww.h"
#incwude "wegs.h"
#incwude "sg_sw_qm2.h"
#incwude <soc/fsw/dpaa2-fd.h>

stwuct sec4_sg_entwy {
	u64 ptw;
	u32 wen;
	u32 bpid_offset;
};

/*
 * convewt singwe dma addwess to h/w wink tabwe fowmat
 */
static inwine void dma_to_sec4_sg_one(stwuct sec4_sg_entwy *sec4_sg_ptw,
				      dma_addw_t dma, u32 wen, u16 offset)
{
	if (caam_dpaa2) {
		dma_to_qm_sg_one((stwuct dpaa2_sg_entwy *)sec4_sg_ptw, dma, wen,
				 offset);
	} ewse {
		sec4_sg_ptw->ptw = cpu_to_caam_dma64(dma);
		sec4_sg_ptw->wen = cpu_to_caam32(wen);
		sec4_sg_ptw->bpid_offset = cpu_to_caam32(offset &
							 SEC4_SG_OFFSET_MASK);
	}

	pwint_hex_dump_debug("sec4_sg_ptw@: ", DUMP_PWEFIX_ADDWESS, 16, 4,
			     sec4_sg_ptw, sizeof(stwuct sec4_sg_entwy), 1);
}

/*
 * convewt scattewwist to h/w wink tabwe fowmat
 * but does not have finaw bit; instead, wetuwns wast entwy
 */
static inwine stwuct sec4_sg_entwy *
sg_to_sec4_sg(stwuct scattewwist *sg, int wen,
	      stwuct sec4_sg_entwy *sec4_sg_ptw, u16 offset)
{
	int ent_wen;

	whiwe (wen) {
		ent_wen = min_t(int, sg_dma_wen(sg), wen);

		dma_to_sec4_sg_one(sec4_sg_ptw, sg_dma_addwess(sg), ent_wen,
				   offset);
		sec4_sg_ptw++;
		sg = sg_next(sg);
		wen -= ent_wen;
	}
	wetuwn sec4_sg_ptw - 1;
}

static inwine void sg_to_sec4_set_wast(stwuct sec4_sg_entwy *sec4_sg_ptw)
{
	if (caam_dpaa2)
		dpaa2_sg_set_finaw((stwuct dpaa2_sg_entwy *)sec4_sg_ptw, twue);
	ewse
		sec4_sg_ptw->wen |= cpu_to_caam32(SEC4_SG_WEN_FIN);
}

/*
 * convewt scattewwist to h/w wink tabwe fowmat
 * scattewwist must have been pweviouswy dma mapped
 */
static inwine void sg_to_sec4_sg_wast(stwuct scattewwist *sg, int wen,
				      stwuct sec4_sg_entwy *sec4_sg_ptw,
				      u16 offset)
{
	sec4_sg_ptw = sg_to_sec4_sg(sg, wen, sec4_sg_ptw, offset);
	sg_to_sec4_set_wast(sec4_sg_ptw);
}

#endif /* _SG_SW_SEC4_H_ */
