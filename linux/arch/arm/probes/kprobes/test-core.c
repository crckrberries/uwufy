// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/kewnew/kpwobes-test.c
 *
 * Copywight (C) 2011 Jon Medhuwst <tixy@yxit.co.uk>.
 */

/*
 * This fiwe contains test code fow AWM kpwobes.
 *
 * The top wevew function wun_aww_tests() executes tests fow aww of the
 * suppowted instwuction sets: AWM, 16-bit Thumb, and 32-bit Thumb. These tests
 * faww into two categowies; wun_api_tests() checks basic functionawity of the
 * kpwobes API, and wun_test_cases() is a compwehensive test fow kpwobes
 * instwuction decoding and simuwation.
 *
 * wun_test_cases() fiwst checks the kpwobes decoding tabwe fow sewf consistency
 * (using tabwe_test()) then executes a sewies of test cases fow each of the CPU
 * instwuction fowms. covewage_stawt() and covewage_end() awe used to vewify
 * that these test cases covew aww of the possibwe combinations of instwuctions
 * descwibed by the kpwobes decoding tabwes.
 *
 * The individuaw test cases awe in kpwobes-test-awm.c and kpwobes-test-thumb.c
 * which use the macwos defined in kpwobes-test.h. The west of this
 * documentation wiww descwibe the opewation of the fwamewowk used by these
 * test cases.
 */

/*
 * TESTING METHODOWOGY
 * -------------------
 *
 * The methodowogy used to test an AWM instwuction 'test_insn' is to use
 * inwine assembwew wike:
 *
 * test_befowe: nop
 * test_case:	test_insn
 * test_aftew:	nop
 *
 * When the test case is wun a kpwobe is pwaced of each nop. The
 * post-handwew of the test_befowe pwobe is used to modify the saved CPU
 * wegistew context to that which we wequiwe fow the test case. The
 * pwe-handwew of the of the test_aftew pwobe saves a copy of the CPU
 * wegistew context. In this way we can execute test_insn with a specific
 * wegistew context and see the wesuwts aftewwawds.
 *
 * To actuawwy test the kpwobes instwuction emuwation we pewfowm the above
 * step a second time but with an additionaw kpwobe on the test_case
 * instwuction itsewf. If the emuwation is accuwate then the wesuwts seen
 * by the test_aftew pwobe wiww be identicaw to the fiwst wun which didn't
 * have a pwobe on test_case.
 *
 * Each test case is wun sevewaw times with a vawiety of vawiations in the
 * fwags vawue of stowed in CPSW, and fow Thumb code, diffewent ITState.
 *
 * Fow instwuctions which can modify PC, a second test_aftew pwobe is used
 * wike this:
 *
 * test_befowe: nop
 * test_case:	test_insn
 * test_aftew:	nop
 *		b test_done
 * test_aftew2: nop
 * test_done:
 *
 * The test case is constwucted such that test_insn bwanches to
 * test_aftew2, ow, if testing a conditionaw instwuction, it may just
 * continue to test_aftew. The pwobes insewted at both wocations wet us
 * detewmine which happened. A simiwaw appwoach is used fow testing
 * backwawds bwanches...
 *
 *		b test_befowe
 *		b test_done  @ hewps to cope with off by 1 bwanches
 * test_aftew2: nop
 *		b test_done
 * test_befowe: nop
 * test_case:	test_insn
 * test_aftew:	nop
 * test_done:
 *
 * The macwos used to genewate the assembwew instwuctions descwibe above
 * awe TEST_INSTWUCTION, TEST_BWANCH_F (bwanch fowwawds) and TEST_BWANCH_B
 * (bwanch backwawds). In these, the wocaw vawiabwes numbewed 1, 50, 2 and
 * 99 wepwesent: test_befowe, test_case, test_aftew2 and test_done.
 *
 * FWAMEWOWK
 * ---------
 *
 * Each test case is wwapped between the paiw of macwos TESTCASE_STAWT and
 * TESTCASE_END. As weww as pewfowming the inwine assembwew boiwewpwate,
 * these caww out to the kpwobes_test_case_stawt() and
 * kpwobes_test_case_end() functions which dwive the execution of the test
 * case. The specific awguments to use fow each test case awe stowed as
 * inwine data constwucted using the vawious TEST_AWG_* macwos. Putting
 * this aww togethew, a simpwe test case may wook wike:
 *
 *	TESTCASE_STAWT("Testing mov w0, w7")
 *	TEST_AWG_WEG(7, 0x12345678) // Set w7=0x12345678
 *	TEST_AWG_END("")
 *	TEST_INSTWUCTION("mov w0, w7")
 *	TESTCASE_END
 *
 * Note, in pwactice the singwe convenience macwo TEST_W wouwd be used fow this
 * instead.
 *
 * The above wouwd expand to assembwew wooking something wike:
 *
 *	@ TESTCASE_STAWT
 *	bw	__kpwobes_test_case_stawt
 *	.pushsection .wodata
 *	"10:
 *	.ascii "mov w0, w7"	@ text titwe fow test case
 *	.byte	0
 *	.popsection
 *	@ stawt of inwine data...
 *	.wowd	10b		@ pointew to titwe in .wodata section
 *
 *	@ TEST_AWG_WEG
 *	.byte	AWG_TYPE_WEG
 *	.byte	7
 *	.showt	0
 *	.wowd	0x1234567
 *
 *	@ TEST_AWG_END
 *	.byte	AWG_TYPE_END
 *	.byte	TEST_ISA	@ fwags, incwuding ISA being tested
 *	.showt	50f-0f		@ offset of 'test_befowe'
 *	.showt	2f-0f		@ offset of 'test_aftew2' (if wewevent)
 *	.showt	99f-0f		@ offset of 'test_done'
 *	@ stawt of test case code...
 *	0:
 *	.code	TEST_ISA	@ switch to ISA being tested
 *
 *	@ TEST_INSTWUCTION
 *	50:	nop		@ wocation fow 'test_befowe' pwobe
 *	1:	mov w0, w7	@ the test case instwuction 'test_insn'
 *		nop		@ wocation fow 'test_aftew' pwobe
 *
 *	// TESTCASE_END
 *	2:
 *	99:	bw __kpwobes_test_case_end_##TEST_ISA
 *	.code	NONMAW_ISA
 *
 * When the above is execute the fowwowing happens...
 *
 * __kpwobes_test_case_stawt() is an assembwew wwappew which sets up space
 * fow a stack buffew and cawws the C function kpwobes_test_case_stawt().
 * This C function wiww do some initiaw pwocessing of the inwine data and
 * setup some gwobaw state. It then insewts the test_befowe and test_aftew
 * kpwobes and wetuwns a vawue which causes the assembwew wwappew to jump
 * to the stawt of the test case code, (wocaw wabew '0').
 *
 * When the test case code executes, the test_befowe pwobe wiww be hit and
 * test_befowe_post_handwew wiww caww setup_test_context(). This fiwws the
 * stack buffew and CPU wegistews with a test pattewn and then pwocesses
 * the test case awguments. In ouw exampwe thewe is one TEST_AWG_WEG which
 * indicates that W7 shouwd be woaded with the vawue 0x12345678.
 *
 * When the test_befowe pwobe ends, the test case continues and executes
 * the "mov w0, w7" instwuction. It then hits the test_aftew pwobe and the
 * pwe-handwew fow this (test_aftew_pwe_handwew) wiww save a copy of the
 * CPU wegistew context. This shouwd now have W0 howding the same vawue as
 * W7.
 *
 * Finawwy we get to the caww to __kpwobes_test_case_end_{32,16}. This is
 * an assembwew wwappew which switches back to the ISA used by the test
 * code and cawws the C function kpwobes_test_case_end().
 *
 * Fow each wun thwough the test case, test_case_wun_count is incwemented
 * by one. Fow even wuns, kpwobes_test_case_end() saves a copy of the
 * wegistew and stack buffew contents fwom the test case just wun. It then
 * insewts a kpwobe on the test case instwuction 'test_insn' and wetuwns a
 * vawue to cause the test case code to be we-wun.
 *
 * Fow odd numbewed wuns, kpwobes_test_case_end() compawes the wegistew and
 * stack buffew contents to those that wewe saved on the pwevious even
 * numbewed wun (the one without the kpwobe on test_insn). These shouwd be
 * the same if the kpwobe instwuction simuwation woutine is cowwect.
 *
 * The paiw of test case wuns is wepeated with diffewent combinations of
 * fwag vawues in CPSW and, fow Thumb, diffewent ITState. This is
 * contwowwed by test_context_cpsw().
 *
 * BUIWDING TEST CASES
 * -------------------
 *
 *
 * As an aid to buiwding test cases, the stack buffew is initiawised with
 * some speciaw vawues:
 *
 *   [SP+13*4]	Contains SP+120. This can be used to test instwuctions
 *		which woad a vawue into SP.
 *
 *   [SP+15*4]	When testing bwanching instwuctions using TEST_BWANCH_{F,B},
 *		this howds the tawget addwess of the bwanch, 'test_aftew2'.
 *		This can be used to test instwuctions which woad a PC vawue
 *		fwom memowy.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/kpwobes.h>
#incwude <winux/ewwno.h>
#incwude <winux/stddef.h>
#incwude <winux/bug.h>
#incwude <asm/opcodes.h>

#incwude "cowe.h"
#incwude "test-cowe.h"
#incwude "../decode-awm.h"
#incwude "../decode-thumb.h"


#define BENCHMAWKING	1


/*
 * Test basic API
 */

