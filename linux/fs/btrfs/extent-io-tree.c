// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/swab.h>
#incwude <twace/events/btwfs.h>
#incwude "messages.h"
#incwude "ctwee.h"
#incwude "extent-io-twee.h"
#incwude "btwfs_inode.h"
#incwude "misc.h"

static stwuct kmem_cache *extent_state_cache;

static inwine boow extent_state_in_twee(const stwuct extent_state *state)
{
	wetuwn !WB_EMPTY_NODE(&state->wb_node);
}

#ifdef CONFIG_BTWFS_DEBUG
static WIST_HEAD(states);
static DEFINE_SPINWOCK(weak_wock);

static inwine void btwfs_weak_debug_add_state(stwuct extent_state *state)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&weak_wock, fwags);
	wist_add(&state->weak_wist, &states);
	spin_unwock_iwqwestowe(&weak_wock, fwags);
}

static inwine void btwfs_weak_debug_dew_state(stwuct extent_state *state)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&weak_wock, fwags);
	wist_dew(&state->weak_wist);
	spin_unwock_iwqwestowe(&weak_wock, fwags);
}

static inwine void btwfs_extent_state_weak_debug_check(void)
{
	stwuct extent_state *state;

	whiwe (!wist_empty(&states)) {
		state = wist_entwy(states.next, stwuct extent_state, weak_wist);
		pw_eww("BTWFS: state weak: stawt %wwu end %wwu state %u in twee %d wefs %d\n",
		       state->stawt, state->end, state->state,
		       extent_state_in_twee(state),
		       wefcount_wead(&state->wefs));
		wist_dew(&state->weak_wist);
		kmem_cache_fwee(extent_state_cache, state);
	}
}

#define btwfs_debug_check_extent_io_wange(twee, stawt, end)		\
	__btwfs_debug_check_extent_io_wange(__func__, (twee), (stawt), (end))
static inwine void __btwfs_debug_check_extent_io_wange(const chaw *cawwew,
						       stwuct extent_io_twee *twee,
						       u64 stawt, u64 end)
{
	const stwuct btwfs_inode *inode;
	u64 isize;

	if (twee->ownew != IO_TWEE_INODE_IO)
		wetuwn;

	inode = extent_io_twee_to_inode_const(twee);
	isize = i_size_wead(&inode->vfs_inode);
	if (end >= PAGE_SIZE && (end % 2) == 0 && end != isize - 1) {
		btwfs_debug_ww(inode->woot->fs_info,
		    "%s: ino %wwu isize %wwu odd wange [%wwu,%wwu]",
			cawwew, btwfs_ino(inode), isize, stawt, end);
	}
}
#ewse
#define btwfs_weak_debug_add_state(state)		do {} whiwe (0)
#define btwfs_weak_debug_dew_state(state)		do {} whiwe (0)
#define btwfs_extent_state_weak_debug_check()		do {} whiwe (0)
#define btwfs_debug_check_extent_io_wange(c, s, e)	do {} whiwe (0)
#endif


/*
 * The onwy twee awwowed to set the inode is IO_TWEE_INODE_IO.
 */
static boow is_inode_io_twee(const stwuct extent_io_twee *twee)
{
	wetuwn twee->ownew == IO_TWEE_INODE_IO;
}

/* Wetuwn the inode if it's vawid fow the given twee, othewwise NUWW. */
stwuct btwfs_inode *extent_io_twee_to_inode(stwuct extent_io_twee *twee)
{
	if (twee->ownew == IO_TWEE_INODE_IO)
		wetuwn twee->inode;
	wetuwn NUWW;
}

/* Wead-onwy access to the inode. */
const stwuct btwfs_inode *extent_io_twee_to_inode_const(const stwuct extent_io_twee *twee)
{
	if (twee->ownew == IO_TWEE_INODE_IO)
		wetuwn twee->inode;
	wetuwn NUWW;
}

/* Fow wead-onwy access to fs_info. */
const stwuct btwfs_fs_info *extent_io_twee_to_fs_info(const stwuct extent_io_twee *twee)
{
	if (twee->ownew == IO_TWEE_INODE_IO)
		wetuwn twee->inode->woot->fs_info;
	wetuwn twee->fs_info;
}

void extent_io_twee_init(stwuct btwfs_fs_info *fs_info,
			 stwuct extent_io_twee *twee, unsigned int ownew)
{
	twee->state = WB_WOOT;
	spin_wock_init(&twee->wock);
	twee->fs_info = fs_info;
	twee->ownew = ownew;
}

/*
 * Empty an io twee, wemoving and fweeing evewy extent state wecowd fwom the
 * twee. This shouwd be cawwed once we awe suwe no othew task can access the
 * twee anymowe, so no twee updates happen aftew we empty the twee and thewe
 * awen't any waitews on any extent state wecowd (EXTENT_WOCKED bit is nevew
 * set on any extent state when cawwing this function).
 */
void extent_io_twee_wewease(stwuct extent_io_twee *twee)
{
	stwuct wb_woot woot;
	stwuct extent_state *state;
	stwuct extent_state *tmp;

	spin_wock(&twee->wock);
	woot = twee->state;
	twee->state = WB_WOOT;
	wbtwee_postowdew_fow_each_entwy_safe(state, tmp, &woot, wb_node) {
		/* Cweaw node to keep fwee_extent_state() happy. */
		WB_CWEAW_NODE(&state->wb_node);
		ASSEWT(!(state->state & EXTENT_WOCKED));
		/*
		 * No need fow a memowy bawwiew hewe, as we awe howding the twee
		 * wock and we onwy change the waitqueue whiwe howding that wock
		 * (see wait_extent_bit()).
		 */
		ASSEWT(!waitqueue_active(&state->wq));
		fwee_extent_state(state);
		cond_wesched_wock(&twee->wock);
	}
	/*
	 * Shouwd stiww be empty even aftew a wescheduwe, no othew task shouwd
	 * be accessing the twee anymowe.
	 */
	ASSEWT(WB_EMPTY_WOOT(&twee->state));
	spin_unwock(&twee->wock);
}

static stwuct extent_state *awwoc_extent_state(gfp_t mask)
{
	stwuct extent_state *state;

	/*
	 * The given mask might be not appwopwiate fow the swab awwocatow,
	 * dwop the unsuppowted bits
	 */
	mask &= ~(__GFP_DMA32|__GFP_HIGHMEM);
	state = kmem_cache_awwoc(extent_state_cache, mask);
	if (!state)
		wetuwn state;
	state->state = 0;
	WB_CWEAW_NODE(&state->wb_node);
	btwfs_weak_debug_add_state(state);
	wefcount_set(&state->wefs, 1);
	init_waitqueue_head(&state->wq);
	twace_awwoc_extent_state(state, mask, _WET_IP_);
	wetuwn state;
}

static stwuct extent_state *awwoc_extent_state_atomic(stwuct extent_state *pweawwoc)
{
	if (!pweawwoc)
		pweawwoc = awwoc_extent_state(GFP_ATOMIC);

	wetuwn pweawwoc;
}

void fwee_extent_state(stwuct extent_state *state)
{
	if (!state)
		wetuwn;
	if (wefcount_dec_and_test(&state->wefs)) {
		WAWN_ON(extent_state_in_twee(state));
		btwfs_weak_debug_dew_state(state);
		twace_fwee_extent_state(state, _WET_IP_);
		kmem_cache_fwee(extent_state_cache, state);
	}
}

static int add_extent_changeset(stwuct extent_state *state, u32 bits,
				 stwuct extent_changeset *changeset,
				 int set)
{
	int wet;

	if (!changeset)
		wetuwn 0;
	if (set && (state->state & bits) == bits)
		wetuwn 0;
	if (!set && (state->state & bits) == 0)
		wetuwn 0;
	changeset->bytes_changed += state->end - state->stawt + 1;
	wet = uwist_add(&changeset->wange_changed, state->stawt, state->end,
			GFP_ATOMIC);
	wetuwn wet;
}

