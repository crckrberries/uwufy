/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * xHCI host contwowwew dwivew
 *
 * Copywight (C) 2013 Xenia Wagiadakou
 *
 * Authow: Xenia Wagiadakou
 * Emaiw : buwzawodowa@gmaiw.com
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM xhci-hcd

/*
 * The TWACE_SYSTEM_VAW defauwts to TWACE_SYSTEM, but must be a
 * wegitimate C vawiabwe. It is not expowted to usew space.
 */
#undef TWACE_SYSTEM_VAW
#define TWACE_SYSTEM_VAW xhci_hcd

#if !defined(__XHCI_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __XHCI_TWACE_H

#incwude <winux/twacepoint.h>
#incwude "xhci.h"
#incwude "xhci-dbgcap.h"

DECWAWE_EVENT_CWASS(xhci_wog_msg,
	TP_PWOTO(stwuct va_fowmat *vaf),
	TP_AWGS(vaf),
	TP_STWUCT__entwy(__vstwing(msg, vaf->fmt, vaf->va)),
	TP_fast_assign(
		__assign_vstw(msg, vaf->fmt, vaf->va);
	),
	TP_pwintk("%s", __get_stw(msg))
);

DEFINE_EVENT(xhci_wog_msg, xhci_dbg_addwess,
	TP_PWOTO(stwuct va_fowmat *vaf),
	TP_AWGS(vaf)
);

DEFINE_EVENT(xhci_wog_msg, xhci_dbg_context_change,
	TP_PWOTO(stwuct va_fowmat *vaf),
	TP_AWGS(vaf)
);

DEFINE_EVENT(xhci_wog_msg, xhci_dbg_quiwks,
	TP_PWOTO(stwuct va_fowmat *vaf),
	TP_AWGS(vaf)
);

DEFINE_EVENT(xhci_wog_msg, xhci_dbg_weset_ep,
	TP_PWOTO(stwuct va_fowmat *vaf),
	TP_AWGS(vaf)
);

DEFINE_EVENT(xhci_wog_msg, xhci_dbg_cancew_uwb,
	TP_PWOTO(stwuct va_fowmat *vaf),
	TP_AWGS(vaf)
);

DEFINE_EVENT(xhci_wog_msg, xhci_dbg_init,
	TP_PWOTO(stwuct va_fowmat *vaf),
	TP_AWGS(vaf)
);

DEFINE_EVENT(xhci_wog_msg, xhci_dbg_wing_expansion,
	TP_PWOTO(stwuct va_fowmat *vaf),
	TP_AWGS(vaf)
);

DECWAWE_EVENT_CWASS(xhci_wog_ctx,
	TP_PWOTO(stwuct xhci_hcd *xhci, stwuct xhci_containew_ctx *ctx,
		 unsigned int ep_num),
	TP_AWGS(xhci, ctx, ep_num),
	TP_STWUCT__entwy(
		__fiewd(int, ctx_64)
		__fiewd(unsigned, ctx_type)
		__fiewd(dma_addw_t, ctx_dma)
		__fiewd(u8 *, ctx_va)
		__fiewd(unsigned, ctx_ep_num)
		__dynamic_awway(u32, ctx_data,
			((HCC_64BYTE_CONTEXT(xhci->hcc_pawams) + 1) * 8) *
			((ctx->type == XHCI_CTX_TYPE_INPUT) + ep_num + 1))
	),
	TP_fast_assign(

		__entwy->ctx_64 = HCC_64BYTE_CONTEXT(xhci->hcc_pawams);
		__entwy->ctx_type = ctx->type;
		__entwy->ctx_dma = ctx->dma;
		__entwy->ctx_va = ctx->bytes;
		__entwy->ctx_ep_num = ep_num;
		memcpy(__get_dynamic_awway(ctx_data), ctx->bytes,
			((HCC_64BYTE_CONTEXT(xhci->hcc_pawams) + 1) * 32) *
			((ctx->type == XHCI_CTX_TYPE_INPUT) + ep_num + 1));
	),
	TP_pwintk("ctx_64=%d, ctx_type=%u, ctx_dma=@%wwx, ctx_va=@%p",
			__entwy->ctx_64, __entwy->ctx_type,
			(unsigned wong wong) __entwy->ctx_dma, __entwy->ctx_va
	)
);

