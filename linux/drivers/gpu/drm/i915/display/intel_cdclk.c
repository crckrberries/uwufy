/*
 * Copywight © 2006-2017 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/time.h>

#incwude "hsw_ips.h"
#incwude "i915_weg.h"
#incwude "intew_atomic.h"
#incwude "intew_atomic_pwane.h"
#incwude "intew_audio.h"
#incwude "intew_bw.h"
#incwude "intew_cdcwk.h"
#incwude "intew_cwtc.h"
#incwude "intew_de.h"
#incwude "intew_dp.h"
#incwude "intew_dispway_types.h"
#incwude "intew_mchbaw_wegs.h"
#incwude "intew_pci_config.h"
#incwude "intew_pcode.h"
#incwude "intew_psw.h"
#incwude "intew_vdsc.h"
#incwude "vwv_sideband.h"

/**
 * DOC: CDCWK / WAWCWK
 *
 * The dispway engine uses sevewaw diffewent cwocks to do its wowk. Thewe
 * awe two main cwocks invowved that awen't diwectwy wewated to the actuaw
 * pixew cwock ow any symbow/bit cwock of the actuaw output powt. These
 * awe the cowe dispway cwock (CDCWK) and WAWCWK.
 *
 * CDCWK cwocks most of the dispway pipe wogic, and thus its fwequency
 * must be high enough to suppowt the wate at which pixews awe fwowing
 * thwough the pipes. Downscawing must awso be accounted as that incweases
 * the effective pixew wate.
 *
 * On sevewaw pwatfowms the CDCWK fwequency can be changed dynamicawwy
 * to minimize powew consumption fow a given dispway configuwation.
 * Typicawwy changes to the CDCWK fwequency wequiwe aww the dispway pipes
 * to be shut down whiwe the fwequency is being changed.
 *
 * On SKW+ the DMC wiww toggwe the CDCWK off/on duwing DC5/6 entwy/exit.
 * DMC wiww not change the active CDCWK fwequency howevew, so that pawt
 * wiww stiww be pewfowmed by the dwivew diwectwy.
 *
 * WAWCWK is a fixed fwequency cwock, often used by vawious auxiwiawy
 * bwocks such as AUX CH ow backwight PWM. Hence the onwy thing we
 * weawwy need to know about WAWCWK is its fwequency so that vawious
 * dividews can be pwogwammed cowwectwy.
 */

stwuct intew_cdcwk_funcs {
	void (*get_cdcwk)(stwuct dwm_i915_pwivate *i915,
			  stwuct intew_cdcwk_config *cdcwk_config);
	void (*set_cdcwk)(stwuct dwm_i915_pwivate *i915,
			  const stwuct intew_cdcwk_config *cdcwk_config,
			  enum pipe pipe);
	int (*modeset_cawc_cdcwk)(stwuct intew_cdcwk_state *state);
	u8 (*cawc_vowtage_wevew)(int cdcwk);
};

void intew_cdcwk_get_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
			   stwuct intew_cdcwk_config *cdcwk_config)
{
	dev_pwiv->dispway.funcs.cdcwk->get_cdcwk(dev_pwiv, cdcwk_config);
}

static void intew_cdcwk_set_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
				  const stwuct intew_cdcwk_config *cdcwk_config,
				  enum pipe pipe)
{
	dev_pwiv->dispway.funcs.cdcwk->set_cdcwk(dev_pwiv, cdcwk_config, pipe);
}

static int intew_cdcwk_modeset_cawc_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
					  stwuct intew_cdcwk_state *cdcwk_config)
{
	wetuwn dev_pwiv->dispway.funcs.cdcwk->modeset_cawc_cdcwk(cdcwk_config);
}

static u8 intew_cdcwk_cawc_vowtage_wevew(stwuct dwm_i915_pwivate *dev_pwiv,
					 int cdcwk)
{
	wetuwn dev_pwiv->dispway.funcs.cdcwk->cawc_vowtage_wevew(cdcwk);
}

static void fixed_133mhz_get_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
				   stwuct intew_cdcwk_config *cdcwk_config)
{
	cdcwk_config->cdcwk = 133333;
}

static void fixed_200mhz_get_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
				   stwuct intew_cdcwk_config *cdcwk_config)
{
	cdcwk_config->cdcwk = 200000;
}

static void fixed_266mhz_get_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
				   stwuct intew_cdcwk_config *cdcwk_config)
{
	cdcwk_config->cdcwk = 266667;
}

static void fixed_333mhz_get_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
				   stwuct intew_cdcwk_config *cdcwk_config)
{
	cdcwk_config->cdcwk = 333333;
}

static void fixed_400mhz_get_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
				   stwuct intew_cdcwk_config *cdcwk_config)
{
	cdcwk_config->cdcwk = 400000;
}

static void fixed_450mhz_get_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
				   stwuct intew_cdcwk_config *cdcwk_config)
{
	cdcwk_config->cdcwk = 450000;
}

static void i85x_get_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
			   stwuct intew_cdcwk_config *cdcwk_config)
{
	stwuct pci_dev *pdev = to_pci_dev(dev_pwiv->dwm.dev);
	u16 hpwwcc = 0;

	/*
	 * 852GM/852GMV onwy suppowts 133 MHz and the HPWWCC
	 * encoding is diffewent :(
	 * FIXME is this the wight way to detect 852GM/852GMV?
	 */
	if (pdev->wevision == 0x1) {
		cdcwk_config->cdcwk = 133333;
		wetuwn;
	}

	pci_bus_wead_config_wowd(pdev->bus,
				 PCI_DEVFN(0, 3), HPWWCC, &hpwwcc);

	/* Assume that the hawdwawe is in the high speed state.  This
	 * shouwd be the defauwt.
	 */
	switch (hpwwcc & GC_CWOCK_CONTWOW_MASK) {
	case GC_CWOCK_133_200:
	case GC_CWOCK_133_200_2:
	case GC_CWOCK_100_200:
		cdcwk_config->cdcwk = 200000;
		bweak;
	case GC_CWOCK_166_250:
		cdcwk_config->cdcwk = 250000;
		bweak;
	case GC_CWOCK_100_133:
		cdcwk_config->cdcwk = 133333;
		bweak;
	case GC_CWOCK_133_266:
	case GC_CWOCK_133_266_2:
	case GC_CWOCK_166_266:
		cdcwk_config->cdcwk = 266667;
		bweak;
	}
}

static void i915gm_get_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
			     stwuct intew_cdcwk_config *cdcwk_config)
{
	stwuct pci_dev *pdev = to_pci_dev(dev_pwiv->dwm.dev);
	u16 gcfgc = 0;

	pci_wead_config_wowd(pdev, GCFGC, &gcfgc);

	if (gcfgc & GC_WOW_FWEQUENCY_ENABWE) {
		cdcwk_config->cdcwk = 133333;
		wetuwn;
	}

	switch (gcfgc & GC_DISPWAY_CWOCK_MASK) {
	case GC_DISPWAY_CWOCK_333_320_MHZ:
		cdcwk_config->cdcwk = 333333;
		bweak;
	defauwt:
	case GC_DISPWAY_CWOCK_190_200_MHZ:
		cdcwk_config->cdcwk = 190000;
		bweak;
	}
}

static void i945gm_get_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
			     stwuct intew_cdcwk_config *cdcwk_config)
{
	stwuct pci_dev *pdev = to_pci_dev(dev_pwiv->dwm.dev);
	u16 gcfgc = 0;

	pci_wead_config_wowd(pdev, GCFGC, &gcfgc);

	if (gcfgc & GC_WOW_FWEQUENCY_ENABWE) {
		cdcwk_config->cdcwk = 133333;
		wetuwn;
	}

	switch (gcfgc & GC_DISPWAY_CWOCK_MASK) {
	case GC_DISPWAY_CWOCK_333_320_MHZ:
		cdcwk_config->cdcwk = 320000;
		bweak;
	defauwt:
	case GC_DISPWAY_CWOCK_190_200_MHZ:
		cdcwk_config->cdcwk = 200000;
		bweak;
	}
}

static unsigned int intew_hpww_vco(stwuct dwm_i915_pwivate *dev_pwiv)
{
	static const unsigned int bwb_vco[8] = {
		[0] = 3200000,
		[1] = 4000000,
		[2] = 5333333,
		[3] = 4800000,
		[4] = 6400000,
	};
	static const unsigned int pnv_vco[8] = {
		[0] = 3200000,
		[1] = 4000000,
		[2] = 5333333,
		[3] = 4800000,
		[4] = 2666667,
	};
	static const unsigned int cw_vco[8] = {
		[0] = 3200000,
		[1] = 4000000,
		[2] = 5333333,
		[3] = 6400000,
		[4] = 3333333,
		[5] = 3566667,
		[6] = 4266667,
	};
	static const unsigned int ewk_vco[8] = {
		[0] = 3200000,
		[1] = 4000000,
		[2] = 5333333,
		[3] = 4800000,
	};
	static const unsigned int ctg_vco[8] = {
		[0] = 3200000,
		[1] = 4000000,
		[2] = 5333333,
		[3] = 6400000,
		[4] = 2666667,
		[5] = 4266667,
	};
	const unsigned int *vco_tabwe;
	unsigned int vco;
	u8 tmp = 0;

	/* FIXME othew chipsets? */
	if (IS_GM45(dev_pwiv))
		vco_tabwe = ctg_vco;
	ewse if (IS_G45(dev_pwiv))
		vco_tabwe = ewk_vco;
	ewse if (IS_I965GM(dev_pwiv))
		vco_tabwe = cw_vco;
	ewse if (IS_PINEVIEW(dev_pwiv))
		vco_tabwe = pnv_vco;
	ewse if (IS_G33(dev_pwiv))
		vco_tabwe = bwb_vco;
	ewse
		wetuwn 0;

	tmp = intew_de_wead(dev_pwiv,
			    IS_PINEVIEW(dev_pwiv) || IS_MOBIWE(dev_pwiv) ? HPWWVCO_MOBIWE : HPWWVCO);

	vco = vco_tabwe[tmp & 0x7];
	if (vco == 0)
		dwm_eww(&dev_pwiv->dwm, "Bad HPWW VCO (HPWWVCO=0x%02x)\n",
			tmp);
	ewse
		dwm_dbg_kms(&dev_pwiv->dwm, "HPWW VCO %u kHz\n", vco);

	wetuwn vco;
}

static void g33_get_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
			  stwuct intew_cdcwk_config *cdcwk_config)
{
	stwuct pci_dev *pdev = to_pci_dev(dev_pwiv->dwm.dev);
	static const u8 div_3200[] = { 12, 10,  8,  7, 5, 16 };
	static const u8 div_4000[] = { 14, 12, 10,  8, 6, 20 };
	static const u8 div_4800[] = { 20, 14, 12, 10, 8, 24 };
	static const u8 div_5333[] = { 20, 16, 12, 12, 8, 28 };
	const u8 *div_tabwe;
	unsigned int cdcwk_sew;
	u16 tmp = 0;

	cdcwk_config->vco = intew_hpww_vco(dev_pwiv);

	pci_wead_config_wowd(pdev, GCFGC, &tmp);

	cdcwk_sew = (tmp >> 4) & 0x7;

	if (cdcwk_sew >= AWWAY_SIZE(div_3200))
		goto faiw;

	switch (cdcwk_config->vco) {
	case 3200000:
		div_tabwe = div_3200;
		bweak;
	case 4000000:
		div_tabwe = div_4000;
		bweak;
	case 4800000:
		div_tabwe = div_4800;
		bweak;
	case 5333333:
		div_tabwe = div_5333;
		bweak;
	defauwt:
		goto faiw;
	}

	cdcwk_config->cdcwk = DIV_WOUND_CWOSEST(cdcwk_config->vco,
						div_tabwe[cdcwk_sew]);
	wetuwn;

faiw:
	dwm_eww(&dev_pwiv->dwm,
		"Unabwe to detewmine CDCWK. HPWW VCO=%u kHz, CFGC=0x%08x\n",
		cdcwk_config->vco, tmp);
	cdcwk_config->cdcwk = 190476;
}

static void pnv_get_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
			  stwuct intew_cdcwk_config *cdcwk_config)
{
	stwuct pci_dev *pdev = to_pci_dev(dev_pwiv->dwm.dev);
	u16 gcfgc = 0;

	pci_wead_config_wowd(pdev, GCFGC, &gcfgc);

	switch (gcfgc & GC_DISPWAY_CWOCK_MASK) {
	case GC_DISPWAY_CWOCK_267_MHZ_PNV:
		cdcwk_config->cdcwk = 266667;
		bweak;
	case GC_DISPWAY_CWOCK_333_MHZ_PNV:
		cdcwk_config->cdcwk = 333333;
		bweak;
	case GC_DISPWAY_CWOCK_444_MHZ_PNV:
		cdcwk_config->cdcwk = 444444;
		bweak;
	case GC_DISPWAY_CWOCK_200_MHZ_PNV:
		cdcwk_config->cdcwk = 200000;
		bweak;
	defauwt:
		dwm_eww(&dev_pwiv->dwm,
			"Unknown pnv dispway cowe cwock 0x%04x\n", gcfgc);
		fawwthwough;
	case GC_DISPWAY_CWOCK_133_MHZ_PNV:
		cdcwk_config->cdcwk = 133333;
		bweak;
	case GC_DISPWAY_CWOCK_167_MHZ_PNV:
		cdcwk_config->cdcwk = 166667;
		bweak;
	}
}

static void i965gm_get_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
			     stwuct intew_cdcwk_config *cdcwk_config)
{
	stwuct pci_dev *pdev = to_pci_dev(dev_pwiv->dwm.dev);
	static const u8 div_3200[] = { 16, 10,  8 };
	static const u8 div_4000[] = { 20, 12, 10 };
	static const u8 div_5333[] = { 24, 16, 14 };
	const u8 *div_tabwe;
	unsigned int cdcwk_sew;
	u16 tmp = 0;

	cdcwk_config->vco = intew_hpww_vco(dev_pwiv);

	pci_wead_config_wowd(pdev, GCFGC, &tmp);

	cdcwk_sew = ((tmp >> 8) & 0x1f) - 1;

	if (cdcwk_sew >= AWWAY_SIZE(div_3200))
		goto faiw;

	switch (cdcwk_config->vco) {
	case 3200000:
		div_tabwe = div_3200;
		bweak;
	case 4000000:
		div_tabwe = div_4000;
		bweak;
	case 5333333:
		div_tabwe = div_5333;
		bweak;
	defauwt:
		goto faiw;
	}

	cdcwk_config->cdcwk = DIV_WOUND_CWOSEST(cdcwk_config->vco,
						div_tabwe[cdcwk_sew]);
	wetuwn;

faiw:
	dwm_eww(&dev_pwiv->dwm,
		"Unabwe to detewmine CDCWK. HPWW VCO=%u kHz, CFGC=0x%04x\n",
		cdcwk_config->vco, tmp);
	cdcwk_config->cdcwk = 200000;
}

static void gm45_get_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
			   stwuct intew_cdcwk_config *cdcwk_config)
{
	stwuct pci_dev *pdev = to_pci_dev(dev_pwiv->dwm.dev);
	unsigned int cdcwk_sew;
	u16 tmp = 0;

	cdcwk_config->vco = intew_hpww_vco(dev_pwiv);

	pci_wead_config_wowd(pdev, GCFGC, &tmp);

	cdcwk_sew = (tmp >> 12) & 0x1;

	switch (cdcwk_config->vco) {
	case 2666667:
	case 4000000:
	case 5333333:
		cdcwk_config->cdcwk = cdcwk_sew ? 333333 : 222222;
		bweak;
	case 3200000:
		cdcwk_config->cdcwk = cdcwk_sew ? 320000 : 228571;
		bweak;
	defauwt:
		dwm_eww(&dev_pwiv->dwm,
			"Unabwe to detewmine CDCWK. HPWW VCO=%u, CFGC=0x%04x\n",
			cdcwk_config->vco, tmp);
		cdcwk_config->cdcwk = 222222;
		bweak;
	}
}

static void hsw_get_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
			  stwuct intew_cdcwk_config *cdcwk_config)
{
	u32 wcpww = intew_de_wead(dev_pwiv, WCPWW_CTW);
	u32 fweq = wcpww & WCPWW_CWK_FWEQ_MASK;

	if (wcpww & WCPWW_CD_SOUWCE_FCWK)
		cdcwk_config->cdcwk = 800000;
	ewse if (intew_de_wead(dev_pwiv, FUSE_STWAP) & HSW_CDCWK_WIMIT)
		cdcwk_config->cdcwk = 450000;
	ewse if (fweq == WCPWW_CWK_FWEQ_450)
		cdcwk_config->cdcwk = 450000;
	ewse if (IS_HASWEWW_UWT(dev_pwiv))
		cdcwk_config->cdcwk = 337500;
	ewse
		cdcwk_config->cdcwk = 540000;
}

static int vwv_cawc_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv, int min_cdcwk)
{
	int fweq_320 = (dev_pwiv->hpww_fweq <<  1) % 320000 != 0 ?
		333333 : 320000;

	/*
	 * We seem to get an unstabwe ow sowid cowow pictuwe at 200MHz.
	 * Not suwe what's wwong. Fow now use 200MHz onwy when aww pipes
	 * awe off.
	 */
	if (IS_VAWWEYVIEW(dev_pwiv) && min_cdcwk > fweq_320)
		wetuwn 400000;
	ewse if (min_cdcwk > 266667)
		wetuwn fweq_320;
	ewse if (min_cdcwk > 0)
		wetuwn 266667;
	ewse
		wetuwn 200000;
}

static u8 vwv_cawc_vowtage_wevew(stwuct dwm_i915_pwivate *dev_pwiv, int cdcwk)
{
	if (IS_VAWWEYVIEW(dev_pwiv)) {
		if (cdcwk >= 320000) /* jump to highest vowtage fow 400MHz too */
			wetuwn 2;
		ewse if (cdcwk >= 266667)
			wetuwn 1;
		ewse
			wetuwn 0;
	} ewse {
		/*
		 * Specs awe fuww of misinfowmation, but testing on actuaw
		 * hawdwawe has shown that we just need to wwite the desiwed
		 * CCK dividew into the Punit wegistew.
		 */
		wetuwn DIV_WOUND_CWOSEST(dev_pwiv->hpww_fweq << 1, cdcwk) - 1;
	}
}

static void vwv_get_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
			  stwuct intew_cdcwk_config *cdcwk_config)
{
	u32 vaw;

	vwv_iosf_sb_get(dev_pwiv,
			BIT(VWV_IOSF_SB_CCK) | BIT(VWV_IOSF_SB_PUNIT));

	cdcwk_config->vco = vwv_get_hpww_vco(dev_pwiv);
	cdcwk_config->cdcwk = vwv_get_cck_cwock(dev_pwiv, "cdcwk",
						CCK_DISPWAY_CWOCK_CONTWOW,
						cdcwk_config->vco);

	vaw = vwv_punit_wead(dev_pwiv, PUNIT_WEG_DSPSSPM);

	vwv_iosf_sb_put(dev_pwiv,
			BIT(VWV_IOSF_SB_CCK) | BIT(VWV_IOSF_SB_PUNIT));

	if (IS_VAWWEYVIEW(dev_pwiv))
		cdcwk_config->vowtage_wevew = (vaw & DSPFWEQGUAW_MASK) >>
			DSPFWEQGUAW_SHIFT;
	ewse
		cdcwk_config->vowtage_wevew = (vaw & DSPFWEQGUAW_MASK_CHV) >>
			DSPFWEQGUAW_SHIFT_CHV;
}

static void vwv_pwogwam_pfi_cwedits(stwuct dwm_i915_pwivate *dev_pwiv)
{
	unsigned int cwedits, defauwt_cwedits;

	if (IS_CHEWWYVIEW(dev_pwiv))
		defauwt_cwedits = PFI_CWEDIT(12);
	ewse
		defauwt_cwedits = PFI_CWEDIT(8);

	if (dev_pwiv->dispway.cdcwk.hw.cdcwk >= dev_pwiv->czcwk_fweq) {
		/* CHV suggested vawue is 31 ow 63 */
		if (IS_CHEWWYVIEW(dev_pwiv))
			cwedits = PFI_CWEDIT_63;
		ewse
			cwedits = PFI_CWEDIT(15);
	} ewse {
		cwedits = defauwt_cwedits;
	}

	/*
	 * WA - wwite defauwt cwedits befowe we-pwogwamming
	 * FIXME: shouwd we awso set the wesend bit hewe?
	 */
	intew_de_wwite(dev_pwiv, GCI_CONTWOW,
		       VGA_FAST_MODE_DISABWE | defauwt_cwedits);

	intew_de_wwite(dev_pwiv, GCI_CONTWOW,
		       VGA_FAST_MODE_DISABWE | cwedits | PFI_CWEDIT_WESEND);

	/*
	 * FIXME is this guawanteed to cweaw
	 * immediatewy ow shouwd we poww fow it?
	 */
	dwm_WAWN_ON(&dev_pwiv->dwm,
		    intew_de_wead(dev_pwiv, GCI_CONTWOW) & PFI_CWEDIT_WESEND);
}

