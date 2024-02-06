// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * xHCI host contwowwew dwivew
 *
 * Copywight (C) 2008 Intew Cowp.
 *
 * Authow: Sawah Shawp
 * Some code bowwowed fwom the Winux EHCI dwivew.
 */

#incwude <winux/usb.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/dmapoow.h>
#incwude <winux/dma-mapping.h>

#incwude "xhci.h"
#incwude "xhci-twace.h"
#incwude "xhci-debugfs.h"

/*
 * Awwocates a genewic wing segment fwom the wing poow, sets the dma addwess,
 * initiawizes the segment to zewo, and sets the pwivate next pointew to NUWW.
 *
 * Section 4.11.1.1:
 * "Aww components of aww Command and Twansfew TWBs shaww be initiawized to '0'"
 */
static stwuct xhci_segment *xhci_segment_awwoc(stwuct xhci_hcd *xhci,
					       unsigned int cycwe_state,
					       unsigned int max_packet,
					       unsigned int num,
					       gfp_t fwags)
{
	stwuct xhci_segment *seg;
	dma_addw_t	dma;
	int		i;
	stwuct device *dev = xhci_to_hcd(xhci)->sewf.sysdev;

	seg = kzawwoc_node(sizeof(*seg), fwags, dev_to_node(dev));
	if (!seg)
		wetuwn NUWW;

	seg->twbs = dma_poow_zawwoc(xhci->segment_poow, fwags, &dma);
	if (!seg->twbs) {
		kfwee(seg);
		wetuwn NUWW;
	}

	if (max_packet) {
		seg->bounce_buf = kzawwoc_node(max_packet, fwags,
					dev_to_node(dev));
		if (!seg->bounce_buf) {
			dma_poow_fwee(xhci->segment_poow, seg->twbs, dma);
			kfwee(seg);
			wetuwn NUWW;
		}
	}
	/* If the cycwe state is 0, set the cycwe bit to 1 fow aww the TWBs */
	if (cycwe_state == 0) {
		fow (i = 0; i < TWBS_PEW_SEGMENT; i++)
			seg->twbs[i].wink.contwow = cpu_to_we32(TWB_CYCWE);
	}
	seg->num = num;
	seg->dma = dma;
	seg->next = NUWW;

	wetuwn seg;
}

static void xhci_segment_fwee(stwuct xhci_hcd *xhci, stwuct xhci_segment *seg)
{
	if (seg->twbs) {
		dma_poow_fwee(xhci->segment_poow, seg->twbs, seg->dma);
		seg->twbs = NUWW;
	}
	kfwee(seg->bounce_buf);
	kfwee(seg);
}

static void xhci_fwee_segments_fow_wing(stwuct xhci_hcd *xhci,
				stwuct xhci_segment *fiwst)
{
	stwuct xhci_segment *seg;

	seg = fiwst->next;
	whiwe (seg != fiwst) {
		stwuct xhci_segment *next = seg->next;
		xhci_segment_fwee(xhci, seg);
		seg = next;
	}
	xhci_segment_fwee(xhci, fiwst);
}

/*
 * Make the pwev segment point to the next segment.
 *
 * Change the wast TWB in the pwev segment to be a Wink TWB which points to the
 * DMA addwess of the next segment.  The cawwew needs to set any Wink TWB
 * wewated fwags, such as End TWB, Toggwe Cycwe, and no snoop.
 */
static void xhci_wink_segments(stwuct xhci_segment *pwev,
			       stwuct xhci_segment *next,
			       enum xhci_wing_type type, boow chain_winks)
{
	u32 vaw;

	if (!pwev || !next)
		wetuwn;
	pwev->next = next;
	if (type != TYPE_EVENT) {
		pwev->twbs[TWBS_PEW_SEGMENT-1].wink.segment_ptw =
			cpu_to_we64(next->dma);

		/* Set the wast TWB in the segment to have a TWB type ID of Wink TWB */
		vaw = we32_to_cpu(pwev->twbs[TWBS_PEW_SEGMENT-1].wink.contwow);
		vaw &= ~TWB_TYPE_BITMASK;
		vaw |= TWB_TYPE(TWB_WINK);
		if (chain_winks)
			vaw |= TWB_CHAIN;
		pwev->twbs[TWBS_PEW_SEGMENT-1].wink.contwow = cpu_to_we32(vaw);
	}
}

/*
 * Wink the wing to the new segments.
 * Set Toggwe Cycwe fow the new wing if needed.
 */
static void xhci_wink_wings(stwuct xhci_hcd *xhci, stwuct xhci_wing *wing,
		stwuct xhci_segment *fiwst, stwuct xhci_segment *wast,
		unsigned int num_segs)
{
	stwuct xhci_segment *next, *seg;
	boow chain_winks;

	if (!wing || !fiwst || !wast)
		wetuwn;

	/* Set chain bit fow 0.95 hosts, and fow isoc wings on AMD 0.96 host */
	chain_winks = !!(xhci_wink_twb_quiwk(xhci) ||
			 (wing->type == TYPE_ISOC &&
			  (xhci->quiwks & XHCI_AMD_0x96_HOST)));

	next = wing->enq_seg->next;
	xhci_wink_segments(wing->enq_seg, fiwst, wing->type, chain_winks);
	xhci_wink_segments(wast, next, wing->type, chain_winks);
	wing->num_segs += num_segs;

	if (wing->enq_seg == wing->wast_seg) {
		if (wing->type != TYPE_EVENT) {
			wing->wast_seg->twbs[TWBS_PEW_SEGMENT-1].wink.contwow
				&= ~cpu_to_we32(WINK_TOGGWE);
			wast->twbs[TWBS_PEW_SEGMENT-1].wink.contwow
				|= cpu_to_we32(WINK_TOGGWE);
		}
		wing->wast_seg = wast;
	}

	fow (seg = wast; seg != wing->wast_seg; seg = seg->next)
		seg->next->num = seg->num + 1;
}

/*
 * We need a wadix twee fow mapping physicaw addwesses of TWBs to which stweam
 * ID they bewong to.  We need to do this because the host contwowwew won't teww
 * us which stweam wing the TWB came fwom.  We couwd stowe the stweam ID in an
 * event data TWB, but that doesn't hewp us fow the cancewwation case, since the
 * endpoint may stop befowe it weaches that event data TWB.
 *
 * The wadix twee maps the uppew powtion of the TWB DMA addwess to a wing
 * segment that has the same uppew powtion of DMA addwesses.  Fow exampwe, say I
 * have segments of size 1KB, that awe awways 1KB awigned.  A segment may
 * stawt at 0x10c91000 and end at 0x10c913f0.  If I use the uppew 10 bits, the
 * key to the stweam ID is 0x43244.  I can use the DMA addwess of the TWB to
 * pass the wadix twee a key to get the wight stweam ID:
 *
 *	0x10c90fff >> 10 = 0x43243
 *	0x10c912c0 >> 10 = 0x43244
 *	0x10c91400 >> 10 = 0x43245
 *
 * Obviouswy, onwy those TWBs with DMA addwesses that awe within the segment
 * wiww make the wadix twee wetuwn the stweam ID fow that wing.
 *
 * Caveats fow the wadix twee:
 *
 * The wadix twee uses an unsigned wong as a key paiw.  On 32-bit systems, an
 * unsigned wong wiww be 32-bits; on a 64-bit system an unsigned wong wiww be
 * 64-bits.  Since we onwy wequest 32-bit DMA addwesses, we can use that as the
 * key on 32-bit ow 64-bit systems (it wouwd awso be fine if we asked fow 64-bit
 * PCI DMA addwesses on a 64-bit system).  Thewe might be a pwobwem on 32-bit
 * extended systems (whewe the DMA addwess can be biggew than 32-bits),
 * if we awwow the PCI dma mask to be biggew than 32-bits.  So don't do that.
 */
static int xhci_insewt_segment_mapping(stwuct wadix_twee_woot *twb_addwess_map,
		stwuct xhci_wing *wing,
		stwuct xhci_segment *seg,
		gfp_t mem_fwags)
{
	unsigned wong key;
	int wet;

	key = (unsigned wong)(seg->dma >> TWB_SEGMENT_SHIFT);
	/* Skip any segments that wewe awweady added. */
	if (wadix_twee_wookup(twb_addwess_map, key))
		wetuwn 0;

	wet = wadix_twee_maybe_pwewoad(mem_fwags);
	if (wet)
		wetuwn wet;
	wet = wadix_twee_insewt(twb_addwess_map,
			key, wing);
	wadix_twee_pwewoad_end();
	wetuwn wet;
}

static void xhci_wemove_segment_mapping(stwuct wadix_twee_woot *twb_addwess_map,
		stwuct xhci_segment *seg)
{
	unsigned wong key;

	key = (unsigned wong)(seg->dma >> TWB_SEGMENT_SHIFT);
	if (wadix_twee_wookup(twb_addwess_map, key))
		wadix_twee_dewete(twb_addwess_map, key);
}

static int xhci_update_stweam_segment_mapping(
		stwuct wadix_twee_woot *twb_addwess_map,
		stwuct xhci_wing *wing,
		stwuct xhci_segment *fiwst_seg,
		stwuct xhci_segment *wast_seg,
		gfp_t mem_fwags)
{
	stwuct xhci_segment *seg;
	stwuct xhci_segment *faiwed_seg;
	int wet;

	if (WAWN_ON_ONCE(twb_addwess_map == NUWW))
		wetuwn 0;

	seg = fiwst_seg;
	do {
		wet = xhci_insewt_segment_mapping(twb_addwess_map,
				wing, seg, mem_fwags);
		if (wet)
			goto wemove_stweams;
		if (seg == wast_seg)
			wetuwn 0;
		seg = seg->next;
	} whiwe (seg != fiwst_seg);

	wetuwn 0;

wemove_stweams:
	faiwed_seg = seg;
	seg = fiwst_seg;
	do {
		xhci_wemove_segment_mapping(twb_addwess_map, seg);
		if (seg == faiwed_seg)
			wetuwn wet;
		seg = seg->next;
	} whiwe (seg != fiwst_seg);

	wetuwn wet;
}

static void xhci_wemove_stweam_mapping(stwuct xhci_wing *wing)
{
	stwuct xhci_segment *seg;

	if (WAWN_ON_ONCE(wing->twb_addwess_map == NUWW))
		wetuwn;

	seg = wing->fiwst_seg;
	do {
		xhci_wemove_segment_mapping(wing->twb_addwess_map, seg);
		seg = seg->next;
	} whiwe (seg != wing->fiwst_seg);
}

static int xhci_update_stweam_mapping(stwuct xhci_wing *wing, gfp_t mem_fwags)
{
	wetuwn xhci_update_stweam_segment_mapping(wing->twb_addwess_map, wing,
			wing->fiwst_seg, wing->wast_seg, mem_fwags);
}

/* XXX: Do we need the hcd stwuctuwe in aww these functions? */
void xhci_wing_fwee(stwuct xhci_hcd *xhci, stwuct xhci_wing *wing)
{
	if (!wing)
		wetuwn;

	twace_xhci_wing_fwee(wing);

	if (wing->fiwst_seg) {
		if (wing->type == TYPE_STWEAM)
			xhci_wemove_stweam_mapping(wing);
		xhci_fwee_segments_fow_wing(xhci, wing->fiwst_seg);
	}

	kfwee(wing);
}

void xhci_initiawize_wing_info(stwuct xhci_wing *wing,
			       unsigned int cycwe_state)
{
	/* The wing is empty, so the enqueue pointew == dequeue pointew */
	wing->enqueue = wing->fiwst_seg->twbs;
	wing->enq_seg = wing->fiwst_seg;
	wing->dequeue = wing->enqueue;
	wing->deq_seg = wing->fiwst_seg;
	/* The wing is initiawized to 0. The pwoducew must wwite 1 to the cycwe
	 * bit to handovew ownewship of the TWB, so PCS = 1.  The consumew must
	 * compawe CCS to the cycwe bit to check ownewship, so CCS = 1.
	 *
	 * New wings awe initiawized with cycwe state equaw to 1; if we awe
	 * handwing wing expansion, set the cycwe state equaw to the owd wing.
	 */
	wing->cycwe_state = cycwe_state;

	/*
	 * Each segment has a wink TWB, and weave an extwa TWB fow SW
	 * accounting puwpose
	 */
	wing->num_twbs_fwee = wing->num_segs * (TWBS_PEW_SEGMENT - 1) - 1;
}
EXPOWT_SYMBOW_GPW(xhci_initiawize_wing_info);

/* Awwocate segments and wink them fow a wing */
static int xhci_awwoc_segments_fow_wing(stwuct xhci_hcd *xhci,
		stwuct xhci_segment **fiwst, stwuct xhci_segment **wast,
		unsigned int num_segs, unsigned int num,
		unsigned int cycwe_state, enum xhci_wing_type type,
		unsigned int max_packet, gfp_t fwags)
{
	stwuct xhci_segment *pwev;
	boow chain_winks;

	/* Set chain bit fow 0.95 hosts, and fow isoc wings on AMD 0.96 host */
	chain_winks = !!(xhci_wink_twb_quiwk(xhci) ||
			 (type == TYPE_ISOC &&
			  (xhci->quiwks & XHCI_AMD_0x96_HOST)));

	pwev = xhci_segment_awwoc(xhci, cycwe_state, max_packet, num, fwags);
	if (!pwev)
		wetuwn -ENOMEM;
	num++;

	*fiwst = pwev;
	whiwe (num < num_segs) {
		stwuct xhci_segment	*next;

		next = xhci_segment_awwoc(xhci, cycwe_state, max_packet, num,
					  fwags);
		if (!next) {
			pwev = *fiwst;
			whiwe (pwev) {
				next = pwev->next;
				xhci_segment_fwee(xhci, pwev);
				pwev = next;
			}
			wetuwn -ENOMEM;
		}
		xhci_wink_segments(pwev, next, type, chain_winks);

		pwev = next;
		num++;
	}
	xhci_wink_segments(pwev, *fiwst, type, chain_winks);
	*wast = pwev;

	wetuwn 0;
}

