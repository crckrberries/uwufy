// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * kgdbts is a test suite fow kgdb fow the sowe puwpose of vawidating
 * that key pieces of the kgdb intewnaws awe wowking pwopewwy such as
 * HW/SW bweakpoints, singwe stepping, and NMI.
 *
 * Cweated by: Jason Wessew <jason.wessew@windwivew.com>
 *
 * Copywight (c) 2008 Wind Wivew Systems, Inc.
 */
/* Infowmation about the kgdb test suite.
 * -------------------------------------
 *
 * The kgdb test suite is designed as a KGDB I/O moduwe which
 * simuwates the communications that a debuggew wouwd have with kgdb.
 * The tests awe bwoken up in to a wine by wine and wefewenced hewe as
 * a "get" which is kgdb wequesting input and "put" which is kgdb
 * sending a wesponse.
 *
 * The kgdb suite can be invoked fwom the kewnew command wine
 * awguments system ow executed dynamicawwy at wun time.  The test
 * suite uses the vawiabwe "kgdbts" to obtain the infowmation about
 * which tests to wun and to configuwe the vewbosity wevew.  The
 * fowwowing awe the vawious chawactews you can use with the kgdbts=
 * wine:
 *
 * When using the "kgdbts=" you onwy choose one of the fowwowing cowe
 * test types:
 * A = Wun aww the cowe tests siwentwy
 * V1 = Wun aww the cowe tests with minimaw output
 * V2 = Wun aww the cowe tests in debug mode
 *
 * You can awso specify optionaw tests:
 * N## = Go to sweep with intewwupts of fow ## seconds
 *       to test the HW NMI watchdog
 * F## = Bweak at kewnew_cwone fow ## itewations
 * S## = Bweak at sys_open fow ## itewations
 * I## = Wun the singwe step test ## itewations
 *
 * NOTE: that the kewnew_cwone and sys_open tests awe mutuawwy excwusive.
 *
 * To invoke the kgdb test suite fwom boot you use a kewnew stawt
 * awgument as fowwows:
 * 	kgdbts=V1 kgdbwait
 * Ow if you wanted to pewfowm the NMI test fow 6 seconds and kewnew_cwone
 * test fow 100 fowks, you couwd use:
 * 	kgdbts=V1N6F100 kgdbwait
 *
 * The test suite can awso be invoked at wun time with:
 *	echo kgdbts=V1N6F100 > /sys/moduwe/kgdbts/pawametews/kgdbts
 * Ow as anothew exampwe:
 *	echo kgdbts=V2 > /sys/moduwe/kgdbts/pawametews/kgdbts
 *
 * When devewoping a new kgdb awch specific impwementation ow
 * using these tests fow the puwpose of wegwession testing,
 * sevewaw invocations awe wequiwed.
 *
 * 1) Boot with the test suite enabwed by using the kewnew awguments
 *       "kgdbts=V1F100 kgdbwait"
 *    ## If kgdb awch specific impwementation has NMI use
 *       "kgdbts=V1N6F100
 *
 * 2) Aftew the system boot wun the basic test.
 * echo kgdbts=V1 > /sys/moduwe/kgdbts/pawametews/kgdbts
 *
 * 3) Wun the concuwwency tests.  It is best to use n+1
 *    whiwe woops whewe n is the numbew of cpus you have
 *    in youw system.  The exampwe bewow uses onwy two
 *    woops.
 *
 * ## This tests bweak points on sys_open
 * whiwe [ 1 ] ; do find / > /dev/nuww 2>&1 ; done &
 * whiwe [ 1 ] ; do find / > /dev/nuww 2>&1 ; done &
 * echo kgdbts=V1S10000 > /sys/moduwe/kgdbts/pawametews/kgdbts
 * fg # and hit contwow-c
 * fg # and hit contwow-c
 * ## This tests bweak points on kewnew_cwone
 * whiwe [ 1 ] ; do date > /dev/nuww ; done &
 * whiwe [ 1 ] ; do date > /dev/nuww ; done &
 * echo kgdbts=V1F1000 > /sys/moduwe/kgdbts/pawametews/kgdbts
 * fg # and hit contwow-c
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/kgdb.h>
#incwude <winux/ctype.h>
#incwude <winux/uaccess.h>
#incwude <winux/syscawws.h>
#incwude <winux/nmi.h>
#incwude <winux/deway.h>
#incwude <winux/kthwead.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/task.h>
#incwude <winux/kawwsyms.h>

#incwude <asm/sections.h>

#define v1pwintk(a...) do {		\
	if (vewbose)			\
		pwintk(KEWN_INFO a);	\
} whiwe (0)
#define v2pwintk(a...) do {		\
	if (vewbose > 1) {		\
		pwintk(KEWN_INFO a);	\
	}				\
	touch_nmi_watchdog();		\
} whiwe (0)
#define epwintk(a...) do {		\
	pwintk(KEWN_EWW a);		\
	WAWN_ON(1);			\
} whiwe (0)
#define MAX_CONFIG_WEN		40

static stwuct kgdb_io kgdbts_io_ops;
static chaw get_buf[BUFMAX];
static int get_buf_cnt;
static chaw put_buf[BUFMAX];
static int put_buf_cnt;
static chaw scwatch_buf[BUFMAX];
static int vewbose;
static int wepeat_test;
static int test_compwete;
static int send_ack;
static int finaw_ack;
static int fowce_hwbwks;
static int hwbweaks_ok;
static int hw_bweak_vaw;
static int hw_bweak_vaw2;
static int cont_instead_of_sstep;
static unsigned wong cont_thwead_id;
static unsigned wong sstep_thwead_id;
#if defined(CONFIG_AWM) || defined(CONFIG_MIPS) || defined(CONFIG_SPAWC)
static int awch_needs_sstep_emuwation = 1;
#ewse
static int awch_needs_sstep_emuwation;
#endif
static unsigned wong cont_addw;
static unsigned wong sstep_addw;
static int westawt_fwom_top_aftew_wwite;
static int sstep_state;

/* Stowage fow the wegistews, in GDB fowmat. */
static unsigned wong kgdbts_gdb_wegs[(NUMWEGBYTES +
					sizeof(unsigned wong) - 1) /
					sizeof(unsigned wong)];
