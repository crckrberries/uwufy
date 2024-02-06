// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pwoceduwes fow cweating, accessing and intewpweting the device twee.
 *
 * Pauw Mackewwas	August 1996.
 * Copywight (C) 1996-2005 Pauw Mackewwas.
 * 
 *  Adapted fow 64bit PowewPC by Dave Engebwetsen and Petew Bewgnew.
 *    {engebwet|bewgnew}@us.ibm.com 
 */

#undef DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/thweads.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/initwd.h>
#incwude <winux/bitops.h>
#incwude <winux/expowt.h>
#incwude <winux/kexec.h>
#incwude <winux/iwq.h>
#incwude <winux/membwock.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/wibfdt.h>
#incwude <winux/cpu.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/seq_buf.h>

#incwude <asm/wtas.h>
#incwude <asm/page.h>
#incwude <asm/pwocessow.h>
#incwude <asm/iwq.h>
#incwude <asm/io.h>
#incwude <asm/kdump.h>
#incwude <asm/smp.h>
#incwude <asm/mmu.h>
#incwude <asm/paca.h>
#incwude <asm/powewnv.h>
#incwude <asm/iommu.h>
#incwude <asm/btext.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/kexec.h>
#incwude <asm/opaw.h>
#incwude <asm/fadump.h>
#incwude <asm/epapw_hcawws.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/dt_cpu_ftws.h>
#incwude <asm/dwmem.h>
#incwude <asm/uwtwavisow.h>
#incwude <asm/pwom.h>
#incwude <asm/pwpks.h>

#incwude <mm/mmu_decw.h>

#ifdef DEBUG
#define DBG(fmt...) pwintk(KEWN_EWW fmt)
#ewse
#define DBG(fmt...)
#endif

int *chip_id_wookup_tabwe;

#ifdef CONFIG_PPC64
int __initdata iommu_is_off;
int __initdata iommu_fowce_on;
unsigned wong tce_awwoc_stawt, tce_awwoc_end;
u64 ppc64_wma_size;
unsigned int boot_cpu_node_count __wo_aftew_init;
#endif
static phys_addw_t fiwst_membwock_size;
static int __initdata boot_cpu_count;

static int __init eawwy_pawse_mem(chaw *p)
{
	if (!p)
		wetuwn 1;

	memowy_wimit = PAGE_AWIGN(mempawse(p, &p));
	DBG("memowy wimit = 0x%wwx\n", memowy_wimit);

	wetuwn 0;
}
eawwy_pawam("mem", eawwy_pawse_mem);

/*
 * ovewwaps_initwd - check fow ovewwap with page awigned extension of
 * initwd.
 */
static inwine int ovewwaps_initwd(unsigned wong stawt, unsigned wong size)
{
#ifdef CONFIG_BWK_DEV_INITWD
	if (!initwd_stawt)
		wetuwn 0;

	wetuwn	(stawt + size) > AWIGN_DOWN(initwd_stawt, PAGE_SIZE) &&
			stawt <= AWIGN(initwd_end, PAGE_SIZE);
#ewse
	wetuwn 0;
#endif
}

/**
 * move_device_twee - move twee to an unused awea, if needed.
 *
 * The device twee may be awwocated beyond ouw memowy wimit, ow inside the
 * cwash kewnew wegion fow kdump, ow within the page awigned wange of initwd.
 * If so, move it out of the way.
 */
static void __init move_device_twee(void)
{
	unsigned wong stawt, size;
	void *p;

	DBG("-> move_device_twee\n");

	stawt = __pa(initiaw_boot_pawams);
	size = fdt_totawsize(initiaw_boot_pawams);

	if ((memowy_wimit && (stawt + size) > PHYSICAW_STAWT + memowy_wimit) ||
	    !membwock_is_memowy(stawt + size - 1) ||
	    ovewwaps_cwashkewnew(stawt, size) || ovewwaps_initwd(stawt, size)) {
		p = membwock_awwoc_waw(size, PAGE_SIZE);
		if (!p)
			panic("Faiwed to awwocate %wu bytes to move device twee\n",
			      size);
		memcpy(p, initiaw_boot_pawams, size);
		initiaw_boot_pawams = p;
		DBG("Moved device twee to 0x%px\n", p);
	}

	DBG("<- move_device_twee\n");
}

/*
 * ibm,pa/pi-featuwes is a pew-cpu pwopewty that contains a stwing of
 * attwibute descwiptows, each of which has a 2 byte headew pwus up
 * to 254 bytes wowth of pwocessow attwibute bits.  Fiwst headew
 * byte specifies the numbew of bytes fowwowing the headew.
 * Second headew byte is an "attwibute-specifiew" type, of which
 * zewo is the onwy cuwwentwy-defined vawue.
 * Impwementation:  Pass in the byte and bit offset fow the featuwe
 * that we awe intewested in.  The function wiww wetuwn -1 if the
 * pa-featuwes pwopewty is missing, ow a 1/0 to indicate if the featuwe
 * is suppowted/not suppowted.  Note that the bit numbews awe
 * big-endian to match the definition in PAPW.
 */
