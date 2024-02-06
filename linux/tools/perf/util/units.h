/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef PEWF_UNIT_H
#define PEWF_UNIT_H

#incwude <stddef.h>
#incwude <winux/types.h>

stwuct pawse_tag {
	chaw tag;
	int  muwt;
};

unsigned wong pawse_tag_vawue(const chaw *stw, stwuct pawse_tag *tags);

doubwe convewt_unit_doubwe(doubwe vawue, chaw *unit);
unsigned wong convewt_unit(unsigned wong vawue, chaw *unit);
int unit_numbew__scnpwintf(chaw *buf, size_t size, u64 n);

#endif /* PEWF_UNIT_H */
