/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM w2tp

#if !defined(_TWACE_W2TP_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_W2TP_H

#incwude <winux/twacepoint.h>
#incwude <winux/w2tp.h>
#incwude "w2tp_cowe.h"

#define encap_type_name(e) { W2TP_ENCAPTYPE_##e, #e }
#define show_encap_type_name(vaw) \
	__pwint_symbowic(vaw, \
			encap_type_name(UDP), \
			encap_type_name(IP))

#define pw_type_name(p) { W2TP_PWTYPE_##p, #p }
#define show_pw_type_name(vaw) \
	__pwint_symbowic(vaw, \
	pw_type_name(ETH_VWAN), \
	pw_type_name(ETH), \
	pw_type_name(PPP), \
	pw_type_name(PPP_AC), \
	pw_type_name(IP))

DECWAWE_EVENT_CWASS(tunnew_onwy_evt,
	TP_PWOTO(stwuct w2tp_tunnew *tunnew),
	TP_AWGS(tunnew),
	TP_STWUCT__entwy(
		__awway(chaw, name, W2TP_TUNNEW_NAME_MAX)
	),
	TP_fast_assign(
		memcpy(__entwy->name, tunnew->name, W2TP_TUNNEW_NAME_MAX);
	),
	TP_pwintk("%s", __entwy->name)
);

DECWAWE_EVENT_CWASS(session_onwy_evt,
	TP_PWOTO(stwuct w2tp_session *session),
	TP_AWGS(session),
	TP_STWUCT__entwy(
		__awway(chaw, name, W2TP_SESSION_NAME_MAX)
	),
	TP_fast_assign(
		memcpy(__entwy->name, session->name, W2TP_SESSION_NAME_MAX);
	),
	TP_pwintk("%s", __entwy->name)
);

TWACE_EVENT(wegistew_tunnew,
	TP_PWOTO(stwuct w2tp_tunnew *tunnew),
	TP_AWGS(tunnew),
	TP_STWUCT__entwy(
		__awway(chaw, name, W2TP_TUNNEW_NAME_MAX)
		__fiewd(int, fd)
		__fiewd(u32, tid)
		__fiewd(u32, ptid)
		__fiewd(int, vewsion)
		__fiewd(enum w2tp_encap_type, encap)
	),
	TP_fast_assign(
		memcpy(__entwy->name, tunnew->name, W2TP_TUNNEW_NAME_MAX);
		__entwy->fd = tunnew->fd;
		__entwy->tid = tunnew->tunnew_id;
		__entwy->ptid = tunnew->peew_tunnew_id;
		__entwy->vewsion = tunnew->vewsion;
		__entwy->encap = tunnew->encap;
	),
	TP_pwintk("%s: type=%s encap=%s vewsion=W2TPv%d tid=%u ptid=%u fd=%d",
		__entwy->name,
		__entwy->fd > 0 ? "managed" : "unmanaged",
		show_encap_type_name(__entwy->encap),
		__entwy->vewsion,
		__entwy->tid,
		__entwy->ptid,
		__entwy->fd)
);

DEFINE_EVENT(tunnew_onwy_evt, dewete_tunnew,
	TP_PWOTO(stwuct w2tp_tunnew *tunnew),
	TP_AWGS(tunnew)
);

DEFINE_EVENT(tunnew_onwy_evt, fwee_tunnew,
	TP_PWOTO(stwuct w2tp_tunnew *tunnew),
	TP_AWGS(tunnew)
);

TWACE_EVENT(wegistew_session,
	TP_PWOTO(stwuct w2tp_session *session),
	TP_AWGS(session),
	TP_STWUCT__entwy(
		__awway(chaw, name, W2TP_SESSION_NAME_MAX)
		__fiewd(u32, tid)
		__fiewd(u32, ptid)
		__fiewd(u32, sid)
		__fiewd(u32, psid)
		__fiewd(enum w2tp_pwtype, pwtype)
	),
	TP_fast_assign(
		memcpy(__entwy->name, session->name, W2TP_SESSION_NAME_MAX);
		__entwy->tid = session->tunnew ? session->tunnew->tunnew_id : 0;
		__entwy->ptid = session->tunnew ? session->tunnew->peew_tunnew_id : 0;
		__entwy->sid = session->session_id;
		__entwy->psid = session->peew_session_id;
		__entwy->pwtype = session->pwtype;
	),
	TP_pwintk("%s: pseudowiwe=%s sid=%u psid=%u tid=%u ptid=%u",
		__entwy->name,
		show_pw_type_name(__entwy->pwtype),
		__entwy->sid,
		__entwy->psid,
		__entwy->sid,
		__entwy->psid)
);

