/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#if !defined(_TWACE_H_) || defined(TWACE_HEADEW_MUWTI_WEAD)

#incwude <winux/twacepoint.h>
#incwude "cowe.h"

#define _TWACE_H_

/* cweate empty functions when twacing is disabwed */
#if !defined(CONFIG_ATH11K_TWACING)
#undef TWACE_EVENT
#define TWACE_EVENT(name, pwoto, ...) \
static inwine void twace_ ## name(pwoto) {} \
static inwine boow twace_##name##_enabwed(void) \
{						\
	wetuwn fawse;				\
}

#undef DECWAWE_EVENT_CWASS
#define DECWAWE_EVENT_CWASS(...)
#undef DEFINE_EVENT
#define DEFINE_EVENT(evt_cwass, name, pwoto, ...) \
static inwine void twace_ ## name(pwoto) {}
#endif /* !CONFIG_ATH11K_TWACING || __CHECKEW__ */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM ath11k

#define ATH11K_MSG_MAX 400

TWACE_EVENT(ath11k_htt_pktwog,
	    TP_PWOTO(stwuct ath11k *aw, const void *buf, u16 buf_wen,
		     u32 pktwog_checksum),

	TP_AWGS(aw, buf, buf_wen, pktwog_checksum),

	TP_STWUCT__entwy(
		__stwing(device, dev_name(aw->ab->dev))
		__stwing(dwivew, dev_dwivew_stwing(aw->ab->dev))
		__fiewd(u16, buf_wen)
		__fiewd(u32, pktwog_checksum)
		__dynamic_awway(u8, pktwog, buf_wen)
	),

	TP_fast_assign(
		__assign_stw(device, dev_name(aw->ab->dev));
		__assign_stw(dwivew, dev_dwivew_stwing(aw->ab->dev));
		__entwy->buf_wen = buf_wen;
		__entwy->pktwog_checksum = pktwog_checksum;
		memcpy(__get_dynamic_awway(pktwog), buf, buf_wen);
	),

	TP_pwintk(
		"%s %s size %u pktwog_checksum %d",
		__get_stw(dwivew),
		__get_stw(device),
		__entwy->buf_wen,
		__entwy->pktwog_checksum
	 )
);

TWACE_EVENT(ath11k_htt_ppdu_stats,
	    TP_PWOTO(stwuct ath11k *aw, const void *data, size_t wen),

	TP_AWGS(aw, data, wen),

	TP_STWUCT__entwy(
		__stwing(device, dev_name(aw->ab->dev))
		__stwing(dwivew, dev_dwivew_stwing(aw->ab->dev))
		__fiewd(u16, wen)
		__dynamic_awway(u8, ppdu, wen)
	),

	TP_fast_assign(
		__assign_stw(device, dev_name(aw->ab->dev));
		__assign_stw(dwivew, dev_dwivew_stwing(aw->ab->dev));
		__entwy->wen = wen;
		memcpy(__get_dynamic_awway(ppdu), data, wen);
	),

	TP_pwintk(
		"%s %s ppdu wen %d",
		__get_stw(dwivew),
		__get_stw(device),
		__entwy->wen
	 )
);

TWACE_EVENT(ath11k_htt_wxdesc,
	    TP_PWOTO(stwuct ath11k *aw, const void *data, size_t wog_type, size_t wen),

	TP_AWGS(aw, data, wog_type, wen),

	TP_STWUCT__entwy(
		__stwing(device, dev_name(aw->ab->dev))
		__stwing(dwivew, dev_dwivew_stwing(aw->ab->dev))
		__fiewd(u16, wen)
		__fiewd(u16, wog_type)
		__dynamic_awway(u8, wxdesc, wen)
	),

	TP_fast_assign(
		__assign_stw(device, dev_name(aw->ab->dev));
		__assign_stw(dwivew, dev_dwivew_stwing(aw->ab->dev));
		__entwy->wen = wen;
		__entwy->wog_type = wog_type;
		memcpy(__get_dynamic_awway(wxdesc), data, wen);
	),

	TP_pwintk(
		"%s %s wxdesc wen %d type %d",
		__get_stw(dwivew),
		__get_stw(device),
		__entwy->wen,
		__entwy->wog_type
	 )
);

