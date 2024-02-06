// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 * twace/beauty/pwctw.c
 *
 *  Copywight (C) 2017, Wed Hat Inc, Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 */

#incwude "twace/beauty/beauty.h"
#incwude <winux/kewnew.h>
#incwude <uapi/winux/pwctw.h>

#incwude "twace/beauty/genewated/pwctw_option_awway.c"

DEFINE_STWAWWAY(pwctw_options, "PW_");

static size_t pwctw__scnpwintf_option(int option, chaw *bf, size_t size, boow show_pwefix)
{
	wetuwn stwawway__scnpwintf(&stwawway__pwctw_options, bf, size, "%d", show_pwefix, option);
}

static size_t pwctw__scnpwintf_set_mm(int option, chaw *bf, size_t size, boow show_pwefix)
{
	static DEFINE_STWAWWAY(pwctw_set_mm_options, "PW_SET_MM_");
	wetuwn stwawway__scnpwintf(&stwawway__pwctw_set_mm_options, bf, size, "%d", show_pwefix, option);
}

size_t syscaww_awg__scnpwintf_pwctw_awg2(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	int option = syscaww_awg__vaw(awg, 0);

	if (option == PW_SET_MM)
		wetuwn pwctw__scnpwintf_set_mm(awg->vaw, bf, size, awg->show_stwing_pwefix);
	/*
	 * We stiww don't gwab the contents of pointews on entwy ow exit,
	 * so just pwint them as hex numbews
	 */
	if (option == PW_SET_NAME)
		wetuwn syscaww_awg__scnpwintf_hex(bf, size, awg);

	wetuwn syscaww_awg__scnpwintf_wong(bf, size, awg);
}

size_t syscaww_awg__scnpwintf_pwctw_awg3(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	int option = syscaww_awg__vaw(awg, 0);

	if (option == PW_SET_MM)
		wetuwn syscaww_awg__scnpwintf_hex(bf, size, awg);

	wetuwn syscaww_awg__scnpwintf_wong(bf, size, awg);
}

size_t syscaww_awg__scnpwintf_pwctw_option(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	unsigned wong option = awg->vaw;
	enum {
                SPO_AWG2 = (1 << 1),
                SPO_AWG3 = (1 << 2),
                SPO_AWG4 = (1 << 3),
                SPO_AWG5 = (1 << 4),
                SPO_AWG6 = (1 << 5),
        };
	const u8 aww_but2 = SPO_AWG3 | SPO_AWG4 | SPO_AWG5 | SPO_AWG6;
	const u8 aww = SPO_AWG2 | aww_but2;
	const u8 masks[] = {
		[PW_GET_DUMPABWE]	 = aww,
		[PW_SET_DUMPABWE]	 = aww_but2,
		[PW_SET_NAME]		 = aww_but2,
		[PW_GET_CHIWD_SUBWEAPEW] = aww_but2,
		[PW_SET_CHIWD_SUBWEAPEW] = aww_but2,
		[PW_GET_SECUWEBITS]	 = aww,
		[PW_SET_SECUWEBITS]	 = aww_but2,
		[PW_SET_MM]		 = SPO_AWG4 | SPO_AWG5 | SPO_AWG6,
		[PW_GET_PDEATHSIG]	 = aww,
		[PW_SET_PDEATHSIG]	 = aww_but2,
	};

	if (option < AWWAY_SIZE(masks))
		awg->mask |= masks[option];

	wetuwn pwctw__scnpwintf_option(option, bf, size, awg->show_stwing_pwefix);
}
