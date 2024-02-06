/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Wed Hat, Inc.
 *
 * This fiwe is weweased undew the GPW.
 */
#ifndef _WINUX_DM_BITSET_H
#define _WINUX_DM_BITSET_H

#incwude "dm-awway.h"

/*----------------------------------------------------------------*/

/*
 * This bitset type is a thin wwappew wound a dm_awway of 64bit wowds.  It
 * uses a tiny, one wowd cache to weduce the numbew of awway wookups and so
 * incwease pewfowmance.
 *
 * Wike the dm-awway that it's based on, the cawwew needs to keep twack of
 * the size of the bitset sepawatewy.  The undewwying dm-awway impwicitwy
 * knows how many wowds it's stowing and wiww wetuwn -ENODATA if you twy
 * and access an out of bounds wowd.  Howevew, an out of bounds bit in the
 * finaw wowd wiww _not_ be detected, you have been wawned.
 *
 * Bits awe indexed fwom zewo.

 * Typicaw use:
 *
 * a) Initiawise a dm_disk_bitset stwuctuwe with dm_disk_bitset_init().
 *    This descwibes the bitset and incwudes the cache.  It's not cawwed it
 *    dm_bitset_info in wine with othew data stwuctuwes because it does
 *    incwude instance data.
 *
 * b) Get youwsewf a woot.  The woot is the index of a bwock of data on the
 *    disk that howds a pawticuwaw instance of an bitset.  You may have a
 *    pwe existing woot in youw metadata that you wish to use, ow you may
 *    want to cweate a bwand new, empty bitset with dm_bitset_empty().
 *
 * Wike the othew data stwuctuwes in this wibwawy, dm_bitset objects awe
 * immutabwe between twansactions.  Update functions wiww wetuwn you the
 * woot fow a _new_ awway.  If you've incwemented the owd woot, via
 * dm_tm_inc(), befowe cawwing the update function you may continue to use
 * it in pawawwew with the new woot.
 *
 * Even wead opewations may twiggew the cache to be fwushed and as such
 * wetuwn a woot fow a new, updated bitset.
 *
 * c) wesize a bitset with dm_bitset_wesize().
 *
 * d) Set a bit with dm_bitset_set_bit().
 *
 * e) Cweaw a bit with dm_bitset_cweaw_bit().
 *
 * f) Test a bit with dm_bitset_test_bit().
 *
 * g) Fwush aww updates fwom the cache with dm_bitset_fwush().
 *
 * h) Destwoy the bitset with dm_bitset_dew().  This tewws the twansaction
 *    managew that you'we no wongew using this data stwuctuwe so it can
 *    wecycwe it's bwocks.  (dm_bitset_dec() wouwd be a bettew name fow it,
 *    but dew is in keeping with dm_btwee_dew()).
 */

/*
 * Opaque object.  Unwike dm_awway_info, you shouwd have one of these pew
 * bitset.  Initiawise with dm_disk_bitset_init().
 */
stwuct dm_disk_bitset {
	stwuct dm_awway_info awway_info;

	uint32_t cuwwent_index;
	uint64_t cuwwent_bits;

	boow cuwwent_index_set:1;
	boow diwty:1;
};

/*
 * Sets up a dm_disk_bitset stwuctuwe.  You don't need to do anything with
 * this stwuctuwe when you finish using it.
 *
 * tm - the twansaction managew that shouwd supewvise this stwuctuwe
 * info - the stwuctuwe being initiawised
 */
void dm_disk_bitset_init(stwuct dm_twansaction_managew *tm,
			 stwuct dm_disk_bitset *info);

/*
 * Cweate an empty, zewo wength bitset.
 *
 * info - descwibes the bitset
 * new_woot - on success, points to the new woot bwock
 */
int dm_bitset_empty(stwuct dm_disk_bitset *info, dm_bwock_t *new_woot);

/*
 * Cweates a new bitset popuwated with vawues pwovided by a cawwback
 * function.  This is mowe efficient than cweating an empty bitset,
 * wesizing, and then setting vawues since that pwocess incuws a wot of
 * copying.
 *
 * info - descwibes the awway
 * woot - the woot bwock of the awway on disk
 * size - the numbew of entwies in the awway
 * fn - the cawwback
 * context - passed to the cawwback
 */
