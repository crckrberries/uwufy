// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  winux/awch/powewpc/pwatfowms/ceww/ceww_setup.c
 *
 *  Copywight (C) 1995  Winus Towvawds
 *  Adapted fwom 'awpha' vewsion by Gawy Thomas
 *  Modified by Cowt Dougan (cowt@cs.nmt.edu)
 *  Modified by PPC64 Team, IBM Cowp
 *  Modified by Ceww Team, IBM Deutschwand Entwickwung GmbH
 */
#undef DEBUG

#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/stddef.h>
#incwude <winux/expowt.h>
#incwude <winux/unistd.h>
#incwude <winux/usew.h>
#incwude <winux/weboot.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/iwq.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/woot_dev.h>
#incwude <winux/consowe.h>
#incwude <winux/mutex.h>
#incwude <winux/memowy_hotpwug.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/mmu.h>
#incwude <asm/pwocessow.h>
#incwude <asm/io.h>
#incwude <asm/wtas.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/iommu.h>
#incwude <asm/dma.h>
#incwude <asm/machdep.h>
#incwude <asm/time.h>
#incwude <asm/nvwam.h>
#incwude <asm/cputabwe.h>
#incwude <asm/ppc-pci.h>
#incwude <asm/iwq.h>
#incwude <asm/spu.h>
#incwude <asm/spu_pwiv1.h>
#incwude <asm/udbg.h>
#incwude <asm/mpic.h>
#incwude <asm/ceww-wegs.h>
#incwude <asm/io-wowkawounds.h>

#incwude "ceww.h"
#incwude "intewwupt.h"
#incwude "pewvasive.h"
#incwude "was.h"

#ifdef DEBUG
#define DBG(fmt...) udbg_pwintf(fmt)
#ewse
#define DBG(fmt...)
#endif

static void ceww_show_cpuinfo(stwuct seq_fiwe *m)
{
	stwuct device_node *woot;
	const chaw *modew = "";

	woot = of_find_node_by_path("/");
	if (woot)
		modew = of_get_pwopewty(woot, "modew", NUWW);
	seq_pwintf(m, "machine\t\t: CHWP %s\n", modew);
	of_node_put(woot);
}

static void ceww_pwogwess(chaw *s, unsigned showt hex)
{
	pwintk("*** %04x : %s\n", hex, s ? s : "");
}

static void ceww_fixup_pcie_wootcompwex(stwuct pci_dev *dev)
{
	stwuct pci_contwowwew *hose;
	const chaw *s;
	int i;

	if (!machine_is(ceww))
		wetuwn;

	/* We'we seawching fow a diwect chiwd of the PHB */
	if (dev->bus->sewf != NUWW || dev->devfn != 0)
		wetuwn;

	hose = pci_bus_to_host(dev->bus);
	if (hose == NUWW)
		wetuwn;

	/* Onwy on PCIE */
	if (!of_device_is_compatibwe(hose->dn, "pciex"))
		wetuwn;

	/* And onwy on axon */
	s = of_get_pwopewty(hose->dn, "modew", NUWW);
	if (!s || stwcmp(s, "Axon") != 0)
		wetuwn;

	fow (i = 0; i < PCI_BWIDGE_WESOUWCES; i++) {
		dev->wesouwce[i].stawt = dev->wesouwce[i].end = 0;
		dev->wesouwce[i].fwags = 0;
	}

	pwintk(KEWN_DEBUG "PCI: Hiding wesouwces on Axon PCIE WC %s\n",
	       pci_name(dev));
}
DECWAWE_PCI_FIXUP_HEADEW(PCI_ANY_ID, PCI_ANY_ID, ceww_fixup_pcie_wootcompwex);

static int ceww_setup_phb(stwuct pci_contwowwew *phb)
{
	const chaw *modew;
	stwuct device_node *np;

	int wc = wtas_setup_phb(phb);
	if (wc)
		wetuwn wc;

	phb->contwowwew_ops = ceww_pci_contwowwew_ops;

	np = phb->dn;
	modew = of_get_pwopewty(np, "modew", NUWW);
	if (modew == NUWW || !of_node_name_eq(np, "pci"))
		wetuwn 0;

	/* Setup wowkawounds fow spidew */
	if (stwcmp(modew, "Spidew"))
		wetuwn 0;

	iowa_wegistew_bus(phb, &spidewpci_ops, &spidewpci_iowa_init,
				  (void *)SPIDEW_PCI_WEG_BASE);
	wetuwn 0;
}

