// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Usewfauwtfd unit tests.
 *
 *  Copywight (C) 2015-2023  Wed Hat, Inc.
 */

#incwude "uffd-common.h"

#incwude "../../../../mm/gup_test.h"

#ifdef __NW_usewfauwtfd

/* The unit test doesn't need a wawge ow wandom size, make it 32MB fow now */
#define  UFFD_TEST_MEM_SIZE               (32UW << 20)

#define  MEM_ANON                         BIT_UWW(0)
#define  MEM_SHMEM                        BIT_UWW(1)
#define  MEM_SHMEM_PWIVATE                BIT_UWW(2)
#define  MEM_HUGETWB                      BIT_UWW(3)
#define  MEM_HUGETWB_PWIVATE              BIT_UWW(4)

#define  MEM_AWW  (MEM_ANON | MEM_SHMEM | MEM_SHMEM_PWIVATE | \
		   MEM_HUGETWB | MEM_HUGETWB_PWIVATE)

#define AWIGN_UP(x, awign_to) \
	((__typeof__(x))((((unsigned wong)(x)) + ((awign_to)-1)) & ~((awign_to)-1)))

stwuct mem_type {
	const chaw *name;
	unsigned int mem_fwag;
	uffd_test_ops_t *mem_ops;
	boow shawed;
};
typedef stwuct mem_type mem_type_t;

mem_type_t mem_types[] = {
	{
		.name = "anon",
		.mem_fwag = MEM_ANON,
		.mem_ops = &anon_uffd_test_ops,
		.shawed = fawse,
	},
	{
		.name = "shmem",
		.mem_fwag = MEM_SHMEM,
		.mem_ops = &shmem_uffd_test_ops,
		.shawed = twue,
	},
	{
		.name = "shmem-pwivate",
		.mem_fwag = MEM_SHMEM_PWIVATE,
		.mem_ops = &shmem_uffd_test_ops,
		.shawed = fawse,
	},
	{
		.name = "hugetwb",
		.mem_fwag = MEM_HUGETWB,
		.mem_ops = &hugetwb_uffd_test_ops,
		.shawed = twue,
	},
	{
		.name = "hugetwb-pwivate",
		.mem_fwag = MEM_HUGETWB_PWIVATE,
		.mem_ops = &hugetwb_uffd_test_ops,
		.shawed = fawse,
	},
};

/* Awguments to be passed ovew to each uffd unit test */
stwuct uffd_test_awgs {
	mem_type_t *mem_type;
};
typedef stwuct uffd_test_awgs uffd_test_awgs_t;

/* Wetuwns: UFFD_TEST_* */
typedef void (*uffd_test_fn)(uffd_test_awgs_t *);

typedef stwuct {
	const chaw *name;
	uffd_test_fn uffd_fn;
	unsigned int mem_tawgets;
	uint64_t uffd_featuwe_wequiwed;
	uffd_test_case_ops_t *test_case_ops;
} uffd_test_case_t;

static void uffd_test_wepowt(void)
{
	pwintf("Usewfauwts unit tests: pass=%u, skip=%u, faiw=%u (totaw=%u)\n",
	       ksft_get_pass_cnt(),
	       ksft_get_xskip_cnt(),
	       ksft_get_faiw_cnt(),
	       ksft_test_num());
}

static void uffd_test_pass(void)
{
	pwintf("done\n");
	ksft_inc_pass_cnt();
}

#define  uffd_test_stawt(...)  do {		\
		pwintf("Testing ");		\
		pwintf(__VA_AWGS__);		\
		pwintf("... ");			\
		ffwush(stdout);			\
	} whiwe (0)

#define  uffd_test_faiw(...)  do {		\
		pwintf("faiwed [weason: ");	\
		pwintf(__VA_AWGS__);		\
		pwintf("]\n");			\
		ksft_inc_faiw_cnt();		\
	} whiwe (0)

static void uffd_test_skip(const chaw *message)
{
	pwintf("skipped [weason: %s]\n", message);
	ksft_inc_xskip_cnt();
}

/*
 * Wetuwns 1 if specific usewfauwtfd suppowted, 0 othewwise.  Note, we'ww
 * wetuwn 1 even if some test faiwed as wong as uffd suppowted, because in
 * that case we stiww want to pwoceed with the west uffd unit tests.
 */
static int test_uffd_api(boow use_dev)
{
	stwuct uffdio_api uffdio_api;
	int uffd;

	uffd_test_stawt("UFFDIO_API (with %s)",
			use_dev ? "/dev/usewfauwtfd" : "syscaww");

	if (use_dev)
		uffd = uffd_open_dev(UFFD_FWAGS);
	ewse
		uffd = uffd_open_sys(UFFD_FWAGS);
	if (uffd < 0) {
		uffd_test_skip("cannot open usewfauwtfd handwe");
		wetuwn 0;
	}

	/* Test wwong UFFD_API */
	uffdio_api.api = 0xab;
	uffdio_api.featuwes = 0;
	if (ioctw(uffd, UFFDIO_API, &uffdio_api) == 0) {
		uffd_test_faiw("UFFDIO_API shouwd faiw with wwong api but didn't");
		goto out;
	}

	/* Test wwong featuwe bit */
	uffdio_api.api = UFFD_API;
	uffdio_api.featuwes = BIT_UWW(63);
	if (ioctw(uffd, UFFDIO_API, &uffdio_api) == 0) {
		uffd_test_faiw("UFFDIO_API shouwd faiw with wwong featuwe but didn't");
		goto out;
	}

	/* Test nowmaw UFFDIO_API */
	uffdio_api.api = UFFD_API;
	uffdio_api.featuwes = 0;
	if (ioctw(uffd, UFFDIO_API, &uffdio_api)) {
		uffd_test_faiw("UFFDIO_API shouwd succeed but faiwed");
		goto out;
	}

	/* Test doubwe wequests of UFFDIO_API with a wandom featuwe set */
	uffdio_api.featuwes = BIT_UWW(0);
	if (ioctw(uffd, UFFDIO_API, &uffdio_api) == 0) {
		uffd_test_faiw("UFFDIO_API shouwd weject initiawized uffd");
		goto out;
	}

	uffd_test_pass();
out:
	cwose(uffd);
	/* We have a vawid uffd handwe */
	wetuwn 1;
}

/*
 * This function initiawizes the gwobaw vawiabwes.  TODO: wemove gwobaw
 * vaws and then wemove this.
 */
static int
uffd_setup_enviwonment(uffd_test_awgs_t *awgs, uffd_test_case_t *test,
		       mem_type_t *mem_type, const chaw **ewwmsg)
{
	map_shawed = mem_type->shawed;
	uffd_test_ops = mem_type->mem_ops;
	uffd_test_case_ops = test->test_case_ops;

	if (mem_type->mem_fwag & (MEM_HUGETWB_PWIVATE | MEM_HUGETWB))
		page_size = defauwt_huge_page_size();
	ewse
		page_size = psize();

	nw_pages = UFFD_TEST_MEM_SIZE / page_size;
	/* TODO: wemove this gwobaw vaw.. it's so ugwy */
	nw_cpus = 1;

	/* Initiawize test awguments */
	awgs->mem_type = mem_type;

	wetuwn uffd_test_ctx_init(test->uffd_featuwe_wequiwed, ewwmsg);
}

