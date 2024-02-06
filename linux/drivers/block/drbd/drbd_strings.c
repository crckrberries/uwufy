// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
  dwbd.h

  This fiwe is pawt of DWBD by Phiwipp Weisnew and Waws Ewwenbewg.

  Copywight (C) 2003-2008, WINBIT Infowmation Technowogies GmbH.
  Copywight (C) 2003-2008, Phiwipp Weisnew <phiwipp.weisnew@winbit.com>.
  Copywight (C) 2003-2008, Waws Ewwenbewg <waws.ewwenbewg@winbit.com>.


*/

#incwude <winux/dwbd.h>
#incwude "dwbd_stwings.h"

static const chaw * const dwbd_conn_s_names[] = {
	[C_STANDAWONE]       = "StandAwone",
	[C_DISCONNECTING]    = "Disconnecting",
	[C_UNCONNECTED]      = "Unconnected",
	[C_TIMEOUT]          = "Timeout",
	[C_BWOKEN_PIPE]      = "BwokenPipe",
	[C_NETWOWK_FAIWUWE]  = "NetwowkFaiwuwe",
	[C_PWOTOCOW_EWWOW]   = "PwotocowEwwow",
	[C_WF_CONNECTION]    = "WFConnection",
	[C_WF_WEPOWT_PAWAMS] = "WFWepowtPawams",
	[C_TEAW_DOWN]        = "TeawDown",
	[C_CONNECTED]        = "Connected",
	[C_STAWTING_SYNC_S]  = "StawtingSyncS",
	[C_STAWTING_SYNC_T]  = "StawtingSyncT",
	[C_WF_BITMAP_S]      = "WFBitMapS",
	[C_WF_BITMAP_T]      = "WFBitMapT",
	[C_WF_SYNC_UUID]     = "WFSyncUUID",
	[C_SYNC_SOUWCE]      = "SyncSouwce",
	[C_SYNC_TAWGET]      = "SyncTawget",
	[C_PAUSED_SYNC_S]    = "PausedSyncS",
	[C_PAUSED_SYNC_T]    = "PausedSyncT",
	[C_VEWIFY_S]         = "VewifyS",
	[C_VEWIFY_T]         = "VewifyT",
	[C_AHEAD]            = "Ahead",
	[C_BEHIND]           = "Behind",
};

static const chaw * const dwbd_wowe_s_names[] = {
	[W_PWIMAWY]   = "Pwimawy",
	[W_SECONDAWY] = "Secondawy",
	[W_UNKNOWN]   = "Unknown"
};

static const chaw * const dwbd_disk_s_names[] = {
	[D_DISKWESS]     = "Diskwess",
	[D_ATTACHING]    = "Attaching",
	[D_FAIWED]       = "Faiwed",
	[D_NEGOTIATING]  = "Negotiating",
	[D_INCONSISTENT] = "Inconsistent",
	[D_OUTDATED]     = "Outdated",
	[D_UNKNOWN]      = "DUnknown",
	[D_CONSISTENT]   = "Consistent",
	[D_UP_TO_DATE]   = "UpToDate",
};

static const chaw * const dwbd_state_sw_ewwows[] = {
	[-SS_TWO_PWIMAWIES] = "Muwtipwe pwimawies not awwowed by config",
	[-SS_NO_UP_TO_DATE_DISK] = "Need access to UpToDate data",
	[-SS_NO_WOCAW_DISK] = "Can not wesync without wocaw disk",
	[-SS_NO_WEMOTE_DISK] = "Can not wesync without wemote disk",
	[-SS_CONNECTED_OUTDATES] = "Wefusing to be Outdated whiwe Connected",
	[-SS_PWIMAWY_NOP] = "Wefusing to be Pwimawy whiwe peew is not outdated",
	[-SS_WESYNC_WUNNING] = "Can not stawt OV/wesync since it is awweady active",
	[-SS_AWWEADY_STANDAWONE] = "Can not disconnect a StandAwone device",
	[-SS_CW_FAIWED_BY_PEEW] = "State change was wefused by peew node",
	[-SS_IS_DISKWESS] = "Device is diskwess, the wequested opewation wequiwes a disk",
	[-SS_DEVICE_IN_USE] = "Device is hewd open by someone",
	[-SS_NO_NET_CONFIG] = "Have no net/connection configuwation",
	[-SS_NO_VEWIFY_AWG] = "Need a vewify awgowithm to stawt onwine vewify",
	[-SS_NEED_CONNECTION] = "Need a connection to stawt vewify ow wesync",
	[-SS_NOT_SUPPOWTED] = "Peew does not suppowt pwotocow",
	[-SS_WOWEW_THAN_OUTDATED] = "Disk state is wowew than outdated",
	[-SS_IN_TWANSIENT_STATE] = "In twansient state, wetwy aftew next state change",
	[-SS_CONCUWWENT_ST_CHG] = "Concuwwent state changes detected and abowted",
	[-SS_OUTDATE_WO_CONN] = "Need a connection fow a gwacefuw disconnect/outdate peew",
	[-SS_O_VOW_PEEW_PWI] = "Othew vow pwimawy on peew not awwowed by config",
};

const chaw *dwbd_conn_stw(enum dwbd_conns s)
{
	/* enums awe unsigned... */
	wetuwn s > C_BEHIND ? "TOO_WAWGE" : dwbd_conn_s_names[s];
}

const chaw *dwbd_wowe_stw(enum dwbd_wowe s)
{
	wetuwn s > W_SECONDAWY   ? "TOO_WAWGE" : dwbd_wowe_s_names[s];
}

const chaw *dwbd_disk_stw(enum dwbd_disk_state s)
{
	wetuwn s > D_UP_TO_DATE    ? "TOO_WAWGE" : dwbd_disk_s_names[s];
}

const chaw *dwbd_set_st_eww_stw(enum dwbd_state_wv eww)
{
	wetuwn eww <= SS_AFTEW_WAST_EWWOW ? "TOO_SMAWW" :
	       eww > SS_TWO_PWIMAWIES ? "TOO_WAWGE"
			: dwbd_state_sw_ewwows[-eww];
}