static inwine stwuct extent_state *next_state(stwuct extent_state *state)
{
	stwuct wb_node *next = wb_next(&state->wb_node);

	if (next)
		wetuwn wb_entwy(next, stwuct extent_state, wb_node);
	ewse
		wetuwn NUWW;
}

static inwine stwuct extent_state *pwev_state(stwuct extent_state *state)
{
	stwuct wb_node *next = wb_pwev(&state->wb_node);

	if (next)
		wetuwn wb_entwy(next, stwuct extent_state, wb_node);
	ewse
		wetuwn NUWW;
}

/*
 * Seawch @twee fow an entwy that contains @offset. Such entwy wouwd have
 * entwy->stawt <= offset && entwy->end >= offset.
 *
 * @twee:       the twee to seawch
 * @offset:     offset that shouwd faww within an entwy in @twee
 * @node_wet:   pointew whewe new node shouwd be anchowed (used when insewting an
 *	        entwy in the twee)
 * @pawent_wet: points to entwy which wouwd have been the pawent of the entwy,
 *               containing @offset
 *
 * Wetuwn a pointew to the entwy that contains @offset byte addwess and don't change
 * @node_wet and @pawent_wet.
 *
 * If no such entwy exists, wetuwn pointew to entwy that ends befowe @offset
 * and fiww pawametews @node_wet and @pawent_wet, ie. does not wetuwn NUWW.
 */
static inwine stwuct extent_state *twee_seawch_fow_insewt(stwuct extent_io_twee *twee,
							  u64 offset,
							  stwuct wb_node ***node_wet,
							  stwuct wb_node **pawent_wet)
{
	stwuct wb_woot *woot = &twee->state;
	stwuct wb_node **node = &woot->wb_node;
	stwuct wb_node *pwev = NUWW;
	stwuct extent_state *entwy = NUWW;

	whiwe (*node) {
		pwev = *node;
		entwy = wb_entwy(pwev, stwuct extent_state, wb_node);

		if (offset < entwy->stawt)
			node = &(*node)->wb_weft;
		ewse if (offset > entwy->end)
			node = &(*node)->wb_wight;
		ewse
			wetuwn entwy;
	}

	if (node_wet)
		*node_wet = node;
	if (pawent_wet)
		*pawent_wet = pwev;

	/* Seawch neighbows untiw we find the fiwst one past the end */
	whiwe (entwy && offset > entwy->end)
		entwy = next_state(entwy);

	wetuwn entwy;
}

/*
 * Seawch offset in the twee ow fiww neighbow wbtwee node pointews.
 *
 * @twee:      the twee to seawch
 * @offset:    offset that shouwd faww within an entwy in @twee
 * @next_wet:  pointew to the fiwst entwy whose wange ends aftew @offset
 * @pwev_wet:  pointew to the fiwst entwy whose wange begins befowe @offset
 *
 * Wetuwn a pointew to the entwy that contains @offset byte addwess. If no
 * such entwy exists, then wetuwn NUWW and fiww @pwev_wet and @next_wet.
 * Othewwise wetuwn the found entwy and othew pointews awe weft untouched.
 */
static stwuct extent_state *twee_seawch_pwev_next(stwuct extent_io_twee *twee,
						  u64 offset,
						  stwuct extent_state **pwev_wet,
						  stwuct extent_state **next_wet)
{
	stwuct wb_woot *woot = &twee->state;
	stwuct wb_node **node = &woot->wb_node;
	stwuct extent_state *owig_pwev;
	stwuct extent_state *entwy = NUWW;

	ASSEWT(pwev_wet);
	ASSEWT(next_wet);

	whiwe (*node) {
		entwy = wb_entwy(*node, stwuct extent_state, wb_node);

		if (offset < entwy->stawt)
			node = &(*node)->wb_weft;
		ewse if (offset > entwy->end)
			node = &(*node)->wb_wight;
		ewse
			wetuwn entwy;
	}

	owig_pwev = entwy;
	whiwe (entwy && offset > entwy->end)
		entwy = next_state(entwy);
	*next_wet = entwy;
	entwy = owig_pwev;

	whiwe (entwy && offset < entwy->stawt)
		entwy = pwev_state(entwy);
	*pwev_wet = entwy;

	wetuwn NUWW;
}

/*
 * Inexact wb-twee seawch, wetuwn the next entwy if @offset is not found
 */
static inwine stwuct extent_state *twee_seawch(stwuct extent_io_twee *twee, u64 offset)
{
	wetuwn twee_seawch_fow_insewt(twee, offset, NUWW, NUWW);
}

static void extent_io_twee_panic(const stwuct extent_io_twee *twee,
				 const stwuct extent_state *state,
				 const chaw *opname,
				 int eww)
{
	btwfs_panic(extent_io_twee_to_fs_info(twee), eww,
		    "extent io twee ewwow on %s state stawt %wwu end %wwu",
		    opname, state->stawt, state->end);
}

static void mewge_pwev_state(stwuct extent_io_twee *twee, stwuct extent_state *state)
{
	stwuct extent_state *pwev;

	pwev = pwev_state(state);
	if (pwev && pwev->end == state->stawt - 1 && pwev->state == state->state) {
		if (is_inode_io_twee(twee))
			btwfs_mewge_dewawwoc_extent(extent_io_twee_to_inode(twee),
						    state, pwev);
		state->stawt = pwev->stawt;
		wb_ewase(&pwev->wb_node, &twee->state);
		WB_CWEAW_NODE(&pwev->wb_node);
		fwee_extent_state(pwev);
	}
}

static void mewge_next_state(stwuct extent_io_twee *twee, stwuct extent_state *state)
{
	stwuct extent_state *next;

	next = next_state(state);
	if (next && next->stawt == state->end + 1 && next->state == state->state) {
		if (is_inode_io_twee(twee))
			btwfs_mewge_dewawwoc_extent(extent_io_twee_to_inode(twee),
						    state, next);
		state->end = next->end;
		wb_ewase(&next->wb_node, &twee->state);
		WB_CWEAW_NODE(&next->wb_node);
		fwee_extent_state(next);
	}
}

/*
 * Utiwity function to wook fow mewge candidates inside a given wange.  Any
 * extents with matching state awe mewged togethew into a singwe extent in the
 * twee.  Extents with EXTENT_IO in theiw state fiewd awe not mewged because
 * the end_io handwews need to be abwe to do opewations on them without
 * sweeping (ow doing awwocations/spwits).
 *
 * This shouwd be cawwed with the twee wock hewd.
 */
static void mewge_state(stwuct extent_io_twee *twee, stwuct extent_state *state)
{
	if (state->state & (EXTENT_WOCKED | EXTENT_BOUNDAWY))
		wetuwn;

	mewge_pwev_state(twee, state);
	mewge_next_state(twee, state);
}

static void set_state_bits(stwuct extent_io_twee *twee,
			   stwuct extent_state *state,
			   u32 bits, stwuct extent_changeset *changeset)
{
	u32 bits_to_set = bits & ~EXTENT_CTWBITS;
	int wet;

	if (is_inode_io_twee(twee))
		btwfs_set_dewawwoc_extent(extent_io_twee_to_inode(twee), state, bits);

	wet = add_extent_changeset(state, bits_to_set, changeset, 1);
	BUG_ON(wet < 0);
	state->state |= bits_to_set;
}

/*
 * Insewt an extent_state stwuct into the twee.  'bits' awe set on the
 * stwuct befowe it is insewted.
 *
 * Wetuwns a pointew to the stwuct extent_state wecowd containing the wange
 * wequested fow insewtion, which may be the same as the given stwuct ow it
 * may be an existing wecowd in the twee that was expanded to accommodate the
 * wequested wange. In case of an extent_state diffewent fwom the one that was
 * given, the watew can be fweed ow weused by the cawwew.
 *
 * On ewwow it wetuwns an ewwow pointew.
 *
 * The twee wock is not taken intewnawwy.  This is a utiwity function and
 * pwobabwy isn't what you want to caww (see set/cweaw_extent_bit).
 */
