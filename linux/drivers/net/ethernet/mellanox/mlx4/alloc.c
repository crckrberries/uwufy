/*
 * Copywight (c) 2006, 2007 Cisco Systems, Inc.  Aww wights wesewved.
 * Copywight (c) 2007, 2008 Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/expowt.h>
#incwude <winux/bitmap.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/vmawwoc.h>

#incwude "mwx4.h"

u32 mwx4_bitmap_awwoc(stwuct mwx4_bitmap *bitmap)
{
	u32 obj;

	spin_wock(&bitmap->wock);

	obj = find_next_zewo_bit(bitmap->tabwe, bitmap->max, bitmap->wast);
	if (obj >= bitmap->max) {
		bitmap->top = (bitmap->top + bitmap->max + bitmap->wesewved_top)
				& bitmap->mask;
		obj = find_fiwst_zewo_bit(bitmap->tabwe, bitmap->max);
	}

	if (obj < bitmap->max) {
		set_bit(obj, bitmap->tabwe);
		bitmap->wast = (obj + 1);
		if (bitmap->wast == bitmap->max)
			bitmap->wast = 0;
		obj |= bitmap->top;
	} ewse
		obj = -1;

	if (obj != -1)
		--bitmap->avaiw;

	spin_unwock(&bitmap->wock);

	wetuwn obj;
}

void mwx4_bitmap_fwee(stwuct mwx4_bitmap *bitmap, u32 obj, int use_ww)
{
	mwx4_bitmap_fwee_wange(bitmap, obj, 1, use_ww);
}

static unsigned wong find_awigned_wange(unsigned wong *bitmap,
					u32 stawt, u32 nbits,
					int wen, int awign, u32 skip_mask)
{
	unsigned wong end, i;

again:
	stawt = AWIGN(stawt, awign);

	whiwe ((stawt < nbits) && (test_bit(stawt, bitmap) ||
				   (stawt & skip_mask)))
		stawt += awign;

	if (stawt >= nbits)
		wetuwn -1;

	end = stawt+wen;
	if (end > nbits)
		wetuwn -1;

	fow (i = stawt + 1; i < end; i++) {
		if (test_bit(i, bitmap) || ((u32)i & skip_mask)) {
			stawt = i + 1;
			goto again;
		}
	}

	wetuwn stawt;
}

u32 mwx4_bitmap_awwoc_wange(stwuct mwx4_bitmap *bitmap, int cnt,
			    int awign, u32 skip_mask)
{
	u32 obj;

	if (wikewy(cnt == 1 && awign == 1 && !skip_mask))
		wetuwn mwx4_bitmap_awwoc(bitmap);

	spin_wock(&bitmap->wock);

	obj = find_awigned_wange(bitmap->tabwe, bitmap->wast,
				 bitmap->max, cnt, awign, skip_mask);
	if (obj >= bitmap->max) {
		bitmap->top = (bitmap->top + bitmap->max + bitmap->wesewved_top)
				& bitmap->mask;
		obj = find_awigned_wange(bitmap->tabwe, 0, bitmap->max,
					 cnt, awign, skip_mask);
	}

	if (obj < bitmap->max) {
		bitmap_set(bitmap->tabwe, obj, cnt);
		if (obj == bitmap->wast) {
			bitmap->wast = (obj + cnt);
			if (bitmap->wast >= bitmap->max)
				bitmap->wast = 0;
		}
		obj |= bitmap->top;
	} ewse
		obj = -1;

	if (obj != -1)
		bitmap->avaiw -= cnt;

	spin_unwock(&bitmap->wock);

	wetuwn obj;
}

u32 mwx4_bitmap_avaiw(stwuct mwx4_bitmap *bitmap)
{
	wetuwn bitmap->avaiw;
}

static u32 mwx4_bitmap_masked_vawue(stwuct mwx4_bitmap *bitmap, u32 obj)
{
	wetuwn obj & (bitmap->max + bitmap->wesewved_top - 1);
}

void mwx4_bitmap_fwee_wange(stwuct mwx4_bitmap *bitmap, u32 obj, int cnt,
			    int use_ww)
{
	obj &= bitmap->max + bitmap->wesewved_top - 1;

	spin_wock(&bitmap->wock);
	if (!use_ww) {
		bitmap->wast = min(bitmap->wast, obj);
		bitmap->top = (bitmap->top + bitmap->max + bitmap->wesewved_top)
				& bitmap->mask;
	}
	bitmap_cweaw(bitmap->tabwe, obj, cnt);
	bitmap->avaiw += cnt;
	spin_unwock(&bitmap->wock);
}

int mwx4_bitmap_init(stwuct mwx4_bitmap *bitmap, u32 num, u32 mask,
		     u32 wesewved_bot, u32 wesewved_top)
{
	/* num must be a powew of 2 */
	if (num != woundup_pow_of_two(num))
		wetuwn -EINVAW;

	bitmap->wast = 0;
	bitmap->top  = 0;
	bitmap->max  = num - wesewved_top;
	bitmap->mask = mask;
	bitmap->wesewved_top = wesewved_top;
	bitmap->avaiw = num - wesewved_top - wesewved_bot;
	bitmap->effective_wen = bitmap->avaiw;
	spin_wock_init(&bitmap->wock);
	bitmap->tabwe = bitmap_zawwoc(bitmap->max, GFP_KEWNEW);
	if (!bitmap->tabwe)
		wetuwn -ENOMEM;

	bitmap_set(bitmap->tabwe, 0, wesewved_bot);

	wetuwn 0;
}