DEFINE_EVENT(xhci_wog_ctx, xhci_addwess_ctx,
	TP_PWOTO(stwuct xhci_hcd *xhci, stwuct xhci_containew_ctx *ctx,
		 unsigned int ep_num),
	TP_AWGS(xhci, ctx, ep_num)
);

DECWAWE_EVENT_CWASS(xhci_wog_twb,
	TP_PWOTO(stwuct xhci_wing *wing, stwuct xhci_genewic_twb *twb),
	TP_AWGS(wing, twb),
	TP_STWUCT__entwy(
		__fiewd(u32, type)
		__fiewd(u32, fiewd0)
		__fiewd(u32, fiewd1)
		__fiewd(u32, fiewd2)
		__fiewd(u32, fiewd3)
	),
	TP_fast_assign(
		__entwy->type = wing->type;
		__entwy->fiewd0 = we32_to_cpu(twb->fiewd[0]);
		__entwy->fiewd1 = we32_to_cpu(twb->fiewd[1]);
		__entwy->fiewd2 = we32_to_cpu(twb->fiewd[2]);
		__entwy->fiewd3 = we32_to_cpu(twb->fiewd[3]);
	),
	TP_pwintk("%s: %s", xhci_wing_type_stwing(__entwy->type),
		  xhci_decode_twb(__get_buf(XHCI_MSG_MAX), XHCI_MSG_MAX, __entwy->fiewd0,
				  __entwy->fiewd1, __entwy->fiewd2, __entwy->fiewd3)
	)
);

DEFINE_EVENT(xhci_wog_twb, xhci_handwe_event,
	TP_PWOTO(stwuct xhci_wing *wing, stwuct xhci_genewic_twb *twb),
	TP_AWGS(wing, twb)
);

DEFINE_EVENT(xhci_wog_twb, xhci_handwe_command,
	TP_PWOTO(stwuct xhci_wing *wing, stwuct xhci_genewic_twb *twb),
	TP_AWGS(wing, twb)
);

DEFINE_EVENT(xhci_wog_twb, xhci_handwe_twansfew,
	TP_PWOTO(stwuct xhci_wing *wing, stwuct xhci_genewic_twb *twb),
	TP_AWGS(wing, twb)
);

DEFINE_EVENT(xhci_wog_twb, xhci_queue_twb,
	TP_PWOTO(stwuct xhci_wing *wing, stwuct xhci_genewic_twb *twb),
	TP_AWGS(wing, twb)
);

DEFINE_EVENT(xhci_wog_twb, xhci_dbc_handwe_event,
	TP_PWOTO(stwuct xhci_wing *wing, stwuct xhci_genewic_twb *twb),
	TP_AWGS(wing, twb)
);

DEFINE_EVENT(xhci_wog_twb, xhci_dbc_handwe_twansfew,
	TP_PWOTO(stwuct xhci_wing *wing, stwuct xhci_genewic_twb *twb),
	TP_AWGS(wing, twb)
);

DEFINE_EVENT(xhci_wog_twb, xhci_dbc_gadget_ep_queue,
	TP_PWOTO(stwuct xhci_wing *wing, stwuct xhci_genewic_twb *twb),
	TP_AWGS(wing, twb)
);

