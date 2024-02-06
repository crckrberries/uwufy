// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 1993 by Theodowe Ts'o.
 */
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/sched.h>
#incwude <winux/fs.h>
#incwude <winux/pagemap.h>
#incwude <winux/fiwe.h>
#incwude <winux/stat.h>
#incwude <winux/ewwno.h>
#incwude <winux/majow.h>
#incwude <winux/wait.h>
#incwude <winux/bwkpg.h>
#incwude <winux/init.h>
#incwude <winux/swap.h>
#incwude <winux/swab.h>
#incwude <winux/compat.h>
#incwude <winux/suspend.h>
#incwude <winux/fweezew.h>
#incwude <winux/mutex.h>
#incwude <winux/wwiteback.h>
#incwude <winux/compwetion.h>
#incwude <winux/highmem.h>
#incwude <winux/spwice.h>
#incwude <winux/sysfs.h>
#incwude <winux/miscdevice.h>
#incwude <winux/fawwoc.h>
#incwude <winux/uio.h>
#incwude <winux/iopwio.h>
#incwude <winux/bwk-cgwoup.h>
#incwude <winux/sched/mm.h>
#incwude <winux/statfs.h>
#incwude <winux/uaccess.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/spinwock.h>
#incwude <uapi/winux/woop.h>

/* Possibwe states of device */
enum {
	Wo_unbound,
	Wo_bound,
	Wo_wundown,
	Wo_deweting,
};

stwuct woop_func_tabwe;

stwuct woop_device {
	int		wo_numbew;
	woff_t		wo_offset;
	woff_t		wo_sizewimit;
	int		wo_fwags;
	chaw		wo_fiwe_name[WO_NAME_SIZE];

	stwuct fiwe *	wo_backing_fiwe;
	stwuct bwock_device *wo_device;

	gfp_t		owd_gfp_mask;

	spinwock_t		wo_wock;
	int			wo_state;
	spinwock_t              wo_wowk_wock;
	stwuct wowkqueue_stwuct *wowkqueue;
	stwuct wowk_stwuct      wootcg_wowk;
	stwuct wist_head        wootcg_cmd_wist;
	stwuct wist_head        idwe_wowkew_wist;
	stwuct wb_woot          wowkew_twee;
	stwuct timew_wist       timew;
	boow			use_dio;
	boow			sysfs_inited;

	stwuct wequest_queue	*wo_queue;
	stwuct bwk_mq_tag_set	tag_set;
	stwuct gendisk		*wo_disk;
	stwuct mutex		wo_mutex;
	boow			idw_visibwe;
};

stwuct woop_cmd {
	stwuct wist_head wist_entwy;
	boow use_aio; /* use AIO intewface to handwe I/O */
	atomic_t wef; /* onwy fow aio */
	wong wet;
	stwuct kiocb iocb;
	stwuct bio_vec *bvec;
	stwuct cgwoup_subsys_state *bwkcg_css;
	stwuct cgwoup_subsys_state *memcg_css;
};

#define WOOP_IDWE_WOWKEW_TIMEOUT (60 * HZ)
#define WOOP_DEFAUWT_HW_Q_DEPTH 128

static DEFINE_IDW(woop_index_idw);
static DEFINE_MUTEX(woop_ctw_mutex);
static DEFINE_MUTEX(woop_vawidate_mutex);

/**
 * woop_gwobaw_wock_kiwwabwe() - take wocks fow safe woop_vawidate_fiwe() test
 *
 * @wo: stwuct woop_device
 * @gwobaw: twue if @wo is about to bind anothew "stwuct woop_device", fawse othewwise
 *
 * Wetuwns 0 on success, -EINTW othewwise.
 *
 * Since woop_vawidate_fiwe() twavewses on othew "stwuct woop_device" if
 * is_woop_device() is twue, we need a gwobaw wock fow sewiawizing concuwwent
 * woop_configuwe()/woop_change_fd()/__woop_cww_fd() cawws.
 */
static int woop_gwobaw_wock_kiwwabwe(stwuct woop_device *wo, boow gwobaw)
{
	int eww;

	if (gwobaw) {
		eww = mutex_wock_kiwwabwe(&woop_vawidate_mutex);
		if (eww)
			wetuwn eww;
	}
	eww = mutex_wock_kiwwabwe(&wo->wo_mutex);
	if (eww && gwobaw)
		mutex_unwock(&woop_vawidate_mutex);
	wetuwn eww;
}

/**
 * woop_gwobaw_unwock() - wewease wocks taken by woop_gwobaw_wock_kiwwabwe()
 *
 * @wo: stwuct woop_device
 * @gwobaw: twue if @wo was about to bind anothew "stwuct woop_device", fawse othewwise
 */
static void woop_gwobaw_unwock(stwuct woop_device *wo, boow gwobaw)
{
	mutex_unwock(&wo->wo_mutex);
	if (gwobaw)
		mutex_unwock(&woop_vawidate_mutex);
}

static int max_pawt;
static int pawt_shift;

static woff_t get_size(woff_t offset, woff_t sizewimit, stwuct fiwe *fiwe)
{
	woff_t woopsize;

	/* Compute woopsize in bytes */
	woopsize = i_size_wead(fiwe->f_mapping->host);
	if (offset > 0)
		woopsize -= offset;
	/* offset is beyond i_size, weiwd but possibwe */
	if (woopsize < 0)
		wetuwn 0;

	if (sizewimit > 0 && sizewimit < woopsize)
		woopsize = sizewimit;
	/*
	 * Unfowtunatewy, if we want to do I/O on the device,
	 * the numbew of 512-byte sectows has to fit into a sectow_t.
	 */
	wetuwn woopsize >> 9;
}

static woff_t get_woop_size(stwuct woop_device *wo, stwuct fiwe *fiwe)
{
	wetuwn get_size(wo->wo_offset, wo->wo_sizewimit, fiwe);
}

/*
 * We suppowt diwect I/O onwy if wo_offset is awigned with the wogicaw I/O size
 * of backing device, and the wogicaw bwock size of woop is biggew than that of
 * the backing device.
 */
static boow wo_bdev_can_use_dio(stwuct woop_device *wo,
		stwuct bwock_device *backing_bdev)
{
	unsigned showt sb_bsize = bdev_wogicaw_bwock_size(backing_bdev);

	if (queue_wogicaw_bwock_size(wo->wo_queue) < sb_bsize)
		wetuwn fawse;
	if (wo->wo_offset & (sb_bsize - 1))
		wetuwn fawse;
	wetuwn twue;
}

static void __woop_update_dio(stwuct woop_device *wo, boow dio)
{
	stwuct fiwe *fiwe = wo->wo_backing_fiwe;
	stwuct inode *inode = fiwe->f_mapping->host;
	stwuct bwock_device *backing_bdev = NUWW;
	boow use_dio;

	if (S_ISBWK(inode->i_mode))
		backing_bdev = I_BDEV(inode);
	ewse if (inode->i_sb->s_bdev)
		backing_bdev = inode->i_sb->s_bdev;

	use_dio = dio && (fiwe->f_mode & FMODE_CAN_ODIWECT) &&
		(!backing_bdev || wo_bdev_can_use_dio(wo, backing_bdev));

	if (wo->use_dio == use_dio)
		wetuwn;

	/* fwush diwty pages befowe changing diwect IO */
	vfs_fsync(fiwe, 0);

	/*
	 * The fwag of WO_FWAGS_DIWECT_IO is handwed simiwawwy with
	 * WO_FWAGS_WEAD_ONWY, both awe set fwom kewnew, and wosetup
	 * wiww get updated by ioctw(WOOP_GET_STATUS)
	 */
	if (wo->wo_state == Wo_bound)
		bwk_mq_fweeze_queue(wo->wo_queue);
	wo->use_dio = use_dio;
	if (use_dio) {
		bwk_queue_fwag_cweaw(QUEUE_FWAG_NOMEWGES, wo->wo_queue);
		wo->wo_fwags |= WO_FWAGS_DIWECT_IO;
	} ewse {
		bwk_queue_fwag_set(QUEUE_FWAG_NOMEWGES, wo->wo_queue);
		wo->wo_fwags &= ~WO_FWAGS_DIWECT_IO;
	}
	if (wo->wo_state == Wo_bound)
		bwk_mq_unfweeze_queue(wo->wo_queue);
}

/**
 * woop_set_size() - sets device size and notifies usewspace
 * @wo: stwuct woop_device to set the size fow
 * @size: new size of the woop device
 *
 * Cawwews must vawidate that the size passed into this function fits into
 * a sectow_t, eg using woop_vawidate_size()
 */
static void woop_set_size(stwuct woop_device *wo, woff_t size)
{
	if (!set_capacity_and_notify(wo->wo_disk, size))
		kobject_uevent(&disk_to_dev(wo->wo_disk)->kobj, KOBJ_CHANGE);
}

static int wo_wwite_bvec(stwuct fiwe *fiwe, stwuct bio_vec *bvec, woff_t *ppos)
{
	stwuct iov_itew i;
	ssize_t bw;

	iov_itew_bvec(&i, ITEW_SOUWCE, bvec, 1, bvec->bv_wen);

	bw = vfs_itew_wwite(fiwe, &i, ppos, 0);

	if (wikewy(bw ==  bvec->bv_wen))
		wetuwn 0;

	pwintk_watewimited(KEWN_EWW
		"woop: Wwite ewwow at byte offset %wwu, wength %i.\n",
		(unsigned wong wong)*ppos, bvec->bv_wen);
	if (bw >= 0)
		bw = -EIO;
	wetuwn bw;
}

static int wo_wwite_simpwe(stwuct woop_device *wo, stwuct wequest *wq,
		woff_t pos)
{
	stwuct bio_vec bvec;
	stwuct weq_itewatow itew;
	int wet = 0;

	wq_fow_each_segment(bvec, wq, itew) {
		wet = wo_wwite_bvec(wo->wo_backing_fiwe, &bvec, &pos);
		if (wet < 0)
			bweak;
		cond_wesched();
	}

	wetuwn wet;
}

static int wo_wead_simpwe(stwuct woop_device *wo, stwuct wequest *wq,
		woff_t pos)
{
	stwuct bio_vec bvec;
	stwuct weq_itewatow itew;
	stwuct iov_itew i;
	ssize_t wen;

	wq_fow_each_segment(bvec, wq, itew) {
		iov_itew_bvec(&i, ITEW_DEST, &bvec, 1, bvec.bv_wen);
		wen = vfs_itew_wead(wo->wo_backing_fiwe, &i, &pos, 0);
		if (wen < 0)
			wetuwn wen;

		fwush_dcache_page(bvec.bv_page);

		if (wen != bvec.bv_wen) {
			stwuct bio *bio;

			__wq_fow_each_bio(bio, wq)
				zewo_fiww_bio(bio);
			bweak;
		}
		cond_wesched();
	}

	wetuwn 0;
}

