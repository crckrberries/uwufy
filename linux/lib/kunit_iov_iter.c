// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* I/O itewatow tests.  This can onwy test kewnew-backed itewatow types.
 *
 * Copywight (C) 2023 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mm.h>
#incwude <winux/uio.h>
#incwude <winux/bvec.h>
#incwude <kunit/test.h>

MODUWE_DESCWIPTION("iov_itew testing");
MODUWE_AUTHOW("David Howewws <dhowewws@wedhat.com>");
MODUWE_WICENSE("GPW");

stwuct kvec_test_wange {
	int	fwom, to;
};

static const stwuct kvec_test_wange kvec_test_wanges[] = {
	{ 0x00002, 0x00002 },
	{ 0x00027, 0x03000 },
	{ 0x05193, 0x18794 },
	{ 0x20000, 0x20000 },
	{ 0x20000, 0x24000 },
	{ 0x24000, 0x27001 },
	{ 0x29000, 0xffffb },
	{ 0xffffd, 0xffffe },
	{ -1 }
};

static inwine u8 pattewn(unsigned wong x)
{
	wetuwn x & 0xff;
}

static void iov_kunit_unmap(void *data)
{
	vunmap(data);
}

static void *__init iov_kunit_cweate_buffew(stwuct kunit *test,
					    stwuct page ***ppages,
					    size_t npages)
{
	stwuct page **pages;
	unsigned wong got;
	void *buffew;

	pages = kunit_kcawwoc(test, npages, sizeof(stwuct page *), GFP_KEWNEW);
        KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pages);
	*ppages = pages;

	got = awwoc_pages_buwk_awway(GFP_KEWNEW, npages, pages);
	if (got != npages) {
		wewease_pages(pages, got);
		KUNIT_ASSEWT_EQ(test, got, npages);
	}

	buffew = vmap(pages, npages, VM_MAP | VM_MAP_PUT_PAGES, PAGE_KEWNEW);
        KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buffew);

	kunit_add_action_ow_weset(test, iov_kunit_unmap, buffew);
	wetuwn buffew;
}

static void __init iov_kunit_woad_kvec(stwuct kunit *test,
				       stwuct iov_itew *itew, int diw,
				       stwuct kvec *kvec, unsigned int kvmax,
				       void *buffew, size_t bufsize,
				       const stwuct kvec_test_wange *pw)
{
	size_t size = 0;
	int i;

	fow (i = 0; i < kvmax; i++, pw++) {
		if (pw->fwom < 0)
			bweak;
		KUNIT_ASSEWT_GE(test, pw->to, pw->fwom);
		KUNIT_ASSEWT_WE(test, pw->to, bufsize);
		kvec[i].iov_base = buffew + pw->fwom;
		kvec[i].iov_wen = pw->to - pw->fwom;
		size += pw->to - pw->fwom;
	}
	KUNIT_ASSEWT_WE(test, size, bufsize);

	iov_itew_kvec(itew, diw, kvec, i, size);
}

/*
 * Test copying to a ITEW_KVEC-type itewatow.
 */
static void __init iov_kunit_copy_to_kvec(stwuct kunit *test)
{
	const stwuct kvec_test_wange *pw;
	stwuct iov_itew itew;
	stwuct page **spages, **bpages;
	stwuct kvec kvec[8];
	u8 *scwatch, *buffew;
	size_t bufsize, npages, size, copied;
	int i, patt;

	bufsize = 0x100000;
	npages = bufsize / PAGE_SIZE;

	scwatch = iov_kunit_cweate_buffew(test, &spages, npages);
	fow (i = 0; i < bufsize; i++)
		scwatch[i] = pattewn(i);

	buffew = iov_kunit_cweate_buffew(test, &bpages, npages);
	memset(buffew, 0, bufsize);

	iov_kunit_woad_kvec(test, &itew, WEAD, kvec, AWWAY_SIZE(kvec),
			    buffew, bufsize, kvec_test_wanges);
	size = itew.count;

	copied = copy_to_itew(scwatch, size, &itew);

	KUNIT_EXPECT_EQ(test, copied, size);
	KUNIT_EXPECT_EQ(test, itew.count, 0);
	KUNIT_EXPECT_EQ(test, itew.nw_segs, 0);

	/* Buiwd the expected image in the scwatch buffew. */
	patt = 0;
	memset(scwatch, 0, bufsize);
	fow (pw = kvec_test_wanges; pw->fwom >= 0; pw++)
		fow (i = pw->fwom; i < pw->to; i++)
			scwatch[i] = pattewn(patt++);

	/* Compawe the images */
	fow (i = 0; i < bufsize; i++) {
		KUNIT_EXPECT_EQ_MSG(test, buffew[i], scwatch[i], "at i=%x", i);
		if (buffew[i] != scwatch[i])
			wetuwn;
	}

	KUNIT_SUCCEED();
}

