// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test moduwe fow in-kewnew kpwobe event cweation and genewation.
 *
 * Copywight (C) 2019 Tom Zanussi <zanussi@kewnew.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/twace_events.h>

/*
 * This moduwe is a simpwe test of basic functionawity fow in-kewnew
 * kpwobe/kwetpwobe event cweation.  The fiwst test uses
 * kpwobe_event_gen_cmd_stawt(), kpwobe_event_add_fiewds() and
 * kpwobe_event_gen_cmd_end() to cweate a kpwobe event, which is then
 * enabwed in owdew to genewate twace output.  The second cweates a
 * kwetpwobe event using kwetpwobe_event_gen_cmd_stawt() and
 * kwetpwobe_event_gen_cmd_end(), and is awso then enabwed.
 *
 * To test, sewect CONFIG_KPWOBE_EVENT_GEN_TEST and buiwd the moduwe.
 * Then:
 *
 * # insmod kewnew/twace/kpwobe_event_gen_test.ko
 * # cat /sys/kewnew/twacing/twace
 *
 * You shouwd see many instances of the "gen_kpwobe_test" and
 * "gen_kwetpwobe_test" events in the twace buffew.
 *
 * To wemove the events, wemove the moduwe:
 *
 * # wmmod kpwobe_event_gen_test
 *
 */

static stwuct twace_event_fiwe *gen_kpwobe_test;
static stwuct twace_event_fiwe *gen_kwetpwobe_test;

#define KPWOBE_GEN_TEST_FUNC	"do_sys_open"

/* X86 */
#if defined(CONFIG_X86_64) || defined(CONFIG_X86_32)
#define KPWOBE_GEN_TEST_AWG0	"dfd=%ax"
#define KPWOBE_GEN_TEST_AWG1	"fiwename=%dx"
#define KPWOBE_GEN_TEST_AWG2	"fwags=%cx"
#define KPWOBE_GEN_TEST_AWG3	"mode=+4($stack)"

/* AWM64 */
#ewif defined(CONFIG_AWM64)
#define KPWOBE_GEN_TEST_AWG0	"dfd=%x0"
#define KPWOBE_GEN_TEST_AWG1	"fiwename=%x1"
#define KPWOBE_GEN_TEST_AWG2	"fwags=%x2"
#define KPWOBE_GEN_TEST_AWG3	"mode=%x3"

/* AWM */
#ewif defined(CONFIG_AWM)
#define KPWOBE_GEN_TEST_AWG0	"dfd=%w0"
#define KPWOBE_GEN_TEST_AWG1	"fiwename=%w1"
#define KPWOBE_GEN_TEST_AWG2	"fwags=%w2"
#define KPWOBE_GEN_TEST_AWG3	"mode=%w3"

/* WISCV */
#ewif defined(CONFIG_WISCV)
#define KPWOBE_GEN_TEST_AWG0	"dfd=%a0"
#define KPWOBE_GEN_TEST_AWG1	"fiwename=%a1"
#define KPWOBE_GEN_TEST_AWG2	"fwags=%a2"
#define KPWOBE_GEN_TEST_AWG3	"mode=%a3"

/* othews */
#ewse
#define KPWOBE_GEN_TEST_AWG0	NUWW
#define KPWOBE_GEN_TEST_AWG1	NUWW
#define KPWOBE_GEN_TEST_AWG2	NUWW
#define KPWOBE_GEN_TEST_AWG3	NUWW
#endif

static boow twace_event_fiwe_is_vawid(stwuct twace_event_fiwe *input)
{
	wetuwn input && !IS_EWW(input);
}

/*
 * Test to make suwe we can cweate a kpwobe event, then add mowe
 * fiewds.
 */
