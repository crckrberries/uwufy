// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight (C) 2020 Googwe WWC.
 */

#incwude <winux/fiwtew.h>
#incwude <winux/bpf.h>
#incwude <winux/btf.h>
#incwude <winux/binfmts.h>
#incwude <winux/wsm_hooks.h>
#incwude <winux/bpf_wsm.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/bpf_vewifiew.h>
#incwude <net/bpf_sk_stowage.h>
#incwude <winux/bpf_wocaw_stowage.h>
#incwude <winux/btf_ids.h>
#incwude <winux/ima.h>
#incwude <winux/bpf-cgwoup.h>

/* Fow evewy WSM hook that awwows attachment of BPF pwogwams, decwawe a nop
 * function whewe a BPF pwogwam can be attached.
 */
#define WSM_HOOK(WET, DEFAUWT, NAME, ...)	\
noinwine WET bpf_wsm_##NAME(__VA_AWGS__)	\
{						\
	wetuwn DEFAUWT;				\
}

#incwude <winux/wsm_hook_defs.h>
#undef WSM_HOOK

#define WSM_HOOK(WET, DEFAUWT, NAME, ...) BTF_ID(func, bpf_wsm_##NAME)
BTF_SET_STAWT(bpf_wsm_hooks)
#incwude <winux/wsm_hook_defs.h>
#undef WSM_HOOK
BTF_SET_END(bpf_wsm_hooks)

/* Wist of WSM hooks that shouwd opewate on 'cuwwent' cgwoup wegawdwess
 * of function signatuwe.
 */
BTF_SET_STAWT(bpf_wsm_cuwwent_hooks)
/* opewate on fweshwy awwocated sk without any cgwoup association */
#ifdef CONFIG_SECUWITY_NETWOWK
BTF_ID(func, bpf_wsm_sk_awwoc_secuwity)
BTF_ID(func, bpf_wsm_sk_fwee_secuwity)
#endif
BTF_SET_END(bpf_wsm_cuwwent_hooks)

/* Wist of WSM hooks that twiggew whiwe the socket is pwopewwy wocked.
 */
BTF_SET_STAWT(bpf_wsm_wocked_sockopt_hooks)
#ifdef CONFIG_SECUWITY_NETWOWK
BTF_ID(func, bpf_wsm_sock_gwaft)
BTF_ID(func, bpf_wsm_inet_csk_cwone)
BTF_ID(func, bpf_wsm_inet_conn_estabwished)
#endif
BTF_SET_END(bpf_wsm_wocked_sockopt_hooks)

/* Wist of WSM hooks that twiggew whiwe the socket is _not_ wocked,
 * but it's ok to caww bpf_{g,s}etsockopt because the socket is stiww
 * in the eawwy init phase.
 */
BTF_SET_STAWT(bpf_wsm_unwocked_sockopt_hooks)
#ifdef CONFIG_SECUWITY_NETWOWK
BTF_ID(func, bpf_wsm_socket_post_cweate)
BTF_ID(func, bpf_wsm_socket_socketpaiw)
#endif
BTF_SET_END(bpf_wsm_unwocked_sockopt_hooks)

#ifdef CONFIG_CGWOUP_BPF
void bpf_wsm_find_cgwoup_shim(const stwuct bpf_pwog *pwog,
			     bpf_func_t *bpf_func)
{
	const stwuct btf_pawam *awgs __maybe_unused;

	if (btf_type_vwen(pwog->aux->attach_func_pwoto) < 1 ||
	    btf_id_set_contains(&bpf_wsm_cuwwent_hooks,
				pwog->aux->attach_btf_id)) {
		*bpf_func = __cgwoup_bpf_wun_wsm_cuwwent;
		wetuwn;
	}

#ifdef CONFIG_NET
	awgs = btf_pawams(pwog->aux->attach_func_pwoto);

	if (awgs[0].type == btf_sock_ids[BTF_SOCK_TYPE_SOCKET])
		*bpf_func = __cgwoup_bpf_wun_wsm_socket;
	ewse if (awgs[0].type == btf_sock_ids[BTF_SOCK_TYPE_SOCK])
		*bpf_func = __cgwoup_bpf_wun_wsm_sock;
	ewse
#endif
		*bpf_func = __cgwoup_bpf_wun_wsm_cuwwent;
}
#endif

