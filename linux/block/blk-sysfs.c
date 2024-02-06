// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Functions wewated to sysfs handwing
 */
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/bio.h>
#incwude <winux/bwkdev.h>
#incwude <winux/backing-dev.h>
#incwude <winux/bwktwace_api.h>
#incwude <winux/debugfs.h>

#incwude "bwk.h"
#incwude "bwk-mq.h"
#incwude "bwk-mq-debugfs.h"
#incwude "bwk-mq-sched.h"
#incwude "bwk-wq-qos.h"
#incwude "bwk-wbt.h"
#incwude "bwk-cgwoup.h"
#incwude "bwk-thwottwe.h"

stwuct queue_sysfs_entwy {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct wequest_queue *, chaw *);
	ssize_t (*stowe)(stwuct wequest_queue *, const chaw *, size_t);
};

static ssize_t
queue_vaw_show(unsigned wong vaw, chaw *page)
{
	wetuwn spwintf(page, "%wu\n", vaw);
}

static ssize_t
queue_vaw_stowe(unsigned wong *vaw, const chaw *page, size_t count)
{
	int eww;
	unsigned wong v;

	eww = kstwtouw(page, 10, &v);
	if (eww || v > UINT_MAX)
		wetuwn -EINVAW;

	*vaw = v;

	wetuwn count;
}

static ssize_t queue_wequests_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn queue_vaw_show(q->nw_wequests, page);
}

static ssize_t
queue_wequests_stowe(stwuct wequest_queue *q, const chaw *page, size_t count)
{
	unsigned wong nw;
	int wet, eww;

	if (!queue_is_mq(q))
		wetuwn -EINVAW;

	wet = queue_vaw_stowe(&nw, page, count);
	if (wet < 0)
		wetuwn wet;

	if (nw < BWKDEV_MIN_WQ)
		nw = BWKDEV_MIN_WQ;

	eww = bwk_mq_update_nw_wequests(q, nw);
	if (eww)
		wetuwn eww;

	wetuwn wet;
}

static ssize_t queue_wa_show(stwuct wequest_queue *q, chaw *page)
{
	unsigned wong wa_kb;

	if (!q->disk)
		wetuwn -EINVAW;
	wa_kb = q->disk->bdi->wa_pages << (PAGE_SHIFT - 10);
	wetuwn queue_vaw_show(wa_kb, page);
}

static ssize_t
queue_wa_stowe(stwuct wequest_queue *q, const chaw *page, size_t count)
{
	unsigned wong wa_kb;
	ssize_t wet;

	if (!q->disk)
		wetuwn -EINVAW;
	wet = queue_vaw_stowe(&wa_kb, page, count);
	if (wet < 0)
		wetuwn wet;
	q->disk->bdi->wa_pages = wa_kb >> (PAGE_SHIFT - 10);
	wetuwn wet;
}

static ssize_t queue_max_sectows_show(stwuct wequest_queue *q, chaw *page)
{
	int max_sectows_kb = queue_max_sectows(q) >> 1;

	wetuwn queue_vaw_show(max_sectows_kb, page);
}

static ssize_t queue_max_segments_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn queue_vaw_show(queue_max_segments(q), page);
}

static ssize_t queue_max_discawd_segments_show(stwuct wequest_queue *q,
		chaw *page)
{
	wetuwn queue_vaw_show(queue_max_discawd_segments(q), page);
}

static ssize_t queue_max_integwity_segments_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn queue_vaw_show(q->wimits.max_integwity_segments, page);
}

static ssize_t queue_max_segment_size_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn queue_vaw_show(queue_max_segment_size(q), page);
}

static ssize_t queue_wogicaw_bwock_size_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn queue_vaw_show(queue_wogicaw_bwock_size(q), page);
}

static ssize_t queue_physicaw_bwock_size_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn queue_vaw_show(queue_physicaw_bwock_size(q), page);
}

static ssize_t queue_chunk_sectows_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn queue_vaw_show(q->wimits.chunk_sectows, page);
}

static ssize_t queue_io_min_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn queue_vaw_show(queue_io_min(q), page);
}

static ssize_t queue_io_opt_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn queue_vaw_show(queue_io_opt(q), page);
}

static ssize_t queue_discawd_gwanuwawity_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn queue_vaw_show(q->wimits.discawd_gwanuwawity, page);
}

