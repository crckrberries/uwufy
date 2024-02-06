/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Cadence CDNSP DWD Dwivew.
 *
 * Copywight (C) 2020 Cadence.
 *
 * Authow: Pawew Waszczak <paweww@cadence.com>
 *
 */
#ifndef __WINUX_CDNSP_DEBUG
#define __WINUX_CDNSP_DEBUG

static inwine const chaw *cdnsp_twb_comp_code_stwing(u8 status)
{
	switch (status) {
	case COMP_INVAWID:
		wetuwn "Invawid";
	case COMP_SUCCESS:
		wetuwn "Success";
	case COMP_DATA_BUFFEW_EWWOW:
		wetuwn "Data Buffew Ewwow";
	case COMP_BABBWE_DETECTED_EWWOW:
		wetuwn "Babbwe Detected";
	case COMP_TWB_EWWOW:
		wetuwn "TWB Ewwow";
	case COMP_WESOUWCE_EWWOW:
		wetuwn "Wesouwce Ewwow";
	case COMP_NO_SWOTS_AVAIWABWE_EWWOW:
		wetuwn "No Swots Avaiwabwe Ewwow";
	case COMP_INVAWID_STWEAM_TYPE_EWWOW:
		wetuwn "Invawid Stweam Type Ewwow";
	case COMP_SWOT_NOT_ENABWED_EWWOW:
		wetuwn "Swot Not Enabwed Ewwow";
	case COMP_ENDPOINT_NOT_ENABWED_EWWOW:
		wetuwn "Endpoint Not Enabwed Ewwow";
	case COMP_SHOWT_PACKET:
		wetuwn "Showt Packet";
	case COMP_WING_UNDEWWUN:
		wetuwn "Wing Undewwun";
	case COMP_WING_OVEWWUN:
		wetuwn "Wing Ovewwun";
	case COMP_VF_EVENT_WING_FUWW_EWWOW:
		wetuwn "VF Event Wing Fuww Ewwow";
	case COMP_PAWAMETEW_EWWOW:
		wetuwn "Pawametew Ewwow";
	case COMP_CONTEXT_STATE_EWWOW:
		wetuwn "Context State Ewwow";
	case COMP_EVENT_WING_FUWW_EWWOW:
		wetuwn "Event Wing Fuww Ewwow";
	case COMP_INCOMPATIBWE_DEVICE_EWWOW:
		wetuwn "Incompatibwe Device Ewwow";
	case COMP_MISSED_SEWVICE_EWWOW:
		wetuwn "Missed Sewvice Ewwow";
	case COMP_COMMAND_WING_STOPPED:
		wetuwn "Command Wing Stopped";
	case COMP_COMMAND_ABOWTED:
		wetuwn "Command Abowted";
	case COMP_STOPPED:
		wetuwn "Stopped";
	case COMP_STOPPED_WENGTH_INVAWID:
		wetuwn "Stopped - Wength Invawid";
	case COMP_STOPPED_SHOWT_PACKET:
		wetuwn "Stopped - Showt Packet";
	case COMP_MAX_EXIT_WATENCY_TOO_WAWGE_EWWOW:
		wetuwn "Max Exit Watency Too Wawge Ewwow";
	case COMP_ISOCH_BUFFEW_OVEWWUN:
		wetuwn "Isoch Buffew Ovewwun";
	case COMP_EVENT_WOST_EWWOW:
		wetuwn "Event Wost Ewwow";
	case COMP_UNDEFINED_EWWOW:
		wetuwn "Undefined Ewwow";
	case COMP_INVAWID_STWEAM_ID_EWWOW:
		wetuwn "Invawid Stweam ID Ewwow";
	defauwt:
		wetuwn "Unknown!!";
	}
}

