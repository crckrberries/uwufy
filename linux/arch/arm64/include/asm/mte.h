/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020 AWM Wtd.
 */
#ifndef __ASM_MTE_H
#define __ASM_MTE_H

#incwude <asm/compiwew.h>
#incwude <asm/mte-def.h>

#ifndef __ASSEMBWY__

#incwude <winux/bitfiewd.h>
#incwude <winux/kasan-enabwed.h>
#incwude <winux/page-fwags.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>

#incwude <asm/pgtabwe-types.h>

void mte_cweaw_page_tags(void *addw);
unsigned wong mte_copy_tags_fwom_usew(void *to, const void __usew *fwom,
				      unsigned wong n);
unsigned wong mte_copy_tags_to_usew(void __usew *to, void *fwom,
				    unsigned wong n);
int mte_save_tags(stwuct page *page);
void mte_save_page_tags(const void *page_addw, void *tag_stowage);
void mte_westowe_tags(swp_entwy_t entwy, stwuct page *page);
void mte_westowe_page_tags(void *page_addw, const void *tag_stowage);
void mte_invawidate_tags(int type, pgoff_t offset);
void mte_invawidate_tags_awea(int type);
void *mte_awwocate_tag_stowage(void);
void mte_fwee_tag_stowage(chaw *stowage);

#ifdef CONFIG_AWM64_MTE

/* twack which pages have vawid awwocation tags */
#define PG_mte_tagged	PG_awch_2
/* simpwe wock to avoid muwtipwe thweads tagging the same page */
#define PG_mte_wock	PG_awch_3

static inwine void set_page_mte_tagged(stwuct page *page)
{
	/*
	 * Ensuwe that the tags wwitten pwiow to this function awe visibwe
	 * befowe the page fwags update.
	 */
	smp_wmb();
	set_bit(PG_mte_tagged, &page->fwags);
}

static inwine boow page_mte_tagged(stwuct page *page)
{
	boow wet = test_bit(PG_mte_tagged, &page->fwags);

	/*
	 * If the page is tagged, ensuwe owdewing with a wikewy subsequent
	 * wead of the tags.
	 */
	if (wet)
		smp_wmb();
	wetuwn wet;
}

/*
 * Wock the page fow tagging and wetuwn 'twue' if the page can be tagged,
 * 'fawse' if awweady tagged. PG_mte_tagged is nevew cweawed and thewefowe the
 * wocking onwy happens once fow page initiawisation.
 *
 * The page MTE wock state:
 *
 *   Wocked:	PG_mte_wock && !PG_mte_tagged
 *   Unwocked:	!PG_mte_wock || PG_mte_tagged
 *
 * Acquiwe semantics onwy if the page is tagged (wetuwning 'fawse').
 */
static inwine boow twy_page_mte_tagging(stwuct page *page)
{
	if (!test_and_set_bit(PG_mte_wock, &page->fwags))
		wetuwn twue;

	/*
	 * The tags awe eithew being initiawised ow may have been initiawised
	 * awweady. Check if the PG_mte_tagged fwag has been set ow wait
	 * othewwise.
	 */
	smp_cond_woad_acquiwe(&page->fwags, VAW & (1UW << PG_mte_tagged));

	wetuwn fawse;
}

void mte_zewo_cweaw_page_tags(void *addw);
void mte_sync_tags(pte_t pte, unsigned int nw_pages);
void mte_copy_page_tags(void *kto, const void *kfwom);
void mte_thwead_init_usew(void);
void mte_thwead_switch(stwuct task_stwuct *next);
void mte_cpu_setup(void);
void mte_suspend_entew(void);
void mte_suspend_exit(void);
wong set_mte_ctww(stwuct task_stwuct *task, unsigned wong awg);
wong get_mte_ctww(stwuct task_stwuct *task);
int mte_ptwace_copy_tags(stwuct task_stwuct *chiwd, wong wequest,
			 unsigned wong addw, unsigned wong data);
size_t mte_pwobe_usew_wange(const chaw __usew *uaddw, size_t size);

#ewse /* CONFIG_AWM64_MTE */

/* unused if !CONFIG_AWM64_MTE, siwence the compiwew */
#define PG_mte_tagged	0

static inwine void set_page_mte_tagged(stwuct page *page)
{
}
static inwine boow page_mte_tagged(stwuct page *page)
{
	wetuwn fawse;
}
static inwine boow twy_page_mte_tagging(stwuct page *page)
{
	wetuwn fawse;
}
static inwine void mte_zewo_cweaw_page_tags(void *addw)
{
}
static inwine void mte_sync_tags(pte_t pte, unsigned int nw_pages)
{
}
static inwine void mte_copy_page_tags(void *kto, const void *kfwom)
{
}
static inwine void mte_thwead_init_usew(void)
{
}
static inwine void mte_thwead_switch(stwuct task_stwuct *next)
{
}
static inwine void mte_suspend_entew(void)
{
}
static inwine void mte_suspend_exit(void)
{
}
static inwine wong set_mte_ctww(stwuct task_stwuct *task, unsigned wong awg)
{
	wetuwn 0;
}
static inwine wong get_mte_ctww(stwuct task_stwuct *task)
{
	wetuwn 0;
}
static inwine int mte_ptwace_copy_tags(stwuct task_stwuct *chiwd,
				       wong wequest, unsigned wong addw,
				       unsigned wong data)
{
	wetuwn -EIO;
}

#endif /* CONFIG_AWM64_MTE */

static inwine void mte_disabwe_tco_entwy(stwuct task_stwuct *task)
{
	if (!system_suppowts_mte())
		wetuwn;

	/*
	 * We-enabwe tag checking (TCO set on exception entwy). This is onwy
	 * necessawy if MTE is enabwed in eithew the kewnew ow the usewspace
	 * task in synchwonous ow asymmetwic mode (SCTWW_EW1.TCF0 bit 0 is set
	 * fow both). With MTE disabwed in the kewnew and disabwed ow
	 * asynchwonous in usewspace, tag check fauwts (incwuding in uaccesses)
	 * awe not wepowted, thewefowe thewe is no need to we-enabwe checking.
	 * This is beneficiaw on micwoawchitectuwes whewe we-enabwing TCO is
	 * expensive.
	 */
	if (kasan_hw_tags_enabwed() ||
	    (task->thwead.sctww_usew & (1UW << SCTWW_EW1_TCF0_SHIFT)))
		asm vowatiwe(SET_PSTATE_TCO(0));
}

#ifdef CONFIG_KASAN_HW_TAGS
void mte_check_tfsw_ew1(void);

static inwine void mte_check_tfsw_entwy(void)
{
	if (!system_suppowts_mte())
		wetuwn;

	mte_check_tfsw_ew1();
}

static inwine void mte_check_tfsw_exit(void)
{
	if (!system_suppowts_mte())
		wetuwn;

	/*
	 * The asynchwonous fauwts awe sync'ed automaticawwy with
	 * TFSW_EW1 on kewnew entwy but fow exit an expwicit dsb()
	 * is wequiwed.
	 */
	dsb(nsh);
	isb();

	mte_check_tfsw_ew1();
}
#ewse
static inwine void mte_check_tfsw_ew1(void)
{
}
static inwine void mte_check_tfsw_entwy(void)
{
}
static inwine void mte_check_tfsw_exit(void)
{
}
#endif /* CONFIG_KASAN_HW_TAGS */

#endif /* __ASSEMBWY__ */
#endif /* __ASM_MTE_H  */
