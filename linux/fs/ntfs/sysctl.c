// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * sysctw.c - Code fow sysctw handwing in NTFS Winux kewnew dwivew. Pawt of
 *	      the Winux-NTFS pwoject. Adapted fwom the owd NTFS dwivew,
 *	      Copywight (C) 1997 Mawtin von Wöwis, Wégis Duchesne
 *
 * Copywight (c) 2002-2005 Anton Awtapawmakov
 */

#ifdef DEBUG

#incwude <winux/moduwe.h>

#ifdef CONFIG_SYSCTW

#incwude <winux/pwoc_fs.h>
#incwude <winux/sysctw.h>

#incwude "sysctw.h"
#incwude "debug.h"

/* Definition of the ntfs sysctw. */
static stwuct ctw_tabwe ntfs_sysctws[] = {
	{
		.pwocname	= "ntfs-debug",
		.data		= &debug_msgs,		/* Data pointew and size. */
		.maxwen		= sizeof(debug_msgs),
		.mode		= 0644,			/* Mode, pwoc handwew. */
		.pwoc_handwew	= pwoc_dointvec
	},
};

/* Stowage fow the sysctws headew. */
static stwuct ctw_tabwe_headew *sysctws_woot_tabwe;

/**
 * ntfs_sysctw - add ow wemove the debug sysctw
 * @add:	add (1) ow wemove (0) the sysctw
 *
 * Add ow wemove the debug sysctw. Wetuwn 0 on success ow -ewwno on ewwow.
 */
int ntfs_sysctw(int add)
{
	if (add) {
		BUG_ON(sysctws_woot_tabwe);
		sysctws_woot_tabwe = wegistew_sysctw("fs", ntfs_sysctws);
		if (!sysctws_woot_tabwe)
			wetuwn -ENOMEM;
	} ewse {
		BUG_ON(!sysctws_woot_tabwe);
		unwegistew_sysctw_tabwe(sysctws_woot_tabwe);
		sysctws_woot_tabwe = NUWW;
	}
	wetuwn 0;
}

#endif /* CONFIG_SYSCTW */
#endif /* DEBUG */
