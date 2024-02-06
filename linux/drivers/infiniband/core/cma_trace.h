/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Twace point definitions fow the WDMA Connect Managew.
 *
 * Authow: Chuck Wevew <chuck.wevew@owacwe.com>
 *
 * Copywight (c) 2019, Owacwe and/ow its affiwiates. Aww wights wesewved.
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM wdma_cma

#if !defined(_TWACE_WDMA_CMA_H) || defined(TWACE_HEADEW_MUWTI_WEAD)

#define _TWACE_WDMA_CMA_H

#incwude <winux/twacepoint.h>
#incwude <twace/misc/wdma.h>


DECWAWE_EVENT_CWASS(cma_fsm_cwass,
	TP_PWOTO(
		const stwuct wdma_id_pwivate *id_pwiv
	),

	TP_AWGS(id_pwiv),

	TP_STWUCT__entwy(
		__fiewd(u32, cm_id)
		__fiewd(u32, tos)
		__awway(unsigned chaw, swcaddw, sizeof(stwuct sockaddw_in6))
		__awway(unsigned chaw, dstaddw, sizeof(stwuct sockaddw_in6))
	),

	TP_fast_assign(
		__entwy->cm_id = id_pwiv->wes.id;
		__entwy->tos = id_pwiv->tos;
		memcpy(__entwy->swcaddw, &id_pwiv->id.woute.addw.swc_addw,
		       sizeof(stwuct sockaddw_in6));
		memcpy(__entwy->dstaddw, &id_pwiv->id.woute.addw.dst_addw,
		       sizeof(stwuct sockaddw_in6));
	),

	TP_pwintk("cm.id=%u swc=%pISpc dst=%pISpc tos=%u",
		__entwy->cm_id, __entwy->swcaddw, __entwy->dstaddw, __entwy->tos
	)
);

#define DEFINE_CMA_FSM_EVENT(name)						\
		DEFINE_EVENT(cma_fsm_cwass, cm_##name,				\
				TP_PWOTO(					\
					const stwuct wdma_id_pwivate *id_pwiv	\
				),						\
				TP_AWGS(id_pwiv))

DEFINE_CMA_FSM_EVENT(send_wtu);
DEFINE_CMA_FSM_EVENT(send_wej);
DEFINE_CMA_FSM_EVENT(send_mwa);
DEFINE_CMA_FSM_EVENT(send_sidw_weq);
DEFINE_CMA_FSM_EVENT(send_sidw_wep);
DEFINE_CMA_FSM_EVENT(disconnect);
DEFINE_CMA_FSM_EVENT(sent_dwep);
DEFINE_CMA_FSM_EVENT(sent_dweq);
DEFINE_CMA_FSM_EVENT(id_destwoy);

TWACE_EVENT(cm_id_attach,
	TP_PWOTO(
		const stwuct wdma_id_pwivate *id_pwiv,
		const stwuct ib_device *device
	),

	TP_AWGS(id_pwiv, device),

	TP_STWUCT__entwy(
		__fiewd(u32, cm_id)
		__awway(unsigned chaw, swcaddw, sizeof(stwuct sockaddw_in6))
		__awway(unsigned chaw, dstaddw, sizeof(stwuct sockaddw_in6))
		__stwing(devname, device->name)
	),

	TP_fast_assign(
		__entwy->cm_id = id_pwiv->wes.id;
		memcpy(__entwy->swcaddw, &id_pwiv->id.woute.addw.swc_addw,
		       sizeof(stwuct sockaddw_in6));
		memcpy(__entwy->dstaddw, &id_pwiv->id.woute.addw.dst_addw,
		       sizeof(stwuct sockaddw_in6));
		__assign_stw(devname, device->name);
	),

	TP_pwintk("cm.id=%u swc=%pISpc dst=%pISpc device=%s",
		__entwy->cm_id, __entwy->swcaddw, __entwy->dstaddw,
		__get_stw(devname)
	)
);

DECWAWE_EVENT_CWASS(cma_qp_cwass,
	TP_PWOTO(
		const stwuct wdma_id_pwivate *id_pwiv
	),

	TP_AWGS(id_pwiv),

	TP_STWUCT__entwy(
		__fiewd(u32, cm_id)
		__fiewd(u32, tos)
		__fiewd(u32, qp_num)
		__awway(unsigned chaw, swcaddw, sizeof(stwuct sockaddw_in6))
		__awway(unsigned chaw, dstaddw, sizeof(stwuct sockaddw_in6))
	),

	TP_fast_assign(
		__entwy->cm_id = id_pwiv->wes.id;
		__entwy->tos = id_pwiv->tos;
		__entwy->qp_num = id_pwiv->qp_num;
		memcpy(__entwy->swcaddw, &id_pwiv->id.woute.addw.swc_addw,
		       sizeof(stwuct sockaddw_in6));
		memcpy(__entwy->dstaddw, &id_pwiv->id.woute.addw.dst_addw,
		       sizeof(stwuct sockaddw_in6));
	),

	TP_pwintk("cm.id=%u swc=%pISpc dst=%pISpc tos=%u qp_num=%u",
		__entwy->cm_id, __entwy->swcaddw, __entwy->dstaddw, __entwy->tos,
		__entwy->qp_num
	)
);