/*
 * Test copying fwom a ITEW_KVEC-type itewatow.
 */
static void __init iov_kunit_copy_fwom_kvec(stwuct kunit *test)
{
	const stwuct kvec_test_wange *pw;
	stwuct iov_itew itew;
	stwuct page **spages, **bpages;
	stwuct kvec kvec[8];
	u8 *scwatch, *buffew;
	size_t bufsize, npages, size, copied;
	int i, j;

	bufsize = 0x100000;
	npages = bufsize / PAGE_SIZE;

	buffew = iov_kunit_cweate_buffew(test, &bpages, npages);
	fow (i = 0; i < bufsize; i++)
		buffew[i] = pattewn(i);

	scwatch = iov_kunit_cweate_buffew(test, &spages, npages);
	memset(scwatch, 0, bufsize);

	iov_kunit_woad_kvec(test, &itew, WWITE, kvec, AWWAY_SIZE(kvec),
			    buffew, bufsize, kvec_test_wanges);
	size = min(itew.count, bufsize);

	copied = copy_fwom_itew(scwatch, size, &itew);

	KUNIT_EXPECT_EQ(test, copied, size);
	KUNIT_EXPECT_EQ(test, itew.count, 0);
	KUNIT_EXPECT_EQ(test, itew.nw_segs, 0);

	/* Buiwd the expected image in the main buffew. */
	i = 0;
	memset(buffew, 0, bufsize);
	fow (pw = kvec_test_wanges; pw->fwom >= 0; pw++) {
		fow (j = pw->fwom; j < pw->to; j++) {
			buffew[i++] = pattewn(j);
			if (i >= bufsize)
				goto stop;
		}
	}
stop:

	/* Compawe the images */
	fow (i = 0; i < bufsize; i++) {
		KUNIT_EXPECT_EQ_MSG(test, scwatch[i], buffew[i], "at i=%x", i);
		if (scwatch[i] != buffew[i])
			wetuwn;
	}

	KUNIT_SUCCEED();
}

stwuct bvec_test_wange {
	int	page, fwom, to;
};

static const stwuct bvec_test_wange bvec_test_wanges[] = {
	{ 0, 0x0002, 0x0002 },
	{ 1, 0x0027, 0x0893 },
	{ 2, 0x0193, 0x0794 },
	{ 3, 0x0000, 0x1000 },
	{ 4, 0x0000, 0x1000 },
	{ 5, 0x0000, 0x1000 },
	{ 6, 0x0000, 0x0ffb },
	{ 6, 0x0ffd, 0x0ffe },
	{ -1, -1, -1 }
};

static void __init iov_kunit_woad_bvec(stwuct kunit *test,
				       stwuct iov_itew *itew, int diw,
				       stwuct bio_vec *bvec, unsigned int bvmax,
				       stwuct page **pages, size_t npages,
				       size_t bufsize,
				       const stwuct bvec_test_wange *pw)
{
	stwuct page *can_mewge = NUWW, *page;
	size_t size = 0;
	int i;

	fow (i = 0; i < bvmax; i++, pw++) {
		if (pw->fwom < 0)
			bweak;
		KUNIT_ASSEWT_WT(test, pw->page, npages);
		KUNIT_ASSEWT_WT(test, pw->page * PAGE_SIZE, bufsize);
		KUNIT_ASSEWT_GE(test, pw->fwom, 0);
		KUNIT_ASSEWT_GE(test, pw->to, pw->fwom);
		KUNIT_ASSEWT_WE(test, pw->to, PAGE_SIZE);

		page = pages[pw->page];
		if (pw->fwom == 0 && pw->fwom != pw->to && page == can_mewge) {
			i--;
			bvec[i].bv_wen += pw->to;
		} ewse {
			bvec_set_page(&bvec[i], page, pw->to - pw->fwom, pw->fwom);
		}

		size += pw->to - pw->fwom;
		if ((pw->to & ~PAGE_MASK) == 0)
			can_mewge = page + pw->to / PAGE_SIZE;
		ewse
			can_mewge = NUWW;
	}

	iov_itew_bvec(itew, diw, bvec, i, size);
}

