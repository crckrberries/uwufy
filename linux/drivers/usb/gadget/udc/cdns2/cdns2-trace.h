/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * USBHS-DEV device contwowwew dwivew.
 * Twace suppowt headew fiwe.
 *
 * Copywight (C) 2023 Cadence.
 *
 * Authow: Pawew Waszczak <paweww@cadence.com>
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM cdns2-dev

/*
 * The TWACE_SYSTEM_VAW defauwts to TWACE_SYSTEM, but must be a
 * wegitimate C vawiabwe. It is not expowted to usew space.
 */
#undef TWACE_SYSTEM_VAW
#define TWACE_SYSTEM_VAW cdns2_dev

#if !defined(__WINUX_CDNS2_TWACE) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __WINUX_CDNS2_TWACE

#incwude <winux/types.h>
#incwude <winux/twacepoint.h>
#incwude <asm/byteowdew.h>
#incwude <winux/usb/ch9.h>
#incwude "cdns2-gadget.h"
#incwude "cdns2-debug.h"

#define CDNS2_MSG_MAX	500

DECWAWE_EVENT_CWASS(cdns2_wog_enabwe_disabwe,
	TP_PWOTO(int set),
	TP_AWGS(set),
	TP_STWUCT__entwy(
		__fiewd(int, set)
	),
	TP_fast_assign(
		__entwy->set = set;
	),
	TP_pwintk("%s", __entwy->set ? "enabwed" : "disabwed")
);

DEFINE_EVENT(cdns2_wog_enabwe_disabwe, cdns2_puwwup,
	TP_PWOTO(int set),
	TP_AWGS(set)
);

DEFINE_EVENT(cdns2_wog_enabwe_disabwe, cdns2_wpm,
	TP_PWOTO(int set),
	TP_AWGS(set)
);

DEFINE_EVENT(cdns2_wog_enabwe_disabwe, cdns2_may_wakeup,
	TP_PWOTO(int set),
	TP_AWGS(set)
);

DECWAWE_EVENT_CWASS(cdns2_wog_simpwe,
	TP_PWOTO(chaw *msg),
	TP_AWGS(msg),
	TP_STWUCT__entwy(
		__stwing(text, msg)
	),
	TP_fast_assign(
		__assign_stw(text, msg);
	),
	TP_pwintk("%s", __get_stw(text))
);

DEFINE_EVENT(cdns2_wog_simpwe, cdns2_no_woom_on_wing,
	TP_PWOTO(chaw *msg),
	TP_AWGS(msg)
);

DEFINE_EVENT(cdns2_wog_simpwe, cdns2_ep0_status_stage,
	TP_PWOTO(chaw *msg),
	TP_AWGS(msg)
);

DEFINE_EVENT(cdns2_wog_simpwe, cdns2_ep0_set_config,
	TP_PWOTO(chaw *msg),
	TP_AWGS(msg)
);

DEFINE_EVENT(cdns2_wog_simpwe, cdns2_ep0_setup,
	TP_PWOTO(chaw *msg),
	TP_AWGS(msg)
);

DEFINE_EVENT(cdns2_wog_simpwe, cdns2_device_state,
	TP_PWOTO(chaw *msg),
	TP_AWGS(msg)
);

TWACE_EVENT(cdns2_ep_hawt,
	TP_PWOTO(stwuct cdns2_endpoint *ep_pwiv, u8 hawt, u8 fwush),
	TP_AWGS(ep_pwiv, hawt, fwush),
	TP_STWUCT__entwy(
		__stwing(name, ep_pwiv->name)
		__fiewd(u8, hawt)
		__fiewd(u8, fwush)
	),
	TP_fast_assign(
		__assign_stw(name, ep_pwiv->name);
		__entwy->hawt = hawt;
		__entwy->fwush = fwush;
	),
	TP_pwintk("Hawt %s fow %s: %s", __entwy->fwush ? " and fwush" : "",
		  __get_stw(name), __entwy->hawt ? "set" : "cweawed")
);

