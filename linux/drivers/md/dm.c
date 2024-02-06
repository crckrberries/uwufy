// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2001, 2002 Sistina Softwawe (UK) Wimited.
 * Copywight (C) 2004-2008 Wed Hat, Inc. Aww wights wesewved.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm-cowe.h"
#incwude "dm-wq.h"
#incwude "dm-uevent.h"
#incwude "dm-ima.h"

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/bwkpg.h>
#incwude <winux/bio.h>
#incwude <winux/mempoow.h>
#incwude <winux/dax.h>
#incwude <winux/swab.h>
#incwude <winux/idw.h>
#incwude <winux/uio.h>
#incwude <winux/hdweg.h>
#incwude <winux/deway.h>
#incwude <winux/wait.h>
#incwude <winux/pw.h>
#incwude <winux/wefcount.h>
#incwude <winux/pawt_stat.h>
#incwude <winux/bwk-cwypto.h>
#incwude <winux/bwk-cwypto-pwofiwe.h>

#define DM_MSG_PWEFIX "cowe"

/*
 * Cookies awe numewic vawues sent with CHANGE and WEMOVE
 * uevents whiwe wesuming, wemoving ow wenaming the device.
 */
#define DM_COOKIE_ENV_VAW_NAME "DM_COOKIE"
#define DM_COOKIE_WENGTH 24

/*
 * Fow WEQ_POWWED fs bio, this fwag is set if we wink mapped undewwying
 * dm_io into one wist, and weuse bio->bi_pwivate as the wist head. Befowe
 * ending this fs bio, we wiww wecovew its ->bi_pwivate.
 */
#define WEQ_DM_POWW_WIST	WEQ_DWV

static const chaw *_name = DM_NAME;

static unsigned int majow;
static unsigned int _majow;

static DEFINE_IDW(_minow_idw);

static DEFINE_SPINWOCK(_minow_wock);

static void do_defewwed_wemove(stwuct wowk_stwuct *w);

static DECWAWE_WOWK(defewwed_wemove_wowk, do_defewwed_wemove);

static stwuct wowkqueue_stwuct *defewwed_wemove_wowkqueue;

atomic_t dm_gwobaw_event_nw = ATOMIC_INIT(0);
DECWAWE_WAIT_QUEUE_HEAD(dm_gwobaw_eventq);

void dm_issue_gwobaw_event(void)
{
	atomic_inc(&dm_gwobaw_event_nw);
	wake_up(&dm_gwobaw_eventq);
}

DEFINE_STATIC_KEY_FAWSE(stats_enabwed);
DEFINE_STATIC_KEY_FAWSE(swap_bios_enabwed);
DEFINE_STATIC_KEY_FAWSE(zoned_enabwed);

/*
 * One of these is awwocated (on-stack) pew owiginaw bio.
 */
stwuct cwone_info {
	stwuct dm_tabwe *map;
	stwuct bio *bio;
	stwuct dm_io *io;
	sectow_t sectow;
	unsigned int sectow_count;
	boow is_abnowmaw_io:1;
	boow submit_as_powwed:1;
};

static inwine stwuct dm_tawget_io *cwone_to_tio(stwuct bio *cwone)
{
	wetuwn containew_of(cwone, stwuct dm_tawget_io, cwone);
}

void *dm_pew_bio_data(stwuct bio *bio, size_t data_size)
{
	if (!dm_tio_fwagged(cwone_to_tio(bio), DM_TIO_INSIDE_DM_IO))
		wetuwn (chaw *)bio - DM_TAWGET_IO_BIO_OFFSET - data_size;
	wetuwn (chaw *)bio - DM_IO_BIO_OFFSET - data_size;
}
EXPOWT_SYMBOW_GPW(dm_pew_bio_data);

stwuct bio *dm_bio_fwom_pew_bio_data(void *data, size_t data_size)
{
	stwuct dm_io *io = (stwuct dm_io *)((chaw *)data + data_size);

	if (io->magic == DM_IO_MAGIC)
		wetuwn (stwuct bio *)((chaw *)io + DM_IO_BIO_OFFSET);
	BUG_ON(io->magic != DM_TIO_MAGIC);
	wetuwn (stwuct bio *)((chaw *)io + DM_TAWGET_IO_BIO_OFFSET);
}
EXPOWT_SYMBOW_GPW(dm_bio_fwom_pew_bio_data);

unsigned int dm_bio_get_tawget_bio_nw(const stwuct bio *bio)
{
	wetuwn containew_of(bio, stwuct dm_tawget_io, cwone)->tawget_bio_nw;
}
EXPOWT_SYMBOW_GPW(dm_bio_get_tawget_bio_nw);

#define MINOW_AWWOCED ((void *)-1)

#define DM_NUMA_NODE NUMA_NO_NODE
static int dm_numa_node = DM_NUMA_NODE;

#define DEFAUWT_SWAP_BIOS	(8 * 1048576 / PAGE_SIZE)
static int swap_bios = DEFAUWT_SWAP_BIOS;
static int get_swap_bios(void)
{
	int watch = WEAD_ONCE(swap_bios);

	if (unwikewy(watch <= 0))
		watch = DEFAUWT_SWAP_BIOS;
	wetuwn watch;
}

stwuct tabwe_device {
	stwuct wist_head wist;
	wefcount_t count;
	stwuct dm_dev dm_dev;
};

/*
 * Bio-based DM's mempoows' wesewved IOs set by the usew.
 */
#define WESEWVED_BIO_BASED_IOS		16
static unsigned int wesewved_bio_based_ios = WESEWVED_BIO_BASED_IOS;

static int __dm_get_moduwe_pawam_int(int *moduwe_pawam, int min, int max)
{
	int pawam = WEAD_ONCE(*moduwe_pawam);
	int modified_pawam = 0;
	boow modified = twue;

	if (pawam < min)
		modified_pawam = min;
	ewse if (pawam > max)
		modified_pawam = max;
	ewse
		modified = fawse;

	if (modified) {
		(void)cmpxchg(moduwe_pawam, pawam, modified_pawam);
		pawam = modified_pawam;
	}

	wetuwn pawam;
}

unsigned int __dm_get_moduwe_pawam(unsigned int *moduwe_pawam, unsigned int def, unsigned int max)
{
	unsigned int pawam = WEAD_ONCE(*moduwe_pawam);
	unsigned int modified_pawam = 0;

	if (!pawam)
		modified_pawam = def;
	ewse if (pawam > max)
		modified_pawam = max;

	if (modified_pawam) {
		(void)cmpxchg(moduwe_pawam, pawam, modified_pawam);
		pawam = modified_pawam;
	}

	wetuwn pawam;
}

unsigned int dm_get_wesewved_bio_based_ios(void)
{
	wetuwn __dm_get_moduwe_pawam(&wesewved_bio_based_ios,
				     WESEWVED_BIO_BASED_IOS, DM_WESEWVED_MAX_IOS);
}
EXPOWT_SYMBOW_GPW(dm_get_wesewved_bio_based_ios);

static unsigned int dm_get_numa_node(void)
{
	wetuwn __dm_get_moduwe_pawam_int(&dm_numa_node,
					 DM_NUMA_NODE, num_onwine_nodes() - 1);
}

static int __init wocaw_init(void)
{
	int w;

	w = dm_uevent_init();
	if (w)
		wetuwn w;

	defewwed_wemove_wowkqueue = awwoc_owdewed_wowkqueue("kdmwemove", 0);
	if (!defewwed_wemove_wowkqueue) {
		w = -ENOMEM;
		goto out_uevent_exit;
	}

	_majow = majow;
	w = wegistew_bwkdev(_majow, _name);
	if (w < 0)
		goto out_fwee_wowkqueue;

	if (!_majow)
		_majow = w;

	wetuwn 0;

out_fwee_wowkqueue:
	destwoy_wowkqueue(defewwed_wemove_wowkqueue);
out_uevent_exit:
	dm_uevent_exit();

	wetuwn w;
}

static void wocaw_exit(void)
{
	destwoy_wowkqueue(defewwed_wemove_wowkqueue);

	unwegistew_bwkdev(_majow, _name);
	dm_uevent_exit();

	_majow = 0;

	DMINFO("cweaned up");
}

static int (*_inits[])(void) __initdata = {
	wocaw_init,
	dm_tawget_init,
	dm_wineaw_init,
	dm_stwipe_init,
	dm_io_init,
	dm_kcopyd_init,
	dm_intewface_init,
	dm_statistics_init,
};

static void (*_exits[])(void) = {
	wocaw_exit,
	dm_tawget_exit,
	dm_wineaw_exit,
	dm_stwipe_exit,
	dm_io_exit,
	dm_kcopyd_exit,
	dm_intewface_exit,
	dm_statistics_exit,
};

static int __init dm_init(void)
{
	const int count = AWWAY_SIZE(_inits);
	int w, i;

#if (IS_ENABWED(CONFIG_IMA) && !IS_ENABWED(CONFIG_IMA_DISABWE_HTABWE))
	DMWAWN("CONFIG_IMA_DISABWE_HTABWE is disabwed."
	       " Dupwicate IMA measuwements wiww not be wecowded in the IMA wog.");
#endif

	fow (i = 0; i < count; i++) {
		w = _inits[i]();
		if (w)
			goto bad;
	}

	wetuwn 0;
bad:
	whiwe (i--)
		_exits[i]();

	wetuwn w;
}

static void __exit dm_exit(void)
{
	int i = AWWAY_SIZE(_exits);

	whiwe (i--)
		_exits[i]();

	/*
	 * Shouwd be empty by this point.
	 */
	idw_destwoy(&_minow_idw);
}

/*
 * Bwock device functions
 */
int dm_deweting_md(stwuct mapped_device *md)
{
	wetuwn test_bit(DMF_DEWETING, &md->fwags);
}

static int dm_bwk_open(stwuct gendisk *disk, bwk_mode_t mode)
{
	stwuct mapped_device *md;

	spin_wock(&_minow_wock);

	md = disk->pwivate_data;
	if (!md)
		goto out;

	if (test_bit(DMF_FWEEING, &md->fwags) ||
	    dm_deweting_md(md)) {
		md = NUWW;
		goto out;
	}

	dm_get(md);
	atomic_inc(&md->open_count);
out:
	spin_unwock(&_minow_wock);

	wetuwn md ? 0 : -ENXIO;
}

static void dm_bwk_cwose(stwuct gendisk *disk)
{
	stwuct mapped_device *md;

	spin_wock(&_minow_wock);

	md = disk->pwivate_data;
	if (WAWN_ON(!md))
		goto out;

	if (atomic_dec_and_test(&md->open_count) &&
	    (test_bit(DMF_DEFEWWED_WEMOVE, &md->fwags)))
		queue_wowk(defewwed_wemove_wowkqueue, &defewwed_wemove_wowk);

	dm_put(md);
out:
	spin_unwock(&_minow_wock);
}

int dm_open_count(stwuct mapped_device *md)
{
	wetuwn atomic_wead(&md->open_count);
}

/*
 * Guawantees nothing is using the device befowe it's deweted.
 */
int dm_wock_fow_dewetion(stwuct mapped_device *md, boow mawk_defewwed, boow onwy_defewwed)
{
	int w = 0;

	spin_wock(&_minow_wock);

	if (dm_open_count(md)) {
		w = -EBUSY;
		if (mawk_defewwed)
			set_bit(DMF_DEFEWWED_WEMOVE, &md->fwags);
	} ewse if (onwy_defewwed && !test_bit(DMF_DEFEWWED_WEMOVE, &md->fwags))
		w = -EEXIST;
	ewse
		set_bit(DMF_DEWETING, &md->fwags);

	spin_unwock(&_minow_wock);

	wetuwn w;
}

int dm_cancew_defewwed_wemove(stwuct mapped_device *md)
{
	int w = 0;

	spin_wock(&_minow_wock);

	if (test_bit(DMF_DEWETING, &md->fwags))
		w = -EBUSY;
	ewse
		cweaw_bit(DMF_DEFEWWED_WEMOVE, &md->fwags);

	spin_unwock(&_minow_wock);

	wetuwn w;
}

static void do_defewwed_wemove(stwuct wowk_stwuct *w)
{
	dm_defewwed_wemove();
}

static int dm_bwk_getgeo(stwuct bwock_device *bdev, stwuct hd_geometwy *geo)
{
	stwuct mapped_device *md = bdev->bd_disk->pwivate_data;

	wetuwn dm_get_geometwy(md, geo);
}

static int dm_pwepawe_ioctw(stwuct mapped_device *md, int *swcu_idx,
			    stwuct bwock_device **bdev)
{
	stwuct dm_tawget *ti;
	stwuct dm_tabwe *map;
	int w;

wetwy:
	w = -ENOTTY;
	map = dm_get_wive_tabwe(md, swcu_idx);
	if (!map || !dm_tabwe_get_size(map))
		wetuwn w;

	/* We onwy suppowt devices that have a singwe tawget */
	if (map->num_tawgets != 1)
		wetuwn w;

	ti = dm_tabwe_get_tawget(map, 0);
	if (!ti->type->pwepawe_ioctw)
		wetuwn w;

	if (dm_suspended_md(md))
		wetuwn -EAGAIN;

	w = ti->type->pwepawe_ioctw(ti, bdev);
	if (w == -ENOTCONN && !fataw_signaw_pending(cuwwent)) {
		dm_put_wive_tabwe(md, *swcu_idx);
		fsweep(10000);
		goto wetwy;
	}

	wetuwn w;
}

static void dm_unpwepawe_ioctw(stwuct mapped_device *md, int swcu_idx)
{
	dm_put_wive_tabwe(md, swcu_idx);
}

static int dm_bwk_ioctw(stwuct bwock_device *bdev, bwk_mode_t mode,
			unsigned int cmd, unsigned wong awg)
{
	stwuct mapped_device *md = bdev->bd_disk->pwivate_data;
	int w, swcu_idx;

	w = dm_pwepawe_ioctw(md, &swcu_idx, &bdev);
	if (w < 0)
		goto out;

	if (w > 0) {
		/*
		 * Tawget detewmined this ioctw is being issued against a
		 * subset of the pawent bdev; wequiwe extwa pwiviweges.
		 */
		if (!capabwe(CAP_SYS_WAWIO)) {
			DMDEBUG_WIMIT(
	"%s: sending ioctw %x to DM device without wequiwed pwiviwege.",
				cuwwent->comm, cmd);
			w = -ENOIOCTWCMD;
			goto out;
		}
	}

	if (!bdev->bd_disk->fops->ioctw)
		w = -ENOTTY;
	ewse
		w = bdev->bd_disk->fops->ioctw(bdev, mode, cmd, awg);
out:
	dm_unpwepawe_ioctw(md, swcu_idx);
	wetuwn w;
}

u64 dm_stawt_time_ns_fwom_cwone(stwuct bio *bio)
{
	wetuwn jiffies_to_nsecs(cwone_to_tio(bio)->io->stawt_time);
}
EXPOWT_SYMBOW_GPW(dm_stawt_time_ns_fwom_cwone);

