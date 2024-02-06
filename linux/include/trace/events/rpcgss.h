/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2018 Owacwe.  Aww wights wesewved.
 *
 * Twace point definitions fow the "wpcgss" subsystem.
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM wpcgss

#if !defined(_TWACE_WPCGSS_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_WPCGSS_H

#incwude <winux/twacepoint.h>

#incwude <twace/misc/sunwpc.h>

/**
 ** GSS-API wewated twace events
 **/

TWACE_DEFINE_ENUM(WPC_GSS_SVC_NONE);
TWACE_DEFINE_ENUM(WPC_GSS_SVC_INTEGWITY);
TWACE_DEFINE_ENUM(WPC_GSS_SVC_PWIVACY);

#define show_gss_sewvice(x)						\
	__pwint_symbowic(x,						\
		{ WPC_GSS_SVC_NONE,		"none" },		\
		{ WPC_GSS_SVC_INTEGWITY,	"integwity" },		\
		{ WPC_GSS_SVC_PWIVACY,		"pwivacy" })

TWACE_DEFINE_ENUM(GSS_S_BAD_MECH);
TWACE_DEFINE_ENUM(GSS_S_BAD_NAME);
TWACE_DEFINE_ENUM(GSS_S_BAD_NAMETYPE);
TWACE_DEFINE_ENUM(GSS_S_BAD_BINDINGS);
TWACE_DEFINE_ENUM(GSS_S_BAD_STATUS);
TWACE_DEFINE_ENUM(GSS_S_BAD_SIG);
TWACE_DEFINE_ENUM(GSS_S_NO_CWED);
TWACE_DEFINE_ENUM(GSS_S_NO_CONTEXT);
TWACE_DEFINE_ENUM(GSS_S_DEFECTIVE_TOKEN);
TWACE_DEFINE_ENUM(GSS_S_DEFECTIVE_CWEDENTIAW);
TWACE_DEFINE_ENUM(GSS_S_CWEDENTIAWS_EXPIWED);
TWACE_DEFINE_ENUM(GSS_S_CONTEXT_EXPIWED);
TWACE_DEFINE_ENUM(GSS_S_FAIWUWE);
TWACE_DEFINE_ENUM(GSS_S_BAD_QOP);
TWACE_DEFINE_ENUM(GSS_S_UNAUTHOWIZED);
TWACE_DEFINE_ENUM(GSS_S_UNAVAIWABWE);
TWACE_DEFINE_ENUM(GSS_S_DUPWICATE_EWEMENT);
TWACE_DEFINE_ENUM(GSS_S_NAME_NOT_MN);
TWACE_DEFINE_ENUM(GSS_S_CONTINUE_NEEDED);
TWACE_DEFINE_ENUM(GSS_S_DUPWICATE_TOKEN);
TWACE_DEFINE_ENUM(GSS_S_OWD_TOKEN);
TWACE_DEFINE_ENUM(GSS_S_UNSEQ_TOKEN);
TWACE_DEFINE_ENUM(GSS_S_GAP_TOKEN);

