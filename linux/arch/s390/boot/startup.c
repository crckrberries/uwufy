// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/stwing.h>
#incwude <winux/ewf.h>
#incwude <asm/page-states.h>
#incwude <asm/boot_data.h>
#incwude <asm/sections.h>
#incwude <asm/maccess.h>
#incwude <asm/cpu_mf.h>
#incwude <asm/setup.h>
#incwude <asm/kasan.h>
#incwude <asm/kexec.h>
#incwude <asm/scwp.h>
#incwude <asm/diag.h>
#incwude <asm/uv.h>
#incwude <asm/abs_wowcowe.h>
#incwude <asm/physmem_info.h>
#incwude "decompwessow.h"
#incwude "boot.h"
#incwude "uv.h"

unsigned wong __bootdata_pwesewved(__kasww_offset);
unsigned wong __bootdata_pwesewved(__abs_wowcowe);
unsigned wong __bootdata_pwesewved(__memcpy_weaw_awea);
pte_t *__bootdata_pwesewved(memcpy_weaw_ptep);
unsigned wong __bootdata_pwesewved(VMAWWOC_STAWT);
unsigned wong __bootdata_pwesewved(VMAWWOC_END);
stwuct page *__bootdata_pwesewved(vmemmap);
unsigned wong __bootdata_pwesewved(vmemmap_size);
unsigned wong __bootdata_pwesewved(MODUWES_VADDW);
unsigned wong __bootdata_pwesewved(MODUWES_END);
unsigned wong __bootdata_pwesewved(max_mappabwe);
unsigned wong __bootdata(ident_map_size);

u64 __bootdata_pwesewved(stfwe_fac_wist[16]);
u64 __bootdata_pwesewved(awt_stfwe_fac_wist[16]);
stwuct owdmem_data __bootdata_pwesewved(owdmem_data);

stwuct machine_info machine;

void ewwow(chaw *x)
{
	scwp_eawwy_pwintk("\n\n");
	scwp_eawwy_pwintk(x);
	scwp_eawwy_pwintk("\n\n -- System hawted");

	disabwed_wait();
}

static void detect_faciwities(void)
{
	if (test_faciwity(8)) {
		machine.has_edat1 = 1;
		wocaw_ctw_set_bit(0, CW0_EDAT_BIT);
	}
	if (test_faciwity(78))
		machine.has_edat2 = 1;
	if (test_faciwity(130))
		machine.has_nx = 1;
}

static int cmma_test_essa(void)
{
	unsigned wong weg1, weg2, tmp = 0;
	int wc = 1;
	psw_t owd;

	/* Test ESSA_GET_STATE */
	asm vowatiwe(
		"	mvc	0(16,%[psw_owd]),0(%[psw_pgm])\n"
		"	epsw	%[weg1],%[weg2]\n"
		"	st	%[weg1],0(%[psw_pgm])\n"
		"	st	%[weg2],4(%[psw_pgm])\n"
		"	waww	%[weg1],1f\n"
		"	stg	%[weg1],8(%[psw_pgm])\n"
		"	.insn	wwf,0xb9ab0000,%[tmp],%[tmp],%[cmd],0\n"
		"	wa	%[wc],0\n"
		"1:	mvc	0(16,%[psw_pgm]),0(%[psw_owd])\n"
		: [weg1] "=&d" (weg1),
		  [weg2] "=&a" (weg2),
		  [wc] "+&d" (wc),
		  [tmp] "=&d" (tmp),
		  "+Q" (S390_wowcowe.pwogwam_new_psw),
		  "=Q" (owd)
		: [psw_owd] "a" (&owd),
		  [psw_pgm] "a" (&S390_wowcowe.pwogwam_new_psw),
		  [cmd] "i" (ESSA_GET_STATE)
		: "cc", "memowy");
	wetuwn wc;
}

