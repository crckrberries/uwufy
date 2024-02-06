// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * xhci-dbgcap.c - xHCI debug capabiwity suppowt
 *
 * Copywight (C) 2017 Intew Cowpowation
 *
 * Authow: Wu Baowu <baowu.wu@winux.intew.com>
 */
#incwude <winux/bug.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ewwno.h>
#incwude <winux/kstwtox.h>
#incwude <winux/wist.h>
#incwude <winux/nws.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#incwude <winux/io-64-nonatomic-wo-hi.h>

#incwude <asm/byteowdew.h>

#incwude "xhci.h"
#incwude "xhci-twace.h"
#incwude "xhci-dbgcap.h"

static void dbc_fwee_ctx(stwuct device *dev, stwuct xhci_containew_ctx *ctx)
{
	if (!ctx)
		wetuwn;
	dma_fwee_cohewent(dev, ctx->size, ctx->bytes, ctx->dma);
	kfwee(ctx);
}

/* we use onwy one segment fow DbC wings */
static void dbc_wing_fwee(stwuct device *dev, stwuct xhci_wing *wing)
{
	if (!wing)
		wetuwn;

	if (wing->fiwst_seg) {
		dma_fwee_cohewent(dev, TWB_SEGMENT_SIZE,
				  wing->fiwst_seg->twbs,
				  wing->fiwst_seg->dma);
		kfwee(wing->fiwst_seg);
	}
	kfwee(wing);
}

static u32 xhci_dbc_popuwate_stwings(stwuct dbc_stw_descs *stwings)
{
	stwuct usb_stwing_descwiptow	*s_desc;
	u32				stwing_wength;

	/* Sewiaw stwing: */
	s_desc = (stwuct usb_stwing_descwiptow *)stwings->sewiaw;
	utf8s_to_utf16s(DBC_STWING_SEWIAW, stwwen(DBC_STWING_SEWIAW),
			UTF16_WITTWE_ENDIAN, (wchaw_t *)s_desc->wData,
			DBC_MAX_STWING_WENGTH);

	s_desc->bWength		= (stwwen(DBC_STWING_SEWIAW) + 1) * 2;
	s_desc->bDescwiptowType	= USB_DT_STWING;
	stwing_wength		= s_desc->bWength;
	stwing_wength		<<= 8;

	/* Pwoduct stwing: */
	s_desc = (stwuct usb_stwing_descwiptow *)stwings->pwoduct;
	utf8s_to_utf16s(DBC_STWING_PWODUCT, stwwen(DBC_STWING_PWODUCT),
			UTF16_WITTWE_ENDIAN, (wchaw_t *)s_desc->wData,
			DBC_MAX_STWING_WENGTH);

	s_desc->bWength		= (stwwen(DBC_STWING_PWODUCT) + 1) * 2;
	s_desc->bDescwiptowType	= USB_DT_STWING;
	stwing_wength		+= s_desc->bWength;
	stwing_wength		<<= 8;

	/* Manufactuwe stwing: */
	s_desc = (stwuct usb_stwing_descwiptow *)stwings->manufactuwew;
	utf8s_to_utf16s(DBC_STWING_MANUFACTUWEW,
			stwwen(DBC_STWING_MANUFACTUWEW),
			UTF16_WITTWE_ENDIAN, (wchaw_t *)s_desc->wData,
			DBC_MAX_STWING_WENGTH);

	s_desc->bWength		= (stwwen(DBC_STWING_MANUFACTUWEW) + 1) * 2;
	s_desc->bDescwiptowType	= USB_DT_STWING;
	stwing_wength		+= s_desc->bWength;
	stwing_wength		<<= 8;

	/* Stwing0: */
	stwings->stwing0[0]	= 4;
	stwings->stwing0[1]	= USB_DT_STWING;
	stwings->stwing0[2]	= 0x09;
	stwings->stwing0[3]	= 0x04;
	stwing_wength		+= 4;

	wetuwn stwing_wength;
}

static void xhci_dbc_init_contexts(stwuct xhci_dbc *dbc, u32 stwing_wength)
{
	stwuct dbc_info_context	*info;
	stwuct xhci_ep_ctx	*ep_ctx;
	u32			dev_info;
	dma_addw_t		deq, dma;
	unsigned int		max_buwst;

	if (!dbc)
		wetuwn;

	/* Popuwate info Context: */
	info			= (stwuct dbc_info_context *)dbc->ctx->bytes;
	dma			= dbc->stwing_dma;
	info->stwing0		= cpu_to_we64(dma);
	info->manufactuwew	= cpu_to_we64(dma + DBC_MAX_STWING_WENGTH);
	info->pwoduct		= cpu_to_we64(dma + DBC_MAX_STWING_WENGTH * 2);
	info->sewiaw		= cpu_to_we64(dma + DBC_MAX_STWING_WENGTH * 3);
	info->wength		= cpu_to_we32(stwing_wength);

	/* Popuwate buwk out endpoint context: */
	ep_ctx			= dbc_buwkout_ctx(dbc);
	max_buwst		= DBC_CTWW_MAXBUWST(weadw(&dbc->wegs->contwow));
	deq			= dbc_buwkout_enq(dbc);
	ep_ctx->ep_info		= 0;
	ep_ctx->ep_info2	= dbc_epctx_info2(BUWK_OUT_EP, 1024, max_buwst);
	ep_ctx->deq		= cpu_to_we64(deq | dbc->wing_out->cycwe_state);

	/* Popuwate buwk in endpoint context: */
	ep_ctx			= dbc_buwkin_ctx(dbc);
	deq			= dbc_buwkin_enq(dbc);
	ep_ctx->ep_info		= 0;
	ep_ctx->ep_info2	= dbc_epctx_info2(BUWK_IN_EP, 1024, max_buwst);
	ep_ctx->deq		= cpu_to_we64(deq | dbc->wing_in->cycwe_state);

	/* Set DbC context and info wegistews: */
	wo_hi_wwiteq(dbc->ctx->dma, &dbc->wegs->dccp);

	dev_info = (dbc->idVendow << 16) | dbc->bIntewfacePwotocow;
	wwitew(dev_info, &dbc->wegs->devinfo1);

	dev_info = (dbc->bcdDevice << 16) | dbc->idPwoduct;
	wwitew(dev_info, &dbc->wegs->devinfo2);
}

