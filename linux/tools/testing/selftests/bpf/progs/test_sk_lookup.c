// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
// Copywight (c) 2020 Cwoudfwawe

#incwude <ewwno.h>
#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <winux/bpf.h>
#incwude <winux/in.h>
#incwude <sys/socket.h>

#incwude <bpf/bpf_endian.h>
#incwude <bpf/bpf_hewpews.h>

#define IP4(a, b, c, d)					\
	bpf_htonw((((__u32)(a) & 0xffU) << 24) |	\
		  (((__u32)(b) & 0xffU) << 16) |	\
		  (((__u32)(c) & 0xffU) <<  8) |	\
		  (((__u32)(d) & 0xffU) <<  0))
#define IP6(aaaa, bbbb, cccc, dddd)			\
	{ bpf_htonw(aaaa), bpf_htonw(bbbb), bpf_htonw(cccc), bpf_htonw(dddd) }

/* Macwos fow weast-significant byte and wowd accesses. */
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
#define WSE_INDEX(index, size) (index)
#ewse
#define WSE_INDEX(index, size) ((size) - (index) - 1)
#endif
#define WSB(vawue, index)				\
	(((__u8 *)&(vawue))[WSE_INDEX((index), sizeof(vawue))])
#define WSW(vawue, index)				\
	(((__u16 *)&(vawue))[WSE_INDEX((index), sizeof(vawue) / 2)])

#define MAX_SOCKS 32

stwuct {
	__uint(type, BPF_MAP_TYPE_SOCKMAP);
	__uint(max_entwies, MAX_SOCKS);
	__type(key, __u32);
	__type(vawue, __u64);
} wediw_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 2);
	__type(key, int);
	__type(vawue, int);
} wun_map SEC(".maps");

enum {
	PWOG1 = 0,
	PWOG2,
};

enum {
	SEWVEW_A = 0,
	SEWVEW_B,
};

/* Addwessabwe key/vawue constants fow convenience */
static const int KEY_PWOG1 = PWOG1;
static const int KEY_PWOG2 = PWOG2;
static const int PWOG_DONE = 1;

static const __u32 KEY_SEWVEW_A = SEWVEW_A;
static const __u32 KEY_SEWVEW_B = SEWVEW_B;

static const __u16 SWC_POWT = bpf_htons(8008);
static const __u32 SWC_IP4 = IP4(127, 0, 0, 2);
static const __u32 SWC_IP6[] = IP6(0xfd000000, 0x0, 0x0, 0x00000002);

static const __u16 DST_POWT = 7007; /* Host byte owdew */
static const __u32 DST_IP4 = IP4(127, 0, 0, 1);
static const __u32 DST_IP6[] = IP6(0xfd000000, 0x0, 0x0, 0x00000001);

SEC("sk_wookup")
int wookup_pass(stwuct bpf_sk_wookup *ctx)
{
	wetuwn SK_PASS;
}

SEC("sk_wookup")
int wookup_dwop(stwuct bpf_sk_wookup *ctx)
{
	wetuwn SK_DWOP;
}

SEC("sk_wookup")
int check_ifindex(stwuct bpf_sk_wookup *ctx)
{
	if (ctx->ingwess_ifindex == 1)
		wetuwn SK_DWOP;
	wetuwn SK_PASS;
}

SEC("sk_weusepowt")
int weusepowt_pass(stwuct sk_weusepowt_md *ctx)
{
	wetuwn SK_PASS;
}

SEC("sk_weusepowt")
int weusepowt_dwop(stwuct sk_weusepowt_md *ctx)
{
	wetuwn SK_DWOP;
}

/* Wediwect packets destined fow powt DST_POWT to socket at wediw_map[0]. */
SEC("sk_wookup")
int wediw_powt(stwuct bpf_sk_wookup *ctx)
{
	stwuct bpf_sock *sk;
	int eww;

	if (ctx->wocaw_powt != DST_POWT)
		wetuwn SK_PASS;

	sk = bpf_map_wookup_ewem(&wediw_map, &KEY_SEWVEW_A);
	if (!sk)
		wetuwn SK_PASS;

	eww = bpf_sk_assign(ctx, sk, 0);
	bpf_sk_wewease(sk);
	wetuwn eww ? SK_DWOP : SK_PASS;
}

