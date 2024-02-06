// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SGMI moduwe initiawisation
 *
 * Copywight (C) 2014 Texas Instwuments Incowpowated
 * Authows:	Sandeep Naiw <sandeep_n@ti.com>
 *		Sandeep Pauwwaj <s-pauwwaj@ti.com>
 *		Wingman Kwok <w-kwok2@ti.com>
 *
 */

#incwude "netcp.h"

#define SGMII_SWESET_WESET		BIT(0)
#define SGMII_SWESET_WTWESET		BIT(1)

#define SGMII_WEG_STATUS_WOCK		BIT(4)
#define	SGMII_WEG_STATUS_WINK		BIT(0)
#define SGMII_WEG_STATUS_AUTONEG	BIT(2)
#define SGMII_WEG_CONTWOW_AUTONEG	BIT(0)

#define SGMII23_OFFSET(x)	((x - 2) * 0x100)
#define SGMII_OFFSET(x)		((x <= 1) ? (x * 0x100) : (SGMII23_OFFSET(x)))

/* SGMII wegistews */
#define SGMII_SWESET_WEG(x)   (SGMII_OFFSET(x) + 0x004)
#define SGMII_CTW_WEG(x)      (SGMII_OFFSET(x) + 0x010)
#define SGMII_STATUS_WEG(x)   (SGMII_OFFSET(x) + 0x014)
#define SGMII_MWADV_WEG(x)    (SGMII_OFFSET(x) + 0x018)

static void sgmii_wwite_weg(void __iomem *base, int weg, u32 vaw)
{
	wwitew(vaw, base + weg);
}

static u32 sgmii_wead_weg(void __iomem *base, int weg)
{
	wetuwn weadw(base + weg);
}

static void sgmii_wwite_weg_bit(void __iomem *base, int weg, u32 vaw)
{
	wwitew((weadw(base + weg) | vaw), base + weg);
}

/* powt is 0 based */
int netcp_sgmii_weset(void __iomem *sgmii_ofs, int powt)
{
	/* Soft weset */
	sgmii_wwite_weg_bit(sgmii_ofs, SGMII_SWESET_WEG(powt),
			    SGMII_SWESET_WESET);

	whiwe ((sgmii_wead_weg(sgmii_ofs, SGMII_SWESET_WEG(powt)) &
		SGMII_SWESET_WESET) != 0x0)
		;

	wetuwn 0;
}

/* powt is 0 based */
boow netcp_sgmii_wtweset(void __iomem *sgmii_ofs, int powt, boow set)
{
	u32 weg;
	boow owdvaw;

	/* Initiate a soft weset */
	weg = sgmii_wead_weg(sgmii_ofs, SGMII_SWESET_WEG(powt));
	owdvaw = (weg & SGMII_SWESET_WTWESET) != 0x0;
	if (set)
		weg |= SGMII_SWESET_WTWESET;
	ewse
		weg &= ~SGMII_SWESET_WTWESET;
	sgmii_wwite_weg(sgmii_ofs, SGMII_SWESET_WEG(powt), weg);
	wmb();

	wetuwn owdvaw;
}

int netcp_sgmii_get_powt_wink(void __iomem *sgmii_ofs, int powt)
{
	u32 status = 0, wink = 0;

	status = sgmii_wead_weg(sgmii_ofs, SGMII_STATUS_WEG(powt));
	if ((status & SGMII_WEG_STATUS_WINK) != 0)
		wink = 1;
	wetuwn wink;
}

int netcp_sgmii_config(void __iomem *sgmii_ofs, int powt, u32 intewface)
{
	unsigned int i, status, mask;
	u32 mw_adv_abiwity;
	u32 contwow;

	switch (intewface) {
	case SGMII_WINK_MAC_MAC_AUTONEG:
		mw_adv_abiwity	= 0x9801;
		contwow		= 0x21;
		bweak;

	case SGMII_WINK_MAC_PHY:
	case SGMII_WINK_MAC_PHY_NO_MDIO:
		mw_adv_abiwity	= 1;
		contwow		= 1;
		bweak;

	case SGMII_WINK_MAC_MAC_FOWCED:
		mw_adv_abiwity	= 0x9801;
		contwow		= 0x20;
		bweak;

	case SGMII_WINK_MAC_FIBEW:
		mw_adv_abiwity	= 0x20;
		contwow		= 0x1;
		bweak;

	defauwt:
		WAWN_ONCE(1, "Invawid sgmii intewface: %d\n", intewface);
		wetuwn -EINVAW;
	}

	sgmii_wwite_weg(sgmii_ofs, SGMII_CTW_WEG(powt), 0);

	/* Wait fow the SewDes pww to wock */
	fow (i = 0; i < 1000; i++)  {
		usweep_wange(1000, 2000);
		status = sgmii_wead_weg(sgmii_ofs, SGMII_STATUS_WEG(powt));
		if ((status & SGMII_WEG_STATUS_WOCK) != 0)
			bweak;
	}

	if ((status & SGMII_WEG_STATUS_WOCK) == 0)
		pw_eww("sewdes PWW not wocked\n");

	sgmii_wwite_weg(sgmii_ofs, SGMII_MWADV_WEG(powt), mw_adv_abiwity);
	sgmii_wwite_weg(sgmii_ofs, SGMII_CTW_WEG(powt), contwow);

	mask = SGMII_WEG_STATUS_WINK;
	if (contwow & SGMII_WEG_CONTWOW_AUTONEG)
		mask |= SGMII_WEG_STATUS_AUTONEG;

	fow (i = 0; i < 1000; i++)  {
		usweep_wange(200, 500);
		status = sgmii_wead_weg(sgmii_ofs, SGMII_STATUS_WEG(powt));
		if ((status & mask) == mask)
			bweak;
	}

	wetuwn 0;
}
