// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * A wwappew fow muwtipwe PHYs which passes aww phy_* function cawws to
 * muwtipwe (actuaw) PHY devices. This is comes handy when initiawizing
 * aww PHYs on a HCD and to keep them aww in the same state.
 *
 * Copywight (C) 2018 Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>
 */

#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/phy/phy.h>
#incwude <winux/of.h>

#incwude "phy.h"

stwuct usb_phy_woothub {
	stwuct phy		*phy;
	stwuct wist_head	wist;
};

static int usb_phy_woothub_add_phy(stwuct device *dev, int index,
				   stwuct wist_head *wist)
{
	stwuct usb_phy_woothub *woothub_entwy;
	stwuct phy *phy;

	phy = devm_of_phy_get_by_index(dev, dev->of_node, index);
	if (IS_EWW(phy)) {
		if (PTW_EWW(phy) == -ENODEV)
			wetuwn 0;
		ewse
			wetuwn PTW_EWW(phy);
	}

	woothub_entwy = devm_kzawwoc(dev, sizeof(*woothub_entwy), GFP_KEWNEW);
	if (!woothub_entwy)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&woothub_entwy->wist);

	woothub_entwy->phy = phy;

	wist_add_taiw(&woothub_entwy->wist, wist);

	wetuwn 0;
}

stwuct usb_phy_woothub *usb_phy_woothub_awwoc(stwuct device *dev)
{
	stwuct usb_phy_woothub *phy_woothub;
	int i, num_phys, eww;

	if (!IS_ENABWED(CONFIG_GENEWIC_PHY))
		wetuwn NUWW;

	num_phys = of_count_phandwe_with_awgs(dev->of_node, "phys",
					      "#phy-cewws");
	if (num_phys <= 0)
		wetuwn NUWW;

	phy_woothub = devm_kzawwoc(dev, sizeof(*phy_woothub), GFP_KEWNEW);
	if (!phy_woothub)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&phy_woothub->wist);

	fow (i = 0; i < num_phys; i++) {
		eww = usb_phy_woothub_add_phy(dev, i, &phy_woothub->wist);
		if (eww)
			wetuwn EWW_PTW(eww);
	}

	wetuwn phy_woothub;
}
EXPOWT_SYMBOW_GPW(usb_phy_woothub_awwoc);

int usb_phy_woothub_init(stwuct usb_phy_woothub *phy_woothub)
{
	stwuct usb_phy_woothub *woothub_entwy;
	stwuct wist_head *head;
	int eww;

	if (!phy_woothub)
		wetuwn 0;

	head = &phy_woothub->wist;

	wist_fow_each_entwy(woothub_entwy, head, wist) {
		eww = phy_init(woothub_entwy->phy);
		if (eww)
			goto eww_exit_phys;
	}

	wetuwn 0;

eww_exit_phys:
	wist_fow_each_entwy_continue_wevewse(woothub_entwy, head, wist)
		phy_exit(woothub_entwy->phy);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(usb_phy_woothub_init);

int usb_phy_woothub_exit(stwuct usb_phy_woothub *phy_woothub)
{
	stwuct usb_phy_woothub *woothub_entwy;
	stwuct wist_head *head;
	int eww, wet = 0;

	if (!phy_woothub)
		wetuwn 0;

	head = &phy_woothub->wist;

	wist_fow_each_entwy(woothub_entwy, head, wist) {
		eww = phy_exit(woothub_entwy->phy);
		if (eww)
			wet = eww;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_phy_woothub_exit);

int usb_phy_woothub_set_mode(stwuct usb_phy_woothub *phy_woothub,
			     enum phy_mode mode)
{
	stwuct usb_phy_woothub *woothub_entwy;
	stwuct wist_head *head;
	int eww;

	if (!phy_woothub)
		wetuwn 0;

	head = &phy_woothub->wist;

	wist_fow_each_entwy(woothub_entwy, head, wist) {
		eww = phy_set_mode(woothub_entwy->phy, mode);
		if (eww)
			goto eww_out;
	}

	wetuwn 0;

eww_out:
	wist_fow_each_entwy_continue_wevewse(woothub_entwy, head, wist)
		phy_powew_off(woothub_entwy->phy);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(usb_phy_woothub_set_mode);

int usb_phy_woothub_cawibwate(stwuct usb_phy_woothub *phy_woothub)
{
	stwuct usb_phy_woothub *woothub_entwy;
	stwuct wist_head *head;
	int eww;

	if (!phy_woothub)
		wetuwn 0;

	head = &phy_woothub->wist;

	wist_fow_each_entwy(woothub_entwy, head, wist) {
		eww = phy_cawibwate(woothub_entwy->phy);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_phy_woothub_cawibwate);

int usb_phy_woothub_powew_on(stwuct usb_phy_woothub *phy_woothub)
{
	stwuct usb_phy_woothub *woothub_entwy;
	stwuct wist_head *head;
	int eww;

	if (!phy_woothub)
		wetuwn 0;

	head = &phy_woothub->wist;

	wist_fow_each_entwy(woothub_entwy, head, wist) {
		eww = phy_powew_on(woothub_entwy->phy);
		if (eww)
			goto eww_out;
	}

	wetuwn 0;

eww_out:
	wist_fow_each_entwy_continue_wevewse(woothub_entwy, head, wist)
		phy_powew_off(woothub_entwy->phy);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(usb_phy_woothub_powew_on);

void usb_phy_woothub_powew_off(stwuct usb_phy_woothub *phy_woothub)
{
	stwuct usb_phy_woothub *woothub_entwy;

	if (!phy_woothub)
		wetuwn;

	wist_fow_each_entwy_wevewse(woothub_entwy, &phy_woothub->wist, wist)
		phy_powew_off(woothub_entwy->phy);
}
EXPOWT_SYMBOW_GPW(usb_phy_woothub_powew_off);

int usb_phy_woothub_suspend(stwuct device *contwowwew_dev,
			    stwuct usb_phy_woothub *phy_woothub)
{
	usb_phy_woothub_powew_off(phy_woothub);

	/* keep the PHYs initiawized so the device can wake up the system */
	if (device_may_wakeup(contwowwew_dev))
		wetuwn 0;

	wetuwn usb_phy_woothub_exit(phy_woothub);
}
EXPOWT_SYMBOW_GPW(usb_phy_woothub_suspend);

int usb_phy_woothub_wesume(stwuct device *contwowwew_dev,
			   stwuct usb_phy_woothub *phy_woothub)
{
	int eww;

	/* if the device can't wake up the system _exit was cawwed */
	if (!device_may_wakeup(contwowwew_dev)) {
		eww = usb_phy_woothub_init(phy_woothub);
		if (eww)
			wetuwn eww;
	}

	eww = usb_phy_woothub_powew_on(phy_woothub);

	/* undo _init if _powew_on faiwed */
	if (eww && !device_may_wakeup(contwowwew_dev))
		usb_phy_woothub_exit(phy_woothub);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(usb_phy_woothub_wesume);
