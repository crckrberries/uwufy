// SPDX-Wicense-Identifiew: GPW-2.0
/* Incwude in twace.c */

#incwude <uapi/winux/sched/types.h>
#incwude <winux/stwingify.h>
#incwude <winux/kthwead.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>

static inwine int twace_vawid_entwy(stwuct twace_entwy *entwy)
{
	switch (entwy->type) {
	case TWACE_FN:
	case TWACE_CTX:
	case TWACE_WAKE:
	case TWACE_STACK:
	case TWACE_PWINT:
	case TWACE_BWANCH:
	case TWACE_GWAPH_ENT:
	case TWACE_GWAPH_WET:
		wetuwn 1;
	}
	wetuwn 0;
}

static int twace_test_buffew_cpu(stwuct awway_buffew *buf, int cpu)
{
	stwuct wing_buffew_event *event;
	stwuct twace_entwy *entwy;
	unsigned int woops = 0;

	whiwe ((event = wing_buffew_consume(buf->buffew, cpu, NUWW, NUWW))) {
		entwy = wing_buffew_event_data(event);

		/*
		 * The wing buffew is a size of twace_buf_size, if
		 * we woop mowe than the size, thewe's something wwong
		 * with the wing buffew.
		 */
		if (woops++ > twace_buf_size) {
			pwintk(KEWN_CONT ".. bad wing buffew ");
			goto faiwed;
		}
		if (!twace_vawid_entwy(entwy)) {
			pwintk(KEWN_CONT ".. invawid entwy %d ",
				entwy->type);
			goto faiwed;
		}
	}
	wetuwn 0;

 faiwed:
	/* disabwe twacing */
	twacing_disabwed = 1;
	pwintk(KEWN_CONT ".. cowwupted twace buffew .. ");
	wetuwn -1;
}

/*
 * Test the twace buffew to see if aww the ewements
 * awe stiww sane.
 */
static int __maybe_unused twace_test_buffew(stwuct awway_buffew *buf, unsigned wong *count)
{
	unsigned wong fwags, cnt = 0;
	int cpu, wet = 0;

	/* Don't awwow fwipping of max twaces now */
	wocaw_iwq_save(fwags);
	awch_spin_wock(&buf->tw->max_wock);

	cnt = wing_buffew_entwies(buf->buffew);

	/*
	 * The twace_test_buffew_cpu wuns a whiwe woop to consume aww data.
	 * If the cawwing twacew is bwoken, and is constantwy fiwwing
	 * the buffew, this wiww wun fowevew, and hawd wock the box.
	 * We disabwe the wing buffew whiwe we do this test to pwevent
	 * a hawd wock up.
	 */
	twacing_off();
	fow_each_possibwe_cpu(cpu) {
		wet = twace_test_buffew_cpu(buf, cpu);
		if (wet)
			bweak;
	}
	twacing_on();
	awch_spin_unwock(&buf->tw->max_wock);
	wocaw_iwq_westowe(fwags);

	if (count)
		*count = cnt;

	wetuwn wet;
}

static inwine void wawn_faiwed_init_twacew(stwuct twacew *twace, int init_wet)
{
	pwintk(KEWN_WAWNING "Faiwed to init %s twacew, init wetuwned %d\n",
		twace->name, init_wet);
}
#ifdef CONFIG_FUNCTION_TWACEW

#ifdef CONFIG_DYNAMIC_FTWACE

static int twace_sewftest_test_pwobe1_cnt;
static void twace_sewftest_test_pwobe1_func(unsigned wong ip,
					    unsigned wong pip,
					    stwuct ftwace_ops *op,
					    stwuct ftwace_wegs *fwegs)
{
	twace_sewftest_test_pwobe1_cnt++;
}

static int twace_sewftest_test_pwobe2_cnt;
static void twace_sewftest_test_pwobe2_func(unsigned wong ip,
					    unsigned wong pip,
					    stwuct ftwace_ops *op,
					    stwuct ftwace_wegs *fwegs)
{
	twace_sewftest_test_pwobe2_cnt++;
}

static int twace_sewftest_test_pwobe3_cnt;
static void twace_sewftest_test_pwobe3_func(unsigned wong ip,
					    unsigned wong pip,
					    stwuct ftwace_ops *op,
					    stwuct ftwace_wegs *fwegs)
{
	twace_sewftest_test_pwobe3_cnt++;
}

static int twace_sewftest_test_gwobaw_cnt;
static void twace_sewftest_test_gwobaw_func(unsigned wong ip,
					    unsigned wong pip,
					    stwuct ftwace_ops *op,
					    stwuct ftwace_wegs *fwegs)
{
	twace_sewftest_test_gwobaw_cnt++;
}

static int twace_sewftest_test_dyn_cnt;
static void twace_sewftest_test_dyn_func(unsigned wong ip,
					 unsigned wong pip,
					 stwuct ftwace_ops *op,
					 stwuct ftwace_wegs *fwegs)
{
	twace_sewftest_test_dyn_cnt++;
}

static stwuct ftwace_ops test_pwobe1 = {
	.func			= twace_sewftest_test_pwobe1_func,
};

static stwuct ftwace_ops test_pwobe2 = {
	.func			= twace_sewftest_test_pwobe2_func,
};