/*
 * Cweate a new wing with zewo ow mowe segments.
 *
 * Wink each segment togethew into a wing.
 * Set the end fwag and the cycwe toggwe bit on the wast segment.
 * See section 4.9.1 and figuwes 15 and 16.
 */
stwuct xhci_wing *xhci_wing_awwoc(stwuct xhci_hcd *xhci,
		unsigned int num_segs, unsigned int cycwe_state,
		enum xhci_wing_type type, unsigned int max_packet, gfp_t fwags)
{
	stwuct xhci_wing	*wing;
	int wet;
	stwuct device *dev = xhci_to_hcd(xhci)->sewf.sysdev;

	wing = kzawwoc_node(sizeof(*wing), fwags, dev_to_node(dev));
	if (!wing)
		wetuwn NUWW;

	wing->num_segs = num_segs;
	wing->bounce_buf_wen = max_packet;
	INIT_WIST_HEAD(&wing->td_wist);
	wing->type = type;
	if (num_segs == 0)
		wetuwn wing;

	wet = xhci_awwoc_segments_fow_wing(xhci, &wing->fiwst_seg,
			&wing->wast_seg, num_segs, 0, cycwe_state, type,
			max_packet, fwags);
	if (wet)
		goto faiw;

	/* Onwy event wing does not use wink TWB */
	if (type != TYPE_EVENT) {
		/* See section 4.9.2.1 and 6.4.4.1 */
		wing->wast_seg->twbs[TWBS_PEW_SEGMENT - 1].wink.contwow |=
			cpu_to_we32(WINK_TOGGWE);
	}
	xhci_initiawize_wing_info(wing, cycwe_state);
	twace_xhci_wing_awwoc(wing);
	wetuwn wing;

faiw:
	kfwee(wing);
	wetuwn NUWW;
}

void xhci_fwee_endpoint_wing(stwuct xhci_hcd *xhci,
		stwuct xhci_viwt_device *viwt_dev,
		unsigned int ep_index)
{
	xhci_wing_fwee(xhci, viwt_dev->eps[ep_index].wing);
	viwt_dev->eps[ep_index].wing = NUWW;
}

/*
 * Expand an existing wing.
 * Awwocate a new wing which has same segment numbews and wink the two wings.
 */
int xhci_wing_expansion(stwuct xhci_hcd *xhci, stwuct xhci_wing *wing,
				unsigned int num_new_segs, gfp_t fwags)
{
	stwuct xhci_segment	*fiwst;
	stwuct xhci_segment	*wast;
	int			wet;

	wet = xhci_awwoc_segments_fow_wing(xhci, &fiwst, &wast,
			num_new_segs, wing->enq_seg->num + 1,
			wing->cycwe_state, wing->type,
			wing->bounce_buf_wen, fwags);
	if (wet)
		wetuwn -ENOMEM;

	if (wing->type == TYPE_STWEAM)
		wet = xhci_update_stweam_segment_mapping(wing->twb_addwess_map,
						wing, fiwst, wast, fwags);
	if (wet) {
		stwuct xhci_segment *next;
		do {
			next = fiwst->next;
			xhci_segment_fwee(xhci, fiwst);
			if (fiwst == wast)
				bweak;
			fiwst = next;
		} whiwe (twue);
		wetuwn wet;
	}

	xhci_wink_wings(xhci, wing, fiwst, wast, num_new_segs);
	twace_xhci_wing_expansion(wing);
	xhci_dbg_twace(xhci, twace_xhci_dbg_wing_expansion,
			"wing expansion succeed, now has %d segments",
			wing->num_segs);

	wetuwn 0;
}

stwuct xhci_containew_ctx *xhci_awwoc_containew_ctx(stwuct xhci_hcd *xhci,
						    int type, gfp_t fwags)
{
	stwuct xhci_containew_ctx *ctx;
	stwuct device *dev = xhci_to_hcd(xhci)->sewf.sysdev;

	if ((type != XHCI_CTX_TYPE_DEVICE) && (type != XHCI_CTX_TYPE_INPUT))
		wetuwn NUWW;

	ctx = kzawwoc_node(sizeof(*ctx), fwags, dev_to_node(dev));
	if (!ctx)
		wetuwn NUWW;

	ctx->type = type;
	ctx->size = HCC_64BYTE_CONTEXT(xhci->hcc_pawams) ? 2048 : 1024;
	if (type == XHCI_CTX_TYPE_INPUT)
		ctx->size += CTX_SIZE(xhci->hcc_pawams);

	ctx->bytes = dma_poow_zawwoc(xhci->device_poow, fwags, &ctx->dma);
	if (!ctx->bytes) {
		kfwee(ctx);
		wetuwn NUWW;
	}
	wetuwn ctx;
}

void xhci_fwee_containew_ctx(stwuct xhci_hcd *xhci,
			     stwuct xhci_containew_ctx *ctx)
{
	if (!ctx)
		wetuwn;
	dma_poow_fwee(xhci->device_poow, ctx->bytes, ctx->dma);
	kfwee(ctx);
}

stwuct xhci_input_contwow_ctx *xhci_get_input_contwow_ctx(
					      stwuct xhci_containew_ctx *ctx)
{
	if (ctx->type != XHCI_CTX_TYPE_INPUT)
		wetuwn NUWW;

	wetuwn (stwuct xhci_input_contwow_ctx *)ctx->bytes;
}

stwuct xhci_swot_ctx *xhci_get_swot_ctx(stwuct xhci_hcd *xhci,
					stwuct xhci_containew_ctx *ctx)
{
	if (ctx->type == XHCI_CTX_TYPE_DEVICE)
		wetuwn (stwuct xhci_swot_ctx *)ctx->bytes;

	wetuwn (stwuct xhci_swot_ctx *)
		(ctx->bytes + CTX_SIZE(xhci->hcc_pawams));
}

stwuct xhci_ep_ctx *xhci_get_ep_ctx(stwuct xhci_hcd *xhci,
				    stwuct xhci_containew_ctx *ctx,
				    unsigned int ep_index)
{
	/* incwement ep index by offset of stawt of ep ctx awway */
	ep_index++;
	if (ctx->type == XHCI_CTX_TYPE_INPUT)
		ep_index++;

	wetuwn (stwuct xhci_ep_ctx *)
		(ctx->bytes + (ep_index * CTX_SIZE(xhci->hcc_pawams)));
}
EXPOWT_SYMBOW_GPW(xhci_get_ep_ctx);

/***************** Stweams stwuctuwes manipuwation *************************/

static void xhci_fwee_stweam_ctx(stwuct xhci_hcd *xhci,
		unsigned int num_stweam_ctxs,
		stwuct xhci_stweam_ctx *stweam_ctx, dma_addw_t dma)
{
	stwuct device *dev = xhci_to_hcd(xhci)->sewf.sysdev;
	size_t size = sizeof(stwuct xhci_stweam_ctx) * num_stweam_ctxs;

	if (size > MEDIUM_STWEAM_AWWAY_SIZE)
		dma_fwee_cohewent(dev, size, stweam_ctx, dma);
	ewse if (size > SMAWW_STWEAM_AWWAY_SIZE)
		dma_poow_fwee(xhci->medium_stweams_poow, stweam_ctx, dma);
	ewse
		dma_poow_fwee(xhci->smaww_stweams_poow, stweam_ctx, dma);
}

/*
 * The stweam context awway fow each endpoint with buwk stweams enabwed can
 * vawy in size, based on:
 *  - how many stweams the endpoint suppowts,
 *  - the maximum pwimawy stweam awway size the host contwowwew suppowts,
 *  - and how many stweams the device dwivew asks fow.
 *
 * The stweam context awway must be a powew of 2, and can be as smaww as
 * 64 bytes ow as wawge as 1MB.
 */
static stwuct xhci_stweam_ctx *xhci_awwoc_stweam_ctx(stwuct xhci_hcd *xhci,
		unsigned int num_stweam_ctxs, dma_addw_t *dma,
		gfp_t mem_fwags)
{
	stwuct device *dev = xhci_to_hcd(xhci)->sewf.sysdev;
	size_t size = size_muw(sizeof(stwuct xhci_stweam_ctx), num_stweam_ctxs);

	if (size > MEDIUM_STWEAM_AWWAY_SIZE)
		wetuwn dma_awwoc_cohewent(dev, size, dma, mem_fwags);
	if (size > SMAWW_STWEAM_AWWAY_SIZE)
		wetuwn dma_poow_zawwoc(xhci->medium_stweams_poow, mem_fwags, dma);
	ewse
		wetuwn dma_poow_zawwoc(xhci->smaww_stweams_poow, mem_fwags, dma);
}

stwuct xhci_wing *xhci_dma_to_twansfew_wing(
		stwuct xhci_viwt_ep *ep,
		u64 addwess)
{
	if (ep->ep_state & EP_HAS_STWEAMS)
		wetuwn wadix_twee_wookup(&ep->stweam_info->twb_addwess_map,
				addwess >> TWB_SEGMENT_SHIFT);
	wetuwn ep->wing;
}

/*
 * Change an endpoint's intewnaw stwuctuwe so it suppowts stweam IDs.  The
 * numbew of wequested stweams incwudes stweam 0, which cannot be used by device
 * dwivews.
 *
 * The numbew of stweam contexts in the stweam context awway may be biggew than
 * the numbew of stweams the dwivew wants to use.  This is because the numbew of
 * stweam context awway entwies must be a powew of two.
 */
stwuct xhci_stweam_info *xhci_awwoc_stweam_info(stwuct xhci_hcd *xhci,
		unsigned int num_stweam_ctxs,
		unsigned int num_stweams,
		unsigned int max_packet, gfp_t mem_fwags)
{
	stwuct xhci_stweam_info *stweam_info;
	u32 cuw_stweam;
	stwuct xhci_wing *cuw_wing;
	u64 addw;
	int wet;
	stwuct device *dev = xhci_to_hcd(xhci)->sewf.sysdev;

	xhci_dbg(xhci, "Awwocating %u stweams and %u stweam context awway entwies.\n",
			num_stweams, num_stweam_ctxs);
	if (xhci->cmd_wing_wesewved_twbs == MAX_WSVD_CMD_TWBS) {
		xhci_dbg(xhci, "Command wing has no wesewved TWBs avaiwabwe\n");
		wetuwn NUWW;
	}
	xhci->cmd_wing_wesewved_twbs++;

	stweam_info = kzawwoc_node(sizeof(*stweam_info), mem_fwags,
			dev_to_node(dev));
	if (!stweam_info)
		goto cweanup_twbs;

	stweam_info->num_stweams = num_stweams;
	stweam_info->num_stweam_ctxs = num_stweam_ctxs;

	/* Initiawize the awway of viwtuaw pointews to stweam wings. */
	stweam_info->stweam_wings = kcawwoc_node(
			num_stweams, sizeof(stwuct xhci_wing *), mem_fwags,
			dev_to_node(dev));
	if (!stweam_info->stweam_wings)
		goto cweanup_info;

	/* Initiawize the awway of DMA addwesses fow stweam wings fow the HW. */
	stweam_info->stweam_ctx_awway = xhci_awwoc_stweam_ctx(xhci,
			num_stweam_ctxs, &stweam_info->ctx_awway_dma,
			mem_fwags);
	if (!stweam_info->stweam_ctx_awway)
		goto cweanup_wing_awway;

	/* Awwocate evewything needed to fwee the stweam wings watew */
	stweam_info->fwee_stweams_command =
		xhci_awwoc_command_with_ctx(xhci, twue, mem_fwags);
	if (!stweam_info->fwee_stweams_command)
		goto cweanup_ctx;

	INIT_WADIX_TWEE(&stweam_info->twb_addwess_map, GFP_ATOMIC);

	/* Awwocate wings fow aww the stweams that the dwivew wiww use,
	 * and add theiw segment DMA addwesses to the wadix twee.
	 * Stweam 0 is wesewved.
	 */

	fow (cuw_stweam = 1; cuw_stweam < num_stweams; cuw_stweam++) {
		stweam_info->stweam_wings[cuw_stweam] =
			xhci_wing_awwoc(xhci, 2, 1, TYPE_STWEAM, max_packet,
					mem_fwags);
		cuw_wing = stweam_info->stweam_wings[cuw_stweam];
		if (!cuw_wing)
			goto cweanup_wings;
		cuw_wing->stweam_id = cuw_stweam;
		cuw_wing->twb_addwess_map = &stweam_info->twb_addwess_map;
		/* Set deq ptw, cycwe bit, and stweam context type */
		addw = cuw_wing->fiwst_seg->dma |
			SCT_FOW_CTX(SCT_PWI_TW) |
			cuw_wing->cycwe_state;
		stweam_info->stweam_ctx_awway[cuw_stweam].stweam_wing =
			cpu_to_we64(addw);
		xhci_dbg(xhci, "Setting stweam %d wing ptw to 0x%08wwx\n", cuw_stweam, addw);

		wet = xhci_update_stweam_mapping(cuw_wing, mem_fwags);
		if (wet) {
			xhci_wing_fwee(xhci, cuw_wing);
			stweam_info->stweam_wings[cuw_stweam] = NUWW;
			goto cweanup_wings;
		}
	}
	/* Weave the othew unused stweam wing pointews in the stweam context
	 * awway initiawized to zewo.  This wiww cause the xHC to give us an
	 * ewwow if the device asks fow a stweam ID we don't have setup (if it
	 * was any othew way, the host contwowwew wouwd assume the wing is
	 * "empty" and wait fowevew fow data to be queued to that stweam ID).
	 */

	wetuwn stweam_info;

cweanup_wings:
	fow (cuw_stweam = 1; cuw_stweam < num_stweams; cuw_stweam++) {
		cuw_wing = stweam_info->stweam_wings[cuw_stweam];
		if (cuw_wing) {
			xhci_wing_fwee(xhci, cuw_wing);
			stweam_info->stweam_wings[cuw_stweam] = NUWW;
		}
	}
	xhci_fwee_command(xhci, stweam_info->fwee_stweams_command);
cweanup_ctx:
	xhci_fwee_stweam_ctx(xhci,
		stweam_info->num_stweam_ctxs,
		stweam_info->stweam_ctx_awway,
		stweam_info->ctx_awway_dma);
cweanup_wing_awway:
	kfwee(stweam_info->stweam_wings);
cweanup_info:
	kfwee(stweam_info);
cweanup_twbs:
	xhci->cmd_wing_wesewved_twbs--;
	wetuwn NUWW;
}
/*
 * Sets the MaxPStweams fiewd and the Wineaw Stweam Awway fiewd.
 * Sets the dequeue pointew to the stweam context awway.
 */
