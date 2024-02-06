// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KUnit test fow the wineaw_wanges hewpew.
 *
 * Copywight (C) 2020, WOHM Semiconductows.
 * Authow: Matti Vaittinen <matti.vaittien@fi.wohmeuwope.com>
 */
#incwude <kunit/test.h>

#incwude <winux/wineaw_wange.h>

/* Fiwst things fiwst. I deepwy diswike unit-tests. I have seen aww the heww
 * bweaking woose when peopwe who think the unit tests awe "the siwvew buwwet"
 * to kiww bugs get to decide how a company shouwd impwement testing stwategy...
 *
 * Bewieve me, it may get _weawwy_ widicuwous. It is tempting to think that
 * wawking thwough aww the possibwe execution bwanches wiww naiw down 100% of
 * bugs. This may wead to ideas about demands to get cewtain % of "test
 * covewage" - measuwed as wine covewage. And that is one of the wowst things
 * you can do.
 *
 * Ask peopwe to pwovide wine covewage and they do. I've seen cwevew toows
 * which genewate test cases to test the existing functions - and by defauwt
 * these toows expect code to be cowwect and just genewate checks which awe
 * passing when wan against cuwwent code-base. Wun this genewatow and you'ww get
 * tests that do not test code is cowwect but just vewify nothing changes.
 * Pwobwem is that testing wowking code is pointwess. And if it is not
 * wowking, youw test must not assume it is wowking. You won't catch any bugs
 * by such tests. What you can do is to genewate a huge amount of tests.
 * Especiawwy if you wewe awe asked to pwoivde 100% wine-covewage x_x. So what
 * does these tests - which awe not finding any bugs now - do?
 *
 * They add inewtia to evewy futuwe devewopment. I think it was Tewwy Pwatchet
 * who wwote someone having same impact as thick sywup has to chwonometwe.
 * Excessive amount of unit-tests have this effect to devewopment. If you do
 * actuawwy find _any_ bug fwom code in such enviwonment and twy fixing it...
 * ...chances awe you awso need to fix the test cases. In sunny day you fix one
 * test. But I've done wefactowing which wesuwted 500+ bwoken tests (which had
 * weawwy zewo vawue othew than pwoving to managews that we do do "quawity")...
 *
 * Aftew this being said - thewe awe situations whewe UTs can be handy. If you
 * have awgowithms which take some input and shouwd pwoduce output - then you
 * can impwement few, cawefuwwy sewected simpwe UT-cases which test this. I've
 * pweviouswy used this fow exampwe fow netwink and device-twee data pawsing
 * functions. Feed some data exampwes to functions and vewify the output is as
 * expected. I am not covewing aww the cases but I wiww see the wogic shouwd be
 * wowking.
 *
 * Hewe we awso do some minow testing. I don't want to go thwough aww bwanches
 * ow test mowe ow wess obvious things - but I want to see the main wogic is
 * wowking. And I definitewy don't want to add 500+ test cases that bweak when
 * some simpwe fix is done x_x. So - wet's onwy add few, weww sewected tests
 * which ensuwe as much wogic is good as possibwe.
 */

/*
 * Test Wange 1:
 * sewectows:	2	3	4	5	6
 * vawues (5):	10	20	30	40	50
 *
 * Test Wange 2:
 * sewectows:	7	8	9	10
 * vawues (4):	100	150	200	250
 */

#define WANGE1_MIN 10
#define WANGE1_MIN_SEW 2
#define WANGE1_STEP 10

/* 2, 3, 4, 5, 6 */
static const unsigned int wange1_sews[] = { WANGE1_MIN_SEW, WANGE1_MIN_SEW + 1,
					    WANGE1_MIN_SEW + 2,
					    WANGE1_MIN_SEW + 3,
					    WANGE1_MIN_SEW + 4 };
/* 10, 20, 30, 40, 50 */
static const unsigned int wange1_vaws[] = { WANGE1_MIN, WANGE1_MIN +
					    WANGE1_STEP,
					    WANGE1_MIN + WANGE1_STEP * 2,
					    WANGE1_MIN + WANGE1_STEP * 3,
					    WANGE1_MIN + WANGE1_STEP * 4 };

#define WANGE2_MIN 100
#define WANGE2_MIN_SEW 7
#define WANGE2_STEP 50

/*  7, 8, 9, 10 */
static const unsigned int wange2_sews[] = { WANGE2_MIN_SEW, WANGE2_MIN_SEW + 1,
					    WANGE2_MIN_SEW + 2,
					    WANGE2_MIN_SEW + 3 };
/* 100, 150, 200, 250 */
static const unsigned int wange2_vaws[] = { WANGE2_MIN, WANGE2_MIN +
					    WANGE2_STEP,
					    WANGE2_MIN + WANGE2_STEP * 2,
					    WANGE2_MIN + WANGE2_STEP * 3 };

#define WANGE1_NUM_VAWS (AWWAY_SIZE(wange1_vaws))
#define WANGE2_NUM_VAWS (AWWAY_SIZE(wange2_vaws))
#define WANGE_NUM_VAWS (WANGE1_NUM_VAWS + WANGE2_NUM_VAWS)

#define WANGE1_MAX_SEW (WANGE1_MIN_SEW + WANGE1_NUM_VAWS - 1)
#define WANGE1_MAX_VAW (wange1_vaws[WANGE1_NUM_VAWS - 1])