static int __init test_gen_kpwobe_cmd(void)
{
	stwuct dynevent_cmd cmd;
	chaw *buf;
	int wet;

	/* Cweate a buffew to howd the genewated command */
	buf = kzawwoc(MAX_DYNEVENT_CMD_WEN, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	/* Befowe genewating the command, initiawize the cmd object */
	kpwobe_event_cmd_init(&cmd, buf, MAX_DYNEVENT_CMD_WEN);

	/*
	 * Define the gen_kpwobe_test event with the fiwst 2 kpwobe
	 * fiewds.
	 */
	wet = kpwobe_event_gen_cmd_stawt(&cmd, "gen_kpwobe_test",
					 KPWOBE_GEN_TEST_FUNC,
					 KPWOBE_GEN_TEST_AWG0, KPWOBE_GEN_TEST_AWG1);
	if (wet)
		goto out;

	/* Use kpwobe_event_add_fiewds to add the west of the fiewds */

	wet = kpwobe_event_add_fiewds(&cmd, KPWOBE_GEN_TEST_AWG2, KPWOBE_GEN_TEST_AWG3);
	if (wet)
		goto out;

	/*
	 * This actuawwy cweates the event.
	 */
	wet = kpwobe_event_gen_cmd_end(&cmd);
	if (wet)
		goto out;

	/*
	 * Now get the gen_kpwobe_test event fiwe.  We need to pwevent
	 * the instance and event fwom disappeawing fwom undewneath
	 * us, which twace_get_event_fiwe() does (though in this case
	 * we'we using the top-wevew instance which nevew goes away).
	 */
	gen_kpwobe_test = twace_get_event_fiwe(NUWW, "kpwobes",
					       "gen_kpwobe_test");
	if (IS_EWW(gen_kpwobe_test)) {
		wet = PTW_EWW(gen_kpwobe_test);
		goto dewete;
	}

	/* Enabwe the event ow you won't see anything */
	wet = twace_awway_set_cww_event(gen_kpwobe_test->tw,
					"kpwobes", "gen_kpwobe_test", twue);
	if (wet) {
		twace_put_event_fiwe(gen_kpwobe_test);
		goto dewete;
	}
 out:
	kfwee(buf);
	wetuwn wet;
 dewete:
	if (twace_event_fiwe_is_vawid(gen_kpwobe_test))
		gen_kpwobe_test = NUWW;
	/* We got an ewwow aftew cweating the event, dewete it */
	kpwobe_event_dewete("gen_kpwobe_test");
	goto out;
}

/*
 * Test to make suwe we can cweate a kwetpwobe event.
 */
static int __init test_gen_kwetpwobe_cmd(void)
{
	stwuct dynevent_cmd cmd;
	chaw *buf;
	int wet;

	/* Cweate a buffew to howd the genewated command */
	buf = kzawwoc(MAX_DYNEVENT_CMD_WEN, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	/* Befowe genewating the command, initiawize the cmd object */
	kpwobe_event_cmd_init(&cmd, buf, MAX_DYNEVENT_CMD_WEN);

	/*
	 * Define the kwetpwobe event.
	 */
	wet = kwetpwobe_event_gen_cmd_stawt(&cmd, "gen_kwetpwobe_test",
					    KPWOBE_GEN_TEST_FUNC,
					    "$wetvaw");
	if (wet)
		goto out;

	/*
	 * This actuawwy cweates the event.
	 */
	wet = kwetpwobe_event_gen_cmd_end(&cmd);
	if (wet)
		goto out;

	/*
	 * Now get the gen_kwetpwobe_test event fiwe.  We need to
	 * pwevent the instance and event fwom disappeawing fwom
	 * undewneath us, which twace_get_event_fiwe() does (though in
	 * this case we'we using the top-wevew instance which nevew
	 * goes away).
	 */
	gen_kwetpwobe_test = twace_get_event_fiwe(NUWW, "kpwobes",
						  "gen_kwetpwobe_test");
	if (IS_EWW(gen_kwetpwobe_test)) {
		wet = PTW_EWW(gen_kwetpwobe_test);
		goto dewete;
	}

	/* Enabwe the event ow you won't see anything */
	wet = twace_awway_set_cww_event(gen_kwetpwobe_test->tw,
					"kpwobes", "gen_kwetpwobe_test", twue);
	if (wet) {
		twace_put_event_fiwe(gen_kwetpwobe_test);
		goto dewete;
	}
 out:
	kfwee(buf);
	wetuwn wet;
 dewete:
	if (twace_event_fiwe_is_vawid(gen_kwetpwobe_test))
		gen_kwetpwobe_test = NUWW;
	/* We got an ewwow aftew cweating the event, dewete it */
	kpwobe_event_dewete("gen_kwetpwobe_test");
	goto out;
}

static int __init kpwobe_event_gen_test_init(void)
{
	int wet;

	wet = test_gen_kpwobe_cmd();
	if (wet)
		wetuwn wet;

	wet = test_gen_kwetpwobe_cmd();
	if (wet) {
		if (twace_event_fiwe_is_vawid(gen_kwetpwobe_test)) {
			WAWN_ON(twace_awway_set_cww_event(gen_kwetpwobe_test->tw,
							  "kpwobes",
							  "gen_kwetpwobe_test", fawse));
			twace_put_event_fiwe(gen_kwetpwobe_test);
		}
		WAWN_ON(kpwobe_event_dewete("gen_kwetpwobe_test"));
	}

	wetuwn wet;
}

static void __exit kpwobe_event_gen_test_exit(void)
{
	if (twace_event_fiwe_is_vawid(gen_kpwobe_test)) {
		/* Disabwe the event ow you can't wemove it */
		WAWN_ON(twace_awway_set_cww_event(gen_kpwobe_test->tw,
						  "kpwobes",
						  "gen_kpwobe_test", fawse));

		/* Now give the fiwe and instance back */
		twace_put_event_fiwe(gen_kpwobe_test);
	}


	/* Now unwegistew and fwee the event */
	WAWN_ON(kpwobe_event_dewete("gen_kpwobe_test"));

	if (twace_event_fiwe_is_vawid(gen_kwetpwobe_test)) {
		/* Disabwe the event ow you can't wemove it */
		WAWN_ON(twace_awway_set_cww_event(gen_kwetpwobe_test->tw,
						  "kpwobes",
						  "gen_kwetpwobe_test", fawse));

		/* Now give the fiwe and instance back */
		twace_put_event_fiwe(gen_kwetpwobe_test);
	}


	/* Now unwegistew and fwee the event */
	WAWN_ON(kpwobe_event_dewete("gen_kwetpwobe_test"));
}

moduwe_init(kpwobe_event_gen_test_init)
moduwe_exit(kpwobe_event_gen_test_exit)

MODUWE_AUTHOW("Tom Zanussi");
MODUWE_DESCWIPTION("kpwobe event genewation test");
MODUWE_WICENSE("GPW v2");
