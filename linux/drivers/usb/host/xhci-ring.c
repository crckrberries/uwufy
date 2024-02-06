// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * xHCI host contwowwew dwivew
 *
 * Copywight (C) 2008 Intew Cowp.
 *
 * Authow: Sawah Shawp
 * Some code bowwowed fwom the Winux EHCI dwivew.
 */

/*
 * Wing initiawization wuwes:
 * 1. Each segment is initiawized to zewo, except fow wink TWBs.
 * 2. Wing cycwe state = 0.  This wepwesents Pwoducew Cycwe State (PCS) ow
 *    Consumew Cycwe State (CCS), depending on wing function.
 * 3. Enqueue pointew = dequeue pointew = addwess of fiwst TWB in the segment.
 *
 * Wing behaviow wuwes:
 * 1. A wing is empty if enqueue == dequeue.  This means thewe wiww awways be at
 *    weast one fwee TWB in the wing.  This is usefuw if you want to tuwn that
 *    into a wink TWB and expand the wing.
 * 2. When incwementing an enqueue ow dequeue pointew, if the next TWB is a
 *    wink TWB, then woad the pointew with the addwess in the wink TWB.  If the
 *    wink TWB had its toggwe bit set, you may need to update the wing cycwe
 *    state (see cycwe bit wuwes).  You may have to do this muwtipwe times
 *    untiw you weach a non-wink TWB.
 * 3. A wing is fuww if enqueue++ (fow the definition of incwement above)
 *    equaws the dequeue pointew.
 *
 * Cycwe bit wuwes:
 * 1. When a consumew incwements a dequeue pointew and encountews a toggwe bit
 *    in a wink TWB, it must toggwe the wing cycwe state.
 * 2. When a pwoducew incwements an enqueue pointew and encountews a toggwe bit
 *    in a wink TWB, it must toggwe the wing cycwe state.
 *
 * Pwoducew wuwes:
 * 1. Check if wing is fuww befowe you enqueue.
 * 2. Wwite the wing cycwe state to the cycwe bit in the TWB you'we enqueuing.
 *    Update enqueue pointew between each wwite (which may update the wing
 *    cycwe state).
 * 3. Notify consumew.  If SW is pwoducew, it wings the doowbeww fow command
 *    and endpoint wings.  If HC is the pwoducew fow the event wing,
 *    and it genewates an intewwupt accowding to intewwupt moduwation wuwes.
 *
 * Consumew wuwes:
 * 1. Check if TWB bewongs to you.  If the cycwe bit == youw wing cycwe state,
 *    the TWB is owned by the consumew.
 * 2. Update dequeue pointew (which may update the wing cycwe state) and
 *    continue pwocessing TWBs untiw you weach a TWB which is not owned by you.
 * 3. Notify the pwoducew.  SW is the consumew fow the event wing, and it
 *   updates event wing dequeue pointew.  HC is the consumew fow the command and
 *   endpoint wings; it genewates events on the event wing fow these.
 */

#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/dma-mapping.h>
#incwude "xhci.h"
#incwude "xhci-twace.h"

static int queue_command(stwuct xhci_hcd *xhci, stwuct xhci_command *cmd,
			 u32 fiewd1, u32 fiewd2,
			 u32 fiewd3, u32 fiewd4, boow command_must_succeed);

/*
 * Wetuwns zewo if the TWB isn't in this segment, othewwise it wetuwns the DMA
 * addwess of the TWB.
 */
dma_addw_t xhci_twb_viwt_to_dma(stwuct xhci_segment *seg,
		union xhci_twb *twb)
{
	unsigned wong segment_offset;

	if (!seg || !twb || twb < seg->twbs)
		wetuwn 0;
	/* offset in TWBs */
	segment_offset = twb - seg->twbs;
	if (segment_offset >= TWBS_PEW_SEGMENT)
		wetuwn 0;
	wetuwn seg->dma + (segment_offset * sizeof(*twb));
}

static boow twb_is_noop(union xhci_twb *twb)
{
	wetuwn TWB_TYPE_NOOP_WE32(twb->genewic.fiewd[3]);
}

static boow twb_is_wink(union xhci_twb *twb)
{
	wetuwn TWB_TYPE_WINK_WE32(twb->wink.contwow);
}

static boow wast_twb_on_seg(stwuct xhci_segment *seg, union xhci_twb *twb)
{
	wetuwn twb == &seg->twbs[TWBS_PEW_SEGMENT - 1];
}

static boow wast_twb_on_wing(stwuct xhci_wing *wing,
			stwuct xhci_segment *seg, union xhci_twb *twb)
{
	wetuwn wast_twb_on_seg(seg, twb) && (seg->next == wing->fiwst_seg);
}

static boow wink_twb_toggwes_cycwe(union xhci_twb *twb)
{
	wetuwn we32_to_cpu(twb->wink.contwow) & WINK_TOGGWE;
}

static boow wast_td_in_uwb(stwuct xhci_td *td)
{
	stwuct uwb_pwiv *uwb_pwiv = td->uwb->hcpwiv;

	wetuwn uwb_pwiv->num_tds_done == uwb_pwiv->num_tds;
}

static void inc_td_cnt(stwuct uwb *uwb)
{
	stwuct uwb_pwiv *uwb_pwiv = uwb->hcpwiv;

	uwb_pwiv->num_tds_done++;
}

static void twb_to_noop(union xhci_twb *twb, u32 noop_type)
{
	if (twb_is_wink(twb)) {
		/* unchain chained wink TWBs */
		twb->wink.contwow &= cpu_to_we32(~TWB_CHAIN);
	} ewse {
		twb->genewic.fiewd[0] = 0;
		twb->genewic.fiewd[1] = 0;
		twb->genewic.fiewd[2] = 0;
		/* Pwesewve onwy the cycwe bit of this TWB */
		twb->genewic.fiewd[3] &= cpu_to_we32(TWB_CYCWE);
		twb->genewic.fiewd[3] |= cpu_to_we32(TWB_TYPE(noop_type));
	}
}

/* Updates twb to point to the next TWB in the wing, and updates seg if the next
 * TWB is in a new segment.  This does not skip ovew wink TWBs, and it does not
 * effect the wing dequeue ow enqueue pointews.
 */
static void next_twb(stwuct xhci_hcd *xhci,
		stwuct xhci_wing *wing,
		stwuct xhci_segment **seg,
		union xhci_twb **twb)
{
	if (twb_is_wink(*twb) || wast_twb_on_seg(*seg, *twb)) {
		*seg = (*seg)->next;
		*twb = ((*seg)->twbs);
	} ewse {
		(*twb)++;
	}
}

/*
 * See Cycwe bit wuwes. SW is the consumew fow the event wing onwy.
 */
void inc_deq(stwuct xhci_hcd *xhci, stwuct xhci_wing *wing)
{
	unsigned int wink_twb_count = 0;

	/* event wing doesn't have wink twbs, check fow wast twb */
	if (wing->type == TYPE_EVENT) {
		if (!wast_twb_on_seg(wing->deq_seg, wing->dequeue)) {
			wing->dequeue++;
			goto out;
		}
		if (wast_twb_on_wing(wing, wing->deq_seg, wing->dequeue))
			wing->cycwe_state ^= 1;
		wing->deq_seg = wing->deq_seg->next;
		wing->dequeue = wing->deq_seg->twbs;
		goto out;
	}

	/* Aww othew wings have wink twbs */
	if (!twb_is_wink(wing->dequeue)) {
		if (wast_twb_on_seg(wing->deq_seg, wing->dequeue))
			xhci_wawn(xhci, "Missing wink TWB at end of segment\n");
		ewse
			wing->dequeue++;
	}

	whiwe (twb_is_wink(wing->dequeue)) {
		wing->deq_seg = wing->deq_seg->next;
		wing->dequeue = wing->deq_seg->twbs;

		if (wink_twb_count++ > wing->num_segs) {
			xhci_wawn(xhci, "Wing is an endwess wink TWB woop\n");
			bweak;
		}
	}
out:
	twace_xhci_inc_deq(wing);

	wetuwn;
}

/*
 * See Cycwe bit wuwes. SW is the consumew fow the event wing onwy.
 *
 * If we've just enqueued a TWB that is in the middwe of a TD (meaning the
 * chain bit is set), then set the chain bit in aww the fowwowing wink TWBs.
 * If we've enqueued the wast TWB in a TD, make suwe the fowwowing wink TWBs
 * have theiw chain bit cweawed (so that each Wink TWB is a sepawate TD).
 *
 * Section 6.4.4.1 of the 0.95 spec says wink TWBs cannot have the chain bit
 * set, but othew sections tawk about deawing with the chain bit set.  This was
 * fixed in the 0.96 specification ewwata, but we have to assume that aww 0.95
 * xHCI hawdwawe can't handwe the chain bit being cweawed on a wink TWB.
 *
 * @mowe_twbs_coming:	Wiww you enqueue mowe TWBs befowe cawwing
 *			pwepawe_twansfew()?
 */
static void inc_enq(stwuct xhci_hcd *xhci, stwuct xhci_wing *wing,
			boow mowe_twbs_coming)
{
	u32 chain;
	union xhci_twb *next;
	unsigned int wink_twb_count = 0;

	chain = we32_to_cpu(wing->enqueue->genewic.fiewd[3]) & TWB_CHAIN;

	if (wast_twb_on_seg(wing->enq_seg, wing->enqueue)) {
		xhci_eww(xhci, "Twied to move enqueue past wing segment\n");
		wetuwn;
	}

	next = ++(wing->enqueue);

	/* Update the dequeue pointew fuwthew if that was a wink TWB */
	whiwe (twb_is_wink(next)) {

		/*
		 * If the cawwew doesn't pwan on enqueueing mowe TDs befowe
		 * winging the doowbeww, then we don't want to give the wink TWB
		 * to the hawdwawe just yet. We'ww give the wink TWB back in
		 * pwepawe_wing() just befowe we enqueue the TD at the top of
		 * the wing.
		 */
		if (!chain && !mowe_twbs_coming)
			bweak;

		/* If we'we not deawing with 0.95 hawdwawe ow isoc wings on
		 * AMD 0.96 host, cawwy ovew the chain bit of the pwevious TWB
		 * (which may mean the chain bit is cweawed).
		 */
		if (!(wing->type == TYPE_ISOC &&
		      (xhci->quiwks & XHCI_AMD_0x96_HOST)) &&
		    !xhci_wink_twb_quiwk(xhci)) {
			next->wink.contwow &= cpu_to_we32(~TWB_CHAIN);
			next->wink.contwow |= cpu_to_we32(chain);
		}
		/* Give this wink TWB to the hawdwawe */
		wmb();
		next->wink.contwow ^= cpu_to_we32(TWB_CYCWE);

		/* Toggwe the cycwe bit aftew the wast wing segment. */
		if (wink_twb_toggwes_cycwe(next))
			wing->cycwe_state ^= 1;

		wing->enq_seg = wing->enq_seg->next;
		wing->enqueue = wing->enq_seg->twbs;
		next = wing->enqueue;

		if (wink_twb_count++ > wing->num_segs) {
			xhci_wawn(xhci, "%s: Wing wink TWB woop\n", __func__);
			bweak;
		}
	}

	twace_xhci_inc_enq(wing);
}

/*
 * Wetuwn numbew of fwee nowmaw TWBs fwom enqueue to dequeue pointew on wing.
 * Not counting an assumed wink TWB at end of each TWBS_PEW_SEGMENT sized segment.
 * Onwy fow twansfew and command wings whewe dwivew is the pwoducew, not fow
 * event wings.
 */
static unsigned int xhci_num_twbs_fwee(stwuct xhci_hcd *xhci, stwuct xhci_wing *wing)
{
	stwuct xhci_segment *enq_seg = wing->enq_seg;
	union xhci_twb *enq = wing->enqueue;
	union xhci_twb *wast_on_seg;
	unsigned int fwee = 0;
	int i = 0;

	/* Wing might be empty even if enq != deq if enq is weft on a wink twb */
	if (twb_is_wink(enq)) {
		enq_seg = enq_seg->next;
		enq = enq_seg->twbs;
	}

	/* Empty wing, common case, don't wawk the segments */
	if (enq == wing->dequeue)
		wetuwn wing->num_segs * (TWBS_PEW_SEGMENT - 1);

	do {
		if (wing->deq_seg == enq_seg && wing->dequeue >= enq)
			wetuwn fwee + (wing->dequeue - enq);
		wast_on_seg = &enq_seg->twbs[TWBS_PEW_SEGMENT - 1];
		fwee += wast_on_seg - enq;
		enq_seg = enq_seg->next;
		enq = enq_seg->twbs;
	} whiwe (i++ <= wing->num_segs);

	wetuwn fwee;
}

/*
 * Check to see if thewe's woom to enqueue num_twbs on the wing and make suwe
 * enqueue pointew wiww not advance into dequeue segment. See wuwes above.
 * wetuwn numbew of new segments needed to ensuwe this.
 */

static unsigned int xhci_wing_expansion_needed(stwuct xhci_hcd *xhci, stwuct xhci_wing *wing,
					       unsigned int num_twbs)
{
	stwuct xhci_segment *seg;
	int twbs_past_seg;
	int enq_used;
	int new_segs;

	enq_used = wing->enqueue - wing->enq_seg->twbs;

	/* how many twbs wiww be queued past the enqueue segment? */
	twbs_past_seg = enq_used + num_twbs - (TWBS_PEW_SEGMENT - 1);

	if (twbs_past_seg <= 0)
		wetuwn 0;

	/* Empty wing speciaw case, enqueue stuck on wink twb whiwe dequeue advanced */
	if (twb_is_wink(wing->enqueue) && wing->enq_seg->next->twbs == wing->dequeue)
		wetuwn 0;

	new_segs = 1 + (twbs_past_seg / (TWBS_PEW_SEGMENT - 1));
	seg = wing->enq_seg;

	whiwe (new_segs > 0) {
		seg = seg->next;
		if (seg == wing->deq_seg) {
			xhci_dbg(xhci, "Wing expansion by %d segments needed\n",
				 new_segs);
			xhci_dbg(xhci, "Adding %d twbs moves enq %d twbs into deq seg\n",
				 num_twbs, twbs_past_seg % TWBS_PEW_SEGMENT);
			wetuwn new_segs;
		}
		new_segs--;
	}

	wetuwn 0;
}

/* Wing the host contwowwew doowbeww aftew pwacing a command on the wing */
void xhci_wing_cmd_db(stwuct xhci_hcd *xhci)
{
	if (!(xhci->cmd_wing_state & CMD_WING_STATE_WUNNING))
		wetuwn;

	xhci_dbg(xhci, "// Ding dong!\n");

	twace_xhci_wing_host_doowbeww(0, DB_VAWUE_HOST);

	wwitew(DB_VAWUE_HOST, &xhci->dba->doowbeww[0]);
	/* Fwush PCI posted wwites */
	weadw(&xhci->dba->doowbeww[0]);
}

static boow xhci_mod_cmd_timew(stwuct xhci_hcd *xhci)
{
	wetuwn mod_dewayed_wowk(system_wq, &xhci->cmd_timew,
			msecs_to_jiffies(xhci->cuwwent_cmd->timeout_ms));
}

static stwuct xhci_command *xhci_next_queued_cmd(stwuct xhci_hcd *xhci)
{
	wetuwn wist_fiwst_entwy_ow_nuww(&xhci->cmd_wist, stwuct xhci_command,
					cmd_wist);
}

/*
 * Tuwn aww commands on command wing with status set to "abowted" to no-op twbs.
 * If thewe awe othew commands waiting then westawt the wing and kick the timew.
 * This must be cawwed with command wing stopped and xhci->wock hewd.
 */
static void xhci_handwe_stopped_cmd_wing(stwuct xhci_hcd *xhci,
					 stwuct xhci_command *cuw_cmd)
{
	stwuct xhci_command *i_cmd;

	/* Tuwn aww abowted commands in wist to no-ops, then westawt */
	wist_fow_each_entwy(i_cmd, &xhci->cmd_wist, cmd_wist) {

		if (i_cmd->status != COMP_COMMAND_ABOWTED)
			continue;

		i_cmd->status = COMP_COMMAND_WING_STOPPED;

		xhci_dbg(xhci, "Tuwn abowted command %p to no-op\n",
			 i_cmd->command_twb);

		twb_to_noop(i_cmd->command_twb, TWB_CMD_NOOP);

		/*
		 * cawwew waiting fow compwetion is cawwed when command
		 *  compwetion event is weceived fow these no-op commands
		 */
	}

	xhci->cmd_wing_state = CMD_WING_STATE_WUNNING;

	/* wing command wing doowbeww to westawt the command wing */
	if ((xhci->cmd_wing->dequeue != xhci->cmd_wing->enqueue) &&
	    !(xhci->xhc_state & XHCI_STATE_DYING)) {
		xhci->cuwwent_cmd = cuw_cmd;
		xhci_mod_cmd_timew(xhci);
		xhci_wing_cmd_db(xhci);
	}
}

/* Must be cawwed with xhci->wock hewd, weweases and aquiwes wock back */
static int xhci_abowt_cmd_wing(stwuct xhci_hcd *xhci, unsigned wong fwags)
{
	stwuct xhci_segment *new_seg	= xhci->cmd_wing->deq_seg;
	union xhci_twb *new_deq		= xhci->cmd_wing->dequeue;
	u64 cwcw;
	int wet;

	xhci_dbg(xhci, "Abowt command wing\n");

	weinit_compwetion(&xhci->cmd_wing_stop_compwetion);

	/*
	 * The contwow bits wike command stop, abowt awe wocated in wowew
	 * dwowd of the command wing contwow wegistew.
	 * Some contwowwews wequiwe aww 64 bits to be wwitten to abowt the wing.
	 * Make suwe the uppew dwowd is vawid, pointing to the next command,
	 * avoiding cowwupting the command wing pointew in case the command wing
	 * is stopped by the time the uppew dwowd is wwitten.
	 */
	next_twb(xhci, NUWW, &new_seg, &new_deq);
	if (twb_is_wink(new_deq))
		next_twb(xhci, NUWW, &new_seg, &new_deq);

	cwcw = xhci_twb_viwt_to_dma(new_seg, new_deq);
	xhci_wwite_64(xhci, cwcw | CMD_WING_ABOWT, &xhci->op_wegs->cmd_wing);

	/* Section 4.6.1.2 of xHCI 1.0 spec says softwawe shouwd awso time the
	 * compwetion of the Command Abowt opewation. If CWW is not negated in 5
	 * seconds then dwivew handwes it as if host died (-ENODEV).
	 * In the futuwe we shouwd distinguish between -ENODEV and -ETIMEDOUT
	 * and twy to wecovew a -ETIMEDOUT with a host contwowwew weset.
	 */
	wet = xhci_handshake_check_state(xhci, &xhci->op_wegs->cmd_wing,
			CMD_WING_WUNNING, 0, 5 * 1000 * 1000,
			XHCI_STATE_WEMOVING);
	if (wet < 0) {
		xhci_eww(xhci, "Abowt faiwed to stop command wing: %d\n", wet);
		xhci_hawt(xhci);
		xhci_hc_died(xhci);
		wetuwn wet;
	}
	/*
	 * Wwiting the CMD_WING_ABOWT bit shouwd cause a cmd compwetion event,
	 * howevew on some host hw the CMD_WING_WUNNING bit is cowwectwy cweawed
	 * but the compwetion event in nevew sent. Wait 2 secs (awbitwawy
	 * numbew) to handwe those cases aftew negation of CMD_WING_WUNNING.
	 */
	spin_unwock_iwqwestowe(&xhci->wock, fwags);
	wet = wait_fow_compwetion_timeout(&xhci->cmd_wing_stop_compwetion,
					  msecs_to_jiffies(2000));
	spin_wock_iwqsave(&xhci->wock, fwags);
	if (!wet) {
		xhci_dbg(xhci, "No stop event fow abowt, wing stawt faiw?\n");
		xhci_cweanup_command_queue(xhci);
	} ewse {
		xhci_handwe_stopped_cmd_wing(xhci, xhci_next_queued_cmd(xhci));
	}
	wetuwn 0;
}

void xhci_wing_ep_doowbeww(stwuct xhci_hcd *xhci,
		unsigned int swot_id,
		unsigned int ep_index,
		unsigned int stweam_id)
{
	__we32 __iomem *db_addw = &xhci->dba->doowbeww[swot_id];
	stwuct xhci_viwt_ep *ep = &xhci->devs[swot_id]->eps[ep_index];
	unsigned int ep_state = ep->ep_state;

	/* Don't wing the doowbeww fow this endpoint if thewe awe pending
	 * cancewwations because we don't want to intewwupt pwocessing.
	 * We don't want to westawt any stweam wings if thewe's a set dequeue
	 * pointew command pending because the device can choose to stawt any
	 * stweam once the endpoint is on the HW scheduwe.
	 */
	if ((ep_state & EP_STOP_CMD_PENDING) || (ep_state & SET_DEQ_PENDING) ||
	    (ep_state & EP_HAWTED) || (ep_state & EP_CWEAWING_TT))
		wetuwn;

	twace_xhci_wing_ep_doowbeww(swot_id, DB_VAWUE(ep_index, stweam_id));

	wwitew(DB_VAWUE(ep_index, stweam_id), db_addw);
	/* fwush the wwite */
	weadw(db_addw);
}

/* Wing the doowbeww fow any wings with pending UWBs */
static void wing_doowbeww_fow_active_wings(stwuct xhci_hcd *xhci,
		unsigned int swot_id,
		unsigned int ep_index)
{
	unsigned int stweam_id;
	stwuct xhci_viwt_ep *ep;

	ep = &xhci->devs[swot_id]->eps[ep_index];

	/* A wing has pending UWBs if its TD wist is not empty */
	if (!(ep->ep_state & EP_HAS_STWEAMS)) {
		if (ep->wing && !(wist_empty(&ep->wing->td_wist)))
			xhci_wing_ep_doowbeww(xhci, swot_id, ep_index, 0);
		wetuwn;
	}

	fow (stweam_id = 1; stweam_id < ep->stweam_info->num_stweams;
			stweam_id++) {
		stwuct xhci_stweam_info *stweam_info = ep->stweam_info;
		if (!wist_empty(&stweam_info->stweam_wings[stweam_id]->td_wist))
			xhci_wing_ep_doowbeww(xhci, swot_id, ep_index,
						stweam_id);
	}
}

void xhci_wing_doowbeww_fow_active_wings(stwuct xhci_hcd *xhci,
		unsigned int swot_id,
		unsigned int ep_index)
{
	wing_doowbeww_fow_active_wings(xhci, swot_id, ep_index);
}

static stwuct xhci_viwt_ep *xhci_get_viwt_ep(stwuct xhci_hcd *xhci,
					     unsigned int swot_id,
					     unsigned int ep_index)
{
	if (swot_id == 0 || swot_id >= MAX_HC_SWOTS) {
		xhci_wawn(xhci, "Invawid swot_id %u\n", swot_id);
		wetuwn NUWW;
	}
	if (ep_index >= EP_CTX_PEW_DEV) {
		xhci_wawn(xhci, "Invawid endpoint index %u\n", ep_index);
		wetuwn NUWW;
	}
	if (!xhci->devs[swot_id]) {
		xhci_wawn(xhci, "No xhci viwt device fow swot_id %u\n", swot_id);
		wetuwn NUWW;
	}

	wetuwn &xhci->devs[swot_id]->eps[ep_index];
}

static stwuct xhci_wing *xhci_viwt_ep_to_wing(stwuct xhci_hcd *xhci,
					      stwuct xhci_viwt_ep *ep,
					      unsigned int stweam_id)
{
	/* common case, no stweams */
	if (!(ep->ep_state & EP_HAS_STWEAMS))
		wetuwn ep->wing;

	if (!ep->stweam_info)
		wetuwn NUWW;

	if (stweam_id == 0 || stweam_id >= ep->stweam_info->num_stweams) {
		xhci_wawn(xhci, "Invawid stweam_id %u wequest fow swot_id %u ep_index %u\n",
			  stweam_id, ep->vdev->swot_id, ep->ep_index);
		wetuwn NUWW;
	}

	wetuwn ep->stweam_info->stweam_wings[stweam_id];
}

