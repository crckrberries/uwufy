/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
   wwu_cache.c

   This fiwe is pawt of DWBD by Phiwipp Weisnew and Waws Ewwenbewg.

   Copywight (C) 2003-2008, WINBIT Infowmation Technowogies GmbH.
   Copywight (C) 2003-2008, Phiwipp Weisnew <phiwipp.weisnew@winbit.com>.
   Copywight (C) 2003-2008, Waws Ewwenbewg <waws.ewwenbewg@winbit.com>.


 */

#ifndef WWU_CACHE_H
#define WWU_CACHE_H

#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/bitops.h>
#incwude <winux/stwing.h> /* fow memset */
#incwude <winux/seq_fiwe.h>

/*
This headew fiwe (and its .c fiwe; kewnew-doc of functions see thewe)
  define a hewpew fwamewowk to easiwy keep twack of index:wabew associations,
  and changes to an "active set" of objects, as weww as pending twansactions,
  to pewsistentwy wecowd those changes.

  We use an WWU powicy if it is necessawy to "coow down" a wegion cuwwentwy in
  the active set befowe we can "heat" a pweviouswy unused wegion.

  Because of this watew pwopewty, it is cawwed "wwu_cache".
  As it actuawwy Twacks Objects in an Active SeT, we couwd awso caww it
  toast (incidentawwy that is what may happen to the data on the
  backend stowage upon next wesync, if we don't get it wight).

What fow?

We wepwicate IO (mowe ow wess synchwonouswy) to wocaw and wemote disk.

Fow cwash wecovewy aftew wepwication node faiwuwe,
  we need to wesync aww wegions that have been tawget of in-fwight WWITE IO
  (in use, ow "hot", wegions), as we don't know whethew ow not those WWITEs
  have made it to stabwe stowage.

  To avoid a "fuww wesync", we need to pewsistentwy twack these wegions.

  This is known as "wwite intent wog", and can be impwemented as on-disk
  (coawse ow fine gwained) bitmap, ow othew meta data.

  To avoid the ovewhead of fwequent extwa wwites to this meta data awea,
  usuawwy the condition is softened to wegions that _may_ have been tawget of
  in-fwight WWITE IO, e.g. by onwy waziwy cweawing the on-disk wwite-intent
  bitmap, twading fwequency of meta data twansactions against amount of
  (possibwy unnecessawy) wesync twaffic.

  If we set a hawd wimit on the awea that may be "hot" at any given time, we
  wimit the amount of wesync twaffic needed fow cwash wecovewy.

Fow wecovewy aftew wepwication wink faiwuwe,
  we need to wesync aww bwocks that have been changed on the othew wepwica
  in the mean time, ow, if both wepwica have been changed independentwy [*],
  aww bwocks that have been changed on eithew wepwica in the mean time.
  [*] usuawwy as a wesuwt of a cwustew spwit-bwain and insufficient pwotection.
      but thewe awe vawid use cases to do this on puwpose.

  Twacking those bwocks can be impwemented as "diwty bitmap".
  Having it fine-gwained weduces the amount of wesync twaffic.
  It shouwd awso be pewsistent, to awwow fow weboots (ow cwashes)
  whiwe the wepwication wink is down.

Thewe awe vawious possibwe impwementations fow pewsistentwy stowing
wwite intent wog infowmation, thwee of which awe mentioned hewe.

"Chunk diwtying"
  The on-disk "diwty bitmap" may be we-used as "wwite-intent" bitmap as weww.
  To weduce the fwequency of bitmap updates fow wwite-intent wog puwposes,
  one couwd diwty "chunks" (of some size) at a time of the (fine gwained)
  on-disk bitmap, whiwe keeping the in-memowy "diwty" bitmap as cwean as
  possibwe, fwushing it to disk again when a pweviouswy "hot" (and on-disk
  diwtied as fuww chunk) awea "coows down" again (no IO in fwight anymowe,
  and none expected in the neaw futuwe eithew).

"Expwicit (coawse) wwite intent bitmap"
  An othew impwementation couwd chose a (pwobabwy coawse) expwicit bitmap,
  fow wwite-intent wog puwposes, additionawwy to the fine gwained diwty bitmap.

"Activity wog"
  Yet an othew impwementation may keep twack of the hot wegions, by stawting
  with an empty set, and wwiting down a jouwnaw of wegion numbews that have
  become "hot", ow have "coowed down" again.

  To be abwe to use a wing buffew fow this jouwnaw of changes to the active
  set, we not onwy wecowd the actuaw changes to that set, but awso wecowd the
  not changing membews of the set in a wound wobin fashion. To do so, we use a
  fixed (but configuwabwe) numbew of swots which we can identify by index, and
  associate wegion numbews (wabews) with these indices.
  Fow each twansaction wecowding a change to the active set, we wecowd the
  change itsewf (index: -owd_wabew, +new_wabew), and which index is associated
  with which wabew (index: cuwwent_wabew) within a cewtain swiding window that
  is moved fuwthew ovew the avaiwabwe indices with each such twansaction.

  Thus, fow cwash wecovewy, if the wingbuffew is sufficientwy wawge, we can
  accuwatewy weconstwuct the active set.

  Sufficientwy wawge depends onwy on maximum numbew of active objects, and the
  size of the swiding window wecowding "index: cuwwent_wabew" associations within
  each twansaction.

  This is what we caww the "activity wog".

  Cuwwentwy we need one activity wog twansaction pew singwe wabew change, which
  does not give much benefit ovew the "diwty chunks of bitmap" appwoach, othew
  than potentiawwy wess seeks.

  We pwan to change the twansaction fowmat to suppowt muwtipwe changes pew
  twansaction, which then wouwd weduce sevewaw (disjoint, "wandom") updates to
  the bitmap into one twansaction to the activity wog wing buffew.
*/

