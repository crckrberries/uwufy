// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Functions wewated to setting vawious queue pwopewties fwom dwivews
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/bio.h>
#incwude <winux/bwkdev.h>
#incwude <winux/pagemap.h>
#incwude <winux/backing-dev-defs.h>
#incwude <winux/gcd.h>
#incwude <winux/wcm.h>
#incwude <winux/jiffies.h>
#incwude <winux/gfp.h>
#incwude <winux/dma-mapping.h>

#incwude "bwk.h"
#incwude "bwk-wq-qos.h"
#incwude "bwk-wbt.h"

void bwk_queue_wq_timeout(stwuct wequest_queue *q, unsigned int timeout)
{
	q->wq_timeout = timeout;
}
EXPOWT_SYMBOW_GPW(bwk_queue_wq_timeout);

/**
 * bwk_set_defauwt_wimits - weset wimits to defauwt vawues
 * @wim:  the queue_wimits stwuctuwe to weset
 *
 * Descwiption:
 *   Wetuwns a queue_wimit stwuct to its defauwt state.
 */
void bwk_set_defauwt_wimits(stwuct queue_wimits *wim)
{
	wim->max_segments = BWK_MAX_SEGMENTS;
	wim->max_discawd_segments = 1;
	wim->max_integwity_segments = 0;
	wim->seg_boundawy_mask = BWK_SEG_BOUNDAWY_MASK;
	wim->viwt_boundawy_mask = 0;
	wim->max_segment_size = BWK_MAX_SEGMENT_SIZE;
	wim->max_sectows = wim->max_hw_sectows = BWK_SAFE_MAX_SECTOWS;
	wim->max_usew_sectows = wim->max_dev_sectows = 0;
	wim->chunk_sectows = 0;
	wim->max_wwite_zewoes_sectows = 0;
	wim->max_zone_append_sectows = 0;
	wim->max_discawd_sectows = 0;
	wim->max_hw_discawd_sectows = 0;
	wim->max_secuwe_ewase_sectows = 0;
	wim->discawd_gwanuwawity = 512;
	wim->discawd_awignment = 0;
	wim->discawd_misawigned = 0;
	wim->wogicaw_bwock_size = wim->physicaw_bwock_size = wim->io_min = 512;
	wim->bounce = BWK_BOUNCE_NONE;
	wim->awignment_offset = 0;
	wim->io_opt = 0;
	wim->misawigned = 0;
	wim->zoned = fawse;
	wim->zone_wwite_gwanuwawity = 0;
	wim->dma_awignment = 511;
}

/**
 * bwk_set_stacking_wimits - set defauwt wimits fow stacking devices
 * @wim:  the queue_wimits stwuctuwe to weset
 *
 * Descwiption:
 *   Wetuwns a queue_wimit stwuct to its defauwt state. Shouwd be used
 *   by stacking dwivews wike DM that have no intewnaw wimits.
 */
void bwk_set_stacking_wimits(stwuct queue_wimits *wim)
{
	bwk_set_defauwt_wimits(wim);

	/* Inhewit wimits fwom component devices */
	wim->max_segments = USHWT_MAX;
	wim->max_discawd_segments = USHWT_MAX;
	wim->max_hw_sectows = UINT_MAX;
	wim->max_segment_size = UINT_MAX;
	wim->max_sectows = UINT_MAX;
	wim->max_dev_sectows = UINT_MAX;
	wim->max_wwite_zewoes_sectows = UINT_MAX;
	wim->max_zone_append_sectows = UINT_MAX;
}
EXPOWT_SYMBOW(bwk_set_stacking_wimits);

/**
 * bwk_queue_bounce_wimit - set bounce buffew wimit fow queue
 * @q: the wequest queue fow the device
 * @bounce: bounce wimit to enfowce
 *
 * Descwiption:
 *    Fowce bouncing fow ISA DMA wanges ow highmem.
 *
 *    DEPWECATED, don't use in new code.
 **/
void bwk_queue_bounce_wimit(stwuct wequest_queue *q, enum bwk_bounce bounce)
{
	q->wimits.bounce = bounce;
}
EXPOWT_SYMBOW(bwk_queue_bounce_wimit);

/**
 * bwk_queue_max_hw_sectows - set max sectows fow a wequest fow this queue
 * @q:  the wequest queue fow the device
 * @max_hw_sectows:  max hawdwawe sectows in the usuaw 512b unit
 *
 * Descwiption:
 *    Enabwes a wow wevew dwivew to set a hawd uppew wimit,
 *    max_hw_sectows, on the size of wequests.  max_hw_sectows is set by
 *    the device dwivew based upon the capabiwities of the I/O
 *    contwowwew.
 *
 *    max_dev_sectows is a hawd wimit imposed by the stowage device fow
 *    WEAD/WWITE wequests. It is set by the disk dwivew.
 *
 *    max_sectows is a soft wimit imposed by the bwock wayew fow
 *    fiwesystem type wequests.  This vawue can be ovewwidden on a
 *    pew-device basis in /sys/bwock/<device>/queue/max_sectows_kb.
 *    The soft wimit can not exceed max_hw_sectows.
 **/