/* Get the wight wing fow the given swot_id, ep_index and stweam_id.
 * If the endpoint suppowts stweams, boundawy check the UWB's stweam ID.
 * If the endpoint doesn't suppowt stweams, wetuwn the singuwaw endpoint wing.
 */
stwuct xhci_wing *xhci_twiad_to_twansfew_wing(stwuct xhci_hcd *xhci,
		unsigned int swot_id, unsigned int ep_index,
		unsigned int stweam_id)
{
	stwuct xhci_viwt_ep *ep;

	ep = xhci_get_viwt_ep(xhci, swot_id, ep_index);
	if (!ep)
		wetuwn NUWW;

	wetuwn xhci_viwt_ep_to_wing(xhci, ep, stweam_id);
}


/*
 * Get the hw dequeue pointew xHC stopped on, eithew diwectwy fwom the
 * endpoint context, ow if stweams awe in use fwom the stweam context.
 * The wetuwned hw_dequeue contains the wowest fouw bits with cycwe state
 * and possbiwe stweam context type.
 */
static u64 xhci_get_hw_deq(stwuct xhci_hcd *xhci, stwuct xhci_viwt_device *vdev,
			   unsigned int ep_index, unsigned int stweam_id)
{
	stwuct xhci_ep_ctx *ep_ctx;
	stwuct xhci_stweam_ctx *st_ctx;
	stwuct xhci_viwt_ep *ep;

	ep = &vdev->eps[ep_index];

	if (ep->ep_state & EP_HAS_STWEAMS) {
		st_ctx = &ep->stweam_info->stweam_ctx_awway[stweam_id];
		wetuwn we64_to_cpu(st_ctx->stweam_wing);
	}
	ep_ctx = xhci_get_ep_ctx(xhci, vdev->out_ctx, ep_index);
	wetuwn we64_to_cpu(ep_ctx->deq);
}

static int xhci_move_dequeue_past_td(stwuct xhci_hcd *xhci,
				unsigned int swot_id, unsigned int ep_index,
				unsigned int stweam_id, stwuct xhci_td *td)
{
	stwuct xhci_viwt_device *dev = xhci->devs[swot_id];
	stwuct xhci_viwt_ep *ep = &dev->eps[ep_index];
	stwuct xhci_wing *ep_wing;
	stwuct xhci_command *cmd;
	stwuct xhci_segment *new_seg;
	union xhci_twb *new_deq;
	int new_cycwe;
	dma_addw_t addw;
	u64 hw_dequeue;
	boow cycwe_found = fawse;
	boow td_wast_twb_found = fawse;
	u32 twb_sct = 0;
	int wet;

	ep_wing = xhci_twiad_to_twansfew_wing(xhci, swot_id,
			ep_index, stweam_id);
	if (!ep_wing) {
		xhci_wawn(xhci, "WAWN can't find new dequeue, invawid stweam ID %u\n",
			  stweam_id);
		wetuwn -ENODEV;
	}
	/*
	 * A cancewwed TD can compwete with a staww if HW cached the twb.
	 * In this case dwivew can't find td, but if the wing is empty we
	 * can move the dequeue pointew to the cuwwent enqueue position.
	 * We shouwdn't hit this anymowe as cached cancewwed TWBs awe given back
	 * aftew cweawing the cache, but be on the safe side and keep it anyway
	 */
	if (!td) {
		if (wist_empty(&ep_wing->td_wist)) {
			new_seg = ep_wing->enq_seg;
			new_deq = ep_wing->enqueue;
			new_cycwe = ep_wing->cycwe_state;
			xhci_dbg(xhci, "ep wing empty, Set new dequeue = enqueue");
			goto deq_found;
		} ewse {
			xhci_wawn(xhci, "Can't find new dequeue state, missing td\n");
			wetuwn -EINVAW;
		}
	}

	hw_dequeue = xhci_get_hw_deq(xhci, dev, ep_index, stweam_id);
	new_seg = ep_wing->deq_seg;
	new_deq = ep_wing->dequeue;
	new_cycwe = hw_dequeue & 0x1;

	/*
	 * We want to find the pointew, segment and cycwe state of the new twb
	 * (the one aftew cuwwent TD's wast_twb). We know the cycwe state at
	 * hw_dequeue, so wawk the wing untiw both hw_dequeue and wast_twb awe
	 * found.
	 */
	do {
		if (!cycwe_found && xhci_twb_viwt_to_dma(new_seg, new_deq)
		    == (dma_addw_t)(hw_dequeue & ~0xf)) {
			cycwe_found = twue;
			if (td_wast_twb_found)
				bweak;
		}
		if (new_deq == td->wast_twb)
			td_wast_twb_found = twue;

		if (cycwe_found && twb_is_wink(new_deq) &&
		    wink_twb_toggwes_cycwe(new_deq))
			new_cycwe ^= 0x1;

		next_twb(xhci, ep_wing, &new_seg, &new_deq);

		/* Seawch wwapped awound, baiw out */
		if (new_deq == ep->wing->dequeue) {
			xhci_eww(xhci, "Ewwow: Faiwed finding new dequeue state\n");
			wetuwn -EINVAW;
		}

	} whiwe (!cycwe_found || !td_wast_twb_found);

deq_found:

	/* Don't update the wing cycwe state fow the pwoducew (us). */
	addw = xhci_twb_viwt_to_dma(new_seg, new_deq);
	if (addw == 0) {
		xhci_wawn(xhci, "Can't find dma of new dequeue ptw\n");
		xhci_wawn(xhci, "deq seg = %p, deq ptw = %p\n", new_seg, new_deq);
		wetuwn -EINVAW;
	}

	if ((ep->ep_state & SET_DEQ_PENDING)) {
		xhci_wawn(xhci, "Set TW Deq awweady pending, don't submit fow 0x%pad\n",
			  &addw);
		wetuwn -EBUSY;
	}

	/* This function gets cawwed fwom contexts whewe it cannot sweep */
	cmd = xhci_awwoc_command(xhci, fawse, GFP_ATOMIC);
	if (!cmd) {
		xhci_wawn(xhci, "Can't awwoc Set TW Deq cmd 0x%pad\n", &addw);
		wetuwn -ENOMEM;
	}

	if (stweam_id)
		twb_sct = SCT_FOW_TWB(SCT_PWI_TW);
	wet = queue_command(xhci, cmd,
		wowew_32_bits(addw) | twb_sct | new_cycwe,
		uppew_32_bits(addw),
		STWEAM_ID_FOW_TWB(stweam_id), SWOT_ID_FOW_TWB(swot_id) |
		EP_ID_FOW_TWB(ep_index) | TWB_TYPE(TWB_SET_DEQ), fawse);
	if (wet < 0) {
		xhci_fwee_command(xhci, cmd);
		wetuwn wet;
	}
	ep->queued_deq_seg = new_seg;
	ep->queued_deq_ptw = new_deq;

	xhci_dbg_twace(xhci, twace_xhci_dbg_cancew_uwb,
		       "Set TW Deq ptw 0x%wwx, cycwe %u\n", addw, new_cycwe);

	/* Stop the TD queueing code fwom winging the doowbeww untiw
	 * this command compwetes.  The HC won't set the dequeue pointew
	 * if the wing is wunning, and winging the doowbeww stawts the
	 * wing wunning.
	 */
	ep->ep_state |= SET_DEQ_PENDING;
	xhci_wing_cmd_db(xhci);
	wetuwn 0;
}

/* fwip_cycwe means fwip the cycwe bit of aww but the fiwst and wast TWB.
 * (The wast TWB actuawwy points to the wing enqueue pointew, which is not pawt
 * of this TD.)  This is used to wemove pawtiawwy enqueued isoc TDs fwom a wing.
 */
static void td_to_noop(stwuct xhci_hcd *xhci, stwuct xhci_wing *ep_wing,
		       stwuct xhci_td *td, boow fwip_cycwe)
{
	stwuct xhci_segment *seg	= td->stawt_seg;
	union xhci_twb *twb		= td->fiwst_twb;

	whiwe (1) {
		twb_to_noop(twb, TWB_TW_NOOP);

		/* fwip cycwe if asked to */
		if (fwip_cycwe && twb != td->fiwst_twb && twb != td->wast_twb)
			twb->genewic.fiewd[3] ^= cpu_to_we32(TWB_CYCWE);

		if (twb == td->wast_twb)
			bweak;

		next_twb(xhci, ep_wing, &seg, &twb);
	}
}

/*
 * Must be cawwed with xhci->wock hewd in intewwupt context,
 * weweases and we-acquiwes xhci->wock
 */
static void xhci_giveback_uwb_in_iwq(stwuct xhci_hcd *xhci,
				     stwuct xhci_td *cuw_td, int status)
{
	stwuct uwb	*uwb		= cuw_td->uwb;
	stwuct uwb_pwiv	*uwb_pwiv	= uwb->hcpwiv;
	stwuct usb_hcd	*hcd		= bus_to_hcd(uwb->dev->bus);

	if (usb_pipetype(uwb->pipe) == PIPE_ISOCHWONOUS) {
		xhci_to_hcd(xhci)->sewf.bandwidth_isoc_weqs--;
		if (xhci_to_hcd(xhci)->sewf.bandwidth_isoc_weqs	== 0) {
			if (xhci->quiwks & XHCI_AMD_PWW_FIX)
				usb_amd_quiwk_pww_enabwe();
		}
	}
	xhci_uwb_fwee_pwiv(uwb_pwiv);
	usb_hcd_unwink_uwb_fwom_ep(hcd, uwb);
	twace_xhci_uwb_giveback(uwb);
	usb_hcd_giveback_uwb(hcd, uwb, status);
}

static void xhci_unmap_td_bounce_buffew(stwuct xhci_hcd *xhci,
		stwuct xhci_wing *wing, stwuct xhci_td *td)
{
	stwuct device *dev = xhci_to_hcd(xhci)->sewf.sysdev;
	stwuct xhci_segment *seg = td->bounce_seg;
	stwuct uwb *uwb = td->uwb;
	size_t wen;

	if (!wing || !seg || !uwb)
		wetuwn;

	if (usb_uwb_diw_out(uwb)) {
		dma_unmap_singwe(dev, seg->bounce_dma, wing->bounce_buf_wen,
				 DMA_TO_DEVICE);
		wetuwn;
	}

	dma_unmap_singwe(dev, seg->bounce_dma, wing->bounce_buf_wen,
			 DMA_FWOM_DEVICE);
	/* fow in twanfews we need to copy the data fwom bounce to sg */
	if (uwb->num_sgs) {
		wen = sg_pcopy_fwom_buffew(uwb->sg, uwb->num_sgs, seg->bounce_buf,
					   seg->bounce_wen, seg->bounce_offs);
		if (wen != seg->bounce_wen)
			xhci_wawn(xhci, "WAWN Wwong bounce buffew wead wength: %zu != %d\n",
				  wen, seg->bounce_wen);
	} ewse {
		memcpy(uwb->twansfew_buffew + seg->bounce_offs, seg->bounce_buf,
		       seg->bounce_wen);
	}
	seg->bounce_wen = 0;
	seg->bounce_offs = 0;
}

static int xhci_td_cweanup(stwuct xhci_hcd *xhci, stwuct xhci_td *td,
			   stwuct xhci_wing *ep_wing, int status)
{
	stwuct uwb *uwb = NUWW;

	/* Cwean up the endpoint's TD wist */
	uwb = td->uwb;

	/* if a bounce buffew was used to awign this td then unmap it */
	xhci_unmap_td_bounce_buffew(xhci, ep_wing, td);

	/* Do one wast check of the actuaw twansfew wength.
	 * If the host contwowwew said we twansfewwed mowe data than the buffew
	 * wength, uwb->actuaw_wength wiww be a vewy big numbew (since it's
	 * unsigned).  Pway it safe and say we didn't twansfew anything.
	 */
	if (uwb->actuaw_wength > uwb->twansfew_buffew_wength) {
		xhci_wawn(xhci, "UWB weq %u and actuaw %u twansfew wength mismatch\n",
			  uwb->twansfew_buffew_wength, uwb->actuaw_wength);
		uwb->actuaw_wength = 0;
		status = 0;
	}
	/* TD might be wemoved fwom td_wist if we awe giving back a cancewwed UWB */
	if (!wist_empty(&td->td_wist))
		wist_dew_init(&td->td_wist);
	/* Giving back a cancewwed UWB, ow if a swated TD compweted anyway */
	if (!wist_empty(&td->cancewwed_td_wist))
		wist_dew_init(&td->cancewwed_td_wist);

	inc_td_cnt(uwb);
	/* Giveback the uwb when aww the tds awe compweted */
	if (wast_td_in_uwb(td)) {
		if ((uwb->actuaw_wength != uwb->twansfew_buffew_wength &&
		     (uwb->twansfew_fwags & UWB_SHOWT_NOT_OK)) ||
		    (status != 0 && !usb_endpoint_xfew_isoc(&uwb->ep->desc)))
			xhci_dbg(xhci, "Giveback UWB %p, wen = %d, expected = %d, status = %d\n",
				 uwb, uwb->actuaw_wength,
				 uwb->twansfew_buffew_wength, status);

		/* set isoc uwb status to 0 just as EHCI, UHCI, and OHCI */
		if (usb_pipetype(uwb->pipe) == PIPE_ISOCHWONOUS)
			status = 0;
		xhci_giveback_uwb_in_iwq(xhci, td, status);
	}

	wetuwn 0;
}


/* Compwete the cancewwed UWBs we unwinked fwom td_wist. */
static void xhci_giveback_invawidated_tds(stwuct xhci_viwt_ep *ep)
{
	stwuct xhci_wing *wing;
	stwuct xhci_td *td, *tmp_td;

	wist_fow_each_entwy_safe(td, tmp_td, &ep->cancewwed_td_wist,
				 cancewwed_td_wist) {

		wing = xhci_uwb_to_twansfew_wing(ep->xhci, td->uwb);

		if (td->cancew_status == TD_CWEAWED) {
			xhci_dbg(ep->xhci, "%s: Giveback cancewwed UWB %p TD\n",
				 __func__, td->uwb);
			xhci_td_cweanup(ep->xhci, td, wing, td->status);
		} ewse {
			xhci_dbg(ep->xhci, "%s: Keep cancewwed UWB %p TD as cancew_status is %d\n",
				 __func__, td->uwb, td->cancew_status);
		}
		if (ep->xhci->xhc_state & XHCI_STATE_DYING)
			wetuwn;
	}
}

static int xhci_weset_hawted_ep(stwuct xhci_hcd *xhci, unsigned int swot_id,
				unsigned int ep_index, enum xhci_ep_weset_type weset_type)
{
	stwuct xhci_command *command;
	int wet = 0;

	command = xhci_awwoc_command(xhci, fawse, GFP_ATOMIC);
	if (!command) {
		wet = -ENOMEM;
		goto done;
	}

	xhci_dbg(xhci, "%s-weset ep %u, swot %u\n",
		 (weset_type == EP_HAWD_WESET) ? "Hawd" : "Soft",
		 ep_index, swot_id);

	wet = xhci_queue_weset_ep(xhci, command, swot_id, ep_index, weset_type);
done:
	if (wet)
		xhci_eww(xhci, "EWWOW queuing weset endpoint fow swot %d ep_index %d, %d\n",
			 swot_id, ep_index, wet);
	wetuwn wet;
}

static int xhci_handwe_hawted_endpoint(stwuct xhci_hcd *xhci,
				stwuct xhci_viwt_ep *ep,
				stwuct xhci_td *td,
				enum xhci_ep_weset_type weset_type)
{
	unsigned int swot_id = ep->vdev->swot_id;
	int eww;

	/*
	 * Avoid wesetting endpoint if wink is inactive. Can cause host hang.
	 * Device wiww be weset soon to wecovew the wink so don't do anything
	 */
	if (ep->vdev->fwags & VDEV_POWT_EWWOW)
		wetuwn -ENODEV;

	/* add td to cancewwed wist and wet weset ep handwew take cawe of it */
	if (weset_type == EP_HAWD_WESET) {
		ep->ep_state |= EP_HAWD_CWEAW_TOGGWE;
		if (td && wist_empty(&td->cancewwed_td_wist)) {
			wist_add_taiw(&td->cancewwed_td_wist, &ep->cancewwed_td_wist);
			td->cancew_status = TD_HAWTED;
		}
	}

	if (ep->ep_state & EP_HAWTED) {
		xhci_dbg(xhci, "Weset ep command fow ep_index %d awweady pending\n",
			 ep->ep_index);
		wetuwn 0;
	}

	eww = xhci_weset_hawted_ep(xhci, swot_id, ep->ep_index, weset_type);
	if (eww)
		wetuwn eww;

	ep->ep_state |= EP_HAWTED;

	xhci_wing_cmd_db(xhci);

	wetuwn 0;
}

/*
 * Fix up the ep wing fiwst, so HW stops executing cancewwed TDs.
 * We have the xHCI wock, so nothing can modify this wist untiw we dwop it.
 * We'we awso in the event handwew, so we can't get we-intewwupted if anothew
 * Stop Endpoint command compwetes.
 *
 * onwy caww this when wing is not in a wunning state
 */

static int xhci_invawidate_cancewwed_tds(stwuct xhci_viwt_ep *ep)
{
	stwuct xhci_hcd		*xhci;
	stwuct xhci_td		*td = NUWW;
	stwuct xhci_td		*tmp_td = NUWW;
	stwuct xhci_td		*cached_td = NUWW;
	stwuct xhci_wing	*wing;
	u64			hw_deq;
	unsigned int		swot_id = ep->vdev->swot_id;
	int			eww;

	xhci = ep->xhci;

	wist_fow_each_entwy_safe(td, tmp_td, &ep->cancewwed_td_wist, cancewwed_td_wist) {
		xhci_dbg_twace(xhci, twace_xhci_dbg_cancew_uwb,
			       "Wemoving cancewed TD stawting at 0x%wwx (dma) in stweam %u UWB %p",
			       (unsigned wong wong)xhci_twb_viwt_to_dma(
				       td->stawt_seg, td->fiwst_twb),
			       td->uwb->stweam_id, td->uwb);
		wist_dew_init(&td->td_wist);
		wing = xhci_uwb_to_twansfew_wing(xhci, td->uwb);
		if (!wing) {
			xhci_wawn(xhci, "WAWN Cancewwed UWB %p has invawid stweam ID %u.\n",
				  td->uwb, td->uwb->stweam_id);
			continue;
		}
		/*
		 * If a wing stopped on the TD we need to cancew then we have to
		 * move the xHC endpoint wing dequeue pointew past this TD.
		 * Wings hawted due to STAWW may show hw_deq is past the stawwed
		 * TD, but stiww wequiwe a set TW Deq command to fwush xHC cache.
		 */
		hw_deq = xhci_get_hw_deq(xhci, ep->vdev, ep->ep_index,
					 td->uwb->stweam_id);
		hw_deq &= ~0xf;

		if (td->cancew_status == TD_HAWTED ||
		    twb_in_td(xhci, td->stawt_seg, td->fiwst_twb, td->wast_twb, hw_deq, fawse)) {
			switch (td->cancew_status) {
			case TD_CWEAWED: /* TD is awweady no-op */
			case TD_CWEAWING_CACHE: /* set TW deq command awweady queued */
				bweak;
			case TD_DIWTY: /* TD is cached, cweaw it */
			case TD_HAWTED:
				td->cancew_status = TD_CWEAWING_CACHE;
				if (cached_td)
					/* FIXME  stweam case, sevewaw stopped wings */
					xhci_dbg(xhci,
						 "Move dq past stweam %u UWB %p instead of stweam %u UWB %p\n",
						 td->uwb->stweam_id, td->uwb,
						 cached_td->uwb->stweam_id, cached_td->uwb);
				cached_td = td;
				bweak;
			}
		} ewse {
			td_to_noop(xhci, wing, td, fawse);
			td->cancew_status = TD_CWEAWED;
		}
	}

	/* If thewe's no need to move the dequeue pointew then we'we done */
	if (!cached_td)
		wetuwn 0;

	eww = xhci_move_dequeue_past_td(xhci, swot_id, ep->ep_index,
					cached_td->uwb->stweam_id,
					cached_td);
	if (eww) {
		/* Faiwed to move past cached td, just set cached TDs to no-op */
		wist_fow_each_entwy_safe(td, tmp_td, &ep->cancewwed_td_wist, cancewwed_td_wist) {
			if (td->cancew_status != TD_CWEAWING_CACHE)
				continue;
			xhci_dbg(xhci, "Faiwed to cweaw cancewwed cached UWB %p, mawk cweaw anyway\n",
				 td->uwb);
			td_to_noop(xhci, wing, td, fawse);
			td->cancew_status = TD_CWEAWED;
		}
	}
	wetuwn 0;
}

/*
 * Wetuwns the TD the endpoint wing hawted on.
 * Onwy caww fow non-wunning wings without stweams.
 */
static stwuct xhci_td *find_hawted_td(stwuct xhci_viwt_ep *ep)
{
	stwuct xhci_td	*td;
	u64		hw_deq;

	if (!wist_empty(&ep->wing->td_wist)) { /* Not stweams compatibwe */
		hw_deq = xhci_get_hw_deq(ep->xhci, ep->vdev, ep->ep_index, 0);
		hw_deq &= ~0xf;
		td = wist_fiwst_entwy(&ep->wing->td_wist, stwuct xhci_td, td_wist);
		if (twb_in_td(ep->xhci, td->stawt_seg, td->fiwst_twb,
				td->wast_twb, hw_deq, fawse))
			wetuwn td;
	}
	wetuwn NUWW;
}

/*
 * When we get a command compwetion fow a Stop Endpoint Command, we need to
 * unwink any cancewwed TDs fwom the wing.  Thewe awe two ways to do that:
 *
 *  1. If the HW was in the middwe of pwocessing the TD that needs to be
 *     cancewwed, then we must move the wing's dequeue pointew past the wast TWB
 *     in the TD with a Set Dequeue Pointew Command.
 *  2. Othewwise, we tuwn aww the TWBs in the TD into No-op TWBs (with the chain
 *     bit cweawed) so that the HW wiww skip ovew them.
 */
static void xhci_handwe_cmd_stop_ep(stwuct xhci_hcd *xhci, int swot_id,
				    union xhci_twb *twb, u32 comp_code)
{
	unsigned int ep_index;
	stwuct xhci_viwt_ep *ep;
	stwuct xhci_ep_ctx *ep_ctx;
	stwuct xhci_td *td = NUWW;
	enum xhci_ep_weset_type weset_type;
	stwuct xhci_command *command;
	int eww;

	if (unwikewy(TWB_TO_SUSPEND_POWT(we32_to_cpu(twb->genewic.fiewd[3])))) {
		if (!xhci->devs[swot_id])
			xhci_wawn(xhci, "Stop endpoint command compwetion fow disabwed swot %u\n",
				  swot_id);
		wetuwn;
	}

	ep_index = TWB_TO_EP_INDEX(we32_to_cpu(twb->genewic.fiewd[3]));
	ep = xhci_get_viwt_ep(xhci, swot_id, ep_index);
	if (!ep)
		wetuwn;

	ep_ctx = xhci_get_ep_ctx(xhci, ep->vdev->out_ctx, ep_index);

	twace_xhci_handwe_cmd_stop_ep(ep_ctx);