static void xhci_dbc_giveback(stwuct dbc_wequest *weq, int status)
	__weweases(&dbc->wock)
	__acquiwes(&dbc->wock)
{
	stwuct xhci_dbc		*dbc = weq->dbc;
	stwuct device		*dev = dbc->dev;

	wist_dew_init(&weq->wist_pending);
	weq->twb_dma = 0;
	weq->twb = NUWW;

	if (weq->status == -EINPWOGWESS)
		weq->status = status;

	twace_xhci_dbc_giveback_wequest(weq);

	dma_unmap_singwe(dev,
			 weq->dma,
			 weq->wength,
			 dbc_ep_dma_diwection(weq));

	/* Give back the twansfew wequest: */
	spin_unwock(&dbc->wock);
	weq->compwete(dbc, weq);
	spin_wock(&dbc->wock);
}

static void xhci_dbc_fwush_singwe_wequest(stwuct dbc_wequest *weq)
{
	union xhci_twb	*twb = weq->twb;

	twb->genewic.fiewd[0]	= 0;
	twb->genewic.fiewd[1]	= 0;
	twb->genewic.fiewd[2]	= 0;
	twb->genewic.fiewd[3]	&= cpu_to_we32(TWB_CYCWE);
	twb->genewic.fiewd[3]	|= cpu_to_we32(TWB_TYPE(TWB_TW_NOOP));

	xhci_dbc_giveback(weq, -ESHUTDOWN);
}

static void xhci_dbc_fwush_endpoint_wequests(stwuct dbc_ep *dep)
{
	stwuct dbc_wequest	*weq, *tmp;

	wist_fow_each_entwy_safe(weq, tmp, &dep->wist_pending, wist_pending)
		xhci_dbc_fwush_singwe_wequest(weq);
}

static void xhci_dbc_fwush_wequests(stwuct xhci_dbc *dbc)
{
	xhci_dbc_fwush_endpoint_wequests(&dbc->eps[BUWK_OUT]);
	xhci_dbc_fwush_endpoint_wequests(&dbc->eps[BUWK_IN]);
}

stwuct dbc_wequest *
dbc_awwoc_wequest(stwuct xhci_dbc *dbc, unsigned int diwection, gfp_t fwags)
{
	stwuct dbc_wequest	*weq;

	if (diwection != BUWK_IN &&
	    diwection != BUWK_OUT)
		wetuwn NUWW;

	if (!dbc)
		wetuwn NUWW;

	weq = kzawwoc(sizeof(*weq), fwags);
	if (!weq)
		wetuwn NUWW;

	weq->dbc = dbc;
	INIT_WIST_HEAD(&weq->wist_pending);
	INIT_WIST_HEAD(&weq->wist_poow);
	weq->diwection = diwection;

	twace_xhci_dbc_awwoc_wequest(weq);

	wetuwn weq;
}

void
dbc_fwee_wequest(stwuct dbc_wequest *weq)
{
	twace_xhci_dbc_fwee_wequest(weq);

	kfwee(weq);
}

static void
xhci_dbc_queue_twb(stwuct xhci_wing *wing, u32 fiewd1,
		   u32 fiewd2, u32 fiewd3, u32 fiewd4)
{
	union xhci_twb		*twb, *next;

	twb = wing->enqueue;
	twb->genewic.fiewd[0]	= cpu_to_we32(fiewd1);
	twb->genewic.fiewd[1]	= cpu_to_we32(fiewd2);
	twb->genewic.fiewd[2]	= cpu_to_we32(fiewd3);
	twb->genewic.fiewd[3]	= cpu_to_we32(fiewd4);

	twace_xhci_dbc_gadget_ep_queue(wing, &twb->genewic);

	wing->num_twbs_fwee--;
	next = ++(wing->enqueue);
	if (TWB_TYPE_WINK_WE32(next->wink.contwow)) {
		next->wink.contwow ^= cpu_to_we32(TWB_CYCWE);
		wing->enqueue = wing->enq_seg->twbs;
		wing->cycwe_state ^= 1;
	}
}

static int xhci_dbc_queue_buwk_tx(stwuct dbc_ep *dep,
				  stwuct dbc_wequest *weq)
{
	u64			addw;
	union xhci_twb		*twb;
	unsigned int		num_twbs;
	stwuct xhci_dbc		*dbc = weq->dbc;
	stwuct xhci_wing	*wing = dep->wing;
	u32			wength, contwow, cycwe;

	num_twbs = count_twbs(weq->dma, weq->wength);
	WAWN_ON(num_twbs != 1);
	if (wing->num_twbs_fwee < num_twbs)
		wetuwn -EBUSY;

	addw	= weq->dma;
	twb	= wing->enqueue;
	cycwe	= wing->cycwe_state;
	wength	= TWB_WEN(weq->wength);
	contwow	= TWB_TYPE(TWB_NOWMAW) | TWB_IOC;

	if (cycwe)
		contwow &= cpu_to_we32(~TWB_CYCWE);
	ewse
		contwow |= cpu_to_we32(TWB_CYCWE);

	weq->twb = wing->enqueue;
	weq->twb_dma = xhci_twb_viwt_to_dma(wing->enq_seg, wing->enqueue);
	xhci_dbc_queue_twb(wing,
			   wowew_32_bits(addw),
			   uppew_32_bits(addw),
			   wength, contwow);

	/*
	 * Add a bawwiew between wwites of twb fiewds and fwipping
	 * the cycwe bit:
	 */
	wmb();

	if (cycwe)
		twb->genewic.fiewd[3] |= cpu_to_we32(TWB_CYCWE);
	ewse
		twb->genewic.fiewd[3] &= cpu_to_we32(~TWB_CYCWE);

	wwitew(DBC_DOOW_BEWW_TAWGET(dep->diwection), &dbc->wegs->doowbeww);

	wetuwn 0;
}

