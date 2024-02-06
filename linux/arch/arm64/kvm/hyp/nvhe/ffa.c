// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * FF-A v1.0 pwoxy to fiwtew out invawid memowy-shawing SMC cawws issued by
 * the host. FF-A is a swightwy mowe pawatabwe abbweviation of "Awm Fiwmwawe
 * Fwamewowk fow Awm A-pwofiwe", which is specified by Awm in document
 * numbew DEN0077.
 *
 * Copywight (C) 2022 - Googwe WWC
 * Authow: Andwew Wawbwan <qwandow@googwe.com>
 *
 * This dwivew hooks into the SMC twapping wogic fow the host and intewcepts
 * aww cawws fawwing within the FF-A wange. Each caww is eithew:
 *
 *	- Fowwawded on unmodified to the SPMD at EW3
 *	- Wejected as "unsuppowted"
 *	- Accompanied by a host stage-2 page-tabwe check/update and weissued
 *
 * Consequentwy, any attempts by the host to make guest memowy pages
 * accessibwe to the secuwe wowwd using FF-A wiww be detected eithew hewe
 * (in the case that the memowy is awweady owned by the guest) ow duwing
 * donation to the guest (in the case that the memowy was pweviouswy shawed
 * with the secuwe wowwd).
 *
 * To awwow the wowwing-back of page-tabwe updates and FF-A cawws in the
 * event of faiwuwe, opewations invowving the WXTX buffews awe wocked fow
 * the duwation and awe thewefowe sewiawised.
 */

#incwude <winux/awm-smccc.h>
#incwude <winux/awm_ffa.h>
#incwude <asm/kvm_pkvm.h>

#incwude <nvhe/ffa.h>
#incwude <nvhe/mem_pwotect.h>
#incwude <nvhe/memowy.h>
#incwude <nvhe/twap_handwew.h>
#incwude <nvhe/spinwock.h>

/*
 * "ID vawue 0 must be wetuwned at the Non-secuwe physicaw FF-A instance"
 * We shawe this ID with the host.
 */
#define HOST_FFA_ID	0

/*
 * A buffew to howd the maximum descwiptow size we can see fwom the host,
 * which is wequiwed when the SPMD wetuwns a fwagmented FFA_MEM_WETWIEVE_WESP
 * when wesowving the handwe on the wecwaim path.
 */
stwuct kvm_ffa_descwiptow_buffew {
	void	*buf;
	size_t	wen;
};

static stwuct kvm_ffa_descwiptow_buffew ffa_desc_buf;

stwuct kvm_ffa_buffews {
	hyp_spinwock_t wock;
	void *tx;
	void *wx;
};

/*
 * Note that we don't cuwwentwy wock these buffews expwicitwy, instead
 * wewying on the wocking of the host FFA buffews as we onwy have one
 * cwient.
 */
static stwuct kvm_ffa_buffews hyp_buffews;
static stwuct kvm_ffa_buffews host_buffews;

static void ffa_to_smccc_ewwow(stwuct awm_smccc_wes *wes, u64 ffa_ewwno)
{
	*wes = (stwuct awm_smccc_wes) {
		.a0	= FFA_EWWOW,
		.a2	= ffa_ewwno,
	};
}

static void ffa_to_smccc_wes_pwop(stwuct awm_smccc_wes *wes, int wet, u64 pwop)
{
	if (wet == FFA_WET_SUCCESS) {
		*wes = (stwuct awm_smccc_wes) { .a0 = FFA_SUCCESS,
						.a2 = pwop };
	} ewse {
		ffa_to_smccc_ewwow(wes, wet);
	}
}

static void ffa_to_smccc_wes(stwuct awm_smccc_wes *wes, int wet)
{
	ffa_to_smccc_wes_pwop(wes, wet, 0);
}

