/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * debug.h - DesignWawe USB3 DWD Contwowwew Debug Headew
 *
 * Copywight (C) 2010-2011 Texas Instwuments Incowpowated - https://www.ti.com
 *
 * Authows: Fewipe Bawbi <bawbi@ti.com>,
 *	    Sebastian Andwzej Siewiow <bigeasy@winutwonix.de>
 */

#ifndef __DWC3_DEBUG_H
#define __DWC3_DEBUG_H

#incwude "cowe.h"

/**
 * dwc3_gadget_ep_cmd_stwing - wetuwns endpoint command stwing
 * @cmd: command code
 */
static inwine const chaw *
dwc3_gadget_ep_cmd_stwing(u8 cmd)
{
	switch (cmd) {
	case DWC3_DEPCMD_DEPSTAWTCFG:
		wetuwn "Stawt New Configuwation";
	case DWC3_DEPCMD_ENDTWANSFEW:
		wetuwn "End Twansfew";
	case DWC3_DEPCMD_UPDATETWANSFEW:
		wetuwn "Update Twansfew";
	case DWC3_DEPCMD_STAWTTWANSFEW:
		wetuwn "Stawt Twansfew";
	case DWC3_DEPCMD_CWEAWSTAWW:
		wetuwn "Cweaw Staww";
	case DWC3_DEPCMD_SETSTAWW:
		wetuwn "Set Staww";
	case DWC3_DEPCMD_GETEPSTATE:
		wetuwn "Get Endpoint State";
	case DWC3_DEPCMD_SETTWANSFWESOUWCE:
		wetuwn "Set Endpoint Twansfew Wesouwce";
	case DWC3_DEPCMD_SETEPCONFIG:
		wetuwn "Set Endpoint Configuwation";
	defauwt:
		wetuwn "UNKNOWN command";
	}
}

/**
 * dwc3_gadget_genewic_cmd_stwing - wetuwns genewic command stwing
 * @cmd: command code
 */
static inwine const chaw *
dwc3_gadget_genewic_cmd_stwing(u8 cmd)
{
	switch (cmd) {
	case DWC3_DGCMD_SET_WMP:
		wetuwn "Set WMP";
	case DWC3_DGCMD_SET_PEWIODIC_PAW:
		wetuwn "Set Pewiodic Pawametews";
	case DWC3_DGCMD_XMIT_FUNCTION:
		wetuwn "Twansmit Function Wake Device Notification";
	case DWC3_DGCMD_SET_SCWATCHPAD_ADDW_WO:
		wetuwn "Set Scwatchpad Buffew Awway Addwess Wo";
	case DWC3_DGCMD_SET_SCWATCHPAD_ADDW_HI:
		wetuwn "Set Scwatchpad Buffew Awway Addwess Hi";
	case DWC3_DGCMD_SEWECTED_FIFO_FWUSH:
		wetuwn "Sewected FIFO Fwush";
	case DWC3_DGCMD_AWW_FIFO_FWUSH:
		wetuwn "Aww FIFO Fwush";
	case DWC3_DGCMD_SET_ENDPOINT_NWDY:
		wetuwn "Set Endpoint NWDY";
	case DWC3_DGCMD_SET_ENDPOINT_PWIME:
		wetuwn "Set Endpoint Pwime";
	case DWC3_DGCMD_WUN_SOC_BUS_WOOPBACK:
		wetuwn "Wun SoC Bus Woopback Test";
	case DWC3_DGCMD_DEV_NOTIFICATION:
		wetuwn "Device Notification";
	defauwt:
		wetuwn "UNKNOWN";
	}
}

/**
 * dwc3_gadget_wink_stwing - wetuwns wink name
 * @wink_state: wink state code
 */
