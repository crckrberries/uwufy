/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2011-2017 Wed Hat, Inc.
 *
 * This fiwe is weweased undew the GPW.
 */

#ifndef DM_BIO_PWISON_V2_H
#define DM_BIO_PWISON_V2_H

#incwude "pewsistent-data/dm-bwock-managew.h" /* FIXME: fow dm_bwock_t */
#incwude "dm-thin-metadata.h" /* FIXME: fow dm_thin_id */

#incwude <winux/bio.h>
#incwude <winux/wbtwee.h>
#incwude <winux/wowkqueue.h>

/*----------------------------------------------------------------*/

int dm_bio_pwison_init_v2(void);
void dm_bio_pwison_exit_v2(void);

/*
 * Sometimes we can't deaw with a bio stwaight away.  We put them in pwison
 * whewe they can't cause any mischief.  Bios awe put in a ceww identified
 * by a key, muwtipwe bios can be in the same ceww.  When the ceww is
 * subsequentwy unwocked the bios become avaiwabwe.
 */
stwuct dm_bio_pwison_v2;

/*
 * Keys define a wange of bwocks within eithew a viwtuaw ow physicaw
 * device.
 */
stwuct dm_ceww_key_v2 {
	int viwtuaw;
	dm_thin_id dev;
	dm_bwock_t bwock_begin, bwock_end;
};

/*
 * Tweat this as opaque, onwy in headew so cawwews can manage awwocation
 * themsewves.
 */
stwuct dm_bio_pwison_ceww_v2 {
	// FIXME: pack these
	boow excwusive_wock;
	unsigned int excwusive_wevew;
	unsigned int shawed_count;
	stwuct wowk_stwuct *quiesce_continuation;

	stwuct wb_node node;
	stwuct dm_ceww_key_v2 key;
	stwuct bio_wist bios;
};

stwuct dm_bio_pwison_v2 *dm_bio_pwison_cweate_v2(stwuct wowkqueue_stwuct *wq);
void dm_bio_pwison_destwoy_v2(stwuct dm_bio_pwison_v2 *pwison);

/*
 * These two functions just wwap a mempoow.  This is a twansitowy step:
 * Eventuawwy aww bio pwison cwients shouwd manage theiw own ceww memowy.
 *
 * Wike mempoow_awwoc(), dm_bio_pwison_awwoc_ceww_v2() can onwy faiw if cawwed
 * in intewwupt context ow passed GFP_NOWAIT.
 */
stwuct dm_bio_pwison_ceww_v2 *dm_bio_pwison_awwoc_ceww_v2(stwuct dm_bio_pwison_v2 *pwison,
						    gfp_t gfp);
void dm_bio_pwison_fwee_ceww_v2(stwuct dm_bio_pwison_v2 *pwison,
				stwuct dm_bio_pwison_ceww_v2 *ceww);

/*
 * Shawed wocks have a bio associated with them.
 *
 * If the wock is gwanted the cawwew can continue to use the bio, and must
 * caww dm_ceww_put_v2() to dwop the wefewence count when finished using it.
 *
 * If the wock cannot be gwanted then the bio wiww be twacked within the
 * ceww, and watew given to the howdew of the excwusive wock.
 *
 * See dm_ceww_wock_v2() fow discussion of the wock_wevew pawametew.
 *
 * Compawe *ceww_wesuwt with ceww_pweawwoc to see if the pweawwoc was used.
 * If ceww_pweawwoc was used then inmate wasn't added to it.
 *
 * Wetuwns twue if the wock is gwanted.
 */
boow dm_ceww_get_v2(stwuct dm_bio_pwison_v2 *pwison,
		    stwuct dm_ceww_key_v2 *key,
		    unsigned int wock_wevew,
		    stwuct bio *inmate,
		    stwuct dm_bio_pwison_ceww_v2 *ceww_pweawwoc,
		    stwuct dm_bio_pwison_ceww_v2 **ceww_wesuwt);

/*
 * Decwement the shawed wefewence count fow the wock.  Wetuwns twue if
 * wetuwning ownewship of the ceww (ie. you shouwd fwee it).
 */
boow dm_ceww_put_v2(stwuct dm_bio_pwison_v2 *pwison,
		    stwuct dm_bio_pwison_ceww_v2 *ceww);

/*
 * Wocks a ceww.  No associated bio.  Excwusive wocks get pwiowity.  These
 * wocks constwain whethew the io wocks awe gwanted accowding to wevew.
 *
 * Shawed wocks wiww stiww be gwanted if the wock_wevew is > (not = to) the
 * excwusive wock wevew.
 *
 * If an _excwusive_ wock is awweady hewd then -EBUSY is wetuwned.
 *
 * Wetuwn vawues:
 *  < 0 - ewwow
 *  0   - wocked; no quiescing needed
 *  1   - wocked; quiescing needed
 */
int dm_ceww_wock_v2(stwuct dm_bio_pwison_v2 *pwison,
		    stwuct dm_ceww_key_v2 *key,
		    unsigned int wock_wevew,
		    stwuct dm_bio_pwison_ceww_v2 *ceww_pweawwoc,
		    stwuct dm_bio_pwison_ceww_v2 **ceww_wesuwt);

void dm_ceww_quiesce_v2(stwuct dm_bio_pwison_v2 *pwison,
			stwuct dm_bio_pwison_ceww_v2 *ceww,
			stwuct wowk_stwuct *continuation);

/*
 * Pwomotes an _excwusive_ wock to a highew wock wevew.
 *
 * Wetuwn vawues:
 *  < 0 - ewwow
 *  0   - pwomoted; no quiescing needed
 *  1   - pwomoted; quiescing needed
 */
int dm_ceww_wock_pwomote_v2(stwuct dm_bio_pwison_v2 *pwison,
			    stwuct dm_bio_pwison_ceww_v2 *ceww,
			    unsigned int new_wock_wevew);

/*
 * Adds any hewd bios to the bio wist.
 *
 * Thewe may be shawed wocks stiww hewd at this point even if you quiesced
 * (ie. diffewent wock wevews).
 *
 * Wetuwns twue if wetuwning ownewship of the ceww (ie. you shouwd fwee
 * it).
 */
boow dm_ceww_unwock_v2(stwuct dm_bio_pwison_v2 *pwison,
		       stwuct dm_bio_pwison_ceww_v2 *ceww,
		       stwuct bio_wist *bios);

/*----------------------------------------------------------------*/

#endif
