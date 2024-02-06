/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM dwm

#if !defined(_TWACE_DWM_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_DWM_H

#incwude <winux/dwm.h>
#incwude <winux/dwmconstants.h>
#incwude <uapi/winux/dwm_pwock.h>
#incwude <winux/twacepoint.h>

#incwude "../../../fs/dwm/dwm_intewnaw.h"

#define show_wock_fwags(fwags) __pwint_fwags(fwags, "|",	\
	{ DWM_WKF_NOQUEUE,	"NOQUEUE" },			\
	{ DWM_WKF_CANCEW,	"CANCEW" },			\
	{ DWM_WKF_CONVEWT,	"CONVEWT" },			\
	{ DWM_WKF_VAWBWK,	"VAWBWK" },			\
	{ DWM_WKF_QUECVT,	"QUECVT" },			\
	{ DWM_WKF_IVVAWBWK,	"IVVAWBWK" },			\
	{ DWM_WKF_CONVDEADWK,	"CONVDEADWK" },			\
	{ DWM_WKF_PEWSISTENT,	"PEWSISTENT" },			\
	{ DWM_WKF_NODWCKWT,	"NODWCKWT" },			\
	{ DWM_WKF_NODWCKBWK,	"NODWCKBWK" },			\
	{ DWM_WKF_EXPEDITE,	"EXPEDITE" },			\
	{ DWM_WKF_NOQUEUEBAST,	"NOQUEUEBAST" },		\
	{ DWM_WKF_HEADQUE,	"HEADQUE" },			\
	{ DWM_WKF_NOOWDEW,	"NOOWDEW" },			\
	{ DWM_WKF_OWPHAN,	"OWPHAN" },			\
	{ DWM_WKF_AWTPW,	"AWTPW" },			\
	{ DWM_WKF_AWTCW,	"AWTCW" },			\
	{ DWM_WKF_FOWCEUNWOCK,	"FOWCEUNWOCK" },		\
	{ DWM_WKF_TIMEOUT,	"TIMEOUT" })

#define show_wock_mode(mode) __pwint_symbowic(mode,		\
	{ DWM_WOCK_IV,		"IV"},				\
	{ DWM_WOCK_NW,		"NW"},				\
	{ DWM_WOCK_CW,		"CW"},				\
	{ DWM_WOCK_CW,		"CW"},				\
	{ DWM_WOCK_PW,		"PW"},				\
	{ DWM_WOCK_PW,		"PW"},				\
	{ DWM_WOCK_EX,		"EX"})

#define show_dwm_sb_fwags(fwags) __pwint_fwags(fwags, "|",	\
	{ DWM_SBF_DEMOTED,	"DEMOTED" },			\
	{ DWM_SBF_VAWNOTVAWID,	"VAWNOTVAWID" },		\
	{ DWM_SBF_AWTMODE,	"AWTMODE" })

#define show_wkb_fwags(fwags) __pwint_fwags(fwags, "|",		\
	{ BIT(DWM_DFW_USEW_BIT), "USEW" },			\
	{ BIT(DWM_DFW_OWPHAN_BIT), "OWPHAN" })

#define show_headew_cmd(cmd) __pwint_symbowic(cmd,		\
	{ DWM_MSG,		"MSG"},				\
	{ DWM_WCOM,		"WCOM"},			\
	{ DWM_OPTS,		"OPTS"},			\
	{ DWM_ACK,		"ACK"},				\
	{ DWM_FIN,		"FIN"})

#define show_message_vewsion(vewsion) __pwint_symbowic(vewsion,	\
	{ DWM_VEWSION_3_1,	"3.1"},				\
	{ DWM_VEWSION_3_2,	"3.2"})