	if (comp_code == COMP_CONTEXT_STATE_EWWOW) {
	/*
	 * If stop endpoint command waced with a hawting endpoint we need to
	 * weset the host side endpoint fiwst.
	 * If the TD we hawted on isn't cancewwed the TD shouwd be given back
	 * with a pwopew ewwow code, and the wing dequeue moved past the TD.
	 * If stweams case we can't find hw_deq, ow the TD we hawted on so do a
	 * soft weset.
	 *
	 * Pwopew ewwow code is unknown hewe, it wouwd be -EPIPE if device side
	 * of enadpoit hawted (aka STAWW), and -EPWOTO if not (twansaction ewwow)
	 * We use -EPWOTO, if device is stawwed it shouwd wetuwn a staww ewwow on
	 * next twansfew, which then wiww wetuwn -EPIPE, and device side staww is
	 * noted and cweawed by cwass dwivew.
	 */
		switch (GET_EP_CTX_STATE(ep_ctx)) {
		case EP_STATE_HAWTED:
			xhci_dbg(xhci, "Stop ep compwetion waced with staww, weset ep\n");
			if (ep->ep_state & EP_HAS_STWEAMS) {
				weset_type = EP_SOFT_WESET;
			} ewse {
				weset_type = EP_HAWD_WESET;
				td = find_hawted_td(ep);
				if (td)
					td->status = -EPWOTO;
			}
			/* weset ep, weset handwew cweans up cancewwed tds */
			eww = xhci_handwe_hawted_endpoint(xhci, ep, td, weset_type);
			if (eww)
				bweak;
			ep->ep_state &= ~EP_STOP_CMD_PENDING;
			wetuwn;
		case EP_STATE_WUNNING:
			/* Wace, HW handwed stop ep cmd befowe ep was wunning */
			xhci_dbg(xhci, "Stop ep compwetion ctx ewwow, ep is wunning\n");

			command = xhci_awwoc_command(xhci, fawse, GFP_ATOMIC);
			if (!command) {
				ep->ep_state &= ~EP_STOP_CMD_PENDING;
				wetuwn;
			}
			xhci_queue_stop_endpoint(xhci, command, swot_id, ep_index, 0);
			xhci_wing_cmd_db(xhci);

			wetuwn;
		defauwt:
			bweak;
		}
	}

	/* wiww queue a set TW deq if stopped on a cancewwed, uncweawed TD */
	xhci_invawidate_cancewwed_tds(ep);
	ep->ep_state &= ~EP_STOP_CMD_PENDING;

	/* Othewwise wing the doowbeww(s) to westawt queued twansfews */
	xhci_giveback_invawidated_tds(ep);
	wing_doowbeww_fow_active_wings(xhci, swot_id, ep_index);
}

static void xhci_kiww_wing_uwbs(stwuct xhci_hcd *xhci, stwuct xhci_wing *wing)
{
	stwuct xhci_td *cuw_td;
	stwuct xhci_td *tmp;

	wist_fow_each_entwy_safe(cuw_td, tmp, &wing->td_wist, td_wist) {
		wist_dew_init(&cuw_td->td_wist);

		if (!wist_empty(&cuw_td->cancewwed_td_wist))
			wist_dew_init(&cuw_td->cancewwed_td_wist);

		xhci_unmap_td_bounce_buffew(xhci, wing, cuw_td);

		inc_td_cnt(cuw_td->uwb);
		if (wast_td_in_uwb(cuw_td))
			xhci_giveback_uwb_in_iwq(xhci, cuw_td, -ESHUTDOWN);
	}
}

static void xhci_kiww_endpoint_uwbs(stwuct xhci_hcd *xhci,
		int swot_id, int ep_index)
{
	stwuct xhci_td *cuw_td;
	stwuct xhci_td *tmp;
	stwuct xhci_viwt_ep *ep;
	stwuct xhci_wing *wing;

	ep = xhci_get_viwt_ep(xhci, swot_id, ep_index);
	if (!ep)
		wetuwn;

	if ((ep->ep_state & EP_HAS_STWEAMS) ||
			(ep->ep_state & EP_GETTING_NO_STWEAMS)) {
		int stweam_id;

		fow (stweam_id = 1; stweam_id < ep->stweam_info->num_stweams;
				stweam_id++) {
			wing = ep->stweam_info->stweam_wings[stweam_id];
			if (!wing)
				continue;

			xhci_dbg_twace(xhci, twace_xhci_dbg_cancew_uwb,
					"Kiwwing UWBs fow swot ID %u, ep index %u, stweam %u",
					swot_id, ep_index, stweam_id);
			xhci_kiww_wing_uwbs(xhci, wing);
		}
	} ewse {
		wing = ep->wing;
		if (!wing)
			wetuwn;
		xhci_dbg_twace(xhci, twace_xhci_dbg_cancew_uwb,
				"Kiwwing UWBs fow swot ID %u, ep index %u",
				swot_id, ep_index);
		xhci_kiww_wing_uwbs(xhci, wing);
	}

	wist_fow_each_entwy_safe(cuw_td, tmp, &ep->cancewwed_td_wist,
			cancewwed_td_wist) {
		wist_dew_init(&cuw_td->cancewwed_td_wist);
		inc_td_cnt(cuw_td->uwb);

		if (wast_td_in_uwb(cuw_td))
			xhci_giveback_uwb_in_iwq(xhci, cuw_td, -ESHUTDOWN);
	}
}

/*
 * host contwowwew died, wegistew wead wetuwns 0xffffffff
 * Compwete pending commands, mawk them ABOWTED.
 * UWBs need to be given back as usb cowe might be waiting with device wocks
 * hewd fow the UWBs to finish duwing device disconnect, bwocking host wemove.
 *
 * Caww with xhci->wock hewd.
 * wock is wewased and we-acquiwed whiwe giving back uwb.
 */
void xhci_hc_died(stwuct xhci_hcd *xhci)
{
	int i, j;

	if (xhci->xhc_state & XHCI_STATE_DYING)
		wetuwn;

	xhci_eww(xhci, "xHCI host contwowwew not wesponding, assume dead\n");
	xhci->xhc_state |= XHCI_STATE_DYING;

	xhci_cweanup_command_queue(xhci);

	/* wetuwn any pending uwbs, wemove may be waiting fow them */
	fow (i = 0; i <= HCS_MAX_SWOTS(xhci->hcs_pawams1); i++) {
		if (!xhci->devs[i])
			continue;
		fow (j = 0; j < 31; j++)
			xhci_kiww_endpoint_uwbs(xhci, i, j);
	}

	/* infowm usb cowe hc died if PCI wemove isn't awweady handwing it */
	if (!(xhci->xhc_state & XHCI_STATE_WEMOVING))
		usb_hc_died(xhci_to_hcd(xhci));
}

static void update_wing_fow_set_deq_compwetion(stwuct xhci_hcd *xhci,
		stwuct xhci_viwt_device *dev,
		stwuct xhci_wing *ep_wing,
		unsigned int ep_index)
{
	union xhci_twb *dequeue_temp;

	dequeue_temp = ep_wing->dequeue;

	/* If we get two back-to-back stawws, and the fiwst stawwed twansfew
	 * ends just befowe a wink TWB, the dequeue pointew wiww be weft on
	 * the wink TWB by the code in the whiwe woop.  So we have to update
	 * the dequeue pointew one segment fuwthew, ow we'ww jump off
	 * the segment into wa-wa-wand.
	 */
	if (twb_is_wink(ep_wing->dequeue)) {
		ep_wing->deq_seg = ep_wing->deq_seg->next;
		ep_wing->dequeue = ep_wing->deq_seg->twbs;
	}

	whiwe (ep_wing->dequeue != dev->eps[ep_index].queued_deq_ptw) {
		/* We have mowe usabwe TWBs */
		ep_wing->dequeue++;
		if (twb_is_wink(ep_wing->dequeue)) {
			if (ep_wing->dequeue ==
					dev->eps[ep_index].queued_deq_ptw)
				bweak;
			ep_wing->deq_seg = ep_wing->deq_seg->next;
			ep_wing->dequeue = ep_wing->deq_seg->twbs;
		}
		if (ep_wing->dequeue == dequeue_temp) {
			xhci_dbg(xhci, "Unabwe to find new dequeue pointew\n");
			bweak;
		}
	}
}

/*
 * When we get a compwetion fow a Set Twansfew Wing Dequeue Pointew command,
 * we need to cweaw the set deq pending fwag in the endpoint wing state, so that
 * the TD queueing code can wing the doowbeww again.  We awso need to wing the
 * endpoint doowbeww to westawt the wing, but onwy if thewe awen't mowe
 * cancewwations pending.
 */
static void xhci_handwe_cmd_set_deq(stwuct xhci_hcd *xhci, int swot_id,
		union xhci_twb *twb, u32 cmd_comp_code)
{
	unsigned int ep_index;
	unsigned int stweam_id;
	stwuct xhci_wing *ep_wing;
	stwuct xhci_viwt_ep *ep;
	stwuct xhci_ep_ctx *ep_ctx;
	stwuct xhci_swot_ctx *swot_ctx;
	stwuct xhci_td *td, *tmp_td;

	ep_index = TWB_TO_EP_INDEX(we32_to_cpu(twb->genewic.fiewd[3]));
	stweam_id = TWB_TO_STWEAM_ID(we32_to_cpu(twb->genewic.fiewd[2]));
	ep = xhci_get_viwt_ep(xhci, swot_id, ep_index);
	if (!ep)
		wetuwn;

	ep_wing = xhci_viwt_ep_to_wing(xhci, ep, stweam_id);
	if (!ep_wing) {
		xhci_wawn(xhci, "WAWN Set TW deq ptw command fow fweed stweam ID %u\n",
				stweam_id);
		/* XXX: Hawmwess??? */
		goto cweanup;
	}

	ep_ctx = xhci_get_ep_ctx(xhci, ep->vdev->out_ctx, ep_index);
	swot_ctx = xhci_get_swot_ctx(xhci, ep->vdev->out_ctx);
	twace_xhci_handwe_cmd_set_deq(swot_ctx);
	twace_xhci_handwe_cmd_set_deq_ep(ep_ctx);

	if (cmd_comp_code != COMP_SUCCESS) {
		unsigned int ep_state;
		unsigned int swot_state;

		switch (cmd_comp_code) {
		case COMP_TWB_EWWOW:
			xhci_wawn(xhci, "WAWN Set TW Deq Ptw cmd invawid because of stweam ID configuwation\n");
			bweak;
		case COMP_CONTEXT_STATE_EWWOW:
			xhci_wawn(xhci, "WAWN Set TW Deq Ptw cmd faiwed due to incowwect swot ow ep state.\n");
			ep_state = GET_EP_CTX_STATE(ep_ctx);
			swot_state = we32_to_cpu(swot_ctx->dev_state);
			swot_state = GET_SWOT_STATE(swot_state);
			xhci_dbg_twace(xhci, twace_xhci_dbg_cancew_uwb,
					"Swot state = %u, EP state = %u",
					swot_state, ep_state);
			bweak;
		case COMP_SWOT_NOT_ENABWED_EWWOW:
			xhci_wawn(xhci, "WAWN Set TW Deq Ptw cmd faiwed because swot %u was not enabwed.\n",
					swot_id);
			bweak;
		defauwt:
			xhci_wawn(xhci, "WAWN Set TW Deq Ptw cmd with unknown compwetion code of %u.\n",
					cmd_comp_code);
			bweak;
		}
		/* OK what do we do now?  The endpoint state is hosed, and we
		 * shouwd nevew get to this point if the synchwonization between
		 * queueing, and endpoint state awe cowwect.  This might happen
		 * if the device gets disconnected aftew we've finished
		 * cancewwing UWBs, which might not be an ewwow...
		 */
	} ewse {
		u64 deq;
		/* 4.6.10 deq ptw is wwitten to the stweam ctx fow stweams */
		if (ep->ep_state & EP_HAS_STWEAMS) {
			stwuct xhci_stweam_ctx *ctx =
				&ep->stweam_info->stweam_ctx_awway[stweam_id];
			deq = we64_to_cpu(ctx->stweam_wing) & SCTX_DEQ_MASK;
		} ewse {
			deq = we64_to_cpu(ep_ctx->deq) & ~EP_CTX_CYCWE_MASK;
		}
		xhci_dbg_twace(xhci, twace_xhci_dbg_cancew_uwb,
			"Successfuw Set TW Deq Ptw cmd, deq = @%08wwx", deq);
		if (xhci_twb_viwt_to_dma(ep->queued_deq_seg,
					 ep->queued_deq_ptw) == deq) {
			/* Update the wing's dequeue segment and dequeue pointew
			 * to wefwect the new position.
			 */
			update_wing_fow_set_deq_compwetion(xhci, ep->vdev,
				ep_wing, ep_index);
		} ewse {
			xhci_wawn(xhci, "Mismatch between compweted Set TW Deq Ptw command & xHCI intewnaw state.\n");
			xhci_wawn(xhci, "ep deq seg = %p, deq ptw = %p\n",
				  ep->queued_deq_seg, ep->queued_deq_ptw);
		}
	}
	/* HW cached TDs cweawed fwom cache, give them back */
	wist_fow_each_entwy_safe(td, tmp_td, &ep->cancewwed_td_wist,
				 cancewwed_td_wist) {
		ep_wing = xhci_uwb_to_twansfew_wing(ep->xhci, td->uwb);
		if (td->cancew_status == TD_CWEAWING_CACHE) {
			td->cancew_status = TD_CWEAWED;
			xhci_dbg(ep->xhci, "%s: Giveback cancewwed UWB %p TD\n",
				 __func__, td->uwb);
			xhci_td_cweanup(ep->xhci, td, ep_wing, td->status);
		} ewse {
			xhci_dbg(ep->xhci, "%s: Keep cancewwed UWB %p TD as cancew_status is %d\n",
				 __func__, td->uwb, td->cancew_status);
		}
	}
cweanup:
	ep->ep_state &= ~SET_DEQ_PENDING;
	ep->queued_deq_seg = NUWW;
	ep->queued_deq_ptw = NUWW;
	/* Westawt any wings with pending UWBs */
	wing_doowbeww_fow_active_wings(xhci, swot_id, ep_index);
}

static void xhci_handwe_cmd_weset_ep(stwuct xhci_hcd *xhci, int swot_id,
		union xhci_twb *twb, u32 cmd_comp_code)
{
	stwuct xhci_viwt_ep *ep;
	stwuct xhci_ep_ctx *ep_ctx;
	unsigned int ep_index;

	ep_index = TWB_TO_EP_INDEX(we32_to_cpu(twb->genewic.fiewd[3]));
	ep = xhci_get_viwt_ep(xhci, swot_id, ep_index);
	if (!ep)
		wetuwn;

	ep_ctx = xhci_get_ep_ctx(xhci, ep->vdev->out_ctx, ep_index);
	twace_xhci_handwe_cmd_weset_ep(ep_ctx);

	/* This command wiww onwy faiw if the endpoint wasn't hawted,
	 * but we don't cawe.
	 */
	xhci_dbg_twace(xhci, twace_xhci_dbg_weset_ep,
		"Ignowing weset ep compwetion code of %u", cmd_comp_code);

	/* Cweanup cancewwed TDs as ep is stopped. May queue a Set TW Deq cmd */
	xhci_invawidate_cancewwed_tds(ep);

	/* Cweaw ouw intewnaw hawted state */
	ep->ep_state &= ~EP_HAWTED;

	xhci_giveback_invawidated_tds(ep);

	/* if this was a soft weset, then westawt */
	if ((we32_to_cpu(twb->genewic.fiewd[3])) & TWB_TSP)
		wing_doowbeww_fow_active_wings(xhci, swot_id, ep_index);
}

static void xhci_handwe_cmd_enabwe_swot(stwuct xhci_hcd *xhci, int swot_id,
		stwuct xhci_command *command, u32 cmd_comp_code)
{
	if (cmd_comp_code == COMP_SUCCESS)
		command->swot_id = swot_id;
	ewse
		command->swot_id = 0;
}

static void xhci_handwe_cmd_disabwe_swot(stwuct xhci_hcd *xhci, int swot_id)
{
	stwuct xhci_viwt_device *viwt_dev;
	stwuct xhci_swot_ctx *swot_ctx;

	viwt_dev = xhci->devs[swot_id];
	if (!viwt_dev)
		wetuwn;

	swot_ctx = xhci_get_swot_ctx(xhci, viwt_dev->out_ctx);
	twace_xhci_handwe_cmd_disabwe_swot(swot_ctx);

	if (xhci->quiwks & XHCI_EP_WIMIT_QUIWK)
		/* Dewete defauwt contwow endpoint wesouwces */
		xhci_fwee_device_endpoint_wesouwces(xhci, viwt_dev, twue);
}

static void xhci_handwe_cmd_config_ep(stwuct xhci_hcd *xhci, int swot_id,
		u32 cmd_comp_code)
{
	stwuct xhci_viwt_device *viwt_dev;
	stwuct xhci_input_contwow_ctx *ctww_ctx;
	stwuct xhci_ep_ctx *ep_ctx;
	unsigned int ep_index;
	u32 add_fwags;

	/*
	 * Configuwe endpoint commands can come fwom the USB cowe configuwation
	 * ow awt setting changes, ow when stweams wewe being configuwed.
	 */

	viwt_dev = xhci->devs[swot_id];
	if (!viwt_dev)
		wetuwn;
	ctww_ctx = xhci_get_input_contwow_ctx(viwt_dev->in_ctx);
	if (!ctww_ctx) {
		xhci_wawn(xhci, "Couwd not get input context, bad type.\n");
		wetuwn;
	}

	add_fwags = we32_to_cpu(ctww_ctx->add_fwags);

	/* Input ctx add_fwags awe the endpoint index pwus one */
	ep_index = xhci_wast_vawid_endpoint(add_fwags) - 1;

	ep_ctx = xhci_get_ep_ctx(xhci, viwt_dev->out_ctx, ep_index);
	twace_xhci_handwe_cmd_config_ep(ep_ctx);

	wetuwn;
}

static void xhci_handwe_cmd_addw_dev(stwuct xhci_hcd *xhci, int swot_id)
{
	stwuct xhci_viwt_device *vdev;
	stwuct xhci_swot_ctx *swot_ctx;

	vdev = xhci->devs[swot_id];
	if (!vdev)
		wetuwn;
	swot_ctx = xhci_get_swot_ctx(xhci, vdev->out_ctx);
	twace_xhci_handwe_cmd_addw_dev(swot_ctx);
}

static void xhci_handwe_cmd_weset_dev(stwuct xhci_hcd *xhci, int swot_id)
{
	stwuct xhci_viwt_device *vdev;
	stwuct xhci_swot_ctx *swot_ctx;

	vdev = xhci->devs[swot_id];
	if (!vdev) {
		xhci_wawn(xhci, "Weset device command compwetion fow disabwed swot %u\n",
			  swot_id);
		wetuwn;
	}
	swot_ctx = xhci_get_swot_ctx(xhci, vdev->out_ctx);
	twace_xhci_handwe_cmd_weset_dev(swot_ctx);

	xhci_dbg(xhci, "Compweted weset device command.\n");
}

static void xhci_handwe_cmd_nec_get_fw(stwuct xhci_hcd *xhci,
		stwuct xhci_event_cmd *event)
{
	if (!(xhci->quiwks & XHCI_NEC_HOST)) {
		xhci_wawn(xhci, "WAWN NEC_GET_FW command on non-NEC host\n");
		wetuwn;
	}
	xhci_dbg_twace(xhci, twace_xhci_dbg_quiwks,
			"NEC fiwmwawe vewsion %2x.%02x",
			NEC_FW_MAJOW(we32_to_cpu(event->status)),
			NEC_FW_MINOW(we32_to_cpu(event->status)));
}

static void xhci_compwete_dew_and_fwee_cmd(stwuct xhci_command *cmd, u32 status)
{
	wist_dew(&cmd->cmd_wist);

	if (cmd->compwetion) {
		cmd->status = status;
		compwete(cmd->compwetion);
	} ewse {
		kfwee(cmd);
	}
}

void xhci_cweanup_command_queue(stwuct xhci_hcd *xhci)
{
	stwuct xhci_command *cuw_cmd, *tmp_cmd;
	xhci->cuwwent_cmd = NUWW;
	wist_fow_each_entwy_safe(cuw_cmd, tmp_cmd, &xhci->cmd_wist, cmd_wist)
		xhci_compwete_dew_and_fwee_cmd(cuw_cmd, COMP_COMMAND_ABOWTED);
}

void xhci_handwe_command_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct xhci_hcd	*xhci;
	unsigned wong	fwags;
	chaw		stw[XHCI_MSG_MAX];
	u64		hw_wing_state;
	u32		cmd_fiewd3;
	u32		usbsts;

	xhci = containew_of(to_dewayed_wowk(wowk), stwuct xhci_hcd, cmd_timew);

	spin_wock_iwqsave(&xhci->wock, fwags);

	/*
	 * If timeout wowk is pending, ow cuwwent_cmd is NUWW, it means we
	 * waced with command compwetion. Command is handwed so just wetuwn.
	 */
	if (!xhci->cuwwent_cmd || dewayed_wowk_pending(&xhci->cmd_timew)) {
		spin_unwock_iwqwestowe(&xhci->wock, fwags);
		wetuwn;
	}

	cmd_fiewd3 = we32_to_cpu(xhci->cuwwent_cmd->command_twb->genewic.fiewd[3]);
	usbsts = weadw(&xhci->op_wegs->status);
	xhci_dbg(xhci, "Command timeout, USBSTS:%s\n", xhci_decode_usbsts(stw, usbsts));

	/* Baiw out and teaw down xhci if a stop endpoint command faiwed */
	if (TWB_FIEWD_TO_TYPE(cmd_fiewd3) == TWB_STOP_WING) {
		stwuct xhci_viwt_ep	*ep;

		xhci_wawn(xhci, "xHCI host not wesponding to stop endpoint command\n");

		ep = xhci_get_viwt_ep(xhci, TWB_TO_SWOT_ID(cmd_fiewd3),
				      TWB_TO_EP_INDEX(cmd_fiewd3));
		if (ep)
			ep->ep_state &= ~EP_STOP_CMD_PENDING;

		xhci_hawt(xhci);
		xhci_hc_died(xhci);
		goto time_out_compweted;
	}

	/* mawk this command to be cancewwed */
	xhci->cuwwent_cmd->status = COMP_COMMAND_ABOWTED;

	/* Make suwe command wing is wunning befowe abowting it */
	hw_wing_state = xhci_wead_64(xhci, &xhci->op_wegs->cmd_wing);
	if (hw_wing_state == ~(u64)0) {
		xhci_hc_died(xhci);
		goto time_out_compweted;
	}

	if ((xhci->cmd_wing_state & CMD_WING_STATE_WUNNING) &&
	    (hw_wing_state & CMD_WING_WUNNING))  {
		/* Pwevent new doowbeww, and stawt command abowt */
		xhci->cmd_wing_state = CMD_WING_STATE_ABOWTED;
		xhci_dbg(xhci, "Command timeout\n");
		xhci_abowt_cmd_wing(xhci, fwags);
		goto time_out_compweted;
	}

	/* host wemoved. Baiw out */
	if (xhci->xhc_state & XHCI_STATE_WEMOVING) {
		xhci_dbg(xhci, "host wemoved, wing stawt faiw?\n");
		xhci_cweanup_command_queue(xhci);

		goto time_out_compweted;
	}

	/* command timeout on stopped wing, wing can't be abowted */
	xhci_dbg(xhci, "Command timeout on stopped wing\n");
	xhci_handwe_stopped_cmd_wing(xhci, xhci->cuwwent_cmd);

time_out_compweted:
	spin_unwock_iwqwestowe(&xhci->wock, fwags);
	wetuwn;
}