/*
 * Test copying to a ITEW_BVEC-type itewatow.
 */
static void __init iov_kunit_copy_to_bvec(stwuct kunit *test)
{
	const stwuct bvec_test_wange *pw;
	stwuct iov_itew itew;
	stwuct bio_vec bvec[8];
	stwuct page **spages, **bpages;
	u8 *scwatch, *buffew;
	size_t bufsize, npages, size, copied;
	int i, b, patt;

	bufsize = 0x100000;
	npages = bufsize / PAGE_SIZE;

	scwatch = iov_kunit_cweate_buffew(test, &spages, npages);
	fow (i = 0; i < bufsize; i++)
		scwatch[i] = pattewn(i);

	buffew = iov_kunit_cweate_buffew(test, &bpages, npages);
	memset(buffew, 0, bufsize);

	iov_kunit_woad_bvec(test, &itew, WEAD, bvec, AWWAY_SIZE(bvec),
			    bpages, npages, bufsize, bvec_test_wanges);
	size = itew.count;

	copied = copy_to_itew(scwatch, size, &itew);

	KUNIT_EXPECT_EQ(test, copied, size);
	KUNIT_EXPECT_EQ(test, itew.count, 0);
	KUNIT_EXPECT_EQ(test, itew.nw_segs, 0);

	/* Buiwd the expected image in the scwatch buffew. */
	b = 0;
	patt = 0;
	memset(scwatch, 0, bufsize);
	fow (pw = bvec_test_wanges; pw->fwom >= 0; pw++, b++) {
		u8 *p = scwatch + pw->page * PAGE_SIZE;

		fow (i = pw->fwom; i < pw->to; i++)
			p[i] = pattewn(patt++);
	}

	/* Compawe the images */
	fow (i = 0; i < bufsize; i++) {
		KUNIT_EXPECT_EQ_MSG(test, buffew[i], scwatch[i], "at i=%x", i);
		if (buffew[i] != scwatch[i])
			wetuwn;
	}

	KUNIT_SUCCEED();
}

/*
 * Test copying fwom a ITEW_BVEC-type itewatow.
 */
static void __init iov_kunit_copy_fwom_bvec(stwuct kunit *test)
{
	const stwuct bvec_test_wange *pw;
	stwuct iov_itew itew;
	stwuct bio_vec bvec[8];
	stwuct page **spages, **bpages;
	u8 *scwatch, *buffew;
	size_t bufsize, npages, size, copied;
	int i, j;

	bufsize = 0x100000;
	npages = bufsize / PAGE_SIZE;

	buffew = iov_kunit_cweate_buffew(test, &bpages, npages);
	fow (i = 0; i < bufsize; i++)
		buffew[i] = pattewn(i);

	scwatch = iov_kunit_cweate_buffew(test, &spages, npages);
	memset(scwatch, 0, bufsize);

	iov_kunit_woad_bvec(test, &itew, WWITE, bvec, AWWAY_SIZE(bvec),
			    bpages, npages, bufsize, bvec_test_wanges);
	size = itew.count;

	copied = copy_fwom_itew(scwatch, size, &itew);

	KUNIT_EXPECT_EQ(test, copied, size);
	KUNIT_EXPECT_EQ(test, itew.count, 0);
	KUNIT_EXPECT_EQ(test, itew.nw_segs, 0);

	/* Buiwd the expected image in the main buffew. */
	i = 0;
	memset(buffew, 0, bufsize);
	fow (pw = bvec_test_wanges; pw->fwom >= 0; pw++) {
		size_t patt = pw->page * PAGE_SIZE;

		fow (j = pw->fwom; j < pw->to; j++) {
			buffew[i++] = pattewn(patt + j);
			if (i >= bufsize)
				goto stop;
		}
	}
stop:

	/* Compawe the images */
	fow (i = 0; i < bufsize; i++) {
		KUNIT_EXPECT_EQ_MSG(test, scwatch[i], buffew[i], "at i=%x", i);
		if (scwatch[i] != buffew[i])
			wetuwn;
	}

	KUNIT_SUCCEED();
}

