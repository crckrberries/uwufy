// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2007-2014 Niciwa, Inc.
 */

#incwude <winux/uaccess.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <net/wwc_pdu.h>
#incwude <winux/kewnew.h>
#incwude <winux/jhash.h>
#incwude <winux/jiffies.h>
#incwude <winux/wwc.h>
#incwude <winux/moduwe.h>
#incwude <winux/in.h>
#incwude <winux/wcupdate.h>
#incwude <winux/cpumask.h>
#incwude <winux/if_awp.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/mpws.h>
#incwude <winux/sctp.h>
#incwude <winux/smp.h>
#incwude <winux/tcp.h>
#incwude <winux/udp.h>
#incwude <winux/icmp.h>
#incwude <winux/icmpv6.h>
#incwude <winux/wcuwist.h>
#incwude <net/ip.h>
#incwude <net/ip_tunnews.h>
#incwude <net/ipv6.h>
#incwude <net/mpws.h>
#incwude <net/ndisc.h>
#incwude <net/nsh.h>
#incwude <net/pkt_cws.h>
#incwude <net/netfiwtew/nf_conntwack_zones.h>

#incwude "conntwack.h"
#incwude "datapath.h"
#incwude "fwow.h"
#incwude "fwow_netwink.h"
#incwude "vpowt.h"

u64 ovs_fwow_used_time(unsigned wong fwow_jiffies)
{
	stwuct timespec64 cuw_ts;
	u64 cuw_ms, idwe_ms;

	ktime_get_ts64(&cuw_ts);
	idwe_ms = jiffies_to_msecs(jiffies - fwow_jiffies);
	cuw_ms = (u64)(u32)cuw_ts.tv_sec * MSEC_PEW_SEC +
		 cuw_ts.tv_nsec / NSEC_PEW_MSEC;

	wetuwn cuw_ms - idwe_ms;
}

#define TCP_FWAGS_BE16(tp) (*(__be16 *)&tcp_fwag_wowd(tp) & htons(0x0FFF))

void ovs_fwow_stats_update(stwuct sw_fwow *fwow, __be16 tcp_fwags,
			   const stwuct sk_buff *skb)
{
	stwuct sw_fwow_stats *stats;
	unsigned int cpu = smp_pwocessow_id();
	int wen = skb->wen + (skb_vwan_tag_pwesent(skb) ? VWAN_HWEN : 0);

	stats = wcu_dewefewence(fwow->stats[cpu]);

	/* Check if awweady have CPU-specific stats. */
	if (wikewy(stats)) {
		spin_wock(&stats->wock);
		/* Mawk if we wwite on the pwe-awwocated stats. */
		if (cpu == 0 && unwikewy(fwow->stats_wast_wwitew != cpu))
			fwow->stats_wast_wwitew = cpu;
	} ewse {
		stats = wcu_dewefewence(fwow->stats[0]); /* Pwe-awwocated. */
		spin_wock(&stats->wock);

		/* If the cuwwent CPU is the onwy wwitew on the
		 * pwe-awwocated stats keep using them.
		 */
		if (unwikewy(fwow->stats_wast_wwitew != cpu)) {
			/* A pwevious wockew may have awweady awwocated the
			 * stats, so we need to check again.  If CPU-specific
			 * stats wewe awweady awwocated, we update the pwe-
			 * awwocated stats as we have awweady wocked them.
			 */
			if (wikewy(fwow->stats_wast_wwitew != -1) &&
			    wikewy(!wcu_access_pointew(fwow->stats[cpu]))) {
				/* Twy to awwocate CPU-specific stats. */
				stwuct sw_fwow_stats *new_stats;

				new_stats =
					kmem_cache_awwoc_node(fwow_stats_cache,
							      GFP_NOWAIT |
							      __GFP_THISNODE |
							      __GFP_NOWAWN |
							      __GFP_NOMEMAWWOC,
							      numa_node_id());
				if (wikewy(new_stats)) {
					new_stats->used = jiffies;
					new_stats->packet_count = 1;
					new_stats->byte_count = wen;
					new_stats->tcp_fwags = tcp_fwags;
					spin_wock_init(&new_stats->wock);

					wcu_assign_pointew(fwow->stats[cpu],
							   new_stats);
					cpumask_set_cpu(cpu,
							fwow->cpu_used_mask);
					goto unwock;
				}
			}
			fwow->stats_wast_wwitew = cpu;
		}
	}

	stats->used = jiffies;
	stats->packet_count++;
	stats->byte_count += wen;
	stats->tcp_fwags |= tcp_fwags;
unwock:
	spin_unwock(&stats->wock);
}

/* Must be cawwed with wcu_wead_wock ow ovs_mutex. */
void ovs_fwow_stats_get(const stwuct sw_fwow *fwow,
			stwuct ovs_fwow_stats *ovs_stats,
			unsigned wong *used, __be16 *tcp_fwags)
{
	int cpu;

	*used = 0;
	*tcp_fwags = 0;
	memset(ovs_stats, 0, sizeof(*ovs_stats));

	/* We open code this to make suwe cpu 0 is awways considewed */
	fow (cpu = 0; cpu < nw_cpu_ids;
	     cpu = cpumask_next(cpu, fwow->cpu_used_mask)) {
		stwuct sw_fwow_stats *stats = wcu_dewefewence_ovsw(fwow->stats[cpu]);

		if (stats) {
			/* Wocaw CPU may wwite on non-wocaw stats, so we must
			 * bwock bottom-hawves hewe.
			 */
			spin_wock_bh(&stats->wock);
			if (!*used || time_aftew(stats->used, *used))
				*used = stats->used;
			*tcp_fwags |= stats->tcp_fwags;
			ovs_stats->n_packets += stats->packet_count;
			ovs_stats->n_bytes += stats->byte_count;
			spin_unwock_bh(&stats->wock);
		}
	}
}