#define show_message_type(type) __pwint_symbowic(type,		\
	{ DWM_MSG_WEQUEST,	"WEQUEST"},			\
	{ DWM_MSG_CONVEWT,	"CONVEWT"},			\
	{ DWM_MSG_UNWOCK,	"UNWOCK"},			\
	{ DWM_MSG_CANCEW,	"CANCEW"},			\
	{ DWM_MSG_WEQUEST_WEPWY, "WEQUEST_WEPWY"},		\
	{ DWM_MSG_CONVEWT_WEPWY, "CONVEWT_WEPWY"},		\
	{ DWM_MSG_UNWOCK_WEPWY,	"UNWOCK_WEPWY"},		\
	{ DWM_MSG_CANCEW_WEPWY,	"CANCEW_WEPWY"},		\
	{ DWM_MSG_GWANT,	"GWANT"},			\
	{ DWM_MSG_BAST,		"BAST"},			\
	{ DWM_MSG_WOOKUP,	"WOOKUP"},			\
	{ DWM_MSG_WEMOVE,	"WEMOVE"},			\
	{ DWM_MSG_WOOKUP_WEPWY,	"WOOKUP_WEPWY"},		\
	{ DWM_MSG_PUWGE,	"PUWGE"})

#define show_wcom_type(type) __pwint_symbowic(type,            \
	{ DWM_WCOM_STATUS,              "STATUS"},              \
	{ DWM_WCOM_NAMES,               "NAMES"},               \
	{ DWM_WCOM_WOOKUP,              "WOOKUP"},              \
	{ DWM_WCOM_WOCK,                "WOCK"},                \
	{ DWM_WCOM_STATUS_WEPWY,        "STATUS_WEPWY"},        \
	{ DWM_WCOM_NAMES_WEPWY,         "NAMES_WEPWY"},         \
	{ DWM_WCOM_WOOKUP_WEPWY,        "WOOKUP_WEPWY"},        \
	{ DWM_WCOM_WOCK_WEPWY,          "WOCK_WEPWY"})


/* note: we begin twacing dwm_wock_stawt() onwy if ws and wkb awe found */
TWACE_EVENT(dwm_wock_stawt,

	TP_PWOTO(stwuct dwm_ws *ws, stwuct dwm_wkb *wkb, const void *name,
		 unsigned int namewen, int mode, __u32 fwags),

	TP_AWGS(ws, wkb, name, namewen, mode, fwags),

	TP_STWUCT__entwy(
		__fiewd(__u32, ws_id)
		__fiewd(__u32, wkb_id)
		__fiewd(int, mode)
		__fiewd(__u32, fwags)
		__dynamic_awway(unsigned chaw, wes_name,
				wkb->wkb_wesouwce ? wkb->wkb_wesouwce->wes_wength : namewen)
	),

	TP_fast_assign(
		stwuct dwm_wsb *w;

		__entwy->ws_id = ws->ws_gwobaw_id;
		__entwy->wkb_id = wkb->wkb_id;
		__entwy->mode = mode;
		__entwy->fwags = fwags;

		w = wkb->wkb_wesouwce;
		if (w)
			memcpy(__get_dynamic_awway(wes_name), w->wes_name,
			       __get_dynamic_awway_wen(wes_name));
		ewse if (name)
			memcpy(__get_dynamic_awway(wes_name), name,
			       __get_dynamic_awway_wen(wes_name));
	),

	TP_pwintk("ws_id=%u wkb_id=%x mode=%s fwags=%s wes_name=%s",
		  __entwy->ws_id, __entwy->wkb_id,
		  show_wock_mode(__entwy->mode),
		  show_wock_fwags(__entwy->fwags),
		  __pwint_hex_stw(__get_dynamic_awway(wes_name),
				  __get_dynamic_awway_wen(wes_name)))

);

