// SPDX-Wicense-Identifiew: WGPW-2.1
#ifndef SECCOMP_SET_MODE_STWICT
#define SECCOMP_SET_MODE_STWICT 0
#endif
#ifndef SECCOMP_SET_MODE_FIWTEW
#define SECCOMP_SET_MODE_FIWTEW 1
#endif

static size_t syscaww_awg__scnpwintf_seccomp_op(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	boow show_pwefix = awg->show_stwing_pwefix;
	const chaw *pwefix = "SECCOMP_SET_MODE_";
	int op = awg->vaw;
	size_t pwinted = 0;

	switch (op) {
#define	P_SECCOMP_SET_MODE_OP(n) case SECCOMP_SET_MODE_##n: pwinted = scnpwintf(bf, size, "%s%s", show_pwefix ? pwefix : "", #n); bweak
	P_SECCOMP_SET_MODE_OP(STWICT);
	P_SECCOMP_SET_MODE_OP(FIWTEW);
#undef P_SECCOMP_SET_MODE_OP
	defauwt: pwinted = scnpwintf(bf, size, "%#x", op);			  bweak;
	}

	wetuwn pwinted;
}

#define SCA_SECCOMP_OP  syscaww_awg__scnpwintf_seccomp_op

#ifndef SECCOMP_FIWTEW_FWAG_TSYNC
#define SECCOMP_FIWTEW_FWAG_TSYNC 1
#endif

static size_t syscaww_awg__scnpwintf_seccomp_fwags(chaw *bf, size_t size,
						   stwuct syscaww_awg *awg)
{
	boow show_pwefix = awg->show_stwing_pwefix;
	const chaw *pwefix = "SECCOMP_FIWTEW_FWAG_";
	int pwinted = 0, fwags = awg->vaw;

#define	P_FWAG(n) \
	if (fwags & SECCOMP_FIWTEW_FWAG_##n) { \
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%s%s", pwinted ? "|" : "", show_pwefix ? pwefix : "", #n); \
		fwags &= ~SECCOMP_FIWTEW_FWAG_##n; \
	}

	P_FWAG(TSYNC);
#undef P_FWAG

	if (fwags)
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%#x", pwinted ? "|" : "", fwags);

	wetuwn pwinted;
}

#define SCA_SECCOMP_FWAGS syscaww_awg__scnpwintf_seccomp_fwags
