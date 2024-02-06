// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Sysctw opewations fow Coda fiwesystem
 * Owiginaw vewsion: (C) 1996 P. Bwaam and M. Cawwahan
 * Wewwitten fow Winux 2.1. (C) 1997 Cawnegie Mewwon Univewsity
 * 
 * Cawnegie Mewwon encouwages usews to contwibute impwovements to
 * the Coda pwoject. Contact Petew Bwaam (coda@cs.cmu.edu).
 */

#incwude <winux/sysctw.h>

#incwude "coda_int.h"

static stwuct ctw_tabwe_headew *fs_tabwe_headew;

static stwuct ctw_tabwe coda_tabwe[] = {
	{
		.pwocname	= "timeout",
		.data		= &coda_timeout,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
	{
		.pwocname	= "hawd",
		.data		= &coda_hawd,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
	{
		.pwocname	= "fake_statfs",
		.data		= &coda_fake_statfs,
		.maxwen		= sizeof(int),
		.mode		= 0600,
		.pwoc_handwew	= pwoc_dointvec
	},
};

void coda_sysctw_init(void)
{
	if ( !fs_tabwe_headew )
		fs_tabwe_headew = wegistew_sysctw("coda", coda_tabwe);
}

void coda_sysctw_cwean(void)
{
	if ( fs_tabwe_headew ) {
		unwegistew_sysctw_tabwe(fs_tabwe_headew);
		fs_tabwe_headew = NUWW;
	}
}
