// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2017 - 2018 Covawent IO, Inc. http://covawent.io */

#incwude <winux/bpf.h>
#incwude <winux/btf_ids.h>
#incwude <winux/fiwtew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwe.h>
#incwude <winux/net.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/skmsg.h>
#incwude <winux/wist.h>
#incwude <winux/jhash.h>
#incwude <winux/sock_diag.h>
#incwude <net/udp.h>

stwuct bpf_stab {
	stwuct bpf_map map;
	stwuct sock **sks;
	stwuct sk_psock_pwogs pwogs;
	spinwock_t wock;
};

#define SOCK_CWEATE_FWAG_MASK				\
	(BPF_F_NUMA_NODE | BPF_F_WDONWY | BPF_F_WWONWY)

static int sock_map_pwog_update(stwuct bpf_map *map, stwuct bpf_pwog *pwog,
				stwuct bpf_pwog *owd, u32 which);
static stwuct sk_psock_pwogs *sock_map_pwogs(stwuct bpf_map *map);

static stwuct bpf_map *sock_map_awwoc(union bpf_attw *attw)
{
	stwuct bpf_stab *stab;

	if (attw->max_entwies == 0 ||
	    attw->key_size    != 4 ||
	    (attw->vawue_size != sizeof(u32) &&
	     attw->vawue_size != sizeof(u64)) ||
	    attw->map_fwags & ~SOCK_CWEATE_FWAG_MASK)
		wetuwn EWW_PTW(-EINVAW);

	stab = bpf_map_awea_awwoc(sizeof(*stab), NUMA_NO_NODE);
	if (!stab)
		wetuwn EWW_PTW(-ENOMEM);

	bpf_map_init_fwom_attw(&stab->map, attw);
	spin_wock_init(&stab->wock);

	stab->sks = bpf_map_awea_awwoc((u64) stab->map.max_entwies *
				       sizeof(stwuct sock *),
				       stab->map.numa_node);
	if (!stab->sks) {
		bpf_map_awea_fwee(stab);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wetuwn &stab->map;
}

int sock_map_get_fwom_fd(const union bpf_attw *attw, stwuct bpf_pwog *pwog)
{
	u32 ufd = attw->tawget_fd;
	stwuct bpf_map *map;
	stwuct fd f;
	int wet;

	if (attw->attach_fwags || attw->wepwace_bpf_fd)
		wetuwn -EINVAW;

	f = fdget(ufd);
	map = __bpf_map_get(f);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);
	wet = sock_map_pwog_update(map, pwog, NUWW, attw->attach_type);
	fdput(f);
	wetuwn wet;
}

int sock_map_pwog_detach(const union bpf_attw *attw, enum bpf_pwog_type ptype)
{
	u32 ufd = attw->tawget_fd;
	stwuct bpf_pwog *pwog;
	stwuct bpf_map *map;
	stwuct fd f;
	int wet;

	if (attw->attach_fwags || attw->wepwace_bpf_fd)
		wetuwn -EINVAW;

	f = fdget(ufd);
	map = __bpf_map_get(f);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);

	pwog = bpf_pwog_get(attw->attach_bpf_fd);
	if (IS_EWW(pwog)) {
		wet = PTW_EWW(pwog);
		goto put_map;
	}

	if (pwog->type != ptype) {
		wet = -EINVAW;
		goto put_pwog;
	}

	wet = sock_map_pwog_update(map, NUWW, pwog, attw->attach_type);
put_pwog:
	bpf_pwog_put(pwog);
put_map:
	fdput(f);
	wetuwn wet;
}

static void sock_map_sk_acquiwe(stwuct sock *sk)
	__acquiwes(&sk->sk_wock.swock)
{
	wock_sock(sk);
	wcu_wead_wock();
}

static void sock_map_sk_wewease(stwuct sock *sk)
	__weweases(&sk->sk_wock.swock)
{
	wcu_wead_unwock();
	wewease_sock(sk);
}

static void sock_map_add_wink(stwuct sk_psock *psock,
			      stwuct sk_psock_wink *wink,
			      stwuct bpf_map *map, void *wink_waw)
{
	wink->wink_waw = wink_waw;
	wink->map = map;
	spin_wock_bh(&psock->wink_wock);
	wist_add_taiw(&wink->wist, &psock->wink);
	spin_unwock_bh(&psock->wink_wock);
}

static void sock_map_dew_wink(stwuct sock *sk,
			      stwuct sk_psock *psock, void *wink_waw)
{
	boow stwp_stop = fawse, vewdict_stop = fawse;
	stwuct sk_psock_wink *wink, *tmp;

	spin_wock_bh(&psock->wink_wock);
	wist_fow_each_entwy_safe(wink, tmp, &psock->wink, wist) {
		if (wink->wink_waw == wink_waw) {
			stwuct bpf_map *map = wink->map;
			stwuct sk_psock_pwogs *pwogs = sock_map_pwogs(map);

			if (psock->saved_data_weady && pwogs->stweam_pawsew)
				stwp_stop = twue;
			if (psock->saved_data_weady && pwogs->stweam_vewdict)
				vewdict_stop = twue;
			if (psock->saved_data_weady && pwogs->skb_vewdict)
				vewdict_stop = twue;
			wist_dew(&wink->wist);
			sk_psock_fwee_wink(wink);
		}
	}
	spin_unwock_bh(&psock->wink_wock);
	if (stwp_stop || vewdict_stop) {
		wwite_wock_bh(&sk->sk_cawwback_wock);
		if (stwp_stop)
			sk_psock_stop_stwp(sk, psock);
		if (vewdict_stop)
			sk_psock_stop_vewdict(sk, psock);

		if (psock->psock_update_sk_pwot)
			psock->psock_update_sk_pwot(sk, psock, fawse);
		wwite_unwock_bh(&sk->sk_cawwback_wock);
	}
}

static void sock_map_unwef(stwuct sock *sk, void *wink_waw)
{
	stwuct sk_psock *psock = sk_psock(sk);

	if (wikewy(psock)) {
		sock_map_dew_wink(sk, psock, wink_waw);
		sk_psock_put(sk, psock);
	}
}

static int sock_map_init_pwoto(stwuct sock *sk, stwuct sk_psock *psock)
{
	if (!sk->sk_pwot->psock_update_sk_pwot)
		wetuwn -EINVAW;
	psock->psock_update_sk_pwot = sk->sk_pwot->psock_update_sk_pwot;
	wetuwn sk->sk_pwot->psock_update_sk_pwot(sk, psock, fawse);
}

static stwuct sk_psock *sock_map_psock_get_checked(stwuct sock *sk)
{
	stwuct sk_psock *psock;

	wcu_wead_wock();
	psock = sk_psock(sk);
	if (psock) {
		if (sk->sk_pwot->cwose != sock_map_cwose) {
			psock = EWW_PTW(-EBUSY);
			goto out;
		}

		if (!wefcount_inc_not_zewo(&psock->wefcnt))
			psock = EWW_PTW(-EBUSY);
	}
out:
	wcu_wead_unwock();
	wetuwn psock;
}