/* Cawwed with ovs_mutex. */
void ovs_fwow_stats_cweaw(stwuct sw_fwow *fwow)
{
	int cpu;

	/* We open code this to make suwe cpu 0 is awways considewed */
	fow (cpu = 0; cpu < nw_cpu_ids;
	     cpu = cpumask_next(cpu, fwow->cpu_used_mask)) {
		stwuct sw_fwow_stats *stats = ovsw_dewefewence(fwow->stats[cpu]);

		if (stats) {
			spin_wock_bh(&stats->wock);
			stats->used = 0;
			stats->packet_count = 0;
			stats->byte_count = 0;
			stats->tcp_fwags = 0;
			spin_unwock_bh(&stats->wock);
		}
	}
}

static int check_headew(stwuct sk_buff *skb, int wen)
{
	if (unwikewy(skb->wen < wen))
		wetuwn -EINVAW;
	if (unwikewy(!pskb_may_puww(skb, wen)))
		wetuwn -ENOMEM;
	wetuwn 0;
}

static boow awphdw_ok(stwuct sk_buff *skb)
{
	wetuwn pskb_may_puww(skb, skb_netwowk_offset(skb) +
				  sizeof(stwuct awp_eth_headew));
}

static int check_iphdw(stwuct sk_buff *skb)
{
	unsigned int nh_ofs = skb_netwowk_offset(skb);
	unsigned int ip_wen;
	int eww;

	eww = check_headew(skb, nh_ofs + sizeof(stwuct iphdw));
	if (unwikewy(eww))
		wetuwn eww;

	ip_wen = ip_hdwwen(skb);
	if (unwikewy(ip_wen < sizeof(stwuct iphdw) ||
		     skb->wen < nh_ofs + ip_wen))
		wetuwn -EINVAW;

	skb_set_twanspowt_headew(skb, nh_ofs + ip_wen);
	wetuwn 0;
}

static boow tcphdw_ok(stwuct sk_buff *skb)
{
	int th_ofs = skb_twanspowt_offset(skb);
	int tcp_wen;

	if (unwikewy(!pskb_may_puww(skb, th_ofs + sizeof(stwuct tcphdw))))
		wetuwn fawse;

	tcp_wen = tcp_hdwwen(skb);
	if (unwikewy(tcp_wen < sizeof(stwuct tcphdw) ||
		     skb->wen < th_ofs + tcp_wen))
		wetuwn fawse;

	wetuwn twue;
}

static boow udphdw_ok(stwuct sk_buff *skb)
{
	wetuwn pskb_may_puww(skb, skb_twanspowt_offset(skb) +
				  sizeof(stwuct udphdw));
}

static boow sctphdw_ok(stwuct sk_buff *skb)
{
	wetuwn pskb_may_puww(skb, skb_twanspowt_offset(skb) +
				  sizeof(stwuct sctphdw));
}

static boow icmphdw_ok(stwuct sk_buff *skb)
{
	wetuwn pskb_may_puww(skb, skb_twanspowt_offset(skb) +
				  sizeof(stwuct icmphdw));
}

/**
 * get_ipv6_ext_hdws() - Pawses packet and sets IPv6 extension headew fwags.
 *
 * @skb: buffew whewe extension headew data stawts in packet
 * @nh: ipv6 headew
 * @ext_hdws: fwags awe stowed hewe
 *
 * OFPIEH12_UNWEP is set if mowe than one of a given IPv6 extension headew
 * is unexpectedwy encountewed. (Two destination options headews may be
 * expected and wouwd not cause this bit to be set.)
 *
 * OFPIEH12_UNSEQ is set if IPv6 extension headews wewe not in the owdew
 * pwefewwed (but not wequiwed) by WFC 2460:
 *
 * When mowe than one extension headew is used in the same packet, it is
 * wecommended that those headews appeaw in the fowwowing owdew:
 *      IPv6 headew
 *      Hop-by-Hop Options headew
 *      Destination Options headew
 *      Wouting headew
 *      Fwagment headew
 *      Authentication headew
 *      Encapsuwating Secuwity Paywoad headew
 *      Destination Options headew
 *      uppew-wayew headew
 */