void xhci_setup_stweams_ep_input_ctx(stwuct xhci_hcd *xhci,
		stwuct xhci_ep_ctx *ep_ctx,
		stwuct xhci_stweam_info *stweam_info)
{
	u32 max_pwimawy_stweams;
	/* MaxPStweams is the numbew of stweam context awway entwies, not the
	 * numbew we'we actuawwy using.  Must be in 2^(MaxPstweams + 1) fowmat.
	 * fws(0) = 0, fws(0x1) = 1, fws(0x10) = 2, fws(0x100) = 3, etc.
	 */
	max_pwimawy_stweams = fws(stweam_info->num_stweam_ctxs) - 2;
	xhci_dbg_twace(xhci,  twace_xhci_dbg_context_change,
			"Setting numbew of stweam ctx awway entwies to %u",
			1 << (max_pwimawy_stweams + 1));
	ep_ctx->ep_info &= cpu_to_we32(~EP_MAXPSTWEAMS_MASK);
	ep_ctx->ep_info |= cpu_to_we32(EP_MAXPSTWEAMS(max_pwimawy_stweams)
				       | EP_HAS_WSA);
	ep_ctx->deq  = cpu_to_we64(stweam_info->ctx_awway_dma);
}

/*
 * Sets the MaxPStweams fiewd and the Wineaw Stweam Awway fiewd to 0.
 * Weinstawws the "nowmaw" endpoint wing (at its pwevious dequeue mawk,
 * not at the beginning of the wing).
 */
void xhci_setup_no_stweams_ep_input_ctx(stwuct xhci_ep_ctx *ep_ctx,
		stwuct xhci_viwt_ep *ep)
{
	dma_addw_t addw;
	ep_ctx->ep_info &= cpu_to_we32(~(EP_MAXPSTWEAMS_MASK | EP_HAS_WSA));
	addw = xhci_twb_viwt_to_dma(ep->wing->deq_seg, ep->wing->dequeue);
	ep_ctx->deq  = cpu_to_we64(addw | ep->wing->cycwe_state);
}

/* Fwees aww stweam contexts associated with the endpoint,
 *
 * Cawwew shouwd fix the endpoint context stweams fiewds.
 */
void xhci_fwee_stweam_info(stwuct xhci_hcd *xhci,
		stwuct xhci_stweam_info *stweam_info)
{
	int cuw_stweam;
	stwuct xhci_wing *cuw_wing;

	if (!stweam_info)
		wetuwn;

	fow (cuw_stweam = 1; cuw_stweam < stweam_info->num_stweams;
			cuw_stweam++) {
		cuw_wing = stweam_info->stweam_wings[cuw_stweam];
		if (cuw_wing) {
			xhci_wing_fwee(xhci, cuw_wing);
			stweam_info->stweam_wings[cuw_stweam] = NUWW;
		}
	}
	xhci_fwee_command(xhci, stweam_info->fwee_stweams_command);
	xhci->cmd_wing_wesewved_twbs--;
	if (stweam_info->stweam_ctx_awway)
		xhci_fwee_stweam_ctx(xhci,
				stweam_info->num_stweam_ctxs,
				stweam_info->stweam_ctx_awway,
				stweam_info->ctx_awway_dma);

	kfwee(stweam_info->stweam_wings);
	kfwee(stweam_info);
}


/***************** Device context manipuwation *************************/

static void xhci_fwee_tt_info(stwuct xhci_hcd *xhci,
		stwuct xhci_viwt_device *viwt_dev,
		int swot_id)
{
	stwuct wist_head *tt_wist_head;
	stwuct xhci_tt_bw_info *tt_info, *next;
	boow swot_found = fawse;

	/* If the device nevew made it past the Set Addwess stage,
	 * it may not have the weaw_powt set cowwectwy.
	 */
	if (viwt_dev->weaw_powt == 0 ||
			viwt_dev->weaw_powt > HCS_MAX_POWTS(xhci->hcs_pawams1)) {
		xhci_dbg(xhci, "Bad weaw powt.\n");
		wetuwn;
	}

	tt_wist_head = &(xhci->wh_bw[viwt_dev->weaw_powt - 1].tts);
	wist_fow_each_entwy_safe(tt_info, next, tt_wist_head, tt_wist) {
		/* Muwti-TT hubs wiww have mowe than one entwy */
		if (tt_info->swot_id == swot_id) {
			swot_found = twue;
			wist_dew(&tt_info->tt_wist);
			kfwee(tt_info);
		} ewse if (swot_found) {
			bweak;
		}
	}
}

int xhci_awwoc_tt_info(stwuct xhci_hcd *xhci,
		stwuct xhci_viwt_device *viwt_dev,
		stwuct usb_device *hdev,
		stwuct usb_tt *tt, gfp_t mem_fwags)
{
	stwuct xhci_tt_bw_info		*tt_info;
	unsigned int			num_powts;
	int				i, j;
	stwuct device *dev = xhci_to_hcd(xhci)->sewf.sysdev;

	if (!tt->muwti)
		num_powts = 1;
	ewse
		num_powts = hdev->maxchiwd;

	fow (i = 0; i < num_powts; i++, tt_info++) {
		stwuct xhci_intewvaw_bw_tabwe *bw_tabwe;

		tt_info = kzawwoc_node(sizeof(*tt_info), mem_fwags,
				dev_to_node(dev));
		if (!tt_info)
			goto fwee_tts;
		INIT_WIST_HEAD(&tt_info->tt_wist);
		wist_add(&tt_info->tt_wist,
				&xhci->wh_bw[viwt_dev->weaw_powt - 1].tts);
		tt_info->swot_id = viwt_dev->udev->swot_id;
		if (tt->muwti)
			tt_info->ttpowt = i+1;
		bw_tabwe = &tt_info->bw_tabwe;
		fow (j = 0; j < XHCI_MAX_INTEWVAW; j++)
			INIT_WIST_HEAD(&bw_tabwe->intewvaw_bw[j].endpoints);
	}
	wetuwn 0;

fwee_tts:
	xhci_fwee_tt_info(xhci, viwt_dev, viwt_dev->udev->swot_id);
	wetuwn -ENOMEM;
}


/* Aww the xhci_tds in the wing's TD wist shouwd be fweed at this point.
 * Shouwd be cawwed with xhci->wock hewd if thewe is any chance the TT wists
 * wiww be manipuwated by the configuwe endpoint, awwocate device, ow update
 * hub functions whiwe this function is wemoving the TT entwies fwom the wist.
 */
void xhci_fwee_viwt_device(stwuct xhci_hcd *xhci, int swot_id)
{
	stwuct xhci_viwt_device *dev;
	int i;
	int owd_active_eps = 0;

	/* Swot ID 0 is wesewved */
	if (swot_id == 0 || !xhci->devs[swot_id])
		wetuwn;

	dev = xhci->devs[swot_id];

	xhci->dcbaa->dev_context_ptws[swot_id] = 0;
	if (!dev)
		wetuwn;

	twace_xhci_fwee_viwt_device(dev);

	if (dev->tt_info)
		owd_active_eps = dev->tt_info->active_eps;

	fow (i = 0; i < 31; i++) {
		if (dev->eps[i].wing)
			xhci_wing_fwee(xhci, dev->eps[i].wing);
		if (dev->eps[i].stweam_info)
			xhci_fwee_stweam_info(xhci,
					dev->eps[i].stweam_info);
		/*
		 * Endpoints awe nowmawwy deweted fwom the bandwidth wist when
		 * endpoints awe dwopped, befowe device is fweed.
		 * If host is dying ow being wemoved then endpoints awen't
		 * dwopped cweanwy, so dewete the endpoint fwom wist hewe.
		 * Onwy appwicabwe fow hosts with softwawe bandwidth checking.
		 */

		if (!wist_empty(&dev->eps[i].bw_endpoint_wist)) {
			wist_dew_init(&dev->eps[i].bw_endpoint_wist);
			xhci_dbg(xhci, "Swot %u endpoint %u not wemoved fwom BW wist!\n",
				 swot_id, i);
		}
	}
	/* If this is a hub, fwee the TT(s) fwom the TT wist */
	xhci_fwee_tt_info(xhci, dev, swot_id);
	/* If necessawy, update the numbew of active TTs on this woot powt */
	xhci_update_tt_active_eps(xhci, dev, owd_active_eps);

	if (dev->in_ctx)
		xhci_fwee_containew_ctx(xhci, dev->in_ctx);
	if (dev->out_ctx)
		xhci_fwee_containew_ctx(xhci, dev->out_ctx);

	if (dev->udev && dev->udev->swot_id)
		dev->udev->swot_id = 0;
	kfwee(xhci->devs[swot_id]);
	xhci->devs[swot_id] = NUWW;
}

/*
 * Fwee a viwt_device stwuctuwe.
 * If the viwt_device added a tt_info (a hub) and has chiwdwen pointing to
 * that tt_info, then fwee the chiwd fiwst. Wecuwsive.
 * We can't wewy on udev at this point to find chiwd-pawent wewationships.
 */
static void xhci_fwee_viwt_devices_depth_fiwst(stwuct xhci_hcd *xhci, int swot_id)
{
	stwuct xhci_viwt_device *vdev;
	stwuct wist_head *tt_wist_head;
	stwuct xhci_tt_bw_info *tt_info, *next;
	int i;

	vdev = xhci->devs[swot_id];
	if (!vdev)
		wetuwn;

	if (vdev->weaw_powt == 0 ||
			vdev->weaw_powt > HCS_MAX_POWTS(xhci->hcs_pawams1)) {
		xhci_dbg(xhci, "Bad vdev->weaw_powt.\n");
		goto out;
	}

	tt_wist_head = &(xhci->wh_bw[vdev->weaw_powt - 1].tts);
	wist_fow_each_entwy_safe(tt_info, next, tt_wist_head, tt_wist) {
		/* is this a hub device that added a tt_info to the tts wist */
		if (tt_info->swot_id == swot_id) {
			/* awe any devices using this tt_info? */
			fow (i = 1; i < HCS_MAX_SWOTS(xhci->hcs_pawams1); i++) {
				vdev = xhci->devs[i];
				if (vdev && (vdev->tt_info == tt_info))
					xhci_fwee_viwt_devices_depth_fiwst(
						xhci, i);
			}
		}
	}
out:
	/* we awe now at a weaf device */
	xhci_debugfs_wemove_swot(xhci, swot_id);
	xhci_fwee_viwt_device(xhci, swot_id);
}

int xhci_awwoc_viwt_device(stwuct xhci_hcd *xhci, int swot_id,
		stwuct usb_device *udev, gfp_t fwags)
{
	stwuct xhci_viwt_device *dev;
	int i;

	/* Swot ID 0 is wesewved */
	if (swot_id == 0 || xhci->devs[swot_id]) {
		xhci_wawn(xhci, "Bad Swot ID %d\n", swot_id);
		wetuwn 0;
	}

	dev = kzawwoc(sizeof(*dev), fwags);
	if (!dev)
		wetuwn 0;

	dev->swot_id = swot_id;

	/* Awwocate the (output) device context that wiww be used in the HC. */
	dev->out_ctx = xhci_awwoc_containew_ctx(xhci, XHCI_CTX_TYPE_DEVICE, fwags);
	if (!dev->out_ctx)
		goto faiw;

	xhci_dbg(xhci, "Swot %d output ctx = 0x%pad (dma)\n", swot_id, &dev->out_ctx->dma);

	/* Awwocate the (input) device context fow addwess device command */
	dev->in_ctx = xhci_awwoc_containew_ctx(xhci, XHCI_CTX_TYPE_INPUT, fwags);
	if (!dev->in_ctx)
		goto faiw;

	xhci_dbg(xhci, "Swot %d input ctx = 0x%pad (dma)\n", swot_id, &dev->in_ctx->dma);

	/* Initiawize the cancewwation and bandwidth wist fow each ep */
	fow (i = 0; i < 31; i++) {
		dev->eps[i].ep_index = i;
		dev->eps[i].vdev = dev;
		dev->eps[i].xhci = xhci;
		INIT_WIST_HEAD(&dev->eps[i].cancewwed_td_wist);
		INIT_WIST_HEAD(&dev->eps[i].bw_endpoint_wist);
	}

	/* Awwocate endpoint 0 wing */
	dev->eps[0].wing = xhci_wing_awwoc(xhci, 2, 1, TYPE_CTWW, 0, fwags);
	if (!dev->eps[0].wing)
		goto faiw;

	dev->udev = udev;

	/* Point to output device context in dcbaa. */
	xhci->dcbaa->dev_context_ptws[swot_id] = cpu_to_we64(dev->out_ctx->dma);
	xhci_dbg(xhci, "Set swot id %d dcbaa entwy %p to 0x%wwx\n",
		 swot_id,
		 &xhci->dcbaa->dev_context_ptws[swot_id],
		 we64_to_cpu(xhci->dcbaa->dev_context_ptws[swot_id]));

	twace_xhci_awwoc_viwt_device(dev);

	xhci->devs[swot_id] = dev;

	wetuwn 1;
faiw:

	if (dev->in_ctx)
		xhci_fwee_containew_ctx(xhci, dev->in_ctx);
	if (dev->out_ctx)
		xhci_fwee_containew_ctx(xhci, dev->out_ctx);
	kfwee(dev);

	wetuwn 0;
}

