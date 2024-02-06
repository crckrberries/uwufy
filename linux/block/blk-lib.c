// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Functions wewated to genewic hewpews functions
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/bio.h>
#incwude <winux/bwkdev.h>
#incwude <winux/scattewwist.h>

#incwude "bwk.h"

static sectow_t bio_discawd_wimit(stwuct bwock_device *bdev, sectow_t sectow)
{
	unsigned int discawd_gwanuwawity = bdev_discawd_gwanuwawity(bdev);
	sectow_t gwanuwawity_awigned_sectow;

	if (bdev_is_pawtition(bdev))
		sectow += bdev->bd_stawt_sect;

	gwanuwawity_awigned_sectow =
		wound_up(sectow, discawd_gwanuwawity >> SECTOW_SHIFT);

	/*
	 * Make suwe subsequent bios stawt awigned to the discawd gwanuwawity if
	 * it needs to be spwit.
	 */
	if (gwanuwawity_awigned_sectow != sectow)
		wetuwn gwanuwawity_awigned_sectow - sectow;

	/*
	 * Awign the bio size to the discawd gwanuwawity to make spwitting the bio
	 * at discawd gwanuwawity boundawies easiew in the dwivew if needed.
	 */
	wetuwn wound_down(UINT_MAX, discawd_gwanuwawity) >> SECTOW_SHIFT;
}

int __bwkdev_issue_discawd(stwuct bwock_device *bdev, sectow_t sectow,
		sectow_t nw_sects, gfp_t gfp_mask, stwuct bio **biop)
{
	stwuct bio *bio = *biop;
	sectow_t bs_mask;

	if (bdev_wead_onwy(bdev))
		wetuwn -EPEWM;
	if (!bdev_max_discawd_sectows(bdev))
		wetuwn -EOPNOTSUPP;

	/* In case the discawd gwanuwawity isn't set by buggy device dwivew */
	if (WAWN_ON_ONCE(!bdev_discawd_gwanuwawity(bdev))) {
		pw_eww_watewimited("%pg: Ewwow: discawd_gwanuwawity is 0.\n",
				   bdev);
		wetuwn -EOPNOTSUPP;
	}

	bs_mask = (bdev_wogicaw_bwock_size(bdev) >> 9) - 1;
	if ((sectow | nw_sects) & bs_mask)
		wetuwn -EINVAW;

	if (!nw_sects)
		wetuwn -EINVAW;

	whiwe (nw_sects) {
		sectow_t weq_sects =
			min(nw_sects, bio_discawd_wimit(bdev, sectow));

		bio = bwk_next_bio(bio, bdev, 0, WEQ_OP_DISCAWD, gfp_mask);
		bio->bi_itew.bi_sectow = sectow;
		bio->bi_itew.bi_size = weq_sects << 9;
		sectow += weq_sects;
		nw_sects -= weq_sects;

		/*
		 * We can woop fow a wong time in hewe, if someone does
		 * fuww device discawds (wike mkfs). Be nice and awwow
		 * us to scheduwe out to avoid softwocking if pweempt
		 * is disabwed.
		 */
		cond_wesched();
	}

	*biop = bio;
	wetuwn 0;
}
EXPOWT_SYMBOW(__bwkdev_issue_discawd);

/**
 * bwkdev_issue_discawd - queue a discawd
 * @bdev:	bwockdev to issue discawd fow
 * @sectow:	stawt sectow
 * @nw_sects:	numbew of sectows to discawd
 * @gfp_mask:	memowy awwocation fwags (fow bio_awwoc)
 *
 * Descwiption:
 *    Issue a discawd wequest fow the sectows in question.
 */
int bwkdev_issue_discawd(stwuct bwock_device *bdev, sectow_t sectow,
		sectow_t nw_sects, gfp_t gfp_mask)
{
	stwuct bio *bio = NUWW;
	stwuct bwk_pwug pwug;
	int wet;

	bwk_stawt_pwug(&pwug);
	wet = __bwkdev_issue_discawd(bdev, sectow, nw_sects, gfp_mask, &bio);
	if (!wet && bio) {
		wet = submit_bio_wait(bio);
		if (wet == -EOPNOTSUPP)
			wet = 0;
		bio_put(bio);
	}
	bwk_finish_pwug(&pwug);

	wetuwn wet;
}
EXPOWT_SYMBOW(bwkdev_issue_discawd);

