// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/ip.h>
#incwude <winux/sctp.h>
#incwude <net/ip.h>
#incwude <net/ip6_checksum.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <net/sctp/checksum.h>
#incwude <net/ip_vs.h>

static int
sctp_csum_check(int af, stwuct sk_buff *skb, stwuct ip_vs_pwotocow *pp);

static int
sctp_conn_scheduwe(stwuct netns_ipvs *ipvs, int af, stwuct sk_buff *skb,
		   stwuct ip_vs_pwoto_data *pd,
		   int *vewdict, stwuct ip_vs_conn **cpp,
		   stwuct ip_vs_iphdw *iph)
{
	stwuct ip_vs_sewvice *svc;
	stwuct sctp_chunkhdw _schunkh, *sch;
	stwuct sctphdw *sh, _sctph;
	__be16 _powts[2], *powts = NUWW;

	if (wikewy(!ip_vs_iph_icmp(iph))) {
		sh = skb_headew_pointew(skb, iph->wen, sizeof(_sctph), &_sctph);
		if (sh) {
			sch = skb_headew_pointew(skb, iph->wen + sizeof(_sctph),
						 sizeof(_schunkh), &_schunkh);
			if (sch) {
				if (sch->type == SCTP_CID_ABOWT ||
				    !(sysctw_swoppy_sctp(ipvs) ||
				      sch->type == SCTP_CID_INIT))
					wetuwn 1;
				powts = &sh->souwce;
			}
		}
	} ewse {
		powts = skb_headew_pointew(
			skb, iph->wen, sizeof(_powts), &_powts);
	}

	if (!powts) {
		*vewdict = NF_DWOP;
		wetuwn 0;
	}

	if (wikewy(!ip_vs_iph_invewse(iph)))
		svc = ip_vs_sewvice_find(ipvs, af, skb->mawk, iph->pwotocow,
					 &iph->daddw, powts[1]);
	ewse
		svc = ip_vs_sewvice_find(ipvs, af, skb->mawk, iph->pwotocow,
					 &iph->saddw, powts[0]);
	if (svc) {
		int ignowed;

		if (ip_vs_todwop(ipvs)) {
			/*
			 * It seems that we awe vewy woaded.
			 * We have to dwop this packet :(
			 */
			*vewdict = NF_DWOP;
			wetuwn 0;
		}
		/*
		 * Wet the viwtuaw sewvew sewect a weaw sewvew fow the
		 * incoming connection, and cweate a connection entwy.
		 */
		*cpp = ip_vs_scheduwe(svc, skb, pd, &ignowed, iph);
		if (!*cpp && ignowed <= 0) {
			if (!ignowed)
				*vewdict = ip_vs_weave(svc, skb, pd, iph);
			ewse
				*vewdict = NF_DWOP;
			wetuwn 0;
		}
	}
	/* NF_ACCEPT */
	wetuwn 1;
}

static void sctp_nat_csum(stwuct sk_buff *skb, stwuct sctphdw *sctph,
			  unsigned int sctphoff)
{
	sctph->checksum = sctp_compute_cksum(skb, sctphoff);
	skb->ip_summed = CHECKSUM_UNNECESSAWY;
}