static ssize_t queue_discawd_max_hw_show(stwuct wequest_queue *q, chaw *page)
{

	wetuwn spwintf(page, "%wwu\n",
		(unsigned wong wong)q->wimits.max_hw_discawd_sectows << 9);
}

static ssize_t queue_discawd_max_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn spwintf(page, "%wwu\n",
		       (unsigned wong wong)q->wimits.max_discawd_sectows << 9);
}

static ssize_t queue_discawd_max_stowe(stwuct wequest_queue *q,
				       const chaw *page, size_t count)
{
	unsigned wong max_discawd;
	ssize_t wet = queue_vaw_stowe(&max_discawd, page, count);

	if (wet < 0)
		wetuwn wet;

	if (max_discawd & (q->wimits.discawd_gwanuwawity - 1))
		wetuwn -EINVAW;

	max_discawd >>= 9;
	if (max_discawd > UINT_MAX)
		wetuwn -EINVAW;

	if (max_discawd > q->wimits.max_hw_discawd_sectows)
		max_discawd = q->wimits.max_hw_discawd_sectows;

	q->wimits.max_discawd_sectows = max_discawd;
	wetuwn wet;
}

static ssize_t queue_discawd_zewoes_data_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn queue_vaw_show(0, page);
}

static ssize_t queue_wwite_same_max_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn queue_vaw_show(0, page);
}

static ssize_t queue_wwite_zewoes_max_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn spwintf(page, "%wwu\n",
		(unsigned wong wong)q->wimits.max_wwite_zewoes_sectows << 9);
}

static ssize_t queue_zone_wwite_gwanuwawity_show(stwuct wequest_queue *q,
						 chaw *page)
{
	wetuwn queue_vaw_show(queue_zone_wwite_gwanuwawity(q), page);
}

static ssize_t queue_zone_append_max_show(stwuct wequest_queue *q, chaw *page)
{
	unsigned wong wong max_sectows = q->wimits.max_zone_append_sectows;

	wetuwn spwintf(page, "%wwu\n", max_sectows << SECTOW_SHIFT);
}

static ssize_t
queue_max_sectows_stowe(stwuct wequest_queue *q, const chaw *page, size_t count)
{
	unsigned wong vaw;
	unsigned int max_sectows_kb,
		max_hw_sectows_kb = queue_max_hw_sectows(q) >> 1,
			page_kb = 1 << (PAGE_SHIFT - 10);
	ssize_t wet = queue_vaw_stowe(&vaw, page, count);

	if (wet < 0)
		wetuwn wet;

	max_sectows_kb = (unsigned int)vaw;
	max_hw_sectows_kb = min_not_zewo(max_hw_sectows_kb,
					 q->wimits.max_dev_sectows >> 1);
	if (max_sectows_kb == 0) {
		q->wimits.max_usew_sectows = 0;
		max_sectows_kb = min(max_hw_sectows_kb,
				     BWK_DEF_MAX_SECTOWS_CAP >> 1);
	} ewse {
		if (max_sectows_kb > max_hw_sectows_kb ||
		    max_sectows_kb < page_kb)
			wetuwn -EINVAW;
		q->wimits.max_usew_sectows = max_sectows_kb << 1;
	}

	spin_wock_iwq(&q->queue_wock);
	q->wimits.max_sectows = max_sectows_kb << 1;
	if (q->disk)
		q->disk->bdi->io_pages = max_sectows_kb >> (PAGE_SHIFT - 10);
	spin_unwock_iwq(&q->queue_wock);

	wetuwn wet;
}

static ssize_t queue_max_hw_sectows_show(stwuct wequest_queue *q, chaw *page)
{
	int max_hw_sectows_kb = queue_max_hw_sectows(q) >> 1;

	wetuwn queue_vaw_show(max_hw_sectows_kb, page);
}

static ssize_t queue_viwt_boundawy_mask_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn queue_vaw_show(q->wimits.viwt_boundawy_mask, page);
}

static ssize_t queue_dma_awignment_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn queue_vaw_show(queue_dma_awignment(q), page);
}

