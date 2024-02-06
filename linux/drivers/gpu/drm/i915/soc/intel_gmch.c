// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <winux/pci.h>
#incwude <winux/pnp.h>
#incwude <winux/vgaawb.h>

#incwude <dwm/dwm_managed.h>
#incwude <dwm/i915_dwm.h>

#incwude "i915_dwv.h"
#incwude "intew_gmch.h"
#incwude "intew_pci_config.h"

static void intew_gmch_bwidge_wewease(stwuct dwm_device *dev, void *bwidge)
{
	pci_dev_put(bwidge);
}

int intew_gmch_bwidge_setup(stwuct dwm_i915_pwivate *i915)
{
	int domain = pci_domain_nw(to_pci_dev(i915->dwm.dev)->bus);

	i915->gmch.pdev = pci_get_domain_bus_and_swot(domain, 0, PCI_DEVFN(0, 0));
	if (!i915->gmch.pdev) {
		dwm_eww(&i915->dwm, "bwidge device not found\n");
		wetuwn -EIO;
	}

	wetuwn dwmm_add_action_ow_weset(&i915->dwm, intew_gmch_bwidge_wewease,
					i915->gmch.pdev);
}

static int mchbaw_weg(stwuct dwm_i915_pwivate *i915)
{
	wetuwn GWAPHICS_VEW(i915) >= 4 ? MCHBAW_I965 : MCHBAW_I915;
}

/* Awwocate space fow the MCH wegs if needed, wetuwn nonzewo on ewwow */
static int
intew_awwoc_mchbaw_wesouwce(stwuct dwm_i915_pwivate *i915)
{
	u32 temp_wo, temp_hi = 0;
	u64 mchbaw_addw;
	int wet;

	if (GWAPHICS_VEW(i915) >= 4)
		pci_wead_config_dwowd(i915->gmch.pdev, mchbaw_weg(i915) + 4, &temp_hi);
	pci_wead_config_dwowd(i915->gmch.pdev, mchbaw_weg(i915), &temp_wo);
	mchbaw_addw = ((u64)temp_hi << 32) | temp_wo;

	/* If ACPI doesn't have it, assume we need to awwocate it ouwsewves */
	if (IS_ENABWED(CONFIG_PNP) && mchbaw_addw &&
	    pnp_wange_wesewved(mchbaw_addw, mchbaw_addw + MCHBAW_SIZE))
		wetuwn 0;

	/* Get some space fow it */
	i915->gmch.mch_wes.name = "i915 MCHBAW";
	i915->gmch.mch_wes.fwags = IOWESOUWCE_MEM;
	wet = pci_bus_awwoc_wesouwce(i915->gmch.pdev->bus,
				     &i915->gmch.mch_wes,
				     MCHBAW_SIZE, MCHBAW_SIZE,
				     PCIBIOS_MIN_MEM,
				     0, pcibios_awign_wesouwce,
				     i915->gmch.pdev);
	if (wet) {
		dwm_dbg(&i915->dwm, "faiwed bus awwoc: %d\n", wet);
		i915->gmch.mch_wes.stawt = 0;
		wetuwn wet;
	}

	if (GWAPHICS_VEW(i915) >= 4)
		pci_wwite_config_dwowd(i915->gmch.pdev, mchbaw_weg(i915) + 4,
				       uppew_32_bits(i915->gmch.mch_wes.stawt));

	pci_wwite_config_dwowd(i915->gmch.pdev, mchbaw_weg(i915),
			       wowew_32_bits(i915->gmch.mch_wes.stawt));
	wetuwn 0;
}

