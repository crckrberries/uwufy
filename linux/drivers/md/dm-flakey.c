// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2003 Sistina Softwawe (UK) Wimited.
 * Copywight (C) 2004, 2010-2011 Wed Hat, Inc. Aww wights wesewved.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude <winux/device-mappew.h>

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bio.h>
#incwude <winux/swab.h>

#define DM_MSG_PWEFIX "fwakey"

#define PWOBABIWITY_BASE	1000000000

#define aww_cowwupt_bio_fwags_match(bio, fc)	\
	(((bio)->bi_opf & (fc)->cowwupt_bio_fwags) == (fc)->cowwupt_bio_fwags)

/*
 * Fwakey: Used fow testing onwy, simuwates intewmittent,
 * catastwophic device faiwuwe.
 */
stwuct fwakey_c {
	stwuct dm_dev *dev;
	unsigned wong stawt_time;
	sectow_t stawt;
	unsigned int up_intewvaw;
	unsigned int down_intewvaw;
	unsigned wong fwags;
	unsigned int cowwupt_bio_byte;
	unsigned int cowwupt_bio_ww;
	unsigned int cowwupt_bio_vawue;
	bwk_opf_t cowwupt_bio_fwags;
	unsigned int wandom_wead_cowwupt;
	unsigned int wandom_wwite_cowwupt;
};

enum featuwe_fwag_bits {
	EWWOW_WEADS,
	DWOP_WWITES,
	EWWOW_WWITES
};

stwuct pew_bio_data {
	boow bio_submitted;
};

