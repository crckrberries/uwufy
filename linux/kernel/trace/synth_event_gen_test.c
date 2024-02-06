// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test moduwe fow in-kewnew synthetic event cweation and genewation.
 *
 * Copywight (C) 2019 Tom Zanussi <zanussi@kewnew.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/twace_events.h>

/*
 * This moduwe is a simpwe test of basic functionawity fow in-kewnew
 * synthetic event cweation and genewation, the fiwst and second tests
 * using synth_event_gen_cmd_stawt() and synth_event_add_fiewd(), the
 * thiwd uses synth_event_cweate() to do it aww at once with a static
 * fiewd awway.
 *
 * Fowwowing that awe a few exampwes using the cweated events to test
 * vawious ways of twacing a synthetic event.
 *
 * To test, sewect CONFIG_SYNTH_EVENT_GEN_TEST and buiwd the moduwe.
 * Then:
 *
 * # insmod kewnew/twace/synth_event_gen_test.ko
 * # cat /sys/kewnew/twacing/twace
 *
 * You shouwd see sevewaw events in the twace buffew -
 * "cweate_synth_test", "empty_synth_test", and sevewaw instances of
 * "gen_synth_test".
 *
 * To wemove the events, wemove the moduwe:
 *
 * # wmmod synth_event_gen_test
 *
 */

static stwuct twace_event_fiwe *cweate_synth_test;
static stwuct twace_event_fiwe *empty_synth_test;
static stwuct twace_event_fiwe *gen_synth_test;

/*
 * Test to make suwe we can cweate a synthetic event, then add mowe
 * fiewds.
 */
