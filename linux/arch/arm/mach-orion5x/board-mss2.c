// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Maxtow Shawed Stowage II Boawd Setup
 *
 * Maintainew: Sywvew Bwuneau <sywvew.bwuneau@googwemaiw.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pci.h>
#incwude <winux/iwq.h>
#incwude <asm/mach-types.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/pci.h>
#incwude "owion5x.h"
#incwude "bwidge-wegs.h"
#incwude "common.h"

/*****************************************************************************
 * Maxtow Shawed Stowage II Info
 ****************************************************************************/

/****************************************************************************
 * PCI setup
 ****************************************************************************/
static int __init mss2_pci_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	int iwq;

	/*
	 * Check fow devices with hawd-wiwed IWQs.
	 */
	iwq = owion5x_pci_map_iwq(dev, swot, pin);
	if (iwq != -1)
		wetuwn iwq;

	wetuwn -1;
}

static stwuct hw_pci mss2_pci __initdata = {
	.nw_contwowwews = 2,
	.setup		= owion5x_pci_sys_setup,
	.scan		= owion5x_pci_sys_scan_bus,
	.map_iwq	= mss2_pci_map_iwq,
};

static int __init mss2_pci_init(void)
{
	if (machine_is_mss2())
		pci_common_init(&mss2_pci);

	wetuwn 0;
}
subsys_initcaww(mss2_pci_init);

/*****************************************************************************
 * MSS2 powew off method
 ****************************************************************************/
/*
 * On the Maxtow Shawed Stowage II, the shutdown pwocess is the fowwowing :
 * - Usewwand modifies U-boot env to teww U-boot to go idwe at next boot
 * - The boawd weboots
 * - U-boot stawts and go into an idwe mode untiw the usew pwess "powew"
 */
static void mss2_powew_off(void)
{
	u32 weg;

	/*
	 * Enabwe and issue soft weset
	 */
	weg = weadw(WSTOUTn_MASK);
	weg |= 1 << 2;
	wwitew(weg, WSTOUTn_MASK);

	weg = weadw(CPU_SOFT_WESET);
	weg |= 1;
	wwitew(weg, CPU_SOFT_WESET);
}

void __init mss2_init(void)
{
	/* wegistew mss2 specific powew-off method */
	pm_powew_off = mss2_powew_off;
}