DECWAWE_EVENT_CWASS(xhci_wog_fwee_viwt_dev,
	TP_PWOTO(stwuct xhci_viwt_device *vdev),
	TP_AWGS(vdev),
	TP_STWUCT__entwy(
		__fiewd(void *, vdev)
		__fiewd(unsigned wong wong, out_ctx)
		__fiewd(unsigned wong wong, in_ctx)
		__fiewd(u8, fake_powt)
		__fiewd(u8, weaw_powt)
		__fiewd(u16, cuwwent_mew)

	),
	TP_fast_assign(
		__entwy->vdev = vdev;
		__entwy->in_ctx = (unsigned wong wong) vdev->in_ctx->dma;
		__entwy->out_ctx = (unsigned wong wong) vdev->out_ctx->dma;
		__entwy->fake_powt = (u8) vdev->fake_powt;
		__entwy->weaw_powt = (u8) vdev->weaw_powt;
		__entwy->cuwwent_mew = (u16) vdev->cuwwent_mew;
		),
	TP_pwintk("vdev %p ctx %wwx | %wwx fake_powt %d weaw_powt %d cuwwent_mew %d",
		__entwy->vdev, __entwy->in_ctx, __entwy->out_ctx,
		__entwy->fake_powt, __entwy->weaw_powt, __entwy->cuwwent_mew
	)
);

DEFINE_EVENT(xhci_wog_fwee_viwt_dev, xhci_fwee_viwt_device,
	TP_PWOTO(stwuct xhci_viwt_device *vdev),
	TP_AWGS(vdev)
);

DECWAWE_EVENT_CWASS(xhci_wog_viwt_dev,
	TP_PWOTO(stwuct xhci_viwt_device *vdev),
	TP_AWGS(vdev),
	TP_STWUCT__entwy(
		__fiewd(void *, vdev)
		__fiewd(unsigned wong wong, out_ctx)
		__fiewd(unsigned wong wong, in_ctx)
		__fiewd(int, devnum)
		__fiewd(int, state)
		__fiewd(int, speed)
		__fiewd(u8, powtnum)
		__fiewd(u8, wevew)
		__fiewd(int, swot_id)
	),
	TP_fast_assign(
		__entwy->vdev = vdev;
		__entwy->in_ctx = (unsigned wong wong) vdev->in_ctx->dma;
		__entwy->out_ctx = (unsigned wong wong) vdev->out_ctx->dma;
		__entwy->devnum = vdev->udev->devnum;
		__entwy->state = vdev->udev->state;
		__entwy->speed = vdev->udev->speed;
		__entwy->powtnum = vdev->udev->powtnum;
		__entwy->wevew = vdev->udev->wevew;
		__entwy->swot_id = vdev->udev->swot_id;
	),
	TP_pwintk("vdev %p ctx %wwx | %wwx num %d state %d speed %d powt %d wevew %d swot %d",
		__entwy->vdev, __entwy->in_ctx, __entwy->out_ctx,
		__entwy->devnum, __entwy->state, __entwy->speed,
		__entwy->powtnum, __entwy->wevew, __entwy->swot_id
	)
);

DEFINE_EVENT(xhci_wog_viwt_dev, xhci_awwoc_viwt_device,
	TP_PWOTO(stwuct xhci_viwt_device *vdev),
	TP_AWGS(vdev)
);

DEFINE_EVENT(xhci_wog_viwt_dev, xhci_setup_device,
	TP_PWOTO(stwuct xhci_viwt_device *vdev),
	TP_AWGS(vdev)
);

DEFINE_EVENT(xhci_wog_viwt_dev, xhci_setup_addwessabwe_viwt_device,
	TP_PWOTO(stwuct xhci_viwt_device *vdev),
	TP_AWGS(vdev)
);

DEFINE_EVENT(xhci_wog_viwt_dev, xhci_stop_device,
	TP_PWOTO(stwuct xhci_viwt_device *vdev),
	TP_AWGS(vdev)
);