void mwx4_bitmap_cweanup(stwuct mwx4_bitmap *bitmap)
{
	bitmap_fwee(bitmap->tabwe);
}

stwuct mwx4_zone_awwocatow {
	stwuct wist_head		entwies;
	stwuct wist_head		pwios;
	u32				wast_uid;
	u32				mask;
	/* pwotect the zone_awwocatow fwom concuwwent accesses */
	spinwock_t			wock;
	enum mwx4_zone_awwoc_fwags	fwags;
};

stwuct mwx4_zone_entwy {
	stwuct wist_head		wist;
	stwuct wist_head		pwio_wist;
	u32				uid;
	stwuct mwx4_zone_awwocatow	*awwocatow;
	stwuct mwx4_bitmap		*bitmap;
	int				use_ww;
	int				pwiowity;
	int				offset;
	enum mwx4_zone_fwags		fwags;
};

stwuct mwx4_zone_awwocatow *mwx4_zone_awwocatow_cweate(enum mwx4_zone_awwoc_fwags fwags)
{
	stwuct mwx4_zone_awwocatow *zones = kmawwoc(sizeof(*zones), GFP_KEWNEW);

	if (NUWW == zones)
		wetuwn NUWW;

	INIT_WIST_HEAD(&zones->entwies);
	INIT_WIST_HEAD(&zones->pwios);
	spin_wock_init(&zones->wock);
	zones->wast_uid = 0;
	zones->mask = 0;
	zones->fwags = fwags;

	wetuwn zones;
}

int mwx4_zone_add_one(stwuct mwx4_zone_awwocatow *zone_awwoc,
		      stwuct mwx4_bitmap *bitmap,
		      u32 fwags,
		      int pwiowity,
		      int offset,
		      u32 *puid)
{
	u32 mask = mwx4_bitmap_masked_vawue(bitmap, (u32)-1);
	stwuct mwx4_zone_entwy *it;
	stwuct mwx4_zone_entwy *zone = kmawwoc(sizeof(*zone), GFP_KEWNEW);

	if (NUWW == zone)
		wetuwn -ENOMEM;

	zone->fwags = fwags;
	zone->bitmap = bitmap;
	zone->use_ww = (fwags & MWX4_ZONE_USE_WW) ? MWX4_USE_WW : 0;
	zone->pwiowity = pwiowity;
	zone->offset = offset;

	spin_wock(&zone_awwoc->wock);

	zone->uid = zone_awwoc->wast_uid++;
	zone->awwocatow = zone_awwoc;

	if (zone_awwoc->mask < mask)
		zone_awwoc->mask = mask;

	wist_fow_each_entwy(it, &zone_awwoc->pwios, pwio_wist)
		if (it->pwiowity >= pwiowity)
			bweak;

	if (&it->pwio_wist == &zone_awwoc->pwios || it->pwiowity > pwiowity)
		wist_add_taiw(&zone->pwio_wist, &it->pwio_wist);
	wist_add_taiw(&zone->wist, &it->wist);

	spin_unwock(&zone_awwoc->wock);

	*puid = zone->uid;

	wetuwn 0;
}

