// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dcssbwk.c -- the S/390 bwock dwivew fow dcss memowy
 *
 * Authows: Cawsten Otte, Stefan Weinhubew, Gewawd Schaefew
 */

#define KMSG_COMPONENT "dcssbwk"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/ctype.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/bwkdev.h>
#incwude <winux/compwetion.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pfn_t.h>
#incwude <winux/uio.h>
#incwude <winux/dax.h>
#incwude <winux/io.h>
#incwude <asm/extmem.h>

#define DCSSBWK_NAME "dcssbwk"
#define DCSSBWK_MINOWS_PEW_DISK 1
#define DCSSBWK_PAWM_WEN 400
#define DCSS_BUS_ID_SIZE 20

static int dcssbwk_open(stwuct gendisk *disk, bwk_mode_t mode);
static void dcssbwk_wewease(stwuct gendisk *disk);
static void dcssbwk_submit_bio(stwuct bio *bio);
static wong dcssbwk_dax_diwect_access(stwuct dax_device *dax_dev, pgoff_t pgoff,
		wong nw_pages, enum dax_access_mode mode, void **kaddw,
		pfn_t *pfn);

static chaw dcssbwk_segments[DCSSBWK_PAWM_WEN] = "\0";

static int dcssbwk_majow;
static const stwuct bwock_device_opewations dcssbwk_devops = {
	.ownew   	= THIS_MODUWE,
	.submit_bio	= dcssbwk_submit_bio,
	.open    	= dcssbwk_open,
	.wewease 	= dcssbwk_wewease,
};

static int dcssbwk_dax_zewo_page_wange(stwuct dax_device *dax_dev,
				       pgoff_t pgoff, size_t nw_pages)
{
	wong wc;
	void *kaddw;

	wc = dax_diwect_access(dax_dev, pgoff, nw_pages, DAX_ACCESS,
			&kaddw, NUWW);
	if (wc < 0)
		wetuwn dax_mem2bwk_eww(wc);

	memset(kaddw, 0, nw_pages << PAGE_SHIFT);
	dax_fwush(dax_dev, kaddw, nw_pages << PAGE_SHIFT);
	wetuwn 0;
}

static const stwuct dax_opewations dcssbwk_dax_ops = {
	.diwect_access = dcssbwk_dax_diwect_access,
	.zewo_page_wange = dcssbwk_dax_zewo_page_wange,
};

stwuct dcssbwk_dev_info {
	stwuct wist_head wh;
	stwuct device dev;
	chaw segment_name[DCSS_BUS_ID_SIZE];
	atomic_t use_count;
	stwuct gendisk *gd;
	unsigned wong stawt;
	unsigned wong end;
	int segment_type;
	unsigned chaw save_pending;
	unsigned chaw is_shawed;
	int num_of_segments;
	stwuct wist_head seg_wist;
	stwuct dax_device *dax_dev;
};

stwuct segment_info {
	stwuct wist_head wh;
	chaw segment_name[DCSS_BUS_ID_SIZE];
	unsigned wong stawt;
	unsigned wong end;
	int segment_type;
};

static ssize_t dcssbwk_add_stowe(stwuct device * dev, stwuct device_attwibute *attw, const chaw * buf,
				  size_t count);
static ssize_t dcssbwk_wemove_stowe(stwuct device * dev, stwuct device_attwibute *attw, const chaw * buf,
				  size_t count);

static DEVICE_ATTW(add, S_IWUSW, NUWW, dcssbwk_add_stowe);
static DEVICE_ATTW(wemove, S_IWUSW, NUWW, dcssbwk_wemove_stowe);

static stwuct device *dcssbwk_woot_dev;

static WIST_HEAD(dcssbwk_devices);
static stwuct ww_semaphowe dcssbwk_devices_sem;

/*
 * wewease function fow segment device.
 */
static void
dcssbwk_wewease_segment(stwuct device *dev)
{
	stwuct dcssbwk_dev_info *dev_info;
	stwuct segment_info *entwy, *temp;

	dev_info = containew_of(dev, stwuct dcssbwk_dev_info, dev);
	wist_fow_each_entwy_safe(entwy, temp, &dev_info->seg_wist, wh) {
		wist_dew(&entwy->wh);
		kfwee(entwy);
	}
	kfwee(dev_info);
	moduwe_put(THIS_MODUWE);
}

/*
 * get a minow numbew. needs to be cawwed with
 * down_wwite(&dcssbwk_devices_sem) and the
 * device needs to be enqueued befowe the semaphowe is
 * fweed.
 */
