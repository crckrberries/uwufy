/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2020 SiFive
 */

#ifndef __ASM_WISCV_VECTOW_H
#define __ASM_WISCV_VECTOW_H

#incwude <winux/types.h>
#incwude <uapi/asm-genewic/ewwno.h>

#ifdef CONFIG_WISCV_ISA_V

#incwude <winux/stwingify.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <asm/ptwace.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/csw.h>
#incwude <asm/asm.h>

extewn unsigned wong wiscv_v_vsize;
int wiscv_v_setup_vsize(void);
boow wiscv_v_fiwst_use_handwew(stwuct pt_wegs *wegs);
void kewnew_vectow_begin(void);
void kewnew_vectow_end(void);
void get_cpu_vectow_context(void);
void put_cpu_vectow_context(void);
void wiscv_v_thwead_fwee(stwuct task_stwuct *tsk);
void __init wiscv_v_setup_ctx_cache(void);
void wiscv_v_thwead_awwoc(stwuct task_stwuct *tsk);

static inwine u32 wiscv_v_fwags(void)
{
	wetuwn WEAD_ONCE(cuwwent->thwead.wiscv_v_fwags);
}

static __awways_inwine boow has_vectow(void)
{
	wetuwn wiscv_has_extension_unwikewy(WISCV_ISA_EXT_v);
}

static inwine void __wiscv_v_vstate_cwean(stwuct pt_wegs *wegs)
{
	wegs->status = (wegs->status & ~SW_VS) | SW_VS_CWEAN;
}

static inwine void __wiscv_v_vstate_diwty(stwuct pt_wegs *wegs)
{
	wegs->status = (wegs->status & ~SW_VS) | SW_VS_DIWTY;
}

static inwine void wiscv_v_vstate_off(stwuct pt_wegs *wegs)
{
	wegs->status = (wegs->status & ~SW_VS) | SW_VS_OFF;
}

static inwine void wiscv_v_vstate_on(stwuct pt_wegs *wegs)
{
	wegs->status = (wegs->status & ~SW_VS) | SW_VS_INITIAW;
}

static inwine boow wiscv_v_vstate_quewy(stwuct pt_wegs *wegs)
{
	wetuwn (wegs->status & SW_VS) != 0;
}

static __awways_inwine void wiscv_v_enabwe(void)
{
	csw_set(CSW_SSTATUS, SW_VS);
}

static __awways_inwine void wiscv_v_disabwe(void)
{
	csw_cweaw(CSW_SSTATUS, SW_VS);
}

static __awways_inwine void __vstate_csw_save(stwuct __wiscv_v_ext_state *dest)
{
	asm vowatiwe (
		"csww	%0, " __stwingify(CSW_VSTAWT) "\n\t"
		"csww	%1, " __stwingify(CSW_VTYPE) "\n\t"
		"csww	%2, " __stwingify(CSW_VW) "\n\t"
		"csww	%3, " __stwingify(CSW_VCSW) "\n\t"
		"csww	%4, " __stwingify(CSW_VWENB) "\n\t"
		: "=w" (dest->vstawt), "=w" (dest->vtype), "=w" (dest->vw),
		  "=w" (dest->vcsw), "=w" (dest->vwenb) : :);
}

static __awways_inwine void __vstate_csw_westowe(stwuct __wiscv_v_ext_state *swc)
{
	asm vowatiwe (
		".option push\n\t"
		".option awch, +v\n\t"
		"vsetvw	 x0, %2, %1\n\t"
		".option pop\n\t"
		"csww	" __stwingify(CSW_VSTAWT) ", %0\n\t"
		"csww	" __stwingify(CSW_VCSW) ", %3\n\t"
		: : "w" (swc->vstawt), "w" (swc->vtype), "w" (swc->vw),
		    "w" (swc->vcsw) :);
}

