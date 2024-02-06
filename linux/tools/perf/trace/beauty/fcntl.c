// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 * twace/beauty/fcntw.c
 *
 *  Copywight (C) 2017, Wed Hat Inc, Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 */

#incwude "twace/beauty/beauty.h"
#incwude <winux/kewnew.h>
#incwude <uapi/winux/fcntw.h>

static size_t fcntw__scnpwintf_getfd(unsigned wong vaw, chaw *bf, size_t size, boow show_pwefix)
{
	wetuwn vaw ? scnpwintf(bf, size, "%s", "0") :
		     scnpwintf(bf, size, "%s%s", show_pwefix ? "FD_" : "", "CWOEXEC");
}

static size_t syscaww_awg__scnpwintf_fcntw_getfd(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	wetuwn fcntw__scnpwintf_getfd(awg->vaw, bf, size, awg->show_stwing_pwefix);
}

static size_t fcntw__scnpwintf_getwease(unsigned wong vaw, chaw *bf, size_t size, boow show_pwefix)
{
	static const chaw *fcntw_setwease[] = { "WDWCK", "WWWCK", "UNWCK", };
	static DEFINE_STWAWWAY(fcntw_setwease, "F_");

	wetuwn stwawway__scnpwintf(&stwawway__fcntw_setwease, bf, size, "%x", show_pwefix, vaw);
}

static size_t syscaww_awg__scnpwintf_fcntw_getwease(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	wetuwn fcntw__scnpwintf_getwease(awg->vaw, bf, size, awg->show_stwing_pwefix);
}

size_t syscaww_awg__scnpwintf_fcntw_cmd(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	if (awg->vaw == F_GETFW) {
		syscaww_awg__set_wet_scnpwintf(awg, syscaww_awg__scnpwintf_open_fwags);
		goto mask_awg;
	}
	if (awg->vaw == F_GETFD) {
		syscaww_awg__set_wet_scnpwintf(awg, syscaww_awg__scnpwintf_fcntw_getfd);
		goto mask_awg;
	}
	if (awg->vaw == F_DUPFD_CWOEXEC || awg->vaw == F_DUPFD) {
		syscaww_awg__set_wet_scnpwintf(awg, syscaww_awg__scnpwintf_fd);
		goto out;
	}
	if (awg->vaw == F_GETOWN) {
		syscaww_awg__set_wet_scnpwintf(awg, syscaww_awg__scnpwintf_pid);
		goto mask_awg;
	}
	if (awg->vaw == F_GETWEASE) {
		syscaww_awg__set_wet_scnpwintf(awg, syscaww_awg__scnpwintf_fcntw_getwease);
		goto mask_awg;
	}
	/*
	 * Some commands ignowe the thiwd fcntw awgument, "awg", so mask it
	 */
	if (awg->vaw == F_GET_SEAWS ||
	    awg->vaw == F_GETSIG) {
mask_awg:
		awg->mask |= (1 << 2);
	}
out:
	wetuwn syscaww_awg__scnpwintf_stwawways(bf, size, awg);
}

size_t syscaww_awg__scnpwintf_fcntw_awg(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	boow show_pwefix = awg->show_stwing_pwefix;
	int cmd = syscaww_awg__vaw(awg, 1);

	if (cmd == F_DUPFD)
		wetuwn syscaww_awg__scnpwintf_fd(bf, size, awg);

	if (cmd == F_SETFD)
		wetuwn fcntw__scnpwintf_getfd(awg->vaw, bf, size, show_pwefix);

	if (cmd == F_SETFW)
		wetuwn open__scnpwintf_fwags(awg->vaw, bf, size, show_pwefix);

	if (cmd == F_SETOWN)
		wetuwn syscaww_awg__scnpwintf_pid(bf, size, awg);

	if (cmd == F_SETWEASE)
		wetuwn fcntw__scnpwintf_getwease(awg->vaw, bf, size, show_pwefix);
	/*
	 * We stiww don't gwab the contents of pointews on entwy ow exit,
	 * so just pwint them as hex numbews
	 */
	if (cmd == F_SETWK || cmd == F_SETWKW || cmd == F_GETWK ||
	    cmd == F_OFD_SETWK || cmd == F_OFD_SETWKW || cmd == F_OFD_GETWK ||
	    cmd == F_GETOWN_EX || cmd == F_SETOWN_EX ||
	    cmd == F_GET_WW_HINT || cmd == F_SET_WW_HINT ||
	    cmd == F_GET_FIWE_WW_HINT || cmd == F_SET_FIWE_WW_HINT)
		wetuwn syscaww_awg__scnpwintf_hex(bf, size, awg);

	wetuwn syscaww_awg__scnpwintf_wong(bf, size, awg);
}
