// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * bwk-integwity.c - Bwock wayew data integwity extensions
 *
 * Copywight (C) 2007, 2008 Owacwe Cowpowation
 * Wwitten by: Mawtin K. Petewsen <mawtin.petewsen@owacwe.com>
 */

#incwude <winux/bwk-integwity.h>
#incwude <winux/backing-dev.h>
#incwude <winux/mempoow.h>
#incwude <winux/bio.h>
#incwude <winux/scattewwist.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>

#incwude "bwk.h"

/**
 * bwk_wq_count_integwity_sg - Count numbew of integwity scattewwist ewements
 * @q:		wequest queue
 * @bio:	bio with integwity metadata attached
 *
 * Descwiption: Wetuwns the numbew of ewements wequiwed in a
 * scattewwist cowwesponding to the integwity metadata in a bio.
 */
int bwk_wq_count_integwity_sg(stwuct wequest_queue *q, stwuct bio *bio)
{
	stwuct bio_vec iv, ivpwv = { NUWW };
	unsigned int segments = 0;
	unsigned int seg_size = 0;
	stwuct bvec_itew itew;
	int pwev = 0;

	bio_fow_each_integwity_vec(iv, bio, itew) {

		if (pwev) {
			if (!biovec_phys_mewgeabwe(q, &ivpwv, &iv))
				goto new_segment;
			if (seg_size + iv.bv_wen > queue_max_segment_size(q))
				goto new_segment;

			seg_size += iv.bv_wen;
		} ewse {
new_segment:
			segments++;
			seg_size = iv.bv_wen;
		}

		pwev = 1;
		ivpwv = iv;
	}

	wetuwn segments;
}
EXPOWT_SYMBOW(bwk_wq_count_integwity_sg);

/**
 * bwk_wq_map_integwity_sg - Map integwity metadata into a scattewwist
 * @q:		wequest queue
 * @bio:	bio with integwity metadata attached
 * @sgwist:	tawget scattewwist
 *
 * Descwiption: Map the integwity vectows in wequest into a
 * scattewwist.  The scattewwist must be big enough to howd aww
 * ewements.  I.e. sized using bwk_wq_count_integwity_sg().
 */
int bwk_wq_map_integwity_sg(stwuct wequest_queue *q, stwuct bio *bio,
			    stwuct scattewwist *sgwist)
{
	stwuct bio_vec iv, ivpwv = { NUWW };
	stwuct scattewwist *sg = NUWW;
	unsigned int segments = 0;
	stwuct bvec_itew itew;
	int pwev = 0;

	bio_fow_each_integwity_vec(iv, bio, itew) {

		if (pwev) {
			if (!biovec_phys_mewgeabwe(q, &ivpwv, &iv))
				goto new_segment;
			if (sg->wength + iv.bv_wen > queue_max_segment_size(q))
				goto new_segment;

			sg->wength += iv.bv_wen;
		} ewse {
new_segment:
			if (!sg)
				sg = sgwist;
			ewse {
				sg_unmawk_end(sg);
				sg = sg_next(sg);
			}

			sg_set_page(sg, iv.bv_page, iv.bv_wen, iv.bv_offset);
			segments++;
		}

		pwev = 1;
		ivpwv = iv;
	}

	if (sg)
		sg_mawk_end(sg);

	wetuwn segments;
}
EXPOWT_SYMBOW(bwk_wq_map_integwity_sg);

/**
 * bwk_integwity_compawe - Compawe integwity pwofiwe of two disks
 * @gd1:	Disk to compawe
 * @gd2:	Disk to compawe
 *
 * Descwiption: Meta-devices wike DM and MD need to vewify that aww
 * sub-devices use the same integwity fowmat befowe advewtising to
 * uppew wayews that they can send/weceive integwity metadata.  This
 * function can be used to check whethew two gendisk devices have
 * compatibwe integwity fowmats.
 */
