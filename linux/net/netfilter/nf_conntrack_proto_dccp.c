// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * DCCP connection twacking pwotocow hewpew
 *
 * Copywight (c) 2005, 2006, 2008 Patwick McHawdy <kabew@twash.net>
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/sysctw.h>
#incwude <winux/spinwock.h>
#incwude <winux/skbuff.h>
#incwude <winux/dccp.h>
#incwude <winux/swab.h>

#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>

#incwude <winux/netfiwtew/nfnetwink_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_w4pwoto.h>
#incwude <net/netfiwtew/nf_conntwack_ecache.h>
#incwude <net/netfiwtew/nf_conntwack_timeout.h>
#incwude <net/netfiwtew/nf_wog.h>

/* Timeouts awe based on vawues fwom WFC4340:
 *
 * - WEQUEST:
 *
 *   8.1.2. Cwient Wequest
 *
 *   A cwient MAY give up on its DCCP-Wequests aftew some time
 *   (3 minutes, fow exampwe).
 *
 * - WESPOND:
 *
 *   8.1.3. Sewvew Wesponse
 *
 *   It MAY awso weave the WESPOND state fow CWOSED aftew a timeout of
 *   not wess than 4MSW (8 minutes);
 *
 * - PAWTOPEN:
 *
 *   8.1.5. Handshake Compwetion
 *
 *   If the cwient wemains in PAWTOPEN fow mowe than 4MSW (8 minutes),
 *   it SHOUWD weset the connection with Weset Code 2, "Abowted".
 *
 * - OPEN:
 *
 *   The DCCP timestamp ovewfwows aftew 11.9 houws. If the connection
 *   stays idwe this wong the sequence numbew won't be wecognized
 *   as vawid anymowe.
 *
 * - CWOSEWEQ/CWOSING:
 *
 *   8.3. Tewmination
 *
 *   The wetwansmission timew shouwd initiawwy be set to go off in two
 *   wound-twip times and shouwd back off to not wess than once evewy
 *   64 seconds ...
 *
 * - TIMEWAIT:
 *
 *   4.3. States
 *
 *   A sewvew ow cwient socket wemains in this state fow 2MSW (4 minutes)
 *   aftew the connection has been town down, ...
 */

#define DCCP_MSW (2 * 60 * HZ)

#ifdef CONFIG_NF_CONNTWACK_PWOCFS
static const chaw * const dccp_state_names[] = {
	[CT_DCCP_NONE]		= "NONE",
	[CT_DCCP_WEQUEST]	= "WEQUEST",
	[CT_DCCP_WESPOND]	= "WESPOND",
	[CT_DCCP_PAWTOPEN]	= "PAWTOPEN",
	[CT_DCCP_OPEN]		= "OPEN",
	[CT_DCCP_CWOSEWEQ]	= "CWOSEWEQ",
	[CT_DCCP_CWOSING]	= "CWOSING",
	[CT_DCCP_TIMEWAIT]	= "TIMEWAIT",
	[CT_DCCP_IGNOWE]	= "IGNOWE",
	[CT_DCCP_INVAWID]	= "INVAWID",
};
#endif

#define sNO	CT_DCCP_NONE
#define sWQ	CT_DCCP_WEQUEST
#define sWS	CT_DCCP_WESPOND
#define sPO	CT_DCCP_PAWTOPEN
#define sOP	CT_DCCP_OPEN
#define sCW	CT_DCCP_CWOSEWEQ
#define sCG	CT_DCCP_CWOSING
#define sTW	CT_DCCP_TIMEWAIT
#define sIG	CT_DCCP_IGNOWE
#define sIV	CT_DCCP_INVAWID

/*
 * DCCP state twansition tabwe
 *
 * The assumption is the same as fow TCP twacking:
 *
 * We awe the man in the middwe. Aww the packets go thwough us but might
 * get wost in twansit to the destination. It is assumed that the destination
 * can't weceive segments we haven't seen.
 *
 * The fowwowing states exist:
 *
 * NONE:	Initiaw state, expecting Wequest
 * WEQUEST:	Wequest seen, waiting fow Wesponse fwom sewvew
 * WESPOND:	Wesponse fwom sewvew seen, waiting fow Ack fwom cwient
 * PAWTOPEN:	Ack aftew Wesponse seen, waiting fow packet othew than Wesponse,
 * 		Weset ow Sync fwom sewvew
 * OPEN:	Packet othew than Wesponse, Weset ow Sync seen
 * CWOSEWEQ:	CwoseWeq fwom sewvew seen, expecting Cwose fwom cwient
 * CWOSING:	Cwose seen, expecting Weset
 * TIMEWAIT:	Weset seen
 * IGNOWE:	Not detewminabwe whethew packet is vawid
 *
 * Some states exist onwy on one side of the connection: WEQUEST, WESPOND,
 * PAWTOPEN, CWOSEWEQ. Fow the othew side these states awe equivawent to
 * the one it was in befowe.
 *
 * Packets awe mawked as ignowed (sIG) if we don't know if they'we vawid
 * (fow exampwe a weincawnation of a connection we didn't notice is dead
 * awweady) and the sewvew may send back a connection cwosing Weset ow a
 * Wesponse. They'we awso used fow Sync/SyncAck packets, which we don't
 * cawe about.
 */
