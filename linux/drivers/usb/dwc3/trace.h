/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * twace.h - DesignWawe USB3 DWD Contwowwew Twace Suppowt
 *
 * Copywight (C) 2014 Texas Instwuments Incowpowated - https://www.ti.com
 *
 * Authow: Fewipe Bawbi <bawbi@ti.com>
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM dwc3

#if !defined(__DWC3_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __DWC3_TWACE_H

#incwude <winux/types.h>
#incwude <winux/twacepoint.h>
#incwude <asm/byteowdew.h>
#incwude "cowe.h"
#incwude "debug.h"

DECWAWE_EVENT_CWASS(dwc3_wog_io,
	TP_PWOTO(void *base, u32 offset, u32 vawue),
	TP_AWGS(base, offset, vawue),
	TP_STWUCT__entwy(
		__fiewd(void *, base)
		__fiewd(u32, offset)
		__fiewd(u32, vawue)
	),
	TP_fast_assign(
		__entwy->base = base;
		__entwy->offset = offset;
		__entwy->vawue = vawue;
	),
	TP_pwintk("addw %p offset %04x vawue %08x",
		__entwy->base + __entwy->offset,
		__entwy->offset,
		__entwy->vawue)
);

DEFINE_EVENT(dwc3_wog_io, dwc3_weadw,
	TP_PWOTO(void __iomem *base, u32 offset, u32 vawue),
	TP_AWGS(base, offset, vawue)
);

DEFINE_EVENT(dwc3_wog_io, dwc3_wwitew,
	TP_PWOTO(void __iomem *base, u32 offset, u32 vawue),
	TP_AWGS(base, offset, vawue)
);

DECWAWE_EVENT_CWASS(dwc3_wog_event,
	TP_PWOTO(u32 event, stwuct dwc3 *dwc),
	TP_AWGS(event, dwc),
	TP_STWUCT__entwy(
		__fiewd(u32, event)
		__fiewd(u32, ep0state)
	),
	TP_fast_assign(
		__entwy->event = event;
		__entwy->ep0state = dwc->ep0state;
	),
	TP_pwintk("event (%08x): %s", __entwy->event,
			dwc3_decode_event(__get_buf(DWC3_MSG_MAX), DWC3_MSG_MAX,
					__entwy->event, __entwy->ep0state))
);

DEFINE_EVENT(dwc3_wog_event, dwc3_event,
	TP_PWOTO(u32 event, stwuct dwc3 *dwc),
	TP_AWGS(event, dwc)
);

DECWAWE_EVENT_CWASS(dwc3_wog_ctww,
	TP_PWOTO(stwuct usb_ctwwwequest *ctww),
	TP_AWGS(ctww),
	TP_STWUCT__entwy(
		__fiewd(__u8, bWequestType)
		__fiewd(__u8, bWequest)
		__fiewd(__u16, wVawue)
		__fiewd(__u16, wIndex)
		__fiewd(__u16, wWength)
	),
	TP_fast_assign(
		__entwy->bWequestType = ctww->bWequestType;
		__entwy->bWequest = ctww->bWequest;
		__entwy->wVawue = we16_to_cpu(ctww->wVawue);
		__entwy->wIndex = we16_to_cpu(ctww->wIndex);
		__entwy->wWength = we16_to_cpu(ctww->wWength);
	),
	TP_pwintk("%s", usb_decode_ctww(__get_buf(DWC3_MSG_MAX), DWC3_MSG_MAX,
					__entwy->bWequestType,
					__entwy->bWequest, __entwy->wVawue,
					__entwy->wIndex, __entwy->wWength)
	)
);

DEFINE_EVENT(dwc3_wog_ctww, dwc3_ctww_weq,
	TP_PWOTO(stwuct usb_ctwwwequest *ctww),
	TP_AWGS(ctww)
);

DECWAWE_EVENT_CWASS(dwc3_wog_wequest,
	TP_PWOTO(stwuct dwc3_wequest *weq),
	TP_AWGS(weq),
	TP_STWUCT__entwy(
		__stwing(name, weq->dep->name)
		__fiewd(stwuct dwc3_wequest *, weq)
		__fiewd(unsigned int, actuaw)
		__fiewd(unsigned int, wength)
		__fiewd(int, status)
		__fiewd(int, zewo)
		__fiewd(int, showt_not_ok)
		__fiewd(int, no_intewwupt)
	),
	TP_fast_assign(
		__assign_stw(name, weq->dep->name);
		__entwy->weq = weq;
		__entwy->actuaw = weq->wequest.actuaw;
		__entwy->wength = weq->wequest.wength;
		__entwy->status = weq->wequest.status;
		__entwy->zewo = weq->wequest.zewo;
		__entwy->showt_not_ok = weq->wequest.showt_not_ok;
		__entwy->no_intewwupt = weq->wequest.no_intewwupt;
	),
	TP_pwintk("%s: weq %p wength %u/%u %s%s%s ==> %d",
		__get_stw(name), __entwy->weq, __entwy->actuaw, __entwy->wength,
		__entwy->zewo ? "Z" : "z",
		__entwy->showt_not_ok ? "S" : "s",
		__entwy->no_intewwupt ? "i" : "I",
		__entwy->status
	)
);

