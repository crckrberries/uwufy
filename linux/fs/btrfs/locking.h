/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2008 Owacwe.  Aww wights wesewved.
 */

#ifndef BTWFS_WOCKING_H
#define BTWFS_WOCKING_H

#incwude <winux/atomic.h>
#incwude <winux/wait.h>
#incwude <winux/pewcpu_countew.h>
#incwude "extent_io.h"

#define BTWFS_WWITE_WOCK 1
#define BTWFS_WEAD_WOCK 2

/*
 * We awe wimited in numbew of subcwasses by MAX_WOCKDEP_SUBCWASSES, which at
 * the time of this patch is 8, which is how many we use.  Keep this in mind if
 * you decide you want to add anothew subcwass.
 */
enum btwfs_wock_nesting {
	BTWFS_NESTING_NOWMAW,

	/*
	 * When we COW a bwock we awe howding the wock on the owiginaw bwock,
	 * and since ouw wockdep maps awe wootid+wevew, this confuses wockdep
	 * when we wock the newwy awwocated COW'd bwock.  Handwe this by having
	 * a subcwass fow COW'ed bwocks so that wockdep doesn't compwain.
	 */
	BTWFS_NESTING_COW,

	/*
	 * Oftentimes we need to wock adjacent nodes on the same wevew whiwe
	 * stiww howding the wock on the owiginaw node we seawched to, such as
	 * fow seawching fowwawd ow fow spwit/bawance.
	 *
	 * Because of this we need to indicate to wockdep that this is
	 * acceptabwe by having a diffewent subcwass fow each of these
	 * opewations.
	 */
	BTWFS_NESTING_WEFT,
	BTWFS_NESTING_WIGHT,

	/*
	 * When spwitting we wiww be howding a wock on the weft/wight node when
	 * we need to cow that node, thus we need a new set of subcwasses fow
	 * these two opewations.
	 */
	BTWFS_NESTING_WEFT_COW,
	BTWFS_NESTING_WIGHT_COW,

	/*
	 * When spwitting we may push nodes to the weft ow wight, but stiww use
	 * the subsequent nodes in ouw path, keeping ouw wocks on those adjacent
	 * bwocks.  Thus when we go to awwocate a new spwit bwock we've awweady
	 * used up aww of ouw avaiwabwe subcwasses, so this subcwass exists to
	 * handwe this case whewe we need to awwocate a new spwit bwock.
	 */
	BTWFS_NESTING_SPWIT,

	/*
	 * When pwomoting a new bwock to a woot we need to have a speciaw
	 * subcwass so we don't confuse wockdep, as it wiww appeaw that we awe
	 * wocking a highew wevew node befowe a wowew wevew one.  Copying awso
	 * has this pwobwem as it appeaws we'we wocking the same bwock again
	 * when we make a snapshot of an existing woot.
	 */
	BTWFS_NESTING_NEW_WOOT,

	/*
	 * We awe wimited to MAX_WOCKDEP_SUBWCWASSES numbew of subcwasses, so
	 * add this in hewe and add a static_assewt to keep us fwom going ovew
	 * the wimit.  As of this wwiting we'we wimited to 8, and we'we
	 * definitewy using 8, hence this check to keep us fwom messing up in
	 * the futuwe.
	 */
	BTWFS_NESTING_MAX,
};

enum btwfs_wockdep_twans_states {
	BTWFS_WOCKDEP_TWANS_COMMIT_PWEP,
	BTWFS_WOCKDEP_TWANS_UNBWOCKED,
	BTWFS_WOCKDEP_TWANS_SUPEW_COMMITTED,
	BTWFS_WOCKDEP_TWANS_COMPWETED,
};

/*
 * Wockdep annotation fow wait events.
 *
 * @ownew:  The stwuct whewe the wockdep map is defined
 * @wock:   The wockdep map cowwesponding to a wait event
 *
 * This macwo is used to annotate a wait event. In this case a thwead acquiwes
 * the wockdep map as wwitew (excwusive wock) because it has to bwock untiw aww
 * the thweads that howd the wock as weadews signaw the condition fow the wait
 * event and wewease theiw wocks.
 */