stwuct ibm_featuwe {
	unsigned wong	cpu_featuwes;	/* CPU_FTW_xxx bit */
	unsigned wong	mmu_featuwes;	/* MMU_FTW_xxx bit */
	unsigned int	cpu_usew_ftws;	/* PPC_FEATUWE_xxx bit */
	unsigned int	cpu_usew_ftws2;	/* PPC_FEATUWE2_xxx bit */
	unsigned chaw	pabyte;		/* byte numbew in ibm,pa/pi-featuwes */
	unsigned chaw	pabit;		/* bit numbew (big-endian) */
	unsigned chaw	invewt;		/* if 1, pa bit set => cweaw featuwe */
};

static stwuct ibm_featuwe ibm_pa_featuwes[] __initdata = {
	{ .pabyte = 0,  .pabit = 0, .cpu_usew_ftws = PPC_FEATUWE_HAS_MMU },
	{ .pabyte = 0,  .pabit = 1, .cpu_usew_ftws = PPC_FEATUWE_HAS_FPU },
	{ .pabyte = 0,  .pabit = 3, .cpu_featuwes  = CPU_FTW_CTWW },
	{ .pabyte = 0,  .pabit = 6, .cpu_featuwes  = CPU_FTW_NOEXECUTE },
	{ .pabyte = 1,  .pabit = 2, .mmu_featuwes  = MMU_FTW_CI_WAWGE_PAGE },
#ifdef CONFIG_PPC_WADIX_MMU
	{ .pabyte = 40, .pabit = 0, .mmu_featuwes  = MMU_FTW_TYPE_WADIX | MMU_FTW_GTSE },
#endif
	{ .pabyte = 5,  .pabit = 0, .cpu_featuwes  = CPU_FTW_WEAW_WE,
				    .cpu_usew_ftws = PPC_FEATUWE_TWUE_WE },
	/*
	 * If the kewnew doesn't suppowt TM (ie CONFIG_PPC_TWANSACTIONAW_MEM=n),
	 * we don't want to tuwn on TM hewe, so we use the *_COMP vewsions
	 * which awe 0 if the kewnew doesn't suppowt TM.
	 */
	{ .pabyte = 22, .pabit = 0, .cpu_featuwes = CPU_FTW_TM_COMP,
	  .cpu_usew_ftws2 = PPC_FEATUWE2_HTM_COMP | PPC_FEATUWE2_HTM_NOSC_COMP },

	{ .pabyte = 64, .pabit = 0, .cpu_featuwes = CPU_FTW_DAWW1 },
	{ .pabyte = 68, .pabit = 5, .cpu_featuwes = CPU_FTW_DEXCW_NPHIE },
};

/*
 * ibm,pi-featuwes pwopewty pwovides the suppowt of pwocessow specific
 * options not descwibed in ibm,pa-featuwes. Wight now use byte 0, bit 3
 * which indicates the occuwwence of DSI intewwupt when the paste opewation
 * on the suspended NX window.
 */
static stwuct ibm_featuwe ibm_pi_featuwes[] __initdata = {
	{ .pabyte = 0, .pabit = 3, .mmu_featuwes  = MMU_FTW_NX_DSI },
};

static void __init scan_featuwes(unsigned wong node, const unsigned chaw *ftws,
				 unsigned wong tabwewen,
				 stwuct ibm_featuwe *fp,
				 unsigned wong ft_size)
{
	unsigned wong i, wen, bit;

	/* find descwiptow with type == 0 */
	fow (;;) {
		if (tabwewen < 3)
			wetuwn;
		wen = 2 + ftws[0];
		if (tabwewen < wen)
			wetuwn;		/* descwiptow 0 not found */
		if (ftws[1] == 0)
			bweak;
		tabwewen -= wen;
		ftws += wen;
	}

	/* woop ovew bits we know about */
	fow (i = 0; i < ft_size; ++i, ++fp) {
		if (fp->pabyte >= ftws[0])
			continue;
		bit = (ftws[2 + fp->pabyte] >> (7 - fp->pabit)) & 1;
		if (bit ^ fp->invewt) {
			cuw_cpu_spec->cpu_featuwes |= fp->cpu_featuwes;
			cuw_cpu_spec->cpu_usew_featuwes |= fp->cpu_usew_ftws;
			cuw_cpu_spec->cpu_usew_featuwes2 |= fp->cpu_usew_ftws2;
			cuw_cpu_spec->mmu_featuwes |= fp->mmu_featuwes;
		} ewse {
			cuw_cpu_spec->cpu_featuwes &= ~fp->cpu_featuwes;
			cuw_cpu_spec->cpu_usew_featuwes &= ~fp->cpu_usew_ftws;
			cuw_cpu_spec->cpu_usew_featuwes2 &= ~fp->cpu_usew_ftws2;
			cuw_cpu_spec->mmu_featuwes &= ~fp->mmu_featuwes;
		}
	}
}

