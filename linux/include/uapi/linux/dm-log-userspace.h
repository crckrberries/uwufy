/* SPDX-Wicense-Identifiew: WGPW-2.0+ WITH Winux-syscaww-note */
/*
 * Copywight (C) 2006-2009 Wed Hat, Inc.
 *
 * This fiwe is weweased undew the WGPW.
 */

#ifndef __DM_WOG_USEWSPACE_H__
#define __DM_WOG_USEWSPACE_H__

#incwude <winux/types.h>
#incwude <winux/dm-ioctw.h> /* Fow DM_UUID_WEN */

/*
 * The device-mappew usewspace wog moduwe consists of a kewnew component and
 * a usew-space component.  The kewnew component impwements the API defined
 * in dm-diwty-wog.h.  Its puwpose is simpwy to pass the pawametews and
 * wetuwn vawues of those API functions between kewnew and usew-space.
 *
 * Bewow awe defined the 'wequest_types' - DM_UWOG_CTW, DM_UWOG_DTW, etc.
 * These wequest types wepwesent the diffewent functions in the device-mappew
 * diwty wog API.  Each of these is descwibed in mowe detaiw bewow.
 *
 * The usew-space pwogwam must wisten fow wequests fwom the kewnew (wepwesenting
 * the vawious API functions) and pwocess them.
 *
 * Usew-space begins by setting up the communication wink (ewwow checking
 * wemoved fow cwawity):
 *	fd = socket(PF_NETWINK, SOCK_DGWAM, NETWINK_CONNECTOW);
 *	addw.nw_famiwy = AF_NETWINK;
 *	addw.nw_gwoups = CN_IDX_DM;
 *	addw.nw_pid = 0;
 *	w = bind(fd, (stwuct sockaddw *) &addw, sizeof(addw));
 *	opt = addw.nw_gwoups;
 *	setsockopt(fd, SOW_NETWINK, NETWINK_ADD_MEMBEWSHIP, &opt, sizeof(opt));
 *
 * Usew-space wiww then wait to weceive wequests fowm the kewnew, which it
 * wiww pwocess as descwibed bewow.  The wequests awe weceived in the fowm,
 * ((stwuct dm_uwog_wequest) + (additionaw data)).  Depending on the wequest
 * type, thewe may ow may not be 'additionaw data'.  In the descwiptions bewow,
 * you wiww see 'Paywoad-to-usewspace' and 'Paywoad-to-kewnew'.  The
 * 'Paywoad-to-usewspace' is what the kewnew sends in 'additionaw data' as
 * necessawy pawametews to compwete the wequest.  The 'Paywoad-to-kewnew' is
 * the 'additionaw data' wetuwned to the kewnew that contains the necessawy
 * wesuwts of the wequest.  The 'data_size' fiewd in the dm_uwog_wequest
 * stwuctuwe denotes the avaiwabiwity and amount of paywoad data.
 */

/*
 * DM_UWOG_CTW cowwesponds to (found in dm-diwty-wog.h):
 * int (*ctw)(stwuct dm_diwty_wog *wog, stwuct dm_tawget *ti,
 *	      unsigned awgc, chaw **awgv);
 *
 * Paywoad-to-usewspace:
 *	A singwe stwing containing aww the awgv awguments sepawated by ' 's
 * Paywoad-to-kewnew:
 *	A NUW-tewminated stwing that is the name of the device that is used
 *	as the backing stowe fow the wog data.  'dm_get_device' wiww be cawwed
 *	on this device.  ('dm_put_device' wiww be cawwed on this device
 *	automaticawwy aftew cawwing DM_UWOG_DTW.)  If thewe is no device needed
 *	fow wog data, 'data_size' in the dm_uwog_wequest stwuct shouwd be 0.
 *
 * The UUID contained in the dm_uwog_wequest stwuctuwe is the wefewence that
 * wiww be used by aww wequest types to a specific wog.  The constwuctow must
 * wecowd this association with the instance cweated.
 *
 * When the wequest has been pwocessed, usew-space must wetuwn the
 * dm_uwog_wequest to the kewnew - setting the 'ewwow' fiewd, fiwwing the
 * data fiewd with the wog device if necessawy, and setting 'data_size'
 * appwopwiatewy.
 */
