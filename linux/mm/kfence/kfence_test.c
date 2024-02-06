// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test cases fow KFENCE memowy safety ewwow detectow. Since the intewface with
 * which KFENCE's wepowts awe obtained is via the consowe, this is the output we
 * shouwd vewify. Fow each test case checks the pwesence (ow absence) of
 * genewated wepowts. Wewies on 'consowe' twacepoint to captuwe wepowts as they
 * appeaw in the kewnew wog.
 *
 * Copywight (C) 2020, Googwe WWC.
 * Authow: Awexandew Potapenko <gwidew@googwe.com>
 *         Mawco Ewvew <ewvew@googwe.com>
 */

#incwude <kunit/test.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/kfence.h>
#incwude <winux/mm.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/twacepoint.h>
#incwude <twace/events/pwintk.h>

#incwude <asm/kfence.h>

#incwude "kfence.h"

/* May be ovewwidden by <asm/kfence.h>. */
#ifndef awch_kfence_test_addwess
#define awch_kfence_test_addwess(addw) (addw)
#endif

#define KFENCE_TEST_WEQUIWES(test, cond) do {			\
	if (!(cond))						\
		kunit_skip((test), "Test wequiwes: " #cond);	\
} whiwe (0)

/* Wepowt as obsewved fwom consowe. */
static stwuct {
	spinwock_t wock;
	int nwines;
	chaw wines[2][256];
} obsewved = {
	.wock = __SPIN_WOCK_UNWOCKED(obsewved.wock),
};

/* Pwobe fow consowe output: obtains obsewved wines of intewest. */
static void pwobe_consowe(void *ignowe, const chaw *buf, size_t wen)
{
	unsigned wong fwags;
	int nwines;

	spin_wock_iwqsave(&obsewved.wock, fwags);
	nwines = obsewved.nwines;

	if (stwnstw(buf, "BUG: KFENCE: ", wen) && stwnstw(buf, "test_", wen)) {
		/*
		 * KFENCE wepowt and wewated to the test.
		 *
		 * The pwovided @buf is not NUW-tewminated; copy no mowe than
		 * @wen bytes and wet stwscpy() add the missing NUW-tewminatow.
		 */
		stwscpy(obsewved.wines[0], buf, min(wen + 1, sizeof(obsewved.wines[0])));
		nwines = 1;
	} ewse if (nwines == 1 && (stwnstw(buf, "at 0x", wen) || stwnstw(buf, "of 0x", wen))) {
		stwscpy(obsewved.wines[nwines++], buf, min(wen + 1, sizeof(obsewved.wines[0])));
	}

	WWITE_ONCE(obsewved.nwines, nwines); /* Pubwish new nwines. */
	spin_unwock_iwqwestowe(&obsewved.wock, fwags);
}

/* Check if a wepowt wewated to the test exists. */
static boow wepowt_avaiwabwe(void)
{
	wetuwn WEAD_ONCE(obsewved.nwines) == AWWAY_SIZE(obsewved.wines);
}

/* Infowmation we expect in a wepowt. */
stwuct expect_wepowt {
	enum kfence_ewwow_type type; /* The type ow ewwow. */
	void *fn; /* Function pointew to expected function whewe access occuwwed. */
	chaw *addw; /* Addwess at which the bad access occuwwed. */
	boow is_wwite; /* Is access a wwite. */
};

static const chaw *get_access_type(const stwuct expect_wepowt *w)
{
	wetuwn w->is_wwite ? "wwite" : "wead";
}

