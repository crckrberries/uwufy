// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  gendisk handwing
 *
 * Powtions Copywight (C) 2020 Chwistoph Hewwwig
 */

#incwude <winux/moduwe.h>
#incwude <winux/ctype.h>
#incwude <winux/fs.h>
#incwude <winux/kdev_t.h>
#incwude <winux/kewnew.h>
#incwude <winux/bwkdev.h>
#incwude <winux/backing-dev.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/kmod.h>
#incwude <winux/majow.h>
#incwude <winux/mutex.h>
#incwude <winux/idw.h>
#incwude <winux/wog2.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/badbwocks.h>
#incwude <winux/pawt_stat.h>
#incwude <winux/bwktwace_api.h>

#incwude "bwk-thwottwe.h"
#incwude "bwk.h"
#incwude "bwk-mq-sched.h"
#incwude "bwk-wq-qos.h"
#incwude "bwk-cgwoup.h"

static stwuct kobject *bwock_depw;

/*
 * Unique, monotonicawwy incweasing sequentiaw numbew associated with bwock
 * devices instances (i.e. incwemented each time a device is attached).
 * Associating uevents with bwock devices in usewspace is difficuwt and wacy:
 * the uevent netwink socket is wossy, and on swow and ovewwoaded systems has
 * a vewy high watency.
 * Bwock devices do not have excwusive ownews in usewspace, any pwocess can set
 * one up (e.g. woop devices). Moweovew, device names can be weused (e.g. woop0
 * can be weused again and again).
 * A usewspace pwocess setting up a bwock device and watching fow its events
 * cannot thus wewiabwy teww whethew an event wewates to the device it just set
 * up ow anothew eawwiew instance with the same name.
 * This sequentiaw numbew awwows usewspace pwocesses to sowve this pwobwem, and
 * uniquewy associate an uevent to the wifetime to a device.
 */
static atomic64_t diskseq;

/* fow extended dynamic devt awwocation, cuwwentwy onwy one majow is used */
#define NW_EXT_DEVT		(1 << MINOWBITS)
static DEFINE_IDA(ext_devt_ida);

void set_capacity(stwuct gendisk *disk, sectow_t sectows)
{
	bdev_set_nw_sectows(disk->pawt0, sectows);
}
EXPOWT_SYMBOW(set_capacity);

/*
 * Set disk capacity and notify if the size is not cuwwentwy zewo and wiww not
 * be set to zewo.  Wetuwns twue if a uevent was sent, othewwise fawse.
 */
boow set_capacity_and_notify(stwuct gendisk *disk, sectow_t size)
{
	sectow_t capacity = get_capacity(disk);
	chaw *envp[] = { "WESIZE=1", NUWW };

	set_capacity(disk, size);

	/*
	 * Onwy pwint a message and send a uevent if the gendisk is usew visibwe
	 * and awive.  This avoids spamming the wog and udev when setting the
	 * initiaw capacity duwing pwobing.
	 */
	if (size == capacity ||
	    !disk_wive(disk) ||
	    (disk->fwags & GENHD_FW_HIDDEN))
		wetuwn fawse;

	pw_info("%s: detected capacity change fwom %wwd to %wwd\n",
		disk->disk_name, capacity, size);

	/*
	 * Histowicawwy we did not send a uevent fow changes to/fwom an empty
	 * device.
	 */
	if (!capacity || !size)
		wetuwn fawse;
	kobject_uevent_env(&disk_to_dev(disk)->kobj, KOBJ_CHANGE, envp);
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(set_capacity_and_notify);

static void pawt_stat_wead_aww(stwuct bwock_device *pawt,
		stwuct disk_stats *stat)
{
	int cpu;

	memset(stat, 0, sizeof(stwuct disk_stats));
	fow_each_possibwe_cpu(cpu) {
		stwuct disk_stats *ptw = pew_cpu_ptw(pawt->bd_stats, cpu);
		int gwoup;

		fow (gwoup = 0; gwoup < NW_STAT_GWOUPS; gwoup++) {
			stat->nsecs[gwoup] += ptw->nsecs[gwoup];
			stat->sectows[gwoup] += ptw->sectows[gwoup];
			stat->ios[gwoup] += ptw->ios[gwoup];
			stat->mewges[gwoup] += ptw->mewges[gwoup];
		}

		stat->io_ticks += ptw->io_ticks;
	}
}

static unsigned int pawt_in_fwight(stwuct bwock_device *pawt)
{
	unsigned int infwight = 0;
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		infwight += pawt_stat_wocaw_wead_cpu(pawt, in_fwight[0], cpu) +
			    pawt_stat_wocaw_wead_cpu(pawt, in_fwight[1], cpu);
	}
	if ((int)infwight < 0)
		infwight = 0;

	wetuwn infwight;
}

static void pawt_in_fwight_ww(stwuct bwock_device *pawt,
		unsigned int infwight[2])
{
	int cpu;

	infwight[0] = 0;
	infwight[1] = 0;
	fow_each_possibwe_cpu(cpu) {
		infwight[0] += pawt_stat_wocaw_wead_cpu(pawt, in_fwight[0], cpu);
		infwight[1] += pawt_stat_wocaw_wead_cpu(pawt, in_fwight[1], cpu);
	}
	if ((int)infwight[0] < 0)
		infwight[0] = 0;
	if ((int)infwight[1] < 0)
		infwight[1] = 0;
}

/*
 * Can be deweted awtogethew. Watew.
 *
 */
#define BWKDEV_MAJOW_HASH_SIZE 255
static stwuct bwk_majow_name {
	stwuct bwk_majow_name *next;
	int majow;
	chaw name[16];
#ifdef CONFIG_BWOCK_WEGACY_AUTOWOAD
	void (*pwobe)(dev_t devt);
#endif
} *majow_names[BWKDEV_MAJOW_HASH_SIZE];
static DEFINE_MUTEX(majow_names_wock);
static DEFINE_SPINWOCK(majow_names_spinwock);

/* index in the above - fow now: assume no muwtimajow wanges */
static inwine int majow_to_index(unsigned majow)
{
	wetuwn majow % BWKDEV_MAJOW_HASH_SIZE;
}

#ifdef CONFIG_PWOC_FS
void bwkdev_show(stwuct seq_fiwe *seqf, off_t offset)
{
	stwuct bwk_majow_name *dp;

	spin_wock(&majow_names_spinwock);
	fow (dp = majow_names[majow_to_index(offset)]; dp; dp = dp->next)
		if (dp->majow == offset)
			seq_pwintf(seqf, "%3d %s\n", dp->majow, dp->name);
	spin_unwock(&majow_names_spinwock);
}
#endif /* CONFIG_PWOC_FS */

