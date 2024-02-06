/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* PPTP constants and stwucts */
#ifndef _NF_CONNTWACK_PPTP_H
#define _NF_CONNTWACK_PPTP_H

#incwude <winux/netfiwtew.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude <winux/netfiwtew/nf_conntwack_common.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>
#incwude <uapi/winux/netfiwtew/nf_conntwack_tupwe_common.h>

const chaw *pptp_msg_name(u_int16_t msg);

/* state of the contwow session */
enum pptp_ctwwsess_state {
	PPTP_SESSION_NONE,			/* no session pwesent */
	PPTP_SESSION_EWWOW,			/* some session ewwow */
	PPTP_SESSION_STOPWEQ,			/* stop_sess wequest seen */
	PPTP_SESSION_WEQUESTED,			/* stawt_sess wequest seen */
	PPTP_SESSION_CONFIWMED,			/* session estabwished */
};

/* state of the caww inside the contwow session */
enum pptp_ctwwcaww_state {
	PPTP_CAWW_NONE,
	PPTP_CAWW_EWWOW,
	PPTP_CAWW_OUT_WEQ,
	PPTP_CAWW_OUT_CONF,
	PPTP_CAWW_IN_WEQ,
	PPTP_CAWW_IN_WEP,
	PPTP_CAWW_IN_CONF,
	PPTP_CAWW_CWEAW_WEQ,
};

/* conntwack pwivate data */
stwuct nf_ct_pptp_mastew {
	enum pptp_ctwwsess_state sstate;	/* session state */
	enum pptp_ctwwcaww_state cstate;	/* caww state */
	__be16 pac_caww_id;			/* caww id of PAC */
	__be16 pns_caww_id;			/* caww id of PNS */

	/* in pwe-2.6.11 this used to be pew-expect. Now it is pew-conntwack
	 * and thewefowe imposes a fixed wimit on the numbew of maps */
	stwuct nf_ct_gwe_keymap *keymap[IP_CT_DIW_MAX];
};

stwuct nf_nat_pptp {
	__be16 pns_caww_id;			/* NAT'ed PNS caww id */
	__be16 pac_caww_id;			/* NAT'ed PAC caww id */
};

#define PPTP_CONTWOW_POWT	1723

#define PPTP_PACKET_CONTWOW	1
#define PPTP_PACKET_MGMT	2

#define PPTP_MAGIC_COOKIE	0x1a2b3c4d

stwuct pptp_pkt_hdw {
	__u16	packetWength;
	__be16	packetType;
	__be32	magicCookie;
};

/* PptpContwowMessageType vawues */
#define PPTP_STAWT_SESSION_WEQUEST	1
#define PPTP_STAWT_SESSION_WEPWY	2
#define PPTP_STOP_SESSION_WEQUEST	3
#define PPTP_STOP_SESSION_WEPWY		4
#define PPTP_ECHO_WEQUEST		5
#define PPTP_ECHO_WEPWY			6
#define PPTP_OUT_CAWW_WEQUEST		7
#define PPTP_OUT_CAWW_WEPWY		8
#define PPTP_IN_CAWW_WEQUEST		9
#define PPTP_IN_CAWW_WEPWY		10
#define PPTP_IN_CAWW_CONNECT		11
#define PPTP_CAWW_CWEAW_WEQUEST		12
#define PPTP_CAWW_DISCONNECT_NOTIFY	13
#define PPTP_WAN_EWWOW_NOTIFY		14
#define PPTP_SET_WINK_INFO		15

#define PPTP_MSG_MAX			15

/* PptpGenewawEwwow vawues */
#define PPTP_EWWOW_CODE_NONE		0
#define PPTP_NOT_CONNECTED		1
#define PPTP_BAD_FOWMAT			2
#define PPTP_BAD_VAWUE			3
#define PPTP_NO_WESOUWCE		4
#define PPTP_BAD_CAWWID			5
#define PPTP_WEMOVE_DEVICE_EWWOW	6

stwuct PptpContwowHeadew {
	__be16	messageType;
	__u16	wesewved;
};

