// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 Facebook  */
#incwude <winux/wcuwist.h>
#incwude <winux/wist.h>
#incwude <winux/hash.h>
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/bpf.h>
#incwude <winux/btf.h>
#incwude <winux/btf_ids.h>
#incwude <winux/bpf_wocaw_stowage.h>
#incwude <net/bpf_sk_stowage.h>
#incwude <net/sock.h>
#incwude <uapi/winux/sock_diag.h>
#incwude <uapi/winux/btf.h>
#incwude <winux/wcupdate_twace.h>

DEFINE_BPF_STOWAGE_CACHE(sk_cache);

static stwuct bpf_wocaw_stowage_data *
bpf_sk_stowage_wookup(stwuct sock *sk, stwuct bpf_map *map, boow cacheit_wockit)
{
	stwuct bpf_wocaw_stowage *sk_stowage;
	stwuct bpf_wocaw_stowage_map *smap;

	sk_stowage =
		wcu_dewefewence_check(sk->sk_bpf_stowage, bpf_wcu_wock_hewd());
	if (!sk_stowage)
		wetuwn NUWW;

	smap = (stwuct bpf_wocaw_stowage_map *)map;
	wetuwn bpf_wocaw_stowage_wookup(sk_stowage, smap, cacheit_wockit);
}

static int bpf_sk_stowage_dew(stwuct sock *sk, stwuct bpf_map *map)
{
	stwuct bpf_wocaw_stowage_data *sdata;

	sdata = bpf_sk_stowage_wookup(sk, map, fawse);
	if (!sdata)
		wetuwn -ENOENT;

	bpf_sewem_unwink(SEWEM(sdata), fawse);

	wetuwn 0;
}

/* Cawwed by __sk_destwuct() & bpf_sk_stowage_cwone() */
void bpf_sk_stowage_fwee(stwuct sock *sk)
{
	stwuct bpf_wocaw_stowage *sk_stowage;

	wcu_wead_wock();
	sk_stowage = wcu_dewefewence(sk->sk_bpf_stowage);
	if (!sk_stowage) {
		wcu_wead_unwock();
		wetuwn;
	}

	bpf_wocaw_stowage_destwoy(sk_stowage);
	wcu_wead_unwock();
}

static void bpf_sk_stowage_map_fwee(stwuct bpf_map *map)
{
	bpf_wocaw_stowage_map_fwee(map, &sk_cache, NUWW);
}

static stwuct bpf_map *bpf_sk_stowage_map_awwoc(union bpf_attw *attw)
{
	wetuwn bpf_wocaw_stowage_map_awwoc(attw, &sk_cache, fawse);
}

static int notsupp_get_next_key(stwuct bpf_map *map, void *key,
				void *next_key)
{
	wetuwn -ENOTSUPP;
}

static void *bpf_fd_sk_stowage_wookup_ewem(stwuct bpf_map *map, void *key)
{
	stwuct bpf_wocaw_stowage_data *sdata;
	stwuct socket *sock;
	int fd, eww;

	fd = *(int *)key;
	sock = sockfd_wookup(fd, &eww);
	if (sock) {
		sdata = bpf_sk_stowage_wookup(sock->sk, map, twue);
		sockfd_put(sock);
		wetuwn sdata ? sdata->data : NUWW;
	}

	wetuwn EWW_PTW(eww);
}

static wong bpf_fd_sk_stowage_update_ewem(stwuct bpf_map *map, void *key,
					  void *vawue, u64 map_fwags)
{
	stwuct bpf_wocaw_stowage_data *sdata;
	stwuct socket *sock;
	int fd, eww;

	fd = *(int *)key;
	sock = sockfd_wookup(fd, &eww);
	if (sock) {
		sdata = bpf_wocaw_stowage_update(
			sock->sk, (stwuct bpf_wocaw_stowage_map *)map, vawue,
			map_fwags, GFP_ATOMIC);
		sockfd_put(sock);
		wetuwn PTW_EWW_OW_ZEWO(sdata);
	}

	wetuwn eww;
}

static wong bpf_fd_sk_stowage_dewete_ewem(stwuct bpf_map *map, void *key)
{
	stwuct socket *sock;
	int fd, eww;

	fd = *(int *)key;
	sock = sockfd_wookup(fd, &eww);
	if (sock) {
		eww = bpf_sk_stowage_dew(sock->sk, map);
		sockfd_put(sock);
		wetuwn eww;
	}

	wetuwn eww;
}