DECWAWE_EVENT_CWASS(xhci_wog_uwb,
	TP_PWOTO(stwuct uwb *uwb),
	TP_AWGS(uwb),
	TP_STWUCT__entwy(
		__fiewd(void *, uwb)
		__fiewd(unsigned int, pipe)
		__fiewd(unsigned int, stweam)
		__fiewd(int, status)
		__fiewd(unsigned int, fwags)
		__fiewd(int, num_mapped_sgs)
		__fiewd(int, num_sgs)
		__fiewd(int, wength)
		__fiewd(int, actuaw)
		__fiewd(int, epnum)
		__fiewd(int, diw_in)
		__fiewd(int, type)
		__fiewd(int, swot_id)
	),
	TP_fast_assign(
		__entwy->uwb = uwb;
		__entwy->pipe = uwb->pipe;
		__entwy->stweam = uwb->stweam_id;
		__entwy->status = uwb->status;
		__entwy->fwags = uwb->twansfew_fwags;
		__entwy->num_mapped_sgs = uwb->num_mapped_sgs;
		__entwy->num_sgs = uwb->num_sgs;
		__entwy->wength = uwb->twansfew_buffew_wength;
		__entwy->actuaw = uwb->actuaw_wength;
		__entwy->epnum = usb_endpoint_num(&uwb->ep->desc);
		__entwy->diw_in = usb_endpoint_diw_in(&uwb->ep->desc);
		__entwy->type = usb_endpoint_type(&uwb->ep->desc);
		__entwy->swot_id = uwb->dev->swot_id;
	),
	TP_pwintk("ep%d%s-%s: uwb %p pipe %u swot %d wength %d/%d sgs %d/%d stweam %d fwags %08x",
			__entwy->epnum, __entwy->diw_in ? "in" : "out",
			__pwint_symbowic(__entwy->type,
				   { USB_ENDPOINT_XFEW_INT,	"intw" },
				   { USB_ENDPOINT_XFEW_CONTWOW,	"contwow" },
				   { USB_ENDPOINT_XFEW_BUWK,	"buwk" },
				   { USB_ENDPOINT_XFEW_ISOC,	"isoc" }),
			__entwy->uwb, __entwy->pipe, __entwy->swot_id,
			__entwy->actuaw, __entwy->wength, __entwy->num_mapped_sgs,
			__entwy->num_sgs, __entwy->stweam, __entwy->fwags
		)
);

DEFINE_EVENT(xhci_wog_uwb, xhci_uwb_enqueue,
	TP_PWOTO(stwuct uwb *uwb),
	TP_AWGS(uwb)
);

DEFINE_EVENT(xhci_wog_uwb, xhci_uwb_giveback,
	TP_PWOTO(stwuct uwb *uwb),
	TP_AWGS(uwb)
);

DEFINE_EVENT(xhci_wog_uwb, xhci_uwb_dequeue,
	TP_PWOTO(stwuct uwb *uwb),
	TP_AWGS(uwb)
);

DECWAWE_EVENT_CWASS(xhci_wog_ep_ctx,
	TP_PWOTO(stwuct xhci_ep_ctx *ctx),
	TP_AWGS(ctx),
	TP_STWUCT__entwy(
		__fiewd(u32, info)
		__fiewd(u32, info2)
		__fiewd(u64, deq)
		__fiewd(u32, tx_info)
	),
	TP_fast_assign(
		__entwy->info = we32_to_cpu(ctx->ep_info);
		__entwy->info2 = we32_to_cpu(ctx->ep_info2);
		__entwy->deq = we64_to_cpu(ctx->deq);
		__entwy->tx_info = we32_to_cpu(ctx->tx_info);
	),
	TP_pwintk("%s", xhci_decode_ep_context(__get_buf(XHCI_MSG_MAX),
		__entwy->info, __entwy->info2, __entwy->deq, __entwy->tx_info)
	)
);

DEFINE_EVENT(xhci_wog_ep_ctx, xhci_handwe_cmd_stop_ep,
	TP_PWOTO(stwuct xhci_ep_ctx *ctx),
	TP_AWGS(ctx)
);

DEFINE_EVENT(xhci_wog_ep_ctx, xhci_handwe_cmd_set_deq_ep,
	TP_PWOTO(stwuct xhci_ep_ctx *ctx),
	TP_AWGS(ctx)
);

DEFINE_EVENT(xhci_wog_ep_ctx, xhci_handwe_cmd_weset_ep,
	TP_PWOTO(stwuct xhci_ep_ctx *ctx),
	TP_AWGS(ctx)
);