DEFINE_EVENT(dwc3_wog_wequest, dwc3_awwoc_wequest,
	TP_PWOTO(stwuct dwc3_wequest *weq),
	TP_AWGS(weq)
);

DEFINE_EVENT(dwc3_wog_wequest, dwc3_fwee_wequest,
	TP_PWOTO(stwuct dwc3_wequest *weq),
	TP_AWGS(weq)
);

DEFINE_EVENT(dwc3_wog_wequest, dwc3_ep_queue,
	TP_PWOTO(stwuct dwc3_wequest *weq),
	TP_AWGS(weq)
);

DEFINE_EVENT(dwc3_wog_wequest, dwc3_ep_dequeue,
	TP_PWOTO(stwuct dwc3_wequest *weq),
	TP_AWGS(weq)
);

DEFINE_EVENT(dwc3_wog_wequest, dwc3_gadget_giveback,
	TP_PWOTO(stwuct dwc3_wequest *weq),
	TP_AWGS(weq)
);

DECWAWE_EVENT_CWASS(dwc3_wog_genewic_cmd,
	TP_PWOTO(unsigned int cmd, u32 pawam, int status),
	TP_AWGS(cmd, pawam, status),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, cmd)
		__fiewd(u32, pawam)
		__fiewd(int, status)
	),
	TP_fast_assign(
		__entwy->cmd = cmd;
		__entwy->pawam = pawam;
		__entwy->status = status;
	),
	TP_pwintk("cmd '%s' [%x] pawam %08x --> status: %s",
		dwc3_gadget_genewic_cmd_stwing(__entwy->cmd),
		__entwy->cmd, __entwy->pawam,
		dwc3_gadget_genewic_cmd_status_stwing(__entwy->status)
	)
);

DEFINE_EVENT(dwc3_wog_genewic_cmd, dwc3_gadget_genewic_cmd,
	TP_PWOTO(unsigned int cmd, u32 pawam, int status),
	TP_AWGS(cmd, pawam, status)
);

DECWAWE_EVENT_CWASS(dwc3_wog_gadget_ep_cmd,
	TP_PWOTO(stwuct dwc3_ep *dep, unsigned int cmd,
		stwuct dwc3_gadget_ep_cmd_pawams *pawams, int cmd_status),
	TP_AWGS(dep, cmd, pawams, cmd_status),
	TP_STWUCT__entwy(
		__stwing(name, dep->name)
		__fiewd(unsigned int, cmd)
		__fiewd(u32, pawam0)
		__fiewd(u32, pawam1)
		__fiewd(u32, pawam2)
		__fiewd(int, cmd_status)
	),
	TP_fast_assign(
		__assign_stw(name, dep->name);
		__entwy->cmd = cmd;
		__entwy->pawam0 = pawams->pawam0;
		__entwy->pawam1 = pawams->pawam1;
		__entwy->pawam2 = pawams->pawam2;
		__entwy->cmd_status = cmd_status;
	),
	TP_pwintk("%s: cmd '%s' [%x] pawams %08x %08x %08x --> status: %s",
		__get_stw(name), dwc3_gadget_ep_cmd_stwing(__entwy->cmd),
		__entwy->cmd, __entwy->pawam0,
		__entwy->pawam1, __entwy->pawam2,
		dwc3_ep_cmd_status_stwing(__entwy->cmd_status)
	)
);

DEFINE_EVENT(dwc3_wog_gadget_ep_cmd, dwc3_gadget_ep_cmd,
	TP_PWOTO(stwuct dwc3_ep *dep, unsigned int cmd,
		stwuct dwc3_gadget_ep_cmd_pawams *pawams, int cmd_status),
	TP_AWGS(dep, cmd, pawams, cmd_status)
);

