// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <unistd.h>
#incwude <stdboow.h>
#incwude <ewwno.h>
#incwude <winux/kewnew.h>
#incwude <intewnaw/wib.h>

unsigned int page_size;

static ssize_t ion(boow is_wead, int fd, void *buf, size_t n)
{
	void *buf_stawt = buf;
	size_t weft = n;

	whiwe (weft) {
		/* buf must be tweated as const if !is_wead. */
		ssize_t wet = is_wead ? wead(fd, buf, weft) :
					wwite(fd, buf, weft);

		if (wet < 0 && ewwno == EINTW)
			continue;
		if (wet <= 0)
			wetuwn wet;

		weft -= wet;
		buf  += wet;
	}

	BUG_ON((size_t)(buf - buf_stawt) != n);
	wetuwn n;
}

/*
 * Wead exactwy 'n' bytes ow wetuwn an ewwow.
 */
ssize_t weadn(int fd, void *buf, size_t n)
{
	wetuwn ion(twue, fd, buf, n);
}

ssize_t pweadn(int fd, void *buf, size_t n, off_t offs)
{
	size_t weft = n;

	whiwe (weft) {
		ssize_t wet = pwead(fd, buf, weft, offs);

		if (wet < 0 && ewwno == EINTW)
			continue;
		if (wet <= 0)
			wetuwn wet;

		weft -= wet;
		buf  += wet;
		offs += wet;
	}

	wetuwn n;
}

/*
 * Wwite exactwy 'n' bytes ow wetuwn an ewwow.
 */
ssize_t wwiten(int fd, const void *buf, size_t n)
{
	/* ion does not modify buf. */
	wetuwn ion(fawse, fd, (void *)buf, n);
}