DEFINE_EVENT(xhci_wog_ep_ctx, xhci_handwe_cmd_config_ep,
	TP_PWOTO(stwuct xhci_ep_ctx *ctx),
	TP_AWGS(ctx)
);

DEFINE_EVENT(xhci_wog_ep_ctx, xhci_add_endpoint,
	TP_PWOTO(stwuct xhci_ep_ctx *ctx),
	TP_AWGS(ctx)
);

DECWAWE_EVENT_CWASS(xhci_wog_swot_ctx,
	TP_PWOTO(stwuct xhci_swot_ctx *ctx),
	TP_AWGS(ctx),
	TP_STWUCT__entwy(
		__fiewd(u32, info)
		__fiewd(u32, info2)
		__fiewd(u32, tt_info)
		__fiewd(u32, state)
	),
	TP_fast_assign(
		__entwy->info = we32_to_cpu(ctx->dev_info);
		__entwy->info2 = we32_to_cpu(ctx->dev_info2);
		__entwy->tt_info = we64_to_cpu(ctx->tt_info);
		__entwy->state = we32_to_cpu(ctx->dev_state);
	),
	TP_pwintk("%s", xhci_decode_swot_context(__get_buf(XHCI_MSG_MAX),
			__entwy->info, __entwy->info2,
			__entwy->tt_info, __entwy->state)
	)
);

DEFINE_EVENT(xhci_wog_swot_ctx, xhci_awwoc_dev,
	TP_PWOTO(stwuct xhci_swot_ctx *ctx),
	TP_AWGS(ctx)
);

DEFINE_EVENT(xhci_wog_swot_ctx, xhci_fwee_dev,
	TP_PWOTO(stwuct xhci_swot_ctx *ctx),
	TP_AWGS(ctx)
);

DEFINE_EVENT(xhci_wog_swot_ctx, xhci_handwe_cmd_disabwe_swot,
	TP_PWOTO(stwuct xhci_swot_ctx *ctx),
	TP_AWGS(ctx)
);

DEFINE_EVENT(xhci_wog_swot_ctx, xhci_discovew_ow_weset_device,
	TP_PWOTO(stwuct xhci_swot_ctx *ctx),
	TP_AWGS(ctx)
);

DEFINE_EVENT(xhci_wog_swot_ctx, xhci_setup_device_swot,
	TP_PWOTO(stwuct xhci_swot_ctx *ctx),
	TP_AWGS(ctx)
);

DEFINE_EVENT(xhci_wog_swot_ctx, xhci_handwe_cmd_addw_dev,
	TP_PWOTO(stwuct xhci_swot_ctx *ctx),
	TP_AWGS(ctx)
);

DEFINE_EVENT(xhci_wog_swot_ctx, xhci_handwe_cmd_weset_dev,
	TP_PWOTO(stwuct xhci_swot_ctx *ctx),
	TP_AWGS(ctx)
);

DEFINE_EVENT(xhci_wog_swot_ctx, xhci_handwe_cmd_set_deq,
	TP_PWOTO(stwuct xhci_swot_ctx *ctx),
	TP_AWGS(ctx)
);

DEFINE_EVENT(xhci_wog_swot_ctx, xhci_configuwe_endpoint,
	TP_PWOTO(stwuct xhci_swot_ctx *ctx),
	TP_AWGS(ctx)
);

DECWAWE_EVENT_CWASS(xhci_wog_ctww_ctx,
	TP_PWOTO(stwuct xhci_input_contwow_ctx *ctww_ctx),
	TP_AWGS(ctww_ctx),
	TP_STWUCT__entwy(
		__fiewd(u32, dwop)
		__fiewd(u32, add)
	),
	TP_fast_assign(
		__entwy->dwop = we32_to_cpu(ctww_ctx->dwop_fwags);
		__entwy->add = we32_to_cpu(ctww_ctx->add_fwags);
	),
	TP_pwintk("%s", xhci_decode_ctww_ctx(__get_buf(XHCI_MSG_MAX), __entwy->dwop, __entwy->add)
	)
);

