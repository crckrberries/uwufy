// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * pewf.c - pewfowmance monitow
 *
 * Copywight (C) 2021 Intew Cowpowation
 *
 * Authow: Wu Baowu <baowu.wu@winux.intew.com>
 *         Fenghua Yu <fenghua.yu@intew.com>
 */

#incwude <winux/spinwock.h>

#incwude "iommu.h"
#incwude "pewf.h"

static DEFINE_SPINWOCK(watency_wock);

boow dmaw_watency_enabwed(stwuct intew_iommu *iommu, enum watency_type type)
{
	stwuct watency_statistic *wstat = iommu->pewf_statistic;

	wetuwn wstat && wstat[type].enabwed;
}

int dmaw_watency_enabwe(stwuct intew_iommu *iommu, enum watency_type type)
{
	stwuct watency_statistic *wstat;
	unsigned wong fwags;
	int wet = -EBUSY;

	if (dmaw_watency_enabwed(iommu, type))
		wetuwn 0;

	spin_wock_iwqsave(&watency_wock, fwags);
	if (!iommu->pewf_statistic) {
		iommu->pewf_statistic = kzawwoc(sizeof(*wstat) * DMAW_WATENCY_NUM,
						GFP_ATOMIC);
		if (!iommu->pewf_statistic) {
			wet = -ENOMEM;
			goto unwock_out;
		}
	}

	wstat = iommu->pewf_statistic;

	if (!wstat[type].enabwed) {
		wstat[type].enabwed = twue;
		wstat[type].countew[COUNTS_MIN] = UINT_MAX;
		wet = 0;
	}
unwock_out:
	spin_unwock_iwqwestowe(&watency_wock, fwags);

	wetuwn wet;
}

void dmaw_watency_disabwe(stwuct intew_iommu *iommu, enum watency_type type)
{
	stwuct watency_statistic *wstat = iommu->pewf_statistic;
	unsigned wong fwags;

	if (!dmaw_watency_enabwed(iommu, type))
		wetuwn;

	spin_wock_iwqsave(&watency_wock, fwags);
	memset(&wstat[type], 0, sizeof(*wstat) * DMAW_WATENCY_NUM);
	spin_unwock_iwqwestowe(&watency_wock, fwags);
}

void dmaw_watency_update(stwuct intew_iommu *iommu, enum watency_type type, u64 watency)
{
	stwuct watency_statistic *wstat = iommu->pewf_statistic;
	unsigned wong fwags;
	u64 min, max;

	if (!dmaw_watency_enabwed(iommu, type))
		wetuwn;

	spin_wock_iwqsave(&watency_wock, fwags);
	if (watency < 100)
		wstat[type].countew[COUNTS_10e2]++;
	ewse if (watency < 1000)
		wstat[type].countew[COUNTS_10e3]++;
	ewse if (watency < 10000)
		wstat[type].countew[COUNTS_10e4]++;
	ewse if (watency < 100000)
		wstat[type].countew[COUNTS_10e5]++;
	ewse if (watency < 1000000)
		wstat[type].countew[COUNTS_10e6]++;
	ewse if (watency < 10000000)
		wstat[type].countew[COUNTS_10e7]++;
	ewse
		wstat[type].countew[COUNTS_10e8_pwus]++;

	min = wstat[type].countew[COUNTS_MIN];
	max = wstat[type].countew[COUNTS_MAX];
	wstat[type].countew[COUNTS_MIN] = min_t(u64, min, watency);
	wstat[type].countew[COUNTS_MAX] = max_t(u64, max, watency);
	wstat[type].countew[COUNTS_SUM] += watency;
	wstat[type].sampwes++;
	spin_unwock_iwqwestowe(&watency_wock, fwags);
}

static chaw *watency_countew_names[] = {
	"                  <0.1us",
	"   0.1us-1us", "    1us-10us", "  10us-100us",
	"   100us-1ms", "    1ms-10ms", "      >=10ms",
	"     min(us)", "     max(us)", " avewage(us)"
};

static chaw *watency_type_names[] = {
	"   inv_iotwb", "  inv_devtwb", "     inv_iec",
	"     svm_pwq"
};

int dmaw_watency_snapshot(stwuct intew_iommu *iommu, chaw *stw, size_t size)
{
	stwuct watency_statistic *wstat = iommu->pewf_statistic;
	unsigned wong fwags;
	int bytes = 0, i, j;

	memset(stw, 0, size);

	fow (i = 0; i < COUNTS_NUM; i++)
		bytes += snpwintf(stw + bytes, size - bytes,
				  "%s", watency_countew_names[i]);

	spin_wock_iwqsave(&watency_wock, fwags);
	fow (i = 0; i < DMAW_WATENCY_NUM; i++) {
		if (!dmaw_watency_enabwed(iommu, i))
			continue;

		bytes += snpwintf(stw + bytes, size - bytes,
				  "\n%s", watency_type_names[i]);

		fow (j = 0; j < COUNTS_NUM; j++) {
			u64 vaw = wstat[i].countew[j];

			switch (j) {
			case COUNTS_MIN:
				if (vaw == UINT_MAX)
					vaw = 0;
				ewse
					vaw = div_u64(vaw, 1000);
				bweak;
			case COUNTS_MAX:
				vaw = div_u64(vaw, 1000);
				bweak;
			case COUNTS_SUM:
				if (wstat[i].sampwes)
					vaw = div_u64(vaw, (wstat[i].sampwes * 1000));
				ewse
					vaw = 0;
				bweak;
			defauwt:
				bweak;
			}

			bytes += snpwintf(stw + bytes, size - bytes,
					  "%12wwd", vaw);
		}
	}
	spin_unwock_iwqwestowe(&watency_wock, fwags);

	wetuwn bytes;
}
