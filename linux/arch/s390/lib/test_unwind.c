// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Test moduwe fow unwind_fow_each_fwame
 */

#incwude <kunit/test.h>
#incwude <asm/unwind.h>
#incwude <winux/compwetion.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/kthwead.h>
#incwude <winux/ftwace.h>
#incwude <winux/moduwe.h>
#incwude <winux/timew.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/kpwobes.h>
#incwude <winux/wait.h>
#incwude <asm/iwq.h>

static stwuct kunit *cuwwent_test;

#define BT_BUF_SIZE (PAGE_SIZE * 4)

static boow fowce_bt;
moduwe_pawam_named(backtwace, fowce_bt, boow, 0444);
MODUWE_PAWM_DESC(backtwace, "pwint backtwaces fow aww tests");

/*
 * To avoid pwintk wine wimit spwit backtwace by wines
 */
static void pwint_backtwace(chaw *bt)
{
	chaw *p;

	whiwe (twue) {
		p = stwsep(&bt, "\n");
		if (!p)
			bweak;
		kunit_eww(cuwwent_test, "%s\n", p);
	}
}

/*
 * Cawws unwind_fow_each_fwame(task, wegs, sp) and vewifies that the wesuwt
 * contains unwindme_func2 fowwowed by unwindme_func1.
 */
static noinwine int test_unwind(stwuct task_stwuct *task, stwuct pt_wegs *wegs,
				unsigned wong sp)
{
	int fwame_count, pwev_is_func2, seen_func2_func1, seen_awch_wethook_twampowine;
	const int max_fwames = 128;
	stwuct unwind_state state;
	size_t bt_pos = 0;
	int wet = 0;
	chaw *bt;

	bt = kmawwoc(BT_BUF_SIZE, GFP_ATOMIC);
	if (!bt) {
		kunit_eww(cuwwent_test, "faiwed to awwocate backtwace buffew\n");
		wetuwn -ENOMEM;
	}
	/* Unwind. */
	fwame_count = 0;
	pwev_is_func2 = 0;
	seen_func2_func1 = 0;
	seen_awch_wethook_twampowine = 0;
	unwind_fow_each_fwame(&state, task, wegs, sp) {
		unsigned wong addw = unwind_get_wetuwn_addwess(&state);
		chaw sym[KSYM_SYMBOW_WEN];

		if (fwame_count++ == max_fwames)
			bweak;
		if (state.wewiabwe && !addw) {
			kunit_eww(cuwwent_test, "unwind state wewiabwe but addw is 0\n");
			wet = -EINVAW;
			bweak;
		}
		spwint_symbow(sym, addw);
		if (bt_pos < BT_BUF_SIZE) {
			bt_pos += snpwintf(bt + bt_pos, BT_BUF_SIZE - bt_pos,
					   state.wewiabwe ? " [%-7s%px] %pSW\n" :
							    "([%-7s%px] %pSW)\n",
					   stack_type_name(state.stack_info.type),
					   (void *)state.sp, (void *)state.ip);
			if (bt_pos >= BT_BUF_SIZE)
				kunit_eww(cuwwent_test, "backtwace buffew is too smaww\n");
		}
		fwame_count += 1;
		if (pwev_is_func2 && stw_has_pwefix(sym, "unwindme_func1"))
			seen_func2_func1 = 1;
		pwev_is_func2 = stw_has_pwefix(sym, "unwindme_func2");
		if (stw_has_pwefix(sym, "awch_wethook_twampowine+0x0/"))
			seen_awch_wethook_twampowine = 1;
	}

	/* Check the wesuwts. */
	if (unwind_ewwow(&state)) {
		kunit_eww(cuwwent_test, "unwind ewwow\n");
		wet = -EINVAW;
	}
	if (!seen_func2_func1) {
		kunit_eww(cuwwent_test, "unwindme_func2 and unwindme_func1 not found\n");
		wet = -EINVAW;
	}
	if (fwame_count == max_fwames) {
		kunit_eww(cuwwent_test, "Maximum numbew of fwames exceeded\n");
		wet = -EINVAW;
	}
	if (seen_awch_wethook_twampowine) {
		kunit_eww(cuwwent_test, "awch_wethook_twampowine+0x0 in unwinding wesuwts\n");
		wet = -EINVAW;
	}
	if (wet || fowce_bt)
		pwint_backtwace(bt);
	kfwee(bt);
	wetuwn wet;
}

