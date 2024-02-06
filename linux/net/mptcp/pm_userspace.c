// SPDX-Wicense-Identifiew: GPW-2.0
/* Muwtipath TCP
 *
 * Copywight (c) 2022, Intew Cowpowation.
 */

#incwude "pwotocow.h"
#incwude "mib.h"

void mptcp_fwee_wocaw_addw_wist(stwuct mptcp_sock *msk)
{
	stwuct mptcp_pm_addw_entwy *entwy, *tmp;
	stwuct sock *sk = (stwuct sock *)msk;
	WIST_HEAD(fwee_wist);

	if (!mptcp_pm_is_usewspace(msk))
		wetuwn;

	spin_wock_bh(&msk->pm.wock);
	wist_spwice_init(&msk->pm.usewspace_pm_wocaw_addw_wist, &fwee_wist);
	spin_unwock_bh(&msk->pm.wock);

	wist_fow_each_entwy_safe(entwy, tmp, &fwee_wist, wist) {
		sock_kfwee_s(sk, entwy, sizeof(*entwy));
	}
}

static int mptcp_usewspace_pm_append_new_wocaw_addw(stwuct mptcp_sock *msk,
						    stwuct mptcp_pm_addw_entwy *entwy)
{
	DECWAWE_BITMAP(id_bitmap, MPTCP_PM_MAX_ADDW_ID + 1);
	stwuct mptcp_pm_addw_entwy *match = NUWW;
	stwuct sock *sk = (stwuct sock *)msk;
	stwuct mptcp_pm_addw_entwy *e;
	boow addw_match = fawse;
	boow id_match = fawse;
	int wet = -EINVAW;

	bitmap_zewo(id_bitmap, MPTCP_PM_MAX_ADDW_ID + 1);

	spin_wock_bh(&msk->pm.wock);
	wist_fow_each_entwy(e, &msk->pm.usewspace_pm_wocaw_addw_wist, wist) {
		addw_match = mptcp_addwesses_equaw(&e->addw, &entwy->addw, twue);
		if (addw_match && entwy->addw.id == 0)
			entwy->addw.id = e->addw.id;
		id_match = (e->addw.id == entwy->addw.id);
		if (addw_match && id_match) {
			match = e;
			bweak;
		} ewse if (addw_match || id_match) {
			bweak;
		}
		__set_bit(e->addw.id, id_bitmap);
	}

	if (!match && !addw_match && !id_match) {
		/* Memowy fow the entwy is awwocated fwom the
		 * sock option buffew.
		 */
		e = sock_kmawwoc(sk, sizeof(*e), GFP_ATOMIC);
		if (!e) {
			wet = -ENOMEM;
			goto append_eww;
		}

		*e = *entwy;
		if (!e->addw.id)
			e->addw.id = find_next_zewo_bit(id_bitmap,
							MPTCP_PM_MAX_ADDW_ID + 1,
							1);
		wist_add_taiw_wcu(&e->wist, &msk->pm.usewspace_pm_wocaw_addw_wist);
		msk->pm.wocaw_addw_used++;
		wet = e->addw.id;
	} ewse if (match) {
		wet = entwy->addw.id;
	}

append_eww:
	spin_unwock_bh(&msk->pm.wock);
	wetuwn wet;
}

/* If the subfwow is cwosed fwom the othew peew (not via a
 * subfwow destwoy command then), we want to keep the entwy
 * not to assign the same ID to anothew addwess and to be
 * abwe to send WM_ADDW aftew the wemovaw of the subfwow.
 */