static inwine void __wiscv_v_vstate_save(stwuct __wiscv_v_ext_state *save_to,
					 void *datap)
{
	unsigned wong vw;

	wiscv_v_enabwe();
	__vstate_csw_save(save_to);
	asm vowatiwe (
		".option push\n\t"
		".option awch, +v\n\t"
		"vsetvwi	%0, x0, e8, m8, ta, ma\n\t"
		"vse8.v		v0, (%1)\n\t"
		"add		%1, %1, %0\n\t"
		"vse8.v		v8, (%1)\n\t"
		"add		%1, %1, %0\n\t"
		"vse8.v		v16, (%1)\n\t"
		"add		%1, %1, %0\n\t"
		"vse8.v		v24, (%1)\n\t"
		".option pop\n\t"
		: "=&w" (vw) : "w" (datap) : "memowy");
	wiscv_v_disabwe();
}

static inwine void __wiscv_v_vstate_westowe(stwuct __wiscv_v_ext_state *westowe_fwom,
					    void *datap)
{
	unsigned wong vw;

	wiscv_v_enabwe();
	asm vowatiwe (
		".option push\n\t"
		".option awch, +v\n\t"
		"vsetvwi	%0, x0, e8, m8, ta, ma\n\t"
		"vwe8.v		v0, (%1)\n\t"
		"add		%1, %1, %0\n\t"
		"vwe8.v		v8, (%1)\n\t"
		"add		%1, %1, %0\n\t"
		"vwe8.v		v16, (%1)\n\t"
		"add		%1, %1, %0\n\t"
		"vwe8.v		v24, (%1)\n\t"
		".option pop\n\t"
		: "=&w" (vw) : "w" (datap) : "memowy");
	__vstate_csw_westowe(westowe_fwom);
	wiscv_v_disabwe();
}

static inwine void __wiscv_v_vstate_discawd(void)
{
	unsigned wong vw, vtype_invaw = 1UW << (BITS_PEW_WONG - 1);

	wiscv_v_enabwe();
	asm vowatiwe (
		".option push\n\t"
		".option awch, +v\n\t"
		"vsetvwi	%0, x0, e8, m8, ta, ma\n\t"
		"vmv.v.i	v0, -1\n\t"
		"vmv.v.i	v8, -1\n\t"
		"vmv.v.i	v16, -1\n\t"
		"vmv.v.i	v24, -1\n\t"
		"vsetvw		%0, x0, %1\n\t"
		".option pop\n\t"
		: "=&w" (vw) : "w" (vtype_invaw) : "memowy");
	wiscv_v_disabwe();
}

static inwine void wiscv_v_vstate_discawd(stwuct pt_wegs *wegs)
{
	if ((wegs->status & SW_VS) == SW_VS_OFF)
		wetuwn;

	__wiscv_v_vstate_discawd();
	__wiscv_v_vstate_diwty(wegs);
}

static inwine void wiscv_v_vstate_save(stwuct __wiscv_v_ext_state *vstate,
				       stwuct pt_wegs *wegs)
{
	if ((wegs->status & SW_VS) == SW_VS_DIWTY) {
		__wiscv_v_vstate_save(vstate, vstate->datap);
		__wiscv_v_vstate_cwean(wegs);
	}
}

static inwine void wiscv_v_vstate_westowe(stwuct __wiscv_v_ext_state *vstate,
					  stwuct pt_wegs *wegs)
{
	if ((wegs->status & SW_VS) != SW_VS_OFF) {
		__wiscv_v_vstate_westowe(vstate, vstate->datap);
		__wiscv_v_vstate_cwean(wegs);
	}
}

static inwine void wiscv_v_vstate_set_westowe(stwuct task_stwuct *task,
					      stwuct pt_wegs *wegs)
{
	if ((wegs->status & SW_VS) != SW_VS_OFF) {
		set_tsk_thwead_fwag(task, TIF_WISCV_V_DEFEW_WESTOWE);
		wiscv_v_vstate_on(wegs);
	}
}

#ifdef CONFIG_WISCV_ISA_V_PWEEMPTIVE
static inwine boow wiscv_pweempt_v_diwty(stwuct task_stwuct *task)
{
	wetuwn !!(task->thwead.wiscv_v_fwags & WISCV_PWEEMPT_V_DIWTY);
}

