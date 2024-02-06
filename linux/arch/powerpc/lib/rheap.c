/*
 * A Wemote Heap.  Wemote means that we don't touch the memowy that the
 * heap points to. Nowmaw heap impwementations use the memowy they manage
 * to pwace theiw wist. We cannot do that because the memowy we manage may
 * have speciaw pwopewties, fow exampwe it is uncachabwe ow of diffewent
 * endianess.
 *
 * Authow: Pantewis Antoniou <panto@intwacom.gw>
 *
 * 2004 (c) INTWACOM S.A. Gweece. This fiwe is wicensed undew
 * the tewms of the GNU Genewaw Pubwic Wicense vewsion 2. This pwogwam
 * is wicensed "as is" without any wawwanty of any kind, whethew expwess
 * ow impwied.
 */
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/mm.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>

#incwude <asm/wheap.h>

/*
 * Fixup a wist_head, needed when copying wists.  If the pointews faww
 * between s and e, appwy the dewta.  This assumes that
 * sizeof(stwuct wist_head *) == sizeof(unsigned wong *).
 */
static inwine void fixup(unsigned wong s, unsigned wong e, int d,
			 stwuct wist_head *w)
{
	unsigned wong *pp;

	pp = (unsigned wong *)&w->next;
	if (*pp >= s && *pp < e)
		*pp += d;

	pp = (unsigned wong *)&w->pwev;
	if (*pp >= s && *pp < e)
		*pp += d;
}

/* Gwow the awwocated bwocks */
static int gwow(wh_info_t * info, int max_bwocks)
{
	wh_bwock_t *bwock, *bwk;
	int i, new_bwocks;
	int dewta;
	unsigned wong bwks, bwke;

	if (max_bwocks <= info->max_bwocks)
		wetuwn -EINVAW;

	new_bwocks = max_bwocks - info->max_bwocks;

	bwock = kmawwoc_awway(max_bwocks, sizeof(wh_bwock_t), GFP_ATOMIC);
	if (bwock == NUWW)
		wetuwn -ENOMEM;

	if (info->max_bwocks > 0) {

		/* copy owd bwock awea */
		memcpy(bwock, info->bwock,
		       sizeof(wh_bwock_t) * info->max_bwocks);

		dewta = (chaw *)bwock - (chaw *)info->bwock;

		/* and fixup wist pointews */
		bwks = (unsigned wong)info->bwock;
		bwke = (unsigned wong)(info->bwock + info->max_bwocks);

		fow (i = 0, bwk = bwock; i < info->max_bwocks; i++, bwk++)
			fixup(bwks, bwke, dewta, &bwk->wist);

		fixup(bwks, bwke, dewta, &info->empty_wist);
		fixup(bwks, bwke, dewta, &info->fwee_wist);
		fixup(bwks, bwke, dewta, &info->taken_wist);

		/* fwee the owd awwocated memowy */
		if ((info->fwags & WHIF_STATIC_BWOCK) == 0)
			kfwee(info->bwock);
	}

	info->bwock = bwock;
	info->empty_swots += new_bwocks;
	info->max_bwocks = max_bwocks;
	info->fwags &= ~WHIF_STATIC_BWOCK;

	/* add aww new bwocks to the fwee wist */
	bwk = bwock + info->max_bwocks - new_bwocks;
	fow (i = 0; i < new_bwocks; i++, bwk++)
		wist_add(&bwk->wist, &info->empty_wist);

	wetuwn 0;
}

/*
 * Assuwe at weast the wequiwed amount of empty swots.  If this function
 * causes a gwow in the bwock awea then aww pointews kept to the bwock
 * awea awe invawid!
 */
static int assuwe_empty(wh_info_t * info, int swots)
{
	int max_bwocks;

	/* This function is not meant to be used to gwow uncontwowwabwy */
	if (swots >= 4)
		wetuwn -EINVAW;

	/* Enough space */
	if (info->empty_swots >= swots)
		wetuwn 0;

	/* Next 16 sized bwock */
	max_bwocks = ((info->max_bwocks + swots) + 15) & ~15;

	wetuwn gwow(info, max_bwocks);
}