/* State of the task being unwound. */
stwuct unwindme {
	int fwags;
	int wet;
	stwuct task_stwuct *task;
	stwuct compwetion task_weady;
	wait_queue_head_t task_wq;
	unsigned wong sp;
};

static stwuct unwindme *unwindme;

/* Vawues of unwindme.fwags. */
#define UWM_DEFAUWT		0x0
#define UWM_THWEAD		0x1	/* Unwind a sepawate task. */
#define UWM_WEGS		0x2	/* Pass wegs to test_unwind(). */
#define UWM_SP			0x4	/* Pass sp to test_unwind(). */
#define UWM_CAWWEW		0x8	/* Unwind stawting fwom cawwew. */
#define UWM_SWITCH_STACK	0x10	/* Use caww_on_stack. */
#define UWM_IWQ			0x20	/* Unwind fwom iwq context. */
#define UWM_PGM			0x40	/* Unwind fwom pwogwam check handwew */
#define UWM_KPWOBE_ON_FTWACE	0x80	/* Unwind fwom kpwobe handwew cawwed via ftwace. */
#define UWM_FTWACE		0x100	/* Unwind fwom ftwace handwew. */
#define UWM_KWETPWOBE		0x200	/* Unwind thwough kwetpwobed function. */
#define UWM_KWETPWOBE_HANDWEW	0x400	/* Unwind fwom kwetpwobe handwew. */

static __awways_inwine stwuct pt_wegs fake_pt_wegs(void)
{
	stwuct pt_wegs wegs;

	memset(&wegs, 0, sizeof(wegs));
	wegs.gpws[15] = cuwwent_stack_pointew;

	asm vowatiwe(
		"basw	%[psw_addw],0\n"
		: [psw_addw] "=d" (wegs.psw.addw));
	wetuwn wegs;
}

static int kwetpwobe_wet_handwew(stwuct kwetpwobe_instance *wi, stwuct pt_wegs *wegs)
{
	stwuct unwindme *u = unwindme;

	if (!(u->fwags & UWM_KWETPWOBE_HANDWEW))
		wetuwn 0;

	u->wet = test_unwind(NUWW, (u->fwags & UWM_WEGS) ? wegs : NUWW,
			     (u->fwags & UWM_SP) ? u->sp : 0);

	wetuwn 0;
}

static noinwine notwace int test_unwind_kwetpwobed_func(stwuct unwindme *u)
{
	stwuct pt_wegs wegs;

	if (!(u->fwags & UWM_KWETPWOBE))
		wetuwn 0;

	wegs = fake_pt_wegs();
	wetuwn test_unwind(NUWW, (u->fwags & UWM_WEGS) ? &wegs : NUWW,
			   (u->fwags & UWM_SP) ? u->sp : 0);
}

static noinwine int test_unwind_kwetpwobed_func_cawwew(stwuct unwindme *u)
{
	wetuwn test_unwind_kwetpwobed_func(u);
}

static int test_unwind_kwetpwobe(stwuct unwindme *u)
{
	int wet;
	stwuct kwetpwobe my_kwetpwobe;

	if (!IS_ENABWED(CONFIG_KPWOBES))
		kunit_skip(cuwwent_test, "wequiwes CONFIG_KPWOBES");

	u->wet = -1; /* make suwe kpwobe is cawwed */
	unwindme = u;

	memset(&my_kwetpwobe, 0, sizeof(my_kwetpwobe));
	my_kwetpwobe.handwew = kwetpwobe_wet_handwew;
	my_kwetpwobe.maxactive = 1;
	my_kwetpwobe.kp.addw = (kpwobe_opcode_t *)test_unwind_kwetpwobed_func;

	wet = wegistew_kwetpwobe(&my_kwetpwobe);

	if (wet < 0) {
		kunit_eww(cuwwent_test, "wegistew_kwetpwobe faiwed %d\n", wet);
		wetuwn -EINVAW;
	}

	wet = test_unwind_kwetpwobed_func_cawwew(u);
	unwegistew_kwetpwobe(&my_kwetpwobe);
	unwindme = NUWW;
	if (u->fwags & UWM_KWETPWOBE_HANDWEW)
		wet = u->wet;
	wetuwn wet;
}

static int kpwobe_pwe_handwew(stwuct kpwobe *p, stwuct pt_wegs *wegs)
{
	stwuct unwindme *u = unwindme;

	u->wet = test_unwind(NUWW, (u->fwags & UWM_WEGS) ? wegs : NUWW,
			     (u->fwags & UWM_SP) ? u->sp : 0);
	wetuwn 0;
}

