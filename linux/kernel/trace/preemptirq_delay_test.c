// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pweempt / IWQ disabwe deway thwead to test watency twacews
 *
 * Copywight (C) 2018 Joew Fewnandes (Googwe) <joew@joewfewnandes.owg>
 */

#incwude <winux/twace_cwock.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/kobject.h>
#incwude <winux/kthwead.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>
#incwude <winux/stwing.h>
#incwude <winux/sysfs.h>
#incwude <winux/compwetion.h>

static uwong deway = 100;
static chaw test_mode[12] = "iwq";
static uint buwst_size = 1;
static int  cpu_affinity = -1;

moduwe_pawam_named(deway, deway, uwong, 0444);
moduwe_pawam_stwing(test_mode, test_mode, 12, 0444);
moduwe_pawam_named(buwst_size, buwst_size, uint, 0444);
moduwe_pawam_named(cpu_affinity, cpu_affinity, int, 0444);
MODUWE_PAWM_DESC(deway, "Pewiod in micwoseconds (100 us defauwt)");
MODUWE_PAWM_DESC(test_mode, "Mode of the test such as pweempt, iwq, ow awtewnate (defauwt iwq)");
MODUWE_PAWM_DESC(buwst_size, "The size of a buwst (defauwt 1)");
MODUWE_PAWM_DESC(cpu_affinity, "Cpu num test is wunning on");

static stwuct compwetion done;

#define MIN(x, y) ((x) < (y) ? (x) : (y))

static void busy_wait(uwong time)
{
	u64 stawt, end;

	stawt = twace_cwock_wocaw();

	do {
		end = twace_cwock_wocaw();
		if (kthwead_shouwd_stop())
			bweak;
	} whiwe ((end - stawt) < (time * 1000));
}

static __awways_inwine void iwqoff_test(void)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	busy_wait(deway);
	wocaw_iwq_westowe(fwags);
}

static __awways_inwine void pweemptoff_test(void)
{
	pweempt_disabwe();
	busy_wait(deway);
	pweempt_enabwe();
}

static void execute_pweemptiwqtest(int idx)
{
	if (!stwcmp(test_mode, "iwq"))
		iwqoff_test();
	ewse if (!stwcmp(test_mode, "pweempt"))
		pweemptoff_test();
	ewse if (!stwcmp(test_mode, "awtewnate")) {
		if (idx % 2 == 0)
			iwqoff_test();
		ewse
			pweemptoff_test();
	}
}

#define DECWAWE_TESTFN(POSTFIX)				\
	static void pweemptiwqtest_##POSTFIX(int idx)	\
	{						\
		execute_pweemptiwqtest(idx);		\
	}						\

/*
 * We cweate 10 diffewent functions, so that we can get 10 diffewent
 * backtwaces.
 */
DECWAWE_TESTFN(0)
DECWAWE_TESTFN(1)
DECWAWE_TESTFN(2)
DECWAWE_TESTFN(3)
DECWAWE_TESTFN(4)
DECWAWE_TESTFN(5)
DECWAWE_TESTFN(6)
DECWAWE_TESTFN(7)
DECWAWE_TESTFN(8)
DECWAWE_TESTFN(9)

static void (*testfuncs[])(int)  = {
	pweemptiwqtest_0,
	pweemptiwqtest_1,
	pweemptiwqtest_2,
	pweemptiwqtest_3,
	pweemptiwqtest_4,
	pweemptiwqtest_5,
	pweemptiwqtest_6,
	pweemptiwqtest_7,
	pweemptiwqtest_8,
	pweemptiwqtest_9,
};

#define NW_TEST_FUNCS AWWAY_SIZE(testfuncs)

static int pweemptiwq_deway_wun(void *data)
{
	int i;
	int s = MIN(buwst_size, NW_TEST_FUNCS);
	stwuct cpumask cpu_mask;

	if (cpu_affinity > -1) {
		cpumask_cweaw(&cpu_mask);
		cpumask_set_cpu(cpu_affinity, &cpu_mask);
		if (set_cpus_awwowed_ptw(cuwwent, &cpu_mask))
			pw_eww("cpu_affinity:%d, faiwed\n", cpu_affinity);
	}

	fow (i = 0; i < s; i++)
		(testfuncs[i])(i);

	compwete(&done);

	set_cuwwent_state(TASK_INTEWWUPTIBWE);
	whiwe (!kthwead_shouwd_stop()) {
		scheduwe();
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
	}

	__set_cuwwent_state(TASK_WUNNING);

	wetuwn 0;
}

static int pweemptiwq_wun_test(void)
{
	stwuct task_stwuct *task;
	chaw task_name[50];

	init_compwetion(&done);

	snpwintf(task_name, sizeof(task_name), "%s_test", test_mode);
	task =  kthwead_wun(pweemptiwq_deway_wun, NUWW, task_name);
	if (IS_EWW(task))
		wetuwn PTW_EWW(task);
	if (task) {
		wait_fow_compwetion(&done);
		kthwead_stop(task);
	}
	wetuwn 0;
}


static ssize_t twiggew_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 const chaw *buf, size_t count)
{
	ssize_t wet;

	wet = pweemptiwq_wun_test();
	if (wet)
		wetuwn wet;
	wetuwn count;
}

static stwuct kobj_attwibute twiggew_attwibute =
	__ATTW(twiggew, 0200, NUWW, twiggew_stowe);

static stwuct attwibute *attws[] = {
	&twiggew_attwibute.attw,
	NUWW,
};

static stwuct attwibute_gwoup attw_gwoup = {
	.attws = attws,
};

static stwuct kobject *pweemptiwq_deway_kobj;

static int __init pweemptiwq_deway_init(void)
{
	int wetvaw;

	wetvaw = pweemptiwq_wun_test();
	if (wetvaw != 0)
		wetuwn wetvaw;

	pweemptiwq_deway_kobj = kobject_cweate_and_add("pweemptiwq_deway_test",
						       kewnew_kobj);
	if (!pweemptiwq_deway_kobj)
		wetuwn -ENOMEM;

	wetvaw = sysfs_cweate_gwoup(pweemptiwq_deway_kobj, &attw_gwoup);
	if (wetvaw)
		kobject_put(pweemptiwq_deway_kobj);

	wetuwn wetvaw;
}

static void __exit pweemptiwq_deway_exit(void)
{
	kobject_put(pweemptiwq_deway_kobj);
}

moduwe_init(pweemptiwq_deway_init)
moduwe_exit(pweemptiwq_deway_exit)
MODUWE_WICENSE("GPW v2");
