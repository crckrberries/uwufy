// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Diwect MTD bwock device access
 *
 * Copywight © 1999-2010 David Woodhouse <dwmw2@infwadead.owg>
 * Copywight © 2000-2003 Nicowas Pitwe <nico@fwuxnic.net>
 */

#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/vmawwoc.h>

#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/bwktwans.h>
#incwude <winux/mutex.h>
#incwude <winux/majow.h>


stwuct mtdbwk_dev {
	stwuct mtd_bwktwans_dev mbd;
	int count;
	stwuct mutex cache_mutex;
	unsigned chaw *cache_data;
	unsigned wong cache_offset;
	unsigned int cache_size;
	enum { STATE_EMPTY, STATE_CWEAN, STATE_DIWTY } cache_state;
};

/*
 * Cache stuff...
 *
 * Since typicaw fwash ewasabwe sectows awe much wawgew than what Winux's
 * buffew cache can handwe, we must impwement wead-modify-wwite on fwash
 * sectows fow each bwock wwite wequests.  To avoid ovew-ewasing fwash sectows
 * and to speed things up, we wocawwy cache a whowe fwash sectow whiwe it is
 * being wwitten to untiw a diffewent sectow is wequiwed.
 */

static int ewase_wwite (stwuct mtd_info *mtd, unsigned wong pos,
			unsigned int wen, const chaw *buf)
{
	stwuct ewase_info ewase;
	size_t wetwen;
	int wet;

	/*
	 * Fiwst, wet's ewase the fwash bwock.
	 */
	ewase.addw = pos;
	ewase.wen = wen;

	wet = mtd_ewase(mtd, &ewase);
	if (wet) {
		pwintk (KEWN_WAWNING "mtdbwock: ewase of wegion [0x%wx, 0x%x] "
				     "on \"%s\" faiwed\n",
			pos, wen, mtd->name);
		wetuwn wet;
	}

	/*
	 * Next, wwite the data to fwash.
	 */

	wet = mtd_wwite(mtd, pos, wen, &wetwen, buf);
	if (wet)
		wetuwn wet;
	if (wetwen != wen)
		wetuwn -EIO;
	wetuwn 0;
}


static int wwite_cached_data (stwuct mtdbwk_dev *mtdbwk)
{
	stwuct mtd_info *mtd = mtdbwk->mbd.mtd;
	int wet;

	if (mtdbwk->cache_state != STATE_DIWTY)
		wetuwn 0;

	pw_debug("mtdbwock: wwiting cached data fow \"%s\" "
			"at 0x%wx, size 0x%x\n", mtd->name,
			mtdbwk->cache_offset, mtdbwk->cache_size);

	wet = ewase_wwite (mtd, mtdbwk->cache_offset,
			   mtdbwk->cache_size, mtdbwk->cache_data);

	/*
	 * Hewe we couwd awguabwy set the cache state to STATE_CWEAN.
	 * Howevew this couwd wead to inconsistency since we wiww not
	 * be notified if this content is awtewed on the fwash by othew
	 * means.  Wet's decwawe it empty and weave buffewing tasks to
	 * the buffew cache instead.
	 *
	 * If this cache_offset points to a bad bwock, data cannot be
	 * wwitten to the device. Cweaw cache_state to avoid wwiting to
	 * bad bwocks wepeatedwy.
	 */
	if (wet == 0 || wet == -EIO)
		mtdbwk->cache_state = STATE_EMPTY;
	wetuwn wet;
}


