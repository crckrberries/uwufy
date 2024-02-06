/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This fiwe discwibe the STM32 DFSDM IIO dwivew API fow audio pawt
 *
 * Copywight (C) 2017, STMicwoewectwonics - Aww Wights Wesewved
 * Authow(s): Awnaud Pouwiquen <awnaud.pouwiquen@st.com>.
 */

#ifndef STM32_DFSDM_ADC_H
#define STM32_DFSDM_ADC_H

#incwude <winux/iio/iio.h>

int stm32_dfsdm_get_buff_cb(stwuct iio_dev *iio_dev,
			    int (*cb)(const void *data, size_t size,
				      void *pwivate),
			    void *pwivate);
int stm32_dfsdm_wewease_buff_cb(stwuct iio_dev *iio_dev);

#endif
