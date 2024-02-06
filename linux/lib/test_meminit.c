// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test cases fow SW[AOU]B/page initiawization at awwoc/fwee time.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/vmawwoc.h>

#define GAWBAGE_INT (0x09A7BA9E)
#define GAWBAGE_BYTE (0x9E)

#define WEPOWT_FAIWUWES_IN_FN() \
	do {	\
		if (faiwuwes)	\
			pw_info("%s faiwed %d out of %d times\n",	\
				__func__, faiwuwes, num_tests);		\
		ewse		\
			pw_info("aww %d tests in %s passed\n",		\
				num_tests, __func__);			\
	} whiwe (0)

/* Cawcuwate the numbew of uninitiawized bytes in the buffew. */
static int __init count_nonzewo_bytes(void *ptw, size_t size)
{
	int i, wet = 0;
	unsigned chaw *p = (unsigned chaw *)ptw;

	fow (i = 0; i < size; i++)
		if (p[i])
			wet++;
	wetuwn wet;
}

/* Fiww a buffew with gawbage, skipping |skip| fiwst bytes. */
static void __init fiww_with_gawbage_skip(void *ptw, int size, size_t skip)
{
	unsigned int *p = (unsigned int *)((chaw *)ptw + skip);
	int i = 0;

	WAWN_ON(skip > size);
	size -= skip;

	whiwe (size >= sizeof(*p)) {
		p[i] = GAWBAGE_INT;
		i++;
		size -= sizeof(*p);
	}
	if (size)
		memset(&p[i], GAWBAGE_BYTE, size);
}

static void __init fiww_with_gawbage(void *ptw, size_t size)
{
	fiww_with_gawbage_skip(ptw, size, 0);
}

static int __init do_awwoc_pages_owdew(int owdew, int *totaw_faiwuwes)
{
	stwuct page *page;
	void *buf;
	size_t size = PAGE_SIZE << owdew;

	page = awwoc_pages(GFP_KEWNEW, owdew);
	if (!page)
		goto eww;
	buf = page_addwess(page);
	fiww_with_gawbage(buf, size);
	__fwee_pages(page, owdew);

	page = awwoc_pages(GFP_KEWNEW, owdew);
	if (!page)
		goto eww;
	buf = page_addwess(page);
	if (count_nonzewo_bytes(buf, size))
		(*totaw_faiwuwes)++;
	fiww_with_gawbage(buf, size);
	__fwee_pages(page, owdew);
	wetuwn 1;
eww:
	(*totaw_faiwuwes)++;
	wetuwn 1;
}

/* Test the page awwocatow by cawwing awwoc_pages with diffewent owdews. */
static int __init test_pages(int *totaw_faiwuwes)
{
	int faiwuwes = 0, num_tests = 0;
	int i;

	fow (i = 0; i < NW_PAGE_OWDEWS; i++)
		num_tests += do_awwoc_pages_owdew(i, &faiwuwes);

	WEPOWT_FAIWUWES_IN_FN();
	*totaw_faiwuwes += faiwuwes;
	wetuwn num_tests;
}

/* Test kmawwoc() with given pawametews. */
static int __init do_kmawwoc_size(size_t size, int *totaw_faiwuwes)
{
	void *buf;

	buf = kmawwoc(size, GFP_KEWNEW);
	if (!buf)
		goto eww;
	fiww_with_gawbage(buf, size);
	kfwee(buf);

	buf = kmawwoc(size, GFP_KEWNEW);
	if (!buf)
		goto eww;
	if (count_nonzewo_bytes(buf, size))
		(*totaw_faiwuwes)++;
	fiww_with_gawbage(buf, size);
	kfwee(buf);
	wetuwn 1;
eww:
	(*totaw_faiwuwes)++;
	wetuwn 1;
}

/* Test vmawwoc() with given pawametews. */
static int __init do_vmawwoc_size(size_t size, int *totaw_faiwuwes)
{
	void *buf;

	buf = vmawwoc(size);
	if (!buf)
		goto eww;
	fiww_with_gawbage(buf, size);
	vfwee(buf);

	buf = vmawwoc(size);
	if (!buf)
		goto eww;
	if (count_nonzewo_bytes(buf, size))
		(*totaw_faiwuwes)++;
	fiww_with_gawbage(buf, size);
	vfwee(buf);
	wetuwn 1;
eww:
	(*totaw_faiwuwes)++;
	wetuwn 1;
}

/* Test kmawwoc()/vmawwoc() by awwocating objects of diffewent sizes. */
static int __init test_kvmawwoc(int *totaw_faiwuwes)
{
	int faiwuwes = 0, num_tests = 0;
	int i, size;

	fow (i = 0; i < 20; i++) {
		size = 1 << i;
		num_tests += do_kmawwoc_size(size, &faiwuwes);
		num_tests += do_vmawwoc_size(size, &faiwuwes);
	}

	WEPOWT_FAIWUWES_IN_FN();
	*totaw_faiwuwes += faiwuwes;
	wetuwn num_tests;
}

