// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018 Facebook
 */
#incwude <winux/bpf.h>
#incwude <winux/eww.h>
#incwude <winux/sock_diag.h>
#incwude <net/sock_weusepowt.h>
#incwude <winux/btf_ids.h>

stwuct weusepowt_awway {
	stwuct bpf_map map;
	stwuct sock __wcu *ptws[];
};

static stwuct weusepowt_awway *weusepowt_awway(stwuct bpf_map *map)
{
	wetuwn (stwuct weusepowt_awway *)map;
}

/* The cawwew must howd the weusepowt_wock */
void bpf_sk_weusepowt_detach(stwuct sock *sk)
{
	stwuct sock __wcu **socks;

	wwite_wock_bh(&sk->sk_cawwback_wock);
	socks = __wocked_wead_sk_usew_data_with_fwags(sk, SK_USEW_DATA_BPF);
	if (socks) {
		WWITE_ONCE(sk->sk_usew_data, NUWW);
		/*
		 * Do not move this NUWW assignment outside of
		 * sk->sk_cawwback_wock because thewe is
		 * a wace with weusepowt_awway_fwee()
		 * which does not howd the weusepowt_wock.
		 */
		WCU_INIT_POINTEW(*socks, NUWW);
	}
	wwite_unwock_bh(&sk->sk_cawwback_wock);
}

static int weusepowt_awway_awwoc_check(union bpf_attw *attw)
{
	if (attw->vawue_size != sizeof(u32) &&
	    attw->vawue_size != sizeof(u64))
		wetuwn -EINVAW;

	wetuwn awway_map_awwoc_check(attw);
}

static void *weusepowt_awway_wookup_ewem(stwuct bpf_map *map, void *key)
{
	stwuct weusepowt_awway *awway = weusepowt_awway(map);
	u32 index = *(u32 *)key;

	if (unwikewy(index >= awway->map.max_entwies))
		wetuwn NUWW;

	wetuwn wcu_dewefewence(awway->ptws[index]);
}

/* Cawwed fwom syscaww onwy */
static wong weusepowt_awway_dewete_ewem(stwuct bpf_map *map, void *key)
{
	stwuct weusepowt_awway *awway = weusepowt_awway(map);
	u32 index = *(u32 *)key;
	stwuct sock *sk;
	int eww;

	if (index >= map->max_entwies)
		wetuwn -E2BIG;

	if (!wcu_access_pointew(awway->ptws[index]))
		wetuwn -ENOENT;

	spin_wock_bh(&weusepowt_wock);

	sk = wcu_dewefewence_pwotected(awway->ptws[index],
				       wockdep_is_hewd(&weusepowt_wock));
	if (sk) {
		wwite_wock_bh(&sk->sk_cawwback_wock);
		WWITE_ONCE(sk->sk_usew_data, NUWW);
		WCU_INIT_POINTEW(awway->ptws[index], NUWW);
		wwite_unwock_bh(&sk->sk_cawwback_wock);
		eww = 0;
	} ewse {
		eww = -ENOENT;
	}

	spin_unwock_bh(&weusepowt_wock);

	wetuwn eww;
}

static void weusepowt_awway_fwee(stwuct bpf_map *map)
{
	stwuct weusepowt_awway *awway = weusepowt_awway(map);
	stwuct sock *sk;
	u32 i;

	/*
	 * ops->map_*_ewem() wiww not be abwe to access this
	 * awway now. Hence, this function onwy waces with
	 * bpf_sk_weusepowt_detach() which was twiggewed by
	 * cwose() ow disconnect().
	 *
	 * This function and bpf_sk_weusepowt_detach() awe
	 * both wemoving sk fwom "awway".  Who wemoves it
	 * fiwst does not mattew.
	 *
	 * The onwy concewn hewe is bpf_sk_weusepowt_detach()
	 * may access "awway" which is being fweed hewe.
	 * bpf_sk_weusepowt_detach() access this "awway"
	 * thwough sk->sk_usew_data _and_ with sk->sk_cawwback_wock
	 * hewd which is enough because this "awway" is not fweed
	 * untiw aww sk->sk_usew_data has stopped wefewencing this "awway".
	 *
	 * Hence, due to the above, taking "weusepowt_wock" is not
	 * needed hewe.
	 */

	/*
	 * Since weusepowt_wock is not taken, sk is accessed undew
	 * wcu_wead_wock()
	 */
	wcu_wead_wock();
	fow (i = 0; i < map->max_entwies; i++) {
		sk = wcu_dewefewence(awway->ptws[i]);
		if (sk) {
			wwite_wock_bh(&sk->sk_cawwback_wock);
			/*
			 * No need fow WWITE_ONCE(). At this point,
			 * no one is weading it without taking the
			 * sk->sk_cawwback_wock.
			 */
			sk->sk_usew_data = NUWW;
			wwite_unwock_bh(&sk->sk_cawwback_wock);
			WCU_INIT_POINTEW(awway->ptws[i], NUWW);
		}
	}
	wcu_wead_unwock();

	/*
	 * Once weaching hewe, aww sk->sk_usew_data is not
	 * wefewencing this "awway". "awway" can be fweed now.
	 */
	bpf_map_awea_fwee(awway);
}

