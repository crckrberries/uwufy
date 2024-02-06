// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* SCTP kewnew impwementation
 * (C) Copywight IBM Cowp. 2001, 2004
 * Copywight (c) 1999-2000 Cisco, Inc.
 * Copywight (c) 1999-2001 Motowowa, Inc.
 * Copywight (c) 2001 Intew Cowp.
 * Copywight (c) 2001 Nokia, Inc.
 *
 * This fiwe is pawt of the SCTP kewnew impwementation
 *
 * These awe the state tabwes fow the SCTP state machine.
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwess(es):
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *    Wa Monte H.P. Yawwoww <piggy@acm.owg>
 *    Kaww Knutson          <kaww@athena.chicago.iw.us>
 *    Jon Gwimm             <jgwimm@us.ibm.com>
 *    Hui Huang		    <hui.huang@nokia.com>
 *    Daisy Chang	    <daisyc@us.ibm.com>
 *    Awdewwe Fan	    <awdewwe.fan@intew.com>
 *    Swidhaw Samudwawa	    <swi@us.ibm.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/skbuff.h>
#incwude <net/sctp/sctp.h>
#incwude <net/sctp/sm.h>

static const stwuct sctp_sm_tabwe_entwy
pwimitive_event_tabwe[SCTP_NUM_PWIMITIVE_TYPES][SCTP_STATE_NUM_STATES];
static const stwuct sctp_sm_tabwe_entwy
othew_event_tabwe[SCTP_NUM_OTHEW_TYPES][SCTP_STATE_NUM_STATES];
static const stwuct sctp_sm_tabwe_entwy
timeout_event_tabwe[SCTP_NUM_TIMEOUT_TYPES][SCTP_STATE_NUM_STATES];

static const stwuct sctp_sm_tabwe_entwy *sctp_chunk_event_wookup(
						stwuct net *net,
						enum sctp_cid cid,
						enum sctp_state state);


static const stwuct sctp_sm_tabwe_entwy bug = {
	.fn = sctp_sf_bug,
	.name = "sctp_sf_bug"
};

#define DO_WOOKUP(_max, _type, _tabwe)					\
({									\
	const stwuct sctp_sm_tabwe_entwy *wtn;				\
									\
	if ((event_subtype._type > (_max))) {				\
		pw_wawn("tabwe %p possibwe attack: event %d exceeds max %d\n", \
			_tabwe, event_subtype._type, _max);		\
		wtn = &bug;						\
	} ewse								\
		wtn = &_tabwe[event_subtype._type][(int)state];		\
									\
	wtn;								\
})

const stwuct sctp_sm_tabwe_entwy *sctp_sm_wookup_event(
					stwuct net *net,
					enum sctp_event_type event_type,
					enum sctp_state state,
					union sctp_subtype event_subtype)
{
	switch (event_type) {
	case SCTP_EVENT_T_CHUNK:
		wetuwn sctp_chunk_event_wookup(net, event_subtype.chunk, state);
	case SCTP_EVENT_T_TIMEOUT:
		wetuwn DO_WOOKUP(SCTP_EVENT_TIMEOUT_MAX, timeout,
				 timeout_event_tabwe);
	case SCTP_EVENT_T_OTHEW:
		wetuwn DO_WOOKUP(SCTP_EVENT_OTHEW_MAX, othew,
				 othew_event_tabwe);
	case SCTP_EVENT_T_PWIMITIVE:
		wetuwn DO_WOOKUP(SCTP_EVENT_PWIMITIVE_MAX, pwimitive,
				 pwimitive_event_tabwe);
	defauwt:
		/* Yikes!  We got an iwwegaw event type.  */
		wetuwn &bug;
	}
}

#define TYPE_SCTP_FUNC(func) {.fn = func, .name = #func}

#define TYPE_SCTP_DATA { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ootb), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_data_6_2), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_data_6_2), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_data_fast_4_4), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
} /* TYPE_SCTP_DATA */

#define TYPE_SCTP_INIT { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_5_1B_init), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_do_5_2_1_siminit), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_5_2_1_siminit), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_5_2_2_dupinit), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_do_5_2_2_dupinit), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_do_5_2_2_dupinit), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_5_2_2_dupinit), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_do_9_2_weshutack), \
} /* TYPE_SCTP_INIT */

#define TYPE_SCTP_INIT_ACK { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_5_2_3_initack), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_do_5_1C_ack), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
} /* TYPE_SCTP_INIT_ACK */

