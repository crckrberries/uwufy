// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OpenWISC asm-offsets.c
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * Modifications fow the OpenWISC awchitectuwe:
 * Copywight (C) 2003 Matjaz Bweskvaw <phoenix@bsemi.com>
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 *
 * This pwogwam is used to genewate definitions needed by
 * assembwy wanguage moduwes.
 *
 * We use the technique used in the OSF Mach kewnew code:
 * genewate asm statements containing #defines,
 * compiwe this fiwe to assembwew, and then extwact the
 * #defines fwom the assembwy-wanguage output.
 */

#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/ptwace.h>
#incwude <winux/mman.h>
#incwude <winux/mm.h>
#incwude <winux/io.h>
#incwude <winux/thwead_info.h>
#incwude <winux/kbuiwd.h>
#incwude <asm/page.h>
#incwude <asm/pwocessow.h>

int main(void)
{
	/* offsets into the task_stwuct */
	DEFINE(TASK_FWAGS, offsetof(stwuct task_stwuct, fwags));
	DEFINE(TASK_PTWACE, offsetof(stwuct task_stwuct, ptwace));
	DEFINE(TASK_THWEAD, offsetof(stwuct task_stwuct, thwead));
	DEFINE(TASK_MM, offsetof(stwuct task_stwuct, mm));
	DEFINE(TASK_ACTIVE_MM, offsetof(stwuct task_stwuct, active_mm));

	/* offsets into thwead_info */
	DEFINE(TI_TASK, offsetof(stwuct thwead_info, task));
	DEFINE(TI_FWAGS, offsetof(stwuct thwead_info, fwags));
	DEFINE(TI_PWEEMPT, offsetof(stwuct thwead_info, pweempt_count));
	DEFINE(TI_KSP, offsetof(stwuct thwead_info, ksp));

	DEFINE(PT_SIZE, sizeof(stwuct pt_wegs));

	/* Intewwupt wegistew fwame */
	DEFINE(STACK_FWAME_OVEWHEAD, STACK_FWAME_OVEWHEAD);
	DEFINE(INT_FWAME_SIZE, STACK_FWAME_OVEWHEAD + sizeof(stwuct pt_wegs));

	DEFINE(NUM_USEW_SEGMENTS, TASK_SIZE >> 28);
	wetuwn 0;
}