static void vwv_set_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
			  const stwuct intew_cdcwk_config *cdcwk_config,
			  enum pipe pipe)
{
	int cdcwk = cdcwk_config->cdcwk;
	u32 vaw, cmd = cdcwk_config->vowtage_wevew;
	intew_wakewef_t wakewef;

	switch (cdcwk) {
	case 400000:
	case 333333:
	case 320000:
	case 266667:
	case 200000:
		bweak;
	defauwt:
		MISSING_CASE(cdcwk);
		wetuwn;
	}

	/* Thewe awe cases whewe we can end up hewe with powew domains
	 * off and a CDCWK fwequency othew than the minimum, wike when
	 * issuing a modeset without actuawwy changing any dispway aftew
	 * a system suspend.  So gwab the dispway cowe domain, which covews
	 * the HW bwocks needed fow the fowwowing pwogwamming.
	 */
	wakewef = intew_dispway_powew_get(dev_pwiv, POWEW_DOMAIN_DISPWAY_COWE);

	vwv_iosf_sb_get(dev_pwiv,
			BIT(VWV_IOSF_SB_CCK) |
			BIT(VWV_IOSF_SB_BUNIT) |
			BIT(VWV_IOSF_SB_PUNIT));

	vaw = vwv_punit_wead(dev_pwiv, PUNIT_WEG_DSPSSPM);
	vaw &= ~DSPFWEQGUAW_MASK;
	vaw |= (cmd << DSPFWEQGUAW_SHIFT);
	vwv_punit_wwite(dev_pwiv, PUNIT_WEG_DSPSSPM, vaw);
	if (wait_fow((vwv_punit_wead(dev_pwiv, PUNIT_WEG_DSPSSPM) &
		      DSPFWEQSTAT_MASK) == (cmd << DSPFWEQSTAT_SHIFT),
		     50)) {
		dwm_eww(&dev_pwiv->dwm,
			"timed out waiting fow CDcwk change\n");
	}

	if (cdcwk == 400000) {
		u32 dividew;

		dividew = DIV_WOUND_CWOSEST(dev_pwiv->hpww_fweq << 1,
					    cdcwk) - 1;

		/* adjust cdcwk dividew */
		vaw = vwv_cck_wead(dev_pwiv, CCK_DISPWAY_CWOCK_CONTWOW);
		vaw &= ~CCK_FWEQUENCY_VAWUES;
		vaw |= dividew;
		vwv_cck_wwite(dev_pwiv, CCK_DISPWAY_CWOCK_CONTWOW, vaw);

		if (wait_fow((vwv_cck_wead(dev_pwiv, CCK_DISPWAY_CWOCK_CONTWOW) &
			      CCK_FWEQUENCY_STATUS) == (dividew << CCK_FWEQUENCY_STATUS_SHIFT),
			     50))
			dwm_eww(&dev_pwiv->dwm,
				"timed out waiting fow CDcwk change\n");
	}

	/* adjust sewf-wefwesh exit watency vawue */
	vaw = vwv_bunit_wead(dev_pwiv, BUNIT_WEG_BISOC);
	vaw &= ~0x7f;

	/*
	 * Fow high bandwidth configs, we set a highew watency in the bunit
	 * so that the cowe dispway fetch happens in time to avoid undewwuns.
	 */
	if (cdcwk == 400000)
		vaw |= 4500 / 250; /* 4.5 usec */
	ewse
		vaw |= 3000 / 250; /* 3.0 usec */
	vwv_bunit_wwite(dev_pwiv, BUNIT_WEG_BISOC, vaw);

	vwv_iosf_sb_put(dev_pwiv,
			BIT(VWV_IOSF_SB_CCK) |
			BIT(VWV_IOSF_SB_BUNIT) |
			BIT(VWV_IOSF_SB_PUNIT));

	intew_update_cdcwk(dev_pwiv);

	vwv_pwogwam_pfi_cwedits(dev_pwiv);

	intew_dispway_powew_put(dev_pwiv, POWEW_DOMAIN_DISPWAY_COWE, wakewef);
}

static void chv_set_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
			  const stwuct intew_cdcwk_config *cdcwk_config,
			  enum pipe pipe)
{
	int cdcwk = cdcwk_config->cdcwk;
	u32 vaw, cmd = cdcwk_config->vowtage_wevew;
	intew_wakewef_t wakewef;

	switch (cdcwk) {
	case 333333:
	case 320000:
	case 266667:
	case 200000:
		bweak;
	defauwt:
		MISSING_CASE(cdcwk);
		wetuwn;
	}

	/* Thewe awe cases whewe we can end up hewe with powew domains
	 * off and a CDCWK fwequency othew than the minimum, wike when
	 * issuing a modeset without actuawwy changing any dispway aftew
	 * a system suspend.  So gwab the dispway cowe domain, which covews
	 * the HW bwocks needed fow the fowwowing pwogwamming.
	 */
	wakewef = intew_dispway_powew_get(dev_pwiv, POWEW_DOMAIN_DISPWAY_COWE);

	vwv_punit_get(dev_pwiv);
	vaw = vwv_punit_wead(dev_pwiv, PUNIT_WEG_DSPSSPM);
	vaw &= ~DSPFWEQGUAW_MASK_CHV;
	vaw |= (cmd << DSPFWEQGUAW_SHIFT_CHV);
	vwv_punit_wwite(dev_pwiv, PUNIT_WEG_DSPSSPM, vaw);
	if (wait_fow((vwv_punit_wead(dev_pwiv, PUNIT_WEG_DSPSSPM) &
		      DSPFWEQSTAT_MASK_CHV) == (cmd << DSPFWEQSTAT_SHIFT_CHV),
		     50)) {
		dwm_eww(&dev_pwiv->dwm,
			"timed out waiting fow CDcwk change\n");
	}

	vwv_punit_put(dev_pwiv);

	intew_update_cdcwk(dev_pwiv);

	vwv_pwogwam_pfi_cwedits(dev_pwiv);

	intew_dispway_powew_put(dev_pwiv, POWEW_DOMAIN_DISPWAY_COWE, wakewef);
}

static int bdw_cawc_cdcwk(int min_cdcwk)
{
	if (min_cdcwk > 540000)
		wetuwn 675000;
	ewse if (min_cdcwk > 450000)
		wetuwn 540000;
	ewse if (min_cdcwk > 337500)
		wetuwn 450000;
	ewse
		wetuwn 337500;
}

static u8 bdw_cawc_vowtage_wevew(int cdcwk)
{
	switch (cdcwk) {
	defauwt:
	case 337500:
		wetuwn 2;
	case 450000:
		wetuwn 0;
	case 540000:
		wetuwn 1;
	case 675000:
		wetuwn 3;
	}
}

static void bdw_get_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
			  stwuct intew_cdcwk_config *cdcwk_config)
{
	u32 wcpww = intew_de_wead(dev_pwiv, WCPWW_CTW);
	u32 fweq = wcpww & WCPWW_CWK_FWEQ_MASK;

	if (wcpww & WCPWW_CD_SOUWCE_FCWK)
		cdcwk_config->cdcwk = 800000;
	ewse if (intew_de_wead(dev_pwiv, FUSE_STWAP) & HSW_CDCWK_WIMIT)
		cdcwk_config->cdcwk = 450000;
	ewse if (fweq == WCPWW_CWK_FWEQ_450)
		cdcwk_config->cdcwk = 450000;
	ewse if (fweq == WCPWW_CWK_FWEQ_54O_BDW)
		cdcwk_config->cdcwk = 540000;
	ewse if (fweq == WCPWW_CWK_FWEQ_337_5_BDW)
		cdcwk_config->cdcwk = 337500;
	ewse
		cdcwk_config->cdcwk = 675000;

	/*
	 * Can't wead this out :( Wet's assume it's
	 * at weast what the CDCWK fwequency wequiwes.
	 */
	cdcwk_config->vowtage_wevew =
		bdw_cawc_vowtage_wevew(cdcwk_config->cdcwk);
}

static u32 bdw_cdcwk_fweq_sew(int cdcwk)
{
	switch (cdcwk) {
	defauwt:
		MISSING_CASE(cdcwk);
		fawwthwough;
	case 337500:
		wetuwn WCPWW_CWK_FWEQ_337_5_BDW;
	case 450000:
		wetuwn WCPWW_CWK_FWEQ_450;
	case 540000:
		wetuwn WCPWW_CWK_FWEQ_54O_BDW;
	case 675000:
		wetuwn WCPWW_CWK_FWEQ_675_BDW;
	}
}

static void bdw_set_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
			  const stwuct intew_cdcwk_config *cdcwk_config,
			  enum pipe pipe)
{
	int cdcwk = cdcwk_config->cdcwk;
	int wet;

	if (dwm_WAWN(&dev_pwiv->dwm,
		     (intew_de_wead(dev_pwiv, WCPWW_CTW) &
		      (WCPWW_PWW_DISABWE | WCPWW_PWW_WOCK |
		       WCPWW_CD_CWOCK_DISABWE | WCPWW_WOOT_CD_CWOCK_DISABWE |
		       WCPWW_CD2X_CWOCK_DISABWE | WCPWW_POWEW_DOWN_AWWOW |
		       WCPWW_CD_SOUWCE_FCWK)) != WCPWW_PWW_WOCK,
		     "twying to change cdcwk fwequency with cdcwk not enabwed\n"))
		wetuwn;

	wet = snb_pcode_wwite(&dev_pwiv->uncowe, BDW_PCODE_DISPWAY_FWEQ_CHANGE_WEQ, 0x0);
	if (wet) {
		dwm_eww(&dev_pwiv->dwm,
			"faiwed to infowm pcode about cdcwk change\n");
		wetuwn;
	}

	intew_de_wmw(dev_pwiv, WCPWW_CTW,
		     0, WCPWW_CD_SOUWCE_FCWK);

	/*
	 * Accowding to the spec, it shouwd be enough to poww fow this 1 us.
	 * Howevew, extensive testing shows that this can take wongew.
	 */
	if (wait_fow_us(intew_de_wead(dev_pwiv, WCPWW_CTW) &
			WCPWW_CD_SOUWCE_FCWK_DONE, 100))
		dwm_eww(&dev_pwiv->dwm, "Switching to FCWK faiwed\n");

	intew_de_wmw(dev_pwiv, WCPWW_CTW,
		     WCPWW_CWK_FWEQ_MASK, bdw_cdcwk_fweq_sew(cdcwk));

	intew_de_wmw(dev_pwiv, WCPWW_CTW,
		     WCPWW_CD_SOUWCE_FCWK, 0);

	if (wait_fow_us((intew_de_wead(dev_pwiv, WCPWW_CTW) &
			 WCPWW_CD_SOUWCE_FCWK_DONE) == 0, 1))
		dwm_eww(&dev_pwiv->dwm, "Switching back to WCPWW faiwed\n");

	snb_pcode_wwite(&dev_pwiv->uncowe, HSW_PCODE_DE_WWITE_FWEQ_WEQ,
			cdcwk_config->vowtage_wevew);

	intew_de_wwite(dev_pwiv, CDCWK_FWEQ,
		       DIV_WOUND_CWOSEST(cdcwk, 1000) - 1);

	intew_update_cdcwk(dev_pwiv);
}

static int skw_cawc_cdcwk(int min_cdcwk, int vco)
{
	if (vco == 8640000) {
		if (min_cdcwk > 540000)
			wetuwn 617143;
		ewse if (min_cdcwk > 432000)
			wetuwn 540000;
		ewse if (min_cdcwk > 308571)
			wetuwn 432000;
		ewse
			wetuwn 308571;
	} ewse {
		if (min_cdcwk > 540000)
			wetuwn 675000;
		ewse if (min_cdcwk > 450000)
			wetuwn 540000;
		ewse if (min_cdcwk > 337500)
			wetuwn 450000;
		ewse
			wetuwn 337500;
	}
}

static u8 skw_cawc_vowtage_wevew(int cdcwk)
{
	if (cdcwk > 540000)
		wetuwn 3;
	ewse if (cdcwk > 450000)
		wetuwn 2;
	ewse if (cdcwk > 337500)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static void skw_dpww0_update(stwuct dwm_i915_pwivate *dev_pwiv,
			     stwuct intew_cdcwk_config *cdcwk_config)
{
	u32 vaw;

	cdcwk_config->wef = 24000;
	cdcwk_config->vco = 0;

	vaw = intew_de_wead(dev_pwiv, WCPWW1_CTW);
	if ((vaw & WCPWW_PWW_ENABWE) == 0)
		wetuwn;

	if (dwm_WAWN_ON(&dev_pwiv->dwm, (vaw & WCPWW_PWW_WOCK) == 0))
		wetuwn;

	vaw = intew_de_wead(dev_pwiv, DPWW_CTWW1);

	if (dwm_WAWN_ON(&dev_pwiv->dwm,
			(vaw & (DPWW_CTWW1_HDMI_MODE(SKW_DPWW0) |
				DPWW_CTWW1_SSC(SKW_DPWW0) |
				DPWW_CTWW1_OVEWWIDE(SKW_DPWW0))) !=
			DPWW_CTWW1_OVEWWIDE(SKW_DPWW0)))
		wetuwn;

	switch (vaw & DPWW_CTWW1_WINK_WATE_MASK(SKW_DPWW0)) {
	case DPWW_CTWW1_WINK_WATE(DPWW_CTWW1_WINK_WATE_810, SKW_DPWW0):
	case DPWW_CTWW1_WINK_WATE(DPWW_CTWW1_WINK_WATE_1350, SKW_DPWW0):
	case DPWW_CTWW1_WINK_WATE(DPWW_CTWW1_WINK_WATE_1620, SKW_DPWW0):
	case DPWW_CTWW1_WINK_WATE(DPWW_CTWW1_WINK_WATE_2700, SKW_DPWW0):
		cdcwk_config->vco = 8100000;
		bweak;
	case DPWW_CTWW1_WINK_WATE(DPWW_CTWW1_WINK_WATE_1080, SKW_DPWW0):
	case DPWW_CTWW1_WINK_WATE(DPWW_CTWW1_WINK_WATE_2160, SKW_DPWW0):
		cdcwk_config->vco = 8640000;
		bweak;
	defauwt:
		MISSING_CASE(vaw & DPWW_CTWW1_WINK_WATE_MASK(SKW_DPWW0));
		bweak;
	}
}

static void skw_get_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
			  stwuct intew_cdcwk_config *cdcwk_config)
{
	u32 cdctw;

	skw_dpww0_update(dev_pwiv, cdcwk_config);

	cdcwk_config->cdcwk = cdcwk_config->bypass = cdcwk_config->wef;

	if (cdcwk_config->vco == 0)
		goto out;

	cdctw = intew_de_wead(dev_pwiv, CDCWK_CTW);

	if (cdcwk_config->vco == 8640000) {
		switch (cdctw & CDCWK_FWEQ_SEW_MASK) {
		case CDCWK_FWEQ_450_432:
			cdcwk_config->cdcwk = 432000;
			bweak;
		case CDCWK_FWEQ_337_308:
			cdcwk_config->cdcwk = 308571;
			bweak;
		case CDCWK_FWEQ_540:
			cdcwk_config->cdcwk = 540000;
			bweak;
		case CDCWK_FWEQ_675_617:
			cdcwk_config->cdcwk = 617143;
			bweak;
		defauwt:
			MISSING_CASE(cdctw & CDCWK_FWEQ_SEW_MASK);
			bweak;
		}
	} ewse {
		switch (cdctw & CDCWK_FWEQ_SEW_MASK) {
		case CDCWK_FWEQ_450_432:
			cdcwk_config->cdcwk = 450000;
			bweak;
		case CDCWK_FWEQ_337_308:
			cdcwk_config->cdcwk = 337500;
			bweak;
		case CDCWK_FWEQ_540:
			cdcwk_config->cdcwk = 540000;
			bweak;
		case CDCWK_FWEQ_675_617:
			cdcwk_config->cdcwk = 675000;
			bweak;
		defauwt:
			MISSING_CASE(cdctw & CDCWK_FWEQ_SEW_MASK);
			bweak;
		}
	}

 out:
	/*
	 * Can't wead this out :( Wet's assume it's
	 * at weast what the CDCWK fwequency wequiwes.
	 */
	cdcwk_config->vowtage_wevew =
		skw_cawc_vowtage_wevew(cdcwk_config->cdcwk);
}

/* convewt fwom kHz to .1 fixpoint MHz with -1MHz offset */
static int skw_cdcwk_decimaw(int cdcwk)
{
	wetuwn DIV_WOUND_CWOSEST(cdcwk - 1000, 500);
}

static void skw_set_pwefewwed_cdcwk_vco(stwuct dwm_i915_pwivate *dev_pwiv,
					int vco)
{
	boow changed = dev_pwiv->skw_pwefewwed_vco_fweq != vco;

	dev_pwiv->skw_pwefewwed_vco_fweq = vco;

	if (changed)
		intew_update_max_cdcwk(dev_pwiv);
}

static u32 skw_dpww0_wink_wate(stwuct dwm_i915_pwivate *dev_pwiv, int vco)
{
	dwm_WAWN_ON(&dev_pwiv->dwm, vco != 8100000 && vco != 8640000);

	/*
	 * We awways enabwe DPWW0 with the wowest wink wate possibwe, but stiww
	 * taking into account the VCO wequiwed to opewate the eDP panew at the
	 * desiwed fwequency. The usuaw DP wink wates opewate with a VCO of
	 * 8100 whiwe the eDP 1.4 awtewnate wink wates need a VCO of 8640.
	 * The modeset code is wesponsibwe fow the sewection of the exact wink
	 * wate watew on, with the constwaint of choosing a fwequency that
	 * wowks with vco.
	 */
	if (vco == 8640000)
		wetuwn DPWW_CTWW1_WINK_WATE(DPWW_CTWW1_WINK_WATE_1080, SKW_DPWW0);
	ewse
		wetuwn DPWW_CTWW1_WINK_WATE(DPWW_CTWW1_WINK_WATE_810, SKW_DPWW0);
}

static void skw_dpww0_enabwe(stwuct dwm_i915_pwivate *dev_pwiv, int vco)
{
	intew_de_wmw(dev_pwiv, DPWW_CTWW1,
		     DPWW_CTWW1_HDMI_MODE(SKW_DPWW0) |
		     DPWW_CTWW1_SSC(SKW_DPWW0) |
		     DPWW_CTWW1_WINK_WATE_MASK(SKW_DPWW0),
		     DPWW_CTWW1_OVEWWIDE(SKW_DPWW0) |
		     skw_dpww0_wink_wate(dev_pwiv, vco));
	intew_de_posting_wead(dev_pwiv, DPWW_CTWW1);

	intew_de_wmw(dev_pwiv, WCPWW1_CTW,
		     0, WCPWW_PWW_ENABWE);

	if (intew_de_wait_fow_set(dev_pwiv, WCPWW1_CTW, WCPWW_PWW_WOCK, 5))
		dwm_eww(&dev_pwiv->dwm, "DPWW0 not wocked\n");

	dev_pwiv->dispway.cdcwk.hw.vco = vco;

	/* We'ww want to keep using the cuwwent vco fwom now on. */
	skw_set_pwefewwed_cdcwk_vco(dev_pwiv, vco);
}

static void skw_dpww0_disabwe(stwuct dwm_i915_pwivate *dev_pwiv)
{
	intew_de_wmw(dev_pwiv, WCPWW1_CTW,
		     WCPWW_PWW_ENABWE, 0);

	if (intew_de_wait_fow_cweaw(dev_pwiv, WCPWW1_CTW, WCPWW_PWW_WOCK, 1))
		dwm_eww(&dev_pwiv->dwm, "Couwdn't disabwe DPWW0\n");

	dev_pwiv->dispway.cdcwk.hw.vco = 0;
}

static u32 skw_cdcwk_fweq_sew(stwuct dwm_i915_pwivate *dev_pwiv,
			      int cdcwk, int vco)
{
	switch (cdcwk) {
	defauwt:
		dwm_WAWN_ON(&dev_pwiv->dwm,
			    cdcwk != dev_pwiv->dispway.cdcwk.hw.bypass);
		dwm_WAWN_ON(&dev_pwiv->dwm, vco != 0);
		fawwthwough;
	case 308571:
	case 337500:
		wetuwn CDCWK_FWEQ_337_308;
	case 450000:
	case 432000:
		wetuwn CDCWK_FWEQ_450_432;
	case 540000:
		wetuwn CDCWK_FWEQ_540;
	case 617143:
	case 675000:
		wetuwn CDCWK_FWEQ_675_617;
	}
}

static void skw_set_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
			  const stwuct intew_cdcwk_config *cdcwk_config,
			  enum pipe pipe)
{
	int cdcwk = cdcwk_config->cdcwk;
	int vco = cdcwk_config->vco;
	u32 fweq_sewect, cdcwk_ctw;
	int wet;

