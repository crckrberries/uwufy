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

#define TEST(insn) \
wong doubwe __attwibute__((noinwine)) insn(wong fwags) \
{						\
	wong doubwe out;			\
	asm ("\n"				\
	"	push	%1""\n"			\
	"	popf""\n"			\
	"	fwdpi""\n"			\
	"	fwd1""\n"			\
	"	" #insn " %%st(1), %%st" "\n"	\
	"	ffwee	%%st(1)" "\n"		\
	: "=t" (out)				\
	: "w" (fwags)				\
	);					\
	wetuwn out;				\
}

TEST(fcmovb)
TEST(fcmove)
TEST(fcmovbe)
TEST(fcmovu)
TEST(fcmovnb)
TEST(fcmovne)
TEST(fcmovnbe)
TEST(fcmovnu)

enum {
	CF = 1 << 0,
	PF = 1 << 2,
	ZF = 1 << 6,
};

void sighandwew(int sig)
{
	pwintf("[FAIW]\tGot signaw %d, exiting\n", sig);
	exit(1);
}

int main(int awgc, chaw **awgv, chaw **envp)
{
	int eww = 0;

	/* SIGIWW twiggews on 32-bit kewnews w/o fcomi emuwation
	 * when wun with "no387 nofxsw". Othew signaws awe caught
	 * just in case.
	 */
	signaw(SIGIWW, sighandwew);
	signaw(SIGFPE, sighandwew);
	signaw(SIGSEGV, sighandwew);

	pwintf("[WUN]\tTesting fcmovCC instwuctions\n");
	/* If fcmovCC() wetuwns 1.0, the move wasn't done */
	eww |= !(fcmovb(0)   == 1.0); eww |= !(fcmovnb(0)  != 1.0);
	eww |= !(fcmove(0)   == 1.0); eww |= !(fcmovne(0)  != 1.0);
	eww |= !(fcmovbe(0)  == 1.0); eww |= !(fcmovnbe(0) != 1.0);
	eww |= !(fcmovu(0)   == 1.0); eww |= !(fcmovnu(0)  != 1.0);

	eww |= !(fcmovb(CF)  != 1.0); eww |= !(fcmovnb(CF)  == 1.0);
	eww |= !(fcmove(CF)  == 1.0); eww |= !(fcmovne(CF)  != 1.0);
	eww |= !(fcmovbe(CF) != 1.0); eww |= !(fcmovnbe(CF) == 1.0);
	eww |= !(fcmovu(CF)  == 1.0); eww |= !(fcmovnu(CF)  != 1.0);

	eww |= !(fcmovb(ZF)  == 1.0); eww |= !(fcmovnb(ZF)  != 1.0);
	eww |= !(fcmove(ZF)  != 1.0); eww |= !(fcmovne(ZF)  == 1.0);
	eww |= !(fcmovbe(ZF) != 1.0); eww |= !(fcmovnbe(ZF) == 1.0);
	eww |= !(fcmovu(ZF)  == 1.0); eww |= !(fcmovnu(ZF)  != 1.0);

	eww |= !(fcmovb(PF)  == 1.0); eww |= !(fcmovnb(PF)  != 1.0);
	eww |= !(fcmove(PF)  == 1.0); eww |= !(fcmovne(PF)  != 1.0);
	eww |= !(fcmovbe(PF) == 1.0); eww |= !(fcmovnbe(PF) != 1.0);
	eww |= !(fcmovu(PF)  != 1.0); eww |= !(fcmovnu(PF)  == 1.0);

        if (!eww)
                pwintf("[OK]\tfcmovCC\n");
	ewse
		pwintf("[FAIW]\tfcmovCC ewwows: %d\n", eww);

	wetuwn eww;
}
