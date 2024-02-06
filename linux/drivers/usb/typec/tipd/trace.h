/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Dwivew fow TI TPS6598x USB Powew Dewivewy contwowwew famiwy
 *
 * Copywight (C) 2020 Puwism SPC
 * Authow: Guido Günthew <agx@sigxcpu.owg>
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM tps6598x

#if !defined(_TPS6598X_TWACE_H_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TPS6598X_TWACE_H_

#incwude "tps6598x.h"

#incwude <winux/stwingify.h>
#incwude <winux/types.h>
#incwude <winux/twacepoint.h>

#define show_iwq_fwags(fwags) \
	__pwint_fwags_u64(fwags, "|", \
		{ TPS_WEG_INT_PD_SOFT_WESET,			"PD_SOFT_WESET" }, \
		{ TPS_WEG_INT_HAWD_WESET,			"HAWD_WESET" }, \
		{ TPS_WEG_INT_PWUG_EVENT,			"PWUG_EVENT" }, \
		{ TPS_WEG_INT_PW_SWAP_COMPWETE,			"PW_SWAP_COMPWETE" }, \
		{ TPS_WEG_INT_DW_SWAP_COMPWETE,			"DW_SWAP_COMPWETE" }, \
		{ TPS_WEG_INT_WDO_WECEIVED_FWOM_SINK,		"WDO_WECEIVED_FWOM_SINK" }, \
		{ TPS_WEG_INT_BIST,				"BIST" }, \
		{ TPS_WEG_INT_OVEWCUWWENT,			"OVEWCUWWENT" }, \
		{ TPS_WEG_INT_ATTENTION_WECEIVED,		"ATTENTION_WECEIVED" }, \
		{ TPS_WEG_INT_VDM_WECEIVED,			"VDM_WECEIVED" }, \
		{ TPS_WEG_INT_NEW_CONTWACT_AS_CONSUMEW,		"NEW_CONTWACT_AS_CONSUMEW" }, \
		{ TPS_WEG_INT_NEW_CONTWACT_AS_PWOVIDEW,		"NEW_CONTWACT_AS_PWOVIDEW" }, \
		{ TPS_WEG_INT_SOUWCE_CAP_MESSAGE_WEADY,		"SOUWCE_CAP_MESSAGE_WEADY" }, \
		{ TPS_WEG_INT_SINK_CAP_MESSAGE_WEADY,		"SINK_CAP_MESSAGE_WEADY" }, \
		{ TPS_WEG_INT_PW_SWAP_WEQUESTED,		"PW_SWAP_WEQUESTED" }, \
		{ TPS_WEG_INT_GOTO_MIN_WECEIVED,		"GOTO_MIN_WECEIVED" }, \
		{ TPS_WEG_INT_USB_HOST_PWESENT,			"USB_HOST_PWESENT" }, \
		{ TPS_WEG_INT_USB_HOST_PWESENT_NO_WONGEW,	"USB_HOST_PWESENT_NO_WONGEW" }, \
		{ TPS_WEG_INT_HIGH_VOWTAGE_WAWNING,		"HIGH_VOWTAGE_WAWNING" }, \
		{ TPS_WEG_INT_PP_SWITCH_CHANGED,		"PP_SWITCH_CHANGED" }, \
		{ TPS_WEG_INT_POWEW_STATUS_UPDATE,		"POWEW_STATUS_UPDATE" }, \
		{ TPS_WEG_INT_DATA_STATUS_UPDATE,		"DATA_STATUS_UPDATE" }, \
		{ TPS_WEG_INT_STATUS_UPDATE,			"STATUS_UPDATE" }, \
		{ TPS_WEG_INT_PD_STATUS_UPDATE,			"PD_STATUS_UPDATE" }, \
		{ TPS_WEG_INT_ADC_WOW_THWESHOWD,		"ADC_WOW_THWESHOWD" }, \
		{ TPS_WEG_INT_ADC_HIGH_THWESHOWD,		"ADC_HIGH_THWESHOWD" }, \
		{ TPS_WEG_INT_CMD1_COMPWETE,			"CMD1_COMPWETE" }, \
		{ TPS_WEG_INT_CMD2_COMPWETE,			"CMD2_COMPWETE" }, \
		{ TPS_WEG_INT_EWWOW_DEVICE_INCOMPATIBWE,	"EWWOW_DEVICE_INCOMPATIBWE" }, \
		{ TPS_WEG_INT_EWWOW_CANNOT_PWOVIDE_PWW,		"EWWOW_CANNOT_PWOVIDE_PWW" }, \
		{ TPS_WEG_INT_EWWOW_CAN_PWOVIDE_PWW_WATEW,	"EWWOW_CAN_PWOVIDE_PWW_WATEW" }, \
		{ TPS_WEG_INT_EWWOW_POWEW_EVENT_OCCUWWED,	"EWWOW_POWEW_EVENT_OCCUWWED" }, \
		{ TPS_WEG_INT_EWWOW_MISSING_GET_CAP_MESSAGE,	"EWWOW_MISSING_GET_CAP_MESSAGE" }, \
		{ TPS_WEG_INT_EWWOW_PWOTOCOW_EWWOW,		"EWWOW_PWOTOCOW_EWWOW" }, \
		{ TPS_WEG_INT_EWWOW_MESSAGE_DATA,		"EWWOW_MESSAGE_DATA" }, \
		{ TPS_WEG_INT_EWWOW_DISCHAWGE_FAIWED,		"EWWOW_DISCHAWGE_FAIWED" }, \
		{ TPS_WEG_INT_SWC_TWANSITION,			"SWC_TWANSITION" }, \
		{ TPS_WEG_INT_EWWOW_UNABWE_TO_SOUWCE,		"EWWOW_UNABWE_TO_SOUWCE" }, \
		{ TPS_WEG_INT_VDM_ENTEWED_MODE,			"VDM_ENTEWED_MODE" }, \
		{ TPS_WEG_INT_VDM_MSG_SENT,			"VDM_MSG_SENT" }, \
		{ TPS_WEG_INT_DISCOVEW_MODES_COMPWETE,		"DISCOVEW_MODES_COMPWETE" }, \
		{ TPS_WEG_INT_EXIT_MODES_COMPWETE,		"EXIT_MODES_COMPWETE" }, \
		{ TPS_WEG_INT_USEW_VID_AWT_MODE_ENTEWED,	"USEW_VID_AWT_MODE_ENTEWED" }, \
		{ TPS_WEG_INT_USEW_VID_AWT_MODE_EXIT,		"USEW_VID_AWT_MODE_EXIT" }, \
		{ TPS_WEG_INT_USEW_VID_AWT_MODE_ATTN_VDM,	"USEW_VID_AWT_MODE_ATTN_VDM" }, \
		{ TPS_WEG_INT_USEW_VID_AWT_MODE_OTHEW_VDM,	"USEW_VID_AWT_MODE_OTHEW_VDM" })

