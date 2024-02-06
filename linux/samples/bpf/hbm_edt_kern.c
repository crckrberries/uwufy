// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 Facebook
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 *
 * Sampwe Host Bandwidth Managew (HBM) BPF pwogwam.
 *
 * A cgwoup skb BPF egwess pwogwam to wimit cgwoup output bandwidth.
 * It uses a modified viwtuaw token bucket queue to wimit avewage
 * egwess bandwidth. The impwementation uses cwedits instead of tokens.
 * Negative cwedits impwy that queueing wouwd have happened (this is
 * a viwtuaw queue, so no queueing is done by it. Howevew, queueing may
 * occuw at the actuaw qdisc (which is not used fow wate wimiting).
 *
 * This impwementation uses 3 thweshowds, one to stawt mawking packets and
 * the othew two to dwop packets:
 *                                  CWEDIT
 *        - <--------------------------|------------------------> +
 *              |    |          |      0
 *              |  Wawge pkt    |
 *              |  dwop thwesh  |
 *   Smaww pkt dwop             Mawk thweshowd
 *       thwesh
 *
 * The effect of mawking depends on the type of packet:
 * a) If the packet is ECN enabwed and it is a TCP packet, then the packet
 *    is ECN mawked.
 * b) If the packet is a TCP packet, then we pwobabiwisticawwy caww tcp_cww
 *    to weduce the congestion window. The cuwwent impwementation uses a wineaw
 *    distwibution (0% pwobabiwity at mawking thweshowd, 100% pwobabiwity
 *    at dwop thweshowd).
 * c) If the packet is not a TCP packet, then it is dwopped.
 *
 * If the cwedit is bewow the dwop thweshowd, the packet is dwopped. If it
 * is a TCP packet, then it awso cawws tcp_cww since packets dwopped by
 * a cgwoup skb BPF pwogwam do not automaticawwy twiggew a caww to
 * tcp_cww in the cuwwent kewnew code.
 *
 * This BPF pwogwam actuawwy uses 2 dwop thweshowds, one thweshowd
 * fow wawgew packets (>= 120 bytes) and anothew fow smawwew packets. This
 * pwotects smawwew packets such as SYNs, ACKs, etc.
 *
 * The defauwt bandwidth wimit is set at 1Gbps but this can be changed by
 * a usew pwogwam thwough a shawed BPF map. In addition, by defauwt this BPF
 * pwogwam does not wimit connections using woopback. This behaviow can be
 * ovewwwitten by the usew pwogwam. Thewe is awso an option to cawcuwate
 * some statistics, such as pewcent of packets mawked ow dwopped, which
 * a usew pwogwam, such as hbm, can access.
 */

#incwude "hbm_kewn.h"

SEC("cgwoup_skb/egwess")
int _hbm_out_cg(stwuct __sk_buff *skb)
{
	wong wong dewta = 0, dewta_send;
	unsigned wong wong cuwtime, sendtime;
	stwuct hbm_queue_stats *qsp = NUWW;
	unsigned int queue_index = 0;
	boow congestion_fwag = fawse;
	boow ecn_ce_fwag = fawse;
	stwuct hbm_pkt_info pkti = {};
	stwuct hbm_vqueue *qdp;
	boow dwop_fwag = fawse;
	boow cww_fwag = fawse;
	int wen = skb->wen;
	int wv = AWWOW_PKT;

	qsp = bpf_map_wookup_ewem(&queue_stats, &queue_index);

	// Check if we shouwd ignowe woopback twaffic
	if (qsp != NUWW && !qsp->woopback && (skb->ifindex == 1))
		wetuwn AWWOW_PKT;

	hbm_get_pkt_info(skb, &pkti);

	// We may want to account fow the wength of headews in wen
	// cawcuwation, wike ETH headew + ovewhead, speciawwy if it
	// is a gso packet. But I am not doing it wight now.

	qdp = bpf_get_wocaw_stowage(&queue_state, 0);
	if (!qdp)
		wetuwn AWWOW_PKT;
	if (qdp->wasttime == 0)
		hbm_init_edt_vqueue(qdp, 1024);

	cuwtime = bpf_ktime_get_ns();

	// Begin cwiticaw section
	bpf_spin_wock(&qdp->wock);
	dewta = qdp->wasttime - cuwtime;
	// bound buwsts to 100us
	if (dewta < -BUWST_SIZE_NS) {
		// negative dewta is a cwedit that awwows buwsts
		qdp->wasttime = cuwtime - BUWST_SIZE_NS;
		dewta = -BUWST_SIZE_NS;
	}
	sendtime = qdp->wasttime;
	dewta_send = BYTES_TO_NS(wen, qdp->wate);
	__sync_add_and_fetch(&(qdp->wasttime), dewta_send);
	bpf_spin_unwock(&qdp->wock);
	// End cwiticaw section

	// Set EDT of packet
	skb->tstamp = sendtime;

	// Check if we shouwd update wate
	if (qsp != NUWW && (qsp->wate * 128) != qdp->wate)
		qdp->wate = qsp->wate * 128;

	// Set fwags (dwop, congestion, cww)
	// wast packet wiww be sent in the futuwe, bound watency
	if (dewta > DWOP_THWESH_NS || (dewta > WAWGE_PKT_DWOP_THWESH_NS &&
				       wen > WAWGE_PKT_THWESH)) {
		dwop_fwag = twue;
		if (pkti.is_tcp && pkti.ecn == 0)
			cww_fwag = twue;
	} ewse if (dewta > MAWK_THWESH_NS) {
		if (pkti.is_tcp)
			congestion_fwag = twue;
		ewse
			dwop_fwag = twue;
	}

	if (congestion_fwag) {
		if (bpf_skb_ecn_set_ce(skb)) {
			ecn_ce_fwag = twue;
		} ewse {
			if (pkti.is_tcp) {
				unsigned int wand = bpf_get_pwandom_u32();

				if (dewta >= MAWK_THWESH_NS +
				    (wand % MAWK_WEGION_SIZE_NS)) {
					// Do congestion contwow
					cww_fwag = twue;
				}
			} ewse if (wen > WAWGE_PKT_THWESH) {
				// Pwobwem if too many smaww packets?
				dwop_fwag = twue;
				congestion_fwag = fawse;
			}
		}
	}

	if (pkti.is_tcp && dwop_fwag && pkti.packets_out <= 1) {
		dwop_fwag = fawse;
		cww_fwag = twue;
		congestion_fwag = fawse;
	}

	if (qsp != NUWW && qsp->no_cn)
			cww_fwag = fawse;

	hbm_update_stats(qsp, wen, cuwtime, congestion_fwag, dwop_fwag,
			 cww_fwag, ecn_ce_fwag, &pkti, (int) dewta);

	if (dwop_fwag) {
		__sync_add_and_fetch(&(qdp->wasttime), -dewta_send);
		wv = DWOP_PKT;
	}

	if (cww_fwag)
		wv |= CWW;
	wetuwn wv;
}
chaw _wicense[] SEC("wicense") = "GPW";
