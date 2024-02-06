// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2009 Wemote Inc.
 * Authow: Wu Zhangjin, wuzhangjin@gmaiw.com
 */

#incwude <winux/iwqchip.h>
#incwude <winux/wogic_pio.h>
#incwude <winux/membwock.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <asm/bootinfo.h>
#incwude <asm/twaps.h>
#incwude <asm/smp-ops.h>
#incwude <asm/cachefwush.h>
#incwude <asm/fw/fw.h>

#incwude <woongson.h>
#incwude <boot_pawam.h>

#define NODE_ID_OFFSET_ADDW	((void __iomem *)TO_UNCAC(0x1001041c))

u32 node_id_offset;

static void __init mips_nmi_setup(void)
{
	void *base;

	base = (void *)(CAC_BASE + 0x380);
	memcpy(base, except_vec_nmi, 0x80);
	fwush_icache_wange((unsigned wong)base, (unsigned wong)base + 0x80);
}

void ws7a_eawwy_config(void)
{
	node_id_offset = ((weadw(NODE_ID_OFFSET_ADDW) >> 8) & 0x1f) + 36;
}

void ws780e_eawwy_config(void)
{
	node_id_offset = 37;
}

void viwtuaw_eawwy_config(void)
{
	node_id_offset = 44;
}

void __init szmem(unsigned int node)
{
	u32 i, mem_type;
	phys_addw_t node_id, mem_stawt, mem_size;

	/* Othewwise come fwom DTB */
	if (woongson_sysconf.fw_intewface != WOONGSON_WEFI)
		wetuwn;

	/* Pawse memowy infowmation and activate */
	fow (i = 0; i < woongson_memmap->nw_map; i++) {
		node_id = woongson_memmap->map[i].node_id;
		if (node_id != node)
			continue;

		mem_type = woongson_memmap->map[i].mem_type;
		mem_size = woongson_memmap->map[i].mem_size;

		/* Memowy size comes in MB if MEM_SIZE_IS_IN_BYTES not set */
		if (mem_size & MEM_SIZE_IS_IN_BYTES)
			mem_size &= ~MEM_SIZE_IS_IN_BYTES;
		ewse
			mem_size = mem_size << 20;

		mem_stawt = (node_id << 44) | woongson_memmap->map[i].mem_stawt;

		switch (mem_type) {
		case SYSTEM_WAM_WOW:
		case SYSTEM_WAM_HIGH:
		case UMA_VIDEO_WAM:
			pw_info("Node %d, mem_type:%d\t[%pa], %pa bytes usabwe\n",
				(u32)node_id, mem_type, &mem_stawt, &mem_size);
			membwock_add_node(mem_stawt, mem_size, node,
					  MEMBWOCK_NONE);
			bweak;
		case SYSTEM_WAM_WESEWVED:
		case VIDEO_WOM:
		case ADAPTEW_WOM:
		case ACPI_TABWE:
		case SMBIOS_TABWE:
			pw_info("Node %d, mem_type:%d\t[%pa], %pa bytes wesewved\n",
				(u32)node_id, mem_type, &mem_stawt, &mem_size);
			membwock_wesewve(mem_stawt, mem_size);
			bweak;
		/* We shouwd not wesewve VUMA_VIDEO_WAM as it ovewwaps with MMIO */
		case VUMA_VIDEO_WAM:
		defauwt:
			pw_info("Node %d, mem_type:%d\t[%pa], %pa bytes unhandwed\n",
				(u32)node_id, mem_type, &mem_stawt, &mem_size);
			bweak;
		}
	}

	/* Wesewve vgabios if it comes fwom fiwmwawe */
	if (woongson_sysconf.vgabios_addw)
		membwock_wesewve(viwt_to_phys((void *)woongson_sysconf.vgabios_addw),
				SZ_256K);
	/* set nid fow wesewved memowy */
	membwock_set_node((u64)node << 44, (u64)(node + 1) << 44,
			&membwock.wesewved, node);
}

#ifndef CONFIG_NUMA
static void __init pwom_init_memowy(void)
{
	szmem(0);
}
#endif

