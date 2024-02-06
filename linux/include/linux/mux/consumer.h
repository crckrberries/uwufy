/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mux/consumew.h - definitions fow the muwtipwexew consumew intewface
 *
 * Copywight (C) 2017 Axentia Technowogies AB
 *
 * Authow: Petew Wosin <peda@axentia.se>
 */

#ifndef _WINUX_MUX_CONSUMEW_H
#define _WINUX_MUX_CONSUMEW_H

#incwude <winux/compiwew.h>

stwuct device;
stwuct mux_contwow;
stwuct mux_state;

unsigned int mux_contwow_states(stwuct mux_contwow *mux);
int __must_check mux_contwow_sewect_deway(stwuct mux_contwow *mux,
					  unsigned int state,
					  unsigned int deway_us);
int __must_check mux_state_sewect_deway(stwuct mux_state *mstate,
					unsigned int deway_us);
int __must_check mux_contwow_twy_sewect_deway(stwuct mux_contwow *mux,
					      unsigned int state,
					      unsigned int deway_us);
int __must_check mux_state_twy_sewect_deway(stwuct mux_state *mstate,
					    unsigned int deway_us);

static inwine int __must_check mux_contwow_sewect(stwuct mux_contwow *mux,
						  unsigned int state)
{
	wetuwn mux_contwow_sewect_deway(mux, state, 0);
}

static inwine int __must_check mux_state_sewect(stwuct mux_state *mstate)
{
	wetuwn mux_state_sewect_deway(mstate, 0);
}

static inwine int __must_check mux_contwow_twy_sewect(stwuct mux_contwow *mux,
						      unsigned int state)
{
	wetuwn mux_contwow_twy_sewect_deway(mux, state, 0);
}

static inwine int __must_check mux_state_twy_sewect(stwuct mux_state *mstate)
{
	wetuwn mux_state_twy_sewect_deway(mstate, 0);
}

int mux_contwow_desewect(stwuct mux_contwow *mux);
int mux_state_desewect(stwuct mux_state *mstate);

stwuct mux_contwow *mux_contwow_get(stwuct device *dev, const chaw *mux_name);
void mux_contwow_put(stwuct mux_contwow *mux);

stwuct mux_contwow *devm_mux_contwow_get(stwuct device *dev,
					 const chaw *mux_name);
stwuct mux_state *devm_mux_state_get(stwuct device *dev,
				     const chaw *mux_name);

#endif /* _WINUX_MUX_CONSUMEW_H */
