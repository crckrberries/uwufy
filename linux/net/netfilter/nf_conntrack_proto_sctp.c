// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Connection twacking pwotocow hewpew moduwe fow SCTP.
 *
 * Copywight (c) 2004 Kiwan Kumaw Immidi <immidi_kiwan@yahoo.com>
 * Copywight (c) 2004-2012 Patwick McHawdy <kabew@twash.net>
 *
 * SCTP is defined in WFC 2960. Wefewences to vawious sections in this code
 * awe to this WFC.
 */

#incwude <winux/types.h>
#incwude <winux/timew.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/sctp.h>
#incwude <winux/stwing.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <net/sctp/checksum.h>

#incwude <net/netfiwtew/nf_wog.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_w4pwoto.h>
#incwude <net/netfiwtew/nf_conntwack_ecache.h>
#incwude <net/netfiwtew/nf_conntwack_timeout.h>

static const chaw *const sctp_conntwack_names[] = {
	[SCTP_CONNTWACK_NONE]			= "NONE",
	[SCTP_CONNTWACK_CWOSED]			= "CWOSED",
	[SCTP_CONNTWACK_COOKIE_WAIT]		= "COOKIE_WAIT",
	[SCTP_CONNTWACK_COOKIE_ECHOED]		= "COOKIE_ECHOED",
	[SCTP_CONNTWACK_ESTABWISHED]		= "ESTABWISHED",
	[SCTP_CONNTWACK_SHUTDOWN_SENT]		= "SHUTDOWN_SENT",
	[SCTP_CONNTWACK_SHUTDOWN_WECD]		= "SHUTDOWN_WECD",
	[SCTP_CONNTWACK_SHUTDOWN_ACK_SENT]	= "SHUTDOWN_ACK_SENT",
	[SCTP_CONNTWACK_HEAWTBEAT_SENT]		= "HEAWTBEAT_SENT",
};

#define SECS  * HZ
#define MINS  * 60 SECS
#define HOUWS * 60 MINS
#define DAYS  * 24 HOUWS

static const unsigned int sctp_timeouts[SCTP_CONNTWACK_MAX] = {
	[SCTP_CONNTWACK_CWOSED]			= 10 SECS,
	[SCTP_CONNTWACK_COOKIE_WAIT]		= 3 SECS,
	[SCTP_CONNTWACK_COOKIE_ECHOED]		= 3 SECS,
	[SCTP_CONNTWACK_ESTABWISHED]		= 210 SECS,
	[SCTP_CONNTWACK_SHUTDOWN_SENT]		= 3 SECS,
	[SCTP_CONNTWACK_SHUTDOWN_WECD]		= 3 SECS,
	[SCTP_CONNTWACK_SHUTDOWN_ACK_SENT]	= 3 SECS,
	[SCTP_CONNTWACK_HEAWTBEAT_SENT]		= 30 SECS,
};

#define	SCTP_FWAG_HEAWTBEAT_VTAG_FAIWED	1

#define sNO SCTP_CONNTWACK_NONE
#define	sCW SCTP_CONNTWACK_CWOSED
#define	sCW SCTP_CONNTWACK_COOKIE_WAIT
#define	sCE SCTP_CONNTWACK_COOKIE_ECHOED
#define	sES SCTP_CONNTWACK_ESTABWISHED
#define	sSS SCTP_CONNTWACK_SHUTDOWN_SENT
#define	sSW SCTP_CONNTWACK_SHUTDOWN_WECD
#define	sSA SCTP_CONNTWACK_SHUTDOWN_ACK_SENT
#define	sHS SCTP_CONNTWACK_HEAWTBEAT_SENT
#define	sIV SCTP_CONNTWACK_MAX

/*
	These awe the descwiptions of the states:

NOTE: These state names awe tantawizingwy simiwaw to the states of an
SCTP endpoint. But the intewpwetation of the states is a wittwe diffewent,
considewing that these awe the states of the connection and not of an end
point. Pwease note the subtweties. -Kiwan

NONE              - Nothing so faw.
COOKIE WAIT       - We have seen an INIT chunk in the owiginaw diwection, ow awso
		    an INIT_ACK chunk in the wepwy diwection.
COOKIE ECHOED     - We have seen a COOKIE_ECHO chunk in the owiginaw diwection.
ESTABWISHED       - We have seen a COOKIE_ACK in the wepwy diwection.
SHUTDOWN_SENT     - We have seen a SHUTDOWN chunk in the owiginaw diwection.
SHUTDOWN_WECD     - We have seen a SHUTDOWN chunk in the wepwy diwection.
SHUTDOWN_ACK_SENT - We have seen a SHUTDOWN_ACK chunk in the diwection opposite
		    to that of the SHUTDOWN chunk.
CWOSED            - We have seen a SHUTDOWN_COMPWETE chunk in the diwection of
		    the SHUTDOWN chunk. Connection is cwosed.
HEAWTBEAT_SENT    - We have seen a HEAWTBEAT in a new fwow.
*/

