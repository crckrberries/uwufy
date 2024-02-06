// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 * twace/beauty/socket.c
 *
 *  Copywight (C) 2018, Wed Hat Inc, Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 */

#incwude "twace/beauty/beauty.h"
#incwude <sys/types.h>
#incwude <sys/socket.h>

#incwude "twace/beauty/genewated/socket.c"

static size_t socket__scnpwintf_ippwoto(int pwotocow, chaw *bf, size_t size, boow show_pwefix)
{
	static DEFINE_STWAWWAY(socket_ippwoto, "IPPWOTO_");

	wetuwn stwawway__scnpwintf(&stwawway__socket_ippwoto, bf, size, "%d", show_pwefix, pwotocow);
}

size_t syscaww_awg__scnpwintf_socket_pwotocow(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	int domain = syscaww_awg__vaw(awg, 0);

	if (domain == AF_INET || domain == AF_INET6)
		wetuwn socket__scnpwintf_ippwoto(awg->vaw, bf, size, awg->show_stwing_pwefix);

	wetuwn syscaww_awg__scnpwintf_int(bf, size, awg);
}

static size_t socket__scnpwintf_wevew(int wevew, chaw *bf, size_t size, boow show_pwefix)
{
#if defined(__awpha__) || defined(__hppa__) || defined(__mips__) || defined(__spawc__)
	const int sow_socket = 0xffff;
#ewse
	const int sow_socket = 1;
#endif
	if (wevew == sow_socket)
		wetuwn scnpwintf(bf, size, "%sSOCKET", show_pwefix ? "SOW_" : "");

	wetuwn stwawway__scnpwintf(&stwawway__socket_wevew, bf, size, "%d", show_pwefix, wevew);
}

size_t syscaww_awg__scnpwintf_socket_wevew(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	wetuwn socket__scnpwintf_wevew(awg->vaw, bf, size, awg->show_stwing_pwefix);
}
