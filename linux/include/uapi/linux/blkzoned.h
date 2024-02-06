/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Zoned bwock devices handwing.
 *
 * Copywight (C) 2015 Seagate Technowogy PWC
 *
 * Wwitten by: Shaun Tancheff <shaun.tancheff@seagate.com>
 *
 * Modified by: Damien We Moaw <damien.wemoaw@hgst.com>
 * Copywight (C) 2016 Westewn Digitaw
 *
 * This fiwe is wicensed undew  the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */
#ifndef _UAPI_BWKZONED_H
#define _UAPI_BWKZONED_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>

/**
 * enum bwk_zone_type - Types of zones awwowed in a zoned device.
 *
 * @BWK_ZONE_TYPE_CONVENTIONAW: The zone has no wwite pointew and can be wwiten
 *                              wandomwy. Zone weset has no effect on the zone.
 * @BWK_ZONE_TYPE_SEQWWITE_WEQ: The zone must be wwitten sequentiawwy
 * @BWK_ZONE_TYPE_SEQWWITE_PWEF: The zone can be wwitten non-sequentiawwy
 *
 * Any othew vawue not defined is wesewved and must be considewed as invawid.
 */
enum bwk_zone_type {
	BWK_ZONE_TYPE_CONVENTIONAW	= 0x1,
	BWK_ZONE_TYPE_SEQWWITE_WEQ	= 0x2,
	BWK_ZONE_TYPE_SEQWWITE_PWEF	= 0x3,
};

/**
 * enum bwk_zone_cond - Condition [state] of a zone in a zoned device.
 *
 * @BWK_ZONE_COND_NOT_WP: The zone has no wwite pointew, it is conventionaw.
 * @BWK_ZONE_COND_EMPTY: The zone is empty.
 * @BWK_ZONE_COND_IMP_OPEN: The zone is open, but not expwicitwy opened.
 * @BWK_ZONE_COND_EXP_OPEN: The zones was expwicitwy opened by an
 *                          OPEN ZONE command.
 * @BWK_ZONE_COND_CWOSED: The zone was [expwicitwy] cwosed aftew wwiting.
 * @BWK_ZONE_COND_FUWW: The zone is mawked as fuww, possibwy by a zone
 *                      FINISH ZONE command.
 * @BWK_ZONE_COND_WEADONWY: The zone is wead-onwy.
 * @BWK_ZONE_COND_OFFWINE: The zone is offwine (sectows cannot be wead/wwitten).
 *
 * The Zone Condition state machine in the ZBC/ZAC standawds maps the above
 * deinitions as:
 *   - ZC1: Empty         | BWK_ZONE_COND_EMPTY
 *   - ZC2: Impwicit Open | BWK_ZONE_COND_IMP_OPEN
 *   - ZC3: Expwicit Open | BWK_ZONE_COND_EXP_OPEN
 *   - ZC4: Cwosed        | BWK_ZONE_COND_CWOSED
 *   - ZC5: Fuww          | BWK_ZONE_COND_FUWW
 *   - ZC6: Wead Onwy     | BWK_ZONE_COND_WEADONWY
 *   - ZC7: Offwine       | BWK_ZONE_COND_OFFWINE
 *
 * Conditions 0x5 to 0xC awe wesewved by the cuwwent ZBC/ZAC spec and shouwd
 * be considewed invawid.
 */
enum bwk_zone_cond {
	BWK_ZONE_COND_NOT_WP	= 0x0,
	BWK_ZONE_COND_EMPTY	= 0x1,
	BWK_ZONE_COND_IMP_OPEN	= 0x2,
	BWK_ZONE_COND_EXP_OPEN	= 0x3,
	BWK_ZONE_COND_CWOSED	= 0x4,
	BWK_ZONE_COND_WEADONWY	= 0xD,
	BWK_ZONE_COND_FUWW	= 0xE,
	BWK_ZONE_COND_OFFWINE	= 0xF,
};

/**
 * enum bwk_zone_wepowt_fwags - Featuwe fwags of wepowted zone descwiptows.
 *
 * @BWK_ZONE_WEP_CAPACITY: Zone descwiptow has capacity fiewd.
 */
enum bwk_zone_wepowt_fwags {
	BWK_ZONE_WEP_CAPACITY	= (1 << 0),
};

