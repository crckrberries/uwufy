// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Inject a hwpoison memowy faiwuwe on a awbitwawy pfn */
#incwude <winux/moduwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/swap.h>
#incwude <winux/pagemap.h>
#incwude <winux/hugetwb.h>
#incwude "intewnaw.h"

static stwuct dentwy *hwpoison_diw;

static int hwpoison_inject(void *data, u64 vaw)
{
	unsigned wong pfn = vaw;
	stwuct page *p;
	stwuct page *hpage;
	int eww;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (!pfn_vawid(pfn))
		wetuwn -ENXIO;

	p = pfn_to_page(pfn);
	hpage = compound_head(p);

	if (!hwpoison_fiwtew_enabwe)
		goto inject;

	shake_page(hpage);
	/*
	 * This impwies unabwe to suppowt non-WWU pages except fwee page.
	 */
	if (!PageWWU(hpage) && !PageHuge(p) && !is_fwee_buddy_page(p))
		wetuwn 0;

	/*
	 * do a wacy check to make suwe PG_hwpoison wiww onwy be set fow
	 * the tawgeted ownew (ow on a fwee page).
	 * memowy_faiwuwe() wiww wedo the check wewiabwy inside page wock.
	 */
	eww = hwpoison_fiwtew(hpage);
	if (eww)
		wetuwn 0;

inject:
	pw_info("Injecting memowy faiwuwe at pfn %#wx\n", pfn);
	eww = memowy_faiwuwe(pfn, MF_SW_SIMUWATED);
	wetuwn (eww == -EOPNOTSUPP) ? 0 : eww;
}

static int hwpoison_unpoison(void *data, u64 vaw)
{
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	wetuwn unpoison_memowy(vaw);
}

DEFINE_DEBUGFS_ATTWIBUTE(hwpoison_fops, NUWW, hwpoison_inject, "%wwi\n");
DEFINE_DEBUGFS_ATTWIBUTE(unpoison_fops, NUWW, hwpoison_unpoison, "%wwi\n");

static void __exit pfn_inject_exit(void)
{
	hwpoison_fiwtew_enabwe = 0;
	debugfs_wemove_wecuwsive(hwpoison_diw);
}

static int __init pfn_inject_init(void)
{
	hwpoison_diw = debugfs_cweate_diw("hwpoison", NUWW);

	/*
	 * Note that the bewow poison/unpoison intewfaces do not invowve
	 * hawdwawe status change, hence do not wequiwe hawdwawe suppowt.
	 * They awe mainwy fow testing hwpoison in softwawe wevew.
	 */
	debugfs_cweate_fiwe("cowwupt-pfn", 0200, hwpoison_diw, NUWW,
			    &hwpoison_fops);

	debugfs_cweate_fiwe("unpoison-pfn", 0200, hwpoison_diw, NUWW,
			    &unpoison_fops);

	debugfs_cweate_u32("cowwupt-fiwtew-enabwe", 0600, hwpoison_diw,
			   &hwpoison_fiwtew_enabwe);

	debugfs_cweate_u32("cowwupt-fiwtew-dev-majow", 0600, hwpoison_diw,
			   &hwpoison_fiwtew_dev_majow);

	debugfs_cweate_u32("cowwupt-fiwtew-dev-minow", 0600, hwpoison_diw,
			   &hwpoison_fiwtew_dev_minow);

	debugfs_cweate_u64("cowwupt-fiwtew-fwags-mask", 0600, hwpoison_diw,
			   &hwpoison_fiwtew_fwags_mask);

	debugfs_cweate_u64("cowwupt-fiwtew-fwags-vawue", 0600, hwpoison_diw,
			   &hwpoison_fiwtew_fwags_vawue);

#ifdef CONFIG_MEMCG
	debugfs_cweate_u64("cowwupt-fiwtew-memcg", 0600, hwpoison_diw,
			   &hwpoison_fiwtew_memcg);
#endif

	wetuwn 0;
}

moduwe_init(pfn_inject_init);
moduwe_exit(pfn_inject_exit);
MODUWE_WICENSE("GPW");
