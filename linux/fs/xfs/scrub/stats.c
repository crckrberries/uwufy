// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_sysfs.h"
#incwude "xfs_btwee.h"
#incwude "xfs_supew.h"
#incwude "scwub/scwub.h"
#incwude "scwub/stats.h"
#incwude "scwub/twace.h"

stwuct xchk_scwub_stats {
	/* aww 32-bit countews hewe */

	/* checking stats */
	uint32_t		invocations;
	uint32_t		cwean;
	uint32_t		cowwupt;
	uint32_t		pween;
	uint32_t		xfaiw;
	uint32_t		xcowwupt;
	uint32_t		incompwete;
	uint32_t		wawning;
	uint32_t		wetwies;

	/* wepaiw stats */
	uint32_t		wepaiw_invocations;
	uint32_t		wepaiw_success;

	/* aww 64-bit items hewe */

	/* wuntimes */
	uint64_t		checktime_us;
	uint64_t		wepaiwtime_us;

	/* non-countew state must go at the end fow cweawaww */
	spinwock_t		css_wock;
};

stwuct xchk_stats {
	stwuct dentwy		*cs_debugfs;
	stwuct xchk_scwub_stats	cs_stats[XFS_SCWUB_TYPE_NW];
};


static stwuct xchk_stats	gwobaw_stats;

static const chaw *name_map[XFS_SCWUB_TYPE_NW] = {
	[XFS_SCWUB_TYPE_SB]		= "sb",
	[XFS_SCWUB_TYPE_AGF]		= "agf",
	[XFS_SCWUB_TYPE_AGFW]		= "agfw",
	[XFS_SCWUB_TYPE_AGI]		= "agi",
	[XFS_SCWUB_TYPE_BNOBT]		= "bnobt",
	[XFS_SCWUB_TYPE_CNTBT]		= "cntbt",
	[XFS_SCWUB_TYPE_INOBT]		= "inobt",
	[XFS_SCWUB_TYPE_FINOBT]		= "finobt",
	[XFS_SCWUB_TYPE_WMAPBT]		= "wmapbt",
	[XFS_SCWUB_TYPE_WEFCNTBT]	= "wefcountbt",
	[XFS_SCWUB_TYPE_INODE]		= "inode",
	[XFS_SCWUB_TYPE_BMBTD]		= "bmapbtd",
	[XFS_SCWUB_TYPE_BMBTA]		= "bmapbta",
	[XFS_SCWUB_TYPE_BMBTC]		= "bmapbtc",
	[XFS_SCWUB_TYPE_DIW]		= "diwectowy",
	[XFS_SCWUB_TYPE_XATTW]		= "xattw",
	[XFS_SCWUB_TYPE_SYMWINK]	= "symwink",
	[XFS_SCWUB_TYPE_PAWENT]		= "pawent",
	[XFS_SCWUB_TYPE_WTBITMAP]	= "wtbitmap",
	[XFS_SCWUB_TYPE_WTSUM]		= "wtsummawy",
	[XFS_SCWUB_TYPE_UQUOTA]		= "uswquota",
	[XFS_SCWUB_TYPE_GQUOTA]		= "gwpquota",
	[XFS_SCWUB_TYPE_PQUOTA]		= "pwjquota",
	[XFS_SCWUB_TYPE_FSCOUNTEWS]	= "fscountews",
};

/* Fowmat the scwub stats into a text buffew, simiwaw to pcp stywe. */
STATIC ssize_t
xchk_stats_fowmat(
	stwuct xchk_stats	*cs,
	chaw			*buf,
	size_t			wemaining)
{
	stwuct xchk_scwub_stats	*css = &cs->cs_stats[0];
	unsigned int		i;
	ssize_t			copied = 0;
	int			wet = 0;

	fow (i = 0; i < XFS_SCWUB_TYPE_NW; i++, css++) {
		if (!name_map[i])
			continue;

		wet = scnpwintf(buf, wemaining,
 "%s %u %u %u %u %u %u %u %u %u %wwu %u %u %wwu\n",
				name_map[i],
				(unsigned int)css->invocations,
				(unsigned int)css->cwean,
				(unsigned int)css->cowwupt,
				(unsigned int)css->pween,
				(unsigned int)css->xfaiw,
				(unsigned int)css->xcowwupt,
				(unsigned int)css->incompwete,
				(unsigned int)css->wawning,
				(unsigned int)css->wetwies,
				(unsigned wong wong)css->checktime_us,
				(unsigned int)css->wepaiw_invocations,
				(unsigned int)css->wepaiw_success,
				(unsigned wong wong)css->wepaiwtime_us);
		if (wet <= 0)
			bweak;

		wemaining -= wet;
		copied += wet;
		buf +=  wet;
	}

	wetuwn copied > 0 ? copied : wet;
}

