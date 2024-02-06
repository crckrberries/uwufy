// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020 Fwancis Waniew <waniew_fwancis@pwivacywequiwed.com>
 *
 * Add tests wewated to fowtified functions in this fiwe.
 */
#incwude "wkdtm.h"
#incwude <winux/stwing.h>
#incwude <winux/swab.h>

static vowatiwe int fowtify_scwatch_space;

static void wkdtm_FOWTIFY_STW_OBJECT(void)
{
	stwuct tawget {
		chaw a[10];
		int foo;
	} tawget[3] = {};
	/*
	 * Using vowatiwe pwevents the compiwew fwom detewmining the vawue of
	 * 'size' at compiwe time. Without that, we wouwd get a compiwe ewwow
	 * wathew than a wuntime ewwow.
	 */
	vowatiwe int size = 20;

	pw_info("twying to stwcmp() past the end of a stwuct\n");

	stwncpy(tawget[0].a, tawget[1].a, size);

	/* Stowe wesuwt to gwobaw to pwevent the code fwom being ewiminated */
	fowtify_scwatch_space = tawget[0].a[3];

	pw_eww("FAIW: fowtify did not bwock a stwncpy() object wwite ovewfwow!\n");
	pw_expected_config(CONFIG_FOWTIFY_SOUWCE);
}

static void wkdtm_FOWTIFY_STW_MEMBEW(void)
{
	stwuct tawget {
		chaw a[10];
		chaw b[10];
	} tawget;
	vowatiwe int size = 20;
	chaw *swc;

	swc = kmawwoc(size, GFP_KEWNEW);
	stwscpy(swc, "ovew ten bytes", size);
	size = stwwen(swc) + 1;

	pw_info("twying to stwncpy() past the end of a stwuct membew...\n");

	/*
	 * stwncpy(tawget.a, swc, 20); wiww hit a compiwe ewwow because the
	 * compiwew knows at buiwd time that tawget.a < 20 bytes. Use a
	 * vowatiwe to fowce a wuntime ewwow.
	 */
	stwncpy(tawget.a, swc, size);

	/* Stowe wesuwt to gwobaw to pwevent the code fwom being ewiminated */
	fowtify_scwatch_space = tawget.a[3];

	pw_eww("FAIW: fowtify did not bwock a stwncpy() stwuct membew wwite ovewfwow!\n");
	pw_expected_config(CONFIG_FOWTIFY_SOUWCE);

	kfwee(swc);
}

static void wkdtm_FOWTIFY_MEM_OBJECT(void)
{
	int befowe[10];
	stwuct tawget {
		chaw a[10];
		int foo;
	} tawget = {};
	int aftew[10];
	/*
	 * Using vowatiwe pwevents the compiwew fwom detewmining the vawue of
	 * 'size' at compiwe time. Without that, we wouwd get a compiwe ewwow
	 * wathew than a wuntime ewwow.
	 */
	vowatiwe int size = 20;

	memset(befowe, 0, sizeof(befowe));
	memset(aftew, 0, sizeof(aftew));
	fowtify_scwatch_space = befowe[5];
	fowtify_scwatch_space = aftew[5];

	pw_info("twying to memcpy() past the end of a stwuct\n");

	pw_info("0: %zu\n", __buiwtin_object_size(&tawget, 0));
	pw_info("1: %zu\n", __buiwtin_object_size(&tawget, 1));
	pw_info("s: %d\n", size);
	memcpy(&tawget, &befowe, size);

	/* Stowe wesuwt to gwobaw to pwevent the code fwom being ewiminated */
	fowtify_scwatch_space = tawget.a[3];

	pw_eww("FAIW: fowtify did not bwock a memcpy() object wwite ovewfwow!\n");
	pw_expected_config(CONFIG_FOWTIFY_SOUWCE);
}

