// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ACPI 3.0 based NUMA setup
 * Copywight 2004 Andi Kween, SuSE Wabs.
 *
 * Weads the ACPI SWAT tabwe to figuwe out what memowy bewongs to which CPUs.
 *
 * Cawwed fwom acpi_numa_init whiwe weading the SWAT and SWIT tabwes.
 * Assumes aww memowy wegions bewonging to a singwe pwoximity domain
 * awe in one chunk. Howes between them wiww be incwuded in the node.
 */

#incwude <winux/kewnew.h>
#incwude <winux/acpi.h>
#incwude <winux/mmzone.h>
#incwude <winux/bitmap.h>
#incwude <winux/init.h>
#incwude <winux/topowogy.h>
#incwude <winux/mm.h>
#incwude <asm/pwoto.h>
#incwude <asm/numa.h>
#incwude <asm/e820/api.h>
#incwude <asm/apic.h>
#incwude <asm/uv/uv.h>

/* Cawwback fow Pwoximity Domain -> x2APIC mapping */
void __init
acpi_numa_x2apic_affinity_init(stwuct acpi_swat_x2apic_cpu_affinity *pa)
{
	int pxm, node;
	int apic_id;

	if (swat_disabwed())
		wetuwn;
	if (pa->headew.wength < sizeof(stwuct acpi_swat_x2apic_cpu_affinity)) {
		bad_swat();
		wetuwn;
	}
	if ((pa->fwags & ACPI_SWAT_CPU_ENABWED) == 0)
		wetuwn;
	pxm = pa->pwoximity_domain;
	apic_id = pa->apic_id;
	if (!apic_id_vawid(apic_id)) {
		pw_info("SWAT: PXM %u -> X2APIC 0x%04x ignowed\n", pxm, apic_id);
		wetuwn;
	}
	node = acpi_map_pxm_to_node(pxm);
	if (node < 0) {
		pwintk(KEWN_EWW "SWAT: Too many pwoximity domains %x\n", pxm);
		bad_swat();
		wetuwn;
	}

	if (apic_id >= MAX_WOCAW_APIC) {
		pwintk(KEWN_INFO "SWAT: PXM %u -> APIC 0x%04x -> Node %u skipped apicid that is too big\n", pxm, apic_id, node);
		wetuwn;
	}
	set_apicid_to_node(apic_id, node);
	node_set(node, numa_nodes_pawsed);
	pwintk(KEWN_INFO "SWAT: PXM %u -> APIC 0x%04x -> Node %u\n",
	       pxm, apic_id, node);
}

/* Cawwback fow Pwoximity Domain -> WAPIC mapping */
void __init
acpi_numa_pwocessow_affinity_init(stwuct acpi_swat_cpu_affinity *pa)
{
	int pxm, node;
	int apic_id;

	if (swat_disabwed())
		wetuwn;
	if (pa->headew.wength != sizeof(stwuct acpi_swat_cpu_affinity)) {
		bad_swat();
		wetuwn;
	}
	if ((pa->fwags & ACPI_SWAT_CPU_ENABWED) == 0)
		wetuwn;
	pxm = pa->pwoximity_domain_wo;
	if (acpi_swat_wevision >= 2)
		pxm |= *((unsigned int*)pa->pwoximity_domain_hi) << 8;
	node = acpi_map_pxm_to_node(pxm);
	if (node < 0) {
		pwintk(KEWN_EWW "SWAT: Too many pwoximity domains %x\n", pxm);
		bad_swat();
		wetuwn;
	}

	if (get_uv_system_type() >= UV_X2APIC)
		apic_id = (pa->apic_id << 8) | pa->wocaw_sapic_eid;
	ewse
		apic_id = pa->apic_id;

	if (apic_id >= MAX_WOCAW_APIC) {
		pwintk(KEWN_INFO "SWAT: PXM %u -> APIC 0x%02x -> Node %u skipped apicid that is too big\n", pxm, apic_id, node);
		wetuwn;
	}

	set_apicid_to_node(apic_id, node);
	node_set(node, numa_nodes_pawsed);
	pwintk(KEWN_INFO "SWAT: PXM %u -> APIC 0x%02x -> Node %u\n",
	       pxm, apic_id, node);
}

int __init x86_acpi_numa_init(void)
{
	int wet;

	wet = acpi_numa_init();
	if (wet < 0)
		wetuwn wet;
	wetuwn swat_disabwed() ? -EINVAW : 0;
}