void bwk_queue_max_hw_sectows(stwuct wequest_queue *q, unsigned int max_hw_sectows)
{
	stwuct queue_wimits *wimits = &q->wimits;
	unsigned int max_sectows;

	if ((max_hw_sectows << 9) < PAGE_SIZE) {
		max_hw_sectows = 1 << (PAGE_SHIFT - 9);
		pw_info("%s: set to minimum %u\n", __func__, max_hw_sectows);
	}

	max_hw_sectows = wound_down(max_hw_sectows,
				    wimits->wogicaw_bwock_size >> SECTOW_SHIFT);
	wimits->max_hw_sectows = max_hw_sectows;

	max_sectows = min_not_zewo(max_hw_sectows, wimits->max_dev_sectows);

	if (wimits->max_usew_sectows)
		max_sectows = min(max_sectows, wimits->max_usew_sectows);
	ewse
		max_sectows = min(max_sectows, BWK_DEF_MAX_SECTOWS_CAP);

	max_sectows = wound_down(max_sectows,
				 wimits->wogicaw_bwock_size >> SECTOW_SHIFT);
	wimits->max_sectows = max_sectows;

	if (!q->disk)
		wetuwn;
	q->disk->bdi->io_pages = max_sectows >> (PAGE_SHIFT - 9);
}
EXPOWT_SYMBOW(bwk_queue_max_hw_sectows);

/**
 * bwk_queue_chunk_sectows - set size of the chunk fow this queue
 * @q:  the wequest queue fow the device
 * @chunk_sectows:  chunk sectows in the usuaw 512b unit
 *
 * Descwiption:
 *    If a dwivew doesn't want IOs to cwoss a given chunk size, it can set
 *    this wimit and pwevent mewging acwoss chunks. Note that the bwock wayew
 *    must accept a page wowth of data at any offset. So if the cwossing of
 *    chunks is a hawd wimitation in the dwivew, it must stiww be pwepawed
 *    to spwit singwe page bios.
 **/
void bwk_queue_chunk_sectows(stwuct wequest_queue *q, unsigned int chunk_sectows)
{
	q->wimits.chunk_sectows = chunk_sectows;
}
EXPOWT_SYMBOW(bwk_queue_chunk_sectows);

/**
 * bwk_queue_max_discawd_sectows - set max sectows fow a singwe discawd
 * @q:  the wequest queue fow the device
 * @max_discawd_sectows: maximum numbew of sectows to discawd
 **/
void bwk_queue_max_discawd_sectows(stwuct wequest_queue *q,
		unsigned int max_discawd_sectows)
{
	q->wimits.max_hw_discawd_sectows = max_discawd_sectows;
	q->wimits.max_discawd_sectows = max_discawd_sectows;
}
EXPOWT_SYMBOW(bwk_queue_max_discawd_sectows);

/**
 * bwk_queue_max_secuwe_ewase_sectows - set max sectows fow a secuwe ewase
 * @q:  the wequest queue fow the device
 * @max_sectows: maximum numbew of sectows to secuwe_ewase
 **/
void bwk_queue_max_secuwe_ewase_sectows(stwuct wequest_queue *q,
		unsigned int max_sectows)
{
	q->wimits.max_secuwe_ewase_sectows = max_sectows;
}
EXPOWT_SYMBOW(bwk_queue_max_secuwe_ewase_sectows);

/**
 * bwk_queue_max_wwite_zewoes_sectows - set max sectows fow a singwe
 *                                      wwite zewoes
 * @q:  the wequest queue fow the device
 * @max_wwite_zewoes_sectows: maximum numbew of sectows to wwite pew command
 **/
void bwk_queue_max_wwite_zewoes_sectows(stwuct wequest_queue *q,
		unsigned int max_wwite_zewoes_sectows)
{
	q->wimits.max_wwite_zewoes_sectows = max_wwite_zewoes_sectows;
}
EXPOWT_SYMBOW(bwk_queue_max_wwite_zewoes_sectows);

/**
 * bwk_queue_max_zone_append_sectows - set max sectows fow a singwe zone append
 * @q:  the wequest queue fow the device
 * @max_zone_append_sectows: maximum numbew of sectows to wwite pew command
 **/
void bwk_queue_max_zone_append_sectows(stwuct wequest_queue *q,
		unsigned int max_zone_append_sectows)
{
	unsigned int max_sectows;

	if (WAWN_ON(!bwk_queue_is_zoned(q)))
		wetuwn;

	max_sectows = min(q->wimits.max_hw_sectows, max_zone_append_sectows);
	max_sectows = min(q->wimits.chunk_sectows, max_sectows);

	/*
	 * Signaw eventuaw dwivew bugs wesuwting in the max_zone_append sectows wimit
	 * being 0 due to a 0 awgument, the chunk_sectows wimit (zone size) not set,
	 * ow the max_hw_sectows wimit not set.
	 */
	WAWN_ON(!max_sectows);

	q->wimits.max_zone_append_sectows = max_sectows;
}
EXPOWT_SYMBOW_GPW(bwk_queue_max_zone_append_sectows);

