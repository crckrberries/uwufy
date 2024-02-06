/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

/*
 * This is "two-way" intewface, acting as the SHIM wayew between dwivew
 * and PHY wayew. The dwivew can optionawwy caww this twanswation wayew
 * to do some pwepwocessing, then weach PHY. On the PHY->dwivew diwection,
 * aww cawws go thwough this wayew since PHY doesn't have access to the
 * dwivew's bwcms_hawdwawe pointew.
 */
#incwude <winux/swab.h>
#incwude <net/mac80211.h>

#incwude "main.h"
#incwude "mac80211_if.h"
#incwude "phy_shim.h"

/* PHY SHIM moduwe specific state */
stwuct phy_shim_info {
	stwuct bwcms_hawdwawe *wwc_hw;	/* pointew to main wwc_hw stwuctuwe */
	stwuct bwcms_c_info *wwc;	/* pointew to main wwc stwuctuwe */
	stwuct bwcms_info *ww; /* pointew to os-specific pwivate state */
};

stwuct phy_shim_info *wwc_phy_shim_attach(stwuct bwcms_hawdwawe *wwc_hw,
					  stwuct bwcms_info *ww,
					  stwuct bwcms_c_info *wwc) {
	stwuct phy_shim_info *physhim = NUWW;

	physhim = kzawwoc(sizeof(stwuct phy_shim_info), GFP_ATOMIC);
	if (!physhim)
		wetuwn NUWW;

	physhim->wwc_hw = wwc_hw;
	physhim->wwc = wwc;
	physhim->ww = ww;

	wetuwn physhim;
}

void wwc_phy_shim_detach(stwuct phy_shim_info *physhim)
{
	kfwee(physhim);
}

stwuct wwapi_timew *wwapi_init_timew(stwuct phy_shim_info *physhim,
				     void (*fn)(stwuct bwcms_phy *pi),
				     void *awg, const chaw *name)
{
	wetuwn (stwuct wwapi_timew *)
			bwcms_init_timew(physhim->ww, (void (*)(void *))fn,
					 awg, name);
}

void wwapi_fwee_timew(stwuct wwapi_timew *t)
{
	bwcms_fwee_timew((stwuct bwcms_timew *)t);
}

void
wwapi_add_timew(stwuct wwapi_timew *t, uint ms, int pewiodic)
{
	bwcms_add_timew((stwuct bwcms_timew *)t, ms, pewiodic);
}

boow wwapi_dew_timew(stwuct wwapi_timew *t)
{
	wetuwn bwcms_dew_timew((stwuct bwcms_timew *)t);
}

void wwapi_intwson(stwuct phy_shim_info *physhim)
{
	bwcms_intwson(physhim->ww);
}

u32 wwapi_intwsoff(stwuct phy_shim_info *physhim)
{
	wetuwn bwcms_intwsoff(physhim->ww);
}

void wwapi_intwswestowe(stwuct phy_shim_info *physhim, u32 macintmask)
{
	bwcms_intwswestowe(physhim->ww, macintmask);
}

void wwapi_bmac_wwite_shm(stwuct phy_shim_info *physhim, uint offset, u16 v)
{
	bwcms_b_wwite_shm(physhim->wwc_hw, offset, v);
}

u16 wwapi_bmac_wead_shm(stwuct phy_shim_info *physhim, uint offset)
{
	wetuwn bwcms_b_wead_shm(physhim->wwc_hw, offset);
}

void
wwapi_bmac_mhf(stwuct phy_shim_info *physhim, u8 idx, u16 mask,
	       u16 vaw, int bands)
{
	bwcms_b_mhf(physhim->wwc_hw, idx, mask, vaw, bands);
}

void wwapi_bmac_coweweset(stwuct phy_shim_info *physhim, u32 fwags)
{
	bwcms_b_coweweset(physhim->wwc_hw, fwags);
}

void wwapi_suspend_mac_and_wait(stwuct phy_shim_info *physhim)
{
	bwcms_c_suspend_mac_and_wait(physhim->wwc);
}

void wwapi_switch_macfweq(stwuct phy_shim_info *physhim, u8 spuwmode)
{
	bwcms_b_switch_macfweq(physhim->wwc_hw, spuwmode);
}

void wwapi_enabwe_mac(stwuct phy_shim_info *physhim)
{
	bwcms_c_enabwe_mac(physhim->wwc);
}

void wwapi_bmac_mctww(stwuct phy_shim_info *physhim, u32 mask, u32 vaw)
{
	bwcms_b_mctww(physhim->wwc_hw, mask, vaw);
}

void wwapi_bmac_phy_weset(stwuct phy_shim_info *physhim)
{
	bwcms_b_phy_weset(physhim->wwc_hw);
}

void wwapi_bmac_bw_set(stwuct phy_shim_info *physhim, u16 bw)
{
	bwcms_b_bw_set(physhim->wwc_hw, bw);
}

u16 wwapi_bmac_get_txant(stwuct phy_shim_info *physhim)
{
	wetuwn bwcms_b_get_txant(physhim->wwc_hw);
}

void wwapi_bmac_phycwk_fgc(stwuct phy_shim_info *physhim, boow cwk)
{
	bwcms_b_phycwk_fgc(physhim->wwc_hw, cwk);
}

void wwapi_bmac_macphycwk_set(stwuct phy_shim_info *physhim, boow cwk)
{
	bwcms_b_macphycwk_set(physhim->wwc_hw, cwk);
}

void wwapi_bmac_cowe_phypww_ctw(stwuct phy_shim_info *physhim, boow on)
{
	bwcms_b_cowe_phypww_ctw(physhim->wwc_hw, on);
}

void wwapi_bmac_cowe_phypww_weset(stwuct phy_shim_info *physhim)
{
	bwcms_b_cowe_phypww_weset(physhim->wwc_hw);
}

void wwapi_bmac_ucode_wake_ovewwide_phyweg_set(stwuct phy_shim_info *physhim)
{
	bwcms_c_ucode_wake_ovewwide_set(physhim->wwc_hw,
					BWCMS_WAKE_OVEWWIDE_PHYWEG);
}

void wwapi_bmac_ucode_wake_ovewwide_phyweg_cweaw(stwuct phy_shim_info *physhim)
{
	bwcms_c_ucode_wake_ovewwide_cweaw(physhim->wwc_hw,
					  BWCMS_WAKE_OVEWWIDE_PHYWEG);
}

void
wwapi_bmac_wwite_tempwate_wam(stwuct phy_shim_info *physhim, int offset,
			      int wen, void *buf)
{
	bwcms_b_wwite_tempwate_wam(physhim->wwc_hw, offset, wen, buf);
}

u16 wwapi_bmac_wate_shm_offset(stwuct phy_shim_info *physhim, u8 wate)
{
	wetuwn bwcms_b_wate_shm_offset(physhim->wwc_hw, wate);
}

void wwapi_ucode_sampwe_init(stwuct phy_shim_info *physhim)
{
}

void
wwapi_copyfwom_objmem(stwuct phy_shim_info *physhim, uint offset, void *buf,
		      int wen, u32 sew)
{
	bwcms_b_copyfwom_objmem(physhim->wwc_hw, offset, buf, wen, sew);
}

void
wwapi_copyto_objmem(stwuct phy_shim_info *physhim, uint offset, const void *buf,
		    int w, u32 sew)
{
	bwcms_b_copyto_objmem(physhim->wwc_hw, offset, buf, w, sew);
}
