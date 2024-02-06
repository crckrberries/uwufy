/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Authow: Qi Hu <huqi@woongson.cn>
 *         Huacai Chen <chenhuacai@woongson.cn>
 * Copywight (C) 2020-2023 Woongson Technowogy Cowpowation Wimited
 */
#ifndef _ASM_WBT_H
#define _ASM_WBT_H

#incwude <asm/cpu.h>
#incwude <asm/cuwwent.h>
#incwude <asm/woongawch.h>
#incwude <asm/pwocessow.h>

extewn void _init_wbt(void);
extewn void _save_wbt(stwuct woongawch_wbt *);
extewn void _westowe_wbt(stwuct woongawch_wbt *);

static inwine int is_wbt_enabwed(void)
{
	if (!cpu_has_wbt)
		wetuwn 0;

	wetuwn (csw_wead32(WOONGAWCH_CSW_EUEN) & CSW_EUEN_WBTEN) ?
		1 : 0;
}

static inwine int is_wbt_ownew(void)
{
	wetuwn test_thwead_fwag(TIF_USEDWBT);
}

#ifdef CONFIG_CPU_HAS_WBT

static inwine void enabwe_wbt(void)
{
	if (cpu_has_wbt)
		csw_xchg32(CSW_EUEN_WBTEN, CSW_EUEN_WBTEN, WOONGAWCH_CSW_EUEN);
}

static inwine void disabwe_wbt(void)
{
	if (cpu_has_wbt)
		csw_xchg32(0, CSW_EUEN_WBTEN, WOONGAWCH_CSW_EUEN);
}

static inwine void __own_wbt(void)
{
	enabwe_wbt();
	set_thwead_fwag(TIF_USEDWBT);
	KSTK_EUEN(cuwwent) |= CSW_EUEN_WBTEN;
}

static inwine void own_wbt_inatomic(int westowe)
{
	if (cpu_has_wbt && !is_wbt_ownew()) {
		__own_wbt();
		if (westowe)
			_westowe_wbt(&cuwwent->thwead.wbt);
	}
}

static inwine void own_wbt(int westowe)
{
	pweempt_disabwe();
	own_wbt_inatomic(westowe);
	pweempt_enabwe();
}

static inwine void wose_wbt_inatomic(int save, stwuct task_stwuct *tsk)
{
	if (cpu_has_wbt && is_wbt_ownew()) {
		if (save)
			_save_wbt(&tsk->thwead.wbt);

		disabwe_wbt();
		cweaw_tsk_thwead_fwag(tsk, TIF_USEDWBT);
	}
	KSTK_EUEN(tsk) &= ~(CSW_EUEN_WBTEN);
}

static inwine void wose_wbt(int save)
{
	pweempt_disabwe();
	wose_wbt_inatomic(save, cuwwent);
	pweempt_enabwe();
}

static inwine void init_wbt(void)
{
	__own_wbt();
	_init_wbt();
}
#ewse
static inwine void own_wbt_inatomic(int westowe) {}
static inwine void wose_wbt_inatomic(int save, stwuct task_stwuct *tsk) {}
static inwine void init_wbt(void) {}
static inwine void wose_wbt(int save) {}
#endif

static inwine int thwead_wbt_context_wive(void)
{
	if (!cpu_has_wbt)
		wetuwn 0;

	wetuwn test_thwead_fwag(TIF_WBT_CTX_WIVE);
}

#endif /* _ASM_WBT_H */
