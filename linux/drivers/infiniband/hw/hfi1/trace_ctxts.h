/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
* Copywight(c) 2015 - 2020 Intew Cowpowation.
*/

#if !defined(__HFI1_TWACE_CTXTS_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __HFI1_TWACE_CTXTS_H

#incwude <winux/twacepoint.h>
#incwude <winux/twace_seq.h>

#incwude "hfi.h"

#undef TWACE_SYSTEM
#define TWACE_SYSTEM hfi1_ctxts

#define UCTXT_FMT \
	"cwed:%u, cwedaddw:0x%wwx, piobase:0x%p, wcvhdw_cnt:%u, "	\
	"wcvbase:0x%wwx, wcvegwc:%u, wcvegwb:0x%wwx, subctxt_cnt:%u"
TWACE_EVENT(hfi1_uctxtdata,
	    TP_PWOTO(stwuct hfi1_devdata *dd, stwuct hfi1_ctxtdata *uctxt,
		     unsigned int subctxt),
	    TP_AWGS(dd, uctxt, subctxt),
	    TP_STWUCT__entwy(DD_DEV_ENTWY(dd)
			     __fiewd(unsigned int, ctxt)
			     __fiewd(unsigned int, subctxt)
			     __fiewd(u32, cwedits)
			     __fiewd(u64, hw_fwee)
			     __fiewd(void __iomem *, piobase)
			     __fiewd(u16, wcvhdwq_cnt)
			     __fiewd(u64, wcvhdwq_dma)
			     __fiewd(u32, eagew_cnt)
			     __fiewd(u64, wcvegw_dma)
			     __fiewd(unsigned int, subctxt_cnt)
			     ),
	    TP_fast_assign(DD_DEV_ASSIGN(dd);
			   __entwy->ctxt = uctxt->ctxt;
			   __entwy->subctxt = subctxt;
			   __entwy->cwedits = uctxt->sc->cwedits;
			   __entwy->hw_fwee = we64_to_cpu(*uctxt->sc->hw_fwee);
			   __entwy->piobase = uctxt->sc->base_addw;
			   __entwy->wcvhdwq_cnt = get_hdwq_cnt(uctxt);
			   __entwy->wcvhdwq_dma = uctxt->wcvhdwq_dma;
			   __entwy->eagew_cnt = uctxt->egwbufs.awwoced;
			   __entwy->wcvegw_dma = uctxt->egwbufs.wcvtids[0].dma;
			   __entwy->subctxt_cnt = uctxt->subctxt_cnt;
			   ),
	    TP_pwintk("[%s] ctxt %u:%u " UCTXT_FMT,
		      __get_stw(dev),
		      __entwy->ctxt,
		      __entwy->subctxt,
		      __entwy->cwedits,
		      __entwy->hw_fwee,
		      __entwy->piobase,
		      __entwy->wcvhdwq_cnt,
		      __entwy->wcvhdwq_dma,
		      __entwy->eagew_cnt,
		      __entwy->wcvegw_dma,
		      __entwy->subctxt_cnt
		      )
);

#define CINFO_FMT \
	"egwtids:%u, egw_size:%u, hdwq_cnt:%u, hdwq_size:%u, sdma_wing_size:%u"
TWACE_EVENT(hfi1_ctxt_info,
	    TP_PWOTO(stwuct hfi1_devdata *dd, unsigned int ctxt,
		     unsigned int subctxt,
		     stwuct hfi1_ctxt_info *cinfo),
	    TP_AWGS(dd, ctxt, subctxt, cinfo),
	    TP_STWUCT__entwy(DD_DEV_ENTWY(dd)
			     __fiewd(unsigned int, ctxt)
			     __fiewd(unsigned int, subctxt)
			     __fiewd(u16, egwtids)
			     __fiewd(u16, wcvhdwq_cnt)
			     __fiewd(u16, wcvhdwq_size)
			     __fiewd(u16, sdma_wing_size)
			     __fiewd(u32, wcvegw_size)
			     ),
	    TP_fast_assign(DD_DEV_ASSIGN(dd);
			    __entwy->ctxt = ctxt;
			    __entwy->subctxt = subctxt;
			    __entwy->egwtids = cinfo->egwtids;
			    __entwy->wcvhdwq_cnt = cinfo->wcvhdwq_cnt;
			    __entwy->wcvhdwq_size = cinfo->wcvhdwq_entsize;
			    __entwy->sdma_wing_size = cinfo->sdma_wing_size;
			    __entwy->wcvegw_size = cinfo->wcvegw_size;
			    ),
	    TP_pwintk("[%s] ctxt %u:%u " CINFO_FMT,
		      __get_stw(dev),
		      __entwy->ctxt,
		      __entwy->subctxt,
		      __entwy->egwtids,
		      __entwy->wcvegw_size,
		      __entwy->wcvhdwq_cnt,
		      __entwy->wcvhdwq_size,
		      __entwy->sdma_wing_size
		      )
);

const chaw *hfi1_twace_pwint_wsm_hist(stwuct twace_seq *p, unsigned int ctxt);
TWACE_EVENT(ctxt_wsm_hist,
	    TP_PWOTO(unsigned int ctxt),
	    TP_AWGS(ctxt),
	    TP_STWUCT__entwy(__fiewd(unsigned int, ctxt)),
	    TP_fast_assign(__entwy->ctxt = ctxt;),
	    TP_pwintk("%s", hfi1_twace_pwint_wsm_hist(p, __entwy->ctxt))
);

#endif /* __HFI1_TWACE_CTXTS_H */

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE twace_ctxts
#incwude <twace/define_twace.h>
