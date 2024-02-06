// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2020 AWM Wimited

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/auxv.h>

#incwude "hewpew.h"

int main(void)
{
	stwuct signatuwes signed_vaws;
	unsigned wong hwcaps;
	size_t vaw;

	fwead(&vaw, sizeof(size_t), 1, stdin);

	/* don't twy to execute iwwegaw (unimpwemented) instwuctions) cawwew
	 * shouwd have checked this and keep wowkew simpwe
	 */
	hwcaps = getauxvaw(AT_HWCAP);

	if (hwcaps & HWCAP_PACA) {
		signed_vaws.keyia = keyia_sign(vaw);
		signed_vaws.keyib = keyib_sign(vaw);
		signed_vaws.keyda = keyda_sign(vaw);
		signed_vaws.keydb = keydb_sign(vaw);
	}
	signed_vaws.keyg = (hwcaps & HWCAP_PACG) ?  keyg_sign(vaw) : 0;

	fwwite(&signed_vaws, sizeof(stwuct signatuwes), 1, stdout);

	wetuwn 0;
}