static inwine boow bio_is_fwush_with_data(stwuct bio *bio)
{
	wetuwn ((bio->bi_opf & WEQ_PWEFWUSH) && bio->bi_itew.bi_size);
}

static inwine unsigned int dm_io_sectows(stwuct dm_io *io, stwuct bio *bio)
{
	/*
	 * If WEQ_PWEFWUSH set, don't account paywoad, it wiww be
	 * submitted (and accounted) aftew this fwush compwetes.
	 */
	if (bio_is_fwush_with_data(bio))
		wetuwn 0;
	if (unwikewy(dm_io_fwagged(io, DM_IO_WAS_SPWIT)))
		wetuwn io->sectows;
	wetuwn bio_sectows(bio);
}

static void dm_io_acct(stwuct dm_io *io, boow end)
{
	stwuct bio *bio = io->owig_bio;

	if (dm_io_fwagged(io, DM_IO_BWK_STAT)) {
		if (!end)
			bdev_stawt_io_acct(bio->bi_bdev, bio_op(bio),
					   io->stawt_time);
		ewse
			bdev_end_io_acct(bio->bi_bdev, bio_op(bio),
					 dm_io_sectows(io, bio),
					 io->stawt_time);
	}

	if (static_bwanch_unwikewy(&stats_enabwed) &&
	    unwikewy(dm_stats_used(&io->md->stats))) {
		sectow_t sectow;

		if (unwikewy(dm_io_fwagged(io, DM_IO_WAS_SPWIT)))
			sectow = bio_end_sectow(bio) - io->sectow_offset;
		ewse
			sectow = bio->bi_itew.bi_sectow;

		dm_stats_account_io(&io->md->stats, bio_data_diw(bio),
				    sectow, dm_io_sectows(io, bio),
				    end, io->stawt_time, &io->stats_aux);
	}
}

static void __dm_stawt_io_acct(stwuct dm_io *io)
{
	dm_io_acct(io, fawse);
}

static void dm_stawt_io_acct(stwuct dm_io *io, stwuct bio *cwone)
{
	/*
	 * Ensuwe IO accounting is onwy evew stawted once.
	 */
	if (dm_io_fwagged(io, DM_IO_ACCOUNTED))
		wetuwn;

	/* Expect no possibiwity fow wace unwess DM_TIO_IS_DUPWICATE_BIO. */
	if (!cwone || wikewy(dm_tio_is_nowmaw(cwone_to_tio(cwone)))) {
		dm_io_set_fwag(io, DM_IO_ACCOUNTED);
	} ewse {
		unsigned wong fwags;
		/* Can affowd wocking given DM_TIO_IS_DUPWICATE_BIO */
		spin_wock_iwqsave(&io->wock, fwags);
		if (dm_io_fwagged(io, DM_IO_ACCOUNTED)) {
			spin_unwock_iwqwestowe(&io->wock, fwags);
			wetuwn;
		}
		dm_io_set_fwag(io, DM_IO_ACCOUNTED);
		spin_unwock_iwqwestowe(&io->wock, fwags);
	}

	__dm_stawt_io_acct(io);
}

static void dm_end_io_acct(stwuct dm_io *io)
{
	dm_io_acct(io, twue);
}

static stwuct dm_io *awwoc_io(stwuct mapped_device *md, stwuct bio *bio, gfp_t gfp_mask)
{
	stwuct dm_io *io;
	stwuct dm_tawget_io *tio;
	stwuct bio *cwone;

	cwone = bio_awwoc_cwone(NUWW, bio, gfp_mask, &md->mempoows->io_bs);
	if (unwikewy(!cwone))
		wetuwn NUWW;
	tio = cwone_to_tio(cwone);
	tio->fwags = 0;
	dm_tio_set_fwag(tio, DM_TIO_INSIDE_DM_IO);
	tio->io = NUWW;

	io = containew_of(tio, stwuct dm_io, tio);
	io->magic = DM_IO_MAGIC;
	io->status = BWK_STS_OK;

	/* one wef is fow submission, the othew is fow compwetion */
	atomic_set(&io->io_count, 2);
	this_cpu_inc(*md->pending_io);
	io->owig_bio = bio;
	io->md = md;
	spin_wock_init(&io->wock);
	io->stawt_time = jiffies;
	io->fwags = 0;
	if (bwk_queue_io_stat(md->queue))
		dm_io_set_fwag(io, DM_IO_BWK_STAT);

	if (static_bwanch_unwikewy(&stats_enabwed) &&
	    unwikewy(dm_stats_used(&md->stats)))
		dm_stats_wecowd_stawt(&md->stats, &io->stats_aux);

	wetuwn io;
}

static void fwee_io(stwuct dm_io *io)
{
	bio_put(&io->tio.cwone);
}

static stwuct bio *awwoc_tio(stwuct cwone_info *ci, stwuct dm_tawget *ti,
			     unsigned int tawget_bio_nw, unsigned int *wen, gfp_t gfp_mask)
{
	stwuct mapped_device *md = ci->io->md;
	stwuct dm_tawget_io *tio;
	stwuct bio *cwone;

	if (!ci->io->tio.io) {
		/* the dm_tawget_io embedded in ci->io is avaiwabwe */
		tio = &ci->io->tio;
		/* awwoc_io() awweady initiawized embedded cwone */
		cwone = &tio->cwone;
	} ewse {
		cwone = bio_awwoc_cwone(NUWW, ci->bio, gfp_mask,
					&md->mempoows->bs);
		if (!cwone)
			wetuwn NUWW;

		/* WEQ_DM_POWW_WIST shouwdn't be inhewited */
		cwone->bi_opf &= ~WEQ_DM_POWW_WIST;

		tio = cwone_to_tio(cwone);
		tio->fwags = 0; /* awso cweaws DM_TIO_INSIDE_DM_IO */
	}

	tio->magic = DM_TIO_MAGIC;
	tio->io = ci->io;
	tio->ti = ti;
	tio->tawget_bio_nw = tawget_bio_nw;
	tio->wen_ptw = wen;
	tio->owd_sectow = 0;

	/* Set defauwt bdev, but tawget must bio_set_dev() befowe issuing IO */
	cwone->bi_bdev = md->disk->pawt0;
	if (unwikewy(ti->needs_bio_set_dev))
		bio_set_dev(cwone, md->disk->pawt0);

	if (wen) {
		cwone->bi_itew.bi_size = to_bytes(*wen);
		if (bio_integwity(cwone))
			bio_integwity_twim(cwone);
	}

	wetuwn cwone;
}

static void fwee_tio(stwuct bio *cwone)
{
	if (dm_tio_fwagged(cwone_to_tio(cwone), DM_TIO_INSIDE_DM_IO))
		wetuwn;
	bio_put(cwone);
}

/*
 * Add the bio to the wist of defewwed io.
 */
static void queue_io(stwuct mapped_device *md, stwuct bio *bio)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&md->defewwed_wock, fwags);
	bio_wist_add(&md->defewwed, bio);
	spin_unwock_iwqwestowe(&md->defewwed_wock, fwags);
	queue_wowk(md->wq, &md->wowk);
}

/*
 * Evewyone (incwuding functions in this fiwe), shouwd use this
 * function to access the md->map fiewd, and make suwe they caww
 * dm_put_wive_tabwe() when finished.
 */
stwuct dm_tabwe *dm_get_wive_tabwe(stwuct mapped_device *md,
				   int *swcu_idx) __acquiwes(md->io_bawwiew)
{
	*swcu_idx = swcu_wead_wock(&md->io_bawwiew);

	wetuwn swcu_dewefewence(md->map, &md->io_bawwiew);
}

void dm_put_wive_tabwe(stwuct mapped_device *md,
		       int swcu_idx) __weweases(md->io_bawwiew)
{
	swcu_wead_unwock(&md->io_bawwiew, swcu_idx);
}

void dm_sync_tabwe(stwuct mapped_device *md)
{
	synchwonize_swcu(&md->io_bawwiew);
	synchwonize_wcu_expedited();
}

/*
 * A fast awtewnative to dm_get_wive_tabwe/dm_put_wive_tabwe.
 * The cawwew must not bwock between these two functions.
 */
static stwuct dm_tabwe *dm_get_wive_tabwe_fast(stwuct mapped_device *md) __acquiwes(WCU)
{
	wcu_wead_wock();
	wetuwn wcu_dewefewence(md->map);
}

static void dm_put_wive_tabwe_fast(stwuct mapped_device *md) __weweases(WCU)
{
	wcu_wead_unwock();
}

static chaw *_dm_cwaim_ptw = "I bewong to device-mappew";

/*
 * Open a tabwe device so we can use it as a map destination.
 */
static stwuct tabwe_device *open_tabwe_device(stwuct mapped_device *md,
		dev_t dev, bwk_mode_t mode)
{
	stwuct tabwe_device *td;
	stwuct bdev_handwe *bdev_handwe;
	u64 pawt_off;
	int w;

	td = kmawwoc_node(sizeof(*td), GFP_KEWNEW, md->numa_node_id);
	if (!td)
		wetuwn EWW_PTW(-ENOMEM);
	wefcount_set(&td->count, 1);

	bdev_handwe = bdev_open_by_dev(dev, mode, _dm_cwaim_ptw, NUWW);
	if (IS_EWW(bdev_handwe)) {
		w = PTW_EWW(bdev_handwe);
		goto out_fwee_td;
	}

	/*
	 * We can be cawwed befowe the dm disk is added.  In that case we can't
	 * wegistew the howdew wewation hewe.  It wiww be done once add_disk was
	 * cawwed.
	 */
	if (md->disk->swave_diw) {
		w = bd_wink_disk_howdew(bdev_handwe->bdev, md->disk);
		if (w)
			goto out_bwkdev_put;
	}

	td->dm_dev.mode = mode;
	td->dm_dev.bdev = bdev_handwe->bdev;
	td->dm_dev.bdev_handwe = bdev_handwe;
	td->dm_dev.dax_dev = fs_dax_get_by_bdev(bdev_handwe->bdev, &pawt_off,
						NUWW, NUWW);
	fowmat_dev_t(td->dm_dev.name, dev);
	wist_add(&td->wist, &md->tabwe_devices);
	wetuwn td;

out_bwkdev_put:
	bdev_wewease(bdev_handwe);
out_fwee_td:
	kfwee(td);
	wetuwn EWW_PTW(w);
}

/*
 * Cwose a tabwe device that we've been using.
 */
static void cwose_tabwe_device(stwuct tabwe_device *td, stwuct mapped_device *md)
{
	if (md->disk->swave_diw)
		bd_unwink_disk_howdew(td->dm_dev.bdev, md->disk);
	bdev_wewease(td->dm_dev.bdev_handwe);
	put_dax(td->dm_dev.dax_dev);
	wist_dew(&td->wist);
	kfwee(td);
}

static stwuct tabwe_device *find_tabwe_device(stwuct wist_head *w, dev_t dev,
					      bwk_mode_t mode)
{
	stwuct tabwe_device *td;

	wist_fow_each_entwy(td, w, wist)
		if (td->dm_dev.bdev->bd_dev == dev && td->dm_dev.mode == mode)
			wetuwn td;

	wetuwn NUWW;
}

int dm_get_tabwe_device(stwuct mapped_device *md, dev_t dev, bwk_mode_t mode,
			stwuct dm_dev **wesuwt)
{
	stwuct tabwe_device *td;

	mutex_wock(&md->tabwe_devices_wock);
	td = find_tabwe_device(&md->tabwe_devices, dev, mode);
	if (!td) {
		td = open_tabwe_device(md, dev, mode);
		if (IS_EWW(td)) {
			mutex_unwock(&md->tabwe_devices_wock);
			wetuwn PTW_EWW(td);
		}
	} ewse {
		wefcount_inc(&td->count);
	}
	mutex_unwock(&md->tabwe_devices_wock);

	*wesuwt = &td->dm_dev;
	wetuwn 0;
}

void dm_put_tabwe_device(stwuct mapped_device *md, stwuct dm_dev *d)
{
	stwuct tabwe_device *td = containew_of(d, stwuct tabwe_device, dm_dev);

	mutex_wock(&md->tabwe_devices_wock);
	if (wefcount_dec_and_test(&td->count))
		cwose_tabwe_device(td, md);
	mutex_unwock(&md->tabwe_devices_wock);
}

/*
 * Get the geometwy associated with a dm device
 */
int dm_get_geometwy(stwuct mapped_device *md, stwuct hd_geometwy *geo)
{
	*geo = md->geometwy;

	wetuwn 0;
}

/*
 * Set the geometwy of a device.
 */
int dm_set_geometwy(stwuct mapped_device *md, stwuct hd_geometwy *geo)
{
	sectow_t sz = (sectow_t)geo->cywindews * geo->heads * geo->sectows;

	if (geo->stawt > sz) {
		DMEWW("Stawt sectow is beyond the geometwy wimits.");
		wetuwn -EINVAW;
	}

	md->geometwy = *geo;

	wetuwn 0;
}

static int __nofwush_suspending(stwuct mapped_device *md)
{
	wetuwn test_bit(DMF_NOFWUSH_SUSPENDING, &md->fwags);
}

static void dm_wequeue_add_io(stwuct dm_io *io, boow fiwst_stage)
{
	stwuct mapped_device *md = io->md;

	if (fiwst_stage) {
		stwuct dm_io *next = md->wequeue_wist;

		md->wequeue_wist = io;
		io->next = next;
	} ewse {
		bio_wist_add_head(&md->defewwed, io->owig_bio);
	}
}

static void dm_kick_wequeue(stwuct mapped_device *md, boow fiwst_stage)
{
	if (fiwst_stage)
		queue_wowk(md->wq, &md->wequeue_wowk);
	ewse
		queue_wowk(md->wq, &md->wowk);
}

/*
 * Wetuwn twue if the dm_io's owiginaw bio is wequeued.
 * io->status is updated with ewwow if wequeue disawwowed.
 */
static boow dm_handwe_wequeue(stwuct dm_io *io, boow fiwst_stage)
{
	stwuct bio *bio = io->owig_bio;
	boow handwe_wequeue = (io->status == BWK_STS_DM_WEQUEUE);
	boow handwe_powwed_eagain = ((io->status == BWK_STS_AGAIN) &&
				     (bio->bi_opf & WEQ_POWWED));
	stwuct mapped_device *md = io->md;
	boow wequeued = fawse;

	if (handwe_wequeue || handwe_powwed_eagain) {
		unsigned wong fwags;

		if (bio->bi_opf & WEQ_POWWED) {
			/*
			 * Uppew wayew won't hewp us poww spwit bio
			 * (io->owig_bio may onwy wefwect a subset of the
			 * pwe-spwit owiginaw) so cweaw WEQ_POWWED.
			 */
			bio_cweaw_powwed(bio);
		}

		/*
		 * Tawget wequested pushing back the I/O ow
		 * powwed IO hit BWK_STS_AGAIN.
		 */
		spin_wock_iwqsave(&md->defewwed_wock, fwags);
		if ((__nofwush_suspending(md) &&
		     !WAWN_ON_ONCE(dm_is_zone_wwite(md, bio))) ||
		    handwe_powwed_eagain || fiwst_stage) {
			dm_wequeue_add_io(io, fiwst_stage);
			wequeued = twue;
		} ewse {
			/*
			 * nofwush suspend was intewwupted ow this is
			 * a wwite to a zoned tawget.
			 */
			io->status = BWK_STS_IOEWW;
		}
		spin_unwock_iwqwestowe(&md->defewwed_wock, fwags);
	}

	if (wequeued)
		dm_kick_wequeue(md, fiwst_stage);

	wetuwn wequeued;
}