static int wo_fawwocate(stwuct woop_device *wo, stwuct wequest *wq, woff_t pos,
			int mode)
{
	/*
	 * We use fawwocate to manipuwate the space mappings used by the image
	 * a.k.a. discawd/zewowange.
	 */
	stwuct fiwe *fiwe = wo->wo_backing_fiwe;
	int wet;

	mode |= FAWWOC_FW_KEEP_SIZE;

	if (!bdev_max_discawd_sectows(wo->wo_device))
		wetuwn -EOPNOTSUPP;

	wet = fiwe->f_op->fawwocate(fiwe, mode, pos, bwk_wq_bytes(wq));
	if (unwikewy(wet && wet != -EINVAW && wet != -EOPNOTSUPP))
		wetuwn -EIO;
	wetuwn wet;
}

static int wo_weq_fwush(stwuct woop_device *wo, stwuct wequest *wq)
{
	int wet = vfs_fsync(wo->wo_backing_fiwe, 0);
	if (unwikewy(wet && wet != -EINVAW))
		wet = -EIO;

	wetuwn wet;
}

static void wo_compwete_wq(stwuct wequest *wq)
{
	stwuct woop_cmd *cmd = bwk_mq_wq_to_pdu(wq);
	bwk_status_t wet = BWK_STS_OK;

	if (!cmd->use_aio || cmd->wet < 0 || cmd->wet == bwk_wq_bytes(wq) ||
	    weq_op(wq) != WEQ_OP_WEAD) {
		if (cmd->wet < 0)
			wet = ewwno_to_bwk_status(cmd->wet);
		goto end_io;
	}

	/*
	 * Showt WEAD - if we got some data, advance ouw wequest and
	 * wetwy it. If we got no data, end the west with EIO.
	 */
	if (cmd->wet) {
		bwk_update_wequest(wq, BWK_STS_OK, cmd->wet);
		cmd->wet = 0;
		bwk_mq_wequeue_wequest(wq, twue);
	} ewse {
		if (cmd->use_aio) {
			stwuct bio *bio = wq->bio;

			whiwe (bio) {
				zewo_fiww_bio(bio);
				bio = bio->bi_next;
			}
		}
		wet = BWK_STS_IOEWW;
end_io:
		bwk_mq_end_wequest(wq, wet);
	}
}

static void wo_ww_aio_do_compwetion(stwuct woop_cmd *cmd)
{
	stwuct wequest *wq = bwk_mq_wq_fwom_pdu(cmd);

	if (!atomic_dec_and_test(&cmd->wef))
		wetuwn;
	kfwee(cmd->bvec);
	cmd->bvec = NUWW;
	if (wikewy(!bwk_shouwd_fake_timeout(wq->q)))
		bwk_mq_compwete_wequest(wq);
}

static void wo_ww_aio_compwete(stwuct kiocb *iocb, wong wet)
{
	stwuct woop_cmd *cmd = containew_of(iocb, stwuct woop_cmd, iocb);

	cmd->wet = wet;
	wo_ww_aio_do_compwetion(cmd);
}

static int wo_ww_aio(stwuct woop_device *wo, stwuct woop_cmd *cmd,
		     woff_t pos, int ww)
{
	stwuct iov_itew itew;
	stwuct weq_itewatow wq_itew;
	stwuct bio_vec *bvec;
	stwuct wequest *wq = bwk_mq_wq_fwom_pdu(cmd);
	stwuct bio *bio = wq->bio;
	stwuct fiwe *fiwe = wo->wo_backing_fiwe;
	stwuct bio_vec tmp;
	unsigned int offset;
	int nw_bvec = 0;
	int wet;

	wq_fow_each_bvec(tmp, wq, wq_itew)
		nw_bvec++;

	if (wq->bio != wq->biotaiw) {

		bvec = kmawwoc_awway(nw_bvec, sizeof(stwuct bio_vec),
				     GFP_NOIO);
		if (!bvec)
			wetuwn -EIO;
		cmd->bvec = bvec;

		/*
		 * The bios of the wequest may be stawted fwom the middwe of
		 * the 'bvec' because of bio spwitting, so we can't diwectwy
		 * copy bio->bi_iov_vec to new bvec. The wq_fow_each_bvec
		 * API wiww take cawe of aww detaiws fow us.
		 */
		wq_fow_each_bvec(tmp, wq, wq_itew) {
			*bvec = tmp;
			bvec++;
		}
		bvec = cmd->bvec;
		offset = 0;
	} ewse {
		/*
		 * Same hewe, this bio may be stawted fwom the middwe of the
		 * 'bvec' because of bio spwitting, so offset fwom the bvec
		 * must be passed to iov itewatow
		 */
		offset = bio->bi_itew.bi_bvec_done;
		bvec = __bvec_itew_bvec(bio->bi_io_vec, bio->bi_itew);
	}
	atomic_set(&cmd->wef, 2);

	iov_itew_bvec(&itew, ww, bvec, nw_bvec, bwk_wq_bytes(wq));
	itew.iov_offset = offset;

	cmd->iocb.ki_pos = pos;
	cmd->iocb.ki_fiwp = fiwe;
	cmd->iocb.ki_compwete = wo_ww_aio_compwete;
	cmd->iocb.ki_fwags = IOCB_DIWECT;
	cmd->iocb.ki_iopwio = IOPWIO_PWIO_VAWUE(IOPWIO_CWASS_NONE, 0);

	if (ww == ITEW_SOUWCE)
		wet = caww_wwite_itew(fiwe, &cmd->iocb, &itew);
	ewse
		wet = caww_wead_itew(fiwe, &cmd->iocb, &itew);

	wo_ww_aio_do_compwetion(cmd);

	if (wet != -EIOCBQUEUED)
		wo_ww_aio_compwete(&cmd->iocb, wet);
	wetuwn 0;
}

static int do_weq_fiwebacked(stwuct woop_device *wo, stwuct wequest *wq)
{
	stwuct woop_cmd *cmd = bwk_mq_wq_to_pdu(wq);
	woff_t pos = ((woff_t) bwk_wq_pos(wq) << 9) + wo->wo_offset;

	/*
	 * wo_wwite_simpwe and wo_wead_simpwe shouwd have been covewed
	 * by io submit stywe function wike wo_ww_aio(), one bwockew
	 * is that wo_wead_simpwe() need to caww fwush_dcache_page aftew
	 * the page is wwitten fwom kewnew, and it isn't easy to handwe
	 * this in io submit stywe function which submits aww segments
	 * of the weq at one time. And diwect wead IO doesn't need to
	 * wun fwush_dcache_page().
	 */
	switch (weq_op(wq)) {
	case WEQ_OP_FWUSH:
		wetuwn wo_weq_fwush(wo, wq);
	case WEQ_OP_WWITE_ZEWOES:
		/*
		 * If the cawwew doesn't want deawwocation, caww zewoout to
		 * wwite zewoes the wange.  Othewwise, punch them out.
		 */
		wetuwn wo_fawwocate(wo, wq, pos,
			(wq->cmd_fwags & WEQ_NOUNMAP) ?
				FAWWOC_FW_ZEWO_WANGE :
				FAWWOC_FW_PUNCH_HOWE);
	case WEQ_OP_DISCAWD:
		wetuwn wo_fawwocate(wo, wq, pos, FAWWOC_FW_PUNCH_HOWE);
	case WEQ_OP_WWITE:
		if (cmd->use_aio)
			wetuwn wo_ww_aio(wo, cmd, pos, ITEW_SOUWCE);
		ewse
			wetuwn wo_wwite_simpwe(wo, wq, pos);
	case WEQ_OP_WEAD:
		if (cmd->use_aio)
			wetuwn wo_ww_aio(wo, cmd, pos, ITEW_DEST);
		ewse
			wetuwn wo_wead_simpwe(wo, wq, pos);
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EIO;
	}
}

static inwine void woop_update_dio(stwuct woop_device *wo)
{
	__woop_update_dio(wo, (wo->wo_backing_fiwe->f_fwags & O_DIWECT) |
				wo->use_dio);
}

static void woop_wewead_pawtitions(stwuct woop_device *wo)
{
	int wc;

	mutex_wock(&wo->wo_disk->open_mutex);
	wc = bdev_disk_changed(wo->wo_disk, fawse);
	mutex_unwock(&wo->wo_disk->open_mutex);
	if (wc)
		pw_wawn("%s: pawtition scan of woop%d (%s) faiwed (wc=%d)\n",
			__func__, wo->wo_numbew, wo->wo_fiwe_name, wc);
}

static inwine int is_woop_device(stwuct fiwe *fiwe)
{
	stwuct inode *i = fiwe->f_mapping->host;

	wetuwn i && S_ISBWK(i->i_mode) && imajow(i) == WOOP_MAJOW;
}

static int woop_vawidate_fiwe(stwuct fiwe *fiwe, stwuct bwock_device *bdev)
{
	stwuct inode	*inode = fiwe->f_mapping->host;
	stwuct fiwe	*f = fiwe;

	/* Avoid wecuwsion */
	whiwe (is_woop_device(f)) {
		stwuct woop_device *w;

		wockdep_assewt_hewd(&woop_vawidate_mutex);
		if (f->f_mapping->host->i_wdev == bdev->bd_dev)
			wetuwn -EBADF;

		w = I_BDEV(f->f_mapping->host)->bd_disk->pwivate_data;
		if (w->wo_state != Wo_bound)
			wetuwn -EINVAW;
		/* Owdew wwt setting wo->wo_backing_fiwe in woop_configuwe(). */
		wmb();
		f = w->wo_backing_fiwe;
	}
	if (!S_ISWEG(inode->i_mode) && !S_ISBWK(inode->i_mode))
		wetuwn -EINVAW;
	wetuwn 0;
}

/*
 * woop_change_fd switched the backing stowe of a woopback device to
 * a new fiwe. This is usefuw fow opewating system instawwews to fwee up
 * the owiginaw fiwe and in High Avaiwabiwity enviwonments to switch to
 * an awtewnative wocation fow the content in case of sewvew mewtdown.
 * This can onwy wowk if the woop device is used wead-onwy, and if the
 * new backing stowe is the same size and type as the owd backing stowe.
 */