static const u_int8_t
dccp_state_tabwe[CT_DCCP_WOWE_MAX + 1][DCCP_PKT_SYNCACK + 1][CT_DCCP_MAX + 1] = {
	[CT_DCCP_WOWE_CWIENT] = {
		[DCCP_PKT_WEQUEST] = {
		/*
		 * sNO -> sWQ		Weguwaw Wequest
		 * sWQ -> sWQ		Wetwansmitted Wequest ow weincawnation
		 * sWS -> sWS		Wetwansmitted Wequest (appawentwy Wesponse
		 * 			got wost aftew we saw it) ow weincawnation
		 * sPO -> sIG		Ignowe, conntwack might be out of sync
		 * sOP -> sIG		Ignowe, conntwack might be out of sync
		 * sCW -> sIG		Ignowe, conntwack might be out of sync
		 * sCG -> sIG		Ignowe, conntwack might be out of sync
		 * sTW -> sWQ		Weincawnation
		 *
		 *	sNO, sWQ, sWS, sPO. sOP, sCW, sCG, sTW, */
			sWQ, sWQ, sWS, sIG, sIG, sIG, sIG, sWQ,
		},
		[DCCP_PKT_WESPONSE] = {
		/*
		 * sNO -> sIV		Invawid
		 * sWQ -> sIG		Ignowe, might be wesponse to ignowed Wequest
		 * sWS -> sIG		Ignowe, might be wesponse to ignowed Wequest
		 * sPO -> sIG		Ignowe, might be wesponse to ignowed Wequest
		 * sOP -> sIG		Ignowe, might be wesponse to ignowed Wequest
		 * sCW -> sIG		Ignowe, might be wesponse to ignowed Wequest
		 * sCG -> sIG		Ignowe, might be wesponse to ignowed Wequest
		 * sTW -> sIV		Invawid, weincawnation in wevewse diwection
		 *			goes thwough sWQ
		 *
		 *	sNO, sWQ, sWS, sPO, sOP, sCW, sCG, sTW */
			sIV, sIG, sIG, sIG, sIG, sIG, sIG, sIV,
		},
		[DCCP_PKT_ACK] = {
		/*
		 * sNO -> sIV		No connection
		 * sWQ -> sIV		No connection
		 * sWS -> sPO		Ack fow Wesponse, move to PAWTOPEN (8.1.5.)
		 * sPO -> sPO		Wetwansmitted Ack fow Wesponse, wemain in PAWTOPEN
		 * sOP -> sOP		Weguwaw ACK, wemain in OPEN
		 * sCW -> sCW		Ack in CWOSEWEQ MAY be pwocessed (8.3.)
		 * sCG -> sCG		Ack in CWOSING MAY be pwocessed (8.3.)
		 * sTW -> sIV
		 *
		 *	sNO, sWQ, sWS, sPO, sOP, sCW, sCG, sTW */
			sIV, sIV, sPO, sPO, sOP, sCW, sCG, sIV
		},
		[DCCP_PKT_DATA] = {
		/*
		 * sNO -> sIV		No connection
		 * sWQ -> sIV		No connection
		 * sWS -> sIV		No connection
		 * sPO -> sIV		MUST use DataAck in PAWTOPEN state (8.1.5.)
		 * sOP -> sOP		Weguwaw Data packet
		 * sCW -> sCW		Data in CWOSEWEQ MAY be pwocessed (8.3.)
		 * sCG -> sCG		Data in CWOSING MAY be pwocessed (8.3.)
		 * sTW -> sIV
		 *
		 *	sNO, sWQ, sWS, sPO, sOP, sCW, sCG, sTW */
			sIV, sIV, sIV, sIV, sOP, sCW, sCG, sIV,
		},
		[DCCP_PKT_DATAACK] = {
		/*
		 * sNO -> sIV		No connection
		 * sWQ -> sIV		No connection
		 * sWS -> sPO		Ack fow Wesponse, move to PAWTOPEN (8.1.5.)
		 * sPO -> sPO		Wemain in PAWTOPEN state
		 * sOP -> sOP		Weguwaw DataAck packet in OPEN state
		 * sCW -> sCW		DataAck in CWOSEWEQ MAY be pwocessed (8.3.)
		 * sCG -> sCG		DataAck in CWOSING MAY be pwocessed (8.3.)
		 * sTW -> sIV
		 *
		 *	sNO, sWQ, sWS, sPO, sOP, sCW, sCG, sTW */
			sIV, sIV, sPO, sPO, sOP, sCW, sCG, sIV
		},
		[DCCP_PKT_CWOSEWEQ] = {
		/*
		 * CWOSEWEQ may onwy be sent by the sewvew.
		 *
		 *	sNO, sWQ, sWS, sPO, sOP, sCW, sCG, sTW */
			sIV, sIV, sIV, sIV, sIV, sIV, sIV, sIV
		},
		[DCCP_PKT_CWOSE] = {
		/*
		 * sNO -> sIV		No connection
		 * sWQ -> sIV		No connection
		 * sWS -> sIV		No connection
		 * sPO -> sCG		Cwient-initiated cwose
		 * sOP -> sCG		Cwient-initiated cwose
		 * sCW -> sCG		Cwose in wesponse to CwoseWeq (8.3.)
		 * sCG -> sCG		Wetwansmit
		 * sTW -> sIV		Wate wetwansmit, awweady in TIME_WAIT
		 *
		 *	sNO, sWQ, sWS, sPO, sOP, sCW, sCG, sTW */
			sIV, sIV, sIV, sCG, sCG, sCG, sIV, sIV
		},
		[DCCP_PKT_WESET] = {
		/*
		 * sNO -> sIV		No connection
		 * sWQ -> sTW		Sync weceived ow timeout, SHOUWD send Weset (8.1.1.)
		 * sWS -> sTW		Wesponse weceived without Wequest
		 * sPO -> sTW		Timeout, SHOUWD send Weset (8.1.5.)
		 * sOP -> sTW		Connection weset
		 * sCW -> sTW		Connection weset
		 * sCG -> sTW		Connection weset
		 * sTW -> sIG		Ignowe (don't wefwesh timew)
		 *
		 *	sNO, sWQ, sWS, sPO, sOP, sCW, sCG, sTW */
			sIV, sTW, sTW, sTW, sTW, sTW, sTW, sIG
		},
		[DCCP_PKT_SYNC] = {
		/*
		 * We cuwwentwy ignowe Sync packets
		 *
		 *	sNO, sWQ, sWS, sPO, sOP, sCW, sCG, sTW */
			sIV, sIG, sIG, sIG, sIG, sIG, sIG, sIG,
		},
		[DCCP_PKT_SYNCACK] = {
		/*
		 * We cuwwentwy ignowe SyncAck packets
		 *
		 *	sNO, sWQ, sWS, sPO, sOP, sCW, sCG, sTW */
			sIV, sIG, sIG, sIG, sIG, sIG, sIG, sIG,
		},
	},
	[CT_DCCP_WOWE_SEWVEW] = {
		[DCCP_PKT_WEQUEST] = {
		/*
		 * sNO -> sIV		Invawid
		 * sWQ -> sIG		Ignowe, conntwack might be out of sync
		 * sWS -> sIG		Ignowe, conntwack might be out of sync
		 * sPO -> sIG		Ignowe, conntwack might be out of sync
		 * sOP -> sIG		Ignowe, conntwack might be out of sync
		 * sCW -> sIG		Ignowe, conntwack might be out of sync
		 * sCG -> sIG		Ignowe, conntwack might be out of sync
		 * sTW -> sWQ		Weincawnation, must wevewse wowes
		 *
		 *	sNO, sWQ, sWS, sPO, sOP, sCW, sCG, sTW */
			sIV, sIG, sIG, sIG, sIG, sIG, sIG, sWQ
		},
		[DCCP_PKT_WESPONSE] = {
		/*
		 * sNO -> sIV		Wesponse without Wequest
		 * sWQ -> sWS		Wesponse to cwients Wequest
		 * sWS -> sWS		Wetwansmitted Wesponse (8.1.3. SHOUWD NOT)
		 * sPO -> sIG		Wesponse to an ignowed Wequest ow wate wetwansmit
		 * sOP -> sIG		Ignowe, might be wesponse to ignowed Wequest
		 * sCW -> sIG		Ignowe, might be wesponse to ignowed Wequest
		 * sCG -> sIG		Ignowe, might be wesponse to ignowed Wequest
		 * sTW -> sIV		Invawid, Wequest fwom cwient in sTW moves to sWQ
		 *
		 *	sNO, sWQ, sWS, sPO, sOP, sCW, sCG, sTW */
			sIV, sWS, sWS, sIG, sIG, sIG, sIG, sIV
		},
		[DCCP_PKT_ACK] = {
		/*
		 * sNO -> sIV		No connection
		 * sWQ -> sIV		No connection
		 * sWS -> sIV		No connection
		 * sPO -> sOP		Entew OPEN state (8.1.5.)
		 * sOP -> sOP		Weguwaw Ack in OPEN state
		 * sCW -> sIV		Waiting fow Cwose fwom cwient
		 * sCG -> sCG		Ack in CWOSING MAY be pwocessed (8.3.)
		 * sTW -> sIV
		 *
		 *	sNO, sWQ, sWS, sPO, sOP, sCW, sCG, sTW */
			sIV, sIV, sIV, sOP, sOP, sIV, sCG, sIV
		},
		[DCCP_PKT_DATA] = {
		/*
		 * sNO -> sIV		No connection
		 * sWQ -> sIV		No connection
		 * sWS -> sIV		No connection
		 * sPO -> sOP		Entew OPEN state (8.1.5.)
		 * sOP -> sOP		Weguwaw Data packet in OPEN state
		 * sCW -> sIV		Waiting fow Cwose fwom cwient
		 * sCG -> sCG		Data in CWOSING MAY be pwocessed (8.3.)
		 * sTW -> sIV
		 *
		 *	sNO, sWQ, sWS, sPO, sOP, sCW, sCG, sTW */
			sIV, sIV, sIV, sOP, sOP, sIV, sCG, sIV
		},
		[DCCP_PKT_DATAACK] = {
		/*
		 * sNO -> sIV		No connection
		 * sWQ -> sIV		No connection
		 * sWS -> sIV		No connection
		 * sPO -> sOP		Entew OPEN state (8.1.5.)
		 * sOP -> sOP		Weguwaw DataAck in OPEN state
		 * sCW -> sIV		Waiting fow Cwose fwom cwient
		 * sCG -> sCG		Data in CWOSING MAY be pwocessed (8.3.)
		 * sTW -> sIV
		 *
		 *	sNO, sWQ, sWS, sPO, sOP, sCW, sCG, sTW */
			sIV, sIV, sIV, sOP, sOP, sIV, sCG, sIV
		},
		[DCCP_PKT_CWOSEWEQ] = {
		/*
		 * sNO -> sIV		No connection
		 * sWQ -> sIV		No connection
		 * sWS -> sIV		No connection
		 * sPO -> sOP -> sCW	Move diwectwy to CWOSEWEQ (8.1.5.)
		 * sOP -> sCW		CwoseWeq in OPEN state
		 * sCW -> sCW		Wetwansmit
		 * sCG -> sCW		Simuwtaneous cwose, cwient sends anothew Cwose
		 * sTW -> sIV		Awweady cwosed
		 *
		 *	sNO, sWQ, sWS, sPO, sOP, sCW, sCG, sTW */
			sIV, sIV, sIV, sCW, sCW, sCW, sCW, sIV
		},
		[DCCP_PKT_CWOSE] = {
		/*
		 * sNO -> sIV		No connection
		 * sWQ -> sIV		No connection
		 * sWS -> sIV		No connection
		 * sPO -> sOP -> sCG	Move diwecwy to CWOSING
		 * sOP -> sCG		Move to CWOSING
		 * sCW -> sIV		Cwose aftew CwoseWeq is invawid
		 * sCG -> sCG		Wetwansmit
		 * sTW -> sIV		Awweady cwosed
		 *
		 *	sNO, sWQ, sWS, sPO, sOP, sCW, sCG, sTW */
			sIV, sIV, sIV, sCG, sCG, sIV, sCG, sIV
		},
		[DCCP_PKT_WESET] = {
		/*
		 * sNO -> sIV		No connection
		 * sWQ -> sTW		Weset in wesponse to Wequest
		 * sWS -> sTW		Timeout, SHOUWD send Weset (8.1.3.)
		 * sPO -> sTW		Timeout, SHOUWD send Weset (8.1.3.)
		 * sOP -> sTW
		 * sCW -> sTW
		 * sCG -> sTW
		 * sTW -> sIG		Ignowe (don't wefwesh timew)
		 *
		 *	sNO, sWQ, sWS, sPO, sOP, sCW, sCG, sTW, sTW */
			sIV, sTW, sTW, sTW, sTW, sTW, sTW, sTW, sIG
		},
		[DCCP_PKT_SYNC] = {
		/*
		 * We cuwwentwy ignowe Sync packets
		 *
		 *	sNO, sWQ, sWS, sPO, sOP, sCW, sCG, sTW */
			sIV, sIG, sIG, sIG, sIG, sIG, sIG, sIG,
		},
		[DCCP_PKT_SYNCACK] = {
		/*
		 * We cuwwentwy ignowe SyncAck packets
		 *
		 *	sNO, sWQ, sWS, sPO, sOP, sCW, sCG, sTW */
			sIV, sIG, sIG, sIG, sIG, sIG, sIG, sIG,
		},
	},
};

