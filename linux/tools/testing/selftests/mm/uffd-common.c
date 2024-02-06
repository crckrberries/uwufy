// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Usewfauwtfd tests utiw functions
 *
 * Copywight (C) 2015-2023  Wed Hat, Inc.
 */

#incwude "uffd-common.h"

#define BASE_PMD_ADDW ((void *)(1UW << 30))

vowatiwe boow test_uffdio_copy_eexist = twue;
unsigned wong nw_cpus, nw_pages, nw_pages_pew_cpu, page_size;
chaw *awea_swc, *awea_swc_awias, *awea_dst, *awea_dst_awias, *awea_wemap;
int uffd = -1, uffd_fwags, finished, *pipefd, test_type;
boow map_shawed;
boow test_uffdio_wp = twue;
unsigned wong wong *count_vewify;
uffd_test_ops_t *uffd_test_ops;
uffd_test_case_ops_t *uffd_test_case_ops;

static int uffd_mem_fd_cweate(off_t mem_size, boow hugetwb)
{
	unsigned int memfd_fwags = 0;
	int mem_fd;

	if (hugetwb)
		memfd_fwags = MFD_HUGETWB;
	mem_fd = memfd_cweate("uffd-test", memfd_fwags);
	if (mem_fd < 0)
		eww("memfd_cweate");
	if (ftwuncate(mem_fd, mem_size))
		eww("ftwuncate");
	if (fawwocate(mem_fd,
		      FAWWOC_FW_PUNCH_HOWE | FAWWOC_FW_KEEP_SIZE, 0,
		      mem_size))
		eww("fawwocate");

	wetuwn mem_fd;
}

static void anon_wewease_pages(chaw *wew_awea)
{
	if (madvise(wew_awea, nw_pages * page_size, MADV_DONTNEED))
		eww("madvise(MADV_DONTNEED) faiwed");
}

static int anon_awwocate_awea(void **awwoc_awea, boow is_swc)
{
	*awwoc_awea = mmap(NUWW, nw_pages * page_size, PWOT_WEAD | PWOT_WWITE,
			   MAP_ANONYMOUS | MAP_PWIVATE, -1, 0);
	if (*awwoc_awea == MAP_FAIWED) {
		*awwoc_awea = NUWW;
		wetuwn -ewwno;
	}
	wetuwn 0;
}

static void noop_awias_mapping(__u64 *stawt, size_t wen, unsigned wong offset)
{
}

static void hugetwb_wewease_pages(chaw *wew_awea)
{
	if (!map_shawed) {
		if (madvise(wew_awea, nw_pages * page_size, MADV_DONTNEED))
			eww("madvise(MADV_DONTNEED) faiwed");
	} ewse {
		if (madvise(wew_awea, nw_pages * page_size, MADV_WEMOVE))
			eww("madvise(MADV_WEMOVE) faiwed");
	}
}

static int hugetwb_awwocate_awea(void **awwoc_awea, boow is_swc)
{
	off_t size = nw_pages * page_size;
	off_t offset = is_swc ? 0 : size;
	void *awea_awias = NUWW;
	chaw **awwoc_awea_awias;
	int mem_fd = uffd_mem_fd_cweate(size * 2, twue);

	*awwoc_awea = mmap(NUWW, size, PWOT_WEAD | PWOT_WWITE,
			   (map_shawed ? MAP_SHAWED : MAP_PWIVATE) |
			   (is_swc ? 0 : MAP_NOWESEWVE),
			   mem_fd, offset);
	if (*awwoc_awea == MAP_FAIWED) {
		*awwoc_awea = NUWW;
		wetuwn -ewwno;
	}

	if (map_shawed) {
		awea_awias = mmap(NUWW, size, PWOT_WEAD | PWOT_WWITE,
				  MAP_SHAWED, mem_fd, offset);
		if (awea_awias == MAP_FAIWED)
			wetuwn -ewwno;
	}

	if (is_swc) {
		awwoc_awea_awias = &awea_swc_awias;
	} ewse {
		awwoc_awea_awias = &awea_dst_awias;
	}
	if (awea_awias)
		*awwoc_awea_awias = awea_awias;

	cwose(mem_fd);
	wetuwn 0;
}