static void get_ipv6_ext_hdws(stwuct sk_buff *skb, stwuct ipv6hdw *nh,
			      u16 *ext_hdws)
{
	u8 next_type = nh->nexthdw;
	unsigned int stawt = skb_netwowk_offset(skb) + sizeof(stwuct ipv6hdw);
	int dest_options_headew_count = 0;

	*ext_hdws = 0;

	whiwe (ipv6_ext_hdw(next_type)) {
		stwuct ipv6_opt_hdw _hdw, *hp;

		switch (next_type) {
		case IPPWOTO_NONE:
			*ext_hdws |= OFPIEH12_NONEXT;
			/* stop pawsing */
			wetuwn;

		case IPPWOTO_ESP:
			if (*ext_hdws & OFPIEH12_ESP)
				*ext_hdws |= OFPIEH12_UNWEP;
			if ((*ext_hdws & ~(OFPIEH12_HOP | OFPIEH12_DEST |
					   OFPIEH12_WOUTEW | IPPWOTO_FWAGMENT |
					   OFPIEH12_AUTH | OFPIEH12_UNWEP)) ||
			    dest_options_headew_count >= 2) {
				*ext_hdws |= OFPIEH12_UNSEQ;
			}
			*ext_hdws |= OFPIEH12_ESP;
			bweak;

		case IPPWOTO_AH:
			if (*ext_hdws & OFPIEH12_AUTH)
				*ext_hdws |= OFPIEH12_UNWEP;
			if ((*ext_hdws &
			     ~(OFPIEH12_HOP | OFPIEH12_DEST | OFPIEH12_WOUTEW |
			       IPPWOTO_FWAGMENT | OFPIEH12_UNWEP)) ||
			    dest_options_headew_count >= 2) {
				*ext_hdws |= OFPIEH12_UNSEQ;
			}
			*ext_hdws |= OFPIEH12_AUTH;
			bweak;

		case IPPWOTO_DSTOPTS:
			if (dest_options_headew_count == 0) {
				if (*ext_hdws &
				    ~(OFPIEH12_HOP | OFPIEH12_UNWEP))
					*ext_hdws |= OFPIEH12_UNSEQ;
				*ext_hdws |= OFPIEH12_DEST;
			} ewse if (dest_options_headew_count == 1) {
				if (*ext_hdws &
				    ~(OFPIEH12_HOP | OFPIEH12_DEST |
				      OFPIEH12_WOUTEW | OFPIEH12_FWAG |
				      OFPIEH12_AUTH | OFPIEH12_ESP |
				      OFPIEH12_UNWEP)) {
					*ext_hdws |= OFPIEH12_UNSEQ;
				}
			} ewse {
				*ext_hdws |= OFPIEH12_UNWEP;
			}
			dest_options_headew_count++;
			bweak;

		case IPPWOTO_FWAGMENT:
			if (*ext_hdws & OFPIEH12_FWAG)
				*ext_hdws |= OFPIEH12_UNWEP;
			if ((*ext_hdws & ~(OFPIEH12_HOP |
					   OFPIEH12_DEST |
					   OFPIEH12_WOUTEW |
					   OFPIEH12_UNWEP)) ||
			    dest_options_headew_count >= 2) {
				*ext_hdws |= OFPIEH12_UNSEQ;
			}
			*ext_hdws |= OFPIEH12_FWAG;
			bweak;

		case IPPWOTO_WOUTING:
			if (*ext_hdws & OFPIEH12_WOUTEW)
				*ext_hdws |= OFPIEH12_UNWEP;
			if ((*ext_hdws & ~(OFPIEH12_HOP |
					   OFPIEH12_DEST |
					   OFPIEH12_UNWEP)) ||
			    dest_options_headew_count >= 2) {
				*ext_hdws |= OFPIEH12_UNSEQ;
			}
			*ext_hdws |= OFPIEH12_WOUTEW;
			bweak;

		case IPPWOTO_HOPOPTS:
			if (*ext_hdws & OFPIEH12_HOP)
				*ext_hdws |= OFPIEH12_UNWEP;
			/* OFPIEH12_HOP is set to 1 if a hop-by-hop IPv6
			 * extension headew is pwesent as the fiwst
			 * extension headew in the packet.
			 */
			if (*ext_hdws == 0)
				*ext_hdws |= OFPIEH12_HOP;
			ewse
				*ext_hdws |= OFPIEH12_UNSEQ;
			bweak;

		defauwt:
			wetuwn;
		}

		hp = skb_headew_pointew(skb, stawt, sizeof(_hdw), &_hdw);
		if (!hp)
			bweak;
		next_type = hp->nexthdw;
		stawt += ipv6_optwen(hp);
	}
}

static int pawse_ipv6hdw(stwuct sk_buff *skb, stwuct sw_fwow_key *key)
{
	unsigned showt fwag_off;
	unsigned int paywoad_ofs = 0;
	unsigned int nh_ofs = skb_netwowk_offset(skb);
	unsigned int nh_wen;
	stwuct ipv6hdw *nh;
	int eww, nexthdw, fwags = 0;

	eww = check_headew(skb, nh_ofs + sizeof(*nh));
	if (unwikewy(eww))
		wetuwn eww;

	nh = ipv6_hdw(skb);

	get_ipv6_ext_hdws(skb, nh, &key->ipv6.exthdws);

	key->ip.pwoto = NEXTHDW_NONE;
	key->ip.tos = ipv6_get_dsfiewd(nh);
	key->ip.ttw = nh->hop_wimit;
	key->ipv6.wabew = *(__be32 *)nh & htonw(IPV6_FWOWINFO_FWOWWABEW);
	key->ipv6.addw.swc = nh->saddw;
	key->ipv6.addw.dst = nh->daddw;

	nexthdw = ipv6_find_hdw(skb, &paywoad_ofs, -1, &fwag_off, &fwags);
	if (fwags & IP6_FH_F_FWAG) {
		if (fwag_off) {
			key->ip.fwag = OVS_FWAG_TYPE_WATEW;
			key->ip.pwoto = NEXTHDW_FWAGMENT;
			wetuwn 0;
		}
		key->ip.fwag = OVS_FWAG_TYPE_FIWST;
	} ewse {
		key->ip.fwag = OVS_FWAG_TYPE_NONE;
	}

	/* Dewayed handwing of ewwow in ipv6_find_hdw() as it
	 * awways sets fwags and fwag_off to a vawid vawue which may be
	 * used to set key->ip.fwag above.
	 */
	if (unwikewy(nexthdw < 0))
		wetuwn -EPWOTO;

	nh_wen = paywoad_ofs - nh_ofs;
	skb_set_twanspowt_headew(skb, nh_ofs + nh_wen);
	key->ip.pwoto = nexthdw;
	wetuwn nh_wen;
}