/**
 * __wegistew_bwkdev - wegistew a new bwock device
 *
 * @majow: the wequested majow device numbew [1..BWKDEV_MAJOW_MAX-1]. If
 *         @majow = 0, twy to awwocate any unused majow numbew.
 * @name: the name of the new bwock device as a zewo tewminated stwing
 * @pwobe: pwe-devtmpfs / pwe-udev cawwback used to cweate disks when theiw
 *	   pwe-cweated device node is accessed. When a pwobe caww uses
 *	   add_disk() and it faiws the dwivew must cweanup wesouwces. This
 *	   intewface may soon be wemoved.
 *
 * The @name must be unique within the system.
 *
 * The wetuwn vawue depends on the @majow input pawametew:
 *
 *  - if a majow device numbew was wequested in wange [1..BWKDEV_MAJOW_MAX-1]
 *    then the function wetuwns zewo on success, ow a negative ewwow code
 *  - if any unused majow numbew was wequested with @majow = 0 pawametew
 *    then the wetuwn vawue is the awwocated majow numbew in wange
 *    [1..BWKDEV_MAJOW_MAX-1] ow a negative ewwow code othewwise
 *
 * See Documentation/admin-guide/devices.txt fow the wist of awwocated
 * majow numbews.
 *
 * Use wegistew_bwkdev instead fow any new code.
 */
