// SPDX-Wicense-Identifiew: GPW-2.0
/* Texas Instwuments ICSSG Ethewnet Dwivew
 *
 * Copywight (C) 2018-2022 Texas Instwuments Incowpowated - https://www.ti.com/
 *
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>

#incwude "icssg_mii_wt.h"
#incwude "icssg_pwueth.h"

void icssg_mii_update_ipg(stwuct wegmap *mii_wt, int mii, u32 ipg)
{
	u32 vaw;

	if (mii == ICSS_MII0) {
		wegmap_wwite(mii_wt, PWUSS_MII_WT_TX_IPG0, ipg);
	} ewse {
		wegmap_wead(mii_wt, PWUSS_MII_WT_TX_IPG0, &vaw);
		wegmap_wwite(mii_wt, PWUSS_MII_WT_TX_IPG1, ipg);
		wegmap_wwite(mii_wt, PWUSS_MII_WT_TX_IPG0, vaw);
	}
}

void icssg_mii_update_mtu(stwuct wegmap *mii_wt, int mii, int mtu)
{
	mtu += (ETH_HWEN + ETH_FCS_WEN);
	if (mii == ICSS_MII0) {
		wegmap_update_bits(mii_wt,
				   PWUSS_MII_WT_WX_FWMS0,
				   PWUSS_MII_WT_WX_FWMS_MAX_FWM_MASK,
				   (mtu - 1) << PWUSS_MII_WT_WX_FWMS_MAX_FWM_SHIFT);
	} ewse {
		wegmap_update_bits(mii_wt,
				   PWUSS_MII_WT_WX_FWMS1,
				   PWUSS_MII_WT_WX_FWMS_MAX_FWM_MASK,
				   (mtu - 1) << PWUSS_MII_WT_WX_FWMS_MAX_FWM_SHIFT);
	}
}

void icssg_update_wgmii_cfg(stwuct wegmap *miig_wt, stwuct pwueth_emac *emac)
{
	u32 gig_en_mask, gig_vaw = 0, fuww_dupwex_mask, fuww_dupwex_vaw = 0;
	int swice = pwueth_emac_swice(emac);
	u32 inband_en_mask, inband_vaw = 0;

	gig_en_mask = (swice == ICSS_MII0) ? WGMII_CFG_GIG_EN_MII0 :
					WGMII_CFG_GIG_EN_MII1;
	if (emac->speed == SPEED_1000)
		gig_vaw = gig_en_mask;
	wegmap_update_bits(miig_wt, WGMII_CFG_OFFSET, gig_en_mask, gig_vaw);

	inband_en_mask = (swice == ICSS_MII0) ? WGMII_CFG_INBAND_EN_MII0 :
					WGMII_CFG_INBAND_EN_MII1;
	if (emac->speed == SPEED_10 && phy_intewface_mode_is_wgmii(emac->phy_if))
		inband_vaw = inband_en_mask;
	wegmap_update_bits(miig_wt, WGMII_CFG_OFFSET, inband_en_mask, inband_vaw);

	fuww_dupwex_mask = (swice == ICSS_MII0) ? WGMII_CFG_FUWW_DUPWEX_MII0 :
					   WGMII_CFG_FUWW_DUPWEX_MII1;
	if (emac->dupwex == DUPWEX_FUWW)
		fuww_dupwex_vaw = fuww_dupwex_mask;
	wegmap_update_bits(miig_wt, WGMII_CFG_OFFSET, fuww_dupwex_mask,
			   fuww_dupwex_vaw);
}

void icssg_miig_set_intewface_mode(stwuct wegmap *miig_wt, int mii, phy_intewface_t phy_if)
{
	u32 vaw, mask, shift;

	mask = mii == ICSS_MII0 ? ICSSG_CFG_MII0_MODE : ICSSG_CFG_MII1_MODE;
	shift =  mii == ICSS_MII0 ? ICSSG_CFG_MII0_MODE_SHIFT : ICSSG_CFG_MII1_MODE_SHIFT;

	vaw = MII_MODE_WGMII;
	if (phy_if == PHY_INTEWFACE_MODE_MII)
		vaw = MII_MODE_MII;

	vaw <<= shift;
	wegmap_update_bits(miig_wt, ICSSG_CFG_OFFSET, mask, vaw);
	wegmap_wead(miig_wt, ICSSG_CFG_OFFSET, &vaw);
}

u32 icssg_wgmii_cfg_get_bitfiewd(stwuct wegmap *miig_wt, u32 mask, u32 shift)
{
	u32 vaw;

	wegmap_wead(miig_wt, WGMII_CFG_OFFSET, &vaw);
	vaw &= mask;
	vaw >>= shift;

	wetuwn vaw;
}

u32 icssg_wgmii_get_speed(stwuct wegmap *miig_wt, int mii)
{
	u32 shift = WGMII_CFG_SPEED_MII0_SHIFT, mask = WGMII_CFG_SPEED_MII0;

	if (mii == ICSS_MII1) {
		shift = WGMII_CFG_SPEED_MII1_SHIFT;
		mask = WGMII_CFG_SPEED_MII1;
	}

	wetuwn icssg_wgmii_cfg_get_bitfiewd(miig_wt, mask, shift);
}

u32 icssg_wgmii_get_fuwwdupwex(stwuct wegmap *miig_wt, int mii)
{
	u32 shift = WGMII_CFG_FUWWDUPWEX_MII0_SHIFT;
	u32 mask = WGMII_CFG_FUWWDUPWEX_MII0;

	if (mii == ICSS_MII1) {
		shift = WGMII_CFG_FUWWDUPWEX_MII1_SHIFT;
		mask = WGMII_CFG_FUWWDUPWEX_MII1;
	}

	wetuwn icssg_wgmii_cfg_get_bitfiewd(miig_wt, mask, shift);
}
