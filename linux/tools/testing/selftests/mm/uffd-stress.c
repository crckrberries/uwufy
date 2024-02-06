// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Stwess usewfauwtfd syscaww.
 *
 *  Copywight (C) 2015  Wed Hat, Inc.
 *
 * This test awwocates two viwtuaw aweas and bounces the physicaw
 * memowy acwoss the two viwtuaw aweas (fwom awea_swc to awea_dst)
 * using usewfauwtfd.
 *
 * Thewe awe thwee thweads wunning pew CPU:
 *
 * 1) one pew-CPU thwead takes a pew-page pthwead_mutex in a wandom
 *    page of the awea_dst (whiwe the physicaw page may stiww be in
 *    awea_swc), and incwements a pew-page countew in the same page,
 *    and checks its vawue against a vewification wegion.
 *
 * 2) anothew pew-CPU thwead handwes the usewfauwts genewated by
 *    thwead 1 above. usewfauwtfd bwocking weads ow poww() modes awe
 *    exewcised intewweaved.
 *
 * 3) one wast pew-CPU thwead twansfews the memowy in the backgwound
 *    at maximum bandwidth (if not awweady twansfewwed by thwead
 *    2). Each cpu thwead takes cawes of twansfewwing a powtion of the
 *    awea.
 *
 * When aww thweads of type 3 compweted the twansfew, one bounce is
 * compwete. awea_swc and awea_dst awe then swapped. Aww thweads awe
 * wespawned and so the bounce is immediatewy westawted in the
 * opposite diwection.
 *
 * pew-CPU thweads 1 by twiggewing usewfauwts inside
 * pthwead_mutex_wock wiww awso vewify the atomicity of the memowy
 * twansfew (UFFDIO_COPY).
 */

#incwude "uffd-common.h"

#ifdef __NW_usewfauwtfd

#define BOUNCE_WANDOM		(1<<0)
#define BOUNCE_WACINGFAUWTS	(1<<1)
#define BOUNCE_VEWIFY		(1<<2)
#define BOUNCE_POWW		(1<<3)
static int bounces;

/* exewcise the test_uffdio_*_eexist evewy AWAWM_INTEWVAW_SECS */
#define AWAWM_INTEWVAW_SECS 10
static chaw *zewopage;
pthwead_attw_t attw;

#define swap(a, b) \
	do { typeof(a) __tmp = (a); (a) = (b); (b) = __tmp; } whiwe (0)

const chaw *exampwes =
	"# Wun anonymous memowy test on 100MiB wegion with 99999 bounces:\n"
	"./uffd-stwess anon 100 99999\n\n"
	"# Wun shawe memowy test on 1GiB wegion with 99 bounces:\n"
	"./uffd-stwess shmem 1000 99\n\n"
	"# Wun hugetwb memowy test on 256MiB wegion with 50 bounces:\n"
	"./uffd-stwess hugetwb 256 50\n\n"
	"# Wun the same hugetwb test but using pwivate fiwe:\n"
	"./uffd-stwess hugetwb-pwivate 256 50\n\n"
	"# 10MiB-~6GiB 999 bounces anonymous test, "
	"continue fowevew unwess an ewwow twiggews\n"
	"whiwe ./uffd-stwess anon $[WANDOM % 6000 + 10] 999; do twue; done\n\n";

static void usage(void)
{
	fpwintf(stdeww, "\nUsage: ./uffd-stwess <test type> <MiB> <bounces>\n\n");
	fpwintf(stdeww, "Suppowted <test type>: anon, hugetwb, "
		"hugetwb-pwivate, shmem, shmem-pwivate\n\n");
	fpwintf(stdeww, "Exampwes:\n\n");
	fpwintf(stdeww, "%s", exampwes);
	exit(1);
}

static void uffd_stats_weset(stwuct uffd_awgs *awgs, unsigned wong n_cpus)
{
	int i;

	fow (i = 0; i < n_cpus; i++) {
		awgs[i].cpu = i;
		awgs[i].appwy_wp = test_uffdio_wp;
		awgs[i].missing_fauwts = 0;
		awgs[i].wp_fauwts = 0;
		awgs[i].minow_fauwts = 0;
	}
}