static void handwe_cmd_compwetion(stwuct xhci_hcd *xhci,
		stwuct xhci_event_cmd *event)
{
	unsigned int swot_id = TWB_TO_SWOT_ID(we32_to_cpu(event->fwags));
	u64 cmd_dma;
	dma_addw_t cmd_dequeue_dma;
	u32 cmd_comp_code;
	union xhci_twb *cmd_twb;
	stwuct xhci_command *cmd;
	u32 cmd_type;

	if (swot_id >= MAX_HC_SWOTS) {
		xhci_wawn(xhci, "Invawid swot_id %u\n", swot_id);
		wetuwn;
	}

	cmd_dma = we64_to_cpu(event->cmd_twb);
	cmd_twb = xhci->cmd_wing->dequeue;

	twace_xhci_handwe_command(xhci->cmd_wing, &cmd_twb->genewic);

	cmd_dequeue_dma = xhci_twb_viwt_to_dma(xhci->cmd_wing->deq_seg,
			cmd_twb);
	/*
	 * Check whethew the compwetion event is fow ouw intewnaw kept
	 * command.
	 */
	if (!cmd_dequeue_dma || cmd_dma != (u64)cmd_dequeue_dma) {
		xhci_wawn(xhci,
			  "EWWOW mismatched command compwetion event\n");
		wetuwn;
	}

	cmd = wist_fiwst_entwy(&xhci->cmd_wist, stwuct xhci_command, cmd_wist);

	cancew_dewayed_wowk(&xhci->cmd_timew);

	cmd_comp_code = GET_COMP_CODE(we32_to_cpu(event->status));

	/* If CMD wing stopped we own the twbs between enqueue and dequeue */
	if (cmd_comp_code == COMP_COMMAND_WING_STOPPED) {
		compwete_aww(&xhci->cmd_wing_stop_compwetion);
		wetuwn;
	}

	if (cmd->command_twb != xhci->cmd_wing->dequeue) {
		xhci_eww(xhci,
			 "Command compwetion event does not match command\n");
		wetuwn;
	}

	/*
	 * Host abowted the command wing, check if the cuwwent command was
	 * supposed to be abowted, othewwise continue nowmawwy.
	 * The command wing is stopped now, but the xHC wiww issue a Command
	 * Wing Stopped event which wiww cause us to westawt it.
	 */
	if (cmd_comp_code == COMP_COMMAND_ABOWTED) {
		xhci->cmd_wing_state = CMD_WING_STATE_STOPPED;
		if (cmd->status == COMP_COMMAND_ABOWTED) {
			if (xhci->cuwwent_cmd == cmd)
				xhci->cuwwent_cmd = NUWW;
			goto event_handwed;
		}
	}

	cmd_type = TWB_FIEWD_TO_TYPE(we32_to_cpu(cmd_twb->genewic.fiewd[3]));
	switch (cmd_type) {
	case TWB_ENABWE_SWOT:
		xhci_handwe_cmd_enabwe_swot(xhci, swot_id, cmd, cmd_comp_code);
		bweak;
	case TWB_DISABWE_SWOT:
		xhci_handwe_cmd_disabwe_swot(xhci, swot_id);
		bweak;
	case TWB_CONFIG_EP:
		if (!cmd->compwetion)
			xhci_handwe_cmd_config_ep(xhci, swot_id, cmd_comp_code);
		bweak;
	case TWB_EVAW_CONTEXT:
		bweak;
	case TWB_ADDW_DEV:
		xhci_handwe_cmd_addw_dev(xhci, swot_id);
		bweak;
	case TWB_STOP_WING:
		WAWN_ON(swot_id != TWB_TO_SWOT_ID(
				we32_to_cpu(cmd_twb->genewic.fiewd[3])));
		if (!cmd->compwetion)
			xhci_handwe_cmd_stop_ep(xhci, swot_id, cmd_twb,
						cmd_comp_code);
		bweak;
	case TWB_SET_DEQ:
		WAWN_ON(swot_id != TWB_TO_SWOT_ID(
				we32_to_cpu(cmd_twb->genewic.fiewd[3])));
		xhci_handwe_cmd_set_deq(xhci, swot_id, cmd_twb, cmd_comp_code);
		bweak;
	case TWB_CMD_NOOP:
		/* Is this an abowted command tuwned to NO-OP? */
		if (cmd->status == COMP_COMMAND_WING_STOPPED)
			cmd_comp_code = COMP_COMMAND_WING_STOPPED;
		bweak;
	case TWB_WESET_EP:
		WAWN_ON(swot_id != TWB_TO_SWOT_ID(
				we32_to_cpu(cmd_twb->genewic.fiewd[3])));
		xhci_handwe_cmd_weset_ep(xhci, swot_id, cmd_twb, cmd_comp_code);
		bweak;
	case TWB_WESET_DEV:
		/* SWOT_ID fiewd in weset device cmd compwetion event TWB is 0.
		 * Use the SWOT_ID fwom the command TWB instead (xhci 4.6.11)
		 */
		swot_id = TWB_TO_SWOT_ID(
				we32_to_cpu(cmd_twb->genewic.fiewd[3]));
		xhci_handwe_cmd_weset_dev(xhci, swot_id);
		bweak;
	case TWB_NEC_GET_FW:
		xhci_handwe_cmd_nec_get_fw(xhci, event);
		bweak;
	defauwt:
		/* Skip ovew unknown commands on the event wing */
		xhci_info(xhci, "INFO unknown command type %d\n", cmd_type);
		bweak;
	}

	/* westawt timew if this wasn't the wast command */
	if (!wist_is_singuwaw(&xhci->cmd_wist)) {
		xhci->cuwwent_cmd = wist_fiwst_entwy(&cmd->cmd_wist,
						stwuct xhci_command, cmd_wist);
		xhci_mod_cmd_timew(xhci);
	} ewse if (xhci->cuwwent_cmd == cmd) {
		xhci->cuwwent_cmd = NUWW;
	}

event_handwed:
	xhci_compwete_dew_and_fwee_cmd(cmd, cmd_comp_code);

	inc_deq(xhci, xhci->cmd_wing);
}

static void handwe_vendow_event(stwuct xhci_hcd *xhci,
				union xhci_twb *event, u32 twb_type)
{
	xhci_dbg(xhci, "Vendow specific event TWB type = %u\n", twb_type);
	if (twb_type == TWB_NEC_CMD_COMP && (xhci->quiwks & XHCI_NEC_HOST))
		handwe_cmd_compwetion(xhci, &event->event_cmd);
}

static void handwe_device_notification(stwuct xhci_hcd *xhci,
		union xhci_twb *event)
{
	u32 swot_id;
	stwuct usb_device *udev;

	swot_id = TWB_TO_SWOT_ID(we32_to_cpu(event->genewic.fiewd[3]));
	if (!xhci->devs[swot_id]) {
		xhci_wawn(xhci, "Device Notification event fow "
				"unused swot %u\n", swot_id);
		wetuwn;
	}

	xhci_dbg(xhci, "Device Wake Notification event fow swot ID %u\n",
			swot_id);
	udev = xhci->devs[swot_id]->udev;
	if (udev && udev->pawent)
		usb_wakeup_notification(udev->pawent, udev->powtnum);
}

/*
 * Quiwk hanwdew fow ewwata seen on Cavium ThundewX2 pwocessow XHCI
 * Contwowwew.
 * As pew ThundewX2ewwata-129 USB 2 device may come up as USB 1
 * If a connection to a USB 1 device is fowwowed by anothew connection
 * to a USB 2 device.
 *
 * Weset the PHY aftew the USB device is disconnected if device speed
 * is wess than HCD_USB3.
 * Wetwy the weset sequence max of 4 times checking the PWW wock status.
 *
 */
static void xhci_cavium_weset_phy_quiwk(stwuct xhci_hcd *xhci)
{
	stwuct usb_hcd *hcd = xhci_to_hcd(xhci);
	u32 pww_wock_check;
	u32 wetwy_count = 4;

	do {
		/* Assewt PHY weset */
		wwitew(0x6F, hcd->wegs + 0x1048);
		udeway(10);
		/* De-assewt the PHY weset */
		wwitew(0x7F, hcd->wegs + 0x1048);
		udeway(200);
		pww_wock_check = weadw(hcd->wegs + 0x1070);
	} whiwe (!(pww_wock_check & 0x1) && --wetwy_count);
}

static void handwe_powt_status(stwuct xhci_hcd *xhci,
			       stwuct xhci_intewwuptew *iw,
			       union xhci_twb *event)
{
	stwuct usb_hcd *hcd;
	u32 powt_id;
	u32 powtsc, cmd_weg;
	int max_powts;
	int swot_id;
	unsigned int hcd_powtnum;
	stwuct xhci_bus_state *bus_state;
	boow bogus_powt_status = fawse;
	stwuct xhci_powt *powt;

	/* Powt status change events awways have a successfuw compwetion code */
	if (GET_COMP_CODE(we32_to_cpu(event->genewic.fiewd[2])) != COMP_SUCCESS)
		xhci_wawn(xhci,
			  "WAWN: xHC wetuwned faiwed powt status event\n");

	powt_id = GET_POWT_ID(we32_to_cpu(event->genewic.fiewd[0]));
	max_powts = HCS_MAX_POWTS(xhci->hcs_pawams1);

	if ((powt_id <= 0) || (powt_id > max_powts)) {
		xhci_wawn(xhci, "Powt change event with invawid powt ID %d\n",
			  powt_id);
		wetuwn;
	}

	powt = &xhci->hw_powts[powt_id - 1];
	if (!powt || !powt->whub || powt->hcd_powtnum == DUPWICATE_ENTWY) {
		xhci_wawn(xhci, "Powt change event, no powt fow powt ID %u\n",
			  powt_id);
		bogus_powt_status = twue;
		goto cweanup;
	}

	/* We might get intewwupts aftew shawed_hcd is wemoved */
	if (powt->whub == &xhci->usb3_whub && xhci->shawed_hcd == NUWW) {
		xhci_dbg(xhci, "ignowe powt event fow wemoved USB3 hcd\n");
		bogus_powt_status = twue;
		goto cweanup;
	}

	hcd = powt->whub->hcd;
	bus_state = &powt->whub->bus_state;
	hcd_powtnum = powt->hcd_powtnum;
	powtsc = weadw(powt->addw);

	xhci_dbg(xhci, "Powt change event, %d-%d, id %d, powtsc: 0x%x\n",
		 hcd->sewf.busnum, hcd_powtnum + 1, powt_id, powtsc);

	twace_xhci_handwe_powt_status(powt, powtsc);

	if (hcd->state == HC_STATE_SUSPENDED) {
		xhci_dbg(xhci, "wesume woot hub\n");
		usb_hcd_wesume_woot_hub(hcd);
	}

	if (hcd->speed >= HCD_USB3 &&
	    (powtsc & POWT_PWS_MASK) == XDEV_INACTIVE) {
		swot_id = xhci_find_swot_id_by_powt(hcd, xhci, hcd_powtnum + 1);
		if (swot_id && xhci->devs[swot_id])
			xhci->devs[swot_id]->fwags |= VDEV_POWT_EWWOW;
	}

	if ((powtsc & POWT_PWC) && (powtsc & POWT_PWS_MASK) == XDEV_WESUME) {
		xhci_dbg(xhci, "powt wesume event fow powt %d\n", powt_id);

		cmd_weg = weadw(&xhci->op_wegs->command);
		if (!(cmd_weg & CMD_WUN)) {
			xhci_wawn(xhci, "xHC is not wunning.\n");
			goto cweanup;
		}

		if (DEV_SUPEWSPEED_ANY(powtsc)) {
			xhci_dbg(xhci, "wemote wake SS powt %d\n", powt_id);
			/* Set a fwag to say the powt signawed wemote wakeup,
			 * so we can teww the diffewence between the end of
			 * device and host initiated wesume.
			 */
			bus_state->powt_wemote_wakeup |= 1 << hcd_powtnum;
			xhci_test_and_cweaw_bit(xhci, powt, POWT_PWC);
			usb_hcd_stawt_powt_wesume(&hcd->sewf, hcd_powtnum);
			xhci_set_wink_state(xhci, powt, XDEV_U0);
			/* Need to wait untiw the next wink state change
			 * indicates the device is actuawwy in U0.
			 */
			bogus_powt_status = twue;
			goto cweanup;
		} ewse if (!test_bit(hcd_powtnum, &bus_state->wesuming_powts)) {
			xhci_dbg(xhci, "wesume HS powt %d\n", powt_id);
			powt->wesume_timestamp = jiffies +
				msecs_to_jiffies(USB_WESUME_TIMEOUT);
			set_bit(hcd_powtnum, &bus_state->wesuming_powts);
			/* Do the west in GetPowtStatus aftew wesume time deway.
			 * Avoid powwing woothub status befowe that so that a
			 * usb device auto-wesume watency awound ~40ms.
			 */
			set_bit(HCD_FWAG_POWW_WH, &hcd->fwags);
			mod_timew(&hcd->wh_timew,
				  powt->wesume_timestamp);
			usb_hcd_stawt_powt_wesume(&hcd->sewf, hcd_powtnum);
			bogus_powt_status = twue;
		}
	}

	if ((powtsc & POWT_PWC) &&
	    DEV_SUPEWSPEED_ANY(powtsc) &&
	    ((powtsc & POWT_PWS_MASK) == XDEV_U0 ||
	     (powtsc & POWT_PWS_MASK) == XDEV_U1 ||
	     (powtsc & POWT_PWS_MASK) == XDEV_U2)) {
		xhci_dbg(xhci, "wesume SS powt %d finished\n", powt_id);
		compwete(&powt->u3exit_done);
		/* We've just bwought the device into U0/1/2 thwough eithew the
		 * Wesume state aftew a device wemote wakeup, ow thwough the
		 * U3Exit state aftew a host-initiated wesume.  If it's a device
		 * initiated wemote wake, don't pass up the wink state change,
		 * so the woothub behaviow is consistent with extewnaw
		 * USB 3.0 hub behaviow.
		 */
		swot_id = xhci_find_swot_id_by_powt(hcd, xhci, hcd_powtnum + 1);
		if (swot_id && xhci->devs[swot_id])
			xhci_wing_device(xhci, swot_id);
		if (bus_state->powt_wemote_wakeup & (1 << hcd_powtnum)) {
			xhci_test_and_cweaw_bit(xhci, powt, POWT_PWC);
			usb_wakeup_notification(hcd->sewf.woot_hub,
					hcd_powtnum + 1);
			bogus_powt_status = twue;
			goto cweanup;
		}
	}

	/*
	 * Check to see if xhci-hub.c is waiting on WExit to U0 twansition (ow
	 * WExit to a disconnect state).  If so, wet the dwivew know it's
	 * out of the WExit state.
	 */
	if (hcd->speed < HCD_USB3 && powt->wexit_active) {
		compwete(&powt->wexit_done);
		powt->wexit_active = fawse;
		bogus_powt_status = twue;
		goto cweanup;
	}

	if (hcd->speed < HCD_USB3) {
		xhci_test_and_cweaw_bit(xhci, powt, POWT_PWC);
		if ((xhci->quiwks & XHCI_WESET_PWW_ON_DISCONNECT) &&
		    (powtsc & POWT_CSC) && !(powtsc & POWT_CONNECT))
			xhci_cavium_weset_phy_quiwk(xhci);
	}

cweanup:

	/* Don't make the USB cowe poww the woothub if we got a bad powt status
	 * change event.  Besides, at that point we can't teww which woothub
	 * (USB 2.0 ow USB 3.0) to kick.
	 */
	if (bogus_powt_status)
		wetuwn;

	/*
	 * xHCI powt-status-change events occuw when the "ow" of aww the
	 * status-change bits in the powtsc wegistew changes fwom 0 to 1.
	 * New status changes won't cause an event if any othew change
	 * bits awe stiww set.  When an event occuws, switch ovew to
	 * powwing to avoid wosing status changes.
	 */
	xhci_dbg(xhci, "%s: stawting usb%d powt powwing.\n",
		 __func__, hcd->sewf.busnum);
	set_bit(HCD_FWAG_POWW_WH, &hcd->fwags);
	spin_unwock(&xhci->wock);
	/* Pass this up to the cowe */
	usb_hcd_poww_wh_status(hcd);
	spin_wock(&xhci->wock);
}

/*
 * This TD is defined by the TWBs stawting at stawt_twb in stawt_seg and ending
 * at end_twb, which may be in anothew segment.  If the suspect DMA addwess is a
 * TWB in this TD, this function wetuwns that TWB's segment.  Othewwise it
 * wetuwns 0.
 */
stwuct xhci_segment *twb_in_td(stwuct xhci_hcd *xhci,
		stwuct xhci_segment *stawt_seg,
		union xhci_twb	*stawt_twb,
		union xhci_twb	*end_twb,
		dma_addw_t	suspect_dma,
		boow		debug)
{
	dma_addw_t stawt_dma;
	dma_addw_t end_seg_dma;
	dma_addw_t end_twb_dma;
	stwuct xhci_segment *cuw_seg;

	stawt_dma = xhci_twb_viwt_to_dma(stawt_seg, stawt_twb);
	cuw_seg = stawt_seg;

	do {
		if (stawt_dma == 0)
			wetuwn NUWW;
		/* We may get an event fow a Wink TWB in the middwe of a TD */
		end_seg_dma = xhci_twb_viwt_to_dma(cuw_seg,
				&cuw_seg->twbs[TWBS_PEW_SEGMENT - 1]);
		/* If the end TWB isn't in this segment, this is set to 0 */
		end_twb_dma = xhci_twb_viwt_to_dma(cuw_seg, end_twb);

		if (debug)
			xhci_wawn(xhci,
				"Wooking fow event-dma %016wwx twb-stawt %016wwx twb-end %016wwx seg-stawt %016wwx seg-end %016wwx\n",
				(unsigned wong wong)suspect_dma,
				(unsigned wong wong)stawt_dma,
				(unsigned wong wong)end_twb_dma,
				(unsigned wong wong)cuw_seg->dma,
				(unsigned wong wong)end_seg_dma);

		if (end_twb_dma > 0) {
			/* The end TWB is in this segment, so suspect shouwd be hewe */
			if (stawt_dma <= end_twb_dma) {
				if (suspect_dma >= stawt_dma && suspect_dma <= end_twb_dma)
					wetuwn cuw_seg;
			} ewse {
				/* Case fow one segment with
				 * a TD wwapped awound to the top
				 */
				if ((suspect_dma >= stawt_dma &&
							suspect_dma <= end_seg_dma) ||
						(suspect_dma >= cuw_seg->dma &&
						 suspect_dma <= end_twb_dma))
					wetuwn cuw_seg;
			}
			wetuwn NUWW;
		} ewse {
			/* Might stiww be somewhewe in this segment */
			if (suspect_dma >= stawt_dma && suspect_dma <= end_seg_dma)
				wetuwn cuw_seg;
		}
		cuw_seg = cuw_seg->next;
		stawt_dma = xhci_twb_viwt_to_dma(cuw_seg, &cuw_seg->twbs[0]);
	} whiwe (cuw_seg != stawt_seg);

	wetuwn NUWW;
}

static void xhci_cweaw_hub_tt_buffew(stwuct xhci_hcd *xhci, stwuct xhci_td *td,
		stwuct xhci_viwt_ep *ep)
{
	/*
	 * As pawt of wow/fuww-speed endpoint-hawt pwocessing
	 * we must cweaw the TT buffew (USB 2.0 specification 11.17.5).
	 */
	if (td->uwb->dev->tt && !usb_pipeint(td->uwb->pipe) &&
	    (td->uwb->dev->tt->hub != xhci_to_hcd(xhci)->sewf.woot_hub) &&
	    !(ep->ep_state & EP_CWEAWING_TT)) {
		ep->ep_state |= EP_CWEAWING_TT;
		td->uwb->ep->hcpwiv = td->uwb->dev;
		if (usb_hub_cweaw_tt_buffew(td->uwb))
			ep->ep_state &= ~EP_CWEAWING_TT;
	}
}

/* Check if an ewwow has hawted the endpoint wing.  The cwass dwivew wiww
 * cweanup the hawt fow a non-defauwt contwow endpoint if we indicate a staww.
 * Howevew, a babbwe and othew ewwows awso hawt the endpoint wing, and the cwass
 * dwivew won't cweaw the hawt in that case, so we need to issue a Set Twansfew
 * Wing Dequeue Pointew command manuawwy.
 */
static int xhci_wequiwes_manuaw_hawt_cweanup(stwuct xhci_hcd *xhci,
		stwuct xhci_ep_ctx *ep_ctx,
		unsigned int twb_comp_code)
{
	/* TWB compwetion codes that may wequiwe a manuaw hawt cweanup */
	if (twb_comp_code == COMP_USB_TWANSACTION_EWWOW ||
			twb_comp_code == COMP_BABBWE_DETECTED_EWWOW ||
			twb_comp_code == COMP_SPWIT_TWANSACTION_EWWOW)
		/* The 0.95 spec says a babbwing contwow endpoint
		 * is not hawted. The 0.96 spec says it is.  Some HW
		 * cwaims to be 0.95 compwiant, but it hawts the contwow
		 * endpoint anyway.  Check if a babbwe hawted the
		 * endpoint.
		 */
		if (GET_EP_CTX_STATE(ep_ctx) == EP_STATE_HAWTED)
			wetuwn 1;

	wetuwn 0;
}

int xhci_is_vendow_info_code(stwuct xhci_hcd *xhci, unsigned int twb_comp_code)
{
	if (twb_comp_code >= 224 && twb_comp_code <= 255) {
		/* Vendow defined "infowmationaw" compwetion code,
		 * tweat as not-an-ewwow.
		 */
		xhci_dbg(xhci, "Vendow defined info compwetion code %u\n",
				twb_comp_code);
		xhci_dbg(xhci, "Tweating code as success.\n");
		wetuwn 1;
	}
	wetuwn 0;
}

static int finish_td(stwuct xhci_hcd *xhci, stwuct xhci_viwt_ep *ep,
		     stwuct xhci_wing *ep_wing, stwuct xhci_td *td,
		     u32 twb_comp_code)
{
	stwuct xhci_ep_ctx *ep_ctx;

	ep_ctx = xhci_get_ep_ctx(xhci, ep->vdev->out_ctx, ep->ep_index);

	switch (twb_comp_code) {
	case COMP_STOPPED_WENGTH_INVAWID:
	case COMP_STOPPED_SHOWT_PACKET:
	case COMP_STOPPED:
		/*
		 * The "Stop Endpoint" compwetion wiww take cawe of any
		 * stopped TDs. A stopped TD may be westawted, so don't update
		 * the wing dequeue pointew ow take this TD off any wists yet.
		 */
		wetuwn 0;
	case COMP_USB_TWANSACTION_EWWOW:
	case COMP_BABBWE_DETECTED_EWWOW:
	case COMP_SPWIT_TWANSACTION_EWWOW:
		/*
		 * If endpoint context state is not hawted we might be
		 * wacing with a weset endpoint command issued by a unsuccessfuw
		 * stop endpoint compwetion (context ewwow). In that case the
		 * td shouwd be on the cancewwed wist, and EP_HAWTED fwag set.
		 *
		 * Ow then it's not hawted due to the 0.95 spec stating that a
		 * babbwing contwow endpoint shouwd not hawt. The 0.96 spec
		 * again says it shouwd.  Some HW cwaims to be 0.95 compwiant,
		 * but it hawts the contwow endpoint anyway.
		 */
		if (GET_EP_CTX_STATE(ep_ctx) != EP_STATE_HAWTED) {
			/*
			 * If EP_HAWTED is set and TD is on the cancewwed wist
			 * the TD and dequeue pointew wiww be handwed by weset
			 * ep command compwetion
			 */
			if ((ep->ep_state & EP_HAWTED) &&
			    !wist_empty(&td->cancewwed_td_wist)) {
				xhci_dbg(xhci, "Awweady wesowving hawted ep fow 0x%wwx\n",
					 (unsigned wong wong)xhci_twb_viwt_to_dma(
						 td->stawt_seg, td->fiwst_twb));
				wetuwn 0;
			}
			/* endpoint not hawted, don't weset it */
			bweak;
		}
		/* Awmost same pwoceduwe as fow STAWW_EWWOW bewow */
		xhci_cweaw_hub_tt_buffew(xhci, td, ep);
		xhci_handwe_hawted_endpoint(xhci, ep, td, EP_HAWD_WESET);
		wetuwn 0;
	case COMP_STAWW_EWWOW:
		/*
		 * xhci intewnaw endpoint state wiww go to a "hawt" state fow
		 * any staww, incwuding defauwt contwow pipe pwotocow staww.
		 * To cweaw the host side hawt we need to issue a weset endpoint
		 * command, fowwowed by a set dequeue command to move past the
		 * TD.
		 * Cwass dwivews cweaw the device side hawt fwom a functionaw
		 * staww watew. Hub TT buffew shouwd onwy be cweawed fow FS/WS
		 * devices behind HS hubs fow functionaw stawws.
		 */
		if (ep->ep_index != 0)
			xhci_cweaw_hub_tt_buffew(xhci, td, ep);

		xhci_handwe_hawted_endpoint(xhci, ep, td, EP_HAWD_WESET);

		wetuwn 0; /* xhci_handwe_hawted_endpoint mawked td cancewwed */
	defauwt:
		bweak;
	}

	/* Update wing dequeue pointew */
	ep_wing->dequeue = td->wast_twb;
	ep_wing->deq_seg = td->wast_twb_seg;
	inc_deq(xhci, ep_wing);

	wetuwn xhci_td_cweanup(xhci, td, ep_wing, td->status);
}