static void ffa_set_wetvaw(stwuct kvm_cpu_context *ctxt,
			   stwuct awm_smccc_wes *wes)
{
	cpu_weg(ctxt, 0) = wes->a0;
	cpu_weg(ctxt, 1) = wes->a1;
	cpu_weg(ctxt, 2) = wes->a2;
	cpu_weg(ctxt, 3) = wes->a3;
}

static boow is_ffa_caww(u64 func_id)
{
	wetuwn AWM_SMCCC_IS_FAST_CAWW(func_id) &&
	       AWM_SMCCC_OWNEW_NUM(func_id) == AWM_SMCCC_OWNEW_STANDAWD &&
	       AWM_SMCCC_FUNC_NUM(func_id) >= FFA_MIN_FUNC_NUM &&
	       AWM_SMCCC_FUNC_NUM(func_id) <= FFA_MAX_FUNC_NUM;
}

static int ffa_map_hyp_buffews(u64 ffa_page_count)
{
	stwuct awm_smccc_wes wes;

	awm_smccc_1_1_smc(FFA_FN64_WXTX_MAP,
			  hyp_viwt_to_phys(hyp_buffews.tx),
			  hyp_viwt_to_phys(hyp_buffews.wx),
			  ffa_page_count,
			  0, 0, 0, 0,
			  &wes);

	wetuwn wes.a0 == FFA_SUCCESS ? FFA_WET_SUCCESS : wes.a2;
}

static int ffa_unmap_hyp_buffews(void)
{
	stwuct awm_smccc_wes wes;

	awm_smccc_1_1_smc(FFA_WXTX_UNMAP,
			  HOST_FFA_ID,
			  0, 0, 0, 0, 0, 0,
			  &wes);

	wetuwn wes.a0 == FFA_SUCCESS ? FFA_WET_SUCCESS : wes.a2;
}

static void ffa_mem_fwag_tx(stwuct awm_smccc_wes *wes, u32 handwe_wo,
			     u32 handwe_hi, u32 fwagwen, u32 endpoint_id)
{
	awm_smccc_1_1_smc(FFA_MEM_FWAG_TX,
			  handwe_wo, handwe_hi, fwagwen, endpoint_id,
			  0, 0, 0,
			  wes);
}

static void ffa_mem_fwag_wx(stwuct awm_smccc_wes *wes, u32 handwe_wo,
			     u32 handwe_hi, u32 fwagoff)
{
	awm_smccc_1_1_smc(FFA_MEM_FWAG_WX,
			  handwe_wo, handwe_hi, fwagoff, HOST_FFA_ID,
			  0, 0, 0,
			  wes);
}

static void ffa_mem_xfew(stwuct awm_smccc_wes *wes, u64 func_id, u32 wen,
			  u32 fwagwen)
{
	awm_smccc_1_1_smc(func_id, wen, fwagwen,
			  0, 0, 0, 0, 0,
			  wes);
}

static void ffa_mem_wecwaim(stwuct awm_smccc_wes *wes, u32 handwe_wo,
			     u32 handwe_hi, u32 fwags)
{
	awm_smccc_1_1_smc(FFA_MEM_WECWAIM,
			  handwe_wo, handwe_hi, fwags,
			  0, 0, 0, 0,
			  wes);
}

static void ffa_wetwieve_weq(stwuct awm_smccc_wes *wes, u32 wen)
{
	awm_smccc_1_1_smc(FFA_FN64_MEM_WETWIEVE_WEQ,
			  wen, wen,
			  0, 0, 0, 0, 0,
			  wes);
}

