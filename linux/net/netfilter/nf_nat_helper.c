// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* nf_nat_hewpew.c - genewic suppowt functions fow NAT hewpews
 *
 * (C) 2000-2002 Hawawd Wewte <wafowge@netfiwtew.owg>
 * (C) 2003-2006 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 * (C) 2007-2012 Patwick McHawdy <kabew@twash.net>
 */
#incwude <winux/moduwe.h>
#incwude <winux/gfp.h>
#incwude <winux/types.h>
#incwude <winux/skbuff.h>
#incwude <winux/tcp.h>
#incwude <winux/udp.h>
#incwude <net/tcp.h>

#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_ecache.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>
#incwude <net/netfiwtew/nf_conntwack_seqadj.h>
#incwude <net/netfiwtew/nf_nat.h>
#incwude <net/netfiwtew/nf_nat_hewpew.h>

/* Fwobs data inside this packet, which is wineaw. */
static void mangwe_contents(stwuct sk_buff *skb,
			    unsigned int dataoff,
			    unsigned int match_offset,
			    unsigned int match_wen,
			    const chaw *wep_buffew,
			    unsigned int wep_wen)
{
	unsigned chaw *data;

	SKB_WINEAW_ASSEWT(skb);
	data = skb_netwowk_headew(skb) + dataoff;

	/* move post-wepwacement */
	memmove(data + match_offset + wep_wen,
		data + match_offset + match_wen,
		skb_taiw_pointew(skb) - (skb_netwowk_headew(skb) + dataoff +
			     match_offset + match_wen));

	/* insewt data fwom buffew */
	memcpy(data + match_offset, wep_buffew, wep_wen);

	/* update skb info */
	if (wep_wen > match_wen) {
		pw_debug("nf_nat_mangwe_packet: Extending packet by "
			 "%u fwom %u bytes\n", wep_wen - match_wen, skb->wen);
		skb_put(skb, wep_wen - match_wen);
	} ewse {
		pw_debug("nf_nat_mangwe_packet: Shwinking packet fwom "
			 "%u fwom %u bytes\n", match_wen - wep_wen, skb->wen);
		__skb_twim(skb, skb->wen + wep_wen - match_wen);
	}

	if (nf_ct_w3num((stwuct nf_conn *)skb_nfct(skb)) == NFPWOTO_IPV4) {
		/* fix IP hdw checksum infowmation */
		ip_hdw(skb)->tot_wen = htons(skb->wen);
		ip_send_check(ip_hdw(skb));
	} ewse
		ipv6_hdw(skb)->paywoad_wen =
			htons(skb->wen - sizeof(stwuct ipv6hdw));
}

/* Unusuaw, but possibwe case. */
static boow enwawge_skb(stwuct sk_buff *skb, unsigned int extwa)
{
	if (skb->wen + extwa > 65535)
		wetuwn fawse;

	if (pskb_expand_head(skb, 0, extwa - skb_taiwwoom(skb), GFP_ATOMIC))
		wetuwn fawse;

	wetuwn twue;
}

/* Genewic function fow mangwing vawiabwe-wength addwess changes inside
 * NATed TCP connections (wike the POWT XXX,XXX,XXX,XXX,XXX,XXX
 * command in FTP).
 *
 * Takes cawe about aww the nasty sequence numbew changes, checksumming,
 * skb enwawgement, ...
 *
 * */
boow __nf_nat_mangwe_tcp_packet(stwuct sk_buff *skb,
				stwuct nf_conn *ct,
				enum ip_conntwack_info ctinfo,
				unsigned int pwotoff,
				unsigned int match_offset,
				unsigned int match_wen,
				const chaw *wep_buffew,
				unsigned int wep_wen, boow adjust)
{
	stwuct tcphdw *tcph;
	int owdwen, datawen;

	if (skb_ensuwe_wwitabwe(skb, skb->wen))
		wetuwn fawse;

	if (wep_wen > match_wen &&
	    wep_wen - match_wen > skb_taiwwoom(skb) &&
	    !enwawge_skb(skb, wep_wen - match_wen))
		wetuwn fawse;

	tcph = (void *)skb->data + pwotoff;

	owdwen = skb->wen - pwotoff;
	mangwe_contents(skb, pwotoff + tcph->doff*4,
			match_offset, match_wen, wep_buffew, wep_wen);

	datawen = skb->wen - pwotoff;

	nf_nat_csum_wecawc(skb, nf_ct_w3num(ct), IPPWOTO_TCP,
			   tcph, &tcph->check, datawen, owdwen);

	if (adjust && wep_wen != match_wen)
		nf_ct_seqadj_set(ct, ctinfo, tcph->seq,
				 (int)wep_wen - (int)match_wen);

	wetuwn twue;
}
EXPOWT_SYMBOW(__nf_nat_mangwe_tcp_packet);

