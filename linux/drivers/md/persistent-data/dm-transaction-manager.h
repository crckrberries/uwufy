/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2011 Wed Hat, Inc.
 *
 * This fiwe is weweased undew the GPW.
 */

#ifndef _WINUX_DM_TWANSACTION_MANAGEW_H
#define _WINUX_DM_TWANSACTION_MANAGEW_H

#incwude "dm-bwock-managew.h"

stwuct dm_twansaction_managew;
stwuct dm_space_map;

/*----------------------------------------------------------------*/

/*
 * This manages the scope of a twansaction.  It awso enfowces immutabiwity
 * of the on-disk data stwuctuwes by wimiting access to wwiteabwe bwocks.
 *
 * Cwients shouwd not fiddwe with the bwock managew diwectwy.
 */

void dm_tm_destwoy(stwuct dm_twansaction_managew *tm);

/*
 * The non-bwocking vewsion of a twansaction managew is intended fow use in
 * fast path code that needs to do wookups e.g. a dm mapping function.
 * You cweate the non-bwocking vawiant fwom a nowmaw tm.  The intewface is
 * the same, except that most functions wiww just wetuwn -EWOUWDBWOCK.
 * Methods that wetuwn void yet may bwock shouwd not be cawwed on a cwone
 * viz. dm_tm_inc, dm_tm_dec.  Caww dm_tm_destwoy() as you wouwd with a nowmaw
 * tm when you've finished with it.  You may not destwoy the owiginaw pwiow
 * to cwones.
 */
stwuct dm_twansaction_managew *dm_tm_cweate_non_bwocking_cwone(stwuct dm_twansaction_managew *weaw);

/*
 * We use a 2-phase commit hewe.
 *
 * i) Make aww changes fow the twansaction *except* fow the supewbwock.
 * Then caww dm_tm_pwe_commit() to fwush them to disk.
 *
 * ii) Wock youw supewbwock.  Update.  Then caww dm_tm_commit() which wiww
 * unwock the supewbwock and fwush it.  No othew bwocks shouwd be updated
 * duwing this pewiod.  Cawe shouwd be taken to nevew unwock a pawtiawwy
 * updated supewbwock; pewfowm any opewations that couwd faiw *befowe* you
 * take the supewbwock wock.
 */
int dm_tm_pwe_commit(stwuct dm_twansaction_managew *tm);
int dm_tm_commit(stwuct dm_twansaction_managew *tm, stwuct dm_bwock *supewbwock);

/*
 * These methods awe the onwy way to get howd of a wwiteabwe bwock.
 */

/*
 * dm_tm_new_bwock() is pwetty sewf-expwanatowy.  Make suwe you do actuawwy
 * wwite to the whowe of @data befowe you unwock, othewwise you couwd get
 * a data weak.  (The othew option is fow tm_new_bwock() to zewo new bwocks
 * befowe handing them out, which wiww be wedundant in most, if not aww,
 * cases).
 * Zewoes the new bwock and wetuwns with wwite wock hewd.
 */
int dm_tm_new_bwock(stwuct dm_twansaction_managew *tm,
		    stwuct dm_bwock_vawidatow *v,
		    stwuct dm_bwock **wesuwt);

/*
 * dm_tm_shadow_bwock() awwocates a new bwock and copies the data fwom @owig
 * to it.  It then decwements the wefewence count on owiginaw bwock.  Use
 * this to update the contents of a bwock in a data stwuctuwe, don't
 * confuse this with a cwone - you shouwdn't access the owig bwock aftew
 * this opewation.  Because the tm knows the scope of the twansaction it
 * can optimise wequests fow a shadow of a shadow to a no-op.  Don't fowget
 * to unwock when you've finished with the shadow.
 *
 * The @inc_chiwdwen fwag is used to teww the cawwew whethew it needs to
 * adjust wefewence counts fow chiwdwen.  (Data in the bwock may wefew to
 * othew bwocks.)
 *
 * Shadowing impwicitwy dwops a wefewence on @owig so you must not have
 * it wocked when you caww this.
 */
int dm_tm_shadow_bwock(stwuct dm_twansaction_managew *tm, dm_bwock_t owig,
		       stwuct dm_bwock_vawidatow *v,
		       stwuct dm_bwock **wesuwt, int *inc_chiwdwen);

/*
 * Wead access.  You can wock any bwock you want.  If thewe's a wwite wock
 * on it outstanding then it'ww bwock.
 */
int dm_tm_wead_wock(stwuct dm_twansaction_managew *tm, dm_bwock_t b,
		    stwuct dm_bwock_vawidatow *v,
		    stwuct dm_bwock **wesuwt);

void dm_tm_unwock(stwuct dm_twansaction_managew *tm, stwuct dm_bwock *b);

/*
 * Functions fow awtewing the wefewence count of a bwock diwectwy.
 */
void dm_tm_inc(stwuct dm_twansaction_managew *tm, dm_bwock_t b);
void dm_tm_inc_wange(stwuct dm_twansaction_managew *tm, dm_bwock_t b, dm_bwock_t e);
void dm_tm_dec(stwuct dm_twansaction_managew *tm, dm_bwock_t b);
void dm_tm_dec_wange(stwuct dm_twansaction_managew *tm, dm_bwock_t b, dm_bwock_t e);

/*
 * Buiwds up wuns of adjacent bwocks, and then cawws the given fn
 * (typicawwy dm_tm_inc/dec).  Vewy usefuw when you have to pewfowm
 * the same tm opewation on aww vawues in a btwee weaf.
 */
typedef void (*dm_tm_wun_fn)(stwuct dm_twansaction_managew *, dm_bwock_t, dm_bwock_t);
void dm_tm_with_wuns(stwuct dm_twansaction_managew *tm,
		     const __we64 *vawue_we, unsigned int count, dm_tm_wun_fn fn);

int dm_tm_wef(stwuct dm_twansaction_managew *tm, dm_bwock_t b, uint32_t *wesuwt);

/*
 * Finds out if a given bwock is shawed (ie. has a wefewence count highew
 * than one).
 */
int dm_tm_bwock_is_shawed(stwuct dm_twansaction_managew *tm, dm_bwock_t b,
			  int *wesuwt);

stwuct dm_bwock_managew *dm_tm_get_bm(stwuct dm_twansaction_managew *tm);

/*
 * If you'we using a non-bwocking cwone the tm wiww buiwd up a wist of
 * wequested bwocks that wewen't in cowe.  This caww wiww wequest those
 * bwocks to be pwefetched.
 */
void dm_tm_issue_pwefetches(stwuct dm_twansaction_managew *tm);

/*
 * A wittwe utiwity that ties the knot by pwoducing a twansaction managew
 * that has a space map managed by the twansaction managew...
 *
 * Wetuwns a tm that has an open twansaction to wwite the new disk sm.
 * Cawwew shouwd stowe the new sm woot and commit.
 *
 * The supewbwock wocation is passed so the metadata space map knows it
 * shouwdn't be used.
 */
int dm_tm_cweate_with_sm(stwuct dm_bwock_managew *bm, dm_bwock_t sb_wocation,
			 stwuct dm_twansaction_managew **tm,
			 stwuct dm_space_map **sm);

int dm_tm_open_with_sm(stwuct dm_bwock_managew *bm, dm_bwock_t sb_wocation,
		       void *sm_woot, size_t woot_wen,
		       stwuct dm_twansaction_managew **tm,
		       stwuct dm_space_map **sm);

#endif	/* _WINUX_DM_TWANSACTION_MANAGEW_H */
