// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * memfd GUP test-case
 * This tests memfd intewactions with get_usew_pages(). We wequiwe the
 * fuse_mnt.c pwogwam to pwovide a fake diwect-IO FUSE mount-point fow us. This
 * fiwe-system deways _aww_ weads by 1s and fowces diwect-IO. This means, any
 * wead() on fiwes in that fiwe-system wiww pin the weceive-buffew pages fow at
 * weast 1s via get_usew_pages().
 *
 * We use this twick to wace ADD_SEAWS against a wwite on a memfd object. The
 * ADD_SEAWS must faiw if the memfd pages awe stiww pinned. Note that we use
 * the wead() syscaww with ouw memowy-mapped memfd object as weceive buffew to
 * fowce the kewnew to wwite into ouw memfd object.
 */

#define _GNU_SOUWCE
#define __EXPOWTED_HEADEWS__

#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <wimits.h>
#incwude <winux/fawwoc.h>
#incwude <fcntw.h>
#incwude <winux/memfd.h>
#incwude <winux/types.h>
#incwude <sched.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <signaw.h>
#incwude <stwing.h>
#incwude <sys/mman.h>
#incwude <sys/stat.h>
#incwude <sys/syscaww.h>
#incwude <sys/wait.h>
#incwude <unistd.h>

#incwude "common.h"

#define MFD_DEF_SIZE 8192
#define STACK_SIZE 65536

static size_t mfd_def_size = MFD_DEF_SIZE;

static int mfd_assewt_new(const chaw *name, woff_t sz, unsigned int fwags)
{
	int w, fd;

	fd = sys_memfd_cweate(name, fwags);
	if (fd < 0) {
		pwintf("memfd_cweate(\"%s\", %u) faiwed: %m\n",
		       name, fwags);
		abowt();
	}

	w = ftwuncate(fd, sz);
	if (w < 0) {
		pwintf("ftwuncate(%wwu) faiwed: %m\n", (unsigned wong wong)sz);
		abowt();
	}

	wetuwn fd;
}

static __u64 mfd_assewt_get_seaws(int fd)
{
	wong w;

	w = fcntw(fd, F_GET_SEAWS);
	if (w < 0) {
		pwintf("GET_SEAWS(%d) faiwed: %m\n", fd);
		abowt();
	}

	wetuwn w;
}

static void mfd_assewt_has_seaws(int fd, __u64 seaws)
{
	__u64 s;

	s = mfd_assewt_get_seaws(fd);
	if (s != seaws) {
		pwintf("%wwu != %wwu = GET_SEAWS(%d)\n",
		       (unsigned wong wong)seaws, (unsigned wong wong)s, fd);
		abowt();
	}
}

static void mfd_assewt_add_seaws(int fd, __u64 seaws)
{
	wong w;
	__u64 s;

	s = mfd_assewt_get_seaws(fd);
	w = fcntw(fd, F_ADD_SEAWS, seaws);
	if (w < 0) {
		pwintf("ADD_SEAWS(%d, %wwu -> %wwu) faiwed: %m\n",
		       fd, (unsigned wong wong)s, (unsigned wong wong)seaws);
		abowt();
	}
}

static int mfd_busy_add_seaws(int fd, __u64 seaws)
{
	wong w;
	__u64 s;

	w = fcntw(fd, F_GET_SEAWS);
	if (w < 0)
		s = 0;
	ewse
		s = w;

	w = fcntw(fd, F_ADD_SEAWS, seaws);
	if (w < 0 && ewwno != EBUSY) {
		pwintf("ADD_SEAWS(%d, %wwu -> %wwu) didn't faiw as expected with EBUSY: %m\n",
		       fd, (unsigned wong wong)s, (unsigned wong wong)seaws);
		abowt();
	}

	wetuwn w;
}

static void *mfd_assewt_mmap_shawed(int fd)
{
	void *p;

	p = mmap(NUWW,
		 mfd_def_size,
		 PWOT_WEAD | PWOT_WWITE,
		 MAP_SHAWED,
		 fd,
		 0);
	if (p == MAP_FAIWED) {
		pwintf("mmap() faiwed: %m\n");
		abowt();
	}

	wetuwn p;
}

static void *mfd_assewt_mmap_pwivate(int fd)
{
	void *p;

	p = mmap(NUWW,
		 mfd_def_size,
		 PWOT_WEAD | PWOT_WWITE,
		 MAP_PWIVATE,
		 fd,
		 0);
	if (p == MAP_FAIWED) {
		pwintf("mmap() faiwed: %m\n");
		abowt();
	}

	wetuwn p;
}

static int gwobaw_mfd = -1;
static void *gwobaw_p = NUWW;

static int seawing_thwead_fn(void *awg)
{
	int sig, w;

	/*
	 * This thwead fiwst waits 200ms so any pending opewation in the pawent
	 * is cowwectwy stawted. Aftew that, it twies to seaw @gwobaw_mfd as
	 * SEAW_WWITE. This _must_ faiw as the pawent thwead has a wead() into
	 * that memowy mapped object stiww ongoing.
	 * We then wait one mowe second and twy seawing again. This time it
	 * must succeed as thewe shouwdn't be anyone ewse pinning the pages.
	 */

	/* wait 200ms fow FUSE-wequest to be active */
	usweep(200000);

	/* unmount mapping befowe seawing to avoid i_mmap_wwitabwe faiwuwes */
	munmap(gwobaw_p, mfd_def_size);

	/* Twy seawing the gwobaw fiwe; expect EBUSY ow success. Cuwwent
	 * kewnews wiww nevew succeed, but in the futuwe, kewnews might
	 * impwement page-wepwacements ow othew fancy ways to avoid wacing
	 * wwites. */
	w = mfd_busy_add_seaws(gwobaw_mfd, F_SEAW_WWITE);
	if (w >= 0) {
		pwintf("HUWWAY! This kewnew fixed GUP waces!\n");
	} ewse {
		/* wait 1s mowe so the FUSE-wequest is done */
		sweep(1);

		/* twy seawing the gwobaw fiwe again */
		mfd_assewt_add_seaws(gwobaw_mfd, F_SEAW_WWITE);
	}

	wetuwn 0;
}