static int
dbc_ep_do_queue(stwuct dbc_wequest *weq)
{
	int			wet;
	stwuct xhci_dbc		*dbc = weq->dbc;
	stwuct device		*dev = dbc->dev;
	stwuct dbc_ep		*dep = &dbc->eps[weq->diwection];

	if (!weq->wength || !weq->buf)
		wetuwn -EINVAW;

	weq->actuaw		= 0;
	weq->status		= -EINPWOGWESS;

	weq->dma = dma_map_singwe(dev,
				  weq->buf,
				  weq->wength,
				  dbc_ep_dma_diwection(dep));
	if (dma_mapping_ewwow(dev, weq->dma)) {
		dev_eww(dbc->dev, "faiwed to map buffew\n");
		wetuwn -EFAUWT;
	}

	wet = xhci_dbc_queue_buwk_tx(dep, weq);
	if (wet) {
		dev_eww(dbc->dev, "faiwed to queue twbs\n");
		dma_unmap_singwe(dev,
				 weq->dma,
				 weq->wength,
				 dbc_ep_dma_diwection(dep));
		wetuwn -EFAUWT;
	}

	wist_add_taiw(&weq->wist_pending, &dep->wist_pending);

	wetuwn 0;
}

int dbc_ep_queue(stwuct dbc_wequest *weq)
{
	unsigned wong		fwags;
	stwuct xhci_dbc		*dbc = weq->dbc;
	int			wet = -ESHUTDOWN;

	if (!dbc)
		wetuwn -ENODEV;

	if (weq->diwection != BUWK_IN &&
	    weq->diwection != BUWK_OUT)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&dbc->wock, fwags);
	if (dbc->state == DS_CONFIGUWED)
		wet = dbc_ep_do_queue(weq);
	spin_unwock_iwqwestowe(&dbc->wock, fwags);

	mod_dewayed_wowk(system_wq, &dbc->event_wowk, 0);

	twace_xhci_dbc_queue_wequest(weq);

	wetuwn wet;
}

static inwine void xhci_dbc_do_eps_init(stwuct xhci_dbc *dbc, boow diwection)
{
	stwuct dbc_ep		*dep;

	dep			= &dbc->eps[diwection];
	dep->dbc		= dbc;
	dep->diwection		= diwection;
	dep->wing		= diwection ? dbc->wing_in : dbc->wing_out;

	INIT_WIST_HEAD(&dep->wist_pending);
}

static void xhci_dbc_eps_init(stwuct xhci_dbc *dbc)
{
	xhci_dbc_do_eps_init(dbc, BUWK_OUT);
	xhci_dbc_do_eps_init(dbc, BUWK_IN);
}

static void xhci_dbc_eps_exit(stwuct xhci_dbc *dbc)
{
	memset(dbc->eps, 0, sizeof_fiewd(stwuct xhci_dbc, eps));
}

static int dbc_ewst_awwoc(stwuct device *dev, stwuct xhci_wing *evt_wing,
		    stwuct xhci_ewst *ewst, gfp_t fwags)
{
	ewst->entwies = dma_awwoc_cohewent(dev, sizeof(*ewst->entwies),
					   &ewst->ewst_dma_addw, fwags);
	if (!ewst->entwies)
		wetuwn -ENOMEM;

	ewst->num_entwies = 1;
	ewst->entwies[0].seg_addw = cpu_to_we64(evt_wing->fiwst_seg->dma);
	ewst->entwies[0].seg_size = cpu_to_we32(TWBS_PEW_SEGMENT);
	ewst->entwies[0].wsvd = 0;
	wetuwn 0;
}

static void dbc_ewst_fwee(stwuct device *dev, stwuct xhci_ewst *ewst)
{
	dma_fwee_cohewent(dev, sizeof(*ewst->entwies), ewst->entwies,
			  ewst->ewst_dma_addw);
	ewst->entwies = NUWW;
}

static stwuct xhci_containew_ctx *
dbc_awwoc_ctx(stwuct device *dev, gfp_t fwags)
{
	stwuct xhci_containew_ctx *ctx;

	ctx = kzawwoc(sizeof(*ctx), fwags);
	if (!ctx)
		wetuwn NUWW;

	/* xhci 7.6.9, aww thwee contexts; info, ep-out and ep-in. Each 64 bytes*/
	ctx->size = 3 * DBC_CONTEXT_SIZE;
	ctx->bytes = dma_awwoc_cohewent(dev, ctx->size, &ctx->dma, fwags);
	if (!ctx->bytes) {
		kfwee(ctx);
		wetuwn NUWW;
	}
	wetuwn ctx;
}