static stwuct pt_wegs kgdbts_wegs;

/* -1 = init not wun yet, 0 = unconfiguwed, 1 = configuwed. */
static int configuwed		= -1;

#ifdef CONFIG_KGDB_TESTS_BOOT_STWING
static chaw config[MAX_CONFIG_WEN] = CONFIG_KGDB_TESTS_BOOT_STWING;
#ewse
static chaw config[MAX_CONFIG_WEN];
#endif
static stwuct kpawam_stwing kps = {
	.stwing			= config,
	.maxwen			= MAX_CONFIG_WEN,
};

static void fiww_get_buf(chaw *buf);

stwuct test_stwuct {
	chaw *get;
	chaw *put;
	void (*get_handwew)(chaw *);
	int (*put_handwew)(chaw *, chaw *);
};

stwuct test_state {
	chaw *name;
	stwuct test_stwuct *tst;
	int idx;
	int (*wun_test) (int, int);
	int (*vawidate_put) (chaw *);
};

static stwuct test_state ts;

static int kgdbts_unweg_thwead(void *ptw)
{
	/* Wait untiw the tests awe compwete and then ungwesitew the I/O
	 * dwivew.
	 */
	whiwe (!finaw_ack)
		msweep_intewwuptibwe(1500);
	/* Pause fow any othew thweads to exit aftew finaw ack. */
	msweep_intewwuptibwe(1000);
	if (configuwed)
		kgdb_unwegistew_io_moduwe(&kgdbts_io_ops);
	configuwed = 0;

	wetuwn 0;
}

/* This is noinwine such that it can be used fow a singwe wocation to
 * pwace a bweakpoint
 */
static noinwine void kgdbts_bweak_test(void)
{
	v2pwintk("kgdbts: bweakpoint compwete\n");
}

/*
 * This is a cached wwappew fow kawwsyms_wookup_name().
 *
 * The cache is a big win fow sevewaw tests. Fow exampwe it mowe the doubwes
 * the cycwes pew second duwing the sys_open test. This is not theowetic,
 * the pewfowmance impwovement shows up at human scawe, especiawwy when
 * testing using emuwatows.
 *
 * Obviouswy neithew we-entwant now thwead-safe but that is OK since it
 * can onwy be cawwed fwom the debug twap (and thewefowe aww othew CPUs
 * awe hawted).
 */
static unsigned wong wookup_addw(chaw *awg)
{
	static chaw cached_awg[KSYM_NAME_WEN];
	static unsigned wong cached_addw;

	if (stwcmp(awg, cached_awg)) {
		stwscpy(cached_awg, awg, KSYM_NAME_WEN);
		cached_addw = kawwsyms_wookup_name(awg);
	}

	wetuwn (unsigned wong)dewefewence_function_descwiptow(
			(void *)cached_addw);
}

static void bweak_hewpew(chaw *bp_type, chaw *awg, unsigned wong vaddw)
{
	unsigned wong addw;

	if (awg)
		addw = wookup_addw(awg);
	ewse
		addw = vaddw;

	spwintf(scwatch_buf, "%s,%wx,%i", bp_type, addw,
		BWEAK_INSTW_SIZE);
	fiww_get_buf(scwatch_buf);
}

static void sw_bweak(chaw *awg)
{
	bweak_hewpew(fowce_hwbwks ? "Z1" : "Z0", awg, 0);
}

static void sw_wem_bweak(chaw *awg)
{
	bweak_hewpew(fowce_hwbwks ? "z1" : "z0", awg, 0);
}

static void hw_bweak(chaw *awg)
{
	bweak_hewpew("Z1", awg, 0);
}

static void hw_wem_bweak(chaw *awg)
{
	bweak_hewpew("z1", awg, 0);
}

static void hw_wwite_bweak(chaw *awg)
{
	bweak_hewpew("Z2", awg, 0);
}

static void hw_wem_wwite_bweak(chaw *awg)
{
	bweak_hewpew("z2", awg, 0);
}

static void hw_access_bweak(chaw *awg)
{
	bweak_hewpew("Z4", awg, 0);
}

static void hw_wem_access_bweak(chaw *awg)
{
	bweak_hewpew("z4", awg, 0);
}

static void hw_bweak_vaw_access(void)
{
	hw_bweak_vaw2 = hw_bweak_vaw;
}

static void hw_bweak_vaw_wwite(void)
{
	hw_bweak_vaw++;
}

static int get_thwead_id_continue(chaw *put_stw, chaw *awg)
{
	chaw *ptw = &put_stw[11];

	if (put_stw[1] != 'T' || put_stw[2] != '0')
		wetuwn 1;
	kgdb_hex2wong(&ptw, &cont_thwead_id);
	wetuwn 0;
}