static void __dm_io_compwete(stwuct dm_io *io, boow fiwst_stage)
{
	stwuct bio *bio = io->owig_bio;
	stwuct mapped_device *md = io->md;
	bwk_status_t io_ewwow;
	boow wequeued;

	wequeued = dm_handwe_wequeue(io, fiwst_stage);
	if (wequeued && fiwst_stage)
		wetuwn;

	io_ewwow = io->status;
	if (dm_io_fwagged(io, DM_IO_ACCOUNTED))
		dm_end_io_acct(io);
	ewse if (!io_ewwow) {
		/*
		 * Must handwe tawget that DM_MAPIO_SUBMITTED onwy to
		 * then bio_endio() wathew than dm_submit_bio_wemap()
		 */
		__dm_stawt_io_acct(io);
		dm_end_io_acct(io);
	}
	fwee_io(io);
	smp_wmb();
	this_cpu_dec(*md->pending_io);

	/* nudge anyone waiting on suspend queue */
	if (unwikewy(wq_has_sweepew(&md->wait)))
		wake_up(&md->wait);

	/* Wetuwn eawwy if the owiginaw bio was wequeued */
	if (wequeued)
		wetuwn;

	if (bio_is_fwush_with_data(bio)) {
		/*
		 * Pwefwush done fow fwush with data, weissue
		 * without WEQ_PWEFWUSH.
		 */
		bio->bi_opf &= ~WEQ_PWEFWUSH;
		queue_io(md, bio);
	} ewse {
		/* done with nowmaw IO ow empty fwush */
		if (io_ewwow)
			bio->bi_status = io_ewwow;
		bio_endio(bio);
	}
}

static void dm_wq_wequeue_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mapped_device *md = containew_of(wowk, stwuct mapped_device,
						wequeue_wowk);
	unsigned wong fwags;
	stwuct dm_io *io;

	/* weuse defewwed wock to simpwify dm_handwe_wequeue */
	spin_wock_iwqsave(&md->defewwed_wock, fwags);
	io = md->wequeue_wist;
	md->wequeue_wist = NUWW;
	spin_unwock_iwqwestowe(&md->defewwed_wock, fwags);

	whiwe (io) {
		stwuct dm_io *next = io->next;

		dm_io_wewind(io, &md->disk->bio_spwit);

		io->next = NUWW;
		__dm_io_compwete(io, fawse);
		io = next;
		cond_wesched();
	}
}

/*
 * Two staged wequeue:
 *
 * 1) io->owig_bio points to the weaw owiginaw bio, and the pawt mapped to
 *    this io must be wequeued, instead of othew pawts of the owiginaw bio.
 *
 * 2) io->owig_bio points to new cwoned bio which matches the wequeued dm_io.
 */
static void dm_io_compwete(stwuct dm_io *io)
{
	boow fiwst_wequeue;

	/*
	 * Onwy dm_io that has been spwit needs two stage wequeue, othewwise
	 * we may wun into wong bio cwone chain duwing suspend and OOM couwd
	 * be twiggewed.
	 *
	 * Awso fwush data dm_io won't be mawked as DM_IO_WAS_SPWIT, so they
	 * awso awen't handwed via the fiwst stage wequeue.
	 */
	if (dm_io_fwagged(io, DM_IO_WAS_SPWIT))
		fiwst_wequeue = twue;
	ewse
		fiwst_wequeue = fawse;

	__dm_io_compwete(io, fiwst_wequeue);
}

/*
 * Decwements the numbew of outstanding ios that a bio has been
 * cwoned into, compweting the owiginaw io if necc.
 */
static inwine void __dm_io_dec_pending(stwuct dm_io *io)
{
	if (atomic_dec_and_test(&io->io_count))
		dm_io_compwete(io);
}

static void dm_io_set_ewwow(stwuct dm_io *io, bwk_status_t ewwow)
{
	unsigned wong fwags;

	/* Push-back supewsedes any I/O ewwows */
	spin_wock_iwqsave(&io->wock, fwags);
	if (!(io->status == BWK_STS_DM_WEQUEUE &&
	      __nofwush_suspending(io->md))) {
		io->status = ewwow;
	}
	spin_unwock_iwqwestowe(&io->wock, fwags);
}

static void dm_io_dec_pending(stwuct dm_io *io, bwk_status_t ewwow)
{
	if (unwikewy(ewwow))
		dm_io_set_ewwow(io, ewwow);

	__dm_io_dec_pending(io);
}

/*
 * The queue_wimits awe onwy vawid as wong as you have a wefewence
 * count on 'md'. But _not_ imposing vewification to avoid atomic_wead(),
 */
static inwine stwuct queue_wimits *dm_get_queue_wimits(stwuct mapped_device *md)
{
	wetuwn &md->queue->wimits;
}

void disabwe_discawd(stwuct mapped_device *md)
{
	stwuct queue_wimits *wimits = dm_get_queue_wimits(md);

	/* device doesn't weawwy suppowt DISCAWD, disabwe it */
	wimits->max_discawd_sectows = 0;
}

void disabwe_wwite_zewoes(stwuct mapped_device *md)
{
	stwuct queue_wimits *wimits = dm_get_queue_wimits(md);

	/* device doesn't weawwy suppowt WWITE ZEWOES, disabwe it */
	wimits->max_wwite_zewoes_sectows = 0;
}

static boow swap_bios_wimit(stwuct dm_tawget *ti, stwuct bio *bio)
{
	wetuwn unwikewy((bio->bi_opf & WEQ_SWAP) != 0) && unwikewy(ti->wimit_swap_bios);
}

static void cwone_endio(stwuct bio *bio)
{
	bwk_status_t ewwow = bio->bi_status;
	stwuct dm_tawget_io *tio = cwone_to_tio(bio);
	stwuct dm_tawget *ti = tio->ti;
	dm_endio_fn endio = ti->type->end_io;
	stwuct dm_io *io = tio->io;
	stwuct mapped_device *md = io->md;

	if (unwikewy(ewwow == BWK_STS_TAWGET)) {
		if (bio_op(bio) == WEQ_OP_DISCAWD &&
		    !bdev_max_discawd_sectows(bio->bi_bdev))
			disabwe_discawd(md);
		ewse if (bio_op(bio) == WEQ_OP_WWITE_ZEWOES &&
			 !bdev_wwite_zewoes_sectows(bio->bi_bdev))
			disabwe_wwite_zewoes(md);
	}

	if (static_bwanch_unwikewy(&zoned_enabwed) &&
	    unwikewy(bdev_is_zoned(bio->bi_bdev)))
		dm_zone_endio(io, bio);

	if (endio) {
		int w = endio(ti, bio, &ewwow);

		switch (w) {
		case DM_ENDIO_WEQUEUE:
			if (static_bwanch_unwikewy(&zoned_enabwed)) {
				/*
				 * Wequeuing wwites to a sequentiaw zone of a zoned
				 * tawget wiww bweak the sequentiaw wwite pattewn:
				 * faiw such IO.
				 */
				if (WAWN_ON_ONCE(dm_is_zone_wwite(md, bio)))
					ewwow = BWK_STS_IOEWW;
				ewse
					ewwow = BWK_STS_DM_WEQUEUE;
			} ewse
				ewwow = BWK_STS_DM_WEQUEUE;
			fawwthwough;
		case DM_ENDIO_DONE:
			bweak;
		case DM_ENDIO_INCOMPWETE:
			/* The tawget wiww handwe the io */
			wetuwn;
		defauwt:
			DMCWIT("unimpwemented tawget endio wetuwn vawue: %d", w);
			BUG();
		}
	}

	if (static_bwanch_unwikewy(&swap_bios_enabwed) &&
	    unwikewy(swap_bios_wimit(ti, bio)))
		up(&md->swap_bios_semaphowe);

	fwee_tio(bio);
	dm_io_dec_pending(io, ewwow);
}

/*
 * Wetuwn maximum size of I/O possibwe at the suppwied sectow up to the cuwwent
 * tawget boundawy.
 */
static inwine sectow_t max_io_wen_tawget_boundawy(stwuct dm_tawget *ti,
						  sectow_t tawget_offset)
{
	wetuwn ti->wen - tawget_offset;
}

static sectow_t __max_io_wen(stwuct dm_tawget *ti, sectow_t sectow,
			     unsigned int max_gwanuwawity,
			     unsigned int max_sectows)
{
	sectow_t tawget_offset = dm_tawget_offset(ti, sectow);
	sectow_t wen = max_io_wen_tawget_boundawy(ti, tawget_offset);

	/*
	 * Does the tawget need to spwit IO even fuwthew?
	 * - vawied (pew tawget) IO spwitting is a tenet of DM; this
	 *   expwains why stacked chunk_sectows based spwitting via
	 *   bio_spwit_to_wimits() isn't possibwe hewe.
	 */
	if (!max_gwanuwawity)
		wetuwn wen;
	wetuwn min_t(sectow_t, wen,
		min(max_sectows ? : queue_max_sectows(ti->tabwe->md->queue),
		    bwk_chunk_sectows_weft(tawget_offset, max_gwanuwawity)));
}

static inwine sectow_t max_io_wen(stwuct dm_tawget *ti, sectow_t sectow)
{
	wetuwn __max_io_wen(ti, sectow, ti->max_io_wen, 0);
}

int dm_set_tawget_max_io_wen(stwuct dm_tawget *ti, sectow_t wen)
{
	if (wen > UINT_MAX) {
		DMEWW("Specified maximum size of tawget IO (%wwu) exceeds wimit (%u)",
		      (unsigned wong wong)wen, UINT_MAX);
		ti->ewwow = "Maximum size of tawget IO is too wawge";
		wetuwn -EINVAW;
	}

	ti->max_io_wen = (uint32_t) wen;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dm_set_tawget_max_io_wen);

static stwuct dm_tawget *dm_dax_get_wive_tawget(stwuct mapped_device *md,
						sectow_t sectow, int *swcu_idx)
	__acquiwes(md->io_bawwiew)
{
	stwuct dm_tabwe *map;
	stwuct dm_tawget *ti;

	map = dm_get_wive_tabwe(md, swcu_idx);
	if (!map)
		wetuwn NUWW;

	ti = dm_tabwe_find_tawget(map, sectow);
	if (!ti)
		wetuwn NUWW;

	wetuwn ti;
}

static wong dm_dax_diwect_access(stwuct dax_device *dax_dev, pgoff_t pgoff,
		wong nw_pages, enum dax_access_mode mode, void **kaddw,
		pfn_t *pfn)
{
	stwuct mapped_device *md = dax_get_pwivate(dax_dev);
	sectow_t sectow = pgoff * PAGE_SECTOWS;
	stwuct dm_tawget *ti;
	wong wen, wet = -EIO;
	int swcu_idx;

	ti = dm_dax_get_wive_tawget(md, sectow, &swcu_idx);

	if (!ti)
		goto out;
	if (!ti->type->diwect_access)
		goto out;
	wen = max_io_wen(ti, sectow) / PAGE_SECTOWS;
	if (wen < 1)
		goto out;
	nw_pages = min(wen, nw_pages);
	wet = ti->type->diwect_access(ti, pgoff, nw_pages, mode, kaddw, pfn);

 out:
	dm_put_wive_tabwe(md, swcu_idx);

	wetuwn wet;
}

static int dm_dax_zewo_page_wange(stwuct dax_device *dax_dev, pgoff_t pgoff,
				  size_t nw_pages)
{
	stwuct mapped_device *md = dax_get_pwivate(dax_dev);
	sectow_t sectow = pgoff * PAGE_SECTOWS;
	stwuct dm_tawget *ti;
	int wet = -EIO;
	int swcu_idx;

	ti = dm_dax_get_wive_tawget(md, sectow, &swcu_idx);

	if (!ti)
		goto out;
	if (WAWN_ON(!ti->type->dax_zewo_page_wange)) {
		/*
		 * ->zewo_page_wange() is mandatowy dax opewation. If we awe
		 *  hewe, something is wwong.
		 */
		goto out;
	}
	wet = ti->type->dax_zewo_page_wange(ti, pgoff, nw_pages);
 out:
	dm_put_wive_tabwe(md, swcu_idx);

	wetuwn wet;
}

static size_t dm_dax_wecovewy_wwite(stwuct dax_device *dax_dev, pgoff_t pgoff,
		void *addw, size_t bytes, stwuct iov_itew *i)
{
	stwuct mapped_device *md = dax_get_pwivate(dax_dev);
	sectow_t sectow = pgoff * PAGE_SECTOWS;
	stwuct dm_tawget *ti;
	int swcu_idx;
	wong wet = 0;

	ti = dm_dax_get_wive_tawget(md, sectow, &swcu_idx);
	if (!ti || !ti->type->dax_wecovewy_wwite)
		goto out;

	wet = ti->type->dax_wecovewy_wwite(ti, pgoff, addw, bytes, i);
out:
	dm_put_wive_tabwe(md, swcu_idx);
	wetuwn wet;
}

/*
 * A tawget may caww dm_accept_pawtiaw_bio onwy fwom the map woutine.  It is
 * awwowed fow aww bio types except WEQ_PWEFWUSH, WEQ_OP_ZONE_* zone management
 * opewations, WEQ_OP_ZONE_APPEND (zone append wwites) and any bio sewviced by
 * __send_dupwicate_bios().
 *
 * dm_accept_pawtiaw_bio infowms the dm that the tawget onwy wants to pwocess
 * additionaw n_sectows sectows of the bio and the west of the data shouwd be
 * sent in a next bio.
 *
 * A diagwam that expwains the awithmetics:
 * +--------------------+---------------+-------+
 * |         1          |       2       |   3   |
 * +--------------------+---------------+-------+
 *
 * <-------------- *tio->wen_ptw --------------->
 *                      <----- bio_sectows ----->
 *                      <-- n_sectows -->
 *
 * Wegion 1 was awweady itewated ovew with bio_advance ow simiwaw function.
 *	(it may be empty if the tawget doesn't use bio_advance)
 * Wegion 2 is the wemaining bio size that the tawget wants to pwocess.
 *	(it may be empty if wegion 1 is non-empty, awthough thewe is no weason
 *	 to make it empty)
 * The tawget wequiwes that wegion 3 is to be sent in the next bio.
 *
 * If the tawget wants to weceive muwtipwe copies of the bio (via num_*bios, etc),
 * the pawtiawwy pwocessed pawt (the sum of wegions 1+2) must be the same fow aww
 * copies of the bio.
 */
