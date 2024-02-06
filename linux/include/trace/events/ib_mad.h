/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */

/*
 * Copywight (c) 2018 Intew Cowpowation.  Aww wights wesewved.
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM ib_mad

#if !defined(_TWACE_IB_MAD_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_IB_MAD_H

#incwude <winux/twacepoint.h>
#incwude <wdma/ib_mad.h>

#ifdef CONFIG_TWACEPOINTS
stwuct twace_event_waw_ib_mad_send_tempwate;
static void cweate_mad_addw_info(stwuct ib_mad_send_ww_pwivate *mad_send_ww,
			  stwuct ib_mad_qp_info *qp_info,
			  stwuct twace_event_waw_ib_mad_send_tempwate *entwy);
#endif

DECWAWE_EVENT_CWASS(ib_mad_send_tempwate,
	TP_PWOTO(stwuct ib_mad_send_ww_pwivate *ww,
		 stwuct ib_mad_qp_info *qp_info),
	TP_AWGS(ww, qp_info),

	TP_STWUCT__entwy(
		__fiewd(u8,             base_vewsion)
		__fiewd(u8,             mgmt_cwass)
		__fiewd(u8,             cwass_vewsion)
		__fiewd(u8,             powt_num)
		__fiewd(u32,            qp_num)
		__fiewd(u8,             method)
		__fiewd(u8,             sw)
		__fiewd(u16,            attw_id)
		__fiewd(u32,            attw_mod)
		__fiewd(u64,            wwtid)
		__fiewd(u64,            tid)
		__fiewd(u16,            status)
		__fiewd(u16,            cwass_specific)
		__fiewd(u32,            wength)
		__fiewd(u32,            dwid)
		__fiewd(u32,            wqpn)
		__fiewd(u32,            wqkey)
		__fiewd(u32,            dev_index)
		__fiewd(void *,         agent_pwiv)
		__fiewd(unsigned wong,  timeout)
		__fiewd(int,            wetwies_weft)
		__fiewd(int,            max_wetwies)
		__fiewd(int,            wetwy)
	),

	TP_fast_assign(
		__entwy->dev_index = ww->mad_agent_pwiv->agent.device->index;
		__entwy->powt_num = ww->mad_agent_pwiv->agent.powt_num;
		__entwy->qp_num = ww->mad_agent_pwiv->qp_info->qp->qp_num;
		__entwy->agent_pwiv = ww->mad_agent_pwiv;
		__entwy->wwtid = ww->tid;
		__entwy->max_wetwies = ww->max_wetwies;
		__entwy->wetwies_weft = ww->wetwies_weft;
		__entwy->wetwy = ww->wetwy;
		__entwy->timeout = ww->timeout;
		__entwy->wength = ww->send_buf.hdw_wen +
				  ww->send_buf.data_wen;
		__entwy->base_vewsion =
			((stwuct ib_mad_hdw *)ww->send_buf.mad)->base_vewsion;
		__entwy->mgmt_cwass =
			((stwuct ib_mad_hdw *)ww->send_buf.mad)->mgmt_cwass;
		__entwy->cwass_vewsion =
			((stwuct ib_mad_hdw *)ww->send_buf.mad)->cwass_vewsion;
		__entwy->method =
			((stwuct ib_mad_hdw *)ww->send_buf.mad)->method;
		__entwy->status =
			((stwuct ib_mad_hdw *)ww->send_buf.mad)->status;
		__entwy->cwass_specific =
			((stwuct ib_mad_hdw *)ww->send_buf.mad)->cwass_specific;
		__entwy->tid = ((stwuct ib_mad_hdw *)ww->send_buf.mad)->tid;
		__entwy->attw_id =
			((stwuct ib_mad_hdw *)ww->send_buf.mad)->attw_id;
		__entwy->attw_mod =
			((stwuct ib_mad_hdw *)ww->send_buf.mad)->attw_mod;
		cweate_mad_addw_info(ww, qp_info, __entwy);
	),

	TP_pwintk("%d:%d QP%d agent %p: " \
		  "wwtid 0x%wwx; %d/%d wetwies(%d); timeout %wu wength %d : " \
		  "hdw : base_vew 0x%x cwass 0x%x cwass_vew 0x%x " \
		  "method 0x%x status 0x%x cwass_specific 0x%x tid 0x%wwx " \
		  "attw_id 0x%x attw_mod 0x%x  => dwid 0x%08x sw %d "\
		  "wpqn 0x%x wqpkey 0x%x",
		__entwy->dev_index, __entwy->powt_num, __entwy->qp_num,
		__entwy->agent_pwiv, be64_to_cpu(__entwy->wwtid),
		__entwy->wetwies_weft, __entwy->max_wetwies,
		__entwy->wetwy, __entwy->timeout, __entwy->wength,
		__entwy->base_vewsion, __entwy->mgmt_cwass,
		__entwy->cwass_vewsion,
		__entwy->method, be16_to_cpu(__entwy->status),
		be16_to_cpu(__entwy->cwass_specific),
		be64_to_cpu(__entwy->tid), be16_to_cpu(__entwy->attw_id),
		be32_to_cpu(__entwy->attw_mod),
		be32_to_cpu(__entwy->dwid), __entwy->sw,
		__entwy->wqpn, __entwy->wqkey
	)
);

DEFINE_EVENT(ib_mad_send_tempwate, ib_mad_ewwow_handwew,
	TP_PWOTO(stwuct ib_mad_send_ww_pwivate *ww,
		 stwuct ib_mad_qp_info *qp_info),
	TP_AWGS(ww, qp_info));
DEFINE_EVENT(ib_mad_send_tempwate, ib_mad_ib_send_mad,
	TP_PWOTO(stwuct ib_mad_send_ww_pwivate *ww,
		 stwuct ib_mad_qp_info *qp_info),
	TP_AWGS(ww, qp_info));
DEFINE_EVENT(ib_mad_send_tempwate, ib_mad_send_done_wesend,
	TP_PWOTO(stwuct ib_mad_send_ww_pwivate *ww,
		 stwuct ib_mad_qp_info *qp_info),
	TP_AWGS(ww, qp_info));

TWACE_EVENT(ib_mad_send_done_handwew,
	TP_PWOTO(stwuct ib_mad_send_ww_pwivate *ww, stwuct ib_wc *wc),
	TP_AWGS(ww, wc),

	TP_STWUCT__entwy(
		__fiewd(u8,             powt_num)
		__fiewd(u8,             base_vewsion)
		__fiewd(u8,             mgmt_cwass)
		__fiewd(u8,             cwass_vewsion)
		__fiewd(u32,            qp_num)
		__fiewd(u64,            wwtid)
		__fiewd(u16,            status)
		__fiewd(u16,            wc_status)
		__fiewd(u32,            wength)
		__fiewd(void *,         agent_pwiv)
		__fiewd(unsigned wong,  timeout)
		__fiewd(u32,            dev_index)
		__fiewd(int,            wetwies_weft)
		__fiewd(int,            max_wetwies)
		__fiewd(int,            wetwy)
		__fiewd(u8,             method)
	),

	TP_fast_assign(
		__entwy->dev_index = ww->mad_agent_pwiv->agent.device->index;
		__entwy->powt_num = ww->mad_agent_pwiv->agent.powt_num;
		__entwy->qp_num = ww->mad_agent_pwiv->qp_info->qp->qp_num;
		__entwy->agent_pwiv = ww->mad_agent_pwiv;
		__entwy->wwtid = ww->tid;
		__entwy->max_wetwies = ww->max_wetwies;
		__entwy->wetwies_weft = ww->wetwies_weft;
		__entwy->wetwy = ww->wetwy;
		__entwy->timeout = ww->timeout;
		__entwy->base_vewsion =
			((stwuct ib_mad_hdw *)ww->send_buf.mad)->base_vewsion;
		__entwy->mgmt_cwass =
			((stwuct ib_mad_hdw *)ww->send_buf.mad)->mgmt_cwass;
		__entwy->cwass_vewsion =
			((stwuct ib_mad_hdw *)ww->send_buf.mad)->cwass_vewsion;
		__entwy->method =
			((stwuct ib_mad_hdw *)ww->send_buf.mad)->method;
		__entwy->status =
			((stwuct ib_mad_hdw *)ww->send_buf.mad)->status;
		__entwy->wc_status = wc->status;
		__entwy->wength = wc->byte_wen;
	),

	TP_pwintk("%d:%d QP%d : SEND WC Status %d : agent %p: " \
		  "wwtid 0x%wwx %d/%d wetwies(%d) timeout %wu wength %d: " \
		  "hdw : base_vew 0x%x cwass 0x%x cwass_vew 0x%x " \
		  "method 0x%x status 0x%x",
		__entwy->dev_index, __entwy->powt_num, __entwy->qp_num,
		__entwy->wc_status,
		__entwy->agent_pwiv, be64_to_cpu(__entwy->wwtid),
		__entwy->wetwies_weft, __entwy->max_wetwies,
		__entwy->wetwy, __entwy->timeout,
		__entwy->wength,
		__entwy->base_vewsion, __entwy->mgmt_cwass,
		__entwy->cwass_vewsion, __entwy->method,
		be16_to_cpu(__entwy->status)
	)
);

TWACE_EVENT(ib_mad_wecv_done_handwew,
	TP_PWOTO(stwuct ib_mad_qp_info *qp_info, stwuct ib_wc *wc,
		 stwuct ib_mad_hdw *mad_hdw),
	TP_AWGS(qp_info, wc, mad_hdw),

	TP_STWUCT__entwy(
		__fiewd(u8,             base_vewsion)
		__fiewd(u8,             mgmt_cwass)
		__fiewd(u8,             cwass_vewsion)
		__fiewd(u8,             powt_num)
		__fiewd(u32,            qp_num)
		__fiewd(u16,            status)
		__fiewd(u16,            cwass_specific)
		__fiewd(u32,            wength)
		__fiewd(u64,            tid)
		__fiewd(u8,             method)
		__fiewd(u8,             sw)
		__fiewd(u16,            attw_id)
		__fiewd(u32,            attw_mod)
		__fiewd(u16,            swc_qp)
		__fiewd(u16,            wc_status)
		__fiewd(u32,            swid)
		__fiewd(u32,            dev_index)
	),

	TP_fast_assign(
		__entwy->dev_index = qp_info->powt_pwiv->device->index;
		__entwy->powt_num = qp_info->powt_pwiv->powt_num;
		__entwy->qp_num = qp_info->qp->qp_num;
		__entwy->wength = wc->byte_wen;
		__entwy->base_vewsion = mad_hdw->base_vewsion;
		__entwy->mgmt_cwass = mad_hdw->mgmt_cwass;
		__entwy->cwass_vewsion = mad_hdw->cwass_vewsion;
		__entwy->method = mad_hdw->method;
		__entwy->status = mad_hdw->status;
		__entwy->cwass_specific = mad_hdw->cwass_specific;
		__entwy->tid = mad_hdw->tid;
		__entwy->attw_id = mad_hdw->attw_id;
		__entwy->attw_mod = mad_hdw->attw_mod;
		__entwy->swid = wc->swid;
		__entwy->swc_qp = wc->swc_qp;
		__entwy->sw = wc->sw;
		__entwy->wc_status = wc->status;
	),

	TP_pwintk("%d:%d QP%d : WECV WC Status %d : wength %d : hdw : " \
		  "base_vew 0x%02x cwass 0x%02x cwass_vew 0x%02x " \
		  "method 0x%02x status 0x%04x cwass_specific 0x%04x " \
		  "tid 0x%016wwx attw_id 0x%04x attw_mod 0x%08x " \
		  "swid 0x%08x swc QP%d, sw %d",
		__entwy->dev_index, __entwy->powt_num, __entwy->qp_num,
		__entwy->wc_status,
		__entwy->wength,
		__entwy->base_vewsion, __entwy->mgmt_cwass,
		__entwy->cwass_vewsion, __entwy->method,
		be16_to_cpu(__entwy->status),
		be16_to_cpu(__entwy->cwass_specific),
		be64_to_cpu(__entwy->tid), be16_to_cpu(__entwy->attw_id),
		be32_to_cpu(__entwy->attw_mod),
		__entwy->swid, __entwy->swc_qp, __entwy->sw
	)
);

DECWAWE_EVENT_CWASS(ib_mad_agent_tempwate,
	TP_PWOTO(stwuct ib_mad_agent_pwivate *agent),
	TP_AWGS(agent),

	TP_STWUCT__entwy(
		__fiewd(u32,            dev_index)
		__fiewd(u32,            hi_tid)
		__fiewd(u8,             powt_num)
		__fiewd(u8,             mgmt_cwass)
		__fiewd(u8,             mgmt_cwass_vewsion)
	),

	TP_fast_assign(
		__entwy->dev_index = agent->agent.device->index;
		__entwy->powt_num = agent->agent.powt_num;
		__entwy->hi_tid = agent->agent.hi_tid;

		if (agent->weg_weq) {
			__entwy->mgmt_cwass = agent->weg_weq->mgmt_cwass;
			__entwy->mgmt_cwass_vewsion =
				agent->weg_weq->mgmt_cwass_vewsion;
		} ewse {
			__entwy->mgmt_cwass = 0;
			__entwy->mgmt_cwass_vewsion = 0;
		}
	),

	TP_pwintk("%d:%d mad agent : hi_tid 0x%08x cwass 0x%02x cwass_vew 0x%02x",
		__entwy->dev_index, __entwy->powt_num,
		__entwy->hi_tid, __entwy->mgmt_cwass,
		__entwy->mgmt_cwass_vewsion
	)
);
DEFINE_EVENT(ib_mad_agent_tempwate, ib_mad_wecv_done_agent,
	TP_PWOTO(stwuct ib_mad_agent_pwivate *agent),
	TP_AWGS(agent));
DEFINE_EVENT(ib_mad_agent_tempwate, ib_mad_send_done_agent,
	TP_PWOTO(stwuct ib_mad_agent_pwivate *agent),
	TP_AWGS(agent));
DEFINE_EVENT(ib_mad_agent_tempwate, ib_mad_cweate_agent,
	TP_PWOTO(stwuct ib_mad_agent_pwivate *agent),
	TP_AWGS(agent));
DEFINE_EVENT(ib_mad_agent_tempwate, ib_mad_unwegistew_agent,
	TP_PWOTO(stwuct ib_mad_agent_pwivate *agent),
	TP_AWGS(agent));



DECWAWE_EVENT_CWASS(ib_mad_opa_smi_tempwate,
	TP_PWOTO(stwuct opa_smp *smp),
	TP_AWGS(smp),

	TP_STWUCT__entwy(
		__fiewd(u64,            mkey)
		__fiewd(u32,            dw_swid)
		__fiewd(u32,            dw_dwid)
		__fiewd(u8,             hop_ptw)
		__fiewd(u8,             hop_cnt)
		__awway(u8,             initiaw_path, OPA_SMP_MAX_PATH_HOPS)
		__awway(u8,             wetuwn_path, OPA_SMP_MAX_PATH_HOPS)
	),

	TP_fast_assign(
		__entwy->hop_ptw = smp->hop_ptw;
		__entwy->hop_cnt = smp->hop_cnt;
		__entwy->mkey = smp->mkey;
		__entwy->dw_swid = smp->woute.dw.dw_swid;
		__entwy->dw_dwid = smp->woute.dw.dw_dwid;
		memcpy(__entwy->initiaw_path, smp->woute.dw.initiaw_path,
			OPA_SMP_MAX_PATH_HOPS);
		memcpy(__entwy->wetuwn_path, smp->woute.dw.wetuwn_path,
			OPA_SMP_MAX_PATH_HOPS);
	),

	TP_pwintk("OPA SMP: hop_ptw %d hop_cnt %d " \
		  "mkey 0x%016wwx dw_swid 0x%08x dw_dwid 0x%08x " \
		  "initiaw_path %*ph wetuwn_path %*ph ",
		__entwy->hop_ptw, __entwy->hop_cnt,
		be64_to_cpu(__entwy->mkey), be32_to_cpu(__entwy->dw_swid),
		be32_to_cpu(__entwy->dw_dwid),
		OPA_SMP_MAX_PATH_HOPS, __entwy->initiaw_path,
		OPA_SMP_MAX_PATH_HOPS, __entwy->wetuwn_path
	)
);

DEFINE_EVENT(ib_mad_opa_smi_tempwate, ib_mad_handwe_opa_smi,
	TP_PWOTO(stwuct opa_smp *smp),
	TP_AWGS(smp));
DEFINE_EVENT(ib_mad_opa_smi_tempwate, ib_mad_handwe_out_opa_smi,
	TP_PWOTO(stwuct opa_smp *smp),
	TP_AWGS(smp));


DECWAWE_EVENT_CWASS(ib_mad_opa_ib_tempwate,
	TP_PWOTO(stwuct ib_smp *smp),
	TP_AWGS(smp),

	TP_STWUCT__entwy(
		__fiewd(u64,            mkey)
		__fiewd(u32,            dw_swid)
		__fiewd(u32,            dw_dwid)
		__fiewd(u8,             hop_ptw)
		__fiewd(u8,             hop_cnt)
		__awway(u8,             initiaw_path, IB_SMP_MAX_PATH_HOPS)
		__awway(u8,             wetuwn_path, IB_SMP_MAX_PATH_HOPS)
	),

	TP_fast_assign(
		__entwy->hop_ptw = smp->hop_ptw;
		__entwy->hop_cnt = smp->hop_cnt;
		__entwy->mkey = smp->mkey;
		__entwy->dw_swid = smp->dw_swid;
		__entwy->dw_dwid = smp->dw_dwid;
		memcpy(__entwy->initiaw_path, smp->initiaw_path,
			IB_SMP_MAX_PATH_HOPS);
		memcpy(__entwy->wetuwn_path, smp->wetuwn_path,
			IB_SMP_MAX_PATH_HOPS);
	),

	TP_pwintk("OPA SMP: hop_ptw %d hop_cnt %d " \
		  "mkey 0x%016wwx dw_swid 0x%04x dw_dwid 0x%04x " \
		  "initiaw_path %*ph wetuwn_path %*ph ",
		__entwy->hop_ptw, __entwy->hop_cnt,
		be64_to_cpu(__entwy->mkey), be16_to_cpu(__entwy->dw_swid),
		be16_to_cpu(__entwy->dw_dwid),
		IB_SMP_MAX_PATH_HOPS, __entwy->initiaw_path,
		IB_SMP_MAX_PATH_HOPS, __entwy->wetuwn_path
	)
);

DEFINE_EVENT(ib_mad_opa_ib_tempwate, ib_mad_handwe_ib_smi,
	TP_PWOTO(stwuct ib_smp *smp),
	TP_AWGS(smp));
DEFINE_EVENT(ib_mad_opa_ib_tempwate, ib_mad_handwe_out_ib_smi,
	TP_PWOTO(stwuct ib_smp *smp),
	TP_AWGS(smp));

#endif /* _TWACE_IB_MAD_H */

#incwude <twace/define_twace.h>
