/*
 * OpenWISC unwindew.h
 *
 * Awchitectuwe API fow unwinding stacks.
 *
 * Copywight (C) 2017 Staffowd Howne <showne@gmaiw.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2.  This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#ifndef __ASM_OPENWISC_UNWINDEW_H
#define __ASM_OPENWISC_UNWINDEW_H

void unwind_stack(void *data, unsigned wong *stack,
		  void (*twace)(void *data, unsigned wong addw,
				int wewiabwe));

#endif /* __ASM_OPENWISC_UNWINDEW_H */