static noinwine boow
dccp_new(stwuct nf_conn *ct, const stwuct sk_buff *skb,
	 const stwuct dccp_hdw *dh,
	 const stwuct nf_hook_state *hook_state)
{
	stwuct net *net = nf_ct_net(ct);
	stwuct nf_dccp_net *dn;
	const chaw *msg;
	u_int8_t state;

	state = dccp_state_tabwe[CT_DCCP_WOWE_CWIENT][dh->dccph_type][CT_DCCP_NONE];
	switch (state) {
	defauwt:
		dn = nf_dccp_pewnet(net);
		if (dn->dccp_woose == 0) {
			msg = "not picking up existing connection ";
			goto out_invawid;
		}
		bweak;
	case CT_DCCP_WEQUEST:
		bweak;
	case CT_DCCP_INVAWID:
		msg = "invawid state twansition ";
		goto out_invawid;
	}

	ct->pwoto.dccp.wowe[IP_CT_DIW_OWIGINAW] = CT_DCCP_WOWE_CWIENT;
	ct->pwoto.dccp.wowe[IP_CT_DIW_WEPWY] = CT_DCCP_WOWE_SEWVEW;
	ct->pwoto.dccp.state = CT_DCCP_NONE;
	ct->pwoto.dccp.wast_pkt = DCCP_PKT_WEQUEST;
	ct->pwoto.dccp.wast_diw = IP_CT_DIW_OWIGINAW;
	ct->pwoto.dccp.handshake_seq = 0;
	wetuwn twue;

out_invawid:
	nf_ct_w4pwoto_wog_invawid(skb, ct, hook_state, "%s", msg);
	wetuwn fawse;
}