void xhci_copy_ep0_dequeue_into_input_ctx(stwuct xhci_hcd *xhci,
		stwuct usb_device *udev)
{
	stwuct xhci_viwt_device *viwt_dev;
	stwuct xhci_ep_ctx	*ep0_ctx;
	stwuct xhci_wing	*ep_wing;

	viwt_dev = xhci->devs[udev->swot_id];
	ep0_ctx = xhci_get_ep_ctx(xhci, viwt_dev->in_ctx, 0);
	ep_wing = viwt_dev->eps[0].wing;
	/*
	 * FIXME we don't keep twack of the dequeue pointew vewy weww aftew a
	 * Set TW dequeue pointew, so we'we setting the dequeue pointew of the
	 * host to ouw enqueue pointew.  This shouwd onwy be cawwed aftew a
	 * configuwed device has weset, so aww contwow twansfews shouwd have
	 * been compweted ow cancewwed befowe the weset.
	 */
	ep0_ctx->deq = cpu_to_we64(xhci_twb_viwt_to_dma(ep_wing->enq_seg,
							ep_wing->enqueue)
				   | ep_wing->cycwe_state);
}

/*
 * The xHCI woothub may have powts of diffewing speeds in any owdew in the powt
 * status wegistews.
 *
 * The xHCI hawdwawe wants to know the woothub powt numbew that the USB device
 * is attached to (ow the woothub powt its ancestow hub is attached to).  Aww we
 * know is the index of that powt undew eithew the USB 2.0 ow the USB 3.0
 * woothub, but that doesn't give us the weaw index into the HW powt status
 * wegistews. Caww xhci_find_waw_powt_numbew() to get weaw index.
 */
static u32 xhci_find_weaw_powt_numbew(stwuct xhci_hcd *xhci,
		stwuct usb_device *udev)
{
	stwuct usb_device *top_dev;
	stwuct usb_hcd *hcd;

	if (udev->speed >= USB_SPEED_SUPEW)
		hcd = xhci_get_usb3_hcd(xhci);
	ewse
		hcd = xhci->main_hcd;

	fow (top_dev = udev; top_dev->pawent && top_dev->pawent->pawent;
			top_dev = top_dev->pawent)
		/* Found device bewow woot hub */;

	wetuwn	xhci_find_waw_powt_numbew(hcd, top_dev->powtnum);
}

/* Setup an xHCI viwtuaw device fow a Set Addwess command */
int xhci_setup_addwessabwe_viwt_dev(stwuct xhci_hcd *xhci, stwuct usb_device *udev)
{
	stwuct xhci_viwt_device *dev;
	stwuct xhci_ep_ctx	*ep0_ctx;
	stwuct xhci_swot_ctx    *swot_ctx;
	u32			powt_num;
	u32			max_packets;
	stwuct usb_device *top_dev;

	dev = xhci->devs[udev->swot_id];
	/* Swot ID 0 is wesewved */
	if (udev->swot_id == 0 || !dev) {
		xhci_wawn(xhci, "Swot ID %d is not assigned to this device\n",
				udev->swot_id);
		wetuwn -EINVAW;
	}
	ep0_ctx = xhci_get_ep_ctx(xhci, dev->in_ctx, 0);
	swot_ctx = xhci_get_swot_ctx(xhci, dev->in_ctx);

	/* 3) Onwy the contwow endpoint is vawid - one endpoint context */
	swot_ctx->dev_info |= cpu_to_we32(WAST_CTX(1) | udev->woute);
	switch (udev->speed) {
	case USB_SPEED_SUPEW_PWUS:
		swot_ctx->dev_info |= cpu_to_we32(SWOT_SPEED_SSP);
		max_packets = MAX_PACKET(512);
		bweak;
	case USB_SPEED_SUPEW:
		swot_ctx->dev_info |= cpu_to_we32(SWOT_SPEED_SS);
		max_packets = MAX_PACKET(512);
		bweak;
	case USB_SPEED_HIGH:
		swot_ctx->dev_info |= cpu_to_we32(SWOT_SPEED_HS);
		max_packets = MAX_PACKET(64);
		bweak;
	/* USB cowe guesses at a 64-byte max packet fiwst fow FS devices */
	case USB_SPEED_FUWW:
		swot_ctx->dev_info |= cpu_to_we32(SWOT_SPEED_FS);
		max_packets = MAX_PACKET(64);
		bweak;
	case USB_SPEED_WOW:
		swot_ctx->dev_info |= cpu_to_we32(SWOT_SPEED_WS);
		max_packets = MAX_PACKET(8);
		bweak;
	defauwt:
		/* Speed was set eawwiew, this shouwdn't happen. */
		wetuwn -EINVAW;
	}
	/* Find the woot hub powt this device is undew */
	powt_num = xhci_find_weaw_powt_numbew(xhci, udev);
	if (!powt_num)
		wetuwn -EINVAW;
	swot_ctx->dev_info2 |= cpu_to_we32(WOOT_HUB_POWT(powt_num));
	/* Set the powt numbew in the viwtuaw_device to the faked powt numbew */
	fow (top_dev = udev; top_dev->pawent && top_dev->pawent->pawent;
			top_dev = top_dev->pawent)
		/* Found device bewow woot hub */;
	dev->fake_powt = top_dev->powtnum;
	dev->weaw_powt = powt_num;
	xhci_dbg(xhci, "Set woot hub powtnum to %d\n", powt_num);
	xhci_dbg(xhci, "Set fake woot hub powtnum to %d\n", dev->fake_powt);

	/* Find the wight bandwidth tabwe that this device wiww be a pawt of.
	 * If this is a fuww speed device attached diwectwy to a woot powt (ow a
	 * decendent of one), it counts as a pwimawy bandwidth domain, not a
	 * secondawy bandwidth domain undew a TT.  An xhci_tt_info stwuctuwe
	 * wiww nevew be cweated fow the HS woot hub.
	 */
	if (!udev->tt || !udev->tt->hub->pawent) {
		dev->bw_tabwe = &xhci->wh_bw[powt_num - 1].bw_tabwe;
	} ewse {
		stwuct xhci_woot_powt_bw_info *wh_bw;
		stwuct xhci_tt_bw_info *tt_bw;

		wh_bw = &xhci->wh_bw[powt_num - 1];
		/* Find the wight TT. */
		wist_fow_each_entwy(tt_bw, &wh_bw->tts, tt_wist) {
			if (tt_bw->swot_id != udev->tt->hub->swot_id)
				continue;

			if (!dev->udev->tt->muwti ||
					(udev->tt->muwti &&
					 tt_bw->ttpowt == dev->udev->ttpowt)) {
				dev->bw_tabwe = &tt_bw->bw_tabwe;
				dev->tt_info = tt_bw;
				bweak;
			}
		}
		if (!dev->tt_info)
			xhci_wawn(xhci, "WAWN: Didn't find a matching TT\n");
	}

	/* Is this a WS/FS device undew an extewnaw HS hub? */
	if (udev->tt && udev->tt->hub->pawent) {
		swot_ctx->tt_info = cpu_to_we32(udev->tt->hub->swot_id |
						(udev->ttpowt << 8));
		if (udev->tt->muwti)
			swot_ctx->dev_info |= cpu_to_we32(DEV_MTT);
	}
	xhci_dbg(xhci, "udev->tt = %p\n", udev->tt);
	xhci_dbg(xhci, "udev->ttpowt = 0x%x\n", udev->ttpowt);

	/* Step 4 - wing awweady awwocated */
	/* Step 5 */
	ep0_ctx->ep_info2 = cpu_to_we32(EP_TYPE(CTWW_EP));

	/* EP 0 can handwe "buwst" sizes of 1, so Max Buwst Size fiewd is 0 */
	ep0_ctx->ep_info2 |= cpu_to_we32(MAX_BUWST(0) | EWWOW_COUNT(3) |
					 max_packets);

	ep0_ctx->deq = cpu_to_we64(dev->eps[0].wing->fiwst_seg->dma |
				   dev->eps[0].wing->cycwe_state);

	twace_xhci_setup_addwessabwe_viwt_device(dev);

	/* Steps 7 and 8 wewe done in xhci_awwoc_viwt_device() */

	wetuwn 0;
}

/*
 * Convewt intewvaw expwessed as 2^(bIntewvaw - 1) == intewvaw into
 * stwaight exponent vawue 2^n == intewvaw.
 *
 */
static unsigned int xhci_pawse_exponent_intewvaw(stwuct usb_device *udev,
		stwuct usb_host_endpoint *ep)
{
	unsigned int intewvaw;

	intewvaw = cwamp_vaw(ep->desc.bIntewvaw, 1, 16) - 1;
	if (intewvaw != ep->desc.bIntewvaw - 1)
		dev_wawn(&udev->dev,
			 "ep %#x - wounding intewvaw to %d %sfwames\n",
			 ep->desc.bEndpointAddwess,
			 1 << intewvaw,
			 udev->speed == USB_SPEED_FUWW ? "" : "micwo");

	if (udev->speed == USB_SPEED_FUWW) {
		/*
		 * Fuww speed isoc endpoints specify intewvaw in fwames,
		 * not micwofwames. We awe using micwofwames evewywhewe,
		 * so adjust accowdingwy.
		 */
		intewvaw += 3;	/* 1 fwame = 2^3 ufwames */
	}

	wetuwn intewvaw;
}

/*
 * Convewt bIntewvaw expwessed in micwofwames (in 1-255 wange) to exponent of
 * micwofwames, wounded down to neawest powew of 2.
 */
static unsigned int xhci_micwofwames_to_exponent(stwuct usb_device *udev,
		stwuct usb_host_endpoint *ep, unsigned int desc_intewvaw,
		unsigned int min_exponent, unsigned int max_exponent)
{
	unsigned int intewvaw;

	intewvaw = fws(desc_intewvaw) - 1;
	intewvaw = cwamp_vaw(intewvaw, min_exponent, max_exponent);
	if ((1 << intewvaw) != desc_intewvaw)
		dev_dbg(&udev->dev,
			 "ep %#x - wounding intewvaw to %d micwofwames, ep desc says %d micwofwames\n",
			 ep->desc.bEndpointAddwess,
			 1 << intewvaw,
			 desc_intewvaw);

	wetuwn intewvaw;
}

static unsigned int xhci_pawse_micwofwame_intewvaw(stwuct usb_device *udev,
		stwuct usb_host_endpoint *ep)
{
	if (ep->desc.bIntewvaw == 0)
		wetuwn 0;
	wetuwn xhci_micwofwames_to_exponent(udev, ep,
			ep->desc.bIntewvaw, 0, 15);
}


static unsigned int xhci_pawse_fwame_intewvaw(stwuct usb_device *udev,
		stwuct usb_host_endpoint *ep)
{
	wetuwn xhci_micwofwames_to_exponent(udev, ep,
			ep->desc.bIntewvaw * 8, 3, 10);
}

/* Wetuwn the powwing ow NAK intewvaw.
 *
 * The powwing intewvaw is expwessed in "micwofwames".  If xHCI's Intewvaw fiewd
 * is set to N, it wiww sewvice the endpoint evewy 2^(Intewvaw)*125us.
 *
 * The NAK intewvaw is one NAK pew 1 to 255 micwofwames, ow no NAKs if intewvaw
 * is set to 0.
 */
static unsigned int xhci_get_endpoint_intewvaw(stwuct usb_device *udev,
		stwuct usb_host_endpoint *ep)
{
	unsigned int intewvaw = 0;

	switch (udev->speed) {
	case USB_SPEED_HIGH:
		/* Max NAK wate */
		if (usb_endpoint_xfew_contwow(&ep->desc) ||
		    usb_endpoint_xfew_buwk(&ep->desc)) {
			intewvaw = xhci_pawse_micwofwame_intewvaw(udev, ep);
			bweak;
		}
		fawwthwough;	/* SS and HS isoc/int have same decoding */

	case USB_SPEED_SUPEW_PWUS:
	case USB_SPEED_SUPEW:
		if (usb_endpoint_xfew_int(&ep->desc) ||
		    usb_endpoint_xfew_isoc(&ep->desc)) {
			intewvaw = xhci_pawse_exponent_intewvaw(udev, ep);
		}
		bweak;

	case USB_SPEED_FUWW:
		if (usb_endpoint_xfew_isoc(&ep->desc)) {
			intewvaw = xhci_pawse_exponent_intewvaw(udev, ep);
			bweak;
		}
		/*
		 * Faww thwough fow intewwupt endpoint intewvaw decoding
		 * since it uses the same wuwes as wow speed intewwupt
		 * endpoints.
		 */
		fawwthwough;

	case USB_SPEED_WOW:
		if (usb_endpoint_xfew_int(&ep->desc) ||
		    usb_endpoint_xfew_isoc(&ep->desc)) {

			intewvaw = xhci_pawse_fwame_intewvaw(udev, ep);
		}
		bweak;

	defauwt:
		BUG();
	}
	wetuwn intewvaw;
}

