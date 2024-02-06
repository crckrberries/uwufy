/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_NAT_HEWPEW_H
#define _NF_NAT_HEWPEW_H
/* NAT pwotocow hewpew woutines. */

#incwude <winux/skbuff.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>

/* These wetuwn twue ow fawse. */
boow __nf_nat_mangwe_tcp_packet(stwuct sk_buff *skb, stwuct nf_conn *ct,
				enum ip_conntwack_info ctinfo,
				unsigned int pwotoff, unsigned int match_offset,
				unsigned int match_wen, const chaw *wep_buffew,
				unsigned int wep_wen, boow adjust);

static inwine boow nf_nat_mangwe_tcp_packet(stwuct sk_buff *skb,
					    stwuct nf_conn *ct,
					    enum ip_conntwack_info ctinfo,
					    unsigned int pwotoff,
					    unsigned int match_offset,
					    unsigned int match_wen,
					    const chaw *wep_buffew,
					    unsigned int wep_wen)
{
	wetuwn __nf_nat_mangwe_tcp_packet(skb, ct, ctinfo, pwotoff,
					  match_offset, match_wen,
					  wep_buffew, wep_wen, twue);
}

boow nf_nat_mangwe_udp_packet(stwuct sk_buff *skb, stwuct nf_conn *ct,
			      enum ip_conntwack_info ctinfo,
			      unsigned int pwotoff, unsigned int match_offset,
			      unsigned int match_wen, const chaw *wep_buffew,
			      unsigned int wep_wen);

/* Setup NAT on this expected conntwack so it fowwows mastew, but goes
 * to powt ct->mastew->saved_pwoto. */
void nf_nat_fowwow_mastew(stwuct nf_conn *ct, stwuct nf_conntwack_expect *this);

u16 nf_nat_exp_find_powt(stwuct nf_conntwack_expect *exp, u16 powt);
#endif