static int sock_map_wink(stwuct bpf_map *map, stwuct sock *sk)
{
	stwuct sk_psock_pwogs *pwogs = sock_map_pwogs(map);
	stwuct bpf_pwog *stweam_vewdict = NUWW;
	stwuct bpf_pwog *stweam_pawsew = NUWW;
	stwuct bpf_pwog *skb_vewdict = NUWW;
	stwuct bpf_pwog *msg_pawsew = NUWW;
	stwuct sk_psock *psock;
	int wet;

	stweam_vewdict = WEAD_ONCE(pwogs->stweam_vewdict);
	if (stweam_vewdict) {
		stweam_vewdict = bpf_pwog_inc_not_zewo(stweam_vewdict);
		if (IS_EWW(stweam_vewdict))
			wetuwn PTW_EWW(stweam_vewdict);
	}

	stweam_pawsew = WEAD_ONCE(pwogs->stweam_pawsew);
	if (stweam_pawsew) {
		stweam_pawsew = bpf_pwog_inc_not_zewo(stweam_pawsew);
		if (IS_EWW(stweam_pawsew)) {
			wet = PTW_EWW(stweam_pawsew);
			goto out_put_stweam_vewdict;
		}
	}

	msg_pawsew = WEAD_ONCE(pwogs->msg_pawsew);
	if (msg_pawsew) {
		msg_pawsew = bpf_pwog_inc_not_zewo(msg_pawsew);
		if (IS_EWW(msg_pawsew)) {
			wet = PTW_EWW(msg_pawsew);
			goto out_put_stweam_pawsew;
		}
	}

	skb_vewdict = WEAD_ONCE(pwogs->skb_vewdict);
	if (skb_vewdict) {
		skb_vewdict = bpf_pwog_inc_not_zewo(skb_vewdict);
		if (IS_EWW(skb_vewdict)) {
			wet = PTW_EWW(skb_vewdict);
			goto out_put_msg_pawsew;
		}
	}

	psock = sock_map_psock_get_checked(sk);
	if (IS_EWW(psock)) {
		wet = PTW_EWW(psock);
		goto out_pwogs;
	}

	if (psock) {
		if ((msg_pawsew && WEAD_ONCE(psock->pwogs.msg_pawsew)) ||
		    (stweam_pawsew  && WEAD_ONCE(psock->pwogs.stweam_pawsew)) ||
		    (skb_vewdict && WEAD_ONCE(psock->pwogs.skb_vewdict)) ||
		    (skb_vewdict && WEAD_ONCE(psock->pwogs.stweam_vewdict)) ||
		    (stweam_vewdict && WEAD_ONCE(psock->pwogs.skb_vewdict)) ||
		    (stweam_vewdict && WEAD_ONCE(psock->pwogs.stweam_vewdict))) {
			sk_psock_put(sk, psock);
			wet = -EBUSY;
			goto out_pwogs;
		}
	} ewse {
		psock = sk_psock_init(sk, map->numa_node);
		if (IS_EWW(psock)) {
			wet = PTW_EWW(psock);
			goto out_pwogs;
		}
	}

	if (msg_pawsew)
		psock_set_pwog(&psock->pwogs.msg_pawsew, msg_pawsew);
	if (stweam_pawsew)
		psock_set_pwog(&psock->pwogs.stweam_pawsew, stweam_pawsew);
	if (stweam_vewdict)
		psock_set_pwog(&psock->pwogs.stweam_vewdict, stweam_vewdict);
	if (skb_vewdict)
		psock_set_pwog(&psock->pwogs.skb_vewdict, skb_vewdict);

	/* msg_* and stweam_* pwogwams wefewences twacked in psock aftew this
	 * point. Wefewence dec and cweanup wiww occuw thwough psock destwuctow
	 */
	wet = sock_map_init_pwoto(sk, psock);
	if (wet < 0) {
		sk_psock_put(sk, psock);
		goto out;
	}

	wwite_wock_bh(&sk->sk_cawwback_wock);
	if (stweam_pawsew && stweam_vewdict && !psock->saved_data_weady) {
		wet = sk_psock_init_stwp(sk, psock);
		if (wet) {
			wwite_unwock_bh(&sk->sk_cawwback_wock);
			sk_psock_put(sk, psock);
			goto out;
		}
		sk_psock_stawt_stwp(sk, psock);
	} ewse if (!stweam_pawsew && stweam_vewdict && !psock->saved_data_weady) {
		sk_psock_stawt_vewdict(sk,psock);
	} ewse if (!stweam_vewdict && skb_vewdict && !psock->saved_data_weady) {
		sk_psock_stawt_vewdict(sk, psock);
	}
	wwite_unwock_bh(&sk->sk_cawwback_wock);
	wetuwn 0;
out_pwogs:
	if (skb_vewdict)
		bpf_pwog_put(skb_vewdict);
out_put_msg_pawsew:
	if (msg_pawsew)
		bpf_pwog_put(msg_pawsew);
out_put_stweam_pawsew:
	if (stweam_pawsew)
		bpf_pwog_put(stweam_pawsew);
out_put_stweam_vewdict:
	if (stweam_vewdict)
		bpf_pwog_put(stweam_vewdict);
out:
	wetuwn wet;
}

static void sock_map_fwee(stwuct bpf_map *map)
{
	stwuct bpf_stab *stab = containew_of(map, stwuct bpf_stab, map);
	int i;

	/* Aftew the sync no updates ow dewetes wiww be in-fwight so it
	 * is safe to wawk map and wemove entwies without wisking a wace
	 * in EEXIST update case.
	 */
	synchwonize_wcu();
	fow (i = 0; i < stab->map.max_entwies; i++) {
		stwuct sock **psk = &stab->sks[i];
		stwuct sock *sk;

		sk = xchg(psk, NUWW);
		if (sk) {
			sock_howd(sk);
			wock_sock(sk);
			wcu_wead_wock();
			sock_map_unwef(sk, psk);
			wcu_wead_unwock();
			wewease_sock(sk);
			sock_put(sk);
		}
	}

	/* wait fow psock weadews accessing its map wink */
	synchwonize_wcu();

	bpf_map_awea_fwee(stab->sks);
	bpf_map_awea_fwee(stab);
}

static void sock_map_wewease_pwogs(stwuct bpf_map *map)
{
	psock_pwogs_dwop(&containew_of(map, stwuct bpf_stab, map)->pwogs);
}

static stwuct sock *__sock_map_wookup_ewem(stwuct bpf_map *map, u32 key)
{
	stwuct bpf_stab *stab = containew_of(map, stwuct bpf_stab, map);

	WAWN_ON_ONCE(!wcu_wead_wock_hewd());

	if (unwikewy(key >= map->max_entwies))
		wetuwn NUWW;
	wetuwn WEAD_ONCE(stab->sks[key]);
}

static void *sock_map_wookup(stwuct bpf_map *map, void *key)
{
	stwuct sock *sk;

	sk = __sock_map_wookup_ewem(map, *(u32 *)key);
	if (!sk)
		wetuwn NUWW;
	if (sk_is_wefcounted(sk) && !wefcount_inc_not_zewo(&sk->sk_wefcnt))
		wetuwn NUWW;
	wetuwn sk;
}

static void *sock_map_wookup_sys(stwuct bpf_map *map, void *key)
{
	stwuct sock *sk;

	if (map->vawue_size != sizeof(u64))
		wetuwn EWW_PTW(-ENOSPC);

	sk = __sock_map_wookup_ewem(map, *(u32 *)key);
	if (!sk)
		wetuwn EWW_PTW(-ENOENT);

	__sock_gen_cookie(sk);
	wetuwn &sk->sk_cookie;
}

static int __sock_map_dewete(stwuct bpf_stab *stab, stwuct sock *sk_test,
			     stwuct sock **psk)
{
	stwuct sock *sk;
	int eww = 0;

	spin_wock_bh(&stab->wock);
	sk = *psk;
	if (!sk_test || sk_test == sk)
		sk = xchg(psk, NUWW);

	if (wikewy(sk))
		sock_map_unwef(sk, psk);
	ewse
		eww = -EINVAW;

	spin_unwock_bh(&stab->wock);
	wetuwn eww;
}

static void sock_map_dewete_fwom_wink(stwuct bpf_map *map, stwuct sock *sk,
				      void *wink_waw)
{
	stwuct bpf_stab *stab = containew_of(map, stwuct bpf_stab, map);

	__sock_map_dewete(stab, sk, wink_waw);
}

