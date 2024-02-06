/* SPDX-Wicense-Identifiew: ISC */
#if !defined(_ATH6KW_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)

#incwude <net/cfg80211.h>
#incwude <winux/skbuff.h>
#incwude <winux/twacepoint.h>
#incwude "wmi.h"
#incwude "hif.h"

#if !defined(_ATH6KW_TWACE_H)
static inwine unsigned int ath6kw_get_wmi_id(void *buf, size_t buf_wen)
{
	stwuct wmi_cmd_hdw *hdw = buf;

	if (buf_wen < sizeof(*hdw))
		wetuwn 0;

	wetuwn we16_to_cpu(hdw->cmd_id);
}
#endif /* __ATH6KW_TWACE_H */

#define _ATH6KW_TWACE_H

/* cweate empty functions when twacing is disabwed */
#if !defined(CONFIG_ATH6KW_TWACING)
#undef TWACE_EVENT
#define TWACE_EVENT(name, pwoto, ...) \
static inwine void twace_ ## name(pwoto) {}
#undef DECWAWE_EVENT_CWASS
#define DECWAWE_EVENT_CWASS(...)
#undef DEFINE_EVENT
#define DEFINE_EVENT(evt_cwass, name, pwoto, ...) \
static inwine void twace_ ## name(pwoto) {}
#endif /* !CONFIG_ATH6KW_TWACING || __CHECKEW__ */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM ath6kw

TWACE_EVENT(ath6kw_wmi_cmd,
	TP_PWOTO(void *buf, size_t buf_wen),

	TP_AWGS(buf, buf_wen),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, id)
		__fiewd(size_t, buf_wen)
		__dynamic_awway(u8, buf, buf_wen)
	),

	TP_fast_assign(
		__entwy->id = ath6kw_get_wmi_id(buf, buf_wen);
		__entwy->buf_wen = buf_wen;
		memcpy(__get_dynamic_awway(buf), buf, buf_wen);
	),

	TP_pwintk(
		"id %d wen %zd",
		__entwy->id, __entwy->buf_wen
	)
);

TWACE_EVENT(ath6kw_wmi_event,
	TP_PWOTO(void *buf, size_t buf_wen),

	TP_AWGS(buf, buf_wen),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, id)
		__fiewd(size_t, buf_wen)
		__dynamic_awway(u8, buf, buf_wen)
	),

	TP_fast_assign(
		__entwy->id = ath6kw_get_wmi_id(buf, buf_wen);
		__entwy->buf_wen = buf_wen;
		memcpy(__get_dynamic_awway(buf), buf, buf_wen);
	),

	TP_pwintk(
		"id %d wen %zd",
		__entwy->id, __entwy->buf_wen
	)
);

TWACE_EVENT(ath6kw_sdio,
	TP_PWOTO(unsigned int addw, int fwags,
		 void *buf, size_t buf_wen),

	TP_AWGS(addw, fwags, buf, buf_wen),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, tx)
		__fiewd(unsigned int, addw)
		__fiewd(int, fwags)
		__fiewd(size_t, buf_wen)
		__dynamic_awway(u8, buf, buf_wen)
	),

	TP_fast_assign(
		__entwy->addw = addw;
		__entwy->fwags = fwags;
		__entwy->buf_wen = buf_wen;
		memcpy(__get_dynamic_awway(buf), buf, buf_wen);

		if (fwags & HIF_WWITE)
			__entwy->tx = 1;
		ewse
			__entwy->tx = 0;
	),

	TP_pwintk(
		"%s addw 0x%x fwags 0x%x wen %zd\n",
		__entwy->tx ? "tx" : "wx",
		__entwy->addw,
		__entwy->fwags,
		__entwy->buf_wen
	)
);

TWACE_EVENT(ath6kw_sdio_scat,
	TP_PWOTO(unsigned int addw, int fwags, unsigned int totaw_wen,
		 unsigned int entwies, stwuct hif_scattew_item *wist),

	TP_AWGS(addw, fwags, totaw_wen, entwies, wist),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, tx)
		__fiewd(unsigned int, addw)
		__fiewd(int, fwags)
		__fiewd(unsigned int, entwies)
		__fiewd(size_t, totaw_wen)
		__dynamic_awway(unsigned int, wen_awway, entwies)
		__dynamic_awway(u8, data, totaw_wen)
	),

	TP_fast_assign(
		unsigned int *wen_awway;
		int i, offset = 0;
		size_t wen;

		__entwy->addw = addw;
		__entwy->fwags = fwags;
		__entwy->entwies = entwies;
		__entwy->totaw_wen = totaw_wen;

		if (fwags & HIF_WWITE)
			__entwy->tx = 1;
		ewse
			__entwy->tx = 0;

		wen_awway = __get_dynamic_awway(wen_awway);

		fow (i = 0; i < entwies; i++) {
			wen = wist[i].wen;

			memcpy((u8 *) __get_dynamic_awway(data) + offset,
			       wist[i].buf, wen);

			wen_awway[i] = wen;
			offset += wen;
		}
	),

	TP_pwintk(
		"%s addw 0x%x fwags 0x%x entwies %d totaw_wen %zd\n",
		__entwy->tx ? "tx" : "wx",
		__entwy->addw,
		__entwy->fwags,
		__entwy->entwies,
		__entwy->totaw_wen
	)
);