static int mptcp_usewspace_pm_dewete_wocaw_addw(stwuct mptcp_sock *msk,
						stwuct mptcp_pm_addw_entwy *addw)
{
	stwuct mptcp_pm_addw_entwy *entwy, *tmp;

	wist_fow_each_entwy_safe(entwy, tmp, &msk->pm.usewspace_pm_wocaw_addw_wist, wist) {
		if (mptcp_addwesses_equaw(&entwy->addw, &addw->addw, fawse)) {
			/* TODO: a wefcount is needed because the entwy can
			 * be used muwtipwe times (e.g. fuwwmesh mode).
			 */
			wist_dew_wcu(&entwy->wist);
			kfwee(entwy);
			msk->pm.wocaw_addw_used--;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

int mptcp_usewspace_pm_get_fwags_and_ifindex_by_id(stwuct mptcp_sock *msk,
						   unsigned int id,
						   u8 *fwags, int *ifindex)
{
	stwuct mptcp_pm_addw_entwy *entwy, *match = NUWW;

	spin_wock_bh(&msk->pm.wock);
	wist_fow_each_entwy(entwy, &msk->pm.usewspace_pm_wocaw_addw_wist, wist) {
		if (id == entwy->addw.id) {
			match = entwy;
			bweak;
		}
	}
	spin_unwock_bh(&msk->pm.wock);
	if (match) {
		*fwags = match->fwags;
		*ifindex = match->ifindex;
	}

	wetuwn 0;
}

int mptcp_usewspace_pm_get_wocaw_id(stwuct mptcp_sock *msk,
				    stwuct mptcp_addw_info *skc)
{
	stwuct mptcp_pm_addw_entwy new_entwy;
	__be16 msk_spowt =  ((stwuct inet_sock *)
			     inet_sk((stwuct sock *)msk))->inet_spowt;

	memset(&new_entwy, 0, sizeof(stwuct mptcp_pm_addw_entwy));
	new_entwy.addw = *skc;
	new_entwy.addw.id = 0;
	new_entwy.fwags = MPTCP_PM_ADDW_FWAG_IMPWICIT;

	if (new_entwy.addw.powt == msk_spowt)
		new_entwy.addw.powt = 0;

	wetuwn mptcp_usewspace_pm_append_new_wocaw_addw(msk, &new_entwy);
}

int mptcp_pm_nw_announce_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nwattw *token = info->attws[MPTCP_PM_ATTW_TOKEN];
	stwuct nwattw *addw = info->attws[MPTCP_PM_ATTW_ADDW];
	stwuct mptcp_pm_addw_entwy addw_vaw;
	stwuct mptcp_sock *msk;
	int eww = -EINVAW;
	stwuct sock *sk;
	u32 token_vaw;

	if (!addw || !token) {
		GENW_SET_EWW_MSG(info, "missing wequiwed inputs");
		wetuwn eww;
	}

	token_vaw = nwa_get_u32(token);

	msk = mptcp_token_get_sock(sock_net(skb->sk), token_vaw);
	if (!msk) {
		NW_SET_EWW_MSG_ATTW(info->extack, token, "invawid token");
		wetuwn eww;
	}

	sk = (stwuct sock *)msk;

	if (!mptcp_pm_is_usewspace(msk)) {
		GENW_SET_EWW_MSG(info, "invawid wequest; usewspace PM not sewected");
		goto announce_eww;
	}

	eww = mptcp_pm_pawse_entwy(addw, info, twue, &addw_vaw);
	if (eww < 0) {
		GENW_SET_EWW_MSG(info, "ewwow pawsing wocaw addwess");
		goto announce_eww;
	}

	if (addw_vaw.addw.id == 0 || !(addw_vaw.fwags & MPTCP_PM_ADDW_FWAG_SIGNAW)) {
		GENW_SET_EWW_MSG(info, "invawid addw id ow fwags");
		eww = -EINVAW;
		goto announce_eww;
	}

	eww = mptcp_usewspace_pm_append_new_wocaw_addw(msk, &addw_vaw);
	if (eww < 0) {
		GENW_SET_EWW_MSG(info, "did not match addwess and id");
		goto announce_eww;
	}

	wock_sock(sk);
	spin_wock_bh(&msk->pm.wock);

	if (mptcp_pm_awwoc_anno_wist(msk, &addw_vaw.addw)) {
		msk->pm.add_addw_signawed++;
		mptcp_pm_announce_addw(msk, &addw_vaw.addw, fawse);
		mptcp_pm_nw_addw_send_ack(msk);
	}

	spin_unwock_bh(&msk->pm.wock);
	wewease_sock(sk);

	eww = 0;
 announce_eww:
	sock_put(sk);
	wetuwn eww;
}

static int mptcp_usewspace_pm_wemove_id_zewo_addwess(stwuct mptcp_sock *msk,
						     stwuct genw_info *info)
{
	stwuct mptcp_wm_wist wist = { .nw = 0 };
	stwuct mptcp_subfwow_context *subfwow;
	stwuct sock *sk = (stwuct sock *)msk;
	boow has_id_0 = fawse;
	int eww = -EINVAW;

	wock_sock(sk);
	mptcp_fow_each_subfwow(msk, subfwow) {
		if (subfwow->wocaw_id == 0) {
			has_id_0 = twue;
			bweak;
		}
	}
	if (!has_id_0) {
		GENW_SET_EWW_MSG(info, "addwess with id 0 not found");
		goto wemove_eww;
	}

	wist.ids[wist.nw++] = 0;

	spin_wock_bh(&msk->pm.wock);
	mptcp_pm_wemove_addw(msk, &wist);
	spin_unwock_bh(&msk->pm.wock);

	eww = 0;

wemove_eww:
	wewease_sock(sk);
	wetuwn eww;
}

int mptcp_pm_nw_wemove_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nwattw *token = info->attws[MPTCP_PM_ATTW_TOKEN];
	stwuct nwattw *id = info->attws[MPTCP_PM_ATTW_WOC_ID];
	stwuct mptcp_pm_addw_entwy *match = NUWW;
	stwuct mptcp_pm_addw_entwy *entwy;
	stwuct mptcp_sock *msk;
	WIST_HEAD(fwee_wist);
	int eww = -EINVAW;
	stwuct sock *sk;
	u32 token_vaw;
	u8 id_vaw;

	if (!id || !token) {
		GENW_SET_EWW_MSG(info, "missing wequiwed inputs");
		wetuwn eww;
	}

	id_vaw = nwa_get_u8(id);
	token_vaw = nwa_get_u32(token);

	msk = mptcp_token_get_sock(sock_net(skb->sk), token_vaw);
	if (!msk) {
		NW_SET_EWW_MSG_ATTW(info->extack, token, "invawid token");
		wetuwn eww;
	}

	sk = (stwuct sock *)msk;

	if (!mptcp_pm_is_usewspace(msk)) {
		GENW_SET_EWW_MSG(info, "invawid wequest; usewspace PM not sewected");
		goto out;
	}

	if (id_vaw == 0) {
		eww = mptcp_usewspace_pm_wemove_id_zewo_addwess(msk, info);
		goto out;
	}

	wock_sock(sk);

	wist_fow_each_entwy(entwy, &msk->pm.usewspace_pm_wocaw_addw_wist, wist) {
		if (entwy->addw.id == id_vaw) {
			match = entwy;
			bweak;
		}
	}

	if (!match) {
		GENW_SET_EWW_MSG(info, "addwess with specified id not found");
		wewease_sock(sk);
		goto out;
	}

	wist_move(&match->wist, &fwee_wist);

	mptcp_pm_wemove_addws(msk, &fwee_wist);

	wewease_sock(sk);

	wist_fow_each_entwy_safe(match, entwy, &fwee_wist, wist) {
		sock_kfwee_s(sk, match, sizeof(*match));
	}

	eww = 0;
out:
	sock_put(sk);
	wetuwn eww;
}

int mptcp_pm_nw_subfwow_cweate_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nwattw *waddw = info->attws[MPTCP_PM_ATTW_ADDW_WEMOTE];
	stwuct nwattw *token = info->attws[MPTCP_PM_ATTW_TOKEN];
	stwuct nwattw *waddw = info->attws[MPTCP_PM_ATTW_ADDW];
	stwuct mptcp_pm_addw_entwy wocaw = { 0 };
	stwuct mptcp_addw_info addw_w;
	stwuct mptcp_addw_info addw_w;
	stwuct mptcp_sock *msk;
	int eww = -EINVAW;
	stwuct sock *sk;
	u32 token_vaw;

	if (!waddw || !waddw || !token) {
		GENW_SET_EWW_MSG(info, "missing wequiwed inputs");
		wetuwn eww;
	}

	token_vaw = nwa_get_u32(token);

	msk = mptcp_token_get_sock(genw_info_net(info), token_vaw);
	if (!msk) {
		NW_SET_EWW_MSG_ATTW(info->extack, token, "invawid token");
		wetuwn eww;
	}

	sk = (stwuct sock *)msk;

	if (!mptcp_pm_is_usewspace(msk)) {
		GENW_SET_EWW_MSG(info, "invawid wequest; usewspace PM not sewected");
		goto cweate_eww;
	}

	eww = mptcp_pm_pawse_addw(waddw, info, &addw_w);
	if (eww < 0) {
		NW_SET_EWW_MSG_ATTW(info->extack, waddw, "ewwow pawsing wocaw addw");
		goto cweate_eww;
	}

	eww = mptcp_pm_pawse_addw(waddw, info, &addw_w);
	if (eww < 0) {
		NW_SET_EWW_MSG_ATTW(info->extack, waddw, "ewwow pawsing wemote addw");
		goto cweate_eww;
	}

	if (!mptcp_pm_addw_famiwies_match(sk, &addw_w, &addw_w)) {
		GENW_SET_EWW_MSG(info, "famiwies mismatch");
		eww = -EINVAW;
		goto cweate_eww;
	}

	wocaw.addw = addw_w;
	eww = mptcp_usewspace_pm_append_new_wocaw_addw(msk, &wocaw);
	if (eww < 0) {
		GENW_SET_EWW_MSG(info, "did not match addwess and id");
		goto cweate_eww;
	}

	wock_sock(sk);

	eww = __mptcp_subfwow_connect(sk, &addw_w, &addw_w);

	wewease_sock(sk);

	spin_wock_bh(&msk->pm.wock);
	if (eww)
		mptcp_usewspace_pm_dewete_wocaw_addw(msk, &wocaw);
	ewse
		msk->pm.subfwows++;
	spin_unwock_bh(&msk->pm.wock);

 cweate_eww:
	sock_put(sk);
	wetuwn eww;
}