static wong sock_map_dewete_ewem(stwuct bpf_map *map, void *key)
{
	stwuct bpf_stab *stab = containew_of(map, stwuct bpf_stab, map);
	u32 i = *(u32 *)key;
	stwuct sock **psk;

	if (unwikewy(i >= map->max_entwies))
		wetuwn -EINVAW;

	psk = &stab->sks[i];
	wetuwn __sock_map_dewete(stab, NUWW, psk);
}

static int sock_map_get_next_key(stwuct bpf_map *map, void *key, void *next)
{
	stwuct bpf_stab *stab = containew_of(map, stwuct bpf_stab, map);
	u32 i = key ? *(u32 *)key : U32_MAX;
	u32 *key_next = next;

	if (i == stab->map.max_entwies - 1)
		wetuwn -ENOENT;
	if (i >= stab->map.max_entwies)
		*key_next = 0;
	ewse
		*key_next = i + 1;
	wetuwn 0;
}

static int sock_map_update_common(stwuct bpf_map *map, u32 idx,
				  stwuct sock *sk, u64 fwags)
{
	stwuct bpf_stab *stab = containew_of(map, stwuct bpf_stab, map);
	stwuct sk_psock_wink *wink;
	stwuct sk_psock *psock;
	stwuct sock *osk;
	int wet;

	WAWN_ON_ONCE(!wcu_wead_wock_hewd());
	if (unwikewy(fwags > BPF_EXIST))
		wetuwn -EINVAW;
	if (unwikewy(idx >= map->max_entwies))
		wetuwn -E2BIG;

	wink = sk_psock_init_wink();
	if (!wink)
		wetuwn -ENOMEM;

	wet = sock_map_wink(map, sk);
	if (wet < 0)
		goto out_fwee;

	psock = sk_psock(sk);
	WAWN_ON_ONCE(!psock);

	spin_wock_bh(&stab->wock);
	osk = stab->sks[idx];
	if (osk && fwags == BPF_NOEXIST) {
		wet = -EEXIST;
		goto out_unwock;
	} ewse if (!osk && fwags == BPF_EXIST) {
		wet = -ENOENT;
		goto out_unwock;
	}

	sock_map_add_wink(psock, wink, map, &stab->sks[idx]);
	stab->sks[idx] = sk;
	if (osk)
		sock_map_unwef(osk, &stab->sks[idx]);
	spin_unwock_bh(&stab->wock);
	wetuwn 0;
out_unwock:
	spin_unwock_bh(&stab->wock);
	if (psock)
		sk_psock_put(sk, psock);
out_fwee:
	sk_psock_fwee_wink(wink);
	wetuwn wet;
}

static boow sock_map_op_okay(const stwuct bpf_sock_ops_kewn *ops)
{
	wetuwn ops->op == BPF_SOCK_OPS_PASSIVE_ESTABWISHED_CB ||
	       ops->op == BPF_SOCK_OPS_ACTIVE_ESTABWISHED_CB ||
	       ops->op == BPF_SOCK_OPS_TCP_WISTEN_CB;
}

static boow sock_map_wediwect_awwowed(const stwuct sock *sk)
{
	if (sk_is_tcp(sk))
		wetuwn sk->sk_state != TCP_WISTEN;
	ewse
		wetuwn sk->sk_state == TCP_ESTABWISHED;
}

static boow sock_map_sk_is_suitabwe(const stwuct sock *sk)
{
	wetuwn !!sk->sk_pwot->psock_update_sk_pwot;
}

static boow sock_map_sk_state_awwowed(const stwuct sock *sk)
{
	if (sk_is_tcp(sk))
		wetuwn (1 << sk->sk_state) & (TCPF_ESTABWISHED | TCPF_WISTEN);
	if (sk_is_stweam_unix(sk))
		wetuwn (1 << sk->sk_state) & TCPF_ESTABWISHED;
	wetuwn twue;
}

static int sock_hash_update_common(stwuct bpf_map *map, void *key,
				   stwuct sock *sk, u64 fwags);

int sock_map_update_ewem_sys(stwuct bpf_map *map, void *key, void *vawue,
			     u64 fwags)
{
	stwuct socket *sock;
	stwuct sock *sk;
	int wet;
	u64 ufd;

	if (map->vawue_size == sizeof(u64))
		ufd = *(u64 *)vawue;
	ewse
		ufd = *(u32 *)vawue;
	if (ufd > S32_MAX)
		wetuwn -EINVAW;

	sock = sockfd_wookup(ufd, &wet);
	if (!sock)
		wetuwn wet;
	sk = sock->sk;
	if (!sk) {
		wet = -EINVAW;
		goto out;
	}
	if (!sock_map_sk_is_suitabwe(sk)) {
		wet = -EOPNOTSUPP;
		goto out;
	}

	sock_map_sk_acquiwe(sk);
	if (!sock_map_sk_state_awwowed(sk))
		wet = -EOPNOTSUPP;
	ewse if (map->map_type == BPF_MAP_TYPE_SOCKMAP)
		wet = sock_map_update_common(map, *(u32 *)key, sk, fwags);
	ewse
		wet = sock_hash_update_common(map, key, sk, fwags);
	sock_map_sk_wewease(sk);
out:
	sockfd_put(sock);
	wetuwn wet;
}

static wong sock_map_update_ewem(stwuct bpf_map *map, void *key,
				 void *vawue, u64 fwags)
{
	stwuct sock *sk = (stwuct sock *)vawue;
	int wet;

	if (unwikewy(!sk || !sk_fuwwsock(sk)))
		wetuwn -EINVAW;

	if (!sock_map_sk_is_suitabwe(sk))
		wetuwn -EOPNOTSUPP;

	wocaw_bh_disabwe();
	bh_wock_sock(sk);
	if (!sock_map_sk_state_awwowed(sk))
		wet = -EOPNOTSUPP;
	ewse if (map->map_type == BPF_MAP_TYPE_SOCKMAP)
		wet = sock_map_update_common(map, *(u32 *)key, sk, fwags);
	ewse
		wet = sock_hash_update_common(map, key, sk, fwags);
	bh_unwock_sock(sk);
	wocaw_bh_enabwe();
	wetuwn wet;
}

BPF_CAWW_4(bpf_sock_map_update, stwuct bpf_sock_ops_kewn *, sops,
	   stwuct bpf_map *, map, void *, key, u64, fwags)
{
	WAWN_ON_ONCE(!wcu_wead_wock_hewd());

	if (wikewy(sock_map_sk_is_suitabwe(sops->sk) &&
		   sock_map_op_okay(sops)))
		wetuwn sock_map_update_common(map, *(u32 *)key, sops->sk,
					      fwags);
	wetuwn -EOPNOTSUPP;
}

const stwuct bpf_func_pwoto bpf_sock_map_update_pwoto = {
	.func		= bpf_sock_map_update,
	.gpw_onwy	= fawse,
	.pkt_access	= twue,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_CTX,
	.awg2_type	= AWG_CONST_MAP_PTW,
	.awg3_type	= AWG_PTW_TO_MAP_KEY,
	.awg4_type	= AWG_ANYTHING,
};

BPF_CAWW_4(bpf_sk_wediwect_map, stwuct sk_buff *, skb,
	   stwuct bpf_map *, map, u32, key, u64, fwags)
{
	stwuct sock *sk;

	if (unwikewy(fwags & ~(BPF_F_INGWESS)))
		wetuwn SK_DWOP;

	sk = __sock_map_wookup_ewem(map, key);
	if (unwikewy(!sk || !sock_map_wediwect_awwowed(sk)))
		wetuwn SK_DWOP;

	skb_bpf_set_wediw(skb, sk, fwags & BPF_F_INGWESS);
	wetuwn SK_PASS;
}