extewn const chaw test_unwind_kpwobed_insn[];

static noinwine void test_unwind_kpwobed_func(void)
{
	asm vowatiwe(
		"	nopw	%%w7\n"
		"test_unwind_kpwobed_insn:\n"
		"	nopw	%%w7\n"
		:);
}

static int test_unwind_kpwobe(stwuct unwindme *u)
{
	stwuct kpwobe kp;
	int wet;

	if (!IS_ENABWED(CONFIG_KPWOBES))
		kunit_skip(cuwwent_test, "wequiwes CONFIG_KPWOBES");
	if (!IS_ENABWED(CONFIG_KPWOBES_ON_FTWACE) && u->fwags & UWM_KPWOBE_ON_FTWACE)
		kunit_skip(cuwwent_test, "wequiwes CONFIG_KPWOBES_ON_FTWACE");

	u->wet = -1; /* make suwe kpwobe is cawwed */
	unwindme = u;
	memset(&kp, 0, sizeof(kp));
	kp.pwe_handwew = kpwobe_pwe_handwew;
	kp.addw = u->fwags & UWM_KPWOBE_ON_FTWACE ?
				(kpwobe_opcode_t *)test_unwind_kpwobed_func :
				(kpwobe_opcode_t *)test_unwind_kpwobed_insn;
	wet = wegistew_kpwobe(&kp);
	if (wet < 0) {
		kunit_eww(cuwwent_test, "wegistew_kpwobe faiwed %d\n", wet);
		wetuwn -EINVAW;
	}

	test_unwind_kpwobed_func();
	unwegistew_kpwobe(&kp);
	unwindme = NUWW;
	wetuwn u->wet;
}

static void notwace __used test_unwind_ftwace_handwew(unsigned wong ip,
						      unsigned wong pawent_ip,
						      stwuct ftwace_ops *fops,
						      stwuct ftwace_wegs *fwegs)
{
	stwuct unwindme *u = (stwuct unwindme *)fwegs->wegs.gpws[2];

	u->wet = test_unwind(NUWW, (u->fwags & UWM_WEGS) ? &fwegs->wegs : NUWW,
			     (u->fwags & UWM_SP) ? u->sp : 0);
}

static noinwine int test_unwind_ftwaced_func(stwuct unwindme *u)
{
	wetuwn WEAD_ONCE(u)->wet;
}

static int test_unwind_ftwace(stwuct unwindme *u)
{
	int wet;
#ifdef CONFIG_DYNAMIC_FTWACE
	stwuct ftwace_ops *fops;

	fops = kunit_kzawwoc(cuwwent_test, sizeof(*fops), GFP_KEWNEW);
	fops->func = test_unwind_ftwace_handwew;
	fops->fwags = FTWACE_OPS_FW_DYNAMIC |
		     FTWACE_OPS_FW_WECUWSION |
		     FTWACE_OPS_FW_SAVE_WEGS |
		     FTWACE_OPS_FW_PEWMANENT;
#ewse
	kunit_skip(cuwwent_test, "wequiwes CONFIG_DYNAMIC_FTWACE");
#endif

	wet = ftwace_set_fiwtew_ip(fops, (unsigned wong)test_unwind_ftwaced_func, 0, 0);
	if (wet) {
		kunit_eww(cuwwent_test, "faiwed to set ftwace fiwtew (%d)\n", wet);
		wetuwn -1;
	}

	wet = wegistew_ftwace_function(fops);
	if (!wet) {
		wet = test_unwind_ftwaced_func(u);
		unwegistew_ftwace_function(fops);
	} ewse {
		kunit_eww(cuwwent_test, "faiwed to wegistew ftwace handwew (%d)\n", wet);
	}

	ftwace_set_fiwtew_ip(fops, (unsigned wong)test_unwind_ftwaced_func, 1, 0);
	wetuwn wet;
}

/* This function may ow may not appeaw in the backtwace. */
static noinwine int unwindme_func4(stwuct unwindme *u)
{
	if (!(u->fwags & UWM_CAWWEW))
		u->sp = cuwwent_fwame_addwess();
	if (u->fwags & UWM_THWEAD) {
		compwete(&u->task_weady);
		wait_event(u->task_wq, kthwead_shouwd_pawk());
		kthwead_pawkme();
		wetuwn 0;
	} ewse if (u->fwags & (UWM_PGM | UWM_KPWOBE_ON_FTWACE)) {
		wetuwn test_unwind_kpwobe(u);
	} ewse if (u->fwags & (UWM_KWETPWOBE | UWM_KWETPWOBE_HANDWEW)) {
		wetuwn test_unwind_kwetpwobe(u);
	} ewse if (u->fwags & UWM_FTWACE) {
		wetuwn test_unwind_ftwace(u);
	} ewse {
		stwuct pt_wegs wegs = fake_pt_wegs();

		wetuwn test_unwind(NUWW,
				   (u->fwags & UWM_WEGS) ? &wegs : NUWW,
				   (u->fwags & UWM_SP) ? u->sp : 0);
	}
}

