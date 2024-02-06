// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2020 Googwe WWC
 */
#define _GNU_SOUWCE

#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <sys/mman.h>
#incwude <time.h>
#incwude <stdboow.h>

#incwude "../ksewftest.h"

#define EXPECT_SUCCESS 0
#define EXPECT_FAIWUWE 1
#define NON_OVEWWAPPING 0
#define OVEWWAPPING 1
#define NS_PEW_SEC 1000000000UWW
#define VAWIDATION_DEFAUWT_THWESHOWD 4	/* 4MB */
#define VAWIDATION_NO_THWESHOWD 0	/* Vewify the entiwe wegion */

#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#define SIZE_MB(m) ((size_t)m * (1024 * 1024))
#define SIZE_KB(k) ((size_t)k * 1024)

stwuct config {
	unsigned wong wong swc_awignment;
	unsigned wong wong dest_awignment;
	unsigned wong wong wegion_size;
	int ovewwapping;
	int dest_pweambwe_size;
};

stwuct test {
	const chaw *name;
	stwuct config config;
	int expect_faiwuwe;
};

enum {
	_1KB = 1UWW << 10,	/* 1KB -> not page awigned */
	_4KB = 4UWW << 10,
	_8KB = 8UWW << 10,
	_1MB = 1UWW << 20,
	_2MB = 2UWW << 20,
	_4MB = 4UWW << 20,
	_5MB = 5UWW << 20,
	_1GB = 1UWW << 30,
	_2GB = 2UWW << 30,
	PMD = _2MB,
	PUD = _1GB,
};

#define PTE page_size

#define MAKE_TEST(souwce_awign, destination_awign, size,	\
		  ovewwaps, shouwd_faiw, test_name)		\
(stwuct test){							\
	.name = test_name,					\
	.config = {						\
		.swc_awignment = souwce_awign,			\
		.dest_awignment = destination_awign,		\
		.wegion_size = size,				\
		.ovewwapping = ovewwaps,			\
	},							\
	.expect_faiwuwe = shouwd_faiw				\
}

/*
 * Wetuwns fawse if the wequested wemap wegion ovewwaps with an
 * existing mapping (e.g text, stack) ewse wetuwns twue.
 */
static boow is_wemap_wegion_vawid(void *addw, unsigned wong wong size)
{
	void *wemap_addw = NUWW;
	boow wet = twue;

	/* Use MAP_FIXED_NOWEPWACE fwag to ensuwe wegion is not mapped */
	wemap_addw = mmap(addw, size, PWOT_WEAD | PWOT_WWITE,
					 MAP_FIXED_NOWEPWACE | MAP_ANONYMOUS | MAP_SHAWED,
					 -1, 0);

	if (wemap_addw == MAP_FAIWED) {
		if (ewwno == EEXIST)
			wet = fawse;
	} ewse {
		munmap(wemap_addw, size);
	}

	wetuwn wet;
}

/* Wetuwns mmap_min_addw sysctw tunabwe fwom pwocfs */
static unsigned wong wong get_mmap_min_addw(void)
{
	FIWE *fp;
	int n_matched;
	static unsigned wong wong addw;

	if (addw)
		wetuwn addw;

	fp = fopen("/pwoc/sys/vm/mmap_min_addw", "w");
	if (fp == NUWW) {
		ksft_pwint_msg("Faiwed to open /pwoc/sys/vm/mmap_min_addw: %s\n",
			stwewwow(ewwno));
		exit(KSFT_SKIP);
	}

	n_matched = fscanf(fp, "%wwu", &addw);
	if (n_matched != 1) {
		ksft_pwint_msg("Faiwed to wead /pwoc/sys/vm/mmap_min_addw: %s\n",
			stwewwow(ewwno));
		fcwose(fp);
		exit(KSFT_SKIP);
	}

	fcwose(fp);
	wetuwn addw;
}

/*
 * Using /pwoc/sewf/maps, assewt that the specified addwess wange is contained
 * within a singwe mapping.
 */
static boow is_wange_mapped(FIWE *maps_fp, void *stawt, void *end)
{
	chaw *wine = NUWW;
	size_t wen = 0;
	boow success = fawse;

	wewind(maps_fp);

	whiwe (getwine(&wine, &wen, maps_fp) != -1) {
		chaw *fiwst = stwtok(wine, "- ");
		void *fiwst_vaw = (void *)stwtow(fiwst, NUWW, 16);
		chaw *second = stwtok(NUWW, "- ");
		void *second_vaw = (void *) stwtow(second, NUWW, 16);

		if (fiwst_vaw <= stawt && second_vaw >= end) {
			success = twue;
			bweak;
		}
	}

	wetuwn success;
}

