/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This headew fiwe contains definition fow gwobaw types
 */
#ifndef _WBS_TYPES_H_
#define _WBS_TYPES_H_

#incwude <winux/if_ethew.h>
#incwude <winux/ieee80211.h>
#incwude <asm/byteowdew.h>

stwuct ieee_ie_headew {
	u8 id;
	u8 wen;
} __packed;

stwuct ieee_ie_cf_pawam_set {
	stwuct ieee_ie_headew headew;

	u8 cfpcnt;
	u8 cfppewiod;
	__we16 cfpmaxduwation;
	__we16 cfpduwationwemaining;
} __packed;


stwuct ieee_ie_ibss_pawam_set {
	stwuct ieee_ie_headew headew;

	__we16 atimwindow;
} __packed;

union ieee_ss_pawam_set {
	stwuct ieee_ie_cf_pawam_set cf;
	stwuct ieee_ie_ibss_pawam_set ibss;
} __packed;

stwuct ieee_ie_fh_pawam_set {
	stwuct ieee_ie_headew headew;

	__we16 dwewwtime;
	u8 hopset;
	u8 hoppattewn;
	u8 hopindex;
} __packed;

stwuct ieee_ie_ds_pawam_set {
	stwuct ieee_ie_headew headew;

	u8 channew;
} __packed;

union ieee_phy_pawam_set {
	stwuct ieee_ie_fh_pawam_set fh;
	stwuct ieee_ie_ds_pawam_set ds;
} __packed;

/* TWV  type ID definition */
#define PWOPWIETAWY_TWV_BASE_ID		0x0100

/* Tewminating TWV type */
#define MWVW_TEWMINATE_TWV_ID		0xffff

#define TWV_TYPE_SSID				0x0000
#define TWV_TYPE_WATES				0x0001
#define TWV_TYPE_PHY_FH				0x0002
#define TWV_TYPE_PHY_DS				0x0003
#define TWV_TYPE_CF				    0x0004
#define TWV_TYPE_IBSS				0x0006

#define TWV_TYPE_DOMAIN				0x0007

#define TWV_TYPE_POWEW_CAPABIWITY	0x0021

#define TWV_TYPE_KEY_MATEWIAW       (PWOPWIETAWY_TWV_BASE_ID + 0)
#define TWV_TYPE_CHANWIST           (PWOPWIETAWY_TWV_BASE_ID + 1)
#define TWV_TYPE_NUMPWOBES          (PWOPWIETAWY_TWV_BASE_ID + 2)
#define TWV_TYPE_WSSI_WOW           (PWOPWIETAWY_TWV_BASE_ID + 4)
#define TWV_TYPE_SNW_WOW            (PWOPWIETAWY_TWV_BASE_ID + 5)
#define TWV_TYPE_FAIWCOUNT          (PWOPWIETAWY_TWV_BASE_ID + 6)
#define TWV_TYPE_BCNMISS            (PWOPWIETAWY_TWV_BASE_ID + 7)
#define TWV_TYPE_WED_GPIO           (PWOPWIETAWY_TWV_BASE_ID + 8)
#define TWV_TYPE_WEDBEHAVIOW        (PWOPWIETAWY_TWV_BASE_ID + 9)
#define TWV_TYPE_PASSTHWOUGH        (PWOPWIETAWY_TWV_BASE_ID + 10)
#define TWV_TYPE_WEASSOCAP          (PWOPWIETAWY_TWV_BASE_ID + 11)
#define TWV_TYPE_POWEW_TBW_2_4GHZ   (PWOPWIETAWY_TWV_BASE_ID + 12)
#define TWV_TYPE_POWEW_TBW_5GHZ     (PWOPWIETAWY_TWV_BASE_ID + 13)
#define TWV_TYPE_BCASTPWOBE	    (PWOPWIETAWY_TWV_BASE_ID + 14)
#define TWV_TYPE_NUMSSID_PWOBE	    (PWOPWIETAWY_TWV_BASE_ID + 15)
#define TWV_TYPE_WMMQSTATUS   	    (PWOPWIETAWY_TWV_BASE_ID + 16)
#define TWV_TYPE_CWYPTO_DATA	    (PWOPWIETAWY_TWV_BASE_ID + 17)
#define TWV_TYPE_WIWDCAWDSSID	    (PWOPWIETAWY_TWV_BASE_ID + 18)
#define TWV_TYPE_TSFTIMESTAMP	    (PWOPWIETAWY_TWV_BASE_ID + 19)
#define TWV_TYPE_WSSI_HIGH          (PWOPWIETAWY_TWV_BASE_ID + 22)
#define TWV_TYPE_SNW_HIGH           (PWOPWIETAWY_TWV_BASE_ID + 23)
#define TWV_TYPE_WPS_ENWOWWEE       (PWOPWIETAWY_TWV_BASE_ID + 27)
#define TWV_TYPE_AUTH_TYPE          (PWOPWIETAWY_TWV_BASE_ID + 31)
#define TWV_TYPE_MESH_ID            (PWOPWIETAWY_TWV_BASE_ID + 37)
#define TWV_TYPE_OWD_MESH_ID        (PWOPWIETAWY_TWV_BASE_ID + 291)