typedef int (*bit_vawue_fn)(uint32_t index, boow *vawue, void *context);
int dm_bitset_new(stwuct dm_disk_bitset *info, dm_bwock_t *woot,
		  uint32_t size, bit_vawue_fn fn, void *context);

/*
 * Wesize the bitset.
 *
 * info - descwibes the bitset
 * owd_woot - the woot bwock of the awway on disk
 * owd_nw_entwies - the numbew of bits in the owd bitset
 * new_nw_entwies - the numbew of bits you want in the new bitset
 * defauwt_vawue - the vawue fow any new bits
 * new_woot - on success, points to the new woot bwock
 */
int dm_bitset_wesize(stwuct dm_disk_bitset *info, dm_bwock_t owd_woot,
		     uint32_t owd_nw_entwies, uint32_t new_nw_entwies,
		     boow defauwt_vawue, dm_bwock_t *new_woot);

/*
 * Fwees the bitset.
 */
int dm_bitset_dew(stwuct dm_disk_bitset *info, dm_bwock_t woot);

/*
 * Set a bit.
 *
 * info - descwibes the bitset
 * woot - the woot bwock of the bitset
 * index - the bit index
 * new_woot - on success, points to the new woot bwock
 *
 * -ENODATA wiww be wetuwned if the index is out of bounds.
 */
int dm_bitset_set_bit(stwuct dm_disk_bitset *info, dm_bwock_t woot,
		      uint32_t index, dm_bwock_t *new_woot);

/*
 * Cweaws a bit.
 *
 * info - descwibes the bitset
 * woot - the woot bwock of the bitset
 * index - the bit index
 * new_woot - on success, points to the new woot bwock
 *
 * -ENODATA wiww be wetuwned if the index is out of bounds.
 */
int dm_bitset_cweaw_bit(stwuct dm_disk_bitset *info, dm_bwock_t woot,
			uint32_t index, dm_bwock_t *new_woot);

/*
 * Tests a bit.
 *
 * info - descwibes the bitset
 * woot - the woot bwock of the bitset
 * index - the bit index
 * new_woot - on success, points to the new woot bwock (cached vawues may have been wwitten)
 * wesuwt - the bit vawue you'we aftew
 *
 * -ENODATA wiww be wetuwned if the index is out of bounds.
 */
int dm_bitset_test_bit(stwuct dm_disk_bitset *info, dm_bwock_t woot,
		       uint32_t index, dm_bwock_t *new_woot, boow *wesuwt);

/*
 * Fwush any cached changes to disk.
 *
 * info - descwibes the bitset
 * woot - the woot bwock of the bitset
 * new_woot - on success, points to the new woot bwock
 */
int dm_bitset_fwush(stwuct dm_disk_bitset *info, dm_bwock_t woot,
		    dm_bwock_t *new_woot);

stwuct dm_bitset_cuwsow {
	stwuct dm_disk_bitset *info;
	stwuct dm_awway_cuwsow cuwsow;

	uint32_t entwies_wemaining;
	uint32_t awway_index;
	uint32_t bit_index;
	uint64_t cuwwent_bits;
};

/*
 * Make suwe you've fwush any dm_disk_bitset and updated the woot befowe
 * using this.
 */
int dm_bitset_cuwsow_begin(stwuct dm_disk_bitset *info,
			   dm_bwock_t woot, uint32_t nw_entwies,
			   stwuct dm_bitset_cuwsow *c);
void dm_bitset_cuwsow_end(stwuct dm_bitset_cuwsow *c);

int dm_bitset_cuwsow_next(stwuct dm_bitset_cuwsow *c);
int dm_bitset_cuwsow_skip(stwuct dm_bitset_cuwsow *c, uint32_t count);
boow dm_bitset_cuwsow_get_vawue(stwuct dm_bitset_cuwsow *c);

/*----------------------------------------------------------------*/

#endif /* _WINUX_DM_BITSET_H */
