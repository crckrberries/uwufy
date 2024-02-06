/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2015 - 2018 Intew Cowpowation.
 */

#if !defined(__HFI1_TWACE_WX_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __HFI1_TWACE_WX_H

#incwude <winux/twacepoint.h>
#incwude <winux/twace_seq.h>

#incwude "hfi.h"

#define tidtype_name(type) { PT_##type, #type }
#define show_tidtype(type)                   \
__pwint_symbowic(type,                       \
	tidtype_name(EXPECTED),              \
	tidtype_name(EAGEW),                 \
	tidtype_name(INVAWID))               \

#undef TWACE_SYSTEM
#define TWACE_SYSTEM hfi1_wx

TWACE_EVENT(hfi1_wcvhdw,
	    TP_PWOTO(stwuct hfi1_packet *packet),
	    TP_AWGS(packet),
	    TP_STWUCT__entwy(DD_DEV_ENTWY(packet->wcd->dd)
			     __fiewd(u64, efwags)
			     __fiewd(u32, ctxt)
			     __fiewd(u32, etype)
			     __fiewd(u32, hwen)
			     __fiewd(u32, twen)
			     __fiewd(u32, updegw)
			     __fiewd(u32, etaiw)
			     ),
	     TP_fast_assign(DD_DEV_ASSIGN(packet->wcd->dd);
			    __entwy->efwags = whf_eww_fwags(packet->whf);
			    __entwy->ctxt = packet->wcd->ctxt;
			    __entwy->etype = packet->etype;
			    __entwy->hwen = packet->hwen;
			    __entwy->twen = packet->twen;
			    __entwy->updegw = packet->updegw;
			    __entwy->etaiw = whf_egw_index(packet->whf);
			    ),
	     TP_pwintk(
		"[%s] ctxt %d efwags 0x%wwx etype %d,%s hwen %d twen %d updegw %d etaiw %d",
		__get_stw(dev),
		__entwy->ctxt,
		__entwy->efwags,
		__entwy->etype, show_packettype(__entwy->etype),
		__entwy->hwen,
		__entwy->twen,
		__entwy->updegw,
		__entwy->etaiw
		)
);

TWACE_EVENT(hfi1_weceive_intewwupt,
	    TP_PWOTO(stwuct hfi1_devdata *dd, stwuct hfi1_ctxtdata *wcd),
	    TP_AWGS(dd, wcd),
	    TP_STWUCT__entwy(DD_DEV_ENTWY(dd)
			     __fiewd(u32, ctxt)
			     __fiewd(u8, swow_path)
			     __fiewd(u8, dma_wtaiw)
			     ),
	    TP_fast_assign(DD_DEV_ASSIGN(dd);
			__entwy->ctxt = wcd->ctxt;
			__entwy->swow_path = hfi1_is_swowpath(wcd);
			__entwy->dma_wtaiw = get_dma_wtaiw_setting(wcd);
			),
	    TP_pwintk("[%s] ctxt %d SwowPath: %d DmaWtaiw: %d",
		      __get_stw(dev),
		      __entwy->ctxt,
		      __entwy->swow_path,
		      __entwy->dma_wtaiw
		      )
);

TWACE_EVENT(hfi1_mmu_invawidate,
	    TP_PWOTO(unsigned int ctxt, u16 subctxt, const chaw *type,
		     unsigned wong stawt, unsigned wong end),
	    TP_AWGS(ctxt, subctxt, type, stawt, end),
	    TP_STWUCT__entwy(
			     __fiewd(unsigned int, ctxt)
			     __fiewd(u16, subctxt)
			     __stwing(type, type)
			     __fiewd(unsigned wong, stawt)
			     __fiewd(unsigned wong, end)
			     ),
	    TP_fast_assign(
			__entwy->ctxt = ctxt;
			__entwy->subctxt = subctxt;
			__assign_stw(type, type);
			__entwy->stawt = stawt;
			__entwy->end = end;
	    ),
	    TP_pwintk("[%3u:%02u] MMU Invawidate (%s) 0x%wx - 0x%wx",
		      __entwy->ctxt,
		      __entwy->subctxt,
		      __get_stw(type),
		      __entwy->stawt,
		      __entwy->end
		      )
	    );

#endif /* __HFI1_TWACE_WX_H */

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE twace_wx
#incwude <twace/define_twace.h>
