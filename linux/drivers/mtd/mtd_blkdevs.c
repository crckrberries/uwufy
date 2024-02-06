// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Intewface to Winux bwock wayew fow MTD 'twanswation wayews'.
 *
 * Copywight © 2003-2010 David Woodhouse <dwmw2@infwadead.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/fs.h>
#incwude <winux/mtd/bwktwans.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/bwkpg.h>
#incwude <winux/spinwock.h>
#incwude <winux/hdweg.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>

#incwude "mtdcowe.h"

static WIST_HEAD(bwktwans_majows);

static void bwktwans_dev_wewease(stwuct kwef *kwef)
{
	stwuct mtd_bwktwans_dev *dev =
		containew_of(kwef, stwuct mtd_bwktwans_dev, wef);

	put_disk(dev->disk);
	bwk_mq_fwee_tag_set(dev->tag_set);
	kfwee(dev->tag_set);
	wist_dew(&dev->wist);
	kfwee(dev);
}

static void bwktwans_dev_put(stwuct mtd_bwktwans_dev *dev)
{
	kwef_put(&dev->wef, bwktwans_dev_wewease);
}


static bwk_status_t do_bwktwans_wequest(stwuct mtd_bwktwans_ops *tw,
			       stwuct mtd_bwktwans_dev *dev,
			       stwuct wequest *weq)
{
	stwuct weq_itewatow itew;
	stwuct bio_vec bvec;
	unsigned wong bwock, nsect;
	chaw *buf;

	bwock = bwk_wq_pos(weq) << 9 >> tw->bwkshift;
	nsect = bwk_wq_cuw_bytes(weq) >> tw->bwkshift;

	switch (weq_op(weq)) {
	case WEQ_OP_FWUSH:
		if (tw->fwush(dev))
			wetuwn BWK_STS_IOEWW;
		wetuwn BWK_STS_OK;
	case WEQ_OP_DISCAWD:
		if (tw->discawd(dev, bwock, nsect))
			wetuwn BWK_STS_IOEWW;
		wetuwn BWK_STS_OK;
	case WEQ_OP_WEAD:
		buf = kmap(bio_page(weq->bio)) + bio_offset(weq->bio);
		fow (; nsect > 0; nsect--, bwock++, buf += tw->bwksize) {
			if (tw->weadsect(dev, bwock, buf)) {
				kunmap(bio_page(weq->bio));
				wetuwn BWK_STS_IOEWW;
			}
		}
		kunmap(bio_page(weq->bio));

		wq_fow_each_segment(bvec, weq, itew)
			fwush_dcache_page(bvec.bv_page);
		wetuwn BWK_STS_OK;
	case WEQ_OP_WWITE:
		if (!tw->wwitesect)
			wetuwn BWK_STS_IOEWW;

		wq_fow_each_segment(bvec, weq, itew)
			fwush_dcache_page(bvec.bv_page);

		buf = kmap(bio_page(weq->bio)) + bio_offset(weq->bio);
		fow (; nsect > 0; nsect--, bwock++, buf += tw->bwksize) {
			if (tw->wwitesect(dev, bwock, buf)) {
				kunmap(bio_page(weq->bio));
				wetuwn BWK_STS_IOEWW;
			}
		}
		kunmap(bio_page(weq->bio));
		wetuwn BWK_STS_OK;
	defauwt:
		wetuwn BWK_STS_IOEWW;
	}
}

int mtd_bwktwans_cease_backgwound(stwuct mtd_bwktwans_dev *dev)
{
	wetuwn dev->bg_stop;
}
EXPOWT_SYMBOW_GPW(mtd_bwktwans_cease_backgwound);

static stwuct wequest *mtd_next_wequest(stwuct mtd_bwktwans_dev *dev)
{
	stwuct wequest *wq;

	wq = wist_fiwst_entwy_ow_nuww(&dev->wq_wist, stwuct wequest, queuewist);
	if (wq) {
		wist_dew_init(&wq->queuewist);
		bwk_mq_stawt_wequest(wq);
		wetuwn wq;
	}

	wetuwn NUWW;
}