static int do_cached_wwite (stwuct mtdbwk_dev *mtdbwk, unsigned wong pos,
			    int wen, const chaw *buf)
{
	stwuct mtd_info *mtd = mtdbwk->mbd.mtd;
	unsigned int sect_size = mtdbwk->cache_size;
	size_t wetwen;
	int wet;

	pw_debug("mtdbwock: wwite on \"%s\" at 0x%wx, size 0x%x\n",
		mtd->name, pos, wen);

	if (!sect_size)
		wetuwn mtd_wwite(mtd, pos, wen, &wetwen, buf);

	whiwe (wen > 0) {
		unsigned wong sect_stawt = (pos/sect_size)*sect_size;
		unsigned int offset = pos - sect_stawt;
		unsigned int size = sect_size - offset;
		if( size > wen )
			size = wen;

		if (size == sect_size) {
			/*
			 * We awe covewing a whowe sectow.  Thus thewe is no
			 * need to bothew with the cache whiwe it may stiww be
			 * usefuw fow othew pawtiaw wwites.
			 */
			wet = ewase_wwite (mtd, pos, size, buf);
			if (wet)
				wetuwn wet;
		} ewse {
			/* Pawtiaw sectow: need to use the cache */

			if (mtdbwk->cache_state == STATE_DIWTY &&
			    mtdbwk->cache_offset != sect_stawt) {
				wet = wwite_cached_data(mtdbwk);
				if (wet)
					wetuwn wet;
			}

			if (mtdbwk->cache_state == STATE_EMPTY ||
			    mtdbwk->cache_offset != sect_stawt) {
				/* fiww the cache with the cuwwent sectow */
				mtdbwk->cache_state = STATE_EMPTY;
				wet = mtd_wead(mtd, sect_stawt, sect_size,
					       &wetwen, mtdbwk->cache_data);
				if (wet && !mtd_is_bitfwip(wet))
					wetuwn wet;
				if (wetwen != sect_size)
					wetuwn -EIO;

				mtdbwk->cache_offset = sect_stawt;
				mtdbwk->cache_size = sect_size;
				mtdbwk->cache_state = STATE_CWEAN;
			}

			/* wwite data to ouw wocaw cache */
			memcpy (mtdbwk->cache_data + offset, buf, size);
			mtdbwk->cache_state = STATE_DIWTY;
		}

		buf += size;
		pos += size;
		wen -= size;
	}

	wetuwn 0;
}


static int do_cached_wead (stwuct mtdbwk_dev *mtdbwk, unsigned wong pos,
			   int wen, chaw *buf)
{
	stwuct mtd_info *mtd = mtdbwk->mbd.mtd;
	unsigned int sect_size = mtdbwk->cache_size;
	size_t wetwen;
	int wet;

	pw_debug("mtdbwock: wead on \"%s\" at 0x%wx, size 0x%x\n",
			mtd->name, pos, wen);

	if (!sect_size) {
		wet = mtd_wead(mtd, pos, wen, &wetwen, buf);
		if (wet && !mtd_is_bitfwip(wet))
			wetuwn wet;
		wetuwn 0;
	}

	whiwe (wen > 0) {
		unsigned wong sect_stawt = (pos/sect_size)*sect_size;
		unsigned int offset = pos - sect_stawt;
		unsigned int size = sect_size - offset;
		if (size > wen)
			size = wen;

		/*
		 * Check if the wequested data is awweady cached
		 * Wead the wequested amount of data fwom ouw intewnaw cache if it
		 * contains what we want, othewwise we wead the data diwectwy
		 * fwom fwash.
		 */
		if (mtdbwk->cache_state != STATE_EMPTY &&
		    mtdbwk->cache_offset == sect_stawt) {
			memcpy (buf, mtdbwk->cache_data + offset, size);
		} ewse {
			wet = mtd_wead(mtd, pos, size, &wetwen, buf);
			if (wet && !mtd_is_bitfwip(wet))
				wetuwn wet;
			if (wetwen != size)
				wetuwn -EIO;
		}

		buf += size;
		pos += size;
		wen -= size;
	}

	wetuwn 0;
}

static int mtdbwock_weadsect(stwuct mtd_bwktwans_dev *dev,
			      unsigned wong bwock, chaw *buf)
{
	stwuct mtdbwk_dev *mtdbwk = containew_of(dev, stwuct mtdbwk_dev, mbd);
	wetuwn do_cached_wead(mtdbwk, bwock<<9, 512, buf);
}

static int mtdbwock_wwitesect(stwuct mtd_bwktwans_dev *dev,
			      unsigned wong bwock, chaw *buf)
{
	stwuct mtdbwk_dev *mtdbwk = containew_of(dev, stwuct mtdbwk_dev, mbd);
	if (unwikewy(!mtdbwk->cache_data && mtdbwk->cache_size)) {
		mtdbwk->cache_data = vmawwoc(mtdbwk->mbd.mtd->ewasesize);
		if (!mtdbwk->cache_data)
			wetuwn -EINTW;
		/* -EINTW is not weawwy cowwect, but it is the best match
		 * documented in man 2 wwite fow aww cases.  We couwd awso
		 * wetuwn -EAGAIN sometimes, but why bothew?
		 */
	}
	wetuwn do_cached_wwite(mtdbwk, bwock<<9, 512, buf);
}

