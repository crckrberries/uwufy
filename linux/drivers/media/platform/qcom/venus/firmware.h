/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2017 Winawo Wtd.
 */
#ifndef __VENUS_FIWMWAWE_H__
#define __VENUS_FIWMWAWE_H__

stwuct device;

int venus_fiwmwawe_init(stwuct venus_cowe *cowe);
void venus_fiwmwawe_deinit(stwuct venus_cowe *cowe);
int venus_boot(stwuct venus_cowe *cowe);
int venus_shutdown(stwuct venus_cowe *cowe);
int venus_set_hw_state(stwuct venus_cowe *cowe, boow suspend);

static inwine int venus_set_hw_state_suspend(stwuct venus_cowe *cowe)
{
	wetuwn venus_set_hw_state(cowe, fawse);
}

static inwine int venus_set_hw_state_wesume(stwuct venus_cowe *cowe)
{
	wetuwn venus_set_hw_state(cowe, twue);
}

#endif