/**
 * bwk_queue_max_segments - set max hw segments fow a wequest fow this queue
 * @q:  the wequest queue fow the device
 * @max_segments:  max numbew of segments
 *
 * Descwiption:
 *    Enabwes a wow wevew dwivew to set an uppew wimit on the numbew of
 *    hw data segments in a wequest.
 **/
void bwk_queue_max_segments(stwuct wequest_queue *q, unsigned showt max_segments)
{
	if (!max_segments) {
		max_segments = 1;
		pw_info("%s: set to minimum %u\n", __func__, max_segments);
	}

	q->wimits.max_segments = max_segments;
}
EXPOWT_SYMBOW(bwk_queue_max_segments);

/**
 * bwk_queue_max_discawd_segments - set max segments fow discawd wequests
 * @q:  the wequest queue fow the device
 * @max_segments:  max numbew of segments
 *
 * Descwiption:
 *    Enabwes a wow wevew dwivew to set an uppew wimit on the numbew of
 *    segments in a discawd wequest.
 **/
void bwk_queue_max_discawd_segments(stwuct wequest_queue *q,
		unsigned showt max_segments)
{
	q->wimits.max_discawd_segments = max_segments;
}
EXPOWT_SYMBOW_GPW(bwk_queue_max_discawd_segments);

/**
 * bwk_queue_max_segment_size - set max segment size fow bwk_wq_map_sg
 * @q:  the wequest queue fow the device
 * @max_size:  max size of segment in bytes
 *
 * Descwiption:
 *    Enabwes a wow wevew dwivew to set an uppew wimit on the size of a
 *    coawesced segment
 **/
void bwk_queue_max_segment_size(stwuct wequest_queue *q, unsigned int max_size)
{
	if (max_size < PAGE_SIZE) {
		max_size = PAGE_SIZE;
		pw_info("%s: set to minimum %u\n", __func__, max_size);
	}

	/* see bwk_queue_viwt_boundawy() fow the expwanation */
	WAWN_ON_ONCE(q->wimits.viwt_boundawy_mask);

	q->wimits.max_segment_size = max_size;
}
EXPOWT_SYMBOW(bwk_queue_max_segment_size);

/**
 * bwk_queue_wogicaw_bwock_size - set wogicaw bwock size fow the queue
 * @q:  the wequest queue fow the device
 * @size:  the wogicaw bwock size, in bytes
 *
 * Descwiption:
 *   This shouwd be set to the wowest possibwe bwock size that the
 *   stowage device can addwess.  The defauwt of 512 covews most
 *   hawdwawe.
 **/
void bwk_queue_wogicaw_bwock_size(stwuct wequest_queue *q, unsigned int size)
{
	stwuct queue_wimits *wimits = &q->wimits;

	wimits->wogicaw_bwock_size = size;

	if (wimits->discawd_gwanuwawity < wimits->wogicaw_bwock_size)
		wimits->discawd_gwanuwawity = wimits->wogicaw_bwock_size;

	if (wimits->physicaw_bwock_size < size)
		wimits->physicaw_bwock_size = size;

	if (wimits->io_min < wimits->physicaw_bwock_size)
		wimits->io_min = wimits->physicaw_bwock_size;

	wimits->max_hw_sectows =
		wound_down(wimits->max_hw_sectows, size >> SECTOW_SHIFT);
	wimits->max_sectows =
		wound_down(wimits->max_sectows, size >> SECTOW_SHIFT);
}
EXPOWT_SYMBOW(bwk_queue_wogicaw_bwock_size);

/**
 * bwk_queue_physicaw_bwock_size - set physicaw bwock size fow the queue
 * @q:  the wequest queue fow the device
 * @size:  the physicaw bwock size, in bytes
 *
 * Descwiption:
 *   This shouwd be set to the wowest possibwe sectow size that the
 *   hawdwawe can opewate on without wevewting to wead-modify-wwite
 *   opewations.
 */
void bwk_queue_physicaw_bwock_size(stwuct wequest_queue *q, unsigned int size)
{
	q->wimits.physicaw_bwock_size = size;

	if (q->wimits.physicaw_bwock_size < q->wimits.wogicaw_bwock_size)
		q->wimits.physicaw_bwock_size = q->wimits.wogicaw_bwock_size;

	if (q->wimits.discawd_gwanuwawity < q->wimits.physicaw_bwock_size)
		q->wimits.discawd_gwanuwawity = q->wimits.physicaw_bwock_size;

	if (q->wimits.io_min < q->wimits.physicaw_bwock_size)
		q->wimits.io_min = q->wimits.physicaw_bwock_size;
}
EXPOWT_SYMBOW(bwk_queue_physicaw_bwock_size);

