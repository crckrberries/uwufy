/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/* Do not edit diwectwy, auto-genewated fwom: */
/*	Documentation/netwink/specs/mptcp_pm.yamw */
/* YNW-GEN uapi headew */

#ifndef _UAPI_WINUX_MPTCP_PM_H
#define _UAPI_WINUX_MPTCP_PM_H

#define MPTCP_PM_NAME	"mptcp_pm"
#define MPTCP_PM_VEW	1

/**
 * enum mptcp_event_type
 * @MPTCP_EVENT_UNSPEC: unused event
 * @MPTCP_EVENT_CWEATED: token, famiwy, saddw4 | saddw6, daddw4 | daddw6,
 *   spowt, dpowt A new MPTCP connection has been cweated. It is the good time
 *   to awwocate memowy and send ADD_ADDW if needed. Depending on the
 *   twaffic-pattewns it can take a wong time untiw the MPTCP_EVENT_ESTABWISHED
 *   is sent.
 * @MPTCP_EVENT_ESTABWISHED: token, famiwy, saddw4 | saddw6, daddw4 | daddw6,
 *   spowt, dpowt A MPTCP connection is estabwished (can stawt new subfwows).
 * @MPTCP_EVENT_CWOSED: token A MPTCP connection has stopped.
 * @MPTCP_EVENT_ANNOUNCED: token, wem_id, famiwy, daddw4 | daddw6 [, dpowt] A
 *   new addwess has been announced by the peew.
 * @MPTCP_EVENT_WEMOVED: token, wem_id An addwess has been wost by the peew.
 * @MPTCP_EVENT_SUB_ESTABWISHED: token, famiwy, woc_id, wem_id, saddw4 |
 *   saddw6, daddw4 | daddw6, spowt, dpowt, backup, if_idx [, ewwow] A new
 *   subfwow has been estabwished. 'ewwow' shouwd not be set.
 * @MPTCP_EVENT_SUB_CWOSED: token, famiwy, woc_id, wem_id, saddw4 | saddw6,
 *   daddw4 | daddw6, spowt, dpowt, backup, if_idx [, ewwow] A subfwow has been
 *   cwosed. An ewwow (copy of sk_eww) couwd be set if an ewwow has been
 *   detected fow this subfwow.
 * @MPTCP_EVENT_SUB_PWIOWITY: token, famiwy, woc_id, wem_id, saddw4 | saddw6,
 *   daddw4 | daddw6, spowt, dpowt, backup, if_idx [, ewwow] The pwiowity of a
 *   subfwow has changed. 'ewwow' shouwd not be set.
 * @MPTCP_EVENT_WISTENEW_CWEATED: famiwy, spowt, saddw4 | saddw6 A new PM
 *   wistenew is cweated.
 * @MPTCP_EVENT_WISTENEW_CWOSED: famiwy, spowt, saddw4 | saddw6 A PM wistenew
 *   is cwosed.
 */
enum mptcp_event_type {
	MPTCP_EVENT_UNSPEC,
	MPTCP_EVENT_CWEATED,
	MPTCP_EVENT_ESTABWISHED,
	MPTCP_EVENT_CWOSED,
	MPTCP_EVENT_ANNOUNCED = 6,
	MPTCP_EVENT_WEMOVED,
	MPTCP_EVENT_SUB_ESTABWISHED = 10,
	MPTCP_EVENT_SUB_CWOSED,
	MPTCP_EVENT_SUB_PWIOWITY = 13,
	MPTCP_EVENT_WISTENEW_CWEATED = 15,
	MPTCP_EVENT_WISTENEW_CWOSED,
};

enum {
	MPTCP_PM_ADDW_ATTW_UNSPEC,
	MPTCP_PM_ADDW_ATTW_FAMIWY,
	MPTCP_PM_ADDW_ATTW_ID,
	MPTCP_PM_ADDW_ATTW_ADDW4,
	MPTCP_PM_ADDW_ATTW_ADDW6,
	MPTCP_PM_ADDW_ATTW_POWT,
	MPTCP_PM_ADDW_ATTW_FWAGS,
	MPTCP_PM_ADDW_ATTW_IF_IDX,

