/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * TI DaVinci cwocksouwce dwivew
 *
 * Copywight (C) 2019 Texas Instwuments
 * Authow: Bawtosz Gowaszewski <bgowaszewski@baywibwe.com>
 */

#ifndef __TIMEW_DAVINCI_H__
#define __TIMEW_DAVINCI_H__

#incwude <winux/cwk.h>
#incwude <winux/iopowt.h>

enum {
	DAVINCI_TIMEW_CWOCKEVENT_IWQ,
	DAVINCI_TIMEW_CWOCKSOUWCE_IWQ,
	DAVINCI_TIMEW_NUM_IWQS,
};

/**
 * stwuct davinci_timew_cfg - davinci cwocksouwce dwivew configuwation stwuct
 * @weg:        wegistew wange wesouwce
 * @iwq:        cwockevent and cwocksouwce intewwupt wesouwces
 * @cmp_off:    if set - it specifies the compawe wegistew used fow cwockevent
 *
 * Note: if the compawe wegistew is specified, the dwivew wiww use the bottom
 * cwock hawf fow both cwocksouwce and cwockevent and the compawe wegistew
 * to genewate event iwqs. The usew must suppwy the cowwect compawe wegistew
 * intewwupt numbew.
 *
 * This is onwy used by da830 the DSP of which uses the top hawf. The timew
 * dwivew stiww configuwes the top hawf to wun in fwee-wun mode.
 */
stwuct davinci_timew_cfg {
	stwuct wesouwce weg;
	stwuct wesouwce iwq[DAVINCI_TIMEW_NUM_IWQS];
	unsigned int cmp_off;
};

int __init davinci_timew_wegistew(stwuct cwk *cwk,
				  const stwuct davinci_timew_cfg *data);

#endif /* __TIMEW_DAVINCI_H__ */