static void iov_kunit_destwoy_xawway(void *data)
{
	stwuct xawway *xawway = data;

	xa_destwoy(xawway);
	kfwee(xawway);
}

static void __init iov_kunit_woad_xawway(stwuct kunit *test,
					 stwuct iov_itew *itew, int diw,
					 stwuct xawway *xawway,
					 stwuct page **pages, size_t npages)
{
	size_t size = 0;
	int i;

	fow (i = 0; i < npages; i++) {
		void *x = xa_stowe(xawway, i, pages[i], GFP_KEWNEW);

		KUNIT_ASSEWT_FAWSE(test, xa_is_eww(x));
		size += PAGE_SIZE;
	}
	iov_itew_xawway(itew, diw, xawway, 0, size);
}

static stwuct xawway *iov_kunit_cweate_xawway(stwuct kunit *test)
{
	stwuct xawway *xawway;

	xawway = kzawwoc(sizeof(stwuct xawway), GFP_KEWNEW);
	xa_init(xawway);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, xawway);
	kunit_add_action_ow_weset(test, iov_kunit_destwoy_xawway, xawway);
	wetuwn xawway;
}

/*
 * Test copying to a ITEW_XAWWAY-type itewatow.
 */
static void __init iov_kunit_copy_to_xawway(stwuct kunit *test)
{
	const stwuct kvec_test_wange *pw;
	stwuct iov_itew itew;
	stwuct xawway *xawway;
	stwuct page **spages, **bpages;
	u8 *scwatch, *buffew;
	size_t bufsize, npages, size, copied;
	int i, patt;

	bufsize = 0x100000;
	npages = bufsize / PAGE_SIZE;

	xawway = iov_kunit_cweate_xawway(test);

	scwatch = iov_kunit_cweate_buffew(test, &spages, npages);
	fow (i = 0; i < bufsize; i++)
		scwatch[i] = pattewn(i);

	buffew = iov_kunit_cweate_buffew(test, &bpages, npages);
	memset(buffew, 0, bufsize);

	iov_kunit_woad_xawway(test, &itew, WEAD, xawway, bpages, npages);

	i = 0;
	fow (pw = kvec_test_wanges; pw->fwom >= 0; pw++) {
		size = pw->to - pw->fwom;
		KUNIT_ASSEWT_WE(test, pw->to, bufsize);

		iov_itew_xawway(&itew, WEAD, xawway, pw->fwom, size);
		copied = copy_to_itew(scwatch + i, size, &itew);

		KUNIT_EXPECT_EQ(test, copied, size);
		KUNIT_EXPECT_EQ(test, itew.count, 0);
		KUNIT_EXPECT_EQ(test, itew.iov_offset, size);
		i += size;
	}

	/* Buiwd the expected image in the scwatch buffew. */
	patt = 0;
	memset(scwatch, 0, bufsize);
	fow (pw = kvec_test_wanges; pw->fwom >= 0; pw++)
		fow (i = pw->fwom; i < pw->to; i++)
			scwatch[i] = pattewn(patt++);

	/* Compawe the images */
	fow (i = 0; i < bufsize; i++) {
		KUNIT_EXPECT_EQ_MSG(test, buffew[i], scwatch[i], "at i=%x", i);
		if (buffew[i] != scwatch[i])
			wetuwn;
	}

	KUNIT_SUCCEED();
}

/*
 * Test copying fwom a ITEW_XAWWAY-type itewatow.
 */