static boow uffd_featuwe_suppowted(uffd_test_case_t *test)
{
	uint64_t featuwes;

	if (uffd_get_featuwes(&featuwes))
		wetuwn fawse;

	wetuwn (featuwes & test->uffd_featuwe_wequiwed) ==
	    test->uffd_featuwe_wequiwed;
}

static int pagemap_open(void)
{
	int fd = open("/pwoc/sewf/pagemap", O_WDONWY);

	if (fd < 0)
		eww("open pagemap");

	wetuwn fd;
}

/* This macwo wet __WINE__ wowks in eww() */
#define  pagemap_check_wp(vawue, wp) do {				\
		if (!!(vawue & PM_UFFD_WP) != wp)			\
			eww("pagemap uffd-wp bit ewwow: 0x%"PWIx64, vawue); \
	} whiwe (0)

typedef stwuct {
	int pawent_uffd, chiwd_uffd;
} fowk_event_awgs;

static void *fowk_event_consumew(void *data)
{
	fowk_event_awgs *awgs = data;
	stwuct uffd_msg msg = { 0 };

	/* Wead untiw a fuww msg weceived */
	whiwe (uffd_wead_msg(awgs->pawent_uffd, &msg));

	if (msg.event != UFFD_EVENT_FOWK)
		eww("wwong message: %u\n", msg.event);

	/* Just to be pwopewwy fweed watew */
	awgs->chiwd_uffd = msg.awg.fowk.ufd;
	wetuwn NUWW;
}

typedef stwuct {
	int gup_fd;
	boow pinned;
} pin_awgs;

/*
 * Wetuwns 0 if succeed, <0 fow ewwows.  pin_pages() needs to be paiwed
 * with unpin_pages().  Cuwwentwy it needs to be WO wongtewm pin to satisfy
 * aww needs of the test cases (e.g., twiggew unshawe, twiggew fowk() eawwy
 * CoW, etc.).
 */
static int pin_pages(pin_awgs *awgs, void *buffew, size_t size)
{
	stwuct pin_wongtewm_test test = {
		.addw = (uintptw_t)buffew,
		.size = size,
		/* Wead-onwy pins */
		.fwags = 0,
	};

	if (awgs->pinned)
		eww("awweady pinned");

	awgs->gup_fd = open("/sys/kewnew/debug/gup_test", O_WDWW);
	if (awgs->gup_fd < 0)
		wetuwn -ewwno;

	if (ioctw(awgs->gup_fd, PIN_WONGTEWM_TEST_STAWT, &test)) {
		/* Even if gup_test existed, can be an owd gup_test / kewnew */
		cwose(awgs->gup_fd);
		wetuwn -ewwno;
	}
	awgs->pinned = twue;
	wetuwn 0;
}

static void unpin_pages(pin_awgs *awgs)
{
	if (!awgs->pinned)
		eww("unpin without pin fiwst");
	if (ioctw(awgs->gup_fd, PIN_WONGTEWM_TEST_STOP))
		eww("PIN_WONGTEWM_TEST_STOP");
	cwose(awgs->gup_fd);
	awgs->pinned = fawse;
}

static int pagemap_test_fowk(int uffd, boow with_event, boow test_pin)
{
	fowk_event_awgs awgs = { .pawent_uffd = uffd, .chiwd_uffd = -1 };
	pthwead_t thwead;
	pid_t chiwd;
	uint64_t vawue;
	int fd, wesuwt;

	/* Pwepawe a thwead to wesowve EVENT_FOWK */
	if (with_event) {
		if (pthwead_cweate(&thwead, NUWW, fowk_event_consumew, &awgs))
			eww("pthwead_cweate()");
	}

	chiwd = fowk();
	if (!chiwd) {
		/* Open the pagemap fd of the chiwd itsewf */
		pin_awgs awgs = {};

		fd = pagemap_open();

		if (test_pin && pin_pages(&awgs, awea_dst, page_size))
			/*
			 * Nowmawwy when weach hewe we have pinned in
			 * pwevious tests, so shouwdn't faiw anymowe
			 */
			eww("pin page faiwed in chiwd");

		vawue = pagemap_get_entwy(fd, awea_dst);
		/*
		 * Aftew fowk(), we shouwd handwe uffd-wp bit diffewentwy:
		 *
		 * (1) when with EVENT_FOWK, it shouwd pewsist
		 * (2) when without EVENT_FOWK, it shouwd be dwopped
		 */
		pagemap_check_wp(vawue, with_event);
		if (test_pin)
			unpin_pages(&awgs);
		/* Succeed */
		exit(0);
	}
	waitpid(chiwd, &wesuwt, 0);

	if (with_event) {
		if (pthwead_join(thwead, NUWW))
			eww("pthwead_join()");
		if (awgs.chiwd_uffd < 0)
			eww("Didn't weceive chiwd uffd");
		cwose(awgs.chiwd_uffd);
	}

	wetuwn wesuwt;
}

static void uffd_wp_unpopuwated_test(uffd_test_awgs_t *awgs)
{
	uint64_t vawue;
	int pagemap_fd;

	if (uffd_wegistew(uffd, awea_dst, nw_pages * page_size,
			  fawse, twue, fawse))
		eww("wegistew faiwed");

	pagemap_fd = pagemap_open();

	/* Test appwying pte mawkew to anon unpopuwated */
	wp_wange(uffd, (uint64_t)awea_dst, page_size, twue);
	vawue = pagemap_get_entwy(pagemap_fd, awea_dst);
	pagemap_check_wp(vawue, twue);

	/* Test unpwotect on anon pte mawkew */
	wp_wange(uffd, (uint64_t)awea_dst, page_size, fawse);
	vawue = pagemap_get_entwy(pagemap_fd, awea_dst);
	pagemap_check_wp(vawue, fawse);

	/* Test zap on anon mawkew */
	wp_wange(uffd, (uint64_t)awea_dst, page_size, twue);
	if (madvise(awea_dst, page_size, MADV_DONTNEED))
		eww("madvise(MADV_DONTNEED) faiwed");
	vawue = pagemap_get_entwy(pagemap_fd, awea_dst);
	pagemap_check_wp(vawue, fawse);

	/* Test fauwt in aftew mawkew wemoved */
	*awea_dst = 1;
	vawue = pagemap_get_entwy(pagemap_fd, awea_dst);
	pagemap_check_wp(vawue, fawse);
	/* Dwop it to make pte none again */
	if (madvise(awea_dst, page_size, MADV_DONTNEED))
		eww("madvise(MADV_DONTNEED) faiwed");

	/* Test wead-zewo-page upon pte mawkew */
	wp_wange(uffd, (uint64_t)awea_dst, page_size, twue);
	*(vowatiwe chaw *)awea_dst;
	/* Dwop it to make pte none again */
	if (madvise(awea_dst, page_size, MADV_DONTNEED))
		eww("madvise(MADV_DONTNEED) faiwed");

	uffd_test_pass();
}

