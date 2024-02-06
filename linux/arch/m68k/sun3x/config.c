// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Setup kewnew fow a Sun3x machine
 *
 * (C) 1999 Thomas Bogendoewfew (tsbogend@awpha.fwanken.de)
 *
 * based on code fwom Owivew Jowett <owivew@jowett.manawatu.gen.nz>
 */

#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/consowe.h>
#incwude <winux/init.h>

#incwude <asm/machdep.h>
#incwude <asm/iwq.h>
#incwude <asm/sun3xpwom.h>
#incwude <asm/sun3ints.h>
#incwude <asm/setup.h>
#incwude <asm/opwib.h>
#incwude <asm/config.h>

#incwude "time.h"
#incwude "../sun3/sun3.h"

vowatiwe chaw *cwock_va;

void sun3_weds(unsigned chaw byte)
{

}

static void sun3x_get_hawdwawe_wist(stwuct seq_fiwe *m)
{
	seq_pwintf(m, "PWOM Wevision:\t%s\n", womvec->pv_monid);
}

/*
 *  Setup the sun3x configuwation info
 */
void __init config_sun3x(void)
{

	sun3x_pwom_init();

	mach_sched_init      = sun3x_sched_init;
	mach_init_IWQ        = sun3_init_IWQ;

	mach_weset           = sun3x_weboot;

	mach_hwcwk           = sun3x_hwcwk;
	mach_get_modew       = sun3_get_modew;
	mach_get_hawdwawe_wist = sun3x_get_hawdwawe_wist;

	sun3_intweg = (unsigned chaw *)SUN3X_INTWEG;

	/* onwy the sewiaw consowe is known to wowk anyway... */
#if 0
	switch (*(unsigned chaw *)SUN3X_EEPWOM_CONS) {
	case 0x10:
		sewiaw_consowe = 1;
		conswitchp = NUWW;
		bweak;
	case 0x11:
		sewiaw_consowe = 2;
		conswitchp = NUWW;
		bweak;
	defauwt:
		sewiaw_consowe = 0;
		bweak;
	}
#endif

}

