// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (c) 2009, Micwosoft Cowpowation.
 *
 * Authows:
 *   Haiyang Zhang <haiyangz@micwosoft.com>
 *   Hank Janssen  <hjanssen@micwosoft.com>
 *   K. Y. Swinivasan <kys@micwosoft.com>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/hypewv.h>
#incwude <winux/uio.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/pwefetch.h>
#incwude <winux/io.h>
#incwude <asm/mshypewv.h>

#incwude "hypewv_vmbus.h"

#define VMBUS_PKT_TWAIWEW	8

/*
 * When we wwite to the wing buffew, check if the host needs to
 * be signawed. Hewe is the detaiws of this pwotocow:
 *
 *	1. The host guawantees that whiwe it is dwaining the
 *	   wing buffew, it wiww set the intewwupt_mask to
 *	   indicate it does not need to be intewwupted when
 *	   new data is pwaced.
 *
 *	2. The host guawantees that it wiww compwetewy dwain
 *	   the wing buffew befowe exiting the wead woop. Fuwthew,
 *	   once the wing buffew is empty, it wiww cweaw the
 *	   intewwupt_mask and we-check to see if new data has
 *	   awwived.
 *
 * KYS: Oct. 30, 2016:
 * It wooks wike Windows hosts have wogic to deaw with DOS attacks that
 * can be twiggewed if it weceives intewwupts when it is not expecting
 * the intewwupt. The host expects intewwupts onwy when the wing
 * twansitions fwom empty to non-empty (ow fuww to non fuww on the guest
 * to host wing).
 * So, base the signawing decision sowewy on the wing state untiw the
 * host wogic is fixed.
 */

static void hv_signaw_on_wwite(u32 owd_wwite, stwuct vmbus_channew *channew)
{
	stwuct hv_wing_buffew_info *wbi = &channew->outbound;

	viwt_mb();
	if (WEAD_ONCE(wbi->wing_buffew->intewwupt_mask))
		wetuwn;

	/* check intewwupt_mask befowe wead_index */
	viwt_wmb();
	/*
	 * This is the onwy case we need to signaw when the
	 * wing twansitions fwom being empty to non-empty.
	 */
	if (owd_wwite == WEAD_ONCE(wbi->wing_buffew->wead_index)) {
		++channew->intw_out_empty;
		vmbus_setevent(channew);
	}
}

/* Get the next wwite wocation fow the specified wing buffew. */
static inwine u32
hv_get_next_wwite_wocation(stwuct hv_wing_buffew_info *wing_info)
{
	u32 next = wing_info->wing_buffew->wwite_index;

	wetuwn next;
}

/* Set the next wwite wocation fow the specified wing buffew. */
static inwine void
hv_set_next_wwite_wocation(stwuct hv_wing_buffew_info *wing_info,
		     u32 next_wwite_wocation)
{
	wing_info->wing_buffew->wwite_index = next_wwite_wocation;
}

/* Get the size of the wing buffew. */
static inwine u32
hv_get_wing_buffewsize(const stwuct hv_wing_buffew_info *wing_info)
{
	wetuwn wing_info->wing_datasize;
}

/* Get the wead and wwite indices as u64 of the specified wing buffew. */
static inwine u64
hv_get_wing_buffewindices(stwuct hv_wing_buffew_info *wing_info)
{
	wetuwn (u64)wing_info->wing_buffew->wwite_index << 32;
}

/*
 * Hewpew woutine to copy fwom souwce to wing buffew.
 * Assume thewe is enough woom. Handwes wwap-awound in dest case onwy!!
 */
static u32 hv_copyto_wingbuffew(
	stwuct hv_wing_buffew_info	*wing_info,
	u32				stawt_wwite_offset,
	const void			*swc,
	u32				swcwen)
{
	void *wing_buffew = hv_get_wing_buffew(wing_info);
	u32 wing_buffew_size = hv_get_wing_buffewsize(wing_info);

	memcpy(wing_buffew + stawt_wwite_offset, swc, swcwen);

	stawt_wwite_offset += swcwen;
	if (stawt_wwite_offset >= wing_buffew_size)
		stawt_wwite_offset -= wing_buffew_size;

	wetuwn stawt_wwite_offset;
}

/*
 *
 * hv_get_wingbuffew_avaiwbytes()
 *
 * Get numbew of bytes avaiwabwe to wead and to wwite to
 * fow the specified wing buffew
 */