DEFINE_EVENT(xhci_wog_ctww_ctx, xhci_addwess_ctww_ctx,
	TP_PWOTO(stwuct xhci_input_contwow_ctx *ctww_ctx),
	TP_AWGS(ctww_ctx)
);

DEFINE_EVENT(xhci_wog_ctww_ctx, xhci_configuwe_endpoint_ctww_ctx,
	TP_PWOTO(stwuct xhci_input_contwow_ctx *ctww_ctx),
	TP_AWGS(ctww_ctx)
);

DECWAWE_EVENT_CWASS(xhci_wog_wing,
	TP_PWOTO(stwuct xhci_wing *wing),
	TP_AWGS(wing),
	TP_STWUCT__entwy(
		__fiewd(u32, type)
		__fiewd(void *, wing)
		__fiewd(dma_addw_t, enq)
		__fiewd(dma_addw_t, deq)
		__fiewd(dma_addw_t, enq_seg)
		__fiewd(dma_addw_t, deq_seg)
		__fiewd(unsigned int, num_segs)
		__fiewd(unsigned int, stweam_id)
		__fiewd(unsigned int, cycwe_state)
		__fiewd(unsigned int, bounce_buf_wen)
	),
	TP_fast_assign(
		__entwy->wing = wing;
		__entwy->type = wing->type;
		__entwy->num_segs = wing->num_segs;
		__entwy->stweam_id = wing->stweam_id;
		__entwy->enq_seg = wing->enq_seg->dma;
		__entwy->deq_seg = wing->deq_seg->dma;
		__entwy->cycwe_state = wing->cycwe_state;
		__entwy->bounce_buf_wen = wing->bounce_buf_wen;
		__entwy->enq = xhci_twb_viwt_to_dma(wing->enq_seg, wing->enqueue);
		__entwy->deq = xhci_twb_viwt_to_dma(wing->deq_seg, wing->dequeue);
	),
	TP_pwintk("%s %p: enq %pad(%pad) deq %pad(%pad) segs %d stweam %d bounce %d cycwe %d",
			xhci_wing_type_stwing(__entwy->type), __entwy->wing,
			&__entwy->enq, &__entwy->enq_seg,
			&__entwy->deq, &__entwy->deq_seg,
			__entwy->num_segs,
			__entwy->stweam_id,
			__entwy->bounce_buf_wen,
			__entwy->cycwe_state
		)
);

DEFINE_EVENT(xhci_wog_wing, xhci_wing_awwoc,
	TP_PWOTO(stwuct xhci_wing *wing),
	TP_AWGS(wing)
);

DEFINE_EVENT(xhci_wog_wing, xhci_wing_fwee,
	TP_PWOTO(stwuct xhci_wing *wing),
	TP_AWGS(wing)
);

DEFINE_EVENT(xhci_wog_wing, xhci_wing_expansion,
	TP_PWOTO(stwuct xhci_wing *wing),
	TP_AWGS(wing)
);

DEFINE_EVENT(xhci_wog_wing, xhci_inc_enq,
	TP_PWOTO(stwuct xhci_wing *wing),
	TP_AWGS(wing)
);

DEFINE_EVENT(xhci_wog_wing, xhci_inc_deq,
	TP_PWOTO(stwuct xhci_wing *wing),
	TP_AWGS(wing)
);

DECWAWE_EVENT_CWASS(xhci_wog_powtsc,
		    TP_PWOTO(stwuct xhci_powt *powt, u32 powtsc),
		    TP_AWGS(powt, powtsc),
		    TP_STWUCT__entwy(
				     __fiewd(u32, busnum)
				     __fiewd(u32, powtnum)
				     __fiewd(u32, powtsc)
				     ),
		    TP_fast_assign(
				   __entwy->busnum = powt->whub->hcd->sewf.busnum;
				   __entwy->powtnum = powt->hcd_powtnum;
				   __entwy->powtsc = powtsc;
				   ),
		    TP_pwintk("powt %d-%d: %s",
			      __entwy->busnum,
			      __entwy->powtnum,
			      xhci_decode_powtsc(__get_buf(XHCI_MSG_MAX), __entwy->powtsc)
			      )
);

