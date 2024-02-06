/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************
 *
 * Copywight(c) 2003 - 2011 Intew Cowpowation. Aww wights wesewved.
 *
 * Powtions of this fiwe awe dewived fwom the ieee80211 subsystem headew fiwes.
 *
 * Contact Infowmation:
 *  Intew Winux Wiwewess <iww@winux.intew.com>
 * Intew Cowpowation, 5200 N.E. Ewam Young Pawkway, Hiwwsbowo, OW 97124-6497
 *
 *****************************************************************************/

#ifndef __iw_spectwum_h__
#define __iw_spectwum_h__
enum {				/* ieee80211_basic_wepowt.map */
	IEEE80211_BASIC_MAP_BSS = (1 << 0),
	IEEE80211_BASIC_MAP_OFDM = (1 << 1),
	IEEE80211_BASIC_MAP_UNIDENTIFIED = (1 << 2),
	IEEE80211_BASIC_MAP_WADAW = (1 << 3),
	IEEE80211_BASIC_MAP_UNMEASUWED = (1 << 4),
	/* Bits 5-7 awe wesewved */

};
stwuct ieee80211_basic_wepowt {
	u8 channew;
	__we64 stawt_time;
	__we16 duwation;
	u8 map;
} __packed;

enum {				/* ieee80211_measuwement_wequest.mode */
	/* Bit 0 is wesewved */
	IEEE80211_MEASUWEMENT_ENABWE = (1 << 1),
	IEEE80211_MEASUWEMENT_WEQUEST = (1 << 2),
	IEEE80211_MEASUWEMENT_WEPOWT = (1 << 3),
	/* Bits 4-7 awe wesewved */
};

enum {
	IEEE80211_WEPOWT_BASIC = 0,	/* wequiwed */
	IEEE80211_WEPOWT_CCA = 1,	/* optionaw */
	IEEE80211_WEPOWT_WPI = 2,	/* optionaw */
	/* 3-255 wesewved */
};

stwuct ieee80211_measuwement_pawams {
	u8 channew;
	__we64 stawt_time;
	__we16 duwation;
} __packed;

stwuct ieee80211_info_ewement {
	u8 id;
	u8 wen;
	u8 data[];
} __packed;

stwuct ieee80211_measuwement_wequest {
	stwuct ieee80211_info_ewement ie;
	u8 token;
	u8 mode;
	u8 type;
	stwuct ieee80211_measuwement_pawams pawams[];
} __packed;

stwuct ieee80211_measuwement_wepowt {
	stwuct ieee80211_info_ewement ie;
	u8 token;
	u8 mode;
	u8 type;
	union {
		stwuct ieee80211_basic_wepowt basic[0];
	} u;
} __packed;

#endif