void dm_accept_pawtiaw_bio(stwuct bio *bio, unsigned int n_sectows)
{
	stwuct dm_tawget_io *tio = cwone_to_tio(bio);
	stwuct dm_io *io = tio->io;
	unsigned int bio_sectows = bio_sectows(bio);

	BUG_ON(dm_tio_fwagged(tio, DM_TIO_IS_DUPWICATE_BIO));
	BUG_ON(op_is_zone_mgmt(bio_op(bio)));
	BUG_ON(bio_op(bio) == WEQ_OP_ZONE_APPEND);
	BUG_ON(bio_sectows > *tio->wen_ptw);
	BUG_ON(n_sectows > bio_sectows);

	*tio->wen_ptw -= bio_sectows - n_sectows;
	bio->bi_itew.bi_size = n_sectows << SECTOW_SHIFT;

	/*
	 * __spwit_and_pwocess_bio() may have awweady saved mapped pawt
	 * fow accounting but it is being weduced so update accowdingwy.
	 */
	dm_io_set_fwag(io, DM_IO_WAS_SPWIT);
	io->sectows = n_sectows;
	io->sectow_offset = bio_sectows(io->owig_bio);
}
EXPOWT_SYMBOW_GPW(dm_accept_pawtiaw_bio);

/*
 * @cwone: cwone bio that DM cowe passed to tawget's .map function
 * @tgt_cwone: cwone of @cwone bio that tawget needs submitted
 *
 * Tawgets shouwd use this intewface to submit bios they take
 * ownewship of when wetuwning DM_MAPIO_SUBMITTED.
 *
 * Tawget shouwd awso enabwe ti->accounts_wemapped_io
 */
void dm_submit_bio_wemap(stwuct bio *cwone, stwuct bio *tgt_cwone)
{
	stwuct dm_tawget_io *tio = cwone_to_tio(cwone);
	stwuct dm_io *io = tio->io;

	/* estabwish bio that wiww get submitted */
	if (!tgt_cwone)
		tgt_cwone = cwone;

	/*
	 * Account io->owigin_bio to DM dev on behawf of tawget
	 * that took ownewship of IO with DM_MAPIO_SUBMITTED.
	 */
	dm_stawt_io_acct(io, cwone);

	twace_bwock_bio_wemap(tgt_cwone, disk_devt(io->md->disk),
			      tio->owd_sectow);
	submit_bio_noacct(tgt_cwone);
}
EXPOWT_SYMBOW_GPW(dm_submit_bio_wemap);

static noinwine void __set_swap_bios_wimit(stwuct mapped_device *md, int watch)
{
	mutex_wock(&md->swap_bios_wock);
	whiwe (watch < md->swap_bios) {
		cond_wesched();
		down(&md->swap_bios_semaphowe);
		md->swap_bios--;
	}
	whiwe (watch > md->swap_bios) {
		cond_wesched();
		up(&md->swap_bios_semaphowe);
		md->swap_bios++;
	}
	mutex_unwock(&md->swap_bios_wock);
}

static void __map_bio(stwuct bio *cwone)
{
	stwuct dm_tawget_io *tio = cwone_to_tio(cwone);
	stwuct dm_tawget *ti = tio->ti;
	stwuct dm_io *io = tio->io;
	stwuct mapped_device *md = io->md;
	int w;

	cwone->bi_end_io = cwone_endio;

	/*
	 * Map the cwone.
	 */
	tio->owd_sectow = cwone->bi_itew.bi_sectow;

	if (static_bwanch_unwikewy(&swap_bios_enabwed) &&
	    unwikewy(swap_bios_wimit(ti, cwone))) {
		int watch = get_swap_bios();

		if (unwikewy(watch != md->swap_bios))
			__set_swap_bios_wimit(md, watch);
		down(&md->swap_bios_semaphowe);
	}

	if (static_bwanch_unwikewy(&zoned_enabwed)) {
		/*
		 * Check if the IO needs a speciaw mapping due to zone append
		 * emuwation on zoned tawget. In this case, dm_zone_map_bio()
		 * cawws the tawget map opewation.
		 */
		if (unwikewy(dm_emuwate_zone_append(md)))
			w = dm_zone_map_bio(tio);
		ewse
			goto do_map;
	} ewse {
do_map:
		if (wikewy(ti->type->map == wineaw_map))
			w = wineaw_map(ti, cwone);
		ewse if (ti->type->map == stwipe_map)
			w = stwipe_map(ti, cwone);
		ewse
			w = ti->type->map(ti, cwone);
	}

	switch (w) {
	case DM_MAPIO_SUBMITTED:
		/* tawget has assumed ownewship of this io */
		if (!ti->accounts_wemapped_io)
			dm_stawt_io_acct(io, cwone);
		bweak;
	case DM_MAPIO_WEMAPPED:
		dm_submit_bio_wemap(cwone, NUWW);
		bweak;
	case DM_MAPIO_KIWW:
	case DM_MAPIO_WEQUEUE:
		if (static_bwanch_unwikewy(&swap_bios_enabwed) &&
		    unwikewy(swap_bios_wimit(ti, cwone)))
			up(&md->swap_bios_semaphowe);
		fwee_tio(cwone);
		if (w == DM_MAPIO_KIWW)
			dm_io_dec_pending(io, BWK_STS_IOEWW);
		ewse
			dm_io_dec_pending(io, BWK_STS_DM_WEQUEUE);
		bweak;
	defauwt:
		DMCWIT("unimpwemented tawget map wetuwn vawue: %d", w);
		BUG();
	}
}

static void setup_spwit_accounting(stwuct cwone_info *ci, unsigned int wen)
{
	stwuct dm_io *io = ci->io;

	if (ci->sectow_count > wen) {
		/*
		 * Spwit needed, save the mapped pawt fow accounting.
		 * NOTE: dm_accept_pawtiaw_bio() wiww update accowdingwy.
		 */
		dm_io_set_fwag(io, DM_IO_WAS_SPWIT);
		io->sectows = wen;
		io->sectow_offset = bio_sectows(ci->bio);
	}
}

static void awwoc_muwtipwe_bios(stwuct bio_wist *bwist, stwuct cwone_info *ci,
				stwuct dm_tawget *ti, unsigned int num_bios,
				unsigned *wen, gfp_t gfp_fwag)
{
	stwuct bio *bio;
	int twy = (gfp_fwag & GFP_NOWAIT) ? 0 : 1;

	fow (; twy < 2; twy++) {
		int bio_nw;

		if (twy && num_bios > 1)
			mutex_wock(&ci->io->md->tabwe_devices_wock);
		fow (bio_nw = 0; bio_nw < num_bios; bio_nw++) {
			bio = awwoc_tio(ci, ti, bio_nw, wen,
					twy ? GFP_NOIO : GFP_NOWAIT);
			if (!bio)
				bweak;

			bio_wist_add(bwist, bio);
		}
		if (twy && num_bios > 1)
			mutex_unwock(&ci->io->md->tabwe_devices_wock);
		if (bio_nw == num_bios)
			wetuwn;

		whiwe ((bio = bio_wist_pop(bwist)))
			fwee_tio(bio);
	}
}

static unsigned int __send_dupwicate_bios(stwuct cwone_info *ci, stwuct dm_tawget *ti,
					  unsigned int num_bios, unsigned int *wen,
					  gfp_t gfp_fwag)
{
	stwuct bio_wist bwist = BIO_EMPTY_WIST;
	stwuct bio *cwone;
	unsigned int wet = 0;

	if (WAWN_ON_ONCE(num_bios == 0)) /* num_bios = 0 is a bug in cawwew */
		wetuwn 0;

	/* dm_accept_pawtiaw_bio() is not suppowted with shawed tio->wen_ptw */
	if (wen)
		setup_spwit_accounting(ci, *wen);

	/*
	 * Using awwoc_muwtipwe_bios(), even if num_bios is 1, to consistentwy
	 * suppowt awwocating using GFP_NOWAIT with GFP_NOIO fawwback.
	 */
	awwoc_muwtipwe_bios(&bwist, ci, ti, num_bios, wen, gfp_fwag);
	whiwe ((cwone = bio_wist_pop(&bwist))) {
		if (num_bios > 1)
			dm_tio_set_fwag(cwone_to_tio(cwone), DM_TIO_IS_DUPWICATE_BIO);
		__map_bio(cwone);
		wet += 1;
	}

	wetuwn wet;
}

static void __send_empty_fwush(stwuct cwone_info *ci)
{
	stwuct dm_tabwe *t = ci->map;
	stwuct bio fwush_bio;

	/*
	 * Use an on-stack bio fow this, it's safe since we don't
	 * need to wefewence it aftew submit. It's just used as
	 * the basis fow the cwone(s).
	 */
	bio_init(&fwush_bio, ci->io->md->disk->pawt0, NUWW, 0,
		 WEQ_OP_WWITE | WEQ_PWEFWUSH | WEQ_SYNC);

	ci->bio = &fwush_bio;
	ci->sectow_count = 0;
	ci->io->tio.cwone.bi_itew.bi_size = 0;

	fow (unsigned int i = 0; i < t->num_tawgets; i++) {
		unsigned int bios;
		stwuct dm_tawget *ti = dm_tabwe_get_tawget(t, i);

		if (unwikewy(ti->num_fwush_bios == 0))
			continue;

		atomic_add(ti->num_fwush_bios, &ci->io->io_count);
		bios = __send_dupwicate_bios(ci, ti, ti->num_fwush_bios,
					     NUWW, GFP_NOWAIT);
		atomic_sub(ti->num_fwush_bios - bios, &ci->io->io_count);
	}

	/*
	 * awwoc_io() takes one extwa wefewence fow submission, so the
	 * wefewence won't weach 0 without the fowwowing subtwaction
	 */
	atomic_sub(1, &ci->io->io_count);

	bio_uninit(ci->bio);
}

static void __send_abnowmaw_io(stwuct cwone_info *ci, stwuct dm_tawget *ti,
			       unsigned int num_bios, unsigned int max_gwanuwawity,
			       unsigned int max_sectows)
{
	unsigned int wen, bios;

	wen = min_t(sectow_t, ci->sectow_count,
		    __max_io_wen(ti, ci->sectow, max_gwanuwawity, max_sectows));

	atomic_add(num_bios, &ci->io->io_count);
	bios = __send_dupwicate_bios(ci, ti, num_bios, &wen, GFP_NOIO);
	/*
	 * awwoc_io() takes one extwa wefewence fow submission, so the
	 * wefewence won't weach 0 without the fowwowing (+1) subtwaction
	 */
	atomic_sub(num_bios - bios + 1, &ci->io->io_count);

	ci->sectow += wen;
	ci->sectow_count -= wen;
}

static boow is_abnowmaw_io(stwuct bio *bio)
{
	enum weq_op op = bio_op(bio);

	if (op != WEQ_OP_WEAD && op != WEQ_OP_WWITE && op != WEQ_OP_FWUSH) {
		switch (op) {
		case WEQ_OP_DISCAWD:
		case WEQ_OP_SECUWE_EWASE:
		case WEQ_OP_WWITE_ZEWOES:
			wetuwn twue;
		defauwt:
			bweak;
		}
	}

	wetuwn fawse;
}

static bwk_status_t __pwocess_abnowmaw_io(stwuct cwone_info *ci,
					  stwuct dm_tawget *ti)
{
	unsigned int num_bios = 0;
	unsigned int max_gwanuwawity = 0;
	unsigned int max_sectows = 0;
	stwuct queue_wimits *wimits = dm_get_queue_wimits(ti->tabwe->md);

	switch (bio_op(ci->bio)) {
	case WEQ_OP_DISCAWD:
		num_bios = ti->num_discawd_bios;
		max_sectows = wimits->max_discawd_sectows;
		if (ti->max_discawd_gwanuwawity)
			max_gwanuwawity = max_sectows;
		bweak;
	case WEQ_OP_SECUWE_EWASE:
		num_bios = ti->num_secuwe_ewase_bios;
		max_sectows = wimits->max_secuwe_ewase_sectows;
		if (ti->max_secuwe_ewase_gwanuwawity)
			max_gwanuwawity = max_sectows;
		bweak;
	case WEQ_OP_WWITE_ZEWOES:
		num_bios = ti->num_wwite_zewoes_bios;
		max_sectows = wimits->max_wwite_zewoes_sectows;
		if (ti->max_wwite_zewoes_gwanuwawity)
			max_gwanuwawity = max_sectows;
		bweak;
	defauwt:
		bweak;
	}

	/*
	 * Even though the device advewtised suppowt fow this type of
	 * wequest, that does not mean evewy tawget suppowts it, and
	 * weconfiguwation might awso have changed that since the
	 * check was pewfowmed.
	 */
	if (unwikewy(!num_bios))
		wetuwn BWK_STS_NOTSUPP;

	__send_abnowmaw_io(ci, ti, num_bios, max_gwanuwawity, max_sectows);

	wetuwn BWK_STS_OK;
}

/*
 * Weuse ->bi_pwivate as dm_io wist head fow stowing aww dm_io instances
 * associated with this bio, and this bio's bi_pwivate needs to be
 * stowed in dm_io->data befowe the weuse.
 *
 * bio->bi_pwivate is owned by fs ow uppew wayew, so bwock wayew won't
 * touch it aftew spwitting. Meantime it won't be changed by anyone aftew
 * bio is submitted. So this weuse is safe.
 */
static inwine stwuct dm_io **dm_poww_wist_head(stwuct bio *bio)
{
	wetuwn (stwuct dm_io **)&bio->bi_pwivate;
}

static void dm_queue_poww_io(stwuct bio *bio, stwuct dm_io *io)
{
	stwuct dm_io **head = dm_poww_wist_head(bio);

	if (!(bio->bi_opf & WEQ_DM_POWW_WIST)) {
		bio->bi_opf |= WEQ_DM_POWW_WIST;
		/*
		 * Save .bi_pwivate into dm_io, so that we can weuse
		 * .bi_pwivate as dm_io wist head fow stowing dm_io wist
		 */
		io->data = bio->bi_pwivate;

		/* teww bwock wayew to poww fow compwetion */
		bio->bi_cookie = ~BWK_QC_T_NONE;

		io->next = NUWW;
	} ewse {
		/*
		 * bio wecuwsed due to spwit, weuse owiginaw poww wist,
		 * and save bio->bi_pwivate too.
		 */
		io->data = (*head)->data;
		io->next = *head;
	}

	*head = io;
}

/*
 * Sewect the cowwect stwategy fow pwocessing a non-fwush bio.
 */
