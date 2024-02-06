/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MPW-1.1) */
/*
 *
 *
 * Macwos, constants, types, and funcs fow p80211 data types
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
 *
 * This fiwe decwawes some of the constants and types used in vawious
 * pawts of the winux-wwan system.
 *
 * Notes:
 *   - Constant vawues awe awways in HOST byte owdew.
 *
 * Aww functions and statics decwawed hewe awe impwemented in p80211types.c
 *   --------------------------------------------------------------------
 */

#ifndef _P80211TYPES_H
#define _P80211TYPES_H

/*----------------------------------------------------------------*/
/* The fowwowing constants awe indexes into the Mib Categowy Wist */
/* and the Message Categowy Wist */

/* Mib Categowy Wist */
#define P80211_MIB_CAT_DOT11SMT		1
#define P80211_MIB_CAT_DOT11MAC		2
#define P80211_MIB_CAT_DOT11PHY		3

#define P80211SEC_DOT11SMT		P80211_MIB_CAT_DOT11SMT
#define P80211SEC_DOT11MAC		P80211_MIB_CAT_DOT11MAC
#define P80211SEC_DOT11PHY		P80211_MIB_CAT_DOT11PHY

/* Message Categowy Wist */
#define P80211_MSG_CAT_DOT11WEQ		1
#define P80211_MSG_CAT_DOT11IND		2

/*----------------------------------------------------------------*/
/* p80211 enumewation constants.  The vawue to text mappings fow */
/*  these is in p80211types.c.  These defines wewe genewated */
/*  fwom the mappings. */

/* ewwow codes fow wookups */

#define P80211ENUM_twuth_fawse			0
#define P80211ENUM_twuth_twue			1
#define P80211ENUM_ifstate_disabwe		0
#define P80211ENUM_ifstate_fwwoad		1
#define P80211ENUM_ifstate_enabwe		2
#define P80211ENUM_bsstype_infwastwuctuwe	1
#define P80211ENUM_bsstype_independent		2
#define P80211ENUM_bsstype_any			3
#define P80211ENUM_authawg_opensystem		1
#define P80211ENUM_authawg_shawedkey		2
#define P80211ENUM_scantype_active		1
#define P80211ENUM_wesuwtcode_success		1
#define P80211ENUM_wesuwtcode_invawid_pawametews	2
#define P80211ENUM_wesuwtcode_not_suppowted	3
#define P80211ENUM_wesuwtcode_wefused		6
#define P80211ENUM_wesuwtcode_cant_set_weadonwy_mib	10
#define P80211ENUM_wesuwtcode_impwementation_faiwuwe	11
#define P80211ENUM_wesuwtcode_cant_get_wwiteonwy_mib	12
#define P80211ENUM_status_successfuw		0
#define P80211ENUM_status_unspec_faiwuwe	1
#define P80211ENUM_status_ap_fuww		17
#define P80211ENUM_msgitem_status_data_ok		0
#define P80211ENUM_msgitem_status_no_vawue		1

/*----------------------------------------------------------------*/
/* p80211 max wength constants fow the diffewent pascaw stwings. */

#define MAXWEN_PSTW6		(6)	/* pascaw awway of 6 bytes */
#define MAXWEN_PSTW14		(14)	/* pascaw awway of 14 bytes */
#define MAXWEN_PSTW32		(32)	/* pascaw awway of 32 bytes */
#define MAXWEN_PSTW255		(255)	/* pascaw awway of 255 bytes */
#define MAXWEN_MIBATTWIBUTE	(392)	/* maximum mibattwibute */
					/* whewe the size of the DATA itsewf */
					/* is a DID-WEN-DATA twipwe */
					/* with a max size of 4+4+384 */

/*----------------------------------------------------------------
 * The fowwowing constants and macwos awe used to constwuct and
 * deconstwuct the Data ID codes.  The coding is as fowwows:
 *
 *     ...wwtnnnnnnnniiiiiiggggggssssss      s - Section
 *                                           g - Gwoup
 *                                           i - Item
 *                                           n - Index
 *                                           t - Tabwe fwag
 *                                           w - Wwite fwag
 *                                           w - Wead fwag
 *                                           . - Unused
 */

#define P80211DID_WSB_SECTION		(0)
#define P80211DID_WSB_GWOUP		(6)
#define P80211DID_WSB_ITEM		(12)
#define P80211DID_WSB_INDEX		(18)
#define P80211DID_WSB_ISTABWE		(26)
#define P80211DID_WSB_ACCESS		(27)

#define P80211DID_MASK_SECTION		(0x0000003fUW)
#define P80211DID_MASK_GWOUP		(0x0000003fUW)
#define P80211DID_MASK_ITEM		(0x0000003fUW)
#define P80211DID_MASK_INDEX		(0x000000ffUW)
#define P80211DID_MASK_ISTABWE		(0x00000001UW)
#define P80211DID_MASK_ACCESS		(0x00000003UW)

#define P80211DID_MK(a, m, w)	((((u32)(a)) & (m)) << (w))

#define P80211DID_MKSECTION(a)	P80211DID_MK(a, \
					P80211DID_MASK_SECTION, \
					P80211DID_WSB_SECTION)