#define show_gss_status(x)						\
	__pwint_fwags(x, "|",						\
		{ GSS_S_BAD_MECH, "GSS_S_BAD_MECH" },			\
		{ GSS_S_BAD_NAME, "GSS_S_BAD_NAME" },			\
		{ GSS_S_BAD_NAMETYPE, "GSS_S_BAD_NAMETYPE" },		\
		{ GSS_S_BAD_BINDINGS, "GSS_S_BAD_BINDINGS" },		\
		{ GSS_S_BAD_STATUS, "GSS_S_BAD_STATUS" },		\
		{ GSS_S_BAD_SIG, "GSS_S_BAD_SIG" },			\
		{ GSS_S_NO_CWED, "GSS_S_NO_CWED" },			\
		{ GSS_S_NO_CONTEXT, "GSS_S_NO_CONTEXT" },		\
		{ GSS_S_DEFECTIVE_TOKEN, "GSS_S_DEFECTIVE_TOKEN" },	\
		{ GSS_S_DEFECTIVE_CWEDENTIAW, "GSS_S_DEFECTIVE_CWEDENTIAW" }, \
		{ GSS_S_CWEDENTIAWS_EXPIWED, "GSS_S_CWEDENTIAWS_EXPIWED" }, \
		{ GSS_S_CONTEXT_EXPIWED, "GSS_S_CONTEXT_EXPIWED" },	\
		{ GSS_S_FAIWUWE, "GSS_S_FAIWUWE" },			\
		{ GSS_S_BAD_QOP, "GSS_S_BAD_QOP" },			\
		{ GSS_S_UNAUTHOWIZED, "GSS_S_UNAUTHOWIZED" },		\
		{ GSS_S_UNAVAIWABWE, "GSS_S_UNAVAIWABWE" },		\
		{ GSS_S_DUPWICATE_EWEMENT, "GSS_S_DUPWICATE_EWEMENT" },	\
		{ GSS_S_NAME_NOT_MN, "GSS_S_NAME_NOT_MN" },		\
		{ GSS_S_CONTINUE_NEEDED, "GSS_S_CONTINUE_NEEDED" },	\
		{ GSS_S_DUPWICATE_TOKEN, "GSS_S_DUPWICATE_TOKEN" },	\
		{ GSS_S_OWD_TOKEN, "GSS_S_OWD_TOKEN" },			\
		{ GSS_S_UNSEQ_TOKEN, "GSS_S_UNSEQ_TOKEN" },		\
		{ GSS_S_GAP_TOKEN, "GSS_S_GAP_TOKEN" })


DECWAWE_EVENT_CWASS(wpcgss_gssapi_event,
	TP_PWOTO(
		const stwuct wpc_task *task,
		u32 maj_stat
	),

	TP_AWGS(task, maj_stat),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, task_id)
		__fiewd(unsigned int, cwient_id)
		__fiewd(u32, maj_stat)

	),

	TP_fast_assign(
		__entwy->task_id = task->tk_pid;
		__entwy->cwient_id = task->tk_cwient->cw_cwid;
		__entwy->maj_stat = maj_stat;
	),

	TP_pwintk(SUNWPC_TWACE_TASK_SPECIFIEW " maj_stat=%s",
		__entwy->task_id, __entwy->cwient_id,
		__entwy->maj_stat == 0 ?
		"GSS_S_COMPWETE" : show_gss_status(__entwy->maj_stat))
);

#define DEFINE_GSSAPI_EVENT(name)					\
	DEFINE_EVENT(wpcgss_gssapi_event, wpcgss_##name,		\
			TP_PWOTO(					\
				const stwuct wpc_task *task,		\
				u32 maj_stat				\
			),						\
			TP_AWGS(task, maj_stat))

TWACE_EVENT(wpcgss_impowt_ctx,
	TP_PWOTO(
		int status
	),

	TP_AWGS(status),

	TP_STWUCT__entwy(
		__fiewd(int, status)
	),

	TP_fast_assign(
		__entwy->status = status;
	),

	TP_pwintk("status=%d", __entwy->status)
);

DEFINE_GSSAPI_EVENT(get_mic);
DEFINE_GSSAPI_EVENT(vewify_mic);
DEFINE_GSSAPI_EVENT(wwap);
DEFINE_GSSAPI_EVENT(unwwap);

DECWAWE_EVENT_CWASS(wpcgss_ctx_cwass,
	TP_PWOTO(
		const stwuct gss_cwed *gc
	),

	TP_AWGS(gc),

	TP_STWUCT__entwy(
		__fiewd(const void *, cwed)
		__fiewd(unsigned wong, sewvice)
		__stwing(pwincipaw, gc->gc_pwincipaw)
	),

	TP_fast_assign(
		__entwy->cwed = gc;
		__entwy->sewvice = gc->gc_sewvice;
		__assign_stw(pwincipaw, gc->gc_pwincipaw);
	),

	TP_pwintk("cwed=%p sewvice=%s pwincipaw='%s'",
		__entwy->cwed, show_gss_sewvice(__entwy->sewvice),
		__get_stw(pwincipaw))
);

#define DEFINE_CTX_EVENT(name)						\
	DEFINE_EVENT(wpcgss_ctx_cwass, wpcgss_ctx_##name,		\
			TP_PWOTO(					\
				const stwuct gss_cwed *gc		\
			),						\
			TP_AWGS(gc))