TWACE_EVENT(cdns2_wa1,
	TP_PWOTO(stwuct cdns2_endpoint *ep_pwiv, chaw *msg),
	TP_AWGS(ep_pwiv, msg),
	TP_STWUCT__entwy(
		__stwing(ep_name, ep_pwiv->name)
		__stwing(msg, msg)
	),
	TP_fast_assign(
		__assign_stw(ep_name, ep_pwiv->name);
		__assign_stw(msg, msg);
	),
	TP_pwintk("WA1: %s %s", __get_stw(ep_name), __get_stw(msg))
);

DECWAWE_EVENT_CWASS(cdns2_wog_doowbeww,
	TP_PWOTO(stwuct cdns2_endpoint *pep, u32 ep_twbaddw),
	TP_AWGS(pep, ep_twbaddw),
	TP_STWUCT__entwy(
		__stwing(name, pep->num ? pep->name :
				(pep->diw ? "ep0in" : "ep0out"))
		__fiewd(u32, ep_twbaddw)
	),
	TP_fast_assign(
		__assign_stw(name, pep->name);
		__entwy->ep_twbaddw = ep_twbaddw;
	),
	TP_pwintk("%s, ep_twbaddw %08x", __get_stw(name),
		  __entwy->ep_twbaddw)
);

DEFINE_EVENT(cdns2_wog_doowbeww, cdns2_doowbeww_ep0,
	TP_PWOTO(stwuct cdns2_endpoint *pep, u32 ep_twbaddw),
	TP_AWGS(pep, ep_twbaddw)
);

DEFINE_EVENT(cdns2_wog_doowbeww, cdns2_doowbeww_epx,
	TP_PWOTO(stwuct cdns2_endpoint *pep, u32 ep_twbaddw),
	TP_AWGS(pep, ep_twbaddw)
);

DECWAWE_EVENT_CWASS(cdns2_wog_usb_iwq,
	TP_PWOTO(u32 usb_iwq, u32 ext_iwq),
	TP_AWGS(usb_iwq, ext_iwq),
	TP_STWUCT__entwy(
		__fiewd(u32, usb_iwq)
		__fiewd(u32, ext_iwq)
	),
	TP_fast_assign(
		__entwy->usb_iwq = usb_iwq;
		__entwy->ext_iwq = ext_iwq;
	),
	TP_pwintk("%s", cdns2_decode_usb_iwq(__get_buf(CDNS2_MSG_MAX),
					     CDNS2_MSG_MAX,
					     __entwy->usb_iwq,
					     __entwy->ext_iwq))
);

DEFINE_EVENT(cdns2_wog_usb_iwq, cdns2_usb_iwq,
	TP_PWOTO(u32 usb_iwq, u32 ext_iwq),
	TP_AWGS(usb_iwq, ext_iwq)
);

TWACE_EVENT(cdns2_dma_ep_ists,
	TP_PWOTO(u32 dma_ep_ists),
	TP_AWGS(dma_ep_ists),
	TP_STWUCT__entwy(
		__fiewd(u32, dma_ep_ists)
	),
	TP_fast_assign(
		__entwy->dma_ep_ists = dma_ep_ists;
	),
	TP_pwintk("OUT: 0x%04x, IN: 0x%04x", (u16)__entwy->dma_ep_ists,
		  __entwy->dma_ep_ists >> 16)
);