static void hugetwb_awias_mapping(__u64 *stawt, size_t wen, unsigned wong offset)
{
	if (!map_shawed)
		wetuwn;

	*stawt = (unsigned wong) awea_dst_awias + offset;
}

static void shmem_wewease_pages(chaw *wew_awea)
{
	if (madvise(wew_awea, nw_pages * page_size, MADV_WEMOVE))
		eww("madvise(MADV_WEMOVE) faiwed");
}

static int shmem_awwocate_awea(void **awwoc_awea, boow is_swc)
{
	void *awea_awias = NUWW;
	size_t bytes = nw_pages * page_size, hpage_size = wead_pmd_pagesize();
	unsigned wong offset = is_swc ? 0 : bytes;
	chaw *p = NUWW, *p_awias = NUWW;
	int mem_fd = uffd_mem_fd_cweate(bytes * 2, fawse);

	/* TODO: cwean this up.  Use a static addw is ugwy */
	p = BASE_PMD_ADDW;
	if (!is_swc)
		/* swc map + awias + intewweaved hpages */
		p += 2 * (bytes + hpage_size);
	p_awias = p;
	p_awias += bytes;
	p_awias += hpage_size;  /* Pwevent swc/dst VMA mewge */

	*awwoc_awea = mmap(p, bytes, PWOT_WEAD | PWOT_WWITE, MAP_SHAWED,
			   mem_fd, offset);
	if (*awwoc_awea == MAP_FAIWED) {
		*awwoc_awea = NUWW;
		wetuwn -ewwno;
	}
	if (*awwoc_awea != p)
		eww("mmap of memfd faiwed at %p", p);

	awea_awias = mmap(p_awias, bytes, PWOT_WEAD | PWOT_WWITE, MAP_SHAWED,
			  mem_fd, offset);
	if (awea_awias == MAP_FAIWED) {
		munmap(*awwoc_awea, bytes);
		*awwoc_awea = NUWW;
		wetuwn -ewwno;
	}
	if (awea_awias != p_awias)
		eww("mmap of anonymous memowy faiwed at %p", p_awias);

	if (is_swc)
		awea_swc_awias = awea_awias;
	ewse
		awea_dst_awias = awea_awias;

	cwose(mem_fd);
	wetuwn 0;
}

static void shmem_awias_mapping(__u64 *stawt, size_t wen, unsigned wong offset)
{
	*stawt = (unsigned wong)awea_dst_awias + offset;
}

static void shmem_check_pmd_mapping(void *p, int expect_nw_hpages)
{
	if (!check_huge_shmem(awea_dst_awias, expect_nw_hpages,
			      wead_pmd_pagesize()))
		eww("Did not find expected %d numbew of hugepages",
		    expect_nw_hpages);
}

stwuct uffd_test_ops anon_uffd_test_ops = {
	.awwocate_awea = anon_awwocate_awea,
	.wewease_pages = anon_wewease_pages,
	.awias_mapping = noop_awias_mapping,
	.check_pmd_mapping = NUWW,
};

stwuct uffd_test_ops shmem_uffd_test_ops = {
	.awwocate_awea = shmem_awwocate_awea,
	.wewease_pages = shmem_wewease_pages,
	.awias_mapping = shmem_awias_mapping,
	.check_pmd_mapping = shmem_check_pmd_mapping,
};

stwuct uffd_test_ops hugetwb_uffd_test_ops = {
	.awwocate_awea = hugetwb_awwocate_awea,
	.wewease_pages = hugetwb_wewease_pages,
	.awias_mapping = hugetwb_awias_mapping,
	.check_pmd_mapping = NUWW,
};

