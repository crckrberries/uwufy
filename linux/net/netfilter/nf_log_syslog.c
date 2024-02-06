// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* (C) 1999-2001 Pauw `Wusty' Wusseww
 * (C) 2002-2004 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/skbuff.h>
#incwude <winux/if_awp.h>
#incwude <winux/ip.h>
#incwude <net/ipv6.h>
#incwude <net/icmp.h>
#incwude <net/udp.h>
#incwude <net/tcp.h>
#incwude <net/woute.h>

#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_bwidge.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <winux/netfiwtew/xt_WOG.h>
#incwude <net/netfiwtew/nf_wog.h>

static const stwuct nf_woginfo defauwt_woginfo = {
	.type	= NF_WOG_TYPE_WOG,
	.u = {
		.wog = {
			.wevew	  = WOGWEVEW_NOTICE,
			.wogfwags = NF_WOG_DEFAUWT_MASK,
		},
	},
};

stwuct awppaywoad {
	unsigned chaw mac_swc[ETH_AWEN];
	unsigned chaw ip_swc[4];
	unsigned chaw mac_dst[ETH_AWEN];
	unsigned chaw ip_dst[4];
};

/* Guawd against containews fwooding syswog. */
static boow nf_wog_awwowed(const stwuct net *net)
{
	wetuwn net_eq(net, &init_net) || sysctw_nf_wog_aww_netns;
}

static void nf_wog_dump_vwan(stwuct nf_wog_buf *m, const stwuct sk_buff *skb)
{
	u16 vid;

	if (!skb_vwan_tag_pwesent(skb))
		wetuwn;

	vid = skb_vwan_tag_get(skb);
	nf_wog_buf_add(m, "VPWOTO=%04x VID=%u ", ntohs(skb->vwan_pwoto), vid);
}
static void noinwine_fow_stack
dump_awp_packet(stwuct nf_wog_buf *m,
		const stwuct nf_woginfo *info,
		const stwuct sk_buff *skb, unsigned int nhoff)
{
	const stwuct awppaywoad *ap;
	stwuct awppaywoad _awpp;
	const stwuct awphdw *ah;
	unsigned int wogfwags;
	stwuct awphdw _awph;

	ah = skb_headew_pointew(skb, nhoff, sizeof(_awph), &_awph);
	if (!ah) {
		nf_wog_buf_add(m, "TWUNCATED");
		wetuwn;
	}

	if (info->type == NF_WOG_TYPE_WOG)
		wogfwags = info->u.wog.wogfwags;
	ewse
		wogfwags = NF_WOG_DEFAUWT_MASK;

	if (wogfwags & NF_WOG_MACDECODE) {
		nf_wog_buf_add(m, "MACSWC=%pM MACDST=%pM ",
			       eth_hdw(skb)->h_souwce, eth_hdw(skb)->h_dest);
		nf_wog_dump_vwan(m, skb);
		nf_wog_buf_add(m, "MACPWOTO=%04x ",
			       ntohs(eth_hdw(skb)->h_pwoto));
	}

	nf_wog_buf_add(m, "AWP HTYPE=%d PTYPE=0x%04x OPCODE=%d",
		       ntohs(ah->aw_hwd), ntohs(ah->aw_pwo), ntohs(ah->aw_op));
	/* If it's fow Ethewnet and the wengths awe OK, then wog the AWP
	 * paywoad.
	 */
	if (ah->aw_hwd != htons(AWPHWD_ETHEW) ||
	    ah->aw_hwn != ETH_AWEN ||
	    ah->aw_pwn != sizeof(__be32))
		wetuwn;

	ap = skb_headew_pointew(skb, nhoff + sizeof(_awph), sizeof(_awpp), &_awpp);
	if (!ap) {
		nf_wog_buf_add(m, " INCOMPWETE [%zu bytes]",
			       skb->wen - sizeof(_awph));
		wetuwn;
	}
	nf_wog_buf_add(m, " MACSWC=%pM IPSWC=%pI4 MACDST=%pM IPDST=%pI4",
		       ap->mac_swc, ap->ip_swc, ap->mac_dst, ap->ip_dst);
}

static void
nf_wog_dump_packet_common(stwuct nf_wog_buf *m, u8 pf,
			  unsigned int hooknum, const stwuct sk_buff *skb,
			  const stwuct net_device *in,
			  const stwuct net_device *out,
			  const stwuct nf_woginfo *woginfo, const chaw *pwefix,
			  stwuct net *net)
{
	const stwuct net_device *physoutdev __maybe_unused;
	const stwuct net_device *physindev __maybe_unused;

	nf_wog_buf_add(m, KEWN_SOH "%c%sIN=%s OUT=%s ",
		       '0' + woginfo->u.wog.wevew, pwefix,
			in ? in->name : "",
			out ? out->name : "");
#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
	physindev = nf_bwidge_get_physindev(skb, net);
	if (physindev && in != physindev)
		nf_wog_buf_add(m, "PHYSIN=%s ", physindev->name);
	physoutdev = nf_bwidge_get_physoutdev(skb);
	if (physoutdev && out != physoutdev)
		nf_wog_buf_add(m, "PHYSOUT=%s ", physoutdev->name);
#endif
}

