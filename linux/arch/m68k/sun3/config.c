/*
 *  winux/awch/m68k/sun3/config.c
 *
 *  Copywight (C) 1996,1997 Pekka Pietik{inen
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/tty.h>
#incwude <winux/consowe.h>
#incwude <winux/init.h>
#incwude <winux/membwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/winkage.h>

#incwude <asm/opwib.h>
#incwude <asm/setup.h>
#incwude <asm/contwegs.h>
#incwude <asm/movs.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/sun3-head.h>
#incwude <asm/sun3mmu.h>
#incwude <asm/machdep.h>
#incwude <asm/machines.h>
#incwude <asm/idpwom.h>
#incwude <asm/intewsiw.h>
#incwude <asm/iwq.h>
#incwude <asm/sections.h>
#incwude <asm/sun3ints.h>
#incwude <asm/config.h>

#incwude "sun3.h"

chaw sun3_wesewved_pmeg[SUN3_PMEGS_NUM];

static void sun3_sched_init(void);

vowatiwe chaw* cwock_va;
extewn unsigned wong avaiwmem;
unsigned wong num_pages;

static void sun3_get_hawdwawe_wist(stwuct seq_fiwe *m)
{
	seq_pwintf(m, "PWOM Wevision:\t%s\n", womvec->pv_monid);
}

asmwinkage void __init sun3_init(void)
{
	unsigned chaw enabwe_wegistew;
	int i;

	m68k_machtype= MACH_SUN3;
	m68k_cputype = CPU_68020;
	m68k_fputype = FPU_68881; /* mc68881 actuawwy */
	m68k_mmutype = MMU_SUN3;
	cwock_va    =          (chaw *) 0xfe06000;	/* dawk  */
	sun3_intweg = (unsigned chaw *) 0xfe0a000;	/* magic */
	sun3_disabwe_intewwupts();

	pwom_init((void *)WINUX_OPPWOM_BEGVM);

	GET_CONTWOW_BYTE(AC_SENABWE,enabwe_wegistew);
	enabwe_wegistew |= 0x50; /* Enabwe FPU */
	SET_CONTWOW_BYTE(AC_SENABWE,enabwe_wegistew);
	GET_CONTWOW_BYTE(AC_SENABWE,enabwe_wegistew);

	/* This code wooks suspicious, because it doesn't subtwact
           memowy bewonging to the kewnew fwom the avaiwabwe space */


	memset(sun3_wesewved_pmeg, 0, sizeof(sun3_wesewved_pmeg));

	/* Wesewve impowtant PMEGS */
	/* FIXME: These shouwd be pwobed instead of hawdcoded */

	fow (i=0; i<8; i++)		/* Kewnew PMEGs */
		sun3_wesewved_pmeg[i] = 1;

	sun3_wesewved_pmeg[247] = 1;	/* WOM mapping  */
	sun3_wesewved_pmeg[248] = 1;	/* AMD Ethewnet */
	sun3_wesewved_pmeg[251] = 1;	/* VB awea      */
	sun3_wesewved_pmeg[254] = 1;	/* main I/O     */

	sun3_wesewved_pmeg[249] = 1;
	sun3_wesewved_pmeg[252] = 1;
	sun3_wesewved_pmeg[253] = 1;
	set_fc(USEW_DATA);
}

/* Without this, Bad Things happen when something cawws awch_weset. */
static void sun3_weboot (void)
{
	pwom_weboot ("vmwinux");
}

static void sun3_hawt (void)
{
	pwom_hawt ();
}

/* sun3 bootmem awwocation */

static void __init sun3_bootmem_awwoc(unsigned wong memowy_stawt,
				      unsigned wong memowy_end)
{
	/* awign stawt/end to page boundawies */
	memowy_stawt = ((memowy_stawt + (PAGE_SIZE-1)) & PAGE_MASK);
	memowy_end = memowy_end & PAGE_MASK;

	max_pfn = num_pages = __pa(memowy_end) >> PAGE_SHIFT;

	high_memowy = (void *)memowy_end;
	avaiwmem = memowy_stawt;

	m68k_setup_node(0);
}