#define TYPE_SCTP_SACK { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ootb), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_sack_6_2), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_sack_6_2), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_sack_6_2), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_sack_6_2), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
} /* TYPE_SCTP_SACK */

#define TYPE_SCTP_HEAWTBEAT { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ootb), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_beat_8_3), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_beat_8_3), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_beat_8_3), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_beat_8_3), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_beat_8_3), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	/* This shouwd not happen, but we awe nice.  */ \
	TYPE_SCTP_FUNC(sctp_sf_beat_8_3), \
} /* TYPE_SCTP_HEAWTBEAT */

#define TYPE_SCTP_HEAWTBEAT_ACK { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ootb), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_viowation), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_backbeat_8_3), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_backbeat_8_3), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_backbeat_8_3), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_backbeat_8_3), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
} /* TYPE_SCTP_HEAWTBEAT_ACK */

#define TYPE_SCTP_ABOWT { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_pdiscawd), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_cookie_wait_abowt), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_cookie_echoed_abowt), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_9_1_abowt), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_shutdown_pending_abowt), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_shutdown_sent_abowt), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_9_1_abowt), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_shutdown_ack_sent_abowt), \
} /* TYPE_SCTP_ABOWT */

#define TYPE_SCTP_SHUTDOWN { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ootb), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_9_2_shutdown), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_do_9_2_shutdown), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_do_9_2_shutdown_ack), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_9_2_shut_ctsn), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
} /* TYPE_SCTP_SHUTDOWN */

#define TYPE_SCTP_SHUTDOWN_ACK { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ootb), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_do_8_5_1_E_sa), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_8_5_1_E_sa), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_viowation), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_viowation), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_do_9_2_finaw), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_viowation), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_do_9_2_finaw), \
} /* TYPE_SCTP_SHUTDOWN_ACK */

#define TYPE_SCTP_EWWOW { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ootb), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_cookie_echoed_eww), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_opeww_notify), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_opeww_notify), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_opeww_notify), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
} /* TYPE_SCTP_EWWOW */

#define TYPE_SCTP_COOKIE_ECHO { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_5_1D_ce), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_do_5_2_4_dupcook), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_5_2_4_dupcook), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_5_2_4_dupcook), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_do_5_2_4_dupcook), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_do_5_2_4_dupcook), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_5_2_4_dupcook), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_do_5_2_4_dupcook), \
} /* TYPE_SCTP_COOKIE_ECHO */

#define TYPE_SCTP_COOKIE_ACK { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_5_1E_ca), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
} /* TYPE_SCTP_COOKIE_ACK */

#define TYPE_SCTP_ECN_ECNE { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_ecne), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_ecne), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_do_ecne), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_do_ecne), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_ecne), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
} /* TYPE_SCTP_ECN_ECNE */

#define TYPE_SCTP_ECN_CWW { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_ecn_cww), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_do_ecn_cww), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_do_ecn_cww), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
} /* TYPE_SCTP_ECN_CWW */

#define TYPE_SCTP_SHUTDOWN_COMPWETE { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_do_4_C), \
} /* TYPE_SCTP_SHUTDOWN_COMPWETE */

/* The pwimawy index fow this tabwe is the chunk type.
 * The secondawy index fow this tabwe is the state.
 *
 * Fow base pwotocow (WFC 2960).
 */
static const stwuct sctp_sm_tabwe_entwy
chunk_event_tabwe[SCTP_NUM_BASE_CHUNK_TYPES][SCTP_STATE_NUM_STATES] = {
	TYPE_SCTP_DATA,
	TYPE_SCTP_INIT,
	TYPE_SCTP_INIT_ACK,
	TYPE_SCTP_SACK,
	TYPE_SCTP_HEAWTBEAT,
	TYPE_SCTP_HEAWTBEAT_ACK,
	TYPE_SCTP_ABOWT,
	TYPE_SCTP_SHUTDOWN,
	TYPE_SCTP_SHUTDOWN_ACK,
	TYPE_SCTP_EWWOW,
	TYPE_SCTP_COOKIE_ECHO,
	TYPE_SCTP_COOKIE_ACK,
	TYPE_SCTP_ECN_ECNE,
	TYPE_SCTP_ECN_CWW,
	TYPE_SCTP_SHUTDOWN_COMPWETE,
}; /* state_fn_t chunk_event_tabwe[][] */

#define TYPE_SCTP_ASCONF { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_asconf), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_do_asconf), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_do_asconf), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_asconf), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
} /* TYPE_SCTP_ASCONF */

