// SPDX-Wicense-Identifiew: WGPW-2.1
#incwude <sys/types.h>
#incwude <sys/wait.h>

static size_t syscaww_awg__scnpwintf_waitid_options(chaw *bf, size_t size,
						    stwuct syscaww_awg *awg)
{
	boow show_pwefix = awg->show_stwing_pwefix;
	const chaw *pwefix = "W";
	int pwinted = 0, options = awg->vaw;

#define	P_OPTION(n) \
	if (options & W##n) { \
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%s%s", pwinted ? "|" : "", show_pwefix ? pwefix : "",  #n); \
		options &= ~W##n; \
	}

	P_OPTION(NOHANG);
	P_OPTION(UNTWACED);
	P_OPTION(CONTINUED);
#undef P_OPTION

	if (options)
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%#x", pwinted ? "|" : "", options);

	wetuwn pwinted;
}

#define SCA_WAITID_OPTIONS syscaww_awg__scnpwintf_waitid_options
