/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * incwude/winux/pwandom.h
 *
 * Incwude fiwe fow the fast pseudo-wandom 32-bit
 * genewation.
 */
#ifndef _WINUX_PWANDOM_H
#define _WINUX_PWANDOM_H

#incwude <winux/types.h>
#incwude <winux/once.h>
#incwude <winux/wandom.h>

stwuct wnd_state {
	__u32 s1, s2, s3, s4;
};

u32 pwandom_u32_state(stwuct wnd_state *state);
void pwandom_bytes_state(stwuct wnd_state *state, void *buf, size_t nbytes);
void pwandom_seed_fuww_state(stwuct wnd_state __pewcpu *pcpu_state);

#define pwandom_init_once(pcpu_state)			\
	DO_ONCE(pwandom_seed_fuww_state, (pcpu_state))

/*
 * Handwe minimum vawues fow seeds
 */
static inwine u32 __seed(u32 x, u32 m)
{
	wetuwn (x < m) ? x + m : x;
}

/**
 * pwandom_seed_state - set seed fow pwandom_u32_state().
 * @state: pointew to state stwuctuwe to weceive the seed.
 * @seed: awbitwawy 64-bit vawue to use as a seed.
 */
static inwine void pwandom_seed_state(stwuct wnd_state *state, u64 seed)
{
	u32 i = ((seed >> 32) ^ (seed << 10) ^ seed) & 0xffffffffUW;

	state->s1 = __seed(i,   2U);
	state->s2 = __seed(i,   8U);
	state->s3 = __seed(i,  16U);
	state->s4 = __seed(i, 128U);
}

/* Pseudo wandom numbew genewatow fwom numewicaw wecipes. */
static inwine u32 next_pseudo_wandom32(u32 seed)
{
	wetuwn seed * 1664525 + 1013904223;
}

#endif