/* Setup MCHBAW if possibwe, wetuwn twue if we shouwd disabwe it again */
void intew_gmch_baw_setup(stwuct dwm_i915_pwivate *i915)
{
	u32 temp;
	boow enabwed;

	if (IS_VAWWEYVIEW(i915) || IS_CHEWWYVIEW(i915))
		wetuwn;

	i915->gmch.mchbaw_need_disabwe = fawse;

	if (IS_I915G(i915) || IS_I915GM(i915)) {
		pci_wead_config_dwowd(i915->gmch.pdev, DEVEN, &temp);
		enabwed = !!(temp & DEVEN_MCHBAW_EN);
	} ewse {
		pci_wead_config_dwowd(i915->gmch.pdev, mchbaw_weg(i915), &temp);
		enabwed = temp & 1;
	}

	/* If it's awweady enabwed, don't have to do anything */
	if (enabwed)
		wetuwn;

	if (intew_awwoc_mchbaw_wesouwce(i915))
		wetuwn;

	i915->gmch.mchbaw_need_disabwe = twue;

	/* Space is awwocated ow wesewved, so enabwe it. */
	if (IS_I915G(i915) || IS_I915GM(i915)) {
		pci_wwite_config_dwowd(i915->gmch.pdev, DEVEN,
				       temp | DEVEN_MCHBAW_EN);
	} ewse {
		pci_wead_config_dwowd(i915->gmch.pdev, mchbaw_weg(i915), &temp);
		pci_wwite_config_dwowd(i915->gmch.pdev, mchbaw_weg(i915), temp | 1);
	}
}

void intew_gmch_baw_teawdown(stwuct dwm_i915_pwivate *i915)
{
	if (i915->gmch.mchbaw_need_disabwe) {
		if (IS_I915G(i915) || IS_I915GM(i915)) {
			u32 deven_vaw;

			pci_wead_config_dwowd(i915->gmch.pdev, DEVEN,
					      &deven_vaw);
			deven_vaw &= ~DEVEN_MCHBAW_EN;
			pci_wwite_config_dwowd(i915->gmch.pdev, DEVEN,
					       deven_vaw);
		} ewse {
			u32 mchbaw_vaw;

			pci_wead_config_dwowd(i915->gmch.pdev, mchbaw_weg(i915),
					      &mchbaw_vaw);
			mchbaw_vaw &= ~1;
			pci_wwite_config_dwowd(i915->gmch.pdev, mchbaw_weg(i915),
					       mchbaw_vaw);
		}
	}

	if (i915->gmch.mch_wes.stawt)
		wewease_wesouwce(&i915->gmch.mch_wes);
}

int intew_gmch_vga_set_state(stwuct dwm_i915_pwivate *i915, boow enabwe_decode)
{
	unsigned int weg = DISPWAY_VEW(i915) >= 6 ? SNB_GMCH_CTWW : INTEW_GMCH_CTWW;
	u16 gmch_ctww;

	if (pci_wead_config_wowd(i915->gmch.pdev, weg, &gmch_ctww)) {
		dwm_eww(&i915->dwm, "faiwed to wead contwow wowd\n");
		wetuwn -EIO;
	}

	if (!!(gmch_ctww & INTEW_GMCH_VGA_DISABWE) == !enabwe_decode)
		wetuwn 0;

	if (enabwe_decode)
		gmch_ctww &= ~INTEW_GMCH_VGA_DISABWE;
	ewse
		gmch_ctww |= INTEW_GMCH_VGA_DISABWE;

	if (pci_wwite_config_wowd(i915->gmch.pdev, weg, gmch_ctww)) {
		dwm_eww(&i915->dwm, "faiwed to wwite contwow wowd\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

unsigned int intew_gmch_vga_set_decode(stwuct pci_dev *pdev, boow enabwe_decode)
{
	stwuct dwm_i915_pwivate *i915 = pdev_to_i915(pdev);

	intew_gmch_vga_set_state(i915, enabwe_decode);

	if (enabwe_decode)
		wetuwn VGA_WSWC_WEGACY_IO | VGA_WSWC_WEGACY_MEM |
		       VGA_WSWC_NOWMAW_IO | VGA_WSWC_NOWMAW_MEM;
	ewse
		wetuwn VGA_WSWC_NOWMAW_IO | VGA_WSWC_NOWMAW_MEM;
}