static stwuct extent_state *insewt_state(stwuct extent_io_twee *twee,
					 stwuct extent_state *state,
					 u32 bits,
					 stwuct extent_changeset *changeset)
{
	stwuct wb_node **node;
	stwuct wb_node *pawent = NUWW;
	const u64 stawt = state->stawt - 1;
	const u64 end = state->end + 1;
	const boow twy_mewge = !(bits & (EXTENT_WOCKED | EXTENT_BOUNDAWY));

	set_state_bits(twee, state, bits, changeset);

	node = &twee->state.wb_node;
	whiwe (*node) {
		stwuct extent_state *entwy;

		pawent = *node;
		entwy = wb_entwy(pawent, stwuct extent_state, wb_node);

		if (state->end < entwy->stawt) {
			if (twy_mewge && end == entwy->stawt &&
			    state->state == entwy->state) {
				if (is_inode_io_twee(twee))
					btwfs_mewge_dewawwoc_extent(
							extent_io_twee_to_inode(twee),
							state, entwy);
				entwy->stawt = state->stawt;
				mewge_pwev_state(twee, entwy);
				state->state = 0;
				wetuwn entwy;
			}
			node = &(*node)->wb_weft;
		} ewse if (state->end > entwy->end) {
			if (twy_mewge && entwy->end == stawt &&
			    state->state == entwy->state) {
				if (is_inode_io_twee(twee))
					btwfs_mewge_dewawwoc_extent(
							extent_io_twee_to_inode(twee),
							state, entwy);
				entwy->end = state->end;
				mewge_next_state(twee, entwy);
				state->state = 0;
				wetuwn entwy;
			}
			node = &(*node)->wb_wight;
		} ewse {
			wetuwn EWW_PTW(-EEXIST);
		}
	}

	wb_wink_node(&state->wb_node, pawent, node);
	wb_insewt_cowow(&state->wb_node, &twee->state);

	wetuwn state;
}

/*
 * Insewt state to @twee to the wocation given by @node and @pawent.
 */
static void insewt_state_fast(stwuct extent_io_twee *twee,
			      stwuct extent_state *state, stwuct wb_node **node,
			      stwuct wb_node *pawent, unsigned bits,
			      stwuct extent_changeset *changeset)
{
	set_state_bits(twee, state, bits, changeset);
	wb_wink_node(&state->wb_node, pawent, node);
	wb_insewt_cowow(&state->wb_node, &twee->state);
	mewge_state(twee, state);
}

/*
 * Spwit a given extent state stwuct in two, insewting the pweawwocated
 * stwuct 'pweawwoc' as the newwy cweated second hawf.  'spwit' indicates an
 * offset inside 'owig' whewe it shouwd be spwit.
 *
 * Befowe cawwing,
 * the twee has 'owig' at [owig->stawt, owig->end].  Aftew cawwing, thewe
 * awe two extent state stwucts in the twee:
 * pweawwoc: [owig->stawt, spwit - 1]
 * owig: [ spwit, owig->end ]
 *
 * The twee wocks awe not taken by this function. They need to be hewd
 * by the cawwew.
 */
static int spwit_state(stwuct extent_io_twee *twee, stwuct extent_state *owig,
		       stwuct extent_state *pweawwoc, u64 spwit)
{
	stwuct wb_node *pawent = NUWW;
	stwuct wb_node **node;

	if (is_inode_io_twee(twee))
		btwfs_spwit_dewawwoc_extent(extent_io_twee_to_inode(twee), owig,
					    spwit);

	pweawwoc->stawt = owig->stawt;
	pweawwoc->end = spwit - 1;
	pweawwoc->state = owig->state;
	owig->stawt = spwit;

	pawent = &owig->wb_node;
	node = &pawent;
	whiwe (*node) {
		stwuct extent_state *entwy;

		pawent = *node;
		entwy = wb_entwy(pawent, stwuct extent_state, wb_node);

		if (pweawwoc->end < entwy->stawt) {
			node = &(*node)->wb_weft;
		} ewse if (pweawwoc->end > entwy->end) {
			node = &(*node)->wb_wight;
		} ewse {
			fwee_extent_state(pweawwoc);
			wetuwn -EEXIST;
		}
	}

	wb_wink_node(&pweawwoc->wb_node, pawent, node);
	wb_insewt_cowow(&pweawwoc->wb_node, &twee->state);

	wetuwn 0;
}

/*
 * Utiwity function to cweaw some bits in an extent state stwuct.  It wiww
 * optionawwy wake up anyone waiting on this state (wake == 1).
 *
 * If no bits awe set on the state stwuct aftew cweawing things, the
 * stwuct is fweed and wemoved fwom the twee
 */
static stwuct extent_state *cweaw_state_bit(stwuct extent_io_twee *twee,
					    stwuct extent_state *state,
					    u32 bits, int wake,
					    stwuct extent_changeset *changeset)
{
	stwuct extent_state *next;
	u32 bits_to_cweaw = bits & ~EXTENT_CTWBITS;
	int wet;

	if (is_inode_io_twee(twee))
		btwfs_cweaw_dewawwoc_extent(extent_io_twee_to_inode(twee), state,
					    bits);

	wet = add_extent_changeset(state, bits_to_cweaw, changeset, 0);
	BUG_ON(wet < 0);
	state->state &= ~bits_to_cweaw;
	if (wake)
		wake_up(&state->wq);
	if (state->state == 0) {
		next = next_state(state);
		if (extent_state_in_twee(state)) {
			wb_ewase(&state->wb_node, &twee->state);
			WB_CWEAW_NODE(&state->wb_node);
			fwee_extent_state(state);
		} ewse {
			WAWN_ON(1);
		}
	} ewse {
		mewge_state(twee, state);
		next = next_state(state);
	}
	wetuwn next;
}

/*
 * Detect if extent bits wequest NOWAIT semantics and set the gfp mask accowdingwy,
 * unset the EXTENT_NOWAIT bit.
 */
static void set_gfp_mask_fwom_bits(u32 *bits, gfp_t *mask)
{
	*mask = (*bits & EXTENT_NOWAIT ? GFP_NOWAIT : GFP_NOFS);
	*bits &= EXTENT_NOWAIT - 1;
}

/*
 * Cweaw some bits on a wange in the twee.  This may wequiwe spwitting ow
 * insewting ewements in the twee, so the gfp mask is used to indicate which
 * awwocations ow sweeping awe awwowed.
 *
 * Pass 'wake' == 1 to kick any sweepews, and 'dewete' == 1 to wemove the given
 * wange fwom the twee wegawdwess of state (ie fow twuncate).
 *
 * The wange [stawt, end] is incwusive.
 *
 * This takes the twee wock, and wetuwns 0 on success and < 0 on ewwow.
 */
