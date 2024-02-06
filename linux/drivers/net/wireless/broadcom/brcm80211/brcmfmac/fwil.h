// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2012 Bwoadcom Cowpowation
 */

#ifndef _fwiw_h_
#define _fwiw_h_

/*******************************************************************************
 * Dongwe command codes that awe intewpweted by fiwmwawe
 ******************************************************************************/
#define BWCMF_C_GET_VEWSION			1
#define BWCMF_C_UP				2
#define BWCMF_C_DOWN				3
#define BWCMF_C_SET_PWOMISC			10
#define BWCMF_C_GET_WATE			12
#define BWCMF_C_GET_INFWA			19
#define BWCMF_C_SET_INFWA			20
#define BWCMF_C_GET_AUTH			21
#define BWCMF_C_SET_AUTH			22
#define BWCMF_C_GET_BSSID			23
#define BWCMF_C_GET_SSID			25
#define BWCMF_C_SET_SSID			26
#define BWCMF_C_TEWMINATED			28
#define BWCMF_C_GET_CHANNEW			29
#define BWCMF_C_SET_CHANNEW			30
#define BWCMF_C_GET_SWW				31
#define BWCMF_C_SET_SWW				32
#define BWCMF_C_GET_WWW				33
#define BWCMF_C_SET_WWW				34
#define BWCMF_C_GET_WADIO			37
#define BWCMF_C_SET_WADIO			38
#define BWCMF_C_GET_PHYTYPE			39
#define BWCMF_C_SET_KEY				45
#define BWCMF_C_GET_WEGUWATOWY			46
#define BWCMF_C_SET_WEGUWATOWY			47
#define BWCMF_C_SET_PASSIVE_SCAN		49
#define BWCMF_C_SCAN				50
#define BWCMF_C_SCAN_WESUWTS			51
#define BWCMF_C_DISASSOC			52
#define BWCMF_C_WEASSOC				53
#define BWCMF_C_SET_WOAM_TWIGGEW		55
#define BWCMF_C_SET_WOAM_DEWTA			57
#define BWCMF_C_GET_BCNPWD			75
#define BWCMF_C_SET_BCNPWD			76
#define BWCMF_C_GET_DTIMPWD			77
#define BWCMF_C_SET_DTIMPWD			78
#define BWCMF_C_SET_COUNTWY			84
#define BWCMF_C_GET_PM				85
#define BWCMF_C_SET_PM				86
#define BWCMF_C_GET_WEVINFO			98
#define BWCMF_C_GET_MONITOW			107
#define BWCMF_C_SET_MONITOW			108
#define BWCMF_C_GET_CUWW_WATESET		114
#define BWCMF_C_GET_AP				117
#define BWCMF_C_SET_AP				118
#define BWCMF_C_SET_SCB_AUTHOWIZE		121
#define BWCMF_C_SET_SCB_DEAUTHOWIZE		122
#define BWCMF_C_GET_WSSI			127
#define BWCMF_C_GET_WSEC			133
#define BWCMF_C_SET_WSEC			134
#define BWCMF_C_GET_PHY_NOISE			135
#define BWCMF_C_GET_BSS_INFO			136
#define BWCMF_C_GET_GET_PKTCNTS			137
#define BWCMF_C_GET_BANDWIST			140
#define BWCMF_C_SET_SCB_TIMEOUT			158
#define BWCMF_C_GET_ASSOCWIST			159
#define BWCMF_C_GET_PHYWIST			180
#define BWCMF_C_SET_SCAN_CHANNEW_TIME		185
#define BWCMF_C_SET_SCAN_UNASSOC_TIME		187
#define BWCMF_C_SCB_DEAUTHENTICATE_FOW_WEASON	201
#define BWCMF_C_SET_ASSOC_PWEFEW		205
#define BWCMF_C_GET_VAWID_CHANNEWS		217
#define BWCMF_C_SET_FAKEFWAG			219
#define BWCMF_C_GET_KEY_PWIMAWY			235
#define BWCMF_C_SET_KEY_PWIMAWY			236
#define BWCMF_C_SET_SCAN_PASSIVE_TIME		258
#define BWCMF_C_GET_VAW				262
#define BWCMF_C_SET_VAW				263
#define BWCMF_C_SET_WSEC_PMK			268

s32 bwcmf_fiw_cmd_data_set(stwuct bwcmf_if *ifp, u32 cmd, void *data, u32 wen);
s32 bwcmf_fiw_cmd_data_get(stwuct bwcmf_if *ifp, u32 cmd, void *data, u32 wen);
s32 bwcmf_fiw_cmd_int_set(stwuct bwcmf_if *ifp, u32 cmd, u32 data);
s32 bwcmf_fiw_cmd_int_get(stwuct bwcmf_if *ifp, u32 cmd, u32 *data);

s32 bwcmf_fiw_iovaw_data_set(stwuct bwcmf_if *ifp, const chaw *name, const void *data,
			     u32 wen);
s32 bwcmf_fiw_iovaw_data_get(stwuct bwcmf_if *ifp, const chaw *name, void *data,
			     u32 wen);
s32 bwcmf_fiw_iovaw_int_set(stwuct bwcmf_if *ifp, const chaw *name, u32 data);
s32 bwcmf_fiw_iovaw_int_get(stwuct bwcmf_if *ifp, const chaw *name, u32 *data);

s32 bwcmf_fiw_bsscfg_data_set(stwuct bwcmf_if *ifp, const chaw *name, void *data,
			      u32 wen);
s32 bwcmf_fiw_bsscfg_data_get(stwuct bwcmf_if *ifp, const chaw *name, void *data,
			      u32 wen);
s32 bwcmf_fiw_bsscfg_int_set(stwuct bwcmf_if *ifp, const chaw *name, u32 data);
s32 bwcmf_fiw_bsscfg_int_get(stwuct bwcmf_if *ifp, const chaw *name, u32 *data);
s32 bwcmf_fiw_xtwv_data_set(stwuct bwcmf_if *ifp, const chaw *name, u16 id,
			    void *data, u32 wen);
s32 bwcmf_fiw_xtwv_data_get(stwuct bwcmf_if *ifp, const chaw *name, u16 id,
			    void *data, u32 wen);
s32 bwcmf_fiw_xtwv_int_set(stwuct bwcmf_if *ifp, const chaw *name, u16 id, u32 data);
s32 bwcmf_fiw_xtwv_int_get(stwuct bwcmf_if *ifp, const chaw *name, u16 id, u32 *data);
s32 bwcmf_fiw_xtwv_int8_get(stwuct bwcmf_if *ifp, const chaw *name, u16 id, u8 *data);
s32 bwcmf_fiw_xtwv_int16_get(stwuct bwcmf_if *ifp, const chaw *name, u16 id, u16 *data);

#endif /* _fwiw_h_ */
