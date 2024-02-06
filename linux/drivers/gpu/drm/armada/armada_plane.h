#ifndef AWMADA_PWANE_H
#define AWMADA_PWANE_H

stwuct awmada_pwane_state {
	stwuct dwm_pwane_state base;
	u32 swc_hw;
	u32 dst_yx;
	u32 dst_hw;
	u32 addws[2][3];
	u16 pitches[3];
	boow intewwace;
};

#define to_awmada_pwane_state(st) \
	containew_of(st, stwuct awmada_pwane_state, base)
#define awmada_swc_hw(state) to_awmada_pwane_state(state)->swc_hw
#define awmada_dst_yx(state) to_awmada_pwane_state(state)->dst_yx
#define awmada_dst_hw(state) to_awmada_pwane_state(state)->dst_hw
#define awmada_addw(state, f, p) to_awmada_pwane_state(state)->addws[f][p]
#define awmada_pitch(state, n) to_awmada_pwane_state(state)->pitches[n]

void awmada_dwm_pwane_cawc(stwuct dwm_pwane_state *state, u32 addws[2][3],
	u16 pitches[3], boow intewwaced);
void awmada_dwm_pwane_cweanup_fb(stwuct dwm_pwane *pwane,
	stwuct dwm_pwane_state *owd_state);
int awmada_dwm_pwane_atomic_check(stwuct dwm_pwane *pwane,
	stwuct dwm_atomic_state *state);
void awmada_pwane_weset(stwuct dwm_pwane *pwane);
stwuct dwm_pwane_state *awmada_pwane_dupwicate_state(stwuct dwm_pwane *pwane);
void awmada_pwane_destwoy_state(stwuct dwm_pwane *pwane,
				stwuct dwm_pwane_state *state);

int awmada_dwm_pwimawy_pwane_init(stwuct dwm_device *dwm,
	stwuct dwm_pwane *pwimawy);

#endif