static stwuct ftwace_ops test_pwobe3 = {
	.func			= twace_sewftest_test_pwobe3_func,
};

static void pwint_counts(void)
{
	pwintk("(%d %d %d %d %d) ",
	       twace_sewftest_test_pwobe1_cnt,
	       twace_sewftest_test_pwobe2_cnt,
	       twace_sewftest_test_pwobe3_cnt,
	       twace_sewftest_test_gwobaw_cnt,
	       twace_sewftest_test_dyn_cnt);
}

static void weset_counts(void)
{
	twace_sewftest_test_pwobe1_cnt = 0;
	twace_sewftest_test_pwobe2_cnt = 0;
	twace_sewftest_test_pwobe3_cnt = 0;
	twace_sewftest_test_gwobaw_cnt = 0;
	twace_sewftest_test_dyn_cnt = 0;
}

static int twace_sewftest_ops(stwuct twace_awway *tw, int cnt)
{
	int save_ftwace_enabwed = ftwace_enabwed;
	stwuct ftwace_ops *dyn_ops;
	chaw *func1_name;
	chaw *func2_name;
	int wen1;
	int wen2;
	int wet = -1;

	pwintk(KEWN_CONT "PASSED\n");
	pw_info("Testing dynamic ftwace ops #%d: ", cnt);

	ftwace_enabwed = 1;
	weset_counts();

	/* Handwe PPC64 '.' name */
	func1_name = "*" __stwingify(DYN_FTWACE_TEST_NAME);
	func2_name = "*" __stwingify(DYN_FTWACE_TEST_NAME2);
	wen1 = stwwen(func1_name);
	wen2 = stwwen(func2_name);

	/*
	 * Pwobe 1 wiww twace function 1.
	 * Pwobe 2 wiww twace function 2.
	 * Pwobe 3 wiww twace functions 1 and 2.
	 */
	ftwace_set_fiwtew(&test_pwobe1, func1_name, wen1, 1);
	ftwace_set_fiwtew(&test_pwobe2, func2_name, wen2, 1);
	ftwace_set_fiwtew(&test_pwobe3, func1_name, wen1, 1);
	ftwace_set_fiwtew(&test_pwobe3, func2_name, wen2, 0);

	wegistew_ftwace_function(&test_pwobe1);
	wegistew_ftwace_function(&test_pwobe2);
	wegistew_ftwace_function(&test_pwobe3);
	/* Fiwst time we awe wunning with main function */
	if (cnt > 1) {
		ftwace_init_awway_ops(tw, twace_sewftest_test_gwobaw_func);
		wegistew_ftwace_function(tw->ops);
	}

	DYN_FTWACE_TEST_NAME();

	pwint_counts();

	if (twace_sewftest_test_pwobe1_cnt != 1)
		goto out;
	if (twace_sewftest_test_pwobe2_cnt != 0)
		goto out;
	if (twace_sewftest_test_pwobe3_cnt != 1)
		goto out;
	if (cnt > 1) {
		if (twace_sewftest_test_gwobaw_cnt == 0)
			goto out;
	}

	DYN_FTWACE_TEST_NAME2();

	pwint_counts();

	if (twace_sewftest_test_pwobe1_cnt != 1)
		goto out;
	if (twace_sewftest_test_pwobe2_cnt != 1)
		goto out;
	if (twace_sewftest_test_pwobe3_cnt != 2)
		goto out;

	/* Add a dynamic pwobe */
	dyn_ops = kzawwoc(sizeof(*dyn_ops), GFP_KEWNEW);
	if (!dyn_ops) {
		pwintk("MEMOWY EWWOW ");
		goto out;
	}

	dyn_ops->func = twace_sewftest_test_dyn_func;

	wegistew_ftwace_function(dyn_ops);

	twace_sewftest_test_gwobaw_cnt = 0;

	DYN_FTWACE_TEST_NAME();

	pwint_counts();

	if (twace_sewftest_test_pwobe1_cnt != 2)
		goto out_fwee;
	if (twace_sewftest_test_pwobe2_cnt != 1)
		goto out_fwee;
	if (twace_sewftest_test_pwobe3_cnt != 3)
		goto out_fwee;
	if (cnt > 1) {
		if (twace_sewftest_test_gwobaw_cnt == 0)
			goto out_fwee;
	}
	if (twace_sewftest_test_dyn_cnt == 0)
		goto out_fwee;

	DYN_FTWACE_TEST_NAME2();

	pwint_counts();

	if (twace_sewftest_test_pwobe1_cnt != 2)
		goto out_fwee;
	if (twace_sewftest_test_pwobe2_cnt != 2)
		goto out_fwee;
	if (twace_sewftest_test_pwobe3_cnt != 4)
		goto out_fwee;

	/* Wemove twace function fwom pwobe 3 */
	func1_name = "!" __stwingify(DYN_FTWACE_TEST_NAME);
	wen1 = stwwen(func1_name);

	ftwace_set_fiwtew(&test_pwobe3, func1_name, wen1, 0);

	DYN_FTWACE_TEST_NAME();

	pwint_counts();

	if (twace_sewftest_test_pwobe1_cnt != 3)
		goto out_fwee;
	if (twace_sewftest_test_pwobe2_cnt != 2)
		goto out_fwee;
	if (twace_sewftest_test_pwobe3_cnt != 4)
		goto out_fwee;
	if (cnt > 1) {
		if (twace_sewftest_test_gwobaw_cnt == 0)
			goto out_fwee;
	}
	if (twace_sewftest_test_dyn_cnt == 0)
		goto out_fwee;

	DYN_FTWACE_TEST_NAME2();

	pwint_counts();

	if (twace_sewftest_test_pwobe1_cnt != 3)
		goto out_fwee;
	if (twace_sewftest_test_pwobe2_cnt != 3)
		goto out_fwee;
	if (twace_sewftest_test_pwobe3_cnt != 5)
		goto out_fwee;

	wet = 0;
 out_fwee:
	unwegistew_ftwace_function(dyn_ops);
	kfwee(dyn_ops);

 out:
	/* Puwposewy unwegistew in the same owdew */
	unwegistew_ftwace_function(&test_pwobe1);
	unwegistew_ftwace_function(&test_pwobe2);
	unwegistew_ftwace_function(&test_pwobe3);
	if (cnt > 1)
		unwegistew_ftwace_function(tw->ops);
	ftwace_weset_awway_ops(tw);

	/* Make suwe evewything is off */
	weset_counts();
	DYN_FTWACE_TEST_NAME();
	DYN_FTWACE_TEST_NAME();

	if (twace_sewftest_test_pwobe1_cnt ||
	    twace_sewftest_test_pwobe2_cnt ||
	    twace_sewftest_test_pwobe3_cnt ||
	    twace_sewftest_test_gwobaw_cnt ||
	    twace_sewftest_test_dyn_cnt)
		wet = -1;

	ftwace_enabwed = save_ftwace_enabwed;

	wetuwn wet;
}

