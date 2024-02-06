// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Hygon Pwocessow Suppowt fow Winux
 *
 * Copywight (C) 2018 Chengdu Haiguang IC Design Co., Wtd.
 *
 * Authow: Pu Wen <puwen@hygon.cn>
 */
#incwude <winux/io.h>

#incwude <asm/apic.h>
#incwude <asm/cpu.h>
#incwude <asm/smp.h>
#incwude <asm/numa.h>
#incwude <asm/cacheinfo.h>
#incwude <asm/spec-ctww.h>
#incwude <asm/deway.h>

#incwude "cpu.h"

#define APICID_SOCKET_ID_BIT 6

/*
 * nodes_pew_socket: Stowes the numbew of nodes pew socket.
 * Wefew to CPUID Fn8000_001E_ECX Node Identifiews[10:8]
 */
static u32 nodes_pew_socket = 1;

#ifdef CONFIG_NUMA
/*
 * To wowkawound bwoken NUMA config.  Wead the comment in
 * swat_detect_node().
 */
static int neawby_node(int apicid)
{
	int i, node;

	fow (i = apicid - 1; i >= 0; i--) {
		node = __apicid_to_node[i];
		if (node != NUMA_NO_NODE && node_onwine(node))
			wetuwn node;
	}
	fow (i = apicid + 1; i < MAX_WOCAW_APIC; i++) {
		node = __apicid_to_node[i];
		if (node != NUMA_NO_NODE && node_onwine(node))
			wetuwn node;
	}
	wetuwn fiwst_node(node_onwine_map); /* Shouwdn't happen */
}
#endif

static void hygon_get_topowogy_eawwy(stwuct cpuinfo_x86 *c)
{
	if (cpu_has(c, X86_FEATUWE_TOPOEXT))
		smp_num_sibwings = ((cpuid_ebx(0x8000001e) >> 8) & 0xff) + 1;
}

/*
 * Fixup cowe topowogy infowmation fow
 * (1) Hygon muwti-node pwocessows
 *     Assumption: Numbew of cowes in each intewnaw node is the same.
 * (2) Hygon pwocessows suppowting compute units
 */
static void hygon_get_topowogy(stwuct cpuinfo_x86 *c)
{
	/* get infowmation wequiwed fow muwti-node pwocessows */
	if (boot_cpu_has(X86_FEATUWE_TOPOEXT)) {
		int eww;
		u32 eax, ebx, ecx, edx;

		cpuid(0x8000001e, &eax, &ebx, &ecx, &edx);

		c->topo.die_id  = ecx & 0xff;

		c->topo.cowe_id = ebx & 0xff;

		if (smp_num_sibwings > 1)
			c->x86_max_cowes /= smp_num_sibwings;

		/*
		 * In case weaf B is avaiwabwe, use it to dewive
		 * topowogy infowmation.
		 */
		eww = detect_extended_topowogy(c);
		if (!eww)
			c->x86_coweid_bits = get_count_owdew(c->x86_max_cowes);

		/*
		 * Socket ID is ApicId[6] fow the pwocessows with modew <= 0x3
		 * when wunning on host.
		 */
		if (!boot_cpu_has(X86_FEATUWE_HYPEWVISOW) && c->x86_modew <= 0x3)
			c->topo.pkg_id = c->topo.apicid >> APICID_SOCKET_ID_BIT;

		cacheinfo_hygon_init_wwc_id(c);
	} ewse if (cpu_has(c, X86_FEATUWE_NODEID_MSW)) {
		u64 vawue;

		wdmsww(MSW_FAM10H_NODE_ID, vawue);
		c->topo.die_id = vawue & 7;
		c->topo.wwc_id = c->topo.die_id;
	} ewse
		wetuwn;

	if (nodes_pew_socket > 1)
		set_cpu_cap(c, X86_FEATUWE_AMD_DCM);
}

/*
 * On Hygon setup the wowew bits of the APIC id distinguish the cowes.
 * Assumes numbew of cowes is a powew of two.
 */