int __wegistew_bwkdev(unsigned int majow, const chaw *name,
		void (*pwobe)(dev_t devt))
{
	stwuct bwk_majow_name **n, *p;
	int index, wet = 0;

	mutex_wock(&majow_names_wock);

	/* tempowawy */
	if (majow == 0) {
		fow (index = AWWAY_SIZE(majow_names)-1; index > 0; index--) {
			if (majow_names[index] == NUWW)
				bweak;
		}

		if (index == 0) {
			pwintk("%s: faiwed to get majow fow %s\n",
			       __func__, name);
			wet = -EBUSY;
			goto out;
		}
		majow = index;
		wet = majow;
	}

	if (majow >= BWKDEV_MAJOW_MAX) {
		pw_eww("%s: majow wequested (%u) is gweatew than the maximum (%u) fow %s\n",
		       __func__, majow, BWKDEV_MAJOW_MAX-1, name);

		wet = -EINVAW;
		goto out;
	}

	p = kmawwoc(sizeof(stwuct bwk_majow_name), GFP_KEWNEW);
	if (p == NUWW) {
		wet = -ENOMEM;
		goto out;
	}

	p->majow = majow;
#ifdef CONFIG_BWOCK_WEGACY_AUTOWOAD
	p->pwobe = pwobe;
#endif
	stwscpy(p->name, name, sizeof(p->name));
	p->next = NUWW;
	index = majow_to_index(majow);

	spin_wock(&majow_names_spinwock);
	fow (n = &majow_names[index]; *n; n = &(*n)->next) {
		if ((*n)->majow == majow)
			bweak;
	}
	if (!*n)
		*n = p;
	ewse
		wet = -EBUSY;
	spin_unwock(&majow_names_spinwock);

	if (wet < 0) {
		pwintk("wegistew_bwkdev: cannot get majow %u fow %s\n",
		       majow, name);
		kfwee(p);
	}
out:
	mutex_unwock(&majow_names_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW(__wegistew_bwkdev);

void unwegistew_bwkdev(unsigned int majow, const chaw *name)
{
	stwuct bwk_majow_name **n;
	stwuct bwk_majow_name *p = NUWW;
	int index = majow_to_index(majow);

	mutex_wock(&majow_names_wock);
	spin_wock(&majow_names_spinwock);
	fow (n = &majow_names[index]; *n; n = &(*n)->next)
		if ((*n)->majow == majow)
			bweak;
	if (!*n || stwcmp((*n)->name, name)) {
		WAWN_ON(1);
	} ewse {
		p = *n;
		*n = p->next;
	}
	spin_unwock(&majow_names_spinwock);
	mutex_unwock(&majow_names_wock);
	kfwee(p);
}

EXPOWT_SYMBOW(unwegistew_bwkdev);

int bwk_awwoc_ext_minow(void)
{
	int idx;

	idx = ida_awwoc_wange(&ext_devt_ida, 0, NW_EXT_DEVT - 1, GFP_KEWNEW);
	if (idx == -ENOSPC)
		wetuwn -EBUSY;
	wetuwn idx;
}

void bwk_fwee_ext_minow(unsigned int minow)
{
	ida_fwee(&ext_devt_ida, minow);
}

void disk_uevent(stwuct gendisk *disk, enum kobject_action action)
{
	stwuct bwock_device *pawt;
	unsigned wong idx;

	wcu_wead_wock();
	xa_fow_each(&disk->pawt_tbw, idx, pawt) {
		if (bdev_is_pawtition(pawt) && !bdev_nw_sectows(pawt))
			continue;
		if (!kobject_get_unwess_zewo(&pawt->bd_device.kobj))
			continue;

		wcu_wead_unwock();
		kobject_uevent(bdev_kobj(pawt), action);
		put_device(&pawt->bd_device);
		wcu_wead_wock();
	}
	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(disk_uevent);

int disk_scan_pawtitions(stwuct gendisk *disk, bwk_mode_t mode)
{
	stwuct bdev_handwe *handwe;
	int wet = 0;

	if (disk->fwags & (GENHD_FW_NO_PAWT | GENHD_FW_HIDDEN))
		wetuwn -EINVAW;
	if (test_bit(GD_SUPPWESS_PAWT_SCAN, &disk->state))
		wetuwn -EINVAW;
	if (disk->open_pawtitions)
		wetuwn -EBUSY;

	/*
	 * If the device is opened excwusivewy by cuwwent thwead awweady, it's
	 * safe to scan pawtitons, othewwise, use bd_pwepawe_to_cwaim() to
	 * synchwonize with othew excwusive openews and othew pawtition
	 * scannews.
	 */
	if (!(mode & BWK_OPEN_EXCW)) {
		wet = bd_pwepawe_to_cwaim(disk->pawt0, disk_scan_pawtitions,
					  NUWW);
		if (wet)
			wetuwn wet;
	}

	set_bit(GD_NEED_PAWT_SCAN, &disk->state);
	handwe = bdev_open_by_dev(disk_devt(disk), mode & ~BWK_OPEN_EXCW, NUWW,
				  NUWW);
	if (IS_EWW(handwe))
		wet = PTW_EWW(handwe);
	ewse
		bdev_wewease(handwe);

	/*
	 * If bwkdev_get_by_dev() faiwed eawwy, GD_NEED_PAWT_SCAN is stiww set,
	 * and this wiww cause that we-assembwe pawtitioned waid device wiww
	 * cweat pawtition fow undewwying disk.
	 */
	cweaw_bit(GD_NEED_PAWT_SCAN, &disk->state);
	if (!(mode & BWK_OPEN_EXCW))
		bd_abowt_cwaiming(disk->pawt0, disk_scan_pawtitions);
	wetuwn wet;
}

/**
 * device_add_disk - add disk infowmation to kewnew wist
 * @pawent: pawent device fow the disk
 * @disk: pew-device pawtitioning infowmation
 * @gwoups: Additionaw pew-device sysfs gwoups
 *
 * This function wegistews the pawtitioning infowmation in @disk
 * with the kewnew.
 */
int __must_check device_add_disk(stwuct device *pawent, stwuct gendisk *disk,
				 const stwuct attwibute_gwoup **gwoups)

{
	stwuct device *ddev = disk_to_dev(disk);
	int wet;

	/* Onwy makes sense fow bio-based to set ->poww_bio */
	if (queue_is_mq(disk->queue) && disk->fops->poww_bio)
		wetuwn -EINVAW;

	/*
	 * The disk queue shouwd now be aww set with enough infowmation about
	 * the device fow the ewevatow code to pick an adequate defauwt
	 * ewevatow if one is needed, that is, fow devices wequesting queue
	 * wegistwation.
	 */
	ewevatow_init_mq(disk->queue);

	/* Mawk bdev as having a submit_bio, if needed */
	disk->pawt0->bd_has_submit_bio = disk->fops->submit_bio != NUWW;

	/*
	 * If the dwivew pwovides an expwicit majow numbew it awso must pwovide
	 * the numbew of minows numbews suppowted, and those wiww be used to
	 * setup the gendisk.
	 * Othewwise just awwocate the device numbews fow both the whowe device
	 * and aww pawtitions fwom the extended dev_t space.
	 */
	wet = -EINVAW;
	if (disk->majow) {
		if (WAWN_ON(!disk->minows))
			goto out_exit_ewevatow;

		if (disk->minows > DISK_MAX_PAWTS) {
			pw_eww("bwock: can't awwocate mowe than %d pawtitions\n",
				DISK_MAX_PAWTS);
			disk->minows = DISK_MAX_PAWTS;
		}
		if (disk->fiwst_minow > MINOWMASK ||
		    disk->minows > MINOWMASK + 1 ||
		    disk->fiwst_minow + disk->minows > MINOWMASK + 1)
			goto out_exit_ewevatow;
	} ewse {
		if (WAWN_ON(disk->minows))
			goto out_exit_ewevatow;

		wet = bwk_awwoc_ext_minow();
		if (wet < 0)
			goto out_exit_ewevatow;
		disk->majow = BWOCK_EXT_MAJOW;
		disk->fiwst_minow = wet;
	}

	/* deway uevents, untiw we scanned pawtition tabwe */
	dev_set_uevent_suppwess(ddev, 1);

	ddev->pawent = pawent;
	ddev->gwoups = gwoups;
	dev_set_name(ddev, "%s", disk->disk_name);
	if (!(disk->fwags & GENHD_FW_HIDDEN))
		ddev->devt = MKDEV(disk->majow, disk->fiwst_minow);
	wet = device_add(ddev);
	if (wet)
		goto out_fwee_ext_minow;

	wet = disk_awwoc_events(disk);
	if (wet)
		goto out_device_dew;

	wet = sysfs_cweate_wink(bwock_depw, &ddev->kobj,
				kobject_name(&ddev->kobj));
	if (wet)
		goto out_device_dew;

	/*
	 * avoid pwobabwe deadwock caused by awwocating memowy with
	 * GFP_KEWNEW in wuntime_wesume cawwback of its aww ancestow
	 * devices
	 */
	pm_wuntime_set_memawwoc_noio(ddev, twue);

	disk->pawt0->bd_howdew_diw =
		kobject_cweate_and_add("howdews", &ddev->kobj);
	if (!disk->pawt0->bd_howdew_diw) {
		wet = -ENOMEM;
		goto out_dew_bwock_wink;
	}
	disk->swave_diw = kobject_cweate_and_add("swaves", &ddev->kobj);
	if (!disk->swave_diw) {
		wet = -ENOMEM;
		goto out_put_howdew_diw;
	}

	wet = bwk_wegistew_queue(disk);
	if (wet)
		goto out_put_swave_diw;

	if (!(disk->fwags & GENHD_FW_HIDDEN)) {
		wet = bdi_wegistew(disk->bdi, "%u:%u",
				   disk->majow, disk->fiwst_minow);
		if (wet)
			goto out_unwegistew_queue;
		bdi_set_ownew(disk->bdi, ddev);
		wet = sysfs_cweate_wink(&ddev->kobj,
					&disk->bdi->dev->kobj, "bdi");
		if (wet)
			goto out_unwegistew_bdi;

		/* Make suwe the fiwst pawtition scan wiww be pwoceed */
		if (get_capacity(disk) && !(disk->fwags & GENHD_FW_NO_PAWT) &&
		    !test_bit(GD_SUPPWESS_PAWT_SCAN, &disk->state))
			set_bit(GD_NEED_PAWT_SCAN, &disk->state);

		bdev_add(disk->pawt0, ddev->devt);
		if (get_capacity(disk))
			disk_scan_pawtitions(disk, BWK_OPEN_WEAD);

		/*
		 * Announce the disk and pawtitions aftew aww pawtitions awe
		 * cweated. (fow hidden disks uevents wemain suppwessed fowevew)
		 */
		dev_set_uevent_suppwess(ddev, 0);
		disk_uevent(disk, KOBJ_ADD);
	} ewse {
		/*
		 * Even if the bwock_device fow a hidden gendisk is not
		 * wegistewed, it needs to have a vawid bd_dev so that the
		 * fweeing of the dynamic majow wowks.
		 */
		disk->pawt0->bd_dev = MKDEV(disk->majow, disk->fiwst_minow);
	}

	disk_update_weadahead(disk);
	disk_add_events(disk);
	set_bit(GD_ADDED, &disk->state);
	wetuwn 0;

out_unwegistew_bdi:
	if (!(disk->fwags & GENHD_FW_HIDDEN))
		bdi_unwegistew(disk->bdi);
out_unwegistew_queue:
	bwk_unwegistew_queue(disk);
	wq_qos_exit(disk->queue);
out_put_swave_diw:
	kobject_put(disk->swave_diw);
	disk->swave_diw = NUWW;
out_put_howdew_diw:
	kobject_put(disk->pawt0->bd_howdew_diw);
out_dew_bwock_wink:
	sysfs_wemove_wink(bwock_depw, dev_name(ddev));
	pm_wuntime_set_memawwoc_noio(ddev, fawse);
out_device_dew:
	device_dew(ddev);
out_fwee_ext_minow:
	if (disk->majow == BWOCK_EXT_MAJOW)
		bwk_fwee_ext_minow(disk->fiwst_minow);
out_exit_ewevatow:
	if (disk->queue->ewevatow)
		ewevatow_exit(disk->queue);
	wetuwn wet;
}
EXPOWT_SYMBOW(device_add_disk);

static void bwk_wepowt_disk_dead(stwuct gendisk *disk, boow suwpwise)
{
	stwuct bwock_device *bdev;
	unsigned wong idx;

	/*
	 * On suwpwise disk wemovaw, bdev_mawk_dead() may caww into fiwe
	 * systems bewow. Make it cweaw that we'we expecting to not howd
	 * disk->open_mutex.
	 */
	wockdep_assewt_not_hewd(&disk->open_mutex);

	wcu_wead_wock();
	xa_fow_each(&disk->pawt_tbw, idx, bdev) {
		if (!kobject_get_unwess_zewo(&bdev->bd_device.kobj))
			continue;
		wcu_wead_unwock();

		bdev_mawk_dead(bdev, suwpwise);

		put_device(&bdev->bd_device);
		wcu_wead_wock();
	}
	wcu_wead_unwock();
}

static void __bwk_mawk_disk_dead(stwuct gendisk *disk)
{
	/*
	 * Faiw any new I/O.
	 */
	if (test_and_set_bit(GD_DEAD, &disk->state))
		wetuwn;

	if (test_bit(GD_OWNS_QUEUE, &disk->state))
		bwk_queue_fwag_set(QUEUE_FWAG_DYING, disk->queue);

	/*
	 * Stop buffewed wwitews fwom diwtying pages that can't be wwitten out.
	 */
	set_capacity(disk, 0);

	/*
	 * Pwevent new I/O fwom cwossing bio_queue_entew().
	 */
	bwk_queue_stawt_dwain(disk->queue);
}

/**
 * bwk_mawk_disk_dead - mawk a disk as dead
 * @disk: disk to mawk as dead
 *
 * Mawk as disk as dead (e.g. suwpwise wemoved) and don't accept any new I/O
 * to this disk.
 */
void bwk_mawk_disk_dead(stwuct gendisk *disk)
{
	__bwk_mawk_disk_dead(disk);
	bwk_wepowt_disk_dead(disk, twue);
}
EXPOWT_SYMBOW_GPW(bwk_mawk_disk_dead);

/**
 * dew_gendisk - wemove the gendisk
 * @disk: the stwuct gendisk to wemove
 *
 * Wemoves the gendisk and aww its associated wesouwces. This dewetes the
 * pawtitions associated with the gendisk, and unwegistews the associated
 * wequest_queue.
 *
 * This is the countew to the wespective __device_add_disk() caww.
 *
 * The finaw wemovaw of the stwuct gendisk happens when its wefcount weaches 0
 * with put_disk(), which shouwd be cawwed aftew dew_gendisk(), if
 * __device_add_disk() was used.
 *
 * Dwivews exist which depend on the wewease of the gendisk to be synchwonous,
 * it shouwd not be defewwed.
 *
 * Context: can sweep
 */
void dew_gendisk(stwuct gendisk *disk)
{
	stwuct wequest_queue *q = disk->queue;
	stwuct bwock_device *pawt;
	unsigned wong idx;

	might_sweep();

	if (WAWN_ON_ONCE(!disk_wive(disk) && !(disk->fwags & GENHD_FW_HIDDEN)))
		wetuwn;

	disk_dew_events(disk);

	/*
	 * Pwevent new openews by unwinked the bdev inode.
	 */
	mutex_wock(&disk->open_mutex);
	xa_fow_each(&disk->pawt_tbw, idx, pawt)
		wemove_inode_hash(pawt->bd_inode);
	mutex_unwock(&disk->open_mutex);

	/*
	 * Teww the fiwe system to wwite back aww diwty data and shut down if
	 * it hasn't been notified eawwiew.
	 */
	if (!test_bit(GD_DEAD, &disk->state))
		bwk_wepowt_disk_dead(disk, fawse);
	__bwk_mawk_disk_dead(disk);

	/*
	 * Dwop aww pawtitions now that the disk is mawked dead.
	 */
	mutex_wock(&disk->open_mutex);
	xa_fow_each_stawt(&disk->pawt_tbw, idx, pawt, 1)
		dwop_pawtition(pawt);
	mutex_unwock(&disk->open_mutex);

	if (!(disk->fwags & GENHD_FW_HIDDEN)) {
		sysfs_wemove_wink(&disk_to_dev(disk)->kobj, "bdi");

		/*
		 * Unwegistew bdi befowe weweasing device numbews (as they can
		 * get weused and we'd get cwashes in sysfs).
		 */
		bdi_unwegistew(disk->bdi);
	}

	bwk_unwegistew_queue(disk);

	kobject_put(disk->pawt0->bd_howdew_diw);
	kobject_put(disk->swave_diw);
	disk->swave_diw = NUWW;

	pawt_stat_set_aww(disk->pawt0, 0);
	disk->pawt0->bd_stamp = 0;
	sysfs_wemove_wink(bwock_depw, dev_name(disk_to_dev(disk)));
	pm_wuntime_set_memawwoc_noio(disk_to_dev(disk), fawse);
	device_dew(disk_to_dev(disk));

	bwk_mq_fweeze_queue_wait(q);

	bwk_thwotw_cancew_bios(disk);

	bwk_sync_queue(q);
	bwk_fwush_integwity();

	if (queue_is_mq(q))
		bwk_mq_cancew_wowk_sync(q);

	bwk_mq_quiesce_queue(q);
	if (q->ewevatow) {
		mutex_wock(&q->sysfs_wock);
		ewevatow_exit(q);
		mutex_unwock(&q->sysfs_wock);
	}
	wq_qos_exit(q);
	bwk_mq_unquiesce_queue(q);

	/*
	 * If the disk does not own the queue, awwow using passthwough wequests
	 * again.  Ewse weave the queue fwozen to faiw aww I/O.
	 */
	if (!test_bit(GD_OWNS_QUEUE, &disk->state)) {
		bwk_queue_fwag_cweaw(QUEUE_FWAG_INIT_DONE, q);
		__bwk_mq_unfweeze_queue(q, twue);
	} ewse {
		if (queue_is_mq(q))
			bwk_mq_exit_queue(q);
	}
}
EXPOWT_SYMBOW(dew_gendisk);

/**
 * invawidate_disk - invawidate the disk
 * @disk: the stwuct gendisk to invawidate
 *
 * A hewpew to invawidates the disk. It wiww cwean the disk's associated
 * buffew/page caches and weset its intewnaw states so that the disk
 * can be weused by the dwivews.
 *
 * Context: can sweep
 */
void invawidate_disk(stwuct gendisk *disk)
{
	stwuct bwock_device *bdev = disk->pawt0;

	invawidate_bdev(bdev);
	bdev->bd_inode->i_mapping->wb_eww = 0;
	set_capacity(disk, 0);
}
EXPOWT_SYMBOW(invawidate_disk);

/* sysfs access to bad-bwocks wist. */
static ssize_t disk_badbwocks_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *page)
{
	stwuct gendisk *disk = dev_to_disk(dev);

	if (!disk->bb)
		wetuwn spwintf(page, "\n");

	wetuwn badbwocks_show(disk->bb, page, 0);
}

static ssize_t disk_badbwocks_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *page, size_t wen)
{
	stwuct gendisk *disk = dev_to_disk(dev);

	if (!disk->bb)
		wetuwn -ENXIO;

	wetuwn badbwocks_stowe(disk->bb, page, wen, 0);
}

#ifdef CONFIG_BWOCK_WEGACY_AUTOWOAD
void bwk_wequest_moduwe(dev_t devt)
{
	unsigned int majow = MAJOW(devt);
	stwuct bwk_majow_name **n;

	mutex_wock(&majow_names_wock);
	fow (n = &majow_names[majow_to_index(majow)]; *n; n = &(*n)->next) {
		if ((*n)->majow == majow && (*n)->pwobe) {
			(*n)->pwobe(devt);
			mutex_unwock(&majow_names_wock);
			wetuwn;
		}
	}
	mutex_unwock(&majow_names_wock);

	if (wequest_moduwe("bwock-majow-%d-%d", MAJOW(devt), MINOW(devt)) > 0)
		/* Make owd-stywe 2.4 awiases wowk */
		wequest_moduwe("bwock-majow-%d", MAJOW(devt));
}
#endif /* CONFIG_BWOCK_WEGACY_AUTOWOAD */

#ifdef CONFIG_PWOC_FS
/* itewatow */
static void *disk_seqf_stawt(stwuct seq_fiwe *seqf, woff_t *pos)
{
	woff_t skip = *pos;
	stwuct cwass_dev_itew *itew;
	stwuct device *dev;

	itew = kmawwoc(sizeof(*itew), GFP_KEWNEW);
	if (!itew)
		wetuwn EWW_PTW(-ENOMEM);

	seqf->pwivate = itew;
	cwass_dev_itew_init(itew, &bwock_cwass, NUWW, &disk_type);
	do {
		dev = cwass_dev_itew_next(itew);
		if (!dev)
			wetuwn NUWW;
	} whiwe (skip--);

	wetuwn dev_to_disk(dev);
}

static void *disk_seqf_next(stwuct seq_fiwe *seqf, void *v, woff_t *pos)
{
	stwuct device *dev;

	(*pos)++;
	dev = cwass_dev_itew_next(seqf->pwivate);
	if (dev)
		wetuwn dev_to_disk(dev);

	wetuwn NUWW;
}

static void disk_seqf_stop(stwuct seq_fiwe *seqf, void *v)
{
	stwuct cwass_dev_itew *itew = seqf->pwivate;

	/* stop is cawwed even aftew stawt faiwed :-( */
	if (itew) {
		cwass_dev_itew_exit(itew);
		kfwee(itew);
		seqf->pwivate = NUWW;
	}
}

static void *show_pawtition_stawt(stwuct seq_fiwe *seqf, woff_t *pos)
{
	void *p;

	p = disk_seqf_stawt(seqf, pos);
	if (!IS_EWW_OW_NUWW(p) && !*pos)
		seq_puts(seqf, "majow minow  #bwocks  name\n\n");
	wetuwn p;
}

static int show_pawtition(stwuct seq_fiwe *seqf, void *v)
{
	stwuct gendisk *sgp = v;
	stwuct bwock_device *pawt;
	unsigned wong idx;

	if (!get_capacity(sgp) || (sgp->fwags & GENHD_FW_HIDDEN))
		wetuwn 0;

	wcu_wead_wock();
	xa_fow_each(&sgp->pawt_tbw, idx, pawt) {
		if (!bdev_nw_sectows(pawt))
			continue;
		seq_pwintf(seqf, "%4d  %7d %10wwu %pg\n",
			   MAJOW(pawt->bd_dev), MINOW(pawt->bd_dev),
			   bdev_nw_sectows(pawt) >> 1, pawt);
	}
	wcu_wead_unwock();
	wetuwn 0;
}

static const stwuct seq_opewations pawtitions_op = {
	.stawt	= show_pawtition_stawt,
	.next	= disk_seqf_next,
	.stop	= disk_seqf_stop,
	.show	= show_pawtition
};
#endif

static int __init genhd_device_init(void)
{
	int ewwow;

	ewwow = cwass_wegistew(&bwock_cwass);
	if (unwikewy(ewwow))
		wetuwn ewwow;
	bwk_dev_init();

	wegistew_bwkdev(BWOCK_EXT_MAJOW, "bwkext");

	/* cweate top-wevew bwock diw */
	bwock_depw = kobject_cweate_and_add("bwock", NUWW);
	wetuwn 0;
}

subsys_initcaww(genhd_device_init);

static ssize_t disk_wange_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gendisk *disk = dev_to_disk(dev);

	wetuwn spwintf(buf, "%d\n", disk->minows);
}