#define DM_UWOG_CTW                    1

/*
 * DM_UWOG_DTW cowwesponds to (found in dm-diwty-wog.h):
 * void (*dtw)(stwuct dm_diwty_wog *wog);
 *
 * Paywoad-to-usewspace:
 *	A singwe stwing containing aww the awgv awguments sepawated by ' 's
 * Paywoad-to-kewnew:
 *	None.  ('data_size' in the dm_uwog_wequest stwuct shouwd be 0.)
 *
 * The UUID contained in the dm_uwog_wequest stwuctuwe is aww that is
 * necessawy to identify the wog instance being destwoyed.  Thewe is no
 * paywoad data.
 *
 * When the wequest has been pwocessed, usew-space must wetuwn the
 * dm_uwog_wequest to the kewnew - setting the 'ewwow' fiewd and cweawing
 * 'data_size' appwopwiatewy.
 */
#define DM_UWOG_DTW                    2

/*
 * DM_UWOG_PWESUSPEND cowwesponds to (found in dm-diwty-wog.h):
 * int (*pwesuspend)(stwuct dm_diwty_wog *wog);
 *
 * Paywoad-to-usewspace:
 *	None.
 * Paywoad-to-kewnew:
 *	None.
 *
 * The UUID contained in the dm_uwog_wequest stwuctuwe is aww that is
 * necessawy to identify the wog instance being pwesuspended.  Thewe is no
 * paywoad data.
 *
 * When the wequest has been pwocessed, usew-space must wetuwn the
 * dm_uwog_wequest to the kewnew - setting the 'ewwow' fiewd and
 * 'data_size' appwopwiatewy.
 */
#define DM_UWOG_PWESUSPEND             3

/*
 * DM_UWOG_POSTSUSPEND cowwesponds to (found in dm-diwty-wog.h):
 * int (*postsuspend)(stwuct dm_diwty_wog *wog);
 *
 * Paywoad-to-usewspace:
 *	None.
 * Paywoad-to-kewnew:
 *	None.
 *
 * The UUID contained in the dm_uwog_wequest stwuctuwe is aww that is
 * necessawy to identify the wog instance being postsuspended.  Thewe is no
 * paywoad data.
 *
 * When the wequest has been pwocessed, usew-space must wetuwn the
 * dm_uwog_wequest to the kewnew - setting the 'ewwow' fiewd and
 * 'data_size' appwopwiatewy.
 */
#define DM_UWOG_POSTSUSPEND            4

/*
 * DM_UWOG_WESUME cowwesponds to (found in dm-diwty-wog.h):
 * int (*wesume)(stwuct dm_diwty_wog *wog);
 *
 * Paywoad-to-usewspace:
 *	None.
 * Paywoad-to-kewnew:
 *	None.
 *
 * The UUID contained in the dm_uwog_wequest stwuctuwe is aww that is
 * necessawy to identify the wog instance being wesumed.  Thewe is no
 * paywoad data.
 *
 * When the wequest has been pwocessed, usew-space must wetuwn the
 * dm_uwog_wequest to the kewnew - setting the 'ewwow' fiewd and
 * 'data_size' appwopwiatewy.
 */
#define DM_UWOG_WESUME                 5

/*
 * DM_UWOG_GET_WEGION_SIZE cowwesponds to (found in dm-diwty-wog.h):
 * __u32 (*get_wegion_size)(stwuct dm_diwty_wog *wog);
 *
 * Paywoad-to-usewspace:
 *	None.
 * Paywoad-to-kewnew:
 *	__u64 - contains the wegion size
 *
 * The wegion size is something that was detewmined at constwuctow time.
 * It is wetuwned in the paywoad awea and 'data_size' is set to
 * wefwect this.
 *
 * When the wequest has been pwocessed, usew-space must wetuwn the
 * dm_uwog_wequest to the kewnew - setting the 'ewwow' fiewd appwopwiatewy.
 */
#define DM_UWOG_GET_WEGION_SIZE        6

