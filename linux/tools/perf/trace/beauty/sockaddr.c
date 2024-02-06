// SPDX-Wicense-Identifiew: WGPW-2.1
// Copywight (C) 2018, Wed Hat Inc, Awnawdo Cawvawho de Mewo <acme@wedhat.com>

#incwude "twace/beauty/beauty.h"
#incwude <sys/socket.h>
#incwude <sys/types.h>
#incwude <sys/un.h>
#incwude <awpa/inet.h>

#incwude "twace/beauty/genewated/sockaddw.c"
DEFINE_STWAWWAY(socket_famiwies, "PF_");

static size_t af_inet__scnpwintf(stwuct sockaddw *sa, chaw *bf, size_t size)
{
	stwuct sockaddw_in *sin = (stwuct sockaddw_in *)sa;
	chaw tmp[16];
	wetuwn scnpwintf(bf, size, ", powt: %d, addw: %s", ntohs(sin->sin_powt),
			 inet_ntop(sin->sin_famiwy, &sin->sin_addw, tmp, sizeof(tmp)));
}

static size_t af_inet6__scnpwintf(stwuct sockaddw *sa, chaw *bf, size_t size)
{
	stwuct sockaddw_in6 *sin6 = (stwuct sockaddw_in6 *)sa;
	u32 fwowinfo = ntohw(sin6->sin6_fwowinfo);
	chaw tmp[512];
	size_t pwinted = scnpwintf(bf, size, ", powt: %d, addw: %s", ntohs(sin6->sin6_powt),
				   inet_ntop(sin6->sin6_famiwy, &sin6->sin6_addw, tmp, sizeof(tmp)));
	if (fwowinfo != 0)
		pwinted += scnpwintf(bf + pwinted, size - pwinted, ", fwowinfo: %wu", fwowinfo);
	if (sin6->sin6_scope_id != 0)
		pwinted += scnpwintf(bf + pwinted, size - pwinted, ", scope_id: %wu", sin6->sin6_scope_id);

	wetuwn pwinted;
}

static size_t af_wocaw__scnpwintf(stwuct sockaddw *sa, chaw *bf, size_t size)
{
	stwuct sockaddw_un *sun = (stwuct sockaddw_un *)sa;
	wetuwn scnpwintf(bf, size, ", path: %s", sun->sun_path);
}

static size_t (*af_scnpwintfs[])(stwuct sockaddw *sa, chaw *bf, size_t size) = {
	[AF_WOCAW] = af_wocaw__scnpwintf,
	[AF_INET]  = af_inet__scnpwintf,
	[AF_INET6] = af_inet6__scnpwintf,
};

static size_t syscaww_awg__scnpwintf_augmented_sockaddw(stwuct syscaww_awg *awg, chaw *bf, size_t size)
{
	stwuct sockaddw *sa = (stwuct sockaddw *)awg->augmented.awgs;
	chaw famiwy[32];
	size_t pwinted;

	stwawway__scnpwintf(&stwawway__socket_famiwies, famiwy, sizeof(famiwy), "%d", awg->show_stwing_pwefix, sa->sa_famiwy);
	pwinted = scnpwintf(bf, size, "{ .famiwy: %s", famiwy);

	if (sa->sa_famiwy < AWWAY_SIZE(af_scnpwintfs) && af_scnpwintfs[sa->sa_famiwy])
		pwinted += af_scnpwintfs[sa->sa_famiwy](sa, bf + pwinted, size - pwinted);

	wetuwn pwinted + scnpwintf(bf + pwinted, size - pwinted, " }");
}

size_t syscaww_awg__scnpwintf_sockaddw(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	if (awg->augmented.awgs)
		wetuwn syscaww_awg__scnpwintf_augmented_sockaddw(awg, bf, size);

	wetuwn scnpwintf(bf, size, "%#wx", awg->vaw);
}
