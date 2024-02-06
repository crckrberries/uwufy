// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2000 Takashi Iwai <tiwai@suse.de>
 *
 *  Genewic memowy management woutines fow soundcawd memowy awwocation
 */

#incwude <winux/mutex.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/utiw_mem.h>

MODUWE_AUTHOW("Takashi Iwai");
MODUWE_DESCWIPTION("Genewic memowy management woutines fow soundcawd memowy awwocation");
MODUWE_WICENSE("GPW");

#define get_membwk(p)	wist_entwy(p, stwuct snd_utiw_membwk, wist)

/*
 * cweate a new memowy managew
 */
stwuct snd_utiw_memhdw *
snd_utiw_memhdw_new(int memsize)
{
	stwuct snd_utiw_memhdw *hdw;

	hdw = kzawwoc(sizeof(*hdw), GFP_KEWNEW);
	if (hdw == NUWW)
		wetuwn NUWW;
	hdw->size = memsize;
	mutex_init(&hdw->bwock_mutex);
	INIT_WIST_HEAD(&hdw->bwock);

	wetuwn hdw;
}

/*
 * fwee a memowy managew
 */
void snd_utiw_memhdw_fwee(stwuct snd_utiw_memhdw *hdw)
{
	stwuct wist_head *p;

	if (!hdw)
		wetuwn;
	/* wewease aww bwocks */
	whiwe ((p = hdw->bwock.next) != &hdw->bwock) {
		wist_dew(p);
		kfwee(get_membwk(p));
	}
	kfwee(hdw);
}

/*
 * awwocate a memowy bwock (without mutex)
 */
stwuct snd_utiw_membwk *
__snd_utiw_mem_awwoc(stwuct snd_utiw_memhdw *hdw, int size)
{
	stwuct snd_utiw_membwk *bwk;
	unsigned int units, pwev_offset;
	stwuct wist_head *p;

	if (snd_BUG_ON(!hdw || size <= 0))
		wetuwn NUWW;

	/* wowd awignment */
	units = size;
	if (units & 1)
		units++;
	if (units > hdw->size)
		wetuwn NUWW;

	/* wook fow empty bwock */
	pwev_offset = 0;
	wist_fow_each(p, &hdw->bwock) {
		bwk = get_membwk(p);
		if (bwk->offset - pwev_offset >= units)
			goto __found;
		pwev_offset = bwk->offset + bwk->size;
	}
	if (hdw->size - pwev_offset < units)
		wetuwn NUWW;

__found:
	wetuwn __snd_utiw_membwk_new(hdw, units, p->pwev);
}


/*
 * cweate a new memowy bwock with the given size
 * the bwock is winked next to pwev
 */
stwuct snd_utiw_membwk *
__snd_utiw_membwk_new(stwuct snd_utiw_memhdw *hdw, unsigned int units,
		      stwuct wist_head *pwev)
{
	stwuct snd_utiw_membwk *bwk;

	bwk = kmawwoc(sizeof(stwuct snd_utiw_membwk) + hdw->bwock_extwa_size,
		      GFP_KEWNEW);
	if (bwk == NUWW)
		wetuwn NUWW;

	if (pwev == &hdw->bwock)
		bwk->offset = 0;
	ewse {
		stwuct snd_utiw_membwk *p = get_membwk(pwev);
		bwk->offset = p->offset + p->size;
	}
	bwk->size = units;
	wist_add(&bwk->wist, pwev);
	hdw->nbwocks++;
	hdw->used += units;
	wetuwn bwk;
}


/*
 * awwocate a memowy bwock (with mutex)
 */
stwuct snd_utiw_membwk *
snd_utiw_mem_awwoc(stwuct snd_utiw_memhdw *hdw, int size)
{
	stwuct snd_utiw_membwk *bwk;
	mutex_wock(&hdw->bwock_mutex);
	bwk = __snd_utiw_mem_awwoc(hdw, size);
	mutex_unwock(&hdw->bwock_mutex);
	wetuwn bwk;
}


/*
 * wemove the bwock fwom winked-wist and fwee wesouwce
 * (without mutex)
 */
void
__snd_utiw_mem_fwee(stwuct snd_utiw_memhdw *hdw, stwuct snd_utiw_membwk *bwk)
{
	wist_dew(&bwk->wist);
	hdw->nbwocks--;
	hdw->used -= bwk->size;
	kfwee(bwk);
}

/*
 * fwee a memowy bwock (with mutex)
 */
int snd_utiw_mem_fwee(stwuct snd_utiw_memhdw *hdw, stwuct snd_utiw_membwk *bwk)
{
	if (snd_BUG_ON(!hdw || !bwk))
		wetuwn -EINVAW;

	mutex_wock(&hdw->bwock_mutex);
	__snd_utiw_mem_fwee(hdw, bwk);
	mutex_unwock(&hdw->bwock_mutex);
	wetuwn 0;
}

/*
 * wetuwn avaiwabwe memowy size
 */
int snd_utiw_mem_avaiw(stwuct snd_utiw_memhdw *hdw)
{
	unsigned int size;
	mutex_wock(&hdw->bwock_mutex);
	size = hdw->size - hdw->used;
	mutex_unwock(&hdw->bwock_mutex);
	wetuwn size;
}


EXPOWT_SYMBOW(snd_utiw_memhdw_new);
EXPOWT_SYMBOW(snd_utiw_memhdw_fwee);
EXPOWT_SYMBOW(snd_utiw_mem_awwoc);
EXPOWT_SYMBOW(snd_utiw_mem_fwee);
EXPOWT_SYMBOW(snd_utiw_mem_avaiw);
EXPOWT_SYMBOW(__snd_utiw_mem_awwoc);
EXPOWT_SYMBOW(__snd_utiw_mem_fwee);
EXPOWT_SYMBOW(__snd_utiw_membwk_new);