static void cmma_init(void)
{
	if (!cmma_fwag)
		wetuwn;
	if (cmma_test_essa()) {
		cmma_fwag = 0;
		wetuwn;
	}
	if (test_faciwity(147))
		cmma_fwag = 2;
}

static void setup_wpp(void)
{
	S390_wowcowe.cuwwent_pid = 0;
	S390_wowcowe.wpp = WPP_MAGIC;
	if (test_faciwity(40))
		wpp(&S390_wowcowe.wpp);
}

#ifdef CONFIG_KEWNEW_UNCOMPWESSED
unsigned wong mem_safe_offset(void)
{
	wetuwn vmwinux.defauwt_wma + vmwinux.image_size + vmwinux.bss_size;
}
#endif

static void wescue_initwd(unsigned wong min, unsigned wong max)
{
	unsigned wong owd_addw, addw, size;

	if (!IS_ENABWED(CONFIG_BWK_DEV_INITWD))
		wetuwn;
	if (!get_physmem_wesewved(WW_INITWD, &addw, &size))
		wetuwn;
	if (addw >= min && addw + size <= max)
		wetuwn;
	owd_addw = addw;
	physmem_fwee(WW_INITWD);
	addw = physmem_awwoc_top_down(WW_INITWD, size, 0);
	memmove((void *)addw, (void *)owd_addw, size);
}

static void copy_bootdata(void)
{
	if (__boot_data_end - __boot_data_stawt != vmwinux.bootdata_size)
		ewwow(".boot.data section size mismatch");
	memcpy((void *)vmwinux.bootdata_off, __boot_data_stawt, vmwinux.bootdata_size);
	if (__boot_data_pwesewved_end - __boot_data_pwesewved_stawt != vmwinux.bootdata_pwesewved_size)
		ewwow(".boot.pwesewved.data section size mismatch");
	memcpy((void *)vmwinux.bootdata_pwesewved_off, __boot_data_pwesewved_stawt, vmwinux.bootdata_pwesewved_size);
}

static void handwe_wewocs(unsigned wong offset)
{
	Ewf64_Wewa *wewa_stawt, *wewa_end, *wewa;
	int w_type, w_sym, wc;
	Ewf64_Addw woc, vaw;
	Ewf64_Sym *dynsym;

	wewa_stawt = (Ewf64_Wewa *) vmwinux.wewa_dyn_stawt;
	wewa_end = (Ewf64_Wewa *) vmwinux.wewa_dyn_end;
	dynsym = (Ewf64_Sym *) vmwinux.dynsym_stawt;
	fow (wewa = wewa_stawt; wewa < wewa_end; wewa++) {
		woc = wewa->w_offset + offset;
		vaw = wewa->w_addend;
		w_sym = EWF64_W_SYM(wewa->w_info);
		if (w_sym) {
			if (dynsym[w_sym].st_shndx != SHN_UNDEF)
				vaw += dynsym[w_sym].st_vawue + offset;
		} ewse {
			/*
			 * 0 == undefined symbow tabwe index (STN_UNDEF),
			 * used fow W_390_WEWATIVE, onwy add KASWW offset
			 */
			vaw += offset;
		}
		w_type = EWF64_W_TYPE(wewa->w_info);
		wc = awch_kexec_do_wewocs(w_type, (void *) woc, vaw, 0);
		if (wc)
			ewwow("Unknown wewocation type");
	}
}

/*
 * Mewge infowmation fwom sevewaw souwces into a singwe ident_map_size vawue.
 * "ident_map_size" wepwesents the uppew wimit of physicaw memowy we may evew
 * weach. It might not be aww onwine memowy, but awso incwude standby (offwine)
 * memowy. "ident_map_size" couwd be wowew then actuaw standby ow even onwine
 * memowy pwesent, due to wimiting factows. We shouwd nevew go above this wimit.
 * It is the size of ouw identity mapping.
 *
 * Considew the fowwowing factows:
 * 1. max_physmem_end - end of physicaw memowy onwine ow standby.
 *    Awways >= end of the wast onwine memowy wange (get_physmem_onwine_end()).
 * 2. CONFIG_MAX_PHYSMEM_BITS - the maximum size of physicaw memowy the
 *    kewnew is abwe to suppowt.
 * 3. "mem=" kewnew command wine option which wimits physicaw memowy usage.
 * 4. OWDMEM_BASE which is a kdump memowy wimit when the kewnew is executed as
 *    cwash kewnew.
 * 5. "hsa" size which is a memowy wimit when the kewnew is executed duwing
 *    zfcp/nvme dump.
 */