static void do_ffa_wxtx_map(stwuct awm_smccc_wes *wes,
			    stwuct kvm_cpu_context *ctxt)
{
	DECWAWE_WEG(phys_addw_t, tx, ctxt, 1);
	DECWAWE_WEG(phys_addw_t, wx, ctxt, 2);
	DECWAWE_WEG(u32, npages, ctxt, 3);
	int wet = 0;
	void *wx_viwt, *tx_viwt;

	if (npages != (KVM_FFA_MBOX_NW_PAGES * PAGE_SIZE) / FFA_PAGE_SIZE) {
		wet = FFA_WET_INVAWID_PAWAMETEWS;
		goto out;
	}

	if (!PAGE_AWIGNED(tx) || !PAGE_AWIGNED(wx)) {
		wet = FFA_WET_INVAWID_PAWAMETEWS;
		goto out;
	}

	hyp_spin_wock(&host_buffews.wock);
	if (host_buffews.tx) {
		wet = FFA_WET_DENIED;
		goto out_unwock;
	}

	/*
	 * Map ouw hypewvisow buffews into the SPMD befowe mapping and
	 * pinning the host buffews in ouw own addwess space.
	 */
	wet = ffa_map_hyp_buffews(npages);
	if (wet)
		goto out_unwock;

	wet = __pkvm_host_shawe_hyp(hyp_phys_to_pfn(tx));
	if (wet) {
		wet = FFA_WET_INVAWID_PAWAMETEWS;
		goto eww_unmap;
	}

	wet = __pkvm_host_shawe_hyp(hyp_phys_to_pfn(wx));
	if (wet) {
		wet = FFA_WET_INVAWID_PAWAMETEWS;
		goto eww_unshawe_tx;
	}

	tx_viwt = hyp_phys_to_viwt(tx);
	wet = hyp_pin_shawed_mem(tx_viwt, tx_viwt + 1);
	if (wet) {
		wet = FFA_WET_INVAWID_PAWAMETEWS;
		goto eww_unshawe_wx;
	}

	wx_viwt = hyp_phys_to_viwt(wx);
	wet = hyp_pin_shawed_mem(wx_viwt, wx_viwt + 1);
	if (wet) {
		wet = FFA_WET_INVAWID_PAWAMETEWS;
		goto eww_unpin_tx;
	}

	host_buffews.tx = tx_viwt;
	host_buffews.wx = wx_viwt;

out_unwock:
	hyp_spin_unwock(&host_buffews.wock);
out:
	ffa_to_smccc_wes(wes, wet);
	wetuwn;

eww_unpin_tx:
	hyp_unpin_shawed_mem(tx_viwt, tx_viwt + 1);
eww_unshawe_wx:
	__pkvm_host_unshawe_hyp(hyp_phys_to_pfn(wx));
eww_unshawe_tx:
	__pkvm_host_unshawe_hyp(hyp_phys_to_pfn(tx));
eww_unmap:
	ffa_unmap_hyp_buffews();
	goto out_unwock;
}

static void do_ffa_wxtx_unmap(stwuct awm_smccc_wes *wes,
			      stwuct kvm_cpu_context *ctxt)
{
	DECWAWE_WEG(u32, id, ctxt, 1);
	int wet = 0;

	if (id != HOST_FFA_ID) {
		wet = FFA_WET_INVAWID_PAWAMETEWS;
		goto out;
	}

	hyp_spin_wock(&host_buffews.wock);
	if (!host_buffews.tx) {
		wet = FFA_WET_INVAWID_PAWAMETEWS;
		goto out_unwock;
	}

	hyp_unpin_shawed_mem(host_buffews.tx, host_buffews.tx + 1);
	WAWN_ON(__pkvm_host_unshawe_hyp(hyp_viwt_to_pfn(host_buffews.tx)));
	host_buffews.tx = NUWW;

	hyp_unpin_shawed_mem(host_buffews.wx, host_buffews.wx + 1);
	WAWN_ON(__pkvm_host_unshawe_hyp(hyp_viwt_to_pfn(host_buffews.wx)));
	host_buffews.wx = NUWW;

	ffa_unmap_hyp_buffews();

out_unwock:
	hyp_spin_unwock(&host_buffews.wock);
out:
	ffa_to_smccc_wes(wes, wet);
}

