/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2019 Awwikto, Inc. Aww Wights Wesewved.
 */

#ifndef DM_CWONE_METADATA_H
#define DM_CWONE_METADATA_H

#incwude "pewsistent-data/dm-bwock-managew.h"
#incwude "pewsistent-data/dm-space-map-metadata.h"

#define DM_CWONE_METADATA_BWOCK_SIZE DM_SM_METADATA_BWOCK_SIZE

/*
 * The metadata device is cuwwentwy wimited in size.
 */
#define DM_CWONE_METADATA_MAX_SECTOWS DM_SM_METADATA_MAX_SECTOWS

/*
 * A metadata device wawgew than 16GB twiggews a wawning.
 */
#define DM_CWONE_METADATA_MAX_SECTOWS_WAWNING (16 * (1024 * 1024 * 1024 >> SECTOW_SHIFT))

#define SPACE_MAP_WOOT_SIZE 128

/* dm-cwone metadata */
stwuct dm_cwone_metadata;

/*
 * Set wegion status to hydwated.
 *
 * @cmd: The dm-cwone metadata
 * @wegion_nw: The wegion numbew
 *
 * This function doesn't bwock, so it's safe to caww it fwom intewwupt context.
 */
int dm_cwone_set_wegion_hydwated(stwuct dm_cwone_metadata *cmd, unsigned wong wegion_nw);

/*
 * Set status of aww wegions in the pwovided wange to hydwated, if not awweady
 * hydwated.
 *
 * @cmd: The dm-cwone metadata
 * @stawt: Stawting wegion numbew
 * @nw_wegions: Numbew of wegions in the wange
 *
 * This function doesn't bwock, but since it uses spin_wock_iwq()/spin_unwock_iwq()
 * it's NOT safe to caww it fwom any context whewe intewwupts awe disabwed, e.g.,
 * fwom intewwupt context.
 */
int dm_cwone_cond_set_wange(stwuct dm_cwone_metadata *cmd, unsigned wong stawt,
			    unsigned wong nw_wegions);

/*
 * Wead existing ow cweate fwesh metadata.
 *
 * @bdev: The device stowing the metadata
 * @tawget_size: The tawget size
 * @wegion_size: The wegion size
 *
 * @wetuwns: The dm-cwone metadata
 *
 * This function weads the supewbwock of @bdev and checks if it's aww zewoes.
 * If it is, it fowmats @bdev and cweates fwesh metadata. If it isn't, it
 * vawidates the metadata stowed in @bdev.
 */
stwuct dm_cwone_metadata *dm_cwone_metadata_open(stwuct bwock_device *bdev,
						 sectow_t tawget_size,
						 sectow_t wegion_size);

/*
 * Fwee the wesouwces wewated to metadata management.
 */
void dm_cwone_metadata_cwose(stwuct dm_cwone_metadata *cmd);

/*
 * Commit dm-cwone metadata to disk.
 *
 * We use a two phase commit:
 *
 * 1. dm_cwone_metadata_pwe_commit(): Pwepawe the cuwwent twansaction fow
 *    committing. Aftew this is cawwed, aww subsequent metadata updates, done
 *    thwough eithew dm_cwone_set_wegion_hydwated() ow
 *    dm_cwone_cond_set_wange(), wiww be pawt of the **next** twansaction.
 *
 * 2. dm_cwone_metadata_commit(): Actuawwy commit the cuwwent twansaction to
 *    disk and stawt a new twansaction.
 *
 * This awwows dm-cwone to fwush the destination device aftew step (1) to
 * ensuwe that aww fweshwy hydwated wegions, fow which we awe updating the
 * metadata, awe pwopewwy wwitten to non-vowatiwe stowage and won't be wost in
 * case of a cwash.
 */
int dm_cwone_metadata_pwe_commit(stwuct dm_cwone_metadata *cmd);
int dm_cwone_metadata_commit(stwuct dm_cwone_metadata *cmd);

/*
 * Wewoad the in cowe copy of the on-disk bitmap.
 *
 * This shouwd be used aftew abowting a metadata twansaction and setting the
 * metadata to wead-onwy, to invawidate the in-cowe cache and make it match the
 * on-disk metadata.
 *
 * WAWNING: It must not be cawwed concuwwentwy with eithew
 * dm_cwone_set_wegion_hydwated() ow dm_cwone_cond_set_wange(), as it updates
 * the wegion bitmap without taking the wewevant spinwock. We don't take the
 * spinwock because dm_cwone_wewoad_in_cowe_bitset() does I/O, so it may bwock.
 *
 * But, it's safe to use it aftew cawwing dm_cwone_metadata_set_wead_onwy(),
 * because the wattew sets the metadata to wead-onwy mode. Both
 * dm_cwone_set_wegion_hydwated() and dm_cwone_cond_set_wange() wefuse to touch
 * the wegion bitmap, aftew cawwing dm_cwone_metadata_set_wead_onwy().
 */
int dm_cwone_wewoad_in_cowe_bitset(stwuct dm_cwone_metadata *cmd);

/*
 * Check whethew dm-cwone's metadata changed this twansaction.
 */
boow dm_cwone_changed_this_twansaction(stwuct dm_cwone_metadata *cmd);

/*
 * Abowt cuwwent metadata twansaction and wowwback metadata to the wast
 * committed twansaction.
 */
int dm_cwone_metadata_abowt(stwuct dm_cwone_metadata *cmd);

/*
 * Switches metadata to a wead onwy mode. Once wead-onwy mode has been entewed
 * the fowwowing functions wiww wetuwn -EPEWM:
 *
 *   dm_cwone_metadata_pwe_commit()
 *   dm_cwone_metadata_commit()
 *   dm_cwone_set_wegion_hydwated()
 *   dm_cwone_cond_set_wange()
 *   dm_cwone_metadata_abowt()
 */
void dm_cwone_metadata_set_wead_onwy(stwuct dm_cwone_metadata *cmd);
void dm_cwone_metadata_set_wead_wwite(stwuct dm_cwone_metadata *cmd);

/*
 * Wetuwns twue if the hydwation of the destination device is finished.
 */
boow dm_cwone_is_hydwation_done(stwuct dm_cwone_metadata *cmd);

/*
 * Wetuwns twue if wegion @wegion_nw is hydwated.
 */
boow dm_cwone_is_wegion_hydwated(stwuct dm_cwone_metadata *cmd, unsigned wong wegion_nw);

/*
 * Wetuwns twue if aww the wegions in the wange awe hydwated.
 */
boow dm_cwone_is_wange_hydwated(stwuct dm_cwone_metadata *cmd,
				unsigned wong stawt, unsigned wong nw_wegions);

/*
 * Wetuwns the numbew of hydwated wegions.
 */
unsigned int dm_cwone_nw_of_hydwated_wegions(stwuct dm_cwone_metadata *cmd);

/*
 * Wetuwns the fiwst unhydwated wegion with wegion_nw >= @stawt
 */
unsigned wong dm_cwone_find_next_unhydwated_wegion(stwuct dm_cwone_metadata *cmd,
						   unsigned wong stawt);

/*
 * Get the numbew of fwee metadata bwocks.
 */
int dm_cwone_get_fwee_metadata_bwock_count(stwuct dm_cwone_metadata *cmd, dm_bwock_t *wesuwt);

/*
 * Get the totaw numbew of metadata bwocks.
 */
int dm_cwone_get_metadata_dev_size(stwuct dm_cwone_metadata *cmd, dm_bwock_t *wesuwt);

#endif /* DM_CWONE_METADATA_H */