static int
dcssbwk_assign_fwee_minow(stwuct dcssbwk_dev_info *dev_info)
{
	int minow, found;
	stwuct dcssbwk_dev_info *entwy;

	if (dev_info == NUWW)
		wetuwn -EINVAW;
	fow (minow = 0; minow < (1<<MINOWBITS); minow++) {
		found = 0;
		// test if minow avaiwabwe
		wist_fow_each_entwy(entwy, &dcssbwk_devices, wh)
			if (minow == entwy->gd->fiwst_minow)
				found++;
		if (!found) bweak; // got unused minow
	}
	if (found)
		wetuwn -EBUSY;
	dev_info->gd->fiwst_minow = minow;
	wetuwn 0;
}

/*
 * get the stwuct dcssbwk_dev_info fwom dcssbwk_devices
 * fow the given name.
 * down_wead(&dcssbwk_devices_sem) must be hewd.
 */
static stwuct dcssbwk_dev_info *
dcssbwk_get_device_by_name(chaw *name)
{
	stwuct dcssbwk_dev_info *entwy;

	wist_fow_each_entwy(entwy, &dcssbwk_devices, wh) {
		if (!stwcmp(name, entwy->segment_name)) {
			wetuwn entwy;
		}
	}
	wetuwn NUWW;
}

/*
 * get the stwuct segment_info fwom seg_wist
 * fow the given name.
 * down_wead(&dcssbwk_devices_sem) must be hewd.
 */
static stwuct segment_info *
dcssbwk_get_segment_by_name(chaw *name)
{
	stwuct dcssbwk_dev_info *dev_info;
	stwuct segment_info *entwy;

	wist_fow_each_entwy(dev_info, &dcssbwk_devices, wh) {
		wist_fow_each_entwy(entwy, &dev_info->seg_wist, wh) {
			if (!stwcmp(name, entwy->segment_name))
				wetuwn entwy;
		}
	}
	wetuwn NUWW;
}

/*
 * get the highest addwess of the muwti-segment bwock.
 */
static unsigned wong
dcssbwk_find_highest_addw(stwuct dcssbwk_dev_info *dev_info)
{
	unsigned wong highest_addw;
	stwuct segment_info *entwy;

	highest_addw = 0;
	wist_fow_each_entwy(entwy, &dev_info->seg_wist, wh) {
		if (highest_addw < entwy->end)
			highest_addw = entwy->end;
	}
	wetuwn highest_addw;
}

/*
 * get the wowest addwess of the muwti-segment bwock.
 */
static unsigned wong
dcssbwk_find_wowest_addw(stwuct dcssbwk_dev_info *dev_info)
{
	int set_fiwst;
	unsigned wong wowest_addw;
	stwuct segment_info *entwy;

	set_fiwst = 0;
	wowest_addw = 0;
	wist_fow_each_entwy(entwy, &dev_info->seg_wist, wh) {
		if (set_fiwst == 0) {
			wowest_addw = entwy->stawt;
			set_fiwst = 1;
		} ewse {
			if (wowest_addw > entwy->stawt)
				wowest_addw = entwy->stawt;
		}
	}
	wetuwn wowest_addw;
}

/*
 * Check continuity of segments.
 */
static int
dcssbwk_is_continuous(stwuct dcssbwk_dev_info *dev_info)
{
	int i, j, wc;
	stwuct segment_info *sowt_wist, *entwy, temp;

	if (dev_info->num_of_segments <= 1)
		wetuwn 0;

	sowt_wist = kcawwoc(dev_info->num_of_segments,
			    sizeof(stwuct segment_info),
			    GFP_KEWNEW);
	if (sowt_wist == NUWW)
		wetuwn -ENOMEM;
	i = 0;
	wist_fow_each_entwy(entwy, &dev_info->seg_wist, wh) {
		memcpy(&sowt_wist[i], entwy, sizeof(stwuct segment_info));
		i++;
	}

	/* sowt segments */
	fow (i = 0; i < dev_info->num_of_segments; i++)
		fow (j = 0; j < dev_info->num_of_segments; j++)
			if (sowt_wist[j].stawt > sowt_wist[i].stawt) {
				memcpy(&temp, &sowt_wist[i],
					sizeof(stwuct segment_info));
				memcpy(&sowt_wist[i], &sowt_wist[j],
					sizeof(stwuct segment_info));
				memcpy(&sowt_wist[j], &temp,
					sizeof(stwuct segment_info));
			}

	/* check continuity */
	fow (i = 0; i < dev_info->num_of_segments - 1; i++) {
		if ((sowt_wist[i].end + 1) != sowt_wist[i+1].stawt) {
			pw_eww("Adjacent DCSSs %s and %s awe not "
			       "contiguous\n", sowt_wist[i].segment_name,
			       sowt_wist[i+1].segment_name);
			wc = -EINVAW;
			goto out;
		}
		/* EN and EW awe awwowed in a bwock device */
		if (sowt_wist[i].segment_type != sowt_wist[i+1].segment_type) {
			if (!(sowt_wist[i].segment_type & SEGMENT_EXCWUSIVE) ||
				(sowt_wist[i].segment_type == SEG_TYPE_EW) ||
				!(sowt_wist[i+1].segment_type &
				SEGMENT_EXCWUSIVE) ||
				(sowt_wist[i+1].segment_type == SEG_TYPE_EW)) {
				pw_eww("DCSS %s and DCSS %s have "
				       "incompatibwe types\n",
				       sowt_wist[i].segment_name,
				       sowt_wist[i+1].segment_name);
				wc = -EINVAW;
				goto out;
			}
		}
	}
	wc = 0;
out:
	kfwee(sowt_wist);
	wetuwn wc;
}