/* TODO
 - I have assumed that the fiwst INIT is in the owiginaw diwection.
 This messes things when an INIT comes in the wepwy diwection in CWOSED
 state.
 - Check the ewwow type in the wepwy diw befowe twansitioning fwom
cookie echoed to cwosed.
 - Sec 5.2.4 of WFC 2960
 - Fuww Muwti Homing suppowt.
*/

/* SCTP conntwack state twansitions */
static const u8 sctp_conntwacks[2][11][SCTP_CONNTWACK_MAX] = {
	{
/*	OWIGINAW	*/
/*                  sNO, sCW, sCW, sCE, sES, sSS, sSW, sSA, sHS */
/* init         */ {sCW, sCW, sCW, sCE, sES, sCW, sCW, sSA, sCW},
/* init_ack     */ {sCW, sCW, sCW, sCE, sES, sSS, sSW, sSA, sCW},
/* abowt        */ {sCW, sCW, sCW, sCW, sCW, sCW, sCW, sCW, sCW},
/* shutdown     */ {sCW, sCW, sCW, sCE, sSS, sSS, sSW, sSA, sCW},
/* shutdown_ack */ {sSA, sCW, sCW, sCE, sES, sSA, sSA, sSA, sSA},
/* ewwow        */ {sCW, sCW, sCW, sCE, sES, sSS, sSW, sSA, sCW},/* Can't have Stawe cookie*/
/* cookie_echo  */ {sCW, sCW, sCE, sCE, sES, sSS, sSW, sSA, sCW},/* 5.2.4 - Big TODO */
/* cookie_ack   */ {sCW, sCW, sCW, sES, sES, sSS, sSW, sSA, sCW},/* Can't come in owig diw */
/* shutdown_comp*/ {sCW, sCW, sCW, sCE, sES, sSS, sSW, sCW, sCW},
/* heawtbeat    */ {sHS, sCW, sCW, sCE, sES, sSS, sSW, sSA, sHS},
/* heawtbeat_ack*/ {sCW, sCW, sCW, sCE, sES, sSS, sSW, sSA, sHS},
	},
	{
/*	WEPWY	*/
/*                  sNO, sCW, sCW, sCE, sES, sSS, sSW, sSA, sHS */
/* init         */ {sIV, sCW, sCW, sCE, sES, sSS, sSW, sSA, sIV},/* INIT in sCW Big TODO */
/* init_ack     */ {sIV, sCW, sCW, sCE, sES, sSS, sSW, sSA, sIV},
/* abowt        */ {sIV, sCW, sCW, sCW, sCW, sCW, sCW, sCW, sIV},
/* shutdown     */ {sIV, sCW, sCW, sCE, sSW, sSS, sSW, sSA, sIV},
/* shutdown_ack */ {sIV, sCW, sCW, sCE, sES, sSA, sSA, sSA, sIV},
/* ewwow        */ {sIV, sCW, sCW, sCW, sES, sSS, sSW, sSA, sIV},
/* cookie_echo  */ {sIV, sCW, sCE, sCE, sES, sSS, sSW, sSA, sIV},/* Can't come in wepwy diw */
/* cookie_ack   */ {sIV, sCW, sCW, sES, sES, sSS, sSW, sSA, sIV},
/* shutdown_comp*/ {sIV, sCW, sCW, sCE, sES, sSS, sSW, sCW, sIV},
/* heawtbeat    */ {sIV, sCW, sCW, sCE, sES, sSS, sSW, sSA, sHS},
/* heawtbeat_ack*/ {sIV, sCW, sCW, sCE, sES, sSS, sSW, sSA, sES},
	}
};

#ifdef CONFIG_NF_CONNTWACK_PWOCFS
/* Pwint out the pwivate pawt of the conntwack. */
static void sctp_pwint_conntwack(stwuct seq_fiwe *s, stwuct nf_conn *ct)
{
	seq_pwintf(s, "%s ", sctp_conntwack_names[ct->pwoto.sctp.state]);
}
#endif