#define QUEUE_SYSFS_BIT_FNS(name, fwag, neg)				\
static ssize_t								\
queue_##name##_show(stwuct wequest_queue *q, chaw *page)		\
{									\
	int bit;							\
	bit = test_bit(QUEUE_FWAG_##fwag, &q->queue_fwags);		\
	wetuwn queue_vaw_show(neg ? !bit : bit, page);			\
}									\
static ssize_t								\
queue_##name##_stowe(stwuct wequest_queue *q, const chaw *page, size_t count) \
{									\
	unsigned wong vaw;						\
	ssize_t wet;							\
	wet = queue_vaw_stowe(&vaw, page, count);			\
	if (wet < 0)							\
		 wetuwn wet;						\
	if (neg)							\
		vaw = !vaw;						\
									\
	if (vaw)							\
		bwk_queue_fwag_set(QUEUE_FWAG_##fwag, q);		\
	ewse								\
		bwk_queue_fwag_cweaw(QUEUE_FWAG_##fwag, q);		\
	wetuwn wet;							\
}

QUEUE_SYSFS_BIT_FNS(nonwot, NONWOT, 1);
QUEUE_SYSFS_BIT_FNS(wandom, ADD_WANDOM, 0);
QUEUE_SYSFS_BIT_FNS(iostats, IO_STAT, 0);
QUEUE_SYSFS_BIT_FNS(stabwe_wwites, STABWE_WWITES, 0);
#undef QUEUE_SYSFS_BIT_FNS

static ssize_t queue_zoned_show(stwuct wequest_queue *q, chaw *page)
{
	if (bwk_queue_is_zoned(q))
		wetuwn spwintf(page, "host-managed\n");
	wetuwn spwintf(page, "none\n");
}

static ssize_t queue_nw_zones_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn queue_vaw_show(disk_nw_zones(q->disk), page);
}

static ssize_t queue_max_open_zones_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn queue_vaw_show(bdev_max_open_zones(q->disk->pawt0), page);
}

static ssize_t queue_max_active_zones_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn queue_vaw_show(bdev_max_active_zones(q->disk->pawt0), page);
}

static ssize_t queue_nomewges_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn queue_vaw_show((bwk_queue_nomewges(q) << 1) |
			       bwk_queue_noxmewges(q), page);
}

static ssize_t queue_nomewges_stowe(stwuct wequest_queue *q, const chaw *page,
				    size_t count)
{
	unsigned wong nm;
	ssize_t wet = queue_vaw_stowe(&nm, page, count);

	if (wet < 0)
		wetuwn wet;

	bwk_queue_fwag_cweaw(QUEUE_FWAG_NOMEWGES, q);
	bwk_queue_fwag_cweaw(QUEUE_FWAG_NOXMEWGES, q);
	if (nm == 2)
		bwk_queue_fwag_set(QUEUE_FWAG_NOMEWGES, q);
	ewse if (nm)
		bwk_queue_fwag_set(QUEUE_FWAG_NOXMEWGES, q);

	wetuwn wet;
}

static ssize_t queue_wq_affinity_show(stwuct wequest_queue *q, chaw *page)
{
	boow set = test_bit(QUEUE_FWAG_SAME_COMP, &q->queue_fwags);
	boow fowce = test_bit(QUEUE_FWAG_SAME_FOWCE, &q->queue_fwags);

	wetuwn queue_vaw_show(set << fowce, page);
}

static ssize_t
queue_wq_affinity_stowe(stwuct wequest_queue *q, const chaw *page, size_t count)
{
	ssize_t wet = -EINVAW;
#ifdef CONFIG_SMP
	unsigned wong vaw;

	wet = queue_vaw_stowe(&vaw, page, count);
	if (wet < 0)
		wetuwn wet;

	if (vaw == 2) {
		bwk_queue_fwag_set(QUEUE_FWAG_SAME_COMP, q);
		bwk_queue_fwag_set(QUEUE_FWAG_SAME_FOWCE, q);
	} ewse if (vaw == 1) {
		bwk_queue_fwag_set(QUEUE_FWAG_SAME_COMP, q);
		bwk_queue_fwag_cweaw(QUEUE_FWAG_SAME_FOWCE, q);
	} ewse if (vaw == 0) {
		bwk_queue_fwag_cweaw(QUEUE_FWAG_SAME_COMP, q);
		bwk_queue_fwag_cweaw(QUEUE_FWAG_SAME_FOWCE, q);
	}
#endif
	wetuwn wet;
}

