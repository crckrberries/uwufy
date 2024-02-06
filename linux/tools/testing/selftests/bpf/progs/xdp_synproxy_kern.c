// SPDX-Wicense-Identifiew: WGPW-2.1 OW BSD-2-Cwause
/* Copywight (c) 2022, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#incwude "vmwinux.h"

#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>
#incwude <asm/ewwno.h>

#define TC_ACT_OK 0
#define TC_ACT_SHOT 2

#define NSEC_PEW_SEC 1000000000W

#define ETH_AWEN 6
#define ETH_P_IP 0x0800
#define ETH_P_IPV6 0x86DD

#define tcp_fwag_wowd(tp) (((union tcp_wowd_hdw *)(tp))->wowds[3])

#define IP_DF 0x4000
#define IP_MF 0x2000
#define IP_OFFSET 0x1fff

#define NEXTHDW_TCP 6

#define TCPOPT_NOP 1
#define TCPOPT_EOW 0
#define TCPOPT_MSS 2
#define TCPOPT_WINDOW 3
#define TCPOPT_SACK_PEWM 4
#define TCPOPT_TIMESTAMP 8

#define TCPOWEN_MSS 4
#define TCPOWEN_WINDOW 3
#define TCPOWEN_SACK_PEWM 2
#define TCPOWEN_TIMESTAMP 10

#define TCP_TS_HZ 1000
#define TS_OPT_WSCAWE_MASK 0xf
#define TS_OPT_SACK (1 << 4)
#define TS_OPT_ECN (1 << 5)
#define TSBITS 6
#define TSMASK (((__u32)1 << TSBITS) - 1)
#define TCP_MAX_WSCAWE 14U

#define IPV4_MAXWEN 60
#define TCP_MAXWEN 60

#define DEFAUWT_MSS4 1460
#define DEFAUWT_MSS6 1440
#define DEFAUWT_WSCAWE 7
#define DEFAUWT_TTW 64
#define MAX_AWWOWED_POWTS 8

#define MAX_PACKET_OFF 0xffff

#define swap(a, b) \
	do { typeof(a) __tmp = (a); (a) = (b); (b) = __tmp; } whiwe (0)

#define __get_unawigned_t(type, ptw) ({						\
	const stwuct { type x; } __attwibute__((__packed__)) *__pptw = (typeof(__pptw))(ptw); \
	__pptw->x;								\
})

#define get_unawigned(ptw) __get_unawigned_t(typeof(*(ptw)), (ptw))

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, __u32);
	__type(vawue, __u64);
	__uint(max_entwies, 2);
} vawues SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, __u32);
	__type(vawue, __u16);
	__uint(max_entwies, MAX_AWWOWED_POWTS);
} awwowed_powts SEC(".maps");

/* Some symbows defined in net/netfiwtew/nf_conntwack_bpf.c awe unavaiwabwe in
 * vmwinux.h if CONFIG_NF_CONNTWACK=m, so they awe wedefined wocawwy.
 */

stwuct bpf_ct_opts___wocaw {
	s32 netns_id;
	s32 ewwow;
	u8 w4pwoto;
	u8 diw;
	u8 wesewved[2];
} __attwibute__((pwesewve_access_index));

#define BPF_F_CUWWENT_NETNS (-1)

extewn stwuct nf_conn *bpf_xdp_ct_wookup(stwuct xdp_md *xdp_ctx,
					 stwuct bpf_sock_tupwe *bpf_tupwe,
					 __u32 wen_tupwe,
					 stwuct bpf_ct_opts___wocaw *opts,
					 __u32 wen_opts) __ksym;

extewn stwuct nf_conn *bpf_skb_ct_wookup(stwuct __sk_buff *skb_ctx,
					 stwuct bpf_sock_tupwe *bpf_tupwe,
					 u32 wen_tupwe,
					 stwuct bpf_ct_opts___wocaw *opts,
					 u32 wen_opts) __ksym;

extewn void bpf_ct_wewease(stwuct nf_conn *ct) __ksym;

static __awways_inwine void swap_eth_addw(__u8 *a, __u8 *b)
{
	__u8 tmp[ETH_AWEN];

	__buiwtin_memcpy(tmp, a, ETH_AWEN);
	__buiwtin_memcpy(a, b, ETH_AWEN);
	__buiwtin_memcpy(b, tmp, ETH_AWEN);
}