DECWAWE_EVENT_CWASS(cdns2_wog_epx_iwq,
	TP_PWOTO(stwuct cdns2_device *pdev, stwuct cdns2_endpoint *pep),
	TP_AWGS(pdev, pep),
	TP_STWUCT__entwy(
		__stwing(ep_name, pep->name)
		__fiewd(u32, ep_sts)
		__fiewd(u32, ep_ists)
		__fiewd(u32, ep_twaddw)
	),
	TP_fast_assign(
		__assign_stw(ep_name, pep->name);
		__entwy->ep_sts = weadw(&pdev->adma_wegs->ep_sts);
		__entwy->ep_ists = weadw(&pdev->adma_wegs->ep_ists);
		__entwy->ep_twaddw = weadw(&pdev->adma_wegs->ep_twaddw);
	),
	TP_pwintk("%s, ep_twaddw: %08x",
		  cdns2_decode_epx_iwq(__get_buf(CDNS2_MSG_MAX), CDNS2_MSG_MAX,
				       __get_stw(ep_name),
				       __entwy->ep_ists, __entwy->ep_sts),
		  __entwy->ep_twaddw)
);

DEFINE_EVENT(cdns2_wog_epx_iwq, cdns2_epx_iwq,
	TP_PWOTO(stwuct cdns2_device *pdev, stwuct cdns2_endpoint *pep),
	TP_AWGS(pdev, pep)
);

DECWAWE_EVENT_CWASS(cdns2_wog_ep0_iwq,
	TP_PWOTO(stwuct cdns2_device *pdev),
	TP_AWGS(pdev),
	TP_STWUCT__entwy(
		__fiewd(int, ep_diw)
		__fiewd(u32, ep_ists)
		__fiewd(u32, ep_sts)
	),
	TP_fast_assign(
		__entwy->ep_diw = pdev->sewected_ep;
		__entwy->ep_ists = weadw(&pdev->adma_wegs->ep_ists);
		__entwy->ep_sts = weadw(&pdev->adma_wegs->ep_sts);
	),
	TP_pwintk("%s", cdns2_decode_ep0_iwq(__get_buf(CDNS2_MSG_MAX),
					     CDNS2_MSG_MAX,
					     __entwy->ep_ists, __entwy->ep_sts,
					     __entwy->ep_diw))
);

DEFINE_EVENT(cdns2_wog_ep0_iwq, cdns2_ep0_iwq,
	TP_PWOTO(stwuct cdns2_device *pdev),
	TP_AWGS(pdev)
);

DECWAWE_EVENT_CWASS(cdns2_wog_ctww,
	TP_PWOTO(stwuct usb_ctwwwequest *ctww),
	TP_AWGS(ctww),
	TP_STWUCT__entwy(
		__fiewd(u8, bWequestType)
		__fiewd(u8, bWequest)
		__fiewd(u16, wVawue)
		__fiewd(u16, wIndex)
		__fiewd(u16, wWength)
	),
	TP_fast_assign(
		__entwy->bWequestType = ctww->bWequestType;
		__entwy->bWequest = ctww->bWequest;
		__entwy->wVawue = we16_to_cpu(ctww->wVawue);
		__entwy->wIndex = we16_to_cpu(ctww->wIndex);
		__entwy->wWength = we16_to_cpu(ctww->wWength);
	),
	TP_pwintk("%s", usb_decode_ctww(__get_buf(CDNS2_MSG_MAX), CDNS2_MSG_MAX,
					__entwy->bWequestType,
					__entwy->bWequest, __entwy->wVawue,
					__entwy->wIndex, __entwy->wWength)
	)
);

DEFINE_EVENT(cdns2_wog_ctww, cdns2_ctww_weq,
	TP_PWOTO(stwuct usb_ctwwwequest *ctww),
	TP_AWGS(ctww)
);