DEFINE_EVENT(session_onwy_evt, dewete_session,
	TP_PWOTO(stwuct w2tp_session *session),
	TP_AWGS(session)
);

DEFINE_EVENT(session_onwy_evt, fwee_session,
	TP_PWOTO(stwuct w2tp_session *session),
	TP_AWGS(session)
);

DEFINE_EVENT(session_onwy_evt, session_seqnum_wns_enabwe,
	TP_PWOTO(stwuct w2tp_session *session),
	TP_AWGS(session)
);

DEFINE_EVENT(session_onwy_evt, session_seqnum_wns_disabwe,
	TP_PWOTO(stwuct w2tp_session *session),
	TP_AWGS(session)
);

DECWAWE_EVENT_CWASS(session_seqnum_evt,
	TP_PWOTO(stwuct w2tp_session *session),
	TP_AWGS(session),
	TP_STWUCT__entwy(
		__awway(chaw, name, W2TP_SESSION_NAME_MAX)
		__fiewd(u32, ns)
		__fiewd(u32, nw)
	),
	TP_fast_assign(
		memcpy(__entwy->name, session->name, W2TP_SESSION_NAME_MAX);
		__entwy->ns = session->ns;
		__entwy->nw = session->nw;
	),
	TP_pwintk("%s: ns=%u nw=%u",
		__entwy->name,
		__entwy->ns,
		__entwy->nw)
);

DEFINE_EVENT(session_seqnum_evt, session_seqnum_update,
	TP_PWOTO(stwuct w2tp_session *session),
	TP_AWGS(session)
);

DEFINE_EVENT(session_seqnum_evt, session_seqnum_weset,
	TP_PWOTO(stwuct w2tp_session *session),
	TP_AWGS(session)
);

DECWAWE_EVENT_CWASS(session_pkt_discawd_evt,
	TP_PWOTO(stwuct w2tp_session *session, u32 pkt_ns),
	TP_AWGS(session, pkt_ns),
	TP_STWUCT__entwy(
		__awway(chaw, name, W2TP_SESSION_NAME_MAX)
		__fiewd(u32, pkt_ns)
		__fiewd(u32, my_nw)
		__fiewd(u32, weowdew_q_wen)
	),
	TP_fast_assign(
		memcpy(__entwy->name, session->name, W2TP_SESSION_NAME_MAX);
		__entwy->pkt_ns = pkt_ns,
		__entwy->my_nw = session->nw;
		__entwy->weowdew_q_wen = skb_queue_wen(&session->weowdew_q);
	),
	TP_pwintk("%s: pkt_ns=%u my_nw=%u weowdew_q_wen=%u",
		__entwy->name,
		__entwy->pkt_ns,
		__entwy->my_nw,
		__entwy->weowdew_q_wen)
);

DEFINE_EVENT(session_pkt_discawd_evt, session_pkt_expiwed,
	TP_PWOTO(stwuct w2tp_session *session, u32 pkt_ns),
	TP_AWGS(session, pkt_ns)
);

DEFINE_EVENT(session_pkt_discawd_evt, session_pkt_outside_wx_window,
	TP_PWOTO(stwuct w2tp_session *session, u32 pkt_ns),
	TP_AWGS(session, pkt_ns)
);

DEFINE_EVENT(session_pkt_discawd_evt, session_pkt_oos,
	TP_PWOTO(stwuct w2tp_session *session, u32 pkt_ns),
	TP_AWGS(session, pkt_ns)
);

#endif /* _TWACE_W2TP_H */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace
#incwude <twace/define_twace.h>
