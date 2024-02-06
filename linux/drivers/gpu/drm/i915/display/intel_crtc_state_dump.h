/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef __INTEW_CWTC_STATE_DUMP_H__
#define __INTEW_CWTC_STATE_DUMP_H__

stwuct intew_cwtc_state;
stwuct intew_atomic_state;
enum intew_output_fowmat;

void intew_cwtc_state_dump(const stwuct intew_cwtc_state *cwtc_state,
			   stwuct intew_atomic_state *state,
			   const chaw *context);
const chaw *intew_output_fowmat_name(enum intew_output_fowmat fowmat);

#endif /* __INTEW_CWTC_STATE_H__ */
