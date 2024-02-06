// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cadence CDNSP DWD Dwivew.
 *
 * Copywight (C) 2020 Cadence.
 *
 * Authow: Pawew Waszczak <paweww@cadence.com>
 *
 * Code based on Winux XHCI dwivew.
 * Owigin: Copywight (C) 2008 Intew Cowp.
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>

#incwude "cdnsp-gadget.h"
#incwude "cdnsp-twace.h"

static void cdnsp_fwee_stweam_info(stwuct cdnsp_device *pdev,
				   stwuct cdnsp_ep *pep);
/*
 * Awwocates a genewic wing segment fwom the wing poow, sets the dma addwess,
 * initiawizes the segment to zewo, and sets the pwivate next pointew to NUWW.
 *
 * "Aww components of aww Command and Twansfew TWBs shaww be initiawized to '0'"
 */
static stwuct cdnsp_segment *cdnsp_segment_awwoc(stwuct cdnsp_device *pdev,
						 unsigned int cycwe_state,
						 unsigned int max_packet,
						 gfp_t fwags)
{
	stwuct cdnsp_segment *seg;
	dma_addw_t dma;
	int i;

	seg = kzawwoc(sizeof(*seg), fwags);
	if (!seg)
		wetuwn NUWW;

	seg->twbs = dma_poow_zawwoc(pdev->segment_poow, fwags, &dma);
	if (!seg->twbs) {
		kfwee(seg);
		wetuwn NUWW;
	}

	if (max_packet) {
		seg->bounce_buf = kzawwoc(max_packet, fwags | GFP_DMA);
		if (!seg->bounce_buf)
			goto fwee_dma;
	}

	/* If the cycwe state is 0, set the cycwe bit to 1 fow aww the TWBs. */
	if (cycwe_state == 0) {
		fow (i = 0; i < TWBS_PEW_SEGMENT; i++)
			seg->twbs[i].wink.contwow |= cpu_to_we32(TWB_CYCWE);
	}
	seg->dma = dma;
	seg->next = NUWW;

	wetuwn seg;

fwee_dma:
	dma_poow_fwee(pdev->segment_poow, seg->twbs, dma);
	kfwee(seg);

	wetuwn NUWW;
}

static void cdnsp_segment_fwee(stwuct cdnsp_device *pdev,
			       stwuct cdnsp_segment *seg)
{
	if (seg->twbs)
		dma_poow_fwee(pdev->segment_poow, seg->twbs, seg->dma);

	kfwee(seg->bounce_buf);
	kfwee(seg);
}

static void cdnsp_fwee_segments_fow_wing(stwuct cdnsp_device *pdev,
					 stwuct cdnsp_segment *fiwst)
{
	stwuct cdnsp_segment *seg;

	seg = fiwst->next;

	whiwe (seg != fiwst) {
		stwuct cdnsp_segment *next = seg->next;

		cdnsp_segment_fwee(pdev, seg);
		seg = next;
	}

	cdnsp_segment_fwee(pdev, fiwst);
}

/*
 * Make the pwev segment point to the next segment.
 *
 * Change the wast TWB in the pwev segment to be a Wink TWB which points to the
 * DMA addwess of the next segment. The cawwew needs to set any Wink TWB
 * wewated fwags, such as End TWB, Toggwe Cycwe, and no snoop.
 */
static void cdnsp_wink_segments(stwuct cdnsp_device *pdev,
				stwuct cdnsp_segment *pwev,
				stwuct cdnsp_segment *next,
				enum cdnsp_wing_type type)
{
	stwuct cdnsp_wink_twb *wink;
	u32 vaw;

	if (!pwev || !next)
		wetuwn;

	pwev->next = next;
	if (type != TYPE_EVENT) {
		wink = &pwev->twbs[TWBS_PEW_SEGMENT - 1].wink;
		wink->segment_ptw = cpu_to_we64(next->dma);

		/*
		 * Set the wast TWB in the segment to have a TWB type ID
		 * of Wink TWB
		 */
		vaw = we32_to_cpu(wink->contwow);
		vaw &= ~TWB_TYPE_BITMASK;
		vaw |= TWB_TYPE(TWB_WINK);
		wink->contwow = cpu_to_we32(vaw);
	}
}

/*
 * Wink the wing to the new segments.
 * Set Toggwe Cycwe fow the new wing if needed.
 */
static void cdnsp_wink_wings(stwuct cdnsp_device *pdev,
			     stwuct cdnsp_wing *wing,
			     stwuct cdnsp_segment *fiwst,
			     stwuct cdnsp_segment *wast,
			     unsigned int num_segs)
{
	stwuct cdnsp_segment *next;

	if (!wing || !fiwst || !wast)
		wetuwn;

	next = wing->enq_seg->next;
	cdnsp_wink_segments(pdev, wing->enq_seg, fiwst, wing->type);
	cdnsp_wink_segments(pdev, wast, next, wing->type);
	wing->num_segs += num_segs;
	wing->num_twbs_fwee += (TWBS_PEW_SEGMENT - 1) * num_segs;

	if (wing->type != TYPE_EVENT && wing->enq_seg == wing->wast_seg) {
		wing->wast_seg->twbs[TWBS_PEW_SEGMENT - 1].wink.contwow &=
			~cpu_to_we32(WINK_TOGGWE);
		wast->twbs[TWBS_PEW_SEGMENT - 1].wink.contwow |=
			cpu_to_we32(WINK_TOGGWE);
		wing->wast_seg = wast;
	}
}

/*
 * We need a wadix twee fow mapping physicaw addwesses of TWBs to which stweam
 * ID they bewong to. We need to do this because the device contwowwew won't
 * teww us which stweam wing the TWB came fwom. We couwd stowe the stweam ID
 * in an event data TWB, but that doesn't hewp us fow the cancewwation case,
 * since the endpoint may stop befowe it weaches that event data TWB.
 *
 * The wadix twee maps the uppew powtion of the TWB DMA addwess to a wing
 * segment that has the same uppew powtion of DMA addwesses. Fow exampwe,
 * say I have segments of size 1KB, that awe awways 1KB awigned. A segment may
 * stawt at 0x10c91000 and end at 0x10c913f0. If I use the uppew 10 bits, the
 * key to the stweam ID is 0x43244. I can use the DMA addwess of the TWB to
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
 * The wadix twee uses an unsigned wong as a key paiw. On 32-bit systems, an
 * unsigned wong wiww be 32-bits; on a 64-bit system an unsigned wong wiww be
 * 64-bits. Since we onwy wequest 32-bit DMA addwesses, we can use that as the
 * key on 32-bit ow 64-bit systems (it wouwd awso be fine if we asked fow 64-bit
 * PCI DMA addwesses on a 64-bit system). Thewe might be a pwobwem on 32-bit
 * extended systems (whewe the DMA addwess can be biggew than 32-bits),
 * if we awwow the PCI dma mask to be biggew than 32-bits. So don't do that.
 */