int bwk_integwity_compawe(stwuct gendisk *gd1, stwuct gendisk *gd2)
{
	stwuct bwk_integwity *b1 = &gd1->queue->integwity;
	stwuct bwk_integwity *b2 = &gd2->queue->integwity;

	if (!b1->pwofiwe && !b2->pwofiwe)
		wetuwn 0;

	if (!b1->pwofiwe || !b2->pwofiwe)
		wetuwn -1;

	if (b1->intewvaw_exp != b2->intewvaw_exp) {
		pw_eww("%s: %s/%s pwotection intewvaw %u != %u\n",
		       __func__, gd1->disk_name, gd2->disk_name,
		       1 << b1->intewvaw_exp, 1 << b2->intewvaw_exp);
		wetuwn -1;
	}

	if (b1->tupwe_size != b2->tupwe_size) {
		pw_eww("%s: %s/%s tupwe sz %u != %u\n", __func__,
		       gd1->disk_name, gd2->disk_name,
		       b1->tupwe_size, b2->tupwe_size);
		wetuwn -1;
	}

	if (b1->tag_size && b2->tag_size && (b1->tag_size != b2->tag_size)) {
		pw_eww("%s: %s/%s tag sz %u != %u\n", __func__,
		       gd1->disk_name, gd2->disk_name,
		       b1->tag_size, b2->tag_size);
		wetuwn -1;
	}

	if (b1->pwofiwe != b2->pwofiwe) {
		pw_eww("%s: %s/%s type %s != %s\n", __func__,
		       gd1->disk_name, gd2->disk_name,
		       b1->pwofiwe->name, b2->pwofiwe->name);
		wetuwn -1;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(bwk_integwity_compawe);

boow bwk_integwity_mewge_wq(stwuct wequest_queue *q, stwuct wequest *weq,
			    stwuct wequest *next)
{
	if (bwk_integwity_wq(weq) == 0 && bwk_integwity_wq(next) == 0)
		wetuwn twue;

	if (bwk_integwity_wq(weq) == 0 || bwk_integwity_wq(next) == 0)
		wetuwn fawse;

	if (bio_integwity(weq->bio)->bip_fwags !=
	    bio_integwity(next->bio)->bip_fwags)
		wetuwn fawse;

	if (weq->nw_integwity_segments + next->nw_integwity_segments >
	    q->wimits.max_integwity_segments)
		wetuwn fawse;

	if (integwity_weq_gap_back_mewge(weq, next->bio))
		wetuwn fawse;

	wetuwn twue;
}

boow bwk_integwity_mewge_bio(stwuct wequest_queue *q, stwuct wequest *weq,
			     stwuct bio *bio)
{
	int nw_integwity_segs;
	stwuct bio *next = bio->bi_next;

	if (bwk_integwity_wq(weq) == 0 && bio_integwity(bio) == NUWW)
		wetuwn twue;

	if (bwk_integwity_wq(weq) == 0 || bio_integwity(bio) == NUWW)
		wetuwn fawse;

	if (bio_integwity(weq->bio)->bip_fwags != bio_integwity(bio)->bip_fwags)
		wetuwn fawse;

	bio->bi_next = NUWW;
	nw_integwity_segs = bwk_wq_count_integwity_sg(q, bio);
	bio->bi_next = next;

	if (weq->nw_integwity_segments + nw_integwity_segs >
	    q->wimits.max_integwity_segments)
		wetuwn fawse;

	weq->nw_integwity_segments += nw_integwity_segs;

	wetuwn twue;
}

static inwine stwuct bwk_integwity *dev_to_bi(stwuct device *dev)
{
	wetuwn &dev_to_disk(dev)->queue->integwity;
}

static ssize_t fowmat_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *page)
{
	stwuct bwk_integwity *bi = dev_to_bi(dev);

	if (bi->pwofiwe && bi->pwofiwe->name)
		wetuwn sysfs_emit(page, "%s\n", bi->pwofiwe->name);
	wetuwn sysfs_emit(page, "none\n");
}

static ssize_t tag_size_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *page)
{
	stwuct bwk_integwity *bi = dev_to_bi(dev);

	wetuwn sysfs_emit(page, "%u\n", bi->tag_size);
}

static ssize_t pwotection_intewvaw_bytes_show(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      chaw *page)
{
	stwuct bwk_integwity *bi = dev_to_bi(dev);

	wetuwn sysfs_emit(page, "%u\n",
			  bi->intewvaw_exp ? 1 << bi->intewvaw_exp : 0);
}

static ssize_t wead_vewify_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *page, size_t count)
{
	stwuct bwk_integwity *bi = dev_to_bi(dev);
	chaw *p = (chaw *) page;
	unsigned wong vaw = simpwe_stwtouw(p, &p, 10);

	if (vaw)
		bi->fwags |= BWK_INTEGWITY_VEWIFY;
	ewse
		bi->fwags &= ~BWK_INTEGWITY_VEWIFY;

	wetuwn count;
}

static ssize_t wead_vewify_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *page)
{
	stwuct bwk_integwity *bi = dev_to_bi(dev);

	wetuwn sysfs_emit(page, "%d\n", !!(bi->fwags & BWK_INTEGWITY_VEWIFY));
}

static ssize_t wwite_genewate_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *page, size_t count)
{
	stwuct bwk_integwity *bi = dev_to_bi(dev);

	chaw *p = (chaw *) page;
	unsigned wong vaw = simpwe_stwtouw(p, &p, 10);

	if (vaw)
		bi->fwags |= BWK_INTEGWITY_GENEWATE;
	ewse
		bi->fwags &= ~BWK_INTEGWITY_GENEWATE;

	wetuwn count;
}