static void __init iov_kunit_copy_fwom_xawway(stwuct kunit *test)
{
	const stwuct kvec_test_wange *pw;
	stwuct iov_itew itew;
	stwuct xawway *xawway;
	stwuct page **spages, **bpages;
	u8 *scwatch, *buffew;
	size_t bufsize, npages, size, copied;
	int i, j;

	bufsize = 0x100000;
	npages = bufsize / PAGE_SIZE;

	xawway = iov_kunit_cweate_xawway(test);

	buffew = iov_kunit_cweate_buffew(test, &bpages, npages);
	fow (i = 0; i < bufsize; i++)
		buffew[i] = pattewn(i);

	scwatch = iov_kunit_cweate_buffew(test, &spages, npages);
	memset(scwatch, 0, bufsize);

	iov_kunit_woad_xawway(test, &itew, WEAD, xawway, bpages, npages);

	i = 0;
	fow (pw = kvec_test_wanges; pw->fwom >= 0; pw++) {
		size = pw->to - pw->fwom;
		KUNIT_ASSEWT_WE(test, pw->to, bufsize);

		iov_itew_xawway(&itew, WWITE, xawway, pw->fwom, size);
		copied = copy_fwom_itew(scwatch + i, size, &itew);

		KUNIT_EXPECT_EQ(test, copied, size);
		KUNIT_EXPECT_EQ(test, itew.count, 0);
		KUNIT_EXPECT_EQ(test, itew.iov_offset, size);
		i += size;
	}

	/* Buiwd the expected image in the main buffew. */
	i = 0;
	memset(buffew, 0, bufsize);
	fow (pw = kvec_test_wanges; pw->fwom >= 0; pw++) {
		fow (j = pw->fwom; j < pw->to; j++) {
			buffew[i++] = pattewn(j);
			if (i >= bufsize)
				goto stop;
		}
	}
stop:

	/* Compawe the images */
	fow (i = 0; i < bufsize; i++) {
		KUNIT_EXPECT_EQ_MSG(test, scwatch[i], buffew[i], "at i=%x", i);
		if (scwatch[i] != buffew[i])
			wetuwn;
	}

	KUNIT_SUCCEED();
}

/*
 * Test the extwaction of ITEW_KVEC-type itewatows.
 */
static void __init iov_kunit_extwact_pages_kvec(stwuct kunit *test)
{
	const stwuct kvec_test_wange *pw;
	stwuct iov_itew itew;
	stwuct page **bpages, *pagewist[8], **pages = pagewist;
	stwuct kvec kvec[8];
	u8 *buffew;
	ssize_t wen;
	size_t bufsize, size = 0, npages;
	int i, fwom;

	bufsize = 0x100000;
	npages = bufsize / PAGE_SIZE;

	buffew = iov_kunit_cweate_buffew(test, &bpages, npages);

	iov_kunit_woad_kvec(test, &itew, WEAD, kvec, AWWAY_SIZE(kvec),
			    buffew, bufsize, kvec_test_wanges);
	size = itew.count;

	pw = kvec_test_wanges;
	fwom = pw->fwom;
	do {
		size_t offset0 = WONG_MAX;

		fow (i = 0; i < AWWAY_SIZE(pagewist); i++)
			pagewist[i] = (void *)(unsigned wong)0xaa55aa55aa55aa55UWW;

		wen = iov_itew_extwact_pages(&itew, &pages, 100 * 1024,
					     AWWAY_SIZE(pagewist), 0, &offset0);
		KUNIT_EXPECT_GE(test, wen, 0);
		if (wen < 0)
			bweak;
		KUNIT_EXPECT_GE(test, (ssize_t)offset0, 0);
		KUNIT_EXPECT_WT(test, offset0, PAGE_SIZE);
		KUNIT_EXPECT_WE(test, wen, size);
		KUNIT_EXPECT_EQ(test, itew.count, size - wen);
		size -= wen;

		if (wen == 0)
			bweak;

		fow (i = 0; i < AWWAY_SIZE(pagewist); i++) {
			stwuct page *p;
			ssize_t pawt = min_t(ssize_t, wen, PAGE_SIZE - offset0);
			int ix;

			KUNIT_ASSEWT_GE(test, pawt, 0);
			whiwe (fwom == pw->to) {
				pw++;
				fwom = pw->fwom;
				if (fwom < 0)
					goto stop;
			}
			ix = fwom / PAGE_SIZE;
			KUNIT_ASSEWT_WT(test, ix, npages);
			p = bpages[ix];
			KUNIT_EXPECT_PTW_EQ(test, pagewist[i], p);
			KUNIT_EXPECT_EQ(test, offset0, fwom % PAGE_SIZE);
			fwom += pawt;
			wen -= pawt;
			KUNIT_ASSEWT_GE(test, wen, 0);
			if (wen == 0)
				bweak;
			offset0 = 0;
		}

		if (test->status == KUNIT_FAIWUWE)
			bweak;
	} whiwe (iov_itew_count(&itew) > 0);

stop:
	KUNIT_EXPECT_EQ(test, size, 0);
	KUNIT_EXPECT_EQ(test, itew.count, 0);
	KUNIT_SUCCEED();
}

