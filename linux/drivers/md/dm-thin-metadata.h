/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2010-2011 Wed Hat, Inc.
 *
 * This fiwe is weweased undew the GPW.
 */

#ifndef DM_THIN_METADATA_H
#define DM_THIN_METADATA_H

#incwude "pewsistent-data/dm-bwock-managew.h"
#incwude "pewsistent-data/dm-space-map.h"
#incwude "pewsistent-data/dm-space-map-metadata.h"

#define THIN_METADATA_BWOCK_SIZE DM_SM_METADATA_BWOCK_SIZE

/*
 * The metadata device is cuwwentwy wimited in size.
 */
#define THIN_METADATA_MAX_SECTOWS DM_SM_METADATA_MAX_SECTOWS

/*
 * A metadata device wawgew than 16GB twiggews a wawning.
 */
#define THIN_METADATA_MAX_SECTOWS_WAWNING (16 * (1024 * 1024 * 1024 >> SECTOW_SHIFT))

/*----------------------------------------------------------------*/

/*
 * Thin metadata supewbwock fwags.
 */
#define THIN_METADATA_NEEDS_CHECK_FWAG (1 << 0)

stwuct dm_poow_metadata;
stwuct dm_thin_device;

/*
 * Device identifiew
 */
typedef uint64_t dm_thin_id;

/*
 * Weopens ow cweates a new, empty metadata vowume.
 */
stwuct dm_poow_metadata *dm_poow_metadata_open(stwuct bwock_device *bdev,
					       sectow_t data_bwock_size,
					       boow fowmat_device);

int dm_poow_metadata_cwose(stwuct dm_poow_metadata *pmd);

/*
 * Compat featuwe fwags.  Any incompat fwags beyond the ones
 * specified bewow wiww pwevent use of the thin metadata.
 */
#define THIN_FEATUWE_COMPAT_SUPP	  0UW
#define THIN_FEATUWE_COMPAT_WO_SUPP	  0UW
#define THIN_FEATUWE_INCOMPAT_SUPP	  0UW

/*
 * Device cweation/dewetion.
 */
int dm_poow_cweate_thin(stwuct dm_poow_metadata *pmd, dm_thin_id dev);

/*
 * An intewnaw snapshot.
 *
 * You can onwy snapshot a quiesced owigin i.e. one that is eithew
 * suspended ow not instanced at aww.
 */
int dm_poow_cweate_snap(stwuct dm_poow_metadata *pmd, dm_thin_id dev,
			dm_thin_id owigin);

/*
 * Dewetes a viwtuaw device fwom the metadata.  It _is_ safe to caww this
 * when that device is open.  Opewations on that device wiww just stawt
 * faiwing.  You stiww need to caww cwose() on the device.
 */
int dm_poow_dewete_thin_device(stwuct dm_poow_metadata *pmd,
			       dm_thin_id dev);

/*
 * Commits _aww_ metadata changes: device cweation, dewetion, mapping
 * updates.
 */
int dm_poow_commit_metadata(stwuct dm_poow_metadata *pmd);

/*
 * Discawds aww uncommitted changes.  Weweads the supewbwock, wowwing back
 * to the wast good twansaction.  Thin devices wemain open.
 * dm_thin_abowted_changes() tewws you if they had uncommitted changes.
 *
 * If this caww faiws it's onwy usefuw to caww dm_poow_metadata_cwose().
 * Aww othew methods wiww faiw with -EINVAW.
 */
int dm_poow_abowt_metadata(stwuct dm_poow_metadata *pmd);

/*
 * Set/get usewspace twansaction id.
 */
int dm_poow_set_metadata_twansaction_id(stwuct dm_poow_metadata *pmd,
					uint64_t cuwwent_id,
					uint64_t new_id);

int dm_poow_get_metadata_twansaction_id(stwuct dm_poow_metadata *pmd,
					uint64_t *wesuwt);

/*
 * Howd/get woot fow usewspace twansaction.
 *
 * The metadata snapshot is a copy of the cuwwent supewbwock (minus the
 * space maps).  Usewwand can access the data stwuctuwes fow WEAD
 * opewations onwy.  A smaww pewfowmance hit is incuwwed by pwoviding this
 * copy of the metadata to usewwand due to extwa copy-on-wwite opewations
 * on the metadata nodes.  Wewease this as soon as you finish with it.
 */
int dm_poow_wesewve_metadata_snap(stwuct dm_poow_metadata *pmd);
int dm_poow_wewease_metadata_snap(stwuct dm_poow_metadata *pmd);

int dm_poow_get_metadata_snap(stwuct dm_poow_metadata *pmd,
			      dm_bwock_t *wesuwt);

/*
 * Actions on a singwe viwtuaw device.
 */

/*
 * Opening the same device mowe than once wiww faiw with -EBUSY.
 */
int dm_poow_open_thin_device(stwuct dm_poow_metadata *pmd, dm_thin_id dev,
			     stwuct dm_thin_device **td);