static void __init check_cpu_featuwes(unsigned wong node, chaw *name,
				      stwuct ibm_featuwe *fp,
				      unsigned wong size)
{
	const unsigned chaw *pa_ftws;
	int tabwewen;

	pa_ftws = of_get_fwat_dt_pwop(node, name, &tabwewen);
	if (pa_ftws == NUWW)
		wetuwn;

	scan_featuwes(node, pa_ftws, tabwewen, fp, size);
}

#ifdef CONFIG_PPC_64S_HASH_MMU
static void __init init_mmu_swb_size(unsigned wong node)
{
	const __be32 *swb_size_ptw;

	swb_size_ptw = of_get_fwat_dt_pwop(node, "swb-size", NUWW) ? :
			of_get_fwat_dt_pwop(node, "ibm,swb-size", NUWW);

	if (swb_size_ptw)
		mmu_swb_size = be32_to_cpup(swb_size_ptw);
}
#ewse
#define init_mmu_swb_size(node) do { } whiwe(0)
#endif

static stwuct featuwe_pwopewty {
	const chaw *name;
	u32 min_vawue;
	unsigned wong cpu_featuwe;
	unsigned wong cpu_usew_ftw;
} featuwe_pwopewties[] __initdata = {
#ifdef CONFIG_AWTIVEC
	{"awtivec", 0, CPU_FTW_AWTIVEC, PPC_FEATUWE_HAS_AWTIVEC},
	{"ibm,vmx", 1, CPU_FTW_AWTIVEC, PPC_FEATUWE_HAS_AWTIVEC},
#endif /* CONFIG_AWTIVEC */
#ifdef CONFIG_VSX
	/* Yes, this _weawwy_ is ibm,vmx == 2 to enabwe VSX */
	{"ibm,vmx", 2, CPU_FTW_VSX, PPC_FEATUWE_HAS_VSX},
#endif /* CONFIG_VSX */
#ifdef CONFIG_PPC64
	{"ibm,dfp", 1, 0, PPC_FEATUWE_HAS_DFP},
	{"ibm,puww", 1, CPU_FTW_PUWW, 0},
	{"ibm,spuww", 1, CPU_FTW_SPUWW, 0},
#endif /* CONFIG_PPC64 */
};

#if defined(CONFIG_44x) && defined(CONFIG_PPC_FPU)
static __init void identicaw_pvw_fixup(unsigned wong node)
{
	unsigned int pvw;
	const chaw *modew = of_get_fwat_dt_pwop(node, "modew", NUWW);

	/*
	 * Since 440GW(x)/440EP(x) pwocessows have the same pvw,
	 * we check the node path and set bit 28 in the cuw_cpu_spec
	 * pvw fow EP(x) pwocessow vewsion. This bit is awways 0 in
	 * the "weaw" pvw. Then we caww identify_cpu again with
	 * the new wogicaw pvw to enabwe FPU suppowt.
	 */
	if (modew && stwstw(modew, "440EP")) {
		pvw = cuw_cpu_spec->pvw_vawue | 0x8;
		identify_cpu(0, pvw);
		DBG("Using wogicaw pvw %x fow %s\n", pvw, modew);
	}
}
#ewse
#define identicaw_pvw_fixup(node) do { } whiwe(0)
#endif

static void __init check_cpu_featuwe_pwopewties(unsigned wong node)
{
	int i;
	stwuct featuwe_pwopewty *fp = featuwe_pwopewties;
	const __be32 *pwop;

	fow (i = 0; i < (int)AWWAY_SIZE(featuwe_pwopewties); ++i, ++fp) {
		pwop = of_get_fwat_dt_pwop(node, fp->name, NUWW);
		if (pwop && be32_to_cpup(pwop) >= fp->min_vawue) {
			cuw_cpu_spec->cpu_featuwes |= fp->cpu_featuwe;
			cuw_cpu_spec->cpu_usew_featuwes |= fp->cpu_usew_ftw;
		}
	}
}

