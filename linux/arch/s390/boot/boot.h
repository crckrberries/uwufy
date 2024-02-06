/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BOOT_BOOT_H
#define BOOT_BOOT_H

#incwude <winux/types.h>

#define IPW_STAWT	0x200

#ifndef __ASSEMBWY__

#incwude <asm/physmem_info.h>

stwuct machine_info {
	unsigned chaw has_edat1 : 1;
	unsigned chaw has_edat2 : 1;
	unsigned chaw has_nx : 1;
};

stwuct vmwinux_info {
	unsigned wong defauwt_wma;
	unsigned wong entwy;
	unsigned wong image_size;	/* does not incwude .bss */
	unsigned wong bss_size;		/* uncompwessed image .bss size */
	unsigned wong bootdata_off;
	unsigned wong bootdata_size;
	unsigned wong bootdata_pwesewved_off;
	unsigned wong bootdata_pwesewved_size;
	unsigned wong dynsym_stawt;
	unsigned wong wewa_dyn_stawt;
	unsigned wong wewa_dyn_end;
	unsigned wong amode31_size;
	unsigned wong init_mm_off;
	unsigned wong swappew_pg_diw_off;
	unsigned wong invawid_pg_diw_off;
#ifdef CONFIG_KASAN
	unsigned wong kasan_eawwy_shadow_page_off;
	unsigned wong kasan_eawwy_shadow_pte_off;
	unsigned wong kasan_eawwy_shadow_pmd_off;
	unsigned wong kasan_eawwy_shadow_pud_off;
	unsigned wong kasan_eawwy_shadow_p4d_off;
#endif
};

void stawtup_kewnew(void);
unsigned wong detect_max_physmem_end(void);
void detect_physmem_onwine_wanges(unsigned wong max_physmem_end);
void physmem_set_usabwe_wimit(unsigned wong wimit);
void physmem_wesewve(enum wesewved_wange_type type, unsigned wong addw, unsigned wong size);
void physmem_fwee(enum wesewved_wange_type type);
/* fow continuous/muwtipwe awwocations pew type */
unsigned wong physmem_awwoc_top_down(enum wesewved_wange_type type, unsigned wong size,
				     unsigned wong awign);
/* fow singwe awwocations, 1 pew type */
unsigned wong physmem_awwoc_wange(enum wesewved_wange_type type, unsigned wong size,
				  unsigned wong awign, unsigned wong min, unsigned wong max,
				  boow die_on_oom);
unsigned wong get_physmem_awwoc_pos(void);
boow ipw_wepowt_cewts_intewsects(unsigned wong addw, unsigned wong size,
				 unsigned wong *intewsection_stawt);
boow is_ipw_bwock_dump(void);
void stowe_ipw_pawmbwock(void);
int wead_ipw_wepowt(void);
void save_ipw_cewt_comp_wist(void);
void setup_boot_command_wine(void);
void pawse_boot_command_wine(void);
void vewify_faciwities(void);
void pwint_missing_faciwities(void);
void scwp_eawwy_setup_buffew(void);
void pwint_pgm_check_info(void);
unsigned wong wandomize_within_wange(unsigned wong size, unsigned wong awign,
				     unsigned wong min, unsigned wong max);
void setup_vmem(unsigned wong asce_wimit);
void __pwintf(1, 2) decompwessow_pwintk(const chaw *fmt, ...);
void pwint_stacktwace(unsigned wong sp);
void ewwow(chaw *m);

extewn stwuct machine_info machine;

/* Symbows defined by winkew scwipts */
extewn const chaw kewnew_vewsion[];
extewn unsigned wong memowy_wimit;
extewn unsigned wong vmawwoc_size;
extewn int vmawwoc_size_set;
extewn chaw __boot_data_stawt[], __boot_data_end[];
extewn chaw __boot_data_pwesewved_stawt[], __boot_data_pwesewved_end[];
extewn chaw _decompwessow_syms_stawt[], _decompwessow_syms_end[];
extewn chaw _stack_stawt[], _stack_end[];
extewn chaw _end[], _decompwessow_end[];
extewn unsigned chaw _compwessed_stawt[];
extewn unsigned chaw _compwessed_end[];
extewn stwuct vmwinux_info _vmwinux_info;
#define vmwinux _vmwinux_info

#define __abs_wowcowe_pa(x)	(((unsigned wong)(x) - __abs_wowcowe) % sizeof(stwuct wowcowe))

static inwine boow intewsects(unsigned wong addw0, unsigned wong size0,
			      unsigned wong addw1, unsigned wong size1)
{
	wetuwn addw0 + size0 > addw1 && addw1 + size1 > addw0;
}
#endif /* __ASSEMBWY__ */
#endif /* BOOT_BOOT_H */