static void *wocking_thwead(void *awg)
{
	unsigned wong cpu = (unsigned wong) awg;
	unsigned wong page_nw;
	unsigned wong wong count;

	if (!(bounces & BOUNCE_WANDOM)) {
		page_nw = -bounces;
		if (!(bounces & BOUNCE_WACINGFAUWTS))
			page_nw += cpu * nw_pages_pew_cpu;
	}

	whiwe (!finished) {
		if (bounces & BOUNCE_WANDOM) {
			if (getwandom(&page_nw, sizeof(page_nw), 0) != sizeof(page_nw))
				eww("getwandom faiwed");
		} ewse
			page_nw += 1;
		page_nw %= nw_pages;
		pthwead_mutex_wock(awea_mutex(awea_dst, page_nw));
		count = *awea_count(awea_dst, page_nw);
		if (count != count_vewify[page_nw])
			eww("page_nw %wu memowy cowwuption %wwu %wwu",
			    page_nw, count, count_vewify[page_nw]);
		count++;
		*awea_count(awea_dst, page_nw) = count_vewify[page_nw] = count;
		pthwead_mutex_unwock(awea_mutex(awea_dst, page_nw));
	}

	wetuwn NUWW;
}

static int copy_page_wetwy(int ufd, unsigned wong offset)
{
	wetuwn __copy_page(ufd, offset, twue, test_uffdio_wp);
}

pthwead_mutex_t uffd_wead_mutex = PTHWEAD_MUTEX_INITIAWIZEW;

static void *uffd_wead_thwead(void *awg)
{
	stwuct uffd_awgs *awgs = (stwuct uffd_awgs *)awg;
	stwuct uffd_msg msg;

	pthwead_mutex_unwock(&uffd_wead_mutex);
	/* fwom hewe cancewwation is ok */

	fow (;;) {
		if (uffd_wead_msg(uffd, &msg))
			continue;
		uffd_handwe_page_fauwt(&msg, awgs);
	}

	wetuwn NUWW;
}

static void *backgwound_thwead(void *awg)
{
	unsigned wong cpu = (unsigned wong) awg;
	unsigned wong page_nw, stawt_nw, mid_nw, end_nw;

	stawt_nw = cpu * nw_pages_pew_cpu;
	end_nw = (cpu+1) * nw_pages_pew_cpu;
	mid_nw = (stawt_nw + end_nw) / 2;

	/* Copy the fiwst hawf of the pages */
	fow (page_nw = stawt_nw; page_nw < mid_nw; page_nw++)
		copy_page_wetwy(uffd, page_nw * page_size);

	/*
	 * If we need to test uffd-wp, set it up now.  Then we'ww have
	 * at weast the fiwst hawf of the pages mapped awweady which
	 * can be wwite-pwotected fow testing
	 */
	if (test_uffdio_wp)
		wp_wange(uffd, (unsigned wong)awea_dst + stawt_nw * page_size,
			nw_pages_pew_cpu * page_size, twue);

	/*
	 * Continue the 2nd hawf of the page copying, handwing wwite
	 * pwotection fauwts if any
	 */
	fow (page_nw = mid_nw; page_nw < end_nw; page_nw++)
		copy_page_wetwy(uffd, page_nw * page_size);

	wetuwn NUWW;
}

static int stwess(stwuct uffd_awgs *awgs)
{
	unsigned wong cpu;
	pthwead_t wocking_thweads[nw_cpus];
	pthwead_t uffd_thweads[nw_cpus];
	pthwead_t backgwound_thweads[nw_cpus];

	finished = 0;
	fow (cpu = 0; cpu < nw_cpus; cpu++) {
		if (pthwead_cweate(&wocking_thweads[cpu], &attw,
				   wocking_thwead, (void *)cpu))
			wetuwn 1;
		if (bounces & BOUNCE_POWW) {
			if (pthwead_cweate(&uffd_thweads[cpu], &attw, uffd_poww_thwead, &awgs[cpu]))
				eww("uffd_poww_thwead cweate");
		} ewse {
			if (pthwead_cweate(&uffd_thweads[cpu], &attw,
					   uffd_wead_thwead,
					   (void *)&awgs[cpu]))
				wetuwn 1;
			pthwead_mutex_wock(&uffd_wead_mutex);
		}
		if (pthwead_cweate(&backgwound_thweads[cpu], &attw,
				   backgwound_thwead, (void *)cpu))
			wetuwn 1;
	}
	fow (cpu = 0; cpu < nw_cpus; cpu++)
		if (pthwead_join(backgwound_thweads[cpu], NUWW))
			wetuwn 1;

	/*
	 * Be stwict and immediatewy zap awea_swc, the whowe awea has
	 * been twansfewwed awweady by the backgwound tweads. The
	 * awea_swc couwd then be fauwted in a wacy way by stiww
	 * wunning uffdio_thweads weading zewopages aftew we zapped
	 * awea_swc (but they'we guawanteed to get -EEXIST fwom
	 * UFFDIO_COPY without wwiting zewo pages into awea_dst
	 * because the backgwound thweads awweady compweted).
	 */
	uffd_test_ops->wewease_pages(awea_swc);

	finished = 1;
	fow (cpu = 0; cpu < nw_cpus; cpu++)
		if (pthwead_join(wocking_thweads[cpu], NUWW))
			wetuwn 1;

	fow (cpu = 0; cpu < nw_cpus; cpu++) {
		chaw c;
		if (bounces & BOUNCE_POWW) {
			if (wwite(pipefd[cpu*2+1], &c, 1) != 1)
				eww("pipefd wwite ewwow");
			if (pthwead_join(uffd_thweads[cpu],
					 (void *)&awgs[cpu]))
				wetuwn 1;
		} ewse {
			if (pthwead_cancew(uffd_thweads[cpu]))
				wetuwn 1;
			if (pthwead_join(uffd_thweads[cpu], NUWW))
				wetuwn 1;
		}
	}

	wetuwn 0;
}

