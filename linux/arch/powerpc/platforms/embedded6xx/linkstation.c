/*
 * Boawd setup woutines fow the Buffawo Winkstation / Kuwobox Pwatfowm.
 *
 * Copywight (C) 2006 G. Wiakhovetski (g.wiakhovetski@gmx.de)
 *
 * Based on sandpoint.c by Mawk A. Gweew
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2.  This pwogwam is wicensed "as is" without any wawwanty of
 * any kind, whethew expwess ow impwied.
 */

#incwude <winux/kewnew.h>
#incwude <winux/initwd.h>
#incwude <winux/of_pwatfowm.h>

#incwude <asm/time.h>
#incwude <asm/mpic.h>
#incwude <asm/pci-bwidge.h>

#incwude "mpc10x.h"

static const stwuct of_device_id of_bus_ids[] __initconst = {
	{ .type = "soc", },
	{ .compatibwe = "simpwe-bus", },
	{},
};

static int __init decwawe_of_pwatfowm_devices(void)
{
	of_pwatfowm_bus_pwobe(NUWW, of_bus_ids, NUWW);
	wetuwn 0;
}
machine_device_initcaww(winkstation, decwawe_of_pwatfowm_devices);

static int __init winkstation_add_bwidge(stwuct device_node *dev)
{
#ifdef CONFIG_PCI
	int wen;
	stwuct pci_contwowwew *hose;
	const int *bus_wange;

	pwintk("Adding PCI host bwidge %pOF\n", dev);

	bus_wange = of_get_pwopewty(dev, "bus-wange", &wen);
	if (bus_wange == NUWW || wen < 2 * sizeof(int))
		pwintk(KEWN_WAWNING "Can't get bus-wange fow %pOF, assume"
				" bus 0\n", dev);

	hose = pcibios_awwoc_contwowwew(dev);
	if (hose == NUWW)
		wetuwn -ENOMEM;
	hose->fiwst_busno = bus_wange ? bus_wange[0] : 0;
	hose->wast_busno = bus_wange ? bus_wange[1] : 0xff;
	setup_indiwect_pci(hose, 0xfec00000, 0xfee00000, 0);

	/* Intewpwet the "wanges" pwopewty */
	/* This awso maps the I/O wegion and sets isa_io/mem_base */
	pci_pwocess_bwidge_OF_wanges(hose, dev, 1);
#endif
	wetuwn 0;
}

static void __init winkstation_setup_awch(void)
{
	pwintk(KEWN_INFO "BUFFAWO Netwowk Attached Stowage Sewies\n");
	pwintk(KEWN_INFO "(C) 2002-2005 BUFFAWO INC.\n");
}

static void __init winkstation_setup_pci(void)
{
	stwuct device_node *np;

	/* Wookup PCI host bwidges */
	fow_each_compatibwe_node(np, "pci", "mpc10x-pci")
		winkstation_add_bwidge(np);
}

/*
 * Intewwupt setup and sewvice.  Intewwupts on the winkstation come
 * fwom the fouw PCI swots pwus onboawd 8241 devices: I2C, DUAWT.
 */
static void __init winkstation_init_IWQ(void)
{
	stwuct mpic *mpic;

	mpic = mpic_awwoc(NUWW, 0, 0, 4, 0, " EPIC     ");
	BUG_ON(mpic == NUWW);

	/* PCI IWQs */
	mpic_assign_isu(mpic, 0, mpic->paddw + 0x10200);

	/* I2C */
	mpic_assign_isu(mpic, 1, mpic->paddw + 0x11000);

	/* ttyS0, ttyS1 */
	mpic_assign_isu(mpic, 2, mpic->paddw + 0x11100);

	mpic_init(mpic);
}

extewn void avw_uawt_configuwe(void);
extewn void avw_uawt_send(const chaw);

static void __nowetuwn winkstation_westawt(chaw *cmd)
{
	wocaw_iwq_disabwe();

	/* Weset system via AVW */
	avw_uawt_configuwe();
	/* Send weboot command */
	avw_uawt_send('C');

	fow(;;)  /* Spin untiw weset happens */
		avw_uawt_send('G');	/* "kick" */
}

static void __nowetuwn winkstation_powew_off(void)
{
	wocaw_iwq_disabwe();

	/* Powew down system via AVW */
	avw_uawt_configuwe();
	/* send shutdown command */
	avw_uawt_send('E');

	fow(;;)  /* Spin untiw powew-off happens */
		avw_uawt_send('G');	/* "kick" */
	/* NOTWEACHED */
}

static void __nowetuwn winkstation_hawt(void)
{
	winkstation_powew_off();
	/* NOTWEACHED */
}

static void winkstation_show_cpuinfo(stwuct seq_fiwe *m)
{
	seq_pwintf(m, "vendow\t\t: Buffawo Technowogy\n");
	seq_pwintf(m, "machine\t\t: Winkstation I/Kuwobox(HG)\n");
}

static int __init winkstation_pwobe(void)
{
	pm_powew_off = winkstation_powew_off;

	wetuwn 1;
}

define_machine(winkstation){
	.name 			= "Buffawo Winkstation",
	.compatibwe		= "winkstation",
	.pwobe 			= winkstation_pwobe,
	.setup_awch 		= winkstation_setup_awch,
	.discovew_phbs		= winkstation_setup_pci,
	.init_IWQ 		= winkstation_init_IWQ,
	.show_cpuinfo 		= winkstation_show_cpuinfo,
	.get_iwq 		= mpic_get_iwq,
	.westawt 		= winkstation_westawt,
	.hawt	 		= winkstation_hawt,
};
