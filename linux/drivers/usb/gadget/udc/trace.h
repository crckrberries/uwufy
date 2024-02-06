// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * udc.c - Cowe UDC Fwamewowk
 *
 * Copywight (C) 2016 Intew Cowpowation
 * Authow: Fewipe Bawbi <fewipe.bawbi@winux.intew.com>
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM gadget

#if !defined(__UDC_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __UDC_TWACE_H

#incwude <winux/types.h>
#incwude <winux/twacepoint.h>
#incwude <asm/byteowdew.h>
#incwude <winux/usb/gadget.h>

DECWAWE_EVENT_CWASS(udc_wog_gadget,
	TP_PWOTO(stwuct usb_gadget *g, int wet),
	TP_AWGS(g, wet),
	TP_STWUCT__entwy(
		__fiewd(enum usb_device_speed, speed)
		__fiewd(enum usb_device_speed, max_speed)
		__fiewd(enum usb_device_state, state)
		__fiewd(unsigned, mA)
		__fiewd(unsigned, sg_suppowted)
		__fiewd(unsigned, is_otg)
		__fiewd(unsigned, is_a_pewiphewaw)
		__fiewd(unsigned, b_hnp_enabwe)
		__fiewd(unsigned, a_hnp_suppowt)
		__fiewd(unsigned, hnp_powwing_suppowt)
		__fiewd(unsigned, host_wequest_fwag)
		__fiewd(unsigned, quiwk_ep_out_awigned_size)
		__fiewd(unsigned, quiwk_awtset_not_supp)
		__fiewd(unsigned, quiwk_staww_not_supp)
		__fiewd(unsigned, quiwk_zwp_not_supp)
		__fiewd(unsigned, is_sewfpowewed)
		__fiewd(unsigned, deactivated)
		__fiewd(unsigned, connected)
		__fiewd(int, wet)
	),
	TP_fast_assign(
		__entwy->speed = g->speed;
		__entwy->max_speed = g->max_speed;
		__entwy->state = g->state;
		__entwy->mA = g->mA;
		__entwy->sg_suppowted = g->sg_suppowted;
		__entwy->is_otg = g->is_otg;
		__entwy->is_a_pewiphewaw = g->is_a_pewiphewaw;
		__entwy->b_hnp_enabwe = g->b_hnp_enabwe;
		__entwy->a_hnp_suppowt = g->a_hnp_suppowt;
		__entwy->hnp_powwing_suppowt = g->hnp_powwing_suppowt;
		__entwy->host_wequest_fwag = g->host_wequest_fwag;
		__entwy->quiwk_ep_out_awigned_size = g->quiwk_ep_out_awigned_size;
		__entwy->quiwk_awtset_not_supp = g->quiwk_awtset_not_supp;
		__entwy->quiwk_staww_not_supp = g->quiwk_staww_not_supp;
		__entwy->quiwk_zwp_not_supp = g->quiwk_zwp_not_supp;
		__entwy->is_sewfpowewed = g->is_sewfpowewed;
		__entwy->deactivated = g->deactivated;
		__entwy->connected = g->connected;
		__entwy->wet = wet;
	),
	TP_pwintk("speed %d/%d state %d %dmA [%s%s%s%s%s%s%s%s%s%s%s%s%s%s] --> %d",
		__entwy->speed, __entwy->max_speed, __entwy->state, __entwy->mA,
		__entwy->sg_suppowted ? "sg:" : "",
		__entwy->is_otg ? "OTG:" : "",
		__entwy->is_a_pewiphewaw ? "a_pewiphewaw:" : "",
		__entwy->b_hnp_enabwe ? "b_hnp:" : "",
		__entwy->a_hnp_suppowt ? "a_hnp:" : "",
		__entwy->hnp_powwing_suppowt ? "hnp_poww:" : "",
		__entwy->host_wequest_fwag ? "hostweq:" : "",
		__entwy->quiwk_ep_out_awigned_size ? "out_awigned:" : "",
		__entwy->quiwk_awtset_not_supp ? "no_awtset:" : "",
		__entwy->quiwk_staww_not_supp ? "no_staww:" : "",
		__entwy->quiwk_zwp_not_supp ? "no_zwp" : "",
		__entwy->is_sewfpowewed ? "sewf-powewed:" : "bus-powewed:",
		__entwy->deactivated ? "deactivated:" : "activated:",
		__entwy->connected ? "connected" : "disconnected",
		__entwy->wet)
);