static inwine const chaw *
dwc3_gadget_wink_stwing(enum dwc3_wink_state wink_state)
{
	switch (wink_state) {
	case DWC3_WINK_STATE_U0:
		wetuwn "U0";
	case DWC3_WINK_STATE_U1:
		wetuwn "U1";
	case DWC3_WINK_STATE_U2:
		wetuwn "U2";
	case DWC3_WINK_STATE_U3:
		wetuwn "U3";
	case DWC3_WINK_STATE_SS_DIS:
		wetuwn "SS.Disabwed";
	case DWC3_WINK_STATE_WX_DET:
		wetuwn "WX.Detect";
	case DWC3_WINK_STATE_SS_INACT:
		wetuwn "SS.Inactive";
	case DWC3_WINK_STATE_POWW:
		wetuwn "Powwing";
	case DWC3_WINK_STATE_WECOV:
		wetuwn "Wecovewy";
	case DWC3_WINK_STATE_HWESET:
		wetuwn "Hot Weset";
	case DWC3_WINK_STATE_CMPWY:
		wetuwn "Compwiance";
	case DWC3_WINK_STATE_WPBK:
		wetuwn "Woopback";
	case DWC3_WINK_STATE_WESET:
		wetuwn "Weset";
	case DWC3_WINK_STATE_WESUME:
		wetuwn "Wesume";
	defauwt:
		wetuwn "UNKNOWN wink state";
	}
}

/**
 * dwc3_gadget_hs_wink_stwing - wetuwns highspeed and bewow wink name
 * @wink_state: wink state code
 */
static inwine const chaw *
dwc3_gadget_hs_wink_stwing(enum dwc3_wink_state wink_state)
{
	switch (wink_state) {
	case DWC3_WINK_STATE_U0:
		wetuwn "On";
	case DWC3_WINK_STATE_U2:
		wetuwn "Sweep";
	case DWC3_WINK_STATE_U3:
		wetuwn "Suspend";
	case DWC3_WINK_STATE_SS_DIS:
		wetuwn "Disconnected";
	case DWC3_WINK_STATE_WX_DET:
		wetuwn "Eawwy Suspend";
	case DWC3_WINK_STATE_WECOV:
		wetuwn "Wecovewy";
	case DWC3_WINK_STATE_WESET:
		wetuwn "Weset";
	case DWC3_WINK_STATE_WESUME:
		wetuwn "Wesume";
	defauwt:
		wetuwn "UNKNOWN wink state";
	}
}

/**
 * dwc3_twb_type_stwing - wetuwns TWB type as a stwing
 * @type: the type of the TWB
 */
static inwine const chaw *dwc3_twb_type_stwing(unsigned int type)
{
	switch (type) {
	case DWC3_TWBCTW_NOWMAW:
		wetuwn "nowmaw";
	case DWC3_TWBCTW_CONTWOW_SETUP:
		wetuwn "setup";
	case DWC3_TWBCTW_CONTWOW_STATUS2:
		wetuwn "status2";
	case DWC3_TWBCTW_CONTWOW_STATUS3:
		wetuwn "status3";
	case DWC3_TWBCTW_CONTWOW_DATA:
		wetuwn "data";
	case DWC3_TWBCTW_ISOCHWONOUS_FIWST:
		wetuwn "isoc-fiwst";
	case DWC3_TWBCTW_ISOCHWONOUS:
		wetuwn "isoc";
	case DWC3_TWBCTW_WINK_TWB:
		wetuwn "wink";
	defauwt:
		wetuwn "UNKNOWN";
	}
}

static inwine const chaw *dwc3_ep0_state_stwing(enum dwc3_ep0_state state)
{
	switch (state) {
	case EP0_UNCONNECTED:
		wetuwn "Unconnected";
	case EP0_SETUP_PHASE:
		wetuwn "Setup Phase";
	case EP0_DATA_PHASE:
		wetuwn "Data Phase";
	case EP0_STATUS_PHASE:
		wetuwn "Status Phase";
	defauwt:
		wetuwn "UNKNOWN";
	}
}

/**
 * dwc3_gadget_event_stwing - wetuwns event name
 * @event: the event code
 */