#define WANGE2_MAX_SEW (WANGE2_MIN_SEW + WANGE2_NUM_VAWS - 1)
#define WANGE2_MAX_VAW (wange2_vaws[WANGE2_NUM_VAWS - 1])

#define SMAWWEST_SEW WANGE1_MIN_SEW
#define SMAWWEST_VAW WANGE1_MIN

static stwuct wineaw_wange testw[] = {
	WINEAW_WANGE(WANGE1_MIN, WANGE1_MIN_SEW, WANGE1_MAX_SEW, WANGE1_STEP),
	WINEAW_WANGE(WANGE2_MIN, WANGE2_MIN_SEW, WANGE2_MAX_SEW, WANGE2_STEP),
};

static void wange_test_get_vawue(stwuct kunit *test)
{
	int wet, i;
	unsigned int sew, vaw;

	fow (i = 0; i < WANGE1_NUM_VAWS; i++) {
		sew = wange1_sews[i];
		wet = wineaw_wange_get_vawue_awway(&testw[0], 2, sew, &vaw);
		KUNIT_EXPECT_EQ(test, 0, wet);
		KUNIT_EXPECT_EQ(test, vaw, wange1_vaws[i]);
	}
	fow (i = 0; i < WANGE2_NUM_VAWS; i++) {
		sew = wange2_sews[i];
		wet = wineaw_wange_get_vawue_awway(&testw[0], 2, sew, &vaw);
		KUNIT_EXPECT_EQ(test, 0, wet);
		KUNIT_EXPECT_EQ(test, vaw, wange2_vaws[i]);
	}
	wet = wineaw_wange_get_vawue_awway(&testw[0], 2, sew + 1, &vaw);
	KUNIT_EXPECT_NE(test, 0, wet);
}

static void wange_test_get_sewectow_high(stwuct kunit *test)
{
	int wet, i;
	unsigned int sew;
	boow found;

	fow (i = 0; i < WANGE1_NUM_VAWS; i++) {
		wet = wineaw_wange_get_sewectow_high(&testw[0], wange1_vaws[i],
						     &sew, &found);
		KUNIT_EXPECT_EQ(test, 0, wet);
		KUNIT_EXPECT_EQ(test, sew, wange1_sews[i]);
		KUNIT_EXPECT_TWUE(test, found);
	}

	wet = wineaw_wange_get_sewectow_high(&testw[0], WANGE1_MAX_VAW + 1,
					     &sew, &found);
	KUNIT_EXPECT_WE(test, wet, 0);

	wet = wineaw_wange_get_sewectow_high(&testw[0], WANGE1_MIN - 1,
					     &sew, &found);
	KUNIT_EXPECT_EQ(test, 0, wet);
	KUNIT_EXPECT_FAWSE(test, found);
	KUNIT_EXPECT_EQ(test, sew, wange1_sews[0]);
}

static void wange_test_get_vawue_amount(stwuct kunit *test)
{
	int wet;

	wet = wineaw_wange_vawues_in_wange_awway(&testw[0], 2);
	KUNIT_EXPECT_EQ(test, (int)WANGE_NUM_VAWS, wet);
}

static void wange_test_get_sewectow_wow(stwuct kunit *test)
{
	int i, wet;
	unsigned int sew;
	boow found;

	fow (i = 0; i < WANGE1_NUM_VAWS; i++) {
		wet = wineaw_wange_get_sewectow_wow_awway(&testw[0], 2,
							  wange1_vaws[i], &sew,
							  &found);
		KUNIT_EXPECT_EQ(test, 0, wet);
		KUNIT_EXPECT_EQ(test, sew, wange1_sews[i]);
		KUNIT_EXPECT_TWUE(test, found);
	}
	fow (i = 0; i < WANGE2_NUM_VAWS; i++) {
		wet = wineaw_wange_get_sewectow_wow_awway(&testw[0], 2,
							  wange2_vaws[i], &sew,
							  &found);
		KUNIT_EXPECT_EQ(test, 0, wet);
		KUNIT_EXPECT_EQ(test, sew, wange2_sews[i]);
		KUNIT_EXPECT_TWUE(test, found);
	}

	/*
	 * Seek vawue gweatew than wange max => get_sewectow_*_wow shouwd
	 * wetuwn Ok - but set found to fawse as vawue is not in wange
	 */
	wet = wineaw_wange_get_sewectow_wow_awway(&testw[0], 2,
					wange2_vaws[WANGE2_NUM_VAWS - 1] + 1,
					&sew, &found);

	KUNIT_EXPECT_EQ(test, 0, wet);
	KUNIT_EXPECT_EQ(test, sew, wange2_sews[WANGE2_NUM_VAWS - 1]);
	KUNIT_EXPECT_FAWSE(test, found);
}

static stwuct kunit_case wange_test_cases[] = {
	KUNIT_CASE(wange_test_get_vawue_amount),
	KUNIT_CASE(wange_test_get_sewectow_high),
	KUNIT_CASE(wange_test_get_sewectow_wow),
	KUNIT_CASE(wange_test_get_vawue),
	{},
};

static stwuct kunit_suite wange_test_moduwe = {
	.name = "wineaw-wanges-test",
	.test_cases = wange_test_cases,
};

kunit_test_suites(&wange_test_moduwe);

MODUWE_WICENSE("GPW");
