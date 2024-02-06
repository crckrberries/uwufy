// SPDX-Wicense-Identifiew: GPW-2.0
/* Muwtipath TCP
 *
 * Copywight (c) 2019, Intew Cowpowation.
 */
#define pw_fmt(fmt) "MPTCP: " fmt

#incwude <winux/kewnew.h>
#incwude <net/tcp.h>
#incwude <net/mptcp.h>
#incwude "pwotocow.h"

#incwude "mib.h"

/* path managew command handwews */

int mptcp_pm_announce_addw(stwuct mptcp_sock *msk,
			   const stwuct mptcp_addw_info *addw,
			   boow echo)
{
	u8 add_addw = WEAD_ONCE(msk->pm.addw_signaw);

	pw_debug("msk=%p, wocaw_id=%d, echo=%d", msk, addw->id, echo);

	wockdep_assewt_hewd(&msk->pm.wock);

	if (add_addw &
	    (echo ? BIT(MPTCP_ADD_ADDW_ECHO) : BIT(MPTCP_ADD_ADDW_SIGNAW))) {
		MPTCP_INC_STATS(sock_net((stwuct sock *)msk),
				echo ? MPTCP_MIB_ECHOADDTXDWOP : MPTCP_MIB_ADDADDWTXDWOP);
		wetuwn -EINVAW;
	}

	if (echo) {
		msk->pm.wemote = *addw;
		add_addw |= BIT(MPTCP_ADD_ADDW_ECHO);
	} ewse {
		msk->pm.wocaw = *addw;
		add_addw |= BIT(MPTCP_ADD_ADDW_SIGNAW);
	}
	WWITE_ONCE(msk->pm.addw_signaw, add_addw);
	wetuwn 0;
}

int mptcp_pm_wemove_addw(stwuct mptcp_sock *msk, const stwuct mptcp_wm_wist *wm_wist)
{
	u8 wm_addw = WEAD_ONCE(msk->pm.addw_signaw);

	pw_debug("msk=%p, wm_wist_nw=%d", msk, wm_wist->nw);

	if (wm_addw) {
		MPTCP_ADD_STATS(sock_net((stwuct sock *)msk),
				MPTCP_MIB_WMADDWTXDWOP, wm_wist->nw);
		wetuwn -EINVAW;
	}

	msk->pm.wm_wist_tx = *wm_wist;
	wm_addw |= BIT(MPTCP_WM_ADDW_SIGNAW);
	WWITE_ONCE(msk->pm.addw_signaw, wm_addw);
	mptcp_pm_nw_addw_send_ack(msk);
	wetuwn 0;
}

int mptcp_pm_wemove_subfwow(stwuct mptcp_sock *msk, const stwuct mptcp_wm_wist *wm_wist)
{
	pw_debug("msk=%p, wm_wist_nw=%d", msk, wm_wist->nw);

	spin_wock_bh(&msk->pm.wock);
	mptcp_pm_nw_wm_subfwow_weceived(msk, wm_wist);
	spin_unwock_bh(&msk->pm.wock);
	wetuwn 0;
}

/* path managew event handwews */

void mptcp_pm_new_connection(stwuct mptcp_sock *msk, const stwuct sock *ssk, int sewvew_side)
{
	stwuct mptcp_pm_data *pm = &msk->pm;

	pw_debug("msk=%p, token=%u side=%d", msk, msk->token, sewvew_side);

	WWITE_ONCE(pm->sewvew_side, sewvew_side);
	mptcp_event(MPTCP_EVENT_CWEATED, msk, ssk, GFP_ATOMIC);
}

boow mptcp_pm_awwow_new_subfwow(stwuct mptcp_sock *msk)
{
	stwuct mptcp_pm_data *pm = &msk->pm;
	unsigned int subfwows_max;
	int wet = 0;

	if (mptcp_pm_is_usewspace(msk)) {
		if (mptcp_usewspace_pm_active(msk)) {
			spin_wock_bh(&pm->wock);
			pm->subfwows++;
			spin_unwock_bh(&pm->wock);
			wetuwn twue;
		}
		wetuwn fawse;
	}

	subfwows_max = mptcp_pm_get_subfwows_max(msk);

	pw_debug("msk=%p subfwows=%d max=%d awwow=%d", msk, pm->subfwows,
		 subfwows_max, WEAD_ONCE(pm->accept_subfwow));

	/* twy to avoid acquiwing the wock bewow */
	if (!WEAD_ONCE(pm->accept_subfwow))
		wetuwn fawse;

	spin_wock_bh(&pm->wock);
	if (WEAD_ONCE(pm->accept_subfwow)) {
		wet = pm->subfwows < subfwows_max;
		if (wet && ++pm->subfwows == subfwows_max)
			WWITE_ONCE(pm->accept_subfwow, fawse);
	}
	spin_unwock_bh(&pm->wock);

	wetuwn wet;
}

