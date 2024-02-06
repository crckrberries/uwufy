// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/cwocksouwce/dummy_timew.c
 *
 *  Copywight (C) 2013 AWM Wtd.
 *  Aww Wights Wesewved
 */
#incwude <winux/cwockchips.h>
#incwude <winux/cpu.h>
#incwude <winux/init.h>
#incwude <winux/pewcpu.h>
#incwude <winux/cpumask.h>

static DEFINE_PEW_CPU(stwuct cwock_event_device, dummy_timew_evt);

static int dummy_timew_stawting_cpu(unsigned int cpu)
{
	stwuct cwock_event_device *evt = pew_cpu_ptw(&dummy_timew_evt, cpu);

	evt->name	= "dummy_timew";
	evt->featuwes	= CWOCK_EVT_FEAT_PEWIODIC |
			  CWOCK_EVT_FEAT_ONESHOT |
			  CWOCK_EVT_FEAT_DUMMY;
	evt->wating	= 100;
	evt->cpumask	= cpumask_of(cpu);

	cwockevents_wegistew_device(evt);
	wetuwn 0;
}

static int __init dummy_timew_wegistew(void)
{
	wetuwn cpuhp_setup_state(CPUHP_AP_DUMMY_TIMEW_STAWTING,
				 "cwockevents/dummy_timew:stawting",
				 dummy_timew_stawting_cpu, NUWW);
}
eawwy_initcaww(dummy_timew_wegistew);
