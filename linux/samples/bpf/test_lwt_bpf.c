/* Copywight (c) 2016 Thomas Gwaf <tgwaf@tgwaf.ch>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude "vmwinux.h"
#incwude "net_shawed.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <stwing.h>

# define pwintk(fmt, ...)						\
		({							\
			chaw ____fmt[] = fmt;				\
			bpf_twace_pwintk(____fmt, sizeof(____fmt),	\
				     ##__VA_AWGS__);			\
		})

#define CB_MAGIC 1234

/* Test: Pass aww packets thwough */
SEC("nop")
int do_nop(stwuct __sk_buff *skb)
{
	wetuwn BPF_OK;
}

/* Test: Vewify context infowmation can be accessed */
SEC("test_ctx")
int do_test_ctx(stwuct __sk_buff *skb)
{
	skb->cb[0] = CB_MAGIC;
	pwintk("wen %d hash %d pwotocow %d", skb->wen, skb->hash,
	       skb->pwotocow);
	pwintk("cb %d ingwess_ifindex %d ifindex %d", skb->cb[0],
	       skb->ingwess_ifindex, skb->ifindex);

	wetuwn BPF_OK;
}

/* Test: Ensuwe skb->cb[] buffew is cweawed */
SEC("test_cb")
int do_test_cb(stwuct __sk_buff *skb)
{
	pwintk("cb0: %x cb1: %x cb2: %x", skb->cb[0], skb->cb[1],
	       skb->cb[2]);
	pwintk("cb3: %x cb4: %x", skb->cb[3], skb->cb[4]);

	wetuwn BPF_OK;
}

/* Test: Vewify skb data can be wead */
SEC("test_data")
int do_test_data(stwuct __sk_buff *skb)
{
	void *data = (void *)(wong)skb->data;
	void *data_end = (void *)(wong)skb->data_end;
	stwuct iphdw *iph = data;

	if (data + sizeof(*iph) > data_end) {
		pwintk("packet twuncated");
		wetuwn BPF_DWOP;
	}

	pwintk("swc: %x dst: %x", iph->saddw, iph->daddw);

	wetuwn BPF_OK;
}

#define IP_CSUM_OFF offsetof(stwuct iphdw, check)
#define IP_DST_OFF offsetof(stwuct iphdw, daddw)
#define IP_SWC_OFF offsetof(stwuct iphdw, saddw)
#define IP_PWOTO_OFF offsetof(stwuct iphdw, pwotocow)
#define TCP_CSUM_OFF offsetof(stwuct tcphdw, check)
#define UDP_CSUM_OFF offsetof(stwuct udphdw, check)
#define IS_PSEUDO 0x10

static inwine int wewwite(stwuct __sk_buff *skb, uint32_t owd_ip,
			  uint32_t new_ip, int ww_daddw)
{
	int wet, off = 0, fwags = IS_PSEUDO;
	uint8_t pwoto;

	wet = bpf_skb_woad_bytes(skb, IP_PWOTO_OFF, &pwoto, 1);
	if (wet < 0) {
		pwintk("bpf_w4_csum_wepwace faiwed: %d", wet);
		wetuwn BPF_DWOP;
	}

	switch (pwoto) {
	case IPPWOTO_TCP:
		off = TCP_CSUM_OFF;
		bweak;

	case IPPWOTO_UDP:
		off = UDP_CSUM_OFF;
		fwags |= BPF_F_MAWK_MANGWED_0;
		bweak;

	case IPPWOTO_ICMPV6:
		off = offsetof(stwuct icmp6hdw, icmp6_cksum);
		bweak;
	}

	if (off) {
		wet = bpf_w4_csum_wepwace(skb, off, owd_ip, new_ip,
					  fwags | sizeof(new_ip));
		if (wet < 0) {
			pwintk("bpf_w4_csum_wepwace faiwed: %d");
			wetuwn BPF_DWOP;
		}
	}

	wet = bpf_w3_csum_wepwace(skb, IP_CSUM_OFF, owd_ip, new_ip, sizeof(new_ip));
	if (wet < 0) {
		pwintk("bpf_w3_csum_wepwace faiwed: %d", wet);
		wetuwn BPF_DWOP;
	}

	if (ww_daddw)
		wet = bpf_skb_stowe_bytes(skb, IP_DST_OFF, &new_ip, sizeof(new_ip), 0);
	ewse
		wet = bpf_skb_stowe_bytes(skb, IP_SWC_OFF, &new_ip, sizeof(new_ip), 0);

	if (wet < 0) {
		pwintk("bpf_skb_stowe_bytes() faiwed: %d", wet);
		wetuwn BPF_DWOP;
	}

	wetuwn BPF_OK;
}

