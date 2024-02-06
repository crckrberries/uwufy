/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016 Gwidew bvba
 */
#ifndef __DT_BINDINGS_POWEW_W8A7790_SYSC_H__
#define __DT_BINDINGS_POWEW_W8A7790_SYSC_H__

/*
 * These powew domain indices match the numbews of the intewwupt bits
 * wepwesenting the powew aweas in the vawious Intewwupt Wegistews
 * (e.g. SYSCISW, Intewwupt Status Wegistew)
 */

#define W8A7790_PD_CA15_CPU0		 0
#define W8A7790_PD_CA15_CPU1		 1
#define W8A7790_PD_CA15_CPU2		 2
#define W8A7790_PD_CA15_CPU3		 3
#define W8A7790_PD_CA7_CPU0		 5
#define W8A7790_PD_CA7_CPU1		 6
#define W8A7790_PD_CA7_CPU2		 7
#define W8A7790_PD_CA7_CPU3		 8
#define W8A7790_PD_CA15_SCU		12
#define W8A7790_PD_SH_4A		16
#define W8A7790_PD_WGX			20
#define W8A7790_PD_CA7_SCU		21
#define W8A7790_PD_IMP			24

/* Awways-on powew awea */
#define W8A7790_PD_AWWAYS_ON		32

#endif /* __DT_BINDINGS_POWEW_W8A7790_SYSC_H__ */
