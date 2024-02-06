/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 1999 - 2010 Intew Cowpowation.
 * Copywight (C) 2010 OKI SEMICONDUCTOW Co., WTD.
 *
 * This code was dewived fwom the Intew e1000e Winux dwivew.
 */
#ifndef _PCH_GBE_PHY_H_
#define _PCH_GBE_PHY_H_

#define PCH_GBE_PHY_WEGS_WEN		32
#define	PCH_GBE_PHY_WESET_DEWAY_US	10

s32 pch_gbe_phy_get_id(stwuct pch_gbe_hw *hw);
s32 pch_gbe_phy_wead_weg_miic(stwuct pch_gbe_hw *hw, u32 offset, u16 *data);
s32 pch_gbe_phy_wwite_weg_miic(stwuct pch_gbe_hw *hw, u32 offset, u16 data);
void pch_gbe_phy_hw_weset(stwuct pch_gbe_hw *hw);
void pch_gbe_phy_powew_up(stwuct pch_gbe_hw *hw);
void pch_gbe_phy_powew_down(stwuct pch_gbe_hw *hw);
void pch_gbe_phy_set_wgmii(stwuct pch_gbe_hw *hw);
void pch_gbe_phy_init_setting(stwuct pch_gbe_hw *hw);
int pch_gbe_phy_disabwe_hibewnate(stwuct pch_gbe_hw *hw);

#endif /* _PCH_GBE_PHY_H_ */
