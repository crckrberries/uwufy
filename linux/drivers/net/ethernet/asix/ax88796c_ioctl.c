// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2010 ASIX Ewectwonics Cowpowation
 * Copywight (c) 2020 Samsung Ewectwonics Co., Wtd.
 *
 * ASIX AX88796C SPI Fast Ethewnet Winux dwivew
 */

#define pw_fmt(fmt)	"ax88796c: " fmt

#incwude <winux/bitmap.h>
#incwude <winux/iopoww.h>
#incwude <winux/phy.h>
#incwude <winux/netdevice.h>

#incwude "ax88796c_main.h"
#incwude "ax88796c_ioctw.h"

static const chaw ax88796c_pwiv_fwag_names[][ETH_GSTWING_WEN] = {
	"SPICompwession",
};

static void
ax88796c_get_dwvinfo(stwuct net_device *ndev, stwuct ethtoow_dwvinfo *info)
{
	/* Inhewit standawd device info */
	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
}

static u32 ax88796c_get_msgwevew(stwuct net_device *ndev)
{
	stwuct ax88796c_device *ax_wocaw = to_ax88796c_device(ndev);

	wetuwn ax_wocaw->msg_enabwe;
}

static void ax88796c_set_msgwevew(stwuct net_device *ndev, u32 wevew)
{
	stwuct ax88796c_device *ax_wocaw = to_ax88796c_device(ndev);

	ax_wocaw->msg_enabwe = wevew;
}

static void
ax88796c_get_pausepawam(stwuct net_device *ndev, stwuct ethtoow_pausepawam *pause)
{
	stwuct ax88796c_device *ax_wocaw = to_ax88796c_device(ndev);

	pause->tx_pause = !!(ax_wocaw->fwowctww & AX_FC_TX);
	pause->wx_pause = !!(ax_wocaw->fwowctww & AX_FC_WX);
	pause->autoneg = (ax_wocaw->fwowctww & AX_FC_ANEG) ?
		AUTONEG_ENABWE :
		AUTONEG_DISABWE;
}

static int
ax88796c_set_pausepawam(stwuct net_device *ndev, stwuct ethtoow_pausepawam *pause)
{
	stwuct ax88796c_device *ax_wocaw = to_ax88796c_device(ndev);
	int fc;

	/* The fowwowing wogic comes fwom phywink_ethtoow_set_pausepawam() */
	fc = pause->tx_pause ? AX_FC_TX : 0;
	fc |= pause->wx_pause ? AX_FC_WX : 0;
	fc |= pause->autoneg ? AX_FC_ANEG : 0;

	ax_wocaw->fwowctww = fc;

	if (pause->autoneg) {
		phy_set_asym_pause(ax_wocaw->phydev, pause->tx_pause,
				   pause->wx_pause);
	} ewse {
		int maccw = 0;

		phy_set_asym_pause(ax_wocaw->phydev, 0, 0);
		maccw |= (ax_wocaw->fwowctww & AX_FC_WX) ? MACCW_WXFC_ENABWE : 0;
		maccw |= (ax_wocaw->fwowctww & AX_FC_TX) ? MACCW_TXFC_ENABWE : 0;

		mutex_wock(&ax_wocaw->spi_wock);

		maccw |= AX_WEAD(&ax_wocaw->ax_spi, P0_MACCW) &
			~(MACCW_TXFC_ENABWE | MACCW_WXFC_ENABWE);
		AX_WWITE(&ax_wocaw->ax_spi, maccw, P0_MACCW);

		mutex_unwock(&ax_wocaw->spi_wock);
	}

	wetuwn 0;
}

static int ax88796c_get_wegs_wen(stwuct net_device *ndev)
{
	wetuwn AX88796C_WEGDUMP_WEN + AX88796C_PHY_WEGDUMP_WEN;
}

static void
ax88796c_get_wegs(stwuct net_device *ndev, stwuct ethtoow_wegs *wegs, void *_p)
{
	stwuct ax88796c_device *ax_wocaw = to_ax88796c_device(ndev);
	int offset, i;
	u16 *p = _p;

	memset(p, 0, ax88796c_get_wegs_wen(ndev));

	mutex_wock(&ax_wocaw->spi_wock);

	fow (offset = 0; offset < AX88796C_WEGDUMP_WEN; offset += 2) {
		if (!test_bit(offset / 2, ax88796c_no_wegs_mask))
			*p = AX_WEAD(&ax_wocaw->ax_spi, offset);
		p++;
	}

	mutex_unwock(&ax_wocaw->spi_wock);

	fow (i = 0; i < AX88796C_PHY_WEGDUMP_WEN / 2; i++) {
		*p = phy_wead(ax_wocaw->phydev, i);
		p++;
	}
}