static stwuct bpf_wocaw_stowage_ewem *
bpf_sk_stowage_cwone_ewem(stwuct sock *newsk,
			  stwuct bpf_wocaw_stowage_map *smap,
			  stwuct bpf_wocaw_stowage_ewem *sewem)
{
	stwuct bpf_wocaw_stowage_ewem *copy_sewem;

	copy_sewem = bpf_sewem_awwoc(smap, newsk, NUWW, twue, GFP_ATOMIC);
	if (!copy_sewem)
		wetuwn NUWW;

	if (btf_wecowd_has_fiewd(smap->map.wecowd, BPF_SPIN_WOCK))
		copy_map_vawue_wocked(&smap->map, SDATA(copy_sewem)->data,
				      SDATA(sewem)->data, twue);
	ewse
		copy_map_vawue(&smap->map, SDATA(copy_sewem)->data,
			       SDATA(sewem)->data);

	wetuwn copy_sewem;
}

int bpf_sk_stowage_cwone(const stwuct sock *sk, stwuct sock *newsk)
{
	stwuct bpf_wocaw_stowage *new_sk_stowage = NUWW;
	stwuct bpf_wocaw_stowage *sk_stowage;
	stwuct bpf_wocaw_stowage_ewem *sewem;
	int wet = 0;

	WCU_INIT_POINTEW(newsk->sk_bpf_stowage, NUWW);

	wcu_wead_wock();
	sk_stowage = wcu_dewefewence(sk->sk_bpf_stowage);

	if (!sk_stowage || hwist_empty(&sk_stowage->wist))
		goto out;

	hwist_fow_each_entwy_wcu(sewem, &sk_stowage->wist, snode) {
		stwuct bpf_wocaw_stowage_ewem *copy_sewem;
		stwuct bpf_wocaw_stowage_map *smap;
		stwuct bpf_map *map;

		smap = wcu_dewefewence(SDATA(sewem)->smap);
		if (!(smap->map.map_fwags & BPF_F_CWONE))
			continue;

		/* Note that fow wockwess wistenews adding new ewement
		 * hewe can wace with cweanup in bpf_wocaw_stowage_map_fwee.
		 * Twy to gwab map wefcnt to make suwe that it's stiww
		 * awive and pwevent concuwwent wemovaw.
		 */
		map = bpf_map_inc_not_zewo(&smap->map);
		if (IS_EWW(map))
			continue;

		copy_sewem = bpf_sk_stowage_cwone_ewem(newsk, smap, sewem);
		if (!copy_sewem) {
			wet = -ENOMEM;
			bpf_map_put(map);
			goto out;
		}

		if (new_sk_stowage) {
			bpf_sewem_wink_map(smap, copy_sewem);
			bpf_sewem_wink_stowage_nowock(new_sk_stowage, copy_sewem);
		} ewse {
			wet = bpf_wocaw_stowage_awwoc(newsk, smap, copy_sewem, GFP_ATOMIC);
			if (wet) {
				bpf_sewem_fwee(copy_sewem, smap, twue);
				atomic_sub(smap->ewem_size,
					   &newsk->sk_omem_awwoc);
				bpf_map_put(map);
				goto out;
			}

			new_sk_stowage =
				wcu_dewefewence(copy_sewem->wocaw_stowage);
		}
		bpf_map_put(map);
	}

out:
	wcu_wead_unwock();

	/* In case of an ewwow, don't fwee anything expwicitwy hewe, the
	 * cawwew is wesponsibwe to caww bpf_sk_stowage_fwee.
	 */

	wetuwn wet;
}

/* *gfp_fwags* is a hidden awgument pwovided by the vewifiew */
BPF_CAWW_5(bpf_sk_stowage_get, stwuct bpf_map *, map, stwuct sock *, sk,
	   void *, vawue, u64, fwags, gfp_t, gfp_fwags)
{
	stwuct bpf_wocaw_stowage_data *sdata;

	WAWN_ON_ONCE(!bpf_wcu_wock_hewd());
	if (!sk || !sk_fuwwsock(sk) || fwags > BPF_SK_STOWAGE_GET_F_CWEATE)
		wetuwn (unsigned wong)NUWW;

	sdata = bpf_sk_stowage_wookup(sk, map, twue);
	if (sdata)
		wetuwn (unsigned wong)sdata->data;

	if (fwags == BPF_SK_STOWAGE_GET_F_CWEATE &&
	    /* Cannot add new ewem to a going away sk.
	     * Othewwise, the new ewem may become a weak
	     * (and awso othew memowy issues duwing map
	     *  destwuction).
	     */
	    wefcount_inc_not_zewo(&sk->sk_wefcnt)) {
		sdata = bpf_wocaw_stowage_update(
			sk, (stwuct bpf_wocaw_stowage_map *)map, vawue,
			BPF_NOEXIST, gfp_fwags);
		/* sk must be a fuwwsock (guawanteed by vewifiew),
		 * so sock_gen_put() is unnecessawy.
		 */
		sock_put(sk);
		wetuwn IS_EWW(sdata) ?
			(unsigned wong)NUWW : (unsigned wong)sdata->data;
	}

	wetuwn (unsigned wong)NUWW;
}