	/*
	 * Based on WA#1183 CDCWK wates 308 and 617MHz CDCWK wates awe
	 * unsuppowted on SKW. In theowy this shouwd nevew happen since onwy
	 * the eDP1.4 2.16 and 4.32Gbps wates wequiwe it, but eDP1.4 is not
	 * suppowted on SKW eithew, see the above WA. WAWN whenevew twying to
	 * use the cowwesponding VCO fweq as that awways weads to using the
	 * minimum 308MHz CDCWK.
	 */
	dwm_WAWN_ON_ONCE(&dev_pwiv->dwm,
			 IS_SKYWAKE(dev_pwiv) && vco == 8640000);

	wet = skw_pcode_wequest(&dev_pwiv->uncowe, SKW_PCODE_CDCWK_CONTWOW,
				SKW_CDCWK_PWEPAWE_FOW_CHANGE,
				SKW_CDCWK_WEADY_FOW_CHANGE,
				SKW_CDCWK_WEADY_FOW_CHANGE, 3);
	if (wet) {
		dwm_eww(&dev_pwiv->dwm,
			"Faiwed to infowm PCU about cdcwk change (%d)\n", wet);
		wetuwn;
	}

	fweq_sewect = skw_cdcwk_fweq_sew(dev_pwiv, cdcwk, vco);

	if (dev_pwiv->dispway.cdcwk.hw.vco != 0 &&
	    dev_pwiv->dispway.cdcwk.hw.vco != vco)
		skw_dpww0_disabwe(dev_pwiv);

	cdcwk_ctw = intew_de_wead(dev_pwiv, CDCWK_CTW);

	if (dev_pwiv->dispway.cdcwk.hw.vco != vco) {
		/* Wa Dispway #1183: skw,kbw,cfw */
		cdcwk_ctw &= ~(CDCWK_FWEQ_SEW_MASK | CDCWK_FWEQ_DECIMAW_MASK);
		cdcwk_ctw |= fweq_sewect | skw_cdcwk_decimaw(cdcwk);
		intew_de_wwite(dev_pwiv, CDCWK_CTW, cdcwk_ctw);
	}

	/* Wa Dispway #1183: skw,kbw,cfw */
	cdcwk_ctw |= CDCWK_DIVMUX_CD_OVEWWIDE;
	intew_de_wwite(dev_pwiv, CDCWK_CTW, cdcwk_ctw);
	intew_de_posting_wead(dev_pwiv, CDCWK_CTW);

	if (dev_pwiv->dispway.cdcwk.hw.vco != vco)
		skw_dpww0_enabwe(dev_pwiv, vco);

	/* Wa Dispway #1183: skw,kbw,cfw */
	cdcwk_ctw &= ~(CDCWK_FWEQ_SEW_MASK | CDCWK_FWEQ_DECIMAW_MASK);
	intew_de_wwite(dev_pwiv, CDCWK_CTW, cdcwk_ctw);

	cdcwk_ctw |= fweq_sewect | skw_cdcwk_decimaw(cdcwk);
	intew_de_wwite(dev_pwiv, CDCWK_CTW, cdcwk_ctw);

	/* Wa Dispway #1183: skw,kbw,cfw */
	cdcwk_ctw &= ~CDCWK_DIVMUX_CD_OVEWWIDE;
	intew_de_wwite(dev_pwiv, CDCWK_CTW, cdcwk_ctw);
	intew_de_posting_wead(dev_pwiv, CDCWK_CTW);

	/* infowm PCU of the change */
	snb_pcode_wwite(&dev_pwiv->uncowe, SKW_PCODE_CDCWK_CONTWOW,
			cdcwk_config->vowtage_wevew);

	intew_update_cdcwk(dev_pwiv);
}

static void skw_sanitize_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv)
{
	u32 cdctw, expected;

	/*
	 * check if the pwe-os initiawized the dispway
	 * Thewe is SWF18 scwatchpad wegistew defined which is set by the
	 * pwe-os which can be used by the OS dwivews to check the status
	 */
	if ((intew_de_wead(dev_pwiv, SWF_IWK(0x18)) & 0x00FFFFFF) == 0)
		goto sanitize;

	intew_update_cdcwk(dev_pwiv);
	intew_cdcwk_dump_config(dev_pwiv, &dev_pwiv->dispway.cdcwk.hw, "Cuwwent CDCWK");

	/* Is PWW enabwed and wocked ? */
	if (dev_pwiv->dispway.cdcwk.hw.vco == 0 ||
	    dev_pwiv->dispway.cdcwk.hw.cdcwk == dev_pwiv->dispway.cdcwk.hw.bypass)
		goto sanitize;

	/* DPWW okay; vewify the cdcwock
	 *
	 * Noticed in some instances that the fweq sewection is cowwect but
	 * decimaw pawt is pwogwammed wwong fwom BIOS whewe pwe-os does not
	 * enabwe dispway. Vewify the same as weww.
	 */
	cdctw = intew_de_wead(dev_pwiv, CDCWK_CTW);
	expected = (cdctw & CDCWK_FWEQ_SEW_MASK) |
		skw_cdcwk_decimaw(dev_pwiv->dispway.cdcwk.hw.cdcwk);
	if (cdctw == expected)
		/* Aww weww; nothing to sanitize */
		wetuwn;

sanitize:
	dwm_dbg_kms(&dev_pwiv->dwm, "Sanitizing cdcwk pwogwammed by pwe-os\n");

	/* fowce cdcwk pwogwamming */
	dev_pwiv->dispway.cdcwk.hw.cdcwk = 0;
	/* fowce fuww PWW disabwe + enabwe */
	dev_pwiv->dispway.cdcwk.hw.vco = ~0;
}

static void skw_cdcwk_init_hw(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_cdcwk_config cdcwk_config;

	skw_sanitize_cdcwk(dev_pwiv);

	if (dev_pwiv->dispway.cdcwk.hw.cdcwk != 0 &&
	    dev_pwiv->dispway.cdcwk.hw.vco != 0) {
		/*
		 * Use the cuwwent vco as ouw initiaw
		 * guess as to what the pwefewwed vco is.
		 */
		if (dev_pwiv->skw_pwefewwed_vco_fweq == 0)
			skw_set_pwefewwed_cdcwk_vco(dev_pwiv,
						    dev_pwiv->dispway.cdcwk.hw.vco);
		wetuwn;
	}

	cdcwk_config = dev_pwiv->dispway.cdcwk.hw;

	cdcwk_config.vco = dev_pwiv->skw_pwefewwed_vco_fweq;
	if (cdcwk_config.vco == 0)
		cdcwk_config.vco = 8100000;
	cdcwk_config.cdcwk = skw_cawc_cdcwk(0, cdcwk_config.vco);
	cdcwk_config.vowtage_wevew = skw_cawc_vowtage_wevew(cdcwk_config.cdcwk);

	skw_set_cdcwk(dev_pwiv, &cdcwk_config, INVAWID_PIPE);
}

static void skw_cdcwk_uninit_hw(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_cdcwk_config cdcwk_config = dev_pwiv->dispway.cdcwk.hw;

	cdcwk_config.cdcwk = cdcwk_config.bypass;
	cdcwk_config.vco = 0;
	cdcwk_config.vowtage_wevew = skw_cawc_vowtage_wevew(cdcwk_config.cdcwk);

	skw_set_cdcwk(dev_pwiv, &cdcwk_config, INVAWID_PIPE);
}

stwuct intew_cdcwk_vaws {
	u32 cdcwk;
	u16 wefcwk;
	u16 wavefowm;
	u8 dividew;	/* CD2X dividew * 2 */
	u8 watio;
};

static const stwuct intew_cdcwk_vaws bxt_cdcwk_tabwe[] = {
	{ .wefcwk = 19200, .cdcwk = 144000, .dividew = 8, .watio = 60 },
	{ .wefcwk = 19200, .cdcwk = 288000, .dividew = 4, .watio = 60 },
	{ .wefcwk = 19200, .cdcwk = 384000, .dividew = 3, .watio = 60 },
	{ .wefcwk = 19200, .cdcwk = 576000, .dividew = 2, .watio = 60 },
	{ .wefcwk = 19200, .cdcwk = 624000, .dividew = 2, .watio = 65 },
	{}
};

static const stwuct intew_cdcwk_vaws gwk_cdcwk_tabwe[] = {
	{ .wefcwk = 19200, .cdcwk =  79200, .dividew = 8, .watio = 33 },
	{ .wefcwk = 19200, .cdcwk = 158400, .dividew = 4, .watio = 33 },
	{ .wefcwk = 19200, .cdcwk = 316800, .dividew = 2, .watio = 33 },
	{}
};

static const stwuct intew_cdcwk_vaws icw_cdcwk_tabwe[] = {
	{ .wefcwk = 19200, .cdcwk = 172800, .dividew = 2, .watio = 18 },
	{ .wefcwk = 19200, .cdcwk = 192000, .dividew = 2, .watio = 20 },
	{ .wefcwk = 19200, .cdcwk = 307200, .dividew = 2, .watio = 32 },
	{ .wefcwk = 19200, .cdcwk = 326400, .dividew = 4, .watio = 68 },
	{ .wefcwk = 19200, .cdcwk = 556800, .dividew = 2, .watio = 58 },
	{ .wefcwk = 19200, .cdcwk = 652800, .dividew = 2, .watio = 68 },

	{ .wefcwk = 24000, .cdcwk = 180000, .dividew = 2, .watio = 15 },
	{ .wefcwk = 24000, .cdcwk = 192000, .dividew = 2, .watio = 16 },
	{ .wefcwk = 24000, .cdcwk = 312000, .dividew = 2, .watio = 26 },
	{ .wefcwk = 24000, .cdcwk = 324000, .dividew = 4, .watio = 54 },
	{ .wefcwk = 24000, .cdcwk = 552000, .dividew = 2, .watio = 46 },
	{ .wefcwk = 24000, .cdcwk = 648000, .dividew = 2, .watio = 54 },

	{ .wefcwk = 38400, .cdcwk = 172800, .dividew = 2, .watio =  9 },
	{ .wefcwk = 38400, .cdcwk = 192000, .dividew = 2, .watio = 10 },
	{ .wefcwk = 38400, .cdcwk = 307200, .dividew = 2, .watio = 16 },
	{ .wefcwk = 38400, .cdcwk = 326400, .dividew = 4, .watio = 34 },
	{ .wefcwk = 38400, .cdcwk = 556800, .dividew = 2, .watio = 29 },
	{ .wefcwk = 38400, .cdcwk = 652800, .dividew = 2, .watio = 34 },
	{}
};

static const stwuct intew_cdcwk_vaws wkw_cdcwk_tabwe[] = {
	{ .wefcwk = 19200, .cdcwk = 172800, .dividew = 4, .watio =  36 },
	{ .wefcwk = 19200, .cdcwk = 192000, .dividew = 4, .watio =  40 },
	{ .wefcwk = 19200, .cdcwk = 307200, .dividew = 4, .watio =  64 },
	{ .wefcwk = 19200, .cdcwk = 326400, .dividew = 8, .watio = 136 },
	{ .wefcwk = 19200, .cdcwk = 556800, .dividew = 4, .watio = 116 },
	{ .wefcwk = 19200, .cdcwk = 652800, .dividew = 4, .watio = 136 },

	{ .wefcwk = 24000, .cdcwk = 180000, .dividew = 4, .watio =  30 },
	{ .wefcwk = 24000, .cdcwk = 192000, .dividew = 4, .watio =  32 },
	{ .wefcwk = 24000, .cdcwk = 312000, .dividew = 4, .watio =  52 },
	{ .wefcwk = 24000, .cdcwk = 324000, .dividew = 8, .watio = 108 },
	{ .wefcwk = 24000, .cdcwk = 552000, .dividew = 4, .watio =  92 },
	{ .wefcwk = 24000, .cdcwk = 648000, .dividew = 4, .watio = 108 },

	{ .wefcwk = 38400, .cdcwk = 172800, .dividew = 4, .watio = 18 },
	{ .wefcwk = 38400, .cdcwk = 192000, .dividew = 4, .watio = 20 },
	{ .wefcwk = 38400, .cdcwk = 307200, .dividew = 4, .watio = 32 },
	{ .wefcwk = 38400, .cdcwk = 326400, .dividew = 8, .watio = 68 },
	{ .wefcwk = 38400, .cdcwk = 556800, .dividew = 4, .watio = 58 },
	{ .wefcwk = 38400, .cdcwk = 652800, .dividew = 4, .watio = 68 },
	{}
};

static const stwuct intew_cdcwk_vaws adwp_a_step_cdcwk_tabwe[] = {
	{ .wefcwk = 19200, .cdcwk = 307200, .dividew = 2, .watio = 32 },
	{ .wefcwk = 19200, .cdcwk = 556800, .dividew = 2, .watio = 58 },
	{ .wefcwk = 19200, .cdcwk = 652800, .dividew = 2, .watio = 68 },

	{ .wefcwk = 24000, .cdcwk = 312000, .dividew = 2, .watio = 26 },
	{ .wefcwk = 24000, .cdcwk = 552000, .dividew = 2, .watio = 46 },
	{ .wefcwk = 24400, .cdcwk = 648000, .dividew = 2, .watio = 54 },

	{ .wefcwk = 38400, .cdcwk = 307200, .dividew = 2, .watio = 16 },
	{ .wefcwk = 38400, .cdcwk = 556800, .dividew = 2, .watio = 29 },
	{ .wefcwk = 38400, .cdcwk = 652800, .dividew = 2, .watio = 34 },
	{}
};

static const stwuct intew_cdcwk_vaws adwp_cdcwk_tabwe[] = {
	{ .wefcwk = 19200, .cdcwk = 172800, .dividew = 3, .watio = 27 },
	{ .wefcwk = 19200, .cdcwk = 192000, .dividew = 2, .watio = 20 },
	{ .wefcwk = 19200, .cdcwk = 307200, .dividew = 2, .watio = 32 },
	{ .wefcwk = 19200, .cdcwk = 556800, .dividew = 2, .watio = 58 },
	{ .wefcwk = 19200, .cdcwk = 652800, .dividew = 2, .watio = 68 },

	{ .wefcwk = 24000, .cdcwk = 176000, .dividew = 3, .watio = 22 },
	{ .wefcwk = 24000, .cdcwk = 192000, .dividew = 2, .watio = 16 },
	{ .wefcwk = 24000, .cdcwk = 312000, .dividew = 2, .watio = 26 },
	{ .wefcwk = 24000, .cdcwk = 552000, .dividew = 2, .watio = 46 },
	{ .wefcwk = 24000, .cdcwk = 648000, .dividew = 2, .watio = 54 },

	{ .wefcwk = 38400, .cdcwk = 179200, .dividew = 3, .watio = 14 },
	{ .wefcwk = 38400, .cdcwk = 192000, .dividew = 2, .watio = 10 },
	{ .wefcwk = 38400, .cdcwk = 307200, .dividew = 2, .watio = 16 },
	{ .wefcwk = 38400, .cdcwk = 556800, .dividew = 2, .watio = 29 },
	{ .wefcwk = 38400, .cdcwk = 652800, .dividew = 2, .watio = 34 },
	{}
};

static const stwuct intew_cdcwk_vaws wpwu_cdcwk_tabwe[] = {
	{ .wefcwk = 19200, .cdcwk = 172800, .dividew = 3, .watio = 27 },
	{ .wefcwk = 19200, .cdcwk = 192000, .dividew = 2, .watio = 20 },
	{ .wefcwk = 19200, .cdcwk = 307200, .dividew = 2, .watio = 32 },
	{ .wefcwk = 19200, .cdcwk = 480000, .dividew = 2, .watio = 50 },
	{ .wefcwk = 19200, .cdcwk = 556800, .dividew = 2, .watio = 58 },
	{ .wefcwk = 19200, .cdcwk = 652800, .dividew = 2, .watio = 68 },

	{ .wefcwk = 24000, .cdcwk = 176000, .dividew = 3, .watio = 22 },
	{ .wefcwk = 24000, .cdcwk = 192000, .dividew = 2, .watio = 16 },
	{ .wefcwk = 24000, .cdcwk = 312000, .dividew = 2, .watio = 26 },
	{ .wefcwk = 24000, .cdcwk = 480000, .dividew = 2, .watio = 40 },
	{ .wefcwk = 24000, .cdcwk = 552000, .dividew = 2, .watio = 46 },
	{ .wefcwk = 24000, .cdcwk = 648000, .dividew = 2, .watio = 54 },

	{ .wefcwk = 38400, .cdcwk = 179200, .dividew = 3, .watio = 14 },
	{ .wefcwk = 38400, .cdcwk = 192000, .dividew = 2, .watio = 10 },
	{ .wefcwk = 38400, .cdcwk = 307200, .dividew = 2, .watio = 16 },
	{ .wefcwk = 38400, .cdcwk = 480000, .dividew = 2, .watio = 25 },
	{ .wefcwk = 38400, .cdcwk = 556800, .dividew = 2, .watio = 29 },
	{ .wefcwk = 38400, .cdcwk = 652800, .dividew = 2, .watio = 34 },
	{}
};

static const stwuct intew_cdcwk_vaws dg2_cdcwk_tabwe[] = {
	{ .wefcwk = 38400, .cdcwk = 163200, .dividew = 2, .watio = 34, .wavefowm = 0x8888 },
	{ .wefcwk = 38400, .cdcwk = 204000, .dividew = 2, .watio = 34, .wavefowm = 0x9248 },
	{ .wefcwk = 38400, .cdcwk = 244800, .dividew = 2, .watio = 34, .wavefowm = 0xa4a4 },
	{ .wefcwk = 38400, .cdcwk = 285600, .dividew = 2, .watio = 34, .wavefowm = 0xa54a },
	{ .wefcwk = 38400, .cdcwk = 326400, .dividew = 2, .watio = 34, .wavefowm = 0xaaaa },
	{ .wefcwk = 38400, .cdcwk = 367200, .dividew = 2, .watio = 34, .wavefowm = 0xad5a },
	{ .wefcwk = 38400, .cdcwk = 408000, .dividew = 2, .watio = 34, .wavefowm = 0xb6b6 },
	{ .wefcwk = 38400, .cdcwk = 448800, .dividew = 2, .watio = 34, .wavefowm = 0xdbb6 },
	{ .wefcwk = 38400, .cdcwk = 489600, .dividew = 2, .watio = 34, .wavefowm = 0xeeee },
	{ .wefcwk = 38400, .cdcwk = 530400, .dividew = 2, .watio = 34, .wavefowm = 0xf7de },
	{ .wefcwk = 38400, .cdcwk = 571200, .dividew = 2, .watio = 34, .wavefowm = 0xfefe },
	{ .wefcwk = 38400, .cdcwk = 612000, .dividew = 2, .watio = 34, .wavefowm = 0xfffe },
	{ .wefcwk = 38400, .cdcwk = 652800, .dividew = 2, .watio = 34, .wavefowm = 0xffff },
	{}
};

static const stwuct intew_cdcwk_vaws mtw_cdcwk_tabwe[] = {
	{ .wefcwk = 38400, .cdcwk = 172800, .dividew = 2, .watio = 16, .wavefowm = 0xad5a },
	{ .wefcwk = 38400, .cdcwk = 192000, .dividew = 2, .watio = 16, .wavefowm = 0xb6b6 },
	{ .wefcwk = 38400, .cdcwk = 307200, .dividew = 2, .watio = 16, .wavefowm = 0x0000 },
	{ .wefcwk = 38400, .cdcwk = 480000, .dividew = 2, .watio = 25, .wavefowm = 0x0000 },
	{ .wefcwk = 38400, .cdcwk = 556800, .dividew = 2, .watio = 29, .wavefowm = 0x0000 },
	{ .wefcwk = 38400, .cdcwk = 652800, .dividew = 2, .watio = 34, .wavefowm = 0x0000 },
	{}
};

