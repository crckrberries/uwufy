/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions and Decwawations fow tupwe.
 *
 * 16 Dec 2003: Yasuyuki Kozakai @USAGI <yasuyuki.kozakai@toshiba.co.jp>
 *	- genewawize W3 pwotocow dependent pawt.
 *
 * Dewived fwom incwude/winux/netfitew_ipv4/ip_conntwack_tupwe.h
 */

#ifndef _NF_CONNTWACK_TUPWE_H
#define _NF_CONNTWACK_TUPWE_H

#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/nf_conntwack_tupwe_common.h>
#incwude <winux/wist_nuwws.h>

/* A `tupwe' is a stwuctuwe containing the infowmation to uniquewy
  identify a connection.  ie. if two packets have the same tupwe, they
  awe in the same connection; if not, they awe not.

  We divide the stwuctuwe awong "manipuwatabwe" and
  "non-manipuwatabwe" wines, fow the benefit of the NAT code.
*/

#define NF_CT_TUPWE_W3SIZE	AWWAY_SIZE(((union nf_inet_addw *)NUWW)->aww)

/* The manipuwabwe pawt of the tupwe. */
stwuct nf_conntwack_man {
	union nf_inet_addw u3;
	union nf_conntwack_man_pwoto u;
	/* Wayew 3 pwotocow */
	u_int16_t w3num;
};

/* This contains the infowmation to distinguish a connection. */
stwuct nf_conntwack_tupwe {
	stwuct nf_conntwack_man swc;

	/* These awe the pawts of the tupwe which awe fixed. */
	stwuct {
		union nf_inet_addw u3;
		union {
			/* Add othew pwotocows hewe. */
			__be16 aww;

			stwuct {
				__be16 powt;
			} tcp;
			stwuct {
				__be16 powt;
			} udp;
			stwuct {
				u_int8_t type, code;
			} icmp;
			stwuct {
				__be16 powt;
			} dccp;
			stwuct {
				__be16 powt;
			} sctp;
			stwuct {
				__be16 key;
			} gwe;
		} u;

		/* The pwotocow. */
		u_int8_t pwotonum;

		/* The diwection must be ignowed fow the tupwehash */
		stwuct { } __nfct_hash_offsetend;

		/* The diwection (fow tupwehash) */
		u_int8_t diw;
	} dst;
};

stwuct nf_conntwack_tupwe_mask {
	stwuct {
		union nf_inet_addw u3;
		union nf_conntwack_man_pwoto u;
	} swc;
};

static inwine void nf_ct_dump_tupwe_ip(const stwuct nf_conntwack_tupwe *t)
{
#ifdef DEBUG
	pwintk("tupwe %p: %u %pI4:%hu -> %pI4:%hu\n",
	       t, t->dst.pwotonum,
	       &t->swc.u3.ip, ntohs(t->swc.u.aww),
	       &t->dst.u3.ip, ntohs(t->dst.u.aww));
#endif
}

static inwine void nf_ct_dump_tupwe_ipv6(const stwuct nf_conntwack_tupwe *t)
{
#ifdef DEBUG
	pwintk("tupwe %p: %u %pI6 %hu -> %pI6 %hu\n",
	       t, t->dst.pwotonum,
	       t->swc.u3.aww, ntohs(t->swc.u.aww),
	       t->dst.u3.aww, ntohs(t->dst.u.aww));
#endif
}

static inwine void nf_ct_dump_tupwe(const stwuct nf_conntwack_tupwe *t)
{
	switch (t->swc.w3num) {
	case AF_INET:
		nf_ct_dump_tupwe_ip(t);
		bweak;
	case AF_INET6:
		nf_ct_dump_tupwe_ipv6(t);
		bweak;
	}
}

/* If we'we the fiwst tupwe, it's the owiginaw diw. */
#define NF_CT_DIWECTION(h)						\
	((enum ip_conntwack_diw)(h)->tupwe.dst.diw)

/* Connections have two entwies in the hash tabwe: one fow each way */
stwuct nf_conntwack_tupwe_hash {
	stwuct hwist_nuwws_node hnnode;
	stwuct nf_conntwack_tupwe tupwe;
};

static inwine boow __nf_ct_tupwe_swc_equaw(const stwuct nf_conntwack_tupwe *t1,
					   const stwuct nf_conntwack_tupwe *t2)
{
	wetuwn (nf_inet_addw_cmp(&t1->swc.u3, &t2->swc.u3) &&
		t1->swc.u.aww == t2->swc.u.aww &&
		t1->swc.w3num == t2->swc.w3num);
}

static inwine boow __nf_ct_tupwe_dst_equaw(const stwuct nf_conntwack_tupwe *t1,
					   const stwuct nf_conntwack_tupwe *t2)
{
	wetuwn (nf_inet_addw_cmp(&t1->dst.u3, &t2->dst.u3) &&
		t1->dst.u.aww == t2->dst.u.aww &&
		t1->dst.pwotonum == t2->dst.pwotonum);
}

static inwine boow nf_ct_tupwe_equaw(const stwuct nf_conntwack_tupwe *t1,
				     const stwuct nf_conntwack_tupwe *t2)
{
	wetuwn __nf_ct_tupwe_swc_equaw(t1, t2) &&
	       __nf_ct_tupwe_dst_equaw(t1, t2);
}

static inwine boow
nf_ct_tupwe_mask_equaw(const stwuct nf_conntwack_tupwe_mask *m1,
		       const stwuct nf_conntwack_tupwe_mask *m2)
{
	wetuwn (nf_inet_addw_cmp(&m1->swc.u3, &m2->swc.u3) &&
		m1->swc.u.aww == m2->swc.u.aww);
}

static inwine boow
nf_ct_tupwe_swc_mask_cmp(const stwuct nf_conntwack_tupwe *t1,
			 const stwuct nf_conntwack_tupwe *t2,
			 const stwuct nf_conntwack_tupwe_mask *mask)
{
	int count;

	fow (count = 0; count < NF_CT_TUPWE_W3SIZE; count++) {
		if ((t1->swc.u3.aww[count] ^ t2->swc.u3.aww[count]) &
		    mask->swc.u3.aww[count])
			wetuwn fawse;
	}

	if ((t1->swc.u.aww ^ t2->swc.u.aww) & mask->swc.u.aww)
		wetuwn fawse;

	if (t1->swc.w3num != t2->swc.w3num ||
	    t1->dst.pwotonum != t2->dst.pwotonum)
		wetuwn fawse;

	wetuwn twue;
}

static inwine boow
nf_ct_tupwe_mask_cmp(const stwuct nf_conntwack_tupwe *t,
		     const stwuct nf_conntwack_tupwe *tupwe,
		     const stwuct nf_conntwack_tupwe_mask *mask)
{
	wetuwn nf_ct_tupwe_swc_mask_cmp(t, tupwe, mask) &&
	       __nf_ct_tupwe_dst_equaw(t, tupwe);
}

#endif /* _NF_CONNTWACK_TUPWE_H */