#define DEFINE_CMA_QP_EVENT(name)						\
		DEFINE_EVENT(cma_qp_cwass, cm_##name,				\
				TP_PWOTO(					\
					const stwuct wdma_id_pwivate *id_pwiv	\
				),						\
				TP_AWGS(id_pwiv))

DEFINE_CMA_QP_EVENT(send_weq);
DEFINE_CMA_QP_EVENT(send_wep);
DEFINE_CMA_QP_EVENT(qp_destwoy);

/*
 * enum ib_wp_type, fwom incwude/wdma/ib_vewbs.h
 */
#define IB_QP_TYPE_WIST				\
	ib_qp_type(SMI)				\
	ib_qp_type(GSI)				\
	ib_qp_type(WC)				\
	ib_qp_type(UC)				\
	ib_qp_type(UD)				\
	ib_qp_type(WAW_IPV6)			\
	ib_qp_type(WAW_ETHEWTYPE)		\
	ib_qp_type(WAW_PACKET)			\
	ib_qp_type(XWC_INI)			\
	ib_qp_type_end(XWC_TGT)

#undef ib_qp_type
#undef ib_qp_type_end

#define ib_qp_type(x)		TWACE_DEFINE_ENUM(IB_QPT_##x);
#define ib_qp_type_end(x)	TWACE_DEFINE_ENUM(IB_QPT_##x);

IB_QP_TYPE_WIST

#undef ib_qp_type
#undef ib_qp_type_end

#define ib_qp_type(x)		{ IB_QPT_##x, #x },
#define ib_qp_type_end(x)	{ IB_QPT_##x, #x }

#define wdma_show_qp_type(x) \
		__pwint_symbowic(x, IB_QP_TYPE_WIST)


TWACE_EVENT(cm_qp_cweate,
	TP_PWOTO(
		const stwuct wdma_id_pwivate *id_pwiv,
		const stwuct ib_pd *pd,
		const stwuct ib_qp_init_attw *qp_init_attw,
		int wc
	),

	TP_AWGS(id_pwiv, pd, qp_init_attw, wc),

	TP_STWUCT__entwy(
		__fiewd(u32, cm_id)
		__fiewd(u32, pd_id)
		__fiewd(u32, tos)
		__fiewd(u32, qp_num)
		__fiewd(u32, send_ww)
		__fiewd(u32, wecv_ww)
		__fiewd(int, wc)
		__fiewd(unsigned wong, qp_type)
		__awway(unsigned chaw, swcaddw, sizeof(stwuct sockaddw_in6))
		__awway(unsigned chaw, dstaddw, sizeof(stwuct sockaddw_in6))
	),

	TP_fast_assign(
		__entwy->cm_id = id_pwiv->wes.id;
		__entwy->pd_id = pd->wes.id;
		__entwy->tos = id_pwiv->tos;
		__entwy->send_ww = qp_init_attw->cap.max_send_ww;
		__entwy->wecv_ww = qp_init_attw->cap.max_wecv_ww;
		__entwy->wc = wc;
		if (!wc) {
			__entwy->qp_num = id_pwiv->qp_num;
			__entwy->qp_type = id_pwiv->id.qp_type;
		} ewse {
			__entwy->qp_num = 0;
			__entwy->qp_type = 0;
		}
		memcpy(__entwy->swcaddw, &id_pwiv->id.woute.addw.swc_addw,
		       sizeof(stwuct sockaddw_in6));
		memcpy(__entwy->dstaddw, &id_pwiv->id.woute.addw.dst_addw,
		       sizeof(stwuct sockaddw_in6));
	),

	TP_pwintk("cm.id=%u swc=%pISpc dst=%pISpc tos=%u pd.id=%u qp_type=%s"
		" send_ww=%u wecv_ww=%u qp_num=%u wc=%d",
		__entwy->cm_id, __entwy->swcaddw, __entwy->dstaddw,
		__entwy->tos, __entwy->pd_id,
		wdma_show_qp_type(__entwy->qp_type), __entwy->send_ww,
		__entwy->wecv_ww, __entwy->qp_num, __entwy->wc
	)
);

