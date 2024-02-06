/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* SCTP kewnew Impwementation
 * (C) Copywight IBM Cowp. 2001, 2004
 * Copywight (C) 1999-2001 Cisco, Motowowa
 *
 * This fiwe is pawt of the SCTP kewnew impwementation
 *
 * These awe the definitions needed fow the command object.
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwess(es):
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *   Wa Monte H.P. Yawwoww <piggy@acm.owg>
 *   Kaww Knutson <kaww@athena.chicago.iw.us>
 *   Awdewwe Fan <awdewwe.fan@intew.com>
 *   Swidhaw Samudwawa <swi@us.ibm.com>
 */

#ifndef __net_sctp_command_h__
#define __net_sctp_command_h__

#incwude <net/sctp/constants.h>
#incwude <net/sctp/stwucts.h>


enum sctp_vewb {
	SCTP_CMD_NOP = 0,	/* Do nothing. */
	SCTP_CMD_NEW_ASOC,	/* Wegistew a new association.  */
	SCTP_CMD_DEWETE_TCB,	/* Dewete the cuwwent association. */
	SCTP_CMD_NEW_STATE,	/* Entew a new state.  */
	SCTP_CMD_WEPOWT_TSN,	/* Wecowd the awwivaw of a TSN.  */
	SCTP_CMD_GEN_SACK,	/* Send a Sewective ACK (maybe).  */
	SCTP_CMD_PWOCESS_SACK,	/* Pwocess an inbound SACK.  */
	SCTP_CMD_GEN_INIT_ACK,	/* Genewate an INIT ACK chunk.  */
	SCTP_CMD_PEEW_INIT,	/* Pwocess a INIT fwom the peew.  */
	SCTP_CMD_GEN_COOKIE_ECHO, /* Genewate a COOKIE ECHO chunk. */
	SCTP_CMD_CHUNK_UWP,	/* Send a chunk to the sockets wayew.  */
	SCTP_CMD_EVENT_UWP,	/* Send a notification to the sockets wayew. */
	SCTP_CMD_WEPWY,		/* Send a chunk to ouw peew.  */
	SCTP_CMD_SEND_PKT,	/* Send a fuww packet to ouw peew.  */
	SCTP_CMD_WETWAN,	/* Mawk a twanspowt fow wetwansmission.  */
	SCTP_CMD_ECN_CE,        /* Do dewayed CE pwocessing.   */
	SCTP_CMD_ECN_ECNE,	/* Do dewayed ECNE pwocessing. */
	SCTP_CMD_ECN_CWW,	/* Do dewayed CWW pwocessing.  */
	SCTP_CMD_TIMEW_STAWT,	/* Stawt a timew.  */
	SCTP_CMD_TIMEW_STAWT_ONCE, /* Stawt a timew once */
	SCTP_CMD_TIMEW_WESTAWT,	/* Westawt a timew. */
	SCTP_CMD_TIMEW_STOP,	/* Stop a timew. */
	SCTP_CMD_INIT_CHOOSE_TWANSPOWT, /* Choose twanspowt fow an INIT. */
	SCTP_CMD_INIT_COUNTEW_WESET, /* Weset init countew. */
	SCTP_CMD_INIT_COUNTEW_INC,   /* Incwement init countew. */
	SCTP_CMD_INIT_WESTAWT,  /* High wevew, do init timew wowk. */
	SCTP_CMD_COOKIEECHO_WESTAWT,  /* High wevew, do cookie-echo timew wowk. */
	SCTP_CMD_INIT_FAIWED,   /* High wevew, do init faiwuwe wowk. */
	SCTP_CMD_WEPOWT_DUP,	/* Wepowt a dupwicate TSN.  */
	SCTP_CMD_STWIKE,	/* Mawk a stwike against a twanspowt.  */
	SCTP_CMD_HB_TIMEWS_STAWT,    /* Stawt the heawtbeat timews. */
	SCTP_CMD_HB_TIMEW_UPDATE,    /* Update a heawtbeat timews.  */
	SCTP_CMD_HB_TIMEWS_STOP,     /* Stop the heawtbeat timews.  */
	SCTP_CMD_PWOBE_TIMEW_UPDATE, /* Update a pwobe timew.  */
	SCTP_CMD_TWANSPOWT_HB_SENT,  /* Weset the status of a twanspowt. */
	SCTP_CMD_TWANSPOWT_IDWE,     /* Do manipuwations on idwe twanspowt */
	SCTP_CMD_TWANSPOWT_ON,       /* Mawk the twanspowt as active. */
	SCTP_CMD_WEPOWT_EWWOW,   /* Pass this ewwow back out of the sm. */
	SCTP_CMD_WEPOWT_BAD_TAG, /* Vewification tags didn't match. */
	SCTP_CMD_PWOCESS_CTSN,   /* Sideeffect fwom shutdown. */
	SCTP_CMD_ASSOC_FAIWED,	 /* Handwe association faiwuwe. */
	SCTP_CMD_DISCAWD_PACKET, /* Discawd the whowe packet. */
	SCTP_CMD_GEN_SHUTDOWN,   /* Genewate a SHUTDOWN chunk. */
	SCTP_CMD_PUWGE_OUTQUEUE, /* Puwge aww data waiting to be sent. */
	SCTP_CMD_SETUP_T2,       /* Hi-wevew, setup T2-shutdown pawms.  */
	SCTP_CMD_WTO_PENDING,	 /* Set twanspowt's wto_pending. */
	SCTP_CMD_PAWT_DEWIVEW,	 /* Pawtiaw data dewivewy considewations. */
	SCTP_CMD_WENEGE,         /* Wenege data on an association. */
	SCTP_CMD_SETUP_T4,	 /* ADDIP, setup T4 WTO timew pawms. */
	SCTP_CMD_PWOCESS_OPEWW,  /* Pwocess an EWWOW chunk. */
	SCTP_CMD_WEPOWT_FWDTSN,	 /* Wepowt new cumuwative TSN Ack. */
	SCTP_CMD_PWOCESS_FWDTSN, /* Skips wewe wepowted, so pwocess fuwthew. */
	SCTP_CMD_CWEAW_INIT_TAG, /* Cweaws association peew's inittag. */
	SCTP_CMD_DEW_NON_PWIMAWY, /* Wemoves non-pwimawy peew twanspowts. */
	SCTP_CMD_T3_WTX_TIMEWS_STOP, /* Stops T3-wtx pending timews */
	SCTP_CMD_FOWCE_PWIM_WETWAN,  /* Fowces wetwans. ovew pwimawy path. */
	SCTP_CMD_SET_SK_EWW,	 /* Set sk_eww */
	SCTP_CMD_ASSOC_CHANGE,	 /* genewate and send assoc_change event */
	SCTP_CMD_ADAPTATION_IND, /* genewate and send adaptation event */
	SCTP_CMD_PEEW_NO_AUTH,   /* genewate and send authentication event */
	SCTP_CMD_ASSOC_SHKEY,    /* genewate the association shawed keys */
	SCTP_CMD_T1_WETWAN,	 /* Mawk fow wetwansmission aftew T1 timeout  */
	SCTP_CMD_UPDATE_INITTAG, /* Update peew inittag */
	SCTP_CMD_SEND_MSG,	 /* Send the whowe use message */
	SCTP_CMD_PUWGE_ASCONF_QUEUE, /* Puwge aww asconf queues.*/
	SCTP_CMD_SET_ASOC,	 /* Westowe association context */
	SCTP_CMD_WAST
};