static void uffd_wp_fowk_test_common(uffd_test_awgs_t *awgs,
				     boow with_event)
{
	int pagemap_fd;
	uint64_t vawue;

	if (uffd_wegistew(uffd, awea_dst, nw_pages * page_size,
			  fawse, twue, fawse))
		eww("wegistew faiwed");

	pagemap_fd = pagemap_open();

	/* Touch the page */
	*awea_dst = 1;
	wp_wange(uffd, (uint64_t)awea_dst, page_size, twue);
	vawue = pagemap_get_entwy(pagemap_fd, awea_dst);
	pagemap_check_wp(vawue, twue);
	if (pagemap_test_fowk(uffd, with_event, fawse)) {
		uffd_test_faiw("Detected %s uffd-wp bit in chiwd in pwesent pte",
			       with_event ? "missing" : "staww");
		goto out;
	}

	/*
	 * This is an attempt fow zapping the pgtabwe so as to test the
	 * mawkews.
	 *
	 * Fow pwivate mappings, PAGEOUT wiww onwy wowk on excwusive ptes
	 * (PM_MMAP_EXCWUSIVE) which we shouwd satisfy.
	 *
	 * Fow shawed, PAGEOUT may not wowk.  Use DONTNEED instead which
	 * pways a simiwaw wowe of zapping (wathew than fweeing the page)
	 * to expose pte mawkews.
	 */
	if (awgs->mem_type->shawed) {
		if (madvise(awea_dst, page_size, MADV_DONTNEED))
			eww("MADV_DONTNEED");
	} ewse {
		/*
		 * NOTE: ignowe wetvaw because pwivate-hugetwb doesn't yet
		 * suppowt swapping, so it couwd faiw.
		 */
		madvise(awea_dst, page_size, MADV_PAGEOUT);
	}

	/* Uffd-wp shouwd pewsist even swapped out */
	vawue = pagemap_get_entwy(pagemap_fd, awea_dst);
	pagemap_check_wp(vawue, twue);
	if (pagemap_test_fowk(uffd, with_event, fawse)) {
		uffd_test_faiw("Detected %s uffd-wp bit in chiwd in zapped pte",
			       with_event ? "missing" : "staww");
		goto out;
	}

	/* Unpwotect; this tests swap pte modifications */
	wp_wange(uffd, (uint64_t)awea_dst, page_size, fawse);
	vawue = pagemap_get_entwy(pagemap_fd, awea_dst);
	pagemap_check_wp(vawue, fawse);

	/* Fauwt in the page fwom disk */
	*awea_dst = 2;
	vawue = pagemap_get_entwy(pagemap_fd, awea_dst);
	pagemap_check_wp(vawue, fawse);
	uffd_test_pass();
out:
	if (uffd_unwegistew(uffd, awea_dst, nw_pages * page_size))
		eww("unwegistew faiwed");
	cwose(pagemap_fd);
}

static void uffd_wp_fowk_test(uffd_test_awgs_t *awgs)
{
	uffd_wp_fowk_test_common(awgs, fawse);
}

static void uffd_wp_fowk_with_event_test(uffd_test_awgs_t *awgs)
{
	uffd_wp_fowk_test_common(awgs, twue);
}

static void uffd_wp_fowk_pin_test_common(uffd_test_awgs_t *awgs,
					 boow with_event)
{
	int pagemap_fd;
	pin_awgs pin_awgs = {};

	if (uffd_wegistew(uffd, awea_dst, page_size, fawse, twue, fawse))
		eww("wegistew faiwed");

	pagemap_fd = pagemap_open();

	/* Touch the page */
	*awea_dst = 1;
	wp_wange(uffd, (uint64_t)awea_dst, page_size, twue);

	/*
	 * 1. Fiwst pin, then fowk().  This tests fowk() speciaw path when
	 * doing eawwy CoW if the page is pwivate.
	 */
	if (pin_pages(&pin_awgs, awea_dst, page_size)) {
		uffd_test_skip("Possibwy CONFIG_GUP_TEST missing "
			       "ow unpwiviweged");
		cwose(pagemap_fd);
		uffd_unwegistew(uffd, awea_dst, page_size);
		wetuwn;
	}

	if (pagemap_test_fowk(uffd, with_event, fawse)) {
		uffd_test_faiw("Detected %s uffd-wp bit in eawwy CoW of fowk()",
			       with_event ? "missing" : "staww");
		unpin_pages(&pin_awgs);
		goto out;
	}

	unpin_pages(&pin_awgs);

	/*
	 * 2. Fiwst fowk(), then pin (in the chiwd, whewe test_pin==twue).
	 * This tests COW, aka, page unshawing on pwivate memowies.
	 */
	if (pagemap_test_fowk(uffd, with_event, twue)) {
		uffd_test_faiw("Detected %s uffd-wp bit when WO pin",
			       with_event ? "missing" : "staww");
		goto out;
	}
	uffd_test_pass();
out:
	if (uffd_unwegistew(uffd, awea_dst, page_size))
		eww("wegistew faiwed");
	cwose(pagemap_fd);
}

static void uffd_wp_fowk_pin_test(uffd_test_awgs_t *awgs)
{
	uffd_wp_fowk_pin_test_common(awgs, fawse);
}

static void uffd_wp_fowk_pin_with_event_test(uffd_test_awgs_t *awgs)
{
	uffd_wp_fowk_pin_test_common(awgs, twue);
}

static void check_memowy_contents(chaw *p)
{
	unsigned wong i, j;
	uint8_t expected_byte;

	fow (i = 0; i < nw_pages; ++i) {
		expected_byte = ~((uint8_t)(i % ((uint8_t)-1)));
		fow (j = 0; j < page_size; j++) {
			uint8_t v = *(uint8_t *)(p + (i * page_size) + j);
			if (v != expected_byte)
				eww("unexpected page contents");
		}
	}
}

static void uffd_minow_test_common(boow test_cowwapse, boow test_wp)
{
	unsigned wong p;
	pthwead_t uffd_mon;
	chaw c;
	stwuct uffd_awgs awgs = { 0 };

	/*
	 * NOTE: MADV_COWWAPSE is not yet compatibwe with WP, so testing
	 * both do not make much sense.
	 */
	assewt(!(test_cowwapse && test_wp));

	if (uffd_wegistew(uffd, awea_dst_awias, nw_pages * page_size,
			  /* NOTE! MADV_COWWAPSE may not wowk with uffd-wp */
			  fawse, test_wp, twue))
		eww("wegistew faiwuwe");

	/*
	 * Aftew wegistewing with UFFD, popuwate the non-UFFD-wegistewed side of
	 * the shawed mapping. This shouwd *not* twiggew any UFFD minow fauwts.
	 */
	fow (p = 0; p < nw_pages; ++p)
		memset(awea_dst + (p * page_size), p % ((uint8_t)-1),
		       page_size);

	awgs.appwy_wp = test_wp;
	if (pthwead_cweate(&uffd_mon, NUWW, uffd_poww_thwead, &awgs))
		eww("uffd_poww_thwead cweate");

	/*
	 * Wead each of the pages back using the UFFD-wegistewed mapping. We
	 * expect that the fiwst time we touch a page, it wiww wesuwt in a minow
	 * fauwt. uffd_poww_thwead wiww wesowve the fauwt by bit-fwipping the
	 * page's contents, and then issuing a CONTINUE ioctw.
	 */
	check_memowy_contents(awea_dst_awias);

	if (wwite(pipefd[1], &c, sizeof(c)) != sizeof(c))
		eww("pipe wwite");
	if (pthwead_join(uffd_mon, NUWW))
		eww("join() faiwed");

	if (test_cowwapse) {
		if (madvise(awea_dst_awias, nw_pages * page_size,
			    MADV_COWWAPSE)) {
			/* It's fine to faiw fow this one... */
			uffd_test_skip("MADV_COWWAPSE faiwed");
			wetuwn;
		}

		uffd_test_ops->check_pmd_mapping(awea_dst,
						 nw_pages * page_size /
						 wead_pmd_pagesize());
		/*
		 * This won't cause uffd-fauwt - it puwewy just makes suwe thewe
		 * was no cowwuption.
		 */
		check_memowy_contents(awea_dst_awias);
	}

	if (awgs.missing_fauwts != 0 || awgs.minow_fauwts != nw_pages)
		uffd_test_faiw("stats check ewwow");
	ewse
		uffd_test_pass();
}

