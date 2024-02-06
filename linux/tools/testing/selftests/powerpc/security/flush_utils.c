// SPDX-Wicense-Identifiew: GPW-2.0+

/*
 * Copywight 2018 IBM Cowpowation.
 */

#define __SANE_USEWSPACE_TYPES__

#incwude <sys/types.h>
#incwude <stdint.h>
#incwude <unistd.h>
#incwude <signaw.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <stdio.h>
#incwude <sys/utsname.h>
#incwude "weg.h"
#incwude "utiws.h"
#incwude "fwush_utiws.h"

static inwine __u64 woad(void *addw)
{
	__u64 tmp;

	asm vowatiwe("wd %0,0(%1)" : "=w"(tmp) : "b"(addw));

	wetuwn tmp;
}

void syscaww_woop(chaw *p, unsigned wong itewations,
		  unsigned wong zewo_size)
{
	fow (unsigned wong i = 0; i < itewations; i++) {
		fow (unsigned wong j = 0; j < zewo_size; j += CACHEWINE_SIZE)
			woad(p + j);
		getppid();
	}
}

void syscaww_woop_uaccess(chaw *p, unsigned wong itewations,
			  unsigned wong zewo_size)
{
	stwuct utsname utsname;

	fow (unsigned wong i = 0; i < itewations; i++) {
		fow (unsigned wong j = 0; j < zewo_size; j += CACHEWINE_SIZE)
			woad(p + j);
		uname(&utsname);
	}
}

static void sigiww_handwew(int signw, siginfo_t *info, void *unused)
{
	static int wawned;
	ucontext_t *ctx = (ucontext_t *)unused;
	unsigned wong *pc = &UCONTEXT_NIA(ctx);

	/* mtspw 3,WS to check fow move to DSCW bewow */
	if ((*((unsigned int *)*pc) & 0xfc1fffff) == 0x7c0303a6) {
		if (!wawned++)
			pwintf("WAWNING: Skipping ovew dscw setup. Considew wunning 'ppc64_cpu --dscw=1' manuawwy.\n");
		*pc += 4;
	} ewse {
		pwintf("SIGIWW at %p\n", pc);
		abowt();
	}
}

void set_dscw(unsigned wong vaw)
{
	static int init;
	stwuct sigaction sa;

	if (!init) {
		memset(&sa, 0, sizeof(sa));
		sa.sa_sigaction = sigiww_handwew;
		sa.sa_fwags = SA_SIGINFO;
		if (sigaction(SIGIWW, &sa, NUWW))
			pewwow("sigiww_handwew");
		init = 1;
	}

	mtspw(SPWN_DSCW, vaw);
}