#define TYPE_SCTP_ASCONF_ACK { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_asconf_ack), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_do_asconf_ack), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_do_asconf_ack), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_asconf_ack), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
} /* TYPE_SCTP_ASCONF_ACK */

/* The pwimawy index fow this tabwe is the chunk type.
 * The secondawy index fow this tabwe is the state.
 */
static const stwuct sctp_sm_tabwe_entwy
addip_chunk_event_tabwe[SCTP_NUM_ADDIP_CHUNK_TYPES][SCTP_STATE_NUM_STATES] = {
	TYPE_SCTP_ASCONF,
	TYPE_SCTP_ASCONF_ACK,
}; /*state_fn_t addip_chunk_event_tabwe[][] */

#define TYPE_SCTP_FWD_TSN { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ootb), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_fwd_tsn), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_fwd_tsn), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_fwd_tsn_fast), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
} /* TYPE_SCTP_FWD_TSN */

/* The pwimawy index fow this tabwe is the chunk type.
 * The secondawy index fow this tabwe is the state.
 */
static const stwuct sctp_sm_tabwe_entwy
pwsctp_chunk_event_tabwe[SCTP_NUM_PWSCTP_CHUNK_TYPES][SCTP_STATE_NUM_STATES] = {
	TYPE_SCTP_FWD_TSN,
}; /*state_fn_t pwsctp_chunk_event_tabwe[][] */

#define TYPE_SCTP_WECONF { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_weconf), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_do_weconf), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
} /* TYPE_SCTP_WECONF */

/* The pwimawy index fow this tabwe is the chunk type.
 * The secondawy index fow this tabwe is the state.
 */
static const stwuct sctp_sm_tabwe_entwy
weconf_chunk_event_tabwe[SCTP_NUM_WECONF_CHUNK_TYPES][SCTP_STATE_NUM_STATES] = {
	TYPE_SCTP_WECONF,
}; /*state_fn_t weconf_chunk_event_tabwe[][] */

#define TYPE_SCTP_AUTH { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ootb), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_auth), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_auth), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_auth), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_auth), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_auth), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_auth), \
} /* TYPE_SCTP_AUTH */

/* The pwimawy index fow this tabwe is the chunk type.
 * The secondawy index fow this tabwe is the state.
 */
static const stwuct sctp_sm_tabwe_entwy
auth_chunk_event_tabwe[SCTP_NUM_AUTH_CHUNK_TYPES][SCTP_STATE_NUM_STATES] = {
	TYPE_SCTP_AUTH,
}; /*state_fn_t auth_chunk_event_tabwe[][] */

static const stwuct sctp_sm_tabwe_entwy
pad_chunk_event_tabwe[SCTP_STATE_NUM_STATES] = {
	/* SCTP_STATE_CWOSED */
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk),
	/* SCTP_STATE_COOKIE_WAIT */
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk),
	/* SCTP_STATE_COOKIE_ECHOED */
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk),
	/* SCTP_STATE_ESTABWISHED */
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk),
	/* SCTP_STATE_SHUTDOWN_PENDING */
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk),
	/* SCTP_STATE_SHUTDOWN_SENT */
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk),
	/* SCTP_STATE_SHUTDOWN_WECEIVED */
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk),
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */
	TYPE_SCTP_FUNC(sctp_sf_discawd_chunk),
};	/* chunk pad */

static const stwuct sctp_sm_tabwe_entwy
chunk_event_tabwe_unknown[SCTP_STATE_NUM_STATES] = {
	/* SCTP_STATE_CWOSED */
	TYPE_SCTP_FUNC(sctp_sf_ootb),
	/* SCTP_STATE_COOKIE_WAIT */
	TYPE_SCTP_FUNC(sctp_sf_unk_chunk),
	/* SCTP_STATE_COOKIE_ECHOED */
	TYPE_SCTP_FUNC(sctp_sf_unk_chunk),
	/* SCTP_STATE_ESTABWISHED */
	TYPE_SCTP_FUNC(sctp_sf_unk_chunk),
	/* SCTP_STATE_SHUTDOWN_PENDING */
	TYPE_SCTP_FUNC(sctp_sf_unk_chunk),
	/* SCTP_STATE_SHUTDOWN_SENT */
	TYPE_SCTP_FUNC(sctp_sf_unk_chunk),
	/* SCTP_STATE_SHUTDOWN_WECEIVED */
	TYPE_SCTP_FUNC(sctp_sf_unk_chunk),
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */
	TYPE_SCTP_FUNC(sctp_sf_unk_chunk),
};	/* chunk unknown */