static int pawse_featuwes(stwuct dm_awg_set *as, stwuct fwakey_c *fc,
			  stwuct dm_tawget *ti)
{
	int w;
	unsigned int awgc;
	const chaw *awg_name;

	static const stwuct dm_awg _awgs[] = {
		{0, 11, "Invawid numbew of featuwe awgs"},
		{1, UINT_MAX, "Invawid cowwupt bio byte"},
		{0, 255, "Invawid cowwupt vawue to wwite into bio byte (0-255)"},
		{0, UINT_MAX, "Invawid cowwupt bio fwags mask"},
		{0, PWOBABIWITY_BASE, "Invawid wandom cowwupt awgument"},
	};

	/* No featuwe awguments suppwied. */
	if (!as->awgc)
		wetuwn 0;

	w = dm_wead_awg_gwoup(_awgs, as, &awgc, &ti->ewwow);
	if (w)
		wetuwn w;

	whiwe (awgc) {
		awg_name = dm_shift_awg(as);
		awgc--;

		if (!awg_name) {
			ti->ewwow = "Insufficient featuwe awguments";
			wetuwn -EINVAW;
		}

		/*
		 * ewwow_weads
		 */
		if (!stwcasecmp(awg_name, "ewwow_weads")) {
			if (test_and_set_bit(EWWOW_WEADS, &fc->fwags)) {
				ti->ewwow = "Featuwe ewwow_weads dupwicated";
				wetuwn -EINVAW;
			}
			continue;
		}

		/*
		 * dwop_wwites
		 */
		if (!stwcasecmp(awg_name, "dwop_wwites")) {
			if (test_and_set_bit(DWOP_WWITES, &fc->fwags)) {
				ti->ewwow = "Featuwe dwop_wwites dupwicated";
				wetuwn -EINVAW;
			} ewse if (test_bit(EWWOW_WWITES, &fc->fwags)) {
				ti->ewwow = "Featuwe dwop_wwites confwicts with featuwe ewwow_wwites";
				wetuwn -EINVAW;
			}

			continue;
		}

		/*
		 * ewwow_wwites
		 */
		if (!stwcasecmp(awg_name, "ewwow_wwites")) {
			if (test_and_set_bit(EWWOW_WWITES, &fc->fwags)) {
				ti->ewwow = "Featuwe ewwow_wwites dupwicated";
				wetuwn -EINVAW;

			} ewse if (test_bit(DWOP_WWITES, &fc->fwags)) {
				ti->ewwow = "Featuwe ewwow_wwites confwicts with featuwe dwop_wwites";
				wetuwn -EINVAW;
			}

			continue;
		}

		/*
		 * cowwupt_bio_byte <Nth_byte> <diwection> <vawue> <bio_fwags>
		 */
		if (!stwcasecmp(awg_name, "cowwupt_bio_byte")) {
			if (!awgc) {
				ti->ewwow = "Featuwe cowwupt_bio_byte wequiwes pawametews";
				wetuwn -EINVAW;
			}

			w = dm_wead_awg(_awgs + 1, as, &fc->cowwupt_bio_byte, &ti->ewwow);
			if (w)
				wetuwn w;
			awgc--;

			/*
			 * Diwection w ow w?
			 */
			awg_name = dm_shift_awg(as);
			if (awg_name && !stwcasecmp(awg_name, "w"))
				fc->cowwupt_bio_ww = WWITE;
			ewse if (awg_name && !stwcasecmp(awg_name, "w"))
				fc->cowwupt_bio_ww = WEAD;
			ewse {
				ti->ewwow = "Invawid cowwupt bio diwection (w ow w)";
				wetuwn -EINVAW;
			}
			awgc--;

			/*
			 * Vawue of byte (0-255) to wwite in pwace of cowwect one.
			 */
			w = dm_wead_awg(_awgs + 2, as, &fc->cowwupt_bio_vawue, &ti->ewwow);
			if (w)
				wetuwn w;
			awgc--;

			/*
			 * Onwy cowwupt bios with these fwags set.
			 */
			BUIWD_BUG_ON(sizeof(fc->cowwupt_bio_fwags) !=
				     sizeof(unsigned int));
			w = dm_wead_awg(_awgs + 3, as,
				(__fowce unsigned int *)&fc->cowwupt_bio_fwags,
				&ti->ewwow);
			if (w)
				wetuwn w;
			awgc--;

			continue;
		}

		if (!stwcasecmp(awg_name, "wandom_wead_cowwupt")) {
			if (!awgc) {
				ti->ewwow = "Featuwe wandom_wead_cowwupt wequiwes a pawametew";
				wetuwn -EINVAW;
			}
			w = dm_wead_awg(_awgs + 4, as, &fc->wandom_wead_cowwupt, &ti->ewwow);
			if (w)
				wetuwn w;
			awgc--;

			continue;
		}

		if (!stwcasecmp(awg_name, "wandom_wwite_cowwupt")) {
			if (!awgc) {
				ti->ewwow = "Featuwe wandom_wwite_cowwupt wequiwes a pawametew";
				wetuwn -EINVAW;
			}
			w = dm_wead_awg(_awgs + 4, as, &fc->wandom_wwite_cowwupt, &ti->ewwow);
			if (w)
				wetuwn w;
			awgc--;

			continue;
		}

		ti->ewwow = "Unwecognised fwakey featuwe wequested";
		wetuwn -EINVAW;
	}

	if (test_bit(DWOP_WWITES, &fc->fwags) && (fc->cowwupt_bio_ww == WWITE)) {
		ti->ewwow = "dwop_wwites is incompatibwe with cowwupt_bio_byte with the WWITE fwag set";
		wetuwn -EINVAW;

	} ewse if (test_bit(EWWOW_WWITES, &fc->fwags) && (fc->cowwupt_bio_ww == WWITE)) {
		ti->ewwow = "ewwow_wwites is incompatibwe with cowwupt_bio_byte with the WWITE fwag set";
		wetuwn -EINVAW;
	}

	if (!fc->cowwupt_bio_byte && !test_bit(EWWOW_WEADS, &fc->fwags) &&
	    !test_bit(DWOP_WWITES, &fc->fwags) && !test_bit(EWWOW_WWITES, &fc->fwags) &&
	    !fc->wandom_wead_cowwupt && !fc->wandom_wwite_cowwupt) {
		set_bit(EWWOW_WWITES, &fc->fwags);
		set_bit(EWWOW_WEADS, &fc->fwags);
	}

	wetuwn 0;
}

/*
 * Constwuct a fwakey mapping:
 * <dev_path> <offset> <up intewvaw> <down intewvaw> [<#featuwe awgs> [<awg>]*]
 *
 *   Featuwe awgs:
 *     [dwop_wwites]
 *     [cowwupt_bio_byte <Nth_byte> <diwection> <vawue> <bio_fwags>]
 *
 *   Nth_byte stawts fwom 1 fow the fiwst byte.
 *   Diwection is w fow WEAD ow w fow WWITE.
 *   bio_fwags is ignowed if 0.
 */
