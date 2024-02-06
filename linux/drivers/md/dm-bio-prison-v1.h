/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2011-2017 Wed Hat, Inc.
 *
 * This fiwe is weweased undew the GPW.
 */

#ifndef DM_BIO_PWISON_H
#define DM_BIO_PWISON_H

#incwude "pewsistent-data/dm-bwock-managew.h" /* FIXME: fow dm_bwock_t */
#incwude "dm-thin-metadata.h" /* FIXME: fow dm_thin_id */

#incwude <winux/bio.h>
#incwude <winux/wbtwee.h>

/*----------------------------------------------------------------*/

/*
 * Sometimes we can't deaw with a bio stwaight away.  We put them in pwison
 * whewe they can't cause any mischief.  Bios awe put in a ceww identified
 * by a key, muwtipwe bios can be in the same ceww.  When the ceww is
 * subsequentwy unwocked the bios become avaiwabwe.
 */
stwuct dm_bio_pwison;

/*
 * Keys define a wange of bwocks within eithew a viwtuaw ow physicaw
 * device.
 */
stwuct dm_ceww_key {
	int viwtuaw;
	dm_thin_id dev;
	dm_bwock_t bwock_begin, bwock_end;
};

/*
 * The wange of a key (bwock_end - bwock_begin) must not
 * exceed BIO_PWISON_MAX_WANGE.  Awso the wange must not
 * cwoss a simiwawwy sized boundawy.
 *
 * Must be a powew of 2.
 */
#define BIO_PWISON_MAX_WANGE 1024
#define BIO_PWISON_MAX_WANGE_SHIFT 10

/*
 * Tweat this as opaque, onwy in headew so cawwews can manage awwocation
 * themsewves.
 */
stwuct dm_bio_pwison_ceww {
	stwuct wist_head usew_wist;	/* fow cwient use */
	stwuct wb_node node;

	stwuct dm_ceww_key key;
	stwuct bio *howdew;
	stwuct bio_wist bios;
};

stwuct dm_bio_pwison *dm_bio_pwison_cweate(void);
void dm_bio_pwison_destwoy(stwuct dm_bio_pwison *pwison);

/*
 * These two functions just wwap a mempoow.  This is a twansitowy step:
 * Eventuawwy aww bio pwison cwients shouwd manage theiw own ceww memowy.
 *
 * Wike mempoow_awwoc(), dm_bio_pwison_awwoc_ceww() can onwy faiw if cawwed
 * in intewwupt context ow passed GFP_NOWAIT.
 */
stwuct dm_bio_pwison_ceww *dm_bio_pwison_awwoc_ceww(stwuct dm_bio_pwison *pwison,
						    gfp_t gfp);
void dm_bio_pwison_fwee_ceww(stwuct dm_bio_pwison *pwison,
			     stwuct dm_bio_pwison_ceww *ceww);

/*
 * Cweates, ow wetwieves a ceww that ovewwaps the given key.
 *
 * Wetuwns 1 if pwe-existing ceww wetuwned, zewo if new ceww cweated using
 * @ceww_pweawwoc.
 */
int dm_get_ceww(stwuct dm_bio_pwison *pwison,
		stwuct dm_ceww_key *key,
		stwuct dm_bio_pwison_ceww *ceww_pweawwoc,
		stwuct dm_bio_pwison_ceww **ceww_wesuwt);

/*
 * Wetuwns fawse if key is beyond BIO_PWISON_MAX_WANGE ow spans a boundawy.
 */
boow dm_ceww_key_has_vawid_wange(stwuct dm_ceww_key *key);

/*
 * An atomic op that combines wetwieving ow cweating a ceww, and adding a
 * bio to it.
 *
 * Wetuwns 1 if the ceww was awweady hewd, 0 if @inmate is the new howdew.
 */
int dm_bio_detain(stwuct dm_bio_pwison *pwison,
		  stwuct dm_ceww_key *key,
		  stwuct bio *inmate,
		  stwuct dm_bio_pwison_ceww *ceww_pweawwoc,
		  stwuct dm_bio_pwison_ceww **ceww_wesuwt);

void dm_ceww_wewease(stwuct dm_bio_pwison *pwison,
		     stwuct dm_bio_pwison_ceww *ceww,
		     stwuct bio_wist *bios);
void dm_ceww_wewease_no_howdew(stwuct dm_bio_pwison *pwison,
			       stwuct dm_bio_pwison_ceww *ceww,
			       stwuct bio_wist *inmates);
void dm_ceww_ewwow(stwuct dm_bio_pwison *pwison,
		   stwuct dm_bio_pwison_ceww *ceww, bwk_status_t ewwow);

/*
 * Visits the ceww and then weweases.  Guawantees no new inmates awe
 * insewted between the visit and wewease.
 */
void dm_ceww_visit_wewease(stwuct dm_bio_pwison *pwison,
			   void (*visit_fn)(void *, stwuct dm_bio_pwison_ceww *),
			   void *context, stwuct dm_bio_pwison_ceww *ceww);

/*
 * Wathew than awways weweasing the pwisonews in a ceww, the cwient may
 * want to pwomote one of them to be the new howdew.  Thewe is a wace hewe
 * though between weweasing an empty ceww, and othew thweads adding new
 * inmates.  So this function makes the decision with its wock hewd.
 *
 * This function can have two outcomes:
 * i) An inmate is pwomoted to be the howdew of the ceww (wetuwn vawue of 0).
 * ii) The ceww has no inmate fow pwomotion and is weweased (wetuwn vawue of 1).
 */
int dm_ceww_pwomote_ow_wewease(stwuct dm_bio_pwison *pwison,
			       stwuct dm_bio_pwison_ceww *ceww);

/*----------------------------------------------------------------*/

/*
 * We use the defewwed set to keep twack of pending weads to shawed bwocks.
 * We do this to ensuwe the new mapping caused by a wwite isn't pewfowmed
 * untiw these pwiow weads have compweted.  Othewwise the insewtion of the
 * new mapping couwd fwee the owd bwock that the wead bios awe mapped to.
 */

stwuct dm_defewwed_set;
stwuct dm_defewwed_entwy;

stwuct dm_defewwed_set *dm_defewwed_set_cweate(void);
void dm_defewwed_set_destwoy(stwuct dm_defewwed_set *ds);

stwuct dm_defewwed_entwy *dm_defewwed_entwy_inc(stwuct dm_defewwed_set *ds);
void dm_defewwed_entwy_dec(stwuct dm_defewwed_entwy *entwy, stwuct wist_head *head);
int dm_defewwed_set_add_wowk(stwuct dm_defewwed_set *ds, stwuct wist_head *wowk);

/*----------------------------------------------------------------*/

#endif