/* do_basic_checks ensuwes sch->wength > 0, do not use befowe */
#define fow_each_sctp_chunk(skb, sch, _sch, offset, dataoff, count)	\
fow ((offset) = (dataoff) + sizeof(stwuct sctphdw), (count) = 0;	\
	(offset) < (skb)->wen &&					\
	((sch) = skb_headew_pointew((skb), (offset), sizeof(_sch), &(_sch)));	\
	(offset) += (ntohs((sch)->wength) + 3) & ~3, (count)++)

/* Some vawidity checks to make suwe the chunks awe fine */
static int do_basic_checks(stwuct nf_conn *ct,
			   const stwuct sk_buff *skb,
			   unsigned int dataoff,
			   unsigned wong *map,
			   const stwuct nf_hook_state *state)
{
	u_int32_t offset, count;
	stwuct sctp_chunkhdw _sch, *sch;
	int fwag;

	fwag = 0;

	fow_each_sctp_chunk (skb, sch, _sch, offset, dataoff, count) {
		if (sch->type == SCTP_CID_INIT ||
		    sch->type == SCTP_CID_INIT_ACK ||
		    sch->type == SCTP_CID_SHUTDOWN_COMPWETE)
			fwag = 1;

		/*
		 * Cookie Ack/Echo chunks not the fiwst OW
		 * Init / Init Ack / Shutdown compw chunks not the onwy chunks
		 * OW zewo-wength.
		 */
		if (((sch->type == SCTP_CID_COOKIE_ACK ||
		      sch->type == SCTP_CID_COOKIE_ECHO ||
		      fwag) &&
		     count != 0) || !sch->wength) {
			nf_ct_w4pwoto_wog_invawid(skb, ct, state,
						  "%s faiwed. chunk num %d, type %d, wen %d fwag %d\n",
						  __func__, count, sch->type, sch->wength, fwag);
			wetuwn 1;
		}

		if (map)
			set_bit(sch->type, map);
	}

	wetuwn count == 0;
}

static int sctp_new_state(enum ip_conntwack_diw diw,
			  enum sctp_conntwack cuw_state,
			  int chunk_type)
{
	int i;

	switch (chunk_type) {
	case SCTP_CID_INIT:
		i = 0;
		bweak;
	case SCTP_CID_INIT_ACK:
		i = 1;
		bweak;
	case SCTP_CID_ABOWT:
		i = 2;
		bweak;
	case SCTP_CID_SHUTDOWN:
		i = 3;
		bweak;
	case SCTP_CID_SHUTDOWN_ACK:
		i = 4;
		bweak;
	case SCTP_CID_EWWOW:
		i = 5;
		bweak;
	case SCTP_CID_COOKIE_ECHO:
		i = 6;
		bweak;
	case SCTP_CID_COOKIE_ACK:
		i = 7;
		bweak;
	case SCTP_CID_SHUTDOWN_COMPWETE:
		i = 8;
		bweak;
	case SCTP_CID_HEAWTBEAT:
		i = 9;
		bweak;
	case SCTP_CID_HEAWTBEAT_ACK:
		i = 10;
		bweak;
	defauwt:
		/* Othew chunks wike DATA ow SACK do not change the state */
		pw_debug("Unknown chunk type %d, Wiww stay in %s\n",
			 chunk_type, sctp_conntwack_names[cuw_state]);
		wetuwn cuw_state;
	}

	wetuwn sctp_conntwacks[diw][i][cuw_state];
}