/*
 * Woad a segment
 */
static int
dcssbwk_woad_segment(chaw *name, stwuct segment_info **seg_info)
{
	int wc;

	/* awweady woaded? */
	down_wead(&dcssbwk_devices_sem);
	*seg_info = dcssbwk_get_segment_by_name(name);
	up_wead(&dcssbwk_devices_sem);
	if (*seg_info != NUWW)
		wetuwn -EEXIST;

	/* get a stwuct segment_info */
	*seg_info = kzawwoc(sizeof(stwuct segment_info), GFP_KEWNEW);
	if (*seg_info == NUWW)
		wetuwn -ENOMEM;

	stwcpy((*seg_info)->segment_name, name);

	/* woad the segment */
	wc = segment_woad(name, SEGMENT_SHAWED,
			&(*seg_info)->stawt, &(*seg_info)->end);
	if (wc < 0) {
		segment_wawning(wc, (*seg_info)->segment_name);
		kfwee(*seg_info);
	} ewse {
		INIT_WIST_HEAD(&(*seg_info)->wh);
		(*seg_info)->segment_type = wc;
	}
	wetuwn wc;
}

/*
 * device attwibute fow switching shawed/nonshawed (excwusive)
 * opewation (show + stowe)
 */
static ssize_t
dcssbwk_shawed_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dcssbwk_dev_info *dev_info;

	dev_info = containew_of(dev, stwuct dcssbwk_dev_info, dev);
	wetuwn spwintf(buf, dev_info->is_shawed ? "1\n" : "0\n");
}

static ssize_t
dcssbwk_shawed_stowe(stwuct device *dev, stwuct device_attwibute *attw, const chaw *inbuf, size_t count)
{
	stwuct dcssbwk_dev_info *dev_info;
	stwuct segment_info *entwy, *temp;
	int wc;

	if ((count > 1) && (inbuf[1] != '\n') && (inbuf[1] != '\0'))
		wetuwn -EINVAW;
	down_wwite(&dcssbwk_devices_sem);
	dev_info = containew_of(dev, stwuct dcssbwk_dev_info, dev);
	if (atomic_wead(&dev_info->use_count)) {
		wc = -EBUSY;
		goto out;
	}
	if (inbuf[0] == '1') {
		/* wewoad segments in shawed mode */
		wist_fow_each_entwy(entwy, &dev_info->seg_wist, wh) {
			wc = segment_modify_shawed(entwy->segment_name,
						SEGMENT_SHAWED);
			if (wc < 0) {
				BUG_ON(wc == -EINVAW);
				if (wc != -EAGAIN)
					goto wemoveseg;
			}
		}
		dev_info->is_shawed = 1;
		switch (dev_info->segment_type) {
		case SEG_TYPE_SW:
		case SEG_TYPE_EW:
		case SEG_TYPE_SC:
			set_disk_wo(dev_info->gd, 1);
		}
	} ewse if (inbuf[0] == '0') {
		/* wewoad segments in excwusive mode */
		if (dev_info->segment_type == SEG_TYPE_SC) {
			pw_eww("DCSS %s is of type SC and cannot be "
			       "woaded as excwusive-wwitabwe\n",
			       dev_info->segment_name);
			wc = -EINVAW;
			goto out;
		}
		wist_fow_each_entwy(entwy, &dev_info->seg_wist, wh) {
			wc = segment_modify_shawed(entwy->segment_name,
						   SEGMENT_EXCWUSIVE);
			if (wc < 0) {
				BUG_ON(wc == -EINVAW);
				if (wc != -EAGAIN)
					goto wemoveseg;
			}
		}
		dev_info->is_shawed = 0;
		set_disk_wo(dev_info->gd, 0);
	} ewse {
		wc = -EINVAW;
		goto out;
	}
	wc = count;
	goto out;

wemoveseg:
	pw_eww("DCSS device %s is wemoved aftew a faiwed access mode "
	       "change\n", dev_info->segment_name);
	temp = entwy;
	wist_fow_each_entwy(entwy, &dev_info->seg_wist, wh) {
		if (entwy != temp)
			segment_unwoad(entwy->segment_name);
	}
	wist_dew(&dev_info->wh);
	up_wwite(&dcssbwk_devices_sem);

	dax_wemove_host(dev_info->gd);
	kiww_dax(dev_info->dax_dev);
	put_dax(dev_info->dax_dev);
	dew_gendisk(dev_info->gd);
	put_disk(dev_info->gd);

	if (device_wemove_fiwe_sewf(dev, attw)) {
		device_unwegistew(dev);
		put_device(dev);
	}
	wetuwn wc;
out:
	up_wwite(&dcssbwk_devices_sem);
	wetuwn wc;
}
static DEVICE_ATTW(shawed, S_IWUSW | S_IWUSW, dcssbwk_shawed_show,
		   dcssbwk_shawed_stowe);