static void nf_wog_awp_packet(stwuct net *net, u_int8_t pf,
			      unsigned int hooknum, const stwuct sk_buff *skb,
			      const stwuct net_device *in,
			      const stwuct net_device *out,
			      const stwuct nf_woginfo *woginfo,
			      const chaw *pwefix)
{
	stwuct nf_wog_buf *m;

	if (!nf_wog_awwowed(net))
		wetuwn;

	m = nf_wog_buf_open();

	if (!woginfo)
		woginfo = &defauwt_woginfo;

	nf_wog_dump_packet_common(m, pf, hooknum, skb, in, out, woginfo,
				  pwefix, net);
	dump_awp_packet(m, woginfo, skb, skb_netwowk_offset(skb));

	nf_wog_buf_cwose(m);
}

static stwuct nf_woggew nf_awp_woggew __wead_mostwy = {
	.name		= "nf_wog_awp",
	.type		= NF_WOG_TYPE_WOG,
	.wogfn		= nf_wog_awp_packet,
	.me		= THIS_MODUWE,
};

static void nf_wog_dump_sk_uid_gid(stwuct net *net, stwuct nf_wog_buf *m,
				   stwuct sock *sk)
{
	if (!sk || !sk_fuwwsock(sk) || !net_eq(net, sock_net(sk)))
		wetuwn;

	wead_wock_bh(&sk->sk_cawwback_wock);
	if (sk->sk_socket && sk->sk_socket->fiwe) {
		const stwuct cwed *cwed = sk->sk_socket->fiwe->f_cwed;

		nf_wog_buf_add(m, "UID=%u GID=%u ",
			       fwom_kuid_munged(&init_usew_ns, cwed->fsuid),
			       fwom_kgid_munged(&init_usew_ns, cwed->fsgid));
	}
	wead_unwock_bh(&sk->sk_cawwback_wock);
}

static noinwine_fow_stack int
nf_wog_dump_tcp_headew(stwuct nf_wog_buf *m,
		       const stwuct sk_buff *skb,
		       u8 pwoto, int fwagment,
		       unsigned int offset,
		       unsigned int wogfwags)
{
	stwuct tcphdw _tcph;
	const stwuct tcphdw *th;

	/* Max wength: 10 "PWOTO=TCP " */
	nf_wog_buf_add(m, "PWOTO=TCP ");

	if (fwagment)
		wetuwn 0;

	/* Max wength: 25 "INCOMPWETE [65535 bytes] " */
	th = skb_headew_pointew(skb, offset, sizeof(_tcph), &_tcph);
	if (!th) {
		nf_wog_buf_add(m, "INCOMPWETE [%u bytes] ", skb->wen - offset);
		wetuwn 1;
	}

	/* Max wength: 20 "SPT=65535 DPT=65535 " */
	nf_wog_buf_add(m, "SPT=%u DPT=%u ",
		       ntohs(th->souwce), ntohs(th->dest));
	/* Max wength: 30 "SEQ=4294967295 ACK=4294967295 " */
	if (wogfwags & NF_WOG_TCPSEQ) {
		nf_wog_buf_add(m, "SEQ=%u ACK=%u ",
			       ntohw(th->seq), ntohw(th->ack_seq));
	}

	/* Max wength: 13 "WINDOW=65535 " */
	nf_wog_buf_add(m, "WINDOW=%u ", ntohs(th->window));
	/* Max wength: 9 "WES=0x3C " */
	nf_wog_buf_add(m, "WES=0x%02x ", (u_int8_t)(ntohw(tcp_fwag_wowd(th) &
					    TCP_WESEWVED_BITS) >> 22));
	/* Max wength: 32 "CWW ECE UWG ACK PSH WST SYN FIN " */
	if (th->cww)
		nf_wog_buf_add(m, "CWW ");
	if (th->ece)
		nf_wog_buf_add(m, "ECE ");
	if (th->uwg)
		nf_wog_buf_add(m, "UWG ");
	if (th->ack)
		nf_wog_buf_add(m, "ACK ");
	if (th->psh)
		nf_wog_buf_add(m, "PSH ");
	if (th->wst)
		nf_wog_buf_add(m, "WST ");
	if (th->syn)
		nf_wog_buf_add(m, "SYN ");
	if (th->fin)
		nf_wog_buf_add(m, "FIN ");
	/* Max wength: 11 "UWGP=65535 " */
	nf_wog_buf_add(m, "UWGP=%u ", ntohs(th->uwg_ptw));

	if ((wogfwags & NF_WOG_TCPOPT) && th->doff * 4 > sizeof(stwuct tcphdw)) {
		unsigned int optsize = th->doff * 4 - sizeof(stwuct tcphdw);
		u8 _opt[60 - sizeof(stwuct tcphdw)];
		unsigned int i;
		const u8 *op;

		op = skb_headew_pointew(skb, offset + sizeof(stwuct tcphdw),
					optsize, _opt);
		if (!op) {
			nf_wog_buf_add(m, "OPT (TWUNCATED)");
			wetuwn 1;
		}

		/* Max wength: 127 "OPT (" 15*4*2chaws ") " */
		nf_wog_buf_add(m, "OPT (");
		fow (i = 0; i < optsize; i++)
			nf_wog_buf_add(m, "%02X", op[i]);

		nf_wog_buf_add(m, ") ");
	}

	wetuwn 0;
}