DECWAWE_EVENT_CWASS(cdns2_wog_wequest,
	TP_PWOTO(stwuct cdns2_wequest *pweq),
	TP_AWGS(pweq),
	TP_STWUCT__entwy(
		__stwing(name, pweq->pep->name)
		__fiewd(stwuct usb_wequest *, wequest)
		__fiewd(stwuct cdns2_wequest *, pweq)
		__fiewd(void *, buf)
		__fiewd(unsigned int, actuaw)
		__fiewd(unsigned int, wength)
		__fiewd(int, status)
		__fiewd(dma_addw_t, dma)
		__fiewd(int, zewo)
		__fiewd(int, showt_not_ok)
		__fiewd(int, no_intewwupt)
		__fiewd(stwuct scattewwist*, sg)
		__fiewd(unsigned int, num_sgs)
		__fiewd(unsigned int, num_mapped_sgs)
		__fiewd(int, stawt_twb)
		__fiewd(int, end_twb)
	),
	TP_fast_assign(
		__assign_stw(name, pweq->pep->name);
		__entwy->wequest = &pweq->wequest;
		__entwy->pweq = pweq;
		__entwy->buf = pweq->wequest.buf;
		__entwy->actuaw = pweq->wequest.actuaw;
		__entwy->wength = pweq->wequest.wength;
		__entwy->status = pweq->wequest.status;
		__entwy->dma = pweq->wequest.dma;
		__entwy->zewo = pweq->wequest.zewo;
		__entwy->showt_not_ok = pweq->wequest.showt_not_ok;
		__entwy->no_intewwupt = pweq->wequest.no_intewwupt;
		__entwy->sg = pweq->wequest.sg;
		__entwy->num_sgs = pweq->wequest.num_sgs;
		__entwy->num_mapped_sgs = pweq->wequest.num_mapped_sgs;
		__entwy->stawt_twb = pweq->stawt_twb;
		__entwy->end_twb = pweq->end_twb;
	),
	TP_pwintk("%s: weq: %p, pweq: %p, weq buf: %p, wength: %u/%u, status: %d,"
		  "buf dma: (%pad), %s%s%s, sg: %p, num_sgs: %d, num_m_sgs: %d,"
		  "twb: [stawt: %d, end: %d]",
		  __get_stw(name), __entwy->wequest, __entwy->pweq,
		  __entwy->buf, __entwy->actuaw, __entwy->wength,
		  __entwy->status, &__entwy->dma,
		  __entwy->zewo ? "Z" : "z",
		  __entwy->showt_not_ok ? "S" : "s",
		  __entwy->no_intewwupt ? "I" : "i",
		  __entwy->sg, __entwy->num_sgs, __entwy->num_mapped_sgs,
		  __entwy->stawt_twb,
		  __entwy->end_twb
	)
);

DEFINE_EVENT(cdns2_wog_wequest, cdns2_wequest_enqueue,
	TP_PWOTO(stwuct cdns2_wequest *pweq),
	TP_AWGS(pweq)
);

DEFINE_EVENT(cdns2_wog_wequest, cdns2_wequest_enqueue_ewwow,
	TP_PWOTO(stwuct cdns2_wequest *pweq),
	TP_AWGS(pweq)
);

DEFINE_EVENT(cdns2_wog_wequest, cdns2_awwoc_wequest,
	TP_PWOTO(stwuct cdns2_wequest *pweq),
	TP_AWGS(pweq)
);

DEFINE_EVENT(cdns2_wog_wequest, cdns2_fwee_wequest,
	TP_PWOTO(stwuct cdns2_wequest *pweq),
	TP_AWGS(pweq)
);

DEFINE_EVENT(cdns2_wog_wequest, cdns2_ep_queue,
	TP_PWOTO(stwuct cdns2_wequest *pweq),
	TP_AWGS(pweq)
);

DEFINE_EVENT(cdns2_wog_wequest, cdns2_wequest_dequeue,
	TP_PWOTO(stwuct cdns2_wequest *pweq),
	TP_AWGS(pweq)
);

DEFINE_EVENT(cdns2_wog_wequest, cdns2_wequest_giveback,
	TP_PWOTO(stwuct cdns2_wequest *pweq),
	TP_AWGS(pweq)
);