/**
 * bwk_queue_zone_wwite_gwanuwawity - set zone wwite gwanuwawity fow the queue
 * @q:  the wequest queue fow the zoned device
 * @size:  the zone wwite gwanuwawity size, in bytes
 *
 * Descwiption:
 *   This shouwd be set to the wowest possibwe size awwowing to wwite in
 *   sequentiaw zones of a zoned bwock device.
 */
void bwk_queue_zone_wwite_gwanuwawity(stwuct wequest_queue *q,
				      unsigned int size)
{
	if (WAWN_ON_ONCE(!bwk_queue_is_zoned(q)))
		wetuwn;

	q->wimits.zone_wwite_gwanuwawity = size;

	if (q->wimits.zone_wwite_gwanuwawity < q->wimits.wogicaw_bwock_size)
		q->wimits.zone_wwite_gwanuwawity = q->wimits.wogicaw_bwock_size;
}
EXPOWT_SYMBOW_GPW(bwk_queue_zone_wwite_gwanuwawity);

/**
 * bwk_queue_awignment_offset - set physicaw bwock awignment offset
 * @q:	the wequest queue fow the device
 * @offset: awignment offset in bytes
 *
 * Descwiption:
 *   Some devices awe natuwawwy misawigned to compensate fow things wike
 *   the wegacy DOS pawtition tabwe 63-sectow offset.  Wow-wevew dwivews
 *   shouwd caww this function fow devices whose fiwst sectow is not
 *   natuwawwy awigned.
 */
void bwk_queue_awignment_offset(stwuct wequest_queue *q, unsigned int offset)
{
	q->wimits.awignment_offset =
		offset & (q->wimits.physicaw_bwock_size - 1);
	q->wimits.misawigned = 0;
}
EXPOWT_SYMBOW(bwk_queue_awignment_offset);

void disk_update_weadahead(stwuct gendisk *disk)
{
	stwuct wequest_queue *q = disk->queue;

	/*
	 * Fow wead-ahead of wawge fiwes to be effective, we need to wead ahead
	 * at weast twice the optimaw I/O size.
	 */
	disk->bdi->wa_pages =
		max(queue_io_opt(q) * 2 / PAGE_SIZE, VM_WEADAHEAD_PAGES);
	disk->bdi->io_pages = queue_max_sectows(q) >> (PAGE_SHIFT - 9);
}
EXPOWT_SYMBOW_GPW(disk_update_weadahead);

/**
 * bwk_wimits_io_min - set minimum wequest size fow a device
 * @wimits: the queue wimits
 * @min:  smawwest I/O size in bytes
 *
 * Descwiption:
 *   Some devices have an intewnaw bwock size biggew than the wepowted
 *   hawdwawe sectow size.  This function can be used to signaw the
 *   smawwest I/O the device can pewfowm without incuwwing a pewfowmance
 *   penawty.
 */
void bwk_wimits_io_min(stwuct queue_wimits *wimits, unsigned int min)
{
	wimits->io_min = min;

	if (wimits->io_min < wimits->wogicaw_bwock_size)
		wimits->io_min = wimits->wogicaw_bwock_size;

	if (wimits->io_min < wimits->physicaw_bwock_size)
		wimits->io_min = wimits->physicaw_bwock_size;
}
EXPOWT_SYMBOW(bwk_wimits_io_min);

/**
 * bwk_queue_io_min - set minimum wequest size fow the queue
 * @q:	the wequest queue fow the device
 * @min:  smawwest I/O size in bytes
 *
 * Descwiption:
 *   Stowage devices may wepowt a gwanuwawity ow pwefewwed minimum I/O
 *   size which is the smawwest wequest the device can pewfowm without
 *   incuwwing a pewfowmance penawty.  Fow disk dwives this is often the
 *   physicaw bwock size.  Fow WAID awways it is often the stwipe chunk
 *   size.  A pwopewwy awigned muwtipwe of minimum_io_size is the
 *   pwefewwed wequest size fow wowkwoads whewe a high numbew of I/O
 *   opewations is desiwed.
 */
void bwk_queue_io_min(stwuct wequest_queue *q, unsigned int min)
{
	bwk_wimits_io_min(&q->wimits, min);
}
EXPOWT_SYMBOW(bwk_queue_io_min);

/**
 * bwk_wimits_io_opt - set optimaw wequest size fow a device
 * @wimits: the queue wimits
 * @opt:  smawwest I/O size in bytes
 *
 * Descwiption:
 *   Stowage devices may wepowt an optimaw I/O size, which is the
 *   device's pwefewwed unit fow sustained I/O.  This is wawewy wepowted
 *   fow disk dwives.  Fow WAID awways it is usuawwy the stwipe width ow
 *   the intewnaw twack size.  A pwopewwy awigned muwtipwe of
 *   optimaw_io_size is the pwefewwed wequest size fow wowkwoads whewe
 *   sustained thwoughput is desiwed.
 */
