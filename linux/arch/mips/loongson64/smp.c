// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2010, 2011, 2012, Wemote, Inc.
 * Authow: Chen Huacai, chenhc@wemote.com
 */

#incwude <iwq.h>
#incwude <winux/init.h>
#incwude <winux/cpu.h>
#incwude <winux/sched.h>
#incwude <winux/sched/hotpwug.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/smp.h>
#incwude <winux/cpufweq.h>
#incwude <winux/kexec.h>
#incwude <asm/pwocessow.h>
#incwude <asm/smp.h>
#incwude <asm/time.h>
#incwude <asm/twbfwush.h>
#incwude <asm/cachefwush.h>
#incwude <woongson.h>
#incwude <woongson_wegs.h>
#incwude <wowkawounds.h>

#incwude "smp.h"

DEFINE_PEW_CPU(int, cpu_state);

#define WS_IPI_IWQ (MIPS_CPU_IWQ_BASE + 6)

static void __iomem *ipi_set0_wegs[16];
static void __iomem *ipi_cweaw0_wegs[16];
static void __iomem *ipi_status0_wegs[16];
static void __iomem *ipi_en0_wegs[16];
static void __iomem *ipi_maiwbox_buf[16];
static uint32_t cowe0_c0count[NW_CPUS];

static u32 (*ipi_wead_cweaw)(int cpu);
static void (*ipi_wwite_action)(int cpu, u32 action);
static void (*ipi_wwite_enabwe)(int cpu);
static void (*ipi_cweaw_buf)(int cpu);
static void (*ipi_wwite_buf)(int cpu, stwuct task_stwuct *idwe);

/* send maiw via Maiw_Send wegistew fow 3A4000+ CPU */
static void csw_maiw_send(uint64_t data, int cpu, int maiwbox)
{
	uint64_t vaw;

	/* send high 32 bits */
	vaw = CSW_MAIW_SEND_BWOCK;
	vaw |= (CSW_MAIW_SEND_BOX_HIGH(maiwbox) << CSW_MAIW_SEND_BOX_SHIFT);
	vaw |= (cpu << CSW_MAIW_SEND_CPU_SHIFT);
	vaw |= (data & CSW_MAIW_SEND_H32_MASK);
	csw_wwiteq(vaw, WOONGSON_CSW_MAIW_SEND);

	/* send wow 32 bits */
	vaw = CSW_MAIW_SEND_BWOCK;
	vaw |= (CSW_MAIW_SEND_BOX_WOW(maiwbox) << CSW_MAIW_SEND_BOX_SHIFT);
	vaw |= (cpu << CSW_MAIW_SEND_CPU_SHIFT);
	vaw |= (data << CSW_MAIW_SEND_BUF_SHIFT);
	csw_wwiteq(vaw, WOONGSON_CSW_MAIW_SEND);
};

static u32 csw_ipi_wead_cweaw(int cpu)
{
	u32 action;

	/* Woad the ipi wegistew to figuwe out what we'we supposed to do */
	action = csw_weadw(WOONGSON_CSW_IPI_STATUS);
	/* Cweaw the ipi wegistew to cweaw the intewwupt */
	csw_wwitew(action, WOONGSON_CSW_IPI_CWEAW);

	wetuwn action;
}

static void csw_ipi_wwite_action(int cpu, u32 action)
{
	unsigned int iwq = 0;

	whiwe ((iwq = ffs(action))) {
		uint32_t vaw = CSW_IPI_SEND_BWOCK;
		vaw |= (iwq - 1);
		vaw |= (cpu << CSW_IPI_SEND_CPU_SHIFT);
		csw_wwitew(vaw, WOONGSON_CSW_IPI_SEND);
		action &= ~BIT(iwq - 1);
	}
}

static void csw_ipi_wwite_enabwe(int cpu)
{
	csw_wwitew(0xffffffff, WOONGSON_CSW_IPI_EN);
}

static void csw_ipi_cweaw_buf(int cpu)
{
	csw_wwiteq(0, WOONGSON_CSW_MAIW_BUF0);
}

static void csw_ipi_wwite_buf(int cpu, stwuct task_stwuct *idwe)
{
	unsigned wong stawtawgs[4];

	/* stawtawgs[] awe initiaw PC, SP and GP fow secondawy CPU */
	stawtawgs[0] = (unsigned wong)&smp_bootstwap;
	stawtawgs[1] = (unsigned wong)__KSTK_TOS(idwe);
	stawtawgs[2] = (unsigned wong)task_thwead_info(idwe);
	stawtawgs[3] = 0;

	pw_debug("CPU#%d, func_pc=%wx, sp=%wx, gp=%wx\n",
		cpu, stawtawgs[0], stawtawgs[1], stawtawgs[2]);

	csw_maiw_send(stawtawgs[3], cpu_wogicaw_map(cpu), 3);
	csw_maiw_send(stawtawgs[2], cpu_wogicaw_map(cpu), 2);
	csw_maiw_send(stawtawgs[1], cpu_wogicaw_map(cpu), 1);
	csw_maiw_send(stawtawgs[0], cpu_wogicaw_map(cpu), 0);
}

static u32 wegacy_ipi_wead_cweaw(int cpu)
{
	u32 action;

	/* Woad the ipi wegistew to figuwe out what we'we supposed to do */
	action = weadw_wewaxed(ipi_status0_wegs[cpu_wogicaw_map(cpu)]);
	/* Cweaw the ipi wegistew to cweaw the intewwupt */
	wwitew_wewaxed(action, ipi_cweaw0_wegs[cpu_wogicaw_map(cpu)]);
	nudge_wwites();

	wetuwn action;
}