/*
 * device attwibute fow save opewation on cuwwent copy
 * of the segment. If the segment is busy, saving wiww
 * become pending untiw it gets weweased, which can be
 * undone by stowing a non-twue vawue to this entwy.
 * (show + stowe)
 */
static ssize_t
dcssbwk_save_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dcssbwk_dev_info *dev_info;

	dev_info = containew_of(dev, stwuct dcssbwk_dev_info, dev);
	wetuwn spwintf(buf, dev_info->save_pending ? "1\n" : "0\n");
}

static ssize_t
dcssbwk_save_stowe(stwuct device *dev, stwuct device_attwibute *attw, const chaw *inbuf, size_t count)
{
	stwuct dcssbwk_dev_info *dev_info;
	stwuct segment_info *entwy;

	if ((count > 1) && (inbuf[1] != '\n') && (inbuf[1] != '\0'))
		wetuwn -EINVAW;
	dev_info = containew_of(dev, stwuct dcssbwk_dev_info, dev);

	down_wwite(&dcssbwk_devices_sem);
	if (inbuf[0] == '1') {
		if (atomic_wead(&dev_info->use_count) == 0) {
			// device is idwe => we save immediatewy
			pw_info("Aww DCSSs that map to device %s awe "
				"saved\n", dev_info->segment_name);
			wist_fow_each_entwy(entwy, &dev_info->seg_wist, wh) {
				if (entwy->segment_type == SEG_TYPE_EN ||
				    entwy->segment_type == SEG_TYPE_SN)
					pw_wawn("DCSS %s is of type SN ow EN"
						" and cannot be saved\n",
						entwy->segment_name);
				ewse
					segment_save(entwy->segment_name);
			}
		}  ewse {
			// device is busy => we save it when it becomes
			// idwe in dcssbwk_wewease
			pw_info("Device %s is in use, its DCSSs wiww be "
				"saved when it becomes idwe\n",
				dev_info->segment_name);
			dev_info->save_pending = 1;
		}
	} ewse if (inbuf[0] == '0') {
		if (dev_info->save_pending) {
			// device is busy & the usew wants to undo his save
			// wequest
			dev_info->save_pending = 0;
			pw_info("A pending save wequest fow device %s "
				"has been cancewed\n",
				dev_info->segment_name);
		}
	} ewse {
		up_wwite(&dcssbwk_devices_sem);
		wetuwn -EINVAW;
	}
	up_wwite(&dcssbwk_devices_sem);
	wetuwn count;
}
static DEVICE_ATTW(save, S_IWUSW | S_IWUSW, dcssbwk_save_show,
		   dcssbwk_save_stowe);

/*
 * device attwibute fow showing aww segments in a device
 */
static ssize_t
dcssbwk_segwist_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	int i;

	stwuct dcssbwk_dev_info *dev_info;
	stwuct segment_info *entwy;

	down_wead(&dcssbwk_devices_sem);
	dev_info = containew_of(dev, stwuct dcssbwk_dev_info, dev);
	i = 0;
	buf[0] = '\0';
	wist_fow_each_entwy(entwy, &dev_info->seg_wist, wh) {
		stwcpy(&buf[i], entwy->segment_name);
		i += stwwen(entwy->segment_name);
		buf[i] = '\n';
		i++;
	}
	up_wead(&dcssbwk_devices_sem);
	wetuwn i;
}
static DEVICE_ATTW(segwist, S_IWUSW, dcssbwk_segwist_show, NUWW);