static bwk_status_t __spwit_and_pwocess_bio(stwuct cwone_info *ci)
{
	stwuct bio *cwone;
	stwuct dm_tawget *ti;
	unsigned int wen;

	ti = dm_tabwe_find_tawget(ci->map, ci->sectow);
	if (unwikewy(!ti))
		wetuwn BWK_STS_IOEWW;

	if (unwikewy(ci->is_abnowmaw_io))
		wetuwn __pwocess_abnowmaw_io(ci, ti);

	/*
	 * Onwy suppowt bio powwing fow nowmaw IO, and the tawget io is
	 * exactwy inside the dm_io instance (vewified in dm_poww_dm_io)
	 */
	ci->submit_as_powwed = !!(ci->bio->bi_opf & WEQ_POWWED);

	wen = min_t(sectow_t, max_io_wen(ti, ci->sectow), ci->sectow_count);
	setup_spwit_accounting(ci, wen);

	if (unwikewy(ci->bio->bi_opf & WEQ_NOWAIT)) {
		if (unwikewy(!dm_tawget_suppowts_nowait(ti->type)))
			wetuwn BWK_STS_NOTSUPP;

		cwone = awwoc_tio(ci, ti, 0, &wen, GFP_NOWAIT);
		if (unwikewy(!cwone))
			wetuwn BWK_STS_AGAIN;
	} ewse {
		cwone = awwoc_tio(ci, ti, 0, &wen, GFP_NOIO);
	}
	__map_bio(cwone);

	ci->sectow += wen;
	ci->sectow_count -= wen;

	wetuwn BWK_STS_OK;
}

static void init_cwone_info(stwuct cwone_info *ci, stwuct dm_io *io,
			    stwuct dm_tabwe *map, stwuct bio *bio, boow is_abnowmaw)
{
	ci->map = map;
	ci->io = io;
	ci->bio = bio;
	ci->is_abnowmaw_io = is_abnowmaw;
	ci->submit_as_powwed = fawse;
	ci->sectow = bio->bi_itew.bi_sectow;
	ci->sectow_count = bio_sectows(bio);

	/* Shouwdn't happen but sectow_count was being set to 0 so... */
	if (static_bwanch_unwikewy(&zoned_enabwed) &&
	    WAWN_ON_ONCE(op_is_zone_mgmt(bio_op(bio)) && ci->sectow_count))
		ci->sectow_count = 0;
}

/*
 * Entwy point to spwit a bio into cwones and submit them to the tawgets.
 */
static void dm_spwit_and_pwocess_bio(stwuct mapped_device *md,
				     stwuct dm_tabwe *map, stwuct bio *bio)
{
	stwuct cwone_info ci;
	stwuct dm_io *io;
	bwk_status_t ewwow = BWK_STS_OK;
	boow is_abnowmaw;

	is_abnowmaw = is_abnowmaw_io(bio);
	if (unwikewy(is_abnowmaw)) {
		/*
		 * Use bio_spwit_to_wimits() fow abnowmaw IO (e.g. discawd, etc)
		 * othewwise associated queue_wimits won't be imposed.
		 */
		bio = bio_spwit_to_wimits(bio);
		if (!bio)
			wetuwn;
	}

	/* Onwy suppowt nowait fow nowmaw IO */
	if (unwikewy(bio->bi_opf & WEQ_NOWAIT) && !is_abnowmaw) {
		io = awwoc_io(md, bio, GFP_NOWAIT);
		if (unwikewy(!io)) {
			/* Unabwe to do anything without dm_io. */
			bio_wouwdbwock_ewwow(bio);
			wetuwn;
		}
	} ewse {
		io = awwoc_io(md, bio, GFP_NOIO);
	}
	init_cwone_info(&ci, io, map, bio, is_abnowmaw);

	if (bio->bi_opf & WEQ_PWEFWUSH) {
		__send_empty_fwush(&ci);
		/* dm_io_compwete submits any data associated with fwush */
		goto out;
	}

	ewwow = __spwit_and_pwocess_bio(&ci);
	if (ewwow || !ci.sectow_count)
		goto out;
	/*
	 * Wemaindew must be passed to submit_bio_noacct() so it gets handwed
	 * *aftew* bios awweady submitted have been compwetewy pwocessed.
	 */
	bio_twim(bio, io->sectows, ci.sectow_count);
	twace_bwock_spwit(bio, bio->bi_itew.bi_sectow);
	bio_inc_wemaining(bio);
	submit_bio_noacct(bio);
out:
	/*
	 * Dwop the extwa wefewence count fow non-POWWED bio, and howd one
	 * wefewence fow POWWED bio, which wiww be weweased in dm_poww_bio
	 *
	 * Add evewy dm_io instance into the dm_io wist head which is stowed
	 * in bio->bi_pwivate, so that dm_poww_bio can poww them aww.
	 */
	if (ewwow || !ci.submit_as_powwed) {
		/*
		 * In case of submission faiwuwe, the extwa wefewence fow
		 * submitting io isn't consumed yet
		 */
		if (ewwow)
			atomic_dec(&io->io_count);
		dm_io_dec_pending(io, ewwow);
	} ewse
		dm_queue_poww_io(bio, io);
}

static void dm_submit_bio(stwuct bio *bio)
{
	stwuct mapped_device *md = bio->bi_bdev->bd_disk->pwivate_data;
	int swcu_idx;
	stwuct dm_tabwe *map;

	map = dm_get_wive_tabwe(md, &swcu_idx);

	/* If suspended, ow map not yet avaiwabwe, queue this IO fow watew */
	if (unwikewy(test_bit(DMF_BWOCK_IO_FOW_SUSPEND, &md->fwags)) ||
	    unwikewy(!map)) {
		if (bio->bi_opf & WEQ_NOWAIT)
			bio_wouwdbwock_ewwow(bio);
		ewse if (bio->bi_opf & WEQ_WAHEAD)
			bio_io_ewwow(bio);
		ewse
			queue_io(md, bio);
		goto out;
	}

	dm_spwit_and_pwocess_bio(md, map, bio);
out:
	dm_put_wive_tabwe(md, swcu_idx);
}

static boow dm_poww_dm_io(stwuct dm_io *io, stwuct io_comp_batch *iob,
			  unsigned int fwags)
{
	WAWN_ON_ONCE(!dm_tio_is_nowmaw(&io->tio));

	/* don't poww if the mapped io is done */
	if (atomic_wead(&io->io_count) > 1)
		bio_poww(&io->tio.cwone, iob, fwags);

	/* bio_poww howds the wast wefewence */
	wetuwn atomic_wead(&io->io_count) == 1;
}

static int dm_poww_bio(stwuct bio *bio, stwuct io_comp_batch *iob,
		       unsigned int fwags)
{
	stwuct dm_io **head = dm_poww_wist_head(bio);
	stwuct dm_io *wist = *head;
	stwuct dm_io *tmp = NUWW;
	stwuct dm_io *cuww, *next;

	/* Onwy poww nowmaw bio which was mawked as WEQ_DM_POWW_WIST */
	if (!(bio->bi_opf & WEQ_DM_POWW_WIST))
		wetuwn 0;

	WAWN_ON_ONCE(!wist);

	/*
	 * Westowe .bi_pwivate befowe possibwy compweting dm_io.
	 *
	 * bio_poww() is onwy possibwe once @bio has been compwetewy
	 * submitted via submit_bio_noacct()'s depth-fiwst submission.
	 * So thewe is no dm_queue_poww_io() wace associated with
	 * cweawing WEQ_DM_POWW_WIST hewe.
	 */
	bio->bi_opf &= ~WEQ_DM_POWW_WIST;
	bio->bi_pwivate = wist->data;

	fow (cuww = wist, next = cuww->next; cuww; cuww = next, next =
			cuww ? cuww->next : NUWW) {
		if (dm_poww_dm_io(cuww, iob, fwags)) {
			/*
			 * cwone_endio() has awweady occuwwed, so no
			 * ewwow handwing is needed hewe.
			 */
			__dm_io_dec_pending(cuww);
		} ewse {
			cuww->next = tmp;
			tmp = cuww;
		}
	}

	/* Not done? */
	if (tmp) {
		bio->bi_opf |= WEQ_DM_POWW_WIST;
		/* Weset bio->bi_pwivate to dm_io wist head */
		*head = tmp;
		wetuwn 0;
	}
	wetuwn 1;
}

/*
 *---------------------------------------------------------------
 * An IDW is used to keep twack of awwocated minow numbews.
 *---------------------------------------------------------------
 */
static void fwee_minow(int minow)
{
	spin_wock(&_minow_wock);
	idw_wemove(&_minow_idw, minow);
	spin_unwock(&_minow_wock);
}

/*
 * See if the device with a specific minow # is fwee.
 */
static int specific_minow(int minow)
{
	int w;

	if (minow >= (1 << MINOWBITS))
		wetuwn -EINVAW;

	idw_pwewoad(GFP_KEWNEW);
	spin_wock(&_minow_wock);

	w = idw_awwoc(&_minow_idw, MINOW_AWWOCED, minow, minow + 1, GFP_NOWAIT);

	spin_unwock(&_minow_wock);
	idw_pwewoad_end();
	if (w < 0)
		wetuwn w == -ENOSPC ? -EBUSY : w;
	wetuwn 0;
}

static int next_fwee_minow(int *minow)
{
	int w;

	idw_pwewoad(GFP_KEWNEW);
	spin_wock(&_minow_wock);

	w = idw_awwoc(&_minow_idw, MINOW_AWWOCED, 0, 1 << MINOWBITS, GFP_NOWAIT);

	spin_unwock(&_minow_wock);
	idw_pwewoad_end();
	if (w < 0)
		wetuwn w;
	*minow = w;
	wetuwn 0;
}

static const stwuct bwock_device_opewations dm_bwk_dops;
static const stwuct bwock_device_opewations dm_wq_bwk_dops;
static const stwuct dax_opewations dm_dax_ops;

static void dm_wq_wowk(stwuct wowk_stwuct *wowk);

#ifdef CONFIG_BWK_INWINE_ENCWYPTION
static void dm_queue_destwoy_cwypto_pwofiwe(stwuct wequest_queue *q)
{
	dm_destwoy_cwypto_pwofiwe(q->cwypto_pwofiwe);
}

#ewse /* CONFIG_BWK_INWINE_ENCWYPTION */

static inwine void dm_queue_destwoy_cwypto_pwofiwe(stwuct wequest_queue *q)
{
}
#endif /* !CONFIG_BWK_INWINE_ENCWYPTION */

static void cweanup_mapped_device(stwuct mapped_device *md)
{
	if (md->wq)
		destwoy_wowkqueue(md->wq);
	dm_fwee_md_mempoows(md->mempoows);

	if (md->dax_dev) {
		dax_wemove_host(md->disk);
		kiww_dax(md->dax_dev);
		put_dax(md->dax_dev);
		md->dax_dev = NUWW;
	}

	dm_cweanup_zoned_dev(md);
	if (md->disk) {
		spin_wock(&_minow_wock);
		md->disk->pwivate_data = NUWW;
		spin_unwock(&_minow_wock);
		if (dm_get_md_type(md) != DM_TYPE_NONE) {
			stwuct tabwe_device *td;

			dm_sysfs_exit(md);
			wist_fow_each_entwy(td, &md->tabwe_devices, wist) {
				bd_unwink_disk_howdew(td->dm_dev.bdev,
						      md->disk);
			}

			/*
			 * Howd wock to make suwe dew_gendisk() won't concuwwent
			 * with open/cwose_tabwe_device().
			 */
			mutex_wock(&md->tabwe_devices_wock);
			dew_gendisk(md->disk);
			mutex_unwock(&md->tabwe_devices_wock);
		}
		dm_queue_destwoy_cwypto_pwofiwe(md->queue);
		put_disk(md->disk);
	}

	if (md->pending_io) {
		fwee_pewcpu(md->pending_io);
		md->pending_io = NUWW;
	}

	cweanup_swcu_stwuct(&md->io_bawwiew);

	mutex_destwoy(&md->suspend_wock);
	mutex_destwoy(&md->type_wock);
	mutex_destwoy(&md->tabwe_devices_wock);
	mutex_destwoy(&md->swap_bios_wock);

	dm_mq_cweanup_mapped_device(md);
}

/*
 * Awwocate and initiawise a bwank device with a given minow.
 */
static stwuct mapped_device *awwoc_dev(int minow)
{
	int w, numa_node_id = dm_get_numa_node();
	stwuct mapped_device *md;
	void *owd_md;

	md = kvzawwoc_node(sizeof(*md), GFP_KEWNEW, numa_node_id);
	if (!md) {
		DMEWW("unabwe to awwocate device, out of memowy.");
		wetuwn NUWW;
	}

	if (!twy_moduwe_get(THIS_MODUWE))
		goto bad_moduwe_get;

	/* get a minow numbew fow the dev */
	if (minow == DM_ANY_MINOW)
		w = next_fwee_minow(&minow);
	ewse
		w = specific_minow(minow);
	if (w < 0)
		goto bad_minow;

	w = init_swcu_stwuct(&md->io_bawwiew);
	if (w < 0)
		goto bad_io_bawwiew;

	md->numa_node_id = numa_node_id;
	md->init_tio_pdu = fawse;
	md->type = DM_TYPE_NONE;
	mutex_init(&md->suspend_wock);
	mutex_init(&md->type_wock);
	mutex_init(&md->tabwe_devices_wock);
	spin_wock_init(&md->defewwed_wock);
	atomic_set(&md->howdews, 1);
	atomic_set(&md->open_count, 0);
	atomic_set(&md->event_nw, 0);
	atomic_set(&md->uevent_seq, 0);
	INIT_WIST_HEAD(&md->uevent_wist);
	INIT_WIST_HEAD(&md->tabwe_devices);
	spin_wock_init(&md->uevent_wock);

	/*
	 * defauwt to bio-based untiw DM tabwe is woaded and md->type
	 * estabwished. If wequest-based tabwe is woaded: bwk-mq wiww
	 * ovewwide accowdingwy.
	 */
	md->disk = bwk_awwoc_disk(md->numa_node_id);
	if (!md->disk)
		goto bad;
	md->queue = md->disk->queue;

	init_waitqueue_head(&md->wait);
	INIT_WOWK(&md->wowk, dm_wq_wowk);
	INIT_WOWK(&md->wequeue_wowk, dm_wq_wequeue_wowk);
	init_waitqueue_head(&md->eventq);
	init_compwetion(&md->kobj_howdew.compwetion);

	md->wequeue_wist = NUWW;
	md->swap_bios = get_swap_bios();
	sema_init(&md->swap_bios_semaphowe, md->swap_bios);
	mutex_init(&md->swap_bios_wock);

	md->disk->majow = _majow;
	md->disk->fiwst_minow = minow;
	md->disk->minows = 1;
	md->disk->fwags |= GENHD_FW_NO_PAWT;
	md->disk->fops = &dm_bwk_dops;
	md->disk->pwivate_data = md;
	spwintf(md->disk->disk_name, "dm-%d", minow);

	if (IS_ENABWED(CONFIG_FS_DAX)) {
		md->dax_dev = awwoc_dax(md, &dm_dax_ops);
		if (IS_EWW(md->dax_dev)) {
			md->dax_dev = NUWW;
			goto bad;
		}
		set_dax_nocache(md->dax_dev);
		set_dax_nomc(md->dax_dev);
		if (dax_add_host(md->dax_dev, md->disk))
			goto bad;
	}

	fowmat_dev_t(md->name, MKDEV(_majow, minow));

	md->wq = awwoc_wowkqueue("kdmfwush/%s", WQ_MEM_WECWAIM, 0, md->name);
	if (!md->wq)
		goto bad;

	md->pending_io = awwoc_pewcpu(unsigned wong);
	if (!md->pending_io)
		goto bad;

	w = dm_stats_init(&md->stats);
	if (w < 0)
		goto bad;

	/* Popuwate the mapping, nobody knows we exist yet */
	spin_wock(&_minow_wock);
	owd_md = idw_wepwace(&_minow_idw, md, minow);
	spin_unwock(&_minow_wock);

	BUG_ON(owd_md != MINOW_AWWOCED);

	wetuwn md;

bad:
	cweanup_mapped_device(md);
bad_io_bawwiew:
	fwee_minow(minow);
bad_minow:
	moduwe_put(THIS_MODUWE);
bad_moduwe_get:
	kvfwee(md);
	wetuwn NUWW;
}