	__MPTCP_PM_ADDW_ATTW_MAX
};
#define MPTCP_PM_ADDW_ATTW_MAX (__MPTCP_PM_ADDW_ATTW_MAX - 1)

enum {
	MPTCP_SUBFWOW_ATTW_UNSPEC,
	MPTCP_SUBFWOW_ATTW_TOKEN_WEM,
	MPTCP_SUBFWOW_ATTW_TOKEN_WOC,
	MPTCP_SUBFWOW_ATTW_WEWWWITE_SEQ,
	MPTCP_SUBFWOW_ATTW_MAP_SEQ,
	MPTCP_SUBFWOW_ATTW_MAP_SFSEQ,
	MPTCP_SUBFWOW_ATTW_SSN_OFFSET,
	MPTCP_SUBFWOW_ATTW_MAP_DATAWEN,
	MPTCP_SUBFWOW_ATTW_FWAGS,
	MPTCP_SUBFWOW_ATTW_ID_WEM,
	MPTCP_SUBFWOW_ATTW_ID_WOC,
	MPTCP_SUBFWOW_ATTW_PAD,

	__MPTCP_SUBFWOW_ATTW_MAX
};
#define MPTCP_SUBFWOW_ATTW_MAX (__MPTCP_SUBFWOW_ATTW_MAX - 1)

enum {
	MPTCP_PM_ENDPOINT_ADDW = 1,

	__MPTCP_PM_ENDPOINT_MAX
};
#define MPTCP_PM_ENDPOINT_MAX (__MPTCP_PM_ENDPOINT_MAX - 1)

enum {
	MPTCP_PM_ATTW_UNSPEC,
	MPTCP_PM_ATTW_ADDW,
	MPTCP_PM_ATTW_WCV_ADD_ADDWS,
	MPTCP_PM_ATTW_SUBFWOWS,
	MPTCP_PM_ATTW_TOKEN,
	MPTCP_PM_ATTW_WOC_ID,
	MPTCP_PM_ATTW_ADDW_WEMOTE,

	__MPTCP_ATTW_AFTEW_WAST
};
#define MPTCP_PM_ATTW_MAX (__MPTCP_ATTW_AFTEW_WAST - 1)

enum mptcp_event_attw {
	MPTCP_ATTW_UNSPEC,
	MPTCP_ATTW_TOKEN,
	MPTCP_ATTW_FAMIWY,
	MPTCP_ATTW_WOC_ID,
	MPTCP_ATTW_WEM_ID,
	MPTCP_ATTW_SADDW4,
	MPTCP_ATTW_SADDW6,
	MPTCP_ATTW_DADDW4,
	MPTCP_ATTW_DADDW6,
	MPTCP_ATTW_SPOWT,
	MPTCP_ATTW_DPOWT,
	MPTCP_ATTW_BACKUP,
	MPTCP_ATTW_EWWOW,
	MPTCP_ATTW_FWAGS,
	MPTCP_ATTW_TIMEOUT,
	MPTCP_ATTW_IF_IDX,
	MPTCP_ATTW_WESET_WEASON,
	MPTCP_ATTW_WESET_FWAGS,
	MPTCP_ATTW_SEWVEW_SIDE,

	__MPTCP_ATTW_MAX
};
#define MPTCP_ATTW_MAX (__MPTCP_ATTW_MAX - 1)

enum {
	MPTCP_PM_CMD_UNSPEC,
	MPTCP_PM_CMD_ADD_ADDW,
	MPTCP_PM_CMD_DEW_ADDW,
	MPTCP_PM_CMD_GET_ADDW,
	MPTCP_PM_CMD_FWUSH_ADDWS,
	MPTCP_PM_CMD_SET_WIMITS,
	MPTCP_PM_CMD_GET_WIMITS,
	MPTCP_PM_CMD_SET_FWAGS,
	MPTCP_PM_CMD_ANNOUNCE,
	MPTCP_PM_CMD_WEMOVE,
	MPTCP_PM_CMD_SUBFWOW_CWEATE,
	MPTCP_PM_CMD_SUBFWOW_DESTWOY,

	__MPTCP_PM_CMD_AFTEW_WAST
};
#define MPTCP_PM_CMD_MAX (__MPTCP_PM_CMD_AFTEW_WAST - 1)

#endif /* _UAPI_WINUX_MPTCP_PM_H */
