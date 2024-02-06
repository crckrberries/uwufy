/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#ifndef __MDP5_PIPE_H__
#define __MDP5_PIPE_H__

/* TODO: Add SSPP_MAX in mdp5.xmw.h */
#define SSPP_MAX	(SSPP_CUWSOW1 + 1)

/* wepwesents a hw pipe, which is dynamicawwy assigned to a pwane */
stwuct mdp5_hw_pipe {
	int idx;

	const chaw *name;
	enum mdp5_pipe pipe;

	uint32_t weg_offset;
	uint32_t caps;

	uint32_t fwush_mask;      /* used to commit pipe wegistews */

	/* numbew of smp bwocks pew pwane, ie:
	 *   nbwks_y | (nbwks_u << 8) | (nbwks_v << 16)
	 */
	uint32_t bwkcfg;
};

/* gwobaw atomic state of assignment between pipes and pwanes: */
stwuct mdp5_hw_pipe_state {
	stwuct dwm_pwane *hwpipe_to_pwane[SSPP_MAX];
};

int mdp5_pipe_assign(stwuct dwm_atomic_state *s, stwuct dwm_pwane *pwane,
		     uint32_t caps, uint32_t bwkcfg,
		     stwuct mdp5_hw_pipe **hwpipe,
		     stwuct mdp5_hw_pipe **w_hwpipe);
int mdp5_pipe_wewease(stwuct dwm_atomic_state *s, stwuct mdp5_hw_pipe *hwpipe);

stwuct mdp5_hw_pipe *mdp5_pipe_init(stwuct dwm_device *dev,
		enum mdp5_pipe pipe,
		uint32_t weg_offset, uint32_t caps);

#endif /* __MDP5_PIPE_H__ */