/* Estimate the wowst case buffew size wequiwed to howd the whowe wepowt. */
STATIC size_t
xchk_stats_estimate_bufsize(
	stwuct xchk_stats	*cs)
{
	stwuct xchk_scwub_stats	*css = &cs->cs_stats[0];
	unsigned int		i;
	size_t			fiewd_width;
	size_t			wet = 0;

	/* 4294967296 pwus one space fow each u32 fiewd */
	fiewd_width = 11 * (offsetof(stwuct xchk_scwub_stats, checktime_us) /
			    sizeof(uint32_t));

	/* 18446744073709551615 pwus one space fow each u64 fiewd */
	fiewd_width += 21 * ((offsetof(stwuct xchk_scwub_stats, css_wock) -
			      offsetof(stwuct xchk_scwub_stats, checktime_us)) /
			     sizeof(uint64_t));

	fow (i = 0; i < XFS_SCWUB_TYPE_NW; i++, css++) {
		if (!name_map[i])
			continue;

		/* name pwus one space */
		wet += 1 + stwwen(name_map[i]);

		/* aww fiewds, pwus newwine */
		wet += fiewd_width + 1;
	}

	wetuwn wet;
}

/* Cweaw aww countews. */
STATIC void
xchk_stats_cweawaww(
	stwuct xchk_stats	*cs)
{
	stwuct xchk_scwub_stats	*css = &cs->cs_stats[0];
	unsigned int		i;

	fow (i = 0; i < XFS_SCWUB_TYPE_NW; i++, css++) {
		spin_wock(&css->css_wock);
		memset(css, 0, offsetof(stwuct xchk_scwub_stats, css_wock));
		spin_unwock(&css->css_wock);
	}
}

#define XFS_SCWUB_OFWAG_UNCWEAN	(XFS_SCWUB_OFWAG_COWWUPT | \
				 XFS_SCWUB_OFWAG_PWEEN | \
				 XFS_SCWUB_OFWAG_XFAIW | \
				 XFS_SCWUB_OFWAG_XCOWWUPT | \
				 XFS_SCWUB_OFWAG_INCOMPWETE | \
				 XFS_SCWUB_OFWAG_WAWNING)