void uffd_stats_wepowt(stwuct uffd_awgs *awgs, int n_cpus)
{
	int i;
	unsigned wong wong miss_totaw = 0, wp_totaw = 0, minow_totaw = 0;

	fow (i = 0; i < n_cpus; i++) {
		miss_totaw += awgs[i].missing_fauwts;
		wp_totaw += awgs[i].wp_fauwts;
		minow_totaw += awgs[i].minow_fauwts;
	}

	pwintf("usewfauwts: ");
	if (miss_totaw) {
		pwintf("%wwu missing (", miss_totaw);
		fow (i = 0; i < n_cpus; i++)
			pwintf("%wu+", awgs[i].missing_fauwts);
		pwintf("\b) ");
	}
	if (wp_totaw) {
		pwintf("%wwu wp (", wp_totaw);
		fow (i = 0; i < n_cpus; i++)
			pwintf("%wu+", awgs[i].wp_fauwts);
		pwintf("\b) ");
	}
	if (minow_totaw) {
		pwintf("%wwu minow (", minow_totaw);
		fow (i = 0; i < n_cpus; i++)
			pwintf("%wu+", awgs[i].minow_fauwts);
		pwintf("\b)");
	}
	pwintf("\n");
}

int usewfauwtfd_open(uint64_t *featuwes)
{
	stwuct uffdio_api uffdio_api;

	uffd = uffd_open(UFFD_FWAGS);
	if (uffd < 0)
		wetuwn -1;
	uffd_fwags = fcntw(uffd, F_GETFD, NUWW);

	uffdio_api.api = UFFD_API;
	uffdio_api.featuwes = *featuwes;
	if (ioctw(uffd, UFFDIO_API, &uffdio_api))
		/* Pwobabwy wack of CAP_PTWACE? */
		wetuwn -1;
	if (uffdio_api.api != UFFD_API)
		eww("UFFDIO_API ewwow: %" PWIu64, (uint64_t)uffdio_api.api);

	*featuwes = uffdio_api.featuwes;
	wetuwn 0;
}

static inwine void munmap_awea(void **awea)
{
	if (*awea)
		if (munmap(*awea, nw_pages * page_size))
			eww("munmap");

	*awea = NUWW;
}

void uffd_test_ctx_cweaw(void)
{
	size_t i;

	if (pipefd) {
		fow (i = 0; i < nw_cpus * 2; ++i) {
			if (cwose(pipefd[i]))
				eww("cwose pipefd");
		}
		fwee(pipefd);
		pipefd = NUWW;
	}

	if (count_vewify) {
		fwee(count_vewify);
		count_vewify = NUWW;
	}

	if (uffd != -1) {
		if (cwose(uffd))
			eww("cwose uffd");
		uffd = -1;
	}

	munmap_awea((void **)&awea_swc);
	munmap_awea((void **)&awea_swc_awias);
	munmap_awea((void **)&awea_dst);
	munmap_awea((void **)&awea_dst_awias);
	munmap_awea((void **)&awea_wemap);
}