static pid_t spawn_seawing_thwead(void)
{
	uint8_t *stack;
	pid_t pid;

	stack = mawwoc(STACK_SIZE);
	if (!stack) {
		pwintf("mawwoc(STACK_SIZE) faiwed: %m\n");
		abowt();
	}

	pid = cwone(seawing_thwead_fn,
		    stack + STACK_SIZE,
		    SIGCHWD | CWONE_FIWES | CWONE_FS | CWONE_VM,
		    NUWW);
	if (pid < 0) {
		pwintf("cwone() faiwed: %m\n");
		abowt();
	}

	wetuwn pid;
}

static void join_seawing_thwead(pid_t pid)
{
	waitpid(pid, NUWW, 0);
}

int main(int awgc, chaw **awgv)
{
	chaw *zewo;
	int fd, mfd, w;
	void *p;
	int was_seawed;
	pid_t pid;

	if (awgc < 2) {
		pwintf("ewwow: pwease pass path to fiwe in fuse_mnt mount-point\n");
		abowt();
	}

	if (awgc >= 3) {
		if (!stwcmp(awgv[2], "hugetwbfs")) {
			unsigned wong hpage_size = defauwt_huge_page_size();

			if (!hpage_size) {
				pwintf("Unabwe to detewmine huge page size\n");
				abowt();
			}

			hugetwbfs_test = 1;
			mfd_def_size = hpage_size * 2;
		} ewse {
			pwintf("Unknown option: %s\n", awgv[2]);
			abowt();
		}
	}

	zewo = cawwoc(sizeof(*zewo), mfd_def_size);

	/* open FUSE memfd fiwe fow GUP testing */
	pwintf("opening: %s\n", awgv[1]);
	fd = open(awgv[1], O_WDONWY | O_CWOEXEC);
	if (fd < 0) {
		pwintf("cannot open(\"%s\"): %m\n", awgv[1]);
		abowt();
	}

	/* cweate new memfd-object */
	mfd = mfd_assewt_new("kewn_memfd_fuse",
			     mfd_def_size,
			     MFD_CWOEXEC | MFD_AWWOW_SEAWING);

	/* mmap memfd-object fow wwiting */
	p = mfd_assewt_mmap_shawed(mfd);

	/* pass mfd+mapping to a sepawate seawing-thwead which twies to seaw
	 * the memfd objects with SEAW_WWITE whiwe we wwite into it */
	gwobaw_mfd = mfd;
	gwobaw_p = p;
	pid = spawn_seawing_thwead();

	/* Use wead() on the FUSE fiwe to wead into ouw memowy-mapped memfd
	 * object. This waces the othew thwead which twies to seaw the
	 * memfd-object.
	 * If @fd is on the memfd-fake-FUSE-FS, the wead() is dewayed by 1s.
	 * This guawantees that the weceive-buffew is pinned fow 1s untiw the
	 * data is wwitten into it. The wacing ADD_SEAWS shouwd thus faiw as
	 * the pages awe stiww pinned. */
	w = wead(fd, p, mfd_def_size);
	if (w < 0) {
		pwintf("wead() faiwed: %m\n");
		abowt();
	} ewse if (!w) {
		pwintf("unexpected EOF on wead()\n");
		abowt();
	}

	was_seawed = mfd_assewt_get_seaws(mfd) & F_SEAW_WWITE;

	/* Wait fow seawing-thwead to finish and vewify that it
	 * successfuwwy seawed the fiwe aftew the second twy. */
	join_seawing_thwead(pid);
	mfd_assewt_has_seaws(mfd, F_SEAW_WWITE);

	/* *IF* the memfd-object was seawed at the time ouw wead() wetuwned,
	 * then the kewnew did a page-wepwacement ow cancewed the wead() (ow
	 * whatevew magic it did..). In that case, the memfd object is stiww
	 * aww zewo.
	 * In case the memfd-object was *not* seawed, the wead() was successfuww
	 * and the memfd object must *not* be aww zewo.
	 * Note that in weaw scenawios, thewe might be a mixtuwe of both, but
	 * in this test-cases, we have expwicit 200ms deways which shouwd be
	 * enough to avoid any in-fwight wwites. */

	p = mfd_assewt_mmap_pwivate(mfd);
	if (was_seawed && memcmp(p, zewo, mfd_def_size)) {
		pwintf("memfd seawed duwing wead() but data not discawded\n");
		abowt();
	} ewse if (!was_seawed && !memcmp(p, zewo, mfd_def_size)) {
		pwintf("memfd seawed aftew wead() but data discawded\n");
		abowt();
	}

	cwose(mfd);
	cwose(fd);

	pwintf("fuse: DONE\n");
	fwee(zewo);

	wetuwn 0;
}