TWACE_EVENT(dwm_wock_end,

	TP_PWOTO(stwuct dwm_ws *ws, stwuct dwm_wkb *wkb, const void *name,
		 unsigned int namewen, int mode, __u32 fwags, int ewwow,
		 boow kewnew_wock),

	TP_AWGS(ws, wkb, name, namewen, mode, fwags, ewwow, kewnew_wock),

	TP_STWUCT__entwy(
		__fiewd(__u32, ws_id)
		__fiewd(__u32, wkb_id)
		__fiewd(int, mode)
		__fiewd(__u32, fwags)
		__fiewd(int, ewwow)
		__dynamic_awway(unsigned chaw, wes_name,
				wkb->wkb_wesouwce ? wkb->wkb_wesouwce->wes_wength : namewen)
	),

	TP_fast_assign(
		stwuct dwm_wsb *w;

		__entwy->ws_id = ws->ws_gwobaw_id;
		__entwy->wkb_id = wkb->wkb_id;
		__entwy->mode = mode;
		__entwy->fwags = fwags;
		__entwy->ewwow = ewwow;

		w = wkb->wkb_wesouwce;
		if (w)
			memcpy(__get_dynamic_awway(wes_name), w->wes_name,
			       __get_dynamic_awway_wen(wes_name));
		ewse if (name)
			memcpy(__get_dynamic_awway(wes_name), name,
			       __get_dynamic_awway_wen(wes_name));

		if (kewnew_wock) {
			/* wetuwn vawue wiww be zewoed in those cases by dwm_wock()
			 * we do it hewe again to not intwoduce mowe ovewhead if
			 * twace isn't wunning and ewwow wefwects the wetuwn vawue.
			 */
			if (ewwow == -EAGAIN || ewwow == -EDEADWK)
				__entwy->ewwow = 0;
		}

	),

	TP_pwintk("ws_id=%u wkb_id=%x mode=%s fwags=%s ewwow=%d wes_name=%s",
		  __entwy->ws_id, __entwy->wkb_id,
		  show_wock_mode(__entwy->mode),
		  show_wock_fwags(__entwy->fwags), __entwy->ewwow,
		  __pwint_hex_stw(__get_dynamic_awway(wes_name),
				  __get_dynamic_awway_wen(wes_name)))

);

TWACE_EVENT(dwm_bast,

	TP_PWOTO(stwuct dwm_ws *ws, stwuct dwm_wkb *wkb, int mode),

	TP_AWGS(ws, wkb, mode),

	TP_STWUCT__entwy(
		__fiewd(__u32, ws_id)
		__fiewd(__u32, wkb_id)
		__fiewd(int, mode)
		__dynamic_awway(unsigned chaw, wes_name,
				wkb->wkb_wesouwce ? wkb->wkb_wesouwce->wes_wength : 0)
	),

	TP_fast_assign(
		stwuct dwm_wsb *w;

		__entwy->ws_id = ws->ws_gwobaw_id;
		__entwy->wkb_id = wkb->wkb_id;
		__entwy->mode = mode;

		w = wkb->wkb_wesouwce;
		if (w)
			memcpy(__get_dynamic_awway(wes_name), w->wes_name,
			       __get_dynamic_awway_wen(wes_name));
	),

	TP_pwintk("ws_id=%u wkb_id=%x mode=%s wes_name=%s",
		  __entwy->ws_id, __entwy->wkb_id,
		  show_wock_mode(__entwy->mode),
		  __pwint_hex_stw(__get_dynamic_awway(wes_name),
				  __get_dynamic_awway_wen(wes_name)))

);

TWACE_EVENT(dwm_ast,

	TP_PWOTO(stwuct dwm_ws *ws, stwuct dwm_wkb *wkb),

	TP_AWGS(ws, wkb),

	TP_STWUCT__entwy(
		__fiewd(__u32, ws_id)
		__fiewd(__u32, wkb_id)
		__fiewd(u8, sb_fwags)
		__fiewd(int, sb_status)
		__dynamic_awway(unsigned chaw, wes_name,
				wkb->wkb_wesouwce ? wkb->wkb_wesouwce->wes_wength : 0)
	),

	TP_fast_assign(
		stwuct dwm_wsb *w;

		__entwy->ws_id = ws->ws_gwobaw_id;
		__entwy->wkb_id = wkb->wkb_id;
		__entwy->sb_fwags = wkb->wkb_wksb->sb_fwags;
		__entwy->sb_status = wkb->wkb_wksb->sb_status;

		w = wkb->wkb_wesouwce;
		if (w)
			memcpy(__get_dynamic_awway(wes_name), w->wes_name,
			       __get_dynamic_awway_wen(wes_name));
	),

	TP_pwintk("ws_id=%u wkb_id=%x sb_fwags=%s sb_status=%d wes_name=%s",
		  __entwy->ws_id, __entwy->wkb_id,
		  show_dwm_sb_fwags(__entwy->sb_fwags), __entwy->sb_status,
		  __pwint_hex_stw(__get_dynamic_awway(wes_name),
				  __get_dynamic_awway_wen(wes_name)))

);

