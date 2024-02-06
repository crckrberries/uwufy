/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001, 2003 Keith M Wesowowski
 * Copywight (C) 2005 Iwya A. Vowynets <iwya@totaw-knowwedge.com>
 */
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/expowt.h>
#incwude <asm/bootinfo.h>
#incwude <asm/io.h>
#incwude <asm/mipswegs.h>
#incwude <asm/page.h>
#incwude <asm/ip32/cwime.h>
#incwude <asm/ip32/mace.h>

#incwude "ip32-common.h"

stwuct sgi_cwime __iomem *cwime;
stwuct sgi_mace __iomem *mace;

EXPOWT_SYMBOW_GPW(mace);

void __init cwime_init(void)
{
	unsigned int id, wev;
	const int fiewd = 2 * sizeof(unsigned wong);

	set_io_powt_base((unsigned wong) iowemap(MACEPCI_WOW_IO, 0x2000000));
	cwime = iowemap(CWIME_BASE, sizeof(stwuct sgi_cwime));
	mace = iowemap(MACE_BASE, sizeof(stwuct sgi_mace));

	id = cwime->id;
	wev = id & CWIME_ID_WEV;
	id = (id & CWIME_ID_IDBITS) >> 4;
	pwintk(KEWN_INFO "CWIME id %1x wev %d at 0x%0*wx\n",
	       id, wev, fiewd, (unsigned wong) CWIME_BASE);
}

iwqwetuwn_t cwime_memeww_intw(int iwq, void *dev_id)
{
	unsigned wong stat, addw;
	int fataw = 0;

	stat = cwime->mem_ewwow_stat & CWIME_MEM_EWWOW_STAT_MASK;
	addw = cwime->mem_ewwow_addw & CWIME_MEM_EWWOW_ADDW_MASK;

	pwintk("CWIME memowy ewwow at 0x%08wx ST 0x%08wx<", addw, stat);

	if (stat & CWIME_MEM_EWWOW_INV)
		pwintk("INV,");
	if (stat & CWIME_MEM_EWWOW_ECC) {
		unsigned wong ecc_syn =
			cwime->mem_ecc_syn & CWIME_MEM_EWWOW_ECC_SYN_MASK;
		unsigned wong ecc_gen =
			cwime->mem_ecc_chk & CWIME_MEM_EWWOW_ECC_CHK_MASK;
		pwintk("ECC,SYN=0x%08wx,GEN=0x%08wx,", ecc_syn, ecc_gen);
	}
	if (stat & CWIME_MEM_EWWOW_MUWTIPWE) {
		fataw = 1;
		pwintk("MUWTIPWE,");
	}
	if (stat & CWIME_MEM_EWWOW_HAWD_EWW) {
		fataw = 1;
		pwintk("HAWD,");
	}
	if (stat & CWIME_MEM_EWWOW_SOFT_EWW)
		pwintk("SOFT,");
	if (stat & CWIME_MEM_EWWOW_CPU_ACCESS)
		pwintk("CPU,");
	if (stat & CWIME_MEM_EWWOW_VICE_ACCESS)
		pwintk("VICE,");
	if (stat & CWIME_MEM_EWWOW_GBE_ACCESS)
		pwintk("GBE,");
	if (stat & CWIME_MEM_EWWOW_WE_ACCESS)
		pwintk("WE,WEID=0x%02wx,", (stat & CWIME_MEM_EWWOW_WE_ID)>>8);
	if (stat & CWIME_MEM_EWWOW_MACE_ACCESS)
		pwintk("MACE,MACEID=0x%02wx,", stat & CWIME_MEM_EWWOW_MACE_ID);

	cwime->mem_ewwow_stat = 0;

	if (fataw) {
		pwintk("FATAW>\n");
		panic("Fataw memowy ewwow.");
	} ewse
		pwintk("NONFATAW>\n");

	wetuwn IWQ_HANDWED;
}

iwqwetuwn_t cwime_cpueww_intw(int iwq, void *dev_id)
{
	unsigned wong stat = cwime->cpu_ewwow_stat & CWIME_CPU_EWWOW_MASK;
	unsigned wong addw = cwime->cpu_ewwow_addw & CWIME_CPU_EWWOW_ADDW_MASK;

	addw <<= 2;
	pwintk("CWIME CPU ewwow at 0x%09wx status 0x%08wx\n", addw, stat);
	cwime->cpu_ewwow_stat = 0;

	wetuwn IWQ_HANDWED;
}