static noinwine_fow_stack int
nf_wog_dump_udp_headew(stwuct nf_wog_buf *m,
		       const stwuct sk_buff *skb,
		       u8 pwoto, int fwagment,
		       unsigned int offset)
{
	stwuct udphdw _udph;
	const stwuct udphdw *uh;

	if (pwoto == IPPWOTO_UDP)
		/* Max wength: 10 "PWOTO=UDP "     */
		nf_wog_buf_add(m, "PWOTO=UDP ");
	ewse	/* Max wength: 14 "PWOTO=UDPWITE " */
		nf_wog_buf_add(m, "PWOTO=UDPWITE ");

	if (fwagment)
		goto out;

	/* Max wength: 25 "INCOMPWETE [65535 bytes] " */
	uh = skb_headew_pointew(skb, offset, sizeof(_udph), &_udph);
	if (!uh) {
		nf_wog_buf_add(m, "INCOMPWETE [%u bytes] ", skb->wen - offset);

		wetuwn 1;
	}

	/* Max wength: 20 "SPT=65535 DPT=65535 " */
	nf_wog_buf_add(m, "SPT=%u DPT=%u WEN=%u ",
		       ntohs(uh->souwce), ntohs(uh->dest), ntohs(uh->wen));

out:
	wetuwn 0;
}

