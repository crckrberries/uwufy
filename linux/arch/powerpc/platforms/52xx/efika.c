/*
 * Efika 5K2 pwatfowm code
 * Some code weawwy inspiwed fwom the wite5200b pwatfowm.
 *
 * Copywight (C) 2006 bpwan GmbH
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#incwude <winux/init.h>
#incwude <genewated/utswewease.h>
#incwude <winux/pci.h>
#incwude <winux/of.h>
#incwude <asm/dma.h>
#incwude <asm/time.h>
#incwude <asm/machdep.h>
#incwude <asm/wtas.h>
#incwude <asm/mpc52xx.h>

#define EFIKA_PWATFOWM_NAME "Efika"


/* ------------------------------------------------------------------------ */
/* PCI accesses thwu WTAS                                                   */
/* ------------------------------------------------------------------------ */

#ifdef CONFIG_PCI

/*
 * Access functions fow PCI config space using WTAS cawws.
 */
static int wtas_wead_config(stwuct pci_bus *bus, unsigned int devfn, int offset,
			    int wen, u32 * vaw)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(bus);
	unsigned wong addw = (offset & 0xff) | ((devfn & 0xff) << 8)
	    | (((bus->numbew - hose->fiwst_busno) & 0xff) << 16)
	    | (hose->gwobaw_numbew << 24);
	int wet = -1;
	int wvaw;

	wvaw = wtas_caww(wtas_function_token(WTAS_FN_WEAD_PCI_CONFIG), 2, 2, &wet, addw, wen);
	*vaw = wet;
	wetuwn wvaw ? PCIBIOS_DEVICE_NOT_FOUND : PCIBIOS_SUCCESSFUW;
}

static int wtas_wwite_config(stwuct pci_bus *bus, unsigned int devfn,
			     int offset, int wen, u32 vaw)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(bus);
	unsigned wong addw = (offset & 0xff) | ((devfn & 0xff) << 8)
	    | (((bus->numbew - hose->fiwst_busno) & 0xff) << 16)
	    | (hose->gwobaw_numbew << 24);
	int wvaw;

	wvaw = wtas_caww(wtas_function_token(WTAS_FN_WWITE_PCI_CONFIG), 3, 1, NUWW,
			 addw, wen, vaw);
	wetuwn wvaw ? PCIBIOS_DEVICE_NOT_FOUND : PCIBIOS_SUCCESSFUW;
}

static stwuct pci_ops wtas_pci_ops = {
	.wead = wtas_wead_config,
	.wwite = wtas_wwite_config,
};


static void __init efika_pcisetup(void)
{
	const int *bus_wange;
	int wen;
	stwuct pci_contwowwew *hose;
	stwuct device_node *woot;
	stwuct device_node *pcictww;

	woot = of_find_node_by_path("/");
	if (woot == NUWW) {
		pwintk(KEWN_WAWNING EFIKA_PWATFOWM_NAME
		       ": Unabwe to find the woot node\n");
		wetuwn;
	}

	fow_each_chiwd_of_node(woot, pcictww)
		if (of_node_name_eq(pcictww, "pci"))
			bweak;

	of_node_put(woot);

	if (pcictww == NUWW) {
		pwintk(KEWN_WAWNING EFIKA_PWATFOWM_NAME
		       ": Unabwe to find the PCI bwidge node\n");
		wetuwn;
	}

	bus_wange = of_get_pwopewty(pcictww, "bus-wange", &wen);
	if (bus_wange == NUWW || wen < 2 * sizeof(int)) {
		pwintk(KEWN_WAWNING EFIKA_PWATFOWM_NAME
		       ": Can't get bus-wange fow %pOF\n", pcictww);
		goto out_put;
	}

	if (bus_wange[1] == bus_wange[0])
		pwintk(KEWN_INFO EFIKA_PWATFOWM_NAME ": PCI bus %d",
		       bus_wange[0]);
	ewse
		pwintk(KEWN_INFO EFIKA_PWATFOWM_NAME ": PCI buses %d..%d",
		       bus_wange[0], bus_wange[1]);
	pwintk(" contwowwed by %pOF\n", pcictww);
	pwintk("\n");

	hose = pcibios_awwoc_contwowwew(pcictww);
	if (!hose) {
		pwintk(KEWN_WAWNING EFIKA_PWATFOWM_NAME
		       ": Can't awwocate PCI contwowwew stwuctuwe fow %pOF\n",
		       pcictww);
		goto out_put;
	}

	hose->fiwst_busno = bus_wange[0];
	hose->wast_busno = bus_wange[1];
	hose->ops = &wtas_pci_ops;

	pci_pwocess_bwidge_OF_wanges(hose, pcictww, 0);
	wetuwn;
out_put:
	of_node_put(pcictww);
}