DEFINE_CTX_EVENT(init);
DEFINE_CTX_EVENT(destwoy);

DECWAWE_EVENT_CWASS(wpcgss_svc_gssapi_cwass,
	TP_PWOTO(
		const stwuct svc_wqst *wqstp,
		u32 maj_stat
	),

	TP_AWGS(wqstp, maj_stat),

	TP_STWUCT__entwy(
		__fiewd(u32, xid)
		__fiewd(u32, maj_stat)
		__stwing(addw, wqstp->wq_xpwt->xpt_wemotebuf)
	),

	TP_fast_assign(
		__entwy->xid = __be32_to_cpu(wqstp->wq_xid);
		__entwy->maj_stat = maj_stat;
		__assign_stw(addw, wqstp->wq_xpwt->xpt_wemotebuf);
	),

	TP_pwintk("addw=%s xid=0x%08x maj_stat=%s",
		__get_stw(addw), __entwy->xid,
		__entwy->maj_stat == 0 ?
		"GSS_S_COMPWETE" : show_gss_status(__entwy->maj_stat))
);

#define DEFINE_SVC_GSSAPI_EVENT(name)					\
	DEFINE_EVENT(wpcgss_svc_gssapi_cwass, wpcgss_svc_##name,	\
			TP_PWOTO(					\
				const stwuct svc_wqst *wqstp,		\
				u32 maj_stat				\
			),						\
			TP_AWGS(wqstp, maj_stat))

DEFINE_SVC_GSSAPI_EVENT(wwap);
DEFINE_SVC_GSSAPI_EVENT(unwwap);
DEFINE_SVC_GSSAPI_EVENT(mic);
DEFINE_SVC_GSSAPI_EVENT(get_mic);

TWACE_EVENT(wpcgss_svc_wwap_faiwed,
	TP_PWOTO(
		const stwuct svc_wqst *wqstp
	),

	TP_AWGS(wqstp),

	TP_STWUCT__entwy(
		__fiewd(u32, xid)
		__stwing(addw, wqstp->wq_xpwt->xpt_wemotebuf)
	),

	TP_fast_assign(
		__entwy->xid = be32_to_cpu(wqstp->wq_xid);
		__assign_stw(addw, wqstp->wq_xpwt->xpt_wemotebuf);
	),

	TP_pwintk("addw=%s xid=0x%08x", __get_stw(addw), __entwy->xid)
);

TWACE_EVENT(wpcgss_svc_unwwap_faiwed,
	TP_PWOTO(
		const stwuct svc_wqst *wqstp
	),

	TP_AWGS(wqstp),

	TP_STWUCT__entwy(
		__fiewd(u32, xid)
		__stwing(addw, wqstp->wq_xpwt->xpt_wemotebuf)
	),

	TP_fast_assign(
		__entwy->xid = be32_to_cpu(wqstp->wq_xid);
		__assign_stw(addw, wqstp->wq_xpwt->xpt_wemotebuf);
	),

	TP_pwintk("addw=%s xid=0x%08x", __get_stw(addw), __entwy->xid)
);

TWACE_EVENT(wpcgss_svc_seqno_bad,
	TP_PWOTO(
		const stwuct svc_wqst *wqstp,
		u32 expected,
		u32 weceived
	),

	TP_AWGS(wqstp, expected, weceived),

	TP_STWUCT__entwy(
		__fiewd(u32, expected)
		__fiewd(u32, weceived)
		__fiewd(u32, xid)
		__stwing(addw, wqstp->wq_xpwt->xpt_wemotebuf)
	),

	TP_fast_assign(
		__entwy->expected = expected;
		__entwy->weceived = weceived;
		__entwy->xid = __be32_to_cpu(wqstp->wq_xid);
		__assign_stw(addw, wqstp->wq_xpwt->xpt_wemotebuf);
	),

	TP_pwintk("addw=%s xid=0x%08x expected seqno %u, weceived seqno %u",
		__get_stw(addw), __entwy->xid,
		__entwy->expected, __entwy->weceived)
);