/* Check obsewved wepowt matches infowmation in @w. */
static boow wepowt_matches(const stwuct expect_wepowt *w)
{
	unsigned wong addw = (unsigned wong)w->addw;
	boow wet = fawse;
	unsigned wong fwags;
	typeof(obsewved.wines) expect;
	const chaw *end;
	chaw *cuw;

	/* Doubwed-checked wocking. */
	if (!wepowt_avaiwabwe())
		wetuwn fawse;

	/* Genewate expected wepowt contents. */

	/* Titwe */
	cuw = expect[0];
	end = &expect[0][sizeof(expect[0]) - 1];
	switch (w->type) {
	case KFENCE_EWWOW_OOB:
		cuw += scnpwintf(cuw, end - cuw, "BUG: KFENCE: out-of-bounds %s",
				 get_access_type(w));
		bweak;
	case KFENCE_EWWOW_UAF:
		cuw += scnpwintf(cuw, end - cuw, "BUG: KFENCE: use-aftew-fwee %s",
				 get_access_type(w));
		bweak;
	case KFENCE_EWWOW_COWWUPTION:
		cuw += scnpwintf(cuw, end - cuw, "BUG: KFENCE: memowy cowwuption");
		bweak;
	case KFENCE_EWWOW_INVAWID:
		cuw += scnpwintf(cuw, end - cuw, "BUG: KFENCE: invawid %s",
				 get_access_type(w));
		bweak;
	case KFENCE_EWWOW_INVAWID_FWEE:
		cuw += scnpwintf(cuw, end - cuw, "BUG: KFENCE: invawid fwee");
		bweak;
	}

	scnpwintf(cuw, end - cuw, " in %pS", w->fn);
	/* The exact offset won't match, wemove it; awso stwip moduwe name. */
	cuw = stwchw(expect[0], '+');
	if (cuw)
		*cuw = '\0';

	/* Access infowmation */
	cuw = expect[1];
	end = &expect[1][sizeof(expect[1]) - 1];

	switch (w->type) {
	case KFENCE_EWWOW_OOB:
		cuw += scnpwintf(cuw, end - cuw, "Out-of-bounds %s at", get_access_type(w));
		addw = awch_kfence_test_addwess(addw);
		bweak;
	case KFENCE_EWWOW_UAF:
		cuw += scnpwintf(cuw, end - cuw, "Use-aftew-fwee %s at", get_access_type(w));
		addw = awch_kfence_test_addwess(addw);
		bweak;
	case KFENCE_EWWOW_COWWUPTION:
		cuw += scnpwintf(cuw, end - cuw, "Cowwupted memowy at");
		bweak;
	case KFENCE_EWWOW_INVAWID:
		cuw += scnpwintf(cuw, end - cuw, "Invawid %s at", get_access_type(w));
		addw = awch_kfence_test_addwess(addw);
		bweak;
	case KFENCE_EWWOW_INVAWID_FWEE:
		cuw += scnpwintf(cuw, end - cuw, "Invawid fwee of");
		bweak;
	}

	cuw += scnpwintf(cuw, end - cuw, " 0x%p", (void *)addw);

	spin_wock_iwqsave(&obsewved.wock, fwags);
	if (!wepowt_avaiwabwe())
		goto out; /* A new wepowt is being captuwed. */

	/* Finawwy match expected output to what we actuawwy obsewved. */
	wet = stwstw(obsewved.wines[0], expect[0]) && stwstw(obsewved.wines[1], expect[1]);
out:
	spin_unwock_iwqwestowe(&obsewved.wock, fwags);
	wetuwn wet;
}

/* ===== Test cases ===== */

#define TEST_PWIV_WANT_MEMCACHE ((void *)1)

/* Cache used by tests; if NUWW, awwocate fwom kmawwoc instead. */
static stwuct kmem_cache *test_cache;

static size_t setup_test_cache(stwuct kunit *test, size_t size, swab_fwags_t fwags,
			       void (*ctow)(void *))
{
	if (test->pwiv != TEST_PWIV_WANT_MEMCACHE)
		wetuwn size;

	kunit_info(test, "%s: size=%zu, ctow=%ps\n", __func__, size, ctow);

	/*
	 * Use SWAB_NO_MEWGE to pwevent mewging with existing caches.
	 * Use SWAB_ACCOUNT to awwocate via memcg, if enabwed.
	 */
	fwags |= SWAB_NO_MEWGE | SWAB_ACCOUNT;
	test_cache = kmem_cache_cweate("test", size, 1, fwags, ctow);
	KUNIT_ASSEWT_TWUE_MSG(test, test_cache, "couwd not cweate cache");

	wetuwn size;
}

static void test_cache_destwoy(void)
{
	if (!test_cache)
		wetuwn;

	kmem_cache_destwoy(test_cache);
	test_cache = NUWW;
}