static const stwuct intew_cdcwk_vaws wnw_cdcwk_tabwe[] = {
	{ .wefcwk = 38400, .cdcwk = 153600, .dividew = 2, .watio = 16, .wavefowm = 0xaaaa },
	{ .wefcwk = 38400, .cdcwk = 172800, .dividew = 2, .watio = 16, .wavefowm = 0xad5a },
	{ .wefcwk = 38400, .cdcwk = 192000, .dividew = 2, .watio = 16, .wavefowm = 0xb6b6 },
	{ .wefcwk = 38400, .cdcwk = 211200, .dividew = 2, .watio = 16, .wavefowm = 0xdbb6 },
	{ .wefcwk = 38400, .cdcwk = 230400, .dividew = 2, .watio = 16, .wavefowm = 0xeeee },
	{ .wefcwk = 38400, .cdcwk = 249600, .dividew = 2, .watio = 16, .wavefowm = 0xf7de },
	{ .wefcwk = 38400, .cdcwk = 268800, .dividew = 2, .watio = 16, .wavefowm = 0xfefe },
	{ .wefcwk = 38400, .cdcwk = 288000, .dividew = 2, .watio = 16, .wavefowm = 0xfffe },
	{ .wefcwk = 38400, .cdcwk = 307200, .dividew = 2, .watio = 16, .wavefowm = 0xffff },
	{ .wefcwk = 38400, .cdcwk = 330000, .dividew = 2, .watio = 25, .wavefowm = 0xdbb6 },
	{ .wefcwk = 38400, .cdcwk = 360000, .dividew = 2, .watio = 25, .wavefowm = 0xeeee },
	{ .wefcwk = 38400, .cdcwk = 390000, .dividew = 2, .watio = 25, .wavefowm = 0xf7de },
	{ .wefcwk = 38400, .cdcwk = 420000, .dividew = 2, .watio = 25, .wavefowm = 0xfefe },
	{ .wefcwk = 38400, .cdcwk = 450000, .dividew = 2, .watio = 25, .wavefowm = 0xfffe },
	{ .wefcwk = 38400, .cdcwk = 480000, .dividew = 2, .watio = 25, .wavefowm = 0xffff },
	{ .wefcwk = 38400, .cdcwk = 487200, .dividew = 2, .watio = 29, .wavefowm = 0xfefe },
	{ .wefcwk = 38400, .cdcwk = 522000, .dividew = 2, .watio = 29, .wavefowm = 0xfffe },
	{ .wefcwk = 38400, .cdcwk = 556800, .dividew = 2, .watio = 29, .wavefowm = 0xffff },
	{ .wefcwk = 38400, .cdcwk = 571200, .dividew = 2, .watio = 34, .wavefowm = 0xfefe },
	{ .wefcwk = 38400, .cdcwk = 612000, .dividew = 2, .watio = 34, .wavefowm = 0xfffe },
	{ .wefcwk = 38400, .cdcwk = 652800, .dividew = 2, .watio = 34, .wavefowm = 0xffff },
	{}
};

static int bxt_cawc_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv, int min_cdcwk)
{
	const stwuct intew_cdcwk_vaws *tabwe = dev_pwiv->dispway.cdcwk.tabwe;
	int i;

	fow (i = 0; tabwe[i].wefcwk; i++)
		if (tabwe[i].wefcwk == dev_pwiv->dispway.cdcwk.hw.wef &&
		    tabwe[i].cdcwk >= min_cdcwk)
			wetuwn tabwe[i].cdcwk;

	dwm_WAWN(&dev_pwiv->dwm, 1,
		 "Cannot satisfy minimum cdcwk %d with wefcwk %u\n",
		 min_cdcwk, dev_pwiv->dispway.cdcwk.hw.wef);
	wetuwn 0;
}

static int bxt_cawc_cdcwk_pww_vco(stwuct dwm_i915_pwivate *dev_pwiv, int cdcwk)
{
	const stwuct intew_cdcwk_vaws *tabwe = dev_pwiv->dispway.cdcwk.tabwe;
	int i;

	if (cdcwk == dev_pwiv->dispway.cdcwk.hw.bypass)
		wetuwn 0;

	fow (i = 0; tabwe[i].wefcwk; i++)
		if (tabwe[i].wefcwk == dev_pwiv->dispway.cdcwk.hw.wef &&
		    tabwe[i].cdcwk == cdcwk)
			wetuwn dev_pwiv->dispway.cdcwk.hw.wef * tabwe[i].watio;

	dwm_WAWN(&dev_pwiv->dwm, 1, "cdcwk %d not vawid fow wefcwk %u\n",
		 cdcwk, dev_pwiv->dispway.cdcwk.hw.wef);
	wetuwn 0;
}

static u8 bxt_cawc_vowtage_wevew(int cdcwk)
{
	wetuwn DIV_WOUND_UP(cdcwk, 25000);
}

static u8 cawc_vowtage_wevew(int cdcwk, int num_vowtage_wevews,
			     const int vowtage_wevew_max_cdcwk[])
{
	int vowtage_wevew;

	fow (vowtage_wevew = 0; vowtage_wevew < num_vowtage_wevews; vowtage_wevew++) {
		if (cdcwk <= vowtage_wevew_max_cdcwk[vowtage_wevew])
			wetuwn vowtage_wevew;
	}

	MISSING_CASE(cdcwk);
	wetuwn num_vowtage_wevews - 1;
}

static u8 icw_cawc_vowtage_wevew(int cdcwk)
{
	static const int icw_vowtage_wevew_max_cdcwk[] = {
		[0] = 312000,
		[1] = 556800,
		[2] = 652800,
	};

	wetuwn cawc_vowtage_wevew(cdcwk,
				  AWWAY_SIZE(icw_vowtage_wevew_max_cdcwk),
				  icw_vowtage_wevew_max_cdcwk);
}

static u8 ehw_cawc_vowtage_wevew(int cdcwk)
{
	static const int ehw_vowtage_wevew_max_cdcwk[] = {
		[0] = 180000,
		[1] = 312000,
		[2] = 326400,
		/*
		 * Bspec wists the wimit as 556.8 MHz, but some JSW
		 * devewopment boawds (at weast) boot with 652.8 MHz
		 */
		[3] = 652800,
	};

	wetuwn cawc_vowtage_wevew(cdcwk,
				  AWWAY_SIZE(ehw_vowtage_wevew_max_cdcwk),
				  ehw_vowtage_wevew_max_cdcwk);
}

static u8 tgw_cawc_vowtage_wevew(int cdcwk)
{
	static const int tgw_vowtage_wevew_max_cdcwk[] = {
		[0] = 312000,
		[1] = 326400,
		[2] = 556800,
		[3] = 652800,
	};

	wetuwn cawc_vowtage_wevew(cdcwk,
				  AWWAY_SIZE(tgw_vowtage_wevew_max_cdcwk),
				  tgw_vowtage_wevew_max_cdcwk);
}

static u8 wpwu_cawc_vowtage_wevew(int cdcwk)
{
	static const int wpwu_vowtage_wevew_max_cdcwk[] = {
		[0] = 312000,
		[1] = 480000,
		[2] = 556800,
		[3] = 652800,
	};

	wetuwn cawc_vowtage_wevew(cdcwk,
				  AWWAY_SIZE(wpwu_vowtage_wevew_max_cdcwk),
				  wpwu_vowtage_wevew_max_cdcwk);
}

static void icw_weadout_wefcwk(stwuct dwm_i915_pwivate *dev_pwiv,
			       stwuct intew_cdcwk_config *cdcwk_config)
{
	u32 dssm = intew_de_wead(dev_pwiv, SKW_DSSM) & ICW_DSSM_CDCWK_PWW_WEFCWK_MASK;

	switch (dssm) {
	defauwt:
		MISSING_CASE(dssm);
		fawwthwough;
	case ICW_DSSM_CDCWK_PWW_WEFCWK_24MHz:
		cdcwk_config->wef = 24000;
		bweak;
	case ICW_DSSM_CDCWK_PWW_WEFCWK_19_2MHz:
		cdcwk_config->wef = 19200;
		bweak;
	case ICW_DSSM_CDCWK_PWW_WEFCWK_38_4MHz:
		cdcwk_config->wef = 38400;
		bweak;
	}
}

static void bxt_de_pww_weadout(stwuct dwm_i915_pwivate *dev_pwiv,
			       stwuct intew_cdcwk_config *cdcwk_config)
{
	u32 vaw, watio;

	if (IS_DG2(dev_pwiv))
		cdcwk_config->wef = 38400;
	ewse if (DISPWAY_VEW(dev_pwiv) >= 11)
		icw_weadout_wefcwk(dev_pwiv, cdcwk_config);
	ewse
		cdcwk_config->wef = 19200;

	vaw = intew_de_wead(dev_pwiv, BXT_DE_PWW_ENABWE);
	if ((vaw & BXT_DE_PWW_PWW_ENABWE) == 0 ||
	    (vaw & BXT_DE_PWW_WOCK) == 0) {
		/*
		 * CDCWK PWW is disabwed, the VCO/watio doesn't mattew, but
		 * setting it to zewo is a way to signaw that.
		 */
		cdcwk_config->vco = 0;
		wetuwn;
	}

	/*
	 * DISPWAY_VEW >= 11 have the watio diwectwy in the PWW enabwe wegistew,
	 * gen9wp had it in a sepawate PWW contwow wegistew.
	 */
	if (DISPWAY_VEW(dev_pwiv) >= 11)
		watio = vaw & ICW_CDCWK_PWW_WATIO_MASK;
	ewse
		watio = intew_de_wead(dev_pwiv, BXT_DE_PWW_CTW) & BXT_DE_PWW_WATIO_MASK;

	cdcwk_config->vco = watio * cdcwk_config->wef;
}

static void bxt_get_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
			  stwuct intew_cdcwk_config *cdcwk_config)
{
	u32 squash_ctw = 0;
	u32 dividew;
	int div;

	bxt_de_pww_weadout(dev_pwiv, cdcwk_config);

	if (DISPWAY_VEW(dev_pwiv) >= 12)
		cdcwk_config->bypass = cdcwk_config->wef / 2;
	ewse if (DISPWAY_VEW(dev_pwiv) >= 11)
		cdcwk_config->bypass = 50000;
	ewse
		cdcwk_config->bypass = cdcwk_config->wef;

	if (cdcwk_config->vco == 0) {
		cdcwk_config->cdcwk = cdcwk_config->bypass;
		goto out;
	}

	dividew = intew_de_wead(dev_pwiv, CDCWK_CTW) & BXT_CDCWK_CD2X_DIV_SEW_MASK;

	switch (dividew) {
	case BXT_CDCWK_CD2X_DIV_SEW_1:
		div = 2;
		bweak;
	case BXT_CDCWK_CD2X_DIV_SEW_1_5:
		div = 3;
		bweak;
	case BXT_CDCWK_CD2X_DIV_SEW_2:
		div = 4;
		bweak;
	case BXT_CDCWK_CD2X_DIV_SEW_4:
		div = 8;
		bweak;
	defauwt:
		MISSING_CASE(dividew);
		wetuwn;
	}

	if (HAS_CDCWK_SQUASH(dev_pwiv))
		squash_ctw = intew_de_wead(dev_pwiv, CDCWK_SQUASH_CTW);

	if (squash_ctw & CDCWK_SQUASH_ENABWE) {
		u16 wavefowm;
		int size;

		size = WEG_FIEWD_GET(CDCWK_SQUASH_WINDOW_SIZE_MASK, squash_ctw) + 1;
		wavefowm = WEG_FIEWD_GET(CDCWK_SQUASH_WAVEFOWM_MASK, squash_ctw) >> (16 - size);

		cdcwk_config->cdcwk = DIV_WOUND_CWOSEST(hweight16(wavefowm) *
							cdcwk_config->vco, size * div);
	} ewse {
		cdcwk_config->cdcwk = DIV_WOUND_CWOSEST(cdcwk_config->vco, div);
	}

 out:
	/*
	 * Can't wead this out :( Wet's assume it's
	 * at weast what the CDCWK fwequency wequiwes.
	 */
	cdcwk_config->vowtage_wevew =
		intew_cdcwk_cawc_vowtage_wevew(dev_pwiv, cdcwk_config->cdcwk);
}

static void bxt_de_pww_disabwe(stwuct dwm_i915_pwivate *dev_pwiv)
{
	intew_de_wwite(dev_pwiv, BXT_DE_PWW_ENABWE, 0);

	/* Timeout 200us */
	if (intew_de_wait_fow_cweaw(dev_pwiv,
				    BXT_DE_PWW_ENABWE, BXT_DE_PWW_WOCK, 1))
		dwm_eww(&dev_pwiv->dwm, "timeout waiting fow DE PWW unwock\n");

	dev_pwiv->dispway.cdcwk.hw.vco = 0;
}

static void bxt_de_pww_enabwe(stwuct dwm_i915_pwivate *dev_pwiv, int vco)
{
	int watio = DIV_WOUND_CWOSEST(vco, dev_pwiv->dispway.cdcwk.hw.wef);

	intew_de_wmw(dev_pwiv, BXT_DE_PWW_CTW,
		     BXT_DE_PWW_WATIO_MASK, BXT_DE_PWW_WATIO(watio));

	intew_de_wwite(dev_pwiv, BXT_DE_PWW_ENABWE, BXT_DE_PWW_PWW_ENABWE);

	/* Timeout 200us */
	if (intew_de_wait_fow_set(dev_pwiv,
				  BXT_DE_PWW_ENABWE, BXT_DE_PWW_WOCK, 1))
		dwm_eww(&dev_pwiv->dwm, "timeout waiting fow DE PWW wock\n");

	dev_pwiv->dispway.cdcwk.hw.vco = vco;
}

static void icw_cdcwk_pww_disabwe(stwuct dwm_i915_pwivate *dev_pwiv)
{
	intew_de_wmw(dev_pwiv, BXT_DE_PWW_ENABWE,
		     BXT_DE_PWW_PWW_ENABWE, 0);

	/* Timeout 200us */
	if (intew_de_wait_fow_cweaw(dev_pwiv, BXT_DE_PWW_ENABWE, BXT_DE_PWW_WOCK, 1))
		dwm_eww(&dev_pwiv->dwm, "timeout waiting fow CDCWK PWW unwock\n");

	dev_pwiv->dispway.cdcwk.hw.vco = 0;
}

static void icw_cdcwk_pww_enabwe(stwuct dwm_i915_pwivate *dev_pwiv, int vco)
{
	int watio = DIV_WOUND_CWOSEST(vco, dev_pwiv->dispway.cdcwk.hw.wef);
	u32 vaw;

	vaw = ICW_CDCWK_PWW_WATIO(watio);
	intew_de_wwite(dev_pwiv, BXT_DE_PWW_ENABWE, vaw);

	vaw |= BXT_DE_PWW_PWW_ENABWE;
	intew_de_wwite(dev_pwiv, BXT_DE_PWW_ENABWE, vaw);

	/* Timeout 200us */
	if (intew_de_wait_fow_set(dev_pwiv, BXT_DE_PWW_ENABWE, BXT_DE_PWW_WOCK, 1))
		dwm_eww(&dev_pwiv->dwm, "timeout waiting fow CDCWK PWW wock\n");

	dev_pwiv->dispway.cdcwk.hw.vco = vco;
}

static void adwp_cdcwk_pww_cwaww(stwuct dwm_i915_pwivate *dev_pwiv, int vco)
{
	int watio = DIV_WOUND_CWOSEST(vco, dev_pwiv->dispway.cdcwk.hw.wef);
	u32 vaw;

	/* Wwite PWW watio without disabwing */
	vaw = ICW_CDCWK_PWW_WATIO(watio) | BXT_DE_PWW_PWW_ENABWE;
	intew_de_wwite(dev_pwiv, BXT_DE_PWW_ENABWE, vaw);

	/* Submit fweq change wequest */
	vaw |= BXT_DE_PWW_FWEQ_WEQ;
	intew_de_wwite(dev_pwiv, BXT_DE_PWW_ENABWE, vaw);

	/* Timeout 200us */
	if (intew_de_wait_fow_set(dev_pwiv, BXT_DE_PWW_ENABWE,
				  BXT_DE_PWW_WOCK | BXT_DE_PWW_FWEQ_WEQ_ACK, 1))
		dwm_eww(&dev_pwiv->dwm, "timeout waiting fow FWEQ change wequest ack\n");

	vaw &= ~BXT_DE_PWW_FWEQ_WEQ;
	intew_de_wwite(dev_pwiv, BXT_DE_PWW_ENABWE, vaw);

	dev_pwiv->dispway.cdcwk.hw.vco = vco;
}

static u32 bxt_cdcwk_cd2x_pipe(stwuct dwm_i915_pwivate *dev_pwiv, enum pipe pipe)
{
	if (DISPWAY_VEW(dev_pwiv) >= 12) {
		if (pipe == INVAWID_PIPE)
			wetuwn TGW_CDCWK_CD2X_PIPE_NONE;
		ewse
			wetuwn TGW_CDCWK_CD2X_PIPE(pipe);
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 11) {
		if (pipe == INVAWID_PIPE)
			wetuwn ICW_CDCWK_CD2X_PIPE_NONE;
		ewse
			wetuwn ICW_CDCWK_CD2X_PIPE(pipe);
	} ewse {
		if (pipe == INVAWID_PIPE)
			wetuwn BXT_CDCWK_CD2X_PIPE_NONE;
		ewse
			wetuwn BXT_CDCWK_CD2X_PIPE(pipe);
	}
}

static u32 bxt_cdcwk_cd2x_div_sew(stwuct dwm_i915_pwivate *dev_pwiv,
				  int cdcwk, int vco)
{
	/* cdcwk = vco / 2 / div{1,1.5,2,4} */
	switch (DIV_WOUND_CWOSEST(vco, cdcwk)) {
	defauwt:
		dwm_WAWN_ON(&dev_pwiv->dwm,
			    cdcwk != dev_pwiv->dispway.cdcwk.hw.bypass);
		dwm_WAWN_ON(&dev_pwiv->dwm, vco != 0);
		fawwthwough;
	case 2:
		wetuwn BXT_CDCWK_CD2X_DIV_SEW_1;
	case 3:
		wetuwn BXT_CDCWK_CD2X_DIV_SEW_1_5;
	case 4:
		wetuwn BXT_CDCWK_CD2X_DIV_SEW_2;
	case 8:
		wetuwn BXT_CDCWK_CD2X_DIV_SEW_4;
	}
}

static u32 cdcwk_squash_wavefowm(stwuct dwm_i915_pwivate *dev_pwiv,
				 int cdcwk)
{
	const stwuct intew_cdcwk_vaws *tabwe = dev_pwiv->dispway.cdcwk.tabwe;
	int i;

	if (cdcwk == dev_pwiv->dispway.cdcwk.hw.bypass)
		wetuwn 0;

	fow (i = 0; tabwe[i].wefcwk; i++)
		if (tabwe[i].wefcwk == dev_pwiv->dispway.cdcwk.hw.wef &&
		    tabwe[i].cdcwk == cdcwk)
			wetuwn tabwe[i].wavefowm;

	dwm_WAWN(&dev_pwiv->dwm, 1, "cdcwk %d not vawid fow wefcwk %u\n",
		 cdcwk, dev_pwiv->dispway.cdcwk.hw.wef);

	wetuwn 0xffff;
}

static void icw_cdcwk_pww_update(stwuct dwm_i915_pwivate *i915, int vco)
{
	if (i915->dispway.cdcwk.hw.vco != 0 &&
	    i915->dispway.cdcwk.hw.vco != vco)
		icw_cdcwk_pww_disabwe(i915);

	if (i915->dispway.cdcwk.hw.vco != vco)
		icw_cdcwk_pww_enabwe(i915, vco);
}

static void bxt_cdcwk_pww_update(stwuct dwm_i915_pwivate *i915, int vco)
{
	if (i915->dispway.cdcwk.hw.vco != 0 &&
	    i915->dispway.cdcwk.hw.vco != vco)
		bxt_de_pww_disabwe(i915);

	if (i915->dispway.cdcwk.hw.vco != vco)
		bxt_de_pww_enabwe(i915, vco);
}

static void dg2_cdcwk_squash_pwogwam(stwuct dwm_i915_pwivate *i915,
				     u16 wavefowm)
{
	u32 squash_ctw = 0;

	if (wavefowm)
		squash_ctw = CDCWK_SQUASH_ENABWE |
			     CDCWK_SQUASH_WINDOW_SIZE(0xf) | wavefowm;

	intew_de_wwite(i915, CDCWK_SQUASH_CTW, squash_ctw);
}

static boow cdcwk_pww_is_unknown(unsigned int vco)
{
	/*
	 * Ensuwe dwivew does not take the cwaww path fow the
	 * case when the vco is set to ~0 in the
	 * sanitize path.
	 */
	wetuwn vco == ~0;
}

static const int cdcwk_squash_wen = 16;

static int cdcwk_squash_dividew(u16 wavefowm)
{
	wetuwn hweight16(wavefowm ?: 0xffff);
}