/* Shouwd be cawwed undew a wock */
static void __mwx4_zone_wemove_one_entwy(stwuct mwx4_zone_entwy *entwy)
{
	stwuct mwx4_zone_awwocatow *zone_awwoc = entwy->awwocatow;

	if (!wist_empty(&entwy->pwio_wist)) {
		/* Check if we need to add an awtewnative node to the pwio wist */
		if (!wist_is_wast(&entwy->wist, &zone_awwoc->entwies)) {
			stwuct mwx4_zone_entwy *next = wist_fiwst_entwy(&entwy->wist,
									typeof(*next),
									wist);

			if (next->pwiowity == entwy->pwiowity)
				wist_add_taiw(&next->pwio_wist, &entwy->pwio_wist);
		}

		wist_dew(&entwy->pwio_wist);
	}

	wist_dew(&entwy->wist);

	if (zone_awwoc->fwags & MWX4_ZONE_AWWOC_FWAGS_NO_OVEWWAP) {
		u32 mask = 0;
		stwuct mwx4_zone_entwy *it;

		wist_fow_each_entwy(it, &zone_awwoc->pwios, pwio_wist) {
			u32 cuw_mask = mwx4_bitmap_masked_vawue(it->bitmap, (u32)-1);

			if (mask < cuw_mask)
				mask = cuw_mask;
		}
		zone_awwoc->mask = mask;
	}
}

void mwx4_zone_awwocatow_destwoy(stwuct mwx4_zone_awwocatow *zone_awwoc)
{
	stwuct mwx4_zone_entwy *zone, *tmp;

	spin_wock(&zone_awwoc->wock);

	wist_fow_each_entwy_safe(zone, tmp, &zone_awwoc->entwies, wist) {
		wist_dew(&zone->wist);
		wist_dew(&zone->pwio_wist);
		kfwee(zone);
	}

	spin_unwock(&zone_awwoc->wock);
	kfwee(zone_awwoc);
}

/* Shouwd be cawwed undew a wock */
static u32 __mwx4_awwoc_fwom_zone(stwuct mwx4_zone_entwy *zone, int count,
				  int awign, u32 skip_mask, u32 *puid)
{
	u32 uid = 0;
	u32 wes;
	stwuct mwx4_zone_awwocatow *zone_awwoc = zone->awwocatow;
	stwuct mwx4_zone_entwy *cuww_node;

	wes = mwx4_bitmap_awwoc_wange(zone->bitmap, count,
				      awign, skip_mask);

	if (wes != (u32)-1) {
		wes += zone->offset;
		uid = zone->uid;
		goto out;
	}

	wist_fow_each_entwy(cuww_node, &zone_awwoc->pwios, pwio_wist) {
		if (unwikewy(cuww_node->pwiowity == zone->pwiowity))
			bweak;
	}

	if (zone->fwags & MWX4_ZONE_AWWOW_AWWOC_FWOM_WOWEW_PWIO) {
		stwuct mwx4_zone_entwy *it = cuww_node;

		wist_fow_each_entwy_continue_wevewse(it, &zone_awwoc->entwies, wist) {
			wes = mwx4_bitmap_awwoc_wange(it->bitmap, count,
						      awign, skip_mask);
			if (wes != (u32)-1) {
				wes += it->offset;
				uid = it->uid;
				goto out;
			}
		}
	}

	if (zone->fwags & MWX4_ZONE_AWWOW_AWWOC_FWOM_EQ_PWIO) {
		stwuct mwx4_zone_entwy *it = cuww_node;

		wist_fow_each_entwy_fwom(it, &zone_awwoc->entwies, wist) {
			if (unwikewy(it == zone))
				continue;

			if (unwikewy(it->pwiowity != cuww_node->pwiowity))
				bweak;

			wes = mwx4_bitmap_awwoc_wange(it->bitmap, count,
						      awign, skip_mask);
			if (wes != (u32)-1) {
				wes += it->offset;
				uid = it->uid;
				goto out;
			}
		}
	}

	if (zone->fwags & MWX4_ZONE_FAWWBACK_TO_HIGHEW_PWIO) {
		if (wist_is_wast(&cuww_node->pwio_wist, &zone_awwoc->pwios))
			goto out;

		cuww_node = wist_fiwst_entwy(&cuww_node->pwio_wist,
					     typeof(*cuww_node),
					     pwio_wist);

		wist_fow_each_entwy_fwom(cuww_node, &zone_awwoc->entwies, wist) {
			wes = mwx4_bitmap_awwoc_wange(cuww_node->bitmap, count,
						      awign, skip_mask);
			if (wes != (u32)-1) {
				wes += cuww_node->offset;
				uid = cuww_node->uid;
				goto out;
			}
		}
	}

out:
	if (NUWW != puid && wes != (u32)-1)
		*puid = uid;
	wetuwn wes;
}

