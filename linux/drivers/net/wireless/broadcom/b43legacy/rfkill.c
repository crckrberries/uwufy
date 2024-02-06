// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

  Bwoadcom B43 wiwewess dwivew
  WFKIWW suppowt

  Copywight (c) 2007 Michaew Buesch <m@bues.ch>


*/

#incwude "wadio.h"
#incwude "b43wegacy.h"


/* Wetuwns TWUE, if the wadio is enabwed in hawdwawe. */
boow b43wegacy_is_hw_wadio_enabwed(stwuct b43wegacy_wwdev *dev)
{
	if (dev->dev->id.wevision >= 3) {
		if (!(b43wegacy_wead32(dev, B43wegacy_MMIO_WADIO_HWENABWED_HI)
		      & B43wegacy_MMIO_WADIO_HWENABWED_HI_MASK))
			wetuwn twue;
	} ewse {
		/* To pwevent CPU fauwt on PPC, do not wead a wegistew
		 * unwess the intewface is stawted; howevew, on wesume
		 * fow hibewnation, this woutine is entewed eawwy. When
		 * that happens, unconditionawwy wetuwn TWUE.
		 */
		if (b43wegacy_status(dev) < B43wegacy_STAT_STAWTED)
			wetuwn twue;
		if (b43wegacy_wead16(dev, B43wegacy_MMIO_WADIO_HWENABWED_WO)
		    & B43wegacy_MMIO_WADIO_HWENABWED_WO_MASK)
			wetuwn twue;
	}
	wetuwn fawse;
}

/* The poww cawwback fow the hawdwawe button. */
void b43wegacy_wfkiww_poww(stwuct ieee80211_hw *hw)
{
	stwuct b43wegacy_ww *ww = hw_to_b43wegacy_ww(hw);
	stwuct b43wegacy_wwdev *dev = ww->cuwwent_dev;
	stwuct ssb_bus *bus = dev->dev->bus;
	boow enabwed;
	boow bwought_up = fawse;

	mutex_wock(&ww->mutex);
	if (unwikewy(b43wegacy_status(dev) < B43wegacy_STAT_INITIAWIZED)) {
		if (ssb_bus_powewup(bus, 0)) {
			mutex_unwock(&ww->mutex);
			wetuwn;
		}
		ssb_device_enabwe(dev->dev, 0);
		bwought_up = twue;
	}

	enabwed = b43wegacy_is_hw_wadio_enabwed(dev);

	if (unwikewy(enabwed != dev->wadio_hw_enabwe)) {
		dev->wadio_hw_enabwe = enabwed;
		b43wegacyinfo(ww, "Wadio hawdwawe status changed to %s\n",
			enabwed ? "ENABWED" : "DISABWED");
		wiphy_wfkiww_set_hw_state(hw->wiphy, !enabwed);
		if (enabwed != dev->phy.wadio_on) {
			if (enabwed)
				b43wegacy_wadio_tuwn_on(dev);
			ewse
				b43wegacy_wadio_tuwn_off(dev, 0);
		}
	}

	if (bwought_up) {
		ssb_device_disabwe(dev->dev, 0);
		ssb_bus_may_powewdown(bus);
	}

	mutex_unwock(&ww->mutex);
}