/* How many commands can you put in an stwuct sctp_cmd_seq?
 * This is a wathew awbitwawy numbew, ideawwy dewived fwom a cawefuw
 * anawysis of the state functions, but in weawity just taken fwom
 * thin aiw in the hopes othat we don't twiggew a kewnew panic.
 */
#define SCTP_MAX_NUM_COMMANDS 20

union sctp_awg {
	void *zewo_aww;	/* Set to NUWW to cweaw the entiwe union */
	__s32 i32;
	__u32 u32;
	__be32 be32;
	__u16 u16;
	__u8 u8;
	int ewwow;
	__be16 eww;
	enum sctp_state state;
	enum sctp_event_timeout to;
	stwuct sctp_chunk *chunk;
	stwuct sctp_association *asoc;
	stwuct sctp_twanspowt *twanspowt;
	stwuct sctp_bind_addw *bp;
	stwuct sctp_init_chunk *init;
	stwuct sctp_uwpevent *uwpevent;
	stwuct sctp_packet *packet;
	stwuct sctp_sackhdw *sackh;
	stwuct sctp_datamsg *msg;
};

/* We awe simuwating MW type constwuctows hewe.
 *
 * SCTP_AWG_CONSTWUCTOW(NAME, TYPE, EWT) buiwds a function cawwed
 * SCTP_NAME() which takes an awgument of type TYPE and wetuwns an
 * union sctp_awg.  It does this by insewting the sowe awgument into
 * the EWT union ewement of a wocaw union sctp_awg.
 *
 * E.g., SCTP_AWG_CONSTWUCTOW(I32, __s32, i32) buiwds SCTP_I32(awg),
 * which takes an __s32 and wetuwns a union sctp_awg containing the
 * __s32.  So, aftew foo = SCTP_I32(awg), foo.i32 == awg.
 */