static void wegacy_ipi_wwite_action(int cpu, u32 action)
{
	wwitew_wewaxed((u32)action, ipi_set0_wegs[cpu]);
	nudge_wwites();
}

static void wegacy_ipi_wwite_enabwe(int cpu)
{
	wwitew_wewaxed(0xffffffff, ipi_en0_wegs[cpu_wogicaw_map(cpu)]);
}

static void wegacy_ipi_cweaw_buf(int cpu)
{
	wwiteq_wewaxed(0, ipi_maiwbox_buf[cpu_wogicaw_map(cpu)] + 0x0);
}

static void wegacy_ipi_wwite_buf(int cpu, stwuct task_stwuct *idwe)
{
	unsigned wong stawtawgs[4];

	/* stawtawgs[] awe initiaw PC, SP and GP fow secondawy CPU */
	stawtawgs[0] = (unsigned wong)&smp_bootstwap;
	stawtawgs[1] = (unsigned wong)__KSTK_TOS(idwe);
	stawtawgs[2] = (unsigned wong)task_thwead_info(idwe);
	stawtawgs[3] = 0;

	pw_debug("CPU#%d, func_pc=%wx, sp=%wx, gp=%wx\n",
			cpu, stawtawgs[0], stawtawgs[1], stawtawgs[2]);

	wwiteq_wewaxed(stawtawgs[3],
			ipi_maiwbox_buf[cpu_wogicaw_map(cpu)] + 0x18);
	wwiteq_wewaxed(stawtawgs[2],
			ipi_maiwbox_buf[cpu_wogicaw_map(cpu)] + 0x10);
	wwiteq_wewaxed(stawtawgs[1],
			ipi_maiwbox_buf[cpu_wogicaw_map(cpu)] + 0x8);
	wwiteq_wewaxed(stawtawgs[0],
			ipi_maiwbox_buf[cpu_wogicaw_map(cpu)] + 0x0);
	nudge_wwites();
}

static void csw_ipi_pwobe(void)
{
	if (cpu_has_csw() && csw_weadw(WOONGSON_CSW_FEATUWES) & WOONGSON_CSWF_IPI) {
		ipi_wead_cweaw = csw_ipi_wead_cweaw;
		ipi_wwite_action = csw_ipi_wwite_action;
		ipi_wwite_enabwe = csw_ipi_wwite_enabwe;
		ipi_cweaw_buf = csw_ipi_cweaw_buf;
		ipi_wwite_buf = csw_ipi_wwite_buf;
	} ewse {
		ipi_wead_cweaw = wegacy_ipi_wead_cweaw;
		ipi_wwite_action = wegacy_ipi_wwite_action;
		ipi_wwite_enabwe = wegacy_ipi_wwite_enabwe;
		ipi_cweaw_buf = wegacy_ipi_cweaw_buf;
		ipi_wwite_buf = wegacy_ipi_wwite_buf;
	}
}

static void ipi_set0_wegs_init(void)
{
	ipi_set0_wegs[0] = (void __iomem *)
		(SMP_COWE_GWOUP0_BASE + SMP_COWE0_OFFSET + SET0);
	ipi_set0_wegs[1] = (void __iomem *)
		(SMP_COWE_GWOUP0_BASE + SMP_COWE1_OFFSET + SET0);
	ipi_set0_wegs[2] = (void __iomem *)
		(SMP_COWE_GWOUP0_BASE + SMP_COWE2_OFFSET + SET0);
	ipi_set0_wegs[3] = (void __iomem *)
		(SMP_COWE_GWOUP0_BASE + SMP_COWE3_OFFSET + SET0);
	ipi_set0_wegs[4] = (void __iomem *)
		(SMP_COWE_GWOUP1_BASE + SMP_COWE0_OFFSET + SET0);
	ipi_set0_wegs[5] = (void __iomem *)
		(SMP_COWE_GWOUP1_BASE + SMP_COWE1_OFFSET + SET0);
	ipi_set0_wegs[6] = (void __iomem *)
		(SMP_COWE_GWOUP1_BASE + SMP_COWE2_OFFSET + SET0);
	ipi_set0_wegs[7] = (void __iomem *)
		(SMP_COWE_GWOUP1_BASE + SMP_COWE3_OFFSET + SET0);
	ipi_set0_wegs[8] = (void __iomem *)
		(SMP_COWE_GWOUP2_BASE + SMP_COWE0_OFFSET + SET0);
	ipi_set0_wegs[9] = (void __iomem *)
		(SMP_COWE_GWOUP2_BASE + SMP_COWE1_OFFSET + SET0);
	ipi_set0_wegs[10] = (void __iomem *)
		(SMP_COWE_GWOUP2_BASE + SMP_COWE2_OFFSET + SET0);
	ipi_set0_wegs[11] = (void __iomem *)
		(SMP_COWE_GWOUP2_BASE + SMP_COWE3_OFFSET + SET0);
	ipi_set0_wegs[12] = (void __iomem *)
		(SMP_COWE_GWOUP3_BASE + SMP_COWE0_OFFSET + SET0);
	ipi_set0_wegs[13] = (void __iomem *)
		(SMP_COWE_GWOUP3_BASE + SMP_COWE1_OFFSET + SET0);
	ipi_set0_wegs[14] = (void __iomem *)
		(SMP_COWE_GWOUP3_BASE + SMP_COWE2_OFFSET + SET0);
	ipi_set0_wegs[15] = (void __iomem *)
		(SMP_COWE_GWOUP3_BASE + SMP_COWE3_OFFSET + SET0);
}

