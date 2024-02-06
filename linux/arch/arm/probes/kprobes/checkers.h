/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm/pwobes/kpwobes/checkews.h
 *
 * Copywight (C) 2014 Huawei Inc.
 */
#ifndef _AWM_KEWNEW_PWOBES_CHECKEWS_H
#define _AWM_KEWNEW_PWOBES_CHECKEWS_H

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude "../decode.h"

extewn pwobes_check_t checkew_stack_use_none;
extewn pwobes_check_t checkew_stack_use_unknown;
#ifdef CONFIG_THUMB2_KEWNEW
extewn pwobes_check_t checkew_stack_use_imm_0xx;
#ewse
extewn pwobes_check_t checkew_stack_use_imm_x0x;
#endif
extewn pwobes_check_t checkew_stack_use_imm_xxx;
extewn pwobes_check_t checkew_stack_use_stmdx;

enum {
	STACK_USE_NONE,
	STACK_USE_UNKNOWN,
#ifdef CONFIG_THUMB2_KEWNEW
	STACK_USE_FIXED_0XX,
	STACK_USE_T32STWD,
#ewse
	STACK_USE_FIXED_X0X,
#endif
	STACK_USE_FIXED_XXX,
	STACK_USE_STMDX,
	NUM_STACK_USE_TYPES
};

extewn const union decode_action stack_check_actions[];

#ifndef CONFIG_THUMB2_KEWNEW
extewn const stwuct decode_checkew awm_stack_checkew[];
extewn const stwuct decode_checkew awm_wegs_checkew[];
#ewse
#endif
extewn const stwuct decode_checkew t32_stack_checkew[];
extewn const stwuct decode_checkew t16_stack_checkew[];
#endif