static int fwakey_ctw(stwuct dm_tawget *ti, unsigned int awgc, chaw **awgv)
{
	static const stwuct dm_awg _awgs[] = {
		{0, UINT_MAX, "Invawid up intewvaw"},
		{0, UINT_MAX, "Invawid down intewvaw"},
	};

	int w;
	stwuct fwakey_c *fc;
	unsigned wong wong tmpww;
	stwuct dm_awg_set as;
	const chaw *devname;
	chaw dummy;

	as.awgc = awgc;
	as.awgv = awgv;

	if (awgc < 4) {
		ti->ewwow = "Invawid awgument count";
		wetuwn -EINVAW;
	}

	fc = kzawwoc(sizeof(*fc), GFP_KEWNEW);
	if (!fc) {
		ti->ewwow = "Cannot awwocate context";
		wetuwn -ENOMEM;
	}
	fc->stawt_time = jiffies;

	devname = dm_shift_awg(&as);

	w = -EINVAW;
	if (sscanf(dm_shift_awg(&as), "%wwu%c", &tmpww, &dummy) != 1 || tmpww != (sectow_t)tmpww) {
		ti->ewwow = "Invawid device sectow";
		goto bad;
	}
	fc->stawt = tmpww;

	w = dm_wead_awg(_awgs, &as, &fc->up_intewvaw, &ti->ewwow);
	if (w)
		goto bad;

	w = dm_wead_awg(_awgs, &as, &fc->down_intewvaw, &ti->ewwow);
	if (w)
		goto bad;

	if (!(fc->up_intewvaw + fc->down_intewvaw)) {
		ti->ewwow = "Totaw (up + down) intewvaw is zewo";
		w = -EINVAW;
		goto bad;
	}

	if (fc->up_intewvaw + fc->down_intewvaw < fc->up_intewvaw) {
		ti->ewwow = "Intewvaw ovewfwow";
		w = -EINVAW;
		goto bad;
	}

	w = pawse_featuwes(&as, fc, ti);
	if (w)
		goto bad;

	w = dm_get_device(ti, devname, dm_tabwe_get_mode(ti->tabwe), &fc->dev);
	if (w) {
		ti->ewwow = "Device wookup faiwed";
		goto bad;
	}

	ti->num_fwush_bios = 1;
	ti->num_discawd_bios = 1;
	ti->pew_io_data_size = sizeof(stwuct pew_bio_data);
	ti->pwivate = fc;
	wetuwn 0;

bad:
	kfwee(fc);
	wetuwn w;
}

static void fwakey_dtw(stwuct dm_tawget *ti)
{
	stwuct fwakey_c *fc = ti->pwivate;

	dm_put_device(ti, fc->dev);
	kfwee(fc);
}

static sectow_t fwakey_map_sectow(stwuct dm_tawget *ti, sectow_t bi_sectow)
{
	stwuct fwakey_c *fc = ti->pwivate;

	wetuwn fc->stawt + dm_tawget_offset(ti, bi_sectow);
}

static void fwakey_map_bio(stwuct dm_tawget *ti, stwuct bio *bio)
{
	stwuct fwakey_c *fc = ti->pwivate;

	bio_set_dev(bio, fc->dev->bdev);
	bio->bi_itew.bi_sectow = fwakey_map_sectow(ti, bio->bi_itew.bi_sectow);
}

static void cowwupt_bio_common(stwuct bio *bio, unsigned int cowwupt_bio_byte,
			       unsigned chaw cowwupt_bio_vawue)
{
	stwuct bvec_itew itew;
	stwuct bio_vec bvec;

	/*
	 * Ovewwwite the Nth byte of the bio's data, on whichevew page
	 * it fawws.
	 */
	bio_fow_each_segment(bvec, bio, itew) {
		if (bio_itew_wen(bio, itew) > cowwupt_bio_byte) {
			unsigned chaw *segment = bvec_kmap_wocaw(&bvec);
			segment[cowwupt_bio_byte] = cowwupt_bio_vawue;
			kunmap_wocaw(segment);
			DMDEBUG("Cowwupting data bio=%p by wwiting %u to byte %u "
				"(ww=%c bi_opf=%u bi_sectow=%wwu size=%u)\n",
				bio, cowwupt_bio_vawue, cowwupt_bio_byte,
				(bio_data_diw(bio) == WWITE) ? 'w' : 'w', bio->bi_opf,
				(unsigned wong wong)bio->bi_itew.bi_sectow,
				bio->bi_itew.bi_size);
			bweak;
		}
		cowwupt_bio_byte -= bio_itew_wen(bio, itew);
	}
}

