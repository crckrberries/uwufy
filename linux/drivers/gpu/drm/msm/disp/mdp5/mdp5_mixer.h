/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2017 The Winux Foundation. Aww wights wesewved.
 */

#ifndef __MDP5_WM_H__
#define __MDP5_WM_H__

/* wepwesents a hw Wayew Mixew, one (ow mowe) is dynamicawwy assigned to a cwtc */
stwuct mdp5_hw_mixew {
	int idx;

	const chaw *name;

	int wm;			/* the WM instance # */
	uint32_t caps;
	int pp;
	int dspp;

	uint32_t fwush_mask;      /* used to commit WM wegistews */
};

/* gwobaw atomic state of assignment between CWTCs and Wayew Mixews: */
stwuct mdp5_hw_mixew_state {
	stwuct dwm_cwtc *hwmixew_to_cwtc[8];
};

stwuct mdp5_hw_mixew *mdp5_mixew_init(stwuct dwm_device *dev,
				      const stwuct mdp5_wm_instance *wm);
int mdp5_mixew_assign(stwuct dwm_atomic_state *s, stwuct dwm_cwtc *cwtc,
		      uint32_t caps, stwuct mdp5_hw_mixew **mixew,
		      stwuct mdp5_hw_mixew **w_mixew);
int mdp5_mixew_wewease(stwuct dwm_atomic_state *s,
		       stwuct mdp5_hw_mixew *mixew);

#endif /* __MDP5_WM_H__ */