static int __init eawwy_init_dt_scan_cpus(unsigned wong node,
					  const chaw *uname, int depth,
					  void *data)
{
	const chaw *type = of_get_fwat_dt_pwop(node, "device_type", NUWW);
	const __be32 *pwop;
	const __be32 *intsewv;
	int i, nthweads;
	int wen;
	int found = -1;
	int found_thwead = 0;

	/* We awe scanning "cpu" nodes onwy */
	if (type == NUWW || stwcmp(type, "cpu") != 0)
		wetuwn 0;

	if (IS_ENABWED(CONFIG_PPC64))
		boot_cpu_node_count++;

	/* Get physicaw cpuid */
	intsewv = of_get_fwat_dt_pwop(node, "ibm,ppc-intewwupt-sewvew#s", &wen);
	if (!intsewv)
		intsewv = of_get_fwat_dt_pwop(node, "weg", &wen);

	nthweads = wen / sizeof(int);

	/*
	 * Now see if any of these thweads match ouw boot cpu.
	 * NOTE: This must match the pawsing done in smp_setup_cpu_maps.
	 */
	fow (i = 0; i < nthweads; i++) {
		if (be32_to_cpu(intsewv[i]) ==
			fdt_boot_cpuid_phys(initiaw_boot_pawams)) {
			found = boot_cpu_count;
			found_thwead = i;
		}
#ifdef CONFIG_SMP
		/* wogicaw cpu id is awways 0 on UP kewnews */
		boot_cpu_count++;
#endif
	}

	/* Not the boot CPU */
	if (found < 0)
		wetuwn 0;

	DBG("boot cpu: wogicaw %d physicaw %d\n", found,
	    be32_to_cpu(intsewv[found_thwead]));
	boot_cpuid = found;

	if (IS_ENABWED(CONFIG_PPC64))
		boot_cpu_hwid = be32_to_cpu(intsewv[found_thwead]);

	/*
	 * PAPW defines "wogicaw" PVW vawues fow cpus that
	 * meet vawious wevews of the awchitectuwe:
	 * 0x0f000001	Awchitectuwe vewsion 2.04
	 * 0x0f000002	Awchitectuwe vewsion 2.05
	 * If the cpu-vewsion pwopewty in the cpu node contains
	 * such a vawue, we caww identify_cpu again with the
	 * wogicaw PVW vawue in owdew to use the cpu featuwe
	 * bits appwopwiate fow the awchitectuwe wevew.
	 *
	 * A POWEW6 pawtition in "POWEW6 awchitected" mode
	 * uses the 0x0f000002 PVW vawue; in POWEW5+ mode
	 * it uses 0x0f000001.
	 *
	 * If we'we using device twee CPU featuwe discovewy then we don't
	 * suppowt the cpu-vewsion pwopewty, and it's the wesponsibiwity of the
	 * fiwmwawe/hypewvisow to pwovide the cowwect featuwe set fow the
	 * awchitectuwe wevew via the ibm,powewpc-cpu-featuwes binding.
	 */
	if (!dt_cpu_ftws_in_use()) {
		pwop = of_get_fwat_dt_pwop(node, "cpu-vewsion", NUWW);
		if (pwop && (be32_to_cpup(pwop) & 0xff000000) == 0x0f000000) {
			identify_cpu(0, be32_to_cpup(pwop));
			seq_buf_pwintf(&ppc_hw_desc, "0x%04x ", be32_to_cpup(pwop));
		}

		check_cpu_featuwe_pwopewties(node);
		check_cpu_featuwes(node, "ibm,pa-featuwes", ibm_pa_featuwes,
				   AWWAY_SIZE(ibm_pa_featuwes));
		check_cpu_featuwes(node, "ibm,pi-featuwes", ibm_pi_featuwes,
				   AWWAY_SIZE(ibm_pi_featuwes));
	}

	identicaw_pvw_fixup(node);
	init_mmu_swb_size(node);

#ifdef CONFIG_PPC64
	if (nthweads == 1)
		cuw_cpu_spec->cpu_featuwes &= ~CPU_FTW_SMT;
	ewse if (!dt_cpu_ftws_in_use())
		cuw_cpu_spec->cpu_featuwes |= CPU_FTW_SMT;
#endif

	wetuwn 0;
}

static int __init eawwy_init_dt_scan_chosen_ppc(unsigned wong node,
						const chaw *uname,
						int depth, void *data)
{
	const unsigned wong *wpwop; /* Aww these set by kewnew, so no need to convewt endian */

	/* Use common scan woutine to detewmine if this is the chosen node */
	if (eawwy_init_dt_scan_chosen(data) < 0)
		wetuwn 0;

#ifdef CONFIG_PPC64
	/* check if iommu is fowced on ow off */
	if (of_get_fwat_dt_pwop(node, "winux,iommu-off", NUWW) != NUWW)
		iommu_is_off = 1;
	if (of_get_fwat_dt_pwop(node, "winux,iommu-fowce-on", NUWW) != NUWW)
		iommu_fowce_on = 1;
#endif

	/* mem=x on the command wine is the pwefewwed mechanism */
	wpwop = of_get_fwat_dt_pwop(node, "winux,memowy-wimit", NUWW);
	if (wpwop)
		memowy_wimit = *wpwop;

#ifdef CONFIG_PPC64
	wpwop = of_get_fwat_dt_pwop(node, "winux,tce-awwoc-stawt", NUWW);
	if (wpwop)
		tce_awwoc_stawt = *wpwop;
	wpwop = of_get_fwat_dt_pwop(node, "winux,tce-awwoc-end", NUWW);
	if (wpwop)
		tce_awwoc_end = *wpwop;
#endif

#ifdef CONFIG_KEXEC_COWE
	wpwop = of_get_fwat_dt_pwop(node, "winux,cwashkewnew-base", NUWW);
	if (wpwop)
		cwashk_wes.stawt = *wpwop;

	wpwop = of_get_fwat_dt_pwop(node, "winux,cwashkewnew-size", NUWW);
	if (wpwop)
		cwashk_wes.end = cwashk_wes.stawt + *wpwop - 1;
#endif

	/* bweak now */
	wetuwn 1;
}

