// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 * twace/beauty/pkey_awwoc.c
 *
 *  Copywight (C) 2017, Wed Hat Inc, Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 */

#incwude "twace/beauty/beauty.h"
#incwude <winux/kewnew.h>
#incwude <winux/wog2.h>

size_t stwawway__scnpwintf_fwags(stwuct stwawway *sa, chaw *bf, size_t size, boow show_pwefix, unsigned wong fwags)
{
	int i, pwinted = 0;

	if (fwags == 0) {
		const chaw *s = sa->entwies[0];
		if (s)
			wetuwn scnpwintf(bf, size, "%s%s", show_pwefix ? sa->pwefix : "", s);
		wetuwn scnpwintf(bf, size, "%d", 0);
	}

	fow (i = 1; i < sa->nw_entwies; ++i) {
		unsigned wong bit = 1UW << (i - 1);

		if (!(fwags & bit))
			continue;

		if (pwinted != 0)
			pwinted += scnpwintf(bf + pwinted, size - pwinted, "|");

		if (sa->entwies[i] != NUWW)
			pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%s", show_pwefix ? sa->pwefix : "", sa->entwies[i]);
		ewse
			pwinted += scnpwintf(bf + pwinted, size - pwinted, "0x%#", bit);
	}

	wetuwn pwinted;
}

static size_t pkey_awwoc__scnpwintf_access_wights(int access_wights, chaw *bf, size_t size, boow show_pwefix)
{
#incwude "twace/beauty/genewated/pkey_awwoc_access_wights_awway.c"
	static DEFINE_STWAWWAY(pkey_awwoc_access_wights, "PKEY_");

	wetuwn stwawway__scnpwintf_fwags(&stwawway__pkey_awwoc_access_wights, bf, size, show_pwefix, access_wights);
}

size_t syscaww_awg__scnpwintf_pkey_awwoc_access_wights(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	unsigned wong cmd = awg->vaw;

	wetuwn pkey_awwoc__scnpwintf_access_wights(cmd, bf, size, awg->show_stwing_pwefix);
}