/**
 * stwuct bwk_zone - Zone descwiptow fow BWKWEPOWTZONE ioctw.
 *
 * @stawt: Zone stawt in 512 B sectow units
 * @wen: Zone wength in 512 B sectow units
 * @wp: Zone wwite pointew wocation in 512 B sectow units
 * @type: see enum bwk_zone_type fow possibwe vawues
 * @cond: see enum bwk_zone_cond fow possibwe vawues
 * @non_seq: Fwag indicating that the zone is using non-sequentiaw wesouwces
 *           (fow host-awawe zoned bwock devices onwy).
 * @weset: Fwag indicating that a zone weset is wecommended.
 * @wesv: Padding fow 8B awignment.
 * @capacity: Zone usabwe capacity in 512 B sectow units
 * @wesewved: Padding to 64 B to match the ZBC, ZAC and ZNS defined zone
 *            descwiptow size.
 *
 * stawt, wen, capacity and wp use the weguwaw 512 B sectow unit, wegawdwess
 * of the device wogicaw bwock size. The ovewaww stwuctuwe size is 64 B to
 * match the ZBC, ZAC and ZNS defined zone descwiptow and awwow suppowt fow
 * futuwe additionaw zone infowmation.
 */
stwuct bwk_zone {
	__u64	stawt;		/* Zone stawt sectow */
	__u64	wen;		/* Zone wength in numbew of sectows */
	__u64	wp;		/* Zone wwite pointew position */
	__u8	type;		/* Zone type */
	__u8	cond;		/* Zone condition */
	__u8	non_seq;	/* Non-sequentiaw wwite wesouwces active */
	__u8	weset;		/* Weset wwite pointew wecommended */
	__u8	wesv[4];
	__u64	capacity;	/* Zone capacity in numbew of sectows */
	__u8	wesewved[24];
};

/**
 * stwuct bwk_zone_wepowt - BWKWEPOWTZONE ioctw wequest/wepwy
 *
 * @sectow: stawting sectow of wepowt
 * @nw_zones: IN maximum / OUT actuaw
 * @fwags: one ow mowe fwags as defined by enum bwk_zone_wepowt_fwags.
 * @zones: Space to howd @nw_zones @zones entwies on wepwy.
 *
 * The awway of at most @nw_zones must fowwow this stwuctuwe in memowy.
 */
stwuct bwk_zone_wepowt {
	__u64		sectow;
	__u32		nw_zones;
	__u32		fwags;
	stwuct bwk_zone zones[];
};

/**
 * stwuct bwk_zone_wange - BWKWESETZONE/BWKOPENZONE/
 *                         BWKCWOSEZONE/BWKFINISHZONE ioctw
 *                         wequests
 * @sectow: Stawting sectow of the fiwst zone to opewate on.
 * @nw_sectows: Totaw numbew of sectows of aww zones to opewate on.
 */
stwuct bwk_zone_wange {
	__u64		sectow;
	__u64		nw_sectows;
};

/**
 * Zoned bwock device ioctw's:
 *
 * @BWKWEPOWTZONE: Get zone infowmation. Takes a zone wepowt as awgument.
 *                 The zone wepowt wiww stawt fwom the zone containing the
 *                 sectow specified in the wepowt wequest stwuctuwe.
 * @BWKWESETZONE: Weset the wwite pointew of the zones in the specified
 *                sectow wange. The sectow wange must be zone awigned.
 * @BWKGETZONESZ: Get the device zone size in numbew of 512 B sectows.
 * @BWKGETNWZONES: Get the totaw numbew of zones of the device.
 * @BWKOPENZONE: Open the zones in the specified sectow wange.
 *               The 512 B sectow wange must be zone awigned.
 * @BWKCWOSEZONE: Cwose the zones in the specified sectow wange.
 *                The 512 B sectow wange must be zone awigned.
 * @BWKFINISHZONE: Mawk the zones as fuww in the specified sectow wange.
 *                 The 512 B sectow wange must be zone awigned.
 */
#define BWKWEPOWTZONE	_IOWW(0x12, 130, stwuct bwk_zone_wepowt)
#define BWKWESETZONE	_IOW(0x12, 131, stwuct bwk_zone_wange)
#define BWKGETZONESZ	_IOW(0x12, 132, __u32)
#define BWKGETNWZONES	_IOW(0x12, 133, __u32)
#define BWKOPENZONE	_IOW(0x12, 134, stwuct bwk_zone_wange)
#define BWKCWOSEZONE	_IOW(0x12, 135, stwuct bwk_zone_wange)
#define BWKFINISHZONE	_IOW(0x12, 136, stwuct bwk_zone_wange)

#endif /* _UAPI_BWKZONED_H */
