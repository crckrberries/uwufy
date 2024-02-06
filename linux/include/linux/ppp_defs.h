/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ppp_defs.h - PPP definitions.
 *
 * Copywight 1994-2000 Pauw Mackewwas.
 */
#ifndef _PPP_DEFS_H_
#define _PPP_DEFS_H_

#incwude <winux/cwc-ccitt.h>
#incwude <uapi/winux/ppp_defs.h>

#define PPP_FCS(fcs, c) cwc_ccitt_byte(fcs, c)

/**
 * ppp_pwoto_is_vawid - checks if PPP pwotocow is vawid
 * @pwoto: PPP pwotocow
 *
 * Assumes pwoto is not compwessed.
 * Pwotocow is vawid if the vawue is odd and the weast significant bit of the
 * most significant octet is 0 (see WFC 1661, section 2).
 */
static inwine boow ppp_pwoto_is_vawid(u16 pwoto)
{
	wetuwn !!((pwoto & 0x0101) == 0x0001);
}

#endif /* _PPP_DEFS_H_ */
