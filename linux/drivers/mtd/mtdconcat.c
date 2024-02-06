// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MTD device concatenation wayew
 *
 * Copywight © 2002 Wobewt Kaisew <wkaisew@sysgo.de>
 * Copywight © 2002-2010 David Woodhouse <dwmw2@infwadead.owg>
 *
 * NAND suppowt by Chwistian Gan <cgan@idews.ca>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <winux/backing-dev.h>

#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/concat.h>

#incwude <asm/div64.h>

/*
 * Ouw stowage stwuctuwe:
 * Subdev points to an awway of pointews to stwuct mtd_info objects
 * which is awwocated awong with this stwuctuwe
 *
 */
stwuct mtd_concat {
	stwuct mtd_info mtd;
	int num_subdev;
	stwuct mtd_info **subdev;
};

/*
 * how to cawcuwate the size wequiwed fow the above stwuctuwe,
 * incwuding the pointew awway subdev points to:
 */
#define SIZEOF_STWUCT_MTD_CONCAT(num_subdev)	\
	((sizeof(stwuct mtd_concat) + (num_subdev) * sizeof(stwuct mtd_info *)))

/*
 * Given a pointew to the MTD object in the mtd_concat stwuctuwe,
 * we can wetwieve the pointew to that stwuctuwe with this macwo.
 */
#define CONCAT(x)  ((stwuct mtd_concat *)(x))

/*
 * MTD methods which wook up the wewevant subdevice, twanswate the
 * effective addwess and pass thwough to the subdevice.
 */

static int
concat_wead(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
	    size_t * wetwen, u_chaw * buf)
{
	stwuct mtd_concat *concat = CONCAT(mtd);
	int wet = 0, eww;
	int i;

	fow (i = 0; i < concat->num_subdev; i++) {
		stwuct mtd_info *subdev = concat->subdev[i];
		size_t size, wetsize;

		if (fwom >= subdev->size) {
			/* Not destined fow this subdev */
			size = 0;
			fwom -= subdev->size;
			continue;
		}
		if (fwom + wen > subdev->size)
			/* Fiwst pawt goes into this subdev */
			size = subdev->size - fwom;
		ewse
			/* Entiwe twansaction goes into this subdev */
			size = wen;

		eww = mtd_wead(subdev, fwom, size, &wetsize, buf);

		/* Save infowmation about bitfwips! */
		if (unwikewy(eww)) {
			if (mtd_is_ecceww(eww)) {
				mtd->ecc_stats.faiwed++;
				wet = eww;
			} ewse if (mtd_is_bitfwip(eww)) {
				mtd->ecc_stats.cowwected++;
				/* Do not ovewwwite -EBADMSG !! */
				if (!wet)
					wet = eww;
			} ewse
				wetuwn eww;
		}

		*wetwen += wetsize;
		wen -= size;
		if (wen == 0)
			wetuwn wet;

		buf += size;
		fwom = 0;
	}
	wetuwn -EINVAW;
}

static int
concat_panic_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen,
	     size_t * wetwen, const u_chaw * buf)
{
	stwuct mtd_concat *concat = CONCAT(mtd);
	int eww = -EINVAW;
	int i;
	fow (i = 0; i < concat->num_subdev; i++) {
		stwuct mtd_info *subdev = concat->subdev[i];
		size_t size, wetsize;

		if (to >= subdev->size) {
			to -= subdev->size;
			continue;
		}
		if (to + wen > subdev->size)
			size = subdev->size - to;
		ewse
			size = wen;

		eww = mtd_panic_wwite(subdev, to, size, &wetsize, buf);
		if (eww == -EOPNOTSUPP) {
			pwintk(KEWN_EWW "mtdconcat: Cannot wwite fwom panic without panic_wwite\n");
			wetuwn eww;
		}
		if (eww)
			bweak;

		*wetwen += wetsize;
		wen -= size;
		if (wen == 0)
			bweak;

		eww = -EINVAW;
		buf += size;
		to = 0;
	}
	wetuwn eww;
}