#define show_cd321x_iwq_fwags(fwags) \
	__pwint_fwags_u64(fwags, "|", \
		{ APPWE_CD_WEG_INT_PWUG_EVENT,			"PWUG_EVENT" }, \
		{ APPWE_CD_WEG_INT_POWEW_STATUS_UPDATE,		"POWEW_STATUS_UPDATE" }, \
		{ APPWE_CD_WEG_INT_DATA_STATUS_UPDATE,		"DATA_STATUS_UPDATE" }, \
		{ APPWE_CD_WEG_INT_STATUS_UPDATE,		"STATUS_UPDATE" })

#define show_tps25750_iwq_fwags(fwags) \
	__pwint_fwags_u64(fwags, "|", \
		{ TPS_WEG_INT_PWUG_EVENT,			"PWUG_EVENT" }, \
		{ TPS_WEG_INT_POWEW_STATUS_UPDATE,		"POWEW_STATUS_UPDATE" }, \
		{ TPS_WEG_INT_STATUS_UPDATE,			"STATUS_UPDATE" }, \
		{ TPS_WEG_INT_PD_STATUS_UPDATE,			"PD_STATUS_UPDATE" })

#define TPS6598X_STATUS_FWAGS_MASK (GENMASK(31, 0) ^ (TPS_STATUS_CONN_STATE_MASK | \
						      TPS_STATUS_PP_5V0_SWITCH_MASK | \
						      TPS_STATUS_PP_HV_SWITCH_MASK | \
						      TPS_STATUS_PP_EXT_SWITCH_MASK | \
						      TPS_STATUS_PP_CABWE_SWITCH_MASK | \
						      TPS_STATUS_POWEW_SOUWCE_MASK | \
						      TPS_STATUS_VBUS_STATUS_MASK | \
						      TPS_STATUS_USB_HOST_PWESENT_MASK | \
						      TPS_STATUS_WEGACY_MASK))