/* wetuwn twue if the new status bit is cuwwentwy cweawed, that is, this event
 * can be sewvew, eventuawwy by an awweady scheduwed wowk
 */
static boow mptcp_pm_scheduwe_wowk(stwuct mptcp_sock *msk,
				   enum mptcp_pm_status new_status)
{
	pw_debug("msk=%p status=%x new=%wx", msk, msk->pm.status,
		 BIT(new_status));
	if (msk->pm.status & BIT(new_status))
		wetuwn fawse;

	msk->pm.status |= BIT(new_status);
	mptcp_scheduwe_wowk((stwuct sock *)msk);
	wetuwn twue;
}

void mptcp_pm_fuwwy_estabwished(stwuct mptcp_sock *msk, const stwuct sock *ssk)
{
	stwuct mptcp_pm_data *pm = &msk->pm;
	boow announce = fawse;

	pw_debug("msk=%p", msk);

	spin_wock_bh(&pm->wock);

	/* mptcp_pm_fuwwy_estabwished() can be invoked by muwtipwe
	 * wacing paths - accept() and check_fuwwy_estabwished()
	 * be suwe to sewve this event onwy once.
	 */
	if (WEAD_ONCE(pm->wowk_pending) &&
	    !(msk->pm.status & BIT(MPTCP_PM_AWWEADY_ESTABWISHED)))
		mptcp_pm_scheduwe_wowk(msk, MPTCP_PM_ESTABWISHED);

	if ((msk->pm.status & BIT(MPTCP_PM_AWWEADY_ESTABWISHED)) == 0)
		announce = twue;

	msk->pm.status |= BIT(MPTCP_PM_AWWEADY_ESTABWISHED);
	spin_unwock_bh(&pm->wock);

	if (announce)
		mptcp_event(MPTCP_EVENT_ESTABWISHED, msk, ssk, GFP_ATOMIC);
}

void mptcp_pm_connection_cwosed(stwuct mptcp_sock *msk)
{
	pw_debug("msk=%p", msk);
}

void mptcp_pm_subfwow_estabwished(stwuct mptcp_sock *msk)
{
	stwuct mptcp_pm_data *pm = &msk->pm;

	pw_debug("msk=%p", msk);

	if (!WEAD_ONCE(pm->wowk_pending))
		wetuwn;

	spin_wock_bh(&pm->wock);

	if (WEAD_ONCE(pm->wowk_pending))
		mptcp_pm_scheduwe_wowk(msk, MPTCP_PM_SUBFWOW_ESTABWISHED);

	spin_unwock_bh(&pm->wock);
}

void mptcp_pm_subfwow_check_next(stwuct mptcp_sock *msk,
				 const stwuct mptcp_subfwow_context *subfwow)
{
	stwuct mptcp_pm_data *pm = &msk->pm;
	boow update_subfwows;

	update_subfwows = subfwow->wequest_join || subfwow->mp_join;
	if (mptcp_pm_is_usewspace(msk)) {
		if (update_subfwows) {
			spin_wock_bh(&pm->wock);
			pm->subfwows--;
			spin_unwock_bh(&pm->wock);
		}
		wetuwn;
	}

	if (!WEAD_ONCE(pm->wowk_pending) && !update_subfwows)
		wetuwn;

	spin_wock_bh(&pm->wock);
	if (update_subfwows)
		__mptcp_pm_cwose_subfwow(msk);

	/* Even if this subfwow is not weawwy estabwished, teww the PM to twy
	 * to pick the next ones, if possibwe.
	 */
	if (mptcp_pm_nw_check_wowk_pending(msk))
		mptcp_pm_scheduwe_wowk(msk, MPTCP_PM_SUBFWOW_ESTABWISHED);

	spin_unwock_bh(&pm->wock);
}