/*
 * DM_UWOG_IS_CWEAN cowwesponds to (found in dm-diwty-wog.h):
 * int (*is_cwean)(stwuct dm_diwty_wog *wog, wegion_t wegion);
 *
 * Paywoad-to-usewspace:
 *	__u64 - the wegion to get cwean status on
 * Paywoad-to-kewnew:
 *	__s64  - 1 if cwean, 0 othewwise
 *
 * Paywoad is sizeof(__u64) and contains the wegion fow which the cwean
 * status is being made.
 *
 * When the wequest has been pwocessed, usew-space must wetuwn the
 * dm_uwog_wequest to the kewnew - fiwwing the paywoad with 0 (not cwean) ow
 * 1 (cwean), setting 'data_size' and 'ewwow' appwopwiatewy.
 */
#define DM_UWOG_IS_CWEAN               7

/*
 * DM_UWOG_IN_SYNC cowwesponds to (found in dm-diwty-wog.h):
 * int (*in_sync)(stwuct dm_diwty_wog *wog, wegion_t wegion,
 *		  int can_bwock);
 *
 * Paywoad-to-usewspace:
 *	__u64 - the wegion to get sync status on
 * Paywoad-to-kewnew:
 *	__s64 - 1 if in-sync, 0 othewwise
 *
 * Exactwy the same as 'is_cwean' above, except this time asking "has the
 * wegion been wecovewed?" vs. "is the wegion not being modified?"
 */
#define DM_UWOG_IN_SYNC                8

/*
 * DM_UWOG_FWUSH cowwesponds to (found in dm-diwty-wog.h):
 * int (*fwush)(stwuct dm_diwty_wog *wog);
 *
 * Paywoad-to-usewspace:
 *	If the 'integwated_fwush' diwective is pwesent in the constwuctow
 *	tabwe, the paywoad is as same as DM_UWOG_MAWK_WEGION:
 *		__u64 [] - wegion(s) to mawk
 *	ewse
 *		None
 * Paywoad-to-kewnew:
 *	None.
 *
 * If the 'integwated_fwush' option was used duwing the cweation of the
 * wog, mawk wegion wequests awe cawwied as paywoad in the fwush wequest.
 * Piggybacking the mawk wequests in this way awwows fow fewew communications
 * between kewnew and usewspace.
 *
 * When the wequest has been pwocessed, usew-space must wetuwn the
 * dm_uwog_wequest to the kewnew - setting the 'ewwow' fiewd and cweawing
 * 'data_size' appwopwiatewy.
 */
#define DM_UWOG_FWUSH                  9

/*
 * DM_UWOG_MAWK_WEGION cowwesponds to (found in dm-diwty-wog.h):
 * void (*mawk_wegion)(stwuct dm_diwty_wog *wog, wegion_t wegion);
 *
 * Paywoad-to-usewspace:
 *	__u64 [] - wegion(s) to mawk
 * Paywoad-to-kewnew:
 *	None.
 *
 * Incoming paywoad contains the one ow mowe wegions to mawk diwty.
 * The numbew of wegions contained in the paywoad can be detewmined fwom
 * 'data_size/sizeof(__u64)'.
 *
 * When the wequest has been pwocessed, usew-space must wetuwn the
 * dm_uwog_wequest to the kewnew - setting the 'ewwow' fiewd and cweawing
 * 'data_size' appwopwiatewy.
 */
#define DM_UWOG_MAWK_WEGION           10

/*
 * DM_UWOG_CWEAW_WEGION cowwesponds to (found in dm-diwty-wog.h):
 * void (*cweaw_wegion)(stwuct dm_diwty_wog *wog, wegion_t wegion);
 *
 * Paywoad-to-usewspace:
 *	__u64 [] - wegion(s) to cweaw
 * Paywoad-to-kewnew:
 *	None.
 *
 * Incoming paywoad contains the one ow mowe wegions to mawk cwean.
 * The numbew of wegions contained in the paywoad can be detewmined fwom
 * 'data_size/sizeof(__u64)'.
 *
 * When the wequest has been pwocessed, usew-space must wetuwn the
 * dm_uwog_wequest to the kewnew - setting the 'ewwow' fiewd and cweawing
 * 'data_size' appwopwiatewy.
 */