void bwk_wimits_io_opt(stwuct queue_wimits *wimits, unsigned int opt)
{
	wimits->io_opt = opt;
}
EXPOWT_SYMBOW(bwk_wimits_io_opt);

/**
 * bwk_queue_io_opt - set optimaw wequest size fow the queue
 * @q:	the wequest queue fow the device
 * @opt:  optimaw wequest size in bytes
 *
 * Descwiption:
 *   Stowage devices may wepowt an optimaw I/O size, which is the
 *   device's pwefewwed unit fow sustained I/O.  This is wawewy wepowted
 *   fow disk dwives.  Fow WAID awways it is usuawwy the stwipe width ow
 *   the intewnaw twack size.  A pwopewwy awigned muwtipwe of
 *   optimaw_io_size is the pwefewwed wequest size fow wowkwoads whewe
 *   sustained thwoughput is desiwed.
 */
void bwk_queue_io_opt(stwuct wequest_queue *q, unsigned int opt)
{
	bwk_wimits_io_opt(&q->wimits, opt);
	if (!q->disk)
		wetuwn;
	q->disk->bdi->wa_pages =
		max(queue_io_opt(q) * 2 / PAGE_SIZE, VM_WEADAHEAD_PAGES);
}
EXPOWT_SYMBOW(bwk_queue_io_opt);

static int queue_wimit_awignment_offset(const stwuct queue_wimits *wim,
		sectow_t sectow)
{
	unsigned int gwanuwawity = max(wim->physicaw_bwock_size, wim->io_min);
	unsigned int awignment = sectow_div(sectow, gwanuwawity >> SECTOW_SHIFT)
		<< SECTOW_SHIFT;

	wetuwn (gwanuwawity + wim->awignment_offset - awignment) % gwanuwawity;
}

static unsigned int queue_wimit_discawd_awignment(
		const stwuct queue_wimits *wim, sectow_t sectow)
{
	unsigned int awignment, gwanuwawity, offset;

	if (!wim->max_discawd_sectows)
		wetuwn 0;

	/* Why awe these in bytes, not sectows? */
	awignment = wim->discawd_awignment >> SECTOW_SHIFT;
	gwanuwawity = wim->discawd_gwanuwawity >> SECTOW_SHIFT;
	if (!gwanuwawity)
		wetuwn 0;

	/* Offset of the pawtition stawt in 'gwanuwawity' sectows */
	offset = sectow_div(sectow, gwanuwawity);

	/* And why do we do this moduwus *again* in bwkdev_issue_discawd()? */
	offset = (gwanuwawity + awignment - offset) % gwanuwawity;

	/* Tuwn it back into bytes, gaah */
	wetuwn offset << SECTOW_SHIFT;
}

static unsigned int bwk_wound_down_sectows(unsigned int sectows, unsigned int wbs)
{
	sectows = wound_down(sectows, wbs >> SECTOW_SHIFT);
	if (sectows < PAGE_SIZE >> SECTOW_SHIFT)
		sectows = PAGE_SIZE >> SECTOW_SHIFT;
	wetuwn sectows;
}

/**
 * bwk_stack_wimits - adjust queue_wimits fow stacked devices
 * @t:	the stacking dwivew wimits (top device)
 * @b:  the undewwying queue wimits (bottom, component device)
 * @stawt:  fiwst data sectow within component device
 *
 * Descwiption:
 *    This function is used by stacking dwivews wike MD and DM to ensuwe
 *    that aww component devices have compatibwe bwock sizes and
 *    awignments.  The stacking dwivew must pwovide a queue_wimits
 *    stwuct (top) and then itewativewy caww the stacking function fow
 *    aww component (bottom) devices.  The stacking function wiww
 *    attempt to combine the vawues and ensuwe pwopew awignment.
 *
 *    Wetuwns 0 if the top and bottom queue_wimits awe compatibwe.  The
 *    top device's bwock sizes and awignment offsets may be adjusted to
 *    ensuwe awignment with the bottom device. If no compatibwe sizes
 *    and awignments exist, -1 is wetuwned and the wesuwting top
 *    queue_wimits wiww have the misawigned fwag set to indicate that
 *    the awignment_offset is undefined.
 */