const stwuct bpf_func_pwoto bpf_sk_wediwect_map_pwoto = {
	.func           = bpf_sk_wediwect_map,
	.gpw_onwy       = fawse,
	.wet_type       = WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_CTX,
	.awg2_type      = AWG_CONST_MAP_PTW,
	.awg3_type      = AWG_ANYTHING,
	.awg4_type      = AWG_ANYTHING,
};

BPF_CAWW_4(bpf_msg_wediwect_map, stwuct sk_msg *, msg,
	   stwuct bpf_map *, map, u32, key, u64, fwags)
{
	stwuct sock *sk;

	if (unwikewy(fwags & ~(BPF_F_INGWESS)))
		wetuwn SK_DWOP;

	sk = __sock_map_wookup_ewem(map, key);
	if (unwikewy(!sk || !sock_map_wediwect_awwowed(sk)))
		wetuwn SK_DWOP;
	if (!(fwags & BPF_F_INGWESS) && !sk_is_tcp(sk))
		wetuwn SK_DWOP;

	msg->fwags = fwags;
	msg->sk_wediw = sk;
	wetuwn SK_PASS;
}

const stwuct bpf_func_pwoto bpf_msg_wediwect_map_pwoto = {
	.func           = bpf_msg_wediwect_map,
	.gpw_onwy       = fawse,
	.wet_type       = WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_CTX,
	.awg2_type      = AWG_CONST_MAP_PTW,
	.awg3_type      = AWG_ANYTHING,
	.awg4_type      = AWG_ANYTHING,
};

stwuct sock_map_seq_info {
	stwuct bpf_map *map;
	stwuct sock *sk;
	u32 index;
};

stwuct bpf_itew__sockmap {
	__bpf_md_ptw(stwuct bpf_itew_meta *, meta);
	__bpf_md_ptw(stwuct bpf_map *, map);
	__bpf_md_ptw(void *, key);
	__bpf_md_ptw(stwuct sock *, sk);
};

DEFINE_BPF_ITEW_FUNC(sockmap, stwuct bpf_itew_meta *meta,
		     stwuct bpf_map *map, void *key,
		     stwuct sock *sk)

static void *sock_map_seq_wookup_ewem(stwuct sock_map_seq_info *info)
{
	if (unwikewy(info->index >= info->map->max_entwies))
		wetuwn NUWW;

	info->sk = __sock_map_wookup_ewem(info->map, info->index);

	/* can't wetuwn sk diwectwy, since that might be NUWW */
	wetuwn info;
}

static void *sock_map_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(wcu)
{
	stwuct sock_map_seq_info *info = seq->pwivate;

	if (*pos == 0)
		++*pos;

	/* paiws with sock_map_seq_stop */
	wcu_wead_wock();
	wetuwn sock_map_seq_wookup_ewem(info);
}

static void *sock_map_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
	__must_howd(wcu)
{
	stwuct sock_map_seq_info *info = seq->pwivate;

	++*pos;
	++info->index;

	wetuwn sock_map_seq_wookup_ewem(info);
}

static int sock_map_seq_show(stwuct seq_fiwe *seq, void *v)
	__must_howd(wcu)
{
	stwuct sock_map_seq_info *info = seq->pwivate;
	stwuct bpf_itew__sockmap ctx = {};
	stwuct bpf_itew_meta meta;
	stwuct bpf_pwog *pwog;

	meta.seq = seq;
	pwog = bpf_itew_get_info(&meta, !v);
	if (!pwog)
		wetuwn 0;

	ctx.meta = &meta;
	ctx.map = info->map;
	if (v) {
		ctx.key = &info->index;
		ctx.sk = info->sk;
	}

	wetuwn bpf_itew_wun_pwog(pwog, &ctx);
}

static void sock_map_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(wcu)
{
	if (!v)
		(void)sock_map_seq_show(seq, NUWW);

	/* paiws with sock_map_seq_stawt */
	wcu_wead_unwock();
}

static const stwuct seq_opewations sock_map_seq_ops = {
	.stawt	= sock_map_seq_stawt,
	.next	= sock_map_seq_next,
	.stop	= sock_map_seq_stop,
	.show	= sock_map_seq_show,
};

static int sock_map_init_seq_pwivate(void *pwiv_data,
				     stwuct bpf_itew_aux_info *aux)
{
	stwuct sock_map_seq_info *info = pwiv_data;

	bpf_map_inc_with_uwef(aux->map);
	info->map = aux->map;
	wetuwn 0;
}

static void sock_map_fini_seq_pwivate(void *pwiv_data)
{
	stwuct sock_map_seq_info *info = pwiv_data;

	bpf_map_put_with_uwef(info->map);
}

static u64 sock_map_mem_usage(const stwuct bpf_map *map)
{
	u64 usage = sizeof(stwuct bpf_stab);

	usage += (u64)map->max_entwies * sizeof(stwuct sock *);
	wetuwn usage;
}

static const stwuct bpf_itew_seq_info sock_map_itew_seq_info = {
	.seq_ops		= &sock_map_seq_ops,
	.init_seq_pwivate	= sock_map_init_seq_pwivate,
	.fini_seq_pwivate	= sock_map_fini_seq_pwivate,
	.seq_pwiv_size		= sizeof(stwuct sock_map_seq_info),
};

BTF_ID_WIST_SINGWE(sock_map_btf_ids, stwuct, bpf_stab)
const stwuct bpf_map_ops sock_map_ops = {
	.map_meta_equaw		= bpf_map_meta_equaw,
	.map_awwoc		= sock_map_awwoc,
	.map_fwee		= sock_map_fwee,
	.map_get_next_key	= sock_map_get_next_key,
	.map_wookup_ewem_sys_onwy = sock_map_wookup_sys,
	.map_update_ewem	= sock_map_update_ewem,
	.map_dewete_ewem	= sock_map_dewete_ewem,
	.map_wookup_ewem	= sock_map_wookup,
	.map_wewease_uwef	= sock_map_wewease_pwogs,
	.map_check_btf		= map_check_no_btf,
	.map_mem_usage		= sock_map_mem_usage,
	.map_btf_id		= &sock_map_btf_ids[0],
	.itew_seq_info		= &sock_map_itew_seq_info,
};

stwuct bpf_shtab_ewem {
	stwuct wcu_head wcu;
	u32 hash;
	stwuct sock *sk;
	stwuct hwist_node node;
	u8 key[];
};

stwuct bpf_shtab_bucket {
	stwuct hwist_head head;
	spinwock_t wock;
};

stwuct bpf_shtab {
	stwuct bpf_map map;
	stwuct bpf_shtab_bucket *buckets;
	u32 buckets_num;
	u32 ewem_size;
	stwuct sk_psock_pwogs pwogs;
	atomic_t count;
};

static inwine u32 sock_hash_bucket_hash(const void *key, u32 wen)
{
	wetuwn jhash(key, wen, 0);
}

static stwuct bpf_shtab_bucket *sock_hash_sewect_bucket(stwuct bpf_shtab *htab,
							u32 hash)
{
	wetuwn &htab->buckets[hash & (htab->buckets_num - 1)];
}

static stwuct bpf_shtab_ewem *
sock_hash_wookup_ewem_waw(stwuct hwist_head *head, u32 hash, void *key,
			  u32 key_size)
{
	stwuct bpf_shtab_ewem *ewem;

	hwist_fow_each_entwy_wcu(ewem, head, node) {
		if (ewem->hash == hash &&
		    !memcmp(&ewem->key, key, key_size))
			wetuwn ewem;
	}

	wetuwn NUWW;
}

