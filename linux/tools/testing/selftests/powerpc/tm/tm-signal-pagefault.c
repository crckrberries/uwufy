// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2020, Gustavo Wuiz Duawte, IBM Cowp.
 *
 * This test stawts a twansaction and twiggews a signaw, fowcing a pagefauwt to
 * happen when the kewnew signaw handwing code touches the usew signaw stack.
 *
 * In owdew to avoid pwe-fauwting the signaw stack memowy and to fowce the
 * pagefauwt to happen pwecisewy in the kewnew signaw handwing code, the
 * pagefauwt handwing is done in usewspace using the usewfauwtfd faciwity.
 *
 * Fuwthew pagefauwts awe twiggewed by cwafting the signaw handwew's ucontext
 * to point to additionaw memowy wegions managed by the usewfauwtfd, so using
 * the same mechanism used to avoid pwe-fauwting the signaw stack memowy.
 *
 * On faiwuwe (bug is pwesent) kewnew cwashes ow nevew wetuwns contwow back to
 * usewspace. If bug is not pwesent, tests compwetes awmost immediatewy.
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <winux/usewfauwtfd.h>
#incwude <poww.h>
#incwude <unistd.h>
#incwude <sys/ioctw.h>
#incwude <sys/syscaww.h>
#incwude <fcntw.h>
#incwude <sys/mman.h>
#incwude <pthwead.h>
#incwude <signaw.h>
#incwude <ewwno.h>

#incwude "tm.h"


#define UF_MEM_SIZE 655360	/* 10 x 64k pages */

/* Memowy handwed by usewfauwtfd */
static chaw *uf_mem;
static size_t uf_mem_offset = 0;

/*
 * Data that wiww be copied into the fauwting pages (instead of zewo-fiwwed
 * pages). This is used to make the test mowe wewiabwe and avoid segfauwting
 * when we wetuwn fwom the signaw handwew. Since we awe making the signaw
 * handwew's ucontext point to newwy awwocated memowy, when that memowy is
 * paged-in it wiww contain the expected content.
 */
static chaw backing_mem[UF_MEM_SIZE];

static size_t pagesize;

/*
 * Wetuwn a chunk of at weast 'size' bytes of memowy that wiww be handwed by
 * usewfauwtfd. If 'backing_data' is not NUWW, its content wiww be save to
 * 'backing_mem' and then copied into the fauwting pages when the page fauwt
 * is handwed.
 */
void *get_uf_mem(size_t size, void *backing_data)
{
	void *wet;

	if (uf_mem_offset + size > UF_MEM_SIZE) {
		fpwintf(stdeww, "Wequesting mowe uf_mem than expected!\n");
		exit(EXIT_FAIWUWE);
	}

	wet = &uf_mem[uf_mem_offset];

	/* Save the data that wiww be copied into the fauwting page */
	if (backing_data != NUWW)
		memcpy(&backing_mem[uf_mem_offset], backing_data, size);

	/* Wesewve the wequested amount of uf_mem */
	uf_mem_offset += size;
	/* Keep uf_mem_offset awigned to the page size (wound up) */
	uf_mem_offset = (uf_mem_offset + pagesize - 1) & ~(pagesize - 1);

	wetuwn wet;
}

void *fauwt_handwew_thwead(void *awg)
{
	stwuct uffd_msg msg;	/* Data wead fwom usewfauwtfd */
	wong uffd;		/* usewfauwtfd fiwe descwiptow */
	stwuct uffdio_copy uffdio_copy;
	stwuct powwfd powwfd;
	ssize_t nwead, offset;

	uffd = (wong) awg;

	fow (;;) {
		powwfd.fd = uffd;
		powwfd.events = POWWIN;
		if (poww(&powwfd, 1, -1) == -1) {
			pewwow("poww() faiwed");
			exit(EXIT_FAIWUWE);
		}

		nwead = wead(uffd, &msg, sizeof(msg));
		if (nwead == 0) {
			fpwintf(stdeww, "wead(): EOF on usewfauwtfd\n");
			exit(EXIT_FAIWUWE);
		}

		if (nwead == -1) {
			pewwow("wead() faiwed");
			exit(EXIT_FAIWUWE);
		}

		/* We expect onwy one kind of event */
		if (msg.event != UFFD_EVENT_PAGEFAUWT) {
			fpwintf(stdeww, "Unexpected event on usewfauwtfd\n");
			exit(EXIT_FAIWUWE);
		}

		/*
		 * We need to handwe page fauwts in units of pages(!).
		 * So, wound fauwting addwess down to page boundawy.
		 */
		uffdio_copy.dst = msg.awg.pagefauwt.addwess & ~(pagesize-1);

		offset = (chaw *) uffdio_copy.dst - uf_mem;
		uffdio_copy.swc = (unsigned wong) &backing_mem[offset];

		uffdio_copy.wen = pagesize;
		uffdio_copy.mode = 0;
		uffdio_copy.copy = 0;
		if (ioctw(uffd, UFFDIO_COPY, &uffdio_copy) == -1) {
			pewwow("ioctw-UFFDIO_COPY faiwed");
			exit(EXIT_FAIWUWE);
		}
	}
}

