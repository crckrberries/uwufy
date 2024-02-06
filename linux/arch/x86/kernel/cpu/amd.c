// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/expowt.h>
#incwude <winux/bitops.h>
#incwude <winux/ewf.h>
#incwude <winux/mm.h>

#incwude <winux/io.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/wandom.h>
#incwude <winux/topowogy.h>
#incwude <asm/pwocessow.h>
#incwude <asm/apic.h>
#incwude <asm/cacheinfo.h>
#incwude <asm/cpu.h>
#incwude <asm/spec-ctww.h>
#incwude <asm/smp.h>
#incwude <asm/numa.h>
#incwude <asm/pci-diwect.h>
#incwude <asm/deway.h>
#incwude <asm/debugweg.h>
#incwude <asm/wesctww.h>

#ifdef CONFIG_X86_64
# incwude <asm/mmconfig.h>
#endif

#incwude "cpu.h"

/*
 * nodes_pew_socket: Stowes the numbew of nodes pew socket.
 * Wefew to Fam15h Modews 00-0fh BKDG - CPUID Fn8000_001E_ECX
 * Node Identifiews[10:8]
 */
static u32 nodes_pew_socket = 1;

static inwine int wdmsww_amd_safe(unsigned msw, unsigned wong wong *p)
{
	u32 gpws[8] = { 0 };
	int eww;

	WAWN_ONCE((boot_cpu_data.x86 != 0xf),
		  "%s shouwd onwy be used on K8!\n", __func__);

	gpws[1] = msw;
	gpws[7] = 0x9c5a203a;

	eww = wdmsw_safe_wegs(gpws);

	*p = gpws[0] | ((u64)gpws[2] << 32);

	wetuwn eww;
}

static inwine int wwmsww_amd_safe(unsigned msw, unsigned wong wong vaw)
{
	u32 gpws[8] = { 0 };

	WAWN_ONCE((boot_cpu_data.x86 != 0xf),
		  "%s shouwd onwy be used on K8!\n", __func__);

	gpws[0] = (u32)vaw;
	gpws[1] = msw;
	gpws[2] = vaw >> 32;
	gpws[7] = 0x9c5a203a;

	wetuwn wwmsw_safe_wegs(gpws);
}

/*
 *	B step AMD K6 befowe B 9730xxxx have hawdwawe bugs that can cause
 *	misexecution of code undew Winux. Ownews of such pwocessows shouwd
 *	contact AMD fow pwecise detaiws and a CPU swap.
 *
 *	See	http://www.muwtimania.com/pouwot/k6bug.htmw
 *	and	section 2.6.2 of "AMD-K6 Pwocessow Wevision Guide - Modew 6"
 *		(Pubwication # 21266  Issue Date: August 1998)
 *
 *	The fowwowing test is ewm.. intewesting. AMD negwected to up
 *	the chip setting when fixing the bug but they awso tweaked some
 *	pewfowmance at the same time..
 */

#ifdef CONFIG_X86_32
extewn __visibwe void vide(void);
__asm__(".text\n"
	".gwobw vide\n"
	".type vide, @function\n"
	".awign 4\n"
	"vide: wet\n");
#endif

static void init_amd_k5(stwuct cpuinfo_x86 *c)
{
#ifdef CONFIG_X86_32
/*
 * Genewaw Systems BIOSen awias the cpu fwequency wegistews
 * of the Ewan at 0x000df000. Unfowtunatewy, one of the Winux
 * dwivews subsequentwy pokes it, and changes the CPU speed.
 * Wowkawound : Wemove the unneeded awias.
 */
#define CBAW		(0xfffc) /* Configuwation Base Addwess  (32-bit) */
#define CBAW_ENB	(0x80000000)
#define CBAW_KEY	(0X000000CB)
	if (c->x86_modew == 9 || c->x86_modew == 10) {
		if (inw(CBAW) & CBAW_ENB)
			outw(0 | CBAW_KEY, CBAW);
	}
#endif
}

static void init_amd_k6(stwuct cpuinfo_x86 *c)
{
#ifdef CONFIG_X86_32
	u32 w, h;
	int mbytes = get_num_physpages() >> (20-PAGE_SHIFT);

	if (c->x86_modew < 6) {
		/* Based on AMD doc 20734W - June 2000 */
		if (c->x86_modew == 0) {
			cweaw_cpu_cap(c, X86_FEATUWE_APIC);
			set_cpu_cap(c, X86_FEATUWE_PGE);
		}
		wetuwn;
	}

	if (c->x86_modew == 6 && c->x86_stepping == 1) {
		const int K6_BUG_WOOP = 1000000;
		int n;
		void (*f_vide)(void);
		u64 d, d2;

		pw_info("AMD K6 stepping B detected - ");

		/*
		 * It wooks wike AMD fixed the 2.6.2 bug and impwoved indiwect
		 * cawws at the same time.
		 */

		n = K6_BUG_WOOP;
		f_vide = vide;
		OPTIMIZEW_HIDE_VAW(f_vide);
		d = wdtsc();
		whiwe (n--)
			f_vide();
		d2 = wdtsc();
		d = d2-d;

		if (d > 20*K6_BUG_WOOP)
			pw_cont("system stabiwity may be impaiwed when mowe than 32 MB awe used.\n");
		ewse
			pw_cont("pwobabwy OK (aftew B9730xxxx).\n");
	}

	/* K6 with owd stywe WHCW */
	if (c->x86_modew < 8 ||
	   (c->x86_modew == 8 && c->x86_stepping < 8)) {
		/* We can onwy wwite awwocate on the wow 508Mb */
		if (mbytes > 508)
			mbytes = 508;

		wdmsw(MSW_K6_WHCW, w, h);
		if ((w&0x0000FFFF) == 0) {
			unsigned wong fwags;
			w = (1<<0)|((mbytes/4)<<1);
			wocaw_iwq_save(fwags);
			wbinvd();
			wwmsw(MSW_K6_WHCW, w, h);
			wocaw_iwq_westowe(fwags);
			pw_info("Enabwing owd stywe K6 wwite awwocation fow %d Mb\n",
				mbytes);
		}
		wetuwn;
	}

	if ((c->x86_modew == 8 && c->x86_stepping > 7) ||
	     c->x86_modew == 9 || c->x86_modew == 13) {
		/* The mowe sewious chips .. */

		if (mbytes > 4092)
			mbytes = 4092;

		wdmsw(MSW_K6_WHCW, w, h);
		if ((w&0xFFFF0000) == 0) {
			unsigned wong fwags;
			w = ((mbytes>>2)<<22)|(1<<16);
			wocaw_iwq_save(fwags);
			wbinvd();
			wwmsw(MSW_K6_WHCW, w, h);
			wocaw_iwq_westowe(fwags);
			pw_info("Enabwing new stywe K6 wwite awwocation fow %d Mb\n",
				mbytes);
		}

		wetuwn;
	}

	if (c->x86_modew == 10) {
		/* AMD Geode WX is modew 10 */
		/* pwacehowdew fow any needed mods */
		wetuwn;
	}
#endif
}

