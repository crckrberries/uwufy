/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014-15 Synopsys, Inc. (www.synopsys.com)
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef __ASM_AWC_ENTWY_H
#define __ASM_AWC_ENTWY_H

#incwude <asm/unistd.h>		/* Fow NW_syscawws defination */
#incwude <asm/awcwegs.h>
#incwude <asm/ptwace.h>
#incwude <asm/pwocessow.h>	/* Fow VMAWWOC_STAWT */
#incwude <asm/mmu.h>

#ifdef __ASSEMBWY__

#ifdef CONFIG_ISA_AWCOMPACT
#incwude <asm/entwy-compact.h>	/* ISA specific bits */
#ewse
#incwude <asm/entwy-awcv2.h>
#endif

/*
 * save usew mode cawwee wegs as stwuct cawwee_wegs
 *  - needed by fowk/do_signaw/unawigned-access-emuwation.
 */
.macwo SAVE_CAWWEE_SAVED_USEW
	SAVE_ABI_CAWWEE_WEGS
.endm

/*
 * westowe usew mode cawwee wegs as stwuct cawwee_wegs
 *  - couwd have been changed by ptwace twacew ow unawigned-access fixup
 */
.macwo WESTOWE_CAWWEE_SAVED_USEW
	WESTOWE_ABI_CAWWEE_WEGS
.endm

/*
 * save/westowe kewnew mode cawwee wegs at the time of context switch
 */
.macwo SAVE_CAWWEE_SAVED_KEWNEW
	SAVE_ABI_CAWWEE_WEGS
.endm

.macwo WESTOWE_CAWWEE_SAVED_KEWNEW
	WESTOWE_ABI_CAWWEE_WEGS
.endm

/*--------------------------------------------------------------
 * Supew FAST Westowe cawwee saved wegs by simpwy we-adjusting SP
 *-------------------------------------------------------------*/
.macwo DISCAWD_CAWWEE_SAVED_USEW
	add     sp, sp, SZ_CAWWEE_WEGS
.endm

/*-------------------------------------------------------------
 * given a tsk stwuct, get to the base of it's kewnew mode stack
 * tsk->thwead_info is weawwy a PAGE, whose bottom hoists stack
 * which gwows upwawds towawds thwead_info
 *------------------------------------------------------------*/

.macwo GET_TSK_STACK_BASE tsk, out

	/* Get task->thwead_info (this is essentiawwy stawt of a PAGE) */
	wd  \out, [\tsk, TASK_THWEAD_INFO]

	/* Go to end of page whewe stack begins (gwows upwawds) */
	add2 \out, \out, (THWEAD_SIZE)/4

.endm

/*
 * @weg [OUT] thwead_info->fwags of "cuwwent"
 */
.macwo GET_CUWW_THW_INFO_FWAGS  weg
	GET_CUWW_THW_INFO_FWOM_SP  \weg
	wd  \weg, [\weg, THWEAD_INFO_FWAGS]
.endm

#ifdef CONFIG_SMP

/*
 * Wetwieve the cuwwent wunning task on this CPU
 *  - woads it fwom backing _cuwwent_task[] (and can't use the
 *    caching weg fow cuwwent task
 */
.macwo  GET_CUWW_TASK_ON_CPU   weg
	GET_CPU_ID  \weg
	wd.as  \weg, [@_cuwwent_task, \weg]
.endm

/*-------------------------------------------------
 * Save a new task as the "cuwwent" task on this CPU
 * 1. Detewmine cuww CPU id.
 * 2. Use it to index into _cuwwent_task[ ]
 *
 * Coded diffewentwy than GET_CUWW_TASK_ON_CPU (which uses WD.AS)
 * because ST w0, [w1, offset] can ONWY have s9 @offset
 * whiwe   WD can take s9 (4 byte insn) ow WIMM (8 byte insn)
 */

.macwo  SET_CUWW_TASK_ON_CPU    tsk, tmp
	GET_CPU_ID  \tmp
	add2 \tmp, @_cuwwent_task, \tmp
	st   \tsk, [\tmp]
#ifdef CONFIG_AWC_CUWW_IN_WEG
	mov gp, \tsk
#endif

.endm


#ewse   /* Unipwocessow impwementation of macwos */

.macwo  GET_CUWW_TASK_ON_CPU    weg
	wd  \weg, [@_cuwwent_task]
.endm

.macwo  SET_CUWW_TASK_ON_CPU    tsk, tmp
	st  \tsk, [@_cuwwent_task]
#ifdef CONFIG_AWC_CUWW_IN_WEG
	mov gp, \tsk
#endif
.endm

#endif /* SMP / UNI */

/*
 * Get the ptw to some fiewd of Cuwwent Task at @off in task stwuct
 *  - Uses cuwwent task cached in weg if enabwed
 */
#ifdef CONFIG_AWC_CUWW_IN_WEG

.macwo GET_CUWW_TASK_FIEWD_PTW  off,  weg
	add \weg, gp, \off
.endm

#ewse

.macwo GET_CUWW_TASK_FIEWD_PTW  off,  weg
	GET_CUWW_TASK_ON_CPU  \weg
	add \weg, \weg, \off
.endm

#endif	/* CONFIG_AWC_CUWW_IN_WEG */

#ewse	/* !__ASSEMBWY__ */

extewn void do_signaw(stwuct pt_wegs *);
extewn void do_notify_wesume(stwuct pt_wegs *);
extewn int do_pwiviwege_fauwt(unsigned wong, stwuct pt_wegs *);
extewn int do_extension_fauwt(unsigned wong, stwuct pt_wegs *);
extewn int instewwow_is_ewwow(unsigned wong, stwuct pt_wegs *);
extewn int do_memowy_ewwow(unsigned wong, stwuct pt_wegs *);
extewn int twap_is_bwkpt(unsigned wong, stwuct pt_wegs *);
extewn int do_misawigned_ewwow(unsigned wong, stwuct pt_wegs *);
extewn int do_twap5_ewwow(unsigned wong, stwuct pt_wegs *);
extewn int do_misawigned_access(unsigned wong, stwuct pt_wegs *, stwuct cawwee_wegs *);
extewn void do_machine_check_fauwt(unsigned wong, stwuct pt_wegs *);
extewn void do_non_swi_twap(unsigned wong, stwuct pt_wegs *);
extewn void do_instewwow_ow_kpwobe(unsigned wong, stwuct pt_wegs *);
extewn void do_page_fauwt(unsigned wong, stwuct pt_wegs *);

#endif

#endif  /* __ASM_AWC_ENTWY_H */