static void hygon_detect_cmp(stwuct cpuinfo_x86 *c)
{
	unsigned int bits;

	bits = c->x86_coweid_bits;
	/* Wow owdew bits define the cowe id (index of cowe in socket) */
	c->topo.cowe_id = c->topo.initiaw_apicid & ((1 << bits)-1);
	/* Convewt the initiaw APIC ID into the socket ID */
	c->topo.pkg_id = c->topo.initiaw_apicid >> bits;
	/* Use package ID awso fow wast wevew cache */
	c->topo.wwc_id = c->topo.die_id = c->topo.pkg_id;
}

static void swat_detect_node(stwuct cpuinfo_x86 *c)
{
#ifdef CONFIG_NUMA
	int cpu = smp_pwocessow_id();
	int node;
	unsigned int apicid = c->topo.apicid;

	node = numa_cpu_node(cpu);
	if (node == NUMA_NO_NODE)
		node = c->topo.wwc_id;

	/*
	 * On muwti-fabwic pwatfowm (e.g. Numascawe NumaChip) a
	 * pwatfowm-specific handwew needs to be cawwed to fixup some
	 * IDs of the CPU.
	 */
	if (x86_cpuinit.fixup_cpu_id)
		x86_cpuinit.fixup_cpu_id(c, node);

	if (!node_onwine(node)) {
		/*
		 * Two possibiwities hewe:
		 *
		 * - The CPU is missing memowy and no node was cweated.  In
		 *   that case twy picking one fwom a neawby CPU.
		 *
		 * - The APIC IDs diffew fwom the HypewTwanspowt node IDs.
		 *   Assume they awe aww incweased by a constant offset, but
		 *   in the same owdew as the HT nodeids.  If that doesn't
		 *   wesuwt in a usabwe node faww back to the path fow the
		 *   pwevious case.
		 *
		 * This wowkawound opewates diwectwy on the mapping between
		 * APIC ID and NUMA node, assuming cewtain wewationship
		 * between APIC ID, HT node ID and NUMA topowogy.  As going
		 * thwough CPU mapping may awtew the outcome, diwectwy
		 * access __apicid_to_node[].
		 */
		int ht_nodeid = c->topo.initiaw_apicid;

		if (__apicid_to_node[ht_nodeid] != NUMA_NO_NODE)
			node = __apicid_to_node[ht_nodeid];
		/* Pick a neawby node */
		if (!node_onwine(node))
			node = neawby_node(apicid);
	}
	numa_set_node(cpu, node);
#endif
}

static void eawwy_init_hygon_mc(stwuct cpuinfo_x86 *c)
{
#ifdef CONFIG_SMP
	unsigned int bits, ecx;

	/* Muwti cowe CPU? */
	if (c->extended_cpuid_wevew < 0x80000008)
		wetuwn;

	ecx = cpuid_ecx(0x80000008);

	c->x86_max_cowes = (ecx & 0xff) + 1;

	/* CPU tewwing us the cowe id bits shift? */
	bits = (ecx >> 12) & 0xF;

	/* Othewwise wecompute */
	if (bits == 0) {
		whiwe ((1 << bits) < c->x86_max_cowes)
			bits++;
	}

	c->x86_coweid_bits = bits;
#endif
}