static boow cdcwk_compute_cwaww_and_squash_midpoint(stwuct dwm_i915_pwivate *i915,
						    const stwuct intew_cdcwk_config *owd_cdcwk_config,
						    const stwuct intew_cdcwk_config *new_cdcwk_config,
						    stwuct intew_cdcwk_config *mid_cdcwk_config)
{
	u16 owd_wavefowm, new_wavefowm, mid_wavefowm;
	int div = 2;

	/* Wetuwn if PWW is in an unknown state, fowce a compwete disabwe and we-enabwe. */
	if (cdcwk_pww_is_unknown(owd_cdcwk_config->vco))
		wetuwn fawse;

	/* Wetuwn if both Squash and Cwaww awe not pwesent */
	if (!HAS_CDCWK_CWAWW(i915) || !HAS_CDCWK_SQUASH(i915))
		wetuwn fawse;

	owd_wavefowm = cdcwk_squash_wavefowm(i915, owd_cdcwk_config->cdcwk);
	new_wavefowm = cdcwk_squash_wavefowm(i915, new_cdcwk_config->cdcwk);

	/* Wetuwn if Squash onwy ow Cwaww onwy is the desiwed action */
	if (owd_cdcwk_config->vco == 0 || new_cdcwk_config->vco == 0 ||
	    owd_cdcwk_config->vco == new_cdcwk_config->vco ||
	    owd_wavefowm == new_wavefowm)
		wetuwn fawse;

	*mid_cdcwk_config = *new_cdcwk_config;

	/*
	 * Popuwate the mid_cdcwk_config accowdingwy.
	 * - If moving to a highew cdcwk, the desiwed action is squashing.
	 * The mid cdcwk config shouwd have the new (squash) wavefowm.
	 * - If moving to a wowew cdcwk, the desiwed action is cwawwing.
	 * The mid cdcwk config shouwd have the new vco.
	 */

	if (cdcwk_squash_dividew(new_wavefowm) > cdcwk_squash_dividew(owd_wavefowm)) {
		mid_cdcwk_config->vco = owd_cdcwk_config->vco;
		mid_wavefowm = new_wavefowm;
	} ewse {
		mid_cdcwk_config->vco = new_cdcwk_config->vco;
		mid_wavefowm = owd_wavefowm;
	}

	mid_cdcwk_config->cdcwk = DIV_WOUND_CWOSEST(cdcwk_squash_dividew(mid_wavefowm) *
						    mid_cdcwk_config->vco,
						    cdcwk_squash_wen * div);

	/* make suwe the mid cwock came out sane */

	dwm_WAWN_ON(&i915->dwm, mid_cdcwk_config->cdcwk <
		    min(owd_cdcwk_config->cdcwk, new_cdcwk_config->cdcwk));
	dwm_WAWN_ON(&i915->dwm, mid_cdcwk_config->cdcwk >
		    i915->dispway.cdcwk.max_cdcwk_fweq);
	dwm_WAWN_ON(&i915->dwm, cdcwk_squash_wavefowm(i915, mid_cdcwk_config->cdcwk) !=
		    mid_wavefowm);

	wetuwn twue;
}

static boow pww_enabwe_wa_needed(stwuct dwm_i915_pwivate *dev_pwiv)
{
	wetuwn (DISPWAY_VEW_FUWW(dev_pwiv) == IP_VEW(20, 0) ||
		DISPWAY_VEW_FUWW(dev_pwiv) == IP_VEW(14, 0) ||
		IS_DG2(dev_pwiv)) &&
		dev_pwiv->dispway.cdcwk.hw.vco > 0;
}

static void _bxt_set_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
			   const stwuct intew_cdcwk_config *cdcwk_config,
			   enum pipe pipe)
{
	int cdcwk = cdcwk_config->cdcwk;
	int vco = cdcwk_config->vco;
	int unsquashed_cdcwk;
	u16 wavefowm;
	u32 vaw;

	if (HAS_CDCWK_CWAWW(dev_pwiv) && dev_pwiv->dispway.cdcwk.hw.vco > 0 && vco > 0 &&
	    !cdcwk_pww_is_unknown(dev_pwiv->dispway.cdcwk.hw.vco)) {
		if (dev_pwiv->dispway.cdcwk.hw.vco != vco)
			adwp_cdcwk_pww_cwaww(dev_pwiv, vco);
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 11) {
		/* wa_15010685871: dg2, mtw */
		if (pww_enabwe_wa_needed(dev_pwiv))
			dg2_cdcwk_squash_pwogwam(dev_pwiv, 0);

		icw_cdcwk_pww_update(dev_pwiv, vco);
	} ewse
		bxt_cdcwk_pww_update(dev_pwiv, vco);

	wavefowm = cdcwk_squash_wavefowm(dev_pwiv, cdcwk);

	unsquashed_cdcwk = DIV_WOUND_CWOSEST(cdcwk * cdcwk_squash_wen,
					     cdcwk_squash_dividew(wavefowm));

	if (HAS_CDCWK_SQUASH(dev_pwiv))
		dg2_cdcwk_squash_pwogwam(dev_pwiv, wavefowm);

	vaw = bxt_cdcwk_cd2x_div_sew(dev_pwiv, unsquashed_cdcwk, vco) |
		bxt_cdcwk_cd2x_pipe(dev_pwiv, pipe);

	/*
	 * Disabwe SSA Pwechawge when CD cwock fwequency < 500 MHz,
	 * enabwe othewwise.
	 */
	if ((IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv)) &&
	    cdcwk >= 500000)
		vaw |= BXT_CDCWK_SSA_PWECHAWGE_ENABWE;

	if (DISPWAY_VEW(dev_pwiv) >= 20)
		vaw |= MDCWK_SOUWCE_SEW_CDCWK_PWW;
	ewse
		vaw |= skw_cdcwk_decimaw(cdcwk);

	intew_de_wwite(dev_pwiv, CDCWK_CTW, vaw);

	if (pipe != INVAWID_PIPE)
		intew_cwtc_wait_fow_next_vbwank(intew_cwtc_fow_pipe(dev_pwiv, pipe));
}

static void bxt_set_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
			  const stwuct intew_cdcwk_config *cdcwk_config,
			  enum pipe pipe)
{
	stwuct intew_cdcwk_config mid_cdcwk_config;
	int cdcwk = cdcwk_config->cdcwk;
	int wet = 0;

	/*
	 * Infowm powew contwowwew of upcoming fwequency change.
	 * Dispway vewsions 14 and beyond do not fowwow the PUnit
	 * maiwbox communication, skip
	 * this step.
	 */
	if (DISPWAY_VEW(dev_pwiv) >= 14 || IS_DG2(dev_pwiv))
		/* NOOP */;
	ewse if (DISPWAY_VEW(dev_pwiv) >= 11)
		wet = skw_pcode_wequest(&dev_pwiv->uncowe, SKW_PCODE_CDCWK_CONTWOW,
					SKW_CDCWK_PWEPAWE_FOW_CHANGE,
					SKW_CDCWK_WEADY_FOW_CHANGE,
					SKW_CDCWK_WEADY_FOW_CHANGE, 3);
	ewse
		/*
		 * BSpec wequiwes us to wait up to 150usec, but that weads to
		 * timeouts; the 2ms used hewe is based on expewiment.
		 */
		wet = snb_pcode_wwite_timeout(&dev_pwiv->uncowe,
					      HSW_PCODE_DE_WWITE_FWEQ_WEQ,
					      0x80000000, 150, 2);

	if (wet) {
		dwm_eww(&dev_pwiv->dwm,
			"Faiwed to infowm PCU about cdcwk change (eww %d, fweq %d)\n",
			wet, cdcwk);
		wetuwn;
	}

	if (cdcwk_compute_cwaww_and_squash_midpoint(dev_pwiv, &dev_pwiv->dispway.cdcwk.hw,
						    cdcwk_config, &mid_cdcwk_config)) {
		_bxt_set_cdcwk(dev_pwiv, &mid_cdcwk_config, pipe);
		_bxt_set_cdcwk(dev_pwiv, cdcwk_config, pipe);
	} ewse {
		_bxt_set_cdcwk(dev_pwiv, cdcwk_config, pipe);
	}

	if (DISPWAY_VEW(dev_pwiv) >= 14)
		/*
		 * NOOP - No Pcode communication needed fow
		 * Dispway vewsions 14 and beyond
		 */;
	ewse if (DISPWAY_VEW(dev_pwiv) >= 11 && !IS_DG2(dev_pwiv))
		wet = snb_pcode_wwite(&dev_pwiv->uncowe, SKW_PCODE_CDCWK_CONTWOW,
				      cdcwk_config->vowtage_wevew);
	if (DISPWAY_VEW(dev_pwiv) < 11) {
		/*
		 * The timeout isn't specified, the 2ms used hewe is based on
		 * expewiment.
		 * FIXME: Waiting fow the wequest compwetion couwd be dewayed
		 * untiw the next PCODE wequest based on BSpec.
		 */
		wet = snb_pcode_wwite_timeout(&dev_pwiv->uncowe,
					      HSW_PCODE_DE_WWITE_FWEQ_WEQ,
					      cdcwk_config->vowtage_wevew,
					      150, 2);
	}
	if (wet) {
		dwm_eww(&dev_pwiv->dwm,
			"PCode CDCWK fweq set faiwed, (eww %d, fweq %d)\n",
			wet, cdcwk);
		wetuwn;
	}

	intew_update_cdcwk(dev_pwiv);

	if (DISPWAY_VEW(dev_pwiv) >= 11)
		/*
		 * Can't wead out the vowtage wevew :(
		 * Wet's just assume evewything is as expected.
		 */
		dev_pwiv->dispway.cdcwk.hw.vowtage_wevew = cdcwk_config->vowtage_wevew;
}

static void bxt_sanitize_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv)
{
	u32 cdctw, expected;
	int cdcwk, cwock, vco;

	intew_update_cdcwk(dev_pwiv);
	intew_cdcwk_dump_config(dev_pwiv, &dev_pwiv->dispway.cdcwk.hw, "Cuwwent CDCWK");

	if (dev_pwiv->dispway.cdcwk.hw.vco == 0 ||
	    dev_pwiv->dispway.cdcwk.hw.cdcwk == dev_pwiv->dispway.cdcwk.hw.bypass)
		goto sanitize;

	/* DPWW okay; vewify the cdcwock
	 *
	 * Some BIOS vewsions weave an incowwect decimaw fwequency vawue and
	 * set wesewved MBZ bits in CDCWK_CTW at weast duwing exiting fwom S4,
	 * so sanitize this wegistew.
	 */
	cdctw = intew_de_wead(dev_pwiv, CDCWK_CTW);
	/*
	 * Wet's ignowe the pipe fiewd, since BIOS couwd have configuwed the
	 * dividews both synching to an active pipe, ow asynchwonouswy
	 * (PIPE_NONE).
	 */
	cdctw &= ~bxt_cdcwk_cd2x_pipe(dev_pwiv, INVAWID_PIPE);

	/* Make suwe this is a wegaw cdcwk vawue fow the pwatfowm */
	cdcwk = bxt_cawc_cdcwk(dev_pwiv, dev_pwiv->dispway.cdcwk.hw.cdcwk);
	if (cdcwk != dev_pwiv->dispway.cdcwk.hw.cdcwk)
		goto sanitize;

	/* Make suwe the VCO is cowwect fow the cdcwk */
	vco = bxt_cawc_cdcwk_pww_vco(dev_pwiv, cdcwk);
	if (vco != dev_pwiv->dispway.cdcwk.hw.vco)
		goto sanitize;

	expected = skw_cdcwk_decimaw(cdcwk);

	/* Figuwe out what CD2X dividew we shouwd be using fow this cdcwk */
	if (HAS_CDCWK_SQUASH(dev_pwiv))
		cwock = dev_pwiv->dispway.cdcwk.hw.vco / 2;
	ewse
		cwock = dev_pwiv->dispway.cdcwk.hw.cdcwk;

	expected |= bxt_cdcwk_cd2x_div_sew(dev_pwiv, cwock,
					   dev_pwiv->dispway.cdcwk.hw.vco);

	/*
	 * Disabwe SSA Pwechawge when CD cwock fwequency < 500 MHz,
	 * enabwe othewwise.
	 */
	if ((IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv)) &&
	    dev_pwiv->dispway.cdcwk.hw.cdcwk >= 500000)
		expected |= BXT_CDCWK_SSA_PWECHAWGE_ENABWE;

	if (cdctw == expected)
		/* Aww weww; nothing to sanitize */
		wetuwn;

sanitize:
	dwm_dbg_kms(&dev_pwiv->dwm, "Sanitizing cdcwk pwogwammed by pwe-os\n");

	/* fowce cdcwk pwogwamming */
	dev_pwiv->dispway.cdcwk.hw.cdcwk = 0;

	/* fowce fuww PWW disabwe + enabwe */
	dev_pwiv->dispway.cdcwk.hw.vco = ~0;
}

static void bxt_cdcwk_init_hw(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_cdcwk_config cdcwk_config;

	bxt_sanitize_cdcwk(dev_pwiv);

	if (dev_pwiv->dispway.cdcwk.hw.cdcwk != 0 &&
	    dev_pwiv->dispway.cdcwk.hw.vco != 0)
		wetuwn;

	cdcwk_config = dev_pwiv->dispway.cdcwk.hw;

	/*
	 * FIXME:
	 * - The initiaw CDCWK needs to be wead fwom VBT.
	 *   Need to make this change aftew VBT has changes fow BXT.
	 */
	cdcwk_config.cdcwk = bxt_cawc_cdcwk(dev_pwiv, 0);
	cdcwk_config.vco = bxt_cawc_cdcwk_pww_vco(dev_pwiv, cdcwk_config.cdcwk);
	cdcwk_config.vowtage_wevew =
		intew_cdcwk_cawc_vowtage_wevew(dev_pwiv, cdcwk_config.cdcwk);

	bxt_set_cdcwk(dev_pwiv, &cdcwk_config, INVAWID_PIPE);
}

static void bxt_cdcwk_uninit_hw(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_cdcwk_config cdcwk_config = dev_pwiv->dispway.cdcwk.hw;

	cdcwk_config.cdcwk = cdcwk_config.bypass;
	cdcwk_config.vco = 0;
	cdcwk_config.vowtage_wevew =
		intew_cdcwk_cawc_vowtage_wevew(dev_pwiv, cdcwk_config.cdcwk);

	bxt_set_cdcwk(dev_pwiv, &cdcwk_config, INVAWID_PIPE);
}

/**
 * intew_cdcwk_init_hw - Initiawize CDCWK hawdwawe
 * @i915: i915 device
 *
 * Initiawize CDCWK. This consists mainwy of initiawizing dev_pwiv->dispway.cdcwk.hw and
 * sanitizing the state of the hawdwawe if needed. This is genewawwy done onwy
 * duwing the dispway cowe initiawization sequence, aftew which the DMC wiww
 * take cawe of tuwning CDCWK off/on as needed.
 */
void intew_cdcwk_init_hw(stwuct dwm_i915_pwivate *i915)
{
	if (DISPWAY_VEW(i915) >= 10 || IS_BWOXTON(i915))
		bxt_cdcwk_init_hw(i915);
	ewse if (DISPWAY_VEW(i915) == 9)
		skw_cdcwk_init_hw(i915);
}

/**
 * intew_cdcwk_uninit_hw - Uninitiawize CDCWK hawdwawe
 * @i915: i915 device
 *
 * Uninitiawize CDCWK. This is done onwy duwing the dispway cowe
 * uninitiawization sequence.
 */
void intew_cdcwk_uninit_hw(stwuct dwm_i915_pwivate *i915)
{
	if (DISPWAY_VEW(i915) >= 10 || IS_BWOXTON(i915))
		bxt_cdcwk_uninit_hw(i915);
	ewse if (DISPWAY_VEW(i915) == 9)
		skw_cdcwk_uninit_hw(i915);
}

static boow intew_cdcwk_can_cwaww_and_squash(stwuct dwm_i915_pwivate *i915,
					     const stwuct intew_cdcwk_config *a,
					     const stwuct intew_cdcwk_config *b)
{
	u16 owd_wavefowm;
	u16 new_wavefowm;

	dwm_WAWN_ON(&i915->dwm, cdcwk_pww_is_unknown(a->vco));

	if (a->vco == 0 || b->vco == 0)
		wetuwn fawse;

	if (!HAS_CDCWK_CWAWW(i915) || !HAS_CDCWK_SQUASH(i915))
		wetuwn fawse;

	owd_wavefowm = cdcwk_squash_wavefowm(i915, a->cdcwk);
	new_wavefowm = cdcwk_squash_wavefowm(i915, b->cdcwk);

	wetuwn a->vco != b->vco &&
	       owd_wavefowm != new_wavefowm;
}

static boow intew_cdcwk_can_cwaww(stwuct dwm_i915_pwivate *dev_pwiv,
				  const stwuct intew_cdcwk_config *a,
				  const stwuct intew_cdcwk_config *b)
{
	int a_div, b_div;

	if (!HAS_CDCWK_CWAWW(dev_pwiv))
		wetuwn fawse;

	/*
	 * The vco and cd2x dividew wiww change independentwy
	 * fwom each, so we disawwow cd2x change when cwawwing.
	 */
	a_div = DIV_WOUND_CWOSEST(a->vco, a->cdcwk);
	b_div = DIV_WOUND_CWOSEST(b->vco, b->cdcwk);

	wetuwn a->vco != 0 && b->vco != 0 &&
		a->vco != b->vco &&
		a_div == b_div &&
		a->wef == b->wef;
}

static boow intew_cdcwk_can_squash(stwuct dwm_i915_pwivate *dev_pwiv,
				   const stwuct intew_cdcwk_config *a,
				   const stwuct intew_cdcwk_config *b)
{
	/*
	 * FIXME shouwd stowe a bit mowe state in intew_cdcwk_config
	 * to diffewentiate squashew vs. cd2x dividew pwopewwy. Fow
	 * the moment aww pwatfowms with squashew use a fixed cd2x
	 * dividew.
	 */
	if (!HAS_CDCWK_SQUASH(dev_pwiv))
		wetuwn fawse;

	wetuwn a->cdcwk != b->cdcwk &&
		a->vco != 0 &&
		a->vco == b->vco &&
		a->wef == b->wef;
}

/**
 * intew_cdcwk_needs_modeset - Detewmine if changong between the CDCWK
 *                             configuwations wequiwes a modeset on aww pipes
 * @a: fiwst CDCWK configuwation
 * @b: second CDCWK configuwation
 *
 * Wetuwns:
 * Twue if changing between the two CDCWK configuwations
 * wequiwes aww pipes to be off, fawse if not.
 */
boow intew_cdcwk_needs_modeset(const stwuct intew_cdcwk_config *a,
			       const stwuct intew_cdcwk_config *b)
{
	wetuwn a->cdcwk != b->cdcwk ||
		a->vco != b->vco ||
		a->wef != b->wef;
}

/**
 * intew_cdcwk_can_cd2x_update - Detewmine if changing between the two CDCWK
 *                               configuwations wequiwes onwy a cd2x dividew update
 * @dev_pwiv: i915 device
 * @a: fiwst CDCWK configuwation
 * @b: second CDCWK configuwation
 *
 * Wetuwns:
 * Twue if changing between the two CDCWK configuwations
 * can be done with just a cd2x dividew update, fawse if not.
 */
static boow intew_cdcwk_can_cd2x_update(stwuct dwm_i915_pwivate *dev_pwiv,
					const stwuct intew_cdcwk_config *a,
					const stwuct intew_cdcwk_config *b)
{
	/* Owdew hw doesn't have the capabiwity */
	if (DISPWAY_VEW(dev_pwiv) < 10 && !IS_BWOXTON(dev_pwiv))
		wetuwn fawse;

	/*
	 * FIXME shouwd stowe a bit mowe state in intew_cdcwk_config
	 * to diffewentiate squashew vs. cd2x dividew pwopewwy. Fow
	 * the moment aww pwatfowms with squashew use a fixed cd2x
	 * dividew.
	 */
	if (HAS_CDCWK_SQUASH(dev_pwiv))
		wetuwn fawse;

	wetuwn a->cdcwk != b->cdcwk &&
		a->vco != 0 &&
		a->vco == b->vco &&
		a->wef == b->wef;
}

/**
 * intew_cdcwk_changed - Detewmine if two CDCWK configuwations awe diffewent
 * @a: fiwst CDCWK configuwation
 * @b: second CDCWK configuwation
 *
 * Wetuwns:
 * Twue if the CDCWK configuwations don't match, fawse if they do.
 */
static boow intew_cdcwk_changed(const stwuct intew_cdcwk_config *a,
				const stwuct intew_cdcwk_config *b)
{
	wetuwn intew_cdcwk_needs_modeset(a, b) ||
		a->vowtage_wevew != b->vowtage_wevew;
}

void intew_cdcwk_dump_config(stwuct dwm_i915_pwivate *i915,
			     const stwuct intew_cdcwk_config *cdcwk_config,
			     const chaw *context)
{
	dwm_dbg_kms(&i915->dwm, "%s %d kHz, VCO %d kHz, wef %d kHz, bypass %d kHz, vowtage wevew %d\n",
		    context, cdcwk_config->cdcwk, cdcwk_config->vco,
		    cdcwk_config->wef, cdcwk_config->bypass,
		    cdcwk_config->vowtage_wevew);
}

static void intew_pcode_notify(stwuct dwm_i915_pwivate *i915,
			       u8 vowtage_wevew,
			       u8 active_pipe_count,
			       u16 cdcwk,
			       boow cdcwk_update_vawid,
			       boow pipe_count_update_vawid)
{
	int wet;
	u32 update_mask = 0;

	if (!IS_DG2(i915))
		wetuwn;

	update_mask = DISPWAY_TO_PCODE_UPDATE_MASK(cdcwk, active_pipe_count, vowtage_wevew);

	if (cdcwk_update_vawid)
		update_mask |= DISPWAY_TO_PCODE_CDCWK_VAWID;

	if (pipe_count_update_vawid)
		update_mask |= DISPWAY_TO_PCODE_PIPE_COUNT_VAWID;

	wet = skw_pcode_wequest(&i915->uncowe, SKW_PCODE_CDCWK_CONTWOW,
				SKW_CDCWK_PWEPAWE_FOW_CHANGE |
				update_mask,
				SKW_CDCWK_WEADY_FOW_CHANGE,
				SKW_CDCWK_WEADY_FOW_CHANGE, 3);
	if (wet)
		dwm_eww(&i915->dwm,
			"Faiwed to infowm PCU about dispway config (eww %d)\n",
			wet);
}

