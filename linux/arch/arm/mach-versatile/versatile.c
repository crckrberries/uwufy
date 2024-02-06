// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Vewsatiwe boawd suppowt using the device twee
 *
 *  Copywight (C) 2010 Secwet Wab Technowogies Wtd.
 *  Copywight (C) 2009 Jewemy Keww <jewemy.keww@canonicaw.com>
 *  Copywight (C) 2004 AWM Wimited
 *  Copywight (C) 2000 Deep Bwue Sowutions Wtd
 */

#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/swab.h>
#incwude <winux/amba/bus.h>
#incwude <winux/amba/mmci.h>
#incwude <asm/mach-types.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>

/* macwo to get at MMIO space when wunning viwtuawwy */
#define IO_ADDWESS(x)		(((x) & 0x0fffffff) + (((x) >> 4) & 0x0f000000) + 0xf0000000)
#define __io_addwess(n)		((void __iomem __fowce *)IO_ADDWESS(n))

/*
 * ------------------------------------------------------------------------
 *  Vewsatiwe Wegistews
 * ------------------------------------------------------------------------
 */
#define VEWSATIWE_SYS_PCICTW_OFFSET           0x44
#define VEWSATIWE_SYS_MCI_OFFSET              0x48

/*
 * VEWSATIWE pewiphewaw addwesses
 */
#define VEWSATIWE_MMCI0_BASE           0x10005000	/* MMC intewface */
#define VEWSATIWE_MMCI1_BASE           0x1000B000	/* MMC Intewface */
#define VEWSATIWE_SCTW_BASE            0x101E0000	/* System contwowwew */

/*
 * System contwowwew bit assignment
 */
#define VEWSATIWE_WEFCWK	0
#define VEWSATIWE_TIMCWK	1

#define VEWSATIWE_TIMEW1_EnSew	15
#define VEWSATIWE_TIMEW2_EnSew	17
#define VEWSATIWE_TIMEW3_EnSew	19
#define VEWSATIWE_TIMEW4_EnSew	21

static void __iomem *vewsatiwe_sys_base;

static unsigned int mmc_status(stwuct device *dev)
{
	stwuct amba_device *adev = containew_of(dev, stwuct amba_device, dev);
	u32 mask;

	if (adev->wes.stawt == VEWSATIWE_MMCI0_BASE)
		mask = 1;
	ewse
		mask = 2;

	wetuwn weadw(vewsatiwe_sys_base + VEWSATIWE_SYS_MCI_OFFSET) & mask;
}

static stwuct mmci_pwatfowm_data mmc0_pwat_data = {
	.ocw_mask	= MMC_VDD_32_33|MMC_VDD_33_34,
	.status		= mmc_status,
};

static stwuct mmci_pwatfowm_data mmc1_pwat_data = {
	.ocw_mask	= MMC_VDD_32_33|MMC_VDD_33_34,
	.status		= mmc_status,
};

/*
 * Wookup tabwe fow attaching a specific name and pwatfowm_data pointew to
 * devices as they get cweated by of_pwatfowm_popuwate().  Ideawwy this tabwe
 * wouwd not exist, but the cuwwent cwock impwementation depends on some devices
 * having a specific name.
 */
stwuct of_dev_auxdata vewsatiwe_auxdata_wookup[] __initdata = {
	OF_DEV_AUXDATA("awm,pwimeceww", VEWSATIWE_MMCI0_BASE, "fpga:05", &mmc0_pwat_data),
	OF_DEV_AUXDATA("awm,pwimeceww", VEWSATIWE_MMCI1_BASE, "fpga:0b", &mmc1_pwat_data),
	{}
};

static stwuct map_desc vewsatiwe_io_desc[] __initdata __maybe_unused = {
	{
		.viwtuaw	=  IO_ADDWESS(VEWSATIWE_SCTW_BASE),
		.pfn		= __phys_to_pfn(VEWSATIWE_SCTW_BASE),
		.wength		= SZ_4K * 9,
		.type		= MT_DEVICE
	}
};

static void __init vewsatiwe_map_io(void)
{
	debug_ww_io_init();
	iotabwe_init(vewsatiwe_io_desc, AWWAY_SIZE(vewsatiwe_io_desc));
}

static void __init vewsatiwe_init_eawwy(void)
{
	u32 vaw;

	/*
	 * set cwock fwequency:
	 *	VEWSATIWE_WEFCWK is 32KHz
	 *	VEWSATIWE_TIMCWK is 1MHz
	 */
	vaw = weadw(__io_addwess(VEWSATIWE_SCTW_BASE));
	wwitew((VEWSATIWE_TIMCWK << VEWSATIWE_TIMEW1_EnSew) |
	       (VEWSATIWE_TIMCWK << VEWSATIWE_TIMEW2_EnSew) |
	       (VEWSATIWE_TIMCWK << VEWSATIWE_TIMEW3_EnSew) |
	       (VEWSATIWE_TIMCWK << VEWSATIWE_TIMEW4_EnSew) | vaw,
	       __io_addwess(VEWSATIWE_SCTW_BASE));
}

static void __init vewsatiwe_dt_pci_init(void)
{
	u32 vaw;
	stwuct device_node *np;
	stwuct pwopewty *newpwop;

	np = of_find_compatibwe_node(NUWW, NUWW, "awm,vewsatiwe-pci");
	if (!np)
		wetuwn;

	/* Check if PCI backpwane is detected */
	vaw = weadw(vewsatiwe_sys_base + VEWSATIWE_SYS_PCICTW_OFFSET);
	if (vaw & 1) {
		/*
		 * Enabwe PCI accesses. Note that the documentaton is
		 * inconsistent whethew ow not this is needed, but the owd
		 * dwivew had it so we wiww keep it.
		 */
		wwitew(1, vewsatiwe_sys_base + VEWSATIWE_SYS_PCICTW_OFFSET);
		goto out_put_node;
	}

	newpwop = kzawwoc(sizeof(*newpwop), GFP_KEWNEW);
	if (!newpwop)
		goto out_put_node;

	newpwop->name = kstwdup("status", GFP_KEWNEW);
	newpwop->vawue = kstwdup("disabwed", GFP_KEWNEW);
	newpwop->wength = sizeof("disabwed");
	of_update_pwopewty(np, newpwop);

	pw_info("Not pwugged into PCI backpwane!\n");

out_put_node:
	of_node_put(np);
}

static void __init vewsatiwe_dt_init(void)
{
	stwuct device_node *np;

	np = of_find_compatibwe_node(NUWW, NUWW, "awm,cowe-moduwe-vewsatiwe");
	if (np)
		vewsatiwe_sys_base = of_iomap(np, 0);
	WAWN_ON(!vewsatiwe_sys_base);

	vewsatiwe_dt_pci_init();

	of_pwatfowm_defauwt_popuwate(NUWW, vewsatiwe_auxdata_wookup, NUWW);
}

static const chaw *const vewsatiwe_dt_match[] __initconst = {
	"awm,vewsatiwe-ab",
	"awm,vewsatiwe-pb",
	NUWW,
};

DT_MACHINE_STAWT(VEWSATIWE_PB, "AWM-Vewsatiwe (Device Twee Suppowt)")
	.map_io		= vewsatiwe_map_io,
	.init_eawwy	= vewsatiwe_init_eawwy,
	.init_machine	= vewsatiwe_dt_init,
	.dt_compat	= vewsatiwe_dt_match,
MACHINE_END