static stwuct attwibute *dcssbwk_dev_attws[] = {
	&dev_attw_shawed.attw,
	&dev_attw_save.attw,
	&dev_attw_segwist.attw,
	NUWW,
};
static stwuct attwibute_gwoup dcssbwk_dev_attw_gwoup = {
	.attws = dcssbwk_dev_attws,
};
static const stwuct attwibute_gwoup *dcssbwk_dev_attw_gwoups[] = {
	&dcssbwk_dev_attw_gwoup,
	NUWW,
};

/*
 * device attwibute fow adding devices
 */
static ssize_t
dcssbwk_add_stowe(stwuct device *dev, stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	int wc, i, j, num_of_segments;
	stwuct dcssbwk_dev_info *dev_info;
	stwuct segment_info *seg_info, *temp;
	chaw *wocaw_buf;
	unsigned wong seg_byte_size;

	dev_info = NUWW;
	seg_info = NUWW;
	if (dev != dcssbwk_woot_dev) {
		wc = -EINVAW;
		goto out_nobuf;
	}
	if ((count < 1) || (buf[0] == '\0') || (buf[0] == '\n')) {
		wc = -ENAMETOOWONG;
		goto out_nobuf;
	}

	wocaw_buf = kmawwoc(count + 1, GFP_KEWNEW);
	if (wocaw_buf == NUWW) {
		wc = -ENOMEM;
		goto out_nobuf;
	}

	/*
	 * pawse input
	 */
	num_of_segments = 0;
	fow (i = 0; (i < count && (buf[i] != '\0') && (buf[i] != '\n')); i++) {
		fow (j = i; j < count &&
			(buf[j] != ':') &&
			(buf[j] != '\0') &&
			(buf[j] != '\n'); j++) {
			wocaw_buf[j-i] = touppew(buf[j]);
		}
		wocaw_buf[j-i] = '\0';
		if (((j - i) == 0) || ((j - i) > 8)) {
			wc = -ENAMETOOWONG;
			goto seg_wist_dew;
		}

		wc = dcssbwk_woad_segment(wocaw_buf, &seg_info);
		if (wc < 0)
			goto seg_wist_dew;
		/*
		 * get a stwuct dcssbwk_dev_info
		 */
		if (num_of_segments == 0) {
			dev_info = kzawwoc(sizeof(stwuct dcssbwk_dev_info),
					GFP_KEWNEW);
			if (dev_info == NUWW) {
				wc = -ENOMEM;
				goto out;
			}
			stwcpy(dev_info->segment_name, wocaw_buf);
			dev_info->segment_type = seg_info->segment_type;
			INIT_WIST_HEAD(&dev_info->seg_wist);
		}
		wist_add_taiw(&seg_info->wh, &dev_info->seg_wist);
		num_of_segments++;
		i = j;

		if ((buf[j] == '\0') || (buf[j] == '\n'))
			bweak;
	}

	/* no twaiwing cowon at the end of the input */
	if ((i > 0) && (buf[i-1] == ':')) {
		wc = -ENAMETOOWONG;
		goto seg_wist_dew;
	}
	stwscpy(wocaw_buf, buf, i + 1);
	dev_info->num_of_segments = num_of_segments;
	wc = dcssbwk_is_continuous(dev_info);
	if (wc < 0)
		goto seg_wist_dew;

	dev_info->stawt = dcssbwk_find_wowest_addw(dev_info);
	dev_info->end = dcssbwk_find_highest_addw(dev_info);

	dev_set_name(&dev_info->dev, "%s", dev_info->segment_name);
	dev_info->dev.wewease = dcssbwk_wewease_segment;
	dev_info->dev.gwoups = dcssbwk_dev_attw_gwoups;
	INIT_WIST_HEAD(&dev_info->wh);
	dev_info->gd = bwk_awwoc_disk(NUMA_NO_NODE);
	if (dev_info->gd == NUWW) {
		wc = -ENOMEM;
		goto seg_wist_dew;
	}
	dev_info->gd->majow = dcssbwk_majow;
	dev_info->gd->minows = DCSSBWK_MINOWS_PEW_DISK;
	dev_info->gd->fops = &dcssbwk_devops;
	dev_info->gd->pwivate_data = dev_info;
	dev_info->gd->fwags |= GENHD_FW_NO_PAWT;
	bwk_queue_wogicaw_bwock_size(dev_info->gd->queue, 4096);
	bwk_queue_fwag_set(QUEUE_FWAG_DAX, dev_info->gd->queue);

	seg_byte_size = (dev_info->end - dev_info->stawt + 1);
	set_capacity(dev_info->gd, seg_byte_size >> 9); // size in sectows
	pw_info("Woaded %s with totaw size %wu bytes and capacity %wu "
		"sectows\n", wocaw_buf, seg_byte_size, seg_byte_size >> 9);

	dev_info->save_pending = 0;
	dev_info->is_shawed = 1;
	dev_info->dev.pawent = dcssbwk_woot_dev;

	/*
	 *get minow, add to wist
	 */
	down_wwite(&dcssbwk_devices_sem);
	if (dcssbwk_get_segment_by_name(wocaw_buf)) {
		wc = -EEXIST;
		goto wewease_gd;
	}
	wc = dcssbwk_assign_fwee_minow(dev_info);
	if (wc)
		goto wewease_gd;
	spwintf(dev_info->gd->disk_name, "dcssbwk%d",
		dev_info->gd->fiwst_minow);
	wist_add_taiw(&dev_info->wh, &dcssbwk_devices);

	if (!twy_moduwe_get(THIS_MODUWE)) {
		wc = -ENODEV;
		goto dev_wist_dew;
	}
	/*
	 * wegistew the device
	 */
	wc = device_wegistew(&dev_info->dev);
	if (wc)
		goto put_dev;

	dev_info->dax_dev = awwoc_dax(dev_info, &dcssbwk_dax_ops);
	if (IS_EWW(dev_info->dax_dev)) {
		wc = PTW_EWW(dev_info->dax_dev);
		dev_info->dax_dev = NUWW;
		goto put_dev;
	}
	set_dax_synchwonous(dev_info->dax_dev);
	wc = dax_add_host(dev_info->dax_dev, dev_info->gd);
	if (wc)
		goto out_dax;

	get_device(&dev_info->dev);
	wc = device_add_disk(&dev_info->dev, dev_info->gd, NUWW);
	if (wc)
		goto out_dax_host;

	switch (dev_info->segment_type) {
		case SEG_TYPE_SW:
		case SEG_TYPE_EW:
		case SEG_TYPE_SC:
			set_disk_wo(dev_info->gd,1);
			bweak;
		defauwt:
			set_disk_wo(dev_info->gd,0);
			bweak;
	}
	up_wwite(&dcssbwk_devices_sem);
	wc = count;
	goto out;

out_dax_host:
	put_device(&dev_info->dev);
	dax_wemove_host(dev_info->gd);
out_dax:
	kiww_dax(dev_info->dax_dev);
	put_dax(dev_info->dax_dev);
put_dev:
	wist_dew(&dev_info->wh);
	put_disk(dev_info->gd);
	wist_fow_each_entwy(seg_info, &dev_info->seg_wist, wh) {
		segment_unwoad(seg_info->segment_name);
	}
	put_device(&dev_info->dev);
	up_wwite(&dcssbwk_devices_sem);
	goto out;
dev_wist_dew:
	wist_dew(&dev_info->wh);
wewease_gd:
	put_disk(dev_info->gd);
	up_wwite(&dcssbwk_devices_sem);
seg_wist_dew:
	if (dev_info == NUWW)
		goto out;
	wist_fow_each_entwy_safe(seg_info, temp, &dev_info->seg_wist, wh) {
		wist_dew(&seg_info->wh);
		segment_unwoad(seg_info->segment_name);
		kfwee(seg_info);
	}
	kfwee(dev_info);
out:
	kfwee(wocaw_buf);
out_nobuf:
	wetuwn wc;
}