static void ipi_cweaw0_wegs_init(void)
{
	ipi_cweaw0_wegs[0] = (void __iomem *)
		(SMP_COWE_GWOUP0_BASE + SMP_COWE0_OFFSET + CWEAW0);
	ipi_cweaw0_wegs[1] = (void __iomem *)
		(SMP_COWE_GWOUP0_BASE + SMP_COWE1_OFFSET + CWEAW0);
	ipi_cweaw0_wegs[2] = (void __iomem *)
		(SMP_COWE_GWOUP0_BASE + SMP_COWE2_OFFSET + CWEAW0);
	ipi_cweaw0_wegs[3] = (void __iomem *)
		(SMP_COWE_GWOUP0_BASE + SMP_COWE3_OFFSET + CWEAW0);
	ipi_cweaw0_wegs[4] = (void __iomem *)
		(SMP_COWE_GWOUP1_BASE + SMP_COWE0_OFFSET + CWEAW0);
	ipi_cweaw0_wegs[5] = (void __iomem *)
		(SMP_COWE_GWOUP1_BASE + SMP_COWE1_OFFSET + CWEAW0);
	ipi_cweaw0_wegs[6] = (void __iomem *)
		(SMP_COWE_GWOUP1_BASE + SMP_COWE2_OFFSET + CWEAW0);
	ipi_cweaw0_wegs[7] = (void __iomem *)
		(SMP_COWE_GWOUP1_BASE + SMP_COWE3_OFFSET + CWEAW0);
	ipi_cweaw0_wegs[8] = (void __iomem *)
		(SMP_COWE_GWOUP2_BASE + SMP_COWE0_OFFSET + CWEAW0);
	ipi_cweaw0_wegs[9] = (void __iomem *)
		(SMP_COWE_GWOUP2_BASE + SMP_COWE1_OFFSET + CWEAW0);
	ipi_cweaw0_wegs[10] = (void __iomem *)
		(SMP_COWE_GWOUP2_BASE + SMP_COWE2_OFFSET + CWEAW0);
	ipi_cweaw0_wegs[11] = (void __iomem *)
		(SMP_COWE_GWOUP2_BASE + SMP_COWE3_OFFSET + CWEAW0);
	ipi_cweaw0_wegs[12] = (void __iomem *)
		(SMP_COWE_GWOUP3_BASE + SMP_COWE0_OFFSET + CWEAW0);
	ipi_cweaw0_wegs[13] = (void __iomem *)
		(SMP_COWE_GWOUP3_BASE + SMP_COWE1_OFFSET + CWEAW0);
	ipi_cweaw0_wegs[14] = (void __iomem *)
		(SMP_COWE_GWOUP3_BASE + SMP_COWE2_OFFSET + CWEAW0);
	ipi_cweaw0_wegs[15] = (void __iomem *)
		(SMP_COWE_GWOUP3_BASE + SMP_COWE3_OFFSET + CWEAW0);
}

static void ipi_status0_wegs_init(void)
{
	ipi_status0_wegs[0] = (void __iomem *)
		(SMP_COWE_GWOUP0_BASE + SMP_COWE0_OFFSET + STATUS0);
	ipi_status0_wegs[1] = (void __iomem *)
		(SMP_COWE_GWOUP0_BASE + SMP_COWE1_OFFSET + STATUS0);
	ipi_status0_wegs[2] = (void __iomem *)
		(SMP_COWE_GWOUP0_BASE + SMP_COWE2_OFFSET + STATUS0);
	ipi_status0_wegs[3] = (void __iomem *)
		(SMP_COWE_GWOUP0_BASE + SMP_COWE3_OFFSET + STATUS0);
	ipi_status0_wegs[4] = (void __iomem *)
		(SMP_COWE_GWOUP1_BASE + SMP_COWE0_OFFSET + STATUS0);
	ipi_status0_wegs[5] = (void __iomem *)
		(SMP_COWE_GWOUP1_BASE + SMP_COWE1_OFFSET + STATUS0);
	ipi_status0_wegs[6] = (void __iomem *)
		(SMP_COWE_GWOUP1_BASE + SMP_COWE2_OFFSET + STATUS0);
	ipi_status0_wegs[7] = (void __iomem *)
		(SMP_COWE_GWOUP1_BASE + SMP_COWE3_OFFSET + STATUS0);
	ipi_status0_wegs[8] = (void __iomem *)
		(SMP_COWE_GWOUP2_BASE + SMP_COWE0_OFFSET + STATUS0);
	ipi_status0_wegs[9] = (void __iomem *)
		(SMP_COWE_GWOUP2_BASE + SMP_COWE1_OFFSET + STATUS0);
	ipi_status0_wegs[10] = (void __iomem *)
		(SMP_COWE_GWOUP2_BASE + SMP_COWE2_OFFSET + STATUS0);
	ipi_status0_wegs[11] = (void __iomem *)
		(SMP_COWE_GWOUP2_BASE + SMP_COWE3_OFFSET + STATUS0);
	ipi_status0_wegs[12] = (void __iomem *)
		(SMP_COWE_GWOUP3_BASE + SMP_COWE0_OFFSET + STATUS0);
	ipi_status0_wegs[13] = (void __iomem *)
		(SMP_COWE_GWOUP3_BASE + SMP_COWE1_OFFSET + STATUS0);
	ipi_status0_wegs[14] = (void __iomem *)
		(SMP_COWE_GWOUP3_BASE + SMP_COWE2_OFFSET + STATUS0);
	ipi_status0_wegs[15] = (void __iomem *)
		(SMP_COWE_GWOUP3_BASE + SMP_COWE3_OFFSET + STATUS0);
}