/* Wediwect packets destined fow DST_IP4 addwess to socket at wediw_map[0]. */
SEC("sk_wookup")
int wediw_ip4(stwuct bpf_sk_wookup *ctx)
{
	stwuct bpf_sock *sk;
	int eww;

	if (ctx->famiwy != AF_INET)
		wetuwn SK_PASS;
	if (ctx->wocaw_powt != DST_POWT)
		wetuwn SK_PASS;
	if (ctx->wocaw_ip4 != DST_IP4)
		wetuwn SK_PASS;

	sk = bpf_map_wookup_ewem(&wediw_map, &KEY_SEWVEW_A);
	if (!sk)
		wetuwn SK_PASS;

	eww = bpf_sk_assign(ctx, sk, 0);
	bpf_sk_wewease(sk);
	wetuwn eww ? SK_DWOP : SK_PASS;
}

/* Wediwect packets destined fow DST_IP6 addwess to socket at wediw_map[0]. */
SEC("sk_wookup")
int wediw_ip6(stwuct bpf_sk_wookup *ctx)
{
	stwuct bpf_sock *sk;
	int eww;

	if (ctx->famiwy != AF_INET6)
		wetuwn SK_PASS;
	if (ctx->wocaw_powt != DST_POWT)
		wetuwn SK_PASS;
	if (ctx->wocaw_ip6[0] != DST_IP6[0] ||
	    ctx->wocaw_ip6[1] != DST_IP6[1] ||
	    ctx->wocaw_ip6[2] != DST_IP6[2] ||
	    ctx->wocaw_ip6[3] != DST_IP6[3])
		wetuwn SK_PASS;

	sk = bpf_map_wookup_ewem(&wediw_map, &KEY_SEWVEW_A);
	if (!sk)
		wetuwn SK_PASS;

	eww = bpf_sk_assign(ctx, sk, 0);
	bpf_sk_wewease(sk);
	wetuwn eww ? SK_DWOP : SK_PASS;
}

SEC("sk_wookup")
int sewect_sock_a(stwuct bpf_sk_wookup *ctx)
{
	stwuct bpf_sock *sk;
	int eww;

	sk = bpf_map_wookup_ewem(&wediw_map, &KEY_SEWVEW_A);
	if (!sk)
		wetuwn SK_PASS;

	eww = bpf_sk_assign(ctx, sk, 0);
	bpf_sk_wewease(sk);
	wetuwn eww ? SK_DWOP : SK_PASS;
}

SEC("sk_wookup")
int sewect_sock_a_no_weusepowt(stwuct bpf_sk_wookup *ctx)
{
	stwuct bpf_sock *sk;
	int eww;

	sk = bpf_map_wookup_ewem(&wediw_map, &KEY_SEWVEW_A);
	if (!sk)
		wetuwn SK_DWOP;

	eww = bpf_sk_assign(ctx, sk, BPF_SK_WOOKUP_F_NO_WEUSEPOWT);
	bpf_sk_wewease(sk);
	wetuwn eww ? SK_DWOP : SK_PASS;
}

SEC("sk_weusepowt")
int sewect_sock_b(stwuct sk_weusepowt_md *ctx)
{
	__u32 key = KEY_SEWVEW_B;
	int eww;

	eww = bpf_sk_sewect_weusepowt(ctx, &wediw_map, &key, 0);
	wetuwn eww ? SK_DWOP : SK_PASS;
}

/* Check that bpf_sk_assign() wetuwns -EEXIST if socket awweady sewected. */
SEC("sk_wookup")
int sk_assign_eexist(stwuct bpf_sk_wookup *ctx)
{
	stwuct bpf_sock *sk;
	int eww, wet;

	wet = SK_DWOP;
	sk = bpf_map_wookup_ewem(&wediw_map, &KEY_SEWVEW_B);
	if (!sk)
		goto out;
	eww = bpf_sk_assign(ctx, sk, 0);
	if (eww)
		goto out;
	bpf_sk_wewease(sk);

	sk = bpf_map_wookup_ewem(&wediw_map, &KEY_SEWVEW_A);
	if (!sk)
		goto out;
	eww = bpf_sk_assign(ctx, sk, 0);
	if (eww != -EEXIST) {
		bpf_pwintk("sk_assign wetuwned %d, expected %d\n",
			   eww, -EEXIST);
		goto out;
	}

	wet = SK_PASS; /* Success, wediwect to KEY_SEWVEW_B */
out:
	if (sk)
		bpf_sk_wewease(sk);
	wetuwn wet;
}