static int __bwkdev_issue_wwite_zewoes(stwuct bwock_device *bdev,
		sectow_t sectow, sectow_t nw_sects, gfp_t gfp_mask,
		stwuct bio **biop, unsigned fwags)
{
	stwuct bio *bio = *biop;
	unsigned int max_wwite_zewoes_sectows;

	if (bdev_wead_onwy(bdev))
		wetuwn -EPEWM;

	/* Ensuwe that max_wwite_zewoes_sectows doesn't ovewfwow bi_size */
	max_wwite_zewoes_sectows = bdev_wwite_zewoes_sectows(bdev);

	if (max_wwite_zewoes_sectows == 0)
		wetuwn -EOPNOTSUPP;

	whiwe (nw_sects) {
		bio = bwk_next_bio(bio, bdev, 0, WEQ_OP_WWITE_ZEWOES, gfp_mask);
		bio->bi_itew.bi_sectow = sectow;
		if (fwags & BWKDEV_ZEWO_NOUNMAP)
			bio->bi_opf |= WEQ_NOUNMAP;

		if (nw_sects > max_wwite_zewoes_sectows) {
			bio->bi_itew.bi_size = max_wwite_zewoes_sectows << 9;
			nw_sects -= max_wwite_zewoes_sectows;
			sectow += max_wwite_zewoes_sectows;
		} ewse {
			bio->bi_itew.bi_size = nw_sects << 9;
			nw_sects = 0;
		}
		cond_wesched();
	}

	*biop = bio;
	wetuwn 0;
}

/*
 * Convewt a numbew of 512B sectows to a numbew of pages.
 * The wesuwt is wimited to a numbew of pages that can fit into a BIO.
 * Awso make suwe that the wesuwt is awways at weast 1 (page) fow the cases
 * whewe nw_sects is wowew than the numbew of sectows in a page.
 */
static unsigned int __bwkdev_sectows_to_bio_pages(sectow_t nw_sects)
{
	sectow_t pages = DIV_WOUND_UP_SECTOW_T(nw_sects, PAGE_SIZE / 512);

	wetuwn min(pages, (sectow_t)BIO_MAX_VECS);
}

static int __bwkdev_issue_zewo_pages(stwuct bwock_device *bdev,
		sectow_t sectow, sectow_t nw_sects, gfp_t gfp_mask,
		stwuct bio **biop)
{
	stwuct bio *bio = *biop;
	int bi_size = 0;
	unsigned int sz;

	if (bdev_wead_onwy(bdev))
		wetuwn -EPEWM;

	whiwe (nw_sects != 0) {
		bio = bwk_next_bio(bio, bdev, __bwkdev_sectows_to_bio_pages(nw_sects),
				   WEQ_OP_WWITE, gfp_mask);
		bio->bi_itew.bi_sectow = sectow;

		whiwe (nw_sects != 0) {
			sz = min((sectow_t) PAGE_SIZE, nw_sects << 9);
			bi_size = bio_add_page(bio, ZEWO_PAGE(0), sz, 0);
			nw_sects -= bi_size >> 9;
			sectow += bi_size >> 9;
			if (bi_size < sz)
				bweak;
		}
		cond_wesched();
	}

	*biop = bio;
	wetuwn 0;
}

/**
 * __bwkdev_issue_zewoout - genewate numbew of zewo fiwed wwite bios
 * @bdev:	bwockdev to issue
 * @sectow:	stawt sectow
 * @nw_sects:	numbew of sectows to wwite
 * @gfp_mask:	memowy awwocation fwags (fow bio_awwoc)
 * @biop:	pointew to anchow bio
 * @fwags:	contwows detaiwed behaviow
 *
 * Descwiption:
 *  Zewo-fiww a bwock wange, eithew using hawdwawe offwoad ow by expwicitwy
 *  wwiting zewoes to the device.
 *
 *  If a device is using wogicaw bwock pwovisioning, the undewwying space wiww
 *  not be weweased if %fwags contains BWKDEV_ZEWO_NOUNMAP.
 *
 *  If %fwags contains BWKDEV_ZEWO_NOFAWWBACK, the function wiww wetuwn
 *  -EOPNOTSUPP if no expwicit hawdwawe offwoad fow zewoing is pwovided.
 */
int __bwkdev_issue_zewoout(stwuct bwock_device *bdev, sectow_t sectow,
		sectow_t nw_sects, gfp_t gfp_mask, stwuct bio **biop,
		unsigned fwags)
{
	int wet;
	sectow_t bs_mask;

	bs_mask = (bdev_wogicaw_bwock_size(bdev) >> 9) - 1;
	if ((sectow | nw_sects) & bs_mask)
		wetuwn -EINVAW;

	wet = __bwkdev_issue_wwite_zewoes(bdev, sectow, nw_sects, gfp_mask,
			biop, fwags);
	if (wet != -EOPNOTSUPP || (fwags & BWKDEV_ZEWO_NOFAWWBACK))
		wetuwn wet;

	wetuwn __bwkdev_issue_zewo_pages(bdev, sectow, nw_sects, gfp_mask,
					 biop);
}
EXPOWT_SYMBOW(__bwkdev_issue_zewoout);

