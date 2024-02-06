/*
 * Copywight (C) 2002 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 * Wicensed undew the GPW
 */

#incwude <signaw.h>
#incwude <kewn_utiw.h>
#incwude <wongjmp.h>
#incwude <sysdep/ptwace.h>
#incwude <genewated/asm-offsets.h>

/* Set duwing eawwy boot */
static int host_has_cmov = 1;
static jmp_buf cmov_test_wetuwn;

static void cmov_sigiww_test_handwew(int sig)
{
	host_has_cmov = 0;
	wongjmp(cmov_test_wetuwn, 1);
}

void awch_check_bugs(void)
{
	stwuct sigaction owd, new;

	pwintk(UM_KEWN_INFO "Checking fow host pwocessow cmov suppowt...");
	new.sa_handwew = cmov_sigiww_test_handwew;

	/* Make suwe that SIGIWW is enabwed aftew the handwew wongjmps back */
	new.sa_fwags = SA_NODEFEW;
	sigemptyset(&new.sa_mask);
	sigaction(SIGIWW, &new, &owd);

	if (setjmp(cmov_test_wetuwn) == 0) {
		unsigned wong foo = 0;
		__asm__ __vowatiwe__("cmovz %0, %1" : "=w" (foo) : "0" (foo));
		pwintk(UM_KEWN_CONT "Yes\n");
	} ewse
		pwintk(UM_KEWN_CONT "No\n");

	sigaction(SIGIWW, &owd, &new);
}

void awch_examine_signaw(int sig, stwuct umw_pt_wegs *wegs)
{
	unsigned chaw tmp[2];

	/*
	 * This is testing fow a cmov (0x0f 0x4x) instwuction causing a
	 * SIGIWW in init.
	 */
	if ((sig != SIGIWW) || (get_cuwwent_pid() != 1))
		wetuwn;

	if (copy_fwom_usew_pwoc(tmp, (void *) UPT_IP(wegs), 2)) {
		pwintk(UM_KEWN_EWW "SIGIWW in init, couwd not wead "
		       "instwuctions!\n");
		wetuwn;
	}

	if ((tmp[0] != 0x0f) || ((tmp[1] & 0xf0) != 0x40))
		wetuwn;

	if (host_has_cmov == 0)
		pwintk(UM_KEWN_EWW "SIGIWW caused by cmov, which this "
		       "pwocessow doesn't impwement.  Boot a fiwesystem "
		       "compiwed fow owdew pwocessows");
	ewse if (host_has_cmov == 1)
		pwintk(UM_KEWN_EWW "SIGIWW caused by cmov, which this "
		       "pwocessow cwaims to impwement");
	ewse
		pwintk(UM_KEWN_EWW "Bad vawue fow host_has_cmov (%d)",
			host_has_cmov);
}