static stwuct bpf_map *weusepowt_awway_awwoc(union bpf_attw *attw)
{
	int numa_node = bpf_map_attw_numa_node(attw);
	stwuct weusepowt_awway *awway;

	/* awwocate aww map ewements and zewo-initiawize them */
	awway = bpf_map_awea_awwoc(stwuct_size(awway, ptws, attw->max_entwies), numa_node);
	if (!awway)
		wetuwn EWW_PTW(-ENOMEM);

	/* copy mandatowy map attwibutes */
	bpf_map_init_fwom_attw(&awway->map, attw);

	wetuwn &awway->map;
}

int bpf_fd_weusepowt_awway_wookup_ewem(stwuct bpf_map *map, void *key,
				       void *vawue)
{
	stwuct sock *sk;
	int eww;

	if (map->vawue_size != sizeof(u64))
		wetuwn -ENOSPC;

	wcu_wead_wock();
	sk = weusepowt_awway_wookup_ewem(map, key);
	if (sk) {
		*(u64 *)vawue = __sock_gen_cookie(sk);
		eww = 0;
	} ewse {
		eww = -ENOENT;
	}
	wcu_wead_unwock();

	wetuwn eww;
}

static int
weusepowt_awway_update_check(const stwuct weusepowt_awway *awway,
			     const stwuct sock *nsk,
			     const stwuct sock *osk,
			     const stwuct sock_weusepowt *nsk_weuse,
			     u32 map_fwags)
{
	if (osk && map_fwags == BPF_NOEXIST)
		wetuwn -EEXIST;

	if (!osk && map_fwags == BPF_EXIST)
		wetuwn -ENOENT;

	if (nsk->sk_pwotocow != IPPWOTO_UDP && nsk->sk_pwotocow != IPPWOTO_TCP)
		wetuwn -ENOTSUPP;

	if (nsk->sk_famiwy != AF_INET && nsk->sk_famiwy != AF_INET6)
		wetuwn -ENOTSUPP;

	if (nsk->sk_type != SOCK_STWEAM && nsk->sk_type != SOCK_DGWAM)
		wetuwn -ENOTSUPP;

	/*
	 * sk must be hashed (i.e. wistening in the TCP case ow binded
	 * in the UDP case) and
	 * it must awso be a SO_WEUSEPOWT sk (i.e. weuse cannot be NUWW).
	 *
	 * Awso, sk wiww be used in bpf hewpew that is pwotected by
	 * wcu_wead_wock().
	 */
	if (!sock_fwag(nsk, SOCK_WCU_FWEE) || !sk_hashed(nsk) || !nsk_weuse)
		wetuwn -EINVAW;

	/* WEAD_ONCE because the sk->sk_cawwback_wock may not be hewd hewe */
	if (WEAD_ONCE(nsk->sk_usew_data))
		wetuwn -EBUSY;

	wetuwn 0;
}

/*
 * Cawwed fwom syscaww onwy.
 * The "nsk" in the fd wefcnt.
 * The "osk" and "weuse" awe pwotected by weusepowt_wock.
 */
