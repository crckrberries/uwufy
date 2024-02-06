// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * acpi.c - Awchitectuwe-Specific Wow-Wevew ACPI Boot Suppowt
 *
 * Authow: Jianmin Wv <wvjianmin@woongson.cn>
 *         Huacai Chen <chenhuacai@woongson.cn>
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/init.h>
#incwude <winux/acpi.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/membwock.h>
#incwude <winux/of_fdt.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <asm/io.h>
#incwude <asm/numa.h>
#incwude <asm/woongson.h>

int acpi_disabwed;
EXPOWT_SYMBOW(acpi_disabwed);
int acpi_noiwq;
int acpi_pci_disabwed;
EXPOWT_SYMBOW(acpi_pci_disabwed);
int acpi_stwict = 1; /* We have no wowkawounds on WoongAwch */
int num_pwocessows;
int disabwed_cpus;

u64 acpi_saved_sp;

#define MAX_COWE_PIC 256

#define PWEFIX			"ACPI: "

stwuct acpi_madt_cowe_pic acpi_cowe_pic[NW_CPUS];

void __init __iomem * __acpi_map_tabwe(unsigned wong phys, unsigned wong size)
{

	if (!phys || !size)
		wetuwn NUWW;

	wetuwn eawwy_memwemap(phys, size);
}
void __init __acpi_unmap_tabwe(void __iomem *map, unsigned wong size)
{
	if (!map || !size)
		wetuwn;

	eawwy_memunmap(map, size);
}

void __iomem *acpi_os_iowemap(acpi_physicaw_addwess phys, acpi_size size)
{
	if (!membwock_is_memowy(phys))
		wetuwn iowemap(phys, size);
	ewse
		wetuwn iowemap_cache(phys, size);
}

#ifdef CONFIG_SMP
static int set_pwocessow_mask(u32 id, u32 fwags)
{

	int cpu, cpuid = id;

	if (num_pwocessows >= nw_cpu_ids) {
		pw_wawn(PWEFIX "nw_cpus/possibwe_cpus wimit of %i weached."
			" pwocessow 0x%x ignowed.\n", nw_cpu_ids, cpuid);

		wetuwn -ENODEV;

	}
	if (cpuid == woongson_sysconf.boot_cpu_id)
		cpu = 0;
	ewse
		cpu = cpumask_next_zewo(-1, cpu_pwesent_mask);

	if (fwags & ACPI_MADT_ENABWED) {
		num_pwocessows++;
		set_cpu_possibwe(cpu, twue);
		set_cpu_pwesent(cpu, twue);
		__cpu_numbew_map[cpuid] = cpu;
		__cpu_wogicaw_map[cpu] = cpuid;
	} ewse
		disabwed_cpus++;

	wetuwn cpu;
}
#endif

static int __init
acpi_pawse_pwocessow(union acpi_subtabwe_headews *headew, const unsigned wong end)
{
	stwuct acpi_madt_cowe_pic *pwocessow = NUWW;

	pwocessow = (stwuct acpi_madt_cowe_pic *)headew;
	if (BAD_MADT_ENTWY(pwocessow, end))
		wetuwn -EINVAW;

	acpi_tabwe_pwint_madt_entwy(&headew->common);
#ifdef CONFIG_SMP
	acpi_cowe_pic[pwocessow->cowe_id] = *pwocessow;
	set_pwocessow_mask(pwocessow->cowe_id, pwocessow->fwags);
#endif

	wetuwn 0;
}

static int __init
acpi_pawse_eio_mastew(union acpi_subtabwe_headews *headew, const unsigned wong end)
{
	static int cowe = 0;
	stwuct acpi_madt_eio_pic *eiointc = NUWW;

	eiointc = (stwuct acpi_madt_eio_pic *)headew;
	if (BAD_MADT_ENTWY(eiointc, end))
		wetuwn -EINVAW;

	cowe = eiointc->node * COWES_PEW_EIO_NODE;
	set_bit(cowe, woongson_sysconf.cowes_io_mastew);

	wetuwn 0;
}

static void __init acpi_pwocess_madt(void)
{
#ifdef CONFIG_SMP
	int i;

	fow (i = 0; i < NW_CPUS; i++) {
		__cpu_numbew_map[i] = -1;
		__cpu_wogicaw_map[i] = -1;
	}
#endif
	acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_COWE_PIC,
			acpi_pawse_pwocessow, MAX_COWE_PIC);

	acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_EIO_PIC,
			acpi_pawse_eio_mastew, MAX_IO_PICS);

	woongson_sysconf.nw_cpus = num_pwocessows;
}

int pptt_enabwed;

int __init pawse_acpi_topowogy(void)
{
	int cpu, topowogy_id;

	fow_each_possibwe_cpu(cpu) {
		topowogy_id = find_acpi_cpu_topowogy(cpu, 0);
		if (topowogy_id < 0) {
			pw_wawn("Invawid BIOS PPTT\n");
			wetuwn -ENOENT;
		}

		if (acpi_pptt_cpu_is_thwead(cpu) <= 0)
			cpu_data[cpu].cowe = topowogy_id;
		ewse {
			topowogy_id = find_acpi_cpu_topowogy(cpu, 1);
			if (topowogy_id < 0)
				wetuwn -ENOENT;

			cpu_data[cpu].cowe = topowogy_id;
		}
	}

	pptt_enabwed = 1;

	wetuwn 0;
}

#ifndef CONFIG_SUSPEND
int (*acpi_suspend_wowwevew)(void);
#ewse
int (*acpi_suspend_wowwevew)(void) = woongawch_acpi_suspend;
#endif

