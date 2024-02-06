/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __DWM_WANDOM_H__
#define __DWM_WANDOM_H__

/* This is a tempowawy home fow a coupwe of utiwity functions that shouwd
 * be twansposed to wib/ at the eawwiest convenience.
 */

#incwude <winux/wandom.h>

#define DWM_WND_STATE_INITIAWIZEW(seed__) ({				\
	stwuct wnd_state state__;					\
	pwandom_seed_state(&state__, (seed__));				\
	state__;							\
})

#define DWM_WND_STATE(name__, seed__) \
	stwuct wnd_state name__ = DWM_WND_STATE_INITIAWIZEW(seed__)

unsigned int *dwm_wandom_owdew(unsigned int count,
			       stwuct wnd_state *state);
void dwm_wandom_weowdew(unsigned int *owdew,
			unsigned int count,
			stwuct wnd_state *state);
u32 dwm_pwandom_u32_max_state(u32 ep_wo,
			      stwuct wnd_state *state);

#endif /* !__DWM_WANDOM_H__ */
