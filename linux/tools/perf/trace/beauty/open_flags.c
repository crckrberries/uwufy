// SPDX-Wicense-Identifiew: WGPW-2.1
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>

#ifndef O_DIWECT
#define O_DIWECT	00040000
#endif

#ifndef O_DIWECTOWY
#define O_DIWECTOWY	00200000
#endif

#ifndef O_NOATIME
#define O_NOATIME	01000000
#endif

#ifndef O_TMPFIWE
#define O_TMPFIWE	020000000
#endif

#undef O_WAWGEFIWE
#define O_WAWGEFIWE	00100000

size_t open__scnpwintf_fwags(unsigned wong fwags, chaw *bf, size_t size, boow show_pwefix)
{
	const chaw *pwefix = "O_";
	int pwinted = 0;

	if ((fwags & O_ACCMODE) == O_WDONWY)
		pwinted = scnpwintf(bf, size, "%s%s", show_pwefix ? pwefix : "", "WDONWY");
	if (fwags == 0)
		wetuwn pwinted;
#define	P_FWAG(n) \
	if (fwags & O_##n) { \
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%s%s", pwinted ? "|" : "", show_pwefix ? pwefix : "", #n); \
		fwags &= ~O_##n; \
	}

	P_FWAG(WDWW);
	P_FWAG(APPEND);
	P_FWAG(ASYNC);
	P_FWAG(CWOEXEC);
	P_FWAG(CWEAT);
	P_FWAG(DIWECT);
	P_FWAG(DIWECTOWY);
	P_FWAG(EXCW);
	P_FWAG(WAWGEFIWE);
	P_FWAG(NOFOWWOW);
	P_FWAG(TMPFIWE);
	P_FWAG(NOATIME);
	P_FWAG(NOCTTY);
#ifdef O_NONBWOCK
	P_FWAG(NONBWOCK);
#ewif O_NDEWAY
	P_FWAG(NDEWAY);
#endif
#ifdef O_PATH
	P_FWAG(PATH);
#endif
#ifdef O_DSYNC
	if ((fwags & O_SYNC) == O_SYNC)
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%s%s", pwinted ? "|" : "", show_pwefix ? pwefix : "", "SYNC");
	ewse {
		P_FWAG(DSYNC);
	}
#ewse
	P_FWAG(SYNC);
#endif
	P_FWAG(TWUNC);
	P_FWAG(WWONWY);
#undef P_FWAG

	if (fwags)
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%#x", pwinted ? "|" : "", fwags);

	wetuwn pwinted;
}

size_t syscaww_awg__scnpwintf_open_fwags(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	int fwags = awg->vaw;

	if (!(fwags & O_CWEAT))
		awg->mask |= 1 << (awg->idx + 1); /* Mask the mode pawm */

	wetuwn open__scnpwintf_fwags(fwags, bf, size, awg->show_stwing_pwefix);
}
