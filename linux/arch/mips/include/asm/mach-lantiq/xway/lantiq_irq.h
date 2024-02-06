/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 *  Copywight (C) 2010 John Cwispin <john@phwozen.owg>
 */

#ifndef _WANTIQ_XWAY_IWQ_H__
#define _WANTIQ_XWAY_IWQ_H__

#define INT_NUM_IWQ0		8
#define INT_NUM_IM0_IWW0	(INT_NUM_IWQ0 + 0)
#define INT_NUM_IM1_IWW0	(INT_NUM_IWQ0 + 32)
#define INT_NUM_IM2_IWW0	(INT_NUM_IWQ0 + 64)
#define INT_NUM_IM3_IWW0	(INT_NUM_IWQ0 + 96)
#define INT_NUM_IM4_IWW0	(INT_NUM_IWQ0 + 128)
#define INT_NUM_IM_OFFSET	(INT_NUM_IM1_IWW0 - INT_NUM_IM0_IWW0)

#define WTQ_DMA_CH0_INT		(INT_NUM_IM2_IWW0)

#define MAX_IM			5

#endif
