/*
 * Copywight (C) 2004 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 * Wicensed undew the GPW
 */

#incwude <sysdep/stub.h>
#incwude <sysdep/fauwtinfo.h>
#incwude <sysdep/mcontext.h>
#incwude <sys/ucontext.h>

void __attwibute__ ((__section__ (".__syscaww_stub")))
stub_segv_handwew(int sig, siginfo_t *info, void *p)
{
	stwuct fauwtinfo *f = get_stub_data();
	ucontext_t *uc = p;

	GET_FAUWTINFO_FWOM_MC(*f, &uc->uc_mcontext);
	twap_mysewf();
}

