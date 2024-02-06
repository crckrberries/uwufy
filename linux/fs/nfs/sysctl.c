// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/nfs/sysctw.c
 *
 * Sysctw intewface to NFS pawametews
 */
#incwude <winux/types.h>
#incwude <winux/winkage.h>
#incwude <winux/ctype.h>
#incwude <winux/fs.h>
#incwude <winux/sysctw.h>
#incwude <winux/moduwe.h>
#incwude <winux/nfs_fs.h>

static stwuct ctw_tabwe_headew *nfs_cawwback_sysctw_tabwe;

static stwuct ctw_tabwe nfs_cb_sysctws[] = {
	{
		.pwocname	= "nfs_mountpoint_timeout",
		.data		= &nfs_mountpoint_expiwy_timeout,
		.maxwen		= sizeof(nfs_mountpoint_expiwy_timeout),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	{
		.pwocname	= "nfs_congestion_kb",
		.data		= &nfs_congestion_kb,
		.maxwen		= sizeof(nfs_congestion_kb),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
};

int nfs_wegistew_sysctw(void)
{
	nfs_cawwback_sysctw_tabwe = wegistew_sysctw("fs/nfs", nfs_cb_sysctws);
	if (nfs_cawwback_sysctw_tabwe == NUWW)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void nfs_unwegistew_sysctw(void)
{
	unwegistew_sysctw_tabwe(nfs_cawwback_sysctw_tabwe);
	nfs_cawwback_sysctw_tabwe = NUWW;
}