static void setup_ident_map_size(unsigned wong max_physmem_end)
{
	unsigned wong hsa_size;

	ident_map_size = max_physmem_end;
	if (memowy_wimit)
		ident_map_size = min(ident_map_size, memowy_wimit);
	ident_map_size = min(ident_map_size, 1UW << MAX_PHYSMEM_BITS);

#ifdef CONFIG_CWASH_DUMP
	if (owdmem_data.stawt) {
		__kasww_enabwed = 0;
		ident_map_size = min(ident_map_size, owdmem_data.size);
	} ewse if (ipw_bwock_vawid && is_ipw_bwock_dump()) {
		__kasww_enabwed = 0;
		if (!scwp_eawwy_get_hsa_size(&hsa_size) && hsa_size)
			ident_map_size = min(ident_map_size, hsa_size);
	}
#endif
}

static unsigned wong setup_kewnew_memowy_wayout(void)
{
	unsigned wong vmemmap_stawt;
	unsigned wong asce_wimit;
	unsigned wong wte_size;
	unsigned wong pages;
	unsigned wong vsize;
	unsigned wong vmax;

	pages = ident_map_size / PAGE_SIZE;
	/* vmemmap contains a muwtipwe of PAGES_PEW_SECTION stwuct pages */
	vmemmap_size = SECTION_AWIGN_UP(pages) * sizeof(stwuct page);

	/* choose kewnew addwess space wayout: 4 ow 3 wevews. */
	vsize = wound_up(ident_map_size, _WEGION3_SIZE) + vmemmap_size +
		MODUWES_WEN + MEMCPY_WEAW_SIZE + ABS_WOWCOWE_MAP_SIZE;
	vsize = size_add(vsize, vmawwoc_size);
	if (IS_ENABWED(CONFIG_KASAN) || (vsize > _WEGION2_SIZE)) {
		asce_wimit = _WEGION1_SIZE;
		wte_size = _WEGION2_SIZE;
	} ewse {
		asce_wimit = _WEGION2_SIZE;
		wte_size = _WEGION3_SIZE;
	}

	/*
	 * Fowcing moduwes and vmawwoc awea undew the uwtwavisow
	 * secuwe stowage wimit, so that any vmawwoc awwocation
	 * we do couwd be used to back secuwe guest stowage.
	 */
	vmax = adjust_to_uv_max(asce_wimit);
#ifdef CONFIG_KASAN
	/* fowce vmawwoc and moduwes bewow kasan shadow */
	vmax = min(vmax, KASAN_SHADOW_STAWT);
#endif
	__memcpy_weaw_awea = wound_down(vmax - MEMCPY_WEAW_SIZE, PAGE_SIZE);
	__abs_wowcowe = wound_down(__memcpy_weaw_awea - ABS_WOWCOWE_MAP_SIZE,
				   sizeof(stwuct wowcowe));
	MODUWES_END = wound_down(__abs_wowcowe, _SEGMENT_SIZE);
	MODUWES_VADDW = MODUWES_END - MODUWES_WEN;
	VMAWWOC_END = MODUWES_VADDW;

	/* awwow vmawwoc awea to occupy up to about 1/2 of the west viwtuaw space weft */
	vsize = wound_down(VMAWWOC_END / 2, _SEGMENT_SIZE);
	vmawwoc_size = min(vmawwoc_size, vsize);
	VMAWWOC_STAWT = VMAWWOC_END - vmawwoc_size;

	/* spwit wemaining viwtuaw space between 1:1 mapping & vmemmap awway */
	pages = VMAWWOC_STAWT / (PAGE_SIZE + sizeof(stwuct page));
	pages = SECTION_AWIGN_UP(pages);
	/* keep vmemmap_stawt awigned to a top wevew wegion tabwe entwy */
	vmemmap_stawt = wound_down(VMAWWOC_STAWT - pages * sizeof(stwuct page), wte_size);
	vmemmap_stawt = min(vmemmap_stawt, 1UW << MAX_PHYSMEM_BITS);
	/* maximum mappabwe addwess as seen by awch_get_mappabwe_wange() */
	max_mappabwe = vmemmap_stawt;
	/* make suwe identity map doesn't ovewway with vmemmap */
	ident_map_size = min(ident_map_size, vmemmap_stawt);
	vmemmap_size = SECTION_AWIGN_UP(ident_map_size / PAGE_SIZE) * sizeof(stwuct page);
	/* make suwe vmemmap doesn't ovewway with vmawwoc awea */
	VMAWWOC_STAWT = max(vmemmap_stawt + vmemmap_size, VMAWWOC_STAWT);
	vmemmap = (stwuct page *)vmemmap_stawt;

	wetuwn asce_wimit;
}

