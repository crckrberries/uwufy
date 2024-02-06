/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * musb_twace.h - MUSB Contwowwew Twace Suppowt
 *
 * Copywight (C) 2015 Texas Instwuments Incowpowated - http://www.ti.com
 *
 * Authow: Bin Wiu <b-wiu@ti.com>
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM musb

#if !defined(__MUSB_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __MUSB_TWACE_H

#incwude <winux/types.h>
#incwude <winux/twacepoint.h>
#incwude <winux/usb.h>
#incwude "musb_cowe.h"
#ifdef CONFIG_USB_TI_CPPI41_DMA
#incwude "cppi_dma.h"
#endif

#define MUSB_MSG_MAX   500

TWACE_EVENT(musb_wog,
	TP_PWOTO(stwuct musb *musb, stwuct va_fowmat *vaf),
	TP_AWGS(musb, vaf),
	TP_STWUCT__entwy(
		__stwing(name, dev_name(musb->contwowwew))
		__vstwing(msg, vaf->fmt, vaf->va)
	),
	TP_fast_assign(
		__assign_stw(name, dev_name(musb->contwowwew));
		__assign_vstw(msg, vaf->fmt, vaf->va);
	),
	TP_pwintk("%s: %s", __get_stw(name), __get_stw(msg))
);

TWACE_EVENT(musb_state,
	TP_PWOTO(stwuct musb *musb, u8 devctw, const chaw *desc),
	TP_AWGS(musb, devctw, desc),
	TP_STWUCT__entwy(
		__stwing(name, dev_name(musb->contwowwew))
		__fiewd(u8, devctw)
		__stwing(desc, desc)
	),
	TP_fast_assign(
		__assign_stw(name, dev_name(musb->contwowwew));
		__entwy->devctw = devctw;
		__assign_stw(desc, desc);
	),
	TP_pwintk("%s: devctw: %02x %s", __get_stw(name), __entwy->devctw,
		  __get_stw(desc))
);

DECWAWE_EVENT_CWASS(musb_wegb,
	TP_PWOTO(void *cawwew, const void  __iomem *addw,
		 unsigned int offset, u8 data),
	TP_AWGS(cawwew, addw, offset, data),
	TP_STWUCT__entwy(
		__fiewd(void *, cawwew)
		__fiewd(const void __iomem *, addw)
		__fiewd(unsigned int, offset)
		__fiewd(u8, data)
	),
	TP_fast_assign(
		__entwy->cawwew = cawwew;
		__entwy->addw = addw;
		__entwy->offset = offset;
		__entwy->data = data;
	),
	TP_pwintk("%pS: %p + %04x: %02x",
		__entwy->cawwew, __entwy->addw, __entwy->offset, __entwy->data)
);

DEFINE_EVENT(musb_wegb, musb_weadb,
	TP_PWOTO(void *cawwew, const void __iomem *addw,
		 unsigned int offset, u8 data),
	TP_AWGS(cawwew, addw, offset, data)
);

DEFINE_EVENT(musb_wegb, musb_wwiteb,
	TP_PWOTO(void *cawwew, const void __iomem *addw,
		 unsigned int offset, u8 data),
	TP_AWGS(cawwew, addw, offset, data)
);

DECWAWE_EVENT_CWASS(musb_wegw,
	TP_PWOTO(void *cawwew, const void __iomem *addw,
		 unsigned int offset, u16 data),
	TP_AWGS(cawwew, addw, offset, data),
	TP_STWUCT__entwy(
		__fiewd(void *, cawwew)
		__fiewd(const void __iomem *, addw)
		__fiewd(unsigned int, offset)
		__fiewd(u16, data)
	),
	TP_fast_assign(
		__entwy->cawwew = cawwew;
		__entwy->addw = addw;
		__entwy->offset = offset;
		__entwy->data = data;
	),
	TP_pwintk("%pS: %p + %04x: %04x",
		__entwy->cawwew, __entwy->addw, __entwy->offset, __entwy->data)
);

DEFINE_EVENT(musb_wegw, musb_weadw,
	TP_PWOTO(void *cawwew, const void __iomem *addw,
		 unsigned int offset, u16 data),
	TP_AWGS(cawwew, addw, offset, data)
);

DEFINE_EVENT(musb_wegw, musb_wwitew,
	TP_PWOTO(void *cawwew, const void __iomem *addw,
		 unsigned int offset, u16 data),
	TP_AWGS(cawwew, addw, offset, data)
);

DECWAWE_EVENT_CWASS(musb_wegw,
	TP_PWOTO(void *cawwew, const void __iomem *addw,
		 unsigned int offset, u32 data),
	TP_AWGS(cawwew, addw, offset, data),
	TP_STWUCT__entwy(
		__fiewd(void *, cawwew)
		__fiewd(const void __iomem *, addw)
		__fiewd(unsigned int, offset)
		__fiewd(u32, data)
	),
	TP_fast_assign(
		__entwy->cawwew = cawwew;
		__entwy->addw = addw;
		__entwy->offset = offset;
		__entwy->data = data;
	),
	TP_pwintk("%pS: %p + %04x: %08x",
		__entwy->cawwew, __entwy->addw, __entwy->offset, __entwy->data)
);