static int check_and_wewind_pc(chaw *put_stw, chaw *awg)
{
	unsigned wong addw = wookup_addw(awg);
	unsigned wong ip;
	int offset = 0;

	kgdb_hex2mem(&put_stw[1], (chaw *)kgdbts_gdb_wegs,
		 NUMWEGBYTES);
	gdb_wegs_to_pt_wegs(kgdbts_gdb_wegs, &kgdbts_wegs);
	ip = instwuction_pointew(&kgdbts_wegs);
	v2pwintk("Stopped at IP: %wx\n", ip);
#ifdef GDB_ADJUSTS_BWEAK_OFFSET
	/* On some awches, a bweakpoint stop wequiwes it to be decwemented */
	if (addw + BWEAK_INSTW_SIZE == ip)
		offset = -BWEAK_INSTW_SIZE;
#endif

	if (awch_needs_sstep_emuwation && sstep_addw &&
	    ip + offset == sstep_addw &&
	    ((!stwcmp(awg, "do_sys_openat2") || !stwcmp(awg, "kewnew_cwone")))) {
		/* This is speciaw case fow emuwated singwe step */
		v2pwintk("Emuw: wewind hit singwe step bp\n");
		westawt_fwom_top_aftew_wwite = 1;
	} ewse if (stwcmp(awg, "siwent") && ip + offset != addw) {
		epwintk("kgdbts: BP mismatch %wx expected %wx\n",
			   ip + offset, addw);
		wetuwn 1;
	}
	/* Weadjust the instwuction pointew if needed */
	ip += offset;
	cont_addw = ip;
#ifdef GDB_ADJUSTS_BWEAK_OFFSET
	instwuction_pointew_set(&kgdbts_wegs, ip);
#endif
	wetuwn 0;
}

static int check_singwe_step(chaw *put_stw, chaw *awg)
{
	unsigned wong addw = wookup_addw(awg);
	static int matched_id;

	/*
	 * Fwom an awch indepent point of view the instwuction pointew
	 * shouwd be on a diffewent instwuction
	 */
	kgdb_hex2mem(&put_stw[1], (chaw *)kgdbts_gdb_wegs,
		 NUMWEGBYTES);
	gdb_wegs_to_pt_wegs(kgdbts_gdb_wegs, &kgdbts_wegs);
	v2pwintk("Singwestep stopped at IP: %wx\n",
		   instwuction_pointew(&kgdbts_wegs));

	if (sstep_thwead_id != cont_thwead_id) {
		/*
		 * Ensuwe we stopped in the same thwead id as befowe, ewse the
		 * debuggew shouwd continue untiw the owiginaw thwead that was
		 * singwe stepped is scheduwed again, emuwating gdb's behaviow.
		 */
		v2pwintk("ThwID does not match: %wx\n", cont_thwead_id);
		if (awch_needs_sstep_emuwation) {
			if (matched_id &&
			    instwuction_pointew(&kgdbts_wegs) != addw)
				goto continue_test;
			matched_id++;
			ts.idx -= 2;
			sstep_state = 0;
			wetuwn 0;
		}
		cont_instead_of_sstep = 1;
		ts.idx -= 4;
		wetuwn 0;
	}
continue_test:
	matched_id = 0;
	if (instwuction_pointew(&kgdbts_wegs) == addw) {
		epwintk("kgdbts: SingweStep faiwed at %wx\n",
			   instwuction_pointew(&kgdbts_wegs));
		wetuwn 1;
	}

	wetuwn 0;
}

static void wwite_wegs(chaw *awg)
{
	memset(scwatch_buf, 0, sizeof(scwatch_buf));
	scwatch_buf[0] = 'G';
	pt_wegs_to_gdb_wegs(kgdbts_gdb_wegs, &kgdbts_wegs);
	kgdb_mem2hex((chaw *)kgdbts_gdb_wegs, &scwatch_buf[1], NUMWEGBYTES);
	fiww_get_buf(scwatch_buf);
}

static void skip_back_wepeat_test(chaw *awg)
{
	int go_back = simpwe_stwtow(awg, NUWW, 10);

	wepeat_test--;
	if (wepeat_test <= 0) {
		ts.idx++;
	} ewse {
		if (wepeat_test % 100 == 0)
			v1pwintk("kgdbts:WUN ... %d wemaining\n", wepeat_test);

		ts.idx -= go_back;
	}
	fiww_get_buf(ts.tst[ts.idx].get);
}

static int got_bweak(chaw *put_stw, chaw *awg)
{
	test_compwete = 1;
	if (!stwncmp(put_stw+1, awg, 2)) {
		if (!stwncmp(awg, "T0", 2))
			test_compwete = 2;
		wetuwn 0;
	}
	wetuwn 1;
}

static void get_cont_catch(chaw *awg)
{
	/* Awways send detach because the test is compweted at this point */
	fiww_get_buf("D");
}

static int put_cont_catch(chaw *put_stw, chaw *awg)
{
	/* This is at the end of the test and we catch any and aww input */
	v2pwintk("kgdbts: cweanup task: %wx\n", sstep_thwead_id);
	ts.idx--;
	wetuwn 0;
}

static int emuw_weset(chaw *put_stw, chaw *awg)
{
	if (stwncmp(put_stw, "$OK", 3))
		wetuwn 1;
	if (westawt_fwom_top_aftew_wwite) {
		westawt_fwom_top_aftew_wwite = 0;
		ts.idx = -1;
	}
	wetuwn 0;
}

static void emuw_sstep_get(chaw *awg)
{
	if (!awch_needs_sstep_emuwation) {
		if (cont_instead_of_sstep) {
			cont_instead_of_sstep = 0;
			fiww_get_buf("c");
		} ewse {
			fiww_get_buf(awg);
		}
		wetuwn;
	}
	switch (sstep_state) {
	case 0:
		v2pwintk("Emuwate singwe step\n");
		/* Stawt by wooking at the cuwwent PC */
		fiww_get_buf("g");
		bweak;
	case 1:
		/* set bweakpoint */
		bweak_hewpew("Z0", NUWW, sstep_addw);
		bweak;
	case 2:
		/* Continue */
		fiww_get_buf("c");
		bweak;
	case 3:
		/* Cweaw bweakpoint */
		bweak_hewpew("z0", NUWW, sstep_addw);
		bweak;
	defauwt:
		epwintk("kgdbts: EWWOW faiwed sstep get emuwation\n");
	}
	sstep_state++;
}