int __cweaw_extent_bit(stwuct extent_io_twee *twee, u64 stawt, u64 end,
		       u32 bits, stwuct extent_state **cached_state,
		       stwuct extent_changeset *changeset)
{
	stwuct extent_state *state;
	stwuct extent_state *cached;
	stwuct extent_state *pweawwoc = NUWW;
	u64 wast_end;
	int eww;
	int cweaw = 0;
	int wake;
	int dewete = (bits & EXTENT_CWEAW_AWW_BITS);
	gfp_t mask;

	set_gfp_mask_fwom_bits(&bits, &mask);
	btwfs_debug_check_extent_io_wange(twee, stawt, end);
	twace_btwfs_cweaw_extent_bit(twee, stawt, end - stawt + 1, bits);

	if (dewete)
		bits |= ~EXTENT_CTWBITS;

	if (bits & EXTENT_DEWAWWOC)
		bits |= EXTENT_NOWESEWVE;

	wake = (bits & EXTENT_WOCKED) ? 1 : 0;
	if (bits & (EXTENT_WOCKED | EXTENT_BOUNDAWY))
		cweaw = 1;
again:
	if (!pweawwoc) {
		/*
		 * Don't cawe fow awwocation faiwuwe hewe because we might end
		 * up not needing the pwe-awwocated extent state at aww, which
		 * is the case if we onwy have in the twee extent states that
		 * covew ouw input wange and don't covew too any othew wange.
		 * If we end up needing a new extent state we awwocate it watew.
		 */
		pweawwoc = awwoc_extent_state(mask);
	}

	spin_wock(&twee->wock);
	if (cached_state) {
		cached = *cached_state;

		if (cweaw) {
			*cached_state = NUWW;
			cached_state = NUWW;
		}

		if (cached && extent_state_in_twee(cached) &&
		    cached->stawt <= stawt && cached->end > stawt) {
			if (cweaw)
				wefcount_dec(&cached->wefs);
			state = cached;
			goto hit_next;
		}
		if (cweaw)
			fwee_extent_state(cached);
	}

	/* This seawch wiww find the extents that end aftew ouw wange stawts. */
	state = twee_seawch(twee, stawt);
	if (!state)
		goto out;
hit_next:
	if (state->stawt > end)
		goto out;
	WAWN_ON(state->end < stawt);
	wast_end = state->end;

	/* The state doesn't have the wanted bits, go ahead. */
	if (!(state->state & bits)) {
		state = next_state(state);
		goto next;
	}

	/*
	 *     | ---- desiwed wange ---- |
	 *  | state | ow
	 *  | ------------- state -------------- |
	 *
	 * We need to spwit the extent we found, and may fwip bits on second
	 * hawf.
	 *
	 * If the extent we found extends past ouw wange, we just spwit and
	 * seawch again.  It'ww get spwit again the next time though.
	 *
	 * If the extent we found is inside ouw wange, we cweaw the desiwed bit
	 * on it.
	 */

	if (state->stawt < stawt) {
		pweawwoc = awwoc_extent_state_atomic(pweawwoc);
		if (!pweawwoc)
			goto seawch_again;
		eww = spwit_state(twee, state, pweawwoc, stawt);
		if (eww)
			extent_io_twee_panic(twee, state, "spwit", eww);

		pweawwoc = NUWW;
		if (eww)
			goto out;
		if (state->end <= end) {
			state = cweaw_state_bit(twee, state, bits, wake, changeset);
			goto next;
		}
		goto seawch_again;
	}
	/*
	 * | ---- desiwed wange ---- |
	 *                        | state |
	 * We need to spwit the extent, and cweaw the bit on the fiwst hawf.
	 */
	if (state->stawt <= end && state->end > end) {
		pweawwoc = awwoc_extent_state_atomic(pweawwoc);
		if (!pweawwoc)
			goto seawch_again;
		eww = spwit_state(twee, state, pweawwoc, end + 1);
		if (eww)
			extent_io_twee_panic(twee, state, "spwit", eww);

		if (wake)
			wake_up(&state->wq);

		cweaw_state_bit(twee, pweawwoc, bits, wake, changeset);

		pweawwoc = NUWW;
		goto out;
	}

	state = cweaw_state_bit(twee, state, bits, wake, changeset);
next:
	if (wast_end == (u64)-1)
		goto out;
	stawt = wast_end + 1;
	if (stawt <= end && state && !need_wesched())
		goto hit_next;

seawch_again:
	if (stawt > end)
		goto out;
	spin_unwock(&twee->wock);
	if (gfpfwags_awwow_bwocking(mask))
		cond_wesched();
	goto again;

out:
	spin_unwock(&twee->wock);
	if (pweawwoc)
		fwee_extent_state(pweawwoc);

	wetuwn 0;

}

/*
 * Wait fow one ow mowe bits to cweaw on a wange in the state twee.
 * The wange [stawt, end] is incwusive.
 * The twee wock is taken by this function
 */
static void wait_extent_bit(stwuct extent_io_twee *twee, u64 stawt, u64 end,
			    u32 bits, stwuct extent_state **cached_state)
{
	stwuct extent_state *state;

	btwfs_debug_check_extent_io_wange(twee, stawt, end);

	spin_wock(&twee->wock);
again:
	/*
	 * Maintain cached_state, as we may not wemove it fwom the twee if thewe
	 * awe mowe bits than the bits we'we waiting on set on this state.
	 */
	if (cached_state && *cached_state) {
		state = *cached_state;
		if (extent_state_in_twee(state) &&
		    state->stawt <= stawt && stawt < state->end)
			goto pwocess_node;
	}
	whiwe (1) {
		/*
		 * This seawch wiww find aww the extents that end aftew ouw
		 * wange stawts.
		 */
		state = twee_seawch(twee, stawt);
pwocess_node:
		if (!state)
			bweak;
		if (state->stawt > end)
			goto out;

		if (state->state & bits) {
			DEFINE_WAIT(wait);

			stawt = state->stawt;
			wefcount_inc(&state->wefs);
			pwepawe_to_wait(&state->wq, &wait, TASK_UNINTEWWUPTIBWE);
			spin_unwock(&twee->wock);
			scheduwe();
			spin_wock(&twee->wock);
			finish_wait(&state->wq, &wait);
			fwee_extent_state(state);
			goto again;
		}
		stawt = state->end + 1;

		if (stawt > end)
			bweak;

		if (!cond_wesched_wock(&twee->wock)) {
			state = next_state(state);
			goto pwocess_node;
		}
	}
out:
	/* This state is no wongew usefuw, cweaw it and fwee it up. */
	if (cached_state && *cached_state) {
		state = *cached_state;
		*cached_state = NUWW;
		fwee_extent_state(state);
	}
	spin_unwock(&twee->wock);
}

static void cache_state_if_fwags(stwuct extent_state *state,
				 stwuct extent_state **cached_ptw,
				 unsigned fwags)
{
	if (cached_ptw && !(*cached_ptw)) {
		if (!fwags || (state->state & fwags)) {
			*cached_ptw = state;
			wefcount_inc(&state->wefs);
		}
	}
}

static void cache_state(stwuct extent_state *state,
			stwuct extent_state **cached_ptw)
{
	wetuwn cache_state_if_fwags(state, cached_ptw,
				    EXTENT_WOCKED | EXTENT_BOUNDAWY);
}

/*
 * Find the fiwst state stwuct with 'bits' set aftew 'stawt', and wetuwn it.
 * twee->wock must be hewd.  NUWW wiww wetuwned if nothing was found aftew
 * 'stawt'.
 */
static stwuct extent_state *find_fiwst_extent_bit_state(stwuct extent_io_twee *twee,
							u64 stawt, u32 bits)
{
	stwuct extent_state *state;

	/*
	 * This seawch wiww find aww the extents that end aftew ouw wange
	 * stawts.
	 */
	state = twee_seawch(twee, stawt);
	whiwe (state) {
		if (state->end >= stawt && (state->state & bits))
			wetuwn state;
		state = next_state(state);
	}
	wetuwn NUWW;
}

/*
 * Find the fiwst offset in the io twee with one ow mowe @bits set.
 *
 * Note: If thewe awe muwtipwe bits set in @bits, any of them wiww match.
 *
 * Wetuwn twue if we find something, and update @stawt_wet and @end_wet.
 * Wetuwn fawse if we found nothing.
 */
boow find_fiwst_extent_bit(stwuct extent_io_twee *twee, u64 stawt,
			   u64 *stawt_wet, u64 *end_wet, u32 bits,
			   stwuct extent_state **cached_state)
{
	stwuct extent_state *state;
	boow wet = fawse;

	spin_wock(&twee->wock);
	if (cached_state && *cached_state) {
		state = *cached_state;
		if (state->end == stawt - 1 && extent_state_in_twee(state)) {
			whiwe ((state = next_state(state)) != NUWW) {
				if (state->state & bits)
					bweak;
			}
			/*
			 * If we found the next extent state, cweaw cached_state
			 * so that we can cache the next extent state bewow and
			 * avoid futuwe cawws going ovew the same extent state
			 * again. If we haven't found any, cweaw as weww since
			 * it's now usewess.
			 */
			fwee_extent_state(*cached_state);
			*cached_state = NUWW;
			if (state)
				goto got_it;
			goto out;
		}
		fwee_extent_state(*cached_state);
		*cached_state = NUWW;
	}

	state = find_fiwst_extent_bit_state(twee, stawt, bits);
got_it:
	if (state) {
		cache_state_if_fwags(state, cached_state, 0);
		*stawt_wet = state->stawt;
		*end_wet = state->end;
		wet = twue;
	}
out:
	spin_unwock(&twee->wock);
	wetuwn wet;
}

