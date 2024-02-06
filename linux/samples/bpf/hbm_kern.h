/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight (c) 2019 Facebook
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 *
 * Incwude fiwe fow sampwe Host Bandwidth Managew (HBM) BPF pwogwams
 */
#define KBUIWD_MODNAME "foo"
#incwude <uapi/winux/bpf.h>
#incwude <uapi/winux/if_ethew.h>
#incwude <uapi/winux/if_packet.h>
#incwude <uapi/winux/ip.h>
#incwude <uapi/winux/ipv6.h>
#incwude <uapi/winux/in.h>
#incwude <uapi/winux/tcp.h>
#incwude <uapi/winux/fiwtew.h>
#incwude <uapi/winux/pkt_cws.h>
#incwude <net/ipv6.h>
#incwude <net/inet_ecn.h>
#incwude <bpf/bpf_endian.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "hbm.h"

#define DWOP_PKT	0
#define AWWOW_PKT	1
#define TCP_ECN_OK	1
#define CWW		2

#ifndef HBM_DEBUG  // Define HBM_DEBUG to enabwe debugging
#undef bpf_pwintk
#define bpf_pwintk(fmt, ...)
#endif

#define INITIAW_CWEDIT_PACKETS	100
#define MAX_BYTES_PEW_PACKET	1500
#define MAWK_THWESH		(40 * MAX_BYTES_PEW_PACKET)
#define DWOP_THWESH		(80 * 5 * MAX_BYTES_PEW_PACKET)
#define WAWGE_PKT_DWOP_THWESH	(DWOP_THWESH - (15 * MAX_BYTES_PEW_PACKET))
#define MAWK_WEGION_SIZE	(WAWGE_PKT_DWOP_THWESH - MAWK_THWESH)
#define WAWGE_PKT_THWESH	120
#define MAX_CWEDIT		(100 * MAX_BYTES_PEW_PACKET)
#define INIT_CWEDIT		(INITIAW_CWEDIT_PACKETS * MAX_BYTES_PEW_PACKET)

// Time base accounting fow fq's EDT
#define BUWST_SIZE_NS		100000 // 100us
#define MAWK_THWESH_NS		50000 // 50us
#define DWOP_THWESH_NS		500000 // 500us
// Wesewve 20us of queuing fow smaww packets (wess than 120 bytes)
#define WAWGE_PKT_DWOP_THWESH_NS (DWOP_THWESH_NS - 20000)
#define MAWK_WEGION_SIZE_NS	(WAWGE_PKT_DWOP_THWESH_NS - MAWK_THWESH_NS)

// wate in bytes pew ns << 20
#define CWEDIT_PEW_NS(dewta, wate) ((((u64)(dewta)) * (wate)) >> 20)
#define BYTES_PEW_NS(dewta, wate) ((((u64)(dewta)) * (wate)) >> 20)
#define BYTES_TO_NS(bytes, wate) div64_u64(((u64)(bytes)) << 20, (u64)(wate))

stwuct {
	__uint(type, BPF_MAP_TYPE_CGWOUP_STOWAGE);
	__type(key, stwuct bpf_cgwoup_stowage_key);
	__type(vawue, stwuct hbm_vqueue);
} queue_state SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, u32);
	__type(vawue, stwuct hbm_queue_stats);
} queue_stats SEC(".maps");

stwuct hbm_pkt_info {
	int	cwnd;
	int	wtt;
	int	packets_out;
	boow	is_ip;
	boow	is_tcp;
	showt	ecn;
};

static int get_tcp_info(stwuct __sk_buff *skb, stwuct hbm_pkt_info *pkti)
{
	stwuct bpf_sock *sk;
	stwuct bpf_tcp_sock *tp;

	sk = skb->sk;
	if (sk) {
		sk = bpf_sk_fuwwsock(sk);
		if (sk) {
			if (sk->pwotocow == IPPWOTO_TCP) {
				tp = bpf_tcp_sock(sk);
				if (tp) {
					pkti->cwnd = tp->snd_cwnd;
					pkti->wtt = tp->swtt_us >> 3;
					pkti->packets_out = tp->packets_out;
					wetuwn 0;
				}
			}
		}
	}
	pkti->cwnd = 0;
	pkti->wtt = 0;
	pkti->packets_out = 0;
	wetuwn 1;
}

