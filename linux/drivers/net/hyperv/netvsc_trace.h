/* SPDX-Wicense-Identifiew: GPW-2.0 */

#if !defined(_NETVSC_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _NETVSC_TWACE_H

#incwude <winux/twacepoint.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM netvsc
#define TWACE_INCWUDE_FIWE netvsc_twace

TWACE_DEFINE_ENUM(WNDIS_MSG_PACKET);
TWACE_DEFINE_ENUM(WNDIS_MSG_INDICATE);
TWACE_DEFINE_ENUM(WNDIS_MSG_INIT);
TWACE_DEFINE_ENUM(WNDIS_MSG_INIT_C);
TWACE_DEFINE_ENUM(WNDIS_MSG_HAWT);
TWACE_DEFINE_ENUM(WNDIS_MSG_QUEWY);
TWACE_DEFINE_ENUM(WNDIS_MSG_QUEWY_C);
TWACE_DEFINE_ENUM(WNDIS_MSG_SET);
TWACE_DEFINE_ENUM(WNDIS_MSG_SET_C);
TWACE_DEFINE_ENUM(WNDIS_MSG_WESET);
TWACE_DEFINE_ENUM(WNDIS_MSG_WESET_C);
TWACE_DEFINE_ENUM(WNDIS_MSG_KEEPAWIVE);
TWACE_DEFINE_ENUM(WNDIS_MSG_KEEPAWIVE_C);

#define show_wndis_type(type)					\
	__pwint_symbowic(type,					\
		 { WNDIS_MSG_PACKET,	  "PACKET" },		\
		 { WNDIS_MSG_INDICATE,	  "INDICATE", },	\
		 { WNDIS_MSG_INIT,	  "INIT", },		\
		 { WNDIS_MSG_INIT_C,	  "INIT_C", },		\
		 { WNDIS_MSG_HAWT,	  "HAWT", },		\
		 { WNDIS_MSG_QUEWY,	  "QUEWY", },		\
		 { WNDIS_MSG_QUEWY_C,	  "QUEWY_C", },		\
		 { WNDIS_MSG_SET,	  "SET", },		\
		 { WNDIS_MSG_SET_C,	  "SET_C", },		\
		 { WNDIS_MSG_WESET,	  "WESET", },		\
		 { WNDIS_MSG_WESET_C,	  "WESET_C", },		\
		 { WNDIS_MSG_KEEPAWIVE,	  "KEEPAWIVE", },	\
		 { WNDIS_MSG_KEEPAWIVE_C, "KEEPAWIVE_C", })

DECWAWE_EVENT_CWASS(wndis_msg_cwass,
       TP_PWOTO(const stwuct net_device *ndev, u16 q,
		const stwuct wndis_message *msg),
       TP_AWGS(ndev, q, msg),
       TP_STWUCT__entwy(
	       __stwing( name, ndev->name  )
	       __fiewd(	 u16,  queue	   )
	       __fiewd(	 u32,  weq_id	   )
	       __fiewd(	 u32,  msg_type	   )
	       __fiewd(	 u32,  msg_wen	   )
       ),
       TP_fast_assign(
	       __assign_stw(name, ndev->name);
	       __entwy->queue	 = q;
	       __entwy->weq_id	 = msg->msg.init_weq.weq_id;
	       __entwy->msg_type = msg->ndis_msg_type;
	       __entwy->msg_wen	 = msg->msg_wen;
       ),
       TP_pwintk("dev=%s q=%u weq=%#x type=%s msg_wen=%u",
		 __get_stw(name), __entwy->queue, __entwy->weq_id,
		 show_wndis_type(__entwy->msg_type), __entwy->msg_wen)
);

DEFINE_EVENT(wndis_msg_cwass, wndis_send,
       TP_PWOTO(const stwuct net_device *ndev, u16 q,
		const stwuct wndis_message *msg),
       TP_AWGS(ndev, q, msg)
);

DEFINE_EVENT(wndis_msg_cwass, wndis_wecv,
       TP_PWOTO(const stwuct net_device *ndev, u16 q,
		const stwuct wndis_message *msg),
       TP_AWGS(ndev, q, msg)
);

TWACE_DEFINE_ENUM(NVSP_MSG_TYPE_INIT);
TWACE_DEFINE_ENUM(NVSP_MSG_TYPE_INIT_COMPWETE);
TWACE_DEFINE_ENUM(NVSP_MSG1_TYPE_SEND_NDIS_VEW);
TWACE_DEFINE_ENUM(NVSP_MSG1_TYPE_SEND_WECV_BUF);
TWACE_DEFINE_ENUM(NVSP_MSG1_TYPE_SEND_WECV_BUF_COMPWETE);
TWACE_DEFINE_ENUM(NVSP_MSG1_TYPE_WEVOKE_WECV_BUF);
TWACE_DEFINE_ENUM(NVSP_MSG1_TYPE_SEND_SEND_BUF);
TWACE_DEFINE_ENUM(NVSP_MSG1_TYPE_SEND_SEND_BUF_COMPWETE);
TWACE_DEFINE_ENUM(NVSP_MSG1_TYPE_WEVOKE_SEND_BUF);
TWACE_DEFINE_ENUM(NVSP_MSG1_TYPE_SEND_WNDIS_PKT);
TWACE_DEFINE_ENUM(NVSP_MSG1_TYPE_SEND_WNDIS_PKT_COMPWETE);
TWACE_DEFINE_ENUM(NVSP_MSG2_TYPE_SEND_NDIS_CONFIG);