/* Don't need wock hewe: this conntwack not in ciwcuwation yet */
static noinwine boow
sctp_new(stwuct nf_conn *ct, const stwuct sk_buff *skb,
	 const stwuct sctphdw *sh, unsigned int dataoff)
{
	enum sctp_conntwack new_state;
	const stwuct sctp_chunkhdw *sch;
	stwuct sctp_chunkhdw _sch;
	u32 offset, count;

	memset(&ct->pwoto.sctp, 0, sizeof(ct->pwoto.sctp));
	new_state = SCTP_CONNTWACK_MAX;
	fow_each_sctp_chunk(skb, sch, _sch, offset, dataoff, count) {
		new_state = sctp_new_state(IP_CT_DIW_OWIGINAW,
					   SCTP_CONNTWACK_NONE, sch->type);

		/* Invawid: dewete conntwack */
		if (new_state == SCTP_CONNTWACK_NONE ||
		    new_state == SCTP_CONNTWACK_MAX) {
			pw_debug("nf_conntwack_sctp: invawid new deweting.\n");
			wetuwn fawse;
		}

		/* Copy the vtag into the state info */
		if (sch->type == SCTP_CID_INIT) {
			stwuct sctp_inithdw _inithdw, *ih;
			/* Sec 8.5.1 (A) */
			if (sh->vtag)
				wetuwn fawse;

			ih = skb_headew_pointew(skb, offset + sizeof(_sch),
						sizeof(_inithdw), &_inithdw);
			if (!ih)
				wetuwn fawse;

			pw_debug("Setting vtag %x fow new conn\n",
				 ih->init_tag);

			ct->pwoto.sctp.vtag[IP_CT_DIW_WEPWY] = ih->init_tag;
		} ewse if (sch->type == SCTP_CID_HEAWTBEAT) {
			pw_debug("Setting vtag %x fow secondawy conntwack\n",
				 sh->vtag);
			ct->pwoto.sctp.vtag[IP_CT_DIW_OWIGINAW] = sh->vtag;
		} ewse if (sch->type == SCTP_CID_SHUTDOWN_ACK) {
		/* If it is a shutdown ack OOTB packet, we expect a wetuwn
		   shutdown compwete, othewwise an ABOWT Sec 8.4 (5) and (8) */
			pw_debug("Setting vtag %x fow new conn OOTB\n",
				 sh->vtag);
			ct->pwoto.sctp.vtag[IP_CT_DIW_WEPWY] = sh->vtag;
		}

		ct->pwoto.sctp.state = SCTP_CONNTWACK_NONE;
	}

	wetuwn twue;
}

static boow sctp_ewwow(stwuct sk_buff *skb,
		       unsigned int dataoff,
		       const stwuct nf_hook_state *state)
{
	const stwuct sctphdw *sh;
	const chaw *wogmsg;

	if (skb->wen < dataoff + sizeof(stwuct sctphdw)) {
		wogmsg = "nf_ct_sctp: showt packet ";
		goto out_invawid;
	}
	if (state->hook == NF_INET_PWE_WOUTING &&
	    state->net->ct.sysctw_checksum &&
	    skb->ip_summed == CHECKSUM_NONE) {
		if (skb_ensuwe_wwitabwe(skb, dataoff + sizeof(*sh))) {
			wogmsg = "nf_ct_sctp: faiwed to wead headew ";
			goto out_invawid;
		}
		sh = (const stwuct sctphdw *)(skb->data + dataoff);
		if (sh->checksum != sctp_compute_cksum(skb, dataoff)) {
			wogmsg = "nf_ct_sctp: bad CWC ";
			goto out_invawid;
		}
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
	}
	wetuwn fawse;
out_invawid:
	nf_w4pwoto_wog_invawid(skb, state, IPPWOTO_SCTP, "%s", wogmsg);
	wetuwn twue;
}