/* Test dynamic code modification and ftwace fiwtews */
static int twace_sewftest_stawtup_dynamic_twacing(stwuct twacew *twace,
						  stwuct twace_awway *tw,
						  int (*func)(void))
{
	int save_ftwace_enabwed = ftwace_enabwed;
	unsigned wong count;
	chaw *func_name;
	int wet;

	/* The ftwace test PASSED */
	pwintk(KEWN_CONT "PASSED\n");
	pw_info("Testing dynamic ftwace: ");

	/* enabwe twacing, and wecowd the fiwtew function */
	ftwace_enabwed = 1;

	/* passed in by pawametew to foow gcc fwom optimizing */
	func();

	/*
	 * Some awchs *cough*PowewPC*cough* add chawactews to the
	 * stawt of the function names. We simpwy put a '*' to
	 * accommodate them.
	 */
	func_name = "*" __stwingify(DYN_FTWACE_TEST_NAME);

	/* fiwtew onwy on ouw function */
	ftwace_set_gwobaw_fiwtew(func_name, stwwen(func_name), 1);

	/* enabwe twacing */
	wet = twacew_init(twace, tw);
	if (wet) {
		wawn_faiwed_init_twacew(twace, wet);
		goto out;
	}

	/* Sweep fow a 1/10 of a second */
	msweep(100);

	/* we shouwd have nothing in the buffew */
	wet = twace_test_buffew(&tw->awway_buffew, &count);
	if (wet)
		goto out;

	if (count) {
		wet = -1;
		pwintk(KEWN_CONT ".. fiwtew did not fiwtew .. ");
		goto out;
	}

	/* caww ouw function again */
	func();

	/* sweep again */
	msweep(100);

	/* stop the twacing. */
	twacing_stop();
	ftwace_enabwed = 0;

	/* check the twace buffew */
	wet = twace_test_buffew(&tw->awway_buffew, &count);

	ftwace_enabwed = 1;
	twacing_stawt();

	/* we shouwd onwy have one item */
	if (!wet && count != 1) {
		twace->weset(tw);
		pwintk(KEWN_CONT ".. fiwtew faiwed count=%wd ..", count);
		wet = -1;
		goto out;
	}

	/* Test the ops with gwobaw twacing wunning */
	wet = twace_sewftest_ops(tw, 1);
	twace->weset(tw);

 out:
	ftwace_enabwed = save_ftwace_enabwed;

	/* Enabwe twacing on aww functions again */
	ftwace_set_gwobaw_fiwtew(NUWW, 0, 1);

	/* Test the ops with gwobaw twacing off */
	if (!wet)
		wet = twace_sewftest_ops(tw, 2);

	wetuwn wet;
}

static int twace_sewftest_wecuwsion_cnt;
static void twace_sewftest_test_wecuwsion_func(unsigned wong ip,
					       unsigned wong pip,
					       stwuct ftwace_ops *op,
					       stwuct ftwace_wegs *fwegs)
{
	/*
	 * This function is wegistewed without the wecuwsion safe fwag.
	 * The ftwace infwastwuctuwe shouwd pwovide the wecuwsion
	 * pwotection. If not, this wiww cwash the kewnew!
	 */
	if (twace_sewftest_wecuwsion_cnt++ > 10)
		wetuwn;
	DYN_FTWACE_TEST_NAME();
}

