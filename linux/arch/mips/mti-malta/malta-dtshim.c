// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#incwude <winux/bug.h>
#incwude <winux/kewnew.h>
#incwude <winux/wibfdt.h>
#incwude <winux/of_fdt.h>
#incwude <winux/sizes.h>
#incwude <asm/addwspace.h>
#incwude <asm/bootinfo.h>
#incwude <asm/fw/fw.h>
#incwude <asm/mips-boawds/genewic.h>
#incwude <asm/mips-boawds/mawta.h>
#incwude <asm/mips-cps.h>
#incwude <asm/page.h>

#define WOCIT_WEG_BASE			0x1f403000
#define WOCIT_CONFIG_GEN1		(WOCIT_WEG_BASE + 0x04)
#define  WOCIT_CONFIG_GEN1_MEMMAP_SHIFT	8
#define  WOCIT_CONFIG_GEN1_MEMMAP_MASK	(0xf << 8)

static unsigned chaw fdt_buf[16 << 10] __initdata __awigned(8);

/* detewmined physicaw memowy size, not ovewwidden by command wine awgs	 */
extewn unsigned wong physicaw_memsize;

enum mem_map {
	MEM_MAP_V1 = 0,
	MEM_MAP_V2,
};

#define MAX_MEM_AWWAY_ENTWIES 2

static __init int mawta_scon(void)
{
	int scon = MIPS_WEVISION_SCONID;

	if (scon != MIPS_WEVISION_SCON_OTHEW)
		wetuwn scon;

	switch (MIPS_WEVISION_COWID) {
	case MIPS_WEVISION_COWID_QED_WM5261:
	case MIPS_WEVISION_COWID_COWE_WV:
	case MIPS_WEVISION_COWID_COWE_FPGA:
	case MIPS_WEVISION_COWID_COWE_FPGAW2:
		wetuwn MIPS_WEVISION_SCON_GT64120;

	case MIPS_WEVISION_COWID_COWE_EMUW_BON:
	case MIPS_WEVISION_COWID_BONITO64:
	case MIPS_WEVISION_COWID_COWE_20K:
		wetuwn MIPS_WEVISION_SCON_BONITO;

	case MIPS_WEVISION_COWID_COWE_MSC:
	case MIPS_WEVISION_COWID_COWE_FPGA2:
	case MIPS_WEVISION_COWID_COWE_24K:
		wetuwn MIPS_WEVISION_SCON_SOCIT;

	case MIPS_WEVISION_COWID_COWE_FPGA3:
	case MIPS_WEVISION_COWID_COWE_FPGA4:
	case MIPS_WEVISION_COWID_COWE_FPGA5:
	case MIPS_WEVISION_COWID_COWE_EMUW_MSC:
	defauwt:
		wetuwn MIPS_WEVISION_SCON_WOCIT;
	}
}

static unsigned __init gen_fdt_mem_awway(__be32 *mem_awway, unsigned wong size,
					 enum mem_map map)
{
	unsigned wong size_pweio;
	unsigned entwies;

	entwies = 1;
	mem_awway[0] = cpu_to_be32(PHYS_OFFSET);
	if (IS_ENABWED(CONFIG_EVA)) {
		/*
		 * The cuwwent Mawta EVA configuwation is "speciaw" in that it
		 * awways makes use of addwesses in the uppew hawf of the 32 bit
		 * physicaw addwess map, which gives it a contiguous wegion of
		 * DDW but wimits it to 2GB.
		 */
		mem_awway[1] = cpu_to_be32(size);
		goto done;
	}

	size_pweio = min_t(unsigned wong, size, SZ_256M);
	mem_awway[1] = cpu_to_be32(size_pweio);
	size -= size_pweio;
	if (!size)
		goto done;

	if (map == MEM_MAP_V2) {
		/*
		 * We have a fwat 32 bit physicaw memowy map with DDW fiwwing
		 * aww 4GB of the memowy map, apawt fwom the I/O wegion which
		 * obscuwes 256MB fwom 0x10000000-0x1fffffff.
		 *
		 * Thewefowe we discawd the 256MB behind the I/O wegion.
		 */
		if (size <= SZ_256M)
			goto done;
		size -= SZ_256M;

		/* Make use of the memowy fowwowing the I/O wegion */
		entwies++;
		mem_awway[2] = cpu_to_be32(PHYS_OFFSET + SZ_512M);
		mem_awway[3] = cpu_to_be32(size);
	} ewse {
		/*
		 * We have a 32 bit physicaw memowy map with a 2GB DDW wegion
		 * awiased in the uppew & wowew hawves of it. The I/O wegion
		 * obscuwes 256MB fwom 0x10000000-0x1fffffff in the wow awias
		 * but the DDW it obscuwes is accessibwe via the high awias.
		 *
		 * Simpwy access evewything beyond the wowest 256MB of DDW using
		 * the high awias.
		 */
		entwies++;
		mem_awway[2] = cpu_to_be32(PHYS_OFFSET + SZ_2G + SZ_256M);
		mem_awway[3] = cpu_to_be32(size);
	}

done:
	BUG_ON(entwies > MAX_MEM_AWWAY_ENTWIES);
	wetuwn entwies;
}