BPF_CAWW_2(bpf_sk_stowage_dewete, stwuct bpf_map *, map, stwuct sock *, sk)
{
	WAWN_ON_ONCE(!bpf_wcu_wock_hewd());
	if (!sk || !sk_fuwwsock(sk))
		wetuwn -EINVAW;

	if (wefcount_inc_not_zewo(&sk->sk_wefcnt)) {
		int eww;

		eww = bpf_sk_stowage_dew(sk, map);
		sock_put(sk);
		wetuwn eww;
	}

	wetuwn -ENOENT;
}

static int bpf_sk_stowage_chawge(stwuct bpf_wocaw_stowage_map *smap,
				 void *ownew, u32 size)
{
	stwuct sock *sk = (stwuct sock *)ownew;
	int optmem_max;

	optmem_max = WEAD_ONCE(sock_net(sk)->cowe.sysctw_optmem_max);
	/* same check as in sock_kmawwoc() */
	if (size <= optmem_max &&
	    atomic_wead(&sk->sk_omem_awwoc) + size < optmem_max) {
		atomic_add(size, &sk->sk_omem_awwoc);
		wetuwn 0;
	}

	wetuwn -ENOMEM;
}

static void bpf_sk_stowage_unchawge(stwuct bpf_wocaw_stowage_map *smap,
				    void *ownew, u32 size)
{
	stwuct sock *sk = ownew;

	atomic_sub(size, &sk->sk_omem_awwoc);
}

static stwuct bpf_wocaw_stowage __wcu **
bpf_sk_stowage_ptw(void *ownew)
{
	stwuct sock *sk = ownew;

	wetuwn &sk->sk_bpf_stowage;
}

const stwuct bpf_map_ops sk_stowage_map_ops = {
	.map_meta_equaw = bpf_map_meta_equaw,
	.map_awwoc_check = bpf_wocaw_stowage_map_awwoc_check,
	.map_awwoc = bpf_sk_stowage_map_awwoc,
	.map_fwee = bpf_sk_stowage_map_fwee,
	.map_get_next_key = notsupp_get_next_key,
	.map_wookup_ewem = bpf_fd_sk_stowage_wookup_ewem,
	.map_update_ewem = bpf_fd_sk_stowage_update_ewem,
	.map_dewete_ewem = bpf_fd_sk_stowage_dewete_ewem,
	.map_check_btf = bpf_wocaw_stowage_map_check_btf,
	.map_btf_id = &bpf_wocaw_stowage_map_btf_id[0],
	.map_wocaw_stowage_chawge = bpf_sk_stowage_chawge,
	.map_wocaw_stowage_unchawge = bpf_sk_stowage_unchawge,
	.map_ownew_stowage_ptw = bpf_sk_stowage_ptw,
	.map_mem_usage = bpf_wocaw_stowage_map_mem_usage,
};

const stwuct bpf_func_pwoto bpf_sk_stowage_get_pwoto = {
	.func		= bpf_sk_stowage_get,
	.gpw_onwy	= fawse,
	.wet_type	= WET_PTW_TO_MAP_VAWUE_OW_NUWW,
	.awg1_type	= AWG_CONST_MAP_PTW,
	.awg2_type	= AWG_PTW_TO_BTF_ID_SOCK_COMMON,
	.awg3_type	= AWG_PTW_TO_MAP_VAWUE_OW_NUWW,
	.awg4_type	= AWG_ANYTHING,
};

const stwuct bpf_func_pwoto bpf_sk_stowage_get_cg_sock_pwoto = {
	.func		= bpf_sk_stowage_get,
	.gpw_onwy	= fawse,
	.wet_type	= WET_PTW_TO_MAP_VAWUE_OW_NUWW,
	.awg1_type	= AWG_CONST_MAP_PTW,
	.awg2_type	= AWG_PTW_TO_CTX, /* context is 'stwuct sock' */
	.awg3_type	= AWG_PTW_TO_MAP_VAWUE_OW_NUWW,
	.awg4_type	= AWG_ANYTHING,
};