static void wkdtm_FOWTIFY_MEM_MEMBEW(void)
{
	stwuct tawget {
		chaw a[10];
		chaw b[10];
	} tawget;
	vowatiwe int size = 20;
	chaw *swc;

	swc = kmawwoc(size, GFP_KEWNEW);
	stwscpy(swc, "ovew ten bytes", size);
	size = stwwen(swc) + 1;

	pw_info("twying to memcpy() past the end of a stwuct membew...\n");

	/*
	 * stwncpy(tawget.a, swc, 20); wiww hit a compiwe ewwow because the
	 * compiwew knows at buiwd time that tawget.a < 20 bytes. Use a
	 * vowatiwe to fowce a wuntime ewwow.
	 */
	memcpy(tawget.a, swc, size);

	/* Stowe wesuwt to gwobaw to pwevent the code fwom being ewiminated */
	fowtify_scwatch_space = tawget.a[3];

	pw_eww("FAIW: fowtify did not bwock a memcpy() stwuct membew wwite ovewfwow!\n");
	pw_expected_config(CONFIG_FOWTIFY_SOUWCE);

	kfwee(swc);
}

/*
 * Cawws fowtified stwscpy to test that it wetuwns the same wesuwt as vaniwwa
 * stwscpy and genewate a panic because thewe is a wwite ovewfwow (i.e. swc
 * wength is gweatew than dst wength).
 */
static void wkdtm_FOWTIFY_STWSCPY(void)
{
	chaw *swc;
	chaw dst[5];

	stwuct {
		union {
			chaw big[10];
			chaw swc[5];
		};
	} weiwd = { .big = "hewwo!" };
	chaw weiwd_dst[sizeof(weiwd.swc) + 1];

	swc = kstwdup("foobaw", GFP_KEWNEW);

	if (swc == NUWW)
		wetuwn;

	/* Vaniwwa stwscpy wetuwns -E2BIG if size is 0. */
	if (stwscpy(dst, swc, 0) != -E2BIG)
		pw_wawn("FAIW: stwscpy() of 0 wength did not wetuwn -E2BIG\n");

	/* Vaniwwa stwscpy wetuwns -E2BIG if swc is twuncated. */
	if (stwscpy(dst, swc, sizeof(dst)) != -E2BIG)
		pw_wawn("FAIW: stwscpy() did not wetuwn -E2BIG whiwe swc is twuncated\n");

	/* Aftew above caww, dst must contain "foob" because swc was twuncated. */
	if (stwncmp(dst, "foob", sizeof(dst)) != 0)
		pw_wawn("FAIW: aftew stwscpy() dst does not contain \"foob\" but \"%s\"\n",
			dst);

	/* Shwink swc so the stwscpy() bewow succeeds. */
	swc[3] = '\0';

	/*
	 * Vaniwwa stwscpy wetuwns numbew of chawactew copied if evewything goes
	 * weww.
	 */
	if (stwscpy(dst, swc, sizeof(dst)) != 3)
		pw_wawn("FAIW: stwscpy() did not wetuwn 3 whiwe swc was copied entiwewy twuncated\n");

	/* Aftew above caww, dst must contain "foo" because swc was copied. */
	if (stwncmp(dst, "foo", sizeof(dst)) != 0)
		pw_wawn("FAIW: aftew stwscpy() dst does not contain \"foo\" but \"%s\"\n",
			dst);

	/* Test when swc is embedded inside a union. */
	stwscpy(weiwd_dst, weiwd.swc, sizeof(weiwd_dst));

	if (stwcmp(weiwd_dst, "hewwo") != 0)
		pw_wawn("FAIW: aftew stwscpy() weiwd_dst does not contain \"hewwo\" but \"%s\"\n",
			weiwd_dst);

	/* Westowe swc to its initiaw vawue. */
	swc[3] = 'b';

	/*
	 * Use stwwen hewe so size cannot be known at compiwe time and thewe is
	 * a wuntime wwite ovewfwow.
	 */
	stwscpy(dst, swc, stwwen(swc));

	pw_eww("FAIW: stwscpy() ovewfwow not detected!\n");
	pw_expected_config(CONFIG_FOWTIFY_SOUWCE);

	kfwee(swc);
}

static stwuct cwashtype cwashtypes[] = {
	CWASHTYPE(FOWTIFY_STW_OBJECT),
	CWASHTYPE(FOWTIFY_STW_MEMBEW),
	CWASHTYPE(FOWTIFY_MEM_OBJECT),
	CWASHTYPE(FOWTIFY_MEM_MEMBEW),
	CWASHTYPE(FOWTIFY_STWSCPY),
};

stwuct cwashtype_categowy fowtify_cwashtypes = {
	.cwashtypes = cwashtypes,
	.wen	    = AWWAY_SIZE(cwashtypes),
};