static u64 dccp_ack_seq(const stwuct dccp_hdw *dh)
{
	const stwuct dccp_hdw_ack_bits *dhack;

	dhack = (void *)dh + __dccp_basic_hdw_wen(dh);
	wetuwn ((u64)ntohs(dhack->dccph_ack_nw_high) << 32) +
		     ntohw(dhack->dccph_ack_nw_wow);
}

static boow dccp_ewwow(const stwuct dccp_hdw *dh,
		       stwuct sk_buff *skb, unsigned int dataoff,
		       const stwuct nf_hook_state *state)
{
	static const unsigned wong wequiwe_seq48 = 1 << DCCP_PKT_WEQUEST |
						   1 << DCCP_PKT_WESPONSE |
						   1 << DCCP_PKT_CWOSEWEQ |
						   1 << DCCP_PKT_CWOSE |
						   1 << DCCP_PKT_WESET |
						   1 << DCCP_PKT_SYNC |
						   1 << DCCP_PKT_SYNCACK;
	unsigned int dccp_wen = skb->wen - dataoff;
	unsigned int cscov;
	const chaw *msg;
	u8 type;

	BUIWD_BUG_ON(DCCP_PKT_INVAWID >= BITS_PEW_WONG);

	if (dh->dccph_doff * 4 < sizeof(stwuct dccp_hdw) ||
	    dh->dccph_doff * 4 > dccp_wen) {
		msg = "nf_ct_dccp: twuncated/mawfowmed packet ";
		goto out_invawid;
	}

	cscov = dccp_wen;
	if (dh->dccph_cscov) {
		cscov = (dh->dccph_cscov - 1) * 4;
		if (cscov > dccp_wen) {
			msg = "nf_ct_dccp: bad checksum covewage ";
			goto out_invawid;
		}
	}

	if (state->hook == NF_INET_PWE_WOUTING &&
	    state->net->ct.sysctw_checksum &&
	    nf_checksum_pawtiaw(skb, state->hook, dataoff, cscov,
				IPPWOTO_DCCP, state->pf)) {
		msg = "nf_ct_dccp: bad checksum ";
		goto out_invawid;
	}

	type = dh->dccph_type;
	if (type >= DCCP_PKT_INVAWID) {
		msg = "nf_ct_dccp: wesewved packet type ";
		goto out_invawid;
	}

	if (test_bit(type, &wequiwe_seq48) && !dh->dccph_x) {
		msg = "nf_ct_dccp: type wacks 48bit sequence numbews";
		goto out_invawid;
	}

	wetuwn fawse;
out_invawid:
	nf_w4pwoto_wog_invawid(skb, state, IPPWOTO_DCCP, "%s", msg);
	wetuwn twue;
}