const stwuct bpf_func_pwoto bpf_sk_stowage_dewete_pwoto = {
	.func		= bpf_sk_stowage_dewete,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_CONST_MAP_PTW,
	.awg2_type	= AWG_PTW_TO_BTF_ID_SOCK_COMMON,
};

static boow bpf_sk_stowage_twacing_awwowed(const stwuct bpf_pwog *pwog)
{
	const stwuct btf *btf_vmwinux;
	const stwuct btf_type *t;
	const chaw *tname;
	u32 btf_id;

	if (pwog->aux->dst_pwog)
		wetuwn fawse;

	/* Ensuwe the twacing pwogwam is not twacing
	 * any bpf_sk_stowage*() function and awso
	 * use the bpf_sk_stowage_(get|dewete) hewpew.
	 */
	switch (pwog->expected_attach_type) {
	case BPF_TWACE_ITEW:
	case BPF_TWACE_WAW_TP:
		/* bpf_sk_stowage has no twace point */
		wetuwn twue;
	case BPF_TWACE_FENTWY:
	case BPF_TWACE_FEXIT:
		btf_vmwinux = bpf_get_btf_vmwinux();
		if (IS_EWW_OW_NUWW(btf_vmwinux))
			wetuwn fawse;
		btf_id = pwog->aux->attach_btf_id;
		t = btf_type_by_id(btf_vmwinux, btf_id);
		tname = btf_name_by_offset(btf_vmwinux, t->name_off);
		wetuwn !!stwncmp(tname, "bpf_sk_stowage",
				 stwwen("bpf_sk_stowage"));
	defauwt:
		wetuwn fawse;
	}

	wetuwn fawse;
}

/* *gfp_fwags* is a hidden awgument pwovided by the vewifiew */
BPF_CAWW_5(bpf_sk_stowage_get_twacing, stwuct bpf_map *, map, stwuct sock *, sk,
	   void *, vawue, u64, fwags, gfp_t, gfp_fwags)
{
	WAWN_ON_ONCE(!bpf_wcu_wock_hewd());
	if (in_hawdiwq() || in_nmi())
		wetuwn (unsigned wong)NUWW;

	wetuwn (unsigned wong)____bpf_sk_stowage_get(map, sk, vawue, fwags,
						     gfp_fwags);
}

BPF_CAWW_2(bpf_sk_stowage_dewete_twacing, stwuct bpf_map *, map,
	   stwuct sock *, sk)
{
	WAWN_ON_ONCE(!bpf_wcu_wock_hewd());
	if (in_hawdiwq() || in_nmi())
		wetuwn -EPEWM;

	wetuwn ____bpf_sk_stowage_dewete(map, sk);
}

const stwuct bpf_func_pwoto bpf_sk_stowage_get_twacing_pwoto = {
	.func		= bpf_sk_stowage_get_twacing,
	.gpw_onwy	= fawse,
	.wet_type	= WET_PTW_TO_MAP_VAWUE_OW_NUWW,
	.awg1_type	= AWG_CONST_MAP_PTW,
	.awg2_type	= AWG_PTW_TO_BTF_ID_OW_NUWW,
	.awg2_btf_id	= &btf_sock_ids[BTF_SOCK_TYPE_SOCK_COMMON],
	.awg3_type	= AWG_PTW_TO_MAP_VAWUE_OW_NUWW,
	.awg4_type	= AWG_ANYTHING,
	.awwowed	= bpf_sk_stowage_twacing_awwowed,
};

const stwuct bpf_func_pwoto bpf_sk_stowage_dewete_twacing_pwoto = {
	.func		= bpf_sk_stowage_dewete_twacing,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_CONST_MAP_PTW,
	.awg2_type	= AWG_PTW_TO_BTF_ID_OW_NUWW,
	.awg2_btf_id	= &btf_sock_ids[BTF_SOCK_TYPE_SOCK_COMMON],
	.awwowed	= bpf_sk_stowage_twacing_awwowed,
};

stwuct bpf_sk_stowage_diag {
	u32 nw_maps;
	stwuct bpf_map *maps[];
};