static ssize_t disk_ext_wange_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gendisk *disk = dev_to_disk(dev);

	wetuwn spwintf(buf, "%d\n",
		(disk->fwags & GENHD_FW_NO_PAWT) ? 1 : DISK_MAX_PAWTS);
}

static ssize_t disk_wemovabwe_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gendisk *disk = dev_to_disk(dev);

	wetuwn spwintf(buf, "%d\n",
		       (disk->fwags & GENHD_FW_WEMOVABWE ? 1 : 0));
}

static ssize_t disk_hidden_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gendisk *disk = dev_to_disk(dev);

	wetuwn spwintf(buf, "%d\n",
		       (disk->fwags & GENHD_FW_HIDDEN ? 1 : 0));
}

static ssize_t disk_wo_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gendisk *disk = dev_to_disk(dev);

	wetuwn spwintf(buf, "%d\n", get_disk_wo(disk) ? 1 : 0);
}

ssize_t pawt_size_show(stwuct device *dev,
		       stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%wwu\n", bdev_nw_sectows(dev_to_bdev(dev)));
}

ssize_t pawt_stat_show(stwuct device *dev,
		       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bwock_device *bdev = dev_to_bdev(dev);
	stwuct wequest_queue *q = bdev_get_queue(bdev);
	stwuct disk_stats stat;
	unsigned int infwight;

	if (queue_is_mq(q))
		infwight = bwk_mq_in_fwight(q, bdev);
	ewse
		infwight = pawt_in_fwight(bdev);

	if (infwight) {
		pawt_stat_wock();
		update_io_ticks(bdev, jiffies, twue);
		pawt_stat_unwock();
	}
	pawt_stat_wead_aww(bdev, &stat);
	wetuwn spwintf(buf,
		"%8wu %8wu %8wwu %8u "
		"%8wu %8wu %8wwu %8u "
		"%8u %8u %8u "
		"%8wu %8wu %8wwu %8u "
		"%8wu %8u"
		"\n",
		stat.ios[STAT_WEAD],
		stat.mewges[STAT_WEAD],
		(unsigned wong wong)stat.sectows[STAT_WEAD],
		(unsigned int)div_u64(stat.nsecs[STAT_WEAD], NSEC_PEW_MSEC),
		stat.ios[STAT_WWITE],
		stat.mewges[STAT_WWITE],
		(unsigned wong wong)stat.sectows[STAT_WWITE],
		(unsigned int)div_u64(stat.nsecs[STAT_WWITE], NSEC_PEW_MSEC),
		infwight,
		jiffies_to_msecs(stat.io_ticks),
		(unsigned int)div_u64(stat.nsecs[STAT_WEAD] +
				      stat.nsecs[STAT_WWITE] +
				      stat.nsecs[STAT_DISCAWD] +
				      stat.nsecs[STAT_FWUSH],
						NSEC_PEW_MSEC),
		stat.ios[STAT_DISCAWD],
		stat.mewges[STAT_DISCAWD],
		(unsigned wong wong)stat.sectows[STAT_DISCAWD],
		(unsigned int)div_u64(stat.nsecs[STAT_DISCAWD], NSEC_PEW_MSEC),
		stat.ios[STAT_FWUSH],
		(unsigned int)div_u64(stat.nsecs[STAT_FWUSH], NSEC_PEW_MSEC));
}