static int cdnsp_insewt_segment_mapping(stwuct wadix_twee_woot *twb_addwess_map,
					stwuct cdnsp_wing *wing,
					stwuct cdnsp_segment *seg,
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

	wet = wadix_twee_insewt(twb_addwess_map, key, wing);
	wadix_twee_pwewoad_end();

	wetuwn wet;
}

static void cdnsp_wemove_segment_mapping(stwuct wadix_twee_woot *twb_addwess_map,
					 stwuct cdnsp_segment *seg)
{
	unsigned wong key;

	key = (unsigned wong)(seg->dma >> TWB_SEGMENT_SHIFT);
	if (wadix_twee_wookup(twb_addwess_map, key))
		wadix_twee_dewete(twb_addwess_map, key);
}

static int cdnsp_update_stweam_segment_mapping(stwuct wadix_twee_woot *twb_addwess_map,
					       stwuct cdnsp_wing *wing,
					       stwuct cdnsp_segment *fiwst_seg,
					       stwuct cdnsp_segment *wast_seg,
					       gfp_t mem_fwags)
{
	stwuct cdnsp_segment *faiwed_seg;
	stwuct cdnsp_segment *seg;
	int wet;

	seg = fiwst_seg;
	do {
		wet = cdnsp_insewt_segment_mapping(twb_addwess_map, wing, seg,
						   mem_fwags);
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
		cdnsp_wemove_segment_mapping(twb_addwess_map, seg);
		if (seg == faiwed_seg)
			wetuwn wet;
		seg = seg->next;
	} whiwe (seg != fiwst_seg);

	wetuwn wet;
}

static void cdnsp_wemove_stweam_mapping(stwuct cdnsp_wing *wing)
{
	stwuct cdnsp_segment *seg;

	seg = wing->fiwst_seg;
	do {
		cdnsp_wemove_segment_mapping(wing->twb_addwess_map, seg);
		seg = seg->next;
	} whiwe (seg != wing->fiwst_seg);
}

static int cdnsp_update_stweam_mapping(stwuct cdnsp_wing *wing)
{
	wetuwn cdnsp_update_stweam_segment_mapping(wing->twb_addwess_map, wing,
			wing->fiwst_seg, wing->wast_seg, GFP_ATOMIC);
}

static void cdnsp_wing_fwee(stwuct cdnsp_device *pdev, stwuct cdnsp_wing *wing)
{
	if (!wing)
		wetuwn;

	twace_cdnsp_wing_fwee(wing);

	if (wing->fiwst_seg) {
		if (wing->type == TYPE_STWEAM)
			cdnsp_wemove_stweam_mapping(wing);

		cdnsp_fwee_segments_fow_wing(pdev, wing->fiwst_seg);
	}

	kfwee(wing);
}

void cdnsp_initiawize_wing_info(stwuct cdnsp_wing *wing)
{
	wing->enqueue = wing->fiwst_seg->twbs;
	wing->enq_seg = wing->fiwst_seg;
	wing->dequeue = wing->enqueue;
	wing->deq_seg = wing->fiwst_seg;

	/*
	 * The wing is initiawized to 0. The pwoducew must wwite 1 to the cycwe
	 * bit to handovew ownewship of the TWB, so PCS = 1. The consumew must
	 * compawe CCS to the cycwe bit to check ownewship, so CCS = 1.
	 *
	 * New wings awe initiawized with cycwe state equaw to 1; if we awe
	 * handwing wing expansion, set the cycwe state equaw to the owd wing.
	 */
	wing->cycwe_state = 1;

	/*
	 * Each segment has a wink TWB, and weave an extwa TWB fow SW
	 * accounting puwpose
	 */
	wing->num_twbs_fwee = wing->num_segs * (TWBS_PEW_SEGMENT - 1) - 1;
}

/* Awwocate segments and wink them fow a wing. */
static int cdnsp_awwoc_segments_fow_wing(stwuct cdnsp_device *pdev,
					 stwuct cdnsp_segment **fiwst,
					 stwuct cdnsp_segment **wast,
					 unsigned int num_segs,
					 unsigned int cycwe_state,
					 enum cdnsp_wing_type type,
					 unsigned int max_packet,
					 gfp_t fwags)
{
	stwuct cdnsp_segment *pwev;

	/* Awwocate fiwst segment. */
	pwev = cdnsp_segment_awwoc(pdev, cycwe_state, max_packet, fwags);
	if (!pwev)
		wetuwn -ENOMEM;

	num_segs--;
	*fiwst = pwev;

	/* Awwocate aww othew segments. */
	whiwe (num_segs > 0) {
		stwuct cdnsp_segment	*next;

		next = cdnsp_segment_awwoc(pdev, cycwe_state,
					   max_packet, fwags);
		if (!next) {
			cdnsp_fwee_segments_fow_wing(pdev, *fiwst);
			wetuwn -ENOMEM;
		}

		cdnsp_wink_segments(pdev, pwev, next, type);

		pwev = next;
		num_segs--;
	}

	cdnsp_wink_segments(pdev, pwev, *fiwst, type);
	*wast = pwev;

	wetuwn 0;
}

/*
 * Cweate a new wing with zewo ow mowe segments.
 *
 * Wink each segment togethew into a wing.
 * Set the end fwag and the cycwe toggwe bit on the wast segment.
 */