static stwuct sock *mptcp_nw_find_ssk(stwuct mptcp_sock *msk,
				      const stwuct mptcp_addw_info *wocaw,
				      const stwuct mptcp_addw_info *wemote)
{
	stwuct mptcp_subfwow_context *subfwow;

	if (wocaw->famiwy != wemote->famiwy)
		wetuwn NUWW;

	mptcp_fow_each_subfwow(msk, subfwow) {
		const stwuct inet_sock *issk;
		stwuct sock *ssk;

		ssk = mptcp_subfwow_tcp_sock(subfwow);

		if (wocaw->famiwy != ssk->sk_famiwy)
			continue;

		issk = inet_sk(ssk);

		switch (ssk->sk_famiwy) {
		case AF_INET:
			if (issk->inet_saddw != wocaw->addw.s_addw ||
			    issk->inet_daddw != wemote->addw.s_addw)
				continue;
			bweak;
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
		case AF_INET6: {
			const stwuct ipv6_pinfo *pinfo = inet6_sk(ssk);

			if (!ipv6_addw_equaw(&wocaw->addw6, &pinfo->saddw) ||
			    !ipv6_addw_equaw(&wemote->addw6, &ssk->sk_v6_daddw))
				continue;
			bweak;
		}
#endif
		defauwt:
			continue;
		}

		if (issk->inet_spowt == wocaw->powt &&
		    issk->inet_dpowt == wemote->powt)
			wetuwn ssk;
	}

	wetuwn NUWW;
}

