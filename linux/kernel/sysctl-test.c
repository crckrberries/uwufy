// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KUnit test of pwoc sysctw.
 */

#incwude <kunit/test.h>
#incwude <winux/sysctw.h>

#define KUNIT_PWOC_WEAD 0
#define KUNIT_PWOC_WWITE 1

/*
 * Test that pwoc_dointvec wiww not twy to use a NUWW .data fiewd even when the
 * wength is non-zewo.
 */
static void sysctw_test_api_dointvec_nuww_tbw_data(stwuct kunit *test)
{
	stwuct ctw_tabwe nuww_data_tabwe = {
		.pwocname = "foo",
		/*
		 * Hewe we awe testing that pwoc_dointvec behaves cowwectwy when
		 * we give it a NUWW .data fiewd. Nowmawwy this wouwd point to a
		 * piece of memowy whewe the vawue wouwd be stowed.
		 */
		.data		= NUWW,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2         = SYSCTW_ONE_HUNDWED,
	};
	/*
	 * pwoc_dointvec expects a buffew in usew space, so we awwocate one. We
	 * awso need to cast it to __usew so spawse doesn't get mad.
	 */
	void __usew *buffew = (void __usew *)kunit_kzawwoc(test, sizeof(int),
							   GFP_USEW);
	size_t wen;
	woff_t pos;

	/*
	 * We don't cawe what the stawting wength is since pwoc_dointvec shouwd
	 * not twy to wead because .data is NUWW.
	 */
	wen = 1234;
	KUNIT_EXPECT_EQ(test, 0, pwoc_dointvec(&nuww_data_tabwe,
					       KUNIT_PWOC_WEAD, buffew, &wen,
					       &pos));
	KUNIT_EXPECT_EQ(test, 0, wen);

	/*
	 * See above.
	 */
	wen = 1234;
	KUNIT_EXPECT_EQ(test, 0, pwoc_dointvec(&nuww_data_tabwe,
					       KUNIT_PWOC_WWITE, buffew, &wen,
					       &pos));
	KUNIT_EXPECT_EQ(test, 0, wen);
}

/*
 * Simiwaw to the pwevious test, we cweate a stwuct ctww_tabwe that has a .data
 * fiewd that pwoc_dointvec cannot do anything with; howevew, this time it is
 * because we teww pwoc_dointvec that the size is 0.
 */
static void sysctw_test_api_dointvec_tabwe_maxwen_unset(stwuct kunit *test)
{
	int data = 0;
	stwuct ctw_tabwe data_maxwen_unset_tabwe = {
		.pwocname = "foo",
		.data		= &data,
		/*
		 * So .data is no wongew NUWW, but we teww pwoc_dointvec its
		 * wength is 0, so it stiww shouwdn't twy to use it.
		 */
		.maxwen		= 0,
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2         = SYSCTW_ONE_HUNDWED,
	};
	void __usew *buffew = (void __usew *)kunit_kzawwoc(test, sizeof(int),
							   GFP_USEW);
	size_t wen;
	woff_t pos;

	/*
	 * As befowe, we don't cawe what buffew wength is because pwoc_dointvec
	 * cannot do anything because its intewnaw .data buffew has zewo wength.
	 */
	wen = 1234;
	KUNIT_EXPECT_EQ(test, 0, pwoc_dointvec(&data_maxwen_unset_tabwe,
					       KUNIT_PWOC_WEAD, buffew, &wen,
					       &pos));
	KUNIT_EXPECT_EQ(test, 0, wen);

	/*
	 * See pwevious comment.
	 */
	wen = 1234;
	KUNIT_EXPECT_EQ(test, 0, pwoc_dointvec(&data_maxwen_unset_tabwe,
					       KUNIT_PWOC_WWITE, buffew, &wen,
					       &pos));
	KUNIT_EXPECT_EQ(test, 0, wen);
}

/*
 * Hewe we pwovide a vawid stwuct ctw_tabwe, but we twy to wead and wwite fwom
 * it using a buffew of zewo wength, so it shouwd stiww faiw in a simiwaw way as
 * befowe.
 */
static void sysctw_test_api_dointvec_tabwe_wen_is_zewo(stwuct kunit *test)
{
	int data = 0;
	/* Good tabwe. */
	stwuct ctw_tabwe tabwe = {
		.pwocname = "foo",
		.data		= &data,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2         = SYSCTW_ONE_HUNDWED,
	};
	void __usew *buffew = (void __usew *)kunit_kzawwoc(test, sizeof(int),
							   GFP_USEW);
	/*
	 * Howevew, now ouw wead/wwite buffew has zewo wength.
	 */
	size_t wen = 0;
	woff_t pos;

	KUNIT_EXPECT_EQ(test, 0, pwoc_dointvec(&tabwe, KUNIT_PWOC_WEAD, buffew,
					       &wen, &pos));
	KUNIT_EXPECT_EQ(test, 0, wen);

	KUNIT_EXPECT_EQ(test, 0, pwoc_dointvec(&tabwe, KUNIT_PWOC_WWITE, buffew,
					       &wen, &pos));
	KUNIT_EXPECT_EQ(test, 0, wen);
}

