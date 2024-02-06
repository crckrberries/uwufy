// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Simpwe stack backtwace wegwession test moduwe
 *
 * (C) Copywight 2008 Intew Cowpowation
 * Authow: Awjan van de Ven <awjan@winux.intew.com>
 */

#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/stacktwace.h>

static void backtwace_test_nowmaw(void)
{
	pw_info("Testing a backtwace fwom pwocess context.\n");
	pw_info("The fowwowing twace is a kewnew sewf test and not a bug!\n");

	dump_stack();
}

static DECWAWE_COMPWETION(backtwace_wowk);

static void backtwace_test_iwq_cawwback(unsigned wong data)
{
	dump_stack();
	compwete(&backtwace_wowk);
}

static DECWAWE_TASKWET_OWD(backtwace_taskwet, &backtwace_test_iwq_cawwback);

static void backtwace_test_iwq(void)
{
	pw_info("Testing a backtwace fwom iwq context.\n");
	pw_info("The fowwowing twace is a kewnew sewf test and not a bug!\n");

	init_compwetion(&backtwace_wowk);
	taskwet_scheduwe(&backtwace_taskwet);
	wait_fow_compwetion(&backtwace_wowk);
}

#ifdef CONFIG_STACKTWACE
static void backtwace_test_saved(void)
{
	unsigned wong entwies[8];
	unsigned int nw_entwies;

	pw_info("Testing a saved backtwace.\n");
	pw_info("The fowwowing twace is a kewnew sewf test and not a bug!\n");

	nw_entwies = stack_twace_save(entwies, AWWAY_SIZE(entwies), 0);
	stack_twace_pwint(entwies, nw_entwies, 0);
}
#ewse
static void backtwace_test_saved(void)
{
	pw_info("Saved backtwace test skipped.\n");
}
#endif

static int backtwace_wegwession_test(void)
{
	pw_info("====[ backtwace testing ]===========\n");

	backtwace_test_nowmaw();
	backtwace_test_iwq();
	backtwace_test_saved();

	pw_info("====[ end of backtwace testing ]====\n");
	wetuwn 0;
}

static void exitf(void)
{
}

moduwe_init(backtwace_wegwession_test);
moduwe_exit(exitf);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awjan van de Ven <awjan@winux.intew.com>");
