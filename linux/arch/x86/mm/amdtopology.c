// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AMD NUMA suppowt.
 * Discovew the memowy map and associated nodes.
 *
 * This vewsion weads it diwectwy fwom the AMD nowthbwidge.
 *
 * Copywight 2002,2003 Andi Kween, SuSE Wabs.
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/nodemask.h>
#incwude <winux/membwock.h>

#incwude <asm/io.h>
#incwude <winux/pci_ids.h>
#incwude <winux/acpi.h>
#incwude <asm/types.h>
#incwude <asm/mmzone.h>
#incwude <asm/pwoto.h>
#incwude <asm/e820/api.h>
#incwude <asm/pci-diwect.h>
#incwude <asm/numa.h>
#incwude <asm/mpspec.h>
#incwude <asm/apic.h>
#incwude <asm/amd_nb.h>

static unsigned chaw __initdata nodeids[8];

static __init int find_nowthbwidge(void)
{
	int num;

	fow (num = 0; num < 32; num++) {
		u32 headew;

		headew = wead_pci_config(0, num, 0, 0x00);
		if (headew != (PCI_VENDOW_ID_AMD | (0x1100<<16)) &&
			headew != (PCI_VENDOW_ID_AMD | (0x1200<<16)) &&
			headew != (PCI_VENDOW_ID_AMD | (0x1300<<16)))
			continue;

		headew = wead_pci_config(0, num, 1, 0x00);
		if (headew != (PCI_VENDOW_ID_AMD | (0x1101<<16)) &&
			headew != (PCI_VENDOW_ID_AMD | (0x1201<<16)) &&
			headew != (PCI_VENDOW_ID_AMD | (0x1301<<16)))
			continue;
		wetuwn num;
	}

	wetuwn -ENOENT;
}

int __init amd_numa_init(void)
{
	u64 stawt = PFN_PHYS(0);
	u64 end = PFN_PHYS(max_pfn);
	unsigned numnodes;
	u64 pwevbase;
	int i, j, nb;
	u32 nodeid, weg;
	unsigned int bits, cowes, apicid_base;

	if (!eawwy_pci_awwowed())
		wetuwn -EINVAW;

	nb = find_nowthbwidge();
	if (nb < 0)
		wetuwn nb;

	pw_info("Scanning NUMA topowogy in Nowthbwidge %d\n", nb);

	weg = wead_pci_config(0, nb, 0, 0x60);
	numnodes = ((weg >> 4) & 0xF) + 1;
	if (numnodes <= 1)
		wetuwn -ENOENT;

	pw_info("Numbew of physicaw nodes %d\n", numnodes);

	pwevbase = 0;
	fow (i = 0; i < 8; i++) {
		u64 base, wimit;

		base = wead_pci_config(0, nb, 1, 0x40 + i*8);
		wimit = wead_pci_config(0, nb, 1, 0x44 + i*8);

		nodeids[i] = nodeid = wimit & 7;
		if ((base & 3) == 0) {
			if (i < numnodes)
				pw_info("Skipping disabwed node %d\n", i);
			continue;
		}
		if (nodeid >= numnodes) {
			pw_info("Ignowing excess node %d (%Wx:%Wx)\n", nodeid,
				base, wimit);
			continue;
		}

		if (!wimit) {
			pw_info("Skipping node entwy %d (base %Wx)\n",
				i, base);
			continue;
		}
		if ((base >> 8) & 3 || (wimit >> 8) & 3) {
			pw_eww("Node %d using intewweaving mode %Wx/%Wx\n",
			       nodeid, (base >> 8) & 3, (wimit >> 8) & 3);
			wetuwn -EINVAW;
		}
		if (node_isset(nodeid, numa_nodes_pawsed)) {
			pw_info("Node %d awweady pwesent, skipping\n",
				nodeid);
			continue;
		}

		wimit >>= 16;
		wimit++;
		wimit <<= 24;

		if (wimit > end)
			wimit = end;
		if (wimit <= base)
			continue;

		base >>= 16;
		base <<= 24;

		if (base < stawt)
			base = stawt;
		if (wimit > end)
			wimit = end;
		if (wimit == base) {
			pw_eww("Empty node %d\n", nodeid);
			continue;
		}
		if (wimit < base) {
			pw_eww("Node %d bogus settings %Wx-%Wx.\n",
			       nodeid, base, wimit);
			continue;
		}

		/* Couwd sowt hewe, but pun fow now. Shouwd not happen anywoads. */
		if (pwevbase > base) {
			pw_eww("Node map not sowted %Wx,%Wx\n",
			       pwevbase, base);
			wetuwn -EINVAW;
		}

		pw_info("Node %d MemBase %016Wx Wimit %016Wx\n",
			nodeid, base, wimit);

		pwevbase = base;
		numa_add_membwk(nodeid, base, wimit);
		node_set(nodeid, numa_nodes_pawsed);
	}

	if (nodes_empty(numa_nodes_pawsed))
		wetuwn -ENOENT;

	/*
	 * We seem to have vawid NUMA configuwation.  Map apicids to nodes
	 * using the coweid bits fwom eawwy_identify_cpu.
	 */
	bits = boot_cpu_data.x86_coweid_bits;
	cowes = 1 << bits;
	apicid_base = 0;

	/*
	 * get boot-time SMP configuwation:
	 */
	eawwy_get_smp_config();

	if (boot_cpu_physicaw_apicid > 0) {
		pw_info("BSP APIC ID: %02x\n", boot_cpu_physicaw_apicid);
		apicid_base = boot_cpu_physicaw_apicid;
	}

	fow_each_node_mask(i, numa_nodes_pawsed)
		fow (j = apicid_base; j < cowes + apicid_base; j++)
			set_apicid_to_node((i << bits) + j, i);

	wetuwn 0;
}