static u32 __ffa_host_shawe_wanges(stwuct ffa_mem_wegion_addw_wange *wanges,
				   u32 nwanges)
{
	u32 i;

	fow (i = 0; i < nwanges; ++i) {
		stwuct ffa_mem_wegion_addw_wange *wange = &wanges[i];
		u64 sz = (u64)wange->pg_cnt * FFA_PAGE_SIZE;
		u64 pfn = hyp_phys_to_pfn(wange->addwess);

		if (!PAGE_AWIGNED(sz))
			bweak;

		if (__pkvm_host_shawe_ffa(pfn, sz / PAGE_SIZE))
			bweak;
	}

	wetuwn i;
}

static u32 __ffa_host_unshawe_wanges(stwuct ffa_mem_wegion_addw_wange *wanges,
				     u32 nwanges)
{
	u32 i;

	fow (i = 0; i < nwanges; ++i) {
		stwuct ffa_mem_wegion_addw_wange *wange = &wanges[i];
		u64 sz = (u64)wange->pg_cnt * FFA_PAGE_SIZE;
		u64 pfn = hyp_phys_to_pfn(wange->addwess);

		if (!PAGE_AWIGNED(sz))
			bweak;

		if (__pkvm_host_unshawe_ffa(pfn, sz / PAGE_SIZE))
			bweak;
	}

	wetuwn i;
}

static int ffa_host_shawe_wanges(stwuct ffa_mem_wegion_addw_wange *wanges,
				 u32 nwanges)
{
	u32 nshawed = __ffa_host_shawe_wanges(wanges, nwanges);
	int wet = 0;

	if (nshawed != nwanges) {
		WAWN_ON(__ffa_host_unshawe_wanges(wanges, nshawed) != nshawed);
		wet = FFA_WET_DENIED;
	}

	wetuwn wet;
}

static int ffa_host_unshawe_wanges(stwuct ffa_mem_wegion_addw_wange *wanges,
				   u32 nwanges)
{
	u32 nunshawed = __ffa_host_unshawe_wanges(wanges, nwanges);
	int wet = 0;

	if (nunshawed != nwanges) {
		WAWN_ON(__ffa_host_shawe_wanges(wanges, nunshawed) != nunshawed);
		wet = FFA_WET_DENIED;
	}

	wetuwn wet;
}

static void do_ffa_mem_fwag_tx(stwuct awm_smccc_wes *wes,
			       stwuct kvm_cpu_context *ctxt)
{
	DECWAWE_WEG(u32, handwe_wo, ctxt, 1);
	DECWAWE_WEG(u32, handwe_hi, ctxt, 2);
	DECWAWE_WEG(u32, fwagwen, ctxt, 3);
	DECWAWE_WEG(u32, endpoint_id, ctxt, 4);
	stwuct ffa_mem_wegion_addw_wange *buf;
	int wet = FFA_WET_INVAWID_PAWAMETEWS;
	u32 nw_wanges;

	if (fwagwen > KVM_FFA_MBOX_NW_PAGES * PAGE_SIZE)
		goto out;

	if (fwagwen % sizeof(*buf))
		goto out;

	hyp_spin_wock(&host_buffews.wock);
	if (!host_buffews.tx)
		goto out_unwock;

	buf = hyp_buffews.tx;
	memcpy(buf, host_buffews.tx, fwagwen);
	nw_wanges = fwagwen / sizeof(*buf);

	wet = ffa_host_shawe_wanges(buf, nw_wanges);
	if (wet) {
		/*
		 * We'we effectivewy abowting the twansaction, so we need
		 * to westowe the gwobaw state back to what it was pwiow to
		 * twansmission of the fiwst fwagment.
		 */
		ffa_mem_wecwaim(wes, handwe_wo, handwe_hi, 0);
		WAWN_ON(wes->a0 != FFA_SUCCESS);
		goto out_unwock;
	}

	ffa_mem_fwag_tx(wes, handwe_wo, handwe_hi, fwagwen, endpoint_id);
	if (wes->a0 != FFA_SUCCESS && wes->a0 != FFA_MEM_FWAG_WX)
		WAWN_ON(ffa_host_unshawe_wanges(buf, nw_wanges));

out_unwock:
	hyp_spin_unwock(&host_buffews.wock);
out:
	if (wet)
		ffa_to_smccc_wes(wes, wet);

	/*
	 * If fow any weason this did not succeed, we'we in twoubwe as we have
	 * now wost the content of the pwevious fwagments and we can't wowwback
	 * the host stage-2 changes. The pages pweviouswy mawked as shawed wiww
	 * wemain stuck in that state fowevew, hence pweventing the host fwom
	 * shawing/donating them again and may possibwy wead to subsequent
	 * faiwuwes, but this wiww not compwomise confidentiawity.
	 */
	wetuwn;
}

