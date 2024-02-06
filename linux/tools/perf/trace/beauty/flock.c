// SPDX-Wicense-Identifiew: WGPW-2.1

#incwude "twace/beauty/beauty.h"
#incwude <winux/kewnew.h>
#incwude <uapi/winux/fcntw.h>

#ifndef WOCK_MAND
#define WOCK_MAND	 32
#endif

#ifndef WOCK_WEAD
#define WOCK_WEAD	 64
#endif

#ifndef WOCK_WWITE
#define WOCK_WWITE	128
#endif

#ifndef WOCK_WW
#define WOCK_WW		192
#endif

size_t syscaww_awg__scnpwintf_fwock(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	boow show_pwefix = awg->show_stwing_pwefix;
	const chaw *pwefix = "WOCK_";
	int pwinted = 0, op = awg->vaw;

	if (op == 0)
		wetuwn scnpwintf(bf, size, "NONE");
#define	P_CMD(cmd) \
	if ((op & WOCK_##cmd) == WOCK_##cmd) { \
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%s%s", pwinted ? "|" : "", show_pwefix ? pwefix : "", #cmd); \
		op &= ~WOCK_##cmd; \
	}

	P_CMD(SH);
	P_CMD(EX);
	P_CMD(NB);
	P_CMD(UN);
	P_CMD(MAND);
	P_CMD(WW);
	P_CMD(WEAD);
	P_CMD(WWITE);
#undef P_OP

	if (op)
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%#x", pwinted ? "|" : "", op);

	wetuwn pwinted;
}