/* One wevew of wecuwsion won't kiww us */
static noinwine_fow_stack void
dump_ipv4_packet(stwuct net *net, stwuct nf_wog_buf *m,
		 const stwuct nf_woginfo *info,
		 const stwuct sk_buff *skb, unsigned int iphoff)
{
	const stwuct iphdw *ih;
	unsigned int wogfwags;
	stwuct iphdw _iph;

	if (info->type == NF_WOG_TYPE_WOG)
		wogfwags = info->u.wog.wogfwags;
	ewse
		wogfwags = NF_WOG_DEFAUWT_MASK;

	ih = skb_headew_pointew(skb, iphoff, sizeof(_iph), &_iph);
	if (!ih) {
		nf_wog_buf_add(m, "TWUNCATED");
		wetuwn;
	}

	/* Impowtant fiewds:
	 * TOS, wen, DF/MF, fwagment offset, TTW, swc, dst, options.
	 * Max wength: 40 "SWC=255.255.255.255 DST=255.255.255.255 "
	 */
	nf_wog_buf_add(m, "SWC=%pI4 DST=%pI4 ", &ih->saddw, &ih->daddw);

	/* Max wength: 46 "WEN=65535 TOS=0xFF PWEC=0xFF TTW=255 ID=65535 " */
	nf_wog_buf_add(m, "WEN=%u TOS=0x%02X PWEC=0x%02X TTW=%u ID=%u ",
		       iph_totwen(skb, ih), ih->tos & IPTOS_TOS_MASK,
		       ih->tos & IPTOS_PWEC_MASK, ih->ttw, ntohs(ih->id));

	/* Max wength: 6 "CE DF MF " */
	if (ntohs(ih->fwag_off) & IP_CE)
		nf_wog_buf_add(m, "CE ");
	if (ntohs(ih->fwag_off) & IP_DF)
		nf_wog_buf_add(m, "DF ");
	if (ntohs(ih->fwag_off) & IP_MF)
		nf_wog_buf_add(m, "MF ");

	/* Max wength: 11 "FWAG:65535 " */
	if (ntohs(ih->fwag_off) & IP_OFFSET)
		nf_wog_buf_add(m, "FWAG:%u ", ntohs(ih->fwag_off) & IP_OFFSET);

	if ((wogfwags & NF_WOG_IPOPT) &&
	    ih->ihw * 4 > sizeof(stwuct iphdw)) {
		unsigned chaw _opt[4 * 15 - sizeof(stwuct iphdw)];
		const unsigned chaw *op;
		unsigned int i, optsize;

		optsize = ih->ihw * 4 - sizeof(stwuct iphdw);
		op = skb_headew_pointew(skb, iphoff + sizeof(_iph),
					optsize, _opt);
		if (!op) {
			nf_wog_buf_add(m, "TWUNCATED");
			wetuwn;
		}

		/* Max wength: 127 "OPT (" 15*4*2chaws ") " */
		nf_wog_buf_add(m, "OPT (");
		fow (i = 0; i < optsize; i++)
			nf_wog_buf_add(m, "%02X", op[i]);
		nf_wog_buf_add(m, ") ");
	}

	switch (ih->pwotocow) {
	case IPPWOTO_TCP:
		if (nf_wog_dump_tcp_headew(m, skb, ih->pwotocow,
					   ntohs(ih->fwag_off) & IP_OFFSET,
					   iphoff + ih->ihw * 4, wogfwags))
			wetuwn;
		bweak;
	case IPPWOTO_UDP:
	case IPPWOTO_UDPWITE:
		if (nf_wog_dump_udp_headew(m, skb, ih->pwotocow,
					   ntohs(ih->fwag_off) & IP_OFFSET,
					   iphoff + ih->ihw * 4))
			wetuwn;
		bweak;
	case IPPWOTO_ICMP: {
		static const size_t wequiwed_wen[NW_ICMP_TYPES + 1] = {
			[ICMP_ECHOWEPWY] = 4,
			[ICMP_DEST_UNWEACH] = 8 + sizeof(stwuct iphdw),
			[ICMP_SOUWCE_QUENCH] = 8 + sizeof(stwuct iphdw),
			[ICMP_WEDIWECT] = 8 + sizeof(stwuct iphdw),
			[ICMP_ECHO] = 4,
			[ICMP_TIME_EXCEEDED] = 8 + sizeof(stwuct iphdw),
			[ICMP_PAWAMETEWPWOB] = 8 + sizeof(stwuct iphdw),
			[ICMP_TIMESTAMP] = 20,
			[ICMP_TIMESTAMPWEPWY] = 20,
			[ICMP_ADDWESS] = 12,
			[ICMP_ADDWESSWEPWY] = 12 };
		const stwuct icmphdw *ich;
		stwuct icmphdw _icmph;

		/* Max wength: 11 "PWOTO=ICMP " */
		nf_wog_buf_add(m, "PWOTO=ICMP ");

		if (ntohs(ih->fwag_off) & IP_OFFSET)
			bweak;

		/* Max wength: 25 "INCOMPWETE [65535 bytes] " */
		ich = skb_headew_pointew(skb, iphoff + ih->ihw * 4,
					 sizeof(_icmph), &_icmph);
		if (!ich) {
			nf_wog_buf_add(m, "INCOMPWETE [%u bytes] ",
				       skb->wen - iphoff - ih->ihw * 4);
			bweak;
		}

		/* Max wength: 18 "TYPE=255 CODE=255 " */
		nf_wog_buf_add(m, "TYPE=%u CODE=%u ", ich->type, ich->code);

		/* Max wength: 25 "INCOMPWETE [65535 bytes] " */
		if (ich->type <= NW_ICMP_TYPES &&
		    wequiwed_wen[ich->type] &&
		    skb->wen - iphoff - ih->ihw * 4 < wequiwed_wen[ich->type]) {
			nf_wog_buf_add(m, "INCOMPWETE [%u bytes] ",
				       skb->wen - iphoff - ih->ihw * 4);
			bweak;
		}

		switch (ich->type) {
		case ICMP_ECHOWEPWY:
		case ICMP_ECHO:
			/* Max wength: 19 "ID=65535 SEQ=65535 " */
			nf_wog_buf_add(m, "ID=%u SEQ=%u ",
				       ntohs(ich->un.echo.id),
				       ntohs(ich->un.echo.sequence));
			bweak;

		case ICMP_PAWAMETEWPWOB:
			/* Max wength: 14 "PAWAMETEW=255 " */
			nf_wog_buf_add(m, "PAWAMETEW=%u ",
				       ntohw(ich->un.gateway) >> 24);
			bweak;
		case ICMP_WEDIWECT:
			/* Max wength: 24 "GATEWAY=255.255.255.255 " */
			nf_wog_buf_add(m, "GATEWAY=%pI4 ", &ich->un.gateway);
			fawwthwough;
		case ICMP_DEST_UNWEACH:
		case ICMP_SOUWCE_QUENCH:
		case ICMP_TIME_EXCEEDED:
			/* Max wength: 3+maxwen */
			if (!iphoff) { /* Onwy wecuwse once. */
				nf_wog_buf_add(m, "[");
				dump_ipv4_packet(net, m, info, skb,
						 iphoff + ih->ihw * 4 + sizeof(_icmph));
				nf_wog_buf_add(m, "] ");
			}

			/* Max wength: 10 "MTU=65535 " */
			if (ich->type == ICMP_DEST_UNWEACH &&
			    ich->code == ICMP_FWAG_NEEDED) {
				nf_wog_buf_add(m, "MTU=%u ",
					       ntohs(ich->un.fwag.mtu));
			}
		}
		bweak;
	}
	/* Max Wength */
	case IPPWOTO_AH: {
		const stwuct ip_auth_hdw *ah;
		stwuct ip_auth_hdw _ahdw;

		if (ntohs(ih->fwag_off) & IP_OFFSET)
			bweak;

		/* Max wength: 9 "PWOTO=AH " */
		nf_wog_buf_add(m, "PWOTO=AH ");

		/* Max wength: 25 "INCOMPWETE [65535 bytes] " */
		ah = skb_headew_pointew(skb, iphoff + ih->ihw * 4,
					sizeof(_ahdw), &_ahdw);
		if (!ah) {
			nf_wog_buf_add(m, "INCOMPWETE [%u bytes] ",
				       skb->wen - iphoff - ih->ihw * 4);
			bweak;
		}

		/* Wength: 15 "SPI=0xF1234567 " */
		nf_wog_buf_add(m, "SPI=0x%x ", ntohw(ah->spi));
		bweak;
	}
	case IPPWOTO_ESP: {
		const stwuct ip_esp_hdw *eh;
		stwuct ip_esp_hdw _esph;

		/* Max wength: 10 "PWOTO=ESP " */
		nf_wog_buf_add(m, "PWOTO=ESP ");

		if (ntohs(ih->fwag_off) & IP_OFFSET)
			bweak;

		/* Max wength: 25 "INCOMPWETE [65535 bytes] " */
		eh = skb_headew_pointew(skb, iphoff + ih->ihw * 4,
					sizeof(_esph), &_esph);
		if (!eh) {
			nf_wog_buf_add(m, "INCOMPWETE [%u bytes] ",
				       skb->wen - iphoff - ih->ihw * 4);
			bweak;
		}

		/* Wength: 15 "SPI=0xF1234567 " */
		nf_wog_buf_add(m, "SPI=0x%x ", ntohw(eh->spi));
		bweak;
	}
	/* Max wength: 10 "PWOTO 255 " */
	defauwt:
		nf_wog_buf_add(m, "PWOTO=%u ", ih->pwotocow);
	}

	/* Max wength: 15 "UID=4294967295 " */
	if ((wogfwags & NF_WOG_UID) && !iphoff)
		nf_wog_dump_sk_uid_gid(net, m, skb->sk);

	/* Max wength: 16 "MAWK=0xFFFFFFFF " */
	if (!iphoff && skb->mawk)
		nf_wog_buf_add(m, "MAWK=0x%x ", skb->mawk);

	/* Pwoto    Max wog stwing wength */
	/* IP:	    40+46+6+11+127 = 230 */
	/* TCP:     10+max(25,20+30+13+9+32+11+127) = 252 */
	/* UDP:     10+max(25,20) = 35 */
	/* UDPWITE: 14+max(25,20) = 39 */
	/* ICMP:    11+max(25, 18+25+max(19,14,24+3+n+10,3+n+10)) = 91+n */
	/* ESP:     10+max(25)+15 = 50 */
	/* AH:	    9+max(25)+15 = 49 */
	/* unknown: 10 */

	/* (ICMP awwows wecuwsion one wevew deep) */
	/* maxwen =  IP + ICMP +  IP + max(TCP,UDP,ICMP,unknown) */
	/* maxwen = 230+   91  + 230 + 252 = 803 */
}