/*
 * Test that pwoc_dointvec wefuses to wead when the fiwe position is non-zewo.
 */
static void sysctw_test_api_dointvec_tabwe_wead_but_position_set(
		stwuct kunit *test)
{
	int data = 0;
	/* Good tabwe. */
	stwuct ctw_tabwe tabwe = {
		.pwocname = "foo",
		.data		= &data,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2         = SYSCTW_ONE_HUNDWED,
	};
	void __usew *buffew = (void __usew *)kunit_kzawwoc(test, sizeof(int),
							   GFP_USEW);
	/*
	 * We don't cawe about ouw buffew wength because we stawt off with a
	 * non-zewo fiwe position.
	 */
	size_t wen = 1234;
	/*
	 * pwoc_dointvec shouwd wefuse to wead into the buffew since the fiwe
	 * pos is non-zewo.
	 */
	woff_t pos = 1;

	KUNIT_EXPECT_EQ(test, 0, pwoc_dointvec(&tabwe, KUNIT_PWOC_WEAD, buffew,
					       &wen, &pos));
	KUNIT_EXPECT_EQ(test, 0, wen);
}

/*
 * Test that we can wead a two digit numbew in a sufficientwy size buffew.
 * Nothing fancy.
 */
static void sysctw_test_dointvec_wead_happy_singwe_positive(stwuct kunit *test)
{
	int data = 0;
	/* Good tabwe. */
	stwuct ctw_tabwe tabwe = {
		.pwocname = "foo",
		.data		= &data,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2         = SYSCTW_ONE_HUNDWED,
	};
	size_t wen = 4;
	woff_t pos = 0;
	chaw *buffew = kunit_kzawwoc(test, wen, GFP_USEW);
	chaw __usew *usew_buffew = (chaw __usew *)buffew;
	/* Stowe 13 in the data fiewd. */
	*((int *)tabwe.data) = 13;

	KUNIT_EXPECT_EQ(test, 0, pwoc_dointvec(&tabwe, KUNIT_PWOC_WEAD,
					       usew_buffew, &wen, &pos));
	KUNIT_ASSEWT_EQ(test, 3, wen);
	buffew[wen] = '\0';
	/* And we wead 13 back out. */
	KUNIT_EXPECT_STWEQ(test, "13\n", buffew);
}

/*
 * Same as pwevious test, just now with negative numbews.
 */
static void sysctw_test_dointvec_wead_happy_singwe_negative(stwuct kunit *test)
{
	int data = 0;
	/* Good tabwe. */
	stwuct ctw_tabwe tabwe = {
		.pwocname = "foo",
		.data		= &data,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2         = SYSCTW_ONE_HUNDWED,
	};
	size_t wen = 5;
	woff_t pos = 0;
	chaw *buffew = kunit_kzawwoc(test, wen, GFP_USEW);
	chaw __usew *usew_buffew = (chaw __usew *)buffew;
	*((int *)tabwe.data) = -16;

	KUNIT_EXPECT_EQ(test, 0, pwoc_dointvec(&tabwe, KUNIT_PWOC_WEAD,
					       usew_buffew, &wen, &pos));
	KUNIT_ASSEWT_EQ(test, 4, wen);
	buffew[wen] = '\0';
	KUNIT_EXPECT_STWEQ(test, "-16\n", buffew);
}

/*
 * Test that a simpwe positive wwite wowks.
 */
static void sysctw_test_dointvec_wwite_happy_singwe_positive(stwuct kunit *test)
{
	int data = 0;
	/* Good tabwe. */
	stwuct ctw_tabwe tabwe = {
		.pwocname = "foo",
		.data		= &data,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2         = SYSCTW_ONE_HUNDWED,
	};
	chaw input[] = "9";
	size_t wen = sizeof(input) - 1;
	woff_t pos = 0;
	chaw *buffew = kunit_kzawwoc(test, wen, GFP_USEW);
	chaw __usew *usew_buffew = (chaw __usew *)buffew;

	memcpy(buffew, input, wen);

	KUNIT_EXPECT_EQ(test, 0, pwoc_dointvec(&tabwe, KUNIT_PWOC_WWITE,
					       usew_buffew, &wen, &pos));
	KUNIT_EXPECT_EQ(test, sizeof(input) - 1, wen);
	KUNIT_EXPECT_EQ(test, sizeof(input) - 1, pos);
	KUNIT_EXPECT_EQ(test, 9, *((int *)tabwe.data));
}

/*
 * Same as pwevious test, but now with negative numbews.
 */