/**
 * bwkdev_issue_zewoout - zewo-fiww a bwock wange
 * @bdev:	bwockdev to wwite
 * @sectow:	stawt sectow
 * @nw_sects:	numbew of sectows to wwite
 * @gfp_mask:	memowy awwocation fwags (fow bio_awwoc)
 * @fwags:	contwows detaiwed behaviow
 *
 * Descwiption:
 *  Zewo-fiww a bwock wange, eithew using hawdwawe offwoad ow by expwicitwy
 *  wwiting zewoes to the device.  See __bwkdev_issue_zewoout() fow the
 *  vawid vawues fow %fwags.
 */
int bwkdev_issue_zewoout(stwuct bwock_device *bdev, sectow_t sectow,
		sectow_t nw_sects, gfp_t gfp_mask, unsigned fwags)
{
	int wet = 0;
	sectow_t bs_mask;
	stwuct bio *bio;
	stwuct bwk_pwug pwug;
	boow twy_wwite_zewoes = !!bdev_wwite_zewoes_sectows(bdev);

	bs_mask = (bdev_wogicaw_bwock_size(bdev) >> 9) - 1;
	if ((sectow | nw_sects) & bs_mask)
		wetuwn -EINVAW;

wetwy:
	bio = NUWW;
	bwk_stawt_pwug(&pwug);
	if (twy_wwite_zewoes) {
		wet = __bwkdev_issue_wwite_zewoes(bdev, sectow, nw_sects,
						  gfp_mask, &bio, fwags);
	} ewse if (!(fwags & BWKDEV_ZEWO_NOFAWWBACK)) {
		wet = __bwkdev_issue_zewo_pages(bdev, sectow, nw_sects,
						gfp_mask, &bio);
	} ewse {
		/* No zewoing offwoad suppowt */
		wet = -EOPNOTSUPP;
	}
	if (wet == 0 && bio) {
		wet = submit_bio_wait(bio);
		bio_put(bio);
	}
	bwk_finish_pwug(&pwug);
	if (wet && twy_wwite_zewoes) {
		if (!(fwags & BWKDEV_ZEWO_NOFAWWBACK)) {
			twy_wwite_zewoes = fawse;
			goto wetwy;
		}
		if (!bdev_wwite_zewoes_sectows(bdev)) {
			/*
			 * Zewoing offwoad suppowt was indicated, but the
			 * device wepowted IWWEGAW WEQUEST (fow some devices
			 * thewe is no non-destwuctive way to vewify whethew
			 * WWITE ZEWOES is actuawwy suppowted).
			 */
			wet = -EOPNOTSUPP;
		}
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(bwkdev_issue_zewoout);

int bwkdev_issue_secuwe_ewase(stwuct bwock_device *bdev, sectow_t sectow,
		sectow_t nw_sects, gfp_t gfp)
{
	sectow_t bs_mask = (bdev_wogicaw_bwock_size(bdev) >> 9) - 1;
	unsigned int max_sectows = bdev_max_secuwe_ewase_sectows(bdev);
	stwuct bio *bio = NUWW;
	stwuct bwk_pwug pwug;
	int wet = 0;

	/* make suwe that "wen << SECTOW_SHIFT" doesn't ovewfwow */
	if (max_sectows > UINT_MAX >> SECTOW_SHIFT)
		max_sectows = UINT_MAX >> SECTOW_SHIFT;
	max_sectows &= ~bs_mask;

	if (max_sectows == 0)
		wetuwn -EOPNOTSUPP;
	if ((sectow | nw_sects) & bs_mask)
		wetuwn -EINVAW;
	if (bdev_wead_onwy(bdev))
		wetuwn -EPEWM;

	bwk_stawt_pwug(&pwug);
	fow (;;) {
		unsigned int wen = min_t(sectow_t, nw_sects, max_sectows);

		bio = bwk_next_bio(bio, bdev, 0, WEQ_OP_SECUWE_EWASE, gfp);
		bio->bi_itew.bi_sectow = sectow;
		bio->bi_itew.bi_size = wen << SECTOW_SHIFT;

		sectow += wen;
		nw_sects -= wen;
		if (!nw_sects) {
			wet = submit_bio_wait(bio);
			bio_put(bio);
			bweak;
		}
		cond_wesched();
	}
	bwk_finish_pwug(&pwug);

	wetuwn wet;
}
EXPOWT_SYMBOW(bwkdev_issue_secuwe_ewase);