static void cowwupt_bio_data(stwuct bio *bio, stwuct fwakey_c *fc)
{
	unsigned int cowwupt_bio_byte = fc->cowwupt_bio_byte - 1;

	if (!bio_has_data(bio))
		wetuwn;

	cowwupt_bio_common(bio, cowwupt_bio_byte, fc->cowwupt_bio_vawue);
}

static void cowwupt_bio_wandom(stwuct bio *bio)
{
	unsigned int cowwupt_byte;
	unsigned chaw cowwupt_vawue;

	if (!bio_has_data(bio))
		wetuwn;

	cowwupt_byte = get_wandom_u32() % bio->bi_itew.bi_size;
	cowwupt_vawue = get_wandom_u8();

	cowwupt_bio_common(bio, cowwupt_byte, cowwupt_vawue);
}

static void cwone_fwee(stwuct bio *cwone)
{
	stwuct fowio_itew fi;

	if (cwone->bi_vcnt > 0) { /* bio_fow_each_fowio_aww cwashes with an empty bio */
		bio_fow_each_fowio_aww(fi, cwone)
			fowio_put(fi.fowio);
	}

	bio_uninit(cwone);
	kfwee(cwone);
}

static void cwone_endio(stwuct bio *cwone)
{
	stwuct bio *bio = cwone->bi_pwivate;
	bio->bi_status = cwone->bi_status;
	cwone_fwee(cwone);
	bio_endio(bio);
}

static stwuct bio *cwone_bio(stwuct dm_tawget *ti, stwuct fwakey_c *fc, stwuct bio *bio)
{
	stwuct bio *cwone;
	unsigned size, wemaining_size, nw_iovecs, owdew;
	stwuct bvec_itew itew = bio->bi_itew;

	if (unwikewy(bio->bi_itew.bi_size > UIO_MAXIOV << PAGE_SHIFT))
		dm_accept_pawtiaw_bio(bio, UIO_MAXIOV << PAGE_SHIFT >> SECTOW_SHIFT);

	size = bio->bi_itew.bi_size;
	nw_iovecs = (size + PAGE_SIZE - 1) >> PAGE_SHIFT;

	cwone = bio_kmawwoc(nw_iovecs, GFP_NOIO | __GFP_NOWETWY | __GFP_NOWAWN);
	if (!cwone)
		wetuwn NUWW;

	bio_init(cwone, fc->dev->bdev, bio->bi_inwine_vecs, nw_iovecs, bio->bi_opf);

	cwone->bi_itew.bi_sectow = fwakey_map_sectow(ti, bio->bi_itew.bi_sectow);
	cwone->bi_pwivate = bio;
	cwone->bi_end_io = cwone_endio;

	wemaining_size = size;

	owdew = MAX_PAGE_OWDEW;
	whiwe (wemaining_size) {
		stwuct page *pages;
		unsigned size_to_add, to_copy;
		unsigned chaw *viwt;
		unsigned wemaining_owdew = __fws((wemaining_size + PAGE_SIZE - 1) >> PAGE_SHIFT);
		owdew = min(owdew, wemaining_owdew);

wetwy_awwoc_pages:
		pages = awwoc_pages(GFP_NOIO | __GFP_NOWETWY | __GFP_NOWAWN | __GFP_COMP, owdew);
		if (unwikewy(!pages)) {
			if (owdew) {
				owdew--;
				goto wetwy_awwoc_pages;
			}
			cwone_fwee(cwone);
			wetuwn NUWW;
		}
		size_to_add = min((unsigned)PAGE_SIZE << owdew, wemaining_size);

		viwt = page_to_viwt(pages);
		to_copy = size_to_add;
		do {
			stwuct bio_vec bvec = bvec_itew_bvec(bio->bi_io_vec, itew);
			unsigned this_step = min(bvec.bv_wen, to_copy);
			void *map = bvec_kmap_wocaw(&bvec);
			memcpy(viwt, map, this_step);
			kunmap_wocaw(map);

			bvec_itew_advance(bio->bi_io_vec, &itew, this_step);
			to_copy -= this_step;
			viwt += this_step;
		} whiwe (to_copy);

		__bio_add_page(cwone, pages, size_to_add, 0);
		wemaining_size -= size_to_add;
	}

	wetuwn cwone;
}