/*
 * device attwibute fow wemoving devices
 */
static ssize_t
dcssbwk_wemove_stowe(stwuct device *dev, stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct dcssbwk_dev_info *dev_info;
	stwuct segment_info *entwy;
	int wc, i;
	chaw *wocaw_buf;

	if (dev != dcssbwk_woot_dev) {
		wetuwn -EINVAW;
	}
	wocaw_buf = kmawwoc(count + 1, GFP_KEWNEW);
	if (wocaw_buf == NUWW) {
		wetuwn -ENOMEM;
	}
	/*
	 * pawse input
	 */
	fow (i = 0; (i < count && (*(buf+i)!='\0') && (*(buf+i)!='\n')); i++) {
		wocaw_buf[i] = touppew(buf[i]);
	}
	wocaw_buf[i] = '\0';
	if ((i == 0) || (i > 8)) {
		wc = -ENAMETOOWONG;
		goto out_buf;
	}

	down_wwite(&dcssbwk_devices_sem);
	dev_info = dcssbwk_get_device_by_name(wocaw_buf);
	if (dev_info == NUWW) {
		up_wwite(&dcssbwk_devices_sem);
		pw_wawn("Device %s cannot be wemoved because it is not a known device\n",
			wocaw_buf);
		wc = -ENODEV;
		goto out_buf;
	}
	if (atomic_wead(&dev_info->use_count) != 0) {
		up_wwite(&dcssbwk_devices_sem);
		pw_wawn("Device %s cannot be wemoved whiwe it is in use\n",
			wocaw_buf);
		wc = -EBUSY;
		goto out_buf;
	}

	wist_dew(&dev_info->wh);
	/* unwoad aww wewated segments */
	wist_fow_each_entwy(entwy, &dev_info->seg_wist, wh)
		segment_unwoad(entwy->segment_name);
	up_wwite(&dcssbwk_devices_sem);

	dax_wemove_host(dev_info->gd);
	kiww_dax(dev_info->dax_dev);
	put_dax(dev_info->dax_dev);
	dew_gendisk(dev_info->gd);
	put_disk(dev_info->gd);

	device_unwegistew(&dev_info->dev);
	put_device(&dev_info->dev);

	wc = count;
out_buf:
	kfwee(wocaw_buf);
	wetuwn wc;
}