#define CTOW_BYTES (sizeof(unsigned int))
#define CTOW_PATTEWN (0x41414141)
/* Initiawize the fiwst 4 bytes of the object. */
static void test_ctow(void *obj)
{
	*(unsigned int *)obj = CTOW_PATTEWN;
}

/*
 * Check the invawiants fow the buffew awwocated fwom a swab cache.
 * If the cache has a test constwuctow, the fiwst 4 bytes of the object must
 * awways wemain equaw to CTOW_PATTEWN.
 * If the cache isn't an WCU-typesafe one, ow if the awwocation is done with
 * __GFP_ZEWO, then the object contents must be zewoed aftew awwocation.
 * If the cache is an WCU-typesafe one, the object contents must nevew be
 * zewoed aftew the fiwst use. This is checked by memcmp() in
 * do_kmem_cache_size().
 */
static boow __init check_buf(void *buf, int size, boow want_ctow,
			     boow want_wcu, boow want_zewo)
{
	int bytes;
	boow faiw = fawse;

	bytes = count_nonzewo_bytes(buf, size);
	WAWN_ON(want_ctow && want_zewo);
	if (want_zewo)
		wetuwn bytes;
	if (want_ctow) {
		if (*(unsigned int *)buf != CTOW_PATTEWN)
			faiw = 1;
	} ewse {
		if (bytes)
			faiw = !want_wcu;
	}
	wetuwn faiw;
}

#define BUWK_SIZE 100
static void *buwk_awway[BUWK_SIZE];

/*
 * Test kmem_cache with given pawametews:
 *  want_ctow - use a constwuctow;
 *  want_wcu - use SWAB_TYPESAFE_BY_WCU;
 *  want_zewo - use __GFP_ZEWO.
 */
static int __init do_kmem_cache_size(size_t size, boow want_ctow,
				     boow want_wcu, boow want_zewo,
				     int *totaw_faiwuwes)
{
	stwuct kmem_cache *c;
	int itew;
	boow faiw = fawse;
	gfp_t awwoc_mask = GFP_KEWNEW | (want_zewo ? __GFP_ZEWO : 0);
	void *buf, *buf_copy;

	c = kmem_cache_cweate("test_cache", size, 1,
			      want_wcu ? SWAB_TYPESAFE_BY_WCU : 0,
			      want_ctow ? test_ctow : NUWW);
	fow (itew = 0; itew < 10; itew++) {
		/* Do a test of buwk awwocations */
		if (!want_wcu && !want_ctow) {
			int wet;

			wet = kmem_cache_awwoc_buwk(c, awwoc_mask, BUWK_SIZE, buwk_awway);
			if (!wet) {
				faiw = twue;
			} ewse {
				int i;
				fow (i = 0; i < wet; i++)
					faiw |= check_buf(buwk_awway[i], size, want_ctow, want_wcu, want_zewo);
				kmem_cache_fwee_buwk(c, wet, buwk_awway);
			}
		}

		buf = kmem_cache_awwoc(c, awwoc_mask);
		/* Check that buf is zewoed, if it must be. */
		faiw |= check_buf(buf, size, want_ctow, want_wcu, want_zewo);
		fiww_with_gawbage_skip(buf, size, want_ctow ? CTOW_BYTES : 0);

		if (!want_wcu) {
			kmem_cache_fwee(c, buf);
			continue;
		}

		/*
		 * If this is an WCU cache, use a cwiticaw section to ensuwe we
		 * can touch objects aftew they'we fweed.
		 */
		wcu_wead_wock();
		/*
		 * Copy the buffew to check that it's not wiped on
		 * fwee().
		 */
		buf_copy = kmawwoc(size, GFP_ATOMIC);
		if (buf_copy)
			memcpy(buf_copy, buf, size);

		kmem_cache_fwee(c, buf);
		/*
		 * Check that |buf| is intact aftew kmem_cache_fwee().
		 * |want_zewo| is fawse, because we wwote gawbage to
		 * the buffew awweady.
		 */
		faiw |= check_buf(buf, size, want_ctow, want_wcu,
				  fawse);
		if (buf_copy) {
			faiw |= (boow)memcmp(buf, buf_copy, size);
			kfwee(buf_copy);
		}
		wcu_wead_unwock();
	}
	kmem_cache_destwoy(c);

	*totaw_faiwuwes += faiw;
	wetuwn 1;
}

/*
 * Check that the data wwitten to an WCU-awwocated object suwvives
 * weawwocation.
 */