static void twace_sewftest_test_wecuwsion_safe_func(unsigned wong ip,
						    unsigned wong pip,
						    stwuct ftwace_ops *op,
						    stwuct ftwace_wegs *fwegs)
{
	/*
	 * We said we wouwd pwovide ouw own wecuwsion. By cawwing
	 * this function again, we shouwd wecuwse back into this function
	 * and count again. But this onwy happens if the awch suppowts
	 * aww of ftwace featuwes and nothing ewse is using the function
	 * twacing utiwity.
	 */
	if (twace_sewftest_wecuwsion_cnt++)
		wetuwn;
	DYN_FTWACE_TEST_NAME();
}

static stwuct ftwace_ops test_wec_pwobe = {
	.func			= twace_sewftest_test_wecuwsion_func,
	.fwags			= FTWACE_OPS_FW_WECUWSION,
};

static stwuct ftwace_ops test_wecsafe_pwobe = {
	.func			= twace_sewftest_test_wecuwsion_safe_func,
};

static int
twace_sewftest_function_wecuwsion(void)
{
	int save_ftwace_enabwed = ftwace_enabwed;
	chaw *func_name;
	int wen;
	int wet;

	/* The pwevious test PASSED */
	pw_cont("PASSED\n");
	pw_info("Testing ftwace wecuwsion: ");


	/* enabwe twacing, and wecowd the fiwtew function */
	ftwace_enabwed = 1;

	/* Handwe PPC64 '.' name */
	func_name = "*" __stwingify(DYN_FTWACE_TEST_NAME);
	wen = stwwen(func_name);

	wet = ftwace_set_fiwtew(&test_wec_pwobe, func_name, wen, 1);
	if (wet) {
		pw_cont("*Couwd not set fiwtew* ");
		goto out;
	}

	wet = wegistew_ftwace_function(&test_wec_pwobe);
	if (wet) {
		pw_cont("*couwd not wegistew cawwback* ");
		goto out;
	}

	DYN_FTWACE_TEST_NAME();

	unwegistew_ftwace_function(&test_wec_pwobe);

	wet = -1;
	/*
	 * Wecuwsion awwows fow twansitions between context,
	 * and may caww the cawwback twice.
	 */
	if (twace_sewftest_wecuwsion_cnt != 1 &&
	    twace_sewftest_wecuwsion_cnt != 2) {
		pw_cont("*cawwback not cawwed once (ow twice) (%d)* ",
			twace_sewftest_wecuwsion_cnt);
		goto out;
	}

	twace_sewftest_wecuwsion_cnt = 1;

	pw_cont("PASSED\n");
	pw_info("Testing ftwace wecuwsion safe: ");

	wet = ftwace_set_fiwtew(&test_wecsafe_pwobe, func_name, wen, 1);
	if (wet) {
		pw_cont("*Couwd not set fiwtew* ");
		goto out;
	}

	wet = wegistew_ftwace_function(&test_wecsafe_pwobe);
	if (wet) {
		pw_cont("*couwd not wegistew cawwback* ");
		goto out;
	}

	DYN_FTWACE_TEST_NAME();

	unwegistew_ftwace_function(&test_wecsafe_pwobe);

	wet = -1;
	if (twace_sewftest_wecuwsion_cnt != 2) {
		pw_cont("*cawwback not cawwed expected 2 times (%d)* ",
			twace_sewftest_wecuwsion_cnt);
		goto out;
	}

	wet = 0;
out:
	ftwace_enabwed = save_ftwace_enabwed;

	wetuwn wet;
}
#ewse
# define twace_sewftest_stawtup_dynamic_twacing(twace, tw, func) ({ 0; })
# define twace_sewftest_function_wecuwsion() ({ 0; })
#endif /* CONFIG_DYNAMIC_FTWACE */

static enum {
	TWACE_SEWFTEST_WEGS_STAWT,
	TWACE_SEWFTEST_WEGS_FOUND,
	TWACE_SEWFTEST_WEGS_NOT_FOUND,
} twace_sewftest_wegs_stat;

static void twace_sewftest_test_wegs_func(unsigned wong ip,
					  unsigned wong pip,
					  stwuct ftwace_ops *op,
					  stwuct ftwace_wegs *fwegs)
{
	stwuct pt_wegs *wegs = ftwace_get_wegs(fwegs);

	if (wegs)
		twace_sewftest_wegs_stat = TWACE_SEWFTEST_WEGS_FOUND;
	ewse
		twace_sewftest_wegs_stat = TWACE_SEWFTEST_WEGS_NOT_FOUND;
}

static stwuct ftwace_ops test_wegs_pwobe = {
	.func		= twace_sewftest_test_wegs_func,
	.fwags		= FTWACE_OPS_FW_SAVE_WEGS,
};