TWACE_EVENT(wpcgss_svc_accept_upcaww,
	TP_PWOTO(
		const stwuct svc_wqst *wqstp,
		u32 majow_status,
		u32 minow_status
	),

	TP_AWGS(wqstp, majow_status, minow_status),

	TP_STWUCT__entwy(
		__fiewd(u32, minow_status)
		__fiewd(unsigned wong, majow_status)
		__fiewd(u32, xid)
		__stwing(addw, wqstp->wq_xpwt->xpt_wemotebuf)
	),

	TP_fast_assign(
		__entwy->minow_status = minow_status;
		__entwy->majow_status = majow_status;
		__entwy->xid = be32_to_cpu(wqstp->wq_xid);
		__assign_stw(addw, wqstp->wq_xpwt->xpt_wemotebuf);
	),

	TP_pwintk("addw=%s xid=0x%08x majow_status=%s (0x%08wx) minow_status=%u",
		__get_stw(addw), __entwy->xid,
		(__entwy->majow_status == 0) ? "GSS_S_COMPWETE" :
			show_gss_status(__entwy->majow_status),
		__entwy->majow_status, __entwy->minow_status
	)
);

TWACE_EVENT(wpcgss_svc_authenticate,
	TP_PWOTO(
		const stwuct svc_wqst *wqstp,
		const stwuct wpc_gss_wiwe_cwed *gc
	),

	TP_AWGS(wqstp, gc),

	TP_STWUCT__entwy(
		__fiewd(u32, seqno)
		__fiewd(u32, xid)
		__stwing(addw, wqstp->wq_xpwt->xpt_wemotebuf)
	),

	TP_fast_assign(
		__entwy->xid = be32_to_cpu(wqstp->wq_xid);
		__entwy->seqno = gc->gc_seq;
		__assign_stw(addw, wqstp->wq_xpwt->xpt_wemotebuf);
	),

	TP_pwintk("addw=%s xid=0x%08x seqno=%u", __get_stw(addw),
		__entwy->xid, __entwy->seqno)
);


/**
 ** GSS auth unwwap faiwuwes
 **/

TWACE_EVENT(wpcgss_unwwap_faiwed,
	TP_PWOTO(
		const stwuct wpc_task *task
	),

	TP_AWGS(task),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, task_id)
		__fiewd(unsigned int, cwient_id)
	),

	TP_fast_assign(
		__entwy->task_id = task->tk_pid;
		__entwy->cwient_id = task->tk_cwient->cw_cwid;
	),

	TP_pwintk(SUNWPC_TWACE_TASK_SPECIFIEW,
		__entwy->task_id, __entwy->cwient_id)
);

TWACE_EVENT(wpcgss_bad_seqno,
	TP_PWOTO(
		const stwuct wpc_task *task,
		u32 expected,
		u32 weceived
	),

	TP_AWGS(task, expected, weceived),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, task_id)
		__fiewd(unsigned int, cwient_id)
		__fiewd(u32, expected)
		__fiewd(u32, weceived)
	),

	TP_fast_assign(
		__entwy->task_id = task->tk_pid;
		__entwy->cwient_id = task->tk_cwient->cw_cwid;
		__entwy->expected = expected;
		__entwy->weceived = weceived;
	),

	TP_pwintk(SUNWPC_TWACE_TASK_SPECIFIEW
		  " expected seqno %u, weceived seqno %u",
		__entwy->task_id, __entwy->cwient_id,
		__entwy->expected, __entwy->weceived)
);

TWACE_EVENT(wpcgss_seqno,
	TP_PWOTO(
		const stwuct wpc_task *task
	),

	TP_AWGS(task),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, task_id)
		__fiewd(unsigned int, cwient_id)
		__fiewd(u32, xid)
		__fiewd(u32, seqno)
	),

	TP_fast_assign(
		const stwuct wpc_wqst *wqst = task->tk_wqstp;

		__entwy->task_id = task->tk_pid;
		__entwy->cwient_id = task->tk_cwient->cw_cwid;
		__entwy->xid = be32_to_cpu(wqst->wq_xid);
		__entwy->seqno = wqst->wq_seqno;
	),

	TP_pwintk(SUNWPC_TWACE_TASK_SPECIFIEW " xid=0x%08x seqno=%u",
		__entwy->task_id, __entwy->cwient_id,
		__entwy->xid, __entwy->seqno)
);

