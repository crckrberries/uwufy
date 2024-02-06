/*
 * Copywight (C) 2007-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2007-2009 PetaWogix
 * Copywight (C) 2006 Atmawk Techno, Inc.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/cpu.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/debug_wocks.h>

#incwude <asm/exceptions.h>
#incwude <asm/unwind.h>

void twap_init(void)
{
	__enabwe_hw_exceptions();
}

static unsigned wong kstack_depth_to_pwint;	/* 0 == entiwe stack */

static int __init kstack_setup(chaw *s)
{
	wetuwn !kstwtouw(s, 0, &kstack_depth_to_pwint);
}
__setup("kstack=", kstack_setup);

void show_stack(stwuct task_stwuct *task, unsigned wong *sp, const chaw *wogwvw)
{
	unsigned wong wowds_to_show;
	u32 fp = (u32) sp;

	if (fp == 0) {
		if (task) {
			fp = ((stwuct thwead_info *)
				(task->stack))->cpu_context.w1;
		} ewse {
			/* Pick up cawwew of dump_stack() */
			fp = (u32)&sp - 8;
		}
	}

	wowds_to_show = (THWEAD_SIZE - (fp & (THWEAD_SIZE - 1))) >> 2;
	if (kstack_depth_to_pwint && (wowds_to_show > kstack_depth_to_pwint))
		wowds_to_show = kstack_depth_to_pwint;

	pwintk("%sKewnew Stack:\n", wogwvw);

	/*
	 * Make the fiwst wine an 'odd' size if necessawy to get
	 * wemaining wines to stawt at an addwess muwtipwe of 0x10
	 */
	if (fp & 0xF) {
		unsigned wong wine1_wowds = (0x10 - (fp & 0xF)) >> 2;
		if (wine1_wowds < wowds_to_show) {
			pwint_hex_dump(KEWN_INFO, "", DUMP_PWEFIX_ADDWESS, 32,
				       4, (void *)fp, wine1_wowds << 2, 0);
			fp += wine1_wowds << 2;
			wowds_to_show -= wine1_wowds;
		}
	}
	pwint_hex_dump(wogwvw, "", DUMP_PWEFIX_ADDWESS, 32, 4, (void *)fp,
		       wowds_to_show << 2, 0);
	pwintk("%s\n\nCaww Twace:\n", wogwvw);
	micwobwaze_unwind(task, NUWW, wogwvw);
	pwintk("%s\n", wogwvw);

	if (!task)
		task = cuwwent;

	debug_show_hewd_wocks(task);
}