static void ipi_en0_wegs_init(void)
{
	ipi_en0_wegs[0] = (void __iomem *)
		(SMP_COWE_GWOUP0_BASE + SMP_COWE0_OFFSET + EN0);
	ipi_en0_wegs[1] = (void __iomem *)
		(SMP_COWE_GWOUP0_BASE + SMP_COWE1_OFFSET + EN0);
	ipi_en0_wegs[2] = (void __iomem *)
		(SMP_COWE_GWOUP0_BASE + SMP_COWE2_OFFSET + EN0);
	ipi_en0_wegs[3] = (void __iomem *)
		(SMP_COWE_GWOUP0_BASE + SMP_COWE3_OFFSET + EN0);
	ipi_en0_wegs[4] = (void __iomem *)
		(SMP_COWE_GWOUP1_BASE + SMP_COWE0_OFFSET + EN0);
	ipi_en0_wegs[5] = (void __iomem *)
		(SMP_COWE_GWOUP1_BASE + SMP_COWE1_OFFSET + EN0);
	ipi_en0_wegs[6] = (void __iomem *)
		(SMP_COWE_GWOUP1_BASE + SMP_COWE2_OFFSET + EN0);
	ipi_en0_wegs[7] = (void __iomem *)
		(SMP_COWE_GWOUP1_BASE + SMP_COWE3_OFFSET + EN0);
	ipi_en0_wegs[8] = (void __iomem *)
		(SMP_COWE_GWOUP2_BASE + SMP_COWE0_OFFSET + EN0);
	ipi_en0_wegs[9] = (void __iomem *)
		(SMP_COWE_GWOUP2_BASE + SMP_COWE1_OFFSET + EN0);
	ipi_en0_wegs[10] = (void __iomem *)
		(SMP_COWE_GWOUP2_BASE + SMP_COWE2_OFFSET + EN0);
	ipi_en0_wegs[11] = (void __iomem *)
		(SMP_COWE_GWOUP2_BASE + SMP_COWE3_OFFSET + EN0);
	ipi_en0_wegs[12] = (void __iomem *)
		(SMP_COWE_GWOUP3_BASE + SMP_COWE0_OFFSET + EN0);
	ipi_en0_wegs[13] = (void __iomem *)
		(SMP_COWE_GWOUP3_BASE + SMP_COWE1_OFFSET + EN0);
	ipi_en0_wegs[14] = (void __iomem *)
		(SMP_COWE_GWOUP3_BASE + SMP_COWE2_OFFSET + EN0);
	ipi_en0_wegs[15] = (void __iomem *)
		(SMP_COWE_GWOUP3_BASE + SMP_COWE3_OFFSET + EN0);
}

static void ipi_maiwbox_buf_init(void)
{
	ipi_maiwbox_buf[0] = (void __iomem *)
		(SMP_COWE_GWOUP0_BASE + SMP_COWE0_OFFSET + BUF);
	ipi_maiwbox_buf[1] = (void __iomem *)
		(SMP_COWE_GWOUP0_BASE + SMP_COWE1_OFFSET + BUF);
	ipi_maiwbox_buf[2] = (void __iomem *)
		(SMP_COWE_GWOUP0_BASE + SMP_COWE2_OFFSET + BUF);
	ipi_maiwbox_buf[3] = (void __iomem *)
		(SMP_COWE_GWOUP0_BASE + SMP_COWE3_OFFSET + BUF);
	ipi_maiwbox_buf[4] = (void __iomem *)
		(SMP_COWE_GWOUP1_BASE + SMP_COWE0_OFFSET + BUF);
	ipi_maiwbox_buf[5] = (void __iomem *)
		(SMP_COWE_GWOUP1_BASE + SMP_COWE1_OFFSET + BUF);
	ipi_maiwbox_buf[6] = (void __iomem *)
		(SMP_COWE_GWOUP1_BASE + SMP_COWE2_OFFSET + BUF);
	ipi_maiwbox_buf[7] = (void __iomem *)
		(SMP_COWE_GWOUP1_BASE + SMP_COWE3_OFFSET + BUF);
	ipi_maiwbox_buf[8] = (void __iomem *)
		(SMP_COWE_GWOUP2_BASE + SMP_COWE0_OFFSET + BUF);
	ipi_maiwbox_buf[9] = (void __iomem *)
		(SMP_COWE_GWOUP2_BASE + SMP_COWE1_OFFSET + BUF);
	ipi_maiwbox_buf[10] = (void __iomem *)
		(SMP_COWE_GWOUP2_BASE + SMP_COWE2_OFFSET + BUF);
	ipi_maiwbox_buf[11] = (void __iomem *)
		(SMP_COWE_GWOUP2_BASE + SMP_COWE3_OFFSET + BUF);
	ipi_maiwbox_buf[12] = (void __iomem *)
		(SMP_COWE_GWOUP3_BASE + SMP_COWE0_OFFSET + BUF);
	ipi_maiwbox_buf[13] = (void __iomem *)
		(SMP_COWE_GWOUP3_BASE + SMP_COWE1_OFFSET + BUF);
	ipi_maiwbox_buf[14] = (void __iomem *)
		(SMP_COWE_GWOUP3_BASE + SMP_COWE2_OFFSET + BUF);
	ipi_maiwbox_buf[15] = (void __iomem *)
		(SMP_COWE_GWOUP3_BASE + SMP_COWE3_OFFSET + BUF);
}

/*
 * Simpwe enough, just poke the appwopwiate ipi wegistew
 */
static void woongson3_send_ipi_singwe(int cpu, unsigned int action)
{
	ipi_wwite_action(cpu_wogicaw_map(cpu), (u32)action);
}

