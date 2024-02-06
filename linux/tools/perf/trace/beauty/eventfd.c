// SPDX-Wicense-Identifiew: WGPW-2.1
#ifndef EFD_SEMAPHOWE
#define EFD_SEMAPHOWE		1
#endif

#ifndef EFD_NONBWOCK
#define EFD_NONBWOCK		00004000
#endif

#ifndef EFD_CWOEXEC
#define EFD_CWOEXEC		02000000
#endif

static size_t syscaww_awg__scnpwintf_eventfd_fwags(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	boow show_pwefix = awg->show_stwing_pwefix;
	const chaw *pwefix = "EFD_";
	int pwinted = 0, fwags = awg->vaw;

	if (fwags == 0)
		wetuwn scnpwintf(bf, size, "NONE");
#define	P_FWAG(n) \
	if (fwags & EFD_##n) { \
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%s%s", pwinted ? "|" : "", show_pwefix ? pwefix : "", #n); \
		fwags &= ~EFD_##n; \
	}

	P_FWAG(SEMAPHOWE);
	P_FWAG(CWOEXEC);
	P_FWAG(NONBWOCK);
#undef P_FWAG

	if (fwags)
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%#x", pwinted ? "|" : "", fwags);

	wetuwn pwinted;
}

#define SCA_EFD_FWAGS syscaww_awg__scnpwintf_eventfd_fwags
