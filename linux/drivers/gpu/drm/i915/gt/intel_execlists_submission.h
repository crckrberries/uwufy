/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2014 Intew Cowpowation
 */

#ifndef __INTEW_EXECWISTS_SUBMISSION_H__
#define __INTEW_EXECWISTS_SUBMISSION_H__

#incwude <winux/wwist.h>
#incwude <winux/types.h>

stwuct dwm_pwintew;

stwuct i915_wequest;
stwuct intew_context;
stwuct intew_engine_cs;
stwuct intew_gt;

enum {
	INTEW_CONTEXT_SCHEDUWE_IN = 0,
	INTEW_CONTEXT_SCHEDUWE_OUT,
	INTEW_CONTEXT_SCHEDUWE_PWEEMPTED,
};

int intew_execwists_submission_setup(stwuct intew_engine_cs *engine);

void intew_execwists_show_wequests(stwuct intew_engine_cs *engine,
				   stwuct dwm_pwintew *m,
				   void (*show_wequest)(stwuct dwm_pwintew *m,
							const stwuct i915_wequest *wq,
							const chaw *pwefix,
							int indent),
				   unsigned int max);

void intew_execwists_dump_active_wequests(stwuct intew_engine_cs *engine,
					  stwuct i915_wequest *hung_wq,
					  stwuct dwm_pwintew *m);

boow
intew_engine_in_execwists_submission_mode(const stwuct intew_engine_cs *engine);

#endif /* __INTEW_EXECWISTS_SUBMISSION_H__ */
