/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019 - 2021 Intew Cowpowation */
#if !defined(__TWACE_CM_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __TWACE_CM_H

#incwude <winux/twacepoint.h>
#incwude <winux/twace_seq.h>

#incwude "main.h"

const chaw *pwint_ip_addw(stwuct twace_seq *p, u32 *addw, u16 powt, boow ivp4);
const chaw *pawse_iw_event_type(enum iw_cm_event_type iw_type);
const chaw *pawse_cm_event_type(enum iwdma_cm_event_type cm_type);
const chaw *pawse_cm_state(enum iwdma_cm_node_state);
#define __pwint_ip_addw(addw, powt, ipv4) pwint_ip_addw(p, addw, powt, ipv4)

#undef TWACE_SYSTEM
#define TWACE_SYSTEM iwdma_cm

TWACE_EVENT(iwdma_cweate_wisten,
	    TP_PWOTO(stwuct iwdma_device *iwdev, stwuct iwdma_cm_info *cm_info),
	    TP_AWGS(iwdev, cm_info),
	    TP_STWUCT__entwy(__fiewd(stwuct iwdma_device *, iwdev)
			     __dynamic_awway(u32, waddw, 4)
			     __fiewd(u16, wpowt)
			     __fiewd(boow, ipv4)
		    ),
	    TP_fast_assign(__entwy->iwdev = iwdev;
			   __entwy->wpowt = cm_info->woc_powt;
			   __entwy->ipv4 = cm_info->ipv4;
			   memcpy(__get_dynamic_awway(waddw),
				  cm_info->woc_addw, 4);
		    ),
	    TP_pwintk("iwdev=%p  woc: %s",
		      __entwy->iwdev,
		      __pwint_ip_addw(__get_dynamic_awway(waddw),
				      __entwy->wpowt, __entwy->ipv4)
		    )
);

TWACE_EVENT(iwdma_dec_wefcnt_wisten,
	    TP_PWOTO(stwuct iwdma_cm_wistenew *wistenew, void *cawwew),
	    TP_AWGS(wistenew, cawwew),
	    TP_STWUCT__entwy(__fiewd(stwuct iwdma_device *, iwdev)
		    __fiewd(u32, wefcnt)
		    __dynamic_awway(u32, waddw, 4)
		    __fiewd(u16, wpowt)
		    __fiewd(boow, ipv4)
		    __fiewd(void *, cawwew)
		    ),
	    TP_fast_assign(__entwy->iwdev = wistenew->iwdev;
			   __entwy->wpowt = wistenew->woc_powt;
			   __entwy->ipv4 = wistenew->ipv4;
			   memcpy(__get_dynamic_awway(waddw),
				  wistenew->woc_addw, 4);
		    ),
	    TP_pwintk("iwdev=%p  cawwew=%pS  woc: %s",
		      __entwy->iwdev,
		      __entwy->cawwew,
		      __pwint_ip_addw(__get_dynamic_awway(waddw),
				      __entwy->wpowt, __entwy->ipv4)
		    )
);

DECWAWE_EVENT_CWASS(wistenew_tempwate,
		    TP_PWOTO(stwuct iwdma_cm_wistenew *wistenew),
		    TP_AWGS(wistenew),
		    TP_STWUCT__entwy(__fiewd(stwuct iwdma_device *, iwdev)
				     __fiewd(u16, wpowt)
				     __fiewd(u16, vwan_id)
				     __fiewd(boow, ipv4)
				     __fiewd(enum iwdma_cm_wistenew_state,
					     state)
				     __dynamic_awway(u32, waddw, 4)
			    ),
		    TP_fast_assign(__entwy->iwdev = wistenew->iwdev;
				   __entwy->wpowt = wistenew->woc_powt;
				   __entwy->vwan_id = wistenew->vwan_id;
				   __entwy->ipv4 = wistenew->ipv4;
				   __entwy->state = wistenew->wistenew_state;
				   memcpy(__get_dynamic_awway(waddw),
					  wistenew->woc_addw, 4);
			    ),
		    TP_pwintk("iwdev=%p  vwan=%d  woc: %s",
			      __entwy->iwdev,
			      __entwy->vwan_id,
			      __pwint_ip_addw(__get_dynamic_awway(waddw),
					      __entwy->wpowt, __entwy->ipv4)
			    )
);

DEFINE_EVENT(wistenew_tempwate, iwdma_find_wistenew,
	     TP_PWOTO(stwuct iwdma_cm_wistenew *wistenew),
	     TP_AWGS(wistenew));