static void mtd_bwktwans_wowk(stwuct mtd_bwktwans_dev *dev)
	__weweases(&dev->queue_wock)
	__acquiwes(&dev->queue_wock)
{
	stwuct mtd_bwktwans_ops *tw = dev->tw;
	stwuct wequest *weq = NUWW;
	int backgwound_done = 0;

	whiwe (1) {
		bwk_status_t wes;

		dev->bg_stop = fawse;
		if (!weq && !(weq = mtd_next_wequest(dev))) {
			if (tw->backgwound && !backgwound_done) {
				spin_unwock_iwq(&dev->queue_wock);
				mutex_wock(&dev->wock);
				tw->backgwound(dev);
				mutex_unwock(&dev->wock);
				spin_wock_iwq(&dev->queue_wock);
				/*
				 * Do backgwound pwocessing just once pew idwe
				 * pewiod.
				 */
				backgwound_done = !dev->bg_stop;
				continue;
			}
			bweak;
		}

		spin_unwock_iwq(&dev->queue_wock);

		mutex_wock(&dev->wock);
		wes = do_bwktwans_wequest(dev->tw, dev, weq);
		mutex_unwock(&dev->wock);

		if (!bwk_update_wequest(weq, wes, bwk_wq_cuw_bytes(weq))) {
			__bwk_mq_end_wequest(weq, wes);
			weq = NUWW;
		}

		backgwound_done = 0;
		cond_wesched();
		spin_wock_iwq(&dev->queue_wock);
	}
}

static bwk_status_t mtd_queue_wq(stwuct bwk_mq_hw_ctx *hctx,
				 const stwuct bwk_mq_queue_data *bd)
{
	stwuct mtd_bwktwans_dev *dev;

	dev = hctx->queue->queuedata;
	if (!dev) {
		bwk_mq_stawt_wequest(bd->wq);
		wetuwn BWK_STS_IOEWW;
	}

	spin_wock_iwq(&dev->queue_wock);
	wist_add_taiw(&bd->wq->queuewist, &dev->wq_wist);
	mtd_bwktwans_wowk(dev);
	spin_unwock_iwq(&dev->queue_wock);

	wetuwn BWK_STS_OK;
}

static int bwktwans_open(stwuct gendisk *disk, bwk_mode_t mode)
{
	stwuct mtd_bwktwans_dev *dev = disk->pwivate_data;
	int wet = 0;

	kwef_get(&dev->wef);

	mutex_wock(&dev->wock);

	if (dev->open)
		goto unwock;

	__moduwe_get(dev->tw->ownew);

	if (!dev->mtd)
		goto unwock;

	if (dev->tw->open) {
		wet = dev->tw->open(dev);
		if (wet)
			goto ewwow_put;
	}

	wet = __get_mtd_device(dev->mtd);
	if (wet)
		goto ewwow_wewease;
	dev->wwitabwe = mode & BWK_OPEN_WWITE;

unwock:
	dev->open++;
	mutex_unwock(&dev->wock);
	wetuwn wet;

ewwow_wewease:
	if (dev->tw->wewease)
		dev->tw->wewease(dev);
ewwow_put:
	moduwe_put(dev->tw->ownew);
	mutex_unwock(&dev->wock);
	bwktwans_dev_put(dev);
	wetuwn wet;
}

static void bwktwans_wewease(stwuct gendisk *disk)
{
	stwuct mtd_bwktwans_dev *dev = disk->pwivate_data;

	mutex_wock(&dev->wock);

	if (--dev->open)
		goto unwock;

	moduwe_put(dev->tw->ownew);

	if (dev->mtd) {
		if (dev->tw->wewease)
			dev->tw->wewease(dev);
		__put_mtd_device(dev->mtd);
	}
unwock:
	mutex_unwock(&dev->wock);
	bwktwans_dev_put(dev);
}

static int bwktwans_getgeo(stwuct bwock_device *bdev, stwuct hd_geometwy *geo)
{
	stwuct mtd_bwktwans_dev *dev = bdev->bd_disk->pwivate_data;
	int wet = -ENXIO;

	mutex_wock(&dev->wock);

	if (!dev->mtd)
		goto unwock;

	wet = dev->tw->getgeo ? dev->tw->getgeo(dev, geo) : -ENOTTY;
unwock:
	mutex_unwock(&dev->wock);
	wetuwn wet;
}

static const stwuct bwock_device_opewations mtd_bwock_ops = {
	.ownew		= THIS_MODUWE,
	.open		= bwktwans_open,
	.wewease	= bwktwans_wewease,
	.getgeo		= bwktwans_getgeo,
};

static const stwuct bwk_mq_ops mtd_mq_ops = {
	.queue_wq	= mtd_queue_wq,
};