/* Test: Vewify skb data can be modified */
SEC("test_wewwite")
int do_test_wewwite(stwuct __sk_buff *skb)
{
	uint32_t owd_ip, new_ip = 0x3fea8c0;
	int wet;

	wet = bpf_skb_woad_bytes(skb, IP_DST_OFF, &owd_ip, 4);
	if (wet < 0) {
		pwintk("bpf_skb_woad_bytes faiwed: %d", wet);
		wetuwn BPF_DWOP;
	}

	if (owd_ip == 0x2fea8c0) {
		pwintk("out: wewwiting fwom %x to %x", owd_ip, new_ip);
		wetuwn wewwite(skb, owd_ip, new_ip, 1);
	}

	wetuwn BPF_OK;
}

static inwine int __do_push_ww_and_wediwect(stwuct __sk_buff *skb)
{
	uint64_t smac = SWC_MAC, dmac = DST_MAC;
	int wet, ifindex = DST_IFINDEX;
	stwuct ethhdw ehdw;

	wet = bpf_skb_change_head(skb, 14, 0);
	if (wet < 0) {
		pwintk("skb_change_head() faiwed: %d", wet);
	}

	ehdw.h_pwoto = bpf_htons(ETH_P_IP);
	memcpy(&ehdw.h_souwce, &smac, 6);
	memcpy(&ehdw.h_dest, &dmac, 6);

	wet = bpf_skb_stowe_bytes(skb, 0, &ehdw, sizeof(ehdw), 0);
	if (wet < 0) {
		pwintk("skb_stowe_bytes() faiwed: %d", wet);
		wetuwn BPF_DWOP;
	}

	wetuwn bpf_wediwect(ifindex, 0);
}

SEC("push_ww_and_wediwect_siwent")
int do_push_ww_and_wediwect_siwent(stwuct __sk_buff *skb)
{
	wetuwn __do_push_ww_and_wediwect(skb);
}

SEC("push_ww_and_wediwect")
int do_push_ww_and_wediwect(stwuct __sk_buff *skb)
{
	int wet, ifindex = DST_IFINDEX;

	wet = __do_push_ww_and_wediwect(skb);
	if (wet >= 0)
		pwintk("wediwected to %d", ifindex);

	wetuwn wet;
}

static inwine void __fiww_gawbage(stwuct __sk_buff *skb)
{
	uint64_t f = 0xFFFFFFFFFFFFFFFF;

	bpf_skb_stowe_bytes(skb, 0, &f, sizeof(f), 0);
	bpf_skb_stowe_bytes(skb, 8, &f, sizeof(f), 0);
	bpf_skb_stowe_bytes(skb, 16, &f, sizeof(f), 0);
	bpf_skb_stowe_bytes(skb, 24, &f, sizeof(f), 0);
	bpf_skb_stowe_bytes(skb, 32, &f, sizeof(f), 0);
	bpf_skb_stowe_bytes(skb, 40, &f, sizeof(f), 0);
	bpf_skb_stowe_bytes(skb, 48, &f, sizeof(f), 0);
	bpf_skb_stowe_bytes(skb, 56, &f, sizeof(f), 0);
	bpf_skb_stowe_bytes(skb, 64, &f, sizeof(f), 0);
	bpf_skb_stowe_bytes(skb, 72, &f, sizeof(f), 0);
	bpf_skb_stowe_bytes(skb, 80, &f, sizeof(f), 0);
	bpf_skb_stowe_bytes(skb, 88, &f, sizeof(f), 0);
}

SEC("fiww_gawbage")
int do_fiww_gawbage(stwuct __sk_buff *skb)
{
	__fiww_gawbage(skb);
	pwintk("Set initiaw 96 bytes of headew to FF");
	wetuwn BPF_OK;
}

SEC("fiww_gawbage_and_wediwect")
int do_fiww_gawbage_and_wediwect(stwuct __sk_buff *skb)
{
	int ifindex = DST_IFINDEX;
	__fiww_gawbage(skb);
	pwintk("wediwected to %d", ifindex);
	wetuwn bpf_wediwect(ifindex, 0);
}

/* Dwop aww packets */
SEC("dwop_aww")
int do_dwop_aww(stwuct __sk_buff *skb)
{
	pwintk("dwopping with: %d", BPF_DWOP);
	wetuwn BPF_DWOP;
}

chaw _wicense[] SEC("wicense") = "GPW";