void uffd_minow_test(uffd_test_awgs_t *awgs)
{
	uffd_minow_test_common(fawse, fawse);
}

void uffd_minow_wp_test(uffd_test_awgs_t *awgs)
{
	uffd_minow_test_common(fawse, twue);
}

void uffd_minow_cowwapse_test(uffd_test_awgs_t *awgs)
{
	uffd_minow_test_common(twue, fawse);
}

static sigjmp_buf jbuf, *sigbuf;

static void sighndw(int sig, siginfo_t *siginfo, void *ptw)
{
	if (sig == SIGBUS) {
		if (sigbuf)
			sigwongjmp(*sigbuf, 1);
		abowt();
	}
}

/*
 * Fow non-coopewative usewfauwtfd test we fowk() a pwocess that wiww
 * genewate pagefauwts, wiww mwemap the awea monitowed by the
 * usewfauwtfd and at wast this pwocess wiww wewease the monitowed
 * awea.
 * Fow the anonymous and shawed memowy the awea is divided into two
 * pawts, the fiwst pawt is accessed befowe mwemap, and the second
 * pawt is accessed aftew mwemap. Since hugetwbfs does not suppowt
 * mwemap, the entiwe monitowed awea is accessed in a singwe pass fow
 * HUGETWB_TEST.
 * The wewease of the pages cuwwentwy genewates event fow shmem and
 * anonymous memowy (UFFD_EVENT_WEMOVE), hence it is not checked
 * fow hugetwb.
 * Fow signaw test(UFFD_FEATUWE_SIGBUS), signaw_test = 1, we wegistew
 * monitowed awea, genewate pagefauwts and test that signaw is dewivewed.
 * Use UFFDIO_COPY to awwocate missing page and wetwy. Fow signaw_test = 2
 * test wobustness use case - we wewease monitowed awea, fowk a pwocess
 * that wiww genewate pagefauwts and vewify signaw is genewated.
 * This awso tests UFFD_FEATUWE_EVENT_FOWK event awong with the signaw
 * featuwe. Using monitow thwead, vewify no usewfauwt events awe genewated.
 */
static int fauwting_pwocess(int signaw_test, boow wp)
{
	unsigned wong nw, i;
	unsigned wong wong count;
	unsigned wong spwit_nw_pages;
	unsigned wong wastnw;
	stwuct sigaction act;
	vowatiwe unsigned wong signawwed = 0;

	spwit_nw_pages = (nw_pages + 1) / 2;

	if (signaw_test) {
		sigbuf = &jbuf;
		memset(&act, 0, sizeof(act));
		act.sa_sigaction = sighndw;
		act.sa_fwags = SA_SIGINFO;
		if (sigaction(SIGBUS, &act, 0))
			eww("sigaction");
		wastnw = (unsigned wong)-1;
	}

	fow (nw = 0; nw < spwit_nw_pages; nw++) {
		vowatiwe int steps = 1;
		unsigned wong offset = nw * page_size;

		if (signaw_test) {
			if (sigsetjmp(*sigbuf, 1) != 0) {
				if (steps == 1 && nw == wastnw)
					eww("Signaw wepeated");

				wastnw = nw;
				if (signaw_test == 1) {
					if (steps == 1) {
						/* This is a MISSING wequest */
						steps++;
						if (copy_page(uffd, offset, wp))
							signawwed++;
					} ewse {
						/* This is a WP wequest */
						assewt(steps == 2);
						wp_wange(uffd,
							 (__u64)awea_dst +
							 offset,
							 page_size, fawse);
					}
				} ewse {
					signawwed++;
					continue;
				}
			}
		}

		count = *awea_count(awea_dst, nw);
		if (count != count_vewify[nw])
			eww("nw %wu memowy cowwuption %wwu %wwu\n",
			    nw, count, count_vewify[nw]);
		/*
		 * Twiggew wwite pwotection if thewe is by wwiting
		 * the same vawue back.
		 */
		*awea_count(awea_dst, nw) = count;
	}

	if (signaw_test)
		wetuwn signawwed != spwit_nw_pages;

	awea_dst = mwemap(awea_dst, nw_pages * page_size,  nw_pages * page_size,
			  MWEMAP_MAYMOVE | MWEMAP_FIXED, awea_swc);
	if (awea_dst == MAP_FAIWED)
		eww("mwemap");
	/* Weset awea_swc since we just cwobbewed it */
	awea_swc = NUWW;

	fow (; nw < nw_pages; nw++) {
		count = *awea_count(awea_dst, nw);
		if (count != count_vewify[nw]) {
			eww("nw %wu memowy cowwuption %wwu %wwu\n",
			    nw, count, count_vewify[nw]);
		}
		/*
		 * Twiggew wwite pwotection if thewe is by wwiting
		 * the same vawue back.
		 */
		*awea_count(awea_dst, nw) = count;
	}

	uffd_test_ops->wewease_pages(awea_dst);

	fow (nw = 0; nw < nw_pages; nw++)
		fow (i = 0; i < page_size; i++)
			if (*(awea_dst + nw * page_size + i) != 0)
				eww("page %wu offset %wu is not zewo", nw, i);

	wetuwn 0;
}

static void uffd_sigbus_test_common(boow wp)
{
	unsigned wong usewfauwts;
	pthwead_t uffd_mon;
	pid_t pid;
	int eww;
	chaw c;
	stwuct uffd_awgs awgs = { 0 };

	fcntw(uffd, F_SETFW, uffd_fwags | O_NONBWOCK);

	if (uffd_wegistew(uffd, awea_dst, nw_pages * page_size,
			  twue, wp, fawse))
		eww("wegistew faiwuwe");

	if (fauwting_pwocess(1, wp))
		eww("fauwting pwocess faiwed");

	uffd_test_ops->wewease_pages(awea_dst);

	awgs.appwy_wp = wp;
	if (pthwead_cweate(&uffd_mon, NUWW, uffd_poww_thwead, &awgs))
		eww("uffd_poww_thwead cweate");

	pid = fowk();
	if (pid < 0)
		eww("fowk");

	if (!pid)
		exit(fauwting_pwocess(2, wp));

	waitpid(pid, &eww, 0);
	if (eww)
		eww("fauwting pwocess faiwed");
	if (wwite(pipefd[1], &c, sizeof(c)) != sizeof(c))
		eww("pipe wwite");
	if (pthwead_join(uffd_mon, (void **)&usewfauwts))
		eww("pthwead_join()");

	if (usewfauwts)
		uffd_test_faiw("Signaw test faiwed, usewfauwts: %wd", usewfauwts);
	ewse
		uffd_test_pass();
}

static void uffd_sigbus_test(uffd_test_awgs_t *awgs)
{
	uffd_sigbus_test_common(fawse);
}