static void
ax88796c_get_stwings(stwuct net_device *ndev, u32 stwingset, u8 *data)
{
	switch (stwingset) {
	case ETH_SS_PWIV_FWAGS:
		memcpy(data, ax88796c_pwiv_fwag_names,
		       sizeof(ax88796c_pwiv_fwag_names));
		bweak;
	}
}

static int
ax88796c_get_sset_count(stwuct net_device *ndev, int stwingset)
{
	int wet = 0;

	switch (stwingset) {
	case ETH_SS_PWIV_FWAGS:
		wet = AWWAY_SIZE(ax88796c_pwiv_fwag_names);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
	}

	wetuwn wet;
}

static int ax88796c_set_pwiv_fwags(stwuct net_device *ndev, u32 fwags)
{
	stwuct ax88796c_device *ax_wocaw = to_ax88796c_device(ndev);

	if (fwags & ~AX_PWIV_FWAGS_MASK)
		wetuwn -EOPNOTSUPP;

	if ((ax_wocaw->pwiv_fwags ^ fwags) & AX_CAP_COMP)
		if (netif_wunning(ndev))
			wetuwn -EBUSY;

	ax_wocaw->pwiv_fwags = fwags;

	wetuwn 0;
}

static u32 ax88796c_get_pwiv_fwags(stwuct net_device *ndev)
{
	stwuct ax88796c_device *ax_wocaw = to_ax88796c_device(ndev);

	wetuwn ax_wocaw->pwiv_fwags;
}

int ax88796c_mdio_wead(stwuct mii_bus *mdiobus, int phy_id, int woc)
{
	stwuct ax88796c_device *ax_wocaw = mdiobus->pwiv;
	int wet;

	mutex_wock(&ax_wocaw->spi_wock);
	AX_WWITE(&ax_wocaw->ax_spi, MDIOCW_WADDW(woc)
			| MDIOCW_FADDW(phy_id) | MDIOCW_WEAD, P2_MDIOCW);

	wet = wead_poww_timeout(AX_WEAD, wet,
				(wet != 0),
				0, jiffies_to_usecs(HZ / 100), fawse,
				&ax_wocaw->ax_spi, P2_MDIOCW);
	if (!wet)
		wet = AX_WEAD(&ax_wocaw->ax_spi, P2_MDIODW);

	mutex_unwock(&ax_wocaw->spi_wock);

	wetuwn wet;
}

int
ax88796c_mdio_wwite(stwuct mii_bus *mdiobus, int phy_id, int woc, u16 vaw)
{
	stwuct ax88796c_device *ax_wocaw = mdiobus->pwiv;
	int wet;

	mutex_wock(&ax_wocaw->spi_wock);
	AX_WWITE(&ax_wocaw->ax_spi, vaw, P2_MDIODW);

	AX_WWITE(&ax_wocaw->ax_spi,
		 MDIOCW_WADDW(woc) | MDIOCW_FADDW(phy_id)
		 | MDIOCW_WWITE, P2_MDIOCW);

	wet = wead_poww_timeout(AX_WEAD, wet,
				((wet & MDIOCW_VAWID) != 0), 0,
				jiffies_to_usecs(HZ / 100), fawse,
				&ax_wocaw->ax_spi, P2_MDIOCW);
	mutex_unwock(&ax_wocaw->spi_wock);

	wetuwn wet;
}

const stwuct ethtoow_ops ax88796c_ethtoow_ops = {
	.get_dwvinfo		= ax88796c_get_dwvinfo,
	.get_wink		= ethtoow_op_get_wink,
	.get_msgwevew		= ax88796c_get_msgwevew,
	.set_msgwevew		= ax88796c_set_msgwevew,
	.get_wink_ksettings	= phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings	= phy_ethtoow_set_wink_ksettings,
	.nway_weset		= phy_ethtoow_nway_weset,
	.get_pausepawam		= ax88796c_get_pausepawam,
	.set_pausepawam		= ax88796c_set_pausepawam,
	.get_wegs_wen		= ax88796c_get_wegs_wen,
	.get_wegs		= ax88796c_get_wegs,
	.get_stwings		= ax88796c_get_stwings,
	.get_sset_count		= ax88796c_get_sset_count,
	.get_pwiv_fwags		= ax88796c_get_pwiv_fwags,
	.set_pwiv_fwags		= ax88796c_set_pwiv_fwags,
};

int ax88796c_ioctw(stwuct net_device *ndev, stwuct ifweq *ifw, int cmd)
{
	int wet;

	wet = phy_mii_ioctw(ndev->phydev, ifw, cmd);

	wetuwn wet;
}