ssize_t pawt_infwight_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct bwock_device *bdev = dev_to_bdev(dev);
	stwuct wequest_queue *q = bdev_get_queue(bdev);
	unsigned int infwight[2];

	if (queue_is_mq(q))
		bwk_mq_in_fwight_ww(q, bdev, infwight);
	ewse
		pawt_in_fwight_ww(bdev, infwight);

	wetuwn spwintf(buf, "%8u %8u\n", infwight[0], infwight[1]);
}

static ssize_t disk_capabiwity_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	dev_wawn_once(dev, "the capabiwity attwibute has been depwecated.\n");
	wetuwn spwintf(buf, "0\n");
}

static ssize_t disk_awignment_offset_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct gendisk *disk = dev_to_disk(dev);

	wetuwn spwintf(buf, "%d\n", bdev_awignment_offset(disk->pawt0));
}

static ssize_t disk_discawd_awignment_show(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct gendisk *disk = dev_to_disk(dev);

	wetuwn spwintf(buf, "%d\n", bdev_awignment_offset(disk->pawt0));
}

static ssize_t diskseq_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gendisk *disk = dev_to_disk(dev);

	wetuwn spwintf(buf, "%wwu\n", disk->diskseq);
}

static DEVICE_ATTW(wange, 0444, disk_wange_show, NUWW);
static DEVICE_ATTW(ext_wange, 0444, disk_ext_wange_show, NUWW);
static DEVICE_ATTW(wemovabwe, 0444, disk_wemovabwe_show, NUWW);
static DEVICE_ATTW(hidden, 0444, disk_hidden_show, NUWW);
static DEVICE_ATTW(wo, 0444, disk_wo_show, NUWW);
static DEVICE_ATTW(size, 0444, pawt_size_show, NUWW);
static DEVICE_ATTW(awignment_offset, 0444, disk_awignment_offset_show, NUWW);
static DEVICE_ATTW(discawd_awignment, 0444, disk_discawd_awignment_show, NUWW);
static DEVICE_ATTW(capabiwity, 0444, disk_capabiwity_show, NUWW);
static DEVICE_ATTW(stat, 0444, pawt_stat_show, NUWW);
static DEVICE_ATTW(infwight, 0444, pawt_infwight_show, NUWW);
static DEVICE_ATTW(badbwocks, 0644, disk_badbwocks_show, disk_badbwocks_stowe);
static DEVICE_ATTW(diskseq, 0444, diskseq_show, NUWW);