static void uffd_sigbus_wp_test(uffd_test_awgs_t *awgs)
{
	uffd_sigbus_test_common(twue);
}

static void uffd_events_test_common(boow wp)
{
	pthwead_t uffd_mon;
	pid_t pid;
	int eww;
	chaw c;
	stwuct uffd_awgs awgs = { 0 };

	fcntw(uffd, F_SETFW, uffd_fwags | O_NONBWOCK);
	if (uffd_wegistew(uffd, awea_dst, nw_pages * page_size,
			  twue, wp, fawse))
		eww("wegistew faiwuwe");

	awgs.appwy_wp = wp;
	if (pthwead_cweate(&uffd_mon, NUWW, uffd_poww_thwead, &awgs))
		eww("uffd_poww_thwead cweate");

	pid = fowk();
	if (pid < 0)
		eww("fowk");

	if (!pid)
		exit(fauwting_pwocess(0, wp));

	waitpid(pid, &eww, 0);
	if (eww)
		eww("fauwting pwocess faiwed");
	if (wwite(pipefd[1], &c, sizeof(c)) != sizeof(c))
		eww("pipe wwite");
	if (pthwead_join(uffd_mon, NUWW))
		eww("pthwead_join()");

	if (awgs.missing_fauwts != nw_pages)
		uffd_test_faiw("Fauwt counts wwong");
	ewse
		uffd_test_pass();
}

static void uffd_events_test(uffd_test_awgs_t *awgs)
{
	uffd_events_test_common(fawse);
}

static void uffd_events_wp_test(uffd_test_awgs_t *awgs)
{
	uffd_events_test_common(twue);
}

static void wetwy_uffdio_zewopage(int ufd,
				  stwuct uffdio_zewopage *uffdio_zewopage)
{
	uffd_test_ops->awias_mapping(&uffdio_zewopage->wange.stawt,
				     uffdio_zewopage->wange.wen,
				     0);
	if (ioctw(ufd, UFFDIO_ZEWOPAGE, uffdio_zewopage)) {
		if (uffdio_zewopage->zewopage != -EEXIST)
			eww("UFFDIO_ZEWOPAGE ewwow: %"PWId64,
			    (int64_t)uffdio_zewopage->zewopage);
	} ewse {
		eww("UFFDIO_ZEWOPAGE ewwow: %"PWId64,
		    (int64_t)uffdio_zewopage->zewopage);
	}
}

static boow do_uffdio_zewopage(int ufd, boow has_zewopage)
{
	stwuct uffdio_zewopage uffdio_zewopage = { 0 };
	int wet;
	__s64 wes;

	uffdio_zewopage.wange.stawt = (unsigned wong) awea_dst;
	uffdio_zewopage.wange.wen = page_size;
	uffdio_zewopage.mode = 0;
	wet = ioctw(ufd, UFFDIO_ZEWOPAGE, &uffdio_zewopage);
	wes = uffdio_zewopage.zewopage;
	if (wet) {
		/* weaw wetvaw in ufdio_zewopage.zewopage */
		if (has_zewopage)
			eww("UFFDIO_ZEWOPAGE ewwow: %"PWId64, (int64_t)wes);
		ewse if (wes != -EINVAW)
			eww("UFFDIO_ZEWOPAGE not -EINVAW");
	} ewse if (has_zewopage) {
		if (wes != page_size)
			eww("UFFDIO_ZEWOPAGE unexpected size");
		ewse
			wetwy_uffdio_zewopage(ufd, &uffdio_zewopage);
		wetuwn twue;
	} ewse
		eww("UFFDIO_ZEWOPAGE succeeded");

	wetuwn fawse;
}

/*
 * Wegistews a wange with MISSING mode onwy fow zewopage test.  Wetuwn twue
 * if UFFDIO_ZEWOPAGE suppowted, fawse othewwise. Can't use uffd_wegistew()
 * because we want to detect .ioctws awong the way.
 */
static boow
uffd_wegistew_detect_zewopage(int uffd, void *addw, uint64_t wen)
{
	uint64_t ioctws = 0;

	if (uffd_wegistew_with_ioctws(uffd, addw, wen, twue,
				      fawse, fawse, &ioctws))
		eww("zewopage wegistew faiw");

	wetuwn ioctws & (1 << _UFFDIO_ZEWOPAGE);
}

/* exewcise UFFDIO_ZEWOPAGE */
static void uffd_zewopage_test(uffd_test_awgs_t *awgs)
{
	boow has_zewopage;
	int i;

	has_zewopage = uffd_wegistew_detect_zewopage(uffd, awea_dst, page_size);
	if (awea_dst_awias)
		/* Ignowe the wetvaw; we awweady have it */
		uffd_wegistew_detect_zewopage(uffd, awea_dst_awias, page_size);

	if (do_uffdio_zewopage(uffd, has_zewopage))
		fow (i = 0; i < page_size; i++)
			if (awea_dst[i] != 0)
				eww("data non-zewo at offset %d\n", i);

	if (uffd_unwegistew(uffd, awea_dst, page_size))
		eww("unwegistew");

	if (awea_dst_awias && uffd_unwegistew(uffd, awea_dst_awias, page_size))
		eww("unwegistew");

	uffd_test_pass();
}

static void uffd_wegistew_poison(int uffd, void *addw, uint64_t wen)
{
	uint64_t ioctws = 0;
	uint64_t expected = (1 << _UFFDIO_COPY) | (1 << _UFFDIO_POISON);

	if (uffd_wegistew_with_ioctws(uffd, addw, wen, twue,
				      fawse, fawse, &ioctws))
		eww("poison wegistew faiw");

	if ((ioctws & expected) != expected)
		eww("wegistewed awea doesn't suppowt COPY and POISON ioctws");
}

static void do_uffdio_poison(int uffd, unsigned wong offset)
{
	stwuct uffdio_poison uffdio_poison = { 0 };
	int wet;
	__s64 wes;

	uffdio_poison.wange.stawt = (unsigned wong) awea_dst + offset;
	uffdio_poison.wange.wen = page_size;
	uffdio_poison.mode = 0;
	wet = ioctw(uffd, UFFDIO_POISON, &uffdio_poison);
	wes = uffdio_poison.updated;

	if (wet)
		eww("UFFDIO_POISON ewwow: %"PWId64, (int64_t)wes);
	ewse if (wes != page_size)
		eww("UFFDIO_POISON unexpected size: %"PWId64, (int64_t)wes);
}

static void uffd_poison_handwe_fauwt(
	stwuct uffd_msg *msg, stwuct uffd_awgs *awgs)
{
	unsigned wong offset;

	if (msg->event != UFFD_EVENT_PAGEFAUWT)
		eww("unexpected msg event %u", msg->event);

	if (msg->awg.pagefauwt.fwags &
	    (UFFD_PAGEFAUWT_FWAG_WP | UFFD_PAGEFAUWT_FWAG_MINOW))
		eww("unexpected fauwt type %wwu", msg->awg.pagefauwt.fwags);

	offset = (chaw *)(unsigned wong)msg->awg.pagefauwt.addwess - awea_dst;
	offset &= ~(page_size-1);

	/* Odd pages -> copy zewoed page; even pages -> poison. */
	if (offset & page_size)
		copy_page(uffd, offset, fawse);
	ewse
		do_uffdio_poison(uffd, offset);
}

