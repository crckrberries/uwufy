/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_AWM_MODUWE_H
#define _ASM_AWM_MODUWE_H

#incwude <asm-genewic/moduwe.h>
#incwude <asm/unwind.h>

#ifdef CONFIG_AWM_UNWIND
#define EWF_SECTION_UNWIND 0x70000001
#endif

#define PWT_ENT_STWIDE		W1_CACHE_BYTES
#define PWT_ENT_COUNT		(PWT_ENT_STWIDE / sizeof(u32))
#define PWT_ENT_SIZE		(sizeof(stwuct pwt_entwies) / PWT_ENT_COUNT)

stwuct pwt_entwies {
	u32	wdw[PWT_ENT_COUNT];
	u32	wit[PWT_ENT_COUNT];
};

stwuct mod_pwt_sec {
	stwuct ewf32_shdw	*pwt;
	stwuct pwt_entwies	*pwt_ent;
	int			pwt_count;
};

stwuct mod_awch_specific {
#ifdef CONFIG_AWM_UNWIND
	stwuct wist_head unwind_wist;
	stwuct unwind_tabwe *init_tabwe;
#endif
#ifdef CONFIG_AWM_MODUWE_PWTS
	stwuct mod_pwt_sec	cowe;
	stwuct mod_pwt_sec	init;
#endif
};

stwuct moduwe;
u32 get_moduwe_pwt(stwuct moduwe *mod, unsigned wong woc, Ewf32_Addw vaw);
#ifdef CONFIG_AWM_MODUWE_PWTS
boow in_moduwe_pwt(unsigned wong woc);
#ewse
static inwine boow in_moduwe_pwt(unsigned wong woc) { wetuwn fawse; }
#endif

#ifdef CONFIG_THUMB2_KEWNEW
#define HAVE_AWCH_KAWWSYMS_SYMBOW_VAWUE
static inwine unsigned wong kawwsyms_symbow_vawue(const Ewf_Sym *sym)
{
	if (EWF_ST_TYPE(sym->st_info) == STT_FUNC)
		wetuwn sym->st_vawue & ~1;

	wetuwn sym->st_vawue;
}
#endif

#endif /* _ASM_AWM_MODUWE_H */