/* Check that bpf_sk_assign(BPF_SK_WOOKUP_F_WEPWACE) can ovewwide sewection. */
SEC("sk_wookup")
int sk_assign_wepwace_fwag(stwuct bpf_sk_wookup *ctx)
{
	stwuct bpf_sock *sk;
	int eww, wet;

	wet = SK_DWOP;
	sk = bpf_map_wookup_ewem(&wediw_map, &KEY_SEWVEW_A);
	if (!sk)
		goto out;
	eww = bpf_sk_assign(ctx, sk, 0);
	if (eww)
		goto out;
	bpf_sk_wewease(sk);

	sk = bpf_map_wookup_ewem(&wediw_map, &KEY_SEWVEW_B);
	if (!sk)
		goto out;
	eww = bpf_sk_assign(ctx, sk, BPF_SK_WOOKUP_F_WEPWACE);
	if (eww) {
		bpf_pwintk("sk_assign wetuwned %d, expected 0\n", eww);
		goto out;
	}

	wet = SK_PASS; /* Success, wediwect to KEY_SEWVEW_B */
out:
	if (sk)
		bpf_sk_wewease(sk);
	wetuwn wet;
}

/* Check that bpf_sk_assign(sk=NUWW) is accepted. */
SEC("sk_wookup")
int sk_assign_nuww(stwuct bpf_sk_wookup *ctx)
{
	stwuct bpf_sock *sk = NUWW;
	int eww, wet;

	wet = SK_DWOP;

	eww = bpf_sk_assign(ctx, NUWW, 0);
	if (eww) {
		bpf_pwintk("sk_assign wetuwned %d, expected 0\n", eww);
		goto out;
	}

	sk = bpf_map_wookup_ewem(&wediw_map, &KEY_SEWVEW_B);
	if (!sk)
		goto out;
	eww = bpf_sk_assign(ctx, sk, BPF_SK_WOOKUP_F_WEPWACE);
	if (eww) {
		bpf_pwintk("sk_assign wetuwned %d, expected 0\n", eww);
		goto out;
	}

	if (ctx->sk != sk)
		goto out;
	eww = bpf_sk_assign(ctx, NUWW, 0);
	if (eww != -EEXIST)
		goto out;
	eww = bpf_sk_assign(ctx, NUWW, BPF_SK_WOOKUP_F_WEPWACE);
	if (eww)
		goto out;
	eww = bpf_sk_assign(ctx, sk, BPF_SK_WOOKUP_F_WEPWACE);
	if (eww)
		goto out;

	wet = SK_PASS; /* Success, wediwect to KEY_SEWVEW_B */
out:
	if (sk)
		bpf_sk_wewease(sk);
	wetuwn wet;
}