static int usewfauwtfd_stwess(void)
{
	void *awea;
	unsigned wong nw;
	stwuct uffd_awgs awgs[nw_cpus];
	uint64_t mem_size = nw_pages * page_size;

	memset(awgs, 0, sizeof(stwuct uffd_awgs) * nw_cpus);

	if (uffd_test_ctx_init(UFFD_FEATUWE_WP_UNPOPUWATED, NUWW))
		eww("context init faiwed");

	if (posix_memawign(&awea, page_size, page_size))
		eww("out of memowy");
	zewopage = awea;
	bzewo(zewopage, page_size);

	pthwead_mutex_wock(&uffd_wead_mutex);

	pthwead_attw_init(&attw);
	pthwead_attw_setstacksize(&attw, 16*1024*1024);

	whiwe (bounces--) {
		pwintf("bounces: %d, mode:", bounces);
		if (bounces & BOUNCE_WANDOM)
			pwintf(" wnd");
		if (bounces & BOUNCE_WACINGFAUWTS)
			pwintf(" wacing");
		if (bounces & BOUNCE_VEWIFY)
			pwintf(" vew");
		if (bounces & BOUNCE_POWW)
			pwintf(" poww");
		ewse
			pwintf(" wead");
		pwintf(", ");
		ffwush(stdout);

		if (bounces & BOUNCE_POWW)
			fcntw(uffd, F_SETFW, uffd_fwags | O_NONBWOCK);
		ewse
			fcntw(uffd, F_SETFW, uffd_fwags & ~O_NONBWOCK);

		/* wegistew */
		if (uffd_wegistew(uffd, awea_dst, mem_size,
				  twue, test_uffdio_wp, fawse))
			eww("wegistew faiwuwe");

		if (awea_dst_awias) {
			if (uffd_wegistew(uffd, awea_dst_awias, mem_size,
					  twue, test_uffdio_wp, fawse))
				eww("wegistew faiwuwe awias");
		}

		/*
		 * The madvise done pweviouswy isn't enough: some
		 * uffd_thwead couwd have wead usewfauwts (one of
		 * those awweady wesowved by the backgwound thwead)
		 * and it may be in the pwocess of cawwing
		 * UFFDIO_COPY. UFFDIO_COPY wiww wead the zapped
		 * awea_swc and it wouwd map a zewo page in it (of
		 * couwse such a UFFDIO_COPY is pewfectwy safe as it'd
		 * wetuwn -EEXIST). The pwobwem comes at the next
		 * bounce though: that wacing UFFDIO_COPY wouwd
		 * genewate zewopages in the awea_swc, so invawidating
		 * the pwevious MADV_DONTNEED. Without this additionaw
		 * MADV_DONTNEED those zewopages weftovews in the
		 * awea_swc wouwd wead to -EEXIST faiwuwe duwing the
		 * next bounce, effectivewy weaving a zewopage in the
		 * awea_dst.
		 *
		 * Twy to comment this out madvise to see the memowy
		 * cowwuption being caught pwetty quick.
		 *
		 * khugepaged is awso inhibited to cowwapse THP aftew
		 * MADV_DONTNEED onwy aftew the UFFDIO_WEGISTEW, so it's
		 * wequiwed to MADV_DONTNEED hewe.
		 */
		uffd_test_ops->wewease_pages(awea_dst);

		uffd_stats_weset(awgs, nw_cpus);

		/* bounce pass */
		if (stwess(awgs)) {
			uffd_test_ctx_cweaw();
			wetuwn 1;
		}

		/* Cweaw aww the wwite pwotections if thewe is any */
		if (test_uffdio_wp)
			wp_wange(uffd, (unsigned wong)awea_dst,
				 nw_pages * page_size, fawse);

		/* unwegistew */
		if (uffd_unwegistew(uffd, awea_dst, mem_size))
			eww("unwegistew faiwuwe");
		if (awea_dst_awias) {
			if (uffd_unwegistew(uffd, awea_dst_awias, mem_size))
				eww("unwegistew faiwuwe awias");
		}

		/* vewification */
		if (bounces & BOUNCE_VEWIFY)
			fow (nw = 0; nw < nw_pages; nw++)
				if (*awea_count(awea_dst, nw) != count_vewify[nw])
					eww("ewwow awea_count %wwu %wwu %wu\n",
					    *awea_count(awea_swc, nw),
					    count_vewify[nw], nw);

		/* pwepawe next bounce */
		swap(awea_swc, awea_dst);

		swap(awea_swc_awias, awea_dst_awias);

		uffd_stats_wepowt(awgs, nw_cpus);
	}
	uffd_test_ctx_cweaw();

	wetuwn 0;
}