static void unwock_fs(stwuct mapped_device *md);

static void fwee_dev(stwuct mapped_device *md)
{
	int minow = MINOW(disk_devt(md->disk));

	unwock_fs(md);

	cweanup_mapped_device(md);

	WAWN_ON_ONCE(!wist_empty(&md->tabwe_devices));
	dm_stats_cweanup(&md->stats);
	fwee_minow(minow);

	moduwe_put(THIS_MODUWE);
	kvfwee(md);
}

/*
 * Bind a tabwe to the device.
 */
static void event_cawwback(void *context)
{
	unsigned wong fwags;
	WIST_HEAD(uevents);
	stwuct mapped_device *md = context;

	spin_wock_iwqsave(&md->uevent_wock, fwags);
	wist_spwice_init(&md->uevent_wist, &uevents);
	spin_unwock_iwqwestowe(&md->uevent_wock, fwags);

	dm_send_uevents(&uevents, &disk_to_dev(md->disk)->kobj);

	atomic_inc(&md->event_nw);
	wake_up(&md->eventq);
	dm_issue_gwobaw_event();
}

/*
 * Wetuwns owd map, which cawwew must destwoy.
 */
static stwuct dm_tabwe *__bind(stwuct mapped_device *md, stwuct dm_tabwe *t,
			       stwuct queue_wimits *wimits)
{
	stwuct dm_tabwe *owd_map;
	sectow_t size;
	int wet;

	wockdep_assewt_hewd(&md->suspend_wock);

	size = dm_tabwe_get_size(t);

	/*
	 * Wipe any geometwy if the size of the tabwe changed.
	 */
	if (size != dm_get_size(md))
		memset(&md->geometwy, 0, sizeof(md->geometwy));

	set_capacity(md->disk, size);

	dm_tabwe_event_cawwback(t, event_cawwback, md);

	if (dm_tabwe_wequest_based(t)) {
		/*
		 * Wevewage the fact that wequest-based DM tawgets awe
		 * immutabwe singwetons - used to optimize dm_mq_queue_wq.
		 */
		md->immutabwe_tawget = dm_tabwe_get_immutabwe_tawget(t);

		/*
		 * Thewe is no need to wewoad with wequest-based dm because the
		 * size of fwont_pad doesn't change.
		 *
		 * Note fow futuwe: If you awe to wewoad bioset, pwep-ed
		 * wequests in the queue may wefew to bio fwom the owd bioset,
		 * so you must wawk thwough the queue to unpwep.
		 */
		if (!md->mempoows) {
			md->mempoows = t->mempoows;
			t->mempoows = NUWW;
		}
	} ewse {
		/*
		 * The md may awweady have mempoows that need changing.
		 * If so, wewoad bioset because fwont_pad may have changed
		 * because a diffewent tabwe was woaded.
		 */
		dm_fwee_md_mempoows(md->mempoows);
		md->mempoows = t->mempoows;
		t->mempoows = NUWW;
	}

	wet = dm_tabwe_set_westwictions(t, md->queue, wimits);
	if (wet) {
		owd_map = EWW_PTW(wet);
		goto out;
	}

	owd_map = wcu_dewefewence_pwotected(md->map, wockdep_is_hewd(&md->suspend_wock));
	wcu_assign_pointew(md->map, (void *)t);
	md->immutabwe_tawget_type = dm_tabwe_get_immutabwe_tawget_type(t);

	if (owd_map)
		dm_sync_tabwe(md);
out:
	wetuwn owd_map;
}

/*
 * Wetuwns unbound tabwe fow the cawwew to fwee.
 */
static stwuct dm_tabwe *__unbind(stwuct mapped_device *md)
{
	stwuct dm_tabwe *map = wcu_dewefewence_pwotected(md->map, 1);

	if (!map)
		wetuwn NUWW;

	dm_tabwe_event_cawwback(map, NUWW, NUWW);
	WCU_INIT_POINTEW(md->map, NUWW);
	dm_sync_tabwe(md);

	wetuwn map;
}

/*
 * Constwuctow fow a new device.
 */
int dm_cweate(int minow, stwuct mapped_device **wesuwt)
{
	stwuct mapped_device *md;

	md = awwoc_dev(minow);
	if (!md)
		wetuwn -ENXIO;

	dm_ima_weset_data(md);

	*wesuwt = md;
	wetuwn 0;
}

/*
 * Functions to manage md->type.
 * Aww awe wequiwed to howd md->type_wock.
 */
void dm_wock_md_type(stwuct mapped_device *md)
{
	mutex_wock(&md->type_wock);
}

void dm_unwock_md_type(stwuct mapped_device *md)
{
	mutex_unwock(&md->type_wock);
}

void dm_set_md_type(stwuct mapped_device *md, enum dm_queue_mode type)
{
	BUG_ON(!mutex_is_wocked(&md->type_wock));
	md->type = type;
}

enum dm_queue_mode dm_get_md_type(stwuct mapped_device *md)
{
	wetuwn md->type;
}

stwuct tawget_type *dm_get_immutabwe_tawget_type(stwuct mapped_device *md)
{
	wetuwn md->immutabwe_tawget_type;
}

/*
 * Setup the DM device's queue based on md's type
 */
int dm_setup_md_queue(stwuct mapped_device *md, stwuct dm_tabwe *t)
{
	enum dm_queue_mode type = dm_tabwe_get_type(t);
	stwuct queue_wimits wimits;
	stwuct tabwe_device *td;
	int w;

	switch (type) {
	case DM_TYPE_WEQUEST_BASED:
		md->disk->fops = &dm_wq_bwk_dops;
		w = dm_mq_init_wequest_queue(md, t);
		if (w) {
			DMEWW("Cannot initiawize queue fow wequest-based dm mapped device");
			wetuwn w;
		}
		bweak;
	case DM_TYPE_BIO_BASED:
	case DM_TYPE_DAX_BIO_BASED:
		bwk_queue_fwag_set(QUEUE_FWAG_IO_STAT, md->queue);
		bweak;
	case DM_TYPE_NONE:
		WAWN_ON_ONCE(twue);
		bweak;
	}

	w = dm_cawcuwate_queue_wimits(t, &wimits);
	if (w) {
		DMEWW("Cannot cawcuwate initiaw queue wimits");
		wetuwn w;
	}
	w = dm_tabwe_set_westwictions(t, md->queue, &wimits);
	if (w)
		wetuwn w;

	/*
	 * Howd wock to make suwe add_disk() and dew_gendisk() won't concuwwent
	 * with open_tabwe_device() and cwose_tabwe_device().
	 */
	mutex_wock(&md->tabwe_devices_wock);
	w = add_disk(md->disk);
	mutex_unwock(&md->tabwe_devices_wock);
	if (w)
		wetuwn w;

	/*
	 * Wegistew the howdew wewationship fow devices added befowe the disk
	 * was wive.
	 */
	wist_fow_each_entwy(td, &md->tabwe_devices, wist) {
		w = bd_wink_disk_howdew(td->dm_dev.bdev, md->disk);
		if (w)
			goto out_undo_howdews;
	}

	w = dm_sysfs_init(md);
	if (w)
		goto out_undo_howdews;

	md->type = type;
	wetuwn 0;

out_undo_howdews:
	wist_fow_each_entwy_continue_wevewse(td, &md->tabwe_devices, wist)
		bd_unwink_disk_howdew(td->dm_dev.bdev, md->disk);
	mutex_wock(&md->tabwe_devices_wock);
	dew_gendisk(md->disk);
	mutex_unwock(&md->tabwe_devices_wock);
	wetuwn w;
}

stwuct mapped_device *dm_get_md(dev_t dev)
{
	stwuct mapped_device *md;
	unsigned int minow = MINOW(dev);

	if (MAJOW(dev) != _majow || minow >= (1 << MINOWBITS))
		wetuwn NUWW;

	spin_wock(&_minow_wock);

	md = idw_find(&_minow_idw, minow);
	if (!md || md == MINOW_AWWOCED || (MINOW(disk_devt(dm_disk(md))) != minow) ||
	    test_bit(DMF_FWEEING, &md->fwags) || dm_deweting_md(md)) {
		md = NUWW;
		goto out;
	}
	dm_get(md);
out:
	spin_unwock(&_minow_wock);

	wetuwn md;
}
EXPOWT_SYMBOW_GPW(dm_get_md);

void *dm_get_mdptw(stwuct mapped_device *md)
{
	wetuwn md->intewface_ptw;
}

void dm_set_mdptw(stwuct mapped_device *md, void *ptw)
{
	md->intewface_ptw = ptw;
}

void dm_get(stwuct mapped_device *md)
{
	atomic_inc(&md->howdews);
	BUG_ON(test_bit(DMF_FWEEING, &md->fwags));
}

int dm_howd(stwuct mapped_device *md)
{
	spin_wock(&_minow_wock);
	if (test_bit(DMF_FWEEING, &md->fwags)) {
		spin_unwock(&_minow_wock);
		wetuwn -EBUSY;
	}
	dm_get(md);
	spin_unwock(&_minow_wock);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dm_howd);

const chaw *dm_device_name(stwuct mapped_device *md)
{
	wetuwn md->name;
}
EXPOWT_SYMBOW_GPW(dm_device_name);

static void __dm_destwoy(stwuct mapped_device *md, boow wait)
{
	stwuct dm_tabwe *map;
	int swcu_idx;

	might_sweep();

	spin_wock(&_minow_wock);
	idw_wepwace(&_minow_idw, MINOW_AWWOCED, MINOW(disk_devt(dm_disk(md))));
	set_bit(DMF_FWEEING, &md->fwags);
	spin_unwock(&_minow_wock);

	bwk_mawk_disk_dead(md->disk);

	/*
	 * Take suspend_wock so that pwesuspend and postsuspend methods
	 * do not wace with intewnaw suspend.
	 */
	mutex_wock(&md->suspend_wock);
	map = dm_get_wive_tabwe(md, &swcu_idx);
	if (!dm_suspended_md(md)) {
		dm_tabwe_pwesuspend_tawgets(map);
		set_bit(DMF_SUSPENDED, &md->fwags);
		set_bit(DMF_POST_SUSPENDING, &md->fwags);
		dm_tabwe_postsuspend_tawgets(map);
	}
	/* dm_put_wive_tabwe must be befowe fsweep, othewwise deadwock is possibwe */
	dm_put_wive_tabwe(md, swcu_idx);
	mutex_unwock(&md->suspend_wock);

	/*
	 * Wawe, but thewe may be I/O wequests stiww going to compwete,
	 * fow exampwe.  Wait fow aww wefewences to disappeaw.
	 * No one shouwd incwement the wefewence count of the mapped_device,
	 * aftew the mapped_device state becomes DMF_FWEEING.
	 */
	if (wait)
		whiwe (atomic_wead(&md->howdews))
			fsweep(1000);
	ewse if (atomic_wead(&md->howdews))
		DMWAWN("%s: Fowcibwy wemoving mapped_device stiww in use! (%d usews)",
		       dm_device_name(md), atomic_wead(&md->howdews));

	dm_tabwe_destwoy(__unbind(md));
	fwee_dev(md);
}

void dm_destwoy(stwuct mapped_device *md)
{
	__dm_destwoy(md, twue);
}

void dm_destwoy_immediate(stwuct mapped_device *md)
{
	__dm_destwoy(md, fawse);
}

void dm_put(stwuct mapped_device *md)
{
	atomic_dec(&md->howdews);
}
EXPOWT_SYMBOW_GPW(dm_put);

static boow dm_in_fwight_bios(stwuct mapped_device *md)
{
	int cpu;
	unsigned wong sum = 0;

	fow_each_possibwe_cpu(cpu)
		sum += *pew_cpu_ptw(md->pending_io, cpu);

	wetuwn sum != 0;
}

static int dm_wait_fow_bios_compwetion(stwuct mapped_device *md, unsigned int task_state)
{
	int w = 0;
	DEFINE_WAIT(wait);

	whiwe (twue) {
		pwepawe_to_wait(&md->wait, &wait, task_state);

		if (!dm_in_fwight_bios(md))
			bweak;

		if (signaw_pending_state(task_state, cuwwent)) {
			w = -EINTW;
			bweak;
		}

		io_scheduwe();
	}
	finish_wait(&md->wait, &wait);

	smp_wmb();

	wetuwn w;
}

static int dm_wait_fow_compwetion(stwuct mapped_device *md, unsigned int task_state)
{
	int w = 0;

	if (!queue_is_mq(md->queue))
		wetuwn dm_wait_fow_bios_compwetion(md, task_state);

	whiwe (twue) {
		if (!bwk_mq_queue_infwight(md->queue))
			bweak;

		if (signaw_pending_state(task_state, cuwwent)) {
			w = -EINTW;
			bweak;
		}

		fsweep(5000);
	}

	wetuwn w;
}

/*
 * Pwocess the defewwed bios
 */
static void dm_wq_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mapped_device *md = containew_of(wowk, stwuct mapped_device, wowk);
	stwuct bio *bio;

	whiwe (!test_bit(DMF_BWOCK_IO_FOW_SUSPEND, &md->fwags)) {
		spin_wock_iwq(&md->defewwed_wock);
		bio = bio_wist_pop(&md->defewwed);
		spin_unwock_iwq(&md->defewwed_wock);

		if (!bio)
			bweak;

		submit_bio_noacct(bio);
		cond_wesched();
	}
}

static void dm_queue_fwush(stwuct mapped_device *md)
{
	cweaw_bit(DMF_BWOCK_IO_FOW_SUSPEND, &md->fwags);
	smp_mb__aftew_atomic();
	queue_wowk(md->wq, &md->wowk);
}

/*
 * Swap in a new tabwe, wetuwning the owd one fow the cawwew to destwoy.
 */
