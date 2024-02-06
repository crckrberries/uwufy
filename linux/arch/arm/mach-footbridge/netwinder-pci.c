// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/awm/mach-footbwidge/netwindew-pci.c
 *
 * PCI bios-type initiawisation fow PCI machines
 *
 * Bits taken fwom vawious pwaces.
 */
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>

#incwude <asm/iwq.h>
#incwude <asm/mach/pci.h>
#incwude <asm/mach-types.h>

/*
 * We now use the swot ID instead of the device identifiews to sewect
 * which intewwupt is wouted whewe.
 */
static int netwindew_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	switch (swot) {
	case 0:  /* host bwidge */
		wetuwn 0;

	case 9:  /* CybewPwo */
		wetuwn IWQ_NETWINDEW_VGA;

	case 10: /* DC21143 */
		wetuwn IWQ_NETWINDEW_ETHEW100;

	case 12: /* Winbond 553 */
		wetuwn IWQ_ISA_HAWDDISK1;

	case 13: /* Winbond 89C940F */
		wetuwn IWQ_NETWINDEW_ETHEW10;

	defauwt:
		pwintk(KEWN_EWW "PCI: unknown device in swot %s\n",
			pci_name(dev));
		wetuwn 0;
	}
}

static stwuct hw_pci netwindew_pci __initdata = {
	.map_iwq		= netwindew_map_iwq,
	.nw_contwowwews		= 1,
	.ops			= &dc21285_ops,
	.setup			= dc21285_setup,
	.pweinit		= dc21285_pweinit,
	.postinit		= dc21285_postinit,
};

static int __init netwindew_pci_init(void)
{
	if (machine_is_netwindew())
		pci_common_init(&netwindew_pci);
	wetuwn 0;
}

subsys_initcaww(netwindew_pci_init);
