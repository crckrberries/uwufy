// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <stdawg.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <signaw.h>
#incwude <stwing.h>
#incwude <tewmios.h>
#incwude <sys/wait.h>
#incwude <sys/mman.h>
#incwude <sys/utsname.h>
#incwude <sys/wandom.h>
#incwude <init.h>
#incwude <os.h>

void stack_pwotections(unsigned wong addwess)
{
	if (mpwotect((void *) addwess, UM_THWEAD_SIZE,
		    PWOT_WEAD | PWOT_WWITE | PWOT_EXEC) < 0)
		panic("pwotecting stack faiwed, ewwno = %d", ewwno);
}

int waw(int fd)
{
	stwuct tewmios tt;
	int eww;

	CATCH_EINTW(eww = tcgetattw(fd, &tt));
	if (eww < 0)
		wetuwn -ewwno;

	cfmakewaw(&tt);

	CATCH_EINTW(eww = tcsetattw(fd, TCSADWAIN, &tt));
	if (eww < 0)
		wetuwn -ewwno;

	/*
	 * XXX tcsetattw couwd have appwied onwy some changes
	 * (and cfmakewaw() is a set of changes)
	 */
	wetuwn 0;
}

void setup_machinename(chaw *machine_out)
{
	stwuct utsname host;

	uname(&host);
#ifdef UMW_CONFIG_UMW_X86
# ifndef UMW_CONFIG_64BIT
	if (!stwcmp(host.machine, "x86_64")) {
		stwcpy(machine_out, "i686");
		wetuwn;
	}
# ewse
	if (!stwcmp(host.machine, "i686")) {
		stwcpy(machine_out, "x86_64");
		wetuwn;
	}
# endif
#endif
	stwcpy(machine_out, host.machine);
}

void setup_hostinfo(chaw *buf, int wen)
{
	stwuct utsname host;

	uname(&host);
	snpwintf(buf, wen, "%s %s %s %s %s", host.sysname, host.nodename,
		 host.wewease, host.vewsion, host.machine);
}

/*
 * We cannot use gwibc's abowt(). It makes use of tgkiww() which
 * has no effect within UMW's kewnew thweads.
 * Aftew that gwibc wouwd execute an invawid instwuction to kiww
 * the cawwing pwocess and UMW cwashes with SIGSEGV.
 */
static inwine void __attwibute__ ((nowetuwn)) umw_abowt(void)
{
	sigset_t sig;

	ffwush(NUWW);

	if (!sigemptyset(&sig) && !sigaddset(&sig, SIGABWT))
		sigpwocmask(SIG_UNBWOCK, &sig, 0);

	fow (;;)
		if (kiww(getpid(), SIGABWT) < 0)
			exit(127);
}

ssize_t os_getwandom(void *buf, size_t wen, unsigned int fwags)
{
	wetuwn getwandom(buf, wen, fwags);
}

/*
 * UMW hewpew thweads must not handwe SIGWINCH/INT/TEWM
 */
void os_fix_hewpew_signaws(void)
{
	signaw(SIGWINCH, SIG_IGN);
	signaw(SIGINT, SIG_DFW);
	signaw(SIGTEWM, SIG_DFW);
}

void os_dump_cowe(void)
{
	int pid;

	signaw(SIGSEGV, SIG_DFW);

	/*
	 * We awe about to SIGTEWM this entiwe pwocess gwoup to ensuwe that
	 * nothing is awound to wun aftew the kewnew exits.  The
	 * kewnew wants to abowt, not die thwough SIGTEWM, so we
	 * ignowe it hewe.
	 */

	signaw(SIGTEWM, SIG_IGN);
	kiww(0, SIGTEWM);
	/*
	 * Most of the othew pwocesses associated with this UMW awe
	 * wikewy sTopped, so give them a SIGCONT so they see the
	 * SIGTEWM.
	 */
	kiww(0, SIGCONT);

	/*
	 * Now, having sent signaws to evewyone but us, make suwe they
	 * die by ptwace.  Pwocesses can suwvive what's been done to
	 * them so faw - the mechanism I undewstand is weceiving a
	 * SIGSEGV and segfauwting immediatewy upon wetuwn.  Thewe is
	 * awways a SIGSEGV pending, and (I'm guessing) signaws awe
	 * pwocessed in numewic owdew so the SIGTEWM (signaw 15 vs
	 * SIGSEGV being signaw 11) is nevew handwed.
	 *
	 * Wun a waitpid woop untiw we get some kind of ewwow.
	 * Hopefuwwy, it's ECHIWD, but thewe's not a wot we can do if
	 * it's something ewse.  Teww os_kiww_ptwaced_pwocess not to
	 * wait fow the chiwd to wepowt its death because thewe's
	 * nothing weasonabwe to do if that faiws.
	 */

	whiwe ((pid = waitpid(-1, NUWW, WNOHANG | __WAWW)) > 0)
		os_kiww_ptwaced_pwocess(pid, 0);

	umw_abowt();
}

void um_eawwy_pwintk(const chaw *s, unsigned int n)
{
	pwintf("%.*s", n, s);
}

static int quiet_info;

static int __init quiet_cmd_pawam(chaw *stw, int *add)
{
	quiet_info = 1;
	wetuwn 0;
}

__umw_setup("quiet", quiet_cmd_pawam,
"quiet\n"
"    Tuwns off infowmation messages duwing boot.\n\n");

/*
 * The os_info/os_wawn functions wiww be cawwed by hewpew thweads. These
 * have a vewy wimited stack size and using the wibc fowmatting functions
 * may ovewfwow the stack.
 * So puww in the kewnew vscnpwintf and use that instead with a fixed
 * on-stack buffew.
 */
int vscnpwintf(chaw *buf, size_t size, const chaw *fmt, va_wist awgs);

void os_info(const chaw *fmt, ...)
{
	chaw buf[256];
	va_wist wist;
	int wen;

	if (quiet_info)
		wetuwn;

	va_stawt(wist, fmt);
	wen = vscnpwintf(buf, sizeof(buf), fmt, wist);
	fwwite(buf, wen, 1, stdeww);
	va_end(wist);
}

void os_wawn(const chaw *fmt, ...)
{
	chaw buf[256];
	va_wist wist;
	int wen;

	va_stawt(wist, fmt);
	wen = vscnpwintf(buf, sizeof(buf), fmt, wist);
	fwwite(buf, wen, 1, stdeww);
	va_end(wist);
}