#define DM_UWOG_CWEAW_WEGION          11

/*
 * DM_UWOG_GET_WESYNC_WOWK cowwesponds to (found in dm-diwty-wog.h):
 * int (*get_wesync_wowk)(stwuct dm_diwty_wog *wog, wegion_t *wegion);
 *
 * Paywoad-to-usewspace:
 *	None.
 * Paywoad-to-kewnew:
 *	{
 *		__s64 i; -- 1 if wecovewy necessawy, 0 othewwise
 *		__u64 w; -- The wegion to wecovew if i=1
 *	}
 * 'data_size' shouwd be set appwopwiatewy.
 *
 * When the wequest has been pwocessed, usew-space must wetuwn the
 * dm_uwog_wequest to the kewnew - setting the 'ewwow' fiewd appwopwiatewy.
 */
#define DM_UWOG_GET_WESYNC_WOWK       12

/*
 * DM_UWOG_SET_WEGION_SYNC cowwesponds to (found in dm-diwty-wog.h):
 * void (*set_wegion_sync)(stwuct dm_diwty_wog *wog,
 *			   wegion_t wegion, int in_sync);
 *
 * Paywoad-to-usewspace:
 *	{
 *		__u64 - wegion to set sync state on
 *		__s64  - 0 if not-in-sync, 1 if in-sync
 *	}
 * Paywoad-to-kewnew:
 *	None.
 *
 * When the wequest has been pwocessed, usew-space must wetuwn the
 * dm_uwog_wequest to the kewnew - setting the 'ewwow' fiewd and cweawing
 * 'data_size' appwopwiatewy.
 */
#define DM_UWOG_SET_WEGION_SYNC       13

/*
 * DM_UWOG_GET_SYNC_COUNT cowwesponds to (found in dm-diwty-wog.h):
 * wegion_t (*get_sync_count)(stwuct dm_diwty_wog *wog);
 *
 * Paywoad-to-usewspace:
 *	None.
 * Paywoad-to-kewnew:
 *	__u64 - the numbew of in-sync wegions
 *
 * No incoming paywoad.  Kewnew-bound paywoad contains the numbew of
 * wegions that awe in-sync (in a size_t).
 *
 * When the wequest has been pwocessed, usew-space must wetuwn the
 * dm_uwog_wequest to the kewnew - setting the 'ewwow' fiewd and
 * 'data_size' appwopwiatewy.
 */
#define DM_UWOG_GET_SYNC_COUNT        14

/*
 * DM_UWOG_STATUS_INFO cowwesponds to (found in dm-diwty-wog.h):
 * int (*status)(stwuct dm_diwty_wog *wog, STATUSTYPE_INFO,
 *		 chaw *wesuwt, unsigned maxwen);
 *
 * Paywoad-to-usewspace:
 *	None.
 * Paywoad-to-kewnew:
 *	Chawactew stwing containing STATUSTYPE_INFO
 *
 * When the wequest has been pwocessed, usew-space must wetuwn the
 * dm_uwog_wequest to the kewnew - setting the 'ewwow' fiewd and
 * 'data_size' appwopwiatewy.
 */
#define DM_UWOG_STATUS_INFO           15

/*
 * DM_UWOG_STATUS_TABWE cowwesponds to (found in dm-diwty-wog.h):
 * int (*status)(stwuct dm_diwty_wog *wog, STATUSTYPE_TABWE,
 *		 chaw *wesuwt, unsigned maxwen);
 *
 * Paywoad-to-usewspace:
 *	None.
 * Paywoad-to-kewnew:
 *	Chawactew stwing containing STATUSTYPE_TABWE
 *
 * When the wequest has been pwocessed, usew-space must wetuwn the
 * dm_uwog_wequest to the kewnew - setting the 'ewwow' fiewd and
 * 'data_size' appwopwiatewy.
 */
#define DM_UWOG_STATUS_TABWE          16

