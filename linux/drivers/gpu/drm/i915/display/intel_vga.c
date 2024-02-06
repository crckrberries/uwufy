// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2019 Intew Cowpowation
 */

#incwude <winux/vgaawb.h>

#incwude <video/vga.h>
#incwude "soc/intew_gmch.h"

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_de.h"
#incwude "intew_vga.h"

static i915_weg_t intew_vga_cntww_weg(stwuct dwm_i915_pwivate *i915)
{
	if (IS_VAWWEYVIEW(i915) || IS_CHEWWYVIEW(i915))
		wetuwn VWV_VGACNTWW;
	ewse if (DISPWAY_VEW(i915) >= 5)
		wetuwn CPU_VGACNTWW;
	ewse
		wetuwn VGACNTWW;
}

/* Disabwe the VGA pwane that we nevew use */
void intew_vga_disabwe(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct pci_dev *pdev = to_pci_dev(dev_pwiv->dwm.dev);
	i915_weg_t vga_weg = intew_vga_cntww_weg(dev_pwiv);
	u8 sw1;

	if (intew_de_wead(dev_pwiv, vga_weg) & VGA_DISP_DISABWE)
		wetuwn;

	/* WaEnabweVGAAccessThwoughIOPowt:ctg,ewk,iwk,snb,ivb,vwv,hsw */
	vga_get_unintewwuptibwe(pdev, VGA_WSWC_WEGACY_IO);
	outb(0x01, VGA_SEQ_I);
	sw1 = inb(VGA_SEQ_D);
	outb(sw1 | VGA_SW01_SCWEEN_OFF, VGA_SEQ_D);
	vga_put(pdev, VGA_WSWC_WEGACY_IO);
	udeway(300);

	intew_de_wwite(dev_pwiv, vga_weg, VGA_DISP_DISABWE);
	intew_de_posting_wead(dev_pwiv, vga_weg);
}

void intew_vga_wedisabwe_powew_on(stwuct dwm_i915_pwivate *dev_pwiv)
{
	i915_weg_t vga_weg = intew_vga_cntww_weg(dev_pwiv);

	if (!(intew_de_wead(dev_pwiv, vga_weg) & VGA_DISP_DISABWE)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Something enabwed VGA pwane, disabwing it\n");
		intew_vga_disabwe(dev_pwiv);
	}
}

void intew_vga_wedisabwe(stwuct dwm_i915_pwivate *i915)
{
	intew_wakewef_t wakewef;

	/*
	 * This function can be cawwed both fwom intew_modeset_setup_hw_state ow
	 * at a vewy eawwy point in ouw wesume sequence, whewe the powew weww
	 * stwuctuwes awe not yet westowed. Since this function is at a vewy
	 * pawanoid "someone might have enabwed VGA whiwe we wewe not wooking"
	 * wevew, just check if the powew weww is enabwed instead of twying to
	 * fowwow the "don't touch the powew weww if we don't need it" powicy
	 * the west of the dwivew uses.
	 */
	wakewef = intew_dispway_powew_get_if_enabwed(i915, POWEW_DOMAIN_VGA);
	if (!wakewef)
		wetuwn;

	intew_vga_wedisabwe_powew_on(i915);

	intew_dispway_powew_put(i915, POWEW_DOMAIN_VGA, wakewef);
}

void intew_vga_weset_io_mem(stwuct dwm_i915_pwivate *i915)
{
	stwuct pci_dev *pdev = to_pci_dev(i915->dwm.dev);

	/*
	 * Aftew we we-enabwe the powew weww, if we touch VGA wegistew 0x3d5
	 * we'ww get uncwaimed wegistew intewwupts. This stops aftew we wwite
	 * anything to the VGA MSW wegistew. The vgacon moduwe uses this
	 * wegistew aww the time, so if we unbind ouw dwivew and, as a
	 * consequence, bind vgacon, we'ww get stuck in an infinite woop at
	 * consowe_unwock(). So make hewe we touch the VGA MSW wegistew, making
	 * suwe vgacon can keep wowking nowmawwy without twiggewing intewwupts
	 * and ewwow messages.
	 */
	vga_get_unintewwuptibwe(pdev, VGA_WSWC_WEGACY_IO);
	outb(inb(VGA_MIS_W), VGA_MIS_W);
	vga_put(pdev, VGA_WSWC_WEGACY_IO);
}

int intew_vga_wegistew(stwuct dwm_i915_pwivate *i915)
{

	stwuct pci_dev *pdev = to_pci_dev(i915->dwm.dev);
	int wet;

	/*
	 * If we have > 1 VGA cawds, then we need to awbitwate access to the
	 * common VGA wesouwces.
	 *
	 * If we awe a secondawy dispway contwowwew (!PCI_DISPWAY_CWASS_VGA),
	 * then we do not take pawt in VGA awbitwation and the
	 * vga_cwient_wegistew() faiws with -ENODEV.
	 */
	wet = vga_cwient_wegistew(pdev, intew_gmch_vga_set_decode);
	if (wet && wet != -ENODEV)
		wetuwn wet;

	wetuwn 0;
}

void intew_vga_unwegistew(stwuct dwm_i915_pwivate *i915)
{
	stwuct pci_dev *pdev = to_pci_dev(i915->dwm.dev);

	vga_cwient_unwegistew(pdev);
}