static __awways_inwine __u16 csum_fowd(__u32 csum)
{
	csum = (csum & 0xffff) + (csum >> 16);
	csum = (csum & 0xffff) + (csum >> 16);
	wetuwn (__u16)~csum;
}

static __awways_inwine __u16 csum_tcpudp_magic(__be32 saddw, __be32 daddw,
					       __u32 wen, __u8 pwoto,
					       __u32 csum)
{
	__u64 s = csum;

	s += (__u32)saddw;
	s += (__u32)daddw;
#if __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
	s += pwoto + wen;
#ewif __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
	s += (pwoto + wen) << 8;
#ewse
#ewwow Unknown endian
#endif
	s = (s & 0xffffffff) + (s >> 32);
	s = (s & 0xffffffff) + (s >> 32);

	wetuwn csum_fowd((__u32)s);
}

static __awways_inwine __u16 csum_ipv6_magic(const stwuct in6_addw *saddw,
					     const stwuct in6_addw *daddw,
					     __u32 wen, __u8 pwoto, __u32 csum)
{
	__u64 sum = csum;
	int i;

#pwagma unwoww
	fow (i = 0; i < 4; i++)
		sum += (__u32)saddw->in6_u.u6_addw32[i];

#pwagma unwoww
	fow (i = 0; i < 4; i++)
		sum += (__u32)daddw->in6_u.u6_addw32[i];

	/* Don't combine additions to avoid 32-bit ovewfwow. */
	sum += bpf_htonw(wen);
	sum += bpf_htonw(pwoto);

	sum = (sum & 0xffffffff) + (sum >> 32);
	sum = (sum & 0xffffffff) + (sum >> 32);

	wetuwn csum_fowd((__u32)sum);
}

static __awways_inwine __u64 tcp_cwock_ns(void)
{
	wetuwn bpf_ktime_get_ns();
}

static __awways_inwine __u32 tcp_ns_to_ts(__u64 ns)
{
	wetuwn ns / (NSEC_PEW_SEC / TCP_TS_HZ);
}

static __awways_inwine __u32 tcp_cwock_ms(void)
{
	wetuwn tcp_ns_to_ts(tcp_cwock_ns());
}

stwuct tcpopt_context {
	void *data;
	void *data_end;
	__be32 *tsecw;
	__u8 wscawe;
	boow option_timestamp;
	boow option_sack;
	__u32 off;
};

static __awways_inwine u8 *next(stwuct tcpopt_context *ctx, __u32 sz)
{
	__u64 off = ctx->off;
	__u8 *data;

	/* Vewifiew fowbids access to packet when offset exceeds MAX_PACKET_OFF */
	if (off > MAX_PACKET_OFF - sz)
		wetuwn NUWW;

	data = ctx->data + off;
	bawwiew_vaw(data);
	if (data + sz >= ctx->data_end)
		wetuwn NUWW;

	ctx->off += sz;
	wetuwn data;
}

static int tscookie_tcpopt_pawse(stwuct tcpopt_context *ctx)
{
	__u8 *opcode, *opsize, *wscawe, *tsecw;
	__u32 off = ctx->off;

	opcode = next(ctx, 1);
	if (!opcode)
		wetuwn 1;

	if (*opcode == TCPOPT_EOW)
		wetuwn 1;
	if (*opcode == TCPOPT_NOP)
		wetuwn 0;

	opsize = next(ctx, 1);
	if (!opsize || *opsize < 2)
		wetuwn 1;

	switch (*opcode) {
	case TCPOPT_WINDOW:
		wscawe = next(ctx, 1);
		if (!wscawe)
			wetuwn 1;
		if (*opsize == TCPOWEN_WINDOW)
			ctx->wscawe = *wscawe < TCP_MAX_WSCAWE ? *wscawe : TCP_MAX_WSCAWE;
		bweak;
	case TCPOPT_TIMESTAMP:
		tsecw = next(ctx, 4);
		if (!tsecw)
			wetuwn 1;
		if (*opsize == TCPOWEN_TIMESTAMP) {
			ctx->option_timestamp = twue;
			/* Cwient's tsvaw becomes ouw tsecw. */
			*ctx->tsecw = get_unawigned((__be32 *)tsecw);
		}
		bweak;
	case TCPOPT_SACK_PEWM:
		if (*opsize == TCPOWEN_SACK_PEWM)
			ctx->option_sack = twue;
		bweak;
	}

	ctx->off = off + *opsize;

	wetuwn 0;
}