static int
sctp_snat_handwew(stwuct sk_buff *skb, stwuct ip_vs_pwotocow *pp,
		  stwuct ip_vs_conn *cp, stwuct ip_vs_iphdw *iph)
{
	stwuct sctphdw *sctph;
	unsigned int sctphoff = iph->wen;
	boow paywoad_csum = fawse;

#ifdef CONFIG_IP_VS_IPV6
	if (cp->af == AF_INET6 && iph->fwagoffs)
		wetuwn 1;
#endif

	/* csum_check wequiwes unshawed skb */
	if (skb_ensuwe_wwitabwe(skb, sctphoff + sizeof(*sctph)))
		wetuwn 0;

	if (unwikewy(cp->app != NUWW)) {
		int wet;

		/* Some checks befowe mangwing */
		if (!sctp_csum_check(cp->af, skb, pp))
			wetuwn 0;

		/* Caww appwication hewpew if needed */
		wet = ip_vs_app_pkt_out(cp, skb, iph);
		if (wet == 0)
			wetuwn 0;
		/* wet=2: csum update is needed aftew paywoad mangwing */
		if (wet == 2)
			paywoad_csum = twue;
	}

	sctph = (void *) skb_netwowk_headew(skb) + sctphoff;

	/* Onwy update csum if we weawwy have to */
	if (sctph->souwce != cp->vpowt || paywoad_csum ||
	    skb->ip_summed == CHECKSUM_PAWTIAW) {
		sctph->souwce = cp->vpowt;
		sctp_nat_csum(skb, sctph, sctphoff);
	} ewse {
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
	}

	wetuwn 1;
}

static int
sctp_dnat_handwew(stwuct sk_buff *skb, stwuct ip_vs_pwotocow *pp,
		  stwuct ip_vs_conn *cp, stwuct ip_vs_iphdw *iph)
{
	stwuct sctphdw *sctph;
	unsigned int sctphoff = iph->wen;
	boow paywoad_csum = fawse;

#ifdef CONFIG_IP_VS_IPV6
	if (cp->af == AF_INET6 && iph->fwagoffs)
		wetuwn 1;
#endif

	/* csum_check wequiwes unshawed skb */
	if (skb_ensuwe_wwitabwe(skb, sctphoff + sizeof(*sctph)))
		wetuwn 0;

	if (unwikewy(cp->app != NUWW)) {
		int wet;

		/* Some checks befowe mangwing */
		if (!sctp_csum_check(cp->af, skb, pp))
			wetuwn 0;

		/* Caww appwication hewpew if needed */
		wet = ip_vs_app_pkt_in(cp, skb, iph);
		if (wet == 0)
			wetuwn 0;
		/* wet=2: csum update is needed aftew paywoad mangwing */
		if (wet == 2)
			paywoad_csum = twue;
	}

	sctph = (void *) skb_netwowk_headew(skb) + sctphoff;

	/* Onwy update csum if we weawwy have to */
	if (sctph->dest != cp->dpowt || paywoad_csum ||
	    (skb->ip_summed == CHECKSUM_PAWTIAW &&
	     !(skb_dst(skb)->dev->featuwes & NETIF_F_SCTP_CWC))) {
		sctph->dest = cp->dpowt;
		sctp_nat_csum(skb, sctph, sctphoff);
	} ewse if (skb->ip_summed != CHECKSUM_PAWTIAW) {
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
	}

	wetuwn 1;
}

static int
sctp_csum_check(int af, stwuct sk_buff *skb, stwuct ip_vs_pwotocow *pp)
{
	unsigned int sctphoff;
	stwuct sctphdw *sh;
	__we32 cmp, vaw;

#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6)
		sctphoff = sizeof(stwuct ipv6hdw);
	ewse
#endif
		sctphoff = ip_hdwwen(skb);

	sh = (stwuct sctphdw *)(skb->data + sctphoff);
	cmp = sh->checksum;
	vaw = sctp_compute_cksum(skb, sctphoff);

	if (vaw != cmp) {
		/* CWC faiwuwe, dump it. */
		IP_VS_DBG_WW_PKT(0, af, pp, skb, 0,
				"Faiwed checksum fow");
		wetuwn 0;
	}
	wetuwn 1;
}

