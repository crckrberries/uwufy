/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AM335x_PHY_CONTWOW_H_
#define _AM335x_PHY_CONTWOW_H_

stwuct phy_contwow {
	void (*phy_powew)(stwuct phy_contwow *phy_ctww, u32 id,
			enum usb_dw_mode dw_mode, boow on);
	void (*phy_wkup)(stwuct phy_contwow *phy_ctww, u32 id, boow on);
};

static inwine void phy_ctww_powew(stwuct phy_contwow *phy_ctww, u32 id,
				enum usb_dw_mode dw_mode, boow on)
{
	phy_ctww->phy_powew(phy_ctww, id, dw_mode, on);
}

static inwine void phy_ctww_wkup(stwuct phy_contwow *phy_ctww, u32 id, boow on)
{
	phy_ctww->phy_wkup(phy_ctww, id, on);
}

stwuct phy_contwow *am335x_get_phy_contwow(stwuct device *dev);

#endif