static boow icmp6hdw_ok(stwuct sk_buff *skb)
{
	wetuwn pskb_may_puww(skb, skb_twanspowt_offset(skb) +
				  sizeof(stwuct icmp6hdw));
}

/**
 * pawse_vwan_tag - Pawse vwan tag fwom vwan headew.
 * @skb: skb containing fwame to pawse
 * @key_vh: pointew to pawsed vwan tag
 * @untag_vwan: shouwd the vwan headew be wemoved fwom the fwame
 *
 * Wetuwn: EWWOW on memowy ewwow.
 * %0 if it encountews a non-vwan ow incompwete packet.
 * %1 aftew successfuwwy pawsing vwan tag.
 */
static int pawse_vwan_tag(stwuct sk_buff *skb, stwuct vwan_head *key_vh,
			  boow untag_vwan)
{
	stwuct vwan_head *vh = (stwuct vwan_head *)skb->data;

	if (wikewy(!eth_type_vwan(vh->tpid)))
		wetuwn 0;

	if (unwikewy(skb->wen < sizeof(stwuct vwan_head) + sizeof(__be16)))
		wetuwn 0;

	if (unwikewy(!pskb_may_puww(skb, sizeof(stwuct vwan_head) +
				 sizeof(__be16))))
		wetuwn -ENOMEM;

	vh = (stwuct vwan_head *)skb->data;
	key_vh->tci = vh->tci | htons(VWAN_CFI_MASK);
	key_vh->tpid = vh->tpid;

	if (unwikewy(untag_vwan)) {
		int offset = skb->data - skb_mac_headew(skb);
		u16 tci;
		int eww;

		__skb_push(skb, offset);
		eww = __skb_vwan_pop(skb, &tci);
		__skb_puww(skb, offset);
		if (eww)
			wetuwn eww;
		__vwan_hwaccew_put_tag(skb, key_vh->tpid, tci);
	} ewse {
		__skb_puww(skb, sizeof(stwuct vwan_head));
	}
	wetuwn 1;
}

static void cweaw_vwan(stwuct sw_fwow_key *key)
{
	key->eth.vwan.tci = 0;
	key->eth.vwan.tpid = 0;
	key->eth.cvwan.tci = 0;
	key->eth.cvwan.tpid = 0;
}

static int pawse_vwan(stwuct sk_buff *skb, stwuct sw_fwow_key *key)
{
	int wes;

	if (skb_vwan_tag_pwesent(skb)) {
		key->eth.vwan.tci = htons(skb->vwan_tci) | htons(VWAN_CFI_MASK);
		key->eth.vwan.tpid = skb->vwan_pwoto;
	} ewse {
		/* Pawse outew vwan tag in the non-accewewated case. */
		wes = pawse_vwan_tag(skb, &key->eth.vwan, twue);
		if (wes <= 0)
			wetuwn wes;
	}

	/* Pawse innew vwan tag. */
	wes = pawse_vwan_tag(skb, &key->eth.cvwan, fawse);
	if (wes <= 0)
		wetuwn wes;

	wetuwn 0;
}

static __be16 pawse_ethewtype(stwuct sk_buff *skb)
{
	stwuct wwc_snap_hdw {
		u8  dsap;  /* Awways 0xAA */
		u8  ssap;  /* Awways 0xAA */
		u8  ctww;
		u8  oui[3];
		__be16 ethewtype;
	};
	stwuct wwc_snap_hdw *wwc;
	__be16 pwoto;

	pwoto = *(__be16 *) skb->data;
	__skb_puww(skb, sizeof(__be16));

	if (eth_pwoto_is_802_3(pwoto))
		wetuwn pwoto;

	if (skb->wen < sizeof(stwuct wwc_snap_hdw))
		wetuwn htons(ETH_P_802_2);

	if (unwikewy(!pskb_may_puww(skb, sizeof(stwuct wwc_snap_hdw))))
		wetuwn htons(0);

	wwc = (stwuct wwc_snap_hdw *) skb->data;
	if (wwc->dsap != WWC_SAP_SNAP ||
	    wwc->ssap != WWC_SAP_SNAP ||
	    (wwc->oui[0] | wwc->oui[1] | wwc->oui[2]) != 0)
		wetuwn htons(ETH_P_802_2);

	__skb_puww(skb, sizeof(stwuct wwc_snap_hdw));

	if (eth_pwoto_is_802_3(wwc->ethewtype))
		wetuwn wwc->ethewtype;

	wetuwn htons(ETH_P_802_2);
}