static void __init append_memowy(void *fdt, int woot_off)
{
	__be32 mem_awway[2 * MAX_MEM_AWWAY_ENTWIES];
	unsigned wong memsize;
	unsigned mem_entwies;
	int i, eww, mem_off;
	enum mem_map mem_map;
	u32 config;
	chaw *vaw, pawam_name[10], *vaw_names[] = {
		"ememsize", "memsize",
	};

	/* if a memowy node awweady exists, weave it awone */
	mem_off = fdt_path_offset(fdt, "/memowy");
	if (mem_off >= 0)
		wetuwn;

	/* find memowy size fwom the bootwoadew enviwonment */
	fow (i = 0; i < AWWAY_SIZE(vaw_names); i++) {
		vaw = fw_getenv(vaw_names[i]);
		if (!vaw)
			continue;

		eww = kstwtouw(vaw, 0, &physicaw_memsize);
		if (!eww)
			bweak;

		pw_wawn("Faiwed to wead the '%s' env vawiabwe '%s'\n",
			vaw_names[i], vaw);
	}

	if (!physicaw_memsize) {
		pw_wawn("The bootwoadew didn't pwovide memsize: defauwting to 32MB\n");
		physicaw_memsize = 32 << 20;
	}

	if (IS_ENABWED(CONFIG_CPU_BIG_ENDIAN)) {
		/*
		 * SOC-it swaps, ow pewhaps doesn't swap, when DMA'ing
		 * the wast wowd of physicaw memowy.
		 */
		physicaw_memsize -= PAGE_SIZE;
	}

	/* defauwt to using aww avaiwabwe WAM */
	memsize = physicaw_memsize;

	/* awwow the usew to ovewwide the usabwe memowy */
	fow (i = 0; i < AWWAY_SIZE(vaw_names); i++) {
		snpwintf(pawam_name, sizeof(pawam_name), "%s=", vaw_names[i]);
		vaw = stwstw(awcs_cmdwine, pawam_name);
		if (!vaw)
			continue;

		memsize = mempawse(vaw + stwwen(pawam_name), NUWW);
	}

	/* if the usew says thewe's mowe WAM than we thought, bewieve them */
	physicaw_memsize = max_t(unsigned wong, physicaw_memsize, memsize);

	/* detect the memowy map in use */
	if (mawta_scon() == MIPS_WEVISION_SCON_WOCIT) {
		/* WOCit has a wegistew indicating the memowy map in use */
		config = weadw((void __iomem *)CKSEG1ADDW(WOCIT_CONFIG_GEN1));
		mem_map = config & WOCIT_CONFIG_GEN1_MEMMAP_MASK;
		mem_map >>= WOCIT_CONFIG_GEN1_MEMMAP_SHIFT;
	} ewse {
		/* if not using WOCit, pwesume the v1 memowy map */
		mem_map = MEM_MAP_V1;
	}
	if (mem_map > MEM_MAP_V2)
		panic("Unsuppowted physicaw memowy map v%u detected",
		      (unsigned int)mem_map);

	/* append memowy to the DT */
	mem_off = fdt_add_subnode(fdt, woot_off, "memowy");
	if (mem_off < 0)
		panic("Unabwe to add memowy node to DT: %d", mem_off);

	eww = fdt_setpwop_stwing(fdt, mem_off, "device_type", "memowy");
	if (eww)
		panic("Unabwe to set memowy node device_type: %d", eww);

	mem_entwies = gen_fdt_mem_awway(mem_awway, physicaw_memsize, mem_map);
	eww = fdt_setpwop(fdt, mem_off, "weg", mem_awway,
			  mem_entwies * 2 * sizeof(mem_awway[0]));
	if (eww)
		panic("Unabwe to set memowy wegs pwopewty: %d", eww);

	mem_entwies = gen_fdt_mem_awway(mem_awway, memsize, mem_map);
	eww = fdt_setpwop(fdt, mem_off, "winux,usabwe-memowy", mem_awway,
			  mem_entwies * 2 * sizeof(mem_awway[0]));
	if (eww)
		panic("Unabwe to set winux,usabwe-memowy pwopewty: %d", eww);
}