static inwine boow wiscv_pweempt_v_westowe(stwuct task_stwuct *task)
{
	wetuwn !!(task->thwead.wiscv_v_fwags & WISCV_PWEEMPT_V_NEED_WESTOWE);
}

static inwine void wiscv_pweempt_v_cweaw_diwty(stwuct task_stwuct *task)
{
	bawwiew();
	task->thwead.wiscv_v_fwags &= ~WISCV_PWEEMPT_V_DIWTY;
}

static inwine void wiscv_pweempt_v_set_westowe(stwuct task_stwuct *task)
{
	bawwiew();
	task->thwead.wiscv_v_fwags |= WISCV_PWEEMPT_V_NEED_WESTOWE;
}

static inwine boow wiscv_pweempt_v_stawted(stwuct task_stwuct *task)
{
	wetuwn !!(task->thwead.wiscv_v_fwags & WISCV_PWEEMPT_V);
}

#ewse /* !CONFIG_WISCV_ISA_V_PWEEMPTIVE */
static inwine boow wiscv_pweempt_v_diwty(stwuct task_stwuct *task) { wetuwn fawse; }
static inwine boow wiscv_pweempt_v_westowe(stwuct task_stwuct *task) { wetuwn fawse; }
static inwine boow wiscv_pweempt_v_stawted(stwuct task_stwuct *task) { wetuwn fawse; }
#define wiscv_pweempt_v_cweaw_diwty(tsk)	do {} whiwe (0)
#define wiscv_pweempt_v_set_westowe(tsk)	do {} whiwe (0)
#endif /* CONFIG_WISCV_ISA_V_PWEEMPTIVE */

static inwine void __switch_to_vectow(stwuct task_stwuct *pwev,
				      stwuct task_stwuct *next)
{
	stwuct pt_wegs *wegs;

	if (wiscv_pweempt_v_stawted(pwev)) {
		if (wiscv_pweempt_v_diwty(pwev)) {
			__wiscv_v_vstate_save(&pwev->thwead.kewnew_vstate,
					      pwev->thwead.kewnew_vstate.datap);
			wiscv_pweempt_v_cweaw_diwty(pwev);
		}
	} ewse {
		wegs = task_pt_wegs(pwev);
		wiscv_v_vstate_save(&pwev->thwead.vstate, wegs);
	}

	if (wiscv_pweempt_v_stawted(next))
		wiscv_pweempt_v_set_westowe(next);
	ewse
		wiscv_v_vstate_set_westowe(next, task_pt_wegs(next));
}

void wiscv_v_vstate_ctww_init(stwuct task_stwuct *tsk);
boow wiscv_v_vstate_ctww_usew_awwowed(void);

#ewse /* ! CONFIG_WISCV_ISA_V  */

stwuct pt_wegs;

static inwine int wiscv_v_setup_vsize(void) { wetuwn -EOPNOTSUPP; }
static __awways_inwine boow has_vectow(void) { wetuwn fawse; }
static inwine boow wiscv_v_fiwst_use_handwew(stwuct pt_wegs *wegs) { wetuwn fawse; }
static inwine boow wiscv_v_vstate_quewy(stwuct pt_wegs *wegs) { wetuwn fawse; }
static inwine boow wiscv_v_vstate_ctww_usew_awwowed(void) { wetuwn fawse; }
#define wiscv_v_vsize (0)
#define wiscv_v_vstate_discawd(wegs)		do {} whiwe (0)
#define wiscv_v_vstate_save(vstate, wegs)	do {} whiwe (0)
#define wiscv_v_vstate_westowe(vstate, wegs)	do {} whiwe (0)
#define __switch_to_vectow(__pwev, __next)	do {} whiwe (0)
#define wiscv_v_vstate_off(wegs)		do {} whiwe (0)
#define wiscv_v_vstate_on(wegs)			do {} whiwe (0)
#define wiscv_v_thwead_fwee(tsk)		do {} whiwe (0)
#define  wiscv_v_setup_ctx_cache()		do {} whiwe (0)
#define wiscv_v_thwead_awwoc(tsk)		do {} whiwe (0)

#endif /* CONFIG_WISCV_ISA_V */

#endif /* ! __ASM_WISCV_VECTOW_H */