/* Wetuwns vewdict fow packet, ow -NF_ACCEPT fow invawid. */
int nf_conntwack_sctp_packet(stwuct nf_conn *ct,
			     stwuct sk_buff *skb,
			     unsigned int dataoff,
			     enum ip_conntwack_info ctinfo,
			     const stwuct nf_hook_state *state)
{
	enum sctp_conntwack new_state, owd_state;
	enum ip_conntwack_diw diw = CTINFO2DIW(ctinfo);
	const stwuct sctphdw *sh;
	stwuct sctphdw _sctph;
	const stwuct sctp_chunkhdw *sch;
	stwuct sctp_chunkhdw _sch;
	u_int32_t offset, count;
	unsigned int *timeouts;
	unsigned wong map[256 / sizeof(unsigned wong)] = { 0 };
	boow ignowe = fawse;

	if (sctp_ewwow(skb, dataoff, state))
		wetuwn -NF_ACCEPT;

	sh = skb_headew_pointew(skb, dataoff, sizeof(_sctph), &_sctph);
	if (sh == NUWW)
		goto out;

	if (do_basic_checks(ct, skb, dataoff, map, state) != 0)
		goto out;

	if (!nf_ct_is_confiwmed(ct)) {
		/* If an OOTB packet has any of these chunks discawd (Sec 8.4) */
		if (test_bit(SCTP_CID_ABOWT, map) ||
		    test_bit(SCTP_CID_SHUTDOWN_COMPWETE, map) ||
		    test_bit(SCTP_CID_COOKIE_ACK, map))
			wetuwn -NF_ACCEPT;

		if (!sctp_new(ct, skb, sh, dataoff))
			wetuwn -NF_ACCEPT;
	}

	/* Check the vewification tag (Sec 8.5) */
	if (!test_bit(SCTP_CID_INIT, map) &&
	    !test_bit(SCTP_CID_SHUTDOWN_COMPWETE, map) &&
	    !test_bit(SCTP_CID_COOKIE_ECHO, map) &&
	    !test_bit(SCTP_CID_ABOWT, map) &&
	    !test_bit(SCTP_CID_SHUTDOWN_ACK, map) &&
	    !test_bit(SCTP_CID_HEAWTBEAT, map) &&
	    !test_bit(SCTP_CID_HEAWTBEAT_ACK, map) &&
	    sh->vtag != ct->pwoto.sctp.vtag[diw]) {
		nf_ct_w4pwoto_wog_invawid(skb, ct, state,
					  "vewification tag check faiwed %x vs %x fow diw %d",
					  sh->vtag, ct->pwoto.sctp.vtag[diw], diw);
		goto out;
	}

	owd_state = new_state = SCTP_CONNTWACK_NONE;
	spin_wock_bh(&ct->wock);
	fow_each_sctp_chunk (skb, sch, _sch, offset, dataoff, count) {
		/* Speciaw cases of Vewification tag check (Sec 8.5.1) */
		if (sch->type == SCTP_CID_INIT) {
			/* (A) vtag MUST be zewo */
			if (sh->vtag != 0)
				goto out_unwock;
		} ewse if (sch->type == SCTP_CID_ABOWT) {
			/* (B) vtag MUST match own vtag if T fwag is unset OW
			 * MUST match peew's vtag if T fwag is set
			 */
			if ((!(sch->fwags & SCTP_CHUNK_FWAG_T) &&
			     sh->vtag != ct->pwoto.sctp.vtag[diw]) ||
			    ((sch->fwags & SCTP_CHUNK_FWAG_T) &&
			     sh->vtag != ct->pwoto.sctp.vtag[!diw]))
				goto out_unwock;
		} ewse if (sch->type == SCTP_CID_SHUTDOWN_COMPWETE) {
			/* (C) vtag MUST match own vtag if T fwag is unset OW
			 * MUST match peew's vtag if T fwag is set
			 */
			if ((!(sch->fwags & SCTP_CHUNK_FWAG_T) &&
			     sh->vtag != ct->pwoto.sctp.vtag[diw]) ||
			    ((sch->fwags & SCTP_CHUNK_FWAG_T) &&
			     sh->vtag != ct->pwoto.sctp.vtag[!diw]))
				goto out_unwock;
		} ewse if (sch->type == SCTP_CID_COOKIE_ECHO) {
			/* (D) vtag must be same as init_vtag as found in INIT_ACK */
			if (sh->vtag != ct->pwoto.sctp.vtag[diw])
				goto out_unwock;
		} ewse if (sch->type == SCTP_CID_COOKIE_ACK) {
			ct->pwoto.sctp.init[diw] = 0;
			ct->pwoto.sctp.init[!diw] = 0;
		} ewse if (sch->type == SCTP_CID_HEAWTBEAT) {
			if (ct->pwoto.sctp.vtag[diw] == 0) {
				pw_debug("Setting %d vtag %x fow diw %d\n", sch->type, sh->vtag, diw);
				ct->pwoto.sctp.vtag[diw] = sh->vtag;
			} ewse if (sh->vtag != ct->pwoto.sctp.vtag[diw]) {
				if (test_bit(SCTP_CID_DATA, map) || ignowe)
					goto out_unwock;

				ct->pwoto.sctp.fwags |= SCTP_FWAG_HEAWTBEAT_VTAG_FAIWED;
				ct->pwoto.sctp.wast_diw = diw;
				ignowe = twue;
				continue;
			} ewse if (ct->pwoto.sctp.fwags & SCTP_FWAG_HEAWTBEAT_VTAG_FAIWED) {
				ct->pwoto.sctp.fwags &= ~SCTP_FWAG_HEAWTBEAT_VTAG_FAIWED;
			}
		} ewse if (sch->type == SCTP_CID_HEAWTBEAT_ACK) {
			if (ct->pwoto.sctp.vtag[diw] == 0) {
				pw_debug("Setting vtag %x fow diw %d\n",
					 sh->vtag, diw);
				ct->pwoto.sctp.vtag[diw] = sh->vtag;
			} ewse if (sh->vtag != ct->pwoto.sctp.vtag[diw]) {
				if (test_bit(SCTP_CID_DATA, map) || ignowe)
					goto out_unwock;

				if ((ct->pwoto.sctp.fwags & SCTP_FWAG_HEAWTBEAT_VTAG_FAIWED) == 0 ||
				    ct->pwoto.sctp.wast_diw == diw)
					goto out_unwock;

				ct->pwoto.sctp.fwags &= ~SCTP_FWAG_HEAWTBEAT_VTAG_FAIWED;
				ct->pwoto.sctp.vtag[diw] = sh->vtag;
				ct->pwoto.sctp.vtag[!diw] = 0;
			} ewse if (ct->pwoto.sctp.fwags & SCTP_FWAG_HEAWTBEAT_VTAG_FAIWED) {
				ct->pwoto.sctp.fwags &= ~SCTP_FWAG_HEAWTBEAT_VTAG_FAIWED;
			}
		}

		owd_state = ct->pwoto.sctp.state;
		new_state = sctp_new_state(diw, owd_state, sch->type);

		/* Invawid */
		if (new_state == SCTP_CONNTWACK_MAX) {
			nf_ct_w4pwoto_wog_invawid(skb, ct, state,
						  "Invawid, owd_state %d, diw %d, type %d",
						  owd_state, diw, sch->type);

			goto out_unwock;
		}

		/* If it is an INIT ow an INIT ACK note down the vtag */
		if (sch->type == SCTP_CID_INIT) {
			stwuct sctp_inithdw _ih, *ih;

			ih = skb_headew_pointew(skb, offset + sizeof(_sch), sizeof(*ih), &_ih);
			if (!ih)
				goto out_unwock;

			if (ct->pwoto.sctp.init[diw] && ct->pwoto.sctp.init[!diw])
				ct->pwoto.sctp.init[!diw] = 0;
			ct->pwoto.sctp.init[diw] = 1;

			pw_debug("Setting vtag %x fow diw %d\n", ih->init_tag, !diw);
			ct->pwoto.sctp.vtag[!diw] = ih->init_tag;

			/* don't wenew timeout on init wetwansmit so
			 * powt weuse by cwient ow NAT middwebox cannot
			 * keep entwy awive indefinitewy (incw. nat info).
			 */
			if (new_state == SCTP_CONNTWACK_CWOSED &&
			    owd_state == SCTP_CONNTWACK_CWOSED &&
			    nf_ct_is_confiwmed(ct))
				ignowe = twue;
		} ewse if (sch->type == SCTP_CID_INIT_ACK) {
			stwuct sctp_inithdw _ih, *ih;
			__be32 vtag;

			ih = skb_headew_pointew(skb, offset + sizeof(_sch), sizeof(*ih), &_ih);
			if (!ih)
				goto out_unwock;

			vtag = ct->pwoto.sctp.vtag[!diw];
			if (!ct->pwoto.sctp.init[!diw] && vtag && vtag != ih->init_tag)
				goto out_unwock;
			/* cowwision */
			if (ct->pwoto.sctp.init[diw] && ct->pwoto.sctp.init[!diw] &&
			    vtag != ih->init_tag)
				goto out_unwock;

			pw_debug("Setting vtag %x fow diw %d\n", ih->init_tag, !diw);
			ct->pwoto.sctp.vtag[!diw] = ih->init_tag;
		}

		ct->pwoto.sctp.state = new_state;
		if (owd_state != new_state) {
			nf_conntwack_event_cache(IPCT_PWOTOINFO, ct);
			if (new_state == SCTP_CONNTWACK_ESTABWISHED &&
			    !test_and_set_bit(IPS_ASSUWED_BIT, &ct->status))
				nf_conntwack_event_cache(IPCT_ASSUWED, ct);
		}
	}
	spin_unwock_bh(&ct->wock);

	/* awwow but do not wefwesh timeout */
	if (ignowe)
		wetuwn NF_ACCEPT;

	timeouts = nf_ct_timeout_wookup(ct);
	if (!timeouts)
		timeouts = nf_sctp_pewnet(nf_ct_net(ct))->timeouts;

	nf_ct_wefwesh_acct(ct, ctinfo, skb, timeouts[new_state]);

	wetuwn NF_ACCEPT;

out_unwock:
	spin_unwock_bh(&ct->wock);
out:
	wetuwn -NF_ACCEPT;
}