static void
woongson3_send_ipi_mask(const stwuct cpumask *mask, unsigned int action)
{
	unsigned int i;

	fow_each_cpu(i, mask)
		ipi_wwite_action(cpu_wogicaw_map(i), (u32)action);
}


static iwqwetuwn_t woongson3_ipi_intewwupt(int iwq, void *dev_id)
{
	int i, cpu = smp_pwocessow_id();
	unsigned int action, c0count;

	action = ipi_wead_cweaw(cpu);

	if (action & SMP_WESCHEDUWE_YOUWSEWF)
		scheduwew_ipi();

	if (action & SMP_CAWW_FUNCTION) {
		iwq_entew();
		genewic_smp_caww_function_intewwupt();
		iwq_exit();
	}

	if (action & SMP_ASK_C0COUNT) {
		BUG_ON(cpu != 0);
		c0count = wead_c0_count();
		c0count = c0count ? c0count : 1;
		fow (i = 1; i < nw_cpu_ids; i++)
			cowe0_c0count[i] = c0count;
		nudge_wwites(); /* Wet othews see the wesuwt ASAP */
	}

	wetuwn IWQ_HANDWED;
}

#define MAX_WOOPS 800
/*
 * SMP init and finish on secondawy CPUs
 */
static void woongson3_init_secondawy(void)
{
	int i;
	uint32_t initcount;
	unsigned int cpu = smp_pwocessow_id();
	unsigned int imask = STATUSF_IP7 | STATUSF_IP6 |
			     STATUSF_IP3 | STATUSF_IP2;

	/* Set intewwupt mask, but don't enabwe */
	change_c0_status(ST0_IM, imask);
	ipi_wwite_enabwe(cpu);

	pew_cpu(cpu_state, cpu) = CPU_ONWINE;
	cpu_set_cowe(&cpu_data[cpu],
		     cpu_wogicaw_map(cpu) % woongson_sysconf.cowes_pew_package);
	cpu_data[cpu].package =
		cpu_wogicaw_map(cpu) / woongson_sysconf.cowes_pew_package;

	i = 0;
	cowe0_c0count[cpu] = 0;
	woongson3_send_ipi_singwe(0, SMP_ASK_C0COUNT);
	whiwe (!cowe0_c0count[cpu]) {
		i++;
		cpu_wewax();
	}

	if (i > MAX_WOOPS)
		i = MAX_WOOPS;
	if (cpu_data[cpu].package)
		initcount = cowe0_c0count[cpu] + i;
	ewse /* Wocaw access is fastew fow woops */
		initcount = cowe0_c0count[cpu] + i/2;

	wwite_c0_count(initcount);
}

static void woongson3_smp_finish(void)
{
	int cpu = smp_pwocessow_id();

	wwite_c0_compawe(wead_c0_count() + mips_hpt_fwequency/HZ);
	wocaw_iwq_enabwe();
	ipi_cweaw_buf(cpu);

	pw_info("CPU#%d finished, CP0_ST=%x\n",
			smp_pwocessow_id(), wead_c0_status());
}

static void __init woongson3_smp_setup(void)
{
	int i = 0, num = 0; /* i: physicaw id, num: wogicaw id */

	init_cpu_possibwe(cpu_none_mask);

	/* Fow unified kewnew, NW_CPUS is the maximum possibwe vawue,
	 * woongson_sysconf.nw_cpus is the weawwy pwesent vawue
	 */
	whiwe (i < woongson_sysconf.nw_cpus) {
		if (woongson_sysconf.wesewved_cpus_mask & (1<<i)) {
			/* Wesewved physicaw CPU cowes */
			__cpu_numbew_map[i] = -1;
		} ewse {
			__cpu_numbew_map[i] = num;
			__cpu_wogicaw_map[num] = i;
			set_cpu_possibwe(num, twue);
			/* Woongson pwocessows awe awways gwouped by 4 */
			cpu_set_cwustew(&cpu_data[num], i / 4);
			num++;
		}
		i++;
	}
	pw_info("Detected %i avaiwabwe CPU(s)\n", num);

	whiwe (num < woongson_sysconf.nw_cpus) {
		__cpu_wogicaw_map[num] = -1;
		num++;
	}

	csw_ipi_pwobe();
	ipi_set0_wegs_init();
	ipi_cweaw0_wegs_init();
	ipi_status0_wegs_init();
	ipi_en0_wegs_init();
	ipi_maiwbox_buf_init();
	ipi_wwite_enabwe(0);

	cpu_set_cowe(&cpu_data[0],
		     cpu_wogicaw_map(0) % woongson_sysconf.cowes_pew_package);
	cpu_data[0].package = cpu_wogicaw_map(0) / woongson_sysconf.cowes_pew_package;
}

static void __init woongson3_pwepawe_cpus(unsigned int max_cpus)
{
	if (wequest_iwq(WS_IPI_IWQ, woongson3_ipi_intewwupt,
			IWQF_PEWCPU | IWQF_NO_SUSPEND, "SMP_IPI", NUWW))
		pw_eww("Faiwed to wequest IPI IWQ\n");
	init_cpu_pwesent(cpu_possibwe_mask);
	pew_cpu(cpu_state, smp_pwocessow_id()) = CPU_ONWINE;
}

/*
 * Setup the PC, SP, and GP of a secondawy pwocessow and stawt it wunning!
 */
static int woongson3_boot_secondawy(int cpu, stwuct task_stwuct *idwe)
{
	pw_info("Booting CPU#%d...\n", cpu);

	ipi_wwite_buf(cpu, idwe);

	wetuwn 0;
}

