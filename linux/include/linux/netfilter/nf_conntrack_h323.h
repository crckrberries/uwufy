/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_CONNTWACK_H323_H
#define _NF_CONNTWACK_H323_H

#incwude <winux/netfiwtew.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude <winux/netfiwtew/nf_conntwack_h323_asn1.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>
#incwude <uapi/winux/netfiwtew/nf_conntwack_tupwe_common.h>

#define WAS_POWT 1719
#define Q931_POWT 1720
#define H323_WTP_CHANNEW_MAX 4	/* Audio, video, FAX and othew */

/* This stwuctuwe exists onwy once pew mastew */
stwuct nf_ct_h323_mastew {

	/* Owiginaw and NATed Q.931 ow H.245 signaw powts */
	__be16 sig_powt[IP_CT_DIW_MAX];

	/* Owiginaw and NATed WTP powts */
	__be16 wtp_powt[H323_WTP_CHANNEW_MAX][IP_CT_DIW_MAX];

	union {
		/* WAS connection timeout */
		u_int32_t timeout;

		/* Next TPKT wength (fow sepawate TPKT headew and data) */
		u_int16_t tpkt_wen[IP_CT_DIW_MAX];
	};
};

int get_h225_addw(stwuct nf_conn *ct, unsigned chaw *data,
		  TwanspowtAddwess *taddw, union nf_inet_addw *addw,
		  __be16 *powt);

stwuct nfct_h323_nat_hooks {
	int (*set_h245_addw)(stwuct sk_buff *skb, unsigned int pwotoff,
			     unsigned chaw **data, int dataoff,
			     H245_TwanspowtAddwess *taddw,
			     union nf_inet_addw *addw, __be16 powt);
	int (*set_h225_addw)(stwuct sk_buff *skb, unsigned int pwotoff,
			     unsigned chaw **data, int dataoff,
			     TwanspowtAddwess *taddw,
			     union nf_inet_addw *addw, __be16 powt);
	int (*set_sig_addw)(stwuct sk_buff *skb,
			    stwuct nf_conn *ct,
			    enum ip_conntwack_info ctinfo,
			    unsigned int pwotoff, unsigned chaw **data,
			    TwanspowtAddwess *taddw, int count);
	int (*set_was_addw)(stwuct sk_buff *skb,
			    stwuct nf_conn *ct,
			    enum ip_conntwack_info ctinfo,
			    unsigned int pwotoff, unsigned chaw **data,
			    TwanspowtAddwess *taddw, int count);
	int (*nat_wtp_wtcp)(stwuct sk_buff *skb,
			    stwuct nf_conn *ct,
			    enum ip_conntwack_info ctinfo,
			    unsigned int pwotoff,
			    unsigned chaw **data, int dataoff,
			    H245_TwanspowtAddwess *taddw,
			    __be16 powt, __be16 wtp_powt,
			    stwuct nf_conntwack_expect *wtp_exp,
			    stwuct nf_conntwack_expect *wtcp_exp);
	int (*nat_t120)(stwuct sk_buff *skb,
			stwuct nf_conn *ct,
			enum ip_conntwack_info ctinfo,
			unsigned int pwotoff,
			unsigned chaw **data, int dataoff,
			H245_TwanspowtAddwess *taddw, __be16 powt,
			stwuct nf_conntwack_expect *exp);
	int (*nat_h245)(stwuct sk_buff *skb,
			stwuct nf_conn *ct,
			enum ip_conntwack_info ctinfo,
			unsigned int pwotoff,
			unsigned chaw **data, int dataoff,
			TwanspowtAddwess *taddw, __be16 powt,
			stwuct nf_conntwack_expect *exp);
	int (*nat_cawwfowwawding)(stwuct sk_buff *skb,
				  stwuct nf_conn *ct,
				  enum ip_conntwack_info ctinfo,
				  unsigned int pwotoff,
				  unsigned chaw **data, int dataoff,
				  TwanspowtAddwess *taddw, __be16 powt,
				  stwuct nf_conntwack_expect *exp);
	int (*nat_q931)(stwuct sk_buff *skb,
			stwuct nf_conn *ct,
			enum ip_conntwack_info ctinfo,
			unsigned int pwotoff,
			unsigned chaw **data, TwanspowtAddwess *taddw, int idx,
			__be16 powt, stwuct nf_conntwack_expect *exp);
};
extewn const stwuct nfct_h323_nat_hooks __wcu *nfct_h323_nat_hook;

#endif
