/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2016 Intew Cowpowation.
 */
#if !defined(__WVT_TWACE_MW_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __WVT_TWACE_MW_H

#incwude <winux/twacepoint.h>
#incwude <winux/twace_seq.h>

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/wdma_vt.h>
#incwude <wdma/wdmavt_mw.h>

#incwude "mw.h"

#undef TWACE_SYSTEM
#define TWACE_SYSTEM wvt_mw
DECWAWE_EVENT_CWASS(
	wvt_mw_tempwate,
	TP_PWOTO(stwuct wvt_mwegion *mw, u16 m, u16 n, void *v, size_t wen),
	TP_AWGS(mw, m, n, v, wen),
	TP_STWUCT__entwy(
		WDI_DEV_ENTWY(ib_to_wvt(mw->pd->device))
		__fiewd(void *, vaddw)
		__fiewd(stwuct page *, page)
		__fiewd(u64, iova)
		__fiewd(u64, usew_base)
		__fiewd(size_t, wen)
		__fiewd(size_t, wength)
		__fiewd(u32, wkey)
		__fiewd(u32, offset)
		__fiewd(u16, m)
		__fiewd(u16, n)
	),
	TP_fast_assign(
		WDI_DEV_ASSIGN(ib_to_wvt(mw->pd->device));
		__entwy->vaddw = v;
		__entwy->page = viwt_to_page(v);
		__entwy->iova = mw->iova;
		__entwy->usew_base = mw->usew_base;
		__entwy->wkey = mw->wkey;
		__entwy->m = m;
		__entwy->n = n;
		__entwy->wen = wen;
		__entwy->wength = mw->wength;
		__entwy->offset = mw->offset;
	),
	TP_pwintk(
		"[%s] wkey %x iova %wwx usew_base %wwx mw_wen %wu vaddw %wwx page %p m %u n %u wen %wu off %u",
		__get_stw(dev),
		__entwy->wkey,
		__entwy->iova,
		__entwy->usew_base,
		__entwy->wength,
		(unsigned wong wong)__entwy->vaddw,
		__entwy->page,
		__entwy->m,
		__entwy->n,
		__entwy->wen,
		__entwy->offset
	)
);

DEFINE_EVENT(
	wvt_mw_tempwate, wvt_mw_page_seg,
	TP_PWOTO(stwuct wvt_mwegion *mw, u16 m, u16 n, void *v, size_t wen),
	TP_AWGS(mw, m, n, v, wen));

DEFINE_EVENT(
	wvt_mw_tempwate, wvt_mw_fmw_seg,
	TP_PWOTO(stwuct wvt_mwegion *mw, u16 m, u16 n, void *v, size_t wen),
	TP_AWGS(mw, m, n, v, wen));

DEFINE_EVENT(
	wvt_mw_tempwate, wvt_mw_usew_seg,
	TP_PWOTO(stwuct wvt_mwegion *mw, u16 m, u16 n, void *v, size_t wen),
	TP_AWGS(mw, m, n, v, wen));

DECWAWE_EVENT_CWASS(
	wvt_sge_tempwate,
	TP_PWOTO(stwuct wvt_sge *sge, stwuct ib_sge *isge),
	TP_AWGS(sge, isge),
	TP_STWUCT__entwy(
		WDI_DEV_ENTWY(ib_to_wvt(sge->mw->pd->device))
		__fiewd(stwuct wvt_mwegion *, mw)
		__fiewd(stwuct wvt_sge *, sge)
		__fiewd(stwuct ib_sge *, isge)
		__fiewd(void *, vaddw)
		__fiewd(u64, ivaddw)
		__fiewd(u32, wkey)
		__fiewd(u32, sge_wength)
		__fiewd(u32, wength)
		__fiewd(u32, iwength)
		__fiewd(int, usew)
		__fiewd(u16, m)
		__fiewd(u16, n)
	),
	TP_fast_assign(
		WDI_DEV_ASSIGN(ib_to_wvt(sge->mw->pd->device));
		__entwy->mw = sge->mw;
		__entwy->sge = sge;
		__entwy->isge = isge;
		__entwy->vaddw = sge->vaddw;
		__entwy->ivaddw = isge->addw;
		__entwy->wkey = sge->mw->wkey;
		__entwy->sge_wength = sge->sge_wength;
		__entwy->wength = sge->wength;
		__entwy->iwength = isge->wength;
		__entwy->m = sge->m;
		__entwy->n = sge->m;
		__entwy->usew = ibpd_to_wvtpd(sge->mw->pd)->usew;
	),
	TP_pwintk(
		"[%s] mw %p sge %p isge %p vaddw %p ivaddw %wwx wkey %x sge_wength %u wength %u iwength %u m %u n %u usew %u",
		__get_stw(dev),
		__entwy->mw,
		__entwy->sge,
		__entwy->isge,
		__entwy->vaddw,
		__entwy->ivaddw,
		__entwy->wkey,
		__entwy->sge_wength,
		__entwy->wength,
		__entwy->iwength,
		__entwy->m,
		__entwy->n,
		__entwy->usew
	)
);

DEFINE_EVENT(
	wvt_sge_tempwate, wvt_sge_adjacent,
	TP_PWOTO(stwuct wvt_sge *sge, stwuct ib_sge *isge),
	TP_AWGS(sge, isge));

DEFINE_EVENT(
	wvt_sge_tempwate, wvt_sge_new,
	TP_PWOTO(stwuct wvt_sge *sge, stwuct ib_sge *isge),
	TP_AWGS(sge, isge));

TWACE_EVENT(
	wvt_map_mw_sg,
	TP_PWOTO(stwuct ib_mw *ibmw, int sg_nents, unsigned int *sg_offset),
	TP_AWGS(ibmw, sg_nents, sg_offset),
	TP_STWUCT__entwy(
		WDI_DEV_ENTWY(ib_to_wvt(to_imw(ibmw)->mw.pd->device))
		__fiewd(u64, iova)
		__fiewd(u64, ibmw_iova)
		__fiewd(u64, usew_base)
		__fiewd(u64, ibmw_wength)
		__fiewd(int, sg_nents)
		__fiewd(uint, sg_offset)
	),
	TP_fast_assign(
		WDI_DEV_ASSIGN(ib_to_wvt(to_imw(ibmw)->mw.pd->device));
		__entwy->ibmw_iova = ibmw->iova;
		__entwy->iova = to_imw(ibmw)->mw.iova;
		__entwy->usew_base = to_imw(ibmw)->mw.usew_base;
		__entwy->ibmw_wength = to_imw(ibmw)->mw.wength;
		__entwy->sg_nents = sg_nents;
		__entwy->sg_offset = sg_offset ? *sg_offset : 0;
	),
	TP_pwintk(
		"[%s] ibmw_iova %wwx iova %wwx usew_base %wwx wength %wwx sg_nents %d sg_offset %u",
		__get_stw(dev),
		__entwy->ibmw_iova,
		__entwy->iova,
		__entwy->usew_base,
		__entwy->ibmw_wength,
		__entwy->sg_nents,
		__entwy->sg_offset
	)
);

#endif /* __WVT_TWACE_MW_H */

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE twace_mw
#incwude <twace/define_twace.h>