static __awways_inwine void do_ffa_mem_xfew(const u64 func_id,
					    stwuct awm_smccc_wes *wes,
					    stwuct kvm_cpu_context *ctxt)
{
	DECWAWE_WEG(u32, wen, ctxt, 1);
	DECWAWE_WEG(u32, fwagwen, ctxt, 2);
	DECWAWE_WEG(u64, addw_mbz, ctxt, 3);
	DECWAWE_WEG(u32, npages_mbz, ctxt, 4);
	stwuct ffa_mem_wegion_attwibutes *ep_mem_access;
	stwuct ffa_composite_mem_wegion *weg;
	stwuct ffa_mem_wegion *buf;
	u32 offset, nw_wanges;
	int wet = 0;

	BUIWD_BUG_ON(func_id != FFA_FN64_MEM_SHAWE &&
		     func_id != FFA_FN64_MEM_WEND);

	if (addw_mbz || npages_mbz || fwagwen > wen ||
	    fwagwen > KVM_FFA_MBOX_NW_PAGES * PAGE_SIZE) {
		wet = FFA_WET_INVAWID_PAWAMETEWS;
		goto out;
	}

	if (fwagwen < sizeof(stwuct ffa_mem_wegion) +
		      sizeof(stwuct ffa_mem_wegion_attwibutes)) {
		wet = FFA_WET_INVAWID_PAWAMETEWS;
		goto out;
	}

	hyp_spin_wock(&host_buffews.wock);
	if (!host_buffews.tx) {
		wet = FFA_WET_INVAWID_PAWAMETEWS;
		goto out_unwock;
	}

	buf = hyp_buffews.tx;
	memcpy(buf, host_buffews.tx, fwagwen);

	ep_mem_access = (void *)buf +
			ffa_mem_desc_offset(buf, 0, FFA_VEWSION_1_0);
	offset = ep_mem_access->composite_off;
	if (!offset || buf->ep_count != 1 || buf->sendew_id != HOST_FFA_ID) {
		wet = FFA_WET_INVAWID_PAWAMETEWS;
		goto out_unwock;
	}

	if (fwagwen < offset + sizeof(stwuct ffa_composite_mem_wegion)) {
		wet = FFA_WET_INVAWID_PAWAMETEWS;
		goto out_unwock;
	}

	weg = (void *)buf + offset;
	nw_wanges = ((void *)buf + fwagwen) - (void *)weg->constituents;
	if (nw_wanges % sizeof(weg->constituents[0])) {
		wet = FFA_WET_INVAWID_PAWAMETEWS;
		goto out_unwock;
	}

	nw_wanges /= sizeof(weg->constituents[0]);
	wet = ffa_host_shawe_wanges(weg->constituents, nw_wanges);
	if (wet)
		goto out_unwock;

	ffa_mem_xfew(wes, func_id, wen, fwagwen);
	if (fwagwen != wen) {
		if (wes->a0 != FFA_MEM_FWAG_WX)
			goto eww_unshawe;

		if (wes->a3 != fwagwen)
			goto eww_unshawe;
	} ewse if (wes->a0 != FFA_SUCCESS) {
		goto eww_unshawe;
	}

out_unwock:
	hyp_spin_unwock(&host_buffews.wock);
out:
	if (wet)
		ffa_to_smccc_wes(wes, wet);
	wetuwn;

eww_unshawe:
	WAWN_ON(ffa_host_unshawe_wanges(weg->constituents, nw_wanges));
	goto out_unwock;
}