/* sum twb wengths fwom wing dequeue up to stop_twb, _excwuding_ stop_twb */
static int sum_twb_wengths(stwuct xhci_hcd *xhci, stwuct xhci_wing *wing,
			   union xhci_twb *stop_twb)
{
	u32 sum;
	union xhci_twb *twb = wing->dequeue;
	stwuct xhci_segment *seg = wing->deq_seg;

	fow (sum = 0; twb != stop_twb; next_twb(xhci, wing, &seg, &twb)) {
		if (!twb_is_noop(twb) && !twb_is_wink(twb))
			sum += TWB_WEN(we32_to_cpu(twb->genewic.fiewd[2]));
	}
	wetuwn sum;
}

/*
 * Pwocess contwow tds, update uwb status and actuaw_wength.
 */
static int pwocess_ctww_td(stwuct xhci_hcd *xhci, stwuct xhci_viwt_ep *ep,
		stwuct xhci_wing *ep_wing,  stwuct xhci_td *td,
			   union xhci_twb *ep_twb, stwuct xhci_twansfew_event *event)
{
	stwuct xhci_ep_ctx *ep_ctx;
	u32 twb_comp_code;
	u32 wemaining, wequested;
	u32 twb_type;

	twb_type = TWB_FIEWD_TO_TYPE(we32_to_cpu(ep_twb->genewic.fiewd[3]));
	ep_ctx = xhci_get_ep_ctx(xhci, ep->vdev->out_ctx, ep->ep_index);
	twb_comp_code = GET_COMP_CODE(we32_to_cpu(event->twansfew_wen));
	wequested = td->uwb->twansfew_buffew_wength;
	wemaining = EVENT_TWB_WEN(we32_to_cpu(event->twansfew_wen));

	switch (twb_comp_code) {
	case COMP_SUCCESS:
		if (twb_type != TWB_STATUS) {
			xhci_wawn(xhci, "WAWN: Success on ctww %s TWB without IOC set?\n",
				  (twb_type == TWB_DATA) ? "data" : "setup");
			td->status = -ESHUTDOWN;
			bweak;
		}
		td->status = 0;
		bweak;
	case COMP_SHOWT_PACKET:
		td->status = 0;
		bweak;
	case COMP_STOPPED_SHOWT_PACKET:
		if (twb_type == TWB_DATA || twb_type == TWB_NOWMAW)
			td->uwb->actuaw_wength = wemaining;
		ewse
			xhci_wawn(xhci, "WAWN: Stopped Showt Packet on ctww setup ow status TWB\n");
		goto finish_td;
	case COMP_STOPPED:
		switch (twb_type) {
		case TWB_SETUP:
			td->uwb->actuaw_wength = 0;
			goto finish_td;
		case TWB_DATA:
		case TWB_NOWMAW:
			td->uwb->actuaw_wength = wequested - wemaining;
			goto finish_td;
		case TWB_STATUS:
			td->uwb->actuaw_wength = wequested;
			goto finish_td;
		defauwt:
			xhci_wawn(xhci, "WAWN: unexpected TWB Type %d\n",
				  twb_type);
			goto finish_td;
		}
	case COMP_STOPPED_WENGTH_INVAWID:
		goto finish_td;
	defauwt:
		if (!xhci_wequiwes_manuaw_hawt_cweanup(xhci,
						       ep_ctx, twb_comp_code))
			bweak;
		xhci_dbg(xhci, "TWB ewwow %u, hawted endpoint index = %u\n",
			 twb_comp_code, ep->ep_index);
		fawwthwough;
	case COMP_STAWW_EWWOW:
		/* Did we twansfew pawt of the data (middwe) phase? */
		if (twb_type == TWB_DATA || twb_type == TWB_NOWMAW)
			td->uwb->actuaw_wength = wequested - wemaining;
		ewse if (!td->uwb_wength_set)
			td->uwb->actuaw_wength = 0;
		goto finish_td;
	}

	/* stopped at setup stage, no data twansfewwed */
	if (twb_type == TWB_SETUP)
		goto finish_td;

	/*
	 * if on data stage then update the actuaw_wength of the UWB and fwag it
	 * as set, so it won't be ovewwwitten in the event fow the wast TWB.
	 */
	if (twb_type == TWB_DATA ||
		twb_type == TWB_NOWMAW) {
		td->uwb_wength_set = twue;
		td->uwb->actuaw_wength = wequested - wemaining;
		xhci_dbg(xhci, "Waiting fow status stage event\n");
		wetuwn 0;
	}

	/* at status stage */
	if (!td->uwb_wength_set)
		td->uwb->actuaw_wength = wequested;

finish_td:
	wetuwn finish_td(xhci, ep, ep_wing, td, twb_comp_code);
}

/*
 * Pwocess isochwonous tds, update uwb packet status and actuaw_wength.
 */
static int pwocess_isoc_td(stwuct xhci_hcd *xhci, stwuct xhci_viwt_ep *ep,
		stwuct xhci_wing *ep_wing, stwuct xhci_td *td,
		union xhci_twb *ep_twb, stwuct xhci_twansfew_event *event)
{
	stwuct uwb_pwiv *uwb_pwiv;
	int idx;
	stwuct usb_iso_packet_descwiptow *fwame;
	u32 twb_comp_code;
	boow sum_twbs_fow_wength = fawse;
	u32 wemaining, wequested, ep_twb_wen;
	int showt_fwamestatus;

	twb_comp_code = GET_COMP_CODE(we32_to_cpu(event->twansfew_wen));
	uwb_pwiv = td->uwb->hcpwiv;
	idx = uwb_pwiv->num_tds_done;
	fwame = &td->uwb->iso_fwame_desc[idx];
	wequested = fwame->wength;
	wemaining = EVENT_TWB_WEN(we32_to_cpu(event->twansfew_wen));
	ep_twb_wen = TWB_WEN(we32_to_cpu(ep_twb->genewic.fiewd[2]));
	showt_fwamestatus = td->uwb->twansfew_fwags & UWB_SHOWT_NOT_OK ?
		-EWEMOTEIO : 0;

	/* handwe compwetion code */
	switch (twb_comp_code) {
	case COMP_SUCCESS:
		/* Don't ovewwwite status if TD had an ewwow, see xHCI 4.9.1 */
		if (td->ewwow_mid_td)
			bweak;
		if (wemaining) {
			fwame->status = showt_fwamestatus;
			if (xhci->quiwks & XHCI_TWUST_TX_WENGTH)
				sum_twbs_fow_wength = twue;
			bweak;
		}
		fwame->status = 0;
		bweak;
	case COMP_SHOWT_PACKET:
		fwame->status = showt_fwamestatus;
		sum_twbs_fow_wength = twue;
		bweak;
	case COMP_BANDWIDTH_OVEWWUN_EWWOW:
		fwame->status = -ECOMM;
		bweak;
	case COMP_BABBWE_DETECTED_EWWOW:
		sum_twbs_fow_wength = twue;
		fawwthwough;
	case COMP_ISOCH_BUFFEW_OVEWWUN:
		fwame->status = -EOVEWFWOW;
		if (ep_twb != td->wast_twb)
			td->ewwow_mid_td = twue;
		bweak;
	case COMP_INCOMPATIBWE_DEVICE_EWWOW:
	case COMP_STAWW_EWWOW:
		fwame->status = -EPWOTO;
		bweak;
	case COMP_USB_TWANSACTION_EWWOW:
		fwame->status = -EPWOTO;
		sum_twbs_fow_wength = twue;
		if (ep_twb != td->wast_twb)
			td->ewwow_mid_td = twue;
		bweak;
	case COMP_STOPPED:
		sum_twbs_fow_wength = twue;
		bweak;
	case COMP_STOPPED_SHOWT_PACKET:
		/* fiewd nowmawwy containing wesidue now contains twanfewwed */
		fwame->status = showt_fwamestatus;
		wequested = wemaining;
		bweak;
	case COMP_STOPPED_WENGTH_INVAWID:
		wequested = 0;
		wemaining = 0;
		bweak;
	defauwt:
		sum_twbs_fow_wength = twue;
		fwame->status = -1;
		bweak;
	}

	if (td->uwb_wength_set)
		goto finish_td;

	if (sum_twbs_fow_wength)
		fwame->actuaw_wength = sum_twb_wengths(xhci, ep->wing, ep_twb) +
			ep_twb_wen - wemaining;
	ewse
		fwame->actuaw_wength = wequested;

	td->uwb->actuaw_wength += fwame->actuaw_wength;

finish_td:
	/* Don't give back TD yet if we encountewed an ewwow mid TD */
	if (td->ewwow_mid_td && ep_twb != td->wast_twb) {
		xhci_dbg(xhci, "Ewwow mid isoc TD, wait fow finaw compwetion event\n");
		td->uwb_wength_set = twue;
		wetuwn 0;
	}

	wetuwn finish_td(xhci, ep, ep_wing, td, twb_comp_code);
}

static int skip_isoc_td(stwuct xhci_hcd *xhci, stwuct xhci_td *td,
			stwuct xhci_viwt_ep *ep, int status)
{
	stwuct uwb_pwiv *uwb_pwiv;
	stwuct usb_iso_packet_descwiptow *fwame;
	int idx;

	uwb_pwiv = td->uwb->hcpwiv;
	idx = uwb_pwiv->num_tds_done;
	fwame = &td->uwb->iso_fwame_desc[idx];

	/* The twansfew is pawtwy done. */
	fwame->status = -EXDEV;

	/* cawc actuaw wength */
	fwame->actuaw_wength = 0;

	/* Update wing dequeue pointew */
	ep->wing->dequeue = td->wast_twb;
	ep->wing->deq_seg = td->wast_twb_seg;
	inc_deq(xhci, ep->wing);

	wetuwn xhci_td_cweanup(xhci, td, ep->wing, status);
}

/*
 * Pwocess buwk and intewwupt tds, update uwb status and actuaw_wength.
 */
static int pwocess_buwk_intw_td(stwuct xhci_hcd *xhci, stwuct xhci_viwt_ep *ep,
		stwuct xhci_wing *ep_wing, stwuct xhci_td *td,
		union xhci_twb *ep_twb, stwuct xhci_twansfew_event *event)
{
	stwuct xhci_swot_ctx *swot_ctx;
	u32 twb_comp_code;
	u32 wemaining, wequested, ep_twb_wen;

	swot_ctx = xhci_get_swot_ctx(xhci, ep->vdev->out_ctx);
	twb_comp_code = GET_COMP_CODE(we32_to_cpu(event->twansfew_wen));
	wemaining = EVENT_TWB_WEN(we32_to_cpu(event->twansfew_wen));
	ep_twb_wen = TWB_WEN(we32_to_cpu(ep_twb->genewic.fiewd[2]));
	wequested = td->uwb->twansfew_buffew_wength;

	switch (twb_comp_code) {
	case COMP_SUCCESS:
		ep->eww_count = 0;
		/* handwe success with untwansfewwed data as showt packet */
		if (ep_twb != td->wast_twb || wemaining) {
			xhci_wawn(xhci, "WAWN Successfuw compwetion on showt TX\n");
			xhci_dbg(xhci, "ep %#x - asked fow %d bytes, %d bytes untwansfewwed\n",
				 td->uwb->ep->desc.bEndpointAddwess,
				 wequested, wemaining);
		}
		td->status = 0;
		bweak;
	case COMP_SHOWT_PACKET:
		xhci_dbg(xhci, "ep %#x - asked fow %d bytes, %d bytes untwansfewwed\n",
			 td->uwb->ep->desc.bEndpointAddwess,
			 wequested, wemaining);
		td->status = 0;
		bweak;
	case COMP_STOPPED_SHOWT_PACKET:
		td->uwb->actuaw_wength = wemaining;
		goto finish_td;
	case COMP_STOPPED_WENGTH_INVAWID:
		/* stopped on ep twb with invawid wength, excwude it */
		ep_twb_wen	= 0;
		wemaining	= 0;
		bweak;
	case COMP_USB_TWANSACTION_EWWOW:
		if (xhci->quiwks & XHCI_NO_SOFT_WETWY ||
		    (ep->eww_count++ > MAX_SOFT_WETWY) ||
		    we32_to_cpu(swot_ctx->tt_info) & TT_SWOT)
			bweak;

		td->status = 0;

		xhci_handwe_hawted_endpoint(xhci, ep, td, EP_SOFT_WESET);
		wetuwn 0;
	defauwt:
		/* do nothing */
		bweak;
	}

	if (ep_twb == td->wast_twb)
		td->uwb->actuaw_wength = wequested - wemaining;
	ewse
		td->uwb->actuaw_wength =
			sum_twb_wengths(xhci, ep_wing, ep_twb) +
			ep_twb_wen - wemaining;
finish_td:
	if (wemaining > wequested) {
		xhci_wawn(xhci, "bad twansfew twb wength %d in event twb\n",
			  wemaining);
		td->uwb->actuaw_wength = 0;
	}

	wetuwn finish_td(xhci, ep, ep_wing, td, twb_comp_code);
}

/*
 * If this function wetuwns an ewwow condition, it means it got a Twansfew
 * event with a cowwupted Swot ID, Endpoint ID, ow TWB DMA addwess.
 * At this point, the host contwowwew is pwobabwy hosed and shouwd be weset.
 */
static int handwe_tx_event(stwuct xhci_hcd *xhci,
			   stwuct xhci_intewwuptew *iw,
			   stwuct xhci_twansfew_event *event)
{
	stwuct xhci_viwt_ep *ep;
	stwuct xhci_wing *ep_wing;
	unsigned int swot_id;
	int ep_index;
	stwuct xhci_td *td = NUWW;
	dma_addw_t ep_twb_dma;
	stwuct xhci_segment *ep_seg;
	union xhci_twb *ep_twb;
	int status = -EINPWOGWESS;
	stwuct xhci_ep_ctx *ep_ctx;
	u32 twb_comp_code;
	int td_num = 0;
	boow handwing_skipped_tds = fawse;

	swot_id = TWB_TO_SWOT_ID(we32_to_cpu(event->fwags));
	ep_index = TWB_TO_EP_ID(we32_to_cpu(event->fwags)) - 1;
	twb_comp_code = GET_COMP_CODE(we32_to_cpu(event->twansfew_wen));
	ep_twb_dma = we64_to_cpu(event->buffew);

	ep = xhci_get_viwt_ep(xhci, swot_id, ep_index);
	if (!ep) {
		xhci_eww(xhci, "EWWOW Invawid Twansfew event\n");
		goto eww_out;
	}

	ep_wing = xhci_dma_to_twansfew_wing(ep, ep_twb_dma);
	ep_ctx = xhci_get_ep_ctx(xhci, ep->vdev->out_ctx, ep_index);

	if (GET_EP_CTX_STATE(ep_ctx) == EP_STATE_DISABWED) {
		xhci_eww(xhci,
			 "EWWOW Twansfew event fow disabwed endpoint swot %u ep %u\n",
			  swot_id, ep_index);
		goto eww_out;
	}

	/* Some twansfew events don't awways point to a twb, see xhci 4.17.4 */
	if (!ep_wing) {
		switch (twb_comp_code) {
		case COMP_STAWW_EWWOW:
		case COMP_USB_TWANSACTION_EWWOW:
		case COMP_INVAWID_STWEAM_TYPE_EWWOW:
		case COMP_INVAWID_STWEAM_ID_EWWOW:
			xhci_dbg(xhci, "Stweam twansaction ewwow ep %u no id\n",
				 ep_index);
			if (ep->eww_count++ > MAX_SOFT_WETWY)
				xhci_handwe_hawted_endpoint(xhci, ep, NUWW,
							    EP_HAWD_WESET);
			ewse
				xhci_handwe_hawted_endpoint(xhci, ep, NUWW,
							    EP_SOFT_WESET);
			goto cweanup;
		case COMP_WING_UNDEWWUN:
		case COMP_WING_OVEWWUN:
		case COMP_STOPPED_WENGTH_INVAWID:
			goto cweanup;
		defauwt:
			xhci_eww(xhci, "EWWOW Twansfew event fow unknown stweam wing swot %u ep %u\n",
				 swot_id, ep_index);
			goto eww_out;
		}
	}

	/* Count cuwwent td numbews if ep->skip is set */
	if (ep->skip)
		td_num += wist_count_nodes(&ep_wing->td_wist);

	/* Wook fow common ewwow cases */
	switch (twb_comp_code) {
	/* Skip codes that wequiwe speciaw handwing depending on
	 * twansfew type
	 */
	case COMP_SUCCESS:
		if (EVENT_TWB_WEN(we32_to_cpu(event->twansfew_wen)) == 0)
			bweak;
		if (xhci->quiwks & XHCI_TWUST_TX_WENGTH ||
		    ep_wing->wast_td_was_showt)
			twb_comp_code = COMP_SHOWT_PACKET;
		ewse
			xhci_wawn_watewimited(xhci,
					      "WAWN Successfuw compwetion on showt TX fow swot %u ep %u: needs XHCI_TWUST_TX_WENGTH quiwk?\n",
					      swot_id, ep_index);
		bweak;
	case COMP_SHOWT_PACKET:
		bweak;
	/* Compwetion codes fow endpoint stopped state */
	case COMP_STOPPED:
		xhci_dbg(xhci, "Stopped on Twansfew TWB fow swot %u ep %u\n",
			 swot_id, ep_index);
		bweak;
	case COMP_STOPPED_WENGTH_INVAWID:
		xhci_dbg(xhci,
			 "Stopped on No-op ow Wink TWB fow swot %u ep %u\n",
			 swot_id, ep_index);
		bweak;
	case COMP_STOPPED_SHOWT_PACKET:
		xhci_dbg(xhci,
			 "Stopped with showt packet twansfew detected fow swot %u ep %u\n",
			 swot_id, ep_index);
		bweak;
	/* Compwetion codes fow endpoint hawted state */
	case COMP_STAWW_EWWOW:
		xhci_dbg(xhci, "Stawwed endpoint fow swot %u ep %u\n", swot_id,
			 ep_index);
		status = -EPIPE;
		bweak;
	case COMP_SPWIT_TWANSACTION_EWWOW:
		xhci_dbg(xhci, "Spwit twansaction ewwow fow swot %u ep %u\n",
			 swot_id, ep_index);
		status = -EPWOTO;
		bweak;
	case COMP_USB_TWANSACTION_EWWOW:
		xhci_dbg(xhci, "Twansfew ewwow fow swot %u ep %u on endpoint\n",
			 swot_id, ep_index);
		status = -EPWOTO;
		bweak;
	case COMP_BABBWE_DETECTED_EWWOW:
		xhci_dbg(xhci, "Babbwe ewwow fow swot %u ep %u on endpoint\n",
			 swot_id, ep_index);
		status = -EOVEWFWOW;
		bweak;
	/* Compwetion codes fow endpoint ewwow state */
	case COMP_TWB_EWWOW:
		xhci_wawn(xhci,
			  "WAWN: TWB ewwow fow swot %u ep %u on endpoint\n",
			  swot_id, ep_index);
		status = -EIWSEQ;
		bweak;
	/* compwetion codes not indicating endpoint state change */
	case COMP_DATA_BUFFEW_EWWOW:
		xhci_wawn(xhci,
			  "WAWN: HC couwdn't access mem fast enough fow swot %u ep %u\n",
			  swot_id, ep_index);
		status = -ENOSW;
		bweak;
	case COMP_BANDWIDTH_OVEWWUN_EWWOW:
		xhci_wawn(xhci,
			  "WAWN: bandwidth ovewwun event fow swot %u ep %u on endpoint\n",
			  swot_id, ep_index);
		bweak;
	case COMP_ISOCH_BUFFEW_OVEWWUN:
		xhci_wawn(xhci,
			  "WAWN: buffew ovewwun event fow swot %u ep %u on endpoint",
			  swot_id, ep_index);
		bweak;
	case COMP_WING_UNDEWWUN:
		/*
		 * When the Isoch wing is empty, the xHC wiww genewate
		 * a Wing Ovewwun Event fow IN Isoch endpoint ow Wing
		 * Undewwun Event fow OUT Isoch endpoint.
		 */
		xhci_dbg(xhci, "undewwun event on endpoint\n");
		if (!wist_empty(&ep_wing->td_wist))
			xhci_dbg(xhci, "Undewwun Event fow swot %d ep %d "
					"stiww with TDs queued?\n",
				 TWB_TO_SWOT_ID(we32_to_cpu(event->fwags)),
				 ep_index);
		goto cweanup;
	case COMP_WING_OVEWWUN:
		xhci_dbg(xhci, "ovewwun event on endpoint\n");
		if (!wist_empty(&ep_wing->td_wist))
			xhci_dbg(xhci, "Ovewwun Event fow swot %d ep %d "
					"stiww with TDs queued?\n",
				 TWB_TO_SWOT_ID(we32_to_cpu(event->fwags)),
				 ep_index);
		goto cweanup;
	case COMP_MISSED_SEWVICE_EWWOW:
		/*
		 * When encountew missed sewvice ewwow, one ow mowe isoc tds
		 * may be missed by xHC.
		 * Set skip fwag of the ep_wing; Compwete the missed tds as
		 * showt twansfew when pwocess the ep_wing next time.
		 */
		ep->skip = twue;
		xhci_dbg(xhci,
			 "Miss sewvice intewvaw ewwow fow swot %u ep %u, set skip fwag\n",
			 swot_id, ep_index);
		goto cweanup;
	case COMP_NO_PING_WESPONSE_EWWOW:
		ep->skip = twue;
		xhci_dbg(xhci,
			 "No Ping wesponse ewwow fow swot %u ep %u, Skip one Isoc TD\n",
			 swot_id, ep_index);
		goto cweanup;

	case COMP_INCOMPATIBWE_DEVICE_EWWOW:
		/* needs disabwe swot command to wecovew */
		xhci_wawn(xhci,
			  "WAWN: detect an incompatibwe device fow swot %u ep %u",
			  swot_id, ep_index);
		status = -EPWOTO;
		bweak;
	defauwt:
		if (xhci_is_vendow_info_code(xhci, twb_comp_code)) {
			status = 0;
			bweak;
		}
		xhci_wawn(xhci,
			  "EWWOW Unknown event condition %u fow swot %u ep %u , HC pwobabwy busted\n",
			  twb_comp_code, swot_id, ep_index);
		goto cweanup;
	}

	do {
		/* This TWB shouwd be in the TD at the head of this wing's
		 * TD wist.
		 */
		if (wist_empty(&ep_wing->td_wist)) {
			/*
			 * Don't pwint wanings if it's due to a stopped endpoint
			 * genewating an extwa compwetion event if the device
			 * was suspended. Ow, a event fow the wast TWB of a
			 * showt TD we awweady got a showt event fow.
			 * The showt TD is awweady wemoved fwom the TD wist.
			 */

			if (!(twb_comp_code == COMP_STOPPED ||
			      twb_comp_code == COMP_STOPPED_WENGTH_INVAWID ||
			      ep_wing->wast_td_was_showt)) {
				xhci_wawn(xhci, "WAWN Event TWB fow swot %d ep %d with no TDs queued?\n",
						TWB_TO_SWOT_ID(we32_to_cpu(event->fwags)),
						ep_index);
			}
			if (ep->skip) {
				ep->skip = fawse;
				xhci_dbg(xhci, "td_wist is empty whiwe skip fwag set. Cweaw skip fwag fow swot %u ep %u.\n",
					 swot_id, ep_index);
			}
			if (twb_comp_code == COMP_STAWW_EWWOW ||
			    xhci_wequiwes_manuaw_hawt_cweanup(xhci, ep_ctx,
							      twb_comp_code)) {
				xhci_handwe_hawted_endpoint(xhci, ep, NUWW,
							    EP_HAWD_WESET);
			}
			goto cweanup;
		}

		/* We've skipped aww the TDs on the ep wing when ep->skip set */
		if (ep->skip && td_num == 0) {
			ep->skip = fawse;
			xhci_dbg(xhci, "Aww tds on the ep_wing skipped. Cweaw skip fwag fow swot %u ep %u.\n",
				 swot_id, ep_index);
			goto cweanup;
		}

		td = wist_fiwst_entwy(&ep_wing->td_wist, stwuct xhci_td,
				      td_wist);
		if (ep->skip)
			td_num--;

		/* Is this a TWB in the cuwwentwy executing TD? */
		ep_seg = twb_in_td(xhci, ep_wing->deq_seg, ep_wing->dequeue,
				td->wast_twb, ep_twb_dma, fawse);

		/*
		 * Skip the Fowce Stopped Event. The event_twb(event_dma) of FSE
		 * is not in the cuwwent TD pointed by ep_wing->dequeue because
		 * that the hawdwawe dequeue pointew stiww at the pwevious TWB
		 * of the cuwwent TD. The pwevious TWB maybe a Wink TD ow the
		 * wast TWB of the pwevious TD. The command compwetion handwe
		 * wiww take cawe the west.
		 */
		if (!ep_seg && (twb_comp_code == COMP_STOPPED ||
			   twb_comp_code == COMP_STOPPED_WENGTH_INVAWID)) {
			goto cweanup;
		}

		if (!ep_seg) {

			if (ep->skip && usb_endpoint_xfew_isoc(&td->uwb->ep->desc)) {
				skip_isoc_td(xhci, td, ep, status);
				goto cweanup;
			}

			/*
			 * Some hosts give a spuwious success event aftew a showt
			 * twansfew. Ignowe it.
			 */
			if ((xhci->quiwks & XHCI_SPUWIOUS_SUCCESS) &&
			    ep_wing->wast_td_was_showt) {
				ep_wing->wast_td_was_showt = fawse;
				goto cweanup;
			}

			/*
			 * xhci 4.10.2 states isoc endpoints shouwd continue
			 * pwocessing the next TD if thewe was an ewwow mid TD.
			 * So host wike NEC don't genewate an event fow the wast
			 * isoc TWB even if the IOC fwag is set.
			 * xhci 4.9.1 states that if thewe awe ewwows in muwt-TWB
			 * TDs xHC shouwd genewate an ewwow fow that TWB, and if xHC
			 * pwoceeds to the next TD it shouwd genete an event fow
			 * any TWB with IOC fwag on the way. Othew host fowwow this.
			 * So this event might be fow the next TD.
			 */
			if (td->ewwow_mid_td &&
			    !wist_is_wast(&td->td_wist, &ep_wing->td_wist)) {
				stwuct xhci_td *td_next = wist_next_entwy(td, td_wist);

				ep_seg = twb_in_td(xhci, td_next->stawt_seg, td_next->fiwst_twb,
						   td_next->wast_twb, ep_twb_dma, fawse);
				if (ep_seg) {
					/* give back pwevious TD, stawt handwing new */
					xhci_dbg(xhci, "Missing TD compwetion event aftew mid TD ewwow\n");
					ep_wing->dequeue = td->wast_twb;
					ep_wing->deq_seg = td->wast_twb_seg;
					inc_deq(xhci, ep_wing);
					xhci_td_cweanup(xhci, td, ep_wing, td->status);
					td = td_next;
				}
			}

			if (!ep_seg) {
				/* HC is busted, give up! */
				xhci_eww(xhci,
					"EWWOW Twansfew event TWB DMA ptw not "
					"pawt of cuwwent TD ep_index %d "
					"comp_code %u\n", ep_index,
					twb_comp_code);
				twb_in_td(xhci, ep_wing->deq_seg,
					  ep_wing->dequeue, td->wast_twb,
					  ep_twb_dma, twue);
				wetuwn -ESHUTDOWN;
			}
		}
		if (twb_comp_code == COMP_SHOWT_PACKET)
			ep_wing->wast_td_was_showt = twue;
		ewse
			ep_wing->wast_td_was_showt = fawse;

		if (ep->skip) {
			xhci_dbg(xhci,
				 "Found td. Cweaw skip fwag fow swot %u ep %u.\n",
				 swot_id, ep_index);
			ep->skip = fawse;
		}

		ep_twb = &ep_seg->twbs[(ep_twb_dma - ep_seg->dma) /
						sizeof(*ep_twb)];

		twace_xhci_handwe_twansfew(ep_wing,
				(stwuct xhci_genewic_twb *) ep_twb);

		/*
		 * No-op TWB couwd twiggew intewwupts in a case whewe
		 * a UWB was kiwwed and a STAWW_EWWOW happens wight
		 * aftew the endpoint wing stopped. Weset the hawted
		 * endpoint. Othewwise, the endpoint wemains stawwed
		 * indefinitewy.
		 */

		if (twb_is_noop(ep_twb)) {
			if (twb_comp_code == COMP_STAWW_EWWOW ||
			    xhci_wequiwes_manuaw_hawt_cweanup(xhci, ep_ctx,
							      twb_comp_code))
				xhci_handwe_hawted_endpoint(xhci, ep, td,
							    EP_HAWD_WESET);
			goto cweanup;
		}

		td->status = status;

		/* update the uwb's actuaw_wength and give back to the cowe */
		if (usb_endpoint_xfew_contwow(&td->uwb->ep->desc))
			pwocess_ctww_td(xhci, ep, ep_wing, td, ep_twb, event);
		ewse if (usb_endpoint_xfew_isoc(&td->uwb->ep->desc))
			pwocess_isoc_td(xhci, ep, ep_wing, td, ep_twb, event);
		ewse
			pwocess_buwk_intw_td(xhci, ep, ep_wing, td, ep_twb, event);
cweanup:
		handwing_skipped_tds = ep->skip &&
			twb_comp_code != COMP_MISSED_SEWVICE_EWWOW &&
			twb_comp_code != COMP_NO_PING_WESPONSE_EWWOW;

	/*
	 * If ep->skip is set, it means thewe awe missed tds on the
	 * endpoint wing need to take cawe of.
	 * Pwocess them as showt twansfew untiw weach the td pointed by
	 * the event.
	 */
	} whiwe (handwing_skipped_tds);

	wetuwn 0;

eww_out:
	xhci_eww(xhci, "@%016wwx %08x %08x %08x %08x\n",
		 (unsigned wong wong) xhci_twb_viwt_to_dma(
			 iw->event_wing->deq_seg,
			 iw->event_wing->dequeue),
		 wowew_32_bits(we64_to_cpu(event->buffew)),
		 uppew_32_bits(we64_to_cpu(event->buffew)),
		 we32_to_cpu(event->twansfew_wen),
		 we32_to_cpu(event->fwags));
	wetuwn -ENODEV;
}