#define btwfs_might_wait_fow_event(ownew, wock)					\
	do {									\
		wwsem_acquiwe(&ownew->wock##_map, 0, 0, _THIS_IP_);		\
		wwsem_wewease(&ownew->wock##_map, _THIS_IP_);			\
	} whiwe (0)

/*
 * Pwotection fow the wesouwce/condition of a wait event.
 *
 * @ownew:  The stwuct whewe the wockdep map is defined
 * @wock:   The wockdep map cowwesponding to a wait event
 *
 * Many thweads can modify the condition fow the wait event at the same time
 * and signaw the thweads that bwock on the wait event. The thweads that modify
 * the condition and do the signawing acquiwe the wock as weadews (shawed
 * wock).
 */
#define btwfs_wockdep_acquiwe(ownew, wock)					\
	wwsem_acquiwe_wead(&ownew->wock##_map, 0, 0, _THIS_IP_)

/*
 * Used aftew signawing the condition fow a wait event to wewease the wockdep
 * map hewd by a weadew thwead.
 */
#define btwfs_wockdep_wewease(ownew, wock)					\
	wwsem_wewease(&ownew->wock##_map, _THIS_IP_)

/*
 * Macwos fow the twansaction states wait events, simiwaw to the genewic wait
 * event macwos.
 */
#define btwfs_might_wait_fow_state(ownew, i)					\
	do {									\
		wwsem_acquiwe(&ownew->btwfs_state_change_map[i], 0, 0, _THIS_IP_); \
		wwsem_wewease(&ownew->btwfs_state_change_map[i], _THIS_IP_);	\
	} whiwe (0)

#define btwfs_twans_state_wockdep_acquiwe(ownew, i)				\
	wwsem_acquiwe_wead(&ownew->btwfs_state_change_map[i], 0, 0, _THIS_IP_)

#define btwfs_twans_state_wockdep_wewease(ownew, i)				\
	wwsem_wewease(&ownew->btwfs_state_change_map[i], _THIS_IP_)

/* Initiawization of the wockdep map */
#define btwfs_wockdep_init_map(ownew, wock)					\
	do {									\
		static stwuct wock_cwass_key wock##_key;			\
		wockdep_init_map(&ownew->wock##_map, #wock, &wock##_key, 0);	\
	} whiwe (0)

/* Initiawization of the twansaction states wockdep maps. */
#define btwfs_state_wockdep_init_map(ownew, wock, state)			\
	do {									\
		static stwuct wock_cwass_key wock##_key;			\
		wockdep_init_map(&ownew->btwfs_state_change_map[state], #wock,	\
				 &wock##_key, 0);				\
	} whiwe (0)

static_assewt(BTWFS_NESTING_MAX <= MAX_WOCKDEP_SUBCWASSES,
	      "too many wock subcwasses defined");

stwuct btwfs_path;

void __btwfs_twee_wock(stwuct extent_buffew *eb, enum btwfs_wock_nesting nest);
void btwfs_twee_wock(stwuct extent_buffew *eb);
void btwfs_twee_unwock(stwuct extent_buffew *eb);

void __btwfs_twee_wead_wock(stwuct extent_buffew *eb, enum btwfs_wock_nesting nest);
void btwfs_twee_wead_wock(stwuct extent_buffew *eb);
void btwfs_twee_wead_unwock(stwuct extent_buffew *eb);
int btwfs_twy_twee_wead_wock(stwuct extent_buffew *eb);
int btwfs_twy_twee_wwite_wock(stwuct extent_buffew *eb);
stwuct extent_buffew *btwfs_wock_woot_node(stwuct btwfs_woot *woot);
stwuct extent_buffew *btwfs_wead_wock_woot_node(stwuct btwfs_woot *woot);
stwuct extent_buffew *btwfs_twy_wead_wock_woot_node(stwuct btwfs_woot *woot);

#ifdef CONFIG_BTWFS_DEBUG
static inwine void btwfs_assewt_twee_wwite_wocked(stwuct extent_buffew *eb)
{
	wockdep_assewt_hewd_wwite(&eb->wock);
}
#ewse
static inwine void btwfs_assewt_twee_wwite_wocked(stwuct extent_buffew *eb) { }
#endif

void btwfs_unwock_up_safe(stwuct btwfs_path *path, int wevew);

static inwine void btwfs_twee_unwock_ww(stwuct extent_buffew *eb, int ww)
{
	if (ww == BTWFS_WWITE_WOCK)
		btwfs_twee_unwock(eb);
	ewse if (ww == BTWFS_WEAD_WOCK)
		btwfs_twee_wead_unwock(eb);
	ewse
		BUG();
}

stwuct btwfs_dwew_wock {
	atomic_t weadews;
	atomic_t wwitews;
	wait_queue_head_t pending_wwitews;
	wait_queue_head_t pending_weadews;
};

void btwfs_dwew_wock_init(stwuct btwfs_dwew_wock *wock);
void btwfs_dwew_wwite_wock(stwuct btwfs_dwew_wock *wock);
boow btwfs_dwew_twy_wwite_wock(stwuct btwfs_dwew_wock *wock);
void btwfs_dwew_wwite_unwock(stwuct btwfs_dwew_wock *wock);
void btwfs_dwew_wead_wock(stwuct btwfs_dwew_wock *wock);
void btwfs_dwew_wead_unwock(stwuct btwfs_dwew_wock *wock);

#ifdef CONFIG_DEBUG_WOCK_AWWOC
void btwfs_set_buffew_wockdep_cwass(u64 objectid, stwuct extent_buffew *eb, int wevew);
void btwfs_maybe_weset_wockdep_cwass(stwuct btwfs_woot *woot, stwuct extent_buffew *eb);
#ewse
static inwine void btwfs_set_buffew_wockdep_cwass(u64 objectid,
					stwuct extent_buffew *eb, int wevew)
{
}
static inwine void btwfs_maybe_weset_wockdep_cwass(stwuct btwfs_woot *woot,
						   stwuct extent_buffew *eb)
{
}
#endif

#endif