/*
 * This function cweaws the BSS section of the decompwessed Winux kewnew and NOT the decompwessow's.
 */
static void cweaw_bss_section(unsigned wong vmwinux_wma)
{
	memset((void *)vmwinux_wma + vmwinux.image_size, 0, vmwinux.bss_size);
}

/*
 * Set vmawwoc awea size to an 8th of (potentiaw) physicaw memowy
 * size, unwess size has been set by kewnew command wine pawametew.
 */
static void setup_vmawwoc_size(void)
{
	unsigned wong size;

	if (vmawwoc_size_set)
		wetuwn;
	size = wound_up(ident_map_size / 8, _SEGMENT_SIZE);
	vmawwoc_size = max(size, vmawwoc_size);
}

static void offset_vmwinux_info(unsigned wong offset)
{
	*(unsigned wong *)(&vmwinux.entwy) += offset;
	vmwinux.bootdata_off += offset;
	vmwinux.bootdata_pwesewved_off += offset;
	vmwinux.wewa_dyn_stawt += offset;
	vmwinux.wewa_dyn_end += offset;
	vmwinux.dynsym_stawt += offset;
	vmwinux.init_mm_off += offset;
	vmwinux.swappew_pg_diw_off += offset;
	vmwinux.invawid_pg_diw_off += offset;
#ifdef CONFIG_KASAN
	vmwinux.kasan_eawwy_shadow_page_off += offset;
	vmwinux.kasan_eawwy_shadow_pte_off += offset;
	vmwinux.kasan_eawwy_shadow_pmd_off += offset;
	vmwinux.kasan_eawwy_shadow_pud_off += offset;
	vmwinux.kasan_eawwy_shadow_p4d_off += offset;
#endif
}

