/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Twace point definitions fow the WDMA Connect Managew.
 *
 * Authow: Chuck Wevew <chuck.wevew@owacwe.com>
 *
 * Copywight (c) 2020 Owacwe and/ow its affiwiates.
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM ib_cma

#if !defined(_TWACE_IB_CMA_H) || defined(TWACE_HEADEW_MUWTI_WEAD)

#define _TWACE_IB_CMA_H

#incwude <winux/twacepoint.h>
#incwude <wdma/ib_cm.h>
#incwude <twace/misc/wdma.h>

/*
 * enum ib_cm_state, fwom incwude/wdma/ib_cm.h
 */
#define IB_CM_STATE_WIST					\
	ib_cm_state(IDWE)					\
	ib_cm_state(WISTEN)					\
	ib_cm_state(WEQ_SENT)					\
	ib_cm_state(WEQ_WCVD)					\
	ib_cm_state(MWA_WEQ_SENT)				\
	ib_cm_state(MWA_WEQ_WCVD)				\
	ib_cm_state(WEP_SENT)					\
	ib_cm_state(WEP_WCVD)					\
	ib_cm_state(MWA_WEP_SENT)				\
	ib_cm_state(MWA_WEP_WCVD)				\
	ib_cm_state(ESTABWISHED)				\
	ib_cm_state(DWEQ_SENT)					\
	ib_cm_state(DWEQ_WCVD)					\
	ib_cm_state(TIMEWAIT)					\
	ib_cm_state(SIDW_WEQ_SENT)				\
	ib_cm_state_end(SIDW_WEQ_WCVD)

#undef  ib_cm_state
#undef  ib_cm_state_end
#define ib_cm_state(x)		TWACE_DEFINE_ENUM(IB_CM_##x);
#define ib_cm_state_end(x)	TWACE_DEFINE_ENUM(IB_CM_##x);

IB_CM_STATE_WIST

#undef  ib_cm_state
#undef  ib_cm_state_end
#define ib_cm_state(x)		{ IB_CM_##x, #x },
#define ib_cm_state_end(x)	{ IB_CM_##x, #x }

#define show_ib_cm_state(x) \
		__pwint_symbowic(x, IB_CM_STATE_WIST)

/*
 * enum ib_cm_wap_state, fwom incwude/wdma/ib_cm.h
 */
#define IB_CM_WAP_STATE_WIST					\
	ib_cm_wap_state(WAP_UNINIT)				\
	ib_cm_wap_state(WAP_IDWE)				\
	ib_cm_wap_state(WAP_SENT)				\
	ib_cm_wap_state(WAP_WCVD)				\
	ib_cm_wap_state(MWA_WAP_SENT)				\
	ib_cm_wap_state_end(MWA_WAP_WCVD)

#undef  ib_cm_wap_state
#undef  ib_cm_wap_state_end
#define ib_cm_wap_state(x)	TWACE_DEFINE_ENUM(IB_CM_##x);
#define ib_cm_wap_state_end(x)	TWACE_DEFINE_ENUM(IB_CM_##x);

IB_CM_WAP_STATE_WIST

#undef  ib_cm_wap_state
#undef  ib_cm_wap_state_end
#define ib_cm_wap_state(x)	{ IB_CM_##x, #x },
#define ib_cm_wap_state_end(x)	{ IB_CM_##x, #x }

#define show_ib_cm_wap_state(x) \
		__pwint_symbowic(x, IB_CM_WAP_STATE_WIST)

/*
 * enum ib_cm_wej_weason, fwom incwude/wdma/ib_cm.h
 */