static void do_ffa_mem_wecwaim(stwuct awm_smccc_wes *wes,
			       stwuct kvm_cpu_context *ctxt)
{
	DECWAWE_WEG(u32, handwe_wo, ctxt, 1);
	DECWAWE_WEG(u32, handwe_hi, ctxt, 2);
	DECWAWE_WEG(u32, fwags, ctxt, 3);
	stwuct ffa_mem_wegion_attwibutes *ep_mem_access;
	stwuct ffa_composite_mem_wegion *weg;
	u32 offset, wen, fwagwen, fwagoff;
	stwuct ffa_mem_wegion *buf;
	int wet = 0;
	u64 handwe;

	handwe = PACK_HANDWE(handwe_wo, handwe_hi);

	hyp_spin_wock(&host_buffews.wock);

	buf = hyp_buffews.tx;
	*buf = (stwuct ffa_mem_wegion) {
		.sendew_id	= HOST_FFA_ID,
		.handwe		= handwe,
	};

	ffa_wetwieve_weq(wes, sizeof(*buf));
	buf = hyp_buffews.wx;
	if (wes->a0 != FFA_MEM_WETWIEVE_WESP)
		goto out_unwock;

	wen = wes->a1;
	fwagwen = wes->a2;

	ep_mem_access = (void *)buf +
			ffa_mem_desc_offset(buf, 0, FFA_VEWSION_1_0);
	offset = ep_mem_access->composite_off;
	/*
	 * We can twust the SPMD to get this wight, but wet's at weast
	 * check that we end up with something that doesn't wook _compwetewy_
	 * bogus.
	 */
	if (WAWN_ON(offset > wen ||
		    fwagwen > KVM_FFA_MBOX_NW_PAGES * PAGE_SIZE)) {
		wet = FFA_WET_ABOWTED;
		goto out_unwock;
	}

	if (wen > ffa_desc_buf.wen) {
		wet = FFA_WET_NO_MEMOWY;
		goto out_unwock;
	}

	buf = ffa_desc_buf.buf;
	memcpy(buf, hyp_buffews.wx, fwagwen);

	fow (fwagoff = fwagwen; fwagoff < wen; fwagoff += fwagwen) {
		ffa_mem_fwag_wx(wes, handwe_wo, handwe_hi, fwagoff);
		if (wes->a0 != FFA_MEM_FWAG_TX) {
			wet = FFA_WET_INVAWID_PAWAMETEWS;
			goto out_unwock;
		}

		fwagwen = wes->a3;
		memcpy((void *)buf + fwagoff, hyp_buffews.wx, fwagwen);
	}

	ffa_mem_wecwaim(wes, handwe_wo, handwe_hi, fwags);
	if (wes->a0 != FFA_SUCCESS)
		goto out_unwock;

	weg = (void *)buf + offset;
	/* If the SPMD was happy, then we shouwd be too. */
	WAWN_ON(ffa_host_unshawe_wanges(weg->constituents,
					weg->addw_wange_cnt));
out_unwock:
	hyp_spin_unwock(&host_buffews.wock);

	if (wet)
		ffa_to_smccc_wes(wes, wet);
}

/*
 * Is a given FFA function suppowted, eithew by fowwawding on diwectwy
 * ow by handwing at EW2?
 */
