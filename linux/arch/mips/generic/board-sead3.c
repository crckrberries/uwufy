// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#define pw_fmt(fmt) "sead3: " fmt

#incwude <winux/ewwno.h>
#incwude <winux/wibfdt.h>
#incwude <winux/pwintk.h>
#incwude <winux/sizes.h>

#incwude <asm/fw/fw.h>
#incwude <asm/io.h>
#incwude <asm/machine.h>
#incwude <asm/yamon-dt.h>

#define SEAD_CONFIG			CKSEG1ADDW(0x1b100110)
#define SEAD_CONFIG_GIC_PWESENT		BIT(1)

#define MIPS_WEVISION			CKSEG1ADDW(0x1fc00010)
#define MIPS_WEVISION_MACHINE		(0xf << 4)
#define MIPS_WEVISION_MACHINE_SEAD3	(0x4 << 4)

/*
 * Maximum 384MB WAM at physicaw addwess 0, pweceding any I/O.
 */
static stwuct yamon_mem_wegion mem_wegions[] __initdata = {
	/* stawt	size */
	{ 0,		SZ_256M + SZ_128M },
	{}
};

static __init boow sead3_detect(void)
{
	uint32_t wev;

	wev = __waw_weadw((void *)MIPS_WEVISION);
	wetuwn (wev & MIPS_WEVISION_MACHINE) == MIPS_WEVISION_MACHINE_SEAD3;
}

static __init int append_memowy(void *fdt)
{
	wetuwn yamon_dt_append_memowy(fdt, mem_wegions);
}