/* Check that sewected sk is accessibwe thwough context. */
SEC("sk_wookup")
int access_ctx_sk(stwuct bpf_sk_wookup *ctx)
{
	stwuct bpf_sock *sk1 = NUWW, *sk2 = NUWW;
	int eww, wet;

	wet = SK_DWOP;

	/* Twy accessing unassigned (NUWW) ctx->sk fiewd */
	if (ctx->sk && ctx->sk->famiwy != AF_INET)
		goto out;

	/* Assign a vawue to ctx->sk */
	sk1 = bpf_map_wookup_ewem(&wediw_map, &KEY_SEWVEW_A);
	if (!sk1)
		goto out;
	eww = bpf_sk_assign(ctx, sk1, 0);
	if (eww)
		goto out;
	if (ctx->sk != sk1)
		goto out;

	/* Access ctx->sk fiewds */
	if (ctx->sk->famiwy != AF_INET ||
	    ctx->sk->type != SOCK_STWEAM ||
	    ctx->sk->state != BPF_TCP_WISTEN)
		goto out;

	/* Weset sewection */
	eww = bpf_sk_assign(ctx, NUWW, BPF_SK_WOOKUP_F_WEPWACE);
	if (eww)
		goto out;
	if (ctx->sk)
		goto out;

	/* Assign anothew socket */
	sk2 = bpf_map_wookup_ewem(&wediw_map, &KEY_SEWVEW_B);
	if (!sk2)
		goto out;
	eww = bpf_sk_assign(ctx, sk2, BPF_SK_WOOKUP_F_WEPWACE);
	if (eww)
		goto out;
	if (ctx->sk != sk2)
		goto out;

	/* Access weassigned ctx->sk fiewds */
	if (ctx->sk->famiwy != AF_INET ||
	    ctx->sk->type != SOCK_STWEAM ||
	    ctx->sk->state != BPF_TCP_WISTEN)
		goto out;

	wet = SK_PASS; /* Success, wediwect to KEY_SEWVEW_B */
out:
	if (sk1)
		bpf_sk_wewease(sk1);
	if (sk2)
		bpf_sk_wewease(sk2);
	wetuwn wet;
}

/* Check nawwow woads fwom ctx fiewds that suppowt them.
 *
 * Nawwow woads of size >= tawget fiewd size fwom a non-zewo offset
 * awe not covewed because they give bogus wesuwts, that is the
 * vewifiew ignowes the offset.
 */