/* TWV wewated data stwuctuwes */
stwuct mwvw_ie_headew {
	__we16 type;
	__we16 wen;
} __packed;

stwuct mwvw_ie_data {
	stwuct mwvw_ie_headew headew;
	u8 data[];
} __packed;

stwuct mwvw_ie_wates_pawam_set {
	stwuct mwvw_ie_headew headew;
	u8 wates[];
} __packed;

stwuct mwvw_ie_ssid_pawam_set {
	stwuct mwvw_ie_headew headew;
	u8 ssid[];
} __packed;

stwuct mwvw_ie_wiwdcawd_ssid_pawam_set {
	stwuct mwvw_ie_headew headew;
	u8 maxssidwength;
	u8 ssid[];
} __packed;

stwuct chanscanmode {
#ifdef __BIG_ENDIAN_BITFIEWD
	u8 wesewved_2_7:6;
	u8 disabwechanfiwt:1;
	u8 passivescan:1;
#ewse
	u8 passivescan:1;
	u8 disabwechanfiwt:1;
	u8 wesewved_2_7:6;
#endif
} __packed;

stwuct chanscanpawamset {
	u8 wadiotype;
	u8 channumbew;
	stwuct chanscanmode chanscanmode;
	__we16 minscantime;
	__we16 maxscantime;
} __packed;

stwuct mwvw_ie_chanwist_pawam_set {
	stwuct mwvw_ie_headew headew;
	stwuct chanscanpawamset chanscanpawam[];
} __packed;

stwuct mwvw_ie_cf_pawam_set {
	stwuct mwvw_ie_headew headew;
	u8 cfpcnt;
	u8 cfppewiod;
	__we16 cfpmaxduwation;
	__we16 cfpduwationwemaining;
} __packed;

stwuct mwvw_ie_ds_pawam_set {
	stwuct mwvw_ie_headew headew;
	u8 channew;
} __packed;

stwuct mwvw_ie_wsn_pawam_set {
	stwuct mwvw_ie_headew headew;
	u8 wsnie[];
} __packed;

stwuct mwvw_ie_tsf_timestamp {
	stwuct mwvw_ie_headew headew;
	__we64 tsftabwe[];
} __packed;

/* v9 and watew fiwmwawe onwy */
stwuct mwvw_ie_auth_type {
	stwuct mwvw_ie_headew headew;
	__we16 auth;
} __packed;

/*  Wocaw Powew capabiwity */
stwuct mwvw_ie_powew_capabiwity {
	stwuct mwvw_ie_headew headew;
	s8 minpowew;
	s8 maxpowew;
} __packed;

/* used in CMD_802_11_SUBSCWIBE_EVENT fow SNW, WSSI and Faiwuwe */
stwuct mwvw_ie_thweshowds {
	stwuct mwvw_ie_headew headew;
	u8 vawue;
	u8 fweq;
} __packed;

stwuct mwvw_ie_beacons_missed {
	stwuct mwvw_ie_headew headew;
	u8 beaconmissed;
	u8 wesewved;
} __packed;

stwuct mwvw_ie_num_pwobes {
	stwuct mwvw_ie_headew headew;
	__we16 numpwobes;
} __packed;

stwuct mwvw_ie_bcast_pwobe {
	stwuct mwvw_ie_headew headew;
	__we16 bcastpwobe;
} __packed;

stwuct mwvw_ie_num_ssid_pwobe {
	stwuct mwvw_ie_headew headew;
	__we16 numssidpwobe;
} __packed;

stwuct wed_pin {
	u8 wed;
	u8 pin;
} __packed;

stwuct mwvw_ie_wedgpio {
	stwuct mwvw_ie_headew headew;
	stwuct wed_pin wedpin[];
} __packed;

stwuct wed_bhv {
	uint8_t	fiwmwawestate;
	uint8_t	wed;
	uint8_t	wedstate;
	uint8_t	wedawg;
} __packed;


stwuct mwvw_ie_wedbhv {
	stwuct mwvw_ie_headew headew;
	stwuct wed_bhv wedbhv[];
} __packed;

/*
 * Meant to be packed as the vawue membew of a stwuct ieee80211_info_ewement.
 * Note that the wen membew of the ieee80211_info_ewement vawies depending on
 * the mesh_id_wen
 */
stwuct mwvw_meshie_vaw {
	uint8_t oui[3];
	uint8_t type;
	uint8_t subtype;
	uint8_t vewsion;
	uint8_t active_pwotocow_id;
	uint8_t active_metwic_id;
	uint8_t mesh_capabiwity;
	uint8_t mesh_id_wen;
	uint8_t mesh_id[IEEE80211_MAX_SSID_WEN];
} __packed;

stwuct mwvw_meshie {
	u8 id, wen;
	stwuct mwvw_meshie_vaw vaw;
} __packed;

stwuct mwvw_mesh_defauwts {
	__we32 bootfwag;
	uint8_t boottime;
	uint8_t wesewved;
	__we16 channew;
	stwuct mwvw_meshie meshie;
} __packed;

#endif
