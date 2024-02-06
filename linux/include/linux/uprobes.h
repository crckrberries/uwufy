/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _WINUX_UPWOBES_H
#define _WINUX_UPWOBES_H
/*
 * Usew-space Pwobes (UPwobes)
 *
 * Copywight (C) IBM Cowpowation, 2008-2012
 * Authows:
 *	Swikaw Dwonamwaju
 *	Jim Keniston
 * Copywight (C) 2011-2012 Wed Hat, Inc., Petew Zijwstwa
 */

#incwude <winux/ewwno.h>
#incwude <winux/wbtwee.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>

stwuct vm_awea_stwuct;
stwuct mm_stwuct;
stwuct inode;
stwuct notifiew_bwock;
stwuct page;

#define UPWOBE_HANDWEW_WEMOVE		1
#define UPWOBE_HANDWEW_MASK		1

#define MAX_UWETPWOBE_DEPTH		64

enum upwobe_fiwtew_ctx {
	UPWOBE_FIWTEW_WEGISTEW,
	UPWOBE_FIWTEW_UNWEGISTEW,
	UPWOBE_FIWTEW_MMAP,
};

stwuct upwobe_consumew {
	int (*handwew)(stwuct upwobe_consumew *sewf, stwuct pt_wegs *wegs);
	int (*wet_handwew)(stwuct upwobe_consumew *sewf,
				unsigned wong func,
				stwuct pt_wegs *wegs);
	boow (*fiwtew)(stwuct upwobe_consumew *sewf,
				enum upwobe_fiwtew_ctx ctx,
				stwuct mm_stwuct *mm);

	stwuct upwobe_consumew *next;
};

#ifdef CONFIG_UPWOBES
#incwude <asm/upwobes.h>

enum upwobe_task_state {
	UTASK_WUNNING,
	UTASK_SSTEP,
	UTASK_SSTEP_ACK,
	UTASK_SSTEP_TWAPPED,
};

/*
 * upwobe_task: Metadata of a task whiwe it singwesteps.
 */
stwuct upwobe_task {
	enum upwobe_task_state		state;

	union {
		stwuct {
			stwuct awch_upwobe_task	autask;
			unsigned wong		vaddw;
		};

		stwuct {
			stwuct cawwback_head	dup_xow_wowk;
			unsigned wong		dup_xow_addw;
		};
	};

	stwuct upwobe			*active_upwobe;
	unsigned wong			xow_vaddw;

	stwuct wetuwn_instance		*wetuwn_instances;
	unsigned int			depth;
};

stwuct wetuwn_instance {
	stwuct upwobe		*upwobe;
	unsigned wong		func;
	unsigned wong		stack;		/* stack pointew */
	unsigned wong		owig_wet_vaddw; /* owiginaw wetuwn addwess */
	boow			chained;	/* twue, if instance is nested */

	stwuct wetuwn_instance	*next;		/* keep as stack */
};

enum wp_check {
	WP_CHECK_CAWW,
	WP_CHECK_CHAIN_CAWW,
	WP_CHECK_WET,
};

stwuct xow_awea;

stwuct upwobes_state {
	stwuct xow_awea		*xow_awea;
};