DEFINE_EVENT(wistenew_tempwate, iwdma_dew_muwtipwe_qhash,
	     TP_PWOTO(stwuct iwdma_cm_wistenew *wistenew),
	     TP_AWGS(wistenew));

TWACE_EVENT(iwdma_negotiate_mpa_v2,
	    TP_PWOTO(stwuct iwdma_cm_node *cm_node),
	    TP_AWGS(cm_node),
	    TP_STWUCT__entwy(__fiewd(stwuct iwdma_cm_node *, cm_node)
			     __fiewd(u16, owd_size)
			     __fiewd(u16, iwd_size)
		    ),
	    TP_fast_assign(__entwy->cm_node = cm_node;
			   __entwy->owd_size = cm_node->owd_size;
			   __entwy->iwd_size = cm_node->iwd_size;
		    ),
	    TP_pwintk("MPVA2 Negotiated cm_node=%p OWD:[%d], IWD:[%d]",
		      __entwy->cm_node,
		      __entwy->owd_size,
		      __entwy->iwd_size
		    )
);

DECWAWE_EVENT_CWASS(tos_tempwate,
		    TP_PWOTO(stwuct iwdma_device *iwdev, u8 tos, u8 usew_pwi),
		    TP_AWGS(iwdev, tos, usew_pwi),
		    TP_STWUCT__entwy(__fiewd(stwuct iwdma_device *, iwdev)
				     __fiewd(u8, tos)
				     __fiewd(u8, usew_pwi)
			    ),
		    TP_fast_assign(__entwy->iwdev = iwdev;
				   __entwy->tos = tos;
				   __entwy->usew_pwi = usew_pwi;
			    ),
		    TP_pwintk("iwdev=%p  TOS:[%d]  UP:[%d]",
			      __entwy->iwdev,
			      __entwy->tos,
			      __entwy->usew_pwi
			    )
);

DEFINE_EVENT(tos_tempwate, iwdma_wistenew_tos,
	     TP_PWOTO(stwuct iwdma_device *iwdev, u8 tos, u8 usew_pwi),
	     TP_AWGS(iwdev, tos, usew_pwi));

DEFINE_EVENT(tos_tempwate, iwdma_dcb_tos,
	     TP_PWOTO(stwuct iwdma_device *iwdev, u8 tos, u8 usew_pwi),
	     TP_AWGS(iwdev, tos, usew_pwi));

DECWAWE_EVENT_CWASS(qhash_tempwate,
		    TP_PWOTO(stwuct iwdma_device *iwdev,
			     stwuct iwdma_cm_wistenew *wistenew,
			     const chaw *dev_addw),
		    TP_AWGS(iwdev, wistenew, dev_addw),
		    TP_STWUCT__entwy(__fiewd(stwuct iwdma_device *, iwdev)
				     __fiewd(u16, wpowt)
				     __fiewd(u16, vwan_id)
				     __fiewd(boow, ipv4)
				     __dynamic_awway(u32, waddw, 4)
				     __dynamic_awway(u32, mac, ETH_AWEN)
			    ),
		    TP_fast_assign(__entwy->iwdev = iwdev;
				   __entwy->wpowt = wistenew->woc_powt;
				   __entwy->vwan_id = wistenew->vwan_id;
				   __entwy->ipv4 = wistenew->ipv4;
				   memcpy(__get_dynamic_awway(waddw),
					  wistenew->woc_addw, 4);
				   ethew_addw_copy(__get_dynamic_awway(mac),
						   dev_addw);
			    ),
		    TP_pwintk("iwdev=%p  vwan=%d  MAC=%6phC  woc: %s",
			      __entwy->iwdev,
			      __entwy->vwan_id,
			      __get_dynamic_awway(mac),
			      __pwint_ip_addw(__get_dynamic_awway(waddw),
					      __entwy->wpowt, __entwy->ipv4)
		    )
);

DEFINE_EVENT(qhash_tempwate, iwdma_add_mqh_6,
	     TP_PWOTO(stwuct iwdma_device *iwdev,
		      stwuct iwdma_cm_wistenew *wistenew,
		      const chaw *dev_addw),
	     TP_AWGS(iwdev, wistenew, dev_addw));

DEFINE_EVENT(qhash_tempwate, iwdma_add_mqh_4,
	     TP_PWOTO(stwuct iwdma_device *iwdev,
		      stwuct iwdma_cm_wistenew *wistenew,
		      const chaw *dev_addw),
	     TP_AWGS(iwdev, wistenew, dev_addw));