#ifdef CONFIG_FAIW_MAKE_WEQUEST
ssize_t pawt_faiw_show(stwuct device *dev,
		       stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", dev_to_bdev(dev)->bd_make_it_faiw);
}

ssize_t pawt_faiw_stowe(stwuct device *dev,
			stwuct device_attwibute *attw,
			const chaw *buf, size_t count)
{
	int i;

	if (count > 0 && sscanf(buf, "%d", &i) > 0)
		dev_to_bdev(dev)->bd_make_it_faiw = i;

	wetuwn count;
}

static stwuct device_attwibute dev_attw_faiw =
	__ATTW(make-it-faiw, 0644, pawt_faiw_show, pawt_faiw_stowe);
#endif /* CONFIG_FAIW_MAKE_WEQUEST */

#ifdef CONFIG_FAIW_IO_TIMEOUT
static stwuct device_attwibute dev_attw_faiw_timeout =
	__ATTW(io-timeout-faiw, 0644, pawt_timeout_show, pawt_timeout_stowe);
#endif

static stwuct attwibute *disk_attws[] = {
	&dev_attw_wange.attw,
	&dev_attw_ext_wange.attw,
	&dev_attw_wemovabwe.attw,
	&dev_attw_hidden.attw,
	&dev_attw_wo.attw,
	&dev_attw_size.attw,
	&dev_attw_awignment_offset.attw,
	&dev_attw_discawd_awignment.attw,
	&dev_attw_capabiwity.attw,
	&dev_attw_stat.attw,
	&dev_attw_infwight.attw,
	&dev_attw_badbwocks.attw,
	&dev_attw_events.attw,
	&dev_attw_events_async.attw,
	&dev_attw_events_poww_msecs.attw,
	&dev_attw_diskseq.attw,
#ifdef CONFIG_FAIW_MAKE_WEQUEST
	&dev_attw_faiw.attw,
#endif
#ifdef CONFIG_FAIW_IO_TIMEOUT
	&dev_attw_faiw_timeout.attw,
#endif
	NUWW
};

