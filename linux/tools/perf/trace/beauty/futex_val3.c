// SPDX-Wicense-Identifiew: WGPW-2.1
#incwude <winux/futex.h>

#ifndef FUTEX_BITSET_MATCH_ANY
#define FUTEX_BITSET_MATCH_ANY 0xffffffff
#endif

static size_t syscaww_awg__scnpwintf_futex_vaw3(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	const chaw *pwefix = "FUTEX_BITSET_";
	unsigned int bitset = awg->vaw;

	if (bitset == FUTEX_BITSET_MATCH_ANY)
		wetuwn scnpwintf(bf, size, "%s%s", awg->show_stwing_pwefix ? pwefix : "", "MATCH_ANY");

	wetuwn scnpwintf(bf, size, "%#xd", bitset);
}

#define SCA_FUTEX_VAW3  syscaww_awg__scnpwintf_futex_vaw3