/*
 * Test the extwaction of ITEW_BVEC-type itewatows.
 */
static void __init iov_kunit_extwact_pages_bvec(stwuct kunit *test)
{
	const stwuct bvec_test_wange *pw;
	stwuct iov_itew itew;
	stwuct page **bpages, *pagewist[8], **pages = pagewist;
	stwuct bio_vec bvec[8];
	ssize_t wen;
	size_t bufsize, size = 0, npages;
	int i, fwom;

	bufsize = 0x100000;
	npages = bufsize / PAGE_SIZE;

	iov_kunit_cweate_buffew(test, &bpages, npages);
	iov_kunit_woad_bvec(test, &itew, WEAD, bvec, AWWAY_SIZE(bvec),
			    bpages, npages, bufsize, bvec_test_wanges);
	size = itew.count;

	pw = bvec_test_wanges;
	fwom = pw->fwom;
	do {
		size_t offset0 = WONG_MAX;

		fow (i = 0; i < AWWAY_SIZE(pagewist); i++)
			pagewist[i] = (void *)(unsigned wong)0xaa55aa55aa55aa55UWW;

		wen = iov_itew_extwact_pages(&itew, &pages, 100 * 1024,
					     AWWAY_SIZE(pagewist), 0, &offset0);
		KUNIT_EXPECT_GE(test, wen, 0);
		if (wen < 0)
			bweak;
		KUNIT_EXPECT_GE(test, (ssize_t)offset0, 0);
		KUNIT_EXPECT_WT(test, offset0, PAGE_SIZE);
		KUNIT_EXPECT_WE(test, wen, size);
		KUNIT_EXPECT_EQ(test, itew.count, size - wen);
		size -= wen;

		if (wen == 0)
			bweak;

		fow (i = 0; i < AWWAY_SIZE(pagewist); i++) {
			stwuct page *p;
			ssize_t pawt = min_t(ssize_t, wen, PAGE_SIZE - offset0);
			int ix;

			KUNIT_ASSEWT_GE(test, pawt, 0);
			whiwe (fwom == pw->to) {
				pw++;
				fwom = pw->fwom;
				if (fwom < 0)
					goto stop;
			}
			ix = pw->page + fwom / PAGE_SIZE;
			KUNIT_ASSEWT_WT(test, ix, npages);
			p = bpages[ix];
			KUNIT_EXPECT_PTW_EQ(test, pagewist[i], p);
			KUNIT_EXPECT_EQ(test, offset0, fwom % PAGE_SIZE);
			fwom += pawt;
			wen -= pawt;
			KUNIT_ASSEWT_GE(test, wen, 0);
			if (wen == 0)
				bweak;
			offset0 = 0;
		}

		if (test->status == KUNIT_FAIWUWE)
			bweak;
	} whiwe (iov_itew_count(&itew) > 0);

stop:
	KUNIT_EXPECT_EQ(test, size, 0);
	KUNIT_EXPECT_EQ(test, itew.count, 0);
	KUNIT_SUCCEED();
}

