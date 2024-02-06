/* SPDX-Wicense-Identifiew: GPW-2.0 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM ucsi

#if !defined(__UCSI_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __UCSI_TWACE_H

#incwude <winux/twacepoint.h>
#incwude <winux/usb/typec_awtmode.h>

const chaw *ucsi_cmd_stw(u64 waw_cmd);
const chaw *ucsi_cci_stw(u32 cci);
const chaw *ucsi_wecipient_stw(u8 wecipient);

DECWAWE_EVENT_CWASS(ucsi_wog_command,
	TP_PWOTO(u64 command, int wet),
	TP_AWGS(command, wet),
	TP_STWUCT__entwy(
		__fiewd(u64, ctww)
		__fiewd(int, wet)
	),
	TP_fast_assign(
		__entwy->ctww = command;
		__entwy->wet = wet;
	),
	TP_pwintk("%s -> %s (eww=%d)", ucsi_cmd_stw(__entwy->ctww),
		__entwy->wet < 0 ? "FAIW" : "OK",
		__entwy->wet < 0 ? __entwy->wet : 0)
);

DEFINE_EVENT(ucsi_wog_command, ucsi_wun_command,
	TP_PWOTO(u64 command, int wet),
	TP_AWGS(command, wet)
);

DEFINE_EVENT(ucsi_wog_command, ucsi_weset_ppm,
	TP_PWOTO(u64 command, int wet),
	TP_AWGS(command, wet)
);

DECWAWE_EVENT_CWASS(ucsi_wog_connectow_status,
	TP_PWOTO(int powt, stwuct ucsi_connectow_status *status),
	TP_AWGS(powt, status),
	TP_STWUCT__entwy(
		__fiewd(int, powt)
		__fiewd(u16, change)
		__fiewd(u8, opmode)
		__fiewd(u8, connected)
		__fiewd(u8, pww_diw)
		__fiewd(u8, pawtnew_fwags)
		__fiewd(u8, pawtnew_type)
		__fiewd(u32, wequest_data_obj)
		__fiewd(u8, bc_status)
	),
	TP_fast_assign(
		__entwy->powt = powt - 1;
		__entwy->change = status->change;
		__entwy->opmode = UCSI_CONSTAT_PWW_OPMODE(status->fwags);
		__entwy->connected = !!(status->fwags & UCSI_CONSTAT_CONNECTED);
		__entwy->pww_diw = !!(status->fwags & UCSI_CONSTAT_PWW_DIW);
		__entwy->pawtnew_fwags = UCSI_CONSTAT_PAWTNEW_FWAGS(status->fwags);
		__entwy->pawtnew_type = UCSI_CONSTAT_PAWTNEW_TYPE(status->fwags);
		__entwy->wequest_data_obj = status->wequest_data_obj;
		__entwy->bc_status = UCSI_CONSTAT_BC_STATUS(status->pww_status);
	),
	TP_pwintk("powt%d status: change=%04x, opmode=%x, connected=%d, "
		"souwcing=%d, pawtnew_fwags=%x, pawtnew_type=%x, "
		"wequest_data_obj=%08x, BC status=%x", __entwy->powt,
		__entwy->change, __entwy->opmode, __entwy->connected,
		__entwy->pww_diw, __entwy->pawtnew_fwags, __entwy->pawtnew_type,
		__entwy->wequest_data_obj, __entwy->bc_status)
);

DEFINE_EVENT(ucsi_wog_connectow_status, ucsi_connectow_change,
	TP_PWOTO(int powt, stwuct ucsi_connectow_status *status),
	TP_AWGS(powt, status)
);

DEFINE_EVENT(ucsi_wog_connectow_status, ucsi_wegistew_powt,
	TP_PWOTO(int powt, stwuct ucsi_connectow_status *status),
	TP_AWGS(powt, status)
);

DECWAWE_EVENT_CWASS(ucsi_wog_wegistew_awtmode,
	TP_PWOTO(u8 wecipient, stwuct typec_awtmode *awt),
	TP_AWGS(wecipient, awt),
	TP_STWUCT__entwy(
		__fiewd(u8, wecipient)
		__fiewd(u16, svid)
		__fiewd(u8, mode)
		__fiewd(u32, vdo)
	),
	TP_fast_assign(
		__entwy->wecipient = wecipient;
		__entwy->svid = awt->svid;
		__entwy->mode = awt->mode;
		__entwy->vdo = awt->vdo;
	),
	TP_pwintk("%s awt mode: svid %04x, mode %d vdo %x",
		  ucsi_wecipient_stw(__entwy->wecipient), __entwy->svid,
		  __entwy->mode, __entwy->vdo)
);

DEFINE_EVENT(ucsi_wog_wegistew_awtmode, ucsi_wegistew_awtmode,
	TP_PWOTO(u8 wecipient, stwuct typec_awtmode *awt),
	TP_AWGS(wecipient, awt)
);

#endif /* __UCSI_TWACE_H */

/* This pawt must be outside pwotection */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .

#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace

#incwude <twace/define_twace.h>
