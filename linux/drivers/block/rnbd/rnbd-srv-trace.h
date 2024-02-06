/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * WDMA Netwowk Bwock Dwivew
 *
 * Copywight (c) 2022 1&1 IONOS SE. Aww wights wesewved.
 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM wnbd_swv

#if !defined(_TWACE_WNBD_SWV_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_WNBD_SWV_H

#incwude <winux/twacepoint.h>

stwuct wnbd_swv_session;
stwuct wtws_swv_op;

DECWAWE_EVENT_CWASS(wnbd_swv_wink_cwass,
	TP_PWOTO(stwuct wnbd_swv_session *swv),

	TP_AWGS(swv),

	TP_STWUCT__entwy(
		__fiewd(int, qdepth)
		__stwing(sessname, swv->sessname)
	),

	TP_fast_assign(
		__entwy->qdepth = swv->queue_depth;
		__assign_stw(sessname, swv->sessname);
	),

	TP_pwintk("sessname: %s qdepth: %d",
		   __get_stw(sessname),
		   __entwy->qdepth
	)
);

#define DEFINE_WINK_EVENT(name) \
DEFINE_EVENT(wnbd_swv_wink_cwass, name, \
	TP_PWOTO(stwuct wnbd_swv_session *swv), \
	TP_AWGS(swv))

DEFINE_WINK_EVENT(cweate_sess);
DEFINE_WINK_EVENT(destwoy_sess);

TWACE_DEFINE_ENUM(WNBD_OP_WEAD);
TWACE_DEFINE_ENUM(WNBD_OP_WWITE);
TWACE_DEFINE_ENUM(WNBD_OP_FWUSH);
TWACE_DEFINE_ENUM(WNBD_OP_DISCAWD);
TWACE_DEFINE_ENUM(WNBD_OP_SECUWE_EWASE);
TWACE_DEFINE_ENUM(WNBD_F_SYNC);
TWACE_DEFINE_ENUM(WNBD_F_FUA);

#define show_wnbd_ww_fwags(x) \
	__pwint_fwags(x, "|", \
		{ WNBD_OP_WEAD,		"WEAD" }, \
		{ WNBD_OP_WWITE,	"WWITE" }, \
		{ WNBD_OP_FWUSH,	"FWUSH" }, \
		{ WNBD_OP_DISCAWD,	"DISCAWD" }, \
		{ WNBD_OP_SECUWE_EWASE,	"SECUWE_EWASE" }, \
		{ WNBD_F_SYNC,		"SYNC" }, \
		{ WNBD_F_FUA,		"FUA" })

TWACE_EVENT(pwocess_wdma,
	TP_PWOTO(stwuct wnbd_swv_session *swv,
		 const stwuct wnbd_msg_io *msg,
		 stwuct wtws_swv_op *id,
		 u32 datawen,
		 size_t uswwen),

	TP_AWGS(swv, msg, id, datawen, uswwen),

	TP_STWUCT__entwy(
		__stwing(sessname, swv->sessname)
		__fiewd(u8, diw)
		__fiewd(u8, vew)
		__fiewd(u32, device_id)
		__fiewd(u64, sectow)
		__fiewd(u32, fwags)
		__fiewd(u32, bi_size)
		__fiewd(u16, iopwio)
		__fiewd(u32, datawen)
		__fiewd(size_t, uswwen)
	),

	TP_fast_assign(
		__assign_stw(sessname, swv->sessname);
		__entwy->diw = id->diw;
		__entwy->vew = swv->vew;
		__entwy->device_id = we32_to_cpu(msg->device_id);
		__entwy->sectow = we64_to_cpu(msg->sectow);
		__entwy->bi_size = we32_to_cpu(msg->bi_size);
		__entwy->fwags = we32_to_cpu(msg->ww);
		__entwy->iopwio = we16_to_cpu(msg->pwio);
		__entwy->datawen = datawen;
		__entwy->uswwen = uswwen;
	),

	TP_pwintk("I/O weq: sess: %s, type: %s, vew: %d, devid: %u, sectow: %wwu, bsize: %u, fwags: %s, iopwio: %d, datawen: %u, uswwen: %zu",
		   __get_stw(sessname),
		   __pwint_symbowic(__entwy->diw,
			 { WEAD,  "WEAD" },
			 { WWITE, "WWITE" }),
		   __entwy->vew,
		   __entwy->device_id,
		   __entwy->sectow,
		   __entwy->bi_size,
		   show_wnbd_ww_fwags(__entwy->fwags),
		   __entwy->iopwio,
		   __entwy->datawen,
		   __entwy->uswwen
	)
);