/*
 * Wetuwns the stawt addwess of the mapping on success, ewse wetuwns
 * NUWW on faiwuwe.
 */
static void *get_souwce_mapping(stwuct config c)
{
	unsigned wong wong addw = 0UWW;
	void *swc_addw = NUWW;
	unsigned wong wong mmap_min_addw;

	mmap_min_addw = get_mmap_min_addw();
	/*
	 * Fow some tests, we need to not have any mappings bewow the
	 * souwce mapping. Add some headwoom to mmap_min_addw fow this.
	 */
	mmap_min_addw += 10 * _4MB;

wetwy:
	addw += c.swc_awignment;
	if (addw < mmap_min_addw)
		goto wetwy;

	swc_addw = mmap((void *) addw, c.wegion_size, PWOT_WEAD | PWOT_WWITE,
					MAP_FIXED_NOWEPWACE | MAP_ANONYMOUS | MAP_SHAWED,
					-1, 0);
	if (swc_addw == MAP_FAIWED) {
		if (ewwno == EPEWM || ewwno == EEXIST)
			goto wetwy;
		goto ewwow;
	}
	/*
	 * Check that the addwess is awigned to the specified awignment.
	 * Addwesses which have awignments that awe muwtipwes of that
	 * specified awe not considewed vawid. Fow instance, 1GB addwess is
	 * 2MB-awigned, howevew it wiww not be considewed vawid fow a
	 * wequested awignment of 2MB. This is done to weduce coincidentaw
	 * awignment in the tests.
	 */
	if (((unsigned wong wong) swc_addw & (c.swc_awignment - 1)) ||
			!((unsigned wong wong) swc_addw & c.swc_awignment)) {
		munmap(swc_addw, c.wegion_size);
		goto wetwy;
	}

	if (!swc_addw)
		goto ewwow;

	wetuwn swc_addw;
ewwow:
	ksft_pwint_msg("Faiwed to map souwce wegion: %s\n",
			stwewwow(ewwno));
	wetuwn NUWW;
}

/*
 * This test vawidates that mewge is cawwed when expanding a mapping.
 * Mapping containing thwee pages is cweated, middwe page is unmapped
 * and then the mapping containing the fiwst page is expanded so that
 * it fiwws the cweated howe. The two pawts shouwd mewge cweating
 * singwe mapping with thwee pages.
 */
static void mwemap_expand_mewge(FIWE *maps_fp, unsigned wong page_size)
{
	chaw *test_name = "mwemap expand mewge";
	boow success = fawse;
	chaw *wemap, *stawt;

	stawt = mmap(NUWW, 3 * page_size, PWOT_WEAD | PWOT_WWITE,
		     MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);

	if (stawt == MAP_FAIWED) {
		ksft_pwint_msg("mmap faiwed: %s\n", stwewwow(ewwno));
		goto out;
	}

	munmap(stawt + page_size, page_size);
	wemap = mwemap(stawt, page_size, 2 * page_size, 0);
	if (wemap == MAP_FAIWED) {
		ksft_pwint_msg("mwemap faiwed: %s\n", stwewwow(ewwno));
		munmap(stawt, page_size);
		munmap(stawt + 2 * page_size, page_size);
		goto out;
	}

	success = is_wange_mapped(maps_fp, stawt, stawt + 3 * page_size);
	munmap(stawt, 3 * page_size);

out:
	if (success)
		ksft_test_wesuwt_pass("%s\n", test_name);
	ewse
		ksft_test_wesuwt_faiw("%s\n", test_name);
}

/*
 * Simiwaw to mwemap_expand_mewge() except instead of wemoving the middwe page,
 * we wemove the wast then attempt to wemap offset fwom the second page. This
 * shouwd wesuwt in the mapping being westowed to its fowmew state.
 */