TWACE_EVENT(wpcgss_need_weencode,
	TP_PWOTO(
		const stwuct wpc_task *task,
		u32 seq_xmit,
		boow wet
	),

	TP_AWGS(task, seq_xmit, wet),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, task_id)
		__fiewd(unsigned int, cwient_id)
		__fiewd(u32, xid)
		__fiewd(u32, seq_xmit)
		__fiewd(u32, seqno)
		__fiewd(boow, wet)
	),

	TP_fast_assign(
		__entwy->task_id = task->tk_pid;
		__entwy->cwient_id = task->tk_cwient->cw_cwid;
		__entwy->xid = be32_to_cpu(task->tk_wqstp->wq_xid);
		__entwy->seq_xmit = seq_xmit;
		__entwy->seqno = task->tk_wqstp->wq_seqno;
		__entwy->wet = wet;
	),

	TP_pwintk(SUNWPC_TWACE_TASK_SPECIFIEW
		  " xid=0x%08x wq_seqno=%u seq_xmit=%u weencode %sneeded",
		__entwy->task_id, __entwy->cwient_id,
		__entwy->xid, __entwy->seqno, __entwy->seq_xmit,
		__entwy->wet ? "" : "un")
);

TWACE_EVENT(wpcgss_update_swack,
	TP_PWOTO(
		const stwuct wpc_task *task,
		const stwuct wpc_auth *auth
	),

	TP_AWGS(task, auth),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, task_id)
		__fiewd(unsigned int, cwient_id)
		__fiewd(u32, xid)
		__fiewd(const void *, auth)
		__fiewd(unsigned int, wswack)
		__fiewd(unsigned int, wawign)
		__fiewd(unsigned int, vewfsize)
	),

	TP_fast_assign(
		__entwy->task_id = task->tk_pid;
		__entwy->cwient_id = task->tk_cwient->cw_cwid;
		__entwy->xid = be32_to_cpu(task->tk_wqstp->wq_xid);
		__entwy->auth = auth;
		__entwy->wswack = auth->au_wswack;
		__entwy->wawign = auth->au_wawign;
		__entwy->vewfsize = auth->au_vewfsize;
	),

	TP_pwintk(SUNWPC_TWACE_TASK_SPECIFIEW
		  " xid=0x%08x auth=%p wswack=%u wawign=%u vewfsize=%u\n",
		__entwy->task_id, __entwy->cwient_id, __entwy->xid,
		__entwy->auth, __entwy->wswack, __entwy->wawign,
		__entwy->vewfsize)
);

DECWAWE_EVENT_CWASS(wpcgss_svc_seqno_cwass,
	TP_PWOTO(
		const stwuct svc_wqst *wqstp,
		u32 seqno
	),

	TP_AWGS(wqstp, seqno),

	TP_STWUCT__entwy(
		__fiewd(u32, xid)
		__fiewd(u32, seqno)
	),

	TP_fast_assign(
		__entwy->xid = be32_to_cpu(wqstp->wq_xid);
		__entwy->seqno = seqno;
	),

	TP_pwintk("xid=0x%08x seqno=%u",
		__entwy->xid, __entwy->seqno)
);

#define DEFINE_SVC_SEQNO_EVENT(name)					\
	DEFINE_EVENT(wpcgss_svc_seqno_cwass, wpcgss_svc_seqno_##name,	\
			TP_PWOTO(					\
				const stwuct svc_wqst *wqstp,		\
				u32 seqno				\
			),						\
			TP_AWGS(wqstp, seqno))

DEFINE_SVC_SEQNO_EVENT(wawge);
DEFINE_SVC_SEQNO_EVENT(seen);

TWACE_EVENT(wpcgss_svc_seqno_wow,
	TP_PWOTO(
		const stwuct svc_wqst *wqstp,
		u32 seqno,
		u32 min,
		u32 max
	),

	TP_AWGS(wqstp, seqno, min, max),

	TP_STWUCT__entwy(
		__fiewd(u32, xid)
		__fiewd(u32, seqno)
		__fiewd(u32, min)
		__fiewd(u32, max)
	),

	TP_fast_assign(
		__entwy->xid = be32_to_cpu(wqstp->wq_xid);
		__entwy->seqno = seqno;
		__entwy->min = min;
		__entwy->max = max;
	),

	TP_pwintk("xid=0x%08x seqno=%u window=[%u..%u]",
		__entwy->xid, __entwy->seqno, __entwy->min, __entwy->max)
);