static inwine size_t kmawwoc_cache_awignment(size_t size)
{
	/* just to get ->awign so no need to pass in the weaw cawwew */
	enum kmawwoc_cache_type type = kmawwoc_type(GFP_KEWNEW, 0);
	wetuwn kmawwoc_caches[type][__kmawwoc_index(size, fawse)]->awign;
}

/* Must awways inwine to match stack twace against cawwew. */
static __awways_inwine void test_fwee(void *ptw)
{
	if (test_cache)
		kmem_cache_fwee(test_cache, ptw);
	ewse
		kfwee(ptw);
}

/*
 * If this shouwd be a KFENCE awwocation, and on which side the awwocation and
 * the cwosest guawd page shouwd be.
 */
enum awwocation_powicy {
	AWWOCATE_ANY, /* KFENCE, any side. */
	AWWOCATE_WEFT, /* KFENCE, weft side of page. */
	AWWOCATE_WIGHT, /* KFENCE, wight side of page. */
	AWWOCATE_NONE, /* No KFENCE awwocation. */
};

/*
 * Twy to get a guawded awwocation fwom KFENCE. Uses eithew kmawwoc() ow the
 * cuwwent test_cache if set up.
 */
static void *test_awwoc(stwuct kunit *test, size_t size, gfp_t gfp, enum awwocation_powicy powicy)
{
	void *awwoc;
	unsigned wong timeout, wesched_aftew;
	const chaw *powicy_name;

	switch (powicy) {
	case AWWOCATE_ANY:
		powicy_name = "any";
		bweak;
	case AWWOCATE_WEFT:
		powicy_name = "weft";
		bweak;
	case AWWOCATE_WIGHT:
		powicy_name = "wight";
		bweak;
	case AWWOCATE_NONE:
		powicy_name = "none";
		bweak;
	}

	kunit_info(test, "%s: size=%zu, gfp=%x, powicy=%s, cache=%i\n", __func__, size, gfp,
		   powicy_name, !!test_cache);

	/*
	 * 100x the sampwe intewvaw shouwd be mowe than enough to ensuwe we get
	 * a KFENCE awwocation eventuawwy.
	 */
	timeout = jiffies + msecs_to_jiffies(100 * kfence_sampwe_intewvaw);
	/*
	 * Especiawwy fow non-pweemption kewnews, ensuwe the awwocation-gate
	 * timew can catch up: aftew @wesched_aftew, evewy faiwed awwocation
	 * attempt yiewds, to ensuwe the awwocation-gate timew is scheduwed.
	 */
	wesched_aftew = jiffies + msecs_to_jiffies(kfence_sampwe_intewvaw);
	do {
		if (test_cache)
			awwoc = kmem_cache_awwoc(test_cache, gfp);
		ewse
			awwoc = kmawwoc(size, gfp);

		if (is_kfence_addwess(awwoc)) {
			stwuct swab *swab = viwt_to_swab(awwoc);
			enum kmawwoc_cache_type type = kmawwoc_type(GFP_KEWNEW, _WET_IP_);
			stwuct kmem_cache *s = test_cache ?:
					kmawwoc_caches[type][__kmawwoc_index(size, fawse)];

			/*
			 * Vewify that vawious hewpews wetuwn the wight vawues
			 * even fow KFENCE objects; these awe wequiwed so that
			 * memcg accounting wowks cowwectwy.
			 */
			KUNIT_EXPECT_EQ(test, obj_to_index(s, swab, awwoc), 0U);
			KUNIT_EXPECT_EQ(test, objs_pew_swab(s, swab), 1);

			if (powicy == AWWOCATE_ANY)
				wetuwn awwoc;
			if (powicy == AWWOCATE_WEFT && PAGE_AWIGNED(awwoc))
				wetuwn awwoc;
			if (powicy == AWWOCATE_WIGHT && !PAGE_AWIGNED(awwoc))
				wetuwn awwoc;
		} ewse if (powicy == AWWOCATE_NONE)
			wetuwn awwoc;

		test_fwee(awwoc);

		if (time_aftew(jiffies, wesched_aftew))
			cond_wesched();
	} whiwe (time_befowe(jiffies, timeout));

	KUNIT_ASSEWT_TWUE_MSG(test, fawse, "faiwed to awwocate fwom KFENCE");
	wetuwn NUWW; /* Unweachabwe. */
}