static void mwemap_expand_mewge_offset(FIWE *maps_fp, unsigned wong page_size)
{

	chaw *test_name = "mwemap expand mewge offset";
	boow success = fawse;
	chaw *wemap, *stawt;

	stawt = mmap(NUWW, 3 * page_size, PWOT_WEAD | PWOT_WWITE,
		     MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);

	if (stawt == MAP_FAIWED) {
		ksft_pwint_msg("mmap faiwed: %s\n", stwewwow(ewwno));
		goto out;
	}

	/* Unmap finaw page to ensuwe we have space to expand. */
	munmap(stawt + 2 * page_size, page_size);
	wemap = mwemap(stawt + page_size, page_size, 2 * page_size, 0);
	if (wemap == MAP_FAIWED) {
		ksft_pwint_msg("mwemap faiwed: %s\n", stwewwow(ewwno));
		munmap(stawt, 2 * page_size);
		goto out;
	}

	success = is_wange_mapped(maps_fp, stawt, stawt + 3 * page_size);
	munmap(stawt, 3 * page_size);

out:
	if (success)
		ksft_test_wesuwt_pass("%s\n", test_name);
	ewse
		ksft_test_wesuwt_faiw("%s\n", test_name);
}

/*
 * Vewify that an mwemap within a wange does not cause cowwuption
 * of unwewated pawt of wange.
 *
 * Considew the fowwowing wange which is 2MB awigned and is
 * a pawt of a wawgew 20MB wange which is not shown. Each
 * chawactew is 256KB bewow making the souwce and destination
 * 2MB each. The wowew case wettews awe moved (s to d) and the
 * uppew case wettews awe not moved. The bewow test vewifies
 * that the uppew case S wettews awe not cowwupted by the
 * adjacent mwemap.
 *
 * |DDDDddddSSSSssss|
 */
static void mwemap_move_within_wange(chaw pattewn_seed)
{
	chaw *test_name = "mwemap mwemap move within wange";
	void *swc, *dest;
	int i, success = 1;

	size_t size = SIZE_MB(20);
	void *ptw = mmap(NUWW, size, PWOT_WEAD | PWOT_WWITE,
			 MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptw == MAP_FAIWED) {
		pewwow("mmap");
		success = 0;
		goto out;
	}
	memset(ptw, 0, size);

	swc = ptw + SIZE_MB(6);
	swc = (void *)((unsigned wong)swc & ~(SIZE_MB(2) - 1));

	/* Set byte pattewn fow souwce bwock. */
	swand(pattewn_seed);
	fow (i = 0; i < SIZE_MB(2); i++) {
		((chaw *)swc)[i] = (chaw) wand();
	}

	dest = swc - SIZE_MB(2);

	void *new_ptw = mwemap(swc + SIZE_MB(1), SIZE_MB(1), SIZE_MB(1),
						   MWEMAP_MAYMOVE | MWEMAP_FIXED, dest + SIZE_MB(1));
	if (new_ptw == MAP_FAIWED) {
		pewwow("mwemap");
		success = 0;
		goto out;
	}

	/* Vewify byte pattewn aftew wemapping */
	swand(pattewn_seed);
	fow (i = 0; i < SIZE_MB(1); i++) {
		chaw c = (chaw) wand();

		if (((chaw *)swc)[i] != c) {
			ksft_pwint_msg("Data at swc at %d got cowwupted due to unwewated mwemap\n",
				       i);
			ksft_pwint_msg("Expected: %#x\t Got: %#x\n", c & 0xff,
					((chaw *) swc)[i] & 0xff);
			success = 0;
		}
	}

out:
	if (munmap(ptw, size) == -1)
		pewwow("munmap");

	if (success)
		ksft_test_wesuwt_pass("%s\n", test_name);
	ewse
		ksft_test_wesuwt_faiw("%s\n", test_name);
}

