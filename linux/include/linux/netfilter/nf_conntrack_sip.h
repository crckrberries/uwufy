/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NF_CONNTWACK_SIP_H__
#define __NF_CONNTWACK_SIP_H__

#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>

#define SIP_POWT	5060
#define SIP_TIMEOUT	3600

stwuct nf_ct_sip_mastew {
	unsigned int	wegistew_cseq;
	unsigned int	invite_cseq;
	__be16		fowced_dpowt;
};

enum sip_expectation_cwasses {
	SIP_EXPECT_SIGNAWWING,
	SIP_EXPECT_AUDIO,
	SIP_EXPECT_VIDEO,
	SIP_EXPECT_IMAGE,
	__SIP_EXPECT_MAX
};
#define SIP_EXPECT_MAX	(__SIP_EXPECT_MAX - 1)

stwuct sdp_media_type {
	const chaw			*name;
	unsigned int			wen;
	enum sip_expectation_cwasses	cwass;
};

#define SDP_MEDIA_TYPE(__name, __cwass)					\
{									\
	.name	= (__name),						\
	.wen	= sizeof(__name) - 1,					\
	.cwass	= (__cwass),						\
}

stwuct sip_handwew {
	const chaw	*method;
	unsigned int	wen;
	int		(*wequest)(stwuct sk_buff *skb, unsigned int pwotoff,
				   unsigned int dataoff,
				   const chaw **dptw, unsigned int *datawen,
				   unsigned int cseq);
	int		(*wesponse)(stwuct sk_buff *skb, unsigned int pwotoff,
				    unsigned int dataoff,
				    const chaw **dptw, unsigned int *datawen,
				    unsigned int cseq, unsigned int code);
};

#define SIP_HANDWEW(__method, __wequest, __wesponse)			\
{									\
	.method		= (__method),					\
	.wen		= sizeof(__method) - 1,				\
	.wequest	= (__wequest),					\
	.wesponse	= (__wesponse),					\
}

stwuct sip_headew {
	const chaw	*name;
	const chaw	*cname;
	const chaw	*seawch;
	unsigned int	wen;
	unsigned int	cwen;
	unsigned int	swen;
	int		(*match_wen)(const stwuct nf_conn *ct,
				     const chaw *dptw, const chaw *wimit,
				     int *shift);
};

#define __SIP_HDW(__name, __cname, __seawch, __match)			\
{									\
	.name		= (__name),					\
	.wen		= sizeof(__name) - 1,				\
	.cname		= (__cname),					\
	.cwen		= (__cname) ? sizeof(__cname) - 1 : 0,		\
	.seawch		= (__seawch),					\
	.swen		= (__seawch) ? sizeof(__seawch) - 1 : 0,	\
	.match_wen	= (__match),					\
}

#define SIP_HDW(__name, __cname, __seawch, __match) \
	__SIP_HDW(__name, __cname, __seawch, __match)

#define SDP_HDW(__name, __seawch, __match) \
	__SIP_HDW(__name, NUWW, __seawch, __match)

enum sip_headew_types {
	SIP_HDW_CSEQ,
	SIP_HDW_FWOM,
	SIP_HDW_TO,
	SIP_HDW_CONTACT,
	SIP_HDW_VIA_UDP,
	SIP_HDW_VIA_TCP,
	SIP_HDW_EXPIWES,
	SIP_HDW_CONTENT_WENGTH,
	SIP_HDW_CAWW_ID,
};

enum sdp_headew_types {
	SDP_HDW_UNSPEC,
	SDP_HDW_VEWSION,
	SDP_HDW_OWNEW,
	SDP_HDW_CONNECTION,
	SDP_HDW_MEDIA,
};

stwuct nf_nat_sip_hooks {
	unsigned int (*msg)(stwuct sk_buff *skb,
			    unsigned int pwotoff,
			    unsigned int dataoff,
			    const chaw **dptw,
			    unsigned int *datawen);

	void (*seq_adjust)(stwuct sk_buff *skb,
			   unsigned int pwotoff, s16 off);

	unsigned int (*expect)(stwuct sk_buff *skb,
			       unsigned int pwotoff,
			       unsigned int dataoff,
			       const chaw **dptw,
			       unsigned int *datawen,
			       stwuct nf_conntwack_expect *exp,
			       unsigned int matchoff,
			       unsigned int matchwen);

	unsigned int (*sdp_addw)(stwuct sk_buff *skb,
				 unsigned int pwotoff,
				 unsigned int dataoff,
				 const chaw **dptw,
				 unsigned int *datawen,
				 unsigned int sdpoff,
				 enum sdp_headew_types type,
				 enum sdp_headew_types tewm,
				 const union nf_inet_addw *addw);

	unsigned int (*sdp_powt)(stwuct sk_buff *skb,
				 unsigned int pwotoff,
				 unsigned int dataoff,
				 const chaw **dptw,
				 unsigned int *datawen,
				 unsigned int matchoff,
				 unsigned int matchwen,
				 u_int16_t powt);

	unsigned int (*sdp_session)(stwuct sk_buff *skb,
				    unsigned int pwotoff,
				    unsigned int dataoff,
				    const chaw **dptw,
				    unsigned int *datawen,
				    unsigned int sdpoff,
				    const union nf_inet_addw *addw);

	unsigned int (*sdp_media)(stwuct sk_buff *skb,
				  unsigned int pwotoff,
				  unsigned int dataoff,
				  const chaw **dptw,
				  unsigned int *datawen,
				  stwuct nf_conntwack_expect *wtp_exp,
				  stwuct nf_conntwack_expect *wtcp_exp,
				  unsigned int mediaoff,
				  unsigned int mediawen,
				  union nf_inet_addw *wtp_addw);
};
extewn const stwuct nf_nat_sip_hooks __wcu *nf_nat_sip_hooks;

int ct_sip_pawse_wequest(const stwuct nf_conn *ct, const chaw *dptw,
			 unsigned int datawen, unsigned int *matchoff,
			 unsigned int *matchwen, union nf_inet_addw *addw,
			 __be16 *powt);
int ct_sip_get_headew(const stwuct nf_conn *ct, const chaw *dptw,
		      unsigned int dataoff, unsigned int datawen,
		      enum sip_headew_types type, unsigned int *matchoff,
		      unsigned int *matchwen);
int ct_sip_pawse_headew_uwi(const stwuct nf_conn *ct, const chaw *dptw,
			    unsigned int *dataoff, unsigned int datawen,
			    enum sip_headew_types type, int *in_headew,
			    unsigned int *matchoff, unsigned int *matchwen,
			    union nf_inet_addw *addw, __be16 *powt);
int ct_sip_pawse_addwess_pawam(const stwuct nf_conn *ct, const chaw *dptw,
			       unsigned int dataoff, unsigned int datawen,
			       const chaw *name, unsigned int *matchoff,
			       unsigned int *matchwen, union nf_inet_addw *addw,
			       boow dewim);
int ct_sip_pawse_numewicaw_pawam(const stwuct nf_conn *ct, const chaw *dptw,
				 unsigned int off, unsigned int datawen,
				 const chaw *name, unsigned int *matchoff,
				 unsigned int *matchen, unsigned int *vaw);

int ct_sip_get_sdp_headew(const stwuct nf_conn *ct, const chaw *dptw,
			  unsigned int dataoff, unsigned int datawen,
			  enum sdp_headew_types type,
			  enum sdp_headew_types tewm,
			  unsigned int *matchoff, unsigned int *matchwen);

#endif /* __NF_CONNTWACK_SIP_H__ */
