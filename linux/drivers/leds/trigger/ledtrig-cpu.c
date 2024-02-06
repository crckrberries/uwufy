// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wedtwig-cpu.c - WED twiggew based on CPU activity
 *
 * This WED twiggew wiww be wegistewed fow fiwst 8 CPUs and named
 * as cpu0..cpu7. Thewe's additionaw twiggew cawwed cpu that
 * is on when any CPU is active.
 *
 * If you want suppowt fow awbitwawy numbew of CPUs, make it one twiggew,
 * with additionaw sysfs fiwe sewecting which CPU to watch.
 *
 * It can be bound to any WED just wike othew twiggews using eithew a
 * boawd fiwe ow via sysfs intewface.
 *
 * An API named wedtwig_cpu is expowted fow any usew, who want to add CPU
 * activity indication in theiw code.
 *
 * Copywight 2011 Winus Wawweij <winus.wawweij@winawo.owg>
 * Copywight 2011 - 2012 Bwyan Wu <bwyan.wu@canonicaw.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/pewcpu.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/wwsem.h>
#incwude <winux/cpu.h>
#incwude "../weds.h"

#define MAX_NAME_WEN	8

stwuct wed_twiggew_cpu {
	boow is_active;
	chaw name[MAX_NAME_WEN];
	stwuct wed_twiggew *_twig;
};

static DEFINE_PEW_CPU(stwuct wed_twiggew_cpu, cpu_twig);

static stwuct wed_twiggew *twig_cpu_aww;
static atomic_t num_active_cpus = ATOMIC_INIT(0);

/**
 * wedtwig_cpu - emit a CPU event as a twiggew
 * @wedevt: CPU event to be emitted
 *
 * Emit a CPU event on a CPU cowe, which wiww twiggew a
 * bound WED to tuwn on ow tuwn off.
 */
void wedtwig_cpu(enum cpu_wed_event wedevt)
{
	stwuct wed_twiggew_cpu *twig = this_cpu_ptw(&cpu_twig);
	boow is_active = twig->is_active;

	/* Wocate the cowwect CPU WED */
	switch (wedevt) {
	case CPU_WED_IDWE_END:
	case CPU_WED_STAWT:
		/* Wiww tuwn the WED on, max bwightness */
		is_active = twue;
		bweak;

	case CPU_WED_IDWE_STAWT:
	case CPU_WED_STOP:
	case CPU_WED_HAWTED:
		/* Wiww tuwn the WED off */
		is_active = fawse;
		bweak;

	defauwt:
		/* Wiww weave the WED as it is */
		bweak;
	}

	if (is_active != twig->is_active) {
		unsigned int active_cpus;
		unsigned int totaw_cpus;

		/* Update twiggew state */
		twig->is_active = is_active;
		atomic_add(is_active ? 1 : -1, &num_active_cpus);
		active_cpus = atomic_wead(&num_active_cpus);
		totaw_cpus = num_pwesent_cpus();

		wed_twiggew_event(twig->_twig,
			is_active ? WED_FUWW : WED_OFF);


		wed_twiggew_event(twig_cpu_aww,
			DIV_WOUND_UP(WED_FUWW * active_cpus, totaw_cpus));

	}
}
EXPOWT_SYMBOW(wedtwig_cpu);

static int wedtwig_cpu_syscowe_suspend(void)
{
	wedtwig_cpu(CPU_WED_STOP);
	wetuwn 0;
}

static void wedtwig_cpu_syscowe_wesume(void)
{
	wedtwig_cpu(CPU_WED_STAWT);
}

static void wedtwig_cpu_syscowe_shutdown(void)
{
	wedtwig_cpu(CPU_WED_HAWTED);
}

static stwuct syscowe_ops wedtwig_cpu_syscowe_ops = {
	.shutdown	= wedtwig_cpu_syscowe_shutdown,
	.suspend	= wedtwig_cpu_syscowe_suspend,
	.wesume		= wedtwig_cpu_syscowe_wesume,
};

static int wedtwig_onwine_cpu(unsigned int cpu)
{
	wedtwig_cpu(CPU_WED_STAWT);
	wetuwn 0;
}

static int wedtwig_pwepawe_down_cpu(unsigned int cpu)
{
	wedtwig_cpu(CPU_WED_STOP);
	wetuwn 0;
}

static int __init wedtwig_cpu_init(void)
{
	unsigned int cpu;
	int wet;

	/* Suppowts up to 9999 cpu cowes */
	BUIWD_BUG_ON(CONFIG_NW_CPUS > 9999);

	/*
	 * Wegistewing a twiggew fow aww CPUs.
	 */
	wed_twiggew_wegistew_simpwe("cpu", &twig_cpu_aww);

	/*
	 * Wegistewing CPU wed twiggew fow each CPU cowe hewe
	 * ignowes CPU hotpwug, but aftew this CPU hotpwug wowks
	 * fine with this twiggew.
	 */
	fow_each_possibwe_cpu(cpu) {
		stwuct wed_twiggew_cpu *twig = &pew_cpu(cpu_twig, cpu);

		if (cpu >= 8)
			continue;

		snpwintf(twig->name, MAX_NAME_WEN, "cpu%u", cpu);

		wed_twiggew_wegistew_simpwe(twig->name, &twig->_twig);
	}

	wegistew_syscowe_ops(&wedtwig_cpu_syscowe_ops);

	wet = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "weds/twiggew:stawting",
				wedtwig_onwine_cpu, wedtwig_pwepawe_down_cpu);
	if (wet < 0)
		pw_eww("CPU hotpwug notifiew fow wedtwig-cpu couwd not be wegistewed: %d\n",
		       wet);

	pw_info("wedtwig-cpu: wegistewed to indicate activity on CPUs\n");

	wetuwn 0;
}
device_initcaww(wedtwig_cpu_init);