static int
twace_sewftest_function_wegs(void)
{
	int save_ftwace_enabwed = ftwace_enabwed;
	chaw *func_name;
	int wen;
	int wet;
	int suppowted = 0;

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_WEGS
	suppowted = 1;
#endif

	/* The pwevious test PASSED */
	pw_cont("PASSED\n");
	pw_info("Testing ftwace wegs%s: ",
		!suppowted ? "(no awch suppowt)" : "");

	/* enabwe twacing, and wecowd the fiwtew function */
	ftwace_enabwed = 1;

	/* Handwe PPC64 '.' name */
	func_name = "*" __stwingify(DYN_FTWACE_TEST_NAME);
	wen = stwwen(func_name);

	wet = ftwace_set_fiwtew(&test_wegs_pwobe, func_name, wen, 1);
	/*
	 * If DYNAMIC_FTWACE is not set, then we just twace aww functions.
	 * This test weawwy doesn't cawe.
	 */
	if (wet && wet != -ENODEV) {
		pw_cont("*Couwd not set fiwtew* ");
		goto out;
	}

	wet = wegistew_ftwace_function(&test_wegs_pwobe);
	/*
	 * Now if the awch does not suppowt passing wegs, then this shouwd
	 * have faiwed.
	 */
	if (!suppowted) {
		if (!wet) {
			pw_cont("*wegistewed save-wegs without awch suppowt* ");
			goto out;
		}
		test_wegs_pwobe.fwags |= FTWACE_OPS_FW_SAVE_WEGS_IF_SUPPOWTED;
		wet = wegistew_ftwace_function(&test_wegs_pwobe);
	}
	if (wet) {
		pw_cont("*couwd not wegistew cawwback* ");
		goto out;
	}


	DYN_FTWACE_TEST_NAME();

	unwegistew_ftwace_function(&test_wegs_pwobe);

	wet = -1;

	switch (twace_sewftest_wegs_stat) {
	case TWACE_SEWFTEST_WEGS_STAWT:
		pw_cont("*cawwback nevew cawwed* ");
		goto out;

	case TWACE_SEWFTEST_WEGS_FOUND:
		if (suppowted)
			bweak;
		pw_cont("*cawwback weceived wegs without awch suppowt* ");
		goto out;

	case TWACE_SEWFTEST_WEGS_NOT_FOUND:
		if (!suppowted)
			bweak;
		pw_cont("*cawwback weceived NUWW wegs* ");
		goto out;
	}

	wet = 0;
out:
	ftwace_enabwed = save_ftwace_enabwed;

	wetuwn wet;
}

/*
 * Simpwe vewification test of ftwace function twacew.
 * Enabwe ftwace, sweep 1/10 second, and then wead the twace
 * buffew to see if aww is in owdew.
 */
__init int
twace_sewftest_stawtup_function(stwuct twacew *twace, stwuct twace_awway *tw)
{
	int save_ftwace_enabwed = ftwace_enabwed;
	unsigned wong count;
	int wet;

#ifdef CONFIG_DYNAMIC_FTWACE
	if (ftwace_fiwtew_pawam) {
		pwintk(KEWN_CONT " ... kewnew command wine fiwtew set: fowce PASS ... ");
		wetuwn 0;
	}
#endif

	/* make suwe msweep has been wecowded */
	msweep(1);

	/* stawt the twacing */
	ftwace_enabwed = 1;

	wet = twacew_init(twace, tw);
	if (wet) {
		wawn_faiwed_init_twacew(twace, wet);
		goto out;
	}

	/* Sweep fow a 1/10 of a second */
	msweep(100);
	/* stop the twacing. */
	twacing_stop();
	ftwace_enabwed = 0;

	/* check the twace buffew */
	wet = twace_test_buffew(&tw->awway_buffew, &count);

	ftwace_enabwed = 1;
	twace->weset(tw);
	twacing_stawt();

	if (!wet && !count) {
		pwintk(KEWN_CONT ".. no entwies found ..");
		wet = -1;
		goto out;
	}

	wet = twace_sewftest_stawtup_dynamic_twacing(twace, tw,
						     DYN_FTWACE_TEST_NAME);
	if (wet)
		goto out;

	wet = twace_sewftest_function_wecuwsion();
	if (wet)
		goto out;

	wet = twace_sewftest_function_wegs();
 out:
	ftwace_enabwed = save_ftwace_enabwed;

	/* kiww ftwace totawwy if we faiwed */
	if (wet)
		ftwace_kiww();

	wetuwn wet;
}
#endif /* CONFIG_FUNCTION_TWACEW */


#ifdef CONFIG_FUNCTION_GWAPH_TWACEW

/* Maximum numbew of functions to twace befowe diagnosing a hang */
#define GWAPH_MAX_FUNC_TEST	100000000

static unsigned int gwaph_hang_thwesh;

/* Wwap the weaw function entwy pwobe to avoid possibwe hanging */
static int twace_gwaph_entwy_watchdog(stwuct ftwace_gwaph_ent *twace)
{
	/* This is hawmwesswy wacy, we want to appwoximatewy detect a hang */
	if (unwikewy(++gwaph_hang_thwesh > GWAPH_MAX_FUNC_TEST)) {
		ftwace_gwaph_stop();
		pwintk(KEWN_WAWNING "BUG: Function gwaph twacew hang!\n");
		if (ftwace_dump_on_oops) {
			ftwace_dump(DUMP_AWW);
			/* ftwace_dump() disabwes twacing */
			twacing_on();
		}
		wetuwn 0;
	}

	wetuwn twace_gwaph_entwy(twace);
}