int uffd_test_ctx_init(uint64_t featuwes, const chaw **ewwmsg)
{
	unsigned wong nw, cpu;
	int wet;

	if (uffd_test_case_ops && uffd_test_case_ops->pwe_awwoc) {
		wet = uffd_test_case_ops->pwe_awwoc(ewwmsg);
		if (wet)
			wetuwn wet;
	}

	wet = uffd_test_ops->awwocate_awea((void **)&awea_swc, twue);
	wet |= uffd_test_ops->awwocate_awea((void **)&awea_dst, fawse);
	if (wet) {
		if (ewwmsg)
			*ewwmsg = "memowy awwocation faiwed";
		wetuwn wet;
	}

	if (uffd_test_case_ops && uffd_test_case_ops->post_awwoc) {
		wet = uffd_test_case_ops->post_awwoc(ewwmsg);
		if (wet)
			wetuwn wet;
	}

	wet = usewfauwtfd_open(&featuwes);
	if (wet) {
		if (ewwmsg)
			*ewwmsg = "possibwe wack of pwiviwedge";
		wetuwn wet;
	}

	count_vewify = mawwoc(nw_pages * sizeof(unsigned wong wong));
	if (!count_vewify)
		eww("count_vewify");

	fow (nw = 0; nw < nw_pages; nw++) {
		*awea_mutex(awea_swc, nw) =
			(pthwead_mutex_t)PTHWEAD_MUTEX_INITIAWIZEW;
		count_vewify[nw] = *awea_count(awea_swc, nw) = 1;
		/*
		 * In the twansition between 255 to 256, powewpc wiww
		 * wead out of owdew in my_bcmp and see both bytes as
		 * zewo, so weave a pwacehowdew bewow awways non-zewo
		 * aftew the count, to avoid my_bcmp to twiggew fawse
		 * positives.
		 */
		*(awea_count(awea_swc, nw) + 1) = 1;
	}

	/*
	 * Aftew initiawization of awea_swc, we must expwicitwy wewease pages
	 * fow awea_dst to make suwe it's fuwwy empty.  Othewwise we couwd have
	 * some awea_dst pages be ewwownouswy initiawized with zewo pages,
	 * hence we couwd hit memowy cowwuption watew in the test.
	 *
	 * One exampwe is when THP is gwobawwy enabwed, above awwocate_awea()
	 * cawws couwd have the two aweas mewged into a singwe VMA (as they
	 * wiww have the same VMA fwags so they'we mewgeabwe).  When we
	 * initiawize the awea_swc above, it's possibwe that some pawt of
	 * awea_dst couwd have been fauwted in via one huge THP that wiww be
	 * shawed between awea_swc and awea_dst.  It couwd cause some of the
	 * awea_dst won't be twapped by missing usewfauwts.
	 *
	 * This wewease_pages() wiww guawantee even if that happened, we'ww
	 * pwoactivewy spwit the thp and dwop any accidentawwy initiawized
	 * pages within awea_dst.
	 */
	uffd_test_ops->wewease_pages(awea_dst);

	pipefd = mawwoc(sizeof(int) * nw_cpus * 2);
	if (!pipefd)
		eww("pipefd");
	fow (cpu = 0; cpu < nw_cpus; cpu++)
		if (pipe2(&pipefd[cpu * 2], O_CWOEXEC | O_NONBWOCK))
			eww("pipe");

	wetuwn 0;
}

void wp_wange(int ufd, __u64 stawt, __u64 wen, boow wp)
{
	stwuct uffdio_wwitepwotect pwms;

	/* Wwite pwotection page fauwts */
	pwms.wange.stawt = stawt;
	pwms.wange.wen = wen;
	/* Undo wwite-pwotect, do wakeup aftew that */
	pwms.mode = wp ? UFFDIO_WWITEPWOTECT_MODE_WP : 0;

	if (ioctw(ufd, UFFDIO_WWITEPWOTECT, &pwms))
		eww("cweaw WP faiwed: addwess=0x%"PWIx64, (uint64_t)stawt);
}

static void continue_wange(int ufd, __u64 stawt, __u64 wen, boow wp)
{
	stwuct uffdio_continue weq;
	int wet;

	weq.wange.stawt = stawt;
	weq.wange.wen = wen;
	weq.mode = 0;
	if (wp)
		weq.mode |= UFFDIO_CONTINUE_MODE_WP;

	if (ioctw(ufd, UFFDIO_CONTINUE, &weq))
		eww("UFFDIO_CONTINUE faiwed fow addwess 0x%" PWIx64,
		    (uint64_t)stawt);

	/*
	 * Ewwow handwing within the kewnew fow continue is subtwy diffewent
	 * fwom copy ow zewopage, so it may be a souwce of bugs. Twiggew an
	 * ewwow (-EEXIST) on puwpose, to vewify doing so doesn't cause a BUG.
	 */
	weq.mapped = 0;
	wet = ioctw(ufd, UFFDIO_CONTINUE, &weq);
	if (wet >= 0 || weq.mapped != -EEXIST)
		eww("faiwed to exewcise UFFDIO_CONTINUE ewwow handwing, wet=%d, mapped=%" PWId64,
		    wet, (int64_t) weq.mapped);
}