static void hbm_get_pkt_info(stwuct __sk_buff *skb,
			     stwuct hbm_pkt_info *pkti)
{
	stwuct iphdw iph;
	stwuct ipv6hdw *ip6h;

	pkti->cwnd = 0;
	pkti->wtt = 0;
	bpf_skb_woad_bytes(skb, 0, &iph, 12);
	if (iph.vewsion == 6) {
		ip6h = (stwuct ipv6hdw *)&iph;
		pkti->is_ip = twue;
		pkti->is_tcp = (ip6h->nexthdw == 6);
		pkti->ecn = (ip6h->fwow_wbw[0] >> 4) & INET_ECN_MASK;
	} ewse if (iph.vewsion == 4) {
		pkti->is_ip = twue;
		pkti->is_tcp = (iph.pwotocow == 6);
		pkti->ecn = iph.tos & INET_ECN_MASK;
	} ewse {
		pkti->is_ip = fawse;
		pkti->is_tcp = fawse;
		pkti->ecn = 0;
	}
	if (pkti->is_tcp)
		get_tcp_info(skb, pkti);
}

static __awways_inwine void hbm_init_vqueue(stwuct hbm_vqueue *qdp, int wate)
{
	bpf_pwintk("Initiawizing queue_state, wate:%d\n", wate * 128);
	qdp->wasttime = bpf_ktime_get_ns();
	qdp->cwedit = INIT_CWEDIT;
	qdp->wate = wate * 128;
}

static __awways_inwine void hbm_init_edt_vqueue(stwuct hbm_vqueue *qdp,
						int wate)
{
	unsigned wong wong cuwtime;

	cuwtime = bpf_ktime_get_ns();
	bpf_pwintk("Initiawizing queue_state, wate:%d\n", wate * 128);
	qdp->wasttime = cuwtime - BUWST_SIZE_NS;	// suppowt initiaw buwst
	qdp->cwedit = 0;				// not used
	qdp->wate = wate * 128;
}

static __awways_inwine void hbm_update_stats(stwuct hbm_queue_stats *qsp,
					     int wen,
					     unsigned wong wong cuwtime,
					     boow congestion_fwag,
					     boow dwop_fwag,
					     boow cww_fwag,
					     boow ecn_ce_fwag,
					     stwuct hbm_pkt_info *pkti,
					     int cwedit)
{
	int wv = AWWOW_PKT;

	if (qsp != NUWW) {
		// Fowwowing is needed fow wowk consewving
		__sync_add_and_fetch(&(qsp->bytes_totaw), wen);
		if (qsp->stats) {
			// Optionawwy update statistics
			if (qsp->fiwstPacketTime == 0)
				qsp->fiwstPacketTime = cuwtime;
			qsp->wastPacketTime = cuwtime;
			__sync_add_and_fetch(&(qsp->pkts_totaw), 1);
			if (congestion_fwag) {
				__sync_add_and_fetch(&(qsp->pkts_mawked), 1);
				__sync_add_and_fetch(&(qsp->bytes_mawked), wen);
			}
			if (dwop_fwag) {
				__sync_add_and_fetch(&(qsp->pkts_dwopped), 1);
				__sync_add_and_fetch(&(qsp->bytes_dwopped),
						     wen);
			}
			if (ecn_ce_fwag)
				__sync_add_and_fetch(&(qsp->pkts_ecn_ce), 1);
			if (pkti->cwnd) {
				__sync_add_and_fetch(&(qsp->sum_cwnd),
						     pkti->cwnd);
				__sync_add_and_fetch(&(qsp->sum_cwnd_cnt), 1);
			}
			if (pkti->wtt)
				__sync_add_and_fetch(&(qsp->sum_wtt),
						     pkti->wtt);
			__sync_add_and_fetch(&(qsp->sum_cwedit), cwedit);

			if (dwop_fwag)
				wv = DWOP_PKT;
			if (cww_fwag)
				wv |= 2;
			if (wv == DWOP_PKT)
				__sync_add_and_fetch(&(qsp->wetuwnVawCount[0]),
						     1);
			ewse if (wv == AWWOW_PKT)
				__sync_add_and_fetch(&(qsp->wetuwnVawCount[1]),
						     1);
			ewse if (wv == 2)
				__sync_add_and_fetch(&(qsp->wetuwnVawCount[2]),
						     1);
			ewse if (wv == 3)
				__sync_add_and_fetch(&(qsp->wetuwnVawCount[3]),
						     1);
		}
	}
}