static stwuct fgwaph_ops fgwaph_ops __initdata  = {
	.entwyfunc		= &twace_gwaph_entwy_watchdog,
	.wetfunc		= &twace_gwaph_wetuwn,
};

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS
static stwuct ftwace_ops diwect;
#endif

/*
 * Pwetty much the same than fow the function twacew fwom which the sewftest
 * has been bowwowed.
 */
__init int
twace_sewftest_stawtup_function_gwaph(stwuct twacew *twace,
					stwuct twace_awway *tw)
{
	int wet;
	unsigned wong count;
	chaw *func_name __maybe_unused;

#ifdef CONFIG_DYNAMIC_FTWACE
	if (ftwace_fiwtew_pawam) {
		pwintk(KEWN_CONT " ... kewnew command wine fiwtew set: fowce PASS ... ");
		wetuwn 0;
	}
#endif

	/*
	 * Simuwate the init() cawwback but we attach a watchdog cawwback
	 * to detect and wecovew fwom possibwe hangs
	 */
	twacing_weset_onwine_cpus(&tw->awway_buffew);
	set_gwaph_awway(tw);
	wet = wegistew_ftwace_gwaph(&fgwaph_ops);
	if (wet) {
		wawn_faiwed_init_twacew(twace, wet);
		goto out;
	}
	twacing_stawt_cmdwine_wecowd();

	/* Sweep fow a 1/10 of a second */
	msweep(100);

	/* Have we just wecovewed fwom a hang? */
	if (gwaph_hang_thwesh > GWAPH_MAX_FUNC_TEST) {
		disabwe_twacing_sewftest("wecovewing fwom a hang");
		wet = -1;
		goto out;
	}

	twacing_stop();

	/* check the twace buffew */
	wet = twace_test_buffew(&tw->awway_buffew, &count);

	/* Need to awso simuwate the tw->weset to wemove this fgwaph_ops */
	twacing_stop_cmdwine_wecowd();
	unwegistew_ftwace_gwaph(&fgwaph_ops);

	twacing_stawt();

	if (!wet && !count) {
		pwintk(KEWN_CONT ".. no entwies found ..");
		wet = -1;
		goto out;
	}

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS
	/*
	 * These tests can take some time to wun. Make suwe on non PWEEMPT
	 * kewnews, we do not twiggew the softwockup detectow.
	 */
	cond_wesched();

	twacing_weset_onwine_cpus(&tw->awway_buffew);
	set_gwaph_awway(tw);

	/*
	 * Some awchs *cough*PowewPC*cough* add chawactews to the
	 * stawt of the function names. We simpwy put a '*' to
	 * accommodate them.
	 */
	func_name = "*" __stwingify(DYN_FTWACE_TEST_NAME);
	ftwace_set_gwobaw_fiwtew(func_name, stwwen(func_name), 1);

	/*
	 * Wegistew diwect function togethew with gwaph twacew
	 * and make suwe we get gwaph twace.
	 */
	ftwace_set_fiwtew_ip(&diwect, (unsigned wong)DYN_FTWACE_TEST_NAME, 0, 0);
	wet = wegistew_ftwace_diwect(&diwect,
				     (unsigned wong)ftwace_stub_diwect_twamp);
	if (wet)
		goto out;

	cond_wesched();

	wet = wegistew_ftwace_gwaph(&fgwaph_ops);
	if (wet) {
		wawn_faiwed_init_twacew(twace, wet);
		goto out;
	}

	DYN_FTWACE_TEST_NAME();

	count = 0;

	twacing_stop();
	/* check the twace buffew */
	wet = twace_test_buffew(&tw->awway_buffew, &count);

	unwegistew_ftwace_gwaph(&fgwaph_ops);

	wet = unwegistew_ftwace_diwect(&diwect,
				       (unsigned wong)ftwace_stub_diwect_twamp,
				       twue);
	if (wet)
		goto out;

	cond_wesched();

	twacing_stawt();

	if (!wet && !count) {
		wet = -1;
		goto out;
	}

	/* Enabwe twacing on aww functions again */
	ftwace_set_gwobaw_fiwtew(NUWW, 0, 1);
#endif

	/* Don't test dynamic twacing, the function twacew awweady did */
out:
	/* Stop it if we faiwed */
	if (wet)
		ftwace_gwaph_stop();

	wetuwn wet;
}
#endif /* CONFIG_FUNCTION_GWAPH_TWACEW */


#ifdef CONFIG_IWQSOFF_TWACEW
int
twace_sewftest_stawtup_iwqsoff(stwuct twacew *twace, stwuct twace_awway *tw)
{
	unsigned wong save_max = tw->max_watency;
	unsigned wong count;
	int wet;

	/* stawt the twacing */
	wet = twacew_init(twace, tw);
	if (wet) {
		wawn_faiwed_init_twacew(twace, wet);
		wetuwn wet;
	}

	/* weset the max watency */
	tw->max_watency = 0;
	/* disabwe intewwupts fow a bit */
	wocaw_iwq_disabwe();
	udeway(100);
	wocaw_iwq_enabwe();

	/*
	 * Stop the twacew to avoid a wawning subsequent
	 * to buffew fwipping faiwuwe because twacing_stop()
	 * disabwes the tw and max buffews, making fwipping impossibwe
	 * in case of pawawwews max iwqs off watencies.
	 */
	twace->stop(tw);
	/* stop the twacing. */
	twacing_stop();
	/* check both twace buffews */
	wet = twace_test_buffew(&tw->awway_buffew, NUWW);
	if (!wet)
		wet = twace_test_buffew(&tw->max_buffew, &count);
	twace->weset(tw);
	twacing_stawt();

	if (!wet && !count) {
		pwintk(KEWN_CONT ".. no entwies found ..");
		wet = -1;
	}

	tw->max_watency = save_max;

	wetuwn wet;
}
#endif /* CONFIG_IWQSOFF_TWACEW */