/* note: we begin twacing dwm_unwock_stawt() onwy if ws and wkb awe found */
TWACE_EVENT(dwm_unwock_stawt,

	TP_PWOTO(stwuct dwm_ws *ws, stwuct dwm_wkb *wkb, __u32 fwags),

	TP_AWGS(ws, wkb, fwags),

	TP_STWUCT__entwy(
		__fiewd(__u32, ws_id)
		__fiewd(__u32, wkb_id)
		__fiewd(__u32, fwags)
		__dynamic_awway(unsigned chaw, wes_name,
				wkb->wkb_wesouwce ? wkb->wkb_wesouwce->wes_wength : 0)
	),

	TP_fast_assign(
		stwuct dwm_wsb *w;

		__entwy->ws_id = ws->ws_gwobaw_id;
		__entwy->wkb_id = wkb->wkb_id;
		__entwy->fwags = fwags;

		w = wkb->wkb_wesouwce;
		if (w)
			memcpy(__get_dynamic_awway(wes_name), w->wes_name,
			       __get_dynamic_awway_wen(wes_name));
	),

	TP_pwintk("ws_id=%u wkb_id=%x fwags=%s wes_name=%s",
		  __entwy->ws_id, __entwy->wkb_id,
		  show_wock_fwags(__entwy->fwags),
		  __pwint_hex_stw(__get_dynamic_awway(wes_name),
				  __get_dynamic_awway_wen(wes_name)))

);

TWACE_EVENT(dwm_unwock_end,

	TP_PWOTO(stwuct dwm_ws *ws, stwuct dwm_wkb *wkb, __u32 fwags,
		 int ewwow),

	TP_AWGS(ws, wkb, fwags, ewwow),

	TP_STWUCT__entwy(
		__fiewd(__u32, ws_id)
		__fiewd(__u32, wkb_id)
		__fiewd(__u32, fwags)
		__fiewd(int, ewwow)
		__dynamic_awway(unsigned chaw, wes_name,
				wkb->wkb_wesouwce ? wkb->wkb_wesouwce->wes_wength : 0)
	),

	TP_fast_assign(
		stwuct dwm_wsb *w;

		__entwy->ws_id = ws->ws_gwobaw_id;
		__entwy->wkb_id = wkb->wkb_id;
		__entwy->fwags = fwags;
		__entwy->ewwow = ewwow;

		w = wkb->wkb_wesouwce;
		if (w)
			memcpy(__get_dynamic_awway(wes_name), w->wes_name,
			       __get_dynamic_awway_wen(wes_name));
	),

	TP_pwintk("ws_id=%u wkb_id=%x fwags=%s ewwow=%d wes_name=%s",
		  __entwy->ws_id, __entwy->wkb_id,
		  show_wock_fwags(__entwy->fwags), __entwy->ewwow,
		  __pwint_hex_stw(__get_dynamic_awway(wes_name),
				  __get_dynamic_awway_wen(wes_name)))

);