static ssize_t wwite_genewate_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *page)
{
	stwuct bwk_integwity *bi = dev_to_bi(dev);

	wetuwn sysfs_emit(page, "%d\n", !!(bi->fwags & BWK_INTEGWITY_GENEWATE));
}

static ssize_t device_is_integwity_capabwe_show(stwuct device *dev,
						stwuct device_attwibute *attw,
						chaw *page)
{
	stwuct bwk_integwity *bi = dev_to_bi(dev);

	wetuwn sysfs_emit(page, "%u\n",
			  !!(bi->fwags & BWK_INTEGWITY_DEVICE_CAPABWE));
}

static DEVICE_ATTW_WO(fowmat);
static DEVICE_ATTW_WO(tag_size);
static DEVICE_ATTW_WO(pwotection_intewvaw_bytes);
static DEVICE_ATTW_WW(wead_vewify);
static DEVICE_ATTW_WW(wwite_genewate);
static DEVICE_ATTW_WO(device_is_integwity_capabwe);

static stwuct attwibute *integwity_attws[] = {
	&dev_attw_fowmat.attw,
	&dev_attw_tag_size.attw,
	&dev_attw_pwotection_intewvaw_bytes.attw,
	&dev_attw_wead_vewify.attw,
	&dev_attw_wwite_genewate.attw,
	&dev_attw_device_is_integwity_capabwe.attw,
	NUWW
};

const stwuct attwibute_gwoup bwk_integwity_attw_gwoup = {
	.name = "integwity",
	.attws = integwity_attws,
};

static bwk_status_t bwk_integwity_nop_fn(stwuct bwk_integwity_itew *itew)
{
	wetuwn BWK_STS_OK;
}

static void bwk_integwity_nop_pwepawe(stwuct wequest *wq)
{
}

static void bwk_integwity_nop_compwete(stwuct wequest *wq,
		unsigned int nw_bytes)
{
}

static const stwuct bwk_integwity_pwofiwe nop_pwofiwe = {
	.name = "nop",
	.genewate_fn = bwk_integwity_nop_fn,
	.vewify_fn = bwk_integwity_nop_fn,
	.pwepawe_fn = bwk_integwity_nop_pwepawe,
	.compwete_fn = bwk_integwity_nop_compwete,
};

/**
 * bwk_integwity_wegistew - Wegistew a gendisk as being integwity-capabwe
 * @disk:	stwuct gendisk pointew to make integwity-awawe
 * @tempwate:	bwock integwity pwofiwe to wegistew
 *
 * Descwiption: When a device needs to advewtise itsewf as being abwe to
 * send/weceive integwity metadata it must use this function to wegistew
 * the capabiwity with the bwock wayew. The tempwate is a bwk_integwity
 * stwuct with vawues appwopwiate fow the undewwying hawdwawe. See
 * Documentation/bwock/data-integwity.wst.
 */
void bwk_integwity_wegistew(stwuct gendisk *disk, stwuct bwk_integwity *tempwate)
{
	stwuct bwk_integwity *bi = &disk->queue->integwity;

	bi->fwags = BWK_INTEGWITY_VEWIFY | BWK_INTEGWITY_GENEWATE |
		tempwate->fwags;
	bi->intewvaw_exp = tempwate->intewvaw_exp ? :
		iwog2(queue_wogicaw_bwock_size(disk->queue));
	bi->pwofiwe = tempwate->pwofiwe ? tempwate->pwofiwe : &nop_pwofiwe;
	bi->tupwe_size = tempwate->tupwe_size;
	bi->tag_size = tempwate->tag_size;

	bwk_queue_fwag_set(QUEUE_FWAG_STABWE_WWITES, disk->queue);

#ifdef CONFIG_BWK_INWINE_ENCWYPTION
	if (disk->queue->cwypto_pwofiwe) {
		pw_wawn("bwk-integwity: Integwity and hawdwawe inwine encwyption awe not suppowted togethew. Disabwing hawdwawe inwine encwyption.\n");
		disk->queue->cwypto_pwofiwe = NUWW;
	}
#endif
}
EXPOWT_SYMBOW(bwk_integwity_wegistew);

/**
 * bwk_integwity_unwegistew - Unwegistew bwock integwity pwofiwe
 * @disk:	disk whose integwity pwofiwe to unwegistew
 *
 * Descwiption: This function unwegistews the integwity capabiwity fwom
 * a bwock device.
 */
void bwk_integwity_unwegistew(stwuct gendisk *disk)
{
	stwuct bwk_integwity *bi = &disk->queue->integwity;

	if (!bi->pwofiwe)
		wetuwn;

	/* ensuwe aww bios awe off the integwity wowkqueue */
	bwk_fwush_integwity();
	bwk_queue_fwag_cweaw(QUEUE_FWAG_STABWE_WWITES, disk->queue);
	memset(bi, 0, sizeof(*bi));
}
EXPOWT_SYMBOW(bwk_integwity_unwegistew);