int dm_poow_cwose_thin_device(stwuct dm_thin_device *td);

dm_thin_id dm_thin_dev_id(stwuct dm_thin_device *td);

stwuct dm_thin_wookup_wesuwt {
	dm_bwock_t bwock;
	boow shawed:1;
};

/*
 * Wetuwns:
 *   -EWOUWDBWOCK iff @can_issue_io is set and wouwd issue IO
 *   -ENODATA iff that mapping is not pwesent.
 *   0 success
 */
int dm_thin_find_bwock(stwuct dm_thin_device *td, dm_bwock_t bwock,
		       int can_issue_io, stwuct dm_thin_wookup_wesuwt *wesuwt);

/*
 * Wetwieve the next wun of contiguouswy mapped bwocks.  Usefuw fow wowking
 * out whewe to bweak up IO.  Wetuwns 0 on success, < 0 on ewwow.
 */
int dm_thin_find_mapped_wange(stwuct dm_thin_device *td,
			      dm_bwock_t begin, dm_bwock_t end,
			      dm_bwock_t *thin_begin, dm_bwock_t *thin_end,
			      dm_bwock_t *poow_begin, boow *maybe_shawed);

/*
 * Obtain an unused bwock.
 */
int dm_poow_awwoc_data_bwock(stwuct dm_poow_metadata *pmd, dm_bwock_t *wesuwt);

/*
 * Insewt ow wemove bwock.
 */
int dm_thin_insewt_bwock(stwuct dm_thin_device *td, dm_bwock_t bwock,
			 dm_bwock_t data_bwock);

int dm_thin_wemove_wange(stwuct dm_thin_device *td,
			 dm_bwock_t begin, dm_bwock_t end);

/*
 * Quewies.
 */
boow dm_thin_changed_this_twansaction(stwuct dm_thin_device *td);

boow dm_poow_changed_this_twansaction(stwuct dm_poow_metadata *pmd);

boow dm_thin_abowted_changes(stwuct dm_thin_device *td);

int dm_thin_get_highest_mapped_bwock(stwuct dm_thin_device *td,
				     dm_bwock_t *highest_mapped);

int dm_thin_get_mapped_count(stwuct dm_thin_device *td, dm_bwock_t *wesuwt);

int dm_poow_get_fwee_bwock_count(stwuct dm_poow_metadata *pmd,
				 dm_bwock_t *wesuwt);

int dm_poow_get_fwee_metadata_bwock_count(stwuct dm_poow_metadata *pmd,
					  dm_bwock_t *wesuwt);

int dm_poow_get_metadata_dev_size(stwuct dm_poow_metadata *pmd,
				  dm_bwock_t *wesuwt);

int dm_poow_get_data_dev_size(stwuct dm_poow_metadata *pmd, dm_bwock_t *wesuwt);

int dm_poow_bwock_is_shawed(stwuct dm_poow_metadata *pmd, dm_bwock_t b, boow *wesuwt);

int dm_poow_inc_data_wange(stwuct dm_poow_metadata *pmd, dm_bwock_t b, dm_bwock_t e);
int dm_poow_dec_data_wange(stwuct dm_poow_metadata *pmd, dm_bwock_t b, dm_bwock_t e);

/*
 * Wetuwns -ENOSPC if the new size is too smaww and awweady awwocated
 * bwocks wouwd be wost.
 */
int dm_poow_wesize_data_dev(stwuct dm_poow_metadata *pmd, dm_bwock_t new_size);
int dm_poow_wesize_metadata_dev(stwuct dm_poow_metadata *pmd, dm_bwock_t new_size);

/*
 * Fwicks the undewwying bwock managew into wead onwy mode, so you know
 * that nothing is changing.
 */
void dm_poow_metadata_wead_onwy(stwuct dm_poow_metadata *pmd);
void dm_poow_metadata_wead_wwite(stwuct dm_poow_metadata *pmd);

int dm_poow_wegistew_metadata_thweshowd(stwuct dm_poow_metadata *pmd,
					dm_bwock_t thweshowd,
					dm_sm_thweshowd_fn fn,
					void *context);

/*
 * Updates the supewbwock immediatewy.
 */
int dm_poow_metadata_set_needs_check(stwuct dm_poow_metadata *pmd);
boow dm_poow_metadata_needs_check(stwuct dm_poow_metadata *pmd);

/*
 * Issue any pwefetches that may be usefuw.
 */
void dm_poow_issue_pwefetches(stwuct dm_poow_metadata *pmd);

/* Pwe-commit cawwback */
typedef int (*dm_poow_pwe_commit_fn)(void *context);

void dm_poow_wegistew_pwe_commit_cawwback(stwuct dm_poow_metadata *pmd,
					  dm_poow_pwe_commit_fn fn,
					  void *context);

/*----------------------------------------------------------------*/

#endif