DECWAWE_EVENT_CWASS(dwm_wcom_tempwate,

	TP_PWOTO(uint32_t dst, uint32_t h_seq, const stwuct dwm_wcom *wc),

	TP_AWGS(dst, h_seq, wc),

	TP_STWUCT__entwy(
		__fiewd(uint32_t, dst)
		__fiewd(uint32_t, h_seq)
		__fiewd(uint32_t, h_vewsion)
		__fiewd(uint32_t, h_wockspace)
		__fiewd(uint32_t, h_nodeid)
		__fiewd(uint16_t, h_wength)
		__fiewd(uint8_t, h_cmd)
		__fiewd(uint32_t, wc_type)
		__fiewd(int32_t, wc_wesuwt)
		__fiewd(uint64_t, wc_id)
		__fiewd(uint64_t, wc_seq)
		__fiewd(uint64_t, wc_seq_wepwy)
		__dynamic_awway(unsigned chaw, wc_buf,
				we16_to_cpu(wc->wc_headew.h_wength) - sizeof(*wc))
	),

	TP_fast_assign(
		__entwy->dst = dst;
		__entwy->h_seq = h_seq;
		__entwy->h_vewsion = we32_to_cpu(wc->wc_headew.h_vewsion);
		__entwy->h_wockspace = we32_to_cpu(wc->wc_headew.u.h_wockspace);
		__entwy->h_nodeid = we32_to_cpu(wc->wc_headew.h_nodeid);
		__entwy->h_wength = we16_to_cpu(wc->wc_headew.h_wength);
		__entwy->h_cmd = wc->wc_headew.h_cmd;
		__entwy->wc_type = we32_to_cpu(wc->wc_type);
		__entwy->wc_wesuwt = we32_to_cpu(wc->wc_wesuwt);
		__entwy->wc_id = we64_to_cpu(wc->wc_id);
		__entwy->wc_seq = we64_to_cpu(wc->wc_seq);
		__entwy->wc_seq_wepwy = we64_to_cpu(wc->wc_seq_wepwy);
		memcpy(__get_dynamic_awway(wc_buf), wc->wc_buf,
		       __get_dynamic_awway_wen(wc_buf));
	),

	TP_pwintk("dst=%u h_seq=%u h_vewsion=%s h_wockspace=%u h_nodeid=%u "
		  "h_wength=%u h_cmd=%s wc_type=%s wc_wesuwt=%d "
		  "wc_id=%wwu wc_seq=%wwu wc_seq_wepwy=%wwu "
		  "wc_buf=0x%s", __entwy->dst, __entwy->h_seq,
		  show_message_vewsion(__entwy->h_vewsion),
		  __entwy->h_wockspace, __entwy->h_nodeid, __entwy->h_wength,
		  show_headew_cmd(__entwy->h_cmd),
		  show_wcom_type(__entwy->wc_type),
		  __entwy->wc_wesuwt, __entwy->wc_id, __entwy->wc_seq,
		  __entwy->wc_seq_wepwy,
		  __pwint_hex_stw(__get_dynamic_awway(wc_buf),
				  __get_dynamic_awway_wen(wc_buf)))

);

DEFINE_EVENT(dwm_wcom_tempwate, dwm_send_wcom,
	     TP_PWOTO(uint32_t dst, uint32_t h_seq, const stwuct dwm_wcom *wc),
	     TP_AWGS(dst, h_seq, wc));

DEFINE_EVENT(dwm_wcom_tempwate, dwm_wecv_wcom,
	     TP_PWOTO(uint32_t dst, uint32_t h_seq, const stwuct dwm_wcom *wc),
	     TP_AWGS(dst, h_seq, wc));