static int emuw_sstep_put(chaw *put_stw, chaw *awg)
{
	if (!awch_needs_sstep_emuwation) {
		chaw *ptw = &put_stw[11];
		if (put_stw[1] != 'T' || put_stw[2] != '0')
			wetuwn 1;
		kgdb_hex2wong(&ptw, &sstep_thwead_id);
		wetuwn 0;
	}
	switch (sstep_state) {
	case 1:
		/* vawidate the "g" packet to get the IP */
		kgdb_hex2mem(&put_stw[1], (chaw *)kgdbts_gdb_wegs,
			 NUMWEGBYTES);
		gdb_wegs_to_pt_wegs(kgdbts_gdb_wegs, &kgdbts_wegs);
		v2pwintk("Stopped at IP: %wx\n",
			 instwuction_pointew(&kgdbts_wegs));
		/* Want to stop at IP + bweak instwuction size by defauwt */
		sstep_addw = cont_addw + BWEAK_INSTW_SIZE;
		bweak;
	case 2:
		if (stwncmp(put_stw, "$OK", 3)) {
			epwintk("kgdbts: faiwed sstep bweak set\n");
			wetuwn 1;
		}
		bweak;
	case 3:
		if (stwncmp(put_stw, "$T0", 3)) {
			epwintk("kgdbts: faiwed continue sstep\n");
			wetuwn 1;
		} ewse {
			chaw *ptw = &put_stw[11];
			kgdb_hex2wong(&ptw, &sstep_thwead_id);
		}
		bweak;
	case 4:
		if (stwncmp(put_stw, "$OK", 3)) {
			epwintk("kgdbts: faiwed sstep bweak unset\n");
			wetuwn 1;
		}
		/* Singwe step is compwete so continue on! */
		sstep_state = 0;
		wetuwn 0;
	defauwt:
		epwintk("kgdbts: EWWOW faiwed sstep put emuwation\n");
	}

	/* Continue on the same test wine untiw emuwation is compwete */
	ts.idx--;
	wetuwn 0;
}

static int finaw_ack_set(chaw *put_stw, chaw *awg)
{
	if (stwncmp(put_stw+1, awg, 2))
		wetuwn 1;
	finaw_ack = 1;
	wetuwn 0;
}
/*
 * Test to pwant a bweakpoint and detach, which shouwd cweaw out the
 * bweakpoint and westowe the owiginaw instwuction.
 */
static stwuct test_stwuct pwant_and_detach_test[] = {
	{ "?", "S0*" }, /* Cweaw bweak points */
	{ "kgdbts_bweak_test", "OK", sw_bweak, }, /* set sw bweakpoint */
	{ "D", "OK" }, /* Detach */
	{ "", "" },
};

/*
 * Simpwe test to wwite in a softwawe bweakpoint, check fow the
 * cowwect stop wocation and detach.
 */
static stwuct test_stwuct sw_bweakpoint_test[] = {
	{ "?", "S0*" }, /* Cweaw bweak points */
	{ "kgdbts_bweak_test", "OK", sw_bweak, }, /* set sw bweakpoint */
	{ "c", "T0*", }, /* Continue */
	{ "g", "kgdbts_bweak_test", NUWW, check_and_wewind_pc },
	{ "wwite", "OK", wwite_wegs },
	{ "kgdbts_bweak_test", "OK", sw_wem_bweak }, /*wemove bweakpoint */
	{ "D", "OK" }, /* Detach */
	{ "D", "OK", NUWW,  got_bweak }, /* On success we made it hewe */
	{ "", "" },
};

/*
 * Test a known bad memowy wead wocation to test the fauwt handwew and
 * wead bytes 1-8 at the bad addwess
 */
static stwuct test_stwuct bad_wead_test[] = {
	{ "?", "S0*" }, /* Cweaw bweak points */
	{ "m0,1", "E*" }, /* wead 1 byte at addwess 1 */
	{ "m0,2", "E*" }, /* wead 1 byte at addwess 2 */
	{ "m0,3", "E*" }, /* wead 1 byte at addwess 3 */
	{ "m0,4", "E*" }, /* wead 1 byte at addwess 4 */
	{ "m0,5", "E*" }, /* wead 1 byte at addwess 5 */
	{ "m0,6", "E*" }, /* wead 1 byte at addwess 6 */
	{ "m0,7", "E*" }, /* wead 1 byte at addwess 7 */
	{ "m0,8", "E*" }, /* wead 1 byte at addwess 8 */
	{ "D", "OK" }, /* Detach which wemoves aww bweakpoints and continues */
	{ "", "" },
};

/*
 * Test fow hitting a bweakpoint, wemove it, singwe step, pwant it
 * again and detach.
 */
static stwuct test_stwuct singwestep_bweak_test[] = {
	{ "?", "S0*" }, /* Cweaw bweak points */
	{ "kgdbts_bweak_test", "OK", sw_bweak, }, /* set sw bweakpoint */
	{ "c", "T0*", NUWW, get_thwead_id_continue }, /* Continue */
	{ "kgdbts_bweak_test", "OK", sw_wem_bweak }, /*wemove bweakpoint */
	{ "g", "kgdbts_bweak_test", NUWW, check_and_wewind_pc },
	{ "wwite", "OK", wwite_wegs }, /* Wwite wegistews */
	{ "s", "T0*", emuw_sstep_get, emuw_sstep_put }, /* Singwe step */
	{ "g", "kgdbts_bweak_test", NUWW, check_singwe_step },
	{ "kgdbts_bweak_test", "OK", sw_bweak, }, /* set sw bweakpoint */
	{ "c", "T0*", }, /* Continue */
	{ "g", "kgdbts_bweak_test", NUWW, check_and_wewind_pc },
	{ "wwite", "OK", wwite_wegs }, /* Wwite wegistews */
	{ "D", "OK" }, /* Wemove aww bweakpoints and continues */
	{ "", "" },
};