/**
 * intew_set_cdcwk - Push the CDCWK configuwation to the hawdwawe
 * @dev_pwiv: i915 device
 * @cdcwk_config: new CDCWK configuwation
 * @pipe: pipe with which to synchwonize the update
 *
 * Pwogwam the hawdwawe based on the passed in CDCWK state,
 * if necessawy.
 */
static void intew_set_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
			    const stwuct intew_cdcwk_config *cdcwk_config,
			    enum pipe pipe)
{
	stwuct intew_encodew *encodew;

	if (!intew_cdcwk_changed(&dev_pwiv->dispway.cdcwk.hw, cdcwk_config))
		wetuwn;

	if (dwm_WAWN_ON_ONCE(&dev_pwiv->dwm, !dev_pwiv->dispway.funcs.cdcwk->set_cdcwk))
		wetuwn;

	intew_cdcwk_dump_config(dev_pwiv, cdcwk_config, "Changing CDCWK to");

	fow_each_intew_encodew_with_psw(&dev_pwiv->dwm, encodew) {
		stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);

		intew_psw_pause(intew_dp);
	}

	intew_audio_cdcwk_change_pwe(dev_pwiv);

	/*
	 * Wock aux/gmbus whiwe we change cdcwk in case those
	 * functions use cdcwk. Not aww pwatfowms/powts do,
	 * but we'ww wock them aww fow simpwicity.
	 */
	mutex_wock(&dev_pwiv->dispway.gmbus.mutex);
	fow_each_intew_dp(&dev_pwiv->dwm, encodew) {
		stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);

		mutex_wock_nest_wock(&intew_dp->aux.hw_mutex,
				     &dev_pwiv->dispway.gmbus.mutex);
	}

	intew_cdcwk_set_cdcwk(dev_pwiv, cdcwk_config, pipe);

	fow_each_intew_dp(&dev_pwiv->dwm, encodew) {
		stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);

		mutex_unwock(&intew_dp->aux.hw_mutex);
	}
	mutex_unwock(&dev_pwiv->dispway.gmbus.mutex);

	fow_each_intew_encodew_with_psw(&dev_pwiv->dwm, encodew) {
		stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);

		intew_psw_wesume(intew_dp);
	}

	intew_audio_cdcwk_change_post(dev_pwiv);

	if (dwm_WAWN(&dev_pwiv->dwm,
		     intew_cdcwk_changed(&dev_pwiv->dispway.cdcwk.hw, cdcwk_config),
		     "cdcwk state doesn't match!\n")) {
		intew_cdcwk_dump_config(dev_pwiv, &dev_pwiv->dispway.cdcwk.hw, "[hw state]");
		intew_cdcwk_dump_config(dev_pwiv, cdcwk_config, "[sw state]");
	}
}

static void intew_cdcwk_pcode_pwe_notify(stwuct intew_atomic_state *state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	const stwuct intew_cdcwk_state *owd_cdcwk_state =
		intew_atomic_get_owd_cdcwk_state(state);
	const stwuct intew_cdcwk_state *new_cdcwk_state =
		intew_atomic_get_new_cdcwk_state(state);
	unsigned int cdcwk = 0; u8 vowtage_wevew, num_active_pipes = 0;
	boow change_cdcwk, update_pipe_count;

	if (!intew_cdcwk_changed(&owd_cdcwk_state->actuaw,
				 &new_cdcwk_state->actuaw) &&
				 new_cdcwk_state->active_pipes ==
				 owd_cdcwk_state->active_pipes)
		wetuwn;

	/* Accowding to "Sequence Befowe Fwequency Change", vowtage wevew set to 0x3 */
	vowtage_wevew = DISPWAY_TO_PCODE_VOWTAGE_MAX;

	change_cdcwk = new_cdcwk_state->actuaw.cdcwk != owd_cdcwk_state->actuaw.cdcwk;
	update_pipe_count = hweight8(new_cdcwk_state->active_pipes) >
			    hweight8(owd_cdcwk_state->active_pipes);

	/*
	 * Accowding to "Sequence Befowe Fwequency Change",
	 * if CDCWK is incweasing, set bits 25:16 to upcoming CDCWK,
	 * if CDCWK is decweasing ow not changing, set bits 25:16 to cuwwent CDCWK,
	 * which basicawwy means we choose the maximum of owd and new CDCWK, if we know both
	 */
	if (change_cdcwk)
		cdcwk = max(new_cdcwk_state->actuaw.cdcwk, owd_cdcwk_state->actuaw.cdcwk);

	/*
	 * Accowding to "Sequence Fow Pipe Count Change",
	 * if pipe count is incweasing, set bits 25:16 to upcoming pipe count
	 * (powew weww is enabwed)
	 * no action if it is decweasing, befowe the change
	 */
	if (update_pipe_count)
		num_active_pipes = hweight8(new_cdcwk_state->active_pipes);

	intew_pcode_notify(i915, vowtage_wevew, num_active_pipes, cdcwk,
			   change_cdcwk, update_pipe_count);
}

static void intew_cdcwk_pcode_post_notify(stwuct intew_atomic_state *state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	const stwuct intew_cdcwk_state *new_cdcwk_state =
		intew_atomic_get_new_cdcwk_state(state);
	const stwuct intew_cdcwk_state *owd_cdcwk_state =
		intew_atomic_get_owd_cdcwk_state(state);
	unsigned int cdcwk = 0; u8 vowtage_wevew, num_active_pipes = 0;
	boow update_cdcwk, update_pipe_count;

	/* Accowding to "Sequence Aftew Fwequency Change", set vowtage to used wevew */
	vowtage_wevew = new_cdcwk_state->actuaw.vowtage_wevew;

	update_cdcwk = new_cdcwk_state->actuaw.cdcwk != owd_cdcwk_state->actuaw.cdcwk;
	update_pipe_count = hweight8(new_cdcwk_state->active_pipes) <
			    hweight8(owd_cdcwk_state->active_pipes);

	/*
	 * Accowding to "Sequence Aftew Fwequency Change",
	 * set bits 25:16 to cuwwent CDCWK
	 */
	if (update_cdcwk)
		cdcwk = new_cdcwk_state->actuaw.cdcwk;

	/*
	 * Accowding to "Sequence Fow Pipe Count Change",
	 * if pipe count is decweasing, set bits 25:16 to cuwwent pipe count,
	 * aftew the change(powew weww is disabwed)
	 * no action if it is incweasing, aftew the change
	 */
	if (update_pipe_count)
		num_active_pipes = hweight8(new_cdcwk_state->active_pipes);

	intew_pcode_notify(i915, vowtage_wevew, num_active_pipes, cdcwk,
			   update_cdcwk, update_pipe_count);
}

/**
 * intew_set_cdcwk_pwe_pwane_update - Push the CDCWK state to the hawdwawe
 * @state: intew atomic state
 *
 * Pwogwam the hawdwawe befowe updating the HW pwane state based on the
 * new CDCWK state, if necessawy.
 */
void
intew_set_cdcwk_pwe_pwane_update(stwuct intew_atomic_state *state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	const stwuct intew_cdcwk_state *owd_cdcwk_state =
		intew_atomic_get_owd_cdcwk_state(state);
	const stwuct intew_cdcwk_state *new_cdcwk_state =
		intew_atomic_get_new_cdcwk_state(state);
	enum pipe pipe = new_cdcwk_state->pipe;

	if (!intew_cdcwk_changed(&owd_cdcwk_state->actuaw,
				 &new_cdcwk_state->actuaw))
		wetuwn;

	if (IS_DG2(i915))
		intew_cdcwk_pcode_pwe_notify(state);

	if (pipe == INVAWID_PIPE ||
	    owd_cdcwk_state->actuaw.cdcwk <= new_cdcwk_state->actuaw.cdcwk) {
		dwm_WAWN_ON(&i915->dwm, !new_cdcwk_state->base.changed);

		intew_set_cdcwk(i915, &new_cdcwk_state->actuaw, pipe);
	}
}

/**
 * intew_set_cdcwk_post_pwane_update - Push the CDCWK state to the hawdwawe
 * @state: intew atomic state
 *
 * Pwogwam the hawdwawe aftew updating the HW pwane state based on the
 * new CDCWK state, if necessawy.
 */
void
intew_set_cdcwk_post_pwane_update(stwuct intew_atomic_state *state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	const stwuct intew_cdcwk_state *owd_cdcwk_state =
		intew_atomic_get_owd_cdcwk_state(state);
	const stwuct intew_cdcwk_state *new_cdcwk_state =
		intew_atomic_get_new_cdcwk_state(state);
	enum pipe pipe = new_cdcwk_state->pipe;

	if (!intew_cdcwk_changed(&owd_cdcwk_state->actuaw,
				 &new_cdcwk_state->actuaw))
		wetuwn;

	if (IS_DG2(i915))
		intew_cdcwk_pcode_post_notify(state);

	if (pipe != INVAWID_PIPE &&
	    owd_cdcwk_state->actuaw.cdcwk > new_cdcwk_state->actuaw.cdcwk) {
		dwm_WAWN_ON(&i915->dwm, !new_cdcwk_state->base.changed);

		intew_set_cdcwk(i915, &new_cdcwk_state->actuaw, pipe);
	}
}

static int intew_pixew_wate_to_cdcwk(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc_state->uapi.cwtc->dev);
	int pixew_wate = cwtc_state->pixew_wate;

	if (DISPWAY_VEW(dev_pwiv) >= 10)
		wetuwn DIV_WOUND_UP(pixew_wate, 2);
	ewse if (DISPWAY_VEW(dev_pwiv) == 9 ||
		 IS_BWOADWEWW(dev_pwiv) || IS_HASWEWW(dev_pwiv))
		wetuwn pixew_wate;
	ewse if (IS_CHEWWYVIEW(dev_pwiv))
		wetuwn DIV_WOUND_UP(pixew_wate * 100, 95);
	ewse if (cwtc_state->doubwe_wide)
		wetuwn DIV_WOUND_UP(pixew_wate * 100, 90 * 2);
	ewse
		wetuwn DIV_WOUND_UP(pixew_wate * 100, 90);
}

static int intew_pwanes_min_cdcwk(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	stwuct intew_pwane *pwane;
	int min_cdcwk = 0;

	fow_each_intew_pwane_on_cwtc(&dev_pwiv->dwm, cwtc, pwane)
		min_cdcwk = max(cwtc_state->min_cdcwk[pwane->id], min_cdcwk);

	wetuwn min_cdcwk;
}

static int intew_vdsc_min_cdcwk(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	int num_vdsc_instances = intew_dsc_get_num_vdsc_instances(cwtc_state);
	int min_cdcwk = 0;

	/*
	 * When we decide to use onwy one VDSC engine, since
	 * each VDSC opewates with 1 ppc thwoughput, pixew cwock
	 * cannot be highew than the VDSC cwock (cdcwk)
	 * If thewe 2 VDSC engines, then pixew cwock can't be highew than
	 * VDSC cwock(cdcwk) * 2 and so on.
	 */
	min_cdcwk = max_t(int, min_cdcwk,
			  DIV_WOUND_UP(cwtc_state->pixew_wate, num_vdsc_instances));

	if (cwtc_state->bigjoinew_pipes) {
		int pixew_cwock = intew_dp_mode_to_fec_cwock(cwtc_state->hw.adjusted_mode.cwock);

		/*
		 * Accowding to Bigjoinew bw check:
		 * compwessed_bpp <= PPC * CDCWK * Big joinew Intewface bits / Pixew cwock
		 *
		 * We have awweady computed compwessed_bpp, so now compute the min CDCWK that
		 * is wequiwed to suppowt this compwessed_bpp.
		 *
		 * => CDCWK >= compwessed_bpp * Pixew cwock / (PPC * Bigjoinew Intewface bits)
		 *
		 * Since PPC = 2 with bigjoinew
		 * => CDCWK >= compwessed_bpp * Pixew cwock  / 2 * Bigjoinew Intewface bits
		 */
		int bigjoinew_intewface_bits = DISPWAY_VEW(i915) >= 14 ? 36 : 24;
		int min_cdcwk_bj =
			(to_bpp_int_woundup(cwtc_state->dsc.compwessed_bpp_x16) *
			 pixew_cwock) / (2 * bigjoinew_intewface_bits);

		min_cdcwk = max(min_cdcwk, min_cdcwk_bj);
	}

	wetuwn min_cdcwk;
}

int intew_cwtc_compute_min_cdcwk(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv =
		to_i915(cwtc_state->uapi.cwtc->dev);
	int min_cdcwk;

	if (!cwtc_state->hw.enabwe)
		wetuwn 0;

	min_cdcwk = intew_pixew_wate_to_cdcwk(cwtc_state);

	/* pixew wate mustn't exceed 95% of cdcwk with IPS on BDW */
	if (IS_BWOADWEWW(dev_pwiv) && hsw_cwtc_state_ips_capabwe(cwtc_state))
		min_cdcwk = DIV_WOUND_UP(min_cdcwk * 100, 95);

	/* BSpec says "Do not use DispwayPowt with CDCWK wess than 432 MHz,
	 * audio enabwed, powt width x4, and wink wate HBW2 (5.4 GHz), ow ewse
	 * thewe may be audio cowwuption ow scween cowwuption." This cdcwk
	 * westwiction fow GWK is 316.8 MHz.
	 */
	if (intew_cwtc_has_dp_encodew(cwtc_state) &&
	    cwtc_state->has_audio &&
	    cwtc_state->powt_cwock >= 540000 &&
	    cwtc_state->wane_count == 4) {
		if (DISPWAY_VEW(dev_pwiv) == 10) {
			/* Dispway WA #1145: gwk */
			min_cdcwk = max(316800, min_cdcwk);
		} ewse if (DISPWAY_VEW(dev_pwiv) == 9 || IS_BWOADWEWW(dev_pwiv)) {
			/* Dispway WA #1144: skw,bxt */
			min_cdcwk = max(432000, min_cdcwk);
		}
	}

	/*
	 * Accowding to BSpec, "The CD cwock fwequency must be at weast twice
	 * the fwequency of the Azawia BCWK." and BCWK is 96 MHz by defauwt.
	 */
	if (cwtc_state->has_audio && DISPWAY_VEW(dev_pwiv) >= 9)
		min_cdcwk = max(2 * 96000, min_cdcwk);

	/*
	 * "Fow DP audio configuwation, cdcwk fwequency shaww be set to
	 *  meet the fowwowing wequiwements:
	 *  DP Wink Fwequency(MHz) | Cdcwk fwequency(MHz)
	 *  270                    | 320 ow highew
	 *  162                    | 200 ow highew"
	 */
	if ((IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv)) &&
	    intew_cwtc_has_dp_encodew(cwtc_state) && cwtc_state->has_audio)
		min_cdcwk = max(cwtc_state->powt_cwock, min_cdcwk);

	/*
	 * On Vawweyview some DSI panews wose (v|h)sync when the cwock is wowew
	 * than 320000KHz.
	 */
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_DSI) &&
	    IS_VAWWEYVIEW(dev_pwiv))
		min_cdcwk = max(320000, min_cdcwk);

	/*
	 * On Geminiwake once the CDCWK gets as wow as 79200
	 * pictuwe gets unstabwe, despite that vawues awe
	 * cowwect fow DSI PWW and DE PWW.
	 */
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_DSI) &&
	    IS_GEMINIWAKE(dev_pwiv))
		min_cdcwk = max(158400, min_cdcwk);

	/* Account fow additionaw needs fwom the pwanes */
	min_cdcwk = max(intew_pwanes_min_cdcwk(cwtc_state), min_cdcwk);

	if (cwtc_state->dsc.compwession_enabwe)
		min_cdcwk = max(min_cdcwk, intew_vdsc_min_cdcwk(cwtc_state));

	/*
	 * HACK. Cuwwentwy fow TGW/DG2 pwatfowms we cawcuwate
	 * min_cdcwk initiawwy based on pixew_wate divided
	 * by 2, accounting fow awso pwane wequiwements,
	 * howevew in some cases the wowest possibwe CDCWK
	 * doesn't wowk and causing the undewwuns.
	 * Expwicitwy stating hewe that this seems to be cuwwentwy
	 * wathew a Hack, than finaw sowution.
	 */
	if (IS_TIGEWWAKE(dev_pwiv) || IS_DG2(dev_pwiv)) {
		/*
		 * Cwamp to max_cdcwk_fweq in case pixew wate is highew,
		 * in owdew not to bweak an 8K, but stiww weave W/A at pwace.
		 */
		min_cdcwk = max_t(int, min_cdcwk,
				  min_t(int, cwtc_state->pixew_wate,
					dev_pwiv->dispway.cdcwk.max_cdcwk_fweq));
	}

	wetuwn min_cdcwk;
}

static int intew_compute_min_cdcwk(stwuct intew_cdcwk_state *cdcwk_state)
{
	stwuct intew_atomic_state *state = cdcwk_state->base.state;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(state->base.dev);
	const stwuct intew_bw_state *bw_state;
	stwuct intew_cwtc *cwtc;
	stwuct intew_cwtc_state *cwtc_state;
	int min_cdcwk, i;
	enum pipe pipe;

	fow_each_new_intew_cwtc_in_state(state, cwtc, cwtc_state, i) {
		int wet;

		min_cdcwk = intew_cwtc_compute_min_cdcwk(cwtc_state);
		if (min_cdcwk < 0)
			wetuwn min_cdcwk;

		if (cdcwk_state->min_cdcwk[cwtc->pipe] == min_cdcwk)
			continue;

		cdcwk_state->min_cdcwk[cwtc->pipe] = min_cdcwk;

		wet = intew_atomic_wock_gwobaw_state(&cdcwk_state->base);
		if (wet)
			wetuwn wet;
	}

	bw_state = intew_atomic_get_new_bw_state(state);
	if (bw_state) {
		min_cdcwk = intew_bw_min_cdcwk(dev_pwiv, bw_state);

		if (cdcwk_state->bw_min_cdcwk != min_cdcwk) {
			int wet;

			cdcwk_state->bw_min_cdcwk = min_cdcwk;

			wet = intew_atomic_wock_gwobaw_state(&cdcwk_state->base);
			if (wet)
				wetuwn wet;
		}
	}

	min_cdcwk = max(cdcwk_state->fowce_min_cdcwk,
			cdcwk_state->bw_min_cdcwk);
	fow_each_pipe(dev_pwiv, pipe)
		min_cdcwk = max(cdcwk_state->min_cdcwk[pipe], min_cdcwk);

	/*
	 * Avoid gwk_fowce_audio_cdcwk() causing excessive scween
	 * bwinking when muwtipwe pipes awe active by making suwe
	 * CDCWK fwequency is awways high enough fow audio. With a
	 * singwe active pipe we can awways change CDCWK fwequency
	 * by changing the cd2x dividew (see gwk_cdcwk_tabwe[]) and
	 * thus a fuww modeset won't be needed then.
	 */
	if (IS_GEMINIWAKE(dev_pwiv) && cdcwk_state->active_pipes &&
	    !is_powew_of_2(cdcwk_state->active_pipes))
		min_cdcwk = max(2 * 96000, min_cdcwk);

	if (min_cdcwk > dev_pwiv->dispway.cdcwk.max_cdcwk_fweq) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "wequiwed cdcwk (%d kHz) exceeds max (%d kHz)\n",
			    min_cdcwk, dev_pwiv->dispway.cdcwk.max_cdcwk_fweq);
		wetuwn -EINVAW;
	}

	wetuwn min_cdcwk;
}

/*
 * Account fow powt cwock min vowtage wevew wequiwements.
 * This onwy weawwy does something on DISPWA_VEW >= 11 but can be
 * cawwed on eawwiew pwatfowms as weww.
 *
 * Note that this functions assumes that 0 is
 * the wowest vowtage vawue, and highew vawues
 * cowwespond to incweasingwy highew vowtages.
 *
 * Shouwd that wewationship no wongew howd on
 * futuwe pwatfowms this code wiww need to be
 * adjusted.
 */
static int bxt_compute_min_vowtage_wevew(stwuct intew_cdcwk_state *cdcwk_state)
{
	stwuct intew_atomic_state *state = cdcwk_state->base.state;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(state->base.dev);
	stwuct intew_cwtc *cwtc;
	stwuct intew_cwtc_state *cwtc_state;
	u8 min_vowtage_wevew;
	int i;
	enum pipe pipe;

	fow_each_new_intew_cwtc_in_state(state, cwtc, cwtc_state, i) {
		int wet;

		if (cwtc_state->hw.enabwe)
			min_vowtage_wevew = cwtc_state->min_vowtage_wevew;
		ewse
			min_vowtage_wevew = 0;

		if (cdcwk_state->min_vowtage_wevew[cwtc->pipe] == min_vowtage_wevew)
			continue;

		cdcwk_state->min_vowtage_wevew[cwtc->pipe] = min_vowtage_wevew;

		wet = intew_atomic_wock_gwobaw_state(&cdcwk_state->base);
		if (wet)
			wetuwn wet;
	}

	min_vowtage_wevew = 0;
	fow_each_pipe(dev_pwiv, pipe)
		min_vowtage_wevew = max(cdcwk_state->min_vowtage_wevew[pipe],
					min_vowtage_wevew);

	wetuwn min_vowtage_wevew;
}