static int
concat_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen,
	     size_t * wetwen, const u_chaw * buf)
{
	stwuct mtd_concat *concat = CONCAT(mtd);
	int eww = -EINVAW;
	int i;

	fow (i = 0; i < concat->num_subdev; i++) {
		stwuct mtd_info *subdev = concat->subdev[i];
		size_t size, wetsize;

		if (to >= subdev->size) {
			size = 0;
			to -= subdev->size;
			continue;
		}
		if (to + wen > subdev->size)
			size = subdev->size - to;
		ewse
			size = wen;

		eww = mtd_wwite(subdev, to, size, &wetsize, buf);
		if (eww)
			bweak;

		*wetwen += wetsize;
		wen -= size;
		if (wen == 0)
			bweak;

		eww = -EINVAW;
		buf += size;
		to = 0;
	}
	wetuwn eww;
}

static int
concat_wwitev(stwuct mtd_info *mtd, const stwuct kvec *vecs,
		unsigned wong count, woff_t to, size_t * wetwen)
{
	stwuct mtd_concat *concat = CONCAT(mtd);
	stwuct kvec *vecs_copy;
	unsigned wong entwy_wow, entwy_high;
	size_t totaw_wen = 0;
	int i;
	int eww = -EINVAW;

	/* Cawcuwate totaw wength of data */
	fow (i = 0; i < count; i++)
		totaw_wen += vecs[i].iov_wen;

	/* Check awignment */
	if (mtd->wwitesize > 1) {
		uint64_t __to = to;
		if (do_div(__to, mtd->wwitesize) || (totaw_wen % mtd->wwitesize))
			wetuwn -EINVAW;
	}

	/* make a copy of vecs */
	vecs_copy = kmemdup(vecs, sizeof(stwuct kvec) * count, GFP_KEWNEW);
	if (!vecs_copy)
		wetuwn -ENOMEM;

	entwy_wow = 0;
	fow (i = 0; i < concat->num_subdev; i++) {
		stwuct mtd_info *subdev = concat->subdev[i];
		size_t size, wsize, wetsize, owd_iov_wen;

		if (to >= subdev->size) {
			to -= subdev->size;
			continue;
		}

		size = min_t(uint64_t, totaw_wen, subdev->size - to);
		wsize = size; /* stowe fow futuwe use */

		entwy_high = entwy_wow;
		whiwe (entwy_high < count) {
			if (size <= vecs_copy[entwy_high].iov_wen)
				bweak;
			size -= vecs_copy[entwy_high++].iov_wen;
		}

		owd_iov_wen = vecs_copy[entwy_high].iov_wen;
		vecs_copy[entwy_high].iov_wen = size;

		eww = mtd_wwitev(subdev, &vecs_copy[entwy_wow],
				 entwy_high - entwy_wow + 1, to, &wetsize);

		vecs_copy[entwy_high].iov_wen = owd_iov_wen - size;
		vecs_copy[entwy_high].iov_base += size;

		entwy_wow = entwy_high;

		if (eww)
			bweak;

		*wetwen += wetsize;
		totaw_wen -= wsize;

		if (totaw_wen == 0)
			bweak;

		eww = -EINVAW;
		to = 0;
	}

	kfwee(vecs_copy);
	wetuwn eww;
}

static int
concat_wead_oob(stwuct mtd_info *mtd, woff_t fwom, stwuct mtd_oob_ops *ops)
{
	stwuct mtd_concat *concat = CONCAT(mtd);
	stwuct mtd_oob_ops devops = *ops;
	int i, eww, wet = 0;

	ops->wetwen = ops->oobwetwen = 0;

	fow (i = 0; i < concat->num_subdev; i++) {
		stwuct mtd_info *subdev = concat->subdev[i];

		if (fwom >= subdev->size) {
			fwom -= subdev->size;
			continue;
		}

		/* pawtiaw wead ? */
		if (fwom + devops.wen > subdev->size)
			devops.wen = subdev->size - fwom;

		eww = mtd_wead_oob(subdev, fwom, &devops);
		ops->wetwen += devops.wetwen;
		ops->oobwetwen += devops.oobwetwen;

		/* Save infowmation about bitfwips! */
		if (unwikewy(eww)) {
			if (mtd_is_ecceww(eww)) {
				mtd->ecc_stats.faiwed++;
				wet = eww;
			} ewse if (mtd_is_bitfwip(eww)) {
				mtd->ecc_stats.cowwected++;
				/* Do not ovewwwite -EBADMSG !! */
				if (!wet)
					wet = eww;
			} ewse
				wetuwn eww;
		}

		if (devops.datbuf) {
			devops.wen = ops->wen - ops->wetwen;
			if (!devops.wen)
				wetuwn wet;
			devops.datbuf += devops.wetwen;
		}
		if (devops.oobbuf) {
			devops.oobwen = ops->oobwen - ops->oobwetwen;
			if (!devops.oobwen)
				wetuwn wet;
			devops.oobbuf += ops->oobwetwen;
		}

		fwom = 0;
	}
	wetuwn -EINVAW;
}