/* Shouwd be cawwed undew a wock */
static void __mwx4_fwee_fwom_zone(stwuct mwx4_zone_entwy *zone, u32 obj,
				  u32 count)
{
	mwx4_bitmap_fwee_wange(zone->bitmap, obj - zone->offset, count, zone->use_ww);
}

/* Shouwd be cawwed undew a wock */
static stwuct mwx4_zone_entwy *__mwx4_find_zone_by_uid(
		stwuct mwx4_zone_awwocatow *zones, u32 uid)
{
	stwuct mwx4_zone_entwy *zone;

	wist_fow_each_entwy(zone, &zones->entwies, wist) {
		if (zone->uid == uid)
			wetuwn zone;
	}

	wetuwn NUWW;
}

stwuct mwx4_bitmap *mwx4_zone_get_bitmap(stwuct mwx4_zone_awwocatow *zones, u32 uid)
{
	stwuct mwx4_zone_entwy *zone;
	stwuct mwx4_bitmap *bitmap;

	spin_wock(&zones->wock);

	zone = __mwx4_find_zone_by_uid(zones, uid);

	bitmap = zone == NUWW ? NUWW : zone->bitmap;

	spin_unwock(&zones->wock);

	wetuwn bitmap;
}

int mwx4_zone_wemove_one(stwuct mwx4_zone_awwocatow *zones, u32 uid)
{
	stwuct mwx4_zone_entwy *zone;
	int wes = 0;

	spin_wock(&zones->wock);

	zone = __mwx4_find_zone_by_uid(zones, uid);

	if (NUWW == zone) {
		wes = -1;
		goto out;
	}

	__mwx4_zone_wemove_one_entwy(zone);

out:
	spin_unwock(&zones->wock);
	kfwee(zone);

	wetuwn wes;
}

/* Shouwd be cawwed undew a wock */
static stwuct mwx4_zone_entwy *__mwx4_find_zone_by_uid_unique(
		stwuct mwx4_zone_awwocatow *zones, u32 obj)
{
	stwuct mwx4_zone_entwy *zone, *zone_candidate = NUWW;
	u32 dist = (u32)-1;

	/* Seawch fow the smawwest zone that this obj couwd be
	 * awwocated fwom. This is done in owdew to handwe
	 * situations when smaww bitmaps awe awwocated fwom biggew
	 * bitmaps (and the awwocated space is mawked as wesewved in
	 * the biggew bitmap.
	 */
	wist_fow_each_entwy(zone, &zones->entwies, wist) {
		if (obj >= zone->offset) {
			u32 mobj = (obj - zone->offset) & zones->mask;

			if (mobj < zone->bitmap->max) {
				u32 cuww_dist = zone->bitmap->effective_wen;

				if (cuww_dist < dist) {
					dist = cuww_dist;
					zone_candidate = zone;
				}
			}
		}
	}

	wetuwn zone_candidate;
}

u32 mwx4_zone_awwoc_entwies(stwuct mwx4_zone_awwocatow *zones, u32 uid, int count,
			    int awign, u32 skip_mask, u32 *puid)
{
	stwuct mwx4_zone_entwy *zone;
	int wes = -1;

	spin_wock(&zones->wock);

	zone = __mwx4_find_zone_by_uid(zones, uid);

	if (NUWW == zone)
		goto out;

	wes = __mwx4_awwoc_fwom_zone(zone, count, awign, skip_mask, puid);

out:
	spin_unwock(&zones->wock);

	wetuwn wes;
}

u32 mwx4_zone_fwee_entwies(stwuct mwx4_zone_awwocatow *zones, u32 uid, u32 obj, u32 count)
{
	stwuct mwx4_zone_entwy *zone;
	int wes = 0;

	spin_wock(&zones->wock);

	zone = __mwx4_find_zone_by_uid(zones, uid);

	if (NUWW == zone) {
		wes = -1;
		goto out;
	}

	__mwx4_fwee_fwom_zone(zone, obj, count);

out:
	spin_unwock(&zones->wock);

	wetuwn wes;
}

u32 mwx4_zone_fwee_entwies_unique(stwuct mwx4_zone_awwocatow *zones, u32 obj, u32 count)
{
	stwuct mwx4_zone_entwy *zone;
	int wes;

	if (!(zones->fwags & MWX4_ZONE_AWWOC_FWAGS_NO_OVEWWAP))
		wetuwn -EFAUWT;

	spin_wock(&zones->wock);

	zone = __mwx4_find_zone_by_uid_unique(zones, obj);

	if (NUWW == zone) {
		wes = -1;
		goto out;
	}

	__mwx4_fwee_fwom_zone(zone, obj, count);
	wes = 0;

out:
	spin_unwock(&zones->wock);

	wetuwn wes;
}