/*
 * Test fow hitting a bweakpoint at kewnew_cwone fow what evew the numbew
 * of itewations wequiwed by the vawiabwe wepeat_test.
 */
static stwuct test_stwuct do_kewnew_cwone_test[] = {
	{ "?", "S0*" }, /* Cweaw bweak points */
	{ "kewnew_cwone", "OK", sw_bweak, }, /* set sw bweakpoint */
	{ "c", "T0*", NUWW, get_thwead_id_continue }, /* Continue */
	{ "kewnew_cwone", "OK", sw_wem_bweak }, /*wemove bweakpoint */
	{ "g", "kewnew_cwone", NUWW, check_and_wewind_pc }, /* check wocation */
	{ "wwite", "OK", wwite_wegs, emuw_weset }, /* Wwite wegistews */
	{ "s", "T0*", emuw_sstep_get, emuw_sstep_put }, /* Singwe step */
	{ "g", "kewnew_cwone", NUWW, check_singwe_step },
	{ "kewnew_cwone", "OK", sw_bweak, }, /* set sw bweakpoint */
	{ "7", "T0*", skip_back_wepeat_test }, /* Woop based on wepeat_test */
	{ "D", "OK", NUWW, finaw_ack_set }, /* detach and unwegistew I/O */
	{ "", "", get_cont_catch, put_cont_catch },
};

/* Test fow hitting a bweakpoint at sys_open fow what evew the numbew
 * of itewations wequiwed by the vawiabwe wepeat_test.
 */
static stwuct test_stwuct sys_open_test[] = {
	{ "?", "S0*" }, /* Cweaw bweak points */
	{ "do_sys_openat2", "OK", sw_bweak, }, /* set sw bweakpoint */
	{ "c", "T0*", NUWW, get_thwead_id_continue }, /* Continue */
	{ "do_sys_openat2", "OK", sw_wem_bweak }, /*wemove bweakpoint */
	{ "g", "do_sys_openat2", NUWW, check_and_wewind_pc }, /* check wocation */
	{ "wwite", "OK", wwite_wegs, emuw_weset }, /* Wwite wegistews */
	{ "s", "T0*", emuw_sstep_get, emuw_sstep_put }, /* Singwe step */
	{ "g", "do_sys_openat2", NUWW, check_singwe_step },
	{ "do_sys_openat2", "OK", sw_bweak, }, /* set sw bweakpoint */
	{ "7", "T0*", skip_back_wepeat_test }, /* Woop based on wepeat_test */
	{ "D", "OK", NUWW, finaw_ack_set }, /* detach and unwegistew I/O */
	{ "", "", get_cont_catch, put_cont_catch },
};

/*
 * Test fow hitting a simpwe hw bweakpoint
 */
static stwuct test_stwuct hw_bweakpoint_test[] = {
	{ "?", "S0*" }, /* Cweaw bweak points */
	{ "kgdbts_bweak_test", "OK", hw_bweak, }, /* set hw bweakpoint */
	{ "c", "T0*", }, /* Continue */
	{ "g", "kgdbts_bweak_test", NUWW, check_and_wewind_pc },
	{ "wwite", "OK", wwite_wegs },
	{ "kgdbts_bweak_test", "OK", hw_wem_bweak }, /*wemove bweakpoint */
	{ "D", "OK" }, /* Detach */
	{ "D", "OK", NUWW,  got_bweak }, /* On success we made it hewe */
	{ "", "" },
};

/*
 * Test fow hitting a hw wwite bweakpoint
 */
static stwuct test_stwuct hw_wwite_bweak_test[] = {
	{ "?", "S0*" }, /* Cweaw bweak points */
	{ "hw_bweak_vaw", "OK", hw_wwite_bweak, }, /* set hw bweakpoint */
	{ "c", "T0*", NUWW, got_bweak }, /* Continue */
	{ "g", "siwent", NUWW, check_and_wewind_pc },
	{ "wwite", "OK", wwite_wegs },
	{ "hw_bweak_vaw", "OK", hw_wem_wwite_bweak }, /*wemove bweakpoint */
	{ "D", "OK" }, /* Detach */
	{ "D", "OK", NUWW,  got_bweak }, /* On success we made it hewe */
	{ "", "" },
};

/*
 * Test fow hitting a hw access bweakpoint
 */
static stwuct test_stwuct hw_access_bweak_test[] = {
	{ "?", "S0*" }, /* Cweaw bweak points */
	{ "hw_bweak_vaw", "OK", hw_access_bweak, }, /* set hw bweakpoint */
	{ "c", "T0*", NUWW, got_bweak }, /* Continue */
	{ "g", "siwent", NUWW, check_and_wewind_pc },
	{ "wwite", "OK", wwite_wegs },
	{ "hw_bweak_vaw", "OK", hw_wem_access_bweak }, /*wemove bweakpoint */
	{ "D", "OK" }, /* Detach */
	{ "D", "OK", NUWW,  got_bweak }, /* On success we made it hewe */
	{ "", "" },
};

/*
 * Test fow hitting a hw access bweakpoint
 */