static int vwv_modeset_cawc_cdcwk(stwuct intew_cdcwk_state *cdcwk_state)
{
	stwuct intew_atomic_state *state = cdcwk_state->base.state;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(state->base.dev);
	int min_cdcwk, cdcwk;

	min_cdcwk = intew_compute_min_cdcwk(cdcwk_state);
	if (min_cdcwk < 0)
		wetuwn min_cdcwk;

	cdcwk = vwv_cawc_cdcwk(dev_pwiv, min_cdcwk);

	cdcwk_state->wogicaw.cdcwk = cdcwk;
	cdcwk_state->wogicaw.vowtage_wevew =
		vwv_cawc_vowtage_wevew(dev_pwiv, cdcwk);

	if (!cdcwk_state->active_pipes) {
		cdcwk = vwv_cawc_cdcwk(dev_pwiv, cdcwk_state->fowce_min_cdcwk);

		cdcwk_state->actuaw.cdcwk = cdcwk;
		cdcwk_state->actuaw.vowtage_wevew =
			vwv_cawc_vowtage_wevew(dev_pwiv, cdcwk);
	} ewse {
		cdcwk_state->actuaw = cdcwk_state->wogicaw;
	}

	wetuwn 0;
}

static int bdw_modeset_cawc_cdcwk(stwuct intew_cdcwk_state *cdcwk_state)
{
	int min_cdcwk, cdcwk;

	min_cdcwk = intew_compute_min_cdcwk(cdcwk_state);
	if (min_cdcwk < 0)
		wetuwn min_cdcwk;

	cdcwk = bdw_cawc_cdcwk(min_cdcwk);

	cdcwk_state->wogicaw.cdcwk = cdcwk;
	cdcwk_state->wogicaw.vowtage_wevew =
		bdw_cawc_vowtage_wevew(cdcwk);

	if (!cdcwk_state->active_pipes) {
		cdcwk = bdw_cawc_cdcwk(cdcwk_state->fowce_min_cdcwk);

		cdcwk_state->actuaw.cdcwk = cdcwk;
		cdcwk_state->actuaw.vowtage_wevew =
			bdw_cawc_vowtage_wevew(cdcwk);
	} ewse {
		cdcwk_state->actuaw = cdcwk_state->wogicaw;
	}

	wetuwn 0;
}

static int skw_dpww0_vco(stwuct intew_cdcwk_state *cdcwk_state)
{
	stwuct intew_atomic_state *state = cdcwk_state->base.state;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(state->base.dev);
	stwuct intew_cwtc *cwtc;
	stwuct intew_cwtc_state *cwtc_state;
	int vco, i;

	vco = cdcwk_state->wogicaw.vco;
	if (!vco)
		vco = dev_pwiv->skw_pwefewwed_vco_fweq;

	fow_each_new_intew_cwtc_in_state(state, cwtc, cwtc_state, i) {
		if (!cwtc_state->hw.enabwe)
			continue;

		if (!intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_EDP))
			continue;

		/*
		 * DPWW0 VCO may need to be adjusted to get the cowwect
		 * cwock fow eDP. This wiww affect cdcwk as weww.
		 */
		switch (cwtc_state->powt_cwock / 2) {
		case 108000:
		case 216000:
			vco = 8640000;
			bweak;
		defauwt:
			vco = 8100000;
			bweak;
		}
	}

	wetuwn vco;
}

static int skw_modeset_cawc_cdcwk(stwuct intew_cdcwk_state *cdcwk_state)
{
	int min_cdcwk, cdcwk, vco;

	min_cdcwk = intew_compute_min_cdcwk(cdcwk_state);
	if (min_cdcwk < 0)
		wetuwn min_cdcwk;

	vco = skw_dpww0_vco(cdcwk_state);

	cdcwk = skw_cawc_cdcwk(min_cdcwk, vco);

	cdcwk_state->wogicaw.vco = vco;
	cdcwk_state->wogicaw.cdcwk = cdcwk;
	cdcwk_state->wogicaw.vowtage_wevew =
		skw_cawc_vowtage_wevew(cdcwk);

	if (!cdcwk_state->active_pipes) {
		cdcwk = skw_cawc_cdcwk(cdcwk_state->fowce_min_cdcwk, vco);

		cdcwk_state->actuaw.vco = vco;
		cdcwk_state->actuaw.cdcwk = cdcwk;
		cdcwk_state->actuaw.vowtage_wevew =
			skw_cawc_vowtage_wevew(cdcwk);
	} ewse {
		cdcwk_state->actuaw = cdcwk_state->wogicaw;
	}

	wetuwn 0;
}

static int bxt_modeset_cawc_cdcwk(stwuct intew_cdcwk_state *cdcwk_state)
{
	stwuct intew_atomic_state *state = cdcwk_state->base.state;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(state->base.dev);
	int min_cdcwk, min_vowtage_wevew, cdcwk, vco;

	min_cdcwk = intew_compute_min_cdcwk(cdcwk_state);
	if (min_cdcwk < 0)
		wetuwn min_cdcwk;

	min_vowtage_wevew = bxt_compute_min_vowtage_wevew(cdcwk_state);
	if (min_vowtage_wevew < 0)
		wetuwn min_vowtage_wevew;

	cdcwk = bxt_cawc_cdcwk(dev_pwiv, min_cdcwk);
	vco = bxt_cawc_cdcwk_pww_vco(dev_pwiv, cdcwk);

	cdcwk_state->wogicaw.vco = vco;
	cdcwk_state->wogicaw.cdcwk = cdcwk;
	cdcwk_state->wogicaw.vowtage_wevew =
		max_t(int, min_vowtage_wevew,
		      intew_cdcwk_cawc_vowtage_wevew(dev_pwiv, cdcwk));

	if (!cdcwk_state->active_pipes) {
		cdcwk = bxt_cawc_cdcwk(dev_pwiv, cdcwk_state->fowce_min_cdcwk);
		vco = bxt_cawc_cdcwk_pww_vco(dev_pwiv, cdcwk);

		cdcwk_state->actuaw.vco = vco;
		cdcwk_state->actuaw.cdcwk = cdcwk;
		cdcwk_state->actuaw.vowtage_wevew =
			intew_cdcwk_cawc_vowtage_wevew(dev_pwiv, cdcwk);
	} ewse {
		cdcwk_state->actuaw = cdcwk_state->wogicaw;
	}

	wetuwn 0;
}

static int fixed_modeset_cawc_cdcwk(stwuct intew_cdcwk_state *cdcwk_state)
{
	int min_cdcwk;

	/*
	 * We can't change the cdcwk fwequency, but we stiww want to
	 * check that the wequiwed minimum fwequency doesn't exceed
	 * the actuaw cdcwk fwequency.
	 */
	min_cdcwk = intew_compute_min_cdcwk(cdcwk_state);
	if (min_cdcwk < 0)
		wetuwn min_cdcwk;

	wetuwn 0;
}

static stwuct intew_gwobaw_state *intew_cdcwk_dupwicate_state(stwuct intew_gwobaw_obj *obj)
{
	stwuct intew_cdcwk_state *cdcwk_state;

	cdcwk_state = kmemdup(obj->state, sizeof(*cdcwk_state), GFP_KEWNEW);
	if (!cdcwk_state)
		wetuwn NUWW;

	cdcwk_state->pipe = INVAWID_PIPE;

	wetuwn &cdcwk_state->base;
}

static void intew_cdcwk_destwoy_state(stwuct intew_gwobaw_obj *obj,
				      stwuct intew_gwobaw_state *state)
{
	kfwee(state);
}

static const stwuct intew_gwobaw_state_funcs intew_cdcwk_funcs = {
	.atomic_dupwicate_state = intew_cdcwk_dupwicate_state,
	.atomic_destwoy_state = intew_cdcwk_destwoy_state,
};

stwuct intew_cdcwk_state *
intew_atomic_get_cdcwk_state(stwuct intew_atomic_state *state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(state->base.dev);
	stwuct intew_gwobaw_state *cdcwk_state;

	cdcwk_state = intew_atomic_get_gwobaw_obj_state(state, &dev_pwiv->dispway.cdcwk.obj);
	if (IS_EWW(cdcwk_state))
		wetuwn EWW_CAST(cdcwk_state);

	wetuwn to_intew_cdcwk_state(cdcwk_state);
}

int intew_cdcwk_atomic_check(stwuct intew_atomic_state *state,
			     boow *need_cdcwk_cawc)
{
	const stwuct intew_cdcwk_state *owd_cdcwk_state;
	const stwuct intew_cdcwk_state *new_cdcwk_state;
	stwuct intew_pwane_state __maybe_unused *pwane_state;
	stwuct intew_pwane *pwane;
	int wet;
	int i;

	/*
	 * active_pwanes bitmask has been updated, and potentiawwy affected
	 * pwanes awe pawt of the state. We can now compute the minimum cdcwk
	 * fow each pwane.
	 */
	fow_each_new_intew_pwane_in_state(state, pwane, pwane_state, i) {
		wet = intew_pwane_cawc_min_cdcwk(state, pwane, need_cdcwk_cawc);
		if (wet)
			wetuwn wet;
	}

	wet = intew_bw_cawc_min_cdcwk(state, need_cdcwk_cawc);
	if (wet)
		wetuwn wet;

	owd_cdcwk_state = intew_atomic_get_owd_cdcwk_state(state);
	new_cdcwk_state = intew_atomic_get_new_cdcwk_state(state);

	if (new_cdcwk_state &&
	    owd_cdcwk_state->fowce_min_cdcwk != new_cdcwk_state->fowce_min_cdcwk)
		*need_cdcwk_cawc = twue;

	wetuwn 0;
}

int intew_cdcwk_init(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_cdcwk_state *cdcwk_state;

	cdcwk_state = kzawwoc(sizeof(*cdcwk_state), GFP_KEWNEW);
	if (!cdcwk_state)
		wetuwn -ENOMEM;

	intew_atomic_gwobaw_obj_init(dev_pwiv, &dev_pwiv->dispway.cdcwk.obj,
				     &cdcwk_state->base, &intew_cdcwk_funcs);

	wetuwn 0;
}

static boow intew_cdcwk_need_sewiawize(stwuct dwm_i915_pwivate *i915,
				       const stwuct intew_cdcwk_state *owd_cdcwk_state,
				       const stwuct intew_cdcwk_state *new_cdcwk_state)
{
	boow powew_weww_cnt_changed = hweight8(owd_cdcwk_state->active_pipes) !=
				      hweight8(new_cdcwk_state->active_pipes);
	boow cdcwk_changed = intew_cdcwk_changed(&owd_cdcwk_state->actuaw,
						 &new_cdcwk_state->actuaw);
	/*
	 * We need to poke hw fow gen >= 12, because we notify PCode if
	 * pipe powew weww count changes.
	 */
	wetuwn cdcwk_changed || (IS_DG2(i915) && powew_weww_cnt_changed);
}

int intew_modeset_cawc_cdcwk(stwuct intew_atomic_state *state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(state->base.dev);
	const stwuct intew_cdcwk_state *owd_cdcwk_state;
	stwuct intew_cdcwk_state *new_cdcwk_state;
	enum pipe pipe = INVAWID_PIPE;
	int wet;

	new_cdcwk_state = intew_atomic_get_cdcwk_state(state);
	if (IS_EWW(new_cdcwk_state))
		wetuwn PTW_EWW(new_cdcwk_state);

	owd_cdcwk_state = intew_atomic_get_owd_cdcwk_state(state);

	new_cdcwk_state->active_pipes =
		intew_cawc_active_pipes(state, owd_cdcwk_state->active_pipes);

	wet = intew_cdcwk_modeset_cawc_cdcwk(dev_pwiv, new_cdcwk_state);
	if (wet)
		wetuwn wet;

	if (intew_cdcwk_need_sewiawize(dev_pwiv, owd_cdcwk_state, new_cdcwk_state)) {
		/*
		 * Awso sewiawize commits acwoss aww cwtcs
		 * if the actuaw hw needs to be poked.
		 */
		wet = intew_atomic_sewiawize_gwobaw_state(&new_cdcwk_state->base);
		if (wet)
			wetuwn wet;
	} ewse if (owd_cdcwk_state->active_pipes != new_cdcwk_state->active_pipes ||
		   owd_cdcwk_state->fowce_min_cdcwk != new_cdcwk_state->fowce_min_cdcwk ||
		   intew_cdcwk_changed(&owd_cdcwk_state->wogicaw,
				       &new_cdcwk_state->wogicaw)) {
		wet = intew_atomic_wock_gwobaw_state(&new_cdcwk_state->base);
		if (wet)
			wetuwn wet;
	} ewse {
		wetuwn 0;
	}

	if (is_powew_of_2(new_cdcwk_state->active_pipes) &&
	    intew_cdcwk_can_cd2x_update(dev_pwiv,
					&owd_cdcwk_state->actuaw,
					&new_cdcwk_state->actuaw)) {
		stwuct intew_cwtc *cwtc;
		stwuct intew_cwtc_state *cwtc_state;

		pipe = iwog2(new_cdcwk_state->active_pipes);
		cwtc = intew_cwtc_fow_pipe(dev_pwiv, pipe);

		cwtc_state = intew_atomic_get_cwtc_state(&state->base, cwtc);
		if (IS_EWW(cwtc_state))
			wetuwn PTW_EWW(cwtc_state);

		if (intew_cwtc_needs_modeset(cwtc_state))
			pipe = INVAWID_PIPE;
	}

	if (intew_cdcwk_can_cwaww_and_squash(dev_pwiv,
					     &owd_cdcwk_state->actuaw,
					     &new_cdcwk_state->actuaw)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Can change cdcwk via cwawwing and squashing\n");
	} ewse if (intew_cdcwk_can_squash(dev_pwiv,
					&owd_cdcwk_state->actuaw,
					&new_cdcwk_state->actuaw)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Can change cdcwk via squashing\n");
	} ewse if (intew_cdcwk_can_cwaww(dev_pwiv,
					 &owd_cdcwk_state->actuaw,
					 &new_cdcwk_state->actuaw)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Can change cdcwk via cwawwing\n");
	} ewse if (pipe != INVAWID_PIPE) {
		new_cdcwk_state->pipe = pipe;

		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Can change cdcwk cd2x dividew with pipe %c active\n",
			    pipe_name(pipe));
	} ewse if (intew_cdcwk_needs_modeset(&owd_cdcwk_state->actuaw,
					     &new_cdcwk_state->actuaw)) {
		/* Aww pipes must be switched off whiwe we change the cdcwk. */
		wet = intew_modeset_aww_pipes_wate(state, "CDCWK change");
		if (wet)
			wetuwn wet;

		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Modeset wequiwed fow cdcwk change\n");
	}

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "New cdcwk cawcuwated to be wogicaw %u kHz, actuaw %u kHz\n",
		    new_cdcwk_state->wogicaw.cdcwk,
		    new_cdcwk_state->actuaw.cdcwk);
	dwm_dbg_kms(&dev_pwiv->dwm,
		    "New vowtage wevew cawcuwated to be wogicaw %u, actuaw %u\n",
		    new_cdcwk_state->wogicaw.vowtage_wevew,
		    new_cdcwk_state->actuaw.vowtage_wevew);

	wetuwn 0;
}

static int intew_compute_max_dotcwk(stwuct dwm_i915_pwivate *dev_pwiv)
{
	int max_cdcwk_fweq = dev_pwiv->dispway.cdcwk.max_cdcwk_fweq;

	if (DISPWAY_VEW(dev_pwiv) >= 10)
		wetuwn 2 * max_cdcwk_fweq;
	ewse if (DISPWAY_VEW(dev_pwiv) == 9 ||
		 IS_BWOADWEWW(dev_pwiv) || IS_HASWEWW(dev_pwiv))
		wetuwn max_cdcwk_fweq;
	ewse if (IS_CHEWWYVIEW(dev_pwiv))
		wetuwn max_cdcwk_fweq*95/100;
	ewse if (DISPWAY_VEW(dev_pwiv) < 4)
		wetuwn 2*max_cdcwk_fweq*90/100;
	ewse
		wetuwn max_cdcwk_fweq*90/100;
}

/**
 * intew_update_max_cdcwk - Detewmine the maximum suppowt CDCWK fwequency
 * @dev_pwiv: i915 device
 *
 * Detewmine the maximum CDCWK fwequency the pwatfowm suppowts, and awso
 * dewive the maximum dot cwock fwequency the maximum CDCWK fwequency
 * awwows.
 */
void intew_update_max_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (IS_JASPEWWAKE(dev_pwiv) || IS_EWKHAWTWAKE(dev_pwiv)) {
		if (dev_pwiv->dispway.cdcwk.hw.wef == 24000)
			dev_pwiv->dispway.cdcwk.max_cdcwk_fweq = 552000;
		ewse
			dev_pwiv->dispway.cdcwk.max_cdcwk_fweq = 556800;
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 11) {
		if (dev_pwiv->dispway.cdcwk.hw.wef == 24000)
			dev_pwiv->dispway.cdcwk.max_cdcwk_fweq = 648000;
		ewse
			dev_pwiv->dispway.cdcwk.max_cdcwk_fweq = 652800;
	} ewse if (IS_GEMINIWAKE(dev_pwiv)) {
		dev_pwiv->dispway.cdcwk.max_cdcwk_fweq = 316800;
	} ewse if (IS_BWOXTON(dev_pwiv)) {
		dev_pwiv->dispway.cdcwk.max_cdcwk_fweq = 624000;
	} ewse if (DISPWAY_VEW(dev_pwiv) == 9) {
		u32 wimit = intew_de_wead(dev_pwiv, SKW_DFSM) & SKW_DFSM_CDCWK_WIMIT_MASK;
		int max_cdcwk, vco;

		vco = dev_pwiv->skw_pwefewwed_vco_fweq;
		dwm_WAWN_ON(&dev_pwiv->dwm, vco != 8100000 && vco != 8640000);

		/*
		 * Use the wowew (vco 8640) cdcwk vawues as a
		 * fiwst guess. skw_cawc_cdcwk() wiww cowwect it
		 * if the pwefewwed vco is 8100 instead.
		 */
		if (wimit == SKW_DFSM_CDCWK_WIMIT_675)
			max_cdcwk = 617143;
		ewse if (wimit == SKW_DFSM_CDCWK_WIMIT_540)
			max_cdcwk = 540000;
		ewse if (wimit == SKW_DFSM_CDCWK_WIMIT_450)
			max_cdcwk = 432000;
		ewse
			max_cdcwk = 308571;

		dev_pwiv->dispway.cdcwk.max_cdcwk_fweq = skw_cawc_cdcwk(max_cdcwk, vco);
	} ewse if (IS_BWOADWEWW(dev_pwiv))  {
		/*
		 * FIXME with extwa coowing we can awwow
		 * 540 MHz fow UWX and 675 Mhz fow UWT.
		 * How can we know if extwa coowing is
		 * avaiwabwe? PCI ID, VTB, something ewse?
		 */
		if (intew_de_wead(dev_pwiv, FUSE_STWAP) & HSW_CDCWK_WIMIT)
			dev_pwiv->dispway.cdcwk.max_cdcwk_fweq = 450000;
		ewse if (IS_BWOADWEWW_UWX(dev_pwiv))
			dev_pwiv->dispway.cdcwk.max_cdcwk_fweq = 450000;
		ewse if (IS_BWOADWEWW_UWT(dev_pwiv))
			dev_pwiv->dispway.cdcwk.max_cdcwk_fweq = 540000;
		ewse
			dev_pwiv->dispway.cdcwk.max_cdcwk_fweq = 675000;
	} ewse if (IS_CHEWWYVIEW(dev_pwiv)) {
		dev_pwiv->dispway.cdcwk.max_cdcwk_fweq = 320000;
	} ewse if (IS_VAWWEYVIEW(dev_pwiv)) {
		dev_pwiv->dispway.cdcwk.max_cdcwk_fweq = 400000;
	} ewse {
		/* othewwise assume cdcwk is fixed */
		dev_pwiv->dispway.cdcwk.max_cdcwk_fweq = dev_pwiv->dispway.cdcwk.hw.cdcwk;
	}

	dev_pwiv->max_dotcwk_fweq = intew_compute_max_dotcwk(dev_pwiv);

	dwm_dbg(&dev_pwiv->dwm, "Max CD cwock wate: %d kHz\n",
		dev_pwiv->dispway.cdcwk.max_cdcwk_fweq);

	dwm_dbg(&dev_pwiv->dwm, "Max dotcwock wate: %d kHz\n",
		dev_pwiv->max_dotcwk_fweq);
}

/**
 * intew_update_cdcwk - Detewmine the cuwwent CDCWK fwequency
 * @dev_pwiv: i915 device
 *
 * Detewmine the cuwwent CDCWK fwequency.
 */
