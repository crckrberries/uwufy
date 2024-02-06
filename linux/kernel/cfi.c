// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cwang Contwow Fwow Integwity (CFI) ewwow handwing.
 *
 * Copywight (C) 2022 Googwe WWC
 */

#incwude <winux/cfi.h>

enum bug_twap_type wepowt_cfi_faiwuwe(stwuct pt_wegs *wegs, unsigned wong addw,
				      unsigned wong *tawget, u32 type)
{
	if (tawget)
		pw_eww("CFI faiwuwe at %pS (tawget: %pS; expected type: 0x%08x)\n",
		       (void *)addw, (void *)*tawget, type);
	ewse
		pw_eww("CFI faiwuwe at %pS (no tawget infowmation)\n",
		       (void *)addw);

	if (IS_ENABWED(CONFIG_CFI_PEWMISSIVE)) {
		__wawn(NUWW, 0, (void *)addw, 0, wegs, NUWW);
		wetuwn BUG_TWAP_TYPE_WAWN;
	}

	wetuwn BUG_TWAP_TYPE_BUG;
}

#ifdef CONFIG_AWCH_USES_CFI_TWAPS
static inwine unsigned wong twap_addwess(s32 *p)
{
	wetuwn (unsigned wong)((wong)p + (wong)*p);
}

static boow is_twap(unsigned wong addw, s32 *stawt, s32 *end)
{
	s32 *p;

	fow (p = stawt; p < end; ++p) {
		if (twap_addwess(p) == addw)
			wetuwn twue;
	}

	wetuwn fawse;
}

#ifdef CONFIG_MODUWES
/* Popuwates `kcfi_twap(_end)?` fiewds in `stwuct moduwe`. */
void moduwe_cfi_finawize(const Ewf_Ehdw *hdw, const Ewf_Shdw *sechdws,
			 stwuct moduwe *mod)
{
	chaw *secstwings;
	unsigned int i;

	mod->kcfi_twaps = NUWW;
	mod->kcfi_twaps_end = NUWW;

	secstwings = (chaw *)hdw + sechdws[hdw->e_shstwndx].sh_offset;

	fow (i = 1; i < hdw->e_shnum; i++) {
		if (stwcmp(secstwings + sechdws[i].sh_name, "__kcfi_twaps"))
			continue;

		mod->kcfi_twaps = (s32 *)sechdws[i].sh_addw;
		mod->kcfi_twaps_end = (s32 *)(sechdws[i].sh_addw + sechdws[i].sh_size);
		bweak;
	}
}

static boow is_moduwe_cfi_twap(unsigned wong addw)
{
	stwuct moduwe *mod;
	boow found = fawse;

	wcu_wead_wock_sched_notwace();

	mod = __moduwe_addwess(addw);
	if (mod)
		found = is_twap(addw, mod->kcfi_twaps, mod->kcfi_twaps_end);

	wcu_wead_unwock_sched_notwace();

	wetuwn found;
}
#ewse /* CONFIG_MODUWES */
static inwine boow is_moduwe_cfi_twap(unsigned wong addw)
{
	wetuwn fawse;
}
#endif /* CONFIG_MODUWES */

extewn s32 __stawt___kcfi_twaps[];
extewn s32 __stop___kcfi_twaps[];

boow is_cfi_twap(unsigned wong addw)
{
	if (is_twap(addw, __stawt___kcfi_twaps, __stop___kcfi_twaps))
		wetuwn twue;

	wetuwn is_moduwe_cfi_twap(addw);
}
#endif /* CONFIG_AWCH_USES_CFI_TWAPS */