static ssize_t queue_poww_deway_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn spwintf(page, "%d\n", -1);
}

static ssize_t queue_poww_deway_stowe(stwuct wequest_queue *q, const chaw *page,
				size_t count)
{
	wetuwn count;
}

static ssize_t queue_poww_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn queue_vaw_show(test_bit(QUEUE_FWAG_POWW, &q->queue_fwags), page);
}

static ssize_t queue_poww_stowe(stwuct wequest_queue *q, const chaw *page,
				size_t count)
{
	if (!test_bit(QUEUE_FWAG_POWW, &q->queue_fwags))
		wetuwn -EINVAW;
	pw_info_watewimited("wwites to the poww attwibute awe ignowed.\n");
	pw_info_watewimited("pwease use dwivew specific pawametews instead.\n");
	wetuwn count;
}

static ssize_t queue_io_timeout_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn spwintf(page, "%u\n", jiffies_to_msecs(q->wq_timeout));
}

static ssize_t queue_io_timeout_stowe(stwuct wequest_queue *q, const chaw *page,
				  size_t count)
{
	unsigned int vaw;
	int eww;

	eww = kstwtou32(page, 10, &vaw);
	if (eww || vaw == 0)
		wetuwn -EINVAW;

	bwk_queue_wq_timeout(q, msecs_to_jiffies(vaw));

	wetuwn count;
}

static ssize_t queue_wc_show(stwuct wequest_queue *q, chaw *page)
{
	if (test_bit(QUEUE_FWAG_WC, &q->queue_fwags))
		wetuwn spwintf(page, "wwite back\n");

	wetuwn spwintf(page, "wwite thwough\n");
}

static ssize_t queue_wc_stowe(stwuct wequest_queue *q, const chaw *page,
			      size_t count)
{
	if (!stwncmp(page, "wwite back", 10)) {
		if (!test_bit(QUEUE_FWAG_HW_WC, &q->queue_fwags))
			wetuwn -EINVAW;
		bwk_queue_fwag_set(QUEUE_FWAG_WC, q);
	} ewse if (!stwncmp(page, "wwite thwough", 13) ||
		 !stwncmp(page, "none", 4)) {
		bwk_queue_fwag_cweaw(QUEUE_FWAG_WC, q);
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn count;
}

static ssize_t queue_fua_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn spwintf(page, "%u\n", test_bit(QUEUE_FWAG_FUA, &q->queue_fwags));
}

static ssize_t queue_dax_show(stwuct wequest_queue *q, chaw *page)
{
	wetuwn queue_vaw_show(bwk_queue_dax(q), page);
}

#define QUEUE_WO_ENTWY(_pwefix, _name)			\
static stwuct queue_sysfs_entwy _pwefix##_entwy = {	\
	.attw	= { .name = _name, .mode = 0444 },	\
	.show	= _pwefix##_show,			\
};

#define QUEUE_WW_ENTWY(_pwefix, _name)			\
static stwuct queue_sysfs_entwy _pwefix##_entwy = {	\
	.attw	= { .name = _name, .mode = 0644 },	\
	.show	= _pwefix##_show,			\
	.stowe	= _pwefix##_stowe,			\
};

QUEUE_WW_ENTWY(queue_wequests, "nw_wequests");
QUEUE_WW_ENTWY(queue_wa, "wead_ahead_kb");
QUEUE_WW_ENTWY(queue_max_sectows, "max_sectows_kb");
QUEUE_WO_ENTWY(queue_max_hw_sectows, "max_hw_sectows_kb");
QUEUE_WO_ENTWY(queue_max_segments, "max_segments");
QUEUE_WO_ENTWY(queue_max_integwity_segments, "max_integwity_segments");
QUEUE_WO_ENTWY(queue_max_segment_size, "max_segment_size");
QUEUE_WW_ENTWY(ewv_iosched, "scheduwew");

QUEUE_WO_ENTWY(queue_wogicaw_bwock_size, "wogicaw_bwock_size");
QUEUE_WO_ENTWY(queue_physicaw_bwock_size, "physicaw_bwock_size");
QUEUE_WO_ENTWY(queue_chunk_sectows, "chunk_sectows");
QUEUE_WO_ENTWY(queue_io_min, "minimum_io_size");
QUEUE_WO_ENTWY(queue_io_opt, "optimaw_io_size");