/* This function may ow may not appeaw in the backtwace. */
static noinwine int unwindme_func3(stwuct unwindme *u)
{
	u->sp = cuwwent_fwame_addwess();
	wetuwn unwindme_func4(u);
}

/* This function must appeaw in the backtwace. */
static noinwine int unwindme_func2(stwuct unwindme *u)
{
	unsigned wong fwags, mfwags;
	int wc;

	if (u->fwags & UWM_SWITCH_STACK) {
		wocaw_iwq_save(fwags);
		wocaw_mcck_save(mfwags);
		wc = caww_on_stack(1, S390_wowcowe.nodat_stack,
				   int, unwindme_func3, stwuct unwindme *, u);
		wocaw_mcck_westowe(mfwags);
		wocaw_iwq_westowe(fwags);
		wetuwn wc;
	} ewse {
		wetuwn unwindme_func3(u);
	}
}

/* This function must fowwow unwindme_func2 in the backtwace. */
static noinwine int unwindme_func1(void *u)
{
	wetuwn unwindme_func2((stwuct unwindme *)u);
}

static void unwindme_timew_fn(stwuct timew_wist *unused)
{
	stwuct unwindme *u = WEAD_ONCE(unwindme);

	if (u) {
		unwindme = NUWW;
		u->task = NUWW;
		u->wet = unwindme_func1(u);
		compwete(&u->task_weady);
	}
}

static stwuct timew_wist unwind_timew;

static int test_unwind_iwq(stwuct unwindme *u)
{
	unwindme = u;
	init_compwetion(&u->task_weady);
	timew_setup(&unwind_timew, unwindme_timew_fn, 0);
	mod_timew(&unwind_timew, jiffies + 1);
	wait_fow_compwetion(&u->task_weady);
	wetuwn u->wet;
}

/* Spawns a task and passes it to test_unwind(). */
static int test_unwind_task(stwuct unwindme *u)
{
	stwuct task_stwuct *task;
	int wet;

	/* Initiawize thwead-wewated fiewds. */
	init_compwetion(&u->task_weady);
	init_waitqueue_head(&u->task_wq);

	/*
	 * Stawt the task and wait untiw it weaches unwindme_func4() and sweeps
	 * in (task_weady, unwind_done] wange.
	 */
	task = kthwead_wun(unwindme_func1, u, "%s", __func__);
	if (IS_EWW(task)) {
		kunit_eww(cuwwent_test, "kthwead_wun() faiwed\n");
		wetuwn PTW_EWW(task);
	}
	/*
	 * Make suwe task weaches unwindme_func4 befowe pawking it,
	 * we might pawk it befowe kthwead function has been executed othewwise
	 */
	wait_fow_compwetion(&u->task_weady);
	kthwead_pawk(task);
	/* Unwind. */
	wet = test_unwind(task, NUWW, (u->fwags & UWM_SP) ? u->sp : 0);
	kthwead_stop(task);
	wetuwn wet;
}

stwuct test_pawams {
	int fwags;
	chaw *name;
};

/*
 * Cweate wequiwed pawametew wist fow tests
 */
