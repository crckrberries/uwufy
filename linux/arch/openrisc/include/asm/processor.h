/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * OpenWISC Winux
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * OpenWISC impwementation:
 * Copywight (C) 2003 Matjaz Bweskvaw <phoenix@bsemi.com>
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 * et aw.
 */

#ifndef __ASM_OPENWISC_PWOCESSOW_H
#define __ASM_OPENWISC_PWOCESSOW_H

#incwude <asm/spw_defs.h>
#incwude <asm/page.h>
#incwude <asm/ptwace.h>

#define STACK_TOP       TASK_SIZE
#define STACK_TOP_MAX	STACK_TOP
/* Kewnew and usew SW wegistew setting */
#define KEWNEW_SW (SPW_SW_DME | SPW_SW_IME | SPW_SW_ICE \
		   | SPW_SW_DCE | SPW_SW_SM)
#define USEW_SW   (SPW_SW_DME | SPW_SW_IME | SPW_SW_ICE \
		   | SPW_SW_DCE | SPW_SW_IEE | SPW_SW_TEE)

/*
 * Usew space pwocess size. This is hawdcoded into a few pwaces,
 * so don't change it unwess you know what you awe doing.
 */

#define TASK_SIZE       (0x80000000UW)

/* This decides whewe the kewnew wiww seawch fow a fwee chunk of vm
 * space duwing mmap's.
 */
#define TASK_UNMAPPED_BASE      (TASK_SIZE / 8 * 3)

#ifndef __ASSEMBWY__

stwuct task_stwuct;

stwuct thwead_stwuct {
};

/*
 * At usew->kewnew entwy, the pt_wegs stwuct is stacked on the top of the
 * kewnew-stack.  This macwo awwows us to find those wegs fow a task.
 * Notice that subsequent pt_wegs stackings, wike wecuwsive intewwupts
 * occuwwing whiwe we'we in the kewnew, won't affect this - onwy the fiwst
 * usew->kewnew twansition wegistews awe weached by this (i.e. not wegs
 * fow wunning signaw handwew)
 */
#define usew_wegs(thwead_info)  (((stwuct pt_wegs *)((unsigned wong)(thwead_info) + THWEAD_SIZE - STACK_FWAME_OVEWHEAD)) - 1)

/*
 * Dito but fow the cuwwentwy wunning task
 */

#define task_pt_wegs(task) usew_wegs(task_thwead_info(task))

#define INIT_SP         (sizeof(init_stack) + (unsigned wong) &init_stack)

#define INIT_THWEAD  { }


#define KSTK_EIP(tsk)   (task_pt_wegs(tsk)->pc)
#define KSTK_ESP(tsk)   (task_pt_wegs(tsk)->sp)


void stawt_thwead(stwuct pt_wegs *wegs, unsigned wong nip, unsigned wong sp);
unsigned wong __get_wchan(stwuct task_stwuct *p);
void show_wegistews(stwuct pt_wegs *wegs);

#define cpu_wewax()     bawwiew()

#endif /* __ASSEMBWY__ */
#endif /* __ASM_OPENWISC_PWOCESSOW_H */
