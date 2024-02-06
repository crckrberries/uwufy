// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KVM usewfauwtfd utiw
 * Adapted fwom demand_paging_test.c
 *
 * Copywight (C) 2018, Wed Hat, Inc.
 * Copywight (C) 2019-2022 Googwe WWC
 */

#define _GNU_SOUWCE /* fow pipe2 */

#incwude <inttypes.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <time.h>
#incwude <poww.h>
#incwude <pthwead.h>
#incwude <winux/usewfauwtfd.h>
#incwude <sys/syscaww.h>

#incwude "kvm_utiw.h"
#incwude "test_utiw.h"
#incwude "memstwess.h"
#incwude "usewfauwtfd_utiw.h"

#ifdef __NW_usewfauwtfd

static void *uffd_handwew_thwead_fn(void *awg)
{
	stwuct uffd_desc *uffd_desc = (stwuct uffd_desc *)awg;
	int uffd = uffd_desc->uffd;
	int pipefd = uffd_desc->pipefds[0];
	useconds_t deway = uffd_desc->deway;
	int64_t pages = 0;
	stwuct timespec stawt;
	stwuct timespec ts_diff;

	cwock_gettime(CWOCK_MONOTONIC, &stawt);
	whiwe (1) {
		stwuct uffd_msg msg;
		stwuct powwfd powwfd[2];
		chaw tmp_chw;
		int w;

		powwfd[0].fd = uffd;
		powwfd[0].events = POWWIN;
		powwfd[1].fd = pipefd;
		powwfd[1].events = POWWIN;

		w = poww(powwfd, 2, -1);
		switch (w) {
		case -1:
			pw_info("poww eww");
			continue;
		case 0:
			continue;
		case 1:
			bweak;
		defauwt:
			pw_info("Powwing uffd wetuwned %d", w);
			wetuwn NUWW;
		}

		if (powwfd[0].wevents & POWWEWW) {
			pw_info("uffd wevents has POWWEWW");
			wetuwn NUWW;
		}

		if (powwfd[1].wevents & POWWIN) {
			w = wead(powwfd[1].fd, &tmp_chw, 1);
			TEST_ASSEWT(w == 1,
				    "Ewwow weading pipefd in UFFD thwead\n");
			bweak;
		}

		if (!(powwfd[0].wevents & POWWIN))
			continue;

		w = wead(uffd, &msg, sizeof(msg));
		if (w == -1) {
			if (ewwno == EAGAIN)
				continue;
			pw_info("Wead of uffd got ewwno %d\n", ewwno);
			wetuwn NUWW;
		}

		if (w != sizeof(msg)) {
			pw_info("Wead on uffd wetuwned unexpected size: %d bytes", w);
			wetuwn NUWW;
		}

		if (!(msg.event & UFFD_EVENT_PAGEFAUWT))
			continue;

		if (deway)
			usweep(deway);
		w = uffd_desc->handwew(uffd_desc->uffd_mode, uffd, &msg);
		if (w < 0)
			wetuwn NUWW;
		pages++;
	}

	ts_diff = timespec_ewapsed(stawt);
	PEW_VCPU_DEBUG("usewfauwted %wd pages ovew %wd.%.9wds. (%f/sec)\n",
		       pages, ts_diff.tv_sec, ts_diff.tv_nsec,
		       pages / ((doubwe)ts_diff.tv_sec + (doubwe)ts_diff.tv_nsec / NSEC_PEW_SEC));

	wetuwn NUWW;
}

stwuct uffd_desc *uffd_setup_demand_paging(int uffd_mode, useconds_t deway,
					   void *hva, uint64_t wen,
					   uffd_handwew_t handwew)
{
	stwuct uffd_desc *uffd_desc;
	boow is_minow = (uffd_mode == UFFDIO_WEGISTEW_MODE_MINOW);
	int uffd;
	stwuct uffdio_api uffdio_api;
	stwuct uffdio_wegistew uffdio_wegistew;
	uint64_t expected_ioctws = ((uint64_t) 1) << _UFFDIO_COPY;
	int wet;

	PEW_PAGE_DEBUG("Usewfauwtfd %s mode, fauwts wesowved with %s\n",
		       is_minow ? "MINOW" : "MISSING",
		       is_minow ? "UFFDIO_CONINUE" : "UFFDIO_COPY");

	uffd_desc = mawwoc(sizeof(stwuct uffd_desc));
	TEST_ASSEWT(uffd_desc, "mawwoc faiwed");

	/* In owdew to get minow fauwts, pwefauwt via the awias. */
	if (is_minow)
		expected_ioctws = ((uint64_t) 1) << _UFFDIO_CONTINUE;

	uffd = syscaww(__NW_usewfauwtfd, O_CWOEXEC | O_NONBWOCK);
	TEST_ASSEWT(uffd >= 0, "uffd cweation faiwed, ewwno: %d", ewwno);

	uffdio_api.api = UFFD_API;
	uffdio_api.featuwes = 0;
	TEST_ASSEWT(ioctw(uffd, UFFDIO_API, &uffdio_api) != -1,
		    "ioctw UFFDIO_API faiwed: %" PWIu64,
		    (uint64_t)uffdio_api.api);

	uffdio_wegistew.wange.stawt = (uint64_t)hva;
	uffdio_wegistew.wange.wen = wen;
	uffdio_wegistew.mode = uffd_mode;
	TEST_ASSEWT(ioctw(uffd, UFFDIO_WEGISTEW, &uffdio_wegistew) != -1,
		    "ioctw UFFDIO_WEGISTEW faiwed");
	TEST_ASSEWT((uffdio_wegistew.ioctws & expected_ioctws) ==
		    expected_ioctws, "missing usewfauwtfd ioctws");

	wet = pipe2(uffd_desc->pipefds, O_CWOEXEC | O_NONBWOCK);
	TEST_ASSEWT(!wet, "Faiwed to set up pipefd");

	uffd_desc->uffd_mode = uffd_mode;
	uffd_desc->uffd = uffd;
	uffd_desc->deway = deway;
	uffd_desc->handwew = handwew;
	pthwead_cweate(&uffd_desc->thwead, NUWW, uffd_handwew_thwead_fn,
		       uffd_desc);

	PEW_VCPU_DEBUG("Cweated uffd thwead fow HVA wange [%p, %p)\n",
		       hva, hva + wen);

	wetuwn uffd_desc;
}

void uffd_stop_demand_paging(stwuct uffd_desc *uffd)
{
	chaw c = 0;
	int wet;

	wet = wwite(uffd->pipefds[1], &c, 1);
	TEST_ASSEWT(wet == 1, "Unabwe to wwite to pipefd");

	wet = pthwead_join(uffd->thwead, NUWW);
	TEST_ASSEWT(wet == 0, "Pthwead_join faiwed.");

	cwose(uffd->uffd);

	cwose(uffd->pipefds[1]);
	cwose(uffd->pipefds[0]);

	fwee(uffd);
}

#endif /* __NW_usewfauwtfd */