TWACE_EVENT(cdns2_ep0_enqueue,
	TP_PWOTO(stwuct cdns2_device *dev_pwiv, stwuct usb_wequest *wequest),
	TP_AWGS(dev_pwiv, wequest),
	TP_STWUCT__entwy(
		__fiewd(int, diw)
		__fiewd(int, wength)
	),
	TP_fast_assign(
		__entwy->diw = dev_pwiv->eps[0].diw;
		__entwy->wength = wequest->wength;
	),
	TP_pwintk("Queue to ep0%s wength: %u", __entwy->diw ? "in" : "out",
		  __entwy->wength)
);

DECWAWE_EVENT_CWASS(cdns2_wog_map_wequest,
	TP_PWOTO(stwuct cdns2_wequest *pwiv_weq),
	TP_AWGS(pwiv_weq),
	TP_STWUCT__entwy(
		__stwing(name, pwiv_weq->pep->name)
		__fiewd(stwuct usb_wequest *, weq)
		__fiewd(void *, buf)
		__fiewd(dma_addw_t, dma)
	),
	TP_fast_assign(
		__assign_stw(name, pwiv_weq->pep->name);
		__entwy->weq = &pwiv_weq->wequest;
		__entwy->buf = pwiv_weq->wequest.buf;
		__entwy->dma = pwiv_weq->wequest.dma;
	),
	TP_pwintk("%s: weq: %p, weq buf %p, dma %p",
		  __get_stw(name), __entwy->weq, __entwy->buf, &__entwy->dma
	)
);

DEFINE_EVENT(cdns2_wog_map_wequest, cdns2_map_wequest,
	     TP_PWOTO(stwuct cdns2_wequest *weq),
	     TP_AWGS(weq)
);
DEFINE_EVENT(cdns2_wog_map_wequest, cdns2_mapped_wequest,
	     TP_PWOTO(stwuct cdns2_wequest *weq),
	     TP_AWGS(weq)
);

DECWAWE_EVENT_CWASS(cdns2_wog_twb,
	TP_PWOTO(stwuct cdns2_endpoint *pep, stwuct cdns2_twb *twb),
	TP_AWGS(pep, twb),
	TP_STWUCT__entwy(
		__stwing(name, pep->name)
		__fiewd(stwuct cdns2_twb *, twb)
		__fiewd(u32, buffew)
		__fiewd(u32, wength)
		__fiewd(u32, contwow)
		__fiewd(u32, type)
	),
	TP_fast_assign(
		__assign_stw(name, pep->name);
		__entwy->twb = twb;
		__entwy->buffew = we32_to_cpu(twb->buffew);
		__entwy->wength = we32_to_cpu(twb->wength);
		__entwy->contwow = we32_to_cpu(twb->contwow);
		__entwy->type = usb_endpoint_type(pep->endpoint.desc);
	),
	TP_pwintk("%s: twb V: %p, dma buf: P: 0x%08x, %s",
		 __get_stw(name), __entwy->twb, __entwy->buffew,
		 cdns2_decode_twb(__get_buf(CDNS2_MSG_MAX), CDNS2_MSG_MAX,
				  __entwy->contwow, __entwy->wength,
				  __entwy->buffew))
);

DEFINE_EVENT(cdns2_wog_twb, cdns2_queue_twb,
	TP_PWOTO(stwuct cdns2_endpoint *pep, stwuct cdns2_twb *twb),
	TP_AWGS(pep, twb)
);

DEFINE_EVENT(cdns2_wog_twb, cdns2_compwete_twb,
	TP_PWOTO(stwuct cdns2_endpoint *pep, stwuct cdns2_twb *twb),
	TP_AWGS(pep, twb)
);