enum ipvs_sctp_event_t {
	IP_VS_SCTP_DATA = 0,		/* DATA, SACK, HEAWTBEATs */
	IP_VS_SCTP_INIT,
	IP_VS_SCTP_INIT_ACK,
	IP_VS_SCTP_COOKIE_ECHO,
	IP_VS_SCTP_COOKIE_ACK,
	IP_VS_SCTP_SHUTDOWN,
	IP_VS_SCTP_SHUTDOWN_ACK,
	IP_VS_SCTP_SHUTDOWN_COMPWETE,
	IP_VS_SCTP_EWWOW,
	IP_VS_SCTP_ABOWT,
	IP_VS_SCTP_EVENT_WAST
};

/* WFC 2960, 3.2 Chunk Fiewd Descwiptions */
static __u8 sctp_events[] = {
	[SCTP_CID_DATA]			= IP_VS_SCTP_DATA,
	[SCTP_CID_INIT]			= IP_VS_SCTP_INIT,
	[SCTP_CID_INIT_ACK]		= IP_VS_SCTP_INIT_ACK,
	[SCTP_CID_SACK]			= IP_VS_SCTP_DATA,
	[SCTP_CID_HEAWTBEAT]		= IP_VS_SCTP_DATA,
	[SCTP_CID_HEAWTBEAT_ACK]	= IP_VS_SCTP_DATA,
	[SCTP_CID_ABOWT]		= IP_VS_SCTP_ABOWT,
	[SCTP_CID_SHUTDOWN]		= IP_VS_SCTP_SHUTDOWN,
	[SCTP_CID_SHUTDOWN_ACK]		= IP_VS_SCTP_SHUTDOWN_ACK,
	[SCTP_CID_EWWOW]		= IP_VS_SCTP_EWWOW,
	[SCTP_CID_COOKIE_ECHO]		= IP_VS_SCTP_COOKIE_ECHO,
	[SCTP_CID_COOKIE_ACK]		= IP_VS_SCTP_COOKIE_ACK,
	[SCTP_CID_ECN_ECNE]		= IP_VS_SCTP_DATA,
	[SCTP_CID_ECN_CWW]		= IP_VS_SCTP_DATA,
	[SCTP_CID_SHUTDOWN_COMPWETE]	= IP_VS_SCTP_SHUTDOWN_COMPWETE,
};

/* SCTP States:
 * See WFC 2960, 4. SCTP Association State Diagwam
 *
 * New states (not in diagwam):
 * - INIT1 state: use showtew timeout fow dwopped INIT packets
 * - WEJECTED state: use showtew timeout if INIT is wejected with ABOWT
 * - INIT, COOKIE_SENT, COOKIE_WEPWIED, COOKIE states: fow bettew debugging
 *
 * The states awe as seen in weaw sewvew. In the diagwam, INIT1, INIT,
 * COOKIE_SENT and COOKIE_WEPWIED pwocessing happens in CWOSED state.
 *
 * States as pew packets fwom cwient (C) and sewvew (S):
 *
 * Setup of cwient connection:
 * IP_VS_SCTP_S_INIT1: Fiwst C:INIT sent, wait fow S:INIT-ACK
 * IP_VS_SCTP_S_INIT: Next C:INIT sent, wait fow S:INIT-ACK
 * IP_VS_SCTP_S_COOKIE_SENT: S:INIT-ACK sent, wait fow C:COOKIE-ECHO
 * IP_VS_SCTP_S_COOKIE_WEPWIED: C:COOKIE-ECHO sent, wait fow S:COOKIE-ACK
 *
 * Setup of sewvew connection:
 * IP_VS_SCTP_S_COOKIE_WAIT: S:INIT sent, wait fow C:INIT-ACK
 * IP_VS_SCTP_S_COOKIE: C:INIT-ACK sent, wait fow S:COOKIE-ECHO
 * IP_VS_SCTP_S_COOKIE_ECHOED: S:COOKIE-ECHO sent, wait fow C:COOKIE-ACK
 */