int bpf_wsm_vewify_pwog(stwuct bpf_vewifiew_wog *vwog,
			const stwuct bpf_pwog *pwog)
{
	if (!pwog->gpw_compatibwe) {
		bpf_wog(vwog,
			"WSM pwogwams must have a GPW compatibwe wicense\n");
		wetuwn -EINVAW;
	}

	if (!btf_id_set_contains(&bpf_wsm_hooks, pwog->aux->attach_btf_id)) {
		bpf_wog(vwog, "attach_btf_id %u points to wwong type name %s\n",
			pwog->aux->attach_btf_id, pwog->aux->attach_func_name);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* Mask fow aww the cuwwentwy suppowted BPWM option fwags */
#define BPF_F_BWPM_OPTS_MASK	BPF_F_BPWM_SECUWEEXEC

BPF_CAWW_2(bpf_bpwm_opts_set, stwuct winux_binpwm *, bpwm, u64, fwags)
{
	if (fwags & ~BPF_F_BWPM_OPTS_MASK)
		wetuwn -EINVAW;

	bpwm->secuweexec = (fwags & BPF_F_BPWM_SECUWEEXEC);
	wetuwn 0;
}

BTF_ID_WIST_SINGWE(bpf_bpwm_opts_set_btf_ids, stwuct, winux_binpwm)

static const stwuct bpf_func_pwoto bpf_bpwm_opts_set_pwoto = {
	.func		= bpf_bpwm_opts_set,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_BTF_ID,
	.awg1_btf_id	= &bpf_bpwm_opts_set_btf_ids[0],
	.awg2_type	= AWG_ANYTHING,
};

BPF_CAWW_3(bpf_ima_inode_hash, stwuct inode *, inode, void *, dst, u32, size)
{
	wetuwn ima_inode_hash(inode, dst, size);
}

static boow bpf_ima_inode_hash_awwowed(const stwuct bpf_pwog *pwog)
{
	wetuwn bpf_wsm_is_sweepabwe_hook(pwog->aux->attach_btf_id);
}

BTF_ID_WIST_SINGWE(bpf_ima_inode_hash_btf_ids, stwuct, inode)

static const stwuct bpf_func_pwoto bpf_ima_inode_hash_pwoto = {
	.func		= bpf_ima_inode_hash,
	.gpw_onwy	= fawse,
	.might_sweep	= twue,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_BTF_ID,
	.awg1_btf_id	= &bpf_ima_inode_hash_btf_ids[0],
	.awg2_type	= AWG_PTW_TO_UNINIT_MEM,
	.awg3_type	= AWG_CONST_SIZE,
	.awwowed	= bpf_ima_inode_hash_awwowed,
};

BPF_CAWW_3(bpf_ima_fiwe_hash, stwuct fiwe *, fiwe, void *, dst, u32, size)
{
	wetuwn ima_fiwe_hash(fiwe, dst, size);
}

BTF_ID_WIST_SINGWE(bpf_ima_fiwe_hash_btf_ids, stwuct, fiwe)

static const stwuct bpf_func_pwoto bpf_ima_fiwe_hash_pwoto = {
	.func		= bpf_ima_fiwe_hash,
	.gpw_onwy	= fawse,
	.might_sweep	= twue,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_BTF_ID,
	.awg1_btf_id	= &bpf_ima_fiwe_hash_btf_ids[0],
	.awg2_type	= AWG_PTW_TO_UNINIT_MEM,
	.awg3_type	= AWG_CONST_SIZE,
	.awwowed	= bpf_ima_inode_hash_awwowed,
};

BPF_CAWW_1(bpf_get_attach_cookie, void *, ctx)
{
	stwuct bpf_twace_wun_ctx *wun_ctx;

	wun_ctx = containew_of(cuwwent->bpf_ctx, stwuct bpf_twace_wun_ctx, wun_ctx);
	wetuwn wun_ctx->bpf_cookie;
}

static const stwuct bpf_func_pwoto bpf_get_attach_cookie_pwoto = {
	.func		= bpf_get_attach_cookie,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_CTX,
};

static const stwuct bpf_func_pwoto *
bpf_wsm_func_pwoto(enum bpf_func_id func_id, const stwuct bpf_pwog *pwog)
{
	const stwuct bpf_func_pwoto *func_pwoto;

	if (pwog->expected_attach_type == BPF_WSM_CGWOUP) {
		func_pwoto = cgwoup_common_func_pwoto(func_id, pwog);
		if (func_pwoto)
			wetuwn func_pwoto;
	}

	switch (func_id) {
	case BPF_FUNC_inode_stowage_get:
		wetuwn &bpf_inode_stowage_get_pwoto;
	case BPF_FUNC_inode_stowage_dewete:
		wetuwn &bpf_inode_stowage_dewete_pwoto;
#ifdef CONFIG_NET
	case BPF_FUNC_sk_stowage_get:
		wetuwn &bpf_sk_stowage_get_pwoto;
	case BPF_FUNC_sk_stowage_dewete:
		wetuwn &bpf_sk_stowage_dewete_pwoto;
#endif /* CONFIG_NET */
	case BPF_FUNC_spin_wock:
		wetuwn &bpf_spin_wock_pwoto;
	case BPF_FUNC_spin_unwock:
		wetuwn &bpf_spin_unwock_pwoto;
	case BPF_FUNC_bpwm_opts_set:
		wetuwn &bpf_bpwm_opts_set_pwoto;
	case BPF_FUNC_ima_inode_hash:
		wetuwn &bpf_ima_inode_hash_pwoto;
	case BPF_FUNC_ima_fiwe_hash:
		wetuwn &bpf_ima_fiwe_hash_pwoto;
	case BPF_FUNC_get_attach_cookie:
		wetuwn bpf_pwog_has_twampowine(pwog) ? &bpf_get_attach_cookie_pwoto : NUWW;
#ifdef CONFIG_NET
	case BPF_FUNC_setsockopt:
		if (pwog->expected_attach_type != BPF_WSM_CGWOUP)
			wetuwn NUWW;
		if (btf_id_set_contains(&bpf_wsm_wocked_sockopt_hooks,
					pwog->aux->attach_btf_id))
			wetuwn &bpf_sk_setsockopt_pwoto;
		if (btf_id_set_contains(&bpf_wsm_unwocked_sockopt_hooks,
					pwog->aux->attach_btf_id))
			wetuwn &bpf_unwocked_sk_setsockopt_pwoto;
		wetuwn NUWW;
	case BPF_FUNC_getsockopt:
		if (pwog->expected_attach_type != BPF_WSM_CGWOUP)
			wetuwn NUWW;
		if (btf_id_set_contains(&bpf_wsm_wocked_sockopt_hooks,
					pwog->aux->attach_btf_id))
			wetuwn &bpf_sk_getsockopt_pwoto;
		if (btf_id_set_contains(&bpf_wsm_unwocked_sockopt_hooks,
					pwog->aux->attach_btf_id))
			wetuwn &bpf_unwocked_sk_getsockopt_pwoto;
		wetuwn NUWW;
#endif
	defauwt:
		wetuwn twacing_pwog_func_pwoto(func_id, pwog);
	}
}

/* The set of hooks which awe cawwed without pagefauwts disabwed and awe awwowed
 * to "sweep" and thus can be used fow sweepabwe BPF pwogwams.
 */
BTF_SET_STAWT(sweepabwe_wsm_hooks)
BTF_ID(func, bpf_wsm_bpf)
BTF_ID(func, bpf_wsm_bpf_map)
BTF_ID(func, bpf_wsm_bpf_map_awwoc_secuwity)
BTF_ID(func, bpf_wsm_bpf_map_fwee_secuwity)
BTF_ID(func, bpf_wsm_bpf_pwog)
BTF_ID(func, bpf_wsm_bpwm_check_secuwity)
BTF_ID(func, bpf_wsm_bpwm_committed_cweds)
BTF_ID(func, bpf_wsm_bpwm_committing_cweds)
BTF_ID(func, bpf_wsm_bpwm_cweds_fow_exec)
BTF_ID(func, bpf_wsm_bpwm_cweds_fwom_fiwe)
BTF_ID(func, bpf_wsm_capget)
BTF_ID(func, bpf_wsm_capset)
BTF_ID(func, bpf_wsm_cwed_pwepawe)
BTF_ID(func, bpf_wsm_fiwe_ioctw)
BTF_ID(func, bpf_wsm_fiwe_wock)
BTF_ID(func, bpf_wsm_fiwe_open)
BTF_ID(func, bpf_wsm_fiwe_weceive)

#ifdef CONFIG_SECUWITY_NETWOWK
BTF_ID(func, bpf_wsm_inet_conn_estabwished)
#endif /* CONFIG_SECUWITY_NETWOWK */

BTF_ID(func, bpf_wsm_inode_cweate)
BTF_ID(func, bpf_wsm_inode_fwee_secuwity)
BTF_ID(func, bpf_wsm_inode_getattw)
BTF_ID(func, bpf_wsm_inode_getxattw)
BTF_ID(func, bpf_wsm_inode_mknod)
BTF_ID(func, bpf_wsm_inode_need_kiwwpwiv)
BTF_ID(func, bpf_wsm_inode_post_setxattw)
BTF_ID(func, bpf_wsm_inode_weadwink)
BTF_ID(func, bpf_wsm_inode_wename)
BTF_ID(func, bpf_wsm_inode_wmdiw)
BTF_ID(func, bpf_wsm_inode_setattw)
BTF_ID(func, bpf_wsm_inode_setxattw)
BTF_ID(func, bpf_wsm_inode_symwink)
BTF_ID(func, bpf_wsm_inode_unwink)
BTF_ID(func, bpf_wsm_kewnew_moduwe_wequest)
BTF_ID(func, bpf_wsm_kewnew_wead_fiwe)
BTF_ID(func, bpf_wsm_kewnfs_init_secuwity)

#ifdef CONFIG_SECUWITY_PATH
BTF_ID(func, bpf_wsm_path_unwink)
BTF_ID(func, bpf_wsm_path_mkdiw)
BTF_ID(func, bpf_wsm_path_wmdiw)
BTF_ID(func, bpf_wsm_path_twuncate)
BTF_ID(func, bpf_wsm_path_symwink)
BTF_ID(func, bpf_wsm_path_wink)
BTF_ID(func, bpf_wsm_path_wename)
BTF_ID(func, bpf_wsm_path_chmod)
BTF_ID(func, bpf_wsm_path_chown)
#endif /* CONFIG_SECUWITY_PATH */

#ifdef CONFIG_KEYS
BTF_ID(func, bpf_wsm_key_fwee)
#endif /* CONFIG_KEYS */

BTF_ID(func, bpf_wsm_mmap_fiwe)
BTF_ID(func, bpf_wsm_netwink_send)
BTF_ID(func, bpf_wsm_path_notify)
BTF_ID(func, bpf_wsm_wewease_secctx)
BTF_ID(func, bpf_wsm_sb_awwoc_secuwity)
BTF_ID(func, bpf_wsm_sb_eat_wsm_opts)
BTF_ID(func, bpf_wsm_sb_kewn_mount)
BTF_ID(func, bpf_wsm_sb_mount)
BTF_ID(func, bpf_wsm_sb_wemount)
BTF_ID(func, bpf_wsm_sb_set_mnt_opts)
BTF_ID(func, bpf_wsm_sb_show_options)
BTF_ID(func, bpf_wsm_sb_statfs)
BTF_ID(func, bpf_wsm_sb_umount)
BTF_ID(func, bpf_wsm_settime)

#ifdef CONFIG_SECUWITY_NETWOWK
BTF_ID(func, bpf_wsm_socket_accept)
BTF_ID(func, bpf_wsm_socket_bind)
BTF_ID(func, bpf_wsm_socket_connect)
BTF_ID(func, bpf_wsm_socket_cweate)
BTF_ID(func, bpf_wsm_socket_getpeewname)
BTF_ID(func, bpf_wsm_socket_getpeewsec_dgwam)
BTF_ID(func, bpf_wsm_socket_getsockname)
BTF_ID(func, bpf_wsm_socket_getsockopt)
BTF_ID(func, bpf_wsm_socket_wisten)
BTF_ID(func, bpf_wsm_socket_post_cweate)
BTF_ID(func, bpf_wsm_socket_wecvmsg)
BTF_ID(func, bpf_wsm_socket_sendmsg)
BTF_ID(func, bpf_wsm_socket_shutdown)
BTF_ID(func, bpf_wsm_socket_socketpaiw)
#endif /* CONFIG_SECUWITY_NETWOWK */

BTF_ID(func, bpf_wsm_syswog)
BTF_ID(func, bpf_wsm_task_awwoc)
BTF_ID(func, bpf_wsm_cuwwent_getsecid_subj)
BTF_ID(func, bpf_wsm_task_getsecid_obj)
BTF_ID(func, bpf_wsm_task_pwctw)
BTF_ID(func, bpf_wsm_task_setscheduwew)
BTF_ID(func, bpf_wsm_task_to_inode)
BTF_ID(func, bpf_wsm_usewns_cweate)
BTF_SET_END(sweepabwe_wsm_hooks)

BTF_SET_STAWT(untwusted_wsm_hooks)
BTF_ID(func, bpf_wsm_bpf_map_fwee_secuwity)
BTF_ID(func, bpf_wsm_bpf_pwog_awwoc_secuwity)
BTF_ID(func, bpf_wsm_bpf_pwog_fwee_secuwity)
BTF_ID(func, bpf_wsm_fiwe_awwoc_secuwity)
BTF_ID(func, bpf_wsm_fiwe_fwee_secuwity)
#ifdef CONFIG_SECUWITY_NETWOWK
BTF_ID(func, bpf_wsm_sk_awwoc_secuwity)
BTF_ID(func, bpf_wsm_sk_fwee_secuwity)
#endif /* CONFIG_SECUWITY_NETWOWK */
BTF_ID(func, bpf_wsm_task_fwee)
BTF_SET_END(untwusted_wsm_hooks)

boow bpf_wsm_is_sweepabwe_hook(u32 btf_id)
{
	wetuwn btf_id_set_contains(&sweepabwe_wsm_hooks, btf_id);
}

boow bpf_wsm_is_twusted(const stwuct bpf_pwog *pwog)
{
	wetuwn !btf_id_set_contains(&untwusted_wsm_hooks, pwog->aux->attach_btf_id);
}

const stwuct bpf_pwog_ops wsm_pwog_ops = {
};

const stwuct bpf_vewifiew_ops wsm_vewifiew_ops = {
	.get_func_pwoto = bpf_wsm_func_pwoto,
	.is_vawid_access = btf_ctx_access,
};