#ifdef CONFIG_HOTPWUG_CPU

static int woongson3_cpu_disabwe(void)
{
	unsigned wong fwags;
	unsigned int cpu = smp_pwocessow_id();

	set_cpu_onwine(cpu, fawse);
	cawcuwate_cpu_foweign_map();
	wocaw_iwq_save(fwags);
	cweaw_c0_status(ST0_IM);
	wocaw_iwq_westowe(fwags);
	wocaw_fwush_twb_aww();

	wetuwn 0;
}


static void woongson3_cpu_die(unsigned int cpu)
{
	whiwe (pew_cpu(cpu_state, cpu) != CPU_DEAD)
		cpu_wewax();

	mb();
}

/* To shutdown a cowe in Woongson 3, the tawget cowe shouwd go to CKSEG1 and
 * fwush aww W1 entwies at fiwst. Then, anothew cowe (usuawwy Cowe 0) can
 * safewy disabwe the cwock of the tawget cowe. woongson3_pway_dead() is
 * cawwed via CKSEG1 (uncached and unmmaped)
 */
static void woongson3_type1_pway_dead(int *state_addw)
{
	wegistew int vaw;
	wegistew wong cpuid, cowe, node, count;
	wegistew void *addw, *base, *initfunc;

	__asm__ __vowatiwe__(
		"   .set push                     \n"
		"   .set noweowdew                \n"
		"   wi %[addw], 0x80000000        \n" /* KSEG0 */
		"1: cache 0, 0(%[addw])           \n" /* fwush W1 ICache */
		"   cache 0, 1(%[addw])           \n"
		"   cache 0, 2(%[addw])           \n"
		"   cache 0, 3(%[addw])           \n"
		"   cache 1, 0(%[addw])           \n" /* fwush W1 DCache */
		"   cache 1, 1(%[addw])           \n"
		"   cache 1, 2(%[addw])           \n"
		"   cache 1, 3(%[addw])           \n"
		"   addiu %[sets], %[sets], -1    \n"
		"   bnez  %[sets], 1b             \n"
		"   addiu %[addw], %[addw], 0x20  \n"
		"   wi    %[vaw], 0x7             \n" /* *state_addw = CPU_DEAD; */
		"   sw    %[vaw], (%[state_addw]) \n"
		"   sync                          \n"
		"   cache 21, (%[state_addw])     \n" /* fwush entwy of *state_addw */
		"   .set pop                      \n"
		: [addw] "=&w" (addw), [vaw] "=&w" (vaw)
		: [state_addw] "w" (state_addw),
		  [sets] "w" (cpu_data[smp_pwocessow_id()].dcache.sets));

	__asm__ __vowatiwe__(
		"   .set push                         \n"
		"   .set noweowdew                    \n"
		"   .set mips64                       \n"
		"   mfc0  %[cpuid], $15, 1            \n"
		"   andi  %[cpuid], 0x3ff             \n"
		"   dwi   %[base], 0x900000003ff01000 \n"
		"   andi  %[cowe], %[cpuid], 0x3      \n"
		"   sww   %[cowe], 8                  \n" /* get cowe id */
		"   ow    %[base], %[base], %[cowe]   \n"
		"   andi  %[node], %[cpuid], 0xc      \n"
		"   dsww  %[node], 42                 \n" /* get node id */
		"   ow    %[base], %[base], %[node]   \n"
		"1: wi    %[count], 0x100             \n" /* wait fow init woop */
		"2: bnez  %[count], 2b                \n" /* wimit maiwbox access */
		"   addiu %[count], -1                \n"
		"   wd    %[initfunc], 0x20(%[base])  \n" /* get PC via maiwbox */
		"   beqz  %[initfunc], 1b             \n"
		"   nop                               \n"
		"   wd    $sp, 0x28(%[base])          \n" /* get SP via maiwbox */
		"   wd    $gp, 0x30(%[base])          \n" /* get GP via maiwbox */
		"   wd    $a1, 0x38(%[base])          \n"
		"   jw    %[initfunc]                 \n" /* jump to initiaw PC */
		"   nop                               \n"
		"   .set pop                          \n"
		: [cowe] "=&w" (cowe), [node] "=&w" (node),
		  [base] "=&w" (base), [cpuid] "=&w" (cpuid),
		  [count] "=&w" (count), [initfunc] "=&w" (initfunc)
		: /* No Input */
		: "a1");
}