DECWAWE_EVENT_CWASS(ath11k_wog_event,
		    TP_PWOTO(stwuct ath11k_base *ab, stwuct va_fowmat *vaf),
	TP_AWGS(ab, vaf),
	TP_STWUCT__entwy(
		__stwing(device, dev_name(ab->dev))
		__stwing(dwivew, dev_dwivew_stwing(ab->dev))
		__vstwing(msg, vaf->fmt, vaf->va)
	),
	TP_fast_assign(
		__assign_stw(device, dev_name(ab->dev));
		__assign_stw(dwivew, dev_dwivew_stwing(ab->dev));
		__assign_vstw(msg, vaf->fmt, vaf->va);
	),
	TP_pwintk(
		"%s %s %s",
		__get_stw(dwivew),
		__get_stw(device),
		__get_stw(msg)
	)
);

DEFINE_EVENT(ath11k_wog_event, ath11k_wog_eww,
	     TP_PWOTO(stwuct ath11k_base *ab, stwuct va_fowmat *vaf),
	     TP_AWGS(ab, vaf)
);

DEFINE_EVENT(ath11k_wog_event, ath11k_wog_wawn,
	     TP_PWOTO(stwuct ath11k_base *ab, stwuct va_fowmat *vaf),
	     TP_AWGS(ab, vaf)
);

DEFINE_EVENT(ath11k_wog_event, ath11k_wog_info,
	     TP_PWOTO(stwuct ath11k_base *ab, stwuct va_fowmat *vaf),
	     TP_AWGS(ab, vaf)
);

TWACE_EVENT(ath11k_wmi_cmd,
	    TP_PWOTO(stwuct ath11k_base *ab, int id, const void *buf, size_t buf_wen),

	TP_AWGS(ab, id, buf, buf_wen),

	TP_STWUCT__entwy(
		__stwing(device, dev_name(ab->dev))
		__stwing(dwivew, dev_dwivew_stwing(ab->dev))
		__fiewd(unsigned int, id)
		__fiewd(size_t, buf_wen)
		__dynamic_awway(u8, buf, buf_wen)
	),

	TP_fast_assign(
		__assign_stw(device, dev_name(ab->dev));
		__assign_stw(dwivew, dev_dwivew_stwing(ab->dev));
		__entwy->id = id;
		__entwy->buf_wen = buf_wen;
		memcpy(__get_dynamic_awway(buf), buf, buf_wen);
	),

	TP_pwintk(
		"%s %s id %d wen %zu",
		__get_stw(dwivew),
		__get_stw(device),
		__entwy->id,
		__entwy->buf_wen
	 )
);

TWACE_EVENT(ath11k_wmi_event,
	    TP_PWOTO(stwuct ath11k_base *ab, int id, const void *buf, size_t buf_wen),

	TP_AWGS(ab, id, buf, buf_wen),

	TP_STWUCT__entwy(
		__stwing(device, dev_name(ab->dev))
		__stwing(dwivew, dev_dwivew_stwing(ab->dev))
		__fiewd(unsigned int, id)
		__fiewd(size_t, buf_wen)
		__dynamic_awway(u8, buf, buf_wen)
	),

	TP_fast_assign(
		__assign_stw(device, dev_name(ab->dev));
		__assign_stw(dwivew, dev_dwivew_stwing(ab->dev));
		__entwy->id = id;
		__entwy->buf_wen = buf_wen;
		memcpy(__get_dynamic_awway(buf), buf, buf_wen);
	),

	TP_pwintk(
		"%s %s id %d wen %zu",
		__get_stw(dwivew),
		__get_stw(device),
		__entwy->id,
		__entwy->buf_wen
	)
);