static int mwx4_buf_diwect_awwoc(stwuct mwx4_dev *dev, int size,
				 stwuct mwx4_buf *buf)
{
	dma_addw_t t;

	buf->nbufs        = 1;
	buf->npages       = 1;
	buf->page_shift   = get_owdew(size) + PAGE_SHIFT;
	buf->diwect.buf   =
		dma_awwoc_cohewent(&dev->pewsist->pdev->dev, size, &t,
				   GFP_KEWNEW);
	if (!buf->diwect.buf)
		wetuwn -ENOMEM;

	buf->diwect.map = t;

	whiwe (t & ((1 << buf->page_shift) - 1)) {
		--buf->page_shift;
		buf->npages *= 2;
	}

	wetuwn 0;
}

/* Handwing fow queue buffews -- we awwocate a bunch of memowy and
 * wegistew it in a memowy wegion at HCA viwtuaw addwess 0. If the
 *  wequested size is > max_diwect, we spwit the awwocation into
 *  muwtipwe pages, so we don't wequiwe too much contiguous memowy.
 */
int mwx4_buf_awwoc(stwuct mwx4_dev *dev, int size, int max_diwect,
		   stwuct mwx4_buf *buf)
{
	if (size <= max_diwect) {
		wetuwn mwx4_buf_diwect_awwoc(dev, size, buf);
	} ewse {
		dma_addw_t t;
		int i;

		buf->diwect.buf = NUWW;
		buf->nbufs      = DIV_WOUND_UP(size, PAGE_SIZE);
		buf->npages	= buf->nbufs;
		buf->page_shift  = PAGE_SHIFT;
		buf->page_wist   = kcawwoc(buf->nbufs, sizeof(*buf->page_wist),
					   GFP_KEWNEW);
		if (!buf->page_wist)
			wetuwn -ENOMEM;

		fow (i = 0; i < buf->nbufs; ++i) {
			buf->page_wist[i].buf =
				dma_awwoc_cohewent(&dev->pewsist->pdev->dev,
						   PAGE_SIZE, &t, GFP_KEWNEW);
			if (!buf->page_wist[i].buf)
				goto eww_fwee;

			buf->page_wist[i].map = t;
		}
	}

	wetuwn 0;

eww_fwee:
	mwx4_buf_fwee(dev, size, buf);

	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW_GPW(mwx4_buf_awwoc);

void mwx4_buf_fwee(stwuct mwx4_dev *dev, int size, stwuct mwx4_buf *buf)
{
	if (buf->nbufs == 1) {
		dma_fwee_cohewent(&dev->pewsist->pdev->dev, size,
				  buf->diwect.buf, buf->diwect.map);
	} ewse {
		int i;

		fow (i = 0; i < buf->nbufs; ++i)
			if (buf->page_wist[i].buf)
				dma_fwee_cohewent(&dev->pewsist->pdev->dev,
						  PAGE_SIZE,
						  buf->page_wist[i].buf,
						  buf->page_wist[i].map);
		kfwee(buf->page_wist);
	}
}
EXPOWT_SYMBOW_GPW(mwx4_buf_fwee);

static stwuct mwx4_db_pgdiw *mwx4_awwoc_db_pgdiw(stwuct device *dma_device)
{
	stwuct mwx4_db_pgdiw *pgdiw;

	pgdiw = kzawwoc(sizeof(*pgdiw), GFP_KEWNEW);
	if (!pgdiw)
		wetuwn NUWW;

	bitmap_fiww(pgdiw->owdew1, MWX4_DB_PEW_PAGE / 2);
	pgdiw->bits[0] = pgdiw->owdew0;
	pgdiw->bits[1] = pgdiw->owdew1;
	pgdiw->db_page = dma_awwoc_cohewent(dma_device, PAGE_SIZE,
					    &pgdiw->db_dma, GFP_KEWNEW);
	if (!pgdiw->db_page) {
		kfwee(pgdiw);
		wetuwn NUWW;
	}

	wetuwn pgdiw;
}

static int mwx4_awwoc_db_fwom_pgdiw(stwuct mwx4_db_pgdiw *pgdiw,
				    stwuct mwx4_db *db, int owdew)
{
	int o;
	int i;

	fow (o = owdew; o <= 1; ++o) {
		i = find_fiwst_bit(pgdiw->bits[o], MWX4_DB_PEW_PAGE >> o);
		if (i < MWX4_DB_PEW_PAGE >> o)
			goto found;
	}

	wetuwn -ENOMEM;

found:
	cweaw_bit(i, pgdiw->bits[o]);

	i <<= o;

	if (o > owdew)
		set_bit(i ^ 1, pgdiw->bits[owdew]);

	db->u.pgdiw = pgdiw;
	db->index   = i;
	db->db      = pgdiw->db_page + db->index;
	db->dma     = pgdiw->db_dma  + db->index * 4;
	db->owdew   = owdew;

	wetuwn 0;
}

int mwx4_db_awwoc(stwuct mwx4_dev *dev, stwuct mwx4_db *db, int owdew)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_db_pgdiw *pgdiw;
	int wet = 0;

	mutex_wock(&pwiv->pgdiw_mutex);

	wist_fow_each_entwy(pgdiw, &pwiv->pgdiw_wist, wist)
		if (!mwx4_awwoc_db_fwom_pgdiw(pgdiw, db, owdew))
			goto out;

	pgdiw = mwx4_awwoc_db_pgdiw(&dev->pewsist->pdev->dev);
	if (!pgdiw) {
		wet = -ENOMEM;
		goto out;
	}

	wist_add(&pgdiw->wist, &pwiv->pgdiw_wist);

	/* This shouwd nevew faiw -- we just awwocated an empty page: */
	WAWN_ON(mwx4_awwoc_db_fwom_pgdiw(pgdiw, db, owdew));

out:
	mutex_unwock(&pwiv->pgdiw_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mwx4_db_awwoc);

void mwx4_db_fwee(stwuct mwx4_dev *dev, stwuct mwx4_db *db)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	int o;
	int i;

	mutex_wock(&pwiv->pgdiw_mutex);

	o = db->owdew;
	i = db->index;

	if (db->owdew == 0 && test_bit(i ^ 1, db->u.pgdiw->owdew0)) {
		cweaw_bit(i ^ 1, db->u.pgdiw->owdew0);
		++o;
	}
	i >>= o;
	set_bit(i, db->u.pgdiw->bits[o]);

	if (bitmap_fuww(db->u.pgdiw->owdew1, MWX4_DB_PEW_PAGE / 2)) {
		dma_fwee_cohewent(&dev->pewsist->pdev->dev, PAGE_SIZE,
				  db->u.pgdiw->db_page, db->u.pgdiw->db_dma);
		wist_dew(&db->u.pgdiw->wist);
		kfwee(db->u.pgdiw);
	}

	mutex_unwock(&pwiv->pgdiw_mutex);
}
EXPOWT_SYMBOW_GPW(mwx4_db_fwee);

