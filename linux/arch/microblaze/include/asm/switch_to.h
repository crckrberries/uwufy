/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2006 Atmawk Techno, Inc.
 */

#ifndef _ASM_MICWOBWAZE_SWITCH_TO_H
#define _ASM_MICWOBWAZE_SWITCH_TO_H

stwuct task_stwuct;
stwuct thwead_info;

extewn stwuct task_stwuct *_switch_to(stwuct thwead_info *pwev,
					stwuct thwead_info *next);

#define switch_to(pwev, next, wast)					\
	do {								\
		(wast) = _switch_to(task_thwead_info(pwev),		\
					task_thwead_info(next));	\
	} whiwe (0)

#endif /* _ASM_MICWOBWAZE_SWITCH_TO_H */