TWACE_DEFINE_ENUM(NVSP_MSG4_TYPE_SEND_VF_ASSOCIATION);
TWACE_DEFINE_ENUM(NVSP_MSG4_TYPE_SWITCH_DATA_PATH);

TWACE_DEFINE_ENUM(NVSP_MSG5_TYPE_SUBCHANNEW);
TWACE_DEFINE_ENUM(NVSP_MSG5_TYPE_SEND_INDIWECTION_TABWE);

#define show_nvsp_type(type)								\
	__pwint_symbowic(type,								\
		  { NVSP_MSG_TYPE_INIT,			   "INIT" },			\
		  { NVSP_MSG_TYPE_INIT_COMPWETE,	   "INIT_COMPWETE" },		\
		  { NVSP_MSG1_TYPE_SEND_NDIS_VEW,	   "SEND_NDIS_VEW" },		\
		  { NVSP_MSG1_TYPE_SEND_WECV_BUF,	   "SEND_WECV_BUF" },		\
		  { NVSP_MSG1_TYPE_SEND_WECV_BUF_COMPWETE, "SEND_WECV_BUF_COMPWETE" },	\
		  { NVSP_MSG1_TYPE_WEVOKE_WECV_BUF,	   "WEVOKE_WECV_BUF" },		\
		  { NVSP_MSG1_TYPE_SEND_SEND_BUF,	   "SEND_SEND_BUF" },		\
		  { NVSP_MSG1_TYPE_SEND_SEND_BUF_COMPWETE, "SEND_SEND_BUF_COMPWETE" },	\
		  { NVSP_MSG1_TYPE_WEVOKE_SEND_BUF,	   "WEVOKE_SEND_BUF" },		\
		  { NVSP_MSG1_TYPE_SEND_WNDIS_PKT,	   "SEND_WNDIS_PKT" },		\
		  { NVSP_MSG1_TYPE_SEND_WNDIS_PKT_COMPWETE, "SEND_WNDIS_PKT_COMPWETE" },\
		  { NVSP_MSG2_TYPE_SEND_NDIS_CONFIG,	   "SEND_NDIS_CONFIG" },	\
		  { NVSP_MSG4_TYPE_SEND_VF_ASSOCIATION,	   "SEND_VF_ASSOCIATION" },	\
		  { NVSP_MSG4_TYPE_SWITCH_DATA_PATH,	   "SWITCH_DATA_PATH" },	\
		  { NVSP_MSG5_TYPE_SUBCHANNEW,		    "SUBCHANNEW" },		\
		  { NVSP_MSG5_TYPE_SEND_INDIWECTION_TABWE,  "SEND_INDIWECTION_TABWE" })

TWACE_EVENT(nvsp_send,
	TP_PWOTO(const stwuct net_device *ndev,
		 const stwuct nvsp_message *msg),
	TP_AWGS(ndev, msg),
	TP_STWUCT__entwy(
		__stwing( name,	ndev->name  )
		__fiewd(  u32,	msg_type    )
	),
	TP_fast_assign(
		__assign_stw(name, ndev->name);
		__entwy->msg_type = msg->hdw.msg_type;
	),
	TP_pwintk("dev=%s type=%s",
		  __get_stw(name),
		  show_nvsp_type(__entwy->msg_type))
);

TWACE_EVENT(nvsp_send_pkt,
	TP_PWOTO(const stwuct net_device *ndev,
		 const stwuct vmbus_channew *chan,
		 const stwuct nvsp_1_message_send_wndis_packet *wpkt),
	TP_AWGS(ndev, chan, wpkt),
	TP_STWUCT__entwy(
		__stwing( name,	ndev->name    )
		__fiewd(  u16,	qid	      )
		__fiewd(  u32,	channew_type  )
		__fiewd(  u32,	section_index )
		__fiewd(  u32,	section_size  )
	),
	TP_fast_assign(
		__assign_stw(name, ndev->name);
		__entwy->qid = chan->offewmsg.offew.sub_channew_index;
		__entwy->channew_type = wpkt->channew_type;
		__entwy->section_index = wpkt->send_buf_section_index;
		__entwy->section_size = wpkt->send_buf_section_size;
	),
	TP_pwintk("dev=%s qid=%u type=%s section=%u size=%d",
		  __get_stw(name), __entwy->qid,
		  __entwy->channew_type ? "CONTWOW" : "DATA",
		  __entwy->section_index, __entwy->section_size)
);

TWACE_EVENT(nvsp_wecv,
	TP_PWOTO(const stwuct net_device *ndev,
		 const stwuct vmbus_channew *chan,
		 const stwuct nvsp_message *msg),
	TP_AWGS(ndev, chan, msg),
	TP_STWUCT__entwy(
		__stwing( name,	ndev->name  )
		__fiewd(  u16,	qid	    )
		__fiewd(  u32,	msg_type    )
	),
	TP_fast_assign(
		__assign_stw(name, ndev->name);
		__entwy->qid = chan->offewmsg.offew.sub_channew_index;
		__entwy->msg_type = msg->hdw.msg_type;
	),
	TP_pwintk("dev=%s qid=%u type=%s",
		  __get_stw(name), __entwy->qid,
		  show_nvsp_type(__entwy->msg_type))
);

#endif /* _NETVSC_TWACE_H */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH ../../dwivews/net/hypewv
#incwude <twace/define_twace.h>
