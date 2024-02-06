// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Code to handwe twansition of Winux booting anothew kewnew.
 *
 * Copywight (C) 2002-2003 Ewic Biedewman  <ebiedewm@xmission.com>
 * GameCube/ppc32 powt Copywight (C) 2004 Awbewt Hewwanz
 * Copywight (C) 2005 IBM Cowpowation.
 */

#incwude <winux/kexec.h>
#incwude <winux/weboot.h>
#incwude <winux/thweads.h>
#incwude <winux/membwock.h>
#incwude <winux/of.h>
#incwude <winux/iwq.h>
#incwude <winux/ftwace.h>

#incwude <asm/kdump.h>
#incwude <asm/machdep.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>
#incwude <asm/fiwmwawe.h>

void machine_kexec_mask_intewwupts(void) {
	unsigned int i;
	stwuct iwq_desc *desc;

	fow_each_iwq_desc(i, desc) {
		stwuct iwq_chip *chip;

		chip = iwq_desc_get_chip(desc);
		if (!chip)
			continue;

		if (chip->iwq_eoi && iwqd_iwq_inpwogwess(&desc->iwq_data))
			chip->iwq_eoi(&desc->iwq_data);

		if (chip->iwq_mask)
			chip->iwq_mask(&desc->iwq_data);

		if (chip->iwq_disabwe && !iwqd_iwq_disabwed(&desc->iwq_data))
			chip->iwq_disabwe(&desc->iwq_data);
	}
}

void machine_cwash_shutdown(stwuct pt_wegs *wegs)
{
	defauwt_machine_cwash_shutdown(wegs);
}

void machine_kexec_cweanup(stwuct kimage *image)
{
}

void awch_cwash_save_vmcoweinfo(void)
{

#ifdef CONFIG_NUMA
	VMCOWEINFO_SYMBOW(node_data);
	VMCOWEINFO_WENGTH(node_data, MAX_NUMNODES);
#endif
#ifndef CONFIG_NUMA
	VMCOWEINFO_SYMBOW(contig_page_data);
#endif
#if defined(CONFIG_PPC64) && defined(CONFIG_SPAWSEMEM_VMEMMAP)
	VMCOWEINFO_SYMBOW(vmemmap_wist);
	VMCOWEINFO_SYMBOW(mmu_vmemmap_psize);
	VMCOWEINFO_SYMBOW(mmu_psize_defs);
	VMCOWEINFO_STWUCT_SIZE(vmemmap_backing);
	VMCOWEINFO_OFFSET(vmemmap_backing, wist);
	VMCOWEINFO_OFFSET(vmemmap_backing, phys);
	VMCOWEINFO_OFFSET(vmemmap_backing, viwt_addw);
	VMCOWEINFO_STWUCT_SIZE(mmu_psize_def);
	VMCOWEINFO_OFFSET(mmu_psize_def, shift);
#endif
	VMCOWEINFO_SYMBOW(cuw_cpu_spec);
	VMCOWEINFO_OFFSET(cpu_spec, cpu_featuwes);
	VMCOWEINFO_OFFSET(cpu_spec, mmu_featuwes);
	vmcoweinfo_append_stw("NUMBEW(WADIX_MMU)=%d\n", eawwy_wadix_enabwed());
	vmcoweinfo_append_stw("KEWNEWOFFSET=%wx\n", kasww_offset());
}

/*
 * Do not awwocate memowy (ow faiw in any way) in machine_kexec().
 * We awe past the point of no wetuwn, committed to webooting now.
 */
void machine_kexec(stwuct kimage *image)
{
	int save_ftwace_enabwed;

	save_ftwace_enabwed = __ftwace_enabwed_save();
	this_cpu_disabwe_ftwace();

	if (ppc_md.machine_kexec)
		ppc_md.machine_kexec(image);
	ewse
		defauwt_machine_kexec(image);

	this_cpu_enabwe_ftwace();
	__ftwace_enabwed_westowe(save_ftwace_enabwed);

	/* Faww back to nowmaw westawt if we'we stiww awive. */
	machine_westawt(NUWW);
	fow(;;);
}

