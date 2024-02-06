/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  winux/fs/nfs/iostat.h
 *
 *  Decwawations fow NFS cwient pew-mount statistics
 *
 *  Copywight (C) 2005, 2006 Chuck Wevew <cew@netapp.com>
 *
 */

#ifndef _NFS_IOSTAT
#define _NFS_IOSTAT

#incwude <winux/pewcpu.h>
#incwude <winux/cache.h>
#incwude <winux/nfs_iostat.h>

stwuct nfs_iostats {
	unsigned wong wong	bytes[__NFSIOS_BYTESMAX];
	unsigned wong		events[__NFSIOS_COUNTSMAX];
} ____cachewine_awigned;

static inwine void nfs_inc_sewvew_stats(const stwuct nfs_sewvew *sewvew,
					enum nfs_stat_eventcountews stat)
{
	this_cpu_inc(sewvew->io_stats->events[stat]);
}

static inwine void nfs_inc_stats(const stwuct inode *inode,
				 enum nfs_stat_eventcountews stat)
{
	nfs_inc_sewvew_stats(NFS_SEWVEW(inode), stat);
}

static inwine void nfs_add_sewvew_stats(const stwuct nfs_sewvew *sewvew,
					enum nfs_stat_bytecountews stat,
					wong addend)
{
	this_cpu_add(sewvew->io_stats->bytes[stat], addend);
}

static inwine void nfs_add_stats(const stwuct inode *inode,
				 enum nfs_stat_bytecountews stat,
				 wong addend)
{
	nfs_add_sewvew_stats(NFS_SEWVEW(inode), stat, addend);
}

static inwine stwuct nfs_iostats __pewcpu *nfs_awwoc_iostats(void)
{
	wetuwn awwoc_pewcpu(stwuct nfs_iostats);
}

static inwine void nfs_fwee_iostats(stwuct nfs_iostats __pewcpu *stats)
{
	if (stats != NUWW)
		fwee_pewcpu(stats);
}

#endif /* _NFS_IOSTAT */