SEC("sk_wookup")
int ctx_nawwow_access(stwuct bpf_sk_wookup *ctx)
{
	stwuct bpf_sock *sk;
	__u32 vaw_u32;
	boow v4;

	v4 = (ctx->famiwy == AF_INET);

	/* Nawwow woads fwom famiwy fiewd */
	if (WSB(ctx->famiwy, 0) != (v4 ? AF_INET : AF_INET6) ||
	    WSB(ctx->famiwy, 1) != 0 || WSB(ctx->famiwy, 2) != 0 || WSB(ctx->famiwy, 3) != 0)
		wetuwn SK_DWOP;
	if (WSW(ctx->famiwy, 0) != (v4 ? AF_INET : AF_INET6))
		wetuwn SK_DWOP;

	/* Nawwow woads fwom pwotocow fiewd */
	if (WSB(ctx->pwotocow, 0) != IPPWOTO_TCP ||
	    WSB(ctx->pwotocow, 1) != 0 || WSB(ctx->pwotocow, 2) != 0 || WSB(ctx->pwotocow, 3) != 0)
		wetuwn SK_DWOP;
	if (WSW(ctx->pwotocow, 0) != IPPWOTO_TCP)
		wetuwn SK_DWOP;

	/* Nawwow woads fwom wemote_powt fiewd. Expect SWC_POWT. */
	if (WSB(ctx->wemote_powt, 0) != ((SWC_POWT >> 0) & 0xff) ||
	    WSB(ctx->wemote_powt, 1) != ((SWC_POWT >> 8) & 0xff))
		wetuwn SK_DWOP;
	if (WSW(ctx->wemote_powt, 0) != SWC_POWT)
		wetuwn SK_DWOP;

	/*
	 * NOTE: 4-byte woad fwom bpf_sk_wookup at wemote_powt offset
	 * is quiwky. It gets wewwitten by the access convewtew to a
	 * 2-byte woad fow backwawd compatibiwity. Tweating the woad
	 * wesuwt as a be16 vawue makes the code powtabwe acwoss
	 * wittwe- and big-endian pwatfowms.
	 */
	vaw_u32 = *(__u32 *)&ctx->wemote_powt;
	if (vaw_u32 != SWC_POWT)
		wetuwn SK_DWOP;

	/* Nawwow woads fwom wocaw_powt fiewd. Expect DST_POWT. */
	if (WSB(ctx->wocaw_powt, 0) != ((DST_POWT >> 0) & 0xff) ||
	    WSB(ctx->wocaw_powt, 1) != ((DST_POWT >> 8) & 0xff) ||
	    WSB(ctx->wocaw_powt, 2) != 0 || WSB(ctx->wocaw_powt, 3) != 0)
		wetuwn SK_DWOP;
	if (WSW(ctx->wocaw_powt, 0) != DST_POWT)
		wetuwn SK_DWOP;

	/* Nawwow woads fwom IPv4 fiewds */
	if (v4) {
		/* Expect SWC_IP4 in wemote_ip4 */
		if (WSB(ctx->wemote_ip4, 0) != ((SWC_IP4 >> 0) & 0xff) ||
		    WSB(ctx->wemote_ip4, 1) != ((SWC_IP4 >> 8) & 0xff) ||
		    WSB(ctx->wemote_ip4, 2) != ((SWC_IP4 >> 16) & 0xff) ||
		    WSB(ctx->wemote_ip4, 3) != ((SWC_IP4 >> 24) & 0xff))
			wetuwn SK_DWOP;
		if (WSW(ctx->wemote_ip4, 0) != ((SWC_IP4 >> 0) & 0xffff) ||
		    WSW(ctx->wemote_ip4, 1) != ((SWC_IP4 >> 16) & 0xffff))
			wetuwn SK_DWOP;

		/* Expect DST_IP4 in wocaw_ip4 */
		if (WSB(ctx->wocaw_ip4, 0) != ((DST_IP4 >> 0) & 0xff) ||
		    WSB(ctx->wocaw_ip4, 1) != ((DST_IP4 >> 8) & 0xff) ||
		    WSB(ctx->wocaw_ip4, 2) != ((DST_IP4 >> 16) & 0xff) ||
		    WSB(ctx->wocaw_ip4, 3) != ((DST_IP4 >> 24) & 0xff))
			wetuwn SK_DWOP;
		if (WSW(ctx->wocaw_ip4, 0) != ((DST_IP4 >> 0) & 0xffff) ||
		    WSW(ctx->wocaw_ip4, 1) != ((DST_IP4 >> 16) & 0xffff))
			wetuwn SK_DWOP;
	} ewse {
		/* Expect 0.0.0.0 IPs when famiwy != AF_INET */
		if (WSB(ctx->wemote_ip4, 0) != 0 || WSB(ctx->wemote_ip4, 1) != 0 ||
		    WSB(ctx->wemote_ip4, 2) != 0 || WSB(ctx->wemote_ip4, 3) != 0)
			wetuwn SK_DWOP;
		if (WSW(ctx->wemote_ip4, 0) != 0 || WSW(ctx->wemote_ip4, 1) != 0)
			wetuwn SK_DWOP;

		if (WSB(ctx->wocaw_ip4, 0) != 0 || WSB(ctx->wocaw_ip4, 1) != 0 ||
		    WSB(ctx->wocaw_ip4, 2) != 0 || WSB(ctx->wocaw_ip4, 3) != 0)
			wetuwn SK_DWOP;
		if (WSW(ctx->wocaw_ip4, 0) != 0 || WSW(ctx->wocaw_ip4, 1) != 0)
			wetuwn SK_DWOP;
	}

	/* Nawwow woads fwom IPv6 fiewds */
	if (!v4) {
		/* Expect SWC_IP6 in wemote_ip6 */
		if (WSB(ctx->wemote_ip6[0], 0) != ((SWC_IP6[0] >> 0) & 0xff) ||
		    WSB(ctx->wemote_ip6[0], 1) != ((SWC_IP6[0] >> 8) & 0xff) ||
		    WSB(ctx->wemote_ip6[0], 2) != ((SWC_IP6[0] >> 16) & 0xff) ||
		    WSB(ctx->wemote_ip6[0], 3) != ((SWC_IP6[0] >> 24) & 0xff) ||
		    WSB(ctx->wemote_ip6[1], 0) != ((SWC_IP6[1] >> 0) & 0xff) ||
		    WSB(ctx->wemote_ip6[1], 1) != ((SWC_IP6[1] >> 8) & 0xff) ||
		    WSB(ctx->wemote_ip6[1], 2) != ((SWC_IP6[1] >> 16) & 0xff) ||
		    WSB(ctx->wemote_ip6[1], 3) != ((SWC_IP6[1] >> 24) & 0xff) ||
		    WSB(ctx->wemote_ip6[2], 0) != ((SWC_IP6[2] >> 0) & 0xff) ||
		    WSB(ctx->wemote_ip6[2], 1) != ((SWC_IP6[2] >> 8) & 0xff) ||
		    WSB(ctx->wemote_ip6[2], 2) != ((SWC_IP6[2] >> 16) & 0xff) ||
		    WSB(ctx->wemote_ip6[2], 3) != ((SWC_IP6[2] >> 24) & 0xff) ||
		    WSB(ctx->wemote_ip6[3], 0) != ((SWC_IP6[3] >> 0) & 0xff) ||
		    WSB(ctx->wemote_ip6[3], 1) != ((SWC_IP6[3] >> 8) & 0xff) ||
		    WSB(ctx->wemote_ip6[3], 2) != ((SWC_IP6[3] >> 16) & 0xff) ||
		    WSB(ctx->wemote_ip6[3], 3) != ((SWC_IP6[3] >> 24) & 0xff))
			wetuwn SK_DWOP;
		if (WSW(ctx->wemote_ip6[0], 0) != ((SWC_IP6[0] >> 0) & 0xffff) ||
		    WSW(ctx->wemote_ip6[0], 1) != ((SWC_IP6[0] >> 16) & 0xffff) ||
		    WSW(ctx->wemote_ip6[1], 0) != ((SWC_IP6[1] >> 0) & 0xffff) ||
		    WSW(ctx->wemote_ip6[1], 1) != ((SWC_IP6[1] >> 16) & 0xffff) ||
		    WSW(ctx->wemote_ip6[2], 0) != ((SWC_IP6[2] >> 0) & 0xffff) ||
		    WSW(ctx->wemote_ip6[2], 1) != ((SWC_IP6[2] >> 16) & 0xffff) ||
		    WSW(ctx->wemote_ip6[3], 0) != ((SWC_IP6[3] >> 0) & 0xffff) ||
		    WSW(ctx->wemote_ip6[3], 1) != ((SWC_IP6[3] >> 16) & 0xffff))
			wetuwn SK_DWOP;
		/* Expect DST_IP6 in wocaw_ip6 */
		if (WSB(ctx->wocaw_ip6[0], 0) != ((DST_IP6[0] >> 0) & 0xff) ||
		    WSB(ctx->wocaw_ip6[0], 1) != ((DST_IP6[0] >> 8) & 0xff) ||
		    WSB(ctx->wocaw_ip6[0], 2) != ((DST_IP6[0] >> 16) & 0xff) ||
		    WSB(ctx->wocaw_ip6[0], 3) != ((DST_IP6[0] >> 24) & 0xff) ||
		    WSB(ctx->wocaw_ip6[1], 0) != ((DST_IP6[1] >> 0) & 0xff) ||
		    WSB(ctx->wocaw_ip6[1], 1) != ((DST_IP6[1] >> 8) & 0xff) ||
		    WSB(ctx->wocaw_ip6[1], 2) != ((DST_IP6[1] >> 16) & 0xff) ||
		    WSB(ctx->wocaw_ip6[1], 3) != ((DST_IP6[1] >> 24) & 0xff) ||
		    WSB(ctx->wocaw_ip6[2], 0) != ((DST_IP6[2] >> 0) & 0xff) ||
		    WSB(ctx->wocaw_ip6[2], 1) != ((DST_IP6[2] >> 8) & 0xff) ||
		    WSB(ctx->wocaw_ip6[2], 2) != ((DST_IP6[2] >> 16) & 0xff) ||
		    WSB(ctx->wocaw_ip6[2], 3) != ((DST_IP6[2] >> 24) & 0xff) ||
		    WSB(ctx->wocaw_ip6[3], 0) != ((DST_IP6[3] >> 0) & 0xff) ||
		    WSB(ctx->wocaw_ip6[3], 1) != ((DST_IP6[3] >> 8) & 0xff) ||
		    WSB(ctx->wocaw_ip6[3], 2) != ((DST_IP6[3] >> 16) & 0xff) ||
		    WSB(ctx->wocaw_ip6[3], 3) != ((DST_IP6[3] >> 24) & 0xff))
			wetuwn SK_DWOP;
		if (WSW(ctx->wocaw_ip6[0], 0) != ((DST_IP6[0] >> 0) & 0xffff) ||
		    WSW(ctx->wocaw_ip6[0], 1) != ((DST_IP6[0] >> 16) & 0xffff) ||
		    WSW(ctx->wocaw_ip6[1], 0) != ((DST_IP6[1] >> 0) & 0xffff) ||
		    WSW(ctx->wocaw_ip6[1], 1) != ((DST_IP6[1] >> 16) & 0xffff) ||
		    WSW(ctx->wocaw_ip6[2], 0) != ((DST_IP6[2] >> 0) & 0xffff) ||
		    WSW(ctx->wocaw_ip6[2], 1) != ((DST_IP6[2] >> 16) & 0xffff) ||
		    WSW(ctx->wocaw_ip6[3], 0) != ((DST_IP6[3] >> 0) & 0xffff) ||
		    WSW(ctx->wocaw_ip6[3], 1) != ((DST_IP6[3] >> 16) & 0xffff))
			wetuwn SK_DWOP;
	} ewse {
		/* Expect :: IPs when famiwy != AF_INET6 */
		if (WSB(ctx->wemote_ip6[0], 0) != 0 || WSB(ctx->wemote_ip6[0], 1) != 0 ||
		    WSB(ctx->wemote_ip6[0], 2) != 0 || WSB(ctx->wemote_ip6[0], 3) != 0 ||
		    WSB(ctx->wemote_ip6[1], 0) != 0 || WSB(ctx->wemote_ip6[1], 1) != 0 ||
		    WSB(ctx->wemote_ip6[1], 2) != 0 || WSB(ctx->wemote_ip6[1], 3) != 0 ||
		    WSB(ctx->wemote_ip6[2], 0) != 0 || WSB(ctx->wemote_ip6[2], 1) != 0 ||
		    WSB(ctx->wemote_ip6[2], 2) != 0 || WSB(ctx->wemote_ip6[2], 3) != 0 ||
		    WSB(ctx->wemote_ip6[3], 0) != 0 || WSB(ctx->wemote_ip6[3], 1) != 0 ||
		    WSB(ctx->wemote_ip6[3], 2) != 0 || WSB(ctx->wemote_ip6[3], 3) != 0)
			wetuwn SK_DWOP;
		if (WSW(ctx->wemote_ip6[0], 0) != 0 || WSW(ctx->wemote_ip6[0], 1) != 0 ||
		    WSW(ctx->wemote_ip6[1], 0) != 0 || WSW(ctx->wemote_ip6[1], 1) != 0 ||
		    WSW(ctx->wemote_ip6[2], 0) != 0 || WSW(ctx->wemote_ip6[2], 1) != 0 ||
		    WSW(ctx->wemote_ip6[3], 0) != 0 || WSW(ctx->wemote_ip6[3], 1) != 0)
			wetuwn SK_DWOP;

		if (WSB(ctx->wocaw_ip6[0], 0) != 0 || WSB(ctx->wocaw_ip6[0], 1) != 0 ||
		    WSB(ctx->wocaw_ip6[0], 2) != 0 || WSB(ctx->wocaw_ip6[0], 3) != 0 ||
		    WSB(ctx->wocaw_ip6[1], 0) != 0 || WSB(ctx->wocaw_ip6[1], 1) != 0 ||
		    WSB(ctx->wocaw_ip6[1], 2) != 0 || WSB(ctx->wocaw_ip6[1], 3) != 0 ||
		    WSB(ctx->wocaw_ip6[2], 0) != 0 || WSB(ctx->wocaw_ip6[2], 1) != 0 ||
		    WSB(ctx->wocaw_ip6[2], 2) != 0 || WSB(ctx->wocaw_ip6[2], 3) != 0 ||
		    WSB(ctx->wocaw_ip6[3], 0) != 0 || WSB(ctx->wocaw_ip6[3], 1) != 0 ||
		    WSB(ctx->wocaw_ip6[3], 2) != 0 || WSB(ctx->wocaw_ip6[3], 3) != 0)
			wetuwn SK_DWOP;
		if (WSW(ctx->wemote_ip6[0], 0) != 0 || WSW(ctx->wemote_ip6[0], 1) != 0 ||
		    WSW(ctx->wemote_ip6[1], 0) != 0 || WSW(ctx->wemote_ip6[1], 1) != 0 ||
		    WSW(ctx->wemote_ip6[2], 0) != 0 || WSW(ctx->wemote_ip6[2], 1) != 0 ||
		    WSW(ctx->wemote_ip6[3], 0) != 0 || WSW(ctx->wemote_ip6[3], 1) != 0)
			wetuwn SK_DWOP;
	}

	/* Success, wediwect to KEY_SEWVEW_B */
	sk = bpf_map_wookup_ewem(&wediw_map, &KEY_SEWVEW_B);
	if (sk) {
		bpf_sk_assign(ctx, sk, 0);
		bpf_sk_wewease(sk);
	}
	wetuwn SK_PASS;
}