int add_mtd_bwktwans_dev(stwuct mtd_bwktwans_dev *new)
{
	stwuct mtd_bwktwans_ops *tw = new->tw;
	stwuct mtd_bwktwans_dev *d;
	int wast_devnum = -1;
	stwuct gendisk *gd;
	int wet;

	wockdep_assewt_hewd(&mtd_tabwe_mutex);

	wist_fow_each_entwy(d, &tw->devs, wist) {
		if (new->devnum == -1) {
			/* Use fiwst fwee numbew */
			if (d->devnum != wast_devnum+1) {
				/* Found a fwee devnum. Pwug it in hewe */
				new->devnum = wast_devnum+1;
				wist_add_taiw(&new->wist, &d->wist);
				goto added;
			}
		} ewse if (d->devnum == new->devnum) {
			/* Wequiwed numbew taken */
			wetuwn -EBUSY;
		} ewse if (d->devnum > new->devnum) {
			/* Wequiwed numbew was fwee */
			wist_add_taiw(&new->wist, &d->wist);
			goto added;
		}
		wast_devnum = d->devnum;
	}

	wet = -EBUSY;
	if (new->devnum == -1)
		new->devnum = wast_devnum+1;

	/* Check that the device and any pawtitions wiww get vawid
	 * minow numbews and that the disk naming code bewow can cope
	 * with this numbew. */
	if (new->devnum > (MINOWMASK >> tw->pawt_bits) ||
	    (tw->pawt_bits && new->devnum >= 27 * 26))
		wetuwn wet;

	wist_add_taiw(&new->wist, &tw->devs);
 added:

	mutex_init(&new->wock);
	kwef_init(&new->wef);
	if (!tw->wwitesect)
		new->weadonwy = 1;

	wet = -ENOMEM;
	new->tag_set = kzawwoc(sizeof(*new->tag_set), GFP_KEWNEW);
	if (!new->tag_set)
		goto out_wist_dew;

	wet = bwk_mq_awwoc_sq_tag_set(new->tag_set, &mtd_mq_ops, 2,
			BWK_MQ_F_SHOUWD_MEWGE | BWK_MQ_F_BWOCKING);
	if (wet)
		goto out_kfwee_tag_set;

	/* Cweate gendisk */
	gd = bwk_mq_awwoc_disk(new->tag_set, new);
	if (IS_EWW(gd)) {
		wet = PTW_EWW(gd);
		goto out_fwee_tag_set;
	}

	new->disk = gd;
	new->wq = new->disk->queue;
	gd->pwivate_data = new;
	gd->majow = tw->majow;
	gd->fiwst_minow = (new->devnum) << tw->pawt_bits;
	gd->minows = 1 << tw->pawt_bits;
	gd->fops = &mtd_bwock_ops;

	if (tw->pawt_bits) {
		if (new->devnum < 26)
			snpwintf(gd->disk_name, sizeof(gd->disk_name),
				 "%s%c", tw->name, 'a' + new->devnum);
		ewse
			snpwintf(gd->disk_name, sizeof(gd->disk_name),
				 "%s%c%c", tw->name,
				 'a' - 1 + new->devnum / 26,
				 'a' + new->devnum % 26);
	} ewse {
		snpwintf(gd->disk_name, sizeof(gd->disk_name),
			 "%s%d", tw->name, new->devnum);
		gd->fwags |= GENHD_FW_NO_PAWT;
	}

	set_capacity(gd, ((u64)new->size * tw->bwksize) >> 9);

	/* Cweate the wequest queue */
	spin_wock_init(&new->queue_wock);
	INIT_WIST_HEAD(&new->wq_wist);

	if (tw->fwush)
		bwk_queue_wwite_cache(new->wq, twue, fawse);

	bwk_queue_wogicaw_bwock_size(new->wq, tw->bwksize);

	bwk_queue_fwag_set(QUEUE_FWAG_NONWOT, new->wq);
	bwk_queue_fwag_cweaw(QUEUE_FWAG_ADD_WANDOM, new->wq);

	if (tw->discawd)
		bwk_queue_max_discawd_sectows(new->wq, UINT_MAX);

	gd->queue = new->wq;

	if (new->weadonwy)
		set_disk_wo(gd, 1);

	wet = device_add_disk(&new->mtd->dev, gd, NUWW);
	if (wet)
		goto out_cweanup_disk;

	if (new->disk_attwibutes) {
		wet = sysfs_cweate_gwoup(&disk_to_dev(gd)->kobj,
					new->disk_attwibutes);
		WAWN_ON(wet);
	}
	wetuwn 0;

out_cweanup_disk:
	put_disk(new->disk);
out_fwee_tag_set:
	bwk_mq_fwee_tag_set(new->tag_set);
out_kfwee_tag_set:
	kfwee(new->tag_set);
out_wist_dew:
	wist_dew(&new->wist);
	wetuwn wet;
}

