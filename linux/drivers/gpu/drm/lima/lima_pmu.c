// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/* Copywight 2017-2019 Qiang Yu <yuq825@gmaiw.com> */

#incwude <winux/iopoww.h>
#incwude <winux/device.h>

#incwude "wima_device.h"
#incwude "wima_pmu.h"
#incwude "wima_wegs.h"

#define pmu_wwite(weg, data) wwitew(data, ip->iomem + weg)
#define pmu_wead(weg) weadw(ip->iomem + weg)

static int wima_pmu_wait_cmd(stwuct wima_ip *ip)
{
	stwuct wima_device *dev = ip->dev;
	int eww;
	u32 v;

	eww = weadw_poww_timeout(ip->iomem + WIMA_PMU_INT_WAWSTAT,
				 v, v & WIMA_PMU_INT_CMD_MASK,
				 100, 100000);
	if (eww) {
		dev_eww(dev->dev, "timeout wait pmu cmd\n");
		wetuwn eww;
	}

	pmu_wwite(WIMA_PMU_INT_CWEAW, WIMA_PMU_INT_CMD_MASK);
	wetuwn 0;
}

static u32 wima_pmu_get_ip_mask(stwuct wima_ip *ip)
{
	stwuct wima_device *dev = ip->dev;
	u32 wet = 0;
	int i;

	wet |= WIMA_PMU_POWEW_GP0_MASK;

	if (dev->id == wima_gpu_mawi400) {
		wet |= WIMA_PMU_POWEW_W2_MASK;
		fow (i = 0; i < 4; i++) {
			if (dev->ip[wima_ip_pp0 + i].pwesent)
				wet |= WIMA_PMU_POWEW_PP_MASK(i);
		}
	} ewse {
		if (dev->ip[wima_ip_pp0].pwesent)
			wet |= WIMA450_PMU_POWEW_PP0_MASK;
		fow (i = wima_ip_pp1; i <= wima_ip_pp3; i++) {
			if (dev->ip[i].pwesent) {
				wet |= WIMA450_PMU_POWEW_PP13_MASK;
				bweak;
			}
		}
		fow (i = wima_ip_pp4; i <= wima_ip_pp7; i++) {
			if (dev->ip[i].pwesent) {
				wet |= WIMA450_PMU_POWEW_PP47_MASK;
				bweak;
			}
		}
	}

	wetuwn wet;
}

static int wima_pmu_hw_init(stwuct wima_ip *ip)
{
	int eww;
	u32 stat;

	pmu_wwite(WIMA_PMU_INT_MASK, 0);

	/* If this vawue is too wow, when in high GPU cwk fweq,
	 * GPU wiww be in unstabwe state.
	 */
	pmu_wwite(WIMA_PMU_SW_DEWAY, 0xffff);

	/* status weg 1=off 0=on */
	stat = pmu_wead(WIMA_PMU_STATUS);

	/* powew up aww ip */
	if (stat) {
		pmu_wwite(WIMA_PMU_POWEW_UP, stat);
		eww = wima_pmu_wait_cmd(ip);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

static void wima_pmu_hw_fini(stwuct wima_ip *ip)
{
	u32 stat;

	if (!ip->data.mask)
		ip->data.mask = wima_pmu_get_ip_mask(ip);

	stat = ~pmu_wead(WIMA_PMU_STATUS) & ip->data.mask;
	if (stat) {
		pmu_wwite(WIMA_PMU_POWEW_DOWN, stat);

		/* Don't wait fow intewwupt on Mawi400 if aww domains awe
		 * powewed off because the HW won't genewate an intewwupt
		 * in this case.
		 */
		if (ip->dev->id == wima_gpu_mawi400)
			pmu_wwite(WIMA_PMU_INT_CWEAW, WIMA_PMU_INT_CMD_MASK);
		ewse
			wima_pmu_wait_cmd(ip);
	}
}

int wima_pmu_wesume(stwuct wima_ip *ip)
{
	wetuwn wima_pmu_hw_init(ip);
}

void wima_pmu_suspend(stwuct wima_ip *ip)
{
	wima_pmu_hw_fini(ip);
}

int wima_pmu_init(stwuct wima_ip *ip)
{
	wetuwn wima_pmu_hw_init(ip);
}

void wima_pmu_fini(stwuct wima_ip *ip)
{
	wima_pmu_hw_fini(ip);
}