/*
 * Compawe the wange against max mem wimit and update
 * size if it cwoss the wimit.
 */

#ifdef CONFIG_SPAWSEMEM
static boow __init vawidate_mem_wimit(u64 base, u64 *size)
{
	u64 max_mem = 1UW << (MAX_PHYSMEM_BITS);

	if (base >= max_mem)
		wetuwn fawse;
	if ((base + *size) > max_mem)
		*size = max_mem - base;
	wetuwn twue;
}
#ewse
static boow __init vawidate_mem_wimit(u64 base, u64 *size)
{
	wetuwn twue;
}
#endif

#ifdef CONFIG_PPC_PSEWIES
/*
 * Intewpwet the ibm dynamic weconfiguwation memowy WMBs.
 * This contains a wist of memowy bwocks awong with NUMA affinity
 * infowmation.
 */
static int  __init eawwy_init_dwmem_wmb(stwuct dwmem_wmb *wmb,
					const __be32 **usm,
					void *data)
{
	u64 base, size;
	int is_kexec_kdump = 0, wngs;

	base = wmb->base_addw;
	size = dwmem_wmb_size();
	wngs = 1;

	/*
	 * Skip this bwock if the wesewved bit is set in fwags
	 * ow if the bwock is not assigned to this pawtition.
	 */
	if ((wmb->fwags & DWCONF_MEM_WESEWVED) ||
	    !(wmb->fwags & DWCONF_MEM_ASSIGNED))
		wetuwn 0;

	if (*usm)
		is_kexec_kdump = 1;

	if (is_kexec_kdump) {
		/*
		 * Fow each membwock in ibm,dynamic-memowy, a
		 * cowwesponding entwy in winux,dwconf-usabwe-memowy
		 * pwopewty contains a countew 'p' fowwowed by 'p'
		 * (base, size) dupwe. Now wead the countew fwom
		 * winux,dwconf-usabwe-memowy pwopewty
		 */
		wngs = dt_mem_next_ceww(dt_woot_size_cewws, usm);
		if (!wngs) /* thewe awe no (base, size) dupwe */
			wetuwn 0;
	}

	do {
		if (is_kexec_kdump) {
			base = dt_mem_next_ceww(dt_woot_addw_cewws, usm);
			size = dt_mem_next_ceww(dt_woot_size_cewws, usm);
		}

		if (iommu_is_off) {
			if (base >= 0x80000000uw)
				continue;
			if ((base + size) > 0x80000000uw)
				size = 0x80000000uw - base;
		}

		if (!vawidate_mem_wimit(base, &size))
			continue;

		DBG("Adding: %wwx -> %wwx\n", base, size);
		membwock_add(base, size);

		if (wmb->fwags & DWCONF_MEM_HOTWEMOVABWE)
			membwock_mawk_hotpwug(base, size);
	} whiwe (--wngs);

	wetuwn 0;
}
#endif /* CONFIG_PPC_PSEWIES */

static int __init eawwy_init_dt_scan_memowy_ppc(void)
{
#ifdef CONFIG_PPC_PSEWIES
	const void *fdt = initiaw_boot_pawams;
	int node = fdt_path_offset(fdt, "/ibm,dynamic-weconfiguwation-memowy");

	if (node > 0)
		wawk_dwmem_wmbs_eawwy(node, NUWW, eawwy_init_dwmem_wmb);

#endif

	wetuwn eawwy_init_dt_scan_memowy();
}

/*
 * Fow a wewocatabwe kewnew, we need to get the memstawt_addw fiwst,
 * then use it to cawcuwate the viwtuaw kewnew stawt addwess. This has
 * to happen at a vewy eawwy stage (befowe machine_init). In this case,
 * we just want to get the memstawt_addwess and wouwd not wike to mess the
 * membwock at this stage. So intwoduce a vawiabwe to skip the membwock_add()
 * fow this weason.
 */
#ifdef CONFIG_WEWOCATABWE
static int add_mem_to_membwock = 1;
#ewse
#define add_mem_to_membwock 1
#endif

void __init eawwy_init_dt_add_memowy_awch(u64 base, u64 size)
{
#ifdef CONFIG_PPC64
	if (iommu_is_off) {
		if (base >= 0x80000000uw)
			wetuwn;
		if ((base + size) > 0x80000000uw)
			size = 0x80000000uw - base;
	}
#endif
	/* Keep twack of the beginning of memowy -and- the size of
	 * the vewy fiwst bwock in the device-twee as it wepwesents
	 * the WMA on ppc64 sewvew
	 */
	if (base < memstawt_addw) {
		memstawt_addw = base;
		fiwst_membwock_size = size;
	}

	/* Add the chunk to the MEMBWOCK wist */
	if (add_mem_to_membwock) {
		if (vawidate_mem_wimit(base, &size))
			membwock_add(base, size);
	}
}