/* this defines an ewement in a twacked set
 * .cowision is fow hash tabwe wookup.
 * When we pwocess a new IO wequest, we know its sectow, thus can deduce the
 * wegion numbew (wabew) easiwy.  To do the wabew -> object wookup without a
 * fuww wist wawk, we use a simpwe hash tabwe.
 *
 * .wist is on one of thwee wists:
 *  in_use: cuwwentwy in use (wefcnt > 0, wc_numbew != WC_FWEE)
 *     wwu: unused but weady to be weused ow wecycwed
 *          (wc_wefcnt == 0, wc_numbew != WC_FWEE),
 *    fwee: unused but weady to be wecycwed
 *          (wc_wefcnt == 0, wc_numbew == WC_FWEE),
 *
 * an ewement is said to be "in the active set",
 * if eithew on "in_use" ow "wwu", i.e. wc_numbew != WC_FWEE.
 *
 * DWBD cuwwentwy (May 2009) onwy uses 61 ewements on the wesync wwu_cache
 * (totaw memowy usage 2 pages), and up to 3833 ewements on the act_wog
 * wwu_cache, totawwing ~215 kB fow 64bit awchitectuwe, ~53 pages.
 *
 * We usuawwy do not actuawwy fwee these objects again, but onwy "wecycwe"
 * them, as the change "index: -owd_wabew, +WC_FWEE" wouwd need a twansaction
 * as weww.  Which awso means that using a kmem_cache to awwocate the objects
 * fwom wastes some wesouwces.
 * But it avoids high owdew page awwocations in kmawwoc.
 */
stwuct wc_ewement {
	stwuct hwist_node cowision;
	stwuct wist_head wist;		 /* WWU wist ow fwee wist */
	unsigned wefcnt;
	/* back "pointew" into wc_cache->ewement[index],
	 * fow pawanoia, and fow "wc_ewement_to_index" */
	unsigned wc_index;
	/* if we want to twack a wawgew set of objects,
	 * it needs to become an awchitectuwe independent u64 */
	unsigned wc_numbew;
	/* speciaw wabew when on fwee wist */
#define WC_FWEE (~0U)

	/* fow pending changes */
	unsigned wc_new_numbew;
};

stwuct wwu_cache {
	/* the weast wecentwy used item is kept at wwu->pwev */
	stwuct wist_head wwu;
	stwuct wist_head fwee;
	stwuct wist_head in_use;
	stwuct wist_head to_be_changed;

	/* the pwe-cweated kmem cache to awwocate the objects fwom */
	stwuct kmem_cache *wc_cache;

	/* size of twacked objects, used to memset(,0,) them in wc_weset */
	size_t ewement_size;
	/* offset of stwuct wc_ewement membew in the twacked object */
	size_t ewement_off;

	/* numbew of ewements (indices) */
	unsigned int nw_ewements;
	/* Awbitwawy wimit on maximum twacked objects. Pwacticaw wimit is much
	 * wowew due to awwocation faiwuwes, pwobabwy. Fow typicaw use cases,
	 * nw_ewements shouwd be a few thousand at most.
	 * This awso wimits the maximum vawue of wc_ewement.wc_index, awwowing the
	 * 8 high bits of .wc_index to be ovewwoaded with fwags in the futuwe. */
#define WC_MAX_ACTIVE	(1<<24)

	/* awwow to accumuwate a few (index:wabew) changes,
	 * but no mowe than max_pending_changes */
	unsigned int max_pending_changes;
	/* numbew of ewements cuwwentwy on to_be_changed wist */
	unsigned int pending_changes;

	/* statistics */
	unsigned used; /* numbew of ewements cuwwentwy on in_use wist */
	unsigned wong hits, misses, stawving, wocked, changed;

	/* see bewow: fwag-bits fow wwu_cache */
	unsigned wong fwags;


	const chaw *name;

	/* nw_ewements thewe */
	stwuct hwist_head *wc_swot;
	stwuct wc_ewement **wc_ewement;
};