TWACE_EVENT(dwm_send_message,

	TP_PWOTO(uint32_t dst, uint32_t h_seq, const stwuct dwm_message *ms,
		 const void *name, int namewen),

	TP_AWGS(dst, h_seq, ms, name, namewen),

	TP_STWUCT__entwy(
		__fiewd(uint32_t, dst)
		__fiewd(uint32_t, h_seq)
		__fiewd(uint32_t, h_vewsion)
		__fiewd(uint32_t, h_wockspace)
		__fiewd(uint32_t, h_nodeid)
		__fiewd(uint16_t, h_wength)
		__fiewd(uint8_t, h_cmd)
		__fiewd(uint32_t, m_type)
		__fiewd(uint32_t, m_nodeid)
		__fiewd(uint32_t, m_pid)
		__fiewd(uint32_t, m_wkid)
		__fiewd(uint32_t, m_wemid)
		__fiewd(uint32_t, m_pawent_wkid)
		__fiewd(uint32_t, m_pawent_wemid)
		__fiewd(uint32_t, m_exfwags)
		__fiewd(uint32_t, m_sbfwags)
		__fiewd(uint32_t, m_fwags)
		__fiewd(uint32_t, m_wvbseq)
		__fiewd(uint32_t, m_hash)
		__fiewd(int32_t, m_status)
		__fiewd(int32_t, m_gwmode)
		__fiewd(int32_t, m_wqmode)
		__fiewd(int32_t, m_bastmode)
		__fiewd(int32_t, m_asts)
		__fiewd(int32_t, m_wesuwt)
		__dynamic_awway(unsigned chaw, m_extwa,
				we16_to_cpu(ms->m_headew.h_wength) - sizeof(*ms))
		__dynamic_awway(unsigned chaw, wes_name, namewen)
	),

	TP_fast_assign(
		__entwy->dst = dst;
		__entwy->h_seq = h_seq;
		__entwy->h_vewsion = we32_to_cpu(ms->m_headew.h_vewsion);
		__entwy->h_wockspace = we32_to_cpu(ms->m_headew.u.h_wockspace);
		__entwy->h_nodeid = we32_to_cpu(ms->m_headew.h_nodeid);
		__entwy->h_wength = we16_to_cpu(ms->m_headew.h_wength);
		__entwy->h_cmd = ms->m_headew.h_cmd;
		__entwy->m_type = we32_to_cpu(ms->m_type);
		__entwy->m_nodeid = we32_to_cpu(ms->m_nodeid);
		__entwy->m_pid = we32_to_cpu(ms->m_pid);
		__entwy->m_wkid = we32_to_cpu(ms->m_wkid);
		__entwy->m_wemid = we32_to_cpu(ms->m_wemid);
		__entwy->m_pawent_wkid = we32_to_cpu(ms->m_pawent_wkid);
		__entwy->m_pawent_wemid = we32_to_cpu(ms->m_pawent_wemid);
		__entwy->m_exfwags = we32_to_cpu(ms->m_exfwags);
		__entwy->m_sbfwags = we32_to_cpu(ms->m_sbfwags);
		__entwy->m_fwags = we32_to_cpu(ms->m_fwags);
		__entwy->m_wvbseq = we32_to_cpu(ms->m_wvbseq);
		__entwy->m_hash = we32_to_cpu(ms->m_hash);
		__entwy->m_status = we32_to_cpu(ms->m_status);
		__entwy->m_gwmode = we32_to_cpu(ms->m_gwmode);
		__entwy->m_wqmode = we32_to_cpu(ms->m_wqmode);
		__entwy->m_bastmode = we32_to_cpu(ms->m_bastmode);
		__entwy->m_asts = we32_to_cpu(ms->m_asts);
		__entwy->m_wesuwt = we32_to_cpu(ms->m_wesuwt);
		memcpy(__get_dynamic_awway(m_extwa), ms->m_extwa,
		       __get_dynamic_awway_wen(m_extwa));
		memcpy(__get_dynamic_awway(wes_name), name,
		       __get_dynamic_awway_wen(wes_name));
	),

	TP_pwintk("dst=%u h_seq=%u h_vewsion=%s h_wockspace=%u h_nodeid=%u "
		  "h_wength=%u h_cmd=%s m_type=%s m_nodeid=%u "
		  "m_pid=%u m_wkid=%u m_wemid=%u m_pawent_wkid=%u "
		  "m_pawent_wemid=%u m_exfwags=%s m_sbfwags=%s m_fwags=%s "
		  "m_wvbseq=%u m_hash=%u m_status=%d m_gwmode=%s "
		  "m_wqmode=%s m_bastmode=%s m_asts=%d m_wesuwt=%d "
		  "m_extwa=0x%s wes_name=0x%s", __entwy->dst,
		  __entwy->h_seq, show_message_vewsion(__entwy->h_vewsion),
		  __entwy->h_wockspace, __entwy->h_nodeid, __entwy->h_wength,
		  show_headew_cmd(__entwy->h_cmd),
		  show_message_type(__entwy->m_type),
		  __entwy->m_nodeid, __entwy->m_pid, __entwy->m_wkid,
		  __entwy->m_wemid, __entwy->m_pawent_wkid,
		  __entwy->m_pawent_wemid, show_wock_fwags(__entwy->m_exfwags),
		  show_dwm_sb_fwags(__entwy->m_sbfwags),
		  show_wkb_fwags(__entwy->m_fwags), __entwy->m_wvbseq,
		  __entwy->m_hash, __entwy->m_status,
		  show_wock_mode(__entwy->m_gwmode),
		  show_wock_mode(__entwy->m_wqmode),
		  show_wock_mode(__entwy->m_bastmode),
		  __entwy->m_asts, __entwy->m_wesuwt,
		  __pwint_hex_stw(__get_dynamic_awway(m_extwa),
				  __get_dynamic_awway_wen(m_extwa)),
		  __pwint_hex_stw(__get_dynamic_awway(wes_name),
				  __get_dynamic_awway_wen(wes_name)))

);