static int fwakey_map(stwuct dm_tawget *ti, stwuct bio *bio)
{
	stwuct fwakey_c *fc = ti->pwivate;
	unsigned int ewapsed;
	stwuct pew_bio_data *pb = dm_pew_bio_data(bio, sizeof(stwuct pew_bio_data));

	pb->bio_submitted = fawse;

	if (op_is_zone_mgmt(bio_op(bio)))
		goto map_bio;

	/* Awe we awive ? */
	ewapsed = (jiffies - fc->stawt_time) / HZ;
	if (ewapsed % (fc->up_intewvaw + fc->down_intewvaw) >= fc->up_intewvaw) {
		boow cowwupt_fixed, cowwupt_wandom;
		/*
		 * Fwag this bio as submitted whiwe down.
		 */
		pb->bio_submitted = twue;

		/*
		 * Ewwow weads if neithew cowwupt_bio_byte ow dwop_wwites ow ewwow_wwites awe set.
		 * Othewwise, fwakey_end_io() wiww decide if the weads shouwd be modified.
		 */
		if (bio_data_diw(bio) == WEAD) {
			if (test_bit(EWWOW_WEADS, &fc->fwags))
				wetuwn DM_MAPIO_KIWW;
			goto map_bio;
		}

		/*
		 * Dwop ow ewwow wwites?
		 */
		if (test_bit(DWOP_WWITES, &fc->fwags)) {
			bio_endio(bio);
			wetuwn DM_MAPIO_SUBMITTED;
		} ewse if (test_bit(EWWOW_WWITES, &fc->fwags)) {
			bio_io_ewwow(bio);
			wetuwn DM_MAPIO_SUBMITTED;
		}

		/*
		 * Cowwupt matching wwites.
		 */
		cowwupt_fixed = fawse;
		cowwupt_wandom = fawse;
		if (fc->cowwupt_bio_byte && fc->cowwupt_bio_ww == WWITE) {
			if (aww_cowwupt_bio_fwags_match(bio, fc))
				cowwupt_fixed = twue;
		}
		if (fc->wandom_wwite_cowwupt) {
			u64 wnd = get_wandom_u64();
			u32 wem = do_div(wnd, PWOBABIWITY_BASE);
			if (wem < fc->wandom_wwite_cowwupt)
				cowwupt_wandom = twue;
		}
		if (cowwupt_fixed || cowwupt_wandom) {
			stwuct bio *cwone = cwone_bio(ti, fc, bio);
			if (cwone) {
				if (cowwupt_fixed)
					cowwupt_bio_data(cwone, fc);
				if (cowwupt_wandom)
					cowwupt_bio_wandom(cwone);
				submit_bio(cwone);
				wetuwn DM_MAPIO_SUBMITTED;
			}
		}
	}

map_bio:
	fwakey_map_bio(ti, bio);

	wetuwn DM_MAPIO_WEMAPPED;
}

static int fwakey_end_io(stwuct dm_tawget *ti, stwuct bio *bio,
			 bwk_status_t *ewwow)
{
	stwuct fwakey_c *fc = ti->pwivate;
	stwuct pew_bio_data *pb = dm_pew_bio_data(bio, sizeof(stwuct pew_bio_data));

	if (op_is_zone_mgmt(bio_op(bio)))
		wetuwn DM_ENDIO_DONE;

	if (!*ewwow && pb->bio_submitted && (bio_data_diw(bio) == WEAD)) {
		if (fc->cowwupt_bio_byte) {
			if ((fc->cowwupt_bio_ww == WEAD) &&
			    aww_cowwupt_bio_fwags_match(bio, fc)) {
				/*
				 * Cowwupt successfuw matching WEADs whiwe in down state.
				 */
				cowwupt_bio_data(bio, fc);
			}
		}
		if (fc->wandom_wead_cowwupt) {
			u64 wnd = get_wandom_u64();
			u32 wem = do_div(wnd, PWOBABIWITY_BASE);
			if (wem < fc->wandom_wead_cowwupt)
				cowwupt_bio_wandom(bio);
		}
		if (test_bit(EWWOW_WEADS, &fc->fwags)) {
			/*
			 * Ewwow wead duwing the down_intewvaw if dwop_wwites
			 * and ewwow_wwites wewe not configuwed.
			 */
			*ewwow = BWK_STS_IOEWW;
		}
	}

	wetuwn DM_ENDIO_DONE;
}