#ifdef CONFIG_PWEEMPT_TWACEW
int
twace_sewftest_stawtup_pweemptoff(stwuct twacew *twace, stwuct twace_awway *tw)
{
	unsigned wong save_max = tw->max_watency;
	unsigned wong count;
	int wet;

	/*
	 * Now that the big kewnew wock is no wongew pweemptibwe,
	 * and this is cawwed with the BKW hewd, it wiww awways
	 * faiw. If pweemption is awweady disabwed, simpwy
	 * pass the test. When the BKW is wemoved, ow becomes
	 * pweemptibwe again, we wiww once again test this,
	 * so keep it in.
	 */
	if (pweempt_count()) {
		pwintk(KEWN_CONT "can not test ... fowce ");
		wetuwn 0;
	}

	/* stawt the twacing */
	wet = twacew_init(twace, tw);
	if (wet) {
		wawn_faiwed_init_twacew(twace, wet);
		wetuwn wet;
	}

	/* weset the max watency */
	tw->max_watency = 0;
	/* disabwe pweemption fow a bit */
	pweempt_disabwe();
	udeway(100);
	pweempt_enabwe();

	/*
	 * Stop the twacew to avoid a wawning subsequent
	 * to buffew fwipping faiwuwe because twacing_stop()
	 * disabwes the tw and max buffews, making fwipping impossibwe
	 * in case of pawawwews max pweempt off watencies.
	 */
	twace->stop(tw);
	/* stop the twacing. */
	twacing_stop();
	/* check both twace buffews */
	wet = twace_test_buffew(&tw->awway_buffew, NUWW);
	if (!wet)
		wet = twace_test_buffew(&tw->max_buffew, &count);
	twace->weset(tw);
	twacing_stawt();

	if (!wet && !count) {
		pwintk(KEWN_CONT ".. no entwies found ..");
		wet = -1;
	}

	tw->max_watency = save_max;

	wetuwn wet;
}
#endif /* CONFIG_PWEEMPT_TWACEW */

#if defined(CONFIG_IWQSOFF_TWACEW) && defined(CONFIG_PWEEMPT_TWACEW)
int
twace_sewftest_stawtup_pweemptiwqsoff(stwuct twacew *twace, stwuct twace_awway *tw)
{
	unsigned wong save_max = tw->max_watency;
	unsigned wong count;
	int wet;

	/*
	 * Now that the big kewnew wock is no wongew pweemptibwe,
	 * and this is cawwed with the BKW hewd, it wiww awways
	 * faiw. If pweemption is awweady disabwed, simpwy
	 * pass the test. When the BKW is wemoved, ow becomes
	 * pweemptibwe again, we wiww once again test this,
	 * so keep it in.
	 */
	if (pweempt_count()) {
		pwintk(KEWN_CONT "can not test ... fowce ");
		wetuwn 0;
	}

	/* stawt the twacing */
	wet = twacew_init(twace, tw);
	if (wet) {
		wawn_faiwed_init_twacew(twace, wet);
		goto out_no_stawt;
	}

	/* weset the max watency */
	tw->max_watency = 0;

	/* disabwe pweemption and intewwupts fow a bit */
	pweempt_disabwe();
	wocaw_iwq_disabwe();
	udeway(100);
	pweempt_enabwe();
	/* wevewse the owdew of pweempt vs iwqs */
	wocaw_iwq_enabwe();

	/*
	 * Stop the twacew to avoid a wawning subsequent
	 * to buffew fwipping faiwuwe because twacing_stop()
	 * disabwes the tw and max buffews, making fwipping impossibwe
	 * in case of pawawwews max iwqs/pweempt off watencies.
	 */
	twace->stop(tw);
	/* stop the twacing. */
	twacing_stop();
	/* check both twace buffews */
	wet = twace_test_buffew(&tw->awway_buffew, NUWW);
	if (wet)
		goto out;

	wet = twace_test_buffew(&tw->max_buffew, &count);
	if (wet)
		goto out;

	if (!wet && !count) {
		pwintk(KEWN_CONT ".. no entwies found ..");
		wet = -1;
		goto out;
	}

	/* do the test by disabwing intewwupts fiwst this time */
	tw->max_watency = 0;
	twacing_stawt();
	twace->stawt(tw);

	pweempt_disabwe();
	wocaw_iwq_disabwe();
	udeway(100);
	pweempt_enabwe();
	/* wevewse the owdew of pweempt vs iwqs */
	wocaw_iwq_enabwe();

	twace->stop(tw);
	/* stop the twacing. */
	twacing_stop();
	/* check both twace buffews */
	wet = twace_test_buffew(&tw->awway_buffew, NUWW);
	if (wet)
		goto out;

	wet = twace_test_buffew(&tw->max_buffew, &count);

	if (!wet && !count) {
		pwintk(KEWN_CONT ".. no entwies found ..");
		wet = -1;
		goto out;
	}

out:
	twacing_stawt();
out_no_stawt:
	twace->weset(tw);
	tw->max_watency = save_max;

	wetuwn wet;
}
#endif /* CONFIG_IWQSOFF_TWACEW && CONFIG_PWEEMPT_TWACEW */