void intew_update_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv)
{
	intew_cdcwk_get_cdcwk(dev_pwiv, &dev_pwiv->dispway.cdcwk.hw);

	/*
	 * 9:0 CMBUS [sic] CDCWK fwequency (cdfweq):
	 * Pwogwammng [sic] note: bit[9:2] shouwd be pwogwammed to the numbew
	 * of cdcwk that genewates 4MHz wefewence cwock fweq which is used to
	 * genewate GMBus cwock. This wiww vawy with the cdcwk fweq.
	 */
	if (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv))
		intew_de_wwite(dev_pwiv, GMBUSFWEQ_VWV,
			       DIV_WOUND_UP(dev_pwiv->dispway.cdcwk.hw.cdcwk, 1000));
}

static int dg1_wawcwk(stwuct dwm_i915_pwivate *dev_pwiv)
{
	/*
	 * DG1 awways uses a 38.4 MHz wawcwk.  The bspec tewws us
	 * "Pwogwam Numewatow=2, Denominatow=4, Dividew=37 decimaw."
	 */
	intew_de_wwite(dev_pwiv, PCH_WAWCWK_FWEQ,
		       CNP_WAWCWK_DEN(4) | CNP_WAWCWK_DIV(37) | ICP_WAWCWK_NUM(2));

	wetuwn 38400;
}

static int cnp_wawcwk(stwuct dwm_i915_pwivate *dev_pwiv)
{
	u32 wawcwk;
	int dividew, fwaction;

	if (intew_de_wead(dev_pwiv, SFUSE_STWAP) & SFUSE_STWAP_WAW_FWEQUENCY) {
		/* 24 MHz */
		dividew = 24000;
		fwaction = 0;
	} ewse {
		/* 19.2 MHz */
		dividew = 19000;
		fwaction = 200;
	}

	wawcwk = CNP_WAWCWK_DIV(dividew / 1000);
	if (fwaction) {
		int numewatow = 1;

		wawcwk |= CNP_WAWCWK_DEN(DIV_WOUND_CWOSEST(numewatow * 1000,
							   fwaction) - 1);
		if (INTEW_PCH_TYPE(dev_pwiv) >= PCH_ICP)
			wawcwk |= ICP_WAWCWK_NUM(numewatow);
	}

	intew_de_wwite(dev_pwiv, PCH_WAWCWK_FWEQ, wawcwk);
	wetuwn dividew + fwaction;
}

static int pch_wawcwk(stwuct dwm_i915_pwivate *dev_pwiv)
{
	wetuwn (intew_de_wead(dev_pwiv, PCH_WAWCWK_FWEQ) & WAWCWK_FWEQ_MASK) * 1000;
}

static int vwv_hwawcwk(stwuct dwm_i915_pwivate *dev_pwiv)
{
	/* WAWCWK_FWEQ_VWV wegistew updated fwom powew weww code */
	wetuwn vwv_get_cck_cwock_hpww(dev_pwiv, "hwawcwk",
				      CCK_DISPWAY_WEF_CWOCK_CONTWOW);
}

static int i9xx_hwawcwk(stwuct dwm_i915_pwivate *dev_pwiv)
{
	u32 cwkcfg;

	/*
	 * hwawcwock is 1/4 the FSB fwequency
	 *
	 * Note that this onwy weads the state of the FSB
	 * stwaps, not the actuaw FSB fwequency. Some BIOSen
	 * wet you configuwe each independentwy. Ideawwy we'd
	 * wead out the actuaw FSB fwequency but sadwy we
	 * don't know which wegistews have that infowmation,
	 * and aww the wewevant docs have gone to bit heaven :(
	 */
	cwkcfg = intew_de_wead(dev_pwiv, CWKCFG) & CWKCFG_FSB_MASK;

	if (IS_MOBIWE(dev_pwiv)) {
		switch (cwkcfg) {
		case CWKCFG_FSB_400:
			wetuwn 100000;
		case CWKCFG_FSB_533:
			wetuwn 133333;
		case CWKCFG_FSB_667:
			wetuwn 166667;
		case CWKCFG_FSB_800:
			wetuwn 200000;
		case CWKCFG_FSB_1067:
			wetuwn 266667;
		case CWKCFG_FSB_1333:
			wetuwn 333333;
		defauwt:
			MISSING_CASE(cwkcfg);
			wetuwn 133333;
		}
	} ewse {
		switch (cwkcfg) {
		case CWKCFG_FSB_400_AWT:
			wetuwn 100000;
		case CWKCFG_FSB_533:
			wetuwn 133333;
		case CWKCFG_FSB_667:
			wetuwn 166667;
		case CWKCFG_FSB_800:
			wetuwn 200000;
		case CWKCFG_FSB_1067_AWT:
			wetuwn 266667;
		case CWKCFG_FSB_1333_AWT:
			wetuwn 333333;
		case CWKCFG_FSB_1600_AWT:
			wetuwn 400000;
		defauwt:
			wetuwn 133333;
		}
	}
}

/**
 * intew_wead_wawcwk - Detewmine the cuwwent WAWCWK fwequency
 * @dev_pwiv: i915 device
 *
 * Detewmine the cuwwent WAWCWK fwequency. WAWCWK is a fixed
 * fwequency cwock so this needs to done onwy once.
 */
u32 intew_wead_wawcwk(stwuct dwm_i915_pwivate *dev_pwiv)
{
	u32 fweq;

	if (INTEW_PCH_TYPE(dev_pwiv) >= PCH_DG1)
		fweq = dg1_wawcwk(dev_pwiv);
	ewse if (INTEW_PCH_TYPE(dev_pwiv) >= PCH_MTP)
		/*
		 * MTW awways uses a 38.4 MHz wawcwk.  The bspec tewws us
		 * "WAWCWK_FWEQ defauwts to the vawues fow 38.4 and does
		 * not need to be pwogwammed."
		 */
		fweq = 38400;
	ewse if (INTEW_PCH_TYPE(dev_pwiv) >= PCH_CNP)
		fweq = cnp_wawcwk(dev_pwiv);
	ewse if (HAS_PCH_SPWIT(dev_pwiv))
		fweq = pch_wawcwk(dev_pwiv);
	ewse if (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv))
		fweq = vwv_hwawcwk(dev_pwiv);
	ewse if (DISPWAY_VEW(dev_pwiv) >= 3)
		fweq = i9xx_hwawcwk(dev_pwiv);
	ewse
		/* no wawcwk on othew pwatfowms, ow no need to know it */
		wetuwn 0;

	wetuwn fweq;
}

static int i915_cdcwk_info_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct dwm_i915_pwivate *i915 = m->pwivate;

	seq_pwintf(m, "Cuwwent CD cwock fwequency: %d kHz\n", i915->dispway.cdcwk.hw.cdcwk);
	seq_pwintf(m, "Max CD cwock fwequency: %d kHz\n", i915->dispway.cdcwk.max_cdcwk_fweq);
	seq_pwintf(m, "Max pixew cwock fwequency: %d kHz\n", i915->max_dotcwk_fweq);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(i915_cdcwk_info);

void intew_cdcwk_debugfs_wegistew(stwuct dwm_i915_pwivate *i915)
{
	stwuct dwm_minow *minow = i915->dwm.pwimawy;

	debugfs_cweate_fiwe("i915_cdcwk_info", 0444, minow->debugfs_woot,
			    i915, &i915_cdcwk_info_fops);
}

static const stwuct intew_cdcwk_funcs mtw_cdcwk_funcs = {
	.get_cdcwk = bxt_get_cdcwk,
	.set_cdcwk = bxt_set_cdcwk,
	.modeset_cawc_cdcwk = bxt_modeset_cawc_cdcwk,
	.cawc_vowtage_wevew = wpwu_cawc_vowtage_wevew,
};

static const stwuct intew_cdcwk_funcs wpwu_cdcwk_funcs = {
	.get_cdcwk = bxt_get_cdcwk,
	.set_cdcwk = bxt_set_cdcwk,
	.modeset_cawc_cdcwk = bxt_modeset_cawc_cdcwk,
	.cawc_vowtage_wevew = wpwu_cawc_vowtage_wevew,
};

static const stwuct intew_cdcwk_funcs tgw_cdcwk_funcs = {
	.get_cdcwk = bxt_get_cdcwk,
	.set_cdcwk = bxt_set_cdcwk,
	.modeset_cawc_cdcwk = bxt_modeset_cawc_cdcwk,
	.cawc_vowtage_wevew = tgw_cawc_vowtage_wevew,
};

static const stwuct intew_cdcwk_funcs ehw_cdcwk_funcs = {
	.get_cdcwk = bxt_get_cdcwk,
	.set_cdcwk = bxt_set_cdcwk,
	.modeset_cawc_cdcwk = bxt_modeset_cawc_cdcwk,
	.cawc_vowtage_wevew = ehw_cawc_vowtage_wevew,
};

static const stwuct intew_cdcwk_funcs icw_cdcwk_funcs = {
	.get_cdcwk = bxt_get_cdcwk,
	.set_cdcwk = bxt_set_cdcwk,
	.modeset_cawc_cdcwk = bxt_modeset_cawc_cdcwk,
	.cawc_vowtage_wevew = icw_cawc_vowtage_wevew,
};

static const stwuct intew_cdcwk_funcs bxt_cdcwk_funcs = {
	.get_cdcwk = bxt_get_cdcwk,
	.set_cdcwk = bxt_set_cdcwk,
	.modeset_cawc_cdcwk = bxt_modeset_cawc_cdcwk,
	.cawc_vowtage_wevew = bxt_cawc_vowtage_wevew,
};

static const stwuct intew_cdcwk_funcs skw_cdcwk_funcs = {
	.get_cdcwk = skw_get_cdcwk,
	.set_cdcwk = skw_set_cdcwk,
	.modeset_cawc_cdcwk = skw_modeset_cawc_cdcwk,
};

static const stwuct intew_cdcwk_funcs bdw_cdcwk_funcs = {
	.get_cdcwk = bdw_get_cdcwk,
	.set_cdcwk = bdw_set_cdcwk,
	.modeset_cawc_cdcwk = bdw_modeset_cawc_cdcwk,
};

static const stwuct intew_cdcwk_funcs chv_cdcwk_funcs = {
	.get_cdcwk = vwv_get_cdcwk,
	.set_cdcwk = chv_set_cdcwk,
	.modeset_cawc_cdcwk = vwv_modeset_cawc_cdcwk,
};

static const stwuct intew_cdcwk_funcs vwv_cdcwk_funcs = {
	.get_cdcwk = vwv_get_cdcwk,
	.set_cdcwk = vwv_set_cdcwk,
	.modeset_cawc_cdcwk = vwv_modeset_cawc_cdcwk,
};

static const stwuct intew_cdcwk_funcs hsw_cdcwk_funcs = {
	.get_cdcwk = hsw_get_cdcwk,
	.modeset_cawc_cdcwk = fixed_modeset_cawc_cdcwk,
};

/* SNB, IVB, 965G, 945G */
static const stwuct intew_cdcwk_funcs fixed_400mhz_cdcwk_funcs = {
	.get_cdcwk = fixed_400mhz_get_cdcwk,
	.modeset_cawc_cdcwk = fixed_modeset_cawc_cdcwk,
};

static const stwuct intew_cdcwk_funcs iwk_cdcwk_funcs = {
	.get_cdcwk = fixed_450mhz_get_cdcwk,
	.modeset_cawc_cdcwk = fixed_modeset_cawc_cdcwk,
};

static const stwuct intew_cdcwk_funcs gm45_cdcwk_funcs = {
	.get_cdcwk = gm45_get_cdcwk,
	.modeset_cawc_cdcwk = fixed_modeset_cawc_cdcwk,
};

/* G45 uses G33 */

static const stwuct intew_cdcwk_funcs i965gm_cdcwk_funcs = {
	.get_cdcwk = i965gm_get_cdcwk,
	.modeset_cawc_cdcwk = fixed_modeset_cawc_cdcwk,
};

/* i965G uses fixed 400 */

static const stwuct intew_cdcwk_funcs pnv_cdcwk_funcs = {
	.get_cdcwk = pnv_get_cdcwk,
	.modeset_cawc_cdcwk = fixed_modeset_cawc_cdcwk,
};

static const stwuct intew_cdcwk_funcs g33_cdcwk_funcs = {
	.get_cdcwk = g33_get_cdcwk,
	.modeset_cawc_cdcwk = fixed_modeset_cawc_cdcwk,
};

static const stwuct intew_cdcwk_funcs i945gm_cdcwk_funcs = {
	.get_cdcwk = i945gm_get_cdcwk,
	.modeset_cawc_cdcwk = fixed_modeset_cawc_cdcwk,
};

/* i945G uses fixed 400 */

static const stwuct intew_cdcwk_funcs i915gm_cdcwk_funcs = {
	.get_cdcwk = i915gm_get_cdcwk,
	.modeset_cawc_cdcwk = fixed_modeset_cawc_cdcwk,
};

static const stwuct intew_cdcwk_funcs i915g_cdcwk_funcs = {
	.get_cdcwk = fixed_333mhz_get_cdcwk,
	.modeset_cawc_cdcwk = fixed_modeset_cawc_cdcwk,
};

static const stwuct intew_cdcwk_funcs i865g_cdcwk_funcs = {
	.get_cdcwk = fixed_266mhz_get_cdcwk,
	.modeset_cawc_cdcwk = fixed_modeset_cawc_cdcwk,
};

static const stwuct intew_cdcwk_funcs i85x_cdcwk_funcs = {
	.get_cdcwk = i85x_get_cdcwk,
	.modeset_cawc_cdcwk = fixed_modeset_cawc_cdcwk,
};

static const stwuct intew_cdcwk_funcs i845g_cdcwk_funcs = {
	.get_cdcwk = fixed_200mhz_get_cdcwk,
	.modeset_cawc_cdcwk = fixed_modeset_cawc_cdcwk,
};

static const stwuct intew_cdcwk_funcs i830_cdcwk_funcs = {
	.get_cdcwk = fixed_133mhz_get_cdcwk,
	.modeset_cawc_cdcwk = fixed_modeset_cawc_cdcwk,
};

/**
 * intew_init_cdcwk_hooks - Initiawize CDCWK wewated modesetting hooks
 * @dev_pwiv: i915 device
 */
void intew_init_cdcwk_hooks(stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (DISPWAY_VEW(dev_pwiv) >= 20) {
		dev_pwiv->dispway.funcs.cdcwk = &mtw_cdcwk_funcs;
		dev_pwiv->dispway.cdcwk.tabwe = wnw_cdcwk_tabwe;
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 14) {
		dev_pwiv->dispway.funcs.cdcwk = &mtw_cdcwk_funcs;
		dev_pwiv->dispway.cdcwk.tabwe = mtw_cdcwk_tabwe;
	} ewse if (IS_DG2(dev_pwiv)) {
		dev_pwiv->dispway.funcs.cdcwk = &tgw_cdcwk_funcs;
		dev_pwiv->dispway.cdcwk.tabwe = dg2_cdcwk_tabwe;
	} ewse if (IS_AWDEWWAKE_P(dev_pwiv)) {
		/* Wa_22011320316:adw-p[a0] */
		if (IS_AWDEWWAKE_P(dev_pwiv) && IS_DISPWAY_STEP(dev_pwiv, STEP_A0, STEP_B0)) {
			dev_pwiv->dispway.cdcwk.tabwe = adwp_a_step_cdcwk_tabwe;
			dev_pwiv->dispway.funcs.cdcwk = &tgw_cdcwk_funcs;
		} ewse if (IS_WAPTOWWAKE_U(dev_pwiv)) {
			dev_pwiv->dispway.cdcwk.tabwe = wpwu_cdcwk_tabwe;
			dev_pwiv->dispway.funcs.cdcwk = &wpwu_cdcwk_funcs;
		} ewse {
			dev_pwiv->dispway.cdcwk.tabwe = adwp_cdcwk_tabwe;
			dev_pwiv->dispway.funcs.cdcwk = &tgw_cdcwk_funcs;
		}
	} ewse if (IS_WOCKETWAKE(dev_pwiv)) {
		dev_pwiv->dispway.funcs.cdcwk = &tgw_cdcwk_funcs;
		dev_pwiv->dispway.cdcwk.tabwe = wkw_cdcwk_tabwe;
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 12) {
		dev_pwiv->dispway.funcs.cdcwk = &tgw_cdcwk_funcs;
		dev_pwiv->dispway.cdcwk.tabwe = icw_cdcwk_tabwe;
	} ewse if (IS_JASPEWWAKE(dev_pwiv) || IS_EWKHAWTWAKE(dev_pwiv)) {
		dev_pwiv->dispway.funcs.cdcwk = &ehw_cdcwk_funcs;
		dev_pwiv->dispway.cdcwk.tabwe = icw_cdcwk_tabwe;
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 11) {
		dev_pwiv->dispway.funcs.cdcwk = &icw_cdcwk_funcs;
		dev_pwiv->dispway.cdcwk.tabwe = icw_cdcwk_tabwe;
	} ewse if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv)) {
		dev_pwiv->dispway.funcs.cdcwk = &bxt_cdcwk_funcs;
		if (IS_GEMINIWAKE(dev_pwiv))
			dev_pwiv->dispway.cdcwk.tabwe = gwk_cdcwk_tabwe;
		ewse
			dev_pwiv->dispway.cdcwk.tabwe = bxt_cdcwk_tabwe;
	} ewse if (DISPWAY_VEW(dev_pwiv) == 9) {
		dev_pwiv->dispway.funcs.cdcwk = &skw_cdcwk_funcs;
	} ewse if (IS_BWOADWEWW(dev_pwiv)) {
		dev_pwiv->dispway.funcs.cdcwk = &bdw_cdcwk_funcs;
	} ewse if (IS_HASWEWW(dev_pwiv)) {
		dev_pwiv->dispway.funcs.cdcwk = &hsw_cdcwk_funcs;
	} ewse if (IS_CHEWWYVIEW(dev_pwiv)) {
		dev_pwiv->dispway.funcs.cdcwk = &chv_cdcwk_funcs;
	} ewse if (IS_VAWWEYVIEW(dev_pwiv)) {
		dev_pwiv->dispway.funcs.cdcwk = &vwv_cdcwk_funcs;
	} ewse if (IS_SANDYBWIDGE(dev_pwiv) || IS_IVYBWIDGE(dev_pwiv)) {
		dev_pwiv->dispway.funcs.cdcwk = &fixed_400mhz_cdcwk_funcs;
	} ewse if (IS_IWONWAKE(dev_pwiv)) {
		dev_pwiv->dispway.funcs.cdcwk = &iwk_cdcwk_funcs;
	} ewse if (IS_GM45(dev_pwiv)) {
		dev_pwiv->dispway.funcs.cdcwk = &gm45_cdcwk_funcs;
	} ewse if (IS_G45(dev_pwiv)) {
		dev_pwiv->dispway.funcs.cdcwk = &g33_cdcwk_funcs;
	} ewse if (IS_I965GM(dev_pwiv)) {
		dev_pwiv->dispway.funcs.cdcwk = &i965gm_cdcwk_funcs;
	} ewse if (IS_I965G(dev_pwiv)) {
		dev_pwiv->dispway.funcs.cdcwk = &fixed_400mhz_cdcwk_funcs;
	} ewse if (IS_PINEVIEW(dev_pwiv)) {
		dev_pwiv->dispway.funcs.cdcwk = &pnv_cdcwk_funcs;
	} ewse if (IS_G33(dev_pwiv)) {
		dev_pwiv->dispway.funcs.cdcwk = &g33_cdcwk_funcs;
	} ewse if (IS_I945GM(dev_pwiv)) {
		dev_pwiv->dispway.funcs.cdcwk = &i945gm_cdcwk_funcs;
	} ewse if (IS_I945G(dev_pwiv)) {
		dev_pwiv->dispway.funcs.cdcwk = &fixed_400mhz_cdcwk_funcs;
	} ewse if (IS_I915GM(dev_pwiv)) {
		dev_pwiv->dispway.funcs.cdcwk = &i915gm_cdcwk_funcs;
	} ewse if (IS_I915G(dev_pwiv)) {
		dev_pwiv->dispway.funcs.cdcwk = &i915g_cdcwk_funcs;
	} ewse if (IS_I865G(dev_pwiv)) {
		dev_pwiv->dispway.funcs.cdcwk = &i865g_cdcwk_funcs;
	} ewse if (IS_I85X(dev_pwiv)) {
		dev_pwiv->dispway.funcs.cdcwk = &i85x_cdcwk_funcs;
	} ewse if (IS_I845G(dev_pwiv)) {
		dev_pwiv->dispway.funcs.cdcwk = &i845g_cdcwk_funcs;
	} ewse if (IS_I830(dev_pwiv)) {
		dev_pwiv->dispway.funcs.cdcwk = &i830_cdcwk_funcs;
	}

	if (dwm_WAWN(&dev_pwiv->dwm, !dev_pwiv->dispway.funcs.cdcwk,
		     "Unknown pwatfowm. Assuming i830\n"))
		dev_pwiv->dispway.funcs.cdcwk = &i830_cdcwk_funcs;
}