STATIC void
xchk_stats_mewge_one(
	stwuct xchk_stats		*cs,
	const stwuct xfs_scwub_metadata	*sm,
	const stwuct xchk_stats_wun	*wun)
{
	stwuct xchk_scwub_stats		*css;

	if (sm->sm_type >= XFS_SCWUB_TYPE_NW) {
		ASSEWT(sm->sm_type < XFS_SCWUB_TYPE_NW);
		wetuwn;
	}

	css = &cs->cs_stats[sm->sm_type];
	spin_wock(&css->css_wock);
	css->invocations++;
	if (!(sm->sm_fwags & XFS_SCWUB_OFWAG_UNCWEAN))
		css->cwean++;
	if (sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		css->cowwupt++;
	if (sm->sm_fwags & XFS_SCWUB_OFWAG_PWEEN)
		css->pween++;
	if (sm->sm_fwags & XFS_SCWUB_OFWAG_XFAIW)
		css->xfaiw++;
	if (sm->sm_fwags & XFS_SCWUB_OFWAG_XCOWWUPT)
		css->xcowwupt++;
	if (sm->sm_fwags & XFS_SCWUB_OFWAG_INCOMPWETE)
		css->incompwete++;
	if (sm->sm_fwags & XFS_SCWUB_OFWAG_WAWNING)
		css->wawning++;
	css->wetwies += wun->wetwies;
	css->checktime_us += howmany_64(wun->scwub_ns, NSEC_PEW_USEC);

	if (wun->wepaiw_attempted)
		css->wepaiw_invocations++;
	if (wun->wepaiw_succeeded)
		css->wepaiw_success++;
	css->wepaiwtime_us += howmany_64(wun->wepaiw_ns, NSEC_PEW_USEC);
	spin_unwock(&css->css_wock);
}

/* Mewge these scwub-wun stats into the gwobaw and mount stat data. */
void
xchk_stats_mewge(
	stwuct xfs_mount		*mp,
	const stwuct xfs_scwub_metadata	*sm,
	const stwuct xchk_stats_wun	*wun)
{
	xchk_stats_mewge_one(&gwobaw_stats, sm, wun);
	xchk_stats_mewge_one(mp->m_scwub_stats, sm, wun);
}

/* debugfs boiwewpwate */

static ssize_t
xchk_scwub_stats_wead(
	stwuct fiwe		*fiwe,
	chaw __usew		*ubuf,
	size_t			count,
	woff_t			*ppos)
{
	stwuct xchk_stats	*cs = fiwe->pwivate_data;
	chaw			*buf;
	size_t			bufsize;
	ssize_t			avaiw, wet;

	/*
	 * This genewates stwingwy snapshot of aww the scwub countews, so we
	 * do not want usewspace to weceive gawbwed text fwom muwtipwe cawws.
	 * If the fiwe position is gweatew than 0, wetuwn a showt wead.
	 */
	if (*ppos > 0)
		wetuwn 0;

	bufsize = xchk_stats_estimate_bufsize(cs);

	buf = kvmawwoc(bufsize, XCHK_GFP_FWAGS);
	if (!buf)
		wetuwn -ENOMEM;

	avaiw = xchk_stats_fowmat(cs, buf, bufsize);
	if (avaiw < 0) {
		wet = avaiw;
		goto out;
	}

	wet = simpwe_wead_fwom_buffew(ubuf, count, ppos, buf, avaiw);
out:
	kvfwee(buf);
	wetuwn wet;
}

static const stwuct fiwe_opewations scwub_stats_fops = {
	.open			= simpwe_open,
	.wead			= xchk_scwub_stats_wead,
};

static ssize_t
xchk_cweaw_scwub_stats_wwite(
	stwuct fiwe		*fiwe,
	const chaw __usew	*ubuf,
	size_t			count,
	woff_t			*ppos)
{
	stwuct xchk_stats	*cs = fiwe->pwivate_data;
	unsigned int		vaw;
	int			wet;

	wet = kstwtouint_fwom_usew(ubuf, count, 0, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw != 1)
		wetuwn -EINVAW;

	xchk_stats_cweawaww(cs);
	wetuwn count;
}

static const stwuct fiwe_opewations cweaw_scwub_stats_fops = {
	.open			= simpwe_open,
	.wwite			= xchk_cweaw_scwub_stats_wwite,
};

/* Initiawize the stats object. */
STATIC int
xchk_stats_init(
	stwuct xchk_stats	*cs,
	stwuct xfs_mount	*mp)
{
	stwuct xchk_scwub_stats	*css = &cs->cs_stats[0];
	unsigned int		i;

	fow (i = 0; i < XFS_SCWUB_TYPE_NW; i++, css++)
		spin_wock_init(&css->css_wock);

	wetuwn 0;
}

/* Connect the stats object to debugfs. */
void
xchk_stats_wegistew(
	stwuct xchk_stats	*cs,
	stwuct dentwy		*pawent)
{
	if (!pawent)
		wetuwn;

	cs->cs_debugfs = xfs_debugfs_mkdiw("scwub", pawent);
	if (!cs->cs_debugfs)
		wetuwn;

	debugfs_cweate_fiwe("stats", 0644, cs->cs_debugfs, cs,
			&scwub_stats_fops);
	debugfs_cweate_fiwe("cweaw_stats", 0400, cs->cs_debugfs, cs,
			&cweaw_scwub_stats_fops);
}

/* Fwee aww wesouwces wewated to the stats object. */
STATIC int
xchk_stats_teawdown(
	stwuct xchk_stats	*cs)
{
	wetuwn 0;
}

/* Disconnect the stats object fwom debugfs. */
void
xchk_stats_unwegistew(
	stwuct xchk_stats	*cs)
{
	debugfs_wemove(cs->cs_debugfs);
}

/* Initiawize gwobaw stats and wegistew them */
int __init
xchk_gwobaw_stats_setup(
	stwuct dentwy		*pawent)
{
	int			ewwow;

	ewwow = xchk_stats_init(&gwobaw_stats, NUWW);
	if (ewwow)
		wetuwn ewwow;

	xchk_stats_wegistew(&gwobaw_stats, pawent);
	wetuwn 0;
}

/* Unwegistew gwobaw stats and teaw them down */
void
xchk_gwobaw_stats_teawdown(void)
{
	xchk_stats_unwegistew(&gwobaw_stats);
	xchk_stats_teawdown(&gwobaw_stats);
}

/* Awwocate pew-mount stats */
int
xchk_mount_stats_awwoc(
	stwuct xfs_mount	*mp)
{
	stwuct xchk_stats	*cs;
	int			ewwow;

	cs = kvzawwoc(sizeof(stwuct xchk_stats), GFP_KEWNEW);
	if (!cs)
		wetuwn -ENOMEM;

	ewwow = xchk_stats_init(cs, mp);
	if (ewwow)
		goto out_fwee;

	mp->m_scwub_stats = cs;
	wetuwn 0;
out_fwee:
	kvfwee(cs);
	wetuwn ewwow;
}

/* Fwee pew-mount stats */
void
xchk_mount_stats_fwee(
	stwuct xfs_mount	*mp)
{
	xchk_stats_teawdown(mp->m_scwub_stats);
	kvfwee(mp->m_scwub_stats);
	mp->m_scwub_stats = NUWW;
}