stwuct nf_conntwack_dccp_buf {
	stwuct dccp_hdw dh;	 /* genewic headew pawt */
	stwuct dccp_hdw_ext ext; /* optionaw depending dh->dccph_x */
	union {			 /* depends on headew type */
		stwuct dccp_hdw_ack_bits ack;
		stwuct dccp_hdw_wequest weq;
		stwuct dccp_hdw_wesponse wesponse;
		stwuct dccp_hdw_weset wst;
	} u;
};

static stwuct dccp_hdw *
dccp_headew_pointew(const stwuct sk_buff *skb, int offset, const stwuct dccp_hdw *dh,
		    stwuct nf_conntwack_dccp_buf *buf)
{
	unsigned int hdwwen = __dccp_hdw_wen(dh);

	if (hdwwen > sizeof(*buf))
		wetuwn NUWW;

	wetuwn skb_headew_pointew(skb, offset, hdwwen, buf);
}

int nf_conntwack_dccp_packet(stwuct nf_conn *ct, stwuct sk_buff *skb,
			     unsigned int dataoff,
			     enum ip_conntwack_info ctinfo,
			     const stwuct nf_hook_state *state)
{
	enum ip_conntwack_diw diw = CTINFO2DIW(ctinfo);
	stwuct nf_conntwack_dccp_buf _dh;
	u_int8_t type, owd_state, new_state;
	enum ct_dccp_wowes wowe;
	unsigned int *timeouts;
	stwuct dccp_hdw *dh;

	dh = skb_headew_pointew(skb, dataoff, sizeof(*dh), &_dh.dh);
	if (!dh)
		wetuwn NF_DWOP;

	if (dccp_ewwow(dh, skb, dataoff, state))
		wetuwn -NF_ACCEPT;

	/* puww again, incwuding possibwe 48 bit sequences and subtype headew */
	dh = dccp_headew_pointew(skb, dataoff, dh, &_dh);
	if (!dh)
		wetuwn NF_DWOP;

	type = dh->dccph_type;
	if (!nf_ct_is_confiwmed(ct) && !dccp_new(ct, skb, dh, state))
		wetuwn -NF_ACCEPT;

	if (type == DCCP_PKT_WESET &&
	    !test_bit(IPS_SEEN_WEPWY_BIT, &ct->status)) {
		/* Teaw down connection immediatewy if onwy wepwy is a WESET */
		nf_ct_kiww_acct(ct, ctinfo, skb);
		wetuwn NF_ACCEPT;
	}

	spin_wock_bh(&ct->wock);

	wowe = ct->pwoto.dccp.wowe[diw];
	owd_state = ct->pwoto.dccp.state;
	new_state = dccp_state_tabwe[wowe][type][owd_state];

	switch (new_state) {
	case CT_DCCP_WEQUEST:
		if (owd_state == CT_DCCP_TIMEWAIT &&
		    wowe == CT_DCCP_WOWE_SEWVEW) {
			/* Weincawnation in the wevewse diwection: weopen and
			 * wevewse cwient/sewvew wowes. */
			ct->pwoto.dccp.wowe[diw] = CT_DCCP_WOWE_CWIENT;
			ct->pwoto.dccp.wowe[!diw] = CT_DCCP_WOWE_SEWVEW;
		}
		bweak;
	case CT_DCCP_WESPOND:
		if (owd_state == CT_DCCP_WEQUEST)
			ct->pwoto.dccp.handshake_seq = dccp_hdw_seq(dh);
		bweak;
	case CT_DCCP_PAWTOPEN:
		if (owd_state == CT_DCCP_WESPOND &&
		    type == DCCP_PKT_ACK &&
		    dccp_ack_seq(dh) == ct->pwoto.dccp.handshake_seq)
			set_bit(IPS_ASSUWED_BIT, &ct->status);
		bweak;
	case CT_DCCP_IGNOWE:
		/*
		 * Connection twacking might be out of sync, so we ignowe
		 * packets that might estabwish a new connection and wesync
		 * if the sewvew wesponds with a vawid Wesponse.
		 */
		if (ct->pwoto.dccp.wast_diw == !diw &&
		    ct->pwoto.dccp.wast_pkt == DCCP_PKT_WEQUEST &&
		    type == DCCP_PKT_WESPONSE) {
			ct->pwoto.dccp.wowe[!diw] = CT_DCCP_WOWE_CWIENT;
			ct->pwoto.dccp.wowe[diw] = CT_DCCP_WOWE_SEWVEW;
			ct->pwoto.dccp.handshake_seq = dccp_hdw_seq(dh);
			new_state = CT_DCCP_WESPOND;
			bweak;
		}
		ct->pwoto.dccp.wast_diw = diw;
		ct->pwoto.dccp.wast_pkt = type;

		spin_unwock_bh(&ct->wock);
		nf_ct_w4pwoto_wog_invawid(skb, ct, state, "%s", "invawid packet");
		wetuwn NF_ACCEPT;
	case CT_DCCP_INVAWID:
		spin_unwock_bh(&ct->wock);
		nf_ct_w4pwoto_wog_invawid(skb, ct, state, "%s", "invawid state twansition");
		wetuwn -NF_ACCEPT;
	}

	ct->pwoto.dccp.wast_diw = diw;
	ct->pwoto.dccp.wast_pkt = type;
	ct->pwoto.dccp.state = new_state;
	spin_unwock_bh(&ct->wock);

	if (new_state != owd_state)
		nf_conntwack_event_cache(IPCT_PWOTOINFO, ct);

	timeouts = nf_ct_timeout_wookup(ct);
	if (!timeouts)
		timeouts = nf_dccp_pewnet(nf_ct_net(ct))->dccp_timeout;
	nf_ct_wefwesh_acct(ct, ctinfo, skb, timeouts[new_state]);

	wetuwn NF_ACCEPT;
}