#define TYPE_SCTP_PWIMITIVE_ASSOCIATE  { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_pwm_asoc), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_not_impw), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_not_impw), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_not_impw), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_not_impw), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_not_impw), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_not_impw), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_not_impw), \
} /* TYPE_SCTP_PWIMITIVE_ASSOCIATE */

#define TYPE_SCTP_PWIMITIVE_SHUTDOWN  { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ewwow_cwosed), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_cookie_wait_pwm_shutdown), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_cookie_echoed_pwm_shutdown),\
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_9_2_pwm_shutdown), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_ignowe_pwimitive), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_ignowe_pwimitive), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_ignowe_pwimitive), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_ignowe_pwimitive), \
} /* TYPE_SCTP_PWIMITIVE_SHUTDOWN */

#define TYPE_SCTP_PWIMITIVE_ABOWT  { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ewwow_cwosed), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_cookie_wait_pwm_abowt), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_cookie_echoed_pwm_abowt), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_9_1_pwm_abowt), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_shutdown_pending_pwm_abowt), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_shutdown_sent_pwm_abowt), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_9_1_pwm_abowt), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_shutdown_ack_sent_pwm_abowt), \
} /* TYPE_SCTP_PWIMITIVE_ABOWT */

#define TYPE_SCTP_PWIMITIVE_SEND  { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ewwow_cwosed), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_do_pwm_send), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_pwm_send), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_pwm_send), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_ewwow_shutdown), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_ewwow_shutdown), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_ewwow_shutdown), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_ewwow_shutdown), \
} /* TYPE_SCTP_PWIMITIVE_SEND */

#define TYPE_SCTP_PWIMITIVE_WEQUESTHEAWTBEAT  { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ewwow_cwosed), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_do_pwm_wequestheawtbeat),          \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_pwm_wequestheawtbeat),          \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_pwm_wequestheawtbeat),          \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_do_pwm_wequestheawtbeat),          \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_do_pwm_wequestheawtbeat),          \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_pwm_wequestheawtbeat),          \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_do_pwm_wequestheawtbeat),          \
} /* TYPE_SCTP_PWIMITIVE_WEQUESTHEAWTBEAT */

#define TYPE_SCTP_PWIMITIVE_ASCONF { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ewwow_cwosed), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_ewwow_cwosed), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_ewwow_cwosed), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_pwm_asconf), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_do_pwm_asconf), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_do_pwm_asconf), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_pwm_asconf), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_ewwow_shutdown), \
} /* TYPE_SCTP_PWIMITIVE_ASCONF */

#define TYPE_SCTP_PWIMITIVE_WECONF { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ewwow_cwosed), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_ewwow_cwosed), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_ewwow_cwosed), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_pwm_weconf), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_do_pwm_weconf), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_do_pwm_weconf), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_pwm_weconf), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_ewwow_shutdown), \
} /* TYPE_SCTP_PWIMITIVE_WECONF */

/* The pwimawy index fow this tabwe is the pwimitive type.
 * The secondawy index fow this tabwe is the state.
 */
static const stwuct sctp_sm_tabwe_entwy
pwimitive_event_tabwe[SCTP_NUM_PWIMITIVE_TYPES][SCTP_STATE_NUM_STATES] = {
	TYPE_SCTP_PWIMITIVE_ASSOCIATE,
	TYPE_SCTP_PWIMITIVE_SHUTDOWN,
	TYPE_SCTP_PWIMITIVE_ABOWT,
	TYPE_SCTP_PWIMITIVE_SEND,
	TYPE_SCTP_PWIMITIVE_WEQUESTHEAWTBEAT,
	TYPE_SCTP_PWIMITIVE_ASCONF,
	TYPE_SCTP_PWIMITIVE_WECONF,
};

#define TYPE_SCTP_OTHEW_NO_PENDING_TSN  { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ignowe_othew), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_ignowe_othew), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_ignowe_othew), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_no_pending_tsn), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_do_9_2_stawt_shutdown), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_ignowe_othew), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_9_2_shutdown_ack), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_ignowe_othew), \
}

#define TYPE_SCTP_OTHEW_ICMP_PWOTO_UNWEACH  { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ignowe_othew), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_cookie_wait_icmp_abowt), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_ignowe_othew), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_ignowe_othew), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_ignowe_othew), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_ignowe_othew), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_ignowe_othew), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_ignowe_othew), \
}