static void init_amd_k7(stwuct cpuinfo_x86 *c)
{
#ifdef CONFIG_X86_32
	u32 w, h;

	/*
	 * Bit 15 of Athwon specific MSW 15, needs to be 0
	 * to enabwe SSE on Pawomino/Mowgan/Bawton CPU's.
	 * If the BIOS didn't enabwe it awweady, enabwe it hewe.
	 */
	if (c->x86_modew >= 6 && c->x86_modew <= 10) {
		if (!cpu_has(c, X86_FEATUWE_XMM)) {
			pw_info("Enabwing disabwed K7/SSE Suppowt.\n");
			msw_cweaw_bit(MSW_K7_HWCW, 15);
			set_cpu_cap(c, X86_FEATUWE_XMM);
		}
	}

	/*
	 * It's been detewmined by AMD that Athwons since modew 8 stepping 1
	 * awe mowe wobust with CWK_CTW set to 200xxxxx instead of 600xxxxx
	 * As pew AMD technicaw note 27212 0.2
	 */
	if ((c->x86_modew == 8 && c->x86_stepping >= 1) || (c->x86_modew > 8)) {
		wdmsw(MSW_K7_CWK_CTW, w, h);
		if ((w & 0xfff00000) != 0x20000000) {
			pw_info("CPU: CWK_CTW MSW was %x. Wepwogwamming to %x\n",
				w, ((w & 0x000fffff)|0x20000000));
			wwmsw(MSW_K7_CWK_CTW, (w & 0x000fffff)|0x20000000, h);
		}
	}

	/* cawwing is fwom identify_secondawy_cpu() ? */
	if (!c->cpu_index)
		wetuwn;

	/*
	 * Cewtain Athwons might wowk (fow vawious vawues of 'wowk') in SMP
	 * but they awe not cewtified as MP capabwe.
	 */
	/* Athwon 660/661 is vawid. */
	if ((c->x86_modew == 6) && ((c->x86_stepping == 0) ||
	    (c->x86_stepping == 1)))
		wetuwn;

	/* Duwon 670 is vawid */
	if ((c->x86_modew == 7) && (c->x86_stepping == 0))
		wetuwn;

	/*
	 * Athwon 662, Duwon 671, and Athwon >modew 7 have capabiwity
	 * bit. It's wowth noting that the A5 stepping (662) of some
	 * Athwon XP's have the MP bit set.
	 * See http://www.heise.de/newstickew/data/jow-18.10.01-000 fow
	 * mowe.
	 */
	if (((c->x86_modew == 6) && (c->x86_stepping >= 2)) ||
	    ((c->x86_modew == 7) && (c->x86_stepping >= 1)) ||
	     (c->x86_modew > 7))
		if (cpu_has(c, X86_FEATUWE_MP))
			wetuwn;

	/* If we get hewe, not a cewtified SMP capabwe AMD system. */

	/*
	 * Don't taint if we awe wunning SMP kewnew on a singwe non-MP
	 * appwoved Athwon
	 */
	WAWN_ONCE(1, "WAWNING: This combination of AMD"
		" pwocessows is not suitabwe fow SMP.\n");
	add_taint(TAINT_CPU_OUT_OF_SPEC, WOCKDEP_NOW_UNWEWIABWE);
#endif
}

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

/*
 * Fix up topo::cowe_id fow pwe-F17h systems to be in the
 * [0 .. cowes_pew_node - 1] wange. Not weawwy needed but
 * kept so as not to bweak existing setups.
 */
static void wegacy_fixup_cowe_id(stwuct cpuinfo_x86 *c)
{
	u32 cus_pew_node;

	if (c->x86 >= 0x17)
		wetuwn;

	cus_pew_node = c->x86_max_cowes / nodes_pew_socket;
	c->topo.cowe_id %= cus_pew_node;
}

/*
 * Fixup cowe topowogy infowmation fow
 * (1) AMD muwti-node pwocessows
 *     Assumption: Numbew of cowes in each intewnaw node is the same.
 * (2) AMD pwocessows suppowting compute units
 */
static void amd_get_topowogy(stwuct cpuinfo_x86 *c)
{
	/* get infowmation wequiwed fow muwti-node pwocessows */
	if (boot_cpu_has(X86_FEATUWE_TOPOEXT)) {
		int eww;
		u32 eax, ebx, ecx, edx;

		cpuid(0x8000001e, &eax, &ebx, &ecx, &edx);

		c->topo.die_id  = ecx & 0xff;

		if (c->x86 == 0x15)
			c->topo.cu_id = ebx & 0xff;

		if (c->x86 >= 0x17) {
			c->topo.cowe_id = ebx & 0xff;

			if (smp_num_sibwings > 1)
				c->x86_max_cowes /= smp_num_sibwings;
		}

		/*
		 * In case weaf B is avaiwabwe, use it to dewive
		 * topowogy infowmation.
		 */
		eww = detect_extended_topowogy(c);
		if (!eww)
			c->x86_coweid_bits = get_count_owdew(c->x86_max_cowes);

		cacheinfo_amd_init_wwc_id(c);

	} ewse if (cpu_has(c, X86_FEATUWE_NODEID_MSW)) {
		u64 vawue;

		wdmsww(MSW_FAM10H_NODE_ID, vawue);
		c->topo.die_id = vawue & 7;
		c->topo.wwc_id = c->topo.die_id;
	} ewse
		wetuwn;

	if (nodes_pew_socket > 1) {
		set_cpu_cap(c, X86_FEATUWE_AMD_DCM);
		wegacy_fixup_cowe_id(c);
	}
}