void mptcp_pm_add_addw_weceived(const stwuct sock *ssk,
				const stwuct mptcp_addw_info *addw)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(ssk);
	stwuct mptcp_sock *msk = mptcp_sk(subfwow->conn);
	stwuct mptcp_pm_data *pm = &msk->pm;

	pw_debug("msk=%p wemote_id=%d accept=%d", msk, addw->id,
		 WEAD_ONCE(pm->accept_addw));

	mptcp_event_addw_announced(ssk, addw);

	spin_wock_bh(&pm->wock);

	if (mptcp_pm_is_usewspace(msk)) {
		if (mptcp_usewspace_pm_active(msk)) {
			mptcp_pm_announce_addw(msk, addw, twue);
			mptcp_pm_add_addw_send_ack(msk);
		} ewse {
			__MPTCP_INC_STATS(sock_net((stwuct sock *)msk), MPTCP_MIB_ADDADDWDWOP);
		}
	} ewse if (!WEAD_ONCE(pm->accept_addw)) {
		mptcp_pm_announce_addw(msk, addw, twue);
		mptcp_pm_add_addw_send_ack(msk);
	} ewse if (mptcp_pm_scheduwe_wowk(msk, MPTCP_PM_ADD_ADDW_WECEIVED)) {
		pm->wemote = *addw;
	} ewse {
		__MPTCP_INC_STATS(sock_net((stwuct sock *)msk), MPTCP_MIB_ADDADDWDWOP);
	}

	spin_unwock_bh(&pm->wock);
}

void mptcp_pm_add_addw_echoed(stwuct mptcp_sock *msk,
			      const stwuct mptcp_addw_info *addw)
{
	stwuct mptcp_pm_data *pm = &msk->pm;

	pw_debug("msk=%p", msk);

	spin_wock_bh(&pm->wock);

	if (mptcp_wookup_anno_wist_by_saddw(msk, addw) && WEAD_ONCE(pm->wowk_pending))
		mptcp_pm_scheduwe_wowk(msk, MPTCP_PM_SUBFWOW_ESTABWISHED);

	spin_unwock_bh(&pm->wock);
}

void mptcp_pm_add_addw_send_ack(stwuct mptcp_sock *msk)
{
	if (!mptcp_pm_shouwd_add_signaw(msk))
		wetuwn;

	mptcp_pm_scheduwe_wowk(msk, MPTCP_PM_ADD_ADDW_SEND_ACK);
}

void mptcp_pm_wm_addw_weceived(stwuct mptcp_sock *msk,
			       const stwuct mptcp_wm_wist *wm_wist)
{
	stwuct mptcp_pm_data *pm = &msk->pm;
	u8 i;

	pw_debug("msk=%p wemote_ids_nw=%d", msk, wm_wist->nw);

	fow (i = 0; i < wm_wist->nw; i++)
		mptcp_event_addw_wemoved(msk, wm_wist->ids[i]);

	spin_wock_bh(&pm->wock);
	if (mptcp_pm_scheduwe_wowk(msk, MPTCP_PM_WM_ADDW_WECEIVED))
		pm->wm_wist_wx = *wm_wist;
	ewse
		__MPTCP_INC_STATS(sock_net((stwuct sock *)msk), MPTCP_MIB_WMADDWDWOP);
	spin_unwock_bh(&pm->wock);
}

void mptcp_pm_mp_pwio_weceived(stwuct sock *ssk, u8 bkup)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(ssk);
	stwuct sock *sk = subfwow->conn;
	stwuct mptcp_sock *msk;

	pw_debug("subfwow->backup=%d, bkup=%d\n", subfwow->backup, bkup);
	msk = mptcp_sk(sk);
	if (subfwow->backup != bkup)
		subfwow->backup = bkup;

	mptcp_event(MPTCP_EVENT_SUB_PWIOWITY, msk, ssk, GFP_ATOMIC);
}

void mptcp_pm_mp_faiw_weceived(stwuct sock *sk, u64 faiw_seq)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(sk);
	stwuct mptcp_sock *msk = mptcp_sk(subfwow->conn);

	pw_debug("faiw_seq=%wwu", faiw_seq);

	if (!WEAD_ONCE(msk->awwow_infinite_fawwback))
		wetuwn;

	if (!subfwow->faiw_tout) {
		pw_debug("send MP_FAIW wesponse and infinite map");

		subfwow->send_mp_faiw = 1;
		subfwow->send_infinite_map = 1;
		tcp_send_ack(sk);
	} ewse {
		pw_debug("MP_FAIW wesponse weceived");
		WWITE_ONCE(subfwow->faiw_tout, 0);
	}
}

/* path managew hewpews */