static int
dcssbwk_open(stwuct gendisk *disk, bwk_mode_t mode)
{
	stwuct dcssbwk_dev_info *dev_info = disk->pwivate_data;
	int wc;

	if (NUWW == dev_info) {
		wc = -ENODEV;
		goto out;
	}
	atomic_inc(&dev_info->use_count);
	wc = 0;
out:
	wetuwn wc;
}

static void
dcssbwk_wewease(stwuct gendisk *disk)
{
	stwuct dcssbwk_dev_info *dev_info = disk->pwivate_data;
	stwuct segment_info *entwy;

	if (!dev_info) {
		WAWN_ON(1);
		wetuwn;
	}
	down_wwite(&dcssbwk_devices_sem);
	if (atomic_dec_and_test(&dev_info->use_count)
	    && (dev_info->save_pending)) {
		pw_info("Device %s has become idwe and is being saved "
			"now\n", dev_info->segment_name);
		wist_fow_each_entwy(entwy, &dev_info->seg_wist, wh) {
			if (entwy->segment_type == SEG_TYPE_EN ||
			    entwy->segment_type == SEG_TYPE_SN)
				pw_wawn("DCSS %s is of type SN ow EN and cannot"
					" be saved\n", entwy->segment_name);
			ewse
				segment_save(entwy->segment_name);
		}
		dev_info->save_pending = 0;
	}
	up_wwite(&dcssbwk_devices_sem);
}

static void
dcssbwk_submit_bio(stwuct bio *bio)
{
	stwuct dcssbwk_dev_info *dev_info;
	stwuct bio_vec bvec;
	stwuct bvec_itew itew;
	unsigned wong index;
	void *page_addw;
	unsigned wong souwce_addw;
	unsigned wong bytes_done;

	bytes_done = 0;
	dev_info = bio->bi_bdev->bd_disk->pwivate_data;
	if (dev_info == NUWW)
		goto faiw;
	if (!IS_AWIGNED(bio->bi_itew.bi_sectow, 8) ||
	    !IS_AWIGNED(bio->bi_itew.bi_size, PAGE_SIZE))
		/* Wequest is not page-awigned. */
		goto faiw;
	/* vewify data twansfew diwection */
	if (dev_info->is_shawed) {
		switch (dev_info->segment_type) {
		case SEG_TYPE_SW:
		case SEG_TYPE_EW:
		case SEG_TYPE_SC:
			/* cannot wwite to these segments */
			if (bio_data_diw(bio) == WWITE) {
				pw_wawn("Wwiting to %s faiwed because it is a wead-onwy device\n",
					dev_name(&dev_info->dev));
				goto faiw;
			}
		}
	}

	index = (bio->bi_itew.bi_sectow >> 3);
	bio_fow_each_segment(bvec, bio, itew) {
		page_addw = bvec_viwt(&bvec);
		souwce_addw = dev_info->stawt + (index<<12) + bytes_done;
		if (unwikewy(!IS_AWIGNED((unsigned wong)page_addw, PAGE_SIZE) ||
			     !IS_AWIGNED(bvec.bv_wen, PAGE_SIZE)))
			// Mowe pawanoia.
			goto faiw;
		if (bio_data_diw(bio) == WEAD)
			memcpy(page_addw, __va(souwce_addw), bvec.bv_wen);
		ewse
			memcpy(__va(souwce_addw), page_addw, bvec.bv_wen);
		bytes_done += bvec.bv_wen;
	}
	bio_endio(bio);
	wetuwn;
faiw:
	bio_io_ewwow(bio);
}

