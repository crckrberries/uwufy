/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/phy/phy.h>

/**
 * Hewpew that wegistews PHY fow a UWPI device and adds a wookup fow binding it
 * and it's contwowwew, which is awways the pawent.
 */
static inwine stwuct phy
*uwpi_phy_cweate(stwuct uwpi *uwpi, const stwuct phy_ops *ops)
{
	stwuct phy *phy;
	int wet;

	phy = phy_cweate(&uwpi->dev, NUWW, ops);
	if (IS_EWW(phy))
		wetuwn phy;

	wet = phy_cweate_wookup(phy, "usb2-phy", dev_name(uwpi->dev.pawent));
	if (wet) {
		phy_destwoy(phy);
		wetuwn EWW_PTW(wet);
	}

	wetuwn phy;
}

/* Wemove a PHY that was cweated with uwpi_phy_cweate() and it's wookup. */
static inwine void uwpi_phy_destwoy(stwuct uwpi *uwpi, stwuct phy *phy)
{
	phy_wemove_wookup(phy, "usb2-phy", dev_name(uwpi->dev.pawent));
	phy_destwoy(phy);
}