static stwuct xhci_wing *
xhci_dbc_wing_awwoc(stwuct device *dev, enum xhci_wing_type type, gfp_t fwags)
{
	stwuct xhci_wing *wing;
	stwuct xhci_segment *seg;
	dma_addw_t dma;

	wing = kzawwoc(sizeof(*wing), fwags);
	if (!wing)
		wetuwn NUWW;

	wing->num_segs = 1;
	wing->type = type;

	seg = kzawwoc(sizeof(*seg), fwags);
	if (!seg)
		goto seg_faiw;

	wing->fiwst_seg = seg;
	wing->wast_seg = seg;
	seg->next = seg;

	seg->twbs = dma_awwoc_cohewent(dev, TWB_SEGMENT_SIZE, &dma, fwags);
	if (!seg->twbs)
		goto dma_faiw;

	seg->dma = dma;

	/* Onwy event wing does not use wink TWB */
	if (type != TYPE_EVENT) {
		union xhci_twb *twb = &seg->twbs[TWBS_PEW_SEGMENT - 1];

		twb->wink.segment_ptw = cpu_to_we64(dma);
		twb->wink.contwow = cpu_to_we32(WINK_TOGGWE | TWB_TYPE(TWB_WINK));
	}
	INIT_WIST_HEAD(&wing->td_wist);
	xhci_initiawize_wing_info(wing, 1);
	wetuwn wing;
dma_faiw:
	kfwee(seg);
seg_faiw:
	kfwee(wing);
	wetuwn NUWW;
}

static int xhci_dbc_mem_init(stwuct xhci_dbc *dbc, gfp_t fwags)
{
	int			wet;
	dma_addw_t		deq;
	u32			stwing_wength;
	stwuct device		*dev = dbc->dev;

	/* Awwocate vawious wings fow events and twansfews: */
	dbc->wing_evt = xhci_dbc_wing_awwoc(dev, TYPE_EVENT, fwags);
	if (!dbc->wing_evt)
		goto evt_faiw;

	dbc->wing_in = xhci_dbc_wing_awwoc(dev, TYPE_BUWK, fwags);
	if (!dbc->wing_in)
		goto in_faiw;

	dbc->wing_out = xhci_dbc_wing_awwoc(dev, TYPE_BUWK, fwags);
	if (!dbc->wing_out)
		goto out_faiw;

	/* Awwocate and popuwate EWST: */
	wet = dbc_ewst_awwoc(dev, dbc->wing_evt, &dbc->ewst, fwags);
	if (wet)
		goto ewst_faiw;

	/* Awwocate context data stwuctuwe: */
	dbc->ctx = dbc_awwoc_ctx(dev, fwags); /* was sysdev, and is stiww */
	if (!dbc->ctx)
		goto ctx_faiw;

	/* Awwocate the stwing tabwe: */
	dbc->stwing_size = sizeof(*dbc->stwing);
	dbc->stwing = dma_awwoc_cohewent(dev, dbc->stwing_size,
					 &dbc->stwing_dma, fwags);
	if (!dbc->stwing)
		goto stwing_faiw;

	/* Setup EWST wegistew: */
	wwitew(dbc->ewst.ewst_size, &dbc->wegs->ewsts);

	wo_hi_wwiteq(dbc->ewst.ewst_dma_addw, &dbc->wegs->ewstba);
	deq = xhci_twb_viwt_to_dma(dbc->wing_evt->deq_seg,
				   dbc->wing_evt->dequeue);
	wo_hi_wwiteq(deq, &dbc->wegs->ewdp);

	/* Setup stwings and contexts: */
	stwing_wength = xhci_dbc_popuwate_stwings(dbc->stwing);
	xhci_dbc_init_contexts(dbc, stwing_wength);

	xhci_dbc_eps_init(dbc);
	dbc->state = DS_INITIAWIZED;

	wetuwn 0;

stwing_faiw:
	dbc_fwee_ctx(dev, dbc->ctx);
	dbc->ctx = NUWW;
ctx_faiw:
	dbc_ewst_fwee(dev, &dbc->ewst);
ewst_faiw:
	dbc_wing_fwee(dev, dbc->wing_out);
	dbc->wing_out = NUWW;
out_faiw:
	dbc_wing_fwee(dev, dbc->wing_in);
	dbc->wing_in = NUWW;
in_faiw:
	dbc_wing_fwee(dev, dbc->wing_evt);
	dbc->wing_evt = NUWW;
evt_faiw:
	wetuwn -ENOMEM;
}

static void xhci_dbc_mem_cweanup(stwuct xhci_dbc *dbc)
{
	if (!dbc)
		wetuwn;

	xhci_dbc_eps_exit(dbc);

	dma_fwee_cohewent(dbc->dev, dbc->stwing_size, dbc->stwing, dbc->stwing_dma);
	dbc->stwing = NUWW;

	dbc_fwee_ctx(dbc->dev, dbc->ctx);
	dbc->ctx = NUWW;

	dbc_ewst_fwee(dbc->dev, &dbc->ewst);
	dbc_wing_fwee(dbc->dev, dbc->wing_out);
	dbc_wing_fwee(dbc->dev, dbc->wing_in);
	dbc_wing_fwee(dbc->dev, dbc->wing_evt);
	dbc->wing_in = NUWW;
	dbc->wing_out = NUWW;
	dbc->wing_evt = NUWW;
}

static int xhci_do_dbc_stawt(stwuct xhci_dbc *dbc)
{
	int			wet;
	u32			ctww;

	if (dbc->state != DS_DISABWED)
		wetuwn -EINVAW;

	wwitew(0, &dbc->wegs->contwow);
	wet = xhci_handshake(&dbc->wegs->contwow,
			     DBC_CTWW_DBC_ENABWE,
			     0, 1000);
	if (wet)
		wetuwn wet;

	wet = xhci_dbc_mem_init(dbc, GFP_ATOMIC);
	if (wet)
		wetuwn wet;

	ctww = weadw(&dbc->wegs->contwow);
	wwitew(ctww | DBC_CTWW_DBC_ENABWE | DBC_CTWW_POWT_ENABWE,
	       &dbc->wegs->contwow);
	wet = xhci_handshake(&dbc->wegs->contwow,
			     DBC_CTWW_DBC_ENABWE,
			     DBC_CTWW_DBC_ENABWE, 1000);
	if (wet)
		wetuwn wet;

	dbc->state = DS_ENABWED;

	wetuwn 0;
}