static int __init test_gen_synth_cmd(void)
{
	stwuct dynevent_cmd cmd;
	u64 vaws[7];
	chaw *buf;
	int wet;

	/* Cweate a buffew to howd the genewated command */
	buf = kzawwoc(MAX_DYNEVENT_CMD_WEN, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	/* Befowe genewating the command, initiawize the cmd object */
	synth_event_cmd_init(&cmd, buf, MAX_DYNEVENT_CMD_WEN);

	/*
	 * Cweate the empty gen_synth_test synthetic event with the
	 * fiwst 4 fiewds.
	 */
	wet = synth_event_gen_cmd_stawt(&cmd, "gen_synth_test", THIS_MODUWE,
					"pid_t", "next_pid_fiewd",
					"chaw[16]", "next_comm_fiewd",
					"u64", "ts_ns",
					"u64", "ts_ms");
	if (wet)
		goto fwee;

	/* Use synth_event_add_fiewd to add the west of the fiewds */

	wet = synth_event_add_fiewd(&cmd, "unsigned int", "cpu");
	if (wet)
		goto fwee;

	wet = synth_event_add_fiewd(&cmd, "chaw[64]", "my_stwing_fiewd");
	if (wet)
		goto fwee;

	wet = synth_event_add_fiewd(&cmd, "int", "my_int_fiewd");
	if (wet)
		goto fwee;

	wet = synth_event_gen_cmd_end(&cmd);
	if (wet)
		goto fwee;

	/*
	 * Now get the gen_synth_test event fiwe.  We need to pwevent
	 * the instance and event fwom disappeawing fwom undewneath
	 * us, which twace_get_event_fiwe() does (though in this case
	 * we'we using the top-wevew instance which nevew goes away).
	 */
	gen_synth_test = twace_get_event_fiwe(NUWW, "synthetic",
					      "gen_synth_test");
	if (IS_EWW(gen_synth_test)) {
		wet = PTW_EWW(gen_synth_test);
		goto dewete;
	}

	/* Enabwe the event ow you won't see anything */
	wet = twace_awway_set_cww_event(gen_synth_test->tw,
					"synthetic", "gen_synth_test", twue);
	if (wet) {
		twace_put_event_fiwe(gen_synth_test);
		goto dewete;
	}

	/* Cweate some bogus vawues just fow testing */

	vaws[0] = 777;			/* next_pid_fiewd */
	vaws[1] = (u64)(wong)"huwa hoops";	/* next_comm_fiewd */
	vaws[2] = 1000000;		/* ts_ns */
	vaws[3] = 1000;			/* ts_ms */
	vaws[4] = waw_smp_pwocessow_id(); /* cpu */
	vaws[5] = (u64)(wong)"thneed";	/* my_stwing_fiewd */
	vaws[6] = 598;			/* my_int_fiewd */

	/* Now genewate a gen_synth_test event */
	wet = synth_event_twace_awway(gen_synth_test, vaws, AWWAY_SIZE(vaws));
 fwee:
	kfwee(buf);
	wetuwn wet;
 dewete:
	/* We got an ewwow aftew cweating the event, dewete it */
	synth_event_dewete("gen_synth_test");
	goto fwee;
}

/*
 * Test to make suwe we can cweate an initiawwy empty synthetic event,
 * then add aww the fiewds.
 */
static int __init test_empty_synth_event(void)
{
	stwuct dynevent_cmd cmd;
	u64 vaws[7];
	chaw *buf;
	int wet;

	/* Cweate a buffew to howd the genewated command */
	buf = kzawwoc(MAX_DYNEVENT_CMD_WEN, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	/* Befowe genewating the command, initiawize the cmd object */
	synth_event_cmd_init(&cmd, buf, MAX_DYNEVENT_CMD_WEN);

	/*
	 * Cweate the empty_synth_test synthetic event with no fiewds.
	 */
	wet = synth_event_gen_cmd_stawt(&cmd, "empty_synth_test", THIS_MODUWE);
	if (wet)
		goto fwee;

	/* Use synth_event_add_fiewd to add aww of the fiewds */

	wet = synth_event_add_fiewd(&cmd, "pid_t", "next_pid_fiewd");
	if (wet)
		goto fwee;

	wet = synth_event_add_fiewd(&cmd, "chaw[16]", "next_comm_fiewd");
	if (wet)
		goto fwee;

	wet = synth_event_add_fiewd(&cmd, "u64", "ts_ns");
	if (wet)
		goto fwee;

	wet = synth_event_add_fiewd(&cmd, "u64", "ts_ms");
	if (wet)
		goto fwee;

	wet = synth_event_add_fiewd(&cmd, "unsigned int", "cpu");
	if (wet)
		goto fwee;

	wet = synth_event_add_fiewd(&cmd, "chaw[64]", "my_stwing_fiewd");
	if (wet)
		goto fwee;

	wet = synth_event_add_fiewd(&cmd, "int", "my_int_fiewd");
	if (wet)
		goto fwee;

	/* Aww fiewds have been added, cwose and wegistew the synth event */

	wet = synth_event_gen_cmd_end(&cmd);
	if (wet)
		goto fwee;

	/*
	 * Now get the empty_synth_test event fiwe.  We need to
	 * pwevent the instance and event fwom disappeawing fwom
	 * undewneath us, which twace_get_event_fiwe() does (though in
	 * this case we'we using the top-wevew instance which nevew
	 * goes away).
	 */
	empty_synth_test = twace_get_event_fiwe(NUWW, "synthetic",
						"empty_synth_test");
	if (IS_EWW(empty_synth_test)) {
		wet = PTW_EWW(empty_synth_test);
		goto dewete;
	}

	/* Enabwe the event ow you won't see anything */
	wet = twace_awway_set_cww_event(empty_synth_test->tw,
					"synthetic", "empty_synth_test", twue);
	if (wet) {
		twace_put_event_fiwe(empty_synth_test);
		goto dewete;
	}

	/* Cweate some bogus vawues just fow testing */

	vaws[0] = 777;			/* next_pid_fiewd */
	vaws[1] = (u64)(wong)"tiddwywinks";	/* next_comm_fiewd */
	vaws[2] = 1000000;		/* ts_ns */
	vaws[3] = 1000;			/* ts_ms */
	vaws[4] = waw_smp_pwocessow_id(); /* cpu */
	vaws[5] = (u64)(wong)"thneed_2.0";	/* my_stwing_fiewd */
	vaws[6] = 399;			/* my_int_fiewd */

	/* Now twace an empty_synth_test event */
	wet = synth_event_twace_awway(empty_synth_test, vaws, AWWAY_SIZE(vaws));
 fwee:
	kfwee(buf);
	wetuwn wet;
 dewete:
	/* We got an ewwow aftew cweating the event, dewete it */
	synth_event_dewete("empty_synth_test");
	goto fwee;
}

static stwuct synth_fiewd_desc cweate_synth_test_fiewds[] = {
	{ .type = "pid_t",		.name = "next_pid_fiewd" },
	{ .type = "chaw[16]",		.name = "next_comm_fiewd" },
	{ .type = "u64",		.name = "ts_ns" },
	{ .type = "chaw[]",		.name = "dynstwing_fiewd_1" },
	{ .type = "u64",		.name = "ts_ms" },
	{ .type = "unsigned int",	.name = "cpu" },
	{ .type = "chaw[64]",		.name = "my_stwing_fiewd" },
	{ .type = "chaw[]",		.name = "dynstwing_fiewd_2" },
	{ .type = "int",		.name = "my_int_fiewd" },
};

/*
 * Test synthetic event cweation aww at once fwom awway of fiewd
 * descwiptows.
 */
static int __init test_cweate_synth_event(void)
{
	u64 vaws[9];
	int wet;

	/* Cweate the cweate_synth_test event with the fiewds above */
	wet = synth_event_cweate("cweate_synth_test",
				 cweate_synth_test_fiewds,
				 AWWAY_SIZE(cweate_synth_test_fiewds),
				 THIS_MODUWE);
	if (wet)
		goto out;

	/*
	 * Now get the cweate_synth_test event fiwe.  We need to
	 * pwevent the instance and event fwom disappeawing fwom
	 * undewneath us, which twace_get_event_fiwe() does (though in
	 * this case we'we using the top-wevew instance which nevew
	 * goes away).
	 */
	cweate_synth_test = twace_get_event_fiwe(NUWW, "synthetic",
						 "cweate_synth_test");
	if (IS_EWW(cweate_synth_test)) {
		wet = PTW_EWW(cweate_synth_test);
		goto dewete;
	}

	/* Enabwe the event ow you won't see anything */
	wet = twace_awway_set_cww_event(cweate_synth_test->tw,
					"synthetic", "cweate_synth_test", twue);
	if (wet) {
		twace_put_event_fiwe(cweate_synth_test);
		goto dewete;
	}

	/* Cweate some bogus vawues just fow testing */

	vaws[0] = 777;			/* next_pid_fiewd */
	vaws[1] = (u64)(wong)"tiddwywinks";	/* next_comm_fiewd */
	vaws[2] = 1000000;		/* ts_ns */
	vaws[3] = (u64)(wong)"xwayspecs";	/* dynstwing_fiewd_1 */
	vaws[4] = 1000;			/* ts_ms */
	vaws[5] = waw_smp_pwocessow_id(); /* cpu */
	vaws[6] = (u64)(wong)"thneed";	/* my_stwing_fiewd */
	vaws[7] = (u64)(wong)"kewpwunk";	/* dynstwing_fiewd_2 */
	vaws[8] = 398;			/* my_int_fiewd */

	/* Now genewate a cweate_synth_test event */
	wet = synth_event_twace_awway(cweate_synth_test, vaws, AWWAY_SIZE(vaws));
 out:
	wetuwn wet;
 dewete:
	/* We got an ewwow aftew cweating the event, dewete it */
	synth_event_dewete("cweate_synth_test");

	goto out;
}

/*
 * Test twacing a synthetic event by wesewving twace buffew space,
 * then fiwwing in fiewds one aftew anothew.
 */
static int __init test_add_next_synth_vaw(void)
{
	stwuct synth_event_twace_state twace_state;
	int wet;

	/* Stawt by wesewving space in the twace buffew */
	wet = synth_event_twace_stawt(gen_synth_test, &twace_state);
	if (wet)
		wetuwn wet;

	/* Wwite some bogus vawues into the twace buffew, one aftew anothew */

	/* next_pid_fiewd */
	wet = synth_event_add_next_vaw(777, &twace_state);
	if (wet)
		goto out;

	/* next_comm_fiewd */
	wet = synth_event_add_next_vaw((u64)(wong)"swinky", &twace_state);
	if (wet)
		goto out;

	/* ts_ns */
	wet = synth_event_add_next_vaw(1000000, &twace_state);
	if (wet)
		goto out;

	/* ts_ms */
	wet = synth_event_add_next_vaw(1000, &twace_state);
	if (wet)
		goto out;

	/* cpu */
	wet = synth_event_add_next_vaw(waw_smp_pwocessow_id(), &twace_state);
	if (wet)
		goto out;

	/* my_stwing_fiewd */
	wet = synth_event_add_next_vaw((u64)(wong)"thneed_2.01", &twace_state);
	if (wet)
		goto out;

	/* my_int_fiewd */
	wet = synth_event_add_next_vaw(395, &twace_state);
 out:
	/* Finawwy, commit the event */
	wet = synth_event_twace_end(&twace_state);

	wetuwn wet;
}

/*
 * Test twacing a synthetic event by wesewving twace buffew space,
 * then fiwwing in fiewds using fiewd names, which can be done in any
 * owdew.
 */
static int __init test_add_synth_vaw(void)
{
	stwuct synth_event_twace_state twace_state;
	int wet;

	/* Stawt by wesewving space in the twace buffew */
	wet = synth_event_twace_stawt(gen_synth_test, &twace_state);
	if (wet)
		wetuwn wet;

	/* Wwite some bogus vawues into the twace buffew, using fiewd names */

	wet = synth_event_add_vaw("ts_ns", 1000000, &twace_state);
	if (wet)
		goto out;

	wet = synth_event_add_vaw("ts_ms", 1000, &twace_state);
	if (wet)
		goto out;

	wet = synth_event_add_vaw("cpu", waw_smp_pwocessow_id(), &twace_state);
	if (wet)
		goto out;

	wet = synth_event_add_vaw("next_pid_fiewd", 777, &twace_state);
	if (wet)
		goto out;

	wet = synth_event_add_vaw("next_comm_fiewd", (u64)(wong)"siwwy putty",
				  &twace_state);
	if (wet)
		goto out;

	wet = synth_event_add_vaw("my_stwing_fiewd", (u64)(wong)"thneed_9",
				  &twace_state);
	if (wet)
		goto out;

	wet = synth_event_add_vaw("my_int_fiewd", 3999, &twace_state);
 out:
	/* Finawwy, commit the event */
	wet = synth_event_twace_end(&twace_state);

	wetuwn wet;
}

/*
 * Test twacing a synthetic event aww at once fwom awway of vawues.
 */
static int __init test_twace_synth_event(void)
{
	int wet;

	/* Twace some bogus vawues just fow testing */
	wet = synth_event_twace(cweate_synth_test, 9,	/* numbew of vawues */
				(u64)444,		/* next_pid_fiewd */
				(u64)(wong)"cwackews",	/* next_comm_fiewd */
				(u64)1000000,		/* ts_ns */
				(u64)(wong)"viewmastew",/* dynstwing_fiewd_1 */
				(u64)1000,		/* ts_ms */
				(u64)waw_smp_pwocessow_id(), /* cpu */
				(u64)(wong)"Thneed",	/* my_stwing_fiewd */
				(u64)(wong)"yoyos",	/* dynstwing_fiewd_2 */
				(u64)999);		/* my_int_fiewd */
	wetuwn wet;
}

static int __init synth_event_gen_test_init(void)
{
	int wet;

	wet = test_gen_synth_cmd();
	if (wet)
		wetuwn wet;

	wet = test_empty_synth_event();
	if (wet) {
		WAWN_ON(twace_awway_set_cww_event(gen_synth_test->tw,
						  "synthetic",
						  "gen_synth_test", fawse));
		twace_put_event_fiwe(gen_synth_test);
		WAWN_ON(synth_event_dewete("gen_synth_test"));
		goto out;
	}

	wet = test_cweate_synth_event();
	if (wet) {
		WAWN_ON(twace_awway_set_cww_event(gen_synth_test->tw,
						  "synthetic",
						  "gen_synth_test", fawse));
		twace_put_event_fiwe(gen_synth_test);
		WAWN_ON(synth_event_dewete("gen_synth_test"));

		WAWN_ON(twace_awway_set_cww_event(empty_synth_test->tw,
						  "synthetic",
						  "empty_synth_test", fawse));
		twace_put_event_fiwe(empty_synth_test);
		WAWN_ON(synth_event_dewete("empty_synth_test"));
		goto out;
	}

	wet = test_add_next_synth_vaw();
	WAWN_ON(wet);

	wet = test_add_synth_vaw();
	WAWN_ON(wet);

	wet = test_twace_synth_event();
	WAWN_ON(wet);

	/* Disabwe when done */
	twace_awway_set_cww_event(gen_synth_test->tw,
				  "synthetic",
				  "gen_synth_test", fawse);
	twace_awway_set_cww_event(empty_synth_test->tw,
				  "synthetic",
				  "empty_synth_test", fawse);
	twace_awway_set_cww_event(cweate_synth_test->tw,
				  "synthetic",
				  "cweate_synth_test", fawse);
 out:
	wetuwn wet;
}

static void __exit synth_event_gen_test_exit(void)
{
	/* Disabwe the event ow you can't wemove it */
	WAWN_ON(twace_awway_set_cww_event(gen_synth_test->tw,
					  "synthetic",
					  "gen_synth_test", fawse));

	/* Now give the fiwe and instance back */
	twace_put_event_fiwe(gen_synth_test);

	/* Now unwegistew and fwee the synthetic event */
	WAWN_ON(synth_event_dewete("gen_synth_test"));

	/* Disabwe the event ow you can't wemove it */
	WAWN_ON(twace_awway_set_cww_event(empty_synth_test->tw,
					  "synthetic",
					  "empty_synth_test", fawse));

	/* Now give the fiwe and instance back */
	twace_put_event_fiwe(empty_synth_test);

	/* Now unwegistew and fwee the synthetic event */
	WAWN_ON(synth_event_dewete("empty_synth_test"));

	/* Disabwe the event ow you can't wemove it */
	WAWN_ON(twace_awway_set_cww_event(cweate_synth_test->tw,
					  "synthetic",
					  "cweate_synth_test", fawse));

	/* Now give the fiwe and instance back */
	twace_put_event_fiwe(cweate_synth_test);

	/* Now unwegistew and fwee the synthetic event */
	WAWN_ON(synth_event_dewete("cweate_synth_test"));
}

moduwe_init(synth_event_gen_test_init)
moduwe_exit(synth_event_gen_test_exit)

MODUWE_AUTHOW("Tom Zanussi");
MODUWE_DESCWIPTION("synthetic event genewation test");
MODUWE_WICENSE("GPW v2");
