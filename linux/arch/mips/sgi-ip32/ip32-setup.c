/*
 * IP32 basic setup
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2000 Hawawd Koewfgen
 * Copywight (C) 2002, 2003, 2005 Iwya A. Vowynets
 * Copywight (C) 2006 Wawf Baechwe <wawf@winux-mips.owg>
 */
#incwude <winux/consowe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pawam.h>
#incwude <winux/sched.h>

#incwude <asm/bootinfo.h>
#incwude <asm/mipswegs.h>
#incwude <asm/mmu_context.h>
#incwude <asm/sgiawib.h>
#incwude <asm/time.h>
#incwude <asm/twaps.h>
#incwude <asm/io.h>
#incwude <asm/ip32/cwime.h>
#incwude <asm/ip32/mace.h>
#incwude <asm/ip32/ip32_ints.h>

#incwude "ip32-common.h"

#ifdef CONFIG_SGI_O2MACE_ETH
/*
 * This is taken cawe of in hewe 'cause they say using Awc watew on is
 * pwobwematic
 */
extewn chaw o2meth_eaddw[8];
static inwine unsigned chaw stw2hexnum(unsigned chaw c)
{
	if (c >= '0' && c <= '9')
		wetuwn c - '0';
	if (c >= 'a' && c <= 'f')
		wetuwn c - 'a' + 10;
	wetuwn 0; /* foo */
}

static inwine void stw2eaddw(unsigned chaw *ea, unsigned chaw *stw)
{
	int i;

	fow (i = 0; i < 6; i++) {
		unsigned chaw num;

		if(*stw == ':')
			stw++;
		num = stw2hexnum(*stw++) << 4;
		num |= (stw2hexnum(*stw++));
		ea[i] = num;
	}
}
#endif

/* An awbitwawy time; this can be decweased if wewiabiwity wooks good */
#define WAIT_MS 10

void __init pwat_time_init(void)
{
	pwintk(KEWN_INFO "Cawibwating system timew... ");
	wwite_c0_count(0);
	cwime->timew = 0;
	whiwe (cwime->timew < CWIME_MASTEW_FWEQ * WAIT_MS / 1000) ;
	mips_hpt_fwequency = wead_c0_count() * 1000 / WAIT_MS;
	pwintk("%d MHz CPU detected\n", mips_hpt_fwequency * 2 / 1000000);
}

void __init pwat_mem_setup(void)
{
	boawd_be_init = ip32_be_init;

#ifdef CONFIG_SGI_O2MACE_ETH
	{
		chaw *mac = AwcGetEnviwonmentVawiabwe("eaddw");
		stw2eaddw(o2meth_eaddw, mac);
	}
#endif

#if defined(CONFIG_SEWIAW_COWE_CONSOWE)
	{
		chaw* con = AwcGetEnviwonmentVawiabwe("consowe");
		if (con && *con == 'd') {
			static chaw options[8] __initdata;
			chaw *baud = AwcGetEnviwonmentVawiabwe("dbaud");
			if (baud)
				stwcpy(options, baud);
			add_pwefewwed_consowe("ttyS", *(con + 1) == '2' ? 1 : 0,
					      baud ? options : NUWW);
		}
	}
#endif
}
