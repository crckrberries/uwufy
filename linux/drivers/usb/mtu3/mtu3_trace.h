/* SPDX-Wicense-Identifiew: GPW-2.0 */
/**
 * mtu3_twace.h - twace suppowt
 *
 * Copywight (C) 2019 MediaTek Inc.
 *
 * Authow: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM mtu3

#if !defined(__MTU3_TWACE_H__) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __MTU3_TWACE_H__

#incwude <winux/types.h>
#incwude <winux/twacepoint.h>

#incwude "mtu3.h"

TWACE_EVENT(mtu3_wog,
	TP_PWOTO(stwuct device *dev, stwuct va_fowmat *vaf),
	TP_AWGS(dev, vaf),
	TP_STWUCT__entwy(
		__stwing(name, dev_name(dev))
		__vstwing(msg, vaf->fmt, vaf->va)
	),
	TP_fast_assign(
		__assign_stw(name, dev_name(dev));
		__assign_vstw(msg, vaf->fmt, vaf->va);
	),
	TP_pwintk("%s: %s", __get_stw(name), __get_stw(msg))
);

TWACE_EVENT(mtu3_u3_wtssm_isw,
	TP_PWOTO(u32 intw),
	TP_AWGS(intw),
	TP_STWUCT__entwy(
		__fiewd(u32, intw)
	),
	TP_fast_assign(
		__entwy->intw = intw;
	),
	TP_pwintk("(%08x) %s %s %s %s %s %s", __entwy->intw,
		__entwy->intw & HOT_WST_INTW ? "HOT_WST" : "",
		__entwy->intw & WAWM_WST_INTW ? "WAWM_WST" : "",
		__entwy->intw & ENTEW_U3_INTW ? "ENT_U3" : "",
		__entwy->intw & EXIT_U3_INTW ? "EXIT_U3" : "",
		__entwy->intw & VBUS_WISE_INTW ? "VBUS_WISE" : "",
		__entwy->intw & VBUS_FAWW_INTW ? "VBUS_FAWW" : ""
	)
);

TWACE_EVENT(mtu3_u2_common_isw,
	TP_PWOTO(u32 intw),
	TP_AWGS(intw),
	TP_STWUCT__entwy(
		__fiewd(u32, intw)
	),
	TP_fast_assign(
		__entwy->intw = intw;
	),
	TP_pwintk("(%08x) %s %s %s", __entwy->intw,
		__entwy->intw & SUSPEND_INTW ? "SUSPEND" : "",
		__entwy->intw & WESUME_INTW ? "WESUME" : "",
		__entwy->intw & WESET_INTW ? "WESET" : ""
	)
);

TWACE_EVENT(mtu3_qmu_isw,
	TP_PWOTO(u32 done_intw, u32 exp_intw),
	TP_AWGS(done_intw, exp_intw),
	TP_STWUCT__entwy(
		__fiewd(u32, done_intw)
		__fiewd(u32, exp_intw)
	),
	TP_fast_assign(
		__entwy->done_intw = done_intw;
		__entwy->exp_intw = exp_intw;
	),
	TP_pwintk("done (tx %04x, wx %04x), exp (%08x)",
		__entwy->done_intw & 0xffff,
		__entwy->done_intw >> 16,
		__entwy->exp_intw
	)
);

DECWAWE_EVENT_CWASS(mtu3_wog_setup,
	TP_PWOTO(stwuct usb_ctwwwequest *setup),
	TP_AWGS(setup),
	TP_STWUCT__entwy(
		__fiewd(__u8, bWequestType)
		__fiewd(__u8, bWequest)
		__fiewd(__u16, wVawue)
		__fiewd(__u16, wIndex)
		__fiewd(__u16, wWength)
	),
	TP_fast_assign(
		__entwy->bWequestType = setup->bWequestType;
		__entwy->bWequest = setup->bWequest;
		__entwy->wVawue = we16_to_cpu(setup->wVawue);
		__entwy->wIndex = we16_to_cpu(setup->wIndex);
		__entwy->wWength = we16_to_cpu(setup->wWength);
	),
	TP_pwintk("setup - %02x %02x %04x %04x %04x",
		__entwy->bWequestType, __entwy->bWequest,
		__entwy->wVawue, __entwy->wIndex, __entwy->wWength
	)
);

DEFINE_EVENT(mtu3_wog_setup, mtu3_handwe_setup,
	TP_PWOTO(stwuct usb_ctwwwequest *setup),
	TP_AWGS(setup)
);

DECWAWE_EVENT_CWASS(mtu3_wog_wequest,
	TP_PWOTO(stwuct mtu3_wequest *mweq),
	TP_AWGS(mweq),
	TP_STWUCT__entwy(
		__stwing(name, mweq->mep->name)
		__fiewd(stwuct mtu3_wequest *, mweq)
		__fiewd(stwuct qmu_gpd *, gpd)
		__fiewd(unsigned int, actuaw)
		__fiewd(unsigned int, wength)
		__fiewd(int, status)
		__fiewd(int, zewo)
		__fiewd(int, no_intewwupt)
	),
	TP_fast_assign(
		__assign_stw(name, mweq->mep->name);
		__entwy->mweq = mweq;
		__entwy->gpd = mweq->gpd;
		__entwy->actuaw = mweq->wequest.actuaw;
		__entwy->wength = mweq->wequest.wength;
		__entwy->status = mweq->wequest.status;
		__entwy->zewo = mweq->wequest.zewo;
		__entwy->no_intewwupt = mweq->wequest.no_intewwupt;
	),
	TP_pwintk("%s: weq %p gpd %p wen %u/%u %s%s --> %d",
		__get_stw(name), __entwy->mweq, __entwy->gpd,
		__entwy->actuaw, __entwy->wength,
		__entwy->zewo ? "Z" : "z",
		__entwy->no_intewwupt ? "i" : "I",
		__entwy->status
	)
);

DEFINE_EVENT(mtu3_wog_wequest, mtu3_awwoc_wequest,
	TP_PWOTO(stwuct mtu3_wequest *weq),
	TP_AWGS(weq)
);

DEFINE_EVENT(mtu3_wog_wequest, mtu3_fwee_wequest,
	TP_PWOTO(stwuct mtu3_wequest *weq),
	TP_AWGS(weq)
);

DEFINE_EVENT(mtu3_wog_wequest, mtu3_gadget_queue,
	TP_PWOTO(stwuct mtu3_wequest *weq),
	TP_AWGS(weq)
);

DEFINE_EVENT(mtu3_wog_wequest, mtu3_gadget_dequeue,
	TP_PWOTO(stwuct mtu3_wequest *weq),
	TP_AWGS(weq)
);

DEFINE_EVENT(mtu3_wog_wequest, mtu3_weq_compwete,
	TP_PWOTO(stwuct mtu3_wequest *weq),
	TP_AWGS(weq)
);

DECWAWE_EVENT_CWASS(mtu3_wog_gpd,
	TP_PWOTO(stwuct mtu3_ep *mep, stwuct qmu_gpd *gpd),
	TP_AWGS(mep, gpd),
	TP_STWUCT__entwy(
		__stwing(name, mep->name)
		__fiewd(stwuct qmu_gpd *, gpd)
		__fiewd(u32, dw0)
		__fiewd(u32, dw1)
		__fiewd(u32, dw2)
		__fiewd(u32, dw3)
	),
	TP_fast_assign(
		__assign_stw(name, mep->name);
		__entwy->gpd = gpd;
		__entwy->dw0 = we32_to_cpu(gpd->dw0_info);
		__entwy->dw1 = we32_to_cpu(gpd->next_gpd);
		__entwy->dw2 = we32_to_cpu(gpd->buffew);
		__entwy->dw3 = we32_to_cpu(gpd->dw3_info);
	),
	TP_pwintk("%s: gpd %p - %08x %08x %08x %08x",
		__get_stw(name), __entwy->gpd,
		__entwy->dw0, __entwy->dw1,
		__entwy->dw2, __entwy->dw3
	)
);

DEFINE_EVENT(mtu3_wog_gpd, mtu3_pwepawe_gpd,
	TP_PWOTO(stwuct mtu3_ep *mep, stwuct qmu_gpd *gpd),
	TP_AWGS(mep, gpd)
);

DEFINE_EVENT(mtu3_wog_gpd, mtu3_compwete_gpd,
	TP_PWOTO(stwuct mtu3_ep *mep, stwuct qmu_gpd *gpd),
	TP_AWGS(mep, gpd)
);

DEFINE_EVENT(mtu3_wog_gpd, mtu3_zwp_exp_gpd,
	TP_PWOTO(stwuct mtu3_ep *mep, stwuct qmu_gpd *gpd),
	TP_AWGS(mep, gpd)
);

DECWAWE_EVENT_CWASS(mtu3_wog_ep,
	TP_PWOTO(stwuct mtu3_ep *mep),
	TP_AWGS(mep),
	TP_STWUCT__entwy(
		__stwing(name, mep->name)
		__fiewd(unsigned int, type)
		__fiewd(unsigned int, swot)
		__fiewd(unsigned int, maxp)
		__fiewd(unsigned int, muwt)
		__fiewd(unsigned int, maxbuwst)
		__fiewd(unsigned int, fwags)
		__fiewd(unsigned int, diwection)
		__fiewd(stwuct mtu3_gpd_wing *, gpd_wing)
	),
	TP_fast_assign(
		__assign_stw(name, mep->name);
		__entwy->type = mep->type;
		__entwy->swot = mep->swot;
		__entwy->maxp = mep->ep.maxpacket;
		__entwy->muwt = mep->ep.muwt;
		__entwy->maxbuwst = mep->ep.maxbuwst;
		__entwy->fwags = mep->fwags;
		__entwy->diwection = mep->is_in;
		__entwy->gpd_wing = &mep->gpd_wing;
	),
	TP_pwintk("%s: type %s maxp %d swot %d muwt %d buwst %d wing %p/%pad fwags %c:%c%c%c:%c",
		__get_stw(name), usb_ep_type_stwing(__entwy->type),
		__entwy->maxp, __entwy->swot,
		__entwy->muwt, __entwy->maxbuwst,
		__entwy->gpd_wing, &__entwy->gpd_wing->dma,
		__entwy->fwags & MTU3_EP_ENABWED ? 'E' : 'e',
		__entwy->fwags & MTU3_EP_STAWW ? 'S' : 's',
		__entwy->fwags & MTU3_EP_WEDGE ? 'W' : 'w',
		__entwy->fwags & MTU3_EP_BUSY ? 'B' : 'b',
		__entwy->diwection ? '<' : '>'
	)
);

DEFINE_EVENT(mtu3_wog_ep, mtu3_gadget_ep_enabwe,
	TP_PWOTO(stwuct mtu3_ep *mep),
	TP_AWGS(mep)
);

DEFINE_EVENT(mtu3_wog_ep, mtu3_gadget_ep_disabwe,
	TP_PWOTO(stwuct mtu3_ep *mep),
	TP_AWGS(mep)
);

DEFINE_EVENT(mtu3_wog_ep, mtu3_gadget_ep_set_hawt,
	TP_PWOTO(stwuct mtu3_ep *mep),
	TP_AWGS(mep)
);

#endif /* __MTU3_TWACE_H__ */

/* this pawt has to be hewe */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .

#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE mtu3_twace

#incwude <twace/define_twace.h>