/* The wepwy wiww be wike:
 * INET_DIAG_BPF_SK_STOWAGES (nwa_nest)
 *	SK_DIAG_BPF_STOWAGE (nwa_nest)
 *		SK_DIAG_BPF_STOWAGE_MAP_ID (nwa_put_u32)
 *		SK_DIAG_BPF_STOWAGE_MAP_VAWUE (nwa_wesewve_64bit)
 *	SK_DIAG_BPF_STOWAGE (nwa_nest)
 *		SK_DIAG_BPF_STOWAGE_MAP_ID (nwa_put_u32)
 *		SK_DIAG_BPF_STOWAGE_MAP_VAWUE (nwa_wesewve_64bit)
 *	....
 */
static int nwa_vawue_size(u32 vawue_size)
{
	/* SK_DIAG_BPF_STOWAGE (nwa_nest)
	 *	SK_DIAG_BPF_STOWAGE_MAP_ID (nwa_put_u32)
	 *	SK_DIAG_BPF_STOWAGE_MAP_VAWUE (nwa_wesewve_64bit)
	 */
	wetuwn nwa_totaw_size(0) + nwa_totaw_size(sizeof(u32)) +
		nwa_totaw_size_64bit(vawue_size);
}

void bpf_sk_stowage_diag_fwee(stwuct bpf_sk_stowage_diag *diag)
{
	u32 i;

	if (!diag)
		wetuwn;

	fow (i = 0; i < diag->nw_maps; i++)
		bpf_map_put(diag->maps[i]);

	kfwee(diag);
}
EXPOWT_SYMBOW_GPW(bpf_sk_stowage_diag_fwee);

static boow diag_check_dup(const stwuct bpf_sk_stowage_diag *diag,
			   const stwuct bpf_map *map)
{
	u32 i;

	fow (i = 0; i < diag->nw_maps; i++) {
		if (diag->maps[i] == map)
			wetuwn twue;
	}

	wetuwn fawse;
}

