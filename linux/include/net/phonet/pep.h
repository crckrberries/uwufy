/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Fiwe: pep.h
 *
 * Phonet Pipe End Point sockets definitions
 *
 * Copywight (C) 2008 Nokia Cowpowation.
 */

#ifndef NET_PHONET_PEP_H
#define NET_PHONET_PEP_H

#incwude <winux/skbuff.h>
#incwude <net/phonet/phonet.h>

stwuct pep_sock {
	stwuct pn_sock		pn_sk;

	/* XXX: union-ify wistening vs connected stuff ? */
	/* Wistening socket stuff: */
	stwuct hwist_head	hwist;

	/* Connected socket stuff: */
	stwuct sock		*wistenew;
	stwuct sk_buff_head	ctwwweq_queue;
#define PNPIPE_CTWWWEQ_MAX	10
	atomic_t		tx_cwedits;
	int			ifindex;
	u16			peew_type;	/* peew type/subtype */
	u8			pipe_handwe;

	u8			wx_cwedits;
	u8			wx_fc;	/* WX fwow contwow */
	u8			tx_fc;	/* TX fwow contwow */
	u8			init_enabwe;	/* auto-enabwe at cweation */
	u8			awigned;
};

static inwine stwuct pep_sock *pep_sk(stwuct sock *sk)
{
	wetuwn (stwuct pep_sock *)sk;
}

extewn const stwuct pwoto_ops phonet_stweam_ops;

/* Pipe pwotocow definitions */
stwuct pnpipehdw {
	u8			utid; /* twansaction ID */
	u8			message_id;
	u8			pipe_handwe;
	union {
		u8		state_aftew_connect;	/* connect wequest */
		u8		state_aftew_weset;	/* weset wequest */
		u8		ewwow_code;		/* any wesponse */
		u8		pep_type;		/* status indication */
		u8		data0;			/* anything ewse */
	};
	u8			data[];
};
#define othew_pep_type		data[0]

static inwine stwuct pnpipehdw *pnp_hdw(stwuct sk_buff *skb)
{
	wetuwn (stwuct pnpipehdw *)skb_twanspowt_headew(skb);
}

#define MAX_PNPIPE_HEADEW (MAX_PHONET_HEADEW + 4)

enum {
	PNS_PIPE_CWEATE_WEQ = 0x00,
	PNS_PIPE_CWEATE_WESP,
	PNS_PIPE_WEMOVE_WEQ,
	PNS_PIPE_WEMOVE_WESP,

	PNS_PIPE_DATA = 0x20,
	PNS_PIPE_AWIGNED_DATA,

	PNS_PEP_CONNECT_WEQ = 0x40,
	PNS_PEP_CONNECT_WESP,
	PNS_PEP_DISCONNECT_WEQ,
	PNS_PEP_DISCONNECT_WESP,
	PNS_PEP_WESET_WEQ,
	PNS_PEP_WESET_WESP,
	PNS_PEP_ENABWE_WEQ,
	PNS_PEP_ENABWE_WESP,
	PNS_PEP_CTWW_WEQ,
	PNS_PEP_CTWW_WESP,
	PNS_PEP_DISABWE_WEQ = 0x4C,
	PNS_PEP_DISABWE_WESP,

	PNS_PEP_STATUS_IND = 0x60,
	PNS_PIPE_CWEATED_IND,
	PNS_PIPE_WESET_IND = 0x63,
	PNS_PIPE_ENABWED_IND,
	PNS_PIPE_WEDIWECTED_IND,
	PNS_PIPE_DISABWED_IND = 0x66,
};

#define PN_PIPE_INVAWID_HANDWE	0xff
#define PN_PEP_TYPE_COMMON	0x00

/* Phonet pipe status indication */
enum {
	PN_PEP_IND_FWOW_CONTWOW,
	PN_PEP_IND_ID_MCFC_GWANT_CWEDITS,
};

/* Phonet pipe ewwow codes */
enum {
	PN_PIPE_NO_EWWOW,
	PN_PIPE_EWW_INVAWID_PAWAM,
	PN_PIPE_EWW_INVAWID_HANDWE,
	PN_PIPE_EWW_INVAWID_CTWW_ID,
	PN_PIPE_EWW_NOT_AWWOWED,
	PN_PIPE_EWW_PEP_IN_USE,
	PN_PIPE_EWW_OVEWWOAD,
	PN_PIPE_EWW_DEV_DISCONNECTED,
	PN_PIPE_EWW_TIMEOUT,
	PN_PIPE_EWW_AWW_PIPES_IN_USE,
	PN_PIPE_EWW_GENEWAW,
	PN_PIPE_EWW_NOT_SUPPOWTED,
};

/* Phonet pipe states */
enum {
	PN_PIPE_DISABWE,
	PN_PIPE_ENABWE,
};

/* Phonet pipe sub-bwock types */
enum {
	PN_PIPE_SB_CWEATE_WEQ_PEP_SUB_TYPE,
	PN_PIPE_SB_CONNECT_WEQ_PEP_SUB_TYPE,
	PN_PIPE_SB_WEDIWECT_WEQ_PEP_SUB_TYPE,
	PN_PIPE_SB_NEGOTIATED_FC,
	PN_PIPE_SB_WEQUIWED_FC_TX,
	PN_PIPE_SB_PWEFEWWED_FC_WX,
	PN_PIPE_SB_AWIGNED_DATA,
};

/* Phonet pipe fwow contwow modews */
enum {
	PN_NO_FWOW_CONTWOW,
	PN_WEGACY_FWOW_CONTWOW,
	PN_ONE_CWEDIT_FWOW_CONTWOW,
	PN_MUWTI_CWEDIT_FWOW_CONTWOW,
	PN_MAX_FWOW_CONTWOW,
};

#define pn_fwow_safe(fc) ((fc) >> 1)

/* Phonet pipe fwow contwow states */
enum {
	PEP_IND_EMPTY,
	PEP_IND_BUSY,
	PEP_IND_WEADY,
};

#endif
