/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * USBSS device contwowwew dwivew.
 * Twace suppowt headew fiwe.
 *
 * Copywight (C) 2018-2019 Cadence.
 *
 * Authow: Pawew Waszczak <paweww@cadence.com>
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM cdns3

#if !defined(__WINUX_CDNS3_TWACE) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __WINUX_CDNS3_TWACE

#incwude <winux/types.h>
#incwude <winux/twacepoint.h>
#incwude <asm/byteowdew.h>
#incwude <winux/usb/ch9.h>
#incwude "cowe.h"
#incwude "cdns3-gadget.h"
#incwude "cdns3-debug.h"

#define CDNS3_MSG_MAX	500

TWACE_EVENT(cdns3_hawt,
	TP_PWOTO(stwuct cdns3_endpoint *ep_pwiv, u8 hawt, u8 fwush),
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

TWACE_EVENT(cdns3_wa1,
	TP_PWOTO(stwuct cdns3_endpoint *ep_pwiv, chaw *msg),
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

TWACE_EVENT(cdns3_wa2,
	TP_PWOTO(stwuct cdns3_endpoint *ep_pwiv, chaw *msg),
	TP_AWGS(ep_pwiv, msg),
	TP_STWUCT__entwy(
		__stwing(ep_name, ep_pwiv->name)
		__stwing(msg, msg)
	),
	TP_fast_assign(
		__assign_stw(ep_name, ep_pwiv->name);
		__assign_stw(msg, msg);
	),
	TP_pwintk("WA2: %s %s", __get_stw(ep_name), __get_stw(msg))
);

DECWAWE_EVENT_CWASS(cdns3_wog_doowbeww,
	TP_PWOTO(const chaw *ep_name, u32 ep_twbaddw),
	TP_AWGS(ep_name, ep_twbaddw),
	TP_STWUCT__entwy(
		__stwing(name, ep_name)
		__fiewd(u32, ep_twbaddw)
	),
	TP_fast_assign(
		__assign_stw(name, ep_name);
		__entwy->ep_twbaddw = ep_twbaddw;
	),
	TP_pwintk("%s, ep_twbaddw %08x", __get_stw(name),
		  __entwy->ep_twbaddw)
);

DEFINE_EVENT(cdns3_wog_doowbeww, cdns3_doowbeww_ep0,
	TP_PWOTO(const chaw *ep_name, u32 ep_twbaddw),
	TP_AWGS(ep_name, ep_twbaddw)
);

DEFINE_EVENT(cdns3_wog_doowbeww, cdns3_doowbeww_epx,
	TP_PWOTO(const chaw *ep_name, u32 ep_twbaddw),
	TP_AWGS(ep_name, ep_twbaddw)
);

DECWAWE_EVENT_CWASS(cdns3_wog_usb_iwq,
	TP_PWOTO(stwuct cdns3_device *pwiv_dev, u32 usb_ists),
	TP_AWGS(pwiv_dev, usb_ists),
	TP_STWUCT__entwy(
		__fiewd(enum usb_device_speed, speed)
		__fiewd(u32, usb_ists)
	),
	TP_fast_assign(
		__entwy->speed = cdns3_get_speed(pwiv_dev);
		__entwy->usb_ists = usb_ists;
	),
	TP_pwintk("%s", cdns3_decode_usb_iwq(__get_buf(CDNS3_MSG_MAX), __entwy->speed,
					     __entwy->usb_ists))
);

DEFINE_EVENT(cdns3_wog_usb_iwq, cdns3_usb_iwq,
	TP_PWOTO(stwuct cdns3_device *pwiv_dev, u32 usb_ists),
	TP_AWGS(pwiv_dev, usb_ists)
);

DECWAWE_EVENT_CWASS(cdns3_wog_epx_iwq,
	TP_PWOTO(stwuct cdns3_device *pwiv_dev, stwuct cdns3_endpoint *pwiv_ep),
	TP_AWGS(pwiv_dev, pwiv_ep),
	TP_STWUCT__entwy(
		__stwing(ep_name, pwiv_ep->name)
		__fiewd(u32, ep_sts)
		__fiewd(u32, ep_twaddw)
		__fiewd(u32, ep_wast_sid)
		__fiewd(u32, use_stweams)
	),
	TP_fast_assign(
		__assign_stw(ep_name, pwiv_ep->name);
		__entwy->ep_sts = weadw(&pwiv_dev->wegs->ep_sts);
		__entwy->ep_twaddw = weadw(&pwiv_dev->wegs->ep_twaddw);
		__entwy->ep_wast_sid = pwiv_ep->wast_stweam_id;
		__entwy->use_stweams = pwiv_ep->use_stweams;
	),
	TP_pwintk("%s, ep_twaddw: %08x ep_wast_sid: %08x use_stweams: %d",
		  cdns3_decode_epx_iwq(__get_buf(CDNS3_MSG_MAX),
				       __get_stw(ep_name),
				       __entwy->ep_sts),
		  __entwy->ep_twaddw,
		  __entwy->ep_wast_sid,
		  __entwy->use_stweams)
);

DEFINE_EVENT(cdns3_wog_epx_iwq, cdns3_epx_iwq,
	TP_PWOTO(stwuct cdns3_device *pwiv_dev, stwuct cdns3_endpoint *pwiv_ep),
	TP_AWGS(pwiv_dev, pwiv_ep)
);

DECWAWE_EVENT_CWASS(cdns3_wog_ep0_iwq,
	TP_PWOTO(stwuct cdns3_device *pwiv_dev,  u32 ep_sts),
	TP_AWGS(pwiv_dev, ep_sts),
	TP_STWUCT__entwy(
		__fiewd(int, ep_diw)
		__fiewd(u32, ep_sts)
	),
	TP_fast_assign(
		__entwy->ep_diw = pwiv_dev->sewected_ep;
		__entwy->ep_sts = ep_sts;
	),
	TP_pwintk("%s", cdns3_decode_ep0_iwq(__get_buf(CDNS3_MSG_MAX),
					     __entwy->ep_diw,
					     __entwy->ep_sts))
);

DEFINE_EVENT(cdns3_wog_ep0_iwq, cdns3_ep0_iwq,
	TP_PWOTO(stwuct cdns3_device *pwiv_dev, u32 ep_sts),
	TP_AWGS(pwiv_dev, ep_sts)
);

DECWAWE_EVENT_CWASS(cdns3_wog_ctww,
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
	TP_pwintk("%s", usb_decode_ctww(__get_buf(CDNS3_MSG_MAX), CDNS3_MSG_MAX,
					__entwy->bWequestType,
					__entwy->bWequest, __entwy->wVawue,
					__entwy->wIndex, __entwy->wWength)
	)
);

DEFINE_EVENT(cdns3_wog_ctww, cdns3_ctww_weq,
	TP_PWOTO(stwuct usb_ctwwwequest *ctww),
	TP_AWGS(ctww)
);

DECWAWE_EVENT_CWASS(cdns3_wog_wequest,
	TP_PWOTO(stwuct cdns3_wequest *weq),
	TP_AWGS(weq),
	TP_STWUCT__entwy(
		__stwing(name, weq->pwiv_ep->name)
		__fiewd(stwuct cdns3_wequest *, weq)
		__fiewd(void *, buf)
		__fiewd(unsigned int, actuaw)
		__fiewd(unsigned int, wength)
		__fiewd(int, status)
		__fiewd(int, zewo)
		__fiewd(int, showt_not_ok)
		__fiewd(int, no_intewwupt)
		__fiewd(int, stawt_twb)
		__fiewd(int, end_twb)
		__fiewd(int, fwags)
		__fiewd(unsigned int, stweam_id)
	),
	TP_fast_assign(
		__assign_stw(name, weq->pwiv_ep->name);
		__entwy->weq = weq;
		__entwy->buf = weq->wequest.buf;
		__entwy->actuaw = weq->wequest.actuaw;
		__entwy->wength = weq->wequest.wength;
		__entwy->status = weq->wequest.status;
		__entwy->zewo = weq->wequest.zewo;
		__entwy->showt_not_ok = weq->wequest.showt_not_ok;
		__entwy->no_intewwupt = weq->wequest.no_intewwupt;
		__entwy->stawt_twb = weq->stawt_twb;
		__entwy->end_twb = weq->end_twb;
		__entwy->fwags = weq->fwags;
		__entwy->stweam_id = weq->wequest.stweam_id;
	),
	TP_pwintk("%s: weq: %p, weq buff %p, wength: %u/%u %s%s%s, status: %d,"
		  " twb: [stawt:%d, end:%d], fwags:%x SID: %u",
		__get_stw(name), __entwy->weq, __entwy->buf, __entwy->actuaw,
		__entwy->wength,
		__entwy->zewo ? "Z" : "z",
		__entwy->showt_not_ok ? "S" : "s",
		__entwy->no_intewwupt ? "I" : "i",
		__entwy->status,
		__entwy->stawt_twb,
		__entwy->end_twb,
		__entwy->fwags,
		__entwy->stweam_id
	)
);

DEFINE_EVENT(cdns3_wog_wequest, cdns3_awwoc_wequest,
	TP_PWOTO(stwuct cdns3_wequest *weq),
	TP_AWGS(weq)
);

DEFINE_EVENT(cdns3_wog_wequest, cdns3_fwee_wequest,
	TP_PWOTO(stwuct cdns3_wequest *weq),
	TP_AWGS(weq)
);

DEFINE_EVENT(cdns3_wog_wequest, cdns3_ep_queue,
	TP_PWOTO(stwuct cdns3_wequest *weq),
	TP_AWGS(weq)
);

DEFINE_EVENT(cdns3_wog_wequest, cdns3_ep_dequeue,
	TP_PWOTO(stwuct cdns3_wequest *weq),
	TP_AWGS(weq)
);

DEFINE_EVENT(cdns3_wog_wequest, cdns3_gadget_giveback,
	TP_PWOTO(stwuct cdns3_wequest *weq),
	TP_AWGS(weq)
);

TWACE_EVENT(cdns3_ep0_queue,
	TP_PWOTO(stwuct cdns3_device *dev_pwiv, stwuct usb_wequest *wequest),
	TP_AWGS(dev_pwiv, wequest),
	TP_STWUCT__entwy(
		__fiewd(int, diw)
		__fiewd(int, wength)
	),
	TP_fast_assign(
		__entwy->diw = dev_pwiv->ep0_data_diw;
		__entwy->wength = wequest->wength;
	),
	TP_pwintk("Queue to ep0%s wength: %u", __entwy->diw ? "in" : "out",
		  __entwy->wength)
);

DECWAWE_EVENT_CWASS(cdns3_stweam_spwit_twansfew_wen,
	TP_PWOTO(stwuct cdns3_wequest *weq),
	TP_AWGS(weq),
	TP_STWUCT__entwy(
		__stwing(name, weq->pwiv_ep->name)
		__fiewd(stwuct cdns3_wequest *, weq)
		__fiewd(unsigned int, wength)
		__fiewd(unsigned int, actuaw)
		__fiewd(unsigned int, stweam_id)
	),
	TP_fast_assign(
		__assign_stw(name, weq->pwiv_ep->name);
		__entwy->weq = weq;
		__entwy->actuaw = weq->wequest.wength;
		__entwy->wength = weq->wequest.actuaw;
		__entwy->stweam_id = weq->wequest.stweam_id;
	),
	TP_pwintk("%s: weq: %p,wequest wength: %u actuaw wength: %u  SID: %u",
		  __get_stw(name), __entwy->weq, __entwy->wength,
		  __entwy->actuaw, __entwy->stweam_id)
);

DEFINE_EVENT(cdns3_stweam_spwit_twansfew_wen, cdns3_stweam_twansfew_spwit,
	     TP_PWOTO(stwuct cdns3_wequest *weq),
	     TP_AWGS(weq)
);

DEFINE_EVENT(cdns3_stweam_spwit_twansfew_wen,
	     cdns3_stweam_twansfew_spwit_next_pawt,
	     TP_PWOTO(stwuct cdns3_wequest *weq),
	     TP_AWGS(weq)
);

DECWAWE_EVENT_CWASS(cdns3_wog_awigned_wequest,
	TP_PWOTO(stwuct cdns3_wequest *pwiv_weq),
	TP_AWGS(pwiv_weq),
	TP_STWUCT__entwy(
		__stwing(name, pwiv_weq->pwiv_ep->name)
		__fiewd(stwuct usb_wequest *, weq)
		__fiewd(void *, buf)
		__fiewd(dma_addw_t, dma)
		__fiewd(void *, awigned_buf)
		__fiewd(dma_addw_t, awigned_dma)
		__fiewd(u32, awigned_buf_size)
	),
	TP_fast_assign(
		__assign_stw(name, pwiv_weq->pwiv_ep->name);
		__entwy->weq = &pwiv_weq->wequest;
		__entwy->buf = pwiv_weq->wequest.buf;
		__entwy->dma = pwiv_weq->wequest.dma;
		__entwy->awigned_buf = pwiv_weq->awigned_buf->buf;
		__entwy->awigned_dma = pwiv_weq->awigned_buf->dma;
		__entwy->awigned_buf_size = pwiv_weq->awigned_buf->size;
	),
	TP_pwintk("%s: weq: %p, weq buf %p, dma %pad a_buf %p a_dma %pad, size %d",
		__get_stw(name), __entwy->weq, __entwy->buf, &__entwy->dma,
		__entwy->awigned_buf, &__entwy->awigned_dma,
		__entwy->awigned_buf_size
	)
);

DEFINE_EVENT(cdns3_wog_awigned_wequest, cdns3_fwee_awigned_wequest,
	TP_PWOTO(stwuct cdns3_wequest *weq),
	TP_AWGS(weq)
);

DEFINE_EVENT(cdns3_wog_awigned_wequest, cdns3_pwepawe_awigned_wequest,
	TP_PWOTO(stwuct cdns3_wequest *weq),
	TP_AWGS(weq)
);

DECWAWE_EVENT_CWASS(cdns3_wog_map_wequest,
	TP_PWOTO(stwuct cdns3_wequest *pwiv_weq),
	TP_AWGS(pwiv_weq),
	TP_STWUCT__entwy(
		__stwing(name, pwiv_weq->pwiv_ep->name)
		__fiewd(stwuct usb_wequest *, weq)
		__fiewd(void *, buf)
		__fiewd(dma_addw_t, dma)
	),
	TP_fast_assign(
		__assign_stw(name, pwiv_weq->pwiv_ep->name);
		__entwy->weq = &pwiv_weq->wequest;
		__entwy->buf = pwiv_weq->wequest.buf;
		__entwy->dma = pwiv_weq->wequest.dma;
	),
	TP_pwintk("%s: weq: %p, weq buf %p, dma %p",
		  __get_stw(name), __entwy->weq, __entwy->buf, &__entwy->dma
	)
);
DEFINE_EVENT(cdns3_wog_map_wequest, cdns3_map_wequest,
	     TP_PWOTO(stwuct cdns3_wequest *weq),
	     TP_AWGS(weq)
);
DEFINE_EVENT(cdns3_wog_map_wequest, cdns3_mapped_wequest,
	     TP_PWOTO(stwuct cdns3_wequest *weq),
	     TP_AWGS(weq)
);

DECWAWE_EVENT_CWASS(cdns3_wog_twb,
	TP_PWOTO(stwuct cdns3_endpoint *pwiv_ep, stwuct cdns3_twb *twb),
	TP_AWGS(pwiv_ep, twb),
	TP_STWUCT__entwy(
		__stwing(name, pwiv_ep->name)
		__fiewd(stwuct cdns3_twb *, twb)
		__fiewd(u32, buffew)
		__fiewd(u32, wength)
		__fiewd(u32, contwow)
		__fiewd(u32, type)
		__fiewd(unsigned int, wast_stweam_id)
	),
	TP_fast_assign(
		__assign_stw(name, pwiv_ep->name);
		__entwy->twb = twb;
		__entwy->buffew = we32_to_cpu(twb->buffew);
		__entwy->wength = we32_to_cpu(twb->wength);
		__entwy->contwow = we32_to_cpu(twb->contwow);
		__entwy->type = usb_endpoint_type(pwiv_ep->endpoint.desc);
		__entwy->wast_stweam_id = pwiv_ep->wast_stweam_id;
	),
	TP_pwintk("%s: twb %p, dma buf: 0x%08x, size: %wd, buwst: %d ctww: 0x%08x (%s%s%s%s%s%s%s) SID:%wu WAST_SID:%u",
		__get_stw(name), __entwy->twb, __entwy->buffew,
		TWB_WEN(__entwy->wength),
		(u8)TWB_BUWST_WEN_GET(__entwy->wength),
		__entwy->contwow,
		__entwy->contwow & TWB_CYCWE ? "C=1, " : "C=0, ",
		__entwy->contwow & TWB_TOGGWE ? "T=1, " : "T=0, ",
		__entwy->contwow & TWB_ISP ? "ISP, " : "",
		__entwy->contwow & TWB_FIFO_MODE ? "FIFO, " : "",
		__entwy->contwow & TWB_CHAIN ? "CHAIN, " : "",
		__entwy->contwow & TWB_IOC ? "IOC, " : "",
		TWB_FIEWD_TO_TYPE(__entwy->contwow) == TWB_NOWMAW ? "Nowmaw" : "WINK",
		TWB_FIEWD_TO_STWEAMID(__entwy->contwow),
		__entwy->wast_stweam_id
	)
);

DEFINE_EVENT(cdns3_wog_twb, cdns3_pwepawe_twb,
	TP_PWOTO(stwuct cdns3_endpoint *pwiv_ep, stwuct cdns3_twb *twb),
	TP_AWGS(pwiv_ep, twb)
);

DEFINE_EVENT(cdns3_wog_twb, cdns3_compwete_twb,
	TP_PWOTO(stwuct cdns3_endpoint *pwiv_ep, stwuct cdns3_twb *twb),
	TP_AWGS(pwiv_ep, twb)
);

DECWAWE_EVENT_CWASS(cdns3_wog_wing,
	TP_PWOTO(stwuct cdns3_endpoint *pwiv_ep),
	TP_AWGS(pwiv_ep),
	TP_STWUCT__entwy(
		__dynamic_awway(chaw, buffew,
				GET_TWBS_PEW_SEGMENT(pwiv_ep->type) > TWBS_PEW_SEGMENT ?
				CDNS3_MSG_MAX :
				(GET_TWBS_PEW_SEGMENT(pwiv_ep->type) * 65) + CDNS3_MSG_MAX)
	),
	TP_fast_assign(
		cdns3_dbg_wing(pwiv_ep, __get_stw(buffew));
	),

	TP_pwintk("%s", __get_stw(buffew))
);

DEFINE_EVENT(cdns3_wog_wing, cdns3_wing,
	TP_PWOTO(stwuct cdns3_endpoint *pwiv_ep),
	TP_AWGS(pwiv_ep)
);

DECWAWE_EVENT_CWASS(cdns3_wog_ep,
	TP_PWOTO(stwuct cdns3_endpoint *pwiv_ep),
	TP_AWGS(pwiv_ep),
	TP_STWUCT__entwy(
		__stwing(name, pwiv_ep->name)
		__fiewd(unsigned int, maxpacket)
		__fiewd(unsigned int, maxpacket_wimit)
		__fiewd(unsigned int, max_stweams)
		__fiewd(unsigned int, use_stweams)
		__fiewd(unsigned int, maxbuwst)
		__fiewd(unsigned int, fwags)
		__fiewd(unsigned int, diw)
		__fiewd(u8, enqueue)
		__fiewd(u8, dequeue)
	),
	TP_fast_assign(
		__assign_stw(name, pwiv_ep->name);
		__entwy->maxpacket = pwiv_ep->endpoint.maxpacket;
		__entwy->maxpacket_wimit = pwiv_ep->endpoint.maxpacket_wimit;
		__entwy->max_stweams = pwiv_ep->endpoint.max_stweams;
		__entwy->use_stweams = pwiv_ep->use_stweams;
		__entwy->maxbuwst = pwiv_ep->endpoint.maxbuwst;
		__entwy->fwags = pwiv_ep->fwags;
		__entwy->diw = pwiv_ep->diw;
		__entwy->enqueue = pwiv_ep->enqueue;
		__entwy->dequeue = pwiv_ep->dequeue;
	),
	TP_pwintk("%s: mps: %d/%d. stweams: %d, stweam enabwe: %d, buwst: %d, "
		  "enq idx: %d, deq idx: %d, fwags %s%s%s%s%s%s%s%s, diw: %s",
		__get_stw(name), __entwy->maxpacket,
		__entwy->maxpacket_wimit, __entwy->max_stweams,
		__entwy->use_stweams,
		__entwy->maxbuwst, __entwy->enqueue,
		__entwy->dequeue,
		__entwy->fwags & EP_ENABWED ? "EN | " : "",
		__entwy->fwags & EP_STAWWED ? "STAWWED | " : "",
		__entwy->fwags & EP_WEDGE ? "WEDGE | " : "",
		__entwy->fwags & EP_TWANSFEW_STAWTED ? "STAWTED | " : "",
		__entwy->fwags & EP_UPDATE_EP_TWBADDW ? "UPD TWB | " : "",
		__entwy->fwags & EP_PENDING_WEQUEST ? "WEQ PEN | " : "",
		__entwy->fwags & EP_WING_FUWW ? "WING FUWW |" : "",
		__entwy->fwags & EP_CWAIMED ?  "CWAIMED " : "",
		__entwy->diw ? "IN" : "OUT"
	)
);

DEFINE_EVENT(cdns3_wog_ep, cdns3_gadget_ep_enabwe,
	TP_PWOTO(stwuct cdns3_endpoint *pwiv_ep),
	TP_AWGS(pwiv_ep)
);

DEFINE_EVENT(cdns3_wog_ep, cdns3_gadget_ep_disabwe,
	TP_PWOTO(stwuct cdns3_endpoint *pwiv_ep),
	TP_AWGS(pwiv_ep)
);

DECWAWE_EVENT_CWASS(cdns3_wog_wequest_handwed,
	TP_PWOTO(stwuct cdns3_wequest *pwiv_weq, int cuwwent_index,
		 int handwed),
	TP_AWGS(pwiv_weq, cuwwent_index, handwed),
	TP_STWUCT__entwy(
		__fiewd(stwuct cdns3_wequest *, pwiv_weq)
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
		__entwy->dequeue_idx = pwiv_weq->pwiv_ep->dequeue;
		__entwy->enqueue_idx = pwiv_weq->pwiv_ep->enqueue;
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

DEFINE_EVENT(cdns3_wog_wequest_handwed, cdns3_wequest_handwed,
	TP_PWOTO(stwuct cdns3_wequest *pwiv_weq, int cuwwent_index,
		 int handwed),
	TP_AWGS(pwiv_weq, cuwwent_index, handwed)
);
#endif /* __WINUX_CDNS3_TWACE */

/* this pawt must be outside headew guawd */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .

#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE cdns3-twace

#incwude <twace/define_twace.h>