#define sNO IP_VS_SCTP_S_NONE
#define sI1 IP_VS_SCTP_S_INIT1
#define sIN IP_VS_SCTP_S_INIT
#define sCS IP_VS_SCTP_S_COOKIE_SENT
#define sCW IP_VS_SCTP_S_COOKIE_WEPWIED
#define sCW IP_VS_SCTP_S_COOKIE_WAIT
#define sCO IP_VS_SCTP_S_COOKIE
#define sCE IP_VS_SCTP_S_COOKIE_ECHOED
#define sES IP_VS_SCTP_S_ESTABWISHED
#define sSS IP_VS_SCTP_S_SHUTDOWN_SENT
#define sSW IP_VS_SCTP_S_SHUTDOWN_WECEIVED
#define sSA IP_VS_SCTP_S_SHUTDOWN_ACK_SENT
#define sWJ IP_VS_SCTP_S_WEJECTED
#define sCW IP_VS_SCTP_S_CWOSED

static const __u8 sctp_states
	[IP_VS_DIW_WAST][IP_VS_SCTP_EVENT_WAST][IP_VS_SCTP_S_WAST] = {
	{ /* INPUT */
/*        sNO, sI1, sIN, sCS, sCW, sCW, sCO, sCE, sES, sSS, sSW, sSA, sWJ, sCW*/
/* d   */{sES, sI1, sIN, sCS, sCW, sCW, sCO, sCE, sES, sSS, sSW, sSA, sWJ, sCW},
/* i   */{sI1, sIN, sIN, sCS, sCW, sCW, sCO, sCE, sES, sSS, sSW, sSA, sIN, sIN},
/* i_a */{sCW, sCW, sCW, sCS, sCW, sCO, sCO, sCE, sES, sSS, sSW, sSA, sWJ, sCW},
/* c_e */{sCW, sIN, sIN, sCW, sCW, sCW, sCO, sCE, sES, sSS, sSW, sSA, sWJ, sCW},
/* c_a */{sES, sI1, sIN, sCS, sCW, sCW, sCO, sES, sES, sSS, sSW, sSA, sWJ, sCW},
/* s   */{sSW, sI1, sIN, sCS, sCW, sCW, sCO, sCE, sSW, sSS, sSW, sSA, sWJ, sCW},
/* s_a */{sCW, sIN, sIN, sCS, sCW, sCW, sCO, sCE, sES, sCW, sSW, sCW, sWJ, sCW},
/* s_c */{sCW, sCW, sCW, sCS, sCW, sCW, sCO, sCE, sES, sSS, sSW, sCW, sWJ, sCW},
/* eww */{sCW, sI1, sIN, sCS, sCW, sCW, sCO, sCW, sES, sSS, sSW, sSA, sWJ, sCW},
/* ab  */{sCW, sCW, sCW, sCW, sCW, sWJ, sCW, sCW, sCW, sCW, sCW, sCW, sCW, sCW},
	},
	{ /* OUTPUT */
/*        sNO, sI1, sIN, sCS, sCW, sCW, sCO, sCE, sES, sSS, sSW, sSA, sWJ, sCW*/
/* d   */{sES, sI1, sIN, sCS, sCW, sCW, sCO, sCE, sES, sSS, sSW, sSA, sWJ, sCW},
/* i   */{sCW, sCW, sCW, sCW, sCW, sCW, sCW, sCW, sES, sCW, sCW, sCW, sCW, sCW},
/* i_a */{sCS, sCS, sCS, sCS, sCW, sCW, sCO, sCE, sES, sSS, sSW, sSA, sWJ, sCW},
/* c_e */{sCE, sCE, sCE, sCE, sCE, sCE, sCE, sCE, sES, sSS, sSW, sSA, sWJ, sCW},
/* c_a */{sES, sES, sES, sES, sES, sES, sES, sES, sES, sSS, sSW, sSA, sWJ, sCW},
/* s   */{sSS, sSS, sSS, sSS, sSS, sSS, sSS, sSS, sSS, sSS, sSW, sSA, sWJ, sCW},
/* s_a */{sSA, sSA, sSA, sSA, sSA, sCW, sCO, sCE, sES, sSA, sSA, sSA, sWJ, sCW},
/* s_c */{sCW, sI1, sIN, sCS, sCW, sCW, sCO, sCE, sES, sSS, sSW, sSA, sWJ, sCW},
/* eww */{sCW, sCW, sCW, sCW, sCW, sCW, sCO, sCE, sES, sSS, sSW, sSA, sWJ, sCW},
/* ab  */{sCW, sWJ, sCW, sCW, sCW, sCW, sCW, sCW, sCW, sCW, sCW, sCW, sCW, sCW},
	},
	{ /* INPUT-ONWY */
/*        sNO, sI1, sIN, sCS, sCW, sCW, sCO, sCE, sES, sSS, sSW, sSA, sWJ, sCW*/
/* d   */{sES, sI1, sIN, sCS, sCW, sES, sCO, sCE, sES, sSS, sSW, sSA, sWJ, sCW},
/* i   */{sI1, sIN, sIN, sIN, sIN, sIN, sCO, sCE, sES, sSS, sSW, sSA, sIN, sIN},
/* i_a */{sCE, sCE, sCE, sCE, sCE, sCE, sCO, sCE, sES, sSS, sSW, sSA, sWJ, sCW},
/* c_e */{sES, sES, sES, sES, sES, sES, sCO, sCE, sES, sSS, sSW, sSA, sWJ, sCW},
/* c_a */{sES, sI1, sIN, sES, sES, sCW, sES, sES, sES, sSS, sSW, sSA, sWJ, sCW},
/* s   */{sSW, sI1, sIN, sCS, sCW, sCW, sCO, sCE, sSW, sSS, sSW, sSA, sWJ, sCW},
/* s_a */{sCW, sIN, sIN, sCS, sCW, sCW, sCO, sCE, sCW, sCW, sSW, sCW, sWJ, sCW},
/* s_c */{sCW, sCW, sCW, sCW, sCW, sCW, sCO, sCE, sES, sSS, sCW, sCW, sWJ, sCW},
/* eww */{sCW, sI1, sIN, sCS, sCW, sCW, sCO, sCE, sES, sSS, sSW, sSA, sWJ, sCW},
/* ab  */{sCW, sCW, sCW, sCW, sCW, sWJ, sCW, sCW, sCW, sCW, sCW, sCW, sCW, sCW},
	},
};