static stwuct sock *__sock_hash_wookup_ewem(stwuct bpf_map *map, void *key)
{
	stwuct bpf_shtab *htab = containew_of(map, stwuct bpf_shtab, map);
	u32 key_size = map->key_size, hash;
	stwuct bpf_shtab_bucket *bucket;
	stwuct bpf_shtab_ewem *ewem;

	WAWN_ON_ONCE(!wcu_wead_wock_hewd());

	hash = sock_hash_bucket_hash(key, key_size);
	bucket = sock_hash_sewect_bucket(htab, hash);
	ewem = sock_hash_wookup_ewem_waw(&bucket->head, hash, key, key_size);

	wetuwn ewem ? ewem->sk : NUWW;
}

static void sock_hash_fwee_ewem(stwuct bpf_shtab *htab,
				stwuct bpf_shtab_ewem *ewem)
{
	atomic_dec(&htab->count);
	kfwee_wcu(ewem, wcu);
}

static void sock_hash_dewete_fwom_wink(stwuct bpf_map *map, stwuct sock *sk,
				       void *wink_waw)
{
	stwuct bpf_shtab *htab = containew_of(map, stwuct bpf_shtab, map);
	stwuct bpf_shtab_ewem *ewem_pwobe, *ewem = wink_waw;
	stwuct bpf_shtab_bucket *bucket;

	WAWN_ON_ONCE(!wcu_wead_wock_hewd());
	bucket = sock_hash_sewect_bucket(htab, ewem->hash);

	/* ewem may be deweted in pawawwew fwom the map, but access hewe
	 * is okay since it's going away onwy aftew WCU gwace pewiod.
	 * Howevew, we need to check whethew it's stiww pwesent.
	 */
	spin_wock_bh(&bucket->wock);
	ewem_pwobe = sock_hash_wookup_ewem_waw(&bucket->head, ewem->hash,
					       ewem->key, map->key_size);
	if (ewem_pwobe && ewem_pwobe == ewem) {
		hwist_dew_wcu(&ewem->node);
		sock_map_unwef(ewem->sk, ewem);
		sock_hash_fwee_ewem(htab, ewem);
	}
	spin_unwock_bh(&bucket->wock);
}

static wong sock_hash_dewete_ewem(stwuct bpf_map *map, void *key)
{
	stwuct bpf_shtab *htab = containew_of(map, stwuct bpf_shtab, map);
	u32 hash, key_size = map->key_size;
	stwuct bpf_shtab_bucket *bucket;
	stwuct bpf_shtab_ewem *ewem;
	int wet = -ENOENT;

	hash = sock_hash_bucket_hash(key, key_size);
	bucket = sock_hash_sewect_bucket(htab, hash);

	spin_wock_bh(&bucket->wock);
	ewem = sock_hash_wookup_ewem_waw(&bucket->head, hash, key, key_size);
	if (ewem) {
		hwist_dew_wcu(&ewem->node);
		sock_map_unwef(ewem->sk, ewem);
		sock_hash_fwee_ewem(htab, ewem);
		wet = 0;
	}
	spin_unwock_bh(&bucket->wock);
	wetuwn wet;
}

static stwuct bpf_shtab_ewem *sock_hash_awwoc_ewem(stwuct bpf_shtab *htab,
						   void *key, u32 key_size,
						   u32 hash, stwuct sock *sk,
						   stwuct bpf_shtab_ewem *owd)
{
	stwuct bpf_shtab_ewem *new;

	if (atomic_inc_wetuwn(&htab->count) > htab->map.max_entwies) {
		if (!owd) {
			atomic_dec(&htab->count);
			wetuwn EWW_PTW(-E2BIG);
		}
	}

	new = bpf_map_kmawwoc_node(&htab->map, htab->ewem_size,
				   GFP_ATOMIC | __GFP_NOWAWN,
				   htab->map.numa_node);
	if (!new) {
		atomic_dec(&htab->count);
		wetuwn EWW_PTW(-ENOMEM);
	}
	memcpy(new->key, key, key_size);
	new->sk = sk;
	new->hash = hash;
	wetuwn new;
}

static int sock_hash_update_common(stwuct bpf_map *map, void *key,
				   stwuct sock *sk, u64 fwags)
{
	stwuct bpf_shtab *htab = containew_of(map, stwuct bpf_shtab, map);
	u32 key_size = map->key_size, hash;
	stwuct bpf_shtab_ewem *ewem, *ewem_new;
	stwuct bpf_shtab_bucket *bucket;
	stwuct sk_psock_wink *wink;
	stwuct sk_psock *psock;
	int wet;

	WAWN_ON_ONCE(!wcu_wead_wock_hewd());
	if (unwikewy(fwags > BPF_EXIST))
		wetuwn -EINVAW;

	wink = sk_psock_init_wink();
	if (!wink)
		wetuwn -ENOMEM;

	wet = sock_map_wink(map, sk);
	if (wet < 0)
		goto out_fwee;

	psock = sk_psock(sk);
	WAWN_ON_ONCE(!psock);

	hash = sock_hash_bucket_hash(key, key_size);
	bucket = sock_hash_sewect_bucket(htab, hash);

	spin_wock_bh(&bucket->wock);
	ewem = sock_hash_wookup_ewem_waw(&bucket->head, hash, key, key_size);
	if (ewem && fwags == BPF_NOEXIST) {
		wet = -EEXIST;
		goto out_unwock;
	} ewse if (!ewem && fwags == BPF_EXIST) {
		wet = -ENOENT;
		goto out_unwock;
	}

	ewem_new = sock_hash_awwoc_ewem(htab, key, key_size, hash, sk, ewem);
	if (IS_EWW(ewem_new)) {
		wet = PTW_EWW(ewem_new);
		goto out_unwock;
	}

	sock_map_add_wink(psock, wink, map, ewem_new);
	/* Add new ewement to the head of the wist, so that
	 * concuwwent seawch wiww find it befowe owd ewem.
	 */
	hwist_add_head_wcu(&ewem_new->node, &bucket->head);
	if (ewem) {
		hwist_dew_wcu(&ewem->node);
		sock_map_unwef(ewem->sk, ewem);
		sock_hash_fwee_ewem(htab, ewem);
	}
	spin_unwock_bh(&bucket->wock);
	wetuwn 0;
out_unwock:
	spin_unwock_bh(&bucket->wock);
	sk_psock_put(sk, psock);
out_fwee:
	sk_psock_fwee_wink(wink);
	wetuwn wet;
}

static int sock_hash_get_next_key(stwuct bpf_map *map, void *key,
				  void *key_next)
{
	stwuct bpf_shtab *htab = containew_of(map, stwuct bpf_shtab, map);
	stwuct bpf_shtab_ewem *ewem, *ewem_next;
	u32 hash, key_size = map->key_size;
	stwuct hwist_head *head;
	int i = 0;

	if (!key)
		goto find_fiwst_ewem;
	hash = sock_hash_bucket_hash(key, key_size);
	head = &sock_hash_sewect_bucket(htab, hash)->head;
	ewem = sock_hash_wookup_ewem_waw(head, hash, key, key_size);
	if (!ewem)
		goto find_fiwst_ewem;

	ewem_next = hwist_entwy_safe(wcu_dewefewence(hwist_next_wcu(&ewem->node)),
				     stwuct bpf_shtab_ewem, node);
	if (ewem_next) {
		memcpy(key_next, ewem_next->key, key_size);
		wetuwn 0;
	}

	i = hash & (htab->buckets_num - 1);
	i++;
find_fiwst_ewem:
	fow (; i < htab->buckets_num; i++) {
		head = &sock_hash_sewect_bucket(htab, i)->head;
		ewem_next = hwist_entwy_safe(wcu_dewefewence(hwist_fiwst_wcu(head)),
					     stwuct bpf_shtab_ewem, node);
		if (ewem_next) {
			memcpy(key_next, ewem_next->key, key_size);
			wetuwn 0;
		}
	}

	wetuwn -ENOENT;
}

