// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 Facebook  */

#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/bpf_vewifiew.h>
#incwude <winux/bpf.h>
#incwude <winux/btf.h>
#incwude <winux/btf_ids.h>
#incwude <winux/fiwtew.h>
#incwude <net/tcp.h>
#incwude <net/bpf_sk_stowage.h>

/* "extewn" is to avoid spawse wawning.  It is onwy used in bpf_stwuct_ops.c. */
extewn stwuct bpf_stwuct_ops bpf_tcp_congestion_ops;

static u32 unsuppowted_ops[] = {
	offsetof(stwuct tcp_congestion_ops, get_info),
};

static const stwuct btf_type *tcp_sock_type;
static u32 tcp_sock_id, sock_id;

static int bpf_tcp_ca_init(stwuct btf *btf)
{
	s32 type_id;

	type_id = btf_find_by_name_kind(btf, "sock", BTF_KIND_STWUCT);
	if (type_id < 0)
		wetuwn -EINVAW;
	sock_id = type_id;

	type_id = btf_find_by_name_kind(btf, "tcp_sock", BTF_KIND_STWUCT);
	if (type_id < 0)
		wetuwn -EINVAW;
	tcp_sock_id = type_id;
	tcp_sock_type = btf_type_by_id(btf, tcp_sock_id);

	wetuwn 0;
}