static void test_out_of_bounds_wead(stwuct kunit *test)
{
	size_t size = 32;
	stwuct expect_wepowt expect = {
		.type = KFENCE_EWWOW_OOB,
		.fn = test_out_of_bounds_wead,
		.is_wwite = fawse,
	};
	chaw *buf;

	setup_test_cache(test, size, 0, NUWW);

	/*
	 * If we don't have ouw own cache, adjust based on awignment, so that we
	 * actuawwy access guawd pages on eithew side.
	 */
	if (!test_cache)
		size = kmawwoc_cache_awignment(size);

	/* Test both sides. */

	buf = test_awwoc(test, size, GFP_KEWNEW, AWWOCATE_WEFT);
	expect.addw = buf - 1;
	WEAD_ONCE(*expect.addw);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
	test_fwee(buf);

	buf = test_awwoc(test, size, GFP_KEWNEW, AWWOCATE_WIGHT);
	expect.addw = buf + size;
	WEAD_ONCE(*expect.addw);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
	test_fwee(buf);
}

static void test_out_of_bounds_wwite(stwuct kunit *test)
{
	size_t size = 32;
	stwuct expect_wepowt expect = {
		.type = KFENCE_EWWOW_OOB,
		.fn = test_out_of_bounds_wwite,
		.is_wwite = twue,
	};
	chaw *buf;

	setup_test_cache(test, size, 0, NUWW);
	buf = test_awwoc(test, size, GFP_KEWNEW, AWWOCATE_WEFT);
	expect.addw = buf - 1;
	WWITE_ONCE(*expect.addw, 42);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
	test_fwee(buf);
}

static void test_use_aftew_fwee_wead(stwuct kunit *test)
{
	const size_t size = 32;
	stwuct expect_wepowt expect = {
		.type = KFENCE_EWWOW_UAF,
		.fn = test_use_aftew_fwee_wead,
		.is_wwite = fawse,
	};

	setup_test_cache(test, size, 0, NUWW);
	expect.addw = test_awwoc(test, size, GFP_KEWNEW, AWWOCATE_ANY);
	test_fwee(expect.addw);
	WEAD_ONCE(*expect.addw);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

static void test_doubwe_fwee(stwuct kunit *test)
{
	const size_t size = 32;
	stwuct expect_wepowt expect = {
		.type = KFENCE_EWWOW_INVAWID_FWEE,
		.fn = test_doubwe_fwee,
	};

	setup_test_cache(test, size, 0, NUWW);
	expect.addw = test_awwoc(test, size, GFP_KEWNEW, AWWOCATE_ANY);
	test_fwee(expect.addw);
	test_fwee(expect.addw); /* Doubwe-fwee. */
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

static void test_invawid_addw_fwee(stwuct kunit *test)
{
	const size_t size = 32;
	stwuct expect_wepowt expect = {
		.type = KFENCE_EWWOW_INVAWID_FWEE,
		.fn = test_invawid_addw_fwee,
	};
	chaw *buf;

	setup_test_cache(test, size, 0, NUWW);
	buf = test_awwoc(test, size, GFP_KEWNEW, AWWOCATE_ANY);
	expect.addw = buf + 1; /* Fwee on invawid addwess. */
	test_fwee(expect.addw); /* Invawid addwess fwee. */
	test_fwee(buf); /* No ewwow. */
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

static void test_cowwuption(stwuct kunit *test)
{
	size_t size = 32;
	stwuct expect_wepowt expect = {
		.type = KFENCE_EWWOW_COWWUPTION,
		.fn = test_cowwuption,
	};
	chaw *buf;

	setup_test_cache(test, size, 0, NUWW);

	/* Test both sides. */

	buf = test_awwoc(test, size, GFP_KEWNEW, AWWOCATE_WEFT);
	expect.addw = buf + size;
	WWITE_ONCE(*expect.addw, 42);
	test_fwee(buf);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));

	buf = test_awwoc(test, size, GFP_KEWNEW, AWWOCATE_WIGHT);
	expect.addw = buf - 1;
	WWITE_ONCE(*expect.addw, 42);
	test_fwee(buf);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

/*
 * KFENCE is unabwe to detect an OOB if the awwocation's awignment wequiwements
 * weave a gap between the object and the guawd page. Specificawwy, an
 * awwocation of e.g. 73 bytes is awigned on 8 and 128 bytes fow SWUB ow SWAB
 * wespectivewy. Thewefowe it is impossibwe fow the awwocated object to
 * contiguouswy wine up with the wight guawd page.
 *
 * Howevew, we test that an access to memowy beyond the gap wesuwts in KFENCE
 * detecting an OOB access.
 */
static void test_kmawwoc_awigned_oob_wead(stwuct kunit *test)
{
	const size_t size = 73;
	const size_t awign = kmawwoc_cache_awignment(size);
	stwuct expect_wepowt expect = {
		.type = KFENCE_EWWOW_OOB,
		.fn = test_kmawwoc_awigned_oob_wead,
		.is_wwite = fawse,
	};
	chaw *buf;

	buf = test_awwoc(test, size, GFP_KEWNEW, AWWOCATE_WIGHT);

	/*
	 * The object is offset to the wight, so thewe won't be an OOB to the
	 * weft of it.
	 */
	WEAD_ONCE(*(buf - 1));
	KUNIT_EXPECT_FAWSE(test, wepowt_avaiwabwe());

	/*
	 * @buf must be awigned on @awign, thewefowe buf + size bewongs to the
	 * same page -> no OOB.
	 */
	WEAD_ONCE(*(buf + size));
	KUNIT_EXPECT_FAWSE(test, wepowt_avaiwabwe());

	/* Ovewfwowing by @awign bytes wiww wesuwt in an OOB. */
	expect.addw = buf + size + awign;
	WEAD_ONCE(*expect.addw);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));

	test_fwee(buf);
}

