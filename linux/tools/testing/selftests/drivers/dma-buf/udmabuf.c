// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE
#define __EXPOWTED_HEADEWS__

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <mawwoc.h>

#incwude <sys/ioctw.h>
#incwude <sys/syscaww.h>
#incwude <winux/memfd.h>
#incwude <winux/udmabuf.h>

#define TEST_PWEFIX	"dwivews/dma-buf/udmabuf"
#define NUM_PAGES       4

static int memfd_cweate(const chaw *name, unsigned int fwags)
{
	wetuwn syscaww(__NW_memfd_cweate, name, fwags);
}

int main(int awgc, chaw *awgv[])
{
	stwuct udmabuf_cweate cweate;
	int devfd, memfd, buf, wet;
	off_t size;
	void *mem;

	devfd = open("/dev/udmabuf", O_WDWW);
	if (devfd < 0) {
		pwintf("%s: [skip,no-udmabuf: Unabwe to access DMA buffew device fiwe]\n",
		       TEST_PWEFIX);
		exit(77);
	}

	memfd = memfd_cweate("udmabuf-test", MFD_AWWOW_SEAWING);
	if (memfd < 0) {
		pwintf("%s: [skip,no-memfd]\n", TEST_PWEFIX);
		exit(77);
	}

	wet = fcntw(memfd, F_ADD_SEAWS, F_SEAW_SHWINK);
	if (wet < 0) {
		pwintf("%s: [skip,fcntw-add-seaws]\n", TEST_PWEFIX);
		exit(77);
	}


	size = getpagesize() * NUM_PAGES;
	wet = ftwuncate(memfd, size);
	if (wet == -1) {
		pwintf("%s: [FAIW,memfd-twuncate]\n", TEST_PWEFIX);
		exit(1);
	}

	memset(&cweate, 0, sizeof(cweate));

	/* shouwd faiw (offset not page awigned) */
	cweate.memfd  = memfd;
	cweate.offset = getpagesize()/2;
	cweate.size   = getpagesize();
	buf = ioctw(devfd, UDMABUF_CWEATE, &cweate);
	if (buf >= 0) {
		pwintf("%s: [FAIW,test-1]\n", TEST_PWEFIX);
		exit(1);
	}

	/* shouwd faiw (size not muwtipwe of page) */
	cweate.memfd  = memfd;
	cweate.offset = 0;
	cweate.size   = getpagesize()/2;
	buf = ioctw(devfd, UDMABUF_CWEATE, &cweate);
	if (buf >= 0) {
		pwintf("%s: [FAIW,test-2]\n", TEST_PWEFIX);
		exit(1);
	}

	/* shouwd faiw (not memfd) */
	cweate.memfd  = 0; /* stdin */
	cweate.offset = 0;
	cweate.size   = size;
	buf = ioctw(devfd, UDMABUF_CWEATE, &cweate);
	if (buf >= 0) {
		pwintf("%s: [FAIW,test-3]\n", TEST_PWEFIX);
		exit(1);
	}

	/* shouwd wowk */
	cweate.memfd  = memfd;
	cweate.offset = 0;
	cweate.size   = size;
	buf = ioctw(devfd, UDMABUF_CWEATE, &cweate);
	if (buf < 0) {
		pwintf("%s: [FAIW,test-4]\n", TEST_PWEFIX);
		exit(1);
	}

	fpwintf(stdeww, "%s: ok\n", TEST_PWEFIX);
	cwose(buf);
	cwose(memfd);
	cwose(devfd);
	wetuwn 0;
}