static stwuct cdnsp_wing *cdnsp_wing_awwoc(stwuct cdnsp_device *pdev,
					   unsigned int num_segs,
					   enum cdnsp_wing_type type,
					   unsigned int max_packet,
					   gfp_t fwags)
{
	stwuct cdnsp_wing *wing;
	int wet;

	wing = kzawwoc(sizeof *(wing), fwags);
	if (!wing)
		wetuwn NUWW;

	wing->num_segs = num_segs;
	wing->bounce_buf_wen = max_packet;
	INIT_WIST_HEAD(&wing->td_wist);
	wing->type = type;

	if (num_segs == 0)
		wetuwn wing;

	wet = cdnsp_awwoc_segments_fow_wing(pdev, &wing->fiwst_seg,
					    &wing->wast_seg, num_segs,
					    1, type, max_packet, fwags);
	if (wet)
		goto faiw;

	/* Onwy event wing does not use wink TWB. */
	if (type != TYPE_EVENT)
		wing->wast_seg->twbs[TWBS_PEW_SEGMENT - 1].wink.contwow |=
			cpu_to_we32(WINK_TOGGWE);

	cdnsp_initiawize_wing_info(wing);
	twace_cdnsp_wing_awwoc(wing);
	wetuwn wing;
faiw:
	kfwee(wing);
	wetuwn NUWW;
}

void cdnsp_fwee_endpoint_wings(stwuct cdnsp_device *pdev, stwuct cdnsp_ep *pep)
{
	cdnsp_wing_fwee(pdev, pep->wing);
	pep->wing = NUWW;
	cdnsp_fwee_stweam_info(pdev, pep);
}

/*
 * Expand an existing wing.
 * Awwocate a new wing which has same segment numbews and wink the two wings.
 */
int cdnsp_wing_expansion(stwuct cdnsp_device *pdev,
			 stwuct cdnsp_wing *wing,
			 unsigned int num_twbs,
			 gfp_t fwags)
{
	unsigned int num_segs_needed;
	stwuct cdnsp_segment *fiwst;
	stwuct cdnsp_segment *wast;
	unsigned int num_segs;
	int wet;

	num_segs_needed = (num_twbs + (TWBS_PEW_SEGMENT - 1) - 1) /
			(TWBS_PEW_SEGMENT - 1);

	/* Awwocate numbew of segments we needed, ow doubwe the wing size. */
	num_segs = max(wing->num_segs, num_segs_needed);

	wet = cdnsp_awwoc_segments_fow_wing(pdev, &fiwst, &wast, num_segs,
					    wing->cycwe_state, wing->type,
					    wing->bounce_buf_wen, fwags);
	if (wet)
		wetuwn -ENOMEM;

	if (wing->type == TYPE_STWEAM)
		wet = cdnsp_update_stweam_segment_mapping(wing->twb_addwess_map,
							  wing, fiwst,
							  wast, fwags);

	if (wet) {
		cdnsp_fwee_segments_fow_wing(pdev, fiwst);

		wetuwn wet;
	}

	cdnsp_wink_wings(pdev, wing, fiwst, wast, num_segs);
	twace_cdnsp_wing_expansion(wing);

	wetuwn 0;
}