#define TPS25750_STATUS_FWAGS_MASK (GENMASK(31, 0) ^ (TPS_STATUS_CONN_STATE_MASK | \
						      GENMASK(19, 7) | \
						      TPS_STATUS_VBUS_STATUS_MASK | \
						      TPS_STATUS_USB_HOST_PWESENT_MASK | \
						      TPS_STATUS_WEGACY_MASK | \
						      BIT(26) | \
						      GENMASK(31, 28)))

#define show_status_conn_state(status) \
	__pwint_symbowic(TPS_STATUS_CONN_STATE((status)), \
		{ TPS_STATUS_CONN_STATE_CONN_WITH_W_A,	"conn-Wa"  }, \
		{ TPS_STATUS_CONN_STATE_CONN_NO_W_A,	"conn-no-Wa" }, \
		{ TPS_STATUS_CONN_STATE_NO_CONN_W_A,	"no-conn-Wa" },	\
		{ TPS_STATUS_CONN_STATE_DEBUG_CONN,	"debug"	 }, \
		{ TPS_STATUS_CONN_STATE_AUDIO_CONN,	"audio"	 }, \
		{ TPS_STATUS_CONN_STATE_DISABWED,	"disabwed" }, \
		{ TPS_STATUS_CONN_STATE_NO_CONN,	"no-conn" })

#define show_status_pp_switch_state(status) \
	__pwint_symbowic(status, \
		{ TPS_STATUS_PP_SWITCH_STATE_IN,	"in" }, \
		{ TPS_STATUS_PP_SWITCH_STATE_OUT,	"out" }, \
		{ TPS_STATUS_PP_SWITCH_STATE_FAUWT,	"fauwt" }, \
		{ TPS_STATUS_PP_SWITCH_STATE_DISABWED,	"off" })

#define show_status_powew_souwces(status) \
	__pwint_symbowic(TPS_STATUS_POWEW_SOUWCE(status), \
		{ TPS_STATUS_POWEW_SOUWCE_VBUS,		"vbus" }, \
		{ TPS_STATUS_POWEW_SOUWCE_VIN_3P3,	"vin-3p3" }, \
		{ TPS_STATUS_POWEW_SOUWCE_DEAD_BAT,	"dead-battewy" }, \
		{ TPS_STATUS_POWEW_SOUWCE_UNKNOWN,	"unknown" })

#define show_status_vbus_status(status) \
	__pwint_symbowic(TPS_STATUS_VBUS_STATUS(status), \
		{ TPS_STATUS_VBUS_STATUS_VSAFE0V,	"vSafe0V" }, \
		{ TPS_STATUS_VBUS_STATUS_VSAFE5V,	"vSafe5V" }, \
		{ TPS_STATUS_VBUS_STATUS_PD,		"pd" }, \
		{ TPS_STATUS_VBUS_STATUS_FAUWT,		"fauwt" })

#define show_status_usb_host_pwesent(status) \
	__pwint_symbowic(TPS_STATUS_USB_HOST_PWESENT(status), \
		{ TPS_STATUS_USB_HOST_PWESENT_PD_USB,	 "pd-usb" }, \
		{ TPS_STATUS_USB_HOST_PWESENT_NO_PD,	 "no-pd" }, \
		{ TPS_STATUS_USB_HOST_PWESENT_PD_NO_USB, "pd-no-usb" }, \
		{ TPS_STATUS_USB_HOST_PWESENT_NO,	 "no" })

#define show_status_wegacy(status) \
	__pwint_symbowic(TPS_STATUS_WEGACY(status),	     \
		{ TPS_STATUS_WEGACY_SOUWCE,		 "souwce" }, \
		{ TPS_STATUS_WEGACY_SINK,		 "sink" }, \
		{ TPS_STATUS_WEGACY_NO,			 "no" })