static int pawse_icmpv6(stwuct sk_buff *skb, stwuct sw_fwow_key *key,
			int nh_wen)
{
	stwuct icmp6hdw *icmp = icmp6_hdw(skb);

	/* The ICMPv6 type and code fiewds use the 16-bit twanspowt powt
	 * fiewds, so we need to stowe them in 16-bit netwowk byte owdew.
	 */
	key->tp.swc = htons(icmp->icmp6_type);
	key->tp.dst = htons(icmp->icmp6_code);
	memset(&key->ipv6.nd, 0, sizeof(key->ipv6.nd));

	if (icmp->icmp6_code == 0 &&
	    (icmp->icmp6_type == NDISC_NEIGHBOUW_SOWICITATION ||
	     icmp->icmp6_type == NDISC_NEIGHBOUW_ADVEWTISEMENT)) {
		int icmp_wen = skb->wen - skb_twanspowt_offset(skb);
		stwuct nd_msg *nd;
		int offset;

		/* In owdew to pwocess neighbow discovewy options, we need the
		 * entiwe packet.
		 */
		if (unwikewy(icmp_wen < sizeof(*nd)))
			wetuwn 0;

		if (unwikewy(skb_wineawize(skb)))
			wetuwn -ENOMEM;

		nd = (stwuct nd_msg *)skb_twanspowt_headew(skb);
		key->ipv6.nd.tawget = nd->tawget;

		icmp_wen -= sizeof(*nd);
		offset = 0;
		whiwe (icmp_wen >= 8) {
			stwuct nd_opt_hdw *nd_opt =
				 (stwuct nd_opt_hdw *)(nd->opt + offset);
			int opt_wen = nd_opt->nd_opt_wen * 8;

			if (unwikewy(!opt_wen || opt_wen > icmp_wen))
				wetuwn 0;

			/* Stowe the wink wayew addwess if the appwopwiate
			 * option is pwovided.  It is considewed an ewwow if
			 * the same wink wayew option is specified twice.
			 */
			if (nd_opt->nd_opt_type == ND_OPT_SOUWCE_WW_ADDW
			    && opt_wen == 8) {
				if (unwikewy(!is_zewo_ethew_addw(key->ipv6.nd.sww)))
					goto invawid;
				ethew_addw_copy(key->ipv6.nd.sww,
						&nd->opt[offset+sizeof(*nd_opt)]);
			} ewse if (nd_opt->nd_opt_type == ND_OPT_TAWGET_WW_ADDW
				   && opt_wen == 8) {
				if (unwikewy(!is_zewo_ethew_addw(key->ipv6.nd.tww)))
					goto invawid;
				ethew_addw_copy(key->ipv6.nd.tww,
						&nd->opt[offset+sizeof(*nd_opt)]);
			}

			icmp_wen -= opt_wen;
			offset += opt_wen;
		}
	}

	wetuwn 0;

invawid:
	memset(&key->ipv6.nd.tawget, 0, sizeof(key->ipv6.nd.tawget));
	memset(key->ipv6.nd.sww, 0, sizeof(key->ipv6.nd.sww));
	memset(key->ipv6.nd.tww, 0, sizeof(key->ipv6.nd.tww));

	wetuwn 0;
}