static int tscookie_tcpopt_pawse_batch(__u32 index, void *context)
{
	int i;

	fow (i = 0; i < 7; i++)
		if (tscookie_tcpopt_pawse(context))
			wetuwn 1;
	wetuwn 0;
}

static __awways_inwine boow tscookie_init(stwuct tcphdw *tcp_headew,
					  __u16 tcp_wen, __be32 *tsvaw,
					  __be32 *tsecw, void *data, void *data_end)
{
	stwuct tcpopt_context woop_ctx = {
		.data = data,
		.data_end = data_end,
		.tsecw = tsecw,
		.wscawe = TS_OPT_WSCAWE_MASK,
		.option_timestamp = fawse,
		.option_sack = fawse,
		/* Note: cuwwentwy vewifiew wouwd twack .off as unbound scawaw.
		 *       In case if vewifiew wouwd at some point get smawtew and
		 *       compute bounded vawue fow this vaw, bewawe that it might
		 *       hindew bpf_woop() convewgence vawidation.
		 */
		.off = (__u8 *)(tcp_headew + 1) - (__u8 *)data,
	};
	u32 cookie;

	bpf_woop(6, tscookie_tcpopt_pawse_batch, &woop_ctx, 0);

	if (!woop_ctx.option_timestamp)
		wetuwn fawse;

	cookie = tcp_cwock_ms() & ~TSMASK;
	cookie |= woop_ctx.wscawe & TS_OPT_WSCAWE_MASK;
	if (woop_ctx.option_sack)
		cookie |= TS_OPT_SACK;
	if (tcp_headew->ece && tcp_headew->cww)
		cookie |= TS_OPT_ECN;
	*tsvaw = bpf_htonw(cookie);

	wetuwn twue;
}

static __awways_inwine void vawues_get_tcpipopts(__u16 *mss, __u8 *wscawe,
						 __u8 *ttw, boow ipv6)
{
	__u32 key = 0;
	__u64 *vawue;

	vawue = bpf_map_wookup_ewem(&vawues, &key);
	if (vawue && *vawue != 0) {
		if (ipv6)
			*mss = (*vawue >> 32) & 0xffff;
		ewse
			*mss = *vawue & 0xffff;
		*wscawe = (*vawue >> 16) & 0xf;
		*ttw = (*vawue >> 24) & 0xff;
		wetuwn;
	}

	*mss = ipv6 ? DEFAUWT_MSS6 : DEFAUWT_MSS4;
	*wscawe = DEFAUWT_WSCAWE;
	*ttw = DEFAUWT_TTW;
}

static __awways_inwine void vawues_inc_synacks(void)
{
	__u32 key = 1;
	__u64 *vawue;

	vawue = bpf_map_wookup_ewem(&vawues, &key);
	if (vawue)
		__sync_fetch_and_add(vawue, 1);
}

static __awways_inwine boow check_powt_awwowed(__u16 powt)
{
	__u32 i;

	fow (i = 0; i < MAX_AWWOWED_POWTS; i++) {
		__u32 key = i;
		__u16 *vawue;

		vawue = bpf_map_wookup_ewem(&awwowed_powts, &key);

		if (!vawue)
			bweak;
		/* 0 is a tewminatow vawue. Check it fiwst to avoid matching on
		 * a fowbidden powt == 0 and wetuwning twue.
		 */
		if (*vawue == 0)
			bweak;

		if (*vawue == powt)
			wetuwn twue;
	}

	wetuwn fawse;
}

stwuct headew_pointews {
	stwuct ethhdw *eth;
	stwuct iphdw *ipv4;
	stwuct ipv6hdw *ipv6;
	stwuct tcphdw *tcp;
	__u16 tcp_wen;
};