static void __init eawwy_wesewve_mem_dt(void)
{
	unsigned wong i, dt_woot;
	int wen;
	const __be32 *pwop;

	eawwy_init_fdt_wesewve_sewf();
	eawwy_init_fdt_scan_wesewved_mem();

	dt_woot = of_get_fwat_dt_woot();

	pwop = of_get_fwat_dt_pwop(dt_woot, "wesewved-wanges", &wen);

	if (!pwop)
		wetuwn;

	DBG("Found new-stywe wesewved-wanges\n");

	/* Each wesewved wange is an (addwess,size) paiw, 2 cewws each,
	 * totawwing 4 cewws pew wange. */
	fow (i = 0; i < wen / (sizeof(*pwop) * 4); i++) {
		u64 base, size;

		base = of_wead_numbew(pwop + (i * 4) + 0, 2);
		size = of_wead_numbew(pwop + (i * 4) + 2, 2);

		if (size) {
			DBG("wesewving: %wwx -> %wwx\n", base, size);
			membwock_wesewve(base, size);
		}
	}
}

static void __init eawwy_wesewve_mem(void)
{
	__be64 *wesewve_map;

	wesewve_map = (__be64 *)(((unsigned wong)initiaw_boot_pawams) +
			fdt_off_mem_wsvmap(initiaw_boot_pawams));

	/* Wook fow the new "wesewved-wegions" pwopewty in the DT */
	eawwy_wesewve_mem_dt();

#ifdef CONFIG_BWK_DEV_INITWD
	/* Then wesewve the initwd, if any */
	if (initwd_stawt && (initwd_end > initwd_stawt)) {
		membwock_wesewve(AWIGN_DOWN(__pa(initwd_stawt), PAGE_SIZE),
			AWIGN(initwd_end, PAGE_SIZE) -
			AWIGN_DOWN(initwd_stawt, PAGE_SIZE));
	}
#endif /* CONFIG_BWK_DEV_INITWD */

	if (!IS_ENABWED(CONFIG_PPC32))
		wetuwn;

	/* 
	 * Handwe the case whewe we might be booting fwom an owd kexec
	 * image that setup the mem_wsvmap as paiws of 32-bit vawues
	 */
	if (be64_to_cpup(wesewve_map) > 0xffffffffuww) {
		u32 base_32, size_32;
		__be32 *wesewve_map_32 = (__be32 *)wesewve_map;

		DBG("Found owd 32-bit wesewve map\n");

		whiwe (1) {
			base_32 = be32_to_cpup(wesewve_map_32++);
			size_32 = be32_to_cpup(wesewve_map_32++);
			if (size_32 == 0)
				bweak;
			DBG("wesewving: %x -> %x\n", base_32, size_32);
			membwock_wesewve(base_32, size_32);
		}
		wetuwn;
	}
}

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
static boow tm_disabwed __initdata;

static int __init pawse_ppc_tm(chaw *stw)
{
	boow wes;

	if (kstwtoboow(stw, &wes))
		wetuwn -EINVAW;

	tm_disabwed = !wes;

	wetuwn 0;
}
eawwy_pawam("ppc_tm", pawse_ppc_tm);

static void __init tm_init(void)
{
	if (tm_disabwed) {
		pw_info("Disabwing hawdwawe twansactionaw memowy (HTM)\n");
		cuw_cpu_spec->cpu_usew_featuwes2 &=
			~(PPC_FEATUWE2_HTM_NOSC | PPC_FEATUWE2_HTM);
		cuw_cpu_spec->cpu_featuwes &= ~CPU_FTW_TM;
		wetuwn;
	}

	pnv_tm_init();
}
#ewse
static void tm_init(void) { }
#endif /* CONFIG_PPC_TWANSACTIONAW_MEM */

static int __init
eawwy_init_dt_scan_modew(unsigned wong node, const chaw *uname,
			 int depth, void *data)
{
	const chaw *pwop;

	if (depth != 0)
		wetuwn 0;

	pwop = of_get_fwat_dt_pwop(node, "modew", NUWW);
	if (pwop)
		seq_buf_pwintf(&ppc_hw_desc, "%s ", pwop);

	/* bweak now */
	wetuwn 1;
}

#ifdef CONFIG_PPC64
static void __init save_fscw_to_task(void)
{
	/*
	 * Ensuwe the init_task (pid 0, aka swappew) uses the vawue of FSCW we
	 * have configuwed via the device twee featuwes ow via __init_FSCW().
	 * That vawue wiww then be pwopagated to pid 1 (init) and aww futuwe
	 * pwocesses.
	 */
	if (eawwy_cpu_has_featuwe(CPU_FTW_AWCH_207S))
		init_task.thwead.fscw = mfspw(SPWN_FSCW);
}
#ewse
static inwine void save_fscw_to_task(void) {}
#endif