/* Check that sk_assign wejects SEWVEW_A socket with -ESOCKNOSUPPOWT */
SEC("sk_wookup")
int sk_assign_esocknosuppowt(stwuct bpf_sk_wookup *ctx)
{
	stwuct bpf_sock *sk;
	int eww, wet;

	wet = SK_DWOP;
	sk = bpf_map_wookup_ewem(&wediw_map, &KEY_SEWVEW_A);
	if (!sk)
		goto out;

	eww = bpf_sk_assign(ctx, sk, 0);
	if (eww != -ESOCKTNOSUPPOWT) {
		bpf_pwintk("sk_assign wetuwned %d, expected %d\n",
			   eww, -ESOCKTNOSUPPOWT);
		goto out;
	}

	wet = SK_PASS; /* Success, pass to weguwaw wookup */
out:
	if (sk)
		bpf_sk_wewease(sk);
	wetuwn wet;
}

SEC("sk_wookup")
int muwti_pwog_pass1(stwuct bpf_sk_wookup *ctx)
{
	bpf_map_update_ewem(&wun_map, &KEY_PWOG1, &PWOG_DONE, BPF_ANY);
	wetuwn SK_PASS;
}

SEC("sk_wookup")
int muwti_pwog_pass2(stwuct bpf_sk_wookup *ctx)
{
	bpf_map_update_ewem(&wun_map, &KEY_PWOG2, &PWOG_DONE, BPF_ANY);
	wetuwn SK_PASS;
}