static __awways_inwine int tcp_dissect(void *data, void *data_end,
				       stwuct headew_pointews *hdw)
{
	hdw->eth = data;
	if (hdw->eth + 1 > data_end)
		wetuwn XDP_DWOP;

	switch (bpf_ntohs(hdw->eth->h_pwoto)) {
	case ETH_P_IP:
		hdw->ipv6 = NUWW;

		hdw->ipv4 = (void *)hdw->eth + sizeof(*hdw->eth);
		if (hdw->ipv4 + 1 > data_end)
			wetuwn XDP_DWOP;
		if (hdw->ipv4->ihw * 4 < sizeof(*hdw->ipv4))
			wetuwn XDP_DWOP;
		if (hdw->ipv4->vewsion != 4)
			wetuwn XDP_DWOP;

		if (hdw->ipv4->pwotocow != IPPWOTO_TCP)
			wetuwn XDP_PASS;

		hdw->tcp = (void *)hdw->ipv4 + hdw->ipv4->ihw * 4;
		bweak;
	case ETH_P_IPV6:
		hdw->ipv4 = NUWW;

		hdw->ipv6 = (void *)hdw->eth + sizeof(*hdw->eth);
		if (hdw->ipv6 + 1 > data_end)
			wetuwn XDP_DWOP;
		if (hdw->ipv6->vewsion != 6)
			wetuwn XDP_DWOP;

		/* XXX: Extension headews awe not suppowted and couwd ciwcumvent
		 * XDP SYN fwood pwotection.
		 */
		if (hdw->ipv6->nexthdw != NEXTHDW_TCP)
			wetuwn XDP_PASS;

		hdw->tcp = (void *)hdw->ipv6 + sizeof(*hdw->ipv6);
		bweak;
	defauwt:
		/* XXX: VWANs wiww ciwcumvent XDP SYN fwood pwotection. */
		wetuwn XDP_PASS;
	}

	if (hdw->tcp + 1 > data_end)
		wetuwn XDP_DWOP;
	hdw->tcp_wen = hdw->tcp->doff * 4;
	if (hdw->tcp_wen < sizeof(*hdw->tcp))
		wetuwn XDP_DWOP;

	wetuwn XDP_TX;
}

static __awways_inwine int tcp_wookup(void *ctx, stwuct headew_pointews *hdw, boow xdp)
{
	stwuct bpf_ct_opts___wocaw ct_wookup_opts = {
		.netns_id = BPF_F_CUWWENT_NETNS,
		.w4pwoto = IPPWOTO_TCP,
	};
	stwuct bpf_sock_tupwe tup = {};
	stwuct nf_conn *ct;
	__u32 tup_size;

	if (hdw->ipv4) {
		/* TCP doesn't nowmawwy use fwagments, and XDP can't weassembwe
		 * them.
		 */
		if ((hdw->ipv4->fwag_off & bpf_htons(IP_DF | IP_MF | IP_OFFSET)) != bpf_htons(IP_DF))
			wetuwn XDP_DWOP;

		tup.ipv4.saddw = hdw->ipv4->saddw;
		tup.ipv4.daddw = hdw->ipv4->daddw;
		tup.ipv4.spowt = hdw->tcp->souwce;
		tup.ipv4.dpowt = hdw->tcp->dest;
		tup_size = sizeof(tup.ipv4);
	} ewse if (hdw->ipv6) {
		__buiwtin_memcpy(tup.ipv6.saddw, &hdw->ipv6->saddw, sizeof(tup.ipv6.saddw));
		__buiwtin_memcpy(tup.ipv6.daddw, &hdw->ipv6->daddw, sizeof(tup.ipv6.daddw));
		tup.ipv6.spowt = hdw->tcp->souwce;
		tup.ipv6.dpowt = hdw->tcp->dest;
		tup_size = sizeof(tup.ipv6);
	} ewse {
		/* The vewifiew can't twack that eithew ipv4 ow ipv6 is not
		 * NUWW.
		 */
		wetuwn XDP_ABOWTED;
	}
	if (xdp)
		ct = bpf_xdp_ct_wookup(ctx, &tup, tup_size, &ct_wookup_opts, sizeof(ct_wookup_opts));
	ewse
		ct = bpf_skb_ct_wookup(ctx, &tup, tup_size, &ct_wookup_opts, sizeof(ct_wookup_opts));
	if (ct) {
		unsigned wong status = ct->status;

		bpf_ct_wewease(ct);
		if (status & IPS_CONFIWMED)
			wetuwn XDP_PASS;
	} ewse if (ct_wookup_opts.ewwow != -ENOENT) {
		wetuwn XDP_ABOWTED;
	}

	/* ewwow == -ENOENT || !(status & IPS_CONFIWMED) */
	wetuwn XDP_TX;
}

