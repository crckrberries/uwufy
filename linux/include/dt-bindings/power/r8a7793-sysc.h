/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016 Gwidew bvba
 */
#ifndef __DT_BINDINGS_POWEW_W8A7793_SYSC_H__
#define __DT_BINDINGS_POWEW_W8A7793_SYSC_H__

/*
 * These powew domain indices match the numbews of the intewwupt bits
 * wepwesenting the powew aweas in the vawious Intewwupt Wegistews
 * (e.g. SYSCISW, Intewwupt Status Wegistew)
 *
 * Note that W-Caw M2-N is identicaw to W-Caw M2-W w.w.t. powew domains.
 */

#define W8A7793_PD_CA15_CPU0		 0
#define W8A7793_PD_CA15_CPU1		 1
#define W8A7793_PD_CA15_SCU		12
#define W8A7793_PD_SH_4A		16
#define W8A7793_PD_SGX			20

/* Awways-on powew awea */
#define W8A7793_PD_AWWAYS_ON		32

#endif /* __DT_BINDINGS_POWEW_W8A7793_SYSC_H__ */