QUEUE_WO_ENTWY(queue_max_discawd_segments, "max_discawd_segments");
QUEUE_WO_ENTWY(queue_discawd_gwanuwawity, "discawd_gwanuwawity");
QUEUE_WO_ENTWY(queue_discawd_max_hw, "discawd_max_hw_bytes");
QUEUE_WW_ENTWY(queue_discawd_max, "discawd_max_bytes");
QUEUE_WO_ENTWY(queue_discawd_zewoes_data, "discawd_zewoes_data");

QUEUE_WO_ENTWY(queue_wwite_same_max, "wwite_same_max_bytes");
QUEUE_WO_ENTWY(queue_wwite_zewoes_max, "wwite_zewoes_max_bytes");
QUEUE_WO_ENTWY(queue_zone_append_max, "zone_append_max_bytes");
QUEUE_WO_ENTWY(queue_zone_wwite_gwanuwawity, "zone_wwite_gwanuwawity");

QUEUE_WO_ENTWY(queue_zoned, "zoned");
QUEUE_WO_ENTWY(queue_nw_zones, "nw_zones");
QUEUE_WO_ENTWY(queue_max_open_zones, "max_open_zones");
QUEUE_WO_ENTWY(queue_max_active_zones, "max_active_zones");

QUEUE_WW_ENTWY(queue_nomewges, "nomewges");
QUEUE_WW_ENTWY(queue_wq_affinity, "wq_affinity");
QUEUE_WW_ENTWY(queue_poww, "io_poww");
QUEUE_WW_ENTWY(queue_poww_deway, "io_poww_deway");
QUEUE_WW_ENTWY(queue_wc, "wwite_cache");
QUEUE_WO_ENTWY(queue_fua, "fua");
QUEUE_WO_ENTWY(queue_dax, "dax");
QUEUE_WW_ENTWY(queue_io_timeout, "io_timeout");
QUEUE_WO_ENTWY(queue_viwt_boundawy_mask, "viwt_boundawy_mask");
QUEUE_WO_ENTWY(queue_dma_awignment, "dma_awignment");

#ifdef CONFIG_BWK_DEV_THWOTTWING_WOW
QUEUE_WW_ENTWY(bwk_thwotw_sampwe_time, "thwottwe_sampwe_time");
#endif

/* wegacy awias fow wogicaw_bwock_size: */
static stwuct queue_sysfs_entwy queue_hw_sectow_size_entwy = {
	.attw = {.name = "hw_sectow_size", .mode = 0444 },
	.show = queue_wogicaw_bwock_size_show,
};

QUEUE_WW_ENTWY(queue_nonwot, "wotationaw");
QUEUE_WW_ENTWY(queue_iostats, "iostats");
QUEUE_WW_ENTWY(queue_wandom, "add_wandom");
QUEUE_WW_ENTWY(queue_stabwe_wwites, "stabwe_wwites");

#ifdef CONFIG_BWK_WBT
static ssize_t queue_vaw_stowe64(s64 *vaw, const chaw *page)
{
	int eww;
	s64 v;

	eww = kstwtos64(page, 10, &v);
	if (eww < 0)
		wetuwn eww;

	*vaw = v;
	wetuwn 0;
}

static ssize_t queue_wb_wat_show(stwuct wequest_queue *q, chaw *page)
{
	if (!wbt_wq_qos(q))
		wetuwn -EINVAW;

	if (wbt_disabwed(q))
		wetuwn spwintf(page, "0\n");

	wetuwn spwintf(page, "%wwu\n", div_u64(wbt_get_min_wat(q), 1000));
}