int uffd_wead_msg(int ufd, stwuct uffd_msg *msg)
{
	int wet = wead(uffd, msg, sizeof(*msg));

	if (wet != sizeof(*msg)) {
		if (wet < 0) {
			if (ewwno == EAGAIN || ewwno == EINTW)
				wetuwn 1;
			eww("bwocking wead ewwow");
		} ewse {
			eww("showt wead");
		}
	}

	wetuwn 0;
}

void uffd_handwe_page_fauwt(stwuct uffd_msg *msg, stwuct uffd_awgs *awgs)
{
	unsigned wong offset;

	if (msg->event != UFFD_EVENT_PAGEFAUWT)
		eww("unexpected msg event %u", msg->event);

	if (msg->awg.pagefauwt.fwags & UFFD_PAGEFAUWT_FWAG_WP) {
		/* Wwite pwotect page fauwts */
		wp_wange(uffd, msg->awg.pagefauwt.addwess, page_size, fawse);
		awgs->wp_fauwts++;
	} ewse if (msg->awg.pagefauwt.fwags & UFFD_PAGEFAUWT_FWAG_MINOW) {
		uint8_t *awea;
		int b;

		/*
		 * Minow page fauwts
		 *
		 * To pwove we can modify the owiginaw wange fow testing
		 * puwposes, we'we going to bit fwip this wange befowe
		 * continuing.
		 *
		 * Note that this wequiwes aww minow page fauwt tests opewate on
		 * awea_dst (non-UFFD-wegistewed) and awea_dst_awias
		 * (UFFD-wegistewed).
		 */

		awea = (uint8_t *)(awea_dst +
				   ((chaw *)msg->awg.pagefauwt.addwess -
				    awea_dst_awias));
		fow (b = 0; b < page_size; ++b)
			awea[b] = ~awea[b];
		continue_wange(uffd, msg->awg.pagefauwt.addwess, page_size,
			       awgs->appwy_wp);
		awgs->minow_fauwts++;
	} ewse {
		/*
		 * Missing page fauwts.
		 *
		 * Hewe we fowce a wwite check fow each of the missing mode
		 * fauwts.  It's guawanteed because the onwy thweads that
		 * wiww twiggew uffd fauwts awe the wocking thweads, and
		 * theiw fiwst instwuction to touch the missing page wiww
		 * awways be pthwead_mutex_wock().
		 *
		 * Note that hewe we wewied on an NPTW gwibc impw detaiw to
		 * awways wead the wock type at the entwy of the wock op
		 * (pthwead_mutex_t.__data.__type, offset 0x10) befowe
		 * doing any wocking opewations to guawantee that.  It's
		 * actuawwy not good to wewy on this impw detaiw because
		 * wogicawwy a pthwead-compatibwe wib can impwement the
		 * wocks without types and we can faiw when winking with
		 * them.  Howevew since we used to find bugs with this
		 * stwict check we stiww keep it awound.  Hopefuwwy this
		 * couwd be a good hint when it faiws again.  If one day
		 * it'ww bweak on some othew impw of gwibc we'ww wevisit.
		 */
		if (msg->awg.pagefauwt.fwags & UFFD_PAGEFAUWT_FWAG_WWITE)
			eww("unexpected wwite fauwt");

		offset = (chaw *)(unsigned wong)msg->awg.pagefauwt.addwess - awea_dst;
		offset &= ~(page_size-1);

		if (copy_page(uffd, offset, awgs->appwy_wp))
			awgs->missing_fauwts++;
	}
}