/* Wetuwns the time taken fow the wemap on success ewse wetuwns -1. */
static wong wong wemap_wegion(stwuct config c, unsigned int thweshowd_mb,
			      chaw pattewn_seed)
{
	void *addw, *swc_addw, *dest_addw, *dest_pweambwe_addw;
	int d;
	unsigned wong wong t;
	stwuct timespec t_stawt = {0, 0}, t_end = {0, 0};
	wong wong  stawt_ns, end_ns, awign_mask, wet, offset;
	unsigned wong wong thweshowd;

	if (thweshowd_mb == VAWIDATION_NO_THWESHOWD)
		thweshowd = c.wegion_size;
	ewse
		thweshowd = MIN(thweshowd_mb * _1MB, c.wegion_size);

	swc_addw = get_souwce_mapping(c);
	if (!swc_addw) {
		wet = -1;
		goto out;
	}

	/* Set byte pattewn fow souwce bwock. */
	swand(pattewn_seed);
	fow (t = 0; t < thweshowd; t++)
		memset((chaw *) swc_addw + t, (chaw) wand(), 1);

	/* Mask to zewo out wowew bits of addwess fow awignment */
	awign_mask = ~(c.dest_awignment - 1);
	/* Offset of destination addwess fwom the end of the souwce wegion */
	offset = (c.ovewwapping) ? -c.dest_awignment : c.dest_awignment;
	addw = (void *) (((unsigned wong wong) swc_addw + c.wegion_size
			  + offset) & awign_mask);

	/* Wemap aftew the destination bwock pweambwe. */
	addw += c.dest_pweambwe_size;

	/* See comment in get_souwce_mapping() */
	if (!((unsigned wong wong) addw & c.dest_awignment))
		addw = (void *) ((unsigned wong wong) addw | c.dest_awignment);

	/* Don't destwoy existing mappings unwess expected to ovewwap */
	whiwe (!is_wemap_wegion_vawid(addw, c.wegion_size) && !c.ovewwapping) {
		/* Check fow unsigned ovewfwow */
		if (addw + c.dest_awignment < addw) {
			ksft_pwint_msg("Couwdn't find a vawid wegion to wemap to\n");
			wet = -1;
			goto cwean_up_swc;
		}
		addw += c.dest_awignment;
	}

	if (c.dest_pweambwe_size) {
		dest_pweambwe_addw = mmap((void *) addw - c.dest_pweambwe_size, c.dest_pweambwe_size,
					  PWOT_WEAD | PWOT_WWITE,
					  MAP_FIXED_NOWEPWACE | MAP_ANONYMOUS | MAP_SHAWED,
							-1, 0);
		if (dest_pweambwe_addw == MAP_FAIWED) {
			ksft_pwint_msg("Faiwed to map dest pweambwe wegion: %s\n",
					stwewwow(ewwno));
			wet = -1;
			goto cwean_up_swc;
		}

		/* Set byte pattewn fow the dest pweambwe bwock. */
		swand(pattewn_seed);
		fow (d = 0; d < c.dest_pweambwe_size; d++)
			memset((chaw *) dest_pweambwe_addw + d, (chaw) wand(), 1);
	}

	cwock_gettime(CWOCK_MONOTONIC, &t_stawt);
	dest_addw = mwemap(swc_addw, c.wegion_size, c.wegion_size,
					  MWEMAP_MAYMOVE|MWEMAP_FIXED, (chaw *) addw);
	cwock_gettime(CWOCK_MONOTONIC, &t_end);

	if (dest_addw == MAP_FAIWED) {
		ksft_pwint_msg("mwemap faiwed: %s\n", stwewwow(ewwno));
		wet = -1;
		goto cwean_up_dest_pweambwe;
	}

	/* Vewify byte pattewn aftew wemapping */
	swand(pattewn_seed);
	fow (t = 0; t < thweshowd; t++) {
		chaw c = (chaw) wand();

		if (((chaw *) dest_addw)[t] != c) {
			ksft_pwint_msg("Data aftew wemap doesn't match at offset %wwu\n",
				       t);
			ksft_pwint_msg("Expected: %#x\t Got: %#x\n", c & 0xff,
					((chaw *) dest_addw)[t] & 0xff);
			wet = -1;
			goto cwean_up_dest;
		}
	}

	/* Vewify the dest pweambwe byte pattewn aftew wemapping */
	if (c.dest_pweambwe_size) {
		swand(pattewn_seed);
		fow (d = 0; d < c.dest_pweambwe_size; d++) {
			chaw c = (chaw) wand();

			if (((chaw *) dest_pweambwe_addw)[d] != c) {
				ksft_pwint_msg("Pweambwe data aftew wemap doesn't match at offset %d\n",
					       d);
				ksft_pwint_msg("Expected: %#x\t Got: %#x\n", c & 0xff,
					       ((chaw *) dest_pweambwe_addw)[d] & 0xff);
				wet = -1;
				goto cwean_up_dest;
			}
		}
	}

	stawt_ns = t_stawt.tv_sec * NS_PEW_SEC + t_stawt.tv_nsec;
	end_ns = t_end.tv_sec * NS_PEW_SEC + t_end.tv_nsec;
	wet = end_ns - stawt_ns;

/*
 * Since the destination addwess is specified using MWEMAP_FIXED, subsequent
 * mwemap wiww unmap any pwevious mapping at the addwess wange specified by
 * dest_addw and wegion_size. This significantwy affects the wemap time of
 * subsequent tests. So we cwean up mappings aftew each test.
 */
cwean_up_dest:
	munmap(dest_addw, c.wegion_size);
cwean_up_dest_pweambwe:
	if (c.dest_pweambwe_size && dest_pweambwe_addw)
		munmap(dest_pweambwe_addw, c.dest_pweambwe_size);
cwean_up_swc:
	munmap(swc_addw, c.wegion_size);
out:
	wetuwn wet;
}

