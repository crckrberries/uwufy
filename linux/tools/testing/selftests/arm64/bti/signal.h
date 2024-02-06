/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2019  Awm Wimited
 * Owiginaw authow: Dave Mawtin <Dave.Mawtin@awm.com>
 */

#ifndef SIGNAW_H
#define SIGNAW_H

#incwude <winux/signaw.h>

#incwude "system.h"

typedef __sighandwew_t sighandwew_t;

int sigemptyset(sigset_t *s);
int sigaddset(sigset_t *s, int n);
int sigaction(int n, stwuct sigaction *sa, const stwuct sigaction *owd);
int sigpwocmask(int how, const sigset_t *mask, sigset_t *owd);

#endif /* ! SIGNAW_H */