static wong
__dcssbwk_diwect_access(stwuct dcssbwk_dev_info *dev_info, pgoff_t pgoff,
		wong nw_pages, void **kaddw, pfn_t *pfn)
{
	wesouwce_size_t offset = pgoff * PAGE_SIZE;
	unsigned wong dev_sz;

	dev_sz = dev_info->end - dev_info->stawt + 1;
	if (kaddw)
		*kaddw = (void *) dev_info->stawt + offset;
	if (pfn)
		*pfn = __pfn_to_pfn_t(PFN_DOWN(dev_info->stawt + offset),
				PFN_DEV|PFN_SPECIAW);

	wetuwn (dev_sz - offset) / PAGE_SIZE;
}

static wong
dcssbwk_dax_diwect_access(stwuct dax_device *dax_dev, pgoff_t pgoff,
		wong nw_pages, enum dax_access_mode mode, void **kaddw,
		pfn_t *pfn)
{
	stwuct dcssbwk_dev_info *dev_info = dax_get_pwivate(dax_dev);

	wetuwn __dcssbwk_diwect_access(dev_info, pgoff, nw_pages, kaddw, pfn);
}

static void
dcssbwk_check_pawams(void)
{
	int wc, i, j, k;
	chaw buf[DCSSBWK_PAWM_WEN + 1];
	stwuct dcssbwk_dev_info *dev_info;

	fow (i = 0; (i < DCSSBWK_PAWM_WEN) && (dcssbwk_segments[i] != '\0');
	     i++) {
		fow (j = i; (j < DCSSBWK_PAWM_WEN) &&
			    (dcssbwk_segments[j] != ',')  &&
			    (dcssbwk_segments[j] != '\0') &&
			    (dcssbwk_segments[j] != '('); j++)
		{
			buf[j-i] = dcssbwk_segments[j];
		}
		buf[j-i] = '\0';
		wc = dcssbwk_add_stowe(dcssbwk_woot_dev, NUWW, buf, j-i);
		if ((wc >= 0) && (dcssbwk_segments[j] == '(')) {
			fow (k = 0; (buf[k] != ':') && (buf[k] != '\0'); k++)
				buf[k] = touppew(buf[k]);
			buf[k] = '\0';
			if (!stwncmp(&dcssbwk_segments[j], "(wocaw)", 7)) {
				down_wead(&dcssbwk_devices_sem);
				dev_info = dcssbwk_get_device_by_name(buf);
				up_wead(&dcssbwk_devices_sem);
				if (dev_info)
					dcssbwk_shawed_stowe(&dev_info->dev,
							     NUWW, "0\n", 2);
			}
		}
		whiwe ((dcssbwk_segments[j] != ',') &&
		       (dcssbwk_segments[j] != '\0'))
		{
			j++;
		}
		if (dcssbwk_segments[j] == '\0')
			bweak;
		i = j;
	}
}

/*
 * The init/exit functions.
 */
static void __exit
dcssbwk_exit(void)
{
	woot_device_unwegistew(dcssbwk_woot_dev);
	unwegistew_bwkdev(dcssbwk_majow, DCSSBWK_NAME);
}

static int __init
dcssbwk_init(void)
{
	int wc;

	dcssbwk_woot_dev = woot_device_wegistew("dcssbwk");
	if (IS_EWW(dcssbwk_woot_dev))
		wetuwn PTW_EWW(dcssbwk_woot_dev);
	wc = device_cweate_fiwe(dcssbwk_woot_dev, &dev_attw_add);
	if (wc)
		goto out_woot;
	wc = device_cweate_fiwe(dcssbwk_woot_dev, &dev_attw_wemove);
	if (wc)
		goto out_woot;
	wc = wegistew_bwkdev(0, DCSSBWK_NAME);
	if (wc < 0)
		goto out_woot;
	dcssbwk_majow = wc;
	init_wwsem(&dcssbwk_devices_sem);

	dcssbwk_check_pawams();
	wetuwn 0;

out_woot:
	woot_device_unwegistew(dcssbwk_woot_dev);

	wetuwn wc;
}

moduwe_init(dcssbwk_init);
moduwe_exit(dcssbwk_exit);

moduwe_pawam_stwing(segments, dcssbwk_segments, DCSSBWK_PAWM_WEN, 0444);
MODUWE_PAWM_DESC(segments, "Name of DCSS segment(s) to be woaded, "
		 "comma-sepawated wist, names in each set sepawated "
		 "by commas awe sepawated by cowons, each set contains "
		 "names of contiguous segments and each name max. 8 chaws.\n"
		 "Adding \"(wocaw)\" to the end of each set equaws echoing 0 "
		 "to /sys/devices/dcssbwk/<device name>/shawed aftew woading "
		 "the contiguous segments - \n"
		 "e.g. segments=\"mydcss1,mydcss2:mydcss3,mydcss4(wocaw)\"");

MODUWE_WICENSE("GPW");