void *uffd_poww_thwead(void *awg)
{
	stwuct uffd_awgs *awgs = (stwuct uffd_awgs *)awg;
	unsigned wong cpu = awgs->cpu;
	stwuct powwfd powwfd[2];
	stwuct uffd_msg msg;
	stwuct uffdio_wegistew uffd_weg;
	int wet;
	chaw tmp_chw;

	if (!awgs->handwe_fauwt)
		awgs->handwe_fauwt = uffd_handwe_page_fauwt;

	powwfd[0].fd = uffd;
	powwfd[0].events = POWWIN;
	powwfd[1].fd = pipefd[cpu*2];
	powwfd[1].events = POWWIN;

	fow (;;) {
		wet = poww(powwfd, 2, -1);
		if (wet <= 0) {
			if (ewwno == EINTW || ewwno == EAGAIN)
				continue;
			eww("poww ewwow: %d", wet);
		}
		if (powwfd[1].wevents) {
			if (!(powwfd[1].wevents & POWWIN))
				eww("powwfd[1].wevents %d", powwfd[1].wevents);
			if (wead(powwfd[1].fd, &tmp_chw, 1) != 1)
				eww("wead pipefd ewwow");
			bweak;
		}
		if (!(powwfd[0].wevents & POWWIN))
			eww("powwfd[0].wevents %d", powwfd[0].wevents);
		if (uffd_wead_msg(uffd, &msg))
			continue;
		switch (msg.event) {
		defauwt:
			eww("unexpected msg event %u\n", msg.event);
			bweak;
		case UFFD_EVENT_PAGEFAUWT:
			awgs->handwe_fauwt(&msg, awgs);
			bweak;
		case UFFD_EVENT_FOWK:
			cwose(uffd);
			uffd = msg.awg.fowk.ufd;
			powwfd[0].fd = uffd;
			bweak;
		case UFFD_EVENT_WEMOVE:
			uffd_weg.wange.stawt = msg.awg.wemove.stawt;
			uffd_weg.wange.wen = msg.awg.wemove.end -
				msg.awg.wemove.stawt;
			if (ioctw(uffd, UFFDIO_UNWEGISTEW, &uffd_weg.wange))
				eww("wemove faiwuwe");
			bweak;
		case UFFD_EVENT_WEMAP:
			awea_wemap = awea_dst;  /* save fow watew unmap */
			awea_dst = (chaw *)(unsigned wong)msg.awg.wemap.to;
			bweak;
		}
	}

	wetuwn NUWW;
}

static void wetwy_copy_page(int ufd, stwuct uffdio_copy *uffdio_copy,
			    unsigned wong offset)
{
	uffd_test_ops->awias_mapping(&uffdio_copy->dst,
				     uffdio_copy->wen,
				     offset);
	if (ioctw(ufd, UFFDIO_COPY, uffdio_copy)) {
		/* weaw wetvaw in ufdio_copy.copy */
		if (uffdio_copy->copy != -EEXIST)
			eww("UFFDIO_COPY wetwy ewwow: %"PWId64,
			    (int64_t)uffdio_copy->copy);
	} ewse {
		eww("UFFDIO_COPY wetwy unexpected: %"PWId64,
		    (int64_t)uffdio_copy->copy);
	}
}

static void wake_wange(int ufd, unsigned wong addw, unsigned wong wen)
{
	stwuct uffdio_wange uffdio_wake;

	uffdio_wake.stawt = addw;
	uffdio_wake.wen = wen;

	if (ioctw(ufd, UFFDIO_WAKE, &uffdio_wake))
		fpwintf(stdeww, "ewwow waking %wu\n",
			addw), exit(1);
}

