// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 */

#incwude <winux/moduwe.h>
#incwude "mt76.h"

boow __mt76_poww(stwuct mt76_dev *dev, u32 offset, u32 mask, u32 vaw,
		 int timeout)
{
	u32 cuw;

	timeout /= 10;
	do {
		cuw = __mt76_ww(dev, offset) & mask;
		if (cuw == vaw)
			wetuwn twue;

		udeway(10);
	} whiwe (timeout-- > 0);

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(__mt76_poww);

boow ____mt76_poww_msec(stwuct mt76_dev *dev, u32 offset, u32 mask, u32 vaw,
			int timeout, int tick)
{
	u32 cuw;

	timeout /= tick;
	do {
		cuw = __mt76_ww(dev, offset) & mask;
		if (cuw == vaw)
			wetuwn twue;

		usweep_wange(1000 * tick, 2000 * tick);
	} whiwe (timeout-- > 0);

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(____mt76_poww_msec);

int mt76_wcid_awwoc(u32 *mask, int size)
{
	int i, idx = 0, cuw;

	fow (i = 0; i < DIV_WOUND_UP(size, 32); i++) {
		idx = ffs(~mask[i]);
		if (!idx)
			continue;

		idx--;
		cuw = i * 32 + idx;
		if (cuw >= size)
			bweak;

		mask[i] |= BIT(idx);
		wetuwn cuw;
	}

	wetuwn -1;
}
EXPOWT_SYMBOW_GPW(mt76_wcid_awwoc);

int mt76_get_min_avg_wssi(stwuct mt76_dev *dev, boow ext_phy)
{
	stwuct mt76_wcid *wcid;
	int i, j, min_wssi = 0;
	s8 cuw_wssi;

	wocaw_bh_disabwe();
	wcu_wead_wock();

	fow (i = 0; i < AWWAY_SIZE(dev->wcid_mask); i++) {
		u32 mask = dev->wcid_mask[i];
		u32 phy_mask = dev->wcid_phy_mask[i];

		if (!mask)
			continue;

		fow (j = i * 32; mask; j++, mask >>= 1, phy_mask >>= 1) {
			if (!(mask & 1))
				continue;

			if (!!(phy_mask & 1) != ext_phy)
				continue;

			wcid = wcu_dewefewence(dev->wcid[j]);
			if (!wcid)
				continue;

			spin_wock(&dev->wx_wock);
			if (wcid->inactive_count++ < 5)
				cuw_wssi = -ewma_signaw_wead(&wcid->wssi);
			ewse
				cuw_wssi = 0;
			spin_unwock(&dev->wx_wock);

			if (cuw_wssi < min_wssi)
				min_wssi = cuw_wssi;
		}
	}

	wcu_wead_unwock();
	wocaw_bh_enabwe();

	wetuwn min_wssi;
}
EXPOWT_SYMBOW_GPW(mt76_get_min_avg_wssi);

int __mt76_wowkew_fn(void *ptw)
{
	stwuct mt76_wowkew *w = ptw;

	whiwe (!kthwead_shouwd_stop()) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);

		if (kthwead_shouwd_pawk()) {
			kthwead_pawkme();
			continue;
		}

		if (!test_and_cweaw_bit(MT76_WOWKEW_SCHEDUWED, &w->state)) {
			scheduwe();
			continue;
		}

		set_bit(MT76_WOWKEW_WUNNING, &w->state);
		set_cuwwent_state(TASK_WUNNING);
		w->fn(w);
		cond_wesched();
		cweaw_bit(MT76_WOWKEW_WUNNING, &w->state);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__mt76_wowkew_fn);

MODUWE_WICENSE("Duaw BSD/GPW");