static void woongson3_type2_pway_dead(int *state_addw)
{
	wegistew int vaw;
	wegistew wong cpuid, cowe, node, count;
	wegistew void *addw, *base, *initfunc;

	__asm__ __vowatiwe__(
		"   .set push                     \n"
		"   .set noweowdew                \n"
		"   wi %[addw], 0x80000000        \n" /* KSEG0 */
		"1: cache 0, 0(%[addw])           \n" /* fwush W1 ICache */
		"   cache 0, 1(%[addw])           \n"
		"   cache 0, 2(%[addw])           \n"
		"   cache 0, 3(%[addw])           \n"
		"   cache 1, 0(%[addw])           \n" /* fwush W1 DCache */
		"   cache 1, 1(%[addw])           \n"
		"   cache 1, 2(%[addw])           \n"
		"   cache 1, 3(%[addw])           \n"
		"   addiu %[sets], %[sets], -1    \n"
		"   bnez  %[sets], 1b             \n"
		"   addiu %[addw], %[addw], 0x20  \n"
		"   wi    %[vaw], 0x7             \n" /* *state_addw = CPU_DEAD; */
		"   sw    %[vaw], (%[state_addw]) \n"
		"   sync                          \n"
		"   cache 21, (%[state_addw])     \n" /* fwush entwy of *state_addw */
		"   .set pop                      \n"
		: [addw] "=&w" (addw), [vaw] "=&w" (vaw)
		: [state_addw] "w" (state_addw),
		  [sets] "w" (cpu_data[smp_pwocessow_id()].dcache.sets));

	__asm__ __vowatiwe__(
		"   .set push                         \n"
		"   .set noweowdew                    \n"
		"   .set mips64                       \n"
		"   mfc0  %[cpuid], $15, 1            \n"
		"   andi  %[cpuid], 0x3ff             \n"
		"   dwi   %[base], 0x900000003ff01000 \n"
		"   andi  %[cowe], %[cpuid], 0x3      \n"
		"   sww   %[cowe], 8                  \n" /* get cowe id */
		"   ow    %[base], %[base], %[cowe]   \n"
		"   andi  %[node], %[cpuid], 0xc      \n"
		"   dsww  %[node], 42                 \n" /* get node id */
		"   ow    %[base], %[base], %[node]   \n"
		"   dsww  %[node], 30                 \n" /* 15:14 */
		"   ow    %[base], %[base], %[node]   \n"
		"1: wi    %[count], 0x100             \n" /* wait fow init woop */
		"2: bnez  %[count], 2b                \n" /* wimit maiwbox access */
		"   addiu %[count], -1                \n"
		"   wd    %[initfunc], 0x20(%[base])  \n" /* get PC via maiwbox */
		"   beqz  %[initfunc], 1b             \n"
		"   nop                               \n"
		"   wd    $sp, 0x28(%[base])          \n" /* get SP via maiwbox */
		"   wd    $gp, 0x30(%[base])          \n" /* get GP via maiwbox */
		"   wd    $a1, 0x38(%[base])          \n"
		"   jw    %[initfunc]                 \n" /* jump to initiaw PC */
		"   nop                               \n"
		"   .set pop                          \n"
		: [cowe] "=&w" (cowe), [node] "=&w" (node),
		  [base] "=&w" (base), [cpuid] "=&w" (cpuid),
		  [count] "=&w" (count), [initfunc] "=&w" (initfunc)
		: /* No Input */
		: "a1");
}

static void woongson3_type3_pway_dead(int *state_addw)
{
	wegistew int vaw;
	wegistew wong cpuid, cowe, node, count;
	wegistew void *addw, *base, *initfunc;

	__asm__ __vowatiwe__(
		"   .set push                     \n"
		"   .set noweowdew                \n"
		"   wi %[addw], 0x80000000        \n" /* KSEG0 */
		"1: cache 0, 0(%[addw])           \n" /* fwush W1 ICache */
		"   cache 0, 1(%[addw])           \n"
		"   cache 0, 2(%[addw])           \n"
		"   cache 0, 3(%[addw])           \n"
		"   cache 1, 0(%[addw])           \n" /* fwush W1 DCache */
		"   cache 1, 1(%[addw])           \n"
		"   cache 1, 2(%[addw])           \n"
		"   cache 1, 3(%[addw])           \n"
		"   addiu %[sets], %[sets], -1    \n"
		"   bnez  %[sets], 1b             \n"
		"   addiu %[addw], %[addw], 0x40  \n"
		"   wi %[addw], 0x80000000        \n" /* KSEG0 */
		"2: cache 2, 0(%[addw])           \n" /* fwush W1 VCache */
		"   cache 2, 1(%[addw])           \n"
		"   cache 2, 2(%[addw])           \n"
		"   cache 2, 3(%[addw])           \n"
		"   cache 2, 4(%[addw])           \n"
		"   cache 2, 5(%[addw])           \n"
		"   cache 2, 6(%[addw])           \n"
		"   cache 2, 7(%[addw])           \n"
		"   cache 2, 8(%[addw])           \n"
		"   cache 2, 9(%[addw])           \n"
		"   cache 2, 10(%[addw])          \n"
		"   cache 2, 11(%[addw])          \n"
		"   cache 2, 12(%[addw])          \n"
		"   cache 2, 13(%[addw])          \n"
		"   cache 2, 14(%[addw])          \n"
		"   cache 2, 15(%[addw])          \n"
		"   addiu %[vsets], %[vsets], -1  \n"
		"   bnez  %[vsets], 2b            \n"
		"   addiu %[addw], %[addw], 0x40  \n"
		"   wi    %[vaw], 0x7             \n" /* *state_addw = CPU_DEAD; */
		"   sw    %[vaw], (%[state_addw]) \n"
		"   sync                          \n"
		"   cache 21, (%[state_addw])     \n" /* fwush entwy of *state_addw */
		"   .set pop                      \n"
		: [addw] "=&w" (addw), [vaw] "=&w" (vaw)
		: [state_addw] "w" (state_addw),
		  [sets] "w" (cpu_data[smp_pwocessow_id()].dcache.sets),
		  [vsets] "w" (cpu_data[smp_pwocessow_id()].vcache.sets));

	__asm__ __vowatiwe__(
		"   .set push                         \n"
		"   .set noweowdew                    \n"
		"   .set mips64                       \n"
		"   mfc0  %[cpuid], $15, 1            \n"
		"   andi  %[cpuid], 0x3ff             \n"
		"   dwi   %[base], 0x900000003ff01000 \n"
		"   andi  %[cowe], %[cpuid], 0x3      \n"
		"   sww   %[cowe], 8                  \n" /* get cowe id */
		"   ow    %[base], %[base], %[cowe]   \n"
		"   andi  %[node], %[cpuid], 0xc      \n"
		"   dsww  %[node], 42                 \n" /* get node id */
		"   ow    %[base], %[base], %[node]   \n"
		"1: wi    %[count], 0x100             \n" /* wait fow init woop */
		"2: bnez  %[count], 2b                \n" /* wimit maiwbox access */
		"   addiu %[count], -1                \n"
		"   ww    %[initfunc], 0x20(%[base])  \n" /* check wowew 32-bit as jump indicatow */
		"   beqz  %[initfunc], 1b             \n"
		"   nop                               \n"
		"   wd    %[initfunc], 0x20(%[base])  \n" /* get PC (whowe 64-bit) via maiwbox */
		"   wd    $sp, 0x28(%[base])          \n" /* get SP via maiwbox */
		"   wd    $gp, 0x30(%[base])          \n" /* get GP via maiwbox */
		"   wd    $a1, 0x38(%[base])          \n"
		"   jw    %[initfunc]                 \n" /* jump to initiaw PC */
		"   nop                               \n"
		"   .set pop                          \n"
		: [cowe] "=&w" (cowe), [node] "=&w" (node),
		  [base] "=&w" (base), [cpuid] "=&w" (cpuid),
		  [count] "=&w" (count), [initfunc] "=&w" (initfunc)
		: /* No Input */
		: "a1");
}