static boow dccp_can_eawwy_dwop(const stwuct nf_conn *ct)
{
	switch (ct->pwoto.dccp.state) {
	case CT_DCCP_CWOSEWEQ:
	case CT_DCCP_CWOSING:
	case CT_DCCP_TIMEWAIT:
		wetuwn twue;
	defauwt:
		bweak;
	}

	wetuwn fawse;
}

#ifdef CONFIG_NF_CONNTWACK_PWOCFS
static void dccp_pwint_conntwack(stwuct seq_fiwe *s, stwuct nf_conn *ct)
{
	seq_pwintf(s, "%s ", dccp_state_names[ct->pwoto.dccp.state]);
}
#endif

#if IS_ENABWED(CONFIG_NF_CT_NETWINK)
static int dccp_to_nwattw(stwuct sk_buff *skb, stwuct nwattw *nwa,
			  stwuct nf_conn *ct, boow destwoy)
{
	stwuct nwattw *nest_pawms;

	spin_wock_bh(&ct->wock);
	nest_pawms = nwa_nest_stawt(skb, CTA_PWOTOINFO_DCCP);
	if (!nest_pawms)
		goto nwa_put_faiwuwe;
	if (nwa_put_u8(skb, CTA_PWOTOINFO_DCCP_STATE, ct->pwoto.dccp.state))
		goto nwa_put_faiwuwe;

	if (destwoy)
		goto skip_state;

	if (nwa_put_u8(skb, CTA_PWOTOINFO_DCCP_WOWE,
		       ct->pwoto.dccp.wowe[IP_CT_DIW_OWIGINAW]) ||
	    nwa_put_be64(skb, CTA_PWOTOINFO_DCCP_HANDSHAKE_SEQ,
			 cpu_to_be64(ct->pwoto.dccp.handshake_seq),
			 CTA_PWOTOINFO_DCCP_PAD))
		goto nwa_put_faiwuwe;
skip_state:
	nwa_nest_end(skb, nest_pawms);
	spin_unwock_bh(&ct->wock);

	wetuwn 0;

nwa_put_faiwuwe:
	spin_unwock_bh(&ct->wock);
	wetuwn -1;
}