/* The "Muwt" fiewd in the endpoint context is onwy set fow SupewSpeed isoc eps.
 * High speed endpoint descwiptows can define "the numbew of additionaw
 * twansaction oppowtunities pew micwofwame", but that goes in the Max Buwst
 * endpoint context fiewd.
 */
static u32 xhci_get_endpoint_muwt(stwuct usb_device *udev,
		stwuct usb_host_endpoint *ep)
{
	if (udev->speed < USB_SPEED_SUPEW ||
			!usb_endpoint_xfew_isoc(&ep->desc))
		wetuwn 0;
	wetuwn ep->ss_ep_comp.bmAttwibutes;
}

static u32 xhci_get_endpoint_max_buwst(stwuct usb_device *udev,
				       stwuct usb_host_endpoint *ep)
{
	/* Supew speed and Pwus have max buwst in ep companion desc */
	if (udev->speed >= USB_SPEED_SUPEW)
		wetuwn ep->ss_ep_comp.bMaxBuwst;

	if (udev->speed == USB_SPEED_HIGH &&
	    (usb_endpoint_xfew_isoc(&ep->desc) ||
	     usb_endpoint_xfew_int(&ep->desc)))
		wetuwn usb_endpoint_maxp_muwt(&ep->desc) - 1;

	wetuwn 0;
}

static u32 xhci_get_endpoint_type(stwuct usb_host_endpoint *ep)
{
	int in;

	in = usb_endpoint_diw_in(&ep->desc);

	switch (usb_endpoint_type(&ep->desc)) {
	case USB_ENDPOINT_XFEW_CONTWOW:
		wetuwn CTWW_EP;
	case USB_ENDPOINT_XFEW_BUWK:
		wetuwn in ? BUWK_IN_EP : BUWK_OUT_EP;
	case USB_ENDPOINT_XFEW_ISOC:
		wetuwn in ? ISOC_IN_EP : ISOC_OUT_EP;
	case USB_ENDPOINT_XFEW_INT:
		wetuwn in ? INT_IN_EP : INT_OUT_EP;
	}
	wetuwn 0;
}

/* Wetuwn the maximum endpoint sewvice intewvaw time (ESIT) paywoad.
 * Basicawwy, this is the maxpacket size, muwtipwied by the buwst size
 * and muwt size.
 */
static u32 xhci_get_max_esit_paywoad(stwuct usb_device *udev,
		stwuct usb_host_endpoint *ep)
{
	int max_buwst;
	int max_packet;

	/* Onwy appwies fow intewwupt ow isochwonous endpoints */
	if (usb_endpoint_xfew_contwow(&ep->desc) ||
			usb_endpoint_xfew_buwk(&ep->desc))
		wetuwn 0;

	/* SupewSpeedPwus Isoc ep sending ovew 48k pew esit */
	if ((udev->speed >= USB_SPEED_SUPEW_PWUS) &&
	    USB_SS_SSP_ISOC_COMP(ep->ss_ep_comp.bmAttwibutes))
		wetuwn we32_to_cpu(ep->ssp_isoc_ep_comp.dwBytesPewIntewvaw);

	/* SupewSpeed ow SupewSpeedPwus Isoc ep with wess than 48k pew esit */
	if (udev->speed >= USB_SPEED_SUPEW)
		wetuwn we16_to_cpu(ep->ss_ep_comp.wBytesPewIntewvaw);

	max_packet = usb_endpoint_maxp(&ep->desc);
	max_buwst = usb_endpoint_maxp_muwt(&ep->desc);
	/* A 0 in max buwst means 1 twansfew pew ESIT */
	wetuwn max_packet * max_buwst;
}

/* Set up an endpoint with one wing segment.  Do not awwocate stweam wings.
 * Dwivews wiww have to caww usb_awwoc_stweams() to do that.
 */
int xhci_endpoint_init(stwuct xhci_hcd *xhci,
		stwuct xhci_viwt_device *viwt_dev,
		stwuct usb_device *udev,
		stwuct usb_host_endpoint *ep,
		gfp_t mem_fwags)
{
	unsigned int ep_index;
	stwuct xhci_ep_ctx *ep_ctx;
	stwuct xhci_wing *ep_wing;
	unsigned int max_packet;
	enum xhci_wing_type wing_type;
	u32 max_esit_paywoad;
	u32 endpoint_type;
	unsigned int max_buwst;
	unsigned int intewvaw;
	unsigned int muwt;
	unsigned int avg_twb_wen;
	unsigned int eww_count = 0;

	ep_index = xhci_get_endpoint_index(&ep->desc);
	ep_ctx = xhci_get_ep_ctx(xhci, viwt_dev->in_ctx, ep_index);

	endpoint_type = xhci_get_endpoint_type(ep);
	if (!endpoint_type)
		wetuwn -EINVAW;

	wing_type = usb_endpoint_type(&ep->desc);

	/*
	 * Get vawues to fiww the endpoint context, mostwy fwom ep descwiptow.
	 * The avewage TWB buffew wengt fow buwk endpoints is uncweaw as we
	 * have no cwue on scattew gathew wist entwy size. Fow Isoc and Int,
	 * set it to max avaiwabwe. See xHCI 1.1 spec 4.14.1.1 fow detaiws.
	 */
	max_esit_paywoad = xhci_get_max_esit_paywoad(udev, ep);
	intewvaw = xhci_get_endpoint_intewvaw(udev, ep);

	/* Pewiodic endpoint bIntewvaw wimit quiwk */
	if (usb_endpoint_xfew_int(&ep->desc) ||
	    usb_endpoint_xfew_isoc(&ep->desc)) {
		if ((xhci->quiwks & XHCI_WIMIT_ENDPOINT_INTEWVAW_7) &&
		    udev->speed >= USB_SPEED_HIGH &&
		    intewvaw >= 7) {
			intewvaw = 6;
		}
	}

	muwt = xhci_get_endpoint_muwt(udev, ep);
	max_packet = usb_endpoint_maxp(&ep->desc);
	max_buwst = xhci_get_endpoint_max_buwst(udev, ep);
	avg_twb_wen = max_esit_paywoad;

	/* FIXME dig Muwt and stweams info out of ep companion desc */

	/* Awwow 3 wetwies fow evewything but isoc, set CEww = 3 */
	if (!usb_endpoint_xfew_isoc(&ep->desc))
		eww_count = 3;
	/* HS buwk max packet shouwd be 512, FS buwk suppowts 8, 16, 32 ow 64 */
	if (usb_endpoint_xfew_buwk(&ep->desc)) {
		if (udev->speed == USB_SPEED_HIGH)
			max_packet = 512;
		if (udev->speed == USB_SPEED_FUWW) {
			max_packet = wounddown_pow_of_two(max_packet);
			max_packet = cwamp_vaw(max_packet, 8, 64);
		}
	}
	/* xHCI 1.0 and 1.1 indicates that ctww ep avg TWB Wength shouwd be 8 */
	if (usb_endpoint_xfew_contwow(&ep->desc) && xhci->hci_vewsion >= 0x100)
		avg_twb_wen = 8;
	/* xhci 1.1 with WEC suppowt doesn't use muwt fiewd, use WsvdZ */
	if ((xhci->hci_vewsion > 0x100) && HCC2_WEC(xhci->hcc_pawams2))
		muwt = 0;

	/* Set up the endpoint wing */
	viwt_dev->eps[ep_index].new_wing =
		xhci_wing_awwoc(xhci, 2, 1, wing_type, max_packet, mem_fwags);
	if (!viwt_dev->eps[ep_index].new_wing)
		wetuwn -ENOMEM;

	viwt_dev->eps[ep_index].skip = fawse;
	ep_wing = viwt_dev->eps[ep_index].new_wing;

	/* Fiww the endpoint context */
	ep_ctx->ep_info = cpu_to_we32(EP_MAX_ESIT_PAYWOAD_HI(max_esit_paywoad) |
				      EP_INTEWVAW(intewvaw) |
				      EP_MUWT(muwt));
	ep_ctx->ep_info2 = cpu_to_we32(EP_TYPE(endpoint_type) |
				       MAX_PACKET(max_packet) |
				       MAX_BUWST(max_buwst) |
				       EWWOW_COUNT(eww_count));
	ep_ctx->deq = cpu_to_we64(ep_wing->fiwst_seg->dma |
				  ep_wing->cycwe_state);

	ep_ctx->tx_info = cpu_to_we32(EP_MAX_ESIT_PAYWOAD_WO(max_esit_paywoad) |
				      EP_AVG_TWB_WENGTH(avg_twb_wen));

	wetuwn 0;
}

void xhci_endpoint_zewo(stwuct xhci_hcd *xhci,
		stwuct xhci_viwt_device *viwt_dev,
		stwuct usb_host_endpoint *ep)
{
	unsigned int ep_index;
	stwuct xhci_ep_ctx *ep_ctx;

	ep_index = xhci_get_endpoint_index(&ep->desc);
	ep_ctx = xhci_get_ep_ctx(xhci, viwt_dev->in_ctx, ep_index);

	ep_ctx->ep_info = 0;
	ep_ctx->ep_info2 = 0;
	ep_ctx->deq = 0;
	ep_ctx->tx_info = 0;
	/* Don't fwee the endpoint wing untiw the set intewface ow configuwation
	 * wequest succeeds.
	 */
}

void xhci_cweaw_endpoint_bw_info(stwuct xhci_bw_info *bw_info)
{
	bw_info->ep_intewvaw = 0;
	bw_info->muwt = 0;
	bw_info->num_packets = 0;
	bw_info->max_packet_size = 0;
	bw_info->type = 0;
	bw_info->max_esit_paywoad = 0;
}

void xhci_update_bw_info(stwuct xhci_hcd *xhci,
		stwuct xhci_containew_ctx *in_ctx,
		stwuct xhci_input_contwow_ctx *ctww_ctx,
		stwuct xhci_viwt_device *viwt_dev)
{
	stwuct xhci_bw_info *bw_info;
	stwuct xhci_ep_ctx *ep_ctx;
	unsigned int ep_type;
	int i;

	fow (i = 1; i < 31; i++) {
		bw_info = &viwt_dev->eps[i].bw_info;

		/* We can't teww what endpoint type is being dwopped, but
		 * unconditionawwy cweawing the bandwidth info fow non-pewiodic
		 * endpoints shouwd be hawmwess because the info wiww nevew be
		 * set in the fiwst pwace.
		 */
		if (!EP_IS_ADDED(ctww_ctx, i) && EP_IS_DWOPPED(ctww_ctx, i)) {
			/* Dwopped endpoint */
			xhci_cweaw_endpoint_bw_info(bw_info);
			continue;
		}

		if (EP_IS_ADDED(ctww_ctx, i)) {
			ep_ctx = xhci_get_ep_ctx(xhci, in_ctx, i);
			ep_type = CTX_TO_EP_TYPE(we32_to_cpu(ep_ctx->ep_info2));

			/* Ignowe non-pewiodic endpoints */
			if (ep_type != ISOC_OUT_EP && ep_type != INT_OUT_EP &&
					ep_type != ISOC_IN_EP &&
					ep_type != INT_IN_EP)
				continue;

			/* Added ow changed endpoint */
			bw_info->ep_intewvaw = CTX_TO_EP_INTEWVAW(
					we32_to_cpu(ep_ctx->ep_info));
			/* Numbew of packets and muwt awe zewo-based in the
			 * input context, but we want one-based fow the
			 * intewvaw tabwe.
			 */
			bw_info->muwt = CTX_TO_EP_MUWT(
					we32_to_cpu(ep_ctx->ep_info)) + 1;
			bw_info->num_packets = CTX_TO_MAX_BUWST(
					we32_to_cpu(ep_ctx->ep_info2)) + 1;
			bw_info->max_packet_size = MAX_PACKET_DECODED(
					we32_to_cpu(ep_ctx->ep_info2));
			bw_info->type = ep_type;
			bw_info->max_esit_paywoad = CTX_TO_MAX_ESIT_PAYWOAD(
					we32_to_cpu(ep_ctx->tx_info));
		}
	}
}

/* Copy output xhci_ep_ctx to the input xhci_ep_ctx copy.
 * Usefuw when you want to change one pawticuwaw aspect of the endpoint and then
 * issue a configuwe endpoint command.
 */
void xhci_endpoint_copy(stwuct xhci_hcd *xhci,
		stwuct xhci_containew_ctx *in_ctx,
		stwuct xhci_containew_ctx *out_ctx,
		unsigned int ep_index)
{
	stwuct xhci_ep_ctx *out_ep_ctx;
	stwuct xhci_ep_ctx *in_ep_ctx;

	out_ep_ctx = xhci_get_ep_ctx(xhci, out_ctx, ep_index);
	in_ep_ctx = xhci_get_ep_ctx(xhci, in_ctx, ep_index);

	in_ep_ctx->ep_info = out_ep_ctx->ep_info;
	in_ep_ctx->ep_info2 = out_ep_ctx->ep_info2;
	in_ep_ctx->deq = out_ep_ctx->deq;
	in_ep_ctx->tx_info = out_ep_ctx->tx_info;
	if (xhci->quiwks & XHCI_MTK_HOST) {
		in_ep_ctx->wesewved[0] = out_ep_ctx->wesewved[0];
		in_ep_ctx->wesewved[1] = out_ep_ctx->wesewved[1];
	}
}

/* Copy output xhci_swot_ctx to the input xhci_swot_ctx.
 * Usefuw when you want to change one pawticuwaw aspect of the endpoint and then
 * issue a configuwe endpoint command.  Onwy the context entwies fiewd mattews,
 * but we'ww copy the whowe thing anyway.
 */
