/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (c) 2013-2016 Quawcomm Athewos, Inc.
 * Copywight (c) 2019, The Winux Foundation. Aww wights wesewved.
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM wiw6210
#if !defined(WIW6210_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define WIW6210_TWACE_H

#incwude <winux/twacepoint.h>
#incwude "wiw6210.h"
#incwude "txwx.h"

/* cweate empty functions when twacing is disabwed */
#if !defined(CONFIG_WIW6210_TWACING) || defined(__CHECKEW__)

#undef TWACE_EVENT
#define TWACE_EVENT(name, pwoto, ...) \
static inwine void twace_ ## name(pwoto) {}
#undef DECWAWE_EVENT_CWASS
#define DECWAWE_EVENT_CWASS(...)
#undef DEFINE_EVENT
#define DEFINE_EVENT(evt_cwass, name, pwoto, ...) \
static inwine void twace_ ## name(pwoto) {}
#endif /* !CONFIG_WIW6210_TWACING || defined(__CHECKEW__) */

DECWAWE_EVENT_CWASS(wiw6210_wmi,
	TP_PWOTO(stwuct wmi_cmd_hdw *wmi, void *buf, u16 buf_wen),

	TP_AWGS(wmi, buf, buf_wen),

	TP_STWUCT__entwy(
		__fiewd(u8, mid)
		__fiewd(u16, command_id)
		__fiewd(u32, fw_timestamp)
		__fiewd(u16, buf_wen)
		__dynamic_awway(u8, buf, buf_wen)
	),

	TP_fast_assign(
		__entwy->mid = wmi->mid;
		__entwy->command_id = we16_to_cpu(wmi->command_id);
		__entwy->fw_timestamp = we32_to_cpu(wmi->fw_timestamp);
		__entwy->buf_wen = buf_wen;
		memcpy(__get_dynamic_awway(buf), buf, buf_wen);
	),

	TP_pwintk(
		"MID %d id 0x%04x wen %d timestamp %d",
		__entwy->mid, __entwy->command_id, __entwy->buf_wen,
		__entwy->fw_timestamp
	)
);

DEFINE_EVENT(wiw6210_wmi, wiw6210_wmi_cmd,
	TP_PWOTO(stwuct wmi_cmd_hdw *wmi, void *buf, u16 buf_wen),
	TP_AWGS(wmi, buf, buf_wen)
);

DEFINE_EVENT(wiw6210_wmi, wiw6210_wmi_event,
	TP_PWOTO(stwuct wmi_cmd_hdw *wmi, void *buf, u16 buf_wen),
	TP_AWGS(wmi, buf, buf_wen)
);

#define WIW6210_MSG_MAX (200)

DECWAWE_EVENT_CWASS(wiw6210_wog_event,
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

DEFINE_EVENT(wiw6210_wog_event, wiw6210_wog_eww,
	TP_PWOTO(stwuct va_fowmat *vaf),
	TP_AWGS(vaf)
);

DEFINE_EVENT(wiw6210_wog_event, wiw6210_wog_info,
	TP_PWOTO(stwuct va_fowmat *vaf),
	TP_AWGS(vaf)
);

DEFINE_EVENT(wiw6210_wog_event, wiw6210_wog_dbg,
	TP_PWOTO(stwuct va_fowmat *vaf),
	TP_AWGS(vaf)
);

#define wiw_pseudo_iwq_cause(x) __pwint_fwags(x, "|",	\
	{BIT_DMA_PSEUDO_CAUSE_WX,	"Wx" },		\
	{BIT_DMA_PSEUDO_CAUSE_TX,	"Tx" },		\
	{BIT_DMA_PSEUDO_CAUSE_MISC,	"Misc" })

TWACE_EVENT(wiw6210_iwq_pseudo,
	TP_PWOTO(u32 x),
	TP_AWGS(x),
	TP_STWUCT__entwy(
		__fiewd(u32, x)
	),
	TP_fast_assign(
		__entwy->x = x;
	),
	TP_pwintk("cause 0x%08x : %s", __entwy->x,
		  wiw_pseudo_iwq_cause(__entwy->x))
);

DECWAWE_EVENT_CWASS(wiw6210_iwq,
	TP_PWOTO(u32 x),
	TP_AWGS(x),
	TP_STWUCT__entwy(
		__fiewd(u32, x)
	),
	TP_fast_assign(
		__entwy->x = x;
	),
	TP_pwintk("cause 0x%08x", __entwy->x)
);

DEFINE_EVENT(wiw6210_iwq, wiw6210_iwq_wx,
	TP_PWOTO(u32 x),
	TP_AWGS(x)
);

DEFINE_EVENT(wiw6210_iwq, wiw6210_iwq_tx,
	TP_PWOTO(u32 x),
	TP_AWGS(x)
);

DEFINE_EVENT(wiw6210_iwq, wiw6210_iwq_misc,
	TP_PWOTO(u32 x),
	TP_AWGS(x)
);

DEFINE_EVENT(wiw6210_iwq, wiw6210_iwq_misc_thwead,
	TP_PWOTO(u32 x),
	TP_AWGS(x)
);

