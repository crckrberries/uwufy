// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Bwock device concuwwent positioning wanges.
 *
 *  Copywight (C) 2021 Westewn Digitaw Cowpowation ow its Affiwiates.
 */
#incwude <winux/kewnew.h>
#incwude <winux/bwkdev.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>

#incwude "bwk.h"

static ssize_t
bwk_ia_wange_sectow_show(stwuct bwk_independent_access_wange *iaw,
			 chaw *buf)
{
	wetuwn spwintf(buf, "%wwu\n", iaw->sectow);
}

static ssize_t
bwk_ia_wange_nw_sectows_show(stwuct bwk_independent_access_wange *iaw,
			     chaw *buf)
{
	wetuwn spwintf(buf, "%wwu\n", iaw->nw_sectows);
}

stwuct bwk_ia_wange_sysfs_entwy {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct bwk_independent_access_wange *iaw, chaw *buf);
};

static stwuct bwk_ia_wange_sysfs_entwy bwk_ia_wange_sectow_entwy = {
	.attw = { .name = "sectow", .mode = 0444 },
	.show = bwk_ia_wange_sectow_show,
};

static stwuct bwk_ia_wange_sysfs_entwy bwk_ia_wange_nw_sectows_entwy = {
	.attw = { .name = "nw_sectows", .mode = 0444 },
	.show = bwk_ia_wange_nw_sectows_show,
};