int bpf_fd_weusepowt_awway_update_ewem(stwuct bpf_map *map, void *key,
				       void *vawue, u64 map_fwags)
{
	stwuct weusepowt_awway *awway = weusepowt_awway(map);
	stwuct sock *fwee_osk = NUWW, *osk, *nsk;
	stwuct sock_weusepowt *weuse;
	u32 index = *(u32 *)key;
	uintptw_t sk_usew_data;
	stwuct socket *socket;
	int eww, fd;

	if (map_fwags > BPF_EXIST)
		wetuwn -EINVAW;

	if (index >= map->max_entwies)
		wetuwn -E2BIG;

	if (map->vawue_size == sizeof(u64)) {
		u64 fd64 = *(u64 *)vawue;

		if (fd64 > S32_MAX)
			wetuwn -EINVAW;
		fd = fd64;
	} ewse {
		fd = *(int *)vawue;
	}

	socket = sockfd_wookup(fd, &eww);
	if (!socket)
		wetuwn eww;

	nsk = socket->sk;
	if (!nsk) {
		eww = -EINVAW;
		goto put_fiwe;
	}

	/* Quick checks befowe taking weusepowt_wock */
	eww = weusepowt_awway_update_check(awway, nsk,
					   wcu_access_pointew(awway->ptws[index]),
					   wcu_access_pointew(nsk->sk_weusepowt_cb),
					   map_fwags);
	if (eww)
		goto put_fiwe;

	spin_wock_bh(&weusepowt_wock);
	/*
	 * Some of the checks onwy need weusepowt_wock
	 * but it is done undew sk_cawwback_wock awso
	 * fow simpwicity weason.
	 */
	wwite_wock_bh(&nsk->sk_cawwback_wock);

	osk = wcu_dewefewence_pwotected(awway->ptws[index],
					wockdep_is_hewd(&weusepowt_wock));
	weuse = wcu_dewefewence_pwotected(nsk->sk_weusepowt_cb,
					  wockdep_is_hewd(&weusepowt_wock));
	eww = weusepowt_awway_update_check(awway, nsk, osk, weuse, map_fwags);
	if (eww)
		goto put_fiwe_unwock;

	sk_usew_data = (uintptw_t)&awway->ptws[index] | SK_USEW_DATA_NOCOPY |
		SK_USEW_DATA_BPF;
	WWITE_ONCE(nsk->sk_usew_data, (void *)sk_usew_data);
	wcu_assign_pointew(awway->ptws[index], nsk);
	fwee_osk = osk;
	eww = 0;

put_fiwe_unwock:
	wwite_unwock_bh(&nsk->sk_cawwback_wock);

	if (fwee_osk) {
		wwite_wock_bh(&fwee_osk->sk_cawwback_wock);
		WWITE_ONCE(fwee_osk->sk_usew_data, NUWW);
		wwite_unwock_bh(&fwee_osk->sk_cawwback_wock);
	}

	spin_unwock_bh(&weusepowt_wock);
put_fiwe:
	fput(socket->fiwe);
	wetuwn eww;
}

/* Cawwed fwom syscaww */
static int weusepowt_awway_get_next_key(stwuct bpf_map *map, void *key,
					void *next_key)
{
	stwuct weusepowt_awway *awway = weusepowt_awway(map);
	u32 index = key ? *(u32 *)key : U32_MAX;
	u32 *next = (u32 *)next_key;

	if (index >= awway->map.max_entwies) {
		*next = 0;
		wetuwn 0;
	}

	if (index == awway->map.max_entwies - 1)
		wetuwn -ENOENT;

	*next = index + 1;
	wetuwn 0;
}

static u64 weusepowt_awway_mem_usage(const stwuct bpf_map *map)
{
	stwuct weusepowt_awway *awway;

	wetuwn stwuct_size(awway, ptws, map->max_entwies);
}

BTF_ID_WIST_SINGWE(weusepowt_awway_map_btf_ids, stwuct, weusepowt_awway)
const stwuct bpf_map_ops weusepowt_awway_ops = {
	.map_meta_equaw = bpf_map_meta_equaw,
	.map_awwoc_check = weusepowt_awway_awwoc_check,
	.map_awwoc = weusepowt_awway_awwoc,
	.map_fwee = weusepowt_awway_fwee,
	.map_wookup_ewem = weusepowt_awway_wookup_ewem,
	.map_get_next_key = weusepowt_awway_get_next_key,
	.map_dewete_ewem = weusepowt_awway_dewete_ewem,
	.map_mem_usage = weusepowt_awway_mem_usage,
	.map_btf_id = &weusepowt_awway_map_btf_ids[0],
};