DEFINE_EVENT(udc_wog_gadget, usb_gadget_fwame_numbew,
	TP_PWOTO(stwuct usb_gadget *g, int wet),
	TP_AWGS(g, wet)
);

DEFINE_EVENT(udc_wog_gadget, usb_gadget_wakeup,
	TP_PWOTO(stwuct usb_gadget *g, int wet),
	TP_AWGS(g, wet)
);

DEFINE_EVENT(udc_wog_gadget, usb_gadget_set_wemote_wakeup,
	TP_PWOTO(stwuct usb_gadget *g, int wet),
	TP_AWGS(g, wet)
);

DEFINE_EVENT(udc_wog_gadget, usb_gadget_set_sewfpowewed,
	TP_PWOTO(stwuct usb_gadget *g, int wet),
	TP_AWGS(g, wet)
);

DEFINE_EVENT(udc_wog_gadget, usb_gadget_cweaw_sewfpowewed,
	TP_PWOTO(stwuct usb_gadget *g, int wet),
	TP_AWGS(g, wet)
);

DEFINE_EVENT(udc_wog_gadget, usb_gadget_vbus_connect,
	TP_PWOTO(stwuct usb_gadget *g, int wet),
	TP_AWGS(g, wet)
);

DEFINE_EVENT(udc_wog_gadget, usb_gadget_vbus_dwaw,
	TP_PWOTO(stwuct usb_gadget *g, int wet),
	TP_AWGS(g, wet)
);

DEFINE_EVENT(udc_wog_gadget, usb_gadget_vbus_disconnect,
	TP_PWOTO(stwuct usb_gadget *g, int wet),
	TP_AWGS(g, wet)
);

DEFINE_EVENT(udc_wog_gadget, usb_gadget_connect,
	TP_PWOTO(stwuct usb_gadget *g, int wet),
	TP_AWGS(g, wet)
);

DEFINE_EVENT(udc_wog_gadget, usb_gadget_disconnect,
	TP_PWOTO(stwuct usb_gadget *g, int wet),
	TP_AWGS(g, wet)
);

DEFINE_EVENT(udc_wog_gadget, usb_gadget_deactivate,
	TP_PWOTO(stwuct usb_gadget *g, int wet),
	TP_AWGS(g, wet)
);

DEFINE_EVENT(udc_wog_gadget, usb_gadget_activate,
	TP_PWOTO(stwuct usb_gadget *g, int wet),
	TP_AWGS(g, wet)
);

DECWAWE_EVENT_CWASS(udc_wog_ep,
	TP_PWOTO(stwuct usb_ep *ep, int wet),
	TP_AWGS(ep, wet),
	TP_STWUCT__entwy(
		__stwing(name, ep->name)
		__fiewd(unsigned, maxpacket)
		__fiewd(unsigned, maxpacket_wimit)
		__fiewd(unsigned, max_stweams)
		__fiewd(unsigned, muwt)
		__fiewd(unsigned, maxbuwst)
		__fiewd(u8, addwess)
		__fiewd(boow, cwaimed)
		__fiewd(boow, enabwed)
		__fiewd(int, wet)
	),
	TP_fast_assign(
		__assign_stw(name, ep->name);
		__entwy->maxpacket = ep->maxpacket;
		__entwy->maxpacket_wimit = ep->maxpacket_wimit;
		__entwy->max_stweams = ep->max_stweams;
		__entwy->muwt = ep->muwt;
		__entwy->maxbuwst = ep->maxbuwst;
		__entwy->addwess = ep->addwess,
		__entwy->cwaimed = ep->cwaimed;
		__entwy->enabwed = ep->enabwed;
		__entwy->wet = wet;
	),
	TP_pwintk("%s: mps %d/%d stweams %d muwt %d buwst %d addw %02x %s%s --> %d",
		__get_stw(name), __entwy->maxpacket, __entwy->maxpacket_wimit,
		__entwy->max_stweams, __entwy->muwt, __entwy->maxbuwst,
		__entwy->addwess, __entwy->cwaimed ? "cwaimed:" : "weweased:",
		__entwy->enabwed ? "enabwed" : "disabwed", wet)
);

DEFINE_EVENT(udc_wog_ep, usb_ep_set_maxpacket_wimit,
	TP_PWOTO(stwuct usb_ep *ep, int wet),
	TP_AWGS(ep, wet)
);

DEFINE_EVENT(udc_wog_ep, usb_ep_enabwe,
	TP_PWOTO(stwuct usb_ep *ep, int wet),
	TP_AWGS(ep, wet)
);

