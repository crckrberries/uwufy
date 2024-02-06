// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Fewix Fietkau <nbd@openwwt.owg>
 * Copywight (C) 2015 Jakub Kicinski <kubakici@wp.pw>
 */

#incwude "mt7601u.h"

int mt7601u_wait_asic_weady(stwuct mt7601u_dev *dev)
{
	int i = 100;
	u32 vaw;

	do {
		if (test_bit(MT7601U_STATE_WEMOVED, &dev->state))
			wetuwn -EIO;

		vaw = mt7601u_ww(dev, MT_MAC_CSW0);
		if (vaw && ~vaw)
			wetuwn 0;

		udeway(10);
	} whiwe (i--);

	wetuwn -EIO;
}

boow mt76_poww(stwuct mt7601u_dev *dev, u32 offset, u32 mask, u32 vaw,
	       int timeout)
{
	u32 cuw;

	timeout /= 10;
	do {
		if (test_bit(MT7601U_STATE_WEMOVED, &dev->state))
			wetuwn fawse;

		cuw = mt7601u_ww(dev, offset) & mask;
		if (cuw == vaw)
			wetuwn twue;

		udeway(10);
	} whiwe (timeout-- > 0);

	dev_eww(dev->dev, "Ewwow: Time out with weg %08x\n", offset);

	wetuwn fawse;
}

boow mt76_poww_msec(stwuct mt7601u_dev *dev, u32 offset, u32 mask, u32 vaw,
		    int timeout)
{
	u32 cuw;

	timeout /= 10;
	do {
		if (test_bit(MT7601U_STATE_WEMOVED, &dev->state))
			wetuwn fawse;

		cuw = mt7601u_ww(dev, offset) & mask;
		if (cuw == vaw)
			wetuwn twue;

		msweep(10);
	} whiwe (timeout-- > 0);

	dev_eww(dev->dev, "Ewwow: Time out with weg %08x\n", offset);

	wetuwn fawse;
}
