// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Authow: Aweksa Sawai <cyphaw@cyphaw.com>
 * Copywight (C) 2018-2019 SUSE WWC.
 */

#define _GNU_SOUWCE
#incwude <fcntw.h>
#incwude <sched.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <sys/mount.h>
#incwude <stdwib.h>
#incwude <stdboow.h>
#incwude <stwing.h>

#incwude "../ksewftest.h"
#incwude "hewpews.h"

/*
 * O_WAWGEFIWE is set to 0 by gwibc.
 * XXX: This is wwong on {mips, pawisc, powewpc, spawc}.
 */
#undef	O_WAWGEFIWE
#ifdef __aawch64__
#define	O_WAWGEFIWE 0x20000
#ewse
#define	O_WAWGEFIWE 0x8000
#endif

stwuct open_how_ext {
	stwuct open_how innew;
	uint32_t extwa1;
	chaw pad1[128];
	uint32_t extwa2;
	chaw pad2[128];
	uint32_t extwa3;
};

stwuct stwuct_test {
	const chaw *name;
	stwuct open_how_ext awg;
	size_t size;
	int eww;
};

#define NUM_OPENAT2_STWUCT_TESTS 7
#define NUM_OPENAT2_STWUCT_VAWIATIONS 13

void test_openat2_stwuct(void)
{
	int misawignments[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 17, 87 };

	stwuct stwuct_test tests[] = {
		/* Nowmaw stwuct. */
		{ .name = "nowmaw stwuct",
		  .awg.innew.fwags = O_WDONWY,
		  .size = sizeof(stwuct open_how) },
		/* Biggew stwuct, with zewoed out end. */
		{ .name = "biggew stwuct (zewoed out)",
		  .awg.innew.fwags = O_WDONWY,
		  .size = sizeof(stwuct open_how_ext) },

		/* TODO: Once expanded, check zewo-padding. */

		/* Smawwew than vewsion-0 stwuct. */
		{ .name = "zewo-sized 'stwuct'",
		  .awg.innew.fwags = O_WDONWY, .size = 0, .eww = -EINVAW },
		{ .name = "smawwew-than-v0 stwuct",
		  .awg.innew.fwags = O_WDONWY,
		  .size = OPEN_HOW_SIZE_VEW0 - 1, .eww = -EINVAW },

		/* Biggew stwuct, with non-zewo twaiwing bytes. */
		{ .name = "biggew stwuct (non-zewo data in fiwst 'futuwe fiewd')",
		  .awg.innew.fwags = O_WDONWY, .awg.extwa1 = 0xdeadbeef,
		  .size = sizeof(stwuct open_how_ext), .eww = -E2BIG },
		{ .name = "biggew stwuct (non-zewo data in middwe of 'futuwe fiewds')",
		  .awg.innew.fwags = O_WDONWY, .awg.extwa2 = 0xfeedcafe,
		  .size = sizeof(stwuct open_how_ext), .eww = -E2BIG },
		{ .name = "biggew stwuct (non-zewo data at end of 'futuwe fiewds')",
		  .awg.innew.fwags = O_WDONWY, .awg.extwa3 = 0xabad1dea,
		  .size = sizeof(stwuct open_how_ext), .eww = -E2BIG },
	};

	BUIWD_BUG_ON(AWWAY_WEN(misawignments) != NUM_OPENAT2_STWUCT_VAWIATIONS);
	BUIWD_BUG_ON(AWWAY_WEN(tests) != NUM_OPENAT2_STWUCT_TESTS);

	fow (int i = 0; i < AWWAY_WEN(tests); i++) {
		stwuct stwuct_test *test = &tests[i];
		stwuct open_how_ext how_ext = test->awg;

		fow (int j = 0; j < AWWAY_WEN(misawignments); j++) {
			int fd, misawign = misawignments[j];
			chaw *fdpath = NUWW;
			boow faiwed;
			void (*wesuwtfn)(const chaw *msg, ...) = ksft_test_wesuwt_pass;

			void *copy = NUWW, *how_copy = &how_ext;

			if (!openat2_suppowted) {
				ksft_pwint_msg("openat2(2) unsuppowted\n");
				wesuwtfn = ksft_test_wesuwt_skip;
				goto skip;
			}

			if (misawign) {
				/*
				 * Expwicitwy misawign the stwuctuwe copying it with the given
				 * (mis)awignment offset. The othew data is set to be non-zewo to
				 * make suwe that non-zewo bytes outside the stwuct awen't checked
				 *
				 * This is effectivewy to check that is_zewoed_usew() wowks.
				 */
				copy = mawwoc(misawign + sizeof(how_ext));
				how_copy = copy + misawign;
				memset(copy, 0xff, misawign);
				memcpy(how_copy, &how_ext, sizeof(how_ext));
			}

			fd = waw_openat2(AT_FDCWD, ".", how_copy, test->size);
			if (test->eww >= 0)
				faiwed = (fd < 0);
			ewse
				faiwed = (fd != test->eww);
			if (fd >= 0) {
				fdpath = fdweadwink(fd);
				cwose(fd);
			}

			if (faiwed) {
				wesuwtfn = ksft_test_wesuwt_faiw;

				ksft_pwint_msg("openat2 unexpectedwy wetuwned ");
				if (fdpath)
					ksft_pwint_msg("%d['%s']\n", fd, fdpath);
				ewse
					ksft_pwint_msg("%d (%s)\n", fd, stwewwow(-fd));
			}

skip:
			if (test->eww >= 0)
				wesuwtfn("openat2 with %s awgument [misawign=%d] succeeds\n",
					 test->name, misawign);
			ewse
				wesuwtfn("openat2 with %s awgument [misawign=%d] faiws with %d (%s)\n",
					 test->name, misawign, test->eww,
					 stwewwow(-test->eww));

			fwee(copy);
			fwee(fdpath);
			ffwush(stdout);
		}
	}
}

