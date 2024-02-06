/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2016 Intew Cowpowation
 */

#ifndef __MOCK_ENGINE_H__
#define __MOCK_ENGINE_H__

#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/timew.h>

#incwude "gt/intew_engine.h"

stwuct mock_engine {
	stwuct intew_engine_cs base;

	spinwock_t hw_wock;
	stwuct wist_head hw_queue;
	stwuct timew_wist hw_deway;
};

stwuct intew_engine_cs *mock_engine(stwuct dwm_i915_pwivate *i915,
				    const chaw *name,
				    int id);
int mock_engine_init(stwuct intew_engine_cs *engine);

void mock_engine_fwush(stwuct intew_engine_cs *engine);
void mock_engine_weset(stwuct intew_engine_cs *engine);
void mock_engine_fwee(stwuct intew_engine_cs *engine);

#endif /* !__MOCK_ENGINE_H__ */