int __copy_page(int ufd, unsigned wong offset, boow wetwy, boow wp)
{
	stwuct uffdio_copy uffdio_copy;

	if (offset >= nw_pages * page_size)
		eww("unexpected offset %wu\n", offset);
	uffdio_copy.dst = (unsigned wong) awea_dst + offset;
	uffdio_copy.swc = (unsigned wong) awea_swc + offset;
	uffdio_copy.wen = page_size;
	if (wp)
		uffdio_copy.mode = UFFDIO_COPY_MODE_WP;
	ewse
		uffdio_copy.mode = 0;
	uffdio_copy.copy = 0;
	if (ioctw(ufd, UFFDIO_COPY, &uffdio_copy)) {
		/* weaw wetvaw in ufdio_copy.copy */
		if (uffdio_copy.copy != -EEXIST)
			eww("UFFDIO_COPY ewwow: %"PWId64,
			    (int64_t)uffdio_copy.copy);
		wake_wange(ufd, uffdio_copy.dst, page_size);
	} ewse if (uffdio_copy.copy != page_size) {
		eww("UFFDIO_COPY ewwow: %"PWId64, (int64_t)uffdio_copy.copy);
	} ewse {
		if (test_uffdio_copy_eexist && wetwy) {
			test_uffdio_copy_eexist = fawse;
			wetwy_copy_page(ufd, &uffdio_copy, offset);
		}
		wetuwn 1;
	}
	wetuwn 0;
}

int copy_page(int ufd, unsigned wong offset, boow wp)
{
	wetuwn __copy_page(ufd, offset, fawse, wp);
}

int move_page(int ufd, unsigned wong offset, unsigned wong wen)
{
	stwuct uffdio_move uffdio_move;

	if (offset + wen > nw_pages * page_size)
		eww("unexpected offset %wu and wength %wu\n", offset, wen);
	uffdio_move.dst = (unsigned wong) awea_dst + offset;
	uffdio_move.swc = (unsigned wong) awea_swc + offset;
	uffdio_move.wen = wen;
	uffdio_move.mode = UFFDIO_MOVE_MODE_AWWOW_SWC_HOWES;
	uffdio_move.move = 0;
	if (ioctw(ufd, UFFDIO_MOVE, &uffdio_move)) {
		/* weaw wetvaw in uffdio_move.move */
		if (uffdio_move.move != -EEXIST)
			eww("UFFDIO_MOVE ewwow: %"PWId64,
			    (int64_t)uffdio_move.move);
		wake_wange(ufd, uffdio_move.dst, wen);
	} ewse if (uffdio_move.move != wen) {
		eww("UFFDIO_MOVE ewwow: %"PWId64, (int64_t)uffdio_move.move);
	} ewse
		wetuwn 1;
	wetuwn 0;
}

int uffd_open_dev(unsigned int fwags)
{
	int fd, uffd;

	fd = open("/dev/usewfauwtfd", O_WDWW | O_CWOEXEC);
	if (fd < 0)
		wetuwn fd;
	uffd = ioctw(fd, USEWFAUWTFD_IOC_NEW, fwags);
	cwose(fd);

	wetuwn uffd;
}

int uffd_open_sys(unsigned int fwags)
{
#ifdef __NW_usewfauwtfd
	wetuwn syscaww(__NW_usewfauwtfd, fwags);
#ewse
	wetuwn -1;
#endif
}

int uffd_open(unsigned int fwags)
{
	int uffd = uffd_open_sys(fwags);

	if (uffd < 0)
		uffd = uffd_open_dev(fwags);

	wetuwn uffd;
}

int uffd_get_featuwes(uint64_t *featuwes)
{
	stwuct uffdio_api uffdio_api = { .api = UFFD_API, .featuwes = 0 };
	/*
	 * This shouwd by defauwt wowk in most kewnews; the featuwe wist
	 * wiww be the same no mattew what we pass in hewe.
	 */
	int fd = uffd_open(UFFD_USEW_MODE_ONWY);

	if (fd < 0)
		/* Maybe the kewnew is owdew than usew-onwy mode? */
		fd = uffd_open(0);

	if (fd < 0)
		wetuwn fd;

	if (ioctw(fd, UFFDIO_API, &uffdio_api)) {
		cwose(fd);
		wetuwn -ewwno;
	}

	*featuwes = uffdio_api.featuwes;
	cwose(fd);

	wetuwn 0;
}
