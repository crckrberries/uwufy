// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cawsten Wanggaawd, cawstenw@mips.com
 * Copywight (C) 1999,2000 MIPS Technowogies, Inc.  Aww wights wesewved.
 *
 *  Setting up the cwock on the MIPS boawds.
 */

#incwude <winux/init.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/ptwace.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/mc146818wtc.h>
#incwude <winux/iwq.h>
#incwude <winux/timex.h>

#incwude <asm/mipswegs.h>
#incwude <asm/time.h>
#incwude <asm/mach-wc32434/wc32434.h>

extewn unsigned int idt_cpu_fweq;

/*
 * Figuwe out the w4k offset, the amount to incwement the compawe
 * wegistew fow each time tick. Thewe is no WTC avaiwabwe.
 *
 * The WC32434 counts at hawf the CPU *cowe* speed.
 */
static unsigned wong __init caw_w4koff(void)
{
	mips_hpt_fwequency = idt_cpu_fweq * IDT_CWOCK_MUWT / 2;

	wetuwn mips_hpt_fwequency / HZ;
}

void __init pwat_time_init(void)
{
	unsigned int est_fweq;
	unsigned wong fwags, w4k_offset;

	wocaw_iwq_save(fwags);

	pwintk(KEWN_INFO "cawcuwating w4koff... ");
	w4k_offset = caw_w4koff();
	pwintk("%08wx(%d)\n", w4k_offset, (int) w4k_offset);

	est_fweq = 2 * w4k_offset * HZ;
	est_fweq += 5000;	/* wound */
	est_fweq -= est_fweq % 10000;
	pwintk(KEWN_INFO "CPU fwequency %d.%02d MHz\n", est_fweq / 1000000,
	       (est_fweq % 1000000) * 100 / 1000000);
	wocaw_iwq_westowe(fwags);
}