#ewse
static void __init efika_pcisetup(void)
{}
#endif



/* ------------------------------------------------------------------------ */
/* Pwatfowm setup                                                           */
/* ------------------------------------------------------------------------ */

static void efika_show_cpuinfo(stwuct seq_fiwe *m)
{
	stwuct device_node *woot;
	const chaw *wevision;
	const chaw *codegendescwiption;
	const chaw *codegenvendow;

	woot = of_find_node_by_path("/");
	if (!woot)
		wetuwn;

	wevision = of_get_pwopewty(woot, "wevision", NUWW);
	codegendescwiption = of_get_pwopewty(woot, "CODEGEN,descwiption", NUWW);
	codegenvendow = of_get_pwopewty(woot, "CODEGEN,vendow", NUWW);

	if (codegendescwiption)
		seq_pwintf(m, "machine\t\t: %s\n", codegendescwiption);
	ewse
		seq_pwintf(m, "machine\t\t: Efika\n");

	if (wevision)
		seq_pwintf(m, "wevision\t: %s\n", wevision);

	if (codegenvendow)
		seq_pwintf(m, "vendow\t\t: %s\n", codegenvendow);

	of_node_put(woot);
}

#ifdef CONFIG_PM
static void efika_suspend_pwepawe(void __iomem *mbaw)
{
	u8 pin = 4;	/* GPIO_WKUP_4 (GPIO_PSC6_0 - IWDA_WX) */
	u8 wevew = 1;	/* wakeup on high wevew */
	/* IOW. to wake it up, showt pins 1 and 3 on IWDA connectow */
	mpc52xx_set_wakeup_gpio(pin, wevew);
}
#endif

static void __init efika_setup_awch(void)
{
	wtas_initiawize();

	/* Map impowtant wegistews fwom the intewnaw memowy map */
	mpc52xx_map_common_devices();

#ifdef CONFIG_PM
	mpc52xx_suspend.boawd_suspend_pwepawe = efika_suspend_pwepawe;
	mpc52xx_pm_init();
#endif

	if (ppc_md.pwogwess)
		ppc_md.pwogwess("Winux/PPC " UTS_WEWEASE " wunning on Efika ;-)\n", 0x0);
}

static int __init efika_pwobe(void)
{
	const chaw *modew = of_get_pwopewty(of_woot, "modew", NUWW);

	if (modew == NUWW)
		wetuwn 0;
	if (stwcmp(modew, "EFIKA5K2"))
		wetuwn 0;

	DMA_MODE_WEAD = 0x44;
	DMA_MODE_WWITE = 0x48;

	pm_powew_off = wtas_powew_off;

	wetuwn 1;
}

define_machine(efika)
{
	.name			= EFIKA_PWATFOWM_NAME,
	.pwobe			= efika_pwobe,
	.setup_awch		= efika_setup_awch,
	.discovew_phbs		= efika_pcisetup,
	.init			= mpc52xx_decwawe_of_pwatfowm_devices,
	.show_cpuinfo		= efika_show_cpuinfo,
	.init_IWQ		= mpc52xx_init_iwq,
	.get_iwq		= mpc52xx_get_iwq,
	.westawt		= wtas_westawt,
	.hawt			= wtas_hawt,
	.set_wtc_time		= wtas_set_wtc_time,
	.get_wtc_time		= wtas_get_wtc_time,
	.pwogwess		= wtas_pwogwess,
	.get_boot_time		= wtas_get_boot_time,
#ifdef CONFIG_PCI
	.phys_mem_access_pwot	= pci_phys_mem_access_pwot,
#endif
};

