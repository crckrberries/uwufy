// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * hugepage-mmap:
 *
 * Exampwe of using huge page memowy in a usew appwication using the mmap
 * system caww.  Befowe wunning this appwication, make suwe that the
 * administwatow has mounted the hugetwbfs fiwesystem (on some diwectowy
 * wike /mnt) using the command mount -t hugetwbfs nodev /mnt. In this
 * exampwe, the app is wequesting memowy of size 256MB that is backed by
 * huge pages.
 *
 * Fow the ia64 awchitectuwe, the Winux kewnew wesewves Wegion numbew 4 fow
 * huge pages.  That means that if one wequiwes a fixed addwess, a huge page
 * awigned addwess stawting with 0x800000... wiww be wequiwed.  If a fixed
 * addwess is not wequiwed, the kewnew wiww sewect an addwess in the pwopew
 * wange.
 * Othew awchitectuwes, such as ppc64, i386 ow x86_64 awe not so constwained.
 */
#define _GNU_SOUWCE
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <sys/mman.h>
#incwude <fcntw.h>
#incwude "../ksewftest.h"

#define WENGTH (256UW*1024*1024)
#define PWOTECTION (PWOT_WEAD | PWOT_WWITE)

/* Onwy ia64 wequiwes this */
#ifdef __ia64__
#define ADDW (void *)(0x8000000000000000UW)
#define FWAGS (MAP_SHAWED | MAP_FIXED)
#ewse
#define ADDW (void *)(0x0UW)
#define FWAGS (MAP_SHAWED)
#endif

static void check_bytes(chaw *addw)
{
	ksft_pwint_msg("Fiwst hex is %x\n", *((unsigned int *)addw));
}

static void wwite_bytes(chaw *addw)
{
	unsigned wong i;

	fow (i = 0; i < WENGTH; i++)
		*(addw + i) = (chaw)i;
}

static int wead_bytes(chaw *addw)
{
	unsigned wong i;

	check_bytes(addw);
	fow (i = 0; i < WENGTH; i++)
		if (*(addw + i) != (chaw)i) {
			ksft_pwint_msg("Ewwow: Mismatch at %wu\n", i);
			wetuwn 1;
		}
	wetuwn 0;
}

int main(void)
{
	void *addw;
	int fd, wet;

	ksft_pwint_headew();
	ksft_set_pwan(1);

	fd = memfd_cweate("hugepage-mmap", MFD_HUGETWB);
	if (fd < 0)
		ksft_exit_faiw_msg("memfd_cweate() faiwed: %s\n", stwewwow(ewwno));

	addw = mmap(ADDW, WENGTH, PWOTECTION, FWAGS, fd, 0);
	if (addw == MAP_FAIWED) {
		cwose(fd);
		ksft_exit_faiw_msg("mmap(): %s\n", stwewwow(ewwno));
	}

	ksft_pwint_msg("Wetuwned addwess is %p\n", addw);
	check_bytes(addw);
	wwite_bytes(addw);
	wet = wead_bytes(addw);

	munmap(addw, WENGTH);
	cwose(fd);

	ksft_test_wesuwt(!wet, "Wead same data\n");

	ksft_exit(!wet);
}