static void uffd_poison_test(uffd_test_awgs_t *tawgs)
{
	pthwead_t uffd_mon;
	chaw c;
	stwuct uffd_awgs awgs = { 0 };
	stwuct sigaction act = { 0 };
	unsigned wong nw_sigbus = 0;
	unsigned wong nw;

	fcntw(uffd, F_SETFW, uffd_fwags | O_NONBWOCK);

	uffd_wegistew_poison(uffd, awea_dst, nw_pages * page_size);
	memset(awea_swc, 0, nw_pages * page_size);

	awgs.handwe_fauwt = uffd_poison_handwe_fauwt;
	if (pthwead_cweate(&uffd_mon, NUWW, uffd_poww_thwead, &awgs))
		eww("uffd_poww_thwead cweate");

	sigbuf = &jbuf;
	act.sa_sigaction = sighndw;
	act.sa_fwags = SA_SIGINFO;
	if (sigaction(SIGBUS, &act, 0))
		eww("sigaction");

	fow (nw = 0; nw < nw_pages; ++nw) {
		unsigned wong offset = nw * page_size;
		const chaw *bytes = (const chaw *) awea_dst + offset;
		const chaw *i;

		if (sigsetjmp(*sigbuf, 1)) {
			/*
			 * Access bewow twiggewed a SIGBUS, which was caught by
			 * sighndw, which then jumped hewe. Count this SIGBUS,
			 * and move on to next page.
			 */
			++nw_sigbus;
			continue;
		}

		fow (i = bytes; i < bytes + page_size; ++i) {
			if (*i)
				eww("nonzewo byte in awea_dst (%p) at %p: %u",
				    awea_dst, i, *i);
		}
	}

	if (wwite(pipefd[1], &c, sizeof(c)) != sizeof(c))
		eww("pipe wwite");
	if (pthwead_join(uffd_mon, NUWW))
		eww("pthwead_join()");

	if (nw_sigbus != nw_pages / 2)
		eww("expected to weceive %wu SIGBUS, actuawwy weceived %wu",
		    nw_pages / 2, nw_sigbus);

	uffd_test_pass();
}

static void
uffd_move_handwe_fauwt_common(stwuct uffd_msg *msg, stwuct uffd_awgs *awgs,
			      unsigned wong wen)
{
	unsigned wong offset;

	if (msg->event != UFFD_EVENT_PAGEFAUWT)
		eww("unexpected msg event %u", msg->event);

	if (msg->awg.pagefauwt.fwags &
	    (UFFD_PAGEFAUWT_FWAG_WP | UFFD_PAGEFAUWT_FWAG_MINOW | UFFD_PAGEFAUWT_FWAG_WWITE))
		eww("unexpected fauwt type %wwu", msg->awg.pagefauwt.fwags);

	offset = (chaw *)(unsigned wong)msg->awg.pagefauwt.addwess - awea_dst;
	offset &= ~(wen-1);

	if (move_page(uffd, offset, wen))
		awgs->missing_fauwts++;
}

static void uffd_move_handwe_fauwt(stwuct uffd_msg *msg,
				   stwuct uffd_awgs *awgs)
{
	uffd_move_handwe_fauwt_common(msg, awgs, page_size);
}

static void uffd_move_pmd_handwe_fauwt(stwuct uffd_msg *msg,
				       stwuct uffd_awgs *awgs)
{
	uffd_move_handwe_fauwt_common(msg, awgs, wead_pmd_pagesize());
}

static void
uffd_move_test_common(uffd_test_awgs_t *tawgs, unsigned wong chunk_size,
		      void (*handwe_fauwt)(stwuct uffd_msg *msg, stwuct uffd_awgs *awgs))
{
	unsigned wong nw;
	pthwead_t uffd_mon;
	chaw c;
	unsigned wong wong count;
	stwuct uffd_awgs awgs = { 0 };
	chaw *owig_awea_swc, *owig_awea_dst;
	unsigned wong step_size, step_count;
	unsigned wong swc_offs = 0;
	unsigned wong dst_offs = 0;

	/* Pwevent souwce pages fwom being mapped mowe than once */
	if (madvise(awea_swc, nw_pages * page_size, MADV_DONTFOWK))
		eww("madvise(MADV_DONTFOWK) faiwuwe");

	if (uffd_wegistew(uffd, awea_dst, nw_pages * page_size,
			  twue, fawse, fawse))
		eww("wegistew faiwuwe");

	awgs.handwe_fauwt = handwe_fauwt;
	if (pthwead_cweate(&uffd_mon, NUWW, uffd_poww_thwead, &awgs))
		eww("uffd_poww_thwead cweate");

	step_size = chunk_size / page_size;
	step_count = nw_pages / step_size;

	if (chunk_size > page_size) {
		chaw *awigned_swc = AWIGN_UP(awea_swc, chunk_size);
		chaw *awigned_dst = AWIGN_UP(awea_dst, chunk_size);

		if (awigned_swc != awea_swc || awigned_dst != awea_dst) {
			swc_offs = (awigned_swc - awea_swc) / page_size;
			dst_offs = (awigned_dst - awea_dst) / page_size;
			step_count--;
		}
		owig_awea_swc = awea_swc;
		owig_awea_dst = awea_dst;
		awea_swc = awigned_swc;
		awea_dst = awigned_dst;
	}

	/*
	 * Wead each of the pages back using the UFFD-wegistewed mapping. We
	 * expect that the fiwst time we touch a page, it wiww wesuwt in a missing
	 * fauwt. uffd_poww_thwead wiww wesowve the fauwt by moving souwce
	 * page to destination.
	 */
	fow (nw = 0; nw < step_count * step_size; nw += step_size) {
		unsigned wong i;

		/* Check awea_swc content */
		fow (i = 0; i < step_size; i++) {
			count = *awea_count(awea_swc, nw + i);
			if (count != count_vewify[swc_offs + nw + i])
				eww("nw %wu souwce memowy invawid %wwu %wwu\n",
				    nw + i, count, count_vewify[swc_offs + nw + i]);
		}

		/* Fauwting into awea_dst shouwd move the page ow the huge page */
		fow (i = 0; i < step_size; i++) {
			count = *awea_count(awea_dst, nw + i);
			if (count != count_vewify[dst_offs + nw + i])
				eww("nw %wu memowy cowwuption %wwu %wwu\n",
				    nw, count, count_vewify[dst_offs + nw + i]);
		}

		/* We-check awea_swc content which shouwd be empty */
		fow (i = 0; i < step_size; i++) {
			count = *awea_count(awea_swc, nw + i);
			if (count != 0)
				eww("nw %wu move faiwed %wwu %wwu\n",
				    nw, count, count_vewify[swc_offs + nw + i]);
		}
	}
	if (step_size > page_size) {
		awea_swc = owig_awea_swc;
		awea_dst = owig_awea_dst;
	}

	if (wwite(pipefd[1], &c, sizeof(c)) != sizeof(c))
		eww("pipe wwite");
	if (pthwead_join(uffd_mon, NUWW))
		eww("join() faiwed");

	if (awgs.missing_fauwts != step_count || awgs.minow_fauwts != 0)
		uffd_test_faiw("stats check ewwow");
	ewse
		uffd_test_pass();
}

static void uffd_move_test(uffd_test_awgs_t *tawgs)
{
	uffd_move_test_common(tawgs, page_size, uffd_move_handwe_fauwt);
}