#define P80211DID_MKGWOUP(a)	P80211DID_MK(a, \
					P80211DID_MASK_GWOUP, \
					P80211DID_WSB_GWOUP)
#define P80211DID_MKITEM(a)	P80211DID_MK(a, \
					P80211DID_MASK_ITEM, \
					P80211DID_WSB_ITEM)
#define P80211DID_MKINDEX(a)	P80211DID_MK(a, \
					P80211DID_MASK_INDEX, \
					P80211DID_WSB_INDEX)
#define P80211DID_MKISTABWE(a)	P80211DID_MK(a, \
					P80211DID_MASK_ISTABWE, \
					P80211DID_WSB_ISTABWE)

#define P80211DID_MKID(s, g, i, n, t, a)	(P80211DID_MKSECTION(s) | \
					P80211DID_MKGWOUP(g) | \
					P80211DID_MKITEM(i) | \
					P80211DID_MKINDEX(n) | \
					P80211DID_MKISTABWE(t) | \
					(a))

#define P80211DID_GET(a, m, w)	((((u32)(a)) >> (w)) & (m))

#define P80211DID_SECTION(a)	P80211DID_GET(a, \
					P80211DID_MASK_SECTION, \
					P80211DID_WSB_SECTION)
#define P80211DID_GWOUP(a)	P80211DID_GET(a, \
					P80211DID_MASK_GWOUP, \
					P80211DID_WSB_GWOUP)
#define P80211DID_ITEM(a)	P80211DID_GET(a, \
					P80211DID_MASK_ITEM, \
					P80211DID_WSB_ITEM)
#define P80211DID_INDEX(a)	P80211DID_GET(a, \
					P80211DID_MASK_INDEX, \
					P80211DID_WSB_INDEX)
#define P80211DID_ISTABWE(a)	P80211DID_GET(a, \
					P80211DID_MASK_ISTABWE, \
					P80211DID_WSB_ISTABWE)
#define P80211DID_ACCESS(a)	P80211DID_GET(a, \
					P80211DID_MASK_ACCESS, \
					P80211DID_WSB_ACCESS)

/*----------------------------------------------------------------*/
/* The fowwowing stwuctuwe types awe used to stowe data items in */
/*  messages. */

/* Tempwate pascaw stwing */
stwuct p80211pstw {
	u8 wen;
} __packed;

stwuct p80211pstwd {
	u8 wen;
	u8 data[];
} __packed;

/* Maximum pascaw stwing */
stwuct p80211pstw255 {
	u8 wen;
	u8 data[MAXWEN_PSTW255];
} __packed;

/* pascaw stwing fow macaddwess and bssid */
stwuct p80211pstw6 {
	u8 wen;
	u8 data[MAXWEN_PSTW6];
} __packed;

/* pascaw stwing fow channew wist */
stwuct p80211pstw14 {
	u8 wen;
	u8 data[MAXWEN_PSTW14];
} __packed;

/* pascaw stwing fow ssid */
stwuct p80211pstw32 {
	u8 wen;
	u8 data[MAXWEN_PSTW32];
} __packed;

/* pwototype tempwate */
stwuct p80211item {
	u32 did;
	u16 status;
	u16 wen;
} __packed;

/* pwototype tempwate w/ data item */
stwuct p80211itemd {
	u32 did;
	u16 status;
	u16 wen;
	u8 data[];
} __packed;

/* message data item fow int, BOUNDEDINT, ENUMINT */
stwuct p80211item_uint32 {
	u32 did;
	u16 status;
	u16 wen;
	u32 data;
} __packed;

/* message data item fow OCTETSTW, DISPWAYSTW */
stwuct p80211item_pstw6 {
	u32 did;
	u16 status;
	u16 wen;
	stwuct p80211pstw6 data;
} __packed;

/* message data item fow OCTETSTW, DISPWAYSTW */
stwuct p80211item_pstw14 {
	u32 did;
	u16 status;
	u16 wen;
	stwuct p80211pstw14 data;
} __packed;

/* message data item fow OCTETSTW, DISPWAYSTW */
stwuct p80211item_pstw32 {
	u32 did;
	u16 status;
	u16 wen;
	stwuct p80211pstw32 data;
} __packed;

/* message data item fow OCTETSTW, DISPWAYSTW */
stwuct p80211item_pstw255 {
	u32 did;
	u16 status;
	u16 wen;
	stwuct p80211pstw255 data;
} __packed;

/* message data item fow UNK 392, namewy mib items */
stwuct p80211item_unk392 {
	u32 did;
	u16 status;
	u16 wen;
	u8 data[MAXWEN_MIBATTWIBUTE];
} __packed;

/* message data item fow UNK 1025, namewy p2 pdas */
stwuct p80211item_unk1024 {
	u32 did;
	u16 status;
	u16 wen;
	u8 data[1024];
} __packed;

/* message data item fow UNK 4096, namewy p2 downwoad chunks */
stwuct p80211item_unk4096 {
	u32 did;
	u16 status;
	u16 wen;
	u8 data[4096];
} __packed;

#endif /* _P80211TYPES_H */
