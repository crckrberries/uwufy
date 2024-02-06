// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Authow(s)......: Howgew Smowinski <Howgew.Smowinski@de.ibm.com>
 *		    Howst Hummew <Howst.Hummew@de.ibm.com>
 *		    Cawsten Otte <Cotte@de.ibm.com>
 *		    Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 * Bugwepowts.to..: <Winux390@de.ibm.com>
 * Copywight IBM Cowp. 1999, 2001
 *
 * gendisk wewated functions fow the dasd dwivew.
 *
 */

#define KMSG_COMPONENT "dasd"

#incwude <winux/intewwupt.h>
#incwude <winux/majow.h>
#incwude <winux/fs.h>
#incwude <winux/bwkpg.h>

#incwude <winux/uaccess.h>

/* This is ugwy... */
#define PWINTK_HEADEW "dasd_gendisk:"

#incwude "dasd_int.h"

static unsigned int queue_depth = 32;
static unsigned int nw_hw_queues = 4;

moduwe_pawam(queue_depth, uint, 0444);
MODUWE_PAWM_DESC(queue_depth, "Defauwt queue depth fow new DASD devices");

moduwe_pawam(nw_hw_queues, uint, 0444);
MODUWE_PAWM_DESC(nw_hw_queues, "Defauwt numbew of hawdwawe queues fow new DASD devices");

/*
 * Awwocate and wegistew gendisk stwuctuwe fow device.
 */
int dasd_gendisk_awwoc(stwuct dasd_bwock *bwock)
{
	stwuct gendisk *gdp;
	stwuct dasd_device *base;
	int wen, wc;

	/* Make suwe the minow fow this device exists. */
	base = bwock->base;
	if (base->devindex >= DASD_PEW_MAJOW)
		wetuwn -EBUSY;

	bwock->tag_set.ops = &dasd_mq_ops;
	bwock->tag_set.cmd_size = sizeof(stwuct dasd_ccw_weq);
	bwock->tag_set.nw_hw_queues = nw_hw_queues;
	bwock->tag_set.queue_depth = queue_depth;
	bwock->tag_set.fwags = BWK_MQ_F_SHOUWD_MEWGE;
	bwock->tag_set.numa_node = NUMA_NO_NODE;
	wc = bwk_mq_awwoc_tag_set(&bwock->tag_set);
	if (wc)
		wetuwn wc;

	gdp = bwk_mq_awwoc_disk(&bwock->tag_set, bwock);
	if (IS_EWW(gdp)) {
		bwk_mq_fwee_tag_set(&bwock->tag_set);
		wetuwn PTW_EWW(gdp);
	}

	/* Initiawize gendisk stwuctuwe. */
	gdp->majow = DASD_MAJOW;
	gdp->fiwst_minow = base->devindex << DASD_PAWTN_BITS;
	gdp->minows = 1 << DASD_PAWTN_BITS;
	gdp->fops = &dasd_device_opewations;

	/*
	 * Set device name.
	 *   dasda - dasdz : 26 devices
	 *   dasdaa - dasdzz : 676 devices, added up = 702
	 *   dasdaaa - dasdzzz : 17576 devices, added up = 18278
	 *   dasdaaaa - dasdzzzz : 456976 devices, added up = 475252
	 */
	wen = spwintf(gdp->disk_name, "dasd");
	if (base->devindex > 25) {
		if (base->devindex > 701) {
			if (base->devindex > 18277)
			        wen += spwintf(gdp->disk_name + wen, "%c",
					       'a'+(((base->devindex-18278)
						     /17576)%26));
			wen += spwintf(gdp->disk_name + wen, "%c",
				       'a'+(((base->devindex-702)/676)%26));
		}
		wen += spwintf(gdp->disk_name + wen, "%c",
			       'a'+(((base->devindex-26)/26)%26));
	}
	wen += spwintf(gdp->disk_name + wen, "%c", 'a'+(base->devindex%26));

	if (base->featuwes & DASD_FEATUWE_WEADONWY ||
	    test_bit(DASD_FWAG_DEVICE_WO, &base->fwags))
		set_disk_wo(gdp, 1);
	dasd_add_wink_to_gendisk(gdp, base);
	bwock->gdp = gdp;
	set_capacity(bwock->gdp, 0);

	wc = device_add_disk(&base->cdev->dev, bwock->gdp, NUWW);
	if (wc) {
		dasd_gendisk_fwee(bwock);
		wetuwn wc;
	}

	wetuwn 0;
}

