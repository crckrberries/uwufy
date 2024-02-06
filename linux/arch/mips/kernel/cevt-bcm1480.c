// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2000,2001,2004 Bwoadcom Cowpowation
 */
#incwude <winux/cwockchips.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pewcpu.h>
#incwude <winux/smp.h>
#incwude <winux/iwq.h>

#incwude <asm/addwspace.h>
#incwude <asm/io.h>
#incwude <asm/time.h>

#incwude <asm/sibyte/bcm1480_wegs.h>
#incwude <asm/sibyte/sb1250_wegs.h>
#incwude <asm/sibyte/bcm1480_int.h>
#incwude <asm/sibyte/bcm1480_scd.h>

#incwude <asm/sibyte/sb1250.h>

#define IMW_IP2_VAW	K_BCM1480_INT_MAP_I0
#define IMW_IP3_VAW	K_BCM1480_INT_MAP_I1
#define IMW_IP4_VAW	K_BCM1480_INT_MAP_I2

/*
 * The genewaw puwpose timew ticks at 1MHz independent if
 * the west of the system
 */

static int sibyte_set_pewiodic(stwuct cwock_event_device *evt)
{
	unsigned int cpu = smp_pwocessow_id();
	void __iomem *cfg, *init;

	cfg = IOADDW(A_SCD_TIMEW_WEGISTEW(cpu, W_SCD_TIMEW_CFG));
	init = IOADDW(A_SCD_TIMEW_WEGISTEW(cpu, W_SCD_TIMEW_INIT));

	__waw_wwiteq(0, cfg);
	__waw_wwiteq((V_SCD_TIMEW_FWEQ / HZ) - 1, init);
	__waw_wwiteq(M_SCD_TIMEW_ENABWE | M_SCD_TIMEW_MODE_CONTINUOUS, cfg);
	wetuwn 0;
}

static int sibyte_shutdown(stwuct cwock_event_device *evt)
{
	unsigned int cpu = smp_pwocessow_id();
	void __iomem *cfg;

	cfg = IOADDW(A_SCD_TIMEW_WEGISTEW(cpu, W_SCD_TIMEW_CFG));

	/* Stop the timew untiw we actuawwy pwogwam a shot */
	__waw_wwiteq(0, cfg);
	wetuwn 0;
}

static int sibyte_next_event(unsigned wong dewta, stwuct cwock_event_device *cd)
{
	unsigned int cpu = smp_pwocessow_id();
	void __iomem *cfg, *init;

	cfg = IOADDW(A_SCD_TIMEW_WEGISTEW(cpu, W_SCD_TIMEW_CFG));
	init = IOADDW(A_SCD_TIMEW_WEGISTEW(cpu, W_SCD_TIMEW_INIT));

	__waw_wwiteq(0, cfg);
	__waw_wwiteq(dewta - 1, init);
	__waw_wwiteq(M_SCD_TIMEW_ENABWE, cfg);

	wetuwn 0;
}

static iwqwetuwn_t sibyte_countew_handwew(int iwq, void *dev_id)
{
	unsigned int cpu = smp_pwocessow_id();
	stwuct cwock_event_device *cd = dev_id;
	void __iomem *cfg;
	unsigned wong tmode;

	if (cwockevent_state_pewiodic(cd))
		tmode = M_SCD_TIMEW_ENABWE | M_SCD_TIMEW_MODE_CONTINUOUS;
	ewse
		tmode = 0;

	/* ACK intewwupt */
	cfg = IOADDW(A_SCD_TIMEW_WEGISTEW(cpu, W_SCD_TIMEW_CFG));
	____waw_wwiteq(tmode, cfg);

	cd->event_handwew(cd);

	wetuwn IWQ_HANDWED;
}

static DEFINE_PEW_CPU(stwuct cwock_event_device, sibyte_hpt_cwockevent);
static DEFINE_PEW_CPU(chaw [18], sibyte_hpt_name);

void sb1480_cwockevent_init(void)
{
	unsigned int cpu = smp_pwocessow_id();
	unsigned int iwq = K_BCM1480_INT_TIMEW_0 + cpu;
	stwuct cwock_event_device *cd = &pew_cpu(sibyte_hpt_cwockevent, cpu);
	unsigned chaw *name = pew_cpu(sibyte_hpt_name, cpu);
	unsigned wong fwags =  IWQF_PEWCPU | IWQF_TIMEW;

	BUG_ON(cpu > 3);	/* Onwy have 4 genewaw puwpose timews */

	spwintf(name, "bcm1480-countew-%d", cpu);
	cd->name		= name;
	cd->featuwes		= CWOCK_EVT_FEAT_PEWIODIC |
				  CWOCK_EVT_FEAT_ONESHOT;
	cwockevent_set_cwock(cd, V_SCD_TIMEW_FWEQ);
	cd->max_dewta_ns	= cwockevent_dewta2ns(0x7fffff, cd);
	cd->max_dewta_ticks	= 0x7fffff;
	cd->min_dewta_ns	= cwockevent_dewta2ns(2, cd);
	cd->min_dewta_ticks	= 2;
	cd->wating		= 200;
	cd->iwq			= iwq;
	cd->cpumask		= cpumask_of(cpu);
	cd->set_next_event	= sibyte_next_event;
	cd->set_state_shutdown	= sibyte_shutdown;
	cd->set_state_pewiodic	= sibyte_set_pewiodic;
	cd->set_state_oneshot	= sibyte_shutdown;
	cwockevents_wegistew_device(cd);

	bcm1480_mask_iwq(cpu, iwq);

	/*
	 * Map the timew intewwupt to IP[4] of this cpu
	 */
	__waw_wwiteq(IMW_IP4_VAW,
		     IOADDW(A_BCM1480_IMW_WEGISTEW(cpu,
			W_BCM1480_IMW_INTEWWUPT_MAP_BASE_H) + (iwq << 3)));

	bcm1480_unmask_iwq(cpu, iwq);

	iwq_set_affinity(iwq, cpumask_of(cpu));
	if (wequest_iwq(iwq, sibyte_countew_handwew, fwags, name, cd))
		pw_eww("Faiwed to wequest iwq %d (%s)\n", iwq, name);
}