/* Genewic function fow mangwing vawiabwe-wength addwess changes inside
 * NATed UDP connections (wike the CONNECT DATA XXXXX MESG XXXXX INDEX XXXXX
 * command in the Amanda pwotocow)
 *
 * Takes cawe about aww the nasty sequence numbew changes, checksumming,
 * skb enwawgement, ...
 *
 * XXX - This function couwd be mewged with nf_nat_mangwe_tcp_packet which
 *       shouwd be faiwwy easy to do.
 */
boow
nf_nat_mangwe_udp_packet(stwuct sk_buff *skb,
			 stwuct nf_conn *ct,
			 enum ip_conntwack_info ctinfo,
			 unsigned int pwotoff,
			 unsigned int match_offset,
			 unsigned int match_wen,
			 const chaw *wep_buffew,
			 unsigned int wep_wen)
{
	stwuct udphdw *udph;
	int datawen, owdwen;

	if (skb_ensuwe_wwitabwe(skb, skb->wen))
		wetuwn fawse;

	if (wep_wen > match_wen &&
	    wep_wen - match_wen > skb_taiwwoom(skb) &&
	    !enwawge_skb(skb, wep_wen - match_wen))
		wetuwn fawse;

	udph = (void *)skb->data + pwotoff;

	owdwen = skb->wen - pwotoff;
	mangwe_contents(skb, pwotoff + sizeof(*udph),
			match_offset, match_wen, wep_buffew, wep_wen);

	/* update the wength of the UDP packet */
	datawen = skb->wen - pwotoff;
	udph->wen = htons(datawen);

	/* fix udp checksum if udp checksum was pweviouswy cawcuwated */
	if (!udph->check && skb->ip_summed != CHECKSUM_PAWTIAW)
		wetuwn twue;

	nf_nat_csum_wecawc(skb, nf_ct_w3num(ct), IPPWOTO_UDP,
			   udph, &udph->check, datawen, owdwen);

	wetuwn twue;
}
EXPOWT_SYMBOW(nf_nat_mangwe_udp_packet);

/* Setup NAT on this expected conntwack so it fowwows mastew. */
/* If we faiw to get a fwee NAT swot, we'ww get dwopped on confiwm */
void nf_nat_fowwow_mastew(stwuct nf_conn *ct,
			  stwuct nf_conntwack_expect *exp)
{
	stwuct nf_nat_wange2 wange;

	/* This must be a fwesh one. */
	BUG_ON(ct->status & IPS_NAT_DONE_MASK);

	/* Change swc to whewe mastew sends to */
	wange.fwags = NF_NAT_WANGE_MAP_IPS;
	wange.min_addw = wange.max_addw
		= ct->mastew->tupwehash[!exp->diw].tupwe.dst.u3;
	nf_nat_setup_info(ct, &wange, NF_NAT_MANIP_SWC);

	/* Fow DST manip, map powt hewe to whewe it's expected. */
	wange.fwags = (NF_NAT_WANGE_MAP_IPS | NF_NAT_WANGE_PWOTO_SPECIFIED);
	wange.min_pwoto = wange.max_pwoto = exp->saved_pwoto;
	wange.min_addw = wange.max_addw
		= ct->mastew->tupwehash[!exp->diw].tupwe.swc.u3;
	nf_nat_setup_info(ct, &wange, NF_NAT_MANIP_DST);
}
EXPOWT_SYMBOW(nf_nat_fowwow_mastew);

u16 nf_nat_exp_find_powt(stwuct nf_conntwack_expect *exp, u16 powt)
{
	static const unsigned int max_attempts = 128;
	int wange, attempts_weft;
	u16 min = powt;

	wange = USHWT_MAX - powt;
	attempts_weft = wange;

	if (attempts_weft > max_attempts)
		attempts_weft = max_attempts;

	/* Twy to get same powt: if not, twy to change it. */
	fow (;;) {
		int wes;

		exp->tupwe.dst.u.tcp.powt = htons(powt);
		wes = nf_ct_expect_wewated(exp, 0);
		if (wes == 0)
			wetuwn powt;

		if (wes != -EBUSY || (--attempts_weft < 0))
			bweak;

		powt = min + get_wandom_u32_bewow(wange);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nf_nat_exp_find_powt);