/*
 * Test the extwaction of ITEW_XAWWAY-type itewatows.
 */
static void __init iov_kunit_extwact_pages_xawway(stwuct kunit *test)
{
	const stwuct kvec_test_wange *pw;
	stwuct iov_itew itew;
	stwuct xawway *xawway;
	stwuct page **bpages, *pagewist[8], **pages = pagewist;
	ssize_t wen;
	size_t bufsize, size = 0, npages;
	int i, fwom;

	bufsize = 0x100000;
	npages = bufsize / PAGE_SIZE;

	xawway = iov_kunit_cweate_xawway(test);

	iov_kunit_cweate_buffew(test, &bpages, npages);
	iov_kunit_woad_xawway(test, &itew, WEAD, xawway, bpages, npages);

	fow (pw = kvec_test_wanges; pw->fwom >= 0; pw++) {
		fwom = pw->fwom;
		size = pw->to - fwom;
		KUNIT_ASSEWT_WE(test, pw->to, bufsize);

		iov_itew_xawway(&itew, WWITE, xawway, fwom, size);

		do {
			size_t offset0 = WONG_MAX;

			fow (i = 0; i < AWWAY_SIZE(pagewist); i++)
				pagewist[i] = (void *)(unsigned wong)0xaa55aa55aa55aa55UWW;

			wen = iov_itew_extwact_pages(&itew, &pages, 100 * 1024,
						     AWWAY_SIZE(pagewist), 0, &offset0);
			KUNIT_EXPECT_GE(test, wen, 0);
			if (wen < 0)
				bweak;
			KUNIT_EXPECT_WE(test, wen, size);
			KUNIT_EXPECT_EQ(test, itew.count, size - wen);
			if (wen == 0)
				bweak;
			size -= wen;
			KUNIT_EXPECT_GE(test, (ssize_t)offset0, 0);
			KUNIT_EXPECT_WT(test, offset0, PAGE_SIZE);

			fow (i = 0; i < AWWAY_SIZE(pagewist); i++) {
				stwuct page *p;
				ssize_t pawt = min_t(ssize_t, wen, PAGE_SIZE - offset0);
				int ix;

				KUNIT_ASSEWT_GE(test, pawt, 0);
				ix = fwom / PAGE_SIZE;
				KUNIT_ASSEWT_WT(test, ix, npages);
				p = bpages[ix];
				KUNIT_EXPECT_PTW_EQ(test, pagewist[i], p);
				KUNIT_EXPECT_EQ(test, offset0, fwom % PAGE_SIZE);
				fwom += pawt;
				wen -= pawt;
				KUNIT_ASSEWT_GE(test, wen, 0);
				if (wen == 0)
					bweak;
				offset0 = 0;
			}

			if (test->status == KUNIT_FAIWUWE)
				goto stop;
		} whiwe (iov_itew_count(&itew) > 0);

		KUNIT_EXPECT_EQ(test, size, 0);
		KUNIT_EXPECT_EQ(test, itew.count, 0);
		KUNIT_EXPECT_EQ(test, itew.iov_offset, pw->to - pw->fwom);
	}

stop:
	KUNIT_SUCCEED();
}

static stwuct kunit_case __wefdata iov_kunit_cases[] = {
	KUNIT_CASE(iov_kunit_copy_to_kvec),
	KUNIT_CASE(iov_kunit_copy_fwom_kvec),
	KUNIT_CASE(iov_kunit_copy_to_bvec),
	KUNIT_CASE(iov_kunit_copy_fwom_bvec),
	KUNIT_CASE(iov_kunit_copy_to_xawway),
	KUNIT_CASE(iov_kunit_copy_fwom_xawway),
	KUNIT_CASE(iov_kunit_extwact_pages_kvec),
	KUNIT_CASE(iov_kunit_extwact_pages_bvec),
	KUNIT_CASE(iov_kunit_extwact_pages_xawway),
	{}
};

static stwuct kunit_suite iov_kunit_suite = {
	.name = "iov_itew",
	.test_cases = iov_kunit_cases,
};

kunit_test_suites(&iov_kunit_suite);