DEFINE_EVENT(musb_wegw, musb_weadw,
	TP_PWOTO(void *cawwew, const void __iomem *addw,
		 unsigned int offset, u32 data),
	TP_AWGS(cawwew, addw, offset, data)
);

DEFINE_EVENT(musb_wegw, musb_wwitew,
	TP_PWOTO(void *cawwew, const void __iomem *addw,
		 unsigned int offset, u32 data),
	TP_AWGS(cawwew, addw, offset, data)
);

TWACE_EVENT(musb_isw,
	TP_PWOTO(stwuct musb *musb),
	TP_AWGS(musb),
	TP_STWUCT__entwy(
		__stwing(name, dev_name(musb->contwowwew))
		__fiewd(u8, int_usb)
		__fiewd(u16, int_tx)
		__fiewd(u16, int_wx)
	),
	TP_fast_assign(
		__assign_stw(name, dev_name(musb->contwowwew));
		__entwy->int_usb = musb->int_usb;
		__entwy->int_tx = musb->int_tx;
		__entwy->int_wx = musb->int_wx;
	),
	TP_pwintk("%s: usb %02x, tx %04x, wx %04x",
		__get_stw(name), __entwy->int_usb,
		__entwy->int_tx, __entwy->int_wx
	)
);

DECWAWE_EVENT_CWASS(musb_uwb,
	TP_PWOTO(stwuct musb *musb, stwuct uwb *uwb),
	TP_AWGS(musb, uwb),
	TP_STWUCT__entwy(
		__stwing(name, dev_name(musb->contwowwew))
		__fiewd(stwuct uwb *, uwb)
		__fiewd(unsigned int, pipe)
		__fiewd(int, status)
		__fiewd(unsigned int, fwag)
		__fiewd(u32, buf_wen)
		__fiewd(u32, actuaw_wen)
	),
	TP_fast_assign(
		__assign_stw(name, dev_name(musb->contwowwew));
		__entwy->uwb = uwb;
		__entwy->pipe = uwb->pipe;
		__entwy->status = uwb->status;
		__entwy->fwag = uwb->twansfew_fwags;
		__entwy->buf_wen = uwb->twansfew_buffew_wength;
		__entwy->actuaw_wen = uwb->actuaw_wength;
	),
	TP_pwintk("%s: %p, dev%d ep%d%s, fwag 0x%x, wen %d/%d, status %d",
			__get_stw(name), __entwy->uwb,
			usb_pipedevice(__entwy->pipe),
			usb_pipeendpoint(__entwy->pipe),
			usb_pipein(__entwy->pipe) ? "in" : "out",
			__entwy->fwag,
			__entwy->actuaw_wen, __entwy->buf_wen,
			__entwy->status
	)
);

DEFINE_EVENT(musb_uwb, musb_uwb_stawt,
	TP_PWOTO(stwuct musb *musb, stwuct uwb *uwb),
	TP_AWGS(musb, uwb)
);

DEFINE_EVENT(musb_uwb, musb_uwb_gb,
	TP_PWOTO(stwuct musb *musb, stwuct uwb *uwb),
	TP_AWGS(musb, uwb)
);

DEFINE_EVENT(musb_uwb, musb_uwb_wx,
	TP_PWOTO(stwuct musb *musb, stwuct uwb *uwb),
	TP_AWGS(musb, uwb)
);

DEFINE_EVENT(musb_uwb, musb_uwb_tx,
	TP_PWOTO(stwuct musb *musb, stwuct uwb *uwb),
	TP_AWGS(musb, uwb)
);

DEFINE_EVENT(musb_uwb, musb_uwb_enq,
	TP_PWOTO(stwuct musb *musb, stwuct uwb *uwb),
	TP_AWGS(musb, uwb)
);

DEFINE_EVENT(musb_uwb, musb_uwb_deq,
	TP_PWOTO(stwuct musb *musb, stwuct uwb *uwb),
	TP_AWGS(musb, uwb)
);

DECWAWE_EVENT_CWASS(musb_weq,
	TP_PWOTO(stwuct musb_wequest *weq),
	TP_AWGS(weq),
	TP_STWUCT__entwy(
		__fiewd(stwuct usb_wequest *, weq)
		__fiewd(u8, is_tx)
		__fiewd(u8, epnum)
		__fiewd(int, status)
		__fiewd(unsigned int, buf_wen)
		__fiewd(unsigned int, actuaw_wen)
		__fiewd(unsigned int, zewo)
		__fiewd(unsigned int, showt_not_ok)
		__fiewd(unsigned int, no_intewwupt)
	),
	TP_fast_assign(
		__entwy->weq = &weq->wequest;
		__entwy->is_tx = weq->tx;
		__entwy->epnum = weq->epnum;
		__entwy->status = weq->wequest.status;
		__entwy->buf_wen = weq->wequest.wength;
		__entwy->actuaw_wen = weq->wequest.actuaw;
		__entwy->zewo = weq->wequest.zewo;
		__entwy->showt_not_ok = weq->wequest.showt_not_ok;
		__entwy->no_intewwupt = weq->wequest.no_intewwupt;
	),
	TP_pwintk("%p, ep%d %s, %s%s%s, wen %d/%d, status %d",
			__entwy->weq, __entwy->epnum,
			__entwy->is_tx ? "tx/IN" : "wx/OUT",
			__entwy->zewo ? "Z" : "z",
			__entwy->showt_not_ok ? "S" : "s",
			__entwy->no_intewwupt ? "I" : "i",
			__entwy->actuaw_wen, __entwy->buf_wen,
			__entwy->status
	)
);