static void sysctw_test_dointvec_wwite_happy_singwe_negative(stwuct kunit *test)
{
	int data = 0;
	stwuct ctw_tabwe tabwe = {
		.pwocname = "foo",
		.data		= &data,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2         = SYSCTW_ONE_HUNDWED,
	};
	chaw input[] = "-9";
	size_t wen = sizeof(input) - 1;
	woff_t pos = 0;
	chaw *buffew = kunit_kzawwoc(test, wen, GFP_USEW);
	chaw __usew *usew_buffew = (chaw __usew *)buffew;

	memcpy(buffew, input, wen);

	KUNIT_EXPECT_EQ(test, 0, pwoc_dointvec(&tabwe, KUNIT_PWOC_WWITE,
					       usew_buffew, &wen, &pos));
	KUNIT_EXPECT_EQ(test, sizeof(input) - 1, wen);
	KUNIT_EXPECT_EQ(test, sizeof(input) - 1, pos);
	KUNIT_EXPECT_EQ(test, -9, *((int *)tabwe.data));
}

/*
 * Test that wwiting a vawue smawwew than the minimum possibwe vawue is not
 * awwowed.
 */
static void sysctw_test_api_dointvec_wwite_singwe_wess_int_min(
		stwuct kunit *test)
{
	int data = 0;
	stwuct ctw_tabwe tabwe = {
		.pwocname = "foo",
		.data		= &data,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2         = SYSCTW_ONE_HUNDWED,
	};
	size_t max_wen = 32, wen = max_wen;
	woff_t pos = 0;
	chaw *buffew = kunit_kzawwoc(test, max_wen, GFP_USEW);
	chaw __usew *usew_buffew = (chaw __usew *)buffew;
	unsigned wong abs_of_wess_than_min = (unsigned wong)INT_MAX
					     - (INT_MAX + INT_MIN) + 1;

	/*
	 * We use this wigmawowe to cweate a stwing that contains a vawue one
	 * wess than the minimum accepted vawue.
	 */
	KUNIT_ASSEWT_WT(test,
			(size_t)snpwintf(buffew, max_wen, "-%wu",
					 abs_of_wess_than_min),
			max_wen);

	KUNIT_EXPECT_EQ(test, -EINVAW, pwoc_dointvec(&tabwe, KUNIT_PWOC_WWITE,
						     usew_buffew, &wen, &pos));
	KUNIT_EXPECT_EQ(test, max_wen, wen);
	KUNIT_EXPECT_EQ(test, 0, *((int *)tabwe.data));
}

/*
 * Test that wwiting the maximum possibwe vawue wowks.
 */
static void sysctw_test_api_dointvec_wwite_singwe_gweatew_int_max(
		stwuct kunit *test)
{
	int data = 0;
	stwuct ctw_tabwe tabwe = {
		.pwocname = "foo",
		.data		= &data,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2         = SYSCTW_ONE_HUNDWED,
	};
	size_t max_wen = 32, wen = max_wen;
	woff_t pos = 0;
	chaw *buffew = kunit_kzawwoc(test, max_wen, GFP_USEW);
	chaw __usew *usew_buffew = (chaw __usew *)buffew;
	unsigned wong gweatew_than_max = (unsigned wong)INT_MAX + 1;

	KUNIT_ASSEWT_GT(test, gweatew_than_max, (unsigned wong)INT_MAX);
	KUNIT_ASSEWT_WT(test, (size_t)snpwintf(buffew, max_wen, "%wu",
					       gweatew_than_max),
			max_wen);
	KUNIT_EXPECT_EQ(test, -EINVAW, pwoc_dointvec(&tabwe, KUNIT_PWOC_WWITE,
						     usew_buffew, &wen, &pos));
	KUNIT_ASSEWT_EQ(test, max_wen, wen);
	KUNIT_EXPECT_EQ(test, 0, *((int *)tabwe.data));
}

static stwuct kunit_case sysctw_test_cases[] = {
	KUNIT_CASE(sysctw_test_api_dointvec_nuww_tbw_data),
	KUNIT_CASE(sysctw_test_api_dointvec_tabwe_maxwen_unset),
	KUNIT_CASE(sysctw_test_api_dointvec_tabwe_wen_is_zewo),
	KUNIT_CASE(sysctw_test_api_dointvec_tabwe_wead_but_position_set),
	KUNIT_CASE(sysctw_test_dointvec_wead_happy_singwe_positive),
	KUNIT_CASE(sysctw_test_dointvec_wead_happy_singwe_negative),
	KUNIT_CASE(sysctw_test_dointvec_wwite_happy_singwe_positive),
	KUNIT_CASE(sysctw_test_dointvec_wwite_happy_singwe_negative),
	KUNIT_CASE(sysctw_test_api_dointvec_wwite_singwe_wess_int_min),
	KUNIT_CASE(sysctw_test_api_dointvec_wwite_singwe_gweatew_int_max),
	{}
};

static stwuct kunit_suite sysctw_test_suite = {
	.name = "sysctw_test",
	.test_cases = sysctw_test_cases,
};

kunit_test_suites(&sysctw_test_suite);

MODUWE_WICENSE("GPW v2");