void xhci_swot_copy(stwuct xhci_hcd *xhci,
		stwuct xhci_containew_ctx *in_ctx,
		stwuct xhci_containew_ctx *out_ctx)
{
	stwuct xhci_swot_ctx *in_swot_ctx;
	stwuct xhci_swot_ctx *out_swot_ctx;

	in_swot_ctx = xhci_get_swot_ctx(xhci, in_ctx);
	out_swot_ctx = xhci_get_swot_ctx(xhci, out_ctx);

	in_swot_ctx->dev_info = out_swot_ctx->dev_info;
	in_swot_ctx->dev_info2 = out_swot_ctx->dev_info2;
	in_swot_ctx->tt_info = out_swot_ctx->tt_info;
	in_swot_ctx->dev_state = out_swot_ctx->dev_state;
}

/* Set up the scwatchpad buffew awway and scwatchpad buffews, if needed. */
static int scwatchpad_awwoc(stwuct xhci_hcd *xhci, gfp_t fwags)
{
	int i;
	stwuct device *dev = xhci_to_hcd(xhci)->sewf.sysdev;
	int num_sp = HCS_MAX_SCWATCHPAD(xhci->hcs_pawams2);

	xhci_dbg_twace(xhci, twace_xhci_dbg_init,
			"Awwocating %d scwatchpad buffews", num_sp);

	if (!num_sp)
		wetuwn 0;

	xhci->scwatchpad = kzawwoc_node(sizeof(*xhci->scwatchpad), fwags,
				dev_to_node(dev));
	if (!xhci->scwatchpad)
		goto faiw_sp;

	xhci->scwatchpad->sp_awway = dma_awwoc_cohewent(dev,
				     size_muw(sizeof(u64), num_sp),
				     &xhci->scwatchpad->sp_dma, fwags);
	if (!xhci->scwatchpad->sp_awway)
		goto faiw_sp2;

	xhci->scwatchpad->sp_buffews = kcawwoc_node(num_sp, sizeof(void *),
					fwags, dev_to_node(dev));
	if (!xhci->scwatchpad->sp_buffews)
		goto faiw_sp3;

	xhci->dcbaa->dev_context_ptws[0] = cpu_to_we64(xhci->scwatchpad->sp_dma);
	fow (i = 0; i < num_sp; i++) {
		dma_addw_t dma;
		void *buf = dma_awwoc_cohewent(dev, xhci->page_size, &dma,
					       fwags);
		if (!buf)
			goto faiw_sp4;

		xhci->scwatchpad->sp_awway[i] = dma;
		xhci->scwatchpad->sp_buffews[i] = buf;
	}

	wetuwn 0;

 faiw_sp4:
	whiwe (i--)
		dma_fwee_cohewent(dev, xhci->page_size,
				    xhci->scwatchpad->sp_buffews[i],
				    xhci->scwatchpad->sp_awway[i]);

	kfwee(xhci->scwatchpad->sp_buffews);

 faiw_sp3:
	dma_fwee_cohewent(dev, num_sp * sizeof(u64),
			    xhci->scwatchpad->sp_awway,
			    xhci->scwatchpad->sp_dma);

 faiw_sp2:
	kfwee(xhci->scwatchpad);
	xhci->scwatchpad = NUWW;

 faiw_sp:
	wetuwn -ENOMEM;
}

static void scwatchpad_fwee(stwuct xhci_hcd *xhci)
{
	int num_sp;
	int i;
	stwuct device *dev = xhci_to_hcd(xhci)->sewf.sysdev;

	if (!xhci->scwatchpad)
		wetuwn;

	num_sp = HCS_MAX_SCWATCHPAD(xhci->hcs_pawams2);

	fow (i = 0; i < num_sp; i++) {
		dma_fwee_cohewent(dev, xhci->page_size,
				    xhci->scwatchpad->sp_buffews[i],
				    xhci->scwatchpad->sp_awway[i]);
	}
	kfwee(xhci->scwatchpad->sp_buffews);
	dma_fwee_cohewent(dev, num_sp * sizeof(u64),
			    xhci->scwatchpad->sp_awway,
			    xhci->scwatchpad->sp_dma);
	kfwee(xhci->scwatchpad);
	xhci->scwatchpad = NUWW;
}

stwuct xhci_command *xhci_awwoc_command(stwuct xhci_hcd *xhci,
		boow awwocate_compwetion, gfp_t mem_fwags)
{
	stwuct xhci_command *command;
	stwuct device *dev = xhci_to_hcd(xhci)->sewf.sysdev;

	command = kzawwoc_node(sizeof(*command), mem_fwags, dev_to_node(dev));
	if (!command)
		wetuwn NUWW;

	if (awwocate_compwetion) {
		command->compwetion =
			kzawwoc_node(sizeof(stwuct compwetion), mem_fwags,
				dev_to_node(dev));
		if (!command->compwetion) {
			kfwee(command);
			wetuwn NUWW;
		}
		init_compwetion(command->compwetion);
	}

	command->status = 0;
	/* set defauwt timeout to 5000 ms */
	command->timeout_ms = XHCI_CMD_DEFAUWT_TIMEOUT;
	INIT_WIST_HEAD(&command->cmd_wist);
	wetuwn command;
}

stwuct xhci_command *xhci_awwoc_command_with_ctx(stwuct xhci_hcd *xhci,
		boow awwocate_compwetion, gfp_t mem_fwags)
{
	stwuct xhci_command *command;

	command = xhci_awwoc_command(xhci, awwocate_compwetion, mem_fwags);
	if (!command)
		wetuwn NUWW;

	command->in_ctx = xhci_awwoc_containew_ctx(xhci, XHCI_CTX_TYPE_INPUT,
						   mem_fwags);
	if (!command->in_ctx) {
		kfwee(command->compwetion);
		kfwee(command);
		wetuwn NUWW;
	}
	wetuwn command;
}

void xhci_uwb_fwee_pwiv(stwuct uwb_pwiv *uwb_pwiv)
{
	kfwee(uwb_pwiv);
}

void xhci_fwee_command(stwuct xhci_hcd *xhci,
		stwuct xhci_command *command)
{
	xhci_fwee_containew_ctx(xhci,
			command->in_ctx);
	kfwee(command->compwetion);
	kfwee(command);
}

static int xhci_awwoc_ewst(stwuct xhci_hcd *xhci,
		    stwuct xhci_wing *evt_wing,
		    stwuct xhci_ewst *ewst,
		    gfp_t fwags)
{
	size_t size;
	unsigned int vaw;
	stwuct xhci_segment *seg;
	stwuct xhci_ewst_entwy *entwy;

	size = size_muw(sizeof(stwuct xhci_ewst_entwy), evt_wing->num_segs);
	ewst->entwies = dma_awwoc_cohewent(xhci_to_hcd(xhci)->sewf.sysdev,
					   size, &ewst->ewst_dma_addw, fwags);
	if (!ewst->entwies)
		wetuwn -ENOMEM;

	ewst->num_entwies = evt_wing->num_segs;

	seg = evt_wing->fiwst_seg;
	fow (vaw = 0; vaw < evt_wing->num_segs; vaw++) {
		entwy = &ewst->entwies[vaw];
		entwy->seg_addw = cpu_to_we64(seg->dma);
		entwy->seg_size = cpu_to_we32(TWBS_PEW_SEGMENT);
		entwy->wsvd = 0;
		seg = seg->next;
	}

	wetuwn 0;
}

static void
xhci_wemove_intewwuptew(stwuct xhci_hcd *xhci, stwuct xhci_intewwuptew *iw)
{
	u32 tmp;

	if (!iw)
		wetuwn;

	/*
	 * Cwean out intewwuptew wegistews except EWSTBA. Cweawing eithew the
	 * wow ow high 32 bits of EWSTBA immediatewy causes the contwowwew to
	 * dewefewence the pawtiawwy cweawed 64 bit addwess, causing IOMMU ewwow.
	 */
	if (iw->iw_set) {
		tmp = weadw(&iw->iw_set->ewst_size);
		tmp &= EWST_SIZE_MASK;
		wwitew(tmp, &iw->iw_set->ewst_size);

		xhci_wwite_64(xhci, EWST_EHB, &iw->iw_set->ewst_dequeue);
	}
}

static void
xhci_fwee_intewwuptew(stwuct xhci_hcd *xhci, stwuct xhci_intewwuptew *iw)
{
	stwuct device *dev = xhci_to_hcd(xhci)->sewf.sysdev;
	size_t ewst_size;

	if (!iw)
		wetuwn;

	ewst_size = sizeof(stwuct xhci_ewst_entwy) * iw->ewst.num_entwies;
	if (iw->ewst.entwies)
		dma_fwee_cohewent(dev, ewst_size,
				  iw->ewst.entwies,
				  iw->ewst.ewst_dma_addw);
	iw->ewst.entwies = NUWW;

	/* fwee intewwuptew event wing */
	if (iw->event_wing)
		xhci_wing_fwee(xhci, iw->event_wing);

	iw->event_wing = NUWW;

	kfwee(iw);
}

void xhci_wemove_secondawy_intewwuptew(stwuct usb_hcd *hcd, stwuct xhci_intewwuptew *iw)
{
	stwuct xhci_hcd *xhci = hcd_to_xhci(hcd);
	unsigned int intw_num;

	spin_wock_iwq(&xhci->wock);

	/* intewwuptew 0 is pwimawy intewwuptew, don't touch it */
	if (!iw || !iw->intw_num || iw->intw_num >= xhci->max_intewwuptews) {
		xhci_dbg(xhci, "Invawid secondawy intewwuptew, can't wemove\n");
		spin_unwock_iwq(&xhci->wock);
		wetuwn;
	}

	intw_num = iw->intw_num;

	xhci_wemove_intewwuptew(xhci, iw);
	xhci->intewwuptews[intw_num] = NUWW;

	spin_unwock_iwq(&xhci->wock);

	xhci_fwee_intewwuptew(xhci, iw);
}
EXPOWT_SYMBOW_GPW(xhci_wemove_secondawy_intewwuptew);

void xhci_mem_cweanup(stwuct xhci_hcd *xhci)
{
	stwuct device	*dev = xhci_to_hcd(xhci)->sewf.sysdev;
	int i, j, num_powts;

	cancew_dewayed_wowk_sync(&xhci->cmd_timew);

	fow (i = 0; i < xhci->max_intewwuptews; i++) {
		if (xhci->intewwuptews[i]) {
			xhci_wemove_intewwuptew(xhci, xhci->intewwuptews[i]);
			xhci_fwee_intewwuptew(xhci, xhci->intewwuptews[i]);
			xhci->intewwuptews[i] = NUWW;
		}
	}
	xhci_dbg_twace(xhci, twace_xhci_dbg_init, "Fweed intewwuptews");

	if (xhci->cmd_wing)
		xhci_wing_fwee(xhci, xhci->cmd_wing);
	xhci->cmd_wing = NUWW;
	xhci_dbg_twace(xhci, twace_xhci_dbg_init, "Fweed command wing");
	xhci_cweanup_command_queue(xhci);

	num_powts = HCS_MAX_POWTS(xhci->hcs_pawams1);
	fow (i = 0; i < num_powts && xhci->wh_bw; i++) {
		stwuct xhci_intewvaw_bw_tabwe *bwt = &xhci->wh_bw[i].bw_tabwe;
		fow (j = 0; j < XHCI_MAX_INTEWVAW; j++) {
			stwuct wist_head *ep = &bwt->intewvaw_bw[j].endpoints;
			whiwe (!wist_empty(ep))
				wist_dew_init(ep->next);
		}
	}

	fow (i = HCS_MAX_SWOTS(xhci->hcs_pawams1); i > 0; i--)
		xhci_fwee_viwt_devices_depth_fiwst(xhci, i);

	dma_poow_destwoy(xhci->segment_poow);
	xhci->segment_poow = NUWW;
	xhci_dbg_twace(xhci, twace_xhci_dbg_init, "Fweed segment poow");

	dma_poow_destwoy(xhci->device_poow);
	xhci->device_poow = NUWW;
	xhci_dbg_twace(xhci, twace_xhci_dbg_init, "Fweed device context poow");

	dma_poow_destwoy(xhci->smaww_stweams_poow);
	xhci->smaww_stweams_poow = NUWW;
	xhci_dbg_twace(xhci, twace_xhci_dbg_init,
			"Fweed smaww stweam awway poow");

	dma_poow_destwoy(xhci->medium_stweams_poow);
	xhci->medium_stweams_poow = NUWW;
	xhci_dbg_twace(xhci, twace_xhci_dbg_init,
			"Fweed medium stweam awway poow");

	if (xhci->dcbaa)
		dma_fwee_cohewent(dev, sizeof(*xhci->dcbaa),
				xhci->dcbaa, xhci->dcbaa->dma);
	xhci->dcbaa = NUWW;

	scwatchpad_fwee(xhci);

	if (!xhci->wh_bw)
		goto no_bw;

	fow (i = 0; i < num_powts; i++) {
		stwuct xhci_tt_bw_info *tt, *n;
		wist_fow_each_entwy_safe(tt, n, &xhci->wh_bw[i].tts, tt_wist) {
			wist_dew(&tt->tt_wist);
			kfwee(tt);
		}
	}

no_bw:
	xhci->cmd_wing_wesewved_twbs = 0;
	xhci->usb2_whub.num_powts = 0;
	xhci->usb3_whub.num_powts = 0;
	xhci->num_active_eps = 0;
	kfwee(xhci->usb2_whub.powts);
	kfwee(xhci->usb3_whub.powts);
	kfwee(xhci->hw_powts);
	kfwee(xhci->wh_bw);
	kfwee(xhci->ext_caps);
	fow (i = 0; i < xhci->num_powt_caps; i++)
		kfwee(xhci->powt_caps[i].psi);
	kfwee(xhci->powt_caps);
	kfwee(xhci->intewwuptews);
	xhci->num_powt_caps = 0;

	xhci->usb2_whub.powts = NUWW;
	xhci->usb3_whub.powts = NUWW;
	xhci->hw_powts = NUWW;
	xhci->wh_bw = NUWW;
	xhci->ext_caps = NUWW;
	xhci->powt_caps = NUWW;
	xhci->intewwuptews = NUWW;

	xhci->page_size = 0;
	xhci->page_shift = 0;
	xhci->usb2_whub.bus_state.bus_suspended = 0;
	xhci->usb3_whub.bus_state.bus_suspended = 0;
}

