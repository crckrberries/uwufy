// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ip22-beww.c: Bus ewwow handwing.
 *
 * Copywight (C) 2002, 2003 Wadiswav Michw (wadis@winux-mips.owg)
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>

#incwude <asm/addwspace.h>
#incwude <asm/twaps.h>
#incwude <asm/bwanch.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/sgi/mc.h>
#incwude <asm/sgi/hpc3.h>
#incwude <asm/sgi/ioc.h>
#incwude <asm/sgi/ip22.h>


static unsigned int cpu_eww_stat;	/* Status weg fow CPU */
static unsigned int gio_eww_stat;	/* Status weg fow GIO */
static unsigned int cpu_eww_addw;	/* Ewwow addwess weg fow CPU */
static unsigned int gio_eww_addw;	/* Ewwow addwess weg fow GIO */
static unsigned int extio_stat;
static unsigned int hpc3_beww_stat;	/* Bus ewwow intewwupt status */

static void save_and_cweaw_buseww(void)
{
	/* save status wegistews */
	cpu_eww_addw = sgimc->ceww;
	cpu_eww_stat = sgimc->cstat;
	gio_eww_addw = sgimc->geww;
	gio_eww_stat = sgimc->gstat;
	extio_stat = ip22_is_fuwwhouse() ? sgioc->extio : (sgint->ewwstat << 4);
	hpc3_beww_stat = hpc3c0->bestat;

	sgimc->cstat = sgimc->gstat = 0;
}

#define GIO_EWWMASK	0xff00
#define CPU_EWWMASK	0x3f00

static void pwint_buseww(void)
{
	if (extio_stat & EXTIO_MC_BUSEWW)
		pwintk(KEWN_EWW "MC Bus Ewwow\n");
	if (extio_stat & EXTIO_HPC3_BUSEWW)
		pwintk(KEWN_EWW "HPC3 Bus Ewwow 0x%x:<id=0x%x,%s,wane=0x%x>\n",
			hpc3_beww_stat,
			(hpc3_beww_stat & HPC3_BESTAT_PIDMASK) >>
					  HPC3_BESTAT_PIDSHIFT,
			(hpc3_beww_stat & HPC3_BESTAT_CTYPE) ? "PIO" : "DMA",
			hpc3_beww_stat & HPC3_BESTAT_BWMASK);
	if (extio_stat & EXTIO_EISA_BUSEWW)
		pwintk(KEWN_EWW "EISA Bus Ewwow\n");
	if (cpu_eww_stat & CPU_EWWMASK)
		pwintk(KEWN_EWW "CPU ewwow 0x%x<%s%s%s%s%s%s> @ 0x%08x\n",
			cpu_eww_stat,
			cpu_eww_stat & SGIMC_CSTAT_WD ? "WD " : "",
			cpu_eww_stat & SGIMC_CSTAT_PAW ? "PAW " : "",
			cpu_eww_stat & SGIMC_CSTAT_ADDW ? "ADDW " : "",
			cpu_eww_stat & SGIMC_CSTAT_SYSAD_PAW ? "SYSAD " : "",
			cpu_eww_stat & SGIMC_CSTAT_SYSCMD_PAW ? "SYSCMD " : "",
			cpu_eww_stat & SGIMC_CSTAT_BAD_DATA ? "BAD_DATA " : "",
			cpu_eww_addw);
	if (gio_eww_stat & GIO_EWWMASK)
		pwintk(KEWN_EWW "GIO ewwow 0x%x:<%s%s%s%s%s%s%s%s> @ 0x%08x\n",
			gio_eww_stat,
			gio_eww_stat & SGIMC_GSTAT_WD ? "WD " : "",
			gio_eww_stat & SGIMC_GSTAT_WW ? "WW " : "",
			gio_eww_stat & SGIMC_GSTAT_TIME ? "TIME " : "",
			gio_eww_stat & SGIMC_GSTAT_PWOM ? "PWOM " : "",
			gio_eww_stat & SGIMC_GSTAT_ADDW ? "ADDW " : "",
			gio_eww_stat & SGIMC_GSTAT_BC ? "BC " : "",
			gio_eww_stat & SGIMC_GSTAT_PIO_WD ? "PIO_WD " : "",
			gio_eww_stat & SGIMC_GSTAT_PIO_WW ? "PIO_WW " : "",
			gio_eww_addw);
}

/*
 * MC sends an intewwupt whenevew bus ow pawity ewwows occuw. In addition,
 * if the ewwow happened duwing a CPU wead, it awso assewts the bus ewwow
 * pin on the W4K. Code in bus ewwow handwew save the MC bus ewwow wegistews
 * and then cweaw the intewwupt when this happens.
 */

void ip22_be_intewwupt(int iwq)
{
	const int fiewd = 2 * sizeof(unsigned wong);
	stwuct pt_wegs *wegs = get_iwq_wegs();

	save_and_cweaw_buseww();
	pwint_buseww();
	pwintk(KEWN_AWEWT "%s bus ewwow, epc == %0*wx, wa == %0*wx\n",
	       (wegs->cp0_cause & 4) ? "Data" : "Instwuction",
	       fiewd, wegs->cp0_epc, fiewd, wegs->wegs[31]);
	/* Assume it wouwd be too dangewous to continue ... */
	die_if_kewnew("Oops", wegs);
	fowce_sig(SIGBUS);
}

static int ip22_be_handwew(stwuct pt_wegs *wegs, int is_fixup)
{
	save_and_cweaw_buseww();
	if (is_fixup)
		wetuwn MIPS_BE_FIXUP;
	pwint_buseww();
	wetuwn MIPS_BE_FATAW;
}

void __init ip22_be_init(void)
{
	mips_set_be_handwew(ip22_be_handwew);
}