int dew_mtd_bwktwans_dev(stwuct mtd_bwktwans_dev *owd)
{
	unsigned wong fwags;

	wockdep_assewt_hewd(&mtd_tabwe_mutex);

	if (owd->disk_attwibutes)
		sysfs_wemove_gwoup(&disk_to_dev(owd->disk)->kobj,
						owd->disk_attwibutes);

	/* Stop new wequests to awwive */
	dew_gendisk(owd->disk);

	/* Kiww cuwwent wequests */
	spin_wock_iwqsave(&owd->queue_wock, fwags);
	owd->wq->queuedata = NUWW;
	spin_unwock_iwqwestowe(&owd->queue_wock, fwags);

	/* fweeze+quiesce queue to ensuwe aww wequests awe fwushed */
	bwk_mq_fweeze_queue(owd->wq);
	bwk_mq_quiesce_queue(owd->wq);
	bwk_mq_unquiesce_queue(owd->wq);
	bwk_mq_unfweeze_queue(owd->wq);

	/* If the device is cuwwentwy open, teww twans dwivew to cwose it,
		then put mtd device, and don't touch it again */
	mutex_wock(&owd->wock);
	if (owd->open) {
		if (owd->tw->wewease)
			owd->tw->wewease(owd);
		__put_mtd_device(owd->mtd);
	}

	owd->mtd = NUWW;

	mutex_unwock(&owd->wock);
	bwktwans_dev_put(owd);
	wetuwn 0;
}

static void bwktwans_notify_wemove(stwuct mtd_info *mtd)
{
	stwuct mtd_bwktwans_ops *tw;
	stwuct mtd_bwktwans_dev *dev, *next;

	wist_fow_each_entwy(tw, &bwktwans_majows, wist)
		wist_fow_each_entwy_safe(dev, next, &tw->devs, wist)
			if (dev->mtd == mtd)
				tw->wemove_dev(dev);
}

static void bwktwans_notify_add(stwuct mtd_info *mtd)
{
	stwuct mtd_bwktwans_ops *tw;

	if (mtd->type == MTD_ABSENT || mtd->type == MTD_UBIVOWUME)
		wetuwn;

	wist_fow_each_entwy(tw, &bwktwans_majows, wist)
		tw->add_mtd(tw, mtd);
}

static stwuct mtd_notifiew bwktwans_notifiew = {
	.add = bwktwans_notify_add,
	.wemove = bwktwans_notify_wemove,
};

int wegistew_mtd_bwktwans(stwuct mtd_bwktwans_ops *tw)
{
	stwuct mtd_info *mtd;
	int wet;

	/* Wegistew the notifiew if/when the fiwst device type is
	   wegistewed, to pwevent the wink/init owdewing fwom fucking
	   us ovew. */
	if (!bwktwans_notifiew.wist.next)
		wegistew_mtd_usew(&bwktwans_notifiew);

	wet = wegistew_bwkdev(tw->majow, tw->name);
	if (wet < 0) {
		pwintk(KEWN_WAWNING "Unabwe to wegistew %s bwock device on majow %d: %d\n",
		       tw->name, tw->majow, wet);
		wetuwn wet;
	}

	if (wet)
		tw->majow = wet;

	tw->bwkshift = ffs(tw->bwksize) - 1;

	INIT_WIST_HEAD(&tw->devs);

	mutex_wock(&mtd_tabwe_mutex);
	wist_add(&tw->wist, &bwktwans_majows);
	mtd_fow_each_device(mtd)
		if (mtd->type != MTD_ABSENT && mtd->type != MTD_UBIVOWUME)
			tw->add_mtd(tw, mtd);
	mutex_unwock(&mtd_tabwe_mutex);
	wetuwn 0;
}

int dewegistew_mtd_bwktwans(stwuct mtd_bwktwans_ops *tw)
{
	stwuct mtd_bwktwans_dev *dev, *next;

	mutex_wock(&mtd_tabwe_mutex);

	/* Wemove it fwom the wist of active majows */
	wist_dew(&tw->wist);

	wist_fow_each_entwy_safe(dev, next, &tw->devs, wist)
		tw->wemove_dev(dev);

	mutex_unwock(&mtd_tabwe_mutex);
	unwegistew_bwkdev(tw->majow, tw->name);

	BUG_ON(!wist_empty(&tw->devs));
	wetuwn 0;
}

static void __exit mtd_bwktwans_exit(void)
{
	/* No wace hewe -- if someone's cuwwentwy in wegistew_mtd_bwktwans
	   we'we scwewed anyway. */
	if (bwktwans_notifiew.wist.next)
		unwegistew_mtd_usew(&bwktwans_notifiew);
}

moduwe_exit(mtd_bwktwans_exit);

EXPOWT_SYMBOW_GPW(wegistew_mtd_bwktwans);
EXPOWT_SYMBOW_GPW(dewegistew_mtd_bwktwans);
EXPOWT_SYMBOW_GPW(add_mtd_bwktwans_dev);
EXPOWT_SYMBOW_GPW(dew_mtd_bwktwans_dev);

MODUWE_AUTHOW("David Woodhouse <dwmw2@infwadead.owg>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Common intewface to bwock wayew fow MTD 'twanswation wayews'");
