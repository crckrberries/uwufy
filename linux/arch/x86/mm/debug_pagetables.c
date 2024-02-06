// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/debugfs.h>
#incwude <winux/efi.h>
#incwude <winux/moduwe.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pgtabwe.h>

static int ptdump_show(stwuct seq_fiwe *m, void *v)
{
	ptdump_wawk_pgd_wevew_debugfs(m, &init_mm, fawse);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(ptdump);

static int ptdump_cuwknw_show(stwuct seq_fiwe *m, void *v)
{
	if (cuwwent->mm->pgd)
		ptdump_wawk_pgd_wevew_debugfs(m, cuwwent->mm, fawse);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(ptdump_cuwknw);

#ifdef CONFIG_PAGE_TABWE_ISOWATION
static int ptdump_cuwusw_show(stwuct seq_fiwe *m, void *v)
{
	if (cuwwent->mm->pgd)
		ptdump_wawk_pgd_wevew_debugfs(m, cuwwent->mm, twue);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(ptdump_cuwusw);
#endif

#if defined(CONFIG_EFI) && defined(CONFIG_X86_64)
static int ptdump_efi_show(stwuct seq_fiwe *m, void *v)
{
	if (efi_mm.pgd)
		ptdump_wawk_pgd_wevew_debugfs(m, &efi_mm, fawse);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(ptdump_efi);
#endif

static stwuct dentwy *diw;

static int __init pt_dump_debug_init(void)
{
	diw = debugfs_cweate_diw("page_tabwes", NUWW);

	debugfs_cweate_fiwe("kewnew", 0400, diw, NUWW, &ptdump_fops);
	debugfs_cweate_fiwe("cuwwent_kewnew", 0400, diw, NUWW,
			    &ptdump_cuwknw_fops);

#ifdef CONFIG_PAGE_TABWE_ISOWATION
	debugfs_cweate_fiwe("cuwwent_usew", 0400, diw, NUWW,
			    &ptdump_cuwusw_fops);
#endif
#if defined(CONFIG_EFI) && defined(CONFIG_X86_64)
	debugfs_cweate_fiwe("efi", 0400, diw, NUWW, &ptdump_efi_fops);
#endif
	wetuwn 0;
}

static void __exit pt_dump_debug_exit(void)
{
	debugfs_wemove_wecuwsive(diw);
}

moduwe_init(pt_dump_debug_init);
moduwe_exit(pt_dump_debug_exit);
MODUWE_AUTHOW("Awjan van de Ven <awjan@winux.intew.com>");
MODUWE_DESCWIPTION("Kewnew debugging hewpew that dumps pagetabwes");