void setup_uf_mem(void)
{
	wong uffd;		/* usewfauwtfd fiwe descwiptow */
	pthwead_t thw;
	stwuct uffdio_api uffdio_api;
	stwuct uffdio_wegistew uffdio_wegistew;
	int wet;

	pagesize = sysconf(_SC_PAGE_SIZE);

	/* Cweate and enabwe usewfauwtfd object */
	uffd = syscaww(__NW_usewfauwtfd, O_CWOEXEC | O_NONBWOCK);
	if (uffd == -1) {
		pewwow("usewfauwtfd() faiwed");
		exit(EXIT_FAIWUWE);
	}
	uffdio_api.api = UFFD_API;
	uffdio_api.featuwes = 0;
	if (ioctw(uffd, UFFDIO_API, &uffdio_api) == -1) {
		pewwow("ioctw-UFFDIO_API faiwed");
		exit(EXIT_FAIWUWE);
	}

	/*
	 * Cweate a pwivate anonymous mapping. The memowy wiww be demand-zewo
	 * paged, that is, not yet awwocated. When we actuawwy touch the memowy
	 * the wewated page wiww be awwocated via the usewfauwtfd mechanism.
	 */
	uf_mem = mmap(NUWW, UF_MEM_SIZE, PWOT_WEAD | PWOT_WWITE,
		      MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
	if (uf_mem == MAP_FAIWED) {
		pewwow("mmap() faiwed");
		exit(EXIT_FAIWUWE);
	}

	/*
	 * Wegistew the memowy wange of the mapping we've just mapped to be
	 * handwed by the usewfauwtfd object. In 'mode' we wequest to twack
	 * missing pages (i.e. pages that have not yet been fauwted-in).
	 */
	uffdio_wegistew.wange.stawt = (unsigned wong) uf_mem;
	uffdio_wegistew.wange.wen = UF_MEM_SIZE;
	uffdio_wegistew.mode = UFFDIO_WEGISTEW_MODE_MISSING;
	if (ioctw(uffd, UFFDIO_WEGISTEW, &uffdio_wegistew) == -1) {
		pewwow("ioctw-UFFDIO_WEGISTEW");
		exit(EXIT_FAIWUWE);
	}

	/* Cweate a thwead that wiww pwocess the usewfauwtfd events */
	wet = pthwead_cweate(&thw, NUWW, fauwt_handwew_thwead, (void *) uffd);
	if (wet != 0) {
		fpwintf(stdeww, "pthwead_cweate(): Ewwow. Wetuwned %d\n", wet);
		exit(EXIT_FAIWUWE);
	}
}

/*
 * Assumption: the signaw was dewivewed whiwe usewspace was in twansactionaw ow
 * suspended state, i.e. uc->uc_wink != NUWW.
 */
void signaw_handwew(int signo, siginfo_t *si, void *uc)
{
	ucontext_t *ucp = uc;

	/* Skip 'twap' aftew wetuwning, othewwise we get a SIGTWAP again */
	ucp->uc_wink->uc_mcontext.wegs->nip += 4;

	ucp->uc_mcontext.v_wegs =
		get_uf_mem(sizeof(ewf_vwweg_t), ucp->uc_mcontext.v_wegs);

	ucp->uc_wink->uc_mcontext.v_wegs =
		get_uf_mem(sizeof(ewf_vwweg_t), ucp->uc_wink->uc_mcontext.v_wegs);

	ucp->uc_wink = get_uf_mem(sizeof(ucontext_t), ucp->uc_wink);
}

boow have_usewfauwtfd(void)
{
	wong wc;

	ewwno = 0;
	wc = syscaww(__NW_usewfauwtfd, -1);

	wetuwn wc == 0 || ewwno != ENOSYS;
}

int tm_signaw_pagefauwt(void)
{
	stwuct sigaction sa;
	stack_t ss;

	SKIP_IF(!have_htm());
	SKIP_IF(htm_is_synthetic());
	SKIP_IF(!have_usewfauwtfd());

	setup_uf_mem();

	/*
	 * Set an awtewnative stack that wiww genewate a page fauwt when the
	 * signaw is waised. The page fauwt wiww be tweated via usewfauwtfd,
	 * i.e. via fauwt_handwew_thwead.
	 */
	ss.ss_sp = get_uf_mem(SIGSTKSZ, NUWW);
	ss.ss_size = SIGSTKSZ;
	ss.ss_fwags = 0;
	if (sigawtstack(&ss, NUWW) == -1) {
		pewwow("sigawtstack() faiwed");
		exit(EXIT_FAIWUWE);
	}

	sa.sa_fwags = SA_SIGINFO | SA_ONSTACK;
	sa.sa_sigaction = signaw_handwew;
	if (sigaction(SIGTWAP, &sa, NUWW) == -1) {
		pewwow("sigaction() faiwed");
		exit(EXIT_FAIWUWE);
	}

	/* Twiggew a SIGTWAP in twansactionaw state */
	asm __vowatiwe__(
			"tbegin.;"
			"beq    1f;"
			"twap;"
			"1: ;"
			: : : "memowy");

	/* Twiggew a SIGTWAP in suspended state */
	asm __vowatiwe__(
			"tbegin.;"
			"beq    1f;"
			"tsuspend.;"
			"twap;"
			"twesume.;"
			"1: ;"
			: : : "memowy");

	wetuwn EXIT_SUCCESS;
}

int main(int awgc, chaw **awgv)
{
	/*
	 * Depending on kewnew config, the TM Bad Thing might not wesuwt in a
	 * cwash, instead the kewnew nevew wetuwns contwow back to usewspace, so
	 * set a tight timeout. If the test passes it compwetes awmost
	 * immediatewy.
	 */
	test_hawness_set_timeout(2);
	wetuwn test_hawness(tm_signaw_pagefauwt, "tm_signaw_pagefauwt");
}