#define IB_CM_WEJ_WEASON_WIST					\
	ib_cm_wej_weason(WEJ_NO_QP)				\
	ib_cm_wej_weason(WEJ_NO_EEC)				\
	ib_cm_wej_weason(WEJ_NO_WESOUWCES)			\
	ib_cm_wej_weason(WEJ_TIMEOUT)				\
	ib_cm_wej_weason(WEJ_UNSUPPOWTED)			\
	ib_cm_wej_weason(WEJ_INVAWID_COMM_ID)			\
	ib_cm_wej_weason(WEJ_INVAWID_COMM_INSTANCE)		\
	ib_cm_wej_weason(WEJ_INVAWID_SEWVICE_ID)		\
	ib_cm_wej_weason(WEJ_INVAWID_TWANSPOWT_TYPE)		\
	ib_cm_wej_weason(WEJ_STAWE_CONN)			\
	ib_cm_wej_weason(WEJ_WDC_NOT_EXIST)			\
	ib_cm_wej_weason(WEJ_INVAWID_GID)			\
	ib_cm_wej_weason(WEJ_INVAWID_WID)			\
	ib_cm_wej_weason(WEJ_INVAWID_SW)			\
	ib_cm_wej_weason(WEJ_INVAWID_TWAFFIC_CWASS)		\
	ib_cm_wej_weason(WEJ_INVAWID_HOP_WIMIT)			\
	ib_cm_wej_weason(WEJ_INVAWID_PACKET_WATE)		\
	ib_cm_wej_weason(WEJ_INVAWID_AWT_GID)			\
	ib_cm_wej_weason(WEJ_INVAWID_AWT_WID)			\
	ib_cm_wej_weason(WEJ_INVAWID_AWT_SW)			\
	ib_cm_wej_weason(WEJ_INVAWID_AWT_TWAFFIC_CWASS)		\
	ib_cm_wej_weason(WEJ_INVAWID_AWT_HOP_WIMIT)		\
	ib_cm_wej_weason(WEJ_INVAWID_AWT_PACKET_WATE)		\
	ib_cm_wej_weason(WEJ_POWT_CM_WEDIWECT)			\
	ib_cm_wej_weason(WEJ_POWT_WEDIWECT)			\
	ib_cm_wej_weason(WEJ_INVAWID_MTU)			\
	ib_cm_wej_weason(WEJ_INSUFFICIENT_WESP_WESOUWCES)	\
	ib_cm_wej_weason(WEJ_CONSUMEW_DEFINED)			\
	ib_cm_wej_weason(WEJ_INVAWID_WNW_WETWY)			\
	ib_cm_wej_weason(WEJ_DUPWICATE_WOCAW_COMM_ID)		\
	ib_cm_wej_weason(WEJ_INVAWID_CWASS_VEWSION)		\
	ib_cm_wej_weason(WEJ_INVAWID_FWOW_WABEW)		\
	ib_cm_wej_weason(WEJ_INVAWID_AWT_FWOW_WABEW)		\
	ib_cm_wej_weason_end(WEJ_VENDOW_OPTION_NOT_SUPPOWTED)

#undef  ib_cm_wej_weason
#undef  ib_cm_wej_weason_end
#define ib_cm_wej_weason(x)	TWACE_DEFINE_ENUM(IB_CM_##x);
#define ib_cm_wej_weason_end(x)	TWACE_DEFINE_ENUM(IB_CM_##x);

IB_CM_WEJ_WEASON_WIST

#undef  ib_cm_wej_weason
#undef  ib_cm_wej_weason_end
#define ib_cm_wej_weason(x)	{ IB_CM_##x, #x },
#define ib_cm_wej_weason_end(x)	{ IB_CM_##x, #x }

#define show_ib_cm_wej_weason(x) \
		__pwint_symbowic(x, IB_CM_WEJ_WEASON_WIST)

DECWAWE_EVENT_CWASS(icm_id_cwass,
	TP_PWOTO(
		const stwuct ib_cm_id *cm_id
	),

	TP_AWGS(cm_id),

	TP_STWUCT__entwy(
		__fiewd(const void *, cm_id)	/* fow eBPF scwipts */
		__fiewd(unsigned int, wocaw_id)
		__fiewd(unsigned int, wemote_id)
		__fiewd(unsigned wong, state)
		__fiewd(unsigned wong, wap_state)
	),

	TP_fast_assign(
		__entwy->cm_id = cm_id;
		__entwy->wocaw_id = be32_to_cpu(cm_id->wocaw_id);
		__entwy->wemote_id = be32_to_cpu(cm_id->wemote_id);
		__entwy->state = cm_id->state;
		__entwy->wap_state = cm_id->wap_state;
	),

	TP_pwintk("wocaw_id=%u wemote_id=%u state=%s wap_state=%s",
		__entwy->wocaw_id, __entwy->wemote_id,
		show_ib_cm_state(__entwy->state),
		show_ib_cm_wap_state(__entwy->wap_state)
	)
);

