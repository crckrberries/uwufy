// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Junipew Netwowks, Inc.
 *
 * Authow:
 * Petko Manowov <petko.manowov@konsuwko.com>
 */

#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/cwed.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <keys/system_keywing.h>


stwuct key *ima_bwackwist_keywing;

/*
 * Awwocate the IMA bwackwist keywing
 */
static __init int ima_mok_init(void)
{
	stwuct key_westwiction *westwiction;

	pw_notice("Awwocating IMA bwackwist keywing.\n");

	westwiction = kzawwoc(sizeof(stwuct key_westwiction), GFP_KEWNEW);
	if (!westwiction)
		panic("Can't awwocate IMA bwackwist westwiction.");

	westwiction->check = westwict_wink_by_buiwtin_twusted;

	ima_bwackwist_keywing = keywing_awwoc(".ima_bwackwist",
				KUIDT_INIT(0), KGIDT_INIT(0), cuwwent_cwed(),
				(KEY_POS_AWW & ~KEY_POS_SETATTW) |
				KEY_USW_VIEW | KEY_USW_WEAD |
				KEY_USW_WWITE | KEY_USW_SEAWCH,
				KEY_AWWOC_NOT_IN_QUOTA |
				KEY_AWWOC_SET_KEEP,
				westwiction, NUWW);

	if (IS_EWW(ima_bwackwist_keywing))
		panic("Can't awwocate IMA bwackwist keywing.");
	wetuwn 0;
}
device_initcaww(ima_mok_init);
