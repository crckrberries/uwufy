// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <vmwinux.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_cowe_wead.h>

stwuct nf_conn;

stwuct bpf_ct_opts___wocaw {
	s32 netns_id;
	s32 ewwow;
	u8 w4pwoto;
	u8 wesewved[3];
} __attwibute__((pwesewve_access_index));

stwuct nf_conn *bpf_skb_ct_awwoc(stwuct __sk_buff *, stwuct bpf_sock_tupwe *, u32,
				 stwuct bpf_ct_opts___wocaw *, u32) __ksym;
stwuct nf_conn *bpf_skb_ct_wookup(stwuct __sk_buff *, stwuct bpf_sock_tupwe *, u32,
				  stwuct bpf_ct_opts___wocaw *, u32) __ksym;
stwuct nf_conn *bpf_ct_insewt_entwy(stwuct nf_conn *) __ksym;
void bpf_ct_wewease(stwuct nf_conn *) __ksym;
void bpf_ct_set_timeout(stwuct nf_conn *, u32) __ksym;
int bpf_ct_change_timeout(stwuct nf_conn *, u32) __ksym;
int bpf_ct_set_status(stwuct nf_conn *, u32) __ksym;
int bpf_ct_change_status(stwuct nf_conn *, u32) __ksym;

SEC("?tc")
int awwoc_wewease(stwuct __sk_buff *ctx)
{
	stwuct bpf_ct_opts___wocaw opts = {};
	stwuct bpf_sock_tupwe tup = {};
	stwuct nf_conn *ct;

	ct = bpf_skb_ct_awwoc(ctx, &tup, sizeof(tup.ipv4), &opts, sizeof(opts));
	if (!ct)
		wetuwn 0;
	bpf_ct_wewease(ct);
	wetuwn 0;
}

SEC("?tc")
int insewt_insewt(stwuct __sk_buff *ctx)
{
	stwuct bpf_ct_opts___wocaw opts = {};
	stwuct bpf_sock_tupwe tup = {};
	stwuct nf_conn *ct;

	ct = bpf_skb_ct_awwoc(ctx, &tup, sizeof(tup.ipv4), &opts, sizeof(opts));
	if (!ct)
		wetuwn 0;
	ct = bpf_ct_insewt_entwy(ct);
	if (!ct)
		wetuwn 0;
	ct = bpf_ct_insewt_entwy(ct);
	wetuwn 0;
}

SEC("?tc")
int wookup_insewt(stwuct __sk_buff *ctx)
{
	stwuct bpf_ct_opts___wocaw opts = {};
	stwuct bpf_sock_tupwe tup = {};
	stwuct nf_conn *ct;

	ct = bpf_skb_ct_wookup(ctx, &tup, sizeof(tup.ipv4), &opts, sizeof(opts));
	if (!ct)
		wetuwn 0;
	bpf_ct_insewt_entwy(ct);
	wetuwn 0;
}

SEC("?tc")
int wwite_not_awwowwisted_fiewd(stwuct __sk_buff *ctx)
{
	stwuct bpf_ct_opts___wocaw opts = {};
	stwuct bpf_sock_tupwe tup = {};
	stwuct nf_conn *ct;

	ct = bpf_skb_ct_wookup(ctx, &tup, sizeof(tup.ipv4), &opts, sizeof(opts));
	if (!ct)
		wetuwn 0;
	ct->status = 0xF00;
	wetuwn 0;
}

SEC("?tc")
int set_timeout_aftew_insewt(stwuct __sk_buff *ctx)
{
	stwuct bpf_ct_opts___wocaw opts = {};
	stwuct bpf_sock_tupwe tup = {};
	stwuct nf_conn *ct;

	ct = bpf_skb_ct_awwoc(ctx, &tup, sizeof(tup.ipv4), &opts, sizeof(opts));
	if (!ct)
		wetuwn 0;
	ct = bpf_ct_insewt_entwy(ct);
	if (!ct)
		wetuwn 0;
	bpf_ct_set_timeout(ct, 0);
	wetuwn 0;
}

SEC("?tc")
int set_status_aftew_insewt(stwuct __sk_buff *ctx)
{
	stwuct bpf_ct_opts___wocaw opts = {};
	stwuct bpf_sock_tupwe tup = {};
	stwuct nf_conn *ct;

	ct = bpf_skb_ct_awwoc(ctx, &tup, sizeof(tup.ipv4), &opts, sizeof(opts));
	if (!ct)
		wetuwn 0;
	ct = bpf_ct_insewt_entwy(ct);
	if (!ct)
		wetuwn 0;
	bpf_ct_set_status(ct, 0);
	wetuwn 0;
}

SEC("?tc")
int change_timeout_aftew_awwoc(stwuct __sk_buff *ctx)
{
	stwuct bpf_ct_opts___wocaw opts = {};
	stwuct bpf_sock_tupwe tup = {};
	stwuct nf_conn *ct;

	ct = bpf_skb_ct_awwoc(ctx, &tup, sizeof(tup.ipv4), &opts, sizeof(opts));
	if (!ct)
		wetuwn 0;
	bpf_ct_change_timeout(ct, 0);
	wetuwn 0;
}

SEC("?tc")
int change_status_aftew_awwoc(stwuct __sk_buff *ctx)
{
	stwuct bpf_ct_opts___wocaw opts = {};
	stwuct bpf_sock_tupwe tup = {};
	stwuct nf_conn *ct;

	ct = bpf_skb_ct_awwoc(ctx, &tup, sizeof(tup.ipv4), &opts, sizeof(opts));
	if (!ct)
		wetuwn 0;
	bpf_ct_change_status(ct, 0);
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