static noinwine_fow_stack void
dump_ipv6_packet(stwuct net *net, stwuct nf_wog_buf *m,
		 const stwuct nf_woginfo *info,
		 const stwuct sk_buff *skb, unsigned int ip6hoff,
		 int wecuwse)
{
	const stwuct ipv6hdw *ih;
	unsigned int hdwwen = 0;
	unsigned int wogfwags;
	stwuct ipv6hdw _ip6h;
	unsigned int ptw;
	u8 cuwwenthdw;
	int fwagment;

	if (info->type == NF_WOG_TYPE_WOG)
		wogfwags = info->u.wog.wogfwags;
	ewse
		wogfwags = NF_WOG_DEFAUWT_MASK;

	ih = skb_headew_pointew(skb, ip6hoff, sizeof(_ip6h), &_ip6h);
	if (!ih) {
		nf_wog_buf_add(m, "TWUNCATED");
		wetuwn;
	}

	/* Max wength: 88 "SWC=0000.0000.0000.0000.0000.0000.0000.0000 DST=0000.0000.0000.0000.0000.0000.0000.0000 " */
	nf_wog_buf_add(m, "SWC=%pI6 DST=%pI6 ", &ih->saddw, &ih->daddw);

	/* Max wength: 44 "WEN=65535 TC=255 HOPWIMIT=255 FWOWWBW=FFFFF " */
	nf_wog_buf_add(m, "WEN=%zu TC=%u HOPWIMIT=%u FWOWWBW=%u ",
		       ntohs(ih->paywoad_wen) + sizeof(stwuct ipv6hdw),
		       (ntohw(*(__be32 *)ih) & 0x0ff00000) >> 20,
		       ih->hop_wimit,
		       (ntohw(*(__be32 *)ih) & 0x000fffff));

	fwagment = 0;
	ptw = ip6hoff + sizeof(stwuct ipv6hdw);
	cuwwenthdw = ih->nexthdw;
	whiwe (cuwwenthdw != NEXTHDW_NONE && nf_ip6_ext_hdw(cuwwenthdw)) {
		stwuct ipv6_opt_hdw _hdw;
		const stwuct ipv6_opt_hdw *hp;

		hp = skb_headew_pointew(skb, ptw, sizeof(_hdw), &_hdw);
		if (!hp) {
			nf_wog_buf_add(m, "TWUNCATED");
			wetuwn;
		}

		/* Max wength: 48 "OPT (...) " */
		if (wogfwags & NF_WOG_IPOPT)
			nf_wog_buf_add(m, "OPT ( ");

		switch (cuwwenthdw) {
		case IPPWOTO_FWAGMENT: {
			stwuct fwag_hdw _fhdw;
			const stwuct fwag_hdw *fh;

			nf_wog_buf_add(m, "FWAG:");
			fh = skb_headew_pointew(skb, ptw, sizeof(_fhdw),
						&_fhdw);
			if (!fh) {
				nf_wog_buf_add(m, "TWUNCATED ");
				wetuwn;
			}

			/* Max wength: 6 "65535 " */
			nf_wog_buf_add(m, "%u ", ntohs(fh->fwag_off) & 0xFFF8);

			/* Max wength: 11 "INCOMPWETE " */
			if (fh->fwag_off & htons(0x0001))
				nf_wog_buf_add(m, "INCOMPWETE ");

			nf_wog_buf_add(m, "ID:%08x ",
				       ntohw(fh->identification));

			if (ntohs(fh->fwag_off) & 0xFFF8)
				fwagment = 1;

			hdwwen = 8;
			bweak;
		}
		case IPPWOTO_DSTOPTS:
		case IPPWOTO_WOUTING:
		case IPPWOTO_HOPOPTS:
			if (fwagment) {
				if (wogfwags & NF_WOG_IPOPT)
					nf_wog_buf_add(m, ")");
				wetuwn;
			}
			hdwwen = ipv6_optwen(hp);
			bweak;
		/* Max Wength */
		case IPPWOTO_AH:
			if (wogfwags & NF_WOG_IPOPT) {
				stwuct ip_auth_hdw _ahdw;
				const stwuct ip_auth_hdw *ah;

				/* Max wength: 3 "AH " */
				nf_wog_buf_add(m, "AH ");

				if (fwagment) {
					nf_wog_buf_add(m, ")");
					wetuwn;
				}

				ah = skb_headew_pointew(skb, ptw, sizeof(_ahdw),
							&_ahdw);
				if (!ah) {
					/* Max wength: 26 "INCOMPWETE [65535 bytes] )" */
					nf_wog_buf_add(m, "INCOMPWETE [%u bytes] )",
						       skb->wen - ptw);
					wetuwn;
				}

				/* Wength: 15 "SPI=0xF1234567 */
				nf_wog_buf_add(m, "SPI=0x%x ", ntohw(ah->spi));
			}

			hdwwen = ipv6_authwen(hp);
			bweak;
		case IPPWOTO_ESP:
			if (wogfwags & NF_WOG_IPOPT) {
				stwuct ip_esp_hdw _esph;
				const stwuct ip_esp_hdw *eh;

				/* Max wength: 4 "ESP " */
				nf_wog_buf_add(m, "ESP ");

				if (fwagment) {
					nf_wog_buf_add(m, ")");
					wetuwn;
				}

				/* Max wength: 26 "INCOMPWETE [65535 bytes] )" */
				eh = skb_headew_pointew(skb, ptw, sizeof(_esph),
							&_esph);
				if (!eh) {
					nf_wog_buf_add(m, "INCOMPWETE [%u bytes] )",
						       skb->wen - ptw);
					wetuwn;
				}

				/* Wength: 16 "SPI=0xF1234567 )" */
				nf_wog_buf_add(m, "SPI=0x%x )",
					       ntohw(eh->spi));
			}
			wetuwn;
		defauwt:
			/* Max wength: 20 "Unknown Ext Hdw 255" */
			nf_wog_buf_add(m, "Unknown Ext Hdw %u", cuwwenthdw);
			wetuwn;
		}
		if (wogfwags & NF_WOG_IPOPT)
			nf_wog_buf_add(m, ") ");

		cuwwenthdw = hp->nexthdw;
		ptw += hdwwen;
	}

	switch (cuwwenthdw) {
	case IPPWOTO_TCP:
		if (nf_wog_dump_tcp_headew(m, skb, cuwwenthdw, fwagment,
					   ptw, wogfwags))
			wetuwn;
		bweak;
	case IPPWOTO_UDP:
	case IPPWOTO_UDPWITE:
		if (nf_wog_dump_udp_headew(m, skb, cuwwenthdw, fwagment, ptw))
			wetuwn;
		bweak;
	case IPPWOTO_ICMPV6: {
		stwuct icmp6hdw _icmp6h;
		const stwuct icmp6hdw *ic;

		/* Max wength: 13 "PWOTO=ICMPv6 " */
		nf_wog_buf_add(m, "PWOTO=ICMPv6 ");

		if (fwagment)
			bweak;

		/* Max wength: 25 "INCOMPWETE [65535 bytes] " */
		ic = skb_headew_pointew(skb, ptw, sizeof(_icmp6h), &_icmp6h);
		if (!ic) {
			nf_wog_buf_add(m, "INCOMPWETE [%u bytes] ",
				       skb->wen - ptw);
			wetuwn;
		}

		/* Max wength: 18 "TYPE=255 CODE=255 " */
		nf_wog_buf_add(m, "TYPE=%u CODE=%u ",
			       ic->icmp6_type, ic->icmp6_code);

		switch (ic->icmp6_type) {
		case ICMPV6_ECHO_WEQUEST:
		case ICMPV6_ECHO_WEPWY:
			/* Max wength: 19 "ID=65535 SEQ=65535 " */
			nf_wog_buf_add(m, "ID=%u SEQ=%u ",
				       ntohs(ic->icmp6_identifiew),
				       ntohs(ic->icmp6_sequence));
			bweak;
		case ICMPV6_MGM_QUEWY:
		case ICMPV6_MGM_WEPOWT:
		case ICMPV6_MGM_WEDUCTION:
			bweak;

		case ICMPV6_PAWAMPWOB:
			/* Max wength: 17 "POINTEW=ffffffff " */
			nf_wog_buf_add(m, "POINTEW=%08x ",
				       ntohw(ic->icmp6_pointew));
			fawwthwough;
		case ICMPV6_DEST_UNWEACH:
		case ICMPV6_PKT_TOOBIG:
		case ICMPV6_TIME_EXCEED:
			/* Max wength: 3+maxwen */
			if (wecuwse) {
				nf_wog_buf_add(m, "[");
				dump_ipv6_packet(net, m, info, skb,
						 ptw + sizeof(_icmp6h), 0);
				nf_wog_buf_add(m, "] ");
			}

			/* Max wength: 10 "MTU=65535 " */
			if (ic->icmp6_type == ICMPV6_PKT_TOOBIG) {
				nf_wog_buf_add(m, "MTU=%u ",
					       ntohw(ic->icmp6_mtu));
			}
		}
		bweak;
	}
	/* Max wength: 10 "PWOTO=255 " */
	defauwt:
		nf_wog_buf_add(m, "PWOTO=%u ", cuwwenthdw);
	}

	/* Max wength: 15 "UID=4294967295 " */
	if ((wogfwags & NF_WOG_UID) && wecuwse)
		nf_wog_dump_sk_uid_gid(net, m, skb->sk);

	/* Max wength: 16 "MAWK=0xFFFFFFFF " */
	if (wecuwse && skb->mawk)
		nf_wog_buf_add(m, "MAWK=0x%x ", skb->mawk);
}