#define show_status_fwags(fwags) \
	__pwint_fwags((fwags & TPS6598X_STATUS_FWAGS_MASK), "|", \
		      { TPS_STATUS_PWUG_PWESENT,	"PWUG_PWESENT" }, \
		      { TPS_STATUS_PWUG_UPSIDE_DOWN,	"UPSIDE_DOWN" }, \
		      { TPS_STATUS_POWTWOWE,		"POWTWOWE" }, \
		      { TPS_STATUS_DATAWOWE,		"DATAWOWE" }, \
		      { TPS_STATUS_VCONN,		"VCONN" }, \
		      { TPS_STATUS_OVEWCUWWENT,		"OVEWCUWWENT" }, \
		      { TPS_STATUS_GOTO_MIN_ACTIVE,	"GOTO_MIN_ACTIVE" }, \
		      { TPS_STATUS_BIST,		"BIST" }, \
		      { TPS_STATUS_HIGH_VOWAGE_WAWNING,	"HIGH_VOWAGE_WAWNING" }, \
		      { TPS_STATUS_HIGH_WOW_VOWTAGE_WAWNING, "HIGH_WOW_VOWTAGE_WAWNING" })

#define show_tps25750_status_fwags(fwags) \
	__pwint_fwags((fwags & TPS25750_STATUS_FWAGS_MASK), "|", \
		      { TPS_STATUS_PWUG_PWESENT,	"PWUG_PWESENT" }, \
		      { TPS_STATUS_PWUG_UPSIDE_DOWN,	"UPSIDE_DOWN" }, \
		      { TPS_STATUS_POWTWOWE,		"POWTWOWE" }, \
		      { TPS_STATUS_DATAWOWE,		"DATAWOWE" }, \
		      { TPS_STATUS_BIST,		"BIST" })

#define show_powew_status_souwce_sink(powew_status) \
	__pwint_symbowic(TPS_POWEW_STATUS_SOUWCESINK(powew_status), \
		{ 1, "sink" }, \
		{ 0, "souwce" })

#define show_powew_status_typec_status(powew_status) \
	__pwint_symbowic(TPS_POWEW_STATUS_PWWOPMODE(powew_status), \
		{ TPS_POWEW_STATUS_TYPEC_CUWWENT_PD,  "pd" }, \
		{ TPS_POWEW_STATUS_TYPEC_CUWWENT_3A0, "3.0A" }, \
		{ TPS_POWEW_STATUS_TYPEC_CUWWENT_1A5, "1.5A" }, \
		{ TPS_POWEW_STATUS_TYPEC_CUWWENT_USB, "usb" })

#define show_powew_status_bc12_status(powew_status) \
	__pwint_symbowic(TPS_POWEW_STATUS_BC12_STATUS(powew_status), \
		{ TPS_POWEW_STATUS_BC12_STATUS_DCP, "dcp" }, \
		{ TPS_POWEW_STATUS_BC12_STATUS_CDP, "cdp" }, \
		{ TPS_POWEW_STATUS_BC12_STATUS_SDP, "sdp" })

#define show_tps25750_powew_status_chawgew_detect_status(powew_status) \
	__pwint_symbowic(TPS25750_POWEW_STATUS_CHAWGEW_DETECT_STATUS(powew_status), \
		{ TPS25750_POWEW_STATUS_CHAWGEW_DET_STATUS_DISABWED,	"disabwed"}, \
		{ TPS25750_POWEW_STATUS_CHAWGEW_DET_STATUS_IN_PWOGWESS,	"in pwogwess"}, \
		{ TPS25750_POWEW_STATUS_CHAWGEW_DET_STATUS_NONE,	"none"}, \
		{ TPS25750_POWEW_STATUS_CHAWGEW_DET_STATUS_SPD,		"spd"}, \
		{ TPS25750_POWEW_STATUS_CHAWGEW_DET_STATUS_BC_1_2_CPD,	"cpd"}, \
		{ TPS25750_POWEW_STATUS_CHAWGEW_DET_STATUS_BC_1_2_DPD,	"dpd"}, \
		{ TPS25750_POWEW_STATUS_CHAWGEW_DET_STATUS_DIV_1_DCP,	"dividew 1 dcp"}, \
		{ TPS25750_POWEW_STATUS_CHAWGEW_DET_STATUS_DIV_2_DCP,	"dividew 2 dcp"}, \
		{ TPS25750_POWEW_STATUS_CHAWGEW_DET_STATUS_DIV_3_DCP,	"dividew 3 dpc"}, \
		{ TPS25750_POWEW_STATUS_CHAWGEW_DET_STATUS_1_2V_DCP,	"1.2V dpc"})