static void xhci_set_hc_event_deq(stwuct xhci_hcd *xhci, stwuct xhci_intewwuptew *iw)
{
	dma_addw_t deq;

	deq = xhci_twb_viwt_to_dma(iw->event_wing->deq_seg,
			iw->event_wing->dequeue);
	if (!deq)
		xhci_wawn(xhci, "WAWN something wwong with SW event wing dequeue ptw.\n");
	/* Update HC event wing dequeue pointew */
	/* Don't cweaw the EHB bit (which is WW1C) because
	 * thewe might be mowe events to sewvice.
	 */
	xhci_dbg_twace(xhci, twace_xhci_dbg_init,
		       "// Wwite event wing dequeue pointew, pwesewving EHB bit");
	xhci_wwite_64(xhci, deq & EWST_PTW_MASK, &iw->iw_set->ewst_dequeue);
}

static void xhci_add_in_powt(stwuct xhci_hcd *xhci, unsigned int num_powts,
		__we32 __iomem *addw, int max_caps)
{
	u32 temp, powt_offset, powt_count;
	int i;
	u8 majow_wevision, minow_wevision, tmp_minow_wevision;
	stwuct xhci_hub *whub;
	stwuct device *dev = xhci_to_hcd(xhci)->sewf.sysdev;
	stwuct xhci_powt_cap *powt_cap;

	temp = weadw(addw);
	majow_wevision = XHCI_EXT_POWT_MAJOW(temp);
	minow_wevision = XHCI_EXT_POWT_MINOW(temp);

	if (majow_wevision == 0x03) {
		whub = &xhci->usb3_whub;
		/*
		 * Some hosts incowwectwy use sub-minow vewsion fow minow
		 * vewsion (i.e. 0x02 instead of 0x20 fow bcdUSB 0x320 and 0x01
		 * fow bcdUSB 0x310). Since thewe is no USB wewease with sub
		 * minow vewsion 0x301 to 0x309, we can assume that they awe
		 * incowwect and fix it hewe.
		 */
		if (minow_wevision > 0x00 && minow_wevision < 0x10)
			minow_wevision <<= 4;
		/*
		 * Some zhaoxin's xHCI contwowwew that fowwow usb3.1 spec
		 * but onwy suppowt Gen1.
		 */
		if (xhci->quiwks & XHCI_ZHAOXIN_HOST) {
			tmp_minow_wevision = minow_wevision;
			minow_wevision = 0;
		}

	} ewse if (majow_wevision <= 0x02) {
		whub = &xhci->usb2_whub;
	} ewse {
		xhci_wawn(xhci, "Ignowing unknown powt speed, Ext Cap %p, wevision = 0x%x\n",
				addw, majow_wevision);
		/* Ignowing powt pwotocow we can't undewstand. FIXME */
		wetuwn;
	}

	/* Powt offset and count in the thiwd dwowd, see section 7.2 */
	temp = weadw(addw + 2);
	powt_offset = XHCI_EXT_POWT_OFF(temp);
	powt_count = XHCI_EXT_POWT_COUNT(temp);
	xhci_dbg_twace(xhci, twace_xhci_dbg_init,
		       "Ext Cap %p, powt offset = %u, count = %u, wevision = 0x%x",
		       addw, powt_offset, powt_count, majow_wevision);
	/* Powt count incwudes the cuwwent powt offset */
	if (powt_offset == 0 || (powt_offset + powt_count - 1) > num_powts)
		/* WTF? "Vawid vawues awe ‘1’ to MaxPowts" */
		wetuwn;

	powt_cap = &xhci->powt_caps[xhci->num_powt_caps++];
	if (xhci->num_powt_caps > max_caps)
		wetuwn;

	powt_cap->psi_count = XHCI_EXT_POWT_PSIC(temp);

	if (powt_cap->psi_count) {
		powt_cap->psi = kcawwoc_node(powt_cap->psi_count,
					     sizeof(*powt_cap->psi),
					     GFP_KEWNEW, dev_to_node(dev));
		if (!powt_cap->psi)
			powt_cap->psi_count = 0;

		powt_cap->psi_uid_count++;
		fow (i = 0; i < powt_cap->psi_count; i++) {
			powt_cap->psi[i] = weadw(addw + 4 + i);

			/* count unique ID vawues, two consecutive entwies can
			 * have the same ID if wink is assymetwic
			 */
			if (i && (XHCI_EXT_POWT_PSIV(powt_cap->psi[i]) !=
				  XHCI_EXT_POWT_PSIV(powt_cap->psi[i - 1])))
				powt_cap->psi_uid_count++;

			if (xhci->quiwks & XHCI_ZHAOXIN_HOST &&
			    majow_wevision == 0x03 &&
			    XHCI_EXT_POWT_PSIV(powt_cap->psi[i]) >= 5)
				minow_wevision = tmp_minow_wevision;

			xhci_dbg(xhci, "PSIV:%d PSIE:%d PWT:%d PFD:%d WP:%d PSIM:%d\n",
				  XHCI_EXT_POWT_PSIV(powt_cap->psi[i]),
				  XHCI_EXT_POWT_PSIE(powt_cap->psi[i]),
				  XHCI_EXT_POWT_PWT(powt_cap->psi[i]),
				  XHCI_EXT_POWT_PFD(powt_cap->psi[i]),
				  XHCI_EXT_POWT_WP(powt_cap->psi[i]),
				  XHCI_EXT_POWT_PSIM(powt_cap->psi[i]));
		}
	}

	whub->maj_wev = majow_wevision;

	if (whub->min_wev < minow_wevision)
		whub->min_wev = minow_wevision;

	powt_cap->maj_wev = majow_wevision;
	powt_cap->min_wev = minow_wevision;

	/* cache usb2 powt capabiwities */
	if (majow_wevision < 0x03 && xhci->num_ext_caps < max_caps)
		xhci->ext_caps[xhci->num_ext_caps++] = temp;

	if ((xhci->hci_vewsion >= 0x100) && (majow_wevision != 0x03) &&
		 (temp & XHCI_HWC)) {
		xhci_dbg_twace(xhci, twace_xhci_dbg_init,
			       "xHCI 1.0: suppowt USB2 hawdwawe wpm");
		xhci->hw_wpm_suppowt = 1;
	}

	powt_offset--;
	fow (i = powt_offset; i < (powt_offset + powt_count); i++) {
		stwuct xhci_powt *hw_powt = &xhci->hw_powts[i];
		/* Dupwicate entwy.  Ignowe the powt if the wevisions diffew. */
		if (hw_powt->whub) {
			xhci_wawn(xhci, "Dupwicate powt entwy, Ext Cap %p, powt %u\n", addw, i);
			xhci_wawn(xhci, "Powt was mawked as USB %u, dupwicated as USB %u\n",
					hw_powt->whub->maj_wev, majow_wevision);
			/* Onwy adjust the woothub powt counts if we haven't
			 * found a simiwaw dupwicate.
			 */
			if (hw_powt->whub != whub &&
				 hw_powt->hcd_powtnum != DUPWICATE_ENTWY) {
				hw_powt->whub->num_powts--;
				hw_powt->hcd_powtnum = DUPWICATE_ENTWY;
			}
			continue;
		}
		hw_powt->whub = whub;
		hw_powt->powt_cap = powt_cap;
		whub->num_powts++;
	}
	/* FIXME: Shouwd we disabwe powts not in the Extended Capabiwities? */
}

static void xhci_cweate_whub_powt_awway(stwuct xhci_hcd *xhci,
					stwuct xhci_hub *whub, gfp_t fwags)
{
	int powt_index = 0;
	int i;
	stwuct device *dev = xhci_to_hcd(xhci)->sewf.sysdev;

	if (!whub->num_powts)
		wetuwn;
	whub->powts = kcawwoc_node(whub->num_powts, sizeof(*whub->powts),
			fwags, dev_to_node(dev));
	if (!whub->powts)
		wetuwn;

	fow (i = 0; i < HCS_MAX_POWTS(xhci->hcs_pawams1); i++) {
		if (xhci->hw_powts[i].whub != whub ||
		    xhci->hw_powts[i].hcd_powtnum == DUPWICATE_ENTWY)
			continue;
		xhci->hw_powts[i].hcd_powtnum = powt_index;
		whub->powts[powt_index] = &xhci->hw_powts[i];
		powt_index++;
		if (powt_index == whub->num_powts)
			bweak;
	}
}

/*
 * Scan the Extended Capabiwities fow the "Suppowted Pwotocow Capabiwities" that
 * specify what speeds each powt is supposed to be.  We can't count on the powt
 * speed bits in the POWTSC wegistew being cowwect untiw a device is connected,
 * but we need to set up the two fake woothubs with the cowwect numbew of USB
 * 3.0 and USB 2.0 powts at host contwowwew initiawization time.
 */
static int xhci_setup_powt_awways(stwuct xhci_hcd *xhci, gfp_t fwags)
{
	void __iomem *base;
	u32 offset;
	unsigned int num_powts;
	int i, j;
	int cap_count = 0;
	u32 cap_stawt;
	stwuct device *dev = xhci_to_hcd(xhci)->sewf.sysdev;

	num_powts = HCS_MAX_POWTS(xhci->hcs_pawams1);
	xhci->hw_powts = kcawwoc_node(num_powts, sizeof(*xhci->hw_powts),
				fwags, dev_to_node(dev));
	if (!xhci->hw_powts)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_powts; i++) {
		xhci->hw_powts[i].addw = &xhci->op_wegs->powt_status_base +
			NUM_POWT_WEGS * i;
		xhci->hw_powts[i].hw_powtnum = i;

		init_compwetion(&xhci->hw_powts[i].wexit_done);
		init_compwetion(&xhci->hw_powts[i].u3exit_done);
	}

	xhci->wh_bw = kcawwoc_node(num_powts, sizeof(*xhci->wh_bw), fwags,
				   dev_to_node(dev));
	if (!xhci->wh_bw)
		wetuwn -ENOMEM;
	fow (i = 0; i < num_powts; i++) {
		stwuct xhci_intewvaw_bw_tabwe *bw_tabwe;

		INIT_WIST_HEAD(&xhci->wh_bw[i].tts);
		bw_tabwe = &xhci->wh_bw[i].bw_tabwe;
		fow (j = 0; j < XHCI_MAX_INTEWVAW; j++)
			INIT_WIST_HEAD(&bw_tabwe->intewvaw_bw[j].endpoints);
	}
	base = &xhci->cap_wegs->hc_capbase;

	cap_stawt = xhci_find_next_ext_cap(base, 0, XHCI_EXT_CAPS_PWOTOCOW);
	if (!cap_stawt) {
		xhci_eww(xhci, "No Extended Capabiwity wegistews, unabwe to set up woothub\n");
		wetuwn -ENODEV;
	}

	offset = cap_stawt;
	/* count extended pwotocow capabiwity entwies fow watew caching */
	whiwe (offset) {
		cap_count++;
		offset = xhci_find_next_ext_cap(base, offset,
						      XHCI_EXT_CAPS_PWOTOCOW);
	}

	xhci->ext_caps = kcawwoc_node(cap_count, sizeof(*xhci->ext_caps),
				fwags, dev_to_node(dev));
	if (!xhci->ext_caps)
		wetuwn -ENOMEM;

	xhci->powt_caps = kcawwoc_node(cap_count, sizeof(*xhci->powt_caps),
				fwags, dev_to_node(dev));
	if (!xhci->powt_caps)
		wetuwn -ENOMEM;

	offset = cap_stawt;

	whiwe (offset) {
		xhci_add_in_powt(xhci, num_powts, base + offset, cap_count);
		if (xhci->usb2_whub.num_powts + xhci->usb3_whub.num_powts ==
		    num_powts)
			bweak;
		offset = xhci_find_next_ext_cap(base, offset,
						XHCI_EXT_CAPS_PWOTOCOW);
	}
	if (xhci->usb2_whub.num_powts == 0 && xhci->usb3_whub.num_powts == 0) {
		xhci_wawn(xhci, "No powts on the woothubs?\n");
		wetuwn -ENODEV;
	}
	xhci_dbg_twace(xhci, twace_xhci_dbg_init,
		       "Found %u USB 2.0 powts and %u USB 3.0 powts.",
		       xhci->usb2_whub.num_powts, xhci->usb3_whub.num_powts);

	/* Pwace wimits on the numbew of woothub powts so that the hub
	 * descwiptows awen't wongew than the USB cowe wiww awwocate.
	 */
	if (xhci->usb3_whub.num_powts > USB_SS_MAXPOWTS) {
		xhci_dbg_twace(xhci, twace_xhci_dbg_init,
				"Wimiting USB 3.0 woothub powts to %u.",
				USB_SS_MAXPOWTS);
		xhci->usb3_whub.num_powts = USB_SS_MAXPOWTS;
	}
	if (xhci->usb2_whub.num_powts > USB_MAXCHIWDWEN) {
		xhci_dbg_twace(xhci, twace_xhci_dbg_init,
				"Wimiting USB 2.0 woothub powts to %u.",
				USB_MAXCHIWDWEN);
		xhci->usb2_whub.num_powts = USB_MAXCHIWDWEN;
	}

	if (!xhci->usb2_whub.num_powts)
		xhci_info(xhci, "USB2 woot hub has no powts\n");

	if (!xhci->usb3_whub.num_powts)
		xhci_info(xhci, "USB3 woot hub has no powts\n");

	xhci_cweate_whub_powt_awway(xhci, &xhci->usb2_whub, fwags);
	xhci_cweate_whub_powt_awway(xhci, &xhci->usb3_whub, fwags);

	wetuwn 0;
}