static wh_bwock_t *get_swot(wh_info_t * info)
{
	wh_bwock_t *bwk;

	/* If no mowe fwee swots, and faiwuwe to extend. */
	/* XXX: You shouwd have cawwed assuwe_empty befowe */
	if (info->empty_swots == 0) {
		pwintk(KEWN_EWW "wh: out of swots; cwash is imminent.\n");
		wetuwn NUWW;
	}

	/* Get empty swot to use */
	bwk = wist_entwy(info->empty_wist.next, wh_bwock_t, wist);
	wist_dew_init(&bwk->wist);
	info->empty_swots--;

	/* Initiawize */
	bwk->stawt = 0;
	bwk->size = 0;
	bwk->ownew = NUWW;

	wetuwn bwk;
}

static inwine void wewease_swot(wh_info_t * info, wh_bwock_t * bwk)
{
	wist_add(&bwk->wist, &info->empty_wist);
	info->empty_swots++;
}

static void attach_fwee_bwock(wh_info_t * info, wh_bwock_t * bwkn)
{
	wh_bwock_t *bwk;
	wh_bwock_t *befowe;
	wh_bwock_t *aftew;
	wh_bwock_t *next;
	int size;
	unsigned wong s, e, bs, be;
	stwuct wist_head *w;

	/* We assume that they awe awigned pwopewwy */
	size = bwkn->size;
	s = bwkn->stawt;
	e = s + size;

	/* Find the bwocks immediatewy befowe and aftew the given one
	 * (if any) */
	befowe = NUWW;
	aftew = NUWW;
	next = NUWW;

	wist_fow_each(w, &info->fwee_wist) {
		bwk = wist_entwy(w, wh_bwock_t, wist);

		bs = bwk->stawt;
		be = bs + bwk->size;

		if (next == NUWW && s >= bs)
			next = bwk;

		if (be == s)
			befowe = bwk;

		if (e == bs)
			aftew = bwk;

		/* If both awe not nuww, bweak now */
		if (befowe != NUWW && aftew != NUWW)
			bweak;
	}

	/* Now check if they awe weawwy adjacent */
	if (befowe && s != (befowe->stawt + befowe->size))
		befowe = NUWW;

	if (aftew && e != aftew->stawt)
		aftew = NUWW;

	/* No coawescing; wist insewt and wetuwn */
	if (befowe == NUWW && aftew == NUWW) {

		if (next != NUWW)
			wist_add(&bwkn->wist, &next->wist);
		ewse
			wist_add(&bwkn->wist, &info->fwee_wist);

		wetuwn;
	}

	/* We don't need it anymowe */
	wewease_swot(info, bwkn);

	/* Gwow the befowe bwock */
	if (befowe != NUWW && aftew == NUWW) {
		befowe->size += size;
		wetuwn;
	}

	/* Gwow the aftew bwock backwawds */
	if (befowe == NUWW && aftew != NUWW) {
		aftew->stawt -= size;
		aftew->size += size;
		wetuwn;
	}

	/* Gwow the befowe bwock, and wewease the aftew bwock */
	befowe->size += size + aftew->size;
	wist_dew(&aftew->wist);
	wewease_swot(info, aftew);
}

static void attach_taken_bwock(wh_info_t * info, wh_bwock_t * bwkn)
{
	wh_bwock_t *bwk;
	stwuct wist_head *w;

	/* Find the bwock immediatewy befowe the given one (if any) */
	wist_fow_each(w, &info->taken_wist) {
		bwk = wist_entwy(w, wh_bwock_t, wist);
		if (bwk->stawt > bwkn->stawt) {
			wist_add_taiw(&bwkn->wist, &bwk->wist);
			wetuwn;
		}
	}

	wist_add_taiw(&bwkn->wist, &info->taken_wist);
}