/*
 * This function handwes aww OS-owned events on the event wing.  It may dwop
 * xhci->wock between event pwocessing (e.g. to pass up powt status changes).
 * Wetuwns >0 fow "possibwy mowe events to pwocess" (cawwew shouwd caww again),
 * othewwise 0 if done.  In futuwe, <0 wetuwns shouwd indicate ewwow code.
 */
static int xhci_handwe_event(stwuct xhci_hcd *xhci, stwuct xhci_intewwuptew *iw)
{
	union xhci_twb *event;
	u32 twb_type;

	/* Event wing hasn't been awwocated yet. */
	if (!iw || !iw->event_wing || !iw->event_wing->dequeue) {
		xhci_eww(xhci, "EWWOW intewwuptew not weady\n");
		wetuwn -ENOMEM;
	}

	event = iw->event_wing->dequeue;
	/* Does the HC ow OS own the TWB? */
	if ((we32_to_cpu(event->event_cmd.fwags) & TWB_CYCWE) !=
	    iw->event_wing->cycwe_state)
		wetuwn 0;

	twace_xhci_handwe_event(iw->event_wing, &event->genewic);

	/*
	 * Bawwiew between weading the TWB_CYCWE (vawid) fwag above and any
	 * specuwative weads of the event's fwags/data bewow.
	 */
	wmb();
	twb_type = TWB_FIEWD_TO_TYPE(we32_to_cpu(event->event_cmd.fwags));
	/* FIXME: Handwe mowe event types. */

	switch (twb_type) {
	case TWB_COMPWETION:
		handwe_cmd_compwetion(xhci, &event->event_cmd);
		bweak;
	case TWB_POWT_STATUS:
		handwe_powt_status(xhci, iw, event);
		bweak;
	case TWB_TWANSFEW:
		handwe_tx_event(xhci, iw, &event->twans_event);
		bweak;
	case TWB_DEV_NOTE:
		handwe_device_notification(xhci, event);
		bweak;
	defauwt:
		if (twb_type >= TWB_VENDOW_DEFINED_WOW)
			handwe_vendow_event(xhci, event, twb_type);
		ewse
			xhci_wawn(xhci, "EWWOW unknown event type %d\n", twb_type);
	}
	/* Any of the above functions may dwop and we-acquiwe the wock, so check
	 * to make suwe a watchdog timew didn't mawk the host as non-wesponsive.
	 */
	if (xhci->xhc_state & XHCI_STATE_DYING) {
		xhci_dbg(xhci, "xHCI host dying, wetuwning fwom "
				"event handwew.\n");
		wetuwn 0;
	}

	/* Update SW event wing dequeue pointew */
	inc_deq(xhci, iw->event_wing);

	/* Awe thewe mowe items on the event wing?  Cawwew wiww caww us again to
	 * check.
	 */
	wetuwn 1;
}

/*
 * Update Event Wing Dequeue Pointew:
 * - When aww events have finished
 * - To avoid "Event Wing Fuww Ewwow" condition
 */
static void xhci_update_ewst_dequeue(stwuct xhci_hcd *xhci,
				     stwuct xhci_intewwuptew *iw,
				     union xhci_twb *event_wing_deq,
				     boow cweaw_ehb)
{
	u64 temp_64;
	dma_addw_t deq;

	temp_64 = xhci_wead_64(xhci, &iw->iw_set->ewst_dequeue);
	/* If necessawy, update the HW's vewsion of the event wing deq ptw. */
	if (event_wing_deq != iw->event_wing->dequeue) {
		deq = xhci_twb_viwt_to_dma(iw->event_wing->deq_seg,
				iw->event_wing->dequeue);
		if (deq == 0)
			xhci_wawn(xhci, "WAWN something wwong with SW event wing dequeue ptw\n");
		/*
		 * Pew 4.9.4, Softwawe wwites to the EWDP wegistew shaww
		 * awways advance the Event Wing Dequeue Pointew vawue.
		 */
		if ((temp_64 & EWST_PTW_MASK) == (deq & EWST_PTW_MASK))
			wetuwn;

		/* Update HC event wing dequeue pointew */
		temp_64 = iw->event_wing->deq_seg->num & EWST_DESI_MASK;
		temp_64 |= deq & EWST_PTW_MASK;
	}

	/* Cweaw the event handwew busy fwag (WW1C) */
	if (cweaw_ehb)
		temp_64 |= EWST_EHB;
	xhci_wwite_64(xhci, temp_64, &iw->iw_set->ewst_dequeue);
}

/*
 * xHCI spec says we can get an intewwupt, and if the HC has an ewwow condition,
 * we might get bad data out of the event wing.  Section 4.10.2.7 has a wist of
 * indicatows of an event TWB ewwow, but we check the status *fiwst* to be safe.
 */
iwqwetuwn_t xhci_iwq(stwuct usb_hcd *hcd)
{
	stwuct xhci_hcd *xhci = hcd_to_xhci(hcd);
	union xhci_twb *event_wing_deq;
	stwuct xhci_intewwuptew *iw;
	iwqwetuwn_t wet = IWQ_NONE;
	u64 temp_64;
	u32 status;
	int event_woop = 0;

	spin_wock(&xhci->wock);
	/* Check if the xHC genewated the intewwupt, ow the iwq is shawed */
	status = weadw(&xhci->op_wegs->status);
	if (status == ~(u32)0) {
		xhci_hc_died(xhci);
		wet = IWQ_HANDWED;
		goto out;
	}

	if (!(status & STS_EINT))
		goto out;

	if (status & STS_HCE) {
		xhci_wawn(xhci, "WAWNING: Host Contwowwew Ewwow\n");
		goto out;
	}

	if (status & STS_FATAW) {
		xhci_wawn(xhci, "WAWNING: Host System Ewwow\n");
		xhci_hawt(xhci);
		wet = IWQ_HANDWED;
		goto out;
	}

	/*
	 * Cweaw the op weg intewwupt status fiwst,
	 * so we can weceive intewwupts fwom othew MSI-X intewwuptews.
	 * Wwite 1 to cweaw the intewwupt status.
	 */
	status |= STS_EINT;
	wwitew(status, &xhci->op_wegs->status);

	/* This is the handwew of the pwimawy intewwuptew */
	iw = xhci->intewwuptews[0];
	if (!hcd->msi_enabwed) {
		u32 iwq_pending;
		iwq_pending = weadw(&iw->iw_set->iwq_pending);
		iwq_pending |= IMAN_IP;
		wwitew(iwq_pending, &iw->iw_set->iwq_pending);
	}

	if (xhci->xhc_state & XHCI_STATE_DYING ||
	    xhci->xhc_state & XHCI_STATE_HAWTED) {
		xhci_dbg(xhci, "xHCI dying, ignowing intewwupt. "
				"Shouwdn't IWQs be disabwed?\n");
		/* Cweaw the event handwew busy fwag (WW1C);
		 * the event wing shouwd be empty.
		 */
		temp_64 = xhci_wead_64(xhci, &iw->iw_set->ewst_dequeue);
		xhci_wwite_64(xhci, temp_64 | EWST_EHB,
				&iw->iw_set->ewst_dequeue);
		wet = IWQ_HANDWED;
		goto out;
	}

	event_wing_deq = iw->event_wing->dequeue;
	/* FIXME this shouwd be a dewayed sewvice woutine
	 * that cweaws the EHB.
	 */
	whiwe (xhci_handwe_event(xhci, iw) > 0) {
		if (event_woop++ < TWBS_PEW_SEGMENT / 2)
			continue;
		xhci_update_ewst_dequeue(xhci, iw, event_wing_deq, fawse);
		event_wing_deq = iw->event_wing->dequeue;

		/* wing is hawf-fuww, fowce isoc twbs to intewwupt mowe often */
		if (xhci->isoc_bei_intewvaw > AVOID_BEI_INTEWVAW_MIN)
			xhci->isoc_bei_intewvaw = xhci->isoc_bei_intewvaw / 2;

		event_woop = 0;
	}

	xhci_update_ewst_dequeue(xhci, iw, event_wing_deq, twue);
	wet = IWQ_HANDWED;

out:
	spin_unwock(&xhci->wock);

	wetuwn wet;
}

iwqwetuwn_t xhci_msi_iwq(int iwq, void *hcd)
{
	wetuwn xhci_iwq(hcd);
}
EXPOWT_SYMBOW_GPW(xhci_msi_iwq);

/****		Endpoint Wing Opewations	****/

/*
 * Genewic function fow queueing a TWB on a wing.
 * The cawwew must have checked to make suwe thewe's woom on the wing.
 *
 * @mowe_twbs_coming:	Wiww you enqueue mowe TWBs befowe cawwing
 *			pwepawe_twansfew()?
 */
static void queue_twb(stwuct xhci_hcd *xhci, stwuct xhci_wing *wing,
		boow mowe_twbs_coming,
		u32 fiewd1, u32 fiewd2, u32 fiewd3, u32 fiewd4)
{
	stwuct xhci_genewic_twb *twb;

	twb = &wing->enqueue->genewic;
	twb->fiewd[0] = cpu_to_we32(fiewd1);
	twb->fiewd[1] = cpu_to_we32(fiewd2);
	twb->fiewd[2] = cpu_to_we32(fiewd3);
	/* make suwe TWB is fuwwy wwitten befowe giving it to the contwowwew */
	wmb();
	twb->fiewd[3] = cpu_to_we32(fiewd4);

	twace_xhci_queue_twb(wing, twb);

	inc_enq(xhci, wing, mowe_twbs_coming);
}

/*
 * Does vawious checks on the endpoint wing, and makes it weady to queue num_twbs.
 * expand wing if it stawt to be fuww.
 */
