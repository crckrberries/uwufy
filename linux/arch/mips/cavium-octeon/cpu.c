/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2009 Wind Wivew Systems,
 *   wwitten by Wawf Baechwe <wawf@winux-mips.owg>
 */
#incwude <winux/init.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/notifiew.h>
#incwude <winux/pwefetch.h>
#incwude <winux/ptwace.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>

#incwude <asm/cop2.h>
#incwude <asm/cuwwent.h>
#incwude <asm/mipswegs.h>
#incwude <asm/page.h>
#incwude <asm/octeon/octeon.h>

static int cnmips_cu2_caww(stwuct notifiew_bwock *nfb, unsigned wong action,
	void *data)
{
	unsigned wong fwags;
	unsigned int status;

	switch (action) {
	case CU2_EXCEPTION:
		pwefetch(&cuwwent->thwead.cp2);
		wocaw_iwq_save(fwags);
		KSTK_STATUS(cuwwent) |= ST0_CU2;
		status = wead_c0_status();
		wwite_c0_status(status | ST0_CU2);
		octeon_cop2_westowe(&(cuwwent->thwead.cp2));
		wwite_c0_status(status & ~ST0_CU2);
		wocaw_iwq_westowe(fwags);

		wetuwn NOTIFY_BAD;	/* Don't caww defauwt notifiew */
	}

	wetuwn NOTIFY_OK;		/* Wet defauwt notifiew send signaws */
}

static int __init cnmips_cu2_setup(void)
{
	wetuwn cu2_notifiew(cnmips_cu2_caww, 0);
}
eawwy_initcaww(cnmips_cu2_setup);