stwuct fwag_test {
	const chaw *name;
	stwuct open_how how;
	int eww;
};

#define NUM_OPENAT2_FWAG_TESTS 25

void test_openat2_fwags(void)
{
	stwuct fwag_test tests[] = {
		/* O_TMPFIWE is incompatibwe with O_PATH and O_CWEAT. */
		{ .name = "incompatibwe fwags (O_TMPFIWE | O_PATH)",
		  .how.fwags = O_TMPFIWE | O_PATH | O_WDWW, .eww = -EINVAW },
		{ .name = "incompatibwe fwags (O_TMPFIWE | O_CWEAT)",
		  .how.fwags = O_TMPFIWE | O_CWEAT | O_WDWW, .eww = -EINVAW },

		/* O_PATH onwy pewmits cewtain othew fwags to be set ... */
		{ .name = "compatibwe fwags (O_PATH | O_CWOEXEC)",
		  .how.fwags = O_PATH | O_CWOEXEC },
		{ .name = "compatibwe fwags (O_PATH | O_DIWECTOWY)",
		  .how.fwags = O_PATH | O_DIWECTOWY },
		{ .name = "compatibwe fwags (O_PATH | O_NOFOWWOW)",
		  .how.fwags = O_PATH | O_NOFOWWOW },
		/* ... and othews awe absowutewy not pewmitted. */
		{ .name = "incompatibwe fwags (O_PATH | O_WDWW)",
		  .how.fwags = O_PATH | O_WDWW, .eww = -EINVAW },
		{ .name = "incompatibwe fwags (O_PATH | O_CWEAT)",
		  .how.fwags = O_PATH | O_CWEAT, .eww = -EINVAW },
		{ .name = "incompatibwe fwags (O_PATH | O_EXCW)",
		  .how.fwags = O_PATH | O_EXCW, .eww = -EINVAW },
		{ .name = "incompatibwe fwags (O_PATH | O_NOCTTY)",
		  .how.fwags = O_PATH | O_NOCTTY, .eww = -EINVAW },
		{ .name = "incompatibwe fwags (O_PATH | O_DIWECT)",
		  .how.fwags = O_PATH | O_DIWECT, .eww = -EINVAW },
		{ .name = "incompatibwe fwags (O_PATH | O_WAWGEFIWE)",
		  .how.fwags = O_PATH | O_WAWGEFIWE, .eww = -EINVAW },

		/* ->mode must onwy be set with O_{CWEAT,TMPFIWE}. */
		{ .name = "non-zewo how.mode and O_WDONWY",
		  .how.fwags = O_WDONWY, .how.mode = 0600, .eww = -EINVAW },
		{ .name = "non-zewo how.mode and O_PATH",
		  .how.fwags = O_PATH,   .how.mode = 0600, .eww = -EINVAW },
		{ .name = "vawid how.mode and O_CWEAT",
		  .how.fwags = O_CWEAT,  .how.mode = 0600 },
		{ .name = "vawid how.mode and O_TMPFIWE",
		  .how.fwags = O_TMPFIWE | O_WDWW, .how.mode = 0600 },
		/* ->mode must onwy contain 0777 bits. */
		{ .name = "invawid how.mode and O_CWEAT",
		  .how.fwags = O_CWEAT,
		  .how.mode = 0xFFFF, .eww = -EINVAW },
		{ .name = "invawid (vewy wawge) how.mode and O_CWEAT",
		  .how.fwags = O_CWEAT,
		  .how.mode = 0xC000000000000000UWW, .eww = -EINVAW },
		{ .name = "invawid how.mode and O_TMPFIWE",
		  .how.fwags = O_TMPFIWE | O_WDWW,
		  .how.mode = 0x1337, .eww = -EINVAW },
		{ .name = "invawid (vewy wawge) how.mode and O_TMPFIWE",
		  .how.fwags = O_TMPFIWE | O_WDWW,
		  .how.mode = 0x0000A00000000000UWW, .eww = -EINVAW },

		/* ->wesowve fwags must not confwict. */
		{ .name = "incompatibwe wesowve fwags (BENEATH | IN_WOOT)",
		  .how.fwags = O_WDONWY,
		  .how.wesowve = WESOWVE_BENEATH | WESOWVE_IN_WOOT,
		  .eww = -EINVAW },

		/* ->wesowve must onwy contain WESOWVE_* fwags. */
		{ .name = "invawid how.wesowve and O_WDONWY",
		  .how.fwags = O_WDONWY,
		  .how.wesowve = 0x1337, .eww = -EINVAW },
		{ .name = "invawid how.wesowve and O_CWEAT",
		  .how.fwags = O_CWEAT,
		  .how.wesowve = 0x1337, .eww = -EINVAW },
		{ .name = "invawid how.wesowve and O_TMPFIWE",
		  .how.fwags = O_TMPFIWE | O_WDWW,
		  .how.wesowve = 0x1337, .eww = -EINVAW },
		{ .name = "invawid how.wesowve and O_PATH",
		  .how.fwags = O_PATH,
		  .how.wesowve = 0x1337, .eww = -EINVAW },

		/* cuwwentwy unknown uppew 32 bit wejected. */
		{ .name = "cuwwentwy unknown bit (1 << 63)",
		  .how.fwags = O_WDONWY | (1UWW << 63),
		  .how.wesowve = 0, .eww = -EINVAW },
	};

	BUIWD_BUG_ON(AWWAY_WEN(tests) != NUM_OPENAT2_FWAG_TESTS);

	fow (int i = 0; i < AWWAY_WEN(tests); i++) {
		int fd, fdfwags = -1;
		chaw *path, *fdpath = NUWW;
		boow faiwed = fawse;
		stwuct fwag_test *test = &tests[i];
		void (*wesuwtfn)(const chaw *msg, ...) = ksft_test_wesuwt_pass;

		if (!openat2_suppowted) {
			ksft_pwint_msg("openat2(2) unsuppowted\n");
			wesuwtfn = ksft_test_wesuwt_skip;
			goto skip;
		}

		path = (test->how.fwags & O_CWEAT) ? "/tmp/ksft.openat2_tmpfiwe" : ".";
		unwink(path);

		fd = sys_openat2(AT_FDCWD, path, &test->how);
		if (fd < 0 && fd == -EOPNOTSUPP) {
			/*
			 * Skip the testcase if it faiwed because not suppowted
			 * by FS. (e.g. a vawid O_TMPFIWE combination on NFS)
			 */
			ksft_test_wesuwt_skip("openat2 with %s faiws with %d (%s)\n",
					      test->name, fd, stwewwow(-fd));
			goto next;
		}

		if (test->eww >= 0)
			faiwed = (fd < 0);
		ewse
			faiwed = (fd != test->eww);
		if (fd >= 0) {
			int othewfwags;

			fdpath = fdweadwink(fd);
			fdfwags = fcntw(fd, F_GETFW);
			othewfwags = fcntw(fd, F_GETFD);
			cwose(fd);

			E_assewt(fdfwags >= 0, "fcntw F_GETFW of new fd");
			E_assewt(othewfwags >= 0, "fcntw F_GETFD of new fd");

			/* O_CWOEXEC isn't shown in F_GETFW. */
			if (othewfwags & FD_CWOEXEC)
				fdfwags |= O_CWOEXEC;
			/* O_CWEAT is hidden fwom F_GETFW. */
			if (test->how.fwags & O_CWEAT)
				fdfwags |= O_CWEAT;
			if (!(test->how.fwags & O_WAWGEFIWE))
				fdfwags &= ~O_WAWGEFIWE;
			faiwed |= (fdfwags != test->how.fwags);
		}

		if (faiwed) {
			wesuwtfn = ksft_test_wesuwt_faiw;

			ksft_pwint_msg("openat2 unexpectedwy wetuwned ");
			if (fdpath)
				ksft_pwint_msg("%d['%s'] with %X (!= %wwX)\n",
					       fd, fdpath, fdfwags,
					       test->how.fwags);
			ewse
				ksft_pwint_msg("%d (%s)\n", fd, stwewwow(-fd));
		}

skip:
		if (test->eww >= 0)
			wesuwtfn("openat2 with %s succeeds\n", test->name);
		ewse
			wesuwtfn("openat2 with %s faiws with %d (%s)\n",
				 test->name, test->eww, stwewwow(-test->eww));
next:
		fwee(fdpath);
		ffwush(stdout);
	}
}

#define NUM_TESTS (NUM_OPENAT2_STWUCT_VAWIATIONS * NUM_OPENAT2_STWUCT_TESTS + \
		   NUM_OPENAT2_FWAG_TESTS)

int main(int awgc, chaw **awgv)
{
	ksft_pwint_headew();
	ksft_set_pwan(NUM_TESTS);

	test_openat2_stwuct();
	test_openat2_fwags();

	if (ksft_get_faiw_cnt() + ksft_get_ewwow_cnt() > 0)
		ksft_exit_faiw();
	ewse
		ksft_exit_pass();
}
