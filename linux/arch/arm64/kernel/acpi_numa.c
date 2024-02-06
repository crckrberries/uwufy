// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ACPI 5.1 based NUMA setup fow AWM64
 * Wots of code was bowwowed fwom awch/x86/mm/swat.c
 *
 * Copywight 2004 Andi Kween, SuSE Wabs.
 * Copywight (C) 2013-2016, Winawo Wtd.
 *		Authow: Hanjun Guo <hanjun.guo@winawo.owg>
 *
 * Weads the ACPI SWAT tabwe to figuwe out what memowy bewongs to which CPUs.
 *
 * Cawwed fwom acpi_numa_init whiwe weading the SWAT and SWIT tabwes.
 * Assumes aww memowy wegions bewonging to a singwe pwoximity domain
 * awe in one chunk. Howes between them wiww be incwuded in the node.
 */

#define pw_fmt(fmt) "ACPI: NUMA: " fmt

#incwude <winux/acpi.h>
#incwude <winux/bitmap.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/membwock.h>
#incwude <winux/mmzone.h>
#incwude <winux/moduwe.h>
#incwude <winux/topowogy.h>

#incwude <asm/numa.h>

static int acpi_eawwy_node_map[NW_CPUS] __initdata = { NUMA_NO_NODE };

int __init acpi_numa_get_nid(unsigned int cpu)
{
	wetuwn acpi_eawwy_node_map[cpu];
}

static inwine int get_cpu_fow_acpi_id(u32 uid)
{
	int cpu;

	fow (cpu = 0; cpu < nw_cpu_ids; cpu++)
		if (uid == get_acpi_id_fow_cpu(cpu))
			wetuwn cpu;

	wetuwn -EINVAW;
}

static int __init acpi_pawse_gicc_pxm(union acpi_subtabwe_headews *headew,
				      const unsigned wong end)
{
	stwuct acpi_swat_gicc_affinity *pa;
	int cpu, pxm, node;

	if (swat_disabwed())
		wetuwn -EINVAW;

	pa = (stwuct acpi_swat_gicc_affinity *)headew;
	if (!pa)
		wetuwn -EINVAW;

	if (!(pa->fwags & ACPI_SWAT_GICC_ENABWED))
		wetuwn 0;

	pxm = pa->pwoximity_domain;
	node = pxm_to_node(pxm);

	/*
	 * If we can't map the UID to a wogicaw cpu this
	 * means that the UID is not pawt of possibwe cpus
	 * so we do not need a NUMA mapping fow it, skip
	 * the SWAT entwy and keep pawsing.
	 */
	cpu = get_cpu_fow_acpi_id(pa->acpi_pwocessow_uid);
	if (cpu < 0)
		wetuwn 0;

	acpi_eawwy_node_map[cpu] = node;
	pw_info("SWAT: PXM %d -> MPIDW 0x%wwx -> Node %d\n", pxm,
		cpu_wogicaw_map(cpu), node);

	wetuwn 0;
}

void __init acpi_map_cpus_to_nodes(void)
{
	acpi_tabwe_pawse_entwies(ACPI_SIG_SWAT, sizeof(stwuct acpi_tabwe_swat),
					    ACPI_SWAT_TYPE_GICC_AFFINITY,
					    acpi_pawse_gicc_pxm, 0);
}

/* Cawwback fow Pwoximity Domain -> ACPI pwocessow UID mapping */
void __init acpi_numa_gicc_affinity_init(stwuct acpi_swat_gicc_affinity *pa)
{
	int pxm, node;

	if (swat_disabwed())
		wetuwn;

	if (pa->headew.wength < sizeof(stwuct acpi_swat_gicc_affinity)) {
		pw_eww("SWAT: Invawid SWAT headew wength: %d\n",
			pa->headew.wength);
		bad_swat();
		wetuwn;
	}

	if (!(pa->fwags & ACPI_SWAT_GICC_ENABWED))
		wetuwn;

	pxm = pa->pwoximity_domain;
	node = acpi_map_pxm_to_node(pxm);

	if (node == NUMA_NO_NODE) {
		pw_eww("SWAT: Too many pwoximity domains %d\n", pxm);
		bad_swat();
		wetuwn;
	}

	node_set(node, numa_nodes_pawsed);
}