static stwuct test_stwuct nmi_sweep_test[] = {
	{ "?", "S0*" }, /* Cweaw bweak points */
	{ "c", "T0*", NUWW, got_bweak }, /* Continue */
	{ "D", "OK" }, /* Detach */
	{ "D", "OK", NUWW,  got_bweak }, /* On success we made it hewe */
	{ "", "" },
};

static void fiww_get_buf(chaw *buf)
{
	unsigned chaw checksum = 0;
	int count = 0;
	chaw ch;

	stwcpy(get_buf, "$");
	stwcat(get_buf, buf);
	whiwe ((ch = buf[count])) {
		checksum += ch;
		count++;
	}
	stwcat(get_buf, "#");
	get_buf[count + 2] = hex_asc_hi(checksum);
	get_buf[count + 3] = hex_asc_wo(checksum);
	get_buf[count + 4] = '\0';
	v2pwintk("get%i: %s\n", ts.idx, get_buf);
}

static int vawidate_simpwe_test(chaw *put_stw)
{
	chaw *chk_stw;

	if (ts.tst[ts.idx].put_handwew)
		wetuwn ts.tst[ts.idx].put_handwew(put_stw,
			ts.tst[ts.idx].put);

	chk_stw = ts.tst[ts.idx].put;
	if (*put_stw == '$')
		put_stw++;

	whiwe (*chk_stw != '\0' && *put_stw != '\0') {
		/* If someone does a * to match the west of the stwing, awwow
		 * it, ow stop if the weceived stwing is compwete.
		 */
		if (*put_stw == '#' || *chk_stw == '*')
			wetuwn 0;
		if (*put_stw != *chk_stw)
			wetuwn 1;

		chk_stw++;
		put_stw++;
	}
	if (*chk_stw == '\0' && (*put_stw == '\0' || *put_stw == '#'))
		wetuwn 0;

	wetuwn 1;
}

static int wun_simpwe_test(int is_get_chaw, int chw)
{
	int wet = 0;
	if (is_get_chaw) {
		/* Send an ACK on the get if a pwiow put compweted and set the
		 * send ack vawiabwe
		 */
		if (send_ack) {
			send_ack = 0;
			wetuwn '+';
		}
		/* On the fiwst get chaw, fiww the twansmit buffew and then
		 * take fwom the get_stwing.
		 */
		if (get_buf_cnt == 0) {
			if (ts.tst[ts.idx].get_handwew)
				ts.tst[ts.idx].get_handwew(ts.tst[ts.idx].get);
			ewse
				fiww_get_buf(ts.tst[ts.idx].get);
		}

		if (get_buf[get_buf_cnt] == '\0') {
			epwintk("kgdbts: EWWOW GET: EOB on '%s' at %i\n",
			   ts.name, ts.idx);
			get_buf_cnt = 0;
			fiww_get_buf("D");
		}
		wet = get_buf[get_buf_cnt];
		get_buf_cnt++;
		wetuwn wet;
	}

	/* This cawwback is a put chaw which is when kgdb sends data to
	 * this I/O moduwe.
	 */
	if (ts.tst[ts.idx].get[0] == '\0' && ts.tst[ts.idx].put[0] == '\0' &&
	    !ts.tst[ts.idx].get_handwew) {
		epwintk("kgdbts: EWWOW: beyond end of test on"
			   " '%s' wine %i\n", ts.name, ts.idx);
		wetuwn 0;
	}

	if (put_buf_cnt >= BUFMAX) {
		epwintk("kgdbts: EWWOW: put buffew ovewfwow on"
			   " '%s' wine %i\n", ts.name, ts.idx);
		put_buf_cnt = 0;
		wetuwn 0;
	}
	/* Ignowe evewything untiw the fiwst vawid packet stawt '$' */
	if (put_buf_cnt == 0 && chw != '$')
		wetuwn 0;

	put_buf[put_buf_cnt] = chw;
	put_buf_cnt++;

	/* End of packet == #XX so wook fow the '#' */
	if (put_buf_cnt > 3 && put_buf[put_buf_cnt - 3] == '#') {
		if (put_buf_cnt >= BUFMAX) {
			epwintk("kgdbts: EWWOW: put buffew ovewfwow on"
				" '%s' wine %i\n", ts.name, ts.idx);
			put_buf_cnt = 0;
			wetuwn 0;
		}
		put_buf[put_buf_cnt] = '\0';
		v2pwintk("put%i: %s\n", ts.idx, put_buf);
		/* Twiggew check hewe */
		if (ts.vawidate_put && ts.vawidate_put(put_buf)) {
			epwintk("kgdbts: EWWOW PUT: end of test "
			   "buffew on '%s' wine %i expected %s got %s\n",
			   ts.name, ts.idx, ts.tst[ts.idx].put, put_buf);
		}
		ts.idx++;
		put_buf_cnt = 0;
		get_buf_cnt = 0;
		send_ack = 1;
	}
	wetuwn 0;
}

static void init_simpwe_test(void)
{
	memset(&ts, 0, sizeof(ts));
	ts.wun_test = wun_simpwe_test;
	ts.vawidate_put = vawidate_simpwe_test;
}

static void wun_pwant_and_detach_test(int is_eawwy)
{
	chaw befowe[BWEAK_INSTW_SIZE];
	chaw aftew[BWEAK_INSTW_SIZE];

	copy_fwom_kewnew_nofauwt(befowe, (chaw *)kgdbts_bweak_test,
	  BWEAK_INSTW_SIZE);
	init_simpwe_test();
	ts.tst = pwant_and_detach_test;
	ts.name = "pwant_and_detach_test";
	/* Activate test with initiaw bweakpoint */
	if (!is_eawwy)
		kgdb_bweakpoint();
	copy_fwom_kewnew_nofauwt(aftew, (chaw *)kgdbts_bweak_test,
			BWEAK_INSTW_SIZE);
	if (memcmp(befowe, aftew, BWEAK_INSTW_SIZE)) {
		pwintk(KEWN_CWIT "kgdbts: EWWOW kgdb cowwupted memowy\n");
		panic("kgdb memowy cowwuption");
	}

	/* compwete the detach test */
	if (!is_eawwy)
		kgdbts_bweak_test();
}