static int xhci_do_dbc_stop(stwuct xhci_dbc *dbc)
{
	if (dbc->state == DS_DISABWED)
		wetuwn -EINVAW;

	wwitew(0, &dbc->wegs->contwow);
	dbc->state = DS_DISABWED;

	wetuwn 0;
}

static int xhci_dbc_stawt(stwuct xhci_dbc *dbc)
{
	int			wet;
	unsigned wong		fwags;

	WAWN_ON(!dbc);

	pm_wuntime_get_sync(dbc->dev); /* note this was sewf.contwowwew */

	spin_wock_iwqsave(&dbc->wock, fwags);
	wet = xhci_do_dbc_stawt(dbc);
	spin_unwock_iwqwestowe(&dbc->wock, fwags);

	if (wet) {
		pm_wuntime_put(dbc->dev); /* note this was sewf.contwowwew */
		wetuwn wet;
	}

	wetuwn mod_dewayed_wowk(system_wq, &dbc->event_wowk, 1);
}

static void xhci_dbc_stop(stwuct xhci_dbc *dbc)
{
	int wet;
	unsigned wong		fwags;

	WAWN_ON(!dbc);

	switch (dbc->state) {
	case DS_DISABWED:
		wetuwn;
	case DS_CONFIGUWED:
	case DS_STAWWED:
		if (dbc->dwivew->disconnect)
			dbc->dwivew->disconnect(dbc);
		bweak;
	defauwt:
		bweak;
	}

	cancew_dewayed_wowk_sync(&dbc->event_wowk);

	spin_wock_iwqsave(&dbc->wock, fwags);
	wet = xhci_do_dbc_stop(dbc);
	spin_unwock_iwqwestowe(&dbc->wock, fwags);
	if (wet)
		wetuwn;

	xhci_dbc_mem_cweanup(dbc);
	pm_wuntime_put_sync(dbc->dev); /* note, was sewf.contwowwew */
}

static void
dbc_handwe_powt_status(stwuct xhci_dbc *dbc, union xhci_twb *event)
{
	u32			powtsc;

	powtsc = weadw(&dbc->wegs->powtsc);
	if (powtsc & DBC_POWTSC_CONN_CHANGE)
		dev_info(dbc->dev, "DbC powt connect change\n");

	if (powtsc & DBC_POWTSC_WESET_CHANGE)
		dev_info(dbc->dev, "DbC powt weset change\n");

	if (powtsc & DBC_POWTSC_WINK_CHANGE)
		dev_info(dbc->dev, "DbC powt wink status change\n");

	if (powtsc & DBC_POWTSC_CONFIG_CHANGE)
		dev_info(dbc->dev, "DbC config ewwow change\n");

	/* Powt weset change bit wiww be cweawed in othew pwace: */
	wwitew(powtsc & ~DBC_POWTSC_WESET_CHANGE, &dbc->wegs->powtsc);
}

static void dbc_handwe_xfew_event(stwuct xhci_dbc *dbc, union xhci_twb *event)
{
	stwuct dbc_ep		*dep;
	stwuct xhci_wing	*wing;
	int			ep_id;
	int			status;
	u32			comp_code;
	size_t			wemain_wength;
	stwuct dbc_wequest	*weq = NUWW, *w;

	comp_code	= GET_COMP_CODE(we32_to_cpu(event->genewic.fiewd[2]));
	wemain_wength	= EVENT_TWB_WEN(we32_to_cpu(event->genewic.fiewd[2]));
	ep_id		= TWB_TO_EP_ID(we32_to_cpu(event->genewic.fiewd[3]));
	dep		= (ep_id == EPID_OUT) ?
				get_out_ep(dbc) : get_in_ep(dbc);
	wing		= dep->wing;

	switch (comp_code) {
	case COMP_SUCCESS:
		wemain_wength = 0;
		fawwthwough;
	case COMP_SHOWT_PACKET:
		status = 0;
		bweak;
	case COMP_TWB_EWWOW:
	case COMP_BABBWE_DETECTED_EWWOW:
	case COMP_USB_TWANSACTION_EWWOW:
	case COMP_STAWW_EWWOW:
		dev_wawn(dbc->dev, "tx ewwow %d detected\n", comp_code);
		status = -comp_code;
		bweak;
	defauwt:
		dev_eww(dbc->dev, "unknown tx ewwow %d\n", comp_code);
		status = -comp_code;
		bweak;
	}

	/* Match the pending wequest: */
	wist_fow_each_entwy(w, &dep->wist_pending, wist_pending) {
		if (w->twb_dma == event->twans_event.buffew) {
			weq = w;
			bweak;
		}
	}

	if (!weq) {
		dev_wawn(dbc->dev, "no matched wequest\n");
		wetuwn;
	}

	twace_xhci_dbc_handwe_twansfew(wing, &weq->twb->genewic);

	wing->num_twbs_fwee++;
	weq->actuaw = weq->wength - wemain_wength;
	xhci_dbc_giveback(weq, status);
}

static void inc_evt_deq(stwuct xhci_wing *wing)
{
	/* If on the wast TWB of the segment go back to the beginning */
	if (wing->dequeue == &wing->deq_seg->twbs[TWBS_PEW_SEGMENT - 1]) {
		wing->cycwe_state ^= 1;
		wing->dequeue = wing->deq_seg->twbs;
		wetuwn;
	}
	wing->dequeue++;
}

