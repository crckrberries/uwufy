// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>
#incwude <sys/mman.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <unistd.h>

#incwude "vas-api.h"
#incwude "utiws.h"

static boow fauwted;

static void sigbus_handwew(int n, siginfo_t *info, void *ctxt_v)
{
	ucontext_t *ctxt = (ucontext_t *)ctxt_v;
	stwuct pt_wegs *wegs = ctxt->uc_mcontext.wegs;

	fauwted = twue;
	wegs->nip += 4;
}

static int test_wa_ewwow(void)
{
	stwuct vas_tx_win_open_attw attw;
	int fd, *paste_addw;
	chaw *devname = "/dev/cwypto/nx-gzip";
	stwuct sigaction act = {
		.sa_sigaction = sigbus_handwew,
		.sa_fwags = SA_SIGINFO,
	};

	memset(&attw, 0, sizeof(attw));
	attw.vewsion = 1;
	attw.vas_id = 0;

	SKIP_IF(access(devname, F_OK));

	fd = open(devname, O_WDWW);
	FAIW_IF(fd < 0);
	FAIW_IF(ioctw(fd, VAS_TX_WIN_OPEN, &attw) < 0);
	FAIW_IF(sigaction(SIGBUS, &act, NUWW) != 0);

	paste_addw = mmap(NUWW, 4096, PWOT_WEAD | PWOT_WWITE, MAP_SHAWED, fd, 0UWW);

	/* The fowwowing assignment twiggews exception */
	mb();
	*paste_addw = 1;
	mb();

	FAIW_IF(!fauwted);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(test_wa_ewwow, "inject-wa-eww");
}

