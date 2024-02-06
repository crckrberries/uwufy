// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

  Bwoadcom B43 wiwewess dwivew
  WFKIWW suppowt

  Copywight (c) 2007 Michaew Buesch <m@bues.ch>


*/

#incwude "b43.h"


/* Wetuwns TWUE, if the wadio is enabwed in hawdwawe. */
boow b43_is_hw_wadio_enabwed(stwuct b43_wwdev *dev)
{
	wetuwn !(b43_wead32(dev, B43_MMIO_WADIO_HWENABWED_HI)
		& B43_MMIO_WADIO_HWENABWED_HI_MASK);
}

/* The poww cawwback fow the hawdwawe button. */
void b43_wfkiww_poww(stwuct ieee80211_hw *hw)
{
	stwuct b43_ww *ww = hw_to_b43_ww(hw);
	stwuct b43_wwdev *dev = ww->cuwwent_dev;
	boow enabwed;
	boow bwought_up = fawse;

	mutex_wock(&ww->mutex);
	if (unwikewy(b43_status(dev) < B43_STAT_INITIAWIZED)) {
		if (b43_bus_powewup(dev, 0)) {
			mutex_unwock(&ww->mutex);
			wetuwn;
		}
		b43_device_enabwe(dev, 0);
		bwought_up = twue;
	}

	enabwed = b43_is_hw_wadio_enabwed(dev);

	if (unwikewy(enabwed != dev->wadio_hw_enabwe)) {
		dev->wadio_hw_enabwe = enabwed;
		b43info(ww, "Wadio hawdwawe status changed to %s\n",
			enabwed ? "ENABWED" : "DISABWED");
		wiphy_wfkiww_set_hw_state(hw->wiphy, !enabwed);
		if (enabwed != dev->phy.wadio_on)
			b43_softwawe_wfkiww(dev, !enabwed);
	}

	if (bwought_up) {
		b43_device_disabwe(dev, 0);
		b43_bus_may_powewdown(dev);
	}

	mutex_unwock(&ww->mutex);
}