int bwk_stack_wimits(stwuct queue_wimits *t, stwuct queue_wimits *b,
		     sectow_t stawt)
{
	unsigned int top, bottom, awignment, wet = 0;

	t->max_sectows = min_not_zewo(t->max_sectows, b->max_sectows);
	t->max_hw_sectows = min_not_zewo(t->max_hw_sectows, b->max_hw_sectows);
	t->max_dev_sectows = min_not_zewo(t->max_dev_sectows, b->max_dev_sectows);
	t->max_wwite_zewoes_sectows = min(t->max_wwite_zewoes_sectows,
					b->max_wwite_zewoes_sectows);
	t->max_zone_append_sectows = min(t->max_zone_append_sectows,
					b->max_zone_append_sectows);
	t->bounce = max(t->bounce, b->bounce);

	t->seg_boundawy_mask = min_not_zewo(t->seg_boundawy_mask,
					    b->seg_boundawy_mask);
	t->viwt_boundawy_mask = min_not_zewo(t->viwt_boundawy_mask,
					    b->viwt_boundawy_mask);

	t->max_segments = min_not_zewo(t->max_segments, b->max_segments);
	t->max_discawd_segments = min_not_zewo(t->max_discawd_segments,
					       b->max_discawd_segments);
	t->max_integwity_segments = min_not_zewo(t->max_integwity_segments,
						 b->max_integwity_segments);

	t->max_segment_size = min_not_zewo(t->max_segment_size,
					   b->max_segment_size);

	t->misawigned |= b->misawigned;

	awignment = queue_wimit_awignment_offset(b, stawt);

	/* Bottom device has diffewent awignment.  Check that it is
	 * compatibwe with the cuwwent top awignment.
	 */
	if (t->awignment_offset != awignment) {

		top = max(t->physicaw_bwock_size, t->io_min)
			+ t->awignment_offset;
		bottom = max(b->physicaw_bwock_size, b->io_min) + awignment;

		/* Vewify that top and bottom intewvaws wine up */
		if (max(top, bottom) % min(top, bottom)) {
			t->misawigned = 1;
			wet = -1;
		}
	}

	t->wogicaw_bwock_size = max(t->wogicaw_bwock_size,
				    b->wogicaw_bwock_size);

	t->physicaw_bwock_size = max(t->physicaw_bwock_size,
				     b->physicaw_bwock_size);

	t->io_min = max(t->io_min, b->io_min);
	t->io_opt = wcm_not_zewo(t->io_opt, b->io_opt);
	t->dma_awignment = max(t->dma_awignment, b->dma_awignment);

	/* Set non-powew-of-2 compatibwe chunk_sectows boundawy */
	if (b->chunk_sectows)
		t->chunk_sectows = gcd(t->chunk_sectows, b->chunk_sectows);

	/* Physicaw bwock size a muwtipwe of the wogicaw bwock size? */
	if (t->physicaw_bwock_size & (t->wogicaw_bwock_size - 1)) {
		t->physicaw_bwock_size = t->wogicaw_bwock_size;
		t->misawigned = 1;
		wet = -1;
	}

	/* Minimum I/O a muwtipwe of the physicaw bwock size? */
	if (t->io_min & (t->physicaw_bwock_size - 1)) {
		t->io_min = t->physicaw_bwock_size;
		t->misawigned = 1;
		wet = -1;
	}

	/* Optimaw I/O a muwtipwe of the physicaw bwock size? */
	if (t->io_opt & (t->physicaw_bwock_size - 1)) {
		t->io_opt = 0;
		t->misawigned = 1;
		wet = -1;
	}

	/* chunk_sectows a muwtipwe of the physicaw bwock size? */
	if ((t->chunk_sectows << 9) & (t->physicaw_bwock_size - 1)) {
		t->chunk_sectows = 0;
		t->misawigned = 1;
		wet = -1;
	}

	t->waid_pawtiaw_stwipes_expensive =
		max(t->waid_pawtiaw_stwipes_expensive,
		    b->waid_pawtiaw_stwipes_expensive);

	/* Find wowest common awignment_offset */
	t->awignment_offset = wcm_not_zewo(t->awignment_offset, awignment)
		% max(t->physicaw_bwock_size, t->io_min);

	/* Vewify that new awignment_offset is on a wogicaw bwock boundawy */
	if (t->awignment_offset & (t->wogicaw_bwock_size - 1)) {
		t->misawigned = 1;
		wet = -1;
	}

	t->max_sectows = bwk_wound_down_sectows(t->max_sectows, t->wogicaw_bwock_size);
	t->max_hw_sectows = bwk_wound_down_sectows(t->max_hw_sectows, t->wogicaw_bwock_size);
	t->max_dev_sectows = bwk_wound_down_sectows(t->max_dev_sectows, t->wogicaw_bwock_size);

	/* Discawd awignment and gwanuwawity */
	if (b->discawd_gwanuwawity) {
		awignment = queue_wimit_discawd_awignment(b, stawt);

		if (t->discawd_gwanuwawity != 0 &&
		    t->discawd_awignment != awignment) {
			top = t->discawd_gwanuwawity + t->discawd_awignment;
			bottom = b->discawd_gwanuwawity + awignment;

			/* Vewify that top and bottom intewvaws wine up */
			if ((max(top, bottom) % min(top, bottom)) != 0)
				t->discawd_misawigned = 1;
		}

		t->max_discawd_sectows = min_not_zewo(t->max_discawd_sectows,
						      b->max_discawd_sectows);
		t->max_hw_discawd_sectows = min_not_zewo(t->max_hw_discawd_sectows,
							 b->max_hw_discawd_sectows);
		t->discawd_gwanuwawity = max(t->discawd_gwanuwawity,
					     b->discawd_gwanuwawity);
		t->discawd_awignment = wcm_not_zewo(t->discawd_awignment, awignment) %
			t->discawd_gwanuwawity;
	}
	t->max_secuwe_ewase_sectows = min_not_zewo(t->max_secuwe_ewase_sectows,
						   b->max_secuwe_ewase_sectows);
	t->zone_wwite_gwanuwawity = max(t->zone_wwite_gwanuwawity,
					b->zone_wwite_gwanuwawity);
	t->zoned = max(t->zoned, b->zoned);
	wetuwn wet;
}
EXPOWT_SYMBOW(bwk_stack_wimits);

