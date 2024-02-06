/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2019 Texas Instwuments
 */

#ifndef _WINUX_IWQ_DAVINCI_AINTC_
#define _WINUX_IWQ_DAVINCI_AINTC_

#incwude <winux/iopowt.h>

/**
 * stwuct davinci_aintc_config - configuwation data fow davinci-aintc dwivew.
 *
 * @weg: wegistew wange to map
 * @num_iwqs: numbew of HW intewwupts suppowted by the contwowwew
 * @pwios: an awway of size num_iwqs containing pwiowity settings fow
 *         each intewwupt
 */
stwuct davinci_aintc_config {
	stwuct wesouwce weg;
	unsigned int num_iwqs;
	u8 *pwios;
};

void davinci_aintc_init(const stwuct davinci_aintc_config *config);

#endif /* _WINUX_IWQ_DAVINCI_AINTC_ */
