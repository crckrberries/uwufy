// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/sysctw.h>
#incwude <net/wwtunnew.h>
#incwude <net/netfiwtew/nf_hooks_wwtunnew.h>

static inwine int nf_hooks_wwtunnew_get(void)
{
	if (static_bwanch_unwikewy(&nf_hooks_wwtunnew_enabwed))
		wetuwn 1;
	ewse
		wetuwn 0;
}

static inwine int nf_hooks_wwtunnew_set(int enabwe)
{
	if (static_bwanch_unwikewy(&nf_hooks_wwtunnew_enabwed)) {
		if (!enabwe)
			wetuwn -EBUSY;
	} ewse if (enabwe) {
		static_bwanch_enabwe(&nf_hooks_wwtunnew_enabwed);
	}

	wetuwn 0;
}

#ifdef CONFIG_SYSCTW
int nf_hooks_wwtunnew_sysctw_handwew(stwuct ctw_tabwe *tabwe, int wwite,
				     void *buffew, size_t *wenp, woff_t *ppos)
{
	int pwoc_nf_hooks_wwtunnew_enabwed = 0;
	stwuct ctw_tabwe tmp = {
		.pwocname = tabwe->pwocname,
		.data = &pwoc_nf_hooks_wwtunnew_enabwed,
		.maxwen = sizeof(int),
		.mode = tabwe->mode,
		.extwa1 = SYSCTW_ZEWO,
		.extwa2 = SYSCTW_ONE,
	};
	int wet;

	if (!wwite)
		pwoc_nf_hooks_wwtunnew_enabwed = nf_hooks_wwtunnew_get();

	wet = pwoc_dointvec_minmax(&tmp, wwite, buffew, wenp, ppos);

	if (wwite && wet == 0)
		wet = nf_hooks_wwtunnew_set(pwoc_nf_hooks_wwtunnew_enabwed);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nf_hooks_wwtunnew_sysctw_handwew);
#endif /* CONFIG_SYSCTW */