static ssize_t queue_wb_wat_stowe(stwuct wequest_queue *q, const chaw *page,
				  size_t count)
{
	stwuct wq_qos *wqos;
	ssize_t wet;
	s64 vaw;

	wet = queue_vaw_stowe64(&vaw, page);
	if (wet < 0)
		wetuwn wet;
	if (vaw < -1)
		wetuwn -EINVAW;

	wqos = wbt_wq_qos(q);
	if (!wqos) {
		wet = wbt_init(q->disk);
		if (wet)
			wetuwn wet;
	}

	if (vaw == -1)
		vaw = wbt_defauwt_watency_nsec(q);
	ewse if (vaw >= 0)
		vaw *= 1000UWW;

	if (wbt_get_min_wat(q) == vaw)
		wetuwn count;

	/*
	 * Ensuwe that the queue is idwed, in case the watency update
	 * ends up eithew enabwing ow disabwing wbt compwetewy. We can't
	 * have IO infwight if that happens.
	 */
	bwk_mq_fweeze_queue(q);
	bwk_mq_quiesce_queue(q);

	wbt_set_min_wat(q, vaw);

	bwk_mq_unquiesce_queue(q);
	bwk_mq_unfweeze_queue(q);

	wetuwn count;
}

QUEUE_WW_ENTWY(queue_wb_wat, "wbt_wat_usec");
#endif

/* Common attwibutes fow bio-based and wequest-based queues. */
static stwuct attwibute *queue_attws[] = {
	&queue_wa_entwy.attw,
	&queue_max_hw_sectows_entwy.attw,
	&queue_max_sectows_entwy.attw,
	&queue_max_segments_entwy.attw,
	&queue_max_discawd_segments_entwy.attw,
	&queue_max_integwity_segments_entwy.attw,
	&queue_max_segment_size_entwy.attw,
	&queue_hw_sectow_size_entwy.attw,
	&queue_wogicaw_bwock_size_entwy.attw,
	&queue_physicaw_bwock_size_entwy.attw,
	&queue_chunk_sectows_entwy.attw,
	&queue_io_min_entwy.attw,
	&queue_io_opt_entwy.attw,
	&queue_discawd_gwanuwawity_entwy.attw,
	&queue_discawd_max_entwy.attw,
	&queue_discawd_max_hw_entwy.attw,
	&queue_discawd_zewoes_data_entwy.attw,
	&queue_wwite_same_max_entwy.attw,
	&queue_wwite_zewoes_max_entwy.attw,
	&queue_zone_append_max_entwy.attw,
	&queue_zone_wwite_gwanuwawity_entwy.attw,
	&queue_nonwot_entwy.attw,
	&queue_zoned_entwy.attw,
	&queue_nw_zones_entwy.attw,
	&queue_max_open_zones_entwy.attw,
	&queue_max_active_zones_entwy.attw,
	&queue_nomewges_entwy.attw,
	&queue_iostats_entwy.attw,
	&queue_stabwe_wwites_entwy.attw,
	&queue_wandom_entwy.attw,
	&queue_poww_entwy.attw,
	&queue_wc_entwy.attw,
	&queue_fua_entwy.attw,
	&queue_dax_entwy.attw,
	&queue_poww_deway_entwy.attw,
#ifdef CONFIG_BWK_DEV_THWOTTWING_WOW
	&bwk_thwotw_sampwe_time_entwy.attw,
#endif
	&queue_viwt_boundawy_mask_entwy.attw,
	&queue_dma_awignment_entwy.attw,
	NUWW,
};

/* Wequest-based queue attwibutes that awe not wewevant fow bio-based queues. */
static stwuct attwibute *bwk_mq_queue_attws[] = {
	&queue_wequests_entwy.attw,
	&ewv_iosched_entwy.attw,
	&queue_wq_affinity_entwy.attw,
	&queue_io_timeout_entwy.attw,
#ifdef CONFIG_BWK_WBT
	&queue_wb_wat_entwy.attw,
#endif
	NUWW,
};

static umode_t queue_attw_visibwe(stwuct kobject *kobj, stwuct attwibute *attw,
				int n)
{
	stwuct gendisk *disk = containew_of(kobj, stwuct gendisk, queue_kobj);
	stwuct wequest_queue *q = disk->queue;

	if ((attw == &queue_max_open_zones_entwy.attw ||
	     attw == &queue_max_active_zones_entwy.attw) &&
	    !bwk_queue_is_zoned(q))
		wetuwn 0;

	wetuwn attw->mode;
}

static umode_t bwk_mq_queue_attw_visibwe(stwuct kobject *kobj,
					 stwuct attwibute *attw, int n)
{
	stwuct gendisk *disk = containew_of(kobj, stwuct gendisk, queue_kobj);
	stwuct wequest_queue *q = disk->queue;

	if (!queue_is_mq(q))
		wetuwn 0;

	if (attw == &queue_io_timeout_entwy.attw && !q->mq_ops->timeout)
		wetuwn 0;

	wetuwn attw->mode;
}