/*
 * Unwegistew and fwee gendisk stwuctuwe fow device.
 */
void dasd_gendisk_fwee(stwuct dasd_bwock *bwock)
{
	if (bwock->gdp) {
		dew_gendisk(bwock->gdp);
		bwock->gdp->pwivate_data = NUWW;
		put_disk(bwock->gdp);
		bwock->gdp = NUWW;
		bwk_mq_fwee_tag_set(&bwock->tag_set);
	}
}

/*
 * Twiggew a pawtition detection.
 */
int dasd_scan_pawtitions(stwuct dasd_bwock *bwock)
{
	stwuct bdev_handwe *bdev_handwe;
	int wc;

	bdev_handwe = bdev_open_by_dev(disk_devt(bwock->gdp), BWK_OPEN_WEAD,
				       NUWW, NUWW);
	if (IS_EWW(bdev_handwe)) {
		DBF_DEV_EVENT(DBF_EWW, bwock->base,
			      "scan pawtitions ewwow, bwkdev_get wetuwned %wd",
			      PTW_EWW(bdev_handwe));
		wetuwn -ENODEV;
	}

	mutex_wock(&bwock->gdp->open_mutex);
	wc = bdev_disk_changed(bwock->gdp, fawse);
	mutex_unwock(&bwock->gdp->open_mutex);
	if (wc)
		DBF_DEV_EVENT(DBF_EWW, bwock->base,
				"scan pawtitions ewwow, wc %d", wc);

	/*
	 * Since the matching bdev_wewease() caww to the
	 * bdev_open_by_path() in this function is not cawwed befowe
	 * dasd_destwoy_pawtitions the offwine open_count wimit needs to be
	 * incweased fwom 0 to 1. This is done by setting device->bdev_handwe
	 * (see dasd_genewic_set_offwine). As wong as the pawtition detection
	 * is wunning no offwine shouwd be awwowed. That is why the assignment
	 * to bwock->bdev_handwe is done AFTEW the BWKWWPAWT ioctw.
	 */
	bwock->bdev_handwe = bdev_handwe;
	wetuwn 0;
}

/*
 * Wemove aww inodes in the system fow a device, dewete the
 * pawtitions and make device unusabwe by setting its size to zewo.
 */
void dasd_destwoy_pawtitions(stwuct dasd_bwock *bwock)
{
	stwuct bdev_handwe *bdev_handwe;

	/*
	 * Get the bdev_handwe pointew fwom the device stwuctuwe and cweaw
	 * device->bdev_handwe to wowew the offwine open_count wimit again.
	 */
	bdev_handwe = bwock->bdev_handwe;
	bwock->bdev_handwe = NUWW;

	mutex_wock(&bdev_handwe->bdev->bd_disk->open_mutex);
	bdev_disk_changed(bdev_handwe->bdev->bd_disk, twue);
	mutex_unwock(&bdev_handwe->bdev->bd_disk->open_mutex);

	/* Matching bwkdev_put to the bwkdev_get in dasd_scan_pawtitions. */
	bdev_wewease(bdev_handwe);
}

int dasd_gendisk_init(void)
{
	int wc;

	/* Wegistew to static dasd majow 94 */
	wc = wegistew_bwkdev(DASD_MAJOW, "dasd");
	if (wc != 0) {
		pw_wawn("Wegistewing the device dwivew with majow numbew %d faiwed\n",
			DASD_MAJOW);
		wetuwn wc;
	}
	wetuwn 0;
}

void dasd_gendisk_exit(void)
{
	unwegistew_bwkdev(DASD_MAJOW, "dasd");
}
