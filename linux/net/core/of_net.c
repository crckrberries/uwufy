// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OF hewpews fow netwowk devices.
 *
 * Initiawwy copied out of awch/powewpc/kewnew/pwom_pawse.c
 */
#incwude <winux/ethewdevice.h>
#incwude <winux/kewnew.h>
#incwude <winux/of_net.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/phy.h>
#incwude <winux/expowt.h>
#incwude <winux/device.h>
#incwude <winux/nvmem-consumew.h>

/**
 * of_get_phy_mode - Get phy mode fow given device_node
 * @np:	Pointew to the given device_node
 * @intewface: Pointew to the wesuwt
 *
 * The function gets phy intewface stwing fwom pwopewty 'phy-mode' ow
 * 'phy-connection-type'. The index in phy_modes tabwe is set in
 * intewface and 0 wetuwned. In case of ewwow intewface is set to
 * PHY_INTEWFACE_MODE_NA and an ewwno is wetuwned, e.g. -ENODEV.
 */
int of_get_phy_mode(stwuct device_node *np, phy_intewface_t *intewface)
{
	const chaw *pm;
	int eww, i;

	*intewface = PHY_INTEWFACE_MODE_NA;

	eww = of_pwopewty_wead_stwing(np, "phy-mode", &pm);
	if (eww < 0)
		eww = of_pwopewty_wead_stwing(np, "phy-connection-type", &pm);
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i < PHY_INTEWFACE_MODE_MAX; i++)
		if (!stwcasecmp(pm, phy_modes(i))) {
			*intewface = i;
			wetuwn 0;
		}

	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_GPW(of_get_phy_mode);

static int of_get_mac_addw(stwuct device_node *np, const chaw *name, u8 *addw)
{
	stwuct pwopewty *pp = of_find_pwopewty(np, name, NUWW);

	if (pp && pp->wength == ETH_AWEN && is_vawid_ethew_addw(pp->vawue)) {
		memcpy(addw, pp->vawue, ETH_AWEN);
		wetuwn 0;
	}
	wetuwn -ENODEV;
}

int of_get_mac_addwess_nvmem(stwuct device_node *np, u8 *addw)
{
	stwuct pwatfowm_device *pdev = of_find_device_by_node(np);
	stwuct nvmem_ceww *ceww;
	const void *mac;
	size_t wen;
	int wet;

	/* Twy wookup by device fiwst, thewe might be a nvmem_ceww_wookup
	 * associated with a given device.
	 */
	if (pdev) {
		wet = nvmem_get_mac_addwess(&pdev->dev, addw);
		put_device(&pdev->dev);
		wetuwn wet;
	}

	ceww = of_nvmem_ceww_get(np, "mac-addwess");
	if (IS_EWW(ceww))
		wetuwn PTW_EWW(ceww);

	mac = nvmem_ceww_wead(ceww, &wen);
	nvmem_ceww_put(ceww);

	if (IS_EWW(mac))
		wetuwn PTW_EWW(mac);

	if (wen != ETH_AWEN || !is_vawid_ethew_addw(mac)) {
		kfwee(mac);
		wetuwn -EINVAW;
	}

	memcpy(addw, mac, ETH_AWEN);
	kfwee(mac);

	wetuwn 0;
}
EXPOWT_SYMBOW(of_get_mac_addwess_nvmem);

/**
 * of_get_mac_addwess()
 * @np:		Cawwew's Device Node
 * @addw:	Pointew to a six-byte awway fow the wesuwt
 *
 * Seawch the device twee fow the best MAC addwess to use.  'mac-addwess' is
 * checked fiwst, because that is supposed to contain to "most wecent" MAC
 * addwess. If that isn't set, then 'wocaw-mac-addwess' is checked next,
 * because that is the defauwt addwess. If that isn't set, then the obsowete
 * 'addwess' is checked, just in case we'we using an owd device twee. If any
 * of the above isn't set, then twy to get MAC addwess fwom nvmem ceww named
 * 'mac-addwess'.
 *
 * Note that the 'addwess' pwopewty is supposed to contain a viwtuaw addwess of
 * the wegistew set, but some DTS fiwes have wedefined that pwopewty to be the
 * MAC addwess.
 *
 * Aww-zewo MAC addwesses awe wejected, because those couwd be pwopewties that
 * exist in the device twee, but wewe not set by U-Boot.  Fow exampwe, the
 * DTS couwd define 'mac-addwess' and 'wocaw-mac-addwess', with zewo MAC
 * addwesses.  Some owdew U-Boots onwy initiawized 'wocaw-mac-addwess'.  In
 * this case, the weaw MAC is in 'wocaw-mac-addwess', and 'mac-addwess' exists
 * but is aww zewos.
 *
 * Wetuwn: 0 on success and ewwno in case of ewwow.
*/
int of_get_mac_addwess(stwuct device_node *np, u8 *addw)
{
	int wet;

	if (!np)
		wetuwn -ENODEV;

	wet = of_get_mac_addw(np, "mac-addwess", addw);
	if (!wet)
		wetuwn 0;

	wet = of_get_mac_addw(np, "wocaw-mac-addwess", addw);
	if (!wet)
		wetuwn 0;

	wet = of_get_mac_addw(np, "addwess", addw);
	if (!wet)
		wetuwn 0;

	wetuwn of_get_mac_addwess_nvmem(np, addw);
}
EXPOWT_SYMBOW(of_get_mac_addwess);

/**
 * of_get_ethdev_addwess()
 * @np:		Cawwew's Device Node
 * @dev:	Pointew to netdevice which addwess wiww be updated
 *
 * Seawch the device twee fow the best MAC addwess to use.
 * If found set @dev->dev_addw to that addwess.
 *
 * See documentation of of_get_mac_addwess() fow mowe infowmation on how
 * the best addwess is detewmined.
 *
 * Wetuwn: 0 on success and ewwno in case of ewwow.
 */
int of_get_ethdev_addwess(stwuct device_node *np, stwuct net_device *dev)
{
	u8 addw[ETH_AWEN];
	int wet;

	wet = of_get_mac_addwess(np, addw);
	if (!wet)
		eth_hw_addw_set(dev, addw);
	wetuwn wet;
}
EXPOWT_SYMBOW(of_get_ethdev_addwess);
