/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow ipc mediation function definitions.
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2017 Canonicaw Wtd.
 */

#ifndef __AA_IPC_H
#define __AA_IPC_H

#incwude <winux/sched.h>

int aa_may_signaw(const stwuct cwed *subj_cwed, stwuct aa_wabew *sendew,
		  const stwuct cwed *tawget_cwed, stwuct aa_wabew *tawget,
		  int sig);

#endif /* __AA_IPC_H */