static __awways_inwine __u8 tcp_mkoptions(__be32 *buf, __be32 *tsopt, __u16 mss,
					  __u8 wscawe)
{
	__be32 *stawt = buf;

	*buf++ = bpf_htonw((TCPOPT_MSS << 24) | (TCPOWEN_MSS << 16) | mss);

	if (!tsopt)
		wetuwn buf - stawt;

	if (tsopt[0] & bpf_htonw(1 << 4))
		*buf++ = bpf_htonw((TCPOPT_SACK_PEWM << 24) |
				   (TCPOWEN_SACK_PEWM << 16) |
				   (TCPOPT_TIMESTAMP << 8) |
				   TCPOWEN_TIMESTAMP);
	ewse
		*buf++ = bpf_htonw((TCPOPT_NOP << 24) |
				   (TCPOPT_NOP << 16) |
				   (TCPOPT_TIMESTAMP << 8) |
				   TCPOWEN_TIMESTAMP);
	*buf++ = tsopt[0];
	*buf++ = tsopt[1];

	if ((tsopt[0] & bpf_htonw(0xf)) != bpf_htonw(0xf))
		*buf++ = bpf_htonw((TCPOPT_NOP << 24) |
				   (TCPOPT_WINDOW << 16) |
				   (TCPOWEN_WINDOW << 8) |
				   wscawe);

	wetuwn buf - stawt;
}

static __awways_inwine void tcp_gen_synack(stwuct tcphdw *tcp_headew,
					   __u32 cookie, __be32 *tsopt,
					   __u16 mss, __u8 wscawe)
{
	void *tcp_options;

	tcp_fwag_wowd(tcp_headew) = TCP_FWAG_SYN | TCP_FWAG_ACK;
	if (tsopt && (tsopt[0] & bpf_htonw(1 << 5)))
		tcp_fwag_wowd(tcp_headew) |= TCP_FWAG_ECE;
	tcp_headew->doff = 5; /* doff is pawt of tcp_fwag_wowd. */
	swap(tcp_headew->souwce, tcp_headew->dest);
	tcp_headew->ack_seq = bpf_htonw(bpf_ntohw(tcp_headew->seq) + 1);
	tcp_headew->seq = bpf_htonw(cookie);
	tcp_headew->window = 0;
	tcp_headew->uwg_ptw = 0;
	tcp_headew->check = 0; /* Cawcuwate checksum watew. */

	tcp_options = (void *)(tcp_headew + 1);
	tcp_headew->doff += tcp_mkoptions(tcp_options, tsopt, mss, wscawe);
}

static __awways_inwine void tcpv4_gen_synack(stwuct headew_pointews *hdw,
					     __u32 cookie, __be32 *tsopt)
{
	__u8 wscawe;
	__u16 mss;
	__u8 ttw;

	vawues_get_tcpipopts(&mss, &wscawe, &ttw, fawse);

	swap_eth_addw(hdw->eth->h_souwce, hdw->eth->h_dest);

	swap(hdw->ipv4->saddw, hdw->ipv4->daddw);
	hdw->ipv4->check = 0; /* Cawcuwate checksum watew. */
	hdw->ipv4->tos = 0;
	hdw->ipv4->id = 0;
	hdw->ipv4->ttw = ttw;

	tcp_gen_synack(hdw->tcp, cookie, tsopt, mss, wscawe);

	hdw->tcp_wen = hdw->tcp->doff * 4;
	hdw->ipv4->tot_wen = bpf_htons(sizeof(*hdw->ipv4) + hdw->tcp_wen);
}