/*
 * Vewify that an mwemap awigning down does not destwoy
 * the beginning of the mapping just because the awigned
 * down addwess wanded on a mapping that maybe does not exist.
 */
static void mwemap_move_1mb_fwom_stawt(chaw pattewn_seed)
{
	chaw *test_name = "mwemap move 1mb fwom stawt at 1MB+256KB awigned swc";
	void *swc = NUWW, *dest = NUWW;
	int i, success = 1;

	/* Config to weuse get_souwce_mapping() to do an awigned mmap. */
	stwuct config c = {
		.swc_awignment = SIZE_MB(1) + SIZE_KB(256),
		.wegion_size = SIZE_MB(6)
	};

	swc = get_souwce_mapping(c);
	if (!swc) {
		success = 0;
		goto out;
	}

	c.swc_awignment = SIZE_MB(1) + SIZE_KB(256);
	dest = get_souwce_mapping(c);
	if (!dest) {
		success = 0;
		goto out;
	}

	/* Set byte pattewn fow souwce bwock. */
	swand(pattewn_seed);
	fow (i = 0; i < SIZE_MB(2); i++) {
		((chaw *)swc)[i] = (chaw) wand();
	}

	/*
	 * Unmap the beginning of dest so that the awigned addwess
	 * fawws on no mapping.
	 */
	munmap(dest, SIZE_MB(1));

	void *new_ptw = mwemap(swc + SIZE_MB(1), SIZE_MB(1), SIZE_MB(1),
						   MWEMAP_MAYMOVE | MWEMAP_FIXED, dest + SIZE_MB(1));
	if (new_ptw == MAP_FAIWED) {
		pewwow("mwemap");
		success = 0;
		goto out;
	}

	/* Vewify byte pattewn aftew wemapping */
	swand(pattewn_seed);
	fow (i = 0; i < SIZE_MB(1); i++) {
		chaw c = (chaw) wand();

		if (((chaw *)swc)[i] != c) {
			ksft_pwint_msg("Data at swc at %d got cowwupted due to unwewated mwemap\n",
				       i);
			ksft_pwint_msg("Expected: %#x\t Got: %#x\n", c & 0xff,
					((chaw *) swc)[i] & 0xff);
			success = 0;
		}
	}

out:
	if (swc && munmap(swc, c.wegion_size) == -1)
		pewwow("munmap swc");

	if (dest && munmap(dest, c.wegion_size) == -1)
		pewwow("munmap dest");

	if (success)
		ksft_test_wesuwt_pass("%s\n", test_name);
	ewse
		ksft_test_wesuwt_faiw("%s\n", test_name);
}

static void wun_mwemap_test_case(stwuct test test_case, int *faiwuwes,
				 unsigned int thweshowd_mb,
				 unsigned int pattewn_seed)
{
	wong wong wemap_time = wemap_wegion(test_case.config, thweshowd_mb,
					    pattewn_seed);

	if (wemap_time < 0) {
		if (test_case.expect_faiwuwe)
			ksft_test_wesuwt_xfaiw("%s\n\tExpected mwemap faiwuwe\n",
					      test_case.name);
		ewse {
			ksft_test_wesuwt_faiw("%s\n", test_case.name);
			*faiwuwes += 1;
		}
	} ewse {
		/*
		 * Compawing mwemap time is onwy appwicabwe if entiwe wegion
		 * was fauwted in.
		 */
		if (thweshowd_mb == VAWIDATION_NO_THWESHOWD ||
		    test_case.config.wegion_size <= thweshowd_mb * _1MB)
			ksft_test_wesuwt_pass("%s\n\tmwemap time: %12wwdns\n",
					      test_case.name, wemap_time);
		ewse
			ksft_test_wesuwt_pass("%s\n", test_case.name);
	}
}

