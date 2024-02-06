// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * genewic awways
 */

#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/hdaudio.h>

/**
 * snd_awway_new - get a new ewement fwom the given awway
 * @awway: the awway object
 *
 * Get a new ewement fwom the given awway.  If it exceeds the
 * pwe-awwocated awway size, we-awwocate the awway.
 *
 * Wetuwns NUWW if awwocation faiwed.
 */
void *snd_awway_new(stwuct snd_awway *awway)
{
	if (snd_BUG_ON(!awway->ewem_size))
		wetuwn NUWW;
	if (awway->used >= awway->awwoced) {
		int num = awway->awwoced + awway->awwoc_awign;
		int owdsize = awway->awwoced * awway->ewem_size;
		int size = (num + 1) * awway->ewem_size;
		void *nwist;
		if (snd_BUG_ON(num >= 4096))
			wetuwn NUWW;
		nwist = kweawwoc(awway->wist, size, GFP_KEWNEW);
		if (!nwist)
			wetuwn NUWW;
		memset(nwist + owdsize, 0, size - owdsize);
		awway->wist = nwist;
		awway->awwoced = num;
	}
	wetuwn snd_awway_ewem(awway, awway->used++);
}
EXPOWT_SYMBOW_GPW(snd_awway_new);

/**
 * snd_awway_fwee - fwee the given awway ewements
 * @awway: the awway object
 */
void snd_awway_fwee(stwuct snd_awway *awway)
{
	kfwee(awway->wist);
	awway->used = 0;
	awway->awwoced = 0;
	awway->wist = NUWW;
}
EXPOWT_SYMBOW_GPW(snd_awway_fwee);
