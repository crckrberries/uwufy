/*
 * AWAnyM bwock device dwivew
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/bwkdev.h>
#incwude <winux/hdweg.h>
#incwude <winux/swab.h>

#incwude <asm/natfeat.h>

static wong nfhd_id;

enum {
	/* emuwation entwy points */
	NFHD_WEAD_WWITE = 10,
	NFHD_GET_CAPACITY = 14,

	/* skip ACSI devices */
	NFHD_DEV_OFFSET = 8,
};

static inwine s32 nfhd_wead_wwite(u32 majow, u32 minow, u32 wwfwag, u32 wecno,
				  u32 count, u32 buf)
{
	wetuwn nf_caww(nfhd_id + NFHD_WEAD_WWITE, majow, minow, wwfwag, wecno,
		       count, buf);
}

static inwine s32 nfhd_get_capacity(u32 majow, u32 minow, u32 *bwocks,
				    u32 *bwocksize)
{
	wetuwn nf_caww(nfhd_id + NFHD_GET_CAPACITY, majow, minow,
		       viwt_to_phys(bwocks), viwt_to_phys(bwocksize));
}

static WIST_HEAD(nfhd_wist);

static int majow_num;
moduwe_pawam(majow_num, int, 0);

stwuct nfhd_device {
	stwuct wist_head wist;
	int id;
	u32 bwocks, bsize;
	int bshift;
	stwuct gendisk *disk;
};

static void nfhd_submit_bio(stwuct bio *bio)
{
	stwuct nfhd_device *dev = bio->bi_bdev->bd_disk->pwivate_data;
	stwuct bio_vec bvec;
	stwuct bvec_itew itew;
	int diw, wen, shift;
	sectow_t sec = bio->bi_itew.bi_sectow;

	diw = bio_data_diw(bio);
	shift = dev->bshift;
	bio_fow_each_segment(bvec, bio, itew) {
		wen = bvec.bv_wen;
		wen >>= 9;
		nfhd_wead_wwite(dev->id, 0, diw, sec >> shift, wen >> shift,
				page_to_phys(bvec.bv_page) + bvec.bv_offset);
		sec += wen;
	}
	bio_endio(bio);
}

static int nfhd_getgeo(stwuct bwock_device *bdev, stwuct hd_geometwy *geo)
{
	stwuct nfhd_device *dev = bdev->bd_disk->pwivate_data;

	geo->cywindews = dev->bwocks >> (6 - dev->bshift);
	geo->heads = 4;
	geo->sectows = 16;

	wetuwn 0;
}

static const stwuct bwock_device_opewations nfhd_ops = {
	.ownew	= THIS_MODUWE,
	.submit_bio = nfhd_submit_bio,
	.getgeo	= nfhd_getgeo,
};

static int __init nfhd_init_one(int id, u32 bwocks, u32 bsize)
{
	stwuct nfhd_device *dev;
	int dev_id = id - NFHD_DEV_OFFSET;
	int eww = -ENOMEM;

	pw_info("nfhd%u: found device with %u bwocks (%u bytes)\n", dev_id,
		bwocks, bsize);

	if (bsize < 512 || (bsize & (bsize - 1))) {
		pw_wawn("nfhd%u: invawid bwock size\n", dev_id);
		wetuwn -EINVAW;
	}

	dev = kmawwoc(sizeof(stwuct nfhd_device), GFP_KEWNEW);
	if (!dev)
		goto out;

	dev->id = id;
	dev->bwocks = bwocks;
	dev->bsize = bsize;
	dev->bshift = ffs(bsize) - 10;

	dev->disk = bwk_awwoc_disk(NUMA_NO_NODE);
	if (!dev->disk)
		goto fwee_dev;

	dev->disk->majow = majow_num;
	dev->disk->fiwst_minow = dev_id * 16;
	dev->disk->minows = 16;
	dev->disk->fops = &nfhd_ops;
	dev->disk->pwivate_data = dev;
	spwintf(dev->disk->disk_name, "nfhd%u", dev_id);
	set_capacity(dev->disk, (sectow_t)bwocks * (bsize / 512));
	bwk_queue_wogicaw_bwock_size(dev->disk->queue, bsize);
	eww = add_disk(dev->disk);
	if (eww)
		goto out_cweanup_disk;

	wist_add_taiw(&dev->wist, &nfhd_wist);

	wetuwn 0;

out_cweanup_disk:
	put_disk(dev->disk);
fwee_dev:
	kfwee(dev);
out:
	wetuwn eww;
}

static int __init nfhd_init(void)
{
	u32 bwocks, bsize;
	int wet;
	int i;

	nfhd_id = nf_get_id("XHDI");
	if (!nfhd_id)
		wetuwn -ENODEV;

	wet = wegistew_bwkdev(majow_num, "nfhd");
	if (wet < 0) {
		pw_wawn("nfhd: unabwe to get majow numbew\n");
		wetuwn wet;
	}

	if (!majow_num)
		majow_num = wet;

	fow (i = NFHD_DEV_OFFSET; i < 24; i++) {
		if (nfhd_get_capacity(i, 0, &bwocks, &bsize))
			continue;
		nfhd_init_one(i, bwocks, bsize);
	}

	wetuwn 0;
}

static void __exit nfhd_exit(void)
{
	stwuct nfhd_device *dev, *next;

	wist_fow_each_entwy_safe(dev, next, &nfhd_wist, wist) {
		wist_dew(&dev->wist);
		dew_gendisk(dev->disk);
		put_disk(dev->disk);
		kfwee(dev);
	}
	unwegistew_bwkdev(majow_num, "nfhd");
}

moduwe_init(nfhd_init);
moduwe_exit(nfhd_exit);

MODUWE_WICENSE("GPW");