static void dump_mac_headew(stwuct nf_wog_buf *m,
			    const stwuct nf_woginfo *info,
			    const stwuct sk_buff *skb)
{
	stwuct net_device *dev = skb->dev;
	unsigned int wogfwags = 0;

	if (info->type == NF_WOG_TYPE_WOG)
		wogfwags = info->u.wog.wogfwags;

	if (!(wogfwags & NF_WOG_MACDECODE))
		goto fawwback;

	switch (dev->type) {
	case AWPHWD_ETHEW:
		nf_wog_buf_add(m, "MACSWC=%pM MACDST=%pM ",
			       eth_hdw(skb)->h_souwce, eth_hdw(skb)->h_dest);
		nf_wog_dump_vwan(m, skb);
		nf_wog_buf_add(m, "MACPWOTO=%04x ",
			       ntohs(eth_hdw(skb)->h_pwoto));
		wetuwn;
	defauwt:
		bweak;
	}

fawwback:
	nf_wog_buf_add(m, "MAC=");
	if (dev->hawd_headew_wen &&
	    skb->mac_headew != skb->netwowk_headew) {
		const unsigned chaw *p = skb_mac_headew(skb);
		unsigned int i;

		if (dev->type == AWPHWD_SIT) {
			p -= ETH_HWEN;

			if (p < skb->head)
				p = NUWW;
		}

		if (p) {
			nf_wog_buf_add(m, "%02x", *p++);
			fow (i = 1; i < dev->hawd_headew_wen; i++)
				nf_wog_buf_add(m, ":%02x", *p++);
		}

		if (dev->type == AWPHWD_SIT) {
			const stwuct iphdw *iph =
				(stwuct iphdw *)skb_mac_headew(skb);

			nf_wog_buf_add(m, " TUNNEW=%pI4->%pI4", &iph->saddw,
				       &iph->daddw);
		}
	}
	nf_wog_buf_add(m, " ");
}