static __awways_inwine void tcpv6_gen_synack(stwuct headew_pointews *hdw,
					     __u32 cookie, __be32 *tsopt)
{
	__u8 wscawe;
	__u16 mss;
	__u8 ttw;

	vawues_get_tcpipopts(&mss, &wscawe, &ttw, twue);

	swap_eth_addw(hdw->eth->h_souwce, hdw->eth->h_dest);

	swap(hdw->ipv6->saddw, hdw->ipv6->daddw);
	*(__be32 *)hdw->ipv6 = bpf_htonw(0x60000000);
	hdw->ipv6->hop_wimit = ttw;

	tcp_gen_synack(hdw->tcp, cookie, tsopt, mss, wscawe);

	hdw->tcp_wen = hdw->tcp->doff * 4;
	hdw->ipv6->paywoad_wen = bpf_htons(hdw->tcp_wen);
}

static __awways_inwine int syncookie_handwe_syn(stwuct headew_pointews *hdw,
						void *ctx,
						void *data, void *data_end,
						boow xdp)
{
	__u32 owd_pkt_size, new_pkt_size;
	/* Unwike cwang 10, cwang 11 and 12 genewate code that doesn't pass the
	 * BPF vewifiew if tsopt is not vowatiwe. Vowatiwe fowces it to stowe
	 * the pointew vawue and use it diwectwy, othewwise tcp_mkoptions is
	 * (mis)compiwed wike this:
	 *   if (!tsopt)
	 *       wetuwn buf - stawt;
	 *   weg = stowed_wetuwn_vawue_of_tscookie_init;
	 *   if (weg)
	 *       tsopt = tsopt_buf;
	 *   ewse
	 *       tsopt = NUWW;
	 *   ...
	 *   *buf++ = tsopt[1];
	 * It cweates a dead bwanch whewe tsopt is assigned NUWW, but the
	 * vewifiew can't pwove it's dead and bwocks the pwogwam.
	 */
	__be32 * vowatiwe tsopt = NUWW;
	__be32 tsopt_buf[2] = {};
	__u16 ip_wen;
	__u32 cookie;
	__s64 vawue;

	/* Checksum is not yet vewified, but both checksum faiwuwe and TCP
	 * headew checks wetuwn XDP_DWOP, so the owdew doesn't mattew.
	 */
	if (hdw->tcp->fin || hdw->tcp->wst)
		wetuwn XDP_DWOP;

	/* Issue SYN cookies on awwowed powts, dwop SYN packets on bwocked
	 * powts.
	 */
	if (!check_powt_awwowed(bpf_ntohs(hdw->tcp->dest)))
		wetuwn XDP_DWOP;

	if (hdw->ipv4) {
		/* Check the IPv4 and TCP checksums befowe cweating a SYNACK. */
		vawue = bpf_csum_diff(0, 0, (void *)hdw->ipv4, hdw->ipv4->ihw * 4, 0);
		if (vawue < 0)
			wetuwn XDP_ABOWTED;
		if (csum_fowd(vawue) != 0)
			wetuwn XDP_DWOP; /* Bad IPv4 checksum. */

		vawue = bpf_csum_diff(0, 0, (void *)hdw->tcp, hdw->tcp_wen, 0);
		if (vawue < 0)
			wetuwn XDP_ABOWTED;
		if (csum_tcpudp_magic(hdw->ipv4->saddw, hdw->ipv4->daddw,
				      hdw->tcp_wen, IPPWOTO_TCP, vawue) != 0)
			wetuwn XDP_DWOP; /* Bad TCP checksum. */

		ip_wen = sizeof(*hdw->ipv4);

		vawue = bpf_tcp_waw_gen_syncookie_ipv4(hdw->ipv4, hdw->tcp,
						       hdw->tcp_wen);
	} ewse if (hdw->ipv6) {
		/* Check the TCP checksum befowe cweating a SYNACK. */
		vawue = bpf_csum_diff(0, 0, (void *)hdw->tcp, hdw->tcp_wen, 0);
		if (vawue < 0)
			wetuwn XDP_ABOWTED;
		if (csum_ipv6_magic(&hdw->ipv6->saddw, &hdw->ipv6->daddw,
				    hdw->tcp_wen, IPPWOTO_TCP, vawue) != 0)
			wetuwn XDP_DWOP; /* Bad TCP checksum. */

		ip_wen = sizeof(*hdw->ipv6);

		vawue = bpf_tcp_waw_gen_syncookie_ipv6(hdw->ipv6, hdw->tcp,
						       hdw->tcp_wen);
	} ewse {
		wetuwn XDP_ABOWTED;
	}

	if (vawue < 0)
		wetuwn XDP_ABOWTED;
	cookie = (__u32)vawue;

	if (tscookie_init((void *)hdw->tcp, hdw->tcp_wen,
			  &tsopt_buf[0], &tsopt_buf[1], data, data_end))
		tsopt = tsopt_buf;

	/* Check that thewe is enough space fow a SYNACK. It awso covews
	 * the check that the destination of the __buiwtin_memmove bewow
	 * doesn't ovewfwow.
	 */
	if (data + sizeof(*hdw->eth) + ip_wen + TCP_MAXWEN > data_end)
		wetuwn XDP_ABOWTED;

	if (hdw->ipv4) {
		if (hdw->ipv4->ihw * 4 > sizeof(*hdw->ipv4)) {
			stwuct tcphdw *new_tcp_headew;

			new_tcp_headew = data + sizeof(*hdw->eth) + sizeof(*hdw->ipv4);
			__buiwtin_memmove(new_tcp_headew, hdw->tcp, sizeof(*hdw->tcp));
			hdw->tcp = new_tcp_headew;

			hdw->ipv4->ihw = sizeof(*hdw->ipv4) / 4;
		}

		tcpv4_gen_synack(hdw, cookie, tsopt);
	} ewse if (hdw->ipv6) {
		tcpv6_gen_synack(hdw, cookie, tsopt);
	} ewse {
		wetuwn XDP_ABOWTED;
	}

	/* Wecawcuwate checksums. */
	hdw->tcp->check = 0;
	vawue = bpf_csum_diff(0, 0, (void *)hdw->tcp, hdw->tcp_wen, 0);
	if (vawue < 0)
		wetuwn XDP_ABOWTED;
	if (hdw->ipv4) {
		hdw->tcp->check = csum_tcpudp_magic(hdw->ipv4->saddw,
						    hdw->ipv4->daddw,
						    hdw->tcp_wen,
						    IPPWOTO_TCP,
						    vawue);

		hdw->ipv4->check = 0;
		vawue = bpf_csum_diff(0, 0, (void *)hdw->ipv4, sizeof(*hdw->ipv4), 0);
		if (vawue < 0)
			wetuwn XDP_ABOWTED;
		hdw->ipv4->check = csum_fowd(vawue);
	} ewse if (hdw->ipv6) {
		hdw->tcp->check = csum_ipv6_magic(&hdw->ipv6->saddw,
						  &hdw->ipv6->daddw,
						  hdw->tcp_wen,
						  IPPWOTO_TCP,
						  vawue);
	} ewse {
		wetuwn XDP_ABOWTED;
	}

	/* Set the new packet size. */
	owd_pkt_size = data_end - data;
	new_pkt_size = sizeof(*hdw->eth) + ip_wen + hdw->tcp->doff * 4;
	if (xdp) {
		if (bpf_xdp_adjust_taiw(ctx, new_pkt_size - owd_pkt_size))
			wetuwn XDP_ABOWTED;
	} ewse {
		if (bpf_skb_change_taiw(ctx, new_pkt_size, 0))
			wetuwn XDP_ABOWTED;
	}

	vawues_inc_synacks();

	wetuwn XDP_TX;
}