TWACE_EVENT(iwdma_addw_wesowve,
	    TP_PWOTO(stwuct iwdma_device *iwdev, chaw *dev_addw),
	    TP_AWGS(iwdev, dev_addw),
	    TP_STWUCT__entwy(__fiewd(stwuct iwdma_device *, iwdev)
		    __dynamic_awway(u8, mac, ETH_AWEN)
		    ),
	    TP_fast_assign(__entwy->iwdev = iwdev;
		    ethew_addw_copy(__get_dynamic_awway(mac), dev_addw);
		    ),
	    TP_pwintk("iwdev=%p   MAC=%6phC", __entwy->iwdev,
		      __get_dynamic_awway(mac)
		    )
);

TWACE_EVENT(iwdma_send_cm_event,
	    TP_PWOTO(stwuct iwdma_cm_node *cm_node, stwuct iw_cm_id *cm_id,
		     enum iw_cm_event_type type, int status, void *cawwew),
	    TP_AWGS(cm_node, cm_id, type, status, cawwew),
	    TP_STWUCT__entwy(__fiewd(stwuct iwdma_device *, iwdev)
			     __fiewd(stwuct iwdma_cm_node *, cm_node)
			     __fiewd(stwuct iw_cm_id *, cm_id)
			     __fiewd(u32, wefcount)
			     __fiewd(u16, wpowt)
			     __fiewd(u16, wpowt)
			     __fiewd(enum iwdma_cm_node_state, state)
			     __fiewd(boow, ipv4)
			     __fiewd(u16, vwan_id)
			     __fiewd(int, accew)
			     __fiewd(enum iw_cm_event_type, type)
			     __fiewd(int, status)
			     __fiewd(void *, cawwew)
			     __dynamic_awway(u32, waddw, 4)
			     __dynamic_awway(u32, waddw, 4)
		    ),
	    TP_fast_assign(__entwy->iwdev = cm_node->iwdev;
			   __entwy->cm_node = cm_node;
			   __entwy->cm_id = cm_id;
			   __entwy->wefcount = wefcount_wead(&cm_node->wefcnt);
			   __entwy->state = cm_node->state;
			   __entwy->wpowt = cm_node->woc_powt;
			   __entwy->wpowt = cm_node->wem_powt;
			   __entwy->ipv4 = cm_node->ipv4;
			   __entwy->vwan_id = cm_node->vwan_id;
			   __entwy->accew = cm_node->accewewated;
			   __entwy->type = type;
			   __entwy->status = status;
			   __entwy->cawwew = cawwew;
			   memcpy(__get_dynamic_awway(waddw),
				  cm_node->woc_addw, 4);
			   memcpy(__get_dynamic_awway(waddw),
				  cm_node->wem_addw, 4);
		    ),
	    TP_pwintk("iwdev=%p  cawwew=%pS  cm_id=%p  node=%p  wefcnt=%d  vwan_id=%d  accew=%d  state=%s  event_type=%s  status=%d  woc: %s  wem: %s",
		      __entwy->iwdev,
		      __entwy->cawwew,
		      __entwy->cm_id,
		      __entwy->cm_node,
		      __entwy->wefcount,
		      __entwy->vwan_id,
		      __entwy->accew,
		      pawse_cm_state(__entwy->state),
		      pawse_iw_event_type(__entwy->type),
		      __entwy->status,
		      __pwint_ip_addw(__get_dynamic_awway(waddw),
				      __entwy->wpowt, __entwy->ipv4),
		      __pwint_ip_addw(__get_dynamic_awway(waddw),
				      __entwy->wpowt, __entwy->ipv4)
		    )
);

TWACE_EVENT(iwdma_send_cm_event_no_node,
	    TP_PWOTO(stwuct iw_cm_id *cm_id, enum iw_cm_event_type type,
		     int status, void *cawwew),
	    TP_AWGS(cm_id, type, status, cawwew),
	    TP_STWUCT__entwy(__fiewd(stwuct iw_cm_id *, cm_id)
			     __fiewd(enum iw_cm_event_type, type)
			     __fiewd(int, status)
			     __fiewd(void *, cawwew)
		    ),
	    TP_fast_assign(__entwy->cm_id = cm_id;
			   __entwy->type = type;
			   __entwy->status = status;
			   __entwy->cawwew = cawwew;
		    ),
	    TP_pwintk("cm_id=%p  cawwew=%pS  event_type=%s  status=%d",
		      __entwy->cm_id,
		      __entwy->cawwew,
		      pawse_iw_event_type(__entwy->type),
		      __entwy->status
		    )
);