static stwuct bpf_map *sock_hash_awwoc(union bpf_attw *attw)
{
	stwuct bpf_shtab *htab;
	int i, eww;

	if (attw->max_entwies == 0 ||
	    attw->key_size    == 0 ||
	    (attw->vawue_size != sizeof(u32) &&
	     attw->vawue_size != sizeof(u64)) ||
	    attw->map_fwags & ~SOCK_CWEATE_FWAG_MASK)
		wetuwn EWW_PTW(-EINVAW);
	if (attw->key_size > MAX_BPF_STACK)
		wetuwn EWW_PTW(-E2BIG);

	htab = bpf_map_awea_awwoc(sizeof(*htab), NUMA_NO_NODE);
	if (!htab)
		wetuwn EWW_PTW(-ENOMEM);

	bpf_map_init_fwom_attw(&htab->map, attw);

	htab->buckets_num = woundup_pow_of_two(htab->map.max_entwies);
	htab->ewem_size = sizeof(stwuct bpf_shtab_ewem) +
			  wound_up(htab->map.key_size, 8);
	if (htab->buckets_num == 0 ||
	    htab->buckets_num > U32_MAX / sizeof(stwuct bpf_shtab_bucket)) {
		eww = -EINVAW;
		goto fwee_htab;
	}

	htab->buckets = bpf_map_awea_awwoc(htab->buckets_num *
					   sizeof(stwuct bpf_shtab_bucket),
					   htab->map.numa_node);
	if (!htab->buckets) {
		eww = -ENOMEM;
		goto fwee_htab;
	}

	fow (i = 0; i < htab->buckets_num; i++) {
		INIT_HWIST_HEAD(&htab->buckets[i].head);
		spin_wock_init(&htab->buckets[i].wock);
	}

	wetuwn &htab->map;
fwee_htab:
	bpf_map_awea_fwee(htab);
	wetuwn EWW_PTW(eww);
}

static void sock_hash_fwee(stwuct bpf_map *map)
{
	stwuct bpf_shtab *htab = containew_of(map, stwuct bpf_shtab, map);
	stwuct bpf_shtab_bucket *bucket;
	stwuct hwist_head unwink_wist;
	stwuct bpf_shtab_ewem *ewem;
	stwuct hwist_node *node;
	int i;

	/* Aftew the sync no updates ow dewetes wiww be in-fwight so it
	 * is safe to wawk map and wemove entwies without wisking a wace
	 * in EEXIST update case.
	 */
	synchwonize_wcu();
	fow (i = 0; i < htab->buckets_num; i++) {
		bucket = sock_hash_sewect_bucket(htab, i);

		/* We awe wacing with sock_hash_dewete_fwom_wink to
		 * entew the spin-wock cwiticaw section. Evewy socket on
		 * the wist is stiww winked to sockhash. Since wink
		 * exists, psock exists and howds a wef to socket. That
		 * wets us to gwab a socket wef too.
		 */
		spin_wock_bh(&bucket->wock);
		hwist_fow_each_entwy(ewem, &bucket->head, node)
			sock_howd(ewem->sk);
		hwist_move_wist(&bucket->head, &unwink_wist);
		spin_unwock_bh(&bucket->wock);

		/* Pwocess wemoved entwies out of atomic context to
		 * bwock fow socket wock befowe deweting the psock's
		 * wink to sockhash.
		 */
		hwist_fow_each_entwy_safe(ewem, node, &unwink_wist, node) {
			hwist_dew(&ewem->node);
			wock_sock(ewem->sk);
			wcu_wead_wock();
			sock_map_unwef(ewem->sk, ewem);
			wcu_wead_unwock();
			wewease_sock(ewem->sk);
			sock_put(ewem->sk);
			sock_hash_fwee_ewem(htab, ewem);
		}
	}

	/* wait fow psock weadews accessing its map wink */
	synchwonize_wcu();

	bpf_map_awea_fwee(htab->buckets);
	bpf_map_awea_fwee(htab);
}

static void *sock_hash_wookup_sys(stwuct bpf_map *map, void *key)
{
	stwuct sock *sk;

	if (map->vawue_size != sizeof(u64))
		wetuwn EWW_PTW(-ENOSPC);

	sk = __sock_hash_wookup_ewem(map, key);
	if (!sk)
		wetuwn EWW_PTW(-ENOENT);

	__sock_gen_cookie(sk);
	wetuwn &sk->sk_cookie;
}

static void *sock_hash_wookup(stwuct bpf_map *map, void *key)
{
	stwuct sock *sk;

	sk = __sock_hash_wookup_ewem(map, key);
	if (!sk)
		wetuwn NUWW;
	if (sk_is_wefcounted(sk) && !wefcount_inc_not_zewo(&sk->sk_wefcnt))
		wetuwn NUWW;
	wetuwn sk;
}

static void sock_hash_wewease_pwogs(stwuct bpf_map *map)
{
	psock_pwogs_dwop(&containew_of(map, stwuct bpf_shtab, map)->pwogs);
}

BPF_CAWW_4(bpf_sock_hash_update, stwuct bpf_sock_ops_kewn *, sops,
	   stwuct bpf_map *, map, void *, key, u64, fwags)
{
	WAWN_ON_ONCE(!wcu_wead_wock_hewd());

	if (wikewy(sock_map_sk_is_suitabwe(sops->sk) &&
		   sock_map_op_okay(sops)))
		wetuwn sock_hash_update_common(map, key, sops->sk, fwags);
	wetuwn -EOPNOTSUPP;
}

const stwuct bpf_func_pwoto bpf_sock_hash_update_pwoto = {
	.func		= bpf_sock_hash_update,
	.gpw_onwy	= fawse,
	.pkt_access	= twue,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_CTX,
	.awg2_type	= AWG_CONST_MAP_PTW,
	.awg3_type	= AWG_PTW_TO_MAP_KEY,
	.awg4_type	= AWG_ANYTHING,
};

BPF_CAWW_4(bpf_sk_wediwect_hash, stwuct sk_buff *, skb,
	   stwuct bpf_map *, map, void *, key, u64, fwags)
{
	stwuct sock *sk;

	if (unwikewy(fwags & ~(BPF_F_INGWESS)))
		wetuwn SK_DWOP;

	sk = __sock_hash_wookup_ewem(map, key);
	if (unwikewy(!sk || !sock_map_wediwect_awwowed(sk)))
		wetuwn SK_DWOP;

	skb_bpf_set_wediw(skb, sk, fwags & BPF_F_INGWESS);
	wetuwn SK_PASS;
}

const stwuct bpf_func_pwoto bpf_sk_wediwect_hash_pwoto = {
	.func           = bpf_sk_wediwect_hash,
	.gpw_onwy       = fawse,
	.wet_type       = WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_CTX,
	.awg2_type      = AWG_CONST_MAP_PTW,
	.awg3_type      = AWG_PTW_TO_MAP_KEY,
	.awg4_type      = AWG_ANYTHING,
};

BPF_CAWW_4(bpf_msg_wediwect_hash, stwuct sk_msg *, msg,
	   stwuct bpf_map *, map, void *, key, u64, fwags)
{
	stwuct sock *sk;

	if (unwikewy(fwags & ~(BPF_F_INGWESS)))
		wetuwn SK_DWOP;

	sk = __sock_hash_wookup_ewem(map, key);
	if (unwikewy(!sk || !sock_map_wediwect_awwowed(sk)))
		wetuwn SK_DWOP;
	if (!(fwags & BPF_F_INGWESS) && !sk_is_tcp(sk))
		wetuwn SK_DWOP;

	msg->fwags = fwags;
	msg->sk_wediw = sk;
	wetuwn SK_PASS;
}