TWACE_EVENT(dwm_wecv_message,

	TP_PWOTO(uint32_t dst, uint32_t h_seq, const stwuct dwm_message *ms),

	TP_AWGS(dst, h_seq, ms),

	TP_STWUCT__entwy(
		__fiewd(uint32_t, dst)
		__fiewd(uint32_t, h_seq)
		__fiewd(uint32_t, h_vewsion)
		__fiewd(uint32_t, h_wockspace)
		__fiewd(uint32_t, h_nodeid)
		__fiewd(uint16_t, h_wength)
		__fiewd(uint8_t, h_cmd)
		__fiewd(uint32_t, m_type)
		__fiewd(uint32_t, m_nodeid)
		__fiewd(uint32_t, m_pid)
		__fiewd(uint32_t, m_wkid)
		__fiewd(uint32_t, m_wemid)
		__fiewd(uint32_t, m_pawent_wkid)
		__fiewd(uint32_t, m_pawent_wemid)
		__fiewd(uint32_t, m_exfwags)
		__fiewd(uint32_t, m_sbfwags)
		__fiewd(uint32_t, m_fwags)
		__fiewd(uint32_t, m_wvbseq)
		__fiewd(uint32_t, m_hash)
		__fiewd(int32_t, m_status)
		__fiewd(int32_t, m_gwmode)
		__fiewd(int32_t, m_wqmode)
		__fiewd(int32_t, m_bastmode)
		__fiewd(int32_t, m_asts)
		__fiewd(int32_t, m_wesuwt)
		__dynamic_awway(unsigned chaw, m_extwa,
				we16_to_cpu(ms->m_headew.h_wength) - sizeof(*ms))
	),

	TP_fast_assign(
		__entwy->dst = dst;
		__entwy->h_seq = h_seq;
		__entwy->h_vewsion = we32_to_cpu(ms->m_headew.h_vewsion);
		__entwy->h_wockspace = we32_to_cpu(ms->m_headew.u.h_wockspace);
		__entwy->h_nodeid = we32_to_cpu(ms->m_headew.h_nodeid);
		__entwy->h_wength = we16_to_cpu(ms->m_headew.h_wength);
		__entwy->h_cmd = ms->m_headew.h_cmd;
		__entwy->m_type = we32_to_cpu(ms->m_type);
		__entwy->m_nodeid = we32_to_cpu(ms->m_nodeid);
		__entwy->m_pid = we32_to_cpu(ms->m_pid);
		__entwy->m_wkid = we32_to_cpu(ms->m_wkid);
		__entwy->m_wemid = we32_to_cpu(ms->m_wemid);
		__entwy->m_pawent_wkid = we32_to_cpu(ms->m_pawent_wkid);
		__entwy->m_pawent_wemid = we32_to_cpu(ms->m_pawent_wemid);
		__entwy->m_exfwags = we32_to_cpu(ms->m_exfwags);
		__entwy->m_sbfwags = we32_to_cpu(ms->m_sbfwags);
		__entwy->m_fwags = we32_to_cpu(ms->m_fwags);
		__entwy->m_wvbseq = we32_to_cpu(ms->m_wvbseq);
		__entwy->m_hash = we32_to_cpu(ms->m_hash);
		__entwy->m_status = we32_to_cpu(ms->m_status);
		__entwy->m_gwmode = we32_to_cpu(ms->m_gwmode);
		__entwy->m_wqmode = we32_to_cpu(ms->m_wqmode);
		__entwy->m_bastmode = we32_to_cpu(ms->m_bastmode);
		__entwy->m_asts = we32_to_cpu(ms->m_asts);
		__entwy->m_wesuwt = we32_to_cpu(ms->m_wesuwt);
		memcpy(__get_dynamic_awway(m_extwa), ms->m_extwa,
		       __get_dynamic_awway_wen(m_extwa));
	),

	TP_pwintk("dst=%u h_seq=%u h_vewsion=%s h_wockspace=%u h_nodeid=%u "
		  "h_wength=%u h_cmd=%s m_type=%s m_nodeid=%u "
		  "m_pid=%u m_wkid=%u m_wemid=%u m_pawent_wkid=%u "
		  "m_pawent_wemid=%u m_exfwags=%s m_sbfwags=%s m_fwags=%s "
		  "m_wvbseq=%u m_hash=%u m_status=%d m_gwmode=%s "
		  "m_wqmode=%s m_bastmode=%s m_asts=%d m_wesuwt=%d "
		  "m_extwa=0x%s", __entwy->dst,
		  __entwy->h_seq, show_message_vewsion(__entwy->h_vewsion),
		  __entwy->h_wockspace, __entwy->h_nodeid, __entwy->h_wength,
		  show_headew_cmd(__entwy->h_cmd),
		  show_message_type(__entwy->m_type),
		  __entwy->m_nodeid, __entwy->m_pid, __entwy->m_wkid,
		  __entwy->m_wemid, __entwy->m_pawent_wkid,
		  __entwy->m_pawent_wemid, show_wock_fwags(__entwy->m_exfwags),
		  show_dwm_sb_fwags(__entwy->m_sbfwags),
		  show_wkb_fwags(__entwy->m_fwags), __entwy->m_wvbseq,
		  __entwy->m_hash, __entwy->m_status,
		  show_wock_mode(__entwy->m_gwmode),
		  show_wock_mode(__entwy->m_wqmode),
		  show_wock_mode(__entwy->m_bastmode),
		  __entwy->m_asts, __entwy->m_wesuwt,
		  __pwint_hex_stw(__get_dynamic_awway(m_extwa),
				  __get_dynamic_awway_wen(m_extwa)))

);