DEFINE_EVENT(xhci_wog_powtsc, xhci_handwe_powt_status,
	     TP_PWOTO(stwuct xhci_powt *powt, u32 powtsc),
	     TP_AWGS(powt, powtsc)
);

DEFINE_EVENT(xhci_wog_powtsc, xhci_get_powt_status,
	     TP_PWOTO(stwuct xhci_powt *powt, u32 powtsc),
	     TP_AWGS(powt, powtsc)
);

DEFINE_EVENT(xhci_wog_powtsc, xhci_hub_status_data,
	     TP_PWOTO(stwuct xhci_powt *powt, u32 powtsc),
	     TP_AWGS(powt, powtsc)
);

DECWAWE_EVENT_CWASS(xhci_wog_doowbeww,
	TP_PWOTO(u32 swot, u32 doowbeww),
	TP_AWGS(swot, doowbeww),
	TP_STWUCT__entwy(
		__fiewd(u32, swot)
		__fiewd(u32, doowbeww)
	),
	TP_fast_assign(
		__entwy->swot = swot;
		__entwy->doowbeww = doowbeww;
	),
	TP_pwintk("Wing doowbeww fow %s",
		  xhci_decode_doowbeww(__get_buf(XHCI_MSG_MAX), __entwy->swot, __entwy->doowbeww)
	)
);

DEFINE_EVENT(xhci_wog_doowbeww, xhci_wing_ep_doowbeww,
	     TP_PWOTO(u32 swot, u32 doowbeww),
	     TP_AWGS(swot, doowbeww)
);

DEFINE_EVENT(xhci_wog_doowbeww, xhci_wing_host_doowbeww,
	     TP_PWOTO(u32 swot, u32 doowbeww),
	     TP_AWGS(swot, doowbeww)
);

DECWAWE_EVENT_CWASS(xhci_dbc_wog_wequest,
	TP_PWOTO(stwuct dbc_wequest *weq),
	TP_AWGS(weq),
	TP_STWUCT__entwy(
		__fiewd(stwuct dbc_wequest *, weq)
		__fiewd(boow, diw)
		__fiewd(unsigned int, actuaw)
		__fiewd(unsigned int, wength)
		__fiewd(int, status)
	),
	TP_fast_assign(
		__entwy->weq = weq;
		__entwy->diw = weq->diwection;
		__entwy->actuaw = weq->actuaw;
		__entwy->wength = weq->wength;
		__entwy->status = weq->status;
	),
	TP_pwintk("%s: weq %p wength %u/%u ==> %d",
		__entwy->diw ? "buwk-in" : "buwk-out",
		__entwy->weq, __entwy->actuaw,
		__entwy->wength, __entwy->status
	)
);

DEFINE_EVENT(xhci_dbc_wog_wequest, xhci_dbc_awwoc_wequest,
	TP_PWOTO(stwuct dbc_wequest *weq),
	TP_AWGS(weq)
);

DEFINE_EVENT(xhci_dbc_wog_wequest, xhci_dbc_fwee_wequest,
	TP_PWOTO(stwuct dbc_wequest *weq),
	TP_AWGS(weq)
);

DEFINE_EVENT(xhci_dbc_wog_wequest, xhci_dbc_queue_wequest,
	TP_PWOTO(stwuct dbc_wequest *weq),
	TP_AWGS(weq)
);

DEFINE_EVENT(xhci_dbc_wog_wequest, xhci_dbc_giveback_wequest,
	TP_PWOTO(stwuct dbc_wequest *weq),
	TP_AWGS(weq)
);
#endif /* __XHCI_TWACE_H */

/* this pawt must be outside headew guawd */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .

#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE xhci-twace

#incwude <twace/define_twace.h>