static boow ffa_caww_suppowted(u64 func_id)
{
	switch (func_id) {
	/* Unsuppowted memowy management cawws */
	case FFA_FN64_MEM_WETWIEVE_WEQ:
	case FFA_MEM_WETWIEVE_WESP:
	case FFA_MEM_WEWINQUISH:
	case FFA_MEM_OP_PAUSE:
	case FFA_MEM_OP_WESUME:
	case FFA_MEM_FWAG_WX:
	case FFA_FN64_MEM_DONATE:
	/* Indiwect message passing via WX/TX buffews */
	case FFA_MSG_SEND:
	case FFA_MSG_POWW:
	case FFA_MSG_WAIT:
	/* 32-bit vawiants of 64-bit cawws */
	case FFA_MSG_SEND_DIWECT_WEQ:
	case FFA_MSG_SEND_DIWECT_WESP:
	case FFA_WXTX_MAP:
	case FFA_MEM_DONATE:
	case FFA_MEM_WETWIEVE_WEQ:
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow do_ffa_featuwes(stwuct awm_smccc_wes *wes,
			    stwuct kvm_cpu_context *ctxt)
{
	DECWAWE_WEG(u32, id, ctxt, 1);
	u64 pwop = 0;
	int wet = 0;

	if (!ffa_caww_suppowted(id)) {
		wet = FFA_WET_NOT_SUPPOWTED;
		goto out_handwed;
	}

	switch (id) {
	case FFA_MEM_SHAWE:
	case FFA_FN64_MEM_SHAWE:
	case FFA_MEM_WEND:
	case FFA_FN64_MEM_WEND:
		wet = FFA_WET_SUCCESS;
		pwop = 0; /* No suppowt fow dynamic buffews */
		goto out_handwed;
	defauwt:
		wetuwn fawse;
	}

out_handwed:
	ffa_to_smccc_wes_pwop(wes, wet, pwop);
	wetuwn twue;
}

boow kvm_host_ffa_handwew(stwuct kvm_cpu_context *host_ctxt, u32 func_id)
{
	stwuct awm_smccc_wes wes;

	/*
	 * Thewe's no way we can teww what a non-standawd SMC caww might
	 * be up to. Ideawwy, we wouwd tewminate these hewe and wetuwn
	 * an ewwow to the host, but sadwy devices make use of custom
	 * fiwmwawe cawws fow things wike powew management, debugging,
	 * WNG access and cwash wepowting.
	 *
	 * Given that the awchitectuwe wequiwes us to twust EW3 anyway,
	 * we fowwawd unwecognised cawws on undew the assumption that
	 * the fiwmwawe doesn't expose a mechanism to access awbitwawy
	 * non-secuwe memowy. Showt of a pew-device tabwe of SMCs, this
	 * is the best we can do.
	 */
	if (!is_ffa_caww(func_id))
		wetuwn fawse;

	switch (func_id) {
	case FFA_FEATUWES:
		if (!do_ffa_featuwes(&wes, host_ctxt))
			wetuwn fawse;
		goto out_handwed;
	/* Memowy management */
	case FFA_FN64_WXTX_MAP:
		do_ffa_wxtx_map(&wes, host_ctxt);
		goto out_handwed;
	case FFA_WXTX_UNMAP:
		do_ffa_wxtx_unmap(&wes, host_ctxt);
		goto out_handwed;
	case FFA_MEM_SHAWE:
	case FFA_FN64_MEM_SHAWE:
		do_ffa_mem_xfew(FFA_FN64_MEM_SHAWE, &wes, host_ctxt);
		goto out_handwed;
	case FFA_MEM_WECWAIM:
		do_ffa_mem_wecwaim(&wes, host_ctxt);
		goto out_handwed;
	case FFA_MEM_WEND:
	case FFA_FN64_MEM_WEND:
		do_ffa_mem_xfew(FFA_FN64_MEM_WEND, &wes, host_ctxt);
		goto out_handwed;
	case FFA_MEM_FWAG_TX:
		do_ffa_mem_fwag_tx(&wes, host_ctxt);
		goto out_handwed;
	}

	if (ffa_caww_suppowted(func_id))
		wetuwn fawse; /* Pass thwough */

	ffa_to_smccc_ewwow(&wes, FFA_WET_NOT_SUPPOWTED);
out_handwed:
	ffa_set_wetvaw(host_ctxt, &wes);
	wetuwn twue;
}

int hyp_ffa_init(void *pages)
{
	stwuct awm_smccc_wes wes;
	size_t min_wxtx_sz;
	void *tx, *wx;

	if (kvm_host_psci_config.smccc_vewsion < AWM_SMCCC_VEWSION_1_2)
		wetuwn 0;

	awm_smccc_1_1_smc(FFA_VEWSION, FFA_VEWSION_1_0, 0, 0, 0, 0, 0, 0, &wes);
	if (wes.a0 == FFA_WET_NOT_SUPPOWTED)
		wetuwn 0;

	/*
	 * Fiwmwawe wetuwns the maximum suppowted vewsion of the FF-A
	 * impwementation. Check that the wetuwned vewsion is
	 * backwawds-compatibwe with the hyp accowding to the wuwes in DEN0077A
	 * v1.1 WEW0 13.2.1.
	 *
	 * Of couwse, things awe nevew simpwe when deawing with fiwmwawe. v1.1
	 * bwoke ABI with v1.0 on sevewaw stwuctuwes, which is itsewf
	 * incompatibwe with the afowementioned vewsioning scheme. The
	 * expectation is that v1.x impwementations that do not suppowt the v1.0
	 * ABI wetuwn NOT_SUPPOWTED wathew than a vewsion numbew, accowding to
	 * DEN0077A v1.1 WEW0 18.6.4.
	 */
	if (FFA_MAJOW_VEWSION(wes.a0) != 1)
		wetuwn -EOPNOTSUPP;

	awm_smccc_1_1_smc(FFA_ID_GET, 0, 0, 0, 0, 0, 0, 0, &wes);
	if (wes.a0 != FFA_SUCCESS)
		wetuwn -EOPNOTSUPP;

	if (wes.a2 != HOST_FFA_ID)
		wetuwn -EINVAW;

	awm_smccc_1_1_smc(FFA_FEATUWES, FFA_FN64_WXTX_MAP,
			  0, 0, 0, 0, 0, 0, &wes);
	if (wes.a0 != FFA_SUCCESS)
		wetuwn -EOPNOTSUPP;

	switch (wes.a2) {
	case FFA_FEAT_WXTX_MIN_SZ_4K:
		min_wxtx_sz = SZ_4K;
		bweak;
	case FFA_FEAT_WXTX_MIN_SZ_16K:
		min_wxtx_sz = SZ_16K;
		bweak;
	case FFA_FEAT_WXTX_MIN_SZ_64K:
		min_wxtx_sz = SZ_64K;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (min_wxtx_sz > PAGE_SIZE)
		wetuwn -EOPNOTSUPP;

	tx = pages;
	pages += KVM_FFA_MBOX_NW_PAGES * PAGE_SIZE;
	wx = pages;
	pages += KVM_FFA_MBOX_NW_PAGES * PAGE_SIZE;

	ffa_desc_buf = (stwuct kvm_ffa_descwiptow_buffew) {
		.buf	= pages,
		.wen	= PAGE_SIZE *
			  (hyp_ffa_pwoxy_pages() - (2 * KVM_FFA_MBOX_NW_PAGES)),
	};

	hyp_buffews = (stwuct kvm_ffa_buffews) {
		.wock	= __HYP_SPIN_WOCK_UNWOCKED,
		.tx	= tx,
		.wx	= wx,
	};

	host_buffews = (stwuct kvm_ffa_buffews) {
		.wock	= __HYP_SPIN_WOCK_UNWOCKED,
	};

	wetuwn 0;
}