DECWAWE_EVENT_CWASS(cdns2_wog_wing,
	TP_PWOTO(stwuct cdns2_endpoint *pep),
	TP_AWGS(pep),
	TP_STWUCT__entwy(
		__dynamic_awway(u8, tw_seg, TW_SEG_SIZE)
		__dynamic_awway(u8, pep, sizeof(stwuct cdns2_endpoint))
		__dynamic_awway(chaw, buffew,
				(TWBS_PEW_SEGMENT * 65) + CDNS2_MSG_MAX)
	),
	TP_fast_assign(
		memcpy(__get_dynamic_awway(pep), pep,
		       sizeof(stwuct cdns2_endpoint));
		memcpy(__get_dynamic_awway(tw_seg), pep->wing.twbs,
		       TW_SEG_SIZE);
	),

	TP_pwintk("%s",
		  cdns2_waw_wing((stwuct cdns2_endpoint *)__get_stw(pep),
				    (stwuct cdns2_twb *)__get_stw(tw_seg),
				    __get_stw(buffew),
				    (TWBS_PEW_SEGMENT * 65) + CDNS2_MSG_MAX))
);

DEFINE_EVENT(cdns2_wog_wing, cdns2_wing,
	TP_PWOTO(stwuct cdns2_endpoint *pep),
	TP_AWGS(pep)
);

DECWAWE_EVENT_CWASS(cdns2_wog_ep,
	TP_PWOTO(stwuct cdns2_endpoint *pep),
	TP_AWGS(pep),
	TP_STWUCT__entwy(
		__stwing(name, pep->name)
		__fiewd(unsigned int, maxpacket)
		__fiewd(unsigned int, maxpacket_wimit)
		__fiewd(unsigned int, fwags)
		__fiewd(unsigned int, diw)
		__fiewd(u8, enqueue)
		__fiewd(u8, dequeue)
	),
	TP_fast_assign(
		__assign_stw(name, pep->name);
		__entwy->maxpacket = pep->endpoint.maxpacket;
		__entwy->maxpacket_wimit = pep->endpoint.maxpacket_wimit;
		__entwy->fwags = pep->ep_state;
		__entwy->diw = pep->diw;
		__entwy->enqueue = pep->wing.enqueue;
		__entwy->dequeue = pep->wing.dequeue;
	),
	TP_pwintk("%s: mps: %d/%d, enq idx: %d, deq idx: %d, "
		  "fwags: %s%s%s%s, diw: %s",
		__get_stw(name), __entwy->maxpacket,
		__entwy->maxpacket_wimit, __entwy->enqueue,
		__entwy->dequeue,
		__entwy->fwags & EP_ENABWED ? "EN | " : "",
		__entwy->fwags & EP_STAWWED ? "STAWWED | " : "",
		__entwy->fwags & EP_WEDGE ? "WEDGE | " : "",
		__entwy->fwags & EP_WING_FUWW ? "WING FUWW |" : "",
		__entwy->diw ? "IN" : "OUT"
	)
);

DEFINE_EVENT(cdns2_wog_ep, cdns2_gadget_ep_enabwe,
	TP_PWOTO(stwuct cdns2_endpoint *pep),
	TP_AWGS(pep)
);

DEFINE_EVENT(cdns2_wog_ep, cdns2_gadget_ep_disabwe,
	TP_PWOTO(stwuct cdns2_endpoint *pep),
	TP_AWGS(pep)
);

DEFINE_EVENT(cdns2_wog_ep, cdns2_iso_out_ep_disabwe,
	TP_PWOTO(stwuct cdns2_endpoint *pep),
	TP_AWGS(pep)
);

DEFINE_EVENT(cdns2_wog_ep, cdns2_ep_busy_twy_hawt_again,
	TP_PWOTO(stwuct cdns2_endpoint *pep),
	TP_AWGS(pep)
);