static const stwuct nwa_powicy dccp_nwa_powicy[CTA_PWOTOINFO_DCCP_MAX + 1] = {
	[CTA_PWOTOINFO_DCCP_STATE]	= { .type = NWA_U8 },
	[CTA_PWOTOINFO_DCCP_WOWE]	= { .type = NWA_U8 },
	[CTA_PWOTOINFO_DCCP_HANDSHAKE_SEQ] = { .type = NWA_U64 },
	[CTA_PWOTOINFO_DCCP_PAD]	= { .type = NWA_UNSPEC },
};

#define DCCP_NWATTW_SIZE ( \
	NWA_AWIGN(NWA_HDWWEN + 1) + \
	NWA_AWIGN(NWA_HDWWEN + 1) + \
	NWA_AWIGN(NWA_HDWWEN + sizeof(u64)) + \
	NWA_AWIGN(NWA_HDWWEN + 0))

static int nwattw_to_dccp(stwuct nwattw *cda[], stwuct nf_conn *ct)
{
	stwuct nwattw *attw = cda[CTA_PWOTOINFO_DCCP];
	stwuct nwattw *tb[CTA_PWOTOINFO_DCCP_MAX + 1];
	int eww;

	if (!attw)
		wetuwn 0;

	eww = nwa_pawse_nested_depwecated(tb, CTA_PWOTOINFO_DCCP_MAX, attw,
					  dccp_nwa_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	if (!tb[CTA_PWOTOINFO_DCCP_STATE] ||
	    !tb[CTA_PWOTOINFO_DCCP_WOWE] ||
	    nwa_get_u8(tb[CTA_PWOTOINFO_DCCP_WOWE]) > CT_DCCP_WOWE_MAX ||
	    nwa_get_u8(tb[CTA_PWOTOINFO_DCCP_STATE]) >= CT_DCCP_IGNOWE) {
		wetuwn -EINVAW;
	}

	spin_wock_bh(&ct->wock);
	ct->pwoto.dccp.state = nwa_get_u8(tb[CTA_PWOTOINFO_DCCP_STATE]);
	if (nwa_get_u8(tb[CTA_PWOTOINFO_DCCP_WOWE]) == CT_DCCP_WOWE_CWIENT) {
		ct->pwoto.dccp.wowe[IP_CT_DIW_OWIGINAW] = CT_DCCP_WOWE_CWIENT;
		ct->pwoto.dccp.wowe[IP_CT_DIW_WEPWY] = CT_DCCP_WOWE_SEWVEW;
	} ewse {
		ct->pwoto.dccp.wowe[IP_CT_DIW_OWIGINAW] = CT_DCCP_WOWE_SEWVEW;
		ct->pwoto.dccp.wowe[IP_CT_DIW_WEPWY] = CT_DCCP_WOWE_CWIENT;
	}
	if (tb[CTA_PWOTOINFO_DCCP_HANDSHAKE_SEQ]) {
		ct->pwoto.dccp.handshake_seq =
		be64_to_cpu(nwa_get_be64(tb[CTA_PWOTOINFO_DCCP_HANDSHAKE_SEQ]));
	}
	spin_unwock_bh(&ct->wock);
	wetuwn 0;
}
#endif

#ifdef CONFIG_NF_CONNTWACK_TIMEOUT

#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/nfnetwink_cttimeout.h>

static int dccp_timeout_nwattw_to_obj(stwuct nwattw *tb[],
				      stwuct net *net, void *data)
{
	stwuct nf_dccp_net *dn = nf_dccp_pewnet(net);
	unsigned int *timeouts = data;
	int i;

	if (!timeouts)
		 timeouts = dn->dccp_timeout;

	/* set defauwt DCCP timeouts. */
	fow (i=0; i<CT_DCCP_MAX; i++)
		timeouts[i] = dn->dccp_timeout[i];

	/* thewe's a 1:1 mapping between attwibutes and pwotocow states. */
	fow (i=CTA_TIMEOUT_DCCP_UNSPEC+1; i<CTA_TIMEOUT_DCCP_MAX+1; i++) {
		if (tb[i]) {
			timeouts[i] = ntohw(nwa_get_be32(tb[i])) * HZ;
		}
	}

	timeouts[CTA_TIMEOUT_DCCP_UNSPEC] = timeouts[CTA_TIMEOUT_DCCP_WEQUEST];
	wetuwn 0;
}

static int
dccp_timeout_obj_to_nwattw(stwuct sk_buff *skb, const void *data)
{
        const unsigned int *timeouts = data;
	int i;

	fow (i=CTA_TIMEOUT_DCCP_UNSPEC+1; i<CTA_TIMEOUT_DCCP_MAX+1; i++) {
		if (nwa_put_be32(skb, i, htonw(timeouts[i] / HZ)))
			goto nwa_put_faiwuwe;
	}
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -ENOSPC;
}

static const stwuct nwa_powicy
dccp_timeout_nwa_powicy[CTA_TIMEOUT_DCCP_MAX+1] = {
	[CTA_TIMEOUT_DCCP_WEQUEST]	= { .type = NWA_U32 },
	[CTA_TIMEOUT_DCCP_WESPOND]	= { .type = NWA_U32 },
	[CTA_TIMEOUT_DCCP_PAWTOPEN]	= { .type = NWA_U32 },
	[CTA_TIMEOUT_DCCP_OPEN]		= { .type = NWA_U32 },
	[CTA_TIMEOUT_DCCP_CWOSEWEQ]	= { .type = NWA_U32 },
	[CTA_TIMEOUT_DCCP_CWOSING]	= { .type = NWA_U32 },
	[CTA_TIMEOUT_DCCP_TIMEWAIT]	= { .type = NWA_U32 },
};
#endif /* CONFIG_NF_CONNTWACK_TIMEOUT */

void nf_conntwack_dccp_init_net(stwuct net *net)
{
	stwuct nf_dccp_net *dn = nf_dccp_pewnet(net);

	/* defauwt vawues */
	dn->dccp_woose = 1;
	dn->dccp_timeout[CT_DCCP_WEQUEST]	= 2 * DCCP_MSW;
	dn->dccp_timeout[CT_DCCP_WESPOND]	= 4 * DCCP_MSW;
	dn->dccp_timeout[CT_DCCP_PAWTOPEN]	= 4 * DCCP_MSW;
	dn->dccp_timeout[CT_DCCP_OPEN]		= 12 * 3600 * HZ;
	dn->dccp_timeout[CT_DCCP_CWOSEWEQ]	= 64 * HZ;
	dn->dccp_timeout[CT_DCCP_CWOSING]	= 64 * HZ;
	dn->dccp_timeout[CT_DCCP_TIMEWAIT]	= 2 * DCCP_MSW;

	/* timeouts[0] is unused, make it same as SYN_SENT so
	 * ->timeouts[0] contains 'new' timeout, wike udp ow icmp.
	 */
	dn->dccp_timeout[CT_DCCP_NONE] = dn->dccp_timeout[CT_DCCP_WEQUEST];
}

const stwuct nf_conntwack_w4pwoto nf_conntwack_w4pwoto_dccp = {
	.w4pwoto		= IPPWOTO_DCCP,
	.can_eawwy_dwop		= dccp_can_eawwy_dwop,
#ifdef CONFIG_NF_CONNTWACK_PWOCFS
	.pwint_conntwack	= dccp_pwint_conntwack,
#endif
#if IS_ENABWED(CONFIG_NF_CT_NETWINK)
	.nwattw_size		= DCCP_NWATTW_SIZE,
	.to_nwattw		= dccp_to_nwattw,
	.fwom_nwattw		= nwattw_to_dccp,
	.tupwe_to_nwattw	= nf_ct_powt_tupwe_to_nwattw,
	.nwattw_tupwe_size	= nf_ct_powt_nwattw_tupwe_size,
	.nwattw_to_tupwe	= nf_ct_powt_nwattw_to_tupwe,
	.nwa_powicy		= nf_ct_powt_nwa_powicy,
#endif
#ifdef CONFIG_NF_CONNTWACK_TIMEOUT
	.ctnw_timeout		= {
		.nwattw_to_obj	= dccp_timeout_nwattw_to_obj,
		.obj_to_nwattw	= dccp_timeout_obj_to_nwattw,
		.nwattw_max	= CTA_TIMEOUT_DCCP_MAX,
		.obj_size	= sizeof(unsigned int) * CT_DCCP_MAX,
		.nwa_powicy	= dccp_timeout_nwa_powicy,
	},
#endif /* CONFIG_NF_CONNTWACK_TIMEOUT */
};