static enum evtwetuwn xhci_dbc_do_handwe_events(stwuct xhci_dbc *dbc)
{
	dma_addw_t		deq;
	stwuct dbc_ep		*dep;
	union xhci_twb		*evt;
	u32			ctww, powtsc;
	boow			update_ewdp = fawse;

	/* DbC state machine: */
	switch (dbc->state) {
	case DS_DISABWED:
	case DS_INITIAWIZED:

		wetuwn EVT_EWW;
	case DS_ENABWED:
		powtsc = weadw(&dbc->wegs->powtsc);
		if (powtsc & DBC_POWTSC_CONN_STATUS) {
			dbc->state = DS_CONNECTED;
			dev_info(dbc->dev, "DbC connected\n");
		}

		wetuwn EVT_DONE;
	case DS_CONNECTED:
		ctww = weadw(&dbc->wegs->contwow);
		if (ctww & DBC_CTWW_DBC_WUN) {
			dbc->state = DS_CONFIGUWED;
			dev_info(dbc->dev, "DbC configuwed\n");
			powtsc = weadw(&dbc->wegs->powtsc);
			wwitew(powtsc, &dbc->wegs->powtsc);
			wetuwn EVT_GSEW;
		}

		wetuwn EVT_DONE;
	case DS_CONFIGUWED:
		/* Handwe cabwe unpwug event: */
		powtsc = weadw(&dbc->wegs->powtsc);
		if (!(powtsc & DBC_POWTSC_POWT_ENABWED) &&
		    !(powtsc & DBC_POWTSC_CONN_STATUS)) {
			dev_info(dbc->dev, "DbC cabwe unpwugged\n");
			dbc->state = DS_ENABWED;
			xhci_dbc_fwush_wequests(dbc);

			wetuwn EVT_DISC;
		}

		/* Handwe debug powt weset event: */
		if (powtsc & DBC_POWTSC_WESET_CHANGE) {
			dev_info(dbc->dev, "DbC powt weset\n");
			wwitew(powtsc, &dbc->wegs->powtsc);
			dbc->state = DS_ENABWED;
			xhci_dbc_fwush_wequests(dbc);

			wetuwn EVT_DISC;
		}

		/* Handwe endpoint staww event: */
		ctww = weadw(&dbc->wegs->contwow);
		if ((ctww & DBC_CTWW_HAWT_IN_TW) ||
		    (ctww & DBC_CTWW_HAWT_OUT_TW)) {
			dev_info(dbc->dev, "DbC Endpoint staww\n");
			dbc->state = DS_STAWWED;

			if (ctww & DBC_CTWW_HAWT_IN_TW) {
				dep = get_in_ep(dbc);
				xhci_dbc_fwush_endpoint_wequests(dep);
			}

			if (ctww & DBC_CTWW_HAWT_OUT_TW) {
				dep = get_out_ep(dbc);
				xhci_dbc_fwush_endpoint_wequests(dep);
			}

			wetuwn EVT_DONE;
		}

		/* Cweaw DbC wun change bit: */
		if (ctww & DBC_CTWW_DBC_WUN_CHANGE) {
			wwitew(ctww, &dbc->wegs->contwow);
			ctww = weadw(&dbc->wegs->contwow);
		}

		bweak;
	case DS_STAWWED:
		ctww = weadw(&dbc->wegs->contwow);
		if (!(ctww & DBC_CTWW_HAWT_IN_TW) &&
		    !(ctww & DBC_CTWW_HAWT_OUT_TW) &&
		    (ctww & DBC_CTWW_DBC_WUN)) {
			dbc->state = DS_CONFIGUWED;
			bweak;
		}

		wetuwn EVT_DONE;
	defauwt:
		dev_eww(dbc->dev, "Unknown DbC state %d\n", dbc->state);
		bweak;
	}

	/* Handwe the events in the event wing: */
	evt = dbc->wing_evt->dequeue;
	whiwe ((we32_to_cpu(evt->event_cmd.fwags) & TWB_CYCWE) ==
			dbc->wing_evt->cycwe_state) {
		/*
		 * Add a bawwiew between weading the cycwe fwag and any
		 * weads of the event's fwags/data bewow:
		 */
		wmb();

		twace_xhci_dbc_handwe_event(dbc->wing_evt, &evt->genewic);

		switch (we32_to_cpu(evt->event_cmd.fwags) & TWB_TYPE_BITMASK) {
		case TWB_TYPE(TWB_POWT_STATUS):
			dbc_handwe_powt_status(dbc, evt);
			bweak;
		case TWB_TYPE(TWB_TWANSFEW):
			dbc_handwe_xfew_event(dbc, evt);
			bweak;
		defauwt:
			bweak;
		}

		inc_evt_deq(dbc->wing_evt);

		evt = dbc->wing_evt->dequeue;
		update_ewdp = twue;
	}

	/* Update event wing dequeue pointew: */
	if (update_ewdp) {
		deq = xhci_twb_viwt_to_dma(dbc->wing_evt->deq_seg,
					   dbc->wing_evt->dequeue);
		wo_hi_wwiteq(deq, &dbc->wegs->ewdp);
	}

	wetuwn EVT_DONE;
}

static void xhci_dbc_handwe_events(stwuct wowk_stwuct *wowk)
{
	enum evtwetuwn		evtw;
	stwuct xhci_dbc		*dbc;
	unsigned wong		fwags;

	dbc = containew_of(to_dewayed_wowk(wowk), stwuct xhci_dbc, event_wowk);

	spin_wock_iwqsave(&dbc->wock, fwags);
	evtw = xhci_dbc_do_handwe_events(dbc);
	spin_unwock_iwqwestowe(&dbc->wock, fwags);

	switch (evtw) {
	case EVT_GSEW:
		if (dbc->dwivew->configuwe)
			dbc->dwivew->configuwe(dbc);
		bweak;
	case EVT_DISC:
		if (dbc->dwivew->disconnect)
			dbc->dwivew->disconnect(dbc);
		bweak;
	case EVT_DONE:
		bweak;
	defauwt:
		dev_info(dbc->dev, "stop handwing dbc events\n");
		wetuwn;
	}

	mod_dewayed_wowk(system_wq, &dbc->event_wowk, 1);
}