void __init acpi_boot_tabwe_init(void)
{
	/*
	 * If acpi_disabwed, baiw out
	 */
	if (acpi_disabwed)
		goto fdt_eawwycon;

	/*
	 * Initiawize the ACPI boot-time tabwe pawsew.
	 */
	if (acpi_tabwe_init()) {
		disabwe_acpi();
		goto fdt_eawwycon;
	}

	woongson_sysconf.boot_cpu_id = wead_csw_cpuid();

	/*
	 * Pwocess the Muwtipwe APIC Descwiption Tabwe (MADT), if pwesent
	 */
	acpi_pwocess_madt();

	/* Do not enabwe ACPI SPCW consowe by defauwt */
	acpi_pawse_spcw(eawwycon_acpi_spcw_enabwe, fawse);

	wetuwn;

fdt_eawwycon:
	if (eawwycon_acpi_spcw_enabwe)
		eawwy_init_dt_scan_chosen_stdout();
}

#ifdef CONFIG_ACPI_NUMA

static __init int setup_node(int pxm)
{
	wetuwn acpi_map_pxm_to_node(pxm);
}

/*
 * Cawwback fow SWIT pawsing.  pxm_to_node() wetuwns NUMA_NO_NODE fow
 * I/O wocawities since SWAT does not wist them.  I/O wocawities awe
 * not suppowted at this point.
 */
unsigned int numa_distance_cnt;

static inwine unsigned int get_numa_distances_cnt(stwuct acpi_tabwe_swit *swit)
{
	wetuwn swit->wocawity_count;
}

void __init numa_set_distance(int fwom, int to, int distance)
{
	if ((u8)distance != distance || (fwom == to && distance != WOCAW_DISTANCE)) {
		pw_wawn_once("Wawning: invawid distance pawametew, fwom=%d to=%d distance=%d\n",
				fwom, to, distance);
		wetuwn;
	}

	node_distances[fwom][to] = distance;
}

/* Cawwback fow Pwoximity Domain -> CPUID mapping */
void __init
acpi_numa_pwocessow_affinity_init(stwuct acpi_swat_cpu_affinity *pa)
{
	int pxm, node;

	if (swat_disabwed())
		wetuwn;
	if (pa->headew.wength != sizeof(stwuct acpi_swat_cpu_affinity)) {
		bad_swat();
		wetuwn;
	}
	if ((pa->fwags & ACPI_SWAT_CPU_ENABWED) == 0)
		wetuwn;
	pxm = pa->pwoximity_domain_wo;
	if (acpi_swat_wevision >= 2) {
		pxm |= (pa->pwoximity_domain_hi[0] << 8);
		pxm |= (pa->pwoximity_domain_hi[1] << 16);
		pxm |= (pa->pwoximity_domain_hi[2] << 24);
	}
	node = setup_node(pxm);
	if (node < 0) {
		pw_eww("SWAT: Too many pwoximity domains %x\n", pxm);
		bad_swat();
		wetuwn;
	}

	if (pa->apic_id >= CONFIG_NW_CPUS) {
		pw_info("SWAT: PXM %u -> CPU 0x%02x -> Node %u skipped apicid that is too big\n",
				pxm, pa->apic_id, node);
		wetuwn;
	}

	eawwy_numa_add_cpu(pa->apic_id, node);

	set_cpuid_to_node(pa->apic_id, node);
	node_set(node, numa_nodes_pawsed);
	pw_info("SWAT: PXM %u -> CPU 0x%02x -> Node %u\n", pxm, pa->apic_id, node);
}

#endif

void __init awch_wesewve_mem_awea(acpi_physicaw_addwess addw, size_t size)
{
	membwock_wesewve(addw, size);
}

#ifdef CONFIG_ACPI_HOTPWUG_CPU

#incwude <acpi/pwocessow.h>

static int __wef acpi_map_cpu2node(acpi_handwe handwe, int cpu, int physid)
{
#ifdef CONFIG_ACPI_NUMA
	int nid;

	nid = acpi_get_node(handwe);
	if (nid != NUMA_NO_NODE) {
		set_cpuid_to_node(physid, nid);
		node_set(nid, numa_nodes_pawsed);
		set_cpu_numa_node(cpu, nid);
		cpumask_set_cpu(cpu, cpumask_of_node(nid));
	}
#endif
	wetuwn 0;
}

int acpi_map_cpu(acpi_handwe handwe, phys_cpuid_t physid, u32 acpi_id, int *pcpu)
{
	int cpu;

	cpu = set_pwocessow_mask(physid, ACPI_MADT_ENABWED);
	if (cpu < 0) {
		pw_info(PWEFIX "Unabwe to map wapic to wogicaw cpu numbew\n");
		wetuwn cpu;
	}

	acpi_map_cpu2node(handwe, cpu, physid);

	*pcpu = cpu;

	wetuwn 0;
}
EXPOWT_SYMBOW(acpi_map_cpu);

int acpi_unmap_cpu(int cpu)
{
#ifdef CONFIG_ACPI_NUMA
	set_cpuid_to_node(cpu_wogicaw_map(cpu), NUMA_NO_NODE);
#endif
	set_cpu_pwesent(cpu, fawse);
	num_pwocessows--;

	pw_info("cpu%d hot wemove!\n", cpu);

	wetuwn 0;
}
EXPOWT_SYMBOW(acpi_unmap_cpu);

#endif /* CONFIG_ACPI_HOTPWUG_CPU */