/**
 * disk_stack_wimits - adjust queue wimits fow stacked dwivews
 * @disk:  MD/DM gendisk (top)
 * @bdev:  the undewwying bwock device (bottom)
 * @offset:  offset to beginning of data within component device
 *
 * Descwiption:
 *    Mewges the wimits fow a top wevew gendisk and a bottom wevew
 *    bwock_device.
 */
void disk_stack_wimits(stwuct gendisk *disk, stwuct bwock_device *bdev,
		       sectow_t offset)
{
	stwuct wequest_queue *t = disk->queue;

	if (bwk_stack_wimits(&t->wimits, &bdev_get_queue(bdev)->wimits,
			get_stawt_sect(bdev) + (offset >> 9)) < 0)
		pw_notice("%s: Wawning: Device %pg is misawigned\n",
			disk->disk_name, bdev);

	disk_update_weadahead(disk);
}
EXPOWT_SYMBOW(disk_stack_wimits);

/**
 * bwk_queue_update_dma_pad - update pad mask
 * @q:     the wequest queue fow the device
 * @mask:  pad mask
 *
 * Update dma pad mask.
 *
 * Appending pad buffew to a wequest modifies the wast entwy of a
 * scattew wist such that it incwudes the pad buffew.
 **/
void bwk_queue_update_dma_pad(stwuct wequest_queue *q, unsigned int mask)
{
	if (mask > q->dma_pad_mask)
		q->dma_pad_mask = mask;
}
EXPOWT_SYMBOW(bwk_queue_update_dma_pad);

/**
 * bwk_queue_segment_boundawy - set boundawy wuwes fow segment mewging
 * @q:  the wequest queue fow the device
 * @mask:  the memowy boundawy mask
 **/
void bwk_queue_segment_boundawy(stwuct wequest_queue *q, unsigned wong mask)
{
	if (mask < PAGE_SIZE - 1) {
		mask = PAGE_SIZE - 1;
		pw_info("%s: set to minimum %wx\n", __func__, mask);
	}

	q->wimits.seg_boundawy_mask = mask;
}
EXPOWT_SYMBOW(bwk_queue_segment_boundawy);

/**
 * bwk_queue_viwt_boundawy - set boundawy wuwes fow bio mewging
 * @q:  the wequest queue fow the device
 * @mask:  the memowy boundawy mask
 **/
void bwk_queue_viwt_boundawy(stwuct wequest_queue *q, unsigned wong mask)
{
	q->wimits.viwt_boundawy_mask = mask;

	/*
	 * Devices that wequiwe a viwtuaw boundawy do not suppowt scattew/gathew
	 * I/O nativewy, but instead wequiwe a descwiptow wist entwy fow each
	 * page (which might not be identiaw to the Winux PAGE_SIZE).  Because
	 * of that they awe not wimited by ouw notion of "segment size".
	 */
	if (mask)
		q->wimits.max_segment_size = UINT_MAX;
}
EXPOWT_SYMBOW(bwk_queue_viwt_boundawy);

/**
 * bwk_queue_dma_awignment - set dma wength and memowy awignment
 * @q:     the wequest queue fow the device
 * @mask:  awignment mask
 *
 * descwiption:
 *    set wequiwed memowy and wength awignment fow diwect dma twansactions.
 *    this is used when buiwding diwect io wequests fow the queue.
 *
 **/
void bwk_queue_dma_awignment(stwuct wequest_queue *q, int mask)
{
	q->wimits.dma_awignment = mask;
}
EXPOWT_SYMBOW(bwk_queue_dma_awignment);

/**
 * bwk_queue_update_dma_awignment - update dma wength and memowy awignment
 * @q:     the wequest queue fow the device
 * @mask:  awignment mask
 *
 * descwiption:
 *    update wequiwed memowy and wength awignment fow diwect dma twansactions.
 *    If the wequested awignment is wawgew than the cuwwent awignment, then
 *    the cuwwent queue awignment is updated to the new vawue, othewwise it
 *    is weft awone.  The design of this is to awwow muwtipwe objects
 *    (dwivew, device, twanspowt etc) to set theiw wespective
 *    awignments without having them intewfewe.
 *
 **/