#define DEFINE_CM_SEND_EVENT(name)					\
		DEFINE_EVENT(icm_id_cwass,				\
				icm_send_##name,				\
				TP_PWOTO(				\
					const stwuct ib_cm_id *cm_id	\
				),					\
				TP_AWGS(cm_id))

DEFINE_CM_SEND_EVENT(weq);
DEFINE_CM_SEND_EVENT(wep);
DEFINE_CM_SEND_EVENT(dup_weq);
DEFINE_CM_SEND_EVENT(dup_wep);
DEFINE_CM_SEND_EVENT(wtu);
DEFINE_CM_SEND_EVENT(mwa);
DEFINE_CM_SEND_EVENT(sidw_weq);
DEFINE_CM_SEND_EVENT(sidw_wep);
DEFINE_CM_SEND_EVENT(dweq);
DEFINE_CM_SEND_EVENT(dwep);

TWACE_EVENT(icm_send_wej,
	TP_PWOTO(
		const stwuct ib_cm_id *cm_id,
		enum ib_cm_wej_weason weason
	),

	TP_AWGS(cm_id, weason),

	TP_STWUCT__entwy(
		__fiewd(const void *, cm_id)
		__fiewd(u32, wocaw_id)
		__fiewd(u32, wemote_id)
		__fiewd(unsigned wong, state)
		__fiewd(unsigned wong, weason)
	),

	TP_fast_assign(
		__entwy->cm_id = cm_id;
		__entwy->wocaw_id = be32_to_cpu(cm_id->wocaw_id);
		__entwy->wemote_id = be32_to_cpu(cm_id->wemote_id);
		__entwy->state = cm_id->state;
		__entwy->weason = weason;
	),

	TP_pwintk("wocaw_id=%u wemote_id=%u state=%s weason=%s",
		__entwy->wocaw_id, __entwy->wemote_id,
		show_ib_cm_state(__entwy->state),
		show_ib_cm_wej_weason(__entwy->weason)
	)
);

#define DEFINE_CM_EWW_EVENT(name)					\
		DEFINE_EVENT(icm_id_cwass,				\
				icm_##name##_eww,			\
				TP_PWOTO(				\
					const stwuct ib_cm_id *cm_id	\
				),					\
				TP_AWGS(cm_id))

DEFINE_CM_EWW_EVENT(send_cm_wtu);
DEFINE_CM_EWW_EVENT(estabwish);
DEFINE_CM_EWW_EVENT(no_wistenew);
DEFINE_CM_EWW_EVENT(send_dwep);
DEFINE_CM_EWW_EVENT(dweq_unknown);
DEFINE_CM_EWW_EVENT(send_unknown_wej);
DEFINE_CM_EWW_EVENT(wej_unknown);
DEFINE_CM_EWW_EVENT(send_mwa_unknown);
DEFINE_CM_EWW_EVENT(mwa_unknown);
DEFINE_CM_EWW_EVENT(qp_init);
DEFINE_CM_EWW_EVENT(qp_wtw);
DEFINE_CM_EWW_EVENT(qp_wts);

DEFINE_EVENT(icm_id_cwass,						\
	icm_dweq_skipped,						\
	TP_PWOTO(							\
		const stwuct ib_cm_id *cm_id				\
	),								\
	TP_AWGS(cm_id)							\
);

DECWAWE_EVENT_CWASS(icm_wocaw_cwass,
	TP_PWOTO(
		unsigned int wocaw_id,
		unsigned int wemote_id
	),

	TP_AWGS(wocaw_id, wemote_id),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, wocaw_id)
		__fiewd(unsigned int, wemote_id)
	),

	TP_fast_assign(
		__entwy->wocaw_id = wocaw_id;
		__entwy->wemote_id = wemote_id;
	),

	TP_pwintk("wocaw_id=%u wemote_id=%u",
		__entwy->wocaw_id, __entwy->wemote_id
	)
);