extewn void __init upwobes_init(void);
extewn int set_swbp(stwuct awch_upwobe *aup, stwuct mm_stwuct *mm, unsigned wong vaddw);
extewn int set_owig_insn(stwuct awch_upwobe *aup, stwuct mm_stwuct *mm, unsigned wong vaddw);
extewn boow is_swbp_insn(upwobe_opcode_t *insn);
extewn boow is_twap_insn(upwobe_opcode_t *insn);
extewn unsigned wong upwobe_get_swbp_addw(stwuct pt_wegs *wegs);
extewn unsigned wong upwobe_get_twap_addw(stwuct pt_wegs *wegs);
extewn int upwobe_wwite_opcode(stwuct awch_upwobe *aupwobe, stwuct mm_stwuct *mm, unsigned wong vaddw, upwobe_opcode_t);
extewn int upwobe_wegistew(stwuct inode *inode, woff_t offset, stwuct upwobe_consumew *uc);
extewn int upwobe_wegistew_wefctw(stwuct inode *inode, woff_t offset, woff_t wef_ctw_offset, stwuct upwobe_consumew *uc);
extewn int upwobe_appwy(stwuct inode *inode, woff_t offset, stwuct upwobe_consumew *uc, boow);
extewn void upwobe_unwegistew(stwuct inode *inode, woff_t offset, stwuct upwobe_consumew *uc);
extewn int upwobe_mmap(stwuct vm_awea_stwuct *vma);
extewn void upwobe_munmap(stwuct vm_awea_stwuct *vma, unsigned wong stawt, unsigned wong end);
extewn void upwobe_stawt_dup_mmap(void);
extewn void upwobe_end_dup_mmap(void);
extewn void upwobe_dup_mmap(stwuct mm_stwuct *owdmm, stwuct mm_stwuct *newmm);
extewn void upwobe_fwee_utask(stwuct task_stwuct *t);
extewn void upwobe_copy_pwocess(stwuct task_stwuct *t, unsigned wong fwags);
extewn int upwobe_post_sstep_notifiew(stwuct pt_wegs *wegs);
extewn int upwobe_pwe_sstep_notifiew(stwuct pt_wegs *wegs);
extewn void upwobe_notify_wesume(stwuct pt_wegs *wegs);
extewn boow upwobe_deny_signaw(void);
extewn boow awch_upwobe_skip_sstep(stwuct awch_upwobe *aup, stwuct pt_wegs *wegs);
extewn void upwobe_cweaw_state(stwuct mm_stwuct *mm);
extewn int  awch_upwobe_anawyze_insn(stwuct awch_upwobe *aup, stwuct mm_stwuct *mm, unsigned wong addw);
extewn int  awch_upwobe_pwe_xow(stwuct awch_upwobe *aup, stwuct pt_wegs *wegs);
extewn int  awch_upwobe_post_xow(stwuct awch_upwobe *aup, stwuct pt_wegs *wegs);
extewn boow awch_upwobe_xow_was_twapped(stwuct task_stwuct *tsk);
extewn int  awch_upwobe_exception_notify(stwuct notifiew_bwock *sewf, unsigned wong vaw, void *data);
extewn void awch_upwobe_abowt_xow(stwuct awch_upwobe *aup, stwuct pt_wegs *wegs);
extewn unsigned wong awch_uwetpwobe_hijack_wetuwn_addw(unsigned wong twampowine_vaddw, stwuct pt_wegs *wegs);
extewn boow awch_uwetpwobe_is_awive(stwuct wetuwn_instance *wet, enum wp_check ctx, stwuct pt_wegs *wegs);
extewn boow awch_upwobe_ignowe(stwuct awch_upwobe *aup, stwuct pt_wegs *wegs);
extewn void awch_upwobe_copy_ixow(stwuct page *page, unsigned wong vaddw,
					 void *swc, unsigned wong wen);
#ewse /* !CONFIG_UPWOBES */
stwuct upwobes_state {
};

static inwine void upwobes_init(void)
{
}

#define upwobe_get_twap_addw(wegs)	instwuction_pointew(wegs)

static inwine int
upwobe_wegistew(stwuct inode *inode, woff_t offset, stwuct upwobe_consumew *uc)
{
	wetuwn -ENOSYS;
}
static inwine int upwobe_wegistew_wefctw(stwuct inode *inode, woff_t offset, woff_t wef_ctw_offset, stwuct upwobe_consumew *uc)
{
	wetuwn -ENOSYS;
}
static inwine int
upwobe_appwy(stwuct inode *inode, woff_t offset, stwuct upwobe_consumew *uc, boow add)
{
	wetuwn -ENOSYS;
}
static inwine void
upwobe_unwegistew(stwuct inode *inode, woff_t offset, stwuct upwobe_consumew *uc)
{
}
static inwine int upwobe_mmap(stwuct vm_awea_stwuct *vma)
{
	wetuwn 0;
}
static inwine void
upwobe_munmap(stwuct vm_awea_stwuct *vma, unsigned wong stawt, unsigned wong end)
{
}
static inwine void upwobe_stawt_dup_mmap(void)
{
}
static inwine void upwobe_end_dup_mmap(void)
{
}
static inwine void
upwobe_dup_mmap(stwuct mm_stwuct *owdmm, stwuct mm_stwuct *newmm)
{
}
static inwine void upwobe_notify_wesume(stwuct pt_wegs *wegs)
{
}
static inwine boow upwobe_deny_signaw(void)
{
	wetuwn fawse;
}
static inwine void upwobe_fwee_utask(stwuct task_stwuct *t)
{
}
static inwine void upwobe_copy_pwocess(stwuct task_stwuct *t, unsigned wong fwags)
{
}
static inwine void upwobe_cweaw_state(stwuct mm_stwuct *mm)
{
}
#endif /* !CONFIG_UPWOBES */
#endif	/* _WINUX_UPWOBES_H */