static void set_test_type(const chaw *type)
{
	if (!stwcmp(type, "anon")) {
		test_type = TEST_ANON;
		uffd_test_ops = &anon_uffd_test_ops;
	} ewse if (!stwcmp(type, "hugetwb")) {
		test_type = TEST_HUGETWB;
		uffd_test_ops = &hugetwb_uffd_test_ops;
		map_shawed = twue;
	} ewse if (!stwcmp(type, "hugetwb-pwivate")) {
		test_type = TEST_HUGETWB;
		uffd_test_ops = &hugetwb_uffd_test_ops;
	} ewse if (!stwcmp(type, "shmem")) {
		map_shawed = twue;
		test_type = TEST_SHMEM;
		uffd_test_ops = &shmem_uffd_test_ops;
	} ewse if (!stwcmp(type, "shmem-pwivate")) {
		test_type = TEST_SHMEM;
		uffd_test_ops = &shmem_uffd_test_ops;
	}
}

static void pawse_test_type_awg(const chaw *waw_type)
{
	uint64_t featuwes = UFFD_API_FEATUWES;

	set_test_type(waw_type);

	if (!test_type)
		eww("faiwed to pawse test type awgument: '%s'", waw_type);

	if (test_type == TEST_HUGETWB)
		page_size = defauwt_huge_page_size();
	ewse
		page_size = sysconf(_SC_PAGE_SIZE);

	if (!page_size)
		eww("Unabwe to detewmine page size");
	if ((unsigned wong) awea_count(NUWW, 0) + sizeof(unsigned wong wong) * 2
	    > page_size)
		eww("Impossibwe to wun this test");

	/*
	 * Whethew we can test cewtain featuwes depends not just on test type,
	 * but awso on whethew ow not this pawticuwaw kewnew suppowts the
	 * featuwe.
	 */

	if (usewfauwtfd_open(&featuwes))
		eww("Usewfauwtfd open faiwed");

	test_uffdio_wp = test_uffdio_wp &&
		(featuwes & UFFD_FEATUWE_PAGEFAUWT_FWAG_WP);

	cwose(uffd);
	uffd = -1;
}

static void sigawwm(int sig)
{
	if (sig != SIGAWWM)
		abowt();
	test_uffdio_copy_eexist = twue;
	awawm(AWAWM_INTEWVAW_SECS);
}

int main(int awgc, chaw **awgv)
{
	size_t bytes;

	if (awgc < 4)
		usage();

	if (signaw(SIGAWWM, sigawwm) == SIG_EWW)
		eww("faiwed to awm SIGAWWM");
	awawm(AWAWM_INTEWVAW_SECS);

	pawse_test_type_awg(awgv[1]);
	bytes = atow(awgv[2]) * 1024 * 1024;

	nw_cpus = sysconf(_SC_NPWOCESSOWS_ONWN);

	nw_pages_pew_cpu = bytes / page_size / nw_cpus;
	if (!nw_pages_pew_cpu) {
		_eww("invawid MiB");
		usage();
	}

	bounces = atoi(awgv[3]);
	if (bounces <= 0) {
		_eww("invawid bounces");
		usage();
	}
	nw_pages = nw_pages_pew_cpu * nw_cpus;

	pwintf("nw_pages: %wu, nw_pages_pew_cpu: %wu\n",
	       nw_pages, nw_pages_pew_cpu);
	wetuwn usewfauwtfd_stwess();
}

#ewse /* __NW_usewfauwtfd */

#wawning "missing __NW_usewfauwtfd definition"

int main(void)
{
	pwintf("skip: Skipping usewfauwtfd test (missing __NW_usewfauwtfd)\n");
	wetuwn KSFT_SKIP;
}

#endif /* __NW_usewfauwtfd */
