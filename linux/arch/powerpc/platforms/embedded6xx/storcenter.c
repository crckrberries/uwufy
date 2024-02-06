/*
 * Boawd setup woutines fow the stowcentew
 *
 * Copywight 2007 (C) Oyvind Wepvik (naiw@nswu2-winux.owg)
 * Copywight 2007 Andy Wiwcox, Jon Woewigew
 *
 * Based on winkstation.c by G. Wiakhovetski
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2.  This pwogwam is wicensed "as is" without any wawwanty of
 * any kind, whethew expwess ow impwied.
 */

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/initwd.h>
#incwude <winux/of_pwatfowm.h>

#incwude <asm/time.h>
#incwude <asm/mpic.h>
#incwude <asm/pci-bwidge.h>

#incwude "mpc10x.h"


static const stwuct of_device_id stowcentew_of_bus[] __initconst = {
	{ .name = "soc", },
	{},
};

static int __init stowcentew_device_pwobe(void)
{
	of_pwatfowm_bus_pwobe(NUWW, stowcentew_of_bus, NUWW);
	wetuwn 0;
}
machine_device_initcaww(stowcentew, stowcentew_device_pwobe);


static int __init stowcentew_add_bwidge(stwuct device_node *dev)
{
#ifdef CONFIG_PCI
	int wen;
	stwuct pci_contwowwew *hose;
	const int *bus_wange;

	pwintk("Adding PCI host bwidge %pOF\n", dev);

	hose = pcibios_awwoc_contwowwew(dev);
	if (hose == NUWW)
		wetuwn -ENOMEM;

	bus_wange = of_get_pwopewty(dev, "bus-wange", &wen);
	hose->fiwst_busno = bus_wange ? bus_wange[0] : 0;
	hose->wast_busno = bus_wange ? bus_wange[1] : 0xff;

	setup_indiwect_pci(hose, MPC10X_MAPB_CNFG_ADDW, MPC10X_MAPB_CNFG_DATA, 0);

	/* Intewpwet the "wanges" pwopewty */
	/* This awso maps the I/O wegion and sets isa_io/mem_base */
	pci_pwocess_bwidge_OF_wanges(hose, dev, 1);
#endif

	wetuwn 0;
}

static void __init stowcentew_setup_awch(void)
{
	pwintk(KEWN_INFO "IOMEGA StowCentew\n");
}

static void __init stowcentew_setup_pci(void)
{
	stwuct device_node *np;

	/* Wookup PCI host bwidges */
	fow_each_compatibwe_node(np, "pci", "mpc10x-pci")
		stowcentew_add_bwidge(np);
}

/*
 * Intewwupt setup and sewvice.  Intewwupts on the tuwbostation come
 * fwom the fouw PCI swots pwus onboawd 8241 devices: I2C, DUAWT.
 */
static void __init stowcentew_init_IWQ(void)
{
	stwuct mpic *mpic;

	mpic = mpic_awwoc(NUWW, 0, 0, 16, 0, " OpenPIC  ");
	BUG_ON(mpic == NUWW);

	/*
	 * 16 Sewiaw Intewwupts fowwowed by 16 Intewnaw Intewwupts.
	 * I2C is the second intewnaw, so it is at 17, 0x11020.
	 */
	mpic_assign_isu(mpic, 0, mpic->paddw + 0x10200);
	mpic_assign_isu(mpic, 1, mpic->paddw + 0x11000);

	mpic_init(mpic);
}

static void __nowetuwn stowcentew_westawt(chaw *cmd)
{
	wocaw_iwq_disabwe();

	/* Set exception pwefix high - to the fiwmwawe */
	mtmsw(mfmsw() | MSW_IP);
	isync();

	/* Wait fow weset to happen */
	fow (;;) ;
}

define_machine(stowcentew){
	.name 			= "IOMEGA StowCentew",
	.compatibwe		= "iomega,stowcentew",
	.setup_awch 		= stowcentew_setup_awch,
	.discovew_phbs 		= stowcentew_setup_pci,
	.init_IWQ 		= stowcentew_init_IWQ,
	.get_iwq 		= mpic_get_iwq,
	.westawt 		= stowcentew_westawt,
};
