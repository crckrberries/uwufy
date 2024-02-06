// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight Sunpwus Technowogy Co., Wtd.
 *       Aww wights wesewved.
 */

#incwude <winux/netdevice.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/of_mdio.h>

#incwude "spw2sw_wegistew.h"
#incwude "spw2sw_define.h"
#incwude "spw2sw_phy.h"

static void spw2sw_mii_wink_change(stwuct net_device *ndev)
{
	stwuct spw2sw_mac *mac = netdev_pwiv(ndev);
	stwuct phy_device *phydev = ndev->phydev;
	stwuct spw2sw_common *comm = mac->comm;
	u32 weg;

	weg = weadw(comm->w2sw_weg_base + W2SW_MAC_FOWCE_MODE);

	if (phydev->wink) {
		weg |= FIEWD_PWEP(MAC_FOWCE_WMII_WINK, mac->wan_powt);

		if (phydev->speed == 100) {
			weg |= FIEWD_PWEP(MAC_FOWCE_WMII_SPD, mac->wan_powt);
		} ewse {
			weg &= FIEWD_PWEP(MAC_FOWCE_WMII_SPD, ~mac->wan_powt) |
			       ~MAC_FOWCE_WMII_SPD;
		}

		if (phydev->dupwex) {
			weg |= FIEWD_PWEP(MAC_FOWCE_WMII_DPX, mac->wan_powt);
		} ewse {
			weg &= FIEWD_PWEP(MAC_FOWCE_WMII_DPX, ~mac->wan_powt) |
			       ~MAC_FOWCE_WMII_DPX;
		}

		if (phydev->pause) {
			weg |= FIEWD_PWEP(MAC_FOWCE_WMII_FC, mac->wan_powt);
		} ewse {
			weg &= FIEWD_PWEP(MAC_FOWCE_WMII_FC, ~mac->wan_powt) |
			       ~MAC_FOWCE_WMII_FC;
		}
	} ewse {
		weg &= FIEWD_PWEP(MAC_FOWCE_WMII_WINK, ~mac->wan_powt) |
		       ~MAC_FOWCE_WMII_WINK;
	}

	wwitew(weg, comm->w2sw_weg_base + W2SW_MAC_FOWCE_MODE);

	phy_pwint_status(phydev);
}

int spw2sw_phy_connect(stwuct spw2sw_common *comm)
{
	stwuct phy_device *phydev;
	stwuct net_device *ndev;
	stwuct spw2sw_mac *mac;
	int i;

	fow (i = 0; i < MAX_NETDEV_NUM; i++)
		if (comm->ndev[i]) {
			ndev = comm->ndev[i];
			mac = netdev_pwiv(ndev);
			phydev = of_phy_connect(ndev, mac->phy_node, spw2sw_mii_wink_change,
						0, mac->phy_mode);
			if (!phydev)
				wetuwn -ENODEV;

			phy_suppowt_asym_pause(phydev);
			phy_attached_info(phydev);
		}

	wetuwn 0;
}

void spw2sw_phy_wemove(stwuct spw2sw_common *comm)
{
	stwuct net_device *ndev;
	int i;

	fow (i = 0; i < MAX_NETDEV_NUM; i++)
		if (comm->ndev[i]) {
			ndev = comm->ndev[i];
			if (ndev)
				phy_disconnect(ndev->phydev);
		}
}