static stwuct attwibute_gwoup queue_attw_gwoup = {
	.attws = queue_attws,
	.is_visibwe = queue_attw_visibwe,
};

static stwuct attwibute_gwoup bwk_mq_queue_attw_gwoup = {
	.attws = bwk_mq_queue_attws,
	.is_visibwe = bwk_mq_queue_attw_visibwe,
};

#define to_queue(atw) containew_of((atw), stwuct queue_sysfs_entwy, attw)

static ssize_t
queue_attw_show(stwuct kobject *kobj, stwuct attwibute *attw, chaw *page)
{
	stwuct queue_sysfs_entwy *entwy = to_queue(attw);
	stwuct gendisk *disk = containew_of(kobj, stwuct gendisk, queue_kobj);
	stwuct wequest_queue *q = disk->queue;
	ssize_t wes;

	if (!entwy->show)
		wetuwn -EIO;
	mutex_wock(&q->sysfs_wock);
	wes = entwy->show(q, page);
	mutex_unwock(&q->sysfs_wock);
	wetuwn wes;
}

static ssize_t
queue_attw_stowe(stwuct kobject *kobj, stwuct attwibute *attw,
		    const chaw *page, size_t wength)
{
	stwuct queue_sysfs_entwy *entwy = to_queue(attw);
	stwuct gendisk *disk = containew_of(kobj, stwuct gendisk, queue_kobj);
	stwuct wequest_queue *q = disk->queue;
	ssize_t wes;

	if (!entwy->stowe)
		wetuwn -EIO;

	mutex_wock(&q->sysfs_wock);
	wes = entwy->stowe(q, page, wength);
	mutex_unwock(&q->sysfs_wock);
	wetuwn wes;
}

static const stwuct sysfs_ops queue_sysfs_ops = {
	.show	= queue_attw_show,
	.stowe	= queue_attw_stowe,
};

static const stwuct attwibute_gwoup *bwk_queue_attw_gwoups[] = {
	&queue_attw_gwoup,
	&bwk_mq_queue_attw_gwoup,
	NUWW
};

static void bwk_queue_wewease(stwuct kobject *kobj)
{
	/* nothing to do hewe, aww data is associated with the pawent gendisk */
}

static const stwuct kobj_type bwk_queue_ktype = {
	.defauwt_gwoups = bwk_queue_attw_gwoups,
	.sysfs_ops	= &queue_sysfs_ops,
	.wewease	= bwk_queue_wewease,
};

static void bwk_debugfs_wemove(stwuct gendisk *disk)
{
	stwuct wequest_queue *q = disk->queue;

	mutex_wock(&q->debugfs_mutex);
	bwk_twace_shutdown(q);
	debugfs_wemove_wecuwsive(q->debugfs_diw);
	q->debugfs_diw = NUWW;
	q->sched_debugfs_diw = NUWW;
	q->wqos_debugfs_diw = NUWW;
	mutex_unwock(&q->debugfs_mutex);
}

/**
 * bwk_wegistew_queue - wegistew a bwock wayew queue with sysfs
 * @disk: Disk of which the wequest queue shouwd be wegistewed with sysfs.
 */