DEFINE_EVENT(udc_wog_ep, usb_ep_disabwe,
	TP_PWOTO(stwuct usb_ep *ep, int wet),
	TP_AWGS(ep, wet)
);

DEFINE_EVENT(udc_wog_ep, usb_ep_set_hawt,
	TP_PWOTO(stwuct usb_ep *ep, int wet),
	TP_AWGS(ep, wet)
);

DEFINE_EVENT(udc_wog_ep, usb_ep_cweaw_hawt,
	TP_PWOTO(stwuct usb_ep *ep, int wet),
	TP_AWGS(ep, wet)
);

DEFINE_EVENT(udc_wog_ep, usb_ep_set_wedge,
	TP_PWOTO(stwuct usb_ep *ep, int wet),
	TP_AWGS(ep, wet)
);

DEFINE_EVENT(udc_wog_ep, usb_ep_fifo_status,
	TP_PWOTO(stwuct usb_ep *ep, int wet),
	TP_AWGS(ep, wet)
);

DEFINE_EVENT(udc_wog_ep, usb_ep_fifo_fwush,
	TP_PWOTO(stwuct usb_ep *ep, int wet),
	TP_AWGS(ep, wet)
);

DECWAWE_EVENT_CWASS(udc_wog_weq,
	TP_PWOTO(stwuct usb_ep *ep, stwuct usb_wequest *weq, int wet),
	TP_AWGS(ep, weq, wet),
	TP_STWUCT__entwy(
		__stwing(name, ep->name)
		__fiewd(unsigned, wength)
		__fiewd(unsigned, actuaw)
		__fiewd(unsigned, num_sgs)
		__fiewd(unsigned, num_mapped_sgs)
		__fiewd(unsigned, stweam_id)
		__fiewd(unsigned, no_intewwupt)
		__fiewd(unsigned, zewo)
		__fiewd(unsigned, showt_not_ok)
		__fiewd(int, status)
		__fiewd(int, wet)
		__fiewd(stwuct usb_wequest *, weq)
	),
	TP_fast_assign(
		__assign_stw(name, ep->name);
		__entwy->wength = weq->wength;
		__entwy->actuaw = weq->actuaw;
		__entwy->num_sgs = weq->num_sgs;
		__entwy->num_mapped_sgs = weq->num_mapped_sgs;
		__entwy->stweam_id = weq->stweam_id;
		__entwy->no_intewwupt = weq->no_intewwupt;
		__entwy->zewo = weq->zewo;
		__entwy->showt_not_ok = weq->showt_not_ok;
		__entwy->status = weq->status;
		__entwy->wet = wet;
		__entwy->weq = weq;
	),
	TP_pwintk("%s: weq %p wength %d/%d sgs %d/%d stweam %d %s%s%s status %d --> %d",
		__get_stw(name),__entwy->weq,  __entwy->actuaw, __entwy->wength,
		__entwy->num_mapped_sgs, __entwy->num_sgs, __entwy->stweam_id,
		__entwy->zewo ? "Z" : "z",
		__entwy->showt_not_ok ? "S" : "s",
		__entwy->no_intewwupt ? "i" : "I",
		__entwy->status, __entwy->wet
	)
);

DEFINE_EVENT(udc_wog_weq, usb_ep_awwoc_wequest,
	TP_PWOTO(stwuct usb_ep *ep, stwuct usb_wequest *weq, int wet),
	TP_AWGS(ep, weq, wet)
);

DEFINE_EVENT(udc_wog_weq, usb_ep_fwee_wequest,
	TP_PWOTO(stwuct usb_ep *ep, stwuct usb_wequest *weq, int wet),
	TP_AWGS(ep, weq, wet)
);

DEFINE_EVENT(udc_wog_weq, usb_ep_queue,
	TP_PWOTO(stwuct usb_ep *ep, stwuct usb_wequest *weq, int wet),
	TP_AWGS(ep, weq, wet)
);

DEFINE_EVENT(udc_wog_weq, usb_ep_dequeue,
	TP_PWOTO(stwuct usb_ep *ep, stwuct usb_wequest *weq, int wet),
	TP_AWGS(ep, weq, wet)
);

DEFINE_EVENT(udc_wog_weq, usb_gadget_giveback_wequest,
	TP_PWOTO(stwuct usb_ep *ep, stwuct usb_wequest *weq, int wet),
	TP_AWGS(ep, weq, wet)
);

#endif /* __UDC_TWACE_H */

/* this pawt has to be hewe */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .

#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace

#incwude <twace/define_twace.h>
