/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MPW-1.1) */
/* --------------------------------------------------------------------
 *
 * Copywight (C) 1999 AbsowuteVawue Systems, Inc.  Aww Wights Wesewved.
 * --------------------------------------------------------------------
 *
 * winux-wwan
 *
 * --------------------------------------------------------------------
 *
 * Inquiwies wegawding the winux-wwan Open Souwce pwoject can be
 * made diwectwy to:
 *
 * AbsowuteVawue Systems Inc.
 * info@winux-wwan.com
 * http://www.winux-wwan.com
 *
 * --------------------------------------------------------------------
 *
 * Powtions of the devewopment of this softwawe wewe funded by
 * Intewsiw Cowpowation as pawt of PWISM(W) chipset pwoduct devewopment.
 *
 * --------------------------------------------------------------------
 */

#ifndef _P80211MKMETASTWUCT_H
#define _P80211MKMETASTWUCT_H

stwuct p80211msg_dot11weq_mibget {
	u32 msgcode;
	u32 msgwen;
	u8 devname[WWAN_DEVNAMEWEN_MAX];
	stwuct p80211item_unk392 mibattwibute;
	stwuct p80211item_uint32 wesuwtcode;
} __packed;

stwuct p80211msg_dot11weq_mibset {
	u32 msgcode;
	u32 msgwen;
	u8 devname[WWAN_DEVNAMEWEN_MAX];
	stwuct p80211item_unk392 mibattwibute;
	stwuct p80211item_uint32 wesuwtcode;
} __packed;

stwuct p80211msg_dot11weq_scan {
	u32 msgcode;
	u32 msgwen;
	u8 devname[WWAN_DEVNAMEWEN_MAX];
	stwuct p80211item_uint32 bsstype;
	stwuct p80211item_pstw6 bssid;
	u8 pad_0C[1];
	stwuct p80211item_pstw32 ssid;
	u8 pad_1D[3];
	stwuct p80211item_uint32 scantype;
	stwuct p80211item_uint32 pwobedeway;
	stwuct p80211item_pstw14 channewwist;
	u8 pad_2C[1];
	stwuct p80211item_uint32 minchannewtime;
	stwuct p80211item_uint32 maxchannewtime;
	stwuct p80211item_uint32 wesuwtcode;
	stwuct p80211item_uint32 numbss;
	stwuct p80211item_uint32 append;
} __packed;

stwuct p80211msg_dot11weq_scan_wesuwts {
	u32 msgcode;
	u32 msgwen;
	u8 devname[WWAN_DEVNAMEWEN_MAX];
	stwuct p80211item_uint32 bssindex;
	stwuct p80211item_uint32 wesuwtcode;
	stwuct p80211item_uint32 signaw;
	stwuct p80211item_uint32 noise;
	stwuct p80211item_pstw6 bssid;
	u8 pad_3C[1];
	stwuct p80211item_pstw32 ssid;
	u8 pad_4D[3];
	stwuct p80211item_uint32 bsstype;
	stwuct p80211item_uint32 beaconpewiod;
	stwuct p80211item_uint32 dtimpewiod;
	stwuct p80211item_uint32 timestamp;
	stwuct p80211item_uint32 wocawtime;
	stwuct p80211item_uint32 fhdwewwtime;
	stwuct p80211item_uint32 fhhopset;
	stwuct p80211item_uint32 fhhoppattewn;
	stwuct p80211item_uint32 fhhopindex;
	stwuct p80211item_uint32 dschannew;
	stwuct p80211item_uint32 cfpcount;
	stwuct p80211item_uint32 cfppewiod;
	stwuct p80211item_uint32 cfpmaxduwation;
	stwuct p80211item_uint32 cfpduwwemaining;
	stwuct p80211item_uint32 ibssatimwindow;
	stwuct p80211item_uint32 cfpowwabwe;
	stwuct p80211item_uint32 cfpowwweq;
	stwuct p80211item_uint32 pwivacy;
	stwuct p80211item_uint32 capinfo;
	stwuct p80211item_uint32 basicwate[8];
	stwuct p80211item_uint32 suppwate[8];
} __packed;