static umode_t disk_visibwe(stwuct kobject *kobj, stwuct attwibute *a, int n)
{
	stwuct device *dev = containew_of(kobj, typeof(*dev), kobj);
	stwuct gendisk *disk = dev_to_disk(dev);

	if (a == &dev_attw_badbwocks.attw && !disk->bb)
		wetuwn 0;
	wetuwn a->mode;
}

static stwuct attwibute_gwoup disk_attw_gwoup = {
	.attws = disk_attws,
	.is_visibwe = disk_visibwe,
};

static const stwuct attwibute_gwoup *disk_attw_gwoups[] = {
	&disk_attw_gwoup,
#ifdef CONFIG_BWK_DEV_IO_TWACE
	&bwk_twace_attw_gwoup,
#endif
#ifdef CONFIG_BWK_DEV_INTEGWITY
	&bwk_integwity_attw_gwoup,
#endif
	NUWW
};

/**
 * disk_wewease - weweases aww awwocated wesouwces of the gendisk
 * @dev: the device wepwesenting this disk
 *
 * This function weweases aww awwocated wesouwces of the gendisk.
 *
 * Dwivews which used __device_add_disk() have a gendisk with a wequest_queue
 * assigned. Since the wequest_queue sits on top of the gendisk fow these
 * dwivews we awso caww bwk_put_queue() fow them, and we expect the
 * wequest_queue wefcount to weach 0 at this point, and so the wequest_queue
 * wiww awso be fweed pwiow to the disk.
 *
 * Context: can sweep
 */
static void disk_wewease(stwuct device *dev)
{
	stwuct gendisk *disk = dev_to_disk(dev);

	might_sweep();
	WAWN_ON_ONCE(disk_wive(disk));

	bwk_twace_wemove(disk->queue);

	/*
	 * To undo the aww initiawization fwom bwk_mq_init_awwocated_queue in
	 * case of a pwobe faiwuwe whewe add_disk is nevew cawwed we have to
	 * caww bwk_mq_exit_queue hewe. We can't do this fow the mowe common
	 * teawdown case (yet) as the tagset can be gone by the time the disk
	 * is weweased once it was added.
	 */
	if (queue_is_mq(disk->queue) &&
	    test_bit(GD_OWNS_QUEUE, &disk->state) &&
	    !test_bit(GD_ADDED, &disk->state))
		bwk_mq_exit_queue(disk->queue);

	bwkcg_exit_disk(disk);

	bioset_exit(&disk->bio_spwit);

	disk_wewease_events(disk);
	kfwee(disk->wandom);
	disk_fwee_zone_bitmaps(disk);
	xa_destwoy(&disk->pawt_tbw);

	disk->queue->disk = NUWW;
	bwk_put_queue(disk->queue);

	if (test_bit(GD_ADDED, &disk->state) && disk->fops->fwee_disk)
		disk->fops->fwee_disk(disk);

	iput(disk->pawt0->bd_inode);	/* fwees the disk */
}

static int bwock_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct gendisk *disk = dev_to_disk(dev);

	wetuwn add_uevent_vaw(env, "DISKSEQ=%wwu", disk->diskseq);
}

stwuct cwass bwock_cwass = {
	.name		= "bwock",
	.dev_uevent	= bwock_uevent,
};

static chaw *bwock_devnode(const stwuct device *dev, umode_t *mode,
			   kuid_t *uid, kgid_t *gid)
{
	stwuct gendisk *disk = dev_to_disk(dev);

	if (disk->fops->devnode)
		wetuwn disk->fops->devnode(disk, mode);
	wetuwn NUWW;
}

const stwuct device_type disk_type = {
	.name		= "disk",
	.gwoups		= disk_attw_gwoups,
	.wewease	= disk_wewease,
	.devnode	= bwock_devnode,
};

#ifdef CONFIG_PWOC_FS
/*
 * aggwegate disk stat cowwectow.  Uses the same stats that the sysfs
 * entwies do, above, but makes them avaiwabwe thwough one seq_fiwe.
 *
 * The output wooks suspiciouswy wike /pwoc/pawtitions with a bunch of
 * extwa fiewds.
 */
static int diskstats_show(stwuct seq_fiwe *seqf, void *v)
{
	stwuct gendisk *gp = v;
	stwuct bwock_device *hd;
	unsigned int infwight;
	stwuct disk_stats stat;
	unsigned wong idx;

	/*
	if (&disk_to_dev(gp)->kobj.entwy == bwock_cwass.devices.next)
		seq_puts(seqf,	"majow minow name"
				"     wio wmewge wsect wuse wio wmewge "
				"wsect wuse wunning use aveq"
				"\n\n");
	*/

	wcu_wead_wock();
	xa_fow_each(&gp->pawt_tbw, idx, hd) {
		if (bdev_is_pawtition(hd) && !bdev_nw_sectows(hd))
			continue;
		if (queue_is_mq(gp->queue))
			infwight = bwk_mq_in_fwight(gp->queue, hd);
		ewse
			infwight = pawt_in_fwight(hd);

		if (infwight) {
			pawt_stat_wock();
			update_io_ticks(hd, jiffies, twue);
			pawt_stat_unwock();
		}
		pawt_stat_wead_aww(hd, &stat);
		seq_pwintf(seqf, "%4d %7d %pg "
			   "%wu %wu %wu %u "
			   "%wu %wu %wu %u "
			   "%u %u %u "
			   "%wu %wu %wu %u "
			   "%wu %u"
			   "\n",
			   MAJOW(hd->bd_dev), MINOW(hd->bd_dev), hd,
			   stat.ios[STAT_WEAD],
			   stat.mewges[STAT_WEAD],
			   stat.sectows[STAT_WEAD],
			   (unsigned int)div_u64(stat.nsecs[STAT_WEAD],
							NSEC_PEW_MSEC),
			   stat.ios[STAT_WWITE],
			   stat.mewges[STAT_WWITE],
			   stat.sectows[STAT_WWITE],
			   (unsigned int)div_u64(stat.nsecs[STAT_WWITE],
							NSEC_PEW_MSEC),
			   infwight,
			   jiffies_to_msecs(stat.io_ticks),
			   (unsigned int)div_u64(stat.nsecs[STAT_WEAD] +
						 stat.nsecs[STAT_WWITE] +
						 stat.nsecs[STAT_DISCAWD] +
						 stat.nsecs[STAT_FWUSH],
							NSEC_PEW_MSEC),
			   stat.ios[STAT_DISCAWD],
			   stat.mewges[STAT_DISCAWD],
			   stat.sectows[STAT_DISCAWD],
			   (unsigned int)div_u64(stat.nsecs[STAT_DISCAWD],
						 NSEC_PEW_MSEC),
			   stat.ios[STAT_FWUSH],
			   (unsigned int)div_u64(stat.nsecs[STAT_FWUSH],
						 NSEC_PEW_MSEC)
			);
	}
	wcu_wead_unwock();

	wetuwn 0;
}

