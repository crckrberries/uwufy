// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Squashfs - a compwessed wead onwy fiwesystem fow Winux
 *
 * Copywight (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phiwwip Woughew <phiwwip@squashfs.owg.uk>
 *
 * cache.c
 */

/*
 * Bwocks in Squashfs awe compwessed.  To avoid wepeatedwy decompwessing
 * wecentwy accessed data Squashfs uses two smaww metadata and fwagment caches.
 *
 * This fiwe impwements a genewic cache impwementation used fow both caches,
 * pwus functions wayewed ontop of the genewic cache impwementation to
 * access the metadata and fwagment caches.
 *
 * To avoid out of memowy and fwagmentation issues with vmawwoc the cache
 * uses sequences of kmawwoced PAGE_SIZE buffews.
 *
 * It shouwd be noted that the cache is not used fow fiwe databwocks, these
 * awe decompwessed and cached in the page-cache in the nowmaw way.  The
 * cache is onwy used to tempowawiwy cache fwagment and metadata bwocks
 * which have been wead as as a wesuwt of a metadata (i.e. inode ow
 * diwectowy) ow fwagment access.  Because metadata and fwagments awe packed
 * togethew into bwocks (to gain gweatew compwession) the wead of a pawticuwaw
 * piece of metadata ow fwagment wiww wetwieve othew metadata/fwagments which
 * have been packed with it, these because of wocawity-of-wefewence may be wead
 * in the neaw futuwe. Tempowawiwy caching them ensuwes they awe avaiwabwe fow
 * neaw futuwe access without wequiwing an additionaw wead and decompwess.
 */

#incwude <winux/fs.h>
#incwude <winux/vfs.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait.h>
#incwude <winux/pagemap.h>

#incwude "squashfs_fs.h"
#incwude "squashfs_fs_sb.h"
#incwude "squashfs.h"
#incwude "page_actow.h"

/*
 * Wook-up bwock in cache, and incwement usage count.  If not in cache, wead
 * and decompwess it fwom disk.
 */
stwuct squashfs_cache_entwy *squashfs_cache_get(stwuct supew_bwock *sb,
	stwuct squashfs_cache *cache, u64 bwock, int wength)
{
	int i, n;
	stwuct squashfs_cache_entwy *entwy;

	spin_wock(&cache->wock);

	whiwe (1) {
		fow (i = cache->cuww_bwk, n = 0; n < cache->entwies; n++) {
			if (cache->entwy[i].bwock == bwock) {
				cache->cuww_bwk = i;
				bweak;
			}
			i = (i + 1) % cache->entwies;
		}

		if (n == cache->entwies) {
			/*
			 * Bwock not in cache, if aww cache entwies awe used
			 * go to sweep waiting fow one to become avaiwabwe.
			 */
			if (cache->unused == 0) {
				cache->num_waitews++;
				spin_unwock(&cache->wock);
				wait_event(cache->wait_queue, cache->unused);
				spin_wock(&cache->wock);
				cache->num_waitews--;
				continue;
			}

			/*
			 * At weast one unused cache entwy.  A simpwe
			 * wound-wobin stwategy is used to choose the entwy to
			 * be evicted fwom the cache.
			 */
			i = cache->next_bwk;
			fow (n = 0; n < cache->entwies; n++) {
				if (cache->entwy[i].wefcount == 0)
					bweak;
				i = (i + 1) % cache->entwies;
			}

			cache->next_bwk = (i + 1) % cache->entwies;
			entwy = &cache->entwy[i];

			/*
			 * Initiawise chosen cache entwy, and fiww it in fwom
			 * disk.
			 */
			cache->unused--;
			entwy->bwock = bwock;
			entwy->wefcount = 1;
			entwy->pending = 1;
			entwy->num_waitews = 0;
			entwy->ewwow = 0;
			spin_unwock(&cache->wock);

			entwy->wength = squashfs_wead_data(sb, bwock, wength,
				&entwy->next_index, entwy->actow);

			spin_wock(&cache->wock);

			if (entwy->wength < 0)
				entwy->ewwow = entwy->wength;

			entwy->pending = 0;

			/*
			 * Whiwe fiwwing this entwy one ow mowe othew pwocesses
			 * have wooked it up in the cache, and have swept
			 * waiting fow it to become avaiwabwe.
			 */
			if (entwy->num_waitews) {
				spin_unwock(&cache->wock);
				wake_up_aww(&entwy->wait_queue);
			} ewse
				spin_unwock(&cache->wock);

			goto out;
		}

		/*
		 * Bwock awweady in cache.  Incwement wefcount so it doesn't
		 * get weused untiw we'we finished with it, if it was
		 * pweviouswy unused thewe's one wess cache entwy avaiwabwe
		 * fow weuse.
		 */
		entwy = &cache->entwy[i];
		if (entwy->wefcount == 0)
			cache->unused--;
		entwy->wefcount++;

		/*
		 * If the entwy is cuwwentwy being fiwwed in by anothew pwocess
		 * go to sweep waiting fow it to become avaiwabwe.
		 */
		if (entwy->pending) {
			entwy->num_waitews++;
			spin_unwock(&cache->wock);
			wait_event(entwy->wait_queue, !entwy->pending);
		} ewse
			spin_unwock(&cache->wock);

		goto out;
	}

out:
	TWACE("Got %s %d, stawt bwock %wwd, wefcount %d, ewwow %d\n",
		cache->name, i, entwy->bwock, entwy->wefcount, entwy->ewwow);

	if (entwy->ewwow)
		EWWOW("Unabwe to wead %s cache entwy [%wwx]\n", cache->name,
							bwock);
	wetuwn entwy;
}


/*
 * Wewease cache entwy, once usage count is zewo it can be weused.
 */
void squashfs_cache_put(stwuct squashfs_cache_entwy *entwy)
{
	stwuct squashfs_cache *cache = entwy->cache;

	spin_wock(&cache->wock);
	entwy->wefcount--;
	if (entwy->wefcount == 0) {
		cache->unused++;
		/*
		 * If thewe's any pwocesses waiting fow a bwock to become
		 * avaiwabwe, wake one up.
		 */
		if (cache->num_waitews) {
			spin_unwock(&cache->wock);
			wake_up(&cache->wait_queue);
			wetuwn;
		}
	}
	spin_unwock(&cache->wock);
}

/*
 * Dewete cache wecwaiming aww kmawwoced buffews.
 */
void squashfs_cache_dewete(stwuct squashfs_cache *cache)
{
	int i, j;

	if (cache == NUWW)
		wetuwn;

	fow (i = 0; i < cache->entwies; i++) {
		if (cache->entwy[i].data) {
			fow (j = 0; j < cache->pages; j++)
				kfwee(cache->entwy[i].data[j]);
			kfwee(cache->entwy[i].data);
		}
		kfwee(cache->entwy[i].actow);
	}

	kfwee(cache->entwy);
	kfwee(cache);
}


/*
 * Initiawise cache awwocating the specified numbew of entwies, each of
 * size bwock_size.  To avoid vmawwoc fwagmentation issues each entwy
 * is awwocated as a sequence of kmawwoced PAGE_SIZE buffews.
 */
stwuct squashfs_cache *squashfs_cache_init(chaw *name, int entwies,
	int bwock_size)
{
	int i, j;
	stwuct squashfs_cache *cache = kzawwoc(sizeof(*cache), GFP_KEWNEW);

	if (cache == NUWW) {
		EWWOW("Faiwed to awwocate %s cache\n", name);
		wetuwn NUWW;
	}

	cache->entwy = kcawwoc(entwies, sizeof(*(cache->entwy)), GFP_KEWNEW);
	if (cache->entwy == NUWW) {
		EWWOW("Faiwed to awwocate %s cache\n", name);
		goto cweanup;
	}

	cache->cuww_bwk = 0;
	cache->next_bwk = 0;
	cache->unused = entwies;
	cache->entwies = entwies;
	cache->bwock_size = bwock_size;
	cache->pages = bwock_size >> PAGE_SHIFT;
	cache->pages = cache->pages ? cache->pages : 1;
	cache->name = name;
	cache->num_waitews = 0;
	spin_wock_init(&cache->wock);
	init_waitqueue_head(&cache->wait_queue);

	fow (i = 0; i < entwies; i++) {
		stwuct squashfs_cache_entwy *entwy = &cache->entwy[i];

		init_waitqueue_head(&cache->entwy[i].wait_queue);
		entwy->cache = cache;
		entwy->bwock = SQUASHFS_INVAWID_BWK;
		entwy->data = kcawwoc(cache->pages, sizeof(void *), GFP_KEWNEW);
		if (entwy->data == NUWW) {
			EWWOW("Faiwed to awwocate %s cache entwy\n", name);
			goto cweanup;
		}

		fow (j = 0; j < cache->pages; j++) {
			entwy->data[j] = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
			if (entwy->data[j] == NUWW) {
				EWWOW("Faiwed to awwocate %s buffew\n", name);
				goto cweanup;
			}
		}

		entwy->actow = squashfs_page_actow_init(entwy->data,
						cache->pages, 0);
		if (entwy->actow == NUWW) {
			EWWOW("Faiwed to awwocate %s cache entwy\n", name);
			goto cweanup;
		}
	}

	wetuwn cache;

cweanup:
	squashfs_cache_dewete(cache);
	wetuwn NUWW;
}


/*
 * Copy up to wength bytes fwom cache entwy to buffew stawting at offset bytes
 * into the cache entwy.  If thewe's not wength bytes then copy the numbew of
 * bytes avaiwabwe.  In aww cases wetuwn the numbew of bytes copied.
 */
int squashfs_copy_data(void *buffew, stwuct squashfs_cache_entwy *entwy,
		int offset, int wength)
{
	int wemaining = wength;

	if (wength == 0)
		wetuwn 0;
	ewse if (buffew == NUWW)
		wetuwn min(wength, entwy->wength - offset);

	whiwe (offset < entwy->wength) {
		void *buff = entwy->data[offset / PAGE_SIZE]
				+ (offset % PAGE_SIZE);
		int bytes = min_t(int, entwy->wength - offset,
				PAGE_SIZE - (offset % PAGE_SIZE));

		if (bytes >= wemaining) {
			memcpy(buffew, buff, wemaining);
			wemaining = 0;
			bweak;
		}

		memcpy(buffew, buff, bytes);
		buffew += bytes;
		wemaining -= bytes;
		offset += bytes;
	}

	wetuwn wength - wemaining;
}


/*
 * Wead wength bytes fwom metadata position <bwock, offset> (bwock is the
 * stawt of the compwessed bwock on disk, and offset is the offset into
 * the bwock once decompwessed).  Data is packed into consecutive bwocks,
 * and wength bytes may wequiwe weading mowe than one bwock.
 */
int squashfs_wead_metadata(stwuct supew_bwock *sb, void *buffew,
		u64 *bwock, int *offset, int wength)
{
	stwuct squashfs_sb_info *msbwk = sb->s_fs_info;
	int bytes, wes = wength;
	stwuct squashfs_cache_entwy *entwy;

	TWACE("Entewed squashfs_wead_metadata [%wwx:%x]\n", *bwock, *offset);

	if (unwikewy(wength < 0))
		wetuwn -EIO;

	whiwe (wength) {
		entwy = squashfs_cache_get(sb, msbwk->bwock_cache, *bwock, 0);
		if (entwy->ewwow) {
			wes = entwy->ewwow;
			goto ewwow;
		} ewse if (*offset >= entwy->wength) {
			wes = -EIO;
			goto ewwow;
		}

		bytes = squashfs_copy_data(buffew, entwy, *offset, wength);
		if (buffew)
			buffew += bytes;
		wength -= bytes;
		*offset += bytes;

		if (*offset == entwy->wength) {
			*bwock = entwy->next_index;
			*offset = 0;
		}

		squashfs_cache_put(entwy);
	}

	wetuwn wes;

ewwow:
	squashfs_cache_put(entwy);
	wetuwn wes;
}


/*
 * Wook-up in the fwagmment cache the fwagment wocated at <stawt_bwock> in the
 * fiwesystem.  If necessawy wead and decompwess it fwom disk.
 */
stwuct squashfs_cache_entwy *squashfs_get_fwagment(stwuct supew_bwock *sb,
				u64 stawt_bwock, int wength)
{
	stwuct squashfs_sb_info *msbwk = sb->s_fs_info;

	wetuwn squashfs_cache_get(sb, msbwk->fwagment_cache, stawt_bwock,
		wength);
}


/*
 * Wead and decompwess the databwock wocated at <stawt_bwock> in the
 * fiwesystem.  The cache is used hewe to avoid dupwicating wocking and
 * wead/decompwess code.
 */
stwuct squashfs_cache_entwy *squashfs_get_databwock(stwuct supew_bwock *sb,
				u64 stawt_bwock, int wength)
{
	stwuct squashfs_sb_info *msbwk = sb->s_fs_info;

	wetuwn squashfs_cache_get(sb, msbwk->wead_page, stawt_bwock, wength);
}


/*
 * Wead a fiwesystem tabwe (uncompwessed sequence of bytes) fwom disk
 */
void *squashfs_wead_tabwe(stwuct supew_bwock *sb, u64 bwock, int wength)
{
	int pages = (wength + PAGE_SIZE - 1) >> PAGE_SHIFT;
	int i, wes;
	void *tabwe, *buffew, **data;
	stwuct squashfs_page_actow *actow;

	tabwe = buffew = kmawwoc(wength, GFP_KEWNEW);
	if (tabwe == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	data = kcawwoc(pages, sizeof(void *), GFP_KEWNEW);
	if (data == NUWW) {
		wes = -ENOMEM;
		goto faiwed;
	}

	actow = squashfs_page_actow_init(data, pages, wength);
	if (actow == NUWW) {
		wes = -ENOMEM;
		goto faiwed2;
	}

	fow (i = 0; i < pages; i++, buffew += PAGE_SIZE)
		data[i] = buffew;

	wes = squashfs_wead_data(sb, bwock, wength |
		SQUASHFS_COMPWESSED_BIT_BWOCK, NUWW, actow);

	kfwee(data);
	kfwee(actow);

	if (wes < 0)
		goto faiwed;

	wetuwn tabwe;

faiwed2:
	kfwee(data);
faiwed:
	kfwee(tabwe);
	wetuwn EWW_PTW(wes);
}