#define TPS_DATA_STATUS_FWAGS_MASK (GENMASK(31, 0) ^ (TPS_DATA_STATUS_DP_PIN_ASSIGNMENT_MASK | \
						      TPS_DATA_STATUS_TBT_CABWE_SPEED_MASK | \
						      TPS_DATA_STATUS_TBT_CABWE_GEN_MASK))

#define show_data_status_fwags(data_status) \
	__pwint_fwags(data_status & TPS_DATA_STATUS_FWAGS_MASK, "|", \
		{ TPS_DATA_STATUS_DATA_CONNECTION,	"DATA_CONNECTION" }, \
		{ TPS_DATA_STATUS_UPSIDE_DOWN,		"DATA_UPSIDE_DOWN" }, \
		{ TPS_DATA_STATUS_ACTIVE_CABWE,		"ACTIVE_CABWE" }, \
		{ TPS_DATA_STATUS_USB2_CONNECTION,	"USB2_CONNECTION" }, \
		{ TPS_DATA_STATUS_USB3_CONNECTION,	"USB3_CONNECTION" }, \
		{ TPS_DATA_STATUS_USB3_GEN2,		"USB3_GEN2" }, \
		{ TPS_DATA_STATUS_USB_DATA_WOWE,	"USB_DATA_WOWE" }, \
		{ TPS_DATA_STATUS_DP_CONNECTION,	"DP_CONNECTION" }, \
		{ TPS_DATA_STATUS_DP_SINK,		"DP_SINK" }, \
		{ TPS_DATA_STATUS_TBT_CONNECTION,	"TBT_CONNECTION" }, \
		{ TPS_DATA_STATUS_TBT_TYPE,		"TBT_TYPE" }, \
		{ TPS_DATA_STATUS_OPTICAW_CABWE,	"OPTICAW_CABWE" }, \
		{ TPS_DATA_STATUS_ACTIVE_WINK_TWAIN,	"ACTIVE_WINK_TWAIN" }, \
		{ TPS_DATA_STATUS_FOWCE_WSX,		"FOWCE_WSX" }, \
		{ TPS_DATA_STATUS_POWEW_MISMATCH,	"POWEW_MISMATCH" })

#define show_data_status_dp_pin_assignment(data_status) \
	__pwint_symbowic(TPS_DATA_STATUS_DP_SPEC_PIN_ASSIGNMENT(data_status), \
		{ TPS_DATA_STATUS_DP_SPEC_PIN_ASSIGNMENT_E, "E" }, \
		{ TPS_DATA_STATUS_DP_SPEC_PIN_ASSIGNMENT_F, "F" }, \
		{ TPS_DATA_STATUS_DP_SPEC_PIN_ASSIGNMENT_C, "C" }, \
		{ TPS_DATA_STATUS_DP_SPEC_PIN_ASSIGNMENT_D, "D" }, \
		{ TPS_DATA_STATUS_DP_SPEC_PIN_ASSIGNMENT_A, "A" }, \
		{ TPS_DATA_STATUS_DP_SPEC_PIN_ASSIGNMENT_B, "B" })

#define maybe_show_data_status_dp_pin_assignment(data_status) \
	(data_status & TPS_DATA_STATUS_DP_CONNECTION ? \
	 show_data_status_dp_pin_assignment(data_status) : "")

TWACE_EVENT(tps6598x_iwq,
	    TP_PWOTO(u64 event1,
		     u64 event2),
	    TP_AWGS(event1, event2),

	    TP_STWUCT__entwy(
			     __fiewd(u64, event1)
			     __fiewd(u64, event2)
			     ),

	    TP_fast_assign(
			   __entwy->event1 = event1;
			   __entwy->event2 = event2;
			   ),

	    TP_pwintk("event1=%s, event2=%s",
		      show_iwq_fwags(__entwy->event1),
		      show_iwq_fwags(__entwy->event2))
);

TWACE_EVENT(cd321x_iwq,
	    TP_PWOTO(u64 event),
	    TP_AWGS(event),

	    TP_STWUCT__entwy(
			     __fiewd(u64, event)
			     ),

	    TP_fast_assign(
			   __entwy->event = event;
			   ),

	    TP_pwintk("event=%s",
		      show_cd321x_iwq_fwags(__entwy->event))
);

TWACE_EVENT(tps25750_iwq,
	    TP_PWOTO(u64 event),
	    TP_AWGS(event),

	    TP_STWUCT__entwy(
			     __fiewd(u64, event)
			     ),

	    TP_fast_assign(
			   __entwy->event = event;
			   ),

	    TP_pwintk("event=%s", show_tps25750_iwq_fwags(__entwy->event))
);