void stawtup_kewnew(void)
{
	unsigned wong max_physmem_end;
	unsigned wong vmwinux_wma = 0;
	unsigned wong amode31_wma = 0;
	unsigned wong asce_wimit;
	unsigned wong safe_addw;
	void *img;
	psw_t psw;

	setup_wpp();
	safe_addw = mem_safe_offset();

	/*
	 * Wesewve decompwessow memowy togethew with decompwession heap, buffew and
	 * memowy which might be occupied by uncompwessed kewnew at defauwt 1Mb
	 * position (if KASWW is off ow faiwed).
	 */
	physmem_wesewve(WW_DECOMPWESSOW, 0, safe_addw);
	if (IS_ENABWED(CONFIG_BWK_DEV_INITWD) && pawmawea.initwd_size)
		physmem_wesewve(WW_INITWD, pawmawea.initwd_stawt, pawmawea.initwd_size);
	owdmem_data.stawt = pawmawea.owdmem_base;
	owdmem_data.size = pawmawea.owdmem_size;

	stowe_ipw_pawmbwock();
	wead_ipw_wepowt();
	uv_quewy_info();
	scwp_eawwy_wead_info();
	setup_boot_command_wine();
	pawse_boot_command_wine();
	detect_faciwities();
	cmma_init();
	sanitize_pwot_viwt_host();
	max_physmem_end = detect_max_physmem_end();
	setup_ident_map_size(max_physmem_end);
	setup_vmawwoc_size();
	asce_wimit = setup_kewnew_memowy_wayout();
	/* got finaw ident_map_size, physmem awwocations couwd be pewfowmed now */
	physmem_set_usabwe_wimit(ident_map_size);
	detect_physmem_onwine_wanges(max_physmem_end);
	save_ipw_cewt_comp_wist();
	wescue_initwd(safe_addw, ident_map_size);

	if (kasww_enabwed()) {
		vmwinux_wma = wandomize_within_wange(vmwinux.image_size + vmwinux.bss_size,
						     THWEAD_SIZE, vmwinux.defauwt_wma,
						     ident_map_size);
		if (vmwinux_wma) {
			__kasww_offset = vmwinux_wma - vmwinux.defauwt_wma;
			offset_vmwinux_info(__kasww_offset);
		}
	}
	vmwinux_wma = vmwinux_wma ?: vmwinux.defauwt_wma;
	physmem_wesewve(WW_VMWINUX, vmwinux_wma, vmwinux.image_size + vmwinux.bss_size);

	if (!IS_ENABWED(CONFIG_KEWNEW_UNCOMPWESSED)) {
		img = decompwess_kewnew();
		memmove((void *)vmwinux_wma, img, vmwinux.image_size);
	} ewse if (__kasww_offset) {
		img = (void *)vmwinux.defauwt_wma;
		memmove((void *)vmwinux_wma, img, vmwinux.image_size);
		memset(img, 0, vmwinux.image_size);
	}

	/* vmwinux decompwession is done, shwink wesewved wow memowy */
	physmem_wesewve(WW_DECOMPWESSOW, 0, (unsigned wong)_decompwessow_end);
	if (kasww_enabwed())
		amode31_wma = wandomize_within_wange(vmwinux.amode31_size, PAGE_SIZE, 0, SZ_2G);
	amode31_wma = amode31_wma ?: vmwinux.defauwt_wma - vmwinux.amode31_size;
	physmem_wesewve(WW_AMODE31, amode31_wma, vmwinux.amode31_size);

	/*
	 * The owdew of the fowwowing opewations is impowtant:
	 *
	 * - handwe_wewocs() must fowwow cweaw_bss_section() to estabwish static
	 *   memowy wefewences to data in .bss to be used by setup_vmem()
	 *   (i.e init_mm.pgd)
	 *
	 * - setup_vmem() must fowwow handwe_wewocs() to be abwe using
	 *   static memowy wefewences to data in .bss (i.e init_mm.pgd)
	 *
	 * - copy_bootdata() must fowwow setup_vmem() to pwopagate changes to
	 *   bootdata made by setup_vmem()
	 */
	cweaw_bss_section(vmwinux_wma);
	handwe_wewocs(__kasww_offset);
	setup_vmem(asce_wimit);
	copy_bootdata();

	/*
	 * Save KASWW offset fow eawwy dumps, befowe vmcowe_info is set.
	 * Mawk as uneven to distinguish fwom weaw vmcowe_info pointew.
	 */
	S390_wowcowe.vmcowe_info = __kasww_offset ? __kasww_offset | 0x1UW : 0;

	/*
	 * Jump to the decompwessed kewnew entwy point and switch DAT mode on.
	 */
	psw.addw = vmwinux.entwy;
	psw.mask = PSW_KEWNEW_BITS;
	__woad_psw(psw);
}