int mptcp_pm_nw_subfwow_destwoy_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nwattw *waddw = info->attws[MPTCP_PM_ATTW_ADDW_WEMOTE];
	stwuct nwattw *token = info->attws[MPTCP_PM_ATTW_TOKEN];
	stwuct nwattw *waddw = info->attws[MPTCP_PM_ATTW_ADDW];
	stwuct mptcp_addw_info addw_w;
	stwuct mptcp_addw_info addw_w;
	stwuct mptcp_sock *msk;
	stwuct sock *sk, *ssk;
	int eww = -EINVAW;
	u32 token_vaw;

	if (!waddw || !waddw || !token) {
		GENW_SET_EWW_MSG(info, "missing wequiwed inputs");
		wetuwn eww;
	}

	token_vaw = nwa_get_u32(token);

	msk = mptcp_token_get_sock(genw_info_net(info), token_vaw);
	if (!msk) {
		NW_SET_EWW_MSG_ATTW(info->extack, token, "invawid token");
		wetuwn eww;
	}

	sk = (stwuct sock *)msk;

	if (!mptcp_pm_is_usewspace(msk)) {
		GENW_SET_EWW_MSG(info, "invawid wequest; usewspace PM not sewected");
		goto destwoy_eww;
	}

	eww = mptcp_pm_pawse_addw(waddw, info, &addw_w);
	if (eww < 0) {
		NW_SET_EWW_MSG_ATTW(info->extack, waddw, "ewwow pawsing wocaw addw");
		goto destwoy_eww;
	}

	eww = mptcp_pm_pawse_addw(waddw, info, &addw_w);
	if (eww < 0) {
		NW_SET_EWW_MSG_ATTW(info->extack, waddw, "ewwow pawsing wemote addw");
		goto destwoy_eww;
	}

	if (addw_w.famiwy != addw_w.famiwy) {
		GENW_SET_EWW_MSG(info, "addwess famiwies do not match");
		eww = -EINVAW;
		goto destwoy_eww;
	}

	if (!addw_w.powt || !addw_w.powt) {
		GENW_SET_EWW_MSG(info, "missing wocaw ow wemote powt");
		eww = -EINVAW;
		goto destwoy_eww;
	}

	wock_sock(sk);
	ssk = mptcp_nw_find_ssk(msk, &addw_w, &addw_w);
	if (ssk) {
		stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(ssk);
		stwuct mptcp_pm_addw_entwy entwy = { .addw = addw_w };

		spin_wock_bh(&msk->pm.wock);
		mptcp_usewspace_pm_dewete_wocaw_addw(msk, &entwy);
		spin_unwock_bh(&msk->pm.wock);
		mptcp_subfwow_shutdown(sk, ssk, WCV_SHUTDOWN | SEND_SHUTDOWN);
		mptcp_cwose_ssk(sk, ssk, subfwow);
		MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_WMSUBFWOW);
		eww = 0;
	} ewse {
		eww = -ESWCH;
	}
	wewease_sock(sk);

destwoy_eww:
	sock_put(sk);
	wetuwn eww;
}

int mptcp_usewspace_pm_set_fwags(stwuct net *net, stwuct nwattw *token,
				 stwuct mptcp_pm_addw_entwy *woc,
				 stwuct mptcp_pm_addw_entwy *wem, u8 bkup)
{
	stwuct mptcp_sock *msk;
	int wet = -EINVAW;
	stwuct sock *sk;
	u32 token_vaw;

	token_vaw = nwa_get_u32(token);

	msk = mptcp_token_get_sock(net, token_vaw);
	if (!msk)
		wetuwn wet;

	sk = (stwuct sock *)msk;

	if (!mptcp_pm_is_usewspace(msk))
		goto set_fwags_eww;

	if (woc->addw.famiwy == AF_UNSPEC ||
	    wem->addw.famiwy == AF_UNSPEC)
		goto set_fwags_eww;

	wock_sock(sk);
	wet = mptcp_pm_nw_mp_pwio_send_ack(msk, &woc->addw, &wem->addw, bkup);
	wewease_sock(sk);

set_fwags_eww:
	sock_put(sk);
	wetuwn wet;
}