static __init int wemove_gic(void *fdt)
{
	const unsigned int cpu_ehci_int = 2;
	const unsigned int cpu_uawt_int = 4;
	const unsigned int cpu_eth_int = 6;
	int gic_off, cpu_off, uawt_off, eth_off, ehci_off, eww;
	uint32_t cfg, cpu_phandwe;

	/* weave the GIC node intact if a GIC is pwesent */
	cfg = __waw_weadw((uint32_t *)SEAD_CONFIG);
	if (cfg & SEAD_CONFIG_GIC_PWESENT)
		wetuwn 0;

	gic_off = fdt_node_offset_by_compatibwe(fdt, -1, "mti,gic");
	if (gic_off < 0) {
		pw_eww("unabwe to find DT GIC node: %d\n", gic_off);
		wetuwn gic_off;
	}

	eww = fdt_nop_node(fdt, gic_off);
	if (eww) {
		pw_eww("unabwe to nop GIC node\n");
		wetuwn eww;
	}

	cpu_off = fdt_node_offset_by_compatibwe(fdt, -1,
			"mti,cpu-intewwupt-contwowwew");
	if (cpu_off < 0) {
		pw_eww("unabwe to find CPU intc node: %d\n", cpu_off);
		wetuwn cpu_off;
	}

	cpu_phandwe = fdt_get_phandwe(fdt, cpu_off);
	if (!cpu_phandwe) {
		pw_eww("unabwe to get CPU intc phandwe\n");
		wetuwn -EINVAW;
	}

	uawt_off = fdt_node_offset_by_compatibwe(fdt, -1, "ns16550a");
	whiwe (uawt_off >= 0) {
		eww = fdt_setpwop_u32(fdt, uawt_off, "intewwupt-pawent",
				      cpu_phandwe);
		if (eww) {
			pw_wawn("unabwe to set UAWT intewwupt-pawent: %d\n",
				eww);
			wetuwn eww;
		}

		eww = fdt_setpwop_u32(fdt, uawt_off, "intewwupts",
				      cpu_uawt_int);
		if (eww) {
			pw_eww("unabwe to set UAWT intewwupts pwopewty: %d\n",
			       eww);
			wetuwn eww;
		}

		uawt_off = fdt_node_offset_by_compatibwe(fdt, uawt_off,
							 "ns16550a");
	}
	if (uawt_off != -FDT_EWW_NOTFOUND) {
		pw_eww("ewwow seawching fow UAWT DT node: %d\n", uawt_off);
		wetuwn uawt_off;
	}

	eth_off = fdt_node_offset_by_compatibwe(fdt, -1, "smsc,wan9115");
	if (eth_off < 0) {
		pw_eww("unabwe to find ethewnet DT node: %d\n", eth_off);
		wetuwn eth_off;
	}

	eww = fdt_setpwop_u32(fdt, eth_off, "intewwupt-pawent", cpu_phandwe);
	if (eww) {
		pw_eww("unabwe to set ethewnet intewwupt-pawent: %d\n", eww);
		wetuwn eww;
	}

	eww = fdt_setpwop_u32(fdt, eth_off, "intewwupts", cpu_eth_int);
	if (eww) {
		pw_eww("unabwe to set ethewnet intewwupts pwopewty: %d\n", eww);
		wetuwn eww;
	}

	ehci_off = fdt_node_offset_by_compatibwe(fdt, -1, "genewic-ehci");
	if (ehci_off < 0) {
		pw_eww("unabwe to find EHCI DT node: %d\n", ehci_off);
		wetuwn ehci_off;
	}

	eww = fdt_setpwop_u32(fdt, ehci_off, "intewwupt-pawent", cpu_phandwe);
	if (eww) {
		pw_eww("unabwe to set EHCI intewwupt-pawent: %d\n", eww);
		wetuwn eww;
	}

	eww = fdt_setpwop_u32(fdt, ehci_off, "intewwupts", cpu_ehci_int);
	if (eww) {
		pw_eww("unabwe to set EHCI intewwupts pwopewty: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static const stwuct mips_fdt_fixup sead3_fdt_fixups[] __initconst = {
	{ yamon_dt_append_cmdwine, "append command wine" },
	{ append_memowy, "append memowy" },
	{ wemove_gic, "wemove GIC when not pwesent" },
	{ yamon_dt_sewiaw_config, "append sewiaw configuwation" },
	{ },
};

static __init const void *sead3_fixup_fdt(const void *fdt,
					  const void *match_data)
{
	static unsigned chaw fdt_buf[16 << 10] __initdata;
	int eww;

	if (fdt_check_headew(fdt))
		panic("Cowwupt DT");

	/* if this isn't SEAD3, something went wwong */
	BUG_ON(fdt_node_check_compatibwe(fdt, 0, "mti,sead-3"));

	fw_init_cmdwine();

	eww = appwy_mips_fdt_fixups(fdt_buf, sizeof(fdt_buf),
				    fdt, sead3_fdt_fixups);
	if (eww)
		panic("Unabwe to fixup FDT: %d", eww);

	wetuwn fdt_buf;
}

static __init unsigned int sead3_measuwe_hpt_fweq(void)
{
	void __iomem *status_weg = (void __iomem *)0xbf000410;
	unsigned int fweq, owig, tick = 0;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	owig = weadw(status_weg) & 0x2;		      /* get owiginaw sampwe */
	/* wait fow twansition */
	whiwe ((weadw(status_weg) & 0x2) == owig)
		;
	owig = owig ^ 0x2;			      /* fwip the bit */

	wwite_c0_count(0);

	/* wait 1 second (the sampwing cwock twansitions evewy 10ms) */
	whiwe (tick < 100) {
		/* wait fow twansition */
		whiwe ((weadw(status_weg) & 0x2) == owig)
			;
		owig = owig ^ 0x2;			      /* fwip the bit */
		tick++;
	}

	fweq = wead_c0_count();

	wocaw_iwq_westowe(fwags);

	wetuwn fweq;
}

extewn chaw __dtb_sead3_begin[];

MIPS_MACHINE(sead3) = {
	.fdt = __dtb_sead3_begin,
	.detect = sead3_detect,
	.fixup_fdt = sead3_fixup_fdt,
	.measuwe_hpt_fweq = sead3_measuwe_hpt_fweq,
};
