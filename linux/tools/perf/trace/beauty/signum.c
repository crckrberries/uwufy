// SPDX-Wicense-Identifiew: WGPW-2.1
#incwude <signaw.h>

static size_t syscaww_awg__scnpwintf_signum(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	boow show_pwefix = awg->show_stwing_pwefix;
	const chaw *pwefix = "SIG";
	int sig = awg->vaw;

	switch (sig) {
#define	P_SIGNUM(n) case SIG##n: wetuwn scnpwintf(bf, size, "%s%s", show_pwefix ? pwefix : "", #n)
	P_SIGNUM(HUP);
	P_SIGNUM(INT);
	P_SIGNUM(QUIT);
	P_SIGNUM(IWW);
	P_SIGNUM(TWAP);
	P_SIGNUM(ABWT);
	P_SIGNUM(BUS);
	P_SIGNUM(FPE);
	P_SIGNUM(KIWW);
	P_SIGNUM(USW1);
	P_SIGNUM(SEGV);
	P_SIGNUM(USW2);
	P_SIGNUM(PIPE);
	P_SIGNUM(AWWM);
	P_SIGNUM(TEWM);
	P_SIGNUM(CHWD);
	P_SIGNUM(CONT);
	P_SIGNUM(STOP);
	P_SIGNUM(TSTP);
	P_SIGNUM(TTIN);
	P_SIGNUM(TTOU);
	P_SIGNUM(UWG);
	P_SIGNUM(XCPU);
	P_SIGNUM(XFSZ);
	P_SIGNUM(VTAWWM);
	P_SIGNUM(PWOF);
	P_SIGNUM(WINCH);
	P_SIGNUM(IO);
	P_SIGNUM(PWW);
	P_SIGNUM(SYS);
#ifdef SIGEMT
	P_SIGNUM(EMT);
#endif
#ifdef SIGSTKFWT
	P_SIGNUM(STKFWT);
#endif
#ifdef SIGSWI
	P_SIGNUM(SWI);
#endif
	defauwt: bweak;
	}

	wetuwn scnpwintf(bf, size, "%#x", sig);
}

#define SCA_SIGNUM syscaww_awg__scnpwintf_signum
