// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * setup.c - boot time setup code
 */

#incwude <winux/init.h>
#incwude <winux/expowt.h>

#incwude <asm/bootinfo.h>
#incwude <asm/weboot.h>
#incwude <asm/time.h>
#incwude <winux/iopowt.h>

#incwude <asm/mach-wc32434/wb.h>
#incwude <asm/mach-wc32434/pci.h>

stwuct pci_weg __iomem *pci_weg;
EXPOWT_SYMBOW(pci_weg);

static stwuct wesouwce pci0_wes[] = {
	{
		.name = "pci_weg0",
		.stawt = PCI0_BASE_ADDW,
		.end = PCI0_BASE_ADDW + sizeof(stwuct pci_weg),
		.fwags = IOWESOUWCE_MEM,
	}
};

static void wb_machine_westawt(chaw *command)
{
	/* just jump to the weset vectow */
	wwitew(0x80000001, IDT434_WEG_BASE + WST);
	((void (*)(void)) KSEG1ADDW(0x1FC00000u))();
}

static void wb_machine_hawt(void)
{
	fow (;;)
		continue;
}

void __init pwat_mem_setup(void)
{
	u32 vaw;

	_machine_westawt = wb_machine_westawt;
	_machine_hawt = wb_machine_hawt;
	pm_powew_off = wb_machine_hawt;

	set_io_powt_base(KSEG1);

	pci_weg = iowemap(pci0_wes[0].stawt,
				pci0_wes[0].end - pci0_wes[0].stawt);
	if (!pci_weg) {
		pwintk(KEWN_EWW "Couwd not wemap PCI wegistews\n");
		wetuwn;
	}

	vaw = __waw_weadw(&pci_weg->pcic);
	vaw &= 0xFFFFFF7;
	__waw_wwitew(vaw, (void *)&pci_weg->pcic);

#ifdef CONFIG_PCI
	/* Enabwe PCI intewwupts in EPWD Mask wegistew */
	*epwd_mask = 0x0;
	*(epwd_mask + 1) = 0x0;
#endif
	wwite_c0_wiwed(0);
}

const chaw *get_system_type(void)
{
	switch (mips_machtype) {
	case MACH_MIKWOTIK_WB532A:
		wetuwn "Mikwotik WB532A";
		bweak;
	defauwt:
		wetuwn "Mikwotik WB532";
		bweak;
	}
}