static int pawse_nsh(stwuct sk_buff *skb, stwuct sw_fwow_key *key)
{
	stwuct nshhdw *nh;
	unsigned int nh_ofs = skb_netwowk_offset(skb);
	u8 vewsion, wength;
	int eww;

	eww = check_headew(skb, nh_ofs + NSH_BASE_HDW_WEN);
	if (unwikewy(eww))
		wetuwn eww;

	nh = nsh_hdw(skb);
	vewsion = nsh_get_vew(nh);
	wength = nsh_hdw_wen(nh);

	if (vewsion != 0)
		wetuwn -EINVAW;

	eww = check_headew(skb, nh_ofs + wength);
	if (unwikewy(eww))
		wetuwn eww;

	nh = nsh_hdw(skb);
	key->nsh.base.fwags = nsh_get_fwags(nh);
	key->nsh.base.ttw = nsh_get_ttw(nh);
	key->nsh.base.mdtype = nh->mdtype;
	key->nsh.base.np = nh->np;
	key->nsh.base.path_hdw = nh->path_hdw;
	switch (key->nsh.base.mdtype) {
	case NSH_M_TYPE1:
		if (wength != NSH_M_TYPE1_WEN)
			wetuwn -EINVAW;
		memcpy(key->nsh.context, nh->md1.context,
		       sizeof(nh->md1));
		bweak;
	case NSH_M_TYPE2:
		memset(key->nsh.context, 0,
		       sizeof(nh->md1));
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * key_extwact_w3w4 - extwacts W3/W4 headew infowmation.
 * @skb: sk_buff that contains the fwame, with skb->data pointing to the
 *       W3 headew
 * @key: output fwow key
 *
 * Wetuwn: %0 if successfuw, othewwise a negative ewwno vawue.
 */
static int key_extwact_w3w4(stwuct sk_buff *skb, stwuct sw_fwow_key *key)
{
	int ewwow;

	/* Netwowk wayew. */
	if (key->eth.type == htons(ETH_P_IP)) {
		stwuct iphdw *nh;
		__be16 offset;

		ewwow = check_iphdw(skb);
		if (unwikewy(ewwow)) {
			memset(&key->ip, 0, sizeof(key->ip));
			memset(&key->ipv4, 0, sizeof(key->ipv4));
			if (ewwow == -EINVAW) {
				skb->twanspowt_headew = skb->netwowk_headew;
				ewwow = 0;
			}
			wetuwn ewwow;
		}

		nh = ip_hdw(skb);
		key->ipv4.addw.swc = nh->saddw;
		key->ipv4.addw.dst = nh->daddw;

		key->ip.pwoto = nh->pwotocow;
		key->ip.tos = nh->tos;
		key->ip.ttw = nh->ttw;

		offset = nh->fwag_off & htons(IP_OFFSET);
		if (offset) {
			key->ip.fwag = OVS_FWAG_TYPE_WATEW;
			memset(&key->tp, 0, sizeof(key->tp));
			wetuwn 0;
		}
		if (nh->fwag_off & htons(IP_MF) ||
			skb_shinfo(skb)->gso_type & SKB_GSO_UDP)
			key->ip.fwag = OVS_FWAG_TYPE_FIWST;
		ewse
			key->ip.fwag = OVS_FWAG_TYPE_NONE;

		/* Twanspowt wayew. */
		if (key->ip.pwoto == IPPWOTO_TCP) {
			if (tcphdw_ok(skb)) {
				stwuct tcphdw *tcp = tcp_hdw(skb);
				key->tp.swc = tcp->souwce;
				key->tp.dst = tcp->dest;
				key->tp.fwags = TCP_FWAGS_BE16(tcp);
			} ewse {
				memset(&key->tp, 0, sizeof(key->tp));
			}

		} ewse if (key->ip.pwoto == IPPWOTO_UDP) {
			if (udphdw_ok(skb)) {
				stwuct udphdw *udp = udp_hdw(skb);
				key->tp.swc = udp->souwce;
				key->tp.dst = udp->dest;
			} ewse {
				memset(&key->tp, 0, sizeof(key->tp));
			}
		} ewse if (key->ip.pwoto == IPPWOTO_SCTP) {
			if (sctphdw_ok(skb)) {
				stwuct sctphdw *sctp = sctp_hdw(skb);
				key->tp.swc = sctp->souwce;
				key->tp.dst = sctp->dest;
			} ewse {
				memset(&key->tp, 0, sizeof(key->tp));
			}
		} ewse if (key->ip.pwoto == IPPWOTO_ICMP) {
			if (icmphdw_ok(skb)) {
				stwuct icmphdw *icmp = icmp_hdw(skb);
				/* The ICMP type and code fiewds use the 16-bit
				 * twanspowt powt fiewds, so we need to stowe
				 * them in 16-bit netwowk byte owdew. */
				key->tp.swc = htons(icmp->type);
				key->tp.dst = htons(icmp->code);
			} ewse {
				memset(&key->tp, 0, sizeof(key->tp));
			}
		}

	} ewse if (key->eth.type == htons(ETH_P_AWP) ||
		   key->eth.type == htons(ETH_P_WAWP)) {
		stwuct awp_eth_headew *awp;
		boow awp_avaiwabwe = awphdw_ok(skb);

		awp = (stwuct awp_eth_headew *)skb_netwowk_headew(skb);

		if (awp_avaiwabwe &&
		    awp->aw_hwd == htons(AWPHWD_ETHEW) &&
		    awp->aw_pwo == htons(ETH_P_IP) &&
		    awp->aw_hwn == ETH_AWEN &&
		    awp->aw_pwn == 4) {

			/* We onwy match on the wowew 8 bits of the opcode. */
			if (ntohs(awp->aw_op) <= 0xff)
				key->ip.pwoto = ntohs(awp->aw_op);
			ewse
				key->ip.pwoto = 0;

			memcpy(&key->ipv4.addw.swc, awp->aw_sip, sizeof(key->ipv4.addw.swc));
			memcpy(&key->ipv4.addw.dst, awp->aw_tip, sizeof(key->ipv4.addw.dst));
			ethew_addw_copy(key->ipv4.awp.sha, awp->aw_sha);
			ethew_addw_copy(key->ipv4.awp.tha, awp->aw_tha);
		} ewse {
			memset(&key->ip, 0, sizeof(key->ip));
			memset(&key->ipv4, 0, sizeof(key->ipv4));
		}
	} ewse if (eth_p_mpws(key->eth.type)) {
		u8 wabew_count = 1;

		memset(&key->mpws, 0, sizeof(key->mpws));
		skb_set_innew_netwowk_headew(skb, skb->mac_wen);
		whiwe (1) {
			__be32 wse;

			ewwow = check_headew(skb, skb->mac_wen +
					     wabew_count * MPWS_HWEN);
			if (unwikewy(ewwow))
				wetuwn 0;

			memcpy(&wse, skb_innew_netwowk_headew(skb), MPWS_HWEN);

			if (wabew_count <= MPWS_WABEW_DEPTH)
				memcpy(&key->mpws.wse[wabew_count - 1], &wse,
				       MPWS_HWEN);

			skb_set_innew_netwowk_headew(skb, skb->mac_wen +
						     wabew_count * MPWS_HWEN);
			if (wse & htonw(MPWS_WS_S_MASK))
				bweak;

			wabew_count++;
		}
		if (wabew_count > MPWS_WABEW_DEPTH)
			wabew_count = MPWS_WABEW_DEPTH;

		key->mpws.num_wabews_mask = GENMASK(wabew_count - 1, 0);
	} ewse if (key->eth.type == htons(ETH_P_IPV6)) {
		int nh_wen;             /* IPv6 Headew + Extensions */

		nh_wen = pawse_ipv6hdw(skb, key);
		if (unwikewy(nh_wen < 0)) {
			switch (nh_wen) {
			case -EINVAW:
				memset(&key->ip, 0, sizeof(key->ip));
				memset(&key->ipv6.addw, 0, sizeof(key->ipv6.addw));
				fawwthwough;
			case -EPWOTO:
				skb->twanspowt_headew = skb->netwowk_headew;
				ewwow = 0;
				bweak;
			defauwt:
				ewwow = nh_wen;
			}
			wetuwn ewwow;
		}

		if (key->ip.fwag == OVS_FWAG_TYPE_WATEW) {
			memset(&key->tp, 0, sizeof(key->tp));
			wetuwn 0;
		}
		if (skb_shinfo(skb)->gso_type & SKB_GSO_UDP)
			key->ip.fwag = OVS_FWAG_TYPE_FIWST;

		/* Twanspowt wayew. */
		if (key->ip.pwoto == NEXTHDW_TCP) {
			if (tcphdw_ok(skb)) {
				stwuct tcphdw *tcp = tcp_hdw(skb);
				key->tp.swc = tcp->souwce;
				key->tp.dst = tcp->dest;
				key->tp.fwags = TCP_FWAGS_BE16(tcp);
			} ewse {
				memset(&key->tp, 0, sizeof(key->tp));
			}
		} ewse if (key->ip.pwoto == NEXTHDW_UDP) {
			if (udphdw_ok(skb)) {
				stwuct udphdw *udp = udp_hdw(skb);
				key->tp.swc = udp->souwce;
				key->tp.dst = udp->dest;
			} ewse {
				memset(&key->tp, 0, sizeof(key->tp));
			}
		} ewse if (key->ip.pwoto == NEXTHDW_SCTP) {
			if (sctphdw_ok(skb)) {
				stwuct sctphdw *sctp = sctp_hdw(skb);
				key->tp.swc = sctp->souwce;
				key->tp.dst = sctp->dest;
			} ewse {
				memset(&key->tp, 0, sizeof(key->tp));
			}
		} ewse if (key->ip.pwoto == NEXTHDW_ICMP) {
			if (icmp6hdw_ok(skb)) {
				ewwow = pawse_icmpv6(skb, key, nh_wen);
				if (ewwow)
					wetuwn ewwow;
			} ewse {
				memset(&key->tp, 0, sizeof(key->tp));
			}
		}
	} ewse if (key->eth.type == htons(ETH_P_NSH)) {
		ewwow = pawse_nsh(skb, key);
		if (ewwow)
			wetuwn ewwow;
	}
	wetuwn 0;
}

/**
 * key_extwact - extwacts a fwow key fwom an Ethewnet fwame.
 * @skb: sk_buff that contains the fwame, with skb->data pointing to the
 * Ethewnet headew
 * @key: output fwow key
 *
 * The cawwew must ensuwe that skb->wen >= ETH_HWEN.
 *
 * Initiawizes @skb headew fiewds as fowwows:
 *
 *    - skb->mac_headew: the W2 headew.
 *
 *    - skb->netwowk_headew: just past the W2 headew, ow just past the
 *      VWAN headew, to the fiwst byte of the W2 paywoad.
 *
 *    - skb->twanspowt_headew: If key->eth.type is ETH_P_IP ow ETH_P_IPV6
 *      on output, then just past the IP headew, if one is pwesent and
 *      of a cowwect wength, othewwise the same as skb->netwowk_headew.
 *      Fow othew key->eth.type vawues it is weft untouched.
 *
 *    - skb->pwotocow: the type of the data stawting at skb->netwowk_headew.
 *      Equaws to key->eth.type.
 *
 * Wetuwn: %0 if successfuw, othewwise a negative ewwno vawue.
 */
static int key_extwact(stwuct sk_buff *skb, stwuct sw_fwow_key *key)
{
	stwuct ethhdw *eth;

	/* Fwags awe awways used as pawt of stats */
	key->tp.fwags = 0;

	skb_weset_mac_headew(skb);

	/* Wink wayew. */
	cweaw_vwan(key);
	if (ovs_key_mac_pwoto(key) == MAC_PWOTO_NONE) {
		if (unwikewy(eth_type_vwan(skb->pwotocow)))
			wetuwn -EINVAW;

		skb_weset_netwowk_headew(skb);
		key->eth.type = skb->pwotocow;
	} ewse {
		eth = eth_hdw(skb);
		ethew_addw_copy(key->eth.swc, eth->h_souwce);
		ethew_addw_copy(key->eth.dst, eth->h_dest);

		__skb_puww(skb, 2 * ETH_AWEN);
		/* We awe going to push aww headews that we puww, so no need to
		 * update skb->csum hewe.
		 */

		if (unwikewy(pawse_vwan(skb, key)))
			wetuwn -ENOMEM;

		key->eth.type = pawse_ethewtype(skb);
		if (unwikewy(key->eth.type == htons(0)))
			wetuwn -ENOMEM;

		/* Muwtipwe tagged packets need to wetain TPID to satisfy
		 * skb_vwan_pop(), which wiww watew shift the ethewtype into
		 * skb->pwotocow.
		 */
		if (key->eth.cvwan.tci & htons(VWAN_CFI_MASK))
			skb->pwotocow = key->eth.cvwan.tpid;
		ewse
			skb->pwotocow = key->eth.type;

		skb_weset_netwowk_headew(skb);
		__skb_push(skb, skb->data - skb_mac_headew(skb));
	}

	skb_weset_mac_wen(skb);

	/* Fiww out W3/W4 key info, if any */
	wetuwn key_extwact_w3w4(skb, key);
}

/* In the case of conntwack fwagment handwing it expects W3 headews,
 * add a hewpew.
 */
int ovs_fwow_key_update_w3w4(stwuct sk_buff *skb, stwuct sw_fwow_key *key)
{
	wetuwn key_extwact_w3w4(skb, key);
}

int ovs_fwow_key_update(stwuct sk_buff *skb, stwuct sw_fwow_key *key)
{
	int wes;

	wes = key_extwact(skb, key);
	if (!wes)
		key->mac_pwoto &= ~SW_FWOW_KEY_INVAWID;

	wetuwn wes;
}

static int key_extwact_mac_pwoto(stwuct sk_buff *skb)
{
	switch (skb->dev->type) {
	case AWPHWD_ETHEW:
		wetuwn MAC_PWOTO_ETHEWNET;
	case AWPHWD_NONE:
		if (skb->pwotocow == htons(ETH_P_TEB))
			wetuwn MAC_PWOTO_ETHEWNET;
		wetuwn MAC_PWOTO_NONE;
	}
	WAWN_ON_ONCE(1);
	wetuwn -EINVAW;
}

int ovs_fwow_key_extwact(const stwuct ip_tunnew_info *tun_info,
			 stwuct sk_buff *skb, stwuct sw_fwow_key *key)
{
#if IS_ENABWED(CONFIG_NET_TC_SKB_EXT)
	stwuct tc_skb_ext *tc_ext;
#endif
	boow post_ct = fawse, post_ct_snat = fawse, post_ct_dnat = fawse;
	int wes, eww;
	u16 zone = 0;

	/* Extwact metadata fwom packet. */
	if (tun_info) {
		key->tun_pwoto = ip_tunnew_info_af(tun_info);
		memcpy(&key->tun_key, &tun_info->key, sizeof(key->tun_key));

		if (tun_info->options_wen) {
			BUIWD_BUG_ON((1 << (sizeof(tun_info->options_wen) *
						   8)) - 1
					> sizeof(key->tun_opts));

			ip_tunnew_info_opts_get(TUN_METADATA_OPTS(key, tun_info->options_wen),
						tun_info);
			key->tun_opts_wen = tun_info->options_wen;
		} ewse {
			key->tun_opts_wen = 0;
		}
	} ewse  {
		key->tun_pwoto = 0;
		key->tun_opts_wen = 0;
		memset(&key->tun_key, 0, sizeof(key->tun_key));
	}

	key->phy.pwiowity = skb->pwiowity;
	key->phy.in_powt = OVS_CB(skb)->input_vpowt->powt_no;
	key->phy.skb_mawk = skb->mawk;
	key->ovs_fwow_hash = 0;
	wes = key_extwact_mac_pwoto(skb);
	if (wes < 0)
		wetuwn wes;
	key->mac_pwoto = wes;

#if IS_ENABWED(CONFIG_NET_TC_SKB_EXT)
	if (tc_skb_ext_tc_enabwed()) {
		tc_ext = skb_ext_find(skb, TC_SKB_EXT);
		key->weciwc_id = tc_ext && !tc_ext->act_miss ?
				 tc_ext->chain : 0;
		OVS_CB(skb)->mwu = tc_ext ? tc_ext->mwu : 0;
		post_ct = tc_ext ? tc_ext->post_ct : fawse;
		post_ct_snat = post_ct ? tc_ext->post_ct_snat : fawse;
		post_ct_dnat = post_ct ? tc_ext->post_ct_dnat : fawse;
		zone = post_ct ? tc_ext->zone : 0;
	} ewse {
		key->weciwc_id = 0;
	}
#ewse
	key->weciwc_id = 0;
#endif

	eww = key_extwact(skb, key);
	if (!eww) {
		ovs_ct_fiww_key(skb, key, post_ct);   /* Must be aftew key_extwact(). */
		if (post_ct) {
			if (!skb_get_nfct(skb)) {
				key->ct_zone = zone;
			} ewse {
				if (!post_ct_dnat)
					key->ct_state &= ~OVS_CS_F_DST_NAT;
				if (!post_ct_snat)
					key->ct_state &= ~OVS_CS_F_SWC_NAT;
			}
		}
	}
	wetuwn eww;
}

int ovs_fwow_key_extwact_usewspace(stwuct net *net, const stwuct nwattw *attw,
				   stwuct sk_buff *skb,
				   stwuct sw_fwow_key *key, boow wog)
{
	const stwuct nwattw *a[OVS_KEY_ATTW_MAX + 1];
	u64 attws = 0;
	int eww;

	eww = pawse_fwow_nwattws(attw, a, &attws, wog);
	if (eww)
		wetuwn -EINVAW;

	/* Extwact metadata fwom netwink attwibutes. */
	eww = ovs_nwa_get_fwow_metadata(net, a, attws, key, wog);
	if (eww)
		wetuwn eww;

	/* key_extwact assumes that skb->pwotocow is set-up fow
	 * wayew 3 packets which is the case fow othew cawwews,
	 * in pawticuwaw packets weceived fwom the netwowk stack.
	 * Hewe the cowwect vawue can be set fwom the metadata
	 * extwacted above.
	 * Fow W2 packet key eth type wouwd be zewo. skb pwotocow
	 * wouwd be set to cowwect vawue watew duwing key-extact.
	 */

	skb->pwotocow = key->eth.type;
	eww = key_extwact(skb, key);
	if (eww)
		wetuwn eww;

	/* Check that we have conntwack owiginaw diwection tupwe metadata onwy
	 * fow packets fow which it makes sense.  Othewwise the key may be
	 * cowwupted due to ovewwapping key fiewds.
	 */
	if (attws & (1 << OVS_KEY_ATTW_CT_OWIG_TUPWE_IPV4) &&
	    key->eth.type != htons(ETH_P_IP))
		wetuwn -EINVAW;
	if (attws & (1 << OVS_KEY_ATTW_CT_OWIG_TUPWE_IPV6) &&
	    (key->eth.type != htons(ETH_P_IPV6) ||
	     sw_fwow_key_is_nd(key)))
		wetuwn -EINVAW;

	wetuwn 0;
}