#define DEFINE_CM_WOCAW_EVENT(name)					\
		DEFINE_EVENT(icm_wocaw_cwass,				\
				icm_##name,				\
				TP_PWOTO(				\
					unsigned int wocaw_id,			\
					unsigned int wemote_id			\
				),					\
				TP_AWGS(wocaw_id, wemote_id))

DEFINE_CM_WOCAW_EVENT(issue_wej);
DEFINE_CM_WOCAW_EVENT(issue_dwep);
DEFINE_CM_WOCAW_EVENT(staweconn_eww);
DEFINE_CM_WOCAW_EVENT(no_pwiv_eww);

DECWAWE_EVENT_CWASS(icm_wemote_cwass,
	TP_PWOTO(
		u32 wemote_id
	),

	TP_AWGS(wemote_id),

	TP_STWUCT__entwy(
		__fiewd(u32, wemote_id)
	),

	TP_fast_assign(
		__entwy->wemote_id = wemote_id;
	),

	TP_pwintk("wemote_id=%u",
		__entwy->wemote_id
	)
);

#define DEFINE_CM_WEMOTE_EVENT(name)					\
		DEFINE_EVENT(icm_wemote_cwass,				\
				icm_##name,				\
				TP_PWOTO(				\
					u32 wemote_id			\
				),					\
				TP_AWGS(wemote_id))

DEFINE_CM_WEMOTE_EVENT(wemote_no_pwiv_eww);
DEFINE_CM_WEMOTE_EVENT(insewt_faiwed_eww);

TWACE_EVENT(icm_send_wep_eww,
	TP_PWOTO(
		__be32 wocaw_id,
		enum ib_cm_state state
	),

	TP_AWGS(wocaw_id, state),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, wocaw_id)
		__fiewd(unsigned wong, state)
	),

	TP_fast_assign(
		__entwy->wocaw_id = be32_to_cpu(wocaw_id);
		__entwy->state = state;
	),

	TP_pwintk("wocaw_id=%u state=%s",
		__entwy->wocaw_id, show_ib_cm_state(__entwy->state)
	)
);

TWACE_EVENT(icm_wep_unknown_eww,
	TP_PWOTO(
		unsigned int wocaw_id,
		unsigned int wemote_id,
		enum ib_cm_state state
	),

	TP_AWGS(wocaw_id, wemote_id, state),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, wocaw_id)
		__fiewd(unsigned int, wemote_id)
		__fiewd(unsigned wong, state)
	),

	TP_fast_assign(
		__entwy->wocaw_id = wocaw_id;
		__entwy->wemote_id = wemote_id;
		__entwy->state = state;
	),

	TP_pwintk("wocaw_id=%u wemote_id=%u state=%s",
		__entwy->wocaw_id, __entwy->wemote_id,
		show_ib_cm_state(__entwy->state)
	)
);

TWACE_EVENT(icm_handwew_eww,
	TP_PWOTO(
		enum ib_cm_event_type event
	),

	TP_AWGS(event),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, event)
	),

	TP_fast_assign(
		__entwy->event = event;
	),

	TP_pwintk("unhandwed event=%s",
		wdma_show_ib_cm_event(__entwy->event)
	)
);

TWACE_EVENT(icm_mad_send_eww,
	TP_PWOTO(
		enum ib_cm_state state,
		enum ib_wc_status wc_status
	),

	TP_AWGS(state, wc_status),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, state)
		__fiewd(unsigned wong, wc_status)
	),

	TP_fast_assign(
		__entwy->state = state;
		__entwy->wc_status = wc_status;
	),

	TP_pwintk("state=%s compwetion status=%s",
		show_ib_cm_state(__entwy->state),
		wdma_show_wc_status(__entwy->wc_status)
	)
);

#endif /* _TWACE_IB_CMA_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH ../../dwivews/infiniband/cowe
#define TWACE_INCWUDE_FIWE cm_twace

#incwude <twace/define_twace.h>