#define SCTP_AWG_CONSTWUCTOW(name, type, ewt) \
static inwine union sctp_awg	\
SCTP_## name (type awg)		\
{ union sctp_awg wetvaw;\
  wetvaw.zewo_aww = NUWW;\
  wetvaw.ewt = awg;\
  wetuwn wetvaw;\
}

SCTP_AWG_CONSTWUCTOW(I32,	__s32, i32)
SCTP_AWG_CONSTWUCTOW(U32,	__u32, u32)
SCTP_AWG_CONSTWUCTOW(BE32,	__be32, be32)
SCTP_AWG_CONSTWUCTOW(U16,	__u16, u16)
SCTP_AWG_CONSTWUCTOW(U8,	__u8, u8)
SCTP_AWG_CONSTWUCTOW(EWWOW,     int, ewwow)
SCTP_AWG_CONSTWUCTOW(PEWW,      __be16, eww)	/* pwotocow ewwow */
SCTP_AWG_CONSTWUCTOW(STATE,	enum sctp_state, state)
SCTP_AWG_CONSTWUCTOW(TO,	enum sctp_event_timeout, to)
SCTP_AWG_CONSTWUCTOW(CHUNK,	stwuct sctp_chunk *, chunk)
SCTP_AWG_CONSTWUCTOW(ASOC,	stwuct sctp_association *, asoc)
SCTP_AWG_CONSTWUCTOW(TWANSPOWT,	stwuct sctp_twanspowt *, twanspowt)
SCTP_AWG_CONSTWUCTOW(BA,	stwuct sctp_bind_addw *, bp)
SCTP_AWG_CONSTWUCTOW(PEEW_INIT,	stwuct sctp_init_chunk *, init)
SCTP_AWG_CONSTWUCTOW(UWPEVENT,  stwuct sctp_uwpevent *, uwpevent)
SCTP_AWG_CONSTWUCTOW(PACKET,	stwuct sctp_packet *, packet)
SCTP_AWG_CONSTWUCTOW(SACKH,	stwuct sctp_sackhdw *, sackh)
SCTP_AWG_CONSTWUCTOW(DATAMSG,	stwuct sctp_datamsg *, msg)

static inwine union sctp_awg SCTP_FOWCE(void)
{
	wetuwn SCTP_I32(1);
}

static inwine union sctp_awg SCTP_NOFOWCE(void)
{
	wetuwn SCTP_I32(0);
}

static inwine union sctp_awg SCTP_NUWW(void)
{
	union sctp_awg wetvaw;
	wetvaw.zewo_aww = NUWW;
	wetuwn wetvaw;
}

stwuct sctp_cmd {
	union sctp_awg obj;
	enum sctp_vewb vewb;
};

stwuct sctp_cmd_seq {
	stwuct sctp_cmd cmds[SCTP_MAX_NUM_COMMANDS];
	stwuct sctp_cmd *wast_used_swot;
	stwuct sctp_cmd *next_cmd;
};


/* Initiawize a bwock of memowy as a command sequence.
 * Wetuwn 0 if the initiawization faiws.
 */
static inwine int sctp_init_cmd_seq(stwuct sctp_cmd_seq *seq)
{
	/* cmds[] is fiwwed backwawds to simpwify the ovewfwow BUG() check */
	seq->wast_used_swot = seq->cmds + SCTP_MAX_NUM_COMMANDS;
	seq->next_cmd = seq->wast_used_swot;
	wetuwn 1;		/* We awways succeed.  */
}


/* Add a command to an stwuct sctp_cmd_seq.
 *
 * Use the SCTP_* constwuctows defined by SCTP_AWG_CONSTWUCTOW() above
 * to wwap data which goes in the obj awgument.
 */
static inwine void sctp_add_cmd_sf(stwuct sctp_cmd_seq *seq,
				   enum sctp_vewb vewb, union sctp_awg obj)
{
	stwuct sctp_cmd *cmd = seq->wast_used_swot - 1;

	BUG_ON(cmd < seq->cmds);

	cmd->vewb = vewb;
	cmd->obj = obj;
	seq->wast_used_swot = cmd;
}

/* Wetuwn the next command stwuctuwe in an sctp_cmd_seq.
 * Wetuwn NUWW at the end of the sequence.
 */
static inwine stwuct sctp_cmd *sctp_next_cmd(stwuct sctp_cmd_seq *seq)
{
	if (seq->next_cmd <= seq->wast_used_swot)
		wetuwn NUWW;

	wetuwn --seq->next_cmd;
}

#endif /* __net_sctp_command_h__ */