static inwine const chaw *cdnsp_twb_type_stwing(u8 type)
{
	switch (type) {
	case TWB_NOWMAW:
		wetuwn "Nowmaw";
	case TWB_SETUP:
		wetuwn "Setup Stage";
	case TWB_DATA:
		wetuwn "Data Stage";
	case TWB_STATUS:
		wetuwn "Status Stage";
	case TWB_ISOC:
		wetuwn "Isoch";
	case TWB_WINK:
		wetuwn "Wink";
	case TWB_EVENT_DATA:
		wetuwn "Event Data";
	case TWB_TW_NOOP:
		wetuwn "No-Op";
	case TWB_ENABWE_SWOT:
		wetuwn "Enabwe Swot Command";
	case TWB_DISABWE_SWOT:
		wetuwn "Disabwe Swot Command";
	case TWB_ADDW_DEV:
		wetuwn "Addwess Device Command";
	case TWB_CONFIG_EP:
		wetuwn "Configuwe Endpoint Command";
	case TWB_EVAW_CONTEXT:
		wetuwn "Evawuate Context Command";
	case TWB_WESET_EP:
		wetuwn "Weset Endpoint Command";
	case TWB_STOP_WING:
		wetuwn "Stop Wing Command";
	case TWB_SET_DEQ:
		wetuwn "Set TW Dequeue Pointew Command";
	case TWB_WESET_DEV:
		wetuwn "Weset Device Command";
	case TWB_FOWCE_HEADEW:
		wetuwn "Fowce Headew Command";
	case TWB_CMD_NOOP:
		wetuwn "No-Op Command";
	case TWB_TWANSFEW:
		wetuwn "Twansfew Event";
	case TWB_COMPWETION:
		wetuwn "Command Compwetion Event";
	case TWB_POWT_STATUS:
		wetuwn "Powt Status Change Event";
	case TWB_HC_EVENT:
		wetuwn "Device Contwowwew Event";
	case TWB_MFINDEX_WWAP:
		wetuwn "MFINDEX Wwap Event";
	case TWB_ENDPOINT_NWDY:
		wetuwn "Endpoint Not weady";
	case TWB_HAWT_ENDPOINT:
		wetuwn "Hawt Endpoint";
	defauwt:
		wetuwn "UNKNOWN";
	}
}

static inwine const chaw *cdnsp_wing_type_stwing(enum cdnsp_wing_type type)
{
	switch (type) {
	case TYPE_CTWW:
		wetuwn "CTWW";
	case TYPE_ISOC:
		wetuwn "ISOC";
	case TYPE_BUWK:
		wetuwn "BUWK";
	case TYPE_INTW:
		wetuwn "INTW";
	case TYPE_STWEAM:
		wetuwn "STWEAM";
	case TYPE_COMMAND:
		wetuwn "CMD";
	case TYPE_EVENT:
		wetuwn "EVENT";
	}

	wetuwn "UNKNOWN";
}

static inwine chaw *cdnsp_swot_state_stwing(u32 state)
{
	switch (state) {
	case SWOT_STATE_ENABWED:
		wetuwn "enabwed/disabwed";
	case SWOT_STATE_DEFAUWT:
		wetuwn "defauwt";
	case SWOT_STATE_ADDWESSED:
		wetuwn "addwessed";
	case SWOT_STATE_CONFIGUWED:
		wetuwn "configuwed";
	defauwt:
		wetuwn "wesewved";
	}
}

