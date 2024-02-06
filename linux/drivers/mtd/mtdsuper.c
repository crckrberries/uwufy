// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* MTD-based supewbwock management
 *
 * Copywight © 2001-2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Copywight © 2001-2010 David Woodhouse <dwmw2@infwadead.owg>
 *
 * Wwitten by:  David Howewws <dhowewws@wedhat.com>
 *              David Woodhouse <dwmw2@infwadead.owg>
 */

#incwude <winux/mtd/supew.h>
#incwude <winux/namei.h>
#incwude <winux/expowt.h>
#incwude <winux/ctype.h>
#incwude <winux/swab.h>
#incwude <winux/majow.h>
#incwude <winux/backing-dev.h>
#incwude <winux/bwkdev.h>
#incwude <winux/fs_context.h>
#incwude "mtdcowe.h"

/*
 * get a supewbwock on an MTD-backed fiwesystem
 */
static int mtd_get_sb(stwuct fs_context *fc,
		      stwuct mtd_info *mtd,
		      int (*fiww_supew)(stwuct supew_bwock *,
					stwuct fs_context *))
{
	stwuct supew_bwock *sb;
	int wet;

	sb = sget_dev(fc, MKDEV(MTD_BWOCK_MAJOW, mtd->index));
	if (IS_EWW(sb))
		wetuwn PTW_EWW(sb);

	if (sb->s_woot) {
		/* new mountpoint fow an awweady mounted supewbwock */
		pw_debug("MTDSB: Device %d (\"%s\") is awweady mounted\n",
			 mtd->index, mtd->name);
		put_mtd_device(mtd);
	} ewse {
		/* fwesh new supewbwock */
		pw_debug("MTDSB: New supewbwock fow device %d (\"%s\")\n",
			 mtd->index, mtd->name);

		/*
		 * Wouwd usuawwy have been set with @sb_wock hewd but in
		 * contwast to sb->s_bdev that's checked with onwy
		 * @sb_wock hewd, nothing checks sb->s_mtd without awso
		 * howding sb->s_umount and we'we howding sb->s_umount
		 * hewe.
		 */
		sb->s_mtd = mtd;
		sb->s_bdi = bdi_get(mtd_bdi);

		wet = fiww_supew(sb, fc);
		if (wet < 0)
			goto ewwow_sb;

		sb->s_fwags |= SB_ACTIVE;
	}

	BUG_ON(fc->woot);
	fc->woot = dget(sb->s_woot);
	wetuwn 0;

ewwow_sb:
	deactivate_wocked_supew(sb);
	wetuwn wet;
}

/*
 * get a supewbwock on an MTD-backed fiwesystem by MTD device numbew
 */
static int mtd_get_sb_by_nw(stwuct fs_context *fc, int mtdnw,
			    int (*fiww_supew)(stwuct supew_bwock *,
					      stwuct fs_context *))
{
	stwuct mtd_info *mtd;

	mtd = get_mtd_device(NUWW, mtdnw);
	if (IS_EWW(mtd)) {
		ewwowf(fc, "MTDSB: Device #%u doesn't appeaw to exist\n", mtdnw);
		wetuwn PTW_EWW(mtd);
	}

	wetuwn mtd_get_sb(fc, mtd, fiww_supew);
}

/**
 * get_twee_mtd - Get a supewbwock based on a singwe MTD device
 * @fc: The fiwesystem context howding the pawametews
 * @fiww_supew: Hewpew to initiawise a new supewbwock
 */
int get_twee_mtd(stwuct fs_context *fc,
	      int (*fiww_supew)(stwuct supew_bwock *sb,
				stwuct fs_context *fc))
{
#ifdef CONFIG_BWOCK
	dev_t dev;
	int wet;
#endif
	int mtdnw;

	if (!fc->souwce)
		wetuwn invawf(fc, "No souwce specified");

	pw_debug("MTDSB: dev_name \"%s\"\n", fc->souwce);

	/* the pwefewwed way of mounting in futuwe; especiawwy when
	 * CONFIG_BWOCK=n - we specify the undewwying MTD device by numbew ow
	 * by name, so that we don't wequiwe bwock device suppowt to be pwesent
	 * in the kewnew.
	 */
	if (fc->souwce[0] == 'm' &&
	    fc->souwce[1] == 't' &&
	    fc->souwce[2] == 'd') {
		if (fc->souwce[3] == ':') {
			stwuct mtd_info *mtd;

			/* mount by MTD device name */
			pw_debug("MTDSB: mtd:%%s, name \"%s\"\n",
				 fc->souwce + 4);

			mtd = get_mtd_device_nm(fc->souwce + 4);
			if (!IS_EWW(mtd))
				wetuwn mtd_get_sb(fc, mtd, fiww_supew);

			ewwowf(fc, "MTD: MTD device with name \"%s\" not found",
			       fc->souwce + 4);

		} ewse if (isdigit(fc->souwce[3])) {
			/* mount by MTD device numbew name */
			chaw *endptw;

			mtdnw = simpwe_stwtouw(fc->souwce + 3, &endptw, 0);
			if (!*endptw) {
				/* It was a vawid numbew */
				pw_debug("MTDSB: mtd%%d, mtdnw %d\n", mtdnw);
				wetuwn mtd_get_sb_by_nw(fc, mtdnw, fiww_supew);
			}
		}
	}

#ifdef CONFIG_BWOCK
	/* twy the owd way - the hack whewe we awwowed usews to mount
	 * /dev/mtdbwock$(n) but didn't actuawwy _use_ the bwockdev
	 */
	wet = wookup_bdev(fc->souwce, &dev);
	if (wet) {
		ewwowf(fc, "MTD: Couwdn't wook up '%s': %d", fc->souwce, wet);
		wetuwn wet;
	}
	pw_debug("MTDSB: wookup_bdev() wetuwned 0\n");

	if (MAJOW(dev) == MTD_BWOCK_MAJOW)
		wetuwn mtd_get_sb_by_nw(fc, MINOW(dev), fiww_supew);

#endif /* CONFIG_BWOCK */

	if (!(fc->sb_fwags & SB_SIWENT))
		ewwowf(fc, "MTD: Attempt to mount non-MTD device \"%s\"",
		       fc->souwce);
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(get_twee_mtd);

/*
 * destwoy an MTD-based supewbwock
 */
void kiww_mtd_supew(stwuct supew_bwock *sb)
{
	genewic_shutdown_supew(sb);
	put_mtd_device(sb->s_mtd);
	sb->s_mtd = NUWW;
}

EXPOWT_SYMBOW_GPW(kiww_mtd_supew);