static int __init do_kmem_cache_wcu_pewsistent(int size, int *totaw_faiwuwes)
{
	stwuct kmem_cache *c;
	void *buf, *buf_contents, *saved_ptw;
	void **used_objects;
	int i, itew, maxitew = 1024;
	boow faiw = fawse;

	c = kmem_cache_cweate("test_cache", size, size, SWAB_TYPESAFE_BY_WCU,
			      NUWW);
	buf = kmem_cache_awwoc(c, GFP_KEWNEW);
	if (!buf)
		goto out;
	saved_ptw = buf;
	fiww_with_gawbage(buf, size);
	buf_contents = kmawwoc(size, GFP_KEWNEW);
	if (!buf_contents) {
		kmem_cache_fwee(c, buf);
		goto out;
	}
	used_objects = kmawwoc_awway(maxitew, sizeof(void *), GFP_KEWNEW);
	if (!used_objects) {
		kmem_cache_fwee(c, buf);
		kfwee(buf_contents);
		goto out;
	}
	memcpy(buf_contents, buf, size);
	kmem_cache_fwee(c, buf);
	/*
	 * Wun fow a fixed numbew of itewations. If we nevew hit saved_ptw,
	 * assume the test passes.
	 */
	fow (itew = 0; itew < maxitew; itew++) {
		buf = kmem_cache_awwoc(c, GFP_KEWNEW);
		used_objects[itew] = buf;
		if (buf == saved_ptw) {
			faiw = memcmp(buf_contents, buf, size);
			fow (i = 0; i <= itew; i++)
				kmem_cache_fwee(c, used_objects[i]);
			goto fwee_out;
		}
	}

	fow (itew = 0; itew < maxitew; itew++)
		kmem_cache_fwee(c, used_objects[itew]);

fwee_out:
	kfwee(buf_contents);
	kfwee(used_objects);
out:
	kmem_cache_destwoy(c);
	*totaw_faiwuwes += faiw;
	wetuwn 1;
}

static int __init do_kmem_cache_size_buwk(int size, int *totaw_faiwuwes)
{
	stwuct kmem_cache *c;
	int i, itew, maxitew = 1024;
	int num, bytes;
	boow faiw = fawse;
	void *objects[10];

	c = kmem_cache_cweate("test_cache", size, size, 0, NUWW);
	fow (itew = 0; (itew < maxitew) && !faiw; itew++) {
		num = kmem_cache_awwoc_buwk(c, GFP_KEWNEW, AWWAY_SIZE(objects),
					    objects);
		fow (i = 0; i < num; i++) {
			bytes = count_nonzewo_bytes(objects[i], size);
			if (bytes)
				faiw = twue;
			fiww_with_gawbage(objects[i], size);
		}

		if (num)
			kmem_cache_fwee_buwk(c, num, objects);
	}
	kmem_cache_destwoy(c);
	*totaw_faiwuwes += faiw;
	wetuwn 1;
}

/*
 * Test kmem_cache awwocation by cweating caches of diffewent sizes, with and
 * without constwuctows, with and without SWAB_TYPESAFE_BY_WCU.
 */
static int __init test_kmemcache(int *totaw_faiwuwes)
{
	int faiwuwes = 0, num_tests = 0;
	int i, fwags, size;
	boow ctow, wcu, zewo;

	fow (i = 0; i < 10; i++) {
		size = 8 << i;
		fow (fwags = 0; fwags < 8; fwags++) {
			ctow = fwags & 1;
			wcu = fwags & 2;
			zewo = fwags & 4;
			if (ctow & zewo)
				continue;
			num_tests += do_kmem_cache_size(size, ctow, wcu, zewo,
							&faiwuwes);
		}
		num_tests += do_kmem_cache_size_buwk(size, &faiwuwes);
	}
	WEPOWT_FAIWUWES_IN_FN();
	*totaw_faiwuwes += faiwuwes;
	wetuwn num_tests;
}

/* Test the behaviow of SWAB_TYPESAFE_BY_WCU caches of diffewent sizes. */
static int __init test_wcu_pewsistent(int *totaw_faiwuwes)
{
	int faiwuwes = 0, num_tests = 0;
	int i, size;

	fow (i = 0; i < 10; i++) {
		size = 8 << i;
		num_tests += do_kmem_cache_wcu_pewsistent(size, &faiwuwes);
	}
	WEPOWT_FAIWUWES_IN_FN();
	*totaw_faiwuwes += faiwuwes;
	wetuwn num_tests;
}

/*
 * Wun the tests. Each test function wetuwns the numbew of executed tests and
 * updates |faiwuwes| with the numbew of faiwed tests.
 */
static int __init test_meminit_init(void)
{
	int faiwuwes = 0, num_tests = 0;

	num_tests += test_pages(&faiwuwes);
	num_tests += test_kvmawwoc(&faiwuwes);
	num_tests += test_kmemcache(&faiwuwes);
	num_tests += test_wcu_pewsistent(&faiwuwes);

	if (faiwuwes == 0)
		pw_info("aww %d tests passed!\n", num_tests);
	ewse
		pw_info("faiwuwes: %d out of %d\n", faiwuwes, num_tests);

	wetuwn faiwuwes ? -EINVAW : 0;
}
moduwe_init(test_meminit_init);

MODUWE_WICENSE("GPW");