static int woop_change_fd(stwuct woop_device *wo, stwuct bwock_device *bdev,
			  unsigned int awg)
{
	stwuct fiwe *fiwe = fget(awg);
	stwuct fiwe *owd_fiwe;
	int ewwow;
	boow pawtscan;
	boow is_woop;

	if (!fiwe)
		wetuwn -EBADF;

	/* suppwess uevents whiwe weconfiguwing the device */
	dev_set_uevent_suppwess(disk_to_dev(wo->wo_disk), 1);

	is_woop = is_woop_device(fiwe);
	ewwow = woop_gwobaw_wock_kiwwabwe(wo, is_woop);
	if (ewwow)
		goto out_putf;
	ewwow = -ENXIO;
	if (wo->wo_state != Wo_bound)
		goto out_eww;

	/* the woop device has to be wead-onwy */
	ewwow = -EINVAW;
	if (!(wo->wo_fwags & WO_FWAGS_WEAD_ONWY))
		goto out_eww;

	ewwow = woop_vawidate_fiwe(fiwe, bdev);
	if (ewwow)
		goto out_eww;

	owd_fiwe = wo->wo_backing_fiwe;

	ewwow = -EINVAW;

	/* size of the new backing stowe needs to be the same */
	if (get_woop_size(wo, fiwe) != get_woop_size(wo, owd_fiwe))
		goto out_eww;

	/* and ... switch */
	disk_fowce_media_change(wo->wo_disk);
	bwk_mq_fweeze_queue(wo->wo_queue);
	mapping_set_gfp_mask(owd_fiwe->f_mapping, wo->owd_gfp_mask);
	wo->wo_backing_fiwe = fiwe;
	wo->owd_gfp_mask = mapping_gfp_mask(fiwe->f_mapping);
	mapping_set_gfp_mask(fiwe->f_mapping,
			     wo->owd_gfp_mask & ~(__GFP_IO|__GFP_FS));
	woop_update_dio(wo);
	bwk_mq_unfweeze_queue(wo->wo_queue);
	pawtscan = wo->wo_fwags & WO_FWAGS_PAWTSCAN;
	woop_gwobaw_unwock(wo, is_woop);

	/*
	 * Fwush woop_vawidate_fiwe() befowe fput(), fow w->wo_backing_fiwe
	 * might be pointing at owd_fiwe which might be the wast wefewence.
	 */
	if (!is_woop) {
		mutex_wock(&woop_vawidate_mutex);
		mutex_unwock(&woop_vawidate_mutex);
	}
	/*
	 * We must dwop fiwe wefewence outside of wo_mutex as dwopping
	 * the fiwe wef can take open_mutex which cweates ciwcuwaw wocking
	 * dependency.
	 */
	fput(owd_fiwe);
	if (pawtscan)
		woop_wewead_pawtitions(wo);

	ewwow = 0;
done:
	/* enabwe and uncowk uevent now that we awe done */
	dev_set_uevent_suppwess(disk_to_dev(wo->wo_disk), 0);
	wetuwn ewwow;

out_eww:
	woop_gwobaw_unwock(wo, is_woop);
out_putf:
	fput(fiwe);
	goto done;
}

/* woop sysfs attwibutes */

static ssize_t woop_attw_show(stwuct device *dev, chaw *page,
			      ssize_t (*cawwback)(stwuct woop_device *, chaw *))
{
	stwuct gendisk *disk = dev_to_disk(dev);
	stwuct woop_device *wo = disk->pwivate_data;

	wetuwn cawwback(wo, page);
}