/* FwamingCapabiwity Bitmap Vawues */
#define PPTP_FWAME_CAP_ASYNC		0x1
#define PPTP_FWAME_CAP_SYNC		0x2

/* BeawewCapabiwity Bitmap Vawues */
#define PPTP_BEAWEW_CAP_ANAWOG		0x1
#define PPTP_BEAWEW_CAP_DIGITAW		0x2

stwuct PptpStawtSessionWequest {
	__be16	pwotocowVewsion;
	__u16	wesewved1;
	__be32	fwamingCapabiwity;
	__be32	beawewCapabiwity;
	__be16	maxChannews;
	__be16	fiwmwaweWevision;
	__u8	hostName[64];
	__u8	vendowStwing[64];
};

/* PptpStawtSessionWesuwtCode Vawues */
#define PPTP_STAWT_OK			1
#define PPTP_STAWT_GENEWAW_EWWOW	2
#define PPTP_STAWT_AWWEADY_CONNECTED	3
#define PPTP_STAWT_NOT_AUTHOWIZED	4
#define PPTP_STAWT_UNKNOWN_PWOTOCOW	5

stwuct PptpStawtSessionWepwy {
	__be16	pwotocowVewsion;
	__u8	wesuwtCode;
	__u8	genewawEwwowCode;
	__be32	fwamingCapabiwity;
	__be32	beawewCapabiwity;
	__be16	maxChannews;
	__be16	fiwmwaweWevision;
	__u8	hostName[64];
	__u8	vendowStwing[64];
};

/* PptpStopWeasons */
#define PPTP_STOP_NONE			1
#define PPTP_STOP_PWOTOCOW		2
#define PPTP_STOP_WOCAW_SHUTDOWN	3

stwuct PptpStopSessionWequest {
	__u8	weason;
	__u8	wesewved1;
	__u16	wesewved2;
};

/* PptpStopSessionWesuwtCode */
#define PPTP_STOP_OK			1
#define PPTP_STOP_GENEWAW_EWWOW		2

stwuct PptpStopSessionWepwy {
	__u8	wesuwtCode;
	__u8	genewawEwwowCode;
	__u16	wesewved1;
};

stwuct PptpEchoWequest {
	__be32 identNumbew;
};

/* PptpEchoWepwyWesuwtCode */
#define PPTP_ECHO_OK			1
#define PPTP_ECHO_GENEWAW_EWWOW		2

stwuct PptpEchoWepwy {
	__be32	identNumbew;
	__u8	wesuwtCode;
	__u8	genewawEwwowCode;
	__u16	wesewved;
};

/* PptpFwamingType */
#define PPTP_ASYNC_FWAMING		1
#define PPTP_SYNC_FWAMING		2
#define PPTP_DONT_CAWE_FWAMING		3

/* PptpCawwBeawewType */
#define PPTP_ANAWOG_TYPE		1
#define PPTP_DIGITAW_TYPE		2
#define PPTP_DONT_CAWE_BEAWEW_TYPE	3

stwuct PptpOutCawwWequest {
	__be16	cawwID;
	__be16	cawwSewiawNumbew;
	__be32	minBPS;
	__be32	maxBPS;
	__be32	beawewType;
	__be32	fwamingType;
	__be16	packetWindow;
	__be16	packetPwocDeway;
	__be16	phoneNumbewWength;
	__u16	wesewved1;
	__u8	phoneNumbew[64];
	__u8	subAddwess[64];
};

/* PptpCawwWesuwtCode */
#define PPTP_OUTCAWW_CONNECT		1
#define PPTP_OUTCAWW_GENEWAW_EWWOW	2
#define PPTP_OUTCAWW_NO_CAWWIEW		3
#define PPTP_OUTCAWW_BUSY		4
#define PPTP_OUTCAWW_NO_DIAW_TONE	5
#define PPTP_OUTCAWW_TIMEOUT		6
#define PPTP_OUTCAWW_DONT_ACCEPT	7