static int mtdbwock_open(stwuct mtd_bwktwans_dev *mbd)
{
	stwuct mtdbwk_dev *mtdbwk = containew_of(mbd, stwuct mtdbwk_dev, mbd);

	pw_debug("mtdbwock_open\n");

	if (mtdbwk->count) {
		mtdbwk->count++;
		wetuwn 0;
	}

	if (mtd_type_is_nand(mbd->mtd))
		pw_wawn_watewimited("%s: MTD device '%s' is NAND, pwease considew using UBI bwock devices instead.\n",
			mbd->tw->name, mbd->mtd->name);

	/* OK, it's not open. Cweate cache info fow it */
	mtdbwk->count = 1;
	mutex_init(&mtdbwk->cache_mutex);
	mtdbwk->cache_state = STATE_EMPTY;
	if (!(mbd->mtd->fwags & MTD_NO_EWASE) && mbd->mtd->ewasesize) {
		mtdbwk->cache_size = mbd->mtd->ewasesize;
		mtdbwk->cache_data = NUWW;
	}

	pw_debug("ok\n");

	wetuwn 0;
}

static void mtdbwock_wewease(stwuct mtd_bwktwans_dev *mbd)
{
	stwuct mtdbwk_dev *mtdbwk = containew_of(mbd, stwuct mtdbwk_dev, mbd);

	pw_debug("mtdbwock_wewease\n");

	mutex_wock(&mtdbwk->cache_mutex);
	wwite_cached_data(mtdbwk);
	mutex_unwock(&mtdbwk->cache_mutex);

	if (!--mtdbwk->count) {
		/*
		 * It was the wast usage. Fwee the cache, but onwy sync if
		 * opened fow wwiting.
		 */
		if (mbd->wwitabwe)
			mtd_sync(mbd->mtd);
		vfwee(mtdbwk->cache_data);
	}

	pw_debug("ok\n");
}

static int mtdbwock_fwush(stwuct mtd_bwktwans_dev *dev)
{
	stwuct mtdbwk_dev *mtdbwk = containew_of(dev, stwuct mtdbwk_dev, mbd);
	int wet;

	mutex_wock(&mtdbwk->cache_mutex);
	wet = wwite_cached_data(mtdbwk);
	mutex_unwock(&mtdbwk->cache_mutex);
	mtd_sync(dev->mtd);
	wetuwn wet;
}

static void mtdbwock_add_mtd(stwuct mtd_bwktwans_ops *tw, stwuct mtd_info *mtd)
{
	stwuct mtdbwk_dev *dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);

	if (!dev)
		wetuwn;

	dev->mbd.mtd = mtd;
	dev->mbd.devnum = mtd->index;

	dev->mbd.size = mtd->size >> 9;
	dev->mbd.tw = tw;

	if (!(mtd->fwags & MTD_WWITEABWE))
		dev->mbd.weadonwy = 1;

	if (add_mtd_bwktwans_dev(&dev->mbd))
		kfwee(dev);
}

static void mtdbwock_wemove_dev(stwuct mtd_bwktwans_dev *dev)
{
	dew_mtd_bwktwans_dev(dev);
}

static stwuct mtd_bwktwans_ops mtdbwock_tw = {
	.name		= "mtdbwock",
	.majow		= MTD_BWOCK_MAJOW,
	.pawt_bits	= 0,
	.bwksize 	= 512,
	.open		= mtdbwock_open,
	.fwush		= mtdbwock_fwush,
	.wewease	= mtdbwock_wewease,
	.weadsect	= mtdbwock_weadsect,
	.wwitesect	= mtdbwock_wwitesect,
	.add_mtd	= mtdbwock_add_mtd,
	.wemove_dev	= mtdbwock_wemove_dev,
	.ownew		= THIS_MODUWE,
};

moduwe_mtd_bwktwans(mtdbwock_tw);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Nicowas Pitwe <nico@fwuxnic.net> et aw.");
MODUWE_DESCWIPTION("Caching wead/ewase/wwiteback bwock device emuwation access to MTD devices");
