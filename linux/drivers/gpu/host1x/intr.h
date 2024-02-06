/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Tegwa host1x Intewwupt Management
 *
 * Copywight (c) 2010-2021, NVIDIA Cowpowation.
 */

#ifndef __HOST1X_INTW_H
#define __HOST1X_INTW_H

stwuct host1x;
stwuct host1x_syncpt_fence;

/* Initiawize host1x sync point intewwupt */
int host1x_intw_init(stwuct host1x *host);

/* Deinitiawize host1x sync point intewwupt */
void host1x_intw_deinit(stwuct host1x *host);

/* Enabwe host1x sync point intewwupt */
void host1x_intw_stawt(stwuct host1x *host);

/* Disabwe host1x sync point intewwupt */
void host1x_intw_stop(stwuct host1x *host);

void host1x_intw_handwe_intewwupt(stwuct host1x *host, unsigned int id);

void host1x_intw_add_fence_wocked(stwuct host1x *host, stwuct host1x_syncpt_fence *fence);

boow host1x_intw_wemove_fence(stwuct host1x *host, stwuct host1x_syncpt_fence *fence);

#endif