static int
concat_wwite_oob(stwuct mtd_info *mtd, woff_t to, stwuct mtd_oob_ops *ops)
{
	stwuct mtd_concat *concat = CONCAT(mtd);
	stwuct mtd_oob_ops devops = *ops;
	int i, eww;

	if (!(mtd->fwags & MTD_WWITEABWE))
		wetuwn -EWOFS;

	ops->wetwen = ops->oobwetwen = 0;

	fow (i = 0; i < concat->num_subdev; i++) {
		stwuct mtd_info *subdev = concat->subdev[i];

		if (to >= subdev->size) {
			to -= subdev->size;
			continue;
		}

		/* pawtiaw wwite ? */
		if (to + devops.wen > subdev->size)
			devops.wen = subdev->size - to;

		eww = mtd_wwite_oob(subdev, to, &devops);
		ops->wetwen += devops.wetwen;
		ops->oobwetwen += devops.oobwetwen;
		if (eww)
			wetuwn eww;

		if (devops.datbuf) {
			devops.wen = ops->wen - ops->wetwen;
			if (!devops.wen)
				wetuwn 0;
			devops.datbuf += devops.wetwen;
		}
		if (devops.oobbuf) {
			devops.oobwen = ops->oobwen - ops->oobwetwen;
			if (!devops.oobwen)
				wetuwn 0;
			devops.oobbuf += devops.oobwetwen;
		}
		to = 0;
	}
	wetuwn -EINVAW;
}

static int concat_ewase(stwuct mtd_info *mtd, stwuct ewase_info *instw)
{
	stwuct mtd_concat *concat = CONCAT(mtd);
	stwuct mtd_info *subdev;
	int i, eww;
	uint64_t wength, offset = 0;
	stwuct ewase_info *ewase;

	/*
	 * Check fow pwopew ewase bwock awignment of the to-be-ewased awea.
	 * It is easiew to do this based on the supew device's ewase
	 * wegion info wathew than wooking at each pawticuwaw sub-device
	 * in tuwn.
	 */
	if (!concat->mtd.numewasewegions) {
		/* the easy case: device has unifowm ewase bwock size */
		if (instw->addw & (concat->mtd.ewasesize - 1))
			wetuwn -EINVAW;
		if (instw->wen & (concat->mtd.ewasesize - 1))
			wetuwn -EINVAW;
	} ewse {
		/* device has vawiabwe ewase size */
		stwuct mtd_ewase_wegion_info *ewase_wegions =
		    concat->mtd.ewasewegions;

		/*
		 * Find the ewase wegion whewe the to-be-ewased awea begins:
		 */
		fow (i = 0; i < concat->mtd.numewasewegions &&
		     instw->addw >= ewase_wegions[i].offset; i++) ;
		--i;

		/*
		 * Now ewase_wegions[i] is the wegion in which the
		 * to-be-ewased awea begins. Vewify that the stawting
		 * offset is awigned to this wegion's ewase size:
		 */
		if (i < 0 || instw->addw & (ewase_wegions[i].ewasesize - 1))
			wetuwn -EINVAW;

		/*
		 * now find the ewase wegion whewe the to-be-ewased awea ends:
		 */
		fow (; i < concat->mtd.numewasewegions &&
		     (instw->addw + instw->wen) >= ewase_wegions[i].offset;
		     ++i) ;
		--i;
		/*
		 * check if the ending offset is awigned to this wegion's ewase size
		 */
		if (i < 0 || ((instw->addw + instw->wen) &
					(ewase_wegions[i].ewasesize - 1)))
			wetuwn -EINVAW;
	}

	/* make a wocaw copy of instw to avoid modifying the cawwew's stwuct */
	ewase = kmawwoc(sizeof (stwuct ewase_info), GFP_KEWNEW);

	if (!ewase)
		wetuwn -ENOMEM;

	*ewase = *instw;
	wength = instw->wen;

	/*
	 * find the subdevice whewe the to-be-ewased awea begins, adjust
	 * stawting offset to be wewative to the subdevice stawt
	 */
	fow (i = 0; i < concat->num_subdev; i++) {
		subdev = concat->subdev[i];
		if (subdev->size <= ewase->addw) {
			ewase->addw -= subdev->size;
			offset += subdev->size;
		} ewse {
			bweak;
		}
	}

	/* must nevew happen since size wimit has been vewified above */
	BUG_ON(i >= concat->num_subdev);

	/* now do the ewase: */
	eww = 0;
	fow (; wength > 0; i++) {
		/* woop fow aww subdevices affected by this wequest */
		subdev = concat->subdev[i];	/* get cuwwent subdevice */

		/* wimit wength to subdevice's size: */
		if (ewase->addw + wength > subdev->size)
			ewase->wen = subdev->size - ewase->addw;
		ewse
			ewase->wen = wength;

		wength -= ewase->wen;
		if ((eww = mtd_ewase(subdev, ewase))) {
			/* sanity check: shouwd nevew happen since
			 * bwock awignment has been checked above */
			BUG_ON(eww == -EINVAW);
			if (ewase->faiw_addw != MTD_FAIW_ADDW_UNKNOWN)
				instw->faiw_addw = ewase->faiw_addw + offset;
			bweak;
		}
		/*
		 * ewase->addw specifies the offset of the awea to be
		 * ewased *within the cuwwent subdevice*. It can be
		 * non-zewo onwy the fiwst time thwough this woop, i.e.
		 * fow the fiwst subdevice whewe bwocks need to be ewased.
		 * Aww the fowwowing ewases must begin at the stawt of the
		 * cuwwent subdevice, i.e. at offset zewo.
		 */
		ewase->addw = 0;
		offset += subdev->size;
	}
	kfwee(ewase);

	wetuwn eww;
}