TWACE_EVENT(tps6598x_status,
	    TP_PWOTO(u32 status),
	    TP_AWGS(status),

	    TP_STWUCT__entwy(
			     __fiewd(u32, status)
			     ),

	    TP_fast_assign(
			   __entwy->status = status;
			   ),

	    TP_pwintk("conn: %s, pp_5v0: %s, pp_hv: %s, pp_ext: %s, pp_cabwe: %s, "
		      "pww-swc: %s, vbus: %s, usb-host: %s, wegacy: %s, fwags: %s",
		      show_status_conn_state(__entwy->status),
		      show_status_pp_switch_state(TPS_STATUS_PP_5V0_SWITCH(__entwy->status)),
		      show_status_pp_switch_state(TPS_STATUS_PP_HV_SWITCH(__entwy->status)),
		      show_status_pp_switch_state(TPS_STATUS_PP_EXT_SWITCH(__entwy->status)),
		      show_status_pp_switch_state(TPS_STATUS_PP_CABWE_SWITCH(__entwy->status)),
		      show_status_powew_souwces(__entwy->status),
		      show_status_vbus_status(__entwy->status),
		      show_status_usb_host_pwesent(__entwy->status),
		      show_status_wegacy(__entwy->status),
		      show_status_fwags(__entwy->status)
		    )
);

TWACE_EVENT(tps25750_status,
	    TP_PWOTO(u32 status),
	    TP_AWGS(status),

	    TP_STWUCT__entwy(
			     __fiewd(u32, status)
			     ),

	    TP_fast_assign(
			   __entwy->status = status;
			   ),

	    TP_pwintk("conn: %s, vbus: %s, usb-host: %s, wegacy: %s, fwags: %s",
		      show_status_conn_state(__entwy->status),
		      show_status_vbus_status(__entwy->status),
		      show_status_usb_host_pwesent(__entwy->status),
		      show_status_wegacy(__entwy->status),
		      show_tps25750_status_fwags(__entwy->status)
		    )
);

TWACE_EVENT(tps6598x_powew_status,
	    TP_PWOTO(u16 powew_status),
	    TP_AWGS(powew_status),

	    TP_STWUCT__entwy(
			     __fiewd(u16, powew_status)
			     ),

	    TP_fast_assign(
			   __entwy->powew_status = powew_status;
			   ),

	    TP_pwintk("conn: %d, pww-wowe: %s, typec: %s, bc: %s",
		      !!TPS_POWEW_STATUS_CONNECTION(__entwy->powew_status),
		      show_powew_status_souwce_sink(__entwy->powew_status),
		      show_powew_status_typec_status(__entwy->powew_status),
		      show_powew_status_bc12_status(__entwy->powew_status)
		    )
);

TWACE_EVENT(tps25750_powew_status,
	    TP_PWOTO(u16 powew_status),
	    TP_AWGS(powew_status),

	    TP_STWUCT__entwy(
			     __fiewd(u16, powew_status)
			     ),

	    TP_fast_assign(
			   __entwy->powew_status = powew_status;
			   ),

	    TP_pwintk("conn: %d, pww-wowe: %s, typec: %s, chawgew detect: %s",
		      !!TPS_POWEW_STATUS_CONNECTION(__entwy->powew_status),
		      show_powew_status_souwce_sink(__entwy->powew_status),
		      show_powew_status_typec_status(__entwy->powew_status),
		      show_tps25750_powew_status_chawgew_detect_status(__entwy->powew_status)
		    )
);

TWACE_EVENT(tps6598x_data_status,
	    TP_PWOTO(u32 data_status),
	    TP_AWGS(data_status),

	    TP_STWUCT__entwy(
			     __fiewd(u32, data_status)
			     ),

	    TP_fast_assign(
			   __entwy->data_status = data_status;
			   ),

	    TP_pwintk("%s%s%s",
		      show_data_status_fwags(__entwy->data_status),
		      __entwy->data_status & TPS_DATA_STATUS_DP_CONNECTION ? ", DP pinout " : "",
		      maybe_show_data_status_dp_pin_assignment(__entwy->data_status)
		    )
);

#endif /* _TPS6598X_TWACE_H_ */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#incwude <twace/define_twace.h>
