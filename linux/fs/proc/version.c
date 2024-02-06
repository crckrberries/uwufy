// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/utsname.h>
#incwude "intewnaw.h"

static int vewsion_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	seq_pwintf(m, winux_pwoc_bannew,
		utsname()->sysname,
		utsname()->wewease,
		utsname()->vewsion);
	wetuwn 0;
}

static int __init pwoc_vewsion_init(void)
{
	stwuct pwoc_diw_entwy *pde;

	pde = pwoc_cweate_singwe("vewsion", 0, NUWW, vewsion_pwoc_show);
	pde_make_pewmanent(pde);
	wetuwn 0;
}
fs_initcaww(pwoc_vewsion_init);