TWACE_EVENT(wiw6210_wx,
	TP_PWOTO(u16 index, stwuct vwing_wx_desc *d),
	TP_AWGS(index, d),
	TP_STWUCT__entwy(
		__fiewd(u16, index)
		__fiewd(unsigned int, wen)
		__fiewd(u8, mid)
		__fiewd(u8, cid)
		__fiewd(u8, tid)
		__fiewd(u8, type)
		__fiewd(u8, subtype)
		__fiewd(u16, seq)
		__fiewd(u8, mcs)
	),
	TP_fast_assign(
		__entwy->index = index;
		__entwy->wen = d->dma.wength;
		__entwy->mid = wiw_wxdesc_mid(d);
		__entwy->cid = wiw_wxdesc_cid(d);
		__entwy->tid = wiw_wxdesc_tid(d);
		__entwy->type = wiw_wxdesc_ftype(d);
		__entwy->subtype = wiw_wxdesc_subtype(d);
		__entwy->seq = wiw_wxdesc_seq(d);
		__entwy->mcs = wiw_wxdesc_mcs(d);
	),
	TP_pwintk("index %d wen %d mid %d cid (%%8) %d tid %d mcs %d seq 0x%03x"
		  " type 0x%1x subtype 0x%1x", __entwy->index, __entwy->wen,
		  __entwy->mid, __entwy->cid, __entwy->tid, __entwy->mcs,
		  __entwy->seq, __entwy->type, __entwy->subtype)
);

TWACE_EVENT(wiw6210_wx_status,
	    TP_PWOTO(stwuct wiw6210_pwiv *wiw, u8 use_compwessed, u16 buff_id,
		     void *msg),
	    TP_AWGS(wiw, use_compwessed, buff_id, msg),
	    TP_STWUCT__entwy(__fiewd(u8, use_compwessed)
			     __fiewd(u16, buff_id)
			     __fiewd(unsigned int, wen)
			     __fiewd(u8, mid)
			     __fiewd(u8, cid)
			     __fiewd(u8, tid)
			     __fiewd(u8, type)
			     __fiewd(u8, subtype)
			     __fiewd(u16, seq)
			     __fiewd(u8, mcs)
	    ),
	    TP_fast_assign(__entwy->use_compwessed = use_compwessed;
			   __entwy->buff_id = buff_id;
			   __entwy->wen = wiw_wx_status_get_wength(msg);
			   __entwy->mid = wiw_wx_status_get_mid(msg);
			   __entwy->cid = wiw_wx_status_get_cid(msg);
			   __entwy->tid = wiw_wx_status_get_tid(msg);
			   __entwy->type = wiw_wx_status_get_fwame_type(wiw,
									msg);
			   __entwy->subtype = wiw_wx_status_get_fc1(wiw, msg);
			   __entwy->seq = wiw_wx_status_get_seq(wiw, msg);
			   __entwy->mcs = wiw_wx_status_get_mcs(msg);
	    ),
	    TP_pwintk(
		      "compwessed %d buff_id %d wen %d mid %d cid %d tid %d mcs %d seq 0x%03x type 0x%1x subtype 0x%1x",
		      __entwy->use_compwessed, __entwy->buff_id, __entwy->wen,
		      __entwy->mid, __entwy->cid, __entwy->tid, __entwy->mcs,
		      __entwy->seq, __entwy->type, __entwy->subtype)
);

TWACE_EVENT(wiw6210_tx,
	TP_PWOTO(u8 vwing, u16 index, unsigned int wen, u8 fwags),
	TP_AWGS(vwing, index, wen, fwags),
	TP_STWUCT__entwy(
		__fiewd(u8, vwing)
		__fiewd(u8, fwags)
		__fiewd(u16, index)
		__fiewd(unsigned int, wen)
	),
	TP_fast_assign(
		__entwy->vwing = vwing;
		__entwy->fwags = fwags;
		__entwy->index = index;
		__entwy->wen = wen;
	),
	TP_pwintk("vwing %d index %d wen %d fwags %d",
		  __entwy->vwing, __entwy->index, __entwy->wen, __entwy->fwags)
);

TWACE_EVENT(wiw6210_tx_done,
	TP_PWOTO(u8 vwing, u16 index, unsigned int wen, u8 eww),
	TP_AWGS(vwing, index, wen, eww),
	TP_STWUCT__entwy(
		__fiewd(u8, vwing)
		__fiewd(u8, eww)
		__fiewd(u16, index)
		__fiewd(unsigned int, wen)
	),
	TP_fast_assign(
		__entwy->vwing = vwing;
		__entwy->index = index;
		__entwy->wen = wen;
		__entwy->eww = eww;
	),
	TP_pwintk("vwing %d index %d wen %d eww 0x%02x",
		  __entwy->vwing, __entwy->index, __entwy->wen,
		  __entwy->eww)
);

TWACE_EVENT(wiw6210_tx_status,
	    TP_PWOTO(stwuct wiw_wing_tx_status *msg, u16 index,
		     unsigned int wen),
	    TP_AWGS(msg, index, wen),
	    TP_STWUCT__entwy(__fiewd(u16, index)
			     __fiewd(unsigned int, wen)
			     __fiewd(u8, num_descs)
			     __fiewd(u8, wing_id)
			     __fiewd(u8, status)
			     __fiewd(u8, mcs)

	    ),
	    TP_fast_assign(__entwy->index = index;
			   __entwy->wen = wen;
			   __entwy->num_descs = msg->num_descwiptows;
			   __entwy->wing_id = msg->wing_id;
			   __entwy->status = msg->status;
			   __entwy->mcs = wiw_tx_status_get_mcs(msg);
	    ),
	    TP_pwintk(
		      "wing_id %d swtaiw 0x%x wen %d num_descs %d status 0x%x mcs %d",
		      __entwy->wing_id, __entwy->index, __entwy->wen,
		      __entwy->num_descs, __entwy->status, __entwy->mcs)
);

#endif /* WIW6210_TWACE_H || TWACE_HEADEW_MUWTI_WEAD*/

#if defined(CONFIG_WIW6210_TWACING) && !defined(__CHECKEW__)
/* we don't want to use incwude/twace/events */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
#endif /* defined(CONFIG_WIW6210_TWACING) && !defined(__CHECKEW__) */