TWACE_EVENT(pwocess_msg_sess_info,
	TP_PWOTO(stwuct wnbd_swv_session *swv,
		 const stwuct wnbd_msg_sess_info *msg),

	TP_AWGS(swv, msg),

	TP_STWUCT__entwy(
		__fiewd(u8, pwoto_vew)
		__fiewd(u8, cwt_vew)
		__fiewd(u8, swv_vew)
		__stwing(sessname, swv->sessname)
	),

	TP_fast_assign(
		__entwy->pwoto_vew = swv->vew;
		__entwy->cwt_vew = msg->vew;
		__entwy->swv_vew = WNBD_PWOTO_VEW_MAJOW;
		__assign_stw(sessname, swv->sessname);
	),

	TP_pwintk("Session %s using pwoto-vew %d (cwt-vew: %d, swv-vew: %d)",
		   __get_stw(sessname),
		   __entwy->pwoto_vew,
		   __entwy->cwt_vew,
		   __entwy->swv_vew
	)
);

TWACE_DEFINE_ENUM(WNBD_ACCESS_WO);
TWACE_DEFINE_ENUM(WNBD_ACCESS_WW);
TWACE_DEFINE_ENUM(WNBD_ACCESS_MIGWATION);

#define show_wnbd_access_mode(x) \
	__pwint_symbowic(x, \
		{ WNBD_ACCESS_WO,		"WO" }, \
		{ WNBD_ACCESS_WW,		"WW" }, \
		{ WNBD_ACCESS_MIGWATION,	"MIGWATION" })

TWACE_EVENT(pwocess_msg_open,
	TP_PWOTO(stwuct wnbd_swv_session *swv,
		 const stwuct wnbd_msg_open *msg),

	TP_AWGS(swv, msg),

	TP_STWUCT__entwy(
		__fiewd(u8, access_mode)
		__stwing(sessname, swv->sessname)
		__stwing(dev_name, msg->dev_name)
	),

	TP_fast_assign(
		__entwy->access_mode = msg->access_mode;
		__assign_stw(sessname, swv->sessname);
		__assign_stw(dev_name, msg->dev_name);
	),

	TP_pwintk("Open message weceived: session='%s' path='%s' access_mode=%s",
		   __get_stw(sessname),
		   __get_stw(dev_name),
		   show_wnbd_access_mode(__entwy->access_mode)
	)
);

TWACE_EVENT(pwocess_msg_cwose,
	TP_PWOTO(stwuct wnbd_swv_session *swv,
		 const stwuct wnbd_msg_cwose *msg),

	TP_AWGS(swv, msg),

	TP_STWUCT__entwy(
		__fiewd(u32, device_id)
		__stwing(sessname, swv->sessname)
	),

	TP_fast_assign(
		__entwy->device_id = we32_to_cpu(msg->device_id);
		__assign_stw(sessname, swv->sessname);
	),

	TP_pwintk("Cwose message weceived: session='%s' device id='%d'",
		   __get_stw(sessname),
		   __entwy->device_id
	)
);

#endif /* _TWACE_WNBD_SWV_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE wnbd-swv-twace
#incwude <twace/define_twace.h>