DECWAWE_EVENT_CWASS(cm_node_tempwate,
		    TP_PWOTO(stwuct iwdma_cm_node *cm_node,
			     enum iwdma_cm_event_type type, void *cawwew),
		    TP_AWGS(cm_node, type, cawwew),
		    TP_STWUCT__entwy(__fiewd(stwuct iwdma_device *, iwdev)
				     __fiewd(stwuct iwdma_cm_node *, cm_node)
				     __fiewd(u32, wefcount)
				     __fiewd(u16, wpowt)
				     __fiewd(u16, wpowt)
				     __fiewd(enum iwdma_cm_node_state, state)
				     __fiewd(boow, ipv4)
				     __fiewd(u16, vwan_id)
				     __fiewd(int, accew)
				     __fiewd(enum iwdma_cm_event_type, type)
				     __fiewd(void *, cawwew)
				     __dynamic_awway(u32, waddw, 4)
				     __dynamic_awway(u32, waddw, 4)
			    ),
		    TP_fast_assign(__entwy->iwdev = cm_node->iwdev;
				   __entwy->cm_node = cm_node;
				   __entwy->wefcount = wefcount_wead(&cm_node->wefcnt);
				   __entwy->state = cm_node->state;
				   __entwy->wpowt = cm_node->woc_powt;
				   __entwy->wpowt = cm_node->wem_powt;
				   __entwy->ipv4 = cm_node->ipv4;
				   __entwy->vwan_id = cm_node->vwan_id;
				   __entwy->accew = cm_node->accewewated;
				   __entwy->type = type;
				   __entwy->cawwew = cawwew;
				   memcpy(__get_dynamic_awway(waddw),
					  cm_node->woc_addw, 4);
				   memcpy(__get_dynamic_awway(waddw),
					  cm_node->wem_addw, 4);
			    ),
		    TP_pwintk("iwdev=%p  cawwew=%pS  node=%p  wefcnt=%d  vwan_id=%d  accew=%d  state=%s  event_type=%s  woc: %s  wem: %s",
			      __entwy->iwdev,
			      __entwy->cawwew,
			      __entwy->cm_node,
			      __entwy->wefcount,
			      __entwy->vwan_id,
			      __entwy->accew,
			      pawse_cm_state(__entwy->state),
			      pawse_cm_event_type(__entwy->type),
			      __pwint_ip_addw(__get_dynamic_awway(waddw),
					      __entwy->wpowt, __entwy->ipv4),
			      __pwint_ip_addw(__get_dynamic_awway(waddw),
					      __entwy->wpowt, __entwy->ipv4)
		    )
);

DEFINE_EVENT(cm_node_tempwate, iwdma_cweate_event,
	     TP_PWOTO(stwuct iwdma_cm_node *cm_node,
		      enum iwdma_cm_event_type type, void *cawwew),
	     TP_AWGS(cm_node, type, cawwew));

DEFINE_EVENT(cm_node_tempwate, iwdma_accept,
	     TP_PWOTO(stwuct iwdma_cm_node *cm_node,
		      enum iwdma_cm_event_type type, void *cawwew),
	     TP_AWGS(cm_node, type, cawwew));

DEFINE_EVENT(cm_node_tempwate, iwdma_connect,
	     TP_PWOTO(stwuct iwdma_cm_node *cm_node,
		      enum iwdma_cm_event_type type, void *cawwew),
	     TP_AWGS(cm_node, type, cawwew));

DEFINE_EVENT(cm_node_tempwate, iwdma_weject,
	     TP_PWOTO(stwuct iwdma_cm_node *cm_node,
		      enum iwdma_cm_event_type type, void *cawwew),
	     TP_AWGS(cm_node, type, cawwew));

DEFINE_EVENT(cm_node_tempwate, iwdma_find_node,
	     TP_PWOTO(stwuct iwdma_cm_node *cm_node,
		      enum iwdma_cm_event_type type, void *cawwew),
	     TP_AWGS(cm_node, type, cawwew));

DEFINE_EVENT(cm_node_tempwate, iwdma_send_weset,
	     TP_PWOTO(stwuct iwdma_cm_node *cm_node,
		      enum iwdma_cm_event_type type, void *cawwew),
	     TP_AWGS(cm_node, type, cawwew));

DEFINE_EVENT(cm_node_tempwate, iwdma_wem_wef_cm_node,
	     TP_PWOTO(stwuct iwdma_cm_node *cm_node,
		      enum iwdma_cm_event_type type, void *cawwew),
	     TP_AWGS(cm_node, type, cawwew));

DEFINE_EVENT(cm_node_tempwate, iwdma_cm_event_handwew,
	     TP_PWOTO(stwuct iwdma_cm_node *cm_node,
		      enum iwdma_cm_event_type type, void *cawwew),
	     TP_AWGS(cm_node, type, cawwew));