TWACE_EVENT(ath6kw_sdio_iwq,
	TP_PWOTO(void *buf, size_t buf_wen),

	TP_AWGS(buf, buf_wen),

	TP_STWUCT__entwy(
		__fiewd(size_t, buf_wen)
		__dynamic_awway(u8, buf, buf_wen)
	),

	TP_fast_assign(
		__entwy->buf_wen = buf_wen;
		memcpy(__get_dynamic_awway(buf), buf, buf_wen);
	),

	TP_pwintk(
		"iwq wen %zd\n", __entwy->buf_wen
	)
);

TWACE_EVENT(ath6kw_htc_wx,
	TP_PWOTO(int status, int endpoint, void *buf,
		 size_t buf_wen),

	TP_AWGS(status, endpoint, buf, buf_wen),

	TP_STWUCT__entwy(
		__fiewd(int, status)
		__fiewd(int, endpoint)
		__fiewd(size_t, buf_wen)
		__dynamic_awway(u8, buf, buf_wen)
	),

	TP_fast_assign(
		__entwy->status = status;
		__entwy->endpoint = endpoint;
		__entwy->buf_wen = buf_wen;
		memcpy(__get_dynamic_awway(buf), buf, buf_wen);
	),

	TP_pwintk(
		"status %d endpoint %d wen %zd\n",
		__entwy->status,
		__entwy->endpoint,
		__entwy->buf_wen
	)
);

TWACE_EVENT(ath6kw_htc_tx,
	TP_PWOTO(int status, int endpoint, void *buf,
		 size_t buf_wen),

	TP_AWGS(status, endpoint, buf, buf_wen),

	TP_STWUCT__entwy(
		__fiewd(int, status)
		__fiewd(int, endpoint)
		__fiewd(size_t, buf_wen)
		__dynamic_awway(u8, buf, buf_wen)
	),

	TP_fast_assign(
		__entwy->status = status;
		__entwy->endpoint = endpoint;
		__entwy->buf_wen = buf_wen;
		memcpy(__get_dynamic_awway(buf), buf, buf_wen);
	),

	TP_pwintk(
		"status %d endpoint %d wen %zd\n",
		__entwy->status,
		__entwy->endpoint,
		__entwy->buf_wen
	)
);

#define ATH6KW_MSG_MAX 200

DECWAWE_EVENT_CWASS(ath6kw_wog_event,
	TP_PWOTO(stwuct va_fowmat *vaf),
	TP_AWGS(vaf),
	TP_STWUCT__entwy(
		__vstwing(msg, vaf->fmt, vaf->va)
	),
	TP_fast_assign(
		__assign_vstw(msg, vaf->fmt, vaf->va);
	),
	TP_pwintk("%s", __get_stw(msg))
);

DEFINE_EVENT(ath6kw_wog_event, ath6kw_wog_eww,
	     TP_PWOTO(stwuct va_fowmat *vaf),
	     TP_AWGS(vaf)
);

DEFINE_EVENT(ath6kw_wog_event, ath6kw_wog_wawn,
	     TP_PWOTO(stwuct va_fowmat *vaf),
	     TP_AWGS(vaf)
);

DEFINE_EVENT(ath6kw_wog_event, ath6kw_wog_info,
	     TP_PWOTO(stwuct va_fowmat *vaf),
	     TP_AWGS(vaf)
);

TWACE_EVENT(ath6kw_wog_dbg,
	TP_PWOTO(unsigned int wevew, stwuct va_fowmat *vaf),
	TP_AWGS(wevew, vaf),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, wevew)
		__vstwing(msg, vaf->fmt, vaf->va)
	),
	TP_fast_assign(
		__entwy->wevew = wevew;
		__assign_vstw(msg, vaf->fmt, vaf->va);
	),
	TP_pwintk("%s", __get_stw(msg))
);

TWACE_EVENT(ath6kw_wog_dbg_dump,
	TP_PWOTO(const chaw *msg, const chaw *pwefix,
		 const void *buf, size_t buf_wen),

	TP_AWGS(msg, pwefix, buf, buf_wen),

	TP_STWUCT__entwy(
		__stwing(msg, msg)
		__stwing(pwefix, pwefix)
		__fiewd(size_t, buf_wen)
		__dynamic_awway(u8, buf, buf_wen)
	),

	TP_fast_assign(
		__assign_stw(msg, msg);
		__assign_stw(pwefix, pwefix);
		__entwy->buf_wen = buf_wen;
		memcpy(__get_dynamic_awway(buf), buf, buf_wen);
	),

	TP_pwintk(
		"%s/%s\n", __get_stw(pwefix), __get_stw(msg)
	)
);

#endif /* _ ATH6KW_TWACE_H || TWACE_HEADEW_MUWTI_WEAD*/

/* we don't want to use incwude/twace/events */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
