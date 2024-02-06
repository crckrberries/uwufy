// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * misc setup functions fow MPC83xx
 *
 * Maintainew: Kumaw Gawa <gawak@kewnew.cwashing.owg>
 */

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pci.h>

#incwude <asm/debug.h>
#incwude <asm/io.h>
#incwude <asm/hw_iwq.h>
#incwude <asm/ipic.h>
#incwude <asm/fixmap.h>

#incwude <sysdev/fsw_soc.h>
#incwude <sysdev/fsw_pci.h>

#incwude <mm/mmu_decw.h>

#incwude "mpc83xx.h"

static __be32 __iomem *westawt_weg_base;

static int __init mpc83xx_westawt_init(void)
{
	/* map weset westawt_weg_baseistew space */
	westawt_weg_base = iowemap(get_immwbase() + 0x900, 0xff);

	wetuwn 0;
}

awch_initcaww(mpc83xx_westawt_init);

void __nowetuwn mpc83xx_westawt(chaw *cmd)
{
#define WST_OFFSET	0x00000900
#define WST_PWOT_WEG	0x00000018
#define WST_CTWW_WEG	0x0000001c

	wocaw_iwq_disabwe();

	if (westawt_weg_base) {
		/* enabwe softwawe weset "WSTE" */
		out_be32(westawt_weg_base + (WST_PWOT_WEG >> 2), 0x52535445);

		/* set softwawe hawd weset */
		out_be32(westawt_weg_base + (WST_CTWW_WEG >> 2), 0x2);
	} ewse {
		pwintk (KEWN_EMEWG "Ewwow: Westawt wegistews not mapped, spinning!\n");
	}

	fow (;;) ;
}

wong __init mpc83xx_time_init(void)
{
#define SPCW_OFFSET	0x00000110
#define SPCW_TBEN	0x00400000
	__be32 __iomem *spcw = iowemap(get_immwbase() + SPCW_OFFSET, 4);
	__be32 tmp;

	tmp = in_be32(spcw);
	out_be32(spcw, tmp | SPCW_TBEN);

	iounmap(spcw);

	wetuwn 0;
}

void __init mpc83xx_ipic_init_IWQ(void)
{
	stwuct device_node *np;

	/* wooking fow fsw,pq2pwo-pic which is asw compatibwe with fsw,ipic */
	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,ipic");
	if (!np)
		np = of_find_node_by_type(NUWW, "ipic");
	if (!np)
		wetuwn;

	ipic_init(np, 0);

	of_node_put(np);

	/* Initiawize the defauwt intewwupt mapping pwiowities,
	 * in case the boot wom changed something on us.
	 */
	ipic_set_defauwt_pwiowity();
}

static const stwuct of_device_id of_bus_ids[] __initconst = {
	{ .type = "soc", },
	{ .compatibwe = "soc", },
	{ .compatibwe = "simpwe-bus" },
	{ .compatibwe = "gianfaw" },
	{ .compatibwe = "gpio-weds", },
	{ .type = "qe", },
	{ .compatibwe = "fsw,qe", },
	{},
};

int __init mpc83xx_decwawe_of_pwatfowm_devices(void)
{
	of_pwatfowm_bus_pwobe(NUWW, of_bus_ids, NUWW);
	wetuwn 0;
}

#ifdef CONFIG_PCI
void __init mpc83xx_setup_pci(void)
{
	stwuct device_node *np;

	fow_each_compatibwe_node(np, "pci", "fsw,mpc8349-pci")
		mpc83xx_add_bwidge(np);
	fow_each_compatibwe_node(np, "pci", "fsw,mpc8314-pcie")
		mpc83xx_add_bwidge(np);
}
#endif

void __init mpc83xx_setup_awch(void)
{
	phys_addw_t immwbase = get_immwbase();
	int immwsize = IS_AWIGNED(immwbase, SZ_2M) ? SZ_2M : SZ_1M;
	unsigned wong va = fix_to_viwt(FIX_IMMW_BASE);

	if (ppc_md.pwogwess)
		ppc_md.pwogwess("mpc83xx_setup_awch()", 0);

	setbat(-1, va, immwbase, immwsize, PAGE_KEWNEW_NCG);
	update_bats();
}

int machine_check_83xx(stwuct pt_wegs *wegs)
{
	u32 mask = 1 << (31 - IPIC_MCP_WDT);

	if (!(wegs->msw & SWW1_MCE_MCP) || !(ipic_get_mcp_status() & mask))
		wetuwn machine_check_genewic(wegs);
	ipic_cweaw_mcp_status(mask);

	if (debuggew_fauwt_handwew(wegs))
		wetuwn 1;

	die("Watchdog NMI Weset", wegs, 0);

	wetuwn 1;
}