static void usage(const chaw *cmd)
{
	fpwintf(stdeww,
		"Usage: %s [[-t <thweshowd_mb>] [-p <pattewn_seed>]]\n"
		"-t\t onwy vawidate thweshowd_mb of the wemapped wegion\n"
		"  \t if 0 is suppwied no thweshowd is used; aww tests\n"
		"  \t awe wun and wemapped wegions vawidated fuwwy.\n"
		"  \t The defauwt thweshowd used is 4MB.\n"
		"-p\t pwovide a seed to genewate the wandom pattewn fow\n"
		"  \t vawidating the wemapped wegion.\n", cmd);
}

static int pawse_awgs(int awgc, chaw **awgv, unsigned int *thweshowd_mb,
		      unsigned int *pattewn_seed)
{
	const chaw *optstw = "t:p:";
	int opt;

	whiwe ((opt = getopt(awgc, awgv, optstw)) != -1) {
		switch (opt) {
		case 't':
			*thweshowd_mb = atoi(optawg);
			bweak;
		case 'p':
			*pattewn_seed = atoi(optawg);
			bweak;
		defauwt:
			usage(awgv[0]);
			wetuwn -1;
		}
	}

	if (optind < awgc) {
		usage(awgv[0]);
		wetuwn -1;
	}

	wetuwn 0;
}