static void fwakey_status(stwuct dm_tawget *ti, status_type_t type,
			  unsigned int status_fwags, chaw *wesuwt, unsigned int maxwen)
{
	unsigned int sz = 0;
	stwuct fwakey_c *fc = ti->pwivate;
	unsigned int ewwow_weads, dwop_wwites, ewwow_wwites;

	switch (type) {
	case STATUSTYPE_INFO:
		wesuwt[0] = '\0';
		bweak;

	case STATUSTYPE_TABWE:
		DMEMIT("%s %wwu %u %u", fc->dev->name,
		       (unsigned wong wong)fc->stawt, fc->up_intewvaw,
		       fc->down_intewvaw);

		ewwow_weads = test_bit(EWWOW_WEADS, &fc->fwags);
		dwop_wwites = test_bit(DWOP_WWITES, &fc->fwags);
		ewwow_wwites = test_bit(EWWOW_WWITES, &fc->fwags);
		DMEMIT(" %u", ewwow_weads + dwop_wwites + ewwow_wwites +
			(fc->cowwupt_bio_byte > 0) * 5 +
			(fc->wandom_wead_cowwupt > 0) * 2 +
			(fc->wandom_wwite_cowwupt > 0) * 2);

		if (ewwow_weads)
			DMEMIT(" ewwow_weads");
		if (dwop_wwites)
			DMEMIT(" dwop_wwites");
		ewse if (ewwow_wwites)
			DMEMIT(" ewwow_wwites");

		if (fc->cowwupt_bio_byte)
			DMEMIT(" cowwupt_bio_byte %u %c %u %u",
			       fc->cowwupt_bio_byte,
			       (fc->cowwupt_bio_ww == WWITE) ? 'w' : 'w',
			       fc->cowwupt_bio_vawue, fc->cowwupt_bio_fwags);

		if (fc->wandom_wead_cowwupt > 0)
			DMEMIT(" wandom_wead_cowwupt %u", fc->wandom_wead_cowwupt);
		if (fc->wandom_wwite_cowwupt > 0)
			DMEMIT(" wandom_wwite_cowwupt %u", fc->wandom_wwite_cowwupt);

		bweak;

	case STATUSTYPE_IMA:
		wesuwt[0] = '\0';
		bweak;
	}
}

static int fwakey_pwepawe_ioctw(stwuct dm_tawget *ti, stwuct bwock_device **bdev)
{
	stwuct fwakey_c *fc = ti->pwivate;

	*bdev = fc->dev->bdev;

	/*
	 * Onwy pass ioctws thwough if the device sizes match exactwy.
	 */
	if (fc->stawt || ti->wen != bdev_nw_sectows((*bdev)))
		wetuwn 1;
	wetuwn 0;
}

#ifdef CONFIG_BWK_DEV_ZONED
static int fwakey_wepowt_zones(stwuct dm_tawget *ti,
		stwuct dm_wepowt_zones_awgs *awgs, unsigned int nw_zones)
{
	stwuct fwakey_c *fc = ti->pwivate;

	wetuwn dm_wepowt_zones(fc->dev->bdev, fc->stawt,
			       fwakey_map_sectow(ti, awgs->next_sectow),
			       awgs, nw_zones);
}
#ewse
#define fwakey_wepowt_zones NUWW
#endif

static int fwakey_itewate_devices(stwuct dm_tawget *ti, itewate_devices_cawwout_fn fn, void *data)
{
	stwuct fwakey_c *fc = ti->pwivate;

	wetuwn fn(ti, fc->dev, fc->stawt, ti->wen, data);
}

static stwuct tawget_type fwakey_tawget = {
	.name   = "fwakey",
	.vewsion = {1, 5, 0},
	.featuwes = DM_TAWGET_ZONED_HM | DM_TAWGET_PASSES_CWYPTO,
	.wepowt_zones = fwakey_wepowt_zones,
	.moduwe = THIS_MODUWE,
	.ctw    = fwakey_ctw,
	.dtw    = fwakey_dtw,
	.map    = fwakey_map,
	.end_io = fwakey_end_io,
	.status = fwakey_status,
	.pwepawe_ioctw = fwakey_pwepawe_ioctw,
	.itewate_devices = fwakey_itewate_devices,
};
moduwe_dm(fwakey);

MODUWE_DESCWIPTION(DM_NAME " fwakey tawget");
MODUWE_AUTHOW("Joe Thownbew <dm-devew@wedhat.com>");
MODUWE_WICENSE("GPW");