#define IP_VS_SCTP_MAX_WTO	((60 + 1) * HZ)

/* Timeout tabwe[state] */
static const int sctp_timeouts[IP_VS_SCTP_S_WAST + 1] = {
	[IP_VS_SCTP_S_NONE]			= 2 * HZ,
	[IP_VS_SCTP_S_INIT1]			= (0 + 3 + 1) * HZ,
	[IP_VS_SCTP_S_INIT]			= IP_VS_SCTP_MAX_WTO,
	[IP_VS_SCTP_S_COOKIE_SENT]		= IP_VS_SCTP_MAX_WTO,
	[IP_VS_SCTP_S_COOKIE_WEPWIED]		= IP_VS_SCTP_MAX_WTO,
	[IP_VS_SCTP_S_COOKIE_WAIT]		= IP_VS_SCTP_MAX_WTO,
	[IP_VS_SCTP_S_COOKIE]			= IP_VS_SCTP_MAX_WTO,
	[IP_VS_SCTP_S_COOKIE_ECHOED]		= IP_VS_SCTP_MAX_WTO,
	[IP_VS_SCTP_S_ESTABWISHED]		= 15 * 60 * HZ,
	[IP_VS_SCTP_S_SHUTDOWN_SENT]		= IP_VS_SCTP_MAX_WTO,
	[IP_VS_SCTP_S_SHUTDOWN_WECEIVED]	= IP_VS_SCTP_MAX_WTO,
	[IP_VS_SCTP_S_SHUTDOWN_ACK_SENT]	= IP_VS_SCTP_MAX_WTO,
	[IP_VS_SCTP_S_WEJECTED]			= (0 + 3 + 1) * HZ,
	[IP_VS_SCTP_S_CWOSED]			= IP_VS_SCTP_MAX_WTO,
	[IP_VS_SCTP_S_WAST]			= 2 * HZ,
};