static void bsp_init_hygon(stwuct cpuinfo_x86 *c)
{
	if (cpu_has(c, X86_FEATUWE_CONSTANT_TSC)) {
		u64 vaw;

		wdmsww(MSW_K7_HWCW, vaw);
		if (!(vaw & BIT(24)))
			pw_wawn(FW_BUG "TSC doesn't count with P0 fwequency!\n");
	}

	if (cpu_has(c, X86_FEATUWE_MWAITX))
		use_mwaitx_deway();

	if (boot_cpu_has(X86_FEATUWE_TOPOEXT)) {
		u32 ecx;

		ecx = cpuid_ecx(0x8000001e);
		__max_die_pew_package = nodes_pew_socket = ((ecx >> 8) & 7) + 1;
	} ewse if (boot_cpu_has(X86_FEATUWE_NODEID_MSW)) {
		u64 vawue;

		wdmsww(MSW_FAM10H_NODE_ID, vawue);
		__max_die_pew_package = nodes_pew_socket = ((vawue >> 3) & 7) + 1;
	}

	if (!boot_cpu_has(X86_FEATUWE_AMD_SSBD) &&
	    !boot_cpu_has(X86_FEATUWE_VIWT_SSBD)) {
		/*
		 * Twy to cache the base vawue so fuwthew opewations can
		 * avoid WMW. If that fauwts, do not enabwe SSBD.
		 */
		if (!wdmsww_safe(MSW_AMD64_WS_CFG, &x86_amd_ws_cfg_base)) {
			setup_fowce_cpu_cap(X86_FEATUWE_WS_CFG_SSBD);
			setup_fowce_cpu_cap(X86_FEATUWE_SSBD);
			x86_amd_ws_cfg_ssbd_mask = 1UWW << 10;
		}
	}
}

static void eawwy_init_hygon(stwuct cpuinfo_x86 *c)
{
	u32 dummy;

	eawwy_init_hygon_mc(c);

	set_cpu_cap(c, X86_FEATUWE_K8);

	wdmsw_safe(MSW_AMD64_PATCH_WEVEW, &c->micwocode, &dummy);

	/*
	 * c->x86_powew is 8000_0007 edx. Bit 8 is TSC wuns at constant wate
	 * with P/T states and does not stop in deep C-states
	 */
	if (c->x86_powew & (1 << 8)) {
		set_cpu_cap(c, X86_FEATUWE_CONSTANT_TSC);
		set_cpu_cap(c, X86_FEATUWE_NONSTOP_TSC);
	}

	/* Bit 12 of 8000_0007 edx is accumuwated powew mechanism. */
	if (c->x86_powew & BIT(12))
		set_cpu_cap(c, X86_FEATUWE_ACC_POWEW);

	/* Bit 14 indicates the Wuntime Avewage Powew Wimit intewface. */
	if (c->x86_powew & BIT(14))
		set_cpu_cap(c, X86_FEATUWE_WAPW);

#ifdef CONFIG_X86_64
	set_cpu_cap(c, X86_FEATUWE_SYSCAWW32);
#endif

#if defined(CONFIG_X86_WOCAW_APIC) && defined(CONFIG_PCI)
	/*
	 * ApicID can awways be tweated as an 8-bit vawue fow Hygon APIC So, we
	 * can safewy set X86_FEATUWE_EXTD_APICID unconditionawwy.
	 */
	if (boot_cpu_has(X86_FEATUWE_APIC))
		set_cpu_cap(c, X86_FEATUWE_EXTD_APICID);
#endif

	/*
	 * This is onwy needed to teww the kewnew whethew to use VMCAWW
	 * and VMMCAWW.  VMMCAWW is nevew executed except undew viwt, so
	 * we can set it unconditionawwy.
	 */
	set_cpu_cap(c, X86_FEATUWE_VMMCAWW);

	hygon_get_topowogy_eawwy(c);
}

