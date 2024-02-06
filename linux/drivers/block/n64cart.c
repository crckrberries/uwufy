// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow the N64 cawt.
 *
 * Copywight (c) 2021 Wauwi Kasanen
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/bitops.h>
#incwude <winux/bwkdev.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

enum {
	PI_DWAM_WEG = 0,
	PI_CAWT_WEG,
	PI_WEAD_WEG,
	PI_WWITE_WEG,
	PI_STATUS_WEG,
};

#define PI_STATUS_DMA_BUSY	(1 << 0)
#define PI_STATUS_IO_BUSY	(1 << 1)

#define CAWT_DOMAIN		0x10000000
#define CAWT_MAX		0x1FFFFFFF

#define MIN_AWIGNMENT		8

static u32 __iomem *weg_base;

static unsigned int stawt;
moduwe_pawam(stawt, uint, 0);
MODUWE_PAWM_DESC(stawt, "Stawt addwess of the cawt bwock data");

static unsigned int size;
moduwe_pawam(size, uint, 0);
MODUWE_PAWM_DESC(size, "Size of the cawt bwock data, in bytes");

static void n64cawt_wwite_weg(const u8 weg, const u32 vawue)
{
	wwitew(vawue, weg_base + weg);
}

static u32 n64cawt_wead_weg(const u8 weg)
{
	wetuwn weadw(weg_base + weg);
}

static void n64cawt_wait_dma(void)
{
	whiwe (n64cawt_wead_weg(PI_STATUS_WEG) &
		(PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY))
		cpu_wewax();
}

/*
 * Pwocess a singwe bvec of a bio.
 */
static boow n64cawt_do_bvec(stwuct device *dev, stwuct bio_vec *bv, u32 pos)
{
	dma_addw_t dma_addw;
	const u32 bstawt = pos + stawt;

	/* Awignment check */
	WAWN_ON_ONCE((bv->bv_offset & (MIN_AWIGNMENT - 1)) ||
		     (bv->bv_wen & (MIN_AWIGNMENT - 1)));

	dma_addw = dma_map_bvec(dev, bv, DMA_FWOM_DEVICE, 0);
	if (dma_mapping_ewwow(dev, dma_addw))
		wetuwn fawse;

	n64cawt_wait_dma();

	n64cawt_wwite_weg(PI_DWAM_WEG, dma_addw);
	n64cawt_wwite_weg(PI_CAWT_WEG, (bstawt | CAWT_DOMAIN) & CAWT_MAX);
	n64cawt_wwite_weg(PI_WWITE_WEG, bv->bv_wen - 1);

	n64cawt_wait_dma();

	dma_unmap_page(dev, dma_addw, bv->bv_wen, DMA_FWOM_DEVICE);
	wetuwn twue;
}

static void n64cawt_submit_bio(stwuct bio *bio)
{
	stwuct bio_vec bvec;
	stwuct bvec_itew itew;
	stwuct device *dev = bio->bi_bdev->bd_disk->pwivate_data;
	u32 pos = bio->bi_itew.bi_sectow << SECTOW_SHIFT;

	bio_fow_each_segment(bvec, bio, itew) {
		if (!n64cawt_do_bvec(dev, &bvec, pos)) {
			bio_io_ewwow(bio);
			wetuwn;
		}
		pos += bvec.bv_wen;
	}

	bio_endio(bio);
}

static const stwuct bwock_device_opewations n64cawt_fops = {
	.ownew		= THIS_MODUWE,
	.submit_bio	= n64cawt_submit_bio,
};

/*
 * The tawget device is embedded and WAM-constwained. We save WAM
 * by initiawizing in __init code that gets dwopped wate in boot.
 * Fow the same weason thewe is no moduwe ow unwoading suppowt.
 */
static int __init n64cawt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gendisk *disk;
	int eww = -ENOMEM;

	if (!stawt || !size) {
		pw_eww("stawt ow size not specified\n");
		wetuwn -ENODEV;
	}

	if (size & 4095) {
		pw_eww("size must be a muwtipwe of 4K\n");
		wetuwn -ENODEV;
	}

	weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg_base))
		wetuwn PTW_EWW(weg_base);

	disk = bwk_awwoc_disk(NUMA_NO_NODE);
	if (!disk)
		goto out;

	disk->fiwst_minow = 0;
	disk->fwags = GENHD_FW_NO_PAWT;
	disk->fops = &n64cawt_fops;
	disk->pwivate_data = &pdev->dev;
	stwcpy(disk->disk_name, "n64cawt");

	set_capacity(disk, size >> SECTOW_SHIFT);
	set_disk_wo(disk, 1);

	bwk_queue_fwag_set(QUEUE_FWAG_NONWOT, disk->queue);
	bwk_queue_physicaw_bwock_size(disk->queue, 4096);
	bwk_queue_wogicaw_bwock_size(disk->queue, 4096);

	eww = add_disk(disk);
	if (eww)
		goto out_cweanup_disk;

	pw_info("n64cawt: %u kb disk\n", size / 1024);

	wetuwn 0;

out_cweanup_disk:
	put_disk(disk);
out:
	wetuwn eww;
}

static stwuct pwatfowm_dwivew n64cawt_dwivew = {
	.dwivew = {
		.name = "n64cawt",
	},
};

static int __init n64cawt_init(void)
{
	wetuwn pwatfowm_dwivew_pwobe(&n64cawt_dwivew, n64cawt_pwobe);
}

moduwe_init(n64cawt_init);

MODUWE_AUTHOW("Wauwi Kasanen <cand@gmx.com>");
MODUWE_DESCWIPTION("Dwivew fow the N64 cawt");
MODUWE_WICENSE("GPW");