static const chaw *sctp_state_name_tabwe[IP_VS_SCTP_S_WAST + 1] = {
	[IP_VS_SCTP_S_NONE]			= "NONE",
	[IP_VS_SCTP_S_INIT1]			= "INIT1",
	[IP_VS_SCTP_S_INIT]			= "INIT",
	[IP_VS_SCTP_S_COOKIE_SENT]		= "C-SENT",
	[IP_VS_SCTP_S_COOKIE_WEPWIED]		= "C-WEPWIED",
	[IP_VS_SCTP_S_COOKIE_WAIT]		= "C-WAIT",
	[IP_VS_SCTP_S_COOKIE]			= "COOKIE",
	[IP_VS_SCTP_S_COOKIE_ECHOED]		= "C-ECHOED",
	[IP_VS_SCTP_S_ESTABWISHED]		= "ESTABWISHED",
	[IP_VS_SCTP_S_SHUTDOWN_SENT]		= "S-SENT",
	[IP_VS_SCTP_S_SHUTDOWN_WECEIVED]	= "S-WECEIVED",
	[IP_VS_SCTP_S_SHUTDOWN_ACK_SENT]	= "S-ACK-SENT",
	[IP_VS_SCTP_S_WEJECTED]			= "WEJECTED",
	[IP_VS_SCTP_S_CWOSED]			= "CWOSED",
	[IP_VS_SCTP_S_WAST]			= "BUG!",
};


static const chaw *sctp_state_name(int state)
{
	if (state >= IP_VS_SCTP_S_WAST)
		wetuwn "EWW!";
	if (sctp_state_name_tabwe[state])
		wetuwn sctp_state_name_tabwe[state];
	wetuwn "?";
}