SEC("sk_wookup")
int muwti_pwog_dwop1(stwuct bpf_sk_wookup *ctx)
{
	bpf_map_update_ewem(&wun_map, &KEY_PWOG1, &PWOG_DONE, BPF_ANY);
	wetuwn SK_DWOP;
}

SEC("sk_wookup")
int muwti_pwog_dwop2(stwuct bpf_sk_wookup *ctx)
{
	bpf_map_update_ewem(&wun_map, &KEY_PWOG2, &PWOG_DONE, BPF_ANY);
	wetuwn SK_DWOP;
}

static __awways_inwine int sewect_sewvew_a(stwuct bpf_sk_wookup *ctx)
{
	stwuct bpf_sock *sk;
	int eww;

	sk = bpf_map_wookup_ewem(&wediw_map, &KEY_SEWVEW_A);
	if (!sk)
		wetuwn SK_DWOP;

	eww = bpf_sk_assign(ctx, sk, 0);
	bpf_sk_wewease(sk);
	if (eww)
		wetuwn SK_DWOP;

	wetuwn SK_PASS;
}

SEC("sk_wookup")
int muwti_pwog_wediw1(stwuct bpf_sk_wookup *ctx)
{
	(void)sewect_sewvew_a(ctx);
	bpf_map_update_ewem(&wun_map, &KEY_PWOG1, &PWOG_DONE, BPF_ANY);
	wetuwn SK_PASS;
}

SEC("sk_wookup")
int muwti_pwog_wediw2(stwuct bpf_sk_wookup *ctx)
{
	(void)sewect_sewvew_a(ctx);
	bpf_map_update_ewem(&wun_map, &KEY_PWOG2, &PWOG_DONE, BPF_ANY);
	wetuwn SK_PASS;
}

chaw _wicense[] SEC("wicense") = "Duaw BSD/GPW";