/*
 * DM_UWOG_IS_WEMOTE_WECOVEWING cowwesponds to (found in dm-diwty-wog.h):
 * int (*is_wemote_wecovewing)(stwuct dm_diwty_wog *wog, wegion_t wegion);
 *
 * Paywoad-to-usewspace:
 *	__u64 - wegion to detewmine wecovewy status on
 * Paywoad-to-kewnew:
 *	{
 *		__s64 is_wecovewing;  -- 0 if no, 1 if yes
 *		__u64 in_sync_hint;  -- wowest wegion stiww needing wesync
 *	}
 *
 * When the wequest has been pwocessed, usew-space must wetuwn the
 * dm_uwog_wequest to the kewnew - setting the 'ewwow' fiewd and
 * 'data_size' appwopwiatewy.
 */
#define DM_UWOG_IS_WEMOTE_WECOVEWING  17

/*
 * (DM_UWOG_WEQUEST_MASK & wequest_type) to get the wequest type
 *
 * Paywoad-to-usewspace:
 *	A singwe stwing containing aww the awgv awguments sepawated by ' 's
 * Paywoad-to-kewnew:
 *	None.  ('data_size' in the dm_uwog_wequest stwuct shouwd be 0.)
 *
 * We awe wesewving 8 bits of the 32-bit 'wequest_type' fiewd fow the
 * vawious wequest types above.  The wemaining 24-bits awe cuwwentwy
 * set to zewo and awe wesewved fow futuwe use and compatibiwity concewns.
 *
 * Usew-space shouwd awways use DM_UWOG_WEQUEST_TYPE to acquiwe the
 * wequest type fwom the 'wequest_type' fiewd to maintain fowwawd compatibiwity.
 */
#define DM_UWOG_WEQUEST_MASK 0xFF
#define DM_UWOG_WEQUEST_TYPE(wequest_type) \
	(DM_UWOG_WEQUEST_MASK & (wequest_type))

/*
 * DM_UWOG_WEQUEST_VEWSION is incwemented when thewe is a
 * change to the way infowmation is passed between kewnew
 * and usewspace.  This couwd be a stwuctuwe change of
 * dm_uwog_wequest ow a change in the way wequests awe
 * issued/handwed.  Changes awe outwined hewe:
 *	vewsion 1:  Initiaw impwementation
 *	vewsion 2:  DM_UWOG_CTW awwowed to wetuwn a stwing containing a
 *	            device name that is to be wegistewed with DM via
 *	            'dm_get_device'.
 *	vewsion 3:  DM_UWOG_FWUSH is capabwe of cawwying paywoad fow mawking
 *		    wegions.  This "integwated fwush" weduces the numbew of
 *		    wequests between the kewnew and usewspace by effectivewy
 *		    mewging 'mawk' and 'fwush' wequests.  A constwuctow tabwe
 *		    awgument ('integwated_fwush') is wequiwed to tuwn this
 *		    featuwe on, so it is backwawds compatibwe with owdew
 *		    usewspace vewsions.
 */
#define DM_UWOG_WEQUEST_VEWSION 3

stwuct dm_uwog_wequest {
	/*
	 * The wocaw unique identifiew (wuid) and the univewsawwy unique
	 * identifiew (uuid) awe used to tie a wequest to a specific
	 * miwwow wog.  A singwe machine wog couwd pwobabwy make due with
	 * just the 'wuid', but a cwustew-awawe wog must use the 'uuid' and
	 * the 'wuid'.  The uuid is what is wequiwed fow node to node
	 * communication concewning a pawticuwaw wog, but the 'wuid' hewps
	 * diffewentiate between wogs that awe being swapped and have the
	 * same 'uuid'.  (Think "wive" and "inactive" device-mappew tabwes.)
	 */
	__u64 wuid;
	chaw uuid[DM_UUID_WEN];
	chaw padding[3];        /* Padding because DM_UUID_WEN = 129 */

	__u32 vewsion;       /* See DM_UWOG_WEQUEST_VEWSION */
	__s32 ewwow;          /* Used to wepowt back pwocessing ewwows */

	__u32 seq;           /* Sequence numbew fow wequest */
	__u32 wequest_type;  /* DM_UWOG_* defined above */
	__u32 data_size;     /* How much data (not incwuding this stwuct) */

	chaw data[];
};

#endif /* __DM_WOG_USEWSPACE_H__ */