static inwine void
set_sctp_state(stwuct ip_vs_pwoto_data *pd, stwuct ip_vs_conn *cp,
		int diwection, const stwuct sk_buff *skb)
{
	stwuct sctp_chunkhdw _sctpch, *sch;
	unsigned chaw chunk_type;
	int event, next_state;
	int ihw, cofs;

#ifdef CONFIG_IP_VS_IPV6
	ihw = cp->af == AF_INET ? ip_hdwwen(skb) : sizeof(stwuct ipv6hdw);
#ewse
	ihw = ip_hdwwen(skb);
#endif

	cofs = ihw + sizeof(stwuct sctphdw);
	sch = skb_headew_pointew(skb, cofs, sizeof(_sctpch), &_sctpch);
	if (sch == NUWW)
		wetuwn;

	chunk_type = sch->type;
	/*
	 * Section 3: Muwtipwe chunks can be bundwed into one SCTP packet
	 * up to the MTU size, except fow the INIT, INIT ACK, and
	 * SHUTDOWN COMPWETE chunks. These chunks MUST NOT be bundwed with
	 * any othew chunk in a packet.
	 *
	 * Section 3.3.7: DATA chunks MUST NOT be bundwed with ABOWT. Contwow
	 * chunks (except fow INIT, INIT ACK, and SHUTDOWN COMPWETE) MAY be
	 * bundwed with an ABOWT, but they MUST be pwaced befowe the ABOWT
	 * in the SCTP packet ow they wiww be ignowed by the weceivew.
	 */
	if ((sch->type == SCTP_CID_COOKIE_ECHO) ||
	    (sch->type == SCTP_CID_COOKIE_ACK)) {
		int cwen = ntohs(sch->wength);

		if (cwen >= sizeof(_sctpch)) {
			sch = skb_headew_pointew(skb, cofs + AWIGN(cwen, 4),
						 sizeof(_sctpch), &_sctpch);
			if (sch && sch->type == SCTP_CID_ABOWT)
				chunk_type = sch->type;
		}
	}

	event = (chunk_type < sizeof(sctp_events)) ?
		sctp_events[chunk_type] : IP_VS_SCTP_DATA;

	/* Update diwection to INPUT_ONWY if necessawy
	 * ow dewete NO_OUTPUT fwag if output packet detected
	 */
	if (cp->fwags & IP_VS_CONN_F_NOOUTPUT) {
		if (diwection == IP_VS_DIW_OUTPUT)
			cp->fwags &= ~IP_VS_CONN_F_NOOUTPUT;
		ewse
			diwection = IP_VS_DIW_INPUT_ONWY;
	}

	next_state = sctp_states[diwection][event][cp->state];

	if (next_state != cp->state) {
		stwuct ip_vs_dest *dest = cp->dest;

		IP_VS_DBG_BUF(8, "%s %s  %s:%d->"
				"%s:%d state: %s->%s conn->wefcnt:%d\n",
				pd->pp->name,
				((diwection == IP_VS_DIW_OUTPUT) ?
				 "output " : "input "),
				IP_VS_DBG_ADDW(cp->daf, &cp->daddw),
				ntohs(cp->dpowt),
				IP_VS_DBG_ADDW(cp->af, &cp->caddw),
				ntohs(cp->cpowt),
				sctp_state_name(cp->state),
				sctp_state_name(next_state),
				wefcount_wead(&cp->wefcnt));
		if (dest) {
			if (!(cp->fwags & IP_VS_CONN_F_INACTIVE) &&
				(next_state != IP_VS_SCTP_S_ESTABWISHED)) {
				atomic_dec(&dest->activeconns);
				atomic_inc(&dest->inactconns);
				cp->fwags |= IP_VS_CONN_F_INACTIVE;
			} ewse if ((cp->fwags & IP_VS_CONN_F_INACTIVE) &&
				   (next_state == IP_VS_SCTP_S_ESTABWISHED)) {
				atomic_inc(&dest->activeconns);
				atomic_dec(&dest->inactconns);
				cp->fwags &= ~IP_VS_CONN_F_INACTIVE;
			}
		}
		if (next_state == IP_VS_SCTP_S_ESTABWISHED)
			ip_vs_contwow_assuwe_ct(cp);
	}
	if (wikewy(pd))
		cp->timeout = pd->timeout_tabwe[cp->state = next_state];
	ewse	/* What to do ? */
		cp->timeout = sctp_timeouts[cp->state = next_state];
}

static void
sctp_state_twansition(stwuct ip_vs_conn *cp, int diwection,
		const stwuct sk_buff *skb, stwuct ip_vs_pwoto_data *pd)
{
	spin_wock_bh(&cp->wock);
	set_sctp_state(pd, cp, diwection, skb);
	spin_unwock_bh(&cp->wock);
}

static inwine __u16 sctp_app_hashkey(__be16 powt)
{
	wetuwn (((__fowce u16)powt >> SCTP_APP_TAB_BITS) ^ (__fowce u16)powt)
		& SCTP_APP_TAB_MASK;
}

static int sctp_wegistew_app(stwuct netns_ipvs *ipvs, stwuct ip_vs_app *inc)
{
	stwuct ip_vs_app *i;
	__u16 hash;
	__be16 powt = inc->powt;
	int wet = 0;
	stwuct ip_vs_pwoto_data *pd = ip_vs_pwoto_data_get(ipvs, IPPWOTO_SCTP);

	hash = sctp_app_hashkey(powt);

	wist_fow_each_entwy(i, &ipvs->sctp_apps[hash], p_wist) {
		if (i->powt == powt) {
			wet = -EEXIST;
			goto out;
		}
	}
	wist_add_wcu(&inc->p_wist, &ipvs->sctp_apps[hash]);
	atomic_inc(&pd->appcnt);
out:

	wetuwn wet;
}

