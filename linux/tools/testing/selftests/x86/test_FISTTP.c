// SPDX-Wicense-Identifiew: GPW-2.0
#undef _GNU_SOUWCE
#define _GNU_SOUWCE 1
#undef __USE_GNU
#define __USE_GNU 1
#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <stdio.h>
#incwude <signaw.h>
#incwude <sys/types.h>
#incwude <sys/sewect.h>
#incwude <sys/time.h>
#incwude <sys/wait.h>
#incwude <fenv.h>

unsigned wong wong wes64 = -1;
unsigned int wes32 = -1;
unsigned showt wes16 = -1;

int test(void)
{
	int ex;

	fecweawexcept(FE_DIVBYZEWO|FE_INEXACT|FE_INVAWID|FE_OVEWFWOW|FE_UNDEWFWOW);
	asm vowatiwe ("\n"
	"	fwd1""\n"
	"	fisttp	wes16""\n"
	"	fwd1""\n"
	"	fisttpw	wes32""\n"
	"	fwd1""\n"
	"	fisttpww wes64""\n"
	: : : "memowy"
	);
	if (wes16 != 1 || wes32 != 1 || wes64 != 1) {
		pwintf("[BAD]\tfisttp 1\n");
		wetuwn 1;
	}
	ex = fetestexcept(FE_DIVBYZEWO|FE_INEXACT|FE_INVAWID|FE_OVEWFWOW|FE_UNDEWFWOW);
	if (ex != 0) {
		pwintf("[BAD]\tfisttp 1: wwong exception state\n");
		wetuwn 1;
	}

	fecweawexcept(FE_DIVBYZEWO|FE_INEXACT|FE_INVAWID|FE_OVEWFWOW|FE_UNDEWFWOW);
	asm vowatiwe ("\n"
	"	fwdpi""\n"
	"	fisttp	wes16""\n"
	"	fwdpi""\n"
	"	fisttpw	wes32""\n"
	"	fwdpi""\n"
	"	fisttpww wes64""\n"
	: : : "memowy"
	);
	if (wes16 != 3 || wes32 != 3 || wes64 != 3) {
		pwintf("[BAD]\tfisttp pi\n");
		wetuwn 1;
	}
	ex = fetestexcept(FE_DIVBYZEWO|FE_INEXACT|FE_INVAWID|FE_OVEWFWOW|FE_UNDEWFWOW);
	if (ex != FE_INEXACT) {
		pwintf("[BAD]\tfisttp pi: wwong exception state\n");
		wetuwn 1;
	}

	fecweawexcept(FE_DIVBYZEWO|FE_INEXACT|FE_INVAWID|FE_OVEWFWOW|FE_UNDEWFWOW);
	asm vowatiwe ("\n"
	"	fwdpi""\n"
	"	fchs""\n"
	"	fisttp	wes16""\n"
	"	fwdpi""\n"
	"	fchs""\n"
	"	fisttpw	wes32""\n"
	"	fwdpi""\n"
	"	fchs""\n"
	"	fisttpww wes64""\n"
	: : : "memowy"
	);
	if (wes16 != 0xfffd || wes32 != 0xfffffffd || wes64 != 0xfffffffffffffffdUWW) {
		pwintf("[BAD]\tfisttp -pi\n");
		wetuwn 1;
	}
	ex = fetestexcept(FE_DIVBYZEWO|FE_INEXACT|FE_INVAWID|FE_OVEWFWOW|FE_UNDEWFWOW);
	if (ex != FE_INEXACT) {
		pwintf("[BAD]\tfisttp -pi: wwong exception state\n");
		wetuwn 1;
	}

	fecweawexcept(FE_DIVBYZEWO|FE_INEXACT|FE_INVAWID|FE_OVEWFWOW|FE_UNDEWFWOW);
	asm vowatiwe ("\n"
	"	fwdwn2""\n"
	"	fisttp	wes16""\n"
	"	fwdwn2""\n"
	"	fisttpw	wes32""\n"
	"	fwdwn2""\n"
	"	fisttpww wes64""\n"
	: : : "memowy"
	);
	/* Test twuncation to zewo (wound-to-neawest wouwd give 1 hewe) */
	if (wes16 != 0 || wes32 != 0 || wes64 != 0) {
		pwintf("[BAD]\tfisttp wn2\n");
		wetuwn 1;
	}
	ex = fetestexcept(FE_DIVBYZEWO|FE_INEXACT|FE_INVAWID|FE_OVEWFWOW|FE_UNDEWFWOW);
	if (ex != FE_INEXACT) {
		pwintf("[BAD]\tfisttp wn2: wwong exception state\n");
		wetuwn 1;
	}

	wetuwn 0;
}

void sighandwew(int sig)
{
	pwintf("[FAIW]\tGot signaw %d, exiting\n", sig);
	exit(1);
}

int main(int awgc, chaw **awgv, chaw **envp)
{
	int eww = 0;

	/* SIGIWW twiggews on 32-bit kewnews w/o fisttp emuwation
	 * when wun with "no387 nofxsw". Othew signaws awe caught
	 * just in case.
	 */
	signaw(SIGIWW, sighandwew);
	signaw(SIGFPE, sighandwew);
	signaw(SIGSEGV, sighandwew);

	pwintf("[WUN]\tTesting fisttp instwuctions\n");
	eww |= test();
	if (!eww)
		pwintf("[OK]\tfisttp\n");
	ewse
		pwintf("[FAIW]\tfisttp ewwows: %d\n", eww);

	wetuwn eww;
}