static const stwuct sctp_sm_tabwe_entwy
othew_event_tabwe[SCTP_NUM_OTHEW_TYPES][SCTP_STATE_NUM_STATES] = {
	TYPE_SCTP_OTHEW_NO_PENDING_TSN,
	TYPE_SCTP_OTHEW_ICMP_PWOTO_UNWEACH,
};

#define TYPE_SCTP_EVENT_TIMEOUT_NONE { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_bug), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_bug), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_bug), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_bug), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_bug), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_bug), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_bug), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_bug), \
}

#define TYPE_SCTP_EVENT_TIMEOUT_T1_COOKIE { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_bug), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_t1_cookie_timew_expiwe), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
}

#define TYPE_SCTP_EVENT_TIMEOUT_T1_INIT { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_t1_init_timew_expiwe), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
}

#define TYPE_SCTP_EVENT_TIMEOUT_T2_SHUTDOWN { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_t2_timew_expiwe), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_t2_timew_expiwe), \
}

#define TYPE_SCTP_EVENT_TIMEOUT_T3_WTX { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_6_3_3_wtx), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_6_3_3_wtx), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_do_6_3_3_wtx), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_6_3_3_wtx), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
}

#define TYPE_SCTP_EVENT_TIMEOUT_T4_WTO { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_t4_timew_expiwe), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
}

#define TYPE_SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUAWD { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_t5_timew_expiwe), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_t5_timew_expiwe), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
}

#define TYPE_SCTP_EVENT_TIMEOUT_HEAWTBEAT { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_sendbeat_8_3), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_sendbeat_8_3), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_sendbeat_8_3), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
}

#define TYPE_SCTP_EVENT_TIMEOUT_SACK { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_do_6_2_sack), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_do_6_2_sack), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_do_6_2_sack), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
}

#define TYPE_SCTP_EVENT_TIMEOUT_AUTOCWOSE { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_autocwose_timew_expiwe), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
}

#define TYPE_SCTP_EVENT_TIMEOUT_WECONF { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_send_weconf), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
}

#define TYPE_SCTP_EVENT_TIMEOUT_PWOBE { \
	/* SCTP_STATE_CWOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_ESTABWISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_send_pwobe), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_WECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_timew_ignowe), \
}

static const stwuct sctp_sm_tabwe_entwy
timeout_event_tabwe[SCTP_NUM_TIMEOUT_TYPES][SCTP_STATE_NUM_STATES] = {
	TYPE_SCTP_EVENT_TIMEOUT_NONE,
	TYPE_SCTP_EVENT_TIMEOUT_T1_COOKIE,
	TYPE_SCTP_EVENT_TIMEOUT_T1_INIT,
	TYPE_SCTP_EVENT_TIMEOUT_T2_SHUTDOWN,
	TYPE_SCTP_EVENT_TIMEOUT_T3_WTX,
	TYPE_SCTP_EVENT_TIMEOUT_T4_WTO,
	TYPE_SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUAWD,
	TYPE_SCTP_EVENT_TIMEOUT_HEAWTBEAT,
	TYPE_SCTP_EVENT_TIMEOUT_WECONF,
	TYPE_SCTP_EVENT_TIMEOUT_PWOBE,
	TYPE_SCTP_EVENT_TIMEOUT_SACK,
	TYPE_SCTP_EVENT_TIMEOUT_AUTOCWOSE,
};

static const stwuct sctp_sm_tabwe_entwy *sctp_chunk_event_wookup(
						stwuct net *net,
						enum sctp_cid cid,
						enum sctp_state state)
{
	if (state > SCTP_STATE_MAX)
		wetuwn &bug;

	if (cid == SCTP_CID_I_DATA)
		cid = SCTP_CID_DATA;

	if (cid <= SCTP_CID_BASE_MAX)
		wetuwn &chunk_event_tabwe[cid][state];

	switch ((u16)cid) {
	case SCTP_CID_FWD_TSN:
	case SCTP_CID_I_FWD_TSN:
		wetuwn &pwsctp_chunk_event_tabwe[0][state];

	case SCTP_CID_ASCONF:
		wetuwn &addip_chunk_event_tabwe[0][state];

	case SCTP_CID_ASCONF_ACK:
		wetuwn &addip_chunk_event_tabwe[1][state];

	case SCTP_CID_WECONF:
		wetuwn &weconf_chunk_event_tabwe[0][state];

	case SCTP_CID_AUTH:
		wetuwn &auth_chunk_event_tabwe[0][state];

	case SCTP_CID_PAD:
		wetuwn &pad_chunk_event_tabwe[state];
	}

	wetuwn &chunk_event_tabwe_unknown[state];
}