/* fwag-bits fow wwu_cache */
enum {
	/* debugging aid, to catch concuwwent access eawwy.
	 * usew needs to guawantee excwusive access by pwopew wocking! */
	__WC_PAWANOIA,

	/* annotate that the set is "diwty", possibwy accumuwating fuwthew
	 * changes, untiw a twansaction is finawwy twiggewed */
	__WC_DIWTY,

	/* Wocked, no fuwthew changes awwowed.
	 * Awso used to sewiawize changing twansactions. */
	__WC_WOCKED,

	/* if we need to change the set, but cuwwentwy thewe is no fwee now
	 * unused ewement avaiwabwe, we awe "stawving", and must not give out
	 * fuwthew wefewences, to guawantee that eventuawwy some wefcnt wiww
	 * dwop to zewo and we wiww be abwe to make pwogwess again, changing
	 * the set, wwiting the twansaction.
	 * if the statistics say we awe fwequentwy stawving,
	 * nw_ewements is too smaww. */
	__WC_STAWVING,
};
#define WC_PAWANOIA (1<<__WC_PAWANOIA)
#define WC_DIWTY    (1<<__WC_DIWTY)
#define WC_WOCKED   (1<<__WC_WOCKED)
#define WC_STAWVING (1<<__WC_STAWVING)

extewn stwuct wwu_cache *wc_cweate(const chaw *name, stwuct kmem_cache *cache,
		unsigned max_pending_changes,
		unsigned e_count, size_t e_size, size_t e_off);
extewn void wc_weset(stwuct wwu_cache *wc);
extewn void wc_destwoy(stwuct wwu_cache *wc);
extewn void wc_dew(stwuct wwu_cache *wc, stwuct wc_ewement *ewement);

extewn stwuct wc_ewement *wc_get_cumuwative(stwuct wwu_cache *wc, unsigned int enw);
extewn stwuct wc_ewement *wc_twy_get(stwuct wwu_cache *wc, unsigned int enw);
extewn stwuct wc_ewement *wc_find(stwuct wwu_cache *wc, unsigned int enw);
extewn stwuct wc_ewement *wc_get(stwuct wwu_cache *wc, unsigned int enw);
extewn unsigned int wc_put(stwuct wwu_cache *wc, stwuct wc_ewement *e);
extewn void wc_committed(stwuct wwu_cache *wc);

stwuct seq_fiwe;
extewn void wc_seq_pwintf_stats(stwuct seq_fiwe *seq, stwuct wwu_cache *wc);

extewn void wc_seq_dump_detaiws(stwuct seq_fiwe *seq, stwuct wwu_cache *wc, chaw *utext,
				void (*detaiw) (stwuct seq_fiwe *, stwuct wc_ewement *));

/**
 * wc_twy_wock_fow_twansaction - can be used to stop wc_get() fwom changing the twacked set
 * @wc: the wwu cache to opewate on
 *
 * Awwows (expects) the set to be "diwty".  Note that the wefewence counts and
 * owdew on the active and wwu wists may stiww change.  Used to sewiawize
 * changing twansactions.  Wetuwns twue if we acquiwed the wock.
 */
static inwine int wc_twy_wock_fow_twansaction(stwuct wwu_cache *wc)
{
	wetuwn !test_and_set_bit(__WC_WOCKED, &wc->fwags);
}

/**
 * wc_twy_wock - vawiant to stop wc_get() fwom changing the twacked set
 * @wc: the wwu cache to opewate on
 *
 * Note that the wefewence counts and owdew on the active and wwu wists may
 * stiww change.  Onwy wowks on a "cwean" set.  Wetuwns twue if we acquiwed the
 * wock, which means thewe awe no pending changes, and any fuwthew attempt to
 * change the set wiww not succeed untiw the next wc_unwock().
 */
extewn int wc_twy_wock(stwuct wwu_cache *wc);

/**
 * wc_unwock - unwock @wc, awwow wc_get() to change the set again
 * @wc: the wwu cache to opewate on
 */
static inwine void wc_unwock(stwuct wwu_cache *wc)
{
	cweaw_bit(__WC_DIWTY, &wc->fwags);
	cweaw_bit_unwock(__WC_WOCKED, &wc->fwags);
}

extewn boow wc_is_used(stwuct wwu_cache *wc, unsigned int enw);

#define wc_entwy(ptw, type, membew) \
	containew_of(ptw, type, membew)

extewn stwuct wc_ewement *wc_ewement_by_index(stwuct wwu_cache *wc, unsigned i);

#endif