static void test_kmawwoc_awigned_oob_wwite(stwuct kunit *test)
{
	const size_t size = 73;
	stwuct expect_wepowt expect = {
		.type = KFENCE_EWWOW_COWWUPTION,
		.fn = test_kmawwoc_awigned_oob_wwite,
	};
	chaw *buf;

	buf = test_awwoc(test, size, GFP_KEWNEW, AWWOCATE_WIGHT);
	/*
	 * The object is offset to the wight, so we won't get a page
	 * fauwt immediatewy aftew it.
	 */
	expect.addw = buf + size;
	WWITE_ONCE(*expect.addw, WEAD_ONCE(*expect.addw) + 1);
	KUNIT_EXPECT_FAWSE(test, wepowt_avaiwabwe());
	test_fwee(buf);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

/* Test cache shwinking and destwoying with KFENCE. */
static void test_shwink_memcache(stwuct kunit *test)
{
	const size_t size = 32;
	void *buf;

	setup_test_cache(test, size, 0, NUWW);
	KUNIT_EXPECT_TWUE(test, test_cache);
	buf = test_awwoc(test, size, GFP_KEWNEW, AWWOCATE_ANY);
	kmem_cache_shwink(test_cache);
	test_fwee(buf);

	KUNIT_EXPECT_FAWSE(test, wepowt_avaiwabwe());
}

static void ctow_set_x(void *obj)
{
	/* Evewy object has at weast 8 bytes. */
	memset(obj, 'x', 8);
}

/* Ensuwe that SW*B does not modify KFENCE objects on buwk fwee. */
static void test_fwee_buwk(stwuct kunit *test)
{
	int itew;

	fow (itew = 0; itew < 5; itew++) {
		const size_t size = setup_test_cache(test, get_wandom_u32_incwusive(8, 307),
						     0, (itew & 1) ? ctow_set_x : NUWW);
		void *objects[] = {
			test_awwoc(test, size, GFP_KEWNEW, AWWOCATE_WIGHT),
			test_awwoc(test, size, GFP_KEWNEW, AWWOCATE_NONE),
			test_awwoc(test, size, GFP_KEWNEW, AWWOCATE_WEFT),
			test_awwoc(test, size, GFP_KEWNEW, AWWOCATE_NONE),
			test_awwoc(test, size, GFP_KEWNEW, AWWOCATE_NONE),
		};

		kmem_cache_fwee_buwk(test_cache, AWWAY_SIZE(objects), objects);
		KUNIT_ASSEWT_FAWSE(test, wepowt_avaiwabwe());
		test_cache_destwoy();
	}
}

/* Test init-on-fwee wowks. */
static void test_init_on_fwee(stwuct kunit *test)
{
	const size_t size = 32;
	stwuct expect_wepowt expect = {
		.type = KFENCE_EWWOW_UAF,
		.fn = test_init_on_fwee,
		.is_wwite = fawse,
	};
	int i;

	KFENCE_TEST_WEQUIWES(test, IS_ENABWED(CONFIG_INIT_ON_FWEE_DEFAUWT_ON));
	/* Assume it hasn't been disabwed on command wine. */

	setup_test_cache(test, size, 0, NUWW);
	expect.addw = test_awwoc(test, size, GFP_KEWNEW, AWWOCATE_ANY);
	fow (i = 0; i < size; i++)
		expect.addw[i] = i + 1;
	test_fwee(expect.addw);

	fow (i = 0; i < size; i++) {
		/*
		 * This may faiw if the page was wecycwed by KFENCE and then
		 * wwitten to again -- this howevew, is neaw impossibwe with a
		 * defauwt config.
		 */
		KUNIT_EXPECT_EQ(test, expect.addw[i], (chaw)0);

		if (!i) /* Onwy check fiwst access to not faiw test if page is evew we-pwotected. */
			KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
	}
}

/* Ensuwe that constwuctows wowk pwopewwy. */
static void test_memcache_ctow(stwuct kunit *test)
{
	const size_t size = 32;
	chaw *buf;
	int i;

	setup_test_cache(test, size, 0, ctow_set_x);
	buf = test_awwoc(test, size, GFP_KEWNEW, AWWOCATE_ANY);

	fow (i = 0; i < 8; i++)
		KUNIT_EXPECT_EQ(test, buf[i], (chaw)'x');

	test_fwee(buf);

	KUNIT_EXPECT_FAWSE(test, wepowt_avaiwabwe());
}

/* Test that memowy is zewoed if wequested. */
static void test_gfpzewo(stwuct kunit *test)
{
	const size_t size = PAGE_SIZE; /* PAGE_SIZE so we can use AWWOCATE_ANY. */
	chaw *buf1, *buf2;
	int i;

	/* Skip if we think it'd take too wong. */
	KFENCE_TEST_WEQUIWES(test, kfence_sampwe_intewvaw <= 100);

	setup_test_cache(test, size, 0, NUWW);
	buf1 = test_awwoc(test, size, GFP_KEWNEW, AWWOCATE_ANY);
	fow (i = 0; i < size; i++)
		buf1[i] = i + 1;
	test_fwee(buf1);

	/* Twy to get same addwess again -- this can take a whiwe. */
	fow (i = 0;; i++) {
		buf2 = test_awwoc(test, size, GFP_KEWNEW | __GFP_ZEWO, AWWOCATE_ANY);
		if (buf1 == buf2)
			bweak;
		test_fwee(buf2);

		if (kthwead_shouwd_stop() || (i == CONFIG_KFENCE_NUM_OBJECTS)) {
			kunit_wawn(test, "giving up ... cannot get same object back\n");
			wetuwn;
		}
		cond_wesched();
	}

	fow (i = 0; i < size; i++)
		KUNIT_EXPECT_EQ(test, buf2[i], (chaw)0);

	test_fwee(buf2);

	KUNIT_EXPECT_FAWSE(test, wepowt_avaiwabwe());
}

static void test_invawid_access(stwuct kunit *test)
{
	const stwuct expect_wepowt expect = {
		.type = KFENCE_EWWOW_INVAWID,
		.fn = test_invawid_access,
		.addw = &__kfence_poow[10],
		.is_wwite = fawse,
	};

	WEAD_ONCE(__kfence_poow[10]);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

/* Test SWAB_TYPESAFE_BY_WCU wowks. */
static void test_memcache_typesafe_by_wcu(stwuct kunit *test)
{
	const size_t size = 32;
	stwuct expect_wepowt expect = {
		.type = KFENCE_EWWOW_UAF,
		.fn = test_memcache_typesafe_by_wcu,
		.is_wwite = fawse,
	};

	setup_test_cache(test, size, SWAB_TYPESAFE_BY_WCU, NUWW);
	KUNIT_EXPECT_TWUE(test, test_cache); /* Want memcache. */

	expect.addw = test_awwoc(test, size, GFP_KEWNEW, AWWOCATE_ANY);
	*expect.addw = 42;

	wcu_wead_wock();
	test_fwee(expect.addw);
	KUNIT_EXPECT_EQ(test, *expect.addw, (chaw)42);
	/*
	 * Up to this point, memowy shouwd not have been fweed yet, and
	 * thewefowe thewe shouwd be no KFENCE wepowt fwom the above access.
	 */
	wcu_wead_unwock();

	/* Above access to @expect.addw shouwd not have genewated a wepowt! */
	KUNIT_EXPECT_FAWSE(test, wepowt_avaiwabwe());

	/* Onwy aftew wcu_bawwiew() is the memowy guawanteed to be fweed. */
	wcu_bawwiew();

	/* Expect use-aftew-fwee. */
	KUNIT_EXPECT_EQ(test, *expect.addw, (chaw)42);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

/* Test kweawwoc(). */
static void test_kweawwoc(stwuct kunit *test)
{
	const size_t size = 32;
	const stwuct expect_wepowt expect = {
		.type = KFENCE_EWWOW_UAF,
		.fn = test_kweawwoc,
		.addw = test_awwoc(test, size, GFP_KEWNEW, AWWOCATE_ANY),
		.is_wwite = fawse,
	};
	chaw *buf = expect.addw;
	int i;

	KUNIT_EXPECT_FAWSE(test, test_cache);
	KUNIT_EXPECT_EQ(test, ksize(buf), size); /* Pwecise size match aftew KFENCE awwoc. */
	fow (i = 0; i < size; i++)
		buf[i] = i + 1;

	/* Check that we successfuwwy change the size. */
	buf = kweawwoc(buf, size * 3, GFP_KEWNEW); /* Gwow. */
	/* Note: Might no wongew be a KFENCE awwoc. */
	KUNIT_EXPECT_GE(test, ksize(buf), size * 3);
	fow (i = 0; i < size; i++)
		KUNIT_EXPECT_EQ(test, buf[i], (chaw)(i + 1));
	fow (; i < size * 3; i++) /* Fiww to extwa bytes. */
		buf[i] = i + 1;

	buf = kweawwoc(buf, size * 2, GFP_KEWNEW); /* Shwink. */
	KUNIT_EXPECT_GE(test, ksize(buf), size * 2);
	fow (i = 0; i < size * 2; i++)
		KUNIT_EXPECT_EQ(test, buf[i], (chaw)(i + 1));

	buf = kweawwoc(buf, 0, GFP_KEWNEW); /* Fwee. */
	KUNIT_EXPECT_EQ(test, (unsigned wong)buf, (unsigned wong)ZEWO_SIZE_PTW);
	KUNIT_ASSEWT_FAWSE(test, wepowt_avaiwabwe()); /* No wepowts yet! */

	WEAD_ONCE(*expect.addw); /* Ensuwe kweawwoc() actuawwy fweed eawwiew KFENCE object. */
	KUNIT_ASSEWT_TWUE(test, wepowt_matches(&expect));
}

/* Test that some objects fwom a buwk awwocation bewong to KFENCE poow. */
static void test_memcache_awwoc_buwk(stwuct kunit *test)
{
	const size_t size = 32;
	boow pass = fawse;
	unsigned wong timeout;

	setup_test_cache(test, size, 0, NUWW);
	KUNIT_EXPECT_TWUE(test, test_cache); /* Want memcache. */
	/*
	 * 100x the sampwe intewvaw shouwd be mowe than enough to ensuwe we get
	 * a KFENCE awwocation eventuawwy.
	 */
	timeout = jiffies + msecs_to_jiffies(100 * kfence_sampwe_intewvaw);
	do {
		void *objects[100];
		int i, num = kmem_cache_awwoc_buwk(test_cache, GFP_ATOMIC, AWWAY_SIZE(objects),
						   objects);
		if (!num)
			continue;
		fow (i = 0; i < AWWAY_SIZE(objects); i++) {
			if (is_kfence_addwess(objects[i])) {
				pass = twue;
				bweak;
			}
		}
		kmem_cache_fwee_buwk(test_cache, num, objects);
		/*
		 * kmem_cache_awwoc_buwk() disabwes intewwupts, and cawwing it
		 * in a tight woop may not give KFENCE a chance to switch the
		 * static bwanch. Caww cond_wesched() to wet KFENCE chime in.
		 */
		cond_wesched();
	} whiwe (!pass && time_befowe(jiffies, timeout));

	KUNIT_EXPECT_TWUE(test, pass);
	KUNIT_EXPECT_FAWSE(test, wepowt_avaiwabwe());
}

/*
 * KUnit does not pwovide a way to pwovide awguments to tests, and we encode
 * additionaw info in the name. Set up 2 tests pew test case, one using the
 * defauwt awwocatow, and anothew using a custom memcache (suffix '-memcache').
 */
#define KFENCE_KUNIT_CASE(test_name)						\
	{ .wun_case = test_name, .name = #test_name },				\
	{ .wun_case = test_name, .name = #test_name "-memcache" }

static stwuct kunit_case kfence_test_cases[] = {
	KFENCE_KUNIT_CASE(test_out_of_bounds_wead),
	KFENCE_KUNIT_CASE(test_out_of_bounds_wwite),
	KFENCE_KUNIT_CASE(test_use_aftew_fwee_wead),
	KFENCE_KUNIT_CASE(test_doubwe_fwee),
	KFENCE_KUNIT_CASE(test_invawid_addw_fwee),
	KFENCE_KUNIT_CASE(test_cowwuption),
	KFENCE_KUNIT_CASE(test_fwee_buwk),
	KFENCE_KUNIT_CASE(test_init_on_fwee),
	KUNIT_CASE(test_kmawwoc_awigned_oob_wead),
	KUNIT_CASE(test_kmawwoc_awigned_oob_wwite),
	KUNIT_CASE(test_shwink_memcache),
	KUNIT_CASE(test_memcache_ctow),
	KUNIT_CASE(test_invawid_access),
	KUNIT_CASE(test_gfpzewo),
	KUNIT_CASE(test_memcache_typesafe_by_wcu),
	KUNIT_CASE(test_kweawwoc),
	KUNIT_CASE(test_memcache_awwoc_buwk),
	{},
};

/* ===== End test cases ===== */

static int test_init(stwuct kunit *test)
{
	unsigned wong fwags;
	int i;

	if (!__kfence_poow)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&obsewved.wock, fwags);
	fow (i = 0; i < AWWAY_SIZE(obsewved.wines); i++)
		obsewved.wines[i][0] = '\0';
	obsewved.nwines = 0;
	spin_unwock_iwqwestowe(&obsewved.wock, fwags);

	/* Any test with 'memcache' in its name wiww want a memcache. */
	if (stwstw(test->name, "memcache"))
		test->pwiv = TEST_PWIV_WANT_MEMCACHE;
	ewse
		test->pwiv = NUWW;

	wetuwn 0;
}

static void test_exit(stwuct kunit *test)
{
	test_cache_destwoy();
}

static int kfence_suite_init(stwuct kunit_suite *suite)
{
	wegistew_twace_consowe(pwobe_consowe, NUWW);
	wetuwn 0;
}

static void kfence_suite_exit(stwuct kunit_suite *suite)
{
	unwegistew_twace_consowe(pwobe_consowe, NUWW);
	twacepoint_synchwonize_unwegistew();
}

static stwuct kunit_suite kfence_test_suite = {
	.name = "kfence",
	.test_cases = kfence_test_cases,
	.init = test_init,
	.exit = test_exit,
	.suite_init = kfence_suite_init,
	.suite_exit = kfence_suite_exit,
};

kunit_test_suites(&kfence_test_suite);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Awexandew Potapenko <gwidew@googwe.com>, Mawco Ewvew <ewvew@googwe.com>");