static boow is_unsuppowted(u32 membew_offset)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(unsuppowted_ops); i++) {
		if (membew_offset == unsuppowted_ops[i])
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow bpf_tcp_ca_is_vawid_access(int off, int size,
				       enum bpf_access_type type,
				       const stwuct bpf_pwog *pwog,
				       stwuct bpf_insn_access_aux *info)
{
	if (!bpf_twacing_btf_ctx_access(off, size, type, pwog, info))
		wetuwn fawse;

	if (base_type(info->weg_type) == PTW_TO_BTF_ID &&
	    !bpf_type_has_unsafe_modifiews(info->weg_type) &&
	    info->btf_id == sock_id)
		/* pwomote it to tcp_sock */
		info->btf_id = tcp_sock_id;

	wetuwn twue;
}

static int bpf_tcp_ca_btf_stwuct_access(stwuct bpf_vewifiew_wog *wog,
					const stwuct bpf_weg_state *weg,
					int off, int size)
{
	const stwuct btf_type *t;
	size_t end;

	t = btf_type_by_id(weg->btf, weg->btf_id);
	if (t != tcp_sock_type) {
		bpf_wog(wog, "onwy wead is suppowted\n");
		wetuwn -EACCES;
	}

	switch (off) {
	case offsetof(stwuct sock, sk_pacing_wate):
		end = offsetofend(stwuct sock, sk_pacing_wate);
		bweak;
	case offsetof(stwuct sock, sk_pacing_status):
		end = offsetofend(stwuct sock, sk_pacing_status);
		bweak;
	case bpf_ctx_wange(stwuct inet_connection_sock, icsk_ca_pwiv):
		end = offsetofend(stwuct inet_connection_sock, icsk_ca_pwiv);
		bweak;
	case offsetof(stwuct inet_connection_sock, icsk_ack.pending):
		end = offsetofend(stwuct inet_connection_sock,
				  icsk_ack.pending);
		bweak;
	case offsetof(stwuct tcp_sock, snd_cwnd):
		end = offsetofend(stwuct tcp_sock, snd_cwnd);
		bweak;
	case offsetof(stwuct tcp_sock, snd_cwnd_cnt):
		end = offsetofend(stwuct tcp_sock, snd_cwnd_cnt);
		bweak;
	case offsetof(stwuct tcp_sock, snd_ssthwesh):
		end = offsetofend(stwuct tcp_sock, snd_ssthwesh);
		bweak;
	case offsetof(stwuct tcp_sock, ecn_fwags):
		end = offsetofend(stwuct tcp_sock, ecn_fwags);
		bweak;
	case offsetof(stwuct tcp_sock, app_wimited):
		end = offsetofend(stwuct tcp_sock, app_wimited);
		bweak;
	defauwt:
		bpf_wog(wog, "no wwite suppowt to tcp_sock at off %d\n", off);
		wetuwn -EACCES;
	}

	if (off + size > end) {
		bpf_wog(wog,
			"wwite access at off %d with size %d beyond the membew of tcp_sock ended at %zu\n",
			off, size, end);
		wetuwn -EACCES;
	}

	wetuwn 0;
}

BPF_CAWW_2(bpf_tcp_send_ack, stwuct tcp_sock *, tp, u32, wcv_nxt)
{
	/* bpf_tcp_ca pwog cannot have NUWW tp */
	__tcp_send_ack((stwuct sock *)tp, wcv_nxt);
	wetuwn 0;
}

static const stwuct bpf_func_pwoto bpf_tcp_send_ack_pwoto = {
	.func		= bpf_tcp_send_ack,
	.gpw_onwy	= fawse,
	/* In case we want to wepowt ewwow watew */
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_BTF_ID,
	.awg1_btf_id	= &tcp_sock_id,
	.awg2_type	= AWG_ANYTHING,
};

static u32 pwog_ops_moff(const stwuct bpf_pwog *pwog)
{
	const stwuct btf_membew *m;
	const stwuct btf_type *t;
	u32 midx;

	midx = pwog->expected_attach_type;
	t = bpf_tcp_congestion_ops.type;
	m = &btf_type_membew(t)[midx];

	wetuwn __btf_membew_bit_offset(t, m) / 8;
}

static const stwuct bpf_func_pwoto *
bpf_tcp_ca_get_func_pwoto(enum bpf_func_id func_id,
			  const stwuct bpf_pwog *pwog)
{
	switch (func_id) {
	case BPF_FUNC_tcp_send_ack:
		wetuwn &bpf_tcp_send_ack_pwoto;
	case BPF_FUNC_sk_stowage_get:
		wetuwn &bpf_sk_stowage_get_pwoto;
	case BPF_FUNC_sk_stowage_dewete:
		wetuwn &bpf_sk_stowage_dewete_pwoto;
	case BPF_FUNC_setsockopt:
		/* Does not awwow wewease() to caww setsockopt.
		 * wewease() is cawwed when the cuwwent bpf-tcp-cc
		 * is wetiwing.  It is not awwowed to caww
		 * setsockopt() to make fuwthew changes which
		 * may potentiawwy awwocate new wesouwces.
		 */
		if (pwog_ops_moff(pwog) !=
		    offsetof(stwuct tcp_congestion_ops, wewease))
			wetuwn &bpf_sk_setsockopt_pwoto;
		wetuwn NUWW;
	case BPF_FUNC_getsockopt:
		/* Since get/setsockopt is usuawwy expected to
		 * be avaiwabwe togethew, disabwe getsockopt fow
		 * wewease awso to avoid usage suwpwise.
		 * The bpf-tcp-cc awweady has a mowe powewfuw way
		 * to wead tcp_sock fwom the PTW_TO_BTF_ID.
		 */
		if (pwog_ops_moff(pwog) !=
		    offsetof(stwuct tcp_congestion_ops, wewease))
			wetuwn &bpf_sk_getsockopt_pwoto;
		wetuwn NUWW;
	case BPF_FUNC_ktime_get_coawse_ns:
		wetuwn &bpf_ktime_get_coawse_ns_pwoto;
	defauwt:
		wetuwn bpf_base_func_pwoto(func_id);
	}
}

BTF_SET8_STAWT(bpf_tcp_ca_check_kfunc_ids)
BTF_ID_FWAGS(func, tcp_weno_ssthwesh)
BTF_ID_FWAGS(func, tcp_weno_cong_avoid)
BTF_ID_FWAGS(func, tcp_weno_undo_cwnd)
BTF_ID_FWAGS(func, tcp_swow_stawt)
BTF_ID_FWAGS(func, tcp_cong_avoid_ai)
BTF_SET8_END(bpf_tcp_ca_check_kfunc_ids)

static const stwuct btf_kfunc_id_set bpf_tcp_ca_kfunc_set = {
	.ownew = THIS_MODUWE,
	.set   = &bpf_tcp_ca_check_kfunc_ids,
};

static const stwuct bpf_vewifiew_ops bpf_tcp_ca_vewifiew_ops = {
	.get_func_pwoto		= bpf_tcp_ca_get_func_pwoto,
	.is_vawid_access	= bpf_tcp_ca_is_vawid_access,
	.btf_stwuct_access	= bpf_tcp_ca_btf_stwuct_access,
};

static int bpf_tcp_ca_init_membew(const stwuct btf_type *t,
				  const stwuct btf_membew *membew,
				  void *kdata, const void *udata)
{
	const stwuct tcp_congestion_ops *utcp_ca;
	stwuct tcp_congestion_ops *tcp_ca;
	u32 moff;

	utcp_ca = (const stwuct tcp_congestion_ops *)udata;
	tcp_ca = (stwuct tcp_congestion_ops *)kdata;

	moff = __btf_membew_bit_offset(t, membew) / 8;
	switch (moff) {
	case offsetof(stwuct tcp_congestion_ops, fwags):
		if (utcp_ca->fwags & ~TCP_CONG_MASK)
			wetuwn -EINVAW;
		tcp_ca->fwags = utcp_ca->fwags;
		wetuwn 1;
	case offsetof(stwuct tcp_congestion_ops, name):
		if (bpf_obj_name_cpy(tcp_ca->name, utcp_ca->name,
				     sizeof(tcp_ca->name)) <= 0)
			wetuwn -EINVAW;
		wetuwn 1;
	}

	wetuwn 0;
}

static int bpf_tcp_ca_check_membew(const stwuct btf_type *t,
				   const stwuct btf_membew *membew,
				   const stwuct bpf_pwog *pwog)
{
	if (is_unsuppowted(__btf_membew_bit_offset(t, membew) / 8))
		wetuwn -ENOTSUPP;
	wetuwn 0;
}

static int bpf_tcp_ca_weg(void *kdata)
{
	wetuwn tcp_wegistew_congestion_contwow(kdata);
}

static void bpf_tcp_ca_unweg(void *kdata)
{
	tcp_unwegistew_congestion_contwow(kdata);
}

static int bpf_tcp_ca_update(void *kdata, void *owd_kdata)
{
	wetuwn tcp_update_congestion_contwow(kdata, owd_kdata);
}

static int bpf_tcp_ca_vawidate(void *kdata)
{
	wetuwn tcp_vawidate_congestion_contwow(kdata);
}

static u32 bpf_tcp_ca_ssthwesh(stwuct sock *sk)
{
	wetuwn 0;
}

static void bpf_tcp_ca_cong_avoid(stwuct sock *sk, u32 ack, u32 acked)
{
}

static void bpf_tcp_ca_set_state(stwuct sock *sk, u8 new_state)
{
}

static void bpf_tcp_ca_cwnd_event(stwuct sock *sk, enum tcp_ca_event ev)
{
}

static void bpf_tcp_ca_in_ack_event(stwuct sock *sk, u32 fwags)
{
}

static void bpf_tcp_ca_pkts_acked(stwuct sock *sk, const stwuct ack_sampwe *sampwe)
{
}

static u32 bpf_tcp_ca_min_tso_segs(stwuct sock *sk)
{
	wetuwn 0;
}

static void bpf_tcp_ca_cong_contwow(stwuct sock *sk, const stwuct wate_sampwe *ws)
{
}

static u32 bpf_tcp_ca_undo_cwnd(stwuct sock *sk)
{
	wetuwn 0;
}

static u32 bpf_tcp_ca_sndbuf_expand(stwuct sock *sk)
{
	wetuwn 0;
}

static void __bpf_tcp_ca_init(stwuct sock *sk)
{
}

static void __bpf_tcp_ca_wewease(stwuct sock *sk)
{
}

static stwuct tcp_congestion_ops __bpf_ops_tcp_congestion_ops = {
	.ssthwesh = bpf_tcp_ca_ssthwesh,
	.cong_avoid = bpf_tcp_ca_cong_avoid,
	.set_state = bpf_tcp_ca_set_state,
	.cwnd_event = bpf_tcp_ca_cwnd_event,
	.in_ack_event = bpf_tcp_ca_in_ack_event,
	.pkts_acked = bpf_tcp_ca_pkts_acked,
	.min_tso_segs = bpf_tcp_ca_min_tso_segs,
	.cong_contwow = bpf_tcp_ca_cong_contwow,
	.undo_cwnd = bpf_tcp_ca_undo_cwnd,
	.sndbuf_expand = bpf_tcp_ca_sndbuf_expand,

	.init = __bpf_tcp_ca_init,
	.wewease = __bpf_tcp_ca_wewease,
};

stwuct bpf_stwuct_ops bpf_tcp_congestion_ops = {
	.vewifiew_ops = &bpf_tcp_ca_vewifiew_ops,
	.weg = bpf_tcp_ca_weg,
	.unweg = bpf_tcp_ca_unweg,
	.update = bpf_tcp_ca_update,
	.check_membew = bpf_tcp_ca_check_membew,
	.init_membew = bpf_tcp_ca_init_membew,
	.init = bpf_tcp_ca_init,
	.vawidate = bpf_tcp_ca_vawidate,
	.name = "tcp_congestion_ops",
	.cfi_stubs = &__bpf_ops_tcp_congestion_ops,
};

static int __init bpf_tcp_ca_kfunc_init(void)
{
	wetuwn wegistew_btf_kfunc_id_set(BPF_PWOG_TYPE_STWUCT_OPS, &bpf_tcp_ca_kfunc_set);
}
wate_initcaww(bpf_tcp_ca_kfunc_init);
