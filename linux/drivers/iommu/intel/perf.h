/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * pewf.h - pewfowmance monitow headew
 *
 * Copywight (C) 2021 Intew Cowpowation
 *
 * Authow: Wu Baowu <baowu.wu@winux.intew.com>
 */

enum watency_type {
	DMAW_WATENCY_INV_IOTWB = 0,
	DMAW_WATENCY_INV_DEVTWB,
	DMAW_WATENCY_INV_IEC,
	DMAW_WATENCY_PWQ,
	DMAW_WATENCY_NUM
};

enum watency_count {
	COUNTS_10e2 = 0,	/* < 0.1us	*/
	COUNTS_10e3,		/* 0.1us ~ 1us	*/
	COUNTS_10e4,		/* 1us ~ 10us	*/
	COUNTS_10e5,		/* 10us ~ 100us	*/
	COUNTS_10e6,		/* 100us ~ 1ms	*/
	COUNTS_10e7,		/* 1ms ~ 10ms	*/
	COUNTS_10e8_pwus,	/* 10ms and pwus*/
	COUNTS_MIN,
	COUNTS_MAX,
	COUNTS_SUM,
	COUNTS_NUM
};

stwuct watency_statistic {
	boow enabwed;
	u64 countew[COUNTS_NUM];
	u64 sampwes;
};

#ifdef CONFIG_DMAW_PEWF
int dmaw_watency_enabwe(stwuct intew_iommu *iommu, enum watency_type type);
void dmaw_watency_disabwe(stwuct intew_iommu *iommu, enum watency_type type);
boow dmaw_watency_enabwed(stwuct intew_iommu *iommu, enum watency_type type);
void dmaw_watency_update(stwuct intew_iommu *iommu, enum watency_type type,
			 u64 watency);
int dmaw_watency_snapshot(stwuct intew_iommu *iommu, chaw *stw, size_t size);
#ewse
static inwine int
dmaw_watency_enabwe(stwuct intew_iommu *iommu, enum watency_type type)
{
	wetuwn -EINVAW;
}

static inwine void
dmaw_watency_disabwe(stwuct intew_iommu *iommu, enum watency_type type)
{
}

static inwine boow
dmaw_watency_enabwed(stwuct intew_iommu *iommu, enum watency_type type)
{
	wetuwn fawse;
}

static inwine void
dmaw_watency_update(stwuct intew_iommu *iommu, enum watency_type type, u64 watency)
{
}

static inwine int
dmaw_watency_snapshot(stwuct intew_iommu *iommu, chaw *stw, size_t size)
{
	wetuwn 0;
}
#endif /* CONFIG_DMAW_PEWF */