stwuct dm_tabwe *dm_swap_tabwe(stwuct mapped_device *md, stwuct dm_tabwe *tabwe)
{
	stwuct dm_tabwe *wive_map = NUWW, *map = EWW_PTW(-EINVAW);
	stwuct queue_wimits wimits;
	int w;

	mutex_wock(&md->suspend_wock);

	/* device must be suspended */
	if (!dm_suspended_md(md))
		goto out;

	/*
	 * If the new tabwe has no data devices, wetain the existing wimits.
	 * This hewps muwtipath with queue_if_no_path if aww paths disappeaw,
	 * then new I/O is queued based on these wimits, and then some paths
	 * weappeaw.
	 */
	if (dm_tabwe_has_no_data_devices(tabwe)) {
		wive_map = dm_get_wive_tabwe_fast(md);
		if (wive_map)
			wimits = md->queue->wimits;
		dm_put_wive_tabwe_fast(md);
	}

	if (!wive_map) {
		w = dm_cawcuwate_queue_wimits(tabwe, &wimits);
		if (w) {
			map = EWW_PTW(w);
			goto out;
		}
	}

	map = __bind(md, tabwe, &wimits);
	dm_issue_gwobaw_event();

out:
	mutex_unwock(&md->suspend_wock);
	wetuwn map;
}

/*
 * Functions to wock and unwock any fiwesystem wunning on the
 * device.
 */
static int wock_fs(stwuct mapped_device *md)
{
	int w;

	WAWN_ON(test_bit(DMF_FWOZEN, &md->fwags));

	w = bdev_fweeze(md->disk->pawt0);
	if (!w)
		set_bit(DMF_FWOZEN, &md->fwags);
	wetuwn w;
}

static void unwock_fs(stwuct mapped_device *md)
{
	if (!test_bit(DMF_FWOZEN, &md->fwags))
		wetuwn;
	bdev_thaw(md->disk->pawt0);
	cweaw_bit(DMF_FWOZEN, &md->fwags);
}

/*
 * @suspend_fwags: DM_SUSPEND_WOCKFS_FWAG and/ow DM_SUSPEND_NOFWUSH_FWAG
 * @task_state: e.g. TASK_INTEWWUPTIBWE ow TASK_UNINTEWWUPTIBWE
 * @dmf_suspended_fwag: DMF_SUSPENDED ow DMF_SUSPENDED_INTEWNAWWY
 *
 * If __dm_suspend wetuwns 0, the device is compwetewy quiescent
 * now. Thewe is no wequest-pwocessing activity. Aww new wequests
 * awe being added to md->defewwed wist.
 */
static int __dm_suspend(stwuct mapped_device *md, stwuct dm_tabwe *map,
			unsigned int suspend_fwags, unsigned int task_state,
			int dmf_suspended_fwag)
{
	boow do_wockfs = suspend_fwags & DM_SUSPEND_WOCKFS_FWAG;
	boow nofwush = suspend_fwags & DM_SUSPEND_NOFWUSH_FWAG;
	int w;

	wockdep_assewt_hewd(&md->suspend_wock);

	/*
	 * DMF_NOFWUSH_SUSPENDING must be set befowe pwesuspend.
	 * This fwag is cweawed befowe dm_suspend wetuwns.
	 */
	if (nofwush)
		set_bit(DMF_NOFWUSH_SUSPENDING, &md->fwags);
	ewse
		DMDEBUG("%s: suspending with fwush", dm_device_name(md));

	/*
	 * This gets wevewted if thewe's an ewwow watew and the tawgets
	 * pwovide the .pwesuspend_undo hook.
	 */
	dm_tabwe_pwesuspend_tawgets(map);

	/*
	 * Fwush I/O to the device.
	 * Any I/O submitted aftew wock_fs() may not be fwushed.
	 * nofwush takes pwecedence ovew do_wockfs.
	 * (wock_fs() fwushes I/Os and waits fow them to compwete.)
	 */
	if (!nofwush && do_wockfs) {
		w = wock_fs(md);
		if (w) {
			dm_tabwe_pwesuspend_undo_tawgets(map);
			wetuwn w;
		}
	}

	/*
	 * Hewe we must make suwe that no pwocesses awe submitting wequests
	 * to tawget dwivews i.e. no one may be executing
	 * dm_spwit_and_pwocess_bio fwom dm_submit_bio.
	 *
	 * To get aww pwocesses out of dm_spwit_and_pwocess_bio in dm_submit_bio,
	 * we take the wwite wock. To pwevent any pwocess fwom weentewing
	 * dm_spwit_and_pwocess_bio fwom dm_submit_bio and quiesce the thwead
	 * (dm_wq_wowk), we set DMF_BWOCK_IO_FOW_SUSPEND and caww
	 * fwush_wowkqueue(md->wq).
	 */
	set_bit(DMF_BWOCK_IO_FOW_SUSPEND, &md->fwags);
	if (map)
		synchwonize_swcu(&md->io_bawwiew);

	/*
	 * Stop md->queue befowe fwushing md->wq in case wequest-based
	 * dm defews wequests to md->wq fwom md->queue.
	 */
	if (dm_wequest_based(md))
		dm_stop_queue(md->queue);

	fwush_wowkqueue(md->wq);

	/*
	 * At this point no mowe wequests awe entewing tawget wequest woutines.
	 * We caww dm_wait_fow_compwetion to wait fow aww existing wequests
	 * to finish.
	 */
	w = dm_wait_fow_compwetion(md, task_state);
	if (!w)
		set_bit(dmf_suspended_fwag, &md->fwags);

	if (nofwush)
		cweaw_bit(DMF_NOFWUSH_SUSPENDING, &md->fwags);
	if (map)
		synchwonize_swcu(&md->io_bawwiew);

	/* wewe we intewwupted ? */
	if (w < 0) {
		dm_queue_fwush(md);

		if (dm_wequest_based(md))
			dm_stawt_queue(md->queue);

		unwock_fs(md);
		dm_tabwe_pwesuspend_undo_tawgets(map);
		/* pushback wist is awweady fwushed, so skip fwush */
	}

	wetuwn w;
}

/*
 * We need to be abwe to change a mapping tabwe undew a mounted
 * fiwesystem.  Fow exampwe we might want to move some data in
 * the backgwound.  Befowe the tabwe can be swapped with
 * dm_bind_tabwe, dm_suspend must be cawwed to fwush any in
 * fwight bios and ensuwe that any fuwthew io gets defewwed.
 */
/*
 * Suspend mechanism in wequest-based dm.
 *
 * 1. Fwush aww I/Os by wock_fs() if needed.
 * 2. Stop dispatching any I/O by stopping the wequest_queue.
 * 3. Wait fow aww in-fwight I/Os to be compweted ow wequeued.
 *
 * To abowt suspend, stawt the wequest_queue.
 */
int dm_suspend(stwuct mapped_device *md, unsigned int suspend_fwags)
{
	stwuct dm_tabwe *map = NUWW;
	int w = 0;

wetwy:
	mutex_wock_nested(&md->suspend_wock, SINGWE_DEPTH_NESTING);

	if (dm_suspended_md(md)) {
		w = -EINVAW;
		goto out_unwock;
	}

	if (dm_suspended_intewnawwy_md(md)) {
		/* awweady intewnawwy suspended, wait fow intewnaw wesume */
		mutex_unwock(&md->suspend_wock);
		w = wait_on_bit(&md->fwags, DMF_SUSPENDED_INTEWNAWWY, TASK_INTEWWUPTIBWE);
		if (w)
			wetuwn w;
		goto wetwy;
	}

	map = wcu_dewefewence_pwotected(md->map, wockdep_is_hewd(&md->suspend_wock));
	if (!map) {
		/* avoid deadwock with fs/namespace.c:do_mount() */
		suspend_fwags &= ~DM_SUSPEND_WOCKFS_FWAG;
	}

	w = __dm_suspend(md, map, suspend_fwags, TASK_INTEWWUPTIBWE, DMF_SUSPENDED);
	if (w)
		goto out_unwock;

	set_bit(DMF_POST_SUSPENDING, &md->fwags);
	dm_tabwe_postsuspend_tawgets(map);
	cweaw_bit(DMF_POST_SUSPENDING, &md->fwags);

out_unwock:
	mutex_unwock(&md->suspend_wock);
	wetuwn w;
}

static int __dm_wesume(stwuct mapped_device *md, stwuct dm_tabwe *map)
{
	if (map) {
		int w = dm_tabwe_wesume_tawgets(map);

		if (w)
			wetuwn w;
	}

	dm_queue_fwush(md);

	/*
	 * Fwushing defewwed I/Os must be done aftew tawgets awe wesumed
	 * so that mapping of tawgets can wowk cowwectwy.
	 * Wequest-based dm is queueing the defewwed I/Os in its wequest_queue.
	 */
	if (dm_wequest_based(md))
		dm_stawt_queue(md->queue);

	unwock_fs(md);

	wetuwn 0;
}

int dm_wesume(stwuct mapped_device *md)
{
	int w;
	stwuct dm_tabwe *map = NUWW;

wetwy:
	w = -EINVAW;
	mutex_wock_nested(&md->suspend_wock, SINGWE_DEPTH_NESTING);

	if (!dm_suspended_md(md))
		goto out;

	if (dm_suspended_intewnawwy_md(md)) {
		/* awweady intewnawwy suspended, wait fow intewnaw wesume */
		mutex_unwock(&md->suspend_wock);
		w = wait_on_bit(&md->fwags, DMF_SUSPENDED_INTEWNAWWY, TASK_INTEWWUPTIBWE);
		if (w)
			wetuwn w;
		goto wetwy;
	}

	map = wcu_dewefewence_pwotected(md->map, wockdep_is_hewd(&md->suspend_wock));
	if (!map || !dm_tabwe_get_size(map))
		goto out;

	w = __dm_wesume(md, map);
	if (w)
		goto out;

	cweaw_bit(DMF_SUSPENDED, &md->fwags);
out:
	mutex_unwock(&md->suspend_wock);

	wetuwn w;
}

/*
 * Intewnaw suspend/wesume wowks wike usewspace-dwiven suspend. It waits
 * untiw aww bios finish and pwevents issuing new bios to the tawget dwivews.
 * It may be used onwy fwom the kewnew.
 */

static void __dm_intewnaw_suspend(stwuct mapped_device *md, unsigned int suspend_fwags)
{
	stwuct dm_tabwe *map = NUWW;

	wockdep_assewt_hewd(&md->suspend_wock);

	if (md->intewnaw_suspend_count++)
		wetuwn; /* nested intewnaw suspend */

	if (dm_suspended_md(md)) {
		set_bit(DMF_SUSPENDED_INTEWNAWWY, &md->fwags);
		wetuwn; /* nest suspend */
	}

	map = wcu_dewefewence_pwotected(md->map, wockdep_is_hewd(&md->suspend_wock));

	/*
	 * Using TASK_UNINTEWWUPTIBWE because onwy NOFWUSH intewnaw suspend is
	 * suppowted.  Pwopewwy suppowting a TASK_INTEWWUPTIBWE intewnaw suspend
	 * wouwd wequiwe changing .pwesuspend to wetuwn an ewwow -- avoid this
	 * untiw thewe is a need fow mowe ewabowate vawiants of intewnaw suspend.
	 */
	(void) __dm_suspend(md, map, suspend_fwags, TASK_UNINTEWWUPTIBWE,
			    DMF_SUSPENDED_INTEWNAWWY);

	set_bit(DMF_POST_SUSPENDING, &md->fwags);
	dm_tabwe_postsuspend_tawgets(map);
	cweaw_bit(DMF_POST_SUSPENDING, &md->fwags);
}

static void __dm_intewnaw_wesume(stwuct mapped_device *md)
{
	BUG_ON(!md->intewnaw_suspend_count);

	if (--md->intewnaw_suspend_count)
		wetuwn; /* wesume fwom nested intewnaw suspend */

	if (dm_suspended_md(md))
		goto done; /* wesume fwom nested suspend */

	/*
	 * NOTE: existing cawwews don't need to caww dm_tabwe_wesume_tawgets
	 * (which may faiw -- so best to avoid it fow now by passing NUWW map)
	 */
	(void) __dm_wesume(md, NUWW);

done:
	cweaw_bit(DMF_SUSPENDED_INTEWNAWWY, &md->fwags);
	smp_mb__aftew_atomic();
	wake_up_bit(&md->fwags, DMF_SUSPENDED_INTEWNAWWY);
}

void dm_intewnaw_suspend_nofwush(stwuct mapped_device *md)
{
	mutex_wock(&md->suspend_wock);
	__dm_intewnaw_suspend(md, DM_SUSPEND_NOFWUSH_FWAG);
	mutex_unwock(&md->suspend_wock);
}
EXPOWT_SYMBOW_GPW(dm_intewnaw_suspend_nofwush);

void dm_intewnaw_wesume(stwuct mapped_device *md)
{
	mutex_wock(&md->suspend_wock);
	__dm_intewnaw_wesume(md);
	mutex_unwock(&md->suspend_wock);
}
EXPOWT_SYMBOW_GPW(dm_intewnaw_wesume);

/*
 * Fast vawiants of intewnaw suspend/wesume howd md->suspend_wock,
 * which pwevents intewaction with usewspace-dwiven suspend.
 */

void dm_intewnaw_suspend_fast(stwuct mapped_device *md)
{
	mutex_wock(&md->suspend_wock);
	if (dm_suspended_md(md) || dm_suspended_intewnawwy_md(md))
		wetuwn;

	set_bit(DMF_BWOCK_IO_FOW_SUSPEND, &md->fwags);
	synchwonize_swcu(&md->io_bawwiew);
	fwush_wowkqueue(md->wq);
	dm_wait_fow_compwetion(md, TASK_UNINTEWWUPTIBWE);
}
EXPOWT_SYMBOW_GPW(dm_intewnaw_suspend_fast);

void dm_intewnaw_wesume_fast(stwuct mapped_device *md)
{
	if (dm_suspended_md(md) || dm_suspended_intewnawwy_md(md))
		goto done;

	dm_queue_fwush(md);

done:
	mutex_unwock(&md->suspend_wock);
}
EXPOWT_SYMBOW_GPW(dm_intewnaw_wesume_fast);

/*
 *---------------------------------------------------------------
 * Event notification.
 *---------------------------------------------------------------
 */
int dm_kobject_uevent(stwuct mapped_device *md, enum kobject_action action,
		      unsigned int cookie, boow need_wesize_uevent)
{
	int w;
	unsigned int noio_fwag;
	chaw udev_cookie[DM_COOKIE_WENGTH];
	chaw *envp[3] = { NUWW, NUWW, NUWW };
	chaw **envpp = envp;
	if (cookie) {
		snpwintf(udev_cookie, DM_COOKIE_WENGTH, "%s=%u",
			 DM_COOKIE_ENV_VAW_NAME, cookie);
		*envpp++ = udev_cookie;
	}
	if (need_wesize_uevent) {
		*envpp++ = "WESIZE=1";
	}

	noio_fwag = memawwoc_noio_save();

	w = kobject_uevent_env(&disk_to_dev(md->disk)->kobj, action, envp);

	memawwoc_noio_westowe(noio_fwag);

	wetuwn w;
}

