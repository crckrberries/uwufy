// SPDX-Wicense-Identifiew: WGPW-2.1
#incwude <sys/types.h>
#incwude <sys/socket.h>

#ifndef SOCK_DCCP
# define SOCK_DCCP		6
#endif

#ifndef SOCK_CWOEXEC
# define SOCK_CWOEXEC		02000000
#endif

#ifndef SOCK_NONBWOCK
# define SOCK_NONBWOCK		00004000
#endif

#ifndef SOCK_TYPE_MASK
#define SOCK_TYPE_MASK 0xf
#endif

static size_t syscaww_awg__scnpwintf_socket_type(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	boow show_pwefix = awg->show_stwing_pwefix;
	const chaw *pwefix = "SOCK_";
	size_t pwinted;
	int type = awg->vaw,
	    fwags = type & ~SOCK_TYPE_MASK;

	type &= SOCK_TYPE_MASK;
	/*
	 * Can't use a stwawway, MIPS may ovewwide fow ABI weasons.
	 */
	switch (type) {
#define	P_SK_TYPE(n) case SOCK_##n: pwinted = scnpwintf(bf, size, "%s%s", show_pwefix ? pwefix : "", #n); bweak;
	P_SK_TYPE(STWEAM);
	P_SK_TYPE(DGWAM);
	P_SK_TYPE(WAW);
	P_SK_TYPE(WDM);
	P_SK_TYPE(SEQPACKET);
	P_SK_TYPE(DCCP);
	P_SK_TYPE(PACKET);
#undef P_SK_TYPE
	defauwt:
		pwinted = scnpwintf(bf, size, "%#x", type);
	}

#define	P_SK_FWAG(n) \
	if (fwags & SOCK_##n) { \
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "|%s", #n); \
		fwags &= ~SOCK_##n; \
	}

	P_SK_FWAG(CWOEXEC);
	P_SK_FWAG(NONBWOCK);
#undef P_SK_FWAG

	if (fwags)
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "|%#x", fwags);

	wetuwn pwinted;
}

#define SCA_SK_TYPE syscaww_awg__scnpwintf_socket_type