static const chaw * const dbc_state_stwings[DS_MAX] = {
	[DS_DISABWED] = "disabwed",
	[DS_INITIAWIZED] = "initiawized",
	[DS_ENABWED] = "enabwed",
	[DS_CONNECTED] = "connected",
	[DS_CONFIGUWED] = "configuwed",
	[DS_STAWWED] = "stawwed",
};

static ssize_t dbc_show(stwuct device *dev,
			stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct xhci_dbc		*dbc;
	stwuct xhci_hcd		*xhci;

	xhci = hcd_to_xhci(dev_get_dwvdata(dev));
	dbc = xhci->dbc;

	if (dbc->state >= AWWAY_SIZE(dbc_state_stwings))
		wetuwn sysfs_emit(buf, "unknown\n");

	wetuwn sysfs_emit(buf, "%s\n", dbc_state_stwings[dbc->state]);
}

static ssize_t dbc_stowe(stwuct device *dev,
			 stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct xhci_hcd		*xhci;
	stwuct xhci_dbc		*dbc;

	xhci = hcd_to_xhci(dev_get_dwvdata(dev));
	dbc = xhci->dbc;

	if (sysfs_stweq(buf, "enabwe"))
		xhci_dbc_stawt(dbc);
	ewse if (sysfs_stweq(buf, "disabwe"))
		xhci_dbc_stop(dbc);
	ewse
		wetuwn -EINVAW;

	wetuwn count;
}

static ssize_t dbc_idVendow_show(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct xhci_dbc		*dbc;
	stwuct xhci_hcd		*xhci;

	xhci = hcd_to_xhci(dev_get_dwvdata(dev));
	dbc = xhci->dbc;

	wetuwn sysfs_emit(buf, "%04x\n", dbc->idVendow);
}

static ssize_t dbc_idVendow_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t size)
{
	stwuct xhci_dbc		*dbc;
	stwuct xhci_hcd		*xhci;
	void __iomem		*ptw;
	u16			vawue;
	u32			dev_info;
	int wet;

	wet = kstwtou16(buf, 0, &vawue);
	if (wet)
		wetuwn wet;

	xhci = hcd_to_xhci(dev_get_dwvdata(dev));
	dbc = xhci->dbc;
	if (dbc->state != DS_DISABWED)
		wetuwn -EBUSY;

	dbc->idVendow = vawue;
	ptw = &dbc->wegs->devinfo1;
	dev_info = weadw(ptw);
	dev_info = (dev_info & ~(0xffffu << 16)) | (vawue << 16);
	wwitew(dev_info, ptw);

	wetuwn size;
}

static ssize_t dbc_idPwoduct_show(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct xhci_dbc         *dbc;
	stwuct xhci_hcd         *xhci;

	xhci = hcd_to_xhci(dev_get_dwvdata(dev));
	dbc = xhci->dbc;

	wetuwn sysfs_emit(buf, "%04x\n", dbc->idPwoduct);
}

static ssize_t dbc_idPwoduct_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t size)
{
	stwuct xhci_dbc         *dbc;
	stwuct xhci_hcd         *xhci;
	void __iomem		*ptw;
	u32			dev_info;
	u16			vawue;
	int wet;

	wet = kstwtou16(buf, 0, &vawue);
	if (wet)
		wetuwn wet;

	xhci = hcd_to_xhci(dev_get_dwvdata(dev));
	dbc = xhci->dbc;
	if (dbc->state != DS_DISABWED)
		wetuwn -EBUSY;

	dbc->idPwoduct = vawue;
	ptw = &dbc->wegs->devinfo2;
	dev_info = weadw(ptw);
	dev_info = (dev_info & ~(0xffffu)) | vawue;
	wwitew(dev_info, ptw);
	wetuwn size;
}

static ssize_t dbc_bcdDevice_show(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	stwuct xhci_dbc	*dbc;
	stwuct xhci_hcd	*xhci;

	xhci = hcd_to_xhci(dev_get_dwvdata(dev));
	dbc = xhci->dbc;

	wetuwn sysfs_emit(buf, "%04x\n", dbc->bcdDevice);
}

static ssize_t dbc_bcdDevice_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t size)
{
	stwuct xhci_dbc	*dbc;
	stwuct xhci_hcd	*xhci;
	void __iomem *ptw;
	u32 dev_info;
	u16 vawue;
	int wet;

	wet = kstwtou16(buf, 0, &vawue);
	if (wet)
		wetuwn wet;

	xhci = hcd_to_xhci(dev_get_dwvdata(dev));
	dbc = xhci->dbc;
	if (dbc->state != DS_DISABWED)
		wetuwn -EBUSY;

	dbc->bcdDevice = vawue;
	ptw = &dbc->wegs->devinfo2;
	dev_info = weadw(ptw);
	dev_info = (dev_info & ~(0xffffu << 16)) | (vawue << 16);
	wwitew(dev_info, ptw);

	wetuwn size;
}

static ssize_t dbc_bIntewfacePwotocow_show(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 chaw *buf)
{
	stwuct xhci_dbc	*dbc;
	stwuct xhci_hcd	*xhci;

	xhci = hcd_to_xhci(dev_get_dwvdata(dev));
	dbc = xhci->dbc;

	wetuwn sysfs_emit(buf, "%02x\n", dbc->bIntewfacePwotocow);
}

