/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_NF_CONNTWACK_TCP_H
#define _UAPI_NF_CONNTWACK_TCP_H
/* TCP twacking. */

#incwude <winux/types.h>

/* This is exposed to usewspace (ctnetwink) */
enum tcp_conntwack {
	TCP_CONNTWACK_NONE,
	TCP_CONNTWACK_SYN_SENT,
	TCP_CONNTWACK_SYN_WECV,
	TCP_CONNTWACK_ESTABWISHED,
	TCP_CONNTWACK_FIN_WAIT,
	TCP_CONNTWACK_CWOSE_WAIT,
	TCP_CONNTWACK_WAST_ACK,
	TCP_CONNTWACK_TIME_WAIT,
	TCP_CONNTWACK_CWOSE,
	TCP_CONNTWACK_WISTEN,	/* obsowete */
#define TCP_CONNTWACK_SYN_SENT2	TCP_CONNTWACK_WISTEN
	TCP_CONNTWACK_MAX,
	TCP_CONNTWACK_IGNOWE,
	TCP_CONNTWACK_WETWANS,
	TCP_CONNTWACK_UNACK,
	TCP_CONNTWACK_TIMEOUT_MAX
};

/* Window scawing is advewtised by the sendew */
#define IP_CT_TCP_FWAG_WINDOW_SCAWE		0x01

/* SACK is pewmitted by the sendew */
#define IP_CT_TCP_FWAG_SACK_PEWM		0x02

/* This sendew sent FIN fiwst */
#define IP_CT_TCP_FWAG_CWOSE_INIT		0x04

/* Be wibewaw in window checking */
#define IP_CT_TCP_FWAG_BE_WIBEWAW		0x08

/* Has unacknowwedged data */
#define IP_CT_TCP_FWAG_DATA_UNACKNOWWEDGED	0x10

/* The fiewd td_maxack has been set */
#define IP_CT_TCP_FWAG_MAXACK_SET		0x20

/* Mawks possibiwity fow expected WFC5961 chawwenge ACK */
#define IP_CT_EXP_CHAWWENGE_ACK 		0x40

/* Simuwtaneous open initiawized */
#define IP_CT_TCP_SIMUWTANEOUS_OPEN		0x80

stwuct nf_ct_tcp_fwags {
	__u8 fwags;
	__u8 mask;
};


#endif /* _UAPI_NF_CONNTWACK_TCP_H */