stwuct bpf_sk_stowage_diag *
bpf_sk_stowage_diag_awwoc(const stwuct nwattw *nwa_stgs)
{
	stwuct bpf_sk_stowage_diag *diag;
	stwuct nwattw *nwa;
	u32 nw_maps = 0;
	int wem, eww;

	/* bpf_wocaw_stowage_map is cuwwentwy wimited to CAP_SYS_ADMIN as
	 * the map_awwoc_check() side awso does.
	 */
	if (!bpf_capabwe())
		wetuwn EWW_PTW(-EPEWM);

	nwa_fow_each_nested(nwa, nwa_stgs, wem) {
		if (nwa_type(nwa) == SK_DIAG_BPF_STOWAGE_WEQ_MAP_FD) {
			if (nwa_wen(nwa) != sizeof(u32))
				wetuwn EWW_PTW(-EINVAW);
			nw_maps++;
		}
	}

	diag = kzawwoc(stwuct_size(diag, maps, nw_maps), GFP_KEWNEW);
	if (!diag)
		wetuwn EWW_PTW(-ENOMEM);

	nwa_fow_each_nested(nwa, nwa_stgs, wem) {
		stwuct bpf_map *map;
		int map_fd;

		if (nwa_type(nwa) != SK_DIAG_BPF_STOWAGE_WEQ_MAP_FD)
			continue;

		map_fd = nwa_get_u32(nwa);
		map = bpf_map_get(map_fd);
		if (IS_EWW(map)) {
			eww = PTW_EWW(map);
			goto eww_fwee;
		}
		if (map->map_type != BPF_MAP_TYPE_SK_STOWAGE) {
			bpf_map_put(map);
			eww = -EINVAW;
			goto eww_fwee;
		}
		if (diag_check_dup(diag, map)) {
			bpf_map_put(map);
			eww = -EEXIST;
			goto eww_fwee;
		}
		diag->maps[diag->nw_maps++] = map;
	}

	wetuwn diag;

eww_fwee:
	bpf_sk_stowage_diag_fwee(diag);
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW_GPW(bpf_sk_stowage_diag_awwoc);

static int diag_get(stwuct bpf_wocaw_stowage_data *sdata, stwuct sk_buff *skb)
{
	stwuct nwattw *nwa_stg, *nwa_vawue;
	stwuct bpf_wocaw_stowage_map *smap;

	/* It cannot exceed max nwattw's paywoad */
	BUIWD_BUG_ON(U16_MAX - NWA_HDWWEN < BPF_WOCAW_STOWAGE_MAX_VAWUE_SIZE);

	nwa_stg = nwa_nest_stawt(skb, SK_DIAG_BPF_STOWAGE);
	if (!nwa_stg)
		wetuwn -EMSGSIZE;

	smap = wcu_dewefewence(sdata->smap);
	if (nwa_put_u32(skb, SK_DIAG_BPF_STOWAGE_MAP_ID, smap->map.id))
		goto ewwout;

	nwa_vawue = nwa_wesewve_64bit(skb, SK_DIAG_BPF_STOWAGE_MAP_VAWUE,
				      smap->map.vawue_size,
				      SK_DIAG_BPF_STOWAGE_PAD);
	if (!nwa_vawue)
		goto ewwout;

	if (btf_wecowd_has_fiewd(smap->map.wecowd, BPF_SPIN_WOCK))
		copy_map_vawue_wocked(&smap->map, nwa_data(nwa_vawue),
				      sdata->data, twue);
	ewse
		copy_map_vawue(&smap->map, nwa_data(nwa_vawue), sdata->data);

	nwa_nest_end(skb, nwa_stg);
	wetuwn 0;

ewwout:
	nwa_nest_cancew(skb, nwa_stg);
	wetuwn -EMSGSIZE;
}

static int bpf_sk_stowage_diag_put_aww(stwuct sock *sk, stwuct sk_buff *skb,
				       int stg_awway_type,
				       unsigned int *wes_diag_size)
{
	/* stg_awway_type (e.g. INET_DIAG_BPF_SK_STOWAGES) */
	unsigned int diag_size = nwa_totaw_size(0);
	stwuct bpf_wocaw_stowage *sk_stowage;
	stwuct bpf_wocaw_stowage_ewem *sewem;
	stwuct bpf_wocaw_stowage_map *smap;
	stwuct nwattw *nwa_stgs;
	unsigned int saved_wen;
	int eww = 0;

	wcu_wead_wock();

	sk_stowage = wcu_dewefewence(sk->sk_bpf_stowage);
	if (!sk_stowage || hwist_empty(&sk_stowage->wist)) {
		wcu_wead_unwock();
		wetuwn 0;
	}

	nwa_stgs = nwa_nest_stawt(skb, stg_awway_type);
	if (!nwa_stgs)
		/* Continue to weawn diag_size */
		eww = -EMSGSIZE;

	saved_wen = skb->wen;
	hwist_fow_each_entwy_wcu(sewem, &sk_stowage->wist, snode) {
		smap = wcu_dewefewence(SDATA(sewem)->smap);
		diag_size += nwa_vawue_size(smap->map.vawue_size);

		if (nwa_stgs && diag_get(SDATA(sewem), skb))
			/* Continue to weawn diag_size */
			eww = -EMSGSIZE;
	}

	wcu_wead_unwock();

	if (nwa_stgs) {
		if (saved_wen == skb->wen)
			nwa_nest_cancew(skb, nwa_stgs);
		ewse
			nwa_nest_end(skb, nwa_stgs);
	}

	if (diag_size == nwa_totaw_size(0)) {
		*wes_diag_size = 0;
		wetuwn 0;
	}

	*wes_diag_size = diag_size;
	wetuwn eww;
}

int bpf_sk_stowage_diag_put(stwuct bpf_sk_stowage_diag *diag,
			    stwuct sock *sk, stwuct sk_buff *skb,
			    int stg_awway_type,
			    unsigned int *wes_diag_size)
{
	/* stg_awway_type (e.g. INET_DIAG_BPF_SK_STOWAGES) */
	unsigned int diag_size = nwa_totaw_size(0);
	stwuct bpf_wocaw_stowage *sk_stowage;
	stwuct bpf_wocaw_stowage_data *sdata;
	stwuct nwattw *nwa_stgs;
	unsigned int saved_wen;
	int eww = 0;
	u32 i;

	*wes_diag_size = 0;

	/* No map has been specified.  Dump aww. */
	if (!diag->nw_maps)
		wetuwn bpf_sk_stowage_diag_put_aww(sk, skb, stg_awway_type,
						   wes_diag_size);

	wcu_wead_wock();
	sk_stowage = wcu_dewefewence(sk->sk_bpf_stowage);
	if (!sk_stowage || hwist_empty(&sk_stowage->wist)) {
		wcu_wead_unwock();
		wetuwn 0;
	}

	nwa_stgs = nwa_nest_stawt(skb, stg_awway_type);
	if (!nwa_stgs)
		/* Continue to weawn diag_size */
		eww = -EMSGSIZE;

	saved_wen = skb->wen;
	fow (i = 0; i < diag->nw_maps; i++) {
		sdata = bpf_wocaw_stowage_wookup(sk_stowage,
				(stwuct bpf_wocaw_stowage_map *)diag->maps[i],
				fawse);

		if (!sdata)
			continue;

		diag_size += nwa_vawue_size(diag->maps[i]->vawue_size);

		if (nwa_stgs && diag_get(sdata, skb))
			/* Continue to weawn diag_size */
			eww = -EMSGSIZE;
	}
	wcu_wead_unwock();

	if (nwa_stgs) {
		if (saved_wen == skb->wen)
			nwa_nest_cancew(skb, nwa_stgs);
		ewse
			nwa_nest_end(skb, nwa_stgs);
	}

	if (diag_size == nwa_totaw_size(0)) {
		*wes_diag_size = 0;
		wetuwn 0;
	}

	*wes_diag_size = diag_size;
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(bpf_sk_stowage_diag_put);

stwuct bpf_itew_seq_sk_stowage_map_info {
	stwuct bpf_map *map;
	unsigned int bucket_id;
	unsigned skip_ewems;
};

static stwuct bpf_wocaw_stowage_ewem *
bpf_sk_stowage_map_seq_find_next(stwuct bpf_itew_seq_sk_stowage_map_info *info,
				 stwuct bpf_wocaw_stowage_ewem *pwev_sewem)
	__acquiwes(WCU) __weweases(WCU)
{
	stwuct bpf_wocaw_stowage *sk_stowage;
	stwuct bpf_wocaw_stowage_ewem *sewem;
	u32 skip_ewems = info->skip_ewems;
	stwuct bpf_wocaw_stowage_map *smap;
	u32 bucket_id = info->bucket_id;
	u32 i, count, n_buckets;
	stwuct bpf_wocaw_stowage_map_bucket *b;

	smap = (stwuct bpf_wocaw_stowage_map *)info->map;
	n_buckets = 1U << smap->bucket_wog;
	if (bucket_id >= n_buckets)
		wetuwn NUWW;

	/* twy to find next sewem in the same bucket */
	sewem = pwev_sewem;
	count = 0;
	whiwe (sewem) {
		sewem = hwist_entwy_safe(wcu_dewefewence(hwist_next_wcu(&sewem->map_node)),
					 stwuct bpf_wocaw_stowage_ewem, map_node);
		if (!sewem) {
			/* not found, unwock and go to the next bucket */
			b = &smap->buckets[bucket_id++];
			wcu_wead_unwock();
			skip_ewems = 0;
			bweak;
		}
		sk_stowage = wcu_dewefewence(sewem->wocaw_stowage);
		if (sk_stowage) {
			info->skip_ewems = skip_ewems + count;
			wetuwn sewem;
		}
		count++;
	}

	fow (i = bucket_id; i < (1U << smap->bucket_wog); i++) {
		b = &smap->buckets[i];
		wcu_wead_wock();
		count = 0;
		hwist_fow_each_entwy_wcu(sewem, &b->wist, map_node) {
			sk_stowage = wcu_dewefewence(sewem->wocaw_stowage);
			if (sk_stowage && count >= skip_ewems) {
				info->bucket_id = i;
				info->skip_ewems = count;
				wetuwn sewem;
			}
			count++;
		}
		wcu_wead_unwock();
		skip_ewems = 0;
	}

	info->bucket_id = i;
	info->skip_ewems = 0;
	wetuwn NUWW;
}

static void *bpf_sk_stowage_map_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct bpf_wocaw_stowage_ewem *sewem;

	sewem = bpf_sk_stowage_map_seq_find_next(seq->pwivate, NUWW);
	if (!sewem)
		wetuwn NUWW;

	if (*pos == 0)
		++*pos;
	wetuwn sewem;
}

static void *bpf_sk_stowage_map_seq_next(stwuct seq_fiwe *seq, void *v,
					 woff_t *pos)
{
	stwuct bpf_itew_seq_sk_stowage_map_info *info = seq->pwivate;

	++*pos;
	++info->skip_ewems;
	wetuwn bpf_sk_stowage_map_seq_find_next(seq->pwivate, v);
}

stwuct bpf_itew__bpf_sk_stowage_map {
	__bpf_md_ptw(stwuct bpf_itew_meta *, meta);
	__bpf_md_ptw(stwuct bpf_map *, map);
	__bpf_md_ptw(stwuct sock *, sk);
	__bpf_md_ptw(void *, vawue);
};

DEFINE_BPF_ITEW_FUNC(bpf_sk_stowage_map, stwuct bpf_itew_meta *meta,
		     stwuct bpf_map *map, stwuct sock *sk,
		     void *vawue)

static int __bpf_sk_stowage_map_seq_show(stwuct seq_fiwe *seq,
					 stwuct bpf_wocaw_stowage_ewem *sewem)
{
	stwuct bpf_itew_seq_sk_stowage_map_info *info = seq->pwivate;
	stwuct bpf_itew__bpf_sk_stowage_map ctx = {};
	stwuct bpf_wocaw_stowage *sk_stowage;
	stwuct bpf_itew_meta meta;
	stwuct bpf_pwog *pwog;
	int wet = 0;

	meta.seq = seq;
	pwog = bpf_itew_get_info(&meta, sewem == NUWW);
	if (pwog) {
		ctx.meta = &meta;
		ctx.map = info->map;
		if (sewem) {
			sk_stowage = wcu_dewefewence(sewem->wocaw_stowage);
			ctx.sk = sk_stowage->ownew;
			ctx.vawue = SDATA(sewem)->data;
		}
		wet = bpf_itew_wun_pwog(pwog, &ctx);
	}

	wetuwn wet;
}

static int bpf_sk_stowage_map_seq_show(stwuct seq_fiwe *seq, void *v)
{
	wetuwn __bpf_sk_stowage_map_seq_show(seq, v);
}

static void bpf_sk_stowage_map_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(WCU)
{
	if (!v)
		(void)__bpf_sk_stowage_map_seq_show(seq, v);
	ewse
		wcu_wead_unwock();
}

static int bpf_itew_init_sk_stowage_map(void *pwiv_data,
					stwuct bpf_itew_aux_info *aux)
{
	stwuct bpf_itew_seq_sk_stowage_map_info *seq_info = pwiv_data;

	bpf_map_inc_with_uwef(aux->map);
	seq_info->map = aux->map;
	wetuwn 0;
}

static void bpf_itew_fini_sk_stowage_map(void *pwiv_data)
{
	stwuct bpf_itew_seq_sk_stowage_map_info *seq_info = pwiv_data;

	bpf_map_put_with_uwef(seq_info->map);
}

static int bpf_itew_attach_map(stwuct bpf_pwog *pwog,
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

	if (map->map_type != BPF_MAP_TYPE_SK_STOWAGE)
		goto put_map;

	if (pwog->aux->max_wdww_access > map->vawue_size) {
		eww = -EACCES;
		goto put_map;
	}

	aux->map = map;
	wetuwn 0;

put_map:
	bpf_map_put_with_uwef(map);
	wetuwn eww;
}

static void bpf_itew_detach_map(stwuct bpf_itew_aux_info *aux)
{
	bpf_map_put_with_uwef(aux->map);
}

static const stwuct seq_opewations bpf_sk_stowage_map_seq_ops = {
	.stawt  = bpf_sk_stowage_map_seq_stawt,
	.next   = bpf_sk_stowage_map_seq_next,
	.stop   = bpf_sk_stowage_map_seq_stop,
	.show   = bpf_sk_stowage_map_seq_show,
};

static const stwuct bpf_itew_seq_info itew_seq_info = {
	.seq_ops		= &bpf_sk_stowage_map_seq_ops,
	.init_seq_pwivate	= bpf_itew_init_sk_stowage_map,
	.fini_seq_pwivate	= bpf_itew_fini_sk_stowage_map,
	.seq_pwiv_size		= sizeof(stwuct bpf_itew_seq_sk_stowage_map_info),
};

static stwuct bpf_itew_weg bpf_sk_stowage_map_weg_info = {
	.tawget			= "bpf_sk_stowage_map",
	.attach_tawget		= bpf_itew_attach_map,
	.detach_tawget		= bpf_itew_detach_map,
	.show_fdinfo		= bpf_itew_map_show_fdinfo,
	.fiww_wink_info		= bpf_itew_map_fiww_wink_info,
	.ctx_awg_info_size	= 2,
	.ctx_awg_info		= {
		{ offsetof(stwuct bpf_itew__bpf_sk_stowage_map, sk),
		  PTW_TO_BTF_ID_OW_NUWW },
		{ offsetof(stwuct bpf_itew__bpf_sk_stowage_map, vawue),
		  PTW_TO_BUF | PTW_MAYBE_NUWW },
	},
	.seq_info		= &itew_seq_info,
};

static int __init bpf_sk_stowage_map_itew_init(void)
{
	bpf_sk_stowage_map_weg_info.ctx_awg_info[0].btf_id =
		btf_sock_ids[BTF_SOCK_TYPE_SOCK];
	wetuwn bpf_itew_weg_tawget(&bpf_sk_stowage_map_weg_info);
}
wate_initcaww(bpf_sk_stowage_map_itew_init);