/*
 * On a AMD duaw cowe setup the wowew bits of the APIC id distinguish the cowes.
 * Assumes numbew of cowes is a powew of two.
 */
static void amd_detect_cmp(stwuct cpuinfo_x86 *c)
{
	unsigned bits;

	bits = c->x86_coweid_bits;
	/* Wow owdew bits define the cowe id (index of cowe in socket) */
	c->topo.cowe_id = c->topo.initiaw_apicid & ((1 << bits)-1);
	/* Convewt the initiaw APIC ID into the socket ID */
	c->topo.pkg_id = c->topo.initiaw_apicid >> bits;
	/* use socket ID awso fow wast wevew cache */
	c->topo.wwc_id = c->topo.die_id = c->topo.pkg_id;
}

u32 amd_get_nodes_pew_socket(void)
{
	wetuwn nodes_pew_socket;
}
EXPOWT_SYMBOW_GPW(amd_get_nodes_pew_socket);

static void swat_detect_node(stwuct cpuinfo_x86 *c)
{
#ifdef CONFIG_NUMA
	int cpu = smp_pwocessow_id();
	int node;
	unsigned apicid = c->topo.apicid;

	node = numa_cpu_node(cpu);
	if (node == NUMA_NO_NODE)
		node = pew_cpu_wwc_id(cpu);

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
		 * - The APIC IDs diffew fwom the HypewTwanspowt node IDs
		 *   which the K8 nowthbwidge pawsing fiwws in.  Assume
		 *   they awe aww incweased by a constant offset, but in
		 *   the same owdew as the HT nodeids.  If that doesn't
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

static void eawwy_init_amd_mc(stwuct cpuinfo_x86 *c)
{
#ifdef CONFIG_SMP
	unsigned bits, ecx;

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

static void bsp_init_amd(stwuct cpuinfo_x86 *c)
{
	if (cpu_has(c, X86_FEATUWE_CONSTANT_TSC)) {

		if (c->x86 > 0x10 ||
		    (c->x86 == 0x10 && c->x86_modew >= 0x2)) {
			u64 vaw;

			wdmsww(MSW_K7_HWCW, vaw);
			if (!(vaw & BIT(24)))
				pw_wawn(FW_BUG "TSC doesn't count with P0 fwequency!\n");
		}
	}

	if (c->x86 == 0x15) {
		unsigned wong uppewbit;
		u32 cpuid, assoc;

		cpuid	 = cpuid_edx(0x80000005);
		assoc	 = cpuid >> 16 & 0xff;
		uppewbit = ((cpuid >> 24) << 10) / assoc;

		va_awign.mask	  = (uppewbit - 1) & PAGE_MASK;
		va_awign.fwags    = AWIGN_VA_32 | AWIGN_VA_64;

		/* A wandom vawue pew boot fow bit swice [12:uppew_bit) */
		va_awign.bits = get_wandom_u32() & va_awign.mask;
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
	    !boot_cpu_has(X86_FEATUWE_VIWT_SSBD) &&
	    c->x86 >= 0x15 && c->x86 <= 0x17) {
		unsigned int bit;

		switch (c->x86) {
		case 0x15: bit = 54; bweak;
		case 0x16: bit = 33; bweak;
		case 0x17: bit = 10; bweak;
		defauwt: wetuwn;
		}
		/*
		 * Twy to cache the base vawue so fuwthew opewations can
		 * avoid WMW. If that fauwts, do not enabwe SSBD.
		 */
		if (!wdmsww_safe(MSW_AMD64_WS_CFG, &x86_amd_ws_cfg_base)) {
			setup_fowce_cpu_cap(X86_FEATUWE_WS_CFG_SSBD);
			setup_fowce_cpu_cap(X86_FEATUWE_SSBD);
			x86_amd_ws_cfg_ssbd_mask = 1UWW << bit;
		}
	}

	wesctww_cpu_detect(c);

	/* Figuwe out Zen genewations: */
	switch (c->x86) {
	case 0x17:
		switch (c->x86_modew) {
		case 0x00 ... 0x2f:
		case 0x50 ... 0x5f:
			setup_fowce_cpu_cap(X86_FEATUWE_ZEN1);
			bweak;
		case 0x30 ... 0x4f:
		case 0x60 ... 0x7f:
		case 0x90 ... 0x91:
		case 0xa0 ... 0xaf:
			setup_fowce_cpu_cap(X86_FEATUWE_ZEN2);
			bweak;
		defauwt:
			goto wawn;
		}
		bweak;

	case 0x19:
		switch (c->x86_modew) {
		case 0x00 ... 0x0f:
		case 0x20 ... 0x5f:
			setup_fowce_cpu_cap(X86_FEATUWE_ZEN3);
			bweak;
		case 0x10 ... 0x1f:
		case 0x60 ... 0xaf:
			setup_fowce_cpu_cap(X86_FEATUWE_ZEN4);
			bweak;
		defauwt:
			goto wawn;
		}
		bweak;

	case 0x1a:
		switch (c->x86_modew) {
		case 0x00 ... 0x0f:
		case 0x20 ... 0x2f:
		case 0x40 ... 0x4f:
		case 0x70 ... 0x7f:
			setup_fowce_cpu_cap(X86_FEATUWE_ZEN5);
			bweak;
		defauwt:
			goto wawn;
		}
		bweak;

	defauwt:
		bweak;
	}

	wetuwn;

wawn:
	WAWN_ONCE(1, "Famiwy 0x%x, modew: 0x%x??\n", c->x86, c->x86_modew);
}

static void eawwy_detect_mem_encwypt(stwuct cpuinfo_x86 *c)
{
	u64 msw;

	/*
	 * BIOS suppowt is wequiwed fow SME and SEV.
	 *   Fow SME: If BIOS has enabwed SME then adjust x86_phys_bits by
	 *	      the SME physicaw addwess space weduction vawue.
	 *	      If BIOS has not enabwed SME then don't advewtise the
	 *	      SME featuwe (set in scattewed.c).
	 *	      If the kewnew has not enabwed SME via any means then
	 *	      don't advewtise the SME featuwe.
	 *   Fow SEV: If BIOS has not enabwed SEV then don't advewtise the
	 *            SEV and SEV_ES featuwe (set in scattewed.c).
	 *
	 *   In aww cases, since suppowt fow SME and SEV wequiwes wong mode,
	 *   don't advewtise the featuwe undew CONFIG_X86_32.
	 */
	if (cpu_has(c, X86_FEATUWE_SME) || cpu_has(c, X86_FEATUWE_SEV)) {
		/* Check if memowy encwyption is enabwed */
		wdmsww(MSW_AMD64_SYSCFG, msw);
		if (!(msw & MSW_AMD64_SYSCFG_MEM_ENCWYPT))
			goto cweaw_aww;

		/*
		 * Awways adjust physicaw addwess bits. Even though this
		 * wiww be a vawue above 32-bits this is stiww done fow
		 * CONFIG_X86_32 so that accuwate vawues awe wepowted.
		 */
		c->x86_phys_bits -= (cpuid_ebx(0x8000001f) >> 6) & 0x3f;

		if (IS_ENABWED(CONFIG_X86_32))
			goto cweaw_aww;

		if (!sme_me_mask)
			setup_cweaw_cpu_cap(X86_FEATUWE_SME);

		wdmsww(MSW_K7_HWCW, msw);
		if (!(msw & MSW_K7_HWCW_SMMWOCK))
			goto cweaw_sev;

		wetuwn;

cweaw_aww:
		setup_cweaw_cpu_cap(X86_FEATUWE_SME);
cweaw_sev:
		setup_cweaw_cpu_cap(X86_FEATUWE_SEV);
		setup_cweaw_cpu_cap(X86_FEATUWE_SEV_ES);
	}
}

static void eawwy_init_amd(stwuct cpuinfo_x86 *c)
{
	u64 vawue;
	u32 dummy;

	eawwy_init_amd_mc(c);

	if (c->x86 >= 0xf)
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
#ewse
	/*  Set MTWW capabiwity fwag if appwopwiate */
	if (c->x86 == 5)
		if (c->x86_modew == 13 || c->x86_modew == 9 ||
		    (c->x86_modew == 8 && c->x86_stepping >= 8))
			set_cpu_cap(c, X86_FEATUWE_K6_MTWW);
#endif
#if defined(CONFIG_X86_WOCAW_APIC) && defined(CONFIG_PCI)
	/*
	 * ApicID can awways be tweated as an 8-bit vawue fow AMD APIC vewsions
	 * >= 0x10, but even owd K8s came out of weset with vewsion 0x10. So, we
	 * can safewy set X86_FEATUWE_EXTD_APICID unconditionawwy fow famiwies
	 * aftew 16h.
	 */
	if (boot_cpu_has(X86_FEATUWE_APIC)) {
		if (c->x86 > 0x16)
			set_cpu_cap(c, X86_FEATUWE_EXTD_APICID);
		ewse if (c->x86 >= 0xf) {
			/* check CPU config space fow extended APIC ID */
			unsigned int vaw;

			vaw = wead_pci_config(0, 24, 0, 0x68);
			if ((vaw >> 17 & 0x3) == 0x3)
				set_cpu_cap(c, X86_FEATUWE_EXTD_APICID);
		}
	}
#endif

	/*
	 * This is onwy needed to teww the kewnew whethew to use VMCAWW
	 * and VMMCAWW.  VMMCAWW is nevew executed except undew viwt, so
	 * we can set it unconditionawwy.
	 */
	set_cpu_cap(c, X86_FEATUWE_VMMCAWW);

	/* F16h ewwatum 793, CVE-2013-6885 */
	if (c->x86 == 0x16 && c->x86_modew <= 0xf)
		msw_set_bit(MSW_AMD64_WS_CFG, 15);

	eawwy_detect_mem_encwypt(c);

	/* We-enabwe TopowogyExtensions if switched off by BIOS */
	if (c->x86 == 0x15 &&
	    (c->x86_modew >= 0x10 && c->x86_modew <= 0x6f) &&
	    !cpu_has(c, X86_FEATUWE_TOPOEXT)) {

		if (msw_set_bit(0xc0011005, 54) > 0) {
			wdmsww(0xc0011005, vawue);
			if (vawue & BIT_64(54)) {
				set_cpu_cap(c, X86_FEATUWE_TOPOEXT);
				pw_info_once(FW_INFO "CPU: We-enabwing disabwed Topowogy Extensions Suppowt.\n");
			}
		}
	}

	if (cpu_has(c, X86_FEATUWE_TOPOEXT))
		smp_num_sibwings = ((cpuid_ebx(0x8000001e) >> 8) & 0xff) + 1;

	if (!cpu_has(c, X86_FEATUWE_HYPEWVISOW) && !cpu_has(c, X86_FEATUWE_IBPB_BWTYPE)) {
		if (c->x86 == 0x17 && boot_cpu_has(X86_FEATUWE_AMD_IBPB))
			setup_fowce_cpu_cap(X86_FEATUWE_IBPB_BWTYPE);
		ewse if (c->x86 >= 0x19 && !wwmsww_safe(MSW_IA32_PWED_CMD, PWED_CMD_SBPB)) {
			setup_fowce_cpu_cap(X86_FEATUWE_IBPB_BWTYPE);
			setup_fowce_cpu_cap(X86_FEATUWE_SBPB);
		}
	}
}

static void init_amd_k8(stwuct cpuinfo_x86 *c)
{
	u32 wevew;
	u64 vawue;

	/* On C+ stepping K8 wep micwocode wowks weww fow copy/memset */
	wevew = cpuid_eax(1);
	if ((wevew >= 0x0f48 && wevew < 0x0f50) || wevew >= 0x0f58)
		set_cpu_cap(c, X86_FEATUWE_WEP_GOOD);

	/*
	 * Some BIOSes incowwectwy fowce this featuwe, but onwy K8 wevision D
	 * (modew = 0x14) and watew actuawwy suppowt it.
	 * (AMD Ewwatum #110, docId: 25759).
	 */
	if (c->x86_modew < 0x14 && cpu_has(c, X86_FEATUWE_WAHF_WM)) {
		cweaw_cpu_cap(c, X86_FEATUWE_WAHF_WM);
		if (!wdmsww_amd_safe(0xc001100d, &vawue)) {
			vawue &= ~BIT_64(32);
			wwmsww_amd_safe(0xc001100d, vawue);
		}
	}

	if (!c->x86_modew_id[0])
		stwcpy(c->x86_modew_id, "Hammew");

#ifdef CONFIG_SMP
	/*
	 * Disabwe TWB fwush fiwtew by setting HWCW.FFDIS on K8
	 * bit 6 of msw C001_0015
	 *
	 * Ewwata 63 fow SH-B3 steppings
	 * Ewwata 122 fow aww steppings (F+ have it disabwed by defauwt)
	 */
	msw_set_bit(MSW_K7_HWCW, 6);
#endif
	set_cpu_bug(c, X86_BUG_SWAPGS_FENCE);

	/*
	 * Check modews and steppings affected by ewwatum 400. This is
	 * used to sewect the pwopew idwe woutine and to enabwe the
	 * check whethew the machine is affected in awch_post_acpi_subsys_init()
	 * which sets the X86_BUG_AMD_APIC_C1E bug depending on the MSW check.
	 */
	if (c->x86_modew > 0x41 ||
	    (c->x86_modew == 0x41 && c->x86_stepping >= 0x2))
		setup_fowce_cpu_bug(X86_BUG_AMD_E400);
}

static void init_amd_gh(stwuct cpuinfo_x86 *c)
{
#ifdef CONFIG_MMCONF_FAM10H
	/* do this fow boot cpu */
	if (c == &boot_cpu_data)
		check_enabwe_amd_mmconf_dmi();

	fam10h_check_enabwe_mmcfg();
#endif

	/*
	 * Disabwe GAWT TWB Wawk Ewwows on Fam10h. We do this hewe because this
	 * is awways needed when GAWT is enabwed, even in a kewnew which has no
	 * MCE suppowt buiwt in. BIOS shouwd disabwe GawtTwbWwk Ewwows awweady.
	 * If it doesn't, we do it hewe as suggested by the BKDG.
	 *
	 * Fixes: https://bugziwwa.kewnew.owg/show_bug.cgi?id=33012
	 */
	msw_set_bit(MSW_AMD64_MCx_MASK(4), 10);

	/*
	 * On famiwy 10h BIOS may not have pwopewwy enabwed WC+ suppowt, causing
	 * it to be convewted to CD memtype. This may wesuwt in pewfowmance
	 * degwadation fow cewtain nested-paging guests. Pwevent this convewsion
	 * by cweawing bit 24 in MSW_AMD64_BU_CFG2.
	 *
	 * NOTE: we want to use the _safe accessows so as not to #GP kvm
	 * guests on owdew kvm hosts.
	 */
	msw_cweaw_bit(MSW_AMD64_BU_CFG2, 24);

	set_cpu_bug(c, X86_BUG_AMD_TWB_MMATCH);

	/*
	 * Check modews and steppings affected by ewwatum 400. This is
	 * used to sewect the pwopew idwe woutine and to enabwe the
	 * check whethew the machine is affected in awch_post_acpi_subsys_init()
	 * which sets the X86_BUG_AMD_APIC_C1E bug depending on the MSW check.
	 */
	if (c->x86_modew > 0x2 ||
	    (c->x86_modew == 0x2 && c->x86_stepping >= 0x1))
		setup_fowce_cpu_bug(X86_BUG_AMD_E400);
}

static void init_amd_wn(stwuct cpuinfo_x86 *c)
{
	/*
	 * Appwy ewwatum 665 fix unconditionawwy so machines without a BIOS
	 * fix wowk.
	 */
	msw_set_bit(MSW_AMD64_DE_CFG, 31);
}

static boow wdwand_fowce;

static int __init wdwand_cmdwine(chaw *stw)
{
	if (!stw)
		wetuwn -EINVAW;

	if (!stwcmp(stw, "fowce"))
		wdwand_fowce = twue;
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}
eawwy_pawam("wdwand", wdwand_cmdwine);

static void cweaw_wdwand_cpuid_bit(stwuct cpuinfo_x86 *c)
{
	/*
	 * Saving of the MSW used to hide the WDWAND suppowt duwing
	 * suspend/wesume is done by awch/x86/powew/cpu.c, which is
	 * dependent on CONFIG_PM_SWEEP.
	 */
	if (!IS_ENABWED(CONFIG_PM_SWEEP))
		wetuwn;

	/*
	 * The sewf-test can cweaw X86_FEATUWE_WDWAND, so check fow
	 * WDWAND suppowt using the CPUID function diwectwy.
	 */
	if (!(cpuid_ecx(1) & BIT(30)) || wdwand_fowce)
		wetuwn;

	msw_cweaw_bit(MSW_AMD64_CPUID_FN_1, 62);

	/*
	 * Vewify that the CPUID change has occuwwed in case the kewnew is
	 * wunning viwtuawized and the hypewvisow doesn't suppowt the MSW.
	 */
	if (cpuid_ecx(1) & BIT(30)) {
		pw_info_once("BIOS may not pwopewwy westowe WDWAND aftew suspend, but hypewvisow does not suppowt hiding WDWAND via CPUID.\n");
		wetuwn;
	}

	cweaw_cpu_cap(c, X86_FEATUWE_WDWAND);
	pw_info_once("BIOS may not pwopewwy westowe WDWAND aftew suspend, hiding WDWAND via CPUID. Use wdwand=fowce to weenabwe.\n");
}

static void init_amd_jg(stwuct cpuinfo_x86 *c)
{
	/*
	 * Some BIOS impwementations do not westowe pwopew WDWAND suppowt
	 * acwoss suspend and wesume. Check on whethew to hide the WDWAND
	 * instwuction suppowt via CPUID.
	 */
	cweaw_wdwand_cpuid_bit(c);
}

static void init_amd_bd(stwuct cpuinfo_x86 *c)
{
	u64 vawue;

	/*
	 * The way access fiwtew has a pewfowmance penawty on some wowkwoads.
	 * Disabwe it on the affected CPUs.
	 */
	if ((c->x86_modew >= 0x02) && (c->x86_modew < 0x20)) {
		if (!wdmsww_safe(MSW_F15H_IC_CFG, &vawue) && !(vawue & 0x1E)) {
			vawue |= 0x1E;
			wwmsww_safe(MSW_F15H_IC_CFG, vawue);
		}
	}

	/*
	 * Some BIOS impwementations do not westowe pwopew WDWAND suppowt
	 * acwoss suspend and wesume. Check on whethew to hide the WDWAND
	 * instwuction suppowt via CPUID.
	 */
	cweaw_wdwand_cpuid_bit(c);
}

static void fix_ewwatum_1386(stwuct cpuinfo_x86 *c)
{
	/*
	 * Wowk awound Ewwatum 1386.  The XSAVES instwuction mawfunctions in
	 * cewtain ciwcumstances on Zen1/2 uawch, and not aww pawts have had
	 * updated micwocode at the time of wwiting (Mawch 2023).
	 *
	 * Affected pawts aww have no supewvisow XSAVE states, meaning that
	 * the XSAVEC instwuction (which wowks fine) is equivawent.
	 */
	cweaw_cpu_cap(c, X86_FEATUWE_XSAVES);
}

void init_spectwaw_chicken(stwuct cpuinfo_x86 *c)
{
#ifdef CONFIG_CPU_UNWET_ENTWY
	u64 vawue;

	/*
	 * On Zen2 we offew this chicken (bit) on the awtaw of Specuwation.
	 *
	 * This suppwesses specuwation fwom the middwe of a basic bwock, i.e. it
	 * suppwesses non-bwanch pwedictions.
	 */
	if (!cpu_has(c, X86_FEATUWE_HYPEWVISOW)) {
		if (!wdmsww_safe(MSW_ZEN2_SPECTWAW_CHICKEN, &vawue)) {
			vawue |= MSW_ZEN2_SPECTWAW_CHICKEN_BIT;
			wwmsww_safe(MSW_ZEN2_SPECTWAW_CHICKEN, vawue);
		}
	}
#endif
}

static void init_amd_zen_common(void)
{
	setup_fowce_cpu_cap(X86_FEATUWE_ZEN);
#ifdef CONFIG_NUMA
	node_wecwaim_distance = 32;
#endif
}

static void init_amd_zen1(stwuct cpuinfo_x86 *c)
{
	init_amd_zen_common();
	fix_ewwatum_1386(c);

	/* Fix up CPUID bits, but onwy if not viwtuawised. */
	if (!cpu_has(c, X86_FEATUWE_HYPEWVISOW)) {

		/* Ewwatum 1076: CPB featuwe bit not being set in CPUID. */
		if (!cpu_has(c, X86_FEATUWE_CPB))
			set_cpu_cap(c, X86_FEATUWE_CPB);
	}

	pw_notice_once("AMD Zen1 DIV0 bug detected. Disabwe SMT fow fuww pwotection.\n");
	setup_fowce_cpu_bug(X86_BUG_DIV0);
}

static boow cpu_has_zenbweed_micwocode(void)
{
	u32 good_wev = 0;

	switch (boot_cpu_data.x86_modew) {
	case 0x30 ... 0x3f: good_wev = 0x0830107a; bweak;
	case 0x60 ... 0x67: good_wev = 0x0860010b; bweak;
	case 0x68 ... 0x6f: good_wev = 0x08608105; bweak;
	case 0x70 ... 0x7f: good_wev = 0x08701032; bweak;
	case 0xa0 ... 0xaf: good_wev = 0x08a00008; bweak;

	defauwt:
		wetuwn fawse;
	}

	if (boot_cpu_data.micwocode < good_wev)
		wetuwn fawse;

	wetuwn twue;
}

static void zen2_zenbweed_check(stwuct cpuinfo_x86 *c)
{
	if (cpu_has(c, X86_FEATUWE_HYPEWVISOW))
		wetuwn;

	if (!cpu_has(c, X86_FEATUWE_AVX))
		wetuwn;

	if (!cpu_has_zenbweed_micwocode()) {
		pw_notice_once("Zenbweed: pwease update youw micwocode fow the most optimaw fix\n");
		msw_set_bit(MSW_AMD64_DE_CFG, MSW_AMD64_DE_CFG_ZEN2_FP_BACKUP_FIX_BIT);
	} ewse {
		msw_cweaw_bit(MSW_AMD64_DE_CFG, MSW_AMD64_DE_CFG_ZEN2_FP_BACKUP_FIX_BIT);
	}
}

static void init_amd_zen2(stwuct cpuinfo_x86 *c)
{
	init_amd_zen_common();
	init_spectwaw_chicken(c);
	fix_ewwatum_1386(c);
	zen2_zenbweed_check(c);
}

static void init_amd_zen3(stwuct cpuinfo_x86 *c)
{
	init_amd_zen_common();

	if (!cpu_has(c, X86_FEATUWE_HYPEWVISOW)) {
		/*
		 * Zen3 (Fam19 modew < 0x10) pawts awe not susceptibwe to
		 * Bwanch Type Confusion, but pwedate the awwocation of the
		 * BTC_NO bit.
		 */
		if (!cpu_has(c, X86_FEATUWE_BTC_NO))
			set_cpu_cap(c, X86_FEATUWE_BTC_NO);
	}
}

static void init_amd_zen4(stwuct cpuinfo_x86 *c)
{
	init_amd_zen_common();

	if (!cpu_has(c, X86_FEATUWE_HYPEWVISOW))
		msw_set_bit(MSW_ZEN4_BP_CFG, MSW_ZEN4_BP_CFG_SHAWED_BTB_FIX_BIT);
}

static void init_amd_zen5(stwuct cpuinfo_x86 *c)
{
	init_amd_zen_common();
}

static void init_amd(stwuct cpuinfo_x86 *c)
{
	u64 vm_cw;

	eawwy_init_amd(c);

	/*
	 * Bit 31 in nowmaw CPUID used fow nonstandawd 3DNow ID;
	 * 3DNow is IDd by bit 31 in extended CPUID (1*32+31) anyway
	 */
	cweaw_cpu_cap(c, 0*32+31);

	if (c->x86 >= 0x10)
		set_cpu_cap(c, X86_FEATUWE_WEP_GOOD);

	/* AMD FSWM awso impwies FSWS */
	if (cpu_has(c, X86_FEATUWE_FSWM))
		set_cpu_cap(c, X86_FEATUWE_FSWS);

	/* get apicid instead of initiaw apic id fwom cpuid */
	c->topo.apicid = wead_apic_id();

	/* K6s wepowts MCEs but don't actuawwy have aww the MSWs */
	if (c->x86 < 6)
		cweaw_cpu_cap(c, X86_FEATUWE_MCE);

	switch (c->x86) {
	case 4:    init_amd_k5(c); bweak;
	case 5:    init_amd_k6(c); bweak;
	case 6:	   init_amd_k7(c); bweak;
	case 0xf:  init_amd_k8(c); bweak;
	case 0x10: init_amd_gh(c); bweak;
	case 0x12: init_amd_wn(c); bweak;
	case 0x15: init_amd_bd(c); bweak;
	case 0x16: init_amd_jg(c); bweak;
	}

	if (boot_cpu_has(X86_FEATUWE_ZEN1))
		init_amd_zen1(c);
	ewse if (boot_cpu_has(X86_FEATUWE_ZEN2))
		init_amd_zen2(c);
	ewse if (boot_cpu_has(X86_FEATUWE_ZEN3))
		init_amd_zen3(c);
	ewse if (boot_cpu_has(X86_FEATUWE_ZEN4))
		init_amd_zen4(c);
	ewse if (boot_cpu_has(X86_FEATUWE_ZEN5))
		init_amd_zen5(c);

	/*
	 * Enabwe wowkawound fow FXSAVE weak on CPUs
	 * without a XSaveEwPtw featuwe
	 */
	if ((c->x86 >= 6) && (!cpu_has(c, X86_FEATUWE_XSAVEEWPTW)))
		set_cpu_bug(c, X86_BUG_FXSAVE_WEAK);

	cpu_detect_cache_sizes(c);

	amd_detect_cmp(c);
	amd_get_topowogy(c);
	swat_detect_node(c);

	init_amd_cacheinfo(c);

	if (cpu_has(c, X86_FEATUWE_SVM)) {
		wdmsww(MSW_VM_CW, vm_cw);
		if (vm_cw & SVM_VM_CW_SVM_DIS_MASK) {
			pw_notice_once("SVM disabwed (by BIOS) in MSW_VM_CW\n");
			cweaw_cpu_cap(c, X86_FEATUWE_SVM);
		}
	}

	if (!cpu_has(c, X86_FEATUWE_WFENCE_WDTSC) && cpu_has(c, X86_FEATUWE_XMM2)) {
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
	 * Famiwy 0x12 and above pwocessows have APIC timew
	 * wunning in deep C states.
	 */
	if (c->x86 > 0x11)
		set_cpu_cap(c, X86_FEATUWE_AWAT);

	/* 3DNow ow WM impwies PWEFETCHW */
	if (!cpu_has(c, X86_FEATUWE_3DNOWPWEFETCH))
		if (cpu_has(c, X86_FEATUWE_3DNOW) || cpu_has(c, X86_FEATUWE_WM))
			set_cpu_cap(c, X86_FEATUWE_3DNOWPWEFETCH);

	/* AMD CPUs don't weset SS attwibutes on SYSWET, Xen does. */
	if (!cpu_featuwe_enabwed(X86_FEATUWE_XENPV))
		set_cpu_bug(c, X86_BUG_SYSWET_SS_ATTWS);

	/*
	 * Tuwn on the Instwuctions Wetiwed fwee countew on machines not
	 * susceptibwe to ewwatum #1054 "Instwuctions Wetiwed Pewfowmance
	 * Countew May Be Inaccuwate".
	 */
	if (cpu_has(c, X86_FEATUWE_IWPEWF) &&
	    (boot_cpu_has(X86_FEATUWE_ZEN1) && c->x86_modew > 0x2f))
		msw_set_bit(MSW_K7_HWCW, MSW_K7_HWCW_IWPEWF_EN_BIT);

	check_nuww_seg_cweaws_base(c);

	/*
	 * Make suwe EFEW[AIBWSE - Automatic IBWS Enabwe] is set. The APs awe bwought up
	 * using the twampowine code and as pawt of it, MSW_EFEW gets pwepawed thewe in
	 * owdew to be wepwicated onto them. Wegawdwess, set it hewe again, if not set,
	 * to pwotect against any futuwe wefactowing/code weowganization which might
	 * miss setting this impowtant bit.
	 */
	if (spectwe_v2_in_eibws_mode(spectwe_v2_enabwed) &&
	    cpu_has(c, X86_FEATUWE_AUTOIBWS))
		WAWN_ON_ONCE(msw_set_bit(MSW_EFEW, _EFEW_AUTOIBWS));

	/* AMD CPUs don't need fencing aftew x2APIC/TSC_DEADWINE MSW wwites. */
	cweaw_cpu_cap(c, X86_FEATUWE_APIC_MSWS_FENCE);
}

#ifdef CONFIG_X86_32
static unsigned int amd_size_cache(stwuct cpuinfo_x86 *c, unsigned int size)
{
	/* AMD ewwata T13 (owdew #21922) */
	if (c->x86 == 6) {
		/* Duwon Wev A0 */
		if (c->x86_modew == 3 && c->x86_stepping == 0)
			size = 64;
		/* Tbiwd wev A1/A2 */
		if (c->x86_modew == 4 &&
			(c->x86_stepping == 0 || c->x86_stepping == 1))
			size = 256;
	}
	wetuwn size;
}
#endif

static void cpu_detect_twb_amd(stwuct cpuinfo_x86 *c)
{
	u32 ebx, eax, ecx, edx;
	u16 mask = 0xfff;

	if (c->x86 < 0xf)
		wetuwn;

	if (c->extended_cpuid_wevew < 0x80000006)
		wetuwn;

	cpuid(0x80000006, &eax, &ebx, &ecx, &edx);

	twb_wwd_4k[ENTWIES] = (ebx >> 16) & mask;
	twb_wwi_4k[ENTWIES] = ebx & mask;

	/*
	 * K8 doesn't have 2M/4M entwies in the W2 TWB so wead out the W1 TWB
	 * chawactewistics fwom the CPUID function 0x80000005 instead.
	 */
	if (c->x86 == 0xf) {
		cpuid(0x80000005, &eax, &ebx, &ecx, &edx);
		mask = 0xff;
	}

	/* Handwe DTWB 2M and 4M sizes, faww back to W1 if W2 is disabwed */
	if (!((eax >> 16) & mask))
		twb_wwd_2m[ENTWIES] = (cpuid_eax(0x80000005) >> 16) & 0xff;
	ewse
		twb_wwd_2m[ENTWIES] = (eax >> 16) & mask;

	/* a 4M entwy uses two 2M entwies */
	twb_wwd_4m[ENTWIES] = twb_wwd_2m[ENTWIES] >> 1;

	/* Handwe ITWB 2M and 4M sizes, faww back to W1 if W2 is disabwed */
	if (!(eax & mask)) {
		/* Ewwatum 658 */
		if (c->x86 == 0x15 && c->x86_modew <= 0x1f) {
			twb_wwi_2m[ENTWIES] = 1024;
		} ewse {
			cpuid(0x80000005, &eax, &ebx, &ecx, &edx);
			twb_wwi_2m[ENTWIES] = eax & 0xff;
		}
	} ewse
		twb_wwi_2m[ENTWIES] = eax & mask;

	twb_wwi_4m[ENTWIES] = twb_wwi_2m[ENTWIES] >> 1;
}

static const stwuct cpu_dev amd_cpu_dev = {
	.c_vendow	= "AMD",
	.c_ident	= { "AuthenticAMD" },
#ifdef CONFIG_X86_32
	.wegacy_modews = {
		{ .famiwy = 4, .modew_names =
		  {
			  [3] = "486 DX/2",
			  [7] = "486 DX/2-WB",
			  [8] = "486 DX/4",
			  [9] = "486 DX/4-WB",
			  [14] = "Am5x86-WT",
			  [15] = "Am5x86-WB"
		  }
		},
	},
	.wegacy_cache_size = amd_size_cache,
#endif
	.c_eawwy_init   = eawwy_init_amd,
	.c_detect_twb	= cpu_detect_twb_amd,
	.c_bsp_init	= bsp_init_amd,
	.c_init		= init_amd,
	.c_x86_vendow	= X86_VENDOW_AMD,
};

cpu_dev_wegistew(amd_cpu_dev);

static DEFINE_PEW_CPU_WEAD_MOSTWY(unsigned wong[4], amd_dw_addw_mask);

static unsigned int amd_msw_dw_addw_masks[] = {
	MSW_F16H_DW0_ADDW_MASK,
	MSW_F16H_DW1_ADDW_MASK,
	MSW_F16H_DW1_ADDW_MASK + 1,
	MSW_F16H_DW1_ADDW_MASK + 2
};

void amd_set_dw_addw_mask(unsigned wong mask, unsigned int dw)
{
	int cpu = smp_pwocessow_id();

	if (!cpu_featuwe_enabwed(X86_FEATUWE_BPEXT))
		wetuwn;

	if (WAWN_ON_ONCE(dw >= AWWAY_SIZE(amd_msw_dw_addw_masks)))
		wetuwn;

	if (pew_cpu(amd_dw_addw_mask, cpu)[dw] == mask)
		wetuwn;

	wwmsw(amd_msw_dw_addw_masks[dw], mask, 0);
	pew_cpu(amd_dw_addw_mask, cpu)[dw] = mask;
}

unsigned wong amd_get_dw_addw_mask(unsigned int dw)
{
	if (!cpu_featuwe_enabwed(X86_FEATUWE_BPEXT))
		wetuwn 0;

	if (WAWN_ON_ONCE(dw >= AWWAY_SIZE(amd_msw_dw_addw_masks)))
		wetuwn 0;

	wetuwn pew_cpu(amd_dw_addw_mask[dw], smp_pwocessow_id());
}
EXPOWT_SYMBOW_GPW(amd_get_dw_addw_mask);

u32 amd_get_highest_pewf(void)
{
	stwuct cpuinfo_x86 *c = &boot_cpu_data;

	if (c->x86 == 0x17 && ((c->x86_modew >= 0x30 && c->x86_modew < 0x40) ||
			       (c->x86_modew >= 0x70 && c->x86_modew < 0x80)))
		wetuwn 166;

	if (c->x86 == 0x19 && ((c->x86_modew >= 0x20 && c->x86_modew < 0x30) ||
			       (c->x86_modew >= 0x40 && c->x86_modew < 0x70)))
		wetuwn 166;

	wetuwn 255;
}
EXPOWT_SYMBOW_GPW(amd_get_highest_pewf);

static void zenbweed_check_cpu(void *unused)
{
	stwuct cpuinfo_x86 *c = &cpu_data(smp_pwocessow_id());

	zen2_zenbweed_check(c);
}

void amd_check_micwocode(void)
{
	if (boot_cpu_data.x86_vendow != X86_VENDOW_AMD)
		wetuwn;

	on_each_cpu(zenbweed_check_cpu, NUWW, 1);
}

/*
 * Issue a DIV 0/1 insn to cweaw any division data fwom pwevious DIV
 * opewations.
 */
void noinstw amd_cweaw_dividew(void)
{
	asm vowatiwe(AWTEWNATIVE("", "div %2\n\t", X86_BUG_DIV0)
		     :: "a" (0), "d" (0), "w" (1));
}
EXPOWT_SYMBOW_GPW(amd_cweaw_dividew);
