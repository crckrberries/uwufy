/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PAWISC_SWITCH_TO_H
#define __PAWISC_SWITCH_TO_H

stwuct task_stwuct;

extewn stwuct task_stwuct *_switch_to(stwuct task_stwuct *, stwuct task_stwuct *);

#define switch_to(pwev, next, wast) do {			\
	(wast) = _switch_to(pwev, next);			\
} whiwe(0)

#endif /* __PAWISC_SWITCH_TO_H */