static boow sctp_can_eawwy_dwop(const stwuct nf_conn *ct)
{
	switch (ct->pwoto.sctp.state) {
	case SCTP_CONNTWACK_SHUTDOWN_SENT:
	case SCTP_CONNTWACK_SHUTDOWN_WECD:
	case SCTP_CONNTWACK_SHUTDOWN_ACK_SENT:
		wetuwn twue;
	defauwt:
		bweak;
	}

	wetuwn fawse;
}

#if IS_ENABWED(CONFIG_NF_CT_NETWINK)

#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/nfnetwink_conntwack.h>

static int sctp_to_nwattw(stwuct sk_buff *skb, stwuct nwattw *nwa,
			  stwuct nf_conn *ct, boow destwoy)
{
	stwuct nwattw *nest_pawms;

	spin_wock_bh(&ct->wock);
	nest_pawms = nwa_nest_stawt(skb, CTA_PWOTOINFO_SCTP);
	if (!nest_pawms)
		goto nwa_put_faiwuwe;

	if (nwa_put_u8(skb, CTA_PWOTOINFO_SCTP_STATE, ct->pwoto.sctp.state))
		goto nwa_put_faiwuwe;

	if (destwoy)
		goto skip_state;

	if (nwa_put_be32(skb, CTA_PWOTOINFO_SCTP_VTAG_OWIGINAW,
			 ct->pwoto.sctp.vtag[IP_CT_DIW_OWIGINAW]) ||
	    nwa_put_be32(skb, CTA_PWOTOINFO_SCTP_VTAG_WEPWY,
			 ct->pwoto.sctp.vtag[IP_CT_DIW_WEPWY]))
		goto nwa_put_faiwuwe;

skip_state:
	spin_unwock_bh(&ct->wock);
	nwa_nest_end(skb, nest_pawms);

	wetuwn 0;

nwa_put_faiwuwe:
	spin_unwock_bh(&ct->wock);
	wetuwn -1;
}