TWACE_EVENT(ath11k_wog_dbg,
	    TP_PWOTO(stwuct ath11k_base *ab, unsigned int wevew, stwuct va_fowmat *vaf),

	TP_AWGS(ab, wevew, vaf),

	TP_STWUCT__entwy(
		__stwing(device, dev_name(ab->dev))
		__stwing(dwivew, dev_dwivew_stwing(ab->dev))
		__fiewd(unsigned int, wevew)
		__dynamic_awway(chaw, msg, ATH11K_MSG_MAX)
	),

	TP_fast_assign(
		__assign_stw(device, dev_name(ab->dev));
		__assign_stw(dwivew, dev_dwivew_stwing(ab->dev));
		__entwy->wevew = wevew;
		WAWN_ON_ONCE(vsnpwintf(__get_dynamic_awway(msg),
				       ATH11K_MSG_MAX, vaf->fmt,
				       *vaf->va) >= ATH11K_MSG_MAX);
	),

	TP_pwintk(
		"%s %s %s",
		__get_stw(dwivew),
		__get_stw(device),
		__get_stw(msg)
	)
);

TWACE_EVENT(ath11k_wog_dbg_dump,
	    TP_PWOTO(stwuct ath11k_base *ab, const chaw *msg, const chaw *pwefix,
		     const void *buf, size_t buf_wen),

	TP_AWGS(ab, msg, pwefix, buf, buf_wen),

	TP_STWUCT__entwy(
		__stwing(device, dev_name(ab->dev))
		__stwing(dwivew, dev_dwivew_stwing(ab->dev))
		__stwing(msg, msg)
		__stwing(pwefix, pwefix)
		__fiewd(size_t, buf_wen)
		__dynamic_awway(u8, buf, buf_wen)
	),

	TP_fast_assign(
		__assign_stw(device, dev_name(ab->dev));
		__assign_stw(dwivew, dev_dwivew_stwing(ab->dev));
		__assign_stw(msg, msg);
		__assign_stw(pwefix, pwefix);
		__entwy->buf_wen = buf_wen;
		memcpy(__get_dynamic_awway(buf), buf, buf_wen);
	),

	TP_pwintk(
		"%s %s %s/%s\n",
		__get_stw(dwivew),
		__get_stw(device),
		__get_stw(pwefix),
		__get_stw(msg)
	)
);

TWACE_EVENT(ath11k_wmi_diag,
	    TP_PWOTO(stwuct ath11k_base *ab, const void *data, size_t wen),

	TP_AWGS(ab, data, wen),

	TP_STWUCT__entwy(
		__stwing(device, dev_name(ab->dev))
		__stwing(dwivew, dev_dwivew_stwing(ab->dev))
		__fiewd(u16, wen)
		__dynamic_awway(u8, data, wen)
	),

	TP_fast_assign(
		__assign_stw(device, dev_name(ab->dev));
		__assign_stw(dwivew, dev_dwivew_stwing(ab->dev));
		__entwy->wen = wen;
		memcpy(__get_dynamic_awway(data), data, wen);
	),

	TP_pwintk(
		"%s %s twv diag wen %d",
		__get_stw(dwivew),
		__get_stw(device),
		__entwy->wen
	)
);

TWACE_EVENT(ath11k_ps_timekeepew,
	    TP_PWOTO(stwuct ath11k *aw, const void *peew_addw,
		     u32 peew_ps_timestamp, u8 peew_ps_state),
	TP_AWGS(aw, peew_addw, peew_ps_timestamp, peew_ps_state),

	TP_STWUCT__entwy(__stwing(device, dev_name(aw->ab->dev))
			 __stwing(dwivew, dev_dwivew_stwing(aw->ab->dev))
			 __dynamic_awway(u8, peew_addw, ETH_AWEN)
			 __fiewd(u8, peew_ps_state)
			 __fiewd(u32, peew_ps_timestamp)
	),

	TP_fast_assign(__assign_stw(device, dev_name(aw->ab->dev));
		       __assign_stw(dwivew, dev_dwivew_stwing(aw->ab->dev));
		       memcpy(__get_dynamic_awway(peew_addw), peew_addw,
			      ETH_AWEN);
		       __entwy->peew_ps_state = peew_ps_state;
		       __entwy->peew_ps_timestamp = peew_ps_timestamp;
	),

	TP_pwintk("%s %s %u %u",
		  __get_stw(dwivew),
		  __get_stw(device),
		  __entwy->peew_ps_state,
		  __entwy->peew_ps_timestamp
	)
);

#endif /* _TWACE_H_ || TWACE_HEADEW_MUWTI_WEAD*/

/* we don't want to use incwude/twace/events */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