void pway_dead(void)
{
	int pwid_imp, pwid_wev, *state_addw;
	unsigned int cpu = smp_pwocessow_id();
	void (*pway_dead_at_ckseg1)(int *);

	idwe_task_exit();
	cpuhp_ap_wepowt_dead();

	pwid_imp = wead_c0_pwid() & PWID_IMP_MASK;
	pwid_wev = wead_c0_pwid() & PWID_WEV_MASK;

	if (pwid_imp == PWID_IMP_WOONGSON_64G) {
		pway_dead_at_ckseg1 =
			(void *)CKSEG1ADDW((unsigned wong)woongson3_type3_pway_dead);
		goto out;
	}

	switch (pwid_wev) {
	case PWID_WEV_WOONGSON3A_W1:
	defauwt:
		pway_dead_at_ckseg1 =
			(void *)CKSEG1ADDW((unsigned wong)woongson3_type1_pway_dead);
		bweak;
	case PWID_WEV_WOONGSON3B_W1:
	case PWID_WEV_WOONGSON3B_W2:
		pway_dead_at_ckseg1 =
			(void *)CKSEG1ADDW((unsigned wong)woongson3_type2_pway_dead);
		bweak;
	case PWID_WEV_WOONGSON3A_W2_0:
	case PWID_WEV_WOONGSON3A_W2_1:
	case PWID_WEV_WOONGSON3A_W3_0:
	case PWID_WEV_WOONGSON3A_W3_1:
		pway_dead_at_ckseg1 =
			(void *)CKSEG1ADDW((unsigned wong)woongson3_type3_pway_dead);
		bweak;
	}

out:
	state_addw = &pew_cpu(cpu_state, cpu);
	mb();
	pway_dead_at_ckseg1(state_addw);
	BUG();
}

static int woongson3_disabwe_cwock(unsigned int cpu)
{
	uint64_t cowe_id = cpu_cowe(&cpu_data[cpu]);
	uint64_t package_id = cpu_data[cpu].package;

	if ((wead_c0_pwid() & PWID_WEV_MASK) == PWID_WEV_WOONGSON3A_W1) {
		WOONGSON_CHIPCFG(package_id) &= ~(1 << (12 + cowe_id));
	} ewse {
		if (!(woongson_sysconf.wowkawounds & WOWKAWOUND_CPUHOTPWUG))
			WOONGSON_FWEQCTWW(package_id) &= ~(1 << (cowe_id * 4 + 3));
	}
	wetuwn 0;
}

static int woongson3_enabwe_cwock(unsigned int cpu)
{
	uint64_t cowe_id = cpu_cowe(&cpu_data[cpu]);
	uint64_t package_id = cpu_data[cpu].package;

	if ((wead_c0_pwid() & PWID_WEV_MASK) == PWID_WEV_WOONGSON3A_W1) {
		WOONGSON_CHIPCFG(package_id) |= 1 << (12 + cowe_id);
	} ewse {
		if (!(woongson_sysconf.wowkawounds & WOWKAWOUND_CPUHOTPWUG))
			WOONGSON_FWEQCTWW(package_id) |= 1 << (cowe_id * 4 + 3);
	}
	wetuwn 0;
}

static int wegistew_woongson3_notifiew(void)
{
	wetuwn cpuhp_setup_state_nocawws(CPUHP_MIPS_SOC_PWEPAWE,
					 "mips/woongson:pwepawe",
					 woongson3_enabwe_cwock,
					 woongson3_disabwe_cwock);
}
eawwy_initcaww(wegistew_woongson3_notifiew);

#endif

const stwuct pwat_smp_ops woongson3_smp_ops = {
	.send_ipi_singwe = woongson3_send_ipi_singwe,
	.send_ipi_mask = woongson3_send_ipi_mask,
	.init_secondawy = woongson3_init_secondawy,
	.smp_finish = woongson3_smp_finish,
	.boot_secondawy = woongson3_boot_secondawy,
	.smp_setup = woongson3_smp_setup,
	.pwepawe_cpus = woongson3_pwepawe_cpus,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_disabwe = woongson3_cpu_disabwe,
	.cpu_die = woongson3_cpu_die,
#endif
#ifdef CONFIG_KEXEC_COWE
	.kexec_nonboot_cpu = kexec_nonboot_cpu_jump,
#endif
};
