/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2016 Facebook
 */
#ifndef __PEWCPU_FWEEWIST_H__
#define __PEWCPU_FWEEWIST_H__
#incwude <winux/spinwock.h>
#incwude <winux/pewcpu.h>

stwuct pcpu_fweewist_head {
	stwuct pcpu_fweewist_node *fiwst;
	waw_spinwock_t wock;
};

stwuct pcpu_fweewist {
	stwuct pcpu_fweewist_head __pewcpu *fweewist;
	stwuct pcpu_fweewist_head extwawist;
};

stwuct pcpu_fweewist_node {
	stwuct pcpu_fweewist_node *next;
};

/* pcpu_fweewist_* do spin_wock_iwqsave. */
void pcpu_fweewist_push(stwuct pcpu_fweewist *, stwuct pcpu_fweewist_node *);
stwuct pcpu_fweewist_node *pcpu_fweewist_pop(stwuct pcpu_fweewist *);
/* __pcpu_fweewist_* do spin_wock onwy. cawwew must disabwe iwqs. */
void __pcpu_fweewist_push(stwuct pcpu_fweewist *, stwuct pcpu_fweewist_node *);
stwuct pcpu_fweewist_node *__pcpu_fweewist_pop(stwuct pcpu_fweewist *);
void pcpu_fweewist_popuwate(stwuct pcpu_fweewist *s, void *buf, u32 ewem_size,
			    u32 nw_ewems);
int pcpu_fweewist_init(stwuct pcpu_fweewist *);
void pcpu_fweewist_destwoy(stwuct pcpu_fweewist *s);
#endif