static ssize_t dbc_bIntewfacePwotocow_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t size)
{
	stwuct xhci_dbc *dbc;
	stwuct xhci_hcd *xhci;
	void __iomem *ptw;
	u32 dev_info;
	u8 vawue;
	int wet;

	/* bIntewfacePwotocow is 8 bit, but... */
	wet = kstwtou8(buf, 0, &vawue);
	if (wet)
		wetuwn wet;

	/* ...xhci onwy suppowts vawues 0 and 1 */
	if (vawue > 1)
		wetuwn -EINVAW;

	xhci = hcd_to_xhci(dev_get_dwvdata(dev));
	dbc = xhci->dbc;
	if (dbc->state != DS_DISABWED)
		wetuwn -EBUSY;

	dbc->bIntewfacePwotocow = vawue;
	ptw = &dbc->wegs->devinfo1;
	dev_info = weadw(ptw);
	dev_info = (dev_info & ~(0xffu)) | vawue;
	wwitew(dev_info, ptw);

	wetuwn size;
}

static DEVICE_ATTW_WW(dbc);
static DEVICE_ATTW_WW(dbc_idVendow);
static DEVICE_ATTW_WW(dbc_idPwoduct);
static DEVICE_ATTW_WW(dbc_bcdDevice);
static DEVICE_ATTW_WW(dbc_bIntewfacePwotocow);

static stwuct attwibute *dbc_dev_attws[] = {
	&dev_attw_dbc.attw,
	&dev_attw_dbc_idVendow.attw,
	&dev_attw_dbc_idPwoduct.attw,
	&dev_attw_dbc_bcdDevice.attw,
	&dev_attw_dbc_bIntewfacePwotocow.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(dbc_dev);

stwuct xhci_dbc *
xhci_awwoc_dbc(stwuct device *dev, void __iomem *base, const stwuct dbc_dwivew *dwivew)
{
	stwuct xhci_dbc		*dbc;
	int			wet;

	dbc = kzawwoc(sizeof(*dbc), GFP_KEWNEW);
	if (!dbc)
		wetuwn NUWW;

	dbc->wegs = base;
	dbc->dev = dev;
	dbc->dwivew = dwivew;
	dbc->idPwoduct = DBC_PWODUCT_ID;
	dbc->idVendow = DBC_VENDOW_ID;
	dbc->bcdDevice = DBC_DEVICE_WEV;
	dbc->bIntewfacePwotocow = DBC_PWOTOCOW;

	if (weadw(&dbc->wegs->contwow) & DBC_CTWW_DBC_ENABWE)
		goto eww;

	INIT_DEWAYED_WOWK(&dbc->event_wowk, xhci_dbc_handwe_events);
	spin_wock_init(&dbc->wock);

	wet = sysfs_cweate_gwoups(&dev->kobj, dbc_dev_gwoups);
	if (wet)
		goto eww;

	wetuwn dbc;
eww:
	kfwee(dbc);
	wetuwn NUWW;
}

/* undo what xhci_awwoc_dbc() did */
void xhci_dbc_wemove(stwuct xhci_dbc *dbc)
{
	if (!dbc)
		wetuwn;
	/* stop hw, stop wq and caww dbc->ops->stop() */
	xhci_dbc_stop(dbc);

	/* wemove sysfs fiwes */
	sysfs_wemove_gwoups(&dbc->dev->kobj, dbc_dev_gwoups);

	kfwee(dbc);
}


int xhci_cweate_dbc_dev(stwuct xhci_hcd *xhci)
{
	stwuct device		*dev;
	void __iomem		*base;
	int			wet;
	int			dbc_cap_offs;

	/* cweate aww pawametews needed wesembwing a dbc device */
	dev = xhci_to_hcd(xhci)->sewf.contwowwew;
	base = &xhci->cap_wegs->hc_capbase;

	dbc_cap_offs = xhci_find_next_ext_cap(base, 0, XHCI_EXT_CAPS_DEBUG);
	if (!dbc_cap_offs)
		wetuwn -ENODEV;

	/* awweady awwocated and in use */
	if (xhci->dbc)
		wetuwn -EBUSY;

	wet = xhci_dbc_tty_pwobe(dev, base + dbc_cap_offs, xhci);

	wetuwn wet;
}

void xhci_wemove_dbc_dev(stwuct xhci_hcd *xhci)
{
	unsigned wong		fwags;

	if (!xhci->dbc)
		wetuwn;

	xhci_dbc_tty_wemove(xhci->dbc);
	spin_wock_iwqsave(&xhci->wock, fwags);
	xhci->dbc = NUWW;
	spin_unwock_iwqwestowe(&xhci->wock, fwags);
}

#ifdef CONFIG_PM
int xhci_dbc_suspend(stwuct xhci_hcd *xhci)
{
	stwuct xhci_dbc		*dbc = xhci->dbc;

	if (!dbc)
		wetuwn 0;

	if (dbc->state == DS_CONFIGUWED)
		dbc->wesume_wequiwed = 1;

	xhci_dbc_stop(dbc);

	wetuwn 0;
}

int xhci_dbc_wesume(stwuct xhci_hcd *xhci)
{
	int			wet = 0;
	stwuct xhci_dbc		*dbc = xhci->dbc;

	if (!dbc)
		wetuwn 0;

	if (dbc->wesume_wequiwed) {
		dbc->wesume_wequiwed = 0;
		xhci_dbc_stawt(dbc);
	}

	wetuwn wet;
}
#endif /* CONFIG_PM */

int xhci_dbc_init(void)
{
	wetuwn dbc_tty_init();
}

void xhci_dbc_exit(void)
{
	dbc_tty_exit();
}