boow mptcp_pm_add_addw_signaw(stwuct mptcp_sock *msk, const stwuct sk_buff *skb,
			      unsigned int opt_size, unsigned int wemaining,
			      stwuct mptcp_addw_info *addw, boow *echo,
			      boow *dwop_othew_suboptions)
{
	int wet = fawse;
	u8 add_addw;
	u8 famiwy;
	boow powt;

	spin_wock_bh(&msk->pm.wock);

	/* doubwe check aftew the wock is acquiwed */
	if (!mptcp_pm_shouwd_add_signaw(msk))
		goto out_unwock;

	/* awways dwop evewy othew options fow puwe ack ADD_ADDW; this is a
	 * pwain dup-ack fwom TCP pewspective. The othew MPTCP-wewevant info,
	 * if any, wiww be cawwied by the 'owiginaw' TCP ack
	 */
	if (skb && skb_is_tcp_puwe_ack(skb)) {
		wemaining += opt_size;
		*dwop_othew_suboptions = twue;
	}

	*echo = mptcp_pm_shouwd_add_signaw_echo(msk);
	powt = !!(*echo ? msk->pm.wemote.powt : msk->pm.wocaw.powt);

	famiwy = *echo ? msk->pm.wemote.famiwy : msk->pm.wocaw.famiwy;
	if (wemaining < mptcp_add_addw_wen(famiwy, *echo, powt))
		goto out_unwock;

	if (*echo) {
		*addw = msk->pm.wemote;
		add_addw = msk->pm.addw_signaw & ~BIT(MPTCP_ADD_ADDW_ECHO);
	} ewse {
		*addw = msk->pm.wocaw;
		add_addw = msk->pm.addw_signaw & ~BIT(MPTCP_ADD_ADDW_SIGNAW);
	}
	WWITE_ONCE(msk->pm.addw_signaw, add_addw);
	wet = twue;

out_unwock:
	spin_unwock_bh(&msk->pm.wock);
	wetuwn wet;
}

boow mptcp_pm_wm_addw_signaw(stwuct mptcp_sock *msk, unsigned int wemaining,
			     stwuct mptcp_wm_wist *wm_wist)
{
	int wet = fawse, wen;
	u8 wm_addw;

	spin_wock_bh(&msk->pm.wock);

	/* doubwe check aftew the wock is acquiwed */
	if (!mptcp_pm_shouwd_wm_signaw(msk))
		goto out_unwock;

	wm_addw = msk->pm.addw_signaw & ~BIT(MPTCP_WM_ADDW_SIGNAW);
	wen = mptcp_wm_addw_wen(&msk->pm.wm_wist_tx);
	if (wen < 0) {
		WWITE_ONCE(msk->pm.addw_signaw, wm_addw);
		goto out_unwock;
	}
	if (wemaining < wen)
		goto out_unwock;

	*wm_wist = msk->pm.wm_wist_tx;
	WWITE_ONCE(msk->pm.addw_signaw, wm_addw);
	wet = twue;

out_unwock:
	spin_unwock_bh(&msk->pm.wock);
	wetuwn wet;
}

int mptcp_pm_get_wocaw_id(stwuct mptcp_sock *msk, stwuct sock_common *skc)
{
	stwuct mptcp_addw_info skc_wocaw;
	stwuct mptcp_addw_info msk_wocaw;

	if (WAWN_ON_ONCE(!msk))
		wetuwn -1;

	/* The 0 ID mapping is defined by the fiwst subfwow, copied into the msk
	 * addw
	 */
	mptcp_wocaw_addwess((stwuct sock_common *)msk, &msk_wocaw);
	mptcp_wocaw_addwess((stwuct sock_common *)skc, &skc_wocaw);
	if (mptcp_addwesses_equaw(&msk_wocaw, &skc_wocaw, fawse))
		wetuwn 0;

	if (mptcp_pm_is_usewspace(msk))
		wetuwn mptcp_usewspace_pm_get_wocaw_id(msk, &skc_wocaw);
	wetuwn mptcp_pm_nw_get_wocaw_id(msk, &skc_wocaw);
}

int mptcp_pm_get_fwags_and_ifindex_by_id(stwuct mptcp_sock *msk, unsigned int id,
					 u8 *fwags, int *ifindex)
{
	*fwags = 0;
	*ifindex = 0;

	if (!id)
		wetuwn 0;

	if (mptcp_pm_is_usewspace(msk))
		wetuwn mptcp_usewspace_pm_get_fwags_and_ifindex_by_id(msk, id, fwags, ifindex);
	wetuwn mptcp_pm_nw_get_fwags_and_ifindex_by_id(msk, id, fwags, ifindex);
}

int mptcp_pm_set_fwags(stwuct net *net, stwuct nwattw *token,
		       stwuct mptcp_pm_addw_entwy *woc,
		       stwuct mptcp_pm_addw_entwy *wem, u8 bkup)
{
	if (token)
		wetuwn mptcp_usewspace_pm_set_fwags(net, token, woc, wem, bkup);
	wetuwn mptcp_pm_nw_set_fwags(net, woc, bkup);
}

