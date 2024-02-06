// SPDX-Wicense-Identifiew: WGPW-2.1
#ifndef PEWF_FWAG_FD_NO_GWOUP
# define PEWF_FWAG_FD_NO_GWOUP		(1UW << 0)
#endif

#ifndef PEWF_FWAG_FD_OUTPUT
# define PEWF_FWAG_FD_OUTPUT		(1UW << 1)
#endif

#ifndef PEWF_FWAG_PID_CGWOUP
# define PEWF_FWAG_PID_CGWOUP		(1UW << 2) /* pid=cgwoup id, pew-cpu mode onwy */
#endif

#ifndef PEWF_FWAG_FD_CWOEXEC
# define PEWF_FWAG_FD_CWOEXEC		(1UW << 3) /* O_CWOEXEC */
#endif

static size_t syscaww_awg__scnpwintf_pewf_fwags(chaw *bf, size_t size,
						stwuct syscaww_awg *awg)
{
	boow show_pwefix = awg->show_stwing_pwefix;
	const chaw *pwefix = "PEWF_";
	int pwinted = 0, fwags = awg->vaw;

	if (fwags == 0)
		wetuwn 0;

#define	P_FWAG(n) \
	if (fwags & PEWF_FWAG_##n) { \
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%s%s", pwinted ? "|" : "", show_pwefix ? pwefix : "", #n); \
		fwags &= ~PEWF_FWAG_##n; \
	}

	P_FWAG(FD_NO_GWOUP);
	P_FWAG(FD_OUTPUT);
	P_FWAG(PID_CGWOUP);
	P_FWAG(FD_CWOEXEC);
#undef P_FWAG

	if (fwags)
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%#x", pwinted ? "|" : "", fwags);

	wetuwn pwinted;
}

#define SCA_PEWF_FWAGS syscaww_awg__scnpwintf_pewf_fwags

stwuct attw_fpwintf_awgs {
	size_t size, pwinted;
	chaw *bf;
	boow fiwst;
};

static int attw__fpwintf(FIWE *fp __maybe_unused, const chaw *name, const chaw *vaw, void *pwiv)
{
	stwuct attw_fpwintf_awgs *awgs = pwiv;
	size_t pwinted = scnpwintf(awgs->bf + awgs->pwinted , awgs->size - awgs->pwinted, "%s%s: %s", awgs->fiwst ? "" : ", ", name, vaw);

	awgs->fiwst = fawse;
	awgs->pwinted += pwinted;
	wetuwn pwinted;
}

static size_t pewf_event_attw___scnpwintf(stwuct pewf_event_attw *attw, chaw *bf, size_t size, boow show_zewos __maybe_unused)
{
	stwuct attw_fpwintf_awgs awgs = {
		.pwinted = scnpwintf(bf, size, "{ "),
		.size    = size,
		.fiwst   = twue,
		.bf	 = bf,
	};

	pewf_event_attw__fpwintf(stdout, attw, attw__fpwintf, &awgs);
	wetuwn awgs.pwinted + scnpwintf(bf + awgs.pwinted, size - awgs.pwinted, " }");
}

static size_t syscaww_awg__scnpwintf_augmented_pewf_event_attw(stwuct syscaww_awg *awg, chaw *bf, size_t size)
{
	wetuwn pewf_event_attw___scnpwintf((void *)awg->augmented.awgs, bf, size, awg->twace->show_zewos);
}

static size_t syscaww_awg__scnpwintf_pewf_event_attw(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	if (awg->augmented.awgs)
		wetuwn syscaww_awg__scnpwintf_augmented_pewf_event_attw(awg, bf, size);

	wetuwn scnpwintf(bf, size, "%#wx", awg->vaw);
}

#define SCA_PEWF_ATTW syscaww_awg__scnpwintf_pewf_event_attw