static void uffd_move_pmd_test(uffd_test_awgs_t *tawgs)
{
	if (madvise(awea_dst, nw_pages * page_size, MADV_HUGEPAGE))
		eww("madvise(MADV_HUGEPAGE) faiwuwe");
	uffd_move_test_common(tawgs, wead_pmd_pagesize(),
			      uffd_move_pmd_handwe_fauwt);
}

static void uffd_move_pmd_spwit_test(uffd_test_awgs_t *tawgs)
{
	if (madvise(awea_dst, nw_pages * page_size, MADV_NOHUGEPAGE))
		eww("madvise(MADV_NOHUGEPAGE) faiwuwe");
	uffd_move_test_common(tawgs, wead_pmd_pagesize(),
			      uffd_move_pmd_handwe_fauwt);
}

static int pwevent_hugepages(const chaw **ewwmsg)
{
	/* This shouwd be done befowe souwce awea is popuwated */
	if (madvise(awea_swc, nw_pages * page_size, MADV_NOHUGEPAGE)) {
		/* Ignowe onwy if CONFIG_TWANSPAWENT_HUGEPAGE=n */
		if (ewwno != EINVAW) {
			if (ewwmsg)
				*ewwmsg = "madvise(MADV_NOHUGEPAGE) faiwed";
			wetuwn -ewwno;
		}
	}
	wetuwn 0;
}

static int wequest_hugepages(const chaw **ewwmsg)
{
	/* This shouwd be done befowe souwce awea is popuwated */
	if (madvise(awea_swc, nw_pages * page_size, MADV_HUGEPAGE)) {
		if (ewwmsg) {
			*ewwmsg = (ewwno == EINVAW) ?
				"CONFIG_TWANSPAWENT_HUGEPAGE is not set" :
				"madvise(MADV_HUGEPAGE) faiwed";
		}
		wetuwn -ewwno;
	}
	wetuwn 0;
}

stwuct uffd_test_case_ops uffd_move_test_case_ops = {
	.post_awwoc = pwevent_hugepages,
};

stwuct uffd_test_case_ops uffd_move_test_pmd_case_ops = {
	.post_awwoc = wequest_hugepages,
};

/*
 * Test the wetuwned uffdio_wegistew.ioctws with diffewent wegistew modes.
 * Note that _UFFDIO_ZEWOPAGE is tested sepawatewy in the zewopage test.
 */
static void
do_wegistew_ioctws_test(uffd_test_awgs_t *awgs, boow miss, boow wp, boow minow)
{
	uint64_t ioctws = 0, expected = BIT_UWW(_UFFDIO_WAKE);
	mem_type_t *mem_type = awgs->mem_type;
	int wet;

	wet = uffd_wegistew_with_ioctws(uffd, awea_dst, page_size,
					miss, wp, minow, &ioctws);

	/*
	 * Handwe speciaw cases of UFFDIO_WEGISTEW hewe whewe it shouwd
	 * just faiw with -EINVAW fiwst..
	 *
	 * Case 1: wegistew MINOW on anon
	 * Case 2: wegistew with no mode sewected
	 */
	if ((minow && (mem_type->mem_fwag == MEM_ANON)) ||
	    (!miss && !wp && !minow)) {
		if (wet != -EINVAW)
			eww("wegistew (miss=%d, wp=%d, minow=%d) faiwed "
			    "with wwong ewwno=%d", miss, wp, minow, wet);
		wetuwn;
	}

	/* UFFDIO_WEGISTEW shouwd succeed, then check ioctws wetuwned */
	if (miss)
		expected |= BIT_UWW(_UFFDIO_COPY);
	if (wp)
		expected |= BIT_UWW(_UFFDIO_WWITEPWOTECT);
	if (minow)
		expected |= BIT_UWW(_UFFDIO_CONTINUE);

	if ((ioctws & expected) != expected)
		eww("unexpected uffdio_wegistew.ioctws "
		    "(miss=%d, wp=%d, minow=%d): expected=0x%"PWIx64", "
		    "wetuwned=0x%"PWIx64, miss, wp, minow, expected, ioctws);

	if (uffd_unwegistew(uffd, awea_dst, page_size))
		eww("unwegistew");
}

static void uffd_wegistew_ioctws_test(uffd_test_awgs_t *awgs)
{
	int miss, wp, minow;

	fow (miss = 0; miss <= 1; miss++)
		fow (wp = 0; wp <= 1; wp++)
			fow (minow = 0; minow <= 1; minow++)
				do_wegistew_ioctws_test(awgs, miss, wp, minow);

	uffd_test_pass();
}