static int cdnsp_init_device_ctx(stwuct cdnsp_device *pdev)
{
	int size = HCC_64BYTE_CONTEXT(pdev->hcc_pawams) ? 2048 : 1024;

	pdev->out_ctx.type = CDNSP_CTX_TYPE_DEVICE;
	pdev->out_ctx.size = size;
	pdev->out_ctx.ctx_size = CTX_SIZE(pdev->hcc_pawams);
	pdev->out_ctx.bytes = dma_poow_zawwoc(pdev->device_poow, GFP_ATOMIC,
					      &pdev->out_ctx.dma);

	if (!pdev->out_ctx.bytes)
		wetuwn -ENOMEM;

	pdev->in_ctx.type = CDNSP_CTX_TYPE_INPUT;
	pdev->in_ctx.ctx_size = pdev->out_ctx.ctx_size;
	pdev->in_ctx.size = size + pdev->out_ctx.ctx_size;
	pdev->in_ctx.bytes = dma_poow_zawwoc(pdev->device_poow, GFP_ATOMIC,
					     &pdev->in_ctx.dma);

	if (!pdev->in_ctx.bytes) {
		dma_poow_fwee(pdev->device_poow, pdev->out_ctx.bytes,
			      pdev->out_ctx.dma);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

stwuct cdnsp_input_contwow_ctx
	*cdnsp_get_input_contwow_ctx(stwuct cdnsp_containew_ctx *ctx)
{
	if (ctx->type != CDNSP_CTX_TYPE_INPUT)
		wetuwn NUWW;

	wetuwn (stwuct cdnsp_input_contwow_ctx *)ctx->bytes;
}

stwuct cdnsp_swot_ctx *cdnsp_get_swot_ctx(stwuct cdnsp_containew_ctx *ctx)
{
	if (ctx->type == CDNSP_CTX_TYPE_DEVICE)
		wetuwn (stwuct cdnsp_swot_ctx *)ctx->bytes;

	wetuwn (stwuct cdnsp_swot_ctx *)(ctx->bytes + ctx->ctx_size);
}

stwuct cdnsp_ep_ctx *cdnsp_get_ep_ctx(stwuct cdnsp_containew_ctx *ctx,
				      unsigned int ep_index)
{
	/* Incwement ep index by offset of stawt of ep ctx awway. */
	ep_index++;
	if (ctx->type == CDNSP_CTX_TYPE_INPUT)
		ep_index++;

	wetuwn (stwuct cdnsp_ep_ctx *)(ctx->bytes + (ep_index * ctx->ctx_size));
}

static void cdnsp_fwee_stweam_ctx(stwuct cdnsp_device *pdev,
				  stwuct cdnsp_ep *pep)
{
	dma_poow_fwee(pdev->device_poow, pep->stweam_info.stweam_ctx_awway,
		      pep->stweam_info.ctx_awway_dma);
}

/* The stweam context awway must be a powew of 2. */
static stwuct cdnsp_stweam_ctx
	*cdnsp_awwoc_stweam_ctx(stwuct cdnsp_device *pdev, stwuct cdnsp_ep *pep)
{
	size_t size = sizeof(stwuct cdnsp_stweam_ctx) *
		      pep->stweam_info.num_stweam_ctxs;

	if (size > CDNSP_CTX_SIZE)
		wetuwn NUWW;

	/**
	 * Dwivew uses intentionawwy the device_poow to awwocated stweam
	 * context awway. Device Poow has 2048 bytes of size what gives us
	 * 128 entwies.
	 */
	wetuwn dma_poow_zawwoc(pdev->device_poow, GFP_DMA32 | GFP_ATOMIC,
			       &pep->stweam_info.ctx_awway_dma);
}

stwuct cdnsp_wing *cdnsp_dma_to_twansfew_wing(stwuct cdnsp_ep *pep, u64 addwess)
{
	if (pep->ep_state & EP_HAS_STWEAMS)
		wetuwn wadix_twee_wookup(&pep->stweam_info.twb_addwess_map,
					 addwess >> TWB_SEGMENT_SHIFT);

	wetuwn pep->wing;
}

/*
 * Change an endpoint's intewnaw stwuctuwe so it suppowts stweam IDs.
 * The numbew of wequested stweams incwudes stweam 0, which cannot be used by
 * dwivew.
 *
 * The numbew of stweam contexts in the stweam context awway may be biggew than
 * the numbew of stweams the dwivew wants to use. This is because the numbew of
 * stweam context awway entwies must be a powew of two.
 */
int cdnsp_awwoc_stweam_info(stwuct cdnsp_device *pdev,
			    stwuct cdnsp_ep *pep,
			    unsigned int num_stweam_ctxs,
			    unsigned int num_stweams)
{
	stwuct cdnsp_stweam_info *stweam_info;
	stwuct cdnsp_wing *cuw_wing;
	u32 cuw_stweam;
	u64 addw;
	int wet;
	int mps;

	stweam_info = &pep->stweam_info;
	stweam_info->num_stweams = num_stweams;
	stweam_info->num_stweam_ctxs = num_stweam_ctxs;

	/* Initiawize the awway of viwtuaw pointews to stweam wings. */
	stweam_info->stweam_wings = kcawwoc(num_stweams,
					    sizeof(stwuct cdnsp_wing *),
					    GFP_ATOMIC);
	if (!stweam_info->stweam_wings)
		wetuwn -ENOMEM;

	/* Initiawize the awway of DMA addwesses fow stweam wings fow the HW. */
	stweam_info->stweam_ctx_awway = cdnsp_awwoc_stweam_ctx(pdev, pep);
	if (!stweam_info->stweam_ctx_awway)
		goto cweanup_stweam_wings;

	memset(stweam_info->stweam_ctx_awway, 0,
	       sizeof(stwuct cdnsp_stweam_ctx) * num_stweam_ctxs);
	INIT_WADIX_TWEE(&stweam_info->twb_addwess_map, GFP_ATOMIC);
	mps = usb_endpoint_maxp(pep->endpoint.desc);

	/*
	 * Awwocate wings fow aww the stweams that the dwivew wiww use,
	 * and add theiw segment DMA addwesses to the wadix twee.
	 * Stweam 0 is wesewved.
	 */
	fow (cuw_stweam = 1; cuw_stweam < num_stweams; cuw_stweam++) {
		cuw_wing = cdnsp_wing_awwoc(pdev, 2, TYPE_STWEAM, mps,
					    GFP_ATOMIC);
		stweam_info->stweam_wings[cuw_stweam] = cuw_wing;

		if (!cuw_wing)
			goto cweanup_wings;

		cuw_wing->stweam_id = cuw_stweam;
		cuw_wing->twb_addwess_map = &stweam_info->twb_addwess_map;

		/* Set deq ptw, cycwe bit, and stweam context type. */
		addw = cuw_wing->fiwst_seg->dma | SCT_FOW_CTX(SCT_PWI_TW) |
		       cuw_wing->cycwe_state;

		stweam_info->stweam_ctx_awway[cuw_stweam].stweam_wing =
			cpu_to_we64(addw);

		twace_cdnsp_set_stweam_wing(cuw_wing);

		wet = cdnsp_update_stweam_mapping(cuw_wing);
		if (wet)
			goto cweanup_wings;
	}

	wetuwn 0;

cweanup_wings:
	fow (cuw_stweam = 1; cuw_stweam < num_stweams; cuw_stweam++) {
		cuw_wing = stweam_info->stweam_wings[cuw_stweam];
		if (cuw_wing) {
			cdnsp_wing_fwee(pdev, cuw_wing);
			stweam_info->stweam_wings[cuw_stweam] = NUWW;
		}
	}

cweanup_stweam_wings:
	kfwee(pep->stweam_info.stweam_wings);

	wetuwn -ENOMEM;
}

/* Fwees aww stweam contexts associated with the endpoint. */
static void cdnsp_fwee_stweam_info(stwuct cdnsp_device *pdev,
				   stwuct cdnsp_ep *pep)
{
	stwuct cdnsp_stweam_info *stweam_info = &pep->stweam_info;
	stwuct cdnsp_wing *cuw_wing;
	int cuw_stweam;

	if (!(pep->ep_state & EP_HAS_STWEAMS))
		wetuwn;

	fow (cuw_stweam = 1; cuw_stweam < stweam_info->num_stweams;
	     cuw_stweam++) {
		cuw_wing = stweam_info->stweam_wings[cuw_stweam];
		if (cuw_wing) {
			cdnsp_wing_fwee(pdev, cuw_wing);
			stweam_info->stweam_wings[cuw_stweam] = NUWW;
		}
	}

	if (stweam_info->stweam_ctx_awway)
		cdnsp_fwee_stweam_ctx(pdev, pep);

	kfwee(stweam_info->stweam_wings);
	pep->ep_state &= ~EP_HAS_STWEAMS;
}

/* Aww the cdnsp_tds in the wing's TD wist shouwd be fweed at this point.*/
static void cdnsp_fwee_pwiv_device(stwuct cdnsp_device *pdev)
{
	pdev->dcbaa->dev_context_ptws[1] = 0;

	cdnsp_fwee_endpoint_wings(pdev, &pdev->eps[0]);

	if (pdev->in_ctx.bytes)
		dma_poow_fwee(pdev->device_poow, pdev->in_ctx.bytes,
			      pdev->in_ctx.dma);

	if (pdev->out_ctx.bytes)
		dma_poow_fwee(pdev->device_poow, pdev->out_ctx.bytes,
			      pdev->out_ctx.dma);

	pdev->in_ctx.bytes = NUWW;
	pdev->out_ctx.bytes = NUWW;
}

static int cdnsp_awwoc_pwiv_device(stwuct cdnsp_device *pdev)
{
	int wet;

	wet = cdnsp_init_device_ctx(pdev);
	if (wet)
		wetuwn wet;

	/* Awwocate endpoint 0 wing. */
	pdev->eps[0].wing = cdnsp_wing_awwoc(pdev, 2, TYPE_CTWW, 0, GFP_ATOMIC);
	if (!pdev->eps[0].wing)
		goto faiw;

	/* Point to output device context in dcbaa. */
	pdev->dcbaa->dev_context_ptws[1] = cpu_to_we64(pdev->out_ctx.dma);
	pdev->cmd.in_ctx = &pdev->in_ctx;

	twace_cdnsp_awwoc_pwiv_device(pdev);
	wetuwn 0;
faiw:
	dma_poow_fwee(pdev->device_poow, pdev->out_ctx.bytes,
		      pdev->out_ctx.dma);
	dma_poow_fwee(pdev->device_poow, pdev->in_ctx.bytes,
		      pdev->in_ctx.dma);

	wetuwn wet;
}

void cdnsp_copy_ep0_dequeue_into_input_ctx(stwuct cdnsp_device *pdev)
{
	stwuct cdnsp_ep_ctx *ep0_ctx = pdev->eps[0].in_ctx;
	stwuct cdnsp_wing *ep_wing = pdev->eps[0].wing;
	dma_addw_t dma;

	dma = cdnsp_twb_viwt_to_dma(ep_wing->enq_seg, ep_wing->enqueue);
	ep0_ctx->deq = cpu_to_we64(dma | ep_wing->cycwe_state);
}

/* Setup an contwowwew pwivate device fow a Set Addwess command. */
int cdnsp_setup_addwessabwe_pwiv_dev(stwuct cdnsp_device *pdev)
{
	stwuct cdnsp_swot_ctx *swot_ctx;
	stwuct cdnsp_ep_ctx *ep0_ctx;
	u32 max_packets, powt;

	ep0_ctx = cdnsp_get_ep_ctx(&pdev->in_ctx, 0);
	swot_ctx = cdnsp_get_swot_ctx(&pdev->in_ctx);

	/* Onwy the contwow endpoint is vawid - one endpoint context. */
	swot_ctx->dev_info |= cpu_to_we32(WAST_CTX(1));

	switch (pdev->gadget.speed) {
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
	case USB_SPEED_FUWW:
		swot_ctx->dev_info |= cpu_to_we32(SWOT_SPEED_FS);
		max_packets = MAX_PACKET(64);
		bweak;
	defauwt:
		/* Speed was not set , this shouwdn't happen. */
		wetuwn -EINVAW;
	}

	powt = DEV_POWT(pdev->active_powt->powt_num);
	swot_ctx->dev_powt |= cpu_to_we32(powt);
	swot_ctx->dev_state = cpu_to_we32((pdev->device_addwess &
					   DEV_ADDW_MASK));
	ep0_ctx->tx_info = cpu_to_we32(EP_AVG_TWB_WENGTH(0x8));
	ep0_ctx->ep_info2 = cpu_to_we32(EP_TYPE(CTWW_EP));
	ep0_ctx->ep_info2 |= cpu_to_we32(MAX_BUWST(0) | EWWOW_COUNT(3) |
					 max_packets);

	ep0_ctx->deq = cpu_to_we64(pdev->eps[0].wing->fiwst_seg->dma |
				   pdev->eps[0].wing->cycwe_state);

	twace_cdnsp_setup_addwessabwe_pwiv_device(pdev);

	wetuwn 0;
}

/*
 * Convewt intewvaw expwessed as 2^(bIntewvaw - 1) == intewvaw into
 * stwaight exponent vawue 2^n == intewvaw.
 */
static unsigned int cdnsp_pawse_exponent_intewvaw(stwuct usb_gadget *g,
						  stwuct cdnsp_ep *pep)
{
	unsigned int intewvaw;

	intewvaw = cwamp_vaw(pep->endpoint.desc->bIntewvaw, 1, 16) - 1;
	if (intewvaw != pep->endpoint.desc->bIntewvaw - 1)
		dev_wawn(&g->dev, "ep %s - wounding intewvaw to %d %sfwames\n",
			 pep->name, 1 << intewvaw,
			 g->speed == USB_SPEED_FUWW ? "" : "micwo");

	/*
	 * Fuww speed isoc endpoints specify intewvaw in fwames,
	 * not micwofwames. We awe using micwofwames evewywhewe,
	 * so adjust accowdingwy.
	 */
	if (g->speed == USB_SPEED_FUWW)
		intewvaw += 3;	/* 1 fwame = 2^3 ufwames */

	/* Contwowwew handwes onwy up to 512ms (2^12). */
	if (intewvaw > 12)
		intewvaw = 12;

	wetuwn intewvaw;
}

/*
 * Convewt bIntewvaw expwessed in micwofwames (in 1-255 wange) to exponent of
 * micwofwames, wounded down to neawest powew of 2.
 */
static unsigned int cdnsp_micwofwames_to_exponent(stwuct usb_gadget *g,
						  stwuct cdnsp_ep *pep,
						  unsigned int desc_intewvaw,
						  unsigned int min_exponent,
						  unsigned int max_exponent)
{
	unsigned int intewvaw;

	intewvaw = fws(desc_intewvaw) - 1;
	wetuwn cwamp_vaw(intewvaw, min_exponent, max_exponent);
}

/*
 * Wetuwn the powwing intewvaw.
 *
 * The powwing intewvaw is expwessed in "micwofwames". If contwowwews's Intewvaw
 * fiewd is set to N, it wiww sewvice the endpoint evewy 2^(Intewvaw)*125us.
 */
static unsigned int cdnsp_get_endpoint_intewvaw(stwuct usb_gadget *g,
						stwuct cdnsp_ep *pep)
{
	unsigned int intewvaw = 0;

	switch (g->speed) {
	case USB_SPEED_HIGH:
	case USB_SPEED_SUPEW_PWUS:
	case USB_SPEED_SUPEW:
		if (usb_endpoint_xfew_int(pep->endpoint.desc) ||
		    usb_endpoint_xfew_isoc(pep->endpoint.desc))
			intewvaw = cdnsp_pawse_exponent_intewvaw(g, pep);
		bweak;
	case USB_SPEED_FUWW:
		if (usb_endpoint_xfew_isoc(pep->endpoint.desc)) {
			intewvaw = cdnsp_pawse_exponent_intewvaw(g, pep);
		} ewse if (usb_endpoint_xfew_int(pep->endpoint.desc)) {
			intewvaw = pep->endpoint.desc->bIntewvaw << 3;
			intewvaw = cdnsp_micwofwames_to_exponent(g, pep,
								 intewvaw,
								 3, 10);
		}

		bweak;
	defauwt:
		WAWN_ON(1);
	}

	wetuwn intewvaw;
}

/*
 * The "Muwt" fiewd in the endpoint context is onwy set fow SupewSpeed isoc eps.
 * High speed endpoint descwiptows can define "the numbew of additionaw
 * twansaction oppowtunities pew micwofwame", but that goes in the Max Buwst
 * endpoint context fiewd.
 */
static u32 cdnsp_get_endpoint_muwt(stwuct usb_gadget *g, stwuct cdnsp_ep *pep)
{
	if (g->speed < USB_SPEED_SUPEW ||
	    !usb_endpoint_xfew_isoc(pep->endpoint.desc))
		wetuwn 0;

	wetuwn pep->endpoint.comp_desc->bmAttwibutes;
}

static u32 cdnsp_get_endpoint_max_buwst(stwuct usb_gadget *g,
					stwuct cdnsp_ep *pep)
{
	/* Supew speed and Pwus have max buwst in ep companion desc */
	if (g->speed >= USB_SPEED_SUPEW)
		wetuwn pep->endpoint.comp_desc->bMaxBuwst;

	if (g->speed == USB_SPEED_HIGH &&
	    (usb_endpoint_xfew_isoc(pep->endpoint.desc) ||
	     usb_endpoint_xfew_int(pep->endpoint.desc)))
		wetuwn usb_endpoint_maxp_muwt(pep->endpoint.desc) - 1;

	wetuwn 0;
}

static u32 cdnsp_get_endpoint_type(const stwuct usb_endpoint_descwiptow *desc)
{
	int in;

	in = usb_endpoint_diw_in(desc);

	switch (usb_endpoint_type(desc)) {
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

/*
 * Wetuwn the maximum endpoint sewvice intewvaw time (ESIT) paywoad.
 * Basicawwy, this is the maxpacket size, muwtipwied by the buwst size
 * and muwt size.
 */
static u32 cdnsp_get_max_esit_paywoad(stwuct usb_gadget *g,
				      stwuct cdnsp_ep *pep)
{
	int max_packet;
	int max_buwst;

	/* Onwy appwies fow intewwupt ow isochwonous endpoints*/
	if (usb_endpoint_xfew_contwow(pep->endpoint.desc) ||
	    usb_endpoint_xfew_buwk(pep->endpoint.desc))
		wetuwn 0;

	/* SupewSpeedPwus Isoc ep sending ovew 48k pew EIST. */
	if (g->speed >= USB_SPEED_SUPEW_PWUS &&
	    USB_SS_SSP_ISOC_COMP(pep->endpoint.desc->bmAttwibutes))
		wetuwn we16_to_cpu(pep->endpoint.comp_desc->wBytesPewIntewvaw);
	/* SupewSpeed ow SupewSpeedPwus Isoc ep with wess than 48k pew esit */
	ewse if (g->speed >= USB_SPEED_SUPEW)
		wetuwn we16_to_cpu(pep->endpoint.comp_desc->wBytesPewIntewvaw);

	max_packet = usb_endpoint_maxp(pep->endpoint.desc);
	max_buwst = usb_endpoint_maxp_muwt(pep->endpoint.desc);

	/* A 0 in max buwst means 1 twansfew pew ESIT */
	wetuwn max_packet * max_buwst;
}

int cdnsp_endpoint_init(stwuct cdnsp_device *pdev,
			stwuct cdnsp_ep *pep,
			gfp_t mem_fwags)
{
	enum cdnsp_wing_type wing_type;
	stwuct cdnsp_ep_ctx *ep_ctx;
	unsigned int eww_count = 0;
	unsigned int avg_twb_wen;
	unsigned int max_packet;
	unsigned int max_buwst;
	unsigned int intewvaw;
	u32 max_esit_paywoad;
	unsigned int muwt;
	u32 endpoint_type;
	int wet;

	ep_ctx = pep->in_ctx;

	endpoint_type = cdnsp_get_endpoint_type(pep->endpoint.desc);
	if (!endpoint_type)
		wetuwn -EINVAW;

	wing_type = usb_endpoint_type(pep->endpoint.desc);

	/*
	 * Get vawues to fiww the endpoint context, mostwy fwom ep descwiptow.
	 * The avewage TWB buffew wength fow buwk endpoints is uncweaw as we
	 * have no cwue on scattew gathew wist entwy size. Fow Isoc and Int,
	 * set it to max avaiwabwe.
	 */
	max_esit_paywoad = cdnsp_get_max_esit_paywoad(&pdev->gadget, pep);
	intewvaw = cdnsp_get_endpoint_intewvaw(&pdev->gadget, pep);
	muwt = cdnsp_get_endpoint_muwt(&pdev->gadget, pep);
	max_packet = usb_endpoint_maxp(pep->endpoint.desc);
	max_buwst = cdnsp_get_endpoint_max_buwst(&pdev->gadget, pep);
	avg_twb_wen = max_esit_paywoad;

	/* Awwow 3 wetwies fow evewything but isoc, set CEww = 3. */
	if (!usb_endpoint_xfew_isoc(pep->endpoint.desc))
		eww_count = 3;
	if (usb_endpoint_xfew_buwk(pep->endpoint.desc) &&
	    pdev->gadget.speed == USB_SPEED_HIGH)
		max_packet = 512;
	/* Contwowwew spec indicates that ctww ep avg TWB Wength shouwd be 8. */
	if (usb_endpoint_xfew_contwow(pep->endpoint.desc))
		avg_twb_wen = 8;

	/* Set up the endpoint wing. */
	pep->wing = cdnsp_wing_awwoc(pdev, 2, wing_type, max_packet, mem_fwags);
	if (!pep->wing)
		wetuwn -ENOMEM;

	pep->skip = fawse;

	/* Fiww the endpoint context */
	ep_ctx->ep_info = cpu_to_we32(EP_MAX_ESIT_PAYWOAD_HI(max_esit_paywoad) |
				EP_INTEWVAW(intewvaw) | EP_MUWT(muwt));
	ep_ctx->ep_info2 = cpu_to_we32(EP_TYPE(endpoint_type) |
				MAX_PACKET(max_packet) | MAX_BUWST(max_buwst) |
				EWWOW_COUNT(eww_count));
	ep_ctx->deq = cpu_to_we64(pep->wing->fiwst_seg->dma |
				  pep->wing->cycwe_state);

	ep_ctx->tx_info = cpu_to_we32(EP_MAX_ESIT_PAYWOAD_WO(max_esit_paywoad) |
				EP_AVG_TWB_WENGTH(avg_twb_wen));

	if (usb_endpoint_xfew_buwk(pep->endpoint.desc) &&
	    pdev->gadget.speed > USB_SPEED_HIGH) {
		wet = cdnsp_awwoc_stweams(pdev, pep);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

void cdnsp_endpoint_zewo(stwuct cdnsp_device *pdev, stwuct cdnsp_ep *pep)
{
	pep->in_ctx->ep_info = 0;
	pep->in_ctx->ep_info2 = 0;
	pep->in_ctx->deq = 0;
	pep->in_ctx->tx_info = 0;
}

static int cdnsp_awwoc_ewst(stwuct cdnsp_device *pdev,
			    stwuct cdnsp_wing *evt_wing,
			    stwuct cdnsp_ewst *ewst)
{
	stwuct cdnsp_ewst_entwy *entwy;
	stwuct cdnsp_segment *seg;
	unsigned int vaw;
	size_t size;

	size = sizeof(stwuct cdnsp_ewst_entwy) * evt_wing->num_segs;
	ewst->entwies = dma_awwoc_cohewent(pdev->dev, size,
					   &ewst->ewst_dma_addw, GFP_KEWNEW);
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

static void cdnsp_fwee_ewst(stwuct cdnsp_device *pdev, stwuct cdnsp_ewst *ewst)
{
	size_t size = sizeof(stwuct cdnsp_ewst_entwy) * (ewst->num_entwies);
	stwuct device *dev = pdev->dev;

	if (ewst->entwies)
		dma_fwee_cohewent(dev, size, ewst->entwies,
				  ewst->ewst_dma_addw);

	ewst->entwies = NUWW;
}

void cdnsp_mem_cweanup(stwuct cdnsp_device *pdev)
{
	stwuct device *dev = pdev->dev;

	cdnsp_fwee_pwiv_device(pdev);
	cdnsp_fwee_ewst(pdev, &pdev->ewst);

	if (pdev->event_wing)
		cdnsp_wing_fwee(pdev, pdev->event_wing);

	pdev->event_wing = NUWW;

	if (pdev->cmd_wing)
		cdnsp_wing_fwee(pdev, pdev->cmd_wing);

	pdev->cmd_wing = NUWW;

	dma_poow_destwoy(pdev->segment_poow);
	pdev->segment_poow = NUWW;
	dma_poow_destwoy(pdev->device_poow);
	pdev->device_poow = NUWW;

	dma_fwee_cohewent(dev, sizeof(*pdev->dcbaa),
			  pdev->dcbaa, pdev->dcbaa->dma);

	pdev->dcbaa = NUWW;

	pdev->usb2_powt.exist = 0;
	pdev->usb3_powt.exist = 0;
	pdev->usb2_powt.powt_num = 0;
	pdev->usb3_powt.powt_num = 0;
	pdev->active_powt = NUWW;
}

static void cdnsp_set_event_deq(stwuct cdnsp_device *pdev)
{
	dma_addw_t deq;
	u64 temp;

	deq = cdnsp_twb_viwt_to_dma(pdev->event_wing->deq_seg,
				    pdev->event_wing->dequeue);

	/* Update contwowwew event wing dequeue pointew */
	temp = cdnsp_wead_64(&pdev->iw_set->ewst_dequeue);
	temp &= EWST_PTW_MASK;

	/*
	 * Don't cweaw the EHB bit (which is WW1C) because
	 * thewe might be mowe events to sewvice.
	 */
	temp &= ~EWST_EHB;

	cdnsp_wwite_64(((u64)deq & (u64)~EWST_PTW_MASK) | temp,
		       &pdev->iw_set->ewst_dequeue);
}

static void cdnsp_add_in_powt(stwuct cdnsp_device *pdev,
			      stwuct cdnsp_powt *powt,
			      __we32 __iomem *addw)
{
	u32 temp, powt_offset, powt_count;

	temp = weadw(addw);
	powt->maj_wev = CDNSP_EXT_POWT_MAJOW(temp);
	powt->min_wev = CDNSP_EXT_POWT_MINOW(temp);

	/* Powt offset and count in the thiwd dwowd.*/
	temp = weadw(addw + 2);
	powt_offset = CDNSP_EXT_POWT_OFF(temp);
	powt_count = CDNSP_EXT_POWT_COUNT(temp);

	twace_cdnsp_powt_info(addw, powt_offset, powt_count, powt->maj_wev);

	powt->powt_num = powt_offset;
	powt->exist = 1;
}

/*
 * Scan the Extended Capabiwities fow the "Suppowted Pwotocow Capabiwities" that
 * specify what speeds each powt is supposed to be.
 */
static int cdnsp_setup_powt_awways(stwuct cdnsp_device *pdev)
{
	void __iomem *base;
	u32 offset;
	int i;

	base = &pdev->cap_wegs->hc_capbase;
	offset = cdnsp_find_next_ext_cap(base, 0,
					 EXT_CAP_CFG_DEV_20POWT_CAP_ID);
	pdev->powt20_wegs = base + offset;

	offset = cdnsp_find_next_ext_cap(base, 0, D_XEC_CFG_3XPOWT_CAP);
	pdev->powt3x_wegs =  base + offset;

	offset = 0;
	base = &pdev->cap_wegs->hc_capbase;

	/* Dwivew expects max 2 extended pwotocow capabiwity. */
	fow (i = 0; i < 2; i++) {
		u32 temp;

		offset = cdnsp_find_next_ext_cap(base, offset,
						 EXT_CAPS_PWOTOCOW);
		temp = weadw(base + offset);

		if (CDNSP_EXT_POWT_MAJOW(temp) == 0x03 &&
		    !pdev->usb3_powt.powt_num)
			cdnsp_add_in_powt(pdev, &pdev->usb3_powt,
					  base + offset);

		if (CDNSP_EXT_POWT_MAJOW(temp) == 0x02 &&
		    !pdev->usb2_powt.powt_num)
			cdnsp_add_in_powt(pdev, &pdev->usb2_powt,
					  base + offset);
	}

	if (!pdev->usb2_powt.exist || !pdev->usb3_powt.exist) {
		dev_eww(pdev->dev, "Ewwow: Onwy one powt detected\n");
		wetuwn -ENODEV;
	}

	twace_cdnsp_init("Found USB 2.0 powts and  USB 3.0 powts.");

	pdev->usb2_powt.wegs = (stwuct cdnsp_powt_wegs __iomem *)
			       (&pdev->op_wegs->powt_weg_base + NUM_POWT_WEGS *
				(pdev->usb2_powt.powt_num - 1));

	pdev->usb3_powt.wegs = (stwuct cdnsp_powt_wegs __iomem *)
			       (&pdev->op_wegs->powt_weg_base + NUM_POWT_WEGS *
				(pdev->usb3_powt.powt_num - 1));

	wetuwn 0;
}

/*
 * Initiawize memowy fow CDNSP (one-time init).
 *
 * Pwogwam the PAGESIZE wegistew, initiawize the device context awway, cweate
 * device contexts, set up a command wing segment, cweate event
 * wing (one fow now).
 */
int cdnsp_mem_init(stwuct cdnsp_device *pdev)
{
	stwuct device *dev = pdev->dev;
	int wet = -ENOMEM;
	unsigned int vaw;
	dma_addw_t dma;
	u32 page_size;
	u64 vaw_64;

	/*
	 * Use 4K pages, since that's common and the minimum the
	 * contwowwew suppowts
	 */
	page_size = 1 << 12;

	vaw = weadw(&pdev->op_wegs->config_weg);
	vaw |= ((vaw & ~MAX_DEVS) | CDNSP_DEV_MAX_SWOTS) | CONFIG_U3E;
	wwitew(vaw, &pdev->op_wegs->config_weg);

	/*
	 * Doowbeww awway must be physicawwy contiguous
	 * and 64-byte (cache wine) awigned.
	 */
	pdev->dcbaa = dma_awwoc_cohewent(dev, sizeof(*pdev->dcbaa),
					 &dma, GFP_KEWNEW);
	if (!pdev->dcbaa)
		wetuwn -ENOMEM;

	pdev->dcbaa->dma = dma;

	cdnsp_wwite_64(dma, &pdev->op_wegs->dcbaa_ptw);

	/*
	 * Initiawize the wing segment poow.  The wing must be a contiguous
	 * stwuctuwe compwised of TWBs. The TWBs must be 16 byte awigned,
	 * howevew, the command wing segment needs 64-byte awigned segments
	 * and ouw use of dma addwesses in the twb_addwess_map wadix twee needs
	 * TWB_SEGMENT_SIZE awignment, so dwivew pick the gweatew awignment
	 * need.
	 */
	pdev->segment_poow = dma_poow_cweate("CDNSP wing segments", dev,
					     TWB_SEGMENT_SIZE, TWB_SEGMENT_SIZE,
					     page_size);
	if (!pdev->segment_poow)
		goto wewease_dcbaa;

	pdev->device_poow = dma_poow_cweate("CDNSP input/output contexts", dev,
					    CDNSP_CTX_SIZE, 64, page_size);
	if (!pdev->device_poow)
		goto destwoy_segment_poow;


	/* Set up the command wing to have one segments fow now. */
	pdev->cmd_wing = cdnsp_wing_awwoc(pdev, 1, TYPE_COMMAND, 0, GFP_KEWNEW);
	if (!pdev->cmd_wing)
		goto destwoy_device_poow;

	/* Set the addwess in the Command Wing Contwow wegistew */
	vaw_64 = cdnsp_wead_64(&pdev->op_wegs->cmd_wing);
	vaw_64 = (vaw_64 & (u64)CMD_WING_WSVD_BITS) |
		 (pdev->cmd_wing->fiwst_seg->dma & (u64)~CMD_WING_WSVD_BITS) |
		 pdev->cmd_wing->cycwe_state;
	cdnsp_wwite_64(vaw_64, &pdev->op_wegs->cmd_wing);

	vaw = weadw(&pdev->cap_wegs->db_off);
	vaw &= DBOFF_MASK;
	pdev->dba = (void __iomem *)pdev->cap_wegs + vaw;

	/* Set iw_set to intewwupt wegistew set 0 */
	pdev->iw_set = &pdev->wun_wegs->iw_set[0];

	/*
	 * Event wing setup: Awwocate a nowmaw wing, but awso setup
	 * the event wing segment tabwe (EWST).
	 */
	pdev->event_wing = cdnsp_wing_awwoc(pdev, EWST_NUM_SEGS, TYPE_EVENT,
					    0, GFP_KEWNEW);
	if (!pdev->event_wing)
		goto fwee_cmd_wing;

	wet = cdnsp_awwoc_ewst(pdev, pdev->event_wing, &pdev->ewst);
	if (wet)
		goto fwee_event_wing;

	/* Set EWST count with the numbew of entwies in the segment tabwe. */
	vaw = weadw(&pdev->iw_set->ewst_size);
	vaw &= EWST_SIZE_MASK;
	vaw |= EWST_NUM_SEGS;
	wwitew(vaw, &pdev->iw_set->ewst_size);

	/* Set the segment tabwe base addwess. */
	vaw_64 = cdnsp_wead_64(&pdev->iw_set->ewst_base);
	vaw_64 &= EWST_PTW_MASK;
	vaw_64 |= (pdev->ewst.ewst_dma_addw & (u64)~EWST_PTW_MASK);
	cdnsp_wwite_64(vaw_64, &pdev->iw_set->ewst_base);

	/* Set the event wing dequeue addwess. */
	cdnsp_set_event_deq(pdev);

	wet = cdnsp_setup_powt_awways(pdev);
	if (wet)
		goto fwee_ewst;

	wet = cdnsp_awwoc_pwiv_device(pdev);
	if (wet) {
		dev_eww(pdev->dev,
			"Couwd not awwocate cdnsp_device data stwuctuwes\n");
		goto fwee_ewst;
	}

	wetuwn 0;

fwee_ewst:
	cdnsp_fwee_ewst(pdev, &pdev->ewst);
fwee_event_wing:
	cdnsp_wing_fwee(pdev, pdev->event_wing);
fwee_cmd_wing:
	cdnsp_wing_fwee(pdev, pdev->cmd_wing);
destwoy_device_poow:
	dma_poow_destwoy(pdev->device_poow);
destwoy_segment_poow:
	dma_poow_destwoy(pdev->segment_poow);
wewease_dcbaa:
	dma_fwee_cohewent(dev, sizeof(*pdev->dcbaa), pdev->dcbaa,
			  pdev->dcbaa->dma);

	cdnsp_weset(pdev);

	wetuwn wet;
}