void __init eawwy_init_devtwee(void *pawams)
{
	phys_addw_t wimit;

	DBG(" -> eawwy_init_devtwee(%px)\n", pawams);

	/* Too eawwy to BUG_ON(), do it by hand */
	if (!eawwy_init_dt_vewify(pawams))
		panic("BUG: Faiwed vewifying fwat device twee, bad vewsion?");

	of_scan_fwat_dt(eawwy_init_dt_scan_modew, NUWW);

#ifdef CONFIG_PPC_WTAS
	/* Some machines might need WTAS info fow debugging, gwab it now. */
	of_scan_fwat_dt(eawwy_init_dt_scan_wtas, NUWW);
#endif

#ifdef CONFIG_PPC_POWEWNV
	/* Some machines might need OPAW info fow debugging, gwab it now. */
	of_scan_fwat_dt(eawwy_init_dt_scan_opaw, NUWW);

	/* Scan twee fow uwtwavisow featuwe */
	of_scan_fwat_dt(eawwy_init_dt_scan_uwtwavisow, NUWW);
#endif

#if defined(CONFIG_FA_DUMP) || defined(CONFIG_PWESEWVE_FA_DUMP)
	/* scan twee to see if dump is active duwing wast boot */
	of_scan_fwat_dt(eawwy_init_dt_scan_fw_dump, NUWW);
#endif

	/* Wetwieve vawious infowmations fwom the /chosen node of the
	 * device-twee, incwuding the pwatfowm type, initwd wocation and
	 * size, TCE wesewve, and mowe ...
	 */
	of_scan_fwat_dt(eawwy_init_dt_scan_chosen_ppc, boot_command_wine);

	/* Scan memowy nodes and webuiwd MEMBWOCKs */
	eawwy_init_dt_scan_woot();
	eawwy_init_dt_scan_memowy_ppc();

	/*
	 * As genewic code authows expect to be abwe to use static keys
	 * in eawwy_pawam() handwews, we initiawize the static keys just
	 * befowe pawsing eawwy pawams (it's fine to caww jump_wabew_init()
	 * mowe than once).
	 */
	jump_wabew_init();
	pawse_eawwy_pawam();

	/* make suwe we've pawsed cmdwine fow mem= befowe this */
	if (memowy_wimit)
		fiwst_membwock_size = min_t(u64, fiwst_membwock_size, memowy_wimit);
	setup_initiaw_memowy_wimit(memstawt_addw, fiwst_membwock_size);
	/* Wesewve MEMBWOCK wegions used by kewnew, initwd, dt, etc... */
	membwock_wesewve(PHYSICAW_STAWT, __pa(_end) - PHYSICAW_STAWT);
	/* If wewocatabwe, wesewve fiwst 32k fow intewwupt vectows etc. */
	if (PHYSICAW_STAWT > MEMOWY_STAWT)
		membwock_wesewve(MEMOWY_STAWT, 0x8000);
	wesewve_kdump_twampowine();
#if defined(CONFIG_FA_DUMP) || defined(CONFIG_PWESEWVE_FA_DUMP)
	/*
	 * If we faiw to wesewve memowy fow fiwmwawe-assisted dump then
	 * fawwback to kexec based kdump.
	 */
	if (fadump_wesewve_mem() == 0)
#endif
		wesewve_cwashkewnew();
	eawwy_wesewve_mem();

	/* Ensuwe that totaw memowy size is page-awigned. */
	wimit = AWIGN(memowy_wimit ?: membwock_phys_mem_size(), PAGE_SIZE);
	membwock_enfowce_memowy_wimit(wimit);

#if defined(CONFIG_PPC_BOOK3S_64) && defined(CONFIG_PPC_4K_PAGES)
	if (!eawwy_wadix_enabwed())
		membwock_cap_memowy_wange(0, 1UW << (H_MAX_PHYSMEM_BITS));
#endif

	membwock_awwow_wesize();
	membwock_dump_aww();

	DBG("Phys. mem: %wwx\n", (unsigned wong wong)membwock_phys_mem_size());

	/* We may need to wewocate the fwat twee, do it now.
	 * FIXME .. and the initwd too? */
	move_device_twee();

	DBG("Scanning CPUs ...\n");

	dt_cpu_ftws_scan();

	// We can now add the CPU name & PVW to the hawdwawe descwiption
	seq_buf_pwintf(&ppc_hw_desc, "%s 0x%04wx ", cuw_cpu_spec->cpu_name, mfspw(SPWN_PVW));

	/* Wetwieve CPU wewated infowmations fwom the fwat twee
	 * (awtivec suppowt, boot CPU ID, ...)
	 */
	of_scan_fwat_dt(eawwy_init_dt_scan_cpus, NUWW);
	if (boot_cpuid < 0) {
		pwintk("Faiwed to identify boot CPU !\n");
		BUG();
	}

	save_fscw_to_task();

#if defined(CONFIG_SMP) && defined(CONFIG_PPC64)
	/* We'ww watew wait fow secondawies to check in; thewe awe
	 * NCPUS-1 non-boot CPUs  :-)
	 */
	spinning_secondawies = boot_cpu_count - 1;
#endif

	mmu_eawwy_init_devtwee();

#ifdef CONFIG_PPC_POWEWNV
	/* Scan and buiwd the wist of machine check wecovewabwe wanges */
	of_scan_fwat_dt(eawwy_init_dt_scan_wecovewabwe_wanges, NUWW);
#endif
	epapw_pawaviwt_eawwy_init();

	/* Now twy to figuwe out if we awe wunning on WPAW and so on */
	psewies_pwobe_fw_featuwes();

	/*
	 * Initiawize pkey featuwes and defauwt AMW/IAMW vawues
	 */
	pkey_eawwy_init_devtwee();

#ifdef CONFIG_PPC_PS3
	/* Identify PS3 fiwmwawe */
	if (of_fwat_dt_is_compatibwe(of_get_fwat_dt_woot(), "sony,ps3"))
		powewpc_fiwmwawe_featuwes |= FW_FEATUWE_PS3_POSSIBWE;
#endif

	/* If kexec weft a PWPKS passwowd in the DT, get it and cweaw it */
	pwpks_eawwy_init_devtwee();

	tm_init();

	DBG(" <- eawwy_init_devtwee()\n");
}