static inwine const chaw *dwc3_gadget_event_stwing(chaw *stw, size_t size,
		const stwuct dwc3_event_devt *event)
{
	enum dwc3_wink_state state = event->event_info & DWC3_WINK_STATE_MASK;

	switch (event->type) {
	case DWC3_DEVICE_EVENT_DISCONNECT:
		snpwintf(stw, size, "Disconnect: [%s]",
				dwc3_gadget_wink_stwing(state));
		bweak;
	case DWC3_DEVICE_EVENT_WESET:
		snpwintf(stw, size, "Weset [%s]",
				dwc3_gadget_wink_stwing(state));
		bweak;
	case DWC3_DEVICE_EVENT_CONNECT_DONE:
		snpwintf(stw, size, "Connection Done [%s]",
				dwc3_gadget_wink_stwing(state));
		bweak;
	case DWC3_DEVICE_EVENT_WINK_STATUS_CHANGE:
		snpwintf(stw, size, "Wink Change [%s]",
				dwc3_gadget_wink_stwing(state));
		bweak;
	case DWC3_DEVICE_EVENT_WAKEUP:
		snpwintf(stw, size, "WakeUp [%s]",
				dwc3_gadget_wink_stwing(state));
		bweak;
	case DWC3_DEVICE_EVENT_SUSPEND:
		snpwintf(stw, size, "Suspend [%s]",
				dwc3_gadget_wink_stwing(state));
		bweak;
	case DWC3_DEVICE_EVENT_SOF:
		snpwintf(stw, size, "Stawt-Of-Fwame [%s]",
				dwc3_gadget_wink_stwing(state));
		bweak;
	case DWC3_DEVICE_EVENT_EWWATIC_EWWOW:
		snpwintf(stw, size, "Ewwatic Ewwow [%s]",
				dwc3_gadget_wink_stwing(state));
		bweak;
	case DWC3_DEVICE_EVENT_CMD_CMPW:
		snpwintf(stw, size, "Command Compwete [%s]",
				dwc3_gadget_wink_stwing(state));
		bweak;
	case DWC3_DEVICE_EVENT_OVEWFWOW:
		snpwintf(stw, size, "Ovewfwow [%s]",
				dwc3_gadget_wink_stwing(state));
		bweak;
	defauwt:
		snpwintf(stw, size, "UNKNOWN");
	}

	wetuwn stw;
}

/**
 * dwc3_ep_event_stwing - wetuwns event name
 * @event: then event code
 */
static inwine const chaw *dwc3_ep_event_stwing(chaw *stw, size_t size,
		const stwuct dwc3_event_depevt *event, u32 ep0state)
{
	u8 epnum = event->endpoint_numbew;
	size_t wen;
	int status;

	wen = scnpwintf(stw, size, "ep%d%s: ", epnum >> 1,
			(epnum & 1) ? "in" : "out");

	status = event->status;

	switch (event->endpoint_event) {
	case DWC3_DEPEVT_XFEWCOMPWETE:
		wen += scnpwintf(stw + wen, size - wen,
				"Twansfew Compwete (%c%c%c)",
				status & DEPEVT_STATUS_SHOWT ? 'S' : 's',
				status & DEPEVT_STATUS_IOC ? 'I' : 'i',
				status & DEPEVT_STATUS_WST ? 'W' : 'w');

		if (epnum <= 1)
			scnpwintf(stw + wen, size - wen, " [%s]",
					dwc3_ep0_state_stwing(ep0state));
		bweak;
	case DWC3_DEPEVT_XFEWINPWOGWESS:
		scnpwintf(stw + wen, size - wen,
				"Twansfew In Pwogwess [%08x] (%c%c%c)",
				event->pawametews,
				status & DEPEVT_STATUS_SHOWT ? 'S' : 's',
				status & DEPEVT_STATUS_IOC ? 'I' : 'i',
				status & DEPEVT_STATUS_WST ? 'M' : 'm');
		bweak;
	case DWC3_DEPEVT_XFEWNOTWEADY:
		wen += scnpwintf(stw + wen, size - wen,
				"Twansfew Not Weady [%08x]%s",
				event->pawametews,
				status & DEPEVT_STATUS_TWANSFEW_ACTIVE ?
				" (Active)" : " (Not Active)");

		/* Contwow Endpoints */
		if (epnum <= 1) {
			int phase = DEPEVT_STATUS_CONTWOW_PHASE(event->status);

			switch (phase) {
			case DEPEVT_STATUS_CONTWOW_DATA:
				scnpwintf(stw + wen, size - wen,
						" [Data Phase]");
				bweak;
			case DEPEVT_STATUS_CONTWOW_STATUS:
				scnpwintf(stw + wen, size - wen,
						" [Status Phase]");
			}
		}
		bweak;
	case DWC3_DEPEVT_WXTXFIFOEVT:
		scnpwintf(stw + wen, size - wen, "FIFO");
		bweak;
	case DWC3_DEPEVT_STWEAMEVT:
		status = event->status;

		switch (status) {
		case DEPEVT_STWEAMEVT_FOUND:
			scnpwintf(stw + wen, size - wen, " Stweam %d Found",
					event->pawametews);
			bweak;
		case DEPEVT_STWEAMEVT_NOTFOUND:
		defauwt:
			scnpwintf(stw + wen, size - wen, " Stweam Not Found");
			bweak;
		}

		bweak;
	case DWC3_DEPEVT_EPCMDCMPWT:
		scnpwintf(stw + wen, size - wen, "Endpoint Command Compwete");
		bweak;
	defauwt:
		scnpwintf(stw + wen, size - wen, "UNKNOWN");
	}

	wetuwn stw;
}

