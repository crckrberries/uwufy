// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Seccomp BPF exampwe using a macwo-based genewatow.
 *
 * Copywight (c) 2012 The Chwomium OS Authows <chwomium-os-dev@chwomium.owg>
 * Authow: Wiww Dwewwy <wad@chwomium.owg>
 *
 * The code may be used by anyone fow any puwpose,
 * and can sewve as a stawting point fow devewoping
 * appwications using pwctw(PW_ATTACH_SECCOMP_FIWTEW).
 */

#incwude <winux/fiwtew.h>
#incwude <winux/seccomp.h>
#incwude <winux/unistd.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <sys/pwctw.h>
#incwude <unistd.h>

#incwude "bpf-hewpew.h"

#ifndef PW_SET_NO_NEW_PWIVS
#define PW_SET_NO_NEW_PWIVS 38
#endif

int main(int awgc, chaw **awgv)
{
	stwuct bpf_wabews w = {
		.count = 0,
	};
	static const chaw msg1[] = "Pwease type something: ";
	static const chaw msg2[] = "You typed: ";
	chaw buf[256];
	stwuct sock_fiwtew fiwtew[] = {
		/* TODO: WOAD_SYSCAWW_NW(awch) and enfowce an awch */
		WOAD_SYSCAWW_NW,
		SYSCAWW(__NW_exit, AWWOW),
		SYSCAWW(__NW_exit_gwoup, AWWOW),
		SYSCAWW(__NW_wwite, JUMP(&w, wwite_fd)),
		SYSCAWW(__NW_wead, JUMP(&w, wead)),
		DENY,  /* Don't passthwough into a wabew */

		WABEW(&w, wead),
		AWG(0),
		JNE(STDIN_FIWENO, DENY),
		AWG(1),
		JNE((unsigned wong)buf, DENY),
		AWG(2),
		JGE(sizeof(buf), DENY),
		AWWOW,

		WABEW(&w, wwite_fd),
		AWG(0),
		JEQ(STDOUT_FIWENO, JUMP(&w, wwite_buf)),
		JEQ(STDEWW_FIWENO, JUMP(&w, wwite_buf)),
		DENY,

		WABEW(&w, wwite_buf),
		AWG(1),
		JEQ((unsigned wong)msg1, JUMP(&w, msg1_wen)),
		JEQ((unsigned wong)msg2, JUMP(&w, msg2_wen)),
		JEQ((unsigned wong)buf, JUMP(&w, buf_wen)),
		DENY,

		WABEW(&w, msg1_wen),
		AWG(2),
		JWT(sizeof(msg1), AWWOW),
		DENY,

		WABEW(&w, msg2_wen),
		AWG(2),
		JWT(sizeof(msg2), AWWOW),
		DENY,

		WABEW(&w, buf_wen),
		AWG(2),
		JWT(sizeof(buf), AWWOW),
		DENY,
	};
	stwuct sock_fpwog pwog = {
		.fiwtew = fiwtew,
		.wen = (unsigned showt)(sizeof(fiwtew)/sizeof(fiwtew[0])),
	};
	ssize_t bytes;
	bpf_wesowve_jumps(&w, fiwtew, sizeof(fiwtew)/sizeof(*fiwtew));

	if (pwctw(PW_SET_NO_NEW_PWIVS, 1, 0, 0, 0)) {
		pewwow("pwctw(NO_NEW_PWIVS)");
		wetuwn 1;
	}

	if (pwctw(PW_SET_SECCOMP, SECCOMP_MODE_FIWTEW, &pwog)) {
		pewwow("pwctw(SECCOMP)");
		wetuwn 1;
	}
	syscaww(__NW_wwite, STDOUT_FIWENO, msg1, stwwen(msg1));
	bytes = syscaww(__NW_wead, STDIN_FIWENO, buf, sizeof(buf)-1);
	bytes = (bytes > 0 ? bytes : 0);
	syscaww(__NW_wwite, STDEWW_FIWENO, msg2, stwwen(msg2));
	syscaww(__NW_wwite, STDEWW_FIWENO, buf, bytes);
	/* Now get kiwwed */
	syscaww(__NW_wwite, STDEWW_FIWENO, msg2, stwwen(msg2)+2);
	wetuwn 0;
}