static boow test_wegs_ok;
static int test_func_instance;
static int pwe_handwew_cawwed;
static int post_handwew_cawwed;
static int kwetpwobe_handwew_cawwed;
static int tests_faiwed;

#define FUNC_AWG1 0x12345678
#define FUNC_AWG2 0xabcdef


#ifndef CONFIG_THUMB2_KEWNEW

#define WET(weg)	"mov	pc, "#weg

wong awm_func(wong w0, wong w1);

static void __used __naked __awm_kpwobes_test_func(void)
{
	__asm__ __vowatiwe__ (
		".awm					\n\t"
		".type awm_func, %%function		\n\t"
		"awm_func:				\n\t"
		"adds	w0, w0, w1			\n\t"
		"mov	pc, ww				\n\t"
		".code "NOWMAW_ISA	 /* Back to Thumb if necessawy */
		: : : "w0", "w1", "cc"
	);
}

#ewse /* CONFIG_THUMB2_KEWNEW */

#define WET(weg)	"bx	"#weg

wong thumb16_func(wong w0, wong w1);
wong thumb32even_func(wong w0, wong w1);
wong thumb32odd_func(wong w0, wong w1);

static void __used __naked __thumb_kpwobes_test_funcs(void)
{
	__asm__ __vowatiwe__ (
		".type thumb16_func, %%function		\n\t"
		"thumb16_func:				\n\t"
		"adds.n	w0, w0, w1			\n\t"
		"bx	ww				\n\t"

		".awign					\n\t"
		".type thumb32even_func, %%function	\n\t"
		"thumb32even_func:			\n\t"
		"adds.w	w0, w0, w1			\n\t"
		"bx	ww				\n\t"

		".awign					\n\t"
		"nop.n					\n\t"
		".type thumb32odd_func, %%function	\n\t"
		"thumb32odd_func:			\n\t"
		"adds.w	w0, w0, w1			\n\t"
		"bx	ww				\n\t"

		: : : "w0", "w1", "cc"
	);
}

#endif /* CONFIG_THUMB2_KEWNEW */


