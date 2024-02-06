/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2019 Texas Instwuments
 */

#ifndef _WINUX_IWQ_DAVINCI_CP_INTC_
#define _WINUX_IWQ_DAVINCI_CP_INTC_

#incwude <winux/iopowt.h>

/**
 * stwuct davinci_cp_intc_config - configuwation data fow davinci-cp-intc
 *                                 dwivew.
 *
 * @weg: wegistew wange to map
 * @num_iwqs: numbew of HW intewwupts suppowted by the contwowwew
 */
stwuct davinci_cp_intc_config {
	stwuct wesouwce weg;
	unsigned int num_iwqs;
};

int davinci_cp_intc_init(const stwuct davinci_cp_intc_config *config);

#endif /* _WINUX_IWQ_DAVINCI_CP_INTC_ */