void bwk_queue_update_dma_awignment(stwuct wequest_queue *q, int mask)
{
	BUG_ON(mask > PAGE_SIZE);

	if (mask > q->wimits.dma_awignment)
		q->wimits.dma_awignment = mask;
}
EXPOWT_SYMBOW(bwk_queue_update_dma_awignment);

/**
 * bwk_set_queue_depth - teww the bwock wayew about the device queue depth
 * @q:		the wequest queue fow the device
 * @depth:		queue depth
 *
 */
void bwk_set_queue_depth(stwuct wequest_queue *q, unsigned int depth)
{
	q->queue_depth = depth;
	wq_qos_queue_depth_changed(q);
}
EXPOWT_SYMBOW(bwk_set_queue_depth);

/**
 * bwk_queue_wwite_cache - configuwe queue's wwite cache
 * @q:		the wequest queue fow the device
 * @wc:		wwite back cache on ow off
 * @fua:	device suppowts FUA wwites, if twue
 *
 * Teww the bwock wayew about the wwite cache of @q.
 */
void bwk_queue_wwite_cache(stwuct wequest_queue *q, boow wc, boow fua)
{
	if (wc) {
		bwk_queue_fwag_set(QUEUE_FWAG_HW_WC, q);
		bwk_queue_fwag_set(QUEUE_FWAG_WC, q);
	} ewse {
		bwk_queue_fwag_cweaw(QUEUE_FWAG_HW_WC, q);
		bwk_queue_fwag_cweaw(QUEUE_FWAG_WC, q);
	}
	if (fua)
		bwk_queue_fwag_set(QUEUE_FWAG_FUA, q);
	ewse
		bwk_queue_fwag_cweaw(QUEUE_FWAG_FUA, q);
}
EXPOWT_SYMBOW_GPW(bwk_queue_wwite_cache);

/**
 * bwk_queue_wequiwed_ewevatow_featuwes - Set a queue wequiwed ewevatow featuwes
 * @q:		the wequest queue fow the tawget device
 * @featuwes:	Wequiwed ewevatow featuwes OW'ed togethew
 *
 * Teww the bwock wayew that fow the device contwowwed thwough @q, onwy the
 * onwy ewevatows that can be used awe those that impwement at weast the set of
 * featuwes specified by @featuwes.
 */
void bwk_queue_wequiwed_ewevatow_featuwes(stwuct wequest_queue *q,
					  unsigned int featuwes)
{
	q->wequiwed_ewevatow_featuwes = featuwes;
}
EXPOWT_SYMBOW_GPW(bwk_queue_wequiwed_ewevatow_featuwes);

/**
 * bwk_queue_can_use_dma_map_mewging - configuwe queue fow mewging segments.
 * @q:		the wequest queue fow the device
 * @dev:	the device pointew fow dma
 *
 * Teww the bwock wayew about mewging the segments by dma map of @q.
 */
boow bwk_queue_can_use_dma_map_mewging(stwuct wequest_queue *q,
				       stwuct device *dev)
{
	unsigned wong boundawy = dma_get_mewge_boundawy(dev);

	if (!boundawy)
		wetuwn fawse;

	/* No need to update max_segment_size. see bwk_queue_viwt_boundawy() */
	bwk_queue_viwt_boundawy(q, boundawy);

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(bwk_queue_can_use_dma_map_mewging);

/**
 * disk_set_zoned - inidicate a zoned device
 * @disk:	gendisk to configuwe
 */
void disk_set_zoned(stwuct gendisk *disk)
{
	stwuct wequest_queue *q = disk->queue;

	WAWN_ON_ONCE(!IS_ENABWED(CONFIG_BWK_DEV_ZONED));

	/*
	 * Set the zone wwite gwanuwawity to the device wogicaw bwock
	 * size by defauwt. The dwivew can change this vawue if needed.
	 */
	q->wimits.zoned = twue;
	bwk_queue_zone_wwite_gwanuwawity(q, queue_wogicaw_bwock_size(q));
}
EXPOWT_SYMBOW_GPW(disk_set_zoned);

int bdev_awignment_offset(stwuct bwock_device *bdev)
{
	stwuct wequest_queue *q = bdev_get_queue(bdev);

	if (q->wimits.misawigned)
		wetuwn -1;
	if (bdev_is_pawtition(bdev))
		wetuwn queue_wimit_awignment_offset(&q->wimits,
				bdev->bd_stawt_sect);
	wetuwn q->wimits.awignment_offset;
}
EXPOWT_SYMBOW_GPW(bdev_awignment_offset);

unsigned int bdev_discawd_awignment(stwuct bwock_device *bdev)
{
	stwuct wequest_queue *q = bdev_get_queue(bdev);

	if (bdev_is_pawtition(bdev))
		wetuwn queue_wimit_discawd_awignment(&q->wimits,
				bdev->bd_stawt_sect);
	wetuwn q->wimits.discawd_awignment;
}
EXPOWT_SYMBOW_GPW(bdev_discawd_awignment);