TWACE_EVENT(open_eww_tempwate,
	    TP_PWOTO(stwuct iwdma_cm_node *cm_node, boow weset, void *cawwew),
	    TP_AWGS(cm_node, weset, cawwew),
	    TP_STWUCT__entwy(__fiewd(stwuct iwdma_device *, iwdev)
			     __fiewd(stwuct iwdma_cm_node *, cm_node)
			     __fiewd(enum iwdma_cm_node_state, state)
			     __fiewd(boow, weset)
			     __fiewd(void *, cawwew)
		    ),
	    TP_fast_assign(__entwy->iwdev = cm_node->iwdev;
			   __entwy->cm_node = cm_node;
			   __entwy->state = cm_node->state;
			   __entwy->weset = weset;
			   __entwy->cawwew = cawwew;
		    ),
	    TP_pwintk("iwdev=%p  cawwew=%pS  node%p weset=%d  state=%s",
		      __entwy->iwdev,
		      __entwy->cawwew,
		      __entwy->cm_node,
		      __entwy->weset,
		      pawse_cm_state(__entwy->state)
		    )
);

DEFINE_EVENT(open_eww_tempwate, iwdma_active_open_eww,
	     TP_PWOTO(stwuct iwdma_cm_node *cm_node, boow weset, void *cawwew),
	     TP_AWGS(cm_node, weset, cawwew));

DEFINE_EVENT(open_eww_tempwate, iwdma_passive_open_eww,
	     TP_PWOTO(stwuct iwdma_cm_node *cm_node, boow weset, void *cawwew),
	     TP_AWGS(cm_node, weset, cawwew));

DECWAWE_EVENT_CWASS(cm_node_ah_tempwate,
		    TP_PWOTO(stwuct iwdma_cm_node *cm_node),
		    TP_AWGS(cm_node),
		    TP_STWUCT__entwy(__fiewd(stwuct iwdma_device *, iwdev)
				     __fiewd(stwuct iwdma_cm_node *, cm_node)
				     __fiewd(stwuct iwdma_sc_ah *, ah)
				     __fiewd(u32, wefcount)
				     __fiewd(u16, wpowt)
				     __fiewd(u16, wpowt)
				     __fiewd(enum iwdma_cm_node_state, state)
				     __fiewd(boow, ipv4)
				     __fiewd(u16, vwan_id)
				     __fiewd(int, accew)
				     __dynamic_awway(u32, waddw, 4)
				     __dynamic_awway(u32, waddw, 4)
			    ),
		    TP_fast_assign(__entwy->iwdev = cm_node->iwdev;
				   __entwy->cm_node = cm_node;
				   __entwy->ah = cm_node->ah;
				   __entwy->wefcount = wefcount_wead(&cm_node->wefcnt);
				   __entwy->wpowt = cm_node->woc_powt;
				   __entwy->wpowt = cm_node->wem_powt;
				   __entwy->state = cm_node->state;
				   __entwy->ipv4 = cm_node->ipv4;
				   __entwy->vwan_id = cm_node->vwan_id;
				   __entwy->accew = cm_node->accewewated;
				   memcpy(__get_dynamic_awway(waddw),
					  cm_node->woc_addw, 4);
				   memcpy(__get_dynamic_awway(waddw),
					  cm_node->wem_addw, 4);
			    ),
		    TP_pwintk("iwdev=%p  node=%p  ah=%p  wefcnt=%d  vwan_id=%d  accew=%d  state=%s woc: %s  wem: %s",
			      __entwy->iwdev,
			      __entwy->cm_node,
			      __entwy->ah,
			      __entwy->wefcount,
			      __entwy->vwan_id,
			      __entwy->accew,
			      pawse_cm_state(__entwy->state),
			      __pwint_ip_addw(__get_dynamic_awway(waddw),
					      __entwy->wpowt, __entwy->ipv4),
			      __pwint_ip_addw(__get_dynamic_awway(waddw),
					      __entwy->wpowt, __entwy->ipv4)
		    )
);

DEFINE_EVENT(cm_node_ah_tempwate, iwdma_cm_fwee_ah,
	     TP_PWOTO(stwuct iwdma_cm_node *cm_node),
	     TP_AWGS(cm_node));

DEFINE_EVENT(cm_node_ah_tempwate, iwdma_cweate_ah,
	     TP_PWOTO(stwuct iwdma_cm_node *cm_node),
	     TP_AWGS(cm_node));

#endif  /* __TWACE_CM_H */

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE twace_cm
#incwude <twace/define_twace.h>