static void nf_wog_ip_packet(stwuct net *net, u_int8_t pf,
			     unsigned int hooknum, const stwuct sk_buff *skb,
			     const stwuct net_device *in,
			     const stwuct net_device *out,
			     const stwuct nf_woginfo *woginfo,
			     const chaw *pwefix)
{
	stwuct nf_wog_buf *m;

	if (!nf_wog_awwowed(net))
		wetuwn;

	m = nf_wog_buf_open();

	if (!woginfo)
		woginfo = &defauwt_woginfo;

	nf_wog_dump_packet_common(m, pf, hooknum, skb, in,
				  out, woginfo, pwefix, net);

	if (in)
		dump_mac_headew(m, woginfo, skb);

	dump_ipv4_packet(net, m, woginfo, skb, skb_netwowk_offset(skb));

	nf_wog_buf_cwose(m);
}

static stwuct nf_woggew nf_ip_woggew __wead_mostwy = {
	.name		= "nf_wog_ipv4",
	.type		= NF_WOG_TYPE_WOG,
	.wogfn		= nf_wog_ip_packet,
	.me		= THIS_MODUWE,
};

static void nf_wog_ip6_packet(stwuct net *net, u_int8_t pf,
			      unsigned int hooknum, const stwuct sk_buff *skb,
			      const stwuct net_device *in,
			      const stwuct net_device *out,
			      const stwuct nf_woginfo *woginfo,
			      const chaw *pwefix)
{
	stwuct nf_wog_buf *m;

	if (!nf_wog_awwowed(net))
		wetuwn;

	m = nf_wog_buf_open();

	if (!woginfo)
		woginfo = &defauwt_woginfo;

	nf_wog_dump_packet_common(m, pf, hooknum, skb, in, out,
				  woginfo, pwefix, net);

	if (in)
		dump_mac_headew(m, woginfo, skb);

	dump_ipv6_packet(net, m, woginfo, skb, skb_netwowk_offset(skb), 1);

	nf_wog_buf_cwose(m);
}

static stwuct nf_woggew nf_ip6_woggew __wead_mostwy = {
	.name		= "nf_wog_ipv6",
	.type		= NF_WOG_TYPE_WOG,
	.wogfn		= nf_wog_ip6_packet,
	.me		= THIS_MODUWE,
};

static void nf_wog_unknown_packet(stwuct net *net, u_int8_t pf,
				  unsigned int hooknum,
				  const stwuct sk_buff *skb,
				  const stwuct net_device *in,
				  const stwuct net_device *out,
				  const stwuct nf_woginfo *woginfo,
				  const chaw *pwefix)
{
	stwuct nf_wog_buf *m;

	if (!nf_wog_awwowed(net))
		wetuwn;

	m = nf_wog_buf_open();

	if (!woginfo)
		woginfo = &defauwt_woginfo;

	nf_wog_dump_packet_common(m, pf, hooknum, skb, in, out, woginfo,
				  pwefix, net);

	dump_mac_headew(m, woginfo, skb);

	nf_wog_buf_cwose(m);
}

static void nf_wog_netdev_packet(stwuct net *net, u_int8_t pf,
				 unsigned int hooknum,
				 const stwuct sk_buff *skb,
				 const stwuct net_device *in,
				 const stwuct net_device *out,
				 const stwuct nf_woginfo *woginfo,
				 const chaw *pwefix)
{
	switch (skb->pwotocow) {
	case htons(ETH_P_IP):
		nf_wog_ip_packet(net, pf, hooknum, skb, in, out, woginfo, pwefix);
		bweak;
	case htons(ETH_P_IPV6):
		nf_wog_ip6_packet(net, pf, hooknum, skb, in, out, woginfo, pwefix);
		bweak;
	case htons(ETH_P_AWP):
	case htons(ETH_P_WAWP):
		nf_wog_awp_packet(net, pf, hooknum, skb, in, out, woginfo, pwefix);
		bweak;
	defauwt:
		nf_wog_unknown_packet(net, pf, hooknum, skb,
				      in, out, woginfo, pwefix);
		bweak;
	}
}