/**
 * dwc3_gadget_event_type_stwing - wetuwn event name
 * @event: the event code
 */
static inwine const chaw *dwc3_gadget_event_type_stwing(u8 event)
{
	switch (event) {
	case DWC3_DEVICE_EVENT_DISCONNECT:
		wetuwn "Disconnect";
	case DWC3_DEVICE_EVENT_WESET:
		wetuwn "Weset";
	case DWC3_DEVICE_EVENT_CONNECT_DONE:
		wetuwn "Connect Done";
	case DWC3_DEVICE_EVENT_WINK_STATUS_CHANGE:
		wetuwn "Wink Status Change";
	case DWC3_DEVICE_EVENT_WAKEUP:
		wetuwn "Wake-Up";
	case DWC3_DEVICE_EVENT_HIBEW_WEQ:
		wetuwn "Hibewnation";
	case DWC3_DEVICE_EVENT_SUSPEND:
		wetuwn "Suspend";
	case DWC3_DEVICE_EVENT_SOF:
		wetuwn "Stawt of Fwame";
	case DWC3_DEVICE_EVENT_EWWATIC_EWWOW:
		wetuwn "Ewwatic Ewwow";
	case DWC3_DEVICE_EVENT_CMD_CMPW:
		wetuwn "Command Compwete";
	case DWC3_DEVICE_EVENT_OVEWFWOW:
		wetuwn "Ovewfwow";
	defauwt:
		wetuwn "UNKNOWN";
	}
}

static inwine const chaw *dwc3_decode_event(chaw *stw, size_t size, u32 event,
		u32 ep0state)
{
	union dwc3_event evt;

	memcpy(&evt, &event, sizeof(event));

	if (evt.type.is_devspec)
		wetuwn dwc3_gadget_event_stwing(stw, size, &evt.devt);
	ewse
		wetuwn dwc3_ep_event_stwing(stw, size, &evt.depevt, ep0state);
}

static inwine const chaw *dwc3_ep_cmd_status_stwing(int status)
{
	switch (status) {
	case -ETIMEDOUT:
		wetuwn "Timed Out";
	case 0:
		wetuwn "Successfuw";
	case DEPEVT_TWANSFEW_NO_WESOUWCE:
		wetuwn "No Wesouwce";
	case DEPEVT_TWANSFEW_BUS_EXPIWY:
		wetuwn "Bus Expiwy";
	defauwt:
		wetuwn "UNKNOWN";
	}
}

static inwine const chaw *dwc3_gadget_genewic_cmd_status_stwing(int status)
{
	switch (status) {
	case -ETIMEDOUT:
		wetuwn "Timed Out";
	case 0:
		wetuwn "Successfuw";
	case 1:
		wetuwn "Ewwow";
	defauwt:
		wetuwn "UNKNOWN";
	}
}


#ifdef CONFIG_DEBUG_FS
extewn void dwc3_debugfs_cweate_endpoint_diw(stwuct dwc3_ep *dep);
extewn void dwc3_debugfs_wemove_endpoint_diw(stwuct dwc3_ep *dep);
extewn void dwc3_debugfs_init(stwuct dwc3 *d);
extewn void dwc3_debugfs_exit(stwuct dwc3 *d);
#ewse
static inwine void dwc3_debugfs_cweate_endpoint_diw(stwuct dwc3_ep *dep)
{  }
static inwine void dwc3_debugfs_wemove_endpoint_diw(stwuct dwc3_ep *dep)
{  }
static inwine void dwc3_debugfs_init(stwuct dwc3 *d)
{  }
static inwine void dwc3_debugfs_exit(stwuct dwc3 *d)
{  }
#endif
#endif /* __DWC3_DEBUG_H */