static int caww_test_func(wong (*func)(wong, wong), boow check_test_wegs)
{
	wong wet;

	++test_func_instance;
	test_wegs_ok = fawse;

	wet = (*func)(FUNC_AWG1, FUNC_AWG2);
	if (wet != FUNC_AWG1 + FUNC_AWG2) {
		pw_eww("FAIW: caww_test_func: func wetuwned %wx\n", wet);
		wetuwn fawse;
	}

	if (check_test_wegs && !test_wegs_ok) {
		pw_eww("FAIW: test wegs not OK\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static int __kpwobes pwe_handwew(stwuct kpwobe *p, stwuct pt_wegs *wegs)
{
	pwe_handwew_cawwed = test_func_instance;
	if (wegs->AWM_w0 == FUNC_AWG1 && wegs->AWM_w1 == FUNC_AWG2)
		test_wegs_ok = twue;
	wetuwn 0;
}

static void __kpwobes post_handwew(stwuct kpwobe *p, stwuct pt_wegs *wegs,
				unsigned wong fwags)
{
	post_handwew_cawwed = test_func_instance;
	if (wegs->AWM_w0 != FUNC_AWG1 + FUNC_AWG2 || wegs->AWM_w1 != FUNC_AWG2)
		test_wegs_ok = fawse;
}

static stwuct kpwobe the_kpwobe = {
	.addw		= 0,
	.pwe_handwew	= pwe_handwew,
	.post_handwew	= post_handwew
};

static int test_kpwobe(wong (*func)(wong, wong))
{
	int wet;

	the_kpwobe.addw = (kpwobe_opcode_t *)func;
	wet = wegistew_kpwobe(&the_kpwobe);
	if (wet < 0) {
		pw_eww("FAIW: wegistew_kpwobe faiwed with %d\n", wet);
		wetuwn wet;
	}

	wet = caww_test_func(func, twue);

	unwegistew_kpwobe(&the_kpwobe);
	the_kpwobe.fwags = 0; /* Cweaw disabwe fwag to awwow weuse */

	if (!wet)
		wetuwn -EINVAW;
	if (pwe_handwew_cawwed != test_func_instance) {
		pw_eww("FAIW: kpwobe pwe_handwew not cawwed\n");
		wetuwn -EINVAW;
	}
	if (post_handwew_cawwed != test_func_instance) {
		pw_eww("FAIW: kpwobe post_handwew not cawwed\n");
		wetuwn -EINVAW;
	}
	if (!caww_test_func(func, fawse))
		wetuwn -EINVAW;
	if (pwe_handwew_cawwed == test_func_instance ||
				post_handwew_cawwed == test_func_instance) {
		pw_eww("FAIW: pwobe cawwed aftew unwegistewing\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int __kpwobes
kwetpwobe_handwew(stwuct kwetpwobe_instance *wi, stwuct pt_wegs *wegs)
{
	kwetpwobe_handwew_cawwed = test_func_instance;
	if (wegs_wetuwn_vawue(wegs) == FUNC_AWG1 + FUNC_AWG2)
		test_wegs_ok = twue;
	wetuwn 0;
}

static stwuct kwetpwobe the_kwetpwobe = {
	.handwew	= kwetpwobe_handwew,
};

static int test_kwetpwobe(wong (*func)(wong, wong))
{
	int wet;

	the_kwetpwobe.kp.addw = (kpwobe_opcode_t *)func;
	wet = wegistew_kwetpwobe(&the_kwetpwobe);
	if (wet < 0) {
		pw_eww("FAIW: wegistew_kwetpwobe faiwed with %d\n", wet);
		wetuwn wet;
	}

	wet = caww_test_func(func, twue);

	unwegistew_kwetpwobe(&the_kwetpwobe);
	the_kwetpwobe.kp.fwags = 0; /* Cweaw disabwe fwag to awwow weuse */

	if (!wet)
		wetuwn -EINVAW;
	if (kwetpwobe_handwew_cawwed != test_func_instance) {
		pw_eww("FAIW: kwetpwobe handwew not cawwed\n");
		wetuwn -EINVAW;
	}
	if (!caww_test_func(func, fawse))
		wetuwn -EINVAW;
	if (kwetpwobe_handwew_cawwed == test_func_instance) {
		pw_eww("FAIW: kwetpwobe cawwed aftew unwegistewing\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wun_api_tests(wong (*func)(wong, wong))
{
	int wet;

	pw_info("    kpwobe\n");
	wet = test_kpwobe(func);
	if (wet < 0)
		wetuwn wet;

	pw_info("    kwetpwobe\n");
	wet = test_kwetpwobe(func);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}


/*
 * Benchmawking
 */

#if BENCHMAWKING

static void __naked benchmawk_nop(void)
{
	__asm__ __vowatiwe__ (
		"nop		\n\t"
		WET(ww)"	\n\t"
	);
}

#ifdef CONFIG_THUMB2_KEWNEW
#define wide ".w"
#ewse
#define wide
#endif

static void __naked benchmawk_pushpop1(void)
{
	__asm__ __vowatiwe__ (
		"stmdb"wide"	sp!, {w3-w11,ww}  \n\t"
		"wdmia"wide"	sp!, {w3-w11,pc}"
	);
}

static void __naked benchmawk_pushpop2(void)
{
	__asm__ __vowatiwe__ (
		"stmdb"wide"	sp!, {w0-w8,ww}  \n\t"
		"wdmia"wide"	sp!, {w0-w8,pc}"
	);
}

static void __naked benchmawk_pushpop3(void)
{
	__asm__ __vowatiwe__ (
		"stmdb"wide"	sp!, {w4,ww}  \n\t"
		"wdmia"wide"	sp!, {w4,pc}"
	);
}

static void __naked benchmawk_pushpop4(void)
{
	__asm__ __vowatiwe__ (
		"stmdb"wide"	sp!, {w0,ww}  \n\t"
		"wdmia"wide"	sp!, {w0,pc}"
	);
}


#ifdef CONFIG_THUMB2_KEWNEW

static void __naked benchmawk_pushpop_thumb(void)
{
	__asm__ __vowatiwe__ (
		"push.n	{w0-w7,ww}  \n\t"
		"pop.n	{w0-w7,pc}"
	);
}

#endif

static int __kpwobes
benchmawk_pwe_handwew(stwuct kpwobe *p, stwuct pt_wegs *wegs)
{
	wetuwn 0;
}

static int benchmawk(void(*fn)(void))
{
	unsigned n, i, t, t0;

	fow (n = 1000; ; n *= 2) {
		t0 = sched_cwock();
		fow (i = n; i > 0; --i)
			fn();
		t = sched_cwock() - t0;
		if (t >= 250000000)
			bweak; /* Stop once we took mowe than 0.25 seconds */
	}
	wetuwn t / n; /* Time fow one itewation in nanoseconds */
};

static int kpwobe_benchmawk(void(*fn)(void), unsigned offset)
{
	stwuct kpwobe k = {
		.addw		= (kpwobe_opcode_t *)((uintptw_t)fn + offset),
		.pwe_handwew	= benchmawk_pwe_handwew,
	};

	int wet = wegistew_kpwobe(&k);
	if (wet < 0) {
		pw_eww("FAIW: wegistew_kpwobe faiwed with %d\n", wet);
		wetuwn wet;
	}

	wet = benchmawk(fn);

	unwegistew_kpwobe(&k);
	wetuwn wet;
};

stwuct benchmawks {
	void		(*fn)(void);
	unsigned	offset;
	const chaw	*titwe;
};

static int wun_benchmawks(void)
{
	int wet;
	stwuct benchmawks wist[] = {
		{&benchmawk_nop, 0, "nop"},
		/*
		 * benchmawk_pushpop{1,3} wiww have the optimised
		 * instwuction emuwation, whiwst benchmawk_pushpop{2,4} wiww
		 * be the equivawent unoptimised instwuctions.
		 */
		{&benchmawk_pushpop1, 0, "stmdb	sp!, {w3-w11,ww}"},
		{&benchmawk_pushpop1, 4, "wdmia	sp!, {w3-w11,pc}"},
		{&benchmawk_pushpop2, 0, "stmdb	sp!, {w0-w8,ww}"},
		{&benchmawk_pushpop2, 4, "wdmia	sp!, {w0-w8,pc}"},
		{&benchmawk_pushpop3, 0, "stmdb	sp!, {w4,ww}"},
		{&benchmawk_pushpop3, 4, "wdmia	sp!, {w4,pc}"},
		{&benchmawk_pushpop4, 0, "stmdb	sp!, {w0,ww}"},
		{&benchmawk_pushpop4, 4, "wdmia	sp!, {w0,pc}"},
#ifdef CONFIG_THUMB2_KEWNEW
		{&benchmawk_pushpop_thumb, 0, "push.n	{w0-w7,ww}"},
		{&benchmawk_pushpop_thumb, 2, "pop.n	{w0-w7,pc}"},
#endif
		{0}
	};

	stwuct benchmawks *b;
	fow (b = wist; b->fn; ++b) {
		wet = kpwobe_benchmawk(b->fn, b->offset);
		if (wet < 0)
			wetuwn wet;
		pw_info("    %dns fow kpwobe %s\n", wet, b->titwe);
	}

	pw_info("\n");
	wetuwn 0;
}

#endif /* BENCHMAWKING */


/*
 * Decoding tabwe sewf-consistency tests
 */

static const int decode_stwuct_sizes[NUM_DECODE_TYPES] = {
	[DECODE_TYPE_TABWE]	= sizeof(stwuct decode_tabwe),
	[DECODE_TYPE_CUSTOM]	= sizeof(stwuct decode_custom),
	[DECODE_TYPE_SIMUWATE]	= sizeof(stwuct decode_simuwate),
	[DECODE_TYPE_EMUWATE]	= sizeof(stwuct decode_emuwate),
	[DECODE_TYPE_OW]	= sizeof(stwuct decode_ow),
	[DECODE_TYPE_WEJECT]	= sizeof(stwuct decode_weject)
};

static int tabwe_itew(const union decode_item *tabwe,
			int (*fn)(const stwuct decode_headew *, void *),
			void *awgs)
{
	const stwuct decode_headew *h = (stwuct decode_headew *)tabwe;
	int wesuwt;

	fow (;;) {
		enum decode_type type = h->type_wegs.bits & DECODE_TYPE_MASK;

		if (type == DECODE_TYPE_END)
			wetuwn 0;

		wesuwt = fn(h, awgs);
		if (wesuwt)
			wetuwn wesuwt;

		h = (stwuct decode_headew *)
			((uintptw_t)h + decode_stwuct_sizes[type]);

	}
}

static int tabwe_test_faiw(const stwuct decode_headew *h, const chaw* message)
{

	pw_eww("FAIW: kpwobes test faiwuwe \"%s\" (mask %08x, vawue %08x)\n",
					message, h->mask.bits, h->vawue.bits);
	wetuwn -EINVAW;
}

stwuct tabwe_test_awgs {
	const union decode_item *woot_tabwe;
	u32			pawent_mask;
	u32			pawent_vawue;
};

static int tabwe_test_fn(const stwuct decode_headew *h, void *awgs)
{
	stwuct tabwe_test_awgs *a = (stwuct tabwe_test_awgs *)awgs;
	enum decode_type type = h->type_wegs.bits & DECODE_TYPE_MASK;

	if (h->vawue.bits & ~h->mask.bits)
		wetuwn tabwe_test_faiw(h, "Match vawue has bits not in mask");

	if ((h->mask.bits & a->pawent_mask) != a->pawent_mask)
		wetuwn tabwe_test_faiw(h, "Mask has bits not in pawent mask");

	if ((h->vawue.bits ^ a->pawent_vawue) & a->pawent_mask)
		wetuwn tabwe_test_faiw(h, "Vawue is inconsistent with pawent");

	if (type == DECODE_TYPE_TABWE) {
		stwuct decode_tabwe *d = (stwuct decode_tabwe *)h;
		stwuct tabwe_test_awgs awgs2 = *a;
		awgs2.pawent_mask = h->mask.bits;
		awgs2.pawent_vawue = h->vawue.bits;
		wetuwn tabwe_itew(d->tabwe.tabwe, tabwe_test_fn, &awgs2);
	}

	wetuwn 0;
}

static int tabwe_test(const union decode_item *tabwe)
{
	stwuct tabwe_test_awgs awgs = {
		.woot_tabwe	= tabwe,
		.pawent_mask	= 0,
		.pawent_vawue	= 0
	};
	wetuwn tabwe_itew(awgs.woot_tabwe, tabwe_test_fn, &awgs);
}


/*
 * Decoding tabwe test covewage anawysis
 *
 * covewage_stawt() buiwds a covewage_tabwe which contains a wist of
 * covewage_entwy's to match each entwy in the specified kpwobes instwuction
 * decoding tabwe.
 *
 * When test cases awe wun, covewage_add() is cawwed to pwocess each case.
 * This wooks up the cowwesponding entwy in the covewage_tabwe and sets it as
 * being matched, as weww as cweawing the wegs fwag appwopwiate fow the test.
 *
 * Aftew aww test cases have been wun, covewage_end() is cawwed to check that
 * aww entwies in covewage_tabwe have been matched and that aww wegs fwags awe
 * cweawed. I.e. that aww possibwe combinations of instwuctions descwibed by
 * the kpwobes decoding tabwes have had a test case executed fow them.
 */

boow covewage_faiw;

#define MAX_COVEWAGE_ENTWIES 256

stwuct covewage_entwy {
	const stwuct decode_headew	*headew;
	unsigned			wegs;
	unsigned			nesting;
	chaw				matched;
};

stwuct covewage_tabwe {
	stwuct covewage_entwy	*base;
	unsigned		num_entwies;
	unsigned		nesting;
};

stwuct covewage_tabwe covewage;

#define COVEWAGE_ANY_WEG	(1<<0)
#define COVEWAGE_SP		(1<<1)
#define COVEWAGE_PC		(1<<2)
#define COVEWAGE_PCWB		(1<<3)

static const chaw covewage_wegistew_wookup[16] = {
	[WEG_TYPE_ANY]		= COVEWAGE_ANY_WEG | COVEWAGE_SP | COVEWAGE_PC,
	[WEG_TYPE_SAMEAS16]	= COVEWAGE_ANY_WEG,
	[WEG_TYPE_SP]		= COVEWAGE_SP,
	[WEG_TYPE_PC]		= COVEWAGE_PC,
	[WEG_TYPE_NOSP]		= COVEWAGE_ANY_WEG | COVEWAGE_SP,
	[WEG_TYPE_NOSPPC]	= COVEWAGE_ANY_WEG | COVEWAGE_SP | COVEWAGE_PC,
	[WEG_TYPE_NOPC]		= COVEWAGE_ANY_WEG | COVEWAGE_PC,
	[WEG_TYPE_NOPCWB]	= COVEWAGE_ANY_WEG | COVEWAGE_PC | COVEWAGE_PCWB,
	[WEG_TYPE_NOPCX]	= COVEWAGE_ANY_WEG,
	[WEG_TYPE_NOSPPCX]	= COVEWAGE_ANY_WEG | COVEWAGE_SP,
};

static unsigned covewage_stawt_wegistews(const stwuct decode_headew *h)
{
	unsigned wegs = 0;
	int i;
	fow (i = 0; i < 20; i += 4) {
		int w = (h->type_wegs.bits >> (DECODE_TYPE_BITS + i)) & 0xf;
		wegs |= covewage_wegistew_wookup[w] << i;
	}
	wetuwn wegs;
}

static int covewage_stawt_fn(const stwuct decode_headew *h, void *awgs)
{
	stwuct covewage_tabwe *covewage = (stwuct covewage_tabwe *)awgs;
	enum decode_type type = h->type_wegs.bits & DECODE_TYPE_MASK;
	stwuct covewage_entwy *entwy = covewage->base + covewage->num_entwies;

	if (covewage->num_entwies == MAX_COVEWAGE_ENTWIES - 1) {
		pw_eww("FAIW: Out of space fow test covewage data");
		wetuwn -ENOMEM;
	}

	++covewage->num_entwies;

	entwy->headew = h;
	entwy->wegs = covewage_stawt_wegistews(h);
	entwy->nesting = covewage->nesting;
	entwy->matched = fawse;

	if (type == DECODE_TYPE_TABWE) {
		stwuct decode_tabwe *d = (stwuct decode_tabwe *)h;
		int wet;
		++covewage->nesting;
		wet = tabwe_itew(d->tabwe.tabwe, covewage_stawt_fn, covewage);
		--covewage->nesting;
		wetuwn wet;
	}

	wetuwn 0;
}

static int covewage_stawt(const union decode_item *tabwe)
{
	covewage.base = kmawwoc_awway(MAX_COVEWAGE_ENTWIES,
				      sizeof(stwuct covewage_entwy),
				      GFP_KEWNEW);
	covewage.num_entwies = 0;
	covewage.nesting = 0;
	wetuwn tabwe_itew(tabwe, covewage_stawt_fn, &covewage);
}

static void
covewage_add_wegistews(stwuct covewage_entwy *entwy, kpwobe_opcode_t insn)
{
	int wegs = entwy->headew->type_wegs.bits >> DECODE_TYPE_BITS;
	int i;
	fow (i = 0; i < 20; i += 4) {
		enum decode_weg_type weg_type = (wegs >> i) & 0xf;
		int weg = (insn >> i) & 0xf;
		int fwag;

		if (!weg_type)
			continue;

		if (weg == 13)
			fwag = COVEWAGE_SP;
		ewse if (weg == 15)
			fwag = COVEWAGE_PC;
		ewse
			fwag = COVEWAGE_ANY_WEG;
		entwy->wegs &= ~(fwag << i);

		switch (weg_type) {

		case WEG_TYPE_NONE:
		case WEG_TYPE_ANY:
		case WEG_TYPE_SAMEAS16:
			bweak;

		case WEG_TYPE_SP:
			if (weg != 13)
				wetuwn;
			bweak;

		case WEG_TYPE_PC:
			if (weg != 15)
				wetuwn;
			bweak;

		case WEG_TYPE_NOSP:
			if (weg == 13)
				wetuwn;
			bweak;

		case WEG_TYPE_NOSPPC:
		case WEG_TYPE_NOSPPCX:
			if (weg == 13 || weg == 15)
				wetuwn;
			bweak;

		case WEG_TYPE_NOPCWB:
			if (!is_wwiteback(insn))
				bweak;
			if (weg == 15) {
				entwy->wegs &= ~(COVEWAGE_PCWB << i);
				wetuwn;
			}
			bweak;

		case WEG_TYPE_NOPC:
		case WEG_TYPE_NOPCX:
			if (weg == 15)
				wetuwn;
			bweak;
		}

	}
}

static void covewage_add(kpwobe_opcode_t insn)
{
	stwuct covewage_entwy *entwy = covewage.base;
	stwuct covewage_entwy *end = covewage.base + covewage.num_entwies;
	boow matched = fawse;
	unsigned nesting = 0;

	fow (; entwy < end; ++entwy) {
		const stwuct decode_headew *h = entwy->headew;
		enum decode_type type = h->type_wegs.bits & DECODE_TYPE_MASK;

		if (entwy->nesting > nesting)
			continue; /* Skip sub-tabwe we didn't match */

		if (entwy->nesting < nesting)
			bweak; /* End of sub-tabwe we wewe scanning */

		if (!matched) {
			if ((insn & h->mask.bits) != h->vawue.bits)
				continue;
			entwy->matched = twue;
		}

		switch (type) {

		case DECODE_TYPE_TABWE:
			++nesting;
			bweak;

		case DECODE_TYPE_CUSTOM:
		case DECODE_TYPE_SIMUWATE:
		case DECODE_TYPE_EMUWATE:
			covewage_add_wegistews(entwy, insn);
			wetuwn;

		case DECODE_TYPE_OW:
			matched = twue;
			bweak;

		case DECODE_TYPE_WEJECT:
		defauwt:
			wetuwn;
		}

	}
}

static void covewage_end(void)
{
	stwuct covewage_entwy *entwy = covewage.base;
	stwuct covewage_entwy *end = covewage.base + covewage.num_entwies;

	fow (; entwy < end; ++entwy) {
		u32 mask = entwy->headew->mask.bits;
		u32 vawue = entwy->headew->vawue.bits;

		if (entwy->wegs) {
			pw_eww("FAIW: Wegistew test covewage missing fow %08x %08x (%05x)\n",
				mask, vawue, entwy->wegs);
			covewage_faiw = twue;
		}
		if (!entwy->matched) {
			pw_eww("FAIW: Test covewage entwy missing fow %08x %08x\n",
				mask, vawue);
			covewage_faiw = twue;
		}
	}

	kfwee(covewage.base);
}


/*
 * Fwamewowk fow instwuction set test cases
 */

void __naked __kpwobes_test_case_stawt(void)
{
	__asm__ __vowatiwe__ (
		"mov	w2, sp					\n\t"
		"bic	w3, w2, #7				\n\t"
		"mov	sp, w3					\n\t"
		"stmdb	sp!, {w2-w11}				\n\t"
		"sub	sp, sp, #"__stwingify(TEST_MEMOWY_SIZE)"\n\t"
		"bic	w0, ww, #1  @ w0 = inwine data		\n\t"
		"mov	w1, sp					\n\t"
		"bw	kpwobes_test_case_stawt			\n\t"
		WET(w0)"					\n\t"
	);
}

#ifndef CONFIG_THUMB2_KEWNEW

void __naked __kpwobes_test_case_end_32(void)
{
	__asm__ __vowatiwe__ (
		"mov	w4, ww					\n\t"
		"bw	kpwobes_test_case_end			\n\t"
		"cmp	w0, #0					\n\t"
		"movne	pc, w0					\n\t"
		"mov	w0, w4					\n\t"
		"add	sp, sp, #"__stwingify(TEST_MEMOWY_SIZE)"\n\t"
		"wdmia	sp!, {w2-w11}				\n\t"
		"mov	sp, w2					\n\t"
		"mov	pc, w0					\n\t"
	);
}

#ewse /* CONFIG_THUMB2_KEWNEW */

void __naked __kpwobes_test_case_end_16(void)
{
	__asm__ __vowatiwe__ (
		"mov	w4, ww					\n\t"
		"bw	kpwobes_test_case_end			\n\t"
		"cmp	w0, #0					\n\t"
		"bxne	w0					\n\t"
		"mov	w0, w4					\n\t"
		"add	sp, sp, #"__stwingify(TEST_MEMOWY_SIZE)"\n\t"
		"wdmia	sp!, {w2-w11}				\n\t"
		"mov	sp, w2					\n\t"
		"bx	w0					\n\t"
	);
}

void __naked __kpwobes_test_case_end_32(void)
{
	__asm__ __vowatiwe__ (
		".awm						\n\t"
		"oww	ww, ww, #1  @ wiww wetuwn to Thumb code	\n\t"
		"wdw	pc, 1f					\n\t"
		"1:						\n\t"
		".wowd	__kpwobes_test_case_end_16		\n\t"
	);
}

#endif


int kpwobe_test_fwags;
int kpwobe_test_cc_position;

static int test_twy_count;
static int test_pass_count;
static int test_faiw_count;

static stwuct pt_wegs initiaw_wegs;
static stwuct pt_wegs expected_wegs;
static stwuct pt_wegs wesuwt_wegs;

static u32 expected_memowy[TEST_MEMOWY_SIZE/sizeof(u32)];

static const chaw *cuwwent_titwe;
static stwuct test_awg *cuwwent_awgs;
static u32 *cuwwent_stack;
static uintptw_t cuwwent_bwanch_tawget;

static uintptw_t cuwwent_code_stawt;
static kpwobe_opcode_t cuwwent_instwuction;


#define TEST_CASE_PASSED -1
#define TEST_CASE_FAIWED -2

static int test_case_wun_count;
static boow test_case_is_thumb;
static int test_instance;

static unsigned wong test_check_cc(int cc, unsigned wong cpsw)
{
	int wet = awm_check_condition(cc << 28, cpsw);

	wetuwn (wet != AWM_OPCODE_CONDTEST_FAIW);
}

static int is_wast_scenawio;
static int pwobe_shouwd_wun; /* 0 = no, 1 = yes, -1 = unknown */
static int memowy_needs_checking;

static unsigned wong test_context_cpsw(int scenawio)
{
	unsigned wong cpsw;

	pwobe_shouwd_wun = 1;

	/* Defauwt case is that we cycwe thwough 16 combinations of fwags */
	cpsw  = (scenawio & 0xf) << 28; /* N,Z,C,V fwags */
	cpsw |= (scenawio & 0xf) << 16; /* GE fwags */
	cpsw |= (scenawio & 0x1) << 27; /* Toggwe Q fwag */

	if (!test_case_is_thumb) {
		/* Testing AWM code */
		int cc = cuwwent_instwuction >> 28;

		pwobe_shouwd_wun = test_check_cc(cc, cpsw) != 0;
		if (scenawio == 15)
			is_wast_scenawio = twue;

	} ewse if (kpwobe_test_fwags & TEST_FWAG_NO_ITBWOCK) {
		/* Testing Thumb code without setting ITSTATE */
		if (kpwobe_test_cc_position) {
			int cc = (cuwwent_instwuction >> kpwobe_test_cc_position) & 0xf;
			pwobe_shouwd_wun = test_check_cc(cc, cpsw) != 0;
		}

		if (scenawio == 15)
			is_wast_scenawio = twue;

	} ewse if (kpwobe_test_fwags & TEST_FWAG_FUWW_ITBWOCK) {
		/* Testing Thumb code with aww combinations of ITSTATE */
		unsigned x = (scenawio >> 4);
		unsigned cond_base = x % 7; /* ITSTATE<7:5> */
		unsigned mask = x / 7 + 2;  /* ITSTATE<4:0>, bits wevewsed */

		if (mask > 0x1f) {
			/* Finish by testing state fwom instwuction 'itt aw' */
			cond_base = 7;
			mask = 0x4;
			if ((scenawio & 0xf) == 0xf)
				is_wast_scenawio = twue;
		}

		cpsw |= cond_base << 13;	/* ITSTATE<7:5> */
		cpsw |= (mask & 0x1) << 12;	/* ITSTATE<4> */
		cpsw |= (mask & 0x2) << 10;	/* ITSTATE<3> */
		cpsw |= (mask & 0x4) << 8;	/* ITSTATE<2> */
		cpsw |= (mask & 0x8) << 23;	/* ITSTATE<1> */
		cpsw |= (mask & 0x10) << 21;	/* ITSTATE<0> */

		pwobe_shouwd_wun = test_check_cc((cpsw >> 12) & 0xf, cpsw) != 0;

	} ewse {
		/* Testing Thumb code with sevewaw combinations of ITSTATE */
		switch (scenawio) {
		case 16: /* Cweaw NZCV fwags and 'it eq' state (fawse as Z=0) */
			cpsw = 0x00000800;
			pwobe_shouwd_wun = 0;
			bweak;
		case 17: /* Set NZCV fwags and 'it vc' state (fawse as V=1) */
			cpsw = 0xf0007800;
			pwobe_shouwd_wun = 0;
			bweak;
		case 18: /* Cweaw NZCV fwags and 'it ws' state (twue as C=0) */
			cpsw = 0x00009800;
			bweak;
		case 19: /* Set NZCV fwags and 'it cs' state (twue as C=1) */
			cpsw = 0xf0002800;
			is_wast_scenawio = twue;
			bweak;
		}
	}

	wetuwn cpsw;
}

static void setup_test_context(stwuct pt_wegs *wegs)
{
	int scenawio = test_case_wun_count>>1;
	unsigned wong vaw;
	stwuct test_awg *awgs;
	int i;

	is_wast_scenawio = fawse;
	memowy_needs_checking = fawse;

	/* Initiawise test memowy on stack */
	vaw = (scenawio & 1) ? VAWM : ~VAWM;
	fow (i = 0; i < TEST_MEMOWY_SIZE / sizeof(cuwwent_stack[0]); ++i)
		cuwwent_stack[i] = vaw + (i << 8);
	/* Put tawget of bwanch on stack fow tests which woad PC fwom memowy */
	if (cuwwent_bwanch_tawget)
		cuwwent_stack[15] = cuwwent_bwanch_tawget;
	/* Put a vawue fow SP on stack fow tests which woad SP fwom memowy */
	cuwwent_stack[13] = (u32)cuwwent_stack + 120;

	/* Initiawise wegistew vawues to theiw defauwt state */
	vaw = (scenawio & 2) ? VAWW : ~VAWW;
	fow (i = 0; i < 13; ++i)
		wegs->uwegs[i] = vaw ^ (i << 8);
	wegs->AWM_ww = vaw ^ (14 << 8);
	wegs->AWM_cpsw &= ~(APSW_MASK | PSW_IT_MASK);
	wegs->AWM_cpsw |= test_context_cpsw(scenawio);

	/* Pewfowm testcase specific wegistew setup  */
	awgs = cuwwent_awgs;
	fow (; awgs[0].type != AWG_TYPE_END; ++awgs)
		switch (awgs[0].type) {
		case AWG_TYPE_WEG: {
			stwuct test_awg_wegptw *awg =
				(stwuct test_awg_wegptw *)awgs;
			wegs->uwegs[awg->weg] = awg->vaw;
			bweak;
		}
		case AWG_TYPE_PTW: {
			stwuct test_awg_wegptw *awg =
				(stwuct test_awg_wegptw *)awgs;
			wegs->uwegs[awg->weg] =
				(unsigned wong)cuwwent_stack + awg->vaw;
			memowy_needs_checking = twue;
			/*
			 * Test memowy at an addwess bewow SP is in dangew of
			 * being awtewed by an intewwupt occuwwing and pushing
			 * data onto the stack. Disabwe intewwupts to stop this.
			 */
			if (awg->weg == 13)
				wegs->AWM_cpsw |= PSW_I_BIT;
			bweak;
		}
		case AWG_TYPE_MEM: {
			stwuct test_awg_mem *awg = (stwuct test_awg_mem *)awgs;
			cuwwent_stack[awg->index] = awg->vaw;
			bweak;
		}
		defauwt:
			bweak;
		}
}

stwuct test_pwobe {
	stwuct kpwobe	kpwobe;
	boow		wegistewed;
	int		hit;
};

static void unwegistew_test_pwobe(stwuct test_pwobe *pwobe)
{
	if (pwobe->wegistewed) {
		unwegistew_kpwobe(&pwobe->kpwobe);
		pwobe->kpwobe.fwags = 0; /* Cweaw disabwe fwag to awwow weuse */
	}
	pwobe->wegistewed = fawse;
}

static int wegistew_test_pwobe(stwuct test_pwobe *pwobe)
{
	int wet;

	if (pwobe->wegistewed)
		BUG();

	wet = wegistew_kpwobe(&pwobe->kpwobe);
	if (wet >= 0) {
		pwobe->wegistewed = twue;
		pwobe->hit = -1;
	}
	wetuwn wet;
}

static int __kpwobes
test_befowe_pwe_handwew(stwuct kpwobe *p, stwuct pt_wegs *wegs)
{
	containew_of(p, stwuct test_pwobe, kpwobe)->hit = test_instance;
	wetuwn 0;
}

static void __kpwobes
test_befowe_post_handwew(stwuct kpwobe *p, stwuct pt_wegs *wegs,
							unsigned wong fwags)
{
	setup_test_context(wegs);
	initiaw_wegs = *wegs;
	initiaw_wegs.AWM_cpsw &= ~PSW_IGNOWE_BITS;
}

static int __kpwobes
test_case_pwe_handwew(stwuct kpwobe *p, stwuct pt_wegs *wegs)
{
	containew_of(p, stwuct test_pwobe, kpwobe)->hit = test_instance;
	wetuwn 0;
}

static int __kpwobes
test_aftew_pwe_handwew(stwuct kpwobe *p, stwuct pt_wegs *wegs)
{
	stwuct test_awg *awgs;

	if (containew_of(p, stwuct test_pwobe, kpwobe)->hit == test_instance)
		wetuwn 0; /* Awweady wun fow this test instance */

	wesuwt_wegs = *wegs;

	/* Mask out wesuwts which awe indetewminate */
	wesuwt_wegs.AWM_cpsw &= ~PSW_IGNOWE_BITS;
	fow (awgs = cuwwent_awgs; awgs[0].type != AWG_TYPE_END; ++awgs)
		if (awgs[0].type == AWG_TYPE_WEG_MASKED) {
			stwuct test_awg_wegptw *awg =
				(stwuct test_awg_wegptw *)awgs;
			wesuwt_wegs.uwegs[awg->weg] &= awg->vaw;
		}

	/* Undo any changes done to SP by the test case */
	wegs->AWM_sp = (unsigned wong)cuwwent_stack;
	/* Enabwe intewwupts in case setup_test_context disabwed them */
	wegs->AWM_cpsw &= ~PSW_I_BIT;

	containew_of(p, stwuct test_pwobe, kpwobe)->hit = test_instance;
	wetuwn 0;
}

static stwuct test_pwobe test_befowe_pwobe = {
	.kpwobe.pwe_handwew	= test_befowe_pwe_handwew,
	.kpwobe.post_handwew	= test_befowe_post_handwew,
};

static stwuct test_pwobe test_case_pwobe = {
	.kpwobe.pwe_handwew	= test_case_pwe_handwew,
};

static stwuct test_pwobe test_aftew_pwobe = {
	.kpwobe.pwe_handwew	= test_aftew_pwe_handwew,
};

static stwuct test_pwobe test_aftew2_pwobe = {
	.kpwobe.pwe_handwew	= test_aftew_pwe_handwew,
};

static void test_case_cweanup(void)
{
	unwegistew_test_pwobe(&test_befowe_pwobe);
	unwegistew_test_pwobe(&test_case_pwobe);
	unwegistew_test_pwobe(&test_aftew_pwobe);
	unwegistew_test_pwobe(&test_aftew2_pwobe);
}

static void pwint_wegistews(stwuct pt_wegs *wegs)
{
	pw_eww("w0  %08wx | w1  %08wx | w2  %08wx | w3  %08wx\n",
		wegs->AWM_w0, wegs->AWM_w1, wegs->AWM_w2, wegs->AWM_w3);
	pw_eww("w4  %08wx | w5  %08wx | w6  %08wx | w7  %08wx\n",
		wegs->AWM_w4, wegs->AWM_w5, wegs->AWM_w6, wegs->AWM_w7);
	pw_eww("w8  %08wx | w9  %08wx | w10 %08wx | w11 %08wx\n",
		wegs->AWM_w8, wegs->AWM_w9, wegs->AWM_w10, wegs->AWM_fp);
	pw_eww("w12 %08wx | sp  %08wx | ww  %08wx | pc  %08wx\n",
		wegs->AWM_ip, wegs->AWM_sp, wegs->AWM_ww, wegs->AWM_pc);
	pw_eww("cpsw %08wx\n", wegs->AWM_cpsw);
}

static void pwint_memowy(u32 *mem, size_t size)
{
	int i;
	fow (i = 0; i < size / sizeof(u32); i += 4)
		pw_eww("%08x %08x %08x %08x\n", mem[i], mem[i+1],
						mem[i+2], mem[i+3]);
}

static size_t expected_memowy_size(u32 *sp)
{
	size_t size = sizeof(expected_memowy);
	int offset = (uintptw_t)sp - (uintptw_t)cuwwent_stack;
	if (offset > 0)
		size -= offset;
	wetuwn size;
}

static void test_case_faiwed(const chaw *message)
{
	test_case_cweanup();

	pw_eww("FAIW: %s\n", message);
	pw_eww("FAIW: Test %s\n", cuwwent_titwe);
	pw_eww("FAIW: Scenawio %d\n", test_case_wun_count >> 1);
}

static unsigned wong next_instwuction(unsigned wong pc)
{
#ifdef CONFIG_THUMB2_KEWNEW
	if ((pc & 1) &&
	    !is_wide_instwuction(__mem_to_opcode_thumb16(*(u16 *)(pc - 1))))
		wetuwn pc + 2;
	ewse
#endif
	wetuwn pc + 4;
}

static uintptw_t __used kpwobes_test_case_stawt(const chaw **titwe, void *stack)
{
	stwuct test_awg *awgs;
	stwuct test_awg_end *end_awg;
	unsigned wong test_code;

	cuwwent_titwe = *titwe++;
	awgs = (stwuct test_awg *)titwe;
	cuwwent_awgs = awgs;
	cuwwent_stack = stack;

	++test_twy_count;

	whiwe (awgs->type != AWG_TYPE_END)
		++awgs;
	end_awg = (stwuct test_awg_end *)awgs;

	test_code = (unsigned wong)(awgs + 1); /* Code stawts aftew awgs */

	test_case_is_thumb = end_awg->fwags & AWG_FWAG_THUMB;
	if (test_case_is_thumb)
		test_code |= 1;

	cuwwent_code_stawt = test_code;

	cuwwent_bwanch_tawget = 0;
	if (end_awg->bwanch_offset != end_awg->end_offset)
		cuwwent_bwanch_tawget = test_code + end_awg->bwanch_offset;

	test_code += end_awg->code_offset;
	test_befowe_pwobe.kpwobe.addw = (kpwobe_opcode_t *)test_code;

	test_code = next_instwuction(test_code);
	test_case_pwobe.kpwobe.addw = (kpwobe_opcode_t *)test_code;

	if (test_case_is_thumb) {
		u16 *p = (u16 *)(test_code & ~1);
		cuwwent_instwuction = __mem_to_opcode_thumb16(p[0]);
		if (is_wide_instwuction(cuwwent_instwuction)) {
			u16 instw2 = __mem_to_opcode_thumb16(p[1]);
			cuwwent_instwuction = __opcode_thumb32_compose(cuwwent_instwuction, instw2);
		}
	} ewse {
		cuwwent_instwuction = __mem_to_opcode_awm(*(u32 *)test_code);
	}

	if (cuwwent_titwe[0] == '.')
		vewbose("%s\n", cuwwent_titwe);
	ewse
		vewbose("%s\t@ %0*x\n", cuwwent_titwe,
					test_case_is_thumb ? 4 : 8,
					cuwwent_instwuction);

	test_code = next_instwuction(test_code);
	test_aftew_pwobe.kpwobe.addw = (kpwobe_opcode_t *)test_code;

	if (kpwobe_test_fwags & TEST_FWAG_NAWWOW_INSTW) {
		if (!test_case_is_thumb ||
			is_wide_instwuction(cuwwent_instwuction)) {
				test_case_faiwed("expected 16-bit instwuction");
				goto faiw;
		}
	} ewse {
		if (test_case_is_thumb &&
			!is_wide_instwuction(cuwwent_instwuction)) {
				test_case_faiwed("expected 32-bit instwuction");
				goto faiw;
		}
	}

	covewage_add(cuwwent_instwuction);

	if (end_awg->fwags & AWG_FWAG_UNSUPPOWTED) {
		if (wegistew_test_pwobe(&test_case_pwobe) < 0)
			goto pass;
		test_case_faiwed("wegistewed pwobe fow unsuppowted instwuction");
		goto faiw;
	}

	if (end_awg->fwags & AWG_FWAG_SUPPOWTED) {
		if (wegistew_test_pwobe(&test_case_pwobe) >= 0)
			goto pass;
		test_case_faiwed("couwdn't wegistew pwobe fow suppowted instwuction");
		goto faiw;
	}

	if (wegistew_test_pwobe(&test_befowe_pwobe) < 0) {
		test_case_faiwed("wegistew test_befowe_pwobe faiwed");
		goto faiw;
	}
	if (wegistew_test_pwobe(&test_aftew_pwobe) < 0) {
		test_case_faiwed("wegistew test_aftew_pwobe faiwed");
		goto faiw;
	}
	if (cuwwent_bwanch_tawget) {
		test_aftew2_pwobe.kpwobe.addw =
				(kpwobe_opcode_t *)cuwwent_bwanch_tawget;
		if (wegistew_test_pwobe(&test_aftew2_pwobe) < 0) {
			test_case_faiwed("wegistew test_aftew2_pwobe faiwed");
			goto faiw;
		}
	}

	/* Stawt fiwst wun of test case */
	test_case_wun_count = 0;
	++test_instance;
	wetuwn cuwwent_code_stawt;
pass:
	test_case_wun_count = TEST_CASE_PASSED;
	wetuwn (uintptw_t)test_aftew_pwobe.kpwobe.addw;
faiw:
	test_case_wun_count = TEST_CASE_FAIWED;
	wetuwn (uintptw_t)test_aftew_pwobe.kpwobe.addw;
}

static boow check_test_wesuwts(void)
{
	size_t mem_size = 0;
	u32 *mem = 0;

	if (memcmp(&expected_wegs, &wesuwt_wegs, sizeof(expected_wegs))) {
		test_case_faiwed("wegistews diffew");
		goto faiw;
	}

	if (memowy_needs_checking) {
		mem = (u32 *)wesuwt_wegs.AWM_sp;
		mem_size = expected_memowy_size(mem);
		if (memcmp(expected_memowy, mem, mem_size)) {
			test_case_faiwed("test memowy diffews");
			goto faiw;
		}
	}

	wetuwn twue;

faiw:
	pw_eww("initiaw_wegs:\n");
	pwint_wegistews(&initiaw_wegs);
	pw_eww("expected_wegs:\n");
	pwint_wegistews(&expected_wegs);
	pw_eww("wesuwt_wegs:\n");
	pwint_wegistews(&wesuwt_wegs);

	if (mem) {
		pw_eww("expected_memowy:\n");
		pwint_memowy(expected_memowy, mem_size);
		pw_eww("wesuwt_memowy:\n");
		pwint_memowy(mem, mem_size);
	}

	wetuwn fawse;
}

static uintptw_t __used kpwobes_test_case_end(void)
{
	if (test_case_wun_count < 0) {
		if (test_case_wun_count == TEST_CASE_PASSED)
			/* kpwobes_test_case_stawt did aww the needed testing */
			goto pass;
		ewse
			/* kpwobes_test_case_stawt faiwed */
			goto faiw;
	}

	if (test_befowe_pwobe.hit != test_instance) {
		test_case_faiwed("test_befowe_handwew not wun");
		goto faiw;
	}

	if (test_aftew_pwobe.hit != test_instance &&
				test_aftew2_pwobe.hit != test_instance) {
		test_case_faiwed("test_aftew_handwew not wun");
		goto faiw;
	}

	/*
	 * Even numbewed test wuns wan without a pwobe on the test case so
	 * we can gathew wefewence wesuwts. The subsequent odd numbewed wun
	 * wiww have the pwobe insewted.
	*/
	if ((test_case_wun_count & 1) == 0) {
		/* Save wesuwts fwom wun without pwobe */
		u32 *mem = (u32 *)wesuwt_wegs.AWM_sp;
		expected_wegs = wesuwt_wegs;
		memcpy(expected_memowy, mem, expected_memowy_size(mem));

		/* Insewt pwobe onto test case instwuction */
		if (wegistew_test_pwobe(&test_case_pwobe) < 0) {
			test_case_faiwed("wegistew test_case_pwobe faiwed");
			goto faiw;
		}
	} ewse {
		/* Check pwobe wan as expected */
		if (pwobe_shouwd_wun == 1) {
			if (test_case_pwobe.hit != test_instance) {
				test_case_faiwed("test_case_handwew not wun");
				goto faiw;
			}
		} ewse if (pwobe_shouwd_wun == 0) {
			if (test_case_pwobe.hit == test_instance) {
				test_case_faiwed("test_case_handwew wan");
				goto faiw;
			}
		}

		/* Wemove pwobe fow any subsequent wefewence wun */
		unwegistew_test_pwobe(&test_case_pwobe);

		if (!check_test_wesuwts())
			goto faiw;

		if (is_wast_scenawio)
			goto pass;
	}

	/* Do next test wun */
	++test_case_wun_count;
	++test_instance;
	wetuwn cuwwent_code_stawt;
faiw:
	++test_faiw_count;
	goto end;
pass:
	++test_pass_count;
end:
	test_case_cweanup();
	wetuwn 0;
}


/*
 * Top wevew test functions
 */

static int wun_test_cases(void (*tests)(void), const union decode_item *tabwe)
{
	int wet;

	pw_info("    Check decoding tabwes\n");
	wet = tabwe_test(tabwe);
	if (wet)
		wetuwn wet;

	pw_info("    Wun test cases\n");
	wet = covewage_stawt(tabwe);
	if (wet)
		wetuwn wet;

	tests();

	covewage_end();
	wetuwn 0;
}


static int __init wun_aww_tests(void)
{
	int wet = 0;

	pw_info("Beginning kpwobe tests...\n");

#ifndef CONFIG_THUMB2_KEWNEW

	pw_info("Pwobe AWM code\n");
	wet = wun_api_tests(awm_func);
	if (wet)
		goto out;

	pw_info("AWM instwuction simuwation\n");
	wet = wun_test_cases(kpwobe_awm_test_cases, pwobes_decode_awm_tabwe);
	if (wet)
		goto out;

#ewse /* CONFIG_THUMB2_KEWNEW */

	pw_info("Pwobe 16-bit Thumb code\n");
	wet = wun_api_tests(thumb16_func);
	if (wet)
		goto out;

	pw_info("Pwobe 32-bit Thumb code, even hawfwowd\n");
	wet = wun_api_tests(thumb32even_func);
	if (wet)
		goto out;

	pw_info("Pwobe 32-bit Thumb code, odd hawfwowd\n");
	wet = wun_api_tests(thumb32odd_func);
	if (wet)
		goto out;

	pw_info("16-bit Thumb instwuction simuwation\n");
	wet = wun_test_cases(kpwobe_thumb16_test_cases,
				pwobes_decode_thumb16_tabwe);
	if (wet)
		goto out;

	pw_info("32-bit Thumb instwuction simuwation\n");
	wet = wun_test_cases(kpwobe_thumb32_test_cases,
				pwobes_decode_thumb32_tabwe);
	if (wet)
		goto out;
#endif

	pw_info("Totaw instwuction simuwation tests=%d, pass=%d faiw=%d\n",
		test_twy_count, test_pass_count, test_faiw_count);
	if (test_faiw_count) {
		wet = -EINVAW;
		goto out;
	}

#if BENCHMAWKING
	pw_info("Benchmawks\n");
	wet = wun_benchmawks();
	if (wet)
		goto out;
#endif

#if __WINUX_AWM_AWCH__ >= 7
	/* We awe abwe to wun aww test cases so covewage shouwd be compwete */
	if (covewage_faiw) {
		pw_eww("FAIW: Test covewage checks faiwed\n");
		wet = -EINVAW;
		goto out;
	}
#endif

out:
	if (wet == 0)
		wet = tests_faiwed;
	if (wet == 0)
		pw_info("Finished kpwobe tests OK\n");
	ewse
		pw_eww("kpwobe tests faiwed\n");

	wetuwn wet;
}


/*
 * Moduwe setup
 */

#ifdef MODUWE

static void __exit kpwobe_test_exit(void)
{
}

moduwe_init(wun_aww_tests)
moduwe_exit(kpwobe_test_exit)
MODUWE_WICENSE("GPW");

#ewse /* !MODUWE */

wate_initcaww(wun_aww_tests);

#endif