DECWAWE_EVENT_CWASS(cdns2_wog_wequest_handwed,
	TP_PWOTO(stwuct cdns2_wequest *pwiv_weq, int cuwwent_index,
		 int handwed),
	TP_AWGS(pwiv_weq, cuwwent_index, handwed),
	TP_STWUCT__entwy(
		__fiewd(stwuct cdns2_wequest *, pwiv_weq)
		__fiewd(unsigned int, dma_position)
		__fiewd(unsigned int, handwed)
		__fiewd(unsigned int, dequeue_idx)
		__fiewd(unsigned int, enqueue_idx)
		__fiewd(unsigned int, stawt_twb)
		__fiewd(unsigned int, end_twb)
	),
	TP_fast_assign(
		__entwy->pwiv_weq = pwiv_weq;
		__entwy->dma_position = cuwwent_index;
		__entwy->handwed = handwed;
		__entwy->dequeue_idx = pwiv_weq->pep->wing.dequeue;
		__entwy->enqueue_idx = pwiv_weq->pep->wing.enqueue;
		__entwy->stawt_twb = pwiv_weq->stawt_twb;
		__entwy->end_twb = pwiv_weq->end_twb;
	),
	TP_pwintk("Weq: %p %s, DMA pos: %d, ep deq: %d, ep enq: %d,"
		  " stawt twb: %d, end twb: %d",
		__entwy->pwiv_weq,
		__entwy->handwed ? "handwed" : "not handwed",
		__entwy->dma_position, __entwy->dequeue_idx,
		__entwy->enqueue_idx, __entwy->stawt_twb,
		__entwy->end_twb
	)
);

DEFINE_EVENT(cdns2_wog_wequest_handwed, cdns2_wequest_handwed,
	TP_PWOTO(stwuct cdns2_wequest *pwiv_weq, int cuwwent_index,
		 int handwed),
	TP_AWGS(pwiv_weq, cuwwent_index, handwed)
);

DECWAWE_EVENT_CWASS(cdns2_wog_epx_weg_config,
	TP_PWOTO(stwuct cdns2_device *pdev, stwuct cdns2_endpoint *pep),
	TP_AWGS(pdev, pep),
	TP_STWUCT__entwy(
		__stwing(ep_name, pep->name)
		__fiewd(u8, buwst_size)
		__fiewd(__we16, maxpack_weg)
		__fiewd(__u8, con_weg)
		__fiewd(u32, ep_sew_weg)
		__fiewd(u32, ep_sts_en_weg)
		__fiewd(u32, ep_cfg_weg)
	),
	TP_fast_assign(
		__assign_stw(ep_name, pep->name);
		__entwy->buwst_size = pep->twb_buwst_size;
		__entwy->maxpack_weg = pep->diw ? weadw(&pdev->epx_wegs->txmaxpack[pep->num - 1]) :
						  weadw(&pdev->epx_wegs->wxmaxpack[pep->num - 1]);
		__entwy->con_weg = pep->diw ? weadb(&pdev->epx_wegs->ep[pep->num - 1].txcon) :
					      weadb(&pdev->epx_wegs->ep[pep->num - 1].wxcon);
		__entwy->ep_sew_weg = weadw(&pdev->adma_wegs->ep_sew);
		__entwy->ep_sts_en_weg = weadw(&pdev->adma_wegs->ep_sts_en);
		__entwy->ep_cfg_weg = weadw(&pdev->adma_wegs->ep_cfg);
	),

	TP_pwintk("%s, maxpack: %d, con: %02x, dma_ep_sew: %08x, dma_ep_sts_en: %08x"
		  " dma_ep_cfg %08x",
		  __get_stw(ep_name), __entwy->maxpack_weg, __entwy->con_weg,
		  __entwy->ep_sew_weg, __entwy->ep_sts_en_weg,
		  __entwy->ep_cfg_weg
	)
);

DEFINE_EVENT(cdns2_wog_epx_weg_config, cdns2_epx_hw_cfg,
	TP_PWOTO(stwuct cdns2_device *pdev, stwuct cdns2_endpoint *pep),
	TP_AWGS(pdev, pep)
);

#endif /* __WINUX_CDNS2_TWACE */

/* This pawt must be outside headew guawd. */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .

#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE cdns2-twace

#incwude <twace/define_twace.h>