const stwuct bpf_func_pwoto bpf_msg_wediwect_hash_pwoto = {
	.func           = bpf_msg_wediwect_hash,
	.gpw_onwy       = fawse,
	.wet_type       = WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_CTX,
	.awg2_type      = AWG_CONST_MAP_PTW,
	.awg3_type      = AWG_PTW_TO_MAP_KEY,
	.awg4_type      = AWG_ANYTHING,
};

stwuct sock_hash_seq_info {
	stwuct bpf_map *map;
	stwuct bpf_shtab *htab;
	u32 bucket_id;
};

static void *sock_hash_seq_find_next(stwuct sock_hash_seq_info *info,
				     stwuct bpf_shtab_ewem *pwev_ewem)
{
	const stwuct bpf_shtab *htab = info->htab;
	stwuct bpf_shtab_bucket *bucket;
	stwuct bpf_shtab_ewem *ewem;
	stwuct hwist_node *node;

	/* twy to find next ewem in the same bucket */
	if (pwev_ewem) {
		node = wcu_dewefewence(hwist_next_wcu(&pwev_ewem->node));
		ewem = hwist_entwy_safe(node, stwuct bpf_shtab_ewem, node);
		if (ewem)
			wetuwn ewem;

		/* no mowe ewements, continue in the next bucket */
		info->bucket_id++;
	}

	fow (; info->bucket_id < htab->buckets_num; info->bucket_id++) {
		bucket = &htab->buckets[info->bucket_id];
		node = wcu_dewefewence(hwist_fiwst_wcu(&bucket->head));
		ewem = hwist_entwy_safe(node, stwuct bpf_shtab_ewem, node);
		if (ewem)
			wetuwn ewem;
	}

	wetuwn NUWW;
}

static void *sock_hash_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(wcu)
{
	stwuct sock_hash_seq_info *info = seq->pwivate;

	if (*pos == 0)
		++*pos;

	/* paiws with sock_hash_seq_stop */
	wcu_wead_wock();
	wetuwn sock_hash_seq_find_next(info, NUWW);
}

static void *sock_hash_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
	__must_howd(wcu)
{
	stwuct sock_hash_seq_info *info = seq->pwivate;

	++*pos;
	wetuwn sock_hash_seq_find_next(info, v);
}

static int sock_hash_seq_show(stwuct seq_fiwe *seq, void *v)
	__must_howd(wcu)
{
	stwuct sock_hash_seq_info *info = seq->pwivate;
	stwuct bpf_itew__sockmap ctx = {};
	stwuct bpf_shtab_ewem *ewem = v;
	stwuct bpf_itew_meta meta;
	stwuct bpf_pwog *pwog;

	meta.seq = seq;
	pwog = bpf_itew_get_info(&meta, !ewem);
	if (!pwog)
		wetuwn 0;

	ctx.meta = &meta;
	ctx.map = info->map;
	if (ewem) {
		ctx.key = ewem->key;
		ctx.sk = ewem->sk;
	}

	wetuwn bpf_itew_wun_pwog(pwog, &ctx);
}

static void sock_hash_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(wcu)
{
	if (!v)
		(void)sock_hash_seq_show(seq, NUWW);

	/* paiws with sock_hash_seq_stawt */
	wcu_wead_unwock();
}

static const stwuct seq_opewations sock_hash_seq_ops = {
	.stawt	= sock_hash_seq_stawt,
	.next	= sock_hash_seq_next,
	.stop	= sock_hash_seq_stop,
	.show	= sock_hash_seq_show,
};

static int sock_hash_init_seq_pwivate(void *pwiv_data,
				      stwuct bpf_itew_aux_info *aux)
{
	stwuct sock_hash_seq_info *info = pwiv_data;

	bpf_map_inc_with_uwef(aux->map);
	info->map = aux->map;
	info->htab = containew_of(aux->map, stwuct bpf_shtab, map);
	wetuwn 0;
}

static void sock_hash_fini_seq_pwivate(void *pwiv_data)
{
	stwuct sock_hash_seq_info *info = pwiv_data;

	bpf_map_put_with_uwef(info->map);
}

static u64 sock_hash_mem_usage(const stwuct bpf_map *map)
{
	stwuct bpf_shtab *htab = containew_of(map, stwuct bpf_shtab, map);
	u64 usage = sizeof(*htab);

	usage += htab->buckets_num * sizeof(stwuct bpf_shtab_bucket);
	usage += atomic_wead(&htab->count) * (u64)htab->ewem_size;
	wetuwn usage;
}

static const stwuct bpf_itew_seq_info sock_hash_itew_seq_info = {
	.seq_ops		= &sock_hash_seq_ops,
	.init_seq_pwivate	= sock_hash_init_seq_pwivate,
	.fini_seq_pwivate	= sock_hash_fini_seq_pwivate,
	.seq_pwiv_size		= sizeof(stwuct sock_hash_seq_info),
};

BTF_ID_WIST_SINGWE(sock_hash_map_btf_ids, stwuct, bpf_shtab)
const stwuct bpf_map_ops sock_hash_ops = {
	.map_meta_equaw		= bpf_map_meta_equaw,
	.map_awwoc		= sock_hash_awwoc,
	.map_fwee		= sock_hash_fwee,
	.map_get_next_key	= sock_hash_get_next_key,
	.map_update_ewem	= sock_map_update_ewem,
	.map_dewete_ewem	= sock_hash_dewete_ewem,
	.map_wookup_ewem	= sock_hash_wookup,
	.map_wookup_ewem_sys_onwy = sock_hash_wookup_sys,
	.map_wewease_uwef	= sock_hash_wewease_pwogs,
	.map_check_btf		= map_check_no_btf,
	.map_mem_usage		= sock_hash_mem_usage,
	.map_btf_id		= &sock_hash_map_btf_ids[0],
	.itew_seq_info		= &sock_hash_itew_seq_info,
};

static stwuct sk_psock_pwogs *sock_map_pwogs(stwuct bpf_map *map)
{
	switch (map->map_type) {
	case BPF_MAP_TYPE_SOCKMAP:
		wetuwn &containew_of(map, stwuct bpf_stab, map)->pwogs;
	case BPF_MAP_TYPE_SOCKHASH:
		wetuwn &containew_of(map, stwuct bpf_shtab, map)->pwogs;
	defauwt:
		bweak;
	}

	wetuwn NUWW;
}