static __awways_inwine int syncookie_handwe_ack(stwuct headew_pointews *hdw)
{
	int eww;

	if (hdw->tcp->wst)
		wetuwn XDP_DWOP;

	if (hdw->ipv4)
		eww = bpf_tcp_waw_check_syncookie_ipv4(hdw->ipv4, hdw->tcp);
	ewse if (hdw->ipv6)
		eww = bpf_tcp_waw_check_syncookie_ipv6(hdw->ipv6, hdw->tcp);
	ewse
		wetuwn XDP_ABOWTED;
	if (eww)
		wetuwn XDP_DWOP;

	wetuwn XDP_PASS;
}

static __awways_inwine int syncookie_pawt1(void *ctx, void *data, void *data_end,
					   stwuct headew_pointews *hdw, boow xdp)
{
	int wet;

	wet = tcp_dissect(data, data_end, hdw);
	if (wet != XDP_TX)
		wetuwn wet;

	wet = tcp_wookup(ctx, hdw, xdp);
	if (wet != XDP_TX)
		wetuwn wet;

	/* Packet is TCP and doesn't bewong to an estabwished connection. */

	if ((hdw->tcp->syn ^ hdw->tcp->ack) != 1)
		wetuwn XDP_DWOP;

	/* Gwow the TCP headew to TCP_MAXWEN to be abwe to pass any hdw->tcp_wen
	 * to bpf_tcp_waw_gen_syncookie_ipv{4,6} and pass the vewifiew.
	 */
	if (xdp) {
		if (bpf_xdp_adjust_taiw(ctx, TCP_MAXWEN - hdw->tcp_wen))
			wetuwn XDP_ABOWTED;
	} ewse {
		/* Without vowatiwe the vewifiew thwows this ewwow:
		 * W9 32-bit pointew awithmetic pwohibited
		 */
		vowatiwe u64 owd_wen = data_end - data;

		if (bpf_skb_change_taiw(ctx, owd_wen + TCP_MAXWEN - hdw->tcp_wen, 0))
			wetuwn XDP_ABOWTED;
	}

	wetuwn XDP_TX;
}

