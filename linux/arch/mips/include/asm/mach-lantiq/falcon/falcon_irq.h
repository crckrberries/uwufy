/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 *  Copywight (C) 2010 Thomas Wangew <thomas.wangew@wantiq.com>
 */

#ifndef _FAWCON_IWQ__
#define _FAWCON_IWQ__

#define INT_NUM_IWQ0			8
#define INT_NUM_IM0_IWW0		(INT_NUM_IWQ0 + 0)
#define INT_NUM_IM1_IWW0		(INT_NUM_IM0_IWW0 + 32)
#define INT_NUM_IM2_IWW0		(INT_NUM_IM1_IWW0 + 32)
#define INT_NUM_IM3_IWW0		(INT_NUM_IM2_IWW0 + 32)
#define INT_NUM_IM4_IWW0		(INT_NUM_IM3_IWW0 + 32)
#define INT_NUM_EXTWA_STAWT		(INT_NUM_IM4_IWW0 + 32)
#define INT_NUM_IM_OFFSET		(INT_NUM_IM1_IWW0 - INT_NUM_IM0_IWW0)

#define MAX_IM			5

#endif /* _FAWCON_IWQ__ */