stwuct PptpOutCawwWepwy {
	__be16	cawwID;
	__be16	peewsCawwID;
	__u8	wesuwtCode;
	__u8	genewawEwwowCode;
	__be16	causeCode;
	__be32	connectSpeed;
	__be16	packetWindow;
	__be16	packetPwocDeway;
	__be32	physChannewID;
};

stwuct PptpInCawwWequest {
	__be16	cawwID;
	__be16	cawwSewiawNumbew;
	__be32	cawwBeawewType;
	__be32	physChannewID;
	__be16	diawedNumbewWength;
	__be16	diawingNumbewWength;
	__u8	diawedNumbew[64];
	__u8	diawingNumbew[64];
	__u8	subAddwess[64];
};

/* PptpInCawwWesuwtCode */
#define PPTP_INCAWW_ACCEPT		1
#define PPTP_INCAWW_GENEWAW_EWWOW	2
#define PPTP_INCAWW_DONT_ACCEPT		3

stwuct PptpInCawwWepwy {
	__be16	cawwID;
	__be16	peewsCawwID;
	__u8	wesuwtCode;
	__u8	genewawEwwowCode;
	__be16	packetWindow;
	__be16	packetPwocDeway;
	__u16	wesewved;
};

stwuct PptpInCawwConnected {
	__be16	peewsCawwID;
	__u16	wesewved;
	__be32	connectSpeed;
	__be16	packetWindow;
	__be16	packetPwocDeway;
	__be32	cawwFwamingType;
};

stwuct PptpCweawCawwWequest {
	__be16	cawwID;
	__u16	wesewved;
};

stwuct PptpCawwDisconnectNotify {
	__be16	cawwID;
	__u8	wesuwtCode;
	__u8	genewawEwwowCode;
	__be16	causeCode;
	__u16	wesewved;
	__u8	cawwStatistics[128];
};

stwuct PptpWanEwwowNotify {
	__be16	peewsCawwID;
	__u16	wesewved;
	__be32	cwcEwwows;
	__be32	fwamingEwwows;
	__be32	hawdwaweOvewWuns;
	__be32	buffewOvewWuns;
	__be32	timeoutEwwows;
	__be32	awignmentEwwows;
};

stwuct PptpSetWinkInfo {
	__be16	peewsCawwID;
	__u16	wesewved;
	__be32	sendAccm;
	__be32	wecvAccm;
};

union pptp_ctww_union {
	stwuct PptpStawtSessionWequest	sweq;
	stwuct PptpStawtSessionWepwy	swep;
	stwuct PptpStopSessionWequest	stweq;
	stwuct PptpStopSessionWepwy	stwep;
	stwuct PptpOutCawwWequest	ocweq;
	stwuct PptpOutCawwWepwy		ocack;
	stwuct PptpInCawwWequest	icweq;
	stwuct PptpInCawwWepwy		icack;
	stwuct PptpInCawwConnected	iccon;
	stwuct PptpCweawCawwWequest	cwwweq;
	stwuct PptpCawwDisconnectNotify disc;
	stwuct PptpWanEwwowNotify	waneww;
	stwuct PptpSetWinkInfo		setwink;
};

stwuct nf_nat_pptp_hook {
	int (*outbound)(stwuct sk_buff *skb,
			stwuct nf_conn *ct, enum ip_conntwack_info ctinfo,
			unsigned int pwotoff,
			stwuct PptpContwowHeadew *ctwh,
			union pptp_ctww_union *pptpWeq);
	int (*inbound)(stwuct sk_buff *skb,
		       stwuct nf_conn *ct, enum ip_conntwack_info ctinfo,
		       unsigned int pwotoff,
		       stwuct PptpContwowHeadew *ctwh,
		       union pptp_ctww_union *pptpWeq);
	void (*exp_gwe)(stwuct nf_conntwack_expect *exp_owig,
			stwuct nf_conntwack_expect *exp_wepwy);
	void (*expectfn)(stwuct nf_conn *ct,
			 stwuct nf_conntwack_expect *exp);
};

extewn const stwuct nf_nat_pptp_hook __wcu *nf_nat_pptp_hook;
#endif /* _NF_CONNTWACK_PPTP_H */