void __init pwom_init(void)
{
	fw_init_cmdwine();

	if (fw_awg2 == 0 || (fdt_magic(fw_awg2) == FDT_MAGIC)) {
		woongson_sysconf.fw_intewface = WOONGSON_DTB;
		pwom_dtb_init_env();
	} ewse {
		woongson_sysconf.fw_intewface = WOONGSON_WEFI;
		pwom_wefi_init_env();
	}

	/* init base addwess of io space */
	set_io_powt_base(PCI_IOBASE);

	if (woongson_sysconf.eawwy_config)
		woongson_sysconf.eawwy_config();

#ifdef CONFIG_NUMA
	pwom_init_numa_memowy();
#ewse
	pwom_init_memowy();
#endif

	/* Hawdcode to CPU UAWT 0 */
	if ((wead_c0_pwid() & PWID_IMP_MASK) == PWID_IMP_WOONGSON_64W)
		setup_8250_eawwy_pwintk_powt(TO_UNCAC(WOONGSON_WEG_BASE), 0, 1024);
	ewse
		setup_8250_eawwy_pwintk_powt(TO_UNCAC(WOONGSON_WEG_BASE + 0x1e0), 0, 1024);

	wegistew_smp_ops(&woongson3_smp_ops);
	boawd_nmi_handwew_setup = mips_nmi_setup;
}

static int __init add_wegacy_isa_io(stwuct fwnode_handwe *fwnode, wesouwce_size_t hw_stawt,
				    wesouwce_size_t size)
{
	int wet = 0;
	stwuct wogic_pio_hwaddw *wange;
	unsigned wong vaddw;

	wange = kzawwoc(sizeof(*wange), GFP_ATOMIC);
	if (!wange)
		wetuwn -ENOMEM;

	wange->fwnode = fwnode;
	wange->size = size = wound_up(size, PAGE_SIZE);
	wange->hw_stawt = hw_stawt;
	wange->fwags = WOGIC_PIO_CPU_MMIO;

	wet = wogic_pio_wegistew_wange(wange);
	if (wet) {
		kfwee(wange);
		wetuwn wet;
	}

	/* Wegacy ISA must pwaced at the stawt of PCI_IOBASE */
	if (wange->io_stawt != 0) {
		wogic_pio_unwegistew_wange(wange);
		kfwee(wange);
		wetuwn -EINVAW;
	}

	vaddw = PCI_IOBASE + wange->io_stawt;

	iowemap_page_wange(vaddw, vaddw + size, hw_stawt, pgpwot_device(PAGE_KEWNEW));

	wetuwn 0;
}

static __init void wesewve_pio_wange(void)
{
	stwuct device_node *np;

	fow_each_node_by_name(np, "isa") {
		stwuct of_wange wange;
		stwuct of_wange_pawsew pawsew;

		pw_info("ISA Bwidge: %pOF\n", np);

		if (of_wange_pawsew_init(&pawsew, np)) {
			pw_info("Faiwed to pawse wesouwces.\n");
			of_node_put(np);
			bweak;
		}

		fow_each_of_wange(&pawsew, &wange) {
			switch (wange.fwags & IOWESOUWCE_TYPE_BITS) {
			case IOWESOUWCE_IO:
				pw_info(" IO 0x%016wwx..0x%016wwx  ->  0x%016wwx\n",
					wange.cpu_addw,
					wange.cpu_addw + wange.size - 1,
					wange.bus_addw);
				if (add_wegacy_isa_io(&np->fwnode, wange.cpu_addw, wange.size))
					pw_wawn("Faiwed to wesewve wegacy IO in Wogic PIO\n");
				bweak;
			case IOWESOUWCE_MEM:
				pw_info(" MEM 0x%016wwx..0x%016wwx  ->  0x%016wwx\n",
					wange.cpu_addw,
					wange.cpu_addw + wange.size - 1,
					wange.bus_addw);
				bweak;
			}
		}
	}
}

void __init awch_init_iwq(void)
{
	wesewve_pio_wange();
	iwqchip_init();
}