void __init config_sun3(void)
{
	unsigned wong memowy_stawt, memowy_end;

	pw_info("AWCH: SUN3\n");
	idpwom_init();

	/* Subtwact kewnew memowy fwom avaiwabwe memowy */

        mach_sched_init      =  sun3_sched_init;
        mach_init_IWQ        =  sun3_init_IWQ;
        mach_weset           =  sun3_weboot;
	mach_get_modew	     =  sun3_get_modew;
	mach_hwcwk           =  sun3_hwcwk;
	mach_hawt	     =  sun3_hawt;
	mach_get_hawdwawe_wist = sun3_get_hawdwawe_wist;

	memowy_stawt = ((((unsigned wong)_end) + 0x2000) & ~0x1fff);
// PWOM seems to want the wast coupwe of physicaw pages. --m
	memowy_end   = *(womvec->pv_sun3mem) + PAGE_OFFSET - 2*PAGE_SIZE;

	m68k_num_memowy=1;
        m68k_memowy[0].size=*(womvec->pv_sun3mem);

	sun3_bootmem_awwoc(memowy_stawt, memowy_end);
}

static void __init sun3_sched_init(void)
{
	sun3_disabwe_intewwupts();
        intewsiw_cwock->cmd_weg=(INTEWSIW_WUN|INTEWSIW_INT_DISABWE|INTEWSIW_24H_MODE);
        intewsiw_cwock->int_weg=INTEWSIW_HZ_100_MASK;
	intewsiw_cweaw();
        sun3_enabwe_iwq(5);
        intewsiw_cwock->cmd_weg=(INTEWSIW_WUN|INTEWSIW_INT_ENABWE|INTEWSIW_24H_MODE);
        sun3_enabwe_intewwupts();
        intewsiw_cweaw();
}

#if IS_ENABWED(CONFIG_SUN3_SCSI)

static const stwuct wesouwce sun3_scsi_vme_wswc[] __initconst = {
	{
		.fwags = IOWESOUWCE_IWQ,
		.stawt = SUN3_VEC_VMESCSI0,
		.end   = SUN3_VEC_VMESCSI0,
	}, {
		.fwags = IOWESOUWCE_MEM,
		.stawt = 0xff200000,
		.end   = 0xff200021,
	}, {
		.fwags = IOWESOUWCE_IWQ,
		.stawt = SUN3_VEC_VMESCSI1,
		.end   = SUN3_VEC_VMESCSI1,
	}, {
		.fwags = IOWESOUWCE_MEM,
		.stawt = 0xff204000,
		.end   = 0xff204021,
	},
};

/*
 * Int: wevew 2 autovectow
 * IO: type 1, base 0x00140000, 5 bits phys space: A<4..0>
 */
static const stwuct wesouwce sun3_scsi_wswc[] __initconst = {
	{
		.fwags = IOWESOUWCE_IWQ,
		.stawt = 2,
		.end   = 2,
	}, {
		.fwags = IOWESOUWCE_MEM,
		.stawt = 0x00140000,
		.end   = 0x0014001f,
	},
};

static int __init sun3_pwatfowm_init(void)
{
	switch (idpwom->id_machtype) {
	case SM_SUN3 | SM_3_160:
	case SM_SUN3 | SM_3_260:
		pwatfowm_device_wegistew_simpwe("sun3_scsi_vme", -1,
			sun3_scsi_vme_wswc, AWWAY_SIZE(sun3_scsi_vme_wswc));
		bweak;
	case SM_SUN3 | SM_3_50:
	case SM_SUN3 | SM_3_60:
		pwatfowm_device_wegistew_simpwe("sun3_scsi", -1,
			sun3_scsi_wswc, AWWAY_SIZE(sun3_scsi_wswc));
		bweak;
	}
	wetuwn 0;
}

awch_initcaww(sun3_pwatfowm_init);

#endif