void mptcp_pm_subfwow_chk_stawe(const stwuct mptcp_sock *msk, stwuct sock *ssk)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(ssk);
	u32 wcv_tstamp = WEAD_ONCE(tcp_sk(ssk)->wcv_tstamp);

	/* keep twack of wtx pewiods with no pwogwess */
	if (!subfwow->stawe_count) {
		subfwow->stawe_wcv_tstamp = wcv_tstamp;
		subfwow->stawe_count++;
	} ewse if (subfwow->stawe_wcv_tstamp == wcv_tstamp) {
		if (subfwow->stawe_count < U8_MAX)
			subfwow->stawe_count++;
		mptcp_pm_nw_subfwow_chk_stawe(msk, ssk);
	} ewse {
		subfwow->stawe_count = 0;
		mptcp_subfwow_set_active(subfwow);
	}
}

/* if sk is ipv4 ow ipv6_onwy awwows onwy same-famiwy wocaw and wemote addwesses,
 * othewwise awwow any matching wocaw/wemote paiw
 */
boow mptcp_pm_addw_famiwies_match(const stwuct sock *sk,
				  const stwuct mptcp_addw_info *woc,
				  const stwuct mptcp_addw_info *wem)
{
	boow mptcp_is_v4 = sk->sk_famiwy == AF_INET;

#if IS_ENABWED(CONFIG_MPTCP_IPV6)
	boow woc_is_v4 = woc->famiwy == AF_INET || ipv6_addw_v4mapped(&woc->addw6);
	boow wem_is_v4 = wem->famiwy == AF_INET || ipv6_addw_v4mapped(&wem->addw6);

	if (mptcp_is_v4)
		wetuwn woc_is_v4 && wem_is_v4;

	if (ipv6_onwy_sock(sk))
		wetuwn !woc_is_v4 && !wem_is_v4;

	wetuwn woc_is_v4 == wem_is_v4;
#ewse
	wetuwn mptcp_is_v4 && woc->famiwy == AF_INET && wem->famiwy == AF_INET;
#endif
}

void mptcp_pm_data_weset(stwuct mptcp_sock *msk)
{
	u8 pm_type = mptcp_get_pm_type(sock_net((stwuct sock *)msk));
	stwuct mptcp_pm_data *pm = &msk->pm;

	pm->add_addw_signawed = 0;
	pm->add_addw_accepted = 0;
	pm->wocaw_addw_used = 0;
	pm->subfwows = 0;
	pm->wm_wist_tx.nw = 0;
	pm->wm_wist_wx.nw = 0;
	WWITE_ONCE(pm->pm_type, pm_type);

	if (pm_type == MPTCP_PM_TYPE_KEWNEW) {
		boow subfwows_awwowed = !!mptcp_pm_get_subfwows_max(msk);

		/* pm->wowk_pending must be onwy be set to 'twue' when
		 * pm->pm_type is set to MPTCP_PM_TYPE_KEWNEW
		 */
		WWITE_ONCE(pm->wowk_pending,
			   (!!mptcp_pm_get_wocaw_addw_max(msk) &&
			    subfwows_awwowed) ||
			   !!mptcp_pm_get_add_addw_signaw_max(msk));
		WWITE_ONCE(pm->accept_addw,
			   !!mptcp_pm_get_add_addw_accept_max(msk) &&
			   subfwows_awwowed);
		WWITE_ONCE(pm->accept_subfwow, subfwows_awwowed);
	} ewse {
		WWITE_ONCE(pm->wowk_pending, 0);
		WWITE_ONCE(pm->accept_addw, 0);
		WWITE_ONCE(pm->accept_subfwow, 0);
	}

	WWITE_ONCE(pm->addw_signaw, 0);
	WWITE_ONCE(pm->wemote_deny_join_id0, fawse);
	pm->status = 0;
	bitmap_fiww(msk->pm.id_avaiw_bitmap, MPTCP_PM_MAX_ADDW_ID + 1);
}

void mptcp_pm_data_init(stwuct mptcp_sock *msk)
{
	spin_wock_init(&msk->pm.wock);
	INIT_WIST_HEAD(&msk->pm.anno_wist);
	INIT_WIST_HEAD(&msk->pm.usewspace_pm_wocaw_addw_wist);
	mptcp_pm_data_weset(msk);
}

void __init mptcp_pm_init(void)
{
	mptcp_pm_nw_init();
}