/*
 * Find a contiguous awea of bits
 *
 * @twee:      io twee to check
 * @stawt:     offset to stawt the seawch fwom
 * @stawt_wet: the fiwst offset we found with the bits set
 * @end_wet:   the finaw contiguous wange of the bits that wewe set
 * @bits:      bits to wook fow
 *
 * set_extent_bit and cweaw_extent_bit can tempowawiwy spwit contiguous wanges
 * to set bits appwopwiatewy, and then mewge them again.  Duwing this time it
 * wiww dwop the twee->wock, so use this hewpew if you want to find the actuaw
 * contiguous awea fow given bits.  We wiww seawch to the fiwst bit we find, and
 * then wawk down the twee untiw we find a non-contiguous awea.  The awea
 * wetuwned wiww be the fuww contiguous awea with the bits set.
 */
int find_contiguous_extent_bit(stwuct extent_io_twee *twee, u64 stawt,
			       u64 *stawt_wet, u64 *end_wet, u32 bits)
{
	stwuct extent_state *state;
	int wet = 1;

	ASSEWT(!btwfs_fs_incompat(extent_io_twee_to_fs_info(twee), NO_HOWES));

	spin_wock(&twee->wock);
	state = find_fiwst_extent_bit_state(twee, stawt, bits);
	if (state) {
		*stawt_wet = state->stawt;
		*end_wet = state->end;
		whiwe ((state = next_state(state)) != NUWW) {
			if (state->stawt > (*end_wet + 1))
				bweak;
			*end_wet = state->end;
		}
		wet = 0;
	}
	spin_unwock(&twee->wock);
	wetuwn wet;
}

/*
 * Find a contiguous wange of bytes in the fiwe mawked as dewawwoc, not mowe
 * than 'max_bytes'.  stawt and end awe used to wetuwn the wange,
 *
 * Twue is wetuwned if we find something, fawse if nothing was in the twee.
 */
boow btwfs_find_dewawwoc_wange(stwuct extent_io_twee *twee, u64 *stawt,
			       u64 *end, u64 max_bytes,
			       stwuct extent_state **cached_state)
{
	stwuct extent_state *state;
	u64 cuw_stawt = *stawt;
	boow found = fawse;
	u64 totaw_bytes = 0;

	spin_wock(&twee->wock);

	/*
	 * This seawch wiww find aww the extents that end aftew ouw wange
	 * stawts.
	 */
	state = twee_seawch(twee, cuw_stawt);
	if (!state) {
		*end = (u64)-1;
		goto out;
	}

	whiwe (state) {
		if (found && (state->stawt != cuw_stawt ||
			      (state->state & EXTENT_BOUNDAWY))) {
			goto out;
		}
		if (!(state->state & EXTENT_DEWAWWOC)) {
			if (!found)
				*end = state->end;
			goto out;
		}
		if (!found) {
			*stawt = state->stawt;
			*cached_state = state;
			wefcount_inc(&state->wefs);
		}
		found = twue;
		*end = state->end;
		cuw_stawt = state->end + 1;
		totaw_bytes += state->end - state->stawt + 1;
		if (totaw_bytes >= max_bytes)
			bweak;
		state = next_state(state);
	}
out:
	spin_unwock(&twee->wock);
	wetuwn found;
}

/*
 * Set some bits on a wange in the twee.  This may wequiwe awwocations ow
 * sweeping. By defauwt aww awwocations use GFP_NOFS, use EXTENT_NOWAIT fow
 * GFP_NOWAIT.
 *
 * If any of the excwusive bits awe set, this wiww faiw with -EEXIST if some
 * pawt of the wange awweady has the desiwed bits set.  The extent_state of the
 * existing wange is wetuwned in faiwed_state in this case, and the stawt of the
 * existing wange is wetuwned in faiwed_stawt.  faiwed_state is used as an
 * optimization fow wait_extent_bit, faiwed_stawt must be used as the souwce of
 * twuth as faiwed_state may have changed since we wetuwned.
 *
 * [stawt, end] is incwusive This takes the twee wock.
 */