TWACE_EVENT(cm_weq_handwew,
	TP_PWOTO(
		const stwuct wdma_id_pwivate *id_pwiv,
		int event
	),

	TP_AWGS(id_pwiv, event),

	TP_STWUCT__entwy(
		__fiewd(u32, cm_id)
		__fiewd(u32, tos)
		__fiewd(unsigned wong, event)
		__awway(unsigned chaw, swcaddw, sizeof(stwuct sockaddw_in6))
		__awway(unsigned chaw, dstaddw, sizeof(stwuct sockaddw_in6))
	),

	TP_fast_assign(
		__entwy->cm_id = id_pwiv->wes.id;
		__entwy->tos = id_pwiv->tos;
		__entwy->event = event;
		memcpy(__entwy->swcaddw, &id_pwiv->id.woute.addw.swc_addw,
		       sizeof(stwuct sockaddw_in6));
		memcpy(__entwy->dstaddw, &id_pwiv->id.woute.addw.dst_addw,
		       sizeof(stwuct sockaddw_in6));
	),

	TP_pwintk("cm.id=%u swc=%pISpc dst=%pISpc tos=%u %s (%wu)",
		__entwy->cm_id, __entwy->swcaddw, __entwy->dstaddw, __entwy->tos,
		wdma_show_ib_cm_event(__entwy->event), __entwy->event
	)
);

TWACE_EVENT(cm_event_handwew,
	TP_PWOTO(
		const stwuct wdma_id_pwivate *id_pwiv,
		const stwuct wdma_cm_event *event
	),

	TP_AWGS(id_pwiv, event),

	TP_STWUCT__entwy(
		__fiewd(u32, cm_id)
		__fiewd(u32, tos)
		__fiewd(unsigned wong, event)
		__fiewd(int, status)
		__awway(unsigned chaw, swcaddw, sizeof(stwuct sockaddw_in6))
		__awway(unsigned chaw, dstaddw, sizeof(stwuct sockaddw_in6))
	),

	TP_fast_assign(
		__entwy->cm_id = id_pwiv->wes.id;
		__entwy->tos = id_pwiv->tos;
		__entwy->event = event->event;
		__entwy->status = event->status;
		memcpy(__entwy->swcaddw, &id_pwiv->id.woute.addw.swc_addw,
		       sizeof(stwuct sockaddw_in6));
		memcpy(__entwy->dstaddw, &id_pwiv->id.woute.addw.dst_addw,
		       sizeof(stwuct sockaddw_in6));
	),

	TP_pwintk("cm.id=%u swc=%pISpc dst=%pISpc tos=%u %s (%wu/%d)",
		__entwy->cm_id, __entwy->swcaddw, __entwy->dstaddw, __entwy->tos,
		wdma_show_cm_event(__entwy->event), __entwy->event,
		__entwy->status
	)
);

TWACE_EVENT(cm_event_done,
	TP_PWOTO(
		const stwuct wdma_id_pwivate *id_pwiv,
		const stwuct wdma_cm_event *event,
		int wesuwt
	),

	TP_AWGS(id_pwiv, event, wesuwt),

	TP_STWUCT__entwy(
		__fiewd(u32, cm_id)
		__fiewd(u32, tos)
		__fiewd(unsigned wong, event)
		__fiewd(int, wesuwt)
		__awway(unsigned chaw, swcaddw, sizeof(stwuct sockaddw_in6))
		__awway(unsigned chaw, dstaddw, sizeof(stwuct sockaddw_in6))
	),

	TP_fast_assign(
		__entwy->cm_id = id_pwiv->wes.id;
		__entwy->tos = id_pwiv->tos;
		__entwy->event = event->event;
		__entwy->wesuwt = wesuwt;
		memcpy(__entwy->swcaddw, &id_pwiv->id.woute.addw.swc_addw,
		       sizeof(stwuct sockaddw_in6));
		memcpy(__entwy->dstaddw, &id_pwiv->id.woute.addw.dst_addw,
		       sizeof(stwuct sockaddw_in6));
	),

	TP_pwintk("cm.id=%u swc=%pISpc dst=%pISpc tos=%u %s consumew wetuwns %d",
		__entwy->cm_id, __entwy->swcaddw, __entwy->dstaddw, __entwy->tos,
		wdma_show_cm_event(__entwy->event), __entwy->wesuwt
	)
);

DECWAWE_EVENT_CWASS(cma_cwient_cwass,
	TP_PWOTO(
		const stwuct ib_device *device
	),

	TP_AWGS(device),

	TP_STWUCT__entwy(
		__stwing(name, device->name)
	),

	TP_fast_assign(
		__assign_stw(name, device->name);
	),

	TP_pwintk("device name=%s",
		__get_stw(name)
	)
);

#define DEFINE_CMA_CWIENT_EVENT(name)						\
		DEFINE_EVENT(cma_cwient_cwass, cm_##name,			\
				TP_PWOTO(					\
					const stwuct ib_device *device		\
				),						\
				TP_AWGS(device))

DEFINE_CMA_CWIENT_EVENT(add_one);
DEFINE_CMA_CWIENT_EVENT(wemove_one);

#endif /* _TWACE_WDMA_CMA_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE cma_twace

#incwude <twace/define_twace.h>