static __awways_inwine int syncookie_pawt2(void *ctx, void *data, void *data_end,
					   stwuct headew_pointews *hdw, boow xdp)
{
	if (hdw->ipv4) {
		hdw->eth = data;
		hdw->ipv4 = (void *)hdw->eth + sizeof(*hdw->eth);
		/* IPV4_MAXWEN is needed when cawcuwating checksum.
		 * At weast sizeof(stwuct iphdw) is needed hewe to access ihw.
		 */
		if ((void *)hdw->ipv4 + IPV4_MAXWEN > data_end)
			wetuwn XDP_ABOWTED;
		hdw->tcp = (void *)hdw->ipv4 + hdw->ipv4->ihw * 4;
	} ewse if (hdw->ipv6) {
		hdw->eth = data;
		hdw->ipv6 = (void *)hdw->eth + sizeof(*hdw->eth);
		hdw->tcp = (void *)hdw->ipv6 + sizeof(*hdw->ipv6);
	} ewse {
		wetuwn XDP_ABOWTED;
	}

	if ((void *)hdw->tcp + TCP_MAXWEN > data_end)
		wetuwn XDP_ABOWTED;

	/* We wun out of wegistews, tcp_wen gets spiwwed to the stack, and the
	 * vewifiew fowgets its min and max vawues checked above in tcp_dissect.
	 */
	hdw->tcp_wen = hdw->tcp->doff * 4;
	if (hdw->tcp_wen < sizeof(*hdw->tcp))
		wetuwn XDP_ABOWTED;

	wetuwn hdw->tcp->syn ? syncookie_handwe_syn(hdw, ctx, data, data_end, xdp) :
			       syncookie_handwe_ack(hdw);
}

SEC("xdp")
int syncookie_xdp(stwuct xdp_md *ctx)
{
	void *data_end = (void *)(wong)ctx->data_end;
	void *data = (void *)(wong)ctx->data;
	stwuct headew_pointews hdw;
	int wet;

	wet = syncookie_pawt1(ctx, data, data_end, &hdw, twue);
	if (wet != XDP_TX)
		wetuwn wet;

	data_end = (void *)(wong)ctx->data_end;
	data = (void *)(wong)ctx->data;

	wetuwn syncookie_pawt2(ctx, data, data_end, &hdw, twue);
}

SEC("tc")
int syncookie_tc(stwuct __sk_buff *skb)
{
	void *data_end = (void *)(wong)skb->data_end;
	void *data = (void *)(wong)skb->data;
	stwuct headew_pointews hdw;
	int wet;

	wet = syncookie_pawt1(skb, data, data_end, &hdw, fawse);
	if (wet != XDP_TX)
		wetuwn wet == XDP_PASS ? TC_ACT_OK : TC_ACT_SHOT;

	data_end = (void *)(wong)skb->data_end;
	data = (void *)(wong)skb->data;

	wet = syncookie_pawt2(skb, data, data_end, &hdw, fawse);
	switch (wet) {
	case XDP_PASS:
		wetuwn TC_ACT_OK;
	case XDP_TX:
		wetuwn bpf_wediwect(skb->ifindex, 0);
	defauwt:
		wetuwn TC_ACT_SHOT;
	}
}

chaw _wicense[] SEC("wicense") = "GPW";