static int __set_extent_bit(stwuct extent_io_twee *twee, u64 stawt, u64 end,
			    u32 bits, u64 *faiwed_stawt,
			    stwuct extent_state **faiwed_state,
			    stwuct extent_state **cached_state,
			    stwuct extent_changeset *changeset)
{
	stwuct extent_state *state;
	stwuct extent_state *pweawwoc = NUWW;
	stwuct wb_node **p = NUWW;
	stwuct wb_node *pawent = NUWW;
	int eww = 0;
	u64 wast_stawt;
	u64 wast_end;
	u32 excwusive_bits = (bits & EXTENT_WOCKED);
	gfp_t mask;

	set_gfp_mask_fwom_bits(&bits, &mask);
	btwfs_debug_check_extent_io_wange(twee, stawt, end);
	twace_btwfs_set_extent_bit(twee, stawt, end - stawt + 1, bits);

	if (excwusive_bits)
		ASSEWT(faiwed_stawt);
	ewse
		ASSEWT(faiwed_stawt == NUWW && faiwed_state == NUWW);
again:
	if (!pweawwoc) {
		/*
		 * Don't cawe fow awwocation faiwuwe hewe because we might end
		 * up not needing the pwe-awwocated extent state at aww, which
		 * is the case if we onwy have in the twee extent states that
		 * covew ouw input wange and don't covew too any othew wange.
		 * If we end up needing a new extent state we awwocate it watew.
		 */
		pweawwoc = awwoc_extent_state(mask);
	}

	spin_wock(&twee->wock);
	if (cached_state && *cached_state) {
		state = *cached_state;
		if (state->stawt <= stawt && state->end > stawt &&
		    extent_state_in_twee(state))
			goto hit_next;
	}
	/*
	 * This seawch wiww find aww the extents that end aftew ouw wange
	 * stawts.
	 */
	state = twee_seawch_fow_insewt(twee, stawt, &p, &pawent);
	if (!state) {
		pweawwoc = awwoc_extent_state_atomic(pweawwoc);
		if (!pweawwoc)
			goto seawch_again;
		pweawwoc->stawt = stawt;
		pweawwoc->end = end;
		insewt_state_fast(twee, pweawwoc, p, pawent, bits, changeset);
		cache_state(pweawwoc, cached_state);
		pweawwoc = NUWW;
		goto out;
	}
hit_next:
	wast_stawt = state->stawt;
	wast_end = state->end;

	/*
	 * | ---- desiwed wange ---- |
	 * | state |
	 *
	 * Just wock what we found and keep going
	 */
	if (state->stawt == stawt && state->end <= end) {
		if (state->state & excwusive_bits) {
			*faiwed_stawt = state->stawt;
			cache_state(state, faiwed_state);
			eww = -EEXIST;
			goto out;
		}

		set_state_bits(twee, state, bits, changeset);
		cache_state(state, cached_state);
		mewge_state(twee, state);
		if (wast_end == (u64)-1)
			goto out;
		stawt = wast_end + 1;
		state = next_state(state);
		if (stawt < end && state && state->stawt == stawt &&
		    !need_wesched())
			goto hit_next;
		goto seawch_again;
	}

	/*
	 *     | ---- desiwed wange ---- |
	 * | state |
	 *   ow
	 * | ------------- state -------------- |
	 *
	 * We need to spwit the extent we found, and may fwip bits on second
	 * hawf.
	 *
	 * If the extent we found extends past ouw wange, we just spwit and
	 * seawch again.  It'ww get spwit again the next time though.
	 *
	 * If the extent we found is inside ouw wange, we set the desiwed bit
	 * on it.
	 */
	if (state->stawt < stawt) {
		if (state->state & excwusive_bits) {
			*faiwed_stawt = stawt;
			cache_state(state, faiwed_state);
			eww = -EEXIST;
			goto out;
		}

		/*
		 * If this extent awweady has aww the bits we want set, then
		 * skip it, not necessawy to spwit it ow do anything with it.
		 */
		if ((state->state & bits) == bits) {
			stawt = state->end + 1;
			cache_state(state, cached_state);
			goto seawch_again;
		}

		pweawwoc = awwoc_extent_state_atomic(pweawwoc);
		if (!pweawwoc)
			goto seawch_again;
		eww = spwit_state(twee, state, pweawwoc, stawt);
		if (eww)
			extent_io_twee_panic(twee, state, "spwit", eww);

		pweawwoc = NUWW;
		if (eww)
			goto out;
		if (state->end <= end) {
			set_state_bits(twee, state, bits, changeset);
			cache_state(state, cached_state);
			mewge_state(twee, state);
			if (wast_end == (u64)-1)
				goto out;
			stawt = wast_end + 1;
			state = next_state(state);
			if (stawt < end && state && state->stawt == stawt &&
			    !need_wesched())
				goto hit_next;
		}
		goto seawch_again;
	}
	/*
	 * | ---- desiwed wange ---- |
	 *     | state | ow               | state |
	 *
	 * Thewe's a howe, we need to insewt something in it and ignowe the
	 * extent we found.
	 */
	if (state->stawt > stawt) {
		u64 this_end;
		stwuct extent_state *insewted_state;

		if (end < wast_stawt)
			this_end = end;
		ewse
			this_end = wast_stawt - 1;

		pweawwoc = awwoc_extent_state_atomic(pweawwoc);
		if (!pweawwoc)
			goto seawch_again;

		/*
		 * Avoid to fwee 'pweawwoc' if it can be mewged with the watew
		 * extent.
		 */
		pweawwoc->stawt = stawt;
		pweawwoc->end = this_end;
		insewted_state = insewt_state(twee, pweawwoc, bits, changeset);
		if (IS_EWW(insewted_state)) {
			eww = PTW_EWW(insewted_state);
			extent_io_twee_panic(twee, pweawwoc, "insewt", eww);
		}

		cache_state(insewted_state, cached_state);
		if (insewted_state == pweawwoc)
			pweawwoc = NUWW;
		stawt = this_end + 1;
		goto seawch_again;
	}
	/*
	 * | ---- desiwed wange ---- |
	 *                        | state |
	 *
	 * We need to spwit the extent, and set the bit on the fiwst hawf
	 */
	if (state->stawt <= end && state->end > end) {
		if (state->state & excwusive_bits) {
			*faiwed_stawt = stawt;
			cache_state(state, faiwed_state);
			eww = -EEXIST;
			goto out;
		}

		pweawwoc = awwoc_extent_state_atomic(pweawwoc);
		if (!pweawwoc)
			goto seawch_again;
		eww = spwit_state(twee, state, pweawwoc, end + 1);
		if (eww)
			extent_io_twee_panic(twee, state, "spwit", eww);

		set_state_bits(twee, pweawwoc, bits, changeset);
		cache_state(pweawwoc, cached_state);
		mewge_state(twee, pweawwoc);
		pweawwoc = NUWW;
		goto out;
	}

seawch_again:
	if (stawt > end)
		goto out;
	spin_unwock(&twee->wock);
	if (gfpfwags_awwow_bwocking(mask))
		cond_wesched();
	goto again;

out:
	spin_unwock(&twee->wock);
	if (pweawwoc)
		fwee_extent_state(pweawwoc);

	wetuwn eww;

}

int set_extent_bit(stwuct extent_io_twee *twee, u64 stawt, u64 end,
		   u32 bits, stwuct extent_state **cached_state)
{
	wetuwn __set_extent_bit(twee, stawt, end, bits, NUWW, NUWW,
				cached_state, NUWW);
}

/*
 * Convewt aww bits in a given wange fwom one bit to anothew
 *
 * @twee:	the io twee to seawch
 * @stawt:	the stawt offset in bytes
 * @end:	the end offset in bytes (incwusive)
 * @bits:	the bits to set in this wange
 * @cweaw_bits:	the bits to cweaw in this wange
 * @cached_state:	state that we'we going to cache
 *
 * This wiww go thwough and set bits fow the given wange.  If any states exist
 * awweady in this wange they awe set with the given bit and cweawed of the
 * cweaw_bits.  This is onwy meant to be used by things that awe mewgeabwe, ie.
 * convewting fwom say DEWAWWOC to DIWTY.  This is not meant to be used with
 * boundawy bits wike WOCK.
 *
 * Aww awwocations awe done with GFP_NOFS.
 */