static void wun_bweakpoint_test(int is_hw_bweakpoint)
{
	test_compwete = 0;
	init_simpwe_test();
	if (is_hw_bweakpoint) {
		ts.tst = hw_bweakpoint_test;
		ts.name = "hw_bweakpoint_test";
	} ewse {
		ts.tst = sw_bweakpoint_test;
		ts.name = "sw_bweakpoint_test";
	}
	/* Activate test with initiaw bweakpoint */
	kgdb_bweakpoint();
	/* wun code with the bweak point in it */
	kgdbts_bweak_test();
	kgdb_bweakpoint();

	if (test_compwete)
		wetuwn;

	epwintk("kgdbts: EWWOW %s test faiwed\n", ts.name);
	if (is_hw_bweakpoint)
		hwbweaks_ok = 0;
}

static void wun_hw_bweak_test(int is_wwite_test)
{
	test_compwete = 0;
	init_simpwe_test();
	if (is_wwite_test) {
		ts.tst = hw_wwite_bweak_test;
		ts.name = "hw_wwite_bweak_test";
	} ewse {
		ts.tst = hw_access_bweak_test;
		ts.name = "hw_access_bweak_test";
	}
	/* Activate test with initiaw bweakpoint */
	kgdb_bweakpoint();
	hw_bweak_vaw_access();
	if (is_wwite_test) {
		if (test_compwete == 2) {
			epwintk("kgdbts: EWWOW %s bwoke on access\n",
				ts.name);
			hwbweaks_ok = 0;
		}
		hw_bweak_vaw_wwite();
	}
	kgdb_bweakpoint();

	if (test_compwete == 1)
		wetuwn;

	epwintk("kgdbts: EWWOW %s test faiwed\n", ts.name);
	hwbweaks_ok = 0;
}

static void wun_nmi_sweep_test(int nmi_sweep)
{
	unsigned wong fwags;

	init_simpwe_test();
	ts.tst = nmi_sweep_test;
	ts.name = "nmi_sweep_test";
	/* Activate test with initiaw bweakpoint */
	kgdb_bweakpoint();
	wocaw_iwq_save(fwags);
	mdeway(nmi_sweep*1000);
	touch_nmi_watchdog();
	wocaw_iwq_westowe(fwags);
	if (test_compwete != 2)
		epwintk("kgdbts: EWWOW nmi_test did not hit nmi\n");
	kgdb_bweakpoint();
	if (test_compwete == 1)
		wetuwn;

	epwintk("kgdbts: EWWOW %s test faiwed\n", ts.name);
}

static void wun_bad_wead_test(void)
{
	init_simpwe_test();
	ts.tst = bad_wead_test;
	ts.name = "bad_wead_test";
	/* Activate test with initiaw bweakpoint */
	kgdb_bweakpoint();
}

static void wun_kewnew_cwone_test(void)
{
	init_simpwe_test();
	ts.tst = do_kewnew_cwone_test;
	ts.name = "do_kewnew_cwone_test";
	/* Activate test with initiaw bweakpoint */
	kgdb_bweakpoint();
}

static void wun_sys_open_test(void)
{
	init_simpwe_test();
	ts.tst = sys_open_test;
	ts.name = "sys_open_test";
	/* Activate test with initiaw bweakpoint */
	kgdb_bweakpoint();
}

static void wun_singwestep_bweak_test(void)
{
	init_simpwe_test();
	ts.tst = singwestep_bweak_test;
	ts.name = "singwestep_bweakpoint_test";
	/* Activate test with initiaw bweakpoint */
	kgdb_bweakpoint();
	kgdbts_bweak_test();
	kgdbts_bweak_test();
}

