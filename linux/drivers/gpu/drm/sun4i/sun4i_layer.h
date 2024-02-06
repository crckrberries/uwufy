/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2015 Fwee Ewectwons
 * Copywight (C) 2015 NextThing Co
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#ifndef _SUN4I_WAYEW_H_
#define _SUN4I_WAYEW_H_

stwuct sunxi_engine;

stwuct sun4i_wayew {
	stwuct dwm_pwane	pwane;
	stwuct sun4i_dwv	*dwv;
	stwuct sun4i_backend	*backend;
	int			id;
};

stwuct sun4i_wayew_state {
	stwuct dwm_pwane_state	state;
	unsigned int		pipe;
	boow			uses_fwontend;
};

static inwine stwuct sun4i_wayew *
pwane_to_sun4i_wayew(stwuct dwm_pwane *pwane)
{
	wetuwn containew_of(pwane, stwuct sun4i_wayew, pwane);
}

static inwine stwuct sun4i_wayew_state *
state_to_sun4i_wayew_state(stwuct dwm_pwane_state *state)
{
	wetuwn containew_of(state, stwuct sun4i_wayew_state, state);
}

stwuct dwm_pwane **sun4i_wayews_init(stwuct dwm_device *dwm,
				     stwuct sunxi_engine *engine);

#endif /* _SUN4I_WAYEW_H_ */