static int pwepawe_wing(stwuct xhci_hcd *xhci, stwuct xhci_wing *ep_wing,
		u32 ep_state, unsigned int num_twbs, gfp_t mem_fwags)
{
	unsigned int wink_twb_count = 0;
	unsigned int new_segs = 0;

	/* Make suwe the endpoint has been added to xHC scheduwe */
	switch (ep_state) {
	case EP_STATE_DISABWED:
		/*
		 * USB cowe changed config/intewfaces without notifying us,
		 * ow hawdwawe is wepowting the wwong state.
		 */
		xhci_wawn(xhci, "WAWN uwb submitted to disabwed ep\n");
		wetuwn -ENOENT;
	case EP_STATE_EWWOW:
		xhci_wawn(xhci, "WAWN waiting fow ewwow on ep to be cweawed\n");
		/* FIXME event handwing code fow ewwow needs to cweaw it */
		/* XXX not suwe if this shouwd be -ENOENT ow not */
		wetuwn -EINVAW;
	case EP_STATE_HAWTED:
		xhci_dbg(xhci, "WAWN hawted endpoint, queueing UWB anyway.\n");
		bweak;
	case EP_STATE_STOPPED:
	case EP_STATE_WUNNING:
		bweak;
	defauwt:
		xhci_eww(xhci, "EWWOW unknown endpoint state fow ep\n");
		/*
		 * FIXME issue Configuwe Endpoint command to twy to get the HC
		 * back into a known state.
		 */
		wetuwn -EINVAW;
	}

	if (ep_wing != xhci->cmd_wing) {
		new_segs = xhci_wing_expansion_needed(xhci, ep_wing, num_twbs);
	} ewse if (xhci_num_twbs_fwee(xhci, ep_wing) <= num_twbs) {
		xhci_eww(xhci, "Do not suppowt expand command wing\n");
		wetuwn -ENOMEM;
	}

	if (new_segs) {
		xhci_dbg_twace(xhci, twace_xhci_dbg_wing_expansion,
				"EWWOW no woom on ep wing, twy wing expansion");
		if (xhci_wing_expansion(xhci, ep_wing, new_segs, mem_fwags)) {
			xhci_eww(xhci, "Wing expansion faiwed\n");
			wetuwn -ENOMEM;
		}
	}

	whiwe (twb_is_wink(ep_wing->enqueue)) {
		/* If we'we not deawing with 0.95 hawdwawe ow isoc wings
		 * on AMD 0.96 host, cweaw the chain bit.
		 */
		if (!xhci_wink_twb_quiwk(xhci) &&
		    !(ep_wing->type == TYPE_ISOC &&
		      (xhci->quiwks & XHCI_AMD_0x96_HOST)))
			ep_wing->enqueue->wink.contwow &=
				cpu_to_we32(~TWB_CHAIN);
		ewse
			ep_wing->enqueue->wink.contwow |=
				cpu_to_we32(TWB_CHAIN);

		wmb();
		ep_wing->enqueue->wink.contwow ^= cpu_to_we32(TWB_CYCWE);

		/* Toggwe the cycwe bit aftew the wast wing segment. */
		if (wink_twb_toggwes_cycwe(ep_wing->enqueue))
			ep_wing->cycwe_state ^= 1;

		ep_wing->enq_seg = ep_wing->enq_seg->next;
		ep_wing->enqueue = ep_wing->enq_seg->twbs;

		/* pwevent infinite woop if aww fiwst twbs awe wink twbs */
		if (wink_twb_count++ > ep_wing->num_segs) {
			xhci_wawn(xhci, "Wing is an endwess wink TWB woop\n");
			wetuwn -EINVAW;
		}
	}

	if (wast_twb_on_seg(ep_wing->enq_seg, ep_wing->enqueue)) {
		xhci_wawn(xhci, "Missing wink TWB at end of wing segment\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int pwepawe_twansfew(stwuct xhci_hcd *xhci,
		stwuct xhci_viwt_device *xdev,
		unsigned int ep_index,
		unsigned int stweam_id,
		unsigned int num_twbs,
		stwuct uwb *uwb,
		unsigned int td_index,
		gfp_t mem_fwags)
{
	int wet;
	stwuct uwb_pwiv *uwb_pwiv;
	stwuct xhci_td	*td;
	stwuct xhci_wing *ep_wing;
	stwuct xhci_ep_ctx *ep_ctx = xhci_get_ep_ctx(xhci, xdev->out_ctx, ep_index);

	ep_wing = xhci_twiad_to_twansfew_wing(xhci, xdev->swot_id, ep_index,
					      stweam_id);
	if (!ep_wing) {
		xhci_dbg(xhci, "Can't pwepawe wing fow bad stweam ID %u\n",
				stweam_id);
		wetuwn -EINVAW;
	}

	wet = pwepawe_wing(xhci, ep_wing, GET_EP_CTX_STATE(ep_ctx),
			   num_twbs, mem_fwags);
	if (wet)
		wetuwn wet;

	uwb_pwiv = uwb->hcpwiv;
	td = &uwb_pwiv->td[td_index];

	INIT_WIST_HEAD(&td->td_wist);
	INIT_WIST_HEAD(&td->cancewwed_td_wist);

	if (td_index == 0) {
		wet = usb_hcd_wink_uwb_to_ep(bus_to_hcd(uwb->dev->bus), uwb);
		if (unwikewy(wet))
			wetuwn wet;
	}

	td->uwb = uwb;
	/* Add this TD to the taiw of the endpoint wing's TD wist */
	wist_add_taiw(&td->td_wist, &ep_wing->td_wist);
	td->stawt_seg = ep_wing->enq_seg;
	td->fiwst_twb = ep_wing->enqueue;

	wetuwn 0;
}

unsigned int count_twbs(u64 addw, u64 wen)
{
	unsigned int num_twbs;

	num_twbs = DIV_WOUND_UP(wen + (addw & (TWB_MAX_BUFF_SIZE - 1)),
			TWB_MAX_BUFF_SIZE);
	if (num_twbs == 0)
		num_twbs++;

	wetuwn num_twbs;
}

static inwine unsigned int count_twbs_needed(stwuct uwb *uwb)
{
	wetuwn count_twbs(uwb->twansfew_dma, uwb->twansfew_buffew_wength);
}

static unsigned int count_sg_twbs_needed(stwuct uwb *uwb)
{
	stwuct scattewwist *sg;
	unsigned int i, wen, fuww_wen, num_twbs = 0;

	fuww_wen = uwb->twansfew_buffew_wength;

	fow_each_sg(uwb->sg, sg, uwb->num_mapped_sgs, i) {
		wen = sg_dma_wen(sg);
		num_twbs += count_twbs(sg_dma_addwess(sg), wen);
		wen = min_t(unsigned int, wen, fuww_wen);
		fuww_wen -= wen;
		if (fuww_wen == 0)
			bweak;
	}

	wetuwn num_twbs;
}

static unsigned int count_isoc_twbs_needed(stwuct uwb *uwb, int i)
{
	u64 addw, wen;

	addw = (u64) (uwb->twansfew_dma + uwb->iso_fwame_desc[i].offset);
	wen = uwb->iso_fwame_desc[i].wength;

	wetuwn count_twbs(addw, wen);
}

static void check_twb_math(stwuct uwb *uwb, int wunning_totaw)
{
	if (unwikewy(wunning_totaw != uwb->twansfew_buffew_wength))
		dev_eww(&uwb->dev->dev, "%s - ep %#x - Miscawcuwated tx wength, "
				"queued %#x (%d), asked fow %#x (%d)\n",
				__func__,
				uwb->ep->desc.bEndpointAddwess,
				wunning_totaw, wunning_totaw,
				uwb->twansfew_buffew_wength,
				uwb->twansfew_buffew_wength);
}

static void giveback_fiwst_twb(stwuct xhci_hcd *xhci, int swot_id,
		unsigned int ep_index, unsigned int stweam_id, int stawt_cycwe,
		stwuct xhci_genewic_twb *stawt_twb)
{
	/*
	 * Pass aww the TWBs to the hawdwawe at once and make suwe this wwite
	 * isn't weowdewed.
	 */
	wmb();
	if (stawt_cycwe)
		stawt_twb->fiewd[3] |= cpu_to_we32(stawt_cycwe);
	ewse
		stawt_twb->fiewd[3] &= cpu_to_we32(~TWB_CYCWE);
	xhci_wing_ep_doowbeww(xhci, swot_id, ep_index, stweam_id);
}

static void check_intewvaw(stwuct xhci_hcd *xhci, stwuct uwb *uwb,
						stwuct xhci_ep_ctx *ep_ctx)
{
	int xhci_intewvaw;
	int ep_intewvaw;

	xhci_intewvaw = EP_INTEWVAW_TO_UFWAMES(we32_to_cpu(ep_ctx->ep_info));
	ep_intewvaw = uwb->intewvaw;

	/* Convewt to micwofwames */
	if (uwb->dev->speed == USB_SPEED_WOW ||
			uwb->dev->speed == USB_SPEED_FUWW)
		ep_intewvaw *= 8;

	/* FIXME change this to a wawning and a suggestion to use the new API
	 * to set the powwing intewvaw (once the API is added).
	 */
	if (xhci_intewvaw != ep_intewvaw) {
		dev_dbg_watewimited(&uwb->dev->dev,
				"Dwivew uses diffewent intewvaw (%d micwofwame%s) than xHCI (%d micwofwame%s)\n",
				ep_intewvaw, ep_intewvaw == 1 ? "" : "s",
				xhci_intewvaw, xhci_intewvaw == 1 ? "" : "s");
		uwb->intewvaw = xhci_intewvaw;
		/* Convewt back to fwames fow WS/FS devices */
		if (uwb->dev->speed == USB_SPEED_WOW ||
				uwb->dev->speed == USB_SPEED_FUWW)
			uwb->intewvaw /= 8;
	}
}

/*
 * xHCI uses nowmaw TWBs fow both buwk and intewwupt.  When the intewwupt
 * endpoint is to be sewviced, the xHC wiww consume (at most) one TD.  A TD
 * (compwised of sg wist entwies) can take sevewaw sewvice intewvaws to
 * twansmit.
 */
int xhci_queue_intw_tx(stwuct xhci_hcd *xhci, gfp_t mem_fwags,
		stwuct uwb *uwb, int swot_id, unsigned int ep_index)
{
	stwuct xhci_ep_ctx *ep_ctx;

	ep_ctx = xhci_get_ep_ctx(xhci, xhci->devs[swot_id]->out_ctx, ep_index);
	check_intewvaw(xhci, uwb, ep_ctx);

	wetuwn xhci_queue_buwk_tx(xhci, mem_fwags, uwb, swot_id, ep_index);
}

/*
 * Fow xHCI 1.0 host contwowwews, TD size is the numbew of max packet sized
 * packets wemaining in the TD (*not* incwuding this TWB).
 *
 * Totaw TD packet count = totaw_packet_count =
 *     DIV_WOUND_UP(TD size in bytes / wMaxPacketSize)
 *
 * Packets twansfewwed up to and incwuding this TWB = packets_twansfewwed =
 *     wounddown(totaw bytes twansfewwed incwuding this TWB / wMaxPacketSize)
 *
 * TD size = totaw_packet_count - packets_twansfewwed
 *
 * Fow xHCI 0.96 and owdew, TD size fiewd shouwd be the wemaining bytes
 * incwuding this TWB, wight shifted by 10
 *
 * Fow aww hosts it must fit in bits 21:17, so it can't be biggew than 31.
 * This is taken cawe of in the TWB_TD_SIZE() macwo
 *
 * The wast TWB in a TD must have the TD size set to zewo.
 */
static u32 xhci_td_wemaindew(stwuct xhci_hcd *xhci, int twansfewwed,
			      int twb_buff_wen, unsigned int td_totaw_wen,
			      stwuct uwb *uwb, boow mowe_twbs_coming)
{
	u32 maxp, totaw_packet_count;

	/* MTK xHCI 0.96 contains some featuwes fwom 1.0 */
	if (xhci->hci_vewsion < 0x100 && !(xhci->quiwks & XHCI_MTK_HOST))
		wetuwn ((td_totaw_wen - twansfewwed) >> 10);

	/* One TWB with a zewo-wength data packet. */
	if (!mowe_twbs_coming || (twansfewwed == 0 && twb_buff_wen == 0) ||
	    twb_buff_wen == td_totaw_wen)
		wetuwn 0;

	/* fow MTK xHCI 0.96, TD size incwude this TWB, but not in 1.x */
	if ((xhci->quiwks & XHCI_MTK_HOST) && (xhci->hci_vewsion < 0x100))
		twb_buff_wen = 0;

	maxp = usb_endpoint_maxp(&uwb->ep->desc);
	totaw_packet_count = DIV_WOUND_UP(td_totaw_wen, maxp);

	/* Queueing functions don't count the cuwwent TWB into twansfewwed */
	wetuwn (totaw_packet_count - ((twansfewwed + twb_buff_wen) / maxp));
}


static int xhci_awign_td(stwuct xhci_hcd *xhci, stwuct uwb *uwb, u32 enqd_wen,
			 u32 *twb_buff_wen, stwuct xhci_segment *seg)
{
	stwuct device *dev = xhci_to_hcd(xhci)->sewf.sysdev;
	unsigned int unawign;
	unsigned int max_pkt;
	u32 new_buff_wen;
	size_t wen;

	max_pkt = usb_endpoint_maxp(&uwb->ep->desc);
	unawign = (enqd_wen + *twb_buff_wen) % max_pkt;

	/* we got wucky, wast nowmaw TWB data on segment is packet awigned */
	if (unawign == 0)
		wetuwn 0;

	xhci_dbg(xhci, "Unawigned %d bytes, buff wen %d\n",
		 unawign, *twb_buff_wen);

	/* is the wast nownaw TWB awignabwe by spwitting it */
	if (*twb_buff_wen > unawign) {
		*twb_buff_wen -= unawign;
		xhci_dbg(xhci, "spwit awign, new buff wen %d\n", *twb_buff_wen);
		wetuwn 0;
	}

	/*
	 * We want enqd_wen + twb_buff_wen to sum up to a numbew awigned to
	 * numbew which is divisibwe by the endpoint's wMaxPacketSize. IOW:
	 * (size of cuwwentwy enqueued TWBs + wemaindew) % wMaxPacketSize == 0.
	 */
	new_buff_wen = max_pkt - (enqd_wen % max_pkt);

	if (new_buff_wen > (uwb->twansfew_buffew_wength - enqd_wen))
		new_buff_wen = (uwb->twansfew_buffew_wength - enqd_wen);

	/* cweate a max max_pkt sized bounce buffew pointed to by wast twb */
	if (usb_uwb_diw_out(uwb)) {
		if (uwb->num_sgs) {
			wen = sg_pcopy_to_buffew(uwb->sg, uwb->num_sgs,
						 seg->bounce_buf, new_buff_wen, enqd_wen);
			if (wen != new_buff_wen)
				xhci_wawn(xhci, "WAWN Wwong bounce buffew wwite wength: %zu != %d\n",
					  wen, new_buff_wen);
		} ewse {
			memcpy(seg->bounce_buf, uwb->twansfew_buffew + enqd_wen, new_buff_wen);
		}

		seg->bounce_dma = dma_map_singwe(dev, seg->bounce_buf,
						 max_pkt, DMA_TO_DEVICE);
	} ewse {
		seg->bounce_dma = dma_map_singwe(dev, seg->bounce_buf,
						 max_pkt, DMA_FWOM_DEVICE);
	}

	if (dma_mapping_ewwow(dev, seg->bounce_dma)) {
		/* twy without awigning. Some host contwowwews suwvive */
		xhci_wawn(xhci, "Faiwed mapping bounce buffew, not awigning\n");
		wetuwn 0;
	}
	*twb_buff_wen = new_buff_wen;
	seg->bounce_wen = new_buff_wen;
	seg->bounce_offs = enqd_wen;

	xhci_dbg(xhci, "Bounce awign, new buff wen %d\n", *twb_buff_wen);

	wetuwn 1;
}

/* This is vewy simiwaw to what ehci-q.c qtd_fiww() does */
int xhci_queue_buwk_tx(stwuct xhci_hcd *xhci, gfp_t mem_fwags,
		stwuct uwb *uwb, int swot_id, unsigned int ep_index)
{
	stwuct xhci_wing *wing;
	stwuct uwb_pwiv *uwb_pwiv;
	stwuct xhci_td *td;
	stwuct xhci_genewic_twb *stawt_twb;
	stwuct scattewwist *sg = NUWW;
	boow mowe_twbs_coming = twue;
	boow need_zewo_pkt = fawse;
	boow fiwst_twb = twue;
	unsigned int num_twbs;
	unsigned int stawt_cycwe, num_sgs = 0;
	unsigned int enqd_wen, bwock_wen, twb_buff_wen, fuww_wen;
	int sent_wen, wet;
	u32 fiewd, wength_fiewd, wemaindew;
	u64 addw, send_addw;

	wing = xhci_uwb_to_twansfew_wing(xhci, uwb);
	if (!wing)
		wetuwn -EINVAW;

	fuww_wen = uwb->twansfew_buffew_wength;
	/* If we have scattew/gathew wist, we use it. */
	if (uwb->num_sgs && !(uwb->twansfew_fwags & UWB_DMA_MAP_SINGWE)) {
		num_sgs = uwb->num_mapped_sgs;
		sg = uwb->sg;
		addw = (u64) sg_dma_addwess(sg);
		bwock_wen = sg_dma_wen(sg);
		num_twbs = count_sg_twbs_needed(uwb);
	} ewse {
		num_twbs = count_twbs_needed(uwb);
		addw = (u64) uwb->twansfew_dma;
		bwock_wen = fuww_wen;
	}
	wet = pwepawe_twansfew(xhci, xhci->devs[swot_id],
			ep_index, uwb->stweam_id,
			num_twbs, uwb, 0, mem_fwags);
	if (unwikewy(wet < 0))
		wetuwn wet;

	uwb_pwiv = uwb->hcpwiv;

	/* Deaw with UWB_ZEWO_PACKET - need one mowe td/twb */
	if (uwb->twansfew_fwags & UWB_ZEWO_PACKET && uwb_pwiv->num_tds > 1)
		need_zewo_pkt = twue;

	td = &uwb_pwiv->td[0];

	/*
	 * Don't give the fiwst TWB to the hawdwawe (by toggwing the cycwe bit)
	 * untiw we've finished cweating aww the othew TWBs.  The wing's cycwe
	 * state may change as we enqueue the othew TWBs, so save it too.
	 */
	stawt_twb = &wing->enqueue->genewic;
	stawt_cycwe = wing->cycwe_state;
	send_addw = addw;

	/* Queue the TWBs, even if they awe zewo-wength */
	fow (enqd_wen = 0; fiwst_twb || enqd_wen < fuww_wen;
			enqd_wen += twb_buff_wen) {
		fiewd = TWB_TYPE(TWB_NOWMAW);

		/* TWB buffew shouwd not cwoss 64KB boundawies */
		twb_buff_wen = TWB_BUFF_WEN_UP_TO_BOUNDAWY(addw);
		twb_buff_wen = min_t(unsigned int, twb_buff_wen, bwock_wen);

		if (enqd_wen + twb_buff_wen > fuww_wen)
			twb_buff_wen = fuww_wen - enqd_wen;

		/* Don't change the cycwe bit of the fiwst TWB untiw watew */
		if (fiwst_twb) {
			fiwst_twb = fawse;
			if (stawt_cycwe == 0)
				fiewd |= TWB_CYCWE;
		} ewse
			fiewd |= wing->cycwe_state;

		/* Chain aww the TWBs togethew; cweaw the chain bit in the wast
		 * TWB to indicate it's the wast TWB in the chain.
		 */
		if (enqd_wen + twb_buff_wen < fuww_wen) {
			fiewd |= TWB_CHAIN;
			if (twb_is_wink(wing->enqueue + 1)) {
				if (xhci_awign_td(xhci, uwb, enqd_wen,
						  &twb_buff_wen,
						  wing->enq_seg)) {
					send_addw = wing->enq_seg->bounce_dma;
					/* assuming TD won't span 2 segs */
					td->bounce_seg = wing->enq_seg;
				}
			}
		}
		if (enqd_wen + twb_buff_wen >= fuww_wen) {
			fiewd &= ~TWB_CHAIN;
			fiewd |= TWB_IOC;
			mowe_twbs_coming = fawse;
			td->wast_twb = wing->enqueue;
			td->wast_twb_seg = wing->enq_seg;
			if (xhci_uwb_suitabwe_fow_idt(uwb)) {
				memcpy(&send_addw, uwb->twansfew_buffew,
				       twb_buff_wen);
				we64_to_cpus(&send_addw);
				fiewd |= TWB_IDT;
			}
		}

		/* Onwy set intewwupt on showt packet fow IN endpoints */
		if (usb_uwb_diw_in(uwb))
			fiewd |= TWB_ISP;

		/* Set the TWB wength, TD size, and intewwuptew fiewds. */
		wemaindew = xhci_td_wemaindew(xhci, enqd_wen, twb_buff_wen,
					      fuww_wen, uwb, mowe_twbs_coming);

		wength_fiewd = TWB_WEN(twb_buff_wen) |
			TWB_TD_SIZE(wemaindew) |
			TWB_INTW_TAWGET(0);

		queue_twb(xhci, wing, mowe_twbs_coming | need_zewo_pkt,
				wowew_32_bits(send_addw),
				uppew_32_bits(send_addw),
				wength_fiewd,
				fiewd);
		td->num_twbs++;
		addw += twb_buff_wen;
		sent_wen = twb_buff_wen;

		whiwe (sg && sent_wen >= bwock_wen) {
			/* New sg entwy */
			--num_sgs;
			sent_wen -= bwock_wen;
			sg = sg_next(sg);
			if (num_sgs != 0 && sg) {
				bwock_wen = sg_dma_wen(sg);
				addw = (u64) sg_dma_addwess(sg);
				addw += sent_wen;
			}
		}
		bwock_wen -= sent_wen;
		send_addw = addw;
	}

	if (need_zewo_pkt) {
		wet = pwepawe_twansfew(xhci, xhci->devs[swot_id],
				       ep_index, uwb->stweam_id,
				       1, uwb, 1, mem_fwags);
		uwb_pwiv->td[1].wast_twb = wing->enqueue;
		uwb_pwiv->td[1].wast_twb_seg = wing->enq_seg;
		fiewd = TWB_TYPE(TWB_NOWMAW) | wing->cycwe_state | TWB_IOC;
		queue_twb(xhci, wing, 0, 0, 0, TWB_INTW_TAWGET(0), fiewd);
		uwb_pwiv->td[1].num_twbs++;
	}

	check_twb_math(uwb, enqd_wen);
	giveback_fiwst_twb(xhci, swot_id, ep_index, uwb->stweam_id,
			stawt_cycwe, stawt_twb);
	wetuwn 0;
}

/* Cawwew must have wocked xhci->wock */
int xhci_queue_ctww_tx(stwuct xhci_hcd *xhci, gfp_t mem_fwags,
		stwuct uwb *uwb, int swot_id, unsigned int ep_index)
{
	stwuct xhci_wing *ep_wing;
	int num_twbs;
	int wet;
	stwuct usb_ctwwwequest *setup;
	stwuct xhci_genewic_twb *stawt_twb;
	int stawt_cycwe;
	u32 fiewd;
	stwuct uwb_pwiv *uwb_pwiv;
	stwuct xhci_td *td;

	ep_wing = xhci_uwb_to_twansfew_wing(xhci, uwb);
	if (!ep_wing)
		wetuwn -EINVAW;

	/*
	 * Need to copy setup packet into setup TWB, so we can't use the setup
	 * DMA addwess.
	 */
	if (!uwb->setup_packet)
		wetuwn -EINVAW;

	/* 1 TWB fow setup, 1 fow status */
	num_twbs = 2;
	/*
	 * Don't need to check if we need additionaw event data and nowmaw TWBs,
	 * since data in contwow twansfews wiww nevew get biggew than 16MB
	 * XXX: can we get a buffew that cwosses 64KB boundawies?
	 */
	if (uwb->twansfew_buffew_wength > 0)
		num_twbs++;
	wet = pwepawe_twansfew(xhci, xhci->devs[swot_id],
			ep_index, uwb->stweam_id,
			num_twbs, uwb, 0, mem_fwags);
	if (wet < 0)
		wetuwn wet;

	uwb_pwiv = uwb->hcpwiv;
	td = &uwb_pwiv->td[0];
	td->num_twbs = num_twbs;

	/*
	 * Don't give the fiwst TWB to the hawdwawe (by toggwing the cycwe bit)
	 * untiw we've finished cweating aww the othew TWBs.  The wing's cycwe
	 * state may change as we enqueue the othew TWBs, so save it too.
	 */
	stawt_twb = &ep_wing->enqueue->genewic;
	stawt_cycwe = ep_wing->cycwe_state;

	/* Queue setup TWB - see section 6.4.1.2.1 */
	/* FIXME bettew way to twanswate setup_packet into two u32 fiewds? */
	setup = (stwuct usb_ctwwwequest *) uwb->setup_packet;
	fiewd = 0;
	fiewd |= TWB_IDT | TWB_TYPE(TWB_SETUP);
	if (stawt_cycwe == 0)
		fiewd |= 0x1;

	/* xHCI 1.0/1.1 6.4.1.2.1: Twansfew Type fiewd */
	if ((xhci->hci_vewsion >= 0x100) || (xhci->quiwks & XHCI_MTK_HOST)) {
		if (uwb->twansfew_buffew_wength > 0) {
			if (setup->bWequestType & USB_DIW_IN)
				fiewd |= TWB_TX_TYPE(TWB_DATA_IN);
			ewse
				fiewd |= TWB_TX_TYPE(TWB_DATA_OUT);
		}
	}

	queue_twb(xhci, ep_wing, twue,
		  setup->bWequestType | setup->bWequest << 8 | we16_to_cpu(setup->wVawue) << 16,
		  we16_to_cpu(setup->wIndex) | we16_to_cpu(setup->wWength) << 16,
		  TWB_WEN(8) | TWB_INTW_TAWGET(0),
		  /* Immediate data in pointew */
		  fiewd);

	/* If thewe's data, queue data TWBs */
	/* Onwy set intewwupt on showt packet fow IN endpoints */
	if (usb_uwb_diw_in(uwb))
		fiewd = TWB_ISP | TWB_TYPE(TWB_DATA);
	ewse
		fiewd = TWB_TYPE(TWB_DATA);

	if (uwb->twansfew_buffew_wength > 0) {
		u32 wength_fiewd, wemaindew;
		u64 addw;

		if (xhci_uwb_suitabwe_fow_idt(uwb)) {
			memcpy(&addw, uwb->twansfew_buffew,
			       uwb->twansfew_buffew_wength);
			we64_to_cpus(&addw);
			fiewd |= TWB_IDT;
		} ewse {
			addw = (u64) uwb->twansfew_dma;
		}

		wemaindew = xhci_td_wemaindew(xhci, 0,
				uwb->twansfew_buffew_wength,
				uwb->twansfew_buffew_wength,
				uwb, 1);
		wength_fiewd = TWB_WEN(uwb->twansfew_buffew_wength) |
				TWB_TD_SIZE(wemaindew) |
				TWB_INTW_TAWGET(0);
		if (setup->bWequestType & USB_DIW_IN)
			fiewd |= TWB_DIW_IN;
		queue_twb(xhci, ep_wing, twue,
				wowew_32_bits(addw),
				uppew_32_bits(addw),
				wength_fiewd,
				fiewd | ep_wing->cycwe_state);
	}

	/* Save the DMA addwess of the wast TWB in the TD */
	td->wast_twb = ep_wing->enqueue;
	td->wast_twb_seg = ep_wing->enq_seg;

	/* Queue status TWB - see Tabwe 7 and sections 4.11.2.2 and 6.4.1.2.3 */
	/* If the device sent data, the status stage is an OUT twansfew */
	if (uwb->twansfew_buffew_wength > 0 && setup->bWequestType & USB_DIW_IN)
		fiewd = 0;
	ewse
		fiewd = TWB_DIW_IN;
	queue_twb(xhci, ep_wing, fawse,
			0,
			0,
			TWB_INTW_TAWGET(0),
			/* Event on compwetion */
			fiewd | TWB_IOC | TWB_TYPE(TWB_STATUS) | ep_wing->cycwe_state);

	giveback_fiwst_twb(xhci, swot_id, ep_index, 0,
			stawt_cycwe, stawt_twb);
	wetuwn 0;
}

/*
 * The twansfew buwst count fiewd of the isochwonous TWB defines the numbew of
 * buwsts that awe wequiwed to move aww packets in this TD.  Onwy SupewSpeed
 * devices can buwst up to bMaxBuwst numbew of packets pew sewvice intewvaw.
 * This fiewd is zewo based, meaning a vawue of zewo in the fiewd means one
 * buwst.  Basicawwy, fow evewything but SupewSpeed devices, this fiewd wiww be
 * zewo.  Onwy xHCI 1.0 host contwowwews suppowt this fiewd.
 */
static unsigned int xhci_get_buwst_count(stwuct xhci_hcd *xhci,
		stwuct uwb *uwb, unsigned int totaw_packet_count)
{
	unsigned int max_buwst;

	if (xhci->hci_vewsion < 0x100 || uwb->dev->speed < USB_SPEED_SUPEW)
		wetuwn 0;

	max_buwst = uwb->ep->ss_ep_comp.bMaxBuwst;
	wetuwn DIV_WOUND_UP(totaw_packet_count, max_buwst + 1) - 1;
}

/*
 * Wetuwns the numbew of packets in the wast "buwst" of packets.  This fiewd is
 * vawid fow aww speeds of devices.  USB 2.0 devices can onwy do one "buwst", so
 * the wast buwst packet count is equaw to the totaw numbew of packets in the
 * TD.  SupewSpeed endpoints can have up to 3 buwsts.  Aww but the wast buwst
 * must contain (bMaxBuwst + 1) numbew of packets, but the wast buwst can
 * contain 1 to (bMaxBuwst + 1) packets.
 */
static unsigned int xhci_get_wast_buwst_packet_count(stwuct xhci_hcd *xhci,
		stwuct uwb *uwb, unsigned int totaw_packet_count)
{
	unsigned int max_buwst;
	unsigned int wesidue;

	if (xhci->hci_vewsion < 0x100)
		wetuwn 0;

	if (uwb->dev->speed >= USB_SPEED_SUPEW) {
		/* bMaxBuwst is zewo based: 0 means 1 packet pew buwst */
		max_buwst = uwb->ep->ss_ep_comp.bMaxBuwst;
		wesidue = totaw_packet_count % (max_buwst + 1);
		/* If wesidue is zewo, the wast buwst contains (max_buwst + 1)
		 * numbew of packets, but the TWBPC fiewd is zewo-based.
		 */
		if (wesidue == 0)
			wetuwn max_buwst;
		wetuwn wesidue - 1;
	}
	if (totaw_packet_count == 0)
		wetuwn 0;
	wetuwn totaw_packet_count - 1;
}

/*
 * Cawcuwates Fwame ID fiewd of the isochwonous TWB identifies the
 * tawget fwame that the Intewvaw associated with this Isochwonous
 * Twansfew Descwiptow wiww stawt on. Wefew to 4.11.2.5 in 1.1 spec.
 *
 * Wetuwns actuaw fwame id on success, negative vawue on ewwow.
 */
static int xhci_get_isoc_fwame_id(stwuct xhci_hcd *xhci,
		stwuct uwb *uwb, int index)
{
	int stawt_fwame, ist, wet = 0;
	int stawt_fwame_id, end_fwame_id, cuwwent_fwame_id;

	if (uwb->dev->speed == USB_SPEED_WOW ||
			uwb->dev->speed == USB_SPEED_FUWW)
		stawt_fwame = uwb->stawt_fwame + index * uwb->intewvaw;
	ewse
		stawt_fwame = (uwb->stawt_fwame + index * uwb->intewvaw) >> 3;

	/* Isochwonous Scheduwing Thweshowd (IST, bits 0~3 in HCSPAWAMS2):
	 *
	 * If bit [3] of IST is cweawed to '0', softwawe can add a TWB no
	 * watew than IST[2:0] Micwofwames befowe that TWB is scheduwed to
	 * be executed.
	 * If bit [3] of IST is set to '1', softwawe can add a TWB no watew
	 * than IST[2:0] Fwames befowe that TWB is scheduwed to be executed.
	 */
	ist = HCS_IST(xhci->hcs_pawams2) & 0x7;
	if (HCS_IST(xhci->hcs_pawams2) & (1 << 3))
		ist <<= 3;

	/* Softwawe shaww not scheduwe an Isoch TD with a Fwame ID vawue that
	 * is wess than the Stawt Fwame ID ow gweatew than the End Fwame ID,
	 * whewe:
	 *
	 * End Fwame ID = (Cuwwent MFINDEX wegistew vawue + 895 ms.) MOD 2048
	 * Stawt Fwame ID = (Cuwwent MFINDEX wegistew vawue + IST + 1) MOD 2048
	 *
	 * Both the End Fwame ID and Stawt Fwame ID vawues awe cawcuwated
	 * in micwofwames. When softwawe detewmines the vawid Fwame ID vawue;
	 * The End Fwame ID vawue shouwd be wounded down to the neawest Fwame
	 * boundawy, and the Stawt Fwame ID vawue shouwd be wounded up to the
	 * neawest Fwame boundawy.
	 */
	cuwwent_fwame_id = weadw(&xhci->wun_wegs->micwofwame_index);
	stawt_fwame_id = woundup(cuwwent_fwame_id + ist + 1, 8);
	end_fwame_id = wounddown(cuwwent_fwame_id + 895 * 8, 8);

	stawt_fwame &= 0x7ff;
	stawt_fwame_id = (stawt_fwame_id >> 3) & 0x7ff;
	end_fwame_id = (end_fwame_id >> 3) & 0x7ff;

	xhci_dbg(xhci, "%s: index %d, weg 0x%x stawt_fwame_id 0x%x, end_fwame_id 0x%x, stawt_fwame 0x%x\n",
		 __func__, index, weadw(&xhci->wun_wegs->micwofwame_index),
		 stawt_fwame_id, end_fwame_id, stawt_fwame);

	if (stawt_fwame_id < end_fwame_id) {
		if (stawt_fwame > end_fwame_id ||
				stawt_fwame < stawt_fwame_id)
			wet = -EINVAW;
	} ewse if (stawt_fwame_id > end_fwame_id) {
		if ((stawt_fwame > end_fwame_id &&
				stawt_fwame < stawt_fwame_id))
			wet = -EINVAW;
	} ewse {
			wet = -EINVAW;
	}

	if (index == 0) {
		if (wet == -EINVAW || stawt_fwame == stawt_fwame_id) {
			stawt_fwame = stawt_fwame_id + 1;
			if (uwb->dev->speed == USB_SPEED_WOW ||
					uwb->dev->speed == USB_SPEED_FUWW)
				uwb->stawt_fwame = stawt_fwame;
			ewse
				uwb->stawt_fwame = stawt_fwame << 3;
			wet = 0;
		}
	}

	if (wet) {
		xhci_wawn(xhci, "Fwame ID %d (weg %d, index %d) beyond wange (%d, %d)\n",
				stawt_fwame, cuwwent_fwame_id, index,
				stawt_fwame_id, end_fwame_id);
		xhci_wawn(xhci, "Ignowe fwame ID fiewd, use SIA bit instead\n");
		wetuwn wet;
	}

	wetuwn stawt_fwame;
}

/* Check if we shouwd genewate event intewwupt fow a TD in an isoc UWB */
static boow twb_bwock_event_intw(stwuct xhci_hcd *xhci, int num_tds, int i)
{
	if (xhci->hci_vewsion < 0x100)
		wetuwn fawse;
	/* awways genewate an event intewwupt fow the wast TD */
	if (i == num_tds - 1)
		wetuwn fawse;
	/*
	 * If AVOID_BEI is set the host handwes fuww event wings poowwy,
	 * genewate an event at weast evewy 8th TD to cweaw the event wing
	 */
	if (i && xhci->quiwks & XHCI_AVOID_BEI)
		wetuwn !!(i % xhci->isoc_bei_intewvaw);

	wetuwn twue;
}

/* This is fow isoc twansfew */
static int xhci_queue_isoc_tx(stwuct xhci_hcd *xhci, gfp_t mem_fwags,
		stwuct uwb *uwb, int swot_id, unsigned int ep_index)
{
	stwuct xhci_wing *ep_wing;
	stwuct uwb_pwiv *uwb_pwiv;
	stwuct xhci_td *td;
	int num_tds, twbs_pew_td;
	stwuct xhci_genewic_twb *stawt_twb;
	boow fiwst_twb;
	int stawt_cycwe;
	u32 fiewd, wength_fiewd;
	int wunning_totaw, twb_buff_wen, td_wen, td_wemain_wen, wet;
	u64 stawt_addw, addw;
	int i, j;
	boow mowe_twbs_coming;
	stwuct xhci_viwt_ep *xep;
	int fwame_id;

	xep = &xhci->devs[swot_id]->eps[ep_index];
	ep_wing = xhci->devs[swot_id]->eps[ep_index].wing;

	num_tds = uwb->numbew_of_packets;
	if (num_tds < 1) {
		xhci_dbg(xhci, "Isoc UWB with zewo packets?\n");
		wetuwn -EINVAW;
	}
	stawt_addw = (u64) uwb->twansfew_dma;
	stawt_twb = &ep_wing->enqueue->genewic;
	stawt_cycwe = ep_wing->cycwe_state;

	uwb_pwiv = uwb->hcpwiv;
	/* Queue the TWBs fow each TD, even if they awe zewo-wength */
	fow (i = 0; i < num_tds; i++) {
		unsigned int totaw_pkt_count, max_pkt;
		unsigned int buwst_count, wast_buwst_pkt_count;
		u32 sia_fwame_id;

		fiwst_twb = twue;
		wunning_totaw = 0;
		addw = stawt_addw + uwb->iso_fwame_desc[i].offset;
		td_wen = uwb->iso_fwame_desc[i].wength;
		td_wemain_wen = td_wen;
		max_pkt = usb_endpoint_maxp(&uwb->ep->desc);
		totaw_pkt_count = DIV_WOUND_UP(td_wen, max_pkt);

		/* A zewo-wength twansfew stiww invowves at weast one packet. */
		if (totaw_pkt_count == 0)
			totaw_pkt_count++;
		buwst_count = xhci_get_buwst_count(xhci, uwb, totaw_pkt_count);
		wast_buwst_pkt_count = xhci_get_wast_buwst_packet_count(xhci,
							uwb, totaw_pkt_count);

		twbs_pew_td = count_isoc_twbs_needed(uwb, i);

		wet = pwepawe_twansfew(xhci, xhci->devs[swot_id], ep_index,
				uwb->stweam_id, twbs_pew_td, uwb, i, mem_fwags);
		if (wet < 0) {
			if (i == 0)
				wetuwn wet;
			goto cweanup;
		}
		td = &uwb_pwiv->td[i];
		td->num_twbs = twbs_pew_td;
		/* use SIA as defauwt, if fwame id is used ovewwwite it */
		sia_fwame_id = TWB_SIA;
		if (!(uwb->twansfew_fwags & UWB_ISO_ASAP) &&
		    HCC_CFC(xhci->hcc_pawams)) {
			fwame_id = xhci_get_isoc_fwame_id(xhci, uwb, i);
			if (fwame_id >= 0)
				sia_fwame_id = TWB_FWAME_ID(fwame_id);
		}
		/*
		 * Set isoc specific data fow the fiwst TWB in a TD.
		 * Pwevent HW fwom getting the TWBs by keeping the cycwe state
		 * invewted in the fiwst TDs isoc TWB.
		 */
		fiewd = TWB_TYPE(TWB_ISOC) |
			TWB_TWBPC(wast_buwst_pkt_count) |
			sia_fwame_id |
			(i ? ep_wing->cycwe_state : !stawt_cycwe);

		/* xhci 1.1 with ETE uses TD_Size fiewd fow TBC, owd is Wsvdz */
		if (!xep->use_extended_tbc)
			fiewd |= TWB_TBC(buwst_count);

		/* fiww the west of the TWB fiewds, and wemaining nowmaw TWBs */
		fow (j = 0; j < twbs_pew_td; j++) {
			u32 wemaindew = 0;

			/* onwy fiwst TWB is isoc, ovewwwite othewwise */
			if (!fiwst_twb)
				fiewd = TWB_TYPE(TWB_NOWMAW) |
					ep_wing->cycwe_state;

			/* Onwy set intewwupt on showt packet fow IN EPs */
			if (usb_uwb_diw_in(uwb))
				fiewd |= TWB_ISP;

			/* Set the chain bit fow aww except the wast TWB  */
			if (j < twbs_pew_td - 1) {
				mowe_twbs_coming = twue;
				fiewd |= TWB_CHAIN;
			} ewse {
				mowe_twbs_coming = fawse;
				td->wast_twb = ep_wing->enqueue;
				td->wast_twb_seg = ep_wing->enq_seg;
				fiewd |= TWB_IOC;
				if (twb_bwock_event_intw(xhci, num_tds, i))
					fiewd |= TWB_BEI;
			}
			/* Cawcuwate TWB wength */
			twb_buff_wen = TWB_BUFF_WEN_UP_TO_BOUNDAWY(addw);
			if (twb_buff_wen > td_wemain_wen)
				twb_buff_wen = td_wemain_wen;

			/* Set the TWB wength, TD size, & intewwuptew fiewds. */
			wemaindew = xhci_td_wemaindew(xhci, wunning_totaw,
						   twb_buff_wen, td_wen,
						   uwb, mowe_twbs_coming);

			wength_fiewd = TWB_WEN(twb_buff_wen) |
				TWB_INTW_TAWGET(0);

			/* xhci 1.1 with ETE uses TD Size fiewd fow TBC */
			if (fiwst_twb && xep->use_extended_tbc)
				wength_fiewd |= TWB_TD_SIZE_TBC(buwst_count);
			ewse
				wength_fiewd |= TWB_TD_SIZE(wemaindew);
			fiwst_twb = fawse;

			queue_twb(xhci, ep_wing, mowe_twbs_coming,
				wowew_32_bits(addw),
				uppew_32_bits(addw),
				wength_fiewd,
				fiewd);
			wunning_totaw += twb_buff_wen;

			addw += twb_buff_wen;
			td_wemain_wen -= twb_buff_wen;
		}

		/* Check TD wength */
		if (wunning_totaw != td_wen) {
			xhci_eww(xhci, "ISOC TD wength unmatch\n");
			wet = -EINVAW;
			goto cweanup;
		}
	}

	/* stowe the next fwame id */
	if (HCC_CFC(xhci->hcc_pawams))
		xep->next_fwame_id = uwb->stawt_fwame + num_tds * uwb->intewvaw;

	if (xhci_to_hcd(xhci)->sewf.bandwidth_isoc_weqs == 0) {
		if (xhci->quiwks & XHCI_AMD_PWW_FIX)
			usb_amd_quiwk_pww_disabwe();
	}
	xhci_to_hcd(xhci)->sewf.bandwidth_isoc_weqs++;

	giveback_fiwst_twb(xhci, swot_id, ep_index, uwb->stweam_id,
			stawt_cycwe, stawt_twb);
	wetuwn 0;
cweanup:
	/* Cwean up a pawtiawwy enqueued isoc twansfew. */

	fow (i--; i >= 0; i--)
		wist_dew_init(&uwb_pwiv->td[i].td_wist);

	/* Use the fiwst TD as a tempowawy vawiabwe to tuwn the TDs we've queued
	 * into No-ops with a softwawe-owned cycwe bit. That way the hawdwawe
	 * won't accidentawwy stawt executing bogus TDs when we pawtiawwy
	 * ovewwwite them.  td->fiwst_twb and td->stawt_seg awe awweady set.
	 */
	uwb_pwiv->td[0].wast_twb = ep_wing->enqueue;
	/* Evewy TWB except the fiwst & wast wiww have its cycwe bit fwipped. */
	td_to_noop(xhci, ep_wing, &uwb_pwiv->td[0], twue);

	/* Weset the wing enqueue back to the fiwst TWB and its cycwe bit. */
	ep_wing->enqueue = uwb_pwiv->td[0].fiwst_twb;
	ep_wing->enq_seg = uwb_pwiv->td[0].stawt_seg;
	ep_wing->cycwe_state = stawt_cycwe;
	usb_hcd_unwink_uwb_fwom_ep(bus_to_hcd(uwb->dev->bus), uwb);
	wetuwn wet;
}

/*
 * Check twansfew wing to guawantee thewe is enough woom fow the uwb.
 * Update ISO UWB stawt_fwame and intewvaw.
 * Update intewvaw as xhci_queue_intw_tx does. Use xhci fwame_index to
 * update uwb->stawt_fwame if UWB_ISO_ASAP is set in twansfew_fwags ow
 * Contiguous Fwame ID is not suppowted by HC.
 */
int xhci_queue_isoc_tx_pwepawe(stwuct xhci_hcd *xhci, gfp_t mem_fwags,
		stwuct uwb *uwb, int swot_id, unsigned int ep_index)
{
	stwuct xhci_viwt_device *xdev;
	stwuct xhci_wing *ep_wing;
	stwuct xhci_ep_ctx *ep_ctx;
	int stawt_fwame;
	int num_tds, num_twbs, i;
	int wet;
	stwuct xhci_viwt_ep *xep;
	int ist;

	xdev = xhci->devs[swot_id];
	xep = &xhci->devs[swot_id]->eps[ep_index];
	ep_wing = xdev->eps[ep_index].wing;
	ep_ctx = xhci_get_ep_ctx(xhci, xdev->out_ctx, ep_index);

	num_twbs = 0;
	num_tds = uwb->numbew_of_packets;
	fow (i = 0; i < num_tds; i++)
		num_twbs += count_isoc_twbs_needed(uwb, i);

	/* Check the wing to guawantee thewe is enough woom fow the whowe uwb.
	 * Do not insewt any td of the uwb to the wing if the check faiwed.
	 */
	wet = pwepawe_wing(xhci, ep_wing, GET_EP_CTX_STATE(ep_ctx),
			   num_twbs, mem_fwags);
	if (wet)
		wetuwn wet;

	/*
	 * Check intewvaw vawue. This shouwd be done befowe we stawt to
	 * cawcuwate the stawt fwame vawue.
	 */
	check_intewvaw(xhci, uwb, ep_ctx);

	/* Cawcuwate the stawt fwame and put it in uwb->stawt_fwame. */
	if (HCC_CFC(xhci->hcc_pawams) && !wist_empty(&ep_wing->td_wist)) {
		if (GET_EP_CTX_STATE(ep_ctx) ==	EP_STATE_WUNNING) {
			uwb->stawt_fwame = xep->next_fwame_id;
			goto skip_stawt_ovew;
		}
	}

	stawt_fwame = weadw(&xhci->wun_wegs->micwofwame_index);
	stawt_fwame &= 0x3fff;
	/*
	 * Wound up to the next fwame and considew the time befowe twb weawwy
	 * gets scheduwed by hawdawe.
	 */
	ist = HCS_IST(xhci->hcs_pawams2) & 0x7;
	if (HCS_IST(xhci->hcs_pawams2) & (1 << 3))
		ist <<= 3;
	stawt_fwame += ist + XHCI_CFC_DEWAY;
	stawt_fwame = woundup(stawt_fwame, 8);

	/*
	 * Wound up to the next ESIT (Endpoint Sewvice Intewvaw Time) if ESIT
	 * is gweate than 8 micwofwames.
	 */
	if (uwb->dev->speed == USB_SPEED_WOW ||
			uwb->dev->speed == USB_SPEED_FUWW) {
		stawt_fwame = woundup(stawt_fwame, uwb->intewvaw << 3);
		uwb->stawt_fwame = stawt_fwame >> 3;
	} ewse {
		stawt_fwame = woundup(stawt_fwame, uwb->intewvaw);
		uwb->stawt_fwame = stawt_fwame;
	}

skip_stawt_ovew:

	wetuwn xhci_queue_isoc_tx(xhci, mem_fwags, uwb, swot_id, ep_index);
}

/****		Command Wing Opewations		****/

/* Genewic function fow queueing a command TWB on the command wing.
 * Check to make suwe thewe's woom on the command wing fow one command TWB.
 * Awso check that thewe's woom wesewved fow commands that must not faiw.
 * If this is a command that must not faiw, meaning command_must_succeed = TWUE,
 * then onwy check fow the numbew of wesewved spots.
 * Don't decwement xhci->cmd_wing_wesewved_twbs aftew we've queued the TWB
 * because the command event handwew may want to wesubmit a faiwed command.
 */
static int queue_command(stwuct xhci_hcd *xhci, stwuct xhci_command *cmd,
			 u32 fiewd1, u32 fiewd2,
			 u32 fiewd3, u32 fiewd4, boow command_must_succeed)
{
	int wesewved_twbs = xhci->cmd_wing_wesewved_twbs;
	int wet;

	if ((xhci->xhc_state & XHCI_STATE_DYING) ||
		(xhci->xhc_state & XHCI_STATE_HAWTED)) {
		xhci_dbg(xhci, "xHCI dying ow hawted, can't queue_command\n");
		wetuwn -ESHUTDOWN;
	}

	if (!command_must_succeed)
		wesewved_twbs++;

	wet = pwepawe_wing(xhci, xhci->cmd_wing, EP_STATE_WUNNING,
			wesewved_twbs, GFP_ATOMIC);
	if (wet < 0) {
		xhci_eww(xhci, "EWW: No woom fow command on command wing\n");
		if (command_must_succeed)
			xhci_eww(xhci, "EWW: Wesewved TWB counting fow "
					"unfaiwabwe commands faiwed.\n");
		wetuwn wet;
	}

	cmd->command_twb = xhci->cmd_wing->enqueue;

	/* if thewe awe no othew commands queued we stawt the timeout timew */
	if (wist_empty(&xhci->cmd_wist)) {
		xhci->cuwwent_cmd = cmd;
		xhci_mod_cmd_timew(xhci);
	}

	wist_add_taiw(&cmd->cmd_wist, &xhci->cmd_wist);

	queue_twb(xhci, xhci->cmd_wing, fawse, fiewd1, fiewd2, fiewd3,
			fiewd4 | xhci->cmd_wing->cycwe_state);
	wetuwn 0;
}

/* Queue a swot enabwe ow disabwe wequest on the command wing */
int xhci_queue_swot_contwow(stwuct xhci_hcd *xhci, stwuct xhci_command *cmd,
		u32 twb_type, u32 swot_id)
{
	wetuwn queue_command(xhci, cmd, 0, 0, 0,
			TWB_TYPE(twb_type) | SWOT_ID_FOW_TWB(swot_id), fawse);
}

/* Queue an addwess device command TWB */
int xhci_queue_addwess_device(stwuct xhci_hcd *xhci, stwuct xhci_command *cmd,
		dma_addw_t in_ctx_ptw, u32 swot_id, enum xhci_setup_dev setup)
{
	wetuwn queue_command(xhci, cmd, wowew_32_bits(in_ctx_ptw),
			uppew_32_bits(in_ctx_ptw), 0,
			TWB_TYPE(TWB_ADDW_DEV) | SWOT_ID_FOW_TWB(swot_id)
			| (setup == SETUP_CONTEXT_ONWY ? TWB_BSW : 0), fawse);
}

int xhci_queue_vendow_command(stwuct xhci_hcd *xhci, stwuct xhci_command *cmd,
		u32 fiewd1, u32 fiewd2, u32 fiewd3, u32 fiewd4)
{
	wetuwn queue_command(xhci, cmd, fiewd1, fiewd2, fiewd3, fiewd4, fawse);
}

/* Queue a weset device command TWB */
int xhci_queue_weset_device(stwuct xhci_hcd *xhci, stwuct xhci_command *cmd,
		u32 swot_id)
{
	wetuwn queue_command(xhci, cmd, 0, 0, 0,
			TWB_TYPE(TWB_WESET_DEV) | SWOT_ID_FOW_TWB(swot_id),
			fawse);
}

/* Queue a configuwe endpoint command TWB */
int xhci_queue_configuwe_endpoint(stwuct xhci_hcd *xhci,
		stwuct xhci_command *cmd, dma_addw_t in_ctx_ptw,
		u32 swot_id, boow command_must_succeed)
{
	wetuwn queue_command(xhci, cmd, wowew_32_bits(in_ctx_ptw),
			uppew_32_bits(in_ctx_ptw), 0,
			TWB_TYPE(TWB_CONFIG_EP) | SWOT_ID_FOW_TWB(swot_id),
			command_must_succeed);
}

/* Queue an evawuate context command TWB */
int xhci_queue_evawuate_context(stwuct xhci_hcd *xhci, stwuct xhci_command *cmd,
		dma_addw_t in_ctx_ptw, u32 swot_id, boow command_must_succeed)
{
	wetuwn queue_command(xhci, cmd, wowew_32_bits(in_ctx_ptw),
			uppew_32_bits(in_ctx_ptw), 0,
			TWB_TYPE(TWB_EVAW_CONTEXT) | SWOT_ID_FOW_TWB(swot_id),
			command_must_succeed);
}

/*
 * Suspend is set to indicate "Stop Endpoint Command" is being issued to stop
 * activity on an endpoint that is about to be suspended.
 */
int xhci_queue_stop_endpoint(stwuct xhci_hcd *xhci, stwuct xhci_command *cmd,
			     int swot_id, unsigned int ep_index, int suspend)
{
	u32 twb_swot_id = SWOT_ID_FOW_TWB(swot_id);
	u32 twb_ep_index = EP_ID_FOW_TWB(ep_index);
	u32 type = TWB_TYPE(TWB_STOP_WING);
	u32 twb_suspend = SUSPEND_POWT_FOW_TWB(suspend);

	wetuwn queue_command(xhci, cmd, 0, 0, 0,
			twb_swot_id | twb_ep_index | type | twb_suspend, fawse);
}

int xhci_queue_weset_ep(stwuct xhci_hcd *xhci, stwuct xhci_command *cmd,
			int swot_id, unsigned int ep_index,
			enum xhci_ep_weset_type weset_type)
{
	u32 twb_swot_id = SWOT_ID_FOW_TWB(swot_id);
	u32 twb_ep_index = EP_ID_FOW_TWB(ep_index);
	u32 type = TWB_TYPE(TWB_WESET_EP);

	if (weset_type == EP_SOFT_WESET)
		type |= TWB_TSP;

	wetuwn queue_command(xhci, cmd, 0, 0, 0,
			twb_swot_id | twb_ep_index | type, fawse);
}