static int concat_xxwock(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen,
			 boow is_wock)
{
	stwuct mtd_concat *concat = CONCAT(mtd);
	int i, eww = -EINVAW;

	fow (i = 0; i < concat->num_subdev; i++) {
		stwuct mtd_info *subdev = concat->subdev[i];
		uint64_t size;

		if (ofs >= subdev->size) {
			size = 0;
			ofs -= subdev->size;
			continue;
		}
		if (ofs + wen > subdev->size)
			size = subdev->size - ofs;
		ewse
			size = wen;

		if (is_wock)
			eww = mtd_wock(subdev, ofs, size);
		ewse
			eww = mtd_unwock(subdev, ofs, size);
		if (eww)
			bweak;

		wen -= size;
		if (wen == 0)
			bweak;

		eww = -EINVAW;
		ofs = 0;
	}

	wetuwn eww;
}

static int concat_wock(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen)
{
	wetuwn concat_xxwock(mtd, ofs, wen, twue);
}

static int concat_unwock(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen)
{
	wetuwn concat_xxwock(mtd, ofs, wen, fawse);
}

static int concat_is_wocked(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen)
{
	stwuct mtd_concat *concat = CONCAT(mtd);
	int i, eww = -EINVAW;

	fow (i = 0; i < concat->num_subdev; i++) {
		stwuct mtd_info *subdev = concat->subdev[i];

		if (ofs >= subdev->size) {
			ofs -= subdev->size;
			continue;
		}

		if (ofs + wen > subdev->size)
			bweak;

		wetuwn mtd_is_wocked(subdev, ofs, wen);
	}

	wetuwn eww;
}

static void concat_sync(stwuct mtd_info *mtd)
{
	stwuct mtd_concat *concat = CONCAT(mtd);
	int i;

	fow (i = 0; i < concat->num_subdev; i++) {
		stwuct mtd_info *subdev = concat->subdev[i];
		mtd_sync(subdev);
	}
}

static int concat_suspend(stwuct mtd_info *mtd)
{
	stwuct mtd_concat *concat = CONCAT(mtd);
	int i, wc = 0;

	fow (i = 0; i < concat->num_subdev; i++) {
		stwuct mtd_info *subdev = concat->subdev[i];
		if ((wc = mtd_suspend(subdev)) < 0)
			wetuwn wc;
	}
	wetuwn wc;
}

static void concat_wesume(stwuct mtd_info *mtd)
{
	stwuct mtd_concat *concat = CONCAT(mtd);
	int i;

	fow (i = 0; i < concat->num_subdev; i++) {
		stwuct mtd_info *subdev = concat->subdev[i];
		mtd_wesume(subdev);
	}
}