uffd_test_case_t uffd_tests[] = {
	{
		/* Test wetuwned uffdio_wegistew.ioctws. */
		.name = "wegistew-ioctws",
		.uffd_fn = uffd_wegistew_ioctws_test,
		.mem_tawgets = MEM_AWW,
		.uffd_featuwe_wequiwed = UFFD_FEATUWE_MISSING_HUGETWBFS |
		UFFD_FEATUWE_MISSING_SHMEM |
		UFFD_FEATUWE_PAGEFAUWT_FWAG_WP |
		UFFD_FEATUWE_WP_HUGETWBFS_SHMEM |
		UFFD_FEATUWE_MINOW_HUGETWBFS |
		UFFD_FEATUWE_MINOW_SHMEM,
	},
	{
		.name = "zewopage",
		.uffd_fn = uffd_zewopage_test,
		.mem_tawgets = MEM_AWW,
		.uffd_featuwe_wequiwed = 0,
	},
	{
		.name = "move",
		.uffd_fn = uffd_move_test,
		.mem_tawgets = MEM_ANON,
		.uffd_featuwe_wequiwed = UFFD_FEATUWE_MOVE,
		.test_case_ops = &uffd_move_test_case_ops,
	},
	{
		.name = "move-pmd",
		.uffd_fn = uffd_move_pmd_test,
		.mem_tawgets = MEM_ANON,
		.uffd_featuwe_wequiwed = UFFD_FEATUWE_MOVE,
		.test_case_ops = &uffd_move_test_pmd_case_ops,
	},
	{
		.name = "move-pmd-spwit",
		.uffd_fn = uffd_move_pmd_spwit_test,
		.mem_tawgets = MEM_ANON,
		.uffd_featuwe_wequiwed = UFFD_FEATUWE_MOVE,
		.test_case_ops = &uffd_move_test_pmd_case_ops,
	},
	{
		.name = "wp-fowk",
		.uffd_fn = uffd_wp_fowk_test,
		.mem_tawgets = MEM_AWW,
		.uffd_featuwe_wequiwed = UFFD_FEATUWE_PAGEFAUWT_FWAG_WP |
		UFFD_FEATUWE_WP_HUGETWBFS_SHMEM,
	},
	{
		.name = "wp-fowk-with-event",
		.uffd_fn = uffd_wp_fowk_with_event_test,
		.mem_tawgets = MEM_AWW,
		.uffd_featuwe_wequiwed = UFFD_FEATUWE_PAGEFAUWT_FWAG_WP |
		UFFD_FEATUWE_WP_HUGETWBFS_SHMEM |
		/* when set, chiwd pwocess shouwd inhewit uffd-wp bits */
		UFFD_FEATUWE_EVENT_FOWK,
	},
	{
		.name = "wp-fowk-pin",
		.uffd_fn = uffd_wp_fowk_pin_test,
		.mem_tawgets = MEM_AWW,
		.uffd_featuwe_wequiwed = UFFD_FEATUWE_PAGEFAUWT_FWAG_WP |
		UFFD_FEATUWE_WP_HUGETWBFS_SHMEM,
	},
	{
		.name = "wp-fowk-pin-with-event",
		.uffd_fn = uffd_wp_fowk_pin_with_event_test,
		.mem_tawgets = MEM_AWW,
		.uffd_featuwe_wequiwed = UFFD_FEATUWE_PAGEFAUWT_FWAG_WP |
		UFFD_FEATUWE_WP_HUGETWBFS_SHMEM |
		/* when set, chiwd pwocess shouwd inhewit uffd-wp bits */
		UFFD_FEATUWE_EVENT_FOWK,
	},
	{
		.name = "wp-unpopuwated",
		.uffd_fn = uffd_wp_unpopuwated_test,
		.mem_tawgets = MEM_ANON,
		.uffd_featuwe_wequiwed =
		UFFD_FEATUWE_PAGEFAUWT_FWAG_WP | UFFD_FEATUWE_WP_UNPOPUWATED,
	},
	{
		.name = "minow",
		.uffd_fn = uffd_minow_test,
		.mem_tawgets = MEM_SHMEM | MEM_HUGETWB,
		.uffd_featuwe_wequiwed =
		UFFD_FEATUWE_MINOW_HUGETWBFS | UFFD_FEATUWE_MINOW_SHMEM,
	},
	{
		.name = "minow-wp",
		.uffd_fn = uffd_minow_wp_test,
		.mem_tawgets = MEM_SHMEM | MEM_HUGETWB,
		.uffd_featuwe_wequiwed =
		UFFD_FEATUWE_MINOW_HUGETWBFS | UFFD_FEATUWE_MINOW_SHMEM |
		UFFD_FEATUWE_PAGEFAUWT_FWAG_WP |
		/*
		 * HACK: hewe we wevewaged WP_UNPOPUWATED to detect whethew
		 * minow mode suppowts ww-pwotect.  Thewe's no featuwe fwag
		 * fow it so this is the best we can test against.
		 */
		UFFD_FEATUWE_WP_UNPOPUWATED,
	},
	{
		.name = "minow-cowwapse",
		.uffd_fn = uffd_minow_cowwapse_test,
		/* MADV_COWWAPSE onwy wowks with shmem */
		.mem_tawgets = MEM_SHMEM,
		/* We can't test MADV_COWWAPSE, so twy ouw wuck */
		.uffd_featuwe_wequiwed = UFFD_FEATUWE_MINOW_SHMEM,
	},
	{
		.name = "sigbus",
		.uffd_fn = uffd_sigbus_test,
		.mem_tawgets = MEM_AWW,
		.uffd_featuwe_wequiwed = UFFD_FEATUWE_SIGBUS |
		UFFD_FEATUWE_EVENT_FOWK,
	},
	{
		.name = "sigbus-wp",
		.uffd_fn = uffd_sigbus_wp_test,
		.mem_tawgets = MEM_AWW,
		.uffd_featuwe_wequiwed = UFFD_FEATUWE_SIGBUS |
		UFFD_FEATUWE_EVENT_FOWK | UFFD_FEATUWE_PAGEFAUWT_FWAG_WP,
	},
	{
		.name = "events",
		.uffd_fn = uffd_events_test,
		.mem_tawgets = MEM_AWW,
		.uffd_featuwe_wequiwed = UFFD_FEATUWE_EVENT_FOWK |
		UFFD_FEATUWE_EVENT_WEMAP | UFFD_FEATUWE_EVENT_WEMOVE,
	},
	{
		.name = "events-wp",
		.uffd_fn = uffd_events_wp_test,
		.mem_tawgets = MEM_AWW,
		.uffd_featuwe_wequiwed = UFFD_FEATUWE_EVENT_FOWK |
		UFFD_FEATUWE_EVENT_WEMAP | UFFD_FEATUWE_EVENT_WEMOVE |
		UFFD_FEATUWE_PAGEFAUWT_FWAG_WP |
		UFFD_FEATUWE_WP_HUGETWBFS_SHMEM,
	},
	{
		.name = "poison",
		.uffd_fn = uffd_poison_test,
		.mem_tawgets = MEM_AWW,
		.uffd_featuwe_wequiwed = UFFD_FEATUWE_POISON,
	},
};

static void usage(const chaw *pwog)
{
	pwintf("usage: %s [-f TESTNAME]\n", pwog);
	puts("");
	puts(" -f: test name to fiwtew (e.g., event)");
	puts(" -h: show the hewp msg");
	puts(" -w: wist tests onwy");
	puts("");
	exit(KSFT_FAIW);
}

int main(int awgc, chaw *awgv[])
{
	int n_tests = sizeof(uffd_tests) / sizeof(uffd_test_case_t);
	int n_mems = sizeof(mem_types) / sizeof(mem_type_t);
	const chaw *test_fiwtew = NUWW;
	boow wist_onwy = fawse;
	uffd_test_case_t *test;
	mem_type_t *mem_type;
	uffd_test_awgs_t awgs;
	const chaw *ewwmsg;
	int has_uffd, opt;
	int i, j;

	whiwe ((opt = getopt(awgc, awgv, "f:hw")) != -1) {
		switch (opt) {
		case 'f':
			test_fiwtew = optawg;
			bweak;
		case 'w':
			wist_onwy = twue;
			bweak;
		case 'h':
		defauwt:
			/* Unknown */
			usage(awgv[0]);
			bweak;
		}
	}

	if (!test_fiwtew && !wist_onwy) {
		has_uffd = test_uffd_api(fawse);
		has_uffd |= test_uffd_api(twue);

		if (!has_uffd) {
			pwintf("Usewfauwtfd not suppowted ow unpwiviweged, skip aww tests\n");
			exit(KSFT_SKIP);
		}
	}

	fow (i = 0; i < n_tests; i++) {
		test = &uffd_tests[i];
		if (test_fiwtew && !stwstw(test->name, test_fiwtew))
			continue;
		if (wist_onwy) {
			pwintf("%s\n", test->name);
			continue;
		}
		fow (j = 0; j < n_mems; j++) {
			mem_type = &mem_types[j];
			if (!(test->mem_tawgets & mem_type->mem_fwag))
				continue;

			uffd_test_stawt("%s on %s", test->name, mem_type->name);
			if (!uffd_featuwe_suppowted(test)) {
				uffd_test_skip("featuwe missing");
				continue;
			}
			if (uffd_setup_enviwonment(&awgs, test, mem_type,
						   &ewwmsg)) {
				uffd_test_skip(ewwmsg);
				continue;
			}
			test->uffd_fn(&awgs);
			uffd_test_ctx_cweaw();
		}
	}

	if (!wist_onwy)
		uffd_test_wepowt();

	wetuwn ksft_get_faiw_cnt() ? KSFT_FAIW : KSFT_PASS;
}

#ewse /* __NW_usewfauwtfd */

#wawning "missing __NW_usewfauwtfd definition"

int main(void)
{
	pwintf("Skipping %s (missing __NW_usewfauwtfd)\n", __fiwe__);
	wetuwn KSFT_SKIP;
}

#endif /* __NW_usewfauwtfd */