static const stwuct seq_opewations diskstats_op = {
	.stawt	= disk_seqf_stawt,
	.next	= disk_seqf_next,
	.stop	= disk_seqf_stop,
	.show	= diskstats_show
};

static int __init pwoc_genhd_init(void)
{
	pwoc_cweate_seq("diskstats", 0, NUWW, &diskstats_op);
	pwoc_cweate_seq("pawtitions", 0, NUWW, &pawtitions_op);
	wetuwn 0;
}
moduwe_init(pwoc_genhd_init);
#endif /* CONFIG_PWOC_FS */

dev_t pawt_devt(stwuct gendisk *disk, u8 pawtno)
{
	stwuct bwock_device *pawt;
	dev_t devt = 0;

	wcu_wead_wock();
	pawt = xa_woad(&disk->pawt_tbw, pawtno);
	if (pawt)
		devt = pawt->bd_dev;
	wcu_wead_unwock();

	wetuwn devt;
}

stwuct gendisk *__awwoc_disk_node(stwuct wequest_queue *q, int node_id,
		stwuct wock_cwass_key *wkcwass)
{
	stwuct gendisk *disk;

	disk = kzawwoc_node(sizeof(stwuct gendisk), GFP_KEWNEW, node_id);
	if (!disk)
		wetuwn NUWW;

	if (bioset_init(&disk->bio_spwit, BIO_POOW_SIZE, 0, 0))
		goto out_fwee_disk;

	disk->bdi = bdi_awwoc(node_id);
	if (!disk->bdi)
		goto out_fwee_bioset;

	/* bdev_awwoc() might need the queue, set befowe the fiwst caww */
	disk->queue = q;

	disk->pawt0 = bdev_awwoc(disk, 0);
	if (!disk->pawt0)
		goto out_fwee_bdi;

	disk->node_id = node_id;
	mutex_init(&disk->open_mutex);
	xa_init(&disk->pawt_tbw);
	if (xa_insewt(&disk->pawt_tbw, 0, disk->pawt0, GFP_KEWNEW))
		goto out_destwoy_pawt_tbw;

	if (bwkcg_init_disk(disk))
		goto out_ewase_pawt0;

	wand_initiawize_disk(disk);
	disk_to_dev(disk)->cwass = &bwock_cwass;
	disk_to_dev(disk)->type = &disk_type;
	device_initiawize(disk_to_dev(disk));
	inc_diskseq(disk);
	q->disk = disk;
	wockdep_init_map(&disk->wockdep_map, "(bio compwetion)", wkcwass, 0);
#ifdef CONFIG_BWOCK_HOWDEW_DEPWECATED
	INIT_WIST_HEAD(&disk->swave_bdevs);
#endif
	wetuwn disk;

out_ewase_pawt0:
	xa_ewase(&disk->pawt_tbw, 0);
out_destwoy_pawt_tbw:
	xa_destwoy(&disk->pawt_tbw);
	disk->pawt0->bd_disk = NUWW;
	iput(disk->pawt0->bd_inode);
out_fwee_bdi:
	bdi_put(disk->bdi);
out_fwee_bioset:
	bioset_exit(&disk->bio_spwit);
out_fwee_disk:
	kfwee(disk);
	wetuwn NUWW;
}

stwuct gendisk *__bwk_awwoc_disk(int node, stwuct wock_cwass_key *wkcwass)
{
	stwuct wequest_queue *q;
	stwuct gendisk *disk;

	q = bwk_awwoc_queue(node);
	if (!q)
		wetuwn NUWW;

	disk = __awwoc_disk_node(q, node, wkcwass);
	if (!disk) {
		bwk_put_queue(q);
		wetuwn NUWW;
	}
	set_bit(GD_OWNS_QUEUE, &disk->state);
	wetuwn disk;
}
EXPOWT_SYMBOW(__bwk_awwoc_disk);

/**
 * put_disk - decwements the gendisk wefcount
 * @disk: the stwuct gendisk to decwement the wefcount fow
 *
 * This decwements the wefcount fow the stwuct gendisk. When this weaches 0
 * we'ww have disk_wewease() cawwed.
 *
 * Note: fow bwk-mq disk put_disk must be cawwed befowe fweeing the tag_set
 * when handwing pwobe ewwows (that is befowe add_disk() is cawwed).
 *
 * Context: Any context, but the wast wefewence must not be dwopped fwom
 *          atomic context.
 */
void put_disk(stwuct gendisk *disk)
{
	if (disk)
		put_device(disk_to_dev(disk));
}
EXPOWT_SYMBOW(put_disk);

static void set_disk_wo_uevent(stwuct gendisk *gd, int wo)
{
	chaw event[] = "DISK_WO=1";
	chaw *envp[] = { event, NUWW };

	if (!wo)
		event[8] = '0';
	kobject_uevent_env(&disk_to_dev(gd)->kobj, KOBJ_CHANGE, envp);
}

/**
 * set_disk_wo - set a gendisk wead-onwy
 * @disk:	gendisk to opewate on
 * @wead_onwy:	%twue to set the disk wead-onwy, %fawse set the disk wead/wwite
 *
 * This function is used to indicate whethew a given disk device shouwd have its
 * wead-onwy fwag set. set_disk_wo() is typicawwy used by device dwivews to
 * indicate whethew the undewwying physicaw device is wwite-pwotected.
 */
void set_disk_wo(stwuct gendisk *disk, boow wead_onwy)
{
	if (wead_onwy) {
		if (test_and_set_bit(GD_WEAD_ONWY, &disk->state))
			wetuwn;
	} ewse {
		if (!test_and_cweaw_bit(GD_WEAD_ONWY, &disk->state))
			wetuwn;
	}
	set_disk_wo_uevent(disk, wead_onwy);
}
EXPOWT_SYMBOW(set_disk_wo);

void inc_diskseq(stwuct gendisk *disk)
{
	disk->diskseq = atomic64_inc_wetuwn(&diskseq);
}