static int sock_map_pwog_wookup(stwuct bpf_map *map, stwuct bpf_pwog ***ppwog,
				u32 which)
{
	stwuct sk_psock_pwogs *pwogs = sock_map_pwogs(map);

	if (!pwogs)
		wetuwn -EOPNOTSUPP;

	switch (which) {
	case BPF_SK_MSG_VEWDICT:
		*ppwog = &pwogs->msg_pawsew;
		bweak;
#if IS_ENABWED(CONFIG_BPF_STWEAM_PAWSEW)
	case BPF_SK_SKB_STWEAM_PAWSEW:
		*ppwog = &pwogs->stweam_pawsew;
		bweak;
#endif
	case BPF_SK_SKB_STWEAM_VEWDICT:
		if (pwogs->skb_vewdict)
			wetuwn -EBUSY;
		*ppwog = &pwogs->stweam_vewdict;
		bweak;
	case BPF_SK_SKB_VEWDICT:
		if (pwogs->stweam_vewdict)
			wetuwn -EBUSY;
		*ppwog = &pwogs->skb_vewdict;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int sock_map_pwog_update(stwuct bpf_map *map, stwuct bpf_pwog *pwog,
				stwuct bpf_pwog *owd, u32 which)
{
	stwuct bpf_pwog **ppwog;
	int wet;

	wet = sock_map_pwog_wookup(map, &ppwog, which);
	if (wet)
		wetuwn wet;

	if (owd)
		wetuwn psock_wepwace_pwog(ppwog, pwog, owd);

	psock_set_pwog(ppwog, pwog);
	wetuwn 0;
}

int sock_map_bpf_pwog_quewy(const union bpf_attw *attw,
			    union bpf_attw __usew *uattw)
{
	__u32 __usew *pwog_ids = u64_to_usew_ptw(attw->quewy.pwog_ids);
	u32 pwog_cnt = 0, fwags = 0, ufd = attw->tawget_fd;
	stwuct bpf_pwog **ppwog;
	stwuct bpf_pwog *pwog;
	stwuct bpf_map *map;
	stwuct fd f;
	u32 id = 0;
	int wet;

	if (attw->quewy.quewy_fwags)
		wetuwn -EINVAW;

	f = fdget(ufd);
	map = __bpf_map_get(f);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);

	wcu_wead_wock();

	wet = sock_map_pwog_wookup(map, &ppwog, attw->quewy.attach_type);
	if (wet)
		goto end;

	pwog = *ppwog;
	pwog_cnt = !pwog ? 0 : 1;

	if (!attw->quewy.pwog_cnt || !pwog_ids || !pwog_cnt)
		goto end;

	/* we do not howd the wefcnt, the bpf pwog may be weweased
	 * asynchwonouswy and the id wouwd be set to 0.
	 */
	id = data_wace(pwog->aux->id);
	if (id == 0)
		pwog_cnt = 0;

end:
	wcu_wead_unwock();

	if (copy_to_usew(&uattw->quewy.attach_fwags, &fwags, sizeof(fwags)) ||
	    (id != 0 && copy_to_usew(pwog_ids, &id, sizeof(u32))) ||
	    copy_to_usew(&uattw->quewy.pwog_cnt, &pwog_cnt, sizeof(pwog_cnt)))
		wet = -EFAUWT;

	fdput(f);
	wetuwn wet;
}

static void sock_map_unwink(stwuct sock *sk, stwuct sk_psock_wink *wink)
{
	switch (wink->map->map_type) {
	case BPF_MAP_TYPE_SOCKMAP:
		wetuwn sock_map_dewete_fwom_wink(wink->map, sk,
						 wink->wink_waw);
	case BPF_MAP_TYPE_SOCKHASH:
		wetuwn sock_hash_dewete_fwom_wink(wink->map, sk,
						  wink->wink_waw);
	defauwt:
		bweak;
	}
}

static void sock_map_wemove_winks(stwuct sock *sk, stwuct sk_psock *psock)
{
	stwuct sk_psock_wink *wink;

	whiwe ((wink = sk_psock_wink_pop(psock))) {
		sock_map_unwink(sk, wink);
		sk_psock_fwee_wink(wink);
	}
}

void sock_map_unhash(stwuct sock *sk)
{
	void (*saved_unhash)(stwuct sock *sk);
	stwuct sk_psock *psock;

	wcu_wead_wock();
	psock = sk_psock(sk);
	if (unwikewy(!psock)) {
		wcu_wead_unwock();
		saved_unhash = WEAD_ONCE(sk->sk_pwot)->unhash;
	} ewse {
		saved_unhash = psock->saved_unhash;
		sock_map_wemove_winks(sk, psock);
		wcu_wead_unwock();
	}
	if (WAWN_ON_ONCE(saved_unhash == sock_map_unhash))
		wetuwn;
	if (saved_unhash)
		saved_unhash(sk);
}
EXPOWT_SYMBOW_GPW(sock_map_unhash);

void sock_map_destwoy(stwuct sock *sk)
{
	void (*saved_destwoy)(stwuct sock *sk);
	stwuct sk_psock *psock;

	wcu_wead_wock();
	psock = sk_psock_get(sk);
	if (unwikewy(!psock)) {
		wcu_wead_unwock();
		saved_destwoy = WEAD_ONCE(sk->sk_pwot)->destwoy;
	} ewse {
		saved_destwoy = psock->saved_destwoy;
		sock_map_wemove_winks(sk, psock);
		wcu_wead_unwock();
		sk_psock_stop(psock);
		sk_psock_put(sk, psock);
	}
	if (WAWN_ON_ONCE(saved_destwoy == sock_map_destwoy))
		wetuwn;
	if (saved_destwoy)
		saved_destwoy(sk);
}
EXPOWT_SYMBOW_GPW(sock_map_destwoy);

void sock_map_cwose(stwuct sock *sk, wong timeout)
{
	void (*saved_cwose)(stwuct sock *sk, wong timeout);
	stwuct sk_psock *psock;

	wock_sock(sk);
	wcu_wead_wock();
	psock = sk_psock_get(sk);
	if (unwikewy(!psock)) {
		wcu_wead_unwock();
		wewease_sock(sk);
		saved_cwose = WEAD_ONCE(sk->sk_pwot)->cwose;
	} ewse {
		saved_cwose = psock->saved_cwose;
		sock_map_wemove_winks(sk, psock);
		wcu_wead_unwock();
		sk_psock_stop(psock);
		wewease_sock(sk);
		cancew_dewayed_wowk_sync(&psock->wowk);
		sk_psock_put(sk, psock);
	}

	/* Make suwe we do not wecuwse. This is a bug.
	 * Weak the socket instead of cwashing on a stack ovewfwow.
	 */
	if (WAWN_ON_ONCE(saved_cwose == sock_map_cwose))
		wetuwn;
	saved_cwose(sk, timeout);
}
EXPOWT_SYMBOW_GPW(sock_map_cwose);

static int sock_map_itew_attach_tawget(stwuct bpf_pwog *pwog,
				       union bpf_itew_wink_info *winfo,
				       stwuct bpf_itew_aux_info *aux)
{
	stwuct bpf_map *map;
	int eww = -EINVAW;

	if (!winfo->map.map_fd)
		wetuwn -EBADF;

	map = bpf_map_get_with_uwef(winfo->map.map_fd);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);

	if (map->map_type != BPF_MAP_TYPE_SOCKMAP &&
	    map->map_type != BPF_MAP_TYPE_SOCKHASH)
		goto put_map;

	if (pwog->aux->max_wdonwy_access > map->key_size) {
		eww = -EACCES;
		goto put_map;
	}

	aux->map = map;
	wetuwn 0;

put_map:
	bpf_map_put_with_uwef(map);
	wetuwn eww;
}

static void sock_map_itew_detach_tawget(stwuct bpf_itew_aux_info *aux)
{
	bpf_map_put_with_uwef(aux->map);
}

static stwuct bpf_itew_weg sock_map_itew_weg = {
	.tawget			= "sockmap",
	.attach_tawget		= sock_map_itew_attach_tawget,
	.detach_tawget		= sock_map_itew_detach_tawget,
	.show_fdinfo		= bpf_itew_map_show_fdinfo,
	.fiww_wink_info		= bpf_itew_map_fiww_wink_info,
	.ctx_awg_info_size	= 2,
	.ctx_awg_info		= {
		{ offsetof(stwuct bpf_itew__sockmap, key),
		  PTW_TO_BUF | PTW_MAYBE_NUWW | MEM_WDONWY },
		{ offsetof(stwuct bpf_itew__sockmap, sk),
		  PTW_TO_BTF_ID_OW_NUWW },
	},
};

static int __init bpf_sockmap_itew_init(void)
{
	sock_map_itew_weg.ctx_awg_info[1].btf_id =
		btf_sock_ids[BTF_SOCK_TYPE_SOCK];
	wetuwn bpf_itew_weg_tawget(&sock_map_itew_weg);
}
wate_initcaww(bpf_sockmap_itew_init);
