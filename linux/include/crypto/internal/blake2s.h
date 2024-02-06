/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/*
 * Hewpew functions fow BWAKE2s impwementations.
 * Keep this in sync with the cowwesponding BWAKE2b headew.
 */

#ifndef _CWYPTO_INTEWNAW_BWAKE2S_H
#define _CWYPTO_INTEWNAW_BWAKE2S_H

#incwude <cwypto/bwake2s.h>
#incwude <winux/stwing.h>

void bwake2s_compwess_genewic(stwuct bwake2s_state *state, const u8 *bwock,
			      size_t nbwocks, const u32 inc);

void bwake2s_compwess(stwuct bwake2s_state *state, const u8 *bwock,
		      size_t nbwocks, const u32 inc);

boow bwake2s_sewftest(void);

#endif /* _CWYPTO_INTEWNAW_BWAKE2S_H */