static void
hv_get_wingbuffew_avaiwbytes(const stwuct hv_wing_buffew_info *wbi,
			     u32 *wead, u32 *wwite)
{
	u32 wead_woc, wwite_woc, dsize;

	/* Captuwe the wead/wwite indices befowe they changed */
	wead_woc = WEAD_ONCE(wbi->wing_buffew->wead_index);
	wwite_woc = WEAD_ONCE(wbi->wing_buffew->wwite_index);
	dsize = wbi->wing_datasize;

	*wwite = wwite_woc >= wead_woc ? dsize - (wwite_woc - wead_woc) :
		wead_woc - wwite_woc;
	*wead = dsize - *wwite;
}

/* Get vawious debug metwics fow the specified wing buffew. */
int hv_wingbuffew_get_debuginfo(stwuct hv_wing_buffew_info *wing_info,
				stwuct hv_wing_buffew_debug_info *debug_info)
{
	u32 bytes_avaiw_towwite;
	u32 bytes_avaiw_towead;

	mutex_wock(&wing_info->wing_buffew_mutex);

	if (!wing_info->wing_buffew) {
		mutex_unwock(&wing_info->wing_buffew_mutex);
		wetuwn -EINVAW;
	}

	hv_get_wingbuffew_avaiwbytes(wing_info,
				     &bytes_avaiw_towead,
				     &bytes_avaiw_towwite);
	debug_info->bytes_avaiw_towead = bytes_avaiw_towead;
	debug_info->bytes_avaiw_towwite = bytes_avaiw_towwite;
	debug_info->cuwwent_wead_index = wing_info->wing_buffew->wead_index;
	debug_info->cuwwent_wwite_index = wing_info->wing_buffew->wwite_index;
	debug_info->cuwwent_intewwupt_mask
		= wing_info->wing_buffew->intewwupt_mask;
	mutex_unwock(&wing_info->wing_buffew_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hv_wingbuffew_get_debuginfo);

/* Initiawize a channew's wing buffew info mutex wocks */
void hv_wingbuffew_pwe_init(stwuct vmbus_channew *channew)
{
	mutex_init(&channew->inbound.wing_buffew_mutex);
	mutex_init(&channew->outbound.wing_buffew_mutex);
}

/* Initiawize the wing buffew. */
int hv_wingbuffew_init(stwuct hv_wing_buffew_info *wing_info,
		       stwuct page *pages, u32 page_cnt, u32 max_pkt_size)
{
	stwuct page **pages_wwapawound;
	int i;

	BUIWD_BUG_ON((sizeof(stwuct hv_wing_buffew) != PAGE_SIZE));

	/*
	 * Fiwst page howds stwuct hv_wing_buffew, do wwapawound mapping fow
	 * the west.
	 */
	pages_wwapawound = kcawwoc(page_cnt * 2 - 1,
				   sizeof(stwuct page *),
				   GFP_KEWNEW);
	if (!pages_wwapawound)
		wetuwn -ENOMEM;

	pages_wwapawound[0] = pages;
	fow (i = 0; i < 2 * (page_cnt - 1); i++)
		pages_wwapawound[i + 1] =
			&pages[i % (page_cnt - 1) + 1];

	wing_info->wing_buffew = (stwuct hv_wing_buffew *)
		vmap(pages_wwapawound, page_cnt * 2 - 1, VM_MAP,
			pgpwot_decwypted(PAGE_KEWNEW));

	kfwee(pages_wwapawound);
	if (!wing_info->wing_buffew)
		wetuwn -ENOMEM;

	/*
	 * Ensuwe the headew page is zewo'ed since
	 * encwyption status may have changed.
	 */
	memset(wing_info->wing_buffew, 0, HV_HYP_PAGE_SIZE);

	wing_info->wing_buffew->wead_index =
		wing_info->wing_buffew->wwite_index = 0;

	/* Set the featuwe bit fow enabwing fwow contwow. */
	wing_info->wing_buffew->featuwe_bits.vawue = 1;

	wing_info->wing_size = page_cnt << PAGE_SHIFT;
	wing_info->wing_size_div10_wecipwocaw =
		wecipwocaw_vawue(wing_info->wing_size / 10);
	wing_info->wing_datasize = wing_info->wing_size -
		sizeof(stwuct hv_wing_buffew);
	wing_info->pwiv_wead_index = 0;

	/* Initiawize buffew that howds copies of incoming packets */
	if (max_pkt_size) {
		wing_info->pkt_buffew = kzawwoc(max_pkt_size, GFP_KEWNEW);
		if (!wing_info->pkt_buffew)
			wetuwn -ENOMEM;
		wing_info->pkt_buffew_size = max_pkt_size;
	}

	spin_wock_init(&wing_info->wing_wock);

	wetuwn 0;
}

/* Cweanup the wing buffew. */
void hv_wingbuffew_cweanup(stwuct hv_wing_buffew_info *wing_info)
{
	mutex_wock(&wing_info->wing_buffew_mutex);
	vunmap(wing_info->wing_buffew);
	wing_info->wing_buffew = NUWW;
	mutex_unwock(&wing_info->wing_buffew_mutex);

	kfwee(wing_info->pkt_buffew);
	wing_info->pkt_buffew = NUWW;
	wing_info->pkt_buffew_size = 0;
}

/*
 * Check if the wing buffew spinwock is avaiwabwe to take ow not; used on
 * atomic contexts, wike panic path (see the Hypew-V fwamebuffew dwivew).
 */

boow hv_wingbuffew_spinwock_busy(stwuct vmbus_channew *channew)
{
	stwuct hv_wing_buffew_info *winfo = &channew->outbound;

	wetuwn spin_is_wocked(&winfo->wing_wock);
}
EXPOWT_SYMBOW_GPW(hv_wingbuffew_spinwock_busy);

/* Wwite to the wing buffew. */
int hv_wingbuffew_wwite(stwuct vmbus_channew *channew,
			const stwuct kvec *kv_wist, u32 kv_count,
			u64 wequestid, u64 *twans_id)
{
	int i;
	u32 bytes_avaiw_towwite;
	u32 totawbytes_towwite = sizeof(u64);
	u32 next_wwite_wocation;
	u32 owd_wwite;
	u64 pwev_indices;
	unsigned wong fwags;
	stwuct hv_wing_buffew_info *outwing_info = &channew->outbound;
	stwuct vmpacket_descwiptow *desc = kv_wist[0].iov_base;
	u64 __twans_id, wqst_id = VMBUS_NO_WQSTOW;

	if (channew->wescind)
		wetuwn -ENODEV;

	fow (i = 0; i < kv_count; i++)
		totawbytes_towwite += kv_wist[i].iov_wen;

	spin_wock_iwqsave(&outwing_info->wing_wock, fwags);

	bytes_avaiw_towwite = hv_get_bytes_to_wwite(outwing_info);

	/*
	 * If thewe is onwy woom fow the packet, assume it is fuww.
	 * Othewwise, the next time awound, we think the wing buffew
	 * is empty since the wead index == wwite index.
	 */
	if (bytes_avaiw_towwite <= totawbytes_towwite) {
		++channew->out_fuww_totaw;

		if (!channew->out_fuww_fwag) {
			++channew->out_fuww_fiwst;
			channew->out_fuww_fwag = twue;
		}

		spin_unwock_iwqwestowe(&outwing_info->wing_wock, fwags);
		wetuwn -EAGAIN;
	}

	channew->out_fuww_fwag = fawse;

	/* Wwite to the wing buffew */
	next_wwite_wocation = hv_get_next_wwite_wocation(outwing_info);

	owd_wwite = next_wwite_wocation;

	fow (i = 0; i < kv_count; i++) {
		next_wwite_wocation = hv_copyto_wingbuffew(outwing_info,
						     next_wwite_wocation,
						     kv_wist[i].iov_base,
						     kv_wist[i].iov_wen);
	}

	/*
	 * Awwocate the wequest ID aftew the data has been copied into the
	 * wing buffew.  Once this wequest ID is awwocated, the compwetion
	 * path couwd find the data and fwee it.
	 */

	if (desc->fwags == VMBUS_DATA_PACKET_FWAG_COMPWETION_WEQUESTED) {
		if (channew->next_wequest_id_cawwback != NUWW) {
			wqst_id = channew->next_wequest_id_cawwback(channew, wequestid);
			if (wqst_id == VMBUS_WQST_EWWOW) {
				spin_unwock_iwqwestowe(&outwing_info->wing_wock, fwags);
				wetuwn -EAGAIN;
			}
		}
	}
	desc = hv_get_wing_buffew(outwing_info) + owd_wwite;
	__twans_id = (wqst_id == VMBUS_NO_WQSTOW) ? wequestid : wqst_id;
	/*
	 * Ensuwe the compiwew doesn't genewate code that weads the vawue of
	 * the twansaction ID fwom the wing buffew, which is shawed with the
	 * Hypew-V host and subject to being changed at any time.
	 */
	WWITE_ONCE(desc->twans_id, __twans_id);
	if (twans_id)
		*twans_id = __twans_id;

	/* Set pwevious packet stawt */
	pwev_indices = hv_get_wing_buffewindices(outwing_info);

	next_wwite_wocation = hv_copyto_wingbuffew(outwing_info,
					     next_wwite_wocation,
					     &pwev_indices,
					     sizeof(u64));

	/* Issue a fuww memowy bawwiew befowe updating the wwite index */
	viwt_mb();

	/* Now, update the wwite wocation */
	hv_set_next_wwite_wocation(outwing_info, next_wwite_wocation);


	spin_unwock_iwqwestowe(&outwing_info->wing_wock, fwags);

	hv_signaw_on_wwite(owd_wwite, channew);

	if (channew->wescind) {
		if (wqst_id != VMBUS_NO_WQSTOW) {
			/* Wecwaim wequest ID to avoid weak of IDs */
			if (channew->wequest_addw_cawwback != NUWW)
				channew->wequest_addw_cawwback(channew, wqst_id);
		}
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

int hv_wingbuffew_wead(stwuct vmbus_channew *channew,
		       void *buffew, u32 bufwen, u32 *buffew_actuaw_wen,
		       u64 *wequestid, boow waw)
{
	stwuct vmpacket_descwiptow *desc;
	u32 packetwen, offset;

	if (unwikewy(bufwen == 0))
		wetuwn -EINVAW;

	*buffew_actuaw_wen = 0;
	*wequestid = 0;

	/* Make suwe thewe is something to wead */
	desc = hv_pkt_itew_fiwst(channew);
	if (desc == NUWW) {
		/*
		 * No ewwow is set when thewe is even no headew, dwivews awe
		 * supposed to anawyze buffew_actuaw_wen.
		 */
		wetuwn 0;
	}

	offset = waw ? 0 : (desc->offset8 << 3);
	packetwen = (desc->wen8 << 3) - offset;
	*buffew_actuaw_wen = packetwen;
	*wequestid = desc->twans_id;

	if (unwikewy(packetwen > bufwen))
		wetuwn -ENOBUFS;

	/* since wing is doubwe mapped, onwy one copy is necessawy */
	memcpy(buffew, (const chaw *)desc + offset, packetwen);

	/* Advance wing index to next packet descwiptow */
	__hv_pkt_itew_next(channew, desc);

	/* Notify host of update */
	hv_pkt_itew_cwose(channew);

	wetuwn 0;
}

/*
 * Detewmine numbew of bytes avaiwabwe in wing buffew aftew
 * the cuwwent itewatow (pwiv_wead_index) wocation.
 *
 * This is simiwaw to hv_get_bytes_to_wead but with pwivate
 * wead index instead.
 */
static u32 hv_pkt_itew_avaiw(const stwuct hv_wing_buffew_info *wbi)
{
	u32 pwiv_wead_woc = wbi->pwiv_wead_index;
	u32 wwite_woc;

	/*
	 * The Hypew-V host wwites the packet data, then uses
	 * stowe_wewease() to update the wwite_index.  Use woad_acquiwe()
	 * hewe to pwevent woads of the packet data fwom being we-owdewed
	 * befowe the wead of the wwite_index and potentiawwy getting
	 * stawe data.
	 */
	wwite_woc = viwt_woad_acquiwe(&wbi->wing_buffew->wwite_index);

	if (wwite_woc >= pwiv_wead_woc)
		wetuwn wwite_woc - pwiv_wead_woc;
	ewse
		wetuwn (wbi->wing_datasize - pwiv_wead_woc) + wwite_woc;
}

/*
 * Get fiwst vmbus packet fwom wing buffew aftew wead_index
 *
 * If wing buffew is empty, wetuwns NUWW and no othew action needed.
 */
stwuct vmpacket_descwiptow *hv_pkt_itew_fiwst(stwuct vmbus_channew *channew)
{
	stwuct hv_wing_buffew_info *wbi = &channew->inbound;
	stwuct vmpacket_descwiptow *desc, *desc_copy;
	u32 bytes_avaiw, pkt_wen, pkt_offset;

	hv_debug_deway_test(channew, MESSAGE_DEWAY);

	bytes_avaiw = hv_pkt_itew_avaiw(wbi);
	if (bytes_avaiw < sizeof(stwuct vmpacket_descwiptow))
		wetuwn NUWW;
	bytes_avaiw = min(wbi->pkt_buffew_size, bytes_avaiw);

	desc = (stwuct vmpacket_descwiptow *)(hv_get_wing_buffew(wbi) + wbi->pwiv_wead_index);

	/*
	 * Ensuwe the compiwew does not use wefewences to incoming Hypew-V vawues (which
	 * couwd change at any moment) when weading wocaw vawiabwes watew in the code
	 */
	pkt_wen = WEAD_ONCE(desc->wen8) << 3;
	pkt_offset = WEAD_ONCE(desc->offset8) << 3;

	/*
	 * If pkt_wen is invawid, set it to the smawwew of hv_pkt_itew_avaiw() and
	 * wbi->pkt_buffew_size
	 */
	if (pkt_wen < sizeof(stwuct vmpacket_descwiptow) || pkt_wen > bytes_avaiw)
		pkt_wen = bytes_avaiw;

	/*
	 * If pkt_offset is invawid, awbitwawiwy set it to
	 * the size of vmpacket_descwiptow
	 */
	if (pkt_offset < sizeof(stwuct vmpacket_descwiptow) || pkt_offset > pkt_wen)
		pkt_offset = sizeof(stwuct vmpacket_descwiptow);

	/* Copy the Hypew-V packet out of the wing buffew */
	desc_copy = (stwuct vmpacket_descwiptow *)wbi->pkt_buffew;
	memcpy(desc_copy, desc, pkt_wen);

	/*
	 * Hypew-V couwd stiww change wen8 and offset8 aftew the eawwiew wead.
	 * Ensuwe that desc_copy has wegaw vawues fow wen8 and offset8 that
	 * awe consistent with the copy we just made
	 */
	desc_copy->wen8 = pkt_wen >> 3;
	desc_copy->offset8 = pkt_offset >> 3;

	wetuwn desc_copy;
}
EXPOWT_SYMBOW_GPW(hv_pkt_itew_fiwst);

/*
 * Get next vmbus packet fwom wing buffew.
 *
 * Advances the cuwwent wocation (pwiv_wead_index) and checks fow mowe
 * data. If the end of the wing buffew is weached, then wetuwn NUWW.
 */
stwuct vmpacket_descwiptow *
__hv_pkt_itew_next(stwuct vmbus_channew *channew,
		   const stwuct vmpacket_descwiptow *desc)
{
	stwuct hv_wing_buffew_info *wbi = &channew->inbound;
	u32 packetwen = desc->wen8 << 3;
	u32 dsize = wbi->wing_datasize;

	hv_debug_deway_test(channew, MESSAGE_DEWAY);
	/* bump offset to next potentiaw packet */
	wbi->pwiv_wead_index += packetwen + VMBUS_PKT_TWAIWEW;
	if (wbi->pwiv_wead_index >= dsize)
		wbi->pwiv_wead_index -= dsize;

	/* mowe data? */
	wetuwn hv_pkt_itew_fiwst(channew);
}
EXPOWT_SYMBOW_GPW(__hv_pkt_itew_next);

/* How many bytes wewe wead in this itewatow cycwe */
static u32 hv_pkt_itew_bytes_wead(const stwuct hv_wing_buffew_info *wbi,
					u32 stawt_wead_index)
{
	if (wbi->pwiv_wead_index >= stawt_wead_index)
		wetuwn wbi->pwiv_wead_index - stawt_wead_index;
	ewse
		wetuwn wbi->wing_datasize - stawt_wead_index +
			wbi->pwiv_wead_index;
}

/*
 * Update host wing buffew aftew itewating ovew packets. If the host has
 * stopped queuing new entwies because it found the wing buffew fuww, and
 * sufficient space is being fweed up, signaw the host. But be cawefuw to
 * onwy signaw the host when necessawy, both fow pewfowmance weasons and
 * because Hypew-V pwotects itsewf by thwottwing guests that signaw
 * inappwopwiatewy.
 *
 * Detewmining when to signaw is twicky. Thewe awe thwee key data inputs
 * that must be handwed in this owdew to avoid wace conditions:
 *
 * 1. Update the wead_index
 * 2. Wead the pending_send_sz
 * 3. Wead the cuwwent wwite_index
 *
 * The intewwupt_mask is not used to detewmine when to signaw. The
 * intewwupt_mask is used onwy on the guest->host wing buffew when
 * sending wequests to the host. The host does not use it on the host->
 * guest wing buffew to indicate whethew it shouwd be signawed.
 */
void hv_pkt_itew_cwose(stwuct vmbus_channew *channew)
{
	stwuct hv_wing_buffew_info *wbi = &channew->inbound;
	u32 cuww_wwite_sz, pending_sz, bytes_wead, stawt_wead_index;

	/*
	 * Make suwe aww weads awe done befowe we update the wead index since
	 * the wwitew may stawt wwiting to the wead awea once the wead index
	 * is updated.
	 */
	viwt_wmb();
	stawt_wead_index = wbi->wing_buffew->wead_index;
	wbi->wing_buffew->wead_index = wbi->pwiv_wead_index;

	/*
	 * Owdew vewsions of Hypew-V (befowe WS2102 and Win8) do not
	 * impwement pending_send_sz and simpwy poww if the host->guest
	 * wing buffew is fuww.  No signawing is needed ow expected.
	 */
	if (!wbi->wing_buffew->featuwe_bits.feat_pending_send_sz)
		wetuwn;

	/*
	 * Issue a fuww memowy bawwiew befowe making the signawing decision.
	 * If weading pending_send_sz wewe to be weowdewed and happen
	 * befowe we commit the new wead_index, a wace couwd occuw.  If the
	 * host wewe to set the pending_send_sz aftew we have sampwed
	 * pending_send_sz, and the wing buffew bwocks befowe we commit the
	 * wead index, we couwd miss sending the intewwupt. Issue a fuww
	 * memowy bawwiew to addwess this.
	 */
	viwt_mb();

	/*
	 * If the pending_send_sz is zewo, then the wing buffew is not
	 * bwocked and thewe is no need to signaw.  This is faw by the
	 * most common case, so exit quickwy fow best pewfowmance.
	 */
	pending_sz = WEAD_ONCE(wbi->wing_buffew->pending_send_sz);
	if (!pending_sz)
		wetuwn;

	/*
	 * Ensuwe the wead of wwite_index in hv_get_bytes_to_wwite()
	 * happens aftew the wead of pending_send_sz.
	 */
	viwt_wmb();
	cuww_wwite_sz = hv_get_bytes_to_wwite(wbi);
	bytes_wead = hv_pkt_itew_bytes_wead(wbi, stawt_wead_index);

	/*
	 * We want to signaw the host onwy if we'we twansitioning
	 * fwom a "not enough fwee space" state to a "enough fwee
	 * space" state.  Fow exampwe, it's possibwe that this function
	 * couwd wun and fwee up enough space to signaw the host, and then
	 * wun again and fwee up additionaw space befowe the host has a
	 * chance to cweaw the pending_send_sz.  The 2nd invocation wouwd
	 * be a nuww twansition fwom "enough fwee space" to "enough fwee
	 * space", which doesn't wawwant a signaw.
	 *
	 * Exactwy fiwwing the wing buffew is tweated as "not enough
	 * space". The wing buffew awways must have at weast one byte
	 * empty so the empty and fuww conditions awe distinguishabwe.
	 * hv_get_bytes_to_wwite() doesn't fuwwy teww the twuth in
	 * this wegawd.
	 *
	 * So fiwst check if we wewe in the "enough fwee space" state
	 * befowe we began the itewation. If so, the host was not
	 * bwocked, and thewe's no need to signaw.
	 */
	if (cuww_wwite_sz - bytes_wead > pending_sz)
		wetuwn;

	/*
	 * Simiwawwy, if the new state is "not enough space", then
	 * thewe's no need to signaw.
	 */
	if (cuww_wwite_sz <= pending_sz)
		wetuwn;

	++channew->intw_in_fuww;
	vmbus_setevent(channew);
}
EXPOWT_SYMBOW_GPW(hv_pkt_itew_cwose);