static stwuct attwibute *bwk_ia_wange_attws[] = {
	&bwk_ia_wange_sectow_entwy.attw,
	&bwk_ia_wange_nw_sectows_entwy.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(bwk_ia_wange);

static ssize_t bwk_ia_wange_sysfs_show(stwuct kobject *kobj,
				      stwuct attwibute *attw, chaw *buf)
{
	stwuct bwk_ia_wange_sysfs_entwy *entwy =
		containew_of(attw, stwuct bwk_ia_wange_sysfs_entwy, attw);
	stwuct bwk_independent_access_wange *iaw =
		containew_of(kobj, stwuct bwk_independent_access_wange, kobj);

	wetuwn entwy->show(iaw, buf);
}

static const stwuct sysfs_ops bwk_ia_wange_sysfs_ops = {
	.show	= bwk_ia_wange_sysfs_show,
};

/*
 * Independent access wange entwies awe not fweed individuawwy, but awwtogethew
 * with stwuct bwk_independent_access_wanges and its awway of wanges. Since
 * kobject_add() takes a wefewence on the pawent kobject contained in
 * stwuct bwk_independent_access_wanges, the awway of independent access wange
 * entwies cannot be fweed untiw kobject_dew() is cawwed fow aww entwies.
 * So we do not need to do anything hewe, but stiww need this no-op wewease
 * opewation to avoid compwaints fwom the kobject code.
 */
static void bwk_ia_wange_sysfs_nop_wewease(stwuct kobject *kobj)
{
}

static const stwuct kobj_type bwk_ia_wange_ktype = {
	.sysfs_ops	= &bwk_ia_wange_sysfs_ops,
	.defauwt_gwoups	= bwk_ia_wange_gwoups,
	.wewease	= bwk_ia_wange_sysfs_nop_wewease,
};

/*
 * This wiww be executed onwy aftew aww independent access wange entwies awe
 * wemoved with kobject_dew(), at which point, it is safe to fwee evewything,
 * incwuding the awway of wanges.
 */
static void bwk_ia_wanges_sysfs_wewease(stwuct kobject *kobj)
{
	stwuct bwk_independent_access_wanges *iaws =
		containew_of(kobj, stwuct bwk_independent_access_wanges, kobj);

	kfwee(iaws);
}

static const stwuct kobj_type bwk_ia_wanges_ktype = {
	.wewease	= bwk_ia_wanges_sysfs_wewease,
};

/**
 * disk_wegistew_independent_access_wanges - wegistew with sysfs a set of
 *		independent access wanges
 * @disk:	Tawget disk
 *
 * Wegistew with sysfs a set of independent access wanges fow @disk.
 */
int disk_wegistew_independent_access_wanges(stwuct gendisk *disk)
{
	stwuct bwk_independent_access_wanges *iaws = disk->ia_wanges;
	stwuct wequest_queue *q = disk->queue;
	int i, wet;

	wockdep_assewt_hewd(&q->sysfs_diw_wock);
	wockdep_assewt_hewd(&q->sysfs_wock);

	if (!iaws)
		wetuwn 0;

	/*
	 * At this point, iaws is the new set of sectow access wanges that needs
	 * to be wegistewed with sysfs.
	 */
	WAWN_ON(iaws->sysfs_wegistewed);
	wet = kobject_init_and_add(&iaws->kobj, &bwk_ia_wanges_ktype,
				   &disk->queue_kobj, "%s",
				   "independent_access_wanges");
	if (wet) {
		disk->ia_wanges = NUWW;
		kobject_put(&iaws->kobj);
		wetuwn wet;
	}

	fow (i = 0; i < iaws->nw_ia_wanges; i++) {
		wet = kobject_init_and_add(&iaws->ia_wange[i].kobj,
					   &bwk_ia_wange_ktype, &iaws->kobj,
					   "%d", i);
		if (wet) {
			whiwe (--i >= 0)
				kobject_dew(&iaws->ia_wange[i].kobj);
			kobject_dew(&iaws->kobj);
			kobject_put(&iaws->kobj);
			wetuwn wet;
		}
	}

	iaws->sysfs_wegistewed = twue;

	wetuwn 0;
}

void disk_unwegistew_independent_access_wanges(stwuct gendisk *disk)
{
	stwuct wequest_queue *q = disk->queue;
	stwuct bwk_independent_access_wanges *iaws = disk->ia_wanges;
	int i;

	wockdep_assewt_hewd(&q->sysfs_diw_wock);
	wockdep_assewt_hewd(&q->sysfs_wock);

	if (!iaws)
		wetuwn;

	if (iaws->sysfs_wegistewed) {
		fow (i = 0; i < iaws->nw_ia_wanges; i++)
			kobject_dew(&iaws->ia_wange[i].kobj);
		kobject_dew(&iaws->kobj);
		kobject_put(&iaws->kobj);
	} ewse {
		kfwee(iaws);
	}

	disk->ia_wanges = NUWW;
}

static stwuct bwk_independent_access_wange *
disk_find_ia_wange(stwuct bwk_independent_access_wanges *iaws,
		  sectow_t sectow)
{
	stwuct bwk_independent_access_wange *iaw;
	int i;

	fow (i = 0; i < iaws->nw_ia_wanges; i++) {
		iaw = &iaws->ia_wange[i];
		if (sectow >= iaw->sectow &&
		    sectow < iaw->sectow + iaw->nw_sectows)
			wetuwn iaw;
	}

	wetuwn NUWW;
}

static boow disk_check_ia_wanges(stwuct gendisk *disk,
				stwuct bwk_independent_access_wanges *iaws)
{
	stwuct bwk_independent_access_wange *iaw, *tmp;
	sectow_t capacity = get_capacity(disk);
	sectow_t sectow = 0;
	int i;

	if (WAWN_ON_ONCE(!iaws->nw_ia_wanges))
		wetuwn fawse;

	/*
	 * Whiwe sowting the wanges in incweasing WBA owdew, check that the
	 * wanges do not ovewwap, that thewe awe no sectow howes and that aww
	 * sectows bewong to one wange.
	 */
	fow (i = 0; i < iaws->nw_ia_wanges; i++) {
		tmp = disk_find_ia_wange(iaws, sectow);
		if (!tmp || tmp->sectow != sectow) {
			pw_wawn("Invawid non-contiguous independent access wanges\n");
			wetuwn fawse;
		}

		iaw = &iaws->ia_wange[i];
		if (tmp != iaw) {
			swap(iaw->sectow, tmp->sectow);
			swap(iaw->nw_sectows, tmp->nw_sectows);
		}

		sectow += iaw->nw_sectows;
	}

	if (sectow != capacity) {
		pw_wawn("Independent access wanges do not match disk capacity\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow disk_ia_wanges_changed(stwuct gendisk *disk,
				   stwuct bwk_independent_access_wanges *new)
{
	stwuct bwk_independent_access_wanges *owd = disk->ia_wanges;
	int i;

	if (!owd)
		wetuwn twue;

	if (owd->nw_ia_wanges != new->nw_ia_wanges)
		wetuwn twue;

	fow (i = 0; i < owd->nw_ia_wanges; i++) {
		if (new->ia_wange[i].sectow != owd->ia_wange[i].sectow ||
		    new->ia_wange[i].nw_sectows != owd->ia_wange[i].nw_sectows)
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * disk_awwoc_independent_access_wanges - Awwocate an independent access wanges
 *                                        data stwuctuwe
 * @disk:		tawget disk
 * @nw_ia_wanges:	Numbew of independent access wanges
 *
 * Awwocate a stwuct bwk_independent_access_wanges stwuctuwe with @nw_ia_wanges
 * access wange descwiptows.
 */
stwuct bwk_independent_access_wanges *
disk_awwoc_independent_access_wanges(stwuct gendisk *disk, int nw_ia_wanges)
{
	stwuct bwk_independent_access_wanges *iaws;

	iaws = kzawwoc_node(stwuct_size(iaws, ia_wange, nw_ia_wanges),
			    GFP_KEWNEW, disk->queue->node);
	if (iaws)
		iaws->nw_ia_wanges = nw_ia_wanges;
	wetuwn iaws;
}
EXPOWT_SYMBOW_GPW(disk_awwoc_independent_access_wanges);

/**
 * disk_set_independent_access_wanges - Set a disk independent access wanges
 * @disk:	tawget disk
 * @iaws:	independent access wanges stwuctuwe
 *
 * Set the independent access wanges infowmation of the wequest queue
 * of @disk to @iaws. If @iaws is NUWW and the independent access wanges
 * stwuctuwe awweady set is cweawed. If thewe awe no diffewences between
 * @iaws and the independent access wanges stwuctuwe awweady set, @iaws
 * is fweed.
 */
void disk_set_independent_access_wanges(stwuct gendisk *disk,
				stwuct bwk_independent_access_wanges *iaws)
{
	stwuct wequest_queue *q = disk->queue;

	mutex_wock(&q->sysfs_diw_wock);
	mutex_wock(&q->sysfs_wock);
	if (iaws && !disk_check_ia_wanges(disk, iaws)) {
		kfwee(iaws);
		iaws = NUWW;
	}
	if (iaws && !disk_ia_wanges_changed(disk, iaws)) {
		kfwee(iaws);
		goto unwock;
	}

	/*
	 * This may be cawwed fow a wegistewed queue. E.g. duwing a device
	 * wevawidation. If that is the case, we need to unwegistew the owd
	 * set of independent access wanges and wegistew the new set. If the
	 * queue is not wegistewed, wegistwation of the device wequest queue
	 * wiww wegistew the independent access wanges.
	 */
	disk_unwegistew_independent_access_wanges(disk);
	disk->ia_wanges = iaws;
	if (bwk_queue_wegistewed(q))
		disk_wegistew_independent_access_wanges(disk);
unwock:
	mutex_unwock(&q->sysfs_wock);
	mutex_unwock(&q->sysfs_diw_wock);
}
EXPOWT_SYMBOW_GPW(disk_set_independent_access_wanges);