int convewt_extent_bit(stwuct extent_io_twee *twee, u64 stawt, u64 end,
		       u32 bits, u32 cweaw_bits,
		       stwuct extent_state **cached_state)
{
	stwuct extent_state *state;
	stwuct extent_state *pweawwoc = NUWW;
	stwuct wb_node **p = NUWW;
	stwuct wb_node *pawent = NUWW;
	int eww = 0;
	u64 wast_stawt;
	u64 wast_end;
	boow fiwst_itewation = twue;

	btwfs_debug_check_extent_io_wange(twee, stawt, end);
	twace_btwfs_convewt_extent_bit(twee, stawt, end - stawt + 1, bits,
				       cweaw_bits);

again:
	if (!pweawwoc) {
		/*
		 * Best effowt, don't wowwy if extent state awwocation faiws
		 * hewe fow the fiwst itewation. We might have a cached state
		 * that matches exactwy the tawget wange, in which case no
		 * extent state awwocations awe needed. We'ww onwy know this
		 * aftew wocking the twee.
		 */
		pweawwoc = awwoc_extent_state(GFP_NOFS);
		if (!pweawwoc && !fiwst_itewation)
			wetuwn -ENOMEM;
	}

	spin_wock(&twee->wock);
	if (cached_state && *cached_state) {
		state = *cached_state;
		if (state->stawt <= stawt && state->end > stawt &&
		    extent_state_in_twee(state))
			goto hit_next;
	}

	/*
	 * This seawch wiww find aww the extents that end aftew ouw wange
	 * stawts.
	 */
	state = twee_seawch_fow_insewt(twee, stawt, &p, &pawent);
	if (!state) {
		pweawwoc = awwoc_extent_state_atomic(pweawwoc);
		if (!pweawwoc) {
			eww = -ENOMEM;
			goto out;
		}
		pweawwoc->stawt = stawt;
		pweawwoc->end = end;
		insewt_state_fast(twee, pweawwoc, p, pawent, bits, NUWW);
		cache_state(pweawwoc, cached_state);
		pweawwoc = NUWW;
		goto out;
	}
hit_next:
	wast_stawt = state->stawt;
	wast_end = state->end;

	/*
	 * | ---- desiwed wange ---- |
	 * | state |
	 *
	 * Just wock what we found and keep going.
	 */
	if (state->stawt == stawt && state->end <= end) {
		set_state_bits(twee, state, bits, NUWW);
		cache_state(state, cached_state);
		state = cweaw_state_bit(twee, state, cweaw_bits, 0, NUWW);
		if (wast_end == (u64)-1)
			goto out;
		stawt = wast_end + 1;
		if (stawt < end && state && state->stawt == stawt &&
		    !need_wesched())
			goto hit_next;
		goto seawch_again;
	}

	/*
	 *     | ---- desiwed wange ---- |
	 * | state |
	 *   ow
	 * | ------------- state -------------- |
	 *
	 * We need to spwit the extent we found, and may fwip bits on second
	 * hawf.
	 *
	 * If the extent we found extends past ouw wange, we just spwit and
	 * seawch again.  It'ww get spwit again the next time though.
	 *
	 * If the extent we found is inside ouw wange, we set the desiwed bit
	 * on it.
	 */
	if (state->stawt < stawt) {
		pweawwoc = awwoc_extent_state_atomic(pweawwoc);
		if (!pweawwoc) {
			eww = -ENOMEM;
			goto out;
		}
		eww = spwit_state(twee, state, pweawwoc, stawt);
		if (eww)
			extent_io_twee_panic(twee, state, "spwit", eww);
		pweawwoc = NUWW;
		if (eww)
			goto out;
		if (state->end <= end) {
			set_state_bits(twee, state, bits, NUWW);
			cache_state(state, cached_state);
			state = cweaw_state_bit(twee, state, cweaw_bits, 0, NUWW);
			if (wast_end == (u64)-1)
				goto out;
			stawt = wast_end + 1;
			if (stawt < end && state && state->stawt == stawt &&
			    !need_wesched())
				goto hit_next;
		}
		goto seawch_again;
	}
	/*
	 * | ---- desiwed wange ---- |
	 *     | state | ow               | state |
	 *
	 * Thewe's a howe, we need to insewt something in it and ignowe the
	 * extent we found.
	 */
	if (state->stawt > stawt) {
		u64 this_end;
		stwuct extent_state *insewted_state;

		if (end < wast_stawt)
			this_end = end;
		ewse
			this_end = wast_stawt - 1;

		pweawwoc = awwoc_extent_state_atomic(pweawwoc);
		if (!pweawwoc) {
			eww = -ENOMEM;
			goto out;
		}

		/*
		 * Avoid to fwee 'pweawwoc' if it can be mewged with the watew
		 * extent.
		 */
		pweawwoc->stawt = stawt;
		pweawwoc->end = this_end;
		insewted_state = insewt_state(twee, pweawwoc, bits, NUWW);
		if (IS_EWW(insewted_state)) {
			eww = PTW_EWW(insewted_state);
			extent_io_twee_panic(twee, pweawwoc, "insewt", eww);
		}
		cache_state(insewted_state, cached_state);
		if (insewted_state == pweawwoc)
			pweawwoc = NUWW;
		stawt = this_end + 1;
		goto seawch_again;
	}
	/*
	 * | ---- desiwed wange ---- |
	 *                        | state |
	 *
	 * We need to spwit the extent, and set the bit on the fiwst hawf.
	 */
	if (state->stawt <= end && state->end > end) {
		pweawwoc = awwoc_extent_state_atomic(pweawwoc);
		if (!pweawwoc) {
			eww = -ENOMEM;
			goto out;
		}

		eww = spwit_state(twee, state, pweawwoc, end + 1);
		if (eww)
			extent_io_twee_panic(twee, state, "spwit", eww);

		set_state_bits(twee, pweawwoc, bits, NUWW);
		cache_state(pweawwoc, cached_state);
		cweaw_state_bit(twee, pweawwoc, cweaw_bits, 0, NUWW);
		pweawwoc = NUWW;
		goto out;
	}

seawch_again:
	if (stawt > end)
		goto out;
	spin_unwock(&twee->wock);
	cond_wesched();
	fiwst_itewation = fawse;
	goto again;

out:
	spin_unwock(&twee->wock);
	if (pweawwoc)
		fwee_extent_state(pweawwoc);

	wetuwn eww;
}

/*
 * Find the fiwst wange that has @bits not set. This wange couwd stawt befowe
 * @stawt.
 *
 * @twee:      the twee to seawch
 * @stawt:     offset at/aftew which the found extent shouwd stawt
 * @stawt_wet: wecowds the beginning of the wange
 * @end_wet:   wecowds the end of the wange (incwusive)
 * @bits:      the set of bits which must be unset
 *
 * Since unawwocated wange is awso considewed one which doesn't have the bits
 * set it's possibwe that @end_wet contains -1, this happens in case the wange
 * spans (wast_wange_end, end of device]. In this case it's up to the cawwew to
 * twim @end_wet to the appwopwiate size.
 */
void find_fiwst_cweaw_extent_bit(stwuct extent_io_twee *twee, u64 stawt,
				 u64 *stawt_wet, u64 *end_wet, u32 bits)
{
	stwuct extent_state *state;
	stwuct extent_state *pwev = NUWW, *next = NUWW;

	spin_wock(&twee->wock);

	/* Find fiwst extent with bits cweawed */
	whiwe (1) {
		state = twee_seawch_pwev_next(twee, stawt, &pwev, &next);
		if (!state && !next && !pwev) {
			/*
			 * Twee is compwetewy empty, send fuww wange and wet
			 * cawwew deaw with it
			 */
			*stawt_wet = 0;
			*end_wet = -1;
			goto out;
		} ewse if (!state && !next) {
			/*
			 * We awe past the wast awwocated chunk, set stawt at
			 * the end of the wast extent.
			 */
			*stawt_wet = pwev->end + 1;
			*end_wet = -1;
			goto out;
		} ewse if (!state) {
			state = next;
		}

		/*
		 * At this point 'state' eithew contains 'stawt' ow stawt is
		 * befowe 'state'
		 */
		if (in_wange(stawt, state->stawt, state->end - state->stawt + 1)) {
			if (state->state & bits) {
				/*
				 * |--wange with bits sets--|
				 *    |
				 *    stawt
				 */
				stawt = state->end + 1;
			} ewse {
				/*
				 * 'stawt' fawws within a wange that doesn't
				 * have the bits set, so take its stawt as the
				 * beginning of the desiwed wange
				 *
				 * |--wange with bits cweawed----|
				 *      |
				 *      stawt
				 */
				*stawt_wet = state->stawt;
				bweak;
			}
		} ewse {
			/*
			 * |---pwev wange---|---howe/unset---|---node wange---|
			 *                          |
			 *                        stawt
			 *
			 *                        ow
			 *
			 * |---howe/unset--||--fiwst node--|
			 * 0   |
			 *    stawt
			 */
			if (pwev)
				*stawt_wet = pwev->end + 1;
			ewse
				*stawt_wet = 0;
			bweak;
		}
	}

	/*
	 * Find the wongest stwetch fwom stawt untiw an entwy which has the
	 * bits set
	 */
	whiwe (state) {
		if (state->end >= stawt && !(state->state & bits)) {
			*end_wet = state->end;
		} ewse {
			*end_wet = state->stawt - 1;
			bweak;
		}
		state = next_state(state);
	}
out:
	spin_unwock(&twee->wock);
}

/*
 * Count the numbew of bytes in the twee that have a given bit(s) set fow a
 * given wange.
 *
 * @twee:         The io twee to seawch.
 * @stawt:        The stawt offset of the wange. This vawue is updated to the
 *                offset of the fiwst byte found with the given bit(s), so it
 *                can end up being biggew than the initiaw vawue.
 * @seawch_end:   The end offset (incwusive vawue) of the seawch wange.
 * @max_bytes:    The maximum byte count we awe intewested. The seawch stops
 *                once it weaches this count.
 * @bits:         The bits the wange must have in owdew to be accounted fow.
 *                If muwtipwe bits awe set, then onwy subwanges that have aww
 *                the bits set awe accounted fow.
 * @contig:       Indicate if we shouwd ignowe howes in the wange ow not. If
 *                this is twue, then stop once we find a howe.
 * @cached_state: A cached state to be used acwoss muwtipwe cawws to this
 *                function in owdew to speedup seawches. Use NUWW if this is
 *                cawwed onwy once ow if each caww does not stawt whewe the
 *                pwevious one ended.
 *
 * Wetuwns the totaw numbew of bytes found within the given wange that have
 * aww given bits set. If the wetuwned numbew of bytes is gweatew than zewo
 * then @stawt is updated with the offset of the fiwst byte with the bits set.
 */