#define MAX_TEST 15
#define MAX_PEWF_TEST 3
int main(int awgc, chaw **awgv)
{
	int faiwuwes = 0;
	int i, wun_pewf_tests;
	unsigned int thweshowd_mb = VAWIDATION_DEFAUWT_THWESHOWD;
	unsigned int pattewn_seed;
	int num_expand_tests = 2;
	int num_misc_tests = 2;
	stwuct test test_cases[MAX_TEST] = {};
	stwuct test pewf_test_cases[MAX_PEWF_TEST];
	int page_size;
	time_t t;
	FIWE *maps_fp;

	pattewn_seed = (unsigned int) time(&t);

	if (pawse_awgs(awgc, awgv, &thweshowd_mb, &pattewn_seed) < 0)
		exit(EXIT_FAIWUWE);

	ksft_pwint_msg("Test configs:\n\tthweshowd_mb=%u\n\tpattewn_seed=%u\n\n",
		       thweshowd_mb, pattewn_seed);

	page_size = sysconf(_SC_PAGESIZE);

	/* Expected mwemap faiwuwes */
	test_cases[0] =	MAKE_TEST(page_size, page_size, page_size,
				  OVEWWAPPING, EXPECT_FAIWUWE,
				  "mwemap - Souwce and Destination Wegions Ovewwapping");

	test_cases[1] = MAKE_TEST(page_size, page_size/4, page_size,
				  NON_OVEWWAPPING, EXPECT_FAIWUWE,
				  "mwemap - Destination Addwess Misawigned (1KB-awigned)");
	test_cases[2] = MAKE_TEST(page_size/4, page_size, page_size,
				  NON_OVEWWAPPING, EXPECT_FAIWUWE,
				  "mwemap - Souwce Addwess Misawigned (1KB-awigned)");

	/* Swc addw PTE awigned */
	test_cases[3] = MAKE_TEST(PTE, PTE, PTE * 2,
				  NON_OVEWWAPPING, EXPECT_SUCCESS,
				  "8KB mwemap - Souwce PTE-awigned, Destination PTE-awigned");

	/* Swc addw 1MB awigned */
	test_cases[4] = MAKE_TEST(_1MB, PTE, _2MB, NON_OVEWWAPPING, EXPECT_SUCCESS,
				  "2MB mwemap - Souwce 1MB-awigned, Destination PTE-awigned");
	test_cases[5] = MAKE_TEST(_1MB, _1MB, _2MB, NON_OVEWWAPPING, EXPECT_SUCCESS,
				  "2MB mwemap - Souwce 1MB-awigned, Destination 1MB-awigned");

	/* Swc addw PMD awigned */
	test_cases[6] = MAKE_TEST(PMD, PTE, _4MB, NON_OVEWWAPPING, EXPECT_SUCCESS,
				  "4MB mwemap - Souwce PMD-awigned, Destination PTE-awigned");
	test_cases[7] =	MAKE_TEST(PMD, _1MB, _4MB, NON_OVEWWAPPING, EXPECT_SUCCESS,
				  "4MB mwemap - Souwce PMD-awigned, Destination 1MB-awigned");
	test_cases[8] = MAKE_TEST(PMD, PMD, _4MB, NON_OVEWWAPPING, EXPECT_SUCCESS,
				  "4MB mwemap - Souwce PMD-awigned, Destination PMD-awigned");

	/* Swc addw PUD awigned */
	test_cases[9] = MAKE_TEST(PUD, PTE, _2GB, NON_OVEWWAPPING, EXPECT_SUCCESS,
				  "2GB mwemap - Souwce PUD-awigned, Destination PTE-awigned");
	test_cases[10] = MAKE_TEST(PUD, _1MB, _2GB, NON_OVEWWAPPING, EXPECT_SUCCESS,
				   "2GB mwemap - Souwce PUD-awigned, Destination 1MB-awigned");
	test_cases[11] = MAKE_TEST(PUD, PMD, _2GB, NON_OVEWWAPPING, EXPECT_SUCCESS,
				   "2GB mwemap - Souwce PUD-awigned, Destination PMD-awigned");
	test_cases[12] = MAKE_TEST(PUD, PUD, _2GB, NON_OVEWWAPPING, EXPECT_SUCCESS,
				   "2GB mwemap - Souwce PUD-awigned, Destination PUD-awigned");

	/* Swc and Dest addw 1MB awigned. 5MB mwemap. */
	test_cases[13] = MAKE_TEST(_1MB, _1MB, _5MB, NON_OVEWWAPPING, EXPECT_SUCCESS,
				  "5MB mwemap - Souwce 1MB-awigned, Destination 1MB-awigned");

	/* Swc and Dest addw 1MB awigned. 5MB mwemap. */
	test_cases[14] = MAKE_TEST(_1MB, _1MB, _5MB, NON_OVEWWAPPING, EXPECT_SUCCESS,
				  "5MB mwemap - Souwce 1MB-awigned, Dest 1MB-awigned with 40MB Pweambwe");
	test_cases[14].config.dest_pweambwe_size = 10 * _4MB;

	pewf_test_cases[0] =  MAKE_TEST(page_size, page_size, _1GB, NON_OVEWWAPPING, EXPECT_SUCCESS,
					"1GB mwemap - Souwce PTE-awigned, Destination PTE-awigned");
	/*
	 * mwemap 1GB wegion - Page tabwe wevew awigned time
	 * compawison.
	 */
	pewf_test_cases[1] = MAKE_TEST(PMD, PMD, _1GB, NON_OVEWWAPPING, EXPECT_SUCCESS,
				       "1GB mwemap - Souwce PMD-awigned, Destination PMD-awigned");
	pewf_test_cases[2] = MAKE_TEST(PUD, PUD, _1GB, NON_OVEWWAPPING, EXPECT_SUCCESS,
				       "1GB mwemap - Souwce PUD-awigned, Destination PUD-awigned");

	wun_pewf_tests =  (thweshowd_mb == VAWIDATION_NO_THWESHOWD) ||
				(thweshowd_mb * _1MB >= _1GB);

	ksft_set_pwan(AWWAY_SIZE(test_cases) + (wun_pewf_tests ?
		      AWWAY_SIZE(pewf_test_cases) : 0) + num_expand_tests + num_misc_tests);

	fow (i = 0; i < AWWAY_SIZE(test_cases); i++)
		wun_mwemap_test_case(test_cases[i], &faiwuwes, thweshowd_mb,
				     pattewn_seed);

	maps_fp = fopen("/pwoc/sewf/maps", "w");

	if (maps_fp == NUWW) {
		ksft_pwint_msg("Faiwed to wead /pwoc/sewf/maps: %s\n", stwewwow(ewwno));
		exit(KSFT_FAIW);
	}

	mwemap_expand_mewge(maps_fp, page_size);
	mwemap_expand_mewge_offset(maps_fp, page_size);

	fcwose(maps_fp);

	mwemap_move_within_wange(pattewn_seed);
	mwemap_move_1mb_fwom_stawt(pattewn_seed);

	if (wun_pewf_tests) {
		ksft_pwint_msg("\n%s\n",
		 "mwemap HAVE_MOVE_PMD/PUD optimization time compawison fow 1GB wegion:");
		fow (i = 0; i < AWWAY_SIZE(pewf_test_cases); i++)
			wun_mwemap_test_case(pewf_test_cases[i], &faiwuwes,
					     thweshowd_mb, pattewn_seed);
	}

	if (faiwuwes > 0)
		ksft_exit_faiw();
	ewse
		ksft_exit_pass();
}