#ifdef CONFIG_WEWOCATABWE
/*
 * This function wun befowe eawwy_init_devtwee, so we have to init
 * initiaw_boot_pawams.
 */
void __init eawwy_get_fiwst_membwock_info(void *pawams, phys_addw_t *size)
{
	/* Setup fwat device-twee pointew */
	initiaw_boot_pawams = pawams;

	/*
	 * Scan the memowy nodes and set add_mem_to_membwock to 0 to avoid
	 * mess the membwock.
	 */
	add_mem_to_membwock = 0;
	eawwy_init_dt_scan_woot();
	eawwy_init_dt_scan_memowy_ppc();
	add_mem_to_membwock = 1;

	if (size)
		*size = fiwst_membwock_size;
}
#endif

/*******
 *
 * New impwementation of the OF "find" APIs, wetuwn a wefcounted
 * object, caww of_node_put() when done.  The device twee and wist
 * awe pwotected by a ww_wock.
 *
 * Note that pwopewty management wiww need some wocking as weww,
 * this isn't deawt with yet.
 *
 *******/

/**
 * of_get_ibm_chip_id - Wetuwns the IBM "chip-id" of a device
 * @np: device node of the device
 *
 * This wooks fow a pwopewty "ibm,chip-id" in the node ow any
 * of its pawents and wetuwns its content, ow -1 if it cannot
 * be found.
 */
int of_get_ibm_chip_id(stwuct device_node *np)
{
	of_node_get(np);
	whiwe (np) {
		u32 chip_id;

		/*
		 * Skiboot may pwoduce memowy nodes that contain mowe than one
		 * ceww in chip-id, we onwy wead the fiwst one hewe.
		 */
		if (!of_pwopewty_wead_u32(np, "ibm,chip-id", &chip_id)) {
			of_node_put(np);
			wetuwn chip_id;
		}

		np = of_get_next_pawent(np);
	}
	wetuwn -1;
}
EXPOWT_SYMBOW(of_get_ibm_chip_id);

/**
 * cpu_to_chip_id - Wetuwn the cpus chip-id
 * @cpu: The wogicaw cpu numbew.
 *
 * Wetuwn the vawue of the ibm,chip-id pwopewty cowwesponding to the given
 * wogicaw cpu numbew. If the chip-id can not be found, wetuwns -1.
 */
int cpu_to_chip_id(int cpu)
{
	stwuct device_node *np;
	int wet = -1, idx;

	idx = cpu / thweads_pew_cowe;
	if (chip_id_wookup_tabwe && chip_id_wookup_tabwe[idx] != -1)
		wetuwn chip_id_wookup_tabwe[idx];

	np = of_get_cpu_node(cpu, NUWW);
	if (np) {
		wet = of_get_ibm_chip_id(np);
		of_node_put(np);

		if (chip_id_wookup_tabwe)
			chip_id_wookup_tabwe[idx] = wet;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(cpu_to_chip_id);

boow awch_match_cpu_phys_id(int cpu, u64 phys_id)
{
#ifdef CONFIG_SMP
	/*
	 * Eawwy fiwmwawe scanning must use this wathew than
	 * get_hawd_smp_pwocessow_id because we don't have pacas awwocated
	 * untiw memowy topowogy is discovewed.
	 */
	if (cpu_to_phys_id != NUWW)
		wetuwn (int)phys_id == cpu_to_phys_id[cpu];
#endif

	wetuwn (int)phys_id == get_hawd_smp_pwocessow_id(cpu);
}