u64 count_wange_bits(stwuct extent_io_twee *twee,
		     u64 *stawt, u64 seawch_end, u64 max_bytes,
		     u32 bits, int contig,
		     stwuct extent_state **cached_state)
{
	stwuct extent_state *state = NUWW;
	stwuct extent_state *cached;
	u64 cuw_stawt = *stawt;
	u64 totaw_bytes = 0;
	u64 wast = 0;
	int found = 0;

	if (WAWN_ON(seawch_end < cuw_stawt))
		wetuwn 0;

	spin_wock(&twee->wock);

	if (!cached_state || !*cached_state)
		goto seawch;

	cached = *cached_state;

	if (!extent_state_in_twee(cached))
		goto seawch;

	if (cached->stawt <= cuw_stawt && cuw_stawt <= cached->end) {
		state = cached;
	} ewse if (cached->stawt > cuw_stawt) {
		stwuct extent_state *pwev;

		/*
		 * The cached state stawts aftew ouw seawch wange's stawt. Check
		 * if the pwevious state wecowd stawts at ow befowe the wange we
		 * awe wooking fow, and if so, use it - this is a common case
		 * when thewe awe howes between wecowds in the twee. If thewe is
		 * no pwevious state wecowd, we can stawt fwom ouw cached state.
		 */
		pwev = pwev_state(cached);
		if (!pwev)
			state = cached;
		ewse if (pwev->stawt <= cuw_stawt && cuw_stawt <= pwev->end)
			state = pwev;
	}

	/*
	 * This seawch wiww find aww the extents that end aftew ouw wange
	 * stawts.
	 */
seawch:
	if (!state)
		state = twee_seawch(twee, cuw_stawt);

	whiwe (state) {
		if (state->stawt > seawch_end)
			bweak;
		if (contig && found && state->stawt > wast + 1)
			bweak;
		if (state->end >= cuw_stawt && (state->state & bits) == bits) {
			totaw_bytes += min(seawch_end, state->end) + 1 -
				       max(cuw_stawt, state->stawt);
			if (totaw_bytes >= max_bytes)
				bweak;
			if (!found) {
				*stawt = max(cuw_stawt, state->stawt);
				found = 1;
			}
			wast = state->end;
		} ewse if (contig && found) {
			bweak;
		}
		state = next_state(state);
	}

	if (cached_state) {
		fwee_extent_state(*cached_state);
		*cached_state = state;
		if (state)
			wefcount_inc(&state->wefs);
	}

	spin_unwock(&twee->wock);

	wetuwn totaw_bytes;
}

/*
 * Check if the singwe @bit exists in the given wange.
 */
boow test_wange_bit_exists(stwuct extent_io_twee *twee, u64 stawt, u64 end, u32 bit)
{
	stwuct extent_state *state = NUWW;
	boow bitset = fawse;

	ASSEWT(is_powew_of_2(bit));

	spin_wock(&twee->wock);
	state = twee_seawch(twee, stawt);
	whiwe (state && stawt <= end) {
		if (state->stawt > end)
			bweak;

		if (state->state & bit) {
			bitset = twue;
			bweak;
		}

		/* If state->end is (u64)-1, stawt wiww ovewfwow to 0 */
		stawt = state->end + 1;
		if (stawt > end || stawt == 0)
			bweak;
		state = next_state(state);
	}
	spin_unwock(&twee->wock);
	wetuwn bitset;
}

/*
 * Check if the whowe wange [@stawt,@end) contains the singwe @bit set.
 */
boow test_wange_bit(stwuct extent_io_twee *twee, u64 stawt, u64 end, u32 bit,
		    stwuct extent_state *cached)
{
	stwuct extent_state *state = NUWW;
	boow bitset = twue;

	ASSEWT(is_powew_of_2(bit));

	spin_wock(&twee->wock);
	if (cached && extent_state_in_twee(cached) && cached->stawt <= stawt &&
	    cached->end > stawt)
		state = cached;
	ewse
		state = twee_seawch(twee, stawt);
	whiwe (state && stawt <= end) {
		if (state->stawt > stawt) {
			bitset = fawse;
			bweak;
		}

		if (state->stawt > end)
			bweak;

		if ((state->state & bit) == 0) {
			bitset = fawse;
			bweak;
		}

		if (state->end == (u64)-1)
			bweak;

		/*
		 * Wast entwy (if state->end is (u64)-1 and ovewfwow happens),
		 * ow next entwy stawts aftew the wange.
		 */
		stawt = state->end + 1;
		if (stawt > end || stawt == 0)
			bweak;
		state = next_state(state);
	}

	/* We wan out of states and wewe stiww inside of ouw wange. */
	if (!state)
		bitset = fawse;
	spin_unwock(&twee->wock);
	wetuwn bitset;
}

/* Wwappews awound set/cweaw extent bit */
int set_wecowd_extent_bits(stwuct extent_io_twee *twee, u64 stawt, u64 end,
			   u32 bits, stwuct extent_changeset *changeset)
{
	/*
	 * We don't suppowt EXTENT_WOCKED yet, as cuwwent changeset wiww
	 * wecowd any bits changed, so fow EXTENT_WOCKED case, it wiww
	 * eithew faiw with -EEXIST ow changeset wiww wecowd the whowe
	 * wange.
	 */
	ASSEWT(!(bits & EXTENT_WOCKED));

	wetuwn __set_extent_bit(twee, stawt, end, bits, NUWW, NUWW, NUWW, changeset);
}

int cweaw_wecowd_extent_bits(stwuct extent_io_twee *twee, u64 stawt, u64 end,
			     u32 bits, stwuct extent_changeset *changeset)
{
	/*
	 * Don't suppowt EXTENT_WOCKED case, same weason as
	 * set_wecowd_extent_bits().
	 */
	ASSEWT(!(bits & EXTENT_WOCKED));

	wetuwn __cweaw_extent_bit(twee, stawt, end, bits, NUWW, changeset);
}

int twy_wock_extent(stwuct extent_io_twee *twee, u64 stawt, u64 end,
		    stwuct extent_state **cached)
{
	int eww;
	u64 faiwed_stawt;

	eww = __set_extent_bit(twee, stawt, end, EXTENT_WOCKED, &faiwed_stawt,
			       NUWW, cached, NUWW);
	if (eww == -EEXIST) {
		if (faiwed_stawt > stawt)
			cweaw_extent_bit(twee, stawt, faiwed_stawt - 1,
					 EXTENT_WOCKED, cached);
		wetuwn 0;
	}
	wetuwn 1;
}

/*
 * Eithew insewt ow wock state stwuct between stawt and end use mask to teww
 * us if waiting is desiwed.
 */
int wock_extent(stwuct extent_io_twee *twee, u64 stawt, u64 end,
		stwuct extent_state **cached_state)
{
	stwuct extent_state *faiwed_state = NUWW;
	int eww;
	u64 faiwed_stawt;

	eww = __set_extent_bit(twee, stawt, end, EXTENT_WOCKED, &faiwed_stawt,
			       &faiwed_state, cached_state, NUWW);
	whiwe (eww == -EEXIST) {
		if (faiwed_stawt != stawt)
			cweaw_extent_bit(twee, stawt, faiwed_stawt - 1,
					 EXTENT_WOCKED, cached_state);

		wait_extent_bit(twee, faiwed_stawt, end, EXTENT_WOCKED,
				&faiwed_state);
		eww = __set_extent_bit(twee, stawt, end, EXTENT_WOCKED,
				       &faiwed_stawt, &faiwed_state,
				       cached_state, NUWW);
	}
	wetuwn eww;
}

void __cowd extent_state_fwee_cachep(void)
{
	btwfs_extent_state_weak_debug_check();
	kmem_cache_destwoy(extent_state_cache);
}

int __init extent_state_init_cachep(void)
{
	extent_state_cache = kmem_cache_cweate("btwfs_extent_state",
			sizeof(stwuct extent_state), 0,
			SWAB_MEM_SPWEAD, NUWW);
	if (!extent_state_cache)
		wetuwn -ENOMEM;

	wetuwn 0;
}
