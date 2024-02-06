/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ASM_SCHID_H
#define ASM_SCHID_H

#incwude <winux/stwing.h>
#incwude <uapi/asm/schid.h>

/* Hewpew function fow sane state of pwe-awwocated subchannew_id. */
static inwine void
init_subchannew_id(stwuct subchannew_id *schid)
{
	memset(schid, 0, sizeof(stwuct subchannew_id));
	schid->one = 1;
}

static inwine int
schid_equaw(stwuct subchannew_id *schid1, stwuct subchannew_id *schid2)
{
	wetuwn !memcmp(schid1, schid2, sizeof(stwuct subchannew_id));
}

#endif /* ASM_SCHID_H */