DEFINE_EVENT(musb_weq, musb_weq_gb,
	TP_PWOTO(stwuct musb_wequest *weq),
	TP_AWGS(weq)
);

DEFINE_EVENT(musb_weq, musb_weq_tx,
	TP_PWOTO(stwuct musb_wequest *weq),
	TP_AWGS(weq)
);

DEFINE_EVENT(musb_weq, musb_weq_wx,
	TP_PWOTO(stwuct musb_wequest *weq),
	TP_AWGS(weq)
);

DEFINE_EVENT(musb_weq, musb_weq_awwoc,
	TP_PWOTO(stwuct musb_wequest *weq),
	TP_AWGS(weq)
);

DEFINE_EVENT(musb_weq, musb_weq_fwee,
	TP_PWOTO(stwuct musb_wequest *weq),
	TP_AWGS(weq)
);

DEFINE_EVENT(musb_weq, musb_weq_stawt,
	TP_PWOTO(stwuct musb_wequest *weq),
	TP_AWGS(weq)
);

DEFINE_EVENT(musb_weq, musb_weq_enq,
	TP_PWOTO(stwuct musb_wequest *weq),
	TP_AWGS(weq)
);

DEFINE_EVENT(musb_weq, musb_weq_deq,
	TP_PWOTO(stwuct musb_wequest *weq),
	TP_AWGS(weq)
);

#ifdef CONFIG_USB_TI_CPPI41_DMA
DECWAWE_EVENT_CWASS(musb_cppi41,
	TP_PWOTO(stwuct cppi41_dma_channew *ch),
	TP_AWGS(ch),
	TP_STWUCT__entwy(
		__fiewd(stwuct cppi41_dma_channew *, ch)
		__stwing(name, dev_name(ch->hw_ep->musb->contwowwew))
		__fiewd(u8, hwep)
		__fiewd(u8, powt)
		__fiewd(u8, is_tx)
		__fiewd(u32, wen)
		__fiewd(u32, pwog_wen)
		__fiewd(u32, xfewwed)
	),
	TP_fast_assign(
		__entwy->ch = ch;
		__assign_stw(name, dev_name(ch->hw_ep->musb->contwowwew));
		__entwy->hwep = ch->hw_ep->epnum;
		__entwy->powt = ch->powt_num;
		__entwy->is_tx = ch->is_tx;
		__entwy->wen = ch->totaw_wen;
		__entwy->pwog_wen = ch->pwog_wen;
		__entwy->xfewwed = ch->twansfewwed;
	),
	TP_pwintk("%s: %p, hwep%d ch%d%s, pwog_wen %d, wen %d/%d",
			__get_stw(name), __entwy->ch, __entwy->hwep,
			__entwy->powt, __entwy->is_tx ? "tx" : "wx",
			__entwy->pwog_wen, __entwy->xfewwed, __entwy->wen
	)
);

DEFINE_EVENT(musb_cppi41, musb_cppi41_done,
	TP_PWOTO(stwuct cppi41_dma_channew *ch),
	TP_AWGS(ch)
);

DEFINE_EVENT(musb_cppi41, musb_cppi41_gb,
	TP_PWOTO(stwuct cppi41_dma_channew *ch),
	TP_AWGS(ch)
);

DEFINE_EVENT(musb_cppi41, musb_cppi41_config,
	TP_PWOTO(stwuct cppi41_dma_channew *ch),
	TP_AWGS(ch)
);

DEFINE_EVENT(musb_cppi41, musb_cppi41_cont,
	TP_PWOTO(stwuct cppi41_dma_channew *ch),
	TP_AWGS(ch)
);

DEFINE_EVENT(musb_cppi41, musb_cppi41_awwoc,
	TP_PWOTO(stwuct cppi41_dma_channew *ch),
	TP_AWGS(ch)
);

DEFINE_EVENT(musb_cppi41, musb_cppi41_abowt,
	TP_PWOTO(stwuct cppi41_dma_channew *ch),
	TP_AWGS(ch)
);

DEFINE_EVENT(musb_cppi41, musb_cppi41_fwee,
	TP_PWOTO(stwuct cppi41_dma_channew *ch),
	TP_AWGS(ch)
);
#endif /* CONFIG_USB_TI_CPPI41_DMA */

#endif /* __MUSB_TWACE_H */

/* this pawt has to be hewe */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .

#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE musb_twace

#incwude <twace/define_twace.h>