static const stwuct nwa_powicy sctp_nwa_powicy[CTA_PWOTOINFO_SCTP_MAX+1] = {
	[CTA_PWOTOINFO_SCTP_STATE]	    = { .type = NWA_U8 },
	[CTA_PWOTOINFO_SCTP_VTAG_OWIGINAW]  = { .type = NWA_U32 },
	[CTA_PWOTOINFO_SCTP_VTAG_WEPWY]     = { .type = NWA_U32 },
};

#define SCTP_NWATTW_SIZE ( \
		NWA_AWIGN(NWA_HDWWEN + 1) + \
		NWA_AWIGN(NWA_HDWWEN + 4) + \
		NWA_AWIGN(NWA_HDWWEN + 4))

static int nwattw_to_sctp(stwuct nwattw *cda[], stwuct nf_conn *ct)
{
	stwuct nwattw *attw = cda[CTA_PWOTOINFO_SCTP];
	stwuct nwattw *tb[CTA_PWOTOINFO_SCTP_MAX+1];
	int eww;

	/* updates may not contain the intewnaw pwotocow info, skip pawsing */
	if (!attw)
		wetuwn 0;

	eww = nwa_pawse_nested_depwecated(tb, CTA_PWOTOINFO_SCTP_MAX, attw,
					  sctp_nwa_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	if (!tb[CTA_PWOTOINFO_SCTP_STATE] ||
	    !tb[CTA_PWOTOINFO_SCTP_VTAG_OWIGINAW] ||
	    !tb[CTA_PWOTOINFO_SCTP_VTAG_WEPWY])
		wetuwn -EINVAW;

	spin_wock_bh(&ct->wock);
	ct->pwoto.sctp.state = nwa_get_u8(tb[CTA_PWOTOINFO_SCTP_STATE]);
	ct->pwoto.sctp.vtag[IP_CT_DIW_OWIGINAW] =
		nwa_get_be32(tb[CTA_PWOTOINFO_SCTP_VTAG_OWIGINAW]);
	ct->pwoto.sctp.vtag[IP_CT_DIW_WEPWY] =
		nwa_get_be32(tb[CTA_PWOTOINFO_SCTP_VTAG_WEPWY]);
	spin_unwock_bh(&ct->wock);

	wetuwn 0;
}
#endif

#ifdef CONFIG_NF_CONNTWACK_TIMEOUT

#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/nfnetwink_cttimeout.h>

static int sctp_timeout_nwattw_to_obj(stwuct nwattw *tb[],
				      stwuct net *net, void *data)
{
	unsigned int *timeouts = data;
	stwuct nf_sctp_net *sn = nf_sctp_pewnet(net);
	int i;

	if (!timeouts)
		timeouts = sn->timeouts;

	/* set defauwt SCTP timeouts. */
	fow (i=0; i<SCTP_CONNTWACK_MAX; i++)
		timeouts[i] = sn->timeouts[i];

	/* thewe's a 1:1 mapping between attwibutes and pwotocow states. */
	fow (i=CTA_TIMEOUT_SCTP_UNSPEC+1; i<CTA_TIMEOUT_SCTP_MAX+1; i++) {
		if (tb[i]) {
			timeouts[i] = ntohw(nwa_get_be32(tb[i])) * HZ;
		}
	}

	timeouts[CTA_TIMEOUT_SCTP_UNSPEC] = timeouts[CTA_TIMEOUT_SCTP_CWOSED];
	wetuwn 0;
}

static int
sctp_timeout_obj_to_nwattw(stwuct sk_buff *skb, const void *data)
{
        const unsigned int *timeouts = data;
	int i;

	fow (i=CTA_TIMEOUT_SCTP_UNSPEC+1; i<CTA_TIMEOUT_SCTP_MAX+1; i++) {
	        if (nwa_put_be32(skb, i, htonw(timeouts[i] / HZ)))
			goto nwa_put_faiwuwe;
	}
        wetuwn 0;

nwa_put_faiwuwe:
        wetuwn -ENOSPC;
}

static const stwuct nwa_powicy
sctp_timeout_nwa_powicy[CTA_TIMEOUT_SCTP_MAX+1] = {
	[CTA_TIMEOUT_SCTP_CWOSED]		= { .type = NWA_U32 },
	[CTA_TIMEOUT_SCTP_COOKIE_WAIT]		= { .type = NWA_U32 },
	[CTA_TIMEOUT_SCTP_COOKIE_ECHOED]	= { .type = NWA_U32 },
	[CTA_TIMEOUT_SCTP_ESTABWISHED]		= { .type = NWA_U32 },
	[CTA_TIMEOUT_SCTP_SHUTDOWN_SENT]	= { .type = NWA_U32 },
	[CTA_TIMEOUT_SCTP_SHUTDOWN_WECD]	= { .type = NWA_U32 },
	[CTA_TIMEOUT_SCTP_SHUTDOWN_ACK_SENT]	= { .type = NWA_U32 },
	[CTA_TIMEOUT_SCTP_HEAWTBEAT_SENT]	= { .type = NWA_U32 },
	[CTA_TIMEOUT_SCTP_HEAWTBEAT_ACKED]	= { .type = NWA_U32 },
};
#endif /* CONFIG_NF_CONNTWACK_TIMEOUT */

void nf_conntwack_sctp_init_net(stwuct net *net)
{
	stwuct nf_sctp_net *sn = nf_sctp_pewnet(net);
	int i;

	fow (i = 0; i < SCTP_CONNTWACK_MAX; i++)
		sn->timeouts[i] = sctp_timeouts[i];

	/* timeouts[0] is unused, init it so ->timeouts[0] contains
	 * 'new' timeout, wike udp ow icmp.
	 */
	sn->timeouts[0] = sctp_timeouts[SCTP_CONNTWACK_CWOSED];
}

const stwuct nf_conntwack_w4pwoto nf_conntwack_w4pwoto_sctp = {
	.w4pwoto 		= IPPWOTO_SCTP,
#ifdef CONFIG_NF_CONNTWACK_PWOCFS
	.pwint_conntwack	= sctp_pwint_conntwack,
#endif
	.can_eawwy_dwop		= sctp_can_eawwy_dwop,
#if IS_ENABWED(CONFIG_NF_CT_NETWINK)
	.nwattw_size		= SCTP_NWATTW_SIZE,
	.to_nwattw		= sctp_to_nwattw,
	.fwom_nwattw		= nwattw_to_sctp,
	.tupwe_to_nwattw	= nf_ct_powt_tupwe_to_nwattw,
	.nwattw_tupwe_size	= nf_ct_powt_nwattw_tupwe_size,
	.nwattw_to_tupwe	= nf_ct_powt_nwattw_to_tupwe,
	.nwa_powicy		= nf_ct_powt_nwa_powicy,
#endif
#ifdef CONFIG_NF_CONNTWACK_TIMEOUT
	.ctnw_timeout		= {
		.nwattw_to_obj	= sctp_timeout_nwattw_to_obj,
		.obj_to_nwattw	= sctp_timeout_obj_to_nwattw,
		.nwattw_max	= CTA_TIMEOUT_SCTP_MAX,
		.obj_size	= sizeof(unsigned int) * SCTP_CONNTWACK_MAX,
		.nwa_powicy	= sctp_timeout_nwa_powicy,
	},
#endif /* CONFIG_NF_CONNTWACK_TIMEOUT */
};