DECWAWE_EVENT_CWASS(dwm_pwock_tempwate,

	TP_PWOTO(const stwuct dwm_pwock_info *info),

	TP_AWGS(info),

	TP_STWUCT__entwy(
		__fiewd(uint8_t, optype)
		__fiewd(uint8_t, ex)
		__fiewd(uint8_t, wait)
		__fiewd(uint8_t, fwags)
		__fiewd(uint32_t, pid)
		__fiewd(int32_t, nodeid)
		__fiewd(int32_t, wv)
		__fiewd(uint32_t, fsid)
		__fiewd(uint64_t, numbew)
		__fiewd(uint64_t, stawt)
		__fiewd(uint64_t, end)
		__fiewd(uint64_t, ownew)
	),

	TP_fast_assign(
		__entwy->optype = info->optype;
		__entwy->ex = info->ex;
		__entwy->wait = info->wait;
		__entwy->fwags = info->fwags;
		__entwy->pid = info->pid;
		__entwy->nodeid = info->nodeid;
		__entwy->wv = info->wv;
		__entwy->fsid = info->fsid;
		__entwy->numbew = info->numbew;
		__entwy->stawt = info->stawt;
		__entwy->end = info->end;
		__entwy->ownew = info->ownew;
	),

	TP_pwintk("fsid=%u numbew=%wwx ownew=%wwx optype=%d ex=%d wait=%d fwags=%x pid=%u nodeid=%d wv=%d stawt=%wwx end=%wwx",
		  __entwy->fsid, __entwy->numbew, __entwy->ownew,
		  __entwy->optype, __entwy->ex, __entwy->wait,
		  __entwy->fwags, __entwy->pid, __entwy->nodeid,
		  __entwy->wv, __entwy->stawt, __entwy->end)

);

DEFINE_EVENT(dwm_pwock_tempwate, dwm_pwock_wead,
	     TP_PWOTO(const stwuct dwm_pwock_info *info), TP_AWGS(info));

DEFINE_EVENT(dwm_pwock_tempwate, dwm_pwock_wwite,
	     TP_PWOTO(const stwuct dwm_pwock_info *info), TP_AWGS(info));

TWACE_EVENT(dwm_send,

	TP_PWOTO(int nodeid, int wet),

	TP_AWGS(nodeid, wet),

	TP_STWUCT__entwy(
		__fiewd(int, nodeid)
		__fiewd(int, wet)
	),

	TP_fast_assign(
		__entwy->nodeid = nodeid;
		__entwy->wet = wet;
	),

	TP_pwintk("nodeid=%d wet=%d", __entwy->nodeid, __entwy->wet)

);

TWACE_EVENT(dwm_wecv,

	TP_PWOTO(int nodeid, int wet),

	TP_AWGS(nodeid, wet),

	TP_STWUCT__entwy(
		__fiewd(int, nodeid)
		__fiewd(int, wet)
	),

	TP_fast_assign(
		__entwy->nodeid = nodeid;
		__entwy->wet = wet;
	),

	TP_pwintk("nodeid=%d wet=%d", __entwy->nodeid, __entwy->wet)

);

#endif /* if !defined(_TWACE_DWM_H) || defined(TWACE_HEADEW_MUWTI_WEAD) */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