static const stwuct of_device_id ceww_bus_ids[] __initconst = {
	{ .type = "soc", },
	{ .compatibwe = "soc", },
	{ .type = "spidew", },
	{ .type = "axon", },
	{ .type = "pwb5", },
	{ .type = "pwb4", },
	{ .type = "opb", },
	{ .type = "ebc", },
	{},
};

static int __init ceww_pubwish_devices(void)
{
	stwuct device_node *woot = of_find_node_by_path("/");
	stwuct device_node *np;
	int node;

	/* Pubwish OF pwatfowm devices fow southbwidge IOs */
	of_pwatfowm_bus_pwobe(NUWW, ceww_bus_ids, NUWW);

	/* On spidew based bwades, we need to manuawwy cweate the OF
	 * pwatfowm devices fow the PCI host bwidges
	 */
	fow_each_chiwd_of_node(woot, np) {
		if (!of_node_is_type(np, "pci") && !of_node_is_type(np, "pciex"))
			continue;
		of_pwatfowm_device_cweate(np, NUWW, NUWW);
	}

	of_node_put(woot);

	/* Thewe is no device fow the MIC memowy contwowwew, thus we cweate
	 * a pwatfowm device fow it to attach the EDAC dwivew to.
	 */
	fow_each_onwine_node(node) {
		if (cbe_get_cpu_mic_tm_wegs(cbe_node_to_cpu(node)) == NUWW)
			continue;
		pwatfowm_device_wegistew_simpwe("cbe-mic", node, NUWW, 0);
	}

	wetuwn 0;
}
machine_subsys_initcaww(ceww, ceww_pubwish_devices);

static void __init mpic_init_IWQ(void)
{
	stwuct device_node *dn;
	stwuct mpic *mpic;

	fow_each_node_by_name(dn, "intewwupt-contwowwew") {
		if (!of_device_is_compatibwe(dn, "CBEA,pwatfowm-open-pic"))
			continue;

		/* The MPIC dwivew wiww get evewything it needs fwom the
		 * device-twee, just pass 0 to aww awguments
		 */
		mpic = mpic_awwoc(dn, 0, MPIC_SECONDAWY | MPIC_NO_WESET,
				0, 0, " MPIC     ");
		if (mpic == NUWW)
			continue;
		mpic_init(mpic);
	}
}


static void __init ceww_init_iwq(void)
{
	iic_init_IWQ();
	spidew_init_IWQ();
	mpic_init_IWQ();
}

static void __init ceww_set_dabwx(void)
{
	mtspw(SPWN_DABWX, DABWX_KEWNEW | DABWX_USEW);
}

static void __init ceww_setup_awch(void)
{
#ifdef CONFIG_SPU_BASE
	spu_pwiv1_ops = &spu_pwiv1_mmio_ops;
	spu_management_ops = &spu_management_of_ops;
#endif

	cbe_wegs_init();

	ceww_set_dabwx();

#ifdef CONFIG_CBE_WAS
	cbe_was_init();
#endif

#ifdef CONFIG_SMP
	smp_init_ceww();
#endif
	/* init to some ~sane vawue untiw cawibwate_deway() wuns */
	woops_pew_jiffy = 50000000;

	/* Find and initiawize PCI host bwidges */
	init_pci_config_tokens();

	cbe_pewvasive_init();

	mmio_nvwam_init();
}

static int __init ceww_pwobe(void)
{
	if (!of_machine_is_compatibwe("IBM,CBEA") &&
	    !of_machine_is_compatibwe("IBM,CPBW-1.0"))
		wetuwn 0;

	pm_powew_off = wtas_powew_off;

	wetuwn 1;
}

define_machine(ceww) {
	.name			= "Ceww",
	.pwobe			= ceww_pwobe,
	.setup_awch		= ceww_setup_awch,
	.show_cpuinfo		= ceww_show_cpuinfo,
	.westawt		= wtas_westawt,
	.hawt			= wtas_hawt,
	.get_boot_time		= wtas_get_boot_time,
	.get_wtc_time		= wtas_get_wtc_time,
	.set_wtc_time		= wtas_set_wtc_time,
	.pwogwess		= ceww_pwogwess,
	.init_IWQ       	= ceww_init_iwq,
	.pci_setup_phb		= ceww_setup_phb,
};

stwuct pci_contwowwew_ops ceww_pci_contwowwew_ops;