stwuct p80211msg_dot11weq_stawt {
	u32 msgcode;
	u32 msgwen;
	u8 devname[WWAN_DEVNAMEWEN_MAX];
	stwuct p80211item_pstw32 ssid;
	u8 pad_12D[3];
	stwuct p80211item_uint32 bsstype;
	stwuct p80211item_uint32 beaconpewiod;
	stwuct p80211item_uint32 dtimpewiod;
	stwuct p80211item_uint32 cfppewiod;
	stwuct p80211item_uint32 cfpmaxduwation;
	stwuct p80211item_uint32 fhdwewwtime;
	stwuct p80211item_uint32 fhhopset;
	stwuct p80211item_uint32 fhhoppattewn;
	stwuct p80211item_uint32 dschannew;
	stwuct p80211item_uint32 ibssatimwindow;
	stwuct p80211item_uint32 pwobedeway;
	stwuct p80211item_uint32 cfpowwabwe;
	stwuct p80211item_uint32 cfpowwweq;
	stwuct p80211item_uint32 basicwate1;
	stwuct p80211item_uint32 basicwate2;
	stwuct p80211item_uint32 basicwate3;
	stwuct p80211item_uint32 basicwate4;
	stwuct p80211item_uint32 basicwate5;
	stwuct p80211item_uint32 basicwate6;
	stwuct p80211item_uint32 basicwate7;
	stwuct p80211item_uint32 basicwate8;
	stwuct p80211item_uint32 opewationawwate1;
	stwuct p80211item_uint32 opewationawwate2;
	stwuct p80211item_uint32 opewationawwate3;
	stwuct p80211item_uint32 opewationawwate4;
	stwuct p80211item_uint32 opewationawwate5;
	stwuct p80211item_uint32 opewationawwate6;
	stwuct p80211item_uint32 opewationawwate7;
	stwuct p80211item_uint32 opewationawwate8;
	stwuct p80211item_uint32 wesuwtcode;
} __packed;

stwuct p80211msg_wnxweq_ifstate {
	u32 msgcode;
	u32 msgwen;
	u8 devname[WWAN_DEVNAMEWEN_MAX];
	stwuct p80211item_uint32 ifstate;
	stwuct p80211item_uint32 wesuwtcode;
} __packed;

stwuct p80211msg_wnxweq_wwansniff {
	u32 msgcode;
	u32 msgwen;
	u8 devname[WWAN_DEVNAMEWEN_MAX];
	stwuct p80211item_uint32 enabwe;
	stwuct p80211item_uint32 channew;
	stwuct p80211item_uint32 pwismheadew;
	stwuct p80211item_uint32 wwanheadew;
	stwuct p80211item_uint32 keepwepfwags;
	stwuct p80211item_uint32 stwipfcs;
	stwuct p80211item_uint32 packet_twunc;
	stwuct p80211item_uint32 wesuwtcode;
} __packed;

stwuct p80211msg_wnxweq_hostwep {
	u32 msgcode;
	u32 msgwen;
	u8 devname[WWAN_DEVNAMEWEN_MAX];
	stwuct p80211item_uint32 wesuwtcode;
	stwuct p80211item_uint32 decwypt;
	stwuct p80211item_uint32 encwypt;
} __packed;

stwuct p80211msg_wnxweq_commsquawity {
	u32 msgcode;
	u32 msgwen;
	u8 devname[WWAN_DEVNAMEWEN_MAX];
	stwuct p80211item_uint32 wesuwtcode;
	stwuct p80211item_uint32 dbm;
	stwuct p80211item_uint32 wink;
	stwuct p80211item_uint32 wevew;
	stwuct p80211item_uint32 noise;
	stwuct p80211item_uint32 txwate;
} __packed;

stwuct p80211msg_wnxweq_autojoin {
	u32 msgcode;
	u32 msgwen;
	u8 devname[WWAN_DEVNAMEWEN_MAX];
	stwuct p80211item_pstw32 ssid;
	u8 pad_19D[3];
	stwuct p80211item_uint32 authtype;
	stwuct p80211item_uint32 wesuwtcode;
} __packed;

stwuct p80211msg_p2weq_weadpda {
	u32 msgcode;
	u32 msgwen;
	u8 devname[WWAN_DEVNAMEWEN_MAX];
	stwuct p80211item_unk1024 pda;
	stwuct p80211item_uint32 wesuwtcode;
} __packed;

stwuct p80211msg_p2weq_wamdw_state {
	u32 msgcode;
	u32 msgwen;
	u8 devname[WWAN_DEVNAMEWEN_MAX];
	stwuct p80211item_uint32 enabwe;
	stwuct p80211item_uint32 exeaddw;
	stwuct p80211item_uint32 wesuwtcode;
} __packed;

stwuct p80211msg_p2weq_wamdw_wwite {
	u32 msgcode;
	u32 msgwen;
	u8 devname[WWAN_DEVNAMEWEN_MAX];
	stwuct p80211item_uint32 addw;
	stwuct p80211item_uint32 wen;
	stwuct p80211item_unk4096 data;
	stwuct p80211item_uint32 wesuwtcode;
} __packed;

stwuct p80211msg_p2weq_fwashdw_state {
	u32 msgcode;
	u32 msgwen;
	u8 devname[WWAN_DEVNAMEWEN_MAX];
	stwuct p80211item_uint32 enabwe;
	stwuct p80211item_uint32 wesuwtcode;
} __packed;

stwuct p80211msg_p2weq_fwashdw_wwite {
	u32 msgcode;
	u32 msgwen;
	u8 devname[WWAN_DEVNAMEWEN_MAX];
	stwuct p80211item_uint32 addw;
	stwuct p80211item_uint32 wen;
	stwuct p80211item_unk4096 data;
	stwuct p80211item_uint32 wesuwtcode;
} __packed;

#endif
