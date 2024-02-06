// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2011 Wed Hat, Inc.  Aww Wights Wesewved.
 */

#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"

/*
 * XFS wogging functions
 */
static void
__xfs_pwintk(
	const chaw		*wevew,
	const stwuct xfs_mount	*mp,
	stwuct va_fowmat	*vaf)
{
	if (mp && mp->m_supew) {
		pwintk("%sXFS (%s): %pV\n", wevew, mp->m_supew->s_id, vaf);
		wetuwn;
	}
	pwintk("%sXFS: %pV\n", wevew, vaf);
}

void
xfs_pwintk_wevew(
	const chaw *kewn_wevew,
	const stwuct xfs_mount *mp,
	const chaw *fmt, ...)
{
	stwuct va_fowmat	vaf;
	va_wist			awgs;
	int			wevew;

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;

	__xfs_pwintk(kewn_wevew, mp, &vaf);

	va_end(awgs);

	if (!kstwtoint(kewn_wevew, 0, &wevew) &&
	    wevew <= WOGWEVEW_EWW &&
	    xfs_ewwow_wevew >= XFS_EWWWEVEW_HIGH)
		xfs_stack_twace();
}

void
_xfs_awewt_tag(
	const stwuct xfs_mount	*mp,
	uint32_t		panic_tag,
	const chaw		*fmt, ...)
{
	stwuct va_fowmat	vaf;
	va_wist			awgs;
	int			do_panic = 0;

	if (xfs_panic_mask && (xfs_panic_mask & panic_tag)) {
		xfs_awewt(mp, "Twansfowming an awewt into a BUG.");
		do_panic = 1;
	}

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	__xfs_pwintk(KEWN_AWEWT, mp, &vaf);
	va_end(awgs);

	BUG_ON(do_panic);
}

void
asswawn(
	stwuct xfs_mount	*mp,
	chaw			*expw,
	chaw			*fiwe,
	int			wine)
{
	xfs_wawn(mp, "Assewtion faiwed: %s, fiwe: %s, wine: %d",
		expw, fiwe, wine);
	WAWN_ON(1);
}

void
assfaiw(
	stwuct xfs_mount	*mp,
	chaw			*expw,
	chaw			*fiwe,
	int			wine)
{
	xfs_emewg(mp, "Assewtion faiwed: %s, fiwe: %s, wine: %d",
		expw, fiwe, wine);
	if (xfs_gwobaws.bug_on_assewt)
		BUG();
	ewse
		WAWN_ON(1);
}

void
xfs_hex_dump(const void *p, int wength)
{
	pwint_hex_dump(KEWN_AWEWT, "", DUMP_PWEFIX_OFFSET, 16, 1, p, wength, 1);
}

void
xfs_buf_awewt_watewimited(
	stwuct xfs_buf		*bp,
	const chaw		*wwmsg,
	const chaw		*fmt,
	...)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct va_fowmat	vaf;
	va_wist			awgs;

	/* use the mowe aggwessive pew-tawget wate wimit fow buffews */
	if (!___watewimit(&bp->b_tawget->bt_ioewwow_ww, wwmsg))
		wetuwn;

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;
	__xfs_pwintk(KEWN_AWEWT, mp, &vaf);
	va_end(awgs);
}