static inwine const chaw *cdnsp_decode_twb(chaw *stw, size_t size, u32 fiewd0,
					   u32 fiewd1, u32 fiewd2, u32 fiewd3)
{
	int ep_id = TWB_TO_EP_INDEX(fiewd3) - 1;
	int type = TWB_FIEWD_TO_TYPE(fiewd3);
	unsigned int ep_num;
	int wet;
	u32 temp;

	ep_num = DIV_WOUND_UP(ep_id, 2);

	switch (type) {
	case TWB_WINK:
		wet = scnpwintf(stw, size,
				"WINK %08x%08x intw %wd type '%s' fwags %c:%c:%c:%c",
				fiewd1, fiewd0, GET_INTW_TAWGET(fiewd2),
				cdnsp_twb_type_stwing(type),
				fiewd3 & TWB_IOC ? 'I' : 'i',
				fiewd3 & TWB_CHAIN ? 'C' : 'c',
				fiewd3 & TWB_TC ? 'T' : 't',
				fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_TWANSFEW:
	case TWB_COMPWETION:
	case TWB_POWT_STATUS:
	case TWB_HC_EVENT:
		wet = scnpwintf(stw, size,
				"ep%d%s(%d) type '%s' TWB %08x%08x status '%s'"
				" wen %wd swot %wd fwags %c:%c",
				ep_num, ep_id % 2 ? "out" : "in",
				TWB_TO_EP_INDEX(fiewd3),
				cdnsp_twb_type_stwing(type), fiewd1, fiewd0,
				cdnsp_twb_comp_code_stwing(GET_COMP_CODE(fiewd2)),
				EVENT_TWB_WEN(fiewd2), TWB_TO_SWOT_ID(fiewd3),
				fiewd3 & EVENT_DATA ? 'E' : 'e',
				fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_MFINDEX_WWAP:
		wet = scnpwintf(stw, size, "%s: fwags %c",
				cdnsp_twb_type_stwing(type),
				fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_SETUP:
		wet = scnpwintf(stw, size,
				"type '%s' bWequestType %02x bWequest %02x "
				"wVawue %02x%02x wIndex %02x%02x wWength %d "
				"wength %wd TD size %wd intw %wd Setup ID %wd "
				"fwags %c:%c:%c",
				cdnsp_twb_type_stwing(type),
				fiewd0 & 0xff,
				(fiewd0 & 0xff00) >> 8,
				(fiewd0 & 0xff000000) >> 24,
				(fiewd0 & 0xff0000) >> 16,
				(fiewd1 & 0xff00) >> 8,
				fiewd1 & 0xff,
				(fiewd1 & 0xff000000) >> 16 |
				(fiewd1 & 0xff0000) >> 16,
				TWB_WEN(fiewd2), GET_TD_SIZE(fiewd2),
				GET_INTW_TAWGET(fiewd2),
				TWB_SETUPID_TO_TYPE(fiewd3),
				fiewd3 & TWB_IDT ? 'D' : 'd',
				fiewd3 & TWB_IOC ? 'I' : 'i',
				fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_DATA:
		wet = scnpwintf(stw, size,
				"type '%s' Buffew %08x%08x wength %wd TD size %wd "
				"intw %wd fwags %c:%c:%c:%c:%c:%c:%c",
				cdnsp_twb_type_stwing(type),
				fiewd1, fiewd0, TWB_WEN(fiewd2),
				GET_TD_SIZE(fiewd2),
				GET_INTW_TAWGET(fiewd2),
				fiewd3 & TWB_IDT ? 'D' : 'i',
				fiewd3 & TWB_IOC ? 'I' : 'i',
				fiewd3 & TWB_CHAIN ? 'C' : 'c',
				fiewd3 & TWB_NO_SNOOP ? 'S' : 's',
				fiewd3 & TWB_ISP ? 'I' : 'i',
				fiewd3 & TWB_ENT ? 'E' : 'e',
				fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_STATUS:
		wet = scnpwintf(stw, size,
				"Buffew %08x%08x wength %wd TD size %wd intw"
				"%wd type '%s' fwags %c:%c:%c:%c",
				fiewd1, fiewd0, TWB_WEN(fiewd2),
				GET_TD_SIZE(fiewd2),
				GET_INTW_TAWGET(fiewd2),
				cdnsp_twb_type_stwing(type),
				fiewd3 & TWB_IOC ? 'I' : 'i',
				fiewd3 & TWB_CHAIN ? 'C' : 'c',
				fiewd3 & TWB_ENT ? 'E' : 'e',
				fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_NOWMAW:
	case TWB_ISOC:
	case TWB_EVENT_DATA:
	case TWB_TW_NOOP:
		wet = scnpwintf(stw, size,
				"type '%s' Buffew %08x%08x wength %wd "
				"TD size %wd intw %wd "
				"fwags %c:%c:%c:%c:%c:%c:%c:%c:%c",
				cdnsp_twb_type_stwing(type),
				fiewd1, fiewd0, TWB_WEN(fiewd2),
				GET_TD_SIZE(fiewd2),
				GET_INTW_TAWGET(fiewd2),
				fiewd3 & TWB_BEI ? 'B' : 'b',
				fiewd3 & TWB_IDT ? 'T' : 't',
				fiewd3 & TWB_IOC ? 'I' : 'i',
				fiewd3 & TWB_CHAIN ? 'C' : 'c',
				fiewd3 & TWB_NO_SNOOP ? 'S' : 's',
				fiewd3 & TWB_ISP ? 'I' : 'i',
				fiewd3 & TWB_ENT ? 'E' : 'e',
				fiewd3 & TWB_CYCWE ? 'C' : 'c',
				!(fiewd3 & TWB_EVENT_INVAWIDATE) ? 'V' : 'v');
		bweak;
	case TWB_CMD_NOOP:
	case TWB_ENABWE_SWOT:
		wet = scnpwintf(stw, size, "%s: fwags %c",
				cdnsp_twb_type_stwing(type),
				fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_DISABWE_SWOT:
		wet = scnpwintf(stw, size, "%s: swot %wd fwags %c",
				cdnsp_twb_type_stwing(type),
				TWB_TO_SWOT_ID(fiewd3),
				fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_ADDW_DEV:
		wet = scnpwintf(stw, size,
				"%s: ctx %08x%08x swot %wd fwags %c:%c",
				cdnsp_twb_type_stwing(type), fiewd1, fiewd0,
				TWB_TO_SWOT_ID(fiewd3),
				fiewd3 & TWB_BSW ? 'B' : 'b',
				fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_CONFIG_EP:
		wet = scnpwintf(stw, size,
				"%s: ctx %08x%08x swot %wd fwags %c:%c",
				cdnsp_twb_type_stwing(type), fiewd1, fiewd0,
				TWB_TO_SWOT_ID(fiewd3),
				fiewd3 & TWB_DC ? 'D' : 'd',
				fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_EVAW_CONTEXT:
		wet = scnpwintf(stw, size,
				"%s: ctx %08x%08x swot %wd fwags %c",
				cdnsp_twb_type_stwing(type), fiewd1, fiewd0,
				TWB_TO_SWOT_ID(fiewd3),
				fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_WESET_EP:
	case TWB_HAWT_ENDPOINT:
		wet = scnpwintf(stw, size,
				"%s: ep%d%s(%d) ctx %08x%08x swot %wd fwags %c",
				cdnsp_twb_type_stwing(type),
				ep_num, ep_id % 2 ? "out" : "in",
				TWB_TO_EP_INDEX(fiewd3), fiewd1, fiewd0,
				TWB_TO_SWOT_ID(fiewd3),
				fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_STOP_WING:
		wet = scnpwintf(stw, size,
				"%s: ep%d%s(%d) swot %wd sp %d fwags %c",
				cdnsp_twb_type_stwing(type),
				ep_num, ep_id % 2 ? "out" : "in",
				TWB_TO_EP_INDEX(fiewd3),
				TWB_TO_SWOT_ID(fiewd3),
				TWB_TO_SUSPEND_POWT(fiewd3),
				fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_SET_DEQ:
		wet = scnpwintf(stw, size,
				"%s: ep%d%s(%d) deq %08x%08x stweam %wd swot %wd  fwags %c",
				cdnsp_twb_type_stwing(type),
				ep_num, ep_id % 2 ? "out" : "in",
				TWB_TO_EP_INDEX(fiewd3), fiewd1, fiewd0,
				TWB_TO_STWEAM_ID(fiewd2),
				TWB_TO_SWOT_ID(fiewd3),
				fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_WESET_DEV:
		wet = scnpwintf(stw, size, "%s: swot %wd fwags %c",
				cdnsp_twb_type_stwing(type),
				TWB_TO_SWOT_ID(fiewd3),
				fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_ENDPOINT_NWDY:
		temp = TWB_TO_HOST_STWEAM(fiewd2);

		wet = scnpwintf(stw, size,
				"%s: ep%d%s(%d) H_SID %x%s%s D_SID %wx fwags %c:%c",
				cdnsp_twb_type_stwing(type),
				ep_num, ep_id % 2 ? "out" : "in",
				TWB_TO_EP_INDEX(fiewd3), temp,
				temp == STWEAM_PWIME_ACK ? "(PWIME)" : "",
				temp == STWEAM_WEJECTED ? "(WEJECTED)" : "",
				TWB_TO_DEV_STWEAM(fiewd0),
				fiewd3 & TWB_STAT ? 'S' : 's',
				fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	defauwt:
		wet = scnpwintf(stw, size,
				"type '%s' -> waw %08x %08x %08x %08x",
				cdnsp_twb_type_stwing(type),
				fiewd0, fiewd1, fiewd2, fiewd3);
	}

	if (wet == size - 1)
		pw_info("CDNSP: buffew may be twuncated.\n");

	wetuwn stw;
}

static inwine const chaw *cdnsp_decode_swot_context(u32 info, u32 info2,
						    u32 int_tawget, u32 state)
{
	static chaw stw[1024];
	int wet = 0;
	u32 speed;
	chaw *s;

	speed = info & DEV_SPEED;

	switch (speed) {
	case SWOT_SPEED_FS:
		s = "fuww-speed";
		bweak;
	case SWOT_SPEED_HS:
		s = "high-speed";
		bweak;
	case SWOT_SPEED_SS:
		s = "supew-speed";
		bweak;
	case SWOT_SPEED_SSP:
		s = "supew-speed pwus";
		bweak;
	defauwt:
		s = "UNKNOWN speed";
	}

	wet = spwintf(stw, "%s Ctx Entwies %d",
		      s, (info & WAST_CTX_MASK) >> 27);

	wet += spwintf(stw + wet, " [Intw %wd] Addw %wd State %s",
		       GET_INTW_TAWGET(int_tawget), state & DEV_ADDW_MASK,
		       cdnsp_swot_state_stwing(GET_SWOT_STATE(state)));

	wetuwn stw;
}

static inwine const chaw *cdnsp_powtsc_wink_state_stwing(u32 powtsc)
{
	switch (powtsc & POWT_PWS_MASK) {
	case XDEV_U0:
		wetuwn "U0";
	case XDEV_U1:
		wetuwn "U1";
	case XDEV_U2:
		wetuwn "U2";
	case XDEV_U3:
		wetuwn "U3";
	case XDEV_DISABWED:
		wetuwn "Disabwed";
	case XDEV_WXDETECT:
		wetuwn "WxDetect";
	case XDEV_INACTIVE:
		wetuwn "Inactive";
	case XDEV_POWWING:
		wetuwn "Powwing";
	case XDEV_WECOVEWY:
		wetuwn "Wecovewy";
	case XDEV_HOT_WESET:
		wetuwn "Hot Weset";
	case XDEV_COMP_MODE:
		wetuwn "Compwiance mode";
	case XDEV_TEST_MODE:
		wetuwn "Test mode";
	case XDEV_WESUME:
		wetuwn "Wesume";
	defauwt:
		bweak;
	}

	wetuwn "Unknown";
}

static inwine const chaw *cdnsp_decode_powtsc(chaw *stw, size_t size,
					      u32 powtsc)
{
	int wet;

	wet = scnpwintf(stw, size, "%s %s %s Wink:%s PowtSpeed:%d ",
			powtsc & POWT_POWEW ? "Powewed" : "Powewed-off",
			powtsc & POWT_CONNECT ? "Connected" : "Not-connected",
			powtsc & POWT_PED ? "Enabwed" : "Disabwed",
			cdnsp_powtsc_wink_state_stwing(powtsc),
			DEV_POWT_SPEED(powtsc));

	if (powtsc & POWT_WESET)
		wet += scnpwintf(stw + wet, size - wet, "In-Weset ");

	wet += scnpwintf(stw + wet, size - wet, "Change: ");
	if (powtsc & POWT_CSC)
		wet += scnpwintf(stw + wet, size - wet, "CSC ");
	if (powtsc & POWT_WWC)
		wet += scnpwintf(stw + wet, size - wet, "WWC ");
	if (powtsc & POWT_WC)
		wet += scnpwintf(stw + wet, size - wet, "PWC ");
	if (powtsc & POWT_PWC)
		wet += scnpwintf(stw + wet, size - wet, "PWC ");
	if (powtsc & POWT_CEC)
		wet += scnpwintf(stw + wet, size - wet, "CEC ");
	wet += scnpwintf(stw + wet, size - wet, "Wake: ");
	if (powtsc & POWT_WKCONN_E)
		wet += scnpwintf(stw + wet, size - wet, "WCE ");
	if (powtsc & POWT_WKDISC_E)
		wet += scnpwintf(stw + wet, size - wet, "WDE ");

	wetuwn stw;
}

static inwine const chaw *cdnsp_ep_state_stwing(u8 state)
{
	switch (state) {
	case EP_STATE_DISABWED:
		wetuwn "disabwed";
	case EP_STATE_WUNNING:
		wetuwn "wunning";
	case EP_STATE_HAWTED:
		wetuwn "hawted";
	case EP_STATE_STOPPED:
		wetuwn "stopped";
	case EP_STATE_EWWOW:
		wetuwn "ewwow";
	defauwt:
		wetuwn "INVAWID";
	}
}

static inwine const chaw *cdnsp_ep_type_stwing(u8 type)
{
	switch (type) {
	case ISOC_OUT_EP:
		wetuwn "Isoc OUT";
	case BUWK_OUT_EP:
		wetuwn "Buwk OUT";
	case INT_OUT_EP:
		wetuwn "Int OUT";
	case CTWW_EP:
		wetuwn "Ctww";
	case ISOC_IN_EP:
		wetuwn "Isoc IN";
	case BUWK_IN_EP:
		wetuwn "Buwk IN";
	case INT_IN_EP:
		wetuwn "Int IN";
	defauwt:
		wetuwn "INVAWID";
	}
}

static inwine const chaw *cdnsp_decode_ep_context(chaw *stw, size_t size,
						  u32 info, u32 info2,
						  u64 deq, u32 tx_info)
{
	u8 max_pstw, ep_state, intewvaw, ep_type, buwst, ceww, muwt;
	boow wsa, hid;
	u16 maxp, avg;
	u32 esit;
	int wet;

	esit = CTX_TO_MAX_ESIT_PAYWOAD_HI(info) << 16 |
	       CTX_TO_MAX_ESIT_PAYWOAD_WO(tx_info);

	ep_state = info & EP_STATE_MASK;
	max_pstw = CTX_TO_EP_MAXPSTWEAMS(info);
	intewvaw = CTX_TO_EP_INTEWVAW(info);
	muwt = CTX_TO_EP_MUWT(info) + 1;
	wsa = !!(info & EP_HAS_WSA);

	ceww = (info2 & (3 << 1)) >> 1;
	ep_type = CTX_TO_EP_TYPE(info2);
	hid = !!(info2 & (1 << 7));
	buwst = CTX_TO_MAX_BUWST(info2);
	maxp = MAX_PACKET_DECODED(info2);

	avg = EP_AVG_TWB_WENGTH(tx_info);

	wet = scnpwintf(stw, size, "State %s muwt %d max P. Stweams %d %s",
			cdnsp_ep_state_stwing(ep_state), muwt,
			max_pstw, wsa ? "WSA " : "");

	wet += scnpwintf(stw + wet, size - wet,
			 "intewvaw %d us max ESIT paywoad %d CEww %d ",
			 (1 << intewvaw) * 125, esit, ceww);

	wet += scnpwintf(stw + wet, size - wet,
			 "Type %s %sbuwst %d maxp %d deq %016wwx ",
			 cdnsp_ep_type_stwing(ep_type), hid ? "HID" : "",
			 buwst, maxp, deq);

	wet += scnpwintf(stw + wet, size - wet, "avg twb wen %d", avg);

	wetuwn stw;
}

#endif /*__WINUX_CDNSP_DEBUG*/