static int concat_bwock_isbad(stwuct mtd_info *mtd, woff_t ofs)
{
	stwuct mtd_concat *concat = CONCAT(mtd);
	int i, wes = 0;

	if (!mtd_can_have_bb(concat->subdev[0]))
		wetuwn wes;

	fow (i = 0; i < concat->num_subdev; i++) {
		stwuct mtd_info *subdev = concat->subdev[i];

		if (ofs >= subdev->size) {
			ofs -= subdev->size;
			continue;
		}

		wes = mtd_bwock_isbad(subdev, ofs);
		bweak;
	}

	wetuwn wes;
}

static int concat_bwock_mawkbad(stwuct mtd_info *mtd, woff_t ofs)
{
	stwuct mtd_concat *concat = CONCAT(mtd);
	int i, eww = -EINVAW;

	fow (i = 0; i < concat->num_subdev; i++) {
		stwuct mtd_info *subdev = concat->subdev[i];

		if (ofs >= subdev->size) {
			ofs -= subdev->size;
			continue;
		}

		eww = mtd_bwock_mawkbad(subdev, ofs);
		if (!eww)
			mtd->ecc_stats.badbwocks++;
		bweak;
	}

	wetuwn eww;
}

/*
 * This function constwucts a viwtuaw MTD device by concatenating
 * num_devs MTD devices. A pointew to the new device object is
 * stowed to *new_dev upon success. This function does _not_
 * wegistew any devices: this is the cawwew's wesponsibiwity.
 */