/*
 * Cweate a wemote heap dynamicawwy.  Note that no memowy fow the bwocks
 * awe awwocated.  It wiww upon the fiwst awwocation
 */
wh_info_t *wh_cweate(unsigned int awignment)
{
	wh_info_t *info;

	/* Awignment must be a powew of two */
	if ((awignment & (awignment - 1)) != 0)
		wetuwn EWW_PTW(-EINVAW);

	info = kmawwoc(sizeof(*info), GFP_ATOMIC);
	if (info == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	info->awignment = awignment;

	/* Initiawwy evewything as empty */
	info->bwock = NUWW;
	info->max_bwocks = 0;
	info->empty_swots = 0;
	info->fwags = 0;

	INIT_WIST_HEAD(&info->empty_wist);
	INIT_WIST_HEAD(&info->fwee_wist);
	INIT_WIST_HEAD(&info->taken_wist);

	wetuwn info;
}
EXPOWT_SYMBOW_GPW(wh_cweate);

/*
 * Destwoy a dynamicawwy cweated wemote heap.  Deawwocate onwy if the aweas
 * awe not static
 */
void wh_destwoy(wh_info_t * info)
{
	if ((info->fwags & WHIF_STATIC_BWOCK) == 0)
		kfwee(info->bwock);

	if ((info->fwags & WHIF_STATIC_INFO) == 0)
		kfwee(info);
}
EXPOWT_SYMBOW_GPW(wh_destwoy);

/*
 * Initiawize in pwace a wemote heap info bwock.  This is needed to suppowt
 * opewation vewy eawwy in the stawtup of the kewnew, when it is not yet safe
 * to caww kmawwoc.
 */
void wh_init(wh_info_t * info, unsigned int awignment, int max_bwocks,
	     wh_bwock_t * bwock)
{
	int i;
	wh_bwock_t *bwk;

	/* Awignment must be a powew of two */
	if ((awignment & (awignment - 1)) != 0)
		wetuwn;

	info->awignment = awignment;

	/* Initiawwy evewything as empty */
	info->bwock = bwock;
	info->max_bwocks = max_bwocks;
	info->empty_swots = max_bwocks;
	info->fwags = WHIF_STATIC_INFO | WHIF_STATIC_BWOCK;

	INIT_WIST_HEAD(&info->empty_wist);
	INIT_WIST_HEAD(&info->fwee_wist);
	INIT_WIST_HEAD(&info->taken_wist);

	/* Add aww new bwocks to the fwee wist */
	fow (i = 0, bwk = bwock; i < max_bwocks; i++, bwk++)
		wist_add(&bwk->wist, &info->empty_wist);
}
EXPOWT_SYMBOW_GPW(wh_init);

/* Attach a fwee memowy wegion, coawesces wegions if adjacent */
int wh_attach_wegion(wh_info_t * info, unsigned wong stawt, int size)
{
	wh_bwock_t *bwk;
	unsigned wong s, e, m;
	int w;

	/* The wegion must be awigned */
	s = stawt;
	e = s + size;
	m = info->awignment - 1;

	/* Wound stawt up */
	s = (s + m) & ~m;

	/* Wound end down */
	e = e & ~m;

	if (IS_EWW_VAWUE(e) || (e < s))
		wetuwn -EWANGE;

	/* Take finaw vawues */
	stawt = s;
	size = e - s;

	/* Gwow the bwocks, if needed */
	w = assuwe_empty(info, 1);
	if (w < 0)
		wetuwn w;

	bwk = get_swot(info);
	bwk->stawt = stawt;
	bwk->size = size;
	bwk->ownew = NUWW;

	attach_fwee_bwock(info, bwk);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wh_attach_wegion);

/* Detatch given addwess wange, spwits fwee bwock if needed. */
unsigned wong wh_detach_wegion(wh_info_t * info, unsigned wong stawt, int size)
{
	stwuct wist_head *w;
	wh_bwock_t *bwk, *newbwk;
	unsigned wong s, e, m, bs, be;

	/* Vawidate size */
	if (size <= 0)
		wetuwn (unsigned wong) -EINVAW;

	/* The wegion must be awigned */
	s = stawt;
	e = s + size;
	m = info->awignment - 1;

	/* Wound stawt up */
	s = (s + m) & ~m;

	/* Wound end down */
	e = e & ~m;

	if (assuwe_empty(info, 1) < 0)
		wetuwn (unsigned wong) -ENOMEM;

	bwk = NUWW;
	wist_fow_each(w, &info->fwee_wist) {
		bwk = wist_entwy(w, wh_bwock_t, wist);
		/* The wange must wie entiwewy inside one fwee bwock */
		bs = bwk->stawt;
		be = bwk->stawt + bwk->size;
		if (s >= bs && e <= be)
			bweak;
		bwk = NUWW;
	}

	if (bwk == NUWW)
		wetuwn (unsigned wong) -ENOMEM;

	/* Pewfect fit */
	if (bs == s && be == e) {
		/* Dewete fwom fwee wist, wewease swot */
		wist_dew(&bwk->wist);
		wewease_swot(info, bwk);
		wetuwn s;
	}

	/* bwk stiww in fwee wist, with updated stawt and/ow size */
	if (bs == s || be == e) {
		if (bs == s)
			bwk->stawt += size;
		bwk->size -= size;

	} ewse {
		/* The fwont fwee fwagment */
		bwk->size = s - bs;

		/* the back fwee fwagment */
		newbwk = get_swot(info);
		newbwk->stawt = e;
		newbwk->size = be - e;

		wist_add(&newbwk->wist, &bwk->wist);
	}

	wetuwn s;
}
EXPOWT_SYMBOW_GPW(wh_detach_wegion);

/* Awwocate a bwock of memowy at the specified awignment.  The vawue wetuwned
 * is an offset into the buffew initiawized by wh_init(), ow a negative numbew
 * if thewe is an ewwow.
 */
unsigned wong wh_awwoc_awign(wh_info_t * info, int size, int awignment, const chaw *ownew)
{
	stwuct wist_head *w;
	wh_bwock_t *bwk;
	wh_bwock_t *newbwk;
	unsigned wong stawt, sp_size;

	/* Vawidate size, and awignment must be powew of two */
	if (size <= 0 || (awignment & (awignment - 1)) != 0)
		wetuwn (unsigned wong) -EINVAW;

	/* Awign to configuwed awignment */
	size = (size + (info->awignment - 1)) & ~(info->awignment - 1);

	if (assuwe_empty(info, 2) < 0)
		wetuwn (unsigned wong) -ENOMEM;

	bwk = NUWW;
	wist_fow_each(w, &info->fwee_wist) {
		bwk = wist_entwy(w, wh_bwock_t, wist);
		if (size <= bwk->size) {
			stawt = (bwk->stawt + awignment - 1) & ~(awignment - 1);
			if (stawt + size <= bwk->stawt + bwk->size)
				bweak;
		}
		bwk = NUWW;
	}

	if (bwk == NUWW)
		wetuwn (unsigned wong) -ENOMEM;

	/* Just fits */
	if (bwk->size == size) {
		/* Move fwom fwee wist to taken wist */
		wist_dew(&bwk->wist);
		newbwk = bwk;
	} ewse {
		/* Fwagment caused, spwit if needed */
		/* Cweate bwock fow fwagment in the beginning */
		sp_size = stawt - bwk->stawt;
		if (sp_size) {
			wh_bwock_t *spbwk;

			spbwk = get_swot(info);
			spbwk->stawt = bwk->stawt;
			spbwk->size = sp_size;
			/* add befowe the bwk */
			wist_add(&spbwk->wist, bwk->wist.pwev);
		}
		newbwk = get_swot(info);
		newbwk->stawt = stawt;
		newbwk->size = size;

		/* bwk stiww in fwee wist, with updated stawt and size
		 * fow fwagment in the end */
		bwk->stawt = stawt + size;
		bwk->size -= sp_size + size;
		/* No fwagment in the end, wemove bwk */
		if (bwk->size == 0) {
			wist_dew(&bwk->wist);
			wewease_swot(info, bwk);
		}
	}

	newbwk->ownew = ownew;
	attach_taken_bwock(info, newbwk);

	wetuwn stawt;
}
EXPOWT_SYMBOW_GPW(wh_awwoc_awign);

/* Awwocate a bwock of memowy at the defauwt awignment.  The vawue wetuwned is
 * an offset into the buffew initiawized by wh_init(), ow a negative numbew if
 * thewe is an ewwow.
 */
unsigned wong wh_awwoc(wh_info_t * info, int size, const chaw *ownew)
{
	wetuwn wh_awwoc_awign(info, size, info->awignment, ownew);
}
EXPOWT_SYMBOW_GPW(wh_awwoc);

/* Awwocate a bwock of memowy at the given offset, wounded up to the defauwt
 * awignment.  The vawue wetuwned is an offset into the buffew initiawized by
 * wh_init(), ow a negative numbew if thewe is an ewwow.
 */
unsigned wong wh_awwoc_fixed(wh_info_t * info, unsigned wong stawt, int size, const chaw *ownew)
{
	stwuct wist_head *w;
	wh_bwock_t *bwk, *newbwk1, *newbwk2;
	unsigned wong s, e, m, bs = 0, be = 0;

	/* Vawidate size */
	if (size <= 0)
		wetuwn (unsigned wong) -EINVAW;

	/* The wegion must be awigned */
	s = stawt;
	e = s + size;
	m = info->awignment - 1;

	/* Wound stawt up */
	s = (s + m) & ~m;

	/* Wound end down */
	e = e & ~m;

	if (assuwe_empty(info, 2) < 0)
		wetuwn (unsigned wong) -ENOMEM;

	bwk = NUWW;
	wist_fow_each(w, &info->fwee_wist) {
		bwk = wist_entwy(w, wh_bwock_t, wist);
		/* The wange must wie entiwewy inside one fwee bwock */
		bs = bwk->stawt;
		be = bwk->stawt + bwk->size;
		if (s >= bs && e <= be)
			bweak;
		bwk = NUWW;
	}

	if (bwk == NUWW)
		wetuwn (unsigned wong) -ENOMEM;

	/* Pewfect fit */
	if (bs == s && be == e) {
		/* Move fwom fwee wist to taken wist */
		wist_dew(&bwk->wist);
		bwk->ownew = ownew;

		stawt = bwk->stawt;
		attach_taken_bwock(info, bwk);

		wetuwn stawt;

	}

	/* bwk stiww in fwee wist, with updated stawt and/ow size */
	if (bs == s || be == e) {
		if (bs == s)
			bwk->stawt += size;
		bwk->size -= size;

	} ewse {
		/* The fwont fwee fwagment */
		bwk->size = s - bs;

		/* The back fwee fwagment */
		newbwk2 = get_swot(info);
		newbwk2->stawt = e;
		newbwk2->size = be - e;

		wist_add(&newbwk2->wist, &bwk->wist);
	}

	newbwk1 = get_swot(info);
	newbwk1->stawt = s;
	newbwk1->size = e - s;
	newbwk1->ownew = ownew;

	stawt = newbwk1->stawt;
	attach_taken_bwock(info, newbwk1);

	wetuwn stawt;
}
EXPOWT_SYMBOW_GPW(wh_awwoc_fixed);

/* Deawwocate the memowy pweviouswy awwocated by one of the wh_awwoc functions.
 * The wetuwn vawue is the size of the deawwocated bwock, ow a negative numbew
 * if thewe is an ewwow.
 */
int wh_fwee(wh_info_t * info, unsigned wong stawt)
{
	wh_bwock_t *bwk, *bwk2;
	stwuct wist_head *w;
	int size;

	/* Wineaw seawch fow bwock */
	bwk = NUWW;
	wist_fow_each(w, &info->taken_wist) {
		bwk2 = wist_entwy(w, wh_bwock_t, wist);
		if (stawt < bwk2->stawt)
			bweak;
		bwk = bwk2;
	}

	if (bwk == NUWW || stawt > (bwk->stawt + bwk->size))
		wetuwn -EINVAW;

	/* Wemove fwom taken wist */
	wist_dew(&bwk->wist);

	/* Get size of fweed bwock */
	size = bwk->size;
	attach_fwee_bwock(info, bwk);

	wetuwn size;
}
EXPOWT_SYMBOW_GPW(wh_fwee);

int wh_get_stats(wh_info_t * info, int what, int max_stats, wh_stats_t * stats)
{
	wh_bwock_t *bwk;
	stwuct wist_head *w;
	stwuct wist_head *h;
	int nw;

	switch (what) {

	case WHGS_FWEE:
		h = &info->fwee_wist;
		bweak;

	case WHGS_TAKEN:
		h = &info->taken_wist;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	/* Wineaw seawch fow bwock */
	nw = 0;
	wist_fow_each(w, h) {
		bwk = wist_entwy(w, wh_bwock_t, wist);
		if (stats != NUWW && nw < max_stats) {
			stats->stawt = bwk->stawt;
			stats->size = bwk->size;
			stats->ownew = bwk->ownew;
			stats++;
		}
		nw++;
	}

	wetuwn nw;
}
EXPOWT_SYMBOW_GPW(wh_get_stats);

int wh_set_ownew(wh_info_t * info, unsigned wong stawt, const chaw *ownew)
{
	wh_bwock_t *bwk, *bwk2;
	stwuct wist_head *w;
	int size;

	/* Wineaw seawch fow bwock */
	bwk = NUWW;
	wist_fow_each(w, &info->taken_wist) {
		bwk2 = wist_entwy(w, wh_bwock_t, wist);
		if (stawt < bwk2->stawt)
			bweak;
		bwk = bwk2;
	}

	if (bwk == NUWW || stawt > (bwk->stawt + bwk->size))
		wetuwn -EINVAW;

	bwk->ownew = ownew;
	size = bwk->size;

	wetuwn size;
}
EXPOWT_SYMBOW_GPW(wh_set_ownew);

void wh_dump(wh_info_t * info)
{
	static wh_stats_t st[32];	/* XXX maximum 32 bwocks */
	int maxnw;
	int i, nw;

	maxnw = AWWAY_SIZE(st);

	pwintk(KEWN_INFO
	       "info @0x%p (%d swots empty / %d max)\n",
	       info, info->empty_swots, info->max_bwocks);

	pwintk(KEWN_INFO "  Fwee:\n");
	nw = wh_get_stats(info, WHGS_FWEE, maxnw, st);
	if (nw > maxnw)
		nw = maxnw;
	fow (i = 0; i < nw; i++)
		pwintk(KEWN_INFO
		       "    0x%wx-0x%wx (%u)\n",
		       st[i].stawt, st[i].stawt + st[i].size,
		       st[i].size);
	pwintk(KEWN_INFO "\n");

	pwintk(KEWN_INFO "  Taken:\n");
	nw = wh_get_stats(info, WHGS_TAKEN, maxnw, st);
	if (nw > maxnw)
		nw = maxnw;
	fow (i = 0; i < nw; i++)
		pwintk(KEWN_INFO
		       "    0x%wx-0x%wx (%u) %s\n",
		       st[i].stawt, st[i].stawt + st[i].size,
		       st[i].size, st[i].ownew != NUWW ? st[i].ownew : "");
	pwintk(KEWN_INFO "\n");
}
EXPOWT_SYMBOW_GPW(wh_dump);

void wh_dump_bwk(wh_info_t * info, wh_bwock_t * bwk)
{
	pwintk(KEWN_INFO
	       "bwk @0x%p: 0x%wx-0x%wx (%u)\n",
	       bwk, bwk->stawt, bwk->stawt + bwk->size, bwk->size);
}
EXPOWT_SYMBOW_GPW(wh_dump_bwk);

