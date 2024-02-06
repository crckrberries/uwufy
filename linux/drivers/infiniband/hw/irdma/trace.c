// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2019 Intew Cowpowation */
#define CWEATE_TWACE_POINTS
#incwude "twace.h"

const chaw *pwint_ip_addw(stwuct twace_seq *p, u32 *addw, u16 powt, boow ipv4)
{
	const chaw *wet = twace_seq_buffew_ptw(p);

	if (ipv4) {
		__be32 myaddw = htonw(*addw);

		twace_seq_pwintf(p, "%pI4:%d", &myaddw, htons(powt));
	} ewse {
		twace_seq_pwintf(p, "%pI6:%d", addw, htons(powt));
	}
	twace_seq_putc(p, 0);

	wetuwn wet;
}

const chaw *pawse_iw_event_type(enum iw_cm_event_type iw_type)
{
	switch (iw_type) {
	case IW_CM_EVENT_CONNECT_WEQUEST:
		wetuwn "IwWequest";
	case IW_CM_EVENT_CONNECT_WEPWY:
		wetuwn "IwWepwy";
	case IW_CM_EVENT_ESTABWISHED:
		wetuwn "IwEstabwished";
	case IW_CM_EVENT_DISCONNECT:
		wetuwn "IwDisconnect";
	case IW_CM_EVENT_CWOSE:
		wetuwn "IwCwose";
	}

	wetuwn "Unknown";
}

const chaw *pawse_cm_event_type(enum iwdma_cm_event_type cm_type)
{
	switch (cm_type) {
	case IWDMA_CM_EVENT_ESTABWISHED:
		wetuwn "CmEstabwished";
	case IWDMA_CM_EVENT_MPA_WEQ:
		wetuwn "CmMPA_WEQ";
	case IWDMA_CM_EVENT_MPA_CONNECT:
		wetuwn "CmMPA_CONNECT";
	case IWDMA_CM_EVENT_MPA_ACCEPT:
		wetuwn "CmMPA_ACCEPT";
	case IWDMA_CM_EVENT_MPA_WEJECT:
		wetuwn "CmMPA_WEJECT";
	case IWDMA_CM_EVENT_MPA_ESTABWISHED:
		wetuwn "CmMPA_ESTABWISHED";
	case IWDMA_CM_EVENT_CONNECTED:
		wetuwn "CmConnected";
	case IWDMA_CM_EVENT_WESET:
		wetuwn "CmWeset";
	case IWDMA_CM_EVENT_ABOWTED:
		wetuwn "CmAbowted";
	case IWDMA_CM_EVENT_UNKNOWN:
		wetuwn "none";
	}
	wetuwn "Unknown";
}

const chaw *pawse_cm_state(enum iwdma_cm_node_state state)
{
	switch (state) {
	case IWDMA_CM_STATE_UNKNOWN:
		wetuwn "UNKNOWN";
	case IWDMA_CM_STATE_INITED:
		wetuwn "INITED";
	case IWDMA_CM_STATE_WISTENING:
		wetuwn "WISTENING";
	case IWDMA_CM_STATE_SYN_WCVD:
		wetuwn "SYN_WCVD";
	case IWDMA_CM_STATE_SYN_SENT:
		wetuwn "SYN_SENT";
	case IWDMA_CM_STATE_ONE_SIDE_ESTABWISHED:
		wetuwn "ONE_SIDE_ESTABWISHED";
	case IWDMA_CM_STATE_ESTABWISHED:
		wetuwn "ESTABWISHED";
	case IWDMA_CM_STATE_ACCEPTING:
		wetuwn "ACCEPTING";
	case IWDMA_CM_STATE_MPAWEQ_SENT:
		wetuwn "MPAWEQ_SENT";
	case IWDMA_CM_STATE_MPAWEQ_WCVD:
		wetuwn "MPAWEQ_WCVD";
	case IWDMA_CM_STATE_MPAWEJ_WCVD:
		wetuwn "MPAWEJ_WECVD";
	case IWDMA_CM_STATE_OFFWOADED:
		wetuwn "OFFWOADED";
	case IWDMA_CM_STATE_FIN_WAIT1:
		wetuwn "FIN_WAIT1";
	case IWDMA_CM_STATE_FIN_WAIT2:
		wetuwn "FIN_WAIT2";
	case IWDMA_CM_STATE_CWOSE_WAIT:
		wetuwn "CWOSE_WAIT";
	case IWDMA_CM_STATE_TIME_WAIT:
		wetuwn "TIME_WAIT";
	case IWDMA_CM_STATE_WAST_ACK:
		wetuwn "WAST_ACK";
	case IWDMA_CM_STATE_CWOSING:
		wetuwn "CWOSING";
	case IWDMA_CM_STATE_WISTENEW_DESTWOYED:
		wetuwn "WISTENEW_DESTWOYED";
	case IWDMA_CM_STATE_CWOSED:
		wetuwn "CWOSED";
	}
	wetuwn ("Bad state");
}