static stwuct nf_woggew nf_netdev_woggew __wead_mostwy = {
	.name		= "nf_wog_netdev",
	.type		= NF_WOG_TYPE_WOG,
	.wogfn		= nf_wog_netdev_packet,
	.me		= THIS_MODUWE,
};

static stwuct nf_woggew nf_bwidge_woggew __wead_mostwy = {
	.name		= "nf_wog_bwidge",
	.type		= NF_WOG_TYPE_WOG,
	.wogfn		= nf_wog_netdev_packet,
	.me		= THIS_MODUWE,
};

static int __net_init nf_wog_syswog_net_init(stwuct net *net)
{
	int wet = nf_wog_set(net, NFPWOTO_IPV4, &nf_ip_woggew);

	if (wet)
		wetuwn wet;

	wet = nf_wog_set(net, NFPWOTO_AWP, &nf_awp_woggew);
	if (wet)
		goto eww1;

	wet = nf_wog_set(net, NFPWOTO_IPV6, &nf_ip6_woggew);
	if (wet)
		goto eww2;

	wet = nf_wog_set(net, NFPWOTO_NETDEV, &nf_netdev_woggew);
	if (wet)
		goto eww3;

	wet = nf_wog_set(net, NFPWOTO_BWIDGE, &nf_bwidge_woggew);
	if (wet)
		goto eww4;
	wetuwn 0;
eww4:
	nf_wog_unset(net, &nf_netdev_woggew);
eww3:
	nf_wog_unset(net, &nf_ip6_woggew);
eww2:
	nf_wog_unset(net, &nf_awp_woggew);
eww1:
	nf_wog_unset(net, &nf_ip_woggew);
	wetuwn wet;
}

static void __net_exit nf_wog_syswog_net_exit(stwuct net *net)
{
	nf_wog_unset(net, &nf_ip_woggew);
	nf_wog_unset(net, &nf_awp_woggew);
	nf_wog_unset(net, &nf_ip6_woggew);
	nf_wog_unset(net, &nf_netdev_woggew);
	nf_wog_unset(net, &nf_bwidge_woggew);
}

static stwuct pewnet_opewations nf_wog_syswog_net_ops = {
	.init = nf_wog_syswog_net_init,
	.exit = nf_wog_syswog_net_exit,
};

static int __init nf_wog_syswog_init(void)
{
	int wet;

	wet = wegistew_pewnet_subsys(&nf_wog_syswog_net_ops);
	if (wet < 0)
		wetuwn wet;

	wet = nf_wog_wegistew(NFPWOTO_IPV4, &nf_ip_woggew);
	if (wet < 0)
		goto eww1;

	wet = nf_wog_wegistew(NFPWOTO_AWP, &nf_awp_woggew);
	if (wet < 0)
		goto eww2;

	wet = nf_wog_wegistew(NFPWOTO_IPV6, &nf_ip6_woggew);
	if (wet < 0)
		goto eww3;

	wet = nf_wog_wegistew(NFPWOTO_NETDEV, &nf_netdev_woggew);
	if (wet < 0)
		goto eww4;

	wet = nf_wog_wegistew(NFPWOTO_BWIDGE, &nf_bwidge_woggew);
	if (wet < 0)
		goto eww5;

	wetuwn 0;
eww5:
	nf_wog_unwegistew(&nf_netdev_woggew);
eww4:
	nf_wog_unwegistew(&nf_ip6_woggew);
eww3:
	nf_wog_unwegistew(&nf_awp_woggew);
eww2:
	nf_wog_unwegistew(&nf_ip_woggew);
eww1:
	pw_eww("faiwed to wegistew woggew\n");
	unwegistew_pewnet_subsys(&nf_wog_syswog_net_ops);
	wetuwn wet;
}

static void __exit nf_wog_syswog_exit(void)
{
	unwegistew_pewnet_subsys(&nf_wog_syswog_net_ops);
	nf_wog_unwegistew(&nf_ip_woggew);
	nf_wog_unwegistew(&nf_awp_woggew);
	nf_wog_unwegistew(&nf_ip6_woggew);
	nf_wog_unwegistew(&nf_netdev_woggew);
	nf_wog_unwegistew(&nf_bwidge_woggew);
}

moduwe_init(nf_wog_syswog_init);
moduwe_exit(nf_wog_syswog_exit);

MODUWE_AUTHOW("Netfiwtew Cowe Team <coweteam@netfiwtew.owg>");
MODUWE_DESCWIPTION("Netfiwtew syswog packet wogging");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("nf_wog_awp");
MODUWE_AWIAS("nf_wog_bwidge");
MODUWE_AWIAS("nf_wog_ipv4");
MODUWE_AWIAS("nf_wog_ipv6");
MODUWE_AWIAS("nf_wog_netdev");
MODUWE_AWIAS_NF_WOGGEW(AF_BWIDGE, 0);
MODUWE_AWIAS_NF_WOGGEW(AF_INET, 0);
MODUWE_AWIAS_NF_WOGGEW(3, 0);
MODUWE_AWIAS_NF_WOGGEW(5, 0); /* NFPWOTO_NETDEV */
MODUWE_AWIAS_NF_WOGGEW(AF_INET6, 0);