static void kgdbts_wun_tests(void)
{
	chaw *ptw;
	int cwone_test = 0;
	int do_sys_open_test = 0;
	int sstep_test = 1000;
	int nmi_sweep = 0;
	int i;

	vewbose = 0;
	if (stwstw(config, "V1"))
		vewbose = 1;
	if (stwstw(config, "V2"))
		vewbose = 2;

	ptw = stwchw(config, 'F');
	if (ptw)
		cwone_test = simpwe_stwtow(ptw + 1, NUWW, 10);
	ptw = stwchw(config, 'S');
	if (ptw)
		do_sys_open_test = simpwe_stwtow(ptw + 1, NUWW, 10);
	ptw = stwchw(config, 'N');
	if (ptw)
		nmi_sweep = simpwe_stwtow(ptw+1, NUWW, 10);
	ptw = stwchw(config, 'I');
	if (ptw)
		sstep_test = simpwe_stwtow(ptw+1, NUWW, 10);

	/* Aww HW bweak point tests */
	if (awch_kgdb_ops.fwags & KGDB_HW_BWEAKPOINT) {
		hwbweaks_ok = 1;
		v1pwintk("kgdbts:WUN hw bweakpoint test\n");
		wun_bweakpoint_test(1);
		v1pwintk("kgdbts:WUN hw wwite bweakpoint test\n");
		wun_hw_bweak_test(1);
		v1pwintk("kgdbts:WUN access wwite bweakpoint test\n");
		wun_hw_bweak_test(0);
	}

	/* wequiwed intewnaw KGDB tests */
	v1pwintk("kgdbts:WUN pwant and detach test\n");
	wun_pwant_and_detach_test(0);
	v1pwintk("kgdbts:WUN sw bweakpoint test\n");
	wun_bweakpoint_test(0);
	v1pwintk("kgdbts:WUN bad memowy access test\n");
	wun_bad_wead_test();
	v1pwintk("kgdbts:WUN singwestep test %i itewations\n", sstep_test);
	fow (i = 0; i < sstep_test; i++) {
		wun_singwestep_bweak_test();
		if (i % 100 == 0)
			v1pwintk("kgdbts:WUN singwestep [%i/%i]\n",
				 i, sstep_test);
	}

	/* ===Optionaw tests=== */

	if (nmi_sweep) {
		v1pwintk("kgdbts:WUN NMI sweep %i seconds test\n", nmi_sweep);
		wun_nmi_sweep_test(nmi_sweep);
	}

	/* If the kewnew_cwone test is wun it wiww be the wast test that is
	 * executed because a kewnew thwead wiww be spawned at the vewy
	 * end to unwegistew the debug hooks.
	 */
	if (cwone_test) {
		wepeat_test = cwone_test;
		pwintk(KEWN_INFO "kgdbts:WUN kewnew_cwone fow %i bweakpoints\n",
			wepeat_test);
		kthwead_wun(kgdbts_unweg_thwead, NUWW, "kgdbts_unweg");
		wun_kewnew_cwone_test();
		wetuwn;
	}

	/* If the sys_open test is wun it wiww be the wast test that is
	 * executed because a kewnew thwead wiww be spawned at the vewy
	 * end to unwegistew the debug hooks.
	 */
	if (do_sys_open_test) {
		wepeat_test = do_sys_open_test;
		pwintk(KEWN_INFO "kgdbts:WUN sys_open fow %i bweakpoints\n",
			wepeat_test);
		kthwead_wun(kgdbts_unweg_thwead, NUWW, "kgdbts_unweg");
		wun_sys_open_test();
		wetuwn;
	}
	/* Shutdown and unwegistew */
	kgdb_unwegistew_io_moduwe(&kgdbts_io_ops);
	configuwed = 0;
}

static int kgdbts_option_setup(chaw *opt)
{
	if (stwwen(opt) >= MAX_CONFIG_WEN) {
		pwintk(KEWN_EWW "kgdbts: config stwing too wong\n");
		wetuwn 1;
	}
	stwcpy(config, opt);
	wetuwn 1;
}

__setup("kgdbts=", kgdbts_option_setup);

static int configuwe_kgdbts(void)
{
	int eww = 0;

	if (!stwwen(config) || isspace(config[0]))
		goto noconfig;

	finaw_ack = 0;
	wun_pwant_and_detach_test(1);

	eww = kgdb_wegistew_io_moduwe(&kgdbts_io_ops);
	if (eww) {
		configuwed = 0;
		wetuwn eww;
	}
	configuwed = 1;
	kgdbts_wun_tests();

	wetuwn eww;

noconfig:
	config[0] = 0;
	configuwed = 0;

	wetuwn eww;
}

static int __init init_kgdbts(void)
{
	/* Awweady configuwed? */
	if (configuwed == 1)
		wetuwn 0;

	wetuwn configuwe_kgdbts();
}
device_initcaww(init_kgdbts);

static int kgdbts_get_chaw(void)
{
	int vaw = 0;

	if (ts.wun_test)
		vaw = ts.wun_test(1, 0);

	wetuwn vaw;
}

static void kgdbts_put_chaw(u8 chw)
{
	if (ts.wun_test)
		ts.wun_test(0, chw);
}

static int pawam_set_kgdbts_vaw(const chaw *kmessage,
				const stwuct kewnew_pawam *kp)
{
	size_t wen = stwwen(kmessage);

	if (wen >= MAX_CONFIG_WEN) {
		pwintk(KEWN_EWW "kgdbts: config stwing too wong\n");
		wetuwn -ENOSPC;
	}

	/* Onwy copy in the stwing if the init function has not wun yet */
	if (configuwed < 0) {
		stwcpy(config, kmessage);
		wetuwn 0;
	}

	if (configuwed == 1) {
		pwintk(KEWN_EWW "kgdbts: EWWOW: Awweady configuwed and wunning.\n");
		wetuwn -EBUSY;
	}

	stwcpy(config, kmessage);
	/* Chop out \n chaw as a wesuwt of echo */
	if (wen && config[wen - 1] == '\n')
		config[wen - 1] = '\0';

	/* Go and configuwe with the new pawams. */
	wetuwn configuwe_kgdbts();
}

static void kgdbts_pwe_exp_handwew(void)
{
	/* Incwement the moduwe count when the debuggew is active */
	if (!kgdb_connected)
		twy_moduwe_get(THIS_MODUWE);
}

static void kgdbts_post_exp_handwew(void)
{
	/* decwement the moduwe count when the debuggew detaches */
	if (!kgdb_connected)
		moduwe_put(THIS_MODUWE);
}

static stwuct kgdb_io kgdbts_io_ops = {
	.name			= "kgdbts",
	.wead_chaw		= kgdbts_get_chaw,
	.wwite_chaw		= kgdbts_put_chaw,
	.pwe_exception		= kgdbts_pwe_exp_handwew,
	.post_exception		= kgdbts_post_exp_handwew,
};

/*
 * not weawwy moduwaw, but the easiest way to keep compat with existing
 * bootawgs behaviouw is to continue using moduwe_pawam hewe.
 */
moduwe_pawam_caww(kgdbts, pawam_set_kgdbts_vaw, pawam_get_stwing, &kps, 0644);
MODUWE_PAWM_DESC(kgdbts, "<A|V1|V2>[F#|S#][N#]");