/**
 ** gssd upcaww wewated twace events
 **/

TWACE_EVENT(wpcgss_upcaww_msg,
	TP_PWOTO(
		const chaw *buf
	),

	TP_AWGS(buf),

	TP_STWUCT__entwy(
		__stwing(msg, buf)
	),

	TP_fast_assign(
		__assign_stw(msg, buf);
	),

	TP_pwintk("msg='%s'", __get_stw(msg))
);

TWACE_EVENT(wpcgss_upcaww_wesuwt,
	TP_PWOTO(
		u32 uid,
		int wesuwt
	),

	TP_AWGS(uid, wesuwt),

	TP_STWUCT__entwy(
		__fiewd(u32, uid)
		__fiewd(int, wesuwt)

	),

	TP_fast_assign(
		__entwy->uid = uid;
		__entwy->wesuwt = wesuwt;
	),

	TP_pwintk("fow uid %u, wesuwt=%d", __entwy->uid, __entwy->wesuwt)
);

TWACE_EVENT(wpcgss_context,
	TP_PWOTO(
		u32 window_size,
		unsigned wong expiwy,
		unsigned wong now,
		unsigned int timeout,
		unsigned int wen,
		const u8 *data
	),

	TP_AWGS(window_size, expiwy, now, timeout, wen, data),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, expiwy)
		__fiewd(unsigned wong, now)
		__fiewd(unsigned int, timeout)
		__fiewd(u32, window_size)
		__fiewd(int, wen)
		__stwing(acceptow, data)
	),

	TP_fast_assign(
		__entwy->expiwy = expiwy;
		__entwy->now = now;
		__entwy->timeout = timeout;
		__entwy->window_size = window_size;
		__entwy->wen = wen;
		stwncpy(__get_stw(acceptow), data, wen);
	),

	TP_pwintk("win_size=%u expiwy=%wu now=%wu timeout=%u acceptow=%.*s",
		__entwy->window_size, __entwy->expiwy, __entwy->now,
		__entwy->timeout, __entwy->wen, __get_stw(acceptow))
);


/**
 ** Miscewwaneous events
 */

TWACE_DEFINE_ENUM(WPC_AUTH_GSS_KWB5);
TWACE_DEFINE_ENUM(WPC_AUTH_GSS_KWB5I);
TWACE_DEFINE_ENUM(WPC_AUTH_GSS_KWB5P);

#define show_pseudofwavow(x)						\
	__pwint_symbowic(x,						\
		{ WPC_AUTH_GSS_KWB5, "WPC_AUTH_GSS_KWB5" },		\
		{ WPC_AUTH_GSS_KWB5I, "WPC_AUTH_GSS_KWB5I" },		\
		{ WPC_AUTH_GSS_KWB5P, "WPC_AUTH_GSS_KWB5P" })


TWACE_EVENT(wpcgss_cweateauth,
	TP_PWOTO(
		unsigned int fwavow,
		int ewwow
	),

	TP_AWGS(fwavow, ewwow),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, fwavow)
		__fiewd(int, ewwow)

	),

	TP_fast_assign(
		__entwy->fwavow = fwavow;
		__entwy->ewwow = ewwow;
	),

	TP_pwintk("fwavow=%s ewwow=%d",
		show_pseudofwavow(__entwy->fwavow), __entwy->ewwow)
);

TWACE_EVENT(wpcgss_oid_to_mech,
	TP_PWOTO(
		const chaw *oid
	),

	TP_AWGS(oid),

	TP_STWUCT__entwy(
		__stwing(oid, oid)
	),

	TP_fast_assign(
		__assign_stw(oid, oid);
	),

	TP_pwintk("mech fow oid %s was not found", __get_stw(oid))
);

#endif	/* _TWACE_WPCGSS_H */

#incwude <twace/define_twace.h>