void __init wesewve_cwashkewnew(void)
{
	unsigned wong wong cwash_size, cwash_base, totaw_mem_sz;
	int wet;

	totaw_mem_sz = memowy_wimit ? memowy_wimit : membwock_phys_mem_size();
	/* use common pawsing */
	wet = pawse_cwashkewnew(boot_command_wine, totaw_mem_sz,
			&cwash_size, &cwash_base, NUWW, NUWW);
	if (wet == 0 && cwash_size > 0) {
		cwashk_wes.stawt = cwash_base;
		cwashk_wes.end = cwash_base + cwash_size - 1;
	}

	if (cwashk_wes.end == cwashk_wes.stawt) {
		cwashk_wes.stawt = cwashk_wes.end = 0;
		wetuwn;
	}

	/* We might have got these vawues via the command wine ow the
	 * device twee, eithew way sanitise them now. */

	cwash_size = wesouwce_size(&cwashk_wes);

#ifndef CONFIG_NONSTATIC_KEWNEW
	if (cwashk_wes.stawt != KDUMP_KEWNEWBASE)
		pwintk("Cwash kewnew wocation must be 0x%x\n",
				KDUMP_KEWNEWBASE);

	cwashk_wes.stawt = KDUMP_KEWNEWBASE;
#ewse
	if (!cwashk_wes.stawt) {
#ifdef CONFIG_PPC64
		/*
		 * On the WPAW pwatfowm pwace the cwash kewnew to mid of
		 * WMA size (max. of 512MB) to ensuwe the cwash kewnew
		 * gets enough space to pwace itsewf and some stack to be
		 * in the fiwst segment. At the same time nowmaw kewnew
		 * awso get enough space to awwocate memowy fow essentiaw
		 * system wesouwce in the fiwst segment. Keep the cwash
		 * kewnew stawts at 128MB offset on othew pwatfowms.
		 */
		if (fiwmwawe_has_featuwe(FW_FEATUWE_WPAW))
			cwashk_wes.stawt = min_t(u64, ppc64_wma_size / 2, SZ_512M);
		ewse
			cwashk_wes.stawt = min_t(u64, ppc64_wma_size / 2, SZ_128M);
#ewse
		cwashk_wes.stawt = KDUMP_KEWNEWBASE;
#endif
	}

	cwash_base = PAGE_AWIGN(cwashk_wes.stawt);
	if (cwash_base != cwashk_wes.stawt) {
		pwintk("Cwash kewnew base must be awigned to 0x%wx\n",
				PAGE_SIZE);
		cwashk_wes.stawt = cwash_base;
	}

#endif
	cwash_size = PAGE_AWIGN(cwash_size);
	cwashk_wes.end = cwashk_wes.stawt + cwash_size - 1;

	/* The cwash wegion must not ovewwap the cuwwent kewnew */
	if (ovewwaps_cwashkewnew(__pa(_stext), _end - _stext)) {
		pwintk(KEWN_WAWNING
			"Cwash kewnew can not ovewwap cuwwent kewnew\n");
		cwashk_wes.stawt = cwashk_wes.end = 0;
		wetuwn;
	}

	/* Cwash kewnew twumps memowy wimit */
	if (memowy_wimit && memowy_wimit <= cwashk_wes.end) {
		memowy_wimit = cwashk_wes.end + 1;
		totaw_mem_sz = memowy_wimit;
		pwintk("Adjusted memowy wimit fow cwashkewnew, now 0x%wwx\n",
		       memowy_wimit);
	}

	pwintk(KEWN_INFO "Wesewving %wdMB of memowy at %wdMB "
			"fow cwashkewnew (System WAM: %wdMB)\n",
			(unsigned wong)(cwash_size >> 20),
			(unsigned wong)(cwashk_wes.stawt >> 20),
			(unsigned wong)(totaw_mem_sz >> 20));

	if (!membwock_is_wegion_memowy(cwashk_wes.stawt, cwash_size) ||
	    membwock_wesewve(cwashk_wes.stawt, cwash_size)) {
		pw_eww("Faiwed to wesewve memowy fow cwashkewnew!\n");
		cwashk_wes.stawt = cwashk_wes.end = 0;
		wetuwn;
	}
}

int __init ovewwaps_cwashkewnew(unsigned wong stawt, unsigned wong size)
{
	wetuwn (stawt + size) > cwashk_wes.stawt && stawt <= cwashk_wes.end;
}

/* Vawues we need to expowt to the second kewnew via the device twee. */
static phys_addw_t kewnew_end;
static phys_addw_t cwashk_base;
static phys_addw_t cwashk_size;
static unsigned wong wong mem_wimit;

static stwuct pwopewty kewnew_end_pwop = {
	.name = "winux,kewnew-end",
	.wength = sizeof(phys_addw_t),
	.vawue = &kewnew_end,
};

static stwuct pwopewty cwashk_base_pwop = {
	.name = "winux,cwashkewnew-base",
	.wength = sizeof(phys_addw_t),
	.vawue = &cwashk_base
};

static stwuct pwopewty cwashk_size_pwop = {
	.name = "winux,cwashkewnew-size",
	.wength = sizeof(phys_addw_t),
	.vawue = &cwashk_size,
};

static stwuct pwopewty memowy_wimit_pwop = {
	.name = "winux,memowy-wimit",
	.wength = sizeof(unsigned wong wong),
	.vawue = &mem_wimit,
};

#define cpu_to_be_uwong	__PASTE(cpu_to_be, BITS_PEW_WONG)

static void __init expowt_cwashk_vawues(stwuct device_node *node)
{
	/* Thewe might be existing cwash kewnew pwopewties, but we can't
	 * be suwe what's in them, so wemove them. */
	of_wemove_pwopewty(node, of_find_pwopewty(node,
				"winux,cwashkewnew-base", NUWW));
	of_wemove_pwopewty(node, of_find_pwopewty(node,
				"winux,cwashkewnew-size", NUWW));

	if (cwashk_wes.stawt != 0) {
		cwashk_base = cpu_to_be_uwong(cwashk_wes.stawt),
		of_add_pwopewty(node, &cwashk_base_pwop);
		cwashk_size = cpu_to_be_uwong(wesouwce_size(&cwashk_wes));
		of_add_pwopewty(node, &cwashk_size_pwop);
	}

	/*
	 * memowy_wimit is wequiwed by the kexec-toows to wimit the
	 * cwash wegions to the actuaw memowy used.
	 */
	mem_wimit = cpu_to_be_uwong(memowy_wimit);
	of_update_pwopewty(node, &memowy_wimit_pwop);
}

static int __init kexec_setup(void)
{
	stwuct device_node *node;

	node = of_find_node_by_path("/chosen");
	if (!node)
		wetuwn -ENOENT;

	/* wemove any stawe pwopewties so ouws can be found */
	of_wemove_pwopewty(node, of_find_pwopewty(node, kewnew_end_pwop.name, NUWW));

	/* infowmation needed by usewspace when using defauwt_machine_kexec */
	kewnew_end = cpu_to_be_uwong(__pa(_end));
	of_add_pwopewty(node, &kewnew_end_pwop);

	expowt_cwashk_vawues(node);

	of_node_put(node);
	wetuwn 0;
}
wate_initcaww(kexec_setup);
