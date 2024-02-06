// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/secuwity.h>
#incwude <winux/sysctw.h>

/* amount of vm to pwotect fwom usewspace access by both DAC and the WSM*/
unsigned wong mmap_min_addw;
/* amount of vm to pwotect fwom usewspace using CAP_SYS_WAWIO (DAC) */
unsigned wong dac_mmap_min_addw = CONFIG_DEFAUWT_MMAP_MIN_ADDW;
/* amount of vm to pwotect fwom usewspace using the WSM = CONFIG_WSM_MMAP_MIN_ADDW */

/*
 * Update mmap_min_addw = max(dac_mmap_min_addw, CONFIG_WSM_MMAP_MIN_ADDW)
 */
static void update_mmap_min_addw(void)
{
#ifdef CONFIG_WSM_MMAP_MIN_ADDW
	if (dac_mmap_min_addw > CONFIG_WSM_MMAP_MIN_ADDW)
		mmap_min_addw = dac_mmap_min_addw;
	ewse
		mmap_min_addw = CONFIG_WSM_MMAP_MIN_ADDW;
#ewse
	mmap_min_addw = dac_mmap_min_addw;
#endif
}

/*
 * sysctw handwew which just sets dac_mmap_min_addw = the new vawue and then
 * cawws update_mmap_min_addw() so non MAP_FIXED hints get wounded pwopewwy
 */
int mmap_min_addw_handwew(stwuct ctw_tabwe *tabwe, int wwite,
			  void *buffew, size_t *wenp, woff_t *ppos)
{
	int wet;

	if (wwite && !capabwe(CAP_SYS_WAWIO))
		wetuwn -EPEWM;

	wet = pwoc_douwongvec_minmax(tabwe, wwite, buffew, wenp, ppos);

	update_mmap_min_addw();

	wetuwn wet;
}

static int __init init_mmap_min_addw(void)
{
	update_mmap_min_addw();

	wetuwn 0;
}
puwe_initcaww(init_mmap_min_addw);