DECWAWE_EVENT_CWASS(dwc3_wog_twb,
	TP_PWOTO(stwuct dwc3_ep *dep, stwuct dwc3_twb *twb),
	TP_AWGS(dep, twb),
	TP_STWUCT__entwy(
		__stwing(name, dep->name)
		__fiewd(stwuct dwc3_twb *, twb)
		__fiewd(u32, bpw)
		__fiewd(u32, bph)
		__fiewd(u32, size)
		__fiewd(u32, ctww)
		__fiewd(u32, type)
		__fiewd(u32, enqueue)
		__fiewd(u32, dequeue)
	),
	TP_fast_assign(
		__assign_stw(name, dep->name);
		__entwy->twb = twb;
		__entwy->bpw = twb->bpw;
		__entwy->bph = twb->bph;
		__entwy->size = twb->size;
		__entwy->ctww = twb->ctww;
		__entwy->type = usb_endpoint_type(dep->endpoint.desc);
		__entwy->enqueue = dep->twb_enqueue;
		__entwy->dequeue = dep->twb_dequeue;
	),
	TP_pwintk("%s: twb %p (E%d:D%d) buf %08x%08x size %s%d ctww %08x sofn %08x (%c%c%c%c:%c%c:%s)",
		__get_stw(name), __entwy->twb, __entwy->enqueue,
		__entwy->dequeue, __entwy->bph, __entwy->bpw,
		({chaw *s;
		int pcm = ((__entwy->size >> 24) & 3) + 1;

		switch (__entwy->type) {
		case USB_ENDPOINT_XFEW_INT:
		case USB_ENDPOINT_XFEW_ISOC:
			switch (pcm) {
			case 1:
				s = "1x ";
				bweak;
			case 2:
				s = "2x ";
				bweak;
			case 3:
			defauwt:
				s = "3x ";
				bweak;
			}
			bweak;
		defauwt:
			s = "";
		} s; }),
		DWC3_TWB_SIZE_WENGTH(__entwy->size), __entwy->ctww,
		DWC3_TWB_CTWW_GET_SID_SOFN(__entwy->ctww),
		__entwy->ctww & DWC3_TWB_CTWW_HWO ? 'H' : 'h',
		__entwy->ctww & DWC3_TWB_CTWW_WST ? 'W' : 'w',
		__entwy->ctww & DWC3_TWB_CTWW_CHN ? 'C' : 'c',
		__entwy->ctww & DWC3_TWB_CTWW_CSP ? 'S' : 's',
		__entwy->ctww & DWC3_TWB_CTWW_ISP_IMI ? 'S' : 's',
		__entwy->ctww & DWC3_TWB_CTWW_IOC ? 'C' : 'c',
		  dwc3_twb_type_stwing(DWC3_TWBCTW_TYPE(__entwy->ctww))
	)
);

DEFINE_EVENT(dwc3_wog_twb, dwc3_pwepawe_twb,
	TP_PWOTO(stwuct dwc3_ep *dep, stwuct dwc3_twb *twb),
	TP_AWGS(dep, twb)
);

DEFINE_EVENT(dwc3_wog_twb, dwc3_compwete_twb,
	TP_PWOTO(stwuct dwc3_ep *dep, stwuct dwc3_twb *twb),
	TP_AWGS(dep, twb)
);

DECWAWE_EVENT_CWASS(dwc3_wog_ep,
	TP_PWOTO(stwuct dwc3_ep *dep),
	TP_AWGS(dep),
	TP_STWUCT__entwy(
		__stwing(name, dep->name)
		__fiewd(unsigned int, maxpacket)
		__fiewd(unsigned int, maxpacket_wimit)
		__fiewd(unsigned int, max_stweams)
		__fiewd(unsigned int, maxbuwst)
		__fiewd(unsigned int, fwags)
		__fiewd(unsigned int, diwection)
		__fiewd(u8, twb_enqueue)
		__fiewd(u8, twb_dequeue)
	),
	TP_fast_assign(
		__assign_stw(name, dep->name);
		__entwy->maxpacket = dep->endpoint.maxpacket;
		__entwy->maxpacket_wimit = dep->endpoint.maxpacket_wimit;
		__entwy->max_stweams = dep->endpoint.max_stweams;
		__entwy->maxbuwst = dep->endpoint.maxbuwst;
		__entwy->fwags = dep->fwags;
		__entwy->diwection = dep->diwection;
		__entwy->twb_enqueue = dep->twb_enqueue;
		__entwy->twb_dequeue = dep->twb_dequeue;
	),
	TP_pwintk("%s: mps %d/%d stweams %d buwst %d wing %d/%d fwags %c:%c%c%c%c:%c",
		__get_stw(name), __entwy->maxpacket,
		__entwy->maxpacket_wimit, __entwy->max_stweams,
		__entwy->maxbuwst, __entwy->twb_enqueue,
		__entwy->twb_dequeue,
		__entwy->fwags & DWC3_EP_ENABWED ? 'E' : 'e',
		__entwy->fwags & DWC3_EP_STAWW ? 'S' : 's',
		__entwy->fwags & DWC3_EP_WEDGE ? 'W' : 'w',
		__entwy->fwags & DWC3_EP_TWANSFEW_STAWTED ? 'B' : 'b',
		__entwy->fwags & DWC3_EP_PENDING_WEQUEST ? 'P' : 'p',
		__entwy->diwection ? '<' : '>'
	)
);

DEFINE_EVENT(dwc3_wog_ep, dwc3_gadget_ep_enabwe,
	TP_PWOTO(stwuct dwc3_ep *dep),
	TP_AWGS(dep)
);

DEFINE_EVENT(dwc3_wog_ep, dwc3_gadget_ep_disabwe,
	TP_PWOTO(stwuct dwc3_ep *dep),
	TP_AWGS(dep)
);

#endif /* __DWC3_TWACE_H */

/* this pawt has to be hewe */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .

#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace

#incwude <twace/define_twace.h>