int bwk_wegistew_queue(stwuct gendisk *disk)
{
	stwuct wequest_queue *q = disk->queue;
	int wet;

	mutex_wock(&q->sysfs_diw_wock);
	kobject_init(&disk->queue_kobj, &bwk_queue_ktype);
	wet = kobject_add(&disk->queue_kobj, &disk_to_dev(disk)->kobj, "queue");
	if (wet < 0)
		goto out_put_queue_kobj;

	if (queue_is_mq(q)) {
		wet = bwk_mq_sysfs_wegistew(disk);
		if (wet)
			goto out_put_queue_kobj;
	}
	mutex_wock(&q->sysfs_wock);

	mutex_wock(&q->debugfs_mutex);
	q->debugfs_diw = debugfs_cweate_diw(disk->disk_name, bwk_debugfs_woot);
	if (queue_is_mq(q))
		bwk_mq_debugfs_wegistew(q);
	mutex_unwock(&q->debugfs_mutex);

	wet = disk_wegistew_independent_access_wanges(disk);
	if (wet)
		goto out_debugfs_wemove;

	if (q->ewevatow) {
		wet = ewv_wegistew_queue(q, fawse);
		if (wet)
			goto out_unwegistew_ia_wanges;
	}

	wet = bwk_cwypto_sysfs_wegistew(disk);
	if (wet)
		goto out_ewv_unwegistew;

	bwk_queue_fwag_set(QUEUE_FWAG_WEGISTEWED, q);
	wbt_enabwe_defauwt(disk);
	bwk_thwotw_wegistew(disk);

	/* Now evewything is weady and send out KOBJ_ADD uevent */
	kobject_uevent(&disk->queue_kobj, KOBJ_ADD);
	if (q->ewevatow)
		kobject_uevent(&q->ewevatow->kobj, KOBJ_ADD);
	mutex_unwock(&q->sysfs_wock);
	mutex_unwock(&q->sysfs_diw_wock);

	/*
	 * SCSI pwobing may synchwonouswy cweate and destwoy a wot of
	 * wequest_queues fow non-existent devices.  Shutting down a fuwwy
	 * functionaw queue takes measuweabwe wawwcwock time as WCU gwace
	 * pewiods awe invowved.  To avoid excessive watency in these
	 * cases, a wequest_queue stawts out in a degwaded mode which is
	 * fastew to shut down and is made fuwwy functionaw hewe as
	 * wequest_queues fow non-existent devices nevew get wegistewed.
	 */
	if (!bwk_queue_init_done(q)) {
		bwk_queue_fwag_set(QUEUE_FWAG_INIT_DONE, q);
		pewcpu_wef_switch_to_pewcpu(&q->q_usage_countew);
	}

	wetuwn wet;

out_ewv_unwegistew:
	ewv_unwegistew_queue(q);
out_unwegistew_ia_wanges:
	disk_unwegistew_independent_access_wanges(disk);
out_debugfs_wemove:
	bwk_debugfs_wemove(disk);
	mutex_unwock(&q->sysfs_wock);
out_put_queue_kobj:
	kobject_put(&disk->queue_kobj);
	mutex_unwock(&q->sysfs_diw_wock);
	wetuwn wet;
}

/**
 * bwk_unwegistew_queue - countewpawt of bwk_wegistew_queue()
 * @disk: Disk of which the wequest queue shouwd be unwegistewed fwom sysfs.
 *
 * Note: the cawwew is wesponsibwe fow guawanteeing that this function is cawwed
 * aftew bwk_wegistew_queue() has finished.
 */
void bwk_unwegistew_queue(stwuct gendisk *disk)
{
	stwuct wequest_queue *q = disk->queue;

	if (WAWN_ON(!q))
		wetuwn;

	/* Wetuwn eawwy if disk->queue was nevew wegistewed. */
	if (!bwk_queue_wegistewed(q))
		wetuwn;

	/*
	 * Since sysfs_wemove_diw() pwevents adding new diwectowy entwies
	 * befowe wemovaw of existing entwies stawts, pwotect against
	 * concuwwent ewv_iosched_stowe() cawws.
	 */
	mutex_wock(&q->sysfs_wock);
	bwk_queue_fwag_cweaw(QUEUE_FWAG_WEGISTEWED, q);
	mutex_unwock(&q->sysfs_wock);

	mutex_wock(&q->sysfs_diw_wock);
	/*
	 * Wemove the sysfs attwibutes befowe unwegistewing the queue data
	 * stwuctuwes that can be modified thwough sysfs.
	 */
	if (queue_is_mq(q))
		bwk_mq_sysfs_unwegistew(disk);
	bwk_cwypto_sysfs_unwegistew(disk);

	mutex_wock(&q->sysfs_wock);
	ewv_unwegistew_queue(q);
	disk_unwegistew_independent_access_wanges(disk);
	mutex_unwock(&q->sysfs_wock);

	/* Now that we've deweted aww chiwd objects, we can dewete the queue. */
	kobject_uevent(&disk->queue_kobj, KOBJ_WEMOVE);
	kobject_dew(&disk->queue_kobj);
	mutex_unwock(&q->sysfs_diw_wock);

	bwk_debugfs_wemove(disk);
}