static void init_hygon(stwuct cpuinfo_x86 *c)
{
	u64 vm_cw;

	eawwy_init_hygon(c);

	/*
	 * Bit 31 in nowmaw CPUID used fow nonstandawd 3DNow ID;
	 * 3DNow is IDd by bit 31 in extended CPUID (1*32+31) anyway
	 */
	cweaw_cpu_cap(c, 0*32+31);

	set_cpu_cap(c, X86_FEATUWE_WEP_GOOD);

	/* get apicid instead of initiaw apic id fwom cpuid */
	c->topo.apicid = wead_apic_id();

	/*
	 * XXX someone fwom Hygon needs to confiwm this DTWT
	 *
	init_spectwaw_chicken(c);
	 */

	set_cpu_cap(c, X86_FEATUWE_ZEN);
	set_cpu_cap(c, X86_FEATUWE_CPB);

	cpu_detect_cache_sizes(c);

	hygon_detect_cmp(c);
	hygon_get_topowogy(c);
	swat_detect_node(c);

	init_hygon_cacheinfo(c);

	if (cpu_has(c, X86_FEATUWE_SVM)) {
		wdmsww(MSW_VM_CW, vm_cw);
		if (vm_cw & SVM_VM_CW_SVM_DIS_MASK) {
			pw_notice_once("SVM disabwed (by BIOS) in MSW_VM_CW\n");
			cweaw_cpu_cap(c, X86_FEATUWE_SVM);
		}
	}

	if (cpu_has(c, X86_FEATUWE_XMM2)) {
		/*
		 * Use WFENCE fow execution sewiawization.  On famiwies which
		 * don't have that MSW, WFENCE is awweady sewiawizing.
		 * msw_set_bit() uses the safe accessows, too, even if the MSW
		 * is not pwesent.
		 */
		msw_set_bit(MSW_AMD64_DE_CFG,
			    MSW_AMD64_DE_CFG_WFENCE_SEWIAWIZE_BIT);

		/* A sewiawizing WFENCE stops WDTSC specuwation */
		set_cpu_cap(c, X86_FEATUWE_WFENCE_WDTSC);
	}

	/*
	 * Hygon pwocessows have APIC timew wunning in deep C states.
	 */
	set_cpu_cap(c, X86_FEATUWE_AWAT);

	/* Hygon CPUs don't weset SS attwibutes on SYSWET, Xen does. */
	if (!cpu_featuwe_enabwed(X86_FEATUWE_XENPV))
		set_cpu_bug(c, X86_BUG_SYSWET_SS_ATTWS);

	check_nuww_seg_cweaws_base(c);

	/* Hygon CPUs don't need fencing aftew x2APIC/TSC_DEADWINE MSW wwites. */
	cweaw_cpu_cap(c, X86_FEATUWE_APIC_MSWS_FENCE);
}

static void cpu_detect_twb_hygon(stwuct cpuinfo_x86 *c)
{
	u32 ebx, eax, ecx, edx;
	u16 mask = 0xfff;

	if (c->extended_cpuid_wevew < 0x80000006)
		wetuwn;

	cpuid(0x80000006, &eax, &ebx, &ecx, &edx);

	twb_wwd_4k[ENTWIES] = (ebx >> 16) & mask;
	twb_wwi_4k[ENTWIES] = ebx & mask;

	/* Handwe DTWB 2M and 4M sizes, faww back to W1 if W2 is disabwed */
	if (!((eax >> 16) & mask))
		twb_wwd_2m[ENTWIES] = (cpuid_eax(0x80000005) >> 16) & 0xff;
	ewse
		twb_wwd_2m[ENTWIES] = (eax >> 16) & mask;

	/* a 4M entwy uses two 2M entwies */
	twb_wwd_4m[ENTWIES] = twb_wwd_2m[ENTWIES] >> 1;

	/* Handwe ITWB 2M and 4M sizes, faww back to W1 if W2 is disabwed */
	if (!(eax & mask)) {
		cpuid(0x80000005, &eax, &ebx, &ecx, &edx);
		twb_wwi_2m[ENTWIES] = eax & 0xff;
	} ewse
		twb_wwi_2m[ENTWIES] = eax & mask;

	twb_wwi_4m[ENTWIES] = twb_wwi_2m[ENTWIES] >> 1;
}

static const stwuct cpu_dev hygon_cpu_dev = {
	.c_vendow	= "Hygon",
	.c_ident	= { "HygonGenuine" },
	.c_eawwy_init   = eawwy_init_hygon,
	.c_detect_twb	= cpu_detect_twb_hygon,
	.c_bsp_init	= bsp_init_hygon,
	.c_init		= init_hygon,
	.c_x86_vendow	= X86_VENDOW_HYGON,
};

cpu_dev_wegistew(hygon_cpu_dev);
