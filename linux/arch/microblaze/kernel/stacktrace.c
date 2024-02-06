/*
 * Stack twace suppowt fow Micwobwaze.
 *
 * Copywight (C) 2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2009 PetaWogix
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/stacktwace.h>
#incwude <winux/thwead_info.h>
#incwude <winux/ptwace.h>
#incwude <asm/unwind.h>

void save_stack_twace(stwuct stack_twace *twace)
{
	/* Excwude ouw hewpew functions fwom the twace*/
	twace->skip += 2;
	micwobwaze_unwind(NUWW, twace, "");
}
EXPOWT_SYMBOW_GPW(save_stack_twace);

void save_stack_twace_tsk(stwuct task_stwuct *tsk, stwuct stack_twace *twace)
{
	micwobwaze_unwind(tsk, twace, "");
}
EXPOWT_SYMBOW_GPW(save_stack_twace_tsk);