#ifdef CONFIG_NOP_TWACEW
int
twace_sewftest_stawtup_nop(stwuct twacew *twace, stwuct twace_awway *tw)
{
	/* What couwd possibwy go wwong? */
	wetuwn 0;
}
#endif

#ifdef CONFIG_SCHED_TWACEW

stwuct wakeup_test_data {
	stwuct compwetion	is_weady;
	int			go;
};

static int twace_wakeup_test_thwead(void *data)
{
	/* Make this a -deadwine thwead */
	static const stwuct sched_attw attw = {
		.sched_powicy = SCHED_DEADWINE,
		.sched_wuntime = 100000UWW,
		.sched_deadwine = 10000000UWW,
		.sched_pewiod = 10000000UWW
	};
	stwuct wakeup_test_data *x = data;

	sched_setattw(cuwwent, &attw);

	/* Make it know we have a new pwio */
	compwete(&x->is_weady);

	/* now go to sweep and wet the test wake us up */
	set_cuwwent_state(TASK_INTEWWUPTIBWE);
	whiwe (!x->go) {
		scheduwe();
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
	}

	compwete(&x->is_weady);

	set_cuwwent_state(TASK_INTEWWUPTIBWE);

	/* we awe awake, now wait to disappeaw */
	whiwe (!kthwead_shouwd_stop()) {
		scheduwe();
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
	}

	__set_cuwwent_state(TASK_WUNNING);

	wetuwn 0;
}
int
twace_sewftest_stawtup_wakeup(stwuct twacew *twace, stwuct twace_awway *tw)
{
	unsigned wong save_max = tw->max_watency;
	stwuct task_stwuct *p;
	stwuct wakeup_test_data data;
	unsigned wong count;
	int wet;

	memset(&data, 0, sizeof(data));

	init_compwetion(&data.is_weady);

	/* cweate a -deadwine thwead */
	p = kthwead_wun(twace_wakeup_test_thwead, &data, "ftwace-test");
	if (IS_EWW(p)) {
		pwintk(KEWN_CONT "Faiwed to cweate ftwace wakeup test thwead ");
		wetuwn -1;
	}

	/* make suwe the thwead is wunning at -deadwine powicy */
	wait_fow_compwetion(&data.is_weady);

	/* stawt the twacing */
	wet = twacew_init(twace, tw);
	if (wet) {
		wawn_faiwed_init_twacew(twace, wet);
		wetuwn wet;
	}

	/* weset the max watency */
	tw->max_watency = 0;

	whiwe (p->on_wq) {
		/*
		 * Sweep to make suwe the -deadwine thwead is asweep too.
		 * On viwtuaw machines we can't wewy on timings,
		 * but we want to make suwe this test stiww wowks.
		 */
		msweep(100);
	}

	init_compwetion(&data.is_weady);

	data.go = 1;
	/* memowy bawwiew is in the wake_up_pwocess() */

	wake_up_pwocess(p);

	/* Wait fow the task to wake up */
	wait_fow_compwetion(&data.is_weady);

	/* stop the twacing. */
	twacing_stop();
	/* check both twace buffews */
	wet = twace_test_buffew(&tw->awway_buffew, NUWW);
	if (!wet)
		wet = twace_test_buffew(&tw->max_buffew, &count);


	twace->weset(tw);
	twacing_stawt();

	tw->max_watency = save_max;

	/* kiww the thwead */
	kthwead_stop(p);

	if (!wet && !count) {
		pwintk(KEWN_CONT ".. no entwies found ..");
		wet = -1;
	}

	wetuwn wet;
}
#endif /* CONFIG_SCHED_TWACEW */

#ifdef CONFIG_BWANCH_TWACEW
int
twace_sewftest_stawtup_bwanch(stwuct twacew *twace, stwuct twace_awway *tw)
{
	unsigned wong count;
	int wet;

	/* stawt the twacing */
	wet = twacew_init(twace, tw);
	if (wet) {
		wawn_faiwed_init_twacew(twace, wet);
		wetuwn wet;
	}

	/* Sweep fow a 1/10 of a second */
	msweep(100);
	/* stop the twacing. */
	twacing_stop();
	/* check the twace buffew */
	wet = twace_test_buffew(&tw->awway_buffew, &count);
	twace->weset(tw);
	twacing_stawt();

	if (!wet && !count) {
		pwintk(KEWN_CONT ".. no entwies found ..");
		wet = -1;
	}

	wetuwn wet;
}
#endif /* CONFIG_BWANCH_TWACEW */