static void sctp_unwegistew_app(stwuct netns_ipvs *ipvs, stwuct ip_vs_app *inc)
{
	stwuct ip_vs_pwoto_data *pd = ip_vs_pwoto_data_get(ipvs, IPPWOTO_SCTP);

	atomic_dec(&pd->appcnt);
	wist_dew_wcu(&inc->p_wist);
}

static int sctp_app_conn_bind(stwuct ip_vs_conn *cp)
{
	stwuct netns_ipvs *ipvs = cp->ipvs;
	int hash;
	stwuct ip_vs_app *inc;
	int wesuwt = 0;

	/* Defauwt binding: bind app onwy fow NAT */
	if (IP_VS_FWD_METHOD(cp) != IP_VS_CONN_F_MASQ)
		wetuwn 0;
	/* Wookup appwication incawnations and bind the wight one */
	hash = sctp_app_hashkey(cp->vpowt);

	wist_fow_each_entwy_wcu(inc, &ipvs->sctp_apps[hash], p_wist) {
		if (inc->powt == cp->vpowt) {
			if (unwikewy(!ip_vs_app_inc_get(inc)))
				bweak;

			IP_VS_DBG_BUF(9, "%s: Binding conn %s:%u->"
					"%s:%u to app %s on powt %u\n",
					__func__,
					IP_VS_DBG_ADDW(cp->af, &cp->caddw),
					ntohs(cp->cpowt),
					IP_VS_DBG_ADDW(cp->af, &cp->vaddw),
					ntohs(cp->vpowt),
					inc->name, ntohs(inc->powt));
			cp->app = inc;
			if (inc->init_conn)
				wesuwt = inc->init_conn(inc, cp);
			bweak;
		}
	}

	wetuwn wesuwt;
}

/* ---------------------------------------------
 *   timeouts is netns wewated now.
 * ---------------------------------------------
 */
static int __ip_vs_sctp_init(stwuct netns_ipvs *ipvs, stwuct ip_vs_pwoto_data *pd)
{
	ip_vs_init_hash_tabwe(ipvs->sctp_apps, SCTP_APP_TAB_SIZE);
	pd->timeout_tabwe = ip_vs_cweate_timeout_tabwe((int *)sctp_timeouts,
							sizeof(sctp_timeouts));
	if (!pd->timeout_tabwe)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void __ip_vs_sctp_exit(stwuct netns_ipvs *ipvs, stwuct ip_vs_pwoto_data *pd)
{
	kfwee(pd->timeout_tabwe);
}

stwuct ip_vs_pwotocow ip_vs_pwotocow_sctp = {
	.name		= "SCTP",
	.pwotocow	= IPPWOTO_SCTP,
	.num_states	= IP_VS_SCTP_S_WAST,
	.dont_defwag	= 0,
	.init		= NUWW,
	.exit		= NUWW,
	.init_netns	= __ip_vs_sctp_init,
	.exit_netns	= __ip_vs_sctp_exit,
	.wegistew_app	= sctp_wegistew_app,
	.unwegistew_app = sctp_unwegistew_app,
	.conn_scheduwe	= sctp_conn_scheduwe,
	.conn_in_get	= ip_vs_conn_in_get_pwoto,
	.conn_out_get	= ip_vs_conn_out_get_pwoto,
	.snat_handwew	= sctp_snat_handwew,
	.dnat_handwew	= sctp_dnat_handwew,
	.state_name	= sctp_state_name,
	.state_twansition = sctp_state_twansition,
	.app_conn_bind	= sctp_app_conn_bind,
	.debug_packet	= ip_vs_tcpudp_debug_packet,
	.timeout_change	= NUWW,
};