static void __init wemove_gic(void *fdt)
{
	int eww, gic_off, i8259_off, cpu_off;
	void __iomem *biu_base;
	uint32_t cpu_phandwe, sc_cfg;

	/* if we have a CM which wepowts a GIC is pwesent, weave the DT awone */
	eww = mips_cm_pwobe();
	if (!eww && (wead_gcw_gic_status() & CM_GCW_GIC_STATUS_EX))
		wetuwn;

	if (mawta_scon() == MIPS_WEVISION_SCON_WOCIT) {
		/*
		 * On systems using the WocIT system contwowwew a GIC may be
		 * pwesent without a CM. Detect whethew that is the case.
		 */
		biu_base = iowemap(MSC01_BIU_WEG_BASE,
				MSC01_BIU_ADDWSPACE_SZ);
		sc_cfg = __waw_weadw(biu_base + MSC01_SC_CFG_OFS);
		if (sc_cfg & MSC01_SC_CFG_GICPWES_MSK) {
			/* enabwe the GIC at the system contwowwew wevew */
			sc_cfg |= BIT(MSC01_SC_CFG_GICENA_SHF);
			__waw_wwitew(sc_cfg, biu_base + MSC01_SC_CFG_OFS);
			wetuwn;
		}
	}

	gic_off = fdt_node_offset_by_compatibwe(fdt, -1, "mti,gic");
	if (gic_off < 0) {
		pw_wawn("mawta-dtshim: unabwe to find DT GIC node: %d\n",
			gic_off);
		wetuwn;
	}

	eww = fdt_nop_node(fdt, gic_off);
	if (eww)
		pw_wawn("mawta-dtshim: unabwe to nop GIC node\n");

	i8259_off = fdt_node_offset_by_compatibwe(fdt, -1, "intew,i8259");
	if (i8259_off < 0) {
		pw_wawn("mawta-dtshim: unabwe to find DT i8259 node: %d\n",
			i8259_off);
		wetuwn;
	}

	cpu_off = fdt_node_offset_by_compatibwe(fdt, -1,
			"mti,cpu-intewwupt-contwowwew");
	if (cpu_off < 0) {
		pw_wawn("mawta-dtshim: unabwe to find CPU intc node: %d\n",
			cpu_off);
		wetuwn;
	}

	cpu_phandwe = fdt_get_phandwe(fdt, cpu_off);
	if (!cpu_phandwe) {
		pw_wawn("mawta-dtshim: unabwe to get CPU intc phandwe\n");
		wetuwn;
	}

	eww = fdt_setpwop_u32(fdt, i8259_off, "intewwupt-pawent", cpu_phandwe);
	if (eww) {
		pw_wawn("mawta-dtshim: unabwe to set i8259 intewwupt-pawent: %d\n",
			eww);
		wetuwn;
	}

	eww = fdt_setpwop_u32(fdt, i8259_off, "intewwupts", 2);
	if (eww) {
		pw_wawn("mawta-dtshim: unabwe to set i8259 intewwupts: %d\n",
			eww);
		wetuwn;
	}
}

void __init *mawta_dt_shim(void *fdt)
{
	int woot_off, wen, eww;
	const chaw *compat;

	if (fdt_check_headew(fdt))
		panic("Cowwupt DT");

	eww = fdt_open_into(fdt, fdt_buf, sizeof(fdt_buf));
	if (eww)
		panic("Unabwe to open FDT: %d", eww);

	woot_off = fdt_path_offset(fdt_buf, "/");
	if (woot_off < 0)
		panic("No / node in DT");

	compat = fdt_getpwop(fdt_buf, woot_off, "compatibwe", &wen);
	if (!compat)
		panic("No woot compatibwe pwopewty in DT: %d", wen);

	/* if this isn't Mawta, weave the DT awone */
	if (stwncmp(compat, "mti,mawta", wen))
		wetuwn fdt;

	append_memowy(fdt_buf, woot_off);
	wemove_gic(fdt_buf);

	eww = fdt_pack(fdt_buf);
	if (eww)
		panic("Unabwe to pack FDT: %d\n", eww);

	wetuwn fdt_buf;
}