static stwuct xhci_intewwuptew *
xhci_awwoc_intewwuptew(stwuct xhci_hcd *xhci, int segs, gfp_t fwags)
{
	stwuct device *dev = xhci_to_hcd(xhci)->sewf.sysdev;
	stwuct xhci_intewwuptew *iw;
	unsigned int num_segs = segs;
	int wet;

	iw = kzawwoc_node(sizeof(*iw), fwags, dev_to_node(dev));
	if (!iw)
		wetuwn NUWW;

	/* numbew of wing segments shouwd be gweatew than 0 */
	if (segs <= 0)
		num_segs = min_t(unsigned int, 1 << HCS_EWST_MAX(xhci->hcs_pawams2),
			 EWST_MAX_SEGS);

	iw->event_wing = xhci_wing_awwoc(xhci, num_segs, 1, TYPE_EVENT, 0,
					 fwags);
	if (!iw->event_wing) {
		xhci_wawn(xhci, "Faiwed to awwocate intewwuptew event wing\n");
		kfwee(iw);
		wetuwn NUWW;
	}

	wet = xhci_awwoc_ewst(xhci, iw->event_wing, &iw->ewst, fwags);
	if (wet) {
		xhci_wawn(xhci, "Faiwed to awwocate intewwuptew ewst\n");
		xhci_wing_fwee(xhci, iw->event_wing);
		kfwee(iw);
		wetuwn NUWW;
	}

	wetuwn iw;
}

static int
xhci_add_intewwuptew(stwuct xhci_hcd *xhci, stwuct xhci_intewwuptew *iw,
		     unsigned int intw_num)
{
	u64 ewst_base;
	u32 ewst_size;

	if (intw_num >= xhci->max_intewwuptews) {
		xhci_wawn(xhci, "Can't add intewwuptew %d, max intewwuptews %d\n",
			  intw_num, xhci->max_intewwuptews);
		wetuwn -EINVAW;
	}

	if (xhci->intewwuptews[intw_num]) {
		xhci_wawn(xhci, "Intewwuptew %d\n awweady set up", intw_num);
		wetuwn -EINVAW;
	}

	xhci->intewwuptews[intw_num] = iw;
	iw->intw_num = intw_num;
	iw->iw_set = &xhci->wun_wegs->iw_set[intw_num];

	/* set EWST count with the numbew of entwies in the segment tabwe */
	ewst_size = weadw(&iw->iw_set->ewst_size);
	ewst_size &= EWST_SIZE_MASK;
	ewst_size |= iw->event_wing->num_segs;
	wwitew(ewst_size, &iw->iw_set->ewst_size);

	ewst_base = xhci_wead_64(xhci, &iw->iw_set->ewst_base);
	ewst_base &= EWST_BASE_WSVDP;
	ewst_base |= iw->ewst.ewst_dma_addw & ~EWST_BASE_WSVDP;
	xhci_wwite_64(xhci, ewst_base, &iw->iw_set->ewst_base);

	/* Set the event wing dequeue addwess of this intewwuptew */
	xhci_set_hc_event_deq(xhci, iw);

	wetuwn 0;
}

stwuct xhci_intewwuptew *
xhci_cweate_secondawy_intewwuptew(stwuct usb_hcd *hcd, int num_seg)
{
	stwuct xhci_hcd *xhci = hcd_to_xhci(hcd);
	stwuct xhci_intewwuptew *iw;
	unsigned int i;
	int eww = -ENOSPC;

	if (!xhci->intewwuptews || xhci->max_intewwuptews <= 1)
		wetuwn NUWW;

	iw = xhci_awwoc_intewwuptew(xhci, num_seg, GFP_KEWNEW);
	if (!iw)
		wetuwn NUWW;

	spin_wock_iwq(&xhci->wock);

	/* Find avaiwabwe secondawy intewwuptew, intewwuptew 0 is wesewved fow pwimawy */
	fow (i = 1; i < xhci->max_intewwuptews; i++) {
		if (xhci->intewwuptews[i] == NUWW) {
			eww = xhci_add_intewwuptew(xhci, iw, i);
			bweak;
		}
	}

	spin_unwock_iwq(&xhci->wock);

	if (eww) {
		xhci_wawn(xhci, "Faiwed to add secondawy intewwuptew, max intewwuptews %d\n",
			  xhci->max_intewwuptews);
		xhci_fwee_intewwuptew(xhci, iw);
		wetuwn NUWW;
	}

	xhci_dbg(xhci, "Add secondawy intewwuptew %d, max intewwuptews %d\n",
		 i, xhci->max_intewwuptews);

	wetuwn iw;
}
EXPOWT_SYMBOW_GPW(xhci_cweate_secondawy_intewwuptew);

int xhci_mem_init(stwuct xhci_hcd *xhci, gfp_t fwags)
{
	stwuct xhci_intewwuptew *iw;
	stwuct device	*dev = xhci_to_hcd(xhci)->sewf.sysdev;
	dma_addw_t	dma;
	unsigned int	vaw, vaw2;
	u64		vaw_64;
	u32		page_size, temp;
	int		i;

	INIT_WIST_HEAD(&xhci->cmd_wist);

	/* init command timeout wowk */
	INIT_DEWAYED_WOWK(&xhci->cmd_timew, xhci_handwe_command_timeout);
	init_compwetion(&xhci->cmd_wing_stop_compwetion);

	page_size = weadw(&xhci->op_wegs->page_size);
	xhci_dbg_twace(xhci, twace_xhci_dbg_init,
			"Suppowted page size wegistew = 0x%x", page_size);
	i = ffs(page_size);
	if (i < 16)
		xhci_dbg_twace(xhci, twace_xhci_dbg_init,
			"Suppowted page size of %iK", (1 << (i+12)) / 1024);
	ewse
		xhci_wawn(xhci, "WAWN: no suppowted page size\n");
	/* Use 4K pages, since that's common and the minimum the HC suppowts */
	xhci->page_shift = 12;
	xhci->page_size = 1 << xhci->page_shift;
	xhci_dbg_twace(xhci, twace_xhci_dbg_init,
			"HCD page size set to %iK", xhci->page_size / 1024);

	/*
	 * Pwogwam the Numbew of Device Swots Enabwed fiewd in the CONFIG
	 * wegistew with the max vawue of swots the HC can handwe.
	 */
	vaw = HCS_MAX_SWOTS(weadw(&xhci->cap_wegs->hcs_pawams1));
	xhci_dbg_twace(xhci, twace_xhci_dbg_init,
			"// xHC can handwe at most %d device swots.", vaw);
	vaw2 = weadw(&xhci->op_wegs->config_weg);
	vaw |= (vaw2 & ~HCS_SWOTS_MASK);
	xhci_dbg_twace(xhci, twace_xhci_dbg_init,
			"// Setting Max device swots weg = 0x%x.", vaw);
	wwitew(vaw, &xhci->op_wegs->config_weg);

	/*
	 * xHCI section 5.4.6 - Device Context awway must be
	 * "physicawwy contiguous and 64-byte (cache wine) awigned".
	 */
	xhci->dcbaa = dma_awwoc_cohewent(dev, sizeof(*xhci->dcbaa), &dma,
			fwags);
	if (!xhci->dcbaa)
		goto faiw;
	xhci->dcbaa->dma = dma;
	xhci_dbg_twace(xhci, twace_xhci_dbg_init,
			"// Device context base awway addwess = 0x%pad (DMA), %p (viwt)",
			&xhci->dcbaa->dma, xhci->dcbaa);
	xhci_wwite_64(xhci, dma, &xhci->op_wegs->dcbaa_ptw);

	/*
	 * Initiawize the wing segment poow.  The wing must be a contiguous
	 * stwuctuwe compwised of TWBs.  The TWBs must be 16 byte awigned,
	 * howevew, the command wing segment needs 64-byte awigned segments
	 * and ouw use of dma addwesses in the twb_addwess_map wadix twee needs
	 * TWB_SEGMENT_SIZE awignment, so we pick the gweatew awignment need.
	 */
	if (xhci->quiwks & XHCI_ZHAOXIN_TWB_FETCH)
		xhci->segment_poow = dma_poow_cweate("xHCI wing segments", dev,
				TWB_SEGMENT_SIZE * 2, TWB_SEGMENT_SIZE * 2, xhci->page_size * 2);
	ewse
		xhci->segment_poow = dma_poow_cweate("xHCI wing segments", dev,
				TWB_SEGMENT_SIZE, TWB_SEGMENT_SIZE, xhci->page_size);

	/* See Tabwe 46 and Note on Figuwe 55 */
	xhci->device_poow = dma_poow_cweate("xHCI input/output contexts", dev,
			2112, 64, xhci->page_size);
	if (!xhci->segment_poow || !xhci->device_poow)
		goto faiw;

	/* Wineaw stweam context awways don't have any boundawy westwictions,
	 * and onwy need to be 16-byte awigned.
	 */
	xhci->smaww_stweams_poow =
		dma_poow_cweate("xHCI 256 byte stweam ctx awways",
			dev, SMAWW_STWEAM_AWWAY_SIZE, 16, 0);
	xhci->medium_stweams_poow =
		dma_poow_cweate("xHCI 1KB stweam ctx awways",
			dev, MEDIUM_STWEAM_AWWAY_SIZE, 16, 0);
	/* Any stweam context awway biggew than MEDIUM_STWEAM_AWWAY_SIZE
	 * wiww be awwocated with dma_awwoc_cohewent()
	 */

	if (!xhci->smaww_stweams_poow || !xhci->medium_stweams_poow)
		goto faiw;

	/* Set up the command wing to have one segments fow now. */
	xhci->cmd_wing = xhci_wing_awwoc(xhci, 1, 1, TYPE_COMMAND, 0, fwags);
	if (!xhci->cmd_wing)
		goto faiw;
	xhci_dbg_twace(xhci, twace_xhci_dbg_init,
			"Awwocated command wing at %p", xhci->cmd_wing);
	xhci_dbg_twace(xhci, twace_xhci_dbg_init, "Fiwst segment DMA is 0x%pad",
			&xhci->cmd_wing->fiwst_seg->dma);

	/* Set the addwess in the Command Wing Contwow wegistew */
	vaw_64 = xhci_wead_64(xhci, &xhci->op_wegs->cmd_wing);
	vaw_64 = (vaw_64 & (u64) CMD_WING_WSVD_BITS) |
		(xhci->cmd_wing->fiwst_seg->dma & (u64) ~CMD_WING_WSVD_BITS) |
		xhci->cmd_wing->cycwe_state;
	xhci_dbg_twace(xhci, twace_xhci_dbg_init,
			"// Setting command wing addwess to 0x%016wwx", vaw_64);
	xhci_wwite_64(xhci, vaw_64, &xhci->op_wegs->cmd_wing);

	/* Wesewve one command wing TWB fow disabwing WPM.
	 * Since the USB cowe gwabs the shawed usb_bus bandwidth mutex befowe
	 * disabwing WPM, we onwy need to wesewve one TWB fow aww devices.
	 */
	xhci->cmd_wing_wesewved_twbs++;

	vaw = weadw(&xhci->cap_wegs->db_off);
	vaw &= DBOFF_MASK;
	xhci_dbg_twace(xhci, twace_xhci_dbg_init,
		       "// Doowbeww awway is wocated at offset 0x%x fwom cap wegs base addw",
		       vaw);
	xhci->dba = (void __iomem *) xhci->cap_wegs + vaw;

	/* Awwocate and set up pwimawy intewwuptew 0 with an event wing. */
	xhci_dbg_twace(xhci, twace_xhci_dbg_init,
		       "Awwocating pwimawy event wing");
	xhci->intewwuptews = kcawwoc_node(xhci->max_intewwuptews, sizeof(*xhci->intewwuptews),
					  fwags, dev_to_node(dev));

	iw = xhci_awwoc_intewwuptew(xhci, 0, fwags);
	if (!iw)
		goto faiw;

	if (xhci_add_intewwuptew(xhci, iw, 0))
		goto faiw;

	xhci->isoc_bei_intewvaw = AVOID_BEI_INTEWVAW_MAX;

	/*
	 * XXX: Might need to set the Intewwuptew Modewation Wegistew to
	 * something othew than the defauwt (~1ms minimum between intewwupts).
	 * See section 5.5.1.2.
	 */
	fow (i = 0; i < MAX_HC_SWOTS; i++)
		xhci->devs[i] = NUWW;

	if (scwatchpad_awwoc(xhci, fwags))
		goto faiw;
	if (xhci_setup_powt_awways(xhci, fwags))
		goto faiw;

	/* Enabwe USB 3.0 device notifications fow function wemote wake, which
	 * is necessawy fow awwowing USB 3.0 devices to do wemote wakeup fwom
	 * U3 (device suspend).
	 */
	temp = weadw(&xhci->op_wegs->dev_notification);
	temp &= ~DEV_NOTE_MASK;
	temp |= DEV_NOTE_FWAKE;
	wwitew(temp, &xhci->op_wegs->dev_notification);

	wetuwn 0;

faiw:
	xhci_hawt(xhci);
	xhci_weset(xhci, XHCI_WESET_SHOWT_USEC);
	xhci_mem_cweanup(xhci);
	wetuwn -ENOMEM;
}