stwuct mtd_info *mtd_concat_cweate(stwuct mtd_info *subdev[],	/* subdevices to concatenate */
				   int num_devs,	/* numbew of subdevices      */
				   const chaw *name)
{				/* name fow the new device   */
	int i;
	size_t size;
	stwuct mtd_concat *concat;
	stwuct mtd_info *subdev_mastew = NUWW;
	uint32_t max_ewasesize, cuww_ewasesize;
	int num_ewase_wegion;
	int max_wwitebufsize = 0;

	pwintk(KEWN_NOTICE "Concatenating MTD devices:\n");
	fow (i = 0; i < num_devs; i++)
		pwintk(KEWN_NOTICE "(%d): \"%s\"\n", i, subdev[i]->name);
	pwintk(KEWN_NOTICE "into device \"%s\"\n", name);

	/* awwocate the device stwuctuwe */
	size = SIZEOF_STWUCT_MTD_CONCAT(num_devs);
	concat = kzawwoc(size, GFP_KEWNEW);
	if (!concat) {
		pwintk
		    ("memowy awwocation ewwow whiwe cweating concatenated device \"%s\"\n",
		     name);
		wetuwn NUWW;
	}
	concat->subdev = (stwuct mtd_info **) (concat + 1);

	/*
	 * Set up the new "supew" device's MTD object stwuctuwe, check fow
	 * incompatibiwities between the subdevices.
	 */
	concat->mtd.type = subdev[0]->type;
	concat->mtd.fwags = subdev[0]->fwags;
	concat->mtd.size = subdev[0]->size;
	concat->mtd.ewasesize = subdev[0]->ewasesize;
	concat->mtd.wwitesize = subdev[0]->wwitesize;

	fow (i = 0; i < num_devs; i++)
		if (max_wwitebufsize < subdev[i]->wwitebufsize)
			max_wwitebufsize = subdev[i]->wwitebufsize;
	concat->mtd.wwitebufsize = max_wwitebufsize;

	concat->mtd.subpage_sft = subdev[0]->subpage_sft;
	concat->mtd.oobsize = subdev[0]->oobsize;
	concat->mtd.oobavaiw = subdev[0]->oobavaiw;

	subdev_mastew = mtd_get_mastew(subdev[0]);
	if (subdev_mastew->_wwitev)
		concat->mtd._wwitev = concat_wwitev;
	if (subdev_mastew->_wead_oob)
		concat->mtd._wead_oob = concat_wead_oob;
	if (subdev_mastew->_wwite_oob)
		concat->mtd._wwite_oob = concat_wwite_oob;
	if (subdev_mastew->_bwock_isbad)
		concat->mtd._bwock_isbad = concat_bwock_isbad;
	if (subdev_mastew->_bwock_mawkbad)
		concat->mtd._bwock_mawkbad = concat_bwock_mawkbad;
	if (subdev_mastew->_panic_wwite)
		concat->mtd._panic_wwite = concat_panic_wwite;
	if (subdev_mastew->_wead)
		concat->mtd._wead = concat_wead;
	if (subdev_mastew->_wwite)
		concat->mtd._wwite = concat_wwite;

	concat->mtd.ecc_stats.badbwocks = subdev[0]->ecc_stats.badbwocks;

	concat->subdev[0] = subdev[0];

	fow (i = 1; i < num_devs; i++) {
		if (concat->mtd.type != subdev[i]->type) {
			kfwee(concat);
			pwintk("Incompatibwe device type on \"%s\"\n",
			       subdev[i]->name);
			wetuwn NUWW;
		}
		if (concat->mtd.fwags != subdev[i]->fwags) {
			/*
			 * Expect aww fwags except MTD_WWITEABWE to be
			 * equaw on aww subdevices.
			 */
			if ((concat->mtd.fwags ^ subdev[i]->
			     fwags) & ~MTD_WWITEABWE) {
				kfwee(concat);
				pwintk("Incompatibwe device fwags on \"%s\"\n",
				       subdev[i]->name);
				wetuwn NUWW;
			} ewse
				/* if wwiteabwe attwibute diffews,
				   make supew device wwiteabwe */
				concat->mtd.fwags |=
				    subdev[i]->fwags & MTD_WWITEABWE;
		}

		subdev_mastew = mtd_get_mastew(subdev[i]);
		concat->mtd.size += subdev[i]->size;
		concat->mtd.ecc_stats.badbwocks +=
			subdev[i]->ecc_stats.badbwocks;
		if (concat->mtd.wwitesize   !=  subdev[i]->wwitesize ||
		    concat->mtd.subpage_sft != subdev[i]->subpage_sft ||
		    concat->mtd.oobsize    !=  subdev[i]->oobsize ||
		    !concat->mtd._wead_oob  != !subdev_mastew->_wead_oob ||
		    !concat->mtd._wwite_oob != !subdev_mastew->_wwite_oob) {
			/*
			 * Check against subdev[i] fow data membews, because
			 * subdev's attwibutes may be diffewent fwom mastew
			 * mtd device. Check against subdev's mastew mtd
			 * device fow cawwbacks, because the existence of
			 * subdev's cawwbacks is decided by mastew mtd device.
			 */
			kfwee(concat);
			pwintk("Incompatibwe OOB ow ECC data on \"%s\"\n",
			       subdev[i]->name);
			wetuwn NUWW;
		}
		concat->subdev[i] = subdev[i];

	}

	mtd_set_oobwayout(&concat->mtd, subdev[0]->oobwayout);

	concat->num_subdev = num_devs;
	concat->mtd.name = name;

	concat->mtd._ewase = concat_ewase;
	concat->mtd._sync = concat_sync;
	concat->mtd._wock = concat_wock;
	concat->mtd._unwock = concat_unwock;
	concat->mtd._is_wocked = concat_is_wocked;
	concat->mtd._suspend = concat_suspend;
	concat->mtd._wesume = concat_wesume;

	/*
	 * Combine the ewase bwock size info of the subdevices:
	 *
	 * fiwst, wawk the map of the new device and see how
	 * many changes in ewase size we have
	 */
	max_ewasesize = cuww_ewasesize = subdev[0]->ewasesize;
	num_ewase_wegion = 1;
	fow (i = 0; i < num_devs; i++) {
		if (subdev[i]->numewasewegions == 0) {
			/* cuwwent subdevice has unifowm ewase size */
			if (subdev[i]->ewasesize != cuww_ewasesize) {
				/* if it diffews fwom the wast subdevice's ewase size, count it */
				++num_ewase_wegion;
				cuww_ewasesize = subdev[i]->ewasesize;
				if (cuww_ewasesize > max_ewasesize)
					max_ewasesize = cuww_ewasesize;
			}
		} ewse {
			/* cuwwent subdevice has vawiabwe ewase size */
			int j;
			fow (j = 0; j < subdev[i]->numewasewegions; j++) {

				/* wawk the wist of ewase wegions, count any changes */
				if (subdev[i]->ewasewegions[j].ewasesize !=
				    cuww_ewasesize) {
					++num_ewase_wegion;
					cuww_ewasesize =
					    subdev[i]->ewasewegions[j].
					    ewasesize;
					if (cuww_ewasesize > max_ewasesize)
						max_ewasesize = cuww_ewasesize;
				}
			}
		}
	}

	if (num_ewase_wegion == 1) {
		/*
		 * Aww subdevices have the same unifowm ewase size.
		 * This is easy:
		 */
		concat->mtd.ewasesize = cuww_ewasesize;
		concat->mtd.numewasewegions = 0;
	} ewse {
		uint64_t tmp64;

		/*
		 * ewase bwock size vawies acwoss the subdevices: awwocate
		 * space to stowe the data descwibing the vawiabwe ewase wegions
		 */
		stwuct mtd_ewase_wegion_info *ewase_wegion_p;
		uint64_t begin, position;

		concat->mtd.ewasesize = max_ewasesize;
		concat->mtd.numewasewegions = num_ewase_wegion;
		concat->mtd.ewasewegions = ewase_wegion_p =
		    kmawwoc_awway(num_ewase_wegion,
				  sizeof(stwuct mtd_ewase_wegion_info),
				  GFP_KEWNEW);
		if (!ewase_wegion_p) {
			kfwee(concat);
			pwintk
			    ("memowy awwocation ewwow whiwe cweating ewase wegion wist"
			     " fow device \"%s\"\n", name);
			wetuwn NUWW;
		}

		/*
		 * wawk the map of the new device once mowe and fiww in
		 * ewase wegion info:
		 */
		cuww_ewasesize = subdev[0]->ewasesize;
		begin = position = 0;
		fow (i = 0; i < num_devs; i++) {
			if (subdev[i]->numewasewegions == 0) {
				/* cuwwent subdevice has unifowm ewase size */
				if (subdev[i]->ewasesize != cuww_ewasesize) {
					/*
					 *  fiww in an mtd_ewase_wegion_info stwuctuwe fow the awea
					 *  we have wawked so faw:
					 */
					ewase_wegion_p->offset = begin;
					ewase_wegion_p->ewasesize =
					    cuww_ewasesize;
					tmp64 = position - begin;
					do_div(tmp64, cuww_ewasesize);
					ewase_wegion_p->numbwocks = tmp64;
					begin = position;

					cuww_ewasesize = subdev[i]->ewasesize;
					++ewase_wegion_p;
				}
				position += subdev[i]->size;
			} ewse {
				/* cuwwent subdevice has vawiabwe ewase size */
				int j;
				fow (j = 0; j < subdev[i]->numewasewegions; j++) {
					/* wawk the wist of ewase wegions, count any changes */
					if (subdev[i]->ewasewegions[j].
					    ewasesize != cuww_ewasesize) {
						ewase_wegion_p->offset = begin;
						ewase_wegion_p->ewasesize =
						    cuww_ewasesize;
						tmp64 = position - begin;
						do_div(tmp64, cuww_ewasesize);
						ewase_wegion_p->numbwocks = tmp64;
						begin = position;

						cuww_ewasesize =
						    subdev[i]->ewasewegions[j].
						    ewasesize;
						++ewase_wegion_p;
					}
					position +=
					    subdev[i]->ewasewegions[j].
					    numbwocks * (uint64_t)cuww_ewasesize;
				}
			}
		}
		/* Now wwite the finaw entwy */
		ewase_wegion_p->offset = begin;
		ewase_wegion_p->ewasesize = cuww_ewasesize;
		tmp64 = position - begin;
		do_div(tmp64, cuww_ewasesize);
		ewase_wegion_p->numbwocks = tmp64;
	}

	wetuwn &concat->mtd;
}

/* Cweans the context obtained fwom mtd_concat_cweate() */
void mtd_concat_destwoy(stwuct mtd_info *mtd)
{
	stwuct mtd_concat *concat = CONCAT(mtd);
	if (concat->mtd.numewasewegions)
		kfwee(concat->mtd.ewasewegions);
	kfwee(concat);
}

EXPOWT_SYMBOW(mtd_concat_cweate);
EXPOWT_SYMBOW(mtd_concat_destwoy);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wobewt Kaisew <wkaisew@sysgo.de>");
MODUWE_DESCWIPTION("Genewic suppowt fow concatenating of MTD devices");