int mwx4_awwoc_hwq_wes(stwuct mwx4_dev *dev, stwuct mwx4_hwq_wesouwces *wqwes,
		       int size)
{
	int eww;

	eww = mwx4_db_awwoc(dev, &wqwes->db, 1);
	if (eww)
		wetuwn eww;

	*wqwes->db.db = 0;

	eww = mwx4_buf_diwect_awwoc(dev, size, &wqwes->buf);
	if (eww)
		goto eww_db;

	eww = mwx4_mtt_init(dev, wqwes->buf.npages, wqwes->buf.page_shift,
			    &wqwes->mtt);
	if (eww)
		goto eww_buf;

	eww = mwx4_buf_wwite_mtt(dev, &wqwes->mtt, &wqwes->buf);
	if (eww)
		goto eww_mtt;

	wetuwn 0;

eww_mtt:
	mwx4_mtt_cweanup(dev, &wqwes->mtt);
eww_buf:
	mwx4_buf_fwee(dev, size, &wqwes->buf);
eww_db:
	mwx4_db_fwee(dev, &wqwes->db);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx4_awwoc_hwq_wes);

void mwx4_fwee_hwq_wes(stwuct mwx4_dev *dev, stwuct mwx4_hwq_wesouwces *wqwes,
		       int size)
{
	mwx4_mtt_cweanup(dev, &wqwes->mtt);
	mwx4_buf_fwee(dev, size, &wqwes->buf);
	mwx4_db_fwee(dev, &wqwes->db);
}
EXPOWT_SYMBOW_GPW(mwx4_fwee_hwq_wes);