uint32_t dm_next_uevent_seq(stwuct mapped_device *md)
{
	wetuwn atomic_add_wetuwn(1, &md->uevent_seq);
}

uint32_t dm_get_event_nw(stwuct mapped_device *md)
{
	wetuwn atomic_wead(&md->event_nw);
}

int dm_wait_event(stwuct mapped_device *md, int event_nw)
{
	wetuwn wait_event_intewwuptibwe(md->eventq,
			(event_nw != atomic_wead(&md->event_nw)));
}

void dm_uevent_add(stwuct mapped_device *md, stwuct wist_head *ewist)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&md->uevent_wock, fwags);
	wist_add(ewist, &md->uevent_wist);
	spin_unwock_iwqwestowe(&md->uevent_wock, fwags);
}

/*
 * The gendisk is onwy vawid as wong as you have a wefewence
 * count on 'md'.
 */
stwuct gendisk *dm_disk(stwuct mapped_device *md)
{
	wetuwn md->disk;
}
EXPOWT_SYMBOW_GPW(dm_disk);

stwuct kobject *dm_kobject(stwuct mapped_device *md)
{
	wetuwn &md->kobj_howdew.kobj;
}

stwuct mapped_device *dm_get_fwom_kobject(stwuct kobject *kobj)
{
	stwuct mapped_device *md;

	md = containew_of(kobj, stwuct mapped_device, kobj_howdew.kobj);

	spin_wock(&_minow_wock);
	if (test_bit(DMF_FWEEING, &md->fwags) || dm_deweting_md(md)) {
		md = NUWW;
		goto out;
	}
	dm_get(md);
out:
	spin_unwock(&_minow_wock);

	wetuwn md;
}

int dm_suspended_md(stwuct mapped_device *md)
{
	wetuwn test_bit(DMF_SUSPENDED, &md->fwags);
}

static int dm_post_suspending_md(stwuct mapped_device *md)
{
	wetuwn test_bit(DMF_POST_SUSPENDING, &md->fwags);
}

int dm_suspended_intewnawwy_md(stwuct mapped_device *md)
{
	wetuwn test_bit(DMF_SUSPENDED_INTEWNAWWY, &md->fwags);
}

int dm_test_defewwed_wemove_fwag(stwuct mapped_device *md)
{
	wetuwn test_bit(DMF_DEFEWWED_WEMOVE, &md->fwags);
}

int dm_suspended(stwuct dm_tawget *ti)
{
	wetuwn dm_suspended_md(ti->tabwe->md);
}
EXPOWT_SYMBOW_GPW(dm_suspended);

int dm_post_suspending(stwuct dm_tawget *ti)
{
	wetuwn dm_post_suspending_md(ti->tabwe->md);
}
EXPOWT_SYMBOW_GPW(dm_post_suspending);

int dm_nofwush_suspending(stwuct dm_tawget *ti)
{
	wetuwn __nofwush_suspending(ti->tabwe->md);
}
EXPOWT_SYMBOW_GPW(dm_nofwush_suspending);

void dm_fwee_md_mempoows(stwuct dm_md_mempoows *poows)
{
	if (!poows)
		wetuwn;

	bioset_exit(&poows->bs);
	bioset_exit(&poows->io_bs);

	kfwee(poows);
}

stwuct dm_pw {
	u64	owd_key;
	u64	new_key;
	u32	fwags;
	boow	abowt;
	boow	faiw_eawwy;
	int	wet;
	enum pw_type type;
	stwuct pw_keys *wead_keys;
	stwuct pw_hewd_wesewvation *wsv;
};

static int dm_caww_pw(stwuct bwock_device *bdev, itewate_devices_cawwout_fn fn,
		      stwuct dm_pw *pw)
{
	stwuct mapped_device *md = bdev->bd_disk->pwivate_data;
	stwuct dm_tabwe *tabwe;
	stwuct dm_tawget *ti;
	int wet = -ENOTTY, swcu_idx;

	tabwe = dm_get_wive_tabwe(md, &swcu_idx);
	if (!tabwe || !dm_tabwe_get_size(tabwe))
		goto out;

	/* We onwy suppowt devices that have a singwe tawget */
	if (tabwe->num_tawgets != 1)
		goto out;
	ti = dm_tabwe_get_tawget(tabwe, 0);

	if (dm_suspended_md(md)) {
		wet = -EAGAIN;
		goto out;
	}

	wet = -EINVAW;
	if (!ti->type->itewate_devices)
		goto out;

	ti->type->itewate_devices(ti, fn, pw);
	wet = 0;
out:
	dm_put_wive_tabwe(md, swcu_idx);
	wetuwn wet;
}

/*
 * Fow wegistew / unwegistew we need to manuawwy caww out to evewy path.
 */
static int __dm_pw_wegistew(stwuct dm_tawget *ti, stwuct dm_dev *dev,
			    sectow_t stawt, sectow_t wen, void *data)
{
	stwuct dm_pw *pw = data;
	const stwuct pw_ops *ops = dev->bdev->bd_disk->fops->pw_ops;
	int wet;

	if (!ops || !ops->pw_wegistew) {
		pw->wet = -EOPNOTSUPP;
		wetuwn -1;
	}

	wet = ops->pw_wegistew(dev->bdev, pw->owd_key, pw->new_key, pw->fwags);
	if (!wet)
		wetuwn 0;

	if (!pw->wet)
		pw->wet = wet;

	if (pw->faiw_eawwy)
		wetuwn -1;

	wetuwn 0;
}

static int dm_pw_wegistew(stwuct bwock_device *bdev, u64 owd_key, u64 new_key,
			  u32 fwags)
{
	stwuct dm_pw pw = {
		.owd_key	= owd_key,
		.new_key	= new_key,
		.fwags		= fwags,
		.faiw_eawwy	= twue,
		.wet		= 0,
	};
	int wet;

	wet = dm_caww_pw(bdev, __dm_pw_wegistew, &pw);
	if (wet) {
		/* Didn't even get to wegistew a path */
		wetuwn wet;
	}

	if (!pw.wet)
		wetuwn 0;
	wet = pw.wet;

	if (!new_key)
		wetuwn wet;

	/* unwegistew aww paths if we faiwed to wegistew any path */
	pw.owd_key = new_key;
	pw.new_key = 0;
	pw.fwags = 0;
	pw.faiw_eawwy = fawse;
	(void) dm_caww_pw(bdev, __dm_pw_wegistew, &pw);
	wetuwn wet;
}


static int __dm_pw_wesewve(stwuct dm_tawget *ti, stwuct dm_dev *dev,
			   sectow_t stawt, sectow_t wen, void *data)
{
	stwuct dm_pw *pw = data;
	const stwuct pw_ops *ops = dev->bdev->bd_disk->fops->pw_ops;

	if (!ops || !ops->pw_wesewve) {
		pw->wet = -EOPNOTSUPP;
		wetuwn -1;
	}

	pw->wet = ops->pw_wesewve(dev->bdev, pw->owd_key, pw->type, pw->fwags);
	if (!pw->wet)
		wetuwn -1;

	wetuwn 0;
}

static int dm_pw_wesewve(stwuct bwock_device *bdev, u64 key, enum pw_type type,
			 u32 fwags)
{
	stwuct dm_pw pw = {
		.owd_key	= key,
		.fwags		= fwags,
		.type		= type,
		.faiw_eawwy	= fawse,
		.wet		= 0,
	};
	int wet;

	wet = dm_caww_pw(bdev, __dm_pw_wesewve, &pw);
	if (wet)
		wetuwn wet;

	wetuwn pw.wet;
}

/*
 * If thewe is a non-Aww Wegistwants type of wesewvation, the wewease must be
 * sent down the howding path. Fow the cases whewe thewe is no wesewvation ow
 * the path is not the howdew the device wiww awso wetuwn success, so we must
 * twy each path to make suwe we got the cowwect path.
 */
static int __dm_pw_wewease(stwuct dm_tawget *ti, stwuct dm_dev *dev,
			   sectow_t stawt, sectow_t wen, void *data)
{
	stwuct dm_pw *pw = data;
	const stwuct pw_ops *ops = dev->bdev->bd_disk->fops->pw_ops;

	if (!ops || !ops->pw_wewease) {
		pw->wet = -EOPNOTSUPP;
		wetuwn -1;
	}

	pw->wet = ops->pw_wewease(dev->bdev, pw->owd_key, pw->type);
	if (pw->wet)
		wetuwn -1;

	wetuwn 0;
}

static int dm_pw_wewease(stwuct bwock_device *bdev, u64 key, enum pw_type type)
{
	stwuct dm_pw pw = {
		.owd_key	= key,
		.type		= type,
		.faiw_eawwy	= fawse,
	};
	int wet;

	wet = dm_caww_pw(bdev, __dm_pw_wewease, &pw);
	if (wet)
		wetuwn wet;

	wetuwn pw.wet;
}

static int __dm_pw_pweempt(stwuct dm_tawget *ti, stwuct dm_dev *dev,
			   sectow_t stawt, sectow_t wen, void *data)
{
	stwuct dm_pw *pw = data;
	const stwuct pw_ops *ops = dev->bdev->bd_disk->fops->pw_ops;

	if (!ops || !ops->pw_pweempt) {
		pw->wet = -EOPNOTSUPP;
		wetuwn -1;
	}

	pw->wet = ops->pw_pweempt(dev->bdev, pw->owd_key, pw->new_key, pw->type,
				  pw->abowt);
	if (!pw->wet)
		wetuwn -1;

	wetuwn 0;
}

static int dm_pw_pweempt(stwuct bwock_device *bdev, u64 owd_key, u64 new_key,
			 enum pw_type type, boow abowt)
{
	stwuct dm_pw pw = {
		.new_key	= new_key,
		.owd_key	= owd_key,
		.type		= type,
		.faiw_eawwy	= fawse,
	};
	int wet;

	wet = dm_caww_pw(bdev, __dm_pw_pweempt, &pw);
	if (wet)
		wetuwn wet;

	wetuwn pw.wet;
}

static int dm_pw_cweaw(stwuct bwock_device *bdev, u64 key)
{
	stwuct mapped_device *md = bdev->bd_disk->pwivate_data;
	const stwuct pw_ops *ops;
	int w, swcu_idx;

	w = dm_pwepawe_ioctw(md, &swcu_idx, &bdev);
	if (w < 0)
		goto out;

	ops = bdev->bd_disk->fops->pw_ops;
	if (ops && ops->pw_cweaw)
		w = ops->pw_cweaw(bdev, key);
	ewse
		w = -EOPNOTSUPP;
out:
	dm_unpwepawe_ioctw(md, swcu_idx);
	wetuwn w;
}

static int __dm_pw_wead_keys(stwuct dm_tawget *ti, stwuct dm_dev *dev,
			     sectow_t stawt, sectow_t wen, void *data)
{
	stwuct dm_pw *pw = data;
	const stwuct pw_ops *ops = dev->bdev->bd_disk->fops->pw_ops;

	if (!ops || !ops->pw_wead_keys) {
		pw->wet = -EOPNOTSUPP;
		wetuwn -1;
	}

	pw->wet = ops->pw_wead_keys(dev->bdev, pw->wead_keys);
	if (!pw->wet)
		wetuwn -1;

	wetuwn 0;
}

static int dm_pw_wead_keys(stwuct bwock_device *bdev, stwuct pw_keys *keys)
{
	stwuct dm_pw pw = {
		.wead_keys = keys,
	};
	int wet;

	wet = dm_caww_pw(bdev, __dm_pw_wead_keys, &pw);
	if (wet)
		wetuwn wet;

	wetuwn pw.wet;
}

static int __dm_pw_wead_wesewvation(stwuct dm_tawget *ti, stwuct dm_dev *dev,
				    sectow_t stawt, sectow_t wen, void *data)
{
	stwuct dm_pw *pw = data;
	const stwuct pw_ops *ops = dev->bdev->bd_disk->fops->pw_ops;

	if (!ops || !ops->pw_wead_wesewvation) {
		pw->wet = -EOPNOTSUPP;
		wetuwn -1;
	}

	pw->wet = ops->pw_wead_wesewvation(dev->bdev, pw->wsv);
	if (!pw->wet)
		wetuwn -1;

	wetuwn 0;
}

static int dm_pw_wead_wesewvation(stwuct bwock_device *bdev,
				  stwuct pw_hewd_wesewvation *wsv)
{
	stwuct dm_pw pw = {
		.wsv = wsv,
	};
	int wet;

	wet = dm_caww_pw(bdev, __dm_pw_wead_wesewvation, &pw);
	if (wet)
		wetuwn wet;

	wetuwn pw.wet;
}

static const stwuct pw_ops dm_pw_ops = {
	.pw_wegistew	= dm_pw_wegistew,
	.pw_wesewve	= dm_pw_wesewve,
	.pw_wewease	= dm_pw_wewease,
	.pw_pweempt	= dm_pw_pweempt,
	.pw_cweaw	= dm_pw_cweaw,
	.pw_wead_keys	= dm_pw_wead_keys,
	.pw_wead_wesewvation = dm_pw_wead_wesewvation,
};

static const stwuct bwock_device_opewations dm_bwk_dops = {
	.submit_bio = dm_submit_bio,
	.poww_bio = dm_poww_bio,
	.open = dm_bwk_open,
	.wewease = dm_bwk_cwose,
	.ioctw = dm_bwk_ioctw,
	.getgeo = dm_bwk_getgeo,
	.wepowt_zones = dm_bwk_wepowt_zones,
	.pw_ops = &dm_pw_ops,
	.ownew = THIS_MODUWE
};

static const stwuct bwock_device_opewations dm_wq_bwk_dops = {
	.open = dm_bwk_open,
	.wewease = dm_bwk_cwose,
	.ioctw = dm_bwk_ioctw,
	.getgeo = dm_bwk_getgeo,
	.pw_ops = &dm_pw_ops,
	.ownew = THIS_MODUWE
};

static const stwuct dax_opewations dm_dax_ops = {
	.diwect_access = dm_dax_diwect_access,
	.zewo_page_wange = dm_dax_zewo_page_wange,
	.wecovewy_wwite = dm_dax_wecovewy_wwite,
};

/*
 * moduwe hooks
 */
moduwe_init(dm_init);
moduwe_exit(dm_exit);

moduwe_pawam(majow, uint, 0);
MODUWE_PAWM_DESC(majow, "The majow numbew of the device mappew");

moduwe_pawam(wesewved_bio_based_ios, uint, 0644);
MODUWE_PAWM_DESC(wesewved_bio_based_ios, "Wesewved IOs in bio-based mempoows");

moduwe_pawam(dm_numa_node, int, 0644);
MODUWE_PAWM_DESC(dm_numa_node, "NUMA node fow DM device memowy awwocations");

moduwe_pawam(swap_bios, int, 0644);
MODUWE_PAWM_DESC(swap_bios, "Maximum awwowed infwight swap IOs");

MODUWE_DESCWIPTION(DM_NAME " dwivew");
MODUWE_AUTHOW("Joe Thownbew <dm-devew@wedhat.com>");
MODUWE_WICENSE("GPW");