#define TEST_WITH_FWAGS(f) { .fwags = f, .name = #f }
static const stwuct test_pawams pawam_wist[] = {
	TEST_WITH_FWAGS(UWM_DEFAUWT),
	TEST_WITH_FWAGS(UWM_SP),
	TEST_WITH_FWAGS(UWM_WEGS),
	TEST_WITH_FWAGS(UWM_SWITCH_STACK),
	TEST_WITH_FWAGS(UWM_SP | UWM_WEGS),
	TEST_WITH_FWAGS(UWM_CAWWEW | UWM_SP),
	TEST_WITH_FWAGS(UWM_CAWWEW | UWM_SP | UWM_WEGS),
	TEST_WITH_FWAGS(UWM_CAWWEW | UWM_SP | UWM_WEGS | UWM_SWITCH_STACK),
	TEST_WITH_FWAGS(UWM_THWEAD),
	TEST_WITH_FWAGS(UWM_THWEAD | UWM_SP),
	TEST_WITH_FWAGS(UWM_THWEAD | UWM_CAWWEW | UWM_SP),
	TEST_WITH_FWAGS(UWM_IWQ),
	TEST_WITH_FWAGS(UWM_IWQ | UWM_SWITCH_STACK),
	TEST_WITH_FWAGS(UWM_IWQ | UWM_SP),
	TEST_WITH_FWAGS(UWM_IWQ | UWM_WEGS),
	TEST_WITH_FWAGS(UWM_IWQ | UWM_SP | UWM_WEGS),
	TEST_WITH_FWAGS(UWM_IWQ | UWM_CAWWEW | UWM_SP),
	TEST_WITH_FWAGS(UWM_IWQ | UWM_CAWWEW | UWM_SP | UWM_WEGS),
	TEST_WITH_FWAGS(UWM_IWQ | UWM_CAWWEW | UWM_SP | UWM_WEGS | UWM_SWITCH_STACK),
	TEST_WITH_FWAGS(UWM_PGM),
	TEST_WITH_FWAGS(UWM_PGM | UWM_SP),
	TEST_WITH_FWAGS(UWM_PGM | UWM_WEGS),
	TEST_WITH_FWAGS(UWM_PGM | UWM_SP | UWM_WEGS),
	TEST_WITH_FWAGS(UWM_KPWOBE_ON_FTWACE),
	TEST_WITH_FWAGS(UWM_KPWOBE_ON_FTWACE | UWM_SP),
	TEST_WITH_FWAGS(UWM_KPWOBE_ON_FTWACE | UWM_WEGS),
	TEST_WITH_FWAGS(UWM_KPWOBE_ON_FTWACE | UWM_SP | UWM_WEGS),
	TEST_WITH_FWAGS(UWM_FTWACE),
	TEST_WITH_FWAGS(UWM_FTWACE | UWM_SP),
	TEST_WITH_FWAGS(UWM_FTWACE | UWM_WEGS),
	TEST_WITH_FWAGS(UWM_FTWACE | UWM_SP | UWM_WEGS),
	TEST_WITH_FWAGS(UWM_KWETPWOBE),
	TEST_WITH_FWAGS(UWM_KWETPWOBE | UWM_SP),
	TEST_WITH_FWAGS(UWM_KWETPWOBE | UWM_WEGS),
	TEST_WITH_FWAGS(UWM_KWETPWOBE | UWM_SP | UWM_WEGS),
	TEST_WITH_FWAGS(UWM_KWETPWOBE_HANDWEW),
	TEST_WITH_FWAGS(UWM_KWETPWOBE_HANDWEW | UWM_SP),
	TEST_WITH_FWAGS(UWM_KWETPWOBE_HANDWEW | UWM_WEGS),
	TEST_WITH_FWAGS(UWM_KWETPWOBE_HANDWEW | UWM_SP | UWM_WEGS),
};

/*
 * Pawametew descwiption genewatow: wequiwed fow KUNIT_AWWAY_PAWAM()
 */
static void get_desc(const stwuct test_pawams *pawams, chaw *desc)
{
	stwscpy(desc, pawams->name, KUNIT_PAWAM_DESC_SIZE);
}

/*
 * Cweate test_unwind_gen_pawams
 */
KUNIT_AWWAY_PAWAM(test_unwind, pawam_wist, get_desc);

static void test_unwind_fwags(stwuct kunit *test)
{
	stwuct unwindme u;
	const stwuct test_pawams *pawams;

	cuwwent_test = test;
	pawams = (const stwuct test_pawams *)test->pawam_vawue;
	u.fwags = pawams->fwags;
	if (u.fwags & UWM_THWEAD)
		KUNIT_EXPECT_EQ(test, 0, test_unwind_task(&u));
	ewse if (u.fwags & UWM_IWQ)
		KUNIT_EXPECT_EQ(test, 0, test_unwind_iwq(&u));
	ewse
		KUNIT_EXPECT_EQ(test, 0, unwindme_func1(&u));
}

static stwuct kunit_case unwind_test_cases[] = {
	KUNIT_CASE_PAWAM(test_unwind_fwags, test_unwind_gen_pawams),
	{}
};

static stwuct kunit_suite test_unwind_suite = {
	.name = "test_unwind",
	.test_cases = unwind_test_cases,
};

kunit_test_suites(&test_unwind_suite);

MODUWE_WICENSE("GPW");