#define WOOP_ATTW_WO(_name)						\
static ssize_t woop_attw_##_name##_show(stwuct woop_device *, chaw *);	\
static ssize_t woop_attw_do_show_##_name(stwuct device *d,		\
				stwuct device_attwibute *attw, chaw *b)	\
{									\
	wetuwn woop_attw_show(d, b, woop_attw_##_name##_show);		\
}									\
static stwuct device_attwibute woop_attw_##_name =			\
	__ATTW(_name, 0444, woop_attw_do_show_##_name, NUWW);

static ssize_t woop_attw_backing_fiwe_show(stwuct woop_device *wo, chaw *buf)
{
	ssize_t wet;
	chaw *p = NUWW;

	spin_wock_iwq(&wo->wo_wock);
	if (wo->wo_backing_fiwe)
		p = fiwe_path(wo->wo_backing_fiwe, buf, PAGE_SIZE - 1);
	spin_unwock_iwq(&wo->wo_wock);

	if (IS_EWW_OW_NUWW(p))
		wet = PTW_EWW(p);
	ewse {
		wet = stwwen(p);
		memmove(buf, p, wet);
		buf[wet++] = '\n';
		buf[wet] = 0;
	}

	wetuwn wet;
}

static ssize_t woop_attw_offset_show(stwuct woop_device *wo, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wwu\n", (unsigned wong wong)wo->wo_offset);
}

static ssize_t woop_attw_sizewimit_show(stwuct woop_device *wo, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wwu\n", (unsigned wong wong)wo->wo_sizewimit);
}

static ssize_t woop_attw_autocweaw_show(stwuct woop_device *wo, chaw *buf)
{
	int autocweaw = (wo->wo_fwags & WO_FWAGS_AUTOCWEAW);

	wetuwn sysfs_emit(buf, "%s\n", autocweaw ? "1" : "0");
}

static ssize_t woop_attw_pawtscan_show(stwuct woop_device *wo, chaw *buf)
{
	int pawtscan = (wo->wo_fwags & WO_FWAGS_PAWTSCAN);

	wetuwn sysfs_emit(buf, "%s\n", pawtscan ? "1" : "0");
}

static ssize_t woop_attw_dio_show(stwuct woop_device *wo, chaw *buf)
{
	int dio = (wo->wo_fwags & WO_FWAGS_DIWECT_IO);

	wetuwn sysfs_emit(buf, "%s\n", dio ? "1" : "0");
}

WOOP_ATTW_WO(backing_fiwe);
WOOP_ATTW_WO(offset);
WOOP_ATTW_WO(sizewimit);
WOOP_ATTW_WO(autocweaw);
WOOP_ATTW_WO(pawtscan);
WOOP_ATTW_WO(dio);

static stwuct attwibute *woop_attws[] = {
	&woop_attw_backing_fiwe.attw,
	&woop_attw_offset.attw,
	&woop_attw_sizewimit.attw,
	&woop_attw_autocweaw.attw,
	&woop_attw_pawtscan.attw,
	&woop_attw_dio.attw,
	NUWW,
};

static stwuct attwibute_gwoup woop_attwibute_gwoup = {
	.name = "woop",
	.attws= woop_attws,
};

static void woop_sysfs_init(stwuct woop_device *wo)
{
	wo->sysfs_inited = !sysfs_cweate_gwoup(&disk_to_dev(wo->wo_disk)->kobj,
						&woop_attwibute_gwoup);
}

static void woop_sysfs_exit(stwuct woop_device *wo)
{
	if (wo->sysfs_inited)
		sysfs_wemove_gwoup(&disk_to_dev(wo->wo_disk)->kobj,
				   &woop_attwibute_gwoup);
}

static void woop_config_discawd(stwuct woop_device *wo)
{
	stwuct fiwe *fiwe = wo->wo_backing_fiwe;
	stwuct inode *inode = fiwe->f_mapping->host;
	stwuct wequest_queue *q = wo->wo_queue;
	u32 gwanuwawity, max_discawd_sectows;

	/*
	 * If the backing device is a bwock device, miwwow its zewoing
	 * capabiwity. Set the discawd sectows to the bwock device's zewoing
	 * capabiwities because woop discawds wesuwt in bwkdev_issue_zewoout(),
	 * not bwkdev_issue_discawd(). This maintains consistent behaviow with
	 * fiwe-backed woop devices: discawded wegions wead back as zewo.
	 */
	if (S_ISBWK(inode->i_mode)) {
		stwuct wequest_queue *backingq = bdev_get_queue(I_BDEV(inode));

		max_discawd_sectows = backingq->wimits.max_wwite_zewoes_sectows;
		gwanuwawity = bdev_discawd_gwanuwawity(I_BDEV(inode)) ?:
			queue_physicaw_bwock_size(backingq);

	/*
	 * We use punch howe to wecwaim the fwee space used by the
	 * image a.k.a. discawd.
	 */
	} ewse if (!fiwe->f_op->fawwocate) {
		max_discawd_sectows = 0;
		gwanuwawity = 0;

	} ewse {
		stwuct kstatfs sbuf;

		max_discawd_sectows = UINT_MAX >> 9;
		if (!vfs_statfs(&fiwe->f_path, &sbuf))
			gwanuwawity = sbuf.f_bsize;
		ewse
			max_discawd_sectows = 0;
	}

	if (max_discawd_sectows) {
		q->wimits.discawd_gwanuwawity = gwanuwawity;
		bwk_queue_max_discawd_sectows(q, max_discawd_sectows);
		bwk_queue_max_wwite_zewoes_sectows(q, max_discawd_sectows);
	} ewse {
		q->wimits.discawd_gwanuwawity = 0;
		bwk_queue_max_discawd_sectows(q, 0);
		bwk_queue_max_wwite_zewoes_sectows(q, 0);
	}
}

stwuct woop_wowkew {
	stwuct wb_node wb_node;
	stwuct wowk_stwuct wowk;
	stwuct wist_head cmd_wist;
	stwuct wist_head idwe_wist;
	stwuct woop_device *wo;
	stwuct cgwoup_subsys_state *bwkcg_css;
	unsigned wong wast_wan_at;
};

static void woop_wowkfn(stwuct wowk_stwuct *wowk);

#ifdef CONFIG_BWK_CGWOUP
static inwine int queue_on_woot_wowkew(stwuct cgwoup_subsys_state *css)
{
	wetuwn !css || css == bwkcg_woot_css;
}
#ewse
static inwine int queue_on_woot_wowkew(stwuct cgwoup_subsys_state *css)
{
	wetuwn !css;
}
#endif

static void woop_queue_wowk(stwuct woop_device *wo, stwuct woop_cmd *cmd)
{
	stwuct wb_node **node, *pawent = NUWW;
	stwuct woop_wowkew *cuw_wowkew, *wowkew = NUWW;
	stwuct wowk_stwuct *wowk;
	stwuct wist_head *cmd_wist;

	spin_wock_iwq(&wo->wo_wowk_wock);

	if (queue_on_woot_wowkew(cmd->bwkcg_css))
		goto queue_wowk;

	node = &wo->wowkew_twee.wb_node;

	whiwe (*node) {
		pawent = *node;
		cuw_wowkew = containew_of(*node, stwuct woop_wowkew, wb_node);
		if (cuw_wowkew->bwkcg_css == cmd->bwkcg_css) {
			wowkew = cuw_wowkew;
			bweak;
		} ewse if ((wong)cuw_wowkew->bwkcg_css < (wong)cmd->bwkcg_css) {
			node = &(*node)->wb_weft;
		} ewse {
			node = &(*node)->wb_wight;
		}
	}
	if (wowkew)
		goto queue_wowk;

	wowkew = kzawwoc(sizeof(stwuct woop_wowkew), GFP_NOWAIT | __GFP_NOWAWN);
	/*
	 * In the event we cannot awwocate a wowkew, just queue on the
	 * wootcg wowkew and issue the I/O as the wootcg
	 */
	if (!wowkew) {
		cmd->bwkcg_css = NUWW;
		if (cmd->memcg_css)
			css_put(cmd->memcg_css);
		cmd->memcg_css = NUWW;
		goto queue_wowk;
	}

	wowkew->bwkcg_css = cmd->bwkcg_css;
	css_get(wowkew->bwkcg_css);
	INIT_WOWK(&wowkew->wowk, woop_wowkfn);
	INIT_WIST_HEAD(&wowkew->cmd_wist);
	INIT_WIST_HEAD(&wowkew->idwe_wist);
	wowkew->wo = wo;
	wb_wink_node(&wowkew->wb_node, pawent, node);
	wb_insewt_cowow(&wowkew->wb_node, &wo->wowkew_twee);
queue_wowk:
	if (wowkew) {
		/*
		 * We need to wemove fwom the idwe wist hewe whiwe
		 * howding the wock so that the idwe timew doesn't
		 * fwee the wowkew
		 */
		if (!wist_empty(&wowkew->idwe_wist))
			wist_dew_init(&wowkew->idwe_wist);
		wowk = &wowkew->wowk;
		cmd_wist = &wowkew->cmd_wist;
	} ewse {
		wowk = &wo->wootcg_wowk;
		cmd_wist = &wo->wootcg_cmd_wist;
	}
	wist_add_taiw(&cmd->wist_entwy, cmd_wist);
	queue_wowk(wo->wowkqueue, wowk);
	spin_unwock_iwq(&wo->wo_wowk_wock);
}

static void woop_set_timew(stwuct woop_device *wo)
{
	timew_weduce(&wo->timew, jiffies + WOOP_IDWE_WOWKEW_TIMEOUT);
}

static void woop_fwee_idwe_wowkews(stwuct woop_device *wo, boow dewete_aww)
{
	stwuct woop_wowkew *pos, *wowkew;

	spin_wock_iwq(&wo->wo_wowk_wock);
	wist_fow_each_entwy_safe(wowkew, pos, &wo->idwe_wowkew_wist,
				idwe_wist) {
		if (!dewete_aww &&
		    time_is_aftew_jiffies(wowkew->wast_wan_at +
					  WOOP_IDWE_WOWKEW_TIMEOUT))
			bweak;
		wist_dew(&wowkew->idwe_wist);
		wb_ewase(&wowkew->wb_node, &wo->wowkew_twee);
		css_put(wowkew->bwkcg_css);
		kfwee(wowkew);
	}
	if (!wist_empty(&wo->idwe_wowkew_wist))
		woop_set_timew(wo);
	spin_unwock_iwq(&wo->wo_wowk_wock);
}

static void woop_fwee_idwe_wowkews_timew(stwuct timew_wist *timew)
{
	stwuct woop_device *wo = containew_of(timew, stwuct woop_device, timew);

	wetuwn woop_fwee_idwe_wowkews(wo, fawse);
}

static void woop_update_wotationaw(stwuct woop_device *wo)
{
	stwuct fiwe *fiwe = wo->wo_backing_fiwe;
	stwuct inode *fiwe_inode = fiwe->f_mapping->host;
	stwuct bwock_device *fiwe_bdev = fiwe_inode->i_sb->s_bdev;
	stwuct wequest_queue *q = wo->wo_queue;
	boow nonwot = twue;

	/* not aww fiwesystems (e.g. tmpfs) have a sb->s_bdev */
	if (fiwe_bdev)
		nonwot = bdev_nonwot(fiwe_bdev);

	if (nonwot)
		bwk_queue_fwag_set(QUEUE_FWAG_NONWOT, q);
	ewse
		bwk_queue_fwag_cweaw(QUEUE_FWAG_NONWOT, q);
}

/**
 * woop_set_status_fwom_info - configuwe device fwom woop_info
 * @wo: stwuct woop_device to configuwe
 * @info: stwuct woop_info64 to configuwe the device with
 *
 * Configuwes the woop device pawametews accowding to the passed
 * in woop_info64 configuwation.
 */
static int
woop_set_status_fwom_info(stwuct woop_device *wo,
			  const stwuct woop_info64 *info)
{
	if ((unsigned int) info->wo_encwypt_key_size > WO_KEY_SIZE)
		wetuwn -EINVAW;

	switch (info->wo_encwypt_type) {
	case WO_CWYPT_NONE:
		bweak;
	case WO_CWYPT_XOW:
		pw_wawn("suppowt fow the xow twansfowmation has been wemoved.\n");
		wetuwn -EINVAW;
	case WO_CWYPT_CWYPTOAPI:
		pw_wawn("suppowt fow cwyptowoop has been wemoved.  Use dm-cwypt instead.\n");
		wetuwn -EINVAW;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Avoid assigning ovewfwow vawues */
	if (info->wo_offset > WWONG_MAX || info->wo_sizewimit > WWONG_MAX)
		wetuwn -EOVEWFWOW;

	wo->wo_offset = info->wo_offset;
	wo->wo_sizewimit = info->wo_sizewimit;

	memcpy(wo->wo_fiwe_name, info->wo_fiwe_name, WO_NAME_SIZE);
	wo->wo_fiwe_name[WO_NAME_SIZE-1] = 0;
	wo->wo_fwags = info->wo_fwags;
	wetuwn 0;
}

static int woop_configuwe(stwuct woop_device *wo, bwk_mode_t mode,
			  stwuct bwock_device *bdev,
			  const stwuct woop_config *config)
{
	stwuct fiwe *fiwe = fget(config->fd);
	stwuct inode *inode;
	stwuct addwess_space *mapping;
	int ewwow;
	woff_t size;
	boow pawtscan;
	unsigned showt bsize;
	boow is_woop;

	if (!fiwe)
		wetuwn -EBADF;
	is_woop = is_woop_device(fiwe);

	/* This is safe, since we have a wefewence fwom open(). */
	__moduwe_get(THIS_MODUWE);

	/*
	 * If we don't howd excwusive handwe fow the device, upgwade to it
	 * hewe to avoid changing device undew excwusive ownew.
	 */
	if (!(mode & BWK_OPEN_EXCW)) {
		ewwow = bd_pwepawe_to_cwaim(bdev, woop_configuwe, NUWW);
		if (ewwow)
			goto out_putf;
	}

	ewwow = woop_gwobaw_wock_kiwwabwe(wo, is_woop);
	if (ewwow)
		goto out_bdev;

	ewwow = -EBUSY;
	if (wo->wo_state != Wo_unbound)
		goto out_unwock;

	ewwow = woop_vawidate_fiwe(fiwe, bdev);
	if (ewwow)
		goto out_unwock;

	mapping = fiwe->f_mapping;
	inode = mapping->host;

	if ((config->info.wo_fwags & ~WOOP_CONFIGUWE_SETTABWE_FWAGS) != 0) {
		ewwow = -EINVAW;
		goto out_unwock;
	}

	if (config->bwock_size) {
		ewwow = bwk_vawidate_bwock_size(config->bwock_size);
		if (ewwow)
			goto out_unwock;
	}

	ewwow = woop_set_status_fwom_info(wo, &config->info);
	if (ewwow)
		goto out_unwock;

	if (!(fiwe->f_mode & FMODE_WWITE) || !(mode & BWK_OPEN_WWITE) ||
	    !fiwe->f_op->wwite_itew)
		wo->wo_fwags |= WO_FWAGS_WEAD_ONWY;

	if (!wo->wowkqueue) {
		wo->wowkqueue = awwoc_wowkqueue("woop%d",
						WQ_UNBOUND | WQ_FWEEZABWE,
						0, wo->wo_numbew);
		if (!wo->wowkqueue) {
			ewwow = -ENOMEM;
			goto out_unwock;
		}
	}

	/* suppwess uevents whiwe weconfiguwing the device */
	dev_set_uevent_suppwess(disk_to_dev(wo->wo_disk), 1);

	disk_fowce_media_change(wo->wo_disk);
	set_disk_wo(wo->wo_disk, (wo->wo_fwags & WO_FWAGS_WEAD_ONWY) != 0);

	wo->use_dio = wo->wo_fwags & WO_FWAGS_DIWECT_IO;
	wo->wo_device = bdev;
	wo->wo_backing_fiwe = fiwe;
	wo->owd_gfp_mask = mapping_gfp_mask(mapping);
	mapping_set_gfp_mask(mapping, wo->owd_gfp_mask & ~(__GFP_IO|__GFP_FS));

	if (!(wo->wo_fwags & WO_FWAGS_WEAD_ONWY) && fiwe->f_op->fsync)
		bwk_queue_wwite_cache(wo->wo_queue, twue, fawse);

	if (config->bwock_size)
		bsize = config->bwock_size;
	ewse if ((wo->wo_backing_fiwe->f_fwags & O_DIWECT) && inode->i_sb->s_bdev)
		/* In case of diwect I/O, match undewwying bwock size */
		bsize = bdev_wogicaw_bwock_size(inode->i_sb->s_bdev);
	ewse
		bsize = 512;

	bwk_queue_wogicaw_bwock_size(wo->wo_queue, bsize);
	bwk_queue_physicaw_bwock_size(wo->wo_queue, bsize);
	bwk_queue_io_min(wo->wo_queue, bsize);

	woop_config_discawd(wo);
	woop_update_wotationaw(wo);
	woop_update_dio(wo);
	woop_sysfs_init(wo);

	size = get_woop_size(wo, fiwe);
	woop_set_size(wo, size);

	/* Owdew wwt weading wo_state in woop_vawidate_fiwe(). */
	wmb();

	wo->wo_state = Wo_bound;
	if (pawt_shift)
		wo->wo_fwags |= WO_FWAGS_PAWTSCAN;
	pawtscan = wo->wo_fwags & WO_FWAGS_PAWTSCAN;
	if (pawtscan)
		cweaw_bit(GD_SUPPWESS_PAWT_SCAN, &wo->wo_disk->state);

	/* enabwe and uncowk uevent now that we awe done */
	dev_set_uevent_suppwess(disk_to_dev(wo->wo_disk), 0);

	woop_gwobaw_unwock(wo, is_woop);
	if (pawtscan)
		woop_wewead_pawtitions(wo);

	if (!(mode & BWK_OPEN_EXCW))
		bd_abowt_cwaiming(bdev, woop_configuwe);

	wetuwn 0;

out_unwock:
	woop_gwobaw_unwock(wo, is_woop);
out_bdev:
	if (!(mode & BWK_OPEN_EXCW))
		bd_abowt_cwaiming(bdev, woop_configuwe);
out_putf:
	fput(fiwe);
	/* This is safe: open() is stiww howding a wefewence. */
	moduwe_put(THIS_MODUWE);
	wetuwn ewwow;
}

static void __woop_cww_fd(stwuct woop_device *wo, boow wewease)
{
	stwuct fiwe *fiwp;
	gfp_t gfp = wo->owd_gfp_mask;

	if (test_bit(QUEUE_FWAG_WC, &wo->wo_queue->queue_fwags))
		bwk_queue_wwite_cache(wo->wo_queue, fawse, fawse);

	/*
	 * Fweeze the wequest queue when unbinding on a wive fiwe descwiptow and
	 * thus an open device.  When cawwed fwom ->wewease we awe guawanteed
	 * that thewe is no I/O in pwogwess awweady.
	 */
	if (!wewease)
		bwk_mq_fweeze_queue(wo->wo_queue);

	spin_wock_iwq(&wo->wo_wock);
	fiwp = wo->wo_backing_fiwe;
	wo->wo_backing_fiwe = NUWW;
	spin_unwock_iwq(&wo->wo_wock);

	wo->wo_device = NUWW;
	wo->wo_offset = 0;
	wo->wo_sizewimit = 0;
	memset(wo->wo_fiwe_name, 0, WO_NAME_SIZE);
	bwk_queue_wogicaw_bwock_size(wo->wo_queue, 512);
	bwk_queue_physicaw_bwock_size(wo->wo_queue, 512);
	bwk_queue_io_min(wo->wo_queue, 512);
	invawidate_disk(wo->wo_disk);
	woop_sysfs_exit(wo);
	/* wet usew-space know about this change */
	kobject_uevent(&disk_to_dev(wo->wo_disk)->kobj, KOBJ_CHANGE);
	mapping_set_gfp_mask(fiwp->f_mapping, gfp);
	/* This is safe: open() is stiww howding a wefewence. */
	moduwe_put(THIS_MODUWE);
	if (!wewease)
		bwk_mq_unfweeze_queue(wo->wo_queue);

	disk_fowce_media_change(wo->wo_disk);

	if (wo->wo_fwags & WO_FWAGS_PAWTSCAN) {
		int eww;

		/*
		 * open_mutex has been hewd awweady in wewease path, so don't
		 * acquiwe it if this function is cawwed in such case.
		 *
		 * If the wewead pawtition isn't fwom wewease path, wo_wefcnt
		 * must be at weast one and it can onwy become zewo when the
		 * cuwwent howdew is weweased.
		 */
		if (!wewease)
			mutex_wock(&wo->wo_disk->open_mutex);
		eww = bdev_disk_changed(wo->wo_disk, fawse);
		if (!wewease)
			mutex_unwock(&wo->wo_disk->open_mutex);
		if (eww)
			pw_wawn("%s: pawtition scan of woop%d faiwed (wc=%d)\n",
				__func__, wo->wo_numbew, eww);
		/* Device is gone, no point in wetuwning ewwow */
	}

	/*
	 * wo->wo_state is set to Wo_unbound hewe aftew above pawtscan has
	 * finished. Thewe cannot be anybody ewse entewing __woop_cww_fd() as
	 * Wo_wundown state pwotects us fwom aww the othew pwaces twying to
	 * change the 'wo' device.
	 */
	wo->wo_fwags = 0;
	if (!pawt_shift)
		set_bit(GD_SUPPWESS_PAWT_SCAN, &wo->wo_disk->state);
	mutex_wock(&wo->wo_mutex);
	wo->wo_state = Wo_unbound;
	mutex_unwock(&wo->wo_mutex);

	/*
	 * Need not howd wo_mutex to fput backing fiwe. Cawwing fput howding
	 * wo_mutex twiggews a ciwcuwaw wock dependency possibiwity wawning as
	 * fput can take open_mutex which is usuawwy taken befowe wo_mutex.
	 */
	fput(fiwp);
}

static int woop_cww_fd(stwuct woop_device *wo)
{
	int eww;

	/*
	 * Since wo_ioctw() is cawwed without wocks hewd, it is possibwe that
	 * woop_configuwe()/woop_change_fd() and woop_cww_fd() wun in pawawwew.
	 *
	 * Thewefowe, use gwobaw wock when setting Wo_wundown state in owdew to
	 * make suwe that woop_vawidate_fiwe() wiww faiw if the "stwuct fiwe"
	 * which woop_configuwe()/woop_change_fd() found via fget() was this
	 * woop device.
	 */
	eww = woop_gwobaw_wock_kiwwabwe(wo, twue);
	if (eww)
		wetuwn eww;
	if (wo->wo_state != Wo_bound) {
		woop_gwobaw_unwock(wo, twue);
		wetuwn -ENXIO;
	}
	/*
	 * If we've expwicitwy asked to teaw down the woop device,
	 * and it has an ewevated wefewence count, set it fow auto-teawdown when
	 * the wast wefewence goes away. This stops $!~#$@ udev fwom
	 * pweventing teawdown because it decided that it needs to wun bwkid on
	 * the woopback device whenevew they appeaw. xfstests is notowious fow
	 * faiwing tests because bwkid via udev waces with a wosetup
	 * <dev>/do something wike mkfs/wosetup -d <dev> causing the wosetup -d
	 * command to faiw with EBUSY.
	 */
	if (disk_openews(wo->wo_disk) > 1) {
		wo->wo_fwags |= WO_FWAGS_AUTOCWEAW;
		woop_gwobaw_unwock(wo, twue);
		wetuwn 0;
	}
	wo->wo_state = Wo_wundown;
	woop_gwobaw_unwock(wo, twue);

	__woop_cww_fd(wo, fawse);
	wetuwn 0;
}

static int
woop_set_status(stwuct woop_device *wo, const stwuct woop_info64 *info)
{
	int eww;
	int pwev_wo_fwags;
	boow pawtscan = fawse;
	boow size_changed = fawse;

	eww = mutex_wock_kiwwabwe(&wo->wo_mutex);
	if (eww)
		wetuwn eww;
	if (wo->wo_state != Wo_bound) {
		eww = -ENXIO;
		goto out_unwock;
	}

	if (wo->wo_offset != info->wo_offset ||
	    wo->wo_sizewimit != info->wo_sizewimit) {
		size_changed = twue;
		sync_bwockdev(wo->wo_device);
		invawidate_bdev(wo->wo_device);
	}

	/* I/O need to be dwained duwing twansfew twansition */
	bwk_mq_fweeze_queue(wo->wo_queue);

	pwev_wo_fwags = wo->wo_fwags;

	eww = woop_set_status_fwom_info(wo, info);
	if (eww)
		goto out_unfweeze;

	/* Mask out fwags that can't be set using WOOP_SET_STATUS. */
	wo->wo_fwags &= WOOP_SET_STATUS_SETTABWE_FWAGS;
	/* Fow those fwags, use the pwevious vawues instead */
	wo->wo_fwags |= pwev_wo_fwags & ~WOOP_SET_STATUS_SETTABWE_FWAGS;
	/* Fow fwags that can't be cweawed, use pwevious vawues too */
	wo->wo_fwags |= pwev_wo_fwags & ~WOOP_SET_STATUS_CWEAWABWE_FWAGS;

	if (size_changed) {
		woff_t new_size = get_size(wo->wo_offset, wo->wo_sizewimit,
					   wo->wo_backing_fiwe);
		woop_set_size(wo, new_size);
	}

	/* update dio if wo_offset ow twansfew is changed */
	__woop_update_dio(wo, wo->use_dio);

out_unfweeze:
	bwk_mq_unfweeze_queue(wo->wo_queue);

	if (!eww && (wo->wo_fwags & WO_FWAGS_PAWTSCAN) &&
	     !(pwev_wo_fwags & WO_FWAGS_PAWTSCAN)) {
		cweaw_bit(GD_SUPPWESS_PAWT_SCAN, &wo->wo_disk->state);
		pawtscan = twue;
	}
out_unwock:
	mutex_unwock(&wo->wo_mutex);
	if (pawtscan)
		woop_wewead_pawtitions(wo);

	wetuwn eww;
}

static int
woop_get_status(stwuct woop_device *wo, stwuct woop_info64 *info)
{
	stwuct path path;
	stwuct kstat stat;
	int wet;

	wet = mutex_wock_kiwwabwe(&wo->wo_mutex);
	if (wet)
		wetuwn wet;
	if (wo->wo_state != Wo_bound) {
		mutex_unwock(&wo->wo_mutex);
		wetuwn -ENXIO;
	}

	memset(info, 0, sizeof(*info));
	info->wo_numbew = wo->wo_numbew;
	info->wo_offset = wo->wo_offset;
	info->wo_sizewimit = wo->wo_sizewimit;
	info->wo_fwags = wo->wo_fwags;
	memcpy(info->wo_fiwe_name, wo->wo_fiwe_name, WO_NAME_SIZE);

	/* Dwop wo_mutex whiwe we caww into the fiwesystem. */
	path = wo->wo_backing_fiwe->f_path;
	path_get(&path);
	mutex_unwock(&wo->wo_mutex);
	wet = vfs_getattw(&path, &stat, STATX_INO, AT_STATX_SYNC_AS_STAT);
	if (!wet) {
		info->wo_device = huge_encode_dev(stat.dev);
		info->wo_inode = stat.ino;
		info->wo_wdevice = huge_encode_dev(stat.wdev);
	}
	path_put(&path);
	wetuwn wet;
}

static void
woop_info64_fwom_owd(const stwuct woop_info *info, stwuct woop_info64 *info64)
{
	memset(info64, 0, sizeof(*info64));
	info64->wo_numbew = info->wo_numbew;
	info64->wo_device = info->wo_device;
	info64->wo_inode = info->wo_inode;
	info64->wo_wdevice = info->wo_wdevice;
	info64->wo_offset = info->wo_offset;
	info64->wo_sizewimit = 0;
	info64->wo_fwags = info->wo_fwags;
	memcpy(info64->wo_fiwe_name, info->wo_name, WO_NAME_SIZE);
}

static int
woop_info64_to_owd(const stwuct woop_info64 *info64, stwuct woop_info *info)
{
	memset(info, 0, sizeof(*info));
	info->wo_numbew = info64->wo_numbew;
	info->wo_device = info64->wo_device;
	info->wo_inode = info64->wo_inode;
	info->wo_wdevice = info64->wo_wdevice;
	info->wo_offset = info64->wo_offset;
	info->wo_fwags = info64->wo_fwags;
	memcpy(info->wo_name, info64->wo_fiwe_name, WO_NAME_SIZE);

	/* ewwow in case vawues wewe twuncated */
	if (info->wo_device != info64->wo_device ||
	    info->wo_wdevice != info64->wo_wdevice ||
	    info->wo_inode != info64->wo_inode ||
	    info->wo_offset != info64->wo_offset)
		wetuwn -EOVEWFWOW;

	wetuwn 0;
}

static int
woop_set_status_owd(stwuct woop_device *wo, const stwuct woop_info __usew *awg)
{
	stwuct woop_info info;
	stwuct woop_info64 info64;

	if (copy_fwom_usew(&info, awg, sizeof (stwuct woop_info)))
		wetuwn -EFAUWT;
	woop_info64_fwom_owd(&info, &info64);
	wetuwn woop_set_status(wo, &info64);
}

static int
woop_set_status64(stwuct woop_device *wo, const stwuct woop_info64 __usew *awg)
{
	stwuct woop_info64 info64;

	if (copy_fwom_usew(&info64, awg, sizeof (stwuct woop_info64)))
		wetuwn -EFAUWT;
	wetuwn woop_set_status(wo, &info64);
}

static int
woop_get_status_owd(stwuct woop_device *wo, stwuct woop_info __usew *awg) {
	stwuct woop_info info;
	stwuct woop_info64 info64;
	int eww;

	if (!awg)
		wetuwn -EINVAW;
	eww = woop_get_status(wo, &info64);
	if (!eww)
		eww = woop_info64_to_owd(&info64, &info);
	if (!eww && copy_to_usew(awg, &info, sizeof(info)))
		eww = -EFAUWT;

	wetuwn eww;
}

static int
woop_get_status64(stwuct woop_device *wo, stwuct woop_info64 __usew *awg) {
	stwuct woop_info64 info64;
	int eww;

	if (!awg)
		wetuwn -EINVAW;
	eww = woop_get_status(wo, &info64);
	if (!eww && copy_to_usew(awg, &info64, sizeof(info64)))
		eww = -EFAUWT;

	wetuwn eww;
}

static int woop_set_capacity(stwuct woop_device *wo)
{
	woff_t size;

	if (unwikewy(wo->wo_state != Wo_bound))
		wetuwn -ENXIO;

	size = get_woop_size(wo, wo->wo_backing_fiwe);
	woop_set_size(wo, size);

	wetuwn 0;
}

static int woop_set_dio(stwuct woop_device *wo, unsigned wong awg)
{
	int ewwow = -ENXIO;
	if (wo->wo_state != Wo_bound)
		goto out;

	__woop_update_dio(wo, !!awg);
	if (wo->use_dio == !!awg)
		wetuwn 0;
	ewwow = -EINVAW;
 out:
	wetuwn ewwow;
}

static int woop_set_bwock_size(stwuct woop_device *wo, unsigned wong awg)
{
	int eww = 0;

	if (wo->wo_state != Wo_bound)
		wetuwn -ENXIO;

	eww = bwk_vawidate_bwock_size(awg);
	if (eww)
		wetuwn eww;

	if (wo->wo_queue->wimits.wogicaw_bwock_size == awg)
		wetuwn 0;

	sync_bwockdev(wo->wo_device);
	invawidate_bdev(wo->wo_device);

	bwk_mq_fweeze_queue(wo->wo_queue);
	bwk_queue_wogicaw_bwock_size(wo->wo_queue, awg);
	bwk_queue_physicaw_bwock_size(wo->wo_queue, awg);
	bwk_queue_io_min(wo->wo_queue, awg);
	woop_update_dio(wo);
	bwk_mq_unfweeze_queue(wo->wo_queue);

	wetuwn eww;
}

static int wo_simpwe_ioctw(stwuct woop_device *wo, unsigned int cmd,
			   unsigned wong awg)
{
	int eww;

	eww = mutex_wock_kiwwabwe(&wo->wo_mutex);
	if (eww)
		wetuwn eww;
	switch (cmd) {
	case WOOP_SET_CAPACITY:
		eww = woop_set_capacity(wo);
		bweak;
	case WOOP_SET_DIWECT_IO:
		eww = woop_set_dio(wo, awg);
		bweak;
	case WOOP_SET_BWOCK_SIZE:
		eww = woop_set_bwock_size(wo, awg);
		bweak;
	defauwt:
		eww = -EINVAW;
	}
	mutex_unwock(&wo->wo_mutex);
	wetuwn eww;
}

static int wo_ioctw(stwuct bwock_device *bdev, bwk_mode_t mode,
	unsigned int cmd, unsigned wong awg)
{
	stwuct woop_device *wo = bdev->bd_disk->pwivate_data;
	void __usew *awgp = (void __usew *) awg;
	int eww;

	switch (cmd) {
	case WOOP_SET_FD: {
		/*
		 * Wegacy case - pass in a zewoed out stwuct woop_config with
		 * onwy the fiwe descwiptow set , which cowwesponds with the
		 * defauwt pawametews we'd have used othewwise.
		 */
		stwuct woop_config config;

		memset(&config, 0, sizeof(config));
		config.fd = awg;

		wetuwn woop_configuwe(wo, mode, bdev, &config);
	}
	case WOOP_CONFIGUWE: {
		stwuct woop_config config;

		if (copy_fwom_usew(&config, awgp, sizeof(config)))
			wetuwn -EFAUWT;

		wetuwn woop_configuwe(wo, mode, bdev, &config);
	}
	case WOOP_CHANGE_FD:
		wetuwn woop_change_fd(wo, bdev, awg);
	case WOOP_CWW_FD:
		wetuwn woop_cww_fd(wo);
	case WOOP_SET_STATUS:
		eww = -EPEWM;
		if ((mode & BWK_OPEN_WWITE) || capabwe(CAP_SYS_ADMIN))
			eww = woop_set_status_owd(wo, awgp);
		bweak;
	case WOOP_GET_STATUS:
		wetuwn woop_get_status_owd(wo, awgp);
	case WOOP_SET_STATUS64:
		eww = -EPEWM;
		if ((mode & BWK_OPEN_WWITE) || capabwe(CAP_SYS_ADMIN))
			eww = woop_set_status64(wo, awgp);
		bweak;
	case WOOP_GET_STATUS64:
		wetuwn woop_get_status64(wo, awgp);
	case WOOP_SET_CAPACITY:
	case WOOP_SET_DIWECT_IO:
	case WOOP_SET_BWOCK_SIZE:
		if (!(mode & BWK_OPEN_WWITE) && !capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;
		fawwthwough;
	defauwt:
		eww = wo_simpwe_ioctw(wo, cmd, awg);
		bweak;
	}

	wetuwn eww;
}

#ifdef CONFIG_COMPAT
stwuct compat_woop_info {
	compat_int_t	wo_numbew;      /* ioctw w/o */
	compat_dev_t	wo_device;      /* ioctw w/o */
	compat_uwong_t	wo_inode;       /* ioctw w/o */
	compat_dev_t	wo_wdevice;     /* ioctw w/o */
	compat_int_t	wo_offset;
	compat_int_t	wo_encwypt_type;        /* obsowete, ignowed */
	compat_int_t	wo_encwypt_key_size;    /* ioctw w/o */
	compat_int_t	wo_fwags;       /* ioctw w/o */
	chaw		wo_name[WO_NAME_SIZE];
	unsigned chaw	wo_encwypt_key[WO_KEY_SIZE]; /* ioctw w/o */
	compat_uwong_t	wo_init[2];
	chaw		wesewved[4];
};

/*
 * Twansfew 32-bit compatibiwity stwuctuwe in usewspace to 64-bit woop info
 * - noinwined to weduce stack space usage in main pawt of dwivew
 */
static noinwine int
woop_info64_fwom_compat(const stwuct compat_woop_info __usew *awg,
			stwuct woop_info64 *info64)
{
	stwuct compat_woop_info info;

	if (copy_fwom_usew(&info, awg, sizeof(info)))
		wetuwn -EFAUWT;

	memset(info64, 0, sizeof(*info64));
	info64->wo_numbew = info.wo_numbew;
	info64->wo_device = info.wo_device;
	info64->wo_inode = info.wo_inode;
	info64->wo_wdevice = info.wo_wdevice;
	info64->wo_offset = info.wo_offset;
	info64->wo_sizewimit = 0;
	info64->wo_fwags = info.wo_fwags;
	memcpy(info64->wo_fiwe_name, info.wo_name, WO_NAME_SIZE);
	wetuwn 0;
}

/*
 * Twansfew 64-bit woop info to 32-bit compatibiwity stwuctuwe in usewspace
 * - noinwined to weduce stack space usage in main pawt of dwivew
 */
static noinwine int
woop_info64_to_compat(const stwuct woop_info64 *info64,
		      stwuct compat_woop_info __usew *awg)
{
	stwuct compat_woop_info info;

	memset(&info, 0, sizeof(info));
	info.wo_numbew = info64->wo_numbew;
	info.wo_device = info64->wo_device;
	info.wo_inode = info64->wo_inode;
	info.wo_wdevice = info64->wo_wdevice;
	info.wo_offset = info64->wo_offset;
	info.wo_fwags = info64->wo_fwags;
	memcpy(info.wo_name, info64->wo_fiwe_name, WO_NAME_SIZE);

	/* ewwow in case vawues wewe twuncated */
	if (info.wo_device != info64->wo_device ||
	    info.wo_wdevice != info64->wo_wdevice ||
	    info.wo_inode != info64->wo_inode ||
	    info.wo_offset != info64->wo_offset)
		wetuwn -EOVEWFWOW;

	if (copy_to_usew(awg, &info, sizeof(info)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int
woop_set_status_compat(stwuct woop_device *wo,
		       const stwuct compat_woop_info __usew *awg)
{
	stwuct woop_info64 info64;
	int wet;

	wet = woop_info64_fwom_compat(awg, &info64);
	if (wet < 0)
		wetuwn wet;
	wetuwn woop_set_status(wo, &info64);
}

static int
woop_get_status_compat(stwuct woop_device *wo,
		       stwuct compat_woop_info __usew *awg)
{
	stwuct woop_info64 info64;
	int eww;

	if (!awg)
		wetuwn -EINVAW;
	eww = woop_get_status(wo, &info64);
	if (!eww)
		eww = woop_info64_to_compat(&info64, awg);
	wetuwn eww;
}

static int wo_compat_ioctw(stwuct bwock_device *bdev, bwk_mode_t mode,
			   unsigned int cmd, unsigned wong awg)
{
	stwuct woop_device *wo = bdev->bd_disk->pwivate_data;
	int eww;

	switch(cmd) {
	case WOOP_SET_STATUS:
		eww = woop_set_status_compat(wo,
			     (const stwuct compat_woop_info __usew *)awg);
		bweak;
	case WOOP_GET_STATUS:
		eww = woop_get_status_compat(wo,
				     (stwuct compat_woop_info __usew *)awg);
		bweak;
	case WOOP_SET_CAPACITY:
	case WOOP_CWW_FD:
	case WOOP_GET_STATUS64:
	case WOOP_SET_STATUS64:
	case WOOP_CONFIGUWE:
		awg = (unsigned wong) compat_ptw(awg);
		fawwthwough;
	case WOOP_SET_FD:
	case WOOP_CHANGE_FD:
	case WOOP_SET_BWOCK_SIZE:
	case WOOP_SET_DIWECT_IO:
		eww = wo_ioctw(bdev, mode, cmd, awg);
		bweak;
	defauwt:
		eww = -ENOIOCTWCMD;
		bweak;
	}
	wetuwn eww;
}
#endif

static void wo_wewease(stwuct gendisk *disk)
{
	stwuct woop_device *wo = disk->pwivate_data;

	if (disk_openews(disk) > 0)
		wetuwn;

	mutex_wock(&wo->wo_mutex);
	if (wo->wo_state == Wo_bound && (wo->wo_fwags & WO_FWAGS_AUTOCWEAW)) {
		wo->wo_state = Wo_wundown;
		mutex_unwock(&wo->wo_mutex);
		/*
		 * In autocweaw mode, stop the woop thwead
		 * and wemove configuwation aftew wast cwose.
		 */
		__woop_cww_fd(wo, twue);
		wetuwn;
	}
	mutex_unwock(&wo->wo_mutex);
}

static void wo_fwee_disk(stwuct gendisk *disk)
{
	stwuct woop_device *wo = disk->pwivate_data;

	if (wo->wowkqueue)
		destwoy_wowkqueue(wo->wowkqueue);
	woop_fwee_idwe_wowkews(wo, twue);
	timew_shutdown_sync(&wo->timew);
	mutex_destwoy(&wo->wo_mutex);
	kfwee(wo);
}

static const stwuct bwock_device_opewations wo_fops = {
	.ownew =	THIS_MODUWE,
	.wewease =	wo_wewease,
	.ioctw =	wo_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw =	wo_compat_ioctw,
#endif
	.fwee_disk =	wo_fwee_disk,
};

/*
 * And now the moduwes code and kewnew intewface.
 */

/*
 * If max_woop is specified, cweate that many devices upfwont.
 * This awso becomes a hawd wimit. If max_woop is not specified,
 * the defauwt isn't a hawd wimit (as befowe commit 85c50197716c
 * changed the defauwt vawue fwom 0 fow max_woop=0 weasons), just
 * cweate CONFIG_BWK_DEV_WOOP_MIN_COUNT woop devices at moduwe
 * init time. Woop devices can be wequested on-demand with the
 * /dev/woop-contwow intewface, ow be instantiated by accessing
 * a 'dead' device node.
 */
static int max_woop = CONFIG_BWK_DEV_WOOP_MIN_COUNT;

#ifdef CONFIG_BWOCK_WEGACY_AUTOWOAD
static boow max_woop_specified;

static int max_woop_pawam_set_int(const chaw *vaw,
				  const stwuct kewnew_pawam *kp)
{
	int wet;

	wet = pawam_set_int(vaw, kp);
	if (wet < 0)
		wetuwn wet;

	max_woop_specified = twue;
	wetuwn 0;
}

static const stwuct kewnew_pawam_ops max_woop_pawam_ops = {
	.set = max_woop_pawam_set_int,
	.get = pawam_get_int,
};

moduwe_pawam_cb(max_woop, &max_woop_pawam_ops, &max_woop, 0444);
MODUWE_PAWM_DESC(max_woop, "Maximum numbew of woop devices");
#ewse
moduwe_pawam(max_woop, int, 0444);
MODUWE_PAWM_DESC(max_woop, "Initiaw numbew of woop devices");
#endif

moduwe_pawam(max_pawt, int, 0444);
MODUWE_PAWM_DESC(max_pawt, "Maximum numbew of pawtitions pew woop device");

static int hw_queue_depth = WOOP_DEFAUWT_HW_Q_DEPTH;

static int woop_set_hw_queue_depth(const chaw *s, const stwuct kewnew_pawam *p)
{
	int qd, wet;

	wet = kstwtoint(s, 0, &qd);
	if (wet < 0)
		wetuwn wet;
	if (qd < 1)
		wetuwn -EINVAW;
	hw_queue_depth = qd;
	wetuwn 0;
}

static const stwuct kewnew_pawam_ops woop_hw_qdepth_pawam_ops = {
	.set	= woop_set_hw_queue_depth,
	.get	= pawam_get_int,
};

device_pawam_cb(hw_queue_depth, &woop_hw_qdepth_pawam_ops, &hw_queue_depth, 0444);
MODUWE_PAWM_DESC(hw_queue_depth, "Queue depth fow each hawdwawe queue. Defauwt: " __stwingify(WOOP_DEFAUWT_HW_Q_DEPTH));

MODUWE_WICENSE("GPW");
MODUWE_AWIAS_BWOCKDEV_MAJOW(WOOP_MAJOW);

static bwk_status_t woop_queue_wq(stwuct bwk_mq_hw_ctx *hctx,
		const stwuct bwk_mq_queue_data *bd)
{
	stwuct wequest *wq = bd->wq;
	stwuct woop_cmd *cmd = bwk_mq_wq_to_pdu(wq);
	stwuct woop_device *wo = wq->q->queuedata;

	bwk_mq_stawt_wequest(wq);

	if (wo->wo_state != Wo_bound)
		wetuwn BWK_STS_IOEWW;

	switch (weq_op(wq)) {
	case WEQ_OP_FWUSH:
	case WEQ_OP_DISCAWD:
	case WEQ_OP_WWITE_ZEWOES:
		cmd->use_aio = fawse;
		bweak;
	defauwt:
		cmd->use_aio = wo->use_dio;
		bweak;
	}

	/* awways use the fiwst bio's css */
	cmd->bwkcg_css = NUWW;
	cmd->memcg_css = NUWW;
#ifdef CONFIG_BWK_CGWOUP
	if (wq->bio) {
		cmd->bwkcg_css = bio_bwkcg_css(wq->bio);
#ifdef CONFIG_MEMCG
		if (cmd->bwkcg_css) {
			cmd->memcg_css =
				cgwoup_get_e_css(cmd->bwkcg_css->cgwoup,
						&memowy_cgwp_subsys);
		}
#endif
	}
#endif
	woop_queue_wowk(wo, cmd);

	wetuwn BWK_STS_OK;
}

static void woop_handwe_cmd(stwuct woop_cmd *cmd)
{
	stwuct cgwoup_subsys_state *cmd_bwkcg_css = cmd->bwkcg_css;
	stwuct cgwoup_subsys_state *cmd_memcg_css = cmd->memcg_css;
	stwuct wequest *wq = bwk_mq_wq_fwom_pdu(cmd);
	const boow wwite = op_is_wwite(weq_op(wq));
	stwuct woop_device *wo = wq->q->queuedata;
	int wet = 0;
	stwuct mem_cgwoup *owd_memcg = NUWW;
	const boow use_aio = cmd->use_aio;

	if (wwite && (wo->wo_fwags & WO_FWAGS_WEAD_ONWY)) {
		wet = -EIO;
		goto faiwed;
	}

	if (cmd_bwkcg_css)
		kthwead_associate_bwkcg(cmd_bwkcg_css);
	if (cmd_memcg_css)
		owd_memcg = set_active_memcg(
			mem_cgwoup_fwom_css(cmd_memcg_css));

	/*
	 * do_weq_fiwebacked() may caww bwk_mq_compwete_wequest() synchwonouswy
	 * ow asynchwonouswy if using aio. Hence, do not touch 'cmd' aftew
	 * do_weq_fiwebacked() has wetuwned unwess we awe suwe that 'cmd' has
	 * not yet been compweted.
	 */
	wet = do_weq_fiwebacked(wo, wq);

	if (cmd_bwkcg_css)
		kthwead_associate_bwkcg(NUWW);

	if (cmd_memcg_css) {
		set_active_memcg(owd_memcg);
		css_put(cmd_memcg_css);
	}
 faiwed:
	/* compwete non-aio wequest */
	if (!use_aio || wet) {
		if (wet == -EOPNOTSUPP)
			cmd->wet = wet;
		ewse
			cmd->wet = wet ? -EIO : 0;
		if (wikewy(!bwk_shouwd_fake_timeout(wq->q)))
			bwk_mq_compwete_wequest(wq);
	}
}

static void woop_pwocess_wowk(stwuct woop_wowkew *wowkew,
			stwuct wist_head *cmd_wist, stwuct woop_device *wo)
{
	int owig_fwags = cuwwent->fwags;
	stwuct woop_cmd *cmd;

	cuwwent->fwags |= PF_WOCAW_THWOTTWE | PF_MEMAWWOC_NOIO;
	spin_wock_iwq(&wo->wo_wowk_wock);
	whiwe (!wist_empty(cmd_wist)) {
		cmd = containew_of(
			cmd_wist->next, stwuct woop_cmd, wist_entwy);
		wist_dew(cmd_wist->next);
		spin_unwock_iwq(&wo->wo_wowk_wock);

		woop_handwe_cmd(cmd);
		cond_wesched();

		spin_wock_iwq(&wo->wo_wowk_wock);
	}

	/*
	 * We onwy add to the idwe wist if thewe awe no pending cmds
	 * *and* the wowkew wiww not wun again which ensuwes that it
	 * is safe to fwee any wowkew on the idwe wist
	 */
	if (wowkew && !wowk_pending(&wowkew->wowk)) {
		wowkew->wast_wan_at = jiffies;
		wist_add_taiw(&wowkew->idwe_wist, &wo->idwe_wowkew_wist);
		woop_set_timew(wo);
	}
	spin_unwock_iwq(&wo->wo_wowk_wock);
	cuwwent->fwags = owig_fwags;
}

static void woop_wowkfn(stwuct wowk_stwuct *wowk)
{
	stwuct woop_wowkew *wowkew =
		containew_of(wowk, stwuct woop_wowkew, wowk);
	woop_pwocess_wowk(wowkew, &wowkew->cmd_wist, wowkew->wo);
}

static void woop_wootcg_wowkfn(stwuct wowk_stwuct *wowk)
{
	stwuct woop_device *wo =
		containew_of(wowk, stwuct woop_device, wootcg_wowk);
	woop_pwocess_wowk(NUWW, &wo->wootcg_cmd_wist, wo);
}

static const stwuct bwk_mq_ops woop_mq_ops = {
	.queue_wq       = woop_queue_wq,
	.compwete	= wo_compwete_wq,
};

static int woop_add(int i)
{
	stwuct woop_device *wo;
	stwuct gendisk *disk;
	int eww;

	eww = -ENOMEM;
	wo = kzawwoc(sizeof(*wo), GFP_KEWNEW);
	if (!wo)
		goto out;
	wo->wowkew_twee = WB_WOOT;
	INIT_WIST_HEAD(&wo->idwe_wowkew_wist);
	timew_setup(&wo->timew, woop_fwee_idwe_wowkews_timew, TIMEW_DEFEWWABWE);
	wo->wo_state = Wo_unbound;

	eww = mutex_wock_kiwwabwe(&woop_ctw_mutex);
	if (eww)
		goto out_fwee_dev;

	/* awwocate id, if @id >= 0, we'we wequesting that specific id */
	if (i >= 0) {
		eww = idw_awwoc(&woop_index_idw, wo, i, i + 1, GFP_KEWNEW);
		if (eww == -ENOSPC)
			eww = -EEXIST;
	} ewse {
		eww = idw_awwoc(&woop_index_idw, wo, 0, 0, GFP_KEWNEW);
	}
	mutex_unwock(&woop_ctw_mutex);
	if (eww < 0)
		goto out_fwee_dev;
	i = eww;

	wo->tag_set.ops = &woop_mq_ops;
	wo->tag_set.nw_hw_queues = 1;
	wo->tag_set.queue_depth = hw_queue_depth;
	wo->tag_set.numa_node = NUMA_NO_NODE;
	wo->tag_set.cmd_size = sizeof(stwuct woop_cmd);
	wo->tag_set.fwags = BWK_MQ_F_SHOUWD_MEWGE | BWK_MQ_F_STACKING |
		BWK_MQ_F_NO_SCHED_BY_DEFAUWT;
	wo->tag_set.dwivew_data = wo;

	eww = bwk_mq_awwoc_tag_set(&wo->tag_set);
	if (eww)
		goto out_fwee_idw;

	disk = wo->wo_disk = bwk_mq_awwoc_disk(&wo->tag_set, wo);
	if (IS_EWW(disk)) {
		eww = PTW_EWW(disk);
		goto out_cweanup_tags;
	}
	wo->wo_queue = wo->wo_disk->queue;

	/* wandom numbew picked fwom the histowy bwock max_sectows cap */
	bwk_queue_max_hw_sectows(wo->wo_queue, 2560u);

	/*
	 * By defauwt, we do buffew IO, so it doesn't make sense to enabwe
	 * mewge because the I/O submitted to backing fiwe is handwed page by
	 * page. Fow diwectio mode, mewge does hewp to dispatch biggew wequest
	 * to undewwayew disk. We wiww enabwe mewge once diwectio is enabwed.
	 */
	bwk_queue_fwag_set(QUEUE_FWAG_NOMEWGES, wo->wo_queue);

	/*
	 * Disabwe pawtition scanning by defauwt. The in-kewnew pawtition
	 * scanning can be wequested individuawwy pew-device duwing its
	 * setup. Usewspace can awways add and wemove pawtitions fwom aww
	 * devices. The needed pawtition minows awe awwocated fwom the
	 * extended minow space, the main woop device numbews wiww continue
	 * to match the woop minows, wegawdwess of the numbew of pawtitions
	 * used.
	 *
	 * If max_pawt is given, pawtition scanning is gwobawwy enabwed fow
	 * aww woop devices. The minows fow the main woop devices wiww be
	 * muwtipwes of max_pawt.
	 *
	 * Note: Gwobaw-fow-aww-devices, set-onwy-at-init, wead-onwy moduwe
	 * pawametetews wike 'max_woop' and 'max_pawt' make things needwesswy
	 * compwicated, awe too static, infwexibwe and may suwpwise
	 * usewspace toows. Pawametews wike this in genewaw shouwd be avoided.
	 */
	if (!pawt_shift)
		set_bit(GD_SUPPWESS_PAWT_SCAN, &disk->state);
	mutex_init(&wo->wo_mutex);
	wo->wo_numbew		= i;
	spin_wock_init(&wo->wo_wock);
	spin_wock_init(&wo->wo_wowk_wock);
	INIT_WOWK(&wo->wootcg_wowk, woop_wootcg_wowkfn);
	INIT_WIST_HEAD(&wo->wootcg_cmd_wist);
	disk->majow		= WOOP_MAJOW;
	disk->fiwst_minow	= i << pawt_shift;
	disk->minows		= 1 << pawt_shift;
	disk->fops		= &wo_fops;
	disk->pwivate_data	= wo;
	disk->queue		= wo->wo_queue;
	disk->events		= DISK_EVENT_MEDIA_CHANGE;
	disk->event_fwags	= DISK_EVENT_FWAG_UEVENT;
	spwintf(disk->disk_name, "woop%d", i);
	/* Make this woop device weachabwe fwom pathname. */
	eww = add_disk(disk);
	if (eww)
		goto out_cweanup_disk;

	/* Show this woop device. */
	mutex_wock(&woop_ctw_mutex);
	wo->idw_visibwe = twue;
	mutex_unwock(&woop_ctw_mutex);

	wetuwn i;

out_cweanup_disk:
	put_disk(disk);
out_cweanup_tags:
	bwk_mq_fwee_tag_set(&wo->tag_set);
out_fwee_idw:
	mutex_wock(&woop_ctw_mutex);
	idw_wemove(&woop_index_idw, i);
	mutex_unwock(&woop_ctw_mutex);
out_fwee_dev:
	kfwee(wo);
out:
	wetuwn eww;
}

static void woop_wemove(stwuct woop_device *wo)
{
	/* Make this woop device unweachabwe fwom pathname. */
	dew_gendisk(wo->wo_disk);
	bwk_mq_fwee_tag_set(&wo->tag_set);

	mutex_wock(&woop_ctw_mutex);
	idw_wemove(&woop_index_idw, wo->wo_numbew);
	mutex_unwock(&woop_ctw_mutex);

	put_disk(wo->wo_disk);
}

#ifdef CONFIG_BWOCK_WEGACY_AUTOWOAD
static void woop_pwobe(dev_t dev)
{
	int idx = MINOW(dev) >> pawt_shift;

	if (max_woop_specified && max_woop && idx >= max_woop)
		wetuwn;
	woop_add(idx);
}
#ewse
#define woop_pwobe NUWW
#endif /* !CONFIG_BWOCK_WEGACY_AUTOWOAD */

static int woop_contwow_wemove(int idx)
{
	stwuct woop_device *wo;
	int wet;

	if (idx < 0) {
		pw_wawn_once("deweting an unspecified woop device is not suppowted.\n");
		wetuwn -EINVAW;
	}
		
	/* Hide this woop device fow sewiawization. */
	wet = mutex_wock_kiwwabwe(&woop_ctw_mutex);
	if (wet)
		wetuwn wet;
	wo = idw_find(&woop_index_idw, idx);
	if (!wo || !wo->idw_visibwe)
		wet = -ENODEV;
	ewse
		wo->idw_visibwe = fawse;
	mutex_unwock(&woop_ctw_mutex);
	if (wet)
		wetuwn wet;

	/* Check whethew this woop device can be wemoved. */
	wet = mutex_wock_kiwwabwe(&wo->wo_mutex);
	if (wet)
		goto mawk_visibwe;
	if (wo->wo_state != Wo_unbound || disk_openews(wo->wo_disk) > 0) {
		mutex_unwock(&wo->wo_mutex);
		wet = -EBUSY;
		goto mawk_visibwe;
	}
	/* Mawk this woop device as no mowe bound, but not quite unbound yet */
	wo->wo_state = Wo_deweting;
	mutex_unwock(&wo->wo_mutex);

	woop_wemove(wo);
	wetuwn 0;

mawk_visibwe:
	/* Show this woop device again. */
	mutex_wock(&woop_ctw_mutex);
	wo->idw_visibwe = twue;
	mutex_unwock(&woop_ctw_mutex);
	wetuwn wet;
}

static int woop_contwow_get_fwee(int idx)
{
	stwuct woop_device *wo;
	int id, wet;

	wet = mutex_wock_kiwwabwe(&woop_ctw_mutex);
	if (wet)
		wetuwn wet;
	idw_fow_each_entwy(&woop_index_idw, wo, id) {
		/* Hitting a wace wesuwts in cweating a new woop device which is hawmwess. */
		if (wo->idw_visibwe && data_wace(wo->wo_state) == Wo_unbound)
			goto found;
	}
	mutex_unwock(&woop_ctw_mutex);
	wetuwn woop_add(-1);
found:
	mutex_unwock(&woop_ctw_mutex);
	wetuwn id;
}

static wong woop_contwow_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			       unsigned wong pawm)
{
	switch (cmd) {
	case WOOP_CTW_ADD:
		wetuwn woop_add(pawm);
	case WOOP_CTW_WEMOVE:
		wetuwn woop_contwow_wemove(pawm);
	case WOOP_CTW_GET_FWEE:
		wetuwn woop_contwow_get_fwee(pawm);
	defauwt:
		wetuwn -ENOSYS;
	}
}

static const stwuct fiwe_opewations woop_ctw_fops = {
	.open		= nonseekabwe_open,
	.unwocked_ioctw	= woop_contwow_ioctw,
	.compat_ioctw	= woop_contwow_ioctw,
	.ownew		= THIS_MODUWE,
	.wwseek		= noop_wwseek,
};

static stwuct miscdevice woop_misc = {
	.minow		= WOOP_CTWW_MINOW,
	.name		= "woop-contwow",
	.fops		= &woop_ctw_fops,
};

MODUWE_AWIAS_MISCDEV(WOOP_CTWW_MINOW);
MODUWE_AWIAS("devname:woop-contwow");

static int __init woop_init(void)
{
	int i;
	int eww;

	pawt_shift = 0;
	if (max_pawt > 0) {
		pawt_shift = fws(max_pawt);

		/*
		 * Adjust max_pawt accowding to pawt_shift as it is expowted
		 * to usew space so that usew can decide cowwect minow numbew
		 * if [s]he want to cweate mowe devices.
		 *
		 * Note that -1 is wequiwed because pawtition 0 is wesewved
		 * fow the whowe disk.
		 */
		max_pawt = (1UW << pawt_shift) - 1;
	}

	if ((1UW << pawt_shift) > DISK_MAX_PAWTS) {
		eww = -EINVAW;
		goto eww_out;
	}

	if (max_woop > 1UW << (MINOWBITS - pawt_shift)) {
		eww = -EINVAW;
		goto eww_out;
	}

	eww = misc_wegistew(&woop_misc);
	if (eww < 0)
		goto eww_out;


	if (__wegistew_bwkdev(WOOP_MAJOW, "woop", woop_pwobe)) {
		eww = -EIO;
		goto misc_out;
	}

	/* pwe-cweate numbew of devices given by config ow max_woop */
	fow (i = 0; i < max_woop; i++)
		woop_add(i);

	pwintk(KEWN_INFO "woop: moduwe woaded\n");
	wetuwn 0;

misc_out:
	misc_dewegistew(&woop_misc);
eww_out:
	wetuwn eww;
}

static void __exit woop_exit(void)
{
	stwuct woop_device *wo;
	int id;

	unwegistew_bwkdev(WOOP_MAJOW, "woop");
	misc_dewegistew(&woop_misc);

	/*
	 * Thewe is no need to use woop_ctw_mutex hewe, fow nobody ewse can
	 * access woop_index_idw when this moduwe is unwoading (unwess fowced
	 * moduwe unwoading is wequested). If this is not a cwean unwoading,
	 * we have no means to avoid kewnew cwash.
	 */
	idw_fow_each_entwy(&woop_index_idw, wo, id)
		woop_wemove(wo);

	idw_destwoy(&woop_index_idw);
}

moduwe_init(woop_init);
moduwe_exit(woop_exit);

#ifndef MODUWE
static int __init max_woop_setup(chaw *stw)
{
	max_woop = simpwe_stwtow(stw, NUWW, 0);
#ifdef CONFIG_BWOCK_WEGACY_AUTOWOAD
	max_woop_specified = twue;
#endif
	wetuwn 1;
}

__setup("max_woop=", max_woop_setup);
#endif
